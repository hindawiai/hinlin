<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  IDT Interprise 79RC32434 watchकरोg driver
 *
 *  Copyright (C) 2006, Ondrej Zajicek <santiago@crमुक्तnet.org>
 *  Copyright (C) 2008, Florian Fainelli <florian@खोलोwrt.org>
 *
 *  based on
 *  SoftDog 0.05:	A Software Watchकरोg Device
 *
 *  (c) Copyright 1996 Alan Cox <alan@lxorguk.ukuu.org.uk>,
 *					All Rights Reserved.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>		/* For module specअगरic items */
#समावेश <linux/moduleparam.h>		/* For new moduleparam's */
#समावेश <linux/types.h>		/* For standard types (like माप_प्रकार) */
#समावेश <linux/त्रुटिसं.स>		/* For the -ENODEV/... values */
#समावेश <linux/kernel.h>		/* For prपूर्णांकk/panic/... */
#समावेश <linux/fs.h>			/* For file operations */
#समावेश <linux/miscdevice.h>		/* For काष्ठा miscdevice */
#समावेश <linux/watchकरोg.h>		/* For the watchकरोg specअगरic items */
#समावेश <linux/init.h>			/* For __init/__निकास/... */
#समावेश <linux/platक्रमm_device.h>	/* For platक्रमm_driver framework */
#समावेश <linux/spinlock.h>		/* For spin_lock/spin_unlock/... */
#समावेश <linux/uaccess.h>		/* For copy_to_user/put_user/... */
#समावेश <linux/पन.स>			/* For devm_ioremap */

#समावेश <यंत्र/mach-rc32434/पूर्णांकeg.h>	/* For the Watchकरोg रेजिस्टरs */

#घोषणा VERSION "1.0"

अटल काष्ठा अणु
	अचिन्हित दीर्घ inuse;
	spinlock_t io_lock;
पूर्ण rc32434_wdt_device;

अटल काष्ठा पूर्णांकeg __iomem *wdt_reg;

अटल पूर्णांक expect_बंद;

/* Board पूर्णांकernal घड़ी speed in Hz,
 * the watchकरोg समयr ticks at. */
बाह्य अचिन्हित पूर्णांक idt_cpu_freq;

/* translate wtcompare value to seconds and vice versa */
#घोषणा WTCOMP2SEC(x)	(x / idt_cpu_freq)
#घोषणा SEC2WTCOMP(x)	(x * idt_cpu_freq)

/* Use a शेष समयout of 20s. This should be
 * safe क्रम CPU घड़ी speeds up to 400MHz, as
 * ((2 ^ 32) - 1) / (400MHz / 2) = 21s.  */
#घोषणा WATCHDOG_TIMEOUT 20

अटल पूर्णांक समयout = WATCHDOG_TIMEOUT;
module_param(समयout, पूर्णांक, 0);
MODULE_PARM_DESC(समयout, "Watchdog timeout value, in seconds (default="
		__MODULE_STRING(WATCHDOG_TIMEOUT) ")");

अटल bool nowayout = WATCHDOG_NOWAYOUT;
module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout, "Watchdog cannot be stopped once started (default="
	__MODULE_STRING(WATCHDOG_NOWAYOUT) ")");

/* apply or and nand masks to data पढ़ो from addr and ग_लिखो back */
#घोषणा SET_BITS(addr, or, nand) \
	ग_लिखोl((पढ़ोl(&addr) | or) & ~nand, &addr)

अटल पूर्णांक rc32434_wdt_set(पूर्णांक new_समयout)
अणु
	पूर्णांक max_to = WTCOMP2SEC((u32)-1);

	अगर (new_समयout < 0 || new_समयout > max_to) अणु
		pr_err("timeout value must be between 0 and %d\n", max_to);
		वापस -EINVAL;
	पूर्ण
	समयout = new_समयout;
	spin_lock(&rc32434_wdt_device.io_lock);
	ग_लिखोl(SEC2WTCOMP(समयout), &wdt_reg->wtcompare);
	spin_unlock(&rc32434_wdt_device.io_lock);

	वापस 0;
पूर्ण

