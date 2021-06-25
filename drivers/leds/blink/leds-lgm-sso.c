<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Intel Lightning Mountain SoC LED Serial Shअगरt Output Controller driver
 *
 * Copyright (c) 2020 Intel Corporation.
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/clk.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/leds.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/property.h>
#समावेश <linux/regmap.h>
#समावेश <linux/sizes.h>
#समावेश <linux/uaccess.h>

#घोषणा SSO_DEV_NAME			"lgm-sso"

#घोषणा LED_BLINK_H8_0			0x0
#घोषणा LED_BLINK_H8_1			0x4
#घोषणा GET_FREQ_OFFSET(pin, src)	(((pin) * 6) + ((src) * 2))
#घोषणा GET_SRC_OFFSET(pinc)		(((pin) * 6) + 4)

#घोषणा DUTY_CYCLE(x)			(0x8 + ((x) * 4))
#घोषणा SSO_CON0			0x2B0
#घोषणा SSO_CON0_RZFL			BIT(26)
#घोषणा SSO_CON0_BLINK_R		BIT(30)
#घोषणा SSO_CON0_SWU			BIT(31)

#घोषणा SSO_CON1			0x2B4
#घोषणा SSO_CON1_FCDSC			GENMASK(21, 20) /* Fixed Divider Shअगरt Clock */
#घोषणा SSO_CON1_FPID			GENMASK(24, 23)
#घोषणा SSO_CON1_GPTD			GENMASK(26, 25)
#घोषणा SSO_CON1_US			GENMASK(31, 30)

#घोषणा SSO_CPU				0x2B8
#घोषणा SSO_CON2			0x2C4
#घोषणा SSO_CON3			0x2C8

/* Driver MACRO */
#घोषणा MAX_PIN_NUM_PER_BANK		SZ_32
#घोषणा MAX_GROUP_NUM			SZ_4
#घोषणा PINS_PER_GROUP			SZ_8
#घोषणा FPID_FREQ_RANK_MAX		SZ_4
#घोषणा SSO_LED_MAX_NUM			SZ_32
#घोषणा MAX_FREQ_RANK			10
#घोषणा DEF_GPTC_CLK_RATE		200000000
#घोषणा SSO_DEF_BRIGHTNESS		LED_HALF
#घोषणा DATA_CLK_EDGE			0 /* 0-rising, 1-falling */

अटल स्थिर u32 freq_भाग_प्रकारbl[] = अणु4000, 2000, 1000, 800पूर्ण;
अटल स्थिर पूर्णांक freq_tbl[] = अणु2, 4, 8, 10, 50000, 100000, 200000, 250000पूर्ण;
अटल स्थिर पूर्णांक shअगरt_clk_freq_tbl[] = अणु25000000, 12500000, 6250000, 3125000पूर्ण;

/*
 * Update Source to update the SOUTs
 * SW - Software has to update the SWU bit
 * GPTC - General Purpose समयr is used as घड़ी source
 * FPID - Divided FSC घड़ी (FPID) is used as घड़ी source
 */
क्रमागत अणु
	US_SW = 0,
	US_GPTC = 1,
	US_FPID = 2
पूर्ण;

क्रमागत अणु
	MAX_FPID_FREQ_RANK = 5, /* 1 to 4 */
	MAX_GPTC_FREQ_RANK = 9, /* 5 to 8 */
	MAX_GPTC_HS_FREQ_RANK = 10, /* 9 to 10 */
पूर्ण;

क्रमागत अणु
	LED_GRP0_PIN_MAX = 24,
	LED_GRP1_PIN_MAX = 29,
	LED_GRP2_PIN_MAX = 32,
पूर्ण;

क्रमागत अणु
	LED_GRP0_0_23,
	LED_GRP1_24_28,
	LED_GRP2_29_31,
	LED_GROUP_MAX,
पूर्ण;

क्रमागत अणु
	CLK_SRC_FPID = 0,
	CLK_SRC_GPTC = 1,
	CLK_SRC_GPTC_HS = 2,
पूर्ण;

काष्ठा sso_led_priv;

