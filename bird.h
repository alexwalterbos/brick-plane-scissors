#pragma once 

#include "glm/glm.hpp"
#include "col.h"
#include "tex.h"

class Bird {
	public:
		Bird(const GLuint texture);
		void flap();
		void update(double deltaTime);
		void draw();
		Circle* getCollider();
		glm::vec3 getPosition();
		void reset();
	private:
		glm::vec3 position, velocity, gravity;
		float size, lastPitch;
		Circle* collider;
		const GLuint texture;
		void init();
};
