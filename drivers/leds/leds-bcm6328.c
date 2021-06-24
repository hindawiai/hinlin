<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम BCM6328 memory-mapped LEDs, based on leds-syscon.c
 *
 * Copyright 2015 थlvaro Fernथँndez Rojas <noltari@gmail.com>
 * Copyright 2015 Jonas Gorski <jogo@खोलोwrt.org>
 */
#समावेश <linux/पन.स>
#समावेश <linux/leds.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/spinlock.h>

#घोषणा BCM6328_REG_INIT		0x00
#घोषणा BCM6328_REG_MODE_HI		0x04
#घोषणा BCM6328_REG_MODE_LO		0x08
#घोषणा BCM6328_REG_HWDIS		0x0c
#घोषणा BCM6328_REG_STROBE		0x10
#घोषणा BCM6328_REG_LNKACTSEL_HI	0x14
#घोषणा BCM6328_REG_LNKACTSEL_LO	0x18
#घोषणा BCM6328_REG_RBACK		0x1c
#घोषणा BCM6328_REG_SERMUX		0x20

#घोषणा BCM6328_LED_MAX_COUNT		24
#घोषणा BCM6328_LED_DEF_DELAY		500

#घोषणा BCM6328_LED_BLINK_DELAYS	2
#घोषणा BCM6328_LED_BLINK_MS		20

#घोषणा BCM6328_LED_BLINK_MASK		0x3f
#घोषणा BCM6328_LED_BLINK1_SHIFT	0
#घोषणा BCM6328_LED_BLINK1_MASK		(BCM6328_LED_BLINK_MASK << \
					 BCM6328_LED_BLINK1_SHIFT)
#घोषणा BCM6328_LED_BLINK2_SHIFT	6
#घोषणा BCM6328_LED_BLINK2_MASK		(BCM6328_LED_BLINK_MASK << \
					 BCM6328_LED_BLINK2_SHIFT)
#घोषणा BCM6328_SERIAL_LED_EN		BIT(12)
#घोषणा BCM6328_SERIAL_LED_MUX		BIT(13)
#घोषणा BCM6328_SERIAL_LED_CLK_NPOL	BIT(14)
#घोषणा BCM6328_SERIAL_LED_DATA_PPOL	BIT(15)
#घोषणा BCM6328_SERIAL_LED_SHIFT_सूची	BIT(16)
#घोषणा BCM6328_LED_SHIFT_TEST		BIT(30)
#घोषणा BCM6328_LED_TEST		BIT(31)
#घोषणा BCM6328_INIT_MASK		(BCM6328_SERIAL_LED_EN | \
					 BCM6328_SERIAL_LED_MUX | \
					 BCM6328_SERIAL_LED_CLK_NPOL | \
					 BCM6328_SERIAL_LED_DATA_PPOL | \
					 BCM6328_SERIAL_LED_SHIFT_सूची)

#घोषणा BCM6328_LED_MODE_MASK		3
#घोषणा BCM6328_LED_MODE_ON		0
#घोषणा BCM6328_LED_MODE_BLINK1		1
#घोषणा BCM6328_LED_MODE_BLINK2		2
#घोषणा BCM6328_LED_MODE_OFF		3
#घोषणा BCM6328_LED_SHIFT(X)		((X) << 1)

/**
 * काष्ठा bcm6328_led - state container क्रम bcm6328 based LEDs
 * @cdev: LED class device क्रम this LED
 * @mem: memory resource
 * @lock: memory lock
 * @pin: LED pin number
 * @blink_leds: blinking LEDs
 * @blink_delay: blinking delay
 * @active_low: LED is active low
 */
काष्ठा bcm6328_led अणु
	काष्ठा led_classdev cdev;
	व्योम __iomem *mem;
	spinlock_t *lock;
	अचिन्हित दीर्घ pin;
	अचिन्हित दीर्घ *blink_leds;
	अचिन्हित दीर्घ *blink_delay;
	bool active_low;
पूर्ण;

अटल व्योम bcm6328_led_ग_लिखो(व्योम __iomem *reg, अचिन्हित दीर्घ data)
अणु
#अगर_घोषित CONFIG_CPU_BIG_ENDIAN
	ioग_लिखो32be(data, reg);