काष्ठा sso_led_desc अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर *शेष_trigger;
	अचिन्हित पूर्णांक brightness;
	अचिन्हित पूर्णांक blink_rate;
	अचिन्हित पूर्णांक retain_state_suspended:1;
	अचिन्हित पूर्णांक retain_state_shutकरोwn:1;
	अचिन्हित पूर्णांक panic_indicator:1;
	अचिन्हित पूर्णांक hw_blink:1;
	अचिन्हित पूर्णांक hw_trig:1;
	अचिन्हित पूर्णांक blinking:1;
	पूर्णांक freq_idx;
	u32 pin;
पूर्ण;

काष्ठा sso_led अणु
	काष्ठा list_head list;
	काष्ठा led_classdev cdev;
	काष्ठा gpio_desc *gpiod;
	काष्ठा sso_led_desc desc;
	काष्ठा sso_led_priv *priv;
पूर्ण;

काष्ठा sso_gpio अणु
	काष्ठा gpio_chip chip;
	पूर्णांक shअगरt_clk_freq;
	पूर्णांक edge;
	पूर्णांक freq;
	u32 pins;
	u32 alloc_biपंचांगap;
पूर्ण;

काष्ठा sso_led_priv अणु
	काष्ठा regmap *mmap;
	काष्ठा device *dev;
	काष्ठा platक्रमm_device *pdev;
	काष्ठा clk *gclk;
	काष्ठा clk *fpid_clk;
	u32 fpid_clkrate;
	u32 gptc_clkrate;
	u32 freq[MAX_FREQ_RANK];
	काष्ठा list_head led_list;
	काष्ठा sso_gpio gpio;
पूर्ण;

अटल पूर्णांक sso_get_blink_rate_idx(काष्ठा sso_led_priv *priv, u32 rate)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MAX_FREQ_RANK; i++) अणु
		अगर (rate <= priv->freq[i])
			वापस i;
	पूर्ण

	वापस -1;
पूर्ण

अटल अचिन्हित पूर्णांक sso_led_pin_to_group(u32 pin)
अणु
	अगर (pin < LED_GRP0_PIN_MAX)
		वापस LED_GRP0_0_23;
	अन्यथा अगर (pin < LED_GRP1_PIN_MAX)
		वापस LED_GRP1_24_28;
	अन्यथा
		वापस LED_GRP2_29_31;
पूर्ण

अटल u32 sso_led_get_freq_src(पूर्णांक freq_idx)
अणु
	अगर (freq_idx < MAX_FPID_FREQ_RANK)
		वापस CLK_SRC_FPID;
	अन्यथा अगर (freq_idx < MAX_GPTC_FREQ_RANK)
		वापस CLK_SRC_GPTC;
	अन्यथा
		वापस CLK_SRC_GPTC_HS;
पूर्ण

अटल u32 sso_led_pin_blink_off(u32 pin, अचिन्हित पूर्णांक group)
अणु
	अगर (group == LED_GRP2_29_31)
		वापस pin - LED_GRP1_PIN_MAX;
	अन्यथा अगर (group == LED_GRP1_24_28)
		वापस pin - LED_GRP0_PIN_MAX;
	अन्यथा	/* led 0 - 23 in led 32 location */
		वापस SSO_LED_MAX_NUM - LED_GRP1_PIN_MAX;
पूर्ण

अटल काष्ठा sso_led
*cdev_to_sso_led_data(काष्ठा led_classdev *led_cdev)
अणु
	वापस container_of(led_cdev, काष्ठा sso_led, cdev);
पूर्ण

अटल व्योम sso_led_freq_set(काष्ठा sso_led_priv *priv, u32 pin, पूर्णांक freq_idx)
अणु
	u32 reg, off, freq_src, val_freq;
	u32 low, high, val;
	अचिन्हित पूर्णांक group;

	अगर (!freq_idx)
		वापस;

	group = sso_led_pin_to_group(pin);
	freq_src = sso_led_get_freq_src(freq_idx);
	off = sso_led_pin_blink_off(pin, group);

	अगर (group == LED_GRP0_0_23)
		वापस;
	अन्यथा अगर (group == LED_GRP1_24_28)
		reg = LED_BLINK_H8_0;
	अन्यथा
		reg = LED_BLINK_H8_1;

	अगर (freq_src == CLK_SRC_FPID)
		val_freq = freq_idx - 1;
	अन्यथा अगर (freq_src == CLK_SRC_GPTC)
		val_freq = freq_idx - MAX_FPID_FREQ_RANK;

	/* set blink rate idx */
	अगर (freq_src != CLK_SRC_GPTC_HS) अणु
		low = GET_FREQ_OFFSET(off, freq_src);
		high = low + 2;
		val = val_freq << high;
		regmap_update_bits(priv->mmap, reg, GENMASK(high, low), val);
	पूर्ण

	/* select घड़ी source */
	low = GET_SRC_OFFSET(off);
	high = low + 2;
	val = freq_src << high;
	regmap_update_bits(priv->mmap, reg, GENMASK(high, low), val);
