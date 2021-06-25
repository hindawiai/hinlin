<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 *
 * Vineetg: August 2010: From Android kernel work
 */

#अगर_अघोषित _ASM_FUTEX_H
#घोषणा _ASM_FUTEX_H

#समावेश <linux/futex.h>
#समावेश <linux/preempt.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/त्रुटिसं.स>

#अगर_घोषित CONFIG_ARC_HAS_LLSC

#घोषणा __futex_atomic_op(insn, ret, oldval, uaddr, oparg)\
							\
	smp_mb();					\
	__यंत्र__ __अस्थिर__(				\
	"1:	llock	%1, [%2]		\n"	\
		insn				"\n"	\
	"2:	scond	%0, [%2]		\n"	\
	"	bnz	1b			\n"	\
	"	mov %0, 0			\n"	\
	"3:					\n"	\
	"	.section .fixup,\"ax\"		\n"	\
	"	.align  4			\n"	\
	"4:	mov %0, %4			\n"	\
	"	j   3b				\n"	\
	"	.previous			\n"	\
	"	.section __ex_table,\"a\"	\n"	\
	"	.align  4			\n"	\
	"	.word   1b, 4b			\n"	\
	"	.word   2b, 4b			\n"	\
	"	.previous			\n"	\
							\
	: "=&r" (ret), "=&r" (oldval)			\
	: "r" (uaddr), "r" (oparg), "ir" (-EFAULT)	\
	: "cc", "memory");				\
	smp_mb()					\

#अन्यथा	/* !CONFIG_ARC_HAS_LLSC */

#घोषणा __futex_atomic_op(insn, ret, oldval, uaddr, oparg)\
							\
	smp_mb();					\
	__यंत्र__ __अस्थिर__(				\
	"1:	ld	%1, [%2]		\n"	\
		insn				"\n"	\
	"2:	st	%0, [%2]		\n"	\
	"	mov %0, 0			\n"	\
	"3:					\n"	\
	"	.section .fixup,\"ax\"		\n"	\
	"	.align  4			\n"	\
	"4:	mov %0, %4			\n"	\
	"	j   3b				\n"	\
	"	.previous			\n"	\
	"	.section __ex_table,\"a\"	\n"	\
	"	.align  4			\n"	\
	"	.word   1b, 4b			\n"	\
	"	.word   2b, 4b			\n"	\
	"	.previous			\n"	\
							\
	: "=&r" (ret), "=&r" (oldval)			\
	: "r" (uaddr), "r" (oparg), "ir" (-EFAULT)	\
	: "cc", "memory");				\
	smp_mb()					\

#पूर्ण_अगर

अटल अंतरभूत पूर्णांक arch_futex_atomic_op_inuser(पूर्णांक op, पूर्णांक oparg, पूर्णांक *oval,
		u32 __user *uaddr)
अणु
	पूर्णांक oldval = 0, ret;

	अगर (!access_ok(uaddr, माप(u32)))
		वापस -EFAULT;

#अगर_अघोषित CONFIG_ARC_HAS_LLSC
	preempt_disable();	/* to guarantee atomic r-m-w of futex op */
#पूर्ण_अगर

	चयन (op) अणु
	हाल FUTEX_OP_SET:
		__futex_atomic_op("mov %0, %3", ret, oldval, uaddr, oparg);
		अवरोध;
	हाल FUTEX_OP_ADD:
		/* oldval = *uaddr; *uaddr += oparg ; ret = *uaddr */
		__futex_atomic_op("add %0, %1, %3", ret, oldval, uaddr, oparg);
		अवरोध;
	हाल FUTEX_OP_OR:
		__futex_atomic_op("or  %0, %1, %3", ret, oldval, uaddr, oparg);
		अवरोध;
	हाल FUTEX_OP_ANDN:
		__futex_atomic_op("bic %0, %1, %3", ret, oldval, uaddr, oparg);
		अवरोध;
	हाल FUTEX_OP_XOR:
		__futex_atomic_op("xor %0, %1, %3", ret, oldval, uaddr, oparg);
		अवरोध;
	शेष:
		ret = -ENOSYS;
	पूर्ण

#अगर_अघोषित CONFIG_ARC_HAS_LLSC
	preempt_enable();
#पूर्ण_अगर

	अगर (!ret)
		*oval = oldval;

	वापस ret;
पूर्ण

/*
 * cmpxchg of futex (pagefaults disabled by caller)
 * Return 0 क्रम success, -EFAULT otherwise
 */
अटल अंतरभूत पूर्णांक
futex_atomic_cmpxchg_inatomic(u32 *uval, u32 __user *uaddr, u32 expval,
			      u32 newval)
अणु
	पूर्णांक ret = 0;
	u32 existval;

	अगर (!access_ok(uaddr, माप(u32)))
		वापस -EFAULT;

#अगर_अघोषित CONFIG_ARC_HAS_LLSC
	preempt_disable();	/* to guarantee atomic r-m-w of futex op */
#पूर्ण_अगर
	smp_mb();

	__यंत्र__ __अस्थिर__(
#अगर_घोषित CONFIG_ARC_HAS_LLSC
	"1:	llock	%1, [%4]		\n"
	"	brne	%1, %2, 3f		\n"
	"2:	scond	%3, [%4]		\n"
	"	bnz	1b			\n"
#अन्यथा
	"1:	ld	%1, [%4]		\n"
	"	brne	%1, %2, 3f		\n"
	"2:	st	%3, [%4]		\n"
#पूर्ण_अगर
	"3:	\n"
	"	.section .fixup,\"ax\"	\n"
	"4:	mov %0, %5	\n"
	"	j   3b	\n"
	"	.previous	\n"
	"	.section __ex_table,\"a\"	\n"
	"	.align  4	\n"
	"	.word   1b, 4b	\n"
	"	.word   2b, 4b	\n"
	"	.previous\n"
	: "+&r"(ret), "=&r"(existval)
	: "r"(expval), "r"(newval), "r"(uaddr), "ir"(-EFAULT)
	: "cc", "memory");

	smp_mb();

#अगर_अघोषित CONFIG_ARC_HAS_LLSC
	preempt_enable();
#पूर्ण_अगर
	*uval = existval;
	वापस ret;
पूर्ण

#पूर्ण_अगर
