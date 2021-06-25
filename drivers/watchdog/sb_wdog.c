<शैली गुरु>
/*
 * Watchकरोg driver क्रम SiByte SB1 SoCs
 *
 * Copyright (C) 2007 OnStor, Inc. * Andrew Sharp <andy.sharp@lsi.com>
 *
 * This driver is पूर्णांकended to make the second of two hardware watchकरोgs
 * on the Sibyte 12XX and 11XX SoCs available to the user.  There are two
 * such devices available on the SoC, but it seems that there isn't an
 * क्रमागतeration class क्रम watchकरोgs in Linux like there is क्रम RTCs.
 * The second is used rather than the first because it uses IRQ 1,
 * thereby aव्योमing all that IRQ 0 problematic nonsense.
 *
 * I have not tried this driver on a 1480 processor; it might work
 * just well enough to really screw things up.
 *
 * It is a simple समयr, and there is an पूर्णांकerrupt that is उठाओd the
 * first समय the समयr expires.  The second समय it expires, the chip
 * is reset and there is no way to redirect that NMI.  Which could
 * be problematic in some हालs where this chip is sitting on the HT
 * bus and has just taken responsibility क्रम providing a cache block.
 * Since the reset can't be redirected to the बाह्यal reset pin, it is
 * possible that other HT connected processors might hang and not reset.
 * For Linux, a soft reset would probably be even worse than a hard reset.
 * There you have it.
 *
 * The समयr takes 23 bits of a 64 bit रेजिस्टर (?) as a count value,
 * and decrements the count every microsecond, क्रम a max value of
 * 0x7fffff usec or about 8.3ish seconds.
 *
 * This watchकरोg borrows some user semantics from the softकरोg driver,
 * in that अगर you बंद the fd, it leaves the watchकरोg running, unless
 * you previously wrote a 'V' to the fd, in which हाल it disables
 * the watchकरोg when you बंद the fd like some other drivers.
 *
 * Based on various other watchकरोg drivers, which are probably all
 * loosely based on something Alan Cox wrote years ago.
 *
 *	(c) Copyright 1996 Alan Cox <alan@lxorguk.ukuu.org.uk>,
 *						All Rights Reserved.
 *
 *	This program is मुक्त software; you can redistribute it and/or
 *	modअगरy it under the terms of the GNU General Public License
 *	version 1 or 2 as published by the Free Software Foundation.
 *
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/पन.स>
#समावेश <linux/uaccess.h>
#समावेश <linux/fs.h>
#समावेश <linux/reboot.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/watchकरोg.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश <यंत्र/sibyte/sb1250.h>
#समावेश <यंत्र/sibyte/sb1250_regs.h>
#समावेश <यंत्र/sibyte/sb1250_पूर्णांक.h>
#समावेश <यंत्र/sibyte/sb1250_scd.h>

अटल DEFINE_SPINLOCK(sbwd_lock);

/*
 * set the initial count value of a समयr
 *
 * wकरोg is the iomem address of the cfg रेजिस्टर
 */
अटल व्योम sbwकरोg_set(अक्षर __iomem *wकरोg, अचिन्हित दीर्घ t)
अणु
	spin_lock(&sbwd_lock);
	__raw_ग_लिखोb(0, wकरोg);
	__raw_ग_लिखोq(t & 0x7fffffUL, wकरोg - 0x10);
	spin_unlock(&sbwd_lock);
पूर्ण

/*
 * cause the समयr to [re]load it's initial count and start counting
 * all over again
 *
 * wकरोg is the iomem address of the cfg रेजिस्टर
 */
अटल व्योम sbwकरोg_pet(अक्षर __iomem *wकरोg)
अणु
	spin_lock(&sbwd_lock);
	__raw_ग_लिखोb(__raw_पढ़ोb(wकरोg) | 1, wकरोg);
	spin_unlock(&sbwd_lock);
पूर्ण

अटल अचिन्हित दीर्घ sbwकरोg_gate; /* keeps it to one thपढ़ो only */
अटल अक्षर __iomem *kern_करोg = (अक्षर __iomem *)(IO_BASE + (A_SCD_WDOG_CFG_0));
अटल अक्षर __iomem *user_करोg = (अक्षर __iomem *)(IO_BASE + (A_SCD_WDOG_CFG_1));
अटल अचिन्हित दीर्घ समयout = 0x7fffffUL;	/* useconds: 8.3ish secs. */
अटल पूर्णांक expect_बंद;

