<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) ST-Ericsson SA 2010
 *
 * Author: Naveen Kumar G <naveen.gaddipati@stericsson.com> क्रम ST-Ericsson
 * Author: Sundar Iyer <sundar.iyer@stericsson.com> क्रम ST-Ericsson
 *
 * Keypad controller driver क्रम the SKE (Scroll Key Encoder) module used in
 * the Nomadik 8815 and Ux500 platक्रमms.
 */

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पन.स>
#समावेश <linux/delay.h>
#समावेश <linux/input.h>
#समावेश <linux/slab.h>
#समावेश <linux/clk.h>
#समावेश <linux/module.h>

#समावेश <linux/platक्रमm_data/keypad-nomadik-ske.h>

/* SKE_CR bits */
#घोषणा SKE_KPMLT	(0x1 << 6)
#घोषणा SKE_KPCN	(0x7 << 3)
#घोषणा SKE_KPASEN	(0x1 << 2)
#घोषणा SKE_KPASON	(0x1 << 7)

/* SKE_IMSC bits */
#घोषणा SKE_KPIMA	(0x1 << 2)

/* SKE_ICR bits */
#घोषणा SKE_KPICS	(0x1 << 3)
#घोषणा SKE_KPICA	(0x1 << 2)

/* SKE_RIS bits */
#घोषणा SKE_KPRISA	(0x1 << 2)

#घोषणा SKE_KEYPAD_ROW_SHIFT	3
#घोषणा SKE_KPD_NUM_ROWS	8
#घोषणा SKE_KPD_NUM_COLS	8

/* keypad स्वतः scan रेजिस्टरs */
#घोषणा SKE_ASR0	0x20
#घोषणा SKE_ASR1	0x24
#घोषणा SKE_ASR2	0x28
#घोषणा SKE_ASR3	0x2C

#घोषणा SKE_NUM_ASRX_REGISTERS	(4)
#घोषणा	KEY_PRESSED_DELAY	10

/**
 * काष्ठा ske_keypad  - data काष्ठाure used by keypad driver
 * @irq:	irq no
 * @reg_base:	ske रेजिस्टरs base address
 * @input:	poपूर्णांकer to input device object
 * @board:	keypad platक्रमm device
 * @keymap:	matrix scan code table क्रम keycodes
 * @clk:	घड़ी काष्ठाure poपूर्णांकer
 * @pclk:	घड़ी काष्ठाure poपूर्णांकer
 * @ske_keypad_lock: spinlock protecting the keypad पढ़ो/ग_लिखोs
 */
काष्ठा ske_keypad अणु
	पूर्णांक irq;
	व्योम __iomem *reg_base;
	काष्ठा input_dev *input;
	स्थिर काष्ठा ske_keypad_platक्रमm_data *board;
	अचिन्हित लघु keymap[SKE_KPD_NUM_ROWS * SKE_KPD_NUM_COLS];
	काष्ठा clk *clk;
	काष्ठा clk *pclk;
	spinlock_t ske_keypad_lock;
पूर्ण;

अटल व्योम ske_keypad_set_bits(काष्ठा ske_keypad *keypad, u16 addr,
		u8 mask, u8 data)
अणु
	u32 ret;

	spin_lock(&keypad->ske_keypad_lock);

	ret = पढ़ोl(keypad->reg_base + addr);
	ret &= ~mask;
	ret |= data;
	ग_लिखोl(ret, keypad->reg_base + addr);

	spin_unlock(&keypad->ske_keypad_lock);
पूर्ण

/*
 * ske_keypad_chip_init: init keypad controller configuration
 *
 * Enable Multi key press detection, स्वतः scan mode
 */
