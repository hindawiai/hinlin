<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2011 Samsung Electronics Co., Ltd.
 *              http://www.samsung.com
 */

#अगर_अघोषित __ASM_PLAT_BACKLIGHT_S3C64XX_H
#घोषणा __ASM_PLAT_BACKLIGHT_S3C64XX_H __खाता__

/* samsung_bl_gpio_info - GPIO info क्रम PWM Backlight control
 * @no:		GPIO number क्रम PWM समयr out
 * @func:	Special function of GPIO line क्रम PWM समयr
 */
काष्ठा samsung_bl_gpio_info अणु
	पूर्णांक no;
	पूर्णांक func;
पूर्ण;

बाह्य व्योम __init samsung_bl_set(काष्ठा samsung_bl_gpio_info *gpio_info,
	काष्ठा platक्रमm_pwm_backlight_data *bl_data);

#पूर्ण_अगर /* __ASM_PLAT_BACKLIGHT_S3C64XX_H */
