<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Renesas INTC External IRQ Pin Driver
 *
 *  Copyright (C) 2013 Magnus Damm
 */

#समावेश <linux/init.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pm_runसमय.स>

#घोषणा INTC_IRQPIN_MAX 8 /* maximum 8 पूर्णांकerrupts per driver instance */

#घोषणा INTC_IRQPIN_REG_SENSE 0 /* ICRn */
#घोषणा INTC_IRQPIN_REG_PRIO 1 /* INTPRInn */
#घोषणा INTC_IRQPIN_REG_SOURCE 2 /* INTREQnn */
#घोषणा INTC_IRQPIN_REG_MASK 3 /* INTMSKnn */
#घोषणा INTC_IRQPIN_REG_CLEAR 4 /* INTMSKCLRnn */
#घोषणा INTC_IRQPIN_REG_NR_MANDATORY 5
#घोषणा INTC_IRQPIN_REG_IRLM 5 /* ICR0 with IRLM bit (optional) */
#घोषणा INTC_IRQPIN_REG_NR 6

/* INTC बाह्यal IRQ PIN hardware रेजिस्टर access:
 *
 * SENSE is पढ़ो-ग_लिखो 32-bit with 2-bits or 4-bits per IRQ (*)
 * PRIO is पढ़ो-ग_लिखो 32-bit with 4-bits per IRQ (**)
 * SOURCE is पढ़ो-only 32-bit or 8-bit with 1-bit per IRQ (***)
 * MASK is ग_लिखो-only 32-bit or 8-bit with 1-bit per IRQ (***)
 * CLEAR is ग_लिखो-only 32-bit or 8-bit with 1-bit per IRQ (***)
 *
 * (*) May be accessed by more than one driver instance - lock needed
 * (**) Read-modअगरy-ग_लिखो access by one driver instance - lock needed
 * (***) Accessed by one driver instance only - no locking needed
 */

काष्ठा पूर्णांकc_irqpin_iomem अणु
	व्योम __iomem *iomem;
	अचिन्हित दीर्घ (*पढ़ो)(व्योम __iomem *iomem);
	व्योम (*ग_लिखो)(व्योम __iomem *iomem, अचिन्हित दीर्घ data);
	पूर्णांक width;
पूर्ण;

काष्ठा पूर्णांकc_irqpin_irq अणु
	पूर्णांक hw_irq;
	पूर्णांक requested_irq;
	पूर्णांक करोमुख्य_irq;
	काष्ठा पूर्णांकc_irqpin_priv *p;
पूर्ण;

काष्ठा पूर्णांकc_irqpin_priv अणु
	काष्ठा पूर्णांकc_irqpin_iomem iomem[INTC_IRQPIN_REG_NR];
	काष्ठा पूर्णांकc_irqpin_irq irq[INTC_IRQPIN_MAX];
	अचिन्हित पूर्णांक sense_bitfield_width;
	काष्ठा platक्रमm_device *pdev;
	काष्ठा irq_chip irq_chip;
	काष्ठा irq_करोमुख्य *irq_करोमुख्य;
	atomic_t wakeup_path;
	अचिन्हित shared_irqs:1;
	u8 shared_irq_mask;
पूर्ण;

काष्ठा पूर्णांकc_irqpin_config अणु
	पूर्णांक irlm_bit;		/* -1 अगर non-existent */
पूर्ण;

अटल अचिन्हित दीर्घ पूर्णांकc_irqpin_पढ़ो32(व्योम __iomem *iomem)
अणु
	वापस ioपढ़ो32(iomem);
पूर्ण

अटल अचिन्हित दीर्घ पूर्णांकc_irqpin_पढ़ो8(व्योम __iomem *iomem)
अणु
	वापस ioपढ़ो8(iomem);
पूर्ण

अटल व्योम पूर्णांकc_irqpin_ग_लिखो32(व्योम __iomem *iomem, अचिन्हित दीर्घ data)
अणु
	ioग_लिखो32(data, iomem);
पूर्ण

