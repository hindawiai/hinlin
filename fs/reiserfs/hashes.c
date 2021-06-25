<शैली गुरु>

/*
 * Keyed 32-bit hash function using TEA in a Davis-Meyer function
 *   H0 = Key
 *   Hi = E Mi(Hi-1) + Hi-1
 *
 * (see Applied Cryptography, 2nd edition, p448).
 *
 * Jeremy Fitzhardinge <jeremy@zip.com.au> 1998
 *
 * Jeremy has agreed to the contents of reiserfs/README. -Hans
 * Yura's function is added (04/07/2000)
 */

#समावेश <linux/kernel.h>
#समावेश "reiserfs.h"
#समावेश <यंत्र/types.h>

#घोषणा DELTA 0x9E3779B9
#घोषणा FULLROUNDS 10		/* 32 is overसमाप्त, 16 is strong crypto */
#घोषणा PARTROUNDS 6		/* 6 माला_लो complete mixing */

/* a, b, c, d - data; h0, h1 - accumulated hash */
#घोषणा TEACORE(rounds)							\
	करो अणु								\
		u32 sum = 0;						\
		पूर्णांक n = rounds;						\
		u32 b0, b1;						\
									\
		b0 = h0;						\
		b1 = h1;						\
									\
		करो							\
		अणु							\
			sum += DELTA;					\
			b0 += ((b1 << 4)+a) ^ (b1+sum) ^ ((b1 >> 5)+b);	\
			b1 += ((b0 << 4)+c) ^ (b0+sum) ^ ((b0 >> 5)+d);	\
		पूर्ण जबतक(--n);						\
									\
		h0 += b0;						\
		h1 += b1;						\
	पूर्ण जबतक(0)

u32 keyed_hash(स्थिर चिन्हित अक्षर *msg, पूर्णांक len)
अणु
	u32 k[] = अणु 0x9464a485, 0x542e1a94, 0x3e846bff, 0xb75bcfc3 पूर्ण;

	u32 h0 = k[0], h1 = k[1];
	u32 a, b, c, d;
	u32 pad;
	पूर्णांक i;

	/*      निश्चित(len >= 0 && len < 256); */

	pad = (u32) len | ((u32) len << 8);
	pad |= pad << 16;

	जबतक (len >= 16) अणु
		a = (u32) msg[0] |
		    (u32) msg[1] << 8 | (u32) msg[2] << 16 | (u32) msg[3] << 24;
		b = (u32) msg[4] |
		    (u32) msg[5] << 8 | (u32) msg[6] << 16 | (u32) msg[7] << 24;
		c = (u32) msg[8] |
		    (u32) msg[9] << 8 |
		    (u32) msg[10] << 16 | (u32) msg[11] << 24;
		d = (u32) msg[12] |
		    (u32) msg[13] << 8 |
		    (u32) msg[14] << 16 | (u32) msg[15] << 24;

		TEACORE(PARTROUNDS);

		len -= 16;
		msg += 16;
	पूर्ण

	अगर (len >= 12) अणु
		a = (u32) msg[0] |
		    (u32) msg[1] << 8 | (u32) msg[2] << 16 | (u32) msg[3] << 24;
		b = (u32) msg[4] |
		    (u32) msg[5] << 8 | (u32) msg[6] << 16 | (u32) msg[7] << 24;
		c = (u32) msg[8] |
		    (u32) msg[9] << 8 |
		    (u32) msg[10] << 16 | (u32) msg[11] << 24;

		d = pad;
		क्रम (i = 12; i < len; i++) अणु
			d <<= 8;
			d |= msg[i];
		पूर्ण
	पूर्ण अन्यथा अगर (len >= 8) अणु
		a = (u32) msg[0] |
		    (u32) msg[1] << 8 | (u32) msg[2] << 16 | (u32) msg[3] << 24;
		b = (u32) msg[4] |
		    (u32) msg[5] << 8 | (u32) msg[6] << 16 | (u32) msg[7] << 24;

		c = d = pad;
		क्रम (i = 8; i < len; i++) अणु
			c <<= 8;
			c |= msg[i];
		पूर्ण
	पूर्ण अन्यथा अगर (len >= 4) अणु
		a = (u32) msg[0] |
		    (u32) msg[1] << 8 | (u32) msg[2] << 16 | (u32) msg[3] << 24;

		b = c = d = pad;
		क्रम (i = 4; i < len; i++) अणु
			b <<= 8;
			b |= msg[i];
		पूर्ण
	पूर्ण अन्यथा अणु
		a = b = c = d = pad;
		क्रम (i = 0; i < len; i++) अणु
			a <<= 8;
			a |= msg[i];
		पूर्ण
	पूर्ण

	TEACORE(FULLROUNDS);

/*	वापस 0;*/
	वापस h0 ^ h1;
पूर्ण

/*
 * What follows in this file is copyright 2000 by Hans Reiser, and the
 * licensing of what follows is governed by reiserfs/README
 */
u32 yura_hash(स्थिर चिन्हित अक्षर *msg, पूर्णांक len)
अणु
	पूर्णांक j, घात;
	u32 a, c;
	पूर्णांक i;

	क्रम (घात = 1, i = 1; i < len; i++)
		घात = घात * 10;

	अगर (len == 1)
		a = msg[0] - 48;
	अन्यथा
		a = (msg[0] - 48) * घात;

	क्रम (i = 1; i < len; i++) अणु
		c = msg[i] - 48;
		क्रम (घात = 1, j = i; j < len - 1; j++)
			घात = घात * 10;
		a = a + c * घात;
	पूर्ण

	क्रम (; i < 40; i++) अणु
		c = '0' - 48;
		क्रम (घात = 1, j = i; j < len - 1; j++)
			घात = घात * 10;
		a = a + c * घात;
	पूर्ण

	क्रम (; i < 256; i++) अणु
		c = i;
		क्रम (घात = 1, j = i; j < len - 1; j++)
			घात = घात * 10;
		a = a + c * घात;
	पूर्ण

	a = a << 7;
	वापस a;
पूर्ण

u32 r5_hash(स्थिर चिन्हित अक्षर *msg, पूर्णांक len)
अणु
	u32 a = 0;
	जबतक (*msg) अणु
		a += *msg << 4;
		a += *msg >> 4;
		a *= 11;
		msg++;
	पूर्ण
	वापस a;
पूर्ण
