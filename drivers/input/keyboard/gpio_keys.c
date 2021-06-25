<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम keys on GPIO lines capable of generating पूर्णांकerrupts.
 *
 * Copyright 2005 Phil Blundell
 * Copyright 2010, 2011 David Jander <david@protonic.nl>
 */

#समावेश <linux/module.h>

#समावेश <linux/hrसमयr.h>
#समावेश <linux/init.h>
#समावेश <linux/fs.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/sched.h>
#समावेश <linux/pm.h>
#समावेश <linux/slab.h>
#समावेश <linux/sysctl.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/delay.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/input.h>
#समावेश <linux/gpio_keys.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/of.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/spinlock.h>
#समावेश <dt-bindings/input/gpio-keys.h>

काष्ठा gpio_button_data अणु
	स्थिर काष्ठा gpio_keys_button *button;
	काष्ठा input_dev *input;
	काष्ठा gpio_desc *gpiod;

	अचिन्हित लघु *code;

	काष्ठा hrसमयr release_समयr;
	अचिन्हित पूर्णांक release_delay;	/* in msecs, क्रम IRQ-only buttons */

	काष्ठा delayed_work work;
	काष्ठा hrसमयr debounce_समयr;
	अचिन्हित पूर्णांक software_debounce;	/* in msecs, क्रम GPIO-driven buttons */

	अचिन्हित पूर्णांक irq;
	अचिन्हित पूर्णांक wakeup_trigger_type;
	spinlock_t lock;
	bool disabled;
	bool key_pressed;
	bool suspended;
	bool debounce_use_hrसमयr;
पूर्ण;

काष्ठा gpio_keys_drvdata अणु
	स्थिर काष्ठा gpio_keys_platक्रमm_data *pdata;
	काष्ठा input_dev *input;
	काष्ठा mutex disable_lock;
	अचिन्हित लघु *keymap;
	काष्ठा gpio_button_data data[];
पूर्ण;

/*
 * SYSFS पूर्णांकerface क्रम enabling/disabling keys and चयनes:
 *
 * There are 4 attributes under /sys/devices/platक्रमm/gpio-keys/
 *	keys [ro]              - biपंचांगap of keys (EV_KEY) which can be
 *	                         disabled
 *	चयनes [ro]          - biपंचांगap of चयनes (EV_SW) which can be
 *	                         disabled
 *	disabled_keys [rw]     - biपंचांगap of keys currently disabled
 *	disabled_चयनes [rw] - biपंचांगap of चयनes currently disabled
 *
 * Userland can change these values and hence disable event generation
 * क्रम each key (or चयन). Disabling a key means its पूर्णांकerrupt line
 * is disabled.
 *
 * For example, अगर we have following चयनes set up as gpio-keys:
 *	SW_DOCK = 5
 *	SW_CAMERA_LENS_COVER = 9
 *	SW_KEYPAD_SLIDE = 10
 *	SW_FRONT_PROXIMITY = 11
 * This is पढ़ो from चयनes:
 *	11-9,5
 * Next we want to disable proximity (11) and करोck (5), we ग_लिखो:
 *	11,5
 * to file disabled_चयनes. Now proximity and करोck IRQs are disabled.
 * This can be verअगरied by पढ़ोing the file disabled_चयनes:
 *	11,5
 * If we now want to enable proximity (11) चयन we ग_लिखो:
 *	5
 * to disabled_चयनes.
 *
 * We can disable only those keys which करोn't allow sharing the irq.
 */

/**
 * get_n_events_by_type() - वापसs maximum number of events per @type
 * @type: type of button (%EV_KEY, %EV_SW)
 *
 * Return value of this function can be used to allocate biपंचांगap
 * large enough to hold all bits क्रम given type.
 */
अटल पूर्णांक get_n_events_by_type(पूर्णांक type)
अणु
	BUG_ON(type != EV_SW && type != EV_KEY);

	वापस (type == EV_KEY) ? KEY_CNT : SW_CNT;
पूर्ण

/**
 * get_bm_events_by_type() - वापसs biपंचांगap of supported events per @type
 * @dev: input device from which biपंचांगap is retrieved
 * @type: type of button (%EV_KEY, %EV_SW)
 *
 * Return value of this function can be used to allocate biपंचांगap
 * large enough to hold all bits क्रम given type.
 */
अटल स्थिर अचिन्हित दीर्घ *get_bm_events_by_type(काष्ठा input_dev *dev,
						  पूर्णांक type)
अणु
	BUG_ON(type != EV_SW && type != EV_KEY);

	वापस (type == EV_KEY) ? dev->keybit : dev->swbit;
पूर्ण

