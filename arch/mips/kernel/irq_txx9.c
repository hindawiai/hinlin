<शैली गुरु>
/*
 * Based on linux/arch/mips/jmr3927/rbhma3100/irq.c,
 *	    linux/arch/mips/tx4927/common/tx4927_irq.c,
 *	    linux/arch/mips/tx4938/common/irq.c
 *
 * Copyright 2001, 2003-2005 MontaVista Software Inc.
 * Author: MontaVista Software, Inc.
 *	   ahennessy@mvista.com
 *	   source@mvista.com
 * Copyright (C) 2000-2001 Toshiba Corporation
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/types.h>
#समावेश <linux/irq.h>
#समावेश <यंत्र/txx9irq.h>

काष्ठा txx9_irc_reg अणु
	u32 cer;
	u32 cr[2];
	u32 unused0;
	u32 ilr[8];
	u32 unused1[4];
	u32 imr;
	u32 unused2[7];
	u32 scr;
	u32 unused3[7];
	u32 ssr;
	u32 unused4[7];
	u32 csr;
पूर्ण;

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
#घोषणा TXx9_IRCSR_ILV_MASK	0x00000700
#घोषणा TXx9_IRCSR_IVL_MASK	0x0000001f

#घोषणा irc_dlevel	0
#घोषणा irc_elevel	1

अटल काष्ठा txx9_irc_reg __iomem *txx9_ircptr __पढ़ो_mostly;

अटल काष्ठा अणु
	अचिन्हित अक्षर level;
	अचिन्हित अक्षर mode;
पूर्ण txx9irq[TXx9_MAX_IR] __पढ़ो_mostly;

अटल व्योम txx9_irq_unmask(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक irq_nr = d->irq - TXX9_IRQ_BASE;
	u32 __iomem *ilrp = &txx9_ircptr->ilr[(irq_nr % 16 ) / 2];
	पूर्णांक ofs = irq_nr / 16 * 16 + (irq_nr & 1) * 8;

	__raw_ग_लिखोl((__raw_पढ़ोl(ilrp) & ~(0xff << ofs))
		     | (txx9irq[irq_nr].level << ofs),
		     ilrp);
#अगर_घोषित CONFIG_CPU_TX39XX
	/* update IRCSR */
	__raw_ग_लिखोl(0, &txx9_ircptr->imr);
	__raw_ग_लिखोl(irc_elevel, &txx9_ircptr->imr);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम txx9_irq_mask(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक irq_nr = d->irq - TXX9_IRQ_BASE;
	u32 __iomem *ilrp = &txx9_ircptr->ilr[(irq_nr % 16) / 2];
	पूर्णांक ofs = irq_nr / 16 * 16 + (irq_nr & 1) * 8;

	__raw_ग_लिखोl((__raw_पढ़ोl(ilrp) & ~(0xff << ofs))
		     | (irc_dlevel << ofs),
		     ilrp);
#अगर_घोषित CONFIG_CPU_TX39XX
	/* update IRCSR */
	__raw_ग_लिखोl(0, &txx9_ircptr->imr);
	__raw_ग_लिखोl(irc_elevel, &txx9_ircptr->imr);
	/* flush ग_लिखो buffer */
	__raw_पढ़ोl(&txx9_ircptr->ssr);
#अन्यथा
	mmiowb();
#पूर्ण_अगर
पूर्ण

अटल व्योम txx9_irq_mask_ack(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक irq_nr = d->irq - TXX9_IRQ_BASE;

	txx9_irq_mask(d);
	/* clear edge detection */
	अगर (unlikely(TXx9_IRCR_EDGE(txx9irq[irq_nr].mode)))
		__raw_ग_लिखोl(TXx9_IRSCR_EIClrE | irq_nr, &txx9_ircptr->scr);
पूर्ण

अटल पूर्णांक txx9_irq_set_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक flow_type)
अणु
	अचिन्हित पूर्णांक irq_nr = d->irq - TXX9_IRQ_BASE;
	u32 cr;
	u32 __iomem *crp;
	पूर्णांक ofs;
	पूर्णांक mode;

	अगर (flow_type & IRQF_TRIGGER_PROBE)
		वापस 0;
	चयन (flow_type & IRQF_TRIGGER_MASK) अणु
	हाल IRQF_TRIGGER_RISING:	mode = TXx9_IRCR_UP;	अवरोध;
	हाल IRQF_TRIGGER_FALLING:	mode = TXx9_IRCR_DOWN;	अवरोध;
	हाल IRQF_TRIGGER_HIGH: mode = TXx9_IRCR_HIGH;	अवरोध;
	हाल IRQF_TRIGGER_LOW:	mode = TXx9_IRCR_LOW;	अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	crp = &txx9_ircptr->cr[(अचिन्हित पूर्णांक)irq_nr / 8];
	cr = __raw_पढ़ोl(crp);
	ofs = (irq_nr & (8 - 1)) * 2;
	cr &= ~(0x3 << ofs);
	cr |= (mode & 0x3) << ofs;
	__raw_ग_लिखोl(cr, crp);
	txx9irq[irq_nr].mode = mode;
	वापस 0;
पूर्ण

अटल काष्ठा irq_chip txx9_irq_chip = अणु
	.name		= "TXX9",
	.irq_ack	= txx9_irq_mask_ack,
	.irq_mask	= txx9_irq_mask,
	.irq_mask_ack	= txx9_irq_mask_ack,
	.irq_unmask	= txx9_irq_unmask,
	.irq_set_type	= txx9_irq_set_type,
पूर्ण;

व्योम __init txx9_irq_init(अचिन्हित दीर्घ baseaddr)
अणु
	पूर्णांक i;

	txx9_ircptr = ioremap(baseaddr, माप(काष्ठा txx9_irc_reg));
	क्रम (i = 0; i < TXx9_MAX_IR; i++) अणु
		txx9irq[i].level = 4; /* middle level */
		txx9irq[i].mode = TXx9_IRCR_LOW;
		irq_set_chip_and_handler(TXX9_IRQ_BASE + i, &txx9_irq_chip,
					 handle_level_irq);
	पूर्ण

	/* mask all IRC पूर्णांकerrupts */
	__raw_ग_लिखोl(0, &txx9_ircptr->imr);
	क्रम (i = 0; i < 8; i++)
		__raw_ग_लिखोl(0, &txx9_ircptr->ilr[i]);
	/* setup IRC पूर्णांकerrupt mode (Low Active) */
	क्रम (i = 0; i < 2; i++)
		__raw_ग_लिखोl(0, &txx9_ircptr->cr[i]);
	/* enable पूर्णांकerrupt control */
	__raw_ग_लिखोl(TXx9_IRCER_ICE, &txx9_ircptr->cer);
	__raw_ग_लिखोl(irc_elevel, &txx9_ircptr->imr);
पूर्ण

पूर्णांक __init txx9_irq_set_pri(पूर्णांक irc_irq, पूर्णांक new_pri)
अणु
	पूर्णांक old_pri;

	अगर ((अचिन्हित पूर्णांक)irc_irq >= TXx9_MAX_IR)
		वापस 0;
	old_pri = txx9irq[irc_irq].level;
	txx9irq[irc_irq].level = new_pri;
	वापस old_pri;
पूर्ण

पूर्णांक txx9_irq(व्योम)
अणु
	u32 csr = __raw_पढ़ोl(&txx9_ircptr->csr);

	अगर (likely(!(csr & TXx9_IRCSR_IF)))
		वापस TXX9_IRQ_BASE + (csr & (TXx9_MAX_IR - 1));
	वापस -1;
पूर्ण
