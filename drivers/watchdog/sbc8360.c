<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *	SBC8360 Watchकरोg driver
 *
 *	(c) Copyright 2005 Webcon, Inc.
 *
 *	Based on ib700wdt.c, which is based on advantechwdt.c which is based
 *	on acquirewdt.c which is based on wdt.c.
 *
 *	(c) Copyright 2001 Charles Howes <chowes@vsol.net>
 *
 *	Based on advantechwdt.c which is based on acquirewdt.c which
 *	is based on wdt.c.
 *
 *	(c) Copyright 2000-2001 Marek Michalkiewicz <marekm@linux.org.pl>
 *
 *	Based on acquirewdt.c which is based on wdt.c.
 *	Original copyright messages:
 *
 *	(c) Copyright 1996 Alan Cox <alan@lxorguk.ukuu.org.uk>,
 *						All Rights Reserved.
 *
 *	Neither Alan Cox nor CymruNet Ltd. admit liability nor provide
 *	warranty क्रम any of this software. This material is provided
 *	"AS-IS" and at no अक्षरge.
 *
 *	(c) Copyright 1995    Alan Cox <alan@lxorguk.ukuu.org.uk>
 *
 *	14-Dec-2001 Matt Domsch <Matt_Domsch@dell.com>
 *	     Added nowayout module option to override CONFIG_WATCHDOG_NOWAYOUT
 *	     Added समयout module option to override शेष
 *
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/watchकरोg.h>
#समावेश <linux/ioport.h>
#समावेश <linux/delay.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/fs.h>
#समावेश <linux/reboot.h>
#समावेश <linux/init.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/पन.स>
#समावेश <linux/uaccess.h>


अटल अचिन्हित दीर्घ sbc8360_is_खोलो;
अटल अक्षर expect_बंद;

/*
 *
 * Watchकरोg Timer Configuration
 *
 * The function of the watchकरोg समयr is to reset the प्रणाली स्वतःmatically
 * and is defined at I/O port 0120H and 0121H.  To enable the watchकरोg समयr
 * and allow the प्रणाली to reset, ग_लिखो appropriate values from the table
 * below to I/O port 0120H and 0121H.  To disable the समयr, ग_लिखो a zero
 * value to I/O port 0121H क्रम the प्रणाली to stop the watchकरोg function.
 *
 * The following describes how the समयr should be programmed (according to
 * the venकरोr करोcumentation)
 *
 * Enabling Watchकरोg:
 * MOV AX,000AH (enable, phase I)
 * MOV DX,0120H
 * OUT DX,AX
 * MOV AX,000BH (enable, phase II)
 * MOV DX,0120H
 * OUT DX,AX
 * MOV AX,000nH (set multiplier n, from 1-4)
 * MOV DX,0120H
 * OUT DX,AX
 * MOV AX,000mH (set base समयr m, from 0-F)
 * MOV DX,0121H
 * OUT DX,AX
 *
 * Reset समयr:
 * MOV AX,000mH (same as set base समयr, above)
 * MOV DX,0121H
 * OUT DX,AX
 *
 * Disabling Watchकरोg:
 * MOV AX,0000H (a zero value)
 * MOV DX,0120H
 * OUT DX,AX
 *
 * Watchकरोg समयout configuration values:
 *		N
 *	M |	1	2	3	4
 *	--|----------------------------------
 *	0 |	0.5s	5s	50s	100s
 *	1 |	1s	10s	100s	200s
 *	2 |	1.5s	15s	150s	300s
 *	3 |	2s	20s	200s	400s
 *	4 |	2.5s	25s	250s	500s
 *	5 |	3s	30s	300s	600s
 *	6 |	3.5s	35s	350s	700s
 *	7 |	4s	40s	400s	800s
 *	8 |	4.5s	45s	450s	900s
 *	9 |	5s	50s	500s	1000s
 *	A |	5.5s	55s	550s	1100s
 *	B |	6s	60s	600s	1200s
 *	C |	6.5s	65s	650s	1300s
 *	D |	7s	70s	700s	1400s
 *	E |	7.5s	75s	750s	1500s
 *	F |	8s	80s	800s	1600s
 *
 * Another way to say the same things is:
 *  For N=1, Timeout = (M+1) * 0.5s
 *  For N=2, Timeout = (M+1) * 5s
 *  For N=3, Timeout = (M+1) * 50s
 *  For N=4, Timeout = (M+1) * 100s
 *
 */

