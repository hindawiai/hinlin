<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  arch/arm/include/यंत्र/memory.h
 *
 *  Copyright (C) 2000-2002 Russell King
 *  modअगरication क्रम nommu, Hyok S. Choi, 2004
 *
 *  Note: this file should not be included by non-यंत्र/.h files
 */
#अगर_अघोषित __ASM_ARM_MEMORY_H
#घोषणा __ASM_ARM_MEMORY_H

#समावेश <linux/compiler.h>
#समावेश <linux/स्थिर.h>
#समावेश <linux/types.h>
#समावेश <linux/sizes.h>

#अगर_घोषित CONFIG_NEED_MACH_MEMORY_H
#समावेश <mach/memory.h>
#पूर्ण_अगर
#समावेश <यंत्र/kasan_def.h>

/* PAGE_OFFSET - the भव address of the start of the kernel image */
#घोषणा PAGE_OFFSET		UL(CONFIG_PAGE_OFFSET)

#अगर_घोषित CONFIG_MMU

/*
 * TASK_SIZE - the maximum size of a user space task.
 * TASK_UNMAPPED_BASE - the lower boundary of the mmap VM area
 */
#अगर_अघोषित CONFIG_KASAN
#घोषणा TASK_SIZE		(UL(CONFIG_PAGE_OFFSET) - UL(SZ_16M))
#अन्यथा
#घोषणा TASK_SIZE		(KASAN_SHADOW_START)
#पूर्ण_अगर
#घोषणा TASK_UNMAPPED_BASE	ALIGN(TASK_SIZE / 3, SZ_16M)

/*
 * The maximum size of a 26-bit user space task.
 */
#घोषणा TASK_SIZE_26		(UL(1) << 26)

/*
 * The module space lives between the addresses given by TASK_SIZE
 * and PAGE_OFFSET - it must be within 32MB of the kernel text.
 */
#अगर_अघोषित CONFIG_THUMB2_KERNEL
#घोषणा MODULES_VADDR		(PAGE_OFFSET - SZ_16M)
#अन्यथा
/* smaller range क्रम Thumb-2 symbols relocation (2^24)*/
#घोषणा MODULES_VADDR		(PAGE_OFFSET - SZ_8M)
#पूर्ण_अगर

#अगर TASK_SIZE > MODULES_VADDR
#त्रुटि Top of user space clashes with start of module space
#पूर्ण_अगर

/*
 * The highmem pkmap भव space shares the end of the module area.
 */
#अगर_घोषित CONFIG_HIGHMEM
#घोषणा MODULES_END		(PAGE_OFFSET - PMD_SIZE)
#अन्यथा
#घोषणा MODULES_END		(PAGE_OFFSET)
#पूर्ण_अगर

/*
 * The XIP kernel माला_लो mapped at the bottom of the module vm area.
 * Since we use sections to map it, this macro replaces the physical address
 * with its भव address जबतक keeping offset from the base section.
 */
#घोषणा XIP_VIRT_ADDR(physaddr)  (MODULES_VADDR + ((physaddr) & 0x000fffff))

#घोषणा FDT_FIXED_BASE		UL(0xff800000)
#घोषणा FDT_FIXED_SIZE		(2 * SECTION_SIZE)
#घोषणा FDT_VIRT_BASE(physbase)	((व्योम *)(FDT_FIXED_BASE | (physbase) % SECTION_SIZE))

#अगर !defined(CONFIG_SMP) && !defined(CONFIG_ARM_LPAE)
/*
 * Allow 16MB-aligned ioremap pages
 */
#घोषणा IOREMAP_MAX_ORDER	24
#पूर्ण_अगर

#घोषणा VECTORS_BASE		UL(0xffff0000)

#अन्यथा /* CONFIG_MMU */

#अगर_अघोषित __ASSEMBLY__
बाह्य अचिन्हित दीर्घ setup_vectors_base(व्योम);
बाह्य अचिन्हित दीर्घ vectors_base;
#घोषणा VECTORS_BASE		vectors_base
#पूर्ण_अगर

/*
 * The limitation of user task size can grow up to the end of मुक्त ram region.
 * It is dअगरficult to define and perhaps will never meet the original meaning
 * of this define that was meant to.
 * Fortunately, there is no reference क्रम this in noMMU mode, क्रम now.
 */
