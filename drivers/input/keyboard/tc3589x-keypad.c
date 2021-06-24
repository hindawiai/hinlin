<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) ST-Ericsson SA 2010
 *
 * Author: Jayeeta Banerjee <jayeeta.banerjee@stericsson.com>
 * Author: Sundar Iyer <sundar.iyer@stericsson.com>
 *
 * TC35893 MFD Keypad Controller driver
 */

#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/input.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/input/matrix_keypad.h>
#समावेश <linux/i2c.h>
#समावेश <linux/slab.h>
#समावेश <linux/mfd/tc3589x.h>
#समावेश <linux/device.h>

/* Maximum supported keypad matrix row/columns size */
#घोषणा TC3589x_MAX_KPROW               8
#घोषणा TC3589x_MAX_KPCOL               12

/* keypad related Constants */
#घोषणा TC3589x_MAX_DEBOUNCE_SETTLE     0xFF
#घोषणा DEDICATED_KEY_VAL		0xFF

/* Pull up/करोwn masks */
#घोषणा TC3589x_NO_PULL_MASK		0x0
#घोषणा TC3589x_PULL_DOWN_MASK		0x1
#घोषणा TC3589x_PULL_UP_MASK		0x2
#घोषणा TC3589x_PULLUP_ALL_MASK		0xAA
#घोषणा TC3589x_IO_PULL_VAL(index, mask)	((mask)<<((index)%4)*2)

/* Bit masks क्रम IOCFG रेजिस्टर */
#घोषणा IOCFG_BALLCFG		0x01
#घोषणा IOCFG_IG		0x08

#घोषणा KP_EVCODE_COL_MASK	0x0F
#घोषणा KP_EVCODE_ROW_MASK	0x70
#घोषणा KP_RELEASE_EVT_MASK	0x80

#घोषणा KP_ROW_SHIFT		4

#घोषणा KP_NO_VALID_KEY_MASK	0x7F

/* bit masks क्रम RESTCTRL रेजिस्टर */
#घोषणा TC3589x_KBDRST		0x2
#घोषणा TC3589x_IRQRST		0x10
#घोषणा TC3589x_RESET_ALL	0x1B

/* KBDMFS रेजिस्टर bit mask */
#घोषणा TC3589x_KBDMFS_EN	0x1

/* CLKEN रेजिस्टर biपंचांगask */
#घोषणा KPD_CLK_EN		0x1

/* RSTINTCLR रेजिस्टर bit mask */
#घोषणा IRQ_CLEAR		0x1

/* bit masks क्रम keyboard पूर्णांकerrupts*/
#घोषणा TC3589x_EVT_LOSS_INT	0x8
#घोषणा TC3589x_EVT_INT		0x4
#घोषणा TC3589x_KBD_LOSS_INT	0x2
#घोषणा TC3589x_KBD_INT		0x1

/* bit masks क्रम keyboard पूर्णांकerrupt clear*/
#घोषणा TC3589x_EVT_INT_CLR	0x2
#घोषणा TC3589x_KBD_INT_CLR	0x1

/**
 * काष्ठा tc35893_keypad_platक्रमm_data - platक्रमm specअगरic keypad data
 * @keymap_data:        matrix scan code table क्रम keycodes
 * @krow:               mask क्रम available rows, value is 0xFF
 * @kcol:               mask क्रम available columns, value is 0xFF
 * @debounce_period:    platक्रमm specअगरic debounce समय
 * @settle_समय:        platक्रमm specअगरic settle करोwn समय
 * @irqtype:            type of पूर्णांकerrupt, falling or rising edge
 * @enable_wakeup:      specअगरies अगर keypad event can wake up प्रणाली from sleep
 * @no_स्वतःrepeat:      flag क्रम स्वतः repetition
 */
काष्ठा tc3589x_keypad_platक्रमm_data अणु
	स्थिर काष्ठा matrix_keymap_data *keymap_data;
	u8                      krow;
	u8                      kcol;
	u8                      debounce_period;
	u8                      settle_समय;
	अचिन्हित दीर्घ           irqtype;
	bool                    enable_wakeup;
	bool                    no_स्वतःrepeat;