पूर्ण

अटल व्योम sso_led_brightness_set(काष्ठा led_classdev *led_cdev,
				   क्रमागत led_brightness brightness)
अणु
	काष्ठा sso_led_priv *priv;
	काष्ठा sso_led_desc *desc;
	काष्ठा sso_led *led;
	पूर्णांक val;

	led = cdev_to_sso_led_data(led_cdev);
	priv = led->priv;
	desc = &led->desc;

	desc->brightness = brightness;
	regmap_ग_लिखो(priv->mmap, DUTY_CYCLE(desc->pin), brightness);

	अगर (brightness == LED_OFF)
		val = 0;
	अन्यथा
		val = 1;

	/* HW blink off */
	अगर (desc->hw_blink && !val && desc->blinking) अणु
		desc->blinking = 0;
		regmap_update_bits(priv->mmap, SSO_CON2, BIT(desc->pin), 0);
	पूर्ण अन्यथा अगर (desc->hw_blink && val && !desc->blinking) अणु
		desc->blinking = 1;
		regmap_update_bits(priv->mmap, SSO_CON2, BIT(desc->pin),
				   1 << desc->pin);
	पूर्ण

	अगर (!desc->hw_trig && led->gpiod)
		gpiod_set_value(led->gpiod, val);
पूर्ण

अटल क्रमागत led_brightness sso_led_brightness_get(काष्ठा led_classdev *led_cdev)
अणु
	काष्ठा sso_led *led = cdev_to_sso_led_data(led_cdev);

	वापस (क्रमागत led_brightness)led->desc.brightness;
पूर्ण

अटल पूर्णांक
delay_to_freq_idx(काष्ठा sso_led *led, अचिन्हित दीर्घ *delay_on,
		  अचिन्हित दीर्घ *delay_off)
अणु
	काष्ठा sso_led_priv *priv = led->priv;
	अचिन्हित दीर्घ delay;
	पूर्णांक freq_idx;
	u32 freq;

	अगर (!*delay_on && !*delay_off) अणु
		*delay_on = *delay_off = (1000 / priv->freq[0]) / 2;
		वापस 0;
	पूर्ण

	delay = *delay_on + *delay_off;
	freq = 1000 / delay;

	freq_idx = sso_get_blink_rate_idx(priv, freq);
	अगर (freq_idx == -1)
		freq_idx = MAX_FREQ_RANK - 1;

	delay = 1000 / priv->freq[freq_idx];
	*delay_on = *delay_off = delay / 2;

	अगर (!*delay_on)
		*delay_on = *delay_off = 1;

	वापस freq_idx;
पूर्ण

अटल पूर्णांक
sso_led_blink_set(काष्ठा led_classdev *led_cdev, अचिन्हित दीर्घ *delay_on,
		  अचिन्हित दीर्घ *delay_off)
अणु
	काष्ठा sso_led_priv *priv;
	काष्ठा sso_led *led;
	पूर्णांक freq_idx;

	led = cdev_to_sso_led_data(led_cdev);
	priv = led->priv;
	freq_idx = delay_to_freq_idx(led, delay_on, delay_off);

	sso_led_freq_set(priv, led->desc.pin, freq_idx);
	regmap_update_bits(priv->mmap, SSO_CON2, BIT(led->desc.pin),
			   1 << led->desc.pin);
	led->desc.freq_idx = freq_idx;
	led->desc.blink_rate = priv->freq[freq_idx];
	led->desc.blinking = 1;

	वापस 1;
