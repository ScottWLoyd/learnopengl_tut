#ifndef _PARTICLE_GENERATOR_H_
#define _PARTICLE_GENERATOR_H_

#include <vector>

#include <GL/glew.h>

#include "shader.h"
#include "texture.h"
#include "game_object.h"

struct Particle {
	Vec2 position;
	Vec2 velocity;
	Vec4 color;
	float life;
};

struct ParticleGenerator {
	std::vector<Particle> particles;
	uint32_t amount;
	Shader shader;
	Texture2D texture;
	GLuint vao;
};

ParticleGenerator* new_particle_generator(Shader shader, Texture2D texture, uint32_t amount);
void update_particles(ParticleGenerator* gen, float dt, GameObject* object, uint32_t new_particles, Vec2 offset = Vec2{ 0 });
void draw_particles(ParticleGenerator* gen);

#endif
