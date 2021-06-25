<शैली गुरु>
/*
 * SPEAr Keyboard Driver
 * Based on omap-keypad driver
 *
 * Copyright (C) 2010 ST Microelectronics
 * Rajeev Kumar <rajeevkumar.linux@gmail.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/clk.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/input.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_wakeup.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/platक्रमm_data/keyboard-spear.h>

/* Keyboard Registers */
#घोषणा MODE_CTL_REG	0x00
#घोषणा STATUS_REG	0x0C
#घोषणा DATA_REG	0x10
#घोषणा INTR_MASK	0x54

/* Register Values */
#घोषणा NUM_ROWS	16
#घोषणा NUM_COLS	16
#घोषणा MODE_CTL_PCLK_FREQ_SHIFT	9
#घोषणा MODE_CTL_PCLK_FREQ_MSK		0x7F

#घोषणा MODE_CTL_KEYBOARD	(0x2 << 0)
#घोषणा MODE_CTL_SCAN_RATE_10	(0x0 << 2)
#घोषणा MODE_CTL_SCAN_RATE_20	(0x1 << 2)
#घोषणा MODE_CTL_SCAN_RATE_40	(0x2 << 2)
#घोषणा MODE_CTL_SCAN_RATE_80	(0x3 << 2)
#घोषणा MODE_CTL_KEYNUM_SHIFT	6
#घोषणा MODE_CTL_START_SCAN	(0x1 << 8)

#घोषणा STATUS_DATA_AVAIL	(0x1 << 1)

#घोषणा DATA_ROW_MASK		0xF0
#घोषणा DATA_COLUMN_MASK	0x0F

#घोषणा ROW_SHIFT		4

काष्ठा spear_kbd अणु
	काष्ठा input_dev *input;
	व्योम __iomem *io_base;
	काष्ठा clk *clk;
	अचिन्हित पूर्णांक irq;
	अचिन्हित पूर्णांक mode;
	अचिन्हित पूर्णांक suspended_rate;
	अचिन्हित लघु last_key;
	अचिन्हित लघु keycodes[NUM_ROWS * NUM_COLS];
	bool rep;
	bool irq_wake_enabled;
	u32 mode_ctl_reg;
पूर्ण;

अटल irqवापस_t spear_kbd_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा spear_kbd *kbd = dev_id;
	काष्ठा input_dev *input = kbd->input;
	अचिन्हित पूर्णांक key;
	u32 sts, val;

	sts = पढ़ोl_relaxed(kbd->io_base + STATUS_REG);
	अगर (!(sts & STATUS_DATA_AVAIL))
		वापस IRQ_NONE;

	अगर (kbd->last_key != KEY_RESERVED) अणु
		input_report_key(input, kbd->last_key, 0);
		kbd->last_key = KEY_RESERVED;
	पूर्ण

	/* following पढ़ोs active (row, col) pair */
	val = पढ़ोl_relaxed(kbd->io_base + DATA_REG) &
		(DATA_ROW_MASK | DATA_COLUMN_MASK);
	key = kbd->keycodes[val];

	input_event(input, EV_MSC, MSC_SCAN, val);
	input_report_key(input, key, 1);
	input_sync(input);

	kbd->last_key = key;

	/* clear पूर्णांकerrupt */
	ग_लिखोl_relaxed(0, kbd->io_base + STATUS_REG);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक spear_kbd_खोलो(काष्ठा input_dev *dev)
अणु
	काष्ठा spear_kbd *kbd = input_get_drvdata(dev);
	पूर्णांक error;
	u32 val;

	kbd->last_key = KEY_RESERVED;

	error = clk_enable(kbd->clk);
	अगर (error)
		वापस error;

	/* keyboard rate to be programmed is input घड़ी (in MHz) - 1 */
	val = clk_get_rate(kbd->clk) / 1000000 - 1;
	val = (val & MODE_CTL_PCLK_FREQ_MSK) << MODE_CTL_PCLK_FREQ_SHIFT;

	/* program keyboard */
	val = MODE_CTL_SCAN_RATE_80 | MODE_CTL_KEYBOARD | val |
		(kbd->mode << MODE_CTL_KEYNUM_SHIFT);
	ग_लिखोl_relaxed(val, kbd->io_base + MODE_CTL_REG);
	ग_लिखोl_relaxed(1, kbd->io_base + STATUS_REG);

	/* start key scan */
	val = पढ़ोl_relaxed(kbd->io_base + MODE_CTL_REG);
	val |= MODE_CTL_START_SCAN;
	ग_लिखोl_relaxed(val, kbd->io_base + MODE_CTL_REG);

	वापस 0;