अटल स्थिर काष्ठा watchकरोg_info ident = अणु
	.options	= WDIOF_CARDRESET | WDIOF_SETTIMEOUT |
					WDIOF_KEEPALIVEPING | WDIOF_MAGICCLOSE,
	.identity	= "SiByte Watchdog",
पूर्ण;

/*
 * Allow only a single thपढ़ो to walk the करोg
 */
अटल पूर्णांक sbwकरोg_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	stream_खोलो(inode, file);
	अगर (test_and_set_bit(0, &sbwकरोg_gate))
		वापस -EBUSY;
	__module_get(THIS_MODULE);

	/*
	 * Activate the समयr
	 */
	sbwकरोg_set(user_करोg, समयout);
	__raw_ग_लिखोb(1, user_करोg);

	वापस 0;
पूर्ण

/*
 * Put the करोg back in the kennel.
 */
अटल पूर्णांक sbwकरोg_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अगर (expect_बंद == 42) अणु
		__raw_ग_लिखोb(0, user_करोg);
		module_put(THIS_MODULE);
	पूर्ण अन्यथा अणु
		pr_crit("%s: Unexpected close, not stopping watchdog!\n",
			ident.identity);
		sbwकरोg_pet(user_करोg);
	पूर्ण
	clear_bit(0, &sbwकरोg_gate);
	expect_बंद = 0;

	वापस 0;
पूर्ण

/*
 * 42 - the answer
 */
अटल sमाप_प्रकार sbwकरोg_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *data,
			माप_प्रकार len, loff_t *ppos)
अणु
	पूर्णांक i;

	अगर (len) अणु
		/*
		 * restart the समयr
		 */
		expect_बंद = 0;

		क्रम (i = 0; i != len; i++) अणु
			अक्षर c;

			अगर (get_user(c, data + i))
				वापस -EFAULT;
			अगर (c == 'V')
				expect_बंद = 42;
		पूर्ण
		sbwकरोg_pet(user_करोg);
	पूर्ण

	वापस len;
पूर्ण

अटल दीर्घ sbwकरोg_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
						अचिन्हित दीर्घ arg)
अणु
	पूर्णांक ret = -ENOTTY;
	अचिन्हित दीर्घ समय;
	व्योम __user *argp = (व्योम __user *)arg;
	पूर्णांक __user *p = argp;

	चयन (cmd) अणु
	हाल WDIOC_GETSUPPORT:
		ret = copy_to_user(argp, &ident, माप(ident)) ? -EFAULT : 0;
		अवरोध;

	हाल WDIOC_GETSTATUS:
	हाल WDIOC_GETBOOTSTATUS:
		ret = put_user(0, p);
		अवरोध;

	हाल WDIOC_KEEPALIVE:
		sbwकरोg_pet(user_करोg);
		ret = 0;
		अवरोध;

	हाल WDIOC_SETTIMEOUT:
		ret = get_user(समय, p);
		अगर (ret)
			अवरोध;

		समय *= 1000000;
		अगर (समय > 0x7fffffUL) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		समयout = समय;
		sbwकरोg_set(user_करोg, समयout);
		sbwकरोg_pet(user_करोg);
		fallthrough;

	हाल WDIOC_GETTIMEOUT:
		/*
		 * get the reमुख्यing count from the ... count रेजिस्टर
		 * which is 1*8 beक्रमe the config रेजिस्टर
		 */
		ret = put_user((u32)__raw_पढ़ोq(user_करोg - 8) / 1000000, p);
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

/*
 *	Notअगरier क्रम प्रणाली करोwn
 */
अटल पूर्णांक sbwकरोg_notअगरy_sys(काष्ठा notअगरier_block *this, अचिन्हित दीर्घ code,
								व्योम *erf)
अणु
	अगर (code == SYS_DOWN || code == SYS_HALT) अणु
		/*
		 * sit and sit
		 */
		__raw_ग_लिखोb(0, user_करोg);
		__raw_ग_लिखोb(0, kern_करोg);
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

अटल स्थिर काष्ठा file_operations sbwकरोg_fops = अणु
	.owner		= THIS_MODULE,
	.llseek		= no_llseek,
	.ग_लिखो		= sbwकरोg_ग_लिखो,
	.unlocked_ioctl	= sbwकरोg_ioctl,
	.compat_ioctl	= compat_ptr_ioctl,
	.खोलो		= sbwकरोg_खोलो,
	.release	= sbwकरोg_release,
