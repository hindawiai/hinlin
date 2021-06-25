<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2017-2019, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/soc/qcom/irq.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>

#घोषणा PDC_MAX_IRQS		168
#घोषणा PDC_MAX_GPIO_IRQS	256

#घोषणा CLEAR_INTR(reg, पूर्णांकr)	(reg & ~(1 << पूर्णांकr))
#घोषणा ENABLE_INTR(reg, पूर्णांकr)	(reg | (1 << पूर्णांकr))

#घोषणा IRQ_ENABLE_BANK		0x10
#घोषणा IRQ_i_CFG		0x110

#घोषणा PDC_NO_PARENT_IRQ	~0UL

काष्ठा pdc_pin_region अणु
	u32 pin_base;
	u32 parent_base;
	u32 cnt;
पूर्ण;

अटल DEFINE_RAW_SPINLOCK(pdc_lock);
अटल व्योम __iomem *pdc_base;
अटल काष्ठा pdc_pin_region *pdc_region;
अटल पूर्णांक pdc_region_cnt;

अटल व्योम pdc_reg_ग_लिखो(पूर्णांक reg, u32 i, u32 val)
अणु
	ग_लिखोl_relaxed(val, pdc_base + reg + i * माप(u32));
पूर्ण

अटल u32 pdc_reg_पढ़ो(पूर्णांक reg, u32 i)
अणु
	वापस पढ़ोl_relaxed(pdc_base + reg + i * माप(u32));
पूर्ण

अटल पूर्णांक qcom_pdc_gic_get_irqchip_state(काष्ठा irq_data *d,
					  क्रमागत irqchip_irq_state which,
					  bool *state)
अणु
	अगर (d->hwirq == GPIO_NO_WAKE_IRQ)
		वापस 0;

	वापस irq_chip_get_parent_state(d, which, state);
पूर्ण

अटल पूर्णांक qcom_pdc_gic_set_irqchip_state(काष्ठा irq_data *d,
					  क्रमागत irqchip_irq_state which,
					  bool value)
अणु
	अगर (d->hwirq == GPIO_NO_WAKE_IRQ)
		वापस 0;

	वापस irq_chip_set_parent_state(d, which, value);
पूर्ण

अटल व्योम pdc_enable_पूर्णांकr(काष्ठा irq_data *d, bool on)
अणु
	पूर्णांक pin_out = d->hwirq;
	u32 index, mask;
	u32 enable;

	index = pin_out / 32;
	mask = pin_out % 32;

	raw_spin_lock(&pdc_lock);
	enable = pdc_reg_पढ़ो(IRQ_ENABLE_BANK, index);
	enable = on ? ENABLE_INTR(enable, mask) : CLEAR_INTR(enable, mask);
	pdc_reg_ग_लिखो(IRQ_ENABLE_BANK, index, enable);
	raw_spin_unlock(&pdc_lock);
पूर्ण

अटल व्योम qcom_pdc_gic_disable(काष्ठा irq_data *d)
अणु
	अगर (d->hwirq == GPIO_NO_WAKE_IRQ)
		वापस;

	pdc_enable_पूर्णांकr(d, false);
	irq_chip_disable_parent(d);
पूर्ण

अटल व्योम qcom_pdc_gic_enable(काष्ठा irq_data *d)
अणु
	अगर (d->hwirq == GPIO_NO_WAKE_IRQ)
		वापस;

	pdc_enable_पूर्णांकr(d, true);
	irq_chip_enable_parent(d);
पूर्ण

अटल व्योम qcom_pdc_gic_mask(काष्ठा irq_data *d)
अणु
	अगर (d->hwirq == GPIO_NO_WAKE_IRQ)
		वापस;

	irq_chip_mask_parent(d);
पूर्ण

अटल व्योम qcom_pdc_gic_unmask(काष्ठा irq_data *d)
अणु
	अगर (d->hwirq == GPIO_NO_WAKE_IRQ)
		वापस;

	irq_chip_unmask_parent(d);
पूर्ण

/*
 * GIC करोes not handle falling edge or active low. To allow falling edge and
 * active low पूर्णांकerrupts to be handled at GIC, PDC has an inverter that inverts
 * falling edge पूर्णांकo a rising edge and active low पूर्णांकo an active high.
 * For the inverter to work, the polarity bit in the IRQ_CONFIG रेजिस्टर has to
 * set as per the table below.
 * Level sensitive active low    LOW
 * Rising edge sensitive         NOT USED
 * Falling edge sensitive        LOW
 * Dual Edge sensitive           NOT USED
 * Level sensitive active High   HIGH
 * Falling Edge sensitive        NOT USED
 * Rising edge sensitive         HIGH
 * Dual Edge sensitive           HIGH
 */
