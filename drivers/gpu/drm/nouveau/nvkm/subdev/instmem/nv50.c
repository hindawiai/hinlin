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
#घोषणा nv50_insपंचांगem(p) container_of((p), काष्ठा nv50_insपंचांगem, base)
#समावेश "priv.h"

#समावेश <core/memory.h>
#समावेश <subdev/bar.h>
#समावेश <subdev/fb.h>
#समावेश <subdev/mmu.h>

काष्ठा nv50_insपंचांगem अणु
	काष्ठा nvkm_insपंचांगem base;
	u64 addr;

	/* Mappings that can be evicted when BAR2 space has been exhausted. */
	काष्ठा list_head lru;
पूर्ण;

/******************************************************************************
 * insपंचांगem object implementation
 *****************************************************************************/
#घोषणा nv50_instobj(p) container_of((p), काष्ठा nv50_instobj, base.memory)

काष्ठा nv50_instobj अणु
	काष्ठा nvkm_instobj base;
	काष्ठा nv50_insपंचांगem *imem;
	काष्ठा nvkm_memory *ram;
	काष्ठा nvkm_vma *bar;
	refcount_t maps;
	व्योम *map;
	काष्ठा list_head lru;
पूर्ण;

अटल व्योम
nv50_instobj_wr32_slow(काष्ठा nvkm_memory *memory, u64 offset, u32 data)
अणु
	काष्ठा nv50_instobj *iobj = nv50_instobj(memory);
	काष्ठा nv50_insपंचांगem *imem = iobj->imem;
	काष्ठा nvkm_device *device = imem->base.subdev.device;
	u64 base = (nvkm_memory_addr(iobj->ram) + offset) & 0xffffff00000ULL;
	u64 addr = (nvkm_memory_addr(iobj->ram) + offset) & 0x000000fffffULL;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&imem->base.lock, flags);
	अगर (unlikely(imem->addr != base)) अणु
		nvkm_wr32(device, 0x001700, base >> 16);
		imem->addr = base;
	पूर्ण
	nvkm_wr32(device, 0x700000 + addr, data);
	spin_unlock_irqrestore(&imem->base.lock, flags);
पूर्ण

अटल u32
nv50_instobj_rd32_slow(काष्ठा nvkm_memory *memory, u64 offset)
अणु
	काष्ठा nv50_instobj *iobj = nv50_instobj(memory);
	काष्ठा nv50_insपंचांगem *imem = iobj->imem;
	काष्ठा nvkm_device *device = imem->base.subdev.device;
	u64 base = (nvkm_memory_addr(iobj->ram) + offset) & 0xffffff00000ULL;
	u64 addr = (nvkm_memory_addr(iobj->ram) + offset) & 0x000000fffffULL;
	u32 data;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&imem->base.lock, flags);
	अगर (unlikely(imem->addr != base)) अणु
		nvkm_wr32(device, 0x001700, base >> 16);
		imem->addr = base;
	पूर्ण
	data = nvkm_rd32(device, 0x700000 + addr);
	spin_unlock_irqrestore(&imem->base.lock, flags);
	वापस data;
पूर्ण

अटल स्थिर काष्ठा nvkm_memory_ptrs
nv50_instobj_slow = अणु
	.rd32 = nv50_instobj_rd32_slow,
	.wr32 = nv50_instobj_wr32_slow,
पूर्ण;

अटल व्योम
nv50_instobj_wr32(काष्ठा nvkm_memory *memory, u64 offset, u32 data)
अणु
	ioग_लिखो32_native(data, nv50_instobj(memory)->map + offset);
पूर्ण

अटल u32
nv50_instobj_rd32(काष्ठा nvkm_memory *memory, u64 offset)
अणु
	वापस ioपढ़ो32_native(nv50_instobj(memory)->map + offset);
पूर्ण

