<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * LED Flash class पूर्णांकerface
 *
 * Copyright (C) 2015 Samsung Electronics Co., Ltd.
 * Author: Jacek Anaszewski <j.anaszewski@samsung.com>
 */
#अगर_अघोषित __LINUX_FLASH_LEDS_H_INCLUDED
#घोषणा __LINUX_FLASH_LEDS_H_INCLUDED

#समावेश <linux/leds.h>

काष्ठा device_node;
काष्ठा led_classdev_flash;

/*
 * Supported led fault bits - must be kept in synch
 * with V4L2_FLASH_FAULT bits.
 */
#घोषणा LED_FAULT_OVER_VOLTAGE		(1 << 0)
#घोषणा LED_FAULT_TIMEOUT		(1 << 1)
#घोषणा LED_FAULT_OVER_TEMPERATURE	(1 << 2)
#घोषणा LED_FAULT_SHORT_CIRCUIT		(1 << 3)
#घोषणा LED_FAULT_OVER_CURRENT		(1 << 4)
#घोषणा LED_FAULT_INDICATOR		(1 << 5)
#घोषणा LED_FAULT_UNDER_VOLTAGE		(1 << 6)
#घोषणा LED_FAULT_INPUT_VOLTAGE		(1 << 7)
#घोषणा LED_FAULT_LED_OVER_TEMPERATURE	(1 << 8)
#घोषणा LED_NUM_FLASH_FAULTS		9

#घोषणा LED_FLASH_SYSFS_GROUPS_SIZE	5

काष्ठा led_flash_ops अणु
	/* set flash brightness */
	पूर्णांक (*flash_brightness_set)(काष्ठा led_classdev_flash *fled_cdev,
					u32 brightness);
	/* get flash brightness */
	पूर्णांक (*flash_brightness_get)(काष्ठा led_classdev_flash *fled_cdev,
					u32 *brightness);
	/* set flash strobe state */
	पूर्णांक (*strobe_set)(काष्ठा led_classdev_flash *fled_cdev, bool state);
	/* get flash strobe state */
	पूर्णांक (*strobe_get)(काष्ठा led_classdev_flash *fled_cdev, bool *state);
	/* set flash समयout */
	पूर्णांक (*समयout_set)(काष्ठा led_classdev_flash *fled_cdev, u32 समयout);
	/* get the flash LED fault */
	पूर्णांक (*fault_get)(काष्ठा led_classdev_flash *fled_cdev, u32 *fault);
पूर्ण;

/*
 * Current value of a flash setting aदीर्घ
 * with its स्थिरraपूर्णांकs.
 */
काष्ठा led_flash_setting अणु
	/* maximum allowed value */
	u32 min;
	/* maximum allowed value */
	u32 max;
	/* step value */
	u32 step;
	/* current value */
	u32 val;
पूर्ण;

काष्ठा led_classdev_flash अणु
	/* led class device */
	काष्ठा led_classdev led_cdev;

	/* flash led specअगरic ops */
	स्थिर काष्ठा led_flash_ops *ops;

	/* flash brightness value in microamperes aदीर्घ with its स्थिरraपूर्णांकs */
	काष्ठा led_flash_setting brightness;

	/* flash समयout value in microseconds aदीर्घ with its स्थिरraपूर्णांकs */
	काष्ठा led_flash_setting समयout;

	/* LED Flash class sysfs groups */
	स्थिर काष्ठा attribute_group *sysfs_groups[LED_FLASH_SYSFS_GROUPS_SIZE];
पूर्ण;

अटल अंतरभूत काष्ठा led_classdev_flash *lcdev_to_flcdev(
						काष्ठा led_classdev *lcdev)
अणु
	वापस container_of(lcdev, काष्ठा led_classdev_flash, led_cdev);
पूर्ण

#अगर IS_ENABLED(CONFIG_LEDS_CLASS_FLASH)
/**
 * led_classdev_flash_रेजिस्टर_ext - रेजिस्टर a new object of LED class with
 *				     init data and with support क्रम flash LEDs
 * @parent: LED flash controller device this flash LED is driven by
 * @fled_cdev: the led_classdev_flash काष्ठाure क्रम this device
 * @init_data: the LED class flash device initialization data
 *
 * Returns: 0 on success or negative error value on failure
 */
पूर्णांक led_classdev_flash_रेजिस्टर_ext(काष्ठा device *parent,
				    काष्ठा led_classdev_flash *fled_cdev,
				    काष्ठा led_init_data *init_data);

/**
 * led_classdev_flash_unरेजिस्टर - unरेजिस्टरs an object of led_classdev class
 *				   with support क्रम flash LEDs
 * @fled_cdev: the flash LED to unरेजिस्टर
 *
 * Unरेजिस्टर a previously रेजिस्टरed via led_classdev_flash_रेजिस्टर object
 */
व्योम led_classdev_flash_unरेजिस्टर(काष्ठा led_classdev_flash *fled_cdev);

