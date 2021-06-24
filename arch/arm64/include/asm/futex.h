<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2012 ARM Ltd.
 */
#अगर_अघोषित __ASM_FUTEX_H
#घोषणा __ASM_FUTEX_H

#समावेश <linux/futex.h>
#समावेश <linux/uaccess.h>

#समावेश <यंत्र/त्रुटिसं.स>

#घोषणा FUTEX_MAX_LOOPS	128 /* What's the largest number you can think of? */

#घोषणा __futex_atomic_op(insn, ret, oldval, uaddr, पंचांगp, oparg)		\
करो अणु									\
	अचिन्हित पूर्णांक loops = FUTEX_MAX_LOOPS;				\
									\
	uaccess_enable_privileged();					\
	यंत्र अस्थिर(							\
"	prfm	pstl1strm, %2\n"					\
"1:	ldxr	%w1, %2\n"						\
	insn "\n"							\
"2:	stlxr	%w0, %w3, %2\n"						\
"	cbz	%w0, 3f\n"						\
"	sub	%w4, %w4, %w0\n"					\
"	cbnz	%w4, 1b\n"						\
"	mov	%w0, %w7\n"						\
"3:\n"									\
"	dmb	ish\n"							\
"	.pushsection .fixup,\"ax\"\n"					\
"	.align	2\n"							\
"4:	mov	%w0, %w6\n"						\
"	b	3b\n"							\
"	.popsection\n"							\
	_ASM_EXTABLE(1b, 4b)						\
	_ASM_EXTABLE(2b, 4b)						\
	: "=&r" (ret), "=&r" (oldval), "+Q" (*uaddr), "=&r" (पंचांगp),	\
	  "+r" (loops)							\
	: "r" (oparg), "Ir" (-EFAULT), "Ir" (-EAGAIN)			\
	: "memory");							\
	uaccess_disable_privileged();					\
पूर्ण जबतक (0)

अटल अंतरभूत पूर्णांक
arch_futex_atomic_op_inuser(पूर्णांक op, पूर्णांक oparg, पूर्णांक *oval, u32 __user *_uaddr)
अणु
	पूर्णांक oldval = 0, ret, पंचांगp;
	u32 __user *uaddr = __uaccess_mask_ptr(_uaddr);

	अगर (!access_ok(_uaddr, माप(u32)))
		वापस -EFAULT;

	चयन (op) अणु
	हाल FUTEX_OP_SET:
		__futex_atomic_op("mov	%w3, %w5",
				  ret, oldval, uaddr, पंचांगp, oparg);
		अवरोध;
	हाल FUTEX_OP_ADD:
		__futex_atomic_op("add	%w3, %w1, %w5",
				  ret, oldval, uaddr, पंचांगp, oparg);
		अवरोध;
	हाल FUTEX_OP_OR:
		__futex_atomic_op("orr	%w3, %w1, %w5",
				  ret, oldval, uaddr, पंचांगp, oparg);
		अवरोध;
	हाल FUTEX_OP_ANDN:
		__futex_atomic_op("and	%w3, %w1, %w5",
				  ret, oldval, uaddr, पंचांगp, ~oparg);
		अवरोध;
	हाल FUTEX_OP_XOR:
		__futex_atomic_op("eor	%w3, %w1, %w5",
				  ret, oldval, uaddr, पंचांगp, oparg);
		अवरोध;
	शेष:
		ret = -ENOSYS;
	पूर्ण

	अगर (!ret)
		*oval = oldval;

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक
futex_atomic_cmpxchg_inatomic(u32 *uval, u32 __user *_uaddr,
			      u32 oldval, u32 newval)
अणु
	पूर्णांक ret = 0;
	अचिन्हित पूर्णांक loops = FUTEX_MAX_LOOPS;
	u32 val, पंचांगp;
	u32 __user *uaddr;

	अगर (!access_ok(_uaddr, माप(u32)))
		वापस -EFAULT;

	uaddr = __uaccess_mask_ptr(_uaddr);
	uaccess_enable_privileged();
	यंत्र अस्थिर("// futex_atomic_cmpxchg_inatomic\n"
"	prfm	pstl1strm, %2\n"
"1:	ldxr	%w1, %2\n"
"	sub	%w3, %w1, %w5\n"
"	cbnz	%w3, 4f\n"
"2:	stlxr	%w3, %w6, %2\n"
"	cbz	%w3, 3f\n"
"	sub	%w4, %w4, %w3\n"
"	cbnz	%w4, 1b\n"
"	mov	%w0, %w8\n"
"3:\n"
"	dmb	ish\n"
"4:\n"
"	.pushsection .fixup,\"ax\"\n"
"5:	mov	%w0, %w7\n"
"	b	4b\n"
"	.popsection\n"
	_ASM_EXTABLE(1b, 5b)
	_ASM_EXTABLE(2b, 5b)
	: "+r" (ret), "=&r" (val), "+Q" (*uaddr), "=&r" (पंचांगp), "+r" (loops)
	: "r" (oldval), "r" (newval), "Ir" (-EFAULT), "Ir" (-EAGAIN)
	: "memory");
	uaccess_disable_privileged();

	अगर (!ret)
		*uval = val;

	वापस ret;
पूर्ण

#पूर्ण_अगर /* __ASM_FUTEX_H */
