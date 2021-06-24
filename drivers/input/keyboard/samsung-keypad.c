<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Samsung keypad driver
 *
 * Copyright (C) 2010 Samsung Electronics Co.Ltd
 * Author: Joonyoung Shim <jy0922.shim@samsung.com>
 * Author: Donghwa Lee <dh09.lee@samsung.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/input.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>
#समावेश <linux/sched.h>
#समावेश <linux/input/samsung-keypad.h>

#घोषणा SAMSUNG_KEYIFCON			0x00
#घोषणा SAMSUNG_KEYIFSTSCLR			0x04
#घोषणा SAMSUNG_KEYIFCOL			0x08
#घोषणा SAMSUNG_KEYIFROW			0x0c
#घोषणा SAMSUNG_KEYIFFC				0x10

/* SAMSUNG_KEYIFCON */
#घोषणा SAMSUNG_KEYIFCON_INT_F_EN		(1 << 0)
#घोषणा SAMSUNG_KEYIFCON_INT_R_EN		(1 << 1)
#घोषणा SAMSUNG_KEYIFCON_DF_EN			(1 << 2)
#घोषणा SAMSUNG_KEYIFCON_FC_EN			(1 << 3)
#घोषणा SAMSUNG_KEYIFCON_WAKEUPEN		(1 << 4)

/* SAMSUNG_KEYIFSTSCLR */
#घोषणा SAMSUNG_KEYIFSTSCLR_P_INT_MASK		(0xff << 0)
#घोषणा SAMSUNG_KEYIFSTSCLR_R_INT_MASK		(0xff << 8)
#घोषणा SAMSUNG_KEYIFSTSCLR_R_INT_OFFSET	8
#घोषणा S5PV210_KEYIFSTSCLR_P_INT_MASK		(0x3fff << 0)
#घोषणा S5PV210_KEYIFSTSCLR_R_INT_MASK		(0x3fff << 16)
#घोषणा S5PV210_KEYIFSTSCLR_R_INT_OFFSET	16

/* SAMSUNG_KEYIFCOL */
#घोषणा SAMSUNG_KEYIFCOL_MASK			(0xff << 0)
#घोषणा S5PV210_KEYIFCOLEN_MASK			(0xff << 8)

/* SAMSUNG_KEYIFROW */
#घोषणा SAMSUNG_KEYIFROW_MASK			(0xff << 0)
#घोषणा S5PV210_KEYIFROW_MASK			(0x3fff << 0)

/* SAMSUNG_KEYIFFC */
#घोषणा SAMSUNG_KEYIFFC_MASK			(0x3ff << 0)

क्रमागत samsung_keypad_type अणु
	KEYPAD_TYPE_SAMSUNG,
	KEYPAD_TYPE_S5PV210,
पूर्ण;

काष्ठा samsung_keypad अणु
	काष्ठा input_dev *input_dev;
	काष्ठा platक्रमm_device *pdev;
	काष्ठा clk *clk;
	व्योम __iomem *base;
	रुको_queue_head_t रुको;
	bool stopped;
	bool wake_enabled;
	पूर्णांक irq;
	क्रमागत samsung_keypad_type type;
	अचिन्हित पूर्णांक row_shअगरt;
	अचिन्हित पूर्णांक rows;
	अचिन्हित पूर्णांक cols;
	अचिन्हित पूर्णांक row_state[SAMSUNG_MAX_COLS];
	अचिन्हित लघु keycodes[];
पूर्ण;

अटल व्योम samsung_keypad_scan(काष्ठा samsung_keypad *keypad,
				अचिन्हित पूर्णांक *row_state)
अणु
	अचिन्हित पूर्णांक col;
	अचिन्हित पूर्णांक val;

	क्रम (col = 0; col < keypad->cols; col++) अणु
		अगर (keypad->type == KEYPAD_TYPE_S5PV210) अणु
			val = S5PV210_KEYIFCOLEN_MASK;
			val &= ~(1 << col) << 8;
		पूर्ण अन्यथा अणु
			val = SAMSUNG_KEYIFCOL_MASK;
			val &= ~(1 << col);
		पूर्ण

		ग_लिखोl(val, keypad->base + SAMSUNG_KEYIFCOL);
		mdelay(1);

		val = पढ़ोl(keypad->base + SAMSUNG_KEYIFROW);
		row_state[col] = ~val & ((1 << keypad->rows) - 1);
	पूर्ण

	/* KEYIFCOL reg clear */
	ग_लिखोl(0, keypad->base + SAMSUNG_KEYIFCOL);