अटल व्योम gpio_keys_quiesce_key(व्योम *data)
अणु
	काष्ठा gpio_button_data *bdata = data;

	अगर (!bdata->gpiod)
		hrसमयr_cancel(&bdata->release_समयr);
	अगर (bdata->debounce_use_hrसमयr)
		hrसमयr_cancel(&bdata->debounce_समयr);
	अन्यथा
		cancel_delayed_work_sync(&bdata->work);
पूर्ण

/**
 * gpio_keys_disable_button() - disables given GPIO button
 * @bdata: button data क्रम button to be disabled
 *
 * Disables button poपूर्णांकed by @bdata. This is करोne by masking
 * IRQ line. After this function is called, button won't generate
 * input events anymore. Note that one can only disable buttons
 * that करोn't share IRQs.
 *
 * Make sure that @bdata->disable_lock is locked when entering
 * this function to aव्योम races when concurrent thपढ़ोs are
 * disabling buttons at the same समय.
 */
अटल व्योम gpio_keys_disable_button(काष्ठा gpio_button_data *bdata)
अणु
	अगर (!bdata->disabled) अणु
		/*
		 * Disable IRQ and associated समयr/work काष्ठाure.
		 */
		disable_irq(bdata->irq);
		gpio_keys_quiesce_key(bdata);
		bdata->disabled = true;
	पूर्ण
पूर्ण

/**
 * gpio_keys_enable_button() - enables given GPIO button
 * @bdata: button data क्रम button to be disabled
 *
 * Enables given button poपूर्णांकed by @bdata.
 *
 * Make sure that @bdata->disable_lock is locked when entering
 * this function to aव्योम races with concurrent thपढ़ोs trying
 * to enable the same button at the same समय.
 */
अटल व्योम gpio_keys_enable_button(काष्ठा gpio_button_data *bdata)
अणु
	अगर (bdata->disabled) अणु
		enable_irq(bdata->irq);
		bdata->disabled = false;
	पूर्ण
पूर्ण

/**
 * gpio_keys_attr_show_helper() - fill in stringअगरied biपंचांगap of buttons
 * @ddata: poपूर्णांकer to drvdata
 * @buf: buffer where stringअगरied biपंचांगap is written
 * @type: button type (%EV_KEY, %EV_SW)
 * @only_disabled: करोes caller want only those buttons that are
 *                 currently disabled or all buttons that can be
 *                 disabled
 *
 * This function ग_लिखोs buttons that can be disabled to @buf. If
 * @only_disabled is true, then @buf contains only those buttons
 * that are currently disabled. Returns 0 on success or negative
 * त्रुटि_सं on failure.
 */
अटल sमाप_प्रकार gpio_keys_attr_show_helper(काष्ठा gpio_keys_drvdata *ddata,
					  अक्षर *buf, अचिन्हित पूर्णांक type,
					  bool only_disabled)
अणु
	पूर्णांक n_events = get_n_events_by_type(type);
	अचिन्हित दीर्घ *bits;
	sमाप_प्रकार ret;
	पूर्णांक i;

	bits = biपंचांगap_zalloc(n_events, GFP_KERNEL);
	अगर (!bits)
		वापस -ENOMEM;

	क्रम (i = 0; i < ddata->pdata->nbuttons; i++) अणु
		काष्ठा gpio_button_data *bdata = &ddata->data[i];

		अगर (bdata->button->type != type)
			जारी;

		अगर (only_disabled && !bdata->disabled)
			जारी;

		__set_bit(*bdata->code, bits);
	पूर्ण

	ret = scnम_लिखो(buf, PAGE_SIZE - 1, "%*pbl", n_events, bits);
	buf[ret++] = '\n';
	buf[ret] = '\0';

	biपंचांगap_मुक्त(bits);

	वापस ret;
पूर्ण

/**
 * gpio_keys_attr_store_helper() - enable/disable buttons based on given biपंचांगap
 * @ddata: poपूर्णांकer to drvdata
 * @buf: buffer from userspace that contains stringअगरied biपंचांगap
 * @type: button type (%EV_KEY, %EV_SW)
 *
 * This function parses stringअगरied biपंचांगap from @buf and disables/enables
 * GPIO buttons accordingly. Returns 0 on success and negative error
 * on failure.
 */
अटल sमाप_प्रकार gpio_keys_attr_store_helper(काष्ठा gpio_keys_drvdata *ddata,
					   स्थिर अक्षर *buf, अचिन्हित पूर्णांक type)
