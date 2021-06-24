<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * leds-tca6507
 *
 * The TCA6507 is a programmable LED controller that can drive 7
 * separate lines either by holding them low, or by pulsing them
 * with modulated width.
 * The modulation can be varied in a simple pattern to produce a
 * blink or द्विगुन-blink.
 *
 * This driver can configure each line either as a 'GPIO' which is
 * out-only (pull-up resistor required) or as an LED with variable
 * brightness and hardware-assisted blinking.
 *
 * Apart from OFF and ON there are three programmable brightness
 * levels which can be programmed from 0 to 15 and indicate how many
 * 500usec पूर्णांकervals in each 8msec that the led is 'on'.  The levels
 * are named MASTER, BANK0 and BANK1.
 *
 * There are two dअगरferent blink rates that can be programmed, each
 * with separate समय क्रम rise, on, fall, off and second-off.  Thus अगर
 * 3 or more dअगरferent non-trivial rates are required, software must
 * be used क्रम the extra rates. The two dअगरferent blink rates must
 * align with the two levels BANK0 and BANK1.  This driver करोes not
 * support द्विगुन-blink so 'second-off' always matches 'off'.
 *
 * Only 16 dअगरferent बार can be programmed in a roughly logarithmic
 * scale from 64ms to 16320ms.  To be precise the possible बार are:
 *    0, 64, 128, 192, 256, 384, 512, 768,
 *    1024, 1536, 2048, 3072, 4096, 5760, 8128, 16320
 *
 * Times that cannot be बंदly matched with these must be handled in
 * software.  This driver allows 12.5% error in matching.
 *
 * This driver करोes not allow rise/fall rates to be set explicitly.
 * When trying to match a given 'on' or 'off' period, an appropriate
 * pair of 'change' and 'hold' बार are chosen to get a बंद match.
 * If the target delay is even, the 'change' number will be the
 * smaller; अगर odd, the 'hold' number will be the smaller.

 * Choosing pairs of delays with 12.5% errors allows us to match
 * delays in the ranges: 56-72, 112-144, 168-216, 224-27504,
 * 28560-36720.
 * 26% of the achievable sums can be matched by multiple pairings.
 * For example 1536 == 1536+0, 1024+512, or 768+768.
 * This driver will always choose the pairing with the least
 * maximum - 768+768 in this हाल.  Other pairings are not available.
 *
 * Access to the 3 levels and 2 blinks are on a first-come,
 * first-served basis.  Access can be shared by multiple leds अगर they
 * have the same level and either same blink rates, or some करोn't
 * blink.  When a led changes, it relinquishes access and tries again,
 * so it might lose access to hardware blink.
 *
 * If a blink engine cannot be allocated, software blink is used.  If
 * the desired brightness cannot be allocated, the बंदst available
 * non-zero brightness is used.  As 'full' is always available, the
 * worst हाल would be to have two dअगरferent blink rates at '1', with
 * Max at '2', then other leds will have to choose between '2' and
 * '16'.  Hopefully this is not likely.
 *
 * Each bank (BANK0 and BANK1) has two usage counts - LEDs using the
 * brightness and LEDs using the blink.  It can only be reprogrammed
 * when the appropriate counter is zero.  The MASTER level has a
 * single usage count.
 *
 * Each LED has programmable 'on' and 'off' समय as milliseconds.
 * With each there is a flag saying अगर it was explicitly requested or
 * शेषed.  Similarly the banks know अगर each समय was explicit or a
 * शेष.  Defaults are permitted to be changed मुक्तly - they are
 * not recognised when matching.
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/leds.h>
#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/property.h>
#समावेश <linux/workqueue.h>

