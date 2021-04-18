#include "shader.h"

#include <glad/glad.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

static char * file_read(const char *filepath)
{
    FILE *file = fopen(filepath, "rb");
    assert(file != NULL);

    fseek(file, 0, SEEK_END);
    uint32_t fileSize = ftell(file);
    rewind(file);

	char *fileSource = (char *)calloc(fileSize + 1, sizeof *fileSource);
    assert(fileSource != NULL);
    assert(fread(fileSource, 1, fileSize, file) == fileSize);
    fclose(file);

    return fileSource;
}

Shader * shader_create(const char *filepath)
{
	char *shaderSource = file_read(filepath);
	char *foundVert = strstr(shaderSource, "#type vertex") + strlen("#type vertex\n");
	char *foundFrag = strstr(shaderSource, "#type fragment") + strlen("#type fragment\n");
    assert(foundVert != NULL && foundFrag != NULL);

	size_t vertSourceLength = strlen(foundVert) - strlen(foundFrag) - strlen("#type fragment\n");
	GLchar *vertexShaderSource = (GLchar *)calloc(vertSourceLength, sizeof *vertexShaderSource);
    assert(vertexShaderSource != NULL);
    strncpy(vertexShaderSource, foundVert, vertSourceLength);
    vertexShaderSource[vertSourceLength - 1] = '\0';

	size_t fragSourceLength = strlen(foundFrag) + 1;
    GLchar *fragmentShaderSource = (GLchar *)calloc(fragSourceLength, sizeof *fragmentShaderSource);
    assert(fragmentShaderSource != NULL);
    strncpy(fragmentShaderSource, foundFrag, fragSourceLength);
    fragmentShaderSource[fragSourceLength - 1] = '\0';

	free(shaderSource);
    
    const GLchar *vert = vertexShaderSource;
    const GLchar *frag = fragmentShaderSource;
    GLint isCompiled;
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	
    glShaderSource(vertexShader, 1, &vert, NULL);
	glShaderSource(fragmentShader, 1, &frag, NULL);
	free(vertexShaderSource);
	free(fragmentShaderSource);

	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);

	if (isCompiled == GL_FALSE)
	{
		GLint length;
		glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &length);
		GLchar *infoLog = (GLchar *)calloc(length, sizeof *infoLog);
        assert(infoLog != NULL);
		glGetShaderInfoLog(vertexShader, length, NULL, infoLog);

		glDeleteShader(vertexShader);
		fprintf(stderr, "VERTEX SHADER ERROR\n%s\n", infoLog);
        free(infoLog);
	}

	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);

	if (isCompiled == GL_FALSE)
	{
		GLint length;
		glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &length);
		GLchar *infoLog = (GLchar *)calloc(length, sizeof *infoLog);
		assert(infoLog != NULL);
		glGetShaderInfoLog(fragmentShader, length, NULL, infoLog);

		glDeleteShader(fragmentShader);
		fprintf(stderr, "FRAGMENT SHADER ERROR\n%s\n", infoLog);
        free(infoLog);
	}

    Shader *newShader = (Shader *)malloc(sizeof(Shader));
    assert(newShader != NULL);

	newShader->id = glCreateProgram();
	glAttachShader(newShader->id, vertexShader);
	glAttachShader(newShader->id, fragmentShader);
	glLinkProgram(newShader->id);
	glGetProgramiv(newShader->id, GL_LINK_STATUS, &isCompiled);

	if (isCompiled == GL_FALSE)
	{
		GLint length;
		glGetProgramiv(newShader->id, GL_INFO_LOG_LENGTH, &length);
		GLchar *infoLog = (GLchar *)calloc(length, sizeof *infoLog);
        assert(infoLog != NULL);
		glGetProgramInfoLog(newShader->id, length, NULL, infoLog);

		glDeleteProgram(newShader->id);
		fprintf(stderr, "SHADER PROGRAM ERROR\n%s\n", infoLog);
        free(infoLog);
	}

	glDetachShader(newShader->id, vertexShader);
	glDetachShader(newShader->id, fragmentShader);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

    return newShader;
}

void shader_free(Shader *shader)
{
	glDeleteProgram(shader->id);
    free(shader);
}

void shader_bind(const Shader *shader)
{
	glUseProgram(shader->id);
}

void shader_set_int(const Shader *shader, const char *name, int value)
{
	GLint location = glGetUniformLocation(shader->id, name);
	glUniform1i(location, value);
}

void shader_set_float(const Shader *shader, const char *name, float value)
{
	GLint location = glGetUniformLocation(shader->id, name);
	glUniform1f(location, value);
}

void shader_set_vec3f(const Shader *shader, const char *name, vec3 vec)
{
	GLint location = glGetUniformLocation(shader->id, name);
	glUniform3f(location, vec[0], vec[1], vec[2]);
}

void shader_set_mat4(const Shader *shader, const char *name, mat4 mat)
{
	GLint location = glGetUniformLocation(shader->id, name);
	glUniformMatrix4fv(location, 1, GL_FALSE, &mat[0][0]);
}