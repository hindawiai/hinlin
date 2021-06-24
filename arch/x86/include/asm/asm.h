<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_ASM_H
#घोषणा _ASM_X86_ASM_H

#अगर_घोषित __ASSEMBLY__
# define __ASM_FORM(x)	x
# define __ASM_FORM_RAW(x)     x
# define __ASM_FORM_COMMA(x) x,
#अन्यथा
#समावेश <linux/stringअगरy.h>

# define __ASM_FORM(x)	" " __stringअगरy(x) " "
# define __ASM_FORM_RAW(x)     __stringअगरy(x)
# define __ASM_FORM_COMMA(x) " " __stringअगरy(x) ","
#पूर्ण_अगर

#अगर_अघोषित __x86_64__
/* 32 bit */
# define __ASM_SEL(a,b) __ASM_FORM(a)
# define __ASM_SEL_RAW(a,b) __ASM_FORM_RAW(a)
#अन्यथा
/* 64 bit */
# define __ASM_SEL(a,b) __ASM_FORM(b)
# define __ASM_SEL_RAW(a,b) __ASM_FORM_RAW(b)
#पूर्ण_अगर

#घोषणा __ASM_SIZE(inst, ...)	__ASM_SEL(inst##l##__VA_ARGS__, \
					  inst##q##__VA_ARGS__)
#घोषणा __ASM_REG(reg)         __ASM_SEL_RAW(e##reg, r##reg)

#घोषणा _ASM_PTR	__ASM_SEL(.दीर्घ, .quad)
#घोषणा _ASM_ALIGN	__ASM_SEL(.balign 4, .balign 8)

#घोषणा _ASM_MOV	__ASM_SIZE(mov)
#घोषणा _ASM_INC	__ASM_SIZE(inc)
#घोषणा _ASM_DEC	__ASM_SIZE(dec)
#घोषणा _ASM_ADD	__ASM_SIZE(add)
#घोषणा _ASM_SUB	__ASM_SIZE(sub)
#घोषणा _ASM_XADD	__ASM_SIZE(xadd)
#घोषणा _ASM_MUL	__ASM_SIZE(mul)

#घोषणा _ASM_AX		__ASM_REG(ax)
#घोषणा _ASM_BX		__ASM_REG(bx)
#घोषणा _ASM_CX		__ASM_REG(cx)
#घोषणा _ASM_DX		__ASM_REG(dx)
#घोषणा _ASM_SP		__ASM_REG(sp)
#घोषणा _ASM_BP		__ASM_REG(bp)
#घोषणा _ASM_SI		__ASM_REG(si)
#घोषणा _ASM_DI		__ASM_REG(di)

#अगर_अघोषित __x86_64__
/* 32 bit */

#घोषणा _ASM_ARG1	_ASM_AX
#घोषणा _ASM_ARG2	_ASM_DX
#घोषणा _ASM_ARG3	_ASM_CX

#घोषणा _ASM_ARG1L	eax
#घोषणा _ASM_ARG2L	edx
#घोषणा _ASM_ARG3L	ecx

#घोषणा _ASM_ARG1W	ax
#घोषणा _ASM_ARG2W	dx
#घोषणा _ASM_ARG3W	cx

#घोषणा _ASM_ARG1B	al
#घोषणा _ASM_ARG2B	dl
#घोषणा _ASM_ARG3B	cl

#अन्यथा
/* 64 bit */

#घोषणा _ASM_ARG1	_ASM_DI
#घोषणा _ASM_ARG2	_ASM_SI
#घोषणा _ASM_ARG3	_ASM_DX
#घोषणा _ASM_ARG4	_ASM_CX
#घोषणा _ASM_ARG5	r8
#घोषणा _ASM_ARG6	r9

#घोषणा _ASM_ARG1Q	rdi
#घोषणा _ASM_ARG2Q	rsi
#घोषणा _ASM_ARG3Q	rdx
#घोषणा _ASM_ARG4Q	rcx
#घोषणा _ASM_ARG5Q	r8
#घोषणा _ASM_ARG6Q	r9

#घोषणा _ASM_ARG1L	edi
#घोषणा _ASM_ARG2L	esi
#घोषणा _ASM_ARG3L	edx
#घोषणा _ASM_ARG4L	ecx
#घोषणा _ASM_ARG5L	r8d
#घोषणा _ASM_ARG6L	r9d

