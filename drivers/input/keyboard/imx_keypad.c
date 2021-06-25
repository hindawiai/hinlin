<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Driver क्रम the IMX keypad port.
// Copyright (C) 2009 Alberto Panizzo <maramaopercheseimorto@gmail.com>

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/input/matrix_keypad.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/समयr.h>

/*
 * Keypad Controller रेजिस्टरs (halfword)
 */
#घोषणा KPCR		0x00 /* Keypad Control Register */

#घोषणा KPSR		0x02 /* Keypad Status Register */
#घोषणा KBD_STAT_KPKD	(0x1 << 0) /* Key Press Interrupt Status bit (w1c) */
#घोषणा KBD_STAT_KPKR	(0x1 << 1) /* Key Release Interrupt Status bit (w1c) */
#घोषणा KBD_STAT_KDSC	(0x1 << 2) /* Key Depress Synch Chain Status bit (w1c)*/
#घोषणा KBD_STAT_KRSS	(0x1 << 3) /* Key Release Synch Status bit (w1c)*/
#घोषणा KBD_STAT_KDIE	(0x1 << 8) /* Key Depress Interrupt Enable Status bit */
#घोषणा KBD_STAT_KRIE	(0x1 << 9) /* Key Release Interrupt Enable */
#घोषणा KBD_STAT_KPPEN	(0x1 << 10) /* Keypad Clock Enable */

#घोषणा KDDR		0x04 /* Keypad Data Direction Register */
#घोषणा KPDR		0x06 /* Keypad Data Register */

#घोषणा MAX_MATRIX_KEY_ROWS	8
#घोषणा MAX_MATRIX_KEY_COLS	8
#घोषणा MATRIX_ROW_SHIFT	3

#घोषणा MAX_MATRIX_KEY_NUM	(MAX_MATRIX_KEY_ROWS * MAX_MATRIX_KEY_COLS)

काष्ठा imx_keypad अणु

	काष्ठा clk *clk;
	काष्ठा input_dev *input_dev;
	व्योम __iomem *mmio_base;

	पूर्णांक			irq;
	काष्ठा समयr_list	check_matrix_समयr;

	/*
	 * The matrix is stable only अगर no changes are detected after
	 * IMX_KEYPAD_SCANS_FOR_STABILITY scans
	 */
#घोषणा IMX_KEYPAD_SCANS_FOR_STABILITY 3
	पूर्णांक			stable_count;

	bool			enabled;

	/* Masks क्रम enabled rows/cols */
	अचिन्हित लघु		rows_en_mask;
	अचिन्हित लघु		cols_en_mask;

	अचिन्हित लघु		keycodes[MAX_MATRIX_KEY_NUM];

	/*
	 * Matrix states:
	 * -stable: achieved after a complete debounce process.
	 * -unstable: used in the debouncing process.
	 */
	अचिन्हित लघु		matrix_stable_state[MAX_MATRIX_KEY_COLS];
	अचिन्हित लघु		matrix_unstable_state[MAX_MATRIX_KEY_COLS];
पूर्ण;

/* Scan the matrix and वापस the new state in *matrix_अस्थिर_state. */
अटल व्योम imx_keypad_scan_matrix(काष्ठा imx_keypad *keypad,
				  अचिन्हित लघु *matrix_अस्थिर_state)
अणु
	पूर्णांक col;
	अचिन्हित लघु reg_val;

	क्रम (col = 0; col < MAX_MATRIX_KEY_COLS; col++) अणु
		अगर ((keypad->cols_en_mask & (1 << col)) == 0)
			जारी;
		/*
		 * Disअक्षरge keypad capacitance:
		 * 2. ग_लिखो 1s on column data.
		 * 3. configure columns as totem-pole to disअक्षरge capacitance.
		 * 4. configure columns as खोलो-drain.
		 */
		reg_val = पढ़ोw(keypad->mmio_base + KPDR);
		reg_val |= 0xff00;
		ग_लिखोw(reg_val, keypad->mmio_base + KPDR);

		reg_val = पढ़ोw(keypad->mmio_base + KPCR);
		reg_val &= ~((keypad->cols_en_mask & 0xff) << 8);
		ग_लिखोw(reg_val, keypad->mmio_base + KPCR);

		udelay(2);

		reg_val = पढ़ोw(keypad->mmio_base + KPCR);
		reg_val |= (keypad->cols_en_mask & 0xff) << 8;
		ग_लिखोw(reg_val, keypad->mmio_base + KPCR);

		/*
		 * 5. Write a single column to 0, others to 1.
		 * 6. Sample row inमाला_दो and save data.
		 * 7. Repeat steps 2 - 6 क्रम reमुख्यing columns.
		 */
		reg_val = पढ़ोw(keypad->mmio_base + KPDR);
		reg_val &= ~(1 << (8 + col));
		ग_लिखोw(reg_val, keypad->mmio_base + KPDR);

		/*
		 * Delay added to aव्योम propagating the 0 from column to row
		 * when scanning.
		 */
		udelay(5);

		/*
		 * 1s in matrix_अस्थिर_state[col] means key pressures
		 * throw data from non enabled rows.
		 */
		reg_val = पढ़ोw(keypad->mmio_base + KPDR);
		matrix_अस्थिर_state[col] = (~reg_val) & keypad->rows_en_mask;
	पूर्ण

	/*
	 * Return in standby mode:
	 * 9. ग_लिखो 0s to columns
	 */
	reg_val = पढ़ोw(keypad->mmio_base + KPDR);
	reg_val &= 0x00ff;
	ग_लिखोw(reg_val, keypad->mmio_base + KPDR);
