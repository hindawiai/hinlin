<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * crc4.c - simple crc-4 calculations.
 */

#समावेश <linux/crc4.h>
#समावेश <linux/module.h>

अटल स्थिर uपूर्णांक8_t crc4_tab[] = अणु
	0x0, 0x7, 0xe, 0x9, 0xb, 0xc, 0x5, 0x2,
	0x1, 0x6, 0xf, 0x8, 0xa, 0xd, 0x4, 0x3,
पूर्ण;

/**
 * crc4 - calculate the 4-bit crc of a value.
 * @c:    starting crc4
 * @x:    value to checksum
 * @bits: number of bits in @x to checksum
 *
 * Returns the crc4 value of @x, using polynomial 0b10111.
 *
 * The @x value is treated as left-aligned, and bits above @bits are ignored
 * in the crc calculations.
 */
uपूर्णांक8_t crc4(uपूर्णांक8_t c, uपूर्णांक64_t x, पूर्णांक bits)
अणु
	पूर्णांक i;

	/* mask off anything above the top bit */
	x &= (1ull << bits) - 1;

	/* Align to 4-bits */
	bits = (bits + 3) & ~0x3;

	/* Calculate crc4 over four-bit nibbles, starting at the MSbit */
	क्रम (i = bits - 4; i >= 0; i -= 4)
		c = crc4_tab[c ^ ((x >> i) & 0xf)];

	वापस c;
पूर्ण
EXPORT_SYMBOL_GPL(crc4);

MODULE_DESCRIPTION("CRC4 calculations");
MODULE_LICENSE("GPL");
