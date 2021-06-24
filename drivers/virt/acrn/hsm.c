<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ACRN Hypervisor Service Module (HSM)
 *
 * Copyright (C) 2020 Intel Corporation. All rights reserved.
 *
 * Authors:
 *	Fengwei Yin <fengwei.yin@पूर्णांकel.com>
 *	Yakui Zhao <yakui.zhao@पूर्णांकel.com>
 */

#समावेश <linux/cpu.h>
#समावेश <linux/पन.स>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/acrn.h>
#समावेश <यंत्र/hypervisor.h>

#समावेश "acrn_drv.h"

/*
 * When /dev/acrn_hsm is खोलोed, a 'struct acrn_vm' object is created to
 * represent a VM instance and जारीs to be associated with the खोलोed file
 * descriptor. All ioctl operations on this file descriptor will be targeted to
 * the VM instance. Release of this file descriptor will destroy the object.
 */
अटल पूर्णांक acrn_dev_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा acrn_vm *vm;

	vm = kzalloc(माप(*vm), GFP_KERNEL);
	अगर (!vm)
		वापस -ENOMEM;

	vm->vmid = ACRN_INVALID_VMID;
	filp->निजी_data = vm;
	वापस 0;
पूर्ण

अटल पूर्णांक pmcmd_ioctl(u64 cmd, व्योम __user *uptr)
अणु
	काष्ठा acrn_pstate_data *px_data;
	काष्ठा acrn_cstate_data *cx_data;
	u64 *pm_info;
	पूर्णांक ret = 0;

	चयन (cmd & PMCMD_TYPE_MASK) अणु
	हाल ACRN_PMCMD_GET_PX_CNT:
	हाल ACRN_PMCMD_GET_CX_CNT:
		pm_info = kदो_स्मृति(माप(u64), GFP_KERNEL);
		अगर (!pm_info)
			वापस -ENOMEM;

		ret = hcall_get_cpu_state(cmd, virt_to_phys(pm_info));
		अगर (ret < 0) अणु
			kमुक्त(pm_info);
			अवरोध;
		पूर्ण

		अगर (copy_to_user(uptr, pm_info, माप(u64)))
			ret = -EFAULT;
		kमुक्त(pm_info);
		अवरोध;
	हाल ACRN_PMCMD_GET_PX_DATA:
		px_data = kदो_स्मृति(माप(*px_data), GFP_KERNEL);
		अगर (!px_data)
			वापस -ENOMEM;

		ret = hcall_get_cpu_state(cmd, virt_to_phys(px_data));
		अगर (ret < 0) अणु
			kमुक्त(px_data);
			अवरोध;
		पूर्ण

		अगर (copy_to_user(uptr, px_data, माप(*px_data)))
			ret = -EFAULT;
		kमुक्त(px_data);
		अवरोध;
	हाल ACRN_PMCMD_GET_CX_DATA:
		cx_data = kदो_स्मृति(माप(*cx_data), GFP_KERNEL);
		अगर (!cx_data)
			वापस -ENOMEM;

		ret = hcall_get_cpu_state(cmd, virt_to_phys(cx_data));
		अगर (ret < 0) अणु
			kमुक्त(cx_data);
			अवरोध;
		पूर्ण

		अगर (copy_to_user(uptr, cx_data, माप(*cx_data)))
			ret = -EFAULT;
		kमुक्त(cx_data);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

/*
 * HSM relies on hypercall layer of the ACRN hypervisor to करो the
 * sanity check against the input parameters.
 */
अटल दीर्घ acrn_dev_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक cmd,
			   अचिन्हित दीर्घ ioctl_param)
