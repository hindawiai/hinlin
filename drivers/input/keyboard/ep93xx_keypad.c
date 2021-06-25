<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम the Cirrus EP93xx matrix keypad controller.
 *
 * Copyright (c) 2008 H Hartley Sweeten <hsweeten@visionengravers.com>
 *
 * Based on the pxa27x matrix keypad controller by Roकरोlfo Giometti.
 *
 * NOTE:
 *
 * The 3-key reset is triggered by pressing the 3 keys in
 * Row 0, Columns 2, 4, and 7 at the same समय.  This action can
 * be disabled by setting the EP93XX_KEYPAD_DISABLE_3_KEY flag.
 *
 * Normal operation क्रम the matrix करोes not स्वतःrepeat the key press.
 * This action can be enabled by setting the EP93XX_KEYPAD_AUTOREPEAT
 * flag.
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/input/matrix_keypad.h>
#समावेश <linux/slab.h>
#समावेश <linux/soc/cirrus/ep93xx.h>
#समावेश <linux/platक्रमm_data/keypad-ep93xx.h>

/*
 * Keypad Interface Register offsets
 */
#घोषणा KEY_INIT		0x00	/* Key Scan Initialization रेजिस्टर */
#घोषणा KEY_DIAG		0x04	/* Key Scan Diagnostic रेजिस्टर */
#घोषणा KEY_REG			0x08	/* Key Value Capture रेजिस्टर */

/* Key Scan Initialization Register bit defines */
#घोषणा KEY_INIT_DBNC_MASK	(0x00ff0000)
#घोषणा KEY_INIT_DBNC_SHIFT	(16)
#घोषणा KEY_INIT_DIS3KY		(1<<15)
#घोषणा KEY_INIT_DIAG		(1<<14)
#घोषणा KEY_INIT_BACK		(1<<13)
#घोषणा KEY_INIT_T2		(1<<12)
#घोषणा KEY_INIT_PRSCL_MASK	(0x000003ff)
#घोषणा KEY_INIT_PRSCL_SHIFT	(0)

/* Key Scan Diagnostic Register bit defines */
#घोषणा KEY_DIAG_MASK		(0x0000003f)
#घोषणा KEY_DIAG_SHIFT		(0)

/* Key Value Capture Register bit defines */
#घोषणा KEY_REG_K		(1<<15)
#घोषणा KEY_REG_INT		(1<<14)
#घोषणा KEY_REG_2KEYS		(1<<13)
#घोषणा KEY_REG_1KEY		(1<<12)
#घोषणा KEY_REG_KEY2_MASK	(0x00000fc0)
#घोषणा KEY_REG_KEY2_SHIFT	(6)
#घोषणा KEY_REG_KEY1_MASK	(0x0000003f)
#घोषणा KEY_REG_KEY1_SHIFT	(0)

#घोषणा EP93XX_MATRIX_SIZE	(EP93XX_MATRIX_ROWS * EP93XX_MATRIX_COLS)

काष्ठा ep93xx_keypad अणु
	काष्ठा ep93xx_keypad_platक्रमm_data *pdata;
	काष्ठा input_dev *input_dev;
	काष्ठा clk *clk;

	व्योम __iomem *mmio_base;

	अचिन्हित लघु keycodes[EP93XX_MATRIX_SIZE];

	पूर्णांक key1;
	पूर्णांक key2;

	पूर्णांक irq;

	bool enabled;
पूर्ण;

अटल irqवापस_t ep93xx_keypad_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा ep93xx_keypad *keypad = dev_id;
	काष्ठा input_dev *input_dev = keypad->input_dev;
	अचिन्हित पूर्णांक status;
	पूर्णांक keycode, key1, key2;

	status = __raw_पढ़ोl(keypad->mmio_base + KEY_REG);

	keycode = (status & KEY_REG_KEY1_MASK) >> KEY_REG_KEY1_SHIFT;
	key1 = keypad->keycodes[keycode];

	keycode = (status & KEY_REG_KEY2_MASK) >> KEY_REG_KEY2_SHIFT;
	key2 = keypad->keycodes[keycode];

	अगर (status & KEY_REG_2KEYS) अणु
		अगर (keypad->key1 && key1 != keypad->key1 && key2 != keypad->key1)
			input_report_key(input_dev, keypad->key1, 0);

		अगर (keypad->key2 && key1 != keypad->key2 && key2 != keypad->key2)
			input_report_key(input_dev, keypad->key2, 0);

		input_report_key(input_dev, key1, 1);
		input_report_key(input_dev, key2, 1);

		keypad->key1 = key1;
		keypad->key2 = key2;

	पूर्ण अन्यथा अगर (status & KEY_REG_1KEY) अणु
		अगर (keypad->key1 && key1 != keypad->key1)
			input_report_key(input_dev, keypad->key1, 0);

		अगर (keypad->key2 && key1 != keypad->key2)
			input_report_key(input_dev, keypad->key2, 0);

		input_report_key(input_dev, key1, 1);

		keypad->key1 = key1;
		keypad->key2 = 0;

	पूर्ण अन्यथा अणु
		input_report_key(input_dev, keypad->key1, 0);
		input_report_key(input_dev, keypad->key2, 0);

		keypad->key1 = keypad->key2 = 0;
	पूर्ण
	input_sync(input_dev);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम ep93xx_keypad_config(काष्ठा ep93xx_keypad *keypad)
