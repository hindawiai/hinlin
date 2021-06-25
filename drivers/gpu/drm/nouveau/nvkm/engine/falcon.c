<शैली गुरु>
/*
 * Copyright 2012 Red Hat Inc.
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
 */
#समावेश <engine/falcon.h>

#समावेश <core/gpuobj.h>
#समावेश <subdev/mc.h>
#समावेश <subdev/समयr.h>
#समावेश <engine/fअगरo.h>

अटल पूर्णांक
nvkm_falcon_oclass_get(काष्ठा nvkm_oclass *oclass, पूर्णांक index)
अणु
	काष्ठा nvkm_falcon *falcon = nvkm_falcon(oclass->engine);
	पूर्णांक c = 0;

	जबतक (falcon->func->sclass[c].oclass) अणु
		अगर (c++ == index) अणु
			oclass->base = falcon->func->sclass[index];
			वापस index;
		पूर्ण
	पूर्ण

	वापस c;
पूर्ण

अटल पूर्णांक
nvkm_falcon_cclass_bind(काष्ठा nvkm_object *object, काष्ठा nvkm_gpuobj *parent,
			पूर्णांक align, काष्ठा nvkm_gpuobj **pgpuobj)
अणु
	वापस nvkm_gpuobj_new(object->engine->subdev.device, 256,
			       align, true, parent, pgpuobj);
पूर्ण

अटल स्थिर काष्ठा nvkm_object_func
nvkm_falcon_cclass = अणु
	.bind = nvkm_falcon_cclass_bind,
पूर्ण;

अटल व्योम
nvkm_falcon_पूर्णांकr(काष्ठा nvkm_engine *engine)
अणु
	काष्ठा nvkm_falcon *falcon = nvkm_falcon(engine);
	काष्ठा nvkm_subdev *subdev = &falcon->engine.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	स्थिर u32 base = falcon->addr;
	u32 dest = nvkm_rd32(device, base + 0x01c);
	u32 पूर्णांकr = nvkm_rd32(device, base + 0x008) & dest & ~(dest >> 16);
	u32 inst = nvkm_rd32(device, base + 0x050) & 0x3fffffff;
	काष्ठा nvkm_fअगरo_chan *chan;
	अचिन्हित दीर्घ flags;

	chan = nvkm_fअगरo_chan_inst(device->fअगरo, (u64)inst << 12, &flags);

	अगर (पूर्णांकr & 0x00000040) अणु
		अगर (falcon->func->पूर्णांकr) अणु
			falcon->func->पूर्णांकr(falcon, chan);
			nvkm_wr32(device, base + 0x004, 0x00000040);
			पूर्णांकr &= ~0x00000040;
		पूर्ण
	पूर्ण

	अगर (पूर्णांकr & 0x00000010) अणु
		nvkm_debug(subdev, "ucode halted\n");
		nvkm_wr32(device, base + 0x004, 0x00000010);
		पूर्णांकr &= ~0x00000010;
	पूर्ण

	अगर (पूर्णांकr)  अणु
		nvkm_error(subdev, "intr %08x\n", पूर्णांकr);
		nvkm_wr32(device, base + 0x004, पूर्णांकr);
	पूर्ण

	nvkm_fअगरo_chan_put(device->fअगरo, flags, &chan);
पूर्ण

अटल पूर्णांक
nvkm_falcon_fini(काष्ठा nvkm_engine *engine, bool suspend)
अणु
	काष्ठा nvkm_falcon *falcon = nvkm_falcon(engine);
	काष्ठा nvkm_device *device = falcon->engine.subdev.device;
	स्थिर u32 base = falcon->addr;

	अगर (!suspend) अणु
		nvkm_memory_unref(&falcon->core);
		अगर (falcon->बाह्यal) अणु
			vमुक्त(falcon->data.data);
			vमुक्त(falcon->code.data);
			falcon->code.data = शून्य;
		पूर्ण
	पूर्ण

	अगर (nvkm_mc_enabled(device, engine->subdev.type, engine->subdev.inst)) अणु
		nvkm_mask(device, base + 0x048, 0x00000003, 0x00000000);
		nvkm_wr32(device, base + 0x014, 0xffffffff);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम *
vmemdup(स्थिर व्योम *src, माप_प्रकार len)
अणु
	व्योम *p = vदो_स्मृति(len);

	अगर (p)
		स_नकल(p, src, len);
	वापस p;
पूर्ण