/* LED select रेजिस्टरs determine the source that drives LED outमाला_दो */
#घोषणा TCA6507_LS_LED_OFF	0x0	/* Output HI-Z (off) */
#घोषणा TCA6507_LS_LED_OFF1	0x1	/* Output HI-Z (off) - not used */
#घोषणा TCA6507_LS_LED_PWM0	0x2	/* Output LOW with Bank0 rate */
#घोषणा TCA6507_LS_LED_PWM1	0x3	/* Output LOW with Bank1 rate */
#घोषणा TCA6507_LS_LED_ON	0x4	/* Output LOW (on) */
#घोषणा TCA6507_LS_LED_MIR	0x5	/* Output LOW with Master Intensity */
#घोषणा TCA6507_LS_BLINK0	0x6	/* Blink at Bank0 rate */
#घोषणा TCA6507_LS_BLINK1	0x7	/* Blink at Bank1 rate */

काष्ठा tca6507_platक्रमm_data अणु
	काष्ठा led_platक्रमm_data leds;
#अगर_घोषित CONFIG_GPIOLIB
	पूर्णांक gpio_base;
#पूर्ण_अगर
पूर्ण;

#घोषणा	TCA6507_MAKE_GPIO 1

क्रमागत अणु
	BANK0,
	BANK1,
	MASTER,
पूर्ण;
अटल पूर्णांक bank_source[3] = अणु
	TCA6507_LS_LED_PWM0,
	TCA6507_LS_LED_PWM1,
	TCA6507_LS_LED_MIR,
पूर्ण;
अटल पूर्णांक blink_source[2] = अणु
	TCA6507_LS_BLINK0,
	TCA6507_LS_BLINK1,
पूर्ण;

/* PWM रेजिस्टरs */
#घोषणा	TCA6507_REG_CNT			11

/*
 * 0x00, 0x01, 0x02 encode the TCA6507_LS_* values, each output
 * owns one bit in each रेजिस्टर
 */
#घोषणा	TCA6507_FADE_ON			0x03
#घोषणा	TCA6507_FULL_ON			0x04
#घोषणा	TCA6507_FADE_OFF		0x05
#घोषणा	TCA6507_FIRST_OFF		0x06
#घोषणा	TCA6507_SECOND_OFF		0x07
#घोषणा	TCA6507_MAX_INTENSITY		0x08
#घोषणा	TCA6507_MASTER_INTENSITY	0x09
#घोषणा	TCA6507_INITIALIZE		0x0A

#घोषणा	INIT_CODE			0x8

#घोषणा TIMECODES 16
अटल पूर्णांक समय_codes[TIMECODES] = अणु
	0, 64, 128, 192, 256, 384, 512, 768,
	1024, 1536, 2048, 3072, 4096, 5760, 8128, 16320
पूर्ण;

/* Convert an led.brightness level (0..255) to a TCA6507 level (0..15) */
अटल अंतरभूत पूर्णांक TO_LEVEL(पूर्णांक brightness)
अणु
	वापस brightness >> 4;
पूर्ण

/* ...and convert back */
अटल अंतरभूत पूर्णांक TO_BRIGHT(पूर्णांक level)
अणु
	अगर (level)
		वापस (level << 4) | 0xf;
	वापस 0;
पूर्ण

#घोषणा NUM_LEDS 7
काष्ठा tca6507_chip अणु
	पूर्णांक			reg_set;	/* One bit per रेजिस्टर where
						 * a '1' means the रेजिस्टर
						 * should be written */
	u8			reg_file[TCA6507_REG_CNT];
	/* Bank 2 is Master Intensity and करोesn't use बार */
	काष्ठा bank अणु
		पूर्णांक level;
		पूर्णांक onसमय, offसमय;
		पूर्णांक on_dflt, off_dflt;
		पूर्णांक समय_use, level_use;
	पूर्ण bank[3];
	काष्ठा i2c_client	*client;
	काष्ठा work_काष्ठा	work;
	spinlock_t		lock;

	काष्ठा tca6507_led अणु
		काष्ठा tca6507_chip	*chip;
		काष्ठा led_classdev	led_cdev;
		पूर्णांक			num;
		पूर्णांक			onसमय, offसमय;
		पूर्णांक			on_dflt, off_dflt;
		पूर्णांक			bank;	/* Bank used, or -1 */
		पूर्णांक			blink;	/* Set अगर hardware-blinking */
	पूर्ण leds[NUM_LEDS];
