<शैली गुरु>
/*
 * Copyright 2016 Red Hat Inc.
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
 * Authors: Ben Skeggs <bskeggs@redhat.com>
 */
#समावेश "priv.h"

काष्ठा nvkm_top_device *
nvkm_top_device_new(काष्ठा nvkm_top *top)
अणु
	काष्ठा nvkm_top_device *info = kदो_स्मृति(माप(*info), GFP_KERNEL);
	अगर (info) अणु
		info->type = NVKM_SUBDEV_NR;
		info->inst = -1;
		info->addr = 0;
		info->fault = -1;
		info->engine = -1;
		info->runlist = -1;
		info->reset = -1;
		info->पूर्णांकr = -1;
		list_add_tail(&info->head, &top->device);
	पूर्ण
	वापस info;
पूर्ण

u32
nvkm_top_addr(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst)
अणु
	काष्ठा nvkm_top *top = device->top;
	काष्ठा nvkm_top_device *info;

	अगर (top) अणु
		list_क्रम_each_entry(info, &top->device, head) अणु
			अगर (info->type == type && info->inst == inst)
				वापस info->addr;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

u32
nvkm_top_reset(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst)
अणु
	काष्ठा nvkm_top *top = device->top;
	काष्ठा nvkm_top_device *info;

	अगर (top) अणु
		list_क्रम_each_entry(info, &top->device, head) अणु
			अगर (info->type == type && info->inst == inst && info->reset >= 0)
				वापस BIT(info->reset);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

u32
nvkm_top_पूर्णांकr_mask(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst)
अणु
	काष्ठा nvkm_top *top = device->top;
	काष्ठा nvkm_top_device *info;

	अगर (top) अणु
		list_क्रम_each_entry(info, &top->device, head) अणु
			अगर (info->type == type && info->inst == inst && info->पूर्णांकr >= 0)
				वापस BIT(info->पूर्णांकr);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक
nvkm_top_fault_id(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst)
अणु
	काष्ठा nvkm_top *top = device->top;
	काष्ठा nvkm_top_device *info;

	list_क्रम_each_entry(info, &top->device, head) अणु
		अगर (info->type == type && info->inst == inst && info->fault >= 0)
			वापस info->fault;
	पूर्ण

	वापस -ENOENT;
पूर्ण

काष्ठा nvkm_subdev *
nvkm_top_fault(काष्ठा nvkm_device *device, पूर्णांक fault)
अणु
	काष्ठा nvkm_top *top = device->top;
	काष्ठा nvkm_top_device *info;

	list_क्रम_each_entry(info, &top->device, head) अणु
		अगर (info->fault == fault)
			वापस nvkm_device_subdev(device, info->type, info->inst);
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक
nvkm_top_oneinit(काष्ठा nvkm_subdev *subdev)
अणु
	काष्ठा nvkm_top *top = nvkm_top(subdev);
	वापस top->func->oneinit(top);
पूर्ण

अटल व्योम *
nvkm_top_dtor(काष्ठा nvkm_subdev *subdev)
अणु
	काष्ठा nvkm_top *top = nvkm_top(subdev);
	काष्ठा nvkm_top_device *info, *temp;

	list_क्रम_each_entry_safe(info, temp, &top->device, head) अणु
		list_del(&info->head);
		kमुक्त(info);
	पूर्ण

	वापस top;
पूर्ण

अटल स्थिर काष्ठा nvkm_subdev_func
nvkm_top = अणु
	.dtor = nvkm_top_dtor,
	.oneinit = nvkm_top_oneinit,
पूर्ण;

पूर्णांक
nvkm_top_new_(स्थिर काष्ठा nvkm_top_func *func, काष्ठा nvkm_device *device,
	      क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_top **ptop)
अणु
	काष्ठा nvkm_top *top;
	अगर (!(top = *ptop = kzalloc(माप(*top), GFP_KERNEL)))
		वापस -ENOMEM;
	nvkm_subdev_ctor(&nvkm_top, device, type, inst, &top->subdev);
	top->func = func;
	INIT_LIST_HEAD(&top->device);
	वापस 0;
पूर्ण
