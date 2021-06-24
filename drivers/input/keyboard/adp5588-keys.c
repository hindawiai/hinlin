<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * File: drivers/input/keyboard/adp5588_keys.c
 * Description:  keypad driver क्रम ADP5588 and ADP5587
 *		 I2C QWERTY Keypad and IO Expander
 * Bugs: Enter bugs at http://blackfin.uclinux.org/
 *
 * Copyright (C) 2008-2010 Analog Devices Inc.
 */

#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/pm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/input.h>
#समावेश <linux/i2c.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/slab.h>

#समावेश <linux/platक्रमm_data/adp5588.h>

/* Key Event Register xy */
#घोषणा KEY_EV_PRESSED		(1 << 7)
#घोषणा KEY_EV_MASK		(0x7F)

#घोषणा KP_SEL(x)		(0xFFFF >> (16 - x))	/* 2^x-1 */

#घोषणा KEYP_MAX_EVENT		10

/*
 * Early pre 4.0 Silicon required to delay पढ़ोout by at least 25ms,
 * since the Event Counter Register updated 25ms after the पूर्णांकerrupt
 * निश्चितed.
 */
#घोषणा WA_DELAYED_READOUT_REVID(rev)		((rev) < 4)

काष्ठा adp5588_kpad अणु
	काष्ठा i2c_client *client;
	काष्ठा input_dev *input;
	काष्ठा delayed_work work;
	अचिन्हित दीर्घ delay;
	अचिन्हित लघु keycode[ADP5588_KEYMAPSIZE];
	स्थिर काष्ठा adp5588_gpi_map *gpimap;
	अचिन्हित लघु gpimapsize;
#अगर_घोषित CONFIG_GPIOLIB
	अचिन्हित अक्षर gpiomap[ADP5588_MAXGPIO];
	bool export_gpio;
	काष्ठा gpio_chip gc;
	काष्ठा mutex gpio_lock;	/* Protect cached dir, dat_out */
	u8 dat_out[3];
	u8 dir[3];
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक adp5588_पढ़ो(काष्ठा i2c_client *client, u8 reg)
अणु
	पूर्णांक ret = i2c_smbus_पढ़ो_byte_data(client, reg);

	अगर (ret < 0)
		dev_err(&client->dev, "Read Error\n");

	वापस ret;
पूर्ण

अटल पूर्णांक adp5588_ग_लिखो(काष्ठा i2c_client *client, u8 reg, u8 val)
अणु
	वापस i2c_smbus_ग_लिखो_byte_data(client, reg, val);
पूर्ण

#अगर_घोषित CONFIG_GPIOLIB
अटल पूर्णांक adp5588_gpio_get_value(काष्ठा gpio_chip *chip, अचिन्हित off)
अणु
	काष्ठा adp5588_kpad *kpad = gpiochip_get_data(chip);
	अचिन्हित पूर्णांक bank = ADP5588_BANK(kpad->gpiomap[off]);
	अचिन्हित पूर्णांक bit = ADP5588_BIT(kpad->gpiomap[off]);
	पूर्णांक val;

	mutex_lock(&kpad->gpio_lock);

	अगर (kpad->dir[bank] & bit)
		val = kpad->dat_out[bank];
	अन्यथा
		val = adp5588_पढ़ो(kpad->client, GPIO_DAT_STAT1 + bank);

	mutex_unlock(&kpad->gpio_lock);

	वापस !!(val & bit);
पूर्ण

अटल व्योम adp5588_gpio_set_value(काष्ठा gpio_chip *chip,
				   अचिन्हित off, पूर्णांक val)
अणु
	काष्ठा adp5588_kpad *kpad = gpiochip_get_data(chip);
	अचिन्हित पूर्णांक bank = ADP5588_BANK(kpad->gpiomap[off]);
	अचिन्हित पूर्णांक bit = ADP5588_BIT(kpad->gpiomap[off]);

	mutex_lock(&kpad->gpio_lock);

	अगर (val)
		kpad->dat_out[bank] |= bit;
	अन्यथा
		kpad->dat_out[bank] &= ~bit;

	adp5588_ग_लिखो(kpad->client, GPIO_DAT_OUT1 + bank,
			   kpad->dat_out[bank]);

	mutex_unlock(&kpad->gpio_lock);