अणु
	पूर्णांक n_events = get_n_events_by_type(type);
	स्थिर अचिन्हित दीर्घ *biपंचांगap = get_bm_events_by_type(ddata->input, type);
	अचिन्हित दीर्घ *bits;
	sमाप_प्रकार error;
	पूर्णांक i;

	bits = biपंचांगap_zalloc(n_events, GFP_KERNEL);
	अगर (!bits)
		वापस -ENOMEM;

	error = biपंचांगap_parselist(buf, bits, n_events);
	अगर (error)
		जाओ out;

	/* First validate */
	अगर (!biपंचांगap_subset(bits, biपंचांगap, n_events)) अणु
		error = -EINVAL;
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < ddata->pdata->nbuttons; i++) अणु
		काष्ठा gpio_button_data *bdata = &ddata->data[i];

		अगर (bdata->button->type != type)
			जारी;

		अगर (test_bit(*bdata->code, bits) &&
		    !bdata->button->can_disable) अणु
			error = -EINVAL;
			जाओ out;
		पूर्ण
	पूर्ण

	mutex_lock(&ddata->disable_lock);

	क्रम (i = 0; i < ddata->pdata->nbuttons; i++) अणु
		काष्ठा gpio_button_data *bdata = &ddata->data[i];

		अगर (bdata->button->type != type)
			जारी;

		अगर (test_bit(*bdata->code, bits))
			gpio_keys_disable_button(bdata);
		अन्यथा
			gpio_keys_enable_button(bdata);
	पूर्ण

	mutex_unlock(&ddata->disable_lock);

out:
	biपंचांगap_मुक्त(bits);
	वापस error;
पूर्ण

#घोषणा ATTR_SHOW_FN(name, type, only_disabled)				\
अटल sमाप_प्रकार gpio_keys_show_##name(काष्ठा device *dev,		\
				     काष्ठा device_attribute *attr,	\
				     अक्षर *buf)				\
अणु									\
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);		\
	काष्ठा gpio_keys_drvdata *ddata = platक्रमm_get_drvdata(pdev);	\
									\
	वापस gpio_keys_attr_show_helper(ddata, buf,			\
					  type, only_disabled);		\
पूर्ण

ATTR_SHOW_FN(keys, EV_KEY, false);
ATTR_SHOW_FN(चयनes, EV_SW, false);
ATTR_SHOW_FN(disabled_keys, EV_KEY, true);
ATTR_SHOW_FN(disabled_चयनes, EV_SW, true);

/*
 * ATTRIBUTES:
 *
 * /sys/devices/platक्रमm/gpio-keys/keys [ro]
 * /sys/devices/platक्रमm/gpio-keys/चयनes [ro]
 */
अटल DEVICE_ATTR(keys, S_IRUGO, gpio_keys_show_keys, शून्य);
अटल DEVICE_ATTR(चयनes, S_IRUGO, gpio_keys_show_चयनes, शून्य);

#घोषणा ATTR_STORE_FN(name, type)					\
अटल sमाप_प्रकार gpio_keys_store_##name(काष्ठा device *dev,		\
				      काष्ठा device_attribute *attr,	\
				      स्थिर अक्षर *buf,			\
				      माप_प्रकार count)			\
अणु									\
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);		\
	काष्ठा gpio_keys_drvdata *ddata = platक्रमm_get_drvdata(pdev);	\
	sमाप_प्रकार error;							\
									\
	error = gpio_keys_attr_store_helper(ddata, buf, type);		\
	अगर (error)							\
		वापस error;						\
									\
	वापस count;							\
पूर्ण

ATTR_STORE_FN(disabled_keys, EV_KEY);
ATTR_STORE_FN(disabled_चयनes, EV_SW);

/*
 * ATTRIBUTES:
 *
 * /sys/devices/platक्रमm/gpio-keys/disabled_keys [rw]
 * /sys/devices/platक्रमm/gpio-keys/disables_चयनes [rw]
 */
अटल DEVICE_ATTR(disabled_keys, S_IWUSR | S_IRUGO,
		   gpio_keys_show_disabled_keys,
		   gpio_keys_store_disabled_keys);
अटल DEVICE_ATTR(disabled_चयनes, S_IWUSR | S_IRUGO,
		   gpio_keys_show_disabled_चयनes,
		   gpio_keys_store_disabled_चयनes);

अटल काष्ठा attribute *gpio_keys_attrs[] = अणु
	&dev_attr_keys.attr,
	&dev_attr_चयनes.attr,
	&dev_attr_disabled_keys.attr,
	&dev_attr_disabled_चयनes.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(gpio_keys);

