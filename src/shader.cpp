#include <shader.hpp>

int Shader::check_link_error(GLuint program)
{
    std::cerr << "check link error" << std::endl;
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
    std::cerr << "compile shader" << std::endl;
    CHECK_GL;
    GLuint shaderObject = glCreateShader(shaderType);
    std::cerr << "truc" << std::endl;
    const char * sc[1] = { sourceBuffer };
    glShaderSource(shaderObject, 1, sc, NULL);
    glCompileShader(shaderObject);
    check_compile_error(shaderObject, sc);
    return shaderObject;
}

GLuint Shader::compile_shader_from_file(GLenum shaderType, const char * path)
{
    std::cerr << "compile shader from file" << std::endl;
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
    std::cerr << "check compile error" << std::endl;
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
    char vert_name[100], frag_name[100];
    sprintf(vert_name, "%s.vert", name.c_str());
    sprintf(frag_name, "%s.frag", name.c_str());
    std::cerr << "vertex_name is " << vert_name << " and fragment_name is " << frag_name << std::endl;
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

    nb_texture = 0;
}

Shader::Shader(const Shader& s)
{
    this -> program = s.program;
    this -> nb_texture = s.nb_texture;
    memcpy(this -> textures, s.textures, nb_max_texture * sizeof(GLuint));
}

GLuint Shader::get_id()
{
    return program;
}

void Shader::attach_texture(std::string texture)
{
    int x, y, comp;
    unsigned char * tex_data = stbi_load(texture.c_str(), &x, &y, &comp, 3);
    GLuint tex;
    if(nb_texture == nb_max_texture)
    {
        throw std::out_of_range("cannot get more textures\n");
    }

    glGenTextures(1, &tex);

    glBindTexture(GL_TEXTURE_2D, tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, tex_data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    textures[nb_texture] = tex;
    nb_texture++;
}

void Shader::active_textures()
{
    switch(nb_texture)
    {
        case 1:
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, textures[0]);
            break;
        case 2:
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, textures[0]);
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, textures[1]);
            break;
        case 3:
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, textures[0]);
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, textures[1]);
            glActiveTexture(GL_TEXTURE2);
            glBindTexture(GL_TEXTURE_2D, textures[2]);
            break;
        default:
            break;
    }
}

void Shader::upload_textures()
{
    switch(nb_texture)
    {
        case 1:
            glProgramUniform1i(program, textures[0], 0);
            break;
        case 2:
            glProgramUniform1i(program, textures[0], 0);
            glProgramUniform1i(program, textures[1], 1);
            break;
        case 3:
            glProgramUniform1i(program, textures[0], 0);
            glProgramUniform1i(program, textures[1], 1);
            glProgramUniform1i(program, textures[2], 2);
            break;
        default:
            break;
    }
}
