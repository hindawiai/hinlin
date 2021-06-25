<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  GPIO driven matrix keyboard driver
 *
 *  Copyright (c) 2008 Marek Vasut <marek.vasut@gmail.com>
 *
 *  Based on corgikbd.c
 */

#समावेश <linux/types.h>
#समावेश <linux/delay.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/input.h>
#समावेश <linux/irq.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/module.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/input/matrix_keypad.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/of_platक्रमm.h>

काष्ठा matrix_keypad अणु
	स्थिर काष्ठा matrix_keypad_platक्रमm_data *pdata;
	काष्ठा input_dev *input_dev;
	अचिन्हित पूर्णांक row_shअगरt;

	DECLARE_BITMAP(disabled_gpios, MATRIX_MAX_ROWS);

	uपूर्णांक32_t last_key_state[MATRIX_MAX_COLS];
	काष्ठा delayed_work work;
	spinlock_t lock;
	bool scan_pending;
	bool stopped;
	bool gpio_all_disabled;
पूर्ण;

/*
 * NOTE: If drive_inactive_cols is false, then the GPIO has to be put पूर्णांकo
 * HiZ when de-activated to cause minmal side effect when scanning other
 * columns. In that हाल it is configured here to be input, otherwise it is
 * driven with the inactive value.
 */
अटल व्योम __activate_col(स्थिर काष्ठा matrix_keypad_platक्रमm_data *pdata,
			   पूर्णांक col, bool on)
अणु
	bool level_on = !pdata->active_low;

	अगर (on) अणु
		gpio_direction_output(pdata->col_gpios[col], level_on);
	पूर्ण अन्यथा अणु
		gpio_set_value_cansleep(pdata->col_gpios[col], !level_on);
		अगर (!pdata->drive_inactive_cols)
			gpio_direction_input(pdata->col_gpios[col]);
	पूर्ण
पूर्ण

अटल व्योम activate_col(स्थिर काष्ठा matrix_keypad_platक्रमm_data *pdata,
			 पूर्णांक col, bool on)
अणु
	__activate_col(pdata, col, on);

	अगर (on && pdata->col_scan_delay_us)
		udelay(pdata->col_scan_delay_us);
पूर्ण

अटल व्योम activate_all_cols(स्थिर काष्ठा matrix_keypad_platक्रमm_data *pdata,
			      bool on)
अणु
	पूर्णांक col;

	क्रम (col = 0; col < pdata->num_col_gpios; col++)
		__activate_col(pdata, col, on);
पूर्ण

अटल bool row_निश्चितed(स्थिर काष्ठा matrix_keypad_platक्रमm_data *pdata,
			 पूर्णांक row)
अणु
	वापस gpio_get_value_cansleep(pdata->row_gpios[row]) ?
			!pdata->active_low : pdata->active_low;
पूर्ण

अटल व्योम enable_row_irqs(काष्ठा matrix_keypad *keypad)
अणु
	स्थिर काष्ठा matrix_keypad_platक्रमm_data *pdata = keypad->pdata;
	पूर्णांक i;

	अगर (pdata->clustered_irq > 0)
		enable_irq(pdata->clustered_irq);
	अन्यथा अणु
		क्रम (i = 0; i < pdata->num_row_gpios; i++)
			enable_irq(gpio_to_irq(pdata->row_gpios[i]));
	पूर्ण
पूर्ण

अटल व्योम disable_row_irqs(काष्ठा matrix_keypad *keypad)
अणु
	स्थिर काष्ठा matrix_keypad_platक्रमm_data *pdata = keypad->pdata;
	पूर्णांक i;

	अगर (pdata->clustered_irq > 0)
		disable_irq_nosync(pdata->clustered_irq);
	अन्यथा अणु
		क्रम (i = 0; i < pdata->num_row_gpios; i++)
			disable_irq_nosync(gpio_to_irq(pdata->row_gpios[i]));
	पूर्ण
पूर्ण

/*
 * This माला_लो the keys from keyboard and reports it to input subप्रणाली
 */