पूर्ण

/*
 * Compare the new matrix state (अस्थिर) with the stable one stored in
 * keypad->matrix_stable_state and fire events अगर changes are detected.
 */
अटल व्योम imx_keypad_fire_events(काष्ठा imx_keypad *keypad,
				   अचिन्हित लघु *matrix_अस्थिर_state)
अणु
	काष्ठा input_dev *input_dev = keypad->input_dev;
	पूर्णांक row, col;

	क्रम (col = 0; col < MAX_MATRIX_KEY_COLS; col++) अणु
		अचिन्हित लघु bits_changed;
		पूर्णांक code;

		अगर ((keypad->cols_en_mask & (1 << col)) == 0)
			जारी; /* Column is not enabled */

		bits_changed = keypad->matrix_stable_state[col] ^
						matrix_अस्थिर_state[col];

		अगर (bits_changed == 0)
			जारी; /* Column करोes not contain changes */

		क्रम (row = 0; row < MAX_MATRIX_KEY_ROWS; row++) अणु
			अगर ((keypad->rows_en_mask & (1 << row)) == 0)
				जारी; /* Row is not enabled */
			अगर ((bits_changed & (1 << row)) == 0)
				जारी; /* Row करोes not contain changes */

			code = MATRIX_SCAN_CODE(row, col, MATRIX_ROW_SHIFT);
			input_event(input_dev, EV_MSC, MSC_SCAN, code);
			input_report_key(input_dev, keypad->keycodes[code],
				matrix_अस्थिर_state[col] & (1 << row));
			dev_dbg(&input_dev->dev, "Event code: %d, val: %d",
				keypad->keycodes[code],
				matrix_अस्थिर_state[col] & (1 << row));
		पूर्ण
	पूर्ण
	input_sync(input_dev);
पूर्ण

/*
 * imx_keypad_check_क्रम_events is the समयr handler.
 */
