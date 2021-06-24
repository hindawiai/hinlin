<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_POWERPC_TASK_SIZE_64_H
#घोषणा _ASM_POWERPC_TASK_SIZE_64_H

/*
 * 64-bit user address space can have multiple limits
 * For now supported values are:
 */
#घोषणा TASK_SIZE_64TB  (0x0000400000000000UL)
#घोषणा TASK_SIZE_128TB (0x0000800000000000UL)
#घोषणा TASK_SIZE_512TB (0x0002000000000000UL)
#घोषणा TASK_SIZE_1PB   (0x0004000000000000UL)
#घोषणा TASK_SIZE_2PB   (0x0008000000000000UL)

/*
 * With 52 bits in the address we can support up to 4PB of range.
 */
#घोषणा TASK_SIZE_4PB   (0x0010000000000000UL)

/*
 * For now 512TB is only supported with book3s and 64K linux page size.
 */
#अगर_घोषित CONFIG_PPC_64K_PAGES
/*
 * Max value currently used:
 */
#घोषणा TASK_SIZE_USER64		TASK_SIZE_4PB
#घोषणा DEFAULT_MAP_WINDOW_USER64	TASK_SIZE_128TB
#घोषणा TASK_CONTEXT_SIZE		TASK_SIZE_512TB
#अन्यथा
#घोषणा TASK_SIZE_USER64		TASK_SIZE_64TB
#घोषणा DEFAULT_MAP_WINDOW_USER64	TASK_SIZE_64TB

/*
 * We करोn't need to allocate extended context ids क्रम 4K page size, because we
 * limit the max effective address on this config to 64TB.
 */
#घोषणा TASK_CONTEXT_SIZE TASK_SIZE_64TB
#पूर्ण_अगर

/*
 * 32-bit user address space is 4GB - 1 page
 * (this 1 page is needed so referencing of 0xFFFFFFFF generates EFAULT
 */
#घोषणा TASK_SIZE_USER32 (0x0000000100000000UL - (1 * PAGE_SIZE))

#घोषणा TASK_SIZE_OF(tsk)						\
	(test_tsk_thपढ़ो_flag(tsk, TIF_32BIT) ? TASK_SIZE_USER32 :	\
						TASK_SIZE_USER64)

#घोषणा TASK_SIZE TASK_SIZE_OF(current)

#घोषणा TASK_UNMAPPED_BASE_USER32 (PAGE_ALIGN(TASK_SIZE_USER32 / 4))
#घोषणा TASK_UNMAPPED_BASE_USER64 (PAGE_ALIGN(DEFAULT_MAP_WINDOW_USER64 / 4))

/*
 * This decides where the kernel will search क्रम a मुक्त chunk of vm space during
 * mmap's.
 */
#घोषणा TASK_UNMAPPED_BASE	\
	((is_32bit_task()) ? TASK_UNMAPPED_BASE_USER32 : TASK_UNMAPPED_BASE_USER64)

/*
 * Initial task size value क्रम user applications. For book3s 64 we start
 * with 128TB and conditionally enable upto 512TB
 */
#अगर_घोषित CONFIG_PPC_BOOK3S_64
#घोषणा DEFAULT_MAP_WINDOW	\
	((is_32bit_task()) ? TASK_SIZE_USER32 : DEFAULT_MAP_WINDOW_USER64)
#अन्यथा
#घोषणा DEFAULT_MAP_WINDOW	TASK_SIZE
#पूर्ण_अगर

#घोषणा STACK_TOP_USER64 DEFAULT_MAP_WINDOW_USER64
#घोषणा STACK_TOP_USER32 TASK_SIZE_USER32
#घोषणा STACK_TOP_MAX TASK_SIZE_USER64
#घोषणा STACK_TOP (is_32bit_task() ? STACK_TOP_USER32 : STACK_TOP_USER64)

#पूर्ण_अगर /* _ASM_POWERPC_TASK_SIZE_64_H */