अटल स्थिर काष्ठा nvkm_memory_ptrs
nv50_instobj_fast = अणु
	.rd32 = nv50_instobj_rd32,
	.wr32 = nv50_instobj_wr32,
पूर्ण;

अटल व्योम
nv50_instobj_kmap(काष्ठा nv50_instobj *iobj, काष्ठा nvkm_vmm *vmm)
अणु
	काष्ठा nv50_insपंचांगem *imem = iobj->imem;
	काष्ठा nv50_instobj *eobj;
	काष्ठा nvkm_memory *memory = &iobj->base.memory;
	काष्ठा nvkm_subdev *subdev = &imem->base.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	काष्ठा nvkm_vma *bar = शून्य, *ebar;
	u64 size = nvkm_memory_size(memory);
	व्योम *emap;
	पूर्णांक ret;

	/* Attempt to allocate BAR2 address-space and map the object
	 * पूर्णांकo it.  The lock has to be dropped जबतक करोing this due
	 * to the possibility of recursion क्रम page table allocation.
	 */
	mutex_unlock(&imem->base.mutex);
	जबतक ((ret = nvkm_vmm_get(vmm, 12, size, &bar))) अणु
		/* Evict unused mappings, and keep retrying until we either
		 * succeed,or there's no more objects left on the LRU.
		 */
		mutex_lock(&imem->base.mutex);
		eobj = list_first_entry_or_null(&imem->lru, typeof(*eobj), lru);
		अगर (eobj) अणु
			nvkm_debug(subdev, "evict %016llx %016llx @ %016llx\n",
				   nvkm_memory_addr(&eobj->base.memory),
				   nvkm_memory_size(&eobj->base.memory),
				   eobj->bar->addr);
			list_del_init(&eobj->lru);
			ebar = eobj->bar;
			eobj->bar = शून्य;
			emap = eobj->map;
			eobj->map = शून्य;
		पूर्ण
		mutex_unlock(&imem->base.mutex);
		अगर (!eobj)
			अवरोध;
		iounmap(emap);
		nvkm_vmm_put(vmm, &ebar);
	पूर्ण

	अगर (ret == 0)
		ret = nvkm_memory_map(memory, 0, vmm, bar, शून्य, 0);
	mutex_lock(&imem->base.mutex);
	अगर (ret || iobj->bar) अणु
		/* We either failed, or another thपढ़ो beat us. */
		mutex_unlock(&imem->base.mutex);
		nvkm_vmm_put(vmm, &bar);
		mutex_lock(&imem->base.mutex);
		वापस;
	पूर्ण

	/* Make the mapping visible to the host. */
	iobj->bar = bar;
	iobj->map = ioremap_wc(device->func->resource_addr(device, 3) +
			       (u32)iobj->bar->addr, size);
	अगर (!iobj->map) अणु
		nvkm_warn(subdev, "PRAMIN ioremap failed\n");
		nvkm_vmm_put(vmm, &iobj->bar);
	पूर्ण
पूर्ण

अटल पूर्णांक
nv50_instobj_map(काष्ठा nvkm_memory *memory, u64 offset, काष्ठा nvkm_vmm *vmm,
		 काष्ठा nvkm_vma *vma, व्योम *argv, u32 argc)
अणु
	memory = nv50_instobj(memory)->ram;
	वापस nvkm_memory_map(memory, offset, vmm, vma, argv, argc);
पूर्ण

अटल व्योम
nv50_instobj_release(काष्ठा nvkm_memory *memory)
अणु
	काष्ठा nv50_instobj *iobj = nv50_instobj(memory);
	काष्ठा nv50_insपंचांगem *imem = iobj->imem;
	काष्ठा nvkm_subdev *subdev = &imem->base.subdev;

	wmb();
	nvkm_bar_flush(subdev->device->bar);

	अगर (refcount_dec_and_mutex_lock(&iobj->maps, &imem->base.mutex)) अणु
		/* Add the now-unused mapping to the LRU instead of directly
		 * unmapping it here, in हाल we need to map it again later.
		 */
		अगर (likely(iobj->lru.next) && iobj->map) अणु
			BUG_ON(!list_empty(&iobj->lru));
			list_add_tail(&iobj->lru, &imem->lru);
		पूर्ण

		/* Switch back to शून्य accessors when last map is gone. */
		iobj->base.memory.ptrs = शून्य;
		mutex_unlock(&imem->base.mutex);
	पूर्ण
