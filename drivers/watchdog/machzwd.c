<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  MachZ ZF-Logic Watchकरोg Timer driver क्रम Linux
 *
 *  The author करोes NOT admit liability nor provide warranty क्रम
 *  any of this software. This material is provided "AS-IS" in
 *  the hope that it may be useful क्रम others.
 *
 *  Author: Fernanकरो Fuganti <fuganti@conectiva.com.br>
 *
 *  Based on sbc60xxwdt.c by Jakob Oestergaard
 *
 *  We have two समयrs (wd#1, wd#2) driven by a 32 KHz घड़ी with the
 *  following periods:
 *      wd#1 - 2 seconds;
 *      wd#2 - 7.2 ms;
 *  After the expiration of wd#1, it can generate a NMI, SCI, SMI, or
 *  a प्रणाली RESET and it starts wd#2 that unconditionally will RESET
 *  the प्रणाली when the counter reaches zero.
 *
 *  14-Dec-2001 Matt Domsch <Matt_Domsch@dell.com>
 *      Added nowayout module option to override CONFIG_WATCHDOG_NOWAYOUT
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/types.h>
#समावेश <linux/समयr.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/watchकरोg.h>
#समावेश <linux/fs.h>
#समावेश <linux/ioport.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/reboot.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/uaccess.h>


/* ports */
#घोषणा ZF_IOBASE	0x218
#घोषणा INDEX		0x218
#घोषणा DATA_B		0x219
#घोषणा DATA_W		0x21A
#घोषणा DATA_D		0x21A

/* indexes */			/* size */
#घोषणा ZFL_VERSION	0x02	/* 16   */
#घोषणा CONTROL		0x10	/* 16   */
#घोषणा STATUS		0x12	/* 8    */
#घोषणा COUNTER_1	0x0C	/* 16   */
#घोषणा COUNTER_2	0x0E	/* 8    */
#घोषणा PULSE_LEN	0x0F	/* 8    */

/* controls */
#घोषणा ENABLE_WD1	0x0001
#घोषणा ENABLE_WD2	0x0002
#घोषणा RESET_WD1	0x0010
#घोषणा RESET_WD2	0x0020
#घोषणा GEN_SCI		0x0100
#घोषणा GEN_NMI		0x0200
#घोषणा GEN_SMI		0x0400
#घोषणा GEN_RESET	0x0800


/* utilities */

#घोषणा WD1	0
#घोषणा WD2	1

#घोषणा zf_ग_लिखोw(port, data)  अणु outb(port, INDEX); outw(data, DATA_W); पूर्ण
#घोषणा zf_ग_लिखोb(port, data)  अणु outb(port, INDEX); outb(data, DATA_B); पूर्ण
#घोषणा zf_get_ZFL_version()   zf_पढ़ोw(ZFL_VERSION)


अटल अचिन्हित लघु zf_पढ़ोw(अचिन्हित अक्षर port)
अणु
	outb(port, INDEX);
	वापस inw(DATA_W);
पूर्ण


MODULE_AUTHOR("Fernando Fuganti <fuganti@conectiva.com.br>");
MODULE_DESCRIPTION("MachZ ZF-Logic Watchdog driver");
MODULE_LICENSE("GPL");

अटल bool nowayout = WATCHDOG_NOWAYOUT;
module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout,
		"Watchdog cannot be stopped once started (default="
				__MODULE_STRING(WATCHDOG_NOWAYOUT) ")");

#घोषणा PFX "machzwd"

अटल स्थिर काष्ठा watchकरोg_info zf_info = अणु
	.options		= WDIOF_KEEPALIVEPING | WDIOF_MAGICCLOSE,
	.firmware_version	= 1,
	.identity		= "ZF-Logic watchdog",
पूर्ण;


/*
 * action refers to action taken when watchकरोg resets
 * 0 = GEN_RESET
 * 1 = GEN_SMI
 * 2 = GEN_NMI
 * 3 = GEN_SCI
 * शेषs to GEN_RESET (0)
 */
