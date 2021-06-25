<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* IBM POWER Barrier Synchronization Register Driver
 *
 * Copyright IBM Corporation 2008
 *
 * Author: Sonny Rao <sonnyrao@us.ibm.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/fs.h>
#समावेश <linux/module.h>
#समावेश <linux/cdev.h>
#समावेश <linux/list.h>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/पन.स>

/*
 This driver exposes a special रेजिस्टर which can be used क्रम fast
 synchronization across a large SMP machine.  The hardware is exposed
 as an array of bytes where each process will ग_लिखो to one of the bytes to
 indicate it has finished the current stage and this update is broadcast to
 all processors without having to bounce a cacheline between them. In
 POWER5 and POWER6 there is one of these रेजिस्टरs per SMP,  but it is
 presented in two क्रमms; first, it is given as a whole and then as a number
 of smaller रेजिस्टरs which alias to parts of the single whole रेजिस्टर.
 This can potentially allow multiple groups of processes to each have their
 own निजी synchronization device.

 Note that this hardware *must* be written to using *only* single byte ग_लिखोs.
 It may be पढ़ो using 1, 2, 4, or 8 byte loads which must be aligned since
 this region is treated as cache-inhibited  processes should also use a
 full sync beक्रमe and after writing to the BSR to ensure all stores and
 the BSR update have made it to all chips in the प्रणाली
*/

/* This is arbitrary number, up to Power6 it's been 17 or fewer  */
#घोषणा BSR_MAX_DEVS (32)

काष्ठा bsr_dev अणु
	u64      bsr_addr;     /* Real address */
	u64      bsr_len;      /* length of mem region we can map */
	अचिन्हित bsr_bytes;    /* size of the BSR reg itself */
	अचिन्हित bsr_stride;   /* पूर्णांकerval at which BSR repeats in the page */
	अचिन्हित bsr_type;     /* maps to क्रमागत below */
	अचिन्हित bsr_num;      /* bsr id number क्रम its type */
	पूर्णांक      bsr_minor;

	काष्ठा list_head bsr_list;

	dev_t    bsr_dev;
	काष्ठा cdev bsr_cdev;
	काष्ठा device *bsr_device;
	अक्षर     bsr_name[32];

पूर्ण;

अटल अचिन्हित total_bsr_devs;
अटल काष्ठा list_head bsr_devs = LIST_HEAD_INIT(bsr_devs);
अटल काष्ठा class *bsr_class;
अटल पूर्णांक bsr_major;

क्रमागत अणु
	BSR_8    = 0,
	BSR_16   = 1,
	BSR_64   = 2,
	BSR_128  = 3,
	BSR_4096 = 4,
	BSR_UNKNOWN = 5,
	BSR_MAX  = 6,
पूर्ण;

अटल अचिन्हित bsr_types[BSR_MAX];

अटल sमाप_प्रकार
bsr_size_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा bsr_dev *bsr_dev = dev_get_drvdata(dev);
	वापस प्र_लिखो(buf, "%u\n", bsr_dev->bsr_bytes);
पूर्ण
अटल DEVICE_ATTR_RO(bsr_size);

अटल sमाप_प्रकार
bsr_stride_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा bsr_dev *bsr_dev = dev_get_drvdata(dev);
	वापस प्र_लिखो(buf, "%u\n", bsr_dev->bsr_stride);
पूर्ण
अटल DEVICE_ATTR_RO(bsr_stride);

अटल sमाप_प्रकार
bsr_length_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा bsr_dev *bsr_dev = dev_get_drvdata(dev);
	वापस प्र_लिखो(buf, "%llu\n", bsr_dev->bsr_len);
पूर्ण
अटल DEVICE_ATTR_RO(bsr_length);

अटल काष्ठा attribute *bsr_dev_attrs[] = अणु
	&dev_attr_bsr_size.attr,
	&dev_attr_bsr_stride.attr,
	&dev_attr_bsr_length.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(bsr_dev);

