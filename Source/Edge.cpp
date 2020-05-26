#include "Edge.h"
#include "Application.h"
#include "Gameobject.h"
#include "Log.h"

Edge::Edge(Gameobject* go) : Behaviour(go, EDGE, NO_UPGRADE, B_EDGE)
{
	max_life = 100;
	current_life = max_life;
	damage = 0;
	dieDelay = 3.0f;
	providesVisibility = false;
	deathFX = EDGE_FX;
	//App->pathfinding.SetWalkabilityTile(int(pos.x), int(pos.y), false);

	SetColliders();
}

Edge::~Edge() {}

void Edge::FreeWalkabilityTiles()
{
	//App->pathfinding.SetWalkabilityTile(int(pos.x), int(pos.y), true);
}

void Edge::AfterDamageAction()
{
	if (App->scene->tutorial_edge == true)
	{
		Event::Push(UPDATE_STAT, App->scene, CURRENT_EDGE, 15);
		Event::Push(UPDATE_STAT, App->scene, EDGE_COLLECTED, 15);
	}
	else
	{
		Event::Push(UPDATE_STAT, App->scene, CURRENT_EDGE, 5);
		Event::Push(UPDATE_STAT, App->scene, EDGE_COLLECTED, 5);
	}
}

