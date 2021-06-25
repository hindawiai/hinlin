<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * OPAL Runसमय Diagnostics पूर्णांकerface driver
 * Supported on POWERNV platक्रमm
 *
 * Copyright IBM Corporation 2015
 */

#घोषणा pr_fmt(fmt) "opal-prd: " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/fs.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/poll.h>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/opal-prd.h>
#समावेश <यंत्र/opal.h>
#समावेश <यंत्र/पन.स>
#समावेश <linux/uaccess.h>


/*
 * The msg member must be at the end of the काष्ठा, as it's followed by the
 * message data.
 */
काष्ठा opal_prd_msg_queue_item अणु
	काष्ठा list_head		list;
	काष्ठा opal_prd_msg_header	msg;
पूर्ण;

अटल काष्ठा device_node *prd_node;
अटल LIST_HEAD(opal_prd_msg_queue);
अटल DEFINE_SPINLOCK(opal_prd_msg_queue_lock);
अटल DECLARE_WAIT_QUEUE_HEAD(opal_prd_msg_रुको);
अटल atomic_t prd_usage;

अटल bool opal_prd_range_is_valid(uपूर्णांक64_t addr, uपूर्णांक64_t size)
अणु
	काष्ठा device_node *parent, *node;
	bool found;

	अगर (addr + size < addr)
		वापस false;

	parent = of_find_node_by_path("/reserved-memory");
	अगर (!parent)
		वापस false;

	found = false;

	क्रम_each_child_of_node(parent, node) अणु
		uपूर्णांक64_t range_addr, range_size, range_end;
		स्थिर __be32 *addrp;
		स्थिर अक्षर *label;

		addrp = of_get_address(node, 0, &range_size, शून्य);

		range_addr = of_पढ़ो_number(addrp, 2);
		range_end = range_addr + range_size;

		label = of_get_property(node, "ibm,prd-label", शून्य);

		/* PRD ranges need a label */
		अगर (!label)
			जारी;

		अगर (range_end <= range_addr)
			जारी;

		अगर (addr >= range_addr && addr + size <= range_end) अणु
			found = true;
			of_node_put(node);
			अवरोध;
		पूर्ण
	पूर्ण

	of_node_put(parent);
	वापस found;
पूर्ण

अटल पूर्णांक opal_prd_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	/*
	 * Prevent multiple (separate) processes from concurrent पूर्णांकeractions
	 * with the FW PRD channel
	 */
	अगर (atomic_xchg(&prd_usage, 1) == 1)
		वापस -EBUSY;

	वापस 0;
पूर्ण

/*
 * opal_prd_mmap - maps firmware-provided ranges पूर्णांकo userspace
 * @file: file काष्ठाure क्रम the device
 * @vma: VMA to map the रेजिस्टरs पूर्णांकo
 */

अटल पूर्णांक opal_prd_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	माप_प्रकार addr, size;
	pgprot_t page_prot;

	pr_devel("opal_prd_mmap(0x%016lx, 0x%016lx, 0x%lx, 0x%lx)\n",
			vma->vm_start, vma->vm_end, vma->vm_pgoff,
			vma->vm_flags);

	addr = vma->vm_pgoff << PAGE_SHIFT;
	size = vma->vm_end - vma->vm_start;

	/* ensure we're mapping within one of the allowable ranges */
	अगर (!opal_prd_range_is_valid(addr, size))
		वापस -EINVAL;

	page_prot = phys_mem_access_prot(file, vma->vm_pgoff,
					 size, vma->vm_page_prot);

	वापस remap_pfn_range(vma, vma->vm_start, vma->vm_pgoff, size,
				page_prot);
पूर्ण

