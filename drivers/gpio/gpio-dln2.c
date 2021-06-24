<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम the Diolan DLN-2 USB-GPIO adapter
 *
 * Copyright (c) 2014 Intel Corporation
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqchip/chained_irq.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mfd/dln2.h>

#घोषणा DLN2_GPIO_ID			0x01

#घोषणा DLN2_GPIO_GET_PIN_COUNT		DLN2_CMD(0x01, DLN2_GPIO_ID)
#घोषणा DLN2_GPIO_SET_DEBOUNCE		DLN2_CMD(0x04, DLN2_GPIO_ID)
#घोषणा DLN2_GPIO_GET_DEBOUNCE		DLN2_CMD(0x05, DLN2_GPIO_ID)
#घोषणा DLN2_GPIO_PORT_GET_VAL		DLN2_CMD(0x06, DLN2_GPIO_ID)
#घोषणा DLN2_GPIO_PIN_GET_VAL		DLN2_CMD(0x0B, DLN2_GPIO_ID)
#घोषणा DLN2_GPIO_PIN_SET_OUT_VAL	DLN2_CMD(0x0C, DLN2_GPIO_ID)
#घोषणा DLN2_GPIO_PIN_GET_OUT_VAL	DLN2_CMD(0x0D, DLN2_GPIO_ID)
#घोषणा DLN2_GPIO_CONDITION_MET_EV	DLN2_CMD(0x0F, DLN2_GPIO_ID)
#घोषणा DLN2_GPIO_PIN_ENABLE		DLN2_CMD(0x10, DLN2_GPIO_ID)
#घोषणा DLN2_GPIO_PIN_DISABLE		DLN2_CMD(0x11, DLN2_GPIO_ID)
#घोषणा DLN2_GPIO_PIN_SET_सूचीECTION	DLN2_CMD(0x13, DLN2_GPIO_ID)
#घोषणा DLN2_GPIO_PIN_GET_सूचीECTION	DLN2_CMD(0x14, DLN2_GPIO_ID)
#घोषणा DLN2_GPIO_PIN_SET_EVENT_CFG	DLN2_CMD(0x1E, DLN2_GPIO_ID)
#घोषणा DLN2_GPIO_PIN_GET_EVENT_CFG	DLN2_CMD(0x1F, DLN2_GPIO_ID)

#घोषणा DLN2_GPIO_EVENT_NONE		0
#घोषणा DLN2_GPIO_EVENT_CHANGE		1
#घोषणा DLN2_GPIO_EVENT_LVL_HIGH	2
#घोषणा DLN2_GPIO_EVENT_LVL_LOW		3
#घोषणा DLN2_GPIO_EVENT_CHANGE_RISING	0x11
#घोषणा DLN2_GPIO_EVENT_CHANGE_FALLING  0x21
#घोषणा DLN2_GPIO_EVENT_MASK		0x0F

#घोषणा DLN2_GPIO_MAX_PINS 32

काष्ठा dln2_gpio अणु
	काष्ठा platक्रमm_device *pdev;
	काष्ठा gpio_chip gpio;

	/*
	 * Cache pin direction to save us one transfer, since the hardware has
	 * separate commands to पढ़ो the in and out values.
	 */
	DECLARE_BITMAP(output_enabled, DLN2_GPIO_MAX_PINS);

	/* active IRQs - not synced to hardware */
	DECLARE_BITMAP(unmasked_irqs, DLN2_GPIO_MAX_PINS);
	/* active IRQS - synced to hardware */
	DECLARE_BITMAP(enabled_irqs, DLN2_GPIO_MAX_PINS);
	पूर्णांक irq_type[DLN2_GPIO_MAX_PINS];
	काष्ठा mutex irq_lock;
पूर्ण;

काष्ठा dln2_gpio_pin अणु
	__le16 pin;
पूर्ण;

काष्ठा dln2_gpio_pin_val अणु
	__le16 pin __packed;
	u8 value;
पूर्ण;

