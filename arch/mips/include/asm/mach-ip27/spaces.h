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
#अगर_अघोषित _ASM_MACH_IP27_SPACES_H
#घोषणा _ASM_MACH_IP27_SPACES_H

#समावेश <linux/स्थिर.h>

/*
 * IP27 uses the R10000's uncached attribute feature.  Attribute 3 selects
 * uncached memory addressing. Hide the definitions on 32-bit compilation
 * of the compat-vdso code.
 */
#अगर_घोषित CONFIG_64BIT
#घोषणा HSPEC_BASE		_AC(0x9000000000000000, UL)
#घोषणा IO_BASE			_AC(0x9200000000000000, UL)
#घोषणा MSPEC_BASE		_AC(0x9400000000000000, UL)
#घोषणा UNCAC_BASE		_AC(0x9600000000000000, UL)
#घोषणा CAC_BASE		_AC(0xa800000000000000, UL)
#पूर्ण_अगर

#घोषणा TO_MSPEC(x)		(MSPEC_BASE | ((x) & TO_PHYS_MASK))
#घोषणा TO_HSPEC(x)		(HSPEC_BASE | ((x) & TO_PHYS_MASK))

#घोषणा HIGHMEM_START		(~0UL)

#समावेश <यंत्र/mach-generic/spaces.h>

#पूर्ण_अगर /* _ASM_MACH_IP27_SPACES_H */
