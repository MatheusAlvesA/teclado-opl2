// Mapa de pinos para terminais
#define EF0 0    // Digital
#define EF1 1    // Digital
#define EF2 14   //A0
#define EF3 15   //A1
#define EF4 16   //A2
#define EF5 17   //A3
#define EF6 18   //A4
#define EF7 19   //A5

#define AB0 2
#define AB1 3
#define AB2 4
#define AB3 5
#define AB4 6
#define AB5 7
#define AB6 8
#define AB7 9

#define N_KEYS 61

enum key_t {
  KEY_0,
  KEY_1,
  KEY_2,
  KEY_3,
  KEY_4,
  KEY_5,
  KEY_6,
  KEY_7,
  KEY_8,
  KEY_9,
  KEY_10,
  KEY_11,
  KEY_12,
  KEY_13,
  KEY_14,
  KEY_15,
  KEY_16,
  KEY_17,
  KEY_18,
  KEY_19,
  KEY_20,
  KEY_21,
  KEY_22,
  KEY_23,
  KEY_24,
  KEY_25,
  KEY_26,
  KEY_27,
  KEY_28,
  KEY_29,
  KEY_30,
  KEY_31,
  KEY_32,
  KEY_33,
  KEY_34,
  KEY_35,
  KEY_36,
  // Teclas de controle
  KEY_PIANO,
  KEY_ORGAN,
  KEY_VIOLIN,
  KEY_TRUMPET,
  KEY_MANDOLIN,
  KEY_BELL,
  KEY_MUSIC_BOX,
  KEY_GUITAR,
  KEY_SLOW_ROCK,
  KEY_ROCK,
  KEY_NEW,
  KEY_DISCO,
  KEY_MARCH,
  KEY_WALTZ,
  KEY_SAMBA,
  KEY_BLUES,
  KEY_RED_3,
  KEY_RED_2,
  KEY_RED_1,
  KEY_RED_0,
  KEY_VOL_PLUS,
  KEY_VOL_MINUS,
  KEY_TEMPO_PLUS,
  KEY_TEMPO_MINUS
};

typedef struct
{
    uint8_t AB;
    uint8_t EF;
    uint8_t minVal;
} Key;

const Key key_list[] = {
	{0, 0, 20},
	{0, 1, 20},
	{0, 2, 20},
	{0, 3, 20},
	{0, 4, 20},
	{0, 5, 20},
	{0, 6, 20},
	{0, 7, 20},
	{1, 0, 20},
	{1, 1, 20},
	{1, 2, 20},
	{1, 3, 20},
	{1, 4, 20},
	{1, 5, 20},
	{1, 6, 20},
	{1, 7, 20},
	{2, 0, 20},
	{2, 1, 20},
	{2, 2, 35},
	{2, 3, 30},
	{2, 4, 20},
	{2, 5, 20},
	{2, 6, 20},
	{2, 7, 20},
	{3, 0, 20},
	{3, 1, 20},
	{3, 2, 35},
	{3, 3, 40},
	{3, 4, 20},
	{3, 5, 20},
	{3, 6, 20},
	{3, 7, 20},
	{4, 0, 20},
	{4, 1, 20},
	{4, 2, 20},
	{4, 3, 25},
	{4, 4, 20},
	// Teclas de controle
	{5, 0, 15},
	{5, 1, 20},
	{5, 2, 20},
	{5, 3, 20},
	{5, 4, 20},
	{5, 5, 20},
	{5, 6, 20},
	{5, 7, 20},
	{6, 0, 20},
	{6, 1, 20},
	{6, 2, 35},
	{6, 3, 20},
	{6, 4, 20},
	{6, 5, 20},
	{6, 6, 20},
	{6, 7, 30},
	{7, 0, 35},
	{7, 1, 30},
	{7, 2, 40},
	{7, 3, 30},
	{7, 4, 25},
	{7, 5, 25},
	{7, 6, 35},
	{7, 7, 30}  
};
