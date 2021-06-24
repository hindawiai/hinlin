<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Coherent per-device memory handling.
 * Borrowed from i386
 */
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/dma-direct.h>
#समावेश <linux/dma-map-ops.h>

काष्ठा dma_coherent_mem अणु
	व्योम		*virt_base;
	dma_addr_t	device_base;
	अचिन्हित दीर्घ	pfn_base;
	पूर्णांक		size;
	अचिन्हित दीर्घ	*biपंचांगap;
	spinlock_t	spinlock;
	bool		use_dev_dma_pfn_offset;
पूर्ण;

अटल काष्ठा dma_coherent_mem *dma_coherent_शेष_memory __ro_after_init;

अटल अंतरभूत काष्ठा dma_coherent_mem *dev_get_coherent_memory(काष्ठा device *dev)
अणु
	अगर (dev && dev->dma_mem)
		वापस dev->dma_mem;
	वापस शून्य;
पूर्ण

अटल अंतरभूत dma_addr_t dma_get_device_base(काष्ठा device *dev,
					     काष्ठा dma_coherent_mem * mem)
अणु
	अगर (mem->use_dev_dma_pfn_offset)
		वापस phys_to_dma(dev, PFN_PHYS(mem->pfn_base));
	वापस mem->device_base;
पूर्ण

अटल पूर्णांक dma_init_coherent_memory(phys_addr_t phys_addr,
		dma_addr_t device_addr, माप_प्रकार size,
		काष्ठा dma_coherent_mem **mem)
अणु
	काष्ठा dma_coherent_mem *dma_mem = शून्य;
	व्योम *mem_base = शून्य;
	पूर्णांक pages = size >> PAGE_SHIFT;
	पूर्णांक biपंचांगap_size = BITS_TO_LONGS(pages) * माप(दीर्घ);
	पूर्णांक ret;

	अगर (!size) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	mem_base = memremap(phys_addr, size, MEMREMAP_WC);
	अगर (!mem_base) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण
	dma_mem = kzalloc(माप(काष्ठा dma_coherent_mem), GFP_KERNEL);
	अगर (!dma_mem) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण
	dma_mem->biपंचांगap = kzalloc(biपंचांगap_size, GFP_KERNEL);
	अगर (!dma_mem->biपंचांगap) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	dma_mem->virt_base = mem_base;
	dma_mem->device_base = device_addr;
	dma_mem->pfn_base = PFN_DOWN(phys_addr);
	dma_mem->size = pages;
	spin_lock_init(&dma_mem->spinlock);

	*mem = dma_mem;
	वापस 0;

out:
	kमुक्त(dma_mem);
	अगर (mem_base)
		memunmap(mem_base);
	वापस ret;
पूर्ण

अटल व्योम dma_release_coherent_memory(काष्ठा dma_coherent_mem *mem)
अणु
	अगर (!mem)
		वापस;

	memunmap(mem->virt_base);
	kमुक्त(mem->biपंचांगap);
	kमुक्त(mem);
पूर्ण

अटल पूर्णांक dma_assign_coherent_memory(काष्ठा device *dev,
				      काष्ठा dma_coherent_mem *mem)
अणु
	अगर (!dev)
		वापस -ENODEV;

	अगर (dev->dma_mem)
		वापस -EBUSY;

	dev->dma_mem = mem;
	वापस 0;
पूर्ण

/*
 * Declare a region of memory to be handed out by dma_alloc_coherent() when it
 * is asked क्रम coherent memory क्रम this device.  This shall only be used
 * from platक्रमm code, usually based on the device tree description.
 * 
 * phys_addr is the CPU physical address to which the memory is currently
 * asचिन्हित (this will be ioremapped so the CPU can access the region).
 *
 * device_addr is the DMA address the device needs to be programmed with to
 * actually address this memory (this will be handed out as the dma_addr_t in
 * dma_alloc_coherent()).
 *
 * size is the size of the area (must be a multiple of PAGE_SIZE).
 *
 * As a simplअगरication क्रम the platक्रमms, only *one* such region of memory may
 * be declared per device.
 */
पूर्णांक dma_declare_coherent_memory(काष्ठा device *dev, phys_addr_t phys_addr,
				dma_addr_t device_addr, माप_प्रकार size)
अणु
	काष्ठा dma_coherent_mem *mem;
	पूर्णांक ret;

	ret = dma_init_coherent_memory(phys_addr, device_addr, size, &mem);
	अगर (ret)
		वापस ret;

	ret = dma_assign_coherent_memory(dev, mem);
	अगर (ret)
		dma_release_coherent_memory(mem);
	वापस ret;
पूर्ण

अटल व्योम *__dma_alloc_from_coherent(काष्ठा device *dev,
				       काष्ठा dma_coherent_mem *mem,
				       sमाप_प्रकार size, dma_addr_t *dma_handle)
