#version 400

layout(std140) uniform camera {
  vec3 eye;
  vec3 center;
  mat4 view;
  mat4 projection;
};
