<शैली गुरु>
/*
 * Various machine type macros
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (c) 1998, 2000 Harald Koerfgen
 */

#अगर_अघोषित __ASM_DEC_MACHTYPE_H
#घोषणा __ASM_DEC_MACHTYPE_H

#समावेश <यंत्र/bootinfo.h>

#घोषणा TURBOCHANNEL	(mips_machtype == MACH_DS5000_200 || \
			 mips_machtype == MACH_DS5000_1XX || \
			 mips_machtype == MACH_DS5000_XX  || \
			 mips_machtype == MACH_DS5000_2X0 || \
			 mips_machtype == MACH_DS5900)

#घोषणा IOASIC		(mips_machtype == MACH_DS5000_1XX || \
			 mips_machtype == MACH_DS5000_XX  || \
			 mips_machtype == MACH_DS5000_2X0 || \
			 mips_machtype == MACH_DS5900)

#पूर्ण_अगर