अणु
	पूर्णांक order = get_order(size);
	अचिन्हित दीर्घ flags;
	पूर्णांक pageno;
	व्योम *ret;

	spin_lock_irqsave(&mem->spinlock, flags);

	अगर (unlikely(size > ((dma_addr_t)mem->size << PAGE_SHIFT)))
		जाओ err;

	pageno = biपंचांगap_find_मुक्त_region(mem->biपंचांगap, mem->size, order);
	अगर (unlikely(pageno < 0))
		जाओ err;

	/*
	 * Memory was found in the coherent area.
	 */
	*dma_handle = dma_get_device_base(dev, mem) +
			((dma_addr_t)pageno << PAGE_SHIFT);
	ret = mem->virt_base + ((dma_addr_t)pageno << PAGE_SHIFT);
	spin_unlock_irqrestore(&mem->spinlock, flags);
	स_रखो(ret, 0, size);
	वापस ret;
err:
	spin_unlock_irqrestore(&mem->spinlock, flags);
	वापस शून्य;
पूर्ण

/**
 * dma_alloc_from_dev_coherent() - allocate memory from device coherent pool
 * @dev:	device from which we allocate memory
 * @size:	size of requested memory area
 * @dma_handle:	This will be filled with the correct dma handle
 * @ret:	This poपूर्णांकer will be filled with the भव address
 *		to allocated area.
 *
 * This function should be only called from per-arch dma_alloc_coherent()
 * to support allocation from per-device coherent memory pools.
 *
 * Returns 0 अगर dma_alloc_coherent should जारी with allocating from
 * generic memory areas, or !0 अगर dma_alloc_coherent should वापस @ret.
 */
पूर्णांक dma_alloc_from_dev_coherent(काष्ठा device *dev, sमाप_प्रकार size,
		dma_addr_t *dma_handle, व्योम **ret)
अणु
	काष्ठा dma_coherent_mem *mem = dev_get_coherent_memory(dev);

	अगर (!mem)
		वापस 0;

	*ret = __dma_alloc_from_coherent(dev, mem, size, dma_handle);
	वापस 1;
पूर्ण

व्योम *dma_alloc_from_global_coherent(काष्ठा device *dev, sमाप_प्रकार size,
				     dma_addr_t *dma_handle)
अणु
	अगर (!dma_coherent_शेष_memory)
		वापस शून्य;

	वापस __dma_alloc_from_coherent(dev, dma_coherent_शेष_memory, size,
					 dma_handle);
पूर्ण

अटल पूर्णांक __dma_release_from_coherent(काष्ठा dma_coherent_mem *mem,
				       पूर्णांक order, व्योम *vaddr)
अणु
	अगर (mem && vaddr >= mem->virt_base && vaddr <
		   (mem->virt_base + ((dma_addr_t)mem->size << PAGE_SHIFT))) अणु
		पूर्णांक page = (vaddr - mem->virt_base) >> PAGE_SHIFT;
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(&mem->spinlock, flags);
		biपंचांगap_release_region(mem->biपंचांगap, page, order);
		spin_unlock_irqrestore(&mem->spinlock, flags);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * dma_release_from_dev_coherent() - मुक्त memory to device coherent memory pool
 * @dev:	device from which the memory was allocated
 * @order:	the order of pages allocated
 * @vaddr:	भव address of allocated pages
 *
 * This checks whether the memory was allocated from the per-device
 * coherent memory pool and अगर so, releases that memory.
 *
 * Returns 1 अगर we correctly released the memory, or 0 अगर the caller should
 * proceed with releasing memory from generic pools.
 */
पूर्णांक dma_release_from_dev_coherent(काष्ठा device *dev, पूर्णांक order, व्योम *vaddr)
अणु
	काष्ठा dma_coherent_mem *mem = dev_get_coherent_memory(dev);

	वापस __dma_release_from_coherent(mem, order, vaddr);
पूर्ण

पूर्णांक dma_release_from_global_coherent(पूर्णांक order, व्योम *vaddr)
अणु
	अगर (!dma_coherent_शेष_memory)
		वापस 0;

	वापस __dma_release_from_coherent(dma_coherent_शेष_memory, order,
			vaddr);
पूर्ण

अटल पूर्णांक __dma_mmap_from_coherent(काष्ठा dma_coherent_mem *mem,
		काष्ठा vm_area_काष्ठा *vma, व्योम *vaddr, माप_प्रकार size, पूर्णांक *ret)
अणु
	अगर (mem && vaddr >= mem->virt_base && vaddr + size <=
		   (mem->virt_base + ((dma_addr_t)mem->size << PAGE_SHIFT))) अणु
		अचिन्हित दीर्घ off = vma->vm_pgoff;
		पूर्णांक start = (vaddr - mem->virt_base) >> PAGE_SHIFT;
		अचिन्हित दीर्घ user_count = vma_pages(vma);
		पूर्णांक count = PAGE_ALIGN(size) >> PAGE_SHIFT;

		*ret = -ENXIO;
		अगर (off < count && user_count <= count - off) अणु
			अचिन्हित दीर्घ pfn = mem->pfn_base + start + off;
			*ret = remap_pfn_range(vma, vma->vm_start, pfn,
					       user_count << PAGE_SHIFT,
					       vma->vm_page_prot);
		पूर्ण
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * dma_mmap_from_dev_coherent() - mmap memory from the device coherent pool
 * @dev:	device from which the memory was allocated
 * @vma:	vm_area क्रम the userspace memory
 * @vaddr:	cpu address वापसed by dma_alloc_from_dev_coherent
 * @size:	size of the memory buffer allocated
 * @ret:	result from remap_pfn_range()
 *
 * This checks whether the memory was allocated from the per-device
 * coherent memory pool and अगर so, maps that memory to the provided vma.
 *
 * Returns 1 अगर @vaddr beदीर्घs to the device coherent pool and the caller
 * should वापस @ret, or 0 अगर they should proceed with mapping memory from
 * generic areas.
 */
