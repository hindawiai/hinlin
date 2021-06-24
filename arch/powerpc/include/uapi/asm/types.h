<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
 * This file is never included by application software unless
 * explicitly requested (e.g., via linux/types.h) in which हाल the
 * application is Linux specअगरic so (user-) name space pollution is
 * not a major issue.  However, क्रम पूर्णांकeroperability, libraries still
 * need to be careful to aव्योम a name clashes.
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */
#अगर_अघोषित _UAPI_ASM_POWERPC_TYPES_H
#घोषणा _UAPI_ASM_POWERPC_TYPES_H

/*
 * This is here because we used to use l64 क्रम 64bit घातerpc
 * and we करोn't want to impact user mode with our change to ll64
 * in the kernel.
 *
 * However, some user programs are fine with this.  They can
 * flag __SANE_USERSPACE_TYPES__ to get पूर्णांक-ll64.h here.
 */
#अगर !defined(__SANE_USERSPACE_TYPES__) && defined(__घातerpc64__) && !defined(__KERNEL__)
# include <यंत्र-generic/पूर्णांक-l64.h>
#अन्यथा
# include <यंत्र-generic/पूर्णांक-ll64.h>
#पूर्ण_अगर

#अगर_अघोषित __ASSEMBLY__


प्रकार काष्ठा अणु
	__u32 u[4];
पूर्ण __attribute__((aligned(16))) __vector128;

#पूर्ण_अगर /* __ASSEMBLY__ */


#पूर्ण_अगर /* _UAPI_ASM_POWERPC_TYPES_H */