#अन्यथा
	ग_लिखोl(data, reg);
#पूर्ण_अगर
पूर्ण

अटल अचिन्हित दीर्घ bcm6328_led_पढ़ो(व्योम __iomem *reg)
अणु
#अगर_घोषित CONFIG_CPU_BIG_ENDIAN
	वापस ioपढ़ो32be(reg);
#अन्यथा
	वापस पढ़ोl(reg);
#पूर्ण_अगर
पूर्ण

/**
 * LEDMode 64 bits / 24 LEDs
 * bits [31:0] -> LEDs 8-23
 * bits [47:32] -> LEDs 0-7
 * bits [63:48] -> unused
 */
अटल अचिन्हित दीर्घ bcm6328_pin2shअगरt(अचिन्हित दीर्घ pin)
अणु
	अगर (pin < 8)
		वापस pin + 16; /* LEDs 0-7 (bits 47:32) */
	अन्यथा
		वापस pin - 8; /* LEDs 8-23 (bits 31:0) */
पूर्ण

अटल व्योम bcm6328_led_mode(काष्ठा bcm6328_led *led, अचिन्हित दीर्घ value)
अणु
	व्योम __iomem *mode;
	अचिन्हित दीर्घ val, shअगरt;

	shअगरt = bcm6328_pin2shअगरt(led->pin);
	अगर (shअगरt / 16)
		mode = led->mem + BCM6328_REG_MODE_HI;
	अन्यथा
		mode = led->mem + BCM6328_REG_MODE_LO;

	val = bcm6328_led_पढ़ो(mode);
	val &= ~(BCM6328_LED_MODE_MASK << BCM6328_LED_SHIFT(shअगरt % 16));
	val |= (value << BCM6328_LED_SHIFT(shअगरt % 16));
	bcm6328_led_ग_लिखो(mode, val);
पूर्ण

अटल व्योम bcm6328_led_set(काष्ठा led_classdev *led_cdev,
			    क्रमागत led_brightness value)
अणु
	काष्ठा bcm6328_led *led =
		container_of(led_cdev, काष्ठा bcm6328_led, cdev);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(led->lock, flags);

	/* Remove LED from cached HW blinking पूर्णांकervals */
	led->blink_leds[0] &= ~BIT(led->pin);
	led->blink_leds[1] &= ~BIT(led->pin);

	/* Set LED on/off */
	अगर ((led->active_low && value == LED_OFF) ||
	    (!led->active_low && value != LED_OFF))
		bcm6328_led_mode(led, BCM6328_LED_MODE_ON);
	अन्यथा
		bcm6328_led_mode(led, BCM6328_LED_MODE_OFF);

	spin_unlock_irqrestore(led->lock, flags);
पूर्ण

अटल अचिन्हित दीर्घ bcm6328_blink_delay(अचिन्हित दीर्घ delay)
अणु
	अचिन्हित दीर्घ bcm6328_delay;

	bcm6328_delay = delay + BCM6328_LED_BLINK_MS / 2;
	bcm6328_delay = bcm6328_delay / BCM6328_LED_BLINK_MS;
	अगर (bcm6328_delay == 0)
		bcm6328_delay = 1;

	वापस bcm6328_delay;
पूर्ण

अटल पूर्णांक bcm6328_blink_set(काष्ठा led_classdev *led_cdev,
			     अचिन्हित दीर्घ *delay_on, अचिन्हित दीर्घ *delay_off)