पूर्ण

अटल व्योम __iomem *
nv50_instobj_acquire(काष्ठा nvkm_memory *memory)
अणु
	काष्ठा nv50_instobj *iobj = nv50_instobj(memory);
	काष्ठा nvkm_insपंचांगem *imem = &iobj->imem->base;
	काष्ठा nvkm_vmm *vmm;
	व्योम __iomem *map = शून्य;

	/* Alपढ़ोy mapped? */
	अगर (refcount_inc_not_zero(&iobj->maps))
		वापस iobj->map;

	/* Take the lock, and re-check that another thपढ़ो hasn't
	 * alपढ़ोy mapped the object in the meanसमय.
	 */
	mutex_lock(&imem->mutex);
	अगर (refcount_inc_not_zero(&iobj->maps)) अणु
		mutex_unlock(&imem->mutex);
		वापस iobj->map;
	पूर्ण

	/* Attempt to get a direct CPU mapping of the object. */
	अगर ((vmm = nvkm_bar_bar2_vmm(imem->subdev.device))) अणु
		अगर (!iobj->map)
			nv50_instobj_kmap(iobj, vmm);
		map = iobj->map;
	पूर्ण

	अगर (!refcount_inc_not_zero(&iobj->maps)) अणु
		/* Exclude object from eviction जबतक it's being accessed. */
		अगर (likely(iobj->lru.next))
			list_del_init(&iobj->lru);

		अगर (map)
			iobj->base.memory.ptrs = &nv50_instobj_fast;
		अन्यथा
			iobj->base.memory.ptrs = &nv50_instobj_slow;
		refcount_set(&iobj->maps, 1);
	पूर्ण

	mutex_unlock(&imem->mutex);
	वापस map;
पूर्ण

अटल व्योम
nv50_instobj_boot(काष्ठा nvkm_memory *memory, काष्ठा nvkm_vmm *vmm)
अणु
	काष्ठा nv50_instobj *iobj = nv50_instobj(memory);
	काष्ठा nvkm_insपंचांगem *imem = &iobj->imem->base;

	/* Exclude bootstrapped objects (ie. the page tables क्रम the
	 * insपंचांगem BAR itself) from eviction.
	 */
	mutex_lock(&imem->mutex);
	अगर (likely(iobj->lru.next)) अणु
		list_del_init(&iobj->lru);
		iobj->lru.next = शून्य;
	पूर्ण

	nv50_instobj_kmap(iobj, vmm);
	nvkm_insपंचांगem_boot(imem);
	mutex_unlock(&imem->mutex);
पूर्ण

अटल u64
nv50_instobj_size(काष्ठा nvkm_memory *memory)
अणु
	वापस nvkm_memory_size(nv50_instobj(memory)->ram);
पूर्ण

अटल u64
nv50_instobj_addr(काष्ठा nvkm_memory *memory)
अणु
	वापस nvkm_memory_addr(nv50_instobj(memory)->ram);
पूर्ण

अटल u64
nv50_instobj_bar2(काष्ठा nvkm_memory *memory)
अणु
	काष्ठा nv50_instobj *iobj = nv50_instobj(memory);
	u64 addr = ~0ULL;
	अगर (nv50_instobj_acquire(&iobj->base.memory)) अणु
		iobj->lru.next = शून्य; /* Exclude from eviction. */
		addr = iobj->bar->addr;
	पूर्ण
	nv50_instobj_release(&iobj->base.memory);
	वापस addr;
