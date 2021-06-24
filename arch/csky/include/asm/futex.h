<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित __ASM_CSKY_FUTEX_H
#घोषणा __ASM_CSKY_FUTEX_H

#अगर_अघोषित CONFIG_SMP
#समावेश <यंत्र-generic/futex.h>
#अन्यथा
#समावेश <linux/atomic.h>
#समावेश <linux/futex.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/त्रुटिसं.स>

#घोषणा __futex_atomic_op(insn, ret, oldval, uaddr, oparg)		\
अणु									\
	u32 पंचांगp;							\
									\
	__atomic_pre_full_fence();					\
									\
	__यंत्र__ __अस्थिर__ (						\
	"1:	ldex.w	%[ov], %[u]			\n"		\
	"	"insn"					\n"		\
	"2:	stex.w	%[t], %[u]			\n"		\
	"	bez	%[t], 1b			\n"		\
	"	br	4f				\n"		\
	"3:	mov	%[r], %[e]			\n"		\
	"4:						\n"		\
	"	.section __ex_table,\"a\"		\n"		\
	"	.balign 4				\n"		\
	"	.long	1b, 3b				\n"		\
	"	.long	2b, 3b				\n"		\
	"	.previous				\n"		\
	: [r] "+r" (ret), [ov] "=&r" (oldval),				\
	  [u] "+m" (*uaddr), [t] "=&r" (पंचांगp)				\
	: [op] "Jr" (oparg), [e] "jr" (-EFAULT)				\
	: "memory");							\
									\
	__atomic_post_full_fence();					\
पूर्ण

अटल अंतरभूत पूर्णांक
arch_futex_atomic_op_inuser(पूर्णांक op, पूर्णांक oparg, पूर्णांक *oval, u32 __user *uaddr)
अणु
	पूर्णांक oldval = 0, ret = 0;

	अगर (!access_ok(uaddr, माप(u32)))
		वापस -EFAULT;

	चयन (op) अणु
	हाल FUTEX_OP_SET:
		__futex_atomic_op("mov %[t], %[ov]",
				  ret, oldval, uaddr, oparg);
		अवरोध;
	हाल FUTEX_OP_ADD:
		__futex_atomic_op("add %[t], %[ov], %[op]",
				  ret, oldval, uaddr, oparg);
		अवरोध;
	हाल FUTEX_OP_OR:
		__futex_atomic_op("or %[t], %[ov], %[op]",
				  ret, oldval, uaddr, oparg);
		अवरोध;
	हाल FUTEX_OP_ANDN:
		__futex_atomic_op("and %[t], %[ov], %[op]",
				  ret, oldval, uaddr, ~oparg);
		अवरोध;
	हाल FUTEX_OP_XOR:
		__futex_atomic_op("xor %[t], %[ov], %[op]",
				  ret, oldval, uaddr, oparg);
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
	u32 val, पंचांगp;

	अगर (!access_ok(uaddr, माप(u32)))
		वापस -EFAULT;

	__atomic_pre_full_fence();

	__यंत्र__ __अस्थिर__ (
	"1:	ldex.w	%[v], %[u]			\n"
	"	cmpne	%[v], %[ov]			\n"
	"	bt	4f				\n"
	"	mov	%[t], %[nv]			\n"
	"2:	stex.w	%[t], %[u]			\n"
	"	bez	%[t], 1b			\n"
	"	br	4f				\n"
	"3:	mov	%[r], %[e]			\n"
	"4:						\n"
	"	.section __ex_table,\"a\"		\n"
	"	.balign 4				\n"
	"	.long	1b, 3b				\n"
	"	.long	2b, 3b				\n"
	"	.previous				\n"
	: [r] "+r" (ret), [v] "=&r" (val), [u] "+m" (*uaddr),
	  [t] "=&r" (पंचांगp)
	: [ov] "Jr" (oldval), [nv] "Jr" (newval), [e] "Jr" (-EFAULT)
	: "memory");

	__atomic_post_full_fence();

	*uval = val;
	वापस ret;
पूर्ण

#पूर्ण_अगर /* CONFIG_SMP */
#पूर्ण_अगर /* __ASM_CSKY_FUTEX_H */
