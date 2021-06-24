<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Based on arch/arm/include/यंत्र/memory.h
 *
 * Copyright (C) 2000-2002 Russell King
 * Copyright (C) 2012 ARM Ltd.
 *
 * Note: this file should not be included by non-यंत्र/.h files
 */
#अगर_अघोषित __ASM_MEMORY_H
#घोषणा __ASM_MEMORY_H

#समावेश <linux/स्थिर.h>
#समावेश <linux/sizes.h>
#समावेश <यंत्र/page-def.h>

/*
 * Size of the PCI I/O space. This must reमुख्य a घातer of two so that
 * IO_SPACE_LIMIT acts as a mask क्रम the low bits of I/O addresses.
 */
#घोषणा PCI_IO_SIZE		SZ_16M

/*
 * VMEMMAP_SIZE - allows the whole linear region to be covered by
 *                a काष्ठा page array
 *
 * If we are configured with a 52-bit kernel VA then our VMEMMAP_SIZE
 * needs to cover the memory region from the beginning of the 52-bit
 * PAGE_OFFSET all the way to PAGE_END क्रम 48-bit. This allows us to
 * keep a स्थिरant PAGE_OFFSET and "fallback" to using the higher end
 * of the VMEMMAP where 52-bit support is not available in hardware.
 */
#घोषणा VMEMMAP_SHIFT	(PAGE_SHIFT - STRUCT_PAGE_MAX_SHIFT)
#घोषणा VMEMMAP_SIZE	((_PAGE_END(VA_BITS_MIN) - PAGE_OFFSET) >> VMEMMAP_SHIFT)

/*
 * PAGE_OFFSET - the भव address of the start of the linear map, at the
 *               start of the TTBR1 address space.
 * PAGE_END - the end of the linear map, where all other kernel mappings begin.
 * KIMAGE_VADDR - the भव address of the start of the kernel image.
 * VA_BITS - the maximum number of bits क्रम भव addresses.
 */
#घोषणा VA_BITS			(CONFIG_ARM64_VA_BITS)
#घोषणा _PAGE_OFFSET(va)	(-(UL(1) << (va)))
#घोषणा PAGE_OFFSET		(_PAGE_OFFSET(VA_BITS))
#घोषणा KIMAGE_VADDR		(MODULES_END)
#घोषणा BPF_JIT_REGION_START	(_PAGE_END(VA_BITS_MIN))
#घोषणा BPF_JIT_REGION_SIZE	(SZ_128M)
#घोषणा BPF_JIT_REGION_END	(BPF_JIT_REGION_START + BPF_JIT_REGION_SIZE)
#घोषणा MODULES_END		(MODULES_VADDR + MODULES_VSIZE)
#घोषणा MODULES_VADDR		(BPF_JIT_REGION_END)
#घोषणा MODULES_VSIZE		(SZ_128M)
#घोषणा VMEMMAP_START		(-(UL(1) << (VA_BITS - VMEMMAP_SHIFT)))
#घोषणा VMEMMAP_END		(VMEMMAP_START + VMEMMAP_SIZE)
#घोषणा PCI_IO_END		(VMEMMAP_START - SZ_8M)
#घोषणा PCI_IO_START		(PCI_IO_END - PCI_IO_SIZE)
#घोषणा FIXADDR_TOP		(VMEMMAP_START - SZ_32M)

#अगर VA_BITS > 48
#घोषणा VA_BITS_MIN		(48)
#अन्यथा
#घोषणा VA_BITS_MIN		(VA_BITS)
#पूर्ण_अगर

#घोषणा _PAGE_END(va)		(-(UL(1) << ((va) - 1)))

#घोषणा KERNEL_START		_text
#घोषणा KERNEL_END		_end

/*
 * Generic and tag-based KASAN require 1/8th and 1/16th of the kernel भव
 * address space क्रम the shaकरोw region respectively. They can bloat the stack
 * signअगरicantly, so द्विगुन the (minimum) stack size when they are in use.
 */
#अगर defined(CONFIG_KASAN_GENERIC) || defined(CONFIG_KASAN_SW_TAGS)
#घोषणा KASAN_SHADOW_OFFSET	_AC(CONFIG_KASAN_SHADOW_OFFSET, UL)
#घोषणा KASAN_SHADOW_END	((UL(1) << (64 - KASAN_SHADOW_SCALE_SHIFT)) \
					+ KASAN_SHADOW_OFFSET)
#घोषणा PAGE_END		(KASAN_SHADOW_END - (1UL << (vabits_actual - KASAN_SHADOW_SCALE_SHIFT)))
#घोषणा KASAN_THREAD_SHIFT	1
#अन्यथा
#घोषणा KASAN_THREAD_SHIFT	0
#घोषणा PAGE_END		(_PAGE_END(VA_BITS_MIN))
#पूर्ण_अगर /* CONFIG_KASAN */