पूर्ण

अटल क्रमागत nvkm_memory_target
nv50_instobj_target(काष्ठा nvkm_memory *memory)
अणु
	वापस nvkm_memory_target(nv50_instobj(memory)->ram);
पूर्ण

अटल व्योम *
nv50_instobj_dtor(काष्ठा nvkm_memory *memory)
अणु
	काष्ठा nv50_instobj *iobj = nv50_instobj(memory);
	काष्ठा nvkm_insपंचांगem *imem = &iobj->imem->base;
	काष्ठा nvkm_vma *bar;
	व्योम *map = map;

	mutex_lock(&imem->mutex);
	अगर (likely(iobj->lru.next))
		list_del(&iobj->lru);
	map = iobj->map;
	bar = iobj->bar;
	mutex_unlock(&imem->mutex);

	अगर (map) अणु
		काष्ठा nvkm_vmm *vmm = nvkm_bar_bar2_vmm(imem->subdev.device);
		iounmap(map);
		अगर (likely(vmm)) /* Can be शून्य during BAR deकाष्ठाor. */
			nvkm_vmm_put(vmm, &bar);
	पूर्ण

	nvkm_memory_unref(&iobj->ram);
	nvkm_instobj_dtor(imem, &iobj->base);
	वापस iobj;
पूर्ण

अटल स्थिर काष्ठा nvkm_memory_func
nv50_instobj_func = अणु
	.dtor = nv50_instobj_dtor,
	.target = nv50_instobj_target,
	.bar2 = nv50_instobj_bar2,
	.addr = nv50_instobj_addr,
	.size = nv50_instobj_size,
	.boot = nv50_instobj_boot,
	.acquire = nv50_instobj_acquire,
	.release = nv50_instobj_release,
	.map = nv50_instobj_map,
पूर्ण;

अटल पूर्णांक
nv50_instobj_new(काष्ठा nvkm_insपंचांगem *base, u32 size, u32 align, bool zero,
		 काष्ठा nvkm_memory **pmemory)
अणु
	काष्ठा nv50_insपंचांगem *imem = nv50_insपंचांगem(base);
	काष्ठा nv50_instobj *iobj;
	काष्ठा nvkm_device *device = imem->base.subdev.device;
	u8 page = max(order_base_2(align), 12);

	अगर (!(iobj = kzalloc(माप(*iobj), GFP_KERNEL)))
		वापस -ENOMEM;
	*pmemory = &iobj->base.memory;

	nvkm_instobj_ctor(&nv50_instobj_func, &imem->base, &iobj->base);
	iobj->imem = imem;
	refcount_set(&iobj->maps, 0);
	INIT_LIST_HEAD(&iobj->lru);

	वापस nvkm_ram_get(device, 0, 1, page, size, true, true, &iobj->ram);
पूर्ण

/******************************************************************************
 * insपंचांगem subdev implementation
 *****************************************************************************/

अटल व्योम
nv50_insपंचांगem_fini(काष्ठा nvkm_insपंचांगem *base)
अणु
	nv50_insपंचांगem(base)->addr = ~0ULL;
पूर्ण

अटल स्थिर काष्ठा nvkm_insपंचांगem_func
nv50_insपंचांगem = अणु
	.fini = nv50_insपंचांगem_fini,
	.memory_new = nv50_instobj_new,
	.zero = false,
पूर्ण;

पूर्णांक
nv50_insपंचांगem_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
		 काष्ठा nvkm_insपंचांगem **pimem)
अणु
	काष्ठा nv50_insपंचांगem *imem;

	अगर (!(imem = kzalloc(माप(*imem), GFP_KERNEL)))
		वापस -ENOMEM;
	nvkm_insपंचांगem_ctor(&nv50_insपंचांगem, device, type, inst, &imem->base);
	INIT_LIST_HEAD(&imem->lru);
	*pimem = &imem->base;
	वापस 0;
पूर्ण
