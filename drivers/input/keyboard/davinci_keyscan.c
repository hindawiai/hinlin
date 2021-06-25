<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * DaVinci Key Scan Driver क्रम TI platक्रमms
 *
 * Copyright (C) 2009 Texas Instruments, Inc
 *
 * Author: Miguel Aguilar <miguel.aguilar@ridgerun.com>
 *
 * Initial Code: Sandeep Paulraj <s-paulraj@ti.com>
 */
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/types.h>
#समावेश <linux/input.h>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>

#समावेश <linux/platक्रमm_data/keyscan-davinci.h>

/* Key scan रेजिस्टरs */
#घोषणा DAVINCI_KEYSCAN_KEYCTRL		0x0000
#घोषणा DAVINCI_KEYSCAN_INTENA		0x0004
#घोषणा DAVINCI_KEYSCAN_INTFLAG		0x0008
#घोषणा DAVINCI_KEYSCAN_INTCLR		0x000c
#घोषणा DAVINCI_KEYSCAN_STRBWIDTH	0x0010
#घोषणा DAVINCI_KEYSCAN_INTERVAL	0x0014
#घोषणा DAVINCI_KEYSCAN_CONTTIME	0x0018
#घोषणा DAVINCI_KEYSCAN_CURRENTST	0x001c
#घोषणा DAVINCI_KEYSCAN_PREVSTATE	0x0020
#घोषणा DAVINCI_KEYSCAN_EMUCTRL		0x0024
#घोषणा DAVINCI_KEYSCAN_IODFTCTRL	0x002c

/* Key Control Register (KEYCTRL) */
#घोषणा DAVINCI_KEYSCAN_KEYEN		0x00000001
#घोषणा DAVINCI_KEYSCAN_PREVMODE	0x00000002
#घोषणा DAVINCI_KEYSCAN_CHATOFF		0x00000004
#घोषणा DAVINCI_KEYSCAN_AUTODET		0x00000008
#घोषणा DAVINCI_KEYSCAN_SCANMODE	0x00000010
#घोषणा DAVINCI_KEYSCAN_OUTTYPE		0x00000020

/* Masks क्रम the पूर्णांकerrupts */
#घोषणा DAVINCI_KEYSCAN_INT_CONT	0x00000008
#घोषणा DAVINCI_KEYSCAN_INT_OFF		0x00000004
#घोषणा DAVINCI_KEYSCAN_INT_ON		0x00000002
#घोषणा DAVINCI_KEYSCAN_INT_CHANGE	0x00000001
#घोषणा DAVINCI_KEYSCAN_INT_ALL		0x0000000f

काष्ठा davinci_ks अणु
	काष्ठा input_dev		*input;
	काष्ठा davinci_ks_platक्रमm_data	*pdata;
	पूर्णांक				irq;
	व्योम __iomem			*base;
	resource_माप_प्रकार			pbase;
	माप_प्रकार				base_size;
	अचिन्हित लघु			keymap[];
पूर्ण;

/* Initializing the kp Module */
अटल पूर्णांक __init davinci_ks_initialize(काष्ठा davinci_ks *davinci_ks)
अणु
	काष्ठा device *dev = &davinci_ks->input->dev;
	काष्ठा davinci_ks_platक्रमm_data *pdata = davinci_ks->pdata;
	u32 matrix_ctrl;

	/* Enable all पूर्णांकerrupts */
	__raw_ग_लिखोl(DAVINCI_KEYSCAN_INT_ALL,
		     davinci_ks->base + DAVINCI_KEYSCAN_INTENA);

	/* Clear पूर्णांकerrupts अगर any */
	__raw_ग_लिखोl(DAVINCI_KEYSCAN_INT_ALL,
		     davinci_ks->base + DAVINCI_KEYSCAN_INTCLR);

	/* Setup the scan period = strobe + पूर्णांकerval */
	__raw_ग_लिखोl(pdata->strobe,
		     davinci_ks->base + DAVINCI_KEYSCAN_STRBWIDTH);
	__raw_ग_लिखोl(pdata->पूर्णांकerval,
		     davinci_ks->base + DAVINCI_KEYSCAN_INTERVAL);
	__raw_ग_लिखोl(0x01,
		     davinci_ks->base + DAVINCI_KEYSCAN_CONTTIME);

	/* Define matrix type */
	चयन (pdata->matrix_type) अणु
	हाल DAVINCI_KEYSCAN_MATRIX_4X4:
		matrix_ctrl = 0;
		अवरोध;
	हाल DAVINCI_KEYSCAN_MATRIX_5X3:
		matrix_ctrl = (1 << 6);
		अवरोध;
	शेष:
		dev_err(dev->parent, "wrong matrix type\n");
		वापस -EINVAL;
	पूर्ण

	/* Enable key scan module and set matrix type */
	__raw_ग_लिखोl(DAVINCI_KEYSCAN_AUTODET | DAVINCI_KEYSCAN_KEYEN |
		     matrix_ctrl, davinci_ks->base + DAVINCI_KEYSCAN_KEYCTRL);

	वापस 0;