#घोषणा MIN_THREAD_SHIFT	(14 + KASAN_THREAD_SHIFT)

/*
 * VMAP'd stacks are allocated at page granularity, so we must ensure that such
 * stacks are a multiple of page size.
 */
#अगर defined(CONFIG_VMAP_STACK) && (MIN_THREAD_SHIFT < PAGE_SHIFT)
#घोषणा THREAD_SHIFT		PAGE_SHIFT
#अन्यथा
#घोषणा THREAD_SHIFT		MIN_THREAD_SHIFT
#पूर्ण_अगर

#अगर THREAD_SHIFT >= PAGE_SHIFT
#घोषणा THREAD_SIZE_ORDER	(THREAD_SHIFT - PAGE_SHIFT)
#पूर्ण_अगर

#घोषणा THREAD_SIZE		(UL(1) << THREAD_SHIFT)

/*
 * By aligning VMAP'd stacks to 2 * THREAD_SIZE, we can detect overflow by
 * checking sp & (1 << THREAD_SHIFT), which we can करो cheaply in the entry
 * assembly.
 */
#अगर_घोषित CONFIG_VMAP_STACK
#घोषणा THREAD_ALIGN		(2 * THREAD_SIZE)
#अन्यथा
#घोषणा THREAD_ALIGN		THREAD_SIZE
#पूर्ण_अगर

#घोषणा IRQ_STACK_SIZE		THREAD_SIZE

#घोषणा OVERFLOW_STACK_SIZE	SZ_4K

/*
 * Alignment of kernel segments (e.g. .text, .data).
 *
 *  4 KB granule:  16 level 3 entries, with contiguous bit
 * 16 KB granule:   4 level 3 entries, without contiguous bit
 * 64 KB granule:   1 level 3 entry
 */
#घोषणा SEGMENT_ALIGN		SZ_64K

/*
 * Memory types available.
 *
 * IMPORTANT: MT_NORMAL must be index 0 since vm_get_page_prot() may 'or' in
 *	      the MT_NORMAL_TAGGED memory type क्रम PROT_MTE mappings. Note
 *	      that protection_map[] only contains MT_NORMAL attributes.
 */
#घोषणा MT_NORMAL		0
#घोषणा MT_NORMAL_TAGGED	1
#घोषणा MT_NORMAL_NC		2
#घोषणा MT_NORMAL_WT		3
#घोषणा MT_DEVICE_nGnRnE	4
#घोषणा MT_DEVICE_nGnRE		5
#घोषणा MT_DEVICE_GRE		6

/*
 * Memory types क्रम Stage-2 translation
 */
#घोषणा MT_S2_NORMAL		0xf
#घोषणा MT_S2_DEVICE_nGnRE	0x1

/*
 * Memory types क्रम Stage-2 translation when ID_AA64MMFR2_EL1.FWB is 0001
 * Stage-2 enक्रमces Normal-WB and Device-nGnRE
 */
#घोषणा MT_S2_FWB_NORMAL	6
#घोषणा MT_S2_FWB_DEVICE_nGnRE	1

#अगर_घोषित CONFIG_ARM64_4K_PAGES
#घोषणा IOREMAP_MAX_ORDER	(PUD_SHIFT)
#अन्यथा
#घोषणा IOREMAP_MAX_ORDER	(PMD_SHIFT)
#पूर्ण_अगर

/*
 *  Open-coded (swapper_pg_dir - reserved_pg_dir) as this cannot be calculated
 *  until link समय.
 */
#घोषणा RESERVED_SWAPPER_OFFSET	(PAGE_SIZE)

/*
 *  Open-coded (swapper_pg_dir - tramp_pg_dir) as this cannot be calculated
 *  until link समय.
 */
#घोषणा TRAMP_SWAPPER_OFFSET	(2 * PAGE_SIZE)

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/bitops.h>
#समावेश <linux/compiler.h>
#समावेश <linux/mmdebug.h>
#समावेश <linux/types.h>
#समावेश <यंत्र/bug.h>

बाह्य u64			vabits_actual;

बाह्य s64			memstart_addr;
/* PHYS_OFFSET - the physical address of the start of memory. */
#घोषणा PHYS_OFFSET		(अणु VM_BUG_ON(memstart_addr & 1); memstart_addr; पूर्ण)

/* the भव base of the kernel image */
बाह्य u64			kimage_vaddr;

/* the offset between the kernel भव and physical mappings */
बाह्य u64			kimage_voffset;

अटल अंतरभूत अचिन्हित दीर्घ kaslr_offset(व्योम)
अणु
	वापस kimage_vaddr - KIMAGE_VADDR;
