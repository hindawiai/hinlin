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
#समावेश <core/subdev.h>
#समावेश <core/device.h>
#समावेश <core/option.h>
#समावेश <subdev/mc.h>

स्थिर अक्षर *
nvkm_subdev_type[NVKM_SUBDEV_NR] = अणु
#घोषणा NVKM_LAYOUT_ONCE(type,data,ptr,...) [type] = #ptr,
#घोषणा NVKM_LAYOUT_INST(A...) NVKM_LAYOUT_ONCE(A)
#समावेश <core/layout.h>
#अघोषित NVKM_LAYOUT_ONCE
#अघोषित NVKM_LAYOUT_INST
पूर्ण;

व्योम
nvkm_subdev_पूर्णांकr(काष्ठा nvkm_subdev *subdev)
अणु
	अगर (subdev->func->पूर्णांकr)
		subdev->func->पूर्णांकr(subdev);
पूर्ण

पूर्णांक
nvkm_subdev_info(काष्ठा nvkm_subdev *subdev, u64 mthd, u64 *data)
अणु
	अगर (subdev->func->info)
		वापस subdev->func->info(subdev, mthd, data);
	वापस -ENOSYS;
पूर्ण

पूर्णांक
nvkm_subdev_fini(काष्ठा nvkm_subdev *subdev, bool suspend)
अणु
	काष्ठा nvkm_device *device = subdev->device;
	स्थिर अक्षर *action = suspend ? "suspend" : "fini";
	s64 समय;

	nvkm_trace(subdev, "%s running...\n", action);
	समय = kसमय_प्रकारo_us(kसमय_get());

	अगर (subdev->func->fini) अणु
		पूर्णांक ret = subdev->func->fini(subdev, suspend);
		अगर (ret) अणु
			nvkm_error(subdev, "%s failed, %d\n", action, ret);
			अगर (suspend)
				वापस ret;
		पूर्ण
	पूर्ण

	nvkm_mc_reset(device, subdev->type, subdev->inst);

	समय = kसमय_प्रकारo_us(kसमय_get()) - समय;
	nvkm_trace(subdev, "%s completed in %lldus\n", action, समय);
	वापस 0;
पूर्ण

पूर्णांक
nvkm_subdev_preinit(काष्ठा nvkm_subdev *subdev)
अणु
	s64 समय;

	nvkm_trace(subdev, "preinit running...\n");
	समय = kसमय_प्रकारo_us(kसमय_get());

	अगर (subdev->func->preinit) अणु
		पूर्णांक ret = subdev->func->preinit(subdev);
		अगर (ret) अणु
			nvkm_error(subdev, "preinit failed, %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	समय = kसमय_प्रकारo_us(kसमय_get()) - समय;
	nvkm_trace(subdev, "preinit completed in %lldus\n", समय);
	वापस 0;
पूर्ण

पूर्णांक
nvkm_subdev_init(काष्ठा nvkm_subdev *subdev)
अणु
	s64 समय;
	पूर्णांक ret;

	nvkm_trace(subdev, "init running...\n");
	समय = kसमय_प्रकारo_us(kसमय_get());

	अगर (subdev->func->oneinit && !subdev->oneinit) अणु
		s64 समय;
		nvkm_trace(subdev, "one-time init running...\n");
		समय = kसमय_प्रकारo_us(kसमय_get());
		ret = subdev->func->oneinit(subdev);
		अगर (ret) अणु
			nvkm_error(subdev, "one-time init failed, %d\n", ret);
			वापस ret;
		पूर्ण

		subdev->oneinit = true;
		समय = kसमय_प्रकारo_us(kसमय_get()) - समय;
		nvkm_trace(subdev, "one-time init completed in %lldus\n", समय);
	पूर्ण

	अगर (subdev->func->init) अणु
		ret = subdev->func->init(subdev);
		अगर (ret) अणु
			nvkm_error(subdev, "init failed, %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	समय = kसमय_प्रकारo_us(kसमय_get()) - समय;
	nvkm_trace(subdev, "init completed in %lldus\n", समय);
	वापस 0;
पूर्ण

व्योम
nvkm_subdev_del(काष्ठा nvkm_subdev **psubdev)
अणु
	काष्ठा nvkm_subdev *subdev = *psubdev;
	s64 समय;

	अगर (subdev && !WARN_ON(!subdev->func)) अणु
		nvkm_trace(subdev, "destroy running...\n");
		समय = kसमय_प्रकारo_us(kसमय_get());
		list_del(&subdev->head);
		अगर (subdev->func->dtor)
			*psubdev = subdev->func->dtor(subdev);
		समय = kसमय_प्रकारo_us(kसमय_get()) - समय;
		nvkm_trace(subdev, "destroy completed in %lldus\n", समय);
		kमुक्त(*psubdev);
		*psubdev = शून्य;
	पूर्ण
पूर्ण

व्योम
nvkm_subdev_disable(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst)
अणु
	काष्ठा nvkm_subdev *subdev;
	list_क्रम_each_entry(subdev, &device->subdev, head) अणु
		अगर (subdev->type == type && subdev->inst == inst) अणु
			*subdev->pself = शून्य;
			nvkm_subdev_del(&subdev);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

व्योम
nvkm_subdev_ctor(स्थिर काष्ठा nvkm_subdev_func *func, काष्ठा nvkm_device *device,
		 क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_subdev *subdev)
अणु
	subdev->func = func;
	subdev->device = device;
	subdev->type = type;
	subdev->inst = inst < 0 ? 0 : inst;

	अगर (inst >= 0)
		snम_लिखो(subdev->name, माप(subdev->name), "%s%d", nvkm_subdev_type[type], inst);
	अन्यथा
		strscpy(subdev->name, nvkm_subdev_type[type], माप(subdev->name));
	subdev->debug = nvkm_dbgopt(device->dbgopt, subdev->name);
	list_add_tail(&subdev->head, &device->subdev);
पूर्ण

पूर्णांक
nvkm_subdev_new_(स्थिर काष्ठा nvkm_subdev_func *func, काष्ठा nvkm_device *device,
		 क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_subdev **psubdev)
अणु
	अगर (!(*psubdev = kzalloc(माप(**psubdev), GFP_KERNEL)))
		वापस -ENOMEM;
	nvkm_subdev_ctor(func, device, type, inst, *psubdev);
	वापस 0;
पूर्ण
