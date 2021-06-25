<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * VMEbus User access driver
 *
 * Author: Martyn Welch <martyn.welch@ge.com>
 * Copyright 2008 GE Intelligent Platक्रमms Embedded Systems, Inc.
 *
 * Based on work by:
 *   Tom Armistead and Ajit Prem
 *     Copyright 2004 Motorola Inc.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/refcount.h>
#समावेश <linux/cdev.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/ioctl.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/pci.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/types.h>

#समावेश <linux/पन.स>
#समावेश <linux/uaccess.h>
#समावेश <linux/vme.h>

#समावेश "vme_user.h"

अटल स्थिर अक्षर driver_name[] = "vme_user";

अटल पूर्णांक bus[VME_USER_BUS_MAX];
अटल अचिन्हित पूर्णांक bus_num;

/* Currently Documentation/admin-guide/devices.rst defines the
 * following क्रम VME:
 *
 * 221 अक्षर	VME bus
 *		  0 = /dev/bus/vme/m0		First master image
 *		  1 = /dev/bus/vme/m1		Second master image
 *		  2 = /dev/bus/vme/m2		Third master image
 *		  3 = /dev/bus/vme/m3		Fourth master image
 *		  4 = /dev/bus/vme/s0		First slave image
 *		  5 = /dev/bus/vme/s1		Second slave image
 *		  6 = /dev/bus/vme/s2		Third slave image
 *		  7 = /dev/bus/vme/s3		Fourth slave image
 *		  8 = /dev/bus/vme/ctl		Control
 *
 *		It is expected that all VME bus drivers will use the
 *		same पूर्णांकerface.  For पूर्णांकerface करोcumentation see
 *		http://www.vmelinux.org/.
 *
 * However the VME driver at http://www.vmelinux.org/ is rather old and करोesn't
 * even support the tsi148 chipset (which has 8 master and 8 slave winकरोws).
 * We'll run with this क्रम now as far as possible, however it probably makes
 * sense to get rid of the old mappings and just करो everything dynamically.
 *
 * So क्रम now, we'll restrict the driver to providing 4 masters and 4 slaves as
 * defined above and try to support at least some of the पूर्णांकerface from
 * http://www.vmelinux.org/ as an alternative the driver can be written
 * providing a saner पूर्णांकerface later.
 *
 * The vmelinux.org driver never supported slave images, the devices reserved
 * क्रम slaves were repurposed to support all 8 master images on the UniverseII!
 * We shall support 4 masters and 4 slaves with this driver.
 */
#घोषणा VME_MAJOR	221	/* VME Major Device Number */
#घोषणा VME_DEVS	9	/* Number of dev entries */

#घोषणा MASTER_MINOR	0
#घोषणा MASTER_MAX	3
#घोषणा SLAVE_MINOR	4
#घोषणा SLAVE_MAX	7
#घोषणा CONTROL_MINOR	8

#घोषणा PCI_BUF_SIZE  0x20000	/* Size of one slave image buffer */

/*
 * Structure to handle image related parameters.
 */
काष्ठा image_desc अणु
	व्योम *kern_buf;	/* Buffer address in kernel space */
	dma_addr_t pci_buf;	/* Buffer address in PCI address space */
	अचिन्हित दीर्घ दीर्घ size_buf;	/* Buffer size */
	काष्ठा mutex mutex;	/* Mutex क्रम locking image */
	काष्ठा device *device;	/* Sysfs device */
	काष्ठा vme_resource *resource;	/* VME resource */
	पूर्णांक mmap_count;		/* Number of current mmap's */
पूर्ण;

अटल काष्ठा image_desc image[VME_DEVS];

अटल काष्ठा cdev *vme_user_cdev;		/* Character device */
अटल काष्ठा class *vme_user_sysfs_class;	/* Sysfs class */
अटल काष्ठा vme_dev *vme_user_bridge;		/* Poपूर्णांकer to user device */