अटल पूर्णांक __init ske_keypad_chip_init(काष्ठा ske_keypad *keypad)
अणु
	u32 value;
	पूर्णांक समयout = keypad->board->debounce_ms;

	/* check SKE_RIS to be 0 */
	जबतक ((पढ़ोl(keypad->reg_base + SKE_RIS) != 0x00000000) && समयout--)
		cpu_relax();

	अगर (समयout == -1)
		वापस -EINVAL;

	/*
	 * set debounce value
	 * keypad dbounce is configured in DBCR[15:8]
	 * dbounce value in steps of 32/32.768 ms
	 */
	spin_lock(&keypad->ske_keypad_lock);
	value = पढ़ोl(keypad->reg_base + SKE_DBCR);
	value = value & 0xff;
	value |= ((keypad->board->debounce_ms * 32000)/32768) << 8;
	ग_लिखोl(value, keypad->reg_base + SKE_DBCR);
	spin_unlock(&keypad->ske_keypad_lock);

	/* enable multi key detection */
	ske_keypad_set_bits(keypad, SKE_CR, 0x0, SKE_KPMLT);

	/*
	 * set up the number of columns
	 * KPCN[5:3] defines no. of keypad columns to be स्वतः scanned
	 */
	value = (keypad->board->kcol - 1) << 3;
	ske_keypad_set_bits(keypad, SKE_CR, SKE_KPCN, value);

	/* clear keypad पूर्णांकerrupt क्रम स्वतः(and pending SW) scans */
	ske_keypad_set_bits(keypad, SKE_ICR, 0x0, SKE_KPICA | SKE_KPICS);

	/* un-mask keypad पूर्णांकerrupts */
	ske_keypad_set_bits(keypad, SKE_IMSC, 0x0, SKE_KPIMA);

	/* enable स्वतःmatic scan */
	ske_keypad_set_bits(keypad, SKE_CR, 0x0, SKE_KPASEN);

	वापस 0;
पूर्ण

अटल व्योम ske_keypad_report(काष्ठा ske_keypad *keypad, u8 status, पूर्णांक col)
अणु
	पूर्णांक row = 0, code, pos;
	काष्ठा input_dev *input = keypad->input;
	u32 ske_ris;
	पूर्णांक key_pressed;
	पूर्णांक num_of_rows;

	/* find out the row */
	num_of_rows = hweight8(status);
	करो अणु
		pos = __ffs(status);
		row = pos;
		status &= ~(1 << pos);

		code = MATRIX_SCAN_CODE(row, col, SKE_KEYPAD_ROW_SHIFT);
		ske_ris = पढ़ोl(keypad->reg_base + SKE_RIS);
		key_pressed = ske_ris & SKE_KPRISA;

		input_event(input, EV_MSC, MSC_SCAN, code);
		input_report_key(input, keypad->keymap[code], key_pressed);
		input_sync(input);
		num_of_rows--;
	पूर्ण जबतक (num_of_rows);
पूर्ण

अटल व्योम ske_keypad_पढ़ो_data(काष्ठा ske_keypad *keypad)
अणु
	u8 status;
	पूर्णांक col = 0;
	पूर्णांक ske_asr, i;

	/*
	 * Read the स्वतः scan रेजिस्टरs
	 *
	 * Each SKE_ASRx (x=0 to x=3) contains two row values.
	 * lower byte contains row value क्रम column 2*x,
	 * upper byte contains row value क्रम column 2*x + 1
	 */
	क्रम (i = 0; i < SKE_NUM_ASRX_REGISTERS; i++) अणु
		ske_asr = पढ़ोl(keypad->reg_base + SKE_ASR0 + (4 * i));
		अगर (!ske_asr)
			जारी;

		/* now that ASRx is zero, find out the coloumn x and row y */
		status = ske_asr & 0xff;
		अगर (status) अणु
			col = i * 2;
			ske_keypad_report(keypad, status, col);
		पूर्ण
		status = (ske_asr & 0xff00) >> 8;
		अगर (status) अणु
			col = (i * 2) + 1;
			ske_keypad_report(keypad, status, col);
		पूर्ण
	पूर्ण
पूर्ण

