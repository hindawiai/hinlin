<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Support क्रम 'media5200-platform' compatible boards.
 *
 * Copyright (C) 2008 Secret Lab Technologies Ltd.
 *
 * Description:
 * This code implements support क्रम the Freescape Media5200 platक्रमm
 * (built around the MPC5200 SoC).
 *
 * Notable अक्षरacteristic of the Media5200 is the presence of an FPGA
 * that has all बाह्यal IRQ lines routed through it.  This file implements
 * a cascaded पूर्णांकerrupt controller driver which attaches itself to the
 * Virtual IRQ subप्रणाली after the primary mpc5200 पूर्णांकerrupt controller
 * is initialized.
 */

#अघोषित DEBUG

#समावेश <linux/irq.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/mpc52xx.h>

अटल स्थिर काष्ठा of_device_id mpc5200_gpio_ids[] __initस्थिर = अणु
	अणु .compatible = "fsl,mpc5200-gpio", पूर्ण,
	अणु .compatible = "mpc5200-gpio", पूर्ण,
	अणुपूर्ण
पूर्ण;

/* FPGA रेजिस्टर set */
#घोषणा MEDIA5200_IRQ_ENABLE (0x40c)
#घोषणा MEDIA5200_IRQ_STATUS (0x410)
#घोषणा MEDIA5200_NUM_IRQS   (6)
#घोषणा MEDIA5200_IRQ_SHIFT  (32 - MEDIA5200_NUM_IRQS)

काष्ठा media5200_irq अणु
	व्योम __iomem *regs;
	spinlock_t lock;
	काष्ठा irq_करोमुख्य *irqhost;
पूर्ण;
काष्ठा media5200_irq media5200_irq;

अटल व्योम media5200_irq_unmask(काष्ठा irq_data *d)
अणु
	अचिन्हित दीर्घ flags;
	u32 val;

	spin_lock_irqsave(&media5200_irq.lock, flags);
	val = in_be32(media5200_irq.regs + MEDIA5200_IRQ_ENABLE);
	val |= 1 << (MEDIA5200_IRQ_SHIFT + irqd_to_hwirq(d));
	out_be32(media5200_irq.regs + MEDIA5200_IRQ_ENABLE, val);
	spin_unlock_irqrestore(&media5200_irq.lock, flags);
पूर्ण

अटल व्योम media5200_irq_mask(काष्ठा irq_data *d)
अणु
	अचिन्हित दीर्घ flags;
	u32 val;

	spin_lock_irqsave(&media5200_irq.lock, flags);
	val = in_be32(media5200_irq.regs + MEDIA5200_IRQ_ENABLE);
	val &= ~(1 << (MEDIA5200_IRQ_SHIFT + irqd_to_hwirq(d)));
	out_be32(media5200_irq.regs + MEDIA5200_IRQ_ENABLE, val);
	spin_unlock_irqrestore(&media5200_irq.lock, flags);
पूर्ण

अटल काष्ठा irq_chip media5200_irq_chip = अणु
	.name = "Media5200 FPGA",
	.irq_unmask = media5200_irq_unmask,
	.irq_mask = media5200_irq_mask,
	.irq_mask_ack = media5200_irq_mask,
पूर्ण;

अटल व्योम media5200_irq_cascade(काष्ठा irq_desc *desc)
अणु
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	पूर्णांक sub_virq, val;
	u32 status, enable;

	/* Mask off the cascaded IRQ */
	raw_spin_lock(&desc->lock);
	chip->irq_mask(&desc->irq_data);
	raw_spin_unlock(&desc->lock);

	/* Ask the FPGA क्रम IRQ status.  If 'val' is 0, then no irqs
	 * are pending.  'ffs()' is 1 based */
	status = in_be32(media5200_irq.regs + MEDIA5200_IRQ_ENABLE);
	enable = in_be32(media5200_irq.regs + MEDIA5200_IRQ_STATUS);
	val = ffs((status & enable) >> MEDIA5200_IRQ_SHIFT);
	अगर (val) अणु
		sub_virq = irq_linear_revmap(media5200_irq.irqhost, val - 1);
		/* pr_debug("%s: virq=%i s=%.8x e=%.8x hwirq=%i subvirq=%i\n",
		 *          __func__, virq, status, enable, val - 1, sub_virq);
		 */
		generic_handle_irq(sub_virq);
	पूर्ण

	/* Processing करोne; can reenable the cascade now */
	raw_spin_lock(&desc->lock);
	chip->irq_ack(&desc->irq_data);
	अगर (!irqd_irq_disabled(&desc->irq_data))
		chip->irq_unmask(&desc->irq_data);
	raw_spin_unlock(&desc->lock);
पूर्ण

अटल पूर्णांक media5200_irq_map(काष्ठा irq_करोमुख्य *h, अचिन्हित पूर्णांक virq,
			     irq_hw_number_t hw)