पूर्ण;

/**
 * काष्ठा tc_keypad - data काष्ठाure used by keypad driver
 * @tc3589x:    poपूर्णांकer to tc35893
 * @input:      poपूर्णांकer to input device object
 * @board:      keypad platक्रमm device
 * @krow:	number of rows
 * @kcol:	number of columns
 * @keymap:     matrix scan code table क्रम keycodes
 * @keypad_stopped: holds keypad status
 */
काष्ठा tc_keypad अणु
	काष्ठा tc3589x *tc3589x;
	काष्ठा input_dev *input;
	स्थिर काष्ठा tc3589x_keypad_platक्रमm_data *board;
	अचिन्हित पूर्णांक krow;
	अचिन्हित पूर्णांक kcol;
	अचिन्हित लघु *keymap;
	bool keypad_stopped;
पूर्ण;

अटल पूर्णांक tc3589x_keypad_init_key_hardware(काष्ठा tc_keypad *keypad)
अणु
	पूर्णांक ret;
	काष्ठा tc3589x *tc3589x = keypad->tc3589x;
	स्थिर काष्ठा tc3589x_keypad_platक्रमm_data *board = keypad->board;

	/* validate platक्रमm configuration */
	अगर (board->kcol > TC3589x_MAX_KPCOL || board->krow > TC3589x_MAX_KPROW)
		वापस -EINVAL;

	/* configure KBDSIZE 4 LSbits क्रम cols and 4 MSbits क्रम rows */
	ret = tc3589x_reg_ग_लिखो(tc3589x, TC3589x_KBDSIZE,
			(board->krow << KP_ROW_SHIFT) | board->kcol);
	अगर (ret < 0)
		वापस ret;

	/* configure dedicated key config, no dedicated key selected */
	ret = tc3589x_reg_ग_लिखो(tc3589x, TC3589x_KBCFG_LSB, DEDICATED_KEY_VAL);
	अगर (ret < 0)
		वापस ret;

	ret = tc3589x_reg_ग_लिखो(tc3589x, TC3589x_KBCFG_MSB, DEDICATED_KEY_VAL);
	अगर (ret < 0)
		वापस ret;

	/* Configure settle समय */
	ret = tc3589x_reg_ग_लिखो(tc3589x, TC3589x_KBDSETTLE_REG,
				board->settle_समय);
	अगर (ret < 0)
		वापस ret;

	/* Configure debounce समय */
	ret = tc3589x_reg_ग_लिखो(tc3589x, TC3589x_KBDBOUNCE,
				board->debounce_period);
	अगर (ret < 0)
		वापस ret;

	/* Start of initialise keypad GPIOs */
	ret = tc3589x_set_bits(tc3589x, TC3589x_IOCFG, 0x0, IOCFG_IG);
	अगर (ret < 0)
		वापस ret;

	/* Configure pull-up resistors क्रम all row GPIOs */
	ret = tc3589x_reg_ग_लिखो(tc3589x, TC3589x_IOPULLCFG0_LSB,
					TC3589x_PULLUP_ALL_MASK);
	अगर (ret < 0)
		वापस ret;

	ret = tc3589x_reg_ग_लिखो(tc3589x, TC3589x_IOPULLCFG0_MSB,
					TC3589x_PULLUP_ALL_MASK);
	अगर (ret < 0)
		वापस ret;

	/* Configure pull-up resistors क्रम all column GPIOs */
	ret = tc3589x_reg_ग_लिखो(tc3589x, TC3589x_IOPULLCFG1_LSB,
			TC3589x_PULLUP_ALL_MASK);
	अगर (ret < 0)
		वापस ret;

	ret = tc3589x_reg_ग_लिखो(tc3589x, TC3589x_IOPULLCFG1_MSB,
			TC3589x_PULLUP_ALL_MASK);
	अगर (ret < 0)
		वापस ret;

	ret = tc3589x_reg_ग_लिखो(tc3589x, TC3589x_IOPULLCFG2_LSB,
			TC3589x_PULLUP_ALL_MASK);

	वापस ret;
पूर्ण