अटल irqवापस_t ske_keypad_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा ske_keypad *keypad = dev_id;
	पूर्णांक समयout = keypad->board->debounce_ms;

	/* disable स्वतः scan पूर्णांकerrupt; mask the पूर्णांकerrupt generated */
	ske_keypad_set_bits(keypad, SKE_IMSC, ~SKE_KPIMA, 0x0);
	ske_keypad_set_bits(keypad, SKE_ICR, 0x0, SKE_KPICA);

	जबतक ((पढ़ोl(keypad->reg_base + SKE_CR) & SKE_KPASON) && --समयout)
		cpu_relax();

	/* SKEx रेजिस्टरs are stable and can be पढ़ो */
	ske_keypad_पढ़ो_data(keypad);

	/* रुको until raw पूर्णांकerrupt is clear */
	जबतक ((पढ़ोl(keypad->reg_base + SKE_RIS)) && --समयout)
		msleep(KEY_PRESSED_DELAY);

	/* enable स्वतः scan पूर्णांकerrupts */
	ske_keypad_set_bits(keypad, SKE_IMSC, 0x0, SKE_KPIMA);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक __init ske_keypad_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा ske_keypad_platक्रमm_data *plat =
			dev_get_platdata(&pdev->dev);
	काष्ठा ske_keypad *keypad;
	काष्ठा input_dev *input;
	काष्ठा resource *res;
	पूर्णांक irq;
	पूर्णांक error;

	अगर (!plat) अणु
		dev_err(&pdev->dev, "invalid keypad platform data\n");
		वापस -EINVAL;
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस -EINVAL;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res) अणु
		dev_err(&pdev->dev, "missing platform resources\n");
		वापस -EINVAL;
	पूर्ण

	keypad = kzalloc(माप(काष्ठा ske_keypad), GFP_KERNEL);
	input = input_allocate_device();
	अगर (!keypad || !input) अणु
		dev_err(&pdev->dev, "failed to allocate keypad memory\n");
		error = -ENOMEM;
		जाओ err_मुक्त_mem;
	पूर्ण

	keypad->irq = irq;
	keypad->board = plat;
	keypad->input = input;
	spin_lock_init(&keypad->ske_keypad_lock);

	अगर (!request_mem_region(res->start, resource_size(res), pdev->name)) अणु
		dev_err(&pdev->dev, "failed to request I/O memory\n");
		error = -EBUSY;
		जाओ err_मुक्त_mem;
	पूर्ण

	keypad->reg_base = ioremap(res->start, resource_size(res));
	अगर (!keypad->reg_base) अणु
		dev_err(&pdev->dev, "failed to remap I/O memory\n");
		error = -ENXIO;
		जाओ err_मुक्त_mem_region;
	पूर्ण

	keypad->pclk = clk_get(&pdev->dev, "apb_pclk");
	अगर (IS_ERR(keypad->pclk)) अणु
		dev_err(&pdev->dev, "failed to get pclk\n");
		error = PTR_ERR(keypad->pclk);
		जाओ err_iounmap;
	पूर्ण

	keypad->clk = clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(keypad->clk)) अणु
		dev_err(&pdev->dev, "failed to get clk\n");
		error = PTR_ERR(keypad->clk);
		जाओ err_pclk;
	पूर्ण

	input->id.bustype = BUS_HOST;
	input->name = "ux500-ske-keypad";
	input->dev.parent = &pdev->dev;

	error = matrix_keypad_build_keymap(plat->keymap_data, शून्य,
					   SKE_KPD_NUM_ROWS, SKE_KPD_NUM_COLS,
					   keypad->keymap, input);
	अगर (error) अणु
		dev_err(&pdev->dev, "Failed to build keymap\n");
		जाओ err_clk;
	पूर्ण

	input_set_capability(input, EV_MSC, MSC_SCAN);
	अगर (!plat->no_स्वतःrepeat)
		__set_bit(EV_REP, input->evbit);

	error = clk_prepare_enable(keypad->pclk);
	अगर (error) अणु
		dev_err(&pdev->dev, "Failed to prepare/enable pclk\n");
		जाओ err_clk;
	पूर्ण

	error = clk_prepare_enable(keypad->clk);
	अगर (error) अणु
		dev_err(&pdev->dev, "Failed to prepare/enable clk\n");
		जाओ err_pclk_disable;
	पूर्ण


	/* go through board initialization helpers */
	अगर (keypad->board->init)
		keypad->board->init();

	error = ske_keypad_chip_init(keypad);
	अगर (error) अणु
		dev_err(&pdev->dev, "unable to init keypad hardware\n");
		जाओ err_clk_disable;
	पूर्ण

	error = request_thपढ़ोed_irq(keypad->irq, शून्य, ske_keypad_irq,
				     IRQF_ONESHOT, "ske-keypad", keypad);
	अगर (error) अणु
		dev_err(&pdev->dev, "allocate irq %d failed\n", keypad->irq);
		जाओ err_clk_disable;
	पूर्ण

	error = input_रेजिस्टर_device(input);
	अगर (error) अणु
		dev_err(&pdev->dev,
				"unable to register input device: %d\n", error);
		जाओ err_मुक्त_irq;
	पूर्ण

	अगर (plat->wakeup_enable)
		device_init_wakeup(&pdev->dev, true);

	platक्रमm_set_drvdata(pdev, keypad);

	वापस 0;

