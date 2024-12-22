#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 aTextCoords;

// out vec3 ourColor;
out vec2 textCoords;

uniform mat4 transform;
uniform mat4 rotate;
uniform mat4 scale;

uniform mat4 view;
uniform mat4 projection;

void main() {
  gl_Position = projection * view * transform * rotate * scale * vec4(pos, 1.0);
  textCoords = aTextCoords;
}
