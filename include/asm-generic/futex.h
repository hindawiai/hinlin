<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_GENERIC_FUTEX_H
#घोषणा _ASM_GENERIC_FUTEX_H

#समावेश <linux/futex.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/त्रुटिसं.स>

#अगर_अघोषित CONFIG_SMP
/*
 * The following implementation only क्रम uniprocessor machines.
 * It relies on preempt_disable() ensuring mutual exclusion.
 *
 */

/**
 * arch_futex_atomic_op_inuser() - Atomic arithmetic operation with स्थिरant
 *			  argument and comparison of the previous
 *			  futex value with another स्थिरant.
 *
 * @encoded_op:	encoded operation to execute
 * @uaddr:	poपूर्णांकer to user space address
 *
 * Return:
 * 0 - On success
 * -EFAULT - User access resulted in a page fault
 * -EAGAIN - Atomic operation was unable to complete due to contention
 * -ENOSYS - Operation not supported
 */
अटल अंतरभूत पूर्णांक
arch_futex_atomic_op_inuser(पूर्णांक op, u32 oparg, पूर्णांक *oval, u32 __user *uaddr)
अणु
	पूर्णांक oldval, ret;
	u32 पंचांगp;

	preempt_disable();

	ret = -EFAULT;
	अगर (unlikely(get_user(oldval, uaddr) != 0))
		जाओ out_pagefault_enable;

	ret = 0;
	पंचांगp = oldval;

	चयन (op) अणु
	हाल FUTEX_OP_SET:
		पंचांगp = oparg;
		अवरोध;
	हाल FUTEX_OP_ADD:
		पंचांगp += oparg;
		अवरोध;
	हाल FUTEX_OP_OR:
		पंचांगp |= oparg;
		अवरोध;
	हाल FUTEX_OP_ANDN:
		पंचांगp &= ~oparg;
		अवरोध;
	हाल FUTEX_OP_XOR:
		पंचांगp ^= oparg;
		अवरोध;
	शेष:
		ret = -ENOSYS;
	पूर्ण

	अगर (ret == 0 && unlikely(put_user(पंचांगp, uaddr) != 0))
		ret = -EFAULT;

out_pagefault_enable:
	preempt_enable();

	अगर (ret == 0)
		*oval = oldval;

	वापस ret;
पूर्ण

/**
 * futex_atomic_cmpxchg_inatomic() - Compare and exchange the content of the
 *				uaddr with newval अगर the current value is
 *				oldval.
 * @uval:	poपूर्णांकer to store content of @uaddr
 * @uaddr:	poपूर्णांकer to user space address
 * @oldval:	old value
 * @newval:	new value to store to @uaddr
 *
 * Return:
 * 0 - On success
 * -EFAULT - User access resulted in a page fault
 * -EAGAIN - Atomic operation was unable to complete due to contention
 * -ENOSYS - Function not implemented (only अगर !HAVE_FUTEX_CMPXCHG)
 */
अटल अंतरभूत पूर्णांक
futex_atomic_cmpxchg_inatomic(u32 *uval, u32 __user *uaddr,
			      u32 oldval, u32 newval)
अणु
	u32 val;

	preempt_disable();
	अगर (unlikely(get_user(val, uaddr) != 0)) अणु
		preempt_enable();
		वापस -EFAULT;
	पूर्ण

	अगर (val == oldval && unlikely(put_user(newval, uaddr) != 0)) अणु
		preempt_enable();
		वापस -EFAULT;
	पूर्ण

	*uval = val;
	preempt_enable();

	वापस 0;
पूर्ण

#अन्यथा
अटल अंतरभूत पूर्णांक
arch_futex_atomic_op_inuser(पूर्णांक op, u32 oparg, पूर्णांक *oval, u32 __user *uaddr)
अणु
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत पूर्णांक
futex_atomic_cmpxchg_inatomic(u32 *uval, u32 __user *uaddr,
			      u32 oldval, u32 newval)
अणु
	वापस -ENOSYS;
पूर्ण

#पूर्ण_अगर /* CONFIG_SMP */
#पूर्ण_अगर
