<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * arc_hostlink.c: Pseuकरो-driver क्रम Metaware provided "hostlink" facility
 *
 * Allows Linux userland access to host in असलence of any peripherals.
 *
 * Copyright (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 */

#समावेश <linux/fs.h>		/* file_operations */
#समावेश <linux/miscdevice.h>
#समावेश <linux/mm.h>		/* VM_IO */
#समावेश <linux/module.h>
#समावेश <linux/uaccess.h>

अटल अचिन्हित अक्षर __HOSTLINK__[4 * PAGE_SIZE] __aligned(PAGE_SIZE);

अटल पूर्णांक arc_hl_mmap(काष्ठा file *fp, काष्ठा vm_area_काष्ठा *vma)
अणु
	vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);

	अगर (io_remap_pfn_range(vma, vma->vm_start, vma->vm_pgoff,
			       vma->vm_end - vma->vm_start,
			       vma->vm_page_prot)) अणु
		pr_warn("Hostlink buffer mmap ERROR\n");
		वापस -EAGAIN;
	पूर्ण
	वापस 0;
पूर्ण

अटल दीर्घ arc_hl_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
			अचिन्हित दीर्घ arg)
अणु
	/* we only support, वापसing the physical addr to mmap in user space */
	put_user((अचिन्हित पूर्णांक)__HOSTLINK__, (पूर्णांक __user *)arg);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations arc_hl_fops = अणु
	.unlocked_ioctl	= arc_hl_ioctl,
	.mmap		= arc_hl_mmap,
पूर्ण;

अटल काष्ठा miscdevice arc_hl_dev = अणु
	.minor	= MISC_DYNAMIC_MINOR,
	.name	= "hostlink",
	.fops	= &arc_hl_fops
पूर्ण;

अटल पूर्णांक __init arc_hl_init(व्योम)
अणु
	pr_info("ARC Hostlink driver mmap at 0x%p\n", __HOSTLINK__);
	वापस misc_रेजिस्टर(&arc_hl_dev);
पूर्ण
module_init(arc_hl_init);