क्रमागत pdc_irq_config_bits अणु
	PDC_LEVEL_LOW		= 0b000,
	PDC_EDGE_FALLING	= 0b010,
	PDC_LEVEL_HIGH		= 0b100,
	PDC_EDGE_RISING		= 0b110,
	PDC_EDGE_DUAL		= 0b111,
पूर्ण;

/**
 * qcom_pdc_gic_set_type: Configure PDC क्रम the पूर्णांकerrupt
 *
 * @d: the पूर्णांकerrupt data
 * @type: the पूर्णांकerrupt type
 *
 * If @type is edge triggered, क्रमward that as Rising edge as PDC
 * takes care of converting falling edge to rising edge संकेत
 * If @type is level, then क्रमward that as level high as PDC
 * takes care of converting falling edge to rising edge संकेत
 */
अटल पूर्णांक qcom_pdc_gic_set_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक type)
अणु
	पूर्णांक pin_out = d->hwirq;
	क्रमागत pdc_irq_config_bits pdc_type;
	क्रमागत pdc_irq_config_bits old_pdc_type;
	पूर्णांक ret;

	अगर (pin_out == GPIO_NO_WAKE_IRQ)
		वापस 0;

	चयन (type) अणु
	हाल IRQ_TYPE_EDGE_RISING:
		pdc_type = PDC_EDGE_RISING;
		अवरोध;
	हाल IRQ_TYPE_EDGE_FALLING:
		pdc_type = PDC_EDGE_FALLING;
		type = IRQ_TYPE_EDGE_RISING;
		अवरोध;
	हाल IRQ_TYPE_EDGE_BOTH:
		pdc_type = PDC_EDGE_DUAL;
		type = IRQ_TYPE_EDGE_RISING;
		अवरोध;
	हाल IRQ_TYPE_LEVEL_HIGH:
		pdc_type = PDC_LEVEL_HIGH;
		अवरोध;
	हाल IRQ_TYPE_LEVEL_LOW:
		pdc_type = PDC_LEVEL_LOW;
		type = IRQ_TYPE_LEVEL_HIGH;
		अवरोध;
	शेष:
		WARN_ON(1);
		वापस -EINVAL;
	पूर्ण

	old_pdc_type = pdc_reg_पढ़ो(IRQ_i_CFG, pin_out);
	pdc_reg_ग_लिखो(IRQ_i_CFG, pin_out, pdc_type);

	ret = irq_chip_set_type_parent(d, type);
	अगर (ret)
		वापस ret;

	/*
	 * When we change types the PDC can give a phantom पूर्णांकerrupt.
	 * Clear it.  Specअगरically the phantom shows up when reconfiguring
	 * polarity of पूर्णांकerrupt without changing the state of the संकेत
	 * but let's be consistent and clear it always.
	 *
	 * Doing this works because we have IRQCHIP_SET_TYPE_MASKED so the
	 * पूर्णांकerrupt will be cleared beक्रमe the rest of the प्रणाली sees it.
	 */
	अगर (old_pdc_type != pdc_type)
		irq_chip_set_parent_state(d, IRQCHIP_STATE_PENDING, false);

	वापस 0;
पूर्ण

अटल काष्ठा irq_chip qcom_pdc_gic_chip = अणु
	.name			= "PDC",
	.irq_eoi		= irq_chip_eoi_parent,
	.irq_mask		= qcom_pdc_gic_mask,
	.irq_unmask		= qcom_pdc_gic_unmask,
	.irq_disable		= qcom_pdc_gic_disable,
	.irq_enable		= qcom_pdc_gic_enable,
	.irq_get_irqchip_state	= qcom_pdc_gic_get_irqchip_state,
	.irq_set_irqchip_state	= qcom_pdc_gic_set_irqchip_state,
	.irq_retrigger		= irq_chip_retrigger_hierarchy,
	.irq_set_type		= qcom_pdc_gic_set_type,
	.flags			= IRQCHIP_MASK_ON_SUSPEND |
				  IRQCHIP_SET_TYPE_MASKED |
				  IRQCHIP_SKIP_SET_WAKE |
				  IRQCHIP_ENABLE_WAKEUP_ON_SUSPEND,
	.irq_set_vcpu_affinity	= irq_chip_set_vcpu_affinity_parent,
	.irq_set_affinity	= irq_chip_set_affinity_parent,
पूर्ण;

