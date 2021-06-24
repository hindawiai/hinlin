<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * mv64x60_wdt.c - MV64X60 (Marvell Discovery) watchकरोg userspace पूर्णांकerface
 *
 * Author: James Chapman <jchapman@katalix.com>
 *
 * Platक्रमm-specअगरic setup code should configure the करोg to generate
 * पूर्णांकerrupt or reset as required.  This code only enables/disables
 * and services the watchकरोg.
 *
 * Derived from mpc8xx_wdt.c, with the following copyright.
 *
 * 2002 (c) Florian Schirmer <jolt@tuxbox.org>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/fs.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/module.h>
#समावेश <linux/watchकरोg.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mv643xx.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/पन.स>

#घोषणा MV64x60_WDT_WDC_OFFSET	0

/*
 * The watchकरोg configuration रेजिस्टर contains a pair of 2-bit fields,
 *   1.  a reload field, bits 27-26, which triggers a reload of
 *       the countकरोwn रेजिस्टर, and
 *   2.  an enable field, bits 25-24, which toggles between
 *       enabling and disabling the watchकरोg समयr.
 * Bit 31 is a पढ़ो-only field which indicates whether the
 * watchकरोg समयr is currently enabled.
 *
 * The low 24 bits contain the समयr reload value.
 */
#घोषणा MV64x60_WDC_ENABLE_SHIFT	24
#घोषणा MV64x60_WDC_SERVICE_SHIFT	26
#घोषणा MV64x60_WDC_ENABLED_SHIFT	31

#घोषणा MV64x60_WDC_ENABLED_TRUE	1
#घोषणा MV64x60_WDC_ENABLED_FALSE	0

/* Flags bits */
#घोषणा MV64x60_WDOG_FLAG_OPENED	0

अटल अचिन्हित दीर्घ wdt_flags;
अटल पूर्णांक wdt_status;
अटल व्योम __iomem *mv64x60_wdt_regs;
अटल पूर्णांक mv64x60_wdt_समयout;
अटल पूर्णांक mv64x60_wdt_count;
अटल अचिन्हित पूर्णांक bus_clk;
अटल अक्षर expect_बंद;
अटल DEFINE_SPINLOCK(mv64x60_wdt_spinlock);

अटल bool nowayout = WATCHDOG_NOWAYOUT;
module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout,
		"Watchdog cannot be stopped once started (default="
				__MODULE_STRING(WATCHDOG_NOWAYOUT) ")");

अटल पूर्णांक mv64x60_wdt_toggle_wdc(पूर्णांक enabled_predicate, पूर्णांक field_shअगरt)
अणु
	u32 data;
	u32 enabled;
	पूर्णांक ret = 0;

	spin_lock(&mv64x60_wdt_spinlock);
	data = पढ़ोl(mv64x60_wdt_regs + MV64x60_WDT_WDC_OFFSET);
	enabled = (data >> MV64x60_WDC_ENABLED_SHIFT) & 1;

	/* only toggle the requested field अगर enabled state matches predicate */
	अगर ((enabled ^ enabled_predicate) == 0) अणु
		/* We ग_लिखो a 1, then a 2 -- to the appropriate field */
		data = (1 << field_shअगरt) | mv64x60_wdt_count;
		ग_लिखोl(data, mv64x60_wdt_regs + MV64x60_WDT_WDC_OFFSET);

		data = (2 << field_shअगरt) | mv64x60_wdt_count;
		ग_लिखोl(data, mv64x60_wdt_regs + MV64x60_WDT_WDC_OFFSET);
		ret = 1;
	पूर्ण
	spin_unlock(&mv64x60_wdt_spinlock);

	वापस ret;
पूर्ण

अटल व्योम mv64x60_wdt_service(व्योम)
अणु
	mv64x60_wdt_toggle_wdc(MV64x60_WDC_ENABLED_TRUE,
			       MV64x60_WDC_SERVICE_SHIFT);
पूर्ण

अटल व्योम mv64x60_wdt_handler_enable(व्योम)
अणु
	अगर (mv64x60_wdt_toggle_wdc(MV64x60_WDC_ENABLED_FALSE,
				   MV64x60_WDC_ENABLE_SHIFT)) अणु
		mv64x60_wdt_service();
		pr_notice("watchdog activated\n");
	पूर्ण
पूर्ण

अटल व्योम mv64x60_wdt_handler_disable(व्योम)
अणु
	अगर (mv64x60_wdt_toggle_wdc(MV64x60_WDC_ENABLED_TRUE,
				   MV64x60_WDC_ENABLE_SHIFT))
		pr_notice("watchdog deactivated\n");
पूर्ण

अटल व्योम mv64x60_wdt_set_समयout(अचिन्हित पूर्णांक समयout)
अणु
	/* maximum bus cycle count is 0xFFFFFFFF */
	अगर (समयout > 0xFFFFFFFF / bus_clk)
		समयout = 0xFFFFFFFF / bus_clk;

	mv64x60_wdt_count = समयout * bus_clk >> 8;
	mv64x60_wdt_समयout = समयout;
पूर्ण

अटल पूर्णांक mv64x60_wdt_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अगर (test_and_set_bit(MV64x60_WDOG_FLAG_OPENED, &wdt_flags))
		वापस -EBUSY;

	अगर (nowayout)
		__module_get(THIS_MODULE);

	mv64x60_wdt_handler_enable();

	वापस stream_खोलो(inode, file);
पूर्ण

अटल पूर्णांक mv64x60_wdt_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अगर (expect_बंद == 42)
		mv64x60_wdt_handler_disable();
	अन्यथा अणु
		pr_crit("unexpected close, not stopping timer!\n");
		mv64x60_wdt_service();
	पूर्ण
	expect_बंद = 0;

	clear_bit(MV64x60_WDOG_FLAG_OPENED, &wdt_flags);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार mv64x60_wdt_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *data,
				 माप_प्रकार len, loff_t *ppos)
