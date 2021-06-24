<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * OMAP4 Keypad Driver
 *
 * Copyright (C) 2010 Texas Instruments
 *
 * Author: Abraham Arce <x0066660@ti.com>
 * Initial Code: Syed Rafiuddin <rafiuddin.syed@ti.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/input.h>
#समावेश <linux/input/matrix_keypad.h>
#समावेश <linux/slab.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/pm_wakeirq.h>

/* OMAP4 रेजिस्टरs */
#घोषणा OMAP4_KBD_REVISION		0x00
#घोषणा OMAP4_KBD_SYSCONFIG		0x10
#घोषणा OMAP4_KBD_SYSSTATUS		0x14
#घोषणा OMAP4_KBD_IRQSTATUS		0x18
#घोषणा OMAP4_KBD_IRQENABLE		0x1C
#घोषणा OMAP4_KBD_WAKEUPENABLE		0x20
#घोषणा OMAP4_KBD_PENDING		0x24
#घोषणा OMAP4_KBD_CTRL			0x28
#घोषणा OMAP4_KBD_DEBOUNCINGTIME	0x2C
#घोषणा OMAP4_KBD_LONGKEYTIME		0x30
#घोषणा OMAP4_KBD_TIMEOUT		0x34
#घोषणा OMAP4_KBD_STATEMACHINE		0x38
#घोषणा OMAP4_KBD_ROWINPUTS		0x3C
#घोषणा OMAP4_KBD_COLUMNOUTPUTS		0x40
#घोषणा OMAP4_KBD_FULLCODE31_0		0x44
#घोषणा OMAP4_KBD_FULLCODE63_32		0x48

/* OMAP4 bit definitions */
#घोषणा OMAP4_DEF_IRQENABLE_EVENTEN	BIT(0)
#घोषणा OMAP4_DEF_IRQENABLE_LONGKEY	BIT(1)
#घोषणा OMAP4_DEF_WUP_EVENT_ENA		BIT(0)
#घोषणा OMAP4_DEF_WUP_LONG_KEY_ENA	BIT(1)
#घोषणा OMAP4_DEF_CTRL_NOSOFTMODE	BIT(1)
#घोषणा OMAP4_DEF_CTRL_PTV_SHIFT	2

/* OMAP4 values */
#घोषणा OMAP4_VAL_IRQDISABLE		0x0

/*
 * Errata i689: If a key is released क्रम a समय लघुer than debounce समय,
 * the keyboard will idle and never detect the key release. The workaround
 * is to use at least a 12ms debounce समय. See omap5432 TRM chapter
 * "26.4.6.2 Keyboard Controller Timer" क्रम more inक्रमmation.
 */
#घोषणा OMAP4_KEYPAD_PTV_DIV_128        0x6
#घोषणा OMAP4_KEYPAD_DEBOUNCINGTIME_MS(dbms, ptv)     \
	((((dbms) * 1000) / ((1 << ((ptv) + 1)) * (1000000 / 32768))) - 1)
#घोषणा OMAP4_VAL_DEBOUNCINGTIME_16MS					\
	OMAP4_KEYPAD_DEBOUNCINGTIME_MS(16, OMAP4_KEYPAD_PTV_DIV_128)
#घोषणा OMAP4_KEYPAD_AUTOIDLE_MS	50	/* Approximate measured समय */
#घोषणा OMAP4_KEYPAD_IDLE_CHECK_MS	(OMAP4_KEYPAD_AUTOIDLE_MS / 2)

क्रमागत अणु
	KBD_REVISION_OMAP4 = 0,
	KBD_REVISION_OMAP5,
पूर्ण;

काष्ठा omap4_keypad अणु
	काष्ठा input_dev *input;

	व्योम __iomem *base;
	अचिन्हित पूर्णांक irq;
	काष्ठा mutex lock;		/* क्रम key scan */

	अचिन्हित पूर्णांक rows;
	अचिन्हित पूर्णांक cols;
	u32 reg_offset;
	u32 irqreg_offset;
	अचिन्हित पूर्णांक row_shअगरt;
	bool no_स्वतःrepeat;
	u64 keys;
	अचिन्हित लघु *keymap;
