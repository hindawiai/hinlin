<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1994 - 1999, 2000, 03, 04 Ralf Baechle
 * Copyright (C) 2000, 2002  Maciej W. Rozycki
 * Copyright (C) 1990, 1999, 2000 Silicon Graphics, Inc.
 */
#अगर_अघोषित _ASM_MACH_GENERIC_SPACES_H
#घोषणा _ASM_MACH_GENERIC_SPACES_H

#समावेश <linux/स्थिर.h>

#समावेश <यंत्र/mipsregs.h>

#अगर_अघोषित IO_SPACE_LIMIT
#घोषणा IO_SPACE_LIMIT 0xffff
#पूर्ण_अगर

/*
 * This gives the physical RAM offset.
 */
#अगर_अघोषित __ASSEMBLY__
# अगर defined(CONFIG_MIPS_AUTO_PFN_OFFSET)
#  define PHYS_OFFSET		((अचिन्हित दीर्घ)PFN_PHYS(ARCH_PFN_OFFSET))
# elअगर !defined(PHYS_OFFSET)
#  define PHYS_OFFSET		_AC(0, UL)
# endअगर
#पूर्ण_अगर /* __ASSEMBLY__ */

#अगर_घोषित CONFIG_32BIT
#घोषणा CAC_BASE		_AC(0x80000000, UL)
#अगर_अघोषित IO_BASE
#घोषणा IO_BASE			_AC(0xa0000000, UL)
#पूर्ण_अगर
#अगर_अघोषित UNCAC_BASE
#घोषणा UNCAC_BASE		_AC(0xa0000000, UL)
#पूर्ण_अगर

#अगर_अघोषित MAP_BASE
#घोषणा MAP_BASE		_AC(0xc0000000, UL)
#पूर्ण_अगर

/*
 * Memory above this physical address will be considered highmem.
 */
#अगर_अघोषित HIGHMEM_START
#घोषणा HIGHMEM_START		_AC(0x20000000, UL)
#पूर्ण_अगर

#पूर्ण_अगर /* CONFIG_32BIT */

#अगर_घोषित CONFIG_64BIT

#अगर_अघोषित CAC_BASE
#घोषणा CAC_BASE	PHYS_TO_XKPHYS(पढ़ो_c0_config() & CONF_CM_CMASK, 0)
#पूर्ण_अगर

#अगर_अघोषित IO_BASE
#घोषणा IO_BASE			_AC(0x9000000000000000, UL)
#पूर्ण_अगर

#अगर_अघोषित UNCAC_BASE
#घोषणा UNCAC_BASE		_AC(0x9000000000000000, UL)
#पूर्ण_अगर

#अगर_अघोषित MAP_BASE
#घोषणा MAP_BASE		_AC(0xc000000000000000, UL)
#पूर्ण_अगर

/*
 * Memory above this physical address will be considered highmem.
 * Fixme: 59 bits is a fictive number and makes assumptions about processors
 * in the distant future.  Nobody will care क्रम a few years :-)
 */
#अगर_अघोषित HIGHMEM_START
#घोषणा HIGHMEM_START		(_AC(1, UL) << _AC(59, UL))
#पूर्ण_अगर

#घोषणा TO_PHYS(x)		(	      ((x) & TO_PHYS_MASK))
#घोषणा TO_CAC(x)		(CAC_BASE   | ((x) & TO_PHYS_MASK))
#घोषणा TO_UNCAC(x)		(UNCAC_BASE | ((x) & TO_PHYS_MASK))

#पूर्ण_अगर /* CONFIG_64BIT */

/*
 * This handles the memory map.
 */
#अगर_अघोषित PAGE_OFFSET
#घोषणा PAGE_OFFSET		(CAC_BASE + PHYS_OFFSET)
#पूर्ण_अगर

#अगर_अघोषित FIXADDR_TOP
#घोषणा FIXADDR_TOP		((अचिन्हित दीर्घ)(दीर्घ)(पूर्णांक)0xfffe0000)
#पूर्ण_अगर

#पूर्ण_अगर /* __ASM_MACH_GENERIC_SPACES_H */
