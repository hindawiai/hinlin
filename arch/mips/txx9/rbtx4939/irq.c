<शैली गुरु>
/*
 * Toshiba RBTX4939 पूर्णांकerrupt routines
 * Based on linux/arch/mips/txx9/rbtx4938/irq.c,
 *	    and RBTX49xx patch from CELF patch archive.
 *
 * Copyright (C) 2000-2001,2005-2006 Toshiba Corporation
 * 2003-2005 (c) MontaVista Software, Inc. This file is licensed under the
 * terms of the GNU General Public License version 2. This program is
 * licensed "as is" without any warranty of any kind, whether express
 * or implied.
 */
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <यंत्र/mipsregs.h>
#समावेश <यंत्र/txx9/rbtx4939.h>

/*
 * RBTX4939 IOC controller definition
 */

अटल व्योम rbtx4939_ioc_irq_unmask(काष्ठा irq_data *d)
अणु
	पूर्णांक ioc_nr = d->irq - RBTX4939_IRQ_IOC;

	ग_लिखोb(पढ़ोb(rbtx4939_ien_addr) | (1 << ioc_nr), rbtx4939_ien_addr);
पूर्ण

अटल व्योम rbtx4939_ioc_irq_mask(काष्ठा irq_data *d)
अणु
	पूर्णांक ioc_nr = d->irq - RBTX4939_IRQ_IOC;

	ग_लिखोb(पढ़ोb(rbtx4939_ien_addr) & ~(1 << ioc_nr), rbtx4939_ien_addr);
	mmiowb();
पूर्ण

अटल काष्ठा irq_chip rbtx4939_ioc_irq_chip = अणु
	.name		= "IOC",
	.irq_mask	= rbtx4939_ioc_irq_mask,
	.irq_unmask	= rbtx4939_ioc_irq_unmask,
पूर्ण;


अटल अंतरभूत पूर्णांक rbtx4939_ioc_irqroute(व्योम)
अणु
	अचिन्हित अक्षर istat = पढ़ोb(rbtx4939_अगरac2_addr);

	अगर (unlikely(istat == 0))
		वापस -1;
	वापस RBTX4939_IRQ_IOC + __fls8(istat);
पूर्ण

अटल पूर्णांक rbtx4939_irq_dispatch(पूर्णांक pending)
अणु
	पूर्णांक irq;

	अगर (pending & CAUSEF_IP7)
		वापस MIPS_CPU_IRQ_BASE + 7;
	irq = tx4939_irq();
	अगर (likely(irq >= 0)) अणु
		/* redirect IOC पूर्णांकerrupts */
		चयन (irq) अणु
		हाल RBTX4939_IRQ_IOCINT:
			irq = rbtx4939_ioc_irqroute();
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (pending & CAUSEF_IP0)
		irq = MIPS_CPU_IRQ_BASE + 0;
	अन्यथा अगर (pending & CAUSEF_IP1)
		irq = MIPS_CPU_IRQ_BASE + 1;
	अन्यथा
		irq = -1;
	वापस irq;
पूर्ण

व्योम __init rbtx4939_irq_setup(व्योम)
अणु
	पूर्णांक i;

	/* mask all IOC पूर्णांकerrupts */
	ग_लिखोb(0, rbtx4939_ien_addr);

	/* clear SoftInt पूर्णांकerrupts */
	ग_लिखोb(0, rbtx4939_softपूर्णांक_addr);

	txx9_irq_dispatch = rbtx4939_irq_dispatch;

	tx4939_irq_init();
	क्रम (i = RBTX4939_IRQ_IOC;
	     i < RBTX4939_IRQ_IOC + RBTX4939_NR_IRQ_IOC; i++)
		irq_set_chip_and_handler(i, &rbtx4939_ioc_irq_chip,
					 handle_level_irq);

	irq_set_chained_handler(RBTX4939_IRQ_IOCINT, handle_simple_irq);
पूर्ण
