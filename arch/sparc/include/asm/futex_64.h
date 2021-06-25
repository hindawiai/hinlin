<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _SPARC64_FUTEX_H
#घोषणा _SPARC64_FUTEX_H

#समावेश <linux/futex.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/त्रुटिसं.स>

#घोषणा __futex_cas_op(insn, ret, oldval, uaddr, oparg)	\
	__यंत्र__ __अस्थिर__(				\
	"\n1:	lduwa	[%3] %%asi, %2\n"		\
	"	" insn "\n"				\
	"2:	casa	[%3] %%asi, %2, %1\n"		\
	"	cmp	%2, %1\n"			\
	"	bne,pn	%%icc, 1b\n"			\
	"	 mov	0, %0\n"			\
	"3:\n"						\
	"	.section .fixup,#alloc,#execinstr\n"	\
	"	.align	4\n"				\
	"4:	sethi	%%hi(3b), %0\n"			\
	"	jmpl	%0 + %%lo(3b), %%g0\n"		\
	"	 mov	%5, %0\n"			\
	"	.previous\n"				\
	"	.section __ex_table,\"a\"\n"		\
	"	.align	4\n"				\
	"	.word	1b, 4b\n"			\
	"	.word	2b, 4b\n"			\
	"	.previous\n"				\
	: "=&r" (ret), "=&r" (oldval), "=&r" (tem)	\
	: "r" (uaddr), "r" (oparg), "i" (-EFAULT)	\
	: "memory")

अटल अंतरभूत पूर्णांक arch_futex_atomic_op_inuser(पूर्णांक op, पूर्णांक oparg, पूर्णांक *oval,
		u32 __user *uaddr)
अणु
	पूर्णांक oldval = 0, ret, tem;

	अगर (unlikely((((अचिन्हित दीर्घ) uaddr) & 0x3UL)))
		वापस -EINVAL;

	चयन (op) अणु
	हाल FUTEX_OP_SET:
		__futex_cas_op("mov\t%4, %1", ret, oldval, uaddr, oparg);
		अवरोध;
	हाल FUTEX_OP_ADD:
		__futex_cas_op("add\t%2, %4, %1", ret, oldval, uaddr, oparg);
		अवरोध;
	हाल FUTEX_OP_OR:
		__futex_cas_op("or\t%2, %4, %1", ret, oldval, uaddr, oparg);
		अवरोध;
	हाल FUTEX_OP_ANDN:
		__futex_cas_op("andn\t%2, %4, %1", ret, oldval, uaddr, oparg);
		अवरोध;
	हाल FUTEX_OP_XOR:
		__futex_cas_op("xor\t%2, %4, %1", ret, oldval, uaddr, oparg);
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

	__यंत्र__ __अस्थिर__(
	"\n1:	casa	[%4] %%asi, %3, %1\n"
	"2:\n"
	"	.section .fixup,#alloc,#execinstr\n"
	"	.align	4\n"
	"3:	sethi	%%hi(2b), %0\n"
	"	jmpl	%0 + %%lo(2b), %%g0\n"
	"	mov	%5, %0\n"
	"	.previous\n"
	"	.section __ex_table,\"a\"\n"
	"	.align	4\n"
	"	.word	1b, 3b\n"
	"	.previous\n"
	: "+r" (ret), "=r" (newval)
	: "1" (newval), "r" (oldval), "r" (uaddr), "i" (-EFAULT)
	: "memory");

	*uval = newval;
	वापस ret;
पूर्ण

#पूर्ण_अगर /* !(_SPARC64_FUTEX_H) */