#घोषणा TC35893_DATA_REGS		4
#घोषणा TC35893_KEYCODE_FIFO_EMPTY	0x7f
#घोषणा TC35893_KEYCODE_FIFO_CLEAR	0xff
#घोषणा TC35893_KEYPAD_ROW_SHIFT	0x3

अटल irqवापस_t tc3589x_keypad_irq(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा tc_keypad *keypad = dev;
	काष्ठा tc3589x *tc3589x = keypad->tc3589x;
	u8 i, row_index, col_index, kbd_code, up;
	u8 code;

	क्रम (i = 0; i < TC35893_DATA_REGS * 2; i++) अणु
		kbd_code = tc3589x_reg_पढ़ो(tc3589x, TC3589x_EVTCODE_FIFO);

		/* loop till fअगरo is empty and no more keys are pressed */
		अगर (kbd_code == TC35893_KEYCODE_FIFO_EMPTY ||
				kbd_code == TC35893_KEYCODE_FIFO_CLEAR)
			जारी;

		/* valid key is found */
		col_index = kbd_code & KP_EVCODE_COL_MASK;
		row_index = (kbd_code & KP_EVCODE_ROW_MASK) >> KP_ROW_SHIFT;
		code = MATRIX_SCAN_CODE(row_index, col_index,
						TC35893_KEYPAD_ROW_SHIFT);
		up = kbd_code & KP_RELEASE_EVT_MASK;

		input_event(keypad->input, EV_MSC, MSC_SCAN, code);
		input_report_key(keypad->input, keypad->keymap[code], !up);
		input_sync(keypad->input);
	पूर्ण

	/* clear IRQ */
	tc3589x_set_bits(tc3589x, TC3589x_KBDIC,
			0x0, TC3589x_EVT_INT_CLR | TC3589x_KBD_INT_CLR);
	/* enable IRQ */
	tc3589x_set_bits(tc3589x, TC3589x_KBDMSK,
			0x0, TC3589x_EVT_LOSS_INT | TC3589x_EVT_INT);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक tc3589x_keypad_enable(काष्ठा tc_keypad *keypad)
अणु
	काष्ठा tc3589x *tc3589x = keypad->tc3589x;
	पूर्णांक ret;

	/* pull the keypad module out of reset */
	ret = tc3589x_set_bits(tc3589x, TC3589x_RSTCTRL, TC3589x_KBDRST, 0x0);
	अगर (ret < 0)
		वापस ret;

	/* configure KBDMFS */
	ret = tc3589x_set_bits(tc3589x, TC3589x_KBDMFS, 0x0, TC3589x_KBDMFS_EN);
	अगर (ret < 0)
		वापस ret;

	/* enable the keypad घड़ी */
	ret = tc3589x_set_bits(tc3589x, TC3589x_CLKEN, 0x0, KPD_CLK_EN);
	अगर (ret < 0)
		वापस ret;

	/* clear pending IRQs */
	ret =  tc3589x_set_bits(tc3589x, TC3589x_RSTINTCLR, 0x0, 0x1);
	अगर (ret < 0)
		वापस ret;

	/* enable the IRQs */
	ret = tc3589x_set_bits(tc3589x, TC3589x_KBDMSK, 0x0,
					TC3589x_EVT_LOSS_INT | TC3589x_EVT_INT);
	अगर (ret < 0)
		वापस ret;

	keypad->keypad_stopped = false;

	वापस ret;
पूर्ण

अटल पूर्णांक tc3589x_keypad_disable(काष्ठा tc_keypad *keypad)
अणु
	काष्ठा tc3589x *tc3589x = keypad->tc3589x;
	पूर्णांक ret;

	/* clear IRQ */
	ret = tc3589x_set_bits(tc3589x, TC3589x_KBDIC,
			0x0, TC3589x_EVT_INT_CLR | TC3589x_KBD_INT_CLR);
	अगर (ret < 0)
		वापस ret;

	/* disable all पूर्णांकerrupts */
	ret = tc3589x_set_bits(tc3589x, TC3589x_KBDMSK,
			~(TC3589x_EVT_LOSS_INT | TC3589x_EVT_INT), 0x0);
	अगर (ret < 0)
		वापस ret;

	/* disable the keypad module */
	ret = tc3589x_set_bits(tc3589x, TC3589x_CLKEN, 0x1, 0x0);
	अगर (ret < 0)
		वापस ret;

	/* put the keypad module पूर्णांकo reset */
	ret = tc3589x_set_bits(tc3589x, TC3589x_RSTCTRL, TC3589x_KBDRST, 0x1);

	keypad->keypad_stopped = true;

	वापस ret;
पूर्ण

अटल पूर्णांक tc3589x_keypad_खोलो(काष्ठा input_dev *input)
अणु
	पूर्णांक error;
	काष्ठा tc_keypad *keypad = input_get_drvdata(input);

	/* enable the keypad module */
	error = tc3589x_keypad_enable(keypad);
	अगर (error < 0) अणु
		dev_err(&input->dev, "failed to enable keypad module\n");
		वापस error;
	पूर्ण

	error = tc3589x_keypad_init_key_hardware(keypad);
	अगर (error < 0) अणु
		dev_err(&input->dev, "failed to configure keypad module\n");
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम tc3589x_keypad_बंद(काष्ठा input_dev *input)
अणु
	काष्ठा tc_keypad *keypad = input_get_drvdata(input);

	/* disable the keypad module */
	tc3589x_keypad_disable(keypad);
पूर्ण

अटल स्थिर काष्ठा tc3589x_keypad_platक्रमm_data *
tc3589x_keypad_of_probe(काष्ठा device *dev)
अणु
	काष्ठा device_node *np = dev->of_node;
	काष्ठा tc3589x_keypad_platक्रमm_data *plat;
	u32 cols, rows;
	u32 debounce_ms;
	पूर्णांक proplen;

	अगर (!np)
		वापस ERR_PTR(-ENODEV);

	plat = devm_kzalloc(dev, माप(*plat), GFP_KERNEL);
	अगर (!plat)
		वापस ERR_PTR(-ENOMEM);

	of_property_पढ़ो_u32(np, "keypad,num-columns", &cols);
	of_property_पढ़ो_u32(np, "keypad,num-rows", &rows);
	plat->kcol = (u8) cols;
	plat->krow = (u8) rows;
	अगर (!plat->krow || !plat->kcol ||
	     plat->krow > TC_KPD_ROWS || plat->kcol > TC_KPD_COLUMNS) अणु
		dev_err(dev,
			"keypad columns/rows not properly specified (%ux%u)\n",
			plat->kcol, plat->krow);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	अगर (!of_get_property(np, "linux,keymap", &proplen)) अणु
		dev_err(dev, "property linux,keymap not found\n");
		वापस ERR_PTR(-ENOENT);
	पूर्ण

	plat->no_स्वतःrepeat = of_property_पढ़ो_bool(np, "linux,no-autorepeat");

	plat->enable_wakeup = of_property_पढ़ो_bool(np, "wakeup-source") ||
			      /* legacy name */
			      of_property_पढ़ो_bool(np, "linux,wakeup");

	/* The custom delay क्रमmat is ms/16 */
	of_property_पढ़ो_u32(np, "debounce-delay-ms", &debounce_ms);
	अगर (debounce_ms)
		plat->debounce_period = debounce_ms * 16;
	अन्यथा
		plat->debounce_period = TC_KPD_DEBOUNCE_PERIOD;

	plat->settle_समय = TC_KPD_SETTLE_TIME;
	/* FIXME: should be property of the IRQ resource? */
	plat->irqtype = IRQF_TRIGGER_FALLING;

	वापस plat;
पूर्ण

अटल पूर्णांक tc3589x_keypad_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tc3589x *tc3589x = dev_get_drvdata(pdev->dev.parent);
	काष्ठा tc_keypad *keypad;
	काष्ठा input_dev *input;
	स्थिर काष्ठा tc3589x_keypad_platक्रमm_data *plat;
	पूर्णांक error, irq;

	plat = tc3589x_keypad_of_probe(&pdev->dev);
	अगर (IS_ERR(plat)) अणु
		dev_err(&pdev->dev, "invalid keypad platform data\n");
		वापस PTR_ERR(plat);
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	keypad = devm_kzalloc(&pdev->dev, माप(काष्ठा tc_keypad),
			      GFP_KERNEL);
	अगर (!keypad)
		वापस -ENOMEM;

	input = devm_input_allocate_device(&pdev->dev);
	अगर (!input) अणु
		dev_err(&pdev->dev, "failed to allocate input device\n");
		वापस -ENOMEM;
	पूर्ण

	keypad->board = plat;
	keypad->input = input;
	keypad->tc3589x = tc3589x;

	input->id.bustype = BUS_I2C;
	input->name = pdev->name;
	input->dev.parent = &pdev->dev;

	input->खोलो = tc3589x_keypad_खोलो;
	input->बंद = tc3589x_keypad_बंद;

	error = matrix_keypad_build_keymap(plat->keymap_data, शून्य,
					   TC3589x_MAX_KPROW, TC3589x_MAX_KPCOL,
					   शून्य, input);
	अगर (error) अणु
		dev_err(&pdev->dev, "Failed to build keymap\n");
		वापस error;
	पूर्ण

	keypad->keymap = input->keycode;

	input_set_capability(input, EV_MSC, MSC_SCAN);
	अगर (!plat->no_स्वतःrepeat)
		__set_bit(EV_REP, input->evbit);

	input_set_drvdata(input, keypad);

	tc3589x_keypad_disable(keypad);

	error = devm_request_thपढ़ोed_irq(&pdev->dev, irq,
					  शून्य, tc3589x_keypad_irq,
					  plat->irqtype | IRQF_ONESHOT,
					  "tc3589x-keypad", keypad);
	अगर (error) अणु
		dev_err(&pdev->dev,
				"Could not allocate irq %d,error %d\n",
				irq, error);
		वापस error;
	पूर्ण

	error = input_रेजिस्टर_device(input);
	अगर (error) अणु
		dev_err(&pdev->dev, "Could not register input device\n");
		वापस error;
	पूर्ण

	/* let platक्रमm decide अगर keypad is a wakeup source or not */
	device_init_wakeup(&pdev->dev, plat->enable_wakeup);
	device_set_wakeup_capable(&pdev->dev, plat->enable_wakeup);

	platक्रमm_set_drvdata(pdev, keypad);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक tc3589x_keypad_suspend(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा tc_keypad *keypad = platक्रमm_get_drvdata(pdev);
	पूर्णांक irq = platक्रमm_get_irq(pdev, 0);

	/* keypad is alपढ़ोy off; we करो nothing */
	अगर (keypad->keypad_stopped)
		वापस 0;

	/* अगर device is not a wakeup source, disable it क्रम घातersave */
	अगर (!device_may_wakeup(&pdev->dev))
		tc3589x_keypad_disable(keypad);
	अन्यथा
		enable_irq_wake(irq);

	वापस 0;
पूर्ण

अटल पूर्णांक tc3589x_keypad_resume(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा tc_keypad *keypad = platक्रमm_get_drvdata(pdev);
	पूर्णांक irq = platक्रमm_get_irq(pdev, 0);

	अगर (!keypad->keypad_stopped)
		वापस 0;

	/* enable the device to resume normal operations */
	अगर (!device_may_wakeup(&pdev->dev))
		tc3589x_keypad_enable(keypad);
	अन्यथा
		disable_irq_wake(irq);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(tc3589x_keypad_dev_pm_ops,
			 tc3589x_keypad_suspend, tc3589x_keypad_resume);

अटल काष्ठा platक्रमm_driver tc3589x_keypad_driver = अणु
	.driver	= अणु
		.name	= "tc3589x-keypad",
		.pm	= &tc3589x_keypad_dev_pm_ops,
	पूर्ण,
	.probe	= tc3589x_keypad_probe,
पूर्ण;
module_platक्रमm_driver(tc3589x_keypad_driver);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Jayeeta Banerjee/Sundar Iyer");
MODULE_DESCRIPTION("TC35893 Keypad Driver");
MODULE_ALIAS("platform:tc3589x-keypad");
