#include <anim_node.hpp>

Anim_Node::Anim_Node()
{

}

Anim_Node::~Anim_Node()
{

}

void Anim_Node::animate1()
{
	int i, n;
	vector<Tree*> tmp = ((Node*)(this->get_children()[2]))->get_children();
	n = tmp.size();
	this->apply_rotation_on_y_first(PI / MAX_ROTATION_BY_TURN);
	for(i = 0; i < n; i++)
    {
		((Leaf*)tmp[i])->obj->apply_rotation_on_y(PI / MAX_SELF_TURN);
	}
}

void Anim_Node::animate2()
{
	int i, n;
	vector<Tree*> tmp = ((Node*)(this->get_children()[2]))->get_children();
	n = tmp.size();
	switch(fire_phasis)
    {
		case 0 :
			if(nb_turn < MAX_SELF_TURN)
            {
				this->apply_rotation_on_y(PI / (2 * MAX_SELF_TURN));
				for(i = 0; i < n; i++)
                {
					if(i % 2 == 0)
                    {
						((Leaf*)tmp[i])->obj->apply_rotation_on_y(PI / (MAX_SELF_TURN / 2));
					}
					else
                    {
						((Leaf*)tmp[i])->obj->apply_rotation_on_y(-PI / (MAX_SELF_TURN / 2));
					}
				}
			}
			else if(nb_turn == MAX_SELF_TURN)
            {
				fire_phasis++;
				nb_turn = 0;
			}
			break;
		case 1 :
			if(nb_turn < (MAX_SPOON_TURN - 1))
            {
				((Node*)(this->get_children()[1]))->apply_rotation_on_y(PI /( 3 * MAX_SPOON_TURN));
			}
			else if(nb_turn == (MAX_SPOON_TURN - 1))
            {
				fire_phasis++;
				nb_turn = 0;
			}
			break;
		case 2 :
			if(nb_turn < (MAX_SPOON_TURN - 1) * 10)
            {
				((Node*)(this->get_children()[1]))->apply_rotation_on_y(-PI /( 3 * 10 * MAX_SPOON_TURN));
			}
			else if(nb_turn == (MAX_SPOON_TURN -1) * 10)
            {
				fire_phasis++;
				nb_turn = 0;
			}
			break;
		case 3 :
			if(nb_turn < MAX_SELF_TURN)
            {
				this->apply_rotation_on_y(-PI / (2 * MAX_SELF_TURN));
				for(i = 0; i < n; i++)
                {
					if(i%2 == 0)
                    {
						((Leaf*)tmp[i])->obj->apply_rotation_on_y(-PI / (MAX_SELF_TURN / 2));
					}
					else
                    {
						((Leaf*)tmp[i])->obj->apply_rotation_on_y(PI / (MAX_SELF_TURN / 2));
					}
				}
			}
			else if(nb_turn == MAX_SELF_TURN)
            {
				fire_phasis = 0;
				nb_turn = 0;
				mod_anim = true;
			}
			break;
		default :
			break;
	}
}

void Anim_Node::animation()
{
	int i;
	if(mod_anim == true)
    {
		this->animate1();
	}
	else
    {
		this->animate2();
	}
    vector<Tree*> sons = this->get_children();
	for(i = 0; i < sons.size(); i++)
		sons[i]->animation();
}	
