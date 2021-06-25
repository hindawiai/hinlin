<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2020, Broadcom */

#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/device.h>
#समावेश <linux/of.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kdebug.h>
#समावेश <linux/gpio/consumer.h>

काष्ठा out_pin अणु
	u32 enable_mask;
	u32 value_mask;
	u32 changed_mask;
	u32 clr_changed_mask;
	काष्ठा gpio_desc *gpiod;
	स्थिर अक्षर *name;
पूर्ण;

काष्ठा in_pin अणु
	u32 enable_mask;
	u32 value_mask;
	काष्ठा gpio_desc *gpiod;
	स्थिर अक्षर *name;
	काष्ठा brcmstb_usb_pinmap_data *pdata;
पूर्ण;

काष्ठा brcmstb_usb_pinmap_data अणु
	व्योम __iomem *regs;
	पूर्णांक in_count;
	काष्ठा in_pin *in_pins;
	पूर्णांक out_count;
	काष्ठा out_pin *out_pins;
पूर्ण;


अटल व्योम pinmap_set(व्योम __iomem *reg, u32 mask)
अणु
	u32 val;

	val = पढ़ोl(reg);
	val |= mask;
	ग_लिखोl(val, reg);
पूर्ण

अटल व्योम pinmap_unset(व्योम __iomem *reg, u32 mask)
अणु
	u32 val;

	val = पढ़ोl(reg);
	val &= ~mask;
	ग_लिखोl(val, reg);
पूर्ण

अटल व्योम sync_in_pin(काष्ठा in_pin *pin)
अणु
	u32 val;

	val = gpiod_get_value(pin->gpiod);
	अगर (val)
		pinmap_set(pin->pdata->regs, pin->value_mask);
	अन्यथा
		pinmap_unset(pin->pdata->regs, pin->value_mask);
पूर्ण

/*
 * Interrupt from override रेजिस्टर, propagate from override bit
 * to GPIO.
 */
अटल irqवापस_t brcmstb_usb_pinmap_ovr_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा brcmstb_usb_pinmap_data *pdata = dev_id;
	काष्ठा out_pin *pout;
	u32 val;
	u32 bit;
	पूर्णांक x;

	pr_debug("%s: reg: 0x%x\n", __func__, पढ़ोl(pdata->regs));
	pout = pdata->out_pins;
	क्रम (x = 0; x < pdata->out_count; x++) अणु
		val = पढ़ोl(pdata->regs);
		अगर (val & pout->changed_mask) अणु
			pinmap_set(pdata->regs, pout->clr_changed_mask);
			pinmap_unset(pdata->regs, pout->clr_changed_mask);
			bit = val & pout->value_mask;
			gpiod_set_value(pout->gpiod, bit ? 1 : 0);
			pr_debug("%s: %s bit changed state to %d\n",
				 __func__, pout->name, bit ? 1 : 0);
		पूर्ण
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

/*
 * Interrupt from GPIO, propagate from GPIO to override bit.
 */
अटल irqवापस_t brcmstb_usb_pinmap_gpio_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा in_pin *pin = dev_id;

	pr_debug("%s: %s pin changed state\n", __func__, pin->name);
	sync_in_pin(pin);
	वापस IRQ_HANDLED;
पूर्ण


अटल व्योम get_pin_counts(काष्ठा device_node *dn, पूर्णांक *in_count,
			   पूर्णांक *out_count)
अणु
	पूर्णांक in;
	पूर्णांक out;

	*in_count = 0;
	*out_count = 0;
	in = of_property_count_strings(dn, "brcm,in-functions");
	अगर (in < 0)
		वापस;
	out = of_property_count_strings(dn, "brcm,out-functions");
	अगर (out < 0)
		वापस;
	*in_count = in;
	*out_count = out;
पूर्ण

अटल पूर्णांक parse_pins(काष्ठा device *dev, काष्ठा device_node *dn,
		      काष्ठा brcmstb_usb_pinmap_data *pdata)