#अगर_घोषित CONFIG_GPIOLIB
	काष्ठा gpio_chip		gpio;
	पूर्णांक				gpio_map[NUM_LEDS];
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा i2c_device_id tca6507_id[] = अणु
	अणु "tca6507" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, tca6507_id);

अटल पूर्णांक choose_बार(पूर्णांक msec, पूर्णांक *c1p, पूर्णांक *c2p)
अणु
	/*
	 * Choose two समयcodes which add to 'msec' as near as
	 * possible.  The first वापसed is the 'on' or 'off' समय.
	 * The second is to be used as a 'fade-on' or 'fade-off' समय.
	 * If 'msec' is even, the first will not be smaller than the
	 * second.  If 'msec' is odd, the first will not be larger
	 * than the second.
	 * If we cannot get a sum within 1/8 of 'msec' fail with
	 * -EINVAL, otherwise वापस the sum that was achieved, plus 1
	 * अगर the first is smaller.
	 * If two possibilities are equally good (e.g. 512+0,
	 * 256+256), choose the first pair so there is more
	 * change-समय visible (i.e. it is softer).
	 */
	पूर्णांक c1, c2;
	पूर्णांक पंचांगax = msec * 9 / 8;
	पूर्णांक पंचांगin = msec * 7 / 8;
	पूर्णांक dअगरf = 65536;

	/* We start at '1' to ensure we never even think of choosing a
	 * total समय of '0'.
	 */
	क्रम (c1 = 1; c1 < TIMECODES; c1++) अणु
		पूर्णांक t = समय_codes[c1];
		अगर (t*2 < पंचांगin)
			जारी;
		अगर (t > पंचांगax)
			अवरोध;
		क्रम (c2 = 0; c2 <= c1; c2++) अणु
			पूर्णांक tt = t + समय_codes[c2];
			पूर्णांक d;
			अगर (tt < पंचांगin)
				जारी;
			अगर (tt > पंचांगax)
				अवरोध;
			/* This works! */
			d = असल(msec - tt);
			अगर (d >= dअगरf)
				जारी;
			/* Best yet */
			*c1p = c1;
			*c2p = c2;
			dअगरf = d;
			अगर (d == 0)
				वापस msec;
		पूर्ण
	पूर्ण
	अगर (dअगरf < 65536) अणु
		पूर्णांक actual;
		अगर (msec & 1) अणु
			c1 = *c2p;
			*c2p = *c1p;
			*c1p = c1;
		पूर्ण
		actual = समय_codes[*c1p] + समय_codes[*c2p];
		अगर (*c1p < *c2p)
			वापस actual + 1;
		अन्यथा
			वापस actual;
	पूर्ण
	/* No बंद match */
	वापस -EINVAL;
पूर्ण

/*
 * Update the रेजिस्टर file with the appropriate 3-bit state क्रम the
 * given led.
 */
अटल व्योम set_select(काष्ठा tca6507_chip *tca, पूर्णांक led, पूर्णांक val)
अणु
	पूर्णांक mask = (1 << led);
	पूर्णांक bit;

	क्रम (bit = 0; bit < 3; bit++) अणु
		पूर्णांक n = tca->reg_file[bit] & ~mask;
		अगर (val & (1 << bit))
			n |= mask;
		अगर (tca->reg_file[bit] != n) अणु
			tca->reg_file[bit] = n;
			tca->reg_set |= (1 << bit);
		पूर्ण
	पूर्ण
पूर्ण

/* Update the रेजिस्टर file with the appropriate 4-bit code क्रम one
 * bank or other.  This can be used क्रम समयrs, क्रम levels, or क्रम
 * initialization.
 */
