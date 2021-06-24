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
 * Authors: Martin Peres
 */
#समावेश "priv.h"

#समावेश <subdev/volt.h>
#समावेश <subdev/gpपन.स>
#समावेश <subdev/मूलप्रण.स>
#समावेश <subdev/bios/volt.h>
#समावेश <subdev/fuse.h>

#घोषणा gk104_volt(p) container_of((p), काष्ठा gk104_volt, base)
काष्ठा gk104_volt अणु
	काष्ठा nvkm_volt base;
	काष्ठा nvbios_volt bios;
पूर्ण;

अटल पूर्णांक
gk104_volt_get(काष्ठा nvkm_volt *base)
अणु
	काष्ठा nvbios_volt *bios = &gk104_volt(base)->bios;
	काष्ठा nvkm_device *device = base->subdev.device;
	u32 भाग, duty;

	भाग  = nvkm_rd32(device, 0x20340);
	duty = nvkm_rd32(device, 0x20344);

	वापस bios->base + bios->pwm_range * duty / भाग;
पूर्ण

अटल पूर्णांक
gk104_volt_set(काष्ठा nvkm_volt *base, u32 uv)
अणु
	काष्ठा nvbios_volt *bios = &gk104_volt(base)->bios;
	काष्ठा nvkm_device *device = base->subdev.device;
	u32 भाग, duty;

	/* the blob uses this crystal frequency, let's use it too. */
	भाग = 27648000 / bios->pwm_freq;
	duty = DIV_ROUND_UP((uv - bios->base) * भाग, bios->pwm_range);

	nvkm_wr32(device, 0x20340, भाग);
	nvkm_wr32(device, 0x20344, 0x80000000 | duty);

	वापस 0;
पूर्ण

अटल पूर्णांक
gk104_volt_speeकरो_पढ़ो(काष्ठा nvkm_volt *volt)
अणु
	काष्ठा nvkm_device *device = volt->subdev.device;
	काष्ठा nvkm_fuse *fuse = device->fuse;
	पूर्णांक ret;

	अगर (!fuse)
		वापस -EINVAL;

	nvkm_wr32(device, 0x122634, 0x0);
	ret = nvkm_fuse_पढ़ो(fuse, 0x3a8);
	nvkm_wr32(device, 0x122634, 0x41);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा nvkm_volt_func
gk104_volt_pwm = अणु
	.oneinit = gf100_volt_oneinit,
	.volt_get = gk104_volt_get,
	.volt_set = gk104_volt_set,
	.speeकरो_पढ़ो = gk104_volt_speeकरो_पढ़ो,
पूर्ण, gk104_volt_gpio = अणु
	.oneinit = gf100_volt_oneinit,
	.vid_get = nvkm_voltgpio_get,
	.vid_set = nvkm_voltgpio_set,
	.speeकरो_पढ़ो = gk104_volt_speeकरो_पढ़ो,
पूर्ण;

पूर्णांक
gk104_volt_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
	       काष्ठा nvkm_volt **pvolt)
अणु
	स्थिर काष्ठा nvkm_volt_func *volt_func = &gk104_volt_gpio;
	काष्ठा dcb_gpio_func gpio;
	काष्ठा nvbios_volt bios;
	काष्ठा gk104_volt *volt;
	u8 ver, hdr, cnt, len;
	स्थिर अक्षर *mode;

	अगर (!nvbios_volt_parse(device->bios, &ver, &hdr, &cnt, &len, &bios))
		वापस 0;

	अगर (!nvkm_gpio_find(device->gpio, 0, DCB_GPIO_VID_PWM, 0xff, &gpio) &&
	    bios.type == NVBIOS_VOLT_PWM) अणु
		volt_func = &gk104_volt_pwm;
	पूर्ण

	अगर (!(volt = kzalloc(माप(*volt), GFP_KERNEL)))
		वापस -ENOMEM;
	nvkm_volt_ctor(volt_func, device, type, inst, &volt->base);
	*pvolt = &volt->base;
	volt->bios = bios;

	/* now that we have a subdev, we can show an error अगर we found through
	 * the voltage table that we were supposed to use the PWN mode but we
	 * did not find the right GPIO क्रम it.
	 */
	अगर (bios.type == NVBIOS_VOLT_PWM && volt_func != &gk104_volt_pwm) अणु
		nvkm_error(&volt->base.subdev,
			   "Type mismatch between the voltage table type and "
			   "the GPIO table. Fallback to GPIO mode.\n");
	पूर्ण

	अगर (volt_func == &gk104_volt_gpio) अणु
		nvkm_voltgpio_init(&volt->base);
		mode = "GPIO";
	पूर्ण अन्यथा
		mode = "PWM";

	nvkm_debug(&volt->base.subdev, "Using %s mode\n", mode);

	वापस 0;
पूर्ण