अटल irq_hw_number_t get_parent_hwirq(पूर्णांक pin)
अणु
	पूर्णांक i;
	काष्ठा pdc_pin_region *region;

	क्रम (i = 0; i < pdc_region_cnt; i++) अणु
		region = &pdc_region[i];
		अगर (pin >= region->pin_base &&
		    pin < region->pin_base + region->cnt)
			वापस (region->parent_base + pin - region->pin_base);
	पूर्ण

	वापस PDC_NO_PARENT_IRQ;
पूर्ण

अटल पूर्णांक qcom_pdc_translate(काष्ठा irq_करोमुख्य *d, काष्ठा irq_fwspec *fwspec,
			      अचिन्हित दीर्घ *hwirq, अचिन्हित पूर्णांक *type)
अणु
	अगर (is_of_node(fwspec->fwnode)) अणु
		अगर (fwspec->param_count != 2)
			वापस -EINVAL;

		*hwirq = fwspec->param[0];
		*type = fwspec->param[1] & IRQ_TYPE_SENSE_MASK;
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक qcom_pdc_alloc(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक virq,
			  अचिन्हित पूर्णांक nr_irqs, व्योम *data)
अणु
	काष्ठा irq_fwspec *fwspec = data;
	काष्ठा irq_fwspec parent_fwspec;
	irq_hw_number_t hwirq, parent_hwirq;
	अचिन्हित पूर्णांक type;
	पूर्णांक ret;

	ret = qcom_pdc_translate(करोमुख्य, fwspec, &hwirq, &type);
	अगर (ret)
		वापस ret;

	ret  = irq_करोमुख्य_set_hwirq_and_chip(करोमुख्य, virq, hwirq,
					     &qcom_pdc_gic_chip, शून्य);
	अगर (ret)
		वापस ret;

	parent_hwirq = get_parent_hwirq(hwirq);
	अगर (parent_hwirq == PDC_NO_PARENT_IRQ)
		वापस 0;

	अगर (type & IRQ_TYPE_EDGE_BOTH)
		type = IRQ_TYPE_EDGE_RISING;

	अगर (type & IRQ_TYPE_LEVEL_MASK)
		type = IRQ_TYPE_LEVEL_HIGH;

	parent_fwspec.fwnode      = करोमुख्य->parent->fwnode;
	parent_fwspec.param_count = 3;
	parent_fwspec.param[0]    = 0;
	parent_fwspec.param[1]    = parent_hwirq;
	parent_fwspec.param[2]    = type;

	वापस irq_करोमुख्य_alloc_irqs_parent(करोमुख्य, virq, nr_irqs,
					    &parent_fwspec);
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops qcom_pdc_ops = अणु
	.translate	= qcom_pdc_translate,
	.alloc		= qcom_pdc_alloc,
	.मुक्त		= irq_करोमुख्य_मुक्त_irqs_common,
पूर्ण;

अटल पूर्णांक qcom_pdc_gpio_alloc(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक virq,
			       अचिन्हित पूर्णांक nr_irqs, व्योम *data)
अणु
	काष्ठा irq_fwspec *fwspec = data;
	काष्ठा irq_fwspec parent_fwspec;
	irq_hw_number_t hwirq, parent_hwirq;
	अचिन्हित पूर्णांक type;
	पूर्णांक ret;

	ret = qcom_pdc_translate(करोमुख्य, fwspec, &hwirq, &type);
	अगर (ret)
		वापस ret;

	ret = irq_करोमुख्य_set_hwirq_and_chip(करोमुख्य, virq, hwirq,
					    &qcom_pdc_gic_chip, शून्य);
	अगर (ret)
		वापस ret;

	अगर (hwirq == GPIO_NO_WAKE_IRQ)
		वापस 0;

	parent_hwirq = get_parent_hwirq(hwirq);
	अगर (parent_hwirq == PDC_NO_PARENT_IRQ)
		वापस 0;

	अगर (type & IRQ_TYPE_EDGE_BOTH)
		type = IRQ_TYPE_EDGE_RISING;

	अगर (type & IRQ_TYPE_LEVEL_MASK)
		type = IRQ_TYPE_LEVEL_HIGH;

	parent_fwspec.fwnode      = करोमुख्य->parent->fwnode;
	parent_fwspec.param_count = 3;
	parent_fwspec.param[0]    = 0;
	parent_fwspec.param[1]    = parent_hwirq;
	parent_fwspec.param[2]    = type;

	वापस irq_करोमुख्य_alloc_irqs_parent(करोमुख्य, virq, nr_irqs,
					    &parent_fwspec);
पूर्ण

अटल पूर्णांक qcom_pdc_gpio_करोमुख्य_select(काष्ठा irq_करोमुख्य *d,
				       काष्ठा irq_fwspec *fwspec,
				       क्रमागत irq_करोमुख्य_bus_token bus_token)
