#include "cube3d.h"

int key_press(int key, void *param)
{
    t_player *p;

    if (!param)
        return (1);
    p = (t_player *)param;
    if (key == XK_Escape)
        exit(0);
    if (key == XK_w)
        p->up = true;
    if (key == XK_d)
        p->right = true;
    if (key == XK_s)
        p->down = true;
    if (key == XK_a)
        p->left = true;
    if (key == XK_Left)
        p->turn_left = true;
    if (key == XK_Right)
        p->turn_right = true;
    return (0);
}

int key_release(int key, void *param)
{
    t_player *p;

    if (!param)
        return (1);
    p = (t_player *)param;
    if (key == XK_Escape)
        exit(0);
    if (key == XK_w)
        p->up = false;
    if (key == XK_d)
        p->right = false;
    if (key == XK_s)
        p->down = false;
    if (key == XK_a)
        p->left = false;
    if (key == XK_Left)
        p->turn_left = false;
    if (key == XK_Right)
        p->turn_right = false;
    return (0);
}