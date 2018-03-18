#include "mylib.h"
#include "monkey.h"
#include <stdio.h>
#include "titlescreen.h"
#include "gameover.h"
#include "spaceBack.h"
#include "win.h"

void DMACPYCHAR(const u16 *, charblock *, u16);
void DMACPYSHORT(const u16 *, u16 *, u16);
void waitForVblank();
void delay(int);
void checkMoveMent(OamEntry *);
void drawImage3 (int r, int c, int width, int height, const u16*image);
void spriteDims(OamEntry);
void moveEnemies(enemy *);
void enemyDims(OamEntry);
void prepareLevel1();
int checkButton(u16);



OamEntry shadow[128];
u16 spriteWidth;
u16 spriteHeight;
u16 enemyWidth = 16;
u16 enemyHeight = 16;
int numEnemies = 1;
enemy enemies[10];
u16 oldButtons = 32767;
enum state gameState = 0;
u16 endLevel;
Player player;



int main() {

	//Setup
	REG_DISPCTL = OBJ_ENABLE | MODE | MONKEY_DIMENSION_TYPE | BG2_ENABLE;
	DMACPYCHAR(monkey, &CHARBLOCKBASE[5], MONKEY_LENGTH);
	DMACPYSHORT(monkey_palette, &SPRITEPALETTE, MONKEY_PALETTE_LENGTH);
	for(int i = 0; i < 128; i++)
        shadow[i].attr0 = ATTR0_HIDE;
    OamEntry sprite;
    sprite.attr0 = (155 - spriteHeight) | MONKEY_PALETTE_TYPE | MONKEY_SPRITE_SHAPE;
    sprite.attr1 = 120 | MONKEY_SPRITE_SIZE;
    sprite.attr2 = MONKEY_PALETTE_ID | MONKEY_ID;
    spriteDims(sprite);
    player.sprite = sprite;
    shadow[0] = sprite;
    //Gameloop
	while(1) {
		if (gameState == 0) {
			REG_DISPCTL = MODE | MONKEY_DIMENSION_TYPE | BG2_ENABLE;
			drawImage3(0,0,240,160, titlescreen);
			if (checkButton(BUTTON_START)) {
				gameState = 3;
			}
		} else if (gameState == 2) {
			REG_DISPCTL = OBJ_ENABLE | MODE | MONKEY_DIMENSION_TYPE | BG2_ENABLE;
			moveEnemies(enemies);
			checkMoveMent(shadow);
			delay(1);
			if(checkButton(BUTTON_SELECT)) {
				gameState = 0;
			}
			DMA[3].src = &shadow;
			DMA[3].dst = OAMMEM;
			DMA[3].cnt = 128 | DMA_DESTINATION_INCREMENT | DMA_SOURCE_INCREMENT | DMA_ON;
		} else if (gameState == 1) {
			REG_DISPCTL = MODE | MONKEY_DIMENSION_TYPE | BG2_ENABLE;
			drawImage3(0,0,240,160, gameover);
			if(checkButton(BUTTON_SELECT)) {
				gameState = 0;
			}
		} else if (gameState == 3) {
			player.sprite.attr0 = (155 - spriteHeight) | MONKEY_PALETTE_TYPE | MONKEY_SPRITE_SHAPE;
			player.sprite.attr1 = 120 | MONKEY_SPRITE_SIZE;
			shadow[0] = player.sprite;
			prepareLevel1();
			drawImage3(0,0,240,160, spaceBack);
			REG_DISPCTL = OBJ_ENABLE | MODE | MONKEY_DIMENSION_TYPE | BG2_ENABLE;
			gameState = 2;
		} else if (gameState == 4) {
			REG_DISPCTL = MODE | MONKEY_DIMENSION_TYPE | BG2_ENABLE;
			drawImage3(0,0,240,160, win);
			if(checkButton(BUTTON_SELECT)) {
				gameState = 0;
			}
		}
		oldButtons = BUTTONS;
	}
}