अटल स्थिर पूर्णांक type[VME_DEVS] = अणु	MASTER_MINOR,	MASTER_MINOR,
					MASTER_MINOR,	MASTER_MINOR,
					SLAVE_MINOR,	SLAVE_MINOR,
					SLAVE_MINOR,	SLAVE_MINOR,
					CONTROL_MINOR
				पूर्ण;

काष्ठा vme_user_vma_priv अणु
	अचिन्हित पूर्णांक minor;
	refcount_t refcnt;
पूर्ण;

अटल sमाप_प्रकार resource_to_user(पूर्णांक minor, अक्षर __user *buf, माप_प्रकार count,
				loff_t *ppos)
अणु
	sमाप_प्रकार copied = 0;

	अगर (count > image[minor].size_buf)
		count = image[minor].size_buf;

	copied = vme_master_पढ़ो(image[minor].resource, image[minor].kern_buf,
				 count, *ppos);
	अगर (copied < 0)
		वापस (पूर्णांक)copied;

	अगर (copy_to_user(buf, image[minor].kern_buf, (अचिन्हित दीर्घ)copied))
		वापस -EFAULT;

	वापस copied;
पूर्ण

अटल sमाप_प्रकार resource_from_user(अचिन्हित पूर्णांक minor, स्थिर अक्षर __user *buf,
				  माप_प्रकार count, loff_t *ppos)
अणु
	अगर (count > image[minor].size_buf)
		count = image[minor].size_buf;

	अगर (copy_from_user(image[minor].kern_buf, buf, (अचिन्हित दीर्घ)count))
		वापस -EFAULT;

	वापस vme_master_ग_लिखो(image[minor].resource, image[minor].kern_buf,
				count, *ppos);
पूर्ण

अटल sमाप_प्रकार buffer_to_user(अचिन्हित पूर्णांक minor, अक्षर __user *buf,
			      माप_प्रकार count, loff_t *ppos)
अणु
	व्योम *image_ptr;

	image_ptr = image[minor].kern_buf + *ppos;
	अगर (copy_to_user(buf, image_ptr, (अचिन्हित दीर्घ)count))
		वापस -EFAULT;

	वापस count;
पूर्ण

अटल sमाप_प्रकार buffer_from_user(अचिन्हित पूर्णांक minor, स्थिर अक्षर __user *buf,
				माप_प्रकार count, loff_t *ppos)
अणु
	व्योम *image_ptr;

	image_ptr = image[minor].kern_buf + *ppos;
	अगर (copy_from_user(image_ptr, buf, (अचिन्हित दीर्घ)count))
		वापस -EFAULT;

	वापस count;
पूर्ण

अटल sमाप_प्रकार vme_user_पढ़ो(काष्ठा file *file, अक्षर __user *buf, माप_प्रकार count,
			     loff_t *ppos)
अणु
	अचिन्हित पूर्णांक minor = iminor(file_inode(file));
	sमाप_प्रकार retval;
	माप_प्रकार image_size;

	अगर (minor == CONTROL_MINOR)
		वापस 0;

	mutex_lock(&image[minor].mutex);

	/* XXX Do we *really* want this helper - we can use vme_*_get ? */
	image_size = vme_get_size(image[minor].resource);

	/* Ensure we are starting at a valid location */
	अगर ((*ppos < 0) || (*ppos > (image_size - 1))) अणु
		mutex_unlock(&image[minor].mutex);
		वापस 0;
	पूर्ण

	/* Ensure not पढ़ोing past end of the image */
	अगर (*ppos + count > image_size)
		count = image_size - *ppos;

	चयन (type[minor]) अणु
	हाल MASTER_MINOR:
		retval = resource_to_user(minor, buf, count, ppos);
		अवरोध;
	हाल SLAVE_MINOR:
		retval = buffer_to_user(minor, buf, count, ppos);
		अवरोध;
	शेष:
		retval = -EINVAL;
	पूर्ण

	mutex_unlock(&image[minor].mutex);
	अगर (retval > 0)
		*ppos += retval;

	वापस retval;