#घोषणा TASK_SIZE		UL(0xffffffff)

#अगर_अघोषित TASK_UNMAPPED_BASE
#घोषणा TASK_UNMAPPED_BASE	UL(0x00000000)
#पूर्ण_अगर

#अगर_अघोषित END_MEM
#घोषणा END_MEM     		(UL(CONFIG_DRAM_BASE) + CONFIG_DRAM_SIZE)
#पूर्ण_अगर

/*
 * The module can be at any place in ram in nommu mode.
 */
#घोषणा MODULES_END		(END_MEM)
#घोषणा MODULES_VADDR		PAGE_OFFSET

#घोषणा XIP_VIRT_ADDR(physaddr)  (physaddr)
#घोषणा FDT_VIRT_BASE(physbase)  ((व्योम *)(physbase))

#पूर्ण_अगर /* !CONFIG_MMU */

#अगर_घोषित CONFIG_XIP_KERNEL
#घोषणा KERNEL_START		_sdata
#अन्यथा
#घोषणा KERNEL_START		_stext
#पूर्ण_अगर
#घोषणा KERNEL_END		_end

/*
 * We fix the TCM memories max 32 KiB ITCM resp DTCM at these
 * locations
 */
#अगर_घोषित CONFIG_HAVE_TCM
#घोषणा ITCM_OFFSET	UL(0xfffe0000)
#घोषणा DTCM_OFFSET	UL(0xfffe8000)
#पूर्ण_अगर

/*
 * Convert a page to/from a physical address
 */
#घोषणा page_to_phys(page)	(__pfn_to_phys(page_to_pfn(page)))
#घोषणा phys_to_page(phys)	(pfn_to_page(__phys_to_pfn(phys)))

/*
 * PLAT_PHYS_OFFSET is the offset (from zero) of the start of physical
 * memory.  This is used क्रम XIP and NoMMU kernels, and on platक्रमms that करोn't
 * have CONFIG_ARM_PATCH_PHYS_VIRT. Assembly code must always use
 * PLAT_PHYS_OFFSET and not PHYS_OFFSET.
 */
#घोषणा PLAT_PHYS_OFFSET	UL(CONFIG_PHYS_OFFSET)

#अगर_अघोषित __ASSEMBLY__

/*
 * Physical vs भव RAM address space conversion.  These are
 * निजी definitions which should NOT be used outside memory.h
 * files.  Use virt_to_phys/phys_to_virt/__pa/__va instead.
 *
 * PFNs are used to describe any physical page; this means
 * PFN 0 == physical address 0.
 */

#अगर defined(CONFIG_ARM_PATCH_PHYS_VIRT)

/*
 * Constants used to क्रमce the right inकाष्ठाion encodings and shअगरts
 * so that all we need to करो is modअगरy the 8-bit स्थिरant field.
 */
#घोषणा __PV_BITS_31_24	0x81000000
#घोषणा __PV_BITS_23_16	0x810000
#घोषणा __PV_BITS_7_0	0x81

बाह्य अचिन्हित दीर्घ __pv_phys_pfn_offset;
बाह्य u64 __pv_offset;
बाह्य व्योम fixup_pv_table(स्थिर व्योम *, अचिन्हित दीर्घ);
बाह्य स्थिर व्योम *__pv_table_begin, *__pv_table_end;

#घोषणा PHYS_OFFSET	((phys_addr_t)__pv_phys_pfn_offset << PAGE_SHIFT)
#घोषणा PHYS_PFN_OFFSET	(__pv_phys_pfn_offset)

#अगर_अघोषित CONFIG_THUMB2_KERNEL
#घोषणा __pv_stub(from,to,instr)			\
	__यंत्र__("@ __pv_stub\n"				\
	"1:	" instr "	%0, %1, %2\n"		\
	"2:	" instr "	%0, %0, %3\n"		\
	"	.pushsection .pv_table,\"a\"\n"		\
	"	.long	1b - ., 2b - .\n"		\
	"	.popsection\n"				\
	: "=r" (to)					\
	: "r" (from), "I" (__PV_BITS_31_24),		\
	  "I"(__PV_BITS_23_16))

