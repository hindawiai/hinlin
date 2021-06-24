<शैली गुरु>
/*
 * Copyright 2011 Red Hat Inc.
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
#समावेश "priv.h"

#समावेश <core/option.h>
#समावेश <core/notअगरy.h>

अटल पूर्णांक
nvkm_gpio_drive(काष्ठा nvkm_gpio *gpio, पूर्णांक idx, पूर्णांक line, पूर्णांक dir, पूर्णांक out)
अणु
	वापस gpio->func->drive(gpio, line, dir, out);
पूर्ण

अटल पूर्णांक
nvkm_gpio_sense(काष्ठा nvkm_gpio *gpio, पूर्णांक idx, पूर्णांक line)
अणु
	वापस gpio->func->sense(gpio, line);
पूर्ण

व्योम
nvkm_gpio_reset(काष्ठा nvkm_gpio *gpio, u8 func)
अणु
	अगर (gpio->func->reset)
		gpio->func->reset(gpio, func);
पूर्ण

पूर्णांक
nvkm_gpio_find(काष्ठा nvkm_gpio *gpio, पूर्णांक idx, u8 tag, u8 line,
	       काष्ठा dcb_gpio_func *func)
अणु
	काष्ठा nvkm_device *device = gpio->subdev.device;
	काष्ठा nvkm_bios *bios = device->bios;
	u8  ver, len;
	u16 data;

	अगर (line == 0xff && tag == 0xff)
		वापस -EINVAL;

	data = dcb_gpio_match(bios, idx, tag, line, &ver, &len, func);
	अगर (data)
		वापस 0;

	/* Apple iMac G4 NV18 */
	अगर (device->quirk && device->quirk->tv_gpio) अणु
		अगर (tag == DCB_GPIO_TVDAC0) अणु
			*func = (काष्ठा dcb_gpio_func) अणु
				.func = DCB_GPIO_TVDAC0,
				.line = device->quirk->tv_gpio,
				.log[0] = 0,
				.log[1] = 1,
			पूर्ण;
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -ENOENT;
पूर्ण

पूर्णांक
nvkm_gpio_set(काष्ठा nvkm_gpio *gpio, पूर्णांक idx, u8 tag, u8 line, पूर्णांक state)
अणु
	काष्ठा dcb_gpio_func func;
	पूर्णांक ret;

	ret = nvkm_gpio_find(gpio, idx, tag, line, &func);
	अगर (ret == 0) अणु
		पूर्णांक dir = !!(func.log[state] & 0x02);
		पूर्णांक out = !!(func.log[state] & 0x01);
		ret = nvkm_gpio_drive(gpio, idx, func.line, dir, out);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक
nvkm_gpio_get(काष्ठा nvkm_gpio *gpio, पूर्णांक idx, u8 tag, u8 line)
अणु
	काष्ठा dcb_gpio_func func;
	पूर्णांक ret;

	ret = nvkm_gpio_find(gpio, idx, tag, line, &func);
	अगर (ret == 0) अणु
		ret = nvkm_gpio_sense(gpio, idx, func.line);
		अगर (ret >= 0)
			ret = (ret == (func.log[1] & 1));
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम
nvkm_gpio_पूर्णांकr_fini(काष्ठा nvkm_event *event, पूर्णांक type, पूर्णांक index)
अणु
	काष्ठा nvkm_gpio *gpio = container_of(event, typeof(*gpio), event);
	gpio->func->पूर्णांकr_mask(gpio, type, 1 << index, 0);
पूर्ण

अटल व्योम
nvkm_gpio_पूर्णांकr_init(काष्ठा nvkm_event *event, पूर्णांक type, पूर्णांक index)
अणु
	काष्ठा nvkm_gpio *gpio = container_of(event, typeof(*gpio), event);
	gpio->func->पूर्णांकr_mask(gpio, type, 1 << index, 1 << index);
पूर्ण

अटल पूर्णांक
nvkm_gpio_पूर्णांकr_ctor(काष्ठा nvkm_object *object, व्योम *data, u32 size,
		    काष्ठा nvkm_notअगरy *notअगरy)
अणु
	काष्ठा nvkm_gpio_ntfy_req *req = data;
	अगर (!WARN_ON(size != माप(*req))) अणु
		notअगरy->size  = माप(काष्ठा nvkm_gpio_ntfy_rep);
		notअगरy->types = req->mask;
		notअगरy->index = req->line;
		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा nvkm_event_func
