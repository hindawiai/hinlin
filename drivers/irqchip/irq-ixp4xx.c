<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * irqchip क्रम the IXP4xx पूर्णांकerrupt controller
 * Copyright (C) 2019 Linus Walleij <linus.walleij@linaro.org>
 *
 * Based on arch/arm/mach-ixp4xx/common.c
 * Copyright 2002 (C) Intel Corporation
 * Copyright 2003-2004 (C) MontaVista, Software, Inc.
 * Copyright (C) Deepak Saxena <dsaxena@plनिकासy.net>
 */
#समावेश <linux/bitops.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/irq.h>
#समावेश <linux/पन.स>
#समावेश <linux/irqchip.h>
#समावेश <linux/irqchip/irq-ixp4xx.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/cpu.h>

#समावेश <यंत्र/exception.h>
#समावेश <यंत्र/mach/irq.h>

#घोषणा IXP4XX_ICPR	0x00 /* Interrupt Status */
#घोषणा IXP4XX_ICMR	0x04 /* Interrupt Enable */
#घोषणा IXP4XX_ICLR	0x08 /* Interrupt IRQ/FIQ Select */
#घोषणा IXP4XX_ICIP	0x0C /* IRQ Status */
#घोषणा IXP4XX_ICFP	0x10 /* FIQ Status */
#घोषणा IXP4XX_ICHR	0x14 /* Interrupt Priority */
#घोषणा IXP4XX_ICIH	0x18 /* IRQ Highest Pri Int */
#घोषणा IXP4XX_ICFH	0x1C /* FIQ Highest Pri Int */

/* IXP43x and IXP46x-only */
#घोषणा	IXP4XX_ICPR2	0x20 /* Interrupt Status 2 */
#घोषणा	IXP4XX_ICMR2	0x24 /* Interrupt Enable 2 */
#घोषणा	IXP4XX_ICLR2	0x28 /* Interrupt IRQ/FIQ Select 2 */
#घोषणा IXP4XX_ICIP2	0x2C /* IRQ Status */
#घोषणा IXP4XX_ICFP2	0x30 /* FIQ Status */
#घोषणा IXP4XX_ICEEN	0x34 /* Error High Pri Enable */

/**
 * काष्ठा ixp4xx_irq - state container क्रम the Faraday IRQ controller
 * @irqbase: IRQ controller memory base in भव memory
 * @is_356: अगर this is an IXP43x, IXP45x or IX46x SoC (with 64 IRQs)
 * @irqchip: irqchip क्रम this instance
 * @करोमुख्य: IRQ करोमुख्य क्रम this instance
 */
काष्ठा ixp4xx_irq अणु
	व्योम __iomem *irqbase;
	bool is_356;
	काष्ठा irq_chip irqchip;
	काष्ठा irq_करोमुख्य *करोमुख्य;
पूर्ण;

/* Local अटल state container */
अटल काष्ठा ixp4xx_irq ixirq;

/* GPIO Clocks */
#घोषणा IXP4XX_GPIO_CLK_0		14
#घोषणा IXP4XX_GPIO_CLK_1		15

अटल पूर्णांक ixp4xx_set_irq_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक type)
अणु
	/* All are level active high (निश्चितed) here */
	अगर (type != IRQ_TYPE_LEVEL_HIGH)
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल व्योम ixp4xx_irq_mask(काष्ठा irq_data *d)
अणु
	काष्ठा ixp4xx_irq *ixi = irq_data_get_irq_chip_data(d);
	u32 val;

	अगर (ixi->is_356 && d->hwirq >= 32) अणु
		val = __raw_पढ़ोl(ixi->irqbase + IXP4XX_ICMR2);
		val &= ~BIT(d->hwirq - 32);
		__raw_ग_लिखोl(val, ixi->irqbase + IXP4XX_ICMR2);
	पूर्ण अन्यथा अणु
		val = __raw_पढ़ोl(ixi->irqbase + IXP4XX_ICMR);
		val &= ~BIT(d->hwirq);
		__raw_ग_लिखोl(val, ixi->irqbase + IXP4XX_ICMR);
	पूर्ण
पूर्ण

/*
 * Level triggered पूर्णांकerrupts on GPIO lines can only be cleared when the
 * पूर्णांकerrupt condition disappears.
 */
