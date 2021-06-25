<शैली गुरु>
/*
 * Copyright 2018 Red Hat Inc.
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
#समावेश "priv.h"

#समावेश <core/memory.h>
#समावेश <core/notअगरy.h>

अटल व्योम
nvkm_fault_ntfy_fini(काष्ठा nvkm_event *event, पूर्णांक type, पूर्णांक index)
अणु
	काष्ठा nvkm_fault *fault = container_of(event, typeof(*fault), event);
	fault->func->buffer.पूर्णांकr(fault->buffer[index], false);
पूर्ण

अटल व्योम
nvkm_fault_ntfy_init(काष्ठा nvkm_event *event, पूर्णांक type, पूर्णांक index)
अणु
	काष्ठा nvkm_fault *fault = container_of(event, typeof(*fault), event);
	fault->func->buffer.पूर्णांकr(fault->buffer[index], true);
पूर्ण

अटल पूर्णांक
nvkm_fault_ntfy_ctor(काष्ठा nvkm_object *object, व्योम *argv, u32 argc,
		     काष्ठा nvkm_notअगरy *notअगरy)
अणु
	काष्ठा nvkm_fault_buffer *buffer = nvkm_fault_buffer(object);
	अगर (argc == 0) अणु
		notअगरy->size  = 0;
		notअगरy->types = 1;
		notअगरy->index = buffer->id;
		वापस 0;
	पूर्ण
	वापस -ENOSYS;
पूर्ण

अटल स्थिर काष्ठा nvkm_event_func
nvkm_fault_ntfy = अणु
	.ctor = nvkm_fault_ntfy_ctor,
	.init = nvkm_fault_ntfy_init,
	.fini = nvkm_fault_ntfy_fini,
पूर्ण;

अटल व्योम
nvkm_fault_पूर्णांकr(काष्ठा nvkm_subdev *subdev)
अणु
	काष्ठा nvkm_fault *fault = nvkm_fault(subdev);
	वापस fault->func->पूर्णांकr(fault);
पूर्ण

अटल पूर्णांक
nvkm_fault_fini(काष्ठा nvkm_subdev *subdev, bool suspend)
अणु
	काष्ठा nvkm_fault *fault = nvkm_fault(subdev);
	अगर (fault->func->fini)
		fault->func->fini(fault);
	वापस 0;
पूर्ण

अटल पूर्णांक
nvkm_fault_init(काष्ठा nvkm_subdev *subdev)
अणु
	काष्ठा nvkm_fault *fault = nvkm_fault(subdev);
	अगर (fault->func->init)
		fault->func->init(fault);
	वापस 0;
पूर्ण

अटल पूर्णांक
nvkm_fault_oneinit_buffer(काष्ठा nvkm_fault *fault, पूर्णांक id)
अणु
	काष्ठा nvkm_subdev *subdev = &fault->subdev;
	काष्ठा nvkm_device *device = subdev->device;
	काष्ठा nvkm_fault_buffer *buffer;
	पूर्णांक ret;

	अगर (!(buffer = kzalloc(माप(*buffer), GFP_KERNEL)))
		वापस -ENOMEM;
	buffer->fault = fault;
	buffer->id = id;
	fault->func->buffer.info(buffer);
	fault->buffer[id] = buffer;

	nvkm_debug(subdev, "buffer %d: %d entries\n", id, buffer->entries);

	ret = nvkm_memory_new(device, NVKM_MEM_TARGET_INST, buffer->entries *
			      fault->func->buffer.entry_size, 0x1000, true,
			      &buffer->mem);
	अगर (ret)
		वापस ret;

	/* Pin fault buffer in BAR2. */
	buffer->addr = fault->func->buffer.pin(buffer);
	अगर (buffer->addr == ~0ULL)
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक
nvkm_fault_oneinit(काष्ठा nvkm_subdev *subdev)
अणु
	काष्ठा nvkm_fault *fault = nvkm_fault(subdev);
	पूर्णांक ret, i;

	क्रम (i = 0; i < ARRAY_SIZE(fault->buffer); i++) अणु
		अगर (i < fault->func->buffer.nr) अणु
			ret = nvkm_fault_oneinit_buffer(fault, i);
			अगर (ret)
				वापस ret;
			fault->buffer_nr = i + 1;
		पूर्ण
	पूर्ण

	ret = nvkm_event_init(&nvkm_fault_ntfy, 1, fault->buffer_nr,
			      &fault->event);
	अगर (ret)
		वापस ret;

	अगर (fault->func->oneinit)
		ret = fault->func->oneinit(fault);
	वापस ret;
पूर्ण

अटल व्योम *
nvkm_fault_dtor(काष्ठा nvkm_subdev *subdev)
अणु
	काष्ठा nvkm_fault *fault = nvkm_fault(subdev);
	पूर्णांक i;

	nvkm_notअगरy_fini(&fault->nrpfb);
	nvkm_event_fini(&fault->event);

	क्रम (i = 0; i < fault->buffer_nr; i++) अणु
		अगर (fault->buffer[i]) अणु
			nvkm_memory_unref(&fault->buffer[i]->mem);
			kमुक्त(fault->buffer[i]);
		पूर्ण
	पूर्ण

	वापस fault;
पूर्ण

अटल स्थिर काष्ठा nvkm_subdev_func
nvkm_fault = अणु
	.dtor = nvkm_fault_dtor,
	.oneinit = nvkm_fault_oneinit,
	.init = nvkm_fault_init,
	.fini = nvkm_fault_fini,
	.पूर्णांकr = nvkm_fault_पूर्णांकr,
पूर्ण;

पूर्णांक
nvkm_fault_new_(स्थिर काष्ठा nvkm_fault_func *func, काष्ठा nvkm_device *device,
		क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_fault **pfault)
अणु
	काष्ठा nvkm_fault *fault;
	अगर (!(fault = *pfault = kzalloc(माप(*fault), GFP_KERNEL)))
		वापस -ENOMEM;
	nvkm_subdev_ctor(&nvkm_fault, device, type, inst, &fault->subdev);
	fault->func = func;
	fault->user.ctor = nvkm_ufault_new;
	fault->user.base = func->user.base;
	वापस 0;
पूर्ण
