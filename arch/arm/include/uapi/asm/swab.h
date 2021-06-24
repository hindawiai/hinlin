<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 *  arch/arm/include/यंत्र/byteorder.h
 *
 * ARM Endian-ness.  In little endian mode, the data bus is connected such
 * that byte accesses appear as:
 *  0 = d0...d7, 1 = d8...d15, 2 = d16...d23, 3 = d24...d31
 * and word accesses (data or inकाष्ठाion) appear as:
 *  d0...d31
 *
 * When in big endian mode, byte accesses appear as:
 *  0 = d24...d31, 1 = d16...d23, 2 = d8...d15, 3 = d0...d7
 * and word accesses (data or inकाष्ठाion) appear as:
 *  d0...d31
 */
#अगर_अघोषित _UAPI__ASM_ARM_SWAB_H
#घोषणा _UAPI__ASM_ARM_SWAB_H

#समावेश <linux/compiler.h>
#समावेश <linux/types.h>

#अगर !defined(__STRICT_ANSI__) || defined(__KERNEL__)
#  define __SWAB_64_THRU_32__
#पूर्ण_अगर


#अगर !defined(__KERNEL__) || __LINUX_ARM_ARCH__ < 6
अटल अंतरभूत __attribute_स्थिर__ __u32 __arch_swab32(__u32 x)
अणु
	__u32 t;

#अगर_अघोषित __thumb__
	अगर (!__builtin_स्थिरant_p(x)) अणु
		/*
		 * The compiler needs a bit of a hपूर्णांक here to always करो the
		 * right thing and not screw it up to dअगरferent degrees
		 * depending on the gcc version.
		 */
		यंत्र ("eor\t%0, %1, %1, ror #16" : "=r" (t) : "r" (x));
	पूर्ण अन्यथा
#पूर्ण_अगर
		t = x ^ ((x << 16) | (x >> 16)); /* eor r1,r0,r0,ror #16 */

	x = (x << 24) | (x >> 8);		/* mov r0,r0,ror #8      */
	t &= ~0x00FF0000;			/* bic r1,r1,#0x00FF0000 */
	x ^= (t >> 8);				/* eor r0,r0,r1,lsr #8   */

	वापस x;
पूर्ण
#घोषणा __arch_swab32 __arch_swab32

#पूर्ण_अगर

#पूर्ण_अगर /* _UAPI__ASM_ARM_SWAB_H */