अणु
	वापस bus_token == DOMAIN_BUS_WAKEUP;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops qcom_pdc_gpio_ops = अणु
	.select		= qcom_pdc_gpio_करोमुख्य_select,
	.alloc		= qcom_pdc_gpio_alloc,
	.मुक्त		= irq_करोमुख्य_मुक्त_irqs_common,
पूर्ण;

अटल पूर्णांक pdc_setup_pin_mapping(काष्ठा device_node *np)
अणु
	पूर्णांक ret, n, i;
	u32 irq_index, reg_index, val;

	n = of_property_count_elems_of_size(np, "qcom,pdc-ranges", माप(u32));
	अगर (n <= 0 || n % 3)
		वापस -EINVAL;

	pdc_region_cnt = n / 3;
	pdc_region = kसुस्मृति(pdc_region_cnt, माप(*pdc_region), GFP_KERNEL);
	अगर (!pdc_region) अणु
		pdc_region_cnt = 0;
		वापस -ENOMEM;
	पूर्ण

	क्रम (n = 0; n < pdc_region_cnt; n++) अणु
		ret = of_property_पढ़ो_u32_index(np, "qcom,pdc-ranges",
						 n * 3 + 0,
						 &pdc_region[n].pin_base);
		अगर (ret)
			वापस ret;
		ret = of_property_पढ़ो_u32_index(np, "qcom,pdc-ranges",
						 n * 3 + 1,
						 &pdc_region[n].parent_base);
		अगर (ret)
			वापस ret;
		ret = of_property_पढ़ो_u32_index(np, "qcom,pdc-ranges",
						 n * 3 + 2,
						 &pdc_region[n].cnt);
		अगर (ret)
			वापस ret;

		क्रम (i = 0; i < pdc_region[n].cnt; i++) अणु
			reg_index = (i + pdc_region[n].pin_base) >> 5;
			irq_index = (i + pdc_region[n].pin_base) & 0x1f;
			val = pdc_reg_पढ़ो(IRQ_ENABLE_BANK, reg_index);
			val &= ~BIT(irq_index);
			pdc_reg_ग_लिखो(IRQ_ENABLE_BANK, reg_index, val);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qcom_pdc_init(काष्ठा device_node *node, काष्ठा device_node *parent)
अणु
	काष्ठा irq_करोमुख्य *parent_करोमुख्य, *pdc_करोमुख्य, *pdc_gpio_करोमुख्य;
	पूर्णांक ret;

	pdc_base = of_iomap(node, 0);
	अगर (!pdc_base) अणु
		pr_err("%pOF: unable to map PDC registers\n", node);
		वापस -ENXIO;
	पूर्ण

	parent_करोमुख्य = irq_find_host(parent);
	अगर (!parent_करोमुख्य) अणु
		pr_err("%pOF: unable to find PDC's parent domain\n", node);
		ret = -ENXIO;
		जाओ fail;
	पूर्ण

	ret = pdc_setup_pin_mapping(node);
	अगर (ret) अणु
		pr_err("%pOF: failed to init PDC pin-hwirq mapping\n", node);
		जाओ fail;
	पूर्ण

	pdc_करोमुख्य = irq_करोमुख्य_create_hierarchy(parent_करोमुख्य, 0, PDC_MAX_IRQS,
						 of_fwnode_handle(node),
						 &qcom_pdc_ops, शून्य);
	अगर (!pdc_करोमुख्य) अणु
		pr_err("%pOF: GIC domain add failed\n", node);
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण

	pdc_gpio_करोमुख्य = irq_करोमुख्य_create_hierarchy(parent_करोमुख्य,
					IRQ_DOMAIN_FLAG_QCOM_PDC_WAKEUP,
					PDC_MAX_GPIO_IRQS,
					of_fwnode_handle(node),
					&qcom_pdc_gpio_ops, शून्य);
	अगर (!pdc_gpio_करोमुख्य) अणु
		pr_err("%pOF: PDC domain add failed for GPIO domain\n", node);
		ret = -ENOMEM;
		जाओ हटाओ;
	पूर्ण

	irq_करोमुख्य_update_bus_token(pdc_gpio_करोमुख्य, DOMAIN_BUS_WAKEUP);

	वापस 0;

हटाओ:
	irq_करोमुख्य_हटाओ(pdc_करोमुख्य);
fail:
	kमुक्त(pdc_region);
	iounmap(pdc_base);
	वापस ret;
पूर्ण

IRQCHIP_DECLARE(qcom_pdc, "qcom,pdc", qcom_pdc_init);