err_मुक्त_irq:
	मुक्त_irq(keypad->irq, keypad);
err_clk_disable:
	clk_disable_unprepare(keypad->clk);
err_pclk_disable:
	clk_disable_unprepare(keypad->pclk);
err_clk:
	clk_put(keypad->clk);
err_pclk:
	clk_put(keypad->pclk);
err_iounmap:
	iounmap(keypad->reg_base);
err_मुक्त_mem_region:
	release_mem_region(res->start, resource_size(res));
err_मुक्त_mem:
	input_मुक्त_device(input);
	kमुक्त(keypad);
	वापस error;
पूर्ण

अटल पूर्णांक ske_keypad_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ske_keypad *keypad = platक्रमm_get_drvdata(pdev);
	काष्ठा resource *res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);

	मुक्त_irq(keypad->irq, keypad);

	input_unरेजिस्टर_device(keypad->input);

	clk_disable_unprepare(keypad->clk);
	clk_put(keypad->clk);

	अगर (keypad->board->निकास)
		keypad->board->निकास();

	iounmap(keypad->reg_base);
	release_mem_region(res->start, resource_size(res));
	kमुक्त(keypad);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक ske_keypad_suspend(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा ske_keypad *keypad = platक्रमm_get_drvdata(pdev);
	पूर्णांक irq = platक्रमm_get_irq(pdev, 0);

	अगर (device_may_wakeup(dev))
		enable_irq_wake(irq);
	अन्यथा
		ske_keypad_set_bits(keypad, SKE_IMSC, ~SKE_KPIMA, 0x0);

	वापस 0;
पूर्ण

अटल पूर्णांक ske_keypad_resume(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा ske_keypad *keypad = platक्रमm_get_drvdata(pdev);
	पूर्णांक irq = platक्रमm_get_irq(pdev, 0);

	अगर (device_may_wakeup(dev))
		disable_irq_wake(irq);
	अन्यथा
		ske_keypad_set_bits(keypad, SKE_IMSC, 0x0, SKE_KPIMA);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(ske_keypad_dev_pm_ops,
			 ske_keypad_suspend, ske_keypad_resume);

अटल काष्ठा platक्रमm_driver ske_keypad_driver = अणु
	.driver = अणु
		.name = "nmk-ske-keypad",
		.pm = &ske_keypad_dev_pm_ops,
	पूर्ण,
	.हटाओ = ske_keypad_हटाओ,
पूर्ण;

module_platक्रमm_driver_probe(ske_keypad_driver, ske_keypad_probe);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Naveen Kumar <naveen.gaddipati@stericsson.com> / Sundar Iyer <sundar.iyer@stericsson.com>");
MODULE_DESCRIPTION("Nomadik Scroll-Key-Encoder Keypad Driver");
MODULE_ALIAS("platform:nomadik-ske-keypad");