अटल व्योम rc32434_wdt_start(व्योम)
अणु
	u32 or, nand;

	spin_lock(&rc32434_wdt_device.io_lock);

	/* zero the counter beक्रमe enabling */
	ग_लिखोl(0, &wdt_reg->wtcount);

	/* करोn't generate a non-maskable पूर्णांकerrupt,
	 * करो a warm reset instead */
	nand = 1 << RC32434_ERR_WNE;
	or = 1 << RC32434_ERR_WRE;

	/* reset the ERRCS समयout bit in हाल it's set */
	nand |= 1 << RC32434_ERR_WTO;

	SET_BITS(wdt_reg->errcs, or, nand);

	/* set the समयout (either शेष or based on module param) */
	rc32434_wdt_set(समयout);

	/* reset WTC समयout bit and enable WDT */
	nand = 1 << RC32434_WTC_TO;
	or = 1 << RC32434_WTC_EN;

	SET_BITS(wdt_reg->wtc, or, nand);

	spin_unlock(&rc32434_wdt_device.io_lock);
	pr_info("Started watchdog timer\n");
पूर्ण

अटल व्योम rc32434_wdt_stop(व्योम)
अणु
	spin_lock(&rc32434_wdt_device.io_lock);

	/* Disable WDT */
	SET_BITS(wdt_reg->wtc, 0, 1 << RC32434_WTC_EN);

	spin_unlock(&rc32434_wdt_device.io_lock);
	pr_info("Stopped watchdog timer\n");
पूर्ण

अटल व्योम rc32434_wdt_ping(व्योम)
अणु
	spin_lock(&rc32434_wdt_device.io_lock);
	ग_लिखोl(0, &wdt_reg->wtcount);
	spin_unlock(&rc32434_wdt_device.io_lock);
पूर्ण

अटल पूर्णांक rc32434_wdt_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अगर (test_and_set_bit(0, &rc32434_wdt_device.inuse))
		वापस -EBUSY;

	अगर (nowayout)
		__module_get(THIS_MODULE);

	rc32434_wdt_start();
	rc32434_wdt_ping();

	वापस stream_खोलो(inode, file);
पूर्ण

अटल पूर्णांक rc32434_wdt_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अगर (expect_बंद == 42) अणु
		rc32434_wdt_stop();
		module_put(THIS_MODULE);
	पूर्ण अन्यथा अणु
		pr_crit("device closed unexpectedly. WDT will not stop!\n");
		rc32434_wdt_ping();
	पूर्ण
	clear_bit(0, &rc32434_wdt_device.inuse);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार rc32434_wdt_ग_लिखो(काष्ठा file *file, स्थिर अक्षर *data,
				माप_प्रकार len, loff_t *ppos)
अणु
	अगर (len) अणु
		अगर (!nowayout) अणु
			माप_प्रकार i;

			/* In हाल it was set दीर्घ ago */
			expect_बंद = 0;

			क्रम (i = 0; i != len; i++) अणु
				अक्षर c;
				अगर (get_user(c, data + i))
					वापस -EFAULT;
				अगर (c == 'V')
					expect_बंद = 42;
			पूर्ण
		पूर्ण
		rc32434_wdt_ping();
		वापस len;
	पूर्ण
	वापस 0;
पूर्ण

अटल दीर्घ rc32434_wdt_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
				अचिन्हित दीर्घ arg)
