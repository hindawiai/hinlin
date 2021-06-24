<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2012-2016 Synaptics Incorporated
 */

#समावेश <linux/kernel.h>
#समावेश <linux/rmi.h>
#समावेश <linux/input.h>
#समावेश <linux/slab.h>
#समावेश "rmi_driver.h"

#घोषणा RMI_F30_QUERY_SIZE			2

/* Defs क्रम Query 0 */
#घोषणा RMI_F30_EXTENDED_PATTERNS		0x01
#घोषणा RMI_F30_HAS_MAPPABLE_BUTTONS		BIT(1)
#घोषणा RMI_F30_HAS_LED				BIT(2)
#घोषणा RMI_F30_HAS_GPIO			BIT(3)
#घोषणा RMI_F30_HAS_HAPTIC			BIT(4)
#घोषणा RMI_F30_HAS_GPIO_DRV_CTL		BIT(5)
#घोषणा RMI_F30_HAS_MECH_MOUSE_BTNS		BIT(6)

/* Defs क्रम Query 1 */
#घोषणा RMI_F30_GPIO_LED_COUNT			0x1F

/* Defs क्रम Control Registers */
#घोषणा RMI_F30_CTRL_1_GPIO_DEBOUNCE		0x01
#घोषणा RMI_F30_CTRL_1_HALT			BIT(4)
#घोषणा RMI_F30_CTRL_1_HALTED			BIT(5)
#घोषणा RMI_F30_CTRL_10_NUM_MECH_MOUSE_BTNS	0x03

#घोषणा RMI_F30_CTRL_MAX_REGS		32
#घोषणा RMI_F30_CTRL_MAX_BYTES		DIV_ROUND_UP(RMI_F30_CTRL_MAX_REGS, 8)
#घोषणा RMI_F30_CTRL_MAX_REG_BLOCKS	11

#घोषणा RMI_F30_CTRL_REGS_MAX_SIZE (RMI_F30_CTRL_MAX_BYTES		\
					+ 1				\
					+ RMI_F30_CTRL_MAX_BYTES	\
					+ RMI_F30_CTRL_MAX_BYTES	\
					+ RMI_F30_CTRL_MAX_BYTES	\
					+ 6				\
					+ RMI_F30_CTRL_MAX_REGS		\
					+ RMI_F30_CTRL_MAX_REGS		\
					+ RMI_F30_CTRL_MAX_BYTES	\
					+ 1				\
					+ 1)

#घोषणा TRACKSTICK_RANGE_START		3
#घोषणा TRACKSTICK_RANGE_END		6

काष्ठा rmi_f30_ctrl_data अणु
	पूर्णांक address;
	पूर्णांक length;
	u8 *regs;
पूर्ण;

काष्ठा f30_data अणु
	/* Query Data */
	bool has_extended_pattern;
	bool has_mappable_buttons;
	bool has_led;
	bool has_gpio;
	bool has_haptic;
	bool has_gpio_driver_control;
	bool has_mech_mouse_btns;
	u8 gpioled_count;

	u8 रेजिस्टर_count;

	/* Control Register Data */
	काष्ठा rmi_f30_ctrl_data ctrl[RMI_F30_CTRL_MAX_REG_BLOCKS];
	u8 ctrl_regs[RMI_F30_CTRL_REGS_MAX_SIZE];
	u32 ctrl_regs_size;

	u8 data_regs[RMI_F30_CTRL_MAX_BYTES];
	u16 *gpioled_key_map;

	काष्ठा input_dev *input;

	काष्ठा rmi_function *f03;
	bool trackstick_buttons;
पूर्ण;

अटल पूर्णांक rmi_f30_पढ़ो_control_parameters(काष्ठा rmi_function *fn,
						काष्ठा f30_data *f30)
