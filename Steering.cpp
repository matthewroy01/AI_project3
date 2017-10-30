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

void Steering::changeWeight(int mode, float amount, bool add)
{
	if (add)
	{
		switch (mode)
		{
			case 0:
			{
				W_COHESION += amount;
				break;
			}
			case 1:
			{
				W_SEPARATION += amount;
				break;
			}
			case 2:
			{
				W_VELOCITY_MATCH += amount;
				break;
			}
			default:
			{
				std::cout << mode << " is not a valid mode number." << std::endl;
			}
		}
	}
	else
	{
		switch (mode)
		{
			case 0:
			{
				W_COHESION -= amount;
				break;
			}
			case 1:
			{
				W_SEPARATION -= amount;
				break;
			}
			case 2:
			{
				W_VELOCITY_MATCH -= amount;
				break;
			}
			default:
			{
				std::cout << mode << " is not a valid mode number." << std::endl;
			}
		}
	}
}