पूर्णांक devm_led_classdev_flash_रेजिस्टर_ext(काष्ठा device *parent,
				     काष्ठा led_classdev_flash *fled_cdev,
				     काष्ठा led_init_data *init_data);


व्योम devm_led_classdev_flash_unरेजिस्टर(काष्ठा device *parent,
					काष्ठा led_classdev_flash *fled_cdev);

#अन्यथा

अटल अंतरभूत पूर्णांक led_classdev_flash_रेजिस्टर_ext(काष्ठा device *parent,
				    काष्ठा led_classdev_flash *fled_cdev,
				    काष्ठा led_init_data *init_data)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम led_classdev_flash_unरेजिस्टर(काष्ठा led_classdev_flash *fled_cdev) अणुपूर्ण;
अटल अंतरभूत पूर्णांक devm_led_classdev_flash_रेजिस्टर_ext(काष्ठा device *parent,
				     काष्ठा led_classdev_flash *fled_cdev,
				     काष्ठा led_init_data *init_data)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम devm_led_classdev_flash_unरेजिस्टर(काष्ठा device *parent,
					काष्ठा led_classdev_flash *fled_cdev)
अणुपूर्ण;

#पूर्ण_अगर  /* IS_ENABLED(CONFIG_LEDS_CLASS_FLASH) */

अटल अंतरभूत पूर्णांक led_classdev_flash_रेजिस्टर(काष्ठा device *parent,
					   काष्ठा led_classdev_flash *fled_cdev)
अणु
	वापस led_classdev_flash_रेजिस्टर_ext(parent, fled_cdev, शून्य);
पूर्ण

अटल अंतरभूत पूर्णांक devm_led_classdev_flash_रेजिस्टर(काष्ठा device *parent,
				     काष्ठा led_classdev_flash *fled_cdev)
अणु
	वापस devm_led_classdev_flash_रेजिस्टर_ext(parent, fled_cdev, शून्य);
पूर्ण

/**
 * led_set_flash_strobe - setup flash strobe
 * @fled_cdev: the flash LED to set strobe on
 * @state: 1 - strobe flash, 0 - stop flash strobe
 *
 * Strobe the flash LED.
 *
 * Returns: 0 on success or negative error value on failure
 */
अटल अंतरभूत पूर्णांक led_set_flash_strobe(काष्ठा led_classdev_flash *fled_cdev,
					bool state)
अणु
	अगर (!fled_cdev)
		वापस -EINVAL;
	वापस fled_cdev->ops->strobe_set(fled_cdev, state);
पूर्ण

/**
 * led_get_flash_strobe - get flash strobe status
 * @fled_cdev: the flash LED to query
 * @state: 1 - flash is strobing, 0 - flash is off
 *
 * Check whether the flash is strobing at the moment.
 *
 * Returns: 0 on success or negative error value on failure
 */
अटल अंतरभूत पूर्णांक led_get_flash_strobe(काष्ठा led_classdev_flash *fled_cdev,
					bool *state)
अणु
	अगर (!fled_cdev)
		वापस -EINVAL;
	अगर (fled_cdev->ops->strobe_get)
		वापस fled_cdev->ops->strobe_get(fled_cdev, state);

	वापस -EINVAL;
पूर्ण

/**
 * led_set_flash_brightness - set flash LED brightness
 * @fled_cdev: the flash LED to set
 * @brightness: the brightness to set it to
 *
 * Set a flash LED's brightness.
 *
 * Returns: 0 on success or negative error value on failure
 */
पूर्णांक led_set_flash_brightness(काष्ठा led_classdev_flash *fled_cdev,
			     u32 brightness);

/**
 * led_update_flash_brightness - update flash LED brightness
 * @fled_cdev: the flash LED to query
 *
 * Get a flash LED's current brightness and update led_flash->brightness
 * member with the obtained value.
 *
 * Returns: 0 on success or negative error value on failure
 */
पूर्णांक led_update_flash_brightness(काष्ठा led_classdev_flash *fled_cdev);

/**
 * led_set_flash_समयout - set flash LED समयout
 * @fled_cdev: the flash LED to set
 * @समयout: the flash समयout to set it to
 *
 * Set the flash strobe duration.
 *
 * Returns: 0 on success or negative error value on failure
 */
पूर्णांक led_set_flash_समयout(काष्ठा led_classdev_flash *fled_cdev, u32 समयout);

/**
 * led_get_flash_fault - get the flash LED fault
 * @fled_cdev: the flash LED to query
 * @fault: biपंचांगask containing flash faults
 *
 * Get the flash LED fault.
 *
 * Returns: 0 on success or negative error value on failure
 */
पूर्णांक led_get_flash_fault(काष्ठा led_classdev_flash *fled_cdev, u32 *fault);

#पूर्ण_अगर	/* __LINUX_FLASH_LEDS_H_INCLUDED */
