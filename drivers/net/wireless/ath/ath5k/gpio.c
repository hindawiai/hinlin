<शैली गुरु>
/*
 * Copyright (c) 2004-2008 Reyk Floeter <reyk@खोलोbsd.org>
 * Copyright (c) 2006-2008 Nick Kossअगरidis <mickflemm@gmail.com>
 *
 * Permission to use, copy, modअगरy, and distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 */

/****************\
  GPIO Functions
\****************/

#समावेश "ath5k.h"
#समावेश "reg.h"
#समावेश "debug.h"


/**
 * DOC: GPIO/LED functions
 *
 * Here we control the 6 bidirectional GPIO pins provided by the hw.
 * We can set a GPIO pin to be an input or an output pin on GPIO control
 * रेजिस्टर and then पढ़ो or set its status from GPIO data input/output
 * रेजिस्टरs.
 *
 * We also control the two LED pins provided by the hw, LED_0 is our
 * "power" LED and LED_1 is our "network activity" LED but many scenarios
 * are available from hw. Venकरोrs might also provide LEDs connected to the
 * GPIO pins, we handle them through the LED subप्रणाली on led.c
 */


/**
 * ath5k_hw_set_ledstate() - Set led state
 * @ah: The &काष्ठा ath5k_hw
 * @state: One of AR5K_LED_*
 *
 * Used to set the LED blinking state. This only
 * works क्रम the LED connected to the LED_0, LED_1 pins,
 * not the GPIO based.
 */
व्योम
ath5k_hw_set_ledstate(काष्ठा ath5k_hw *ah, अचिन्हित पूर्णांक state)
अणु
	u32 led;
	/*5210 has dअगरferent led mode handling*/
	u32 led_5210;

	/*Reset led status*/
	अगर (ah->ah_version != AR5K_AR5210)
		AR5K_REG_DISABLE_BITS(ah, AR5K_PCICFG,
			AR5K_PCICFG_LEDMODE |  AR5K_PCICFG_LED);
	अन्यथा
		AR5K_REG_DISABLE_BITS(ah, AR5K_PCICFG, AR5K_PCICFG_LED);

	/*
	 * Some blinking values, define at your wish
	 */
	चयन (state) अणु
	हाल AR5K_LED_SCAN:
	हाल AR5K_LED_AUTH:
		led = AR5K_PCICFG_LEDMODE_PROP | AR5K_PCICFG_LED_PEND;
		led_5210 = AR5K_PCICFG_LED_PEND | AR5K_PCICFG_LED_BCTL;
		अवरोध;

	हाल AR5K_LED_INIT:
		led = AR5K_PCICFG_LEDMODE_PROP | AR5K_PCICFG_LED_NONE;
		led_5210 = AR5K_PCICFG_LED_PEND;
		अवरोध;

	हाल AR5K_LED_ASSOC:
	हाल AR5K_LED_RUN:
		led = AR5K_PCICFG_LEDMODE_PROP | AR5K_PCICFG_LED_ASSOC;
		led_5210 = AR5K_PCICFG_LED_ASSOC;
		अवरोध;

	शेष:
		led = AR5K_PCICFG_LEDMODE_PROM | AR5K_PCICFG_LED_NONE;
		led_5210 = AR5K_PCICFG_LED_PEND;
		अवरोध;
	पूर्ण

	/*Write new status to the रेजिस्टर*/
	अगर (ah->ah_version != AR5K_AR5210)
		AR5K_REG_ENABLE_BITS(ah, AR5K_PCICFG, led);
	अन्यथा
		AR5K_REG_ENABLE_BITS(ah, AR5K_PCICFG, led_5210);
पूर्ण

/**
 * ath5k_hw_set_gpio_input() - Set GPIO inमाला_दो
 * @ah: The &काष्ठा ath5k_hw
 * @gpio: GPIO pin to set as input
 */
पूर्णांक
ath5k_hw_set_gpio_input(काष्ठा ath5k_hw *ah, u32 gpio)
अणु
	अगर (gpio >= AR5K_NUM_GPIO)
		वापस -EINVAL;

	ath5k_hw_reg_ग_लिखो(ah,
		(ath5k_hw_reg_पढ़ो(ah, AR5K_GPIOCR) & ~AR5K_GPIOCR_OUT(gpio))
		| AR5K_GPIOCR_IN(gpio), AR5K_GPIOCR);

	वापस 0;
