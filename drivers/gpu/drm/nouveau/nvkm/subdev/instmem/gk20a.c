<शैली गुरु>
/*
 * Copyright (c) 2015, NVIDIA CORPORATION. All rights reserved.
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
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

/*
 * GK20A करोes not have dedicated video memory, and to accurately represent this
 * fact Nouveau will not create a RAM device क्रम it. Thereक्रमe its insपंचांगem
 * implementation must be करोne directly on top of प्रणाली memory, जबतक
 * preserving coherency क्रम पढ़ो and ग_लिखो operations.
 *
 * Insपंचांगem can be allocated through two means:
 * 1) If an IOMMU unit has been probed, the IOMMU API is used to make memory
 *    pages contiguous to the GPU. This is the preferred way.
 * 2) If no IOMMU unit is probed, the DMA API is used to allocate physically
 *    contiguous memory.
 *
 * In both हालs CPU पढ़ो and ग_लिखोs are perक्रमmed by creating a ग_लिखो-combined
 * mapping. The GPU L2 cache must thus be flushed/invalidated when required. To
 * be conservative we करो this every समय we acquire or release an instobj, but
 * ideally L2 management should be handled at a higher level.
 *
 * To improve perक्रमmance, CPU mappings are not हटाओd upon instobj release.
 * Instead they are placed पूर्णांकo a LRU list to be recycled when the mapped space
 * goes beyond a certain threshold. At the moment this limit is 1MB.
 */
#समावेश "priv.h"

#समावेश <core/memory.h>
#समावेश <core/tegra.h>
#समावेश <subdev/ltc.h>
#समावेश <subdev/mmu.h>

काष्ठा gk20a_instobj अणु
	काष्ठा nvkm_memory memory;
	काष्ठा nvkm_mm_node *mn;
	काष्ठा gk20a_insपंचांगem *imem;

	/* CPU mapping */
	u32 *vaddr;
पूर्ण;
#घोषणा gk20a_instobj(p) container_of((p), काष्ठा gk20a_instobj, memory)

/*
 * Used क्रम objects allocated using the DMA API
 */
काष्ठा gk20a_instobj_dma अणु
	काष्ठा gk20a_instobj base;

	dma_addr_t handle;
	काष्ठा nvkm_mm_node r;
पूर्ण;
#घोषणा gk20a_instobj_dma(p) \
	container_of(gk20a_instobj(p), काष्ठा gk20a_instobj_dma, base)

/*
 * Used क्रम objects flattened using the IOMMU API
 */
काष्ठा gk20a_instobj_iommu अणु
	काष्ठा gk20a_instobj base;

	/* to link पूर्णांकo gk20a_insपंचांगem::vaddr_lru */
	काष्ठा list_head vaddr_node;
	/* how many clients are using vaddr? */
	u32 use_cpt;

	/* will poपूर्णांक to the higher half of pages */
	dma_addr_t *dma_addrs;
	/* array of base.mem->size pages (+ dma_addr_ts) */
	काष्ठा page *pages[];
पूर्ण;
#घोषणा gk20a_instobj_iommu(p) \
	container_of(gk20a_instobj(p), काष्ठा gk20a_instobj_iommu, base)

काष्ठा gk20a_insपंचांगem अणु
	काष्ठा nvkm_insपंचांगem base;

	/* protects vaddr_* and gk20a_instobj::vaddr* */
	काष्ठा mutex lock;

	/* CPU mappings LRU */
	अचिन्हित पूर्णांक vaddr_use;
	अचिन्हित पूर्णांक vaddr_max;
	काष्ठा list_head vaddr_lru;

	/* Only used अगर IOMMU अगर present */
	काष्ठा mutex *mm_mutex;
	काष्ठा nvkm_mm *mm;
	काष्ठा iommu_करोमुख्य *करोमुख्य;
	अचिन्हित दीर्घ iommu_pgshअगरt;
	u16 iommu_bit;

	/* Only used by DMA API */
	अचिन्हित दीर्घ attrs;