अटल पूर्णांक bsr_mmap(काष्ठा file *filp, काष्ठा vm_area_काष्ठा *vma)
अणु
	अचिन्हित दीर्घ size   = vma->vm_end - vma->vm_start;
	काष्ठा bsr_dev *dev = filp->निजी_data;
	पूर्णांक ret;

	vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);

	/* check क्रम the हाल of a small BSR device and map one 4k page क्रम it*/
	अगर (dev->bsr_len < PAGE_SIZE && size == PAGE_SIZE)
		ret = remap_4k_pfn(vma, vma->vm_start, dev->bsr_addr >> 12,
				   vma->vm_page_prot);
	अन्यथा अगर (size <= dev->bsr_len)
		ret = io_remap_pfn_range(vma, vma->vm_start,
					 dev->bsr_addr >> PAGE_SHIFT,
					 size, vma->vm_page_prot);
	अन्यथा
		वापस -EINVAL;

	अगर (ret)
		वापस -EAGAIN;

	वापस 0;
पूर्ण

अटल पूर्णांक bsr_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा cdev *cdev = inode->i_cdev;
	काष्ठा bsr_dev *dev = container_of(cdev, काष्ठा bsr_dev, bsr_cdev);

	filp->निजी_data = dev;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations bsr_fops = अणु
	.owner = THIS_MODULE,
	.mmap  = bsr_mmap,
	.खोलो  = bsr_खोलो,
	.llseek = noop_llseek,
पूर्ण;

अटल व्योम bsr_cleanup_devs(व्योम)
अणु
	काष्ठा bsr_dev *cur, *n;

	list_क्रम_each_entry_safe(cur, n, &bsr_devs, bsr_list) अणु
		अगर (cur->bsr_device) अणु
			cdev_del(&cur->bsr_cdev);
			device_del(cur->bsr_device);
		पूर्ण
		list_del(&cur->bsr_list);
		kमुक्त(cur);
	पूर्ण
पूर्ण

अटल पूर्णांक bsr_add_node(काष्ठा device_node *bn)
अणु
	पूर्णांक bsr_stride_len, bsr_bytes_len, num_bsr_devs;
	स्थिर u32 *bsr_stride;
	स्थिर u32 *bsr_bytes;
	अचिन्हित i;
	पूर्णांक ret = -ENODEV;

	bsr_stride = of_get_property(bn, "ibm,lock-stride", &bsr_stride_len);
	bsr_bytes  = of_get_property(bn, "ibm,#lock-bytes", &bsr_bytes_len);

	अगर (!bsr_stride || !bsr_bytes ||
	    (bsr_stride_len != bsr_bytes_len)) अणु
		prपूर्णांकk(KERN_ERR "bsr of-node has missing/incorrect property\n");
		वापस ret;
	पूर्ण

	num_bsr_devs = bsr_bytes_len / माप(u32);

	क्रम (i = 0 ; i < num_bsr_devs; i++) अणु
		काष्ठा bsr_dev *cur = kzalloc(माप(काष्ठा bsr_dev),
					      GFP_KERNEL);
		काष्ठा resource res;
		पूर्णांक result;

		अगर (!cur) अणु
			prपूर्णांकk(KERN_ERR "Unable to alloc bsr dev\n");
			ret = -ENOMEM;
			जाओ out_err;
		पूर्ण

		result = of_address_to_resource(bn, i, &res);
		अगर (result < 0) अणु
			prपूर्णांकk(KERN_ERR "bsr of-node has invalid reg property, skipping\n");
			kमुक्त(cur);
			जारी;
		पूर्ण

		cur->bsr_minor  = i + total_bsr_devs;
		cur->bsr_addr   = res.start;
		cur->bsr_len    = resource_size(&res);
		cur->bsr_bytes  = bsr_bytes[i];
		cur->bsr_stride = bsr_stride[i];
		cur->bsr_dev    = MKDEV(bsr_major, i + total_bsr_devs);

		/* अगर we have a bsr_len of > 4k and less then PAGE_SIZE (64k pages) */
		/* we can only map 4k of it, so only advertise the 4k in sysfs */
		अगर (cur->bsr_len > 4096 && cur->bsr_len < PAGE_SIZE)
			cur->bsr_len = 4096;

		चयन(cur->bsr_bytes) अणु
		हाल 8:
			cur->bsr_type = BSR_8;
			अवरोध;
		हाल 16:
			cur->bsr_type = BSR_16;
			अवरोध;
		हाल 64:
			cur->bsr_type = BSR_64;
			अवरोध;
		हाल 128:
			cur->bsr_type = BSR_128;
			अवरोध;
		हाल 4096:
			cur->bsr_type = BSR_4096;
			अवरोध;
		शेष:
			cur->bsr_type = BSR_UNKNOWN;
		पूर्ण

		cur->bsr_num = bsr_types[cur->bsr_type];
		snम_लिखो(cur->bsr_name, 32, "bsr%d_%d",
			 cur->bsr_bytes, cur->bsr_num);

		cdev_init(&cur->bsr_cdev, &bsr_fops);
		result = cdev_add(&cur->bsr_cdev, cur->bsr_dev, 1);
		अगर (result) अणु
			kमुक्त(cur);
			जाओ out_err;
		पूर्ण

		cur->bsr_device = device_create(bsr_class, शून्य, cur->bsr_dev,
						cur, "%s", cur->bsr_name);
		अगर (IS_ERR(cur->bsr_device)) अणु
			prपूर्णांकk(KERN_ERR "device_create failed for %s\n",
			       cur->bsr_name);
			cdev_del(&cur->bsr_cdev);
			kमुक्त(cur);
			जाओ out_err;
		पूर्ण

		bsr_types[cur->bsr_type] = cur->bsr_num + 1;
		list_add_tail(&cur->bsr_list, &bsr_devs);
	पूर्ण

	total_bsr_devs += num_bsr_devs;

	वापस 0;

 out_err:

	bsr_cleanup_devs();
	वापस ret;