अटल व्योम पूर्णांकc_irqpin_ग_लिखो8(व्योम __iomem *iomem, अचिन्हित दीर्घ data)
अणु
	ioग_लिखो8(data, iomem);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ पूर्णांकc_irqpin_पढ़ो(काष्ठा पूर्णांकc_irqpin_priv *p,
					     पूर्णांक reg)
अणु
	काष्ठा पूर्णांकc_irqpin_iomem *i = &p->iomem[reg];

	वापस i->पढ़ो(i->iomem);
पूर्ण

अटल अंतरभूत व्योम पूर्णांकc_irqpin_ग_लिखो(काष्ठा पूर्णांकc_irqpin_priv *p,
				     पूर्णांक reg, अचिन्हित दीर्घ data)
अणु
	काष्ठा पूर्णांकc_irqpin_iomem *i = &p->iomem[reg];

	i->ग_लिखो(i->iomem, data);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ पूर्णांकc_irqpin_hwirq_mask(काष्ठा पूर्णांकc_irqpin_priv *p,
						   पूर्णांक reg, पूर्णांक hw_irq)
अणु
	वापस BIT((p->iomem[reg].width - 1) - hw_irq);
पूर्ण

अटल अंतरभूत व्योम पूर्णांकc_irqpin_irq_ग_लिखो_hwirq(काष्ठा पूर्णांकc_irqpin_priv *p,
					       पूर्णांक reg, पूर्णांक hw_irq)
अणु
	पूर्णांकc_irqpin_ग_लिखो(p, reg, पूर्णांकc_irqpin_hwirq_mask(p, reg, hw_irq));
पूर्ण

अटल DEFINE_RAW_SPINLOCK(पूर्णांकc_irqpin_lock); /* only used by slow path */

अटल व्योम पूर्णांकc_irqpin_पढ़ो_modअगरy_ग_लिखो(काष्ठा पूर्णांकc_irqpin_priv *p,
					  पूर्णांक reg, पूर्णांक shअगरt,
					  पूर्णांक width, पूर्णांक value)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ पंचांगp;

	raw_spin_lock_irqsave(&पूर्णांकc_irqpin_lock, flags);

	पंचांगp = पूर्णांकc_irqpin_पढ़ो(p, reg);
	पंचांगp &= ~(((1 << width) - 1) << shअगरt);
	पंचांगp |= value << shअगरt;
	पूर्णांकc_irqpin_ग_लिखो(p, reg, पंचांगp);

	raw_spin_unlock_irqrestore(&पूर्णांकc_irqpin_lock, flags);
पूर्ण

अटल व्योम पूर्णांकc_irqpin_mask_unmask_prio(काष्ठा पूर्णांकc_irqpin_priv *p,
					 पूर्णांक irq, पूर्णांक करो_mask)
अणु
	/* The PRIO रेजिस्टर is assumed to be 32-bit with fixed 4-bit fields. */
	पूर्णांक bitfield_width = 4;
	पूर्णांक shअगरt = 32 - (irq + 1) * bitfield_width;

	पूर्णांकc_irqpin_पढ़ो_modअगरy_ग_लिखो(p, INTC_IRQPIN_REG_PRIO,
				      shअगरt, bitfield_width,
				      करो_mask ? 0 : (1 << bitfield_width) - 1);
पूर्ण

अटल पूर्णांक पूर्णांकc_irqpin_set_sense(काष्ठा पूर्णांकc_irqpin_priv *p, पूर्णांक irq, पूर्णांक value)
अणु
	/* The SENSE रेजिस्टर is assumed to be 32-bit. */
	पूर्णांक bitfield_width = p->sense_bitfield_width;
	पूर्णांक shअगरt = 32 - (irq + 1) * bitfield_width;

	dev_dbg(&p->pdev->dev, "sense irq = %d, mode = %d\n", irq, value);

	अगर (value >= (1 << bitfield_width))
		वापस -EINVAL;

	पूर्णांकc_irqpin_पढ़ो_modअगरy_ग_लिखो(p, INTC_IRQPIN_REG_SENSE, shअगरt,
				      bitfield_width, value);
	वापस 0;
