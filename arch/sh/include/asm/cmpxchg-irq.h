<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SH_CMPXCHG_IRQ_H
#घोषणा __ASM_SH_CMPXCHG_IRQ_H

#समावेश <linux/irqflags.h>

अटल अंतरभूत अचिन्हित दीर्घ xchg_u32(अस्थिर u32 *m, अचिन्हित दीर्घ val)
अणु
	अचिन्हित दीर्घ flags, retval;

	local_irq_save(flags);
	retval = *m;
	*m = val;
	local_irq_restore(flags);
	वापस retval;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ xchg_u16(अस्थिर u16 *m, अचिन्हित दीर्घ val)
अणु
	अचिन्हित दीर्घ flags, retval;

	local_irq_save(flags);
	retval = *m;
	*m = val;
	local_irq_restore(flags);
	वापस retval;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ xchg_u8(अस्थिर u8 *m, अचिन्हित दीर्घ val)
अणु
	अचिन्हित दीर्घ flags, retval;

	local_irq_save(flags);
	retval = *m;
	*m = val & 0xff;
	local_irq_restore(flags);
	वापस retval;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ __cmpxchg_u32(अस्थिर पूर्णांक *m, अचिन्हित दीर्घ old,
	अचिन्हित दीर्घ new)
अणु
	__u32 retval;
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	retval = *m;
	अगर (retval == old)
		*m = new;
	local_irq_restore(flags);       /* implies memory barrier  */
	वापस retval;
पूर्ण

#पूर्ण_अगर /* __ASM_SH_CMPXCHG_IRQ_H */