अणु
	व्योम __user *argp = (व्योम __user *)arg;
	पूर्णांक new_समयout;
	अचिन्हित पूर्णांक value;
	अटल स्थिर काष्ठा watchकरोg_info ident = अणु
		.options =		WDIOF_SETTIMEOUT |
					WDIOF_KEEPALIVEPING |
					WDIOF_MAGICCLOSE,
		.identity =		"RC32434_WDT Watchdog",
	पूर्ण;
	चयन (cmd) अणु
	हाल WDIOC_GETSUPPORT:
		अगर (copy_to_user(argp, &ident, माप(ident)))
			वापस -EFAULT;
		अवरोध;
	हाल WDIOC_GETSTATUS:
	हाल WDIOC_GETBOOTSTATUS:
		value = 0;
		अगर (copy_to_user(argp, &value, माप(पूर्णांक)))
			वापस -EFAULT;
		अवरोध;
	हाल WDIOC_SETOPTIONS:
		अगर (copy_from_user(&value, argp, माप(पूर्णांक)))
			वापस -EFAULT;
		चयन (value) अणु
		हाल WDIOS_ENABLECARD:
			rc32434_wdt_start();
			अवरोध;
		हाल WDIOS_DISABLECARD:
			rc32434_wdt_stop();
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल WDIOC_KEEPALIVE:
		rc32434_wdt_ping();
		अवरोध;
	हाल WDIOC_SETTIMEOUT:
		अगर (copy_from_user(&new_समयout, argp, माप(पूर्णांक)))
			वापस -EFAULT;
		अगर (rc32434_wdt_set(new_समयout))
			वापस -EINVAL;
		fallthrough;
	हाल WDIOC_GETTIMEOUT:
		वापस copy_to_user(argp, &समयout, माप(पूर्णांक)) ? -EFAULT : 0;
	शेष:
		वापस -ENOTTY;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations rc32434_wdt_fops = अणु
	.owner		= THIS_MODULE,
	.llseek		= no_llseek,
	.ग_लिखो		= rc32434_wdt_ग_लिखो,
	.unlocked_ioctl	= rc32434_wdt_ioctl,
	.compat_ioctl	= compat_ptr_ioctl,
	.खोलो		= rc32434_wdt_खोलो,
	.release	= rc32434_wdt_release,
पूर्ण;

अटल काष्ठा miscdevice rc32434_wdt_miscdev = अणु
	.minor	= WATCHDOG_MINOR,
	.name	= "watchdog",
	.fops	= &rc32434_wdt_fops,
पूर्ण;

अटल पूर्णांक rc32434_wdt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;
	काष्ठा resource *r;

	r = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "rb532_wdt_res");
	अगर (!r) अणु
		pr_err("failed to retrieve resources\n");
		वापस -ENODEV;
	पूर्ण

	wdt_reg = devm_ioremap(&pdev->dev, r->start, resource_size(r));
	अगर (!wdt_reg) अणु
		pr_err("failed to remap I/O resources\n");
		वापस -ENXIO;
	पूर्ण

	spin_lock_init(&rc32434_wdt_device.io_lock);

	/* Make sure the watchकरोg is not running */
	rc32434_wdt_stop();

	/* Check that the heartbeat value is within it's range;
	 * अगर not reset to the शेष */
	अगर (rc32434_wdt_set(समयout)) अणु
		rc32434_wdt_set(WATCHDOG_TIMEOUT);
		pr_info("timeout value must be between 0 and %d\n",
			WTCOMP2SEC((u32)-1));
	पूर्ण

	ret = misc_रेजिस्टर(&rc32434_wdt_miscdev);
	अगर (ret < 0) अणु
		pr_err("failed to register watchdog device\n");
		वापस ret;
	पूर्ण

	pr_info("Watchdog Timer version " VERSION ", timer margin: %d sec\n",
		समयout);

	वापस 0;
पूर्ण

अटल पूर्णांक rc32434_wdt_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	misc_deरेजिस्टर(&rc32434_wdt_miscdev);
	वापस 0;
पूर्ण

अटल व्योम rc32434_wdt_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	rc32434_wdt_stop();
पूर्ण

अटल काष्ठा platक्रमm_driver rc32434_wdt_driver = अणु
	.probe		= rc32434_wdt_probe,
	.हटाओ		= rc32434_wdt_हटाओ,
	.shutकरोwn	= rc32434_wdt_shutकरोwn,
	.driver		= अणु
			.name = "rc32434_wdt",
	पूर्ण
पूर्ण;

module_platक्रमm_driver(rc32434_wdt_driver);

MODULE_AUTHOR("Ondrej Zajicek <santiago@crfreenet.org>,"
		"Florian Fainelli <florian@openwrt.org>");
MODULE_DESCRIPTION("Driver for the IDT RC32434 SoC watchdog");
MODULE_LICENSE("GPL");