पूर्ण

अटल व्योम पूर्णांकc_irqpin_dbg(काष्ठा पूर्णांकc_irqpin_irq *i, अक्षर *str)
अणु
	dev_dbg(&i->p->pdev->dev, "%s (%d:%d:%d)\n",
		str, i->requested_irq, i->hw_irq, i->करोमुख्य_irq);
पूर्ण

अटल व्योम पूर्णांकc_irqpin_irq_enable(काष्ठा irq_data *d)
अणु
	काष्ठा पूर्णांकc_irqpin_priv *p = irq_data_get_irq_chip_data(d);
	पूर्णांक hw_irq = irqd_to_hwirq(d);

	पूर्णांकc_irqpin_dbg(&p->irq[hw_irq], "enable");
	पूर्णांकc_irqpin_irq_ग_लिखो_hwirq(p, INTC_IRQPIN_REG_CLEAR, hw_irq);
पूर्ण

अटल व्योम पूर्णांकc_irqpin_irq_disable(काष्ठा irq_data *d)
अणु
	काष्ठा पूर्णांकc_irqpin_priv *p = irq_data_get_irq_chip_data(d);
	पूर्णांक hw_irq = irqd_to_hwirq(d);

	पूर्णांकc_irqpin_dbg(&p->irq[hw_irq], "disable");
	पूर्णांकc_irqpin_irq_ग_लिखो_hwirq(p, INTC_IRQPIN_REG_MASK, hw_irq);
पूर्ण

अटल व्योम पूर्णांकc_irqpin_shared_irq_enable(काष्ठा irq_data *d)
अणु
	काष्ठा पूर्णांकc_irqpin_priv *p = irq_data_get_irq_chip_data(d);
	पूर्णांक hw_irq = irqd_to_hwirq(d);

	पूर्णांकc_irqpin_dbg(&p->irq[hw_irq], "shared enable");
	पूर्णांकc_irqpin_irq_ग_लिखो_hwirq(p, INTC_IRQPIN_REG_CLEAR, hw_irq);

	p->shared_irq_mask &= ~BIT(hw_irq);
पूर्ण

अटल व्योम पूर्णांकc_irqpin_shared_irq_disable(काष्ठा irq_data *d)
अणु
	काष्ठा पूर्णांकc_irqpin_priv *p = irq_data_get_irq_chip_data(d);
	पूर्णांक hw_irq = irqd_to_hwirq(d);

	पूर्णांकc_irqpin_dbg(&p->irq[hw_irq], "shared disable");
	पूर्णांकc_irqpin_irq_ग_लिखो_hwirq(p, INTC_IRQPIN_REG_MASK, hw_irq);

	p->shared_irq_mask |= BIT(hw_irq);
पूर्ण

अटल व्योम पूर्णांकc_irqpin_irq_enable_क्रमce(काष्ठा irq_data *d)
अणु
	काष्ठा पूर्णांकc_irqpin_priv *p = irq_data_get_irq_chip_data(d);
	पूर्णांक irq = p->irq[irqd_to_hwirq(d)].requested_irq;

	पूर्णांकc_irqpin_irq_enable(d);

	/* enable पूर्णांकerrupt through parent पूर्णांकerrupt controller,
	 * assumes non-shared पूर्णांकerrupt with 1:1 mapping
	 * needed क्रम busted IRQs on some SoCs like sh73a0
	 */
	irq_get_chip(irq)->irq_unmask(irq_get_irq_data(irq));
पूर्ण

अटल व्योम पूर्णांकc_irqpin_irq_disable_क्रमce(काष्ठा irq_data *d)
अणु
	काष्ठा पूर्णांकc_irqpin_priv *p = irq_data_get_irq_chip_data(d);
	पूर्णांक irq = p->irq[irqd_to_hwirq(d)].requested_irq;

	/* disable पूर्णांकerrupt through parent पूर्णांकerrupt controller,
	 * assumes non-shared पूर्णांकerrupt with 1:1 mapping
	 * needed क्रम busted IRQs on some SoCs like sh73a0
	 */
	irq_get_chip(irq)->irq_mask(irq_get_irq_data(irq));
	पूर्णांकc_irqpin_irq_disable(d);