void DMACPYCHAR(const u16 *src, charblock *dst, u16 length) {
	DMA[3].src = src;
	DMA[3].dst = dst;
	DMA[3].cnt = length | DMA_SOURCE_INCREMENT | DMA_DESTINATION_INCREMENT | DMA_ON;
}

void DMACPYSHORT(const u16 *src, u16 *dst, u16 length) {
	DMA[3].src = src;
	DMA[3].dst = dst;
	DMA[3].cnt = length | DMA_SOURCE_INCREMENT | DMA_DESTINATION_INCREMENT |DMA_ON;
}

void waitForVblank()
{
	while(SCANLINECOUNTER > 160);
	while(SCANLINECOUNTER < 160);
}

void delay(int seconds) { //Find a better way to do this, its bad
	for (int i = 0; i < seconds * 20; i++) {
		waitForVblank();
	}
}

void checkMoveMent(OamEntry *sprite) {
	u16 andVal = 255;
	signed short y = sprite->attr0 & andVal;
	signed short x = x = sprite->attr1 & andVal;
	if (KEY_DOWN_NOW(BUTTON_UP) && KEY_DOWN_NOW(BUTTON_LEFT)) {
		y = sprite->attr0 & andVal;
		if (y > 1) {
			y = y - 1;
		}
		x = sprite->attr1 & andVal;
		if (x > 1) {
			x = x - 1;
		}
	} else if (KEY_DOWN_NOW(BUTTON_LEFT) && KEY_DOWN_NOW(BUTTON_DOWN )) {
		y = sprite->attr0 & andVal;
		if (y < 160 - spriteHeight) {
			y = y + 1;
		}
		x = sprite->attr1 & andVal;
		if (x > 1) {
			x = x - 1;
		}
	} else if (KEY_DOWN_NOW(BUTTON_DOWN) && KEY_DOWN_NOW(BUTTON_RIGHT)) {
		y = sprite->attr0 & andVal;
		if (y < 160 - spriteHeight) {
			y = y + 1;
		}
		x = sprite->attr1 & andVal;
		if (x < 240 - spriteWidth) {
			x = x + 1;
		}
	} else if (KEY_DOWN_NOW(BUTTON_RIGHT) && KEY_DOWN_NOW(BUTTON_UP)) {
		y = sprite->attr0 & andVal;
		if (y > 1) {
			y = y - 1;
		}
		x = sprite->attr1 & andVal;
		if (x < 240 - spriteWidth) {
			x = x + 1;
		}
	}else if (KEY_DOWN_NOW(BUTTON_UP)) {
		y = sprite->attr0 & andVal;
		if (y > 1) {
			y = y - 1;
		}
	} else if (KEY_DOWN_NOW(BUTTON_DOWN)) {
		y = sprite->attr0 & andVal;
		if (y < 160 - spriteHeight) {
			y = y + 1;
		}
	} else if (KEY_DOWN_NOW(BUTTON_LEFT)) {
		x = sprite->attr1 & andVal;
		if (x > 1) {
			x = x - 1;
		}
	} else if (KEY_DOWN_NOW(BUTTON_RIGHT)) {
		x = sprite->attr1 & andVal;
		if (x < 240 - spriteWidth) {
			x = x + 1;
		}
	}
	OamEntry newSprite;
	OamEntry playerSprite = shadow[0];
	u16 plX = playerSprite.attr1 & 255;
	u16 plY = playerSprite.attr0 & 255;
	u16 enX;
	u16 enY;
	for (int i = 0; i < numEnemies; i++) {
		newSprite = shadow[i + 1];
		enX = newSprite.attr1 & 255;
		enY = newSprite.attr0 & 255;
		if ((plX > enX && plX < (enX + enemyWidth) && plY > enY && plY < (enY + enemyHeight)) || (enX > plX && enX < (plX + spriteWidth) && enY > plY && enY < (plY + spriteHeight))) {
			gameState = 1;
		}
	}
	if (plY <= 7 && plX > 105 && plX < 136) {
		gameState = 4;
	}
	sprite->attr0 = y | MONKEY_PALETTE_TYPE | MONKEY_SPRITE_SHAPE;
	sprite->attr1 = x | MONKEY_SPRITE_SIZE;

}

