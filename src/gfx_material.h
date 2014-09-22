
#ifndef GFX_MATERIAL_H
#define GFX_MATERIAL_H

#ifdef __cplusplus
extern "C" {
#endif

struct GFXMaterial;

GFXMaterial * gfxCreateMaterial();
void gfxFreeMaterial(GFXMaterial * material);

#ifdef __cplusplus
}
#endif

#endif

#ifdef GFX_MATERIAL_IMPLEMENTATION

#include <GL/glew.h>
#include <memory.h>

struct GFX_Shader
{
  GLuint shader;
  const char * filename;
};

struct GFXMaterial
{
  GLuint program;
  GFX_Shader * shaders;
};

GFXMaterial * gfxCreateMaterial()
{
  GFXMaterial * material = (GFXMaterial *)malloc(sizeof(GFXMaterial));
  memset(material, 0, sizeof(GFXMaterial));

  return material;
}

void gfxFreeMaterial(GFXMaterial * material)
{
  assert(material);
  free(material);
}

#endif