पूर्ण

अटल irqवापस_t davinci_ks_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा davinci_ks *davinci_ks = dev_id;
	काष्ठा device *dev = &davinci_ks->input->dev;
	अचिन्हित लघु *keymap = davinci_ks->keymap;
	पूर्णांक keymapsize = davinci_ks->pdata->keymapsize;
	u32 prev_status, new_status, changed;
	bool release;
	पूर्णांक keycode = KEY_UNKNOWN;
	पूर्णांक i;

	/* Disable पूर्णांकerrupt */
	__raw_ग_लिखोl(0x0, davinci_ks->base + DAVINCI_KEYSCAN_INTENA);

	/* Reading previous and new status of the key scan */
	prev_status = __raw_पढ़ोl(davinci_ks->base + DAVINCI_KEYSCAN_PREVSTATE);
	new_status = __raw_पढ़ोl(davinci_ks->base + DAVINCI_KEYSCAN_CURRENTST);

	changed = prev_status ^ new_status;

	अगर (changed) अणु
		/*
		 * It goes through all bits in 'changed' to ensure
		 * that no key changes are being missed
		 */
		क्रम (i = 0 ; i < keymapsize; i++) अणु
			अगर ((changed>>i) & 0x1) अणु
				keycode = keymap[i];
				release = (new_status >> i) & 0x1;
				dev_dbg(dev->parent, "key %d %s\n", keycode,
					release ? "released" : "pressed");
				input_report_key(davinci_ks->input, keycode,
						 !release);
				input_sync(davinci_ks->input);
			पूर्ण
		पूर्ण
		/* Clearing पूर्णांकerrupt */
		__raw_ग_लिखोl(DAVINCI_KEYSCAN_INT_ALL,
			     davinci_ks->base + DAVINCI_KEYSCAN_INTCLR);
	पूर्ण

	/* Enable पूर्णांकerrupts */
	__raw_ग_लिखोl(0x1, davinci_ks->base + DAVINCI_KEYSCAN_INTENA);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक __init davinci_ks_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा davinci_ks *davinci_ks;
	काष्ठा input_dev *key_dev;
	काष्ठा resource *res, *mem;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा davinci_ks_platक्रमm_data *pdata = dev_get_platdata(dev);
	पूर्णांक error, i;

	अगर (pdata->device_enable) अणु
		error = pdata->device_enable(dev);
		अगर (error < 0) अणु
			dev_dbg(dev, "device enable function failed\n");
			वापस error;
		पूर्ण
	पूर्ण

	अगर (!pdata->keymap) अणु
		dev_dbg(dev, "no keymap from pdata\n");
		वापस -EINVAL;
	पूर्ण

	davinci_ks = kzalloc(माप(काष्ठा davinci_ks) +
		माप(अचिन्हित लघु) * pdata->keymapsize, GFP_KERNEL);
	अगर (!davinci_ks) अणु
		dev_dbg(dev, "could not allocate memory for private data\n");
		वापस -ENOMEM;
	पूर्ण

	स_नकल(davinci_ks->keymap, pdata->keymap,
		माप(अचिन्हित लघु) * pdata->keymapsize);

	key_dev = input_allocate_device();
	अगर (!key_dev) अणु
		dev_dbg(dev, "could not allocate input device\n");
		error = -ENOMEM;
		जाओ fail1;
	पूर्ण

	davinci_ks->input = key_dev;

	davinci_ks->irq = platक्रमm_get_irq(pdev, 0);
	अगर (davinci_ks->irq < 0) अणु
		error = davinci_ks->irq;
		जाओ fail2;
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res) अणु
		dev_err(dev, "no mem resource\n");
		error = -EINVAL;
		जाओ fail2;
	पूर्ण

	davinci_ks->pbase = res->start;
	davinci_ks->base_size = resource_size(res);

	mem = request_mem_region(davinci_ks->pbase, davinci_ks->base_size,
				 pdev->name);
	अगर (!mem) अणु
		dev_err(dev, "key scan registers at %08x are not free\n",
			davinci_ks->pbase);
		error = -EBUSY;
		जाओ fail2;
	पूर्ण

	davinci_ks->base = ioremap(davinci_ks->pbase, davinci_ks->base_size);
	अगर (!davinci_ks->base) अणु
		dev_err(dev, "can't ioremap MEM resource.\n");
		error = -ENOMEM;
		जाओ fail3;
	पूर्ण

	/* Enable स्वतः repeat feature of Linux input subप्रणाली */
	अगर (pdata->rep)
		__set_bit(EV_REP, key_dev->evbit);

	/* Setup input device */
	__set_bit(EV_KEY, key_dev->evbit);

	/* Setup the platक्रमm data */
	davinci_ks->pdata = pdata;

	क्रम (i = 0; i < davinci_ks->pdata->keymapsize; i++)
		__set_bit(davinci_ks->pdata->keymap[i], key_dev->keybit);

	key_dev->name = "davinci_keyscan";
	key_dev->phys = "davinci_keyscan/input0";
	key_dev->dev.parent = dev;
	key_dev->id.bustype = BUS_HOST;
	key_dev->id.venकरोr = 0x0001;
	key_dev->id.product = 0x0001;
	key_dev->id.version = 0x0001;
	key_dev->keycode = davinci_ks->keymap;
	key_dev->keycodesize = माप(davinci_ks->keymap[0]);
	key_dev->keycodemax = davinci_ks->pdata->keymapsize;

	error = input_रेजिस्टर_device(davinci_ks->input);
	अगर (error < 0) अणु
		dev_err(dev, "unable to register davinci key scan device\n");
		जाओ fail4;
	पूर्ण

	error = request_irq(davinci_ks->irq, davinci_ks_पूर्णांकerrupt,
			  0, pdev->name, davinci_ks);
	अगर (error < 0) अणु
		dev_err(dev, "unable to register davinci key scan interrupt\n");
		जाओ fail5;
	पूर्ण

	error = davinci_ks_initialize(davinci_ks);
	अगर (error < 0) अणु
		dev_err(dev, "unable to initialize davinci key scan device\n");
		जाओ fail6;
	पूर्ण

	platक्रमm_set_drvdata(pdev, davinci_ks);
	वापस 0;