void drawImage3 (int r, int c, int width, int height, const u16 *image) {
	u16 *videoBuffer = (u16 *)0x6000000;
	for (int i = r; i < r + height; i++) {
		DMA[3].src = image + (i * width + c);
		DMA[3].dst = videoBuffer + (i * width + c);
		DMA[3].cnt = width | DMA_DESTINATION_INCREMENT | DMA_SOURCE_INCREMENT | DMA_ON;
	}
}

void spriteDims(OamEntry sprite) {
	u16 shape = sprite.attr0 >> 14;
	u16 size = sprite.attr1 >> 14;
	if (shape == 0) {
		if (size == 0) {
			spriteWidth = 8;
			spriteHeight = 8;
		} else if (size == 1) {
			spriteWidth = 16;
			spriteHeight = 16;
		} else if (size == 2) {
			spriteWidth = 32;
			spriteHeight = 32;
		} else if (size == 3) {
			spriteWidth = 64;
			spriteHeight = 64;
		}
	} else if (shape == 1) {
		if (size == 0) {
			spriteWidth = 16;
			spriteHeight = 8;
		} else if (size == 1) {
			spriteWidth = 32;
			spriteHeight = 8;
		} else if (size == 2) {
			spriteWidth = 32;
			spriteHeight = 16;
		} else if (size == 3) {
			spriteWidth = 64;
			spriteHeight = 32;
		}
	} else if (shape == 2) {
		if (size == 0) {
			spriteWidth = 8;
			spriteHeight = 16;
		} else if (size == 1) {
			spriteWidth = 8;
			spriteHeight = 32;
		} else if (size == 2) {
			spriteWidth = 16;
			spriteHeight = 32;
		} else if (size == 3) {
			spriteWidth = 32;
			spriteHeight = 64;
		}
	}
}

void moveEnemies(enemy *ptr) {
	signed short x;
	signed short y;
	for (int i = 0; i < numEnemies; i++) {
		x = (ptr + i)->sprite.attr1 & 255;
		y = (ptr + i)->sprite.attr0 & 255;
		if ((ptr + i)->direction == 1) {
			if (x < 240 - ((ptr +i)-> height)) {
				x = x + 1;
			} else {
				(ptr + i)->direction = 0;
				(ptr + i)->sprite.attr0 = y |  MONKEY_PALETTE_TYPE | ENEMYSHIPLEFT_SPRITE_SHAPE;
				(ptr + i)->sprite.attr2 = ENEMYSHIPLEFT_PALETTE_ID | ENEMYSHIPLEFT_ID;
				(ptr + i)->sprite.attr1 = x | ENEMYSHIPLEFT_SPRITE_SIZE;
				(shadow + i + 1)->attr0 = y |  MONKEY_PALETTE_TYPE | ENEMYSHIPLEFT_SPRITE_SHAPE;
				(shadow + i + 1)->attr2 = ENEMYSHIPRIGHT_PALETTE_ID | ENEMYSHIPLEFT_ID;
				(shadow + i + 1)->attr1 = x | ENEMYSHIPLEFT_SPRITE_SIZE;
			}
		} else if ((ptr + i)->direction == 0) {
			if (x > 1) {
				x = x - 2;
			} else {
				(ptr + i)->direction = 1;
				(ptr + i)->sprite.attr0 = y |  MONKEY_PALETTE_TYPE | ENEMYSHIPRIGHT_SPRITE_SHAPE;
				(ptr + i)->sprite.attr2 = ENEMYSHIPRIGHT_PALETTE_ID | ENEMYSHIPRIGHT_ID;
				(ptr + i)->sprite.attr1 = x | ENEMYSHIPRIGHT_SPRITE_SIZE;
				(shadow + i + 1)->attr0 = y |  MONKEY_PALETTE_TYPE | ENEMYSHIPRIGHT_SPRITE_SHAPE;
				(shadow + i + 1)->attr2 = ENEMYSHIPRIGHT_PALETTE_ID | ENEMYSHIPRIGHT_ID;
				(shadow + i + 1)->attr1 = x | ENEMYSHIPRIGHT_SPRITE_SIZE;
			}
		}
		(ptr + i)->sprite.attr1 = x | ENEMYSHIPLEFT_SPRITE_SIZE;
		(shadow + i + 1)->attr1 = x | ENEMYSHIPLEFT_SPRITE_SIZE;
	}
}

