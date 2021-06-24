<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
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
#अगर_अघोषित __ASM_ARM_SWAB_H
#घोषणा __ASM_ARM_SWAB_H

#समावेश <uapi/यंत्र/swab.h>

#अगर __LINUX_ARM_ARCH__ >= 6

अटल अंतरभूत __attribute_स्थिर__ __u32 __arch_swahb32(__u32 x)
अणु
	__यंत्र__ ("rev16 %0, %1" : "=r" (x) : "r" (x));
	वापस x;
पूर्ण
#घोषणा __arch_swahb32 __arch_swahb32
#घोषणा __arch_swab16(x) ((__u16)__arch_swahb32(x))

अटल अंतरभूत __attribute_स्थिर__ __u32 __arch_swab32(__u32 x)
अणु
	__यंत्र__ ("rev %0, %1" : "=r" (x) : "r" (x));
	वापस x;
पूर्ण
#घोषणा __arch_swab32 __arch_swab32

#पूर्ण_अगर
#पूर्ण_अगर
