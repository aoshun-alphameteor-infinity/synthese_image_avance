#include <camera.hpp>

void Camera::orientation_react()
{
    Matrix matt = Matrix::rotation_y(orientation.y);
    glm::vec3 prod = glm::cross(top_init, direction_init);
    glm::vec3 left_vec = matt * prod;
    Matrix matu = Matrix::rotation(orientation.x, left_vec);
    top_direction = matu * top_init;
    view_direction = matu * (matt * direction_init);
}

Camera::Camera()
{
    position = glm::vec3();
    view_direction = direction_init = glm::vec3(0.0, 0.0, -1.0);
    top_direction = top_init = glm::vec3(0.0, 1.0, 0.0);
    orientation = glm::vec3();
    projection = Matrix::perspective(-1.0 * DEFAULT_LEFT_RIGHT, DEFAULT_LEFT_RIGHT,
                                        -1.0 * DEFAULT_TOP_BOTTOM, DEFAULT_TOP_BOTTOM,
                                        DEFAULT_NEAR, DEFAULT_FAR);
}

Camera::Camera(glm::vec3 pos_init, glm::vec3 dir_init, glm::vec3 top_init, glm::vec3 orient_init)
{
    position = pos_init;
    view_direction= direction_init = dir_init;
    top_direction = this -> top_init = top_init;
    orientation = orient_init;
    orientation_react();
    projection = Matrix::perspective(-1.0 * DEFAULT_LEFT_RIGHT, DEFAULT_LEFT_RIGHT,
                                        -1.0 * DEFAULT_TOP_BOTTOM, DEFAULT_TOP_BOTTOM,
                                        DEFAULT_NEAR, DEFAULT_FAR);
}

void Camera::move_front(float step)
{
    position += view_direction * step;
}

void Camera::move_back(float step)
{
    position -= view_direction * step;
}

void Camera::move_left(float step)
{
    glm::vec3 left_vec = glm::cross(top_direction, view_direction);
    position += left_vec * step;
}

void Camera::move_right(float step)
{
    glm::vec3 left_vec = glm::cross(top_direction, view_direction);
    position -= left_vec*step;
}

void Camera::move_up(float step)
{
    position += top_direction * step;
}

void Camera::move_down(float step)
{
    position -= top_direction * step;
}

void Camera::look_up(float angle)
{
    orientation.x -= angle;
    orientation_react();
}

void Camera::look_down(float angle)
{
    orientation.x += angle;
    orientation_react();
}

void Camera::look_left(float angle)
{
    orientation.y -= angle;
    orientation_react();
}

void Camera::look_right(float angle)
{
    orientation.y += angle;
    orientation_react();
}

Matrix Camera::get_projection()
{
    return projection;
}

void Camera::set_projection(Matrix new_projection)
{
    projection = new_projection;
}

Matrix Camera::get_transformation()
{
    return Matrix::look_at(position, position + view_direction, top_direction);
}

void Camera::set_transformation_GL()
{
    gluLookAt(position.x, position.y, position.z,
      position.x + view_direction.x, position.y + view_direction.y, position.z + view_direction.z,
      top_direction.x, top_direction.y, top_direction.z);
}
