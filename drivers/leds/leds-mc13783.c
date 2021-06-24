<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * LEDs driver क्रम Freescale MC13783/MC13892/MC34708
 *
 * Copyright (C) 2010 Philippe Rथऊtornaz
 *
 * Based on leds-da903x:
 * Copyright (C) 2008 Compulab, Ltd.
 *      Mike Rapoport <mike@compulab.co.il>
 *
 * Copyright (C) 2006-2008 Marvell International Ltd.
 *      Eric Miao <eric.miao@marvell.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/leds.h>
#समावेश <linux/of.h>
#समावेश <linux/mfd/mc13xxx.h>

काष्ठा mc13xxx_led_devtype अणु
	पूर्णांक	led_min;
	पूर्णांक	led_max;
	पूर्णांक	num_regs;
	u32	ledctrl_base;
पूर्ण;

काष्ठा mc13xxx_led अणु
	काष्ठा led_classdev	cdev;
	पूर्णांक			id;
	काष्ठा mc13xxx_leds	*leds;
पूर्ण;

काष्ठा mc13xxx_leds अणु
	काष्ठा mc13xxx			*master;
	काष्ठा mc13xxx_led_devtype	*devtype;
	पूर्णांक				num_leds;
	काष्ठा mc13xxx_led		*led;
पूर्ण;

अटल अचिन्हित पूर्णांक mc13xxx_max_brightness(पूर्णांक id)
अणु
	अगर (id >= MC13783_LED_MD && id <= MC13783_LED_KP)
		वापस 0x0f;
	अन्यथा अगर (id >= MC13783_LED_R1 && id <= MC13783_LED_B3)
		वापस 0x1f;

	वापस 0x3f;
पूर्ण

अटल पूर्णांक mc13xxx_led_set(काष्ठा led_classdev *led_cdev,
			    क्रमागत led_brightness value)
अणु
	काष्ठा mc13xxx_led *led =
		container_of(led_cdev, काष्ठा mc13xxx_led, cdev);
	काष्ठा mc13xxx_leds *leds = led->leds;
	अचिन्हित पूर्णांक reg, bank, off, shअगरt;

	चयन (led->id) अणु
	हाल MC13783_LED_MD:
	हाल MC13783_LED_AD:
	हाल MC13783_LED_KP:
		reg = 2;
		shअगरt = 9 + (led->id - MC13783_LED_MD) * 4;
		अवरोध;
	हाल MC13783_LED_R1:
	हाल MC13783_LED_G1:
	हाल MC13783_LED_B1:
	हाल MC13783_LED_R2:
	हाल MC13783_LED_G2:
	हाल MC13783_LED_B2:
	हाल MC13783_LED_R3:
	हाल MC13783_LED_G3:
	हाल MC13783_LED_B3:
		off = led->id - MC13783_LED_R1;
		bank = off / 3;
		reg = 3 + bank;
		shअगरt = (off - bank * 3) * 5 + 6;
		अवरोध;
	हाल MC13892_LED_MD:
	हाल MC13892_LED_AD:
	हाल MC13892_LED_KP:
		off = led->id - MC13892_LED_MD;
		reg = off / 2;
		shअगरt = 3 + (off - reg * 2) * 12;
		अवरोध;
	हाल MC13892_LED_R:
	हाल MC13892_LED_G:
	हाल MC13892_LED_B:
		off = led->id - MC13892_LED_R;
		bank = off / 2;
		reg = 2 + bank;
		shअगरt = (off - bank * 2) * 12 + 3;
		अवरोध;
	हाल MC34708_LED_R:
	हाल MC34708_LED_G:
		reg = 0;
		shअगरt = 3 + (led->id - MC34708_LED_R) * 12;
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	वापस mc13xxx_reg_rmw(leds->master, leds->devtype->ledctrl_base + reg,
			mc13xxx_max_brightness(led->id) << shअगरt,
			value << shअगरt);