अटल bool opal_msg_queue_empty(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	bool ret;

	spin_lock_irqsave(&opal_prd_msg_queue_lock, flags);
	ret = list_empty(&opal_prd_msg_queue);
	spin_unlock_irqrestore(&opal_prd_msg_queue_lock, flags);

	वापस ret;
पूर्ण

अटल __poll_t opal_prd_poll(काष्ठा file *file,
		काष्ठा poll_table_काष्ठा *रुको)
अणु
	poll_रुको(file, &opal_prd_msg_रुको, रुको);

	अगर (!opal_msg_queue_empty())
		वापस EPOLLIN | EPOLLRDNORM;

	वापस 0;
पूर्ण

अटल sमाप_प्रकार opal_prd_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
		माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा opal_prd_msg_queue_item *item;
	अचिन्हित दीर्घ flags;
	sमाप_प्रकार size, err;
	पूर्णांक rc;

	/* we need at least a header's worth of data */
	अगर (count < माप(item->msg))
		वापस -EINVAL;

	अगर (*ppos)
		वापस -ESPIPE;

	item = शून्य;

	क्रम (;;) अणु

		spin_lock_irqsave(&opal_prd_msg_queue_lock, flags);
		अगर (!list_empty(&opal_prd_msg_queue)) अणु
			item = list_first_entry(&opal_prd_msg_queue,
					काष्ठा opal_prd_msg_queue_item, list);
			list_del(&item->list);
		पूर्ण
		spin_unlock_irqrestore(&opal_prd_msg_queue_lock, flags);

		अगर (item)
			अवरोध;

		अगर (file->f_flags & O_NONBLOCK)
			वापस -EAGAIN;

		rc = रुको_event_पूर्णांकerruptible(opal_prd_msg_रुको,
				!opal_msg_queue_empty());
		अगर (rc)
			वापस -EINTR;
	पूर्ण

	size = be16_to_cpu(item->msg.size);
	अगर (size > count) अणु
		err = -EINVAL;
		जाओ err_requeue;
	पूर्ण

	rc = copy_to_user(buf, &item->msg, size);
	अगर (rc) अणु
		err = -EFAULT;
		जाओ err_requeue;
	पूर्ण

	kमुक्त(item);

	वापस size;

err_requeue:
	/* eep! re-queue at the head of the list */
	spin_lock_irqsave(&opal_prd_msg_queue_lock, flags);
	list_add(&item->list, &opal_prd_msg_queue);
	spin_unlock_irqrestore(&opal_prd_msg_queue_lock, flags);
	वापस err;
पूर्ण

अटल sमाप_प्रकार opal_prd_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
		माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा opal_prd_msg_header hdr;
	sमाप_प्रकार size;
	व्योम *msg;
	पूर्णांक rc;

	size = माप(hdr);

	अगर (count < size)
		वापस -EINVAL;

	/* grab the header */
	rc = copy_from_user(&hdr, buf, माप(hdr));
	अगर (rc)
		वापस -EFAULT;

	size = be16_to_cpu(hdr.size);

	msg = memdup_user(buf, size);
	अगर (IS_ERR(msg))
		वापस PTR_ERR(msg);

	rc = opal_prd_msg(msg);
	अगर (rc) अणु
		pr_warn("write: opal_prd_msg returned %d\n", rc);
		size = -EIO;
	पूर्ण

	kमुक्त(msg);

	वापस size;
पूर्ण

अटल पूर्णांक opal_prd_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा opal_prd_msg_header msg;

	msg.size = cpu_to_be16(माप(msg));
	msg.type = OPAL_PRD_MSG_TYPE_FINI;

	opal_prd_msg((काष्ठा opal_prd_msg *)&msg);

	atomic_xchg(&prd_usage, 0);

	वापस 0;
पूर्ण

अटल दीर्घ opal_prd_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
		अचिन्हित दीर्घ param)
अणु
	काष्ठा opal_prd_info info;
	काष्ठा opal_prd_scom scom;
	पूर्णांक rc = 0;

	चयन (cmd) अणु
	हाल OPAL_PRD_GET_INFO:
		स_रखो(&info, 0, माप(info));
		info.version = OPAL_PRD_KERNEL_VERSION;
		rc = copy_to_user((व्योम __user *)param, &info, माप(info));
		अगर (rc)
			वापस -EFAULT;
		अवरोध;

	हाल OPAL_PRD_SCOM_READ:
		rc = copy_from_user(&scom, (व्योम __user *)param, माप(scom));
		अगर (rc)
			वापस -EFAULT;

		scom.rc = opal_xscom_पढ़ो(scom.chip, scom.addr,
				(__be64 *)&scom.data);
		scom.data = be64_to_cpu(scom.data);
		pr_devel("ioctl SCOM_READ: chip %llx addr %016llx data %016llx rc %lld\n",
				scom.chip, scom.addr, scom.data, scom.rc);

		rc = copy_to_user((व्योम __user *)param, &scom, माप(scom));
		अगर (rc)
			वापस -EFAULT;
		अवरोध;

	हाल OPAL_PRD_SCOM_WRITE:
		rc = copy_from_user(&scom, (व्योम __user *)param, माप(scom));
		अगर (rc)
			वापस -EFAULT;

		scom.rc = opal_xscom_ग_लिखो(scom.chip, scom.addr, scom.data);
		pr_devel("ioctl SCOM_WRITE: chip %llx addr %016llx data %016llx rc %lld\n",
				scom.chip, scom.addr, scom.data, scom.rc);

		rc = copy_to_user((व्योम __user *)param, &scom, माप(scom));
		अगर (rc)
			वापस -EFAULT;
		अवरोध;

	शेष:
		rc = -EINVAL;
	पूर्ण

	वापस rc;
