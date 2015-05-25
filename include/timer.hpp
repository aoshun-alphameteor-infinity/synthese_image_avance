#ifndef __TIMER_HPP__
#define __TIMER_HPP__

    #include <GL/glut.h>

    typedef struct __timer__
    {
        int previous_time;
        int current_time;

        bool is_init = false;

        int elapsed_time()
        {
            if(is_init)
            {
                previous_time = current_time;
                current_time = glutGet(GLUT_ELAPSED_TIME);
                return current_time - previous_time;
            } else
            {
                current_time = glutGet(GLUT_ELAPSED_TIME);
                is_init = true;
                return 0;
            }
        }
    }Timer;

#endif