अटल व्योम imx_keypad_check_क्रम_events(काष्ठा समयr_list *t)
अणु
	काष्ठा imx_keypad *keypad = from_समयr(keypad, t, check_matrix_समयr);
	अचिन्हित लघु matrix_अस्थिर_state[MAX_MATRIX_KEY_COLS];
	अचिन्हित लघु reg_val;
	bool state_changed, is_zero_matrix;
	पूर्णांक i;

	स_रखो(matrix_अस्थिर_state, 0, माप(matrix_अस्थिर_state));

	imx_keypad_scan_matrix(keypad, matrix_अस्थिर_state);

	state_changed = false;
	क्रम (i = 0; i < MAX_MATRIX_KEY_COLS; i++) अणु
		अगर ((keypad->cols_en_mask & (1 << i)) == 0)
			जारी;

		अगर (keypad->matrix_unstable_state[i] ^ matrix_अस्थिर_state[i]) अणु
			state_changed = true;
			अवरोध;
		पूर्ण
	पूर्ण

	/*
	 * If the matrix state is changed from the previous scan
	 *   (Re)Begin the debouncing process, saving the new state in
	 *    keypad->matrix_unstable_state.
	 * अन्यथा
	 *   Increase the count of number of scans with a stable state.
	 */
	अगर (state_changed) अणु
		स_नकल(keypad->matrix_unstable_state, matrix_अस्थिर_state,
			माप(matrix_अस्थिर_state));
		keypad->stable_count = 0;
	पूर्ण अन्यथा
		keypad->stable_count++;

	/*
	 * If the matrix is not as stable as we want reschedule scan
	 * in the near future.
	 */
	अगर (keypad->stable_count < IMX_KEYPAD_SCANS_FOR_STABILITY) अणु
		mod_समयr(&keypad->check_matrix_समयr,
			  jअगरfies + msecs_to_jअगरfies(10));
		वापस;
	पूर्ण

	/*
	 * If the matrix state is stable, fire the events and save the new
	 * stable state. Note, अगर the matrix is kept stable क्रम दीर्घer
	 * (keypad->stable_count > IMX_KEYPAD_SCANS_FOR_STABILITY) all
	 * events have alपढ़ोy been generated.
	 */
	अगर (keypad->stable_count == IMX_KEYPAD_SCANS_FOR_STABILITY) अणु
		imx_keypad_fire_events(keypad, matrix_अस्थिर_state);

		स_नकल(keypad->matrix_stable_state, matrix_अस्थिर_state,
			माप(matrix_अस्थिर_state));
	पूर्ण

	is_zero_matrix = true;
	क्रम (i = 0; i < MAX_MATRIX_KEY_COLS; i++) अणु
		अगर (matrix_अस्थिर_state[i] != 0) अणु
			is_zero_matrix = false;
			अवरोध;
		पूर्ण
	पूर्ण


	अगर (is_zero_matrix) अणु
		/*
		 * All keys have been released. Enable only the KDI
		 * पूर्णांकerrupt क्रम future key presses (clear the KDI
		 * status bit and its sync chain beक्रमe that).
		 */
		reg_val = पढ़ोw(keypad->mmio_base + KPSR);
		reg_val |= KBD_STAT_KPKD | KBD_STAT_KDSC;
		ग_लिखोw(reg_val, keypad->mmio_base + KPSR);

		reg_val = पढ़ोw(keypad->mmio_base + KPSR);
		reg_val |= KBD_STAT_KDIE;
		reg_val &= ~KBD_STAT_KRIE;
		ग_लिखोw(reg_val, keypad->mmio_base + KPSR);
	पूर्ण अन्यथा अणु
		/*
		 * Some keys are still pressed. Schedule a rescan in
		 * attempt to detect multiple key presses and enable
		 * the KRI पूर्णांकerrupt to react quickly to key release
		 * event.
		 */
		mod_समयr(&keypad->check_matrix_समयr,
			  jअगरfies + msecs_to_jअगरfies(60));

		reg_val = पढ़ोw(keypad->mmio_base + KPSR);
		reg_val |= KBD_STAT_KPKR | KBD_STAT_KRSS;
		ग_लिखोw(reg_val, keypad->mmio_base + KPSR);

		reg_val = पढ़ोw(keypad->mmio_base + KPSR);
		reg_val |= KBD_STAT_KRIE;
		reg_val &= ~KBD_STAT_KDIE;
		ग_लिखोw(reg_val, keypad->mmio_base + KPSR);
	पूर्ण
पूर्ण

अटल irqवापस_t imx_keypad_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा imx_keypad *keypad = dev_id;
	अचिन्हित लघु reg_val;

	reg_val = पढ़ोw(keypad->mmio_base + KPSR);

	/* Disable both पूर्णांकerrupt types */
	reg_val &= ~(KBD_STAT_KRIE | KBD_STAT_KDIE);
	/* Clear पूर्णांकerrupts status bits */
	reg_val |= KBD_STAT_KPKR | KBD_STAT_KPKD;
	ग_लिखोw(reg_val, keypad->mmio_base + KPSR);

	अगर (keypad->enabled) अणु
		/* The matrix is supposed to be changed */
		keypad->stable_count = 0;

		/* Schedule the scanning procedure near in the future */
		mod_समयr(&keypad->check_matrix_समयr,
			  jअगरfies + msecs_to_jअगरfies(2));
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम imx_keypad_config(काष्ठा imx_keypad *keypad)
अणु
	अचिन्हित लघु reg_val;

	/*
	 * Include enabled rows in पूर्णांकerrupt generation (KPCR[7:0])
	 * Configure keypad columns as खोलो-drain (KPCR[15:8])
	 */
	reg_val = पढ़ोw(keypad->mmio_base + KPCR);
	reg_val |= keypad->rows_en_mask & 0xff;		/* rows */
	reg_val |= (keypad->cols_en_mask & 0xff) << 8;	/* cols */
	ग_लिखोw(reg_val, keypad->mmio_base + KPCR);

	/* Write 0's to KPDR[15:8] (Colums) */
	reg_val = पढ़ोw(keypad->mmio_base + KPDR);
	reg_val &= 0x00ff;
	ग_लिखोw(reg_val, keypad->mmio_base + KPDR);

	/* Configure columns as output, rows as input (KDDR[15:0]) */
	ग_लिखोw(0xff00, keypad->mmio_base + KDDR);

	/*
	 * Clear Key Depress and Key Release status bit.
	 * Clear both synchronizer chain.
	 */
	reg_val = पढ़ोw(keypad->mmio_base + KPSR);
	reg_val |= KBD_STAT_KPKR | KBD_STAT_KPKD |
		   KBD_STAT_KDSC | KBD_STAT_KRSS;
	ग_लिखोw(reg_val, keypad->mmio_base + KPSR);

	/* Enable KDI and disable KRI (aव्योम false release events). */
	reg_val |= KBD_STAT_KDIE;
	reg_val &= ~KBD_STAT_KRIE;
	ग_लिखोw(reg_val, keypad->mmio_base + KPSR);