अणु
	काष्ठा out_pin *pout;
	काष्ठा in_pin *pin;
	पूर्णांक index;
	पूर्णांक res;
	पूर्णांक x;

	pin = pdata->in_pins;
	क्रम (x = 0, index = 0; x < pdata->in_count; x++) अणु
		pin->gpiod = devm_gpiod_get_index(dev, "in", x, GPIOD_IN);
		अगर (IS_ERR(pin->gpiod)) अणु
			dev_err(dev, "Error getting gpio %s\n", pin->name);
			वापस PTR_ERR(pin->gpiod);

		पूर्ण
		res = of_property_पढ़ो_string_index(dn, "brcm,in-functions", x,
						    &pin->name);
		अगर (res < 0) अणु
			dev_err(dev, "Error getting brcm,in-functions for %s\n",
				pin->name);
			वापस res;
		पूर्ण
		res = of_property_पढ़ो_u32_index(dn, "brcm,in-masks", index++,
						 &pin->enable_mask);
		अगर (res < 0) अणु
			dev_err(dev, "Error getting 1st brcm,in-masks for %s\n",
				pin->name);
			वापस res;
		पूर्ण
		res = of_property_पढ़ो_u32_index(dn, "brcm,in-masks", index++,
						 &pin->value_mask);
		अगर (res < 0) अणु
			dev_err(dev, "Error getting 2nd brcm,in-masks for %s\n",
				pin->name);
			वापस res;
		पूर्ण
		pin->pdata = pdata;
		pin++;
	पूर्ण
	pout = pdata->out_pins;
	क्रम (x = 0, index = 0; x < pdata->out_count; x++) अणु
		pout->gpiod = devm_gpiod_get_index(dev, "out", x,
						   GPIOD_OUT_HIGH);
		अगर (IS_ERR(pout->gpiod)) अणु
			dev_err(dev, "Error getting gpio %s\n", pin->name);
			वापस PTR_ERR(pout->gpiod);
		पूर्ण
		res = of_property_पढ़ो_string_index(dn, "brcm,out-functions", x,
						    &pout->name);
		अगर (res < 0) अणु
			dev_err(dev, "Error getting brcm,out-functions for %s\n",
				pout->name);
			वापस res;
		पूर्ण
		res = of_property_पढ़ो_u32_index(dn, "brcm,out-masks", index++,
						 &pout->enable_mask);
		अगर (res < 0) अणु
			dev_err(dev, "Error getting 1st brcm,out-masks for %s\n",
				pout->name);
			वापस res;
		पूर्ण
		res = of_property_पढ़ो_u32_index(dn, "brcm,out-masks", index++,
						 &pout->value_mask);
		अगर (res < 0) अणु
			dev_err(dev, "Error getting 2nd brcm,out-masks for %s\n",
				pout->name);
			वापस res;
		पूर्ण
		res = of_property_पढ़ो_u32_index(dn, "brcm,out-masks", index++,
						 &pout->changed_mask);
		अगर (res < 0) अणु
			dev_err(dev, "Error getting 3rd brcm,out-masks for %s\n",
				pout->name);
			वापस res;
		पूर्ण
		res = of_property_पढ़ो_u32_index(dn, "brcm,out-masks", index++,
						 &pout->clr_changed_mask);
		अगर (res < 0) अणु
			dev_err(dev, "Error getting 4th out-masks for %s\n",
				pout->name);
			वापस res;
		पूर्ण
		pout++;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम sync_all_pins(काष्ठा brcmstb_usb_pinmap_data *pdata)
अणु
	काष्ठा out_pin *pout;
	काष्ठा in_pin *pin;
	पूर्णांक val;
	पूर्णांक x;

	/*
	 * Enable the override, clear any changed condition and
	 * propagate the state to the GPIO क्रम all out pins.
	 */
	pout = pdata->out_pins;
	क्रम (x = 0; x < pdata->out_count; x++) अणु
		pinmap_set(pdata->regs, pout->enable_mask);
		pinmap_set(pdata->regs, pout->clr_changed_mask);
		pinmap_unset(pdata->regs, pout->clr_changed_mask);
		val = पढ़ोl(pdata->regs) & pout->value_mask;
		gpiod_set_value(pout->gpiod, val ? 1 : 0);
		pout++;
	पूर्ण

	/* sync and enable all in pins. */
	pin = pdata->in_pins;
	क्रम (x = 0; x < pdata->in_count; x++) अणु
		sync_in_pin(pin);
		pinmap_set(pdata->regs, pin->enable_mask);
		pin++;
	पूर्ण