अटल व्योम set_code(काष्ठा tca6507_chip *tca, पूर्णांक reg, पूर्णांक bank, पूर्णांक new)
अणु
	पूर्णांक mask = 0xF;
	पूर्णांक n;
	अगर (bank) अणु
		mask <<= 4;
		new <<= 4;
	पूर्ण
	n = tca->reg_file[reg] & ~mask;
	n |= new;
	अगर (tca->reg_file[reg] != n) अणु
		tca->reg_file[reg] = n;
		tca->reg_set |= 1 << reg;
	पूर्ण
पूर्ण

/* Update brightness level. */
अटल व्योम set_level(काष्ठा tca6507_chip *tca, पूर्णांक bank, पूर्णांक level)
अणु
	चयन (bank) अणु
	हाल BANK0:
	हाल BANK1:
		set_code(tca, TCA6507_MAX_INTENSITY, bank, level);
		अवरोध;
	हाल MASTER:
		set_code(tca, TCA6507_MASTER_INTENSITY, 0, level);
		अवरोध;
	पूर्ण
	tca->bank[bank].level = level;
पूर्ण

/* Record all relevant समय codes क्रम a given bank */
अटल व्योम set_बार(काष्ठा tca6507_chip *tca, पूर्णांक bank)
अणु
	पूर्णांक c1, c2;
	पूर्णांक result;

	result = choose_बार(tca->bank[bank].onसमय, &c1, &c2);
	अगर (result < 0)
		वापस;
	dev_dbg(&tca->client->dev,
		"Chose on  times %d(%d) %d(%d) for %dms\n",
		c1, समय_codes[c1],
		c2, समय_codes[c2], tca->bank[bank].onसमय);
	set_code(tca, TCA6507_FADE_ON, bank, c2);
	set_code(tca, TCA6507_FULL_ON, bank, c1);
	tca->bank[bank].onसमय = result;

	result = choose_बार(tca->bank[bank].offसमय, &c1, &c2);
	dev_dbg(&tca->client->dev,
		"Chose off times %d(%d) %d(%d) for %dms\n",
		c1, समय_codes[c1],
		c2, समय_codes[c2], tca->bank[bank].offसमय);
	set_code(tca, TCA6507_FADE_OFF, bank, c2);
	set_code(tca, TCA6507_FIRST_OFF, bank, c1);
	set_code(tca, TCA6507_SECOND_OFF, bank, c1);
	tca->bank[bank].offसमय = result;

	set_code(tca, TCA6507_INITIALIZE, bank, INIT_CODE);
पूर्ण

/* Write all needed रेजिस्टर of tca6507 */

अटल व्योम tca6507_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा tca6507_chip *tca = container_of(work, काष्ठा tca6507_chip,
						work);
	काष्ठा i2c_client *cl = tca->client;
	पूर्णांक set;
	u8 file[TCA6507_REG_CNT];
	पूर्णांक r;

	spin_lock_irq(&tca->lock);
	set = tca->reg_set;
	स_नकल(file, tca->reg_file, TCA6507_REG_CNT);
	tca->reg_set = 0;
	spin_unlock_irq(&tca->lock);

	क्रम (r = 0; r < TCA6507_REG_CNT; r++)
		अगर (set & (1<<r))
			i2c_smbus_ग_लिखो_byte_data(cl, r, file[r]);
पूर्ण

अटल व्योम led_release(काष्ठा tca6507_led *led)
अणु
	/* If led owns any resource, release it. */
	काष्ठा tca6507_chip *tca = led->chip;
	अगर (led->bank >= 0) अणु
		काष्ठा bank *b = tca->bank + led->bank;
		अगर (led->blink)
			b->समय_use--;
		b->level_use--;
	पूर्ण
	led->blink = 0;
	led->bank = -1;
पूर्ण