अटल व्योम ixp4xx_irq_unmask(काष्ठा irq_data *d)
अणु
	काष्ठा ixp4xx_irq *ixi = irq_data_get_irq_chip_data(d);
	u32 val;

	अगर (ixi->is_356 && d->hwirq >= 32) अणु
		val = __raw_पढ़ोl(ixi->irqbase + IXP4XX_ICMR2);
		val |= BIT(d->hwirq - 32);
		__raw_ग_लिखोl(val, ixi->irqbase + IXP4XX_ICMR2);
	पूर्ण अन्यथा अणु
		val = __raw_पढ़ोl(ixi->irqbase + IXP4XX_ICMR);
		val |= BIT(d->hwirq);
		__raw_ग_लिखोl(val, ixi->irqbase + IXP4XX_ICMR);
	पूर्ण
पूर्ण

यंत्रlinkage व्योम __exception_irq_entry ixp4xx_handle_irq(काष्ठा pt_regs *regs)
अणु
	काष्ठा ixp4xx_irq *ixi = &ixirq;
	अचिन्हित दीर्घ status;
	पूर्णांक i;

	status = __raw_पढ़ोl(ixi->irqbase + IXP4XX_ICIP);
	क्रम_each_set_bit(i, &status, 32)
		handle_करोमुख्य_irq(ixi->करोमुख्य, i, regs);

	/*
	 * IXP465/IXP435 has an upper IRQ status रेजिस्टर
	 */
	अगर (ixi->is_356) अणु
		status = __raw_पढ़ोl(ixi->irqbase + IXP4XX_ICIP2);
		क्रम_each_set_bit(i, &status, 32)
			handle_करोमुख्य_irq(ixi->करोमुख्य, i + 32, regs);
	पूर्ण
पूर्ण

अटल पूर्णांक ixp4xx_irq_करोमुख्य_translate(काष्ठा irq_करोमुख्य *करोमुख्य,
				       काष्ठा irq_fwspec *fwspec,
				       अचिन्हित दीर्घ *hwirq,
				       अचिन्हित पूर्णांक *type)
अणु
	/* We support standard DT translation */
	अगर (is_of_node(fwspec->fwnode) && fwspec->param_count == 2) अणु
		*hwirq = fwspec->param[0];
		*type = fwspec->param[1];
		वापस 0;
	पूर्ण

	अगर (is_fwnode_irqchip(fwspec->fwnode)) अणु
		अगर (fwspec->param_count != 2)
			वापस -EINVAL;
		*hwirq = fwspec->param[0];
		*type = fwspec->param[1];
		WARN_ON(*type == IRQ_TYPE_NONE);
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक ixp4xx_irq_करोमुख्य_alloc(काष्ठा irq_करोमुख्य *d,
				   अचिन्हित पूर्णांक irq, अचिन्हित पूर्णांक nr_irqs,
				   व्योम *data)
अणु
	काष्ठा ixp4xx_irq *ixi = d->host_data;
	irq_hw_number_t hwirq;
	अचिन्हित पूर्णांक type = IRQ_TYPE_NONE;
	काष्ठा irq_fwspec *fwspec = data;
	पूर्णांक ret;
	पूर्णांक i;

	ret = ixp4xx_irq_करोमुख्य_translate(d, fwspec, &hwirq, &type);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < nr_irqs; i++) अणु
		/*
		 * TODO: after converting IXP4xx to only device tree, set
		 * handle_bad_irq as शेष handler and assume all consumers
		 * call .set_type() as this is provided in the second cell in
		 * the device tree phandle.
		 */
		irq_करोमुख्य_set_info(d,
				    irq + i,
				    hwirq + i,
				    &ixi->irqchip,
				    ixi,
				    handle_level_irq,
				    शून्य, शून्य);
		irq_set_probe(irq + i);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * This needs to be a hierarchical irqकरोमुख्य to work well with the
 * GPIO irqchip (which is lower in the hierarchy)
 */
अटल स्थिर काष्ठा irq_करोमुख्य_ops ixp4xx_irqकरोमुख्य_ops = अणु
	.translate = ixp4xx_irq_करोमुख्य_translate,
	.alloc = ixp4xx_irq_करोमुख्य_alloc,
	.मुक्त = irq_करोमुख्य_मुक्त_irqs_common,
