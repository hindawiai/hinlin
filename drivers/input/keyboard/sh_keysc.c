<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * SuperH KEYSC Keypad Driver
 *
 * Copyright (C) 2008 Magnus Damm
 *
 * Based on gpio_keys.c, Copyright 2005 Phil Blundell
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/delay.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/input.h>
#समावेश <linux/input/sh_keysc.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>

अटल स्थिर काष्ठा अणु
	अचिन्हित अक्षर kymd, keyout, keyin;
पूर्ण sh_keysc_mode[] = अणु
	[SH_KEYSC_MODE_1] = अणु 0, 6, 5 पूर्ण,
	[SH_KEYSC_MODE_2] = अणु 1, 5, 6 पूर्ण,
	[SH_KEYSC_MODE_3] = अणु 2, 4, 7 पूर्ण,
	[SH_KEYSC_MODE_4] = अणु 3, 6, 6 पूर्ण,
	[SH_KEYSC_MODE_5] = अणु 4, 6, 7 पूर्ण,
	[SH_KEYSC_MODE_6] = अणु 5, 8, 8 पूर्ण,
पूर्ण;

काष्ठा sh_keysc_priv अणु
	व्योम __iomem *iomem_base;
	DECLARE_BITMAP(last_keys, SH_KEYSC_MAXKEYS);
	काष्ठा input_dev *input;
	काष्ठा sh_keysc_info pdata;
पूर्ण;

#घोषणा KYCR1 0
#घोषणा KYCR2 1
#घोषणा KYINDR 2
#घोषणा KYOUTDR 3

#घोषणा KYCR2_IRQ_LEVEL    0x10
#घोषणा KYCR2_IRQ_DISABLED 0x00

अटल अचिन्हित दीर्घ sh_keysc_पढ़ो(काष्ठा sh_keysc_priv *p, पूर्णांक reg_nr)
अणु
	वापस ioपढ़ो16(p->iomem_base + (reg_nr << 2));
पूर्ण

अटल व्योम sh_keysc_ग_लिखो(काष्ठा sh_keysc_priv *p, पूर्णांक reg_nr,
			   अचिन्हित दीर्घ value)
अणु
	ioग_लिखो16(value, p->iomem_base + (reg_nr << 2));
पूर्ण

अटल व्योम sh_keysc_level_mode(काष्ठा sh_keysc_priv *p,
				अचिन्हित दीर्घ keys_set)
अणु
	काष्ठा sh_keysc_info *pdata = &p->pdata;

	sh_keysc_ग_लिखो(p, KYOUTDR, 0);
	sh_keysc_ग_लिखो(p, KYCR2, KYCR2_IRQ_LEVEL | (keys_set << 8));

	अगर (pdata->kycr2_delay)
		udelay(pdata->kycr2_delay);
पूर्ण

अटल व्योम sh_keysc_map_dbg(काष्ठा device *dev, अचिन्हित दीर्घ *map,
			     स्थिर अक्षर *str)
अणु
	पूर्णांक k;

	क्रम (k = 0; k < BITS_TO_LONGS(SH_KEYSC_MAXKEYS); k++)
		dev_dbg(dev, "%s[%d] 0x%lx\n", str, k, map[k]);
पूर्ण

