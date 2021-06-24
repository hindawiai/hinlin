<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2012-2020 Synaptics Incorporated
 */

#समावेश <linux/kernel.h>
#समावेश <linux/rmi.h>
#समावेश <linux/input.h>
#समावेश <linux/slab.h>
#समावेश "rmi_driver.h"

#घोषणा RMI_F3A_MAX_GPIO_COUNT		128
#घोषणा RMI_F3A_MAX_REG_SIZE		DIV_ROUND_UP(RMI_F3A_MAX_GPIO_COUNT, 8)

/* Defs क्रम Query 0 */
#घोषणा RMI_F3A_GPIO_COUNT		0x7F

#घोषणा RMI_F3A_DATA_REGS_MAX_SIZE	RMI_F3A_MAX_REG_SIZE

#घोषणा TRACKSTICK_RANGE_START		3
#घोषणा TRACKSTICK_RANGE_END		6

काष्ठा f3a_data अणु
	/* Query Data */
	u8 gpio_count;

	u8 रेजिस्टर_count;

	u8 data_regs[RMI_F3A_DATA_REGS_MAX_SIZE];
	u16 *gpio_key_map;

	काष्ठा input_dev *input;

	काष्ठा rmi_function *f03;
	bool trackstick_buttons;
पूर्ण;

अटल व्योम rmi_f3a_report_button(काष्ठा rmi_function *fn,
				  काष्ठा f3a_data *f3a, अचिन्हित पूर्णांक button)
अणु
	u16 key_code = f3a->gpio_key_map[button];
	bool key_करोwn = !(f3a->data_regs[0] & BIT(button));

	अगर (f3a->trackstick_buttons &&
		button >= TRACKSTICK_RANGE_START &&
		button <= TRACKSTICK_RANGE_END) अणु
		rmi_f03_overग_लिखो_button(f3a->f03, key_code, key_करोwn);
	पूर्ण अन्यथा अणु
		rmi_dbg(RMI_DEBUG_FN, &fn->dev,
			"%s: call input report key (0x%04x) value (0x%02x)",
			__func__, key_code, key_करोwn);
		input_report_key(f3a->input, key_code, key_करोwn);
	पूर्ण
पूर्ण

अटल irqवापस_t rmi_f3a_attention(पूर्णांक irq, व्योम *ctx)
अणु
	काष्ठा rmi_function *fn = ctx;
	काष्ठा f3a_data *f3a = dev_get_drvdata(&fn->dev);
	काष्ठा rmi_driver_data *drvdata = dev_get_drvdata(&fn->rmi_dev->dev);
	पूर्णांक error;
	पूर्णांक i;

	अगर (drvdata->attn_data.data) अणु
		अगर (drvdata->attn_data.size < f3a->रेजिस्टर_count) अणु
			dev_warn(&fn->dev,
				 "F3A interrupted, but data is missing\n");
			वापस IRQ_HANDLED;
		पूर्ण
		स_नकल(f3a->data_regs, drvdata->attn_data.data,
			f3a->रेजिस्टर_count);
		drvdata->attn_data.data += f3a->रेजिस्टर_count;
		drvdata->attn_data.size -= f3a->रेजिस्टर_count;
	पूर्ण अन्यथा अणु
		error = rmi_पढ़ो_block(fn->rmi_dev, fn->fd.data_base_addr,
					f3a->data_regs, f3a->रेजिस्टर_count);
		अगर (error) अणु
			dev_err(&fn->dev,
				"%s: Failed to read F3a data registers: %d\n",
				__func__, error);
			वापस IRQ_RETVAL(error);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < f3a->gpio_count; i++)
		अगर (f3a->gpio_key_map[i] != KEY_RESERVED)
			rmi_f3a_report_button(fn, f3a, i);
	अगर (f3a->trackstick_buttons)
		rmi_f03_commit_buttons(f3a->f03);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक rmi_f3a_config(काष्ठा rmi_function *fn)
अणु
	काष्ठा f3a_data *f3a = dev_get_drvdata(&fn->dev);
	काष्ठा rmi_driver *drv = fn->rmi_dev->driver;
	स्थिर काष्ठा rmi_device_platक्रमm_data *pdata =
			rmi_get_platक्रमm_data(fn->rmi_dev);

	अगर (!f3a)
		वापस 0;

	अगर (pdata->gpio_data.trackstick_buttons) अणु
		/* Try [re-]establish link to F03. */
		f3a->f03 = rmi_find_function(fn->rmi_dev, 0x03);
		f3a->trackstick_buttons = f3a->f03 != शून्य;
	पूर्ण

	drv->set_irq_bits(fn->rmi_dev, fn->irq_mask);

	वापस 0;
पूर्ण

अटल bool rmi_f3a_is_valid_button(पूर्णांक button, काष्ठा f3a_data *f3a,
					u8 *query1_regs, u8 *ctrl1_regs)
अणु
	/* gpio exist && direction input */
	वापस (query1_regs[0] & BIT(button)) && !(ctrl1_regs[0] & BIT(button));
पूर्ण

