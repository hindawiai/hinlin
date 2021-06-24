<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित PAGE_FLAGS_LAYOUT_H
#घोषणा PAGE_FLAGS_LAYOUT_H

#समावेश <linux/numa.h>
#समावेश <generated/bounds.h>

/*
 * When a memory allocation must conक्रमm to specअगरic limitations (such
 * as being suitable क्रम DMA) the caller will pass in hपूर्णांकs to the
 * allocator in the gfp_mask, in the zone modअगरier bits.  These bits
 * are used to select a priority ordered list of memory zones which
 * match the requested limits. See gfp_zone() in include/linux/gfp.h
 */
#अगर MAX_NR_ZONES < 2
#घोषणा ZONES_SHIFT 0
#या_अगर MAX_NR_ZONES <= 2
#घोषणा ZONES_SHIFT 1
#या_अगर MAX_NR_ZONES <= 4
#घोषणा ZONES_SHIFT 2
#या_अगर MAX_NR_ZONES <= 8
#घोषणा ZONES_SHIFT 3
#अन्यथा
#त्रुटि ZONES_SHIFT "Too many zones configured"
#पूर्ण_अगर

#घोषणा ZONES_WIDTH		ZONES_SHIFT

#अगर_घोषित CONFIG_SPARSEMEM
#समावेश <यंत्र/sparseस्मृति.स>
#घोषणा SECTIONS_SHIFT	(MAX_PHYSMEM_BITS - SECTION_SIZE_BITS)
#अन्यथा
#घोषणा SECTIONS_SHIFT	0
#पूर्ण_अगर

#अगर_अघोषित BUILD_VDSO32_64
/*
 * page->flags layout:
 *
 * There are five possibilities क्रम how page->flags get laid out.  The first
 * pair is क्रम the normal हाल without sparsemem. The second pair is क्रम
 * sparsemem when there is plenty of space क्रम node and section inक्रमmation.
 * The last is when there is insufficient space in page->flags and a separate
 * lookup is necessary.
 *
 * No sparsemem or sparsemem vmemmap: |       NODE     | ZONE |             ... | FLAGS |
 *      " plus space क्रम last_cpupid: |       NODE     | ZONE | LAST_CPUPID ... | FLAGS |
 * classic sparse with space क्रम node:| SECTION | NODE | ZONE |             ... | FLAGS |
 *      " plus space क्रम last_cpupid: | SECTION | NODE | ZONE | LAST_CPUPID ... | FLAGS |
 * classic sparse no space क्रम node:  | SECTION |     ZONE    | ... | FLAGS |
 */
#अगर defined(CONFIG_SPARSEMEM) && !defined(CONFIG_SPARSEMEM_VMEMMAP)
#घोषणा SECTIONS_WIDTH		SECTIONS_SHIFT
#अन्यथा
#घोषणा SECTIONS_WIDTH		0
#पूर्ण_अगर

#अगर ZONES_WIDTH + SECTIONS_WIDTH + NODES_SHIFT <= BITS_PER_LONG - NR_PAGEFLAGS
#घोषणा NODES_WIDTH		NODES_SHIFT
#या_अगर defined(CONFIG_SPARSEMEM_VMEMMAP)
#त्रुटि "Vmemmap: No space for nodes field in page flags"
#अन्यथा
#घोषणा NODES_WIDTH		0
#पूर्ण_अगर

/*
 * Note that this #घोषणा MUST have a value so that it can be tested with
 * the IS_ENABLED() macro.
 */
#अगर NODES_SHIFT != 0 && NODES_WIDTH == 0
#घोषणा NODE_NOT_IN_PAGE_FLAGS	1
#पूर्ण_अगर

#अगर defined(CONFIG_KASAN_SW_TAGS) || defined(CONFIG_KASAN_HW_TAGS)
#घोषणा KASAN_TAG_WIDTH 8
#अन्यथा
#घोषणा KASAN_TAG_WIDTH 0
#पूर्ण_अगर

#अगर_घोषित CONFIG_NUMA_BALANCING
#घोषणा LAST__PID_SHIFT 8
#घोषणा LAST__PID_MASK  ((1 << LAST__PID_SHIFT)-1)

#घोषणा LAST__CPU_SHIFT NR_CPUS_BITS
#घोषणा LAST__CPU_MASK  ((1 << LAST__CPU_SHIFT)-1)

#घोषणा LAST_CPUPID_SHIFT (LAST__PID_SHIFT+LAST__CPU_SHIFT)
#अन्यथा
#घोषणा LAST_CPUPID_SHIFT 0
#पूर्ण_अगर

#अगर ZONES_WIDTH + SECTIONS_WIDTH + NODES_WIDTH + KASAN_TAG_WIDTH + LAST_CPUPID_SHIFT \
	<= BITS_PER_LONG - NR_PAGEFLAGS
#घोषणा LAST_CPUPID_WIDTH LAST_CPUPID_SHIFT
#अन्यथा
#घोषणा LAST_CPUPID_WIDTH 0
#पूर्ण_अगर

#अगर LAST_CPUPID_SHIFT != 0 && LAST_CPUPID_WIDTH == 0
#घोषणा LAST_CPUPID_NOT_IN_PAGE_FLAGS
#पूर्ण_अगर

#अगर ZONES_WIDTH + SECTIONS_WIDTH + NODES_WIDTH + KASAN_TAG_WIDTH + LAST_CPUPID_WIDTH \
	> BITS_PER_LONG - NR_PAGEFLAGS
#त्रुटि "Not enough bits in page flags"
#पूर्ण_अगर

#पूर्ण_अगर
#पूर्ण_अगर /* _LINUX_PAGE_FLAGS_LAYOUT */
