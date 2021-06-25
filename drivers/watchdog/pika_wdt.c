<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * PIKA FPGA based Watchकरोg Timer
 *
 * Copyright (c) 2008 PIKA Technologies
 *   Sean MacLennan <smaclennan@pikatech.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/fs.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/watchकरोg.h>
#समावेश <linux/reboot.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/समयr.h>
#समावेश <linux/bitops.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/पन.स>
#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>

#घोषणा DRV_NAME "PIKA-WDT"

/* Hardware समयout in seconds */
#घोषणा WDT_HW_TIMEOUT 2

/* Timer heartbeat (500ms) */
#घोषणा WDT_TIMEOUT	(HZ/2)

/* User land समयout */
#घोषणा WDT_HEARTBEAT 15
अटल पूर्णांक heartbeat = WDT_HEARTBEAT;
module_param(heartbeat, पूर्णांक, 0);
MODULE_PARM_DESC(heartbeat, "Watchdog heartbeats in seconds. "
	"(default = " __MODULE_STRING(WDT_HEARTBEAT) ")");

अटल bool nowayout = WATCHDOG_NOWAYOUT;
module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout, "Watchdog cannot be stopped once started "
	"(default=" __MODULE_STRING(WATCHDOG_NOWAYOUT) ")");

अटल काष्ठा अणु
	व्योम __iomem *fpga;
	अचिन्हित दीर्घ next_heartbeat;	/* the next_heartbeat क्रम the समयr */
	अचिन्हित दीर्घ खोलो;
	अक्षर expect_बंद;
	पूर्णांक bootstatus;
	काष्ठा समयr_list समयr;	/* The समयr that pings the watchकरोg */
पूर्ण pikawdt_निजी;

अटल काष्ठा watchकरोg_info ident __ro_after_init = अणु
	.identity	= DRV_NAME,
	.options	= WDIOF_CARDRESET |
			  WDIOF_SETTIMEOUT |
			  WDIOF_KEEPALIVEPING |
			  WDIOF_MAGICCLOSE,
पूर्ण;

/*
 * Reload the watchकरोg समयr.  (ie, pat the watchकरोg)
 */
अटल अंतरभूत व्योम pikawdt_reset(व्योम)
अणु
	/* -- FPGA: Reset Control Register (32bit R/W) (Offset: 0x14) --
	 * Bit 7,    WTCHDG_EN: When set to 1, the watchकरोg समयr is enabled.
	 *           Once enabled, it cannot be disabled. The watchकरोg can be
	 *           kicked by perक्रमming any ग_लिखो access to the reset
	 *           control रेजिस्टर (this रेजिस्टर).
	 * Bit 8-11, WTCHDG_TIMEOUT_SEC: Sets the watchकरोg समयout value in
	 *           seconds. Valid ranges are 1 to 15 seconds. The value can
	 *           be modअगरied dynamically.
	 */
	अचिन्हित reset = in_be32(pikawdt_निजी.fpga + 0x14);
	/* enable with max समयout - 15 seconds */
	reset |= (1 << 7) + (WDT_HW_TIMEOUT << 8);
	out_be32(pikawdt_निजी.fpga + 0x14, reset);
पूर्ण

/*
 * Timer tick
 */
अटल व्योम pikawdt_ping(काष्ठा समयr_list *unused)
अणु
	अगर (समय_beक्रमe(jअगरfies, pikawdt_निजी.next_heartbeat) ||
			(!nowayout && !pikawdt_निजी.खोलो)) अणु
		pikawdt_reset();
		mod_समयr(&pikawdt_निजी.समयr, jअगरfies + WDT_TIMEOUT);
	पूर्ण अन्यथा
		pr_crit("I will reset your machine !\n");
पूर्ण


अटल व्योम pikawdt_keepalive(व्योम)
अणु
	pikawdt_निजी.next_heartbeat = jअगरfies + heartbeat * HZ;
पूर्ण

अटल व्योम pikawdt_start(व्योम)
अणु
	pikawdt_keepalive();
	mod_समयr(&pikawdt_निजी.समयr, jअगरfies + WDT_TIMEOUT);
पूर्ण

/*
 * Watchकरोg device is खोलोed, and watchकरोg starts running.
 */
अटल पूर्णांक pikawdt_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	/* /dev/watchकरोg can only be खोलोed once */
	अगर (test_and_set_bit(0, &pikawdt_निजी.खोलो))
		वापस -EBUSY;

	pikawdt_start();

	वापस stream_खोलो(inode, file);
पूर्ण

/*
 * Close the watchकरोg device.
 */
अटल पूर्णांक pikawdt_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	/* stop पूर्णांकernal ping */
	अगर (!pikawdt_निजी.expect_बंद)
		del_समयr(&pikawdt_निजी.समयr);

	clear_bit(0, &pikawdt_निजी.खोलो);
	pikawdt_निजी.expect_बंद = 0;
	वापस 0;
पूर्ण

/*
 * Pat the watchकरोg whenever device is written to.
 */
अटल sमाप_प्रकार pikawdt_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *data,
			     माप_प्रकार len, loff_t *ppos)