पूर्ण

अटल व्योम sso_led_hw_cfg(काष्ठा sso_led_priv *priv, काष्ठा sso_led *led)
अणु
	काष्ठा sso_led_desc *desc = &led->desc;

	/* set freq */
	अगर (desc->hw_blink) अणु
		sso_led_freq_set(priv, desc->pin, desc->freq_idx);
		regmap_update_bits(priv->mmap, SSO_CON2, BIT(desc->pin),
				   1 << desc->pin);
	पूर्ण

	अगर (desc->hw_trig)
		regmap_update_bits(priv->mmap, SSO_CON3, BIT(desc->pin),
				   1 << desc->pin);

	/* set brightness */
	regmap_ग_लिखो(priv->mmap, DUTY_CYCLE(desc->pin), desc->brightness);

	/* enable output */
	अगर (!desc->hw_trig && desc->brightness)
		gpiod_set_value(led->gpiod, 1);
पूर्ण

अटल पूर्णांक sso_create_led(काष्ठा sso_led_priv *priv, काष्ठा sso_led *led,
			  काष्ठा fwnode_handle *child)
अणु
	काष्ठा sso_led_desc *desc = &led->desc;
	काष्ठा led_init_data init_data;
	पूर्णांक err;

	init_data.fwnode = child;
	init_data.devicename = SSO_DEV_NAME;
	init_data.शेष_label = ":";

	led->cdev.शेष_trigger = desc->शेष_trigger;
	led->cdev.brightness_set = sso_led_brightness_set;
	led->cdev.brightness_get = sso_led_brightness_get;
	led->cdev.brightness = desc->brightness;
	led->cdev.max_brightness = LED_FULL;

	अगर (desc->retain_state_shutकरोwn)
		led->cdev.flags |= LED_RETAIN_AT_SHUTDOWN;
	अगर (desc->retain_state_suspended)
		led->cdev.flags |= LED_CORE_SUSPENDRESUME;
	अगर (desc->panic_indicator)
		led->cdev.flags |= LED_PANIC_INDICATOR;

	अगर (desc->hw_blink)
		led->cdev.blink_set = sso_led_blink_set;

	sso_led_hw_cfg(priv, led);

	err = devm_led_classdev_रेजिस्टर_ext(priv->dev, &led->cdev, &init_data);
	अगर (err)
		वापस err;

	list_add(&led->list, &priv->led_list);

	वापस 0;
पूर्ण

