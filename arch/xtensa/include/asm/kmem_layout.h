<शैली गुरु>
/*
 * Kernel भव memory layout definitions.
 *
 * This file is subject to the terms and conditions of the GNU General
 * Public License.  See the file "COPYING" in the मुख्य directory of
 * this archive क्रम more details.
 *
 * Copyright (C) 2016 Cadence Design Systems Inc.
 */

#अगर_अघोषित _XTENSA_KMEM_LAYOUT_H
#घोषणा _XTENSA_KMEM_LAYOUT_H

#समावेश <यंत्र/core.h>
#समावेश <यंत्र/types.h>

#अगर_घोषित CONFIG_MMU

/*
 * Fixed TLB translations in the processor.
 */

#घोषणा XCHAL_PAGE_TABLE_VADDR	__XTENSA_UL_CONST(0x80000000)
#घोषणा XCHAL_PAGE_TABLE_SIZE	__XTENSA_UL_CONST(0x00400000)

#अगर defined(CONFIG_XTENSA_KSEG_MMU_V2)

#घोषणा XCHAL_KSEG_CACHED_VADDR	__XTENSA_UL_CONST(0xd0000000)
#घोषणा XCHAL_KSEG_BYPASS_VADDR	__XTENSA_UL_CONST(0xd8000000)
#घोषणा XCHAL_KSEG_SIZE		__XTENSA_UL_CONST(0x08000000)
#घोषणा XCHAL_KSEG_ALIGNMENT	__XTENSA_UL_CONST(0x08000000)
#घोषणा XCHAL_KSEG_TLB_WAY	5
#घोषणा XCHAL_KIO_TLB_WAY	6

#या_अगर defined(CONFIG_XTENSA_KSEG_256M)

#घोषणा XCHAL_KSEG_CACHED_VADDR	__XTENSA_UL_CONST(0xb0000000)
#घोषणा XCHAL_KSEG_BYPASS_VADDR	__XTENSA_UL_CONST(0xc0000000)
#घोषणा XCHAL_KSEG_SIZE		__XTENSA_UL_CONST(0x10000000)
#घोषणा XCHAL_KSEG_ALIGNMENT	__XTENSA_UL_CONST(0x10000000)
#घोषणा XCHAL_KSEG_TLB_WAY	6
#घोषणा XCHAL_KIO_TLB_WAY	6

#या_अगर defined(CONFIG_XTENSA_KSEG_512M)

#घोषणा XCHAL_KSEG_CACHED_VADDR	__XTENSA_UL_CONST(0xa0000000)
#घोषणा XCHAL_KSEG_BYPASS_VADDR	__XTENSA_UL_CONST(0xc0000000)
#घोषणा XCHAL_KSEG_SIZE		__XTENSA_UL_CONST(0x20000000)
#घोषणा XCHAL_KSEG_ALIGNMENT	__XTENSA_UL_CONST(0x10000000)
#घोषणा XCHAL_KSEG_TLB_WAY	6
#घोषणा XCHAL_KIO_TLB_WAY	6

#अन्यथा
#त्रुटि Unsupported KSEG configuration
#पूर्ण_अगर

#अगर_घोषित CONFIG_KSEG_PADDR
#घोषणा XCHAL_KSEG_PADDR        __XTENSA_UL_CONST(CONFIG_KSEG_PADDR)
#अन्यथा
#घोषणा XCHAL_KSEG_PADDR	__XTENSA_UL_CONST(0x00000000)
#पूर्ण_अगर

#अगर XCHAL_KSEG_PADDR & (XCHAL_KSEG_ALIGNMENT - 1)
#त्रुटि XCHAL_KSEG_PADDR is not properly aligned to XCHAL_KSEG_ALIGNMENT
#पूर्ण_अगर

#पूर्ण_अगर

/* KIO definition */

#अगर XCHAL_HAVE_PTP_MMU
#घोषणा XCHAL_KIO_CACHED_VADDR		0xe0000000
#घोषणा XCHAL_KIO_BYPASS_VADDR		0xf0000000
#घोषणा XCHAL_KIO_DEFAULT_PADDR		0xf0000000
#अन्यथा
#घोषणा XCHAL_KIO_BYPASS_VADDR		XCHAL_KIO_PADDR
#घोषणा XCHAL_KIO_DEFAULT_PADDR		0x90000000
#पूर्ण_अगर
#घोषणा XCHAL_KIO_SIZE			0x10000000

#अगर (!XCHAL_HAVE_PTP_MMU || XCHAL_HAVE_SPANNING_WAY) && defined(CONFIG_OF)
#घोषणा XCHAL_KIO_PADDR			xtensa_get_kio_paddr()
#अगर_अघोषित __ASSEMBLY__
बाह्य अचिन्हित दीर्घ xtensa_kio_paddr;

अटल अंतरभूत अचिन्हित दीर्घ xtensa_get_kio_paddr(व्योम)
अणु
	वापस xtensa_kio_paddr;
पूर्ण
#पूर्ण_अगर
#अन्यथा
#घोषणा XCHAL_KIO_PADDR			XCHAL_KIO_DEFAULT_PADDR
#पूर्ण_अगर

/* KERNEL_STACK definition */

#अगर_अघोषित CONFIG_KASAN
#घोषणा KERNEL_STACK_SHIFT	13
#अन्यथा
#घोषणा KERNEL_STACK_SHIFT	15
#पूर्ण_अगर
#घोषणा KERNEL_STACK_SIZE	(1 << KERNEL_STACK_SHIFT)

#पूर्ण_अगर