अणु
	काष्ठा bcm6328_led *led =
		container_of(led_cdev, काष्ठा bcm6328_led, cdev);
	अचिन्हित दीर्घ delay, flags;
	पूर्णांक rc;

	अगर (!*delay_on)
		*delay_on = BCM6328_LED_DEF_DELAY;
	अगर (!*delay_off)
		*delay_off = BCM6328_LED_DEF_DELAY;

	delay = bcm6328_blink_delay(*delay_on);
	अगर (delay != bcm6328_blink_delay(*delay_off)) अणु
		dev_dbg(led_cdev->dev,
			"fallback to soft blinking (delay_on != delay_off)\n");
		वापस -EINVAL;
	पूर्ण

	अगर (delay > BCM6328_LED_BLINK_MASK) अणु
		dev_dbg(led_cdev->dev,
			"fallback to soft blinking (delay > %ums)\n",
			BCM6328_LED_BLINK_MASK * BCM6328_LED_BLINK_MS);
		वापस -EINVAL;
	पूर्ण

	spin_lock_irqsave(led->lock, flags);
	/*
	 * Check अगर any of the two configurable HW blinking पूर्णांकervals is
	 * available:
	 *   1. No LEDs asचिन्हित to the HW blinking पूर्णांकerval.
	 *   2. Only this LED is asचिन्हित to the HW blinking पूर्णांकerval.
	 *   3. LEDs with the same delay asचिन्हित.
	 */
	अगर (led->blink_leds[0] == 0 ||
	    led->blink_leds[0] == BIT(led->pin) ||
	    led->blink_delay[0] == delay) अणु
		अचिन्हित दीर्घ val;

		/* Add LED to the first HW blinking पूर्णांकerval cache */
		led->blink_leds[0] |= BIT(led->pin);

		/* Remove LED from the second HW blinking पूर्णांकerval cache */
		led->blink_leds[1] &= ~BIT(led->pin);

		/* Cache first HW blinking पूर्णांकerval delay */
		led->blink_delay[0] = delay;

		/* Update the delay क्रम the first HW blinking पूर्णांकerval */
		val = bcm6328_led_पढ़ो(led->mem + BCM6328_REG_INIT);
		val &= ~BCM6328_LED_BLINK1_MASK;
		val |= (delay << BCM6328_LED_BLINK1_SHIFT);
		bcm6328_led_ग_लिखो(led->mem + BCM6328_REG_INIT, val);

		/* Set the LED to first HW blinking पूर्णांकerval */
		bcm6328_led_mode(led, BCM6328_LED_MODE_BLINK1);

		rc = 0;
	पूर्ण अन्यथा अगर (led->blink_leds[1] == 0 ||
		   led->blink_leds[1] == BIT(led->pin) ||
		   led->blink_delay[1] == delay) अणु
		अचिन्हित दीर्घ val;

		/* Remove LED from the first HW blinking पूर्णांकerval */
		led->blink_leds[0] &= ~BIT(led->pin);

		/* Add LED to the second HW blinking पूर्णांकerval */
		led->blink_leds[1] |= BIT(led->pin);

		/* Cache second HW blinking पूर्णांकerval delay */
		led->blink_delay[1] = delay;

		/* Update the delay क्रम the second HW blinking पूर्णांकerval */
		val = bcm6328_led_पढ़ो(led->mem + BCM6328_REG_INIT);
		val &= ~BCM6328_LED_BLINK2_MASK;
		val |= (delay << BCM6328_LED_BLINK2_SHIFT);
		bcm6328_led_ग_लिखो(led->mem + BCM6328_REG_INIT, val);

		/* Set the LED to second HW blinking पूर्णांकerval */
		bcm6328_led_mode(led, BCM6328_LED_MODE_BLINK2);

		rc = 0;
	पूर्ण अन्यथा अणु
		dev_dbg(led_cdev->dev,
			"fallback to soft blinking (delay already set)\n");
		rc = -EINVAL;
	पूर्ण
	spin_unlock_irqrestore(led->lock, flags);

	वापस rc;
पूर्ण

अटल पूर्णांक bcm6328_hwled(काष्ठा device *dev, काष्ठा device_node *nc, u32 reg,
			 व्योम __iomem *mem, spinlock_t *lock)
