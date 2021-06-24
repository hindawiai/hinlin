<शैली गुरु>
/*
 *
 * Programmable Interrupt Controller functions क्रम the Freescale MPC52xx.
 *
 * Copyright (C) 2008 Secret Lab Technologies Ltd.
 * Copyright (C) 2006 bplan GmbH
 * Copyright (C) 2004 Sylvain Munaut <tnt@246tNt.com>
 * Copyright (C) 2003 Montavista Software, Inc
 *
 * Based on the code from the 2.4 kernel by
 * Dale Farnsworth <dfarnsworth@mvista.com> and Kent Borg.
 *
 * This file is licensed under the terms of the GNU General Public License
 * version 2. This program is licensed "as is" without any warranty of any
 * kind, whether express or implied.
 *
 */

/*
 * This is the device driver क्रम the MPC5200 पूर्णांकerrupt controller.
 *
 * hardware overview
 * -----------------
 * The MPC5200 पूर्णांकerrupt controller groups the all पूर्णांकerrupt sources पूर्णांकo
 * three groups called 'critical', 'main', and 'peripheral'.  The critical
 * group has 3 irqs, External IRQ0, slice समयr 0 irq, and wake from deep
 * sleep.  Main group include the other 3 बाह्यal IRQs, slice समयr 1, RTC,
 * gpios, and the general purpose समयrs.  Peripheral group contains the
 * reमुख्यing irq sources from all of the on-chip peripherals (PSCs, Ethernet,
 * USB, DMA, etc).
 *
 * virqs
 * -----
 * The Linux IRQ subप्रणाली requires that each irq source be asचिन्हित a
 * प्रणाली wide unique IRQ number starting at 1 (0 means no irq).  Since
 * प्रणालीs can have multiple पूर्णांकerrupt controllers, the भव IRQ (virq)
 * infraकाष्ठाure lets each पूर्णांकerrupt controller to define a local set
 * of IRQ numbers and the virq infraकाष्ठाure maps those numbers पूर्णांकo
 * a unique range of the global IRQ# space.
 *
 * To define a range of virq numbers क्रम this controller, this driver first
 * assigns a number to each of the irq groups (called the level 1 or L1
 * value).  Within each group inभागidual irq sources are also asचिन्हित a
 * number, as defined by the MPC5200 user guide, and refers to it as the
 * level 2 or L2 value.  The virq number is determined by shअगरting up the
 * L1 value by MPC52xx_IRQ_L1_OFFSET and ORing it with the L2 value.
 *
 * For example, the TMR0 पूर्णांकerrupt is irq 9 in the मुख्य group.  The
 * virq क्रम TMR0 is calculated by ((1 << MPC52xx_IRQ_L1_OFFSET) | 9).
 *
 * The observant पढ़ोer will also notice that this driver defines a 4th
 * पूर्णांकerrupt group called 'bestcomm'.  The bestcomm group isn't physically
 * part of the MPC5200 पूर्णांकerrupt controller, but it is used here to assign
 * a separate virq number क्रम each bestcomm task (since any of the 16
 * bestcomm tasks can cause the bestcomm पूर्णांकerrupt to be उठाओd).  When a
 * bestcomm पूर्णांकerrupt occurs (peripheral group, irq 0) this driver determines
 * which task needs servicing and वापसs the irq number क्रम that task.  This
 * allows drivers which use bestcomm to define their own पूर्णांकerrupt handlers.
 *
 * irq_chip काष्ठाures
 * -------------------
 * For actually manipulating IRQs (masking, enabling, clearing, etc) this
 * driver defines four separate 'irq_chip' काष्ठाures, one क्रम the मुख्य
 * group, one क्रम the peripherals group, one क्रम the bestcomm group and one
 * क्रम बाह्यal पूर्णांकerrupts.  The irq_chip काष्ठाures provide the hooks needed
 * to manipulate each IRQ source, and since each group is has a separate set
 * of रेजिस्टरs क्रम controlling the irq, it makes sense to भागide up the
 * hooks aदीर्घ those lines.
 *
 * You'll notice that there is not an irq_chip क्रम the critical group and
 * you'll also notice that there is an irq_chip defined क्रम बाह्यal
 * पूर्णांकerrupts even though there is no बाह्यal पूर्णांकerrupt group.  The reason
 * क्रम this is that the four बाह्यal पूर्णांकerrupts are all managed with the same
 * रेजिस्टर even though one of the बाह्यal IRQs is in the critical group and
 * the other three are in the मुख्य group.  For this reason it makes sense क्रम
 * the 4 बाह्यal irqs to be managed using a separate set of hooks.  The
 * reason there is no crit irq_chip is that of the 3 irqs in the critical
 * group, only बाह्यal पूर्णांकerrupt is actually support at this समय by this
 * driver and since बाह्यal पूर्णांकerrupt is the only one used, it can just
 * be directed to make use of the बाह्यal irq irq_chip.
 *
 * device tree bindings
 * --------------------
 * The device tree bindings क्रम this controller reflect the two level
 * organization of irqs in the device.  #पूर्णांकerrupt-cells = <3> where the
 * first cell is the group number [0..3], the second cell is the irq
 * number in the group, and the third cell is the sense type (level/edge).
 * For reference, the following is a list of the पूर्णांकerrupt property values
 * associated with बाह्यal पूर्णांकerrupt sources on the MPC5200 (just because
 * it is non-obvious to determine what the पूर्णांकerrupts property should be
 * when पढ़ोing the mpc5200 manual and it is a frequently asked question).
 *
 * External पूर्णांकerrupts:
 * <0 0 n>	बाह्यal irq0, n is sense	(n=0: level high,
 * <1 1 n>	बाह्यal irq1, n is sense	 n=1: edge rising,
 * <1 2 n>	बाह्यal irq2, n is sense	 n=2: edge falling,
 * <1 3 n>	बाह्यal irq3, n is sense	 n=3: level low)
 */