अटल पूर्णांक
nvkm_falcon_oneinit(काष्ठा nvkm_engine *engine)
अणु
	काष्ठा nvkm_falcon *falcon = nvkm_falcon(engine);
	काष्ठा nvkm_subdev *subdev = &falcon->engine.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	स्थिर u32 base = falcon->addr;
	u32 caps;

	/* determine falcon capabilities */
	अगर (device->chipset <  0xa3 ||
	    device->chipset == 0xaa || device->chipset == 0xac) अणु
		falcon->version = 0;
		falcon->secret  = (falcon->addr == 0x087000) ? 1 : 0;
	पूर्ण अन्यथा अणु
		caps = nvkm_rd32(device, base + 0x12c);
		falcon->version = (caps & 0x0000000f);
		falcon->secret  = (caps & 0x00000030) >> 4;
	पूर्ण

	caps = nvkm_rd32(device, base + 0x108);
	falcon->code.limit = (caps & 0x000001ff) << 8;
	falcon->data.limit = (caps & 0x0003fe00) >> 1;

	nvkm_debug(subdev, "falcon version: %d\n", falcon->version);
	nvkm_debug(subdev, "secret level: %d\n", falcon->secret);
	nvkm_debug(subdev, "code limit: %d\n", falcon->code.limit);
	nvkm_debug(subdev, "data limit: %d\n", falcon->data.limit);
	वापस 0;
पूर्ण

अटल पूर्णांक
nvkm_falcon_init(काष्ठा nvkm_engine *engine)
अणु
	काष्ठा nvkm_falcon *falcon = nvkm_falcon(engine);
	काष्ठा nvkm_subdev *subdev = &falcon->engine.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	स्थिर काष्ठा firmware *fw;
	अक्षर name[32] = "internal";
	स्थिर u32 base = falcon->addr;
	पूर्णांक ret, i;

	/* रुको क्रम 'uc halted' to be संकेतled beक्रमe continuing */
	अगर (falcon->secret && falcon->version < 4) अणु
		अगर (!falcon->version) अणु
			nvkm_msec(device, 2000,
				अगर (nvkm_rd32(device, base + 0x008) & 0x00000010)
					अवरोध;
			);
		पूर्ण अन्यथा अणु
			nvkm_msec(device, 2000,
				अगर (!(nvkm_rd32(device, base + 0x180) & 0x80000000))
					अवरोध;
			);
		पूर्ण
		nvkm_wr32(device, base + 0x004, 0x00000010);
	पूर्ण

	/* disable all पूर्णांकerrupts */
	nvkm_wr32(device, base + 0x014, 0xffffffff);

	/* no शेष ucode provided by the engine implementation, try and
	 * locate a "self-bootstrapping" firmware image क्रम the engine
	 */
	अगर (!falcon->code.data) अणु
		snम_लिखो(name, माप(name), "nouveau/nv%02x_fuc%03x",
			 device->chipset, falcon->addr >> 12);

		ret = request_firmware(&fw, name, device->dev);
		अगर (ret == 0) अणु
			falcon->code.data = vmemdup(fw->data, fw->size);
			falcon->code.size = fw->size;
			falcon->data.data = शून्य;
			falcon->data.size = 0;
			release_firmware(fw);
		पूर्ण

		falcon->बाह्यal = true;
	पूर्ण

	/* next step is to try and load "static code/data segment" firmware
	 * images क्रम the engine
	 */
	अगर (!falcon->code.data) अणु
		snम_लिखो(name, माप(name), "nouveau/nv%02x_fuc%03xd",
			 device->chipset, falcon->addr >> 12);

		ret = request_firmware(&fw, name, device->dev);
		अगर (ret) अणु
			nvkm_error(subdev, "unable to load firmware data\n");
			वापस -ENODEV;
		पूर्ण

		falcon->data.data = vmemdup(fw->data, fw->size);
		falcon->data.size = fw->size;
		release_firmware(fw);
		अगर (!falcon->data.data)
			वापस -ENOMEM;

		snम_लिखो(name, माप(name), "nouveau/nv%02x_fuc%03xc",
			 device->chipset, falcon->addr >> 12);

		ret = request_firmware(&fw, name, device->dev);
		अगर (ret) अणु
			nvkm_error(subdev, "unable to load firmware code\n");
			वापस -ENODEV;
		पूर्ण

		falcon->code.data = vmemdup(fw->data, fw->size);
		falcon->code.size = fw->size;
		release_firmware(fw);
		अगर (!falcon->code.data)
			वापस -ENOMEM;
	पूर्ण

	nvkm_debug(subdev, "firmware: %s (%s)\n", name, falcon->data.data ?
		   "static code/data segments" : "self-bootstrapping");

	/* ensure any "self-bootstrapping" firmware image is in vram */
	अगर (!falcon->data.data && !falcon->core) अणु
		ret = nvkm_memory_new(device, NVKM_MEM_TARGET_INST,
				      falcon->code.size, 256, false,
				      &falcon->core);
		अगर (ret) अणु
			nvkm_error(subdev, "core allocation failed, %d\n", ret);
			वापस ret;
		पूर्ण

		nvkm_kmap(falcon->core);
		क्रम (i = 0; i < falcon->code.size; i += 4)
			nvkm_wo32(falcon->core, i, falcon->code.data[i / 4]);
		nvkm_करोne(falcon->core);
	पूर्ण

	/* upload firmware bootloader (or the full code segments) */
	अगर (falcon->core) अणु
		u64 addr = nvkm_memory_addr(falcon->core);
		अगर (device->card_type < NV_C0)
			nvkm_wr32(device, base + 0x618, 0x04000000);
		अन्यथा
			nvkm_wr32(device, base + 0x618, 0x00000114);
		nvkm_wr32(device, base + 0x11c, 0);
		nvkm_wr32(device, base + 0x110, addr >> 8);
		nvkm_wr32(device, base + 0x114, 0);
		nvkm_wr32(device, base + 0x118, 0x00006610);
	पूर्ण अन्यथा अणु
		अगर (falcon->code.size > falcon->code.limit ||
		    falcon->data.size > falcon->data.limit) अणु
			nvkm_error(subdev, "ucode exceeds falcon limit(s)\n");
			वापस -EINVAL;
		पूर्ण

		अगर (falcon->version < 3) अणु
			nvkm_wr32(device, base + 0xff8, 0x00100000);
			क्रम (i = 0; i < falcon->code.size / 4; i++)
				nvkm_wr32(device, base + 0xff4, falcon->code.data[i]);
		पूर्ण अन्यथा अणु
			nvkm_wr32(device, base + 0x180, 0x01000000);
			क्रम (i = 0; i < falcon->code.size / 4; i++) अणु
				अगर ((i & 0x3f) == 0)
					nvkm_wr32(device, base + 0x188, i >> 6);
				nvkm_wr32(device, base + 0x184, falcon->code.data[i]);
			पूर्ण
		पूर्ण
	पूर्ण

	/* upload data segment (अगर necessary), zeroing the reमुख्यder */
	अगर (falcon->version < 3) अणु
		nvkm_wr32(device, base + 0xff8, 0x00000000);
		क्रम (i = 0; !falcon->core && i < falcon->data.size / 4; i++)
			nvkm_wr32(device, base + 0xff4, falcon->data.data[i]);
		क्रम (; i < falcon->data.limit; i += 4)
			nvkm_wr32(device, base + 0xff4, 0x00000000);
	पूर्ण अन्यथा अणु
		nvkm_wr32(device, base + 0x1c0, 0x01000000);
		क्रम (i = 0; !falcon->core && i < falcon->data.size / 4; i++)
			nvkm_wr32(device, base + 0x1c4, falcon->data.data[i]);
		क्रम (; i < falcon->data.limit / 4; i++)
			nvkm_wr32(device, base + 0x1c4, 0x00000000);
	पूर्ण

	/* start it running */
	nvkm_wr32(device, base + 0x10c, 0x00000001); /* BLOCK_ON_FIFO */
	nvkm_wr32(device, base + 0x104, 0x00000000); /* ENTRY */
	nvkm_wr32(device, base + 0x100, 0x00000002); /* TRIGGER */
	nvkm_wr32(device, base + 0x048, 0x00000003); /* FIFO | CHSW */

	अगर (falcon->func->init)
		falcon->func->init(falcon);
	वापस 0;