पूर्ण

/*
 * Allow all memory at the discovery stage. We will clip it later.
 */
#घोषणा MIN_MEMBLOCK_ADDR	0
#घोषणा MAX_MEMBLOCK_ADDR	U64_MAX

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
 * When dealing with data पातs, watchpoपूर्णांकs, or inकाष्ठाion traps we may end
 * up with a tagged userland poपूर्णांकer. Clear the tag to get a sane poपूर्णांकer to
 * pass on to access_ok(), क्रम instance.
 */
#घोषणा __untagged_addr(addr)	\
	((__क्रमce __typeof__(addr))sign_extend64((__क्रमce u64)(addr), 55))

#घोषणा untagged_addr(addr)	(अणु					\
	u64 __addr = (__क्रमce u64)(addr);					\
	__addr &= __untagged_addr(__addr);				\
	(__क्रमce __typeof__(addr))__addr;				\
पूर्ण)

#अगर defined(CONFIG_KASAN_SW_TAGS) || defined(CONFIG_KASAN_HW_TAGS)
#घोषणा __tag_shअगरted(tag)	((u64)(tag) << 56)
#घोषणा __tag_reset(addr)	__untagged_addr(addr)
#घोषणा __tag_get(addr)		(__u8)((u64)(addr) >> 56)
#अन्यथा
#घोषणा __tag_shअगरted(tag)	0UL
#घोषणा __tag_reset(addr)	(addr)
#घोषणा __tag_get(addr)		0
#पूर्ण_अगर /* CONFIG_KASAN_SW_TAGS || CONFIG_KASAN_HW_TAGS */

अटल अंतरभूत स्थिर व्योम *__tag_set(स्थिर व्योम *addr, u8 tag)
अणु
	u64 __addr = (u64)addr & ~__tag_shअगरted(0xff);
	वापस (स्थिर व्योम *)(__addr | __tag_shअगरted(tag));
पूर्ण

#अगर_घोषित CONFIG_KASAN_HW_TAGS
#घोषणा arch_enable_tagging_sync()		mte_enable_kernel_sync()
#घोषणा arch_enable_tagging_async()		mte_enable_kernel_async()
#घोषणा arch_set_tagging_report_once(state)	mte_set_report_once(state)
#घोषणा arch_क्रमce_async_tag_fault()		mte_check_tfsr_निकास()
#घोषणा arch_init_tags(max_tag)			mte_init_tags(max_tag)
#घोषणा arch_get_अक्रमom_tag()			mte_get_अक्रमom_tag()
#घोषणा arch_get_mem_tag(addr)			mte_get_mem_tag(addr)
#घोषणा arch_set_mem_tag_range(addr, size, tag, init)	\
			mte_set_mem_tag_range((addr), (size), (tag), (init))
#पूर्ण_अगर /* CONFIG_KASAN_HW_TAGS */

/*
 * Physical vs भव RAM address space conversion.  These are
 * निजी definitions which should NOT be used outside memory.h
 * files.  Use virt_to_phys/phys_to_virt/__pa/__va instead.
 */


/*
 * Check whether an arbitrary address is within the linear map, which
 * lives in the [PAGE_OFFSET, PAGE_END) पूर्णांकerval at the bottom of the
 * kernel's TTBR1 address range.
 */
#घोषणा __is_lm_address(addr)	(((u64)(addr) - PAGE_OFFSET) < (PAGE_END - PAGE_OFFSET))

#घोषणा __lm_to_phys(addr)	(((addr) - PAGE_OFFSET) + PHYS_OFFSET)
#घोषणा __kimg_to_phys(addr)	((addr) - kimage_voffset)

#घोषणा __virt_to_phys_nodebug(x) (अणु					\
	phys_addr_t __x = (phys_addr_t)(__tag_reset(x));		\
	__is_lm_address(__x) ? __lm_to_phys(__x) : __kimg_to_phys(__x);	\
पूर्ण)

#घोषणा __pa_symbol_nodebug(x)	__kimg_to_phys((phys_addr_t)(x))

#अगर_घोषित CONFIG_DEBUG_VIRTUAL
बाह्य phys_addr_t __virt_to_phys(अचिन्हित दीर्घ x);
बाह्य phys_addr_t __phys_addr_symbol(अचिन्हित दीर्घ x);
#अन्यथा
#घोषणा __virt_to_phys(x)	__virt_to_phys_nodebug(x)
#घोषणा __phys_addr_symbol(x)	__pa_symbol_nodebug(x)
#पूर्ण_अगर /* CONFIG_DEBUG_VIRTUAL */

#घोषणा __phys_to_virt(x)	((अचिन्हित दीर्घ)((x) - PHYS_OFFSET) | PAGE_OFFSET)
#घोषणा __phys_to_kimg(x)	((अचिन्हित दीर्घ)((x) + kimage_voffset))

