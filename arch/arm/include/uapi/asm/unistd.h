<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 *  arch/arm/include/यंत्र/unistd.h
 *
 *  Copyright (C) 2001-2005 Russell King
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * Please क्रमward _all_ changes to this file to rmk@arm.linux.org.uk,
 * no matter what the change is.  Thanks!
 */
#अगर_अघोषित _UAPI__ASM_ARM_UNISTD_H
#घोषणा _UAPI__ASM_ARM_UNISTD_H

#घोषणा __NR_OABI_SYSCALL_BASE	0x900000

#अगर defined(__thumb__) || defined(__ARM_EABI__)
#घोषणा __NR_SYSCALL_BASE	0
#समावेश <यंत्र/unistd-eabi.h>
#अन्यथा
#घोषणा __NR_SYSCALL_BASE	__NR_OABI_SYSCALL_BASE
#समावेश <यंत्र/unistd-oabi.h>
#पूर्ण_अगर

#घोषणा __NR_sync_file_range2		__NR_arm_sync_file_range

/*
 * The following SWIs are ARM निजी.
 */
#घोषणा __ARM_NR_BASE			(__NR_SYSCALL_BASE+0x0f0000)
#घोषणा __ARM_NR_अवरोधpoपूर्णांक		(__ARM_NR_BASE+1)
#घोषणा __ARM_NR_cacheflush		(__ARM_NR_BASE+2)
#घोषणा __ARM_NR_usr26			(__ARM_NR_BASE+3)
#घोषणा __ARM_NR_usr32			(__ARM_NR_BASE+4)
#घोषणा __ARM_NR_set_tls		(__ARM_NR_BASE+5)
#घोषणा __ARM_NR_get_tls		(__ARM_NR_BASE+6)

#पूर्ण_अगर /* _UAPI__ASM_ARM_UNISTD_H */
