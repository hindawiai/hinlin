<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *      linux/arch/alpha/kernel/irq_i8259.c
 *
 * This is the 'legacy' 8259A Programmable Interrupt Controller,
 * present in the majority of PC/AT boxes.
 *
 * Started hacking from linux-2.3.30pre6/arch/i386/kernel/i8259.c.
 */

#समावेश <linux/init.h>
#समावेश <linux/cache.h>
#समावेश <linux/sched.h>
#समावेश <linux/irq.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश <यंत्र/पन.स>

#समावेश "proto.h"
#समावेश "irq_impl.h"


/* Note mask bit is true क्रम DISABLED irqs.  */
अटल अचिन्हित पूर्णांक cached_irq_mask = 0xffff;
अटल DEFINE_SPINLOCK(i8259_irq_lock);

अटल अंतरभूत व्योम
i8259_update_irq_hw(अचिन्हित पूर्णांक irq, अचिन्हित दीर्घ mask)
अणु
	पूर्णांक port = 0x21;
	अगर (irq & 8) mask >>= 8;
	अगर (irq & 8) port = 0xA1;
	outb(mask, port);
पूर्ण

अंतरभूत व्योम
i8259a_enable_irq(काष्ठा irq_data *d)
अणु
	spin_lock(&i8259_irq_lock);
	i8259_update_irq_hw(d->irq, cached_irq_mask &= ~(1 << d->irq));
	spin_unlock(&i8259_irq_lock);
पूर्ण

अटल अंतरभूत व्योम
__i8259a_disable_irq(अचिन्हित पूर्णांक irq)
अणु
	i8259_update_irq_hw(irq, cached_irq_mask |= 1 << irq);
पूर्ण

व्योम
i8259a_disable_irq(काष्ठा irq_data *d)
अणु
	spin_lock(&i8259_irq_lock);
	__i8259a_disable_irq(d->irq);
	spin_unlock(&i8259_irq_lock);
पूर्ण

व्योम
i8259a_mask_and_ack_irq(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक irq = d->irq;

	spin_lock(&i8259_irq_lock);
	__i8259a_disable_irq(irq);

	/* Ack the पूर्णांकerrupt making it the lowest priority.  */
	अगर (irq >= 8) अणु
		outb(0xE0 | (irq - 8), 0xa0);   /* ack the slave */
		irq = 2;
	पूर्ण
	outb(0xE0 | irq, 0x20);			/* ack the master */
	spin_unlock(&i8259_irq_lock);
पूर्ण

काष्ठा irq_chip i8259a_irq_type = अणु
	.name		= "XT-PIC",
	.irq_unmask	= i8259a_enable_irq,
	.irq_mask	= i8259a_disable_irq,
	.irq_mask_ack	= i8259a_mask_and_ack_irq,
पूर्ण;

व्योम __init
init_i8259a_irqs(व्योम)
अणु
	दीर्घ i;

	outb(0xff, 0x21);	/* mask all of 8259A-1 */
	outb(0xff, 0xA1);	/* mask all of 8259A-2 */

	क्रम (i = 0; i < 16; i++) अणु
		irq_set_chip_and_handler(i, &i8259a_irq_type, handle_level_irq);
	पूर्ण

	अगर (request_irq(2, no_action, 0, "cascade", शून्य))
		pr_err("Failed to request irq 2 (cascade)\n");
पूर्ण


#अगर defined(CONFIG_ALPHA_GENERIC)
# define IACK_SC	alpha_mv.iack_sc
#या_अगर defined(CONFIG_ALPHA_APECS)
# define IACK_SC	APECS_IACK_SC
#या_अगर defined(CONFIG_ALPHA_LCA)
# define IACK_SC	LCA_IACK_SC
#या_अगर defined(CONFIG_ALPHA_CIA)
# define IACK_SC	CIA_IACK_SC
#या_अगर defined(CONFIG_ALPHA_PYXIS)
# define IACK_SC	PYXIS_IACK_SC
#या_अगर defined(CONFIG_ALPHA_TITAN)
# define IACK_SC	TITAN_IACK_SC
#या_अगर defined(CONFIG_ALPHA_TSUNAMI)
# define IACK_SC	TSUNAMI_IACK_SC
#या_अगर defined(CONFIG_ALPHA_IRONGATE)
# define IACK_SC        IRONGATE_IACK_SC
#पूर्ण_अगर
/* Note that CONFIG_ALPHA_POLARIS is पूर्णांकentionally left out here, since
   sys_rx164 wants to use isa_no_iack_sc_device_पूर्णांकerrupt क्रम some reason.  */

#अगर defined(IACK_SC)
व्योम
isa_device_पूर्णांकerrupt(अचिन्हित दीर्घ vector)
अणु
	/*
	 * Generate a PCI पूर्णांकerrupt acknowledge cycle.  The PIC will
	 * respond with the पूर्णांकerrupt vector of the highest priority
	 * पूर्णांकerrupt that is pending.  The PALcode sets up the
	 * पूर्णांकerrupts vectors such that irq level L generates vector L.
	 */
	पूर्णांक j = *(vuip) IACK_SC;
	j &= 0xff;
	handle_irq(j);
पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_ALPHA_GENERIC) || !defined(IACK_SC)
व्योम
isa_no_iack_sc_device_पूर्णांकerrupt(अचिन्हित दीर्घ vector)
अणु
	अचिन्हित दीर्घ pic;

	/*
	 * It seems to me that the probability of two or more *device*
	 * पूर्णांकerrupts occurring at almost exactly the same समय is
	 * pretty low.  So why pay the price of checking क्रम
	 * additional पूर्णांकerrupts here अगर the common हाल can be
	 * handled so much easier?
	 */
	/* 
	 *  The first पढ़ो of gives you *all* पूर्णांकerrupting lines.
	 *  Thereक्रमe, पढ़ो the mask रेजिस्टर and and out those lines
	 *  not enabled.  Note that some करोcumentation has 21 and a1 
	 *  ग_लिखो only.  This is not true.
	 */
	pic = inb(0x20) | (inb(0xA0) << 8);	/* पढ़ो isr */
	pic &= 0xFFFB;				/* mask out cascade & hibits */

	जबतक (pic) अणु
		पूर्णांक j = ffz(~pic);
		pic &= pic - 1;
		handle_irq(j);
	पूर्ण
पूर्ण
#पूर्ण_अगर
