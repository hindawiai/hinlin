<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * This file is only included exactly once!
 *
 * The tables here are derived from the tas3004 datasheet,
 * modulo typo corrections and some smoothing...
 */

#घोषणा TAS3004_TREBLE_MIN	0
#घोषणा TAS3004_TREBLE_MAX	72
#घोषणा TAS3004_BASS_MIN	0
#घोषणा TAS3004_BASS_MAX	72
#घोषणा TAS3004_TREBLE_ZERO	36
#घोषणा TAS3004_BASS_ZERO	36

अटल स्थिर u8 tas3004_treble_table[] = अणु
	150, /* -18 dB */
	149,
	148,
	147,
	146,
	145,
	144,
	143,
	142,
	141,
	140,
	139,
	138,
	137,
	136,
	135,
	134,
	133,
	132,
	131,
	130,
	129,
	128,
	127,
	126,
	125,
	124,
	123,
	122,
	121,
	120,
	119,
	118,
	117,
	116,
	115,
	114, /* 0 dB */
	113,
	112,
	111,
	109,
	108,
	107,
	105,
	104,
	103,
	101,
	99,
	98,
	96,
	93,
	91,
	89,
	86,
	83,
	81,
	77,
	74,
	71,
	67,
	63,
	59,
	54,
	49,
	44,
	38,
	32,
	26,
	19,
	10,
	4,
	2,
	1, /* +18 dB */
पूर्ण;

अटल अंतरभूत u8 tas3004_treble(पूर्णांक idx)
अणु
	वापस tas3004_treble_table[idx];
पूर्ण

/* I only save the dअगरference here to the treble table
 * so that the binary is smaller...
 * I have also ignored completely dअगरferences of
 * +/- 1
 */
अटल स्थिर s8 tas3004_bass_dअगरf_to_treble[] = अणु
	2, /* 7 dB, offset 50 */
	2,
	2,
	2,
	2,
	1,
	2,
	2,
	2,
	3,
	4,
	4,
	5,
	6,
	7,
	8,
	9,
	10,
	11,
	14,
	13,
	8,
	1, /* 18 dB */
पूर्ण;

अटल अंतरभूत u8 tas3004_bass(पूर्णांक idx)
अणु
	u8 result = tas3004_treble_table[idx];

	अगर (idx >= 50)
		result += tas3004_bass_dअगरf_to_treble[idx-50];
	वापस result;
पूर्ण
