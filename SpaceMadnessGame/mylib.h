

typedef unsigned char   u8;
typedef unsigned short  u16;
typedef unsigned int    u32;
typedef struct { u16 tileimg[8192]; } charblock;


typedef u16 COLOR;

typedef struct {
    u16 attr0;
    u16 attr1;
    u16 attr2;
    u16 fill;
} OamEntry;

typedef struct {
	OamEntry sprite;
	int direction;
	u16 height;
	u16 width;
} enemy;

typedef struct {
	OamEntry sprite;
} Player;

enum state {Start, Over, Game, GameSetup};
#define OAMMEM  ((OamEntry*)0x7000000)
#define DIMENSIONTYPE 40

#define MODE 3
#define OBJ_ENABLE 0x1000
#define BG2_ENABLE (1<<10)

#define PRIORITY(pri) ((pri) << 10) //0 - 3
#define ATTR1_NOFLIP 0
#define ATTR1_HFLIP (1<<12)
#define ATTR1_VFLIP (1<<13)
#define ATTR0_REG (0<<8) // Default
#define ATTR0_HIDE (2<<8) // If set the sprite is hidden, by default all sprites are SHOWN
#define ATTR0_MOSAIC (1<<12)


#define REG_DISPCTL *(unsigned short *)0x04000000
#define VRAM *(unsigned short *)0x06000000
#define SPRITEPALETTE *(unsigned short *)0x5000200
#define BUTTONS *(volatile unsigned int *)0x4000130
#define CHARBLOCKBASE (((charblock *)0x6000000))


// --- REG_DISPCNT defines ---
#define DCNT_MODE0      0x0000
#define DCNT_MODE1      0x0001
#define DCNT_MODE2      0x0002
#define DCNT_MODE3      0x0003
#define DCNT_MODE4      0x0004
#define DCNT_MODE5      0x0005
// layers
#define DCNT_BG0        0x0100
#define DCNT_BG1        0x0200
#define DCNT_BG2        0x0400
#define DCNT_BG3        0x0800
#define DCNT_OBJ        0x1000



#define WIDTH   240
#define HEIGHT  160

#define vid_mem     ((u16*)MEM_VRAM)

#define CLR_BLACK   0x0000
#define CLR_RED     0x001F
#define CLR_LIME    0x03E0
#define CLR_YELLOW  0x03FF
#define CLR_BLUE    0x7C00
#define CLR_MAG     0x7C1F
#define CLR_CYAN    0x7FE0
#define CLR_WHITE   0x7FFF
#define COLOR(r, g, b) ((r) | (g)<<5 | (b)<<10)

#define KEY_DOWN_NOW(key)  (~(BUTTONS) & key)

#define SCANLINECOUNTER *(volatile unsigned short *)0x4000006

typedef struct
{
	const volatile void *src;
	volatile void *dst;
	unsigned int cnt;
} DMA_CONTROLLER;

#define DMA ((volatile DMA_CONTROLLER *) 0x040000B0)

#define DMA_CHANNEL_0 0
#define DMA_CHANNEL_1 1
#define DMA_CHANNEL_2 2
#define DMA_CHANNEL_3 3

#define DMA_DESTINATION_INCREMENT (0 << 21)
#define DMA_DESTINATION_DECREMENT (1 << 21)
#define DMA_DESTINATION_FIXED (2 << 21)


#define DMA_SOURCE_INCREMENT (0 << 23)
#define DMA_SOURCE_DECREMENT (1 << 23)
#define DMA_SOURCE_FIXED (2 << 23)

#define DMA_REPEAT (1 << 25)

#define DMA_16 (0 << 26)
#define DMA_32 (1 << 26)

#define DMA_NOW (0 << 28)
#define DMA_AT_VBLANK (1 << 28)
#define DMA_AT_HBLANK (2 << 28)
#define DMA_AT_REFRESH (3 << 28)

#define DMA_IRQ (1 << 30)
#define DMA_ON (1 << 31)

#define BUTTON_A		(1<<0)
#define BUTTON_B		(1<<1)
#define BUTTON_SELECT	(1<<2)
#define BUTTON_START	(1<<3)
#define BUTTON_RIGHT	(1<<4)
#define BUTTON_LEFT		(1<<5)
#define BUTTON_UP		(1<<6)
#define BUTTON_DOWN		(1<<7)
#define BUTTON_R		(1<<8)
#define BUTTON_L		(1<<9)

//Prototypes
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