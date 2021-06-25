<शैली गुरु>
/*
 * Driver क्रम TCA8418 I2C keyboard
 *
 * Copyright (C) 2011 Fuel7, Inc.  All rights reserved.
 *
 * Author: Kyle Manna <kyle.manna@fuel7.com>
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public
 * License v2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public
 * License aदीर्घ with this program; अगर not, ग_लिखो to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 021110-1307, USA.
 *
 * If you can't comply with GPLv2, alternative licensing terms may be
 * arranged. Please contact Fuel7, Inc. (http://fuel7.com/) क्रम proprietary
 * alternative licensing inquiries.
 */

#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/input.h>
#समावेश <linux/input/matrix_keypad.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/property.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>

/* TCA8418 hardware limits */
#घोषणा TCA8418_MAX_ROWS	8
#घोषणा TCA8418_MAX_COLS	10

/* TCA8418 रेजिस्टर offsets */
#घोषणा REG_CFG			0x01
#घोषणा REG_INT_STAT		0x02
#घोषणा REG_KEY_LCK_EC		0x03
#घोषणा REG_KEY_EVENT_A		0x04
#घोषणा REG_KEY_EVENT_B		0x05
#घोषणा REG_KEY_EVENT_C		0x06
#घोषणा REG_KEY_EVENT_D		0x07
#घोषणा REG_KEY_EVENT_E		0x08
#घोषणा REG_KEY_EVENT_F		0x09
#घोषणा REG_KEY_EVENT_G		0x0A
#घोषणा REG_KEY_EVENT_H		0x0B
#घोषणा REG_KEY_EVENT_I		0x0C
#घोषणा REG_KEY_EVENT_J		0x0D
#घोषणा REG_KP_LCK_TIMER	0x0E
#घोषणा REG_UNLOCK1		0x0F
#घोषणा REG_UNLOCK2		0x10
#घोषणा REG_GPIO_INT_STAT1	0x11
#घोषणा REG_GPIO_INT_STAT2	0x12
#घोषणा REG_GPIO_INT_STAT3	0x13
#घोषणा REG_GPIO_DAT_STAT1	0x14
#घोषणा REG_GPIO_DAT_STAT2	0x15
#घोषणा REG_GPIO_DAT_STAT3	0x16
#घोषणा REG_GPIO_DAT_OUT1	0x17
#घोषणा REG_GPIO_DAT_OUT2	0x18
#घोषणा REG_GPIO_DAT_OUT3	0x19
#घोषणा REG_GPIO_INT_EN1	0x1A
#घोषणा REG_GPIO_INT_EN2	0x1B
#घोषणा REG_GPIO_INT_EN3	0x1C
#घोषणा REG_KP_GPIO1		0x1D
#घोषणा REG_KP_GPIO2		0x1E
#घोषणा REG_KP_GPIO3		0x1F
#घोषणा REG_GPI_EM1		0x20
#घोषणा REG_GPI_EM2		0x21
#घोषणा REG_GPI_EM3		0x22
#घोषणा REG_GPIO_सूची1		0x23
#घोषणा REG_GPIO_सूची2		0x24
#घोषणा REG_GPIO_सूची3		0x25
#घोषणा REG_GPIO_INT_LVL1	0x26
#घोषणा REG_GPIO_INT_LVL2	0x27
#घोषणा REG_GPIO_INT_LVL3	0x28
#घोषणा REG_DEBOUNCE_DIS1	0x29
#घोषणा REG_DEBOUNCE_DIS2	0x2A
#घोषणा REG_DEBOUNCE_DIS3	0x2B
#घोषणा REG_GPIO_PULL1		0x2C
#घोषणा REG_GPIO_PULL2		0x2D
#घोषणा REG_GPIO_PULL3		0x2E

/* TCA8418 bit definitions */
#घोषणा CFG_AI			BIT(7)
#घोषणा CFG_GPI_E_CFG		BIT(6)
#घोषणा CFG_OVR_FLOW_M		BIT(5)
#घोषणा CFG_INT_CFG		BIT(4)
#घोषणा CFG_OVR_FLOW_IEN	BIT(3)
#घोषणा CFG_K_LCK_IEN		BIT(2)
#घोषणा CFG_GPI_IEN		BIT(1)
#घोषणा CFG_KE_IEN		BIT(0)

#घोषणा INT_STAT_CAD_INT	BIT(4)
#घोषणा INT_STAT_OVR_FLOW_INT	BIT(3)
#घोषणा INT_STAT_K_LCK_INT	BIT(2)
#घोषणा INT_STAT_GPI_INT	BIT(1)
#घोषणा INT_STAT_K_INT		BIT(0)

/* TCA8418 रेजिस्टर masks */
#घोषणा KEY_LCK_EC_KEC		0x7
#घोषणा KEY_EVENT_CODE		0x7f
#घोषणा KEY_EVENT_VALUE		0x80

