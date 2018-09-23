#include <GL/glew.h>

#include "texture.h"

static Texture2D new_texture()
{
	Texture2D result;

	result.internal_format = GL_RGB;
	result.image_format = GL_RGB;
	result.wrap_s = GL_REPEAT;
	result.wrap_t = GL_REPEAT;
	result.filter_min = GL_LINEAR;
	result.filter_min = GL_LINEAR;
	glGenTextures(1, &result.id);

	return result;
}

static void generate_texture(Texture2D* t, GLuint width, GLuint height, unsigned char* data)
{
	t->width = width;
	t->height = height;
	glBindTexture(GL_TEXTURE_2D, t->id);
	glTexImage2D(GL_TEXTURE_2D, 0, t->internal_format, width, height, 0, t->image_format, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, t->wrap_s);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, t->wrap_t);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, t->filter_min);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, t->filter_max);
	glBindTexture(GL_TEXTURE_2D, 0);
}

static void bind_texture(Texture2D* t)
{
	glBindTexture(GL_TEXTURE_2D, t->id);
}