पूर्ण

अटल व्योम imx_keypad_inhibit(काष्ठा imx_keypad *keypad)
अणु
	अचिन्हित लघु reg_val;

	/* Inhibit KDI and KRI पूर्णांकerrupts. */
	reg_val = पढ़ोw(keypad->mmio_base + KPSR);
	reg_val &= ~(KBD_STAT_KRIE | KBD_STAT_KDIE);
	reg_val |= KBD_STAT_KPKR | KBD_STAT_KPKD;
	ग_लिखोw(reg_val, keypad->mmio_base + KPSR);

	/* Colums as खोलो drain and disable all rows */
	reg_val = (keypad->cols_en_mask & 0xff) << 8;
	ग_लिखोw(reg_val, keypad->mmio_base + KPCR);
पूर्ण

अटल व्योम imx_keypad_बंद(काष्ठा input_dev *dev)
अणु
	काष्ठा imx_keypad *keypad = input_get_drvdata(dev);

	dev_dbg(&dev->dev, ">%s\n", __func__);

	/* Mark keypad as being inactive */
	keypad->enabled = false;
	synchronize_irq(keypad->irq);
	del_समयr_sync(&keypad->check_matrix_समयr);

	imx_keypad_inhibit(keypad);

	/* Disable घड़ी unit */
	clk_disable_unprepare(keypad->clk);
पूर्ण

अटल पूर्णांक imx_keypad_खोलो(काष्ठा input_dev *dev)
अणु
	काष्ठा imx_keypad *keypad = input_get_drvdata(dev);
	पूर्णांक error;

	dev_dbg(&dev->dev, ">%s\n", __func__);

	/* Enable the kpp घड़ी */
	error = clk_prepare_enable(keypad->clk);
	अगर (error)
		वापस error;

	/* We became active from now */
	keypad->enabled = true;

	imx_keypad_config(keypad);

	/* Sanity control, not all the rows must be actived now. */
	अगर ((पढ़ोw(keypad->mmio_base + KPDR) & keypad->rows_en_mask) == 0) अणु
		dev_err(&dev->dev,
			"too many keys pressed, control pins initialisation\n");
		जाओ खोलो_err;
	पूर्ण

	वापस 0;

खोलो_err:
	imx_keypad_बंद(dev);
	वापस -EIO;
पूर्ण

अटल स्थिर काष्ठा of_device_id imx_keypad_of_match[] = अणु
	अणु .compatible = "fsl,imx21-kpp", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, imx_keypad_of_match);