अणु
	पूर्णांक error;

	error = rmi_पढ़ो_block(fn->rmi_dev, fn->fd.control_base_addr,
			       f30->ctrl_regs, f30->ctrl_regs_size);
	अगर (error) अणु
		dev_err(&fn->dev,
			"%s: Could not read control registers at 0x%x: %d\n",
			__func__, fn->fd.control_base_addr, error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम rmi_f30_report_button(काष्ठा rmi_function *fn,
				  काष्ठा f30_data *f30, अचिन्हित पूर्णांक button)
अणु
	अचिन्हित पूर्णांक reg_num = button >> 3;
	अचिन्हित पूर्णांक bit_num = button & 0x07;
	u16 key_code = f30->gpioled_key_map[button];
	bool key_करोwn = !(f30->data_regs[reg_num] & BIT(bit_num));

	अगर (f30->trackstick_buttons &&
	    button >= TRACKSTICK_RANGE_START &&
	    button <= TRACKSTICK_RANGE_END) अणु
		rmi_f03_overग_लिखो_button(f30->f03, key_code, key_करोwn);
	पूर्ण अन्यथा अणु
		rmi_dbg(RMI_DEBUG_FN, &fn->dev,
			"%s: call input report key (0x%04x) value (0x%02x)",
			__func__, key_code, key_करोwn);

		input_report_key(f30->input, key_code, key_करोwn);
	पूर्ण
पूर्ण

अटल irqवापस_t rmi_f30_attention(पूर्णांक irq, व्योम *ctx)
अणु
	काष्ठा rmi_function *fn = ctx;
	काष्ठा f30_data *f30 = dev_get_drvdata(&fn->dev);
	काष्ठा rmi_driver_data *drvdata = dev_get_drvdata(&fn->rmi_dev->dev);
	पूर्णांक error;
	पूर्णांक i;

	/* Read the gpi led data. */
	अगर (drvdata->attn_data.data) अणु
		अगर (drvdata->attn_data.size < f30->रेजिस्टर_count) अणु
			dev_warn(&fn->dev,
				 "F30 interrupted, but data is missing\n");
			वापस IRQ_HANDLED;
		पूर्ण
		स_नकल(f30->data_regs, drvdata->attn_data.data,
			f30->रेजिस्टर_count);
		drvdata->attn_data.data += f30->रेजिस्टर_count;
		drvdata->attn_data.size -= f30->रेजिस्टर_count;
	पूर्ण अन्यथा अणु
		error = rmi_पढ़ो_block(fn->rmi_dev, fn->fd.data_base_addr,
				       f30->data_regs, f30->रेजिस्टर_count);
		अगर (error) अणु
			dev_err(&fn->dev,
				"%s: Failed to read F30 data registers: %d\n",
				__func__, error);
			वापस IRQ_RETVAL(error);
		पूर्ण
	पूर्ण

	अगर (f30->has_gpio) अणु
		क्रम (i = 0; i < f30->gpioled_count; i++)
			अगर (f30->gpioled_key_map[i] != KEY_RESERVED)
				rmi_f30_report_button(fn, f30, i);
		अगर (f30->trackstick_buttons)
			rmi_f03_commit_buttons(f30->f03);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक rmi_f30_config(काष्ठा rmi_function *fn)
अणु
	काष्ठा f30_data *f30 = dev_get_drvdata(&fn->dev);
	काष्ठा rmi_driver *drv = fn->rmi_dev->driver;
	स्थिर काष्ठा rmi_device_platक्रमm_data *pdata =
				rmi_get_platक्रमm_data(fn->rmi_dev);
	पूर्णांक error;

	/* can happen अगर gpio_data.disable is set */
	अगर (!f30)
		वापस 0;

	अगर (pdata->gpio_data.trackstick_buttons) अणु
		/* Try [re-]establish link to F03. */
		f30->f03 = rmi_find_function(fn->rmi_dev, 0x03);
		f30->trackstick_buttons = f30->f03 != शून्य;
	पूर्ण

	अगर (pdata->gpio_data.disable) अणु
		drv->clear_irq_bits(fn->rmi_dev, fn->irq_mask);
	पूर्ण अन्यथा अणु
		/* Write Control Register values back to device */
		error = rmi_ग_लिखो_block(fn->rmi_dev, fn->fd.control_base_addr,
					f30->ctrl_regs, f30->ctrl_regs_size);
		अगर (error) अणु
			dev_err(&fn->dev,
				"%s: Could not write control registers at 0x%x: %d\n",
				__func__, fn->fd.control_base_addr, error);
			वापस error;
		पूर्ण

		drv->set_irq_bits(fn->rmi_dev, fn->irq_mask);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम rmi_f30_set_ctrl_data(काष्ठा rmi_f30_ctrl_data *ctrl,
				  पूर्णांक *ctrl_addr, पूर्णांक len, u8 **reg)
अणु
	ctrl->address = *ctrl_addr;
	ctrl->length = len;
	ctrl->regs = *reg;
	*ctrl_addr += len;
	*reg += len;
पूर्ण

अटल bool rmi_f30_is_valid_button(पूर्णांक button, काष्ठा rmi_f30_ctrl_data *ctrl)
अणु
	पूर्णांक byte_position = button >> 3;
	पूर्णांक bit_position = button & 0x07;

	/*
	 * ctrl2 -> dir == 0 -> input mode
	 * ctrl3 -> data == 1 -> actual button
	 */
	वापस !(ctrl[2].regs[byte_position] & BIT(bit_position)) &&
		(ctrl[3].regs[byte_position] & BIT(bit_position));
पूर्ण

अटल पूर्णांक rmi_f30_map_gpios(काष्ठा rmi_function *fn,
			     काष्ठा f30_data *f30)
अणु
	स्थिर काष्ठा rmi_device_platक्रमm_data *pdata =
					rmi_get_platक्रमm_data(fn->rmi_dev);
	काष्ठा input_dev *input = f30->input;
	अचिन्हित पूर्णांक button = BTN_LEFT;
	अचिन्हित पूर्णांक trackstick_button = BTN_LEFT;
	bool button_mapped = false;
	पूर्णांक i;
	पूर्णांक button_count = min_t(u8, f30->gpioled_count, TRACKSTICK_RANGE_END);

	f30->gpioled_key_map = devm_kसुस्मृति(&fn->dev,
					    button_count,
					    माप(f30->gpioled_key_map[0]),
					    GFP_KERNEL);
	अगर (!f30->gpioled_key_map) अणु
		dev_err(&fn->dev, "Failed to allocate gpioled map memory.\n");
		वापस -ENOMEM;
	पूर्ण

	क्रम (i = 0; i < button_count; i++) अणु
		अगर (!rmi_f30_is_valid_button(i, f30->ctrl))
			जारी;

		अगर (pdata->gpio_data.trackstick_buttons &&
		    i >= TRACKSTICK_RANGE_START && i < TRACKSTICK_RANGE_END) अणु
			f30->gpioled_key_map[i] = trackstick_button++;
		पूर्ण अन्यथा अगर (!pdata->gpio_data.buttonpad || !button_mapped) अणु
			f30->gpioled_key_map[i] = button;
			input_set_capability(input, EV_KEY, button++);
			button_mapped = true;
		पूर्ण
	पूर्ण

	input->keycode = f30->gpioled_key_map;
	input->keycodesize = माप(f30->gpioled_key_map[0]);
	input->keycodemax = f30->gpioled_count;

	/*
	 * Buttonpad could be also inferred from f30->has_mech_mouse_btns,
	 * but I am not sure, so use only the pdata info and the number of
	 * mapped buttons.
	 */
	अगर (pdata->gpio_data.buttonpad || (button - BTN_LEFT == 1))
		__set_bit(INPUT_PROP_BUTTONPAD, input->propbit);

	वापस 0;
पूर्ण

अटल पूर्णांक rmi_f30_initialize(काष्ठा rmi_function *fn, काष्ठा f30_data *f30)
अणु
	u8 *ctrl_reg = f30->ctrl_regs;
	पूर्णांक control_address = fn->fd.control_base_addr;
	u8 buf[RMI_F30_QUERY_SIZE];
	पूर्णांक error;

	error = rmi_पढ़ो_block(fn->rmi_dev, fn->fd.query_base_addr,
			       buf, RMI_F30_QUERY_SIZE);
	अगर (error) अणु
		dev_err(&fn->dev, "Failed to read query register\n");
		वापस error;
	पूर्ण

	f30->has_extended_pattern = buf[0] & RMI_F30_EXTENDED_PATTERNS;
	f30->has_mappable_buttons = buf[0] & RMI_F30_HAS_MAPPABLE_BUTTONS;
	f30->has_led = buf[0] & RMI_F30_HAS_LED;
	f30->has_gpio = buf[0] & RMI_F30_HAS_GPIO;
	f30->has_haptic = buf[0] & RMI_F30_HAS_HAPTIC;
	f30->has_gpio_driver_control = buf[0] & RMI_F30_HAS_GPIO_DRV_CTL;
	f30->has_mech_mouse_btns = buf[0] & RMI_F30_HAS_MECH_MOUSE_BTNS;
	f30->gpioled_count = buf[1] & RMI_F30_GPIO_LED_COUNT;

	f30->रेजिस्टर_count = DIV_ROUND_UP(f30->gpioled_count, 8);

	अगर (f30->has_gpio && f30->has_led)
		rmi_f30_set_ctrl_data(&f30->ctrl[0], &control_address,
				      f30->रेजिस्टर_count, &ctrl_reg);

	rmi_f30_set_ctrl_data(&f30->ctrl[1], &control_address,
			      माप(u8), &ctrl_reg);

	अगर (f30->has_gpio) अणु
		rmi_f30_set_ctrl_data(&f30->ctrl[2], &control_address,
				      f30->रेजिस्टर_count, &ctrl_reg);

		rmi_f30_set_ctrl_data(&f30->ctrl[3], &control_address,
				      f30->रेजिस्टर_count, &ctrl_reg);
	पूर्ण

	अगर (f30->has_led) अणु
		rmi_f30_set_ctrl_data(&f30->ctrl[4], &control_address,
				      f30->रेजिस्टर_count, &ctrl_reg);

		rmi_f30_set_ctrl_data(&f30->ctrl[5], &control_address,
				      f30->has_extended_pattern ? 6 : 2,
				      &ctrl_reg);
	पूर्ण

	अगर (f30->has_led || f30->has_gpio_driver_control) अणु
		/* control 6 uses a byte per gpio/led */
		rmi_f30_set_ctrl_data(&f30->ctrl[6], &control_address,
				      f30->gpioled_count, &ctrl_reg);
	पूर्ण

	अगर (f30->has_mappable_buttons) अणु
		/* control 7 uses a byte per gpio/led */
		rmi_f30_set_ctrl_data(&f30->ctrl[7], &control_address,
				      f30->gpioled_count, &ctrl_reg);
	पूर्ण

	अगर (f30->has_haptic) अणु
		rmi_f30_set_ctrl_data(&f30->ctrl[8], &control_address,
				      f30->रेजिस्टर_count, &ctrl_reg);

		rmi_f30_set_ctrl_data(&f30->ctrl[9], &control_address,
				      माप(u8), &ctrl_reg);
	पूर्ण

	अगर (f30->has_mech_mouse_btns)
		rmi_f30_set_ctrl_data(&f30->ctrl[10], &control_address,
				      माप(u8), &ctrl_reg);

	f30->ctrl_regs_size = ctrl_reg -
				f30->ctrl_regs ?: RMI_F30_CTRL_REGS_MAX_SIZE;

	error = rmi_f30_पढ़ो_control_parameters(fn, f30);
	अगर (error) अणु
		dev_err(&fn->dev,
			"Failed to initialize F30 control params: %d\n",
			error);
		वापस error;
	पूर्ण

	अगर (f30->has_gpio) अणु
		error = rmi_f30_map_gpios(fn, f30);
		अगर (error)
			वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rmi_f30_probe(काष्ठा rmi_function *fn)
अणु
	काष्ठा rmi_device *rmi_dev = fn->rmi_dev;
	स्थिर काष्ठा rmi_device_platक्रमm_data *pdata =
					rmi_get_platक्रमm_data(rmi_dev);
	काष्ठा rmi_driver_data *drv_data = dev_get_drvdata(&rmi_dev->dev);
	काष्ठा f30_data *f30;
	पूर्णांक error;

	अगर (pdata->gpio_data.disable)
		वापस 0;

	अगर (!drv_data->input) अणु
		dev_info(&fn->dev, "F30: no input device found, ignoring\n");
		वापस -ENXIO;
	पूर्ण

	f30 = devm_kzalloc(&fn->dev, माप(*f30), GFP_KERNEL);
	अगर (!f30)
		वापस -ENOMEM;

	f30->input = drv_data->input;

	error = rmi_f30_initialize(fn, f30);
	अगर (error)
		वापस error;

	dev_set_drvdata(&fn->dev, f30);
	वापस 0;
पूर्ण

काष्ठा rmi_function_handler rmi_f30_handler = अणु
	.driver = अणु
		.name = "rmi4_f30",
	पूर्ण,
	.func = 0x30,
	.probe = rmi_f30_probe,
	.config = rmi_f30_config,
	.attention = rmi_f30_attention,
पूर्ण;
