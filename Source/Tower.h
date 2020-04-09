#ifndef __TOWER_H__
#define __TOWER_H__

#include "Behaviour.h"
#include "Canvas.h"

class Tower : public Behaviour
{
public:
	Tower(Gameobject* go);
	~Tower();

	void OnRightClick(float x, float y) override;
	void Upgrade();
	void AfterDamageAction() override;
	void DoAttack() override;
	void Update() override;
	void create_bar() override;
	void update_health_ui();
	void update_upgrades_ui();

protected:

	int t_lvl = 1;
	int t_max_lvl = 5;
	int attack_speed = 1;
	std::pair<float, float> localPos;
	std::pair<float, float> atkPos;
	Behaviour* atkObj;
	float atkDelay;
	Audio_FX attackFX;
	float ms_count;
};

#endif // __TOWER_H__