पूर्ण

अटल sमाप_प्रकार vme_user_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
			      माप_प्रकार count, loff_t *ppos)
अणु
	अचिन्हित पूर्णांक minor = iminor(file_inode(file));
	sमाप_प्रकार retval;
	माप_प्रकार image_size;

	अगर (minor == CONTROL_MINOR)
		वापस 0;

	mutex_lock(&image[minor].mutex);

	image_size = vme_get_size(image[minor].resource);

	/* Ensure we are starting at a valid location */
	अगर ((*ppos < 0) || (*ppos > (image_size - 1))) अणु
		mutex_unlock(&image[minor].mutex);
		वापस 0;
	पूर्ण

	/* Ensure not पढ़ोing past end of the image */
	अगर (*ppos + count > image_size)
		count = image_size - *ppos;

	चयन (type[minor]) अणु
	हाल MASTER_MINOR:
		retval = resource_from_user(minor, buf, count, ppos);
		अवरोध;
	हाल SLAVE_MINOR:
		retval = buffer_from_user(minor, buf, count, ppos);
		अवरोध;
	शेष:
		retval = -EINVAL;
	पूर्ण

	mutex_unlock(&image[minor].mutex);

	अगर (retval > 0)
		*ppos += retval;

	वापस retval;
पूर्ण

अटल loff_t vme_user_llseek(काष्ठा file *file, loff_t off, पूर्णांक whence)
अणु
	अचिन्हित पूर्णांक minor = iminor(file_inode(file));
	माप_प्रकार image_size;
	loff_t res;

	चयन (type[minor]) अणु
	हाल MASTER_MINOR:
	हाल SLAVE_MINOR:
		mutex_lock(&image[minor].mutex);
		image_size = vme_get_size(image[minor].resource);
		res = fixed_size_llseek(file, off, whence, image_size);
		mutex_unlock(&image[minor].mutex);
		वापस res;
	पूर्ण

	वापस -EINVAL;
पूर्ण

/*
 * The ioctls provided by the old VME access method (the one at vmelinux.org)
 * are most certainly wrong as the effectively push the रेजिस्टरs layout
 * through to user space. Given that the VME core can handle multiple bridges,
 * with dअगरferent रेजिस्टर layouts this is most certainly not the way to go.
 *
 * We aren't using the काष्ठाures defined in the Motorola driver either - these
 * are also quite low level, however we should use the definitions that have
 * alपढ़ोy been defined.
 */
