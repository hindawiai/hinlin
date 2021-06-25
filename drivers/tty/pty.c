<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Copyright (C) 1991, 1992  Linus Torvalds
 *
 *  Added support क्रम a Unix98-style pपंचांगx device.
 *    -- C. Scott Ananian <cananian@alumni.princeton.edu>, 14-Jan-1998
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/माला.स>
#समावेश <linux/major.h>
#समावेश <linux/mm.h>
#समावेश <linux/init.h>
#समावेश <linux/device.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/bitops.h>
#समावेश <linux/devpts_fs.h>
#समावेश <linux/slab.h>
#समावेश <linux/mutex.h>
#समावेश <linux/poll.h>
#समावेश <linux/mount.h>
#समावेश <linux/file.h>
#समावेश <linux/ioctl.h>
#समावेश <linux/compat.h>
#समावेश "tty.h"

#अघोषित TTY_DEBUG_HANGUP
#अगर_घोषित TTY_DEBUG_HANGUP
# define tty_debug_hangup(tty, f, args...)	tty_debug(tty, f, ##args)
#अन्यथा
# define tty_debug_hangup(tty, f, args...)	करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर

#अगर_घोषित CONFIG_UNIX98_PTYS
अटल काष्ठा tty_driver *pपंचांग_driver;
अटल काष्ठा tty_driver *pts_driver;
अटल DEFINE_MUTEX(devpts_mutex);
#पूर्ण_अगर

अटल व्योम pty_बंद(काष्ठा tty_काष्ठा *tty, काष्ठा file *filp)
अणु
	अगर (tty->driver->subtype == PTY_TYPE_MASTER)
		WARN_ON(tty->count > 1);
	अन्यथा अणु
		अगर (tty_io_error(tty))
			वापस;
		अगर (tty->count > 2)
			वापस;
	पूर्ण
	set_bit(TTY_IO_ERROR, &tty->flags);
	wake_up_पूर्णांकerruptible(&tty->पढ़ो_रुको);
	wake_up_पूर्णांकerruptible(&tty->ग_लिखो_रुको);
	spin_lock_irq(&tty->ctrl_lock);
	tty->packet = 0;
	spin_unlock_irq(&tty->ctrl_lock);
	/* Review - krefs on tty_link ?? */
	अगर (!tty->link)
		वापस;
	set_bit(TTY_OTHER_CLOSED, &tty->link->flags);
	wake_up_पूर्णांकerruptible(&tty->link->पढ़ो_रुको);
	wake_up_पूर्णांकerruptible(&tty->link->ग_लिखो_रुको);
	अगर (tty->driver->subtype == PTY_TYPE_MASTER) अणु
		set_bit(TTY_OTHER_CLOSED, &tty->flags);
#अगर_घोषित CONFIG_UNIX98_PTYS
		अगर (tty->driver == pपंचांग_driver) अणु
			mutex_lock(&devpts_mutex);
			अगर (tty->link->driver_data)
				devpts_pty_समाप्त(tty->link->driver_data);
			mutex_unlock(&devpts_mutex);
		पूर्ण
#पूर्ण_अगर
		tty_vhangup(tty->link);
	पूर्ण
पूर्ण

/*
 * The unthrottle routine is called by the line discipline to संकेत
 * that it can receive more अक्षरacters.  For PTY's, the TTY_THROTTLED
 * flag is always set, to क्रमce the line discipline to always call the
 * unthrottle routine when there are fewer than TTY_THRESHOLD_UNTHROTTLE
 * अक्षरacters in the queue.  This is necessary since each समय this
 * happens, we need to wake up any sleeping processes that could be
 * (1) trying to send data to the pty, or (2) रुकोing in रुको_until_sent()
 * क्रम the pty buffer to be drained.
 */
अटल व्योम pty_unthrottle(काष्ठा tty_काष्ठा *tty)
अणु
	tty_wakeup(tty->link);
	set_bit(TTY_THROTTLED, &tty->flags);
पूर्ण

/**
 *	pty_ग_लिखो		-	ग_लिखो to a pty
 *	@tty: the tty we ग_लिखो from
 *	@buf: kernel buffer of data
 *	@c: bytes to ग_लिखो
 *
 *	Our "hardware" ग_लिखो method. Data is coming from the ldisc which
 *	may be in a non sleeping state. We simply throw this at the other
 *	end of the link as अगर we were an IRQ handler receiving stuff क्रम
 *	the other side of the pty/tty pair.
 */

अटल पूर्णांक pty_ग_लिखो(काष्ठा tty_काष्ठा *tty, स्थिर अचिन्हित अक्षर *buf, पूर्णांक c)
अणु
	काष्ठा tty_काष्ठा *to = tty->link;
	अचिन्हित दीर्घ flags;

	अगर (tty->stopped)
		वापस 0;

	अगर (c > 0) अणु
		spin_lock_irqsave(&to->port->lock, flags);
		/* Stuff the data पूर्णांकo the input queue of the other end */
		c = tty_insert_flip_string(to->port, buf, c);
		spin_unlock_irqrestore(&to->port->lock, flags);
		/* And shovel */
		अगर (c)
			tty_flip_buffer_push(to->port);
	पूर्ण
	वापस c;