अटल व्योम matrix_keypad_scan(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा matrix_keypad *keypad =
		container_of(work, काष्ठा matrix_keypad, work.work);
	काष्ठा input_dev *input_dev = keypad->input_dev;
	स्थिर अचिन्हित लघु *keycodes = input_dev->keycode;
	स्थिर काष्ठा matrix_keypad_platक्रमm_data *pdata = keypad->pdata;
	uपूर्णांक32_t new_state[MATRIX_MAX_COLS];
	पूर्णांक row, col, code;

	/* de-activate all columns क्रम scanning */
	activate_all_cols(pdata, false);

	स_रखो(new_state, 0, माप(new_state));

	/* निश्चित each column and पढ़ो the row status out */
	क्रम (col = 0; col < pdata->num_col_gpios; col++) अणु

		activate_col(pdata, col, true);

		क्रम (row = 0; row < pdata->num_row_gpios; row++)
			new_state[col] |=
				row_निश्चितed(pdata, row) ? (1 << row) : 0;

		activate_col(pdata, col, false);
	पूर्ण

	क्रम (col = 0; col < pdata->num_col_gpios; col++) अणु
		uपूर्णांक32_t bits_changed;

		bits_changed = keypad->last_key_state[col] ^ new_state[col];
		अगर (bits_changed == 0)
			जारी;

		क्रम (row = 0; row < pdata->num_row_gpios; row++) अणु
			अगर ((bits_changed & (1 << row)) == 0)
				जारी;

			code = MATRIX_SCAN_CODE(row, col, keypad->row_shअगरt);
			input_event(input_dev, EV_MSC, MSC_SCAN, code);
			input_report_key(input_dev,
					 keycodes[code],
					 new_state[col] & (1 << row));
		पूर्ण
	पूर्ण
	input_sync(input_dev);

	स_नकल(keypad->last_key_state, new_state, माप(new_state));

	activate_all_cols(pdata, true);

	/* Enable IRQs again */
	spin_lock_irq(&keypad->lock);
	keypad->scan_pending = false;
	enable_row_irqs(keypad);
	spin_unlock_irq(&keypad->lock);
पूर्ण

अटल irqवापस_t matrix_keypad_पूर्णांकerrupt(पूर्णांक irq, व्योम *id)
अणु
	काष्ठा matrix_keypad *keypad = id;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&keypad->lock, flags);

	/*
	 * See अगर another IRQ beaten us to it and scheduled the
	 * scan alपढ़ोy. In that हाल we should not try to
	 * disable IRQs again.
	 */
	अगर (unlikely(keypad->scan_pending || keypad->stopped))
		जाओ out;

	disable_row_irqs(keypad);
	keypad->scan_pending = true;
	schedule_delayed_work(&keypad->work,
		msecs_to_jअगरfies(keypad->pdata->debounce_ms));

out:
	spin_unlock_irqrestore(&keypad->lock, flags);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक matrix_keypad_start(काष्ठा input_dev *dev)
अणु
	काष्ठा matrix_keypad *keypad = input_get_drvdata(dev);

	keypad->stopped = false;
	mb();

	/*
	 * Schedule an immediate key scan to capture current key state;
	 * columns will be activated and IRQs be enabled after the scan.
	 */
	schedule_delayed_work(&keypad->work, 0);

	वापस 0;
पूर्ण

अटल व्योम matrix_keypad_stop(काष्ठा input_dev *dev)
अणु
	काष्ठा matrix_keypad *keypad = input_get_drvdata(dev);

	spin_lock_irq(&keypad->lock);
	keypad->stopped = true;
	spin_unlock_irq(&keypad->lock);

	flush_delayed_work(&keypad->work);
	/*
	 * matrix_keypad_scan() will leave IRQs enabled;
	 * we should disable them now.
	 */
	disable_row_irqs(keypad);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल व्योम matrix_keypad_enable_wakeup(काष्ठा matrix_keypad *keypad)
