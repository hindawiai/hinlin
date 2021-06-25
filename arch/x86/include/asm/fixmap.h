<शैली गुरु>
/*
 * fixmap.h: compile-समय भव memory allocation
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1998 Ingo Molnar
 *
 * Support of BIGMEM added by Gerhard Wichert, Siemens AG, July 1999
 * x86_32 and x86_64 पूर्णांकegration by Gustavo F. Paकरोvan, February 2009
 */

#अगर_अघोषित _ASM_X86_FIXMAP_H
#घोषणा _ASM_X86_FIXMAP_H

#समावेश <यंत्र/kmap_size.h>

/*
 * Exposed to assembly code क्रम setting up initial page tables. Cannot be
 * calculated in assembly code (fixmap entries are an क्रमागत), but is sanity
 * checked in the actual fixmap C code to make sure that the fixmap is
 * covered fully.
 */
#अगर_अघोषित CONFIG_DEBUG_KMAP_LOCAL_FORCE_MAP
# define FIXMAP_PMD_NUM	2
#अन्यथा
# define KM_PMDS	(KM_MAX_IDX * ((CONFIG_NR_CPUS + 511) / 512))
# define FIXMAP_PMD_NUM (KM_PMDS + 2)
#पूर्ण_अगर
/* fixmap starts करोwnwards from the 507th entry in level2_fixmap_pgt */
#घोषणा FIXMAP_PMD_TOP	507

#अगर_अघोषित __ASSEMBLY__
#समावेश <linux/kernel.h>
#समावेश <यंत्र/apicdef.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/pgtable_types.h>
#अगर_घोषित CONFIG_X86_32
#समावेश <linux/thपढ़ोs.h>
#अन्यथा
#समावेश <uapi/यंत्र/vsyscall.h>
#पूर्ण_अगर

/*
 * We can't declare FIXADDR_TOP as variable क्रम x86_64 because vsyscall
 * uses fixmaps that relies on FIXADDR_TOP क्रम proper address calculation.
 * Because of this, FIXADDR_TOP x86 पूर्णांकegration was left as later work.
 */
#अगर_घोषित CONFIG_X86_32
/*
 * Leave one empty page between vदो_स्मृति'ed areas and
 * the start of the fixmap.
 */
बाह्य अचिन्हित दीर्घ __FIXADDR_TOP;
#घोषणा FIXADDR_TOP	((अचिन्हित दीर्घ)__FIXADDR_TOP)
#अन्यथा
#घोषणा FIXADDR_TOP	(round_up(VSYSCALL_ADDR + PAGE_SIZE, 1<<PMD_SHIFT) - \
			 PAGE_SIZE)
#पूर्ण_अगर

/*
 * Here we define all the compile-समय 'special' भव
 * addresses. The poपूर्णांक is to have a स्थिरant address at
 * compile समय, but to set the physical address only
 * in the boot process.
 * क्रम x86_32: We allocate these special addresses
 * from the end of भव memory (0xfffff000) backwards.
 * Also this lets us करो fail-safe vदो_स्मृति(), we
 * can guarantee that these special addresses and
 * vदो_स्मृति()-ed addresses never overlap.
 *
 * These 'compile-time allocated' memory buffers are
 * fixed-size 4k pages (or larger अगर used with an increment
 * higher than 1). Use set_fixmap(idx,phys) to associate
 * physical memory with fixmap indices.
 *
 * TLB entries of such buffers will not be flushed across
 * task चयनes.
 */
क्रमागत fixed_addresses अणु
#अगर_घोषित CONFIG_X86_32
	FIX_HOLE,
#अन्यथा
#अगर_घोषित CONFIG_X86_VSYSCALL_EMULATION
	VSYSCALL_PAGE = (FIXADDR_TOP - VSYSCALL_ADDR) >> PAGE_SHIFT,
#पूर्ण_अगर
#पूर्ण_अगर
	FIX_DBGP_BASE,
	FIX_EARLYCON_MEM_BASE,
#अगर_घोषित CONFIG_PROVIDE_OHCI1394_DMA_INIT
	FIX_OHCI1394_BASE,
#पूर्ण_अगर
#अगर_घोषित CONFIG_X86_LOCAL_APIC
	FIX_APIC_BASE,	/* local (CPU) APIC) -- required क्रम SMP or not */
#पूर्ण_अगर
#अगर_घोषित CONFIG_X86_IO_APIC
	FIX_IO_APIC_BASE_0,
	FIX_IO_APIC_BASE_END = FIX_IO_APIC_BASE_0 + MAX_IO_APICS - 1,
#पूर्ण_अगर
#अगर_घोषित CONFIG_KMAP_LOCAL
	FIX_KMAP_BEGIN,	/* reserved pte's क्रम temporary kernel mappings */
	FIX_KMAP_END = FIX_KMAP_BEGIN + (KM_MAX_IDX * NR_CPUS) - 1,
