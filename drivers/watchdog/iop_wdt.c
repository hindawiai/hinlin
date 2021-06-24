<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * drivers/अक्षर/watchकरोg/iop_wdt.c
 *
 * WDT driver क्रम Intel I/O Processors
 * Copyright (C) 2005, Intel Corporation.
 *
 * Based on ixp4xx driver, Copyright 2004 (c) MontaVista, Software, Inc.
 *
 *	Curt E Bruns <curt.e.bruns@पूर्णांकel.com>
 *	Peter Milne <peter.milne@d-tacq.com>
 *	Dan Williams <dan.j.williams@पूर्णांकel.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/fs.h>
#समावेश <linux/init.h>
#समावेश <linux/device.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/watchकरोg.h>
#समावेश <linux/uaccess.h>
#समावेश <mach/hardware.h>

अटल bool nowayout = WATCHDOG_NOWAYOUT;
अटल अचिन्हित दीर्घ wdt_status;
अटल अचिन्हित दीर्घ boot_status;
अटल DEFINE_SPINLOCK(wdt_lock);

#घोषणा WDT_IN_USE		0
#घोषणा WDT_OK_TO_CLOSE		1
#घोषणा WDT_ENABLED		2

अटल अचिन्हित दीर्घ iop_watchकरोg_समयout(व्योम)
अणु
	वापस (0xffffffffUL / get_iop_tick_rate());
पूर्ण

/**
 * wdt_supports_disable - determine अगर we are accessing a iop13xx watchकरोg
 * or iop3xx by whether it has a disable command
 */
अटल पूर्णांक wdt_supports_disable(व्योम)
अणु
	पूर्णांक can_disable;

	अगर (IOP_WDTCR_EN_ARM != IOP_WDTCR_DIS_ARM)
		can_disable = 1;
	अन्यथा
		can_disable = 0;

	वापस can_disable;
पूर्ण

अटल व्योम wdt_enable(व्योम)
अणु
	/* Arm and enable the Timer to starting counting करोwn from 0xFFFF.FFFF
	 * Takes approx. 10.7s to समयout
	 */
	spin_lock(&wdt_lock);
	ग_लिखो_wdtcr(IOP_WDTCR_EN_ARM);
	ग_लिखो_wdtcr(IOP_WDTCR_EN);
	spin_unlock(&wdt_lock);
पूर्ण

/* वापसs 0 अगर the समयr was successfully disabled */
अटल पूर्णांक wdt_disable(व्योम)
अणु
	/* Stop Counting */
	अगर (wdt_supports_disable()) अणु
		spin_lock(&wdt_lock);
		ग_लिखो_wdtcr(IOP_WDTCR_DIS_ARM);
		ग_लिखो_wdtcr(IOP_WDTCR_DIS);
		clear_bit(WDT_ENABLED, &wdt_status);
		spin_unlock(&wdt_lock);
		pr_info("Disabled\n");
		वापस 0;
	पूर्ण अन्यथा
		वापस 1;
पूर्ण

अटल पूर्णांक iop_wdt_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अगर (test_and_set_bit(WDT_IN_USE, &wdt_status))
		वापस -EBUSY;

	clear_bit(WDT_OK_TO_CLOSE, &wdt_status);
	wdt_enable();
	set_bit(WDT_ENABLED, &wdt_status);
	वापस stream_खोलो(inode, file);
पूर्ण

अटल sमाप_प्रकार iop_wdt_ग_लिखो(काष्ठा file *file, स्थिर अक्षर *data, माप_प्रकार len,
		  loff_t *ppos)
अणु
	अगर (len) अणु
		अगर (!nowayout) अणु
			माप_प्रकार i;

			clear_bit(WDT_OK_TO_CLOSE, &wdt_status);

			क्रम (i = 0; i != len; i++) अणु
				अक्षर c;

				अगर (get_user(c, data + i))
					वापस -EFAULT;
				अगर (c == 'V')
					set_bit(WDT_OK_TO_CLOSE, &wdt_status);
			पूर्ण
		पूर्ण
		wdt_enable();
	पूर्ण
	वापस len;
पूर्ण

अटल स्थिर काष्ठा watchकरोg_info ident = अणु
	.options = WDIOF_CARDRESET | WDIOF_MAGICCLOSE | WDIOF_KEEPALIVEPING,
	.identity = "iop watchdog",
