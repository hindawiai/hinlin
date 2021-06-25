<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_PARISC_FUTEX_H
#घोषणा _ASM_PARISC_FUTEX_H

#अगर_घोषित __KERNEL__

#समावेश <linux/futex.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/atomic.h>
#समावेश <यंत्र/त्रुटिसं.स>

/* The following has to match the LWS code in syscall.S.  We have
   sixteen four-word locks. */

अटल अंतरभूत व्योम
_futex_spin_lock_irqsave(u32 __user *uaddr, अचिन्हित दीर्घ पूर्णांक *flags)
अणु
	बाह्य u32 lws_lock_start[];
	दीर्घ index = ((दीर्घ)uaddr & 0x3f8) >> 1;
	arch_spinlock_t *s = (arch_spinlock_t *)&lws_lock_start[index];
	local_irq_save(*flags);
	arch_spin_lock(s);
पूर्ण

अटल अंतरभूत व्योम
_futex_spin_unlock_irqrestore(u32 __user *uaddr, अचिन्हित दीर्घ पूर्णांक *flags)
अणु
	बाह्य u32 lws_lock_start[];
	दीर्घ index = ((दीर्घ)uaddr & 0x3f8) >> 1;
	arch_spinlock_t *s = (arch_spinlock_t *)&lws_lock_start[index];
	arch_spin_unlock(s);
	local_irq_restore(*flags);
पूर्ण

अटल अंतरभूत पूर्णांक
arch_futex_atomic_op_inuser(पूर्णांक op, पूर्णांक oparg, पूर्णांक *oval, u32 __user *uaddr)
अणु
	अचिन्हित दीर्घ पूर्णांक flags;
	पूर्णांक oldval, ret;
	u32 पंचांगp;

	_futex_spin_lock_irqsave(uaddr, &flags);

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
	_futex_spin_unlock_irqrestore(uaddr, &flags);

	अगर (!ret)
		*oval = oldval;

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक
futex_atomic_cmpxchg_inatomic(u32 *uval, u32 __user *uaddr,
			      u32 oldval, u32 newval)
अणु
	u32 val;
	अचिन्हित दीर्घ flags;

	/* futex.c wants to करो a cmpxchg_inatomic on kernel शून्य, which is
	 * our gateway page, and causes no end of trouble...
	 */
	अगर (uaccess_kernel() && !uaddr)
		वापस -EFAULT;

	अगर (!access_ok(uaddr, माप(u32)))
		वापस -EFAULT;

	/* HPPA has no cmpxchg in hardware and thereक्रमe the
	 * best we can करो here is use an array of locks. The
	 * lock selected is based on a hash of the userspace
	 * address. This should scale to a couple of CPUs.
	 */

	_futex_spin_lock_irqsave(uaddr, &flags);
	अगर (unlikely(get_user(val, uaddr) != 0)) अणु
		_futex_spin_unlock_irqrestore(uaddr, &flags);
		वापस -EFAULT;
	पूर्ण

	अगर (val == oldval && unlikely(put_user(newval, uaddr) != 0)) अणु
		_futex_spin_unlock_irqrestore(uaddr, &flags);
		वापस -EFAULT;
	पूर्ण

	*uval = val;
	_futex_spin_unlock_irqrestore(uaddr, &flags);

	वापस 0;
पूर्ण

#पूर्ण_अगर /*__KERNEL__*/
#पूर्ण_अगर /*_ASM_PARISC_FUTEX_H*/
