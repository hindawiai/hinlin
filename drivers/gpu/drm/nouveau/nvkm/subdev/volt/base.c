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
#समावेश "priv.h"

#समावेश <subdev/मूलप्रण.स>
#समावेश <subdev/bios/vmap.h>
#समावेश <subdev/bios/volt.h>
#समावेश <subdev/therm.h>

पूर्णांक
nvkm_volt_get(काष्ठा nvkm_volt *volt)
अणु
	पूर्णांक ret, i;

	अगर (volt->func->volt_get)
		वापस volt->func->volt_get(volt);

	ret = volt->func->vid_get(volt);
	अगर (ret >= 0) अणु
		क्रम (i = 0; i < volt->vid_nr; i++) अणु
			अगर (volt->vid[i].vid == ret)
				वापस volt->vid[i].uv;
		पूर्ण
		ret = -EINVAL;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक
nvkm_volt_set(काष्ठा nvkm_volt *volt, u32 uv)
अणु
	काष्ठा nvkm_subdev *subdev = &volt->subdev;
	पूर्णांक i, ret = -EINVAL, best_err = volt->max_uv, best = -1;

	अगर (volt->func->volt_set)
		वापस volt->func->volt_set(volt, uv);

	क्रम (i = 0; i < volt->vid_nr; i++) अणु
		पूर्णांक err = volt->vid[i].uv - uv;
		अगर (err < 0 || err > best_err)
			जारी;

		best_err = err;
		best = i;
		अगर (best_err == 0)
			अवरोध;
	पूर्ण

	अगर (best == -1) अणु
		nvkm_error(subdev, "couldn't set %iuv\n", uv);
		वापस ret;
	पूर्ण

	ret = volt->func->vid_set(volt, volt->vid[best].vid);
	nvkm_debug(subdev, "set req %duv to %duv: %d\n", uv,
		   volt->vid[best].uv, ret);
	वापस ret;
पूर्ण

पूर्णांक
nvkm_volt_map_min(काष्ठा nvkm_volt *volt, u8 id)
अणु
	काष्ठा nvkm_bios *bios = volt->subdev.device->bios;
	काष्ठा nvbios_vmap_entry info;
	u8  ver, len;
	u32 vmap;

	vmap = nvbios_vmap_entry_parse(bios, id, &ver, &len, &info);
	अगर (vmap) अणु
		अगर (info.link != 0xff) अणु
			पूर्णांक ret = nvkm_volt_map_min(volt, info.link);
			अगर (ret < 0)
				वापस ret;
			info.min += ret;
		पूर्ण
		वापस info.min;
	पूर्ण

	वापस id ? id * 10000 : -ENODEV;
पूर्ण

पूर्णांक
nvkm_volt_map(काष्ठा nvkm_volt *volt, u8 id, u8 temp)
अणु
	काष्ठा nvkm_bios *bios = volt->subdev.device->bios;
	काष्ठा nvbios_vmap_entry info;
	u8  ver, len;
	u32 vmap;

	vmap = nvbios_vmap_entry_parse(bios, id, &ver, &len, &info);
	अगर (vmap) अणु
		s64 result;

		अगर (volt->speeकरो < 0)
			वापस volt->speeकरो;

		अगर (ver == 0x10 || (ver == 0x20 && info.mode == 0)) अणु
			result  = भाग64_s64((s64)info.arg[0], 10);
			result += भाग64_s64((s64)info.arg[1] * volt->speeकरो, 10);
			result += भाग64_s64((s64)info.arg[2] * volt->speeकरो * volt->speeकरो, 100000);
		पूर्ण अन्यथा अगर (ver == 0x20) अणु
			चयन (info.mode) अणु
			/* 0x0 handled above! */
			हाल 0x1:
				result =  ((s64)info.arg[0] * 15625) >> 18;
				result += ((s64)info.arg[1] * volt->speeकरो * 15625) >> 18;
				result += ((s64)info.arg[2] * temp * 15625) >> 10;
				result += ((s64)info.arg[3] * volt->speeकरो * temp * 15625) >> 18;
				result += ((s64)info.arg[4] * volt->speeकरो * volt->speeकरो * 15625) >> 30;
				result += ((s64)info.arg[5] * temp * temp * 15625) >> 18;
				अवरोध;
			हाल 0x3:
				result = (info.min + info.max) / 2;
				अवरोध;
			हाल 0x2:
			शेष:
				result = info.min;
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			वापस -ENODEV;
		पूर्ण

		result = min(max(result, (s64)info.min), (s64)info.max);

		अगर (info.link != 0xff) अणु
			पूर्णांक ret = nvkm_volt_map(volt, info.link, temp);
			अगर (ret < 0)
				वापस ret;
			result += ret;
		पूर्ण
		वापस result;
	पूर्ण

	वापस id ? id * 10000 : -ENODEV;
पूर्ण

पूर्णांक
nvkm_volt_set_id(काष्ठा nvkm_volt *volt, u8 id, u8 min_id, u8 temp,
		 पूर्णांक condition)
अणु
	पूर्णांक ret;

	अगर (volt->func->set_id)
		वापस volt->func->set_id(volt, id, condition);

	ret = nvkm_volt_map(volt, id, temp);
	अगर (ret >= 0) अणु
		पूर्णांक prev = nvkm_volt_get(volt);
		अगर (!condition || prev < 0 ||
		    (condition < 0 && ret < prev) ||
		    (condition > 0 && ret > prev)) अणु
			पूर्णांक min = nvkm_volt_map(volt, min_id, temp);
			अगर (min >= 0)
				ret = max(min, ret);
			ret = nvkm_volt_set(volt, ret);
		पूर्ण अन्यथा अणु
			ret = 0;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम
nvkm_volt_parse_bios(काष्ठा nvkm_bios *bios, काष्ठा nvkm_volt *volt)
अणु
	काष्ठा nvkm_subdev *subdev = &bios->subdev;
	काष्ठा nvbios_volt_entry ivid;
	काष्ठा nvbios_volt info;
	u8  ver, hdr, cnt, len;
	u32 data;
	पूर्णांक i;

	data = nvbios_volt_parse(bios, &ver, &hdr, &cnt, &len, &info);
	अगर (data && info.vidmask && info.base && info.step && info.ranged) अणु
		nvkm_debug(subdev, "found ranged based VIDs\n");
		volt->min_uv = info.min;
		volt->max_uv = info.max;
		क्रम (i = 0; i < info.vidmask + 1; i++) अणु
			अगर (info.base >= info.min &&
				info.base <= info.max) अणु
				volt->vid[volt->vid_nr].uv = info.base;
				volt->vid[volt->vid_nr].vid = i;
				volt->vid_nr++;
			पूर्ण
			info.base += info.step;
		पूर्ण
		volt->vid_mask = info.vidmask;
	पूर्ण अन्यथा अगर (data && info.vidmask && !info.ranged) अणु
		nvkm_debug(subdev, "found entry based VIDs\n");
		volt->min_uv = 0xffffffff;
		volt->max_uv = 0;
		क्रम (i = 0; i < cnt; i++) अणु
			data = nvbios_volt_entry_parse(bios, i, &ver, &hdr,
						       &ivid);
			अगर (data) अणु
				volt->vid[volt->vid_nr].uv = ivid.voltage;
				volt->vid[volt->vid_nr].vid = ivid.vid;
				volt->vid_nr++;
				volt->min_uv = min(volt->min_uv, ivid.voltage);
				volt->max_uv = max(volt->max_uv, ivid.voltage);
			पूर्ण
		पूर्ण
		volt->vid_mask = info.vidmask;
	पूर्ण अन्यथा अगर (data && info.type == NVBIOS_VOLT_PWM) अणु
		volt->min_uv = info.base;
		volt->max_uv = info.base + info.pwm_range;
	पूर्ण
पूर्ण

अटल पूर्णांक
nvkm_volt_speeकरो_पढ़ो(काष्ठा nvkm_volt *volt)
अणु
	अगर (volt->func->speeकरो_पढ़ो)
		वापस volt->func->speeकरो_पढ़ो(volt);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक
nvkm_volt_init(काष्ठा nvkm_subdev *subdev)
अणु
	काष्ठा nvkm_volt *volt = nvkm_volt(subdev);
	पूर्णांक ret = nvkm_volt_get(volt);
	अगर (ret < 0) अणु
		अगर (ret != -ENODEV)
			nvkm_debug(subdev, "current voltage unknown\n");
		वापस 0;
	पूर्ण
	nvkm_debug(subdev, "current voltage: %duv\n", ret);
	वापस 0;
पूर्ण

अटल पूर्णांक
nvkm_volt_oneinit(काष्ठा nvkm_subdev *subdev)
अणु
	काष्ठा nvkm_volt *volt = nvkm_volt(subdev);

	volt->speeकरो = nvkm_volt_speeकरो_पढ़ो(volt);
	अगर (volt->speeकरो > 0)
		nvkm_debug(&volt->subdev, "speedo %x\n", volt->speeकरो);

	अगर (volt->func->oneinit)
		वापस volt->func->oneinit(volt);

	वापस 0;
पूर्ण

अटल व्योम *
nvkm_volt_dtor(काष्ठा nvkm_subdev *subdev)
अणु
	वापस nvkm_volt(subdev);
पूर्ण

अटल स्थिर काष्ठा nvkm_subdev_func
nvkm_volt = अणु
	.dtor = nvkm_volt_dtor,
	.init = nvkm_volt_init,
	.oneinit = nvkm_volt_oneinit,
पूर्ण;

व्योम
nvkm_volt_ctor(स्थिर काष्ठा nvkm_volt_func *func, काष्ठा nvkm_device *device,
	       क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_volt *volt)
अणु
	काष्ठा nvkm_bios *bios = device->bios;
	पूर्णांक i;

	nvkm_subdev_ctor(&nvkm_volt, device, type, inst, &volt->subdev);
	volt->func = func;

	/* Assuming the non-bios device should build the voltage table later */
	अगर (bios) अणु
		u8 ver, hdr, cnt, len;
		काष्ठा nvbios_vmap vmap;

		nvkm_volt_parse_bios(bios, volt);
		nvkm_debug(&volt->subdev, "min: %iuv max: %iuv\n",
			   volt->min_uv, volt->max_uv);

		अगर (nvbios_vmap_parse(bios, &ver, &hdr, &cnt, &len, &vmap)) अणु
			volt->max0_id = vmap.max0;
			volt->max1_id = vmap.max1;
			volt->max2_id = vmap.max2;
		पूर्ण अन्यथा अणु
			volt->max0_id = 0xff;
			volt->max1_id = 0xff;
			volt->max2_id = 0xff;
		पूर्ण
	पूर्ण

	अगर (volt->vid_nr) अणु
		क्रम (i = 0; i < volt->vid_nr; i++) अणु
			nvkm_debug(&volt->subdev, "VID %02x: %duv\n",
				   volt->vid[i].vid, volt->vid[i].uv);
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक
nvkm_volt_new_(स्थिर काष्ठा nvkm_volt_func *func, काष्ठा nvkm_device *device,
	       क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_volt **pvolt)
अणु
	अगर (!(*pvolt = kzalloc(माप(**pvolt), GFP_KERNEL)))
		वापस -ENOMEM;
	nvkm_volt_ctor(func, device, type, inst, *pvolt);
	वापस 0;
पूर्ण