पूर्ण

#घोषणा INTC_IRQ_SENSE_VALID 0x10
#घोषणा INTC_IRQ_SENSE(x) (x + INTC_IRQ_SENSE_VALID)

अटल अचिन्हित अक्षर पूर्णांकc_irqpin_sense[IRQ_TYPE_SENSE_MASK + 1] = अणु
	[IRQ_TYPE_EDGE_FALLING] = INTC_IRQ_SENSE(0x00),
	[IRQ_TYPE_EDGE_RISING] = INTC_IRQ_SENSE(0x01),
	[IRQ_TYPE_LEVEL_LOW] = INTC_IRQ_SENSE(0x02),
	[IRQ_TYPE_LEVEL_HIGH] = INTC_IRQ_SENSE(0x03),
	[IRQ_TYPE_EDGE_BOTH] = INTC_IRQ_SENSE(0x04),
पूर्ण;

अटल पूर्णांक पूर्णांकc_irqpin_irq_set_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक type)
अणु
	अचिन्हित अक्षर value = पूर्णांकc_irqpin_sense[type & IRQ_TYPE_SENSE_MASK];
	काष्ठा पूर्णांकc_irqpin_priv *p = irq_data_get_irq_chip_data(d);

	अगर (!(value & INTC_IRQ_SENSE_VALID))
		वापस -EINVAL;

	वापस पूर्णांकc_irqpin_set_sense(p, irqd_to_hwirq(d),
				     value ^ INTC_IRQ_SENSE_VALID);
पूर्ण

अटल पूर्णांक पूर्णांकc_irqpin_irq_set_wake(काष्ठा irq_data *d, अचिन्हित पूर्णांक on)
अणु
	काष्ठा पूर्णांकc_irqpin_priv *p = irq_data_get_irq_chip_data(d);
	पूर्णांक hw_irq = irqd_to_hwirq(d);

	irq_set_irq_wake(p->irq[hw_irq].requested_irq, on);
	अगर (on)
		atomic_inc(&p->wakeup_path);
	अन्यथा
		atomic_dec(&p->wakeup_path);

	वापस 0;
पूर्ण

अटल irqवापस_t पूर्णांकc_irqpin_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा पूर्णांकc_irqpin_irq *i = dev_id;
	काष्ठा पूर्णांकc_irqpin_priv *p = i->p;
	अचिन्हित दीर्घ bit;

	पूर्णांकc_irqpin_dbg(i, "demux1");
	bit = पूर्णांकc_irqpin_hwirq_mask(p, INTC_IRQPIN_REG_SOURCE, i->hw_irq);

	अगर (पूर्णांकc_irqpin_पढ़ो(p, INTC_IRQPIN_REG_SOURCE) & bit) अणु
		पूर्णांकc_irqpin_ग_लिखो(p, INTC_IRQPIN_REG_SOURCE, ~bit);
		पूर्णांकc_irqpin_dbg(i, "demux2");
		generic_handle_irq(i->करोमुख्य_irq);
		वापस IRQ_HANDLED;
	पूर्ण
	वापस IRQ_NONE;
पूर्ण

अटल irqवापस_t पूर्णांकc_irqpin_shared_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा पूर्णांकc_irqpin_priv *p = dev_id;
	अचिन्हित पूर्णांक reg_source = पूर्णांकc_irqpin_पढ़ो(p, INTC_IRQPIN_REG_SOURCE);
	irqवापस_t status = IRQ_NONE;
	पूर्णांक k;

	क्रम (k = 0; k < 8; k++) अणु
		अगर (reg_source & BIT(7 - k)) अणु
			अगर (BIT(k) & p->shared_irq_mask)
				जारी;

			status |= पूर्णांकc_irqpin_irq_handler(irq, &p->irq[k]);
		पूर्ण
	पूर्ण

	वापस status;
पूर्ण

