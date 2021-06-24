<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *	linux/arch/alpha/kernel/irq_pyxis.c
 *
 * Based on code written by David A Rusling (david.rusling@reo.mts.dec.com).
 *
 * IRQ Code common to all PYXIS core logic chips.
 */

#समावेश <linux/init.h>
#समावेश <linux/sched.h>
#समावेश <linux/irq.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/core_cia.h>

#समावेश "proto.h"
#समावेश "irq_impl.h"


/* Note mask bit is true क्रम ENABLED irqs.  */
अटल अचिन्हित दीर्घ cached_irq_mask;

अटल अंतरभूत व्योम
pyxis_update_irq_hw(अचिन्हित दीर्घ mask)
अणु
	*(vulp)PYXIS_INT_MASK = mask;
	mb();
	*(vulp)PYXIS_INT_MASK;
पूर्ण

अटल अंतरभूत व्योम
pyxis_enable_irq(काष्ठा irq_data *d)
अणु
	pyxis_update_irq_hw(cached_irq_mask |= 1UL << (d->irq - 16));
पूर्ण

अटल व्योम
pyxis_disable_irq(काष्ठा irq_data *d)
अणु
	pyxis_update_irq_hw(cached_irq_mask &= ~(1UL << (d->irq - 16)));
पूर्ण

अटल व्योम
pyxis_mask_and_ack_irq(काष्ठा irq_data *d)
अणु
	अचिन्हित दीर्घ bit = 1UL << (d->irq - 16);
	अचिन्हित दीर्घ mask = cached_irq_mask &= ~bit;

	/* Disable the पूर्णांकerrupt.  */
	*(vulp)PYXIS_INT_MASK = mask;
	wmb();
	/* Ack PYXIS PCI पूर्णांकerrupt.  */
	*(vulp)PYXIS_INT_REQ = bit;
	mb();
	/* Re-पढ़ो to क्रमce both ग_लिखोs.  */
	*(vulp)PYXIS_INT_MASK;
पूर्ण

अटल काष्ठा irq_chip pyxis_irq_type = अणु
	.name		= "PYXIS",
	.irq_mask_ack	= pyxis_mask_and_ack_irq,
	.irq_mask	= pyxis_disable_irq,
	.irq_unmask	= pyxis_enable_irq,
पूर्ण;

व्योम 
pyxis_device_पूर्णांकerrupt(अचिन्हित दीर्घ vector)
अणु
	अचिन्हित दीर्घ pld;
	अचिन्हित पूर्णांक i;

	/* Read the पूर्णांकerrupt summary रेजिस्टर of PYXIS */
	pld = *(vulp)PYXIS_INT_REQ;
	pld &= cached_irq_mask;

	/*
	 * Now क्रम every possible bit set, work through them and call
	 * the appropriate पूर्णांकerrupt handler.
	 */
	जबतक (pld) अणु
		i = ffz(~pld);
		pld &= pld - 1; /* clear least bit set */
		अगर (i == 7)
			isa_device_पूर्णांकerrupt(vector);
		अन्यथा
			handle_irq(16+i);
	पूर्ण
पूर्ण

व्योम __init
init_pyxis_irqs(अचिन्हित दीर्घ ignore_mask)
अणु
	दीर्घ i;

	*(vulp)PYXIS_INT_MASK = 0;		/* disable all */
	*(vulp)PYXIS_INT_REQ  = -1;		/* flush all */
	mb();

	/* Send -INTA pulses to clear any pending पूर्णांकerrupts ...*/
	*(vuip) CIA_IACK_SC;

	क्रम (i = 16; i < 48; ++i) अणु
		अगर ((ignore_mask >> i) & 1)
			जारी;
		irq_set_chip_and_handler(i, &pyxis_irq_type, handle_level_irq);
		irq_set_status_flags(i, IRQ_LEVEL);
	पूर्ण

	अगर (request_irq(16 + 7, no_action, 0, "isa-cascade", शून्य))
		pr_err("Failed to register isa-cascade interrupt\n");
पूर्ण