पूर्ण;

अटल पूर्णांक kbd_पढ़ोl(काष्ठा omap4_keypad *keypad_data, u32 offset)
अणु
	वापस __raw_पढ़ोl(keypad_data->base +
				keypad_data->reg_offset + offset);
पूर्ण

अटल व्योम kbd_ग_लिखोl(काष्ठा omap4_keypad *keypad_data, u32 offset, u32 value)
अणु
	__raw_ग_लिखोl(value,
		     keypad_data->base + keypad_data->reg_offset + offset);
पूर्ण

अटल पूर्णांक kbd_पढ़ो_irqreg(काष्ठा omap4_keypad *keypad_data, u32 offset)
अणु
	वापस __raw_पढ़ोl(keypad_data->base +
				keypad_data->irqreg_offset + offset);
पूर्ण

अटल व्योम kbd_ग_लिखो_irqreg(काष्ठा omap4_keypad *keypad_data,
			     u32 offset, u32 value)
अणु
	__raw_ग_लिखोl(value,
		     keypad_data->base + keypad_data->irqreg_offset + offset);
पूर्ण

अटल पूर्णांक omap4_keypad_report_keys(काष्ठा omap4_keypad *keypad_data,
				    u64 keys, bool करोwn)
अणु
	काष्ठा input_dev *input_dev = keypad_data->input;
	अचिन्हित पूर्णांक col, row, code;
	DECLARE_BITMAP(mask, 64);
	अचिन्हित दीर्घ bit;
	पूर्णांक events = 0;

	biपंचांगap_from_u64(mask, keys);

	क्रम_each_set_bit(bit, mask, keypad_data->rows * BITS_PER_BYTE) अणु
		row = bit / BITS_PER_BYTE;
		col = bit % BITS_PER_BYTE;
		code = MATRIX_SCAN_CODE(row, col, keypad_data->row_shअगरt);

		input_event(input_dev, EV_MSC, MSC_SCAN, code);
		input_report_key(input_dev, keypad_data->keymap[code], करोwn);

		events++;
	पूर्ण

	अगर (events)
		input_sync(input_dev);

	वापस events;
पूर्ण

अटल व्योम omap4_keypad_scan_keys(काष्ठा omap4_keypad *keypad_data, u64 keys)
अणु
	u64 changed;

	mutex_lock(&keypad_data->lock);

	changed = keys ^ keypad_data->keys;

	/*
	 * Report key up events separately and first. This matters in हाल we
	 * lost key-up पूर्णांकerrupt and just now catching up.
	 */
	omap4_keypad_report_keys(keypad_data, changed & ~keys, false);

	/* Report key करोwn events */
	omap4_keypad_report_keys(keypad_data, changed & keys, true);

	keypad_data->keys = keys;

	mutex_unlock(&keypad_data->lock);
पूर्ण

/* Interrupt handlers */
अटल irqवापस_t omap4_keypad_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा omap4_keypad *keypad_data = dev_id;

	अगर (kbd_पढ़ो_irqreg(keypad_data, OMAP4_KBD_IRQSTATUS))
		वापस IRQ_WAKE_THREAD;

	वापस IRQ_NONE;
पूर्ण

