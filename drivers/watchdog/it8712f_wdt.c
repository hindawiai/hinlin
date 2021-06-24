<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	IT8712F "Smart Guardian" Watchकरोg support
 *
 *	Copyright (c) 2006-2007 Jorge Boncompte - DTI2 <jorge@dti2.net>
 *
 *	Based on info and code taken from:
 *
 *	drivers/अक्षर/watchकरोg/scx200_wdt.c
 *	drivers/hwmon/it87.c
 *	IT8712F EC-LPC I/O Preliminary Specअगरication 0.8.2
 *	IT8712F EC-LPC I/O Preliminary Specअगरication 0.9.3
 *
 *	The author(s) of this software shall not be held liable क्रम damages
 *	of any nature resulting due to the use of this software. This
 *	software is provided AS-IS with no warranties.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/watchकरोg.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/reboot.h>
#समावेश <linux/fs.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/पन.स>
#समावेश <linux/ioport.h>

#घोषणा NAME "it8712f_wdt"

MODULE_AUTHOR("Jorge Boncompte - DTI2 <jorge@dti2.net>");
MODULE_DESCRIPTION("IT8712F Watchdog Driver");
MODULE_LICENSE("GPL");

अटल पूर्णांक max_units = 255;
अटल पूर्णांक margin = 60;		/* in seconds */
module_param(margin, पूर्णांक, 0);
MODULE_PARM_DESC(margin, "Watchdog margin in seconds");

अटल bool nowayout = WATCHDOG_NOWAYOUT;
module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout, "Disable watchdog shutdown on close");

अटल अचिन्हित दीर्घ wdt_खोलो;
अटल अचिन्हित expect_बंद;
अटल अचिन्हित अक्षर revision;

/* Dog Food address - We use the game port address */
अटल अचिन्हित लघु address;

#घोषणा	REG		0x2e	/* The रेजिस्टर to पढ़ो/ग_लिखो */
#घोषणा	VAL		0x2f	/* The value to पढ़ो/ग_लिखो */

#घोषणा	LDN		0x07	/* Register: Logical device select */
#घोषणा	DEVID		0x20	/* Register: Device ID */
#घोषणा	DEVREV		0x22	/* Register: Device Revision */
#घोषणा ACT_REG		0x30	/* LDN Register: Activation */
#घोषणा BASE_REG	0x60	/* LDN Register: Base address */

#घोषणा IT8712F_DEVID	0x8712

#घोषणा LDN_GPIO	0x07	/* GPIO and Watch Dog Timer */
#घोषणा LDN_GAME	0x09	/* Game Port */

#घोषणा WDT_CONTROL	0x71	/* WDT Register: Control */
#घोषणा WDT_CONFIG	0x72	/* WDT Register: Configuration */
#घोषणा WDT_TIMEOUT	0x73	/* WDT Register: Timeout Value */

#घोषणा WDT_RESET_GAME	0x10	/* Reset समयr on पढ़ो or ग_लिखो to game port */
#घोषणा WDT_RESET_KBD	0x20	/* Reset समयr on keyboard पूर्णांकerrupt */
#घोषणा WDT_RESET_MOUSE	0x40	/* Reset समयr on mouse पूर्णांकerrupt */
#घोषणा WDT_RESET_CIR	0x80	/* Reset समयr on consumer IR पूर्णांकerrupt */

#घोषणा WDT_UNIT_SEC	0x80	/* If 0 in MINUTES */

#घोषणा WDT_OUT_PWROK	0x10	/* Pulse PWROK on समयout */
#घोषणा WDT_OUT_KRST	0x40	/* Pulse reset on समयout */

अटल पूर्णांक wdt_control_reg = WDT_RESET_GAME;
module_param(wdt_control_reg, पूर्णांक, 0);
MODULE_PARM_DESC(wdt_control_reg, "Value to write to watchdog control "
		"register. The default WDT_RESET_GAME resets the timer on "
		"game port reads that this driver generates. You can also "
		"use KBD, MOUSE or CIR if you have some external way to "
		"generate those interrupts.");

अटल पूर्णांक superio_inb(पूर्णांक reg)
अणु
	outb(reg, REG);
	वापस inb(VAL);
पूर्ण

अटल व्योम superio_outb(पूर्णांक val, पूर्णांक reg)
अणु
	outb(reg, REG);
	outb(val, VAL);
पूर्ण

अटल पूर्णांक superio_inw(पूर्णांक reg)
अणु
	पूर्णांक val;
	outb(reg++, REG);
	val = inb(VAL) << 8;
	outb(reg, REG);
	val |= inb(VAL);
	वापस val;
पूर्ण

अटल अंतरभूत व्योम superio_select(पूर्णांक ldn)
अणु
	outb(LDN, REG);
	outb(ldn, VAL);
पूर्ण

