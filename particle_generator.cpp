#include "particle_generator.h"

static uint32_t last_used_particle = 0;
static uint32_t first_unused_particle(ParticleGenerator* gen)
{
	for (uint32_t i = last_used_particle; i < gen->amount; i++)
	{
		if (gen->particles[i].life <= 0)
		{
			last_used_particle = i;
			return i;
		}
	}
	for (uint32_t i = 0; i < last_used_particle; i++)
	{
		if (gen->particles[i].life <= 0)
		{
			last_used_particle = i;
			return i;
		}
	}
	last_used_particle = 0;
	return 0;
}

static void respawn_particle(Particle* particle, GameObject* object, Vec2 offset = Vec2{ 0 })
{
	float random = ((rand() % 100) - 50) / 10.0f;
	float color = 0.5 + ((rand() % 100) / 100.0f);
	particle->position = object->position + random + offset;
	particle->color = Vec4(color, color, color, 1.0f);
	particle->life = 1.0f;
	particle->velocity = object->velocity * 0.1f;
}

ParticleGenerator* new_particle_generator(Shader shader, Texture2D texture, uint32_t amount)
{
	ParticleGenerator* result = new ParticleGenerator();//(ParticleGenerator*)malloc(sizeof(ParticleGenerator));
	result->shader = shader;
	result->texture = texture;
	result->amount = amount;
	
	GLuint vbo;
	float particle_quad[] = {
		0, 1, 0, 1,
		1, 0, 1, 0,
		0, 0, 0, 0,

		0, 1, 0, 1,
		1, 1, 1, 1,
		1, 0, 1, 0,
	};

	glGenVertexArrays(1, &result->vao);
	glGenBuffers(1, &vbo);
	glBindVertexArray(result->vao);
	// Fill mesh buffer
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(particle_quad), particle_quad, GL_STATIC_DRAW);
	// Set mesh attributes
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	glBindVertexArray(0);
		
	for (uint32_t i = 0; i < result->amount; i++)
	{
		result->particles.push_back(Particle{});
	}

	return result;
}

void update_particles(ParticleGenerator* gen, float dt, GameObject* object, uint32_t new_particles, Vec2 offset)
{
	for (uint32_t i = 0; i < new_particles; i++)
	{
		int unused_particle = first_unused_particle(gen);
		respawn_particle(&gen->particles[unused_particle], object, offset);
	}
	for (uint32_t i = 0; i < gen->amount; i++)
	{
		Particle* p = &gen->particles[i];
		p->life -= dt;
		if (p->life > 0)
		{
			p->position -= p->velocity * dt;
			p->color.a -= dt * 2.5;
		}
	}
}

void draw_particles(ParticleGenerator* gen)
{
	for (Particle particle : gen->particles)
	{
		draw_sprite(renderer, &gen->texture, particle.position, Vec2{ 20 });
	}

#if 0
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	shader_use(&gen->shader);
	for (Particle particle : gen->particles)
	{
		if (particle.life > 0)
		{
			shader_set_vector2f(&gen->shader, "offset", particle.position);
			shader_set_vector4f(&gen->shader, "color", particle.color);
			bind_texture(&gen->texture);
			glBindVertexArray(gen->vao);
			glDrawArrays(GL_TRIANGLES, 0, 6);
			glBindVertexArray(0);
		}
	}
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	CHECK_ERROR;
#endif
}