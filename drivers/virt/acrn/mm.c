<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ACRN: Memory mapping management
 *
 * Copyright (C) 2020 Intel Corporation. All rights reserved.
 *
 * Authors:
 *	Fei Li <lei1.li@पूर्णांकel.com>
 *	Shuo Liu <shuo.a.liu@पूर्णांकel.com>
 */

#समावेश <linux/पन.स>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>

#समावेश "acrn_drv.h"

अटल पूर्णांक modअगरy_region(काष्ठा acrn_vm *vm, काष्ठा vm_memory_region_op *region)
अणु
	काष्ठा vm_memory_region_batch *regions;
	पूर्णांक ret;

	regions = kzalloc(माप(*regions), GFP_KERNEL);
	अगर (!regions)
		वापस -ENOMEM;

	regions->vmid = vm->vmid;
	regions->regions_num = 1;
	regions->regions_gpa = virt_to_phys(region);

	ret = hcall_set_memory_regions(virt_to_phys(regions));
	अगर (ret < 0)
		dev_dbg(acrn_dev.this_device,
			"Failed to set memory region for VM[%u]!\n", vm->vmid);

	kमुक्त(regions);
	वापस ret;
पूर्ण

/**
 * acrn_mm_region_add() - Set up the EPT mapping of a memory region.
 * @vm:			User VM.
 * @user_gpa:		A GPA of User VM.
 * @service_gpa:	A GPA of Service VM.
 * @size:		Size of the region.
 * @mem_type:		Combination of ACRN_MEM_TYPE_*.
 * @mem_access_right:	Combination of ACRN_MEM_ACCESS_*.
 *
 * Return: 0 on success, <0 on error.
 */
पूर्णांक acrn_mm_region_add(काष्ठा acrn_vm *vm, u64 user_gpa, u64 service_gpa,
		       u64 size, u32 mem_type, u32 mem_access_right)
अणु
	काष्ठा vm_memory_region_op *region;
	पूर्णांक ret = 0;

	region = kzalloc(माप(*region), GFP_KERNEL);
	अगर (!region)
		वापस -ENOMEM;

	region->type = ACRN_MEM_REGION_ADD;
	region->user_vm_pa = user_gpa;
	region->service_vm_pa = service_gpa;
	region->size = size;
	region->attr = ((mem_type & ACRN_MEM_TYPE_MASK) |
			(mem_access_right & ACRN_MEM_ACCESS_RIGHT_MASK));
	ret = modअगरy_region(vm, region);

	dev_dbg(acrn_dev.this_device,
		"%s: user-GPA[%pK] service-GPA[%pK] size[0x%llx].\n",
		__func__, (व्योम *)user_gpa, (व्योम *)service_gpa, size);
	kमुक्त(region);
	वापस ret;
पूर्ण

/**
 * acrn_mm_region_del() - Del the EPT mapping of a memory region.
 * @vm:		User VM.
 * @user_gpa:	A GPA of the User VM.
 * @size:	Size of the region.
 *
 * Return: 0 on success, <0 क्रम error.
 */
पूर्णांक acrn_mm_region_del(काष्ठा acrn_vm *vm, u64 user_gpa, u64 size)
अणु
	काष्ठा vm_memory_region_op *region;
	पूर्णांक ret = 0;

	region = kzalloc(माप(*region), GFP_KERNEL);
	अगर (!region)
		वापस -ENOMEM;

	region->type = ACRN_MEM_REGION_DEL;
	region->user_vm_pa = user_gpa;
	region->service_vm_pa = 0UL;
	region->size = size;
	region->attr = 0U;

	ret = modअगरy_region(vm, region);

	dev_dbg(acrn_dev.this_device, "%s: user-GPA[%pK] size[0x%llx].\n",
		__func__, (व्योम *)user_gpa, size);
	kमुक्त(region);
	वापस ret;
पूर्ण

