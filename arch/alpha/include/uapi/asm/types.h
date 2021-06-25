<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_ALPHA_TYPES_H
#घोषणा _UAPI_ALPHA_TYPES_H

/*
 * This file is never included by application software unless
 * explicitly requested (e.g., via linux/types.h) in which हाल the
 * application is Linux specअगरic so (user-) name space pollution is
 * not a major issue.  However, क्रम पूर्णांकeroperability, libraries still
 * need to be careful to aव्योम a name clashes.
 */

/*
 * This is here because we used to use l64 क्रम alpha
 * and we करोn't want to impact user mode with our change to ll64
 * in the kernel.
 *
 * However, some user programs are fine with this.  They can
 * flag __SANE_USERSPACE_TYPES__ to get पूर्णांक-ll64.h here.
 */
#अगर !defined(__SANE_USERSPACE_TYPES__) && !defined(__KERNEL__)
#समावेश <यंत्र-generic/पूर्णांक-l64.h>
#अन्यथा
#समावेश <यंत्र-generic/पूर्णांक-ll64.h>
#पूर्ण_अगर

#पूर्ण_अगर /* _UAPI_ALPHA_TYPES_H */
