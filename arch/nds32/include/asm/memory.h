<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
// Copyright (C) 2005-2017 Andes Technology Corporation

#अगर_अघोषित __ASM_NDS32_MEMORY_H
#घोषणा __ASM_NDS32_MEMORY_H

#समावेश <linux/compiler.h>
#समावेश <linux/sizes.h>

#अगर_अघोषित __ASSEMBLY__
#समावेश <यंत्र/page.h>
#पूर्ण_अगर

#अगर_अघोषित PHYS_OFFSET
#घोषणा PHYS_OFFSET     (0x0)
#पूर्ण_अगर

/*
 * TASK_SIZE - the maximum size of a user space task.
 * TASK_UNMAPPED_BASE - the lower boundary of the mmap VM area
 */
#घोषणा TASK_SIZE		((CONFIG_PAGE_OFFSET) - (SZ_32M))
#घोषणा TASK_UNMAPPED_BASE	ALIGN(TASK_SIZE / 3, SZ_32M)
#घोषणा PAGE_OFFSET		(CONFIG_PAGE_OFFSET)

/*
 * Physical vs भव RAM address space conversion.  These are
 * निजी definitions which should NOT be used outside memory.h
 * files.  Use virt_to_phys/phys_to_virt/__pa/__va instead.
 */
#अगर_अघोषित __virt_to_phys
#घोषणा __virt_to_phys(x)	((x) - PAGE_OFFSET + PHYS_OFFSET)
#घोषणा __phys_to_virt(x)	((x) - PHYS_OFFSET + PAGE_OFFSET)
#पूर्ण_अगर

/*
 * The module space lives between the addresses given by TASK_SIZE
 * and PAGE_OFFSET - it must be within 32MB of the kernel text.
 */
#घोषणा MODULES_END	(PAGE_OFFSET)
#घोषणा MODULES_VADDR	(MODULES_END - SZ_32M)

#अगर TASK_SIZE > MODULES_VADDR
#त्रुटि Top of user space clashes with start of module space
#पूर्ण_अगर

#अगर_अघोषित __ASSEMBLY__

/*
 * PFNs are used to describe any physical page; this means
 * PFN 0 == physical address 0.
 *
 * This is the PFN of the first RAM page in the kernel
 * direct-mapped view.  We assume this is the first page
 * of RAM in the mem_map as well.
 */
#घोषणा PHYS_PFN_OFFSET	(PHYS_OFFSET >> PAGE_SHIFT)

/*
 * Drivers should NOT use these either.
 */
#घोषणा __pa(x)			__virt_to_phys((अचिन्हित दीर्घ)(x))
#घोषणा __va(x)			((व्योम *)__phys_to_virt((अचिन्हित दीर्घ)(x)))

/*
 * Conversion between a काष्ठा page and a physical address.
 *
 * Note: when converting an unknown physical address to a
 * काष्ठा page, the resulting poपूर्णांकer must be validated
 * using VALID_PAGE().  It must वापस an invalid काष्ठा page
 * क्रम any physical address not corresponding to a प्रणाली
 * RAM address.
 *
 *  pfn_valid(pfn)	indicates whether a PFN number is valid
 *
 *  virt_to_page(k)	convert a _valid_ भव address to काष्ठा page *
 *  virt_addr_valid(k)	indicates whether a भव address is valid
 */
#अगर_अघोषित CONFIG_DISCONTIGMEM

#घोषणा ARCH_PFN_OFFSET		PHYS_PFN_OFFSET
#घोषणा pfn_valid(pfn)		((pfn) >= PHYS_PFN_OFFSET && (pfn) < (PHYS_PFN_OFFSET + max_mapnr))

#घोषणा virt_to_page(kaddr)	(pfn_to_page(__pa(kaddr) >> PAGE_SHIFT))
#घोषणा virt_addr_valid(kaddr)	((अचिन्हित दीर्घ)(kaddr) >= PAGE_OFFSET && (अचिन्हित दीर्घ)(kaddr) < (अचिन्हित दीर्घ)high_memory)

#अन्यथा /* CONFIG_DISCONTIGMEM */
#त्रुटि CONFIG_DISCONTIGMEM is not supported yet.
#पूर्ण_अगर /* !CONFIG_DISCONTIGMEM */

#घोषणा page_to_phys(page)	(page_to_pfn(page) << PAGE_SHIFT)

#पूर्ण_अगर

#समावेश <यंत्र-generic/memory_model.h>

#पूर्ण_अगर
