#include <iostream>
#include <sstream>
#include <fstream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "resource_manager.h"
#include "util.h"

static ResourceManager resource_manager;

static Shader load_shader_from_file(const char* vertex_shader_file, const char* fragment_shader_file, const char* geometry_shader_file = NULL)
{
	Shader result;

	const char* vertex_code = read_entire_file(vertex_shader_file);
	const char* fragment_code = read_entire_file(fragment_shader_file);
	const char* geometry_code = read_entire_file(geometry_shader_file);

	if (!vertex_code || !fragment_code)
	{
		printf("SHADER ERROR: Failed to read shader files\n");
	}

	shader_compile(&result, vertex_code, fragment_code, geometry_code);
	return result;
}

static Texture2D load_texture_from_file(const char* file, bool alpha)
{
	Texture2D result = new_texture();
	if (alpha)
	{
		result.internal_format = GL_RGBA;
		result.image_format = GL_RGBA;
	}
	int x, y, n;
	int colors_per_channel = alpha ? 4 : 3;
	unsigned char *data = stbi_load(file, &x, &y, &n, colors_per_channel);
	generate_texture(&result, x, y, data);	
	stbi_image_free(data);

	return result;
}

static Shader load_shader(const char* vertex_shader_file, const char* fragment_shader_file, const char* geometry_shader_file, const char* name)
{
	std::string str_name = std::string(name);
	resource_manager.shaders[str_name] = load_shader_from_file(vertex_shader_file, fragment_shader_file, geometry_shader_file);
	return resource_manager.shaders[str_name];
}

static Shader get_shader(const char* name)
{
	return resource_manager.shaders[std::string(name)];
}

static Texture2D load_texture(const char* file, bool alpha, const char* name)
{
	std::string str_name = std::string(name);
	resource_manager.textures[str_name] = load_texture_from_file(file, alpha);
	return resource_manager.textures[str_name];
}

static Texture2D get_texture(const char* name)
{
	return resource_manager.textures[std::string(name)];
}

static void clear_resources()
{
	for (auto iter : resource_manager.shaders)
	{
		glDeleteProgram(iter.second.id);
	}
	for (auto iter : resource_manager.textures)
	{
		glDeleteTextures(1, &iter.second.id);
	}
}