पूर्ण;
#घोषणा gk20a_insपंचांगem(p) container_of((p), काष्ठा gk20a_insपंचांगem, base)

अटल क्रमागत nvkm_memory_target
gk20a_instobj_target(काष्ठा nvkm_memory *memory)
अणु
	वापस NVKM_MEM_TARGET_NCOH;
पूर्ण

अटल u8
gk20a_instobj_page(काष्ठा nvkm_memory *memory)
अणु
	वापस 12;
पूर्ण

अटल u64
gk20a_instobj_addr(काष्ठा nvkm_memory *memory)
अणु
	वापस (u64)gk20a_instobj(memory)->mn->offset << 12;
पूर्ण

अटल u64
gk20a_instobj_size(काष्ठा nvkm_memory *memory)
अणु
	वापस (u64)gk20a_instobj(memory)->mn->length << 12;
पूर्ण

/*
 * Recycle the vaddr of obj. Must be called with gk20a_insपंचांगem::lock held.
 */
अटल व्योम
gk20a_instobj_iommu_recycle_vaddr(काष्ठा gk20a_instobj_iommu *obj)
अणु
	काष्ठा gk20a_insपंचांगem *imem = obj->base.imem;
	/* there should not be any user left... */
	WARN_ON(obj->use_cpt);
	list_del(&obj->vaddr_node);
	vunmap(obj->base.vaddr);
	obj->base.vaddr = शून्य;
	imem->vaddr_use -= nvkm_memory_size(&obj->base.memory);
	nvkm_debug(&imem->base.subdev, "vaddr used: %x/%x\n", imem->vaddr_use,
		   imem->vaddr_max);
पूर्ण

/*
 * Must be called जबतक holding gk20a_insपंचांगem::lock
 */
अटल व्योम
gk20a_insपंचांगem_vaddr_gc(काष्ठा gk20a_insपंचांगem *imem, स्थिर u64 size)
अणु
	जबतक (imem->vaddr_use + size > imem->vaddr_max) अणु
		/* no candidate that can be unmapped, पात... */
		अगर (list_empty(&imem->vaddr_lru))
			अवरोध;

		gk20a_instobj_iommu_recycle_vaddr(
				list_first_entry(&imem->vaddr_lru,
				काष्ठा gk20a_instobj_iommu, vaddr_node));
	पूर्ण
पूर्ण

अटल व्योम __iomem *
gk20a_instobj_acquire_dma(काष्ठा nvkm_memory *memory)
अणु
	काष्ठा gk20a_instobj *node = gk20a_instobj(memory);
	काष्ठा gk20a_insपंचांगem *imem = node->imem;
	काष्ठा nvkm_ltc *ltc = imem->base.subdev.device->ltc;

	nvkm_ltc_flush(ltc);

	वापस node->vaddr;
पूर्ण

अटल व्योम __iomem *
gk20a_instobj_acquire_iommu(काष्ठा nvkm_memory *memory)
अणु
	काष्ठा gk20a_instobj_iommu *node = gk20a_instobj_iommu(memory);
	काष्ठा gk20a_insपंचांगem *imem = node->base.imem;
	काष्ठा nvkm_ltc *ltc = imem->base.subdev.device->ltc;
	स्थिर u64 size = nvkm_memory_size(memory);

	nvkm_ltc_flush(ltc);

	mutex_lock(&imem->lock);

	अगर (node->base.vaddr) अणु
		अगर (!node->use_cpt) अणु
			/* हटाओ from LRU list since mapping in use again */
			list_del(&node->vaddr_node);
		पूर्ण
		जाओ out;
	पूर्ण

	/* try to मुक्त some address space अगर we reached the limit */
	gk20a_insपंचांगem_vaddr_gc(imem, size);

	/* map the pages */
	node->base.vaddr = vmap(node->pages, size >> PAGE_SHIFT, VM_MAP,
				pgprot_ग_लिखोcombine(PAGE_KERNEL));
	अगर (!node->base.vaddr) अणु
		nvkm_error(&imem->base.subdev, "cannot map instobj - "
			   "this is not going to end well...\n");
		जाओ out;
	पूर्ण

	imem->vaddr_use += size;
	nvkm_debug(&imem->base.subdev, "vaddr used: %x/%x\n",
		   imem->vaddr_use, imem->vaddr_max);

