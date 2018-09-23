#ifndef _RESOURCE_MANAGER_H_
#define _RESOURCE_MANAGER_H_

#include <map>
#include <string>

#include <GL/glew.h>

#include "texture.h"
#include "shader.h"

struct ResourceManager {
	std::map<std::string, Shader> shaders;
	std::map<std::string, Texture2D> textures;
};

static Shader load_shader(const char* vertex_shader_file, const char* fragment_shader_file, const char* geometry_shader_file, const char* name);
static Shader get_shader(const char* name);

static Texture2D load_texture(const char* file, bool alpha, const char* name);
static Texture2D get_texture(const char* name);
static void clear_resources();

#endif
