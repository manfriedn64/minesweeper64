#include  <nusys.h>
#include "localdef.h"
#include "minesweeper.h"
#include "minesweeper_textures.h"

void initMenuTextures() {
	/*short i;
	QuickTexture quick[88];
	quick[0]  = (QuickTexture){64, 32,  0,  0, (u32)_menu_0_0SegmentRomStart, (u32)_menu_0_0SegmentRomEnd};
	quick[1]  = (QuickTexture){64, 32,  1,  0, (u32)_menu_1_0SegmentRomStart, (u32)_menu_1_0SegmentRomEnd};
	quick[2]  = (QuickTexture){64, 32,  2,  0, (u32)_menu_2_0SegmentRomStart, (u32)_menu_2_0SegmentRomEnd};
	quick[3]  = (QuickTexture){64, 32,  3,  0, (u32)_menu_3_0SegmentRomStart, (u32)_menu_3_0SegmentRomEnd};
	quick[4]  = (QuickTexture){64, 32,  4,  0, (u32)_menu_4_0SegmentRomStart, (u32)_menu_4_0SegmentRomEnd};
	quick[5]  = (QuickTexture){64, 32,  5,  0, (u32)_menu_5_0SegmentRomStart, (u32)_menu_5_0SegmentRomEnd};
	quick[6]  = (QuickTexture){64, 32,  6,  0, (u32)_menu_6_0SegmentRomStart, (u32)_menu_6_0SegmentRomEnd};
	quick[7]  = (QuickTexture){64, 32,  7,  0, (u32)_menu_7_0SegmentRomStart, (u32)_menu_7_0SegmentRomEnd};
	
	quick[8]  = (QuickTexture){64, 32,  0,  1, (u32)_menu_0_1SegmentRomStart, (u32)_menu_0_1SegmentRomEnd};
	quick[9]  = (QuickTexture){64, 32,  1,  1, (u32)_menu_1_1SegmentRomStart, (u32)_menu_1_1SegmentRomEnd};
	quick[10] = (QuickTexture){64, 32,  2,  1, (u32)_menu_2_1SegmentRomStart, (u32)_menu_2_1SegmentRomEnd};
	quick[11] = (QuickTexture){64, 32,  3,  1, (u32)_menu_3_1SegmentRomStart, (u32)_menu_3_1SegmentRomEnd};
	quick[12] = (QuickTexture){64, 32,  4,  1, (u32)_menu_4_1SegmentRomStart, (u32)_menu_4_1SegmentRomEnd};
	quick[13] = (QuickTexture){64, 32,  5,  1, (u32)_menu_5_1SegmentRomStart, (u32)_menu_5_1SegmentRomEnd};
	quick[14] = (QuickTexture){64, 32,  6,  1, (u32)_menu_6_1SegmentRomStart, (u32)_menu_6_1SegmentRomEnd};
	quick[15] = (QuickTexture){64, 32,  7,  1, (u32)_menu_7_1SegmentRomStart, (u32)_menu_7_1SegmentRomEnd};
	
	quick[16] = (QuickTexture){64, 32,  0,  2, (u32)_menu_0_2SegmentRomStart, (u32)_menu_0_2SegmentRomEnd};
	quick[17] = (QuickTexture){64, 32,  1,  2, (u32)_menu_1_2SegmentRomStart, (u32)_menu_1_2SegmentRomEnd};
	quick[18] = (QuickTexture){64, 32,  2,  2, (u32)_menu_2_2SegmentRomStart, (u32)_menu_2_2SegmentRomEnd};
	quick[19] = (QuickTexture){64, 32,  3,  2, (u32)_menu_3_2SegmentRomStart, (u32)_menu_3_2SegmentRomEnd};
	quick[20] = (QuickTexture){64, 32,  4,  2, (u32)_menu_4_2SegmentRomStart, (u32)_menu_4_2SegmentRomEnd};
	quick[21] = (QuickTexture){64, 32,  5,  2, (u32)_menu_5_2SegmentRomStart, (u32)_menu_5_2SegmentRomEnd};
	quick[22] = (QuickTexture){64, 32,  6,  2, (u32)_menu_6_2SegmentRomStart, (u32)_menu_6_2SegmentRomEnd};
	quick[23] = (QuickTexture){64, 32,  7,  2, (u32)_menu_7_2SegmentRomStart, (u32)_menu_7_2SegmentRomEnd};
	
	quick[24] = (QuickTexture){64, 32,  0,  3, (u32)_menu_0_3SegmentRomStart, (u32)_menu_0_3SegmentRomEnd};
	quick[25] = (QuickTexture){64, 32,  1,  3, (u32)_menu_1_3SegmentRomStart, (u32)_menu_1_3SegmentRomEnd};
	quick[26] = (QuickTexture){64, 32,  2,  3, (u32)_menu_2_3SegmentRomStart, (u32)_menu_2_3SegmentRomEnd};
	quick[27] = (QuickTexture){64, 32,  3,  3, (u32)_menu_3_3SegmentRomStart, (u32)_menu_3_3SegmentRomEnd};
	quick[28] = (QuickTexture){64, 32,  4,  3, (u32)_menu_4_3SegmentRomStart, (u32)_menu_4_3SegmentRomEnd};
	quick[29] = (QuickTexture){64, 32,  5,  3, (u32)_menu_5_3SegmentRomStart, (u32)_menu_5_3SegmentRomEnd};
	quick[30] = (QuickTexture){64, 32,  6,  3, (u32)_menu_6_3SegmentRomStart, (u32)_menu_6_3SegmentRomEnd};
	quick[31] = (QuickTexture){64, 32,  7,  3, (u32)_menu_7_3SegmentRomStart, (u32)_menu_7_3SegmentRomEnd};
	
	quick[32] = (QuickTexture){64, 32,  0,  4, (u32)_menu_0_4SegmentRomStart, (u32)_menu_0_4SegmentRomEnd};
	quick[33] = (QuickTexture){64, 32,  1,  4, (u32)_menu_1_4SegmentRomStart, (u32)_menu_1_4SegmentRomEnd};
	quick[34] = (QuickTexture){64, 32,  2,  4, (u32)_menu_2_4SegmentRomStart, (u32)_menu_2_4SegmentRomEnd};
	quick[35] = (QuickTexture){64, 32,  3,  4, (u32)_menu_3_4SegmentRomStart, (u32)_menu_3_4SegmentRomEnd};
	quick[36] = (QuickTexture){64, 32,  4,  4, (u32)_menu_4_4SegmentRomStart, (u32)_menu_4_4SegmentRomEnd};
	quick[37] = (QuickTexture){64, 32,  5,  4, (u32)_menu_5_4SegmentRomStart, (u32)_menu_5_4SegmentRomEnd};
	quick[38] = (QuickTexture){64, 32,  6,  4, (u32)_menu_6_4SegmentRomStart, (u32)_menu_6_4SegmentRomEnd};
	quick[39] = (QuickTexture){64, 32,  7,  4, (u32)_menu_7_4SegmentRomStart, (u32)_menu_7_4SegmentRomEnd};
	
	quick[40] = (QuickTexture){64, 32,  0,  5, (u32)_menu_0_5SegmentRomStart, (u32)_menu_0_5SegmentRomEnd};
	quick[41] = (QuickTexture){64, 32,  1,  5, (u32)_menu_1_5SegmentRomStart, (u32)_menu_1_5SegmentRomEnd};
	quick[42] = (QuickTexture){64, 32,  2,  5, (u32)_menu_2_5SegmentRomStart, (u32)_menu_2_5SegmentRomEnd};
	quick[43] = (QuickTexture){64, 32,  3,  5, (u32)_menu_3_5SegmentRomStart, (u32)_menu_3_5SegmentRomEnd};
	quick[44] = (QuickTexture){64, 32,  4,  5, (u32)_menu_4_5SegmentRomStart, (u32)_menu_4_5SegmentRomEnd};
	quick[45] = (QuickTexture){64, 32,  5,  5, (u32)_menu_5_5SegmentRomStart, (u32)_menu_5_5SegmentRomEnd};
	quick[46] = (QuickTexture){64, 32,  6,  5, (u32)_menu_6_5SegmentRomStart, (u32)_menu_6_5SegmentRomEnd};
	quick[47] = (QuickTexture){64, 32,  7,  5, (u32)_menu_7_5SegmentRomStart, (u32)_menu_7_5SegmentRomEnd};
	
	quick[48] = (QuickTexture){64, 32,  0,  6, (u32)_menu_0_6SegmentRomStart, (u32)_menu_0_6SegmentRomEnd};
	quick[49] = (QuickTexture){64, 32,  1,  6, (u32)_menu_1_6SegmentRomStart, (u32)_menu_1_6SegmentRomEnd};
	quick[50] = (QuickTexture){64, 32,  2,  6, (u32)_menu_2_6SegmentRomStart, (u32)_menu_2_6SegmentRomEnd};
	quick[51] = (QuickTexture){64, 32,  3,  6, (u32)_menu_3_6SegmentRomStart, (u32)_menu_3_6SegmentRomEnd};
	quick[52] = (QuickTexture){64, 32,  4,  6, (u32)_menu_4_6SegmentRomStart, (u32)_menu_4_6SegmentRomEnd};
	quick[53] = (QuickTexture){64, 32,  5,  6, (u32)_menu_5_6SegmentRomStart, (u32)_menu_5_6SegmentRomEnd};
	quick[54] = (QuickTexture){64, 32,  6,  6, (u32)_menu_6_6SegmentRomStart, (u32)_menu_6_6SegmentRomEnd};
	quick[55] = (QuickTexture){64, 32,  7,  6, (u32)_menu_7_6SegmentRomStart, (u32)_menu_7_6SegmentRomEnd};
	
	quick[56] = (QuickTexture){64, 32,  0,  7, (u32)_menu_0_7SegmentRomStart, (u32)_menu_0_7SegmentRomEnd};
	quick[57] = (QuickTexture){64, 32,  1,  7, (u32)_menu_1_7SegmentRomStart, (u32)_menu_1_7SegmentRomEnd};
	quick[58] = (QuickTexture){64, 32,  2,  7, (u32)_menu_2_7SegmentRomStart, (u32)_menu_2_7SegmentRomEnd};
	quick[59] = (QuickTexture){64, 32,  3,  7, (u32)_menu_3_7SegmentRomStart, (u32)_menu_3_7SegmentRomEnd};
	quick[60] = (QuickTexture){64, 32,  4,  7, (u32)_menu_4_7SegmentRomStart, (u32)_menu_4_7SegmentRomEnd};
	quick[61] = (QuickTexture){64, 32,  5,  7, (u32)_menu_5_7SegmentRomStart, (u32)_menu_5_7SegmentRomEnd};
	quick[62] = (QuickTexture){64, 32,  6,  7, (u32)_menu_6_7SegmentRomStart, (u32)_menu_6_7SegmentRomEnd};
	quick[63] = (QuickTexture){64, 32,  7,  7, (u32)_menu_7_7SegmentRomStart, (u32)_menu_7_7SegmentRomEnd};
	
	quick[64] = (QuickTexture){64, 32,  0,  8, (u32)_menu_0_8SegmentRomStart, (u32)_menu_0_8SegmentRomEnd};
	quick[65] = (QuickTexture){64, 32,  1,  8, (u32)_menu_1_8SegmentRomStart, (u32)_menu_1_8SegmentRomEnd};
	quick[66] = (QuickTexture){64, 32,  2,  8, (u32)_menu_2_8SegmentRomStart, (u32)_menu_2_8SegmentRomEnd};
	quick[67] = (QuickTexture){64, 32,  3,  8, (u32)_menu_3_8SegmentRomStart, (u32)_menu_3_8SegmentRomEnd};
	quick[68] = (QuickTexture){64, 32,  4,  8, (u32)_menu_4_8SegmentRomStart, (u32)_menu_4_8SegmentRomEnd};
	quick[69] = (QuickTexture){64, 32,  5,  8, (u32)_menu_5_8SegmentRomStart, (u32)_menu_5_8SegmentRomEnd};
	quick[70] = (QuickTexture){64, 32,  6,  8, (u32)_menu_6_8SegmentRomStart, (u32)_menu_6_8SegmentRomEnd};
	quick[71] = (QuickTexture){64, 32,  7,  8, (u32)_menu_7_8SegmentRomStart, (u32)_menu_7_8SegmentRomEnd};
	
	quick[72] = (QuickTexture){64, 32,  0,  9, (u32)_menu_0_9SegmentRomStart, (u32)_menu_0_9SegmentRomEnd};
	quick[73] = (QuickTexture){64, 32,  1,  9, (u32)_menu_1_9SegmentRomStart, (u32)_menu_1_9SegmentRomEnd};
	quick[74] = (QuickTexture){64, 32,  2,  9, (u32)_menu_2_9SegmentRomStart, (u32)_menu_2_9SegmentRomEnd};
	quick[75] = (QuickTexture){64, 32,  3,  9, (u32)_menu_3_9SegmentRomStart, (u32)_menu_3_9SegmentRomEnd};
	quick[76] = (QuickTexture){64, 32,  4,  9, (u32)_menu_4_9SegmentRomStart, (u32)_menu_4_9SegmentRomEnd};
	quick[77] = (QuickTexture){64, 32,  5,  9, (u32)_menu_5_9SegmentRomStart, (u32)_menu_5_9SegmentRomEnd};
	quick[78] = (QuickTexture){64, 32,  6,  9, (u32)_menu_6_9SegmentRomStart, (u32)_menu_6_9SegmentRomEnd};
	quick[79] = (QuickTexture){64, 32,  7,  9, (u32)_menu_7_9SegmentRomStart, (u32)_menu_7_9SegmentRomEnd};
	
	quick[80] = (QuickTexture){64, 32,  0, 10, (u32)_menu_0_10SegmentRomStart, (u32)_menu_0_10SegmentRomEnd};
	quick[81] = (QuickTexture){64, 32,  1, 10, (u32)_menu_1_10SegmentRomStart, (u32)_menu_1_10SegmentRomEnd};
	quick[82] = (QuickTexture){64, 32,  2, 10, (u32)_menu_2_10SegmentRomStart, (u32)_menu_2_10SegmentRomEnd};
	quick[83] = (QuickTexture){64, 32,  3, 10, (u32)_menu_3_10SegmentRomStart, (u32)_menu_3_10SegmentRomEnd};
	quick[84] = (QuickTexture){64, 32,  4, 10, (u32)_menu_4_10SegmentRomStart, (u32)_menu_4_10SegmentRomEnd};
	quick[85] = (QuickTexture){64, 32,  5, 10, (u32)_menu_5_10SegmentRomStart, (u32)_menu_5_10SegmentRomEnd};
	quick[86] = (QuickTexture){64, 32,  6, 10, (u32)_menu_6_10SegmentRomStart, (u32)_menu_6_10SegmentRomEnd};
	quick[87] = (QuickTexture){64, 32,  7, 10, (u32)_menu_7_10SegmentRomStart, (u32)_menu_7_10SegmentRomEnd};
	
	gamestate.menuLargeSprite.firstTexture = gamestate.textureCounter;
	gamestate.menuLargeSprite.width  = 8;
	gamestate.menuLargeSprite.height = 8;
	for (i = 0; i < gamestate.menuLargeSprite.width * gamestate.menuLargeSprite.height; i++) {
		textures[gamestate.textureCounter].width		= quick[i].width;
		textures[gamestate.textureCounter].height		= quick[i].height;
		textures[gamestate.textureCounter].romStart		= quick[i].romStart;
		textures[gamestate.textureCounter].romEnd		= quick[i].romEnd;
		textures[gamestate.textureCounter].malloc		= 1;
		gamestate.menuLargeSprite.coordinates[quick[i].x][quick[i].y] = (Coordinates){0, 0, &textures[gamestate.textureCounter], quick[i].width, quick[i].height};
		gamestate.menuLargeSprite.lastTexture = gamestate.textureCounter;
		gamestate.textureCounter++;
		
	}*/
}
