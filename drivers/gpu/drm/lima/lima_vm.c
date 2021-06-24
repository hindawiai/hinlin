<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR MIT
/* Copyright 2017-2019 Qiang Yu <yuq825@gmail.com> */

#समावेश <linux/slab.h>
#समावेश <linux/dma-mapping.h>

#समावेश "lima_device.h"
#समावेश "lima_vm.h"
#समावेश "lima_gem.h"
#समावेश "lima_regs.h"

काष्ठा lima_bo_va अणु
	काष्ठा list_head list;
	अचिन्हित पूर्णांक ref_count;

	काष्ठा drm_mm_node node;

	काष्ठा lima_vm *vm;
पूर्ण;

#घोषणा LIMA_VM_PD_SHIFT 22
#घोषणा LIMA_VM_PT_SHIFT 12
#घोषणा LIMA_VM_PB_SHIFT (LIMA_VM_PD_SHIFT + LIMA_VM_NUM_PT_PER_BT_SHIFT)
#घोषणा LIMA_VM_BT_SHIFT LIMA_VM_PT_SHIFT

#घोषणा LIMA_VM_PT_MASK ((1 << LIMA_VM_PD_SHIFT) - 1)
#घोषणा LIMA_VM_BT_MASK ((1 << LIMA_VM_PB_SHIFT) - 1)

#घोषणा LIMA_PDE(va) (va >> LIMA_VM_PD_SHIFT)
#घोषणा LIMA_PTE(va) ((va & LIMA_VM_PT_MASK) >> LIMA_VM_PT_SHIFT)
#घोषणा LIMA_PBE(va) (va >> LIMA_VM_PB_SHIFT)
#घोषणा LIMA_BTE(va) ((va & LIMA_VM_BT_MASK) >> LIMA_VM_BT_SHIFT)


अटल व्योम lima_vm_unmap_range(काष्ठा lima_vm *vm, u32 start, u32 end)
अणु
	u32 addr;

	क्रम (addr = start; addr <= end; addr += LIMA_PAGE_SIZE) अणु
		u32 pbe = LIMA_PBE(addr);
		u32 bte = LIMA_BTE(addr);

		vm->bts[pbe].cpu[bte] = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक lima_vm_map_page(काष्ठा lima_vm *vm, dma_addr_t pa, u32 va)
अणु
	u32 pbe = LIMA_PBE(va);
	u32 bte = LIMA_BTE(va);

	अगर (!vm->bts[pbe].cpu) अणु
		dma_addr_t pts;
		u32 *pd;
		पूर्णांक j;

		vm->bts[pbe].cpu = dma_alloc_wc(
			vm->dev->dev, LIMA_PAGE_SIZE << LIMA_VM_NUM_PT_PER_BT_SHIFT,
			&vm->bts[pbe].dma, GFP_KERNEL | __GFP_NOWARN | __GFP_ZERO);
		अगर (!vm->bts[pbe].cpu)
			वापस -ENOMEM;

		pts = vm->bts[pbe].dma;
		pd = vm->pd.cpu + (pbe << LIMA_VM_NUM_PT_PER_BT_SHIFT);
		क्रम (j = 0; j < LIMA_VM_NUM_PT_PER_BT; j++) अणु
			pd[j] = pts | LIMA_VM_FLAG_PRESENT;
			pts += LIMA_PAGE_SIZE;
		पूर्ण
	पूर्ण

	vm->bts[pbe].cpu[bte] = pa | LIMA_VM_FLAGS_CACHE;

	वापस 0;
पूर्ण

अटल काष्ठा lima_bo_va *
lima_vm_bo_find(काष्ठा lima_vm *vm, काष्ठा lima_bo *bo)
अणु
	काष्ठा lima_bo_va *bo_va, *ret = शून्य;

	list_क्रम_each_entry(bo_va, &bo->va, list) अणु
		अगर (bo_va->vm == vm) अणु
			ret = bo_va;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक lima_vm_bo_add(काष्ठा lima_vm *vm, काष्ठा lima_bo *bo, bool create)