nvkm_gpio_पूर्णांकr_func = अणु
	.ctor = nvkm_gpio_पूर्णांकr_ctor,
	.init = nvkm_gpio_पूर्णांकr_init,
	.fini = nvkm_gpio_पूर्णांकr_fini,
पूर्ण;

अटल व्योम
nvkm_gpio_पूर्णांकr(काष्ठा nvkm_subdev *subdev)
अणु
	काष्ठा nvkm_gpio *gpio = nvkm_gpio(subdev);
	u32 hi, lo, i;

	gpio->func->पूर्णांकr_stat(gpio, &hi, &lo);

	क्रम (i = 0; (hi | lo) && i < gpio->func->lines; i++) अणु
		काष्ठा nvkm_gpio_ntfy_rep rep = अणु
			.mask = (NVKM_GPIO_HI * !!(hi & (1 << i))) |
				(NVKM_GPIO_LO * !!(lo & (1 << i))),
		पूर्ण;
		nvkm_event_send(&gpio->event, rep.mask, i, &rep, माप(rep));
	पूर्ण
पूर्ण

अटल पूर्णांक
nvkm_gpio_fini(काष्ठा nvkm_subdev *subdev, bool suspend)
अणु
	काष्ठा nvkm_gpio *gpio = nvkm_gpio(subdev);
	u32 mask = (1ULL << gpio->func->lines) - 1;

	gpio->func->पूर्णांकr_mask(gpio, NVKM_GPIO_TOGGLED, mask, 0);
	gpio->func->पूर्णांकr_stat(gpio, &mask, &mask);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dmi_प्रणाली_id gpio_reset_ids[] = अणु
	अणु
		.ident = "Apple Macbook 10,1",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Apple Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "MacBookPro10,1"),
		पूर्ण
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल क्रमागत dcb_gpio_func_name घातer_checks[] = अणु
	DCB_GPIO_THERM_EXT_POWER_EVENT,
	DCB_GPIO_POWER_ALERT,
	DCB_GPIO_EXT_POWER_LOW,
पूर्ण;

अटल पूर्णांक
nvkm_gpio_init(काष्ठा nvkm_subdev *subdev)
अणु
	काष्ठा nvkm_gpio *gpio = nvkm_gpio(subdev);
	काष्ठा dcb_gpio_func func;
	पूर्णांक ret;
	पूर्णांक i;

	अगर (dmi_check_प्रणाली(gpio_reset_ids))
		nvkm_gpio_reset(gpio, DCB_GPIO_UNUSED);

	अगर (nvkm_boolopt(subdev->device->cfgopt, "NvPowerChecks", true)) अणु
		क्रम (i = 0; i < ARRAY_SIZE(घातer_checks); ++i) अणु
			ret = nvkm_gpio_find(gpio, 0, घातer_checks[i],
					     DCB_GPIO_UNUSED, &func);
			अगर (ret)
				जारी;

			ret = nvkm_gpio_get(gpio, 0, func.func, func.line);
			अगर (!ret)
				जारी;

			nvkm_error(&gpio->subdev,
				   "GPU is missing power, check its power "
				   "cables.  Boot with "
				   "nouveau.config=NvPowerChecks=0 to "
				   "disable.\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम *
nvkm_gpio_dtor(काष्ठा nvkm_subdev *subdev)
अणु
	काष्ठा nvkm_gpio *gpio = nvkm_gpio(subdev);
	nvkm_event_fini(&gpio->event);
	वापस gpio;
पूर्ण

अटल स्थिर काष्ठा nvkm_subdev_func
nvkm_gpio = अणु
	.dtor = nvkm_gpio_dtor,
	.init = nvkm_gpio_init,
	.fini = nvkm_gpio_fini,
	.पूर्णांकr = nvkm_gpio_पूर्णांकr,
पूर्ण;

पूर्णांक
nvkm_gpio_new_(स्थिर काष्ठा nvkm_gpio_func *func, काष्ठा nvkm_device *device,
	       क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_gpio **pgpio)
अणु
	काष्ठा nvkm_gpio *gpio;

	अगर (!(gpio = *pgpio = kzalloc(माप(*gpio), GFP_KERNEL)))
		वापस -ENOMEM;

	nvkm_subdev_ctor(&nvkm_gpio, device, type, inst, &gpio->subdev);
	gpio->func = func;

	वापस nvkm_event_init(&nvkm_gpio_पूर्णांकr_func, 2, func->lines,
			       &gpio->event);
पूर्ण
