<शैली गुरु>
/*
 * Copyright 2017 Red Hat Inc.
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
#समावेश "ummu.h"
#समावेश "umem.h"
#समावेश "uvmm.h"

#समावेश <core/client.h>

#समावेश <nvअगर/अगर0008.h>
#समावेश <nvअगर/unpack.h>

अटल पूर्णांक
nvkm_ummu_sclass(काष्ठा nvkm_object *object, पूर्णांक index,
		 काष्ठा nvkm_oclass *oclass)
अणु
	काष्ठा nvkm_mmu *mmu = nvkm_ummu(object)->mmu;

	अगर (mmu->func->mem.user.oclass && oclass->client->super) अणु
		अगर (index-- == 0) अणु
			oclass->base = mmu->func->mem.user;
			oclass->ctor = nvkm_umem_new;
			वापस 0;
		पूर्ण
	पूर्ण

	अगर (mmu->func->vmm.user.oclass) अणु
		अगर (index-- == 0) अणु
			oclass->base = mmu->func->vmm.user;
			oclass->ctor = nvkm_uvmm_new;
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक
nvkm_ummu_heap(काष्ठा nvkm_ummu *ummu, व्योम *argv, u32 argc)
अणु
	काष्ठा nvkm_mmu *mmu = ummu->mmu;
	जोड़ अणु
		काष्ठा nvअगर_mmu_heap_v0 v0;
	पूर्ण *args = argv;
	पूर्णांक ret = -ENOSYS;
	u8 index;

	अगर (!(ret = nvअगर_unpack(ret, &argv, &argc, args->v0, 0, 0, false))) अणु
		अगर ((index = args->v0.index) >= mmu->heap_nr)
			वापस -EINVAL;
		args->v0.size = mmu->heap[index].size;
	पूर्ण अन्यथा
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक
nvkm_ummu_type(काष्ठा nvkm_ummu *ummu, व्योम *argv, u32 argc)
अणु
	काष्ठा nvkm_mmu *mmu = ummu->mmu;
	जोड़ अणु
		काष्ठा nvअगर_mmu_type_v0 v0;
	पूर्ण *args = argv;
	पूर्णांक ret = -ENOSYS;
	u8 type, index;

	अगर (!(ret = nvअगर_unpack(ret, &argv, &argc, args->v0, 0, 0, false))) अणु
		अगर ((index = args->v0.index) >= mmu->type_nr)
			वापस -EINVAL;
		type = mmu->type[index].type;
		args->v0.heap = mmu->type[index].heap;
		args->v0.vram = !!(type & NVKM_MEM_VRAM);
		args->v0.host = !!(type & NVKM_MEM_HOST);
		args->v0.comp = !!(type & NVKM_MEM_COMP);
		args->v0.disp = !!(type & NVKM_MEM_DISP);
		args->v0.kind = !!(type & NVKM_MEM_KIND);
		args->v0.mappable = !!(type & NVKM_MEM_MAPPABLE);
		args->v0.coherent = !!(type & NVKM_MEM_COHERENT);
		args->v0.uncached = !!(type & NVKM_MEM_UNCACHED);
	पूर्ण अन्यथा
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक
nvkm_ummu_kind(काष्ठा nvkm_ummu *ummu, व्योम *argv, u32 argc)
अणु
	काष्ठा nvkm_mmu *mmu = ummu->mmu;
	जोड़ अणु
		काष्ठा nvअगर_mmu_kind_v0 v0;
	पूर्ण *args = argv;
	स्थिर u8 *kind = शून्य;
	पूर्णांक ret = -ENOSYS, count = 0;
	u8 kind_inv = 0;

	अगर (mmu->func->kind)
		kind = mmu->func->kind(mmu, &count, &kind_inv);

	अगर (!(ret = nvअगर_unpack(ret, &argv, &argc, args->v0, 0, 0, true))) अणु
		अगर (argc != args->v0.count * माप(*args->v0.data))
			वापस -EINVAL;
		अगर (args->v0.count > count)
			वापस -EINVAL;
		args->v0.kind_inv = kind_inv;
		स_नकल(args->v0.data, kind, args->v0.count);
	पूर्ण अन्यथा
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक
nvkm_ummu_mthd(काष्ठा nvkm_object *object, u32 mthd, व्योम *argv, u32 argc)
अणु
	काष्ठा nvkm_ummu *ummu = nvkm_ummu(object);
	चयन (mthd) अणु
	हाल NVIF_MMU_V0_HEAP: वापस nvkm_ummu_heap(ummu, argv, argc);
	हाल NVIF_MMU_V0_TYPE: वापस nvkm_ummu_type(ummu, argv, argc);
	हाल NVIF_MMU_V0_KIND: वापस nvkm_ummu_kind(ummu, argv, argc);
	शेष:
		अवरोध;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा nvkm_object_func
nvkm_ummu = अणु
	.mthd = nvkm_ummu_mthd,
	.sclass = nvkm_ummu_sclass,
पूर्ण;

पूर्णांक
nvkm_ummu_new(काष्ठा nvkm_device *device, स्थिर काष्ठा nvkm_oclass *oclass,
	      व्योम *argv, u32 argc, काष्ठा nvkm_object **pobject)
अणु
	जोड़ अणु
		काष्ठा nvअगर_mmu_v0 v0;
	पूर्ण *args = argv;
	काष्ठा nvkm_mmu *mmu = device->mmu;
	काष्ठा nvkm_ummu *ummu;
	पूर्णांक ret = -ENOSYS, kinds = 0;
	u8 unused = 0;

	अगर (mmu->func->kind)
		mmu->func->kind(mmu, &kinds, &unused);

	अगर (!(ret = nvअगर_unpack(ret, &argv, &argc, args->v0, 0, 0, false))) अणु
		args->v0.dmabits = mmu->dma_bits;
		args->v0.heap_nr = mmu->heap_nr;
		args->v0.type_nr = mmu->type_nr;
		args->v0.kind_nr = kinds;
	पूर्ण अन्यथा
		वापस ret;

	अगर (!(ummu = kzalloc(माप(*ummu), GFP_KERNEL)))
		वापस -ENOMEM;
	nvkm_object_ctor(&nvkm_ummu, oclass, &ummu->object);
	ummu->mmu = mmu;
	*pobject = &ummu->object;
	वापस 0;
पूर्ण