पूर्ण

/**
 *	pty_ग_लिखो_room	-	ग_लिखो space
 *	@tty: tty we are writing from
 *
 *	Report how many bytes the ldisc can send पूर्णांकo the queue क्रम
 *	the other device.
 */

अटल पूर्णांक pty_ग_लिखो_room(काष्ठा tty_काष्ठा *tty)
अणु
	अगर (tty->stopped)
		वापस 0;
	वापस tty_buffer_space_avail(tty->link->port);
पूर्ण

/**
 *	pty_अक्षरs_in_buffer	-	अक्षरacters currently in our tx queue
 *	@tty: our tty
 *
 *	Report how much we have in the transmit queue. As everything is
 *	instantly at the other end this is easy to implement.
 */

अटल पूर्णांक pty_अक्षरs_in_buffer(काष्ठा tty_काष्ठा *tty)
अणु
	वापस 0;
पूर्ण

/* Set the lock flag on a pty */
अटल पूर्णांक pty_set_lock(काष्ठा tty_काष्ठा *tty, पूर्णांक __user *arg)
अणु
	पूर्णांक val;

	अगर (get_user(val, arg))
		वापस -EFAULT;
	अगर (val)
		set_bit(TTY_PTY_LOCK, &tty->flags);
	अन्यथा
		clear_bit(TTY_PTY_LOCK, &tty->flags);
	वापस 0;
पूर्ण

अटल पूर्णांक pty_get_lock(काष्ठा tty_काष्ठा *tty, पूर्णांक __user *arg)
अणु
	पूर्णांक locked = test_bit(TTY_PTY_LOCK, &tty->flags);

	वापस put_user(locked, arg);
पूर्ण

/* Set the packet mode on a pty */
अटल पूर्णांक pty_set_pkपंचांगode(काष्ठा tty_काष्ठा *tty, पूर्णांक __user *arg)
अणु
	पूर्णांक pkपंचांगode;

	अगर (get_user(pkपंचांगode, arg))
		वापस -EFAULT;

	spin_lock_irq(&tty->ctrl_lock);
	अगर (pkपंचांगode) अणु
		अगर (!tty->packet) अणु
			tty->link->ctrl_status = 0;
			smp_mb();
			tty->packet = 1;
		पूर्ण
	पूर्ण अन्यथा
		tty->packet = 0;
	spin_unlock_irq(&tty->ctrl_lock);

	वापस 0;
पूर्ण

/* Get the packet mode of a pty */
अटल पूर्णांक pty_get_pkपंचांगode(काष्ठा tty_काष्ठा *tty, पूर्णांक __user *arg)
अणु
	पूर्णांक pkपंचांगode = tty->packet;

	वापस put_user(pkपंचांगode, arg);
पूर्ण