#अगर_घोषित CONFIG_PCI_MMCONFIG
	FIX_PCIE_MCFG,
#पूर्ण_अगर
#पूर्ण_अगर
#अगर_घोषित CONFIG_PARAVIRT_XXL
	FIX_PARAVIRT_BOOTMAP,
#पूर्ण_अगर

#अगर_घोषित CONFIG_ACPI_APEI_GHES
	/* Used क्रम GHES mapping from assorted contexts */
	FIX_APEI_GHES_IRQ,
	FIX_APEI_GHES_NMI,
#पूर्ण_अगर

	__end_of_permanent_fixed_addresses,

	/*
	 * 512 temporary boot-समय mappings, used by early_ioremap(),
	 * beक्रमe ioremap() is functional.
	 *
	 * If necessary we round it up to the next 512 pages boundary so
	 * that we can have a single pmd entry and a single pte table:
	 */
#घोषणा NR_FIX_BTMAPS		64
#घोषणा FIX_BTMAPS_SLOTS	8
#घोषणा TOTAL_FIX_BTMAPS	(NR_FIX_BTMAPS * FIX_BTMAPS_SLOTS)
	FIX_BTMAP_END =
	 (__end_of_permanent_fixed_addresses ^
	  (__end_of_permanent_fixed_addresses + TOTAL_FIX_BTMAPS - 1)) &
	 -PTRS_PER_PTE
	 ? __end_of_permanent_fixed_addresses + TOTAL_FIX_BTMAPS -
	   (__end_of_permanent_fixed_addresses & (TOTAL_FIX_BTMAPS - 1))
	 : __end_of_permanent_fixed_addresses,
	FIX_BTMAP_BEGIN = FIX_BTMAP_END + TOTAL_FIX_BTMAPS - 1,
#अगर_घोषित CONFIG_X86_32
	FIX_WP_TEST,
#पूर्ण_अगर
#अगर_घोषित CONFIG_INTEL_TXT
	FIX_TBOOT_BASE,
#पूर्ण_अगर
	__end_of_fixed_addresses
पूर्ण;


बाह्य व्योम reserve_top_address(अचिन्हित दीर्घ reserve);

#घोषणा FIXADDR_SIZE		(__end_of_permanent_fixed_addresses << PAGE_SHIFT)
#घोषणा FIXADDR_START		(FIXADDR_TOP - FIXADDR_SIZE)
#घोषणा FIXADDR_TOT_SIZE	(__end_of_fixed_addresses << PAGE_SHIFT)
#घोषणा FIXADDR_TOT_START	(FIXADDR_TOP - FIXADDR_TOT_SIZE)

बाह्य पूर्णांक fixmaps_set;

बाह्य pte_t *pkmap_page_table;

व्योम __native_set_fixmap(क्रमागत fixed_addresses idx, pte_t pte);
व्योम native_set_fixmap(अचिन्हित /* क्रमागत fixed_addresses */ idx,
		       phys_addr_t phys, pgprot_t flags);

#अगर_अघोषित CONFIG_PARAVIRT_XXL
अटल अंतरभूत व्योम __set_fixmap(क्रमागत fixed_addresses idx,
				phys_addr_t phys, pgprot_t flags)
अणु
	native_set_fixmap(idx, phys, flags);
पूर्ण
#पूर्ण_अगर

/*
 * FIXMAP_PAGE_NOCACHE is used क्रम MMIO. Memory encryption is not
 * supported क्रम MMIO addresses, so make sure that the memory encryption
 * mask is not part of the page attributes.
 */
#घोषणा FIXMAP_PAGE_NOCACHE PAGE_KERNEL_IO_NOCACHE

/*
 * Early memremap routines used क्रम in-place encryption. The mappings created
 * by these routines are पूर्णांकended to be used as temporary mappings.
 */
व्योम __init *early_memremap_encrypted(resource_माप_प्रकार phys_addr,
				      अचिन्हित दीर्घ size);
व्योम __init *early_memremap_encrypted_wp(resource_माप_प्रकार phys_addr,
					 अचिन्हित दीर्घ size);
व्योम __init *early_memremap_decrypted(resource_माप_प्रकार phys_addr,
				      अचिन्हित दीर्घ size);
व्योम __init *early_memremap_decrypted_wp(resource_माप_प्रकार phys_addr,
					 अचिन्हित दीर्घ size);

#समावेश <यंत्र-generic/fixmap.h>

#घोषणा __late_set_fixmap(idx, phys, flags) __set_fixmap(idx, phys, flags)
#घोषणा __late_clear_fixmap(idx) __set_fixmap(idx, 0, __pgprot(0))

व्योम __early_set_fixmap(क्रमागत fixed_addresses idx,
			phys_addr_t phys, pgprot_t flags);

#पूर्ण_अगर /* !__ASSEMBLY__ */
#पूर्ण_अगर /* _ASM_X86_FIXMAP_H */