अणु
	काष्ठा acrn_vm *vm = filp->निजी_data;
	काष्ठा acrn_vm_creation *vm_param;
	काष्ठा acrn_vcpu_regs *cpu_regs;
	काष्ठा acrn_ioreq_notअगरy notअगरy;
	काष्ठा acrn_ptdev_irq *irq_info;
	काष्ठा acrn_ioeventfd ioeventfd;
	काष्ठा acrn_vm_memmap memmap;
	काष्ठा acrn_msi_entry *msi;
	काष्ठा acrn_pcidev *pcidev;
	काष्ठा acrn_irqfd irqfd;
	काष्ठा page *page;
	u64 cstate_cmd;
	पूर्णांक i, ret = 0;

	अगर (vm->vmid == ACRN_INVALID_VMID && cmd != ACRN_IOCTL_CREATE_VM) अणु
		dev_dbg(acrn_dev.this_device,
			"ioctl 0x%x: Invalid VM state!\n", cmd);
		वापस -EINVAL;
	पूर्ण

	चयन (cmd) अणु
	हाल ACRN_IOCTL_CREATE_VM:
		vm_param = memdup_user((व्योम __user *)ioctl_param,
				       माप(काष्ठा acrn_vm_creation));
		अगर (IS_ERR(vm_param))
			वापस PTR_ERR(vm_param);

		अगर ((vm_param->reserved0 | vm_param->reserved1) != 0)
			वापस -EINVAL;

		vm = acrn_vm_create(vm, vm_param);
		अगर (!vm) अणु
			ret = -EINVAL;
			kमुक्त(vm_param);
			अवरोध;
		पूर्ण

		अगर (copy_to_user((व्योम __user *)ioctl_param, vm_param,
				 माप(काष्ठा acrn_vm_creation))) अणु
			acrn_vm_destroy(vm);
			ret = -EFAULT;
		पूर्ण

		kमुक्त(vm_param);
		अवरोध;
	हाल ACRN_IOCTL_START_VM:
		ret = hcall_start_vm(vm->vmid);
		अगर (ret < 0)
			dev_dbg(acrn_dev.this_device,
				"Failed to start VM %u!\n", vm->vmid);
		अवरोध;
	हाल ACRN_IOCTL_PAUSE_VM:
		ret = hcall_छोड़ो_vm(vm->vmid);
		अगर (ret < 0)
			dev_dbg(acrn_dev.this_device,
				"Failed to pause VM %u!\n", vm->vmid);
		अवरोध;
	हाल ACRN_IOCTL_RESET_VM:
		ret = hcall_reset_vm(vm->vmid);
		अगर (ret < 0)
			dev_dbg(acrn_dev.this_device,
				"Failed to restart VM %u!\n", vm->vmid);
		अवरोध;
	हाल ACRN_IOCTL_DESTROY_VM:
		ret = acrn_vm_destroy(vm);
		अवरोध;
	हाल ACRN_IOCTL_SET_VCPU_REGS:
		cpu_regs = memdup_user((व्योम __user *)ioctl_param,
				       माप(काष्ठा acrn_vcpu_regs));
		अगर (IS_ERR(cpu_regs))
			वापस PTR_ERR(cpu_regs);

		क्रम (i = 0; i < ARRAY_SIZE(cpu_regs->reserved); i++)
			अगर (cpu_regs->reserved[i])
				वापस -EINVAL;

		क्रम (i = 0; i < ARRAY_SIZE(cpu_regs->vcpu_regs.reserved_32); i++)
			अगर (cpu_regs->vcpu_regs.reserved_32[i])
				वापस -EINVAL;

		क्रम (i = 0; i < ARRAY_SIZE(cpu_regs->vcpu_regs.reserved_64); i++)
			अगर (cpu_regs->vcpu_regs.reserved_64[i])
				वापस -EINVAL;

		क्रम (i = 0; i < ARRAY_SIZE(cpu_regs->vcpu_regs.gdt.reserved); i++)
			अगर (cpu_regs->vcpu_regs.gdt.reserved[i] |
			    cpu_regs->vcpu_regs.idt.reserved[i])
				वापस -EINVAL;

		ret = hcall_set_vcpu_regs(vm->vmid, virt_to_phys(cpu_regs));
		अगर (ret < 0)
			dev_dbg(acrn_dev.this_device,
				"Failed to set regs state of VM%u!\n",
				vm->vmid);
		kमुक्त(cpu_regs);
		अवरोध;
	हाल ACRN_IOCTL_SET_MEMSEG:
		अगर (copy_from_user(&memmap, (व्योम __user *)ioctl_param,
				   माप(memmap)))
			वापस -EFAULT;

		ret = acrn_vm_memseg_map(vm, &memmap);
		अवरोध;
	हाल ACRN_IOCTL_UNSET_MEMSEG:
		अगर (copy_from_user(&memmap, (व्योम __user *)ioctl_param,
				   माप(memmap)))
			वापस -EFAULT;

		ret = acrn_vm_memseg_unmap(vm, &memmap);
		अवरोध;
	हाल ACRN_IOCTL_ASSIGN_PCIDEV:
		pcidev = memdup_user((व्योम __user *)ioctl_param,
				     माप(काष्ठा acrn_pcidev));
		अगर (IS_ERR(pcidev))
			वापस PTR_ERR(pcidev);

		ret = hcall_assign_pcidev(vm->vmid, virt_to_phys(pcidev));
		अगर (ret < 0)
			dev_dbg(acrn_dev.this_device,
				"Failed to assign pci device!\n");
		kमुक्त(pcidev);
		अवरोध;
	हाल ACRN_IOCTL_DEASSIGN_PCIDEV:
		pcidev = memdup_user((व्योम __user *)ioctl_param,
				     माप(काष्ठा acrn_pcidev));
		अगर (IS_ERR(pcidev))
			वापस PTR_ERR(pcidev);

		ret = hcall_deassign_pcidev(vm->vmid, virt_to_phys(pcidev));
		अगर (ret < 0)
			dev_dbg(acrn_dev.this_device,
				"Failed to deassign pci device!\n");
		kमुक्त(pcidev);
		अवरोध;
	हाल ACRN_IOCTL_SET_PTDEV_INTR:
		irq_info = memdup_user((व्योम __user *)ioctl_param,
				       माप(काष्ठा acrn_ptdev_irq));
		अगर (IS_ERR(irq_info))
			वापस PTR_ERR(irq_info);

		ret = hcall_set_ptdev_पूर्णांकr(vm->vmid, virt_to_phys(irq_info));
		अगर (ret < 0)
			dev_dbg(acrn_dev.this_device,
				"Failed to configure intr for ptdev!\n");
		kमुक्त(irq_info);
		अवरोध;
	हाल ACRN_IOCTL_RESET_PTDEV_INTR:
		irq_info = memdup_user((व्योम __user *)ioctl_param,
				       माप(काष्ठा acrn_ptdev_irq));
		अगर (IS_ERR(irq_info))
			वापस PTR_ERR(irq_info);

		ret = hcall_reset_ptdev_पूर्णांकr(vm->vmid, virt_to_phys(irq_info));
		अगर (ret < 0)
			dev_dbg(acrn_dev.this_device,
				"Failed to reset intr for ptdev!\n");
		kमुक्त(irq_info);
		अवरोध;
	हाल ACRN_IOCTL_SET_IRQLINE:
		ret = hcall_set_irqline(vm->vmid, ioctl_param);
		अगर (ret < 0)
			dev_dbg(acrn_dev.this_device,
				"Failed to set interrupt line!\n");
		अवरोध;
	हाल ACRN_IOCTL_INJECT_MSI:
		msi = memdup_user((व्योम __user *)ioctl_param,
				  माप(काष्ठा acrn_msi_entry));
		अगर (IS_ERR(msi))
			वापस PTR_ERR(msi);

		ret = hcall_inject_msi(vm->vmid, virt_to_phys(msi));
		अगर (ret < 0)
			dev_dbg(acrn_dev.this_device,
				"Failed to inject MSI!\n");
		kमुक्त(msi);
		अवरोध;
	हाल ACRN_IOCTL_VM_INTR_MONITOR:
		ret = pin_user_pages_fast(ioctl_param, 1,
					  FOLL_WRITE | FOLL_LONGTERM, &page);
		अगर (unlikely(ret != 1)) अणु
			dev_dbg(acrn_dev.this_device,
				"Failed to pin intr hdr buffer!\n");
			वापस -EFAULT;
		पूर्ण

		ret = hcall_vm_पूर्णांकr_monitor(vm->vmid, page_to_phys(page));
		अगर (ret < 0) अणु
			unpin_user_page(page);
			dev_dbg(acrn_dev.this_device,
				"Failed to monitor intr data!\n");
			वापस ret;
		पूर्ण
		अगर (vm->monitor_page)
			unpin_user_page(vm->monitor_page);
		vm->monitor_page = page;
		अवरोध;
	हाल ACRN_IOCTL_CREATE_IOREQ_CLIENT:
		अगर (vm->शेष_client)
			वापस -EEXIST;
		अगर (!acrn_ioreq_client_create(vm, शून्य, शून्य, true, "acrndm"))
			ret = -EINVAL;
		अवरोध;
	हाल ACRN_IOCTL_DESTROY_IOREQ_CLIENT:
		अगर (vm->शेष_client)
			acrn_ioreq_client_destroy(vm->शेष_client);
		अवरोध;
	हाल ACRN_IOCTL_ATTACH_IOREQ_CLIENT:
		अगर (vm->शेष_client)
			ret = acrn_ioreq_client_रुको(vm->शेष_client);
		अन्यथा
			ret = -ENODEV;
		अवरोध;
	हाल ACRN_IOCTL_NOTIFY_REQUEST_FINISH:
		अगर (copy_from_user(&notअगरy, (व्योम __user *)ioctl_param,
				   माप(काष्ठा acrn_ioreq_notअगरy)))
			वापस -EFAULT;

		अगर (notअगरy.reserved != 0)
			वापस -EINVAL;

		ret = acrn_ioreq_request_शेष_complete(vm, notअगरy.vcpu);
		अवरोध;
	हाल ACRN_IOCTL_CLEAR_VM_IOREQ:
		acrn_ioreq_request_clear(vm);
		अवरोध;
	हाल ACRN_IOCTL_PM_GET_CPU_STATE:
		अगर (copy_from_user(&cstate_cmd, (व्योम __user *)ioctl_param,
				   माप(cstate_cmd)))
			वापस -EFAULT;

		ret = pmcmd_ioctl(cstate_cmd, (व्योम __user *)ioctl_param);
		अवरोध;
	हाल ACRN_IOCTL_IOEVENTFD:
		अगर (copy_from_user(&ioeventfd, (व्योम __user *)ioctl_param,
				   माप(ioeventfd)))
			वापस -EFAULT;

		अगर (ioeventfd.reserved != 0)
			वापस -EINVAL;

		ret = acrn_ioeventfd_config(vm, &ioeventfd);
		अवरोध;
	हाल ACRN_IOCTL_IRQFD:
		अगर (copy_from_user(&irqfd, (व्योम __user *)ioctl_param,
				   माप(irqfd)))
			वापस -EFAULT;
		ret = acrn_irqfd_config(vm, &irqfd);
		अवरोध;
	शेष:
		dev_dbg(acrn_dev.this_device, "Unknown IOCTL 0x%x!\n", cmd);
		ret = -ENOTTY;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक acrn_dev_release(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा acrn_vm *vm = filp->निजी_data;

	acrn_vm_destroy(vm);
	kमुक्त(vm);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार हटाओ_cpu_store(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	u64 cpu, lapicid;
	पूर्णांक ret;

	अगर (kम_से_अदीर्घl(buf, 0, &cpu) < 0)
		वापस -EINVAL;

	अगर (cpu >= num_possible_cpus() || cpu == 0 || !cpu_is_hotpluggable(cpu))
		वापस -EINVAL;

	अगर (cpu_online(cpu))
		हटाओ_cpu(cpu);

	lapicid = cpu_data(cpu).apicid;
	dev_dbg(dev, "Try to remove cpu %lld with lapicid %lld\n", cpu, lapicid);
	ret = hcall_sos_हटाओ_cpu(lapicid);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to remove cpu %lld!\n", cpu);
		जाओ fail_हटाओ;
	पूर्ण

	वापस count;

fail_हटाओ:
	add_cpu(cpu);
	वापस ret;
पूर्ण
अटल DEVICE_ATTR_WO(हटाओ_cpu);

अटल umode_t acrn_attr_visible(काष्ठा kobject *kobj, काष्ठा attribute *a, पूर्णांक n)
अणु
       अगर (a == &dev_attr_हटाओ_cpu.attr)
               वापस IS_ENABLED(CONFIG_HOTPLUG_CPU) ? a->mode : 0;

       वापस a->mode;
पूर्ण

अटल काष्ठा attribute *acrn_attrs[] = अणु
	&dev_attr_हटाओ_cpu.attr,
	शून्य
पूर्ण;

अटल काष्ठा attribute_group acrn_attr_group = अणु
	.attrs = acrn_attrs,
	.is_visible = acrn_attr_visible,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *acrn_attr_groups[] = अणु
	&acrn_attr_group,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा file_operations acrn_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= acrn_dev_खोलो,
	.release	= acrn_dev_release,
	.unlocked_ioctl = acrn_dev_ioctl,
पूर्ण;

काष्ठा miscdevice acrn_dev = अणु
	.minor	= MISC_DYNAMIC_MINOR,
	.name	= "acrn_hsm",
	.fops	= &acrn_fops,
	.groups	= acrn_attr_groups,
पूर्ण;

अटल पूर्णांक __init hsm_init(व्योम)
अणु
	पूर्णांक ret;

	अगर (x86_hyper_type != X86_HYPER_ACRN)
		वापस -ENODEV;

	अगर (!(cpuid_eax(ACRN_CPUID_FEATURES) & ACRN_FEATURE_PRIVILEGED_VM))
		वापस -EPERM;

	ret = misc_रेजिस्टर(&acrn_dev);
	अगर (ret) अणु
		pr_err("Create misc dev failed!\n");
		वापस ret;
	पूर्ण

	ret = acrn_ioreq_पूर्णांकr_setup();
	अगर (ret) अणु
		pr_err("Setup I/O request handler failed!\n");
		misc_deरेजिस्टर(&acrn_dev);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम __निकास hsm_निकास(व्योम)
अणु
	acrn_ioreq_पूर्णांकr_हटाओ();
	misc_deरेजिस्टर(&acrn_dev);
पूर्ण
module_init(hsm_init);
module_निकास(hsm_निकास);

MODULE_AUTHOR("Intel Corporation");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("ACRN Hypervisor Service Module (HSM)");
