#ifndef __MATRIX_HPP__
#define __MATRIX_HPP__


    #define GLM_FORCE_RADIANS
    #include <glm/glm.hpp>
    #include <glm/vec4.hpp>
    #include <glm/vec3.hpp>
    #include <tools.hpp>

    class Matrix{
        private:
            float matrix[16];

        public:
            Matrix();
            Matrix(const Matrix& m);

            Matrix transpose();

            static Matrix translation(float x, float y, float z);
            static Matrix rotation_x(float angle);
            static Matrix rotation_y(float angle);
            static Matrix rotation_z(float angle);
            static Matrix rotation(float angle, glm::vec3 axis);
            static Matrix homothety(float x, float y, float z);
            static Matrix perspective(float l,float r,float b,float t,float n,float f);
            static Matrix perspective(float fovy,float ratio,float znear,float zfar);
            static Matrix look_at(const glm::vec3& eye,const glm::vec3& center,const glm::vec3& up);

            Matrix& operator= (const Matrix & m);
            Matrix operator*(const Matrix &m);
            glm::vec3 operator*(glm::vec3 v);
            glm::vec4 operator*(glm::vec4 v);
            Matrix& operator*= (const Matrix &m);
            operator float*();

    };

#endif
