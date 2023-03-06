/** @file Object.hpp
 *  @brief Sets up an OpenGL camera..
 *  
 *  @author Jake Stringfellow
 * 
 *  Significant code contribution by Mike Shah
 * 
 *  @bug No known bugs.
 */
#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <glad/glad.h>

#include <vector>
#include <string>

// Forward declarations
#include "VertexBufferLayout.hpp"
#include "Texture.hpp"
#include "Transform.hpp"
#include "Geometry.hpp"
#include "Camera.hpp"
#include "Shader.hpp"

#include "glm/vec3.hpp"
#include "glm/gtc/matrix_transform.hpp"

// Purpose:
// An abstraction to create multiple objects
class Object{
public:
    // Object Constructor
    Object();
    // Object destructor
    ~Object();
    // Load a texture
    void LoadTexture(std::string fileName);
    // Create a textured quad
    void MakeTexturedQuad(std::string fileName);
    // How to draw the object
    virtual void Render();
	// Helper method for when we are ready to draw or update our object
	void Bind();

    // Set up vertices and texture files for our skybox
    void MakeSkybox();

    // Load a cubemap texture from the skybox
    unsigned int LoadCubemap(std::vector<std::string> faces);

    void RenderSkybox(Camera* camera, int width, int height);

    void SetSkyboxTexture(std::vector<std::string> faces); 

protected: // Classes that inherit from Object are intended to be overridden.

    // For now we have one buffer per object.
    VertexBufferLayout m_vertexBufferLayout;
    // For now we have one diffuse map
    Texture m_textureDiffuse;
    // Terrains are often 'multitextured' and have multiple textures.
    Texture m_detailMap; // NOTE: Note yet supported
    // Store the objects Geometry
	Geometry m_geometry;

    // For now we hav eone shader per object
    Shader m_shader;

    // Cubemap texture used for skybox
    unsigned int m_cubemapTexture;

    unsigned int m_skyboxVAO;

    std::vector<std::string> m_skyboxFaces;
};

#endif
