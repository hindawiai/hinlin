<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम BCM6358 memory-mapped LEDs, based on leds-syscon.c
 *
 * Copyright 2015 थlvaro Fernथँndez Rojas <noltari@gmail.com>
 */
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/leds.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/spinlock.h>

#घोषणा BCM6358_REG_MODE		0x0
#घोषणा BCM6358_REG_CTRL		0x4

#घोषणा BCM6358_SLED_CLKDIV_MASK	3
#घोषणा BCM6358_SLED_CLKDIV_1		0
#घोषणा BCM6358_SLED_CLKDIV_2		1
#घोषणा BCM6358_SLED_CLKDIV_4		2
#घोषणा BCM6358_SLED_CLKDIV_8		3

#घोषणा BCM6358_SLED_POLARITY		BIT(2)
#घोषणा BCM6358_SLED_BUSY		BIT(3)

#घोषणा BCM6358_SLED_MAX_COUNT		32
#घोषणा BCM6358_SLED_WAIT		100

/**
 * काष्ठा bcm6358_led - state container क्रम bcm6358 based LEDs
 * @cdev: LED class device क्रम this LED
 * @mem: memory resource
 * @lock: memory lock
 * @pin: LED pin number
 * @active_low: LED is active low
 */
काष्ठा bcm6358_led अणु
	काष्ठा led_classdev cdev;
	व्योम __iomem *mem;
	spinlock_t *lock;
	अचिन्हित दीर्घ pin;
	bool active_low;
पूर्ण;

अटल व्योम bcm6358_led_ग_लिखो(व्योम __iomem *reg, अचिन्हित दीर्घ data)
अणु
#अगर_घोषित CONFIG_CPU_BIG_ENDIAN
	ioग_लिखो32be(data, reg);
#अन्यथा
	ग_लिखोl(data, reg);
#पूर्ण_अगर
पूर्ण

अटल अचिन्हित दीर्घ bcm6358_led_पढ़ो(व्योम __iomem *reg)
अणु
#अगर_घोषित CONFIG_CPU_BIG_ENDIAN
	वापस ioपढ़ो32be(reg);
#अन्यथा
	वापस पढ़ोl(reg);
#पूर्ण_अगर
पूर्ण

अटल अचिन्हित दीर्घ bcm6358_led_busy(व्योम __iomem *mem)
अणु
	अचिन्हित दीर्घ val;

	जबतक ((val = bcm6358_led_पढ़ो(mem + BCM6358_REG_CTRL)) &
		BCM6358_SLED_BUSY)
		udelay(BCM6358_SLED_WAIT);

	वापस val;
पूर्ण

अटल व्योम bcm6358_led_set(काष्ठा led_classdev *led_cdev,
			    क्रमागत led_brightness value)
अणु
	काष्ठा bcm6358_led *led =
		container_of(led_cdev, काष्ठा bcm6358_led, cdev);
	अचिन्हित दीर्घ flags, val;

	spin_lock_irqsave(led->lock, flags);
	bcm6358_led_busy(led->mem);
	val = bcm6358_led_पढ़ो(led->mem + BCM6358_REG_MODE);
	अगर ((led->active_low && value == LED_OFF) ||
	    (!led->active_low && value != LED_OFF))
		val |= BIT(led->pin);
	अन्यथा
		val &= ~(BIT(led->pin));
	bcm6358_led_ग_लिखो(led->mem + BCM6358_REG_MODE, val);
	spin_unlock_irqrestore(led->lock, flags);
पूर्ण

अटल पूर्णांक bcm6358_led(काष्ठा device *dev, काष्ठा device_node *nc, u32 reg,
		       व्योम __iomem *mem, spinlock_t *lock)