#घोषणा __pv_add_carry_stub(x, y)			\
	__यंत्र__("@ __pv_add_carry_stub\n"		\
	"0:	movw	%R0, #0\n"			\
	"	adds	%Q0, %1, %R0, lsl #20\n"	\
	"1:	mov	%R0, %2\n"			\
	"	adc	%R0, %R0, #0\n"			\
	"	.pushsection .pv_table,\"a\"\n"		\
	"	.long	0b - ., 1b - .\n"		\
	"	.popsection\n"				\
	: "=&r" (y)					\
	: "r" (x), "I" (__PV_BITS_7_0)			\
	: "cc")

#अन्यथा
#घोषणा __pv_stub(from,to,instr)			\
	__यंत्र__("@ __pv_stub\n"				\
	"0:	movw	%0, #0\n"			\
	"	lsl	%0, #21\n"			\
	"	" instr " %0, %1, %0\n"			\
	"	.pushsection .pv_table,\"a\"\n"		\
	"	.long	0b - .\n"			\
	"	.popsection\n"				\
	: "=&r" (to)					\
	: "r" (from))

#घोषणा __pv_add_carry_stub(x, y)			\
	__यंत्र__("@ __pv_add_carry_stub\n"		\
	"0:	movw	%R0, #0\n"			\
	"	lsls	%R0, #21\n"			\
	"	adds	%Q0, %1, %R0\n"			\
	"1:	mvn	%R0, #0\n"			\
	"	adc	%R0, %R0, #0\n"			\
	"	.pushsection .pv_table,\"a\"\n"		\
	"	.long	0b - ., 1b - .\n"		\
	"	.popsection\n"				\
	: "=&r" (y)					\
	: "r" (x)					\
	: "cc")
#पूर्ण_अगर

अटल अंतरभूत phys_addr_t __virt_to_phys_nodebug(अचिन्हित दीर्घ x)
अणु
	phys_addr_t t;

	अगर (माप(phys_addr_t) == 4) अणु
		__pv_stub(x, t, "add");
	पूर्ण अन्यथा अणु
		__pv_add_carry_stub(x, t);
	पूर्ण
	वापस t;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ __phys_to_virt(phys_addr_t x)
अणु
	अचिन्हित दीर्घ t;

	/*
	 * 'unsigned long' cast discard upper word when
	 * phys_addr_t is 64 bit, and makes sure that अंतरभूत
	 * assembler expression receives 32 bit argument
	 * in place where 'r' 32 bit opeअक्रम is expected.
	 */
	__pv_stub((अचिन्हित दीर्घ) x, t, "sub");
	वापस t;
पूर्ण

#अन्यथा

#घोषणा PHYS_OFFSET	PLAT_PHYS_OFFSET
#घोषणा PHYS_PFN_OFFSET	((अचिन्हित दीर्घ)(PHYS_OFFSET >> PAGE_SHIFT))

अटल अंतरभूत phys_addr_t __virt_to_phys_nodebug(अचिन्हित दीर्घ x)
अणु
	वापस (phys_addr_t)x - PAGE_OFFSET + PHYS_OFFSET;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ __phys_to_virt(phys_addr_t x)
अणु
	वापस x - PHYS_OFFSET + PAGE_OFFSET;
पूर्ण

#पूर्ण_अगर

#घोषणा virt_to_pfn(kaddr) \
	((((अचिन्हित दीर्घ)(kaddr) - PAGE_OFFSET) >> PAGE_SHIFT) + \
	 PHYS_PFN_OFFSET)

#घोषणा __pa_symbol_nodebug(x)	__virt_to_phys_nodebug((x))

#अगर_घोषित CONFIG_DEBUG_VIRTUAL
बाह्य phys_addr_t __virt_to_phys(अचिन्हित दीर्घ x);
बाह्य phys_addr_t __phys_addr_symbol(अचिन्हित दीर्घ x);
#अन्यथा
#घोषणा __virt_to_phys(x)	__virt_to_phys_nodebug(x)
#घोषणा __phys_addr_symbol(x)	__pa_symbol_nodebug(x)
#पूर्ण_अगर

/*
 * These are *only* valid on the kernel direct mapped RAM memory.
 * Note: Drivers should NOT use these.  They are the wrong
 * translation क्रम translating DMA addresses.  Use the driver
 * DMA support - see dma-mapping.h.
 */
