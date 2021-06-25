<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *  Broadcom BCM63xx SoC watchकरोg driver
 *
 *  Copyright (C) 2007, Miguel Gaio <miguel.gaio@efixo.com>
 *  Copyright (C) 2008, Florian Fainelli <florian@खोलोwrt.org>
 *
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/bitops.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/fs.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/types.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/watchकरोg.h>
#समावेश <linux/समयr.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/resource.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <bcm63xx_cpu.h>
#समावेश <bcm63xx_पन.स>
#समावेश <bcm63xx_regs.h>
#समावेश <bcm63xx_समयr.h>

#घोषणा PFX KBUILD_MODNAME

#घोषणा WDT_HZ		50000000 /* Fclk */
#घोषणा WDT_DEFAULT_TIME	30      /* seconds */
#घोषणा WDT_MAX_TIME		256     /* seconds */

अटल काष्ठा अणु
	व्योम __iomem *regs;
	काष्ठा समयr_list समयr;
	अचिन्हित दीर्घ inuse;
	atomic_t ticks;
पूर्ण bcm63xx_wdt_device;

अटल पूर्णांक expect_बंद;

अटल पूर्णांक wdt_समय = WDT_DEFAULT_TIME;
अटल bool nowayout = WATCHDOG_NOWAYOUT;
module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout, "Watchdog cannot be stopped once started (default="
	__MODULE_STRING(WATCHDOG_NOWAYOUT) ")");

/* HW functions */
अटल व्योम bcm63xx_wdt_hw_start(व्योम)
अणु
	bcm_ग_लिखोl(0xfffffffe, bcm63xx_wdt_device.regs + WDT_DEFVAL_REG);
	bcm_ग_लिखोl(WDT_START_1, bcm63xx_wdt_device.regs + WDT_CTL_REG);
	bcm_ग_लिखोl(WDT_START_2, bcm63xx_wdt_device.regs + WDT_CTL_REG);
पूर्ण

अटल व्योम bcm63xx_wdt_hw_stop(व्योम)
अणु
	bcm_ग_लिखोl(WDT_STOP_1, bcm63xx_wdt_device.regs + WDT_CTL_REG);
	bcm_ग_लिखोl(WDT_STOP_2, bcm63xx_wdt_device.regs + WDT_CTL_REG);
पूर्ण

अटल व्योम bcm63xx_wdt_isr(व्योम *data)
अणु
	काष्ठा pt_regs *regs = get_irq_regs();

	die(PFX " fire", regs);
पूर्ण

अटल व्योम bcm63xx_समयr_tick(काष्ठा समयr_list *unused)
अणु
	अगर (!atomic_dec_and_test(&bcm63xx_wdt_device.ticks)) अणु
		bcm63xx_wdt_hw_start();
		mod_समयr(&bcm63xx_wdt_device.समयr, jअगरfies + HZ);
	पूर्ण अन्यथा
		pr_crit("watchdog will restart system\n");
पूर्ण

अटल व्योम bcm63xx_wdt_pet(व्योम)
अणु
	atomic_set(&bcm63xx_wdt_device.ticks, wdt_समय);
पूर्ण

अटल व्योम bcm63xx_wdt_start(व्योम)
अणु
	bcm63xx_wdt_pet();
	bcm63xx_समयr_tick(0);
पूर्ण

अटल व्योम bcm63xx_wdt_छोड़ो(व्योम)
अणु
	del_समयr_sync(&bcm63xx_wdt_device.समयr);
	bcm63xx_wdt_hw_stop();
पूर्ण

अटल पूर्णांक bcm63xx_wdt_समय_रखोout(पूर्णांक new_समय)
अणु
	अगर ((new_समय <= 0) || (new_समय > WDT_MAX_TIME))
		वापस -EINVAL;

	wdt_समय = new_समय;

	वापस 0;
पूर्ण

अटल पूर्णांक bcm63xx_wdt_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अगर (test_and_set_bit(0, &bcm63xx_wdt_device.inuse))
		वापस -EBUSY;

	bcm63xx_wdt_start();
	वापस stream_खोलो(inode, file);
पूर्ण

अटल पूर्णांक bcm63xx_wdt_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अगर (expect_बंद == 42)
		bcm63xx_wdt_छोड़ो();
	अन्यथा अणु
		pr_crit("Unexpected close, not stopping watchdog!\n");
		bcm63xx_wdt_start();
	पूर्ण
	clear_bit(0, &bcm63xx_wdt_device.inuse);
	expect_बंद = 0;
	वापस 0;
पूर्ण

अटल sमाप_प्रकार bcm63xx_wdt_ग_लिखो(काष्ठा file *file, स्थिर अक्षर *data,
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
		bcm63xx_wdt_pet();
	पूर्ण
	वापस len;
पूर्ण

अटल काष्ठा watchकरोg_info bcm63xx_wdt_info = अणु
	.identity       = PFX,
	.options        = WDIOF_SETTIMEOUT |
				WDIOF_KEEPALIVEPING |
				WDIOF_MAGICCLOSE,
पूर्ण;


अटल दीर्घ bcm63xx_wdt_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
				अचिन्हित दीर्घ arg)