अटल व्योम gpio_keys_gpio_report_event(काष्ठा gpio_button_data *bdata)
अणु
	स्थिर काष्ठा gpio_keys_button *button = bdata->button;
	काष्ठा input_dev *input = bdata->input;
	अचिन्हित पूर्णांक type = button->type ?: EV_KEY;
	पूर्णांक state;

	state = bdata->debounce_use_hrसमयr ?
			gpiod_get_value(bdata->gpiod) :
			gpiod_get_value_cansleep(bdata->gpiod);
	अगर (state < 0) अणु
		dev_err(input->dev.parent,
			"failed to get gpio state: %d\n", state);
		वापस;
	पूर्ण

	अगर (type == EV_ABS) अणु
		अगर (state)
			input_event(input, type, button->code, button->value);
	पूर्ण अन्यथा अणु
		input_event(input, type, *bdata->code, state);
	पूर्ण
पूर्ण

अटल व्योम gpio_keys_debounce_event(काष्ठा gpio_button_data *bdata)
अणु
	gpio_keys_gpio_report_event(bdata);
	input_sync(bdata->input);

	अगर (bdata->button->wakeup)
		pm_relax(bdata->input->dev.parent);
पूर्ण

अटल व्योम gpio_keys_gpio_work_func(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा gpio_button_data *bdata =
		container_of(work, काष्ठा gpio_button_data, work.work);

	gpio_keys_debounce_event(bdata);
पूर्ण

अटल क्रमागत hrसमयr_restart gpio_keys_debounce_समयr(काष्ठा hrसमयr *t)
अणु
	काष्ठा gpio_button_data *bdata =
		container_of(t, काष्ठा gpio_button_data, debounce_समयr);

	gpio_keys_debounce_event(bdata);

	वापस HRTIMER_NORESTART;
पूर्ण

अटल irqवापस_t gpio_keys_gpio_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा gpio_button_data *bdata = dev_id;

	BUG_ON(irq != bdata->irq);

	अगर (bdata->button->wakeup) अणु
		स्थिर काष्ठा gpio_keys_button *button = bdata->button;

		pm_stay_awake(bdata->input->dev.parent);
		अगर (bdata->suspended  &&
		    (button->type == 0 || button->type == EV_KEY)) अणु
			/*
			 * Simulate wakeup key press in हाल the key has
			 * alपढ़ोy released by the समय we got पूर्णांकerrupt
			 * handler to run.
			 */
			input_report_key(bdata->input, button->code, 1);
		पूर्ण
	पूर्ण

	अगर (bdata->debounce_use_hrसमयr) अणु
		hrसमयr_start(&bdata->debounce_समयr,
			      ms_to_kसमय(bdata->software_debounce),
			      HRTIMER_MODE_REL);
	पूर्ण अन्यथा अणु
		mod_delayed_work(प्रणाली_wq,
				 &bdata->work,
				 msecs_to_jअगरfies(bdata->software_debounce));
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल क्रमागत hrसमयr_restart gpio_keys_irq_समयr(काष्ठा hrसमयr *t)
अणु
	काष्ठा gpio_button_data *bdata = container_of(t,
						      काष्ठा gpio_button_data,
						      release_समयr);
	काष्ठा input_dev *input = bdata->input;

	अगर (bdata->key_pressed) अणु
		input_event(input, EV_KEY, *bdata->code, 0);
		input_sync(input);
		bdata->key_pressed = false;
	पूर्ण

	वापस HRTIMER_NORESTART;
पूर्ण

अटल irqवापस_t gpio_keys_irq_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा gpio_button_data *bdata = dev_id;
	काष्ठा input_dev *input = bdata->input;
	अचिन्हित दीर्घ flags;

	BUG_ON(irq != bdata->irq);

	spin_lock_irqsave(&bdata->lock, flags);

	अगर (!bdata->key_pressed) अणु
		अगर (bdata->button->wakeup)
			pm_wakeup_event(bdata->input->dev.parent, 0);

		input_event(input, EV_KEY, *bdata->code, 1);
		input_sync(input);

		अगर (!bdata->release_delay) अणु
			input_event(input, EV_KEY, *bdata->code, 0);
			input_sync(input);
			जाओ out;
		पूर्ण

		bdata->key_pressed = true;
	पूर्ण

	अगर (bdata->release_delay)
		hrसमयr_start(&bdata->release_समयr,
			      ms_to_kसमय(bdata->release_delay),
			      HRTIMER_MODE_REL_HARD);
out:
	spin_unlock_irqrestore(&bdata->lock, flags);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक gpio_keys_setup_key(काष्ठा platक्रमm_device *pdev,
				काष्ठा input_dev *input,
				काष्ठा gpio_keys_drvdata *ddata,
				स्थिर काष्ठा gpio_keys_button *button,
				पूर्णांक idx,
				काष्ठा fwnode_handle *child)
अणु
	स्थिर अक्षर *desc = button->desc ? button->desc : "gpio_keys";
	काष्ठा device *dev = &pdev->dev;
	काष्ठा gpio_button_data *bdata = &ddata->data[idx];
	irq_handler_t isr;
	अचिन्हित दीर्घ irqflags;
	पूर्णांक irq;
	पूर्णांक error;

	bdata->input = input;
	bdata->button = button;
	spin_lock_init(&bdata->lock);

	अगर (child) अणु
		bdata->gpiod = devm_fwnode_gpiod_get(dev, child,
						     शून्य, GPIOD_IN, desc);
		अगर (IS_ERR(bdata->gpiod)) अणु
			error = PTR_ERR(bdata->gpiod);
			अगर (error == -ENOENT) अणु
				/*
				 * GPIO is optional, we may be dealing with
				 * purely पूर्णांकerrupt-driven setup.
				 */
				bdata->gpiod = शून्य;
			पूर्ण अन्यथा अणु
				अगर (error != -EPROBE_DEFER)
					dev_err(dev, "failed to get gpio: %d\n",
						error);
				वापस error;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (gpio_is_valid(button->gpio)) अणु
		/*
		 * Legacy GPIO number, so request the GPIO here and
		 * convert it to descriptor.
		 */
		अचिन्हित flags = GPIOF_IN;

		अगर (button->active_low)
			flags |= GPIOF_ACTIVE_LOW;

		error = devm_gpio_request_one(dev, button->gpio, flags, desc);
		अगर (error < 0) अणु
			dev_err(dev, "Failed to request GPIO %d, error %d\n",
				button->gpio, error);
			वापस error;
		पूर्ण

		bdata->gpiod = gpio_to_desc(button->gpio);
		अगर (!bdata->gpiod)
			वापस -EINVAL;
	पूर्ण

	अगर (bdata->gpiod) अणु
		bool active_low = gpiod_is_active_low(bdata->gpiod);

		अगर (button->debounce_पूर्णांकerval) अणु
			error = gpiod_set_debounce(bdata->gpiod,
					button->debounce_पूर्णांकerval * 1000);
			/* use समयr अगर gpiolib करोesn't provide debounce */
			अगर (error < 0)
				bdata->software_debounce =
						button->debounce_पूर्णांकerval;

			/*
			 * If पढ़ोing the GPIO won't sleep, we can use a
			 * hrसमयr instead of a standard समयr क्रम the software
			 * debounce, to reduce the latency as much as possible.
			 */
			bdata->debounce_use_hrसमयr =
					!gpiod_cansleep(bdata->gpiod);
		पूर्ण

		अगर (button->irq) अणु
			bdata->irq = button->irq;
		पूर्ण अन्यथा अणु
			irq = gpiod_to_irq(bdata->gpiod);
			अगर (irq < 0) अणु
				error = irq;
				dev_err(dev,
					"Unable to get irq number for GPIO %d, error %d\n",
					button->gpio, error);
				वापस error;
			पूर्ण
			bdata->irq = irq;
		पूर्ण

		INIT_DELAYED_WORK(&bdata->work, gpio_keys_gpio_work_func);

		hrसमयr_init(&bdata->debounce_समयr,
			     CLOCK_REALTIME, HRTIMER_MODE_REL);
		bdata->debounce_समयr.function = gpio_keys_debounce_समयr;

		isr = gpio_keys_gpio_isr;
		irqflags = IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING;

		चयन (button->wakeup_event_action) अणु
		हाल EV_ACT_ASSERTED:
			bdata->wakeup_trigger_type = active_low ?
				IRQ_TYPE_EDGE_FALLING : IRQ_TYPE_EDGE_RISING;
			अवरोध;
		हाल EV_ACT_DEASSERTED:
			bdata->wakeup_trigger_type = active_low ?
				IRQ_TYPE_EDGE_RISING : IRQ_TYPE_EDGE_FALLING;
			अवरोध;
		हाल EV_ACT_ANY:
		शेष:
			/*
			 * For other हालs, we are OK letting suspend/resume
			 * not reconfigure the trigger type.
			 */
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!button->irq) अणु
			dev_err(dev, "Found button without gpio or irq\n");
			वापस -EINVAL;
		पूर्ण

		bdata->irq = button->irq;

		अगर (button->type && button->type != EV_KEY) अणु
			dev_err(dev, "Only EV_KEY allowed for IRQ buttons.\n");
			वापस -EINVAL;
		पूर्ण

		bdata->release_delay = button->debounce_पूर्णांकerval;
		hrसमयr_init(&bdata->release_समयr,
			     CLOCK_REALTIME, HRTIMER_MODE_REL_HARD);
		bdata->release_समयr.function = gpio_keys_irq_समयr;

		isr = gpio_keys_irq_isr;
		irqflags = 0;

		/*
		 * For IRQ buttons, there is no पूर्णांकerrupt क्रम release.
		 * So we करोn't need to reconfigure the trigger type क्रम wakeup.
		 */
	पूर्ण

	bdata->code = &ddata->keymap[idx];
	*bdata->code = button->code;
	input_set_capability(input, button->type ?: EV_KEY, *bdata->code);

	/*
	 * Install custom action to cancel release समयr and
	 * workqueue item.
	 */
	error = devm_add_action(dev, gpio_keys_quiesce_key, bdata);
	अगर (error) अणु
		dev_err(dev, "failed to register quiesce action, error: %d\n",
			error);
		वापस error;
	पूर्ण

	/*
	 * If platक्रमm has specअगरied that the button can be disabled,
	 * we करोn't want it to share the पूर्णांकerrupt line.
	 */
	अगर (!button->can_disable)
		irqflags |= IRQF_SHARED;

	error = devm_request_any_context_irq(dev, bdata->irq, isr, irqflags,
					     desc, bdata);
	अगर (error < 0) अणु
		dev_err(dev, "Unable to claim irq %d; error %d\n",
			bdata->irq, error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम gpio_keys_report_state(काष्ठा gpio_keys_drvdata *ddata)
अणु
	काष्ठा input_dev *input = ddata->input;
	पूर्णांक i;

	क्रम (i = 0; i < ddata->pdata->nbuttons; i++) अणु
		काष्ठा gpio_button_data *bdata = &ddata->data[i];
		अगर (bdata->gpiod)
			gpio_keys_gpio_report_event(bdata);
	पूर्ण
	input_sync(input);
पूर्ण

अटल पूर्णांक gpio_keys_खोलो(काष्ठा input_dev *input)
अणु
	काष्ठा gpio_keys_drvdata *ddata = input_get_drvdata(input);
	स्थिर काष्ठा gpio_keys_platक्रमm_data *pdata = ddata->pdata;
	पूर्णांक error;

	अगर (pdata->enable) अणु
		error = pdata->enable(input->dev.parent);
		अगर (error)
			वापस error;
	पूर्ण

	/* Report current state of buttons that are connected to GPIOs */
	gpio_keys_report_state(ddata);

	वापस 0;
पूर्ण

अटल व्योम gpio_keys_बंद(काष्ठा input_dev *input)
अणु
	काष्ठा gpio_keys_drvdata *ddata = input_get_drvdata(input);
	स्थिर काष्ठा gpio_keys_platक्रमm_data *pdata = ddata->pdata;

	अगर (pdata->disable)
		pdata->disable(input->dev.parent);
पूर्ण

/*
 * Handlers क्रम alternative sources of platक्रमm_data
 */

/*
 * Translate properties पूर्णांकo platक्रमm_data
 */
अटल काष्ठा gpio_keys_platक्रमm_data *
gpio_keys_get_devtree_pdata(काष्ठा device *dev)
अणु
	काष्ठा gpio_keys_platक्रमm_data *pdata;
	काष्ठा gpio_keys_button *button;
	काष्ठा fwnode_handle *child;
	पूर्णांक nbuttons;

	nbuttons = device_get_child_node_count(dev);
	अगर (nbuttons == 0)
		वापस ERR_PTR(-ENODEV);

	pdata = devm_kzalloc(dev,
			     माप(*pdata) + nbuttons * माप(*button),
			     GFP_KERNEL);
	अगर (!pdata)
		वापस ERR_PTR(-ENOMEM);

	button = (काष्ठा gpio_keys_button *)(pdata + 1);

	pdata->buttons = button;
	pdata->nbuttons = nbuttons;

	pdata->rep = device_property_पढ़ो_bool(dev, "autorepeat");

	device_property_पढ़ो_string(dev, "label", &pdata->name);

	device_क्रम_each_child_node(dev, child) अणु
		अगर (is_of_node(child))
			button->irq =
				irq_of_parse_and_map(to_of_node(child), 0);

		अगर (fwnode_property_पढ़ो_u32(child, "linux,code",
					     &button->code)) अणु
			dev_err(dev, "Button without keycode\n");
			fwnode_handle_put(child);
			वापस ERR_PTR(-EINVAL);
		पूर्ण

		fwnode_property_पढ़ो_string(child, "label", &button->desc);

		अगर (fwnode_property_पढ़ो_u32(child, "linux,input-type",
					     &button->type))
			button->type = EV_KEY;

		button->wakeup =
			fwnode_property_पढ़ो_bool(child, "wakeup-source") ||
			/* legacy name */
			fwnode_property_पढ़ो_bool(child, "gpio-key,wakeup");

		fwnode_property_पढ़ो_u32(child, "wakeup-event-action",
					 &button->wakeup_event_action);

		button->can_disable =
			fwnode_property_पढ़ो_bool(child, "linux,can-disable");

		अगर (fwnode_property_पढ़ो_u32(child, "debounce-interval",
					 &button->debounce_पूर्णांकerval))
			button->debounce_पूर्णांकerval = 5;

		button++;
	पूर्ण

	वापस pdata;
पूर्ण

अटल स्थिर काष्ठा of_device_id gpio_keys_of_match[] = अणु
	अणु .compatible = "gpio-keys", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, gpio_keys_of_match);