पूर्ण

अटल व्योम spear_kbd_बंद(काष्ठा input_dev *dev)
अणु
	काष्ठा spear_kbd *kbd = input_get_drvdata(dev);
	u32 val;

	/* stop key scan */
	val = पढ़ोl_relaxed(kbd->io_base + MODE_CTL_REG);
	val &= ~MODE_CTL_START_SCAN;
	ग_लिखोl_relaxed(val, kbd->io_base + MODE_CTL_REG);

	clk_disable(kbd->clk);

	kbd->last_key = KEY_RESERVED;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल पूर्णांक spear_kbd_parse_dt(काष्ठा platक्रमm_device *pdev,
                                        काष्ठा spear_kbd *kbd)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	पूर्णांक error;
	u32 val, suspended_rate;

	अगर (!np) अणु
		dev_err(&pdev->dev, "Missing DT data\n");
		वापस -EINVAL;
	पूर्ण

	अगर (of_property_पढ़ो_bool(np, "autorepeat"))
		kbd->rep = true;

	अगर (of_property_पढ़ो_u32(np, "suspended_rate", &suspended_rate))
		kbd->suspended_rate = suspended_rate;

	error = of_property_पढ़ो_u32(np, "st,mode", &val);
	अगर (error) अणु
		dev_err(&pdev->dev, "DT: Invalid or missing mode\n");
		वापस error;
	पूर्ण

	kbd->mode = val;
	वापस 0;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक spear_kbd_parse_dt(काष्ठा platक्रमm_device *pdev,
				     काष्ठा spear_kbd *kbd)
अणु
	वापस -ENOSYS;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक spear_kbd_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा kbd_platक्रमm_data *pdata = dev_get_platdata(&pdev->dev);
	स्थिर काष्ठा matrix_keymap_data *keymap = pdata ? pdata->keymap : शून्य;
	काष्ठा spear_kbd *kbd;
	काष्ठा input_dev *input_dev;
	काष्ठा resource *res;
	पूर्णांक irq;
	पूर्णांक error;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	kbd = devm_kzalloc(&pdev->dev, माप(*kbd), GFP_KERNEL);
	अगर (!kbd) अणु
		dev_err(&pdev->dev, "not enough memory for driver data\n");
		वापस -ENOMEM;
	पूर्ण

	input_dev = devm_input_allocate_device(&pdev->dev);
	अगर (!input_dev) अणु
		dev_err(&pdev->dev, "unable to allocate input device\n");
		वापस -ENOMEM;
	पूर्ण

	kbd->input = input_dev;
	kbd->irq = irq;

	अगर (!pdata) अणु
		error = spear_kbd_parse_dt(pdev, kbd);
		अगर (error)
			वापस error;
	पूर्ण अन्यथा अणु
		kbd->mode = pdata->mode;
		kbd->rep = pdata->rep;
		kbd->suspended_rate = pdata->suspended_rate;
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	kbd->io_base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(kbd->io_base))
		वापस PTR_ERR(kbd->io_base);

	kbd->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(kbd->clk))
		वापस PTR_ERR(kbd->clk);

	input_dev->name = "Spear Keyboard";
	input_dev->phys = "keyboard/input0";
	input_dev->id.bustype = BUS_HOST;
	input_dev->id.venकरोr = 0x0001;
	input_dev->id.product = 0x0001;
	input_dev->id.version = 0x0100;
	input_dev->खोलो = spear_kbd_खोलो;
	input_dev->बंद = spear_kbd_बंद;

	error = matrix_keypad_build_keymap(keymap, शून्य, NUM_ROWS, NUM_COLS,
					   kbd->keycodes, input_dev);
	अगर (error) अणु
		dev_err(&pdev->dev, "Failed to build keymap\n");
		वापस error;
	पूर्ण

	अगर (kbd->rep)
		__set_bit(EV_REP, input_dev->evbit);
	input_set_capability(input_dev, EV_MSC, MSC_SCAN);

	input_set_drvdata(input_dev, kbd);

	error = devm_request_irq(&pdev->dev, irq, spear_kbd_पूर्णांकerrupt, 0,
			"keyboard", kbd);
	अगर (error) अणु
		dev_err(&pdev->dev, "request_irq failed\n");
		वापस error;
	पूर्ण

	error = clk_prepare(kbd->clk);
	अगर (error)
		वापस error;

	error = input_रेजिस्टर_device(input_dev);
	अगर (error) अणु
		dev_err(&pdev->dev, "Unable to register keyboard device\n");
		clk_unprepare(kbd->clk);
		वापस error;
	पूर्ण

	device_init_wakeup(&pdev->dev, 1);
	platक्रमm_set_drvdata(pdev, kbd);

	वापस 0;