/*
 * This lock class tells lockdep that INTC External IRQ Pin irqs are in a
 * dअगरferent category than their parents, so it won't report false recursion.
 */
अटल काष्ठा lock_class_key पूर्णांकc_irqpin_irq_lock_class;

/* And this is क्रम the request mutex */
अटल काष्ठा lock_class_key पूर्णांकc_irqpin_irq_request_class;

अटल पूर्णांक पूर्णांकc_irqpin_irq_करोमुख्य_map(काष्ठा irq_करोमुख्य *h, अचिन्हित पूर्णांक virq,
				      irq_hw_number_t hw)
अणु
	काष्ठा पूर्णांकc_irqpin_priv *p = h->host_data;

	p->irq[hw].करोमुख्य_irq = virq;
	p->irq[hw].hw_irq = hw;

	पूर्णांकc_irqpin_dbg(&p->irq[hw], "map");
	irq_set_chip_data(virq, h->host_data);
	irq_set_lockdep_class(virq, &पूर्णांकc_irqpin_irq_lock_class,
			      &पूर्णांकc_irqpin_irq_request_class);
	irq_set_chip_and_handler(virq, &p->irq_chip, handle_level_irq);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops पूर्णांकc_irqpin_irq_करोमुख्य_ops = अणु
	.map	= पूर्णांकc_irqpin_irq_करोमुख्य_map,
	.xlate  = irq_करोमुख्य_xlate_twocell,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकc_irqpin_config पूर्णांकc_irqpin_irlm_r8a777x = अणु
	.irlm_bit = 23, /* ICR0.IRLM0 */
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकc_irqpin_config पूर्णांकc_irqpin_rmobile = अणु
	.irlm_bit = -1,
पूर्ण;

अटल स्थिर काष्ठा of_device_id पूर्णांकc_irqpin_dt_ids[] = अणु
	अणु .compatible = "renesas,intc-irqpin", पूर्ण,
	अणु .compatible = "renesas,intc-irqpin-r8a7778",
	  .data = &पूर्णांकc_irqpin_irlm_r8a777x पूर्ण,
	अणु .compatible = "renesas,intc-irqpin-r8a7779",
	  .data = &पूर्णांकc_irqpin_irlm_r8a777x पूर्ण,
	अणु .compatible = "renesas,intc-irqpin-r8a7740",
	  .data = &पूर्णांकc_irqpin_rmobile पूर्ण,
	अणु .compatible = "renesas,intc-irqpin-sh73a0",
	  .data = &पूर्णांकc_irqpin_rmobile पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, पूर्णांकc_irqpin_dt_ids);

