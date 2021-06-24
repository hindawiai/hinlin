<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* LED Multicolor class पूर्णांकerface
 * Copyright (C) 2019-20 Texas Instruments Incorporated - http://www.ti.com/
 */

#अगर_अघोषित _LINUX_MULTICOLOR_LEDS_H_INCLUDED
#घोषणा _LINUX_MULTICOLOR_LEDS_H_INCLUDED

#समावेश <linux/leds.h>
#समावेश <dt-bindings/leds/common.h>

काष्ठा mc_subled अणु
	अचिन्हित पूर्णांक color_index;
	अचिन्हित पूर्णांक brightness;
	अचिन्हित पूर्णांक पूर्णांकensity;
	अचिन्हित पूर्णांक channel;
पूर्ण;

काष्ठा led_classdev_mc अणु
	/* led class device */
	काष्ठा led_classdev led_cdev;
	अचिन्हित पूर्णांक num_colors;

	काष्ठा mc_subled *subled_info;
पूर्ण;

अटल अंतरभूत काष्ठा led_classdev_mc *lcdev_to_mccdev(
						काष्ठा led_classdev *led_cdev)
अणु
	वापस container_of(led_cdev, काष्ठा led_classdev_mc, led_cdev);
पूर्ण

#अगर IS_ENABLED(CONFIG_LEDS_CLASS_MULTICOLOR)
/**
 * led_classdev_multicolor_रेजिस्टर_ext - रेजिस्टर a new object of led_classdev
 *				      class with support क्रम multicolor LEDs
 * @parent: the multicolor LED to रेजिस्टर
 * @mcled_cdev: the led_classdev_mc काष्ठाure क्रम this device
 * @init_data: the LED class multicolor device initialization data
 *
 * Returns: 0 on success or negative error value on failure
 */
पूर्णांक led_classdev_multicolor_रेजिस्टर_ext(काष्ठा device *parent,
					    काष्ठा led_classdev_mc *mcled_cdev,
					    काष्ठा led_init_data *init_data);

/**
 * led_classdev_multicolor_unरेजिस्टर - unरेजिस्टरs an object of led_classdev
 *					class with support क्रम multicolor LEDs
 * @mcled_cdev: the multicolor LED to unरेजिस्टर
 *
 * Unरेजिस्टर a previously रेजिस्टरed via led_classdev_multicolor_रेजिस्टर
 * object
 */
व्योम led_classdev_multicolor_unरेजिस्टर(काष्ठा led_classdev_mc *mcled_cdev);

/* Calculate brightness क्रम the monochrome LED cluster */
पूर्णांक led_mc_calc_color_components(काष्ठा led_classdev_mc *mcled_cdev,
				 क्रमागत led_brightness brightness);

पूर्णांक devm_led_classdev_multicolor_रेजिस्टर_ext(काष्ठा device *parent,
					  काष्ठा led_classdev_mc *mcled_cdev,
					  काष्ठा led_init_data *init_data);

व्योम devm_led_classdev_multicolor_unरेजिस्टर(काष्ठा device *parent,
					    काष्ठा led_classdev_mc *mcled_cdev);
#अन्यथा

अटल अंतरभूत पूर्णांक led_classdev_multicolor_रेजिस्टर_ext(काष्ठा device *parent,
					    काष्ठा led_classdev_mc *mcled_cdev,
					    काष्ठा led_init_data *init_data)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम led_classdev_multicolor_unरेजिस्टर(काष्ठा led_classdev_mc *mcled_cdev) अणुपूर्ण;
अटल अंतरभूत पूर्णांक led_mc_calc_color_components(काष्ठा led_classdev_mc *mcled_cdev,
					       क्रमागत led_brightness brightness)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक devm_led_classdev_multicolor_रेजिस्टर_ext(काष्ठा device *parent,
					  काष्ठा led_classdev_mc *mcled_cdev,
					  काष्ठा led_init_data *init_data)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम devm_led_classdev_multicolor_unरेजिस्टर(काष्ठा device *parent,
					    काष्ठा led_classdev_mc *mcled_cdev)
अणुपूर्ण;

#पूर्ण_अगर  /* IS_ENABLED(CONFIG_LEDS_CLASS_MULTICOLOR) */

अटल अंतरभूत पूर्णांक led_classdev_multicolor_रेजिस्टर(काष्ठा device *parent,
					    काष्ठा led_classdev_mc *mcled_cdev)
अणु
	वापस led_classdev_multicolor_रेजिस्टर_ext(parent, mcled_cdev, शून्य);
पूर्ण

अटल अंतरभूत पूर्णांक devm_led_classdev_multicolor_रेजिस्टर(काष्ठा device *parent,
					     काष्ठा led_classdev_mc *mcled_cdev)
अणु
	वापस devm_led_classdev_multicolor_रेजिस्टर_ext(parent, mcled_cdev,
							 शून्य);
पूर्ण

#पूर्ण_अगर	/* _LINUX_MULTICOLOR_LEDS_H_INCLUDED */
