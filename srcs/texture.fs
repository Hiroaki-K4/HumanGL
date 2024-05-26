#version 330 core
out vec4 FragColor;

in vec3 pos;
in vec2 TexCoord;
flat in int TexIndex;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main() {
    if (TexIndex == 0) {
        FragColor = texture(texture1, TexCoord);
    } else {
        FragColor = texture(texture2, TexCoord);
    }
}
