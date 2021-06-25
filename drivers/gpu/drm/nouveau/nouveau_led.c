<शैली गुरु>
/*
 * Copyright (C) 2016 Martin Peres
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining
 * a copy of this software and associated करोcumentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modअगरy, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE COPYRIGHT OWNER(S) AND/OR ITS SUPPLIERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

/*
 * Authors:
 *  Martin Peres <martin.peres@मुक्त.fr>
 */

#समावेश <linux/leds.h>

#समावेश "nouveau_led.h"
#समावेश <nvkm/subdev/gpपन.स>

अटल क्रमागत led_brightness
nouveau_led_get_brightness(काष्ठा led_classdev *led)
अणु
	काष्ठा drm_device *drm_dev = container_of(led, काष्ठा nouveau_led, led)->dev;
	काष्ठा nouveau_drm *drm = nouveau_drm(drm_dev);
	काष्ठा nvअगर_object *device = &drm->client.device.object;
	u32 भाग, duty;

	भाग =  nvअगर_rd32(device, 0x61c880) & 0x00ffffff;
	duty = nvअगर_rd32(device, 0x61c884) & 0x00ffffff;

	अगर (भाग > 0)
		वापस duty * LED_FULL / भाग;
	अन्यथा
		वापस 0;
पूर्ण

अटल व्योम
nouveau_led_set_brightness(काष्ठा led_classdev *led, क्रमागत led_brightness value)
अणु
	काष्ठा drm_device *drm_dev = container_of(led, काष्ठा nouveau_led, led)->dev;
	काष्ठा nouveau_drm *drm = nouveau_drm(drm_dev);
	काष्ठा nvअगर_object *device = &drm->client.device.object;

	u32 input_clk = 27e6; /* PDISPLAY.SOR[1].PWM is connected to the crystal */
	u32 freq = 100; /* this is what nvidia uses and it should be good-enough */
	u32 भाग, duty;

	भाग = input_clk / freq;
	duty = value * भाग / LED_FULL;

	/* क्रम now, this is safe to directly poke those रेजिस्टरs because:
	 *  - A: nvidia never माला_दो the logo led to any other PWM controler
	 *       than PDISPLAY.SOR[1].PWM.
	 *  - B: nouveau करोes not touch these रेजिस्टरs anywhere अन्यथा
	 */
	nvअगर_wr32(device, 0x61c880, भाग);
	nvअगर_wr32(device, 0x61c884, 0xc0000000 | duty);
पूर्ण


पूर्णांक
nouveau_led_init(काष्ठा drm_device *dev)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	काष्ठा nvkm_gpio *gpio = nvxx_gpio(&drm->client.device);
	काष्ठा dcb_gpio_func logo_led;
	पूर्णांक ret;

	अगर (!gpio)
		वापस 0;

	/* check that there is a GPIO controlling the logo LED */
	अगर (nvkm_gpio_find(gpio, 0, DCB_GPIO_LOGO_LED_PWM, 0xff, &logo_led))
		वापस 0;

	drm->led = kzalloc(माप(*drm->led), GFP_KERNEL);
	अगर (!drm->led)
		वापस -ENOMEM;
	drm->led->dev = dev;

	drm->led->led.name = "nvidia-logo";
	drm->led->led.max_brightness = 255;
	drm->led->led.brightness_get = nouveau_led_get_brightness;
	drm->led->led.brightness_set = nouveau_led_set_brightness;

	ret = led_classdev_रेजिस्टर(dev->dev, &drm->led->led);
	अगर (ret) अणु
		kमुक्त(drm->led);
		drm->led = शून्य;
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

व्योम
nouveau_led_suspend(काष्ठा drm_device *dev)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);

	अगर (drm->led)
		led_classdev_suspend(&drm->led->led);
पूर्ण

व्योम
nouveau_led_resume(काष्ठा drm_device *dev)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);

	अगर (drm->led)
		led_classdev_resume(&drm->led->led);
पूर्ण

व्योम
nouveau_led_fini(काष्ठा drm_device *dev)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);

	अगर (drm->led) अणु
		led_classdev_unरेजिस्टर(&drm->led->led);
		kमुक्त(drm->led);
		drm->led = शून्य;
	पूर्ण
पूर्ण
