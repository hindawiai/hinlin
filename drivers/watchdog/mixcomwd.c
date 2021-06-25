<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * MixCom Watchकरोg: A Simple Hardware Watchकरोg Device
 * Based on Softकरोg driver by Alan Cox and PC Watchकरोg driver by Ken Hollis
 *
 * Author: Gergely Madarasz <gorgo@itc.hu>
 *
 * Copyright (c) 1999 ITConsult-Pro Co. <info@itc.hu>
 *
 * Version 0.1 (99/04/15):
 *		- first version
 *
 * Version 0.2 (99/06/16):
 *		- added kernel समयr watchकरोg ping after बंद
 *		  since the hardware करोes not support watchकरोg shutकरोwn
 *
 * Version 0.3 (99/06/21):
 *		- added WDIOC_GETSTATUS and WDIOC_GETSUPPORT ioctl calls
 *
 * Version 0.3.1 (99/06/22):
 *		- allow module removal जबतक पूर्णांकernal समयr is active,
 *		  prपूर्णांक warning about probable reset
 *
 * Version 0.4 (99/11/15):
 *		- support क्रम one more type board
 *
 * Version 0.5 (2001/12/14) Matt Domsch <Matt_Domsch@dell.com>
 *		- added nowayout module option to override
 *		  CONFIG_WATCHDOG_NOWAYOUT
 *
 * Version 0.6 (2002/04/12): Rob Radez <rob@osinvestor.com>
 *		- make mixcomwd_खोलोed अचिन्हित,
 *		  हटाओd lock_kernel/unlock_kernel from mixcomwd_release,
 *		  modअगरied ioctl a bit to conक्रमm to API
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#घोषणा VERSION "0.6"
#घोषणा WATCHDOG_NAME "mixcomwd"

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/types.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/ioport.h>
#समावेश <linux/watchकरोg.h>
#समावेश <linux/fs.h>
#समावेश <linux/reboot.h>
#समावेश <linux/init.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/समयr.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/पन.स>

/*
 * We have two types of cards that can be probed:
 * 1) The Mixcom cards: these cards can be found at addresses
 *    0x180, 0x280, 0x380 with an additional offset of 0xc10.
 *    (Or 0xd90, 0xe90, 0xf90).
 * 2) The FlashCOM cards: these cards can be set up at
 *    0x300 -> 0x378, in 0x8 jumps with an offset of 0x04.
 *    (Or 0x304 -> 0x37c in 0x8 jumps).
 *    Each card has it's own ID.
 */
#घोषणा MIXCOM_ID 0x11
#घोषणा FLASHCOM_ID 0x18
अटल काष्ठा अणु
	पूर्णांक ioport;
	पूर्णांक id;
पूर्ण mixcomwd_io_info[] = अणु
	/* The Mixcom cards */
	अणु0x0d90, MIXCOM_IDपूर्ण,
	अणु0x0e90, MIXCOM_IDपूर्ण,
	अणु0x0f90, MIXCOM_IDपूर्ण,
	/* The FlashCOM cards */
	अणु0x0304, FLASHCOM_IDपूर्ण,
	अणु0x030c, FLASHCOM_IDपूर्ण,
	अणु0x0314, FLASHCOM_IDपूर्ण,
	अणु0x031c, FLASHCOM_IDपूर्ण,
	अणु0x0324, FLASHCOM_IDपूर्ण,
	अणु0x032c, FLASHCOM_IDपूर्ण,
	अणु0x0334, FLASHCOM_IDपूर्ण,
	अणु0x033c, FLASHCOM_IDपूर्ण,
	अणु0x0344, FLASHCOM_IDपूर्ण,
	अणु0x034c, FLASHCOM_IDपूर्ण,
	अणु0x0354, FLASHCOM_IDपूर्ण,
	अणु0x035c, FLASHCOM_IDपूर्ण,
	अणु0x0364, FLASHCOM_IDपूर्ण,
	अणु0x036c, FLASHCOM_IDपूर्ण,
	अणु0x0374, FLASHCOM_IDपूर्ण,
	अणु0x037c, FLASHCOM_IDपूर्ण,
	/* The end of the list */
	अणु0x0000, 0पूर्ण,
पूर्ण;

अटल व्योम mixcomwd_समयrfun(काष्ठा समयr_list *unused);

अटल अचिन्हित दीर्घ mixcomwd_खोलोed; /* दीर्घ req'd क्रम setbit --RR */

अटल पूर्णांक watchकरोg_port;
अटल पूर्णांक mixcomwd_समयr_alive;
अटल DEFINE_TIMER(mixcomwd_समयr, mixcomwd_समयrfun);
अटल अक्षर expect_बंद;

अटल bool nowayout = WATCHDOG_NOWAYOUT;
module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout,
		"Watchdog cannot be stopped once started (default="
				__MODULE_STRING(WATCHDOG_NOWAYOUT) ")");

अटल व्योम mixcomwd_ping(व्योम)
अणु
	outb_p(55, watchकरोg_port);
	वापस;
पूर्ण

अटल व्योम mixcomwd_समयrfun(काष्ठा समयr_list *unused)
अणु
	mixcomwd_ping();
	mod_समयr(&mixcomwd_समयr, jअगरfies + 5 * HZ);
पूर्ण

/*
 *	Allow only one person to hold it खोलो
 */

