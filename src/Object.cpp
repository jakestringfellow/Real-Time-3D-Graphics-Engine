#include "Object.hpp"
#include "Camera.hpp"
#include "Error.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Object::Object(){
}

Object::~Object(){
}

void Object::LoadTexture(std::string fileName){
        // Load our actual textures
        m_textureDiffuse.LoadTexture(fileName);
}

// Initialization of object as a 'quad'
void Object::MakeTexturedQuad(std::string fileName){

        // Setup geometry
        // We are using a new abstraction which allows us
        // to create triangles shapes on the fly
        // Position and Texture coordinate 
        m_geometry.AddVertex(-1.0f,-1.0f, 0.0f, 0.0f, 0.0f);
        m_geometry.AddVertex( 1.0f,-1.0f, 0.0f, 1.0f, 0.0f);
    	m_geometry.AddVertex( 1.0f, 1.0f, 0.0f, 1.0f, 1.0f);
        m_geometry.AddVertex(-1.0f, 1.0f, 0.0f, 0.0f, 1.0f);
            
        // Make our triangles and populate our
        // indices data structure	
        m_geometry.MakeTriangle(0,1,2);
        m_geometry.MakeTriangle(2,3,0);

        // This is a helper function to generate all of the geometry
        m_geometry.Gen();

        // Create a buffer and set the stride of information
        m_vertexBufferLayout.CreateNormalBufferLayout(m_geometry.GetBufferDataSize(),
                                        m_geometry.GetIndicesSize(),
                                        m_geometry.GetBufferDataPtr(),
                                        m_geometry.GetIndicesDataPtr());

        // Load our actual texture
        // We are using the input parameter as our texture to load
        m_textureDiffuse.LoadTexture(fileName.c_str());
}

// Bind everything we need in our object
void Object::Bind(){
        // Make sure we are updating the correct 'buffers'
        m_vertexBufferLayout.Bind();
        // Diffuse map is 0 by default, but it is good to set it explicitly
        m_textureDiffuse.Bind(0);
        // Detail map
//        m_detailMap.Bind(1); // NOTE: Not yet supported
}

// Render our geometry
void Object::Render(){
    // Call our helper function to just bind everything
    Bind();
	//Render data
    glDrawElements(GL_TRIANGLES,
                   m_geometry.GetIndicesSize(), // The number of indices, not triangles.
                   GL_UNSIGNED_INT,             // Make sure the data type matches
                        nullptr);               // Offset pointer to the data. 
                                                // nullptr because we are currently bound
}

//Create skybox within the object class
void Object::MakeSkybox() {


	// Vertices for the box
	float m_vertices[] = {
          // positions          
            -1.0f,  1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,
             1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,

            -1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,

             1.0f, -1.0f, -1.0f,
             1.0f, -1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f,  1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,

            -1.0f, -1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,

            -1.0f,  1.0f, -1.0f,
             1.0f,  1.0f, -1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f, -1.0f,

            -1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f,  1.0f,
	     1.0f, -1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,
 	    -1.0f, -1.0f,  1.0f,
             1.0f, -1.0f,  1.0f
        };





	//Skybox VAO
        unsigned int skyboxVBO;
        glGenVertexArrays(1, &m_skyboxVAO);
        glGenBuffers(1, &skyboxVBO);
        glBindVertexArray(m_skyboxVAO);
        glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), &m_vertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE, 3*sizeof(float), (void*)0);

	m_cubemapTexture = LoadCubemap(m_skyboxFaces);



	//Set up shaders
	std::string vertexShader = m_shader.LoadShader("./shaders/skyboxVert.glsl");
	std::string fragmentShader = m_shader.LoadShader("./shaders/skyboxFrag.glsl");
	// Actually create our shader
	m_shader.CreateShader(vertexShader, fragmentShader);	
}

//Load our skybox texture
unsigned int Object::LoadCubemap(std::vector<std::string> faces) {
	

	// Creating a cubemap
        // Bind it to the proper texture target before we do any further texture operations
        unsigned int textureID;
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

        int width, height, nrChannels;
        for(unsigned int i = 0; i < 6; i++) {
                unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
                if (data) {
                        glTexImage2D(
                                GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                                0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
                        );
                        stbi_image_free(data);
                }
                else {
                        std::cout << "Cubemap tex failed to load at path: " << faces[i] << std::endl;
                        stbi_image_free(data);
                }
        }

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

        return textureID;
}

// Render our skybox
void Object::RenderSkybox(Camera* camera, int width, int height) {


        glDepthFunc(GL_LEQUAL); // change depth function so depth test passes when values are equal to depth buffer's content

	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);	
	glFrontFace(GL_CW);
	
	m_shader.Bind();
	
	//glm::mat4 model = glm::mat4(1.0f);
	//m_shader.SetUniformMatrix4fv("model", &model[0][0]);
	glm::mat4 projectionMatrix = glm::perspective(45.0f,(float)width/(float)height,0.1f,300.0f);	
	m_shader.SetUniformMatrix4fv("projection", &projectionMatrix[0][0]);
	glm::mat4 viewMatrix = glm::mat4(0.0f);
	viewMatrix = glm::mat4(glm::mat3(camera->GetWorldToViewmatrix())); 
        m_shader.SetUniformMatrix4fv("view", &viewMatrix[0][0]);

	
	glBindVertexArray(m_skyboxVAO);
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_cubemapTexture);

	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glDepthFunc(GL_LESS);


}

void Object::SetSkyboxTexture(std::vector<std::string> faces) {
    m_skyboxFaces = faces;
}