अटल irqवापस_t sh_keysc_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा platक्रमm_device *pdev = dev_id;
	काष्ठा sh_keysc_priv *priv = platक्रमm_get_drvdata(pdev);
	काष्ठा sh_keysc_info *pdata = &priv->pdata;
	पूर्णांक keyout_nr = sh_keysc_mode[pdata->mode].keyout;
	पूर्णांक keyin_nr = sh_keysc_mode[pdata->mode].keyin;
	DECLARE_BITMAP(keys, SH_KEYSC_MAXKEYS);
	DECLARE_BITMAP(keys0, SH_KEYSC_MAXKEYS);
	DECLARE_BITMAP(keys1, SH_KEYSC_MAXKEYS);
	अचिन्हित अक्षर keyin_set, पंचांगp;
	पूर्णांक i, k, n;

	dev_dbg(&pdev->dev, "isr!\n");

	biपंचांगap_fill(keys1, SH_KEYSC_MAXKEYS);
	biपंचांगap_zero(keys0, SH_KEYSC_MAXKEYS);

	करो अणु
		biपंचांगap_zero(keys, SH_KEYSC_MAXKEYS);
		keyin_set = 0;

		sh_keysc_ग_लिखो(priv, KYCR2, KYCR2_IRQ_DISABLED);

		क्रम (i = 0; i < keyout_nr; i++) अणु
			n = keyin_nr * i;

			/* drive one KEYOUT pin low, पढ़ो KEYIN pins */
			sh_keysc_ग_लिखो(priv, KYOUTDR, 0xffff ^ (3 << (i * 2)));
			udelay(pdata->delay);
			पंचांगp = sh_keysc_पढ़ो(priv, KYINDR);

			/* set bit अगर key press has been detected */
			क्रम (k = 0; k < keyin_nr; k++) अणु
				अगर (पंचांगp & (1 << k))
					__set_bit(n + k, keys);
			पूर्ण

			/* keep track of which KEYIN bits that have been set */
			keyin_set |= पंचांगp ^ ((1 << keyin_nr) - 1);
		पूर्ण

		sh_keysc_level_mode(priv, keyin_set);

		biपंचांगap_complement(keys, keys, SH_KEYSC_MAXKEYS);
		biपंचांगap_and(keys1, keys1, keys, SH_KEYSC_MAXKEYS);
		biपंचांगap_or(keys0, keys0, keys, SH_KEYSC_MAXKEYS);

		sh_keysc_map_dbg(&pdev->dev, keys, "keys");

	पूर्ण जबतक (sh_keysc_पढ़ो(priv, KYCR2) & 0x01);

	sh_keysc_map_dbg(&pdev->dev, priv->last_keys, "last_keys");
	sh_keysc_map_dbg(&pdev->dev, keys0, "keys0");
	sh_keysc_map_dbg(&pdev->dev, keys1, "keys1");

	क्रम (i = 0; i < SH_KEYSC_MAXKEYS; i++) अणु
		k = pdata->keycodes[i];
		अगर (!k)
			जारी;

		अगर (test_bit(i, keys0) == test_bit(i, priv->last_keys))
			जारी;

		अगर (test_bit(i, keys1) || test_bit(i, keys0)) अणु
			input_event(priv->input, EV_KEY, k, 1);
			__set_bit(i, priv->last_keys);
		पूर्ण

		अगर (!test_bit(i, keys1)) अणु
			input_event(priv->input, EV_KEY, k, 0);
			__clear_bit(i, priv->last_keys);
		पूर्ण

	पूर्ण
	input_sync(priv->input);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक sh_keysc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sh_keysc_priv *priv;
	काष्ठा sh_keysc_info *pdata;
	काष्ठा resource *res;
	काष्ठा input_dev *input;
	पूर्णांक i;
	पूर्णांक irq, error;

	अगर (!dev_get_platdata(&pdev->dev)) अणु
		dev_err(&pdev->dev, "no platform data defined\n");
		error = -EINVAL;
		जाओ err0;
	पूर्ण

	error = -ENXIO;
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (res == शून्य) अणु
		dev_err(&pdev->dev, "failed to get I/O memory\n");
		जाओ err0;
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		जाओ err0;

	priv = kzalloc(माप(*priv), GFP_KERNEL);
	अगर (priv == शून्य) अणु
		dev_err(&pdev->dev, "failed to allocate driver data\n");
		error = -ENOMEM;
		जाओ err0;
	पूर्ण

	platक्रमm_set_drvdata(pdev, priv);
	स_नकल(&priv->pdata, dev_get_platdata(&pdev->dev), माप(priv->pdata));
	pdata = &priv->pdata;

	priv->iomem_base = ioremap(res->start, resource_size(res));
	अगर (priv->iomem_base == शून्य) अणु
		dev_err(&pdev->dev, "failed to remap I/O memory\n");
		error = -ENXIO;
		जाओ err1;
	पूर्ण

	priv->input = input_allocate_device();
	अगर (!priv->input) अणु
		dev_err(&pdev->dev, "failed to allocate input device\n");
		error = -ENOMEM;
		जाओ err2;
	पूर्ण

	input = priv->input;
	input->evbit[0] = BIT_MASK(EV_KEY);

	input->name = pdev->name;
	input->phys = "sh-keysc-keys/input0";
	input->dev.parent = &pdev->dev;

	input->id.bustype = BUS_HOST;
	input->id.venकरोr = 0x0001;
	input->id.product = 0x0001;
	input->id.version = 0x0100;

	input->keycode = pdata->keycodes;
	input->keycodesize = माप(pdata->keycodes[0]);
	input->keycodemax = ARRAY_SIZE(pdata->keycodes);

	error = request_thपढ़ोed_irq(irq, शून्य, sh_keysc_isr, IRQF_ONESHOT,
				     dev_name(&pdev->dev), pdev);
	अगर (error) अणु
		dev_err(&pdev->dev, "failed to request IRQ\n");
		जाओ err3;
	पूर्ण

	क्रम (i = 0; i < SH_KEYSC_MAXKEYS; i++)
		__set_bit(pdata->keycodes[i], input->keybit);
	__clear_bit(KEY_RESERVED, input->keybit);

	error = input_रेजिस्टर_device(input);
	अगर (error) अणु
		dev_err(&pdev->dev, "failed to register input device\n");
		जाओ err4;
	पूर्ण

	pm_runसमय_enable(&pdev->dev);
	pm_runसमय_get_sync(&pdev->dev);

	sh_keysc_ग_लिखो(priv, KYCR1, (sh_keysc_mode[pdata->mode].kymd << 8) |
		       pdata->scan_timing);
	sh_keysc_level_mode(priv, 0);

	device_init_wakeup(&pdev->dev, 1);

	वापस 0;

 err4:
	मुक्त_irq(irq, pdev);
 err3:
	input_मुक्त_device(input);
 err2:
	iounmap(priv->iomem_base);
 err1:
	kमुक्त(priv);
 err0:
	वापस error;
