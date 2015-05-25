#include <anim_node.hpp>


Anim_Node::Anim_Node()
{

}

Anim_Node::~Anim_Node()
{

}

void Anim_Node::animate1(int elapsed_time)
{
	int i, n;
	vector<Tree*> tmp = ((Node*)(this->get_children()[2]))->get_children();
	n = tmp.size();
	this->apply_rotation_on_y_first(-PI / TIME_AROUND_CASTLE * elapsed_time);
	for(i = 0; i < n; i++)
    {
		((Leaf*)tmp[i])->obj->apply_rotation_on_y(-PI / TIME_ROTATION_SELF * elapsed_time);
	}
}

void Anim_Node::animate2(int elapsed_time)
{
	int i, n;
	vector<Tree*> tmp = ((Node*)(this->get_children()[2]))->get_children();
	n = tmp.size();
	switch(fire_phasis)
    {
		case 0 :
			if((phase_time + elapsed_time) < TIME_ROTATION_SELF)
            {
				this->apply_rotation_on_y(-PI / (2 * TIME_ROTATION_SELF) * elapsed_time);
				for(i = 0; i < n; i++)
                {
					if(i % 2 == 0)
                    {
						((Leaf*)tmp[i])->obj->apply_rotation_on_y(-PI / (TIME_ROTATION_SELF / 2) * elapsed_time);
					}
					else
                    {
						((Leaf*)tmp[i])->obj->apply_rotation_on_y(PI / (TIME_ROTATION_SELF / 2) * elapsed_time);
					}
				}
			}
			else
            {
				this->apply_rotation_on_y(-PI / (2 * TIME_ROTATION_SELF) * (TIME_ROTATION_SELF - phase_time));
				for(i = 0; i < n; i++)
                {
					if(i % 2 == 0)
                    {
						((Leaf*)tmp[i])->obj->apply_rotation_on_y(-PI / (TIME_ROTATION_SELF / 2) * (TIME_ROTATION_SELF - phase_time));
					}
					else
                    {
						((Leaf*)tmp[i])->obj->apply_rotation_on_y(PI / (TIME_ROTATION_SELF / 2) * (TIME_ROTATION_SELF - phase_time));
					}
				}
			}
			break;
		case 1 :
			if((phase_time + elapsed_time) < (TIME_SPOON_REACT - 1))
            {
				((Node*)(this->get_children()[1]))->apply_rotation_on_y(PI /( 3 * TIME_SPOON_REACT) * elapsed_time);
			}
			else
            {
                ((Node*)(this->get_children()[1]))->apply_rotation_on_y(PI /( 3 * TIME_SPOON_REACT) * (TIME_SPOON_REACT - phase_time));
			}
			break;
		case 2 :
			if((phase_time + elapsed_time) < (RELOAD_TIME - 1))
            {
				((Node*)(this->get_children()[1]))->apply_rotation_on_y(-PI /( 3 * RELOAD_TIME) * elapsed_time);
			}
			else
            {                
				((Node*)(this->get_children()[1]))->apply_rotation_on_y(-PI /( 3 * RELOAD_TIME) * (RELOAD_TIME - phase_time));
			}
			break;
		case 3 :
			if((phase_time + elapsed_time) < TIME_ROTATION_SELF)
            {
				this->apply_rotation_on_y(PI / (2 * TIME_ROTATION_SELF) * elapsed_time);
				for(i = 0; i < n; i++)
                {
					if(i % 2 == 0)
                    {
						((Leaf*)tmp[i])->obj->apply_rotation_on_y(PI / (TIME_ROTATION_SELF / 2) * elapsed_time);
					}
					else
                    {
						((Leaf*)tmp[i])->obj->apply_rotation_on_y(-PI / (TIME_ROTATION_SELF / 2) * elapsed_time);
					}
				}
			}
			else
            {
				this->apply_rotation_on_y(PI / (2 * TIME_ROTATION_SELF) * (TIME_ROTATION_SELF - phase_time));
				for(i = 0; i < n; i++)
                {
					if(i % 2 == 0)
                    {
						((Leaf*)tmp[i])->obj->apply_rotation_on_y(PI / (TIME_ROTATION_SELF / 2) * (TIME_ROTATION_SELF - phase_time));
					}
					else
                    {
						((Leaf*)tmp[i])->obj->apply_rotation_on_y(-PI / (TIME_ROTATION_SELF / 2) * (TIME_ROTATION_SELF - phase_time));
					}
				}
			}
			break;
		default :
			break;
	}
}

void Anim_Node::animation(int elapsed_time)
{
	int i;
	if(!shoot_mod_anim)
    {
		this->animate1(elapsed_time);
	}
	else
    {
		this->animate2(elapsed_time);
	}
    vector<Tree*> sons = this->get_children();
	for(i = 0; i < sons.size(); i++)
		sons[i]->animation(elapsed_time);
}	