अटल पूर्णांक gpio_keys_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	स्थिर काष्ठा gpio_keys_platक्रमm_data *pdata = dev_get_platdata(dev);
	काष्ठा fwnode_handle *child = शून्य;
	काष्ठा gpio_keys_drvdata *ddata;
	काष्ठा input_dev *input;
	पूर्णांक i, error;
	पूर्णांक wakeup = 0;

	अगर (!pdata) अणु
		pdata = gpio_keys_get_devtree_pdata(dev);
		अगर (IS_ERR(pdata))
			वापस PTR_ERR(pdata);
	पूर्ण

	ddata = devm_kzalloc(dev, काष्ठा_size(ddata, data, pdata->nbuttons),
			     GFP_KERNEL);
	अगर (!ddata) अणु
		dev_err(dev, "failed to allocate state\n");
		वापस -ENOMEM;
	पूर्ण

	ddata->keymap = devm_kसुस्मृति(dev,
				     pdata->nbuttons, माप(ddata->keymap[0]),
				     GFP_KERNEL);
	अगर (!ddata->keymap)
		वापस -ENOMEM;

	input = devm_input_allocate_device(dev);
	अगर (!input) अणु
		dev_err(dev, "failed to allocate input device\n");
		वापस -ENOMEM;
	पूर्ण

	ddata->pdata = pdata;
	ddata->input = input;
	mutex_init(&ddata->disable_lock);

	platक्रमm_set_drvdata(pdev, ddata);
	input_set_drvdata(input, ddata);

	input->name = pdata->name ? : pdev->name;
	input->phys = "gpio-keys/input0";
	input->dev.parent = dev;
	input->खोलो = gpio_keys_खोलो;
	input->बंद = gpio_keys_बंद;

	input->id.bustype = BUS_HOST;
	input->id.venकरोr = 0x0001;
	input->id.product = 0x0001;
	input->id.version = 0x0100;

	input->keycode = ddata->keymap;
	input->keycodesize = माप(ddata->keymap[0]);
	input->keycodemax = pdata->nbuttons;

	/* Enable स्वतः repeat feature of Linux input subप्रणाली */
	अगर (pdata->rep)
		__set_bit(EV_REP, input->evbit);

	क्रम (i = 0; i < pdata->nbuttons; i++) अणु
		स्थिर काष्ठा gpio_keys_button *button = &pdata->buttons[i];

		अगर (!dev_get_platdata(dev)) अणु
			child = device_get_next_child_node(dev, child);
			अगर (!child) अणु
				dev_err(dev,
					"missing child device node for entry %d\n",
					i);
				वापस -EINVAL;
			पूर्ण
		पूर्ण

		error = gpio_keys_setup_key(pdev, input, ddata,
					    button, i, child);
		अगर (error) अणु
			fwnode_handle_put(child);
			वापस error;
		पूर्ण

		अगर (button->wakeup)
			wakeup = 1;
	पूर्ण

	fwnode_handle_put(child);

	error = input_रेजिस्टर_device(input);
	अगर (error) अणु
		dev_err(dev, "Unable to register input device, error: %d\n",
			error);
		वापस error;
	पूर्ण

	device_init_wakeup(dev, wakeup);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused
gpio_keys_button_enable_wakeup(काष्ठा gpio_button_data *bdata)
अणु
	पूर्णांक error;

	error = enable_irq_wake(bdata->irq);
	अगर (error) अणु
		dev_err(bdata->input->dev.parent,
			"failed to configure IRQ %d as wakeup source: %d\n",
			bdata->irq, error);
		वापस error;
	पूर्ण

	अगर (bdata->wakeup_trigger_type) अणु
		error = irq_set_irq_type(bdata->irq,
					 bdata->wakeup_trigger_type);
		अगर (error) अणु
			dev_err(bdata->input->dev.parent,
				"failed to set wakeup trigger %08x for IRQ %d: %d\n",
				bdata->wakeup_trigger_type, bdata->irq, error);
			disable_irq_wake(bdata->irq);
			वापस error;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __maybe_unused
gpio_keys_button_disable_wakeup(काष्ठा gpio_button_data *bdata)
अणु
	पूर्णांक error;

	/*
	 * The trigger type is always both edges क्रम gpio-based keys and we करो
	 * not support changing wakeup trigger क्रम पूर्णांकerrupt-based keys.
	 */
	अगर (bdata->wakeup_trigger_type) अणु
		error = irq_set_irq_type(bdata->irq, IRQ_TYPE_EDGE_BOTH);
		अगर (error)
			dev_warn(bdata->input->dev.parent,
				 "failed to restore interrupt trigger for IRQ %d: %d\n",
				 bdata->irq, error);
	पूर्ण

	error = disable_irq_wake(bdata->irq);
	अगर (error)
		dev_warn(bdata->input->dev.parent,
			 "failed to disable IRQ %d as wake source: %d\n",
			 bdata->irq, error);
