<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_OPENRISC_FUTEX_H
#घोषणा __ASM_OPENRISC_FUTEX_H

#अगर_घोषित __KERNEL__

#समावेश <linux/futex.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/त्रुटिसं.स>

#घोषणा __futex_atomic_op(insn, ret, oldval, uaddr, oparg) \
(अणु								\
	__यंत्र__ __अस्थिर__ (					\
		"1:	l.lwa	%0, %2			\n"	\
			insn				"\n"	\
		"2:	l.swa	%2, %1			\n"	\
		"	l.bnf	1b			\n"	\
		"	 l.ori	%1, r0, 0		\n"	\
		"3:					\n"	\
		".section .fixup,\"ax\"			\n"	\
		"4:	l.j	3b			\n"	\
		"	 l.addi	%1, r0, %3		\n"	\
		".previous				\n"	\
		".section __ex_table,\"a\"		\n"	\
		".word	1b,4b,2b,4b			\n"	\
		".previous				\n"	\
		: "=&r" (oldval), "=&r" (ret), "+m" (*uaddr)	\
		: "i" (-EFAULT), "r" (oparg)			\
		: "cc", "memory"				\
		);						\
पूर्ण)

अटल अंतरभूत पूर्णांक
arch_futex_atomic_op_inuser(पूर्णांक op, पूर्णांक oparg, पूर्णांक *oval, u32 __user *uaddr)
अणु
	पूर्णांक oldval = 0, ret;

	अगर (!access_ok(uaddr, माप(u32)))
		वापस -EFAULT;

	चयन (op) अणु
	हाल FUTEX_OP_SET:
		__futex_atomic_op("l.or %1,%4,%4", ret, oldval, uaddr, oparg);
		अवरोध;
	हाल FUTEX_OP_ADD:
		__futex_atomic_op("l.add %1,%0,%4", ret, oldval, uaddr, oparg);
		अवरोध;
	हाल FUTEX_OP_OR:
		__futex_atomic_op("l.or %1,%0,%4", ret, oldval, uaddr, oparg);
		अवरोध;
	हाल FUTEX_OP_ANDN:
		__futex_atomic_op("l.and %1,%0,%4", ret, oldval, uaddr, ~oparg);
		अवरोध;
	हाल FUTEX_OP_XOR:
		__futex_atomic_op("l.xor %1,%0,%4", ret, oldval, uaddr, oparg);
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
	पूर्णांक ret = 0;
	u32 prev;

	अगर (!access_ok(uaddr, माप(u32)))
		वापस -EFAULT;

	__यंत्र__ __अस्थिर__ (				\
		"1:	l.lwa	%1, %2		\n"	\
		"	l.sfeq	%1, %3		\n"	\
		"	l.bnf	3f		\n"	\
		"	 l.nop			\n"	\
		"2:	l.swa	%2, %4		\n"	\
		"	l.bnf	1b		\n"	\
		"	 l.nop			\n"	\
		"3:				\n"	\
		".section .fixup,\"ax\"		\n"	\
		"4:	l.j	3b		\n"	\
		"	 l.addi	%0, r0, %5	\n"	\
		".previous			\n"	\
		".section __ex_table,\"a\"	\n"	\
		".word	1b,4b,2b,4b		\n"	\
		".previous			\n"	\
		: "+r" (ret), "=&r" (prev), "+m" (*uaddr) \
		: "r" (oldval), "r" (newval), "i" (-EFAULT) \
		: "cc",	"memory"			\
		);

	*uval = prev;
	वापस ret;
पूर्ण

#पूर्ण_अगर /* __KERNEL__ */

#पूर्ण_अगर /* __ASM_OPENRISC_FUTEX_H */
