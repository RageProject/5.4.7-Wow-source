/*
 * Copyright (C) 2008-2012 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2006-2009 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/* ScriptData
SDName: Ironforge
SD%Complete: 0
SDComment:
SDCategory: Ironforge
EndScriptData */

/* ContentData
EndContentData */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"


class item_paint : public ItemScript
{
public:
	item_paint() : ItemScript("item_paint"){}

	bool OnUse(Player* player, Item* /*item*/, SpellCastTargets const& targets){
		if (Creature* c = player->FindNearestCreature(42291, 5.0f, true)){
			if (c->GetEntry() == 42291){
				if (player->GetQuestStatus(26342) == QUEST_STATUS_INCOMPLETE){
					Quest const* qInfo = sObjectMgr->GetQuestTemplate(26342);
					player->KilledMonsterCredit(42796);
					c->DisappearAndDie();
				}
			}
		}
		return true;
	}
};

class item_techno_granade : public ItemScript
{
public:
	item_techno_granade() : ItemScript("item_techno_granade"){}

	bool OnUse(Player* player, Item* /*item*/, SpellCastTargets const& /*targets*/){
		player->CastSpell(player->getVictim(), 79751);
		return true;
	}
};

class npc_repaired_mechano_tank : public CreatureScript
{
public:
	npc_repaired_mechano_tank() : CreatureScript("npc_repaired_mechano_tank") { }

	struct npc_repaired_mechano_tankAI : ScriptedAI
	{
		npc_repaired_mechano_tankAI(Creature* creature) : ScriptedAI(creature)
		{
			SetCombatMovement(false);
		}

		void SpellHit(Unit* caster, SpellInfo const* spell) {
			//Get the player who cast the spell
			if (Player* p = caster->ToPlayer()){
				//Get the id of the spell 
				if (spell->Id == 79751){
					//if player has that quest incomplete
					if (p->GetQuestStatus(26333) == QUEST_STATUS_INCOMPLETE){
						//reward the monster
						Quest const* qInfo = sObjectMgr->GetQuestTemplate(26333);
						if (qInfo)
						{
							p->KilledMonsterCredit(42224);
							me->DisappearAndDie();
						}
					}
				}
			}
		}

	};

	CreatureAI* GetAI(Creature* creature) const
	{
		return new npc_repaired_mechano_tankAI(creature);
	}
};

class go_makeshift_cage : public GameObjectScript
{
public:
	go_makeshift_cage() : GameObjectScript("go_makeshift_cage") { }

	bool OnGossipHello(Player* player, GameObject* go)
	{
		if (player->GetQuestStatus(26284) == QUEST_STATUS_INCOMPLETE){
			Quest const* qInfo = sObjectMgr->GetQuestTemplate(26284);
			player->KilledMonsterCredit(42645);
			go->Delete();
		}
		return false;
	}
};

class go_detonator : public GameObjectScript
{
public:
	go_detonator() : GameObjectScript("go_detonator") { }

	bool OnGossipHello(Player* player, GameObject* go)
	{
		if (player->GetQuestStatus(26318) == QUEST_STATUS_INCOMPLETE){
			Quest const* qInfo = sObjectMgr->GetQuestTemplate(26284);
			player->KilledMonsterCredit(-204042);
			go->Delete();
		}
		return false;
	}
};

class item_orbit : public ItemScript
{
public:
	item_orbit() : ItemScript("item_orbit"){}

	bool OnUse(Player* player, Item* /*item*/, SpellCastTargets const& targets){
		if (Creature* c = player->FindNearestCreature(42839, 10.0f, true)){
			if (player->GetQuestStatus(26364) == QUEST_STATUS_INCOMPLETE){
				Quest const* qInfo = sObjectMgr->GetQuestTemplate(26364);
				player->KilledMonsterCredit(42860);
				c->DisappearAndDie();
			}
		}
		return true;
	}
};

void AddSC_ironforge()
{
	new item_paint();
	new item_techno_granade();
	new npc_repaired_mechano_tank();
	new go_makeshift_cage();
	new item_orbit();
	new go_detonator();
}
