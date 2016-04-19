//--------
//	Brief: A class that can be moved around by using steering behaviours
//	Author: Elizabeth Rowlands
//	Updated by: Richard Stern
//	Date : 16/4/2015
//--------

#ifndef AGENT_H
#define AGENT_H

class StateMachine;

enum Colour
{
	Orange, //Search
	Red,    //Attack
	Green,  //Patrol
	Blue    //Health
};

struct WayPoint
{
	float x;
	float y;
};

// A bunch of variables used for all behaviors
struct MovementInfo
{
	float m_positionX;
	float m_positionY;

	float m_velocityX;
	float m_velocityY;

	float m_accelerationX;
	float m_accelerationY;

	float m_maxSpeed;
	float m_maxForce;

	float m_rotation;
	float m_rotationDampening;
};

class Agent
{
public:
	Agent();
	Agent(float a_positionX, float a_positionY, float a_windowWidth, float a_windowHeight);
	virtual ~Agent();

	// Getters
	inline float GetPositionX() { return m_movementInfo.m_positionX; }
	inline float GetPositionY() { return m_movementInfo.m_positionY; }

	void Update(float deltaTime);

	// Getters and Setters for the agent's colour
	void SetColour(Colour eColour);
	Colour GetColour();
	
	//Tell the agent where the health pickup currently is.
	void SetPickupPos(float x, float y);
	WayPoint* GetPickupPos();
	
	// Getters for the agents health.
	int GetHealth();
	int GetMaxHealth();

	// Get the distance between the agent and a specified target.
	float GetDistanceFromTarget(float targetX, float targetY);
	
	MovementInfo m_movementInfo;

	//Pathfinding settings
	WayPoint* m_path;
	int m_pathSize;
	int m_nCurrentDst;

	//How far away can the agent see?
	int m_nSightRange;

private:
	// Function for constructors to call
	void Init(float positionX, float positionY);

	//Handles collisions with player and health pickups
	void CheckCollisions();

	//State machine to handle AI behavior
	StateMachine* m_pStateMachine;

	//What colour should the agent be rendered?
	Colour m_eColour;

	//Location of health pickup.
	WayPoint m_pickupPos;

	//Agent's Health.
	int m_currentHealth;
	int m_maxHealth;
	bool m_takingDamage;



    /////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////
    ///////// Agent State Behavior Functions
    /////////
    /////////

    // Called at end of update
    void updateFSM(float dt);

    // function for each state
    void Attack();
    void Patrol();
    void Search();
    void Health();

    // few steering behaviors
    void Seek(float x, float y, float weight = 1);
    void Wander(float radius, float jitter, float distance, float weight = 1);

    // bookkeeping variables for search state
    bool searching = false;
    float searchTimer = 0.0f;
    ///////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////
};

#endif