काष्ठा tca8418_keypad अणु
	काष्ठा i2c_client *client;
	काष्ठा input_dev *input;

	अचिन्हित पूर्णांक row_shअगरt;
पूर्ण;

/*
 * Write a byte to the TCA8418
 */
अटल पूर्णांक tca8418_ग_लिखो_byte(काष्ठा tca8418_keypad *keypad_data,
			      पूर्णांक reg, u8 val)
अणु
	पूर्णांक error;

	error = i2c_smbus_ग_लिखो_byte_data(keypad_data->client, reg, val);
	अगर (error < 0) अणु
		dev_err(&keypad_data->client->dev,
			"%s failed, reg: %d, val: %d, error: %d\n",
			__func__, reg, val, error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Read a byte from the TCA8418
 */
अटल पूर्णांक tca8418_पढ़ो_byte(काष्ठा tca8418_keypad *keypad_data,
			     पूर्णांक reg, u8 *val)
अणु
	पूर्णांक error;

	error = i2c_smbus_पढ़ो_byte_data(keypad_data->client, reg);
	अगर (error < 0) अणु
		dev_err(&keypad_data->client->dev,
				"%s failed, reg: %d, error: %d\n",
				__func__, reg, error);
		वापस error;
	पूर्ण

	*val = (u8)error;

	वापस 0;
पूर्ण

अटल व्योम tca8418_पढ़ो_keypad(काष्ठा tca8418_keypad *keypad_data)
अणु
	काष्ठा input_dev *input = keypad_data->input;
	अचिन्हित लघु *keymap = input->keycode;
	पूर्णांक error, col, row;
	u8 reg, state, code;

	करो अणु
		error = tca8418_पढ़ो_byte(keypad_data, REG_KEY_EVENT_A, &reg);
		अगर (error < 0) अणु
			dev_err(&keypad_data->client->dev,
				"unable to read REG_KEY_EVENT_A\n");
			अवरोध;
		पूर्ण

		/* Assume that key code 0 signअगरies empty FIFO */
		अगर (reg <= 0)
			अवरोध;

		state = reg & KEY_EVENT_VALUE;
		code  = reg & KEY_EVENT_CODE;

		row = code / TCA8418_MAX_COLS;
		col = code % TCA8418_MAX_COLS;

		row = (col) ? row : row - 1;
		col = (col) ? col - 1 : TCA8418_MAX_COLS - 1;

		code = MATRIX_SCAN_CODE(row, col, keypad_data->row_shअगरt);
		input_event(input, EV_MSC, MSC_SCAN, code);
		input_report_key(input, keymap[code], state);

	पूर्ण जबतक (1);

	input_sync(input);
पूर्ण

/*
 * Thपढ़ोed IRQ handler and this can (and will) sleep.
 */
अटल irqवापस_t tca8418_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा tca8418_keypad *keypad_data = dev_id;
	u8 reg;
	पूर्णांक error;

	error = tca8418_पढ़ो_byte(keypad_data, REG_INT_STAT, &reg);
	अगर (error) अणु
		dev_err(&keypad_data->client->dev,
			"unable to read REG_INT_STAT\n");
		वापस IRQ_NONE;
	पूर्ण

	अगर (!reg)
		वापस IRQ_NONE;

	अगर (reg & INT_STAT_OVR_FLOW_INT)
		dev_warn(&keypad_data->client->dev, "overflow occurred\n");

	अगर (reg & INT_STAT_K_INT)
		tca8418_पढ़ो_keypad(keypad_data);

	/* Clear all पूर्णांकerrupts, even IRQs we didn't check (GPI, CAD, LCK) */
	reg = 0xff;
	error = tca8418_ग_लिखो_byte(keypad_data, REG_INT_STAT, reg);
	अगर (error)
		dev_err(&keypad_data->client->dev,
			"unable to clear REG_INT_STAT\n");

	वापस IRQ_HANDLED;
पूर्ण

/*
 * Configure the TCA8418 क्रम keypad operation
 */
अटल पूर्णांक tca8418_configure(काष्ठा tca8418_keypad *keypad_data,
			     u32 rows, u32 cols)
अणु
	पूर्णांक reg, error = 0;

	/* Assemble a mask क्रम row and column रेजिस्टरs */
	reg  =  ~(~0 << rows);
	reg += (~(~0 << cols)) << 8;

	/* Set रेजिस्टरs to keypad mode */
	error |= tca8418_ग_लिखो_byte(keypad_data, REG_KP_GPIO1, reg);
	error |= tca8418_ग_लिखो_byte(keypad_data, REG_KP_GPIO2, reg >> 8);
	error |= tca8418_ग_लिखो_byte(keypad_data, REG_KP_GPIO3, reg >> 16);

	/* Enable column debouncing */
	error |= tca8418_ग_लिखो_byte(keypad_data, REG_DEBOUNCE_DIS1, reg);
	error |= tca8418_ग_लिखो_byte(keypad_data, REG_DEBOUNCE_DIS2, reg >> 8);
	error |= tca8418_ग_लिखो_byte(keypad_data, REG_DEBOUNCE_DIS3, reg >> 16);

	अगर (error)
		वापस error;

	error = tca8418_ग_लिखो_byte(keypad_data, REG_CFG,
				CFG_INT_CFG | CFG_OVR_FLOW_IEN | CFG_KE_IEN);

	वापस error;
पूर्ण

अटल पूर्णांक tca8418_keypad_probe(काष्ठा i2c_client *client,
				स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा tca8418_keypad *keypad_data;
	काष्ठा input_dev *input;
	u32 rows = 0, cols = 0;
	पूर्णांक error, row_shअगरt;
	u8 reg;

	/* Check i2c driver capabilities */
	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_BYTE)) अणु
		dev_err(dev, "%s adapter not supported\n",
			dev_driver_string(&client->adapter->dev));
		वापस -ENODEV;
	पूर्ण

	error = matrix_keypad_parse_properties(dev, &rows, &cols);
	अगर (error)
		वापस error;

	अगर (!rows || rows > TCA8418_MAX_ROWS) अणु
		dev_err(dev, "invalid rows\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!cols || cols > TCA8418_MAX_COLS) अणु
		dev_err(dev, "invalid columns\n");
		वापस -EINVAL;
	पूर्ण

	row_shअगरt = get_count_order(cols);

	/* Allocate memory क्रम keypad_data and input device */
	keypad_data = devm_kzalloc(dev, माप(*keypad_data), GFP_KERNEL);
	अगर (!keypad_data)
		वापस -ENOMEM;

	keypad_data->client = client;
	keypad_data->row_shअगरt = row_shअगरt;

	/* Read key lock रेजिस्टर, अगर this fails assume device not present */
	error = tca8418_पढ़ो_byte(keypad_data, REG_KEY_LCK_EC, &reg);
	अगर (error)
		वापस -ENODEV;

	/* Configure input device */
	input = devm_input_allocate_device(dev);
	अगर (!input)
		वापस -ENOMEM;

	keypad_data->input = input;

	input->name = client->name;
	input->id.bustype = BUS_I2C;
	input->id.venकरोr  = 0x0001;
	input->id.product = 0x001;
	input->id.version = 0x0001;

	error = matrix_keypad_build_keymap(शून्य, शून्य, rows, cols, शून्य, input);
	अगर (error) अणु
		dev_err(dev, "Failed to build keymap\n");
		वापस error;
	पूर्ण

	अगर (device_property_पढ़ो_bool(dev, "keypad,autorepeat"))
		__set_bit(EV_REP, input->evbit);

	input_set_capability(input, EV_MSC, MSC_SCAN);

	error = devm_request_thपढ़ोed_irq(dev, client->irq,
					  शून्य, tca8418_irq_handler,
					  IRQF_SHARED | IRQF_ONESHOT,
					  client->name, keypad_data);
	अगर (error) अणु
		dev_err(dev, "Unable to claim irq %d; error %d\n",
			client->irq, error);
		वापस error;
	पूर्ण

	/* Initialize the chip */
	error = tca8418_configure(keypad_data, rows, cols);
	अगर (error < 0)
		वापस error;

	error = input_रेजिस्टर_device(input);
	अगर (error) अणु
		dev_err(dev, "Unable to register input device, error: %d\n",
			error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id tca8418_id[] = अणु
	अणु "tca8418", 8418, पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, tca8418_id);

अटल स्थिर काष्ठा of_device_id tca8418_dt_ids[] = अणु
	अणु .compatible = "ti,tca8418", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, tca8418_dt_ids);

अटल काष्ठा i2c_driver tca8418_keypad_driver = अणु
	.driver = अणु
		.name	= "tca8418_keypad",
		.of_match_table = tca8418_dt_ids,
	पूर्ण,
	.probe		= tca8418_keypad_probe,
	.id_table	= tca8418_id,
पूर्ण;

अटल पूर्णांक __init tca8418_keypad_init(व्योम)
अणु
	वापस i2c_add_driver(&tca8418_keypad_driver);
पूर्ण
subsys_initcall(tca8418_keypad_init);

अटल व्योम __निकास tca8418_keypad_निकास(व्योम)
अणु
	i2c_del_driver(&tca8418_keypad_driver);
पूर्ण
module_निकास(tca8418_keypad_निकास);

MODULE_AUTHOR("Kyle Manna <kyle.manna@fuel7.com>");
MODULE_DESCRIPTION("Keypad driver for TCA8418");
MODULE_LICENSE("GPL");