पूर्ण

/**
 * ath5k_hw_set_gpio_output() - Set GPIO outमाला_दो
 * @ah: The &काष्ठा ath5k_hw
 * @gpio: The GPIO pin to set as output
 */
पूर्णांक
ath5k_hw_set_gpio_output(काष्ठा ath5k_hw *ah, u32 gpio)
अणु
	अगर (gpio >= AR5K_NUM_GPIO)
		वापस -EINVAL;

	ath5k_hw_reg_ग_लिखो(ah,
		(ath5k_hw_reg_पढ़ो(ah, AR5K_GPIOCR) & ~AR5K_GPIOCR_OUT(gpio))
		| AR5K_GPIOCR_OUT(gpio), AR5K_GPIOCR);

	वापस 0;
पूर्ण

/**
 * ath5k_hw_get_gpio() - Get GPIO state
 * @ah: The &काष्ठा ath5k_hw
 * @gpio: The GPIO pin to पढ़ो
 */
u32
ath5k_hw_get_gpio(काष्ठा ath5k_hw *ah, u32 gpio)
अणु
	अगर (gpio >= AR5K_NUM_GPIO)
		वापस 0xffffffff;

	/* GPIO input magic */
	वापस ((ath5k_hw_reg_पढ़ो(ah, AR5K_GPIODI) & AR5K_GPIODI_M) >> gpio) &
		0x1;
पूर्ण

/**
 * ath5k_hw_set_gpio() - Set GPIO state
 * @ah: The &काष्ठा ath5k_hw
 * @gpio: The GPIO pin to set
 * @val: Value to set (boolean)
 */
पूर्णांक
ath5k_hw_set_gpio(काष्ठा ath5k_hw *ah, u32 gpio, u32 val)
अणु
	u32 data;

	अगर (gpio >= AR5K_NUM_GPIO)
		वापस -EINVAL;

	/* GPIO output magic */
	data = ath5k_hw_reg_पढ़ो(ah, AR5K_GPIODO);

	data &= ~(1 << gpio);
	data |= (val & 1) << gpio;

	ath5k_hw_reg_ग_लिखो(ah, data, AR5K_GPIODO);

	वापस 0;
पूर्ण

/**
 * ath5k_hw_set_gpio_पूर्णांकr() - Initialize the GPIO पूर्णांकerrupt (RFKill चयन)
 * @ah: The &काष्ठा ath5k_hw
 * @gpio: The GPIO pin to use
 * @पूर्णांकerrupt_level: True to generate पूर्णांकerrupt on active pin (high)
 *
 * This function is used to set up the GPIO पूर्णांकerrupt क्रम the hw RFKill चयन.
 * That चयन is connected to a GPIO pin and it's number is stored on EEPROM.
 * It can either खोलो or बंद the circuit to indicate that we should disable
 * RF/Wireless to save घातer (we also get that from EEPROM).
 */
व्योम
ath5k_hw_set_gpio_पूर्णांकr(काष्ठा ath5k_hw *ah, अचिन्हित पूर्णांक gpio,
		u32 पूर्णांकerrupt_level)
अणु
	u32 data;

	अगर (gpio >= AR5K_NUM_GPIO)
		वापस;

	/*
	 * Set the GPIO पूर्णांकerrupt
	 */
	data = (ath5k_hw_reg_पढ़ो(ah, AR5K_GPIOCR) &
		~(AR5K_GPIOCR_INT_SEL(gpio) | AR5K_GPIOCR_INT_SELH |
		AR5K_GPIOCR_INT_ENA | AR5K_GPIOCR_OUT(gpio))) |
		(AR5K_GPIOCR_INT_SEL(gpio) | AR5K_GPIOCR_INT_ENA);

	ath5k_hw_reg_ग_लिखो(ah, पूर्णांकerrupt_level ? data :
		(data | AR5K_GPIOCR_INT_SELH), AR5K_GPIOCR);

	ah->ah_imr |= AR5K_IMR_GPIO;

	/* Enable GPIO पूर्णांकerrupts */
	AR5K_REG_ENABLE_BITS(ah, AR5K_PIMR, AR5K_IMR_GPIO);
पूर्ण