out:
	node->use_cpt++;
	mutex_unlock(&imem->lock);

	वापस node->base.vaddr;
पूर्ण

अटल व्योम
gk20a_instobj_release_dma(काष्ठा nvkm_memory *memory)
अणु
	काष्ठा gk20a_instobj *node = gk20a_instobj(memory);
	काष्ठा gk20a_insपंचांगem *imem = node->imem;
	काष्ठा nvkm_ltc *ltc = imem->base.subdev.device->ltc;

	/* in हाल we got a ग_लिखो-combined mapping */
	wmb();
	nvkm_ltc_invalidate(ltc);
पूर्ण

अटल व्योम
gk20a_instobj_release_iommu(काष्ठा nvkm_memory *memory)
अणु
	काष्ठा gk20a_instobj_iommu *node = gk20a_instobj_iommu(memory);
	काष्ठा gk20a_insपंचांगem *imem = node->base.imem;
	काष्ठा nvkm_ltc *ltc = imem->base.subdev.device->ltc;

	mutex_lock(&imem->lock);

	/* we should at least have one user to release... */
	अगर (WARN_ON(node->use_cpt == 0))
		जाओ out;

	/* add unused objs to the LRU list to recycle their mapping */
	अगर (--node->use_cpt == 0)
		list_add_tail(&node->vaddr_node, &imem->vaddr_lru);

out:
	mutex_unlock(&imem->lock);

	wmb();
	nvkm_ltc_invalidate(ltc);
पूर्ण

अटल u32
gk20a_instobj_rd32(काष्ठा nvkm_memory *memory, u64 offset)
अणु
	काष्ठा gk20a_instobj *node = gk20a_instobj(memory);

	वापस node->vaddr[offset / 4];
पूर्ण

अटल व्योम
gk20a_instobj_wr32(काष्ठा nvkm_memory *memory, u64 offset, u32 data)
अणु
	काष्ठा gk20a_instobj *node = gk20a_instobj(memory);

	node->vaddr[offset / 4] = data;
पूर्ण

अटल पूर्णांक
gk20a_instobj_map(काष्ठा nvkm_memory *memory, u64 offset, काष्ठा nvkm_vmm *vmm,
		  काष्ठा nvkm_vma *vma, व्योम *argv, u32 argc)
अणु
	काष्ठा gk20a_instobj *node = gk20a_instobj(memory);
	काष्ठा nvkm_vmm_map map = अणु
		.memory = &node->memory,
		.offset = offset,
		.mem = node->mn,
	पूर्ण;

	वापस nvkm_vmm_map(vmm, vma, argv, argc, &map);
पूर्ण

अटल व्योम *
gk20a_instobj_dtor_dma(काष्ठा nvkm_memory *memory)
अणु
	काष्ठा gk20a_instobj_dma *node = gk20a_instobj_dma(memory);
	काष्ठा gk20a_insपंचांगem *imem = node->base.imem;
	काष्ठा device *dev = imem->base.subdev.device->dev;

	अगर (unlikely(!node->base.vaddr))
		जाओ out;

	dma_मुक्त_attrs(dev, (u64)node->base.mn->length << PAGE_SHIFT,
		       node->base.vaddr, node->handle, imem->attrs);

out:
	वापस node;
पूर्ण