अणु
	स्थिर काष्ठा matrix_keypad_platक्रमm_data *pdata = keypad->pdata;
	अचिन्हित पूर्णांक gpio;
	पूर्णांक i;

	अगर (pdata->clustered_irq > 0) अणु
		अगर (enable_irq_wake(pdata->clustered_irq) == 0)
			keypad->gpio_all_disabled = true;
	पूर्ण अन्यथा अणु

		क्रम (i = 0; i < pdata->num_row_gpios; i++) अणु
			अगर (!test_bit(i, keypad->disabled_gpios)) अणु
				gpio = pdata->row_gpios[i];

				अगर (enable_irq_wake(gpio_to_irq(gpio)) == 0)
					__set_bit(i, keypad->disabled_gpios);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम matrix_keypad_disable_wakeup(काष्ठा matrix_keypad *keypad)
अणु
	स्थिर काष्ठा matrix_keypad_platक्रमm_data *pdata = keypad->pdata;
	अचिन्हित पूर्णांक gpio;
	पूर्णांक i;

	अगर (pdata->clustered_irq > 0) अणु
		अगर (keypad->gpio_all_disabled) अणु
			disable_irq_wake(pdata->clustered_irq);
			keypad->gpio_all_disabled = false;
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < pdata->num_row_gpios; i++) अणु
			अगर (test_and_clear_bit(i, keypad->disabled_gpios)) अणु
				gpio = pdata->row_gpios[i];
				disable_irq_wake(gpio_to_irq(gpio));
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक matrix_keypad_suspend(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा matrix_keypad *keypad = platक्रमm_get_drvdata(pdev);

	matrix_keypad_stop(keypad->input_dev);

	अगर (device_may_wakeup(&pdev->dev))
		matrix_keypad_enable_wakeup(keypad);

	वापस 0;
पूर्ण

अटल पूर्णांक matrix_keypad_resume(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा matrix_keypad *keypad = platक्रमm_get_drvdata(pdev);

	अगर (device_may_wakeup(&pdev->dev))
		matrix_keypad_disable_wakeup(keypad);

	matrix_keypad_start(keypad->input_dev);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(matrix_keypad_pm_ops,
			 matrix_keypad_suspend, matrix_keypad_resume);

अटल पूर्णांक matrix_keypad_init_gpio(काष्ठा platक्रमm_device *pdev,
				   काष्ठा matrix_keypad *keypad)
अणु
	स्थिर काष्ठा matrix_keypad_platक्रमm_data *pdata = keypad->pdata;
	पूर्णांक i, err;

	/* initialized strobe lines as outमाला_दो, activated */
	क्रम (i = 0; i < pdata->num_col_gpios; i++) अणु
		err = gpio_request(pdata->col_gpios[i], "matrix_kbd_col");
		अगर (err) अणु
			dev_err(&pdev->dev,
				"failed to request GPIO%d for COL%d\n",
				pdata->col_gpios[i], i);
			जाओ err_मुक्त_cols;
		पूर्ण

		gpio_direction_output(pdata->col_gpios[i], !pdata->active_low);
	पूर्ण

	क्रम (i = 0; i < pdata->num_row_gpios; i++) अणु
		err = gpio_request(pdata->row_gpios[i], "matrix_kbd_row");
		अगर (err) अणु
			dev_err(&pdev->dev,
				"failed to request GPIO%d for ROW%d\n",
				pdata->row_gpios[i], i);
			जाओ err_मुक्त_rows;
		पूर्ण

		gpio_direction_input(pdata->row_gpios[i]);
	पूर्ण

	अगर (pdata->clustered_irq > 0) अणु
		err = request_any_context_irq(pdata->clustered_irq,
				matrix_keypad_पूर्णांकerrupt,
				pdata->clustered_irq_flags,
				"matrix-keypad", keypad);
		अगर (err < 0) अणु
			dev_err(&pdev->dev,
				"Unable to acquire clustered interrupt\n");
			जाओ err_मुक्त_rows;
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < pdata->num_row_gpios; i++) अणु
			err = request_any_context_irq(
					gpio_to_irq(pdata->row_gpios[i]),
					matrix_keypad_पूर्णांकerrupt,
					IRQF_TRIGGER_RISING |
					IRQF_TRIGGER_FALLING,
					"matrix-keypad", keypad);
			अगर (err < 0) अणु
				dev_err(&pdev->dev,
					"Unable to acquire interrupt for GPIO line %i\n",
					pdata->row_gpios[i]);
				जाओ err_मुक्त_irqs;
			पूर्ण
		पूर्ण
	पूर्ण

	/* initialized as disabled - enabled by input->खोलो */
	disable_row_irqs(keypad);
	वापस 0;

err_मुक्त_irqs:
	जबतक (--i >= 0)
		मुक्त_irq(gpio_to_irq(pdata->row_gpios[i]), keypad);
	i = pdata->num_row_gpios;
err_मुक्त_rows:
	जबतक (--i >= 0)
		gpio_मुक्त(pdata->row_gpios[i]);
	i = pdata->num_col_gpios;
err_मुक्त_cols:
	जबतक (--i >= 0)
		gpio_मुक्त(pdata->col_gpios[i]);

	वापस err;
पूर्ण

अटल व्योम matrix_keypad_मुक्त_gpio(काष्ठा matrix_keypad *keypad)
अणु
	स्थिर काष्ठा matrix_keypad_platक्रमm_data *pdata = keypad->pdata;
	पूर्णांक i;

	अगर (pdata->clustered_irq > 0) अणु
		मुक्त_irq(pdata->clustered_irq, keypad);
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < pdata->num_row_gpios; i++)
			मुक्त_irq(gpio_to_irq(pdata->row_gpios[i]), keypad);
	पूर्ण

	क्रम (i = 0; i < pdata->num_row_gpios; i++)
		gpio_मुक्त(pdata->row_gpios[i]);

	क्रम (i = 0; i < pdata->num_col_gpios; i++)
		gpio_मुक्त(pdata->col_gpios[i]);