पूर्ण

#अगर_घोषित CONFIG_OF
अटल काष्ठा mc13xxx_leds_platक्रमm_data __init *mc13xxx_led_probe_dt(
	काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mc13xxx_leds *leds = platक्रमm_get_drvdata(pdev);
	काष्ठा mc13xxx_leds_platक्रमm_data *pdata;
	काष्ठा device_node *parent, *child;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक i = 0, ret = -ENODATA;

	pdata = devm_kzalloc(dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		वापस ERR_PTR(-ENOMEM);

	parent = of_get_child_by_name(dev_of_node(dev->parent), "leds");
	अगर (!parent)
		जाओ out_node_put;

	ret = of_property_पढ़ो_u32_array(parent, "led-control",
					 pdata->led_control,
					 leds->devtype->num_regs);
	अगर (ret)
		जाओ out_node_put;

	pdata->num_leds = of_get_available_child_count(parent);

	pdata->led = devm_kसुस्मृति(dev, pdata->num_leds, माप(*pdata->led),
				  GFP_KERNEL);
	अगर (!pdata->led) अणु
		ret = -ENOMEM;
		जाओ out_node_put;
	पूर्ण

	क्रम_each_available_child_of_node(parent, child) अणु
		स्थिर अक्षर *str;
		u32 पंचांगp;

		अगर (of_property_पढ़ो_u32(child, "reg", &पंचांगp))
			जारी;
		pdata->led[i].id = leds->devtype->led_min + पंचांगp;

		अगर (!of_property_पढ़ो_string(child, "label", &str))
			pdata->led[i].name = str;
		अगर (!of_property_पढ़ो_string(child, "linux,default-trigger",
					     &str))
			pdata->led[i].शेष_trigger = str;

		i++;
	पूर्ण

	pdata->num_leds = i;
	ret = i > 0 ? 0 : -ENODATA;

out_node_put:
	of_node_put(parent);

	वापस ret ? ERR_PTR(ret) : pdata;
पूर्ण
#अन्यथा
अटल अंतरभूत काष्ठा mc13xxx_leds_platक्रमm_data __init *mc13xxx_led_probe_dt(
	काष्ठा platक्रमm_device *pdev)
अणु
	वापस ERR_PTR(-ENOSYS);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक __init mc13xxx_led_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा mc13xxx_leds_platक्रमm_data *pdata = dev_get_platdata(dev);
	काष्ठा mc13xxx *mcdev = dev_get_drvdata(dev->parent);
	काष्ठा mc13xxx_led_devtype *devtype =
		(काष्ठा mc13xxx_led_devtype *)pdev->id_entry->driver_data;
	काष्ठा mc13xxx_leds *leds;
	पूर्णांक i, id, ret = -ENODATA;
	u32 init_led = 0;

	leds = devm_kzalloc(dev, माप(*leds), GFP_KERNEL);
	अगर (!leds)
		वापस -ENOMEM;

	leds->devtype = devtype;
	leds->master = mcdev;
	platक्रमm_set_drvdata(pdev, leds);

	अगर (dev_of_node(dev->parent)) अणु
		pdata = mc13xxx_led_probe_dt(pdev);
		अगर (IS_ERR(pdata))
			वापस PTR_ERR(pdata);
	पूर्ण अन्यथा अगर (!pdata)
		वापस -ENODATA;

	leds->num_leds = pdata->num_leds;

	अगर ((leds->num_leds < 1) ||
	    (leds->num_leds > (devtype->led_max - devtype->led_min + 1))) अणु
		dev_err(dev, "Invalid LED count %d\n", leds->num_leds);
		वापस -EINVAL;
	पूर्ण

	leds->led = devm_kसुस्मृति(dev, leds->num_leds, माप(*leds->led),
				 GFP_KERNEL);
	अगर (!leds->led)
		वापस -ENOMEM;

	क्रम (i = 0; i < devtype->num_regs; i++) अणु
		ret = mc13xxx_reg_ग_लिखो(mcdev, leds->devtype->ledctrl_base + i,
					pdata->led_control[i]);
		अगर (ret)
			वापस ret;
	पूर्ण

	क्रम (i = 0; i < leds->num_leds; i++) अणु
		स्थिर अक्षर *name, *trig;

		ret = -EINVAL;

		id = pdata->led[i].id;
		name = pdata->led[i].name;
		trig = pdata->led[i].शेष_trigger;

		अगर ((id > devtype->led_max) || (id < devtype->led_min)) अणु
			dev_err(dev, "Invalid ID %i\n", id);
			अवरोध;
		पूर्ण

		अगर (init_led & (1 << id)) अणु
			dev_warn(dev, "LED %i already initialized\n", id);
			अवरोध;
		पूर्ण

		init_led |= 1 << id;
		leds->led[i].id = id;
		leds->led[i].leds = leds;
		leds->led[i].cdev.name = name;
		leds->led[i].cdev.शेष_trigger = trig;
		leds->led[i].cdev.flags = LED_CORE_SUSPENDRESUME;
		leds->led[i].cdev.brightness_set_blocking = mc13xxx_led_set;
		leds->led[i].cdev.max_brightness = mc13xxx_max_brightness(id);

		ret = led_classdev_रेजिस्टर(dev->parent, &leds->led[i].cdev);
		अगर (ret) अणु
			dev_err(dev, "Failed to register LED %i\n", id);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (ret)
		जबतक (--i >= 0)
			led_classdev_unरेजिस्टर(&leds->led[i].cdev);

	वापस ret;
पूर्ण

अटल पूर्णांक mc13xxx_led_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mc13xxx_leds *leds = platक्रमm_get_drvdata(pdev);
	पूर्णांक i;

	क्रम (i = 0; i < leds->num_leds; i++)
		led_classdev_unरेजिस्टर(&leds->led[i].cdev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mc13xxx_led_devtype mc13783_led_devtype = अणु
	.led_min	= MC13783_LED_MD,
	.led_max	= MC13783_LED_B3,
	.num_regs	= 6,
	.ledctrl_base	= 51,
पूर्ण;

अटल स्थिर काष्ठा mc13xxx_led_devtype mc13892_led_devtype = अणु
	.led_min	= MC13892_LED_MD,
	.led_max	= MC13892_LED_B,
	.num_regs	= 4,
	.ledctrl_base	= 51,
पूर्ण;

अटल स्थिर काष्ठा mc13xxx_led_devtype mc34708_led_devtype = अणु
	.led_min	= MC34708_LED_R,
	.led_max	= MC34708_LED_G,
	.num_regs	= 1,
	.ledctrl_base	= 54,
पूर्ण;

अटल स्थिर काष्ठा platक्रमm_device_id mc13xxx_led_id_table[] = अणु
	अणु "mc13783-led", (kernel_uदीर्घ_t)&mc13783_led_devtype, पूर्ण,
	अणु "mc13892-led", (kernel_uदीर्घ_t)&mc13892_led_devtype, पूर्ण,
	अणु "mc34708-led", (kernel_uदीर्घ_t)&mc34708_led_devtype, पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, mc13xxx_led_id_table);

अटल काष्ठा platक्रमm_driver mc13xxx_led_driver = अणु
	.driver	= अणु
		.name	= "mc13xxx-led",
	पूर्ण,
	.हटाओ		= mc13xxx_led_हटाओ,
	.id_table	= mc13xxx_led_id_table,
पूर्ण;
module_platक्रमm_driver_probe(mc13xxx_led_driver, mc13xxx_led_probe);

MODULE_DESCRIPTION("LEDs driver for Freescale MC13XXX PMIC");
MODULE_AUTHOR("Philippe Retornaz <philippe.retornaz@epfl.ch>");
MODULE_LICENSE("GPL");
