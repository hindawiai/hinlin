<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_MICROBLAZE_FUTEX_H
#घोषणा _ASM_MICROBLAZE_FUTEX_H

#अगर_घोषित __KERNEL__

#समावेश <linux/futex.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/त्रुटिसं.स>

#घोषणा __futex_atomic_op(insn, ret, oldval, uaddr, oparg) \
(अणु									\
	__यंत्र__ __अस्थिर__ (						\
			"1:	lwx	%0, %2, r0; "			\
				insn					\
			"2:	swx	%1, %2, r0;			\
				addic	%1, r0, 0;			\
				bnei	%1, 1b;				\
			3:						\
			.section .fixup,\"ax\";				\
			4:	brid	3b;				\
				addik	%1, r0, %3;			\
			.previous;					\
			.section __ex_table,\"a\";			\
			.word	1b,4b,2b,4b;				\
			.previous;"					\
	: "=&r" (oldval), "=&r" (ret)					\
	: "r" (uaddr), "i" (-EFAULT), "r" (oparg)			\
	);								\
पूर्ण)

अटल अंतरभूत पूर्णांक
arch_futex_atomic_op_inuser(पूर्णांक op, पूर्णांक oparg, पूर्णांक *oval, u32 __user *uaddr)
अणु
	पूर्णांक oldval = 0, ret;

	अगर (!access_ok(uaddr, माप(u32)))
		वापस -EFAULT;

	चयन (op) अणु
	हाल FUTEX_OP_SET:
		__futex_atomic_op("or %1,%4,%4;", ret, oldval, uaddr, oparg);
		अवरोध;
	हाल FUTEX_OP_ADD:
		__futex_atomic_op("add %1,%0,%4;", ret, oldval, uaddr, oparg);
		अवरोध;
	हाल FUTEX_OP_OR:
		__futex_atomic_op("or %1,%0,%4;", ret, oldval, uaddr, oparg);
		अवरोध;
	हाल FUTEX_OP_ANDN:
		__futex_atomic_op("andn %1,%0,%4;", ret, oldval, uaddr, oparg);
		अवरोध;
	हाल FUTEX_OP_XOR:
		__futex_atomic_op("xor %1,%0,%4;", ret, oldval, uaddr, oparg);
		अवरोध;
	शेष:
		ret = -ENOSYS;
	पूर्ण

	अगर (!ret)
		*oval = oldval;

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक
futex_atomic_cmpxchg_inatomic(u32 *uval, u32 __user *uaddr,
			      u32 oldval, u32 newval)
अणु
	पूर्णांक ret = 0, cmp;
	u32 prev;

	अगर (!access_ok(uaddr, माप(u32)))
		वापस -EFAULT;

	__यंत्र__ __अस्थिर__ ("1:	lwx	%1, %3, r0;		\
					cmp	%2, %1, %4;		\
					bnei	%2, 3f;			\
				2:	swx	%5, %3, r0;		\
					addic	%2, r0, 0;		\
					bnei	%2, 1b;			\
				3:					\
				.section .fixup,\"ax\";			\
				4:	brid	3b;			\
					addik	%0, r0, %6;		\
				.previous;				\
				.section __ex_table,\"a\";		\
				.word	1b,4b,2b,4b;			\
				.previous;"				\
		: "+r" (ret), "=&r" (prev), "=&r"(cmp)	\
		: "r" (uaddr), "r" (oldval), "r" (newval), "i" (-EFAULT));

	*uval = prev;
	वापस ret;
पूर्ण

#पूर्ण_अगर /* __KERNEL__ */

#पूर्ण_अगर
