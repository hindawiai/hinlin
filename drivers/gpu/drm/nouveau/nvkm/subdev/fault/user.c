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
#समावेश <subdev/mmu.h>

#समावेश <nvअगर/clb069.h>
#समावेश <nvअगर/unpack.h>

अटल पूर्णांक
nvkm_ufault_map(काष्ठा nvkm_object *object, व्योम *argv, u32 argc,
		क्रमागत nvkm_object_map *type, u64 *addr, u64 *size)
अणु
	काष्ठा nvkm_fault_buffer *buffer = nvkm_fault_buffer(object);
	काष्ठा nvkm_device *device = buffer->fault->subdev.device;
	*type = NVKM_OBJECT_MAP_IO;
	*addr = device->func->resource_addr(device, 3) + buffer->addr;
	*size = nvkm_memory_size(buffer->mem);
	वापस 0;
पूर्ण

अटल पूर्णांक
nvkm_ufault_ntfy(काष्ठा nvkm_object *object, u32 type,
		 काष्ठा nvkm_event **pevent)
अणु
	काष्ठा nvkm_fault_buffer *buffer = nvkm_fault_buffer(object);
	अगर (type == NVB069_V0_NTFY_FAULT) अणु
		*pevent = &buffer->fault->event;
		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक
nvkm_ufault_fini(काष्ठा nvkm_object *object, bool suspend)
अणु
	काष्ठा nvkm_fault_buffer *buffer = nvkm_fault_buffer(object);
	buffer->fault->func->buffer.fini(buffer);
	वापस 0;
पूर्ण

अटल पूर्णांक
nvkm_ufault_init(काष्ठा nvkm_object *object)
अणु
	काष्ठा nvkm_fault_buffer *buffer = nvkm_fault_buffer(object);
	buffer->fault->func->buffer.init(buffer);
	वापस 0;
पूर्ण

अटल व्योम *
nvkm_ufault_dtor(काष्ठा nvkm_object *object)
अणु
	वापस शून्य;
पूर्ण

अटल स्थिर काष्ठा nvkm_object_func
nvkm_ufault = अणु
	.dtor = nvkm_ufault_dtor,
	.init = nvkm_ufault_init,
	.fini = nvkm_ufault_fini,
	.ntfy = nvkm_ufault_ntfy,
	.map = nvkm_ufault_map,
पूर्ण;

पूर्णांक
nvkm_ufault_new(काष्ठा nvkm_device *device, स्थिर काष्ठा nvkm_oclass *oclass,
		व्योम *argv, u32 argc, काष्ठा nvkm_object **pobject)
अणु
	जोड़ अणु
		काष्ठा nvअगर_clb069_v0 v0;
	पूर्ण *args = argv;
	काष्ठा nvkm_fault *fault = device->fault;
	काष्ठा nvkm_fault_buffer *buffer = fault->buffer[fault->func->user.rp];
	पूर्णांक ret = -ENOSYS;

	अगर (!(ret = nvअगर_unpack(ret, &argv, &argc, args->v0, 0, 0, false))) अणु
		args->v0.entries = buffer->entries;
		args->v0.get = buffer->get;
		args->v0.put = buffer->put;
	पूर्ण अन्यथा
		वापस ret;

	nvkm_object_ctor(&nvkm_ufault, oclass, &buffer->object);
	*pobject = &buffer->object;
	वापस 0;
पूर्ण