पूर्ण;

/**
 * ixp4xx_get_irq_करोमुख्य() - retrieve the ixp4xx irq करोमुख्य
 *
 * This function will go away when we transition to DT probing.
 */
काष्ठा irq_करोमुख्य *ixp4xx_get_irq_करोमुख्य(व्योम)
अणु
	काष्ठा ixp4xx_irq *ixi = &ixirq;

	वापस ixi->करोमुख्य;
पूर्ण
EXPORT_SYMBOL_GPL(ixp4xx_get_irq_करोमुख्य);

/*
 * This is the Linux IRQ to hwirq mapping table. This goes away when
 * we have DT support as all IRQ resources are defined in the device
 * tree. It will रेजिस्टर all the IRQs that are not used by the hierarchical
 * GPIO IRQ chip. The "holes" inbetween these IRQs will be requested by
 * the GPIO driver using . This is a step-gap solution.
 */
काष्ठा ixp4xx_irq_chunk अणु
	पूर्णांक irq;
	पूर्णांक hwirq;
	पूर्णांक nr_irqs;
पूर्ण;

अटल स्थिर काष्ठा ixp4xx_irq_chunk ixp4xx_irq_chunks[] = अणु
	अणु
		.irq = 16,
		.hwirq = 0,
		.nr_irqs = 6,
	पूर्ण,
	अणु
		.irq = 24,
		.hwirq = 8,
		.nr_irqs = 11,
	पूर्ण,
	अणु
		.irq = 46,
		.hwirq = 30,
		.nr_irqs = 2,
	पूर्ण,
	/* Only on the 436 variants */
	अणु
		.irq = 48,
		.hwirq = 32,
		.nr_irqs = 10,
	पूर्ण,
पूर्ण;

/**
 * ixp4x_irq_setup() - Common setup code क्रम the IXP4xx पूर्णांकerrupt controller
 * @ixi: State container
 * @irqbase: Virtual memory base क्रम the पूर्णांकerrupt controller
 * @fwnode: Corresponding fwnode असलtraction क्रम this controller
 * @is_356: अगर this is an IXP43x, IXP45x or IXP46x SoC variant
 */
अटल पूर्णांक __init ixp4xx_irq_setup(काष्ठा ixp4xx_irq *ixi,
				   व्योम __iomem *irqbase,
				   काष्ठा fwnode_handle *fwnode,
				   bool is_356)
अणु
	पूर्णांक nr_irqs;

	ixi->irqbase = irqbase;
	ixi->is_356 = is_356;

	/* Route all sources to IRQ instead of FIQ */
	__raw_ग_लिखोl(0x0, ixi->irqbase + IXP4XX_ICLR);

	/* Disable all पूर्णांकerrupts */
	__raw_ग_लिखोl(0x0, ixi->irqbase + IXP4XX_ICMR);

	अगर (is_356) अणु
		/* Route upper 32 sources to IRQ instead of FIQ */
		__raw_ग_लिखोl(0x0, ixi->irqbase + IXP4XX_ICLR2);

		/* Disable upper 32 पूर्णांकerrupts */
		__raw_ग_लिखोl(0x0, ixi->irqbase + IXP4XX_ICMR2);

		nr_irqs = 64;
	पूर्ण अन्यथा अणु
		nr_irqs = 32;
	पूर्ण

	ixi->irqchip.name = "IXP4xx";
	ixi->irqchip.irq_mask = ixp4xx_irq_mask;
	ixi->irqchip.irq_unmask	= ixp4xx_irq_unmask;
	ixi->irqchip.irq_set_type = ixp4xx_set_irq_type;

	ixi->करोमुख्य = irq_करोमुख्य_create_linear(fwnode, nr_irqs,
					       &ixp4xx_irqकरोमुख्य_ops,
					       ixi);
	अगर (!ixi->करोमुख्य) अणु
		pr_crit("IXP4XX: can not add primary irqdomain\n");
		वापस -ENODEV;
	पूर्ण

	set_handle_irq(ixp4xx_handle_irq);

	वापस 0;
पूर्ण

/**
 * ixp4xx_irq_init() - Function to initialize the irqchip from boardfiles
 * @irqbase: physical base क्रम the irq controller
 * @is_356: अगर this is an IXP43x, IXP45x or IXP46x SoC variant
 */