अणु
	अगर (!len)
		वापस 0;

	/* Scan क्रम magic अक्षरacter */
	अगर (!nowayout) अणु
		माप_प्रकार i;

		pikawdt_निजी.expect_बंद = 0;

		क्रम (i = 0; i < len; i++) अणु
			अक्षर c;
			अगर (get_user(c, data + i))
				वापस -EFAULT;
			अगर (c == 'V') अणु
				pikawdt_निजी.expect_बंद = 42;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	pikawdt_keepalive();

	वापस len;
पूर्ण

/*
 * Handle commands from user-space.
 */
अटल दीर्घ pikawdt_ioctl(काष्ठा file *file,
		अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	व्योम __user *argp = (व्योम __user *)arg;
	पूर्णांक __user *p = argp;
	पूर्णांक new_value;

	चयन (cmd) अणु
	हाल WDIOC_GETSUPPORT:
		वापस copy_to_user(argp, &ident, माप(ident)) ? -EFAULT : 0;

	हाल WDIOC_GETSTATUS:
		वापस put_user(0, p);

	हाल WDIOC_GETBOOTSTATUS:
		वापस put_user(pikawdt_निजी.bootstatus, p);

	हाल WDIOC_KEEPALIVE:
		pikawdt_keepalive();
		वापस 0;

	हाल WDIOC_SETTIMEOUT:
		अगर (get_user(new_value, p))
			वापस -EFAULT;

		heartbeat = new_value;
		pikawdt_keepalive();

		वापस put_user(new_value, p);  /* वापस current value */

	हाल WDIOC_GETTIMEOUT:
		वापस put_user(heartbeat, p);
	पूर्ण
	वापस -ENOTTY;
पूर्ण


अटल स्थिर काष्ठा file_operations pikawdt_fops = अणु
	.owner		= THIS_MODULE,
	.llseek		= no_llseek,
	.खोलो		= pikawdt_खोलो,
	.release	= pikawdt_release,
	.ग_लिखो		= pikawdt_ग_लिखो,
	.unlocked_ioctl	= pikawdt_ioctl,
	.compat_ioctl	= compat_ptr_ioctl,
पूर्ण;

अटल काष्ठा miscdevice pikawdt_miscdev = अणु
	.minor	= WATCHDOG_MINOR,
	.name	= "watchdog",
	.fops	= &pikawdt_fops,
पूर्ण;

अटल पूर्णांक __init pikawdt_init(व्योम)
अणु
	काष्ठा device_node *np;
	व्योम __iomem *fpga;
	u32 post1;
	पूर्णांक ret;

	np = of_find_compatible_node(शून्य, शून्य, "pika,fpga");
	अगर (np == शून्य) अणु
		pr_err("Unable to find fpga\n");
		वापस -ENOENT;
	पूर्ण

	pikawdt_निजी.fpga = of_iomap(np, 0);
	of_node_put(np);
	अगर (pikawdt_निजी.fpga == शून्य) अणु
		pr_err("Unable to map fpga\n");
		वापस -ENOMEM;
	पूर्ण

	ident.firmware_version = in_be32(pikawdt_निजी.fpga + 0x1c) & 0xffff;

	/* POST inक्रमmation is in the sd area. */
	np = of_find_compatible_node(शून्य, शून्य, "pika,fpga-sd");
	अगर (np == शून्य) अणु
		pr_err("Unable to find fpga-sd\n");
		ret = -ENOENT;
		जाओ out;
	पूर्ण

	fpga = of_iomap(np, 0);
	of_node_put(np);
	अगर (fpga == शून्य) अणु
		pr_err("Unable to map fpga-sd\n");
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	/* -- FPGA: POST Test Results Register 1 (32bit R/W) (Offset: 0x4040) --
	 * Bit 31,   WDOG: Set to 1 when the last reset was caused by a watchकरोg
	 *           समयout.
	 */
	post1 = in_be32(fpga + 0x40);
	अगर (post1 & 0x80000000)
		pikawdt_निजी.bootstatus = WDIOF_CARDRESET;

	iounmap(fpga);

	समयr_setup(&pikawdt_निजी.समयr, pikawdt_ping, 0);

	ret = misc_रेजिस्टर(&pikawdt_miscdev);
	अगर (ret) अणु
		pr_err("Unable to register miscdev\n");
		जाओ out;
	पूर्ण

	pr_info("initialized. heartbeat=%d sec (nowayout=%d)\n",
		heartbeat, nowayout);
	वापस 0;

out:
	iounmap(pikawdt_निजी.fpga);
	वापस ret;
पूर्ण

अटल व्योम __निकास pikawdt_निकास(व्योम)
अणु
	misc_deरेजिस्टर(&pikawdt_miscdev);

	iounmap(pikawdt_निजी.fpga);
पूर्ण

module_init(pikawdt_init);
module_निकास(pikawdt_निकास);

MODULE_AUTHOR("Sean MacLennan <smaclennan@pikatech.com>");
MODULE_DESCRIPTION("PIKA FPGA based Watchdog Timer");
MODULE_LICENSE("GPL");