अटल पूर्णांक imx_keypad_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा imx_keypad *keypad;
	काष्ठा input_dev *input_dev;
	पूर्णांक irq, error, i, row, col;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	input_dev = devm_input_allocate_device(&pdev->dev);
	अगर (!input_dev) अणु
		dev_err(&pdev->dev, "failed to allocate the input device\n");
		वापस -ENOMEM;
	पूर्ण

	keypad = devm_kzalloc(&pdev->dev, माप(*keypad), GFP_KERNEL);
	अगर (!keypad) अणु
		dev_err(&pdev->dev, "not enough memory for driver data\n");
		वापस -ENOMEM;
	पूर्ण

	keypad->input_dev = input_dev;
	keypad->irq = irq;
	keypad->stable_count = 0;

	समयr_setup(&keypad->check_matrix_समयr,
		    imx_keypad_check_क्रम_events, 0);

	keypad->mmio_base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(keypad->mmio_base))
		वापस PTR_ERR(keypad->mmio_base);

	keypad->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(keypad->clk)) अणु
		dev_err(&pdev->dev, "failed to get keypad clock\n");
		वापस PTR_ERR(keypad->clk);
	पूर्ण

	/* Init the Input device */
	input_dev->name = pdev->name;
	input_dev->id.bustype = BUS_HOST;
	input_dev->dev.parent = &pdev->dev;
	input_dev->खोलो = imx_keypad_खोलो;
	input_dev->बंद = imx_keypad_बंद;

	error = matrix_keypad_build_keymap(शून्य, शून्य,
					   MAX_MATRIX_KEY_ROWS,
					   MAX_MATRIX_KEY_COLS,
					   keypad->keycodes, input_dev);
	अगर (error) अणु
		dev_err(&pdev->dev, "failed to build keymap\n");
		वापस error;
	पूर्ण

	/* Search क्रम rows and cols enabled */
	क्रम (row = 0; row < MAX_MATRIX_KEY_ROWS; row++) अणु
		क्रम (col = 0; col < MAX_MATRIX_KEY_COLS; col++) अणु
			i = MATRIX_SCAN_CODE(row, col, MATRIX_ROW_SHIFT);
			अगर (keypad->keycodes[i] != KEY_RESERVED) अणु
				keypad->rows_en_mask |= 1 << row;
				keypad->cols_en_mask |= 1 << col;
			पूर्ण
		पूर्ण
	पूर्ण
	dev_dbg(&pdev->dev, "enabled rows mask: %x\n", keypad->rows_en_mask);
	dev_dbg(&pdev->dev, "enabled cols mask: %x\n", keypad->cols_en_mask);

	__set_bit(EV_REP, input_dev->evbit);
	input_set_capability(input_dev, EV_MSC, MSC_SCAN);
	input_set_drvdata(input_dev, keypad);

	/* Ensure that the keypad will stay करोrmant until खोलोed */
	error = clk_prepare_enable(keypad->clk);
	अगर (error)
		वापस error;
	imx_keypad_inhibit(keypad);
	clk_disable_unprepare(keypad->clk);

	error = devm_request_irq(&pdev->dev, irq, imx_keypad_irq_handler, 0,
			    pdev->name, keypad);
	अगर (error) अणु
		dev_err(&pdev->dev, "failed to request IRQ\n");
		वापस error;
	पूर्ण

	/* Register the input device */
	error = input_रेजिस्टर_device(input_dev);
	अगर (error) अणु
		dev_err(&pdev->dev, "failed to register input device\n");
		वापस error;
	पूर्ण

	platक्रमm_set_drvdata(pdev, keypad);
	device_init_wakeup(&pdev->dev, 1);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused imx_kbd_noirq_suspend(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा imx_keypad *kbd = platक्रमm_get_drvdata(pdev);
	काष्ठा input_dev *input_dev = kbd->input_dev;
	अचिन्हित लघु reg_val = पढ़ोw(kbd->mmio_base + KPSR);

	/* imx kbd can wake up प्रणाली even घड़ी is disabled */
	mutex_lock(&input_dev->mutex);

	अगर (input_device_enabled(input_dev))
		clk_disable_unprepare(kbd->clk);

	mutex_unlock(&input_dev->mutex);

	अगर (device_may_wakeup(&pdev->dev)) अणु
		अगर (reg_val & KBD_STAT_KPKD)
			reg_val |= KBD_STAT_KRIE;
		अगर (reg_val & KBD_STAT_KPKR)
			reg_val |= KBD_STAT_KDIE;
		ग_लिखोw(reg_val, kbd->mmio_base + KPSR);

		enable_irq_wake(kbd->irq);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused imx_kbd_noirq_resume(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा imx_keypad *kbd = platक्रमm_get_drvdata(pdev);
	काष्ठा input_dev *input_dev = kbd->input_dev;
	पूर्णांक ret = 0;

	अगर (device_may_wakeup(&pdev->dev))
		disable_irq_wake(kbd->irq);

	mutex_lock(&input_dev->mutex);

	अगर (input_device_enabled(input_dev)) अणु
		ret = clk_prepare_enable(kbd->clk);
		अगर (ret)
			जाओ err_clk;
	पूर्ण

err_clk:
	mutex_unlock(&input_dev->mutex);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops imx_kbd_pm_ops = अणु
	SET_NOIRQ_SYSTEM_SLEEP_PM_OPS(imx_kbd_noirq_suspend, imx_kbd_noirq_resume)
पूर्ण;

अटल काष्ठा platक्रमm_driver imx_keypad_driver = अणु
	.driver		= अणु
		.name	= "imx-keypad",
		.pm	= &imx_kbd_pm_ops,
		.of_match_table = imx_keypad_of_match,
	पूर्ण,
	.probe		= imx_keypad_probe,
पूर्ण;
module_platक्रमm_driver(imx_keypad_driver);

MODULE_AUTHOR("Alberto Panizzo <maramaopercheseimorto@gmail.com>");
MODULE_DESCRIPTION("IMX Keypad Port Driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:imx-keypad");
