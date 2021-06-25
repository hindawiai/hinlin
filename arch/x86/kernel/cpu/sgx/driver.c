<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*  Copyright(c) 2016-20 Intel Corporation. */

#समावेश <linux/acpi.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/mman.h>
#समावेश <linux/security.h>
#समावेश <linux/suspend.h>
#समावेश <यंत्र/traps.h>
#समावेश "driver.h"
#समावेश "encl.h"

u64 sgx_attributes_reserved_mask;
u64 sgx_xfrm_reserved_mask = ~0x3;
u32 sgx_misc_reserved_mask;

अटल पूर्णांक sgx_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा sgx_encl *encl;
	पूर्णांक ret;

	encl = kzalloc(माप(*encl), GFP_KERNEL);
	अगर (!encl)
		वापस -ENOMEM;

	kref_init(&encl->refcount);
	xa_init(&encl->page_array);
	mutex_init(&encl->lock);
	INIT_LIST_HEAD(&encl->va_pages);
	INIT_LIST_HEAD(&encl->mm_list);
	spin_lock_init(&encl->mm_lock);

	ret = init_srcu_काष्ठा(&encl->srcu);
	अगर (ret) अणु
		kमुक्त(encl);
		वापस ret;
	पूर्ण

	file->निजी_data = encl;

	वापस 0;
पूर्ण

अटल पूर्णांक sgx_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा sgx_encl *encl = file->निजी_data;
	काष्ठा sgx_encl_mm *encl_mm;

	/*
	 * Drain the reमुख्यing mm_list entries. At this poपूर्णांक the list contains
	 * entries क्रम processes, which have बंदd the enclave file but have
	 * not निकासed yet. The processes, which have निकासed, are gone from the
	 * list by sgx_mmu_notअगरier_release().
	 */
	क्रम ( ; ; )  अणु
		spin_lock(&encl->mm_lock);

		अगर (list_empty(&encl->mm_list)) अणु
			encl_mm = शून्य;
		पूर्ण अन्यथा अणु
			encl_mm = list_first_entry(&encl->mm_list,
						   काष्ठा sgx_encl_mm, list);
			list_del_rcu(&encl_mm->list);
		पूर्ण

		spin_unlock(&encl->mm_lock);

		/* The enclave is no दीर्घer mapped by any mm. */
		अगर (!encl_mm)
			अवरोध;

		synchronize_srcu(&encl->srcu);
		mmu_notअगरier_unरेजिस्टर(&encl_mm->mmu_notअगरier, encl_mm->mm);
		kमुक्त(encl_mm);

		/* 'encl_mm' is gone, put encl_mm->encl reference: */
		kref_put(&encl->refcount, sgx_encl_release);
	पूर्ण

	kref_put(&encl->refcount, sgx_encl_release);
	वापस 0;
पूर्ण

अटल पूर्णांक sgx_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा sgx_encl *encl = file->निजी_data;
	पूर्णांक ret;

	ret = sgx_encl_may_map(encl, vma->vm_start, vma->vm_end, vma->vm_flags);
	अगर (ret)
		वापस ret;

	ret = sgx_encl_mm_add(encl, vma->vm_mm);
	अगर (ret)
		वापस ret;

	vma->vm_ops = &sgx_vm_ops;
	vma->vm_flags |= VM_PFNMAP | VM_DONTEXPAND | VM_DONTDUMP | VM_IO;
	vma->vm_निजी_data = encl;

	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ sgx_get_unmapped_area(काष्ठा file *file,
					   अचिन्हित दीर्घ addr,
					   अचिन्हित दीर्घ len,
					   अचिन्हित दीर्घ pgoff,
					   अचिन्हित दीर्घ flags)
अणु
	अगर ((flags & MAP_TYPE) == MAP_PRIVATE)
		वापस -EINVAL;

	अगर (flags & MAP_FIXED)
		वापस addr;

	वापस current->mm->get_unmapped_area(file, addr, len, pgoff, flags);
पूर्ण

#अगर_घोषित CONFIG_COMPAT
अटल दीर्घ sgx_compat_ioctl(काष्ठा file *filep, अचिन्हित पूर्णांक cmd,
			      अचिन्हित दीर्घ arg)
अणु
	वापस sgx_ioctl(filep, cmd, arg);
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा file_operations sgx_encl_fops = अणु
	.owner			= THIS_MODULE,
	.खोलो			= sgx_खोलो,
	.release		= sgx_release,
	.unlocked_ioctl		= sgx_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl		= sgx_compat_ioctl,
#पूर्ण_अगर
	.mmap			= sgx_mmap,
	.get_unmapped_area	= sgx_get_unmapped_area,
पूर्ण;

अटल काष्ठा miscdevice sgx_dev_enclave = अणु
	.minor = MISC_DYNAMIC_MINOR,
	.name = "sgx_enclave",
	.nodename = "sgx_enclave",
	.fops = &sgx_encl_fops,
पूर्ण;

पूर्णांक __init sgx_drv_init(व्योम)
अणु
	अचिन्हित पूर्णांक eax, ebx, ecx, edx;
	u64 attr_mask;
	u64 xfrm_mask;
	पूर्णांक ret;

	अगर (!cpu_feature_enabled(X86_FEATURE_SGX_LC))
		वापस -ENODEV;

	cpuid_count(SGX_CPUID, 0, &eax, &ebx, &ecx, &edx);

	अगर (!(eax & 1))  अणु
		pr_err("SGX disabled: SGX1 instruction support not available.\n");
		वापस -ENODEV;
	पूर्ण

	sgx_misc_reserved_mask = ~ebx | SGX_MISC_RESERVED_MASK;

	cpuid_count(SGX_CPUID, 1, &eax, &ebx, &ecx, &edx);

	attr_mask = (((u64)ebx) << 32) + (u64)eax;
	sgx_attributes_reserved_mask = ~attr_mask | SGX_ATTR_RESERVED_MASK;

	अगर (cpu_feature_enabled(X86_FEATURE_OSXSAVE)) अणु
		xfrm_mask = (((u64)edx) << 32) + (u64)ecx;
		sgx_xfrm_reserved_mask = ~xfrm_mask;
	पूर्ण

	ret = misc_रेजिस्टर(&sgx_dev_enclave);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण
