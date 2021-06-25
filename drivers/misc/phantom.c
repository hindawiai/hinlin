<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (C) 2005-2007 Jiri Slaby <jirislaby@gmail.com>
 *
 *  You need a userspace library to cooperate with this driver. It (and other
 *  info) may be obtained here:
 *  http://www.fi.muni.cz/~xslaby/phantom.hपंचांगl
 *  or alternatively, you might use OpenHaptics provided by Sensable.
 */

#समावेश <linux/compat.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/pci.h>
#समावेश <linux/fs.h>
#समावेश <linux/poll.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/cdev.h>
#समावेश <linux/slab.h>
#समावेश <linux/phantom.h>
#समावेश <linux/sched.h>
#समावेश <linux/mutex.h>

#समावेश <linux/atomic.h>
#समावेश <यंत्र/पन.स>

#घोषणा PHANTOM_VERSION		"n0.9.8"

#घोषणा PHANTOM_MAX_MINORS	8

#घोषणा PHN_IRQCTL		0x4c    /* irq control in caddr space */

#घोषणा PHB_RUNNING		1
#घोषणा PHB_NOT_OH		2

अटल DEFINE_MUTEX(phantom_mutex);
अटल काष्ठा class *phantom_class;
अटल पूर्णांक phantom_major;

काष्ठा phantom_device अणु
	अचिन्हित पूर्णांक खोलोed;
	व्योम __iomem *caddr;
	u32 __iomem *iaddr;
	u32 __iomem *oaddr;
	अचिन्हित दीर्घ status;
	atomic_t counter;

	रुको_queue_head_t रुको;
	काष्ठा cdev cdev;

	काष्ठा mutex खोलो_lock;
	spinlock_t regs_lock;

	/* used in NOT_OH mode */
	काष्ठा phm_regs oregs;
	u32 ctl_reg;
पूर्ण;

अटल अचिन्हित अक्षर phantom_devices[PHANTOM_MAX_MINORS];

अटल पूर्णांक phantom_status(काष्ठा phantom_device *dev, अचिन्हित दीर्घ newstat)
अणु
	pr_debug("phantom_status %lx %lx\n", dev->status, newstat);

	अगर (!(dev->status & PHB_RUNNING) && (newstat & PHB_RUNNING)) अणु
		atomic_set(&dev->counter, 0);
		ioग_लिखो32(PHN_CTL_IRQ, dev->iaddr + PHN_CONTROL);
		ioग_लिखो32(0x43, dev->caddr + PHN_IRQCTL);
		ioपढ़ो32(dev->caddr + PHN_IRQCTL); /* PCI posting */
	पूर्ण अन्यथा अगर ((dev->status & PHB_RUNNING) && !(newstat & PHB_RUNNING)) अणु
		ioग_लिखो32(0, dev->caddr + PHN_IRQCTL);
		ioपढ़ो32(dev->caddr + PHN_IRQCTL); /* PCI posting */
	पूर्ण

	dev->status = newstat;

	वापस 0;
पूर्ण

/*
 * File ops
 */

अटल दीर्घ phantom_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
		अचिन्हित दीर्घ arg)
