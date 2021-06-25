<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	Intel 21285 watchकरोg driver
 *	Copyright (c) Phil Blundell <pb@nexus.co.uk>, 1998
 *
 *	based on
 *
 *	SoftDog	0.05:	A Software Watchकरोg Device
 *
 *	(c) Copyright 1996 Alan Cox <alan@lxorguk.ukuu.org.uk>,
 *						All Rights Reserved.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/fs.h>
#समावेश <linux/mm.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/watchकरोg.h>
#समावेश <linux/reboot.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/irq.h>
#समावेश <mach/hardware.h>

#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/प्रणाली_info.h>
#समावेश <यंत्र/hardware/dec21285.h>

/*
 * Define this to stop the watchकरोg actually rebooting the machine.
 */
#अघोषित ONLY_TESTING

अटल अचिन्हित पूर्णांक soft_margin = 60;		/* in seconds */
अटल अचिन्हित पूर्णांक reload;
अटल अचिन्हित दीर्घ समयr_alive;

#अगर_घोषित ONLY_TESTING
/*
 *	If the समयr expires..
 */
अटल व्योम watchकरोg_fire(पूर्णांक irq, व्योम *dev_id)
अणु
	pr_crit("Would Reboot\n");
	*CSR_TIMER4_CNTL = 0;
	*CSR_TIMER4_CLR = 0;
पूर्ण
#पूर्ण_अगर

/*
 *	Refresh the समयr.
 */
अटल व्योम watchकरोg_ping(व्योम)
अणु
	*CSR_TIMER4_LOAD = reload;
पूर्ण

/*
 *	Allow only one person to hold it खोलो
 */
अटल पूर्णांक watchकरोg_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	पूर्णांक ret;

	अगर (*CSR_SA110_CNTL & (1 << 13))
		वापस -EBUSY;

	अगर (test_and_set_bit(1, &समयr_alive))
		वापस -EBUSY;

	reload = soft_margin * (mem_fclk_21285 / 256);

	*CSR_TIMER4_CLR = 0;
	watchकरोg_ping();
	*CSR_TIMER4_CNTL = TIMER_CNTL_ENABLE | TIMER_CNTL_AUTORELOAD
		| TIMER_CNTL_DIV256;

#अगर_घोषित ONLY_TESTING
	ret = request_irq(IRQ_TIMER4, watchकरोg_fire, 0, "watchdog", शून्य);
	अगर (ret) अणु
		*CSR_TIMER4_CNTL = 0;
		clear_bit(1, &समयr_alive);
	पूर्ण
#अन्यथा
	/*
	 * Setting this bit is irreversible; once enabled, there is
	 * no way to disable the watchकरोg.
	 */
	*CSR_SA110_CNTL |= 1 << 13;

	ret = 0;
#पूर्ण_अगर
	stream_खोलो(inode, file);
	वापस ret;
पूर्ण

/*
 *	Shut off the समयr.
 *	Note: अगर we really have enabled the watchकरोg, there
 *	is no way to turn off.
 */
अटल पूर्णांक watchकरोg_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
#अगर_घोषित ONLY_TESTING
	मुक्त_irq(IRQ_TIMER4, शून्य);
	clear_bit(1, &समयr_alive);
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल sमाप_प्रकार watchकरोg_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *data,
			      माप_प्रकार len, loff_t *ppos)
अणु
	/*
	 *	Refresh the समयr.
	 */
	अगर (len)
		watchकरोg_ping();

	वापस len;
पूर्ण

अटल स्थिर काष्ठा watchकरोg_info ident = अणु
	.options	= WDIOF_SETTIMEOUT,
	.identity	= "Footbridge Watchdog",
पूर्ण;

अटल दीर्घ watchकरोg_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
			   अचिन्हित दीर्घ arg)
अणु
	पूर्णांक __user *पूर्णांक_arg = (पूर्णांक __user *)arg;
	पूर्णांक new_margin, ret = -ENOTTY;

	चयन (cmd) अणु
	हाल WDIOC_GETSUPPORT:
		ret = 0;
		अगर (copy_to_user((व्योम __user *)arg, &ident, माप(ident)))
			ret = -EFAULT;
		अवरोध;

	हाल WDIOC_GETSTATUS:
	हाल WDIOC_GETBOOTSTATUS:
		ret = put_user(0, पूर्णांक_arg);
		अवरोध;

	हाल WDIOC_KEEPALIVE:
		watchकरोg_ping();
		ret = 0;
		अवरोध;

	हाल WDIOC_SETTIMEOUT:
		ret = get_user(new_margin, पूर्णांक_arg);
		अगर (ret)
			अवरोध;

		/* Arbitrary, can't find the card's limits */
		अगर (new_margin < 0 || new_margin > 60) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		soft_margin = new_margin;
		reload = soft_margin * (mem_fclk_21285 / 256);
		watchकरोg_ping();
		fallthrough;
	हाल WDIOC_GETTIMEOUT:
		ret = put_user(soft_margin, पूर्णांक_arg);
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations watchकरोg_fops = अणु
	.owner		= THIS_MODULE,
	.llseek		= no_llseek,
	.ग_लिखो		= watchकरोg_ग_लिखो,
	.unlocked_ioctl	= watchकरोg_ioctl,
	.compat_ioctl	= compat_ptr_ioctl,
	.खोलो		= watchकरोg_खोलो,
	.release	= watchकरोg_release,
पूर्ण;

अटल काष्ठा miscdevice watchकरोg_miscdev = अणु
	.minor		= WATCHDOG_MINOR,
	.name		= "watchdog",
	.fops		= &watchकरोg_fops,
पूर्ण;

अटल पूर्णांक __init footbridge_watchकरोg_init(व्योम)
अणु
	पूर्णांक retval;

	अगर (machine_is_netwinder())
		वापस -ENODEV;

	retval = misc_रेजिस्टर(&watchकरोg_miscdev);
	अगर (retval < 0)
		वापस retval;

	pr_info("Footbridge Watchdog Timer: 0.01, timer margin: %d sec\n",
		soft_margin);

	अगर (machine_is_cats())
		pr_warn("Warning: Watchdog reset may not work on this machine\n");
	वापस 0;
पूर्ण

अटल व्योम __निकास footbridge_watchकरोg_निकास(व्योम)
अणु
	misc_deरेजिस्टर(&watchकरोg_miscdev);
पूर्ण

MODULE_AUTHOR("Phil Blundell <pb@nexus.co.uk>");
MODULE_DESCRIPTION("Footbridge watchdog driver");
MODULE_LICENSE("GPL");

module_param(soft_margin, पूर्णांक, 0);
MODULE_PARM_DESC(soft_margin, "Watchdog timeout in seconds");

module_init(footbridge_watchकरोg_init);
module_निकास(footbridge_watchकरोg_निकास);
