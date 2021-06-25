<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2014 Imagination Technologies Ltd.
 */

#अगर_अघोषित _ASM_MALTA_SPACES_H
#घोषणा _ASM_MALTA_SPACES_H

#अगर_घोषित CONFIG_EVA

/*
 * Traditional Malta Board Memory Map क्रम EVA
 *
 * 0x00000000 - 0x0fffffff: 1st RAM region, 256MB
 * 0x10000000 - 0x1bffffff: GIC and CPC Control Registers
 * 0x1c000000 - 0x1fffffff: I/O And Flash
 * 0x20000000 - 0x7fffffff: 2nd RAM region, 1.5GB
 * 0x80000000 - 0xffffffff: Physical memory aliases to 0x0 (2GB)
 *
 * The kernel is still located in 0x80000000(kseg0). However,
 * the physical mask has been shअगरted to 0x80000000 which exploits the alias
 * on the Malta board. As a result of which, we override the __pa_symbol
 * to peक्रमm direct mapping from भव to physical addresses. In other
 * words, the 0x80000000 भव address maps to 0x80000000 physical address
 * which in turn aliases to 0x0. We करो this in order to be able to use a flat
 * 2GB of memory (0x80000000 - 0xffffffff) so we can aव्योम the I/O hole in
 * 0x10000000 - 0x1fffffff.
 * The last 64KB of physical memory are reserved क्रम correct HIGHMEM
 * macros arithmetics.
 *
 */

#घोषणा PAGE_OFFSET	_AC(0x0, UL)
#घोषणा PHYS_OFFSET	_AC(0x80000000, UL)
#घोषणा HIGHMEM_START	_AC(0xffff0000, UL)

#घोषणा __pa_symbol(x)	(RELOC_HIDE((अचिन्हित दीर्घ)(x), 0))

#पूर्ण_अगर /* CONFIG_EVA */

#समावेश <यंत्र/mach-generic/spaces.h>

#पूर्ण_अगर /* _ASM_MALTA_SPACES_H */