अटल अंतरभूत पूर्णांक superio_enter(व्योम)
अणु
	/*
	 * Try to reserve REG and REG + 1 क्रम exclusive access.
	 */
	अगर (!request_muxed_region(REG, 2, NAME))
		वापस -EBUSY;

	outb(0x87, REG);
	outb(0x01, REG);
	outb(0x55, REG);
	outb(0x55, REG);
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम superio_निकास(व्योम)
अणु
	outb(0x02, REG);
	outb(0x02, VAL);
	release_region(REG, 2);
पूर्ण

अटल अंतरभूत व्योम it8712f_wdt_ping(व्योम)
अणु
	अगर (wdt_control_reg & WDT_RESET_GAME)
		inb(address);
पूर्ण

अटल व्योम it8712f_wdt_update_margin(व्योम)
अणु
	पूर्णांक config = WDT_OUT_KRST | WDT_OUT_PWROK;
	पूर्णांक units = margin;

	/* Switch to minutes precision अगर the configured margin
	 * value करोes not fit within the रेजिस्टर width.
	 */
	अगर (units <= max_units) अणु
		config |= WDT_UNIT_SEC; /* अन्यथा UNIT is MINUTES */
		pr_info("timer margin %d seconds\n", units);
	पूर्ण अन्यथा अणु
		units /= 60;
		pr_info("timer margin %d minutes\n", units);
	पूर्ण
	superio_outb(config, WDT_CONFIG);

	अगर (revision >= 0x08)
		superio_outb(units >> 8, WDT_TIMEOUT + 1);
	superio_outb(units, WDT_TIMEOUT);
पूर्ण

अटल पूर्णांक it8712f_wdt_get_status(व्योम)
अणु
	अगर (superio_inb(WDT_CONTROL) & 0x01)
		वापस WDIOF_CARDRESET;
	अन्यथा
		वापस 0;
पूर्ण

अटल पूर्णांक it8712f_wdt_enable(व्योम)
अणु
	पूर्णांक ret = superio_enter();
	अगर (ret)
		वापस ret;

	pr_debug("enabling watchdog timer\n");
	superio_select(LDN_GPIO);

	superio_outb(wdt_control_reg, WDT_CONTROL);

	it8712f_wdt_update_margin();

	superio_निकास();

	it8712f_wdt_ping();

	वापस 0;
पूर्ण

अटल पूर्णांक it8712f_wdt_disable(व्योम)
अणु
	पूर्णांक ret = superio_enter();
	अगर (ret)
		वापस ret;

	pr_debug("disabling watchdog timer\n");
	superio_select(LDN_GPIO);

	superio_outb(0, WDT_CONFIG);
	superio_outb(0, WDT_CONTROL);
	अगर (revision >= 0x08)
		superio_outb(0, WDT_TIMEOUT + 1);
	superio_outb(0, WDT_TIMEOUT);

	superio_निकास();
	वापस 0;
पूर्ण

अटल पूर्णांक it8712f_wdt_notअगरy(काष्ठा notअगरier_block *this,
		    अचिन्हित दीर्घ code, व्योम *unused)
अणु
	अगर (code == SYS_HALT || code == SYS_POWER_OFF)
		अगर (!nowayout)
			it8712f_wdt_disable();

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block it8712f_wdt_notअगरier = अणु
	.notअगरier_call = it8712f_wdt_notअगरy,
पूर्ण;

अटल sमाप_प्रकार it8712f_wdt_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *data,
					माप_प्रकार len, loff_t *ppos)
अणु
	/* check क्रम a magic बंद अक्षरacter */
	अगर (len) अणु
		माप_प्रकार i;

		it8712f_wdt_ping();

		expect_बंद = 0;
		क्रम (i = 0; i < len; ++i) अणु
			अक्षर c;
			अगर (get_user(c, data + i))
				वापस -EFAULT;
			अगर (c == 'V')
				expect_बंद = 42;
		पूर्ण
	पूर्ण

	वापस len;
पूर्ण

अटल दीर्घ it8712f_wdt_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
							अचिन्हित दीर्घ arg)
अणु
	व्योम __user *argp = (व्योम __user *)arg;
	पूर्णांक __user *p = argp;
	अटल स्थिर काष्ठा watchकरोg_info ident = अणु
		.identity = "IT8712F Watchdog",
		.firmware_version = 1,
		.options = WDIOF_SETTIMEOUT | WDIOF_KEEPALIVEPING |
						WDIOF_MAGICCLOSE,
	पूर्ण;
	पूर्णांक value;
	पूर्णांक ret;

	चयन (cmd) अणु
	हाल WDIOC_GETSUPPORT:
		अगर (copy_to_user(argp, &ident, माप(ident)))
			वापस -EFAULT;
		वापस 0;
	हाल WDIOC_GETSTATUS:
		ret = superio_enter();
		अगर (ret)
			वापस ret;
		superio_select(LDN_GPIO);

		value = it8712f_wdt_get_status();

		superio_निकास();

		वापस put_user(value, p);
	हाल WDIOC_GETBOOTSTATUS:
		वापस put_user(0, p);
	हाल WDIOC_KEEPALIVE:
		it8712f_wdt_ping();
		वापस 0;
	हाल WDIOC_SETTIMEOUT:
		अगर (get_user(value, p))
			वापस -EFAULT;
		अगर (value < 1)
			वापस -EINVAL;
		अगर (value > (max_units * 60))
			वापस -EINVAL;
		margin = value;
		ret = superio_enter();
		अगर (ret)
			वापस ret;
		superio_select(LDN_GPIO);

		it8712f_wdt_update_margin();

		superio_निकास();
		it8712f_wdt_ping();
		fallthrough;
	हाल WDIOC_GETTIMEOUT:
		अगर (put_user(margin, p))
			वापस -EFAULT;
		वापस 0;
	शेष:
		वापस -ENOTTY;
	पूर्ण