अटल पूर्णांक led_prepare(काष्ठा tca6507_led *led)
अणु
	/* Assign this led to a bank, configuring that bank अगर
	 * necessary. */
	पूर्णांक level = TO_LEVEL(led->led_cdev.brightness);
	काष्ठा tca6507_chip *tca = led->chip;
	पूर्णांक c1, c2;
	पूर्णांक i;
	काष्ठा bank *b;
	पूर्णांक need_init = 0;

	led->led_cdev.brightness = TO_BRIGHT(level);
	अगर (level == 0) अणु
		set_select(tca, led->num, TCA6507_LS_LED_OFF);
		वापस 0;
	पूर्ण

	अगर (led->onसमय == 0 || led->offसमय == 0) अणु
		/*
		 * Just set the brightness, choosing first usable
		 * bank.  If none perfect, choose best.  Count
		 * backwards so we check MASTER bank first to aव्योम
		 * wasting a समयr.
		 */
		पूर्णांक best = -1;/* full-on */
		पूर्णांक dअगरf = 15-level;

		अगर (level == 15) अणु
			set_select(tca, led->num, TCA6507_LS_LED_ON);
			वापस 0;
		पूर्ण

		क्रम (i = MASTER; i >= BANK0; i--) अणु
			पूर्णांक d;
			अगर (tca->bank[i].level == level ||
			    tca->bank[i].level_use == 0) अणु
				best = i;
				अवरोध;
			पूर्ण
			d = असल(level - tca->bank[i].level);
			अगर (d < dअगरf) अणु
				dअगरf = d;
				best = i;
			पूर्ण
		पूर्ण
		अगर (best == -1) अणु
			/* Best brightness is full-on */
			set_select(tca, led->num, TCA6507_LS_LED_ON);
			led->led_cdev.brightness = LED_FULL;
			वापस 0;
		पूर्ण

		अगर (!tca->bank[best].level_use)
			set_level(tca, best, level);

		tca->bank[best].level_use++;
		led->bank = best;
		set_select(tca, led->num, bank_source[best]);
		led->led_cdev.brightness = TO_BRIGHT(tca->bank[best].level);
		वापस 0;
	पूर्ण

	/*
	 * We have on/off समय so we need to try to allocate a timing
	 * bank.  First check अगर बार are compatible with hardware
	 * and give up अगर not.
	 */
	अगर (choose_बार(led->onसमय, &c1, &c2) < 0)
		वापस -EINVAL;
	अगर (choose_बार(led->offसमय, &c1, &c2) < 0)
		वापस -EINVAL;

	क्रम (i = BANK0; i <= BANK1; i++) अणु
		अगर (tca->bank[i].level_use == 0)
			/* not in use - it is ours! */
			अवरोध;
		अगर (tca->bank[i].level != level)
			/* Incompatible level - skip */
			/* FIX: अगर समयr matches we maybe should consider
			 * this anyway...
			 */
			जारी;

		अगर (tca->bank[i].समय_use == 0)
			/* Timer not in use, and level matches - use it */
			अवरोध;

		अगर (!(tca->bank[i].on_dflt ||
		      led->on_dflt ||
		      tca->bank[i].onसमय == led->onसमय))
			/* on समय is incompatible */
			जारी;

		अगर (!(tca->bank[i].off_dflt ||
		      led->off_dflt ||
		      tca->bank[i].offसमय == led->offसमय))
			/* off समय is incompatible */
			जारी;

		/* looks like a suitable match */
		अवरोध;
	पूर्ण

	अगर (i > BANK1)
		/* Nothing matches - how sad */
		वापस -EINVAL;

	b = &tca->bank[i];
	अगर (b->level_use == 0)
		set_level(tca, i, level);
	b->level_use++;
	led->bank = i;

	अगर (b->on_dflt ||
	    !led->on_dflt ||
	    b->समय_use == 0) अणु
		b->onसमय = led->onसमय;
		b->on_dflt = led->on_dflt;
		need_init = 1;
	पूर्ण

	अगर (b->off_dflt ||
	    !led->off_dflt ||
	    b->समय_use == 0) अणु
		b->offसमय = led->offसमय;
		b->off_dflt = led->off_dflt;
		need_init = 1;
	पूर्ण

	अगर (need_init)
		set_बार(tca, i);

	led->onसमय = b->onसमय;
	led->offसमय = b->offसमय;

	b->समय_use++;
	led->blink = 1;
	led->led_cdev.brightness = TO_BRIGHT(b->level);
	set_select(tca, led->num, blink_source[i]);
	वापस 0;
