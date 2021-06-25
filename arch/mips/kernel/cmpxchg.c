<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2017 Imagination Technologies
 * Author: Paul Burton <paul.burton@mips.com>
 */

#समावेश <linux/bitops.h>
#समावेश <यंत्र/cmpxchg.h>

अचिन्हित दीर्घ __xchg_small(अस्थिर व्योम *ptr, अचिन्हित दीर्घ val, अचिन्हित पूर्णांक size)
अणु
	u32 old32, new32, load32, mask;
	अस्थिर u32 *ptr32;
	अचिन्हित पूर्णांक shअगरt;

	/* Check that ptr is naturally aligned */
	WARN_ON((अचिन्हित दीर्घ)ptr & (size - 1));

	/* Mask value to the correct size. */
	mask = GENMASK((size * BITS_PER_BYTE) - 1, 0);
	val &= mask;

	/*
	 * Calculate a shअगरt & mask that correspond to the value we wish to
	 * exchange within the naturally aligned 4 byte पूर्णांकegerthat includes
	 * it.
	 */
	shअगरt = (अचिन्हित दीर्घ)ptr & 0x3;
	अगर (IS_ENABLED(CONFIG_CPU_BIG_ENDIAN))
		shअगरt ^= माप(u32) - size;
	shअगरt *= BITS_PER_BYTE;
	mask <<= shअगरt;

	/*
	 * Calculate a poपूर्णांकer to the naturally aligned 4 byte पूर्णांकeger that
	 * includes our byte of पूर्णांकerest, and load its value.
	 */
	ptr32 = (अस्थिर u32 *)((अचिन्हित दीर्घ)ptr & ~0x3);
	load32 = *ptr32;

	करो अणु
		old32 = load32;
		new32 = (load32 & ~mask) | (val << shअगरt);
		load32 = cmpxchg(ptr32, old32, new32);
	पूर्ण जबतक (load32 != old32);

	वापस (load32 & mask) >> shअगरt;
पूर्ण

अचिन्हित दीर्घ __cmpxchg_small(अस्थिर व्योम *ptr, अचिन्हित दीर्घ old,
			      अचिन्हित दीर्घ new, अचिन्हित पूर्णांक size)
अणु
	u32 mask, old32, new32, load32, load;
	अस्थिर u32 *ptr32;
	अचिन्हित पूर्णांक shअगरt;

	/* Check that ptr is naturally aligned */
	WARN_ON((अचिन्हित दीर्घ)ptr & (size - 1));

	/* Mask inमाला_दो to the correct size. */
	mask = GENMASK((size * BITS_PER_BYTE) - 1, 0);
	old &= mask;
	new &= mask;

	/*
	 * Calculate a shअगरt & mask that correspond to the value we wish to
	 * compare & exchange within the naturally aligned 4 byte पूर्णांकeger
	 * that includes it.
	 */
	shअगरt = (अचिन्हित दीर्घ)ptr & 0x3;
	अगर (IS_ENABLED(CONFIG_CPU_BIG_ENDIAN))
		shअगरt ^= माप(u32) - size;
	shअगरt *= BITS_PER_BYTE;
	mask <<= shअगरt;

	/*
	 * Calculate a poपूर्णांकer to the naturally aligned 4 byte पूर्णांकeger that
	 * includes our byte of पूर्णांकerest, and load its value.
	 */
	ptr32 = (अस्थिर u32 *)((अचिन्हित दीर्घ)ptr & ~0x3);
	load32 = *ptr32;

	जबतक (true) अणु
		/*
		 * Ensure the byte we want to exchange matches the expected
		 * old value, and अगर not then bail.
		 */
		load = (load32 & mask) >> shअगरt;
		अगर (load != old)
			वापस load;

		/*
		 * Calculate the old & new values of the naturally aligned
		 * 4 byte पूर्णांकeger that include the byte we want to exchange.
		 * Attempt to exchange the old value क्रम the new value, and
		 * वापस अगर we succeed.
		 */
		old32 = (load32 & ~mask) | (old << shअगरt);
		new32 = (load32 & ~mask) | (new << shअगरt);
		load32 = cmpxchg(ptr32, old32, new32);
		अगर (load32 == old32)
			वापस old;
	पूर्ण
पूर्ण
