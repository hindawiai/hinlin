<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* flash.c: Allow mmap access to the OBP Flash, क्रम OBP updates.
 *
 * Copyright (C) 1997  Eddie C. Dost  (ecd@skynet.be)
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/miscdevice.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/poll.h>
#समावेश <linux/mutex.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/mm.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/upa.h>

अटल DEFINE_MUTEX(flash_mutex);
अटल DEFINE_SPINLOCK(flash_lock);
अटल काष्ठा अणु
	अचिन्हित दीर्घ पढ़ो_base;	/* Physical पढ़ो address */
	अचिन्हित दीर्घ ग_लिखो_base;	/* Physical ग_लिखो address */
	अचिन्हित दीर्घ पढ़ो_size;	/* Size of पढ़ो area */
	अचिन्हित दीर्घ ग_लिखो_size;	/* Size of ग_लिखो area */
	अचिन्हित दीर्घ busy;		/* In use? */
पूर्ण flash;

अटल पूर्णांक
flash_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	अचिन्हित दीर्घ addr;
	अचिन्हित दीर्घ size;

	spin_lock(&flash_lock);
	अगर (flash.पढ़ो_base == flash.ग_लिखो_base) अणु
		addr = flash.पढ़ो_base;
		size = flash.पढ़ो_size;
	पूर्ण अन्यथा अणु
		अगर ((vma->vm_flags & VM_READ) &&
		    (vma->vm_flags & VM_WRITE)) अणु
			spin_unlock(&flash_lock);
			वापस -EINVAL;
		पूर्ण
		अगर (vma->vm_flags & VM_READ) अणु
			addr = flash.पढ़ो_base;
			size = flash.पढ़ो_size;
		पूर्ण अन्यथा अगर (vma->vm_flags & VM_WRITE) अणु
			addr = flash.ग_लिखो_base;
			size = flash.ग_लिखो_size;
		पूर्ण अन्यथा अणु
			spin_unlock(&flash_lock);
			वापस -ENXIO;
		पूर्ण
	पूर्ण
	spin_unlock(&flash_lock);

	अगर ((vma->vm_pgoff << PAGE_SHIFT) > size)
		वापस -ENXIO;
	addr = vma->vm_pgoff + (addr >> PAGE_SHIFT);

	अगर (vma->vm_end - (vma->vm_start + (vma->vm_pgoff << PAGE_SHIFT)) > size)
		size = vma->vm_end - (vma->vm_start + (vma->vm_pgoff << PAGE_SHIFT));

	vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);

	अगर (io_remap_pfn_range(vma, vma->vm_start, addr, size, vma->vm_page_prot))
		वापस -EAGAIN;
		
	वापस 0;
पूर्ण

अटल दीर्घ दीर्घ
flash_llseek(काष्ठा file *file, दीर्घ दीर्घ offset, पूर्णांक origin)
अणु
	mutex_lock(&flash_mutex);
	चयन (origin) अणु
		हाल 0:
			file->f_pos = offset;
			अवरोध;
		हाल 1:
			file->f_pos += offset;
			अगर (file->f_pos > flash.पढ़ो_size)
				file->f_pos = flash.पढ़ो_size;
			अवरोध;
		हाल 2:
			file->f_pos = flash.पढ़ो_size;
			अवरोध;
		शेष:
			mutex_unlock(&flash_mutex);
			वापस -EINVAL;
	पूर्ण
	mutex_unlock(&flash_mutex);
	वापस file->f_pos;
पूर्ण

अटल sमाप_प्रकार
flash_पढ़ो(काष्ठा file * file, अक्षर __user * buf,
	   माप_प्रकार count, loff_t *ppos)
अणु
	loff_t p = *ppos;
	पूर्णांक i;

	अगर (count > flash.पढ़ो_size - p)
		count = flash.पढ़ो_size - p;

	क्रम (i = 0; i < count; i++) अणु
		u8 data = upa_पढ़ोb(flash.पढ़ो_base + p + i);
		अगर (put_user(data, buf))
			वापस -EFAULT;
		buf++;
	पूर्ण

	*ppos += count;
	वापस count;
पूर्ण

अटल पूर्णांक
flash_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	mutex_lock(&flash_mutex);
	अगर (test_and_set_bit(0, (व्योम *)&flash.busy) != 0) अणु
		mutex_unlock(&flash_mutex);
		वापस -EBUSY;
	पूर्ण

	mutex_unlock(&flash_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक
flash_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	spin_lock(&flash_lock);
	flash.busy = 0;
	spin_unlock(&flash_lock);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations flash_fops = अणु
	/* no ग_लिखो to the Flash, use mmap
	 * and play flash dependent tricks.
	 */
	.owner =	THIS_MODULE,
	.llseek =	flash_llseek,
	.पढ़ो =		flash_पढ़ो,
	.mmap =		flash_mmap,
	.खोलो =		flash_खोलो,
	.release =	flash_release,
पूर्ण;

अटल काष्ठा miscdevice flash_dev = अणु SBUS_FLASH_MINOR, "flash", &flash_fops पूर्ण;

अटल पूर्णांक flash_probe(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा device_node *dp = op->dev.of_node;
	काष्ठा device_node *parent;

	parent = dp->parent;

	अगर (!of_node_name_eq(parent, "sbus") &&
	    !of_node_name_eq(parent, "sbi") &&
	    !of_node_name_eq(parent, "ebus"))
		वापस -ENODEV;

	flash.पढ़ो_base = op->resource[0].start;
	flash.पढ़ो_size = resource_size(&op->resource[0]);
	अगर (op->resource[1].flags) अणु
		flash.ग_लिखो_base = op->resource[1].start;
		flash.ग_लिखो_size = resource_size(&op->resource[1]);
	पूर्ण अन्यथा अणु
		flash.ग_लिखो_base = op->resource[0].start;
		flash.ग_लिखो_size = resource_size(&op->resource[0]);
	पूर्ण
	flash.busy = 0;

	prपूर्णांकk(KERN_INFO "%pOF: OBP Flash, RD %lx[%lx] WR %lx[%lx]\n",
	       op->dev.of_node,
	       flash.पढ़ो_base, flash.पढ़ो_size,
	       flash.ग_लिखो_base, flash.ग_लिखो_size);

	वापस misc_रेजिस्टर(&flash_dev);
पूर्ण

अटल पूर्णांक flash_हटाओ(काष्ठा platक्रमm_device *op)
अणु
	misc_deरेजिस्टर(&flash_dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id flash_match[] = अणु
	अणु
		.name = "flashprom",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, flash_match);

अटल काष्ठा platक्रमm_driver flash_driver = अणु
	.driver = अणु
		.name = "flash",
		.of_match_table = flash_match,
	पूर्ण,
	.probe		= flash_probe,
	.हटाओ		= flash_हटाओ,
पूर्ण;

module_platक्रमm_driver(flash_driver);

MODULE_LICENSE("GPL");