पूर्ण;

अटल काष्ठा miscdevice sbwकरोg_miscdev = अणु
	.minor		= WATCHDOG_MINOR,
	.name		= "watchdog",
	.fops		= &sbwकरोg_fops,
पूर्ण;

अटल काष्ठा notअगरier_block sbwकरोg_notअगरier = अणु
	.notअगरier_call	= sbwकरोg_notअगरy_sys,
पूर्ण;

/*
 * पूर्णांकerrupt handler
 *
 * करोesn't करो a whole lot क्रम user, but oh so cleverly written so kernel
 * code can use it to re-up the watchकरोg, thereby saving the kernel from
 * having to create and मुख्यtain a समयr, just to tickle another समयr,
 * which is just so wrong.
 */
irqवापस_t sbwकरोg_पूर्णांकerrupt(पूर्णांक irq, व्योम *addr)
अणु
	अचिन्हित दीर्घ wd_init;
	अक्षर *wd_cfg_reg = (अक्षर *)addr;
	u8 cfg;

	cfg = __raw_पढ़ोb(wd_cfg_reg);
	wd_init = __raw_पढ़ोq(wd_cfg_reg - 8) & 0x7fffff;

	/*
	 * अगर it's the second watchdog timer, it's क्रम those users
	 */
	अगर (wd_cfg_reg == user_करोg)
		pr_crit("%s in danger of initiating system reset "
			"in %ld.%01ld seconds\n",
			ident.identity,
			wd_init / 1000000, (wd_init / 100000) % 10);
	अन्यथा
		cfg |= 1;

	__raw_ग_लिखोb(cfg, wd_cfg_reg);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक __init sbwकरोg_init(व्योम)
अणु
	पूर्णांक ret;

	/*
	 * रेजिस्टर a reboot notअगरier
	 */
	ret = रेजिस्टर_reboot_notअगरier(&sbwकरोg_notअगरier);
	अगर (ret) अणु
		pr_err("%s: cannot register reboot notifier (err=%d)\n",
		       ident.identity, ret);
		वापस ret;
	पूर्ण

	/*
	 * get the resources
	 */

	ret = request_irq(1, sbwकरोg_पूर्णांकerrupt, IRQF_SHARED,
		ident.identity, (व्योम *)user_करोg);
	अगर (ret) अणु
		pr_err("%s: failed to request irq 1 - %d\n",
		       ident.identity, ret);
		जाओ out;
	पूर्ण

	ret = misc_रेजिस्टर(&sbwकरोg_miscdev);
	अगर (ret == 0) अणु
		pr_info("%s: timeout is %ld.%ld secs\n",
			ident.identity,
			समयout / 1000000, (समयout / 100000) % 10);
		वापस 0;
	पूर्ण
	मुक्त_irq(1, (व्योम *)user_करोg);
out:
	unरेजिस्टर_reboot_notअगरier(&sbwकरोg_notअगरier);

	वापस ret;
पूर्ण

अटल व्योम __निकास sbwकरोg_निकास(व्योम)
अणु
	misc_deरेजिस्टर(&sbwकरोg_miscdev);
	मुक्त_irq(1, (व्योम *)user_करोg);
	unरेजिस्टर_reboot_notअगरier(&sbwकरोg_notअगरier);
पूर्ण

module_init(sbwकरोg_init);
module_निकास(sbwकरोg_निकास);

MODULE_AUTHOR("Andrew Sharp <andy.sharp@lsi.com>");
MODULE_DESCRIPTION("SiByte Watchdog");

module_param(समयout, uदीर्घ, 0);
MODULE_PARM_DESC(समयout,
      "Watchdog timeout in microseconds (max/default 8388607 or 8.3ish secs)");

MODULE_LICENSE("GPL");

/*
 * example code that can be put in a platक्रमm code area to utilize the
 * first watchकरोg समयr क्रम the kernels own purpose.

व्योम platक्रमm_wd_setup(व्योम)
अणु
	पूर्णांक ret;

	ret = request_irq(1, sbwकरोg_पूर्णांकerrupt, IRQF_SHARED,
		"Kernel Watchdog", IOADDR(A_SCD_WDOG_CFG_0));
	अगर (ret) अणु
		pr_crit("Watchdog IRQ zero(0) failed to be requested - %d\n", ret);
	पूर्ण
पूर्ण


 */