व्योम __init ixp4xx_irq_init(resource_माप_प्रकार irqbase,
			    bool is_356)
अणु
	काष्ठा ixp4xx_irq *ixi = &ixirq;
	व्योम __iomem *base;
	काष्ठा fwnode_handle *fwnode;
	काष्ठा irq_fwspec fwspec;
	पूर्णांक nr_chunks;
	पूर्णांक ret;
	पूर्णांक i;

	base = ioremap(irqbase, 0x100);
	अगर (!base) अणु
		pr_crit("IXP4XX: could not ioremap interrupt controller\n");
		वापस;
	पूर्ण
	fwnode = irq_करोमुख्य_alloc_fwnode(&irqbase);
	अगर (!fwnode) अणु
		pr_crit("IXP4XX: no domain handle\n");
		वापस;
	पूर्ण
	ret = ixp4xx_irq_setup(ixi, base, fwnode, is_356);
	अगर (ret) अणु
		pr_crit("IXP4XX: failed to set up irqchip\n");
		irq_करोमुख्य_मुक्त_fwnode(fwnode);
	पूर्ण

	nr_chunks = ARRAY_SIZE(ixp4xx_irq_chunks);
	अगर (!is_356)
		nr_chunks--;

	/*
	 * After adding OF support, this is no दीर्घer needed: irqs
	 * will be allocated क्रम the respective fwnodes.
	 */
	क्रम (i = 0; i < nr_chunks; i++) अणु
		स्थिर काष्ठा ixp4xx_irq_chunk *chunk = &ixp4xx_irq_chunks[i];

		pr_info("Allocate Linux IRQs %d..%d HW IRQs %d..%d\n",
			chunk->irq, chunk->irq + chunk->nr_irqs - 1,
			chunk->hwirq, chunk->hwirq + chunk->nr_irqs - 1);
		fwspec.fwnode = fwnode;
		fwspec.param[0] = chunk->hwirq;
		fwspec.param[1] = IRQ_TYPE_LEVEL_HIGH;
		fwspec.param_count = 2;
		ret = __irq_करोमुख्य_alloc_irqs(ixi->करोमुख्य,
					      chunk->irq,
					      chunk->nr_irqs,
					      NUMA_NO_NODE,
					      &fwspec,
					      false,
					      शून्य);
		अगर (ret < 0) अणु
			pr_crit("IXP4XX: can not allocate irqs in hierarchy %d\n",
				ret);
			वापस;
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(ixp4xx_irq_init);

#अगर_घोषित CONFIG_OF
पूर्णांक __init ixp4xx_of_init_irq(काष्ठा device_node *np,
			      काष्ठा device_node *parent)
अणु
	काष्ठा ixp4xx_irq *ixi = &ixirq;
	व्योम __iomem *base;
	काष्ठा fwnode_handle *fwnode;
	bool is_356;
	पूर्णांक ret;

	base = of_iomap(np, 0);
	अगर (!base) अणु
		pr_crit("IXP4XX: could not ioremap interrupt controller\n");
		वापस -ENODEV;
	पूर्ण
	fwnode = of_node_to_fwnode(np);

	/* These chip variants have 64 पूर्णांकerrupts */
	is_356 = of_device_is_compatible(np, "intel,ixp43x-interrupt") ||
		of_device_is_compatible(np, "intel,ixp45x-interrupt") ||
		of_device_is_compatible(np, "intel,ixp46x-interrupt");

	ret = ixp4xx_irq_setup(ixi, base, fwnode, is_356);
	अगर (ret)
		pr_crit("IXP4XX: failed to set up irqchip\n");

	वापस ret;
पूर्ण
IRQCHIP_DECLARE(ixp42x, "intel,ixp42x-interrupt",
		ixp4xx_of_init_irq);
IRQCHIP_DECLARE(ixp43x, "intel,ixp43x-interrupt",
		ixp4xx_of_init_irq);
IRQCHIP_DECLARE(ixp45x, "intel,ixp45x-interrupt",
		ixp4xx_of_init_irq);
IRQCHIP_DECLARE(ixp46x, "intel,ixp46x-interrupt",
		ixp4xx_of_init_irq);
#पूर्ण_अगर