अटल व्योम *
gk20a_instobj_dtor_iommu(काष्ठा nvkm_memory *memory)
अणु
	काष्ठा gk20a_instobj_iommu *node = gk20a_instobj_iommu(memory);
	काष्ठा gk20a_insपंचांगem *imem = node->base.imem;
	काष्ठा device *dev = imem->base.subdev.device->dev;
	काष्ठा nvkm_mm_node *r = node->base.mn;
	पूर्णांक i;

	अगर (unlikely(!r))
		जाओ out;

	mutex_lock(&imem->lock);

	/* vaddr has alपढ़ोy been recycled */
	अगर (node->base.vaddr)
		gk20a_instobj_iommu_recycle_vaddr(node);

	mutex_unlock(&imem->lock);

	/* clear IOMMU bit to unmap pages */
	r->offset &= ~BIT(imem->iommu_bit - imem->iommu_pgshअगरt);

	/* Unmap pages from GPU address space and मुक्त them */
	क्रम (i = 0; i < node->base.mn->length; i++) अणु
		iommu_unmap(imem->करोमुख्य,
			    (r->offset + i) << imem->iommu_pgshअगरt, PAGE_SIZE);
		dma_unmap_page(dev, node->dma_addrs[i], PAGE_SIZE,
			       DMA_BIसूचीECTIONAL);
		__मुक्त_page(node->pages[i]);
	पूर्ण

	/* Release area from GPU address space */
	mutex_lock(imem->mm_mutex);
	nvkm_mm_मुक्त(imem->mm, &r);
	mutex_unlock(imem->mm_mutex);

out:
	वापस node;
पूर्ण

अटल स्थिर काष्ठा nvkm_memory_func
gk20a_instobj_func_dma = अणु
	.dtor = gk20a_instobj_dtor_dma,
	.target = gk20a_instobj_target,
	.page = gk20a_instobj_page,
	.addr = gk20a_instobj_addr,
	.size = gk20a_instobj_size,
	.acquire = gk20a_instobj_acquire_dma,
	.release = gk20a_instobj_release_dma,
	.map = gk20a_instobj_map,
पूर्ण;

अटल स्थिर काष्ठा nvkm_memory_func
gk20a_instobj_func_iommu = अणु
	.dtor = gk20a_instobj_dtor_iommu,
	.target = gk20a_instobj_target,
	.page = gk20a_instobj_page,
	.addr = gk20a_instobj_addr,
	.size = gk20a_instobj_size,
	.acquire = gk20a_instobj_acquire_iommu,
	.release = gk20a_instobj_release_iommu,
	.map = gk20a_instobj_map,
पूर्ण;

अटल स्थिर काष्ठा nvkm_memory_ptrs
gk20a_instobj_ptrs = अणु
	.rd32 = gk20a_instobj_rd32,
	.wr32 = gk20a_instobj_wr32,
पूर्ण;

अटल पूर्णांक
gk20a_instobj_ctor_dma(काष्ठा gk20a_insपंचांगem *imem, u32 npages, u32 align,
		       काष्ठा gk20a_instobj **_node)
अणु
	काष्ठा gk20a_instobj_dma *node;
	काष्ठा nvkm_subdev *subdev = &imem->base.subdev;
	काष्ठा device *dev = subdev->device->dev;

	अगर (!(node = kzalloc(माप(*node), GFP_KERNEL)))
		वापस -ENOMEM;
	*_node = &node->base;

	nvkm_memory_ctor(&gk20a_instobj_func_dma, &node->base.memory);
	node->base.memory.ptrs = &gk20a_instobj_ptrs;

	node->base.vaddr = dma_alloc_attrs(dev, npages << PAGE_SHIFT,
					   &node->handle, GFP_KERNEL,
					   imem->attrs);
	अगर (!node->base.vaddr) अणु
		nvkm_error(subdev, "cannot allocate DMA memory\n");
		वापस -ENOMEM;
	पूर्ण

	/* alignment check */
	अगर (unlikely(node->handle & (align - 1)))
		nvkm_warn(subdev,
			  "memory not aligned as requested: %pad (0x%x)\n",
			  &node->handle, align);

	/* present memory क्रम being mapped using small pages */
	node->r.type = 12;
	node->r.offset = node->handle >> 12;
	node->r.length = (npages << PAGE_SHIFT) >> 12;

	node->base.mn = &node->r;
	वापस 0;
