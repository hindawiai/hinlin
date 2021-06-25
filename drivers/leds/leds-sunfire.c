<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* leds-sunfire.c: SUNW,Ultra-Enterprise LED driver.
 *
 * Copyright (C) 2008 David S. Miller <davem@davemloft.net>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/leds.h>
#समावेश <linux/पन.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/fhc.h>
#समावेश <यंत्र/upa.h>

MODULE_AUTHOR("David S. Miller (davem@davemloft.net)");
MODULE_DESCRIPTION("Sun Fire LED driver");
MODULE_LICENSE("GPL");

काष्ठा sunfire_led अणु
	काष्ठा led_classdev	led_cdev;
	व्योम __iomem		*reg;
पूर्ण;
#घोषणा	to_sunfire_led(d) container_of(d, काष्ठा sunfire_led, led_cdev)

अटल व्योम __घड़ीboard_set(काष्ठा led_classdev *led_cdev,
			     क्रमागत led_brightness led_val, u8 bit)
अणु
	काष्ठा sunfire_led *p = to_sunfire_led(led_cdev);
	u8 reg = upa_पढ़ोb(p->reg);

	चयन (bit) अणु
	हाल CLOCK_CTRL_LLED:
		अगर (led_val)
			reg &= ~bit;
		अन्यथा
			reg |= bit;
		अवरोध;

	शेष:
		अगर (led_val)
			reg |= bit;
		अन्यथा
			reg &= ~bit;
		अवरोध;
	पूर्ण
	upa_ग_लिखोb(reg, p->reg);
पूर्ण

अटल व्योम घड़ीboard_left_set(काष्ठा led_classdev *led_cdev,
				क्रमागत led_brightness led_val)
अणु
	__घड़ीboard_set(led_cdev, led_val, CLOCK_CTRL_LLED);
पूर्ण

अटल व्योम घड़ीboard_middle_set(काष्ठा led_classdev *led_cdev,
				  क्रमागत led_brightness led_val)
अणु
	__घड़ीboard_set(led_cdev, led_val, CLOCK_CTRL_MLED);
पूर्ण

अटल व्योम घड़ीboard_right_set(काष्ठा led_classdev *led_cdev,
				 क्रमागत led_brightness led_val)
अणु
	__घड़ीboard_set(led_cdev, led_val, CLOCK_CTRL_RLED);
पूर्ण

अटल व्योम __fhc_set(काष्ठा led_classdev *led_cdev,
			     क्रमागत led_brightness led_val, u32 bit)
अणु
	काष्ठा sunfire_led *p = to_sunfire_led(led_cdev);
	u32 reg = upa_पढ़ोl(p->reg);

	चयन (bit) अणु
	हाल FHC_CONTROL_LLED:
		अगर (led_val)
			reg &= ~bit;
		अन्यथा
			reg |= bit;
		अवरोध;

	शेष:
		अगर (led_val)
			reg |= bit;
		अन्यथा
			reg &= ~bit;
		अवरोध;
	पूर्ण
	upa_ग_लिखोl(reg, p->reg);
पूर्ण

अटल व्योम fhc_left_set(काष्ठा led_classdev *led_cdev,
			 क्रमागत led_brightness led_val)
अणु
	__fhc_set(led_cdev, led_val, FHC_CONTROL_LLED);
पूर्ण

अटल व्योम fhc_middle_set(काष्ठा led_classdev *led_cdev,
			   क्रमागत led_brightness led_val)
अणु
	__fhc_set(led_cdev, led_val, FHC_CONTROL_MLED);
पूर्ण

अटल व्योम fhc_right_set(काष्ठा led_classdev *led_cdev,
			  क्रमागत led_brightness led_val)
अणु
	__fhc_set(led_cdev, led_val, FHC_CONTROL_RLED);
पूर्ण

प्रकार व्योम (*set_handler)(काष्ठा led_classdev *, क्रमागत led_brightness);
काष्ठा led_type अणु
	स्थिर अक्षर	*name;
	set_handler	handler;
	स्थिर अक्षर	*शेष_trigger;
पूर्ण;

#घोषणा NUM_LEDS_PER_BOARD	3
काष्ठा sunfire_drvdata अणु
	काष्ठा sunfire_led	leds[NUM_LEDS_PER_BOARD];
पूर्ण;

अटल पूर्णांक sunfire_led_generic_probe(काष्ठा platक्रमm_device *pdev,
					       काष्ठा led_type *types)
