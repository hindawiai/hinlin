<शैली गुरु>
/*
 * drivers/watchकरोg/m54xx_wdt.c
 *
 * Watchकरोg driver क्रम ColdFire MCF547x & MCF548x processors
 * Copyright 2010 (c) Philippe De Muyter <phdm@macqel.be>
 *
 * Adapted from the IXP4xx watchकरोg driver, which carries these notices:
 *
 *  Author: Deepak Saxena <dsaxena@plनिकासy.net>
 *
 *  Copyright 2004 (c) MontaVista, Software, Inc.
 *  Based on sa1100 driver, Copyright (C) 2000 Oleg Drokin <green@crimea.edu>
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
#समावेश <linux/watchकरोg.h>
#समावेश <linux/init.h>
#समावेश <linux/bitops.h>
#समावेश <linux/ioport.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/पन.स>

#समावेश <यंत्र/coldfire.h>
#समावेश <यंत्र/m54xxsim.h>
#समावेश <यंत्र/m54xxgpt.h>

अटल bool nowayout = WATCHDOG_NOWAYOUT;
अटल अचिन्हित पूर्णांक heartbeat = 30;	/* (secs) Default is 0.5 minute */
अटल अचिन्हित दीर्घ wdt_status;

#घोषणा	WDT_IN_USE		0
#घोषणा	WDT_OK_TO_CLOSE		1

अटल व्योम wdt_enable(व्योम)
अणु
	अचिन्हित पूर्णांक gms0;

	/* preserve GPIO usage, अगर any */
	gms0 = __raw_पढ़ोl(MCF_GPT_GMS0);
	अगर (gms0 & MCF_GPT_GMS_TMS_GPIO)
		gms0 &= (MCF_GPT_GMS_TMS_GPIO | MCF_GPT_GMS_GPIO_MASK
							| MCF_GPT_GMS_OD);
	अन्यथा
		gms0 = MCF_GPT_GMS_TMS_GPIO | MCF_GPT_GMS_OD;
	__raw_ग_लिखोl(gms0, MCF_GPT_GMS0);
	__raw_ग_लिखोl(MCF_GPT_GCIR_PRE(heartbeat*(MCF_BUSCLK/0xffff)) |
			MCF_GPT_GCIR_CNT(0xffff), MCF_GPT_GCIR0);
	gms0 |= MCF_GPT_GMS_OCPW(0xA5) | MCF_GPT_GMS_WDEN | MCF_GPT_GMS_CE;
	__raw_ग_लिखोl(gms0, MCF_GPT_GMS0);
पूर्ण

अटल व्योम wdt_disable(व्योम)
अणु
	अचिन्हित पूर्णांक gms0;

	/* disable watchकरोg */
	gms0 = __raw_पढ़ोl(MCF_GPT_GMS0);
	gms0 &= ~(MCF_GPT_GMS_WDEN | MCF_GPT_GMS_CE);
	__raw_ग_लिखोl(gms0, MCF_GPT_GMS0);
पूर्ण

अटल व्योम wdt_keepalive(व्योम)
अणु
	अचिन्हित पूर्णांक gms0;

	gms0 = __raw_पढ़ोl(MCF_GPT_GMS0);
	gms0 |= MCF_GPT_GMS_OCPW(0xA5);
	__raw_ग_लिखोl(gms0, MCF_GPT_GMS0);
पूर्ण

अटल पूर्णांक m54xx_wdt_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अगर (test_and_set_bit(WDT_IN_USE, &wdt_status))
		वापस -EBUSY;

	clear_bit(WDT_OK_TO_CLOSE, &wdt_status);
	wdt_enable();
	वापस stream_खोलो(inode, file);
पूर्ण

अटल sमाप_प्रकार m54xx_wdt_ग_लिखो(काष्ठा file *file, स्थिर अक्षर *data,
						माप_प्रकार len, loff_t *ppos)
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
		wdt_keepalive();
	पूर्ण
	वापस len;
पूर्ण

अटल स्थिर काष्ठा watchकरोg_info ident = अणु
	.options	= WDIOF_MAGICCLOSE | WDIOF_SETTIMEOUT |
				WDIOF_KEEPALIVEPING,
	.identity	= "Coldfire M54xx Watchdog",
पूर्ण;

अटल दीर्घ m54xx_wdt_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
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
		ret = put_user(0, (पूर्णांक *)arg);
		अवरोध;

	हाल WDIOC_KEEPALIVE:
		wdt_keepalive();
		ret = 0;
		अवरोध;

	हाल WDIOC_SETTIMEOUT:
		ret = get_user(समय, (पूर्णांक *)arg);
		अगर (ret)
			अवरोध;

		अगर (समय <= 0 || समय > 30) अणु
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

अटल पूर्णांक m54xx_wdt_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अगर (test_bit(WDT_OK_TO_CLOSE, &wdt_status))
		wdt_disable();
	अन्यथा अणु
		pr_crit("Device closed unexpectedly - timer will not stop\n");
		wdt_keepalive();
	पूर्ण
	clear_bit(WDT_IN_USE, &wdt_status);
	clear_bit(WDT_OK_TO_CLOSE, &wdt_status);

	वापस 0;
पूर्ण


अटल स्थिर काष्ठा file_operations m54xx_wdt_fops = अणु
	.owner		= THIS_MODULE,
	.llseek		= no_llseek,
	.ग_लिखो		= m54xx_wdt_ग_लिखो,
	.unlocked_ioctl	= m54xx_wdt_ioctl,
	.compat_ioctl	= compat_ptr_ioctl,
	.खोलो		= m54xx_wdt_खोलो,
	.release	= m54xx_wdt_release,
पूर्ण;

अटल काष्ठा miscdevice m54xx_wdt_miscdev = अणु
	.minor		= WATCHDOG_MINOR,
	.name		= "watchdog",
	.fops		= &m54xx_wdt_fops,
पूर्ण;

अटल पूर्णांक __init m54xx_wdt_init(व्योम)
अणु
	अगर (!request_mem_region(MCF_GPT_GCIR0, 4, "Coldfire M54xx Watchdog")) अणु
		pr_warn("I/O region busy\n");
		वापस -EBUSY;
	पूर्ण
	pr_info("driver is loaded\n");

	वापस misc_रेजिस्टर(&m54xx_wdt_miscdev);
पूर्ण

अटल व्योम __निकास m54xx_wdt_निकास(व्योम)
अणु
	misc_deरेजिस्टर(&m54xx_wdt_miscdev);
	release_mem_region(MCF_GPT_GCIR0, 4);
पूर्ण

module_init(m54xx_wdt_init);
module_निकास(m54xx_wdt_निकास);

MODULE_AUTHOR("Philippe De Muyter <phdm@macqel.be>");
MODULE_DESCRIPTION("Coldfire M54xx Watchdog");

module_param(heartbeat, पूर्णांक, 0);
MODULE_PARM_DESC(heartbeat, "Watchdog heartbeat in seconds (default 30s)");

module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout, "Watchdog cannot be stopped once started");

MODULE_LICENSE("GPL");