पूर्ण

अटल पूर्णांक spear_kbd_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spear_kbd *kbd = platक्रमm_get_drvdata(pdev);

	input_unरेजिस्टर_device(kbd->input);
	clk_unprepare(kbd->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused spear_kbd_suspend(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा spear_kbd *kbd = platक्रमm_get_drvdata(pdev);
	काष्ठा input_dev *input_dev = kbd->input;
	अचिन्हित पूर्णांक rate = 0, mode_ctl_reg, val;

	mutex_lock(&input_dev->mutex);

	/* explicitly enable घड़ी as we may program device */
	clk_enable(kbd->clk);

	mode_ctl_reg = पढ़ोl_relaxed(kbd->io_base + MODE_CTL_REG);

	अगर (device_may_wakeup(&pdev->dev)) अणु
		अगर (!enable_irq_wake(kbd->irq))
			kbd->irq_wake_enabled = true;

		/*
		 * reprogram the keyboard operating frequency as on some
		 * platक्रमm it may change during प्रणाली suspended
		 */
		अगर (kbd->suspended_rate)
			rate = kbd->suspended_rate / 1000000 - 1;
		अन्यथा
			rate = clk_get_rate(kbd->clk) / 1000000 - 1;

		val = mode_ctl_reg &
			~(MODE_CTL_PCLK_FREQ_MSK << MODE_CTL_PCLK_FREQ_SHIFT);
		val |= (rate & MODE_CTL_PCLK_FREQ_MSK)
			<< MODE_CTL_PCLK_FREQ_SHIFT;
		ग_लिखोl_relaxed(val, kbd->io_base + MODE_CTL_REG);

	पूर्ण अन्यथा अणु
		अगर (input_device_enabled(input_dev)) अणु
			ग_लिखोl_relaxed(mode_ctl_reg & ~MODE_CTL_START_SCAN,
					kbd->io_base + MODE_CTL_REG);
			clk_disable(kbd->clk);
		पूर्ण
	पूर्ण

	/* store current configuration */
	अगर (input_device_enabled(input_dev))
		kbd->mode_ctl_reg = mode_ctl_reg;

	/* restore previous clk state */
	clk_disable(kbd->clk);

	mutex_unlock(&input_dev->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused spear_kbd_resume(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा spear_kbd *kbd = platक्रमm_get_drvdata(pdev);
	काष्ठा input_dev *input_dev = kbd->input;

	mutex_lock(&input_dev->mutex);

	अगर (device_may_wakeup(&pdev->dev)) अणु
		अगर (kbd->irq_wake_enabled) अणु
			kbd->irq_wake_enabled = false;
			disable_irq_wake(kbd->irq);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (input_device_enabled(input_dev))
			clk_enable(kbd->clk);
	पूर्ण

	/* restore current configuration */
	अगर (input_device_enabled(input_dev))
		ग_लिखोl_relaxed(kbd->mode_ctl_reg, kbd->io_base + MODE_CTL_REG);

	mutex_unlock(&input_dev->mutex);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(spear_kbd_pm_ops, spear_kbd_suspend, spear_kbd_resume);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id spear_kbd_id_table[] = अणु
	अणु .compatible = "st,spear300-kbd" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, spear_kbd_id_table);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver spear_kbd_driver = अणु
	.probe		= spear_kbd_probe,
	.हटाओ		= spear_kbd_हटाओ,
	.driver		= अणु
		.name	= "keyboard",
		.pm	= &spear_kbd_pm_ops,
		.of_match_table = of_match_ptr(spear_kbd_id_table),
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(spear_kbd_driver);

MODULE_AUTHOR("Rajeev Kumar");
MODULE_DESCRIPTION("SPEAr Keyboard Driver");
MODULE_LICENSE("GPL");
