<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2019 Facebook
#समावेश <features.h>

प्रकार अचिन्हित पूर्णांक u32;

अटल __always_अंतरभूत u32 rol32(u32 word, अचिन्हित पूर्णांक shअगरt)
अणु
	वापस (word << shअगरt) | (word >> ((-shअगरt) & 31));
पूर्ण

#घोषणा __jhash_mix(a, b, c)			\
अणु						\
	a -= c;  a ^= rol32(c, 4);  c += b;	\
	b -= a;  b ^= rol32(a, 6);  a += c;	\
	c -= b;  c ^= rol32(b, 8);  b += a;	\
	a -= c;  a ^= rol32(c, 16); c += b;	\
	b -= a;  b ^= rol32(a, 19); a += c;	\
	c -= b;  c ^= rol32(b, 4);  b += a;	\
पूर्ण

#घोषणा __jhash_final(a, b, c)			\
अणु						\
	c ^= b; c -= rol32(b, 14);		\
	a ^= c; a -= rol32(c, 11);		\
	b ^= a; b -= rol32(a, 25);		\
	c ^= b; c -= rol32(b, 16);		\
	a ^= c; a -= rol32(c, 4);		\
	b ^= a; b -= rol32(a, 14);		\
	c ^= b; c -= rol32(b, 24);		\
पूर्ण

#घोषणा JHASH_INITVAL		0xdeadbeef

अटल ATTR
u32 jhash(स्थिर व्योम *key, u32 length, u32 initval)
अणु
	u32 a, b, c;
	स्थिर अचिन्हित अक्षर *k = key;

	a = b = c = JHASH_INITVAL + length + initval;

	जबतक (length > 12) अणु
		a += *(अस्थिर u32 *)(k);
		b += *(अस्थिर u32 *)(k + 4);
		c += *(अस्थिर u32 *)(k + 8);
		__jhash_mix(a, b, c);
		length -= 12;
		k += 12;
	पूर्ण
	चयन (length) अणु
	हाल 12: c += (u32)k[11]<<24;
	हाल 11: c += (u32)k[10]<<16;
	हाल 10: c += (u32)k[9]<<8;
	हाल 9:  c += k[8];
	हाल 8:  b += (u32)k[7]<<24;
	हाल 7:  b += (u32)k[6]<<16;
	हाल 6:  b += (u32)k[5]<<8;
	हाल 5:  b += k[4];
	हाल 4:  a += (u32)k[3]<<24;
	हाल 3:  a += (u32)k[2]<<16;
	हाल 2:  a += (u32)k[1]<<8;
	हाल 1:  a += k[0];
		 c ^= a;
		 __jhash_final(a, b, c);
	हाल 0: /* Nothing left to add */
		अवरोध;
	पूर्ण

	वापस c;
पूर्ण
