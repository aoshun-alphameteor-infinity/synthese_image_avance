#include <shader.hpp>

const std::string shader_name = "blinn_phong_texture";
std::map<std::string, GLuint> Shader::compiled = std::map<std::string, GLuint>();
std::map<std::string, GLuint> Shader::charged = std::map<std::string, GLuint>();

int Shader::check_link_error(GLuint program)
{
    // Get link error log size and print it eventually
    int logLength;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 1)
    {
        char * log = new char[logLength];
        glGetProgramInfoLog(program, logLength, &logLength, log);
        fprintf(stderr, "Link : %s \n", log);
        delete[] log;
    }
    int status;
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if (status == GL_FALSE)
        return -1;
    return 0;
}

GLuint Shader::compile_shader(GLenum shaderType, const char * sourceBuffer, int bufferSize)
{
    GLuint shaderObject = glCreateShader(shaderType);
    const char * sc[1] = { sourceBuffer };
    glShaderSource(shaderObject, 1, sc, NULL);
    glCompileShader(shaderObject);
    check_compile_error(shaderObject, sc);
    return shaderObject;
}

GLuint Shader::compile_shader_from_file(GLenum shaderType, const char * path)
{
    FILE * shaderFileDesc = fopen( path, "rb" );
    if (!shaderFileDesc)
        return 0;
    fseek ( shaderFileDesc , 0 , SEEK_END );
    long fileSize = ftell ( shaderFileDesc );
    rewind ( shaderFileDesc );
    char * buffer = new char[fileSize + 1];
    int nb_char = fread( buffer, 1, fileSize, shaderFileDesc );
    buffer[fileSize] = '\0';
    GLuint shaderObject = compile_shader(shaderType, buffer, fileSize );
    delete[] buffer;
    return shaderObject;
}

int Shader::check_compile_error(GLuint shader, const char ** sourceBuffer)
{
    // Get error log size and print it eventually
    int logLength;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 1)
    {
        char * log = new char[logLength];
        glGetShaderInfoLog(shader, logLength, &logLength, log);
        char *token, *string;
        string = strdup(sourceBuffer[0]);
        int lc = 0;
        while ((token = strsep(&string, "\n")) != NULL) {
           printf("%3d : %s\n", lc, token);
           ++lc;
        }
        fprintf(stderr, "Compile : %s", log);
        delete[] log;
    }
    // If an error happend quit
    int status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE)
        return -1;
    return 0;
}

Shader::Shader(std::string name)
{
    if(this -> compiled.count(name) == 1)
    {
        this -> program = this -> compiled[name];
    }
    else
    {
        char vert_name[100], frag_name[100];
        sprintf(vert_name, "%s.vert", name.c_str());
        sprintf(frag_name, "%s.frag", name.c_str());
        GLuint vertID = compile_shader_from_file(GL_VERTEX_SHADER, vert_name);
        GLuint fragID = compile_shader_from_file(GL_FRAGMENT_SHADER, frag_name);
        this -> program = glCreateProgram();
        glAttachShader(this -> program, vertID);
        glAttachShader(this -> program, fragID);
        glLinkProgram(this -> program);
        if(check_link_error(this -> program) < 0)
        {
            std::cerr << "error when linking " << name << " shader" << std::endl;
            exit(EXIT_FAILURE);
        }
        this -> compiled[name] = this -> program;
    }
    this -> nb_texture = 0;
}

Shader::Shader(const Shader& s)
{
    this -> program = s.program;
    this -> nb_texture = s.nb_texture;
    memcpy(this -> textures, s.textures, nb_max_texture * sizeof(GLuint));
}

GLuint Shader::get_id()
{
    return this -> program;
}

void Shader::attach_texture(std::string texture)
{
    int x, y, comp;
    unsigned char * tex_data;
    GLuint tex;
    if(this -> nb_texture == nb_max_texture)
    {
        throw std::out_of_range("cannot get more textures\n");
    }

    if(this -> charged.count(texture) == 1)
    {
        tex = this -> charged[texture];
    }
    else
    {
        tex_data = stbi_load(texture.c_str(), &x, &y, &comp, 3);

        glGenTextures(1, &tex);

        glBindTexture(GL_TEXTURE_2D, tex);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, tex_data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);

        this -> charged[texture] = tex;
    }
    this -> textures[this -> nb_texture] = tex;
    (this -> nb_texture)++;
}

void Shader::active_textures()
{
    switch(this -> nb_texture)
    {
        case 1:
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, this -> textures[0]);
            break;
        case 2:
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, this -> textures[0]);
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, this -> textures[1]);
            break;
        case 3:
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, this -> textures[0]);
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, this -> textures[1]);
            glActiveTexture(GL_TEXTURE2);
            glBindTexture(GL_TEXTURE_2D, this -> textures[2]);
            break;
        default:
            break;
    }
}

void Shader::upload_textures()
{
    switch(this -> nb_texture)
    {
        case 1:
            glProgramUniform1i(this -> program, textures[0], 0);
            break;
        case 2:
            glProgramUniform1i(this -> program, textures[0], 0);
            glProgramUniform1i(this -> program, textures[1], 1);
            break;
        case 3:
            glProgramUniform1i(this -> program, textures[0], 0);
            glProgramUniform1i(this -> program, textures[1], 1);
            glProgramUniform1i(this -> program, textures[2], 2);
            break;
        default:
            break;
    }
}
