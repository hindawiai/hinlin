<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _TOOLS_LINUX_ASM_X86_RMWcc
#घोषणा _TOOLS_LINUX_ASM_X86_RMWcc

#अगर_घोषित CONFIG_CC_HAS_ASM_GOTO

#घोषणा __GEN_RMWcc(fullop, var, cc, ...)				\
करो अणु									\
	यंत्र_अस्थिर_जाओ (fullop "; j" cc " %l[cc_label]"		\
			: : "m" (var), ## __VA_ARGS__ 			\
			: "memory" : cc_label);				\
	वापस 0;							\
cc_label:								\
	वापस 1;							\
पूर्ण जबतक (0)

#घोषणा GEN_UNARY_RMWcc(op, var, arg0, cc) 				\
	__GEN_RMWcc(op " " arg0, var, cc)

#घोषणा GEN_BINARY_RMWcc(op, var, vcon, val, arg0, cc)			\
	__GEN_RMWcc(op " %1, " arg0, var, cc, vcon (val))

#अन्यथा /* !CONFIG_CC_HAS_ASM_GOTO */

#घोषणा __GEN_RMWcc(fullop, var, cc, ...)				\
करो अणु									\
	अक्षर c;								\
	यंत्र अस्थिर (fullop "; set" cc " %1"				\
			: "+m" (var), "=qm" (c)				\
			: __VA_ARGS__ : "memory");			\
	वापस c != 0;							\
पूर्ण जबतक (0)

#घोषणा GEN_UNARY_RMWcc(op, var, arg0, cc)				\
	__GEN_RMWcc(op " " arg0, var, cc)

#घोषणा GEN_BINARY_RMWcc(op, var, vcon, val, arg0, cc)			\
	__GEN_RMWcc(op " %2, " arg0, var, cc, vcon (val))

#पूर्ण_अगर /* CONFIG_CC_HAS_ASM_GOTO */

#पूर्ण_अगर /* _TOOLS_LINUX_ASM_X86_RMWcc */
