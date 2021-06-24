<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * V4L2 flash LED sub-device registration helpers.
 *
 *	Copyright (C) 2015 Samsung Electronics Co., Ltd
 *	Author: Jacek Anaszewski <j.anaszewski@samsung.com>
 */

#अगर_अघोषित _V4L2_FLASH_H
#घोषणा _V4L2_FLASH_H

#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-subdev.h>

काष्ठा led_classdev_flash;
काष्ठा led_classdev;
काष्ठा v4l2_flash;
क्रमागत led_brightness;

/**
 * काष्ठा v4l2_flash_ctrl_data - flash control initialization data, filled
 *				basing on the features declared by the LED flash
 *				class driver in the v4l2_flash_config
 * @config:	initialization data क्रम a control
 * @cid:	contains v4l2 flash control id अगर the config
 *		field was initialized, 0 otherwise
 */
काष्ठा v4l2_flash_ctrl_data अणु
	काष्ठा v4l2_ctrl_config config;
	u32 cid;
पूर्ण;

/**
 * काष्ठा v4l2_flash_ops - V4L2 flash operations
 *
 * @बाह्यal_strobe_set: Setup strobing the flash by hardware pin state
 *	निश्चितion.
 * @पूर्णांकensity_to_led_brightness: Convert पूर्णांकensity to brightness in a device
 *	specअगरic manner
 * @led_brightness_to_पूर्णांकensity: convert brightness to पूर्णांकensity in a device
 *	specअगरic manner.
 */
काष्ठा v4l2_flash_ops अणु
	पूर्णांक (*बाह्यal_strobe_set)(काष्ठा v4l2_flash *v4l2_flash,
					bool enable);
	क्रमागत led_brightness (*पूर्णांकensity_to_led_brightness)
		(काष्ठा v4l2_flash *v4l2_flash, s32 पूर्णांकensity);
	s32 (*led_brightness_to_पूर्णांकensity)
		(काष्ठा v4l2_flash *v4l2_flash, क्रमागत led_brightness);
पूर्ण;

/**
 * काष्ठा v4l2_flash_config - V4L2 Flash sub-device initialization data
 * @dev_name:			the name of the media entity,
 *				unique in the प्रणाली
 * @पूर्णांकensity:			non-flash strobe स्थिरraपूर्णांकs क्रम the LED
 * @flash_faults:		biपंचांगask of flash faults that the LED flash class
 *				device can report; corresponding LED_FAULT* bit
 *				definitions are available in the header file
 *				<linux/led-class-flash.h>
 * @has_बाह्यal_strobe:	बाह्यal strobe capability
 */
काष्ठा v4l2_flash_config अणु
	अक्षर dev_name[32];
	काष्ठा led_flash_setting पूर्णांकensity;
	u32 flash_faults;
	अचिन्हित पूर्णांक has_बाह्यal_strobe:1;
पूर्ण;

/**
 * काष्ठा v4l2_flash - Flash sub-device context
 * @fled_cdev:		LED flash class device controlled by this sub-device
 * @iled_cdev:		LED class device representing indicator LED associated
 *			with the LED flash class device
 * @ops:		V4L2 specअगरic flash ops
 * @sd:			V4L2 sub-device
 * @hdl:		flash controls handler
 * @ctrls:		array of poपूर्णांकers to controls, whose values define
 *			the sub-device state
 */
काष्ठा v4l2_flash अणु
	काष्ठा led_classdev_flash *fled_cdev;
	काष्ठा led_classdev *iled_cdev;
	स्थिर काष्ठा v4l2_flash_ops *ops;

	काष्ठा v4l2_subdev sd;
	काष्ठा v4l2_ctrl_handler hdl;
	काष्ठा v4l2_ctrl **ctrls;
पूर्ण;

/**
 * v4l2_subdev_to_v4l2_flash - Returns a &काष्ठा v4l2_flash from the
 * &काष्ठा v4l2_subdev embedded on it.
 *
 * @sd: poपूर्णांकer to &काष्ठा v4l2_subdev
 */
अटल अंतरभूत काष्ठा v4l2_flash *v4l2_subdev_to_v4l2_flash(
							काष्ठा v4l2_subdev *sd)
