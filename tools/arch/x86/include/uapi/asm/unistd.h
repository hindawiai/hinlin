<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_ASM_X86_UNISTD_H
#घोषणा _UAPI_ASM_X86_UNISTD_H

/*
 * x32 syscall flag bit.  Some user programs expect syscall NR macros
 * and __X32_SYSCALL_BIT to have type पूर्णांक, even though syscall numbers
 * are, क्रम practical purposes, अचिन्हित दीर्घ.
 *
 * Fortunately, expressions like (nr & ~__X32_SYSCALL_BIT) करो the right
 * thing regardless.
 */
#घोषणा __X32_SYSCALL_BIT	0x40000000

#अगर_अघोषित __KERNEL__
# अगरdef __i386__
#  include <यंत्र/unistd_32.h>
# elअगर defined(__ILP32__)
#  include <यंत्र/unistd_x32.h>
# अन्यथा
#  include <यंत्र/unistd_64.h>
# endअगर
#पूर्ण_अगर

#पूर्ण_अगर /* _UAPI_ASM_X86_UNISTD_H */