पूर्ण

अटल स्थिर काष्ठा file_operations opal_prd_fops = अणु
	.खोलो		= opal_prd_खोलो,
	.mmap		= opal_prd_mmap,
	.poll		= opal_prd_poll,
	.पढ़ो		= opal_prd_पढ़ो,
	.ग_लिखो		= opal_prd_ग_लिखो,
	.unlocked_ioctl	= opal_prd_ioctl,
	.release	= opal_prd_release,
	.owner		= THIS_MODULE,
पूर्ण;

अटल काष्ठा miscdevice opal_prd_dev = अणु
	.minor		= MISC_DYNAMIC_MINOR,
	.name		= "opal-prd",
	.fops		= &opal_prd_fops,
पूर्ण;

/* opal पूर्णांकerface */
अटल पूर्णांक opal_prd_msg_notअगरier(काष्ठा notअगरier_block *nb,
		अचिन्हित दीर्घ msg_type, व्योम *_msg)
अणु
	काष्ठा opal_prd_msg_queue_item *item;
	काष्ठा opal_prd_msg_header *hdr;
	काष्ठा opal_msg *msg = _msg;
	पूर्णांक msg_size, item_size;
	अचिन्हित दीर्घ flags;

	अगर (msg_type != OPAL_MSG_PRD && msg_type != OPAL_MSG_PRD2)
		वापस 0;

	/* Calculate total size of the message and item we need to store. The
	 * 'size' field in the header includes the header itself. */
	hdr = (व्योम *)msg->params;
	msg_size = be16_to_cpu(hdr->size);
	item_size = msg_size + माप(*item) - माप(item->msg);

	item = kzalloc(item_size, GFP_ATOMIC);
	अगर (!item)
		वापस -ENOMEM;

	स_नकल(&item->msg, msg->params, msg_size);

	spin_lock_irqsave(&opal_prd_msg_queue_lock, flags);
	list_add_tail(&item->list, &opal_prd_msg_queue);
	spin_unlock_irqrestore(&opal_prd_msg_queue_lock, flags);

	wake_up_पूर्णांकerruptible(&opal_prd_msg_रुको);

	वापस 0;
पूर्ण

अटल काष्ठा notअगरier_block opal_prd_event_nb = अणु
	.notअगरier_call	= opal_prd_msg_notअगरier,
	.next		= शून्य,
	.priority	= 0,
पूर्ण;

अटल पूर्णांक opal_prd_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक rc;

	अगर (!pdev || !pdev->dev.of_node)
		वापस -ENODEV;

	/* We should only have one prd driver instance per machine; ensure
	 * that we only get a valid probe on a single OF node.
	 */
	अगर (prd_node)
		वापस -EBUSY;

	prd_node = pdev->dev.of_node;

	rc = opal_message_notअगरier_रेजिस्टर(OPAL_MSG_PRD, &opal_prd_event_nb);
	अगर (rc) अणु
		pr_err("Couldn't register event notifier\n");
		वापस rc;
	पूर्ण

	rc = opal_message_notअगरier_रेजिस्टर(OPAL_MSG_PRD2, &opal_prd_event_nb);
	अगर (rc) अणु
		pr_err("Couldn't register PRD2 event notifier\n");
		वापस rc;
	पूर्ण

	rc = misc_रेजिस्टर(&opal_prd_dev);
	अगर (rc) अणु
		pr_err("failed to register miscdev\n");
		opal_message_notअगरier_unरेजिस्टर(OPAL_MSG_PRD,
				&opal_prd_event_nb);
		वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक opal_prd_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	misc_deरेजिस्टर(&opal_prd_dev);
	opal_message_notअगरier_unरेजिस्टर(OPAL_MSG_PRD, &opal_prd_event_nb);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id opal_prd_match[] = अणु
	अणु .compatible = "ibm,opal-prd" पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver opal_prd_driver = अणु
	.driver = अणु
		.name		= "opal-prd",
		.of_match_table	= opal_prd_match,
	पूर्ण,
	.probe	= opal_prd_probe,
	.हटाओ	= opal_prd_हटाओ,
पूर्ण;

module_platक्रमm_driver(opal_prd_driver);

MODULE_DEVICE_TABLE(of, opal_prd_match);
MODULE_DESCRIPTION("PowerNV OPAL runtime diagnostic driver");
MODULE_LICENSE("GPL");
