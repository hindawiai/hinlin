<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_POWERPC_TASK_SIZE_32_H
#घोषणा _ASM_POWERPC_TASK_SIZE_32_H

#अगर CONFIG_TASK_SIZE > CONFIG_KERNEL_START
#त्रुटि User TASK_SIZE overlaps with KERNEL_START address
#पूर्ण_अगर

#घोषणा TASK_SIZE (CONFIG_TASK_SIZE)

/*
 * This decides where the kernel will search क्रम a मुक्त chunk of vm space during
 * mmap's.
 */
#घोषणा TASK_UNMAPPED_BASE (TASK_SIZE / 8 * 3)

#घोषणा DEFAULT_MAP_WINDOW TASK_SIZE
#घोषणा STACK_TOP TASK_SIZE
#घोषणा STACK_TOP_MAX STACK_TOP

#पूर्ण_अगर /* _ASM_POWERPC_TASK_SIZE_32_H */
