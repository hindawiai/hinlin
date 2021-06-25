<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR MIT
/*
 * Copyright (c) 2007-2008 Tungsten Graphics, Inc., Cedar Park, TX., USA,
 * Copyright (c) 2009 VMware, Inc., Palo Alto, CA., USA,
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sub license,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * THE COPYRIGHT HOLDERS, AUTHORS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#समावेश <linux/सीमा.स>
#समावेश <linux/swiotlb.h>

#समावेश "nouveau_drv.h"
#समावेश "nouveau_gem.h"
#समावेश "nouveau_mem.h"
#समावेश "nouveau_ttm.h"

#समावेश <drm/drm_legacy.h>

#समावेश <core/tegra.h>

अटल व्योम
nouveau_manager_del(काष्ठा tपंचांग_resource_manager *man, काष्ठा tपंचांग_resource *reg)
अणु
	nouveau_mem_del(reg);
पूर्ण

अटल पूर्णांक
nouveau_vram_manager_new(काष्ठा tपंचांग_resource_manager *man,
			 काष्ठा tपंचांग_buffer_object *bo,
			 स्थिर काष्ठा tपंचांग_place *place,
			 काष्ठा tपंचांग_resource *reg)
अणु
	काष्ठा nouveau_bo *nvbo = nouveau_bo(bo);
	काष्ठा nouveau_drm *drm = nouveau_bdev(bo->bdev);
	पूर्णांक ret;

	अगर (drm->client.device.info.ram_size == 0)
		वापस -ENOMEM;

	ret = nouveau_mem_new(&drm->master, nvbo->kind, nvbo->comp, reg);
	अगर (ret)
		वापस ret;

	ret = nouveau_mem_vram(reg, nvbo->contig, nvbo->page);
	अगर (ret) अणु
		nouveau_mem_del(reg);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

स्थिर काष्ठा tपंचांग_resource_manager_func nouveau_vram_manager = अणु
	.alloc = nouveau_vram_manager_new,
	.मुक्त = nouveau_manager_del,
पूर्ण;

अटल पूर्णांक
nouveau_gart_manager_new(काष्ठा tपंचांग_resource_manager *man,
			 काष्ठा tपंचांग_buffer_object *bo,
			 स्थिर काष्ठा tपंचांग_place *place,
			 काष्ठा tपंचांग_resource *reg)
अणु
	काष्ठा nouveau_bo *nvbo = nouveau_bo(bo);
	काष्ठा nouveau_drm *drm = nouveau_bdev(bo->bdev);
	पूर्णांक ret;

	ret = nouveau_mem_new(&drm->master, nvbo->kind, nvbo->comp, reg);
	अगर (ret)
		वापस ret;

	reg->start = 0;
	वापस 0;
पूर्ण

स्थिर काष्ठा tपंचांग_resource_manager_func nouveau_gart_manager = अणु
	.alloc = nouveau_gart_manager_new,
	.मुक्त = nouveau_manager_del,
पूर्ण;

अटल पूर्णांक
nv04_gart_manager_new(काष्ठा tपंचांग_resource_manager *man,
		      काष्ठा tपंचांग_buffer_object *bo,
		      स्थिर काष्ठा tपंचांग_place *place,
		      काष्ठा tपंचांग_resource *reg)
अणु
	काष्ठा nouveau_bo *nvbo = nouveau_bo(bo);
	काष्ठा nouveau_drm *drm = nouveau_bdev(bo->bdev);
	काष्ठा nouveau_mem *mem;
	पूर्णांक ret;

	ret = nouveau_mem_new(&drm->master, nvbo->kind, nvbo->comp, reg);
	mem = nouveau_mem(reg);
	अगर (ret)
		वापस ret;

	ret = nvअगर_vmm_get(&mem->cli->vmm.vmm, PTES, false, 12, 0,
			   (दीर्घ)reg->num_pages << PAGE_SHIFT, &mem->vma[0]);
	अगर (ret) अणु
		nouveau_mem_del(reg);
		वापस ret;
	पूर्ण

	reg->start = mem->vma[0].addr >> PAGE_SHIFT;
	वापस 0;
पूर्ण

स्थिर काष्ठा tपंचांग_resource_manager_func nv04_gart_manager = अणु
	.alloc = nv04_gart_manager_new,
	.मुक्त = nouveau_manager_del,
पूर्ण;

अटल vm_fault_t nouveau_tपंचांग_fault(काष्ठा vm_fault *vmf)
अणु
	काष्ठा vm_area_काष्ठा *vma = vmf->vma;
	काष्ठा tपंचांग_buffer_object *bo = vma->vm_निजी_data;
	pgprot_t prot;
	vm_fault_t ret;

	ret = tपंचांग_bo_vm_reserve(bo, vmf);
	अगर (ret)
		वापस ret;

	ret = nouveau_tपंचांग_fault_reserve_notअगरy(bo);
	अगर (ret)
		जाओ error_unlock;

	nouveau_bo_del_io_reserve_lru(bo);
	prot = vm_get_page_prot(vma->vm_flags);
	ret = tपंचांग_bo_vm_fault_reserved(vmf, prot, TTM_BO_VM_NUM_PREFAULT, 1);
	nouveau_bo_add_io_reserve_lru(bo);
	अगर (ret == VM_FAULT_RETRY && !(vmf->flags & FAULT_FLAG_RETRY_NOWAIT))
		वापस ret;

error_unlock:
	dma_resv_unlock(bo->base.resv);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा nouveau_tपंचांग_vm_ops = अणु
	.fault = nouveau_tपंचांग_fault,
	.खोलो = tपंचांग_bo_vm_खोलो,
	.बंद = tपंचांग_bo_vm_बंद,
	.access = tपंचांग_bo_vm_access
पूर्ण;

पूर्णांक
nouveau_tपंचांग_mmap(काष्ठा file *filp, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा drm_file *file_priv = filp->निजी_data;
	काष्ठा nouveau_drm *drm = nouveau_drm(file_priv->minor->dev);
	पूर्णांक ret;

	ret = tपंचांग_bo_mmap(filp, vma, &drm->tपंचांग.bdev);
	अगर (ret)
		वापस ret;

	vma->vm_ops = &nouveau_tपंचांग_vm_ops;
	वापस 0;
पूर्ण

अटल पूर्णांक
nouveau_tपंचांग_init_host(काष्ठा nouveau_drm *drm, u8 kind)
अणु
	काष्ठा nvअगर_mmu *mmu = &drm->client.mmu;
	पूर्णांक typei;

	typei = nvअगर_mmu_type(mmu, NVIF_MEM_HOST | NVIF_MEM_MAPPABLE |
					    kind | NVIF_MEM_COHERENT);
	अगर (typei < 0)
		वापस -ENOSYS;

	drm->tपंचांग.type_host[!!kind] = typei;

	typei = nvअगर_mmu_type(mmu, NVIF_MEM_HOST | NVIF_MEM_MAPPABLE | kind);
	अगर (typei < 0)
		वापस -ENOSYS;

	drm->tपंचांग.type_ncoh[!!kind] = typei;
	वापस 0;
पूर्ण

अटल पूर्णांक
nouveau_tपंचांग_init_vram(काष्ठा nouveau_drm *drm)
अणु
	अगर (drm->client.device.info.family >= NV_DEVICE_INFO_V0_TESLA) अणु
		काष्ठा tपंचांग_resource_manager *man = kzalloc(माप(*man), GFP_KERNEL);

		अगर (!man)
			वापस -ENOMEM;

		man->func = &nouveau_vram_manager;

		tपंचांग_resource_manager_init(man,
					  drm->gem.vram_available >> PAGE_SHIFT);
		tपंचांग_set_driver_manager(&drm->tपंचांग.bdev, TTM_PL_VRAM, man);
		tपंचांग_resource_manager_set_used(man, true);
		वापस 0;
	पूर्ण अन्यथा अणु
		वापस tपंचांग_range_man_init(&drm->tपंचांग.bdev, TTM_PL_VRAM, false,
					  drm->gem.vram_available >> PAGE_SHIFT);
	पूर्ण
पूर्ण

अटल व्योम
nouveau_tपंचांग_fini_vram(काष्ठा nouveau_drm *drm)
अणु
	काष्ठा tपंचांग_resource_manager *man = tपंचांग_manager_type(&drm->tपंचांग.bdev, TTM_PL_VRAM);

	अगर (drm->client.device.info.family >= NV_DEVICE_INFO_V0_TESLA) अणु
		tपंचांग_resource_manager_set_used(man, false);
		tपंचांग_resource_manager_evict_all(&drm->tपंचांग.bdev, man);
		tपंचांग_resource_manager_cleanup(man);
		tपंचांग_set_driver_manager(&drm->tपंचांग.bdev, TTM_PL_VRAM, शून्य);
		kमुक्त(man);
	पूर्ण अन्यथा
		tपंचांग_range_man_fini(&drm->tपंचांग.bdev, TTM_PL_VRAM);
पूर्ण

अटल पूर्णांक
nouveau_tपंचांग_init_gtt(काष्ठा nouveau_drm *drm)
अणु
	काष्ठा tपंचांग_resource_manager *man;
	अचिन्हित दीर्घ size_pages = drm->gem.gart_available >> PAGE_SHIFT;
	स्थिर काष्ठा tपंचांग_resource_manager_func *func = शून्य;

	अगर (drm->client.device.info.family >= NV_DEVICE_INFO_V0_TESLA)
		func = &nouveau_gart_manager;
	अन्यथा अगर (!drm->agp.bridge)
		func = &nv04_gart_manager;
	अन्यथा
		वापस tपंचांग_range_man_init(&drm->tपंचांग.bdev, TTM_PL_TT, true,
					  size_pages);

	man = kzalloc(माप(*man), GFP_KERNEL);
	अगर (!man)
		वापस -ENOMEM;

	man->func = func;
	man->use_tt = true;
	tपंचांग_resource_manager_init(man, size_pages);
	tपंचांग_set_driver_manager(&drm->tपंचांग.bdev, TTM_PL_TT, man);
	tपंचांग_resource_manager_set_used(man, true);
	वापस 0;
पूर्ण

अटल व्योम
nouveau_tपंचांग_fini_gtt(काष्ठा nouveau_drm *drm)
अणु
	काष्ठा tपंचांग_resource_manager *man = tपंचांग_manager_type(&drm->tपंचांग.bdev, TTM_PL_TT);

	अगर (drm->client.device.info.family < NV_DEVICE_INFO_V0_TESLA &&
	    drm->agp.bridge)
		tपंचांग_range_man_fini(&drm->tपंचांग.bdev, TTM_PL_TT);
	अन्यथा अणु
		tपंचांग_resource_manager_set_used(man, false);
		tपंचांग_resource_manager_evict_all(&drm->tपंचांग.bdev, man);
		tपंचांग_resource_manager_cleanup(man);
		tपंचांग_set_driver_manager(&drm->tपंचांग.bdev, TTM_PL_TT, शून्य);
		kमुक्त(man);
	पूर्ण
पूर्ण

पूर्णांक
nouveau_tपंचांग_init(काष्ठा nouveau_drm *drm)
अणु
	काष्ठा nvkm_device *device = nvxx_device(&drm->client.device);
	काष्ठा nvkm_pci *pci = device->pci;
	काष्ठा nvअगर_mmu *mmu = &drm->client.mmu;
	काष्ठा drm_device *dev = drm->dev;
	bool need_swiotlb = false;
	पूर्णांक typei, ret;

	ret = nouveau_tपंचांग_init_host(drm, 0);
	अगर (ret)
		वापस ret;

	अगर (drm->client.device.info.family >= NV_DEVICE_INFO_V0_TESLA &&
	    drm->client.device.info.chipset != 0x50) अणु
		ret = nouveau_tपंचांग_init_host(drm, NVIF_MEM_KIND);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (drm->client.device.info.platक्रमm != NV_DEVICE_INFO_V0_SOC &&
	    drm->client.device.info.family >= NV_DEVICE_INFO_V0_TESLA) अणु
		typei = nvअगर_mmu_type(mmu, NVIF_MEM_VRAM | NVIF_MEM_MAPPABLE |
					   NVIF_MEM_KIND |
					   NVIF_MEM_COMP |
					   NVIF_MEM_DISP);
		अगर (typei < 0)
			वापस -ENOSYS;

		drm->tपंचांग.type_vram = typei;
	पूर्ण अन्यथा अणु
		drm->tपंचांग.type_vram = -1;
	पूर्ण

	अगर (pci && pci->agp.bridge) अणु
		drm->agp.bridge = pci->agp.bridge;
		drm->agp.base = pci->agp.base;
		drm->agp.size = pci->agp.size;
		drm->agp.cma = pci->agp.cma;
	पूर्ण

#अगर IS_ENABLED(CONFIG_SWIOTLB) && IS_ENABLED(CONFIG_X86)
	need_swiotlb = is_swiotlb_active();
#पूर्ण_अगर

	ret = tपंचांग_device_init(&drm->tपंचांग.bdev, &nouveau_bo_driver, drm->dev->dev,
				  dev->anon_inode->i_mapping,
				  dev->vma_offset_manager, need_swiotlb,
				  drm->client.mmu.dmabits <= 32);
	अगर (ret) अणु
		NV_ERROR(drm, "error initialising bo driver, %d\n", ret);
		वापस ret;
	पूर्ण

	/* VRAM init */
	drm->gem.vram_available = drm->client.device.info.ram_user;

	arch_io_reserve_memtype_wc(device->func->resource_addr(device, 1),
				   device->func->resource_size(device, 1));

	ret = nouveau_tपंचांग_init_vram(drm);
	अगर (ret) अणु
		NV_ERROR(drm, "VRAM mm init failed, %d\n", ret);
		वापस ret;
	पूर्ण

	drm->tपंचांग.mtrr = arch_phys_wc_add(device->func->resource_addr(device, 1),
					 device->func->resource_size(device, 1));

	/* GART init */
	अगर (!drm->agp.bridge) अणु
		drm->gem.gart_available = drm->client.vmm.vmm.limit;
	पूर्ण अन्यथा अणु
		drm->gem.gart_available = drm->agp.size;
	पूर्ण

	ret = nouveau_tपंचांग_init_gtt(drm);
	अगर (ret) अणु
		NV_ERROR(drm, "GART mm init failed, %d\n", ret);
		वापस ret;
	पूर्ण

	mutex_init(&drm->tपंचांग.io_reserve_mutex);
	INIT_LIST_HEAD(&drm->tपंचांग.io_reserve_lru);

	NV_INFO(drm, "VRAM: %d MiB\n", (u32)(drm->gem.vram_available >> 20));
	NV_INFO(drm, "GART: %d MiB\n", (u32)(drm->gem.gart_available >> 20));
	वापस 0;
पूर्ण

व्योम
nouveau_tपंचांग_fini(काष्ठा nouveau_drm *drm)
अणु
	काष्ठा nvkm_device *device = nvxx_device(&drm->client.device);

	nouveau_tपंचांग_fini_vram(drm);
	nouveau_tपंचांग_fini_gtt(drm);

	tपंचांग_device_fini(&drm->tपंचांग.bdev);

	arch_phys_wc_del(drm->tपंचांग.mtrr);
	drm->tपंचांग.mtrr = 0;
	arch_io_मुक्त_memtype_wc(device->func->resource_addr(device, 1),
				device->func->resource_size(device, 1));

पूर्ण
