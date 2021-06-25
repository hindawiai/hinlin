<शैली गुरु>
/*
 * Toshiba RBTX4938 specअगरic पूर्णांकerrupt handlers
 * Copyright (C) 2000-2001 Toshiba Corporation
 *
 * 2003-2005 (c) MontaVista Software, Inc. This file is licensed under the
 * terms of the GNU General Public License version 2. This program is
 * licensed "as is" without any warranty of any kind, whether express
 * or implied.
 *
 * Support क्रम TX4938 in 2.6 - Manish Lachwani (mlachwani@mvista.com)
 */

/*
 * MIPS_CPU_IRQ_BASE+00 Software 0
 * MIPS_CPU_IRQ_BASE+01 Software 1
 * MIPS_CPU_IRQ_BASE+02 Cascade TX4938-CP0
 * MIPS_CPU_IRQ_BASE+03 Multiplexed -- करो not use
 * MIPS_CPU_IRQ_BASE+04 Multiplexed -- करो not use
 * MIPS_CPU_IRQ_BASE+05 Multiplexed -- करो not use
 * MIPS_CPU_IRQ_BASE+06 Multiplexed -- करो not use
 * MIPS_CPU_IRQ_BASE+07 CPU TIMER
 *
 * TXX9_IRQ_BASE+00
 * TXX9_IRQ_BASE+01
 * TXX9_IRQ_BASE+02 Cascade RBTX4938-IOC
 * TXX9_IRQ_BASE+03 RBTX4938 RTL-8019AS Ethernet
 * TXX9_IRQ_BASE+04
 * TXX9_IRQ_BASE+05 TX4938 ETH1
 * TXX9_IRQ_BASE+06 TX4938 ETH0
 * TXX9_IRQ_BASE+07
 * TXX9_IRQ_BASE+08 TX4938 SIO 0
 * TXX9_IRQ_BASE+09 TX4938 SIO 1
 * TXX9_IRQ_BASE+10 TX4938 DMA0
 * TXX9_IRQ_BASE+11 TX4938 DMA1
 * TXX9_IRQ_BASE+12 TX4938 DMA2
 * TXX9_IRQ_BASE+13 TX4938 DMA3
 * TXX9_IRQ_BASE+14
 * TXX9_IRQ_BASE+15
 * TXX9_IRQ_BASE+16 TX4938 PCIC
 * TXX9_IRQ_BASE+17 TX4938 TMR0
 * TXX9_IRQ_BASE+18 TX4938 TMR1
 * TXX9_IRQ_BASE+19 TX4938 TMR2
 * TXX9_IRQ_BASE+20
 * TXX9_IRQ_BASE+21
 * TXX9_IRQ_BASE+22 TX4938 PCIERR
 * TXX9_IRQ_BASE+23
 * TXX9_IRQ_BASE+24
 * TXX9_IRQ_BASE+25
 * TXX9_IRQ_BASE+26
 * TXX9_IRQ_BASE+27
 * TXX9_IRQ_BASE+28
 * TXX9_IRQ_BASE+29
 * TXX9_IRQ_BASE+30
 * TXX9_IRQ_BASE+31 TX4938 SPI
 *
 * RBTX4938_IRQ_IOC+00 PCI-D
 * RBTX4938_IRQ_IOC+01 PCI-C
 * RBTX4938_IRQ_IOC+02 PCI-B
 * RBTX4938_IRQ_IOC+03 PCI-A
 * RBTX4938_IRQ_IOC+04 RTC
 * RBTX4938_IRQ_IOC+05 ATA
 * RBTX4938_IRQ_IOC+06 MODEM
 * RBTX4938_IRQ_IOC+07 SWINT
 */
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <यंत्र/mipsregs.h>
#समावेश <यंत्र/txx9/generic.h>
#समावेश <यंत्र/txx9/rbtx4938.h>

अटल पूर्णांक toshiba_rbtx4938_irq_nested(पूर्णांक sw_irq)
अणु
	u8 level3;

	level3 = पढ़ोb(rbtx4938_imstat_addr);
	अगर (unlikely(!level3))
		वापस -1;
	/* must use fls so onboard ATA has priority */
	वापस RBTX4938_IRQ_IOC + __fls8(level3);
पूर्ण

अटल व्योम toshiba_rbtx4938_irq_ioc_enable(काष्ठा irq_data *d)
अणु
	अचिन्हित अक्षर v;

	v = पढ़ोb(rbtx4938_imask_addr);
	v |= (1 << (d->irq - RBTX4938_IRQ_IOC));
	ग_लिखोb(v, rbtx4938_imask_addr);
	mmiowb();
पूर्ण

अटल व्योम toshiba_rbtx4938_irq_ioc_disable(काष्ठा irq_data *d)
अणु
	अचिन्हित अक्षर v;

	v = पढ़ोb(rbtx4938_imask_addr);
	v &= ~(1 << (d->irq - RBTX4938_IRQ_IOC));
	ग_लिखोb(v, rbtx4938_imask_addr);
	mmiowb();
पूर्ण

#घोषणा TOSHIBA_RBTX4938_IOC_NAME "RBTX4938-IOC"
अटल काष्ठा irq_chip toshiba_rbtx4938_irq_ioc_type = अणु
	.name = TOSHIBA_RBTX4938_IOC_NAME,
	.irq_mask = toshiba_rbtx4938_irq_ioc_disable,
	.irq_unmask = toshiba_rbtx4938_irq_ioc_enable,
पूर्ण;

अटल पूर्णांक rbtx4938_irq_dispatch(पूर्णांक pending)
अणु
	पूर्णांक irq;

	अगर (pending & STATUSF_IP7)
		irq = MIPS_CPU_IRQ_BASE + 7;
	अन्यथा अगर (pending & STATUSF_IP2) अणु
		irq = txx9_irq();
		अगर (irq == RBTX4938_IRQ_IOCINT)
			irq = toshiba_rbtx4938_irq_nested(irq);
	पूर्ण अन्यथा अगर (pending & STATUSF_IP1)
		irq = MIPS_CPU_IRQ_BASE + 0;
	अन्यथा अगर (pending & STATUSF_IP0)
		irq = MIPS_CPU_IRQ_BASE + 1;
	अन्यथा
		irq = -1;
	वापस irq;
पूर्ण

अटल व्योम __init toshiba_rbtx4938_irq_ioc_init(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = RBTX4938_IRQ_IOC;
	     i < RBTX4938_IRQ_IOC + RBTX4938_NR_IRQ_IOC; i++)
		irq_set_chip_and_handler(i, &toshiba_rbtx4938_irq_ioc_type,
					 handle_level_irq);

	irq_set_chained_handler(RBTX4938_IRQ_IOCINT, handle_simple_irq);
पूर्ण

व्योम __init rbtx4938_irq_setup(व्योम)
अणु
	txx9_irq_dispatch = rbtx4938_irq_dispatch;
	/* Now, पूर्णांकerrupt control disabled, */
	/* all IRC पूर्णांकerrupts are masked, */
	/* all IRC पूर्णांकerrupt mode are Low Active. */

	/* mask all IOC पूर्णांकerrupts */
	ग_लिखोb(0, rbtx4938_imask_addr);

	/* clear SoftInt पूर्णांकerrupts */
	ग_लिखोb(0, rbtx4938_softपूर्णांक_addr);
	tx4938_irq_init();
	toshiba_rbtx4938_irq_ioc_init();
	/* Onboard 10M Ether: High Active */
	irq_set_irq_type(RBTX4938_IRQ_ETHER, IRQF_TRIGGER_HIGH);
पूर्ण
