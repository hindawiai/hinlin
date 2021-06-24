<शैली गुरु>
#अगर_अघोषित _ASM_POWERPC_ASM_CONST_H
#घोषणा _ASM_POWERPC_ASM_CONST_H

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

/*
 * Inline assembly memory स्थिरraपूर्णांक
 *
 * GCC 4.9 करोesn't properly handle pre update memory स्थिरraपूर्णांक "m<>"
 *
 */
#अगर defined(GCC_VERSION) && GCC_VERSION < 50000
#घोषणा UPD_CONSTR ""
#अन्यथा
#घोषणा UPD_CONSTR "<>"
#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_POWERPC_ASM_CONST_H */