अटल पूर्णांक rmi_f3a_map_gpios(काष्ठा rmi_function *fn, काष्ठा f3a_data *f3a,
				u8 *query1_regs, u8 *ctrl1_regs)
अणु
	स्थिर काष्ठा rmi_device_platक्रमm_data *pdata =
			rmi_get_platक्रमm_data(fn->rmi_dev);
	काष्ठा input_dev *input = f3a->input;
	अचिन्हित पूर्णांक button = BTN_LEFT;
	अचिन्हित पूर्णांक trackstick_button = BTN_LEFT;
	bool button_mapped = false;
	पूर्णांक i;
	पूर्णांक button_count = min_t(u8, f3a->gpio_count, TRACKSTICK_RANGE_END);

	f3a->gpio_key_map = devm_kसुस्मृति(&fn->dev,
						button_count,
						माप(f3a->gpio_key_map[0]),
						GFP_KERNEL);
	अगर (!f3a->gpio_key_map) अणु
		dev_err(&fn->dev, "Failed to allocate gpio map memory.\n");
		वापस -ENOMEM;
	पूर्ण

	क्रम (i = 0; i < button_count; i++) अणु
		अगर (!rmi_f3a_is_valid_button(i, f3a, query1_regs, ctrl1_regs))
			जारी;

		अगर (pdata->gpio_data.trackstick_buttons &&
			i >= TRACKSTICK_RANGE_START &&
			i < TRACKSTICK_RANGE_END) अणु
			f3a->gpio_key_map[i] = trackstick_button++;
		पूर्ण अन्यथा अगर (!pdata->gpio_data.buttonpad || !button_mapped) अणु
			f3a->gpio_key_map[i] = button;
			input_set_capability(input, EV_KEY, button++);
			button_mapped = true;
		पूर्ण
	पूर्ण
	input->keycode = f3a->gpio_key_map;
	input->keycodesize = माप(f3a->gpio_key_map[0]);
	input->keycodemax = f3a->gpio_count;

	अगर (pdata->gpio_data.buttonpad || (button - BTN_LEFT == 1))
		__set_bit(INPUT_PROP_BUTTONPAD, input->propbit);

	वापस 0;
पूर्ण

अटल पूर्णांक rmi_f3a_initialize(काष्ठा rmi_function *fn, काष्ठा f3a_data *f3a)
अणु
	u8 query1[RMI_F3A_MAX_REG_SIZE];
	u8 ctrl1[RMI_F3A_MAX_REG_SIZE];
	u8 buf;
	पूर्णांक error;

	error = rmi_पढ़ो(fn->rmi_dev, fn->fd.query_base_addr, &buf);
	अगर (error < 0) अणु
		dev_err(&fn->dev, "Failed to read general info register: %d\n",
			error);
		वापस -ENODEV;
	पूर्ण

	f3a->gpio_count = buf & RMI_F3A_GPIO_COUNT;
	f3a->रेजिस्टर_count = DIV_ROUND_UP(f3a->gpio_count, 8);

	/* Query1 -> gpio exist */
	error = rmi_पढ़ो_block(fn->rmi_dev, fn->fd.query_base_addr + 1,
				query1, f3a->रेजिस्टर_count);
	अगर (error) अणु
		dev_err(&fn->dev, "Failed to read query1 register\n");
		वापस error;
	पूर्ण

	/* Ctrl1 -> gpio direction */
	error = rmi_पढ़ो_block(fn->rmi_dev, fn->fd.control_base_addr + 1,
				ctrl1, f3a->रेजिस्टर_count);
	अगर (error) अणु
		dev_err(&fn->dev, "Failed to read control1 register\n");
		वापस error;
	पूर्ण

	error = rmi_f3a_map_gpios(fn, f3a, query1, ctrl1);
	अगर (error)
		वापस error;

	वापस 0;
पूर्ण

अटल पूर्णांक rmi_f3a_probe(काष्ठा rmi_function *fn)
अणु
	काष्ठा rmi_device *rmi_dev = fn->rmi_dev;
	काष्ठा rmi_driver_data *drv_data = dev_get_drvdata(&rmi_dev->dev);
	काष्ठा f3a_data *f3a;
	पूर्णांक error;

	अगर (!drv_data->input) अणु
		dev_info(&fn->dev, "F3A: no input device found, ignoring\n");
		वापस -ENXIO;
	पूर्ण

	f3a = devm_kzalloc(&fn->dev, माप(*f3a), GFP_KERNEL);
	अगर (!f3a)
		वापस -ENOMEM;

	f3a->input = drv_data->input;

	error = rmi_f3a_initialize(fn, f3a);
	अगर (error)
		वापस error;

	dev_set_drvdata(&fn->dev, f3a);
	वापस 0;
पूर्ण

काष्ठा rmi_function_handler rmi_f3a_handler = अणु
	.driver = अणु
		.name = "rmi4_f3a",
	पूर्ण,
	.func = 0x3a,
	.probe = rmi_f3a_probe,
	.config = rmi_f3a_config,
	.attention = rmi_f3a_attention,
पूर्ण;
