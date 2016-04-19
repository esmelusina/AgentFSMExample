/*-----------------------------------------------------------------------------
Author:			Richard Stern, based on code by Elizabeth Rowlands			
Description:	Finite State machine
-----------------------------------------------------------------------------*/

#include "Game1.h"
#include "SpriteBatch.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "Agent.h"

Game1::Game1(unsigned int windowWidth, unsigned int windowHeight, bool fullscreen, const char *title) : Application(windowWidth, windowHeight, fullscreen, title)
{
	// Creating the sprite batch
	m_spritebatch = SpriteBatch::Factory::Create(this, SpriteBatch::GL3);
	
	// Create an agent and set its position (half screen width and height
	m_testAgent = new Agent(100.0f, 439.0f, (float)windowWidth, (float)windowHeight);

	// Load in the textures that we want to use
	m_backgroundTexture = new Texture("./Images/background.png");
	m_agentOrangeTexture = new Texture("./Images/agent_search.png");
	m_agentRedTexture = new Texture("./Images/agent_angry.png");
	m_agentBlueTexture = new Texture("./Images/agent_health.png");
	m_agentGreenTexture = new Texture("./Images/agent.png");
	m_mouseTexture = new Texture("./Images/Player.png");
	m_waypointTexture = new Texture("./Images/nodeTexture.png");
	m_sightTexture = new Texture("./Images/Sight.png");
	m_pickupTexture = new Texture("./Images/Pickup.png");
	
	// Create the font for use with draw string
	m_font = new Font("./Fonts/calibri_24px.fnt");

	// Defaults for mouse X and Y
	m_mouseX = 0;
	m_mouseY = 0;

	//Position of helath pickup
	m_pickupX = windowWidth - 400.0f;
	m_pickupY = 400.0f;
	m_testAgent->SetPickupPos(m_pickupX, m_pickupY);
}

Game1::~Game1()
{
	// DELETE EVERYTHING!!!
	SpriteBatch::Factory::Destroy(m_spritebatch);

	delete m_testAgent;

	delete m_backgroundTexture;
	delete m_agentOrangeTexture;
	delete m_agentGreenTexture;
	delete m_agentRedTexture;
	delete m_agentBlueTexture;
	delete m_mouseTexture;
	delete m_waypointTexture;
	delete m_sightTexture;
	delete m_pickupTexture;

	delete m_font;
}

void Game1::Update(float deltaTime)
{
	// Get the mouse X and Y position
	Input::GetSingleton()->GetMouseXY(&m_mouseX, &m_mouseY);
	
	// update the agent which will be based on its current behavior
	m_testAgent->Update(deltaTime);
}

void Game1::Draw()
{
	// clear the back buffer
	ClearScreen();
	
	m_spritebatch->Begin();

	// Draw the background
	m_spritebatch->DrawSprite(m_backgroundTexture, 616.0f, 439.0f, (float)m_backgroundTexture->GetWidth() * 2.0f, (float)m_backgroundTexture->GetHeight() * 2.0f);

	//Draw waypoints
	for(int i = 0; i < m_testAgent->m_pathSize; ++i)
	{
		m_spritebatch->DrawSprite(m_waypointTexture, m_testAgent->m_path[i].x, m_testAgent->m_path[i].y);
	}

	m_spritebatch->DrawSprite(m_pickupTexture, m_pickupX, m_pickupY);

	//A red circle to indicate the agent's sight range
	m_spritebatch->DrawSprite(m_sightTexture, m_testAgent->m_movementInfo.m_positionX, m_testAgent->m_movementInfo.m_positionY, m_testAgent->m_nSightRange * 2.0f, m_testAgent->m_nSightRange * 2.0f);

	// Draw the test agent at its current position, it's colour is based on its current state.
	Colour eColour = m_testAgent->GetColour();
	Texture* pAgentTexture;

	switch(eColour)
	{
		case Orange:	pAgentTexture = m_agentOrangeTexture;	break;
		case Red:		pAgentTexture = m_agentRedTexture;		break;
		case Blue:		pAgentTexture = m_agentBlueTexture;		break;
		default:		pAgentTexture = m_agentGreenTexture;	break;
	}
	m_spritebatch->DrawSprite(pAgentTexture, m_testAgent->m_movementInfo.m_positionX, m_testAgent->m_movementInfo.m_positionY, 0.0f, 0.0f, m_testAgent->m_movementInfo.m_rotation);
	
	// Draw mouse texture
	m_spritebatch->DrawSprite(m_mouseTexture, (float)m_mouseX, (float)m_mouseY);

	// Draw info text
	m_spritebatch->DrawString(m_font, "The agent should chase the mouse if it's in the red circle, otherwise it should patrol.\nWhen it loses sight of the mouse it should search aimlessly for 3 seconds then returning to patrol.", 50, 30);

	// Draw a string that tells the user what state the agent is currently in
	switch (eColour)
	{
		case Green:
		{
			m_spritebatch->DrawString(m_font, "Status: Patrolling", 50, 80);
			break;
		}
		case Orange:
		{
			m_spritebatch->DrawString(m_font, "Status: Searching...", 50, 80);
			break;
		}
		case Red:
		{
			m_spritebatch->DrawString(m_font, "Status: Attacking!", 50, 80);
			break;
		}
		case Blue:
		{
			m_spritebatch->DrawString(m_font, "Status: Injured", 50, 80);
			break;
		}
	}


	//Display agent's health
	char buffer[32];
	sprintf_s(buffer, 32, "Agent Health: %d", m_testAgent->GetHealth());
	m_spritebatch->DrawString(m_font, buffer, 50, 105);

	m_spritebatch->End();
}