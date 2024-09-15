#shader vertex
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec4 aColor;

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main() {
    TexCoords = aTexCoords;
    gl_Position = proj * view * model * vec4(aPos, 1.0);
}

#shader fragment
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D textureDiffuse;

void main() {
    FragColor = texture(textureDiffuse, TexCoords);
}