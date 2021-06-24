<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * linux/drivers/input/keyboard/omap-keypad.c
 *
 * OMAP Keypad Driver
 *
 * Copyright (C) 2003 Nokia Corporation
 * Written by Timo Terथअs <ext-timo.teras@nokia.com>
 *
 * Added support क्रम H2 & H3 Keypad
 * Copyright (C) 2004 Texas Instruments
 */

#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/types.h>
#समावेश <linux/input.h>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mutex.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/platक्रमm_data/gpio-omap.h>
#समावेश <linux/platक्रमm_data/keypad-omap.h>

#अघोषित NEW_BOARD_LEARNING_MODE

अटल व्योम omap_kp_tasklet(अचिन्हित दीर्घ);
अटल व्योम omap_kp_समयr(काष्ठा समयr_list *);

अटल अचिन्हित अक्षर keypad_state[8];
अटल DEFINE_MUTEX(kp_enable_mutex);
अटल पूर्णांक kp_enable = 1;
अटल पूर्णांक kp_cur_group = -1;

काष्ठा omap_kp अणु
	काष्ठा input_dev *input;
	काष्ठा समयr_list समयr;
	पूर्णांक irq;
	अचिन्हित पूर्णांक rows;
	अचिन्हित पूर्णांक cols;
	अचिन्हित दीर्घ delay;
	अचिन्हित पूर्णांक debounce;
	अचिन्हित लघु keymap[];
पूर्ण;

अटल DECLARE_TASKLET_DISABLED_OLD(kp_tasklet, omap_kp_tasklet);

अटल अचिन्हित पूर्णांक *row_gpios;
अटल अचिन्हित पूर्णांक *col_gpios;

अटल irqवापस_t omap_kp_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	/* disable keyboard पूर्णांकerrupt and schedule क्रम handling */
	omap_ग_लिखोw(1, OMAP1_MPUIO_BASE + OMAP_MPUIO_KBD_MASKIT);

	tasklet_schedule(&kp_tasklet);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम omap_kp_समयr(काष्ठा समयr_list *unused)
अणु
	tasklet_schedule(&kp_tasklet);
पूर्ण

अटल व्योम omap_kp_scan_keypad(काष्ठा omap_kp *omap_kp, अचिन्हित अक्षर *state)
अणु
	पूर्णांक col = 0;

	/* disable keyboard पूर्णांकerrupt and schedule क्रम handling */
	omap_ग_लिखोw(1, OMAP1_MPUIO_BASE + OMAP_MPUIO_KBD_MASKIT);

	/* पढ़ो the keypad status */
	omap_ग_लिखोw(0xff, OMAP1_MPUIO_BASE + OMAP_MPUIO_KBC);
	क्रम (col = 0; col < omap_kp->cols; col++) अणु
		omap_ग_लिखोw(~(1 << col) & 0xff,
			    OMAP1_MPUIO_BASE + OMAP_MPUIO_KBC);

		udelay(omap_kp->delay);

		state[col] = ~omap_पढ़ोw(OMAP1_MPUIO_BASE +
					 OMAP_MPUIO_KBR_LATCH) & 0xff;
	पूर्ण
	omap_ग_लिखोw(0x00, OMAP1_MPUIO_BASE + OMAP_MPUIO_KBC);
	udelay(2);
पूर्ण

अटल व्योम omap_kp_tasklet(अचिन्हित दीर्घ data)
अणु
	काष्ठा omap_kp *omap_kp_data = (काष्ठा omap_kp *) data;
	अचिन्हित लघु *keycodes = omap_kp_data->input->keycode;
	अचिन्हित पूर्णांक row_shअगरt = get_count_order(omap_kp_data->cols);
	अचिन्हित अक्षर new_state[8], changed, key_करोwn = 0;
	पूर्णांक col, row;

	/* check क्रम any changes */
	omap_kp_scan_keypad(omap_kp_data, new_state);

	/* check क्रम changes and prपूर्णांक those */
	क्रम (col = 0; col < omap_kp_data->cols; col++) अणु
		changed = new_state[col] ^ keypad_state[col];
		key_करोwn |= new_state[col];
		अगर (changed == 0)
			जारी;

		क्रम (row = 0; row < omap_kp_data->rows; row++) अणु
			पूर्णांक key;
			अगर (!(changed & (1 << row)))
				जारी;
