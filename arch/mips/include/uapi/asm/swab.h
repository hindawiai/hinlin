<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1996, 99, 2003 by Ralf Baechle
 */
#अगर_अघोषित _ASM_SWAB_H
#घोषणा _ASM_SWAB_H

#समावेश <linux/compiler.h>
#समावेश <linux/types.h>

#घोषणा __SWAB_64_THRU_32__

#अगर !defined(__mips16) &&					\
	((defined(__mips_isa_rev) && (__mips_isa_rev >= 2)) ||	\
	 defined(_MIPS_ARCH_LOONGSON3A))

अटल अंतरभूत __attribute_स्थिर__ __u16 __arch_swab16(__u16 x)
अणु
	__यंत्र__(
	"	.set	push			\n"
	"	.set	arch=mips32r2		\n"
	"	wsbh	%0, %1			\n"
	"	.set	pop			\n"
	: "=r" (x)
	: "r" (x));

	वापस x;
पूर्ण
#घोषणा __arch_swab16 __arch_swab16

अटल अंतरभूत __attribute_स्थिर__ __u32 __arch_swab32(__u32 x)
अणु
	__यंत्र__(
	"	.set	push			\n"
	"	.set	arch=mips32r2		\n"
	"	wsbh	%0, %1			\n"
	"	rotr	%0, %0, 16		\n"
	"	.set	pop			\n"
	: "=r" (x)
	: "r" (x));

	वापस x;
पूर्ण
#घोषणा __arch_swab32 __arch_swab32

/*
 * Having alपढ़ोy checked क्रम MIPS R2, enable the optimized version क्रम
 * 64-bit kernel on r2 CPUs.
 */
#अगर_घोषित __mips64
अटल अंतरभूत __attribute_स्थिर__ __u64 __arch_swab64(__u64 x)
अणु
	__यंत्र__(
	"	.set	push			\n"
	"	.set	arch=mips64r2		\n"
	"	dsbh	%0, %1			\n"
	"	dshd	%0, %0			\n"
	"	.set	pop			\n"
	: "=r" (x)
	: "r" (x));

	वापस x;
पूर्ण
#घोषणा __arch_swab64 __arch_swab64
#पूर्ण_अगर /* __mips64 */
#पूर्ण_अगर /* (not __mips16) and (MIPS R2 or newer or Loongson 3A) */
#पूर्ण_अगर /* _ASM_SWAB_H */