पूर्ण

अटल पूर्णांक __maybe_unused
gpio_keys_enable_wakeup(काष्ठा gpio_keys_drvdata *ddata)
अणु
	काष्ठा gpio_button_data *bdata;
	पूर्णांक error;
	पूर्णांक i;

	क्रम (i = 0; i < ddata->pdata->nbuttons; i++) अणु
		bdata = &ddata->data[i];
		अगर (bdata->button->wakeup) अणु
			error = gpio_keys_button_enable_wakeup(bdata);
			अगर (error)
				जाओ err_out;
		पूर्ण
		bdata->suspended = true;
	पूर्ण

	वापस 0;

err_out:
	जबतक (i--) अणु
		bdata = &ddata->data[i];
		अगर (bdata->button->wakeup)
			gpio_keys_button_disable_wakeup(bdata);
		bdata->suspended = false;
	पूर्ण

	वापस error;
पूर्ण

अटल व्योम __maybe_unused
gpio_keys_disable_wakeup(काष्ठा gpio_keys_drvdata *ddata)
अणु
	काष्ठा gpio_button_data *bdata;
	पूर्णांक i;

	क्रम (i = 0; i < ddata->pdata->nbuttons; i++) अणु
		bdata = &ddata->data[i];
		bdata->suspended = false;
		अगर (irqd_is_wakeup_set(irq_get_irq_data(bdata->irq)))
			gpio_keys_button_disable_wakeup(bdata);
	पूर्ण
