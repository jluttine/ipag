#ifndef _IMAGES_H_
#define _IMAGES_H_

/*
Game graphics is defined in resource file data/bitmaps. Since Grapichs is
not available everywhere, we use #defines to identify images.
These definitions must be in exact same order as the bitmaps in data/bitmaps.
*/

//S=small, M=medium, L=large, 0...4 are planet types
#define IMAGE_PLANET_01S        0
#define IMAGE_PLANET_01M        1
#define IMAGE_PLANET_01L        2
#define IMAGE_PLANET_02S        3
#define IMAGE_PLANET_02M        4
#define IMAGE_PLANET_02L        5
#define IMAGE_PLANET_03S        6
#define IMAGE_PLANET_03M        7
#define IMAGE_PLANET_03L        8
#define IMAGE_PLANET_04S        9
#define IMAGE_PLANET_04M        10
#define IMAGE_PLANET_04L        11

#define IMAGE_BOUNCING          12
#define IMAGE_FROG              13
#define IMAGE_LASER             14
#define IMAGE_NUKE              15
#define IMAGE_MISSILE           16
#define IMAGE_GRENADE           17
#define IMAGE_PROBE             18
#define IMAGE_EXPLOSION_GB      19  
#define IMAGE_EXPLOSION_NS      20
#define IMAGE_SMOKE             21
#define IMAGE_DEBRIS            22
#define IMAGE_CROSSHAIR         23
#define IMAGE_SIDEBAR           24
#define IMAGE_BACKGROUND        25

#endif