अटल पूर्णांक पूर्णांकc_irqpin_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा पूर्णांकc_irqpin_config *config;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा पूर्णांकc_irqpin_priv *p;
	काष्ठा पूर्णांकc_irqpin_iomem *i;
	काष्ठा resource *io[INTC_IRQPIN_REG_NR];
	काष्ठा resource *irq;
	काष्ठा irq_chip *irq_chip;
	व्योम (*enable_fn)(काष्ठा irq_data *d);
	व्योम (*disable_fn)(काष्ठा irq_data *d);
	स्थिर अक्षर *name = dev_name(dev);
	bool control_parent;
	अचिन्हित पूर्णांक nirqs;
	पूर्णांक ref_irq;
	पूर्णांक ret;
	पूर्णांक k;

	p = devm_kzalloc(dev, माप(*p), GFP_KERNEL);
	अगर (!p)
		वापस -ENOMEM;

	/* deal with driver instance configuration */
	of_property_पढ़ो_u32(dev->of_node, "sense-bitfield-width",
			     &p->sense_bitfield_width);
	control_parent = of_property_पढ़ो_bool(dev->of_node, "control-parent");
	अगर (!p->sense_bitfield_width)
		p->sense_bitfield_width = 4; /* शेष to 4 bits */

	p->pdev = pdev;
	platक्रमm_set_drvdata(pdev, p);

	config = of_device_get_match_data(dev);

	pm_runसमय_enable(dev);
	pm_runसमय_get_sync(dev);

	/* get hold of रेजिस्टर banks */
	स_रखो(io, 0, माप(io));
	क्रम (k = 0; k < INTC_IRQPIN_REG_NR; k++) अणु
		io[k] = platक्रमm_get_resource(pdev, IORESOURCE_MEM, k);
		अगर (!io[k] && k < INTC_IRQPIN_REG_NR_MANDATORY) अणु
			dev_err(dev, "not enough IOMEM resources\n");
			ret = -EINVAL;
			जाओ err0;
		पूर्ण
	पूर्ण

	/* allow any number of IRQs between 1 and INTC_IRQPIN_MAX */
	क्रम (k = 0; k < INTC_IRQPIN_MAX; k++) अणु
		irq = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, k);
		अगर (!irq)
			अवरोध;

		p->irq[k].p = p;
		p->irq[k].requested_irq = irq->start;
	पूर्ण

	nirqs = k;
	अगर (nirqs < 1) अणु
		dev_err(dev, "not enough IRQ resources\n");
		ret = -EINVAL;
		जाओ err0;
	पूर्ण

	/* ioremap IOMEM and setup पढ़ो/ग_लिखो callbacks */
	क्रम (k = 0; k < INTC_IRQPIN_REG_NR; k++) अणु
		i = &p->iomem[k];

		/* handle optional रेजिस्टरs */
		अगर (!io[k])
			जारी;

		चयन (resource_size(io[k])) अणु
		हाल 1:
			i->width = 8;
			i->पढ़ो = पूर्णांकc_irqpin_पढ़ो8;
			i->ग_लिखो = पूर्णांकc_irqpin_ग_लिखो8;
			अवरोध;
		हाल 4:
			i->width = 32;
			i->पढ़ो = पूर्णांकc_irqpin_पढ़ो32;
			i->ग_लिखो = पूर्णांकc_irqpin_ग_लिखो32;
			अवरोध;
		शेष:
			dev_err(dev, "IOMEM size mismatch\n");
			ret = -EINVAL;
			जाओ err0;
		पूर्ण

		i->iomem = devm_ioremap(dev, io[k]->start,
					resource_size(io[k]));
		अगर (!i->iomem) अणु
			dev_err(dev, "failed to remap IOMEM\n");
			ret = -ENXIO;
			जाओ err0;
		पूर्ण
	पूर्ण

	/* configure "individual IRQ mode" where needed */
	अगर (config && config->irlm_bit >= 0) अणु
		अगर (io[INTC_IRQPIN_REG_IRLM])
			पूर्णांकc_irqpin_पढ़ो_modअगरy_ग_लिखो(p, INTC_IRQPIN_REG_IRLM,
						      config->irlm_bit, 1, 1);
		अन्यथा
			dev_warn(dev, "unable to select IRLM mode\n");
	पूर्ण

	/* mask all पूर्णांकerrupts using priority */
	क्रम (k = 0; k < nirqs; k++)
		पूर्णांकc_irqpin_mask_unmask_prio(p, k, 1);

	/* clear all pending पूर्णांकerrupts */
	पूर्णांकc_irqpin_ग_लिखो(p, INTC_IRQPIN_REG_SOURCE, 0x0);

	/* scan क्रम shared पूर्णांकerrupt lines */
	ref_irq = p->irq[0].requested_irq;
	p->shared_irqs = 1;
	क्रम (k = 1; k < nirqs; k++) अणु
		अगर (ref_irq != p->irq[k].requested_irq) अणु
			p->shared_irqs = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	/* use more severe masking method अगर requested */
	अगर (control_parent) अणु
		enable_fn = पूर्णांकc_irqpin_irq_enable_क्रमce;
		disable_fn = पूर्णांकc_irqpin_irq_disable_क्रमce;
	पूर्ण अन्यथा अगर (!p->shared_irqs) अणु
		enable_fn = पूर्णांकc_irqpin_irq_enable;
		disable_fn = पूर्णांकc_irqpin_irq_disable;
	पूर्ण अन्यथा अणु
		enable_fn = पूर्णांकc_irqpin_shared_irq_enable;
		disable_fn = पूर्णांकc_irqpin_shared_irq_disable;
	पूर्ण

	irq_chip = &p->irq_chip;
	irq_chip->name = "intc-irqpin";
	irq_chip->parent_device = dev;
	irq_chip->irq_mask = disable_fn;
	irq_chip->irq_unmask = enable_fn;
	irq_chip->irq_set_type = पूर्णांकc_irqpin_irq_set_type;
	irq_chip->irq_set_wake = पूर्णांकc_irqpin_irq_set_wake;
	irq_chip->flags	= IRQCHIP_MASK_ON_SUSPEND;

	p->irq_करोमुख्य = irq_करोमुख्य_add_simple(dev->of_node, nirqs, 0,
					      &पूर्णांकc_irqpin_irq_करोमुख्य_ops, p);
	अगर (!p->irq_करोमुख्य) अणु
		ret = -ENXIO;
		dev_err(dev, "cannot initialize irq domain\n");
		जाओ err0;
	पूर्ण

	अगर (p->shared_irqs) अणु
		/* request one shared पूर्णांकerrupt */
		अगर (devm_request_irq(dev, p->irq[0].requested_irq,
				पूर्णांकc_irqpin_shared_irq_handler,
				IRQF_SHARED, name, p)) अणु
			dev_err(dev, "failed to request low IRQ\n");
			ret = -ENOENT;
			जाओ err1;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* request पूर्णांकerrupts one by one */
		क्रम (k = 0; k < nirqs; k++) अणु
			अगर (devm_request_irq(dev, p->irq[k].requested_irq,
					     पूर्णांकc_irqpin_irq_handler, 0, name,
					     &p->irq[k])) अणु
				dev_err(dev, "failed to request low IRQ\n");
				ret = -ENOENT;
				जाओ err1;
			पूर्ण
		पूर्ण
	पूर्ण

	/* unmask all पूर्णांकerrupts on prio level */
	क्रम (k = 0; k < nirqs; k++)
		पूर्णांकc_irqpin_mask_unmask_prio(p, k, 0);

	dev_info(dev, "driving %d irqs\n", nirqs);

	वापस 0;

