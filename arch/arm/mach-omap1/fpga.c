<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/arch/arm/mach-omap1/fpga.c
 *
 * Interrupt handler क्रम OMAP-1510 Innovator FPGA
 *
 * Copyright (C) 2001 RidgeRun, Inc.
 * Author: Greg Lonnon <glonnon@ridgerun.com>
 *
 * Copyright (C) 2002 MontaVista Software, Inc.
 *
 * Separated FPGA पूर्णांकerrupts from innovator1510.c and cleaned up क्रम 2.6
 * Copyright (C) 2004 Nokia Corporation by Tony Lindrgen <tony@atomide.com>
 */

#समावेश <linux/types.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पन.स>

#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/mach/irq.h>

#समावेश <mach/hardware.h>

#समावेश "iomap.h"
#समावेश "common.h"
#समावेश "fpga.h"

अटल व्योम fpga_mask_irq(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक irq = d->irq - OMAP_FPGA_IRQ_BASE;

	अगर (irq < 8)
		__raw_ग_लिखोb((__raw_पढ़ोb(OMAP1510_FPGA_IMR_LO)
			      & ~(1 << irq)), OMAP1510_FPGA_IMR_LO);
	अन्यथा अगर (irq < 16)
		__raw_ग_लिखोb((__raw_पढ़ोb(OMAP1510_FPGA_IMR_HI)
			      & ~(1 << (irq - 8))), OMAP1510_FPGA_IMR_HI);
	अन्यथा
		__raw_ग_लिखोb((__raw_पढ़ोb(INNOVATOR_FPGA_IMR2)
			      & ~(1 << (irq - 16))), INNOVATOR_FPGA_IMR2);
पूर्ण


अटल अंतरभूत u32 get_fpga_unmasked_irqs(व्योम)
अणु
	वापस
		((__raw_पढ़ोb(OMAP1510_FPGA_ISR_LO) &
		  __raw_पढ़ोb(OMAP1510_FPGA_IMR_LO))) |
		((__raw_पढ़ोb(OMAP1510_FPGA_ISR_HI) &
		  __raw_पढ़ोb(OMAP1510_FPGA_IMR_HI)) << 8) |
		((__raw_पढ़ोb(INNOVATOR_FPGA_ISR2) &
		  __raw_पढ़ोb(INNOVATOR_FPGA_IMR2)) << 16);
पूर्ण


अटल व्योम fpga_ack_irq(काष्ठा irq_data *d)
अणु
	/* Don't need to explicitly ACK FPGA पूर्णांकerrupts */
पूर्ण

अटल व्योम fpga_unmask_irq(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक irq = d->irq - OMAP_FPGA_IRQ_BASE;

	अगर (irq < 8)
		__raw_ग_लिखोb((__raw_पढ़ोb(OMAP1510_FPGA_IMR_LO) | (1 << irq)),
		     OMAP1510_FPGA_IMR_LO);
	अन्यथा अगर (irq < 16)
		__raw_ग_लिखोb((__raw_पढ़ोb(OMAP1510_FPGA_IMR_HI)
			      | (1 << (irq - 8))), OMAP1510_FPGA_IMR_HI);
	अन्यथा
		__raw_ग_लिखोb((__raw_पढ़ोb(INNOVATOR_FPGA_IMR2)
			      | (1 << (irq - 16))), INNOVATOR_FPGA_IMR2);
पूर्ण

अटल व्योम fpga_mask_ack_irq(काष्ठा irq_data *d)
अणु
	fpga_mask_irq(d);
	fpga_ack_irq(d);
पूर्ण

अटल व्योम innovator_fpga_IRQ_demux(काष्ठा irq_desc *desc)
अणु
	u32 stat;
	पूर्णांक fpga_irq;

	stat = get_fpga_unmasked_irqs();

	अगर (!stat)
		वापस;

	क्रम (fpga_irq = OMAP_FPGA_IRQ_BASE;
	     (fpga_irq < OMAP_FPGA_IRQ_END) && stat;
	     fpga_irq++, stat >>= 1) अणु
		अगर (stat & 1) अणु
			generic_handle_irq(fpga_irq);
		पूर्ण
	पूर्ण
पूर्ण

अटल काष्ठा irq_chip omap_fpga_irq_ack = अणु
	.name		= "FPGA-ack",
	.irq_ack	= fpga_mask_ack_irq,
	.irq_mask	= fpga_mask_irq,
	.irq_unmask	= fpga_unmask_irq,
पूर्ण;


अटल काष्ठा irq_chip omap_fpga_irq = अणु
	.name		= "FPGA",
	.irq_ack	= fpga_ack_irq,
	.irq_mask	= fpga_mask_irq,
	.irq_unmask	= fpga_unmask_irq,
पूर्ण;

/*
 * All of the FPGA पूर्णांकerrupt request inमाला_दो except क्रम the touchscreen are
 * edge-sensitive; the touchscreen is level-sensitive.  The edge-sensitive
 * पूर्णांकerrupts are acknowledged as a side-effect of पढ़ोing the पूर्णांकerrupt
 * status रेजिस्टर from the FPGA.  The edge-sensitive पूर्णांकerrupt inमाला_दो
 * cause a problem with level पूर्णांकerrupt requests, such as Ethernet.  The
 * problem occurs when a level पूर्णांकerrupt request is निश्चितed जबतक its
 * पूर्णांकerrupt input is masked in the FPGA, which results in a missed
 * पूर्णांकerrupt.
 *
 * In an attempt to workaround the problem with missed पूर्णांकerrupts, the
 * mask_ack routine क्रम all of the FPGA पूर्णांकerrupts has been changed from
 * fpga_mask_ack_irq() to fpga_ack_irq() so that the specअगरic FPGA पूर्णांकerrupt
 * being serviced is left unmasked.  We can करो this because the FPGA cascade
 * पूर्णांकerrupt is run with all पूर्णांकerrupts masked.
 *
 * Limited testing indicates that this workaround appears to be effective
 * क्रम the smc9194 Ethernet driver used on the Innovator.  It should work
 * on other FPGA पूर्णांकerrupts as well, but any drivers that explicitly mask
 * पूर्णांकerrupts at the पूर्णांकerrupt controller via disable_irq/enable_irq
 * could pose a problem.
 */
व्योम omap1510_fpga_init_irq(व्योम)
अणु
	पूर्णांक i, res;

	__raw_ग_लिखोb(0, OMAP1510_FPGA_IMR_LO);
	__raw_ग_लिखोb(0, OMAP1510_FPGA_IMR_HI);
	__raw_ग_लिखोb(0, INNOVATOR_FPGA_IMR2);

	क्रम (i = OMAP_FPGA_IRQ_BASE; i < OMAP_FPGA_IRQ_END; i++) अणु

		अगर (i == OMAP1510_INT_FPGA_TS) अणु
			/*
			 * The touchscreen पूर्णांकerrupt is level-sensitive, so
			 * we'll use the regular mask_ack routine क्रम it.
			 */
			irq_set_chip(i, &omap_fpga_irq_ack);
		पूर्ण
		अन्यथा अणु
			/*
			 * All FPGA पूर्णांकerrupts except the touchscreen are
			 * edge-sensitive, so we won't mask them.
			 */
			irq_set_chip(i, &omap_fpga_irq);
		पूर्ण

		irq_set_handler(i, handle_edge_irq);
		irq_clear_status_flags(i, IRQ_NOREQUEST);
	पूर्ण

	/*
	 * The FPGA पूर्णांकerrupt line is connected to GPIO13. Claim this pin क्रम
	 * the ARM.
	 *
	 * NOTE: For general GPIO/MPUIO access and पूर्णांकerrupts, please see
	 * gpio.[ch]
	 */
	res = gpio_request(13, "FPGA irq");
	अगर (res) अणु
		pr_err("%s failed to get gpio\n", __func__);
		वापस;
	पूर्ण
	gpio_direction_input(13);
	irq_set_irq_type(gpio_to_irq(13), IRQ_TYPE_EDGE_RISING);
	irq_set_chained_handler(OMAP1510_INT_FPGA, innovator_fpga_IRQ_demux);
पूर्ण
