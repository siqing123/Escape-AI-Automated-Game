#pragma once
#include<XEngine.h>

namespace AI
{
	struct Agent
	{
		// this matrix places the agent in the world (center is world 0,0)
		// so the inverse of it, will undo the placing (center is agent 0,0)
		X::Math::Matrix3 GetWorldTransform()const
		{
			X::Math::Vector2 h = heading;
			X::Math::Vector2 s = X::Math::PerpendicularRH(h);
			X::Math::Vector2 d = position;
			
			return{
				s.x,s.y,0.0f,      //same as s.x,s.y,0.0f  h.y,-h.x,0.0f,
				h.x, h.y, 0.0f,
				d.x, d.y, 1.0f 
			};
		}
			//|h.y,-h.x,0  | |cos¦È,-sin¦È, 0|   x engine rotate matrix3 means rotate ¦È degree (Counterclockwise)
			//|h.x,h.y ,0  | |sin¦È, cos¦È, 0|
			//|0   ,0  ,1  | |	0 ,	 0  , 1|		
		X::Math::Vector2 position = X::Math::Vector2::Zero();
		X::Math::Vector2 velocity = X::Math::Vector2::Zero();
		X::Math::Vector2 destination = X::Math::Vector2::Zero();
		X::Math::Vector2 heading = X::Math::Vector2::YAxis();//(0,1) Normalized represent(sin¦È,cos¦È)
		float radius = 1.0f;
		float mass = 1.0f;
		float maxSpeed = 100.0f;
	};
}