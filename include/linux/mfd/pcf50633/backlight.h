<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  Copyright (C) 2009-2010, Lars-Peter Clausen <lars@metafoo.de>
 *      PCF50633 backlight device driver
 */

#अगर_अघोषित __LINUX_MFD_PCF50633_BACKLIGHT
#घोषणा __LINUX_MFD_PCF50633_BACKLIGHT

/*
* @शेष_brightness: Backlight brightness is initialized to this value
*
* Brightness to be used after the driver has been probed.
* Valid range 0-63.
*
* @शेष_brightness_limit: The actual brightness is limited by this value
*
* Brightness limit to be used after the driver has been probed. This is useful
* when it is not known how much घातer is available क्रम the backlight during
* probe.
* Valid range 0-63. Can be changed later with pcf50633_bl_set_brightness_limit.
*
* @ramp_समय: Display ramp समय when changing brightness
*
* When changing the backlights brightness the change is not instant, instead
* it fades smooth from one state to another. This value specअगरies how दीर्घ
* the fade should take. The lower the value the higher the fade समय.
* Valid range 0-255
*/
काष्ठा pcf50633_bl_platक्रमm_data अणु
	अचिन्हित पूर्णांक	शेष_brightness;
	अचिन्हित पूर्णांक	शेष_brightness_limit;
	uपूर्णांक8_t		ramp_समय;
पूर्ण;


काष्ठा pcf50633;

पूर्णांक pcf50633_bl_set_brightness_limit(काष्ठा pcf50633 *pcf, अचिन्हित पूर्णांक limit);

#पूर्ण_अगर

