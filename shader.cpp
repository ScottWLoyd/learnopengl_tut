#include <stdio.h>
#include <string.h>
#include <GL/glew.h>
#include <gtc/type_ptr.hpp>

#include "bo_math.h"
#include "shader.h"

static void shader_use(Shader* s)
{
	glUseProgram(s->id);
}

static void shader_compile(Shader* s, const GLchar* vertex_source, const GLchar* fragment_source, const GLchar* geometry_source)
{
	GLuint vertex, fragment, shader;
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vertex_source, NULL);
	glCompileShader(vertex);
	shader_check_compile_errors(s, vertex, "VERTEX");

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragment_source, NULL);
	glCompileShader(fragment);
	shader_check_compile_errors(s, fragment, "FRAGMENT");

	if (geometry_source)
	{
		shader = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(shader, 1, &geometry_source, NULL);
		glCompileShader(shader);
		shader_check_compile_errors(s, shader, "GEOMETRY");
	}

	s->id = glCreateProgram();
	glAttachShader(s->id, vertex);
	glAttachShader(s->id, fragment);
	if (geometry_source)
	{
		glAttachShader(s->id, shader);
	}
	glLinkProgram(s->id);
	shader_check_compile_errors(s, s->id, "PROGRAM");
	glDeleteShader(vertex);
	glDeleteShader(fragment);
	if (geometry_source)
	{
		glDeleteShader(shader);
	}
}

static void shader_set_float(Shader* s, const GLchar* name, GLfloat value, GLboolean use_shader)
{
	if (use_shader)
	{
		shader_use(s);
	}
	glUniform1f(glGetUniformLocation(s->id, name), value);
}

static void shader_set_integer(Shader* s, const GLchar* name, GLint value, GLboolean use_shader)
{
	if (use_shader)
	{
		shader_use(s);
	}
	GLint loc = glGetUniformLocation(s->id, name);
	glUniform1i(loc, value);
}

static void shader_set_vector2f(Shader* s, const GLchar* name, GLfloat x, GLfloat y, GLboolean use_shader)
{
	if (use_shader)
	{
		shader_use(s);
	}
	glUniform2f(glGetUniformLocation(s->id, name), x, y);
}

static void shader_set_vector2f(Shader* s, const GLchar* name, Vec2 value, GLboolean use_shader)
{
	if (use_shader)
	{
		shader_use(s);
	}
	GLint loc = glGetUniformLocation(s->id, name);
	CHECK_ERROR;
	glUniform2f(loc, value.x, value.y);
	CHECK_ERROR;
}

static void shader_set_vector3f(Shader* s, const GLchar* name, GLfloat x, GLfloat y, GLfloat z, GLboolean use_shader)
{
	if (use_shader)
	{
		shader_use(s);
	}
	glUniform3f(glGetUniformLocation(s->id, name), x, y, z);
}

static void shader_set_vector3f(Shader* s, const GLchar* name, Vec3 value, GLboolean use_shader)
{
	if (use_shader)
	{
		shader_use(s);
	}
	GLint loc = glGetUniformLocation(s->id, name);
	glUniform3f(loc, value.x, value.y, value.z);
}

static void shader_set_vector4f(Shader* s, const GLchar* name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean use_shader)
{
	if (use_shader)
	{
		shader_use(s);
	}
	glUniform4f(glGetUniformLocation(s->id, name), x, y, z, w);
}

static void shader_set_vector4f(Shader* s, const GLchar* name, Vec4 value, GLboolean use_shader)
{
	if (use_shader)
	{
		shader_use(s);
	}
	glUniform4f(glGetUniformLocation(s->id, name), value.x, value.y, value.z, value.w);
}

static void shader_set_matrix4(Shader* s, const GLchar* name, Mat4 value, GLboolean use_shader)
{
	if (use_shader)
	{
		shader_use(s);
	}
	GLint loc = glGetUniformLocation(s->id, name);
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(value));
}

static void shader_check_compile_errors(Shader* s, GLuint object, const char* type)
{
	GLint success;
	GLchar info_log[1024];
	if (strcmp(type, "PROGRAM") != 0)
	{
		glGetShaderiv(object, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(object, ARRAY_COUNT(info_log), NULL, info_log);
			printf("SHADER ERROR: Compile-time error: Type: %s\n", type);
			printf("%s\n ------------------------------------------", info_log);
		}
	}
	else
	{
		glGetProgramiv(object, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(object, ARRAY_COUNT(info_log), NULL, info_log);
			printf("SHADER ERROR: Link-time error: Type: %s\n", type);
			printf("%s\n ------------------------------------------", info_log);
		}
	}
}
