<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ACRN_HSM: Virtual Machine management
 *
 * Copyright (C) 2020 Intel Corporation. All rights reserved.
 *
 * Authors:
 *	Jason Chen CJ <jason.cj.chen@पूर्णांकel.com>
 *	Yakui Zhao <yakui.zhao@पूर्णांकel.com>
 */
#समावेश <linux/पन.स>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>

#समावेश "acrn_drv.h"

/* List of VMs */
LIST_HEAD(acrn_vm_list);
/*
 * acrn_vm_list is पढ़ो in a worker thपढ़ो which dispatch I/O requests and
 * is wrote in VM creation ioctl. Use the rwlock mechanism to protect it.
 */
DEFINE_RWLOCK(acrn_vm_list_lock);

काष्ठा acrn_vm *acrn_vm_create(काष्ठा acrn_vm *vm,
			       काष्ठा acrn_vm_creation *vm_param)
अणु
	पूर्णांक ret;

	ret = hcall_create_vm(virt_to_phys(vm_param));
	अगर (ret < 0 || vm_param->vmid == ACRN_INVALID_VMID) अणु
		dev_err(acrn_dev.this_device,
			"Failed to create VM! Error: %d\n", ret);
		वापस शून्य;
	पूर्ण

	mutex_init(&vm->regions_mapping_lock);
	INIT_LIST_HEAD(&vm->ioreq_clients);
	spin_lock_init(&vm->ioreq_clients_lock);
	vm->vmid = vm_param->vmid;
	vm->vcpu_num = vm_param->vcpu_num;

	अगर (acrn_ioreq_init(vm, vm_param->ioreq_buf) < 0) अणु
		hcall_destroy_vm(vm_param->vmid);
		vm->vmid = ACRN_INVALID_VMID;
		वापस शून्य;
	पूर्ण

	ग_लिखो_lock_bh(&acrn_vm_list_lock);
	list_add(&vm->list, &acrn_vm_list);
	ग_लिखो_unlock_bh(&acrn_vm_list_lock);

	acrn_ioeventfd_init(vm);
	acrn_irqfd_init(vm);
	dev_dbg(acrn_dev.this_device, "VM %u created.\n", vm->vmid);
	वापस vm;
पूर्ण

पूर्णांक acrn_vm_destroy(काष्ठा acrn_vm *vm)
अणु
	पूर्णांक ret;

	अगर (vm->vmid == ACRN_INVALID_VMID ||
	    test_and_set_bit(ACRN_VM_FLAG_DESTROYED, &vm->flags))
		वापस 0;

	/* Remove from global VM list */
	ग_लिखो_lock_bh(&acrn_vm_list_lock);
	list_del_init(&vm->list);
	ग_लिखो_unlock_bh(&acrn_vm_list_lock);

	acrn_ioeventfd_deinit(vm);
	acrn_irqfd_deinit(vm);
	acrn_ioreq_deinit(vm);

	अगर (vm->monitor_page) अणु
		put_page(vm->monitor_page);
		vm->monitor_page = शून्य;
	पूर्ण

	ret = hcall_destroy_vm(vm->vmid);
	अगर (ret < 0) अणु
		dev_err(acrn_dev.this_device,
			"Failed to destroy VM %u\n", vm->vmid);
		clear_bit(ACRN_VM_FLAG_DESTROYED, &vm->flags);
		वापस ret;
	पूर्ण

	acrn_vm_all_ram_unmap(vm);

	dev_dbg(acrn_dev.this_device, "VM %u destroyed.\n", vm->vmid);
	vm->vmid = ACRN_INVALID_VMID;
	वापस 0;
पूर्ण

/**
 * acrn_msi_inject() - Inject a MSI पूर्णांकerrupt पूर्णांकo a User VM
 * @vm:		User VM
 * @msi_addr:	The MSI address
 * @msi_data:	The MSI data
 *
 * Return: 0 on success, <0 on error
 */
पूर्णांक acrn_msi_inject(काष्ठा acrn_vm *vm, u64 msi_addr, u64 msi_data)
अणु
	काष्ठा acrn_msi_entry *msi;
	पूर्णांक ret;

	/* might be used in पूर्णांकerrupt context, so use GFP_ATOMIC */
	msi = kzalloc(माप(*msi), GFP_ATOMIC);
	अगर (!msi)
		वापस -ENOMEM;

	/*
	 * msi_addr: addr[19:12] with dest vcpu id
	 * msi_data: data[7:0] with vector
	 */
	msi->msi_addr = msi_addr;
	msi->msi_data = msi_data;
	ret = hcall_inject_msi(vm->vmid, virt_to_phys(msi));
	अगर (ret < 0)
		dev_err(acrn_dev.this_device,
			"Failed to inject MSI to VM %u!\n", vm->vmid);
	kमुक्त(msi);
	वापस ret;
पूर्ण
