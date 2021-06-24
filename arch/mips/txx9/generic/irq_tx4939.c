<शैली गुरु>
/*
 * TX4939 irq routines
 * Based on linux/arch/mips/kernel/irq_txx9.c,
 *	    and RBTX49xx patch from CELF patch archive.
 *
 * Copyright 2001, 2003-2005 MontaVista Software Inc.
 * Author: MontaVista Software, Inc.
 *	   ahennessy@mvista.com
 *	   source@mvista.com
 * Copyright (C) 2000-2001,2005-2007 Toshiba Corporation
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */
/*
 * TX4939 defines 64 IRQs.
 * Similer to irq_txx9.c but dअगरferent रेजिस्टर layouts.
 */
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/types.h>
#समावेश <यंत्र/irq_cpu.h>
#समावेश <यंत्र/txx9irq.h>
#समावेश <यंत्र/txx9/tx4939.h>

/* IRCER : Int. Control Enable */
#घोषणा TXx9_IRCER_ICE	0x00000001

/* IRCR : Int. Control */
#घोषणा TXx9_IRCR_LOW	0x00000000
#घोषणा TXx9_IRCR_HIGH	0x00000001
#घोषणा TXx9_IRCR_DOWN	0x00000002
#घोषणा TXx9_IRCR_UP	0x00000003
#घोषणा TXx9_IRCR_EDGE(cr)	((cr) & 0x00000002)

/* IRSCR : Int. Status Control */
#घोषणा TXx9_IRSCR_EIClrE	0x00000100
#घोषणा TXx9_IRSCR_EIClr_MASK	0x0000000f

/* IRCSR : Int. Current Status */
#घोषणा TXx9_IRCSR_IF	0x00010000

#घोषणा irc_dlevel	0
#घोषणा irc_elevel	1

अटल काष्ठा अणु
	अचिन्हित अक्षर level;
	अचिन्हित अक्षर mode;
पूर्ण tx4939irq[TX4939_NUM_IR] __पढ़ो_mostly;

