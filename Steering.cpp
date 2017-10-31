#include "Steering.h"

Steering* Steering::operator*(float left)
{
	Steering* tmp = new Steering();
	tmp->setAngular(getAngular() * left);
	tmp->setLinear(getLinear() * left);

	return tmp;
}

Steering* Steering::operator+=(Steering* add)
{
	Steering* tmp = new Steering();
	tmp->setAngular(add->getAngular() + this->getAngular());
	tmp->setLinear(add->getLinear() + this->getLinear());

	return tmp;
}