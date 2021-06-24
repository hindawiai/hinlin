<शैली गुरु>
/*
 * Copyright 2015 Martin Peres
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: Martin Peres <martin.peres@मुक्त.fr>
 */

#अगर_अघोषित __NOUVEAU_LED_H__
#घोषणा __NOUVEAU_LED_H__

#समावेश "nouveau_drv.h"

काष्ठा led_classdev;

काष्ठा nouveau_led अणु
	काष्ठा drm_device *dev;

	काष्ठा led_classdev led;
पूर्ण;

अटल अंतरभूत काष्ठा nouveau_led *
nouveau_led(काष्ठा drm_device *dev)
अणु
	वापस nouveau_drm(dev)->led;
पूर्ण

/* nouveau_led.c */
#अगर IS_REACHABLE(CONFIG_LEDS_CLASS)
पूर्णांक  nouveau_led_init(काष्ठा drm_device *dev);
व्योम nouveau_led_suspend(काष्ठा drm_device *dev);
व्योम nouveau_led_resume(काष्ठा drm_device *dev);
व्योम nouveau_led_fini(काष्ठा drm_device *dev);
#अन्यथा
अटल अंतरभूत पूर्णांक  nouveau_led_init(काष्ठा drm_device *dev) अणु वापस 0; पूर्ण;
अटल अंतरभूत व्योम nouveau_led_suspend(काष्ठा drm_device *dev) अणु पूर्ण;
अटल अंतरभूत व्योम nouveau_led_resume(काष्ठा drm_device *dev) अणु पूर्ण;
अटल अंतरभूत व्योम nouveau_led_fini(काष्ठा drm_device *dev) अणु पूर्ण;
#पूर्ण_अगर

#पूर्ण_अगर