पूर्ण

अटल पूर्णांक bsr_create_devs(काष्ठा device_node *bn)
अणु
	पूर्णांक ret;

	जबतक (bn) अणु
		ret = bsr_add_node(bn);
		अगर (ret) अणु
			of_node_put(bn);
			वापस ret;
		पूर्ण
		bn = of_find_compatible_node(bn, शून्य, "ibm,bsr");
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक __init bsr_init(व्योम)
अणु
	काष्ठा device_node *np;
	dev_t bsr_dev;
	पूर्णांक ret = -ENODEV;

	np = of_find_compatible_node(शून्य, शून्य, "ibm,bsr");
	अगर (!np)
		जाओ out_err;

	bsr_class = class_create(THIS_MODULE, "bsr");
	अगर (IS_ERR(bsr_class)) अणु
		prपूर्णांकk(KERN_ERR "class_create() failed for bsr_class\n");
		ret = PTR_ERR(bsr_class);
		जाओ out_err_1;
	पूर्ण
	bsr_class->dev_groups = bsr_dev_groups;

	ret = alloc_chrdev_region(&bsr_dev, 0, BSR_MAX_DEVS, "bsr");
	bsr_major = MAJOR(bsr_dev);
	अगर (ret < 0) अणु
		prपूर्णांकk(KERN_ERR "alloc_chrdev_region() failed for bsr\n");
		जाओ out_err_2;
	पूर्ण

	ret = bsr_create_devs(np);
	अगर (ret < 0) अणु
		np = शून्य;
		जाओ out_err_3;
	पूर्ण

	वापस 0;

 out_err_3:
	unरेजिस्टर_chrdev_region(bsr_dev, BSR_MAX_DEVS);

 out_err_2:
	class_destroy(bsr_class);

 out_err_1:
	of_node_put(np);

 out_err:

	वापस ret;
पूर्ण

अटल व्योम __निकास  bsr_निकास(व्योम)
अणु

	bsr_cleanup_devs();

	अगर (bsr_class)
		class_destroy(bsr_class);

	अगर (bsr_major)
		unरेजिस्टर_chrdev_region(MKDEV(bsr_major, 0), BSR_MAX_DEVS);
पूर्ण

module_init(bsr_init);
module_निकास(bsr_निकास);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sonny Rao <sonnyrao@us.ibm.com>");