पूर्ण

अटल पूर्णांक __init brcmstb_usb_pinmap_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *dn = pdev->dev.of_node;
	काष्ठा brcmstb_usb_pinmap_data *pdata;
	काष्ठा in_pin *pin;
	काष्ठा resource *r;
	पूर्णांक out_count;
	पूर्णांक in_count;
	पूर्णांक err;
	पूर्णांक irq;
	पूर्णांक x;

	get_pin_counts(dn, &in_count, &out_count);
	अगर ((in_count + out_count) == 0)
		वापस -EINVAL;

	r = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!r)
		वापस -EINVAL;

	pdata = devm_kzalloc(&pdev->dev,
			     माप(*pdata) +
			     (माप(काष्ठा in_pin) * in_count) +
			     (माप(काष्ठा out_pin) * out_count), GFP_KERNEL);
	अगर (!pdata)
		वापस -ENOMEM;

	pdata->in_count = in_count;
	pdata->out_count = out_count;
	pdata->in_pins = (काष्ठा in_pin *)(pdata + 1);
	pdata->out_pins = (काष्ठा out_pin *)(pdata->in_pins + in_count);

	pdata->regs = devm_ioremap(&pdev->dev, r->start, resource_size(r));
	अगर (!pdata->regs)
		वापस -ENOMEM;
	platक्रमm_set_drvdata(pdev, pdata);

	err = parse_pins(&pdev->dev, dn, pdata);
	अगर (err)
		वापस err;

	sync_all_pins(pdata);

	अगर (out_count) अणु

		/* Enable पूर्णांकerrupt क्रम out pins */
		irq = platक्रमm_get_irq(pdev, 0);
		err = devm_request_irq(&pdev->dev, irq,
				       brcmstb_usb_pinmap_ovr_isr,
				       IRQF_TRIGGER_RISING,
				       pdev->name, pdata);
		अगर (err < 0) अणु
			dev_err(&pdev->dev, "Error requesting IRQ\n");
			वापस err;
		पूर्ण
	पूर्ण

	क्रम (x = 0, pin = pdata->in_pins; x < pdata->in_count; x++, pin++) अणु
		irq = gpiod_to_irq(pin->gpiod);
		अगर (irq < 0) अणु
			dev_err(&pdev->dev, "Error getting IRQ for %s pin\n",
				pin->name);
			वापस irq;
		पूर्ण
		err = devm_request_irq(&pdev->dev, irq,
				       brcmstb_usb_pinmap_gpio_isr,
				       IRQF_SHARED | IRQF_TRIGGER_RISING |
				       IRQF_TRIGGER_FALLING,
				       pdev->name, pin);
		अगर (err < 0) अणु
			dev_err(&pdev->dev, "Error requesting IRQ for %s pin\n",
				pin->name);
			वापस err;
		पूर्ण
	पूर्ण

	dev_dbg(&pdev->dev, "Driver probe succeeded\n");
	dev_dbg(&pdev->dev, "In pin count: %d, out pin count: %d\n",
		pdata->in_count, pdata->out_count);
	वापस 0;
पूर्ण


अटल स्थिर काष्ठा of_device_id brcmstb_usb_pinmap_of_match[] = अणु
	अणु .compatible = "brcm,usb-pinmap" पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver brcmstb_usb_pinmap_driver = अणु
	.driver = अणु
		.name	= "brcm-usb-pinmap",
		.of_match_table = brcmstb_usb_pinmap_of_match,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init brcmstb_usb_pinmap_init(व्योम)
अणु
	वापस platक्रमm_driver_probe(&brcmstb_usb_pinmap_driver,
				     brcmstb_usb_pinmap_probe);
पूर्ण

module_init(brcmstb_usb_pinmap_init);
MODULE_AUTHOR("Al Cooper <alcooperx@gmail.com>");
MODULE_DESCRIPTION("Broadcom USB Pinmap Driver");
MODULE_LICENSE("GPL");