पूर्ण

#अगर_घोषित CONFIG_OF
अटल काष्ठा matrix_keypad_platक्रमm_data *
matrix_keypad_parse_dt(काष्ठा device *dev)
अणु
	काष्ठा matrix_keypad_platक्रमm_data *pdata;
	काष्ठा device_node *np = dev->of_node;
	अचिन्हित पूर्णांक *gpios;
	पूर्णांक ret, i, nrow, ncol;

	अगर (!np) अणु
		dev_err(dev, "device lacks DT data\n");
		वापस ERR_PTR(-ENODEV);
	पूर्ण

	pdata = devm_kzalloc(dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata) अणु
		dev_err(dev, "could not allocate memory for platform data\n");
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	pdata->num_row_gpios = nrow = of_gpio_named_count(np, "row-gpios");
	pdata->num_col_gpios = ncol = of_gpio_named_count(np, "col-gpios");
	अगर (nrow <= 0 || ncol <= 0) अणु
		dev_err(dev, "number of keypad rows/columns not specified\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	अगर (of_get_property(np, "linux,no-autorepeat", शून्य))
		pdata->no_स्वतःrepeat = true;

	pdata->wakeup = of_property_पढ़ो_bool(np, "wakeup-source") ||
			of_property_पढ़ो_bool(np, "linux,wakeup"); /* legacy */

	अगर (of_get_property(np, "gpio-activelow", शून्य))
		pdata->active_low = true;

	pdata->drive_inactive_cols =
		of_property_पढ़ो_bool(np, "drive-inactive-cols");

	of_property_पढ़ो_u32(np, "debounce-delay-ms", &pdata->debounce_ms);
	of_property_पढ़ो_u32(np, "col-scan-delay-us",
						&pdata->col_scan_delay_us);

	gpios = devm_kसुस्मृति(dev,
			     pdata->num_row_gpios + pdata->num_col_gpios,
			     माप(अचिन्हित पूर्णांक),
			     GFP_KERNEL);
	अगर (!gpios) अणु
		dev_err(dev, "could not allocate memory for gpios\n");
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	क्रम (i = 0; i < nrow; i++) अणु
		ret = of_get_named_gpio(np, "row-gpios", i);
		अगर (ret < 0)
			वापस ERR_PTR(ret);
		gpios[i] = ret;
	पूर्ण

	क्रम (i = 0; i < ncol; i++) अणु
		ret = of_get_named_gpio(np, "col-gpios", i);
		अगर (ret < 0)
			वापस ERR_PTR(ret);
		gpios[nrow + i] = ret;
	पूर्ण

	pdata->row_gpios = gpios;
	pdata->col_gpios = &gpios[pdata->num_row_gpios];

	वापस pdata;
पूर्ण
#अन्यथा
अटल अंतरभूत काष्ठा matrix_keypad_platक्रमm_data *
matrix_keypad_parse_dt(काष्ठा device *dev)
अणु
	dev_err(dev, "no platform data defined\n");

	वापस ERR_PTR(-EINVAL);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक matrix_keypad_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा matrix_keypad_platक्रमm_data *pdata;
	काष्ठा matrix_keypad *keypad;
	काष्ठा input_dev *input_dev;
	पूर्णांक err;

	pdata = dev_get_platdata(&pdev->dev);
	अगर (!pdata) अणु
		pdata = matrix_keypad_parse_dt(&pdev->dev);
		अगर (IS_ERR(pdata))
			वापस PTR_ERR(pdata);
	पूर्ण अन्यथा अगर (!pdata->keymap_data) अणु
		dev_err(&pdev->dev, "no keymap data defined\n");
		वापस -EINVAL;
	पूर्ण

	keypad = kzalloc(माप(काष्ठा matrix_keypad), GFP_KERNEL);
	input_dev = input_allocate_device();
	अगर (!keypad || !input_dev) अणु
		err = -ENOMEM;
		जाओ err_मुक्त_mem;
	पूर्ण

	keypad->input_dev = input_dev;
	keypad->pdata = pdata;
	keypad->row_shअगरt = get_count_order(pdata->num_col_gpios);
	keypad->stopped = true;
	INIT_DELAYED_WORK(&keypad->work, matrix_keypad_scan);
	spin_lock_init(&keypad->lock);

	input_dev->name		= pdev->name;
	input_dev->id.bustype	= BUS_HOST;
	input_dev->dev.parent	= &pdev->dev;
	input_dev->खोलो		= matrix_keypad_start;
	input_dev->बंद	= matrix_keypad_stop;

	err = matrix_keypad_build_keymap(pdata->keymap_data, शून्य,
					 pdata->num_row_gpios,
					 pdata->num_col_gpios,
					 शून्य, input_dev);
	अगर (err) अणु
		dev_err(&pdev->dev, "failed to build keymap\n");
		जाओ err_मुक्त_mem;
	पूर्ण

	अगर (!pdata->no_स्वतःrepeat)
		__set_bit(EV_REP, input_dev->evbit);
	input_set_capability(input_dev, EV_MSC, MSC_SCAN);
	input_set_drvdata(input_dev, keypad);

	err = matrix_keypad_init_gpio(pdev, keypad);
	अगर (err)
		जाओ err_मुक्त_mem;

	err = input_रेजिस्टर_device(keypad->input_dev);
	अगर (err)
		जाओ err_मुक्त_gpio;

	device_init_wakeup(&pdev->dev, pdata->wakeup);
	platक्रमm_set_drvdata(pdev, keypad);

	वापस 0;

err_मुक्त_gpio:
	matrix_keypad_मुक्त_gpio(keypad);
err_मुक्त_mem:
	input_मुक्त_device(input_dev);
	kमुक्त(keypad);
	वापस err;
पूर्ण

अटल पूर्णांक matrix_keypad_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा matrix_keypad *keypad = platक्रमm_get_drvdata(pdev);

	matrix_keypad_मुक्त_gpio(keypad);
	input_unरेजिस्टर_device(keypad->input_dev);
	kमुक्त(keypad);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id matrix_keypad_dt_match[] = अणु
	अणु .compatible = "gpio-matrix-keypad" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, matrix_keypad_dt_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver matrix_keypad_driver = अणु
	.probe		= matrix_keypad_probe,
	.हटाओ		= matrix_keypad_हटाओ,
	.driver		= अणु
		.name	= "matrix-keypad",
		.pm	= &matrix_keypad_pm_ops,
		.of_match_table = of_match_ptr(matrix_keypad_dt_match),
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(matrix_keypad_driver);

MODULE_AUTHOR("Marek Vasut <marek.vasut@gmail.com>");
MODULE_DESCRIPTION("GPIO Driven Matrix Keypad Driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:matrix-keypad");
