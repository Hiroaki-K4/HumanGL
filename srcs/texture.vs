#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in int aTexIndex;
layout (location = 3) in mat4 aInstanceMatrix;

out vec2 TexCoord;
out vec3 pos;
flat out int TexIndex;

uniform mat4 view;
uniform mat4 projection;

void main() {
    gl_Position = projection * view * aInstanceMatrix * vec4(aPos, 1.0);
    TexCoord = vec2(aTexCoord.x, aTexCoord.y);
    pos = aPos;
    TexIndex = aTexIndex;
}