अटल व्योम tx4939_irq_unmask(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक irq_nr = d->irq - TXX9_IRQ_BASE;
	u32 __iomem *lvlp;
	पूर्णांक ofs;
	अगर (irq_nr < 32) अणु
		irq_nr--;
		lvlp = &tx4939_ircptr->lvl[(irq_nr % 16) / 2].r;
	पूर्ण अन्यथा अणु
		irq_nr -= 32;
		lvlp = &tx4939_ircptr->lvl[8 + (irq_nr % 16) / 2].r;
	पूर्ण
	ofs = (irq_nr & 16) + (irq_nr & 1) * 8;
	__raw_ग_लिखोl((__raw_पढ़ोl(lvlp) & ~(0xff << ofs))
		     | (tx4939irq[irq_nr].level << ofs),
		     lvlp);
पूर्ण

अटल अंतरभूत व्योम tx4939_irq_mask(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक irq_nr = d->irq - TXX9_IRQ_BASE;
	u32 __iomem *lvlp;
	पूर्णांक ofs;
	अगर (irq_nr < 32) अणु
		irq_nr--;
		lvlp = &tx4939_ircptr->lvl[(irq_nr % 16) / 2].r;
	पूर्ण अन्यथा अणु
		irq_nr -= 32;
		lvlp = &tx4939_ircptr->lvl[8 + (irq_nr % 16) / 2].r;
	पूर्ण
	ofs = (irq_nr & 16) + (irq_nr & 1) * 8;
	__raw_ग_लिखोl((__raw_पढ़ोl(lvlp) & ~(0xff << ofs))
		     | (irc_dlevel << ofs),
		     lvlp);
	mmiowb();
पूर्ण

अटल व्योम tx4939_irq_mask_ack(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक irq_nr = d->irq - TXX9_IRQ_BASE;

	tx4939_irq_mask(d);
	अगर (TXx9_IRCR_EDGE(tx4939irq[irq_nr].mode)) अणु
		irq_nr--;
		/* clear edge detection */
		__raw_ग_लिखोl((TXx9_IRSCR_EIClrE | (irq_nr & 0xf))
			     << (irq_nr & 0x10),
			     &tx4939_ircptr->edc.r);
	पूर्ण
पूर्ण

अटल पूर्णांक tx4939_irq_set_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक flow_type)
अणु
	अचिन्हित पूर्णांक irq_nr = d->irq - TXX9_IRQ_BASE;
	u32 cr;
	u32 __iomem *crp;
	पूर्णांक ofs;
	पूर्णांक mode;

	अगर (flow_type & IRQF_TRIGGER_PROBE)
		वापस 0;
	चयन (flow_type & IRQF_TRIGGER_MASK) अणु
	हाल IRQF_TRIGGER_RISING:
		mode = TXx9_IRCR_UP;
		अवरोध;
	हाल IRQF_TRIGGER_FALLING:
		mode = TXx9_IRCR_DOWN;
		अवरोध;
	हाल IRQF_TRIGGER_HIGH:
		mode = TXx9_IRCR_HIGH;
		अवरोध;
	हाल IRQF_TRIGGER_LOW:
		mode = TXx9_IRCR_LOW;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	अगर (irq_nr < 32) अणु
		irq_nr--;
		crp = &tx4939_ircptr->dm[(irq_nr & 8) >> 3].r;
	पूर्ण अन्यथा अणु
		irq_nr -= 32;
		crp = &tx4939_ircptr->dm2[((irq_nr & 8) >> 3)].r;
	पूर्ण
	ofs = (((irq_nr & 16) >> 1) | (irq_nr & (8 - 1))) * 2;
	cr = __raw_पढ़ोl(crp);
	cr &= ~(0x3 << ofs);
	cr |= (mode & 0x3) << ofs;
	__raw_ग_लिखोl(cr, crp);
	tx4939irq[irq_nr].mode = mode;
	वापस 0;
पूर्ण

अटल काष्ठा irq_chip tx4939_irq_chip = अणु
	.name		= "TX4939",
	.irq_ack	= tx4939_irq_mask_ack,
	.irq_mask	= tx4939_irq_mask,
	.irq_mask_ack	= tx4939_irq_mask_ack,
	.irq_unmask	= tx4939_irq_unmask,
	.irq_set_type	= tx4939_irq_set_type,
पूर्ण;

अटल पूर्णांक tx4939_irq_set_pri(पूर्णांक irc_irq, पूर्णांक new_pri)
अणु
	पूर्णांक old_pri;

	अगर ((अचिन्हित पूर्णांक)irc_irq >= TX4939_NUM_IR)
		वापस 0;
	old_pri = tx4939irq[irc_irq].level;
	tx4939irq[irc_irq].level = new_pri;
	वापस old_pri;
पूर्ण

व्योम __init tx4939_irq_init(व्योम)
अणु
	पूर्णांक i;

	mips_cpu_irq_init();
	/* disable पूर्णांकerrupt control */
	__raw_ग_लिखोl(0, &tx4939_ircptr->den.r);
	__raw_ग_लिखोl(0, &tx4939_ircptr->maskपूर्णांक.r);
	__raw_ग_लिखोl(0, &tx4939_ircptr->maskext.r);
	/* irq_base + 0 is not used */
	क्रम (i = 1; i < TX4939_NUM_IR; i++) अणु
		tx4939irq[i].level = 4; /* middle level */
		tx4939irq[i].mode = TXx9_IRCR_LOW;
		irq_set_chip_and_handler(TXX9_IRQ_BASE + i, &tx4939_irq_chip,
					 handle_level_irq);
	पूर्ण

	/* mask all IRC पूर्णांकerrupts */
	__raw_ग_लिखोl(0, &tx4939_ircptr->msk.r);
	क्रम (i = 0; i < 16; i++)
		__raw_ग_लिखोl(0, &tx4939_ircptr->lvl[i].r);
	/* setup IRC पूर्णांकerrupt mode (Low Active) */
	क्रम (i = 0; i < 2; i++)
		__raw_ग_लिखोl(0, &tx4939_ircptr->dm[i].r);
	क्रम (i = 0; i < 2; i++)
		__raw_ग_लिखोl(0, &tx4939_ircptr->dm2[i].r);
	/* enable पूर्णांकerrupt control */
	__raw_ग_लिखोl(TXx9_IRCER_ICE, &tx4939_ircptr->den.r);
	__raw_ग_लिखोl(irc_elevel, &tx4939_ircptr->msk.r);

	irq_set_chained_handler(MIPS_CPU_IRQ_BASE + TX4939_IRC_INT,
				handle_simple_irq);

	/* उठाओ priority क्रम errors, समयrs, sio */
	tx4939_irq_set_pri(TX4939_IR_WTOERR, 7);
	tx4939_irq_set_pri(TX4939_IR_PCIERR, 7);
	tx4939_irq_set_pri(TX4939_IR_PCIPME, 7);
	क्रम (i = 0; i < TX4939_NUM_IR_TMR; i++)
		tx4939_irq_set_pri(TX4939_IR_TMR(i), 6);
	क्रम (i = 0; i < TX4939_NUM_IR_SIO; i++)
		tx4939_irq_set_pri(TX4939_IR_SIO(i), 5);
पूर्ण

पूर्णांक tx4939_irq(व्योम)
अणु
	u32 csr = __raw_पढ़ोl(&tx4939_ircptr->cs.r);

	अगर (likely(!(csr & TXx9_IRCSR_IF)))
		वापस TXX9_IRQ_BASE + (csr & (TX4939_NUM_IR - 1));
	वापस -1;
पूर्ण
