<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_PAGE_32_DEFS_H
#घोषणा _ASM_X86_PAGE_32_DEFS_H

#समावेश <linux/स्थिर.h>

/*
 * This handles the memory map.
 *
 * A __PAGE_OFFSET of 0xC0000000 means that the kernel has
 * a भव address space of one gigabyte, which limits the
 * amount of physical memory you can use to about 950MB.
 *
 * If you want more physical memory than this then see the CONFIG_HIGHMEM4G
 * and CONFIG_HIGHMEM64G options in the kernel configuration.
 */
#घोषणा __PAGE_OFFSET_BASE	_AC(CONFIG_PAGE_OFFSET, UL)
#घोषणा __PAGE_OFFSET		__PAGE_OFFSET_BASE

#घोषणा __START_KERNEL_map	__PAGE_OFFSET

#घोषणा THREAD_SIZE_ORDER	1
#घोषणा THREAD_SIZE		(PAGE_SIZE << THREAD_SIZE_ORDER)

#घोषणा IRQ_STACK_SIZE		THREAD_SIZE

#घोषणा N_EXCEPTION_STACKS	1

#अगर_घोषित CONFIG_X86_PAE
/*
 * This is beyond the 44 bit limit imposed by the 32bit दीर्घ pfns,
 * but we need the full mask to make sure inverted PROT_NONE
 * entries have all the host bits set in a guest.
 * The real limit is still 44 bits.
 */
#घोषणा __PHYSICAL_MASK_SHIFT	52
#घोषणा __VIRTUAL_MASK_SHIFT	32

#अन्यथा  /* !CONFIG_X86_PAE */
#घोषणा __PHYSICAL_MASK_SHIFT	32
#घोषणा __VIRTUAL_MASK_SHIFT	32
#पूर्ण_अगर	/* CONFIG_X86_PAE */

/*
 * User space process size: 3GB (शेष).
 */
#घोषणा IA32_PAGE_OFFSET	__PAGE_OFFSET
#घोषणा TASK_SIZE		__PAGE_OFFSET
#घोषणा TASK_SIZE_LOW		TASK_SIZE
#घोषणा TASK_SIZE_MAX		TASK_SIZE
#घोषणा DEFAULT_MAP_WINDOW	TASK_SIZE
#घोषणा STACK_TOP		TASK_SIZE
#घोषणा STACK_TOP_MAX		STACK_TOP

/*
 * In spite of the name, KERNEL_IMAGE_SIZE is a limit on the maximum भव
 * address क्रम the kernel image, rather than the limit on the size itself. On
 * 32-bit, this is not a strict limit, but this value is used to limit the
 * link-समय भव address range of the kernel, and by KASLR to limit the
 * अक्रमomized address from which the kernel is executed. A relocatable kernel
 * can be loaded somewhat higher than KERNEL_IMAGE_SIZE as दीर्घ as enough space
 * reमुख्यs क्रम the vदो_स्मृति area.
 */
#घोषणा KERNEL_IMAGE_SIZE	(512 * 1024 * 1024)

#अगर_अघोषित __ASSEMBLY__

/*
 * This much address space is reserved क्रम vदो_स्मृति() and iomap()
 * as well as fixmap mappings.
 */
बाह्य अचिन्हित पूर्णांक __VMALLOC_RESERVE;
बाह्य पूर्णांक sysctl_legacy_va_layout;

बाह्य व्योम find_low_pfn_range(व्योम);
बाह्य व्योम setup_booपंचांगem_allocator(व्योम);

#पूर्ण_अगर	/* !__ASSEMBLY__ */

#पूर्ण_अगर /* _ASM_X86_PAGE_32_DEFS_H */
