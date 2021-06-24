<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * GE watchकरोg userspace पूर्णांकerface
 *
 * Author:  Martyn Welch <martyn.welch@ge.com>
 *
 * Copyright 2008 GE Intelligent Platक्रमms Embedded Systems, Inc.
 *
 * Based on: mv64x60_wdt.c (MV64X60 watchकरोg userspace पूर्णांकerface)
 *   Author: James Chapman <jchapman@katalix.com>
 */

/* TODO:
 * This driver करोes not provide support क्रम the hardwares capability of sending
 * an पूर्णांकerrupt at a programmable threshold.
 *
 * This driver currently can only support 1 watchकरोg - there are 2 in the
 * hardware that this driver supports. Thus one could be configured as a
 * process-based watchकरोg (via /dev/watchकरोg), the second (using the पूर्णांकerrupt
 * capabilities) a kernel-based watchकरोg.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/compiler.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/watchकरोg.h>
#समावेश <linux/fs.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/पन.स>
#समावेश <linux/uaccess.h>

#समावेश <sysdev/fsl_soc.h>

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
#घोषणा GEF_WDC_ENABLE_SHIFT	24
#घोषणा GEF_WDC_SERVICE_SHIFT	26
#घोषणा GEF_WDC_ENABLED_SHIFT	31

#घोषणा GEF_WDC_ENABLED_TRUE	1
#घोषणा GEF_WDC_ENABLED_FALSE	0

/* Flags bits */
#घोषणा GEF_WDOG_FLAG_OPENED	0

अटल अचिन्हित दीर्घ wdt_flags;
अटल पूर्णांक wdt_status;
अटल व्योम __iomem *gef_wdt_regs;
अटल पूर्णांक gef_wdt_समयout;
अटल पूर्णांक gef_wdt_count;
अटल अचिन्हित पूर्णांक bus_clk;
अटल अक्षर expect_बंद;
अटल DEFINE_SPINLOCK(gef_wdt_spinlock);

अटल bool nowayout = WATCHDOG_NOWAYOUT;
module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout, "Watchdog cannot be stopped once started (default="
	__MODULE_STRING(WATCHDOG_NOWAYOUT) ")");


अटल पूर्णांक gef_wdt_toggle_wdc(पूर्णांक enabled_predicate, पूर्णांक field_shअगरt)
अणु
	u32 data;
	u32 enabled;
	पूर्णांक ret = 0;

	spin_lock(&gef_wdt_spinlock);
	data = ioपढ़ो32be(gef_wdt_regs);
	enabled = (data >> GEF_WDC_ENABLED_SHIFT) & 1;

	/* only toggle the requested field अगर enabled state matches predicate */
	अगर ((enabled ^ enabled_predicate) == 0) अणु
		/* We ग_लिखो a 1, then a 2 -- to the appropriate field */
		data = (1 << field_shअगरt) | gef_wdt_count;
		ioग_लिखो32be(data, gef_wdt_regs);

		data = (2 << field_shअगरt) | gef_wdt_count;
		ioग_लिखो32be(data, gef_wdt_regs);
		ret = 1;
	पूर्ण
	spin_unlock(&gef_wdt_spinlock);

	वापस ret;
पूर्ण

अटल व्योम gef_wdt_service(व्योम)
अणु
	gef_wdt_toggle_wdc(GEF_WDC_ENABLED_TRUE,
		GEF_WDC_SERVICE_SHIFT);
पूर्ण

अटल व्योम gef_wdt_handler_enable(व्योम)
अणु
	अगर (gef_wdt_toggle_wdc(GEF_WDC_ENABLED_FALSE,
				   GEF_WDC_ENABLE_SHIFT)) अणु
		gef_wdt_service();
		pr_notice("watchdog activated\n");
	पूर्ण
पूर्ण

अटल व्योम gef_wdt_handler_disable(व्योम)
अणु
	अगर (gef_wdt_toggle_wdc(GEF_WDC_ENABLED_TRUE,
				   GEF_WDC_ENABLE_SHIFT))
		pr_notice("watchdog deactivated\n");
पूर्ण

अटल व्योम gef_wdt_set_समयout(अचिन्हित पूर्णांक समयout)
अणु
	/* maximum bus cycle count is 0xFFFFFFFF */
	अगर (समयout > 0xFFFFFFFF / bus_clk)
		समयout = 0xFFFFFFFF / bus_clk;

	/* Register only holds upper 24 bits, bit shअगरted पूर्णांकo lower 24 */
	gef_wdt_count = (समयout * bus_clk) >> 8;
	gef_wdt_समयout = समयout;
पूर्ण


अटल sमाप_प्रकार gef_wdt_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *data,
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
		gef_wdt_service();
	पूर्ण

	वापस len;
पूर्ण

