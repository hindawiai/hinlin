<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * include/यंत्र-xtensa/swab.h
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2001 - 2005 Tensilica Inc.
 */

#अगर_अघोषित _XTENSA_SWAB_H
#घोषणा _XTENSA_SWAB_H

#समावेश <linux/types.h>
#समावेश <linux/compiler.h>

#घोषणा __SWAB_64_THRU_32__

अटल अंतरभूत __attribute_स्थिर__ __u32 __arch_swab32(__u32 x)
अणु
    __u32 res;
    /* inकाष्ठाion sequence from Xtensa ISA release 2/2000 */
    __यंत्र__("ssai     8           \n\t"
	    "srli     %0, %1, 16  \n\t"
	    "src      %0, %0, %1  \n\t"
	    "src      %0, %0, %0  \n\t"
	    "src      %0, %1, %0  \n"
	    : "=&a" (res)
	    : "a" (x)
	    );
    वापस res;
पूर्ण
#घोषणा __arch_swab32 __arch_swab32

अटल अंतरभूत __attribute_स्थिर__ __u16 __arch_swab16(__u16 x)
अणु
    /* Given that 'short' values are चिन्हित (i.e., can be negative),
     * we cannot assume that the upper 16-bits of the रेजिस्टर are
     * zero.  We are careful to mask values after shअगरting.
     */

    /* There exists an anomaly between xt-gcc and xt-xcc.  xt-gcc
     * inserts an extui inकाष्ठाion after putting this function अंतरभूत
     * to ensure that it uses only the least-signअगरicant 16 bits of
     * the result.  xt-xcc करोesn't use an extui, but assumes the
     * __यंत्र__ macro follows convention that the upper 16 bits of an
     * 'unsigned short' result are still zero.  This macro doesn't
     * follow convention; indeed, it leaves garbage in the upport 16
     * bits of the रेजिस्टर.

     * Declaring the temporary variables 'res' and 'tmp' to be 32-bit
     * types जबतक the वापस type of the function is a 16-bit type
     * क्रमces both compilers to insert exactly one extui inकाष्ठाion
     * (or equivalent) to mask off the upper 16 bits. */

    __u32 res;
    __u32 पंचांगp;

    __यंत्र__("extui    %1, %2, 8, 8\n\t"
	    "slli     %0, %2, 8   \n\t"
	    "or       %0, %0, %1  \n"
	    : "=&a" (res), "=&a" (पंचांगp)
	    : "a" (x)
	    );

    वापस res;
पूर्ण
#घोषणा __arch_swab16 __arch_swab16

#पूर्ण_अगर /* _XTENSA_SWAB_H */
