<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/arch/arm/lib/xor-neon.c
 *
 * Copyright (C) 2013 Linaro Ltd <ard.biesheuvel@linaro.org>
 */

#समावेश <linux/raid/xor.h>
#समावेश <linux/module.h>

MODULE_LICENSE("GPL");

#अगर_अघोषित __ARM_NEON__
#त्रुटि You should compile this file with '-march=armv7-a -mfloat-abi=softfp -mfpu=neon'
#पूर्ण_अगर

/*
 * Pull in the reference implementations जबतक inकाष्ठाing GCC (through
 * -ftree-vectorize) to attempt to exploit implicit parallelism and emit
 * NEON inकाष्ठाions.
 */
#अगर __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6)
#आशय GCC optimize "tree-vectorize"
#अन्यथा
/*
 * While older versions of GCC करो not generate incorrect code, they fail to
 * recognize the parallel nature of these functions, and emit plain ARM code,
 * which is known to be slower than the optimized ARM code in यंत्र-arm/xor.h.
 */
#warning This code requires at least version 4.6 of GCC
#पूर्ण_अगर

#आशय GCC diagnostic ignored "-Wunused-variable"
#समावेश <यंत्र-generic/xor.h>

काष्ठा xor_block_ढाँचा स्थिर xor_block_neon_inner = अणु
	.name	= "__inner_neon__",
	.करो_2	= xor_8regs_2,
	.करो_3	= xor_8regs_3,
	.करो_4	= xor_8regs_4,
	.करो_5	= xor_8regs_5,
पूर्ण;
EXPORT_SYMBOL(xor_block_neon_inner);