पूर्ण

अटल व्योम *
nvkm_falcon_dtor(काष्ठा nvkm_engine *engine)
अणु
	वापस nvkm_falcon(engine);
पूर्ण

अटल स्थिर काष्ठा nvkm_engine_func
nvkm_falcon = अणु
	.dtor = nvkm_falcon_dtor,
	.oneinit = nvkm_falcon_oneinit,
	.init = nvkm_falcon_init,
	.fini = nvkm_falcon_fini,
	.पूर्णांकr = nvkm_falcon_पूर्णांकr,
	.fअगरo.sclass = nvkm_falcon_oclass_get,
	.cclass = &nvkm_falcon_cclass,
पूर्ण;

पूर्णांक
nvkm_falcon_new_(स्थिर काष्ठा nvkm_falcon_func *func, काष्ठा nvkm_device *device,
		 क्रमागत nvkm_subdev_type type, पूर्णांक inst, bool enable, u32 addr,
		 काष्ठा nvkm_engine **pengine)
अणु
	काष्ठा nvkm_falcon *falcon;

	अगर (!(falcon = kzalloc(माप(*falcon), GFP_KERNEL)))
		वापस -ENOMEM;
	falcon->func = func;
	falcon->addr = addr;
	falcon->code.data = func->code.data;
	falcon->code.size = func->code.size;
	falcon->data.data = func->data.data;
	falcon->data.size = func->data.size;
	*pengine = &falcon->engine;

	वापस nvkm_engine_ctor(&nvkm_falcon, device, type, inst, enable, &falcon->engine);
पूर्ण
