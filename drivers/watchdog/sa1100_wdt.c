<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *	Watchकरोg driver क्रम the SA11x0/PXA2xx
 *
 *	(c) Copyright 2000 Oleg Drokin <green@crimea.edu>
 *	    Based on SoftDog driver by Alan Cox <alan@lxorguk.ukuu.org.uk>
 *
 *	Neither Oleg Drokin nor iXcelerator.com admit liability nor provide
 *	warranty क्रम any of this software. This material is provided
 *	"AS-IS" and at no अक्षरge.
 *
 *	(c) Copyright 2000           Oleg Drokin <green@crimea.edu>
 *
 *	27/11/2000 Initial release
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/clk.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/fs.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/watchकरोg.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/bitops.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/समयx.h>

#अगर_घोषित CONFIG_ARCH_PXA
#समावेश <mach/regs-ost.h>
#पूर्ण_अगर

#समावेश <mach/reset.h>
#समावेश <mach/hardware.h>

अटल अचिन्हित दीर्घ oscr_freq;
अटल अचिन्हित दीर्घ sa1100wdt_users;
अटल अचिन्हित पूर्णांक pre_margin;
अटल पूर्णांक boot_status;

/*
 *	Allow only one person to hold it खोलो
 */
अटल पूर्णांक sa1100करोg_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अगर (test_and_set_bit(1, &sa1100wdt_users))
		वापस -EBUSY;

	/* Activate SA1100 Watchकरोg समयr */
	ग_लिखोl_relaxed(पढ़ोl_relaxed(OSCR) + pre_margin, OSMR3);
	ग_लिखोl_relaxed(OSSR_M3, OSSR);
	ग_लिखोl_relaxed(OWER_WME, OWER);
	ग_लिखोl_relaxed(पढ़ोl_relaxed(OIER) | OIER_E3, OIER);
	वापस stream_खोलो(inode, file);
पूर्ण

/*
 * The watchकरोg cannot be disabled.
 *
 * Previous comments suggested that turning off the पूर्णांकerrupt by
 * clearing OIER[E3] would prevent the watchकरोg timing out but this
 * करोes not appear to be true (at least on the PXA255).
 */
अटल पूर्णांक sa1100करोg_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	pr_crit("Device closed - timer will not stop\n");
	clear_bit(1, &sa1100wdt_users);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार sa1100करोg_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *data,
						माप_प्रकार len, loff_t *ppos)
अणु
	अगर (len)
		/* Refresh OSMR3 समयr. */
		ग_लिखोl_relaxed(पढ़ोl_relaxed(OSCR) + pre_margin, OSMR3);
	वापस len;
पूर्ण

अटल स्थिर काष्ठा watchकरोg_info ident = अणु
	.options	= WDIOF_CARDRESET | WDIOF_SETTIMEOUT
				| WDIOF_KEEPALIVEPING,
	.identity	= "SA1100/PXA255 Watchdog",
	.firmware_version	= 1,
पूर्ण;

अटल दीर्घ sa1100करोg_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
							अचिन्हित दीर्घ arg)
अणु
	पूर्णांक ret = -ENOTTY;
	पूर्णांक समय;
	व्योम __user *argp = (व्योम __user *)arg;
	पूर्णांक __user *p = argp;

	चयन (cmd) अणु
	हाल WDIOC_GETSUPPORT:
		ret = copy_to_user(argp, &ident,
				   माप(ident)) ? -EFAULT : 0;
		अवरोध;

	हाल WDIOC_GETSTATUS:
		ret = put_user(0, p);
		अवरोध;

	हाल WDIOC_GETBOOTSTATUS:
		ret = put_user(boot_status, p);
		अवरोध;

	हाल WDIOC_KEEPALIVE:
		ग_लिखोl_relaxed(पढ़ोl_relaxed(OSCR) + pre_margin, OSMR3);
		ret = 0;
		अवरोध;

	हाल WDIOC_SETTIMEOUT:
		ret = get_user(समय, p);
		अगर (ret)
			अवरोध;

		अगर (समय <= 0 || (oscr_freq * (दीर्घ दीर्घ)समय >= 0xffffffff)) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		pre_margin = oscr_freq * समय;
		ग_लिखोl_relaxed(पढ़ोl_relaxed(OSCR) + pre_margin, OSMR3);
		fallthrough;

	हाल WDIOC_GETTIMEOUT:
		ret = put_user(pre_margin / oscr_freq, p);
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations sa1100करोg_fops = अणु
	.owner		= THIS_MODULE,
	.llseek		= no_llseek,
	.ग_लिखो		= sa1100करोg_ग_लिखो,
	.unlocked_ioctl	= sa1100करोg_ioctl,
	.compat_ioctl	= compat_ptr_ioctl,
	.खोलो		= sa1100करोg_खोलो,
	.release	= sa1100करोg_release,
पूर्ण;

अटल काष्ठा miscdevice sa1100करोg_miscdev = अणु
	.minor		= WATCHDOG_MINOR,
	.name		= "watchdog",
	.fops		= &sa1100करोg_fops,
पूर्ण;

अटल पूर्णांक margin __initdata = 60;		/* (secs) Default is 1 minute */
अटल काष्ठा clk *clk;

अटल पूर्णांक __init sa1100करोg_init(व्योम)
अणु
	पूर्णांक ret;

	clk = clk_get(शून्य, "OSTIMER0");
	अगर (IS_ERR(clk)) अणु
		pr_err("SA1100/PXA2xx Watchdog Timer: clock not found: %d\n",
		       (पूर्णांक) PTR_ERR(clk));
		वापस PTR_ERR(clk);
	पूर्ण

	ret = clk_prepare_enable(clk);
	अगर (ret) अणु
		pr_err("SA1100/PXA2xx Watchdog Timer: clock failed to prepare+enable: %d\n",
		       ret);
		जाओ err;
	पूर्ण

	oscr_freq = clk_get_rate(clk);

	/*
	 * Read the reset status, and save it क्रम later.  If
	 * we suspend, RCSR will be cleared, and the watchकरोg
	 * reset reason will be lost.
	 */
	boot_status = (reset_status & RESET_STATUS_WATCHDOG) ?
				WDIOF_CARDRESET : 0;
	pre_margin = oscr_freq * margin;

	ret = misc_रेजिस्टर(&sa1100करोg_miscdev);
	अगर (ret == 0) अणु
		pr_info("SA1100/PXA2xx Watchdog Timer: timer margin %d sec\n",
			margin);
		वापस 0;
	पूर्ण

	clk_disable_unprepare(clk);
err:
	clk_put(clk);
	वापस ret;
पूर्ण

अटल व्योम __निकास sa1100करोg_निकास(व्योम)
अणु
	misc_deरेजिस्टर(&sa1100करोg_miscdev);
	clk_disable_unprepare(clk);
	clk_put(clk);
पूर्ण

module_init(sa1100करोg_init);
module_निकास(sa1100करोg_निकास);

MODULE_AUTHOR("Oleg Drokin <green@crimea.edu>");
MODULE_DESCRIPTION("SA1100/PXA2xx Watchdog");

module_param(margin, पूर्णांक, 0);
MODULE_PARM_DESC(margin, "Watchdog margin in seconds (default 60s)");

MODULE_LICENSE("GPL");