अणु
	काष्ठा phantom_device *dev = file->निजी_data;
	काष्ठा phm_regs rs;
	काष्ठा phm_reg r;
	व्योम __user *argp = (व्योम __user *)arg;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक i;

	चयन (cmd) अणु
	हाल PHN_SETREG:
	हाल PHN_SET_REG:
		अगर (copy_from_user(&r, argp, माप(r)))
			वापस -EFAULT;

		अगर (r.reg > 7)
			वापस -EINVAL;

		spin_lock_irqsave(&dev->regs_lock, flags);
		अगर (r.reg == PHN_CONTROL && (r.value & PHN_CTL_IRQ) &&
				phantom_status(dev, dev->status | PHB_RUNNING))अणु
			spin_unlock_irqrestore(&dev->regs_lock, flags);
			वापस -ENODEV;
		पूर्ण

		pr_debug("phantom: writing %x to %u\n", r.value, r.reg);

		/* preserve amp bit (करोn't allow to change it when in NOT_OH) */
		अगर (r.reg == PHN_CONTROL && (dev->status & PHB_NOT_OH)) अणु
			r.value &= ~PHN_CTL_AMP;
			r.value |= dev->ctl_reg & PHN_CTL_AMP;
			dev->ctl_reg = r.value;
		पूर्ण

		ioग_लिखो32(r.value, dev->iaddr + r.reg);
		ioपढ़ो32(dev->iaddr); /* PCI posting */

		अगर (r.reg == PHN_CONTROL && !(r.value & PHN_CTL_IRQ))
			phantom_status(dev, dev->status & ~PHB_RUNNING);
		spin_unlock_irqrestore(&dev->regs_lock, flags);
		अवरोध;
	हाल PHN_SETREGS:
	हाल PHN_SET_REGS:
		अगर (copy_from_user(&rs, argp, माप(rs)))
			वापस -EFAULT;

		pr_debug("phantom: SRS %u regs %x\n", rs.count, rs.mask);
		spin_lock_irqsave(&dev->regs_lock, flags);
		अगर (dev->status & PHB_NOT_OH)
			स_नकल(&dev->oregs, &rs, माप(rs));
		अन्यथा अणु
			u32 m = min(rs.count, 8U);
			क्रम (i = 0; i < m; i++)
				अगर (rs.mask & BIT(i))
					ioग_लिखो32(rs.values[i], dev->oaddr + i);
			ioपढ़ो32(dev->iaddr); /* PCI posting */
		पूर्ण
		spin_unlock_irqrestore(&dev->regs_lock, flags);
		अवरोध;
	हाल PHN_GETREG:
	हाल PHN_GET_REG:
		अगर (copy_from_user(&r, argp, माप(r)))
			वापस -EFAULT;

		अगर (r.reg > 7)
			वापस -EINVAL;

		r.value = ioपढ़ो32(dev->iaddr + r.reg);

		अगर (copy_to_user(argp, &r, माप(r)))
			वापस -EFAULT;
		अवरोध;
	हाल PHN_GETREGS:
	हाल PHN_GET_REGS: अणु
		u32 m;

		अगर (copy_from_user(&rs, argp, माप(rs)))
			वापस -EFAULT;

		m = min(rs.count, 8U);

		pr_debug("phantom: GRS %u regs %x\n", rs.count, rs.mask);
		spin_lock_irqsave(&dev->regs_lock, flags);
		क्रम (i = 0; i < m; i++)
			अगर (rs.mask & BIT(i))
				rs.values[i] = ioपढ़ो32(dev->iaddr + i);
		atomic_set(&dev->counter, 0);
		spin_unlock_irqrestore(&dev->regs_lock, flags);

		अगर (copy_to_user(argp, &rs, माप(rs)))
			वापस -EFAULT;
		अवरोध;
	पूर्ण हाल PHN_NOT_OH:
		spin_lock_irqsave(&dev->regs_lock, flags);
		अगर (dev->status & PHB_RUNNING) अणु
			prपूर्णांकk(KERN_ERR "phantom: you need to set NOT_OH "
					"before you start the device!\n");
			spin_unlock_irqrestore(&dev->regs_lock, flags);
			वापस -EINVAL;
		पूर्ण
		dev->status |= PHB_NOT_OH;
		spin_unlock_irqrestore(&dev->regs_lock, flags);
		अवरोध;
	शेष:
		वापस -ENOTTY;
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_COMPAT
अटल दीर्घ phantom_compat_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक cmd,
		अचिन्हित दीर्घ arg)
अणु
	अगर (_IOC_NR(cmd) <= 3 && _IOC_SIZE(cmd) == माप(compat_uptr_t)) अणु
		cmd &= ~(_IOC_SIZEMASK << _IOC_SIZESHIFT);
		cmd |= माप(व्योम *) << _IOC_SIZESHIFT;
	पूर्ण
	वापस phantom_ioctl(filp, cmd, (अचिन्हित दीर्घ)compat_ptr(arg));
पूर्ण
#अन्यथा
#घोषणा phantom_compat_ioctl शून्य
#पूर्ण_अगर