अणु
	वापस container_of(sd, काष्ठा v4l2_flash, sd);
पूर्ण

/**
 * v4l2_ctrl_to_v4l2_flash - Returns a &काष्ठा v4l2_flash from the
 * &काष्ठा v4l2_ctrl embedded on it.
 *
 * @c: poपूर्णांकer to &काष्ठा v4l2_ctrl
 */
अटल अंतरभूत काष्ठा v4l2_flash *v4l2_ctrl_to_v4l2_flash(काष्ठा v4l2_ctrl *c)
अणु
	वापस container_of(c->handler, काष्ठा v4l2_flash, hdl);
पूर्ण

#अगर IS_ENABLED(CONFIG_V4L2_FLASH_LED_CLASS)
/**
 * v4l2_flash_init - initialize V4L2 flash led sub-device
 * @dev:	flash device, e.g. an I2C device
 * @fwn:	fwnode_handle of the LED, may be शून्य अगर the same as device's
 * @fled_cdev:	LED flash class device to wrap
 * @ops:	V4L2 Flash device ops
 * @config:	initialization data क्रम V4L2 Flash sub-device
 *
 * Create V4L2 Flash sub-device wrapping given LED subप्रणाली device.
 * The ops poपूर्णांकer is stored by the V4L2 flash framework. No
 * references are held to config nor its contents once this function
 * has वापसed.
 *
 * Returns: A valid poपूर्णांकer, or, when an error occurs, the वापस
 * value is encoded using ERR_PTR(). Use IS_ERR() to check and
 * PTR_ERR() to obtain the numeric वापस value.
 */
काष्ठा v4l2_flash *v4l2_flash_init(
	काष्ठा device *dev, काष्ठा fwnode_handle *fwn,
	काष्ठा led_classdev_flash *fled_cdev,
	स्थिर काष्ठा v4l2_flash_ops *ops, काष्ठा v4l2_flash_config *config);

/**
 * v4l2_flash_indicator_init - initialize V4L2 indicator sub-device
 * @dev:	flash device, e.g. an I2C device
 * @fwn:	fwnode_handle of the LED, may be शून्य अगर the same as device's
 * @iled_cdev:	LED flash class device representing the indicator LED
 * @config:	initialization data क्रम V4L2 Flash sub-device
 *
 * Create V4L2 Flash sub-device wrapping given LED subप्रणाली device.
 * The ops poपूर्णांकer is stored by the V4L2 flash framework. No
 * references are held to config nor its contents once this function
 * has वापसed.
 *
 * Returns: A valid poपूर्णांकer, or, when an error occurs, the वापस
 * value is encoded using ERR_PTR(). Use IS_ERR() to check and
 * PTR_ERR() to obtain the numeric वापस value.
 */
काष्ठा v4l2_flash *v4l2_flash_indicator_init(
	काष्ठा device *dev, काष्ठा fwnode_handle *fwn,
	काष्ठा led_classdev *iled_cdev, काष्ठा v4l2_flash_config *config);

/**
 * v4l2_flash_release - release V4L2 Flash sub-device
 * @v4l2_flash: the V4L2 Flash sub-device to release
 *
 * Release V4L2 Flash sub-device.
 */
व्योम v4l2_flash_release(काष्ठा v4l2_flash *v4l2_flash);

#अन्यथा
अटल अंतरभूत काष्ठा v4l2_flash *v4l2_flash_init(
	काष्ठा device *dev, काष्ठा fwnode_handle *fwn,
	काष्ठा led_classdev_flash *fled_cdev,
	स्थिर काष्ठा v4l2_flash_ops *ops, काष्ठा v4l2_flash_config *config)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा v4l2_flash *v4l2_flash_indicator_init(
	काष्ठा device *dev, काष्ठा fwnode_handle *fwn,
	काष्ठा led_classdev *iled_cdev, काष्ठा v4l2_flash_config *config)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम v4l2_flash_release(काष्ठा v4l2_flash *v4l2_flash)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_V4L2_FLASH_LED_CLASS */

#पूर्ण_अगर /* _V4L2_FLASH_H */
