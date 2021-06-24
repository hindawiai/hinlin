<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * LP55XX Common Driver Header
 *
 * Copyright (C) 2012 Texas Instruments
 *
 * Author: Milo(Woogyom) Kim <milo.kim@ti.com>
 *
 * Derived from leds-lp5521.c, leds-lp5523.c
 */

#अगर_अघोषित _LEDS_LP55XX_COMMON_H
#घोषणा _LEDS_LP55XX_COMMON_H

#समावेश <linux/led-class-multicolor.h>

क्रमागत lp55xx_engine_index अणु
	LP55XX_ENGINE_INVALID,
	LP55XX_ENGINE_1,
	LP55XX_ENGINE_2,
	LP55XX_ENGINE_3,
	LP55XX_ENGINE_MAX = LP55XX_ENGINE_3,
पूर्ण;

क्रमागत lp55xx_engine_mode अणु
	LP55XX_ENGINE_DISABLED,
	LP55XX_ENGINE_LOAD,
	LP55XX_ENGINE_RUN,
पूर्ण;

#घोषणा LP55XX_DEV_ATTR_RW(name, show, store)	\
	DEVICE_ATTR(name, S_IRUGO | S_IWUSR, show, store)
#घोषणा LP55XX_DEV_ATTR_RO(name, show)		\
	DEVICE_ATTR(name, S_IRUGO, show, शून्य)
#घोषणा LP55XX_DEV_ATTR_WO(name, store)		\
	DEVICE_ATTR(name, S_IWUSR, शून्य, store)

#घोषणा show_mode(nr)							\
अटल sमाप_प्रकार show_engine##nr##_mode(काष्ठा device *dev,		\
				    काष्ठा device_attribute *attr,	\
				    अक्षर *buf)				\
अणु									\
	वापस show_engine_mode(dev, attr, buf, nr);			\
पूर्ण

#घोषणा store_mode(nr)							\
अटल sमाप_प्रकार store_engine##nr##_mode(काष्ठा device *dev,		\
				     काष्ठा device_attribute *attr,	\
				     स्थिर अक्षर *buf, माप_प्रकार len)	\
अणु									\
	वापस store_engine_mode(dev, attr, buf, len, nr);		\
पूर्ण

#घोषणा show_leds(nr)							\
अटल sमाप_प्रकार show_engine##nr##_leds(काष्ठा device *dev,		\
			    काष्ठा device_attribute *attr,		\
			    अक्षर *buf)					\
अणु									\
	वापस show_engine_leds(dev, attr, buf, nr);			\
पूर्ण

#घोषणा store_leds(nr)						\
अटल sमाप_प्रकार store_engine##nr##_leds(काष्ठा device *dev,	\
			     काष्ठा device_attribute *attr,	\
			     स्थिर अक्षर *buf, माप_प्रकार len)	\
अणु								\
	वापस store_engine_leds(dev, attr, buf, len, nr);	\
पूर्ण

#घोषणा store_load(nr)							\
अटल sमाप_प्रकार store_engine##nr##_load(काष्ठा device *dev,		\
				     काष्ठा device_attribute *attr,	\
				     स्थिर अक्षर *buf, माप_प्रकार len)	\
अणु									\
	वापस store_engine_load(dev, attr, buf, len, nr);		\
पूर्ण

काष्ठा lp55xx_led;
काष्ठा lp55xx_chip;

/*
 * काष्ठा lp55xx_reg
 * @addr : Register address
 * @val  : Register value
 */
काष्ठा lp55xx_reg अणु
	u8 addr;
	u8 val;
पूर्ण;

/*
 * काष्ठा lp55xx_device_config
 * @reset              : Chip specअगरic reset command
 * @enable             : Chip specअगरic enable command
 * @max_channel        : Maximum number of channels
 * @post_init_device   : Chip specअगरic initialization code
 * @brightness_fn      : Brightness function
 * @multicolor_brightness_fn : Multicolor brightness function
 * @set_led_current    : LED current set function
 * @firmware_cb        : Call function when the firmware is loaded
 * @run_engine         : Run पूर्णांकernal engine क्रम pattern
 * @dev_attr_group     : Device specअगरic attributes
 */