void prepareLevel1() {
	numEnemies = 5;
	OamEntry sprite1;
	OamEntry sprite2;
	OamEntry sprite3;
	OamEntry sprite4;
	OamEntry sprite5;

	sprite1.attr0 = 10 | MONKEY_PALETTE_TYPE | ENEMYSHIPRIGHT_SPRITE_SHAPE;
	sprite1.attr1 = 0 | ENEMYSHIPRIGHT_SPRITE_SIZE;
	sprite1.attr2 = ENEMYSHIPRIGHT_PALETTE_ID | ENEMYSHIPRIGHT_ID;

	sprite2.attr0 = 70 | MONKEY_PALETTE_TYPE | ENEMYSHIPRIGHT_SPRITE_SHAPE;
	sprite2.attr1 = 0 | ENEMYSHIPRIGHT_SPRITE_SIZE;
	sprite2.attr2 = ENEMYSHIPRIGHT_PALETTE_ID | ENEMYSHIPRIGHT_ID;

	sprite3.attr0 = 120 | MONKEY_PALETTE_TYPE | ENEMYSHIPRIGHT_SPRITE_SHAPE;
	sprite3.attr1 = 0 | ENEMYSHIPRIGHT_SPRITE_SIZE;
	sprite3.attr2 = ENEMYSHIPRIGHT_PALETTE_ID | ENEMYSHIPRIGHT_ID;

	sprite4.attr0 = 40 | MONKEY_PALETTE_TYPE | ENEMYSHIPLEFT_SPRITE_SHAPE;
	sprite4.attr1 = (240 - 16) | ENEMYSHIPLEFT_SPRITE_SIZE;
	sprite4.attr2 = ENEMYSHIPLEFT_PALETTE_ID | ENEMYSHIPLEFT_ID;

	sprite5.attr0 = 95 | MONKEY_PALETTE_TYPE | ENEMYSHIPLEFT_SPRITE_SHAPE;
	sprite5.attr1 = (240 - 16) | ENEMYSHIPLEFT_SPRITE_SIZE;
	sprite5.attr2 = ENEMYSHIPLEFT_PALETTE_ID | ENEMYSHIPLEFT_ID;

	enemy enemy1 = {sprite1, 1, 16, 16};
	enemy enemy2 = {sprite2, 1, 16, 16};
	enemy enemy3 = {sprite3, 1, 16, 16};
	enemy enemy4 = {sprite4, 0, 16, 16};
	enemy enemy5 = {sprite5, 0, 16, 16};

	enemies[0] = enemy1;
	enemies[1] = enemy2;
	enemies[2] = enemy3;
	enemies[3] = enemy4;
	enemies[4] = enemy5;
	shadow[1] = sprite1;
	shadow[2] = sprite2;
	shadow[3] = sprite3;
	shadow[4] = sprite4;
	shadow[5] = sprite5;
}

int checkButton(u16 key) {
	int buttonNotDownLast = ~ (~oldButtons & key);
	int buttonDownNow = (~BUTTONS & key);
	return buttonDownNow && buttonNotDownLast;
}