अणु
	काष्ठा led_init_data init_data = अणुपूर्ण;
	काष्ठा bcm6358_led *led;
	स्थिर अक्षर *state;
	पूर्णांक rc;

	led = devm_kzalloc(dev, माप(*led), GFP_KERNEL);
	अगर (!led)
		वापस -ENOMEM;

	led->pin = reg;
	led->mem = mem;
	led->lock = lock;

	अगर (of_property_पढ़ो_bool(nc, "active-low"))
		led->active_low = true;

	अगर (!of_property_पढ़ो_string(nc, "default-state", &state)) अणु
		अगर (!म_भेद(state, "on")) अणु
			led->cdev.brightness = LED_FULL;
		पूर्ण अन्यथा अगर (!म_भेद(state, "keep")) अणु
			अचिन्हित दीर्घ val;
			val = bcm6358_led_पढ़ो(led->mem + BCM6358_REG_MODE);
			val &= BIT(led->pin);
			अगर ((led->active_low && !val) ||
			    (!led->active_low && val))
				led->cdev.brightness = LED_FULL;
			अन्यथा
				led->cdev.brightness = LED_OFF;
		पूर्ण अन्यथा अणु
			led->cdev.brightness = LED_OFF;
		पूर्ण
	पूर्ण अन्यथा अणु
		led->cdev.brightness = LED_OFF;
	पूर्ण

	bcm6358_led_set(&led->cdev, led->cdev.brightness);

	led->cdev.brightness_set = bcm6358_led_set;
	init_data.fwnode = of_fwnode_handle(nc);

	rc = devm_led_classdev_रेजिस्टर_ext(dev, &led->cdev, &init_data);
	अगर (rc < 0)
		वापस rc;

	dev_dbg(dev, "registered LED %s\n", led->cdev.name);

	वापस 0;
पूर्ण

अटल पूर्णांक bcm6358_leds_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev_of_node(&pdev->dev);
	काष्ठा device_node *child;
	व्योम __iomem *mem;
	spinlock_t *lock; /* memory lock */
	अचिन्हित दीर्घ val;
	u32 clk_भाग;

	mem = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(mem))
		वापस PTR_ERR(mem);

	lock = devm_kzalloc(dev, माप(*lock), GFP_KERNEL);
	अगर (!lock)
		वापस -ENOMEM;

	spin_lock_init(lock);

	val = bcm6358_led_busy(mem);
	val &= ~(BCM6358_SLED_POLARITY | BCM6358_SLED_CLKDIV_MASK);
	अगर (of_property_पढ़ो_bool(np, "brcm,clk-dat-low"))
		val |= BCM6358_SLED_POLARITY;
	of_property_पढ़ो_u32(np, "brcm,clk-div", &clk_भाग);
	चयन (clk_भाग) अणु
	हाल 8:
		val |= BCM6358_SLED_CLKDIV_8;
		अवरोध;
	हाल 4:
		val |= BCM6358_SLED_CLKDIV_4;
		अवरोध;
	हाल 2:
		val |= BCM6358_SLED_CLKDIV_2;
		अवरोध;
	शेष:
		val |= BCM6358_SLED_CLKDIV_1;
		अवरोध;
	पूर्ण
	bcm6358_led_ग_लिखो(mem + BCM6358_REG_CTRL, val);

	क्रम_each_available_child_of_node(np, child) अणु
		पूर्णांक rc;
		u32 reg;

		अगर (of_property_पढ़ो_u32(child, "reg", &reg))
			जारी;

		अगर (reg >= BCM6358_SLED_MAX_COUNT) अणु
			dev_err(dev, "invalid LED (%u >= %d)\n", reg,
				BCM6358_SLED_MAX_COUNT);
			जारी;
		पूर्ण

		rc = bcm6358_led(dev, child, reg, mem, lock);
		अगर (rc < 0) अणु
			of_node_put(child);
			वापस rc;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id bcm6358_leds_of_match[] = अणु
	अणु .compatible = "brcm,bcm6358-leds", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, bcm6358_leds_of_match);

अटल काष्ठा platक्रमm_driver bcm6358_leds_driver = अणु
	.probe = bcm6358_leds_probe,
	.driver = अणु
		.name = "leds-bcm6358",
		.of_match_table = bcm6358_leds_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(bcm6358_leds_driver);

MODULE_AUTHOR("थlvaro Fernथँndez Rojas <noltari@gmail.com>");
MODULE_DESCRIPTION("LED driver for BCM6358 controllers");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:leds-bcm6358");
