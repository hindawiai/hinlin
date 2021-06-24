<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Handle पूर्णांकerrupts from the SRM, assuming no additional weirdness.
 */

#समावेश <linux/init.h>
#समावेश <linux/sched.h>
#समावेश <linux/irq.h>

#समावेश "proto.h"
#समावेश "irq_impl.h"


/*
 * Is the palcode SMP safe? In other words: can we call cserve_ena/dis
 * at the same समय in multiple CPUs? To be safe I added a spinlock
 * but it can be हटाओd trivially अगर the palcode is robust against smp.
 */
DEFINE_SPINLOCK(srm_irq_lock);

अटल अंतरभूत व्योम
srm_enable_irq(काष्ठा irq_data *d)
अणु
	spin_lock(&srm_irq_lock);
	cserve_ena(d->irq - 16);
	spin_unlock(&srm_irq_lock);
पूर्ण

अटल व्योम
srm_disable_irq(काष्ठा irq_data *d)
अणु
	spin_lock(&srm_irq_lock);
	cserve_dis(d->irq - 16);
	spin_unlock(&srm_irq_lock);
पूर्ण

/* Handle पूर्णांकerrupts from the SRM, assuming no additional weirdness.  */
अटल काष्ठा irq_chip srm_irq_type = अणु
	.name		= "SRM",
	.irq_unmask	= srm_enable_irq,
	.irq_mask	= srm_disable_irq,
	.irq_mask_ack	= srm_disable_irq,
पूर्ण;

व्योम __init
init_srm_irqs(दीर्घ max, अचिन्हित दीर्घ ignore_mask)
अणु
	दीर्घ i;

	अगर (NR_IRQS <= 16)
		वापस;
	क्रम (i = 16; i < max; ++i) अणु
		अगर (i < 64 && ((ignore_mask >> i) & 1))
			जारी;
		irq_set_chip_and_handler(i, &srm_irq_type, handle_level_irq);
		irq_set_status_flags(i, IRQ_LEVEL);
	पूर्ण
पूर्ण

व्योम 
srm_device_पूर्णांकerrupt(अचिन्हित दीर्घ vector)
अणु
	पूर्णांक irq = (vector - 0x800) >> 4;
	handle_irq(irq);
पूर्ण
