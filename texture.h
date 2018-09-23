#ifndef _TEXTURE_H_
#define _TEXTURE_H_

struct Texture2D {
	GLuint id;
	GLuint width, height;
	GLuint internal_format;
	GLuint image_format;
	GLuint wrap_s;
	GLuint wrap_t;
	GLuint filter_min;
	GLuint filter_max;
};

static Texture2D new_texture();
static void generate_texture(Texture2D* t, GLuint width, GLuint height, unsigned char* data);
static void bind_texture(Texture2D* t);

#endif
