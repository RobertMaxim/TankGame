#pragma once
#include "Headers.h"

class Shader
{
public:
    // constructor generates the shader on the fly
    // ------------------------------------------------------------------------
    Shader(const char* vertexPath, const char* fragmentPath);

    ~Shader();

    // activate the shader
    // ------------------------------------------------------------------------
    void Use() const;
    

   GLuint GetID() const;

    // MVP
    unsigned int loc_model_matrix;
    unsigned int loc_view_matrix;
    unsigned int loc_projection_matrix;

    // utility uniform functions
    void SetVec3(const std::string& name, const glm::vec3& value) const;

    void SetVec3(const std::string& name, float x, float y, float z) const;
    
    void SetMat4(const std::string& name, const glm::mat4& mat) const;
   
    void SetFloat(const std::string& name, float fValue) const;
 

private:
    void Init(const char* vertexPath, const char* fragmentPath);
    

    // utility function for checking shader compilation/linking errors.
    // ------------------------------------------------------------------------
    void CheckCompileErrors(unsigned int shader, std::string type);
    
private:
    GLuint ID;
};
