<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * arch/um/drivers/mmapper_kern.c
 *
 * BRIEF MODULE DESCRIPTION
 *
 * Copyright (C) 2000 RidgeRun, Inc.
 * Author: RidgeRun, Inc.
 *         Greg Lonnon glonnon@ridgerun.com or info@ridgerun.com
 *
 */

#समावेश <linux/मानकघोष.स>
#समावेश <linux/types.h>
#समावेश <linux/fs.h>
#समावेश <linux/init.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/module.h>
#समावेश <linux/mm.h>

#समावेश <linux/uaccess.h>
#समावेश <mem_user.h>

/* These are set in mmapper_init, which is called at boot समय */
अटल अचिन्हित दीर्घ mmapper_size;
अटल अचिन्हित दीर्घ p_buf;
अटल अक्षर *v_buf;

अटल sमाप_प्रकार mmapper_पढ़ो(काष्ठा file *file, अक्षर __user *buf, माप_प्रकार count,
			    loff_t *ppos)
अणु
	वापस simple_पढ़ो_from_buffer(buf, count, ppos, v_buf, mmapper_size);
पूर्ण

अटल sमाप_प्रकार mmapper_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
			     माप_प्रकार count, loff_t *ppos)
अणु
	अगर (*ppos > mmapper_size)
		वापस -EINVAL;

	वापस simple_ग_लिखो_to_buffer(v_buf, mmapper_size, ppos, buf, count);
पूर्ण

अटल दीर्घ mmapper_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	वापस -ENOIOCTLCMD;
पूर्ण

अटल पूर्णांक mmapper_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	पूर्णांक ret = -EINVAL;
	पूर्णांक size;

	अगर (vma->vm_pgoff != 0)
		जाओ out;

	size = vma->vm_end - vma->vm_start;
	अगर (size > mmapper_size)
		वापस -EFAULT;

	/*
	 * XXX A comment above remap_pfn_range says it should only be
	 * called when the mm semaphore is held
	 */
	अगर (remap_pfn_range(vma, vma->vm_start, p_buf >> PAGE_SHIFT, size,
			    vma->vm_page_prot))
		जाओ out;
	ret = 0;
out:
	वापस ret;
पूर्ण

अटल पूर्णांक mmapper_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक mmapper_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations mmapper_fops = अणु
	.owner		= THIS_MODULE,
	.पढ़ो		= mmapper_पढ़ो,
	.ग_लिखो		= mmapper_ग_लिखो,
	.unlocked_ioctl	= mmapper_ioctl,
	.mmap		= mmapper_mmap,
	.खोलो		= mmapper_खोलो,
	.release	= mmapper_release,
	.llseek		= शेष_llseek,
पूर्ण;

/*
 * No locking needed - only used (and modअगरied) by below initcall and निकासcall.
 */
अटल काष्ठा miscdevice mmapper_dev = अणु
	.minor		= MISC_DYNAMIC_MINOR,
	.name		= "mmapper",
	.fops		= &mmapper_fops
पूर्ण;

अटल पूर्णांक __init mmapper_init(व्योम)
अणु
	पूर्णांक err;

	prपूर्णांकk(KERN_INFO "Mapper v0.1\n");

	v_buf = (अक्षर *) find_iomem("mmapper", &mmapper_size);
	अगर (mmapper_size == 0) अणु
		prपूर्णांकk(KERN_ERR "mmapper_init - find_iomem failed\n");
		वापस -ENODEV;
	पूर्ण
	p_buf = __pa(v_buf);

	err = misc_रेजिस्टर(&mmapper_dev);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "mmapper - misc_register failed, err = %d\n",
		       err);
		वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम mmapper_निकास(व्योम)
अणु
	misc_deरेजिस्टर(&mmapper_dev);
पूर्ण

module_init(mmapper_init);
module_निकास(mmapper_निकास);

MODULE_AUTHOR("Greg Lonnon <glonnon@ridgerun.com>");
MODULE_DESCRIPTION("DSPLinux simulator mmapper driver");
MODULE_LICENSE("GPL");
