<शैली गुरु>
/*
 * drivers/अक्षर/watchकरोg/ixp4xx_wdt.c
 *
 * Watchकरोg driver क्रम Intel IXP4xx network processors
 *
 * Author: Deepak Saxena <dsaxena@plनिकासy.net>
 *
 * Copyright 2004 (c) MontaVista, Software, Inc.
 * Based on sa1100 driver, Copyright (C) 2000 Oleg Drokin <green@crimea.edu>
 *
 * This file is licensed under  the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/fs.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/of.h>
#समावेश <linux/watchकरोg.h>
#समावेश <linux/init.h>
#समावेश <linux/bitops.h>
#समावेश <linux/uaccess.h>
#समावेश <mach/hardware.h>

अटल bool nowayout = WATCHDOG_NOWAYOUT;
अटल पूर्णांक heartbeat = 60;	/* (secs) Default is 1 minute */
अटल अचिन्हित दीर्घ wdt_status;
अटल अचिन्हित दीर्घ boot_status;
अटल DEFINE_SPINLOCK(wdt_lock);

#घोषणा WDT_TICK_RATE (IXP4XX_PERIPHERAL_BUS_CLOCK * 1000000UL)

#घोषणा	WDT_IN_USE		0
#घोषणा	WDT_OK_TO_CLOSE		1

अटल व्योम wdt_enable(व्योम)
अणु
	spin_lock(&wdt_lock);
	*IXP4XX_OSWK = IXP4XX_WDT_KEY;
	*IXP4XX_OSWE = 0;
	*IXP4XX_OSWT = WDT_TICK_RATE * heartbeat;
	*IXP4XX_OSWE = IXP4XX_WDT_COUNT_ENABLE | IXP4XX_WDT_RESET_ENABLE;
	*IXP4XX_OSWK = 0;
	spin_unlock(&wdt_lock);
पूर्ण

अटल व्योम wdt_disable(व्योम)
अणु
	spin_lock(&wdt_lock);
	*IXP4XX_OSWK = IXP4XX_WDT_KEY;
	*IXP4XX_OSWE = 0;
	*IXP4XX_OSWK = 0;
	spin_unlock(&wdt_lock);
पूर्ण

अटल पूर्णांक ixp4xx_wdt_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अगर (test_and_set_bit(WDT_IN_USE, &wdt_status))
		वापस -EBUSY;

	clear_bit(WDT_OK_TO_CLOSE, &wdt_status);
	wdt_enable();
	वापस stream_खोलो(inode, file);
पूर्ण

अटल sमाप_प्रकार
ixp4xx_wdt_ग_लिखो(काष्ठा file *file, स्थिर अक्षर *data, माप_प्रकार len, loff_t *ppos)
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
	.options	= WDIOF_CARDRESET | WDIOF_MAGICCLOSE |
			  WDIOF_SETTIMEOUT | WDIOF_KEEPALIVEPING,
	.identity	= "IXP4xx Watchdog",
पूर्ण;


अटल दीर्घ ixp4xx_wdt_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
							अचिन्हित दीर्घ arg)
अणु
	पूर्णांक ret = -ENOTTY;
	पूर्णांक समय;

	चयन (cmd) अणु
	हाल WDIOC_GETSUPPORT:
		ret = copy_to_user((काष्ठा watchकरोg_info *)arg, &ident,
				   माप(ident)) ? -EFAULT : 0;
		अवरोध;

	हाल WDIOC_GETSTATUS:
		ret = put_user(0, (पूर्णांक *)arg);
		अवरोध;

	हाल WDIOC_GETBOOTSTATUS:
		ret = put_user(boot_status, (पूर्णांक *)arg);
		अवरोध;

	हाल WDIOC_KEEPALIVE:
		wdt_enable();
		ret = 0;
		अवरोध;

	हाल WDIOC_SETTIMEOUT:
		ret = get_user(समय, (पूर्णांक *)arg);
		अगर (ret)
			अवरोध;

		अगर (समय <= 0 || समय > 60) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		heartbeat = समय;
		wdt_enable();
		fallthrough;

	हाल WDIOC_GETTIMEOUT:
		ret = put_user(heartbeat, (पूर्णांक *)arg);
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक ixp4xx_wdt_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अगर (test_bit(WDT_OK_TO_CLOSE, &wdt_status))
		wdt_disable();
	अन्यथा
		pr_crit("Device closed unexpectedly - timer will not stop\n");
	clear_bit(WDT_IN_USE, &wdt_status);
	clear_bit(WDT_OK_TO_CLOSE, &wdt_status);

	वापस 0;
पूर्ण


अटल स्थिर काष्ठा file_operations ixp4xx_wdt_fops = अणु
	.owner		= THIS_MODULE,
	.llseek		= no_llseek,
	.ग_लिखो		= ixp4xx_wdt_ग_लिखो,
	.unlocked_ioctl	= ixp4xx_wdt_ioctl,
	.compat_ioctl	= compat_ptr_ioctl,
	.खोलो		= ixp4xx_wdt_खोलो,
	.release	= ixp4xx_wdt_release,
पूर्ण;

अटल काष्ठा miscdevice ixp4xx_wdt_miscdev = अणु
	.minor		= WATCHDOG_MINOR,
	.name		= "watchdog",
	.fops		= &ixp4xx_wdt_fops,
पूर्ण;

अटल पूर्णांक __init ixp4xx_wdt_init(व्योम)
अणु
	पूर्णांक ret;

	/*
	 * FIXME: we bail out on device tree boot but this really needs
	 * to be fixed in a nicer way: this रेजिस्टरs the MDIO bus beक्रमe
	 * even matching the driver infraकाष्ठाure, we should only probe
	 * detected hardware.
	 */
	अगर (of_have_populated_dt())
		वापस -ENODEV;
	अगर (!(पढ़ो_cpuid_id() & 0xf) && !cpu_is_ixp46x()) अणु
		pr_err("Rev. A0 IXP42x CPU detected - watchdog disabled\n");

		वापस -ENODEV;
	पूर्ण
	boot_status = (*IXP4XX_OSST & IXP4XX_OSST_TIMER_WARM_RESET) ?
			WDIOF_CARDRESET : 0;
	ret = misc_रेजिस्टर(&ixp4xx_wdt_miscdev);
	अगर (ret == 0)
		pr_info("timer heartbeat %d sec\n", heartbeat);
	वापस ret;
पूर्ण

अटल व्योम __निकास ixp4xx_wdt_निकास(व्योम)
अणु
	misc_deरेजिस्टर(&ixp4xx_wdt_miscdev);
पूर्ण


module_init(ixp4xx_wdt_init);
module_निकास(ixp4xx_wdt_निकास);

MODULE_AUTHOR("Deepak Saxena <dsaxena@plexity.net>");
MODULE_DESCRIPTION("IXP4xx Network Processor Watchdog");

module_param(heartbeat, पूर्णांक, 0);
MODULE_PARM_DESC(heartbeat, "Watchdog heartbeat in seconds (default 60s)");

module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout, "Watchdog cannot be stopped once started");

MODULE_LICENSE("GPL");
