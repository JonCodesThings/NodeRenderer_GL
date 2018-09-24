#include <System.hpp>

#include <ShaderConstantData.hpp>
#include <VertexDataLayout.hpp>

#include <Buffer_GL.hpp>
#include <Shader_GL.hpp>
#include <Texture_GL.hpp>

Buffer* createBuffer()
{
    return new Buffer_GL();
}

Shader* createShader()
{
    return new Shader_GL();
}

ShaderConstantData* createShaderConstantData()
{
    return new ShaderConstantData();
}

Texture* createTexture(struct image* image)
{
    return new Texture_GL(image);
}

VertexDataLayout* createVertexDataLayout()
{
    return new VertexDataLayout();
}