अणु
	काष्ठा lima_bo_va *bo_va;
	काष्ठा sg_dma_page_iter sg_iter;
	पूर्णांक offset = 0, err;

	mutex_lock(&bo->lock);

	bo_va = lima_vm_bo_find(vm, bo);
	अगर (bo_va) अणु
		bo_va->ref_count++;
		mutex_unlock(&bo->lock);
		वापस 0;
	पूर्ण

	/* should not create new bo_va अगर not asked by caller */
	अगर (!create) अणु
		mutex_unlock(&bo->lock);
		वापस -ENOENT;
	पूर्ण

	bo_va = kzalloc(माप(*bo_va), GFP_KERNEL);
	अगर (!bo_va) अणु
		err = -ENOMEM;
		जाओ err_out0;
	पूर्ण

	bo_va->vm = vm;
	bo_va->ref_count = 1;

	mutex_lock(&vm->lock);

	err = drm_mm_insert_node(&vm->mm, &bo_va->node, lima_bo_size(bo));
	अगर (err)
		जाओ err_out1;

	क्रम_each_sgtable_dma_page(bo->base.sgt, &sg_iter, 0) अणु
		err = lima_vm_map_page(vm, sg_page_iter_dma_address(&sg_iter),
				       bo_va->node.start + offset);
		अगर (err)
			जाओ err_out2;

		offset += PAGE_SIZE;
	पूर्ण

	mutex_unlock(&vm->lock);

	list_add_tail(&bo_va->list, &bo->va);

	mutex_unlock(&bo->lock);
	वापस 0;

err_out2:
	अगर (offset)
		lima_vm_unmap_range(vm, bo_va->node.start, bo_va->node.start + offset - 1);
	drm_mm_हटाओ_node(&bo_va->node);
err_out1:
	mutex_unlock(&vm->lock);
	kमुक्त(bo_va);
err_out0:
	mutex_unlock(&bo->lock);
	वापस err;
पूर्ण

व्योम lima_vm_bo_del(काष्ठा lima_vm *vm, काष्ठा lima_bo *bo)
अणु
	काष्ठा lima_bo_va *bo_va;
	u32 size;

	mutex_lock(&bo->lock);

	bo_va = lima_vm_bo_find(vm, bo);
	अगर (--bo_va->ref_count > 0) अणु
		mutex_unlock(&bo->lock);
		वापस;
	पूर्ण

	mutex_lock(&vm->lock);

	size = bo->heap_size ? bo->heap_size : bo_va->node.size;
	lima_vm_unmap_range(vm, bo_va->node.start,
			    bo_va->node.start + size - 1);

	drm_mm_हटाओ_node(&bo_va->node);

	mutex_unlock(&vm->lock);

	list_del(&bo_va->list);

	mutex_unlock(&bo->lock);

	kमुक्त(bo_va);
पूर्ण

u32 lima_vm_get_va(काष्ठा lima_vm *vm, काष्ठा lima_bo *bo)
अणु
	काष्ठा lima_bo_va *bo_va;
	u32 ret;

	mutex_lock(&bo->lock);

	bo_va = lima_vm_bo_find(vm, bo);
	ret = bo_va->node.start;

	mutex_unlock(&bo->lock);

	वापस ret;
पूर्ण

काष्ठा lima_vm *lima_vm_create(काष्ठा lima_device *dev)
अणु
	काष्ठा lima_vm *vm;

	vm = kzalloc(माप(*vm), GFP_KERNEL);
	अगर (!vm)
		वापस शून्य;

	vm->dev = dev;
	mutex_init(&vm->lock);
	kref_init(&vm->refcount);

	vm->pd.cpu = dma_alloc_wc(dev->dev, LIMA_PAGE_SIZE, &vm->pd.dma,
				  GFP_KERNEL | __GFP_NOWARN | __GFP_ZERO);
	अगर (!vm->pd.cpu)
		जाओ err_out0;

	अगर (dev->dlbu_cpu) अणु
		पूर्णांक err = lima_vm_map_page(
			vm, dev->dlbu_dma, LIMA_VA_RESERVE_DLBU);
		अगर (err)
			जाओ err_out1;
	पूर्ण

	drm_mm_init(&vm->mm, dev->बहु_शुरू, dev->बहु_पूर्ण - dev->बहु_शुरू);

	वापस vm;