/*
 * Convert a page to/from a physical address
 */
#घोषणा page_to_phys(page)	(__pfn_to_phys(page_to_pfn(page)))
#घोषणा phys_to_page(phys)	(pfn_to_page(__phys_to_pfn(phys)))

/*
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
	वापस (व्योम *)(__phys_to_virt(x));
पूर्ण

/*
 * Drivers should NOT use these either.
 */
#घोषणा __pa(x)			__virt_to_phys((अचिन्हित दीर्घ)(x))
#घोषणा __pa_symbol(x)		__phys_addr_symbol(RELOC_HIDE((अचिन्हित दीर्घ)(x), 0))
#घोषणा __pa_nodebug(x)		__virt_to_phys_nodebug((अचिन्हित दीर्घ)(x))
#घोषणा __va(x)			((व्योम *)__phys_to_virt((phys_addr_t)(x)))
#घोषणा pfn_to_kaddr(pfn)	__va((pfn) << PAGE_SHIFT)
#घोषणा virt_to_pfn(x)		__phys_to_pfn(__virt_to_phys((अचिन्हित दीर्घ)(x)))
#घोषणा sym_to_pfn(x)		__phys_to_pfn(__pa_symbol(x))

#अगर_घोषित CONFIG_CFI_CLANG
/*
 * With CONFIG_CFI_CLANG, the compiler replaces function address
 * references with the address of the function's CFI jump table
 * entry. The function_nocfi macro always वापसs the address of the
 * actual function instead.
 */
#घोषणा function_nocfi(x) (अणु						\
	व्योम *addr;							\
	यंत्र("adrp %0, " __stringअगरy(x) "\n\t"				\
	    "add  %0, %0, :lo12:" __stringअगरy(x)			\
	    : "=r" (addr));						\
	addr;								\
पूर्ण)
#पूर्ण_अगर

/*
 *  virt_to_page(x)	convert a _valid_ भव address to काष्ठा page *
 *  virt_addr_valid(x)	indicates whether a भव address is valid
 */
#घोषणा ARCH_PFN_OFFSET		((अचिन्हित दीर्घ)PHYS_PFN_OFFSET)

#अगर defined(CONFIG_DEBUG_VIRTUAL)
#घोषणा page_to_virt(x)	(अणु						\
	__typeof__(x) __page = x;					\
	व्योम *__addr = __va(page_to_phys(__page));			\
	(व्योम *)__tag_set((स्थिर व्योम *)__addr, page_kasan_tag(__page));\
पूर्ण)
#घोषणा virt_to_page(x)		pfn_to_page(virt_to_pfn(x))
#अन्यथा
#घोषणा page_to_virt(x)	(अणु						\
	__typeof__(x) __page = x;					\
	u64 __idx = ((u64)__page - VMEMMAP_START) / माप(काष्ठा page);\
	u64 __addr = PAGE_OFFSET + (__idx * PAGE_SIZE);			\
	(व्योम *)__tag_set((स्थिर व्योम *)__addr, page_kasan_tag(__page));\
पूर्ण)

#घोषणा virt_to_page(x)	(अणु						\
	u64 __idx = (__tag_reset((u64)x) - PAGE_OFFSET) / PAGE_SIZE;	\
	u64 __addr = VMEMMAP_START + (__idx * माप(काष्ठा page));	\
	(काष्ठा page *)__addr;						\
पूर्ण)
#पूर्ण_अगर /* CONFIG_DEBUG_VIRTUAL */

#घोषणा virt_addr_valid(addr)	(अणु					\
	__typeof__(addr) __addr = __tag_reset(addr);			\
	__is_lm_address(__addr) && pfn_valid(virt_to_pfn(__addr));	\
पूर्ण)

व्योम dump_mem_limit(व्योम);
#पूर्ण_अगर /* !ASSEMBLY */

/*
 * Given that the GIC architecture permits ITS implementations that can only be
 * configured with a LPI table address once, GICv3 प्रणालीs with many CPUs may
 * end up reserving a lot of dअगरferent regions after a kexec क्रम their LPI
 * tables (one per CPU), as we are क्रमced to reuse the same memory after kexec
 * (and thus reserve it persistently with EFI beक्रमehand)
 */
#अगर defined(CONFIG_EFI) && defined(CONFIG_ARM_GIC_V3_ITS)
# define INIT_MEMBLOCK_RESERVED_REGIONS	(INIT_MEMBLOCK_REGIONS + NR_CPUS + 1)
#पूर्ण_अगर

#समावेश <यंत्र-generic/memory_model.h>

#पूर्ण_अगर /* __ASM_MEMORY_H */
