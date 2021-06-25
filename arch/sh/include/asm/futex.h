<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SH_FUTEX_H
#घोषणा __ASM_SH_FUTEX_H

#समावेश <linux/futex.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/त्रुटिसं.स>

#अगर !defined(CONFIG_SMP)
#समावेश <यंत्र/futex-irq.h>
#या_अगर defined(CONFIG_CPU_J2)
#समावेश <यंत्र/futex-cas.h>
#या_अगर defined(CONFIG_CPU_SH4A)
#समावेश <यंत्र/futex-llsc.h>
#अन्यथा
#त्रुटि SMP not supported on this configuration.
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक
futex_atomic_cmpxchg_inatomic(u32 *uval, u32 __user *uaddr,
			      u32 oldval, u32 newval)
अणु
	अगर (!access_ok(uaddr, माप(u32)))
		वापस -EFAULT;

	वापस atomic_futex_op_cmpxchg_inatomic(uval, uaddr, oldval, newval);
पूर्ण

अटल अंतरभूत पूर्णांक arch_futex_atomic_op_inuser(पूर्णांक op, u32 oparg, पूर्णांक *oval,
		u32 __user *uaddr)
अणु
	u32 oldval, newval, prev;
	पूर्णांक ret;

	करो अणु
		ret = get_user(oldval, uaddr);

		अगर (ret) अवरोध;

		चयन (op) अणु
		हाल FUTEX_OP_SET:
			newval = oparg;
			अवरोध;
		हाल FUTEX_OP_ADD:
			newval = oldval + oparg;
			अवरोध;
		हाल FUTEX_OP_OR:
			newval = oldval | oparg;
			अवरोध;
		हाल FUTEX_OP_ANDN:
			newval = oldval & ~oparg;
			अवरोध;
		हाल FUTEX_OP_XOR:
			newval = oldval ^ oparg;
			अवरोध;
		शेष:
			ret = -ENOSYS;
			अवरोध;
		पूर्ण

		अगर (ret) अवरोध;

		ret = futex_atomic_cmpxchg_inatomic(&prev, uaddr, oldval, newval);
	पूर्ण जबतक (!ret && prev != oldval);

	अगर (!ret)
		*oval = oldval;

	वापस ret;
पूर्ण

#पूर्ण_अगर /* __ASM_SH_FUTEX_H */
