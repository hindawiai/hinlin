<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_ALPHA_FUTEX_H
#घोषणा _ASM_ALPHA_FUTEX_H

#अगर_घोषित __KERNEL__

#समावेश <linux/futex.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/त्रुटिसं.स>
#समावेश <यंत्र/barrier.h>

#घोषणा __futex_atomic_op(insn, ret, oldval, uaddr, oparg)	\
	__यंत्र__ __अस्थिर__(					\
		__ASM_SMP_MB					\
	"1:	ldl_l	%0,0(%2)\n"				\
		insn						\
	"2:	stl_c	%1,0(%2)\n"				\
	"	beq	%1,4f\n"				\
	"	mov	$31,%1\n"				\
	"3:	.subsection 2\n"				\
	"4:	br	1b\n"					\
	"	.previous\n"					\
	EXC(1b,3b,$31,%1)					\
	EXC(2b,3b,$31,%1)					\
	:	"=&r" (oldval), "=&r"(ret)			\
	:	"r" (uaddr), "r"(oparg)				\
	:	"memory")

अटल अंतरभूत पूर्णांक arch_futex_atomic_op_inuser(पूर्णांक op, पूर्णांक oparg, पूर्णांक *oval,
		u32 __user *uaddr)
अणु
	पूर्णांक oldval = 0, ret;

	अगर (!access_ok(uaddr, माप(u32)))
		वापस -EFAULT;

	चयन (op) अणु
	हाल FUTEX_OP_SET:
		__futex_atomic_op("mov %3,%1\n", ret, oldval, uaddr, oparg);
		अवरोध;
	हाल FUTEX_OP_ADD:
		__futex_atomic_op("addl %0,%3,%1\n", ret, oldval, uaddr, oparg);
		अवरोध;
	हाल FUTEX_OP_OR:
		__futex_atomic_op("or %0,%3,%1\n", ret, oldval, uaddr, oparg);
		अवरोध;
	हाल FUTEX_OP_ANDN:
		__futex_atomic_op("andnot %0,%3,%1\n", ret, oldval, uaddr, oparg);
		अवरोध;
	हाल FUTEX_OP_XOR:
		__futex_atomic_op("xor %0,%3,%1\n", ret, oldval, uaddr, oparg);
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

	__यंत्र__ __अस्थिर__ (
		__ASM_SMP_MB
	"1:	ldl_l	%1,0(%3)\n"
	"	cmpeq	%1,%4,%2\n"
	"	beq	%2,3f\n"
	"	mov	%5,%2\n"
	"2:	stl_c	%2,0(%3)\n"
	"	beq	%2,4f\n"
	"3:	.subsection 2\n"
	"4:	br	1b\n"
	"	.previous\n"
	EXC(1b,3b,$31,%0)
	EXC(2b,3b,$31,%0)
	:	"+r"(ret), "=&r"(prev), "=&r"(cmp)
	:	"r"(uaddr), "r"((दीर्घ)(पूर्णांक)oldval), "r"(newval)
	:	"memory");

	*uval = prev;
	वापस ret;
पूर्ण

#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर /* _ASM_ALPHA_FUTEX_H */
