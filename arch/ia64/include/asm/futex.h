<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_FUTEX_H
#घोषणा _ASM_FUTEX_H

#समावेश <linux/futex.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/त्रुटिसं.स>

#घोषणा __futex_atomic_op1(insn, ret, oldval, uaddr, oparg) \
करो अणु									\
	रेजिस्टर अचिन्हित दीर्घ r8 __यंत्र ("r8") = 0;			\
	__यंत्र__ __अस्थिर__(						\
		"	mf;;					\n"	\
		"[1:] "	insn ";;				\n"	\
		"	.xdata4 \"__ex_table\", 1b-., 2f-.	\n"	\
		"[2:]"							\
		: "+r" (r8), "=r" (oldval)				\
		: "r" (uaddr), "r" (oparg)				\
		: "memory");						\
	ret = r8;							\
पूर्ण जबतक (0)

#घोषणा __futex_atomic_op2(insn, ret, oldval, uaddr, oparg) \
करो अणु									\
	रेजिस्टर अचिन्हित दीर्घ r8 __यंत्र ("r8") = 0;			\
	पूर्णांक val, newval;						\
	करो अणु								\
		__यंत्र__ __अस्थिर__(					\
			"	mf;;				  \n"	\
			"[1:]	ld4 %3=[%4];;			  \n"	\
			"	mov %2=%3			  \n"	\
				insn	";;			  \n"	\
			"	mov ar.ccv=%2;;			  \n"	\
			"[2:]	cmpxchg4.acq %1=[%4],%3,ar.ccv;;  \n"	\
			"	.xdata4 \"__ex_table\", 1b-., 3f-.\n"	\
			"	.xdata4 \"__ex_table\", 2b-., 3f-.\n"	\
			"[3:]"						\
			: "+r" (r8), "=r" (val), "=&r" (oldval),	\
			   "=&r" (newval)				\
			: "r" (uaddr), "r" (oparg)			\
			: "memory");					\
		अगर (unlikely (r8))					\
			अवरोध;						\
	पूर्ण जबतक (unlikely (val != oldval));				\
	ret = r8;							\
पूर्ण जबतक (0)

अटल अंतरभूत पूर्णांक
arch_futex_atomic_op_inuser(पूर्णांक op, पूर्णांक oparg, पूर्णांक *oval, u32 __user *uaddr)
अणु
	पूर्णांक oldval = 0, ret;

	अगर (!access_ok(uaddr, माप(u32)))
		वापस -EFAULT;

	चयन (op) अणु
	हाल FUTEX_OP_SET:
		__futex_atomic_op1("xchg4 %1=[%2],%3", ret, oldval, uaddr,
				   oparg);
		अवरोध;
	हाल FUTEX_OP_ADD:
		__futex_atomic_op2("add %3=%3,%5", ret, oldval, uaddr, oparg);
		अवरोध;
	हाल FUTEX_OP_OR:
		__futex_atomic_op2("or %3=%3,%5", ret, oldval, uaddr, oparg);
		अवरोध;
	हाल FUTEX_OP_ANDN:
		__futex_atomic_op2("and %3=%3,%5", ret, oldval, uaddr,
				   ~oparg);
		अवरोध;
	हाल FUTEX_OP_XOR:
		__futex_atomic_op2("xor %3=%3,%5", ret, oldval, uaddr, oparg);
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
	अगर (!access_ok(uaddr, माप(u32)))
		वापस -EFAULT;

	अणु
		रेजिस्टर अचिन्हित दीर्घ r8 __यंत्र ("r8") = 0;
		अचिन्हित दीर्घ prev;
		__यंत्र__ __अस्थिर__(
			"	mf;;					\n"
			"	mov ar.ccv=%4;;				\n"
			"[1:]	cmpxchg4.acq %1=[%2],%3,ar.ccv		\n"
			"	.xdata4 \"__ex_table\", 1b-., 2f-.	\n"
			"[2:]"
			: "+r" (r8), "=&r" (prev)
			: "r" (uaddr), "r" (newval),
			  "rO" ((दीर्घ) (अचिन्हित) oldval)
			: "memory");
		*uval = prev;
		वापस r8;
	पूर्ण
पूर्ण

#पूर्ण_अगर /* _ASM_FUTEX_H */
