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
#घोषणा nvkm_udevice(p) container_of((p), काष्ठा nvkm_udevice, object)
#समावेश "priv.h"
#समावेश "ctrl.h"

#समावेश <core/client.h>
#समावेश <subdev/fb.h>
#समावेश <subdev/insपंचांगem.h>
#समावेश <subdev/समयr.h>

#समावेश <nvअगर/class.h>
#समावेश <nvअगर/cl0080.h>
#समावेश <nvअगर/unpack.h>

काष्ठा nvkm_udevice अणु
	काष्ठा nvkm_object object;
	काष्ठा nvkm_device *device;
पूर्ण;

अटल पूर्णांक
nvkm_udevice_info_subdev(काष्ठा nvkm_device *device, u64 mthd, u64 *data)
अणु
	काष्ठा nvkm_subdev *subdev;
	क्रमागत nvkm_subdev_type type;

	चयन (mthd & NV_DEVICE_INFO_UNIT) अणु
	हाल NV_DEVICE_HOST(0): type = NVKM_ENGINE_FIFO; अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	subdev = nvkm_device_subdev(device, type, 0);
	अगर (subdev)
		वापस nvkm_subdev_info(subdev, mthd, data);
	वापस -ENODEV;
पूर्ण

अटल व्योम
nvkm_udevice_info_v1(काष्ठा nvkm_device *device,
		     काष्ठा nv_device_info_v1_data *args)
अणु
	अगर (args->mthd & NV_DEVICE_INFO_UNIT) अणु
		अगर (nvkm_udevice_info_subdev(device, args->mthd, &args->data))
			args->mthd = NV_DEVICE_INFO_INVALID;
		वापस;
	पूर्ण
	args->mthd = NV_DEVICE_INFO_INVALID;
पूर्ण