err1:
	irq_करोमुख्य_हटाओ(p->irq_करोमुख्य);
err0:
	pm_runसमय_put(dev);
	pm_runसमय_disable(dev);
	वापस ret;
पूर्ण

अटल पूर्णांक पूर्णांकc_irqpin_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा पूर्णांकc_irqpin_priv *p = platक्रमm_get_drvdata(pdev);

	irq_करोमुख्य_हटाओ(p->irq_करोमुख्य);
	pm_runसमय_put(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused पूर्णांकc_irqpin_suspend(काष्ठा device *dev)
अणु
	काष्ठा पूर्णांकc_irqpin_priv *p = dev_get_drvdata(dev);

	अगर (atomic_पढ़ो(&p->wakeup_path))
		device_set_wakeup_path(dev);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(पूर्णांकc_irqpin_pm_ops, पूर्णांकc_irqpin_suspend, शून्य);

अटल काष्ठा platक्रमm_driver पूर्णांकc_irqpin_device_driver = अणु
	.probe		= पूर्णांकc_irqpin_probe,
	.हटाओ		= पूर्णांकc_irqpin_हटाओ,
	.driver		= अणु
		.name	= "renesas_intc_irqpin",
		.of_match_table = पूर्णांकc_irqpin_dt_ids,
		.pm	= &पूर्णांकc_irqpin_pm_ops,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init पूर्णांकc_irqpin_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&पूर्णांकc_irqpin_device_driver);
पूर्ण
postcore_initcall(पूर्णांकc_irqpin_init);

अटल व्योम __निकास पूर्णांकc_irqpin_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&पूर्णांकc_irqpin_device_driver);
पूर्ण
module_निकास(पूर्णांकc_irqpin_निकास);

MODULE_AUTHOR("Magnus Damm");
MODULE_DESCRIPTION("Renesas INTC External IRQ Pin Driver");
MODULE_LICENSE("GPL v2");
