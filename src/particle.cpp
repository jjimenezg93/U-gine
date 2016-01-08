#include "../include/particle.h"

Particle::Particle(): Sprite(nullptr) {}

Particle::Particle(Image * image, double velx, double vely, double angularVel, double lifetime, bool autofade): Sprite(image) {
	m_velocityx = velx;
	m_velocityy = vely;
	m_angularVelocity = angularVel;
	m_initialLifetime = lifetime;
	m_lifetime = lifetime;
	m_autofade = autofade;
	SetBlendMode(Renderer::BlendMode::ADDITIVE);
}

void Particle::Update(double elapsed) {
	SetPosition(GetX() + (m_velocityx * elapsed), GetY() + (m_velocityy * elapsed));
	SetAngle(GetAngle() + m_angularVelocity * elapsed);
	if (m_autofade) {
		double fadingRate = 255 / m_initialLifetime;
		SetColor(GetRed(), GetGreen(), GetBlue(), GetAlpha() - (fadingRate * elapsed));
	}
	m_lifetime -= elapsed;
}