#include <cstring>
#include <cmath>

#include <matrix.hpp>


Matrix::Matrix()
{
    memset(this->matrix, 0, sizeof(float)*16);

    this->matrix[0] = 1.;
    this->matrix[5] = 1.;
    this->matrix[10] = 1.;
    this->matrix[15] = 1.;
}

Matrix::Matrix(const Matrix& m)
{
    memcpy(this->matrix, m.matrix, sizeof(float)*16);
}

Matrix Matrix::transpose()
{
    Matrix m(*this);
    m.matrix[1] = this->matrix[4];
    m.matrix[2] = this->matrix[8];
    m.matrix[3] = this->matrix[12];
    m.matrix[6] = this->matrix[9];
    m.matrix[7] = this->matrix[13];
    m.matrix[11] = this->matrix[14];

    m.matrix[4] = this->matrix[1];
    m.matrix[8] = this->matrix[2];
    m.matrix[12] = this->matrix[3];
    m.matrix[9] = this->matrix[6];
    m.matrix[13] = this->matrix[7];
    m.matrix[14] = this->matrix[111];

    return m;
}

Matrix Matrix::translation(float x, float y, float z)
{
    Matrix tmp = Matrix();

    tmp.matrix[3] = x;
    tmp.matrix[7] = y;
    tmp.matrix[11] = z;

    return tmp;
}

Matrix Matrix::rotation_x(float angle)
{
    Matrix R = Matrix();

    R.matrix[5] = R.matrix[10] = cosf(angle);
    R.matrix[6] = -sinf(angle);
    R.matrix[9] = -R.matrix[6];

    return R;
}

Matrix Matrix::rotation_y(float angle)
{
    Matrix R = Matrix();


    R.matrix[0] = R.matrix[10] = cosf(angle);
    R.matrix[2] = sinf(angle);
    R.matrix[8] = -R.matrix[2];

    return R;
}

Matrix Matrix::rotation_z(float angle)
{
    Matrix R = Matrix();


    R.matrix[0] = R.matrix[5] = cosf(angle);
    R.matrix[1] = -sinf(angle);
    R.matrix[4] = -R.matrix[1];

    return R;
}


Matrix Matrix::rotation(float angle, glm::vec3 axis)
{
    Matrix m;
    glm::vec3 n_axe = glm::normalize(axis);
    double c = cos(angle/2.0);
    double s = sin(angle/2.0);
    double qx,qy,qz,qw,xx,yy,zz,xy,xz,yz,xw,yw,zw;

    qx = n_axe[0] * s;
    qy = n_axe[1] * s;
    qz = n_axe[2] * s;
    qw = c;

    xx = qx * qx;
    yy = qy * qy;
    zz = qz * qz;
    xy = qx * qy;
    xz = qx * qz;
    yz = qy * qz;
    xw = qx * qw;
    yw = qy * qw;
    zw = qz * qw;

    m.matrix[0] = 1.0f - 2.0 * ( yy + zz );
    m.matrix[4] = 2.0 * ( xy + zw );
    m.matrix[8] = 2.0 * ( xz - yw );

    m.matrix[1] = 2.0 * ( xy - zw );
    m.matrix[5] = 1.0f - 2.0 * ( xx + zz );
    m.matrix[9] = 2.0 * ( yz + xw );

    m.matrix[2] = 2.0 * ( xz + yw );
    m.matrix[6] = 2.0 * ( yz - xw );
    m.matrix[10]= 1.0f - 2.0 * ( xx + yy );

    return m;
}

Matrix Matrix::homothety(float x, float y, float z)
{
    Matrix H = Matrix();

    H.matrix[0] = x;
    H.matrix[5] = y;
    H.matrix[10] = z;

    return H;
}

Matrix Matrix::perspective(float l,float r,float b,float t,float n,float f)
{
    Matrix m;
    m.matrix[0] = 2.0f * n / (r - l);
    m.matrix[5] = 2.0f * n / (t - b);
    m.matrix[2] = (r + l) / (r - l);
    m.matrix[6] = (t + b) / (t - b);
    m.matrix[10]= -(f + n) / (f - n);
    m.matrix[14]= -1.0f;
    m.matrix[11]= -2.0f * f * n / (f - n);
    m.matrix[15]= 0.0;

    return m;
}

Matrix Matrix::perspective(float fovy,float ratio,float znear,float zfar)
{
    Matrix m;
    double f = 1.0 / tanf(double(fovy) * M_PI / (360.0f)); // 1/tan(fovy/2)
    m.matrix[0] = f / ratio;
    m.matrix[5] = f;
    m.matrix[10]= -(zfar + znear) / (zfar - znear);
    m.matrix[14]= -1.0f;
    m.matrix[11]= -2.0f * zfar * znear / (zfar - znear);
    m.matrix[15]= 0.0;

    return m;
}