#अगर_घोषित NEW_BOARD_LEARNING_MODE
			prपूर्णांकk(KERN_INFO "omap-keypad: key %d-%d %s\n", col,
			       row, (new_state[col] & (1 << row)) ?
			       "pressed" : "released");
#अन्यथा
			key = keycodes[MATRIX_SCAN_CODE(row, col, row_shअगरt)];

			अगर (!(kp_cur_group == (key & GROUP_MASK) ||
			      kp_cur_group == -1))
				जारी;

			kp_cur_group = key & GROUP_MASK;
			input_report_key(omap_kp_data->input, key & ~GROUP_MASK,
					 new_state[col] & (1 << row));
#पूर्ण_अगर
		पूर्ण
	पूर्ण
	input_sync(omap_kp_data->input);
	स_नकल(keypad_state, new_state, माप(keypad_state));

	अगर (key_करोwn) अणु
		/* some key is pressed - keep irq disabled and use समयr
		 * to poll the keypad */
		mod_समयr(&omap_kp_data->समयr, jअगरfies + HZ / 20);
	पूर्ण अन्यथा अणु
		/* enable पूर्णांकerrupts */
		omap_ग_लिखोw(0, OMAP1_MPUIO_BASE + OMAP_MPUIO_KBD_MASKIT);
		kp_cur_group = -1;
	पूर्ण
पूर्ण

अटल sमाप_प्रकार omap_kp_enable_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%u\n", kp_enable);
पूर्ण

अटल sमाप_प्रकार omap_kp_enable_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
				    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा omap_kp *omap_kp = dev_get_drvdata(dev);
	पूर्णांक state;

	अगर (माला_पूछो(buf, "%u", &state) != 1)
		वापस -EINVAL;

	अगर ((state != 1) && (state != 0))
		वापस -EINVAL;

	mutex_lock(&kp_enable_mutex);
	अगर (state != kp_enable) अणु
		अगर (state)
			enable_irq(omap_kp->irq);
		अन्यथा
			disable_irq(omap_kp->irq);
		kp_enable = state;
	पूर्ण
	mutex_unlock(&kp_enable_mutex);

	वापस strnlen(buf, count);
पूर्ण

अटल DEVICE_ATTR(enable, S_IRUGO | S_IWUSR, omap_kp_enable_show, omap_kp_enable_store);