अणु
	काष्ठा ep93xx_keypad_platक्रमm_data *pdata = keypad->pdata;
	अचिन्हित पूर्णांक val = 0;

	clk_set_rate(keypad->clk, pdata->clk_rate);

	अगर (pdata->flags & EP93XX_KEYPAD_DISABLE_3_KEY)
		val |= KEY_INIT_DIS3KY;
	अगर (pdata->flags & EP93XX_KEYPAD_DIAG_MODE)
		val |= KEY_INIT_DIAG;
	अगर (pdata->flags & EP93XX_KEYPAD_BACK_DRIVE)
		val |= KEY_INIT_BACK;
	अगर (pdata->flags & EP93XX_KEYPAD_TEST_MODE)
		val |= KEY_INIT_T2;

	val |= ((pdata->debounce << KEY_INIT_DBNC_SHIFT) & KEY_INIT_DBNC_MASK);

	val |= ((pdata->prescale << KEY_INIT_PRSCL_SHIFT) & KEY_INIT_PRSCL_MASK);

	__raw_ग_लिखोl(val, keypad->mmio_base + KEY_INIT);
पूर्ण

अटल पूर्णांक ep93xx_keypad_खोलो(काष्ठा input_dev *pdev)
अणु
	काष्ठा ep93xx_keypad *keypad = input_get_drvdata(pdev);

	अगर (!keypad->enabled) अणु
		ep93xx_keypad_config(keypad);
		clk_enable(keypad->clk);
		keypad->enabled = true;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ep93xx_keypad_बंद(काष्ठा input_dev *pdev)
अणु
	काष्ठा ep93xx_keypad *keypad = input_get_drvdata(pdev);

	अगर (keypad->enabled) अणु
		clk_disable(keypad->clk);
		keypad->enabled = false;
	पूर्ण
पूर्ण


#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक ep93xx_keypad_suspend(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा ep93xx_keypad *keypad = platक्रमm_get_drvdata(pdev);
	काष्ठा input_dev *input_dev = keypad->input_dev;

	mutex_lock(&input_dev->mutex);

	अगर (keypad->enabled) अणु
		clk_disable(keypad->clk);
		keypad->enabled = false;
	पूर्ण

	mutex_unlock(&input_dev->mutex);

	अगर (device_may_wakeup(&pdev->dev))
		enable_irq_wake(keypad->irq);

	वापस 0;
पूर्ण

