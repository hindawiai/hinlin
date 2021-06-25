<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2014 The Linux Foundation
 */
#समावेश <linux/dma-map-ops.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>

काष्ठा page **dma_common_find_pages(व्योम *cpu_addr)
अणु
	काष्ठा vm_काष्ठा *area = find_vm_area(cpu_addr);

	अगर (!area || area->flags != VM_DMA_COHERENT)
		वापस शून्य;
	वापस area->pages;
पूर्ण

/*
 * Remaps an array of PAGE_SIZE pages पूर्णांकo another vm_area.
 * Cannot be used in non-sleeping contexts
 */
व्योम *dma_common_pages_remap(काष्ठा page **pages, माप_प्रकार size,
			 pgprot_t prot, स्थिर व्योम *caller)
अणु
	व्योम *vaddr;

	vaddr = vmap(pages, PAGE_ALIGN(size) >> PAGE_SHIFT,
		     VM_DMA_COHERENT, prot);
	अगर (vaddr)
		find_vm_area(vaddr)->pages = pages;
	वापस vaddr;
पूर्ण

/*
 * Remaps an allocated contiguous region पूर्णांकo another vm_area.
 * Cannot be used in non-sleeping contexts
 */
व्योम *dma_common_contiguous_remap(काष्ठा page *page, माप_प्रकार size,
			pgprot_t prot, स्थिर व्योम *caller)
अणु
	पूर्णांक count = PAGE_ALIGN(size) >> PAGE_SHIFT;
	काष्ठा page **pages;
	व्योम *vaddr;
	पूर्णांक i;

	pages = kदो_स्मृति_array(count, माप(काष्ठा page *), GFP_KERNEL);
	अगर (!pages)
		वापस शून्य;
	क्रम (i = 0; i < count; i++)
		pages[i] = nth_page(page, i);
	vaddr = vmap(pages, count, VM_DMA_COHERENT, prot);
	kमुक्त(pages);

	वापस vaddr;
पूर्ण

/*
 * Unmaps a range previously mapped by dma_common_*_remap
 */
व्योम dma_common_मुक्त_remap(व्योम *cpu_addr, माप_प्रकार size)
अणु
	काष्ठा vm_काष्ठा *area = find_vm_area(cpu_addr);

	अगर (!area || area->flags != VM_DMA_COHERENT) अणु
		WARN(1, "trying to free invalid coherent area: %p\n", cpu_addr);
		वापस;
	पूर्ण

	vunmap(cpu_addr);
पूर्ण
