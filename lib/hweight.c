<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/export.h>
#समावेश <linux/bitops.h>
#समावेश <यंत्र/types.h>

/**
 * hweightN - वापसs the hamming weight of a N-bit word
 * @x: the word to weigh
 *
 * The Hamming Weight of a number is the total number of bits set in it.
 */

अचिन्हित पूर्णांक __sw_hweight32(अचिन्हित पूर्णांक w)
अणु
#अगर_घोषित CONFIG_ARCH_HAS_FAST_MULTIPLIER
	w -= (w >> 1) & 0x55555555;
	w =  (w & 0x33333333) + ((w >> 2) & 0x33333333);
	w =  (w + (w >> 4)) & 0x0f0f0f0f;
	वापस (w * 0x01010101) >> 24;
#अन्यथा
	अचिन्हित पूर्णांक res = w - ((w >> 1) & 0x55555555);
	res = (res & 0x33333333) + ((res >> 2) & 0x33333333);
	res = (res + (res >> 4)) & 0x0F0F0F0F;
	res = res + (res >> 8);
	वापस (res + (res >> 16)) & 0x000000FF;
#पूर्ण_अगर
पूर्ण
EXPORT_SYMBOL(__sw_hweight32);

अचिन्हित पूर्णांक __sw_hweight16(अचिन्हित पूर्णांक w)
अणु
	अचिन्हित पूर्णांक res = w - ((w >> 1) & 0x5555);
	res = (res & 0x3333) + ((res >> 2) & 0x3333);
	res = (res + (res >> 4)) & 0x0F0F;
	वापस (res + (res >> 8)) & 0x00FF;
पूर्ण
EXPORT_SYMBOL(__sw_hweight16);

अचिन्हित पूर्णांक __sw_hweight8(अचिन्हित पूर्णांक w)
अणु
	अचिन्हित पूर्णांक res = w - ((w >> 1) & 0x55);
	res = (res & 0x33) + ((res >> 2) & 0x33);
	वापस (res + (res >> 4)) & 0x0F;
पूर्ण
EXPORT_SYMBOL(__sw_hweight8);

अचिन्हित दीर्घ __sw_hweight64(__u64 w)
अणु
#अगर BITS_PER_LONG == 32
	वापस __sw_hweight32((अचिन्हित पूर्णांक)(w >> 32)) +
	       __sw_hweight32((अचिन्हित पूर्णांक)w);
#या_अगर BITS_PER_LONG == 64
#अगर_घोषित CONFIG_ARCH_HAS_FAST_MULTIPLIER
	w -= (w >> 1) & 0x5555555555555555ul;
	w =  (w & 0x3333333333333333ul) + ((w >> 2) & 0x3333333333333333ul);
	w =  (w + (w >> 4)) & 0x0f0f0f0f0f0f0f0ful;
	वापस (w * 0x0101010101010101ul) >> 56;
#अन्यथा
	__u64 res = w - ((w >> 1) & 0x5555555555555555ul);
	res = (res & 0x3333333333333333ul) + ((res >> 2) & 0x3333333333333333ul);
	res = (res + (res >> 4)) & 0x0F0F0F0F0F0F0F0Ful;
	res = res + (res >> 8);
	res = res + (res >> 16);
	वापस (res + (res >> 32)) & 0x00000000000000FFul;
#पूर्ण_अगर
#पूर्ण_अगर
पूर्ण
EXPORT_SYMBOL(__sw_hweight64);
