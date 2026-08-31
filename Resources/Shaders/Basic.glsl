#shader vertex
#version 410 core

layout (location = 0) in vec3 aPos;
out vec4 vertexColor;

void main(){
    gl_Position = vec4(aPos, 1.0f);
    vertexColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}

#shader fragment
#version 410 core

in vec4 vertexColor;
out vec4 fragColor;

void main(){
    fragColor = vertexColor;
}