अटल पूर्णांक action;
module_param(action, पूर्णांक, 0);
MODULE_PARM_DESC(action, "after watchdog resets, generate: "
				"0 = RESET(*)  1 = SMI  2 = NMI  3 = SCI");

अटल व्योम zf_ping(काष्ठा समयr_list *unused);

अटल पूर्णांक zf_action = GEN_RESET;
अटल अचिन्हित दीर्घ zf_is_खोलो;
अटल अक्षर zf_expect_बंद;
अटल DEFINE_SPINLOCK(zf_port_lock);
अटल DEFINE_TIMER(zf_समयr, zf_ping);
अटल अचिन्हित दीर्घ next_heartbeat;


/* समयout क्रम user land heart beat (10 seconds) */
#घोषणा ZF_USER_TIMEO (HZ*10)

/* समयout क्रम hardware watchकरोg (~500ms) */
#घोषणा ZF_HW_TIMEO (HZ/2)

/* number of ticks on WD#1 (driven by a 32KHz घड़ी, 2s) */
#घोषणा ZF_CTIMEOUT 0xffff

#अगर_अघोषित ZF_DEBUG
#घोषणा dprपूर्णांकk(क्रमmat, args...)
#अन्यथा
#घोषणा dprपूर्णांकk(क्रमmat, args...)					\
	pr_debug(":%s:%d: " क्रमmat, __func__, __LINE__ , ## args)
#पूर्ण_अगर


अटल अंतरभूत व्योम zf_set_status(अचिन्हित अक्षर new)
अणु
	zf_ग_लिखोb(STATUS, new);
पूर्ण


/* CONTROL रेजिस्टर functions */

अटल अंतरभूत अचिन्हित लघु zf_get_control(व्योम)
अणु
	वापस zf_पढ़ोw(CONTROL);
पूर्ण

अटल अंतरभूत व्योम zf_set_control(अचिन्हित लघु new)
अणु
	zf_ग_लिखोw(CONTROL, new);
पूर्ण


/* WD#? counter functions */
/*
 *	Just set counter value
 */

अटल अंतरभूत व्योम zf_set_समयr(अचिन्हित लघु new, अचिन्हित अक्षर n)
अणु
	चयन (n) अणु
	हाल WD1:
		zf_ग_लिखोw(COUNTER_1, new);
		fallthrough;
	हाल WD2:
		zf_ग_लिखोb(COUNTER_2, new > 0xff ? 0xff : new);
	शेष:
		वापस;
	पूर्ण
पूर्ण

/*
 * stop hardware समयr
 */
अटल व्योम zf_समयr_off(व्योम)
अणु
	अचिन्हित पूर्णांक ctrl_reg = 0;
	अचिन्हित दीर्घ flags;

	/* stop पूर्णांकernal ping */
	del_समयr_sync(&zf_समयr);

	spin_lock_irqsave(&zf_port_lock, flags);
	/* stop watchकरोg समयr */
	ctrl_reg = zf_get_control();
	ctrl_reg |= (ENABLE_WD1|ENABLE_WD2);	/* disable wd1 and wd2 */
	ctrl_reg &= ~(ENABLE_WD1|ENABLE_WD2);
	zf_set_control(ctrl_reg);
	spin_unlock_irqrestore(&zf_port_lock, flags);

	pr_info("Watchdog timer is now disabled\n");
पूर्ण


/*
 * start hardware समयr
 */
अटल व्योम zf_समयr_on(व्योम)
अणु
	अचिन्हित पूर्णांक ctrl_reg = 0;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&zf_port_lock, flags);

	zf_ग_लिखोb(PULSE_LEN, 0xff);

	zf_set_समयr(ZF_CTIMEOUT, WD1);

	/* user land ping */
	next_heartbeat = jअगरfies + ZF_USER_TIMEO;

	/* start the समयr क्रम पूर्णांकernal ping */
	mod_समयr(&zf_समयr, jअगरfies + ZF_HW_TIMEO);

	/* start watchकरोg समयr */
	ctrl_reg = zf_get_control();
	ctrl_reg |= (ENABLE_WD1|zf_action);
	zf_set_control(ctrl_reg);
	spin_unlock_irqrestore(&zf_port_lock, flags);

	pr_info("Watchdog timer is now enabled\n");