अटल पूर्णांक phantom_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा phantom_device *dev = container_of(inode->i_cdev,
			काष्ठा phantom_device, cdev);

	mutex_lock(&phantom_mutex);
	nonseekable_खोलो(inode, file);

	अगर (mutex_lock_पूर्णांकerruptible(&dev->खोलो_lock)) अणु
		mutex_unlock(&phantom_mutex);
		वापस -ERESTARTSYS;
	पूर्ण

	अगर (dev->खोलोed) अणु
		mutex_unlock(&dev->खोलो_lock);
		mutex_unlock(&phantom_mutex);
		वापस -EINVAL;
	पूर्ण

	WARN_ON(dev->status & PHB_NOT_OH);

	file->निजी_data = dev;

	atomic_set(&dev->counter, 0);
	dev->खोलोed++;
	mutex_unlock(&dev->खोलो_lock);
	mutex_unlock(&phantom_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक phantom_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा phantom_device *dev = file->निजी_data;

	mutex_lock(&dev->खोलो_lock);

	dev->खोलोed = 0;
	phantom_status(dev, dev->status & ~PHB_RUNNING);
	dev->status &= ~PHB_NOT_OH;

	mutex_unlock(&dev->खोलो_lock);

	वापस 0;
पूर्ण

अटल __poll_t phantom_poll(काष्ठा file *file, poll_table *रुको)
अणु
	काष्ठा phantom_device *dev = file->निजी_data;
	__poll_t mask = 0;

	pr_debug("phantom_poll: %d\n", atomic_पढ़ो(&dev->counter));
	poll_रुको(file, &dev->रुको, रुको);

	अगर (!(dev->status & PHB_RUNNING))
		mask = EPOLLERR;
	अन्यथा अगर (atomic_पढ़ो(&dev->counter))
		mask = EPOLLIN | EPOLLRDNORM;

	pr_debug("phantom_poll end: %x/%d\n", mask, atomic_पढ़ो(&dev->counter));

	वापस mask;
पूर्ण

अटल स्थिर काष्ठा file_operations phantom_file_ops = अणु
	.खोलो = phantom_खोलो,
	.release = phantom_release,
	.unlocked_ioctl = phantom_ioctl,
	.compat_ioctl = phantom_compat_ioctl,
	.poll = phantom_poll,
	.llseek = no_llseek,
पूर्ण;

अटल irqवापस_t phantom_isr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा phantom_device *dev = data;
	अचिन्हित पूर्णांक i;
	u32 ctl;

	spin_lock(&dev->regs_lock);
	ctl = ioपढ़ो32(dev->iaddr + PHN_CONTROL);
	अगर (!(ctl & PHN_CTL_IRQ)) अणु
		spin_unlock(&dev->regs_lock);
		वापस IRQ_NONE;
	पूर्ण

	ioग_लिखो32(0, dev->iaddr);
	ioग_लिखो32(0xc0, dev->iaddr);

	अगर (dev->status & PHB_NOT_OH) अणु
		काष्ठा phm_regs *r = &dev->oregs;
		u32 m = min(r->count, 8U);

		क्रम (i = 0; i < m; i++)
			अगर (r->mask & BIT(i))
				ioग_लिखो32(r->values[i], dev->oaddr + i);

		dev->ctl_reg ^= PHN_CTL_AMP;
		ioग_लिखो32(dev->ctl_reg, dev->iaddr + PHN_CONTROL);
	पूर्ण
	spin_unlock(&dev->regs_lock);

	ioपढ़ो32(dev->iaddr); /* PCI posting */

	atomic_inc(&dev->counter);
	wake_up_पूर्णांकerruptible(&dev->रुको);

	वापस IRQ_HANDLED;
पूर्ण

/*
 * Init and deinit driver
 */

अटल अचिन्हित पूर्णांक phantom_get_मुक्त(व्योम)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < PHANTOM_MAX_MINORS; i++)
		अगर (phantom_devices[i] == 0)
			अवरोध;

	वापस i;
पूर्ण

अटल पूर्णांक phantom_probe(काष्ठा pci_dev *pdev,
	स्थिर काष्ठा pci_device_id *pci_id)