अटल पूर्णांक wd_बार[64][2] = अणु
	अणु0, 1पूर्ण,			/* 0  = 0.5s */
	अणु1, 1पूर्ण,			/* 1  = 1s   */
	अणु2, 1पूर्ण,			/* 2  = 1.5s */
	अणु3, 1पूर्ण,			/* 3  = 2s   */
	अणु4, 1पूर्ण,			/* 4  = 2.5s */
	अणु5, 1पूर्ण,			/* 5  = 3s   */
	अणु6, 1पूर्ण,			/* 6  = 3.5s */
	अणु7, 1पूर्ण,			/* 7  = 4s   */
	अणु8, 1पूर्ण,			/* 8  = 4.5s */
	अणु9, 1पूर्ण,			/* 9  = 5s   */
	अणु0xA, 1पूर्ण,		/* 10 = 5.5s */
	अणु0xB, 1पूर्ण,		/* 11 = 6s   */
	अणु0xC, 1पूर्ण,		/* 12 = 6.5s */
	अणु0xD, 1पूर्ण,		/* 13 = 7s   */
	अणु0xE, 1पूर्ण,		/* 14 = 7.5s */
	अणु0xF, 1पूर्ण,		/* 15 = 8s   */
	अणु0, 2पूर्ण,			/* 16 = 5s  */
	अणु1, 2पूर्ण,			/* 17 = 10s */
	अणु2, 2पूर्ण,			/* 18 = 15s */
	अणु3, 2पूर्ण,			/* 19 = 20s */
	अणु4, 2पूर्ण,			/* 20 = 25s */
	अणु5, 2पूर्ण,			/* 21 = 30s */
	अणु6, 2पूर्ण,			/* 22 = 35s */
	अणु7, 2पूर्ण,			/* 23 = 40s */
	अणु8, 2पूर्ण,			/* 24 = 45s */
	अणु9, 2पूर्ण,			/* 25 = 50s */
	अणु0xA, 2पूर्ण,		/* 26 = 55s */
	अणु0xB, 2पूर्ण,		/* 27 = 60s */
	अणु0xC, 2पूर्ण,		/* 28 = 65s */
	अणु0xD, 2पूर्ण,		/* 29 = 70s */
	अणु0xE, 2पूर्ण,		/* 30 = 75s */
	अणु0xF, 2पूर्ण,		/* 31 = 80s */
	अणु0, 3पूर्ण,			/* 32 = 50s  */
	अणु1, 3पूर्ण,			/* 33 = 100s */
	अणु2, 3पूर्ण,			/* 34 = 150s */
	अणु3, 3पूर्ण,			/* 35 = 200s */
	अणु4, 3पूर्ण,			/* 36 = 250s */
	अणु5, 3पूर्ण,			/* 37 = 300s */
	अणु6, 3पूर्ण,			/* 38 = 350s */
	अणु7, 3पूर्ण,			/* 39 = 400s */
	अणु8, 3पूर्ण,			/* 40 = 450s */
	अणु9, 3पूर्ण,			/* 41 = 500s */
	अणु0xA, 3पूर्ण,		/* 42 = 550s */
	अणु0xB, 3पूर्ण,		/* 43 = 600s */
	अणु0xC, 3पूर्ण,		/* 44 = 650s */
	अणु0xD, 3पूर्ण,		/* 45 = 700s */
	अणु0xE, 3पूर्ण,		/* 46 = 750s */
	अणु0xF, 3पूर्ण,		/* 47 = 800s */
	अणु0, 4पूर्ण,			/* 48 = 100s */
	अणु1, 4पूर्ण,			/* 49 = 200s */
	अणु2, 4पूर्ण,			/* 50 = 300s */
	अणु3, 4पूर्ण,			/* 51 = 400s */
	अणु4, 4पूर्ण,			/* 52 = 500s */
	अणु5, 4पूर्ण,			/* 53 = 600s */
	अणु6, 4पूर्ण,			/* 54 = 700s */
	अणु7, 4पूर्ण,			/* 55 = 800s */
	अणु8, 4पूर्ण,			/* 56 = 900s */
	अणु9, 4पूर्ण,			/* 57 = 1000s */
	अणु0xA, 4पूर्ण,		/* 58 = 1100s */
	अणु0xB, 4पूर्ण,		/* 59 = 1200s */
	अणु0xC, 4पूर्ण,		/* 60 = 1300s */
	अणु0xD, 4पूर्ण,		/* 61 = 1400s */
	अणु0xE, 4पूर्ण,		/* 62 = 1500s */
	अणु0xF, 4पूर्ण		/* 63 = 1600s */
