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
#समावेश "umem.h"
#समावेश "ummu.h"

#समावेश <core/client.h>
#समावेश <core/memory.h>
#समावेश <subdev/bar.h>

#समावेश <nvअगर/class.h>
#समावेश <nvअगर/अगर000a.h>
#समावेश <nvअगर/unpack.h>

अटल स्थिर काष्ठा nvkm_object_func nvkm_umem;
काष्ठा nvkm_memory *
nvkm_umem_search(काष्ठा nvkm_client *client, u64 handle)
अणु
	काष्ठा nvkm_client *master = client->object.client;
	काष्ठा nvkm_memory *memory = शून्य;
	काष्ठा nvkm_object *object;
	काष्ठा nvkm_umem *umem;

	object = nvkm_object_search(client, handle, &nvkm_umem);
	अगर (IS_ERR(object)) अणु
		अगर (client->super && client != master) अणु
			spin_lock(&master->lock);
			list_क्रम_each_entry(umem, &master->umem, head) अणु
				अगर (umem->object.object == handle) अणु
					memory = nvkm_memory_ref(umem->memory);
					अवरोध;
				पूर्ण
			पूर्ण
			spin_unlock(&master->lock);
		पूर्ण
	पूर्ण अन्यथा अणु
		umem = nvkm_umem(object);
		अगर (!umem->priv || client->super)
			memory = nvkm_memory_ref(umem->memory);
	पूर्ण

	वापस memory ? memory : ERR_PTR(-ENOENT);
पूर्ण

अटल पूर्णांक
nvkm_umem_unmap(काष्ठा nvkm_object *object)
अणु
	काष्ठा nvkm_umem *umem = nvkm_umem(object);

	अगर (!umem->map)
		वापस -EEXIST;

	अगर (umem->io) अणु
		अगर (!IS_ERR(umem->bar)) अणु
			काष्ठा nvkm_device *device = umem->mmu->subdev.device;
			nvkm_vmm_put(nvkm_bar_bar1_vmm(device), &umem->bar);
		पूर्ण अन्यथा अणु
			umem->bar = शून्य;
		पूर्ण
	पूर्ण अन्यथा अणु
		vunmap(umem->map);
		umem->map = शून्य;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
nvkm_umem_map(काष्ठा nvkm_object *object, व्योम *argv, u32 argc,
	      क्रमागत nvkm_object_map *type, u64 *handle, u64 *length)
अणु
	काष्ठा nvkm_umem *umem = nvkm_umem(object);
	काष्ठा nvkm_mmu *mmu = umem->mmu;

	अगर (!umem->mappable)
		वापस -EINVAL;
	अगर (umem->map)
		वापस -EEXIST;

	अगर ((umem->type & NVKM_MEM_HOST) && !argc) अणु
		पूर्णांक ret = nvkm_mem_map_host(umem->memory, &umem->map);
		अगर (ret)
			वापस ret;

		*handle = (अचिन्हित दीर्घ)(व्योम *)umem->map;
		*length = nvkm_memory_size(umem->memory);
		*type = NVKM_OBJECT_MAP_VA;
		वापस 0;
	पूर्ण अन्यथा
	अगर ((umem->type & NVKM_MEM_VRAM) ||
	    (umem->type & NVKM_MEM_KIND)) अणु
		पूर्णांक ret = mmu->func->mem.umap(mmu, umem->memory, argv, argc,
					      handle, length, &umem->bar);
		अगर (ret)
			वापस ret;

		*type = NVKM_OBJECT_MAP_IO;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	umem->io = (*type == NVKM_OBJECT_MAP_IO);
	वापस 0;
पूर्ण

अटल व्योम *
nvkm_umem_dtor(काष्ठा nvkm_object *object)
अणु
	काष्ठा nvkm_umem *umem = nvkm_umem(object);
	spin_lock(&umem->object.client->lock);
	list_del_init(&umem->head);
	spin_unlock(&umem->object.client->lock);
	nvkm_memory_unref(&umem->memory);
	वापस umem;
पूर्ण

अटल स्थिर काष्ठा nvkm_object_func
nvkm_umem = अणु
	.dtor = nvkm_umem_dtor,
	.map = nvkm_umem_map,
	.unmap = nvkm_umem_unmap,
पूर्ण;

पूर्णांक
nvkm_umem_new(स्थिर काष्ठा nvkm_oclass *oclass, व्योम *argv, u32 argc,
	      काष्ठा nvkm_object **pobject)
अणु
	काष्ठा nvkm_mmu *mmu = nvkm_ummu(oclass->parent)->mmu;
	जोड़ अणु
		काष्ठा nvअगर_mem_v0 v0;
	पूर्ण *args = argv;
	काष्ठा nvkm_umem *umem;
	पूर्णांक type, ret = -ENOSYS;
	u8  page;
	u64 size;

	अगर (!(ret = nvअगर_unpack(ret, &argv, &argc, args->v0, 0, 0, true))) अणु
		type = args->v0.type;
		page = args->v0.page;
		size = args->v0.size;
	पूर्ण अन्यथा
		वापस ret;

	अगर (type >= mmu->type_nr)
		वापस -EINVAL;

	अगर (!(umem = kzalloc(माप(*umem), GFP_KERNEL)))
		वापस -ENOMEM;
	nvkm_object_ctor(&nvkm_umem, oclass, &umem->object);
	umem->mmu = mmu;
	umem->type = mmu->type[type].type;
	umem->priv = oclass->client->super;
	INIT_LIST_HEAD(&umem->head);
	*pobject = &umem->object;

	अगर (mmu->type[type].type & NVKM_MEM_MAPPABLE) अणु
		page = max_t(u8, page, PAGE_SHIFT);
		umem->mappable = true;
	पूर्ण

	ret = nvkm_mem_new_type(mmu, type, page, size, argv, argc,
				&umem->memory);
	अगर (ret)
		वापस ret;

	spin_lock(&umem->object.client->lock);
	list_add(&umem->head, &umem->object.client->umem);
	spin_unlock(&umem->object.client->lock);

	args->v0.page = nvkm_memory_page(umem->memory);
	args->v0.addr = nvkm_memory_addr(umem->memory);
	args->v0.size = nvkm_memory_size(umem->memory);
	वापस 0;
पूर्ण
