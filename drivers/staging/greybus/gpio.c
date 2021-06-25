<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * GPIO Greybus driver.
 *
 * Copyright 2014 Google Inc.
 * Copyright 2014 Linaro Ltd.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/mutex.h>
#समावेश <linux/greybus.h>

#समावेश "gbphy.h"

काष्ठा gb_gpio_line अणु
	/* The following has to be an array of line_max entries */
	/* --> make them just a flags field */
	u8			active:    1,
				direction: 1,	/* 0 = output, 1 = input */
				value:     1;	/* 0 = low, 1 = high */
	u16			debounce_usec;

	u8			irq_type;
	bool			irq_type_pending;
	bool			masked;
	bool			masked_pending;
पूर्ण;

काष्ठा gb_gpio_controller अणु
	काष्ठा gbphy_device	*gbphy_dev;
	काष्ठा gb_connection	*connection;
	u8			line_max;	/* max line number */
	काष्ठा gb_gpio_line	*lines;

	काष्ठा gpio_chip	chip;
	काष्ठा irq_chip		irqc;
	काष्ठा mutex		irq_lock;
पूर्ण;
#घोषणा gpio_chip_to_gb_gpio_controller(chip) \
	container_of(chip, काष्ठा gb_gpio_controller, chip)
#घोषणा irq_data_to_gpio_chip(d) (d->करोमुख्य->host_data)

अटल पूर्णांक gb_gpio_line_count_operation(काष्ठा gb_gpio_controller *ggc)
अणु
	काष्ठा gb_gpio_line_count_response response;
	पूर्णांक ret;

	ret = gb_operation_sync(ggc->connection, GB_GPIO_TYPE_LINE_COUNT,
				शून्य, 0, &response, माप(response));
	अगर (!ret)
		ggc->line_max = response.count;
	वापस ret;
पूर्ण

अटल पूर्णांक gb_gpio_activate_operation(काष्ठा gb_gpio_controller *ggc, u8 which)
अणु
	काष्ठा gb_gpio_activate_request request;
	काष्ठा gbphy_device *gbphy_dev = ggc->gbphy_dev;
	पूर्णांक ret;

	ret = gbphy_runसमय_get_sync(gbphy_dev);
	अगर (ret)
		वापस ret;

	request.which = which;
	ret = gb_operation_sync(ggc->connection, GB_GPIO_TYPE_ACTIVATE,
				&request, माप(request), शून्य, 0);
	अगर (ret) अणु
		gbphy_runसमय_put_स्वतःsuspend(gbphy_dev);
		वापस ret;
	पूर्ण

	ggc->lines[which].active = true;

	वापस 0;
पूर्ण

अटल व्योम gb_gpio_deactivate_operation(काष्ठा gb_gpio_controller *ggc,
					 u8 which)
अणु
	काष्ठा gbphy_device *gbphy_dev = ggc->gbphy_dev;
	काष्ठा device *dev = &gbphy_dev->dev;
	काष्ठा gb_gpio_deactivate_request request;
	पूर्णांक ret;

	request.which = which;
	ret = gb_operation_sync(ggc->connection, GB_GPIO_TYPE_DEACTIVATE,
				&request, माप(request), शून्य, 0);
	अगर (ret) अणु
		dev_err(dev, "failed to deactivate gpio %u\n", which);
		जाओ out_pm_put;
	पूर्ण

	ggc->lines[which].active = false;

out_pm_put:
	gbphy_runसमय_put_स्वतःsuspend(gbphy_dev);
पूर्ण

अटल पूर्णांक gb_gpio_get_direction_operation(काष्ठा gb_gpio_controller *ggc,
					   u8 which)
