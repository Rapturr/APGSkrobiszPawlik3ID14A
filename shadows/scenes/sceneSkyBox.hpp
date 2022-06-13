#ifndef SCENESKYBOX_HPP
#define SCENESKYBOX_HPP

#include "../common/shader.hpp"

//#include "../common/includeonce.h"
#include "../shapes/includeShapes.hpp"
#include "../common/texture.hpp"
#include "../common/stb_image.h"
#include "../common/objloader.hpp"

#include "../common/controls.hpp"

#include <glm.hpp>

class sceneSkyBox
{
private:
    Shader shaderSkybox;
    Shader shaderEnv;
    
    Shader shader;
    Shader simpleDepthShader;
    Shader debugDepthQuad;
    
    GLuint vaoHandle;

    const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
    unsigned int depthMapFBO;
    unsigned int depthMap;
    
    cubeTemplate cube;
    cubeTemplate cube1;
    skyBox world;

    GLuint Texture;
    GLuint susantexture;
	GLuint floorTexture;
    unsigned int diffuseMap;
    unsigned int normalMap;


    GLuint vertexbuffer;
	GLuint uvbuffer;
    std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
    std::vector<glm::vec3> floorPos;
    
    glm::vec3 lightPos = glm::vec3(-2.0f, 4.0f, -1.0f);



    void setMatrices();
    void compileAndLinkShader();
    unsigned int loadTexture(char const * path){
        unsigned int textureID;
        glGenTextures(1, &textureID);

        int width, height, nrComponents;
        unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
        if (data)
        {
            GLenum format;
            if (nrComponents == 1)
                format = GL_RED;
            else if (nrComponents == 3)
                format = GL_RGB;
            else if (nrComponents == 4)
                format = GL_RGBA;

            glBindTexture(GL_TEXTURE_2D, textureID);
            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT); // for this tutorial: use GL_CLAMP_TO_EDGE to prevent semi-transparent borders. Due to interpolation it takes texels from next repeat 
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            stbi_image_free(data);
        }
        else
        {
            std::cout << "Texture failed to load at path: " << path << std::endl;
            stbi_image_free(data);
        }

        return textureID;
    }



    unsigned int planeVAO;
    unsigned int planeVBO;
    float planeVertices[48] = {
        // positions            // normals         // texcoords
         25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,  25.0f,  0.0f,
        -25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f,
        -25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,   0.0f, 25.0f,

         25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,  25.0f,  0.0f,
        -25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,   0.0f, 25.0f,
         25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,  25.0f, 25.0f
    };
    
    void renderScene(const Shader &shader);
    void renderScene(const Shader &shader, glm::vec3);


    unsigned int cubeVAO = 0;
    unsigned int cubeVBO = 0;
    void renderCube();



public:
    sceneSkyBox();
    glm::vec3 move = glm::vec3(0.0f,0.0f,0.0f);
    void initScene();
    void render(GLFWwindow*);

};

#endif