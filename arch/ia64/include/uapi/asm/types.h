<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * This file is never included by application software unless explicitly
 * requested (e.g., via linux/types.h) in which हाल the application is
 * Linux specअगरic so (user-) name space pollution is not a major issue.
 * However, क्रम पूर्णांकeroperability, libraries still need to be careful to
 * aव्योम naming clashes.
 *
 * Based on <यंत्र-alpha/types.h>.
 *
 * Modअगरied 1998-2000, 2002
 *	David Mosberger-Tang <davidm@hpl.hp.com>, Hewlett-Packard Co
 */
#अगर_अघोषित _UAPI_ASM_IA64_TYPES_H
#घोषणा _UAPI_ASM_IA64_TYPES_H


#अगर_अघोषित __KERNEL__
#समावेश <यंत्र-generic/पूर्णांक-l64.h>
#पूर्ण_अगर

#अगर_घोषित __ASSEMBLY__
# define __IA64_UL(x)		(x)
# define __IA64_UL_CONST(x)	x

#अन्यथा
# define __IA64_UL(x)		((अचिन्हित दीर्घ)(x))
# define __IA64_UL_CONST(x)	x##UL

#पूर्ण_अगर /* !__ASSEMBLY__ */

#पूर्ण_अगर /* _UAPI_ASM_IA64_TYPES_H */