पूर्ण;

#घोषणा SBC8360_ENABLE 0x120
#घोषणा SBC8360_BASETIME 0x121

अटल पूर्णांक समयout = 27;
अटल पूर्णांक wd_margin = 0xB;
अटल पूर्णांक wd_multiplier = 2;
अटल bool nowayout = WATCHDOG_NOWAYOUT;

module_param(समयout, पूर्णांक, 0);
MODULE_PARM_DESC(समयout, "Index into timeout table (0-63) (default=27 (60s))");
module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout,
		 "Watchdog cannot be stopped once started (default="
				__MODULE_STRING(WATCHDOG_NOWAYOUT) ")");

/*
 *	Kernel methods.
 */

/* Activate and pre-configure watchकरोg */
अटल व्योम sbc8360_activate(व्योम)
अणु
	/* Enable the watchकरोg */
	outb(0x0A, SBC8360_ENABLE);
	msleep_पूर्णांकerruptible(100);
	outb(0x0B, SBC8360_ENABLE);
	msleep_पूर्णांकerruptible(100);
	/* Set समयout multiplier */
	outb(wd_multiplier, SBC8360_ENABLE);
	msleep_पूर्णांकerruptible(100);
	/* Nothing happens until first sbc8360_ping() */
पूर्ण

/* Kernel pings watchकरोg */
अटल व्योम sbc8360_ping(व्योम)
अणु
	/* Write the base समयr रेजिस्टर */
	outb(wd_margin, SBC8360_BASETIME);
पूर्ण

/* stop watchकरोg */
अटल व्योम sbc8360_stop(व्योम)
अणु
	/* De-activate the watchकरोg */
	outb(0, SBC8360_ENABLE);
पूर्ण

/* Userspace pings kernel driver, or requests clean बंद */
अटल sमाप_प्रकार sbc8360_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
			     माप_प्रकार count, loff_t *ppos)
अणु
	अगर (count) अणु
		अगर (!nowayout) अणु
			माप_प्रकार i;

			/* In हाल it was set दीर्घ ago */
			expect_बंद = 0;

			क्रम (i = 0; i != count; i++) अणु
				अक्षर c;
				अगर (get_user(c, buf + i))
					वापस -EFAULT;
				अगर (c == 'V')
					expect_बंद = 42;
			पूर्ण
		पूर्ण
		sbc8360_ping();
	पूर्ण
	वापस count;
पूर्ण

अटल पूर्णांक sbc8360_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अगर (test_and_set_bit(0, &sbc8360_is_खोलो))
		वापस -EBUSY;
	अगर (nowayout)
		__module_get(THIS_MODULE);

	/* Activate and ping once to start the countकरोwn */
	sbc8360_activate();
	sbc8360_ping();
	वापस stream_खोलो(inode, file);
पूर्ण