अणु
	काष्ठा phantom_device *pht;
	अचिन्हित पूर्णांक minor;
	पूर्णांक retval;

	retval = pci_enable_device(pdev);
	अगर (retval) अणु
		dev_err(&pdev->dev, "pci_enable_device failed!\n");
		जाओ err;
	पूर्ण

	minor = phantom_get_मुक्त();
	अगर (minor == PHANTOM_MAX_MINORS) अणु
		dev_err(&pdev->dev, "too many devices found!\n");
		retval = -EIO;
		जाओ err_dis;
	पूर्ण

	phantom_devices[minor] = 1;

	retval = pci_request_regions(pdev, "phantom");
	अगर (retval) अणु
		dev_err(&pdev->dev, "pci_request_regions failed!\n");
		जाओ err_null;
	पूर्ण

	retval = -ENOMEM;
	pht = kzalloc(माप(*pht), GFP_KERNEL);
	अगर (pht == शून्य) अणु
		dev_err(&pdev->dev, "unable to allocate device\n");
		जाओ err_reg;
	पूर्ण

	pht->caddr = pci_iomap(pdev, 0, 0);
	अगर (pht->caddr == शून्य) अणु
		dev_err(&pdev->dev, "can't remap conf space\n");
		जाओ err_fr;
	पूर्ण
	pht->iaddr = pci_iomap(pdev, 2, 0);
	अगर (pht->iaddr == शून्य) अणु
		dev_err(&pdev->dev, "can't remap input space\n");
		जाओ err_unmc;
	पूर्ण
	pht->oaddr = pci_iomap(pdev, 3, 0);
	अगर (pht->oaddr == शून्य) अणु
		dev_err(&pdev->dev, "can't remap output space\n");
		जाओ err_unmi;
	पूर्ण

	mutex_init(&pht->खोलो_lock);
	spin_lock_init(&pht->regs_lock);
	init_रुकोqueue_head(&pht->रुको);
	cdev_init(&pht->cdev, &phantom_file_ops);
	pht->cdev.owner = THIS_MODULE;

	ioग_लिखो32(0, pht->caddr + PHN_IRQCTL);
	ioपढ़ो32(pht->caddr + PHN_IRQCTL); /* PCI posting */
	retval = request_irq(pdev->irq, phantom_isr,
			IRQF_SHARED, "phantom", pht);
	अगर (retval) अणु
		dev_err(&pdev->dev, "can't establish ISR\n");
		जाओ err_unmo;
	पूर्ण

	retval = cdev_add(&pht->cdev, MKDEV(phantom_major, minor), 1);
	अगर (retval) अणु
		dev_err(&pdev->dev, "chardev registration failed\n");
		जाओ err_irq;
	पूर्ण

	अगर (IS_ERR(device_create(phantom_class, &pdev->dev,
				 MKDEV(phantom_major, minor), शून्य,
				 "phantom%u", minor)))
		dev_err(&pdev->dev, "can't create device\n");

	pci_set_drvdata(pdev, pht);

	वापस 0;
err_irq:
	मुक्त_irq(pdev->irq, pht);
err_unmo:
	pci_iounmap(pdev, pht->oaddr);
err_unmi:
	pci_iounmap(pdev, pht->iaddr);
err_unmc:
	pci_iounmap(pdev, pht->caddr);
err_fr:
	kमुक्त(pht);
err_reg:
	pci_release_regions(pdev);
err_null:
	phantom_devices[minor] = 0;
err_dis:
	pci_disable_device(pdev);
err:
	वापस retval;
पूर्ण

अटल व्योम phantom_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा phantom_device *pht = pci_get_drvdata(pdev);
	अचिन्हित पूर्णांक minor = MINOR(pht->cdev.dev);

	device_destroy(phantom_class, MKDEV(phantom_major, minor));

	cdev_del(&pht->cdev);

	ioग_लिखो32(0, pht->caddr + PHN_IRQCTL);
	ioपढ़ो32(pht->caddr + PHN_IRQCTL); /* PCI posting */
	मुक्त_irq(pdev->irq, pht);

	pci_iounmap(pdev, pht->oaddr);
	pci_iounmap(pdev, pht->iaddr);
	pci_iounmap(pdev, pht->caddr);

	kमुक्त(pht);

	pci_release_regions(pdev);

	phantom_devices[minor] = 0;

	pci_disable_device(pdev);