पूर्ण

अटल पूर्णांक
gk20a_instobj_ctor_iommu(काष्ठा gk20a_insपंचांगem *imem, u32 npages, u32 align,
			 काष्ठा gk20a_instobj **_node)
अणु
	काष्ठा gk20a_instobj_iommu *node;
	काष्ठा nvkm_subdev *subdev = &imem->base.subdev;
	काष्ठा device *dev = subdev->device->dev;
	काष्ठा nvkm_mm_node *r;
	पूर्णांक ret;
	पूर्णांक i;

	/*
	 * despite their variable size, insपंचांगem allocations are small enough
	 * (< 1 page) to be handled by kzalloc
	 */
	अगर (!(node = kzalloc(माप(*node) + ((माप(node->pages[0]) +
			     माप(*node->dma_addrs)) * npages), GFP_KERNEL)))
		वापस -ENOMEM;
	*_node = &node->base;
	node->dma_addrs = (व्योम *)(node->pages + npages);

	nvkm_memory_ctor(&gk20a_instobj_func_iommu, &node->base.memory);
	node->base.memory.ptrs = &gk20a_instobj_ptrs;

	/* Allocate backing memory */
	क्रम (i = 0; i < npages; i++) अणु
		काष्ठा page *p = alloc_page(GFP_KERNEL);
		dma_addr_t dma_adr;

		अगर (p == शून्य) अणु
			ret = -ENOMEM;
			जाओ मुक्त_pages;
		पूर्ण
		node->pages[i] = p;
		dma_adr = dma_map_page(dev, p, 0, PAGE_SIZE, DMA_BIसूचीECTIONAL);
		अगर (dma_mapping_error(dev, dma_adr)) अणु
			nvkm_error(subdev, "DMA mapping error!\n");
			ret = -ENOMEM;
			जाओ मुक्त_pages;
		पूर्ण
		node->dma_addrs[i] = dma_adr;
	पूर्ण

	mutex_lock(imem->mm_mutex);
	/* Reserve area from GPU address space */
	ret = nvkm_mm_head(imem->mm, 0, 1, npages, npages,
			   align >> imem->iommu_pgshअगरt, &r);
	mutex_unlock(imem->mm_mutex);
	अगर (ret) अणु
		nvkm_error(subdev, "IOMMU space is full!\n");
		जाओ मुक्त_pages;
	पूर्ण

	/* Map पूर्णांकo GPU address space */
	क्रम (i = 0; i < npages; i++) अणु
		u32 offset = (r->offset + i) << imem->iommu_pgshअगरt;

		ret = iommu_map(imem->करोमुख्य, offset, node->dma_addrs[i],
				PAGE_SIZE, IOMMU_READ | IOMMU_WRITE);
		अगर (ret < 0) अणु
			nvkm_error(subdev, "IOMMU mapping failure: %d\n", ret);

			जबतक (i-- > 0) अणु
				offset -= PAGE_SIZE;
				iommu_unmap(imem->करोमुख्य, offset, PAGE_SIZE);
			पूर्ण
			जाओ release_area;
		पूर्ण
	पूर्ण

	/* IOMMU bit tells that an address is to be resolved through the IOMMU */
	r->offset |= BIT(imem->iommu_bit - imem->iommu_pgshअगरt);

	node->base.mn = r;
	वापस 0;

release_area:
	mutex_lock(imem->mm_mutex);
	nvkm_mm_मुक्त(imem->mm, &r);
	mutex_unlock(imem->mm_mutex);

मुक्त_pages:
	क्रम (i = 0; i < npages && node->pages[i] != शून्य; i++) अणु
		dma_addr_t dma_addr = node->dma_addrs[i];
		अगर (dma_addr)
			dma_unmap_page(dev, dma_addr, PAGE_SIZE,
				       DMA_BIसूचीECTIONAL);
		__मुक्त_page(node->pages[i]);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक
gk20a_instobj_new(काष्ठा nvkm_insपंचांगem *base, u32 size, u32 align, bool zero,
		  काष्ठा nvkm_memory **pmemory)
अणु
	काष्ठा gk20a_insपंचांगem *imem = gk20a_insपंचांगem(base);
	काष्ठा nvkm_subdev *subdev = &imem->base.subdev;
	काष्ठा gk20a_instobj *node = शून्य;
	पूर्णांक ret;

	nvkm_debug(subdev, "%s (%s): size: %x align: %x\n", __func__,
		   imem->करोमुख्य ? "IOMMU" : "DMA", size, align);

	/* Round size and align to page bounds */
	size = max(roundup(size, PAGE_SIZE), PAGE_SIZE);
	align = max(roundup(align, PAGE_SIZE), PAGE_SIZE);

	अगर (imem->करोमुख्य)
		ret = gk20a_instobj_ctor_iommu(imem, size >> PAGE_SHIFT,
					       align, &node);
	अन्यथा
		ret = gk20a_instobj_ctor_dma(imem, size >> PAGE_SHIFT,
					     align, &node);
	*pmemory = node ? &node->memory : शून्य;
	अगर (ret)
		वापस ret;

	node->imem = imem;

	nvkm_debug(subdev, "alloc size: 0x%x, align: 0x%x, gaddr: 0x%llx\n",
		   size, align, (u64)node->mn->offset << 12);

	वापस 0;
पूर्ण

अटल व्योम *
gk20a_insपंचांगem_dtor(काष्ठा nvkm_insपंचांगem *base)
अणु
	काष्ठा gk20a_insपंचांगem *imem = gk20a_insपंचांगem(base);

	/* perक्रमm some sanity checks... */
	अगर (!list_empty(&imem->vaddr_lru))
		nvkm_warn(&base->subdev, "instobj LRU not empty!\n");

	अगर (imem->vaddr_use != 0)
		nvkm_warn(&base->subdev, "instobj vmap area not empty! "
			  "0x%x bytes still mapped\n", imem->vaddr_use);

	वापस imem;
पूर्ण

अटल स्थिर काष्ठा nvkm_insपंचांगem_func
gk20a_insपंचांगem = अणु
	.dtor = gk20a_insपंचांगem_dtor,
	.memory_new = gk20a_instobj_new,
	.zero = false,
पूर्ण;

पूर्णांक
gk20a_insपंचांगem_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
		  काष्ठा nvkm_insपंचांगem **pimem)
अणु
	काष्ठा nvkm_device_tegra *tdev = device->func->tegra(device);
	काष्ठा gk20a_insपंचांगem *imem;

	अगर (!(imem = kzalloc(माप(*imem), GFP_KERNEL)))
		वापस -ENOMEM;
	nvkm_insपंचांगem_ctor(&gk20a_insपंचांगem, device, type, inst, &imem->base);
	mutex_init(&imem->lock);
	*pimem = &imem->base;

	/* करो not allow more than 1MB of CPU-mapped insपंचांगem */
	imem->vaddr_use = 0;
	imem->vaddr_max = 0x100000;
	INIT_LIST_HEAD(&imem->vaddr_lru);

	अगर (tdev->iommu.करोमुख्य) अणु
		imem->mm_mutex = &tdev->iommu.mutex;
		imem->mm = &tdev->iommu.mm;
		imem->करोमुख्य = tdev->iommu.करोमुख्य;
		imem->iommu_pgshअगरt = tdev->iommu.pgshअगरt;
		imem->iommu_bit = tdev->func->iommu_bit;

		nvkm_info(&imem->base.subdev, "using IOMMU\n");
	पूर्ण अन्यथा अणु
		imem->attrs = DMA_ATTR_WEAK_ORDERING |
			      DMA_ATTR_WRITE_COMBINE;

		nvkm_info(&imem->base.subdev, "using DMA API\n");
	पूर्ण

	वापस 0;
पूर्ण