Matrix Matrix::look_at(const glm::vec3& eye,const glm::vec3& center,const glm::vec3& up) {
    glm::vec3 z = glm::normalize(eye - center);
    glm::vec3 x = glm::normalize(glm::cross(up, z));
    glm::vec3 y = glm::normalize(glm::cross(z, x));

    Matrix rot;
    rot.matrix[0] = x.r;
    rot.matrix[1] = x.g;
    rot.matrix[2] = x.b;
    rot.matrix[4] = y.r;
    rot.matrix[5] = y.g;
    rot.matrix[6] = y.b;
    rot.matrix[8] = z.r;
    rot.matrix[9] = z.g;
    rot.matrix[10] = z.b;

    Matrix t = Matrix::translation(-eye.x, -eye.y, -eye.z);

    return rot*t;
}

Matrix& Matrix::operator= (const Matrix& m)
{
    memcpy(this->matrix, m.matrix, sizeof(float)*16);
    return *this;
}

Matrix Matrix::operator*(const Matrix &m)
{
    Matrix tmp = Matrix();

    /***  FIRST ROW ***/
    tmp.matrix[0] = matrix[0] * m.matrix[0] + matrix[1] * m.matrix[4] + matrix[2] * m.matrix[8] + matrix[3] * m.matrix[12];
    tmp.matrix[1] = matrix[0] * m.matrix[1] + matrix[1] * m.matrix[5] + matrix[2] * m.matrix[9] + matrix[3] * m.matrix[13];
    tmp.matrix[2] = matrix[0] * m.matrix[2] + matrix[1] * m.matrix[6] + matrix[2] * m.matrix[10] + matrix[3] * m.matrix[14];
    tmp.matrix[3] = matrix[0] * m.matrix[3] + matrix[1] * m.matrix[7] + matrix[2] * m.matrix[11] + matrix[3] * m.matrix[15];

    /***  SECOND ROW ***/
    tmp.matrix[4] = matrix[4] * m.matrix[0] + matrix[5] * m.matrix[4] + matrix[6] * m.matrix[8] + matrix[7] * m.matrix[12];
    tmp.matrix[5] = matrix[4] * m.matrix[1] + matrix[5] * m.matrix[5] + matrix[6] * m.matrix[9] + matrix[7] * m.matrix[13];
    tmp.matrix[6] = matrix[4] * m.matrix[2] + matrix[5] * m.matrix[6] + matrix[6] * m.matrix[10] + matrix[7] * m.matrix[14];
    tmp.matrix[7] = matrix[4] * m.matrix[3] + matrix[5] * m.matrix[7] + matrix[6] * m.matrix[11] + matrix[7] * m.matrix[15];

    /***  THIRD ROW ***/
    tmp.matrix[8] = matrix[8] * m.matrix[0] + matrix[9] * m.matrix[4] + matrix[10] * m.matrix[8] + matrix[11] * m.matrix[12];
    tmp.matrix[9] = matrix[8] * m.matrix[1] + matrix[9] * m.matrix[5] + matrix[10] * m.matrix[9] + matrix[11] * m.matrix[13];
    tmp.matrix[10] = matrix[8] * m.matrix[2] + matrix[9] * m.matrix[6] + matrix[10] * m.matrix[10] + matrix[11] * m.matrix[14];
    tmp.matrix[11] = matrix[8] * m.matrix[3] + matrix[9] * m.matrix[7] + matrix[10] * m.matrix[11] + matrix[11] * m.matrix[15];

    /***  FORTH ROW ***/
    tmp.matrix[12] = matrix[12] * m.matrix[0] + matrix[13] * m.matrix[4] + matrix[14] * m.matrix[8] + matrix[15] * m.matrix[12];
    tmp.matrix[13] = matrix[12] * m.matrix[1] + matrix[13] * m.matrix[5] + matrix[14] * m.matrix[9] + matrix[15] * m.matrix[13];
    tmp.matrix[14] = matrix[12] * m.matrix[2] + matrix[13] * m.matrix[6] + matrix[14] * m.matrix[10] + matrix[15] * m.matrix[14];
    tmp.matrix[15] = matrix[12] * m.matrix[3] + matrix[13] * m.matrix[7] + matrix[14] * m.matrix[11] + matrix[15] * m.matrix[15];

    return tmp;
}

glm::vec3 Matrix::operator*(glm::vec3 v)
{
    float x, y, z, w;
    x = this->matrix[0] * v.x + this->matrix[1] * v.y + this->matrix[2] * v.z + this->matrix[3];
    y = this->matrix[4] * v.x + this->matrix[5] * v.y + this->matrix[6] * v.z + this->matrix[7];
    z = this->matrix[8] * v.x + this->matrix[9] * v.y + this->matrix[10] * v.z + this->matrix[11];
    w = this->matrix[12] * v.x + this->matrix[13] * v.y + this->matrix[14] * v.z + this->matrix[15];
    if( is_zero(w))
    {
        glm::vec3 o(x, y, z);
        return o;
    }
    glm::vec3 out(x / w, y / w, z / w);
    return out;
}

