<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_S390_FUTEX_H
#घोषणा _ASM_S390_FUTEX_H

#समावेश <linux/uaccess.h>
#समावेश <linux/futex.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/त्रुटिसं.स>

#घोषणा __futex_atomic_op(insn, ret, oldval, newval, uaddr, oparg)	\
	यंत्र अस्थिर(							\
		"   sacf  256\n"					\
		"0: l     %1,0(%6)\n"					\
		"1:"insn						\
		"2: cs    %1,%2,0(%6)\n"				\
		"3: jl    1b\n"						\
		"   lhi   %0,0\n"					\
		"4: sacf  768\n"					\
		EX_TABLE(0b,4b) EX_TABLE(2b,4b) EX_TABLE(3b,4b)		\
		: "=d" (ret), "=&d" (oldval), "=&d" (newval),		\
		  "=m" (*uaddr)						\
		: "0" (-EFAULT), "d" (oparg), "a" (uaddr),		\
		  "m" (*uaddr) : "cc");

अटल अंतरभूत पूर्णांक arch_futex_atomic_op_inuser(पूर्णांक op, पूर्णांक oparg, पूर्णांक *oval,
		u32 __user *uaddr)
अणु
	पूर्णांक oldval = 0, newval, ret;

	चयन (op) अणु
	हाल FUTEX_OP_SET:
		__futex_atomic_op("lr %2,%5\n",
				  ret, oldval, newval, uaddr, oparg);
		अवरोध;
	हाल FUTEX_OP_ADD:
		__futex_atomic_op("lr %2,%1\nar %2,%5\n",
				  ret, oldval, newval, uaddr, oparg);
		अवरोध;
	हाल FUTEX_OP_OR:
		__futex_atomic_op("lr %2,%1\nor %2,%5\n",
				  ret, oldval, newval, uaddr, oparg);
		अवरोध;
	हाल FUTEX_OP_ANDN:
		__futex_atomic_op("lr %2,%1\nnr %2,%5\n",
				  ret, oldval, newval, uaddr, oparg);
		अवरोध;
	हाल FUTEX_OP_XOR:
		__futex_atomic_op("lr %2,%1\nxr %2,%5\n",
				  ret, oldval, newval, uaddr, oparg);
		अवरोध;
	शेष:
		ret = -ENOSYS;
	पूर्ण

	अगर (!ret)
		*oval = oldval;

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक futex_atomic_cmpxchg_inatomic(u32 *uval, u32 __user *uaddr,
						u32 oldval, u32 newval)
अणु
	पूर्णांक ret;

	यंत्र अस्थिर(
		"   sacf 256\n"
		"0: cs   %1,%4,0(%5)\n"
		"1: la   %0,0\n"
		"2: sacf 768\n"
		EX_TABLE(0b,2b) EX_TABLE(1b,2b)
		: "=d" (ret), "+d" (oldval), "=m" (*uaddr)
		: "0" (-EFAULT), "d" (newval), "a" (uaddr), "m" (*uaddr)
		: "cc", "memory");
	*uval = oldval;
	वापस ret;
पूर्ण

#पूर्ण_अगर /* _ASM_S390_FUTEX_H */
