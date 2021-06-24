<शैली गुरु>
/*
 * Copyright 2013 Ilia Mirkin
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
#समावेश <engine/xtensa.h>

#समावेश <core/gpuobj.h>
#समावेश <engine/fअगरo.h>

अटल पूर्णांक
nvkm_xtensa_oclass_get(काष्ठा nvkm_oclass *oclass, पूर्णांक index)
अणु
	काष्ठा nvkm_xtensa *xtensa = nvkm_xtensa(oclass->engine);
	पूर्णांक c = 0;

	जबतक (xtensa->func->sclass[c].oclass) अणु
		अगर (c++ == index) अणु
			oclass->base = xtensa->func->sclass[index];
			वापस index;
		पूर्ण
	पूर्ण

	वापस c;
पूर्ण

अटल पूर्णांक
nvkm_xtensa_cclass_bind(काष्ठा nvkm_object *object, काष्ठा nvkm_gpuobj *parent,
			पूर्णांक align, काष्ठा nvkm_gpuobj **pgpuobj)
अणु
	वापस nvkm_gpuobj_new(object->engine->subdev.device, 0x10000, align,
			       true, parent, pgpuobj);
पूर्ण

अटल स्थिर काष्ठा nvkm_object_func
nvkm_xtensa_cclass = अणु
	.bind = nvkm_xtensa_cclass_bind,
पूर्ण;

अटल व्योम
nvkm_xtensa_पूर्णांकr(काष्ठा nvkm_engine *engine)
अणु
	काष्ठा nvkm_xtensa *xtensa = nvkm_xtensa(engine);
	काष्ठा nvkm_subdev *subdev = &xtensa->engine.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	स्थिर u32 base = xtensa->addr;
	u32 unk104 = nvkm_rd32(device, base + 0xd04);
	u32 पूर्णांकr = nvkm_rd32(device, base + 0xc20);
	u32 chan = nvkm_rd32(device, base + 0xc28);
	u32 unk10c = nvkm_rd32(device, base + 0xd0c);

	अगर (पूर्णांकr & 0x10)
		nvkm_warn(subdev, "Watchdog interrupt, engine hung.\n");
	nvkm_wr32(device, base + 0xc20, पूर्णांकr);
	पूर्णांकr = nvkm_rd32(device, base + 0xc20);
	अगर (unk104 == 0x10001 && unk10c == 0x200 && chan && !पूर्णांकr) अणु
		nvkm_debug(subdev, "Enabling FIFO_CTRL\n");
		nvkm_mask(device, xtensa->addr + 0xd94, 0, xtensa->func->fअगरo_val);
	पूर्ण
पूर्ण

अटल पूर्णांक
nvkm_xtensa_fini(काष्ठा nvkm_engine *engine, bool suspend)
अणु
	काष्ठा nvkm_xtensa *xtensa = nvkm_xtensa(engine);
	काष्ठा nvkm_device *device = xtensa->engine.subdev.device;
	स्थिर u32 base = xtensa->addr;

	nvkm_wr32(device, base + 0xd84, 0); /* INTR_EN */
	nvkm_wr32(device, base + 0xd94, 0); /* FIFO_CTRL */

	अगर (!suspend)
		nvkm_memory_unref(&xtensa->gpu_fw);
	वापस 0;
पूर्ण