अणु
	पूर्णांक i, cnt;
	अचिन्हित दीर्घ flags, val;

	spin_lock_irqsave(lock, flags);
	val = bcm6328_led_पढ़ो(mem + BCM6328_REG_HWDIS);
	val &= ~BIT(reg);
	bcm6328_led_ग_लिखो(mem + BCM6328_REG_HWDIS, val);
	spin_unlock_irqrestore(lock, flags);

	/* Only LEDs 0-7 can be activity/link controlled */
	अगर (reg >= 8)
		वापस 0;

	cnt = of_property_count_elems_of_size(nc, "brcm,link-signal-sources",
					      माप(u32));
	क्रम (i = 0; i < cnt; i++) अणु
		u32 sel;
		व्योम __iomem *addr;

		अगर (reg < 4)
			addr = mem + BCM6328_REG_LNKACTSEL_LO;
		अन्यथा
			addr = mem + BCM6328_REG_LNKACTSEL_HI;

		of_property_पढ़ो_u32_index(nc, "brcm,link-signal-sources", i,
					   &sel);

		अगर (reg / 4 != sel / 4) अणु
			dev_warn(dev, "invalid link signal source\n");
			जारी;
		पूर्ण

		spin_lock_irqsave(lock, flags);
		val = bcm6328_led_पढ़ो(addr);
		val |= (BIT(reg % 4) << (((sel % 4) * 4) + 16));
		bcm6328_led_ग_लिखो(addr, val);
		spin_unlock_irqrestore(lock, flags);
	पूर्ण

	cnt = of_property_count_elems_of_size(nc,
					      "brcm,activity-signal-sources",
					      माप(u32));
	क्रम (i = 0; i < cnt; i++) अणु
		u32 sel;
		व्योम __iomem *addr;

		अगर (reg < 4)
			addr = mem + BCM6328_REG_LNKACTSEL_LO;
		अन्यथा
			addr = mem + BCM6328_REG_LNKACTSEL_HI;

		of_property_पढ़ो_u32_index(nc, "brcm,activity-signal-sources",
					   i, &sel);

		अगर (reg / 4 != sel / 4) अणु
			dev_warn(dev, "invalid activity signal source\n");
			जारी;
		पूर्ण

		spin_lock_irqsave(lock, flags);
		val = bcm6328_led_पढ़ो(addr);
		val |= (BIT(reg % 4) << ((sel % 4) * 4));
		bcm6328_led_ग_लिखो(addr, val);
		spin_unlock_irqrestore(lock, flags);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bcm6328_led(काष्ठा device *dev, काष्ठा device_node *nc, u32 reg,
		       व्योम __iomem *mem, spinlock_t *lock,
		       अचिन्हित दीर्घ *blink_leds, अचिन्हित दीर्घ *blink_delay)
अणु
	काष्ठा led_init_data init_data = अणुपूर्ण;
	काष्ठा bcm6328_led *led;
	स्थिर अक्षर *state;
	पूर्णांक rc;

	led = devm_kzalloc(dev, माप(*led), GFP_KERNEL);
	अगर (!led)
		वापस -ENOMEM;

	led->pin = reg;
	led->mem = mem;
	led->lock = lock;
	led->blink_leds = blink_leds;
	led->blink_delay = blink_delay;

	अगर (of_property_पढ़ो_bool(nc, "active-low"))
		led->active_low = true;

	अगर (!of_property_पढ़ो_string(nc, "default-state", &state)) अणु
		अगर (!म_भेद(state, "on")) अणु
			led->cdev.brightness = LED_FULL;
		पूर्ण अन्यथा अगर (!म_भेद(state, "keep")) अणु
			व्योम __iomem *mode;
			अचिन्हित दीर्घ val, shअगरt;

			shअगरt = bcm6328_pin2shअगरt(led->pin);
			अगर (shअगरt / 16)
				mode = mem + BCM6328_REG_MODE_HI;
			अन्यथा
				mode = mem + BCM6328_REG_MODE_LO;

			val = bcm6328_led_पढ़ो(mode) >>
			      BCM6328_LED_SHIFT(shअगरt % 16);
			val &= BCM6328_LED_MODE_MASK;
			अगर ((led->active_low && val == BCM6328_LED_MODE_OFF) ||
			    (!led->active_low && val == BCM6328_LED_MODE_ON))
				led->cdev.brightness = LED_FULL;
			अन्यथा
				led->cdev.brightness = LED_OFF;
		पूर्ण अन्यथा अणु
			led->cdev.brightness = LED_OFF;
		पूर्ण
	पूर्ण अन्यथा अणु
		led->cdev.brightness = LED_OFF;
	पूर्ण

	bcm6328_led_set(&led->cdev, led->cdev.brightness);

	led->cdev.brightness_set = bcm6328_led_set;
	led->cdev.blink_set = bcm6328_blink_set;
	init_data.fwnode = of_fwnode_handle(nc);

	rc = devm_led_classdev_रेजिस्टर_ext(dev, &led->cdev, &init_data);
	अगर (rc < 0)
		वापस rc;

	dev_dbg(dev, "registered LED %s\n", led->cdev.name);

	वापस 0;
