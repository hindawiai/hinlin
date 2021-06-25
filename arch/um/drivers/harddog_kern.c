<शैली गुरु>
/* UML hardware watchकरोg, shamelessly stolen from:
 *
 *	SoftDog	0.05:	A Software Watchकरोg Device
 *
 *	(c) Copyright 1996 Alan Cox <alan@redhat.com>, All Rights Reserved.
 *				http://www.redhat.com
 *
 *	This program is मुक्त software; you can redistribute it and/or
 *	modअगरy it under the terms of the GNU General Public License
 *	as published by the Free Software Foundation; either version
 *	2 of the License, or (at your option) any later version.
 *
 *	Neither Alan Cox nor CymruNet Ltd. admit liability nor provide
 *	warranty क्रम any of this software. This material is provided
 *	"AS-IS" and at no अक्षरge.
 *
 *	(c) Copyright 1995    Alan Cox <alan@lxorguk.ukuu.org.uk>
 *
 *	Software only watchकरोg driver. Unlike its big brother the WDT501P
 *	driver this won't always recover a failed machine.
 *
 *  03/96: Angelo Haritsis <ah@करोc.ic.ac.uk> :
 *	Modularised.
 *	Added soft_margin; use upon insmod to change the समयr delay.
 *	NB: uses same minor as wdt (WATCHDOG_MINOR); we could use separate
 *	    minors.
 *
 *  19980911 Alan Cox
 *	Made SMP safe क्रम 2.3.x
 *
 *  20011127 Joel Becker (jlbec@evilplan.org>
 *	Added soft_noboot; Allows testing the softकरोg trigger without
 *	requiring a recompile.
 *	Added WDIOC_GETTIMEOUT and WDIOC_SETTIMOUT.
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/fs.h>
#समावेश <linux/mm.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/watchकरोg.h>
#समावेश <linux/reboot.h>
#समावेश <linux/mutex.h>
#समावेश <linux/init.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/uaccess.h>
#समावेश "mconsole.h"

MODULE_LICENSE("GPL");

अटल DEFINE_MUTEX(hardकरोg_mutex);
अटल DEFINE_SPINLOCK(lock);
अटल पूर्णांक समयr_alive;
अटल पूर्णांक hardकरोg_in_fd = -1;
अटल पूर्णांक hardकरोg_out_fd = -1;

/*
 *	Allow only one person to hold it खोलो
 */

बाह्य पूर्णांक start_watchकरोg(पूर्णांक *in_fd_ret, पूर्णांक *out_fd_ret, अक्षर *sock);

अटल पूर्णांक hardकरोg_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	पूर्णांक err = -EBUSY;
	अक्षर *sock = शून्य;

	mutex_lock(&hardकरोg_mutex);
	spin_lock(&lock);
	अगर(समयr_alive)
		जाओ err;
#अगर_घोषित CONFIG_WATCHDOG_NOWAYOUT
	__module_get(THIS_MODULE);
#पूर्ण_अगर

#अगर_घोषित CONFIG_MCONSOLE
	sock = mconsole_notअगरy_socket();
#पूर्ण_अगर
	err = start_watchकरोg(&hardकरोg_in_fd, &hardकरोg_out_fd, sock);
	अगर(err)
		जाओ err;

	समयr_alive = 1;
	spin_unlock(&lock);
	mutex_unlock(&hardकरोg_mutex);
	वापस stream_खोलो(inode, file);
err:
	spin_unlock(&lock);
	mutex_unlock(&hardकरोg_mutex);
	वापस err;
पूर्ण

बाह्य व्योम stop_watchकरोg(पूर्णांक in_fd, पूर्णांक out_fd);

अटल पूर्णांक hardकरोg_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	/*
	 *	Shut off the समयr.
	 */

	spin_lock(&lock);

	stop_watchकरोg(hardकरोg_in_fd, hardकरोg_out_fd);
	hardकरोg_in_fd = -1;
	hardकरोg_out_fd = -1;

	समयr_alive=0;
	spin_unlock(&lock);

	वापस 0;
पूर्ण

बाह्य पूर्णांक ping_watchकरोg(पूर्णांक fd);

अटल sमाप_प्रकार hardकरोg_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *data, माप_प्रकार len,
			     loff_t *ppos)
अणु
	/*
	 *	Refresh the समयr.
	 */
	अगर(len)
		वापस ping_watchकरोg(hardकरोg_out_fd);
	वापस 0;
पूर्ण

अटल पूर्णांक hardकरोg_ioctl_unlocked(काष्ठा file *file,
				  अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	व्योम __user *argp= (व्योम __user *)arg;
	अटल काष्ठा watchकरोg_info ident = अणु
		WDIOC_SETTIMEOUT,
		0,
		"UML Hardware Watchdog"
	पूर्ण;
	चयन (cmd) अणु
		शेष:
			वापस -ENOTTY;
		हाल WDIOC_GETSUPPORT:
			अगर(copy_to_user(argp, &ident, माप(ident)))
				वापस -EFAULT;
			वापस 0;
		हाल WDIOC_GETSTATUS:
		हाल WDIOC_GETBOOTSTATUS:
			वापस put_user(0,(पूर्णांक __user *)argp);
		हाल WDIOC_KEEPALIVE:
			वापस ping_watchकरोg(hardकरोg_out_fd);
	पूर्ण
पूर्ण

अटल दीर्घ hardकरोg_ioctl(काष्ठा file *file,
			  अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	दीर्घ ret;

	mutex_lock(&hardकरोg_mutex);
	ret = hardकरोg_ioctl_unlocked(file, cmd, arg);
	mutex_unlock(&hardकरोg_mutex);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations hardकरोg_fops = अणु
	.owner		= THIS_MODULE,
	.ग_लिखो		= hardकरोg_ग_लिखो,
	.unlocked_ioctl	= hardकरोg_ioctl,
	.compat_ioctl	= compat_ptr_ioctl,
	.खोलो		= hardकरोg_खोलो,
	.release	= hardकरोg_release,
	.llseek		= no_llseek,
पूर्ण;

अटल काष्ठा miscdevice hardकरोg_miscdev = अणु
	.minor		= WATCHDOG_MINOR,
	.name		= "watchdog",
	.fops		= &hardकरोg_fops,
पूर्ण;
module_misc_device(hardकरोg_miscdev);
