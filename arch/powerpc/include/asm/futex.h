<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_POWERPC_FUTEX_H
#घोषणा _ASM_POWERPC_FUTEX_H

#अगर_घोषित __KERNEL__

#समावेश <linux/futex.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/त्रुटिसं.स>
#समावेश <यंत्र/synch.h>

#घोषणा __futex_atomic_op(insn, ret, oldval, uaddr, oparg) \
  __यंत्र__ __अस्थिर ( \
	PPC_ATOMIC_ENTRY_BARRIER \
"1:	lwarx	%0,0,%2\n" \
	insn \
"2:	stwcx.	%1,0,%2\n" \
	"bne-	1b\n" \
	PPC_ATOMIC_EXIT_BARRIER \
	"li	%1,0\n" \
"3:	.section .fixup,\"ax\"\n" \
"4:	li	%1,%3\n" \
	"b	3b\n" \
	".previous\n" \
	EX_TABLE(1b, 4b) \
	EX_TABLE(2b, 4b) \
	: "=&r" (oldval), "=&r" (ret) \
	: "b" (uaddr), "i" (-EFAULT), "r" (oparg) \
	: "cr0", "memory")

अटल अंतरभूत पूर्णांक arch_futex_atomic_op_inuser(पूर्णांक op, पूर्णांक oparg, पूर्णांक *oval,
		u32 __user *uaddr)
अणु
	पूर्णांक oldval = 0, ret;

	अगर (!user_access_begin(uaddr, माप(u32)))
		वापस -EFAULT;

	चयन (op) अणु
	हाल FUTEX_OP_SET:
		__futex_atomic_op("mr %1,%4\n", ret, oldval, uaddr, oparg);
		अवरोध;
	हाल FUTEX_OP_ADD:
		__futex_atomic_op("add %1,%0,%4\n", ret, oldval, uaddr, oparg);
		अवरोध;
	हाल FUTEX_OP_OR:
		__futex_atomic_op("or %1,%0,%4\n", ret, oldval, uaddr, oparg);
		अवरोध;
	हाल FUTEX_OP_ANDN:
		__futex_atomic_op("andc %1,%0,%4\n", ret, oldval, uaddr, oparg);
		अवरोध;
	हाल FUTEX_OP_XOR:
		__futex_atomic_op("xor %1,%0,%4\n", ret, oldval, uaddr, oparg);
		अवरोध;
	शेष:
		ret = -ENOSYS;
	पूर्ण
	user_access_end();

	*oval = oldval;

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक
futex_atomic_cmpxchg_inatomic(u32 *uval, u32 __user *uaddr,
			      u32 oldval, u32 newval)
अणु
	पूर्णांक ret = 0;
	u32 prev;

	अगर (!user_access_begin(uaddr, माप(u32)))
		वापस -EFAULT;

        __यंत्र__ __अस्थिर__ (
        PPC_ATOMIC_ENTRY_BARRIER
"1:     lwarx   %1,0,%3         # futex_atomic_cmpxchg_inatomic\न\
        cmpw    0,%1,%4\न\
        bne-    3f\न"
"2:     stwcx.  %5,0,%3\न\
        bne-    1b\न"
        PPC_ATOMIC_EXIT_BARRIER
"3:	.section .fixup,\"ax\"\न\
4:	li	%0,%6\न\
	b	3b\न\
	.previous\न"
	EX_TABLE(1b, 4b)
	EX_TABLE(2b, 4b)
        : "+r" (ret), "=&r" (prev), "+m" (*uaddr)
        : "r" (uaddr), "r" (oldval), "r" (newval), "i" (-EFAULT)
        : "cc", "memory");

	user_access_end();

	*uval = prev;

        वापस ret;
पूर्ण

#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर /* _ASM_POWERPC_FUTEX_H */