अटल पूर्णांक dln2_gpio_get_pin_count(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;
	__le16 count;
	पूर्णांक len = माप(count);

	ret = dln2_transfer_rx(pdev, DLN2_GPIO_GET_PIN_COUNT, &count, &len);
	अगर (ret < 0)
		वापस ret;
	अगर (len < माप(count))
		वापस -EPROTO;

	वापस le16_to_cpu(count);
पूर्ण

अटल पूर्णांक dln2_gpio_pin_cmd(काष्ठा dln2_gpio *dln2, पूर्णांक cmd, अचिन्हित pin)
अणु
	काष्ठा dln2_gpio_pin req = अणु
		.pin = cpu_to_le16(pin),
	पूर्ण;

	वापस dln2_transfer_tx(dln2->pdev, cmd, &req, माप(req));
पूर्ण

अटल पूर्णांक dln2_gpio_pin_val(काष्ठा dln2_gpio *dln2, पूर्णांक cmd, अचिन्हित पूर्णांक pin)
अणु
	पूर्णांक ret;
	काष्ठा dln2_gpio_pin req = अणु
		.pin = cpu_to_le16(pin),
	पूर्ण;
	काष्ठा dln2_gpio_pin_val rsp;
	पूर्णांक len = माप(rsp);

	ret = dln2_transfer(dln2->pdev, cmd, &req, माप(req), &rsp, &len);
	अगर (ret < 0)
		वापस ret;
	अगर (len < माप(rsp) || req.pin != rsp.pin)
		वापस -EPROTO;

	वापस rsp.value;
पूर्ण

अटल पूर्णांक dln2_gpio_pin_get_in_val(काष्ठा dln2_gpio *dln2, अचिन्हित पूर्णांक pin)
अणु
	पूर्णांक ret;

	ret = dln2_gpio_pin_val(dln2, DLN2_GPIO_PIN_GET_VAL, pin);
	अगर (ret < 0)
		वापस ret;
	वापस !!ret;
पूर्ण

अटल पूर्णांक dln2_gpio_pin_get_out_val(काष्ठा dln2_gpio *dln2, अचिन्हित पूर्णांक pin)
अणु
	पूर्णांक ret;

	ret = dln2_gpio_pin_val(dln2, DLN2_GPIO_PIN_GET_OUT_VAL, pin);
	अगर (ret < 0)
		वापस ret;
	वापस !!ret;
पूर्ण

अटल पूर्णांक dln2_gpio_pin_set_out_val(काष्ठा dln2_gpio *dln2,
				     अचिन्हित पूर्णांक pin, पूर्णांक value)
अणु
	काष्ठा dln2_gpio_pin_val req = अणु
		.pin = cpu_to_le16(pin),
		.value = value,
	पूर्ण;

	वापस dln2_transfer_tx(dln2->pdev, DLN2_GPIO_PIN_SET_OUT_VAL, &req,
				माप(req));
पूर्ण

#घोषणा DLN2_GPIO_सूचीECTION_IN		0
#घोषणा DLN2_GPIO_सूचीECTION_OUT		1

अटल पूर्णांक dln2_gpio_request(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा dln2_gpio *dln2 = gpiochip_get_data(chip);
	काष्ठा dln2_gpio_pin req = अणु
		.pin = cpu_to_le16(offset),
	पूर्ण;
	काष्ठा dln2_gpio_pin_val rsp;
	पूर्णांक len = माप(rsp);
	पूर्णांक ret;

	ret = dln2_gpio_pin_cmd(dln2, DLN2_GPIO_PIN_ENABLE, offset);
	अगर (ret < 0)
		वापस ret;

	/* cache the pin direction */
	ret = dln2_transfer(dln2->pdev, DLN2_GPIO_PIN_GET_सूचीECTION,
			    &req, माप(req), &rsp, &len);
	अगर (ret < 0)
		वापस ret;
	अगर (len < माप(rsp) || req.pin != rsp.pin) अणु
		ret = -EPROTO;
		जाओ out_disable;
	पूर्ण

	चयन (rsp.value) अणु
	हाल DLN2_GPIO_सूचीECTION_IN:
		clear_bit(offset, dln2->output_enabled);
		वापस 0;
	हाल DLN2_GPIO_सूचीECTION_OUT:
		set_bit(offset, dln2->output_enabled);
		वापस 0;
	शेष:
		ret = -EPROTO;
		जाओ out_disable;
	पूर्ण

out_disable:
	dln2_gpio_pin_cmd(dln2, DLN2_GPIO_PIN_DISABLE, offset);
	वापस ret;
पूर्ण

अटल व्योम dln2_gpio_मुक्त(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा dln2_gpio *dln2 = gpiochip_get_data(chip);

	dln2_gpio_pin_cmd(dln2, DLN2_GPIO_PIN_DISABLE, offset);
पूर्ण

अटल पूर्णांक dln2_gpio_get_direction(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा dln2_gpio *dln2 = gpiochip_get_data(chip);

	अगर (test_bit(offset, dln2->output_enabled))
		वापस GPIO_LINE_सूचीECTION_OUT;

	वापस GPIO_LINE_सूचीECTION_IN;
पूर्ण

अटल पूर्णांक dln2_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा dln2_gpio *dln2 = gpiochip_get_data(chip);
	पूर्णांक dir;

	dir = dln2_gpio_get_direction(chip, offset);
	अगर (dir < 0)
		वापस dir;

	अगर (dir == GPIO_LINE_सूचीECTION_IN)
		वापस dln2_gpio_pin_get_in_val(dln2, offset);

	वापस dln2_gpio_pin_get_out_val(dln2, offset);
पूर्ण

अटल व्योम dln2_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित offset, पूर्णांक value)
अणु
	काष्ठा dln2_gpio *dln2 = gpiochip_get_data(chip);

	dln2_gpio_pin_set_out_val(dln2, offset, value);
पूर्ण

अटल पूर्णांक dln2_gpio_set_direction(काष्ठा gpio_chip *chip, अचिन्हित offset,
				   अचिन्हित dir)
अणु
	काष्ठा dln2_gpio *dln2 = gpiochip_get_data(chip);
	काष्ठा dln2_gpio_pin_val req = अणु
		.pin = cpu_to_le16(offset),
		.value = dir,
	पूर्ण;
	पूर्णांक ret;

	ret = dln2_transfer_tx(dln2->pdev, DLN2_GPIO_PIN_SET_सूचीECTION,
			       &req, माप(req));
	अगर (ret < 0)
		वापस ret;

	अगर (dir == DLN2_GPIO_सूचीECTION_OUT)
		set_bit(offset, dln2->output_enabled);
	अन्यथा
		clear_bit(offset, dln2->output_enabled);

	वापस ret;
पूर्ण

अटल पूर्णांक dln2_gpio_direction_input(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	वापस dln2_gpio_set_direction(chip, offset, DLN2_GPIO_सूचीECTION_IN);
पूर्ण

अटल पूर्णांक dln2_gpio_direction_output(काष्ठा gpio_chip *chip, अचिन्हित offset,
				      पूर्णांक value)
अणु
	काष्ठा dln2_gpio *dln2 = gpiochip_get_data(chip);
	पूर्णांक ret;

	ret = dln2_gpio_pin_set_out_val(dln2, offset, value);
	अगर (ret < 0)
		वापस ret;

	वापस dln2_gpio_set_direction(chip, offset, DLN2_GPIO_सूचीECTION_OUT);
पूर्ण

अटल पूर्णांक dln2_gpio_set_config(काष्ठा gpio_chip *chip, अचिन्हित offset,
				अचिन्हित दीर्घ config)
अणु
	काष्ठा dln2_gpio *dln2 = gpiochip_get_data(chip);
	__le32 duration;

	अगर (pinconf_to_config_param(config) != PIN_CONFIG_INPUT_DEBOUNCE)
		वापस -ENOTSUPP;

	duration = cpu_to_le32(pinconf_to_config_argument(config));
	वापस dln2_transfer_tx(dln2->pdev, DLN2_GPIO_SET_DEBOUNCE,
				&duration, माप(duration));
पूर्ण

अटल पूर्णांक dln2_gpio_set_event_cfg(काष्ठा dln2_gpio *dln2, अचिन्हित pin,
				   अचिन्हित type, अचिन्हित period)
अणु
	काष्ठा अणु
		__le16 pin;
		u8 type;
		__le16 period;
	पूर्ण __packed req = अणु
		.pin = cpu_to_le16(pin),
		.type = type,
		.period = cpu_to_le16(period),
	पूर्ण;

	वापस dln2_transfer_tx(dln2->pdev, DLN2_GPIO_PIN_SET_EVENT_CFG,
				&req, माप(req));
पूर्ण

अटल व्योम dln2_irq_unmask(काष्ठा irq_data *irqd)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(irqd);
	काष्ठा dln2_gpio *dln2 = gpiochip_get_data(gc);
	पूर्णांक pin = irqd_to_hwirq(irqd);

	set_bit(pin, dln2->unmasked_irqs);
पूर्ण

अटल व्योम dln2_irq_mask(काष्ठा irq_data *irqd)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(irqd);
	काष्ठा dln2_gpio *dln2 = gpiochip_get_data(gc);
	पूर्णांक pin = irqd_to_hwirq(irqd);

	clear_bit(pin, dln2->unmasked_irqs);
पूर्ण

अटल पूर्णांक dln2_irq_set_type(काष्ठा irq_data *irqd, अचिन्हित type)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(irqd);
	काष्ठा dln2_gpio *dln2 = gpiochip_get_data(gc);
	पूर्णांक pin = irqd_to_hwirq(irqd);

	चयन (type) अणु
	हाल IRQ_TYPE_LEVEL_HIGH:
		dln2->irq_type[pin] = DLN2_GPIO_EVENT_LVL_HIGH;
		अवरोध;
	हाल IRQ_TYPE_LEVEL_LOW:
		dln2->irq_type[pin] = DLN2_GPIO_EVENT_LVL_LOW;
		अवरोध;
	हाल IRQ_TYPE_EDGE_BOTH:
		dln2->irq_type[pin] = DLN2_GPIO_EVENT_CHANGE;
		अवरोध;
	हाल IRQ_TYPE_EDGE_RISING:
		dln2->irq_type[pin] = DLN2_GPIO_EVENT_CHANGE_RISING;
		अवरोध;
	हाल IRQ_TYPE_EDGE_FALLING:
		dln2->irq_type[pin] = DLN2_GPIO_EVENT_CHANGE_FALLING;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम dln2_irq_bus_lock(काष्ठा irq_data *irqd)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(irqd);
	काष्ठा dln2_gpio *dln2 = gpiochip_get_data(gc);

	mutex_lock(&dln2->irq_lock);
पूर्ण

अटल व्योम dln2_irq_bus_unlock(काष्ठा irq_data *irqd)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(irqd);
	काष्ठा dln2_gpio *dln2 = gpiochip_get_data(gc);
	पूर्णांक pin = irqd_to_hwirq(irqd);
	पूर्णांक enabled, unmasked;
	अचिन्हित type;
	पूर्णांक ret;

	enabled = test_bit(pin, dln2->enabled_irqs);
	unmasked = test_bit(pin, dln2->unmasked_irqs);

	अगर (enabled != unmasked) अणु
		अगर (unmasked) अणु
			type = dln2->irq_type[pin] & DLN2_GPIO_EVENT_MASK;
			set_bit(pin, dln2->enabled_irqs);
		पूर्ण अन्यथा अणु
			type = DLN2_GPIO_EVENT_NONE;
			clear_bit(pin, dln2->enabled_irqs);
		पूर्ण

		ret = dln2_gpio_set_event_cfg(dln2, pin, type, 0);
		अगर (ret)
			dev_err(dln2->gpio.parent, "failed to set event\n");
	पूर्ण

	mutex_unlock(&dln2->irq_lock);
पूर्ण

अटल काष्ठा irq_chip dln2_gpio_irqchip = अणु
	.name = "dln2-irq",
	.irq_mask = dln2_irq_mask,
	.irq_unmask = dln2_irq_unmask,
	.irq_set_type = dln2_irq_set_type,
	.irq_bus_lock = dln2_irq_bus_lock,
	.irq_bus_sync_unlock = dln2_irq_bus_unlock,
पूर्ण;

अटल व्योम dln2_gpio_event(काष्ठा platक्रमm_device *pdev, u16 echo,
			    स्थिर व्योम *data, पूर्णांक len)
अणु
	पूर्णांक pin, irq;

	स्थिर काष्ठा अणु
		__le16 count;
		__u8 type;
		__le16 pin;
		__u8 value;
	पूर्ण __packed *event = data;
	काष्ठा dln2_gpio *dln2 = platक्रमm_get_drvdata(pdev);

	अगर (len < माप(*event)) अणु
		dev_err(dln2->gpio.parent, "short event message\n");
		वापस;
	पूर्ण

	pin = le16_to_cpu(event->pin);
	अगर (pin >= dln2->gpio.ngpio) अणु
		dev_err(dln2->gpio.parent, "out of bounds pin %d\n", pin);
		वापस;
	पूर्ण

	irq = irq_find_mapping(dln2->gpio.irq.करोमुख्य, pin);
	अगर (!irq) अणु
		dev_err(dln2->gpio.parent, "pin %d not mapped to IRQ\n", pin);
		वापस;
	पूर्ण

	चयन (dln2->irq_type[pin]) अणु
	हाल DLN2_GPIO_EVENT_CHANGE_RISING:
		अगर (event->value)
			generic_handle_irq(irq);
		अवरोध;
	हाल DLN2_GPIO_EVENT_CHANGE_FALLING:
		अगर (!event->value)
			generic_handle_irq(irq);
		अवरोध;
	शेष:
		generic_handle_irq(irq);
	पूर्ण
पूर्ण

अटल पूर्णांक dln2_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dln2_gpio *dln2;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा gpio_irq_chip *girq;
	पूर्णांक pins;
	पूर्णांक ret;

	pins = dln2_gpio_get_pin_count(pdev);
	अगर (pins < 0) अणु
		dev_err(dev, "failed to get pin count: %d\n", pins);
		वापस pins;
	पूर्ण
	अगर (pins > DLN2_GPIO_MAX_PINS) अणु
		pins = DLN2_GPIO_MAX_PINS;
		dev_warn(dev, "clamping pins to %d\n", DLN2_GPIO_MAX_PINS);
	पूर्ण

	dln2 = devm_kzalloc(&pdev->dev, माप(*dln2), GFP_KERNEL);
	अगर (!dln2)
		वापस -ENOMEM;

	mutex_init(&dln2->irq_lock);

	dln2->pdev = pdev;

	dln2->gpio.label = "dln2";
	dln2->gpio.parent = dev;
	dln2->gpio.owner = THIS_MODULE;
	dln2->gpio.base = -1;
	dln2->gpio.ngpio = pins;
	dln2->gpio.can_sleep = true;
	dln2->gpio.set = dln2_gpio_set;
	dln2->gpio.get = dln2_gpio_get;
	dln2->gpio.request = dln2_gpio_request;
	dln2->gpio.मुक्त = dln2_gpio_मुक्त;
	dln2->gpio.get_direction = dln2_gpio_get_direction;
	dln2->gpio.direction_input = dln2_gpio_direction_input;
	dln2->gpio.direction_output = dln2_gpio_direction_output;
	dln2->gpio.set_config = dln2_gpio_set_config;

	girq = &dln2->gpio.irq;
	girq->chip = &dln2_gpio_irqchip;
	/* The event comes from the outside so no parent handler */
	girq->parent_handler = शून्य;
	girq->num_parents = 0;
	girq->parents = शून्य;
	girq->शेष_type = IRQ_TYPE_NONE;
	girq->handler = handle_simple_irq;

	platक्रमm_set_drvdata(pdev, dln2);

	ret = devm_gpiochip_add_data(dev, &dln2->gpio, dln2);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to add gpio chip: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = dln2_रेजिस्टर_event_cb(pdev, DLN2_GPIO_CONDITION_MET_EV,
				     dln2_gpio_event);
	अगर (ret) अणु
		dev_err(dev, "failed to register event cb: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dln2_gpio_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	dln2_unरेजिस्टर_event_cb(pdev, DLN2_GPIO_CONDITION_MET_EV);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver dln2_gpio_driver = अणु
	.driver.name	= "dln2-gpio",
	.probe		= dln2_gpio_probe,
	.हटाओ		= dln2_gpio_हटाओ,
पूर्ण;

module_platक्रमm_driver(dln2_gpio_driver);

MODULE_AUTHOR("Daniel Baluta <daniel.baluta@intel.com");
MODULE_DESCRIPTION("Driver for the Diolan DLN2 GPIO interface");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:dln2-gpio");
