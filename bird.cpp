#include "bird.h"
#include "pew.h"
#include <GLFW/glfw3.h>
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <cmath>
#include <memory>

#define PI 3.14159265

Bird::Bird(const GLuint texture):
	texture(texture)
{
	init();
}
void Bird::init()
{
	position = glm::vec3(0.f, 0.f, 0.f);
	velocity = glm::vec3(1.5f, 0.f, 0.f);
	gravity = glm::vec3(0.f, -2.5f, 0.f);

	collider = new Circle();
	collider->center = glm::vec2(position.x, position.y);
	collider->radius = 0.1f;

}

void Bird::flap()
{
	velocity.y+=2.5f;
}

unique_ptr<Bullet> Bird::fire()
{
	const GLuint tex = loadTextureFromFile("img/pew-text.png");
	return unique_ptr<Bullet>(new Bullet(tex, position, velocity * 3.f));
}

void Bird::update(double deltaTime)
{
	velocity += gravity * (float) deltaTime;
	position += velocity * (float)deltaTime;
	collider->center = glm::vec2(position.x, position.y);
}

void Bird::draw()
{
	glDepthMask(GL_FALSE);

	// Pitch (forward tilt in planespeak) calculation.
	float pitch = (float) atan2(velocity.y, velocity.x) * 180 / PI;
	pitch = (pitch + lastPitch*3)/4; // To smooth out the transition.
	lastPitch = pitch;

	glm::mat4 result = glm::mat4(1.0f);
	result = glm::translate(result, position);
	result = glm::rotate(result, pitch, glm::vec3(0.0f, 0.f, 1.f));
	result = glm::scale(result, glm::vec3(0.2f));

	glLoadMatrixf(glm::value_ptr(result));
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexEnvf(GL_TEXTURE_2D,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glDepthMask(GL_FALSE);

	glBegin(GL_QUADS);
	glTexCoord2f(0.f,1.f); glVertex3f(-1.f, 1.f, 0.f);
    	glTexCoord2f(1.f,1.f); glVertex3f( 1.f, 1.f, 0.f);
	glTexCoord2f(1.f,0.f); glVertex3f( 1.f, -1.f, 0.f);
	glTexCoord2f(0.f,0.f); glVertex3f(-1.f, -1.f, 0.f);
	glEnd();
	
	glBindTexture(GL_TEXTURE_2D, 0);
	glDepthMask(GL_TRUE);
}

void Bird::reset()
{
	init();
}

glm::vec3 Bird::getPosition()
{
	return position;
}

Circle* Bird::getCollider()
{
	return collider;
}