अटल पूर्णांक sbc8360_बंद(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अगर (expect_बंद == 42)
		sbc8360_stop();
	अन्यथा
		pr_crit("SBC8360 device closed unexpectedly.  SBC8360 will not stop!\n");

	clear_bit(0, &sbc8360_is_खोलो);
	expect_बंद = 0;
	वापस 0;
पूर्ण

/*
 *	Notअगरier क्रम प्रणाली करोwn
 */

अटल पूर्णांक sbc8360_notअगरy_sys(काष्ठा notअगरier_block *this, अचिन्हित दीर्घ code,
			      व्योम *unused)
अणु
	अगर (code == SYS_DOWN || code == SYS_HALT)
		sbc8360_stop();	/* Disable the SBC8360 Watchकरोg */

	वापस NOTIFY_DONE;
पूर्ण

/*
 *	Kernel Interfaces
 */

अटल स्थिर काष्ठा file_operations sbc8360_fops = अणु
	.owner = THIS_MODULE,
	.llseek = no_llseek,
	.ग_लिखो = sbc8360_ग_लिखो,
	.खोलो = sbc8360_खोलो,
	.release = sbc8360_बंद,
पूर्ण;

अटल काष्ठा miscdevice sbc8360_miscdev = अणु
	.minor = WATCHDOG_MINOR,
	.name = "watchdog",
	.fops = &sbc8360_fops,
पूर्ण;

/*
 *	The SBC8360 needs to learn about soft shutकरोwns in order to
 *	turn the समयbomb रेजिस्टरs off.
 */

अटल काष्ठा notअगरier_block sbc8360_notअगरier = अणु
	.notअगरier_call = sbc8360_notअगरy_sys,
पूर्ण;

अटल पूर्णांक __init sbc8360_init(व्योम)
अणु
	पूर्णांक res;
	अचिन्हित दीर्घ पूर्णांक mseconds = 60000;

	अगर (समयout < 0 || समयout > 63) अणु
		pr_err("Invalid timeout index (must be 0-63)\n");
		res = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (!request_region(SBC8360_ENABLE, 1, "SBC8360")) अणु
		pr_err("ENABLE method I/O %X is not available\n",
		       SBC8360_ENABLE);
		res = -EIO;
		जाओ out;
	पूर्ण
	अगर (!request_region(SBC8360_BASETIME, 1, "SBC8360")) अणु
		pr_err("BASETIME method I/O %X is not available\n",
		       SBC8360_BASETIME);
		res = -EIO;
		जाओ out_nobaseसमयreg;
	पूर्ण

	res = रेजिस्टर_reboot_notअगरier(&sbc8360_notअगरier);
	अगर (res) अणु
		pr_err("Failed to register reboot notifier\n");
		जाओ out_noreboot;
	पूर्ण

	res = misc_रेजिस्टर(&sbc8360_miscdev);
	अगर (res) अणु
		pr_err("failed to register misc device\n");
		जाओ out_nomisc;
	पूर्ण

	wd_margin = wd_बार[समयout][0];
	wd_multiplier = wd_बार[समयout][1];

	अगर (wd_multiplier == 1)
		mseconds = (wd_margin + 1) * 500;
	अन्यथा अगर (wd_multiplier == 2)
		mseconds = (wd_margin + 1) * 5000;
	अन्यथा अगर (wd_multiplier == 3)
		mseconds = (wd_margin + 1) * 50000;
	अन्यथा अगर (wd_multiplier == 4)
		mseconds = (wd_margin + 1) * 100000;

	/* My kingकरोm क्रम the ability to prपूर्णांक "0.5 seconds" in the kernel! */
	pr_info("Timeout set at %ld ms\n", mseconds);

	वापस 0;

out_nomisc:
	unरेजिस्टर_reboot_notअगरier(&sbc8360_notअगरier);
out_noreboot:
	release_region(SBC8360_BASETIME, 1);
out_nobaseसमयreg:
	release_region(SBC8360_ENABLE, 1);
out:
	वापस res;
पूर्ण

अटल व्योम __निकास sbc8360_निकास(व्योम)
अणु
	misc_deरेजिस्टर(&sbc8360_miscdev);
	unरेजिस्टर_reboot_notअगरier(&sbc8360_notअगरier);
	release_region(SBC8360_ENABLE, 1);
	release_region(SBC8360_BASETIME, 1);
पूर्ण

module_init(sbc8360_init);
module_निकास(sbc8360_निकास);

MODULE_AUTHOR("Ian E. Morgan <imorgan@webcon.ca>");
MODULE_DESCRIPTION("SBC8360 watchdog driver");
MODULE_LICENSE("GPL");
MODULE_VERSION("1.01");

/* end of sbc8360.c */