अटल पूर्णांक ep93xx_keypad_resume(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा ep93xx_keypad *keypad = platक्रमm_get_drvdata(pdev);
	काष्ठा input_dev *input_dev = keypad->input_dev;

	अगर (device_may_wakeup(&pdev->dev))
		disable_irq_wake(keypad->irq);

	mutex_lock(&input_dev->mutex);

	अगर (input_device_enabled(input_dev)) अणु
		अगर (!keypad->enabled) अणु
			ep93xx_keypad_config(keypad);
			clk_enable(keypad->clk);
			keypad->enabled = true;
		पूर्ण
	पूर्ण

	mutex_unlock(&input_dev->mutex);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(ep93xx_keypad_pm_ops,
			 ep93xx_keypad_suspend, ep93xx_keypad_resume);

अटल पूर्णांक ep93xx_keypad_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ep93xx_keypad *keypad;
	स्थिर काष्ठा matrix_keymap_data *keymap_data;
	काष्ठा input_dev *input_dev;
	काष्ठा resource *res;
	पूर्णांक err;

	keypad = kzalloc(माप(काष्ठा ep93xx_keypad), GFP_KERNEL);
	अगर (!keypad)
		वापस -ENOMEM;

	keypad->pdata = dev_get_platdata(&pdev->dev);
	अगर (!keypad->pdata) अणु
		err = -EINVAL;
		जाओ failed_मुक्त;
	पूर्ण

	keymap_data = keypad->pdata->keymap_data;
	अगर (!keymap_data) अणु
		err = -EINVAL;
		जाओ failed_मुक्त;
	पूर्ण

	keypad->irq = platक्रमm_get_irq(pdev, 0);
	अगर (keypad->irq < 0) अणु
		err = keypad->irq;
		जाओ failed_मुक्त;
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res) अणु
		err = -ENXIO;
		जाओ failed_मुक्त;
	पूर्ण

	res = request_mem_region(res->start, resource_size(res), pdev->name);
	अगर (!res) अणु
		err = -EBUSY;
		जाओ failed_मुक्त;
	पूर्ण

	keypad->mmio_base = ioremap(res->start, resource_size(res));
	अगर (keypad->mmio_base == शून्य) अणु
		err = -ENXIO;
		जाओ failed_मुक्त_mem;
	पूर्ण

	err = ep93xx_keypad_acquire_gpio(pdev);
	अगर (err)
		जाओ failed_मुक्त_io;

	keypad->clk = clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(keypad->clk)) अणु
		err = PTR_ERR(keypad->clk);
		जाओ failed_मुक्त_gpio;
	पूर्ण

	input_dev = input_allocate_device();
	अगर (!input_dev) अणु
		err = -ENOMEM;
		जाओ failed_put_clk;
	पूर्ण

	keypad->input_dev = input_dev;

	input_dev->name = pdev->name;
	input_dev->id.bustype = BUS_HOST;
	input_dev->खोलो = ep93xx_keypad_खोलो;
	input_dev->बंद = ep93xx_keypad_बंद;
	input_dev->dev.parent = &pdev->dev;

	err = matrix_keypad_build_keymap(keymap_data, शून्य,
					 EP93XX_MATRIX_ROWS, EP93XX_MATRIX_COLS,
					 keypad->keycodes, input_dev);
	अगर (err)
		जाओ failed_मुक्त_dev;

	अगर (keypad->pdata->flags & EP93XX_KEYPAD_AUTOREPEAT)
		__set_bit(EV_REP, input_dev->evbit);
	input_set_drvdata(input_dev, keypad);

	err = request_irq(keypad->irq, ep93xx_keypad_irq_handler,
			  0, pdev->name, keypad);
	अगर (err)
		जाओ failed_मुक्त_dev;

	err = input_रेजिस्टर_device(input_dev);
	अगर (err)
		जाओ failed_मुक्त_irq;

	platक्रमm_set_drvdata(pdev, keypad);
	device_init_wakeup(&pdev->dev, 1);

	वापस 0;

failed_मुक्त_irq:
	मुक्त_irq(keypad->irq, keypad);
failed_मुक्त_dev:
	input_मुक्त_device(input_dev);
failed_put_clk:
	clk_put(keypad->clk);
failed_मुक्त_gpio:
	ep93xx_keypad_release_gpio(pdev);
failed_मुक्त_io:
	iounmap(keypad->mmio_base);
failed_मुक्त_mem:
	release_mem_region(res->start, resource_size(res));
failed_मुक्त:
	kमुक्त(keypad);
	वापस err;
पूर्ण

अटल पूर्णांक ep93xx_keypad_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ep93xx_keypad *keypad = platक्रमm_get_drvdata(pdev);
	काष्ठा resource *res;

	मुक्त_irq(keypad->irq, keypad);

	अगर (keypad->enabled)
		clk_disable(keypad->clk);
	clk_put(keypad->clk);

	input_unरेजिस्टर_device(keypad->input_dev);

	ep93xx_keypad_release_gpio(pdev);

	iounmap(keypad->mmio_base);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	release_mem_region(res->start, resource_size(res));

	kमुक्त(keypad);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver ep93xx_keypad_driver = अणु
	.driver		= अणु
		.name	= "ep93xx-keypad",
		.pm	= &ep93xx_keypad_pm_ops,
	पूर्ण,
	.probe		= ep93xx_keypad_probe,
	.हटाओ		= ep93xx_keypad_हटाओ,
पूर्ण;
module_platक्रमm_driver(ep93xx_keypad_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("H Hartley Sweeten <hsweeten@visionengravers.com>");
MODULE_DESCRIPTION("EP93xx Matrix Keypad Controller");
MODULE_ALIAS("platform:ep93xx-keypad");
