<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2017 Linaro Ltd.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/cdev.h>
#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of.h>
#समावेश <linux/of_reserved_स्मृति.स>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/पन.स>
#समावेश <linux/qcom_scm.h>

#घोषणा QCOM_RMTFS_MEM_DEV_MAX	(MINORMASK + 1)

अटल dev_t qcom_rmtfs_mem_major;

काष्ठा qcom_rmtfs_mem अणु
	काष्ठा device dev;
	काष्ठा cdev cdev;

	व्योम *base;
	phys_addr_t addr;
	phys_addr_t size;

	अचिन्हित पूर्णांक client_id;

	अचिन्हित पूर्णांक perms;
पूर्ण;

अटल sमाप_प्रकार qcom_rmtfs_mem_show(काष्ठा device *dev,
			      काष्ठा device_attribute *attr,
			      अक्षर *buf);

अटल DEVICE_ATTR(phys_addr, 0444, qcom_rmtfs_mem_show, शून्य);
अटल DEVICE_ATTR(size, 0444, qcom_rmtfs_mem_show, शून्य);
अटल DEVICE_ATTR(client_id, 0444, qcom_rmtfs_mem_show, शून्य);

अटल sमाप_प्रकार qcom_rmtfs_mem_show(काष्ठा device *dev,
			      काष्ठा device_attribute *attr,
			      अक्षर *buf)
अणु
	काष्ठा qcom_rmtfs_mem *rmtfs_mem = container_of(dev,
							काष्ठा qcom_rmtfs_mem,
							dev);

	अगर (attr == &dev_attr_phys_addr)
		वापस प्र_लिखो(buf, "%pa\n", &rmtfs_mem->addr);
	अगर (attr == &dev_attr_size)
		वापस प्र_लिखो(buf, "%pa\n", &rmtfs_mem->size);
	अगर (attr == &dev_attr_client_id)
		वापस प्र_लिखो(buf, "%d\n", rmtfs_mem->client_id);

	वापस -EINVAL;
पूर्ण

अटल काष्ठा attribute *qcom_rmtfs_mem_attrs[] = अणु
	&dev_attr_phys_addr.attr,
	&dev_attr_size.attr,
	&dev_attr_client_id.attr,
	शून्य
पूर्ण;
ATTRIBUTE_GROUPS(qcom_rmtfs_mem);

अटल पूर्णांक qcom_rmtfs_mem_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा qcom_rmtfs_mem *rmtfs_mem = container_of(inode->i_cdev,
							काष्ठा qcom_rmtfs_mem,
							cdev);

	get_device(&rmtfs_mem->dev);
	filp->निजी_data = rmtfs_mem;

	वापस 0;
पूर्ण
अटल sमाप_प्रकार qcom_rmtfs_mem_पढ़ो(काष्ठा file *filp,
			      अक्षर __user *buf, माप_प्रकार count, loff_t *f_pos)
अणु
	काष्ठा qcom_rmtfs_mem *rmtfs_mem = filp->निजी_data;

	अगर (*f_pos >= rmtfs_mem->size)
		वापस 0;

	अगर (*f_pos + count >= rmtfs_mem->size)
		count = rmtfs_mem->size - *f_pos;

	अगर (copy_to_user(buf, rmtfs_mem->base + *f_pos, count))
		वापस -EFAULT;

	*f_pos += count;
	वापस count;
पूर्ण

अटल sमाप_प्रकार qcom_rmtfs_mem_ग_लिखो(काष्ठा file *filp,
			       स्थिर अक्षर __user *buf, माप_प्रकार count,
			       loff_t *f_pos)
अणु
	काष्ठा qcom_rmtfs_mem *rmtfs_mem = filp->निजी_data;

	अगर (*f_pos >= rmtfs_mem->size)
		वापस 0;

	अगर (*f_pos + count >= rmtfs_mem->size)
		count = rmtfs_mem->size - *f_pos;

	अगर (copy_from_user(rmtfs_mem->base + *f_pos, buf, count))
		वापस -EFAULT;

	*f_pos += count;
	वापस count;
पूर्ण