#घोषणा _ASM_ARG1W	di
#घोषणा _ASM_ARG2W	si
#घोषणा _ASM_ARG3W	dx
#घोषणा _ASM_ARG4W	cx
#घोषणा _ASM_ARG5W	r8w
#घोषणा _ASM_ARG6W	r9w

#घोषणा _ASM_ARG1B	dil
#घोषणा _ASM_ARG2B	sil
#घोषणा _ASM_ARG3B	dl
#घोषणा _ASM_ARG4B	cl
#घोषणा _ASM_ARG5B	r8b
#घोषणा _ASM_ARG6B	r9b

#पूर्ण_अगर

/*
 * Macros to generate condition code outमाला_दो from अंतरभूत assembly,
 * The output opeअक्रम must be type "bool".
 */
#अगर_घोषित __GCC_ASM_FLAG_OUTPUTS__
# define CC_SET(c) "\n\t/* output condition code " #c "*/\n"
# define CC_OUT(c) "=@cc" #c
#अन्यथा
# define CC_SET(c) "\n\tset" #c " %[_cc_" #c "]\n"
# define CC_OUT(c) [_cc_ ## c] "=qm"
#पूर्ण_अगर

/* Exception table entry */
#अगर_घोषित __ASSEMBLY__
# define _ASM_EXTABLE_HANDLE(from, to, handler)			\
	.pushsection "__ex_table","a" ;				\
	.balign 4 ;						\
	.दीर्घ (from) - . ;					\
	.दीर्घ (to) - . ;					\
	.दीर्घ (handler) - . ;					\
	.popsection

# define _ASM_EXTABLE(from, to)					\
	_ASM_EXTABLE_HANDLE(from, to, ex_handler_शेष)

# define _ASM_EXTABLE_UA(from, to)				\
	_ASM_EXTABLE_HANDLE(from, to, ex_handler_uaccess)

# define _ASM_EXTABLE_CPY(from, to)				\
	_ASM_EXTABLE_HANDLE(from, to, ex_handler_copy)

# define _ASM_EXTABLE_FAULT(from, to)				\
	_ASM_EXTABLE_HANDLE(from, to, ex_handler_fault)

# अगरdef CONFIG_KPROBES
#  define _ASM_NOKPROBE(entry)					\
	.pushsection "_kprobe_blacklist","aw" ;			\
	_ASM_ALIGN ;						\
	_ASM_PTR (entry);					\
	.popsection
# अन्यथा
#  define _ASM_NOKPROBE(entry)
# endअगर

#अन्यथा /* ! __ASSEMBLY__ */
# define _EXPAND_EXTABLE_HANDLE(x) #x
# define _ASM_EXTABLE_HANDLE(from, to, handler)			\
	" .pushsection \"__ex_table\",\"a\"\n"			\
	" .balign 4\n"						\
	" .long (" #from ") - .\n"				\
	" .long (" #to ") - .\n"				\
	" .long (" _EXPAND_EXTABLE_HANDLE(handler) ") - .\n"	\
	" .popsection\n"

# define _ASM_EXTABLE(from, to)					\
	_ASM_EXTABLE_HANDLE(from, to, ex_handler_शेष)

# define _ASM_EXTABLE_UA(from, to)				\
	_ASM_EXTABLE_HANDLE(from, to, ex_handler_uaccess)

# define _ASM_EXTABLE_CPY(from, to)				\
	_ASM_EXTABLE_HANDLE(from, to, ex_handler_copy)

# define _ASM_EXTABLE_FAULT(from, to)				\
	_ASM_EXTABLE_HANDLE(from, to, ex_handler_fault)

/* For C file, we alपढ़ोy have NOKPROBE_SYMBOL macro */

/*
 * This output स्थिरraपूर्णांक should be used क्रम any अंतरभूत यंत्र which has a "call"
 * inकाष्ठाion.  Otherwise the यंत्र may be inserted beक्रमe the frame poपूर्णांकer
 * माला_लो set up by the containing function.  If you क्रमget to करो this, objtool
 * may prपूर्णांक a "call without frame pointer save/setup" warning.
 */
रेजिस्टर अचिन्हित दीर्घ current_stack_poपूर्णांकer यंत्र(_ASM_SP);
#घोषणा ASM_CALL_CONSTRAINT "+r" (current_stack_poपूर्णांकer)
#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* _ASM_X86_ASM_H */