अटल पूर्णांक
nvkm_udevice_info(काष्ठा nvkm_udevice *udev, व्योम *data, u32 size)
अणु
	काष्ठा nvkm_object *object = &udev->object;
	काष्ठा nvkm_device *device = udev->device;
	काष्ठा nvkm_fb *fb = device->fb;
	काष्ठा nvkm_insपंचांगem *imem = device->imem;
	जोड़ अणु
		काष्ठा nv_device_info_v0 v0;
		काष्ठा nv_device_info_v1 v1;
	पूर्ण *args = data;
	पूर्णांक ret = -ENOSYS, i;

	nvअगर_ioctl(object, "device info size %d\n", size);
	अगर (!(ret = nvअगर_unpack(ret, &data, &size, args->v1, 1, 1, true))) अणु
		nvअगर_ioctl(object, "device info vers %d count %d\n",
			   args->v1.version, args->v1.count);
		अगर (args->v1.count * माप(args->v1.data[0]) == size) अणु
			क्रम (i = 0; i < args->v1.count; i++)
				nvkm_udevice_info_v1(device, &args->v1.data[i]);
			वापस 0;
		पूर्ण
		वापस -EINVAL;
	पूर्ण अन्यथा
	अगर (!(ret = nvअगर_unpack(ret, &data, &size, args->v0, 0, 0, false))) अणु
		nvअगर_ioctl(object, "device info vers %d\n", args->v0.version);
	पूर्ण अन्यथा
		वापस ret;

	चयन (device->chipset) अणु
	हाल 0x01a:
	हाल 0x01f:
	हाल 0x04c:
	हाल 0x04e:
	हाल 0x063:
	हाल 0x067:
	हाल 0x068:
	हाल 0x0aa:
	हाल 0x0ac:
	हाल 0x0af:
		args->v0.platक्रमm = NV_DEVICE_INFO_V0_IGP;
		अवरोध;
	शेष:
		चयन (device->type) अणु
		हाल NVKM_DEVICE_PCI:
			args->v0.platक्रमm = NV_DEVICE_INFO_V0_PCI;
			अवरोध;
		हाल NVKM_DEVICE_AGP:
			args->v0.platक्रमm = NV_DEVICE_INFO_V0_AGP;
			अवरोध;
		हाल NVKM_DEVICE_PCIE:
			args->v0.platक्रमm = NV_DEVICE_INFO_V0_PCIE;
			अवरोध;
		हाल NVKM_DEVICE_TEGRA:
			args->v0.platक्रमm = NV_DEVICE_INFO_V0_SOC;
			अवरोध;
		शेष:
			WARN_ON(1);
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण

	चयन (device->card_type) अणु
	हाल NV_04: args->v0.family = NV_DEVICE_INFO_V0_TNT; अवरोध;
	हाल NV_10:
	हाल NV_11: args->v0.family = NV_DEVICE_INFO_V0_CELSIUS; अवरोध;
	हाल NV_20: args->v0.family = NV_DEVICE_INFO_V0_KELVIN; अवरोध;
	हाल NV_30: args->v0.family = NV_DEVICE_INFO_V0_RANKINE; अवरोध;
	हाल NV_40: args->v0.family = NV_DEVICE_INFO_V0_CURIE; अवरोध;
	हाल NV_50: args->v0.family = NV_DEVICE_INFO_V0_TESLA; अवरोध;
	हाल NV_C0: args->v0.family = NV_DEVICE_INFO_V0_FERMI; अवरोध;
	हाल NV_E0: args->v0.family = NV_DEVICE_INFO_V0_KEPLER; अवरोध;
	हाल GM100: args->v0.family = NV_DEVICE_INFO_V0_MAXWELL; अवरोध;
	हाल GP100: args->v0.family = NV_DEVICE_INFO_V0_PASCAL; अवरोध;
	हाल GV100: args->v0.family = NV_DEVICE_INFO_V0_VOLTA; अवरोध;
	हाल TU100: args->v0.family = NV_DEVICE_INFO_V0_TURING; अवरोध;
	हाल GA100: args->v0.family = NV_DEVICE_INFO_V0_AMPERE; अवरोध;
	शेष:
		args->v0.family = 0;
		अवरोध;
	पूर्ण

	args->v0.chipset  = device->chipset;
	args->v0.revision = device->chiprev;
	अगर (fb && fb->ram)
		args->v0.ram_size = args->v0.ram_user = fb->ram->size;
	अन्यथा
		args->v0.ram_size = args->v0.ram_user = 0;
	अगर (imem && args->v0.ram_size > 0)
		args->v0.ram_user = args->v0.ram_user - imem->reserved;

	म_नकलन(args->v0.chip, device->chip->name, माप(args->v0.chip));
	म_नकलन(args->v0.name, device->name, माप(args->v0.name));
	वापस 0;
पूर्ण

अटल पूर्णांक
nvkm_udevice_समय(काष्ठा nvkm_udevice *udev, व्योम *data, u32 size)
अणु
	काष्ठा nvkm_object *object = &udev->object;
	काष्ठा nvkm_device *device = udev->device;
	जोड़ अणु
		काष्ठा nv_device_समय_v0 v0;
	पूर्ण *args = data;
	पूर्णांक ret = -ENOSYS;

	nvअगर_ioctl(object, "device time size %d\n", size);
	अगर (!(ret = nvअगर_unpack(ret, &data, &size, args->v0, 0, 0, false))) अणु
		nvअगर_ioctl(object, "device time vers %d\n", args->v0.version);
		args->v0.समय = nvkm_समयr_पढ़ो(device->समयr);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक
nvkm_udevice_mthd(काष्ठा nvkm_object *object, u32 mthd, व्योम *data, u32 size)
अणु
	काष्ठा nvkm_udevice *udev = nvkm_udevice(object);
	nvअगर_ioctl(object, "device mthd %08x\n", mthd);
	चयन (mthd) अणु
	हाल NV_DEVICE_V0_INFO:
		वापस nvkm_udevice_info(udev, data, size);
	हाल NV_DEVICE_V0_TIME:
		वापस nvkm_udevice_समय(udev, data, size);
	शेष:
		अवरोध;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक
nvkm_udevice_rd08(काष्ठा nvkm_object *object, u64 addr, u8 *data)
अणु
	काष्ठा nvkm_udevice *udev = nvkm_udevice(object);
	*data = nvkm_rd08(udev->device, addr);
	वापस 0;