अटल irqवापस_t omap4_keypad_irq_thपढ़ो_fn(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा omap4_keypad *keypad_data = dev_id;
	काष्ठा device *dev = keypad_data->input->dev.parent;
	u32 low, high;
	पूर्णांक error;
	u64 keys;

	error = pm_runसमय_get_sync(dev);
	अगर (error < 0) अणु
		pm_runसमय_put_noidle(dev);
		वापस IRQ_NONE;
	पूर्ण

	low = kbd_पढ़ोl(keypad_data, OMAP4_KBD_FULLCODE31_0);
	high = kbd_पढ़ोl(keypad_data, OMAP4_KBD_FULLCODE63_32);
	keys = low | (u64)high << 32;

	omap4_keypad_scan_keys(keypad_data, keys);

	/* clear pending पूर्णांकerrupts */
	kbd_ग_लिखो_irqreg(keypad_data, OMAP4_KBD_IRQSTATUS,
			 kbd_पढ़ो_irqreg(keypad_data, OMAP4_KBD_IRQSTATUS));

	pm_runसमय_mark_last_busy(dev);
	pm_runसमय_put_स्वतःsuspend(dev);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक omap4_keypad_खोलो(काष्ठा input_dev *input)
अणु
	काष्ठा omap4_keypad *keypad_data = input_get_drvdata(input);
	काष्ठा device *dev = input->dev.parent;
	पूर्णांक error;

	error = pm_runसमय_get_sync(dev);
	अगर (error < 0) अणु
		pm_runसमय_put_noidle(dev);
		वापस error;
	पूर्ण

	disable_irq(keypad_data->irq);

	kbd_ग_लिखोl(keypad_data, OMAP4_KBD_CTRL,
			OMAP4_DEF_CTRL_NOSOFTMODE |
			(OMAP4_KEYPAD_PTV_DIV_128 << OMAP4_DEF_CTRL_PTV_SHIFT));
	kbd_ग_लिखोl(keypad_data, OMAP4_KBD_DEBOUNCINGTIME,
			OMAP4_VAL_DEBOUNCINGTIME_16MS);
	/* clear pending पूर्णांकerrupts */
	kbd_ग_लिखो_irqreg(keypad_data, OMAP4_KBD_IRQSTATUS,
			 kbd_पढ़ो_irqreg(keypad_data, OMAP4_KBD_IRQSTATUS));
	kbd_ग_लिखो_irqreg(keypad_data, OMAP4_KBD_IRQENABLE,
			OMAP4_DEF_IRQENABLE_EVENTEN);
	kbd_ग_लिखोl(keypad_data, OMAP4_KBD_WAKEUPENABLE,
			OMAP4_DEF_WUP_EVENT_ENA);

	enable_irq(keypad_data->irq);

	pm_runसमय_mark_last_busy(dev);
	pm_runसमय_put_स्वतःsuspend(dev);

	वापस 0;
पूर्ण

अटल व्योम omap4_keypad_stop(काष्ठा omap4_keypad *keypad_data)
अणु
	/* Disable पूर्णांकerrupts and wake-up events */
	kbd_ग_लिखो_irqreg(keypad_data, OMAP4_KBD_IRQENABLE,
			 OMAP4_VAL_IRQDISABLE);
	kbd_ग_लिखोl(keypad_data, OMAP4_KBD_WAKEUPENABLE, 0);

	/* clear pending पूर्णांकerrupts */
	kbd_ग_लिखो_irqreg(keypad_data, OMAP4_KBD_IRQSTATUS,
			 kbd_पढ़ो_irqreg(keypad_data, OMAP4_KBD_IRQSTATUS));
पूर्ण

अटल व्योम omap4_keypad_बंद(काष्ठा input_dev *input)
अणु
	काष्ठा omap4_keypad *keypad_data = input_get_drvdata(input);
	काष्ठा device *dev = input->dev.parent;
	पूर्णांक error;

	error = pm_runसमय_get_sync(dev);
	अगर (error < 0)
		pm_runसमय_put_noidle(dev);

	disable_irq(keypad_data->irq);
	omap4_keypad_stop(keypad_data);
	enable_irq(keypad_data->irq);

	pm_runसमय_mark_last_busy(dev);
	pm_runसमय_put_स्वतःsuspend(dev);
पूर्ण

अटल पूर्णांक omap4_keypad_parse_dt(काष्ठा device *dev,
				 काष्ठा omap4_keypad *keypad_data)
अणु
	काष्ठा device_node *np = dev->of_node;
	पूर्णांक err;

	err = matrix_keypad_parse_properties(dev, &keypad_data->rows,
					     &keypad_data->cols);
	अगर (err)
		वापस err;

	अगर (of_get_property(np, "linux,input-no-autorepeat", शून्य))
		keypad_data->no_स्वतःrepeat = true;

	वापस 0;
पूर्ण

अटल पूर्णांक omap4_keypad_check_revision(काष्ठा device *dev,
				       काष्ठा omap4_keypad *keypad_data)
अणु
	अचिन्हित पूर्णांक rev;

	rev = __raw_पढ़ोl(keypad_data->base + OMAP4_KBD_REVISION);
	rev &= 0x03 << 30;
	rev >>= 30;
	चयन (rev) अणु
	हाल KBD_REVISION_OMAP4:
		keypad_data->reg_offset = 0x00;
		keypad_data->irqreg_offset = 0x00;
		अवरोध;
	हाल KBD_REVISION_OMAP5:
		keypad_data->reg_offset = 0x10;
		keypad_data->irqreg_offset = 0x0c;
		अवरोध;
	शेष:
		dev_err(dev, "Keypad reports unsupported revision %d", rev);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Errata ID i689 "1.32 Keyboard Key Up Event Can Be Missed".
 * Interrupt may not happen क्रम key-up events. We must clear stuck
 * key-up events after the keyboard hardware has स्वतः-idled.
 */
अटल पूर्णांक __maybe_unused omap4_keypad_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा omap4_keypad *keypad_data = platक्रमm_get_drvdata(pdev);
	u32 active;

	active = kbd_पढ़ोl(keypad_data, OMAP4_KBD_STATEMACHINE);
	अगर (active) अणु
		pm_runसमय_mark_last_busy(dev);
		वापस -EBUSY;
	पूर्ण

	omap4_keypad_scan_keys(keypad_data, 0);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops omap4_keypad_pm_ops = अणु
	SET_RUNTIME_PM_OPS(omap4_keypad_runसमय_suspend, शून्य, शून्य)
पूर्ण;

अटल व्योम omap4_disable_pm(व्योम *d)
अणु
	pm_runसमय_करोnt_use_स्वतःsuspend(d);
	pm_runसमय_disable(d);
पूर्ण

अटल पूर्णांक omap4_keypad_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा omap4_keypad *keypad_data;
	काष्ठा input_dev *input_dev;
	काष्ठा resource *res;
	अचिन्हित पूर्णांक max_keys;
	पूर्णांक irq;
	पूर्णांक error;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res) अणु
		dev_err(&pdev->dev, "no base address specified\n");
		वापस -EINVAL;
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	keypad_data = devm_kzalloc(dev, माप(*keypad_data), GFP_KERNEL);
	अगर (!keypad_data) अणु
		dev_err(dev, "keypad_data memory allocation failed\n");
		वापस -ENOMEM;
	पूर्ण

	keypad_data->irq = irq;
	mutex_init(&keypad_data->lock);
	platक्रमm_set_drvdata(pdev, keypad_data);

	error = omap4_keypad_parse_dt(dev, keypad_data);
	अगर (error)
		वापस error;

	keypad_data->base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(keypad_data->base))
		वापस PTR_ERR(keypad_data->base);

	pm_runसमय_use_स्वतःsuspend(dev);
	pm_runसमय_set_स्वतःsuspend_delay(dev, OMAP4_KEYPAD_IDLE_CHECK_MS);
	pm_runसमय_enable(dev);

	error = devm_add_action_or_reset(dev, omap4_disable_pm, dev);
	अगर (error) अणु
		dev_err(dev, "unable to register cleanup action\n");
		वापस error;
	पूर्ण

	/*
	 * Enable घड़ीs क्रम the keypad module so that we can पढ़ो
	 * revision रेजिस्टर.
	 */
	error = pm_runसमय_get_sync(dev);
	अगर (error) अणु
		dev_err(dev, "pm_runtime_get_sync() failed\n");
		pm_runसमय_put_noidle(dev);
		वापस error;
	पूर्ण

	error = omap4_keypad_check_revision(dev, keypad_data);
	अगर (!error) अणु
		/* Ensure device करोes not उठाओ पूर्णांकerrupts */
		omap4_keypad_stop(keypad_data);
	पूर्ण

	pm_runसमय_mark_last_busy(dev);
	pm_runसमय_put_स्वतःsuspend(dev);
	अगर (error)
		वापस error;

	/* input device allocation */
	keypad_data->input = input_dev = devm_input_allocate_device(dev);
	अगर (!input_dev)
		वापस -ENOMEM;

	input_dev->name = pdev->name;
	input_dev->id.bustype = BUS_HOST;
	input_dev->id.venकरोr = 0x0001;
	input_dev->id.product = 0x0001;
	input_dev->id.version = 0x0001;

	input_dev->खोलो = omap4_keypad_खोलो;
	input_dev->बंद = omap4_keypad_बंद;

	input_set_capability(input_dev, EV_MSC, MSC_SCAN);
	अगर (!keypad_data->no_स्वतःrepeat)
		__set_bit(EV_REP, input_dev->evbit);

	input_set_drvdata(input_dev, keypad_data);

	keypad_data->row_shअगरt = get_count_order(keypad_data->cols);
	max_keys = keypad_data->rows << keypad_data->row_shअगरt;
	keypad_data->keymap = devm_kसुस्मृति(dev,
					   max_keys,
					   माप(keypad_data->keymap[0]),
					   GFP_KERNEL);
	अगर (!keypad_data->keymap) अणु
		dev_err(dev, "Not enough memory for keymap\n");
		वापस -ENOMEM;
	पूर्ण

	error = matrix_keypad_build_keymap(शून्य, शून्य,
					   keypad_data->rows, keypad_data->cols,
					   keypad_data->keymap, input_dev);
	अगर (error) अणु
		dev_err(dev, "failed to build keymap\n");
		वापस error;
	पूर्ण

	error = devm_request_thपढ़ोed_irq(dev, keypad_data->irq,
					  omap4_keypad_irq_handler,
					  omap4_keypad_irq_thपढ़ो_fn,
					  IRQF_ONESHOT,
					  "omap4-keypad", keypad_data);
	अगर (error) अणु
		dev_err(dev, "failed to register interrupt\n");
		वापस error;
	पूर्ण

	error = input_रेजिस्टर_device(keypad_data->input);
	अगर (error) अणु
		dev_err(dev, "failed to register input device\n");
		वापस error;
	पूर्ण

	device_init_wakeup(dev, true);
	error = dev_pm_set_wake_irq(dev, keypad_data->irq);
	अगर (error)
		dev_warn(dev, "failed to set up wakeup irq: %d\n", error);

	वापस 0;
पूर्ण

अटल पूर्णांक omap4_keypad_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	dev_pm_clear_wake_irq(&pdev->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id omap_keypad_dt_match[] = अणु
	अणु .compatible = "ti,omap4-keypad" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, omap_keypad_dt_match);

अटल काष्ठा platक्रमm_driver omap4_keypad_driver = अणु
	.probe		= omap4_keypad_probe,
	.हटाओ		= omap4_keypad_हटाओ,
	.driver		= अणु
		.name	= "omap4-keypad",
		.of_match_table = omap_keypad_dt_match,
		.pm = &omap4_keypad_pm_ops,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(omap4_keypad_driver);

MODULE_AUTHOR("Texas Instruments");
MODULE_DESCRIPTION("OMAP4 Keypad Driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:omap4-keypad");