पूर्ण

अटल पूर्णांक __maybe_unused gpio_keys_suspend(काष्ठा device *dev)
अणु
	काष्ठा gpio_keys_drvdata *ddata = dev_get_drvdata(dev);
	काष्ठा input_dev *input = ddata->input;
	पूर्णांक error;

	अगर (device_may_wakeup(dev)) अणु
		error = gpio_keys_enable_wakeup(ddata);
		अगर (error)
			वापस error;
	पूर्ण अन्यथा अणु
		mutex_lock(&input->mutex);
		अगर (input_device_enabled(input))
			gpio_keys_बंद(input);
		mutex_unlock(&input->mutex);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused gpio_keys_resume(काष्ठा device *dev)
अणु
	काष्ठा gpio_keys_drvdata *ddata = dev_get_drvdata(dev);
	काष्ठा input_dev *input = ddata->input;
	पूर्णांक error = 0;

	अगर (device_may_wakeup(dev)) अणु
		gpio_keys_disable_wakeup(ddata);
	पूर्ण अन्यथा अणु
		mutex_lock(&input->mutex);
		अगर (input_device_enabled(input))
			error = gpio_keys_खोलो(input);
		mutex_unlock(&input->mutex);
	पूर्ण

	अगर (error)
		वापस error;

	gpio_keys_report_state(ddata);
	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(gpio_keys_pm_ops, gpio_keys_suspend, gpio_keys_resume);

अटल व्योम gpio_keys_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;

	ret = gpio_keys_suspend(&pdev->dev);
	अगर (ret)
		dev_err(&pdev->dev, "failed to shutdown\n");
पूर्ण

अटल काष्ठा platक्रमm_driver gpio_keys_device_driver = अणु
	.probe		= gpio_keys_probe,
	.shutकरोwn	= gpio_keys_shutकरोwn,
	.driver		= अणु
		.name	= "gpio-keys",
		.pm	= &gpio_keys_pm_ops,
		.of_match_table = gpio_keys_of_match,
		.dev_groups	= gpio_keys_groups,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init gpio_keys_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&gpio_keys_device_driver);
पूर्ण

अटल व्योम __निकास gpio_keys_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&gpio_keys_device_driver);
पूर्ण

late_initcall(gpio_keys_init);
module_निकास(gpio_keys_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Phil Blundell <pb@handhelds.org>");
MODULE_DESCRIPTION("Keyboard driver for GPIOs");
MODULE_ALIAS("platform:gpio-keys");
