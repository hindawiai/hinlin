<शैली गुरु>
/*
 *  linux/arch/m68k/amiga/cia.c - CIA support
 *
 *  Copyright (C) 1996 Roman Zippel
 *
 *  The concept of some functions bases on the original Amiga OS function
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/init.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>

#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/amigahw.h>
#समावेश <यंत्र/amigaपूर्णांकs.h>

काष्ठा ciabase अणु
	अस्थिर काष्ठा CIA *cia;
	अचिन्हित अक्षर icr_mask, icr_data;
	अचिन्हित लघु पूर्णांक_mask;
	पूर्णांक handler_irq, cia_irq, server_irq;
	अक्षर *name;
पूर्ण ciaa_base = अणु
	.cia		= &ciaa,
	.पूर्णांक_mask	= IF_PORTS,
	.handler_irq	= IRQ_AMIGA_PORTS,
	.cia_irq	= IRQ_AMIGA_CIAA,
	.name		= "CIAA"
पूर्ण, ciab_base = अणु
	.cia		= &ciab,
	.पूर्णांक_mask	= IF_EXTER,
	.handler_irq	= IRQ_AMIGA_EXTER,
	.cia_irq	= IRQ_AMIGA_CIAB,
	.name		= "CIAB"
पूर्ण;

/*
 *  Cause or clear CIA पूर्णांकerrupts, वापस old पूर्णांकerrupt status.
 */

अचिन्हित अक्षर cia_set_irq(काष्ठा ciabase *base, अचिन्हित अक्षर mask)
अणु
	अचिन्हित अक्षर old;

	old = (base->icr_data |= base->cia->icr);
	अगर (mask & CIA_ICR_SETCLR)
		base->icr_data |= mask;
	अन्यथा
		base->icr_data &= ~mask;
	अगर (base->icr_data & base->icr_mask)
		amiga_custom.पूर्णांकreq = IF_SETCLR | base->पूर्णांक_mask;
	वापस old & base->icr_mask;
पूर्ण

/*
 *  Enable or disable CIA पूर्णांकerrupts, वापस old पूर्णांकerrupt mask,
 */

अचिन्हित अक्षर cia_able_irq(काष्ठा ciabase *base, अचिन्हित अक्षर mask)
अणु
	अचिन्हित अक्षर old;

	old = base->icr_mask;
	base->icr_data |= base->cia->icr;
	base->cia->icr = mask;
	अगर (mask & CIA_ICR_SETCLR)
		base->icr_mask |= mask;
	अन्यथा
		base->icr_mask &= ~mask;
	base->icr_mask &= CIA_ICR_ALL;
	अगर (base->icr_data & base->icr_mask)
		amiga_custom.पूर्णांकreq = IF_SETCLR | base->पूर्णांक_mask;
	वापस old;
पूर्ण

अटल irqवापस_t cia_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा ciabase *base = dev_id;
	पूर्णांक mach_irq;
	अचिन्हित अक्षर पूर्णांकs;
	अचिन्हित दीर्घ flags;

	/* Interrupts get disabled जबतक the समयr irq flag is cleared and
	 * the समयr पूर्णांकerrupt serviced.
	 */
	mach_irq = base->cia_irq;
	local_irq_save(flags);
	पूर्णांकs = cia_set_irq(base, CIA_ICR_ALL);
	amiga_custom.पूर्णांकreq = base->पूर्णांक_mask;
	अगर (पूर्णांकs & 1)
		generic_handle_irq(mach_irq);
	local_irq_restore(flags);
	mach_irq++, पूर्णांकs >>= 1;
	क्रम (; पूर्णांकs; mach_irq++, पूर्णांकs >>= 1) अणु
		अगर (पूर्णांकs & 1)
			generic_handle_irq(mach_irq);
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम cia_irq_enable(काष्ठा irq_data *data)
अणु
	अचिन्हित पूर्णांक irq = data->irq;
	अचिन्हित अक्षर mask;

	अगर (irq >= IRQ_AMIGA_CIAB) अणु
		mask = 1 << (irq - IRQ_AMIGA_CIAB);
		cia_set_irq(&ciab_base, mask);
		cia_able_irq(&ciab_base, CIA_ICR_SETCLR | mask);
	पूर्ण अन्यथा अणु
		mask = 1 << (irq - IRQ_AMIGA_CIAA);
		cia_set_irq(&ciaa_base, mask);
		cia_able_irq(&ciaa_base, CIA_ICR_SETCLR | mask);
	पूर्ण
पूर्ण

अटल व्योम cia_irq_disable(काष्ठा irq_data *data)
अणु
	अचिन्हित पूर्णांक irq = data->irq;

	अगर (irq >= IRQ_AMIGA_CIAB)
		cia_able_irq(&ciab_base, 1 << (irq - IRQ_AMIGA_CIAB));
	अन्यथा
		cia_able_irq(&ciaa_base, 1 << (irq - IRQ_AMIGA_CIAA));
पूर्ण

अटल काष्ठा irq_chip cia_irq_chip = अणु
	.name		= "cia",
	.irq_enable	= cia_irq_enable,
	.irq_disable	= cia_irq_disable,
पूर्ण;

/*
 * Override स्वतः irq 2 & 6 and use them as general chain
 * क्रम बाह्यal पूर्णांकerrupts, we link the CIA पूर्णांकerrupt sources
 * पूर्णांकo this chain.
 */

अटल व्योम स्वतः_irq_enable(काष्ठा irq_data *data)
अणु
	चयन (data->irq) अणु
	हाल IRQ_AUTO_2:
		amiga_custom.पूर्णांकena = IF_SETCLR | IF_PORTS;
		अवरोध;
	हाल IRQ_AUTO_6:
		amiga_custom.पूर्णांकena = IF_SETCLR | IF_EXTER;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम स्वतः_irq_disable(काष्ठा irq_data *data)
अणु
	चयन (data->irq) अणु
	हाल IRQ_AUTO_2:
		amiga_custom.पूर्णांकena = IF_PORTS;
		अवरोध;
	हाल IRQ_AUTO_6:
		amiga_custom.पूर्णांकena = IF_EXTER;
		अवरोध;
	पूर्ण
पूर्ण

अटल काष्ठा irq_chip स्वतः_irq_chip = अणु
	.name		= "auto",
	.irq_enable	= स्वतः_irq_enable,
	.irq_disable	= स्वतः_irq_disable,
पूर्ण;

व्योम __init cia_init_IRQ(काष्ठा ciabase *base)
अणु
	m68k_setup_irq_controller(&cia_irq_chip, handle_simple_irq,
				  base->cia_irq, CIA_IRQS);

	/* clear any pending पूर्णांकerrupt and turn off all पूर्णांकerrupts */
	cia_set_irq(base, CIA_ICR_ALL);
	cia_able_irq(base, CIA_ICR_ALL);

	/* override स्वतः पूर्णांक and install CIA handler */
	m68k_setup_irq_controller(&स्वतः_irq_chip, handle_simple_irq,
				  base->handler_irq, 1);
	m68k_irq_startup_irq(base->handler_irq);
	अगर (request_irq(base->handler_irq, cia_handler, IRQF_SHARED,
			base->name, base))
		pr_err("Couldn't register %s interrupt\n", base->name);
पूर्ण