पूर्णांक dma_mmap_from_dev_coherent(काष्ठा device *dev, काष्ठा vm_area_काष्ठा *vma,
			   व्योम *vaddr, माप_प्रकार size, पूर्णांक *ret)
अणु
	काष्ठा dma_coherent_mem *mem = dev_get_coherent_memory(dev);

	वापस __dma_mmap_from_coherent(mem, vma, vaddr, size, ret);
पूर्ण

पूर्णांक dma_mmap_from_global_coherent(काष्ठा vm_area_काष्ठा *vma, व्योम *vaddr,
				   माप_प्रकार size, पूर्णांक *ret)
अणु
	अगर (!dma_coherent_शेष_memory)
		वापस 0;

	वापस __dma_mmap_from_coherent(dma_coherent_शेष_memory, vma,
					vaddr, size, ret);
पूर्ण

/*
 * Support क्रम reserved memory regions defined in device tree
 */
#अगर_घोषित CONFIG_OF_RESERVED_MEM
#समावेश <linux/of.h>
#समावेश <linux/of_fdt.h>
#समावेश <linux/of_reserved_स्मृति.स>

अटल काष्ठा reserved_mem *dma_reserved_शेष_memory __initdata;

अटल पूर्णांक rmem_dma_device_init(काष्ठा reserved_mem *rmem, काष्ठा device *dev)
अणु
	काष्ठा dma_coherent_mem *mem = rmem->priv;
	पूर्णांक ret;

	अगर (!mem) अणु
		ret = dma_init_coherent_memory(rmem->base, rmem->base,
					       rmem->size, &mem);
		अगर (ret) अणु
			pr_err("Reserved memory: failed to init DMA memory pool at %pa, size %ld MiB\n",
				&rmem->base, (अचिन्हित दीर्घ)rmem->size / SZ_1M);
			वापस ret;
		पूर्ण
	पूर्ण
	mem->use_dev_dma_pfn_offset = true;
	rmem->priv = mem;
	dma_assign_coherent_memory(dev, mem);
	वापस 0;
पूर्ण

अटल व्योम rmem_dma_device_release(काष्ठा reserved_mem *rmem,
				    काष्ठा device *dev)
अणु
	अगर (dev)
		dev->dma_mem = शून्य;
पूर्ण

अटल स्थिर काष्ठा reserved_mem_ops rmem_dma_ops = अणु
	.device_init	= rmem_dma_device_init,
	.device_release	= rmem_dma_device_release,
पूर्ण;

अटल पूर्णांक __init rmem_dma_setup(काष्ठा reserved_mem *rmem)
अणु
	अचिन्हित दीर्घ node = rmem->fdt_node;

	अगर (of_get_flat_dt_prop(node, "reusable", शून्य))
		वापस -EINVAL;

#अगर_घोषित CONFIG_ARM
	अगर (!of_get_flat_dt_prop(node, "no-map", शून्य)) अणु
		pr_err("Reserved memory: regions without no-map are not yet supported\n");
		वापस -EINVAL;
	पूर्ण

	अगर (of_get_flat_dt_prop(node, "linux,dma-default", शून्य)) अणु
		WARN(dma_reserved_शेष_memory,
		     "Reserved memory: region for default DMA coherent area is redefined\n");
		dma_reserved_शेष_memory = rmem;
	पूर्ण
#पूर्ण_अगर

	rmem->ops = &rmem_dma_ops;
	pr_info("Reserved memory: created DMA memory pool at %pa, size %ld MiB\n",
		&rmem->base, (अचिन्हित दीर्घ)rmem->size / SZ_1M);
	वापस 0;
पूर्ण

अटल पूर्णांक __init dma_init_reserved_memory(व्योम)
अणु
	स्थिर काष्ठा reserved_mem_ops *ops;
	पूर्णांक ret;

	अगर (!dma_reserved_शेष_memory)
		वापस -ENOMEM;

	ops = dma_reserved_शेष_memory->ops;

	/*
	 * We rely on rmem_dma_device_init() करोes not propagate error of
	 * dma_assign_coherent_memory() क्रम "NULL" device.
	 */
	ret = ops->device_init(dma_reserved_शेष_memory, शून्य);

	अगर (!ret) अणु
		dma_coherent_शेष_memory = dma_reserved_शेष_memory->priv;
		pr_info("DMA: default coherent area is set\n");
	पूर्ण

	वापस ret;
पूर्ण

core_initcall(dma_init_reserved_memory);

RESERVEDMEM_OF_DECLARE(dma, "shared-dma-pool", rmem_dma_setup);
#पूर्ण_अगर