पूर्ण

अटल पूर्णांक sh_keysc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sh_keysc_priv *priv = platक्रमm_get_drvdata(pdev);

	sh_keysc_ग_लिखो(priv, KYCR2, KYCR2_IRQ_DISABLED);

	input_unरेजिस्टर_device(priv->input);
	मुक्त_irq(platक्रमm_get_irq(pdev, 0), pdev);
	iounmap(priv->iomem_base);

	pm_runसमय_put_sync(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);

	kमुक्त(priv);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक sh_keysc_suspend(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा sh_keysc_priv *priv = platक्रमm_get_drvdata(pdev);
	पूर्णांक irq = platक्रमm_get_irq(pdev, 0);
	अचिन्हित लघु value;

	value = sh_keysc_पढ़ो(priv, KYCR1);

	अगर (device_may_wakeup(dev)) अणु
		sh_keysc_ग_लिखो(priv, KYCR1, value | 0x80);
		enable_irq_wake(irq);
	पूर्ण अन्यथा अणु
		sh_keysc_ग_लिखो(priv, KYCR1, value & ~0x80);
		pm_runसमय_put_sync(dev);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sh_keysc_resume(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	पूर्णांक irq = platक्रमm_get_irq(pdev, 0);

	अगर (device_may_wakeup(dev))
		disable_irq_wake(irq);
	अन्यथा
		pm_runसमय_get_sync(dev);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(sh_keysc_dev_pm_ops,
			 sh_keysc_suspend, sh_keysc_resume);

अटल काष्ठा platक्रमm_driver sh_keysc_device_driver = अणु
	.probe		= sh_keysc_probe,
	.हटाओ		= sh_keysc_हटाओ,
	.driver		= अणु
		.name	= "sh_keysc",
		.pm	= &sh_keysc_dev_pm_ops,
	पूर्ण
पूर्ण;
module_platक्रमm_driver(sh_keysc_device_driver);

MODULE_AUTHOR("Magnus Damm");
MODULE_DESCRIPTION("SuperH KEYSC Keypad Driver");
MODULE_LICENSE("GPL");
