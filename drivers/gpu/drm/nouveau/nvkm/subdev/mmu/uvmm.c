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
#समावेश "uvmm.h"
#समावेश "umem.h"
#समावेश "ummu.h"

#समावेश <core/client.h>
#समावेश <core/memory.h>

#समावेश <nvअगर/अगर000c.h>
#समावेश <nvअगर/unpack.h>

अटल स्थिर काष्ठा nvkm_object_func nvkm_uvmm;
काष्ठा nvkm_vmm *
nvkm_uvmm_search(काष्ठा nvkm_client *client, u64 handle)
अणु
	काष्ठा nvkm_object *object;

	object = nvkm_object_search(client, handle, &nvkm_uvmm);
	अगर (IS_ERR(object))
		वापस (व्योम *)object;

	वापस nvkm_uvmm(object)->vmm;
पूर्ण

अटल पूर्णांक
nvkm_uvmm_mthd_pfnclr(काष्ठा nvkm_uvmm *uvmm, व्योम *argv, u32 argc)
अणु
	काष्ठा nvkm_client *client = uvmm->object.client;
	जोड़ अणु
		काष्ठा nvअगर_vmm_pfnclr_v0 v0;
	पूर्ण *args = argv;
	काष्ठा nvkm_vmm *vmm = uvmm->vmm;
	पूर्णांक ret = -ENOSYS;
	u64 addr, size;

	अगर (!(ret = nvअगर_unpack(ret, &argv, &argc, args->v0, 0, 0, false))) अणु
		addr = args->v0.addr;
		size = args->v0.size;
	पूर्ण अन्यथा
		वापस ret;

	अगर (!client->super)
		वापस -ENOENT;

	अगर (size) अणु
		mutex_lock(&vmm->mutex);
		ret = nvkm_vmm_pfn_unmap(vmm, addr, size);
		mutex_unlock(&vmm->mutex);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक
nvkm_uvmm_mthd_pfnmap(काष्ठा nvkm_uvmm *uvmm, व्योम *argv, u32 argc)
अणु
	काष्ठा nvkm_client *client = uvmm->object.client;
	जोड़ अणु
		काष्ठा nvअगर_vmm_pfnmap_v0 v0;
	पूर्ण *args = argv;
	काष्ठा nvkm_vmm *vmm = uvmm->vmm;
	पूर्णांक ret = -ENOSYS;
	u64 addr, size, *phys;
	u8  page;

	अगर (!(ret = nvअगर_unpack(ret, &argv, &argc, args->v0, 0, 0, true))) अणु
		page = args->v0.page;
		addr = args->v0.addr;
		size = args->v0.size;
		phys = args->v0.phys;
		अगर (argc != (size >> page) * माप(args->v0.phys[0]))
			वापस -EINVAL;
	पूर्ण अन्यथा
		वापस ret;

	अगर (!client->super)
		वापस -ENOENT;

	अगर (size) अणु
		mutex_lock(&vmm->mutex);
		ret = nvkm_vmm_pfn_map(vmm, page, addr, size, phys);
		mutex_unlock(&vmm->mutex);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक
nvkm_uvmm_mthd_unmap(काष्ठा nvkm_uvmm *uvmm, व्योम *argv, u32 argc)
अणु
	काष्ठा nvkm_client *client = uvmm->object.client;
	जोड़ अणु
		काष्ठा nvअगर_vmm_unmap_v0 v0;
	पूर्ण *args = argv;
	काष्ठा nvkm_vmm *vmm = uvmm->vmm;
	काष्ठा nvkm_vma *vma;
	पूर्णांक ret = -ENOSYS;
	u64 addr;

	अगर (!(ret = nvअगर_unpack(ret, &argv, &argc, args->v0, 0, 0, false))) अणु
		addr = args->v0.addr;
	पूर्ण अन्यथा
		वापस ret;

	mutex_lock(&vmm->mutex);
	vma = nvkm_vmm_node_search(vmm, addr);
	अगर (ret = -ENOENT, !vma || vma->addr != addr) अणु
		VMM_DEBUG(vmm, "lookup %016llx: %016llx",
			  addr, vma ? vma->addr : ~0ULL);
		जाओ करोne;
	पूर्ण

	अगर (ret = -ENOENT, (!vma->user && !client->super) || vma->busy) अणु
		VMM_DEBUG(vmm, "denied %016llx: %d %d %d", addr,
			  vma->user, !client->super, vma->busy);
		जाओ करोne;
	पूर्ण

	अगर (ret = -EINVAL, !vma->memory) अणु
		VMM_DEBUG(vmm, "unmapped");
		जाओ करोne;
	पूर्ण

	nvkm_vmm_unmap_locked(vmm, vma, false);
	ret = 0;