अणु
	काष्ठा sunfire_drvdata *p;
	पूर्णांक i, err;

	अगर (pdev->num_resources != 1) अणु
		dev_err(&pdev->dev, "Wrong number of resources %d, should be 1\n",
		       pdev->num_resources);
		वापस -EINVAL;
	पूर्ण

	p = devm_kzalloc(&pdev->dev, माप(*p), GFP_KERNEL);
	अगर (!p)
		वापस -ENOMEM;

	क्रम (i = 0; i < NUM_LEDS_PER_BOARD; i++) अणु
		काष्ठा led_classdev *lp = &p->leds[i].led_cdev;

		p->leds[i].reg = (व्योम __iomem *) pdev->resource[0].start;
		lp->name = types[i].name;
		lp->brightness = LED_FULL;
		lp->brightness_set = types[i].handler;
		lp->शेष_trigger = types[i].शेष_trigger;

		err = led_classdev_रेजिस्टर(&pdev->dev, lp);
		अगर (err) अणु
			dev_err(&pdev->dev, "Could not register %s LED\n",
			       lp->name);
			क्रम (i--; i >= 0; i--)
				led_classdev_unरेजिस्टर(&p->leds[i].led_cdev);
			वापस err;
		पूर्ण
	पूर्ण

	platक्रमm_set_drvdata(pdev, p);

	वापस 0;
पूर्ण

अटल पूर्णांक sunfire_led_generic_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sunfire_drvdata *p = platक्रमm_get_drvdata(pdev);
	पूर्णांक i;

	क्रम (i = 0; i < NUM_LEDS_PER_BOARD; i++)
		led_classdev_unरेजिस्टर(&p->leds[i].led_cdev);

	वापस 0;
पूर्ण

अटल काष्ठा led_type घड़ीboard_led_types[NUM_LEDS_PER_BOARD] = अणु
	अणु
		.name		= "clockboard-left",
		.handler	= घड़ीboard_left_set,
	पूर्ण,
	अणु
		.name		= "clockboard-middle",
		.handler	= घड़ीboard_middle_set,
	पूर्ण,
	अणु
		.name		= "clockboard-right",
		.handler	= घड़ीboard_right_set,
		.शेष_trigger = "heartbeat",
	पूर्ण,
पूर्ण;

अटल पूर्णांक sunfire_घड़ीboard_led_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस sunfire_led_generic_probe(pdev, घड़ीboard_led_types);
पूर्ण

अटल काष्ठा led_type fhc_led_types[NUM_LEDS_PER_BOARD] = अणु
	अणु
		.name		= "fhc-left",
		.handler	= fhc_left_set,
	पूर्ण,
	अणु
		.name		= "fhc-middle",
		.handler	= fhc_middle_set,
	पूर्ण,
	अणु
		.name		= "fhc-right",
		.handler	= fhc_right_set,
		.शेष_trigger = "heartbeat",
	पूर्ण,
पूर्ण;

अटल पूर्णांक sunfire_fhc_led_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस sunfire_led_generic_probe(pdev, fhc_led_types);
पूर्ण

MODULE_ALIAS("platform:sunfire-clockboard-leds");
MODULE_ALIAS("platform:sunfire-fhc-leds");

अटल काष्ठा platक्रमm_driver sunfire_घड़ीboard_led_driver = अणु
	.probe		= sunfire_घड़ीboard_led_probe,
	.हटाओ		= sunfire_led_generic_हटाओ,
	.driver		= अणु
		.name	= "sunfire-clockboard-leds",
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver sunfire_fhc_led_driver = अणु
	.probe		= sunfire_fhc_led_probe,
	.हटाओ		= sunfire_led_generic_हटाओ,
	.driver		= अणु
		.name	= "sunfire-fhc-leds",
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver * स्थिर drivers[] = अणु
	&sunfire_घड़ीboard_led_driver,
	&sunfire_fhc_led_driver,
पूर्ण;

अटल पूर्णांक __init sunfire_leds_init(व्योम)
अणु
	वापस platक्रमm_रेजिस्टर_drivers(drivers, ARRAY_SIZE(drivers));
पूर्ण

अटल व्योम __निकास sunfire_leds_निकास(व्योम)
अणु
	platक्रमm_unरेजिस्टर_drivers(drivers, ARRAY_SIZE(drivers));
पूर्ण

module_init(sunfire_leds_init);
module_निकास(sunfire_leds_निकास);