अटल पूर्णांक qcom_rmtfs_mem_release(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा qcom_rmtfs_mem *rmtfs_mem = filp->निजी_data;

	put_device(&rmtfs_mem->dev);

	वापस 0;
पूर्ण

अटल काष्ठा class rmtfs_class = अणु
	.owner          = THIS_MODULE,
	.name           = "rmtfs",
पूर्ण;

अटल पूर्णांक qcom_rmtfs_mem_mmap(काष्ठा file *filep, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा qcom_rmtfs_mem *rmtfs_mem = filep->निजी_data;

	अगर (vma->vm_end - vma->vm_start > rmtfs_mem->size) अणु
		dev_dbg(&rmtfs_mem->dev,
			"vm_end[%lu] - vm_start[%lu] [%lu] > mem->size[%pa]\n",
			vma->vm_end, vma->vm_start,
			(vma->vm_end - vma->vm_start), &rmtfs_mem->size);
		वापस -EINVAL;
	पूर्ण

	vma->vm_page_prot = pgprot_ग_लिखोcombine(vma->vm_page_prot);
	वापस remap_pfn_range(vma,
			       vma->vm_start,
			       rmtfs_mem->addr >> PAGE_SHIFT,
			       vma->vm_end - vma->vm_start,
			       vma->vm_page_prot);
पूर्ण

अटल स्थिर काष्ठा file_operations qcom_rmtfs_mem_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = qcom_rmtfs_mem_खोलो,
	.पढ़ो = qcom_rmtfs_mem_पढ़ो,
	.ग_लिखो = qcom_rmtfs_mem_ग_लिखो,
	.release = qcom_rmtfs_mem_release,
	.llseek = शेष_llseek,
	.mmap = qcom_rmtfs_mem_mmap,
पूर्ण;

अटल व्योम qcom_rmtfs_mem_release_device(काष्ठा device *dev)
अणु
	काष्ठा qcom_rmtfs_mem *rmtfs_mem = container_of(dev,
							काष्ठा qcom_rmtfs_mem,
							dev);

	kमुक्त(rmtfs_mem);
पूर्ण

अटल पूर्णांक qcom_rmtfs_mem_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *node = pdev->dev.of_node;
	काष्ठा qcom_scm_vmperm perms[2];
	काष्ठा reserved_mem *rmem;
	काष्ठा qcom_rmtfs_mem *rmtfs_mem;
	u32 client_id;
	u32 vmid;
	पूर्णांक ret;

	rmem = of_reserved_mem_lookup(node);
	अगर (!rmem) अणु
		dev_err(&pdev->dev, "failed to acquire memory region\n");
		वापस -EINVAL;
	पूर्ण

	ret = of_property_पढ़ो_u32(node, "qcom,client-id", &client_id);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to parse \"qcom,client-id\"\n");
		वापस ret;

	पूर्ण

	rmtfs_mem = kzalloc(माप(*rmtfs_mem), GFP_KERNEL);
	अगर (!rmtfs_mem)
		वापस -ENOMEM;

	rmtfs_mem->addr = rmem->base;
	rmtfs_mem->client_id = client_id;
	rmtfs_mem->size = rmem->size;

	device_initialize(&rmtfs_mem->dev);
	rmtfs_mem->dev.parent = &pdev->dev;
	rmtfs_mem->dev.groups = qcom_rmtfs_mem_groups;
	rmtfs_mem->dev.release = qcom_rmtfs_mem_release_device;

	rmtfs_mem->base = devm_memremap(&rmtfs_mem->dev, rmtfs_mem->addr,
					rmtfs_mem->size, MEMREMAP_WC);
	अगर (IS_ERR(rmtfs_mem->base)) अणु
		dev_err(&pdev->dev, "failed to remap rmtfs_mem region\n");
		ret = PTR_ERR(rmtfs_mem->base);
		जाओ put_device;
	पूर्ण

	cdev_init(&rmtfs_mem->cdev, &qcom_rmtfs_mem_fops);
	rmtfs_mem->cdev.owner = THIS_MODULE;

	dev_set_name(&rmtfs_mem->dev, "qcom_rmtfs_mem%d", client_id);
	rmtfs_mem->dev.id = client_id;
	rmtfs_mem->dev.class = &rmtfs_class;
	rmtfs_mem->dev.devt = MKDEV(MAJOR(qcom_rmtfs_mem_major), client_id);

	ret = cdev_device_add(&rmtfs_mem->cdev, &rmtfs_mem->dev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to add cdev: %d\n", ret);
		जाओ put_device;
	पूर्ण

	ret = of_property_पढ़ो_u32(node, "qcom,vmid", &vmid);
	अगर (ret < 0 && ret != -EINVAL) अणु
		dev_err(&pdev->dev, "failed to parse qcom,vmid\n");
		जाओ हटाओ_cdev;
	पूर्ण अन्यथा अगर (!ret) अणु
		अगर (!qcom_scm_is_available()) अणु
			ret = -EPROBE_DEFER;
			जाओ हटाओ_cdev;
		पूर्ण

		perms[0].vmid = QCOM_SCM_VMID_HLOS;
		perms[0].perm = QCOM_SCM_PERM_RW;
		perms[1].vmid = vmid;
		perms[1].perm = QCOM_SCM_PERM_RW;

		rmtfs_mem->perms = BIT(QCOM_SCM_VMID_HLOS);
		ret = qcom_scm_assign_mem(rmtfs_mem->addr, rmtfs_mem->size,
					  &rmtfs_mem->perms, perms, 2);
		अगर (ret < 0) अणु
			dev_err(&pdev->dev, "assign memory failed\n");
			जाओ हटाओ_cdev;
		पूर्ण
	पूर्ण

	dev_set_drvdata(&pdev->dev, rmtfs_mem);

	वापस 0;

हटाओ_cdev:
	cdev_device_del(&rmtfs_mem->cdev, &rmtfs_mem->dev);
put_device:
	put_device(&rmtfs_mem->dev);

	वापस ret;
पूर्ण

अटल पूर्णांक qcom_rmtfs_mem_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा qcom_rmtfs_mem *rmtfs_mem = dev_get_drvdata(&pdev->dev);
	काष्ठा qcom_scm_vmperm perm;

	अगर (rmtfs_mem->perms) अणु
		perm.vmid = QCOM_SCM_VMID_HLOS;
		perm.perm = QCOM_SCM_PERM_RW;

		qcom_scm_assign_mem(rmtfs_mem->addr, rmtfs_mem->size,
				    &rmtfs_mem->perms, &perm, 1);
	पूर्ण

	cdev_device_del(&rmtfs_mem->cdev, &rmtfs_mem->dev);
	put_device(&rmtfs_mem->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id qcom_rmtfs_mem_of_match[] = अणु
	अणु .compatible = "qcom,rmtfs-mem" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, qcom_rmtfs_mem_of_match);

अटल काष्ठा platक्रमm_driver qcom_rmtfs_mem_driver = अणु
	.probe = qcom_rmtfs_mem_probe,
	.हटाओ = qcom_rmtfs_mem_हटाओ,
	.driver  = अणु
		.name  = "qcom_rmtfs_mem",
		.of_match_table = qcom_rmtfs_mem_of_match,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init qcom_rmtfs_mem_init(व्योम)
अणु
	पूर्णांक ret;

	ret = class_रेजिस्टर(&rmtfs_class);
	अगर (ret)
		वापस ret;

	ret = alloc_chrdev_region(&qcom_rmtfs_mem_major, 0,
				  QCOM_RMTFS_MEM_DEV_MAX, "qcom_rmtfs_mem");
	अगर (ret < 0) अणु
		pr_err("qcom_rmtfs_mem: failed to allocate char dev region\n");
		जाओ unरेजिस्टर_class;
	पूर्ण

	ret = platक्रमm_driver_रेजिस्टर(&qcom_rmtfs_mem_driver);
	अगर (ret < 0) अणु
		pr_err("qcom_rmtfs_mem: failed to register rmtfs_mem driver\n");
		जाओ unरेजिस्टर_chrdev;
	पूर्ण

	वापस 0;

unरेजिस्टर_chrdev:
	unरेजिस्टर_chrdev_region(qcom_rmtfs_mem_major, QCOM_RMTFS_MEM_DEV_MAX);
unरेजिस्टर_class:
	class_unरेजिस्टर(&rmtfs_class);
	वापस ret;
पूर्ण
module_init(qcom_rmtfs_mem_init);

अटल व्योम __निकास qcom_rmtfs_mem_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&qcom_rmtfs_mem_driver);
	unरेजिस्टर_chrdev_region(qcom_rmtfs_mem_major, QCOM_RMTFS_MEM_DEV_MAX);
	class_unरेजिस्टर(&rmtfs_class);
पूर्ण
module_निकास(qcom_rmtfs_mem_निकास);

MODULE_AUTHOR("Linaro Ltd");
MODULE_DESCRIPTION("Qualcomm Remote Filesystem memory driver");
MODULE_LICENSE("GPL v2");