करोne:
	mutex_unlock(&vmm->mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक
nvkm_uvmm_mthd_map(काष्ठा nvkm_uvmm *uvmm, व्योम *argv, u32 argc)
अणु
	काष्ठा nvkm_client *client = uvmm->object.client;
	जोड़ अणु
		काष्ठा nvअगर_vmm_map_v0 v0;
	पूर्ण *args = argv;
	u64 addr, size, handle, offset;
	काष्ठा nvkm_vmm *vmm = uvmm->vmm;
	काष्ठा nvkm_vma *vma;
	काष्ठा nvkm_memory *memory;
	पूर्णांक ret = -ENOSYS;

	अगर (!(ret = nvअगर_unpack(ret, &argv, &argc, args->v0, 0, 0, true))) अणु
		addr = args->v0.addr;
		size = args->v0.size;
		handle = args->v0.memory;
		offset = args->v0.offset;
	पूर्ण अन्यथा
		वापस ret;

	memory = nvkm_umem_search(client, handle);
	अगर (IS_ERR(memory)) अणु
		VMM_DEBUG(vmm, "memory %016llx %ld\n", handle, PTR_ERR(memory));
		वापस PTR_ERR(memory);
	पूर्ण

	mutex_lock(&vmm->mutex);
	अगर (ret = -ENOENT, !(vma = nvkm_vmm_node_search(vmm, addr))) अणु
		VMM_DEBUG(vmm, "lookup %016llx", addr);
		जाओ fail;
	पूर्ण

	अगर (ret = -ENOENT, (!vma->user && !client->super) || vma->busy) अणु
		VMM_DEBUG(vmm, "denied %016llx: %d %d %d", addr,
			  vma->user, !client->super, vma->busy);
		जाओ fail;
	पूर्ण

	अगर (ret = -EINVAL, vma->mapped && !vma->memory) अणु
		VMM_DEBUG(vmm, "pfnmap %016llx", addr);
		जाओ fail;
	पूर्ण

	अगर (ret = -EINVAL, vma->addr != addr || vma->size != size) अणु
		अगर (addr + size > vma->addr + vma->size || vma->memory ||
		    (vma->refd == NVKM_VMA_PAGE_NONE && !vma->mapref)) अणु
			VMM_DEBUG(vmm, "split %d %d %d "
				       "%016llx %016llx %016llx %016llx",
				  !!vma->memory, vma->refd, vma->mapref,
				  addr, size, vma->addr, (u64)vma->size);
			जाओ fail;
		पूर्ण

		vma = nvkm_vmm_node_split(vmm, vma, addr, size);
		अगर (!vma) अणु
			ret = -ENOMEM;
			जाओ fail;
		पूर्ण
	पूर्ण
	vma->busy = true;
	mutex_unlock(&vmm->mutex);

	ret = nvkm_memory_map(memory, offset, vmm, vma, argv, argc);
	अगर (ret == 0) अणु
		/* Successful map will clear vma->busy. */
		nvkm_memory_unref(&memory);
		वापस 0;
	पूर्ण

	mutex_lock(&vmm->mutex);
	vma->busy = false;
	nvkm_vmm_unmap_region(vmm, vma);
fail:
	mutex_unlock(&vmm->mutex);
	nvkm_memory_unref(&memory);
	वापस ret;
पूर्ण

अटल पूर्णांक
nvkm_uvmm_mthd_put(काष्ठा nvkm_uvmm *uvmm, व्योम *argv, u32 argc)
अणु
	काष्ठा nvkm_client *client = uvmm->object.client;
	जोड़ अणु
		काष्ठा nvअगर_vmm_put_v0 v0;
	पूर्ण *args = argv;
	काष्ठा nvkm_vmm *vmm = uvmm->vmm;
	काष्ठा nvkm_vma *vma;
	पूर्णांक ret = -ENOSYS;
	u64 addr;

	अगर (!(ret = nvअगर_unpack(ret, &argv, &argc, args->v0, 0, 0, false))) अणु
		addr = args->v0.addr;
	पूर्ण अन्यथा
		वापस ret;

	mutex_lock(&vmm->mutex);
	vma = nvkm_vmm_node_search(vmm, args->v0.addr);
	अगर (ret = -ENOENT, !vma || vma->addr != addr || vma->part) अणु
		VMM_DEBUG(vmm, "lookup %016llx: %016llx %d", addr,
			  vma ? vma->addr : ~0ULL, vma ? vma->part : 0);
		जाओ करोne;
	पूर्ण

	अगर (ret = -ENOENT, (!vma->user && !client->super) || vma->busy) अणु
		VMM_DEBUG(vmm, "denied %016llx: %d %d %d", addr,
			  vma->user, !client->super, vma->busy);
		जाओ करोne;
	पूर्ण

	nvkm_vmm_put_locked(vmm, vma);
	ret = 0;
करोne:
	mutex_unlock(&vmm->mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक
nvkm_uvmm_mthd_get(काष्ठा nvkm_uvmm *uvmm, व्योम *argv, u32 argc)
अणु
	काष्ठा nvkm_client *client = uvmm->object.client;
	जोड़ अणु
		काष्ठा nvअगर_vmm_get_v0 v0;
	पूर्ण *args = argv;
	काष्ठा nvkm_vmm *vmm = uvmm->vmm;
	काष्ठा nvkm_vma *vma;
	पूर्णांक ret = -ENOSYS;
	bool getref, mapref, sparse;
	u8 page, align;
	u64 size;

	अगर (!(ret = nvअगर_unpack(ret, &argv, &argc, args->v0, 0, 0, false))) अणु
		getref = args->v0.type == NVIF_VMM_GET_V0_PTES;
		mapref = args->v0.type == NVIF_VMM_GET_V0_ADDR;
		sparse = args->v0.sparse;
		page = args->v0.page;
		align = args->v0.align;
		size = args->v0.size;
	पूर्ण अन्यथा
		वापस ret;

	mutex_lock(&vmm->mutex);
	ret = nvkm_vmm_get_locked(vmm, getref, mapref, sparse,
				  page, align, size, &vma);
	mutex_unlock(&vmm->mutex);
	अगर (ret)
		वापस ret;

	args->v0.addr = vma->addr;
	vma->user = !client->super;
	वापस ret;
पूर्ण

अटल पूर्णांक
nvkm_uvmm_mthd_page(काष्ठा nvkm_uvmm *uvmm, व्योम *argv, u32 argc)
अणु
	जोड़ अणु
		काष्ठा nvअगर_vmm_page_v0 v0;
	पूर्ण *args = argv;
	स्थिर काष्ठा nvkm_vmm_page *page;
	पूर्णांक ret = -ENOSYS;
	u8 type, index, nr;

	page = uvmm->vmm->func->page;
	क्रम (nr = 0; page[nr].shअगरt; nr++);

	अगर (!(ret = nvअगर_unpack(ret, &argv, &argc, args->v0, 0, 0, false))) अणु
		अगर ((index = args->v0.index) >= nr)
			वापस -EINVAL;
		type = page[index].type;
		args->v0.shअगरt = page[index].shअगरt;
		args->v0.sparse = !!(type & NVKM_VMM_PAGE_SPARSE);
		args->v0.vram = !!(type & NVKM_VMM_PAGE_VRAM);
		args->v0.host = !!(type & NVKM_VMM_PAGE_HOST);
		args->v0.comp = !!(type & NVKM_VMM_PAGE_COMP);
	पूर्ण अन्यथा
		वापस -ENOSYS;

	वापस 0;
पूर्ण

अटल पूर्णांक
nvkm_uvmm_mthd(काष्ठा nvkm_object *object, u32 mthd, व्योम *argv, u32 argc)
अणु
	काष्ठा nvkm_uvmm *uvmm = nvkm_uvmm(object);
	चयन (mthd) अणु
	हाल NVIF_VMM_V0_PAGE  : वापस nvkm_uvmm_mthd_page  (uvmm, argv, argc);
	हाल NVIF_VMM_V0_GET   : वापस nvkm_uvmm_mthd_get   (uvmm, argv, argc);
	हाल NVIF_VMM_V0_PUT   : वापस nvkm_uvmm_mthd_put   (uvmm, argv, argc);
	हाल NVIF_VMM_V0_MAP   : वापस nvkm_uvmm_mthd_map   (uvmm, argv, argc);
	हाल NVIF_VMM_V0_UNMAP : वापस nvkm_uvmm_mthd_unmap (uvmm, argv, argc);
	हाल NVIF_VMM_V0_PFNMAP: वापस nvkm_uvmm_mthd_pfnmap(uvmm, argv, argc);
	हाल NVIF_VMM_V0_PFNCLR: वापस nvkm_uvmm_mthd_pfnclr(uvmm, argv, argc);
	हाल NVIF_VMM_V0_MTHD(0x00) ... NVIF_VMM_V0_MTHD(0x7f):
		अगर (uvmm->vmm->func->mthd) अणु
			वापस uvmm->vmm->func->mthd(uvmm->vmm,
						     uvmm->object.client,
						     mthd, argv, argc);
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल व्योम *
nvkm_uvmm_dtor(काष्ठा nvkm_object *object)
अणु
	काष्ठा nvkm_uvmm *uvmm = nvkm_uvmm(object);
	nvkm_vmm_unref(&uvmm->vmm);
	वापस uvmm;
पूर्ण

अटल स्थिर काष्ठा nvkm_object_func
nvkm_uvmm = अणु
	.dtor = nvkm_uvmm_dtor,
	.mthd = nvkm_uvmm_mthd,
पूर्ण;

पूर्णांक
nvkm_uvmm_new(स्थिर काष्ठा nvkm_oclass *oclass, व्योम *argv, u32 argc,
	      काष्ठा nvkm_object **pobject)
अणु
	काष्ठा nvkm_mmu *mmu = nvkm_ummu(oclass->parent)->mmu;
	स्थिर bool more = oclass->base.maxver >= 0;
	जोड़ अणु
		काष्ठा nvअगर_vmm_v0 v0;
	पूर्ण *args = argv;
	स्थिर काष्ठा nvkm_vmm_page *page;
	काष्ठा nvkm_uvmm *uvmm;
	पूर्णांक ret = -ENOSYS;
	u64 addr, size;
	bool managed;

	अगर (!(ret = nvअगर_unpack(ret, &argv, &argc, args->v0, 0, 0, more))) अणु
		managed = args->v0.managed != 0;
		addr = args->v0.addr;
		size = args->v0.size;
	पूर्ण अन्यथा
		वापस ret;

	अगर (!(uvmm = kzalloc(माप(*uvmm), GFP_KERNEL)))
		वापस -ENOMEM;
	nvkm_object_ctor(&nvkm_uvmm, oclass, &uvmm->object);
	*pobject = &uvmm->object;

	अगर (!mmu->vmm) अणु
		ret = mmu->func->vmm.ctor(mmu, managed, addr, size, argv, argc,
					  शून्य, "user", &uvmm->vmm);
		अगर (ret)
			वापस ret;

		uvmm->vmm->debug = max(uvmm->vmm->debug, oclass->client->debug);
	पूर्ण अन्यथा अणु
		अगर (size)
			वापस -EINVAL;

		uvmm->vmm = nvkm_vmm_ref(mmu->vmm);
	पूर्ण

	page = uvmm->vmm->func->page;
	args->v0.page_nr = 0;
	जबतक (page && (page++)->shअगरt)
		args->v0.page_nr++;
	args->v0.addr = uvmm->vmm->start;
	args->v0.size = uvmm->vmm->limit;
	वापस 0;
पूर्ण
