/*
 * Exported with nin10kit v1.7
 * Invocation command was nin10kit --mode=sprites --bpp=8 --for_bitmap monkey monkey.png enemyShipLeft.png enemyShipRight.png --transparent=FFFFFF 
 * Time-stamp: Sunday 11/12/2017, 21:48:18
 * 
 * Image Information
 * -----------------
 * monkey.png 16@16
 * enemyShipLeft.png 16@16
 * enemyShipRight.png 16@16
 * Transparent color: (255, 255, 255)
 * 
 * All bug reports / feature requests are to be filed here https://github.com/TricksterGuy/nin10kit/issues
 */

#ifndef MONKEY_H
#define MONKEY_H

#define MONKEY_PALETTE_TYPE (1 << 13)
#define MONKEY_DIMENSION_TYPE (1 << 6)

extern const unsigned short monkey_palette[110];
#define MONKEY_PALETTE_SIZE 220
#define MONKEY_PALETTE_LENGTH 110

extern const unsigned short monkey[384];
#define MONKEY_SIZE 768
#define MONKEY_LENGTH 384

#define MONKEY_PALETTE_ID (0 << 12)
#define MONKEY_SPRITE_SHAPE (0 << 14)
#define MONKEY_SPRITE_SIZE (1 << 14)
#define MONKEY_ID 512

#define ENEMYSHIPLEFT_PALETTE_ID (0 << 12)
#define ENEMYSHIPLEFT_SPRITE_SHAPE (0 << 14)
#define ENEMYSHIPLEFT_SPRITE_SIZE (1 << 14)
#define ENEMYSHIPLEFT_ID 520

#define ENEMYSHIPRIGHT_PALETTE_ID (0 << 12)
#define ENEMYSHIPRIGHT_SPRITE_SHAPE (0 << 14)
#define ENEMYSHIPRIGHT_SPRITE_SIZE (1 << 14)
#define ENEMYSHIPRIGHT_ID 528

#endif

