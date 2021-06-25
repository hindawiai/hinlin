<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR MIT */
/* Copyright 2017-2019 Qiang Yu <yuq825@gmail.com> */

#अगर_अघोषित __LIMA_VM_H__
#घोषणा __LIMA_VM_H__

#समावेश <drm/drm_mm.h>
#समावेश <linux/kref.h>

#घोषणा LIMA_PAGE_SIZE    4096
#घोषणा LIMA_PAGE_MASK    (LIMA_PAGE_SIZE - 1)
#घोषणा LIMA_PAGE_ENT_NUM (LIMA_PAGE_SIZE / माप(u32))

#घोषणा LIMA_VM_NUM_PT_PER_BT_SHIFT 3
#घोषणा LIMA_VM_NUM_PT_PER_BT (1 << LIMA_VM_NUM_PT_PER_BT_SHIFT)
#घोषणा LIMA_VM_NUM_BT (LIMA_PAGE_ENT_NUM >> LIMA_VM_NUM_PT_PER_BT_SHIFT)

#घोषणा LIMA_VA_RESERVE_START  0x0FFF00000ULL
#घोषणा LIMA_VA_RESERVE_DLBU   LIMA_VA_RESERVE_START
#घोषणा LIMA_VA_RESERVE_END    0x100000000ULL

काष्ठा lima_device;

काष्ठा lima_vm_page अणु
	u32 *cpu;
	dma_addr_t dma;
पूर्ण;

काष्ठा lima_vm अणु
	काष्ठा mutex lock;
	काष्ठा kref refcount;

	काष्ठा drm_mm mm;

	काष्ठा lima_device *dev;

	काष्ठा lima_vm_page pd;
	काष्ठा lima_vm_page bts[LIMA_VM_NUM_BT];
पूर्ण;

पूर्णांक lima_vm_bo_add(काष्ठा lima_vm *vm, काष्ठा lima_bo *bo, bool create);
व्योम lima_vm_bo_del(काष्ठा lima_vm *vm, काष्ठा lima_bo *bo);

u32 lima_vm_get_va(काष्ठा lima_vm *vm, काष्ठा lima_bo *bo);

काष्ठा lima_vm *lima_vm_create(काष्ठा lima_device *dev);
व्योम lima_vm_release(काष्ठा kref *kref);

अटल अंतरभूत काष्ठा lima_vm *lima_vm_get(काष्ठा lima_vm *vm)
अणु
	kref_get(&vm->refcount);
	वापस vm;
पूर्ण

अटल अंतरभूत व्योम lima_vm_put(काष्ठा lima_vm *vm)
अणु
	अगर (vm)
		kref_put(&vm->refcount, lima_vm_release);
पूर्ण

व्योम lima_vm_prपूर्णांक(काष्ठा lima_vm *vm);
पूर्णांक lima_vm_map_bo(काष्ठा lima_vm *vm, काष्ठा lima_bo *bo, पूर्णांक pageoff);

#पूर्ण_अगर
