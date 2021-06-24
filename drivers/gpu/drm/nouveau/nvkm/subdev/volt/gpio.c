<शैली गुरु>
/*
 * Copyright 2013 Red Hat Inc.
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
 * Authors: Ben Skeggs
 */
#समावेश <subdev/volt.h>
#समावेश <subdev/मूलप्रण.स>
#समावेश <subdev/bios/gpपन.स>
#समावेश <subdev/gpपन.स>
#समावेश "priv.h"

अटल स्थिर u8 tags[] = अणु
	DCB_GPIO_VID0, DCB_GPIO_VID1, DCB_GPIO_VID2, DCB_GPIO_VID3,
	DCB_GPIO_VID4, DCB_GPIO_VID5, DCB_GPIO_VID6, DCB_GPIO_VID7,
पूर्ण;

पूर्णांक
nvkm_voltgpio_get(काष्ठा nvkm_volt *volt)
अणु
	काष्ठा nvkm_gpio *gpio = volt->subdev.device->gpio;
	u8 vid = 0;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(tags); i++) अणु
		अगर (volt->vid_mask & (1 << i)) अणु
			पूर्णांक ret = nvkm_gpio_get(gpio, 0, tags[i], 0xff);
			अगर (ret < 0)
				वापस ret;
			vid |= ret << i;
		पूर्ण
	पूर्ण

	वापस vid;
पूर्ण

पूर्णांक
nvkm_voltgpio_set(काष्ठा nvkm_volt *volt, u8 vid)
अणु
	काष्ठा nvkm_gpio *gpio = volt->subdev.device->gpio;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(tags); i++, vid >>= 1) अणु
		अगर (volt->vid_mask & (1 << i)) अणु
			पूर्णांक ret = nvkm_gpio_set(gpio, 0, tags[i], 0xff, vid & 1);
			अगर (ret < 0)
				वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक
nvkm_voltgpio_init(काष्ठा nvkm_volt *volt)
अणु
	काष्ठा nvkm_subdev *subdev = &volt->subdev;
	काष्ठा nvkm_gpio *gpio = subdev->device->gpio;
	काष्ठा dcb_gpio_func func;
	पूर्णांक i;

	/* check we have gpio function info क्रम each vid bit.  on some
	 * boards (ie. nvs295) the vid mask has more bits than there
	 * are valid gpio functions... from traces, nvidia appear to
	 * just touch the existing ones, so let's mask off the invalid
	 * bits and जारी with lअगरe
	 */
	क्रम (i = 0; i < ARRAY_SIZE(tags); i++) अणु
		अगर (volt->vid_mask & (1 << i)) अणु
			पूर्णांक ret = nvkm_gpio_find(gpio, 0, tags[i], 0xff, &func);
			अगर (ret) अणु
				अगर (ret != -ENOENT)
					वापस ret;
				nvkm_debug(subdev, "VID bit %d has no GPIO\n", i);
				volt->vid_mask &= ~(1 << i);
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