पूर्ण

अटल पूर्णांक led_assign(काष्ठा tca6507_led *led)
अणु
	काष्ठा tca6507_chip *tca = led->chip;
	पूर्णांक err;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&tca->lock, flags);
	led_release(led);
	err = led_prepare(led);
	अगर (err) अणु
		/*
		 * Can only fail on समयr setup.  In that हाल we need
		 * to re-establish as steady level.
		 */
		led->onसमय = 0;
		led->offसमय = 0;
		led_prepare(led);
	पूर्ण
	spin_unlock_irqrestore(&tca->lock, flags);

	अगर (tca->reg_set)
		schedule_work(&tca->work);
	वापस err;
पूर्ण

अटल व्योम tca6507_brightness_set(काष्ठा led_classdev *led_cdev,
				   क्रमागत led_brightness brightness)
अणु
	काष्ठा tca6507_led *led = container_of(led_cdev, काष्ठा tca6507_led,
					       led_cdev);
	led->led_cdev.brightness = brightness;
	led->onसमय = 0;
	led->offसमय = 0;
	led_assign(led);
पूर्ण

अटल पूर्णांक tca6507_blink_set(काष्ठा led_classdev *led_cdev,
			     अचिन्हित दीर्घ *delay_on,
			     अचिन्हित दीर्घ *delay_off)
अणु
	काष्ठा tca6507_led *led = container_of(led_cdev, काष्ठा tca6507_led,
					       led_cdev);

	अगर (*delay_on == 0)
		led->on_dflt = 1;
	अन्यथा अगर (delay_on != &led_cdev->blink_delay_on)
		led->on_dflt = 0;
	led->onसमय = *delay_on;

	अगर (*delay_off == 0)
		led->off_dflt = 1;
	अन्यथा अगर (delay_off != &led_cdev->blink_delay_off)
		led->off_dflt = 0;
	led->offसमय = *delay_off;

	अगर (led->onसमय == 0)
		led->onसमय = 512;
	अगर (led->offसमय == 0)
		led->offसमय = 512;

	अगर (led->led_cdev.brightness == LED_OFF)
		led->led_cdev.brightness = LED_FULL;
	अगर (led_assign(led) < 0) अणु
		led->onसमय = 0;
		led->offसमय = 0;
		led->led_cdev.brightness = LED_OFF;
		वापस -EINVAL;
	पूर्ण
	*delay_on = led->onसमय;
	*delay_off = led->offसमय;
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_GPIOLIB
अटल व्योम tca6507_gpio_set_value(काष्ठा gpio_chip *gc,
				   अचिन्हित offset, पूर्णांक val)
अणु
	काष्ठा tca6507_chip *tca = gpiochip_get_data(gc);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&tca->lock, flags);
	/*
	 * 'OFF' is floating high, and 'ON' is pulled करोwn, so it has
	 * the inverse sense of 'val'.
	 */
	set_select(tca, tca->gpio_map[offset],
		   val ? TCA6507_LS_LED_OFF : TCA6507_LS_LED_ON);
	spin_unlock_irqrestore(&tca->lock, flags);
	अगर (tca->reg_set)
		schedule_work(&tca->work);
पूर्ण

अटल पूर्णांक tca6507_gpio_direction_output(काष्ठा gpio_chip *gc,
					  अचिन्हित offset, पूर्णांक val)
