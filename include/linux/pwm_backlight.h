<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Generic PWM backlight driver data - see drivers/video/backlight/pwm_bl.c
 */
#अगर_अघोषित __LINUX_PWM_BACKLIGHT_H
#घोषणा __LINUX_PWM_BACKLIGHT_H

#समावेश <linux/backlight.h>

काष्ठा platक्रमm_pwm_backlight_data अणु
	पूर्णांक pwm_id;
	अचिन्हित पूर्णांक max_brightness;
	अचिन्हित पूर्णांक dft_brightness;
	अचिन्हित पूर्णांक lth_brightness;
	अचिन्हित पूर्णांक pwm_period_ns;
	अचिन्हित पूर्णांक *levels;
	अचिन्हित पूर्णांक post_pwm_on_delay;
	अचिन्हित पूर्णांक pwm_off_delay;
	पूर्णांक (*init)(काष्ठा device *dev);
	पूर्णांक (*notअगरy)(काष्ठा device *dev, पूर्णांक brightness);
	व्योम (*notअगरy_after)(काष्ठा device *dev, पूर्णांक brightness);
	व्योम (*निकास)(काष्ठा device *dev);
	पूर्णांक (*check_fb)(काष्ठा device *dev, काष्ठा fb_info *info);
पूर्ण;

#पूर्ण_अगर
