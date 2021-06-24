<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * RDC321x watchकरोg driver
 *
 * Copyright (C) 2007-2010 Florian Fainelli <florian@खोलोwrt.org>
 *
 * This driver is highly inspired from the cpu5_wdt driver
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/miscdevice.h>
#समावेश <linux/fs.h>
#समावेश <linux/ioport.h>
#समावेश <linux/समयr.h>
#समावेश <linux/completion.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/watchकरोg.h>
#समावेश <linux/पन.स>
#समावेश <linux/uaccess.h>
#समावेश <linux/mfd/rdc321x.h>

#घोषणा RDC_WDT_MASK	0x80000000 /* Mask */
#घोषणा RDC_WDT_EN	0x00800000 /* Enable bit */
#घोषणा RDC_WDT_WTI	0x00200000 /* Generate CPU reset/NMI/WDT on समयout */
#घोषणा RDC_WDT_RST	0x00100000 /* Reset bit */
#घोषणा RDC_WDT_WIF	0x00040000 /* WDT IRQ Flag */
#घोषणा RDC_WDT_IRT	0x00000100 /* IRQ Routing table */
#घोषणा RDC_WDT_CNT	0x00000001 /* WDT count */

#घोषणा RDC_CLS_TMR	0x80003844 /* Clear समयr */

#घोषणा RDC_WDT_INTERVAL	(HZ/10+1)

अटल पूर्णांक ticks = 1000;

/* some device data */

अटल काष्ठा अणु
	काष्ठा completion stop;
	पूर्णांक running;
	काष्ठा समयr_list समयr;
	पूर्णांक queue;
	पूर्णांक शेष_ticks;
	अचिन्हित दीर्घ inuse;
	spinlock_t lock;
	काष्ठा pci_dev *sb_pdev;
	पूर्णांक base_reg;
पूर्ण rdc321x_wdt_device;

/* generic helper functions */

अटल व्योम rdc321x_wdt_trigger(काष्ठा समयr_list *unused)
अणु
	अचिन्हित दीर्घ flags;
	u32 val;

	अगर (rdc321x_wdt_device.running)
		ticks--;

	/* keep watchकरोg alive */
	spin_lock_irqsave(&rdc321x_wdt_device.lock, flags);
	pci_पढ़ो_config_dword(rdc321x_wdt_device.sb_pdev,
					rdc321x_wdt_device.base_reg, &val);
	val |= RDC_WDT_EN;
	pci_ग_लिखो_config_dword(rdc321x_wdt_device.sb_pdev,
					rdc321x_wdt_device.base_reg, val);
	spin_unlock_irqrestore(&rdc321x_wdt_device.lock, flags);

	/* requeue?? */
	अगर (rdc321x_wdt_device.queue && ticks)
		mod_समयr(&rdc321x_wdt_device.समयr,
				jअगरfies + RDC_WDT_INTERVAL);
	अन्यथा अणु
		/* ticks करोesn't matter anyway */
		complete(&rdc321x_wdt_device.stop);
	पूर्ण

पूर्ण

अटल व्योम rdc321x_wdt_reset(व्योम)
अणु
	ticks = rdc321x_wdt_device.शेष_ticks;
पूर्ण

अटल व्योम rdc321x_wdt_start(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	अगर (!rdc321x_wdt_device.queue) अणु
		rdc321x_wdt_device.queue = 1;

		/* Clear the समयr */
		spin_lock_irqsave(&rdc321x_wdt_device.lock, flags);
		pci_ग_लिखो_config_dword(rdc321x_wdt_device.sb_pdev,
				rdc321x_wdt_device.base_reg, RDC_CLS_TMR);

		/* Enable watchकरोg and set the समयout to 81.92 us */
		pci_ग_लिखो_config_dword(rdc321x_wdt_device.sb_pdev,
					rdc321x_wdt_device.base_reg,
					RDC_WDT_EN | RDC_WDT_CNT);
		spin_unlock_irqrestore(&rdc321x_wdt_device.lock, flags);

		mod_समयr(&rdc321x_wdt_device.समयr,
				jअगरfies + RDC_WDT_INTERVAL);
	पूर्ण

	/* अगर process dies, counter is not decremented */
	rdc321x_wdt_device.running++;
पूर्ण

अटल पूर्णांक rdc321x_wdt_stop(व्योम)
अणु
	अगर (rdc321x_wdt_device.running)
		rdc321x_wdt_device.running = 0;

	ticks = rdc321x_wdt_device.शेष_ticks;

	वापस -EIO;
पूर्ण

/* fileप्रणाली operations */
अटल पूर्णांक rdc321x_wdt_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अगर (test_and_set_bit(0, &rdc321x_wdt_device.inuse))
		वापस -EBUSY;

	वापस stream_खोलो(inode, file);
पूर्ण

अटल पूर्णांक rdc321x_wdt_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	clear_bit(0, &rdc321x_wdt_device.inuse);
	वापस 0;
पूर्ण

अटल दीर्घ rdc321x_wdt_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
				अचिन्हित दीर्घ arg)
