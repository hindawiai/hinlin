<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1996, 99 Ralf Baechle
 * Copyright (C) 2000, 2002  Maciej W. Rozycki
 * Copyright (C) 1990, 1999 by Silicon Graphics, Inc.
 */
#अगर_अघोषित _ASM_ADDRSPACE_H
#घोषणा _ASM_ADDRSPACE_H

#समावेश <spaces.h>

/*
 *  Configure language
 */
#अगर_घोषित __ASSEMBLY__
#घोषणा _ATYPE_
#घोषणा _ATYPE32_
#घोषणा _ATYPE64_
#घोषणा _CONST64_(x)	x
#अन्यथा
#घोषणा _ATYPE_		__PTRDIFF_TYPE__
#घोषणा _ATYPE32_	पूर्णांक
#घोषणा _ATYPE64_	__s64
#अगर_घोषित CONFIG_64BIT
#घोषणा _CONST64_(x)	x ## L
#अन्यथा
#घोषणा _CONST64_(x)	x ## LL
#पूर्ण_अगर
#पूर्ण_अगर

/*
 *  32-bit MIPS address spaces
 */
#अगर_घोषित __ASSEMBLY__
#घोषणा _ACAST32_
#घोषणा _ACAST64_
#अन्यथा
#घोषणा _ACAST32_		(_ATYPE_)(_ATYPE32_)	/* widen अगर necessary */
#घोषणा _ACAST64_		(_ATYPE64_)		/* करो _not_ narrow */
#पूर्ण_अगर

/*
 * Returns the kernel segment base of a given address
 */
#घोषणा KSEGX(a)		((_ACAST32_(a)) & _ACAST32_(0xe0000000))

/*
 * Returns the physical address of a CKSEGx / XKPHYS address
 */
#घोषणा CPHYSADDR(a)		((_ACAST32_(a)) & 0x1fffffff)
#घोषणा XPHYSADDR(a)		((_ACAST64_(a)) &			\
				 _CONST64_(0x0000ffffffffffff))

#अगर_घोषित CONFIG_64BIT

/*
 * Memory segments (64bit kernel mode addresses)
 * The compatibility segments use the full 64-bit sign extended value.  Note
 * the R8000 करोesn't have them so don't reference these in generic MIPS code.
 */
#घोषणा XKUSEG			_CONST64_(0x0000000000000000)
#घोषणा XKSSEG			_CONST64_(0x4000000000000000)
#घोषणा XKPHYS			_CONST64_(0x8000000000000000)
#घोषणा XKSEG			_CONST64_(0xc000000000000000)
#घोषणा CKSEG0			_CONST64_(0xffffffff80000000)
#घोषणा CKSEG1			_CONST64_(0xffffffffa0000000)
#घोषणा CKSSEG			_CONST64_(0xffffffffc0000000)
#घोषणा CKSEG3			_CONST64_(0xffffffffe0000000)

#घोषणा CKSEG0ADDR(a)		(CPHYSADDR(a) | CKSEG0)
#घोषणा CKSEG1ADDR(a)		(CPHYSADDR(a) | CKSEG1)
#घोषणा CKSEG2ADDR(a)		(CPHYSADDR(a) | CKSEG2)
#घोषणा CKSEG3ADDR(a)		(CPHYSADDR(a) | CKSEG3)

#अन्यथा

#घोषणा CKSEG0ADDR(a)		(CPHYSADDR(a) | KSEG0)
#घोषणा CKSEG1ADDR(a)		(CPHYSADDR(a) | KSEG1)
#घोषणा CKSEG2ADDR(a)		(CPHYSADDR(a) | KSEG2)
#घोषणा CKSEG3ADDR(a)		(CPHYSADDR(a) | KSEG3)

/*
 * Map an address to a certain kernel segment
 */
#घोषणा KSEG0ADDR(a)		(CPHYSADDR(a) | KSEG0)
#घोषणा KSEG1ADDR(a)		(CPHYSADDR(a) | KSEG1)
#घोषणा KSEG2ADDR(a)		(CPHYSADDR(a) | KSEG2)
#घोषणा KSEG3ADDR(a)		(CPHYSADDR(a) | KSEG3)

/*
 * Memory segments (32bit kernel mode addresses)
 * These are the traditional names used in the 32-bit universe.
 */
#घोषणा KUSEG			0x00000000
#घोषणा KSEG0			0x80000000
#घोषणा KSEG1			0xa0000000
#घोषणा KSEG2			0xc0000000
#घोषणा KSEG3			0xe0000000

#घोषणा CKUSEG			0x00000000
#घोषणा CKSEG0			0x80000000
#घोषणा CKSEG1			0xa0000000
#घोषणा CKSEG2			0xc0000000
#घोषणा CKSEG3			0xe0000000

#पूर्ण_अगर

/*
 * Cache modes क्रम XKPHYS address conversion macros
 */
#घोषणा K_CALG_COH_EXCL1_NOL2	0
#घोषणा K_CALG_COH_SHRL1_NOL2	1
#घोषणा K_CALG_UNCACHED		2
#घोषणा K_CALG_NONCOHERENT	3
#घोषणा K_CALG_COH_EXCL		4
#घोषणा K_CALG_COH_SHAREABLE	5
#घोषणा K_CALG_NOTUSED		6
#घोषणा K_CALG_UNCACHED_ACCEL	7

/*
 * 64-bit address conversions
 */
#घोषणा PHYS_TO_XKSEG_UNCACHED(p)	PHYS_TO_XKPHYS(K_CALG_UNCACHED, (p))
#घोषणा PHYS_TO_XKSEG_CACHED(p)		PHYS_TO_XKPHYS(K_CALG_COH_SHAREABLE, (p))
#घोषणा XKPHYS_TO_PHYS(p)		((p) & TO_PHYS_MASK)
#घोषणा PHYS_TO_XKPHYS(cm, a)		(XKPHYS | (_ACAST64_(cm) << 59) | (a))

/*
 * The ultimate limited of the 64-bit MIPS architecture:  2 bits क्रम selecting
 * the region, 3 bits क्रम the CCA mode.  This leaves 59 bits of which the
 * R8000 implements most with its 48-bit physical address space.
 */
#घोषणा TO_PHYS_MASK	_CONST64_(0x07ffffffffffffff)	/* 2^^59 - 1 */

#घोषणा COMPAT_K1BASE32		_CONST64_(0xffffffffa0000000)
#घोषणा PHYS_TO_COMPATK1(x)	((x) | COMPAT_K1BASE32) /* 32-bit compat k1 */

#घोषणा KDM_TO_PHYS(x)		(_ACAST64_ (x) & TO_PHYS_MASK)
#घोषणा PHYS_TO_K0(x)		(_ACAST64_ (x) | CAC_BASE)

#पूर्ण_अगर /* _ASM_ADDRSPACE_H */
