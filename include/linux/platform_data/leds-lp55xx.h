<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * LP55XX Platक्रमm Data Header
 *
 * Copyright (C) 2012 Texas Instruments
 *
 * Author: Milo(Woogyom) Kim <milo.kim@ti.com>
 *
 * Derived from leds-lp5521.h, leds-lp5523.h
 */

#अगर_अघोषित _LEDS_LP55XX_H
#घोषणा _LEDS_LP55XX_H

#समावेश <linux/gpio/consumer.h>
#समावेश <linux/led-class-multicolor.h>

/* Clock configuration */
#घोषणा LP55XX_CLOCK_AUTO	0
#घोषणा LP55XX_CLOCK_INT	1
#घोषणा LP55XX_CLOCK_EXT	2

#घोषणा LP55XX_MAX_GROUPED_CHAN	4

काष्ठा lp55xx_led_config अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर *शेष_trigger;
	u8 chan_nr;
	u8 led_current; /* mA x10, 0 अगर led is not connected */
	u8 max_current;
	पूर्णांक num_colors;
	अचिन्हित पूर्णांक max_channel;
	पूर्णांक color_id[LED_COLOR_ID_MAX];
	पूर्णांक output_num[LED_COLOR_ID_MAX];
पूर्ण;

काष्ठा lp55xx_predef_pattern अणु
	स्थिर u8 *r;
	स्थिर u8 *g;
	स्थिर u8 *b;
	u8 size_r;
	u8 size_g;
	u8 size_b;
पूर्ण;

क्रमागत lp8501_pwr_sel अणु
	LP8501_ALL_VDD,		/* D1~9 are connected to VDD */
	LP8501_6VDD_3VOUT,	/* D1~6 with VDD, D7~9 with VOUT */
	LP8501_3VDD_6VOUT,	/* D1~6 with VOUT, D7~9 with VDD */
	LP8501_ALL_VOUT,	/* D1~9 are connected to VOUT */
पूर्ण;

/*
 * काष्ठा lp55xx_platक्रमm_data
 * @led_config        : Configurable led class device
 * @num_channels      : Number of LED channels
 * @label             : Used क्रम naming LEDs
 * @घड़ी_mode        : Input घड़ी mode. LP55XX_CLOCK_AUTO or _INT or _EXT
 * @setup_resources   : Platक्रमm specअगरic function beक्रमe enabling the chip
 * @release_resources : Platक्रमm specअगरic function after  disabling the chip
 * @enable_gpiod      : enable GPIO descriptor
 * @patterns          : Predefined pattern data क्रम RGB channels
 * @num_patterns      : Number of patterns
 * @update_config     : Value of CONFIG रेजिस्टर
 */
काष्ठा lp55xx_platक्रमm_data अणु

	/* LED channel configuration */
	काष्ठा lp55xx_led_config *led_config;
	u8 num_channels;
	स्थिर अक्षर *label;

	/* Clock configuration */
	u8 घड़ी_mode;

	/* optional enable GPIO */
	काष्ठा gpio_desc *enable_gpiod;

	/* Predefined pattern data */
	काष्ठा lp55xx_predef_pattern *patterns;
	अचिन्हित पूर्णांक num_patterns;

	/* LP8501 specअगरic */
	क्रमागत lp8501_pwr_sel pwr_sel;
पूर्ण;

#पूर्ण_अगर /* _LEDS_LP55XX_H */