fail6:
	मुक्त_irq(davinci_ks->irq, davinci_ks);
fail5:
	input_unरेजिस्टर_device(davinci_ks->input);
	key_dev = शून्य;
fail4:
	iounmap(davinci_ks->base);
fail3:
	release_mem_region(davinci_ks->pbase, davinci_ks->base_size);
fail2:
	input_मुक्त_device(key_dev);
fail1:
	kमुक्त(davinci_ks);

	वापस error;
पूर्ण

अटल पूर्णांक davinci_ks_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा davinci_ks *davinci_ks = platक्रमm_get_drvdata(pdev);

	मुक्त_irq(davinci_ks->irq, davinci_ks);

	input_unरेजिस्टर_device(davinci_ks->input);

	iounmap(davinci_ks->base);
	release_mem_region(davinci_ks->pbase, davinci_ks->base_size);

	kमुक्त(davinci_ks);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver davinci_ks_driver = अणु
	.driver	= अणु
		.name = "davinci_keyscan",
	पूर्ण,
	.हटाओ	= davinci_ks_हटाओ,
पूर्ण;

module_platक्रमm_driver_probe(davinci_ks_driver, davinci_ks_probe);

MODULE_AUTHOR("Miguel Aguilar");
MODULE_DESCRIPTION("Texas Instruments DaVinci Key Scan Driver");
MODULE_LICENSE("GPL");