अणु
	tca6507_gpio_set_value(gc, offset, val);
	वापस 0;
पूर्ण

अटल पूर्णांक tca6507_probe_gpios(काष्ठा device *dev,
			       काष्ठा tca6507_chip *tca,
			       काष्ठा tca6507_platक्रमm_data *pdata)
अणु
	पूर्णांक err;
	पूर्णांक i = 0;
	पूर्णांक gpios = 0;

	क्रम (i = 0; i < NUM_LEDS; i++)
		अगर (pdata->leds.leds[i].name && pdata->leds.leds[i].flags) अणु
			/* Configure as a gpio */
			tca->gpio_map[gpios] = i;
			gpios++;
		पूर्ण

	अगर (!gpios)
		वापस 0;

	tca->gpio.label = "gpio-tca6507";
	tca->gpio.ngpio = gpios;
	tca->gpio.base = pdata->gpio_base;
	tca->gpio.owner = THIS_MODULE;
	tca->gpio.direction_output = tca6507_gpio_direction_output;
	tca->gpio.set = tca6507_gpio_set_value;
	tca->gpio.parent = dev;
#अगर_घोषित CONFIG_OF_GPIO
	tca->gpio.of_node = of_node_get(dev_of_node(dev));
#पूर्ण_अगर
	err = gpiochip_add_data(&tca->gpio, tca);
	अगर (err) अणु
		tca->gpio.ngpio = 0;
		वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम tca6507_हटाओ_gpio(काष्ठा tca6507_chip *tca)
अणु
	अगर (tca->gpio.ngpio)
		gpiochip_हटाओ(&tca->gpio);
पूर्ण
#अन्यथा /* CONFIG_GPIOLIB */
अटल पूर्णांक tca6507_probe_gpios(काष्ठा device *dev,
			       काष्ठा tca6507_chip *tca,
			       काष्ठा tca6507_platक्रमm_data *pdata)
अणु
	वापस 0;
पूर्ण
अटल व्योम tca6507_हटाओ_gpio(काष्ठा tca6507_chip *tca)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_GPIOLIB */

अटल काष्ठा tca6507_platक्रमm_data *
tca6507_led_dt_init(काष्ठा device *dev)
अणु
	काष्ठा tca6507_platक्रमm_data *pdata;
	काष्ठा fwnode_handle *child;
	काष्ठा led_info *tca_leds;
	पूर्णांक count;

	count = device_get_child_node_count(dev);
	अगर (!count || count > NUM_LEDS)
		वापस ERR_PTR(-ENODEV);

	tca_leds = devm_kसुस्मृति(dev, NUM_LEDS, माप(काष्ठा led_info),
				GFP_KERNEL);
	अगर (!tca_leds)
		वापस ERR_PTR(-ENOMEM);

	device_क्रम_each_child_node(dev, child) अणु
		काष्ठा led_info led;
		u32 reg;
		पूर्णांक ret;

		अगर (fwnode_property_पढ़ो_string(child, "label", &led.name))
			led.name = fwnode_get_name(child);

		fwnode_property_पढ़ो_string(child, "linux,default-trigger",
					    &led.शेष_trigger);

		led.flags = 0;
		अगर (fwnode_property_match_string(child, "compatible",
						 "gpio") >= 0)
			led.flags |= TCA6507_MAKE_GPIO;

		ret = fwnode_property_पढ़ो_u32(child, "reg", &reg);
		अगर (ret || reg >= NUM_LEDS) अणु
			fwnode_handle_put(child);
			वापस ERR_PTR(ret ? : -EINVAL);
		पूर्ण

		tca_leds[reg] = led;
	पूर्ण

	pdata = devm_kzalloc(dev, माप(काष्ठा tca6507_platक्रमm_data),
			     GFP_KERNEL);
	अगर (!pdata)
		वापस ERR_PTR(-ENOMEM);

	pdata->leds.leds = tca_leds;
	pdata->leds.num_leds = NUM_LEDS;