पूर्ण;

अटल दीर्घ iop_wdt_ioctl(काष्ठा file *file,
				अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	पूर्णांक options;
	पूर्णांक ret = -ENOTTY;
	पूर्णांक __user *argp = (पूर्णांक __user *)arg;

	चयन (cmd) अणु
	हाल WDIOC_GETSUPPORT:
		अगर (copy_to_user(argp, &ident, माप(ident)))
			ret = -EFAULT;
		अन्यथा
			ret = 0;
		अवरोध;

	हाल WDIOC_GETSTATUS:
		ret = put_user(0, argp);
		अवरोध;

	हाल WDIOC_GETBOOTSTATUS:
		ret = put_user(boot_status, argp);
		अवरोध;

	हाल WDIOC_SETOPTIONS:
		अगर (get_user(options, (पूर्णांक *)arg))
			वापस -EFAULT;

		अगर (options & WDIOS_DISABLECARD) अणु
			अगर (!nowayout) अणु
				अगर (wdt_disable() == 0) अणु
					set_bit(WDT_OK_TO_CLOSE, &wdt_status);
					ret = 0;
				पूर्ण अन्यथा
					ret = -ENXIO;
			पूर्ण अन्यथा
				ret = 0;
		पूर्ण
		अगर (options & WDIOS_ENABLECARD) अणु
			wdt_enable();
			ret = 0;
		पूर्ण
		अवरोध;

	हाल WDIOC_KEEPALIVE:
		wdt_enable();
		ret = 0;
		अवरोध;

	हाल WDIOC_GETTIMEOUT:
		ret = put_user(iop_watchकरोg_समयout(), argp);
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक iop_wdt_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	पूर्णांक state = 1;
	अगर (test_bit(WDT_OK_TO_CLOSE, &wdt_status))
		अगर (test_bit(WDT_ENABLED, &wdt_status))
			state = wdt_disable();

	/* अगर the समयr is not disabled reload and notअगरy that we are still
	 * going करोwn
	 */
	अगर (state != 0) अणु
		wdt_enable();
		pr_crit("Device closed unexpectedly - reset in %lu seconds\n",
			iop_watchकरोg_समयout());
	पूर्ण

	clear_bit(WDT_IN_USE, &wdt_status);
	clear_bit(WDT_OK_TO_CLOSE, &wdt_status);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations iop_wdt_fops = अणु
	.owner = THIS_MODULE,
	.llseek = no_llseek,
	.ग_लिखो = iop_wdt_ग_लिखो,
	.unlocked_ioctl = iop_wdt_ioctl,
	.compat_ioctl = compat_ptr_ioctl,
	.खोलो = iop_wdt_खोलो,
	.release = iop_wdt_release,
पूर्ण;

अटल काष्ठा miscdevice iop_wdt_miscdev = अणु
	.minor = WATCHDOG_MINOR,
	.name = "watchdog",
	.fops = &iop_wdt_fops,
पूर्ण;

अटल पूर्णांक __init iop_wdt_init(व्योम)
अणु
	पूर्णांक ret;

	/* check अगर the reset was caused by the watchकरोg समयr */
	boot_status = (पढ़ो_rcsr() & IOP_RCSR_WDT) ? WDIOF_CARDRESET : 0;

	/* Configure Watchकरोg Timeout to cause an Internal Bus (IB) Reset
	 * NOTE: An IB Reset will Reset both cores in the IOP342
	 */
	ग_लिखो_wdtsr(IOP13XX_WDTCR_IB_RESET);

	/* Register after we have the device set up so we cannot race
	   with an खोलो */
	ret = misc_रेजिस्टर(&iop_wdt_miscdev);
	अगर (ret == 0)
		pr_info("timeout %lu sec\n", iop_watchकरोg_समयout());

	वापस ret;
पूर्ण

अटल व्योम __निकास iop_wdt_निकास(व्योम)
अणु
	misc_deरेजिस्टर(&iop_wdt_miscdev);
पूर्ण

module_init(iop_wdt_init);
module_निकास(iop_wdt_निकास);

module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout, "Watchdog cannot be stopped once started");

MODULE_AUTHOR("Curt E Bruns <curt.e.bruns@intel.com>");
MODULE_DESCRIPTION("iop watchdog timer driver");
MODULE_LICENSE("GPL");
