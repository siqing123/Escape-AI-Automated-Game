#include "LinkStates.h"
#include "PathFinding.h"
#include "enemyManager.h"
void MoveToEnemyState::Enter(Link& link)
{

}
void MoveToEnemyState::Update(Link& link, float deltaTime)
{
	if (!PathFinding::Get().getPath().empty())
	{
		auto mPath = PathFinding::Get().getPath();
		link.setAllTargetPosition(mPath);
		
		X::Math::Vector2 targetPos = link.GetTargetPosition(link.getTargetNode());
		X::Math::Vector2 finaltargetPos = link.GetTargetPosition(link.getSizeOfTargetPos() - 1);
		
		
		if (X::Math::Distance(link.GetPosition(), finaltargetPos) < 1.0f)
		{
			//reach destination
			link.ChangeState(1);
		}
		if (X::Math::Distance(link.GetPosition(), targetPos) < 1.0f)
		{
			if (link.getTargetNode() < link.getSizeOfTargetPos() - 1)
			{
				link.setTargetNode(link.getTargetNode() + 1);
			}
		}
		else
		{				
			auto direction = X::Math::Normalize(targetPos - link.GetPosition());
			link.changeLinkState(direction);
			auto velocity = direction * link.getSpeed();
			link.SetPosition(link.GetPosition() + (velocity * deltaTime));
		}		
	}
}

void MoveToEnemyState::Exit(Link& link)
{

}

void IdleState::Enter(Link& link)
{
	enemyManager::Get().resetSortBool();
	enemyManager::Get().sortAllVector();
}
void IdleState::Update(Link& link, float deltaTime)
{
	if (!enemyManager::Get().GetEnemies().empty() && Link::Get().getHP() > 50)
	{
		for (auto enemy : enemyManager::Get().GetEnemies())
		{
			if (enemy->IsAlive())
			{
				//get path to the enemy
				Link::Get().SetCurrentNode();
				PathFinding::Get().AstarDiagonal(Link::Get().getColumn(), Link::Get().getRow(), enemy->getColumn(), enemy->getRow());
				link.setTargetNode(0);
				link.ChangeState(0);
				break;
			}
		}
	}
	else if (!enemyManager::Get().GetAllHeath().empty() && Link::Get().getHP() < 50)
	{
		for (auto health : enemyManager::Get().GetAllHeath())
		{
			if (health->IsAlive())
			{
				//get path to the enemy
				Link::Get().SetCurrentNode();
				PathFinding::Get().AstarDiagonal(Link::Get().getColumn(), Link::Get().getRow(), health->getColumn(), health->getRow());
				link.setTargetNode(0);
				link.ChangeState(2);
				break;
			}
		}
	}
}
void IdleState::Exit(Link& link)
{

}

void MoveToHealthState::Enter(Link& link)
{
}

void MoveToHealthState::Update(Link& link, float deltaTime)
{
	enemyManager::Get().resetSortBool();
	if (!PathFinding::Get().getPath().empty())
	{
		auto mPath = PathFinding::Get().getPath();
		link.setAllTargetPosition(mPath);

		X::Math::Vector2 targetPos = link.GetTargetPosition(link.getTargetNode());
		X::Math::Vector2 finaltargetPos = link.GetTargetPosition(link.getSizeOfTargetPos() - 1);


		if (X::Math::Distance(link.GetPosition(), finaltargetPos) < 1.0f)
		{
			//reach destination
			link.ChangeState(1);
		}
		if (X::Math::Distance(link.GetPosition(), targetPos) < 1.0f)
		{
			if (link.getTargetNode() < link.getSizeOfTargetPos() - 1)
			{
				link.setTargetNode(link.getTargetNode() + 1);
			}
		}
		else
		{
			auto direction = X::Math::Normalize(targetPos - link.GetPosition());
			link.changeLinkState(direction);
			auto velocity = direction * link.getSpeed();
			link.SetPosition(link.GetPosition() + (velocity * deltaTime));
		}
	}
}

void MoveToHealthState::Exit(Link& link)
{
}