अटल दीर्घ gef_wdt_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
							अचिन्हित दीर्घ arg)
अणु
	पूर्णांक समयout;
	पूर्णांक options;
	व्योम __user *argp = (व्योम __user *)arg;
	अटल स्थिर काष्ठा watchकरोg_info info = अणु
		.options =	WDIOF_SETTIMEOUT | WDIOF_MAGICCLOSE |
				WDIOF_KEEPALIVEPING,
		.firmware_version = 0,
		.identity = "GE watchdog",
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

	हाल WDIOC_SETOPTIONS:
		अगर (get_user(options, (पूर्णांक __user *)argp))
			वापस -EFAULT;

		अगर (options & WDIOS_DISABLECARD)
			gef_wdt_handler_disable();

		अगर (options & WDIOS_ENABLECARD)
			gef_wdt_handler_enable();
		अवरोध;

	हाल WDIOC_KEEPALIVE:
		gef_wdt_service();
		wdt_status |= WDIOF_KEEPALIVEPING;
		अवरोध;

	हाल WDIOC_SETTIMEOUT:
		अगर (get_user(समयout, (पूर्णांक __user *)argp))
			वापस -EFAULT;
		gef_wdt_set_समयout(समयout);
		fallthrough;

	हाल WDIOC_GETTIMEOUT:
		अगर (put_user(gef_wdt_समयout, (पूर्णांक __user *)argp))
			वापस -EFAULT;
		अवरोध;

	शेष:
		वापस -ENOTTY;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक gef_wdt_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अगर (test_and_set_bit(GEF_WDOG_FLAG_OPENED, &wdt_flags))
		वापस -EBUSY;

	अगर (nowayout)
		__module_get(THIS_MODULE);

	gef_wdt_handler_enable();

	वापस stream_खोलो(inode, file);
पूर्ण

अटल पूर्णांक gef_wdt_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अगर (expect_बंद == 42)
		gef_wdt_handler_disable();
	अन्यथा अणु
		pr_crit("unexpected close, not stopping timer!\n");
		gef_wdt_service();
	पूर्ण
	expect_बंद = 0;

	clear_bit(GEF_WDOG_FLAG_OPENED, &wdt_flags);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations gef_wdt_fops = अणु
	.owner = THIS_MODULE,
	.llseek = no_llseek,
	.ग_लिखो = gef_wdt_ग_लिखो,
	.unlocked_ioctl = gef_wdt_ioctl,
	.compat_ioctl	= compat_ptr_ioctl,
	.खोलो = gef_wdt_खोलो,
	.release = gef_wdt_release,
पूर्ण;

अटल काष्ठा miscdevice gef_wdt_miscdev = अणु
	.minor = WATCHDOG_MINOR,
	.name = "watchdog",
	.fops = &gef_wdt_fops,
पूर्ण;


अटल पूर्णांक gef_wdt_probe(काष्ठा platक्रमm_device *dev)
अणु
	पूर्णांक समयout = 10;
	u32 freq;

	bus_clk = 133; /* in MHz */

	freq = fsl_get_sys_freq();
	अगर (freq != -1)
		bus_clk = freq;

	/* Map devices रेजिस्टरs पूर्णांकo memory */
	gef_wdt_regs = of_iomap(dev->dev.of_node, 0);
	अगर (gef_wdt_regs == शून्य)
		वापस -ENOMEM;

	gef_wdt_set_समयout(समयout);

	gef_wdt_handler_disable();	/* in हाल समयr was alपढ़ोy running */

	वापस misc_रेजिस्टर(&gef_wdt_miscdev);
पूर्ण

अटल पूर्णांक gef_wdt_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	misc_deरेजिस्टर(&gef_wdt_miscdev);

	gef_wdt_handler_disable();

	iounmap(gef_wdt_regs);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id gef_wdt_ids[] = अणु
	अणु
		.compatible = "gef,fpga-wdt",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, gef_wdt_ids);

अटल काष्ठा platक्रमm_driver gef_wdt_driver = अणु
	.driver = अणु
		.name = "gef_wdt",
		.of_match_table = gef_wdt_ids,
	पूर्ण,
	.probe		= gef_wdt_probe,
	.हटाओ		= gef_wdt_हटाओ,
पूर्ण;

अटल पूर्णांक __init gef_wdt_init(व्योम)
अणु
	pr_info("GE watchdog driver\n");
	वापस platक्रमm_driver_रेजिस्टर(&gef_wdt_driver);
पूर्ण

अटल व्योम __निकास gef_wdt_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&gef_wdt_driver);
पूर्ण

module_init(gef_wdt_init);
module_निकास(gef_wdt_निकास);

MODULE_AUTHOR("Martyn Welch <martyn.welch@ge.com>");
MODULE_DESCRIPTION("GE watchdog driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:gef_wdt");
