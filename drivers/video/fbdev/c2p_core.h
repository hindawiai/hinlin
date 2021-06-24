<शैली गुरु>
/*
 *  Fast C2P (Chunky-to-Planar) Conversion
 *
 *  Copyright (C) 2003-2008 Geert Uytterhoeven
 *
 *  NOTES:
 *    - This code was inspired by Scout's C2P tutorial
 *    - It assumes to run on a big endian प्रणाली
 *
 *  This file is subject to the terms and conditions of the GNU General Public
 *  License. See the file COPYING in the मुख्य directory of this archive
 *  क्रम more details.
 */

#समावेश <linux/build_bug.h>


    /*
     *  Basic transpose step
     */

अटल अंतरभूत व्योम _transp(u32 d[], अचिन्हित पूर्णांक i1, अचिन्हित पूर्णांक i2,
			   अचिन्हित पूर्णांक shअगरt, u32 mask)
अणु
	u32 t = (d[i1] ^ (d[i2] >> shअगरt)) & mask;

	d[i1] ^= t;
	d[i2] ^= t << shअगरt;
पूर्ण


अटल __always_अंतरभूत u32 get_mask(अचिन्हित पूर्णांक n)
अणु
	चयन (n) अणु
	हाल 1:
		वापस 0x55555555;

	हाल 2:
		वापस 0x33333333;

	हाल 4:
		वापस 0x0f0f0f0f;

	हाल 8:
		वापस 0x00ff00ff;

	हाल 16:
		वापस 0x0000ffff;
	पूर्ण

	BUILD_BUG();
	वापस 0;
पूर्ण


    /*
     *  Transpose operations on 8 32-bit words
     */

अटल __always_अंतरभूत व्योम transp8(u32 d[], अचिन्हित पूर्णांक n, अचिन्हित पूर्णांक m)
अणु
	u32 mask = get_mask(n);

	चयन (m) अणु
	हाल 1:
		/* First n x 1 block */
		_transp(d, 0, 1, n, mask);
		/* Second n x 1 block */
		_transp(d, 2, 3, n, mask);
		/* Third n x 1 block */
		_transp(d, 4, 5, n, mask);
		/* Fourth n x 1 block */
		_transp(d, 6, 7, n, mask);
		वापस;

	हाल 2:
		/* First n x 2 block */
		_transp(d, 0, 2, n, mask);
		_transp(d, 1, 3, n, mask);
		/* Second n x 2 block */
		_transp(d, 4, 6, n, mask);
		_transp(d, 5, 7, n, mask);
		वापस;

	हाल 4:
		/* Single n x 4 block */
		_transp(d, 0, 4, n, mask);
		_transp(d, 1, 5, n, mask);
		_transp(d, 2, 6, n, mask);
		_transp(d, 3, 7, n, mask);
		वापस;
	पूर्ण

	BUILD_BUG();
पूर्ण


    /*
     *  Transpose operations on 4 32-bit words
     */

अटल __always_अंतरभूत व्योम transp4(u32 d[], अचिन्हित पूर्णांक n, अचिन्हित पूर्णांक m)
अणु
	u32 mask = get_mask(n);

	चयन (m) अणु
	हाल 1:
		/* First n x 1 block */
		_transp(d, 0, 1, n, mask);
		/* Second n x 1 block */
		_transp(d, 2, 3, n, mask);
		वापस;

	हाल 2:
		/* Single n x 2 block */
		_transp(d, 0, 2, n, mask);
		_transp(d, 1, 3, n, mask);
		वापस;
	पूर्ण

	BUILD_BUG();
पूर्ण


    /*
     *  Transpose operations on 4 32-bit words (reverse order)
     */

अटल __always_अंतरभूत व्योम transp4x(u32 d[], अचिन्हित पूर्णांक n, अचिन्हित पूर्णांक m)
अणु
	u32 mask = get_mask(n);

	चयन (m) अणु
	हाल 2:
		/* Single n x 2 block */
		_transp(d, 2, 0, n, mask);
		_transp(d, 3, 1, n, mask);
		वापस;
	पूर्ण

	BUILD_BUG();
पूर्ण


    /*
     *  Compose two values, using a biपंचांगask as decision value
     *  This is equivalent to (a & mask) | (b & ~mask)
     */

अटल अंतरभूत u32 comp(u32 a, u32 b, u32 mask)
अणु
	वापस ((a ^ b) & mask) ^ b;
पूर्ण