पूर्णांक acrn_vm_memseg_map(काष्ठा acrn_vm *vm, काष्ठा acrn_vm_memmap *memmap)
अणु
	पूर्णांक ret;

	अगर (memmap->type == ACRN_MEMMAP_RAM)
		वापस acrn_vm_ram_map(vm, memmap);

	अगर (memmap->type != ACRN_MEMMAP_MMIO) अणु
		dev_dbg(acrn_dev.this_device,
			"Invalid memmap type: %u\n", memmap->type);
		वापस -EINVAL;
	पूर्ण

	ret = acrn_mm_region_add(vm, memmap->user_vm_pa,
				 memmap->service_vm_pa, memmap->len,
				 ACRN_MEM_TYPE_UC, memmap->attr);
	अगर (ret < 0)
		dev_dbg(acrn_dev.this_device,
			"Add memory region failed, VM[%u]!\n", vm->vmid);

	वापस ret;
पूर्ण

पूर्णांक acrn_vm_memseg_unmap(काष्ठा acrn_vm *vm, काष्ठा acrn_vm_memmap *memmap)
अणु
	पूर्णांक ret;

	अगर (memmap->type != ACRN_MEMMAP_MMIO) अणु
		dev_dbg(acrn_dev.this_device,
			"Invalid memmap type: %u\n", memmap->type);
		वापस -EINVAL;
	पूर्ण

	ret = acrn_mm_region_del(vm, memmap->user_vm_pa, memmap->len);
	अगर (ret < 0)
		dev_dbg(acrn_dev.this_device,
			"Del memory region failed, VM[%u]!\n", vm->vmid);

	वापस ret;
पूर्ण

/**
 * acrn_vm_ram_map() - Create a RAM EPT mapping of User VM.
 * @vm:		The User VM poपूर्णांकer
 * @memmap:	Info of the EPT mapping
 *
 * Return: 0 on success, <0 क्रम error.
 */
