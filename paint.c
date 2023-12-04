#include <gb/gb.h>
#include <stdio.h>
#include "hex.c"
//unsigned char 
UINT8 plx,ply;
struct Object{
	UBYTE spritids[16];
	UINT8 x, y;
	int spriteAmount;
};
struct Object player;

void moveSprite(struct Object* obj, UINT8 i, UINT8 x, UINT8 y);
void moveSprite(struct Object* obj, UINT8 i, UINT8 x, UINT8 y){
	move_sprite(obj->spritids[i],x,y);
}
void moveObject(struct Object* obj, UINT8 x, UINT8 y);
void moveObject(struct Object* obj, UINT8 x, UINT8 y) {
	int spritesPerSide = obj->spriteAmount;
	//float spritesPerSide 
	//spriteAmount 
	for (UINT8 i = 0; i < spritesPerSide; i++) {
		for (UINT8 j = 0; j < spritesPerSide; j++) {
			UINT8 index = j*4+i;
			move_sprite(obj->spritids[index], x + (i * 8), y + (j * 8));
		}
	}
}
void setupPlayer(UINT8 spriteAmount);
void setupPlayer(UINT8 spriteAmount){
	player.x=plx;
	player.y=ply;
	UINT8 i = 0;
	player.spriteAmount=spriteAmount;
	while(i<spriteAmount*spriteAmount){
		set_sprite_tile(i,i);
		player.spritids[i]=i;
		++i;
	}
}
void update(void);
void update(void){
	setupPlayer(4);
	unsigned char i = 0;
	while(1){
		player.x=plx;
		player.y=ply;
		if(joypad() & J_RIGHT) ++plx;
		if(joypad() & J_LEFT) --plx;
		if(joypad() & J_DOWN) ++ply;
		if(joypad() & J_UP) --ply;
		moveObject(&player,plx,ply);
		//move_sprite(0,plx,ply);
		delay(10);
		//printf("%d\n",i);
		++i;
	}
}
void main(void)
{
	//printf("La musica murio, hace minimo, 20 anios. Creci escuchando a The Beatles,  Pink Floyd, Queen, Soda, Radiohead, Spinetta en todos sus colores, The  Who, U2, Los Rolling, entre tantos otros .. me apena tanto cuando  escucho hablar a los jovenes de flow y escuchar los que escuchan");
	plx=64;
	ply=64;
	set_sprite_data(0,16,hex);
	set_sprite_tile(0,0);
	SHOW_SPRITES;
	update();
	
}