अणु
	व्योम __user *argp = (व्योम __user *)arg;
	u32 value;
	अटल स्थिर काष्ठा watchकरोg_info ident = अणु
		.options = WDIOF_CARDRESET,
		.identity = "RDC321x WDT",
	पूर्ण;
	अचिन्हित दीर्घ flags;

	चयन (cmd) अणु
	हाल WDIOC_KEEPALIVE:
		rdc321x_wdt_reset();
		अवरोध;
	हाल WDIOC_GETSTATUS:
		/* Read the value from the DATA रेजिस्टर */
		spin_lock_irqsave(&rdc321x_wdt_device.lock, flags);
		pci_पढ़ो_config_dword(rdc321x_wdt_device.sb_pdev,
					rdc321x_wdt_device.base_reg, &value);
		spin_unlock_irqrestore(&rdc321x_wdt_device.lock, flags);
		अगर (copy_to_user(argp, &value, माप(u32)))
			वापस -EFAULT;
		अवरोध;
	हाल WDIOC_GETSUPPORT:
		अगर (copy_to_user(argp, &ident, माप(ident)))
			वापस -EFAULT;
		अवरोध;
	हाल WDIOC_SETOPTIONS:
		अगर (copy_from_user(&value, argp, माप(पूर्णांक)))
			वापस -EFAULT;
		चयन (value) अणु
		हाल WDIOS_ENABLECARD:
			rdc321x_wdt_start();
			अवरोध;
		हाल WDIOS_DISABLECARD:
			वापस rdc321x_wdt_stop();
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		वापस -ENOTTY;
	पूर्ण
	वापस 0;
पूर्ण

अटल sमाप_प्रकार rdc321x_wdt_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
				माप_प्रकार count, loff_t *ppos)
अणु
	अगर (!count)
		वापस -EIO;

	rdc321x_wdt_reset();

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations rdc321x_wdt_fops = अणु
	.owner		= THIS_MODULE,
	.llseek		= no_llseek,
	.unlocked_ioctl	= rdc321x_wdt_ioctl,
	.compat_ioctl	= compat_ptr_ioctl,
	.खोलो		= rdc321x_wdt_खोलो,
	.ग_लिखो		= rdc321x_wdt_ग_लिखो,
	.release	= rdc321x_wdt_release,
पूर्ण;

अटल काष्ठा miscdevice rdc321x_wdt_misc = अणु
	.minor	= WATCHDOG_MINOR,
	.name	= "watchdog",
	.fops	= &rdc321x_wdt_fops,
पूर्ण;

अटल पूर्णांक rdc321x_wdt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक err;
	काष्ठा resource *r;
	काष्ठा rdc321x_wdt_pdata *pdata;

	pdata = dev_get_platdata(&pdev->dev);
	अगर (!pdata) अणु
		dev_err(&pdev->dev, "no platform data supplied\n");
		वापस -ENODEV;
	पूर्ण

	r = platक्रमm_get_resource_byname(pdev, IORESOURCE_IO, "wdt-reg");
	अगर (!r) अणु
		dev_err(&pdev->dev, "failed to get wdt-reg resource\n");
		वापस -ENODEV;
	पूर्ण

	rdc321x_wdt_device.sb_pdev = pdata->sb_pdev;
	rdc321x_wdt_device.base_reg = r->start;
	rdc321x_wdt_device.queue = 0;
	rdc321x_wdt_device.शेष_ticks = ticks;

	err = misc_रेजिस्टर(&rdc321x_wdt_misc);
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "misc_register failed\n");
		वापस err;
	पूर्ण

	spin_lock_init(&rdc321x_wdt_device.lock);

	/* Reset the watchकरोg */
	pci_ग_लिखो_config_dword(rdc321x_wdt_device.sb_pdev,
				rdc321x_wdt_device.base_reg, RDC_WDT_RST);

	init_completion(&rdc321x_wdt_device.stop);

	clear_bit(0, &rdc321x_wdt_device.inuse);

	समयr_setup(&rdc321x_wdt_device.समयr, rdc321x_wdt_trigger, 0);

	dev_info(&pdev->dev, "watchdog init success\n");

	वापस 0;
पूर्ण

अटल पूर्णांक rdc321x_wdt_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	अगर (rdc321x_wdt_device.queue) अणु
		rdc321x_wdt_device.queue = 0;
		रुको_क्रम_completion(&rdc321x_wdt_device.stop);
	पूर्ण

	misc_deरेजिस्टर(&rdc321x_wdt_misc);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver rdc321x_wdt_driver = अणु
	.probe = rdc321x_wdt_probe,
	.हटाओ = rdc321x_wdt_हटाओ,
	.driver = अणु
		.name = "rdc321x-wdt",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(rdc321x_wdt_driver);

MODULE_AUTHOR("Florian Fainelli <florian@openwrt.org>");
MODULE_DESCRIPTION("RDC321x watchdog driver");
MODULE_LICENSE("GPL");