पूर्णांक acrn_vm_ram_map(काष्ठा acrn_vm *vm, काष्ठा acrn_vm_memmap *memmap)
अणु
	काष्ठा vm_memory_region_batch *regions_info;
	पूर्णांक nr_pages, i = 0, order, nr_regions = 0;
	काष्ठा vm_memory_mapping *region_mapping;
	काष्ठा vm_memory_region_op *vm_region;
	काष्ठा page **pages = शून्य, *page;
	व्योम *remap_vaddr;
	पूर्णांक ret, pinned;
	u64 user_vm_pa;

	अगर (!vm || !memmap)
		वापस -EINVAL;

	/* Get the page number of the map region */
	nr_pages = memmap->len >> PAGE_SHIFT;
	pages = vzalloc(nr_pages * माप(काष्ठा page *));
	अगर (!pages)
		वापस -ENOMEM;

	/* Lock the pages of user memory map region */
	pinned = pin_user_pages_fast(memmap->vma_base,
				     nr_pages, FOLL_WRITE | FOLL_LONGTERM,
				     pages);
	अगर (pinned < 0) अणु
		ret = pinned;
		जाओ मुक्त_pages;
	पूर्ण अन्यथा अगर (pinned != nr_pages) अणु
		ret = -EFAULT;
		जाओ put_pages;
	पूर्ण

	/* Create a kernel map क्रम the map region */
	remap_vaddr = vmap(pages, nr_pages, VM_MAP, PAGE_KERNEL);
	अगर (!remap_vaddr) अणु
		ret = -ENOMEM;
		जाओ put_pages;
	पूर्ण

	/* Record Service VM va <-> User VM pa mapping */
	mutex_lock(&vm->regions_mapping_lock);
	region_mapping = &vm->regions_mapping[vm->regions_mapping_count];
	अगर (vm->regions_mapping_count < ACRN_MEM_MAPPING_MAX) अणु
		region_mapping->pages = pages;
		region_mapping->npages = nr_pages;
		region_mapping->size = memmap->len;
		region_mapping->service_vm_va = remap_vaddr;
		region_mapping->user_vm_pa = memmap->user_vm_pa;
		vm->regions_mapping_count++;
	पूर्ण अन्यथा अणु
		dev_warn(acrn_dev.this_device,
			"Run out of memory mapping slots!\n");
		ret = -ENOMEM;
		mutex_unlock(&vm->regions_mapping_lock);
		जाओ unmap_no_count;
	पूर्ण
	mutex_unlock(&vm->regions_mapping_lock);

	/* Calculate count of vm_memory_region_op */
	जबतक (i < nr_pages) अणु
		page = pages[i];
		VM_BUG_ON_PAGE(PageTail(page), page);
		order = compound_order(page);
		nr_regions++;
		i += 1 << order;
	पूर्ण

	/* Prepare the vm_memory_region_batch */
	regions_info = kzalloc(माप(*regions_info) +
			       माप(*vm_region) * nr_regions,
			       GFP_KERNEL);
	अगर (!regions_info) अणु
		ret = -ENOMEM;
		जाओ unmap_kernel_map;
	पूर्ण

	/* Fill each vm_memory_region_op */
	vm_region = (काष्ठा vm_memory_region_op *)(regions_info + 1);
	regions_info->vmid = vm->vmid;
	regions_info->regions_num = nr_regions;
	regions_info->regions_gpa = virt_to_phys(vm_region);
	user_vm_pa = memmap->user_vm_pa;
	i = 0;
	जबतक (i < nr_pages) अणु
		u32 region_size;

		page = pages[i];
		VM_BUG_ON_PAGE(PageTail(page), page);
		order = compound_order(page);
		region_size = PAGE_SIZE << order;
		vm_region->type = ACRN_MEM_REGION_ADD;
		vm_region->user_vm_pa = user_vm_pa;
		vm_region->service_vm_pa = page_to_phys(page);
		vm_region->size = region_size;
		vm_region->attr = (ACRN_MEM_TYPE_WB & ACRN_MEM_TYPE_MASK) |
				  (memmap->attr & ACRN_MEM_ACCESS_RIGHT_MASK);

		vm_region++;
		user_vm_pa += region_size;
		i += 1 << order;
	पूर्ण

	/* Inक्रमm the ACRN Hypervisor to set up EPT mappings */
	ret = hcall_set_memory_regions(virt_to_phys(regions_info));
	अगर (ret < 0) अणु
		dev_dbg(acrn_dev.this_device,
			"Failed to set regions, VM[%u]!\n", vm->vmid);
		जाओ unset_region;
	पूर्ण
	kमुक्त(regions_info);

	dev_dbg(acrn_dev.this_device,
		"%s: VM[%u] service-GVA[%pK] user-GPA[%pK] size[0x%llx]\n",
		__func__, vm->vmid,
		remap_vaddr, (व्योम *)memmap->user_vm_pa, memmap->len);
	वापस ret;

unset_region:
	kमुक्त(regions_info);
unmap_kernel_map:
	mutex_lock(&vm->regions_mapping_lock);
	vm->regions_mapping_count--;
	mutex_unlock(&vm->regions_mapping_lock);
unmap_no_count:
	vunmap(remap_vaddr);
put_pages:
	क्रम (i = 0; i < pinned; i++)
		unpin_user_page(pages[i]);
मुक्त_pages:
	vमुक्त(pages);
	वापस ret;
पूर्ण

/**
 * acrn_vm_all_ram_unmap() - Destroy a RAM EPT mapping of User VM.
 * @vm:	The User VM
 */
व्योम acrn_vm_all_ram_unmap(काष्ठा acrn_vm *vm)
अणु
	काष्ठा vm_memory_mapping *region_mapping;
	पूर्णांक i, j;

	mutex_lock(&vm->regions_mapping_lock);
	क्रम (i = 0; i < vm->regions_mapping_count; i++) अणु
		region_mapping = &vm->regions_mapping[i];
		vunmap(region_mapping->service_vm_va);
		क्रम (j = 0; j < region_mapping->npages; j++)
			unpin_user_page(region_mapping->pages[j]);
		vमुक्त(region_mapping->pages);
	पूर्ण
	mutex_unlock(&vm->regions_mapping_lock);
पूर्ण
