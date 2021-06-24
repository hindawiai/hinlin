<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित ASMARM_SPARSEMEM_H
#घोषणा ASMARM_SPARSEMEM_H

#समावेश <यंत्र/memory.h>

/*
 * Two definitions are required क्रम sparsemem:
 *
 * MAX_PHYSMEM_BITS: The number of physical address bits required
 *   to address the last byte of memory.
 *
 * SECTION_SIZE_BITS: The number of physical address bits to cover
 *   the maximum amount of memory in a section.
 *
 * Eg, अगर you have 2 banks of up to 64MB at 0x80000000, 0x84000000,
 * then MAX_PHYSMEM_BITS is 32, SECTION_SIZE_BITS is 26.
 *
 * These can be overridden in your mach/memory.h.
 */
#अगर !defined(MAX_PHYSMEM_BITS) || !defined(SECTION_SIZE_BITS)
#घोषणा MAX_PHYSMEM_BITS	36
#घोषणा SECTION_SIZE_BITS	28
#पूर्ण_अगर

#पूर्ण_अगर
