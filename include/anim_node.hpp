#ifndef __ANIM_NODE_H__
#define __ANIM_NODE_H__

	#include <node.hpp>
	#define MAX_ROTATION_BY_TURN 200
	#define MAX_SELF_TURN 50
	#define MAX_SPOON_TURN 20
	
	extern int nb_turn;
	extern int fire_phasis;
	extern bool mod_anim;

	class Anim_Node : public Node{
		private:
			void animate1();
			void animate2();
		public:
			Anim_Node();
			~Anim_Node();
			virtual void animation();		
	};

#endif