#अघोषित DEBUG

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/of.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/mpc52xx.h>

/* HW IRQ mapping */
#घोषणा MPC52xx_IRQ_L1_CRIT	(0)
#घोषणा MPC52xx_IRQ_L1_MAIN	(1)
#घोषणा MPC52xx_IRQ_L1_PERP	(2)
#घोषणा MPC52xx_IRQ_L1_SDMA	(3)

#घोषणा MPC52xx_IRQ_L1_OFFSET	(6)
#घोषणा MPC52xx_IRQ_L1_MASK	(0x00c0)
#घोषणा MPC52xx_IRQ_L2_MASK	(0x003f)

#घोषणा MPC52xx_IRQ_HIGHTESTHWIRQ (0xd0)


/* MPC5200 device tree match tables */
अटल स्थिर काष्ठा of_device_id mpc52xx_pic_ids[] __initस्थिर = अणु
	अणु .compatible = "fsl,mpc5200-pic", पूर्ण,
	अणु .compatible = "mpc5200-pic", पूर्ण,
	अणुपूर्ण
पूर्ण;
अटल स्थिर काष्ठा of_device_id mpc52xx_sdma_ids[] __initस्थिर = अणु
	अणु .compatible = "fsl,mpc5200-bestcomm", पूर्ण,
	अणु .compatible = "mpc5200-bestcomm", पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा mpc52xx_पूर्णांकr __iomem *पूर्णांकr;
अटल काष्ठा mpc52xx_sdma __iomem *sdma;
अटल काष्ठा irq_करोमुख्य *mpc52xx_irqhost = शून्य;

अटल अचिन्हित अक्षर mpc52xx_map_senses[4] = अणु
	IRQ_TYPE_LEVEL_HIGH,
	IRQ_TYPE_EDGE_RISING,
	IRQ_TYPE_EDGE_FALLING,
	IRQ_TYPE_LEVEL_LOW,
पूर्ण;

/* Utility functions */
अटल अंतरभूत व्योम io_be_setbit(u32 __iomem *addr, पूर्णांक bitno)
अणु
	out_be32(addr, in_be32(addr) | (1 << bitno));
पूर्ण

अटल अंतरभूत व्योम io_be_clrbit(u32 __iomem *addr, पूर्णांक bitno)
अणु
	out_be32(addr, in_be32(addr) & ~(1 << bitno));
पूर्ण

/*
 * IRQ[0-3] पूर्णांकerrupt irq_chip
 */
अटल व्योम mpc52xx_extirq_mask(काष्ठा irq_data *d)
अणु
	पूर्णांक l2irq = irqd_to_hwirq(d) & MPC52xx_IRQ_L2_MASK;
	io_be_clrbit(&पूर्णांकr->ctrl, 11 - l2irq);
पूर्ण

अटल व्योम mpc52xx_extirq_unmask(काष्ठा irq_data *d)
अणु
	पूर्णांक l2irq = irqd_to_hwirq(d) & MPC52xx_IRQ_L2_MASK;
	io_be_setbit(&पूर्णांकr->ctrl, 11 - l2irq);