पूर्ण

अटल पूर्णांक
nvkm_udevice_rd16(काष्ठा nvkm_object *object, u64 addr, u16 *data)
अणु
	काष्ठा nvkm_udevice *udev = nvkm_udevice(object);
	*data = nvkm_rd16(udev->device, addr);
	वापस 0;
पूर्ण

अटल पूर्णांक
nvkm_udevice_rd32(काष्ठा nvkm_object *object, u64 addr, u32 *data)
अणु
	काष्ठा nvkm_udevice *udev = nvkm_udevice(object);
	*data = nvkm_rd32(udev->device, addr);
	वापस 0;
पूर्ण

अटल पूर्णांक
nvkm_udevice_wr08(काष्ठा nvkm_object *object, u64 addr, u8 data)
अणु
	काष्ठा nvkm_udevice *udev = nvkm_udevice(object);
	nvkm_wr08(udev->device, addr, data);
	वापस 0;
पूर्ण

अटल पूर्णांक
nvkm_udevice_wr16(काष्ठा nvkm_object *object, u64 addr, u16 data)
अणु
	काष्ठा nvkm_udevice *udev = nvkm_udevice(object);
	nvkm_wr16(udev->device, addr, data);
	वापस 0;
पूर्ण

अटल पूर्णांक
nvkm_udevice_wr32(काष्ठा nvkm_object *object, u64 addr, u32 data)
अणु
	काष्ठा nvkm_udevice *udev = nvkm_udevice(object);
	nvkm_wr32(udev->device, addr, data);
	वापस 0;
पूर्ण

अटल पूर्णांक
nvkm_udevice_map(काष्ठा nvkm_object *object, व्योम *argv, u32 argc,
		 क्रमागत nvkm_object_map *type, u64 *addr, u64 *size)