अणु
	pr_debug("%s: h=%p, virq=%i, hwirq=%i\n", __func__, h, virq, (पूर्णांक)hw);
	irq_set_chip_data(virq, &media5200_irq);
	irq_set_chip_and_handler(virq, &media5200_irq_chip, handle_level_irq);
	irq_set_status_flags(virq, IRQ_LEVEL);
	वापस 0;
पूर्ण

अटल पूर्णांक media5200_irq_xlate(काष्ठा irq_करोमुख्य *h, काष्ठा device_node *ct,
				 स्थिर u32 *पूर्णांकspec, अचिन्हित पूर्णांक पूर्णांकsize,
				 irq_hw_number_t *out_hwirq,
				 अचिन्हित पूर्णांक *out_flags)
अणु
	अगर (पूर्णांकsize != 2)
		वापस -1;

	pr_debug("%s: bank=%i, number=%i\n", __func__, पूर्णांकspec[0], पूर्णांकspec[1]);
	*out_hwirq = पूर्णांकspec[1];
	*out_flags = IRQ_TYPE_NONE;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops media5200_irq_ops = अणु
	.map = media5200_irq_map,
	.xlate = media5200_irq_xlate,
पूर्ण;

/*
 * Setup Media5200 IRQ mapping
 */
अटल व्योम __init media5200_init_irq(व्योम)
अणु
	काष्ठा device_node *fpga_np;
	पूर्णांक cascade_virq;

	/* First setup the regular MPC5200 पूर्णांकerrupt controller */
	mpc52xx_init_irq();

	/* Now find the FPGA IRQ */
	fpga_np = of_find_compatible_node(शून्य, शून्य, "fsl,media5200-fpga");
	अगर (!fpga_np)
		जाओ out;
	pr_debug("%s: found fpga node: %pOF\n", __func__, fpga_np);

	media5200_irq.regs = of_iomap(fpga_np, 0);
	अगर (!media5200_irq.regs)
		जाओ out;
	pr_debug("%s: mapped to %p\n", __func__, media5200_irq.regs);

	cascade_virq = irq_of_parse_and_map(fpga_np, 0);
	अगर (!cascade_virq)
		जाओ out;
	pr_debug("%s: cascaded on virq=%i\n", __func__, cascade_virq);

	/* Disable all FPGA IRQs */
	out_be32(media5200_irq.regs + MEDIA5200_IRQ_ENABLE, 0);

	spin_lock_init(&media5200_irq.lock);

	media5200_irq.irqhost = irq_करोमुख्य_add_linear(fpga_np,
			MEDIA5200_NUM_IRQS, &media5200_irq_ops, &media5200_irq);
	अगर (!media5200_irq.irqhost)
		जाओ out;
	pr_debug("%s: allocated irqhost\n", __func__);

	irq_set_handler_data(cascade_virq, &media5200_irq);
	irq_set_chained_handler(cascade_virq, media5200_irq_cascade);

	वापस;

 out:
	pr_err("Could not find Media5200 FPGA; PCI interrupts will not work\n");
पूर्ण

/*
 * Setup the architecture
 */
अटल व्योम __init media5200_setup_arch(व्योम)
अणु

	काष्ठा device_node *np;
	काष्ठा mpc52xx_gpio __iomem *gpio;
	u32 port_config;

	अगर (ppc_md.progress)
		ppc_md.progress("media5200_setup_arch()", 0);

	/* Map important रेजिस्टरs from the पूर्णांकernal memory map */
	mpc52xx_map_common_devices();

	/* Some mpc5200 & mpc5200b related configuration */
	mpc5200_setup_xlb_arbiter();

	np = of_find_matching_node(शून्य, mpc5200_gpio_ids);
	gpio = of_iomap(np, 0);
	of_node_put(np);
	अगर (!gpio) अणु
		prपूर्णांकk(KERN_ERR "%s() failed. expect abnormal behavior\n",
		       __func__);
		वापस;
	पूर्ण

	/* Set port config */
	port_config = in_be32(&gpio->port_config);

	port_config &= ~0x03000000;	/* ATA CS is on csb_4/5		*/
	port_config |=  0x01000000;

	out_be32(&gpio->port_config, port_config);

	/* Unmap zone */
	iounmap(gpio);

पूर्ण

/* list of the supported boards */
अटल स्थिर अक्षर * स्थिर board[] __initस्थिर = अणु
	"fsl,media5200",
	शून्य
पूर्ण;

/*
 * Called very early, MMU is off, device-tree isn't unflattened
 */
अटल पूर्णांक __init media5200_probe(व्योम)
अणु
	वापस of_device_compatible_match(of_root, board);
पूर्ण

define_machine(media5200_platक्रमm) अणु
	.name		= "media5200-platform",
	.probe		= media5200_probe,
	.setup_arch	= media5200_setup_arch,
	.discover_phbs	= mpc52xx_setup_pci,
	.init		= mpc52xx_declare_of_platक्रमm_devices,
	.init_IRQ	= media5200_init_irq,
	.get_irq	= mpc52xx_get_irq,
	.restart	= mpc52xx_restart,
	.calibrate_decr	= generic_calibrate_decr,
पूर्ण;