अणु
	अगर (len) अणु
		अगर (!nowayout) अणु
			माप_प्रकार i;

			expect_बंद = 0;

			क्रम (i = 0; i != len; i++) अणु
				अक्षर c;
				अगर (get_user(c, data + i))
					वापस -EFAULT;
				अगर (c == 'V')
					expect_बंद = 42;
			पूर्ण
		पूर्ण
		mv64x60_wdt_service();
	पूर्ण

	वापस len;
पूर्ण

अटल दीर्घ mv64x60_wdt_ioctl(काष्ठा file *file,
					अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	पूर्णांक समयout;
	पूर्णांक options;
	व्योम __user *argp = (व्योम __user *)arg;
	अटल स्थिर काष्ठा watchकरोg_info info = अणु
		.options =	WDIOF_SETTIMEOUT	|
				WDIOF_MAGICCLOSE	|
				WDIOF_KEEPALIVEPING,
		.firmware_version = 0,
		.identity = "MV64x60 watchdog",
	पूर्ण;

	चयन (cmd) अणु
	हाल WDIOC_GETSUPPORT:
		अगर (copy_to_user(argp, &info, माप(info)))
			वापस -EFAULT;
		अवरोध;

	हाल WDIOC_GETSTATUS:
	हाल WDIOC_GETBOOTSTATUS:
		अगर (put_user(wdt_status, (पूर्णांक __user *)argp))
			वापस -EFAULT;
		wdt_status &= ~WDIOF_KEEPALIVEPING;
		अवरोध;

	हाल WDIOC_GETTEMP:
		वापस -EOPNOTSUPP;

	हाल WDIOC_SETOPTIONS:
		अगर (get_user(options, (पूर्णांक __user *)argp))
			वापस -EFAULT;

		अगर (options & WDIOS_DISABLECARD)
			mv64x60_wdt_handler_disable();

		अगर (options & WDIOS_ENABLECARD)
			mv64x60_wdt_handler_enable();
		अवरोध;

	हाल WDIOC_KEEPALIVE:
		mv64x60_wdt_service();
		wdt_status |= WDIOF_KEEPALIVEPING;
		अवरोध;

	हाल WDIOC_SETTIMEOUT:
		अगर (get_user(समयout, (पूर्णांक __user *)argp))
			वापस -EFAULT;
		mv64x60_wdt_set_समयout(समयout);
		fallthrough;

	हाल WDIOC_GETTIMEOUT:
		अगर (put_user(mv64x60_wdt_समयout, (पूर्णांक __user *)argp))
			वापस -EFAULT;
		अवरोध;

	शेष:
		वापस -ENOTTY;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations mv64x60_wdt_fops = अणु
	.owner = THIS_MODULE,
	.llseek = no_llseek,
	.ग_लिखो = mv64x60_wdt_ग_लिखो,
	.unlocked_ioctl = mv64x60_wdt_ioctl,
	.compat_ioctl = compat_ptr_ioctl,
	.खोलो = mv64x60_wdt_खोलो,
	.release = mv64x60_wdt_release,
पूर्ण;

अटल काष्ठा miscdevice mv64x60_wdt_miscdev = अणु
	.minor = WATCHDOG_MINOR,
	.name = "watchdog",
	.fops = &mv64x60_wdt_fops,
पूर्ण;

अटल पूर्णांक mv64x60_wdt_probe(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा mv64x60_wdt_pdata *pdata = dev_get_platdata(&dev->dev);
	काष्ठा resource *r;
	पूर्णांक समयout = 10;

	bus_clk = 133;			/* in MHz */
	अगर (pdata) अणु
		समयout = pdata->समयout;
		bus_clk = pdata->bus_clk;
	पूर्ण

	/* Since bus_clk is truncated MHz, actual frequency could be
	 * up to 1MHz higher.  Round up, since it's better to समय out
	 * too late than too soon.
	 */
	bus_clk++;
	bus_clk *= 1000000;		/* convert to Hz */

	r = platक्रमm_get_resource(dev, IORESOURCE_MEM, 0);
	अगर (!r)
		वापस -ENODEV;

	mv64x60_wdt_regs = devm_ioremap(&dev->dev, r->start, resource_size(r));
	अगर (mv64x60_wdt_regs == शून्य)
		वापस -ENOMEM;

	mv64x60_wdt_set_समयout(समयout);

	mv64x60_wdt_handler_disable();	/* in हाल समयr was alपढ़ोy running */

	वापस misc_रेजिस्टर(&mv64x60_wdt_miscdev);
पूर्ण

अटल पूर्णांक mv64x60_wdt_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	misc_deरेजिस्टर(&mv64x60_wdt_miscdev);

	mv64x60_wdt_handler_disable();

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver mv64x60_wdt_driver = अणु
	.probe = mv64x60_wdt_probe,
	.हटाओ = mv64x60_wdt_हटाओ,
	.driver = अणु
		.name = MV64x60_WDT_NAME,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init mv64x60_wdt_init(व्योम)
अणु
	pr_info("MV64x60 watchdog driver\n");

	वापस platक्रमm_driver_रेजिस्टर(&mv64x60_wdt_driver);
पूर्ण

अटल व्योम __निकास mv64x60_wdt_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&mv64x60_wdt_driver);
पूर्ण

module_init(mv64x60_wdt_init);
module_निकास(mv64x60_wdt_निकास);

MODULE_AUTHOR("James Chapman <jchapman@katalix.com>");
MODULE_DESCRIPTION("MV64x60 watchdog driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:" MV64x60_WDT_NAME);