अटल पूर्णांक omap_kp_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा omap_kp *omap_kp;
	काष्ठा input_dev *input_dev;
	काष्ठा omap_kp_platक्रमm_data *pdata = dev_get_platdata(&pdev->dev);
	पूर्णांक i, col_idx, row_idx, ret;
	अचिन्हित पूर्णांक row_shअगरt, keycodemax;

	अगर (!pdata->rows || !pdata->cols || !pdata->keymap_data) अणु
		prपूर्णांकk(KERN_ERR "No rows, cols or keymap_data from pdata\n");
		वापस -EINVAL;
	पूर्ण

	row_shअगरt = get_count_order(pdata->cols);
	keycodemax = pdata->rows << row_shअगरt;

	omap_kp = kzalloc(माप(काष्ठा omap_kp) +
			keycodemax * माप(अचिन्हित लघु), GFP_KERNEL);
	input_dev = input_allocate_device();
	अगर (!omap_kp || !input_dev) अणु
		kमुक्त(omap_kp);
		input_मुक्त_device(input_dev);
		वापस -ENOMEM;
	पूर्ण

	platक्रमm_set_drvdata(pdev, omap_kp);

	omap_kp->input = input_dev;

	/* Disable the पूर्णांकerrupt क्रम the MPUIO keyboard */
	omap_ग_लिखोw(1, OMAP1_MPUIO_BASE + OMAP_MPUIO_KBD_MASKIT);

	अगर (pdata->delay)
		omap_kp->delay = pdata->delay;

	अगर (pdata->row_gpios && pdata->col_gpios) अणु
		row_gpios = pdata->row_gpios;
		col_gpios = pdata->col_gpios;
	पूर्ण

	omap_kp->rows = pdata->rows;
	omap_kp->cols = pdata->cols;

	col_idx = 0;
	row_idx = 0;

	समयr_setup(&omap_kp->समयr, omap_kp_समयr, 0);

	/* get the irq and init समयr*/
	kp_tasklet.data = (अचिन्हित दीर्घ) omap_kp;
	tasklet_enable(&kp_tasklet);

	ret = device_create_file(&pdev->dev, &dev_attr_enable);
	अगर (ret < 0)
		जाओ err2;

	/* setup input device */
	input_dev->name = "omap-keypad";
	input_dev->phys = "omap-keypad/input0";
	input_dev->dev.parent = &pdev->dev;

	input_dev->id.bustype = BUS_HOST;
	input_dev->id.venकरोr = 0x0001;
	input_dev->id.product = 0x0001;
	input_dev->id.version = 0x0100;

	अगर (pdata->rep)
		__set_bit(EV_REP, input_dev->evbit);

	ret = matrix_keypad_build_keymap(pdata->keymap_data, शून्य,
					 pdata->rows, pdata->cols,
					 omap_kp->keymap, input_dev);
	अगर (ret < 0)
		जाओ err3;

	ret = input_रेजिस्टर_device(omap_kp->input);
	अगर (ret < 0) अणु
		prपूर्णांकk(KERN_ERR "Unable to register omap-keypad input device\n");
		जाओ err3;
	पूर्ण

	अगर (pdata->dbounce)
		omap_ग_लिखोw(0xff, OMAP1_MPUIO_BASE + OMAP_MPUIO_GPIO_DEBOUNCING);

	/* scan current status and enable पूर्णांकerrupt */
	omap_kp_scan_keypad(omap_kp, keypad_state);
	omap_kp->irq = platक्रमm_get_irq(pdev, 0);
	अगर (omap_kp->irq >= 0) अणु
		अगर (request_irq(omap_kp->irq, omap_kp_पूर्णांकerrupt, 0,
				"omap-keypad", omap_kp) < 0)
			जाओ err4;
	पूर्ण
	omap_ग_लिखोw(0, OMAP1_MPUIO_BASE + OMAP_MPUIO_KBD_MASKIT);

	वापस 0;

err4:
	input_unरेजिस्टर_device(omap_kp->input);
	input_dev = शून्य;
err3:
	device_हटाओ_file(&pdev->dev, &dev_attr_enable);
err2:
	क्रम (i = row_idx - 1; i >= 0; i--)
		gpio_मुक्त(row_gpios[i]);
	क्रम (i = col_idx - 1; i >= 0; i--)
		gpio_मुक्त(col_gpios[i]);

	kमुक्त(omap_kp);
	input_मुक्त_device(input_dev);

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक omap_kp_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा omap_kp *omap_kp = platक्रमm_get_drvdata(pdev);

	/* disable keypad पूर्णांकerrupt handling */
	tasklet_disable(&kp_tasklet);
	omap_ग_लिखोw(1, OMAP1_MPUIO_BASE + OMAP_MPUIO_KBD_MASKIT);
	मुक्त_irq(omap_kp->irq, omap_kp);

	del_समयr_sync(&omap_kp->समयr);
	tasklet_समाप्त(&kp_tasklet);

	/* unरेजिस्टर everything */
	input_unरेजिस्टर_device(omap_kp->input);

	kमुक्त(omap_kp);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver omap_kp_driver = अणु
	.probe		= omap_kp_probe,
	.हटाओ		= omap_kp_हटाओ,
	.driver		= अणु
		.name	= "omap-keypad",
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(omap_kp_driver);

MODULE_AUTHOR("Timo Terथअs");
MODULE_DESCRIPTION("OMAP Keypad Driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:omap-keypad");