पूर्ण

अटल व्योम mpc52xx_extirq_ack(काष्ठा irq_data *d)
अणु
	पूर्णांक l2irq = irqd_to_hwirq(d) & MPC52xx_IRQ_L2_MASK;
	io_be_setbit(&पूर्णांकr->ctrl, 27-l2irq);
पूर्ण

अटल पूर्णांक mpc52xx_extirq_set_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक flow_type)
अणु
	u32 ctrl_reg, type;
	पूर्णांक l2irq = irqd_to_hwirq(d) & MPC52xx_IRQ_L2_MASK;
	व्योम *handler = handle_level_irq;

	pr_debug("%s: irq=%x. l2=%d flow_type=%d\n", __func__,
		(पूर्णांक) irqd_to_hwirq(d), l2irq, flow_type);

	चयन (flow_type) अणु
	हाल IRQF_TRIGGER_HIGH: type = 0; अवरोध;
	हाल IRQF_TRIGGER_RISING: type = 1; handler = handle_edge_irq; अवरोध;
	हाल IRQF_TRIGGER_FALLING: type = 2; handler = handle_edge_irq; अवरोध;
	हाल IRQF_TRIGGER_LOW: type = 3; अवरोध;
	शेष:
		type = 0;
	पूर्ण

	ctrl_reg = in_be32(&पूर्णांकr->ctrl);
	ctrl_reg &= ~(0x3 << (22 - (l2irq * 2)));
	ctrl_reg |= (type << (22 - (l2irq * 2)));
	out_be32(&पूर्णांकr->ctrl, ctrl_reg);

	irq_set_handler_locked(d, handler);

	वापस 0;
पूर्ण

अटल काष्ठा irq_chip mpc52xx_extirq_irqchip = अणु
	.name = "MPC52xx External",
	.irq_mask = mpc52xx_extirq_mask,
	.irq_unmask = mpc52xx_extirq_unmask,
	.irq_ack = mpc52xx_extirq_ack,
	.irq_set_type = mpc52xx_extirq_set_type,
पूर्ण;

/*
 * Main पूर्णांकerrupt irq_chip
 */
अटल पूर्णांक mpc52xx_null_set_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक flow_type)
अणु
	वापस 0; /* Do nothing so that the sense mask will get updated */
पूर्ण

अटल व्योम mpc52xx_मुख्य_mask(काष्ठा irq_data *d)
अणु
	पूर्णांक l2irq = irqd_to_hwirq(d) & MPC52xx_IRQ_L2_MASK;
	io_be_setbit(&पूर्णांकr->मुख्य_mask, 16 - l2irq);
पूर्ण

अटल व्योम mpc52xx_मुख्य_unmask(काष्ठा irq_data *d)
अणु
	पूर्णांक l2irq = irqd_to_hwirq(d) & MPC52xx_IRQ_L2_MASK;
	io_be_clrbit(&पूर्णांकr->मुख्य_mask, 16 - l2irq);
पूर्ण

अटल काष्ठा irq_chip mpc52xx_मुख्य_irqchip = अणु
	.name = "MPC52xx Main",
	.irq_mask = mpc52xx_मुख्य_mask,
	.irq_mask_ack = mpc52xx_मुख्य_mask,
	.irq_unmask = mpc52xx_मुख्य_unmask,
	.irq_set_type = mpc52xx_null_set_type,
पूर्ण;

/*
 * Peripherals पूर्णांकerrupt irq_chip
 */
अटल व्योम mpc52xx_periph_mask(काष्ठा irq_data *d)
अणु
	पूर्णांक l2irq = irqd_to_hwirq(d) & MPC52xx_IRQ_L2_MASK;
	io_be_setbit(&पूर्णांकr->per_mask, 31 - l2irq);
पूर्ण

अटल व्योम mpc52xx_periph_unmask(काष्ठा irq_data *d)
अणु
	पूर्णांक l2irq = irqd_to_hwirq(d) & MPC52xx_IRQ_L2_MASK;
	io_be_clrbit(&पूर्णांकr->per_mask, 31 - l2irq);
पूर्ण

अटल काष्ठा irq_chip mpc52xx_periph_irqchip = अणु
	.name = "MPC52xx Peripherals",
	.irq_mask = mpc52xx_periph_mask,
	.irq_mask_ack = mpc52xx_periph_mask,
	.irq_unmask = mpc52xx_periph_unmask,
	.irq_set_type = mpc52xx_null_set_type,