पूर्ण

अटल पूर्णांक bcm6328_leds_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev_of_node(&pdev->dev);
	काष्ठा device_node *child;
	व्योम __iomem *mem;
	spinlock_t *lock; /* memory lock */
	अचिन्हित दीर्घ val, *blink_leds, *blink_delay;

	mem = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(mem))
		वापस PTR_ERR(mem);

	lock = devm_kzalloc(dev, माप(*lock), GFP_KERNEL);
	अगर (!lock)
		वापस -ENOMEM;

	blink_leds = devm_kसुस्मृति(dev, BCM6328_LED_BLINK_DELAYS,
				  माप(*blink_leds), GFP_KERNEL);
	अगर (!blink_leds)
		वापस -ENOMEM;

	blink_delay = devm_kसुस्मृति(dev, BCM6328_LED_BLINK_DELAYS,
				   माप(*blink_delay), GFP_KERNEL);
	अगर (!blink_delay)
		वापस -ENOMEM;

	spin_lock_init(lock);

	bcm6328_led_ग_लिखो(mem + BCM6328_REG_HWDIS, ~0);
	bcm6328_led_ग_लिखो(mem + BCM6328_REG_LNKACTSEL_HI, 0);
	bcm6328_led_ग_लिखो(mem + BCM6328_REG_LNKACTSEL_LO, 0);

	val = bcm6328_led_पढ़ो(mem + BCM6328_REG_INIT);
	val &= ~(BCM6328_INIT_MASK);
	अगर (of_property_पढ़ो_bool(np, "brcm,serial-leds"))
		val |= BCM6328_SERIAL_LED_EN;
	अगर (of_property_पढ़ो_bool(np, "brcm,serial-mux"))
		val |= BCM6328_SERIAL_LED_MUX;
	अगर (of_property_पढ़ो_bool(np, "brcm,serial-clk-low"))
		val |= BCM6328_SERIAL_LED_CLK_NPOL;
	अगर (!of_property_पढ़ो_bool(np, "brcm,serial-dat-low"))
		val |= BCM6328_SERIAL_LED_DATA_PPOL;
	अगर (!of_property_पढ़ो_bool(np, "brcm,serial-shift-inv"))
		val |= BCM6328_SERIAL_LED_SHIFT_सूची;
	bcm6328_led_ग_लिखो(mem + BCM6328_REG_INIT, val);

	क्रम_each_available_child_of_node(np, child) अणु
		पूर्णांक rc;
		u32 reg;

		अगर (of_property_पढ़ो_u32(child, "reg", &reg))
			जारी;

		अगर (reg >= BCM6328_LED_MAX_COUNT) अणु
			dev_err(dev, "invalid LED (%u >= %d)\n", reg,
				BCM6328_LED_MAX_COUNT);
			जारी;
		पूर्ण

		अगर (of_property_पढ़ो_bool(child, "brcm,hardware-controlled"))
			rc = bcm6328_hwled(dev, child, reg, mem, lock);
		अन्यथा
			rc = bcm6328_led(dev, child, reg, mem, lock,
					 blink_leds, blink_delay);

		अगर (rc < 0) अणु
			of_node_put(child);
			वापस rc;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id bcm6328_leds_of_match[] = अणु
	अणु .compatible = "brcm,bcm6328-leds", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, bcm6328_leds_of_match);

अटल काष्ठा platक्रमm_driver bcm6328_leds_driver = अणु
	.probe = bcm6328_leds_probe,
	.driver = अणु
		.name = "leds-bcm6328",
		.of_match_table = bcm6328_leds_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(bcm6328_leds_driver);

MODULE_AUTHOR("थlvaro Fernथँndez Rojas <noltari@gmail.com>");
MODULE_AUTHOR("Jonas Gorski <jogo@openwrt.org>");
MODULE_DESCRIPTION("LED driver for BCM6328 controllers");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:leds-bcm6328");
