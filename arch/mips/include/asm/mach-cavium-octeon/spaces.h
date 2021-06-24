<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2012 Cavium, Inc.
 */
#अगर_अघोषित _ASM_MACH_CAVIUM_OCTEON_SPACES_H
#घोषणा _ASM_MACH_CAVIUM_OCTEON_SPACES_H

#समावेश <linux/स्थिर.h>

#अगर_घोषित CONFIG_64BIT
/* They are all the same and some OCTEON II cores cannot handle 0xa8.. */
#घोषणा CAC_BASE		_AC(0x8000000000000000, UL)
#घोषणा UNCAC_BASE		_AC(0x8000000000000000, UL)
#घोषणा IO_BASE			_AC(0x8000000000000000, UL)


#पूर्ण_अगर /* CONFIG_64BIT */

#समावेश <यंत्र/mach-generic/spaces.h>

#पूर्ण_अगर /* _ASM_MACH_CAVIUM_OCTEON_SPACES_H */