पूर्ण


अटल व्योम zf_ping(काष्ठा समयr_list *unused)
अणु
	अचिन्हित पूर्णांक ctrl_reg = 0;
	अचिन्हित दीर्घ flags;

	zf_ग_लिखोb(COUNTER_2, 0xff);

	अगर (समय_beक्रमe(jअगरfies, next_heartbeat)) अणु
		dprपूर्णांकk("time_before: %ld\n", next_heartbeat - jअगरfies);
		/*
		 * reset event is activated by transition from 0 to 1 on
		 * RESET_WD1 bit and we assume that it is alपढ़ोy zero...
		 */

		spin_lock_irqsave(&zf_port_lock, flags);
		ctrl_reg = zf_get_control();
		ctrl_reg |= RESET_WD1;
		zf_set_control(ctrl_reg);

		/* ...and nothing changes until here */
		ctrl_reg &= ~(RESET_WD1);
		zf_set_control(ctrl_reg);
		spin_unlock_irqrestore(&zf_port_lock, flags);

		mod_समयr(&zf_समयr, jअगरfies + ZF_HW_TIMEO);
	पूर्ण अन्यथा
		pr_crit("I will reset your machine\n");
पूर्ण

अटल sमाप_प्रकार zf_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf, माप_प्रकार count,
								loff_t *ppos)
अणु
	/* See अगर we got the magic अक्षरacter */
	अगर (count) अणु
		/*
		 * no need to check क्रम बंद confirmation
		 * no way to disable watchकरोg ;)
		 */
		अगर (!nowayout) अणु
			माप_प्रकार ofs;
			/*
			 * note: just in हाल someone wrote the magic अक्षरacter
			 * five months ago...
			 */
			zf_expect_बंद = 0;

			/* now scan */
			क्रम (ofs = 0; ofs != count; ofs++) अणु
				अक्षर c;
				अगर (get_user(c, buf + ofs))
					वापस -EFAULT;
				अगर (c == 'V') अणु
					zf_expect_बंद = 42;
					dprपूर्णांकk("zf_expect_close = 42\n");
				पूर्ण
			पूर्ण
		पूर्ण

		/*
		 * Well, anyhow someone wrote to us,
		 * we should वापस that favour
		 */
		next_heartbeat = jअगरfies + ZF_USER_TIMEO;
		dprपूर्णांकk("user ping at %ld\n", jअगरfies);
	पूर्ण
	वापस count;
पूर्ण

अटल दीर्घ zf_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	व्योम __user *argp = (व्योम __user *)arg;
	पूर्णांक __user *p = argp;
	चयन (cmd) अणु
	हाल WDIOC_GETSUPPORT:
		अगर (copy_to_user(argp, &zf_info, माप(zf_info)))
			वापस -EFAULT;
		अवरोध;
	हाल WDIOC_GETSTATUS:
	हाल WDIOC_GETBOOTSTATUS:
		वापस put_user(0, p);
	हाल WDIOC_KEEPALIVE:
		zf_ping(शून्य);
		अवरोध;
	शेष:
		वापस -ENOTTY;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक zf_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अगर (test_and_set_bit(0, &zf_is_खोलो))
		वापस -EBUSY;
	अगर (nowayout)
		__module_get(THIS_MODULE);
	zf_समयr_on();
	वापस stream_खोलो(inode, file);
पूर्ण