अणु
	काष्ठा device *dev = &ggc->gbphy_dev->dev;
	काष्ठा gb_gpio_get_direction_request request;
	काष्ठा gb_gpio_get_direction_response response;
	पूर्णांक ret;
	u8 direction;

	request.which = which;
	ret = gb_operation_sync(ggc->connection, GB_GPIO_TYPE_GET_सूचीECTION,
				&request, माप(request),
				&response, माप(response));
	अगर (ret)
		वापस ret;

	direction = response.direction;
	अगर (direction && direction != 1) अणु
		dev_warn(dev, "gpio %u direction was %u (should be 0 or 1)\n",
			 which, direction);
	पूर्ण
	ggc->lines[which].direction = direction ? 1 : 0;
	वापस 0;
पूर्ण

अटल पूर्णांक gb_gpio_direction_in_operation(काष्ठा gb_gpio_controller *ggc,
					  u8 which)
अणु
	काष्ठा gb_gpio_direction_in_request request;
	पूर्णांक ret;

	request.which = which;
	ret = gb_operation_sync(ggc->connection, GB_GPIO_TYPE_सूचीECTION_IN,
				&request, माप(request), शून्य, 0);
	अगर (!ret)
		ggc->lines[which].direction = 1;
	वापस ret;
पूर्ण

अटल पूर्णांक gb_gpio_direction_out_operation(काष्ठा gb_gpio_controller *ggc,
					   u8 which, bool value_high)
अणु
	काष्ठा gb_gpio_direction_out_request request;
	पूर्णांक ret;

	request.which = which;
	request.value = value_high ? 1 : 0;
	ret = gb_operation_sync(ggc->connection, GB_GPIO_TYPE_सूचीECTION_OUT,
				&request, माप(request), शून्य, 0);
	अगर (!ret)
		ggc->lines[which].direction = 0;
	वापस ret;
पूर्ण

अटल पूर्णांक gb_gpio_get_value_operation(काष्ठा gb_gpio_controller *ggc,
				       u8 which)
अणु
	काष्ठा device *dev = &ggc->gbphy_dev->dev;
	काष्ठा gb_gpio_get_value_request request;
	काष्ठा gb_gpio_get_value_response response;
	पूर्णांक ret;
	u8 value;

	request.which = which;
	ret = gb_operation_sync(ggc->connection, GB_GPIO_TYPE_GET_VALUE,
				&request, माप(request),
				&response, माप(response));
	अगर (ret) अणु
		dev_err(dev, "failed to get value of gpio %u\n", which);
		वापस ret;
	पूर्ण

	value = response.value;
	अगर (value && value != 1) अणु
		dev_warn(dev, "gpio %u value was %u (should be 0 or 1)\n",
			 which, value);
	पूर्ण
	ggc->lines[which].value = value ? 1 : 0;
	वापस 0;
पूर्ण

अटल व्योम gb_gpio_set_value_operation(काष्ठा gb_gpio_controller *ggc,
					u8 which, bool value_high)
अणु
	काष्ठा device *dev = &ggc->gbphy_dev->dev;
	काष्ठा gb_gpio_set_value_request request;
	पूर्णांक ret;

	अगर (ggc->lines[which].direction == 1) अणु
		dev_warn(dev, "refusing to set value of input gpio %u\n",
			 which);
		वापस;
	पूर्ण

	request.which = which;
	request.value = value_high ? 1 : 0;
	ret = gb_operation_sync(ggc->connection, GB_GPIO_TYPE_SET_VALUE,
				&request, माप(request), शून्य, 0);
	अगर (ret) अणु
		dev_err(dev, "failed to set value of gpio %u\n", which);
		वापस;
	पूर्ण

	ggc->lines[which].value = request.value;
पूर्ण

अटल पूर्णांक gb_gpio_set_debounce_operation(काष्ठा gb_gpio_controller *ggc,
					  u8 which, u16 debounce_usec)
अणु
	काष्ठा gb_gpio_set_debounce_request request;
	पूर्णांक ret;

	request.which = which;
	request.usec = cpu_to_le16(debounce_usec);
	ret = gb_operation_sync(ggc->connection, GB_GPIO_TYPE_SET_DEBOUNCE,
				&request, माप(request), शून्य, 0);
	अगर (!ret)
		ggc->lines[which].debounce_usec = debounce_usec;
	वापस ret;
