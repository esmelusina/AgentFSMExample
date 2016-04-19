/*-----------------------------------------------------------------------------
Author:			Richard Stern, based on code by Elizabeth Rowlands			
Description:	Finite State machine
-----------------------------------------------------------------------------*/

#ifndef GAME1_H
#define GAME1_H

#include "Application.h"

class SpriteBatch;
class Agent;
struct WayPoint;

class Game1 : public Application
{
public:
	// assets loaded in constructor
	Game1(unsigned int windowWidth, unsigned int windowHeight, bool fullscreen, const char *title);

	// assets destroyed in destructor
	virtual ~Game1();

	// update / draw called each frame automaticly
	virtual void Update(float deltaTime);
	virtual void Draw();

protected:
	SpriteBatch *m_spritebatch;
	
private:
	Agent *m_testAgent;

	Texture *m_backgroundTexture;
	Texture *m_agentOrangeTexture;
	Texture *m_agentGreenTexture;
	Texture *m_agentRedTexture;
	Texture *m_agentBlueTexture;
	Texture *m_mouseTexture;
	Texture *m_waypointTexture;
	Texture *m_sightTexture;
	Texture *m_pickupTexture;

	Font *m_font;

	int m_mouseX;
	int m_mouseY;

	float m_pickupX;
	float m_pickupY;
};

#endif