<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Baboon Custom IC Management
 *
 * The Baboon custom IC controls the IDE, PCMCIA and media bay on the
 * PowerBook 190. It multiplexes multiple पूर्णांकerrupt sources onto the
 * Nubus slot $C पूर्णांकerrupt.
 */

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/irq.h>

#समावेश <यंत्र/macपूर्णांकosh.h>
#समावेश <यंत्र/macपूर्णांकs.h>
#समावेश <यंत्र/mac_baboon.h>

पूर्णांक baboon_present;
अटल अस्थिर काष्ठा baboon *baboon;

/*
 * Baboon initialization.
 */

व्योम __init baboon_init(व्योम)
अणु
	अगर (macपूर्णांकosh_config->ident != MAC_MODEL_PB190) अणु
		baboon = शून्य;
		baboon_present = 0;
		वापस;
	पूर्ण

	baboon = (काष्ठा baboon *) BABOON_BASE;
	baboon_present = 1;

	pr_debug("Baboon detected at %p\n", baboon);
पूर्ण

/*
 * Baboon पूर्णांकerrupt handler.
 * XXX how करो you clear a pending IRQ? is it even necessary?
 */

अटल व्योम baboon_irq(काष्ठा irq_desc *desc)
अणु
	लघु events, irq_bit;
	पूर्णांक irq_num;

	events = baboon->mb_अगरr & 0x07;
	irq_num = IRQ_BABOON_0;
	irq_bit = 1;
	करो अणु
		अगर (events & irq_bit) अणु
			events &= ~irq_bit;
			generic_handle_irq(irq_num);
		पूर्ण
		++irq_num;
		irq_bit <<= 1;
	पूर्ण जबतक (events);
पूर्ण

/*
 * Register the Baboon पूर्णांकerrupt dispatcher on nubus slot $C.
 */

व्योम __init baboon_रेजिस्टर_पूर्णांकerrupts(व्योम)
अणु
	irq_set_chained_handler(IRQ_NUBUS_C, baboon_irq);
पूर्ण

/*
 * The means क्रम masking inभागidual Baboon पूर्णांकerrupts reमुख्यs a mystery.
 * However, since we only use the IDE IRQ, we can just enable/disable all
 * Baboon पूर्णांकerrupts. If/when we handle more than one Baboon IRQ, we must
 * either figure out how to mask them inभागidually or अन्यथा implement the
 * same workaround that's used क्रम NuBus slots (see nubus_disabled and
 * via_nubus_irq_shutकरोwn).
 */

व्योम baboon_irq_enable(पूर्णांक irq)
अणु
	mac_irq_enable(irq_get_irq_data(IRQ_NUBUS_C));
पूर्ण

व्योम baboon_irq_disable(पूर्णांक irq)
अणु
	mac_irq_disable(irq_get_irq_data(IRQ_NUBUS_C));
पूर्ण