#घोषणा virt_to_phys virt_to_phys
अटल अंतरभूत phys_addr_t virt_to_phys(स्थिर अस्थिर व्योम *x)
अणु
	वापस __virt_to_phys((अचिन्हित दीर्घ)(x));
पूर्ण

#घोषणा phys_to_virt phys_to_virt
अटल अंतरभूत व्योम *phys_to_virt(phys_addr_t x)
अणु
	वापस (व्योम *)__phys_to_virt(x);
पूर्ण

/*
 * Drivers should NOT use these either.
 */
#घोषणा __pa(x)			__virt_to_phys((अचिन्हित दीर्घ)(x))
#घोषणा __pa_symbol(x)		__phys_addr_symbol(RELOC_HIDE((अचिन्हित दीर्घ)(x), 0))
#घोषणा __va(x)			((व्योम *)__phys_to_virt((phys_addr_t)(x)))
#घोषणा pfn_to_kaddr(pfn)	__va((phys_addr_t)(pfn) << PAGE_SHIFT)

बाह्य दीर्घ दीर्घ arch_phys_to_idmap_offset;

/*
 * These are क्रम प्रणालीs that have a hardware पूर्णांकerconnect supported alias
 * of physical memory क्रम idmap purposes.  Most हालs should leave these
 * untouched.  Note: this can only वापस addresses less than 4GiB.
 */
अटल अंतरभूत bool arm_has_idmap_alias(व्योम)
अणु
	वापस IS_ENABLED(CONFIG_MMU) && arch_phys_to_idmap_offset != 0;
पूर्ण

#घोषणा IDMAP_INVALID_ADDR ((u32)~0)

अटल अंतरभूत अचिन्हित दीर्घ phys_to_idmap(phys_addr_t addr)
अणु
	अगर (IS_ENABLED(CONFIG_MMU) && arch_phys_to_idmap_offset) अणु
		addr += arch_phys_to_idmap_offset;
		अगर (addr > (u32)~0)
			addr = IDMAP_INVALID_ADDR;
	पूर्ण
	वापस addr;
पूर्ण

अटल अंतरभूत phys_addr_t idmap_to_phys(अचिन्हित दीर्घ idmap)
अणु
	phys_addr_t addr = idmap;

	अगर (IS_ENABLED(CONFIG_MMU) && arch_phys_to_idmap_offset)
		addr -= arch_phys_to_idmap_offset;

	वापस addr;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ __virt_to_idmap(अचिन्हित दीर्घ x)
अणु
	वापस phys_to_idmap(__virt_to_phys(x));
पूर्ण

#घोषणा virt_to_idmap(x)	__virt_to_idmap((अचिन्हित दीर्घ)(x))

/*
 * Virtual <-> DMA view memory address translations
 * Again, these are *only* valid on the kernel direct mapped RAM
 * memory.  Use of these is *deprecated* (and that करोesn't mean
 * use the __ prefixed क्रमms instead.)  See dma-mapping.h.
 */
#अगर_अघोषित __virt_to_bus
#घोषणा __virt_to_bus	__virt_to_phys
#घोषणा __bus_to_virt	__phys_to_virt
#घोषणा __pfn_to_bus(x)	__pfn_to_phys(x)
#घोषणा __bus_to_pfn(x)	__phys_to_pfn(x)
#पूर्ण_अगर

/*
 * Conversion between a काष्ठा page and a physical address.
 *
 *  page_to_pfn(page)	convert a काष्ठा page * to a PFN number
 *  pfn_to_page(pfn)	convert a _valid_ PFN number to काष्ठा page *
 *
 *  virt_to_page(k)	convert a _valid_ भव address to काष्ठा page *
 *  virt_addr_valid(k)	indicates whether a भव address is valid
 */
#घोषणा ARCH_PFN_OFFSET		PHYS_PFN_OFFSET

#घोषणा virt_to_page(kaddr)	pfn_to_page(virt_to_pfn(kaddr))
#घोषणा virt_addr_valid(kaddr)	(((अचिन्हित दीर्घ)(kaddr) >= PAGE_OFFSET && (अचिन्हित दीर्घ)(kaddr) < (अचिन्हित दीर्घ)high_memory) \
					&& pfn_valid(virt_to_pfn(kaddr)))

#पूर्ण_अगर

#समावेश <यंत्र-generic/memory_model.h>

#पूर्ण_अगर
