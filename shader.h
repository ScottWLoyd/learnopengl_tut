#ifndef _SHADER_H_
#define _SHADER_H_

#include <GL/glew.h>

#include "bo_math.h"

struct Shader {
	GLuint id;
};

static void shader_use(Shader* s);
static void shader_compile(Shader* s, const GLchar* vertex_source, const GLchar* fragment_source, const GLchar* geometry_source = 0);
static void shader_set_float(Shader* s, const GLchar* name, GLfloat value, GLboolean use_shader = false);
static void shader_set_integer(Shader* s, const GLchar* name, GLint value, GLboolean use_shader = false);
static void shader_set_vector2f(Shader* s, const GLchar* name, GLfloat x, GLfloat y, GLboolean use_shader = false);
static void shader_set_vector2f(Shader* s, const GLchar* name, Vec2 value, GLboolean use_shader = false);
static void shader_set_vector3f(Shader* s, const GLchar* name, GLfloat x, GLfloat y, GLfloat z, GLboolean use_shader = false);
static void shader_set_vector3f(Shader* s, const GLchar* name, Vec3 value, GLboolean use_shader = false);
static void shader_set_vector4f(Shader* s, const GLchar* name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean use_shader = false);
static void shader_set_vector4f(Shader* s, const GLchar* name, Vec4 value, GLboolean use_shader = false);
static void shader_set_matrix4(Shader* s, const GLchar* name, Mat4 value, GLboolean use_shader = false);
static void shader_check_compile_errors(Shader* s, GLuint object, const char* type);

#endif