पूर्ण

अटल व्योम _gb_gpio_irq_mask(काष्ठा gb_gpio_controller *ggc, u8 hwirq)
अणु
	काष्ठा device *dev = &ggc->gbphy_dev->dev;
	काष्ठा gb_gpio_irq_mask_request request;
	पूर्णांक ret;

	request.which = hwirq;
	ret = gb_operation_sync(ggc->connection,
				GB_GPIO_TYPE_IRQ_MASK,
				&request, माप(request), शून्य, 0);
	अगर (ret)
		dev_err(dev, "failed to mask irq: %d\n", ret);
पूर्ण

अटल व्योम _gb_gpio_irq_unmask(काष्ठा gb_gpio_controller *ggc, u8 hwirq)
अणु
	काष्ठा device *dev = &ggc->gbphy_dev->dev;
	काष्ठा gb_gpio_irq_unmask_request request;
	पूर्णांक ret;

	request.which = hwirq;
	ret = gb_operation_sync(ggc->connection,
				GB_GPIO_TYPE_IRQ_UNMASK,
				&request, माप(request), शून्य, 0);
	अगर (ret)
		dev_err(dev, "failed to unmask irq: %d\n", ret);
पूर्ण

अटल व्योम _gb_gpio_irq_set_type(काष्ठा gb_gpio_controller *ggc,
				  u8 hwirq, u8 type)
अणु
	काष्ठा device *dev = &ggc->gbphy_dev->dev;
	काष्ठा gb_gpio_irq_type_request request;
	पूर्णांक ret;

	request.which = hwirq;
	request.type = type;

	ret = gb_operation_sync(ggc->connection,
				GB_GPIO_TYPE_IRQ_TYPE,
				&request, माप(request), शून्य, 0);
	अगर (ret)
		dev_err(dev, "failed to set irq type: %d\n", ret);
पूर्ण