पूर्ण

अटल bool samsung_keypad_report(काष्ठा samsung_keypad *keypad,
				  अचिन्हित पूर्णांक *row_state)
अणु
	काष्ठा input_dev *input_dev = keypad->input_dev;
	अचिन्हित पूर्णांक changed;
	अचिन्हित पूर्णांक pressed;
	अचिन्हित पूर्णांक key_करोwn = 0;
	अचिन्हित पूर्णांक val;
	अचिन्हित पूर्णांक col, row;

	क्रम (col = 0; col < keypad->cols; col++) अणु
		changed = row_state[col] ^ keypad->row_state[col];
		key_करोwn |= row_state[col];
		अगर (!changed)
			जारी;

		क्रम (row = 0; row < keypad->rows; row++) अणु
			अगर (!(changed & (1 << row)))
				जारी;

			pressed = row_state[col] & (1 << row);

			dev_dbg(&keypad->input_dev->dev,
				"key %s, row: %d, col: %d\n",
				pressed ? "pressed" : "released", row, col);

			val = MATRIX_SCAN_CODE(row, col, keypad->row_shअगरt);

			input_event(input_dev, EV_MSC, MSC_SCAN, val);
			input_report_key(input_dev,
					keypad->keycodes[val], pressed);
		पूर्ण
		input_sync(keypad->input_dev);
	पूर्ण

	स_नकल(keypad->row_state, row_state, माप(keypad->row_state));

	वापस key_करोwn;
पूर्ण

अटल irqवापस_t samsung_keypad_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा samsung_keypad *keypad = dev_id;
	अचिन्हित पूर्णांक row_state[SAMSUNG_MAX_COLS];
	bool key_करोwn;

	pm_runसमय_get_sync(&keypad->pdev->dev);

	करो अणु
		पढ़ोl(keypad->base + SAMSUNG_KEYIFSTSCLR);
		/* Clear पूर्णांकerrupt. */
		ग_लिखोl(~0x0, keypad->base + SAMSUNG_KEYIFSTSCLR);

		samsung_keypad_scan(keypad, row_state);

		key_करोwn = samsung_keypad_report(keypad, row_state);
		अगर (key_करोwn)
			रुको_event_समयout(keypad->रुको, keypad->stopped,
					   msecs_to_jअगरfies(50));

	पूर्ण जबतक (key_करोwn && !keypad->stopped);

	pm_runसमय_put(&keypad->pdev->dev);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम samsung_keypad_start(काष्ठा samsung_keypad *keypad)
अणु
	अचिन्हित पूर्णांक val;

	pm_runसमय_get_sync(&keypad->pdev->dev);

	/* Tell IRQ thपढ़ो that it may poll the device. */
	keypad->stopped = false;

	clk_enable(keypad->clk);

	/* Enable पूर्णांकerrupt bits. */
	val = पढ़ोl(keypad->base + SAMSUNG_KEYIFCON);
	val |= SAMSUNG_KEYIFCON_INT_F_EN | SAMSUNG_KEYIFCON_INT_R_EN;
	ग_लिखोl(val, keypad->base + SAMSUNG_KEYIFCON);

	/* KEYIFCOL reg clear. */
	ग_लिखोl(0, keypad->base + SAMSUNG_KEYIFCOL);

	pm_runसमय_put(&keypad->pdev->dev);
पूर्ण

अटल व्योम samsung_keypad_stop(काष्ठा samsung_keypad *keypad)
अणु
	अचिन्हित पूर्णांक val;

	pm_runसमय_get_sync(&keypad->pdev->dev);

	/* Signal IRQ thपढ़ो to stop polling and disable the handler. */
	keypad->stopped = true;
	wake_up(&keypad->रुको);
	disable_irq(keypad->irq);

	/* Clear पूर्णांकerrupt. */
	ग_लिखोl(~0x0, keypad->base + SAMSUNG_KEYIFSTSCLR);

	/* Disable पूर्णांकerrupt bits. */
	val = पढ़ोl(keypad->base + SAMSUNG_KEYIFCON);
	val &= ~(SAMSUNG_KEYIFCON_INT_F_EN | SAMSUNG_KEYIFCON_INT_R_EN);
	ग_लिखोl(val, keypad->base + SAMSUNG_KEYIFCON);

	clk_disable(keypad->clk);

	/*
	 * Now that chip should not generate पूर्णांकerrupts we can safely
	 * re-enable the handler.
	 */
	enable_irq(keypad->irq);

	pm_runसमय_put(&keypad->pdev->dev);
पूर्ण

