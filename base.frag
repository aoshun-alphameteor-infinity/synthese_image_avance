#version 330

in vec4 color;
layout(location = 0) out vec4 final_col;

void main()
{
  final_col = color;
}