glm::vec4 Matrix::operator*(glm::vec4 v)
{
    float x, y, z, w;
    x = this->matrix[0] * v.x + this->matrix[1] * v.y + this->matrix[2] * v.z + this->matrix[3] * v.w;
    y = this->matrix[4] * v.x + this->matrix[5] * v.y + this->matrix[6] * v.z + this->matrix[7] * v.w;
    z = this->matrix[8] * v.x + this->matrix[9] * v.y + this->matrix[10] * v.z + this->matrix[11] * v.w;
    w = this->matrix[12] * v.x + this->matrix[13] * v.y + this->matrix[14] * v.z + this->matrix[15] * v.w;
    if(is_zero(w))
    {
        glm::vec4 o(x, y, z, 1);
        return o;
    }
    glm::vec4 out(x / w, y / w, z / w, 1);
    return out;
}

Matrix& Matrix::operator*= (const Matrix &m)
{
    Matrix tmp = Matrix(*this);
    /***  FIRST ROW ***/
    matrix[0] = tmp.matrix[0] * m.matrix[0] + tmp.matrix[1] * m.matrix[4] + tmp.matrix[2] * m.matrix[8] + tmp.matrix[3] * m.matrix[12];
    matrix[1] = tmp.matrix[0] * m.matrix[1] + tmp.matrix[1] * m.matrix[5] + tmp.matrix[2] * m.matrix[9] + tmp.matrix[3] * m.matrix[13];
    matrix[2] = tmp.matrix[0] * m.matrix[2] + tmp.matrix[1] * m.matrix[6] + tmp.matrix[2] * m.matrix[10] + tmp.matrix[3] * m.matrix[14];
    matrix[3] = tmp.matrix[0] * m.matrix[3] + tmp.matrix[1] * m.matrix[7] + tmp.matrix[2] * m.matrix[11] + tmp.matrix[3] * m.matrix[15];

    /***  SECOND ROW ***/
    matrix[4] = tmp.matrix[4] * m.matrix[0] + tmp.matrix[5] * m.matrix[4] + tmp.matrix[6] * m.matrix[8] + tmp.matrix[7] * m.matrix[12];
    matrix[5] = tmp.matrix[4] * m.matrix[1] + tmp.matrix[5] * m.matrix[5] + tmp.matrix[6] * m.matrix[9] + tmp.matrix[7] * m.matrix[13];
    matrix[6] = tmp.matrix[4] * m.matrix[2] + tmp.matrix[5] * m.matrix[6] + tmp.matrix[6] * m.matrix[10] + tmp.matrix[7] * m.matrix[14];
    matrix[7] = tmp.matrix[4] * m.matrix[3] + tmp.matrix[5] * m.matrix[7] + tmp.matrix[6] * m.matrix[11] + tmp.matrix[7] * m.matrix[15];

    /***  THIRD ROW ***/
    matrix[8] = tmp.matrix[8] * m.matrix[0] + tmp.matrix[9] * m.matrix[4] + tmp.matrix[10] * m.matrix[8] + tmp.matrix[11] * m.matrix[12];
    matrix[9] = tmp.matrix[8] * m.matrix[1] + tmp.matrix[9] * m.matrix[5] + tmp.matrix[10] * m.matrix[9] + tmp.matrix[11] * m.matrix[13];
    matrix[10] = tmp.matrix[8] * m.matrix[2] + tmp.matrix[9] * m.matrix[6] + tmp.matrix[10] * m.matrix[10] + tmp.matrix[11] * m.matrix[14];
    matrix[11] = tmp.matrix[8] * m.matrix[3] + tmp.matrix[9] * m.matrix[7] + tmp.matrix[10] * m.matrix[11] + tmp.matrix[11] * m.matrix[15];

    /***  FORTH ROW ***/
    matrix[12] = tmp.matrix[12] * m.matrix[0] + tmp.matrix[13] * m.matrix[4] + tmp.matrix[14] * m.matrix[8] + tmp.matrix[15] * m.matrix[12];
    matrix[13] = tmp.matrix[12] * m.matrix[1] + tmp.matrix[13] * m.matrix[5] + tmp.matrix[14] * m.matrix[9] + tmp.matrix[15] * m.matrix[13];
    matrix[14] = tmp.matrix[12] * m.matrix[2] + tmp.matrix[13] * m.matrix[6] + tmp.matrix[14] * m.matrix[10] + tmp.matrix[15] * m.matrix[14];
    matrix[15] = tmp.matrix[12] * m.matrix[3] + tmp.matrix[13] * m.matrix[7] + tmp.matrix[14] * m.matrix[11] + tmp.matrix[15] * m.matrix[15];

    return *this;
}

Matrix::operator float*()
{
    float* tmp = new float[16];
    memcpy(tmp, this->matrix, sizeof(float) * 16);
    return tmp;
}