पूर्ण

अटल पूर्णांक adp5588_gpio_direction_input(काष्ठा gpio_chip *chip, अचिन्हित off)
अणु
	काष्ठा adp5588_kpad *kpad = gpiochip_get_data(chip);
	अचिन्हित पूर्णांक bank = ADP5588_BANK(kpad->gpiomap[off]);
	अचिन्हित पूर्णांक bit = ADP5588_BIT(kpad->gpiomap[off]);
	पूर्णांक ret;

	mutex_lock(&kpad->gpio_lock);

	kpad->dir[bank] &= ~bit;
	ret = adp5588_ग_लिखो(kpad->client, GPIO_सूची1 + bank, kpad->dir[bank]);

	mutex_unlock(&kpad->gpio_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक adp5588_gpio_direction_output(काष्ठा gpio_chip *chip,
					 अचिन्हित off, पूर्णांक val)
अणु
	काष्ठा adp5588_kpad *kpad = gpiochip_get_data(chip);
	अचिन्हित पूर्णांक bank = ADP5588_BANK(kpad->gpiomap[off]);
	अचिन्हित पूर्णांक bit = ADP5588_BIT(kpad->gpiomap[off]);
	पूर्णांक ret;

	mutex_lock(&kpad->gpio_lock);

	kpad->dir[bank] |= bit;

	अगर (val)
		kpad->dat_out[bank] |= bit;
	अन्यथा
		kpad->dat_out[bank] &= ~bit;

	ret = adp5588_ग_लिखो(kpad->client, GPIO_DAT_OUT1 + bank,
				 kpad->dat_out[bank]);
	ret |= adp5588_ग_लिखो(kpad->client, GPIO_सूची1 + bank,
				 kpad->dir[bank]);

	mutex_unlock(&kpad->gpio_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक adp5588_build_gpiomap(काष्ठा adp5588_kpad *kpad,
				स्थिर काष्ठा adp5588_kpad_platक्रमm_data *pdata)
अणु
	bool pin_used[ADP5588_MAXGPIO];
	पूर्णांक n_unused = 0;
	पूर्णांक i;

	स_रखो(pin_used, 0, माप(pin_used));

	क्रम (i = 0; i < pdata->rows; i++)
		pin_used[i] = true;

	क्रम (i = 0; i < pdata->cols; i++)
		pin_used[i + GPI_PIN_COL_BASE - GPI_PIN_BASE] = true;

	क्रम (i = 0; i < kpad->gpimapsize; i++)
		pin_used[kpad->gpimap[i].pin - GPI_PIN_BASE] = true;

	क्रम (i = 0; i < ADP5588_MAXGPIO; i++)
		अगर (!pin_used[i])
			kpad->gpiomap[n_unused++] = i;

	वापस n_unused;
पूर्ण

अटल पूर्णांक adp5588_gpio_add(काष्ठा adp5588_kpad *kpad)
अणु
	काष्ठा device *dev = &kpad->client->dev;
	स्थिर काष्ठा adp5588_kpad_platक्रमm_data *pdata = dev_get_platdata(dev);
	स्थिर काष्ठा adp5588_gpio_platक्रमm_data *gpio_data = pdata->gpio_data;
	पूर्णांक i, error;

	अगर (!gpio_data)
		वापस 0;

	kpad->gc.ngpio = adp5588_build_gpiomap(kpad, pdata);
	अगर (kpad->gc.ngpio == 0) अणु
		dev_info(dev, "No unused gpios left to export\n");
		वापस 0;
	पूर्ण

	kpad->export_gpio = true;

	kpad->gc.direction_input = adp5588_gpio_direction_input;
	kpad->gc.direction_output = adp5588_gpio_direction_output;
	kpad->gc.get = adp5588_gpio_get_value;
	kpad->gc.set = adp5588_gpio_set_value;
	kpad->gc.can_sleep = 1;

	kpad->gc.base = gpio_data->gpio_start;
	kpad->gc.label = kpad->client->name;
	kpad->gc.owner = THIS_MODULE;
	kpad->gc.names = gpio_data->names;

	mutex_init(&kpad->gpio_lock);

	error = gpiochip_add_data(&kpad->gc, kpad);
	अगर (error) अणु
		dev_err(dev, "gpiochip_add failed, err: %d\n", error);
		वापस error;
	पूर्ण

	क्रम (i = 0; i <= ADP5588_BANK(ADP5588_MAXGPIO); i++) अणु
		kpad->dat_out[i] = adp5588_पढ़ो(kpad->client,
						GPIO_DAT_OUT1 + i);
		kpad->dir[i] = adp5588_पढ़ो(kpad->client, GPIO_सूची1 + i);
	पूर्ण

	अगर (gpio_data->setup) अणु
		error = gpio_data->setup(kpad->client,
					 kpad->gc.base, kpad->gc.ngpio,
					 gpio_data->context);
		अगर (error)
			dev_warn(dev, "setup failed, %d\n", error);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम adp5588_gpio_हटाओ(काष्ठा adp5588_kpad *kpad)
अणु
	काष्ठा device *dev = &kpad->client->dev;
	स्थिर काष्ठा adp5588_kpad_platक्रमm_data *pdata = dev_get_platdata(dev);
	स्थिर काष्ठा adp5588_gpio_platक्रमm_data *gpio_data = pdata->gpio_data;
	पूर्णांक error;

	अगर (!kpad->export_gpio)
		वापस;

	अगर (gpio_data->tearकरोwn) अणु
		error = gpio_data->tearकरोwn(kpad->client,
					    kpad->gc.base, kpad->gc.ngpio,
					    gpio_data->context);
		अगर (error)
			dev_warn(dev, "teardown failed %d\n", error);
	पूर्ण

	gpiochip_हटाओ(&kpad->gc);
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक adp5588_gpio_add(काष्ठा adp5588_kpad *kpad)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम adp5588_gpio_हटाओ(काष्ठा adp5588_kpad *kpad)
अणु
पूर्ण
#पूर्ण_अगर

अटल व्योम adp5588_report_events(काष्ठा adp5588_kpad *kpad, पूर्णांक ev_cnt)
अणु
	पूर्णांक i, j;

	क्रम (i = 0; i < ev_cnt; i++) अणु
		पूर्णांक key = adp5588_पढ़ो(kpad->client, Key_EVENTA + i);
		पूर्णांक key_val = key & KEY_EV_MASK;

		अगर (key_val >= GPI_PIN_BASE && key_val <= GPI_PIN_END) अणु
			क्रम (j = 0; j < kpad->gpimapsize; j++) अणु
				अगर (key_val == kpad->gpimap[j].pin) अणु
					input_report_चयन(kpad->input,
							kpad->gpimap[j].sw_evt,
							key & KEY_EV_PRESSED);
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			input_report_key(kpad->input,
					 kpad->keycode[key_val - 1],
					 key & KEY_EV_PRESSED);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम adp5588_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा adp5588_kpad *kpad = container_of(work,
						काष्ठा adp5588_kpad, work.work);
	काष्ठा i2c_client *client = kpad->client;
	पूर्णांक status, ev_cnt;

	status = adp5588_पढ़ो(client, INT_STAT);

	अगर (status & ADP5588_OVR_FLOW_INT)	/* Unlikely and should never happen */
		dev_err(&client->dev, "Event Overflow Error\n");

	अगर (status & ADP5588_KE_INT) अणु
		ev_cnt = adp5588_पढ़ो(client, KEY_LCK_EC_STAT) & ADP5588_KEC;
		अगर (ev_cnt) अणु
			adp5588_report_events(kpad, ev_cnt);
			input_sync(kpad->input);
		पूर्ण
	पूर्ण
	adp5588_ग_लिखो(client, INT_STAT, status); /* Status is W1C */
पूर्ण

अटल irqवापस_t adp5588_irq(पूर्णांक irq, व्योम *handle)
अणु
	काष्ठा adp5588_kpad *kpad = handle;

	/*
	 * use keventd context to पढ़ो the event fअगरo रेजिस्टरs
	 * Schedule पढ़ोout at least 25ms after notअगरication क्रम
	 * REVID < 4
	 */

	schedule_delayed_work(&kpad->work, kpad->delay);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक adp5588_setup(काष्ठा i2c_client *client)
अणु
	स्थिर काष्ठा adp5588_kpad_platक्रमm_data *pdata =
			dev_get_platdata(&client->dev);
	स्थिर काष्ठा adp5588_gpio_platक्रमm_data *gpio_data = pdata->gpio_data;
	पूर्णांक i, ret;
	अचिन्हित अक्षर evt_mode1 = 0, evt_mode2 = 0, evt_mode3 = 0;

	ret = adp5588_ग_लिखो(client, KP_GPIO1, KP_SEL(pdata->rows));
	ret |= adp5588_ग_लिखो(client, KP_GPIO2, KP_SEL(pdata->cols) & 0xFF);
	ret |= adp5588_ग_लिखो(client, KP_GPIO3, KP_SEL(pdata->cols) >> 8);

	अगर (pdata->en_keylock) अणु
		ret |= adp5588_ग_लिखो(client, UNLOCK1, pdata->unlock_key1);
		ret |= adp5588_ग_लिखो(client, UNLOCK2, pdata->unlock_key2);
		ret |= adp5588_ग_लिखो(client, KEY_LCK_EC_STAT, ADP5588_K_LCK_EN);
	पूर्ण

	क्रम (i = 0; i < KEYP_MAX_EVENT; i++)
		ret |= adp5588_पढ़ो(client, Key_EVENTA);

	क्रम (i = 0; i < pdata->gpimapsize; i++) अणु
		अचिन्हित लघु pin = pdata->gpimap[i].pin;

		अगर (pin <= GPI_PIN_ROW_END) अणु
			evt_mode1 |= (1 << (pin - GPI_PIN_ROW_BASE));
		पूर्ण अन्यथा अणु
			evt_mode2 |= ((1 << (pin - GPI_PIN_COL_BASE)) & 0xFF);
			evt_mode3 |= ((1 << (pin - GPI_PIN_COL_BASE)) >> 8);
		पूर्ण
	पूर्ण

	अगर (pdata->gpimapsize) अणु
		ret |= adp5588_ग_लिखो(client, GPI_EM1, evt_mode1);
		ret |= adp5588_ग_लिखो(client, GPI_EM2, evt_mode2);
		ret |= adp5588_ग_लिखो(client, GPI_EM3, evt_mode3);
	पूर्ण

	अगर (gpio_data) अणु
		क्रम (i = 0; i <= ADP5588_BANK(ADP5588_MAXGPIO); i++) अणु
			पूर्णांक pull_mask = gpio_data->pullup_dis_mask;

			ret |= adp5588_ग_लिखो(client, GPIO_PULL1 + i,
				(pull_mask >> (8 * i)) & 0xFF);
		पूर्ण
	पूर्ण

	ret |= adp5588_ग_लिखो(client, INT_STAT,
				ADP5588_CMP2_INT | ADP5588_CMP1_INT |
				ADP5588_OVR_FLOW_INT | ADP5588_K_LCK_INT |
				ADP5588_GPI_INT | ADP5588_KE_INT); /* Status is W1C */

	ret |= adp5588_ग_लिखो(client, CFG, ADP5588_INT_CFG |
					  ADP5588_OVR_FLOW_IEN |
					  ADP5588_KE_IEN);

	अगर (ret < 0) अणु
		dev_err(&client->dev, "Write Error\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम adp5588_report_चयन_state(काष्ठा adp5588_kpad *kpad)
अणु
	पूर्णांक gpi_stat1 = adp5588_पढ़ो(kpad->client, GPIO_DAT_STAT1);
	पूर्णांक gpi_stat2 = adp5588_पढ़ो(kpad->client, GPIO_DAT_STAT2);
	पूर्णांक gpi_stat3 = adp5588_पढ़ो(kpad->client, GPIO_DAT_STAT3);
	पूर्णांक gpi_stat_पंचांगp, pin_loc;
	पूर्णांक i;

	क्रम (i = 0; i < kpad->gpimapsize; i++) अणु
		अचिन्हित लघु pin = kpad->gpimap[i].pin;

		अगर (pin <= GPI_PIN_ROW_END) अणु
			gpi_stat_पंचांगp = gpi_stat1;
			pin_loc = pin - GPI_PIN_ROW_BASE;
		पूर्ण अन्यथा अगर ((pin - GPI_PIN_COL_BASE) < 8) अणु
			gpi_stat_पंचांगp = gpi_stat2;
			pin_loc = pin - GPI_PIN_COL_BASE;
		पूर्ण अन्यथा अणु
			gpi_stat_पंचांगp = gpi_stat3;
			pin_loc = pin - GPI_PIN_COL_BASE - 8;
		पूर्ण

		अगर (gpi_stat_पंचांगp < 0) अणु
			dev_err(&kpad->client->dev,
				"Can't read GPIO_DAT_STAT switch %d default to OFF\n",
				pin);
			gpi_stat_पंचांगp = 0;
		पूर्ण

		input_report_चयन(kpad->input,
				    kpad->gpimap[i].sw_evt,
				    !(gpi_stat_पंचांगp & (1 << pin_loc)));
	पूर्ण

	input_sync(kpad->input);
पूर्ण


अटल पूर्णांक adp5588_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा adp5588_kpad *kpad;
	स्थिर काष्ठा adp5588_kpad_platक्रमm_data *pdata =
			dev_get_platdata(&client->dev);
	काष्ठा input_dev *input;
	अचिन्हित पूर्णांक revid;
	पूर्णांक ret, i;
	पूर्णांक error;

	अगर (!i2c_check_functionality(client->adapter,
					I2C_FUNC_SMBUS_BYTE_DATA)) अणु
		dev_err(&client->dev, "SMBUS Byte Data not Supported\n");
		वापस -EIO;
	पूर्ण

	अगर (!pdata) अणु
		dev_err(&client->dev, "no platform data?\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!pdata->rows || !pdata->cols || !pdata->keymap) अणु
		dev_err(&client->dev, "no rows, cols or keymap from pdata\n");
		वापस -EINVAL;
	पूर्ण

	अगर (pdata->keymapsize != ADP5588_KEYMAPSIZE) अणु
		dev_err(&client->dev, "invalid keymapsize\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!pdata->gpimap && pdata->gpimapsize) अणु
		dev_err(&client->dev, "invalid gpimap from pdata\n");
		वापस -EINVAL;
	पूर्ण

	अगर (pdata->gpimapsize > ADP5588_GPIMAPSIZE_MAX) अणु
		dev_err(&client->dev, "invalid gpimapsize\n");
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < pdata->gpimapsize; i++) अणु
		अचिन्हित लघु pin = pdata->gpimap[i].pin;

		अगर (pin < GPI_PIN_BASE || pin > GPI_PIN_END) अणु
			dev_err(&client->dev, "invalid gpi pin data\n");
			वापस -EINVAL;
		पूर्ण

		अगर (pin <= GPI_PIN_ROW_END) अणु
			अगर (pin - GPI_PIN_ROW_BASE + 1 <= pdata->rows) अणु
				dev_err(&client->dev, "invalid gpi row data\n");
				वापस -EINVAL;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (pin - GPI_PIN_COL_BASE + 1 <= pdata->cols) अणु
				dev_err(&client->dev, "invalid gpi col data\n");
				वापस -EINVAL;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!client->irq) अणु
		dev_err(&client->dev, "no IRQ?\n");
		वापस -EINVAL;
	पूर्ण

	kpad = kzalloc(माप(*kpad), GFP_KERNEL);
	input = input_allocate_device();
	अगर (!kpad || !input) अणु
		error = -ENOMEM;
		जाओ err_मुक्त_mem;
	पूर्ण

	kpad->client = client;
	kpad->input = input;
	INIT_DELAYED_WORK(&kpad->work, adp5588_work);

	ret = adp5588_पढ़ो(client, DEV_ID);
	अगर (ret < 0) अणु
		error = ret;
		जाओ err_मुक्त_mem;
	पूर्ण

	revid = (u8) ret & ADP5588_DEVICE_ID_MASK;
	अगर (WA_DELAYED_READOUT_REVID(revid))
		kpad->delay = msecs_to_jअगरfies(30);

	input->name = client->name;
	input->phys = "adp5588-keys/input0";
	input->dev.parent = &client->dev;

	input_set_drvdata(input, kpad);

	input->id.bustype = BUS_I2C;
	input->id.venकरोr = 0x0001;
	input->id.product = 0x0001;
	input->id.version = revid;

	input->keycodesize = माप(kpad->keycode[0]);
	input->keycodemax = pdata->keymapsize;
	input->keycode = kpad->keycode;

	स_नकल(kpad->keycode, pdata->keymap,
		pdata->keymapsize * input->keycodesize);

	kpad->gpimap = pdata->gpimap;
	kpad->gpimapsize = pdata->gpimapsize;

	/* setup input device */
	__set_bit(EV_KEY, input->evbit);

	अगर (pdata->repeat)
		__set_bit(EV_REP, input->evbit);

	क्रम (i = 0; i < input->keycodemax; i++)
		अगर (kpad->keycode[i] <= KEY_MAX)
			__set_bit(kpad->keycode[i], input->keybit);
	__clear_bit(KEY_RESERVED, input->keybit);

	अगर (kpad->gpimapsize)
		__set_bit(EV_SW, input->evbit);
	क्रम (i = 0; i < kpad->gpimapsize; i++)
		__set_bit(kpad->gpimap[i].sw_evt, input->swbit);

	error = input_रेजिस्टर_device(input);
	अगर (error) अणु
		dev_err(&client->dev, "unable to register input device\n");
		जाओ err_मुक्त_mem;
	पूर्ण

	error = request_irq(client->irq, adp5588_irq,
			    IRQF_TRIGGER_FALLING,
			    client->dev.driver->name, kpad);
	अगर (error) अणु
		dev_err(&client->dev, "irq %d busy?\n", client->irq);
		जाओ err_unreg_dev;
	पूर्ण

	error = adp5588_setup(client);
	अगर (error)
		जाओ err_मुक्त_irq;

	अगर (kpad->gpimapsize)
		adp5588_report_चयन_state(kpad);

	error = adp5588_gpio_add(kpad);
	अगर (error)
		जाओ err_मुक्त_irq;

	device_init_wakeup(&client->dev, 1);
	i2c_set_clientdata(client, kpad);

	dev_info(&client->dev, "Rev.%d keypad, irq %d\n", revid, client->irq);
	वापस 0;

 err_मुक्त_irq:
	मुक्त_irq(client->irq, kpad);
	cancel_delayed_work_sync(&kpad->work);
 err_unreg_dev:
	input_unरेजिस्टर_device(input);
	input = शून्य;
 err_मुक्त_mem:
	input_मुक्त_device(input);
	kमुक्त(kpad);

	वापस error;
पूर्ण

अटल पूर्णांक adp5588_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा adp5588_kpad *kpad = i2c_get_clientdata(client);

	adp5588_ग_लिखो(client, CFG, 0);
	मुक्त_irq(client->irq, kpad);
	cancel_delayed_work_sync(&kpad->work);
	input_unरेजिस्टर_device(kpad->input);
	adp5588_gpio_हटाओ(kpad);
	kमुक्त(kpad);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक adp5588_suspend(काष्ठा device *dev)
अणु
	काष्ठा adp5588_kpad *kpad = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = kpad->client;

	disable_irq(client->irq);
	cancel_delayed_work_sync(&kpad->work);

	अगर (device_may_wakeup(&client->dev))
		enable_irq_wake(client->irq);

	वापस 0;
पूर्ण

अटल पूर्णांक adp5588_resume(काष्ठा device *dev)
अणु
	काष्ठा adp5588_kpad *kpad = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = kpad->client;

	अगर (device_may_wakeup(&client->dev))
		disable_irq_wake(client->irq);

	enable_irq(client->irq);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops adp5588_dev_pm_ops = अणु
	.suspend = adp5588_suspend,
	.resume  = adp5588_resume,
पूर्ण;
#पूर्ण_अगर

अटल स्थिर काष्ठा i2c_device_id adp5588_id[] = अणु
	अणु "adp5588-keys", 0 पूर्ण,
	अणु "adp5587-keys", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, adp5588_id);

अटल काष्ठा i2c_driver adp5588_driver = अणु
	.driver = अणु
		.name = KBUILD_MODNAME,
#अगर_घोषित CONFIG_PM
		.pm   = &adp5588_dev_pm_ops,
#पूर्ण_अगर
	पूर्ण,
	.probe    = adp5588_probe,
	.हटाओ   = adp5588_हटाओ,
	.id_table = adp5588_id,
पूर्ण;

module_i2c_driver(adp5588_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Michael Hennerich <hennerich@blackfin.uclinux.org>");
MODULE_DESCRIPTION("ADP5588/87 Keypad driver");