पूर्ण

अटल पूर्णांक it8712f_wdt_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	पूर्णांक ret;
	/* only allow one at a समय */
	अगर (test_and_set_bit(0, &wdt_खोलो))
		वापस -EBUSY;

	ret = it8712f_wdt_enable();
	अगर (ret)
		वापस ret;
	वापस stream_खोलो(inode, file);
पूर्ण

अटल पूर्णांक it8712f_wdt_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अगर (expect_बंद != 42) अणु
		pr_warn("watchdog device closed unexpectedly, will not disable the watchdog timer\n");
	पूर्ण अन्यथा अगर (!nowayout) अणु
		अगर (it8712f_wdt_disable())
			pr_warn("Watchdog disable failed\n");
	पूर्ण
	expect_बंद = 0;
	clear_bit(0, &wdt_खोलो);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations it8712f_wdt_fops = अणु
	.owner = THIS_MODULE,
	.llseek = no_llseek,
	.ग_लिखो = it8712f_wdt_ग_लिखो,
	.unlocked_ioctl = it8712f_wdt_ioctl,
	.compat_ioctl = compat_ptr_ioctl,
	.खोलो = it8712f_wdt_खोलो,
	.release = it8712f_wdt_release,
पूर्ण;

अटल काष्ठा miscdevice it8712f_wdt_miscdev = अणु
	.minor = WATCHDOG_MINOR,
	.name = "watchdog",
	.fops = &it8712f_wdt_fops,
पूर्ण;

अटल पूर्णांक __init it8712f_wdt_find(अचिन्हित लघु *address)
अणु
	पूर्णांक err = -ENODEV;
	पूर्णांक chip_type;
	पूर्णांक ret = superio_enter();
	अगर (ret)
		वापस ret;

	chip_type = superio_inw(DEVID);
	अगर (chip_type != IT8712F_DEVID)
		जाओ निकास;

	superio_select(LDN_GAME);
	superio_outb(1, ACT_REG);
	अगर (!(superio_inb(ACT_REG) & 0x01)) अणु
		pr_err("Device not activated, skipping\n");
		जाओ निकास;
	पूर्ण

	*address = superio_inw(BASE_REG);
	अगर (*address == 0) अणु
		pr_err("Base address not set, skipping\n");
		जाओ निकास;
	पूर्ण

	err = 0;
	revision = superio_inb(DEVREV) & 0x0f;

	/* Later revisions have 16-bit values per datasheet 0.9.1 */
	अगर (revision >= 0x08)
		max_units = 65535;

	अगर (margin > (max_units * 60))
		margin = (max_units * 60);

	pr_info("Found IT%04xF chip revision %d - using DogFood address 0x%x\n",
		chip_type, revision, *address);

निकास:
	superio_निकास();
	वापस err;
पूर्ण

अटल पूर्णांक __init it8712f_wdt_init(व्योम)
अणु
	पूर्णांक err = 0;

	अगर (it8712f_wdt_find(&address))
		वापस -ENODEV;

	अगर (!request_region(address, 1, "IT8712F Watchdog")) अणु
		pr_warn("watchdog I/O region busy\n");
		वापस -EBUSY;
	पूर्ण

	err = it8712f_wdt_disable();
	अगर (err) अणु
		pr_err("unable to disable watchdog timer\n");
		जाओ out;
	पूर्ण

	err = रेजिस्टर_reboot_notअगरier(&it8712f_wdt_notअगरier);
	अगर (err) अणु
		pr_err("unable to register reboot notifier\n");
		जाओ out;
	पूर्ण

	err = misc_रेजिस्टर(&it8712f_wdt_miscdev);
	अगर (err) अणु
		pr_err("cannot register miscdev on minor=%d (err=%d)\n",
		       WATCHDOG_MINOR, err);
		जाओ reboot_out;
	पूर्ण

	वापस 0;


reboot_out:
	unरेजिस्टर_reboot_notअगरier(&it8712f_wdt_notअगरier);
out:
	release_region(address, 1);
	वापस err;
पूर्ण

अटल व्योम __निकास it8712f_wdt_निकास(व्योम)
अणु
	misc_deरेजिस्टर(&it8712f_wdt_miscdev);
	unरेजिस्टर_reboot_notअगरier(&it8712f_wdt_notअगरier);
	release_region(address, 1);
पूर्ण

module_init(it8712f_wdt_init);
module_निकास(it8712f_wdt_निकास);
