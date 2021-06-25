<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
// Copyright 2021 Jonathan Neuschथअfer

#समावेश <linux/irqchip.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/prपूर्णांकk.h>

#समावेश <यंत्र/exception.h>

#घोषणा AIC_SCR(x)	((x)*4)	/* Source control रेजिस्टरs */
#घोषणा AIC_GEN		0x84	/* Interrupt group enable control रेजिस्टर */
#घोषणा AIC_GRSR	0x88	/* Interrupt group raw status रेजिस्टर */
#घोषणा AIC_IRSR	0x100	/* Interrupt raw status रेजिस्टर */
#घोषणा AIC_IASR	0x104	/* Interrupt active status रेजिस्टर */
#घोषणा AIC_ISR		0x108	/* Interrupt status रेजिस्टर */
#घोषणा AIC_IPER	0x10c	/* Interrupt priority encoding रेजिस्टर */
#घोषणा AIC_ISNR	0x110	/* Interrupt source number रेजिस्टर */
#घोषणा AIC_IMR		0x114	/* Interrupt mask रेजिस्टर */
#घोषणा AIC_OISR	0x118	/* Output पूर्णांकerrupt status रेजिस्टर */
#घोषणा AIC_MECR	0x120	/* Mask enable command रेजिस्टर */
#घोषणा AIC_MDCR	0x124	/* Mask disable command रेजिस्टर */
#घोषणा AIC_SSCR	0x128	/* Source set command रेजिस्टर */
#घोषणा AIC_SCCR	0x12c	/* Source clear command रेजिस्टर */
#घोषणा AIC_EOSCR	0x130	/* End of service command रेजिस्टर */

#घोषणा AIC_SCR_SRCTYPE_LOW_LEVEL	(0 << 6)
#घोषणा AIC_SCR_SRCTYPE_HIGH_LEVEL	(1 << 6)
#घोषणा AIC_SCR_SRCTYPE_NEG_EDGE	(2 << 6)
#घोषणा AIC_SCR_SRCTYPE_POS_EDGE	(3 << 6)
#घोषणा AIC_SCR_PRIORITY(x)		(x)
#घोषणा AIC_SCR_PRIORITY_MASK		0x7

#घोषणा AIC_NUM_IRQS		32

काष्ठा wpcm450_aic अणु
	व्योम __iomem *regs;
	काष्ठा irq_करोमुख्य *करोमुख्य;
पूर्ण;

अटल काष्ठा wpcm450_aic *aic;

अटल व्योम wpcm450_aic_init_hw(व्योम)
अणु
	पूर्णांक i;

	/* Disable (mask) all पूर्णांकerrupts */
	ग_लिखोl(0xffffffff, aic->regs + AIC_MDCR);

	/*
	 * Make sure the पूर्णांकerrupt controller is पढ़ोy to serve new पूर्णांकerrupts.
	 * Reading from IPER indicates that the nIRQ संकेत may be deनिश्चितed,
	 * and writing to EOSCR indicates that पूर्णांकerrupt handling has finished.
	 */
	पढ़ोl(aic->regs + AIC_IPER);
	ग_लिखोl(0, aic->regs + AIC_EOSCR);

	/* Initialize trigger mode and priority of each पूर्णांकerrupt source */
	क्रम (i = 0; i < AIC_NUM_IRQS; i++)
		ग_लिखोl(AIC_SCR_SRCTYPE_HIGH_LEVEL | AIC_SCR_PRIORITY(7),
		       aic->regs + AIC_SCR(i));
पूर्ण

अटल व्योम __exception_irq_entry wpcm450_aic_handle_irq(काष्ठा pt_regs *regs)
अणु
	पूर्णांक hwirq;

	/* Determine the पूर्णांकerrupt source */
	/* Read IPER to संकेत that nIRQ can be de-निश्चितed */
	hwirq = पढ़ोl(aic->regs + AIC_IPER) / 4;

	handle_करोमुख्य_irq(aic->करोमुख्य, hwirq, regs);
पूर्ण

अटल व्योम wpcm450_aic_eoi(काष्ठा irq_data *d)
अणु
	/* Signal end-of-service */
	ग_लिखोl(0, aic->regs + AIC_EOSCR);
पूर्ण

अटल व्योम wpcm450_aic_mask(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक mask = BIT(d->hwirq);

	/* Disable (mask) the पूर्णांकerrupt */
	ग_लिखोl(mask, aic->regs + AIC_MDCR);
पूर्ण

अटल व्योम wpcm450_aic_unmask(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक mask = BIT(d->hwirq);

	/* Enable (unmask) the पूर्णांकerrupt */
	ग_लिखोl(mask, aic->regs + AIC_MECR);
पूर्ण

अटल पूर्णांक wpcm450_aic_set_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक flow_type)
अणु
	/*
	 * The hardware supports high/low level, as well as rising/falling edge
	 * modes, and the DT binding accommodates क्रम that, but as दीर्घ as
	 * other modes than high level mode are not used and can't be tested,
	 * they are rejected in this driver.
	 */
	अगर ((flow_type & IRQ_TYPE_SENSE_MASK) != IRQ_TYPE_LEVEL_HIGH)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल काष्ठा irq_chip wpcm450_aic_chip = अणु
	.name = "wpcm450-aic",
	.irq_eoi = wpcm450_aic_eoi,
	.irq_mask = wpcm450_aic_mask,
	.irq_unmask = wpcm450_aic_unmask,
	.irq_set_type = wpcm450_aic_set_type,
पूर्ण;

अटल पूर्णांक wpcm450_aic_map(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक irq, irq_hw_number_t hwirq)
अणु
	अगर (hwirq >= AIC_NUM_IRQS)
		वापस -EPERM;

	irq_set_chip_and_handler(irq, &wpcm450_aic_chip, handle_fasteoi_irq);
	irq_set_chip_data(irq, aic);
	irq_set_probe(irq);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops wpcm450_aic_ops = अणु
	.map = wpcm450_aic_map,
	.xlate = irq_करोमुख्य_xlate_twocell,
पूर्ण;

अटल पूर्णांक __init wpcm450_aic_of_init(काष्ठा device_node *node,
				      काष्ठा device_node *parent)
अणु
	अगर (parent)
		वापस -EINVAL;

	aic = kzalloc(माप(*aic), GFP_KERNEL);
	अगर (!aic)
		वापस -ENOMEM;

	aic->regs = of_iomap(node, 0);
	अगर (!aic->regs) अणु
		pr_err("Failed to map WPCM450 AIC registers\n");
		वापस -ENOMEM;
	पूर्ण

	wpcm450_aic_init_hw();

	set_handle_irq(wpcm450_aic_handle_irq);

	aic->करोमुख्य = irq_करोमुख्य_add_linear(node, AIC_NUM_IRQS, &wpcm450_aic_ops, aic);

	वापस 0;
पूर्ण

IRQCHIP_DECLARE(wpcm450_aic, "nuvoton,wpcm450-aic", wpcm450_aic_of_init);