err_out1:
	dma_मुक्त_wc(dev->dev, LIMA_PAGE_SIZE, vm->pd.cpu, vm->pd.dma);
err_out0:
	kमुक्त(vm);
	वापस शून्य;
पूर्ण

व्योम lima_vm_release(काष्ठा kref *kref)
अणु
	काष्ठा lima_vm *vm = container_of(kref, काष्ठा lima_vm, refcount);
	पूर्णांक i;

	drm_mm_takeकरोwn(&vm->mm);

	क्रम (i = 0; i < LIMA_VM_NUM_BT; i++) अणु
		अगर (vm->bts[i].cpu)
			dma_मुक्त_wc(vm->dev->dev, LIMA_PAGE_SIZE << LIMA_VM_NUM_PT_PER_BT_SHIFT,
				    vm->bts[i].cpu, vm->bts[i].dma);
	पूर्ण

	अगर (vm->pd.cpu)
		dma_मुक्त_wc(vm->dev->dev, LIMA_PAGE_SIZE, vm->pd.cpu, vm->pd.dma);

	kमुक्त(vm);
पूर्ण

व्योम lima_vm_prपूर्णांक(काष्ठा lima_vm *vm)
अणु
	पूर्णांक i, j, k;
	u32 *pd, *pt;

	अगर (!vm->pd.cpu)
		वापस;

	pd = vm->pd.cpu;
	क्रम (i = 0; i < LIMA_VM_NUM_BT; i++) अणु
		अगर (!vm->bts[i].cpu)
			जारी;

		pt = vm->bts[i].cpu;
		क्रम (j = 0; j < LIMA_VM_NUM_PT_PER_BT; j++) अणु
			पूर्णांक idx = (i << LIMA_VM_NUM_PT_PER_BT_SHIFT) + j;

			prपूर्णांकk(KERN_INFO "lima vm pd %03x:%08x\n", idx, pd[idx]);

			क्रम (k = 0; k < LIMA_PAGE_ENT_NUM; k++) अणु
				u32 pte = *pt++;

				अगर (pte)
					prपूर्णांकk(KERN_INFO "  pt %03x:%08x\n", k, pte);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक lima_vm_map_bo(काष्ठा lima_vm *vm, काष्ठा lima_bo *bo, पूर्णांक pageoff)
अणु
	काष्ठा lima_bo_va *bo_va;
	काष्ठा sg_dma_page_iter sg_iter;
	पूर्णांक offset = 0, err;
	u32 base;

	mutex_lock(&bo->lock);

	bo_va = lima_vm_bo_find(vm, bo);
	अगर (!bo_va) अणु
		err = -ENOENT;
		जाओ err_out0;
	पूर्ण

	mutex_lock(&vm->lock);

	base = bo_va->node.start + (pageoff << PAGE_SHIFT);
	क्रम_each_sgtable_dma_page(bo->base.sgt, &sg_iter, pageoff) अणु
		err = lima_vm_map_page(vm, sg_page_iter_dma_address(&sg_iter),
				       base + offset);
		अगर (err)
			जाओ err_out1;

		offset += PAGE_SIZE;
	पूर्ण

	mutex_unlock(&vm->lock);

	mutex_unlock(&bo->lock);
	वापस 0;

err_out1:
	अगर (offset)
		lima_vm_unmap_range(vm, base, base + offset - 1);
	mutex_unlock(&vm->lock);
err_out0:
	mutex_unlock(&bo->lock);
	वापस err;
पूर्ण
