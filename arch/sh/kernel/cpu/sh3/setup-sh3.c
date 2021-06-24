<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Shared SH3 Setup code
 *
 *  Copyright (C) 2008  Magnus Damm
 */

#समावेश <linux/init.h>
#समावेश <linux/irq.h>
#समावेश <linux/पन.स>
#समावेश <यंत्र/platक्रमm_early.h>

/* All SH3 devices are equipped with IRQ0->5 (except sh7708) */

क्रमागत अणु
	UNUSED = 0,

	/* पूर्णांकerrupt sources */
	IRQ0, IRQ1, IRQ2, IRQ3, IRQ4, IRQ5,
पूर्ण;

अटल काष्ठा पूर्णांकc_vect vectors_irq0123[] __initdata = अणु
	INTC_VECT(IRQ0, 0x600), INTC_VECT(IRQ1, 0x620),
	INTC_VECT(IRQ2, 0x640), INTC_VECT(IRQ3, 0x660),
पूर्ण;

अटल काष्ठा पूर्णांकc_vect vectors_irq45[] __initdata = अणु
	INTC_VECT(IRQ4, 0x680), INTC_VECT(IRQ5, 0x6a0),
पूर्ण;

अटल काष्ठा पूर्णांकc_prio_reg prio_रेजिस्टरs[] __initdata = अणु
	अणु 0xa4000016, 0, 16, 4, /* IPRC */ अणु IRQ3, IRQ2, IRQ1, IRQ0 पूर्ण पूर्ण,
	अणु 0xa4000018, 0, 16, 4, /* IPRD */ अणु 0, 0, IRQ5, IRQ4 पूर्ण पूर्ण,
पूर्ण;

अटल काष्ठा पूर्णांकc_mask_reg ack_रेजिस्टरs[] __initdata = अणु
	अणु 0xa4000004, 0, 8, /* IRR0 */
	  अणु 0, 0, IRQ5, IRQ4, IRQ3, IRQ2, IRQ1, IRQ0 पूर्ण पूर्ण,
पूर्ण;

अटल काष्ठा पूर्णांकc_sense_reg sense_रेजिस्टरs[] __initdata = अणु
	अणु 0xa4000010, 16, 2, अणु 0, 0, IRQ5, IRQ4, IRQ3, IRQ2, IRQ1, IRQ0 पूर्ण पूर्ण,
पूर्ण;

अटल DECLARE_INTC_DESC_ACK(पूर्णांकc_desc_irq0123, "sh3-irq0123",
			     vectors_irq0123, शून्य, शून्य,
			     prio_रेजिस्टरs, sense_रेजिस्टरs, ack_रेजिस्टरs);

अटल DECLARE_INTC_DESC_ACK(पूर्णांकc_desc_irq45, "sh3-irq45",
			     vectors_irq45, शून्य, शून्य,
			     prio_रेजिस्टरs, sense_रेजिस्टरs, ack_रेजिस्टरs);

#घोषणा INTC_ICR1		0xa4000010UL
#घोषणा INTC_ICR1_IRQLVL	(1<<14)

व्योम __init plat_irq_setup_pins(पूर्णांक mode)
अणु
	अगर (mode == IRQ_MODE_IRQ) अणु
		__raw_ग_लिखोw(__raw_पढ़ोw(INTC_ICR1) & ~INTC_ICR1_IRQLVL, INTC_ICR1);
		रेजिस्टर_पूर्णांकc_controller(&पूर्णांकc_desc_irq0123);
		वापस;
	पूर्ण
	BUG();
पूर्ण

व्योम __init plat_irq_setup_sh3(व्योम)
अणु
	रेजिस्टर_पूर्णांकc_controller(&पूर्णांकc_desc_irq45);
पूर्ण