पूर्ण

अटल पूर्णांक __maybe_unused phantom_suspend(काष्ठा device *dev_d)
अणु
	काष्ठा phantom_device *dev = dev_get_drvdata(dev_d);

	ioग_लिखो32(0, dev->caddr + PHN_IRQCTL);
	ioपढ़ो32(dev->caddr + PHN_IRQCTL); /* PCI posting */

	synchronize_irq(to_pci_dev(dev_d)->irq);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused phantom_resume(काष्ठा device *dev_d)
अणु
	काष्ठा phantom_device *dev = dev_get_drvdata(dev_d);

	ioग_लिखो32(0, dev->caddr + PHN_IRQCTL);

	वापस 0;
पूर्ण

अटल काष्ठा pci_device_id phantom_pci_tbl[] = अणु
	अणु .venकरोr = PCI_VENDOR_ID_PLX, .device = PCI_DEVICE_ID_PLX_9050,
	  .subvenकरोr = PCI_VENDOR_ID_PLX, .subdevice = PCI_DEVICE_ID_PLX_9050,
	  .class = PCI_CLASS_BRIDGE_OTHER << 8, .class_mask = 0xffff00 पूर्ण,
	अणु 0, पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, phantom_pci_tbl);

अटल SIMPLE_DEV_PM_OPS(phantom_pm_ops, phantom_suspend, phantom_resume);

अटल काष्ठा pci_driver phantom_pci_driver = अणु
	.name = "phantom",
	.id_table = phantom_pci_tbl,
	.probe = phantom_probe,
	.हटाओ = phantom_हटाओ,
	.driver.pm = &phantom_pm_ops,
पूर्ण;

अटल CLASS_ATTR_STRING(version, 0444, PHANTOM_VERSION);

अटल पूर्णांक __init phantom_init(व्योम)
अणु
	पूर्णांक retval;
	dev_t dev;

	phantom_class = class_create(THIS_MODULE, "phantom");
	अगर (IS_ERR(phantom_class)) अणु
		retval = PTR_ERR(phantom_class);
		prपूर्णांकk(KERN_ERR "phantom: can't register phantom class\n");
		जाओ err;
	पूर्ण
	retval = class_create_file(phantom_class, &class_attr_version.attr);
	अगर (retval) अणु
		prपूर्णांकk(KERN_ERR "phantom: can't create sysfs version file\n");
		जाओ err_class;
	पूर्ण

	retval = alloc_chrdev_region(&dev, 0, PHANTOM_MAX_MINORS, "phantom");
	अगर (retval) अणु
		prपूर्णांकk(KERN_ERR "phantom: can't register character device\n");
		जाओ err_attr;
	पूर्ण
	phantom_major = MAJOR(dev);

	retval = pci_रेजिस्टर_driver(&phantom_pci_driver);
	अगर (retval) अणु
		prपूर्णांकk(KERN_ERR "phantom: can't register pci driver\n");
		जाओ err_unchr;
	पूर्ण

	prपूर्णांकk(KERN_INFO "Phantom Linux Driver, version " PHANTOM_VERSION ", "
			"init OK\n");

	वापस 0;
err_unchr:
	unरेजिस्टर_chrdev_region(dev, PHANTOM_MAX_MINORS);
err_attr:
	class_हटाओ_file(phantom_class, &class_attr_version.attr);
err_class:
	class_destroy(phantom_class);
err:
	वापस retval;
पूर्ण

अटल व्योम __निकास phantom_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&phantom_pci_driver);

	unरेजिस्टर_chrdev_region(MKDEV(phantom_major, 0), PHANTOM_MAX_MINORS);

	class_हटाओ_file(phantom_class, &class_attr_version.attr);
	class_destroy(phantom_class);

	pr_debug("phantom: module successfully removed\n");
पूर्ण

module_init(phantom_init);
module_निकास(phantom_निकास);

MODULE_AUTHOR("Jiri Slaby <jirislaby@gmail.com>");
MODULE_DESCRIPTION("Sensable Phantom driver (PCI devices)");
MODULE_LICENSE("GPL");
MODULE_VERSION(PHANTOM_VERSION);