अणु
	व्योम __user *argp = (व्योम __user *)arg;
	पूर्णांक __user *p = argp;
	पूर्णांक new_value, retval = -EINVAL;

	चयन (cmd) अणु
	हाल WDIOC_GETSUPPORT:
		वापस copy_to_user(argp, &bcm63xx_wdt_info,
			माप(bcm63xx_wdt_info)) ? -EFAULT : 0;

	हाल WDIOC_GETSTATUS:
	हाल WDIOC_GETBOOTSTATUS:
		वापस put_user(0, p);

	हाल WDIOC_SETOPTIONS:
		अगर (get_user(new_value, p))
			वापस -EFAULT;

		अगर (new_value & WDIOS_DISABLECARD) अणु
			bcm63xx_wdt_छोड़ो();
			retval = 0;
		पूर्ण
		अगर (new_value & WDIOS_ENABLECARD) अणु
			bcm63xx_wdt_start();
			retval = 0;
		पूर्ण

		वापस retval;

	हाल WDIOC_KEEPALIVE:
		bcm63xx_wdt_pet();
		वापस 0;

	हाल WDIOC_SETTIMEOUT:
		अगर (get_user(new_value, p))
			वापस -EFAULT;

		अगर (bcm63xx_wdt_समय_रखोout(new_value))
			वापस -EINVAL;

		bcm63xx_wdt_pet();

	हाल WDIOC_GETTIMEOUT:
		वापस put_user(wdt_समय, p);

	शेष:
		वापस -ENOTTY;

	पूर्ण
पूर्ण

अटल स्थिर काष्ठा file_operations bcm63xx_wdt_fops = अणु
	.owner		= THIS_MODULE,
	.llseek		= no_llseek,
	.ग_लिखो		= bcm63xx_wdt_ग_लिखो,
	.unlocked_ioctl	= bcm63xx_wdt_ioctl,
	.compat_ioctl	= compat_ptr_ioctl,
	.खोलो		= bcm63xx_wdt_खोलो,
	.release	= bcm63xx_wdt_release,
पूर्ण;

अटल काष्ठा miscdevice bcm63xx_wdt_miscdev = अणु
	.minor	= WATCHDOG_MINOR,
	.name	= "watchdog",
	.fops	= &bcm63xx_wdt_fops,
पूर्ण;


अटल पूर्णांक bcm63xx_wdt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;
	काष्ठा resource *r;

	समयr_setup(&bcm63xx_wdt_device.समयr, bcm63xx_समयr_tick, 0);

	r = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!r) अणु
		dev_err(&pdev->dev, "failed to get resources\n");
		वापस -ENODEV;
	पूर्ण

	bcm63xx_wdt_device.regs = devm_ioremap(&pdev->dev, r->start,
							resource_size(r));
	अगर (!bcm63xx_wdt_device.regs) अणु
		dev_err(&pdev->dev, "failed to remap I/O resources\n");
		वापस -ENXIO;
	पूर्ण

	ret = bcm63xx_समयr_रेजिस्टर(TIMER_WDT_ID, bcm63xx_wdt_isr, शून्य);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "failed to register wdt timer isr\n");
		वापस ret;
	पूर्ण

	अगर (bcm63xx_wdt_समय_रखोout(wdt_समय)) अणु
		bcm63xx_wdt_समय_रखोout(WDT_DEFAULT_TIME);
		dev_info(&pdev->dev,
			": wdt_time value must be 1 <= wdt_time <= 256, using %d\n",
			wdt_समय);
	पूर्ण

	ret = misc_रेजिस्टर(&bcm63xx_wdt_miscdev);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "failed to register watchdog device\n");
		जाओ unरेजिस्टर_समयr;
	पूर्ण

	dev_info(&pdev->dev, " started, timer margin: %d sec\n",
						WDT_DEFAULT_TIME);

	वापस 0;

unरेजिस्टर_समयr:
	bcm63xx_समयr_unरेजिस्टर(TIMER_WDT_ID);
	वापस ret;
पूर्ण

अटल पूर्णांक bcm63xx_wdt_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	अगर (!nowayout)
		bcm63xx_wdt_छोड़ो();

	misc_deरेजिस्टर(&bcm63xx_wdt_miscdev);
	bcm63xx_समयr_unरेजिस्टर(TIMER_WDT_ID);
	वापस 0;
पूर्ण

अटल व्योम bcm63xx_wdt_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	bcm63xx_wdt_छोड़ो();
पूर्ण

अटल काष्ठा platक्रमm_driver bcm63xx_wdt_driver = अणु
	.probe	= bcm63xx_wdt_probe,
	.हटाओ = bcm63xx_wdt_हटाओ,
	.shutकरोwn = bcm63xx_wdt_shutकरोwn,
	.driver = अणु
		.name = "bcm63xx-wdt",
	पूर्ण
पूर्ण;

module_platक्रमm_driver(bcm63xx_wdt_driver);

MODULE_AUTHOR("Miguel Gaio <miguel.gaio@efixo.com>");
MODULE_AUTHOR("Florian Fainelli <florian@openwrt.org>");
MODULE_DESCRIPTION("Driver for the Broadcom BCM63xx SoC watchdog");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:bcm63xx-wdt");