अटल व्योम gb_gpio_irq_mask(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *chip = irq_data_to_gpio_chip(d);
	काष्ठा gb_gpio_controller *ggc = gpio_chip_to_gb_gpio_controller(chip);
	काष्ठा gb_gpio_line *line = &ggc->lines[d->hwirq];

	line->masked = true;
	line->masked_pending = true;
पूर्ण

अटल व्योम gb_gpio_irq_unmask(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *chip = irq_data_to_gpio_chip(d);
	काष्ठा gb_gpio_controller *ggc = gpio_chip_to_gb_gpio_controller(chip);
	काष्ठा gb_gpio_line *line = &ggc->lines[d->hwirq];

	line->masked = false;
	line->masked_pending = true;
पूर्ण

अटल पूर्णांक gb_gpio_irq_set_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक type)
अणु
	काष्ठा gpio_chip *chip = irq_data_to_gpio_chip(d);
	काष्ठा gb_gpio_controller *ggc = gpio_chip_to_gb_gpio_controller(chip);
	काष्ठा gb_gpio_line *line = &ggc->lines[d->hwirq];
	काष्ठा device *dev = &ggc->gbphy_dev->dev;
	u8 irq_type;

	चयन (type) अणु
	हाल IRQ_TYPE_NONE:
		irq_type = GB_GPIO_IRQ_TYPE_NONE;
		अवरोध;
	हाल IRQ_TYPE_EDGE_RISING:
		irq_type = GB_GPIO_IRQ_TYPE_EDGE_RISING;
		अवरोध;
	हाल IRQ_TYPE_EDGE_FALLING:
		irq_type = GB_GPIO_IRQ_TYPE_EDGE_FALLING;
		अवरोध;
	हाल IRQ_TYPE_EDGE_BOTH:
		irq_type = GB_GPIO_IRQ_TYPE_EDGE_BOTH;
		अवरोध;
	हाल IRQ_TYPE_LEVEL_LOW:
		irq_type = GB_GPIO_IRQ_TYPE_LEVEL_LOW;
		अवरोध;
	हाल IRQ_TYPE_LEVEL_HIGH:
		irq_type = GB_GPIO_IRQ_TYPE_LEVEL_HIGH;
		अवरोध;
	शेष:
		dev_err(dev, "unsupported irq type: %u\n", type);
		वापस -EINVAL;
	पूर्ण

	line->irq_type = irq_type;
	line->irq_type_pending = true;

	वापस 0;
पूर्ण

अटल व्योम gb_gpio_irq_bus_lock(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *chip = irq_data_to_gpio_chip(d);
	काष्ठा gb_gpio_controller *ggc = gpio_chip_to_gb_gpio_controller(chip);

	mutex_lock(&ggc->irq_lock);
पूर्ण

अटल व्योम gb_gpio_irq_bus_sync_unlock(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *chip = irq_data_to_gpio_chip(d);
	काष्ठा gb_gpio_controller *ggc = gpio_chip_to_gb_gpio_controller(chip);
	काष्ठा gb_gpio_line *line = &ggc->lines[d->hwirq];

	अगर (line->irq_type_pending) अणु
		_gb_gpio_irq_set_type(ggc, d->hwirq, line->irq_type);
		line->irq_type_pending = false;
	पूर्ण

	अगर (line->masked_pending) अणु
		अगर (line->masked)
			_gb_gpio_irq_mask(ggc, d->hwirq);
		अन्यथा
			_gb_gpio_irq_unmask(ggc, d->hwirq);
		line->masked_pending = false;
	पूर्ण

	mutex_unlock(&ggc->irq_lock);
पूर्ण

अटल पूर्णांक gb_gpio_request_handler(काष्ठा gb_operation *op)
अणु
	काष्ठा gb_connection *connection = op->connection;
	काष्ठा gb_gpio_controller *ggc = gb_connection_get_data(connection);
	काष्ठा device *dev = &ggc->gbphy_dev->dev;
	काष्ठा gb_message *request;
	काष्ठा gb_gpio_irq_event_request *event;
	u8 type = op->type;
	पूर्णांक irq, ret;

	अगर (type != GB_GPIO_TYPE_IRQ_EVENT) अणु
		dev_err(dev, "unsupported unsolicited request: %u\n", type);
		वापस -EINVAL;
	पूर्ण

	request = op->request;

	अगर (request->payload_size < माप(*event)) अणु
		dev_err(dev, "short event received (%zu < %zu)\n",
			request->payload_size, माप(*event));
		वापस -EINVAL;
	पूर्ण

	event = request->payload;
	अगर (event->which > ggc->line_max) अणु
		dev_err(dev, "invalid hw irq: %d\n", event->which);
		वापस -EINVAL;
	पूर्ण

	irq = irq_find_mapping(ggc->chip.irq.करोमुख्य, event->which);
	अगर (!irq) अणु
		dev_err(dev, "failed to find IRQ\n");
		वापस -EINVAL;
	पूर्ण

	local_irq_disable();
	ret = generic_handle_irq(irq);
	local_irq_enable();

	अगर (ret)
		dev_err(dev, "failed to invoke irq handler\n");

	वापस ret;
पूर्ण

अटल पूर्णांक gb_gpio_request(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा gb_gpio_controller *ggc = gpio_chip_to_gb_gpio_controller(chip);

	वापस gb_gpio_activate_operation(ggc, (u8)offset);
पूर्ण

अटल व्योम gb_gpio_मुक्त(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा gb_gpio_controller *ggc = gpio_chip_to_gb_gpio_controller(chip);

	gb_gpio_deactivate_operation(ggc, (u8)offset);
पूर्ण

अटल पूर्णांक gb_gpio_get_direction(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा gb_gpio_controller *ggc = gpio_chip_to_gb_gpio_controller(chip);
	u8 which;
	पूर्णांक ret;

	which = (u8)offset;
	ret = gb_gpio_get_direction_operation(ggc, which);
	अगर (ret)
		वापस ret;

	वापस ggc->lines[which].direction ? 1 : 0;
पूर्ण

अटल पूर्णांक gb_gpio_direction_input(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा gb_gpio_controller *ggc = gpio_chip_to_gb_gpio_controller(chip);

	वापस gb_gpio_direction_in_operation(ggc, (u8)offset);
पूर्ण

अटल पूर्णांक gb_gpio_direction_output(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset,
				    पूर्णांक value)
अणु
	काष्ठा gb_gpio_controller *ggc = gpio_chip_to_gb_gpio_controller(chip);

	वापस gb_gpio_direction_out_operation(ggc, (u8)offset, !!value);
पूर्ण

अटल पूर्णांक gb_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा gb_gpio_controller *ggc = gpio_chip_to_gb_gpio_controller(chip);
	u8 which;
	पूर्णांक ret;

	which = (u8)offset;
	ret = gb_gpio_get_value_operation(ggc, which);
	अगर (ret)
		वापस ret;

	वापस ggc->lines[which].value;
पूर्ण

अटल व्योम gb_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset, पूर्णांक value)
अणु
	काष्ठा gb_gpio_controller *ggc = gpio_chip_to_gb_gpio_controller(chip);

	gb_gpio_set_value_operation(ggc, (u8)offset, !!value);
पूर्ण

अटल पूर्णांक gb_gpio_set_config(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset,
			      अचिन्हित दीर्घ config)
अणु
	काष्ठा gb_gpio_controller *ggc = gpio_chip_to_gb_gpio_controller(chip);
	u32 debounce;

	अगर (pinconf_to_config_param(config) != PIN_CONFIG_INPUT_DEBOUNCE)
		वापस -ENOTSUPP;

	debounce = pinconf_to_config_argument(config);
	अगर (debounce > U16_MAX)
		वापस -EINVAL;

	वापस gb_gpio_set_debounce_operation(ggc, (u8)offset, (u16)debounce);
पूर्ण

अटल पूर्णांक gb_gpio_controller_setup(काष्ठा gb_gpio_controller *ggc)
अणु
	पूर्णांक ret;

	/* Now find out how many lines there are */
	ret = gb_gpio_line_count_operation(ggc);
	अगर (ret)
		वापस ret;

	ggc->lines = kसुस्मृति(ggc->line_max + 1, माप(*ggc->lines),
			     GFP_KERNEL);
	अगर (!ggc->lines)
		वापस -ENOMEM;

	वापस ret;
पूर्ण

अटल पूर्णांक gb_gpio_probe(काष्ठा gbphy_device *gbphy_dev,
			 स्थिर काष्ठा gbphy_device_id *id)
अणु
	काष्ठा gb_connection *connection;
	काष्ठा gb_gpio_controller *ggc;
	काष्ठा gpio_chip *gpio;
	काष्ठा gpio_irq_chip *girq;
	काष्ठा irq_chip *irqc;
	पूर्णांक ret;

	ggc = kzalloc(माप(*ggc), GFP_KERNEL);
	अगर (!ggc)
		वापस -ENOMEM;

	connection =
		gb_connection_create(gbphy_dev->bundle,
				     le16_to_cpu(gbphy_dev->cport_desc->id),
				     gb_gpio_request_handler);
	अगर (IS_ERR(connection)) अणु
		ret = PTR_ERR(connection);
		जाओ निकास_ggc_मुक्त;
	पूर्ण

	ggc->connection = connection;
	gb_connection_set_data(connection, ggc);
	ggc->gbphy_dev = gbphy_dev;
	gb_gbphy_set_data(gbphy_dev, ggc);

	ret = gb_connection_enable_tx(connection);
	अगर (ret)
		जाओ निकास_connection_destroy;

	ret = gb_gpio_controller_setup(ggc);
	अगर (ret)
		जाओ निकास_connection_disable;

	irqc = &ggc->irqc;
	irqc->irq_mask = gb_gpio_irq_mask;
	irqc->irq_unmask = gb_gpio_irq_unmask;
	irqc->irq_set_type = gb_gpio_irq_set_type;
	irqc->irq_bus_lock = gb_gpio_irq_bus_lock;
	irqc->irq_bus_sync_unlock = gb_gpio_irq_bus_sync_unlock;
	irqc->name = "greybus_gpio";

	mutex_init(&ggc->irq_lock);

	gpio = &ggc->chip;

	gpio->label = "greybus_gpio";
	gpio->parent = &gbphy_dev->dev;
	gpio->owner = THIS_MODULE;

	gpio->request = gb_gpio_request;
	gpio->मुक्त = gb_gpio_मुक्त;
	gpio->get_direction = gb_gpio_get_direction;
	gpio->direction_input = gb_gpio_direction_input;
	gpio->direction_output = gb_gpio_direction_output;
	gpio->get = gb_gpio_get;
	gpio->set = gb_gpio_set;
	gpio->set_config = gb_gpio_set_config;
	gpio->base = -1;		/* Allocate base dynamically */
	gpio->ngpio = ggc->line_max + 1;
	gpio->can_sleep = true;

	girq = &gpio->irq;
	girq->chip = irqc;
	/* The event comes from the outside so no parent handler */
	girq->parent_handler = शून्य;
	girq->num_parents = 0;
	girq->parents = शून्य;
	girq->शेष_type = IRQ_TYPE_NONE;
	girq->handler = handle_level_irq;

	ret = gb_connection_enable(connection);
	अगर (ret)
		जाओ निकास_line_मुक्त;

	ret = gpiochip_add(gpio);
	अगर (ret) अणु
		dev_err(&gbphy_dev->dev, "failed to add gpio chip: %d\n", ret);
		जाओ निकास_line_मुक्त;
	पूर्ण

	gbphy_runसमय_put_स्वतःsuspend(gbphy_dev);
	वापस 0;

निकास_line_मुक्त:
	kमुक्त(ggc->lines);
निकास_connection_disable:
	gb_connection_disable(connection);
निकास_connection_destroy:
	gb_connection_destroy(connection);
निकास_ggc_मुक्त:
	kमुक्त(ggc);
	वापस ret;
पूर्ण

अटल व्योम gb_gpio_हटाओ(काष्ठा gbphy_device *gbphy_dev)
अणु
	काष्ठा gb_gpio_controller *ggc = gb_gbphy_get_data(gbphy_dev);
	काष्ठा gb_connection *connection = ggc->connection;
	पूर्णांक ret;

	ret = gbphy_runसमय_get_sync(gbphy_dev);
	अगर (ret)
		gbphy_runसमय_get_noresume(gbphy_dev);

	gb_connection_disable_rx(connection);
	gpiochip_हटाओ(&ggc->chip);
	gb_connection_disable(connection);
	gb_connection_destroy(connection);
	kमुक्त(ggc->lines);
	kमुक्त(ggc);
पूर्ण

अटल स्थिर काष्ठा gbphy_device_id gb_gpio_id_table[] = अणु
	अणु GBPHY_PROTOCOL(GREYBUS_PROTOCOL_GPIO) पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(gbphy, gb_gpio_id_table);

अटल काष्ठा gbphy_driver gpio_driver = अणु
	.name		= "gpio",
	.probe		= gb_gpio_probe,
	.हटाओ		= gb_gpio_हटाओ,
	.id_table	= gb_gpio_id_table,
पूर्ण;

module_gbphy_driver(gpio_driver);
MODULE_LICENSE("GPL v2");
