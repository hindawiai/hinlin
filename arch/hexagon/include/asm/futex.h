<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_HEXAGON_FUTEX_H
#घोषणा _ASM_HEXAGON_FUTEX_H

#अगर_घोषित __KERNEL__

#समावेश <linux/futex.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/त्रुटिसं.स>

/* XXX TODO-- need to add sync barriers! */

#घोषणा __futex_atomic_op(insn, ret, oldval, uaddr, oparg) \
	__यंत्र__ __अस्थिर( \
	"1: %0 = memw_locked(%3);\n" \
	    /* For example: %1 = %4 */ \
	    insn \
	"2: memw_locked(%3,p2) = %1;\n" \
	"   if (!p2) jump 1b;\n" \
	"   %1 = #0;\n" \
	"3:\n" \
	".section .fixup,\"ax\"\n" \
	"4: %1 = #%5;\n" \
	"   jump ##3b\n" \
	".previous\n" \
	".section __ex_table,\"a\"\n" \
	".long 1b,4b,2b,4b\n" \
	".previous\n" \
	: "=&r" (oldval), "=&r" (ret), "+m" (*uaddr) \
	: "r" (uaddr), "r" (oparg), "i" (-EFAULT) \
	: "p2", "memory")


अटल अंतरभूत पूर्णांक
arch_futex_atomic_op_inuser(पूर्णांक op, पूर्णांक oparg, पूर्णांक *oval, u32 __user *uaddr)
अणु
	पूर्णांक oldval = 0, ret;

	अगर (!access_ok(uaddr, माप(u32)))
		वापस -EFAULT;

	चयन (op) अणु
	हाल FUTEX_OP_SET:
		__futex_atomic_op("%1 = %4\n", ret, oldval, uaddr, oparg);
		अवरोध;
	हाल FUTEX_OP_ADD:
		__futex_atomic_op("%1 = add(%0,%4)\n", ret, oldval, uaddr,
				  oparg);
		अवरोध;
	हाल FUTEX_OP_OR:
		__futex_atomic_op("%1 = or(%0,%4)\n", ret, oldval, uaddr,
				  oparg);
		अवरोध;
	हाल FUTEX_OP_ANDN:
		__futex_atomic_op("%1 = not(%4); %1 = and(%0,%1)\n", ret,
				  oldval, uaddr, oparg);
		अवरोध;
	हाल FUTEX_OP_XOR:
		__futex_atomic_op("%1 = xor(%0,%4)\n", ret, oldval, uaddr,
				  oparg);
		अवरोध;
	शेष:
		ret = -ENOSYS;
	पूर्ण

	अगर (!ret)
		*oval = oldval;

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक
futex_atomic_cmpxchg_inatomic(u32 *uval, u32 __user *uaddr, u32 oldval,
			      u32 newval)
अणु
	पूर्णांक prev;
	पूर्णांक ret;

	अगर (!access_ok(uaddr, माप(u32)))
		वापस -EFAULT;

	__यंत्र__ __अस्थिर__ (
	"1: %1 = memw_locked(%3)\n"
	"   {\n"
	"      p2 = cmp.eq(%1,%4)\n"
	"      if (!p2.new) jump:NT 3f\n"
	"   }\n"
	"2: memw_locked(%3,p2) = %5\n"
	"   if (!p2) jump 1b\n"
	"3:\n"
	".section .fixup,\"ax\"\n"
	"4: %0 = #%6\n"
	"   jump ##3b\n"
	".previous\n"
	".section __ex_table,\"a\"\n"
	".long 1b,4b,2b,4b\n"
	".previous\n"
	: "+r" (ret), "=&r" (prev), "+m" (*uaddr)
	: "r" (uaddr), "r" (oldval), "r" (newval), "i"(-EFAULT)
	: "p2", "memory");

	*uval = prev;
	वापस ret;
पूर्ण

#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर /* _ASM_HEXAGON_FUTEX_H */
