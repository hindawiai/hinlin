<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_PAGE_64_DEFS_H
#घोषणा _ASM_X86_PAGE_64_DEFS_H

#अगर_अघोषित __ASSEMBLY__
#समावेश <यंत्र/kaslr.h>
#पूर्ण_अगर

#अगर_घोषित CONFIG_KASAN
#घोषणा KASAN_STACK_ORDER 1
#अन्यथा
#घोषणा KASAN_STACK_ORDER 0
#पूर्ण_अगर

#घोषणा THREAD_SIZE_ORDER	(2 + KASAN_STACK_ORDER)
#घोषणा THREAD_SIZE  (PAGE_SIZE << THREAD_SIZE_ORDER)

#घोषणा EXCEPTION_STACK_ORDER (0 + KASAN_STACK_ORDER)
#घोषणा EXCEPTION_STKSZ (PAGE_SIZE << EXCEPTION_STACK_ORDER)

#घोषणा IRQ_STACK_ORDER (2 + KASAN_STACK_ORDER)
#घोषणा IRQ_STACK_SIZE (PAGE_SIZE << IRQ_STACK_ORDER)

/*
 * The index क्रम the tss.ist[] array. The hardware limit is 7 entries.
 */
#घोषणा	IST_INDEX_DF		0
#घोषणा	IST_INDEX_NMI		1
#घोषणा	IST_INDEX_DB		2
#घोषणा	IST_INDEX_MCE		3
#घोषणा	IST_INDEX_VC		4

/*
 * Set __PAGE_OFFSET to the most negative possible address +
 * PGसूची_SIZE*17 (pgd slot 273).
 *
 * The gap is to allow a space क्रम LDT remap क्रम PTI (1 pgd slot) and space क्रम
 * a hypervisor (16 slots). Choosing 16 slots क्रम a hypervisor is arbitrary,
 * but it's what Xen requires.
 */
#घोषणा __PAGE_OFFSET_BASE_L5	_AC(0xff11000000000000, UL)
#घोषणा __PAGE_OFFSET_BASE_L4	_AC(0xffff888000000000, UL)

#अगर_घोषित CONFIG_DYNAMIC_MEMORY_LAYOUT
#घोषणा __PAGE_OFFSET           page_offset_base
#अन्यथा
#घोषणा __PAGE_OFFSET           __PAGE_OFFSET_BASE_L4
#पूर्ण_अगर /* CONFIG_DYNAMIC_MEMORY_LAYOUT */

#घोषणा __START_KERNEL_map	_AC(0xffffffff80000000, UL)

/* See Documentation/x86/x86_64/mm.rst क्रम a description of the memory map. */

#घोषणा __PHYSICAL_MASK_SHIFT	52

#अगर_घोषित CONFIG_X86_5LEVEL
#घोषणा __VIRTUAL_MASK_SHIFT	(pgtable_l5_enabled() ? 56 : 47)
/* See task_size_max() in <यंत्र/page_64.h> */
#अन्यथा
#घोषणा __VIRTUAL_MASK_SHIFT	47
#घोषणा task_size_max()		((_AC(1,UL) << __VIRTUAL_MASK_SHIFT) - PAGE_SIZE)
#पूर्ण_अगर

#घोषणा TASK_SIZE_MAX		task_size_max()
#घोषणा DEFAULT_MAP_WINDOW	((1UL << 47) - PAGE_SIZE)

/* This decides where the kernel will search क्रम a मुक्त chunk of vm
 * space during mmap's.
 */
#घोषणा IA32_PAGE_OFFSET	((current->personality & ADDR_LIMIT_3GB) ? \
					0xc0000000 : 0xFFFFe000)

#घोषणा TASK_SIZE_LOW		(test_thपढ़ो_flag(TIF_ADDR32) ? \
					IA32_PAGE_OFFSET : DEFAULT_MAP_WINDOW)
#घोषणा TASK_SIZE		(test_thपढ़ो_flag(TIF_ADDR32) ? \
					IA32_PAGE_OFFSET : TASK_SIZE_MAX)
#घोषणा TASK_SIZE_OF(child)	((test_tsk_thपढ़ो_flag(child, TIF_ADDR32)) ? \
					IA32_PAGE_OFFSET : TASK_SIZE_MAX)

#घोषणा STACK_TOP		TASK_SIZE_LOW
#घोषणा STACK_TOP_MAX		TASK_SIZE_MAX

/*
 * In spite of the name, KERNEL_IMAGE_SIZE is a limit on the maximum भव
 * address क्रम the kernel image, rather than the limit on the size itself.
 * This can be at most 1 GiB, due to the fixmap living in the next 1 GiB (see
 * level2_kernel_pgt in arch/x86/kernel/head_64.S).
 *
 * On KASLR use 1 GiB by शेष, leaving 1 GiB क्रम modules once the
 * page tables are fully set up.
 *
 * If KASLR is disabled we can shrink it to 0.5 GiB and increase the size
 * of the modules area to 1.5 GiB.
 */
#अगर_घोषित CONFIG_RANDOMIZE_BASE
#घोषणा KERNEL_IMAGE_SIZE	(1024 * 1024 * 1024)
#अन्यथा
#घोषणा KERNEL_IMAGE_SIZE	(512 * 1024 * 1024)
#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_X86_PAGE_64_DEFS_H */
