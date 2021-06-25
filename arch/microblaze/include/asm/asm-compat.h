<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_MICROBLAZE_ASM_COMPAT_H
#घोषणा _ASM_MICROBLAZE_ASM_COMPAT_H

#समावेश <यंत्र/types.h>

#अगर_घोषित __ASSEMBLY__
#  define stringअगरy_in_c(...)	__VA_ARGS__
#  define ASM_CONST(x)		x
#अन्यथा
/* This version of stringअगरy will deal with commas... */
#  define __stringअगरy_in_c(...)	#__VA_ARGS__
#  define stringअगरy_in_c(...)	__stringअगरy_in_c(__VA_ARGS__) " "
#  define __ASM_CONST(x)	x##UL
#  define ASM_CONST(x)		__ASM_CONST(x)
#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_MICROBLAZE_ASM_COMPAT_H */
