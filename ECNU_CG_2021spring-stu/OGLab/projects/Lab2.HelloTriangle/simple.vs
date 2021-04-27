#version 330 core
layout (location = 0) in vec4 aPos;
void main() {
    gl_Position = vec4(aPos.z, aPos.w, aPos.z, 1.0);
}