अटल व्योम sso_init_freq(काष्ठा sso_led_priv *priv)
अणु
	पूर्णांक i;

	priv->freq[0] = 0;
	क्रम (i = 1; i < MAX_FREQ_RANK; i++) अणु
		अगर (i < MAX_FPID_FREQ_RANK) अणु
			priv->freq[i] = priv->fpid_clkrate / freq_भाग_प्रकारbl[i - 1];
		पूर्ण अन्यथा अगर (i < MAX_GPTC_FREQ_RANK) अणु
			priv->freq[i] = priv->gptc_clkrate /
				freq_भाग_प्रकारbl[i - MAX_FPID_FREQ_RANK];
		पूर्ण अन्यथा अगर (i < MAX_GPTC_HS_FREQ_RANK) अणु
			priv->freq[i] = priv->gptc_clkrate;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक sso_gpio_request(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा sso_led_priv *priv = gpiochip_get_data(chip);

	अगर (priv->gpio.alloc_biपंचांगap & BIT(offset))
		वापस -EINVAL;

	priv->gpio.alloc_biपंचांगap |= BIT(offset);
	regmap_ग_लिखो(priv->mmap, DUTY_CYCLE(offset), 0xFF);

	वापस 0;
पूर्ण

अटल व्योम sso_gpio_मुक्त(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा sso_led_priv *priv = gpiochip_get_data(chip);

	priv->gpio.alloc_biपंचांगap &= ~BIT(offset);
	regmap_ग_लिखो(priv->mmap, DUTY_CYCLE(offset), 0x0);
पूर्ण

अटल पूर्णांक sso_gpio_get_dir(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	वापस GPIOF_सूची_OUT;
पूर्ण

अटल पूर्णांक
sso_gpio_dir_out(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset, पूर्णांक value)
अणु
	काष्ठा sso_led_priv *priv = gpiochip_get_data(chip);
	bool bit = !!value;

	regmap_update_bits(priv->mmap, SSO_CPU, BIT(offset), bit << offset);
	अगर (!priv->gpio.freq)
		regmap_update_bits(priv->mmap, SSO_CON0, SSO_CON0_SWU,
				   SSO_CON0_SWU);

	वापस 0;
पूर्ण

अटल पूर्णांक sso_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा sso_led_priv *priv = gpiochip_get_data(chip);
	u32 reg_val;

	regmap_पढ़ो(priv->mmap, SSO_CPU, &reg_val);

	वापस !!(reg_val & BIT(offset));
पूर्ण

अटल व्योम sso_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset, पूर्णांक value)
अणु
	काष्ठा sso_led_priv *priv = gpiochip_get_data(chip);

	regmap_update_bits(priv->mmap, SSO_CPU, BIT(offset), value << offset);
	अगर (!priv->gpio.freq)
		regmap_update_bits(priv->mmap, SSO_CON0, SSO_CON0_SWU,
				   SSO_CON0_SWU);
पूर्ण

अटल पूर्णांक sso_gpio_gc_init(काष्ठा device *dev, काष्ठा sso_led_priv *priv)
अणु
	काष्ठा gpio_chip *gc = &priv->gpio.chip;

	gc->request             = sso_gpio_request;
	gc->मुक्त                = sso_gpio_मुक्त;
	gc->get_direction       = sso_gpio_get_dir;
	gc->direction_output    = sso_gpio_dir_out;
	gc->get                 = sso_gpio_get;
	gc->set                 = sso_gpio_set;

	gc->label               = "lgm-sso";
	gc->base                = -1;
	/* To exclude pins from control, use "gpio-reserved-ranges" */
	gc->ngpio               = priv->gpio.pins;
	gc->parent              = dev;
	gc->owner               = THIS_MODULE;
	gc->of_node             = dev->of_node;

	वापस devm_gpiochip_add_data(dev, gc, priv);
पूर्ण

अटल पूर्णांक sso_gpio_get_freq_idx(पूर्णांक freq)
अणु
	पूर्णांक idx;

	क्रम (idx = 0; idx < ARRAY_SIZE(freq_tbl); idx++) अणु
		अगर (freq <= freq_tbl[idx])
			वापस idx;
	पूर्ण

	वापस -1;
पूर्ण

अटल व्योम sso_रेजिस्टर_shअगरt_clk(काष्ठा sso_led_priv *priv)
अणु
	पूर्णांक idx, size = ARRAY_SIZE(shअगरt_clk_freq_tbl);
	u32 val = 0;

	क्रम (idx = 0; idx < size; idx++) अणु
		अगर (shअगरt_clk_freq_tbl[idx] <= priv->gpio.shअगरt_clk_freq) अणु
			val = idx;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (idx == size)
		dev_warn(priv->dev, "%s: Invalid freq %d\n",
			 __func__, priv->gpio.shअगरt_clk_freq);

	regmap_update_bits(priv->mmap, SSO_CON1, SSO_CON1_FCDSC,
			   FIELD_PREP(SSO_CON1_FCDSC, val));
पूर्ण

अटल पूर्णांक sso_gpio_freq_set(काष्ठा sso_led_priv *priv)
अणु
	पूर्णांक freq_idx;
	u32 val;

	freq_idx = sso_gpio_get_freq_idx(priv->gpio.freq);
	अगर (freq_idx == -1)
		freq_idx = ARRAY_SIZE(freq_tbl) - 1;

	val = freq_idx % FPID_FREQ_RANK_MAX;

	अगर (!priv->gpio.freq) अणु
		regmap_update_bits(priv->mmap, SSO_CON0, SSO_CON0_BLINK_R, 0);
		regmap_update_bits(priv->mmap, SSO_CON1, SSO_CON1_US,
				   FIELD_PREP(SSO_CON1_US, US_SW));
	पूर्ण अन्यथा अगर (freq_idx < FPID_FREQ_RANK_MAX) अणु
		regmap_update_bits(priv->mmap, SSO_CON0, SSO_CON0_BLINK_R,
				   SSO_CON0_BLINK_R);
		regmap_update_bits(priv->mmap, SSO_CON1, SSO_CON1_US,
				   FIELD_PREP(SSO_CON1_US, US_FPID));
		regmap_update_bits(priv->mmap, SSO_CON1, SSO_CON1_FPID,
				   FIELD_PREP(SSO_CON1_FPID, val));
	पूर्ण अन्यथा अणु
		regmap_update_bits(priv->mmap, SSO_CON0, SSO_CON0_BLINK_R,
				   SSO_CON0_BLINK_R);
		regmap_update_bits(priv->mmap, SSO_CON1, SSO_CON1_US,
				   FIELD_PREP(SSO_CON1_US, US_GPTC));
		regmap_update_bits(priv->mmap, SSO_CON1, SSO_CON1_GPTD,
				   FIELD_PREP(SSO_CON1_GPTD, val));
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sso_gpio_hw_init(काष्ठा sso_led_priv *priv)
अणु
	u32 activate;
	पूर्णांक i, err;

	/* Clear all duty cycles */
	क्रम (i = 0; i < priv->gpio.pins; i++) अणु
		err = regmap_ग_लिखो(priv->mmap, DUTY_CYCLE(i), 0);
		अगर (err)
			वापस err;
	पूर्ण

	/* 4 groups क्रम total 32 pins */
	क्रम (i = 1; i <= MAX_GROUP_NUM; i++) अणु
		activate = !!(i * PINS_PER_GROUP <= priv->gpio.pins ||
			      priv->gpio.pins > (i - 1) * PINS_PER_GROUP);
		err = regmap_update_bits(priv->mmap, SSO_CON1, BIT(i - 1),
					 activate << (i - 1));
		अगर (err)
			वापस err;
	पूर्ण

	/* NO HW directly controlled pin by शेष */
	err = regmap_ग_लिखो(priv->mmap, SSO_CON3, 0);
	अगर (err)
		वापस err;

	/* NO BLINK क्रम all pins */
	err = regmap_ग_लिखो(priv->mmap, SSO_CON2, 0);
	अगर (err)
		वापस err;

	/* OUTPUT 0 by शेष */
	err = regmap_ग_लिखो(priv->mmap, SSO_CPU, 0);
	अगर (err)
		वापस err;

	/* update edge */
	err = regmap_update_bits(priv->mmap, SSO_CON0, SSO_CON0_RZFL,
				 FIELD_PREP(SSO_CON0_RZFL, priv->gpio.edge));
	अगर (err)
		वापस err;

	/* Set GPIO update rate */
	sso_gpio_freq_set(priv);

	/* Register shअगरt घड़ी */
	sso_रेजिस्टर_shअगरt_clk(priv);

	वापस 0;
पूर्ण

अटल व्योम sso_led_shutकरोwn(काष्ठा sso_led *led)
अणु
	काष्ठा sso_led_priv *priv = led->priv;

	/* unरेजिस्टर led */
	devm_led_classdev_unरेजिस्टर(priv->dev, &led->cdev);

	/* clear HW control bit */
	अगर (led->desc.hw_trig)
		regmap_update_bits(priv->mmap, SSO_CON3, BIT(led->desc.pin), 0);

	अगर (led->gpiod)
		devm_gpiod_put(priv->dev, led->gpiod);

	led->priv = शून्य;
पूर्ण

अटल पूर्णांक
__sso_led_dt_parse(काष्ठा sso_led_priv *priv, काष्ठा fwnode_handle *fw_ssoled)
अणु
	काष्ठा fwnode_handle *fwnode_child;
	काष्ठा device *dev = priv->dev;
	काष्ठा sso_led_desc *desc;
	काष्ठा sso_led *led;
	काष्ठा list_head *p;
	स्थिर अक्षर *पंचांगp;
	u32 prop;
	पूर्णांक ret;

	fwnode_क्रम_each_child_node(fw_ssoled, fwnode_child) अणु
		led = devm_kzalloc(dev, माप(*led), GFP_KERNEL);
		अगर (!led)
			वापस -ENOMEM;

		INIT_LIST_HEAD(&led->list);
		led->priv = priv;
		desc = &led->desc;

		led->gpiod = devm_fwnode_get_gpiod_from_child(dev, शून्य,
							      fwnode_child,
							      GPIOD_ASIS, शून्य);
		अगर (IS_ERR(led->gpiod)) अणु
			dev_err(dev, "led: get gpio fail!\n");
			जाओ __dt_err;
		पूर्ण

		fwnode_property_पढ़ो_string(fwnode_child,
					    "linux,default-trigger",
					    &desc->शेष_trigger);

		अगर (fwnode_property_present(fwnode_child,
					    "retain-state-suspended"))
			desc->retain_state_suspended = 1;

		अगर (fwnode_property_present(fwnode_child,
					    "retain-state-shutdown"))
			desc->retain_state_shutकरोwn = 1;

		अगर (fwnode_property_present(fwnode_child, "panic-indicator"))
			desc->panic_indicator = 1;

		ret = fwnode_property_पढ़ो_u32(fwnode_child, "reg", &prop);
		अगर (ret != 0 || prop >= SSO_LED_MAX_NUM) अणु
			dev_err(dev, "invalid LED pin:%u\n", prop);
			जाओ __dt_err;
		पूर्ण
		desc->pin = prop;

		अगर (fwnode_property_present(fwnode_child, "intel,sso-hw-blink"))
			desc->hw_blink = 1;

		desc->hw_trig = fwnode_property_पढ़ो_bool(fwnode_child,
							  "intel,sso-hw-trigger");
		अगर (desc->hw_trig) अणु
			desc->शेष_trigger = शून्य;
			desc->retain_state_shutकरोwn = 0;
			desc->retain_state_suspended = 0;
			desc->panic_indicator = 0;
			desc->hw_blink = 0;
		पूर्ण

		अगर (fwnode_property_पढ़ो_u32(fwnode_child,
					     "intel,sso-blink-rate-hz", &prop)) अणु
			/* शेष first freq rate */
			desc->freq_idx = 0;
			desc->blink_rate = priv->freq[desc->freq_idx];
		पूर्ण अन्यथा अणु
			desc->freq_idx = sso_get_blink_rate_idx(priv, prop);
			अगर (desc->freq_idx == -1)
				desc->freq_idx = MAX_FREQ_RANK - 1;

			desc->blink_rate = priv->freq[desc->freq_idx];
		पूर्ण

		अगर (!fwnode_property_पढ़ो_string(fwnode_child, "default-state", &पंचांगp)) अणु
			अगर (!म_भेद(पंचांगp, "on"))
				desc->brightness = LED_FULL;
		पूर्ण

		अगर (sso_create_led(priv, led, fwnode_child))
			जाओ __dt_err;
	पूर्ण
	fwnode_handle_put(fw_ssoled);

	वापस 0;
__dt_err:
	fwnode_handle_put(fw_ssoled);
	/* unरेजिस्टर leds */
	list_क्रम_each(p, &priv->led_list) अणु
		led = list_entry(p, काष्ठा sso_led, list);
		sso_led_shutकरोwn(led);
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक sso_led_dt_parse(काष्ठा sso_led_priv *priv)
अणु
	काष्ठा fwnode_handle *fwnode = dev_fwnode(priv->dev);
	काष्ठा fwnode_handle *fw_ssoled;
	काष्ठा device *dev = priv->dev;
	पूर्णांक count;
	पूर्णांक ret;

	count = device_get_child_node_count(dev);
	अगर (!count)
		वापस 0;

	fw_ssoled = fwnode_get_named_child_node(fwnode, "ssoled");
	अगर (fw_ssoled) अणु
		ret = __sso_led_dt_parse(priv, fw_ssoled);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sso_probe_gpios(काष्ठा sso_led_priv *priv)
अणु
	काष्ठा device *dev = priv->dev;
	पूर्णांक ret;

	अगर (device_property_पढ़ो_u32(dev, "ngpios", &priv->gpio.pins))
		priv->gpio.pins = MAX_PIN_NUM_PER_BANK;

	अगर (priv->gpio.pins > MAX_PIN_NUM_PER_BANK)
		वापस -EINVAL;

	अगर (device_property_पढ़ो_u32(dev, "intel,sso-update-rate-hz",
				     &priv->gpio.freq))
		priv->gpio.freq = 0;

	priv->gpio.edge = DATA_CLK_EDGE;
	priv->gpio.shअगरt_clk_freq = -1;

	ret = sso_gpio_hw_init(priv);
	अगर (ret)
		वापस ret;

	वापस sso_gpio_gc_init(dev, priv);
पूर्ण

अटल व्योम sso_clk_disable(व्योम *data)
अणु
	काष्ठा sso_led_priv *priv = data;

	clk_disable_unprepare(priv->fpid_clk);
	clk_disable_unprepare(priv->gclk);
पूर्ण

अटल पूर्णांक पूर्णांकel_sso_led_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा sso_led_priv *priv;
	पूर्णांक ret;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->pdev = pdev;
	priv->dev = dev;

	/* gate घड़ी */
	priv->gclk = devm_clk_get(dev, "sso");
	अगर (IS_ERR(priv->gclk)) अणु
		dev_err(dev, "get sso gate clock failed!\n");
		वापस PTR_ERR(priv->gclk);
	पूर्ण

	ret = clk_prepare_enable(priv->gclk);
	अगर (ret) अणु
		dev_err(dev, "Failed to prepare/enable sso gate clock!\n");
		वापस ret;
	पूर्ण

	priv->fpid_clk = devm_clk_get(dev, "fpid");
	अगर (IS_ERR(priv->fpid_clk)) अणु
		dev_err(dev, "Failed to get fpid clock!\n");
		वापस PTR_ERR(priv->fpid_clk);
	पूर्ण

	ret = clk_prepare_enable(priv->fpid_clk);
	अगर (ret) अणु
		dev_err(dev, "Failed to prepare/enable fpid clock!\n");
		वापस ret;
	पूर्ण
	priv->fpid_clkrate = clk_get_rate(priv->fpid_clk);

	ret = devm_add_action_or_reset(dev, sso_clk_disable, priv);
	अगर (ret) अणु
		dev_err(dev, "Failed to devm_add_action_or_reset, %d\n", ret);
		वापस ret;
	पूर्ण

	priv->mmap = syscon_node_to_regmap(dev->of_node);
	अगर (IS_ERR(priv->mmap)) अणु
		dev_err(dev, "Failed to map iomem!\n");
		वापस PTR_ERR(priv->mmap);
	पूर्ण

	ret = sso_probe_gpios(priv);
	अगर (ret) अणु
		regmap_निकास(priv->mmap);
		वापस ret;
	पूर्ण

	INIT_LIST_HEAD(&priv->led_list);

	platक्रमm_set_drvdata(pdev, priv);
	sso_init_freq(priv);

	priv->gptc_clkrate = DEF_GPTC_CLK_RATE;

	ret = sso_led_dt_parse(priv);
	अगर (ret) अणु
		regmap_निकास(priv->mmap);
		वापस ret;
	पूर्ण
	dev_info(priv->dev, "sso LED init success!\n");

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_sso_led_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sso_led_priv *priv;
	काष्ठा list_head *pos, *n;
	काष्ठा sso_led *led;

	priv = platक्रमm_get_drvdata(pdev);

	list_क्रम_each_safe(pos, n, &priv->led_list) अणु
		list_del(pos);
		led = list_entry(pos, काष्ठा sso_led, list);
		sso_led_shutकरोwn(led);
	पूर्ण

	clk_disable_unprepare(priv->fpid_clk);
	clk_disable_unprepare(priv->gclk);
	regmap_निकास(priv->mmap);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id of_sso_led_match[] = अणु
	अणु .compatible = "intel,lgm-ssoled" पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, of_sso_led_match);

अटल काष्ठा platक्रमm_driver पूर्णांकel_sso_led_driver = अणु
	.probe		= पूर्णांकel_sso_led_probe,
	.हटाओ		= पूर्णांकel_sso_led_हटाओ,
	.driver		= अणु
			.name = "lgm-ssoled",
			.of_match_table = of_match_ptr(of_sso_led_match),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(पूर्णांकel_sso_led_driver);

MODULE_DESCRIPTION("Intel SSO LED/GPIO driver");
MODULE_LICENSE("GPL v2");