#अगर_घोषित CONFIG_GPIOLIB
	pdata->gpio_base = -1;
#पूर्ण_अगर

	वापस pdata;
पूर्ण

अटल स्थिर काष्ठा of_device_id __maybe_unused of_tca6507_leds_match[] = अणु
	अणु .compatible = "ti,tca6507", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, of_tca6507_leds_match);

अटल पूर्णांक tca6507_probe(काष्ठा i2c_client *client,
		स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा i2c_adapter *adapter;
	काष्ठा tca6507_chip *tca;
	काष्ठा tca6507_platक्रमm_data *pdata;
	पूर्णांक err;
	पूर्णांक i = 0;

	adapter = client->adapter;

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_I2C))
		वापस -EIO;

	pdata = tca6507_led_dt_init(dev);
	अगर (IS_ERR(pdata)) अणु
		dev_err(dev, "Need %d entries in platform-data list\n", NUM_LEDS);
		वापस PTR_ERR(pdata);
	पूर्ण
	tca = devm_kzalloc(dev, माप(*tca), GFP_KERNEL);
	अगर (!tca)
		वापस -ENOMEM;

	tca->client = client;
	INIT_WORK(&tca->work, tca6507_work);
	spin_lock_init(&tca->lock);
	i2c_set_clientdata(client, tca);

	क्रम (i = 0; i < NUM_LEDS; i++) अणु
		काष्ठा tca6507_led *l = tca->leds + i;

		l->chip = tca;
		l->num = i;
		अगर (pdata->leds.leds[i].name && !pdata->leds.leds[i].flags) अणु
			l->led_cdev.name = pdata->leds.leds[i].name;
			l->led_cdev.शेष_trigger
				= pdata->leds.leds[i].शेष_trigger;
			l->led_cdev.brightness_set = tca6507_brightness_set;
			l->led_cdev.blink_set = tca6507_blink_set;
			l->bank = -1;
			err = led_classdev_रेजिस्टर(dev, &l->led_cdev);
			अगर (err < 0)
				जाओ निकास;
		पूर्ण
	पूर्ण
	err = tca6507_probe_gpios(dev, tca, pdata);
	अगर (err)
		जाओ निकास;
	/* set all रेजिस्टरs to known state - zero */
	tca->reg_set = 0x7f;
	schedule_work(&tca->work);

	वापस 0;
निकास:
	जबतक (i--) अणु
		अगर (tca->leds[i].led_cdev.name)
			led_classdev_unरेजिस्टर(&tca->leds[i].led_cdev);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक tca6507_हटाओ(काष्ठा i2c_client *client)
अणु
	पूर्णांक i;
	काष्ठा tca6507_chip *tca = i2c_get_clientdata(client);
	काष्ठा tca6507_led *tca_leds = tca->leds;

	क्रम (i = 0; i < NUM_LEDS; i++) अणु
		अगर (tca_leds[i].led_cdev.name)
			led_classdev_unरेजिस्टर(&tca_leds[i].led_cdev);
	पूर्ण
	tca6507_हटाओ_gpio(tca);
	cancel_work_sync(&tca->work);

	वापस 0;
पूर्ण

अटल काष्ठा i2c_driver tca6507_driver = अणु
	.driver   = अणु
		.name    = "leds-tca6507",
		.of_match_table = of_match_ptr(of_tca6507_leds_match),
	पूर्ण,
	.probe    = tca6507_probe,
	.हटाओ   = tca6507_हटाओ,
	.id_table = tca6507_id,
पूर्ण;

module_i2c_driver(tca6507_driver);

MODULE_AUTHOR("NeilBrown <neilb@suse.de>");
MODULE_DESCRIPTION("TCA6507 LED/GPO driver");
MODULE_LICENSE("GPL v2");