अटल पूर्णांक
nvkm_xtensa_init(काष्ठा nvkm_engine *engine)
अणु
	काष्ठा nvkm_xtensa *xtensa = nvkm_xtensa(engine);
	काष्ठा nvkm_subdev *subdev = &xtensa->engine.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	स्थिर u32 base = xtensa->addr;
	स्थिर काष्ठा firmware *fw;
	अक्षर name[32];
	पूर्णांक i, ret;
	u64 addr, size;
	u32 पंचांगp;

	अगर (!xtensa->gpu_fw) अणु
		snम_लिखो(name, माप(name), "nouveau/nv84_xuc%03x",
			 xtensa->addr >> 12);

		ret = request_firmware(&fw, name, device->dev);
		अगर (ret) अणु
			nvkm_warn(subdev, "unable to load firmware %s\n", name);
			वापस ret;
		पूर्ण

		अगर (fw->size > 0x40000) अणु
			nvkm_warn(subdev, "firmware %s too large\n", name);
			release_firmware(fw);
			वापस -EINVAL;
		पूर्ण

		ret = nvkm_memory_new(device, NVKM_MEM_TARGET_INST,
				      0x40000, 0x1000, false,
				      &xtensa->gpu_fw);
		अगर (ret) अणु
			release_firmware(fw);
			वापस ret;
		पूर्ण

		nvkm_kmap(xtensa->gpu_fw);
		क्रम (i = 0; i < fw->size / 4; i++)
			nvkm_wo32(xtensa->gpu_fw, i * 4, *((u32 *)fw->data + i));
		nvkm_करोne(xtensa->gpu_fw);
		release_firmware(fw);
	पूर्ण

	addr = nvkm_memory_addr(xtensa->gpu_fw);
	size = nvkm_memory_size(xtensa->gpu_fw);

	nvkm_wr32(device, base + 0xd10, 0x1fffffff); /* ?? */
	nvkm_wr32(device, base + 0xd08, 0x0fffffff); /* ?? */

	nvkm_wr32(device, base + 0xd28, xtensa->func->unkd28); /* ?? */
	nvkm_wr32(device, base + 0xc20, 0x3f); /* INTR */
	nvkm_wr32(device, base + 0xd84, 0x3f); /* INTR_EN */

	nvkm_wr32(device, base + 0xcc0, addr >> 8); /* XT_REGION_BASE */
	nvkm_wr32(device, base + 0xcc4, 0x1c); /* XT_REGION_SETUP */
	nvkm_wr32(device, base + 0xcc8, size >> 8); /* XT_REGION_LIMIT */

	पंचांगp = nvkm_rd32(device, 0x0);
	nvkm_wr32(device, base + 0xde0, पंचांगp); /* SCRATCH_H2X */

	nvkm_wr32(device, base + 0xce8, 0xf); /* XT_REGION_SETUP */

	nvkm_wr32(device, base + 0xc20, 0x3f); /* INTR */
	nvkm_wr32(device, base + 0xd84, 0x3f); /* INTR_EN */
	वापस 0;
पूर्ण

अटल व्योम *
nvkm_xtensa_dtor(काष्ठा nvkm_engine *engine)
अणु
	वापस nvkm_xtensa(engine);
पूर्ण

अटल स्थिर काष्ठा nvkm_engine_func
nvkm_xtensa = अणु
	.dtor = nvkm_xtensa_dtor,
	.init = nvkm_xtensa_init,
	.fini = nvkm_xtensa_fini,
	.पूर्णांकr = nvkm_xtensa_पूर्णांकr,
	.fअगरo.sclass = nvkm_xtensa_oclass_get,
	.cclass = &nvkm_xtensa_cclass,
पूर्ण;

पूर्णांक
nvkm_xtensa_new_(स्थिर काष्ठा nvkm_xtensa_func *func, काष्ठा nvkm_device *device,
		 क्रमागत nvkm_subdev_type type, पूर्णांक inst, bool enable, u32 addr,
		 काष्ठा nvkm_engine **pengine)
अणु
	काष्ठा nvkm_xtensa *xtensa;

	अगर (!(xtensa = kzalloc(माप(*xtensa), GFP_KERNEL)))
		वापस -ENOMEM;
	xtensa->func = func;
	xtensa->addr = addr;
	*pengine = &xtensa->engine;

	वापस nvkm_engine_ctor(&nvkm_xtensa, device, type, inst, enable, &xtensa->engine);
पूर्ण
