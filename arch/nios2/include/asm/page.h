<शैली गुरु>
/*
 * Copyright (C) 2011 Tobias Klauser <tklauser@distanz.ch>
 * Copyright (C) 2004 Microtronix Datacom Ltd.
 *
 * MMU support based on यंत्र/page.h from mips which is:
 *
 * Copyright (C) 1994 - 1999, 2000, 03 Ralf Baechle
 * Copyright (C) 1999, 2000 Silicon Graphics, Inc.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */

#अगर_अघोषित _ASM_NIOS2_PAGE_H
#घोषणा _ASM_NIOS2_PAGE_H

#समावेश <linux/pfn.h>
#समावेश <linux/स्थिर.h>

/*
 * PAGE_SHIFT determines the page size
 */
#घोषणा PAGE_SHIFT	12
#घोषणा PAGE_SIZE	(_AC(1, UL) << PAGE_SHIFT)
#घोषणा PAGE_MASK	(~(PAGE_SIZE - 1))

/*
 * PAGE_OFFSET -- the first address of the first page of memory.
 */
#घोषणा PAGE_OFFSET	\
	(CONFIG_NIOS2_MEM_BASE + CONFIG_NIOS2_KERNEL_REGION_BASE)

#अगर_अघोषित __ASSEMBLY__

/*
 * This gives the physical RAM offset.
 */
#घोषणा PHYS_OFFSET		CONFIG_NIOS2_MEM_BASE

/*
 * It's normally defined only for FLATMEM config but it's
 * used in our early mem init code क्रम all memory models.
 * So always define it.
 */
#घोषणा ARCH_PFN_OFFSET		PFN_UP(PHYS_OFFSET)

#घोषणा clear_page(page)	स_रखो((page), 0, PAGE_SIZE)
#घोषणा copy_page(to, from)	स_नकल((to), (from), PAGE_SIZE)

काष्ठा page;

बाह्य व्योम clear_user_page(व्योम *addr, अचिन्हित दीर्घ vaddr, काष्ठा page *page);
बाह्य व्योम copy_user_page(व्योम *vto, व्योम *vfrom, अचिन्हित दीर्घ vaddr,
				काष्ठा page *to);

/*
 * These are used to make use of C type-checking.
 */
प्रकार काष्ठा page *pgtable_t;
प्रकार काष्ठा अणु अचिन्हित दीर्घ pte; पूर्ण pte_t;
प्रकार काष्ठा अणु अचिन्हित दीर्घ pgd; पूर्ण pgd_t;
प्रकार काष्ठा अणु अचिन्हित दीर्घ pgprot; पूर्ण pgprot_t;

#घोषणा pte_val(x)	((x).pte)
#घोषणा pgd_val(x)	((x).pgd)
#घोषणा pgprot_val(x)	((x).pgprot)

#घोषणा __pte(x)	((pte_t) अणु (x) पूर्ण)
#घोषणा __pgd(x)	((pgd_t) अणु (x) पूर्ण)
#घोषणा __pgprot(x)	((pgprot_t) अणु (x) पूर्ण)

बाह्य अचिन्हित दीर्घ memory_start;
बाह्य अचिन्हित दीर्घ memory_end;
बाह्य अचिन्हित दीर्घ memory_size;

बाह्य काष्ठा page *mem_map;

# define __pa(x)		\
	((अचिन्हित दीर्घ)(x) - PAGE_OFFSET + PHYS_OFFSET)
# define __va(x)		\
	((व्योम *)((अचिन्हित दीर्घ)(x) + PAGE_OFFSET - PHYS_OFFSET))

#घोषणा page_to_virt(page)	\
	((व्योम *)(((page) - mem_map) << PAGE_SHIFT) + PAGE_OFFSET)

# define pfn_to_kaddr(pfn)	__va((pfn) << PAGE_SHIFT)

अटल अंतरभूत bool pfn_valid(अचिन्हित दीर्घ pfn)
अणु
	/* aव्योम <linux/mm.h> include hell */
	बाह्य अचिन्हित दीर्घ max_mapnr;
	अचिन्हित दीर्घ pfn_offset = ARCH_PFN_OFFSET;

	वापस pfn >= pfn_offset && pfn < max_mapnr;
पूर्ण

# define virt_to_page(vaddr)	pfn_to_page(PFN_DOWN(virt_to_phys(vaddr)))
# define virt_addr_valid(vaddr)	pfn_valid(PFN_DOWN(virt_to_phys(vaddr)))

# define VM_DATA_DEFAULT_FLAGS	VM_DATA_FLAGS_NON_EXEC

#समावेश <यंत्र-generic/memory_model.h>

#समावेश <यंत्र-generic/getorder.h>

#पूर्ण_अगर /* !__ASSEMBLY__ */

#पूर्ण_अगर /* _ASM_NIOS2_PAGE_H */
