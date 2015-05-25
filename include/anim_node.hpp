#ifndef __ANIM_NODE_H__
#define __ANIM_NODE_H__

	#include <node.hpp>
	
    #define TIME_AROUND_CASTLE 25000
    #define TIME_ROTATION_SELF 2500
    #define TIME_SPOON_REACT 1000
    #define RELOAD_TIME 8000

	extern int phase_time;
	extern int fire_phasis;
	extern bool shoot_mod_anim;

	class Anim_Node : public Node{
		private:
			void animate1(int elapsed_time);
			void animate2(int elapsed_time);
		public:
			Anim_Node();
			~Anim_Node();
			virtual void animation(int elapsed_time);		
	};

#endif
