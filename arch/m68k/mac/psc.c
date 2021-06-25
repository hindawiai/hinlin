<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *	Apple Peripheral System Controller (PSC)
 *
 *	The PSC is used on the AV Macs to control IO functions not handled
 *	by the VIAs (Ethernet, DSP, SCC).
 *
 * TO DO:
 *
 * Try to figure out what's going on in pIFR5 and pIFR6. There seem to be
 * persisant पूर्णांकerrupt conditions in those रेजिस्टरs and I have no idea what
 * they are. Granted it करोesn't affect since we're not enabling any पूर्णांकerrupts
 * on those levels at the moment, but it would be nice to know. I have a feeling
 * they aren't actually पूर्णांकerrupt lines but data lines (to the DSP?)
 */

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/irq.h>

#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/macपूर्णांकosh.h>
#समावेश <यंत्र/macपूर्णांकs.h>
#समावेश <यंत्र/mac_psc.h>

#घोषणा DEBUG_PSC

अस्थिर __u8 *psc;
EXPORT_SYMBOL_GPL(psc);

/*
 * Debugging dump, used in various places to see what's going on.
 */

अटल व्योम psc_debug_dump(व्योम)
अणु
	पूर्णांक	i;

	अगर (!psc)
		वापस;

	क्रम (i = 0x30 ; i < 0x70 ; i += 0x10) अणु
		prपूर्णांकk(KERN_DEBUG "PSC #%d:  IFR = 0x%02X IER = 0x%02X\n",
			i >> 4,
			(पूर्णांक) psc_पढ़ो_byte(pIFRbase + i),
			(पूर्णांक) psc_पढ़ो_byte(pIERbase + i));
	पूर्ण
पूर्ण

/*
 * Try to समाप्त all DMA channels on the PSC. Not sure how this his
 * supposed to work; this is code lअगरted from macmace.c and then
 * expanded to cover what I think are the other 7 channels.
 */

अटल __init व्योम psc_dma_die_die_die(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0 ; i < 9 ; i++) अणु
		psc_ग_लिखो_word(PSC_CTL_BASE + (i << 4), 0x8800);
		psc_ग_लिखो_word(PSC_CTL_BASE + (i << 4), 0x1000);
		psc_ग_लिखो_word(PSC_CMD_BASE + (i << 5), 0x1100);
		psc_ग_लिखो_word(PSC_CMD_BASE + (i << 5) + 0x10, 0x1100);
	पूर्ण
पूर्ण

/*
 * Initialize the PSC. For now this just involves shutting करोwn all
 * पूर्णांकerrupt sources using the IERs.
 */

व्योम __init psc_init(व्योम)
अणु
	पूर्णांक i;

	अगर (macपूर्णांकosh_config->ident != MAC_MODEL_C660
	 && macपूर्णांकosh_config->ident != MAC_MODEL_Q840)
	अणु
		psc = शून्य;
		वापस;
	पूर्ण

	/*
	 * The PSC is always at the same spot, but using psc
	 * keeps things consistent with the psc_xxxx functions.
	 */

	psc = (व्योम *) PSC_BASE;

	pr_debug("PSC detected at %p\n", psc);

	psc_dma_die_die_die();

#अगर_घोषित DEBUG_PSC
	psc_debug_dump();
#पूर्ण_अगर
	/*
	 * Mask and clear all possible पूर्णांकerrupts
	 */

	क्रम (i = 0x30 ; i < 0x70 ; i += 0x10) अणु
		psc_ग_लिखो_byte(pIERbase + i, 0x0F);
		psc_ग_लिखो_byte(pIFRbase + i, 0x0F);
	पूर्ण
पूर्ण

/*
 * PSC पूर्णांकerrupt handler. It's a lot like the VIA पूर्णांकerrupt handler.
 */

अटल व्योम psc_irq(काष्ठा irq_desc *desc)
अणु
	अचिन्हित पूर्णांक offset = (अचिन्हित पूर्णांक)irq_desc_get_handler_data(desc);
	अचिन्हित पूर्णांक irq = irq_desc_get_irq(desc);
	पूर्णांक pIFR	= pIFRbase + offset;
	पूर्णांक pIER	= pIERbase + offset;
	पूर्णांक irq_num;
	अचिन्हित अक्षर irq_bit, events;

	events = psc_पढ़ो_byte(pIFR) & psc_पढ़ो_byte(pIER) & 0xF;
	अगर (!events)
		वापस;

	irq_num = irq << 3;
	irq_bit = 1;
	करो अणु
		अगर (events & irq_bit) अणु
			psc_ग_लिखो_byte(pIFR, irq_bit);
			generic_handle_irq(irq_num);
		पूर्ण
		irq_num++;
		irq_bit <<= 1;
	पूर्ण जबतक (events >= irq_bit);
पूर्ण

/*
 * Register the PSC पूर्णांकerrupt dispatchers क्रम स्वतःvector पूर्णांकerrupts 3-6.
 */

व्योम __init psc_रेजिस्टर_पूर्णांकerrupts(व्योम)
अणु
	irq_set_chained_handler_and_data(IRQ_AUTO_3, psc_irq, (व्योम *)0x30);
	irq_set_chained_handler_and_data(IRQ_AUTO_4, psc_irq, (व्योम *)0x40);
	irq_set_chained_handler_and_data(IRQ_AUTO_5, psc_irq, (व्योम *)0x50);
	irq_set_chained_handler_and_data(IRQ_AUTO_6, psc_irq, (व्योम *)0x60);
पूर्ण

व्योम psc_irq_enable(पूर्णांक irq) अणु
	पूर्णांक irq_src	= IRQ_SRC(irq);
	पूर्णांक irq_idx	= IRQ_IDX(irq);
	पूर्णांक pIER	= pIERbase + (irq_src << 4);

	psc_ग_लिखो_byte(pIER, (1 << irq_idx) | 0x80);
पूर्ण

व्योम psc_irq_disable(पूर्णांक irq) अणु
	पूर्णांक irq_src	= IRQ_SRC(irq);
	पूर्णांक irq_idx	= IRQ_IDX(irq);
	पूर्णांक pIER	= pIERbase + (irq_src << 4);

	psc_ग_लिखो_byte(pIER, 1 << irq_idx);
पूर्ण
