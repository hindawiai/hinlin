<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SH_FUTEX_IRQ_H
#घोषणा __ASM_SH_FUTEX_IRQ_H

अटल अंतरभूत पूर्णांक atomic_futex_op_cmpxchg_inatomic(u32 *uval,
						   u32 __user *uaddr,
						   u32 oldval, u32 newval)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;
	u32 prev = 0;

	local_irq_save(flags);

	ret = get_user(prev, uaddr);
	अगर (!ret && oldval == prev)
		ret = put_user(newval, uaddr);

	local_irq_restore(flags);

	*uval = prev;
	वापस ret;
पूर्ण

#पूर्ण_अगर /* __ASM_SH_FUTEX_IRQ_H */