अटल पूर्णांक samsung_keypad_खोलो(काष्ठा input_dev *input_dev)
अणु
	काष्ठा samsung_keypad *keypad = input_get_drvdata(input_dev);

	samsung_keypad_start(keypad);

	वापस 0;
पूर्ण

अटल व्योम samsung_keypad_बंद(काष्ठा input_dev *input_dev)
अणु
	काष्ठा samsung_keypad *keypad = input_get_drvdata(input_dev);

	samsung_keypad_stop(keypad);
पूर्ण

#अगर_घोषित CONFIG_OF
अटल काष्ठा samsung_keypad_platdata *
samsung_keypad_parse_dt(काष्ठा device *dev)
अणु
	काष्ठा samsung_keypad_platdata *pdata;
	काष्ठा matrix_keymap_data *keymap_data;
	uपूर्णांक32_t *keymap, num_rows = 0, num_cols = 0;
	काष्ठा device_node *np = dev->of_node, *key_np;
	अचिन्हित पूर्णांक key_count;

	अगर (!np) अणु
		dev_err(dev, "missing device tree data\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	pdata = devm_kzalloc(dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata) अणु
		dev_err(dev, "could not allocate memory for platform data\n");
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	of_property_पढ़ो_u32(np, "samsung,keypad-num-rows", &num_rows);
	of_property_पढ़ो_u32(np, "samsung,keypad-num-columns", &num_cols);
	अगर (!num_rows || !num_cols) अणु
		dev_err(dev, "number of keypad rows/columns not specified\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण
	pdata->rows = num_rows;
	pdata->cols = num_cols;

	keymap_data = devm_kzalloc(dev, माप(*keymap_data), GFP_KERNEL);
	अगर (!keymap_data) अणु
		dev_err(dev, "could not allocate memory for keymap data\n");
		वापस ERR_PTR(-ENOMEM);
	पूर्ण
	pdata->keymap_data = keymap_data;

	key_count = of_get_child_count(np);
	keymap_data->keymap_size = key_count;
	keymap = devm_kसुस्मृति(dev, key_count, माप(uपूर्णांक32_t), GFP_KERNEL);
	अगर (!keymap) अणु
		dev_err(dev, "could not allocate memory for keymap\n");
		वापस ERR_PTR(-ENOMEM);
	पूर्ण
	keymap_data->keymap = keymap;

	क्रम_each_child_of_node(np, key_np) अणु
		u32 row, col, key_code;
		of_property_पढ़ो_u32(key_np, "keypad,row", &row);
		of_property_पढ़ो_u32(key_np, "keypad,column", &col);
		of_property_पढ़ो_u32(key_np, "linux,code", &key_code);
		*keymap++ = KEY(row, col, key_code);
	पूर्ण

	अगर (of_get_property(np, "linux,input-no-autorepeat", शून्य))
		pdata->no_स्वतःrepeat = true;

	pdata->wakeup = of_property_पढ़ो_bool(np, "wakeup-source") ||
			/* legacy name */
			of_property_पढ़ो_bool(np, "linux,input-wakeup");


	वापस pdata;
पूर्ण
#अन्यथा
अटल काष्ठा samsung_keypad_platdata *
samsung_keypad_parse_dt(काष्ठा device *dev)
अणु
	dev_err(dev, "no platform data defined\n");

	वापस ERR_PTR(-EINVAL);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक samsung_keypad_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा samsung_keypad_platdata *pdata;
	स्थिर काष्ठा matrix_keymap_data *keymap_data;
	काष्ठा samsung_keypad *keypad;
	काष्ठा resource *res;
	काष्ठा input_dev *input_dev;
	अचिन्हित पूर्णांक row_shअगरt;
	अचिन्हित पूर्णांक keymap_size;
	पूर्णांक error;

	pdata = dev_get_platdata(&pdev->dev);
	अगर (!pdata) अणु
		pdata = samsung_keypad_parse_dt(&pdev->dev);
		अगर (IS_ERR(pdata))
			वापस PTR_ERR(pdata);
	पूर्ण

	keymap_data = pdata->keymap_data;
	अगर (!keymap_data) अणु
		dev_err(&pdev->dev, "no keymap data defined\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!pdata->rows || pdata->rows > SAMSUNG_MAX_ROWS)
		वापस -EINVAL;

	अगर (!pdata->cols || pdata->cols > SAMSUNG_MAX_COLS)
		वापस -EINVAL;

	/* initialize the gpio */
	अगर (pdata->cfg_gpio)
		pdata->cfg_gpio(pdata->rows, pdata->cols);

	row_shअगरt = get_count_order(pdata->cols);
	keymap_size = (pdata->rows << row_shअगरt) * माप(keypad->keycodes[0]);

	keypad = devm_kzalloc(&pdev->dev, माप(*keypad) + keymap_size,
			      GFP_KERNEL);
	input_dev = devm_input_allocate_device(&pdev->dev);
	अगर (!keypad || !input_dev)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res)
		वापस -ENODEV;

	keypad->base = devm_ioremap(&pdev->dev, res->start, resource_size(res));
	अगर (!keypad->base)
		वापस -EBUSY;

	keypad->clk = devm_clk_get(&pdev->dev, "keypad");
	अगर (IS_ERR(keypad->clk)) अणु
		dev_err(&pdev->dev, "failed to get keypad clk\n");
		वापस PTR_ERR(keypad->clk);
	पूर्ण

	error = clk_prepare(keypad->clk);
	अगर (error) अणु
		dev_err(&pdev->dev, "keypad clock prepare failed\n");
		वापस error;
	पूर्ण

	keypad->input_dev = input_dev;
	keypad->pdev = pdev;
	keypad->row_shअगरt = row_shअगरt;
	keypad->rows = pdata->rows;
	keypad->cols = pdata->cols;
	keypad->stopped = true;
	init_रुकोqueue_head(&keypad->रुको);

	अगर (pdev->dev.of_node)
		keypad->type = of_device_is_compatible(pdev->dev.of_node,
					"samsung,s5pv210-keypad");
	अन्यथा
		keypad->type = platक्रमm_get_device_id(pdev)->driver_data;

	input_dev->name = pdev->name;
	input_dev->id.bustype = BUS_HOST;
	input_dev->dev.parent = &pdev->dev;

	input_dev->खोलो = samsung_keypad_खोलो;
	input_dev->बंद = samsung_keypad_बंद;

	error = matrix_keypad_build_keymap(keymap_data, शून्य,
					   pdata->rows, pdata->cols,
					   keypad->keycodes, input_dev);
	अगर (error) अणु
		dev_err(&pdev->dev, "failed to build keymap\n");
		जाओ err_unprepare_clk;
	पूर्ण

	input_set_capability(input_dev, EV_MSC, MSC_SCAN);
	अगर (!pdata->no_स्वतःrepeat)
		__set_bit(EV_REP, input_dev->evbit);

	input_set_drvdata(input_dev, keypad);

	keypad->irq = platक्रमm_get_irq(pdev, 0);
	अगर (keypad->irq < 0) अणु
		error = keypad->irq;
		जाओ err_unprepare_clk;
	पूर्ण

	error = devm_request_thपढ़ोed_irq(&pdev->dev, keypad->irq, शून्य,
					  samsung_keypad_irq, IRQF_ONESHOT,
					  dev_name(&pdev->dev), keypad);
	अगर (error) अणु
		dev_err(&pdev->dev, "failed to register keypad interrupt\n");
		जाओ err_unprepare_clk;
	पूर्ण

	device_init_wakeup(&pdev->dev, pdata->wakeup);
	platक्रमm_set_drvdata(pdev, keypad);
	pm_runसमय_enable(&pdev->dev);

	error = input_रेजिस्टर_device(keypad->input_dev);
	अगर (error)
		जाओ err_disable_runसमय_pm;

	अगर (pdev->dev.of_node) अणु
		devm_kमुक्त(&pdev->dev, (व्योम *)pdata->keymap_data->keymap);
		devm_kमुक्त(&pdev->dev, (व्योम *)pdata->keymap_data);
		devm_kमुक्त(&pdev->dev, (व्योम *)pdata);
	पूर्ण
	वापस 0;

err_disable_runसमय_pm:
	pm_runसमय_disable(&pdev->dev);
err_unprepare_clk:
	clk_unprepare(keypad->clk);
	वापस error;
पूर्ण

अटल पूर्णांक samsung_keypad_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा samsung_keypad *keypad = platक्रमm_get_drvdata(pdev);

	pm_runसमय_disable(&pdev->dev);

	input_unरेजिस्टर_device(keypad->input_dev);

	clk_unprepare(keypad->clk);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक samsung_keypad_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा samsung_keypad *keypad = platक्रमm_get_drvdata(pdev);
	अचिन्हित पूर्णांक val;
	पूर्णांक error;

	अगर (keypad->stopped)
		वापस 0;

	/* This may fail on some SoCs due to lack of controller support */
	error = enable_irq_wake(keypad->irq);
	अगर (!error)
		keypad->wake_enabled = true;

	val = पढ़ोl(keypad->base + SAMSUNG_KEYIFCON);
	val |= SAMSUNG_KEYIFCON_WAKEUPEN;
	ग_लिखोl(val, keypad->base + SAMSUNG_KEYIFCON);

	clk_disable(keypad->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक samsung_keypad_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा samsung_keypad *keypad = platक्रमm_get_drvdata(pdev);
	अचिन्हित पूर्णांक val;

	अगर (keypad->stopped)
		वापस 0;

	clk_enable(keypad->clk);

	val = पढ़ोl(keypad->base + SAMSUNG_KEYIFCON);
	val &= ~SAMSUNG_KEYIFCON_WAKEUPEN;
	ग_लिखोl(val, keypad->base + SAMSUNG_KEYIFCON);

	अगर (keypad->wake_enabled)
		disable_irq_wake(keypad->irq);

	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PM_SLEEP
अटल व्योम samsung_keypad_toggle_wakeup(काष्ठा samsung_keypad *keypad,
					 bool enable)
अणु
	अचिन्हित पूर्णांक val;

	clk_enable(keypad->clk);

	val = पढ़ोl(keypad->base + SAMSUNG_KEYIFCON);
	अगर (enable) अणु
		val |= SAMSUNG_KEYIFCON_WAKEUPEN;
		अगर (device_may_wakeup(&keypad->pdev->dev))
			enable_irq_wake(keypad->irq);
	पूर्ण अन्यथा अणु
		val &= ~SAMSUNG_KEYIFCON_WAKEUPEN;
		अगर (device_may_wakeup(&keypad->pdev->dev))
			disable_irq_wake(keypad->irq);
	पूर्ण
	ग_लिखोl(val, keypad->base + SAMSUNG_KEYIFCON);

	clk_disable(keypad->clk);
पूर्ण

अटल पूर्णांक samsung_keypad_suspend(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा samsung_keypad *keypad = platक्रमm_get_drvdata(pdev);
	काष्ठा input_dev *input_dev = keypad->input_dev;

	mutex_lock(&input_dev->mutex);

	अगर (input_device_enabled(input_dev))
		samsung_keypad_stop(keypad);

	samsung_keypad_toggle_wakeup(keypad, true);

	mutex_unlock(&input_dev->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक samsung_keypad_resume(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा samsung_keypad *keypad = platक्रमm_get_drvdata(pdev);
	काष्ठा input_dev *input_dev = keypad->input_dev;

	mutex_lock(&input_dev->mutex);

	samsung_keypad_toggle_wakeup(keypad, false);

	अगर (input_device_enabled(input_dev))
		samsung_keypad_start(keypad);

	mutex_unlock(&input_dev->mutex);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops samsung_keypad_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(samsung_keypad_suspend, samsung_keypad_resume)
	SET_RUNTIME_PM_OPS(samsung_keypad_runसमय_suspend,
			   samsung_keypad_runसमय_resume, शून्य)
पूर्ण;

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id samsung_keypad_dt_match[] = अणु
	अणु .compatible = "samsung,s3c6410-keypad" पूर्ण,
	अणु .compatible = "samsung,s5pv210-keypad" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, samsung_keypad_dt_match);
#पूर्ण_अगर

अटल स्थिर काष्ठा platक्रमm_device_id samsung_keypad_driver_ids[] = अणु
	अणु
		.name		= "samsung-keypad",
		.driver_data	= KEYPAD_TYPE_SAMSUNG,
	पूर्ण, अणु
		.name		= "s5pv210-keypad",
		.driver_data	= KEYPAD_TYPE_S5PV210,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, samsung_keypad_driver_ids);

अटल काष्ठा platक्रमm_driver samsung_keypad_driver = अणु
	.probe		= samsung_keypad_probe,
	.हटाओ		= samsung_keypad_हटाओ,
	.driver		= अणु
		.name	= "samsung-keypad",
		.of_match_table = of_match_ptr(samsung_keypad_dt_match),
		.pm	= &samsung_keypad_pm_ops,
	पूर्ण,
	.id_table	= samsung_keypad_driver_ids,
पूर्ण;
module_platक्रमm_driver(samsung_keypad_driver);

MODULE_DESCRIPTION("Samsung keypad driver");
MODULE_AUTHOR("Joonyoung Shim <jy0922.shim@samsung.com>");
MODULE_AUTHOR("Donghwa Lee <dh09.lee@samsung.com>");
MODULE_LICENSE("GPL");