अटल पूर्णांक zf_बंद(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अगर (zf_expect_बंद == 42)
		zf_समयr_off();
	अन्यथा अणु
		del_समयr(&zf_समयr);
		pr_err("device file closed unexpectedly. Will not stop the WDT!\n");
	पूर्ण
	clear_bit(0, &zf_is_खोलो);
	zf_expect_बंद = 0;
	वापस 0;
पूर्ण

/*
 * Notअगरier क्रम प्रणाली करोwn
 */

अटल पूर्णांक zf_notअगरy_sys(काष्ठा notअगरier_block *this, अचिन्हित दीर्घ code,
								व्योम *unused)
अणु
	अगर (code == SYS_DOWN || code == SYS_HALT)
		zf_समयr_off();
	वापस NOTIFY_DONE;
पूर्ण

अटल स्थिर काष्ठा file_operations zf_fops = अणु
	.owner		= THIS_MODULE,
	.llseek		= no_llseek,
	.ग_लिखो		= zf_ग_लिखो,
	.unlocked_ioctl = zf_ioctl,
	.compat_ioctl	= compat_ptr_ioctl,
	.खोलो		= zf_खोलो,
	.release	= zf_बंद,
पूर्ण;

अटल काष्ठा miscdevice zf_miscdev = अणु
	.minor = WATCHDOG_MINOR,
	.name = "watchdog",
	.fops = &zf_fops,
पूर्ण;


/*
 * The device needs to learn about soft shutकरोwns in order to
 * turn the समयbomb रेजिस्टरs off.
 */
अटल काष्ठा notअगरier_block zf_notअगरier = अणु
	.notअगरier_call = zf_notअगरy_sys,
पूर्ण;

अटल व्योम __init zf_show_action(पूर्णांक act)
अणु
	अटल स्थिर अक्षर * स्थिर str[] = अणु "RESET", "SMI", "NMI", "SCI" पूर्ण;

	pr_info("Watchdog using action = %s\n", str[act]);
पूर्ण

अटल पूर्णांक __init zf_init(व्योम)
अणु
	पूर्णांक ret;

	pr_info("MachZ ZF-Logic Watchdog driver initializing\n");

	ret = zf_get_ZFL_version();
	अगर (!ret || ret == 0xffff) अणु
		pr_warn("no ZF-Logic found\n");
		वापस -ENODEV;
	पूर्ण

	अगर (action <= 3 && action >= 0)
		zf_action = zf_action >> action;
	अन्यथा
		action = 0;

	zf_show_action(action);

	अगर (!request_region(ZF_IOBASE, 3, "MachZ ZFL WDT")) अणु
		pr_err("cannot reserve I/O ports at %d\n", ZF_IOBASE);
		ret = -EBUSY;
		जाओ no_region;
	पूर्ण

	ret = रेजिस्टर_reboot_notअगरier(&zf_notअगरier);
	अगर (ret) अणु
		pr_err("can't register reboot notifier (err=%d)\n", ret);
		जाओ no_reboot;
	पूर्ण

	ret = misc_रेजिस्टर(&zf_miscdev);
	अगर (ret) अणु
		pr_err("can't misc_register on minor=%d\n", WATCHDOG_MINOR);
		जाओ no_misc;
	पूर्ण

	zf_set_status(0);
	zf_set_control(0);

	वापस 0;

no_misc:
	unरेजिस्टर_reboot_notअगरier(&zf_notअगरier);
no_reboot:
	release_region(ZF_IOBASE, 3);
no_region:
	वापस ret;
पूर्ण


अटल व्योम __निकास zf_निकास(व्योम)
अणु
	zf_समयr_off();

	misc_deरेजिस्टर(&zf_miscdev);
	unरेजिस्टर_reboot_notअगरier(&zf_notअगरier);
	release_region(ZF_IOBASE, 3);
पूर्ण

module_init(zf_init);
module_निकास(zf_निकास);
