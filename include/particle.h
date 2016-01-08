#ifndef UGINE_PARTICLE_H
#define UGINE_PARTICLE_H

#include "sprite.h"
#include "types.h"

class Particle : public Sprite {
public:
	Particle();
	Particle(Image * image, double velx, double vely, double angularVel, double lifetime, bool autofade);

	virtual double GetLifeTime() const { return m_lifetime; }

	virtual void Update(double elapsed);
private:
	double m_velocityx, m_velocityy;
	double m_angularVelocity;
	double m_lifetime;
	double m_initialLifetime;
	bool m_autofade;
};

#endif //!UGINE_PARTICLE_H