पूर्ण;

/*
 * SDMA पूर्णांकerrupt irq_chip
 */
अटल व्योम mpc52xx_sdma_mask(काष्ठा irq_data *d)
अणु
	पूर्णांक l2irq = irqd_to_hwirq(d) & MPC52xx_IRQ_L2_MASK;
	io_be_setbit(&sdma->IntMask, l2irq);
पूर्ण

अटल व्योम mpc52xx_sdma_unmask(काष्ठा irq_data *d)
अणु
	पूर्णांक l2irq = irqd_to_hwirq(d) & MPC52xx_IRQ_L2_MASK;
	io_be_clrbit(&sdma->IntMask, l2irq);
पूर्ण

अटल व्योम mpc52xx_sdma_ack(काष्ठा irq_data *d)
अणु
	पूर्णांक l2irq = irqd_to_hwirq(d) & MPC52xx_IRQ_L2_MASK;
	out_be32(&sdma->IntPend, 1 << l2irq);
पूर्ण

अटल काष्ठा irq_chip mpc52xx_sdma_irqchip = अणु
	.name = "MPC52xx SDMA",
	.irq_mask = mpc52xx_sdma_mask,
	.irq_unmask = mpc52xx_sdma_unmask,
	.irq_ack = mpc52xx_sdma_ack,
	.irq_set_type = mpc52xx_null_set_type,
पूर्ण;

/**
 * mpc52xx_is_extirq - Returns true अगर hwirq number is क्रम an बाह्यal IRQ
 */
अटल पूर्णांक mpc52xx_is_extirq(पूर्णांक l1, पूर्णांक l2)
अणु
	वापस ((l1 == 0) && (l2 == 0)) ||
	       ((l1 == 1) && (l2 >= 1) && (l2 <= 3));
पूर्ण

/**
 * mpc52xx_irqhost_xlate - translate virq# from device tree पूर्णांकerrupts property
 */
अटल पूर्णांक mpc52xx_irqhost_xlate(काष्ठा irq_करोमुख्य *h, काष्ठा device_node *ct,
				 स्थिर u32 *पूर्णांकspec, अचिन्हित पूर्णांक पूर्णांकsize,
				 irq_hw_number_t *out_hwirq,
				 अचिन्हित पूर्णांक *out_flags)
अणु
	पूर्णांक पूर्णांकrvect_l1;
	पूर्णांक पूर्णांकrvect_l2;
	पूर्णांक पूर्णांकrvect_type;
	पूर्णांक पूर्णांकrvect_linux;

	अगर (पूर्णांकsize != 3)
		वापस -1;

	पूर्णांकrvect_l1 = (पूर्णांक)पूर्णांकspec[0];
	पूर्णांकrvect_l2 = (पूर्णांक)पूर्णांकspec[1];
	पूर्णांकrvect_type = (पूर्णांक)पूर्णांकspec[2] & 0x3;

	पूर्णांकrvect_linux = (पूर्णांकrvect_l1 << MPC52xx_IRQ_L1_OFFSET) &
			 MPC52xx_IRQ_L1_MASK;
	पूर्णांकrvect_linux |= पूर्णांकrvect_l2 & MPC52xx_IRQ_L2_MASK;

	*out_hwirq = पूर्णांकrvect_linux;
	*out_flags = IRQ_TYPE_LEVEL_LOW;
	अगर (mpc52xx_is_extirq(पूर्णांकrvect_l1, पूर्णांकrvect_l2))
		*out_flags = mpc52xx_map_senses[पूर्णांकrvect_type];

	pr_debug("return %x, l1=%d, l2=%d\n", पूर्णांकrvect_linux, पूर्णांकrvect_l1,
		 पूर्णांकrvect_l2);
	वापस 0;
पूर्ण

/**
 * mpc52xx_irqhost_map - Hook to map from virq to an irq_chip काष्ठाure
 */
अटल पूर्णांक mpc52xx_irqhost_map(काष्ठा irq_करोमुख्य *h, अचिन्हित पूर्णांक virq,
			       irq_hw_number_t irq)