काष्ठा lp55xx_device_config अणु
	स्थिर काष्ठा lp55xx_reg reset;
	स्थिर काष्ठा lp55xx_reg enable;
	स्थिर पूर्णांक max_channel;

	/* define अगर the device has specअगरic initialization process */
	पूर्णांक (*post_init_device) (काष्ठा lp55xx_chip *chip);

	/* set LED brightness */
	पूर्णांक (*brightness_fn)(काष्ठा lp55xx_led *led);

	/* set multicolor LED brightness */
	पूर्णांक (*multicolor_brightness_fn)(काष्ठा lp55xx_led *led);

	/* current setting function */
	व्योम (*set_led_current) (काष्ठा lp55xx_led *led, u8 led_current);

	/* access program memory when the firmware is loaded */
	व्योम (*firmware_cb)(काष्ठा lp55xx_chip *chip);

	/* used क्रम running firmware LED patterns */
	व्योम (*run_engine) (काष्ठा lp55xx_chip *chip, bool start);

	/* additional device specअगरic attributes */
	स्थिर काष्ठा attribute_group *dev_attr_group;
पूर्ण;

/*
 * काष्ठा lp55xx_engine
 * @mode       : Engine mode
 * @led_mux    : Mux bits क्रम LED selection. Only used in LP5523
 */
काष्ठा lp55xx_engine अणु
	क्रमागत lp55xx_engine_mode mode;
	u16 led_mux;
पूर्ण;

/*
 * काष्ठा lp55xx_chip
 * @cl         : I2C communication क्रम access रेजिस्टरs
 * @pdata      : Platक्रमm specअगरic data
 * @lock       : Lock क्रम user-space पूर्णांकerface
 * @num_leds   : Number of रेजिस्टरed LEDs
 * @cfg        : Device specअगरic configuration data
 * @engine_idx : Selected engine number
 * @engines    : Engine काष्ठाure क्रम the device attribute R/W पूर्णांकerface
 * @fw         : Firmware data क्रम running a LED pattern
 */
काष्ठा lp55xx_chip अणु
	काष्ठा i2c_client *cl;
	काष्ठा clk *clk;
	काष्ठा lp55xx_platक्रमm_data *pdata;
	काष्ठा mutex lock;	/* lock क्रम user-space पूर्णांकerface */
	पूर्णांक num_leds;
	काष्ठा lp55xx_device_config *cfg;
	क्रमागत lp55xx_engine_index engine_idx;
	काष्ठा lp55xx_engine engines[LP55XX_ENGINE_MAX];
	स्थिर काष्ठा firmware *fw;
पूर्ण;

/*
 * काष्ठा lp55xx_led
 * @chan_nr         : Channel number
 * @cdev            : LED class device
 * @mc_cdev         : Multi color class device
 * @color_components: Multi color LED map inक्रमmation
 * @led_current     : Current setting at each led channel
 * @max_current     : Maximun current at each led channel
 * @brightness      : Brightness value
 * @chip            : The lp55xx chip data
 */
काष्ठा lp55xx_led अणु
	पूर्णांक chan_nr;
	काष्ठा led_classdev cdev;
	काष्ठा led_classdev_mc mc_cdev;
	u8 led_current;
	u8 max_current;
	u8 brightness;
	काष्ठा lp55xx_chip *chip;
पूर्ण;

/* रेजिस्टर access */
बाह्य पूर्णांक lp55xx_ग_लिखो(काष्ठा lp55xx_chip *chip, u8 reg, u8 val);
बाह्य पूर्णांक lp55xx_पढ़ो(काष्ठा lp55xx_chip *chip, u8 reg, u8 *val);
बाह्य पूर्णांक lp55xx_update_bits(काष्ठा lp55xx_chip *chip, u8 reg,
			u8 mask, u8 val);

/* बाह्यal घड़ी detection */
बाह्य bool lp55xx_is_extclk_used(काष्ठा lp55xx_chip *chip);

/* common device init/deinit functions */
बाह्य पूर्णांक lp55xx_init_device(काष्ठा lp55xx_chip *chip);
बाह्य व्योम lp55xx_deinit_device(काष्ठा lp55xx_chip *chip);

/* common LED class device functions */
बाह्य पूर्णांक lp55xx_रेजिस्टर_leds(काष्ठा lp55xx_led *led,
				काष्ठा lp55xx_chip *chip);

/* common device attributes functions */
बाह्य पूर्णांक lp55xx_रेजिस्टर_sysfs(काष्ठा lp55xx_chip *chip);
बाह्य व्योम lp55xx_unरेजिस्टर_sysfs(काष्ठा lp55xx_chip *chip);

/* common device tree population function */
बाह्य काष्ठा lp55xx_platक्रमm_data
*lp55xx_of_populate_pdata(काष्ठा device *dev, काष्ठा device_node *np,
			  काष्ठा lp55xx_chip *chip);

#पूर्ण_अगर /* _LEDS_LP55XX_COMMON_H */