अणु
	काष्ठा nvkm_udevice *udev = nvkm_udevice(object);
	काष्ठा nvkm_device *device = udev->device;
	*type = NVKM_OBJECT_MAP_IO;
	*addr = device->func->resource_addr(device, 0);
	*size = device->func->resource_size(device, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक
nvkm_udevice_fini(काष्ठा nvkm_object *object, bool suspend)
अणु
	काष्ठा nvkm_udevice *udev = nvkm_udevice(object);
	काष्ठा nvkm_device *device = udev->device;
	पूर्णांक ret = 0;

	mutex_lock(&device->mutex);
	अगर (!--device->refcount) अणु
		ret = nvkm_device_fini(device, suspend);
		अगर (ret && suspend) अणु
			device->refcount++;
			जाओ करोne;
		पूर्ण
	पूर्ण

करोne:
	mutex_unlock(&device->mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक
nvkm_udevice_init(काष्ठा nvkm_object *object)
अणु
	काष्ठा nvkm_udevice *udev = nvkm_udevice(object);
	काष्ठा nvkm_device *device = udev->device;
	पूर्णांक ret = 0;

	mutex_lock(&device->mutex);
	अगर (!device->refcount++) अणु
		ret = nvkm_device_init(device);
		अगर (ret) अणु
			device->refcount--;
			जाओ करोne;
		पूर्ण
	पूर्ण

करोne:
	mutex_unlock(&device->mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक
nvkm_udevice_child_new(स्थिर काष्ठा nvkm_oclass *oclass,
		       व्योम *data, u32 size, काष्ठा nvkm_object **pobject)
अणु
	काष्ठा nvkm_udevice *udev = nvkm_udevice(oclass->parent);
	स्थिर काष्ठा nvkm_device_oclass *sclass = oclass->priv;
	वापस sclass->ctor(udev->device, oclass, data, size, pobject);
पूर्ण

अटल पूर्णांक
nvkm_udevice_child_get(काष्ठा nvkm_object *object, पूर्णांक index,
		       काष्ठा nvkm_oclass *oclass)
अणु
	काष्ठा nvkm_udevice *udev = nvkm_udevice(object);
	काष्ठा nvkm_device *device = udev->device;
	काष्ठा nvkm_engine *engine;
	u64 mask = (1ULL << NVKM_ENGINE_DMAOBJ) |
		   (1ULL << NVKM_ENGINE_FIFO) |
		   (1ULL << NVKM_ENGINE_DISP) |
		   (1ULL << NVKM_ENGINE_PM);
	स्थिर काष्ठा nvkm_device_oclass *sclass = शून्य;
	पूर्णांक i;

	क्रम (; i = __ffs64(mask), mask && !sclass; mask &= ~(1ULL << i)) अणु
		अगर (!(engine = nvkm_device_engine(device, i, 0)) ||
		    !(engine->func->base.sclass))
			जारी;
		oclass->engine = engine;

		index -= engine->func->base.sclass(oclass, index, &sclass);
	पूर्ण

	अगर (!sclass) अणु
		अगर (index-- == 0)
			sclass = &nvkm_control_oclass;
		अन्यथा अगर (device->mmu && index-- == 0)
			sclass = &device->mmu->user;
		अन्यथा अगर (device->fault && index-- == 0)
			sclass = &device->fault->user;
		अन्यथा
			वापस -EINVAL;

		oclass->base = sclass->base;
	पूर्ण

	oclass->ctor = nvkm_udevice_child_new;
	oclass->priv = sclass;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nvkm_object_func
nvkm_udevice_super = अणु
	.init = nvkm_udevice_init,
	.fini = nvkm_udevice_fini,
	.mthd = nvkm_udevice_mthd,
	.map = nvkm_udevice_map,
	.rd08 = nvkm_udevice_rd08,
	.rd16 = nvkm_udevice_rd16,
	.rd32 = nvkm_udevice_rd32,
	.wr08 = nvkm_udevice_wr08,
	.wr16 = nvkm_udevice_wr16,
	.wr32 = nvkm_udevice_wr32,
	.sclass = nvkm_udevice_child_get,
पूर्ण;

अटल स्थिर काष्ठा nvkm_object_func
nvkm_udevice = अणु
	.init = nvkm_udevice_init,
	.fini = nvkm_udevice_fini,
	.mthd = nvkm_udevice_mthd,
	.sclass = nvkm_udevice_child_get,
पूर्ण;

अटल पूर्णांक
nvkm_udevice_new(स्थिर काष्ठा nvkm_oclass *oclass, व्योम *data, u32 size,
		 काष्ठा nvkm_object **pobject)
अणु
	जोड़ अणु
		काष्ठा nv_device_v0 v0;
	पूर्ण *args = data;
	काष्ठा nvkm_client *client = oclass->client;
	काष्ठा nvkm_object *parent = &client->object;
	स्थिर काष्ठा nvkm_object_func *func;
	काष्ठा nvkm_udevice *udev;
	पूर्णांक ret = -ENOSYS;

	nvअगर_ioctl(parent, "create device size %d\n", size);
	अगर (!(ret = nvअगर_unpack(ret, &data, &size, args->v0, 0, 0, false))) अणु
		nvअगर_ioctl(parent, "create device v%d device %016llx\n",
			   args->v0.version, args->v0.device);
	पूर्ण अन्यथा
		वापस ret;

	/* give priviledged clients रेजिस्टर access */
	अगर (client->super)
		func = &nvkm_udevice_super;
	अन्यथा
		func = &nvkm_udevice;

	अगर (!(udev = kzalloc(माप(*udev), GFP_KERNEL)))
		वापस -ENOMEM;
	nvkm_object_ctor(func, oclass, &udev->object);
	*pobject = &udev->object;

	/* find the device that matches what the client requested */
	अगर (args->v0.device != ~0)
		udev->device = nvkm_device_find(args->v0.device);
	अन्यथा
		udev->device = nvkm_device_find(client->device);
	अगर (!udev->device)
		वापस -ENODEV;

	वापस 0;
पूर्ण

स्थिर काष्ठा nvkm_sclass
nvkm_udevice_sclass = अणु
	.oclass = NV_DEVICE,
	.minver = 0,
	.maxver = 0,
	.ctor = nvkm_udevice_new,
पूर्ण;
