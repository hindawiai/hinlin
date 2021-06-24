<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_IA64_SPARSEMEM_H
#घोषणा _ASM_IA64_SPARSEMEM_H

#अगर_घोषित CONFIG_SPARSEMEM
#समावेश <यंत्र/page.h>
/*
 * SECTION_SIZE_BITS            2^N: how big each section will be
 * MAX_PHYSMEM_BITS             2^N: how much memory we can have in that space
 */

#घोषणा SECTION_SIZE_BITS	(30)
#घोषणा MAX_PHYSMEM_BITS	(50)
#अगर_घोषित CONFIG_FORCE_MAX_ZONEORDER
#अगर ((CONFIG_FORCE_MAX_ZONEORDER - 1 + PAGE_SHIFT) > SECTION_SIZE_BITS)
#अघोषित SECTION_SIZE_BITS
#घोषणा SECTION_SIZE_BITS (CONFIG_FORCE_MAX_ZONEORDER - 1 + PAGE_SHIFT)
#पूर्ण_अगर
#पूर्ण_अगर

#पूर्ण_अगर /* CONFIG_SPARSEMEM */

#अगर_घोषित CONFIG_MEMORY_HOTPLUG
पूर्णांक memory_add_physaddr_to_nid(u64 addr);
#घोषणा memory_add_physaddr_to_nid memory_add_physaddr_to_nid
#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_IA64_SPARSEMEM_H */
