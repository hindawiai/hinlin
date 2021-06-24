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
 *
 * Authors: Ben Skeggs
 */
#समावेश "priv.h"

#समावेश <core/gpuobj.h>
#समावेश <core/object.h>
#समावेश <subdev/समयr.h>

#समावेश <nvअगर/class.h>

/*******************************************************************************
 * PMPEG context
 ******************************************************************************/

अटल पूर्णांक
nv50_mpeg_cclass_bind(काष्ठा nvkm_object *object, काष्ठा nvkm_gpuobj *parent,
		      पूर्णांक align, काष्ठा nvkm_gpuobj **pgpuobj)
अणु
	पूर्णांक ret = nvkm_gpuobj_new(object->engine->subdev.device, 128 * 4,
				  align, true, parent, pgpuobj);
	अगर (ret == 0) अणु
		nvkm_kmap(*pgpuobj);
		nvkm_wo32(*pgpuobj, 0x70, 0x00801ec1);
		nvkm_wo32(*pgpuobj, 0x7c, 0x0000037c);
		nvkm_करोne(*pgpuobj);
	पूर्ण
	वापस ret;
पूर्ण

स्थिर काष्ठा nvkm_object_func
nv50_mpeg_cclass = अणु
	.bind = nv50_mpeg_cclass_bind,
पूर्ण;

/*******************************************************************************
 * PMPEG engine/subdev functions
 ******************************************************************************/

व्योम
nv50_mpeg_पूर्णांकr(काष्ठा nvkm_engine *mpeg)
अणु
	काष्ठा nvkm_subdev *subdev = &mpeg->subdev;
	काष्ठा nvkm_device *device = subdev->device;
	u32 stat = nvkm_rd32(device, 0x00b100);
	u32 type = nvkm_rd32(device, 0x00b230);
	u32 mthd = nvkm_rd32(device, 0x00b234);
	u32 data = nvkm_rd32(device, 0x00b238);
	u32 show = stat;

	अगर (stat & 0x01000000) अणु
		/* happens on initial binding of the object */
		अगर (type == 0x00000020 && mthd == 0x0000) अणु
			nvkm_wr32(device, 0x00b308, 0x00000100);
			show &= ~0x01000000;
		पूर्ण
	पूर्ण

	अगर (show) अणु
		nvkm_info(subdev, "%08x %08x %08x %08x\n",
			  stat, type, mthd, data);
	पूर्ण

	nvkm_wr32(device, 0x00b100, stat);
	nvkm_wr32(device, 0x00b230, 0x00000001);
पूर्ण

पूर्णांक
nv50_mpeg_init(काष्ठा nvkm_engine *mpeg)
अणु
	काष्ठा nvkm_subdev *subdev = &mpeg->subdev;
	काष्ठा nvkm_device *device = subdev->device;

	nvkm_wr32(device, 0x00b32c, 0x00000000);
	nvkm_wr32(device, 0x00b314, 0x00000100);
	nvkm_wr32(device, 0x00b0e0, 0x0000001a);

	nvkm_wr32(device, 0x00b220, 0x00000044);
	nvkm_wr32(device, 0x00b300, 0x00801ec1);
	nvkm_wr32(device, 0x00b390, 0x00000000);
	nvkm_wr32(device, 0x00b394, 0x00000000);
	nvkm_wr32(device, 0x00b398, 0x00000000);
	nvkm_mask(device, 0x00b32c, 0x00000001, 0x00000001);

	nvkm_wr32(device, 0x00b100, 0xffffffff);
	nvkm_wr32(device, 0x00b140, 0xffffffff);

	अगर (nvkm_msec(device, 2000,
		अगर (!(nvkm_rd32(device, 0x00b200) & 0x00000001))
			अवरोध;
	) < 0) अणु
		nvkm_error(subdev, "timeout %08x\n",
			   nvkm_rd32(device, 0x00b200));
		वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nvkm_engine_func
nv50_mpeg = अणु
	.init = nv50_mpeg_init,
	.पूर्णांकr = nv50_mpeg_पूर्णांकr,
	.cclass = &nv50_mpeg_cclass,
	.sclass = अणु
		अणु -1, -1, NV31_MPEG, &nv31_mpeg_object पूर्ण,
		अणुपूर्ण
	पूर्ण
पूर्ण;

पूर्णांक
nv50_mpeg_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
	      काष्ठा nvkm_engine **pmpeg)
अणु
	वापस nvkm_engine_new_(&nv50_mpeg, device, type, inst, true, pmpeg);
पूर्ण