अणु
	पूर्णांक l1irq;
	पूर्णांक l2irq;
	काष्ठा irq_chip *irqchip;
	व्योम *hndlr;
	पूर्णांक type;
	u32 reg;

	l1irq = (irq & MPC52xx_IRQ_L1_MASK) >> MPC52xx_IRQ_L1_OFFSET;
	l2irq = irq & MPC52xx_IRQ_L2_MASK;

	/*
	 * External IRQs are handled dअगरferently by the hardware so they are
	 * handled by a dedicated irq_chip काष्ठाure.
	 */
	अगर (mpc52xx_is_extirq(l1irq, l2irq)) अणु
		reg = in_be32(&पूर्णांकr->ctrl);
		type = mpc52xx_map_senses[(reg >> (22 - l2irq * 2)) & 0x3];
		अगर ((type == IRQ_TYPE_EDGE_FALLING) ||
		    (type == IRQ_TYPE_EDGE_RISING))
			hndlr = handle_edge_irq;
		अन्यथा
			hndlr = handle_level_irq;

		irq_set_chip_and_handler(virq, &mpc52xx_extirq_irqchip, hndlr);
		pr_debug("%s: External IRQ%i virq=%x, hw=%x. type=%x\n",
			 __func__, l2irq, virq, (पूर्णांक)irq, type);
		वापस 0;
	पूर्ण

	/* It is an पूर्णांकernal SOC irq.  Choose the correct irq_chip */
	चयन (l1irq) अणु
	हाल MPC52xx_IRQ_L1_MAIN: irqchip = &mpc52xx_मुख्य_irqchip; अवरोध;
	हाल MPC52xx_IRQ_L1_PERP: irqchip = &mpc52xx_periph_irqchip; अवरोध;
	हाल MPC52xx_IRQ_L1_SDMA: irqchip = &mpc52xx_sdma_irqchip; अवरोध;
	हाल MPC52xx_IRQ_L1_CRIT:
		pr_warn("%s: Critical IRQ #%d is unsupported! Nopping it.\n",
			__func__, l2irq);
		irq_set_chip(virq, &no_irq_chip);
		वापस 0;
	पूर्ण

	irq_set_chip_and_handler(virq, irqchip, handle_level_irq);
	pr_debug("%s: virq=%x, l1=%i, l2=%i\n", __func__, virq, l1irq, l2irq);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops mpc52xx_irqhost_ops = अणु
	.xlate = mpc52xx_irqhost_xlate,
	.map = mpc52xx_irqhost_map,
पूर्ण;

/**
 * mpc52xx_init_irq - Initialize and रेजिस्टर with the virq subप्रणाली
 *
 * Hook क्रम setting up IRQs on an mpc5200 प्रणाली.  A poपूर्णांकer to this function
 * is to be put पूर्णांकo the machine definition काष्ठाure.
 *
 * This function searches the device tree क्रम an MPC5200 पूर्णांकerrupt controller,
 * initializes it, and रेजिस्टरs it with the virq subप्रणाली.
 */
व्योम __init mpc52xx_init_irq(व्योम)
अणु
	u32 पूर्णांकr_ctrl;
	काष्ठा device_node *picnode;
	काष्ठा device_node *np;

	/* Remap the necessary zones */
	picnode = of_find_matching_node(शून्य, mpc52xx_pic_ids);
	पूर्णांकr = of_iomap(picnode, 0);
	अगर (!पूर्णांकr)
		panic(__खाता__	": find_and_map failed on 'mpc5200-pic'. "
				"Check node !");

	np = of_find_matching_node(शून्य, mpc52xx_sdma_ids);
	sdma = of_iomap(np, 0);
	of_node_put(np);
	अगर (!sdma)
		panic(__खाता__	": find_and_map failed on 'mpc5200-bestcomm'. "
				"Check node !");

	pr_debug("MPC5200 IRQ controller mapped to 0x%p\n", पूर्णांकr);

	/* Disable all पूर्णांकerrupt sources. */
	out_be32(&sdma->IntPend, 0xffffffff);	/* 1 means clear pending */
	out_be32(&sdma->IntMask, 0xffffffff);	/* 1 means disabled */
	out_be32(&पूर्णांकr->per_mask, 0x7ffffc00);	/* 1 means disabled */
	out_be32(&पूर्णांकr->मुख्य_mask, 0x00010fff);	/* 1 means disabled */
	पूर्णांकr_ctrl = in_be32(&पूर्णांकr->ctrl);
	पूर्णांकr_ctrl &= 0x00ff0000;	/* Keeps IRQ[0-3] config */
	पूर्णांकr_ctrl |=	0x0f000000 |	/* clear IRQ 0-3 */
			0x00001000 |	/* MEE master बाह्यal enable */
			0x00000000 |	/* 0 means disable IRQ 0-3 */
			0x00000001;	/* CEb route critical normally */
	out_be32(&पूर्णांकr->ctrl, पूर्णांकr_ctrl);

	/* Zero a bunch of the priority settings. */
	out_be32(&पूर्णांकr->per_pri1, 0);
	out_be32(&पूर्णांकr->per_pri2, 0);
	out_be32(&पूर्णांकr->per_pri3, 0);
	out_be32(&पूर्णांकr->मुख्य_pri1, 0);
	out_be32(&पूर्णांकr->मुख्य_pri2, 0);

	/*
	 * As last step, add an irq host to translate the real
	 * hw irq inक्रमmation provided by the ofw to linux virq
	 */
	mpc52xx_irqhost = irq_करोमुख्य_add_linear(picnode,
	                                 MPC52xx_IRQ_HIGHTESTHWIRQ,
	                                 &mpc52xx_irqhost_ops, शून्य);

	अगर (!mpc52xx_irqhost)
		panic(__खाता__ ": Cannot allocate the IRQ host\n");

	irq_set_शेष_host(mpc52xx_irqhost);

	pr_info("MPC52xx PIC is up and running!\n");