अटल पूर्णांक mixcomwd_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अगर (test_and_set_bit(0, &mixcomwd_खोलोed))
		वापस -EBUSY;

	mixcomwd_ping();

	अगर (nowayout)
		/*
		 * fops_get() code via खोलो() has alपढ़ोy करोne
		 * a try_module_get() so it is safe to करो the
		 * __module_get().
		 */
		__module_get(THIS_MODULE);
	अन्यथा अणु
		अगर (mixcomwd_समयr_alive) अणु
			del_समयr(&mixcomwd_समयr);
			mixcomwd_समयr_alive = 0;
		पूर्ण
	पूर्ण
	वापस stream_खोलो(inode, file);
पूर्ण

अटल पूर्णांक mixcomwd_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अगर (expect_बंद == 42) अणु
		अगर (mixcomwd_समयr_alive) अणु
			pr_err("release called while internal timer alive\n");
			वापस -EBUSY;
		पूर्ण
		mixcomwd_समयr_alive = 1;
		mod_समयr(&mixcomwd_समयr, jअगरfies + 5 * HZ);
	पूर्ण अन्यथा
		pr_crit("WDT device closed unexpectedly.  WDT will not stop!\n");

	clear_bit(0, &mixcomwd_खोलोed);
	expect_बंद = 0;
	वापस 0;
पूर्ण


अटल sमाप_प्रकार mixcomwd_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *data,
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
		mixcomwd_ping();
	पूर्ण
	वापस len;
पूर्ण

अटल दीर्घ mixcomwd_ioctl(काष्ठा file *file,
				अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	व्योम __user *argp = (व्योम __user *)arg;
	पूर्णांक __user *p = argp;
	पूर्णांक status;
	अटल स्थिर काष्ठा watchकरोg_info ident = अणु
		.options = WDIOF_KEEPALIVEPING | WDIOF_MAGICCLOSE,
		.firmware_version = 1,
		.identity = "MixCOM watchdog",
	पूर्ण;

	चयन (cmd) अणु
	हाल WDIOC_GETSUPPORT:
		अगर (copy_to_user(argp, &ident, माप(ident)))
			वापस -EFAULT;
		अवरोध;
	हाल WDIOC_GETSTATUS:
		status = mixcomwd_खोलोed;
		अगर (!nowayout)
			status |= mixcomwd_समयr_alive;
		वापस put_user(status, p);
	हाल WDIOC_GETBOOTSTATUS:
		वापस put_user(0, p);
	हाल WDIOC_KEEPALIVE:
		mixcomwd_ping();
		अवरोध;
	शेष:
		वापस -ENOTTY;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations mixcomwd_fops = अणु
	.owner		= THIS_MODULE,
	.llseek		= no_llseek,
	.ग_लिखो		= mixcomwd_ग_लिखो,
	.unlocked_ioctl	= mixcomwd_ioctl,
	.compat_ioctl	= compat_ptr_ioctl,
	.खोलो		= mixcomwd_खोलो,
	.release	= mixcomwd_release,
पूर्ण;

अटल काष्ठा miscdevice mixcomwd_miscdev = अणु
	.minor	= WATCHDOG_MINOR,
	.name	= "watchdog",
	.fops	= &mixcomwd_fops,
पूर्ण;

अटल पूर्णांक __init checkcard(पूर्णांक port, पूर्णांक card_id)
अणु
	पूर्णांक id;

	अगर (!request_region(port, 1, "MixCOM watchdog"))
		वापस 0;

	id = inb_p(port);
	अगर (card_id == MIXCOM_ID)
		id &= 0x3f;

	अगर (id != card_id) अणु
		release_region(port, 1);
		वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

अटल पूर्णांक __init mixcomwd_init(व्योम)
अणु
	पूर्णांक i, ret, found = 0;

	क्रम (i = 0; !found && mixcomwd_io_info[i].ioport != 0; i++) अणु
		अगर (checkcard(mixcomwd_io_info[i].ioport,
			      mixcomwd_io_info[i].id)) अणु
			found = 1;
			watchकरोg_port = mixcomwd_io_info[i].ioport;
		पूर्ण
	पूर्ण

	अगर (!found) अणु
		pr_err("No card detected, or port not available\n");
		वापस -ENODEV;
	पूर्ण

	ret = misc_रेजिस्टर(&mixcomwd_miscdev);
	अगर (ret) अणु
		pr_err("cannot register miscdev on minor=%d (err=%d)\n",
		       WATCHDOG_MINOR, ret);
		जाओ error_misc_रेजिस्टर_watchकरोg;
	पूर्ण

	pr_info("MixCOM watchdog driver v%s, watchdog port at 0x%3x\n",
		VERSION, watchकरोg_port);

	वापस 0;

error_misc_रेजिस्टर_watchकरोg:
	release_region(watchकरोg_port, 1);
	watchकरोg_port = 0x0000;
	वापस ret;
पूर्ण

अटल व्योम __निकास mixcomwd_निकास(व्योम)
अणु
	अगर (!nowayout) अणु
		अगर (mixcomwd_समयr_alive) अणु
			pr_warn("I quit now, hardware will probably reboot!\n");
			del_समयr_sync(&mixcomwd_समयr);
			mixcomwd_समयr_alive = 0;
		पूर्ण
	पूर्ण
	misc_deरेजिस्टर(&mixcomwd_miscdev);
	release_region(watchकरोg_port, 1);
पूर्ण

module_init(mixcomwd_init);
module_निकास(mixcomwd_निकास);

MODULE_AUTHOR("Gergely Madarasz <gorgo@itc.hu>");
MODULE_DESCRIPTION("MixCom Watchdog driver");
MODULE_VERSION(VERSION);
MODULE_LICENSE("GPL");