/* Send a संकेत to the slave */
अटल पूर्णांक pty_संकेत(काष्ठा tty_काष्ठा *tty, पूर्णांक sig)
अणु
	काष्ठा pid *pgrp;

	अगर (sig != संक_विघ्न && sig != SIGQUIT && sig != SIGTSTP)
		वापस -EINVAL;

	अगर (tty->link) अणु
		pgrp = tty_get_pgrp(tty->link);
		अगर (pgrp)
			समाप्त_pgrp(pgrp, sig, 1);
		put_pid(pgrp);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम pty_flush_buffer(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा tty_काष्ठा *to = tty->link;

	अगर (!to)
		वापस;

	tty_buffer_flush(to, शून्य);
	अगर (to->packet) अणु
		spin_lock_irq(&tty->ctrl_lock);
		tty->ctrl_status |= TIOCPKT_FLUSHWRITE;
		wake_up_पूर्णांकerruptible(&to->पढ़ो_रुको);
		spin_unlock_irq(&tty->ctrl_lock);
	पूर्ण
पूर्ण

अटल पूर्णांक pty_खोलो(काष्ठा tty_काष्ठा *tty, काष्ठा file *filp)
अणु
	अगर (!tty || !tty->link)
		वापस -ENODEV;

	अगर (test_bit(TTY_OTHER_CLOSED, &tty->flags))
		जाओ out;
	अगर (test_bit(TTY_PTY_LOCK, &tty->link->flags))
		जाओ out;
	अगर (tty->driver->subtype == PTY_TYPE_SLAVE && tty->link->count != 1)
		जाओ out;

	clear_bit(TTY_IO_ERROR, &tty->flags);
	clear_bit(TTY_OTHER_CLOSED, &tty->link->flags);
	set_bit(TTY_THROTTLED, &tty->flags);
	वापस 0;

out:
	set_bit(TTY_IO_ERROR, &tty->flags);
	वापस -EIO;
पूर्ण

अटल व्योम pty_set_termios(काष्ठा tty_काष्ठा *tty,
					काष्ठा ktermios *old_termios)
अणु
	/* See अगर packet mode change of state. */
	अगर (tty->link && tty->link->packet) अणु
		पूर्णांक extproc = (old_termios->c_lflag & EXTPROC) | L_EXTPROC(tty);
		पूर्णांक old_flow = ((old_termios->c_अगरlag & IXON) &&
				(old_termios->c_cc[VSTOP] == '\023') &&
				(old_termios->c_cc[VSTART] == '\021'));
		पूर्णांक new_flow = (I_IXON(tty) &&
				STOP_CHAR(tty) == '\023' &&
				START_CHAR(tty) == '\021');
		अगर ((old_flow != new_flow) || extproc) अणु
			spin_lock_irq(&tty->ctrl_lock);
			अगर (old_flow != new_flow) अणु
				tty->ctrl_status &= ~(TIOCPKT_DOSTOP | TIOCPKT_NOSTOP);
				अगर (new_flow)
					tty->ctrl_status |= TIOCPKT_DOSTOP;
				अन्यथा
					tty->ctrl_status |= TIOCPKT_NOSTOP;
			पूर्ण
			अगर (extproc)
				tty->ctrl_status |= TIOCPKT_IOCTL;
			spin_unlock_irq(&tty->ctrl_lock);
			wake_up_पूर्णांकerruptible(&tty->link->पढ़ो_रुको);
		पूर्ण
	पूर्ण

	tty->termios.c_cflag &= ~(CSIZE | PARENB);
	tty->termios.c_cflag |= (CS8 | CREAD);
पूर्ण

/**
 *	pty_करो_resize		-	resize event
 *	@tty: tty being resized
 *	@ws: winकरोw size being set.
 *
 *	Update the termios variables and send the necessary संकेतs to
 *	peक्रमm a terminal resize correctly
 */

अटल पूर्णांक pty_resize(काष्ठा tty_काष्ठा *tty,  काष्ठा winsize *ws)
अणु
	काष्ठा pid *pgrp, *rpgrp;
	काष्ठा tty_काष्ठा *pty = tty->link;

	/* For a PTY we need to lock the tty side */
	mutex_lock(&tty->winsize_mutex);
	अगर (!स_भेद(ws, &tty->winsize, माप(*ws)))
		जाओ करोne;

	/* Signal the क्रमeground process group of both ptys */
	pgrp = tty_get_pgrp(tty);
	rpgrp = tty_get_pgrp(pty);

	अगर (pgrp)
		समाप्त_pgrp(pgrp, SIGWINCH, 1);
	अगर (rpgrp != pgrp && rpgrp)
		समाप्त_pgrp(rpgrp, SIGWINCH, 1);

	put_pid(pgrp);
	put_pid(rpgrp);

	tty->winsize = *ws;
	pty->winsize = *ws;	/* Never used so will go away soon */
करोne:
	mutex_unlock(&tty->winsize_mutex);
	वापस 0;
पूर्ण

/**
 *	pty_start - start() handler
 *	pty_stop  - stop() handler
 *	@tty: tty being flow-controlled
 *
 *	Propagates the TIOCPKT status to the master pty.
 *
 *	NB: only the master pty can be in packet mode so only the slave
 *	    needs start()/stop() handlers
 */
अटल व्योम pty_start(काष्ठा tty_काष्ठा *tty)
अणु
	अचिन्हित दीर्घ flags;

	अगर (tty->link && tty->link->packet) अणु
		spin_lock_irqsave(&tty->ctrl_lock, flags);
		tty->ctrl_status &= ~TIOCPKT_STOP;
		tty->ctrl_status |= TIOCPKT_START;
		spin_unlock_irqrestore(&tty->ctrl_lock, flags);
		wake_up_पूर्णांकerruptible_poll(&tty->link->पढ़ो_रुको, EPOLLIN);
	पूर्ण
पूर्ण

अटल व्योम pty_stop(काष्ठा tty_काष्ठा *tty)
अणु
	अचिन्हित दीर्घ flags;

	अगर (tty->link && tty->link->packet) अणु
		spin_lock_irqsave(&tty->ctrl_lock, flags);
		tty->ctrl_status &= ~TIOCPKT_START;
		tty->ctrl_status |= TIOCPKT_STOP;
		spin_unlock_irqrestore(&tty->ctrl_lock, flags);
		wake_up_पूर्णांकerruptible_poll(&tty->link->पढ़ो_रुको, EPOLLIN);
	पूर्ण
पूर्ण

/**
 *	pty_common_install		-	set up the pty pair
 *	@driver: the pty driver
 *	@tty: the tty being instantiated
 *	@legacy: true अगर this is BSD style
 *
 *	Perक्रमm the initial set up क्रम the tty/pty pair. Called from the
 *	tty layer when the port is first खोलोed.
 *
 *	Locking: the caller must hold the tty_mutex
 */
अटल पूर्णांक pty_common_install(काष्ठा tty_driver *driver, काष्ठा tty_काष्ठा *tty,
		bool legacy)
अणु
	काष्ठा tty_काष्ठा *o_tty;
	काष्ठा tty_port *ports[2];
	पूर्णांक idx = tty->index;
	पूर्णांक retval = -ENOMEM;

	/* Opening the slave first has always वापसed -EIO */
	अगर (driver->subtype != PTY_TYPE_MASTER)
		वापस -EIO;

	ports[0] = kदो_स्मृति(माप **ports, GFP_KERNEL);
	ports[1] = kदो_स्मृति(माप **ports, GFP_KERNEL);
	अगर (!ports[0] || !ports[1])
		जाओ err;
	अगर (!try_module_get(driver->other->owner)) अणु
		/* This cannot in fact currently happen */
		जाओ err;
	पूर्ण
	o_tty = alloc_tty_काष्ठा(driver->other, idx);
	अगर (!o_tty)
		जाओ err_put_module;

	tty_set_lock_subclass(o_tty);
	lockdep_set_subclass(&o_tty->termios_rwsem, TTY_LOCK_SLAVE);

	अगर (legacy) अणु
		/* We always use new tty termios data so we can करो this
		   the easy way .. */
		tty_init_termios(tty);
		tty_init_termios(o_tty);

		driver->other->ttys[idx] = o_tty;
		driver->ttys[idx] = tty;
	पूर्ण अन्यथा अणु
		स_रखो(&tty->termios_locked, 0, माप(tty->termios_locked));
		tty->termios = driver->init_termios;
		स_रखो(&o_tty->termios_locked, 0, माप(tty->termios_locked));
		o_tty->termios = driver->other->init_termios;
	पूर्ण

	/*
	 * Everything allocated ... set up the o_tty काष्ठाure.
	 */
	tty_driver_kref_get(driver->other);
	/* Establish the links in both directions */
	tty->link   = o_tty;
	o_tty->link = tty;
	tty_port_init(ports[0]);
	tty_port_init(ports[1]);
	tty_buffer_set_limit(ports[0], 8192);
	tty_buffer_set_limit(ports[1], 8192);
	o_tty->port = ports[0];
	tty->port = ports[1];
	o_tty->port->itty = o_tty;

	tty_buffer_set_lock_subclass(o_tty->port);

	tty_driver_kref_get(driver);
	tty->count++;
	o_tty->count++;
	वापस 0;

err_put_module:
	module_put(driver->other->owner);
err:
	kमुक्त(ports[0]);
	kमुक्त(ports[1]);
	वापस retval;
पूर्ण

अटल व्योम pty_cleanup(काष्ठा tty_काष्ठा *tty)
अणु
	tty_port_put(tty->port);
पूर्ण

/* Traditional BSD devices */
#अगर_घोषित CONFIG_LEGACY_PTYS

अटल पूर्णांक pty_install(काष्ठा tty_driver *driver, काष्ठा tty_काष्ठा *tty)
अणु
	वापस pty_common_install(driver, tty, true);
पूर्ण

अटल व्योम pty_हटाओ(काष्ठा tty_driver *driver, काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा tty_काष्ठा *pair = tty->link;

	driver->ttys[tty->index] = शून्य;
	अगर (pair)
		pair->driver->ttys[pair->index] = शून्य;
पूर्ण

अटल पूर्णांक pty_bsd_ioctl(काष्ठा tty_काष्ठा *tty,
			 अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	चयन (cmd) अणु
	हाल TIOCSPTLCK: /* Set PT Lock (disallow slave खोलो) */
		वापस pty_set_lock(tty, (पूर्णांक __user *) arg);
	हाल TIOCGPTLCK: /* Get PT Lock status */
		वापस pty_get_lock(tty, (पूर्णांक __user *)arg);
	हाल TIOCPKT: /* Set PT packet mode */
		वापस pty_set_pkपंचांगode(tty, (पूर्णांक __user *)arg);
	हाल TIOCGPKT: /* Get PT packet mode */
		वापस pty_get_pkपंचांगode(tty, (पूर्णांक __user *)arg);
	हाल TIOCSIG:    /* Send संकेत to other side of pty */
		वापस pty_संकेत(tty, (पूर्णांक) arg);
	हाल TIOCGPTN: /* TTY वापसs ENOTTY, but glibc expects EINVAL here */
		वापस -EINVAL;
	पूर्ण
	वापस -ENOIOCTLCMD;
पूर्ण

#अगर_घोषित CONFIG_COMPAT
अटल दीर्घ pty_bsd_compat_ioctl(काष्ठा tty_काष्ठा *tty,
				 अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	/*
	 * PTY ioctls करोn't require any special translation between 32-bit and
	 * 64-bit userspace, they are alपढ़ोy compatible.
	 */
	वापस pty_bsd_ioctl(tty, cmd, (अचिन्हित दीर्घ)compat_ptr(arg));
पूर्ण
#अन्यथा
#घोषणा pty_bsd_compat_ioctl शून्य
#पूर्ण_अगर

अटल पूर्णांक legacy_count = CONFIG_LEGACY_PTY_COUNT;
/*
 * not really modular, but the easiest way to keep compat with existing
 * bootargs behaviour is to जारी using module_param here.
 */
module_param(legacy_count, पूर्णांक, 0);

/*
 * The master side of a pty can करो TIOCSPTLCK and thus
 * has pty_bsd_ioctl.
 */
अटल स्थिर काष्ठा tty_operations master_pty_ops_bsd = अणु
	.install = pty_install,
	.खोलो = pty_खोलो,
	.बंद = pty_बंद,
	.ग_लिखो = pty_ग_लिखो,
	.ग_लिखो_room = pty_ग_लिखो_room,
	.flush_buffer = pty_flush_buffer,
	.अक्षरs_in_buffer = pty_अक्षरs_in_buffer,
	.unthrottle = pty_unthrottle,
	.ioctl = pty_bsd_ioctl,
	.compat_ioctl = pty_bsd_compat_ioctl,
	.cleanup = pty_cleanup,
	.resize = pty_resize,
	.हटाओ = pty_हटाओ
पूर्ण;

अटल स्थिर काष्ठा tty_operations slave_pty_ops_bsd = अणु
	.install = pty_install,
	.खोलो = pty_खोलो,
	.बंद = pty_बंद,
	.ग_लिखो = pty_ग_लिखो,
	.ग_लिखो_room = pty_ग_लिखो_room,
	.flush_buffer = pty_flush_buffer,
	.अक्षरs_in_buffer = pty_अक्षरs_in_buffer,
	.unthrottle = pty_unthrottle,
	.set_termios = pty_set_termios,
	.cleanup = pty_cleanup,
	.resize = pty_resize,
	.start = pty_start,
	.stop = pty_stop,
	.हटाओ = pty_हटाओ
पूर्ण;

अटल व्योम __init legacy_pty_init(व्योम)
अणु
	काष्ठा tty_driver *pty_driver, *pty_slave_driver;

	अगर (legacy_count <= 0)
		वापस;

	pty_driver = tty_alloc_driver(legacy_count,
			TTY_DRIVER_RESET_TERMIOS |
			TTY_DRIVER_REAL_RAW |
			TTY_DRIVER_DYNAMIC_ALLOC);
	अगर (IS_ERR(pty_driver))
		panic("Couldn't allocate pty driver");

	pty_slave_driver = tty_alloc_driver(legacy_count,
			TTY_DRIVER_RESET_TERMIOS |
			TTY_DRIVER_REAL_RAW |
			TTY_DRIVER_DYNAMIC_ALLOC);
	अगर (IS_ERR(pty_slave_driver))
		panic("Couldn't allocate pty slave driver");

	pty_driver->driver_name = "pty_master";
	pty_driver->name = "pty";
	pty_driver->major = PTY_MASTER_MAJOR;
	pty_driver->minor_start = 0;
	pty_driver->type = TTY_DRIVER_TYPE_PTY;
	pty_driver->subtype = PTY_TYPE_MASTER;
	pty_driver->init_termios = tty_std_termios;
	pty_driver->init_termios.c_अगरlag = 0;
	pty_driver->init_termios.c_oflag = 0;
	pty_driver->init_termios.c_cflag = B38400 | CS8 | CREAD;
	pty_driver->init_termios.c_lflag = 0;
	pty_driver->init_termios.c_ispeed = 38400;
	pty_driver->init_termios.c_ospeed = 38400;
	pty_driver->other = pty_slave_driver;
	tty_set_operations(pty_driver, &master_pty_ops_bsd);

	pty_slave_driver->driver_name = "pty_slave";
	pty_slave_driver->name = "ttyp";
	pty_slave_driver->major = PTY_SLAVE_MAJOR;
	pty_slave_driver->minor_start = 0;
	pty_slave_driver->type = TTY_DRIVER_TYPE_PTY;
	pty_slave_driver->subtype = PTY_TYPE_SLAVE;
	pty_slave_driver->init_termios = tty_std_termios;
	pty_slave_driver->init_termios.c_cflag = B38400 | CS8 | CREAD;
	pty_slave_driver->init_termios.c_ispeed = 38400;
	pty_slave_driver->init_termios.c_ospeed = 38400;
	pty_slave_driver->other = pty_driver;
	tty_set_operations(pty_slave_driver, &slave_pty_ops_bsd);

	अगर (tty_रेजिस्टर_driver(pty_driver))
		panic("Couldn't register pty driver");
	अगर (tty_रेजिस्टर_driver(pty_slave_driver))
		panic("Couldn't register pty slave driver");
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम legacy_pty_init(व्योम) अणु पूर्ण
#पूर्ण_अगर

/* Unix98 devices */
#अगर_घोषित CONFIG_UNIX98_PTYS
अटल काष्ठा cdev pपंचांगx_cdev;

/**
 *	pपंचांग_खोलो_peer - खोलो the peer of a pty
 *	@master: the खोलो काष्ठा file of the pपंचांगx device node
 *	@tty: the master of the pty being खोलोed
 *	@flags: the flags क्रम खोलो
 *
 *	Provide a race मुक्त way क्रम userspace to खोलो the slave end of a pty
 *	(where they have the master fd and cannot access or trust the mount
 *	namespace /dev/pts was mounted inside).
 */
पूर्णांक pपंचांग_खोलो_peer(काष्ठा file *master, काष्ठा tty_काष्ठा *tty, पूर्णांक flags)
अणु
	पूर्णांक fd = -1;
	काष्ठा file *filp;
	पूर्णांक retval = -EINVAL;
	काष्ठा path path;

	अगर (tty->driver != pपंचांग_driver)
		वापस -EIO;

	fd = get_unused_fd_flags(flags);
	अगर (fd < 0) अणु
		retval = fd;
		जाओ err;
	पूर्ण

	/* Compute the slave's path */
	path.mnt = devpts_mntget(master, tty->driver_data);
	अगर (IS_ERR(path.mnt)) अणु
		retval = PTR_ERR(path.mnt);
		जाओ err_put;
	पूर्ण
	path.dentry = tty->link->driver_data;

	filp = dentry_खोलो(&path, flags, current_cred());
	mntput(path.mnt);
	अगर (IS_ERR(filp)) अणु
		retval = PTR_ERR(filp);
		जाओ err_put;
	पूर्ण

	fd_install(fd, filp);
	वापस fd;

err_put:
	put_unused_fd(fd);
err:
	वापस retval;
पूर्ण

अटल पूर्णांक pty_unix98_ioctl(काष्ठा tty_काष्ठा *tty,
			    अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	चयन (cmd) अणु
	हाल TIOCSPTLCK: /* Set PT Lock (disallow slave खोलो) */
		वापस pty_set_lock(tty, (पूर्णांक __user *)arg);
	हाल TIOCGPTLCK: /* Get PT Lock status */
		वापस pty_get_lock(tty, (पूर्णांक __user *)arg);
	हाल TIOCPKT: /* Set PT packet mode */
		वापस pty_set_pkपंचांगode(tty, (पूर्णांक __user *)arg);
	हाल TIOCGPKT: /* Get PT packet mode */
		वापस pty_get_pkपंचांगode(tty, (पूर्णांक __user *)arg);
	हाल TIOCGPTN: /* Get PT Number */
		वापस put_user(tty->index, (अचिन्हित पूर्णांक __user *)arg);
	हाल TIOCSIG:    /* Send संकेत to other side of pty */
		वापस pty_संकेत(tty, (पूर्णांक) arg);
	पूर्ण

	वापस -ENOIOCTLCMD;
पूर्ण

#अगर_घोषित CONFIG_COMPAT
अटल दीर्घ pty_unix98_compat_ioctl(काष्ठा tty_काष्ठा *tty,
				 अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	/*
	 * PTY ioctls करोn't require any special translation between 32-bit and
	 * 64-bit userspace, they are alपढ़ोy compatible.
	 */
	वापस pty_unix98_ioctl(tty, cmd,
		cmd == TIOCSIG ? arg : (अचिन्हित दीर्घ)compat_ptr(arg));
पूर्ण
#अन्यथा
#घोषणा pty_unix98_compat_ioctl शून्य
#पूर्ण_अगर

/**
 *	pपंचांग_unix98_lookup	-	find a pty master
 *	@driver: pपंचांग driver
 *	@file: unused
 *	@idx: tty index
 *
 *	Look up a pty master device. Called under the tty_mutex क्रम now.
 *	This provides our locking.
 */

अटल काष्ठा tty_काष्ठा *pपंचांग_unix98_lookup(काष्ठा tty_driver *driver,
		काष्ठा file *file, पूर्णांक idx)
अणु
	/* Master must be खोलो via /dev/pपंचांगx */
	वापस ERR_PTR(-EIO);
पूर्ण

/**
 *	pts_unix98_lookup	-	find a pty slave
 *	@driver: pts driver
 *	@file: file poपूर्णांकer to tty
 *	@idx: tty index
 *
 *	Look up a pty master device. Called under the tty_mutex क्रम now.
 *	This provides our locking क्रम the tty poपूर्णांकer.
 */

अटल काष्ठा tty_काष्ठा *pts_unix98_lookup(काष्ठा tty_driver *driver,
		काष्ठा file *file, पूर्णांक idx)
अणु
	काष्ठा tty_काष्ठा *tty;

	mutex_lock(&devpts_mutex);
	tty = devpts_get_priv(file->f_path.dentry);
	mutex_unlock(&devpts_mutex);
	/* Master must be खोलो beक्रमe slave */
	अगर (!tty)
		वापस ERR_PTR(-EIO);
	वापस tty;
पूर्ण

अटल पूर्णांक pty_unix98_install(काष्ठा tty_driver *driver, काष्ठा tty_काष्ठा *tty)
अणु
	वापस pty_common_install(driver, tty, false);
पूर्ण

/* this is called once with whichever end is बंदd last */
अटल व्योम pty_unix98_हटाओ(काष्ठा tty_driver *driver, काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा pts_fs_info *fsi;

	अगर (tty->driver->subtype == PTY_TYPE_MASTER)
		fsi = tty->driver_data;
	अन्यथा
		fsi = tty->link->driver_data;

	अगर (fsi) अणु
		devpts_समाप्त_index(fsi, tty->index);
		devpts_release(fsi);
	पूर्ण
पूर्ण

अटल व्योम pty_show_fdinfo(काष्ठा tty_काष्ठा *tty, काष्ठा seq_file *m)
अणु
	seq_म_लिखो(m, "tty-index:\t%d\n", tty->index);
पूर्ण

अटल स्थिर काष्ठा tty_operations pपंचांग_unix98_ops = अणु
	.lookup = pपंचांग_unix98_lookup,
	.install = pty_unix98_install,
	.हटाओ = pty_unix98_हटाओ,
	.खोलो = pty_खोलो,
	.बंद = pty_बंद,
	.ग_लिखो = pty_ग_लिखो,
	.ग_लिखो_room = pty_ग_लिखो_room,
	.flush_buffer = pty_flush_buffer,
	.अक्षरs_in_buffer = pty_अक्षरs_in_buffer,
	.unthrottle = pty_unthrottle,
	.ioctl = pty_unix98_ioctl,
	.compat_ioctl = pty_unix98_compat_ioctl,
	.resize = pty_resize,
	.cleanup = pty_cleanup,
	.show_fdinfo = pty_show_fdinfo,
पूर्ण;

अटल स्थिर काष्ठा tty_operations pty_unix98_ops = अणु
	.lookup = pts_unix98_lookup,
	.install = pty_unix98_install,
	.हटाओ = pty_unix98_हटाओ,
	.खोलो = pty_खोलो,
	.बंद = pty_बंद,
	.ग_लिखो = pty_ग_लिखो,
	.ग_लिखो_room = pty_ग_लिखो_room,
	.flush_buffer = pty_flush_buffer,
	.अक्षरs_in_buffer = pty_अक्षरs_in_buffer,
	.unthrottle = pty_unthrottle,
	.set_termios = pty_set_termios,
	.start = pty_start,
	.stop = pty_stop,
	.cleanup = pty_cleanup,
पूर्ण;

/**
 *	pपंचांगx_खोलो		-	खोलो a unix 98 pty master
 *	@inode: inode of device file
 *	@filp: file poपूर्णांकer to tty
 *
 *	Allocate a unix98 pty master device from the pपंचांगx driver.
 *
 *	Locking: tty_mutex protects the init_dev work. tty->count should
 *		protect the rest.
 *		allocated_ptys_lock handles the list of मुक्त pty numbers
 */

अटल पूर्णांक pपंचांगx_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा pts_fs_info *fsi;
	काष्ठा tty_काष्ठा *tty;
	काष्ठा dentry *dentry;
	पूर्णांक retval;
	पूर्णांक index;

	nonseekable_खोलो(inode, filp);

	/* We refuse fsnotअगरy events on pपंचांगx, since it's a shared resource */
	filp->f_mode |= FMODE_NONOTIFY;

	retval = tty_alloc_file(filp);
	अगर (retval)
		वापस retval;

	fsi = devpts_acquire(filp);
	अगर (IS_ERR(fsi)) अणु
		retval = PTR_ERR(fsi);
		जाओ out_मुक्त_file;
	पूर्ण

	/* find a device that is not in use. */
	mutex_lock(&devpts_mutex);
	index = devpts_new_index(fsi);
	mutex_unlock(&devpts_mutex);

	retval = index;
	अगर (index < 0)
		जाओ out_put_fsi;


	mutex_lock(&tty_mutex);
	tty = tty_init_dev(pपंचांग_driver, index);
	/* The tty वापसed here is locked so we can safely
	   drop the mutex */
	mutex_unlock(&tty_mutex);

	retval = PTR_ERR(tty);
	अगर (IS_ERR(tty))
		जाओ out;

	/*
	 * From here on out, the tty is "live", and the index and
	 * fsi will be समाप्तed/put by the tty_release()
	 */
	set_bit(TTY_PTY_LOCK, &tty->flags); /* LOCK THE SLAVE */
	tty->driver_data = fsi;

	tty_add_file(tty, filp);

	dentry = devpts_pty_new(fsi, index, tty->link);
	अगर (IS_ERR(dentry)) अणु
		retval = PTR_ERR(dentry);
		जाओ err_release;
	पूर्ण
	tty->link->driver_data = dentry;

	retval = pपंचांग_driver->ops->खोलो(tty, filp);
	अगर (retval)
		जाओ err_release;

	tty_debug_hangup(tty, "opening (count=%d)\n", tty->count);

	tty_unlock(tty);
	वापस 0;
err_release:
	tty_unlock(tty);
	// This will also put-ref the fsi
	tty_release(inode, filp);
	वापस retval;
out:
	devpts_समाप्त_index(fsi, index);
out_put_fsi:
	devpts_release(fsi);
out_मुक्त_file:
	tty_मुक्त_file(filp);
	वापस retval;
पूर्ण

अटल काष्ठा file_operations pपंचांगx_fops __ro_after_init;

अटल व्योम __init unix98_pty_init(व्योम)
अणु
	pपंचांग_driver = tty_alloc_driver(NR_UNIX98_PTY_MAX,
			TTY_DRIVER_RESET_TERMIOS |
			TTY_DRIVER_REAL_RAW |
			TTY_DRIVER_DYNAMIC_DEV |
			TTY_DRIVER_DEVPTS_MEM |
			TTY_DRIVER_DYNAMIC_ALLOC);
	अगर (IS_ERR(pपंचांग_driver))
		panic("Couldn't allocate Unix98 ptm driver");
	pts_driver = tty_alloc_driver(NR_UNIX98_PTY_MAX,
			TTY_DRIVER_RESET_TERMIOS |
			TTY_DRIVER_REAL_RAW |
			TTY_DRIVER_DYNAMIC_DEV |
			TTY_DRIVER_DEVPTS_MEM |
			TTY_DRIVER_DYNAMIC_ALLOC);
	अगर (IS_ERR(pts_driver))
		panic("Couldn't allocate Unix98 pts driver");

	pपंचांग_driver->driver_name = "pty_master";
	pपंचांग_driver->name = "ptm";
	pपंचांग_driver->major = UNIX98_PTY_MASTER_MAJOR;
	pपंचांग_driver->minor_start = 0;
	pपंचांग_driver->type = TTY_DRIVER_TYPE_PTY;
	pपंचांग_driver->subtype = PTY_TYPE_MASTER;
	pपंचांग_driver->init_termios = tty_std_termios;
	pपंचांग_driver->init_termios.c_अगरlag = 0;
	pपंचांग_driver->init_termios.c_oflag = 0;
	pपंचांग_driver->init_termios.c_cflag = B38400 | CS8 | CREAD;
	pपंचांग_driver->init_termios.c_lflag = 0;
	pपंचांग_driver->init_termios.c_ispeed = 38400;
	pपंचांग_driver->init_termios.c_ospeed = 38400;
	pपंचांग_driver->other = pts_driver;
	tty_set_operations(pपंचांग_driver, &pपंचांग_unix98_ops);

	pts_driver->driver_name = "pty_slave";
	pts_driver->name = "pts";
	pts_driver->major = UNIX98_PTY_SLAVE_MAJOR;
	pts_driver->minor_start = 0;
	pts_driver->type = TTY_DRIVER_TYPE_PTY;
	pts_driver->subtype = PTY_TYPE_SLAVE;
	pts_driver->init_termios = tty_std_termios;
	pts_driver->init_termios.c_cflag = B38400 | CS8 | CREAD;
	pts_driver->init_termios.c_ispeed = 38400;
	pts_driver->init_termios.c_ospeed = 38400;
	pts_driver->other = pपंचांग_driver;
	tty_set_operations(pts_driver, &pty_unix98_ops);

	अगर (tty_रेजिस्टर_driver(pपंचांग_driver))
		panic("Couldn't register Unix98 ptm driver");
	अगर (tty_रेजिस्टर_driver(pts_driver))
		panic("Couldn't register Unix98 pts driver");

	/* Now create the /dev/pपंचांगx special device */
	tty_शेष_fops(&pपंचांगx_fops);
	pपंचांगx_fops.खोलो = pपंचांगx_खोलो;

	cdev_init(&pपंचांगx_cdev, &pपंचांगx_fops);
	अगर (cdev_add(&pपंचांगx_cdev, MKDEV(TTYAUX_MAJOR, 2), 1) ||
	    रेजिस्टर_chrdev_region(MKDEV(TTYAUX_MAJOR, 2), 1, "/dev/ptmx") < 0)
		panic("Couldn't register /dev/ptmx driver");
	device_create(tty_class, शून्य, MKDEV(TTYAUX_MAJOR, 2), शून्य, "ptmx");
पूर्ण

#अन्यथा
अटल अंतरभूत व्योम unix98_pty_init(व्योम) अणु पूर्ण
#पूर्ण_अगर

अटल पूर्णांक __init pty_init(व्योम)
अणु
	legacy_pty_init();
	unix98_pty_init();
	वापस 0;
पूर्ण
device_initcall(pty_init);