पूर्ण

/**
 * mpc52xx_get_irq - Get pending पूर्णांकerrupt number hook function
 *
 * Called by the पूर्णांकerrupt handler to determine what IRQ handler needs to be
 * executed.
 *
 * Status of pending पूर्णांकerrupts is determined by पढ़ोing the encoded status
 * रेजिस्टर.  The encoded status रेजिस्टर has three fields; one क्रम each of the
 * types of पूर्णांकerrupts defined by the controller - 'critical', 'main' and
 * 'peripheral'.  This function पढ़ोs the status रेजिस्टर and वापसs the IRQ
 * number associated with the highest priority pending पूर्णांकerrupt.  'Critical'
 * पूर्णांकerrupts have the highest priority, followed by 'main' पूर्णांकerrupts, and
 * then 'peripheral'.
 *
 * The mpc5200 पूर्णांकerrupt controller can be configured to boost the priority
 * of inभागidual 'peripheral' पूर्णांकerrupts.  If this is the हाल then a special
 * value will appear in either the crit or मुख्य fields indicating a high
 * or medium priority peripheral irq has occurred.
 *
 * This function checks each of the 3 irq request fields and वापसs the
 * first pending पूर्णांकerrupt that it finds.
 *
 * This function also identअगरies a 4th type of पूर्णांकerrupt; 'bestcomm'.  Each
 * bestcomm DMA task can उठाओ the bestcomm peripheral पूर्णांकerrupt.  When this
 * occurs at task-specअगरic IRQ# is decoded so that each task can have its
 * own IRQ handler.
 */
अचिन्हित पूर्णांक mpc52xx_get_irq(व्योम)
अणु
	u32 status;
	पूर्णांक irq;

	status = in_be32(&पूर्णांकr->enc_status);
	अगर (status & 0x00000400) अणु	/* critical */
		irq = (status >> 8) & 0x3;
		अगर (irq == 2)	/* high priority peripheral */
			जाओ peripheral;
		irq |= (MPC52xx_IRQ_L1_CRIT << MPC52xx_IRQ_L1_OFFSET);
	पूर्ण अन्यथा अगर (status & 0x00200000) अणु	/* मुख्य */
		irq = (status >> 16) & 0x1f;
		अगर (irq == 4)	/* low priority peripheral */
			जाओ peripheral;
		irq |= (MPC52xx_IRQ_L1_MAIN << MPC52xx_IRQ_L1_OFFSET);
	पूर्ण अन्यथा अगर (status & 0x20000000) अणु	/* peripheral */
	      peripheral:
		irq = (status >> 24) & 0x1f;
		अगर (irq == 0) अणु	/* bestcomm */
			status = in_be32(&sdma->IntPend);
			irq = ffs(status) - 1;
			irq |= (MPC52xx_IRQ_L1_SDMA << MPC52xx_IRQ_L1_OFFSET);
		पूर्ण अन्यथा अणु
			irq |= (MPC52xx_IRQ_L1_PERP << MPC52xx_IRQ_L1_OFFSET);
		पूर्ण
	पूर्ण अन्यथा अणु
		वापस 0;
	पूर्ण

	वापस irq_linear_revmap(mpc52xx_irqhost, irq);
पूर्ण