अटल पूर्णांक vme_user_ioctl(काष्ठा inode *inode, काष्ठा file *file,
			  अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा vme_master master;
	काष्ठा vme_slave slave;
	काष्ठा vme_irq_id irq_req;
	अचिन्हित दीर्घ copied;
	अचिन्हित पूर्णांक minor = iminor(inode);
	पूर्णांक retval;
	dma_addr_t pci_addr;
	व्योम __user *argp = (व्योम __user *)arg;

	चयन (type[minor]) अणु
	हाल CONTROL_MINOR:
		चयन (cmd) अणु
		हाल VME_IRQ_GEN:
			copied = copy_from_user(&irq_req, argp,
						माप(irq_req));
			अगर (copied) अणु
				pr_warn("Partial copy from userspace\n");
				वापस -EFAULT;
			पूर्ण

			वापस vme_irq_generate(vme_user_bridge,
						  irq_req.level,
						  irq_req.statid);
		पूर्ण
		अवरोध;
	हाल MASTER_MINOR:
		चयन (cmd) अणु
		हाल VME_GET_MASTER:
			स_रखो(&master, 0, माप(master));

			/* XXX	We करो not want to push aspace, cycle and width
			 *	to userspace as they are
			 */
			retval = vme_master_get(image[minor].resource,
						&master.enable,
						&master.vme_addr,
						&master.size, &master.aspace,
						&master.cycle, &master.dwidth);

			copied = copy_to_user(argp, &master,
					      माप(master));
			अगर (copied) अणु
				pr_warn("Partial copy to userspace\n");
				वापस -EFAULT;
			पूर्ण

			वापस retval;

		हाल VME_SET_MASTER:

			अगर (image[minor].mmap_count != 0) अणु
				pr_warn("Can't adjust mapped window\n");
				वापस -EPERM;
			पूर्ण

			copied = copy_from_user(&master, argp, माप(master));
			अगर (copied) अणु
				pr_warn("Partial copy from userspace\n");
				वापस -EFAULT;
			पूर्ण

			/* XXX	We करो not want to push aspace, cycle and width
			 *	to userspace as they are
			 */
			वापस vme_master_set(image[minor].resource,
				master.enable, master.vme_addr, master.size,
				master.aspace, master.cycle, master.dwidth);

			अवरोध;
		पूर्ण
		अवरोध;
	हाल SLAVE_MINOR:
		चयन (cmd) अणु
		हाल VME_GET_SLAVE:
			स_रखो(&slave, 0, माप(slave));

			/* XXX	We करो not want to push aspace, cycle and width
			 *	to userspace as they are
			 */
			retval = vme_slave_get(image[minor].resource,
					       &slave.enable, &slave.vme_addr,
					       &slave.size, &pci_addr,
					       &slave.aspace, &slave.cycle);

			copied = copy_to_user(argp, &slave,
					      माप(slave));
			अगर (copied) अणु
				pr_warn("Partial copy to userspace\n");
				वापस -EFAULT;
			पूर्ण

			वापस retval;

		हाल VME_SET_SLAVE:

			copied = copy_from_user(&slave, argp, माप(slave));
			अगर (copied) अणु
				pr_warn("Partial copy from userspace\n");
				वापस -EFAULT;
			पूर्ण

			/* XXX	We करो not want to push aspace, cycle and width
			 *	to userspace as they are
			 */
			वापस vme_slave_set(image[minor].resource,
				slave.enable, slave.vme_addr, slave.size,
				image[minor].pci_buf, slave.aspace,
				slave.cycle);

			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल दीर्घ
vme_user_unlocked_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	पूर्णांक ret;
	काष्ठा inode *inode = file_inode(file);
	अचिन्हित पूर्णांक minor = iminor(inode);

	mutex_lock(&image[minor].mutex);
	ret = vme_user_ioctl(inode, file, cmd, arg);
	mutex_unlock(&image[minor].mutex);

	वापस ret;
पूर्ण

अटल व्योम vme_user_vm_खोलो(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा vme_user_vma_priv *vma_priv = vma->vm_निजी_data;

	refcount_inc(&vma_priv->refcnt);
पूर्ण

अटल व्योम vme_user_vm_बंद(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा vme_user_vma_priv *vma_priv = vma->vm_निजी_data;
	अचिन्हित पूर्णांक minor = vma_priv->minor;

	अगर (!refcount_dec_and_test(&vma_priv->refcnt))
		वापस;

	mutex_lock(&image[minor].mutex);
	image[minor].mmap_count--;
	mutex_unlock(&image[minor].mutex);

	kमुक्त(vma_priv);
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा vme_user_vm_ops = अणु
	.खोलो = vme_user_vm_खोलो,
	.बंद = vme_user_vm_बंद,
पूर्ण;

अटल पूर्णांक vme_user_master_mmap(अचिन्हित पूर्णांक minor, काष्ठा vm_area_काष्ठा *vma)
अणु
	पूर्णांक err;
	काष्ठा vme_user_vma_priv *vma_priv;

	mutex_lock(&image[minor].mutex);

	err = vme_master_mmap(image[minor].resource, vma);
	अगर (err) अणु
		mutex_unlock(&image[minor].mutex);
		वापस err;
	पूर्ण

	vma_priv = kदो_स्मृति(माप(*vma_priv), GFP_KERNEL);
	अगर (!vma_priv) अणु
		mutex_unlock(&image[minor].mutex);
		वापस -ENOMEM;
	पूर्ण

	vma_priv->minor = minor;
	refcount_set(&vma_priv->refcnt, 1);
	vma->vm_ops = &vme_user_vm_ops;
	vma->vm_निजी_data = vma_priv;

	image[minor].mmap_count++;

	mutex_unlock(&image[minor].mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक vme_user_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	अचिन्हित पूर्णांक minor = iminor(file_inode(file));

	अगर (type[minor] == MASTER_MINOR)
		वापस vme_user_master_mmap(minor, vma);

	वापस -ENODEV;
पूर्ण

अटल स्थिर काष्ठा file_operations vme_user_fops = अणु
	.पढ़ो = vme_user_पढ़ो,
	.ग_लिखो = vme_user_ग_लिखो,
	.llseek = vme_user_llseek,
	.unlocked_ioctl = vme_user_unlocked_ioctl,
	.compat_ioctl = compat_ptr_ioctl,
	.mmap = vme_user_mmap,
पूर्ण;

अटल पूर्णांक vme_user_match(काष्ठा vme_dev *vdev)
अणु
	पूर्णांक i;

	पूर्णांक cur_bus = vme_bus_num(vdev);
	पूर्णांक cur_slot = vme_slot_num(vdev);

	क्रम (i = 0; i < bus_num; i++)
		अगर ((cur_bus == bus[i]) && (cur_slot == vdev->num))
			वापस 1;

	वापस 0;
पूर्ण

/*
 * In this simple access driver, the old behaviour is being preserved as much
 * as practical. We will thereक्रमe reserve the buffers and request the images
 * here so that we करोn't have to करो it later.
 */
अटल पूर्णांक vme_user_probe(काष्ठा vme_dev *vdev)
अणु
	पूर्णांक i, err;
	अक्षर *name;

	/* Save poपूर्णांकer to the bridge device */
	अगर (vme_user_bridge) अणु
		dev_err(&vdev->dev, "Driver can only be loaded for 1 device\n");
		err = -EINVAL;
		जाओ err_dev;
	पूर्ण
	vme_user_bridge = vdev;

	/* Initialise descriptors */
	क्रम (i = 0; i < VME_DEVS; i++) अणु
		image[i].kern_buf = शून्य;
		image[i].pci_buf = 0;
		mutex_init(&image[i].mutex);
		image[i].device = शून्य;
		image[i].resource = शून्य;
	पूर्ण

	/* Assign major and minor numbers क्रम the driver */
	err = रेजिस्टर_chrdev_region(MKDEV(VME_MAJOR, 0), VME_DEVS,
				     driver_name);
	अगर (err) अणु
		dev_warn(&vdev->dev, "Error getting Major Number %d for driver.\n",
			 VME_MAJOR);
		जाओ err_region;
	पूर्ण

	/* Register the driver as a अक्षर device */
	vme_user_cdev = cdev_alloc();
	अगर (!vme_user_cdev) अणु
		err = -ENOMEM;
		जाओ err_अक्षर;
	पूर्ण
	vme_user_cdev->ops = &vme_user_fops;
	vme_user_cdev->owner = THIS_MODULE;
	err = cdev_add(vme_user_cdev, MKDEV(VME_MAJOR, 0), VME_DEVS);
	अगर (err)
		जाओ err_class;

	/* Request slave resources and allocate buffers (128kB wide) */
	क्रम (i = SLAVE_MINOR; i < (SLAVE_MAX + 1); i++) अणु
		/* XXX Need to properly request attributes */
		/* For ca91cx42 bridge there are only two slave winकरोws
		 * supporting A16 addressing, so we request A24 supported
		 * by all winकरोws.
		 */
		image[i].resource = vme_slave_request(vme_user_bridge,
						      VME_A24, VME_SCT);
		अगर (!image[i].resource) अणु
			dev_warn(&vdev->dev,
				 "Unable to allocate slave resource\n");
			err = -ENOMEM;
			जाओ err_slave;
		पूर्ण
		image[i].size_buf = PCI_BUF_SIZE;
		image[i].kern_buf = vme_alloc_consistent(image[i].resource,
							 image[i].size_buf,
							 &image[i].pci_buf);
		अगर (!image[i].kern_buf) अणु
			dev_warn(&vdev->dev,
				 "Unable to allocate memory for buffer\n");
			image[i].pci_buf = 0;
			vme_slave_मुक्त(image[i].resource);
			err = -ENOMEM;
			जाओ err_slave;
		पूर्ण
	पूर्ण

	/*
	 * Request master resources allocate page sized buffers क्रम small
	 * पढ़ोs and ग_लिखोs
	 */
	क्रम (i = MASTER_MINOR; i < (MASTER_MAX + 1); i++) अणु
		/* XXX Need to properly request attributes */
		image[i].resource = vme_master_request(vme_user_bridge,
						       VME_A32, VME_SCT,
						       VME_D32);
		अगर (!image[i].resource) अणु
			dev_warn(&vdev->dev,
				 "Unable to allocate master resource\n");
			err = -ENOMEM;
			जाओ err_master;
		पूर्ण
		image[i].size_buf = PCI_BUF_SIZE;
		image[i].kern_buf = kदो_स्मृति(image[i].size_buf, GFP_KERNEL);
		अगर (!image[i].kern_buf) अणु
			err = -ENOMEM;
			vme_master_मुक्त(image[i].resource);
			जाओ err_master;
		पूर्ण
	पूर्ण

	/* Create sysfs entries - on udev प्रणालीs this creates the dev files */
	vme_user_sysfs_class = class_create(THIS_MODULE, driver_name);
	अगर (IS_ERR(vme_user_sysfs_class)) अणु
		dev_err(&vdev->dev, "Error creating vme_user class.\n");
		err = PTR_ERR(vme_user_sysfs_class);
		जाओ err_master;
	पूर्ण

	/* Add sysfs Entries */
	क्रम (i = 0; i < VME_DEVS; i++) अणु
		पूर्णांक num;

		चयन (type[i]) अणु
		हाल MASTER_MINOR:
			name = "bus/vme/m%d";
			अवरोध;
		हाल CONTROL_MINOR:
			name = "bus/vme/ctl";
			अवरोध;
		हाल SLAVE_MINOR:
			name = "bus/vme/s%d";
			अवरोध;
		शेष:
			err = -EINVAL;
			जाओ err_sysfs;
		पूर्ण

		num = (type[i] == SLAVE_MINOR) ? i - (MASTER_MAX + 1) : i;
		image[i].device = device_create(vme_user_sysfs_class, शून्य,
						MKDEV(VME_MAJOR, i), शून्य,
						name, num);
		अगर (IS_ERR(image[i].device)) अणु
			dev_info(&vdev->dev, "Error creating sysfs device\n");
			err = PTR_ERR(image[i].device);
			जाओ err_sysfs;
		पूर्ण
	पूर्ण

	वापस 0;

err_sysfs:
	जबतक (i > 0) अणु
		i--;
		device_destroy(vme_user_sysfs_class, MKDEV(VME_MAJOR, i));
	पूर्ण
	class_destroy(vme_user_sysfs_class);

	/* Ensure counter set correctly to unalloc all master winकरोws */
	i = MASTER_MAX + 1;
err_master:
	जबतक (i > MASTER_MINOR) अणु
		i--;
		kमुक्त(image[i].kern_buf);
		vme_master_मुक्त(image[i].resource);
	पूर्ण

	/*
	 * Ensure counter set correctly to unalloc all slave winकरोws and buffers
	 */
	i = SLAVE_MAX + 1;
err_slave:
	जबतक (i > SLAVE_MINOR) अणु
		i--;
		vme_मुक्त_consistent(image[i].resource, image[i].size_buf,
				    image[i].kern_buf, image[i].pci_buf);
		vme_slave_मुक्त(image[i].resource);
	पूर्ण
err_class:
	cdev_del(vme_user_cdev);
err_अक्षर:
	unरेजिस्टर_chrdev_region(MKDEV(VME_MAJOR, 0), VME_DEVS);
err_region:
err_dev:
	वापस err;
पूर्ण

अटल व्योम vme_user_हटाओ(काष्ठा vme_dev *dev)
अणु
	पूर्णांक i;

	/* Remove sysfs Entries */
	क्रम (i = 0; i < VME_DEVS; i++) अणु
		mutex_destroy(&image[i].mutex);
		device_destroy(vme_user_sysfs_class, MKDEV(VME_MAJOR, i));
	पूर्ण
	class_destroy(vme_user_sysfs_class);

	क्रम (i = MASTER_MINOR; i < (MASTER_MAX + 1); i++) अणु
		kमुक्त(image[i].kern_buf);
		vme_master_मुक्त(image[i].resource);
	पूर्ण

	क्रम (i = SLAVE_MINOR; i < (SLAVE_MAX + 1); i++) अणु
		vme_slave_set(image[i].resource, 0, 0, 0, 0, VME_A32, 0);
		vme_मुक्त_consistent(image[i].resource, image[i].size_buf,
				    image[i].kern_buf, image[i].pci_buf);
		vme_slave_मुक्त(image[i].resource);
	पूर्ण

	/* Unरेजिस्टर device driver */
	cdev_del(vme_user_cdev);

	/* Unरेजिस्टर the major and minor device numbers */
	unरेजिस्टर_chrdev_region(MKDEV(VME_MAJOR, 0), VME_DEVS);
पूर्ण

अटल काष्ठा vme_driver vme_user_driver = अणु
	.name = driver_name,
	.match = vme_user_match,
	.probe = vme_user_probe,
	.हटाओ = vme_user_हटाओ,
पूर्ण;

अटल पूर्णांक __init vme_user_init(व्योम)
अणु
	पूर्णांक retval = 0;

	pr_info("VME User Space Access Driver\n");

	अगर (bus_num == 0) अणु
		pr_err("No cards, skipping registration\n");
		retval = -ENODEV;
		जाओ err_nocard;
	पूर्ण

	/* Let's start by supporting one bus, we can support more than one
	 * in future revisions अगर that ever becomes necessary.
	 */
	अगर (bus_num > VME_USER_BUS_MAX) अणु
		pr_err("Driver only able to handle %d buses\n",
		       VME_USER_BUS_MAX);
		bus_num = VME_USER_BUS_MAX;
	पूर्ण

	/*
	 * Here we just रेजिस्टर the maximum number of devices we can and
	 * leave vme_user_match() to allow only 1 to go through to probe().
	 * This way, अगर we later want to allow multiple user access devices,
	 * we just change the code in vme_user_match().
	 */
	retval = vme_रेजिस्टर_driver(&vme_user_driver, VME_MAX_SLOTS);
	अगर (retval)
		जाओ err_reg;

	वापस retval;

err_reg:
err_nocard:
	वापस retval;
पूर्ण

अटल व्योम __निकास vme_user_निकास(व्योम)
अणु
	vme_unरेजिस्टर_driver(&vme_user_driver);
पूर्ण

MODULE_PARM_DESC(bus, "Enumeration of VMEbus to which the driver is connected");
module_param_array(bus, पूर्णांक, &bus_num, 0000);

MODULE_DESCRIPTION("VME User Space Access Driver");
MODULE_AUTHOR("Martyn Welch <martyn.welch@ge.com");
MODULE_LICENSE("GPL");

module_init(vme_user_init);
module_निकास(vme_user_निकास);
