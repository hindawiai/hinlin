<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Copyright (C) 1991, 1992  Linus Torvalds
 */

/*
 * 'tty_io.c' gives an orthogonal feeling to tty's, be they consoles
 * or rs-channels. It also implements echoing, cooked mode etc.
 *
 * Kill-line thanks to John T Kohl, who also corrected VMIN = VTIME = 0.
 *
 * Modअगरied by Theoकरोre Ts'o, 9/14/92, to dynamically allocate the
 * tty_काष्ठा and tty_queue काष्ठाures.  Previously there was an array
 * of 256 tty_काष्ठा's which was अटलally allocated, and the
 * tty_queue काष्ठाures were allocated at boot समय.  Both are now
 * dynamically allocated only when the tty is खोलो.
 *
 * Also reकाष्ठाured routines so that there is more of a separation
 * between the high-level tty routines (tty_io.c and tty_ioctl.c) and
 * the low-level tty routines (serial.c, pty.c, console.c).  This
 * makes क्रम cleaner and more compact code.  -TYT, 9/17/92
 *
 * Modअगरied by Fred N. van Kempen, 01/29/93, to add line disciplines
 * which can be dynamically activated and de-activated by the line
 * discipline handling modules (like SLIP).
 *
 * NOTE: pay no attention to the line discipline code (yet); its
 * पूर्णांकerface is still subject to change in this version...
 * -- TYT, 1/31/92
 *
 * Added functionality to the OPOST tty handling.  No delays, but all
 * other bits should be there.
 *	-- Nick Holloway <alfie@dcs.warwick.ac.uk>, 27th May 1993.
 *
 * Rewrote canonical mode and added more termios flags.
 * 	-- julian@uhunix.uhcc.hawaii.edu (J. Cowley), 13Jan94
 *
 * Reorganized FASYNC support so mouse code can share it.
 *	-- cपंचांग@ardi.com, 9Sep95
 *
 * New TIOCLINUX variants added.
 *	-- mj@k332.feld.cvut.cz, 19-Nov-95
 *
 * Restrict vt चयनing via ioctl()
 *      -- grअगर@cs.ucr.edu, 5-Dec-95
 *
 * Move console and भव terminal code to more appropriate files,
 * implement CONFIG_VT and generalize console device पूर्णांकerface.
 *	-- Marko Kohtala <Marko.Kohtala@hut.fi>, March 97
 *
 * Rewrote tty_init_dev and tty_release_dev to eliminate races.
 *	-- Bill Hawes <whawes@star.net>, June 97
 *
 * Added devfs support.
 *      -- C. Scott Ananian <cananian@alumni.princeton.edu>, 13-Jan-1998
 *
 * Added support क्रम a Unix98-style pपंचांगx device.
 *      -- C. Scott Ananian <cananian@alumni.princeton.edu>, 14-Jan-1998
 *
 * Reduced memory usage क्रम older ARM प्रणालीs
 *      -- Russell King <rmk@arm.linux.org.uk>
 *
 * Move करो_SAK() पूर्णांकo process context.  Less stack use in devfs functions.
 * alloc_tty_काष्ठा() always uses kदो_स्मृति()
 *			 -- Andrew Morton <andrewm@uow.edu.eu> 17Mar01
 */

#समावेश <linux/types.h>
#समावेश <linux/major.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/संकेत.स>
#समावेश <linux/fcntl.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/sched/task.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_driver.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/devpts_fs.h>
#समावेश <linux/file.h>
#समावेश <linux/fdtable.h>
#समावेश <linux/console.h>
#समावेश <linux/समयr.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/kd.h>
#समावेश <linux/mm.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/poll.h>
#समावेश <linux/ppp-ioctl.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/रुको.h>
#समावेश <linux/bitops.h>
#समावेश <linux/delay.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/serial.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/compat.h>

#समावेश <linux/uaccess.h>

#समावेश <linux/kbd_kern.h>
#समावेश <linux/vt_kern.h>
#समावेश <linux/selection.h>

#समावेश <linux/kmod.h>
#समावेश <linux/nsproxy.h>
#समावेश "tty.h"

#अघोषित TTY_DEBUG_HANGUP
#अगर_घोषित TTY_DEBUG_HANGUP
# define tty_debug_hangup(tty, f, args...)	tty_debug(tty, f, ##args)
#अन्यथा
# define tty_debug_hangup(tty, f, args...)	करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

#घोषणा TTY_PARANOIA_CHECK 1
#घोषणा CHECK_TTY_COUNT 1

काष्ठा ktermios tty_std_termios = अणु	/* क्रम the benefit of tty drivers  */
	.c_अगरlag = ICRNL | IXON,
	.c_oflag = OPOST | ONLCR,
	.c_cflag = B38400 | CS8 | CREAD | HUPCL,
	.c_lflag = ISIG | ICANON | ECHO | ECHOE | ECHOK |
		   ECHOCTL | ECHOKE | IEXTEN,
	.c_cc = INIT_C_CC,
	.c_ispeed = 38400,
	.c_ospeed = 38400,
	/* .c_line = N_TTY, */
पूर्ण;

EXPORT_SYMBOL(tty_std_termios);

/* This list माला_लो poked at by procfs and various bits of boot up code. This
   could करो with some rationalisation such as pulling the tty proc function
   पूर्णांकo this file */

LIST_HEAD(tty_drivers);			/* linked list of tty drivers */

/* Mutex to protect creating and releasing a tty */
DEFINE_MUTEX(tty_mutex);

अटल sमाप_प्रकार tty_पढ़ो(काष्ठा kiocb *, काष्ठा iov_iter *);
अटल sमाप_प्रकार tty_ग_लिखो(काष्ठा kiocb *, काष्ठा iov_iter *);
अटल __poll_t tty_poll(काष्ठा file *, poll_table *);
अटल पूर्णांक tty_खोलो(काष्ठा inode *, काष्ठा file *);
#अगर_घोषित CONFIG_COMPAT
अटल दीर्घ tty_compat_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
				अचिन्हित दीर्घ arg);
#अन्यथा
#घोषणा tty_compat_ioctl शून्य
#पूर्ण_अगर
अटल पूर्णांक __tty_fasync(पूर्णांक fd, काष्ठा file *filp, पूर्णांक on);
अटल पूर्णांक tty_fasync(पूर्णांक fd, काष्ठा file *filp, पूर्णांक on);
अटल व्योम release_tty(काष्ठा tty_काष्ठा *tty, पूर्णांक idx);

/**
 *	मुक्त_tty_काष्ठा		-	मुक्त a disused tty
 *	@tty: tty काष्ठा to मुक्त
 *
 *	Free the ग_लिखो buffers, tty queue and tty memory itself.
 *
 *	Locking: none. Must be called after tty is definitely unused
 */

अटल व्योम मुक्त_tty_काष्ठा(काष्ठा tty_काष्ठा *tty)
अणु
	tty_ldisc_deinit(tty);
	put_device(tty->dev);
	kमुक्त(tty->ग_लिखो_buf);
	tty->magic = 0xDEADDEAD;
	kमुक्त(tty);
पूर्ण

अटल अंतरभूत काष्ठा tty_काष्ठा *file_tty(काष्ठा file *file)
अणु
	वापस ((काष्ठा tty_file_निजी *)file->निजी_data)->tty;
पूर्ण

पूर्णांक tty_alloc_file(काष्ठा file *file)
अणु
	काष्ठा tty_file_निजी *priv;

	priv = kदो_स्मृति(माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	file->निजी_data = priv;

	वापस 0;
पूर्ण

/* Associate a new file with the tty काष्ठाure */
व्योम tty_add_file(काष्ठा tty_काष्ठा *tty, काष्ठा file *file)
अणु
	काष्ठा tty_file_निजी *priv = file->निजी_data;

	priv->tty = tty;
	priv->file = file;

	spin_lock(&tty->files_lock);
	list_add(&priv->list, &tty->tty_files);
	spin_unlock(&tty->files_lock);
पूर्ण

/*
 * tty_मुक्त_file - मुक्त file->निजी_data
 *
 * This shall be used only क्रम fail path handling when tty_add_file was not
 * called yet.
 */
व्योम tty_मुक्त_file(काष्ठा file *file)
अणु
	काष्ठा tty_file_निजी *priv = file->निजी_data;

	file->निजी_data = शून्य;
	kमुक्त(priv);
पूर्ण

/* Delete file from its tty */
अटल व्योम tty_del_file(काष्ठा file *file)
अणु
	काष्ठा tty_file_निजी *priv = file->निजी_data;
	काष्ठा tty_काष्ठा *tty = priv->tty;

	spin_lock(&tty->files_lock);
	list_del(&priv->list);
	spin_unlock(&tty->files_lock);
	tty_मुक्त_file(file);
पूर्ण

/**
 *	tty_name	-	वापस tty naming
 *	@tty: tty काष्ठाure
 *
 *	Convert a tty काष्ठाure पूर्णांकo a name. The name reflects the kernel
 *	naming policy and अगर udev is in use may not reflect user space
 *
 *	Locking: none
 */

स्थिर अक्षर *tty_name(स्थिर काष्ठा tty_काष्ठा *tty)
अणु
	अगर (!tty) /* Hmm.  शून्य poपूर्णांकer.  That's fun. */
		वापस "NULL tty";
	वापस tty->name;
पूर्ण

EXPORT_SYMBOL(tty_name);

स्थिर अक्षर *tty_driver_name(स्थिर काष्ठा tty_काष्ठा *tty)
अणु
	अगर (!tty || !tty->driver)
		वापस "";
	वापस tty->driver->name;
पूर्ण

अटल पूर्णांक tty_paranoia_check(काष्ठा tty_काष्ठा *tty, काष्ठा inode *inode,
			      स्थिर अक्षर *routine)
अणु
#अगर_घोषित TTY_PARANOIA_CHECK
	अगर (!tty) अणु
		pr_warn("(%d:%d): %s: NULL tty\n",
			imajor(inode), iminor(inode), routine);
		वापस 1;
	पूर्ण
	अगर (tty->magic != TTY_MAGIC) अणु
		pr_warn("(%d:%d): %s: bad magic number\n",
			imajor(inode), iminor(inode), routine);
		वापस 1;
	पूर्ण
#पूर्ण_अगर
	वापस 0;
पूर्ण

/* Caller must hold tty_lock */
अटल पूर्णांक check_tty_count(काष्ठा tty_काष्ठा *tty, स्थिर अक्षर *routine)
अणु
#अगर_घोषित CHECK_TTY_COUNT
	काष्ठा list_head *p;
	पूर्णांक count = 0, kखोलो_count = 0;

	spin_lock(&tty->files_lock);
	list_क्रम_each(p, &tty->tty_files) अणु
		count++;
	पूर्ण
	spin_unlock(&tty->files_lock);
	अगर (tty->driver->type == TTY_DRIVER_TYPE_PTY &&
	    tty->driver->subtype == PTY_TYPE_SLAVE &&
	    tty->link && tty->link->count)
		count++;
	अगर (tty_port_kखोलोed(tty->port))
		kखोलो_count++;
	अगर (tty->count != (count + kखोलो_count)) अणु
		tty_warn(tty, "%s: tty->count(%d) != (#fd's(%d) + #kopen's(%d))\n",
			 routine, tty->count, count, kखोलो_count);
		वापस (count + kखोलो_count);
	पूर्ण
#पूर्ण_अगर
	वापस 0;
पूर्ण

/**
 *	get_tty_driver		-	find device of a tty
 *	@device: device identअगरier
 *	@index: वापसs the index of the tty
 *
 *	This routine वापसs a tty driver काष्ठाure, given a device number
 *	and also passes back the index number.
 *
 *	Locking: caller must hold tty_mutex
 */

अटल काष्ठा tty_driver *get_tty_driver(dev_t device, पूर्णांक *index)
अणु
	काष्ठा tty_driver *p;

	list_क्रम_each_entry(p, &tty_drivers, tty_drivers) अणु
		dev_t base = MKDEV(p->major, p->minor_start);
		अगर (device < base || device >= base + p->num)
			जारी;
		*index = device - base;
		वापस tty_driver_kref_get(p);
	पूर्ण
	वापस शून्य;
पूर्ण

/**
 *	tty_dev_name_to_number	-	वापस dev_t क्रम device name
 *	@name: user space name of device under /dev
 *	@number: poपूर्णांकer to dev_t that this function will populate
 *
 *	This function converts device names like ttyS0 or ttyUSB1 पूर्णांकo dev_t
 *	like (4, 64) or (188, 1). If no corresponding driver is रेजिस्टरed then
 *	the function वापसs -ENODEV.
 *
 *	Locking: this acquires tty_mutex to protect the tty_drivers list from
 *		being modअगरied जबतक we are traversing it, and makes sure to
 *		release it beक्रमe निकासing.
 */
पूर्णांक tty_dev_name_to_number(स्थिर अक्षर *name, dev_t *number)
अणु
	काष्ठा tty_driver *p;
	पूर्णांक ret;
	पूर्णांक index, prefix_length = 0;
	स्थिर अक्षर *str;

	क्रम (str = name; *str && !है_अंक(*str); str++)
		;

	अगर (!*str)
		वापस -EINVAL;

	ret = kstrtoपूर्णांक(str, 10, &index);
	अगर (ret)
		वापस ret;

	prefix_length = str - name;
	mutex_lock(&tty_mutex);

	list_क्रम_each_entry(p, &tty_drivers, tty_drivers)
		अगर (prefix_length == म_माप(p->name) && म_भेदन(name,
					p->name, prefix_length) == 0) अणु
			अगर (index < p->num) अणु
				*number = MKDEV(p->major, p->minor_start + index);
				जाओ out;
			पूर्ण
		पूर्ण

	/* अगर here then driver wasn't found */
	ret = -ENODEV;
out:
	mutex_unlock(&tty_mutex);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(tty_dev_name_to_number);

#अगर_घोषित CONFIG_CONSOLE_POLL

/**
 *	tty_find_polling_driver	-	find device of a polled tty
 *	@name: name string to match
 *	@line: poपूर्णांकer to resulting tty line nr
 *
 *	This routine वापसs a tty driver काष्ठाure, given a name
 *	and the condition that the tty driver is capable of polled
 *	operation.
 */
काष्ठा tty_driver *tty_find_polling_driver(अक्षर *name, पूर्णांक *line)
अणु
	काष्ठा tty_driver *p, *res = शून्य;
	पूर्णांक tty_line = 0;
	पूर्णांक len;
	अक्षर *str, *stp;

	क्रम (str = name; *str; str++)
		अगर ((*str >= '0' && *str <= '9') || *str == ',')
			अवरोध;
	अगर (!*str)
		वापस शून्य;

	len = str - name;
	tty_line = simple_म_से_अदीर्घ(str, &str, 10);

	mutex_lock(&tty_mutex);
	/* Search through the tty devices to look क्रम a match */
	list_क्रम_each_entry(p, &tty_drivers, tty_drivers) अणु
		अगर (!len || म_भेदन(name, p->name, len) != 0)
			जारी;
		stp = str;
		अगर (*stp == ',')
			stp++;
		अगर (*stp == '\0')
			stp = शून्य;

		अगर (tty_line >= 0 && tty_line < p->num && p->ops &&
		    p->ops->poll_init && !p->ops->poll_init(p, tty_line, stp)) अणु
			res = tty_driver_kref_get(p);
			*line = tty_line;
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&tty_mutex);

	वापस res;
पूर्ण
EXPORT_SYMBOL_GPL(tty_find_polling_driver);
#पूर्ण_अगर

अटल sमाप_प्रकार hung_up_tty_पढ़ो(काष्ठा kiocb *iocb, काष्ठा iov_iter *to)
अणु
	वापस 0;
पूर्ण

अटल sमाप_प्रकार hung_up_tty_ग_लिखो(काष्ठा kiocb *iocb, काष्ठा iov_iter *from)
अणु
	वापस -EIO;
पूर्ण

/* No kernel lock held - none needed ;) */
अटल __poll_t hung_up_tty_poll(काष्ठा file *filp, poll_table *रुको)
अणु
	वापस EPOLLIN | EPOLLOUT | EPOLLERR | EPOLLHUP | EPOLLRDNORM | EPOLLWRNORM;
पूर्ण

अटल दीर्घ hung_up_tty_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
		अचिन्हित दीर्घ arg)
अणु
	वापस cmd == TIOCSPGRP ? -ENOTTY : -EIO;
पूर्ण

अटल दीर्घ hung_up_tty_compat_ioctl(काष्ठा file *file,
				     अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	वापस cmd == TIOCSPGRP ? -ENOTTY : -EIO;
पूर्ण

अटल पूर्णांक hung_up_tty_fasync(पूर्णांक fd, काष्ठा file *file, पूर्णांक on)
अणु
	वापस -ENOTTY;
पूर्ण

अटल व्योम tty_show_fdinfo(काष्ठा seq_file *m, काष्ठा file *file)
अणु
	काष्ठा tty_काष्ठा *tty = file_tty(file);

	अगर (tty && tty->ops && tty->ops->show_fdinfo)
		tty->ops->show_fdinfo(tty, m);
पूर्ण

अटल स्थिर काष्ठा file_operations tty_fops = अणु
	.llseek		= no_llseek,
	.पढ़ो_iter	= tty_पढ़ो,
	.ग_लिखो_iter	= tty_ग_लिखो,
	.splice_पढ़ो	= generic_file_splice_पढ़ो,
	.splice_ग_लिखो	= iter_file_splice_ग_लिखो,
	.poll		= tty_poll,
	.unlocked_ioctl	= tty_ioctl,
	.compat_ioctl	= tty_compat_ioctl,
	.खोलो		= tty_खोलो,
	.release	= tty_release,
	.fasync		= tty_fasync,
	.show_fdinfo	= tty_show_fdinfo,
पूर्ण;

अटल स्थिर काष्ठा file_operations console_fops = अणु
	.llseek		= no_llseek,
	.पढ़ो_iter	= tty_पढ़ो,
	.ग_लिखो_iter	= redirected_tty_ग_लिखो,
	.splice_पढ़ो	= generic_file_splice_पढ़ो,
	.splice_ग_लिखो	= iter_file_splice_ग_लिखो,
	.poll		= tty_poll,
	.unlocked_ioctl	= tty_ioctl,
	.compat_ioctl	= tty_compat_ioctl,
	.खोलो		= tty_खोलो,
	.release	= tty_release,
	.fasync		= tty_fasync,
पूर्ण;

अटल स्थिर काष्ठा file_operations hung_up_tty_fops = अणु
	.llseek		= no_llseek,
	.पढ़ो_iter	= hung_up_tty_पढ़ो,
	.ग_लिखो_iter	= hung_up_tty_ग_लिखो,
	.poll		= hung_up_tty_poll,
	.unlocked_ioctl	= hung_up_tty_ioctl,
	.compat_ioctl	= hung_up_tty_compat_ioctl,
	.release	= tty_release,
	.fasync		= hung_up_tty_fasync,
पूर्ण;

अटल DEFINE_SPINLOCK(redirect_lock);
अटल काष्ठा file *redirect;

/**
 *	tty_wakeup	-	request more data
 *	@tty: terminal
 *
 *	Internal and बाह्यal helper क्रम wakeups of tty. This function
 *	inक्रमms the line discipline अगर present that the driver is पढ़ोy
 *	to receive more output data.
 */

व्योम tty_wakeup(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा tty_ldisc *ld;

	अगर (test_bit(TTY_DO_WRITE_WAKEUP, &tty->flags)) अणु
		ld = tty_ldisc_ref(tty);
		अगर (ld) अणु
			अगर (ld->ops->ग_लिखो_wakeup)
				ld->ops->ग_लिखो_wakeup(tty);
			tty_ldisc_deref(ld);
		पूर्ण
	पूर्ण
	wake_up_पूर्णांकerruptible_poll(&tty->ग_लिखो_रुको, EPOLLOUT);
पूर्ण

EXPORT_SYMBOL_GPL(tty_wakeup);

/**
 *	tty_release_redirect	-	Release a redirect on a pty अगर present
 *	@tty: tty device
 *
 *	This is available to the pty code so अगर the master बंदs, अगर the
 *	slave is a redirect it can release the redirect.
 */
अटल काष्ठा file *tty_release_redirect(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा file *f = शून्य;

	spin_lock(&redirect_lock);
	अगर (redirect && file_tty(redirect) == tty) अणु
		f = redirect;
		redirect = शून्य;
	पूर्ण
	spin_unlock(&redirect_lock);

	वापस f;
पूर्ण

/**
 *	__tty_hangup		-	actual handler क्रम hangup events
 *	@tty: tty device
 *	@निकास_session: अगर non-zero, संकेत all क्रमeground group processes
 *
 *	This can be called by a "kworker" kernel thपढ़ो.  That is process
 *	synchronous but करोesn't hold any locks, so we need to make sure we
 *	have the appropriate locks क्रम what we're करोing.
 *
 *	The hangup event clears any pending redirections onto the hung up
 *	device. It ensures future ग_लिखोs will error and it करोes the needed
 *	line discipline hangup and संकेत delivery. The tty object itself
 *	reमुख्यs पूर्णांकact.
 *
 *	Locking:
 *		BTM
 *		  redirect lock क्रम unकरोing redirection
 *		  file list lock क्रम manipulating list of ttys
 *		  tty_ldiscs_lock from called functions
 *		  termios_rwsem resetting termios data
 *		  tasklist_lock to walk task list क्रम hangup event
 *		    ->siglock to protect ->संकेत/->sighand
 */
अटल व्योम __tty_hangup(काष्ठा tty_काष्ठा *tty, पूर्णांक निकास_session)
अणु
	काष्ठा file *cons_filp = शून्य;
	काष्ठा file *filp, *f;
	काष्ठा tty_file_निजी *priv;
	पूर्णांक    बंदcount = 0, n;
	पूर्णांक refs;

	अगर (!tty)
		वापस;

	f = tty_release_redirect(tty);

	tty_lock(tty);

	अगर (test_bit(TTY_HUPPED, &tty->flags)) अणु
		tty_unlock(tty);
		वापस;
	पूर्ण

	/*
	 * Some console devices aren't actually hung up क्रम technical and
	 * historical reasons, which can lead to indefinite पूर्णांकerruptible
	 * sleep in n_tty_पढ़ो().  The following explicitly tells
	 * n_tty_पढ़ो() to पात पढ़ोers.
	 */
	set_bit(TTY_HUPPING, &tty->flags);

	/* inuse_filps is रक्षित by the single tty lock,
	   this really needs to change अगर we want to flush the
	   workqueue with the lock held */
	check_tty_count(tty, "tty_hangup");

	spin_lock(&tty->files_lock);
	/* This अवरोधs क्रम file handles being sent over AF_UNIX sockets ? */
	list_क्रम_each_entry(priv, &tty->tty_files, list) अणु
		filp = priv->file;
		अगर (filp->f_op->ग_लिखो_iter == redirected_tty_ग_लिखो)
			cons_filp = filp;
		अगर (filp->f_op->ग_लिखो_iter != tty_ग_लिखो)
			जारी;
		बंदcount++;
		__tty_fasync(-1, filp, 0);	/* can't block */
		filp->f_op = &hung_up_tty_fops;
	पूर्ण
	spin_unlock(&tty->files_lock);

	refs = tty_संकेत_session_leader(tty, निकास_session);
	/* Account क्रम the p->संकेत references we समाप्तed */
	जबतक (refs--)
		tty_kref_put(tty);

	tty_ldisc_hangup(tty, cons_filp != शून्य);

	spin_lock_irq(&tty->ctrl_lock);
	clear_bit(TTY_THROTTLED, &tty->flags);
	clear_bit(TTY_DO_WRITE_WAKEUP, &tty->flags);
	put_pid(tty->session);
	put_pid(tty->pgrp);
	tty->session = शून्य;
	tty->pgrp = शून्य;
	tty->ctrl_status = 0;
	spin_unlock_irq(&tty->ctrl_lock);

	/*
	 * If one of the devices matches a console poपूर्णांकer, we
	 * cannot just call hangup() because that will cause
	 * tty->count and state->count to go out of sync.
	 * So we just call बंद() the right number of बार.
	 */
	अगर (cons_filp) अणु
		अगर (tty->ops->बंद)
			क्रम (n = 0; n < बंदcount; n++)
				tty->ops->बंद(tty, cons_filp);
	पूर्ण अन्यथा अगर (tty->ops->hangup)
		tty->ops->hangup(tty);
	/*
	 * We करोn't want to have driver/ldisc पूर्णांकeractions beyond the ones
	 * we did here. The driver layer expects no calls after ->hangup()
	 * from the ldisc side, which is now guaranteed.
	 */
	set_bit(TTY_HUPPED, &tty->flags);
	clear_bit(TTY_HUPPING, &tty->flags);
	tty_unlock(tty);

	अगर (f)
		fput(f);
पूर्ण

अटल व्योम करो_tty_hangup(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा tty_काष्ठा *tty =
		container_of(work, काष्ठा tty_काष्ठा, hangup_work);

	__tty_hangup(tty, 0);
पूर्ण

/**
 *	tty_hangup		-	trigger a hangup event
 *	@tty: tty to hangup
 *
 *	A carrier loss (भव or otherwise) has occurred on this like
 *	schedule a hangup sequence to run after this event.
 */

व्योम tty_hangup(काष्ठा tty_काष्ठा *tty)
अणु
	tty_debug_hangup(tty, "hangup\n");
	schedule_work(&tty->hangup_work);
पूर्ण

EXPORT_SYMBOL(tty_hangup);

/**
 *	tty_vhangup		-	process vhangup
 *	@tty: tty to hangup
 *
 *	The user has asked via प्रणाली call क्रम the terminal to be hung up.
 *	We करो this synchronously so that when the syscall वापसs the process
 *	is complete. That guarantee is necessary क्रम security reasons.
 */

व्योम tty_vhangup(काष्ठा tty_काष्ठा *tty)
अणु
	tty_debug_hangup(tty, "vhangup\n");
	__tty_hangup(tty, 0);
पूर्ण

EXPORT_SYMBOL(tty_vhangup);


/**
 *	tty_vhangup_self	-	process vhangup क्रम own ctty
 *
 *	Perक्रमm a vhangup on the current controlling tty
 */

व्योम tty_vhangup_self(व्योम)
अणु
	काष्ठा tty_काष्ठा *tty;

	tty = get_current_tty();
	अगर (tty) अणु
		tty_vhangup(tty);
		tty_kref_put(tty);
	पूर्ण
पूर्ण

/**
 *	tty_vhangup_session		-	hangup session leader निकास
 *	@tty: tty to hangup
 *
 *	The session leader is निकासing and hanging up its controlling terminal.
 *	Every process in the क्रमeground process group is संकेतled SIGHUP.
 *
 *	We करो this synchronously so that when the syscall वापसs the process
 *	is complete. That guarantee is necessary क्रम security reasons.
 */

व्योम tty_vhangup_session(काष्ठा tty_काष्ठा *tty)
अणु
	tty_debug_hangup(tty, "session hangup\n");
	__tty_hangup(tty, 1);
पूर्ण

/**
 *	tty_hung_up_p		-	was tty hung up
 *	@filp: file poपूर्णांकer of tty
 *
 *	Return true अगर the tty has been subject to a vhangup or a carrier
 *	loss
 */

पूर्णांक tty_hung_up_p(काष्ठा file *filp)
अणु
	वापस (filp && filp->f_op == &hung_up_tty_fops);
पूर्ण

EXPORT_SYMBOL(tty_hung_up_p);

/**
 *	stop_tty	-	propagate flow control
 *	@tty: tty to stop
 *
 *	Perक्रमm flow control to the driver. May be called
 *	on an alपढ़ोy stopped device and will not re-call the driver
 *	method.
 *
 *	This functionality is used by both the line disciplines क्रम
 *	halting incoming flow and by the driver. It may thereक्रमe be
 *	called from any context, may be under the tty atomic_ग_लिखो_lock
 *	but not always.
 *
 *	Locking:
 *		flow_lock
 */

व्योम __stop_tty(काष्ठा tty_काष्ठा *tty)
अणु
	अगर (tty->stopped)
		वापस;
	tty->stopped = 1;
	अगर (tty->ops->stop)
		tty->ops->stop(tty);
पूर्ण

व्योम stop_tty(काष्ठा tty_काष्ठा *tty)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&tty->flow_lock, flags);
	__stop_tty(tty);
	spin_unlock_irqrestore(&tty->flow_lock, flags);
पूर्ण
EXPORT_SYMBOL(stop_tty);

/**
 *	start_tty	-	propagate flow control
 *	@tty: tty to start
 *
 *	Start a tty that has been stopped अगर at all possible. If this
 *	tty was previous stopped and is now being started, the driver
 *	start method is invoked and the line discipline woken.
 *
 *	Locking:
 *		flow_lock
 */

व्योम __start_tty(काष्ठा tty_काष्ठा *tty)
अणु
	अगर (!tty->stopped || tty->flow_stopped)
		वापस;
	tty->stopped = 0;
	अगर (tty->ops->start)
		tty->ops->start(tty);
	tty_wakeup(tty);
पूर्ण

व्योम start_tty(काष्ठा tty_काष्ठा *tty)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&tty->flow_lock, flags);
	__start_tty(tty);
	spin_unlock_irqrestore(&tty->flow_lock, flags);
पूर्ण
EXPORT_SYMBOL(start_tty);

अटल व्योम tty_update_समय(काष्ठा बारpec64 *समय)
अणु
	समय64_t sec = kसमय_get_real_seconds();

	/*
	 * We only care अगर the two values dअगरfer in anything other than the
	 * lower three bits (i.e every 8 seconds).  If so, then we can update
	 * the समय of the tty device, otherwise it could be स्थिरruded as a
	 * security leak to let userspace know the exact timing of the tty.
	 */
	अगर ((sec ^ समय->tv_sec) & ~7)
		समय->tv_sec = sec;
पूर्ण

/*
 * Iterate on the ldisc ->पढ़ो() function until we've gotten all
 * the data the ldisc has क्रम us.
 *
 * The "cookie" is something that the ldisc पढ़ो function can fill
 * in to let us know that there is more data to be had.
 *
 * We promise to जारी to call the ldisc until it stops वापसing
 * data or clears the cookie. The cookie may be something that the
 * ldisc मुख्यtains state क्रम and needs to मुक्त.
 */
अटल पूर्णांक iterate_tty_पढ़ो(काष्ठा tty_ldisc *ld, काष्ठा tty_काष्ठा *tty,
		काष्ठा file *file, काष्ठा iov_iter *to)
अणु
	पूर्णांक retval = 0;
	व्योम *cookie = शून्य;
	अचिन्हित दीर्घ offset = 0;
	अक्षर kernel_buf[64];
	माप_प्रकार count = iov_iter_count(to);

	करो अणु
		पूर्णांक size, copied;

		size = count > माप(kernel_buf) ? माप(kernel_buf) : count;
		size = ld->ops->पढ़ो(tty, file, kernel_buf, size, &cookie, offset);
		अगर (!size)
			अवरोध;

		अगर (size < 0) अणु
			/* Did we have an earlier error (ie -EFAULT)? */
			अगर (retval)
				अवरोध;
			retval = size;

			/*
			 * -EOVERFLOW means we didn't have enough space
			 * क्रम a whole packet, and we shouldn't वापस
			 * a partial result.
			 */
			अगर (retval == -EOVERFLOW)
				offset = 0;
			अवरोध;
		पूर्ण

		copied = copy_to_iter(kernel_buf, size, to);
		offset += copied;
		count -= copied;

		/*
		 * If the user copy failed, we still need to करो another ->पढ़ो()
		 * call अगर we had a cookie to let the ldisc clear up.
		 *
		 * But make sure size is zeroed.
		 */
		अगर (unlikely(copied != size)) अणु
			count = 0;
			retval = -EFAULT;
		पूर्ण
	पूर्ण जबतक (cookie);

	/* We always clear tty buffer in हाल they contained passwords */
	memzero_explicit(kernel_buf, माप(kernel_buf));
	वापस offset ? offset : retval;
पूर्ण


/**
 *	tty_पढ़ो	-	पढ़ो method क्रम tty device files
 *	@file: poपूर्णांकer to tty file
 *	@buf: user buffer
 *	@count: size of user buffer
 *	@ppos: unused
 *
 *	Perक्रमm the पढ़ो प्रणाली call function on this terminal device. Checks
 *	क्रम hung up devices beक्रमe calling the line discipline method.
 *
 *	Locking:
 *		Locks the line discipline पूर्णांकernally जबतक needed. Multiple
 *	पढ़ो calls may be outstanding in parallel.
 */

अटल sमाप_प्रकार tty_पढ़ो(काष्ठा kiocb *iocb, काष्ठा iov_iter *to)
अणु
	पूर्णांक i;
	काष्ठा file *file = iocb->ki_filp;
	काष्ठा inode *inode = file_inode(file);
	काष्ठा tty_काष्ठा *tty = file_tty(file);
	काष्ठा tty_ldisc *ld;

	अगर (tty_paranoia_check(tty, inode, "tty_read"))
		वापस -EIO;
	अगर (!tty || tty_io_error(tty))
		वापस -EIO;

	/* We want to रुको क्रम the line discipline to sort out in this
	   situation */
	ld = tty_ldisc_ref_रुको(tty);
	अगर (!ld)
		वापस hung_up_tty_पढ़ो(iocb, to);
	i = -EIO;
	अगर (ld->ops->पढ़ो)
		i = iterate_tty_पढ़ो(ld, tty, file, to);
	tty_ldisc_deref(ld);

	अगर (i > 0)
		tty_update_समय(&inode->i_aसमय);

	वापस i;
पूर्ण

अटल व्योम tty_ग_लिखो_unlock(काष्ठा tty_काष्ठा *tty)
अणु
	mutex_unlock(&tty->atomic_ग_लिखो_lock);
	wake_up_पूर्णांकerruptible_poll(&tty->ग_लिखो_रुको, EPOLLOUT);
पूर्ण

अटल पूर्णांक tty_ग_लिखो_lock(काष्ठा tty_काष्ठा *tty, पूर्णांक ndelay)
अणु
	अगर (!mutex_trylock(&tty->atomic_ग_लिखो_lock)) अणु
		अगर (ndelay)
			वापस -EAGAIN;
		अगर (mutex_lock_पूर्णांकerruptible(&tty->atomic_ग_लिखो_lock))
			वापस -ERESTARTSYS;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Split ग_लिखोs up in sane blocksizes to aव्योम
 * denial-of-service type attacks
 */
अटल अंतरभूत sमाप_प्रकार करो_tty_ग_लिखो(
	sमाप_प्रकार (*ग_लिखो)(काष्ठा tty_काष्ठा *, काष्ठा file *, स्थिर अचिन्हित अक्षर *, माप_प्रकार),
	काष्ठा tty_काष्ठा *tty,
	काष्ठा file *file,
	काष्ठा iov_iter *from)
अणु
	माप_प्रकार count = iov_iter_count(from);
	sमाप_प्रकार ret, written = 0;
	अचिन्हित पूर्णांक chunk;

	ret = tty_ग_लिखो_lock(tty, file->f_flags & O_NDELAY);
	अगर (ret < 0)
		वापस ret;

	/*
	 * We chunk up ग_लिखोs पूर्णांकo a temporary buffer. This
	 * simplअगरies low-level drivers immensely, since they
	 * करोn't have locking issues and user mode accesses.
	 *
	 * But अगर TTY_NO_WRITE_SPLIT is set, we should use a
	 * big chunk-size..
	 *
	 * The शेष chunk-size is 2kB, because the NTTY
	 * layer has problems with bigger chunks. It will
	 * claim to be able to handle more अक्षरacters than
	 * it actually करोes.
	 *
	 * FIXME: This can probably go away now except that 64K chunks
	 * are too likely to fail unless चयनed to vदो_स्मृति...
	 */
	chunk = 2048;
	अगर (test_bit(TTY_NO_WRITE_SPLIT, &tty->flags))
		chunk = 65536;
	अगर (count < chunk)
		chunk = count;

	/* ग_लिखो_buf/ग_लिखो_cnt is रक्षित by the atomic_ग_लिखो_lock mutex */
	अगर (tty->ग_लिखो_cnt < chunk) अणु
		अचिन्हित अक्षर *buf_chunk;

		अगर (chunk < 1024)
			chunk = 1024;

		buf_chunk = kदो_स्मृति(chunk, GFP_KERNEL);
		अगर (!buf_chunk) अणु
			ret = -ENOMEM;
			जाओ out;
		पूर्ण
		kमुक्त(tty->ग_लिखो_buf);
		tty->ग_लिखो_cnt = chunk;
		tty->ग_लिखो_buf = buf_chunk;
	पूर्ण

	/* Do the ग_लिखो .. */
	क्रम (;;) अणु
		माप_प्रकार size = count;
		अगर (size > chunk)
			size = chunk;

		ret = -EFAULT;
		अगर (copy_from_iter(tty->ग_लिखो_buf, size, from) != size)
			अवरोध;

		ret = ग_लिखो(tty, file, tty->ग_लिखो_buf, size);
		अगर (ret <= 0)
			अवरोध;

		written += ret;
		अगर (ret > size)
			अवरोध;

		/* FIXME! Have Al check this! */
		अगर (ret != size)
			iov_iter_revert(from, size-ret);

		count -= ret;
		अगर (!count)
			अवरोध;
		ret = -ERESTARTSYS;
		अगर (संकेत_pending(current))
			अवरोध;
		cond_resched();
	पूर्ण
	अगर (written) अणु
		tty_update_समय(&file_inode(file)->i_mसमय);
		ret = written;
	पूर्ण
out:
	tty_ग_लिखो_unlock(tty);
	वापस ret;
पूर्ण

/**
 * tty_ग_लिखो_message - ग_लिखो a message to a certain tty, not just the console.
 * @tty: the destination tty_काष्ठा
 * @msg: the message to ग_लिखो
 *
 * This is used क्रम messages that need to be redirected to a specअगरic tty.
 * We करोn't put it पूर्णांकo the syslog queue right now maybe in the future अगर
 * really needed.
 *
 * We must still hold the BTM and test the CLOSING flag क्रम the moment.
 */

व्योम tty_ग_लिखो_message(काष्ठा tty_काष्ठा *tty, अक्षर *msg)
अणु
	अगर (tty) अणु
		mutex_lock(&tty->atomic_ग_लिखो_lock);
		tty_lock(tty);
		अगर (tty->ops->ग_लिखो && tty->count > 0)
			tty->ops->ग_लिखो(tty, msg, म_माप(msg));
		tty_unlock(tty);
		tty_ग_लिखो_unlock(tty);
	पूर्ण
	वापस;
पूर्ण


/**
 *	tty_ग_लिखो		-	ग_लिखो method क्रम tty device file
 *	@file: tty file poपूर्णांकer
 *	@buf: user data to ग_लिखो
 *	@count: bytes to ग_लिखो
 *	@ppos: unused
 *
 *	Write data to a tty device via the line discipline.
 *
 *	Locking:
 *		Locks the line discipline as required
 *		Writes to the tty driver are serialized by the atomic_ग_लिखो_lock
 *	and are then processed in chunks to the device. The line discipline
 *	ग_लिखो method will not be invoked in parallel क्रम each device.
 */

अटल sमाप_प्रकार file_tty_ग_लिखो(काष्ठा file *file, काष्ठा kiocb *iocb, काष्ठा iov_iter *from)
अणु
	काष्ठा tty_काष्ठा *tty = file_tty(file);
 	काष्ठा tty_ldisc *ld;
	sमाप_प्रकार ret;

	अगर (tty_paranoia_check(tty, file_inode(file), "tty_write"))
		वापस -EIO;
	अगर (!tty || !tty->ops->ग_लिखो ||	tty_io_error(tty))
			वापस -EIO;
	/* Short term debug to catch buggy drivers */
	अगर (tty->ops->ग_लिखो_room == शून्य)
		tty_err(tty, "missing write_room method\n");
	ld = tty_ldisc_ref_रुको(tty);
	अगर (!ld)
		वापस hung_up_tty_ग_लिखो(iocb, from);
	अगर (!ld->ops->ग_लिखो)
		ret = -EIO;
	अन्यथा
		ret = करो_tty_ग_लिखो(ld->ops->ग_लिखो, tty, file, from);
	tty_ldisc_deref(ld);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार tty_ग_लिखो(काष्ठा kiocb *iocb, काष्ठा iov_iter *from)
अणु
	वापस file_tty_ग_लिखो(iocb->ki_filp, iocb, from);
पूर्ण

sमाप_प्रकार redirected_tty_ग_लिखो(काष्ठा kiocb *iocb, काष्ठा iov_iter *iter)
अणु
	काष्ठा file *p = शून्य;

	spin_lock(&redirect_lock);
	अगर (redirect)
		p = get_file(redirect);
	spin_unlock(&redirect_lock);

	/*
	 * We know the redirected tty is just another tty, we can can
	 * call file_tty_ग_लिखो() directly with that file poपूर्णांकer.
	 */
	अगर (p) अणु
		sमाप_प्रकार res;
		res = file_tty_ग_लिखो(p, iocb, iter);
		fput(p);
		वापस res;
	पूर्ण
	वापस tty_ग_लिखो(iocb, iter);
पूर्ण

/*
 *	tty_send_xअक्षर	-	send priority अक्षरacter
 *
 *	Send a high priority अक्षरacter to the tty even अगर stopped
 *
 *	Locking: none क्रम xअक्षर method, ग_लिखो ordering क्रम ग_लिखो method.
 */

पूर्णांक tty_send_xअक्षर(काष्ठा tty_काष्ठा *tty, अक्षर ch)
अणु
	पूर्णांक	was_stopped = tty->stopped;

	अगर (tty->ops->send_xअक्षर) अणु
		करोwn_पढ़ो(&tty->termios_rwsem);
		tty->ops->send_xअक्षर(tty, ch);
		up_पढ़ो(&tty->termios_rwsem);
		वापस 0;
	पूर्ण

	अगर (tty_ग_लिखो_lock(tty, 0) < 0)
		वापस -ERESTARTSYS;

	करोwn_पढ़ो(&tty->termios_rwsem);
	अगर (was_stopped)
		start_tty(tty);
	tty->ops->ग_लिखो(tty, &ch, 1);
	अगर (was_stopped)
		stop_tty(tty);
	up_पढ़ो(&tty->termios_rwsem);
	tty_ग_लिखो_unlock(tty);
	वापस 0;
पूर्ण

/**
 *	pty_line_name	-	generate name क्रम a pty
 *	@driver: the tty driver in use
 *	@index: the minor number
 *	@p: output buffer of at least 6 bytes
 *
 *	Generate a name from a driver reference and ग_लिखो it to the output
 *	buffer.
 *
 *	Locking: None
 */
अटल व्योम pty_line_name(काष्ठा tty_driver *driver, पूर्णांक index, अक्षर *p)
अणु
	अटल स्थिर अक्षर ptyअक्षर[] = "pqrstuvwxyzabcde";
	पूर्णांक i = index + driver->name_base;
	/* ->name is initialized to "ttyp", but "tty" is expected */
	प्र_लिखो(p, "%s%c%x",
		driver->subtype == PTY_TYPE_SLAVE ? "tty" : driver->name,
		ptyअक्षर[i >> 4 & 0xf], i & 0xf);
पूर्ण

/**
 *	tty_line_name	-	generate name क्रम a tty
 *	@driver: the tty driver in use
 *	@index: the minor number
 *	@p: output buffer of at least 7 bytes
 *
 *	Generate a name from a driver reference and ग_लिखो it to the output
 *	buffer.
 *
 *	Locking: None
 */
अटल sमाप_प्रकार tty_line_name(काष्ठा tty_driver *driver, पूर्णांक index, अक्षर *p)
अणु
	अगर (driver->flags & TTY_DRIVER_UNNUMBERED_NODE)
		वापस प्र_लिखो(p, "%s", driver->name);
	अन्यथा
		वापस प्र_लिखो(p, "%s%d", driver->name,
			       index + driver->name_base);
पूर्ण

/**
 *	tty_driver_lookup_tty() - find an existing tty, अगर any
 *	@driver: the driver क्रम the tty
 *	@file:   file object
 *	@idx:	 the minor number
 *
 *	Return the tty, अगर found. If not found, वापस शून्य or ERR_PTR() अगर the
 *	driver lookup() method वापसs an error.
 *
 *	Locking: tty_mutex must be held. If the tty is found, bump the tty kref.
 */
अटल काष्ठा tty_काष्ठा *tty_driver_lookup_tty(काष्ठा tty_driver *driver,
		काष्ठा file *file, पूर्णांक idx)
अणु
	काष्ठा tty_काष्ठा *tty;

	अगर (driver->ops->lookup)
		अगर (!file)
			tty = ERR_PTR(-EIO);
		अन्यथा
			tty = driver->ops->lookup(driver, file, idx);
	अन्यथा
		tty = driver->ttys[idx];

	अगर (!IS_ERR(tty))
		tty_kref_get(tty);
	वापस tty;
पूर्ण

/**
 *	tty_init_termios	-  helper क्रम termios setup
 *	@tty: the tty to set up
 *
 *	Initialise the termios काष्ठाure क्रम this tty. This runs under
 *	the tty_mutex currently so we can be relaxed about ordering.
 */

व्योम tty_init_termios(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा ktermios *tp;
	पूर्णांक idx = tty->index;

	अगर (tty->driver->flags & TTY_DRIVER_RESET_TERMIOS)
		tty->termios = tty->driver->init_termios;
	अन्यथा अणु
		/* Check क्रम lazy saved data */
		tp = tty->driver->termios[idx];
		अगर (tp != शून्य) अणु
			tty->termios = *tp;
			tty->termios.c_line  = tty->driver->init_termios.c_line;
		पूर्ण अन्यथा
			tty->termios = tty->driver->init_termios;
	पूर्ण
	/* Compatibility until drivers always set this */
	tty->termios.c_ispeed = tty_termios_input_baud_rate(&tty->termios);
	tty->termios.c_ospeed = tty_termios_baud_rate(&tty->termios);
पूर्ण
EXPORT_SYMBOL_GPL(tty_init_termios);

पूर्णांक tty_standard_install(काष्ठा tty_driver *driver, काष्ठा tty_काष्ठा *tty)
अणु
	tty_init_termios(tty);
	tty_driver_kref_get(driver);
	tty->count++;
	driver->ttys[tty->index] = tty;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(tty_standard_install);

/**
 *	tty_driver_install_tty() - install a tty entry in the driver
 *	@driver: the driver क्रम the tty
 *	@tty: the tty
 *
 *	Install a tty object पूर्णांकo the driver tables. The tty->index field
 *	will be set by the समय this is called. This method is responsible
 *	क्रम ensuring any need additional काष्ठाures are allocated and
 *	configured.
 *
 *	Locking: tty_mutex क्रम now
 */
अटल पूर्णांक tty_driver_install_tty(काष्ठा tty_driver *driver,
						काष्ठा tty_काष्ठा *tty)
अणु
	वापस driver->ops->install ? driver->ops->install(driver, tty) :
		tty_standard_install(driver, tty);
पूर्ण

/**
 *	tty_driver_हटाओ_tty() - हटाओ a tty from the driver tables
 *	@driver: the driver क्रम the tty
 *	@tty: tty to हटाओ
 *
 *	Remvoe a tty object from the driver tables. The tty->index field
 *	will be set by the समय this is called.
 *
 *	Locking: tty_mutex क्रम now
 */
अटल व्योम tty_driver_हटाओ_tty(काष्ठा tty_driver *driver, काष्ठा tty_काष्ठा *tty)
अणु
	अगर (driver->ops->हटाओ)
		driver->ops->हटाओ(driver, tty);
	अन्यथा
		driver->ttys[tty->index] = शून्य;
पूर्ण

/**
 *	tty_reखोलो()	- fast re-खोलो of an खोलो tty
 *	@tty: the tty to खोलो
 *
 *	Return 0 on success, -त्रुटि_सं on error.
 *	Re-खोलोs on master ptys are not allowed and वापस -EIO.
 *
 *	Locking: Caller must hold tty_lock
 */
अटल पूर्णांक tty_reखोलो(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा tty_driver *driver = tty->driver;
	काष्ठा tty_ldisc *ld;
	पूर्णांक retval = 0;

	अगर (driver->type == TTY_DRIVER_TYPE_PTY &&
	    driver->subtype == PTY_TYPE_MASTER)
		वापस -EIO;

	अगर (!tty->count)
		वापस -EAGAIN;

	अगर (test_bit(TTY_EXCLUSIVE, &tty->flags) && !capable(CAP_SYS_ADMIN))
		वापस -EBUSY;

	ld = tty_ldisc_ref_रुको(tty);
	अगर (ld) अणु
		tty_ldisc_deref(ld);
	पूर्ण अन्यथा अणु
		retval = tty_ldisc_lock(tty, 5 * HZ);
		अगर (retval)
			वापस retval;

		अगर (!tty->ldisc)
			retval = tty_ldisc_reinit(tty, tty->termios.c_line);
		tty_ldisc_unlock(tty);
	पूर्ण

	अगर (retval == 0)
		tty->count++;

	वापस retval;
पूर्ण

/**
 *	tty_init_dev		-	initialise a tty device
 *	@driver: tty driver we are खोलोing a device on
 *	@idx: device index
 *
 *	Prepare a tty device. This may not be a "new" clean device but
 *	could also be an active device. The pty drivers require special
 *	handling because of this.
 *
 *	Locking:
 *		The function is called under the tty_mutex, which
 *	protects us from the tty काष्ठा or driver itself going away.
 *
 *	On निकास the tty device has the line discipline attached and
 *	a reference count of 1. If a pair was created क्रम pty/tty use
 *	and the other was a pty master then it too has a reference count of 1.
 *
 * WSH 06/09/97: Rewritten to हटाओ races and properly clean up after a
 * failed खोलो.  The new code protects the खोलो with a mutex, so it's
 * really quite straightक्रमward.  The mutex locking can probably be
 * relaxed क्रम the (most common) हाल of reखोलोing a tty.
 *
 *	Return: वापसed tty काष्ठाure
 */

काष्ठा tty_काष्ठा *tty_init_dev(काष्ठा tty_driver *driver, पूर्णांक idx)
अणु
	काष्ठा tty_काष्ठा *tty;
	पूर्णांक retval;

	/*
	 * First समय खोलो is complex, especially क्रम PTY devices.
	 * This code guarantees that either everything succeeds and the
	 * TTY is पढ़ोy क्रम operation, or अन्यथा the table slots are vacated
	 * and the allocated memory released.  (Except that the termios
	 * may be retained.)
	 */

	अगर (!try_module_get(driver->owner))
		वापस ERR_PTR(-ENODEV);

	tty = alloc_tty_काष्ठा(driver, idx);
	अगर (!tty) अणु
		retval = -ENOMEM;
		जाओ err_module_put;
	पूर्ण

	tty_lock(tty);
	retval = tty_driver_install_tty(driver, tty);
	अगर (retval < 0)
		जाओ err_मुक्त_tty;

	अगर (!tty->port)
		tty->port = driver->ports[idx];

	अगर (WARN_RATELIMIT(!tty->port,
			"%s: %s driver does not set tty->port. This would crash the kernel. Fix the driver!\n",
			__func__, tty->driver->name)) अणु
		retval = -EINVAL;
		जाओ err_release_lock;
	पूर्ण

	retval = tty_ldisc_lock(tty, 5 * HZ);
	अगर (retval)
		जाओ err_release_lock;
	tty->port->itty = tty;

	/*
	 * Structures all installed ... call the ldisc खोलो routines.
	 * If we fail here just call release_tty to clean up.  No need
	 * to decrement the use counts, as release_tty करोesn't care.
	 */
	retval = tty_ldisc_setup(tty, tty->link);
	अगर (retval)
		जाओ err_release_tty;
	tty_ldisc_unlock(tty);
	/* Return the tty locked so that it cannot vanish under the caller */
	वापस tty;

err_मुक्त_tty:
	tty_unlock(tty);
	मुक्त_tty_काष्ठा(tty);
err_module_put:
	module_put(driver->owner);
	वापस ERR_PTR(retval);

	/* call the tty release_tty routine to clean out this slot */
err_release_tty:
	tty_ldisc_unlock(tty);
	tty_info_ratelimited(tty, "ldisc open failed (%d), clearing slot %d\n",
			     retval, idx);
err_release_lock:
	tty_unlock(tty);
	release_tty(tty, idx);
	वापस ERR_PTR(retval);
पूर्ण

/**
 * tty_save_termios() - save tty termios data in driver table
 * @tty: tty whose termios data to save
 *
 * Locking: Caller guarantees serialisation with tty_init_termios().
 */
व्योम tty_save_termios(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा ktermios *tp;
	पूर्णांक idx = tty->index;

	/* If the port is going to reset then it has no termios to save */
	अगर (tty->driver->flags & TTY_DRIVER_RESET_TERMIOS)
		वापस;

	/* Stash the termios data */
	tp = tty->driver->termios[idx];
	अगर (tp == शून्य) अणु
		tp = kदो_स्मृति(माप(*tp), GFP_KERNEL);
		अगर (tp == शून्य)
			वापस;
		tty->driver->termios[idx] = tp;
	पूर्ण
	*tp = tty->termios;
पूर्ण
EXPORT_SYMBOL_GPL(tty_save_termios);

/**
 *	tty_flush_works		-	flush all works of a tty/pty pair
 *	@tty: tty device to flush works क्रम (or either end of a pty pair)
 *
 *	Sync flush all works beदीर्घing to @tty (and the 'other' tty).
 */
अटल व्योम tty_flush_works(काष्ठा tty_काष्ठा *tty)
अणु
	flush_work(&tty->SAK_work);
	flush_work(&tty->hangup_work);
	अगर (tty->link) अणु
		flush_work(&tty->link->SAK_work);
		flush_work(&tty->link->hangup_work);
	पूर्ण
पूर्ण

/**
 *	release_one_tty		-	release tty काष्ठाure memory
 *	@work: work of tty we are obliterating
 *
 *	Releases memory associated with a tty काष्ठाure, and clears out the
 *	driver table slots. This function is called when a device is no दीर्घer
 *	in use. It also माला_लो called when setup of a device fails.
 *
 *	Locking:
 *		takes the file list lock पूर्णांकernally when working on the list
 *	of ttys that the driver keeps.
 *
 *	This method माला_लो called from a work queue so that the driver निजी
 *	cleanup ops can sleep (needed क्रम USB at least)
 */
अटल व्योम release_one_tty(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा tty_काष्ठा *tty =
		container_of(work, काष्ठा tty_काष्ठा, hangup_work);
	काष्ठा tty_driver *driver = tty->driver;
	काष्ठा module *owner = driver->owner;

	अगर (tty->ops->cleanup)
		tty->ops->cleanup(tty);

	tty->magic = 0;
	tty_driver_kref_put(driver);
	module_put(owner);

	spin_lock(&tty->files_lock);
	list_del_init(&tty->tty_files);
	spin_unlock(&tty->files_lock);

	put_pid(tty->pgrp);
	put_pid(tty->session);
	मुक्त_tty_काष्ठा(tty);
पूर्ण

अटल व्योम queue_release_one_tty(काष्ठा kref *kref)
अणु
	काष्ठा tty_काष्ठा *tty = container_of(kref, काष्ठा tty_काष्ठा, kref);

	/* The hangup queue is now मुक्त so we can reuse it rather than
	   waste a chunk of memory क्रम each port */
	INIT_WORK(&tty->hangup_work, release_one_tty);
	schedule_work(&tty->hangup_work);
पूर्ण

/**
 *	tty_kref_put		-	release a tty kref
 *	@tty: tty device
 *
 *	Release a reference to a tty device and अगर need be let the kref
 *	layer deकाष्ठा the object क्रम us
 */

व्योम tty_kref_put(काष्ठा tty_काष्ठा *tty)
अणु
	अगर (tty)
		kref_put(&tty->kref, queue_release_one_tty);
पूर्ण
EXPORT_SYMBOL(tty_kref_put);

/**
 *	release_tty		-	release tty काष्ठाure memory
 *	@tty: tty device release
 *	@idx: index of the tty device release
 *
 *	Release both @tty and a possible linked partner (think pty pair),
 *	and decrement the refcount of the backing module.
 *
 *	Locking:
 *		tty_mutex
 *		takes the file list lock पूर्णांकernally when working on the list
 *	of ttys that the driver keeps.
 *
 */
अटल व्योम release_tty(काष्ठा tty_काष्ठा *tty, पूर्णांक idx)
अणु
	/* This should always be true but check क्रम the moment */
	WARN_ON(tty->index != idx);
	WARN_ON(!mutex_is_locked(&tty_mutex));
	अगर (tty->ops->shutकरोwn)
		tty->ops->shutकरोwn(tty);
	tty_save_termios(tty);
	tty_driver_हटाओ_tty(tty->driver, tty);
	अगर (tty->port)
		tty->port->itty = शून्य;
	अगर (tty->link)
		tty->link->port->itty = शून्य;
	अगर (tty->port)
		tty_buffer_cancel_work(tty->port);
	अगर (tty->link)
		tty_buffer_cancel_work(tty->link->port);

	tty_kref_put(tty->link);
	tty_kref_put(tty);
पूर्ण

/**
 *	tty_release_checks - check a tty beक्रमe real release
 *	@tty: tty to check
 *	@idx: index of the tty
 *
 *	Perक्रमms some paranoid checking beक्रमe true release of the @tty.
 *	This is a no-op unless TTY_PARANOIA_CHECK is defined.
 */
अटल पूर्णांक tty_release_checks(काष्ठा tty_काष्ठा *tty, पूर्णांक idx)
अणु
#अगर_घोषित TTY_PARANOIA_CHECK
	अगर (idx < 0 || idx >= tty->driver->num) अणु
		tty_debug(tty, "bad idx %d\n", idx);
		वापस -1;
	पूर्ण

	/* not much to check क्रम devpts */
	अगर (tty->driver->flags & TTY_DRIVER_DEVPTS_MEM)
		वापस 0;

	अगर (tty != tty->driver->ttys[idx]) अणु
		tty_debug(tty, "bad driver table[%d] = %p\n",
			  idx, tty->driver->ttys[idx]);
		वापस -1;
	पूर्ण
	अगर (tty->driver->other) अणु
		काष्ठा tty_काष्ठा *o_tty = tty->link;

		अगर (o_tty != tty->driver->other->ttys[idx]) अणु
			tty_debug(tty, "bad other table[%d] = %p\n",
				  idx, tty->driver->other->ttys[idx]);
			वापस -1;
		पूर्ण
		अगर (o_tty->link != tty) अणु
			tty_debug(tty, "bad link = %p\n", o_tty->link);
			वापस -1;
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	वापस 0;
पूर्ण

/**
 *      tty_kबंद      -       बंदs tty खोलोed by tty_kखोलो
 *      @tty: tty device
 *
 *      Perक्रमms the final steps to release and मुक्त a tty device. It is the
 *      same as tty_release_काष्ठा except that it also resets TTY_PORT_KOPENED
 *      flag on tty->port.
 */
व्योम tty_kबंद(काष्ठा tty_काष्ठा *tty)
अणु
	/*
	 * Ask the line discipline code to release its काष्ठाures
	 */
	tty_ldisc_release(tty);

	/* Wait क्रम pending work beक्रमe tty deकाष्ठाion commmences */
	tty_flush_works(tty);

	tty_debug_hangup(tty, "freeing structure\n");
	/*
	 * The release_tty function takes care of the details of clearing
	 * the slots and preserving the termios काष्ठाure.
	 */
	mutex_lock(&tty_mutex);
	tty_port_set_kखोलोed(tty->port, 0);
	release_tty(tty, tty->index);
	mutex_unlock(&tty_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(tty_kबंद);

/**
 *	tty_release_काष्ठा	-	release a tty काष्ठा
 *	@tty: tty device
 *	@idx: index of the tty
 *
 *	Perक्रमms the final steps to release and मुक्त a tty device. It is
 *	roughly the reverse of tty_init_dev.
 */
व्योम tty_release_काष्ठा(काष्ठा tty_काष्ठा *tty, पूर्णांक idx)
अणु
	/*
	 * Ask the line discipline code to release its काष्ठाures
	 */
	tty_ldisc_release(tty);

	/* Wait क्रम pending work beक्रमe tty deकाष्ठाion commmences */
	tty_flush_works(tty);

	tty_debug_hangup(tty, "freeing structure\n");
	/*
	 * The release_tty function takes care of the details of clearing
	 * the slots and preserving the termios काष्ठाure.
	 */
	mutex_lock(&tty_mutex);
	release_tty(tty, idx);
	mutex_unlock(&tty_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(tty_release_काष्ठा);

/**
 *	tty_release		-	vfs callback क्रम बंद
 *	@inode: inode of tty
 *	@filp: file poपूर्णांकer क्रम handle to tty
 *
 *	Called the last समय each file handle is बंदd that references
 *	this tty. There may however be several such references.
 *
 *	Locking:
 *		Takes bkl. See tty_release_dev
 *
 * Even releasing the tty काष्ठाures is a tricky business.. We have
 * to be very careful that the काष्ठाures are all released at the
 * same समय, as पूर्णांकerrupts might otherwise get the wrong poपूर्णांकers.
 *
 * WSH 09/09/97: rewritten to aव्योम some nasty race conditions that could
 * lead to द्विगुन मुक्तs or releasing memory still in use.
 */

पूर्णांक tty_release(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा tty_काष्ठा *tty = file_tty(filp);
	काष्ठा tty_काष्ठा *o_tty = शून्य;
	पूर्णांक	करो_sleep, final;
	पूर्णांक	idx;
	दीर्घ	समयout = 0;
	पूर्णांक	once = 1;

	अगर (tty_paranoia_check(tty, inode, __func__))
		वापस 0;

	tty_lock(tty);
	check_tty_count(tty, __func__);

	__tty_fasync(-1, filp, 0);

	idx = tty->index;
	अगर (tty->driver->type == TTY_DRIVER_TYPE_PTY &&
	    tty->driver->subtype == PTY_TYPE_MASTER)
		o_tty = tty->link;

	अगर (tty_release_checks(tty, idx)) अणु
		tty_unlock(tty);
		वापस 0;
	पूर्ण

	tty_debug_hangup(tty, "releasing (count=%d)\n", tty->count);

	अगर (tty->ops->बंद)
		tty->ops->बंद(tty, filp);

	/* If tty is pty master, lock the slave pty (stable lock order) */
	tty_lock_slave(o_tty);

	/*
	 * Sanity check: अगर tty->count is going to zero, there shouldn't be
	 * any रुकोers on tty->पढ़ो_रुको or tty->ग_लिखो_रुको.  We test the
	 * रुको queues and kick everyone out _beक्रमe_ actually starting to
	 * बंद.  This ensures that we won't block जबतक releasing the tty
	 * काष्ठाure.
	 *
	 * The test क्रम the o_tty closing is necessary, since the master and
	 * slave sides may बंद in any order.  If the slave side बंदs out
	 * first, its count will be one, since the master side holds an खोलो.
	 * Thus this test wouldn't be triggered at the समय the slave बंदd,
	 * so we करो it now.
	 */
	जबतक (1) अणु
		करो_sleep = 0;

		अगर (tty->count <= 1) अणु
			अगर (रुकोqueue_active(&tty->पढ़ो_रुको)) अणु
				wake_up_poll(&tty->पढ़ो_रुको, EPOLLIN);
				करो_sleep++;
			पूर्ण
			अगर (रुकोqueue_active(&tty->ग_लिखो_रुको)) अणु
				wake_up_poll(&tty->ग_लिखो_रुको, EPOLLOUT);
				करो_sleep++;
			पूर्ण
		पूर्ण
		अगर (o_tty && o_tty->count <= 1) अणु
			अगर (रुकोqueue_active(&o_tty->पढ़ो_रुको)) अणु
				wake_up_poll(&o_tty->पढ़ो_रुको, EPOLLIN);
				करो_sleep++;
			पूर्ण
			अगर (रुकोqueue_active(&o_tty->ग_लिखो_रुको)) अणु
				wake_up_poll(&o_tty->ग_लिखो_रुको, EPOLLOUT);
				करो_sleep++;
			पूर्ण
		पूर्ण
		अगर (!करो_sleep)
			अवरोध;

		अगर (once) अणु
			once = 0;
			tty_warn(tty, "read/write wait queue active!\n");
		पूर्ण
		schedule_समयout_समाप्तable(समयout);
		अगर (समयout < 120 * HZ)
			समयout = 2 * समयout + 1;
		अन्यथा
			समयout = MAX_SCHEDULE_TIMEOUT;
	पूर्ण

	अगर (o_tty) अणु
		अगर (--o_tty->count < 0) अणु
			tty_warn(tty, "bad slave count (%d)\n", o_tty->count);
			o_tty->count = 0;
		पूर्ण
	पूर्ण
	अगर (--tty->count < 0) अणु
		tty_warn(tty, "bad tty->count (%d)\n", tty->count);
		tty->count = 0;
	पूर्ण

	/*
	 * We've decremented tty->count, so we need to हटाओ this file
	 * descriptor off the tty->tty_files list; this serves two
	 * purposes:
	 *  - check_tty_count sees the correct number of file descriptors
	 *    associated with this tty.
	 *  - करो_tty_hangup no दीर्घer sees this file descriptor as
	 *    something that needs to be handled क्रम hangups.
	 */
	tty_del_file(filp);

	/*
	 * Perक्रमm some housekeeping beक्रमe deciding whether to वापस.
	 *
	 * If _either_ side is closing, make sure there aren't any
	 * processes that still think tty or o_tty is their controlling
	 * tty.
	 */
	अगर (!tty->count) अणु
		पढ़ो_lock(&tasklist_lock);
		session_clear_tty(tty->session);
		अगर (o_tty)
			session_clear_tty(o_tty->session);
		पढ़ो_unlock(&tasklist_lock);
	पूर्ण

	/* check whether both sides are closing ... */
	final = !tty->count && !(o_tty && o_tty->count);

	tty_unlock_slave(o_tty);
	tty_unlock(tty);

	/* At this poपूर्णांक, the tty->count == 0 should ensure a dead tty
	   cannot be re-खोलोed by a racing खोलोer */

	अगर (!final)
		वापस 0;

	tty_debug_hangup(tty, "final close\n");

	tty_release_काष्ठा(tty, idx);
	वापस 0;
पूर्ण

/**
 *	tty_खोलो_current_tty - get locked tty of current task
 *	@device: device number
 *	@filp: file poपूर्णांकer to tty
 *	@वापस: locked tty of the current task अगरf @device is /dev/tty
 *
 *	Perक्रमms a re-खोलो of the current task's controlling tty.
 *
 *	We cannot वापस driver and index like क्रम the other nodes because
 *	devpts will not work then. It expects inodes to be from devpts FS.
 */
अटल काष्ठा tty_काष्ठा *tty_खोलो_current_tty(dev_t device, काष्ठा file *filp)
अणु
	काष्ठा tty_काष्ठा *tty;
	पूर्णांक retval;

	अगर (device != MKDEV(TTYAUX_MAJOR, 0))
		वापस शून्य;

	tty = get_current_tty();
	अगर (!tty)
		वापस ERR_PTR(-ENXIO);

	filp->f_flags |= O_NONBLOCK; /* Don't let /dev/tty block */
	/* noctty = 1; */
	tty_lock(tty);
	tty_kref_put(tty);	/* safe to drop the kref now */

	retval = tty_reखोलो(tty);
	अगर (retval < 0) अणु
		tty_unlock(tty);
		tty = ERR_PTR(retval);
	पूर्ण
	वापस tty;
पूर्ण

/**
 *	tty_lookup_driver - lookup a tty driver क्रम a given device file
 *	@device: device number
 *	@filp: file poपूर्णांकer to tty
 *	@index: index क्रम the device in the @वापस driver
 *	@वापस: driver क्रम this inode (with increased refcount)
 *
 * 	If @वापस is not erroneous, the caller is responsible to decrement the
 * 	refcount by tty_driver_kref_put.
 *
 *	Locking: tty_mutex protects get_tty_driver
 */
अटल काष्ठा tty_driver *tty_lookup_driver(dev_t device, काष्ठा file *filp,
		पूर्णांक *index)
अणु
	काष्ठा tty_driver *driver = शून्य;

	चयन (device) अणु
#अगर_घोषित CONFIG_VT
	हाल MKDEV(TTY_MAJOR, 0): अणु
		बाह्य काष्ठा tty_driver *console_driver;
		driver = tty_driver_kref_get(console_driver);
		*index = fg_console;
		अवरोध;
	पूर्ण
#पूर्ण_अगर
	हाल MKDEV(TTYAUX_MAJOR, 1): अणु
		काष्ठा tty_driver *console_driver = console_device(index);
		अगर (console_driver) अणु
			driver = tty_driver_kref_get(console_driver);
			अगर (driver && filp) अणु
				/* Don't let /dev/console block */
				filp->f_flags |= O_NONBLOCK;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (driver)
			tty_driver_kref_put(driver);
		वापस ERR_PTR(-ENODEV);
	पूर्ण
	शेष:
		driver = get_tty_driver(device, index);
		अगर (!driver)
			वापस ERR_PTR(-ENODEV);
		अवरोध;
	पूर्ण
	वापस driver;
पूर्ण

अटल काष्ठा tty_काष्ठा *tty_kखोलो(dev_t device, पूर्णांक shared)
अणु
	काष्ठा tty_काष्ठा *tty;
	काष्ठा tty_driver *driver;
	पूर्णांक index = -1;

	mutex_lock(&tty_mutex);
	driver = tty_lookup_driver(device, शून्य, &index);
	अगर (IS_ERR(driver)) अणु
		mutex_unlock(&tty_mutex);
		वापस ERR_CAST(driver);
	पूर्ण

	/* check whether we're reखोलोing an existing tty */
	tty = tty_driver_lookup_tty(driver, शून्य, index);
	अगर (IS_ERR(tty) || shared)
		जाओ out;

	अगर (tty) अणु
		/* drop kref from tty_driver_lookup_tty() */
		tty_kref_put(tty);
		tty = ERR_PTR(-EBUSY);
	पूर्ण अन्यथा अणु /* tty_init_dev वापसs tty with the tty_lock held */
		tty = tty_init_dev(driver, index);
		अगर (IS_ERR(tty))
			जाओ out;
		tty_port_set_kखोलोed(tty->port, 1);
	पूर्ण
out:
	mutex_unlock(&tty_mutex);
	tty_driver_kref_put(driver);
	वापस tty;
पूर्ण

/**
 *	tty_kखोलो_exclusive	-	खोलो a tty device क्रम kernel
 *	@device: dev_t of device to खोलो
 *
 *	Opens tty exclusively क्रम kernel. Perक्रमms the driver lookup,
 *	makes sure it's not alपढ़ोy खोलोed and perक्रमms the first-समय
 *	tty initialization.
 *
 *	Returns the locked initialized &tty_काष्ठा
 *
 *	Claims the global tty_mutex to serialize:
 *	  - concurrent first-समय tty initialization
 *	  - concurrent tty driver removal w/ lookup
 *	  - concurrent tty removal from driver table
 */
काष्ठा tty_काष्ठा *tty_kखोलो_exclusive(dev_t device)
अणु
	वापस tty_kखोलो(device, 0);
पूर्ण
EXPORT_SYMBOL_GPL(tty_kखोलो_exclusive);

/**
 *	tty_kखोलो_shared	-	खोलो a tty device क्रम shared in-kernel use
 *	@device: dev_t of device to खोलो
 *
 *	Opens an alपढ़ोy existing tty क्रम in-kernel use. Compared to
 *	tty_kखोलो_exclusive() above it करोesn't ensure to be the only user.
 *
 *	Locking is identical to tty_kखोलो() above.
 */
काष्ठा tty_काष्ठा *tty_kखोलो_shared(dev_t device)
अणु
	वापस tty_kखोलो(device, 1);
पूर्ण
EXPORT_SYMBOL_GPL(tty_kखोलो_shared);

/**
 *	tty_खोलो_by_driver	-	खोलो a tty device
 *	@device: dev_t of device to खोलो
 *	@filp: file poपूर्णांकer to tty
 *
 *	Perक्रमms the driver lookup, checks क्रम a reखोलो, or otherwise
 *	perक्रमms the first-समय tty initialization.
 *
 *	Returns the locked initialized or re-खोलोed &tty_काष्ठा
 *
 *	Claims the global tty_mutex to serialize:
 *	  - concurrent first-समय tty initialization
 *	  - concurrent tty driver removal w/ lookup
 *	  - concurrent tty removal from driver table
 */
अटल काष्ठा tty_काष्ठा *tty_खोलो_by_driver(dev_t device,
					     काष्ठा file *filp)
अणु
	काष्ठा tty_काष्ठा *tty;
	काष्ठा tty_driver *driver = शून्य;
	पूर्णांक index = -1;
	पूर्णांक retval;

	mutex_lock(&tty_mutex);
	driver = tty_lookup_driver(device, filp, &index);
	अगर (IS_ERR(driver)) अणु
		mutex_unlock(&tty_mutex);
		वापस ERR_CAST(driver);
	पूर्ण

	/* check whether we're reखोलोing an existing tty */
	tty = tty_driver_lookup_tty(driver, filp, index);
	अगर (IS_ERR(tty)) अणु
		mutex_unlock(&tty_mutex);
		जाओ out;
	पूर्ण

	अगर (tty) अणु
		अगर (tty_port_kखोलोed(tty->port)) अणु
			tty_kref_put(tty);
			mutex_unlock(&tty_mutex);
			tty = ERR_PTR(-EBUSY);
			जाओ out;
		पूर्ण
		mutex_unlock(&tty_mutex);
		retval = tty_lock_पूर्णांकerruptible(tty);
		tty_kref_put(tty);  /* drop kref from tty_driver_lookup_tty() */
		अगर (retval) अणु
			अगर (retval == -EINTR)
				retval = -ERESTARTSYS;
			tty = ERR_PTR(retval);
			जाओ out;
		पूर्ण
		retval = tty_reखोलो(tty);
		अगर (retval < 0) अणु
			tty_unlock(tty);
			tty = ERR_PTR(retval);
		पूर्ण
	पूर्ण अन्यथा अणु /* Returns with the tty_lock held क्रम now */
		tty = tty_init_dev(driver, index);
		mutex_unlock(&tty_mutex);
	पूर्ण
out:
	tty_driver_kref_put(driver);
	वापस tty;
पूर्ण

/**
 *	tty_खोलो		-	खोलो a tty device
 *	@inode: inode of device file
 *	@filp: file poपूर्णांकer to tty
 *
 *	tty_खोलो and tty_release keep up the tty count that contains the
 *	number of खोलोs करोne on a tty. We cannot use the inode-count, as
 *	dअगरferent inodes might poपूर्णांक to the same tty.
 *
 *	Open-counting is needed क्रम pty masters, as well as क्रम keeping
 *	track of serial lines: DTR is dropped when the last बंद happens.
 *	(This is not करोne solely through tty->count, now.  - Ted 1/27/92)
 *
 *	The termios state of a pty is reset on first खोलो so that
 *	settings करोn't persist across reuse.
 *
 *	Locking: tty_mutex protects tty, tty_lookup_driver and tty_init_dev.
 *		 tty->count should protect the rest.
 *		 ->siglock protects ->संकेत/->sighand
 *
 *	Note: the tty_unlock/lock हालs without a ref are only safe due to
 *	tty_mutex
 */

अटल पूर्णांक tty_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा tty_काष्ठा *tty;
	पूर्णांक noctty, retval;
	dev_t device = inode->i_rdev;
	अचिन्हित saved_flags = filp->f_flags;

	nonseekable_खोलो(inode, filp);

retry_खोलो:
	retval = tty_alloc_file(filp);
	अगर (retval)
		वापस -ENOMEM;

	tty = tty_खोलो_current_tty(device, filp);
	अगर (!tty)
		tty = tty_खोलो_by_driver(device, filp);

	अगर (IS_ERR(tty)) अणु
		tty_मुक्त_file(filp);
		retval = PTR_ERR(tty);
		अगर (retval != -EAGAIN || संकेत_pending(current))
			वापस retval;
		schedule();
		जाओ retry_खोलो;
	पूर्ण

	tty_add_file(tty, filp);

	check_tty_count(tty, __func__);
	tty_debug_hangup(tty, "opening (count=%d)\n", tty->count);

	अगर (tty->ops->खोलो)
		retval = tty->ops->खोलो(tty, filp);
	अन्यथा
		retval = -ENODEV;
	filp->f_flags = saved_flags;

	अगर (retval) अणु
		tty_debug_hangup(tty, "open error %d, releasing\n", retval);

		tty_unlock(tty); /* need to call tty_release without BTM */
		tty_release(inode, filp);
		अगर (retval != -ERESTARTSYS)
			वापस retval;

		अगर (संकेत_pending(current))
			वापस retval;

		schedule();
		/*
		 * Need to reset f_op in हाल a hangup happened.
		 */
		अगर (tty_hung_up_p(filp))
			filp->f_op = &tty_fops;
		जाओ retry_खोलो;
	पूर्ण
	clear_bit(TTY_HUPPED, &tty->flags);

	noctty = (filp->f_flags & O_NOCTTY) ||
		 (IS_ENABLED(CONFIG_VT) && device == MKDEV(TTY_MAJOR, 0)) ||
		 device == MKDEV(TTYAUX_MAJOR, 1) ||
		 (tty->driver->type == TTY_DRIVER_TYPE_PTY &&
		  tty->driver->subtype == PTY_TYPE_MASTER);
	अगर (!noctty)
		tty_खोलो_proc_set_tty(filp, tty);
	tty_unlock(tty);
	वापस 0;
पूर्ण



/**
 *	tty_poll	-	check tty status
 *	@filp: file being polled
 *	@रुको: poll रुको काष्ठाures to update
 *
 *	Call the line discipline polling method to obtain the poll
 *	status of the device.
 *
 *	Locking: locks called line discipline but ldisc poll method
 *	may be re-entered मुक्तly by other callers.
 */

अटल __poll_t tty_poll(काष्ठा file *filp, poll_table *रुको)
अणु
	काष्ठा tty_काष्ठा *tty = file_tty(filp);
	काष्ठा tty_ldisc *ld;
	__poll_t ret = 0;

	अगर (tty_paranoia_check(tty, file_inode(filp), "tty_poll"))
		वापस 0;

	ld = tty_ldisc_ref_रुको(tty);
	अगर (!ld)
		वापस hung_up_tty_poll(filp, रुको);
	अगर (ld->ops->poll)
		ret = ld->ops->poll(tty, filp, रुको);
	tty_ldisc_deref(ld);
	वापस ret;
पूर्ण

अटल पूर्णांक __tty_fasync(पूर्णांक fd, काष्ठा file *filp, पूर्णांक on)
अणु
	काष्ठा tty_काष्ठा *tty = file_tty(filp);
	अचिन्हित दीर्घ flags;
	पूर्णांक retval = 0;

	अगर (tty_paranoia_check(tty, file_inode(filp), "tty_fasync"))
		जाओ out;

	retval = fasync_helper(fd, filp, on, &tty->fasync);
	अगर (retval <= 0)
		जाओ out;

	अगर (on) अणु
		क्रमागत pid_type type;
		काष्ठा pid *pid;

		spin_lock_irqsave(&tty->ctrl_lock, flags);
		अगर (tty->pgrp) अणु
			pid = tty->pgrp;
			type = PIDTYPE_PGID;
		पूर्ण अन्यथा अणु
			pid = task_pid(current);
			type = PIDTYPE_TGID;
		पूर्ण
		get_pid(pid);
		spin_unlock_irqrestore(&tty->ctrl_lock, flags);
		__f_setown(filp, pid, type, 0);
		put_pid(pid);
		retval = 0;
	पूर्ण
out:
	वापस retval;
पूर्ण

अटल पूर्णांक tty_fasync(पूर्णांक fd, काष्ठा file *filp, पूर्णांक on)
अणु
	काष्ठा tty_काष्ठा *tty = file_tty(filp);
	पूर्णांक retval = -ENOTTY;

	tty_lock(tty);
	अगर (!tty_hung_up_p(filp))
		retval = __tty_fasync(fd, filp, on);
	tty_unlock(tty);

	वापस retval;
पूर्ण

/**
 *	tiocsti			-	fake input अक्षरacter
 *	@tty: tty to fake input पूर्णांकo
 *	@p: poपूर्णांकer to अक्षरacter
 *
 *	Fake input to a tty device. Does the necessary locking and
 *	input management.
 *
 *	FIXME: करोes not honour flow control ??
 *
 *	Locking:
 *		Called functions take tty_ldiscs_lock
 *		current->संकेत->tty check is safe without locks
 *
 *	FIXME: may race normal receive processing
 */

अटल पूर्णांक tiocsti(काष्ठा tty_काष्ठा *tty, अक्षर __user *p)
अणु
	अक्षर ch, mbz = 0;
	काष्ठा tty_ldisc *ld;

	अगर ((current->संकेत->tty != tty) && !capable(CAP_SYS_ADMIN))
		वापस -EPERM;
	अगर (get_user(ch, p))
		वापस -EFAULT;
	tty_audit_tiocsti(tty, ch);
	ld = tty_ldisc_ref_रुको(tty);
	अगर (!ld)
		वापस -EIO;
	अगर (ld->ops->receive_buf)
		ld->ops->receive_buf(tty, &ch, &mbz, 1);
	tty_ldisc_deref(ld);
	वापस 0;
पूर्ण

/**
 *	tiocgwinsz		-	implement winकरोw query ioctl
 *	@tty: tty
 *	@arg: user buffer क्रम result
 *
 *	Copies the kernel idea of the winकरोw size पूर्णांकo the user buffer.
 *
 *	Locking: tty->winsize_mutex is taken to ensure the winsize data
 *		is consistent.
 */

अटल पूर्णांक tiocgwinsz(काष्ठा tty_काष्ठा *tty, काष्ठा winsize __user *arg)
अणु
	पूर्णांक err;

	mutex_lock(&tty->winsize_mutex);
	err = copy_to_user(arg, &tty->winsize, माप(*arg));
	mutex_unlock(&tty->winsize_mutex);

	वापस err ? -EFAULT: 0;
पूर्ण

/**
 *	tty_करो_resize		-	resize event
 *	@tty: tty being resized
 *	@ws: new dimensions
 *
 *	Update the termios variables and send the necessary संकेतs to
 *	peक्रमm a terminal resize correctly
 */

पूर्णांक tty_करो_resize(काष्ठा tty_काष्ठा *tty, काष्ठा winsize *ws)
अणु
	काष्ठा pid *pgrp;

	/* Lock the tty */
	mutex_lock(&tty->winsize_mutex);
	अगर (!स_भेद(ws, &tty->winsize, माप(*ws)))
		जाओ करोne;

	/* Signal the क्रमeground process group */
	pgrp = tty_get_pgrp(tty);
	अगर (pgrp)
		समाप्त_pgrp(pgrp, SIGWINCH, 1);
	put_pid(pgrp);

	tty->winsize = *ws;
करोne:
	mutex_unlock(&tty->winsize_mutex);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(tty_करो_resize);

/**
 *	tiocswinsz		-	implement winकरोw size set ioctl
 *	@tty: tty side of tty
 *	@arg: user buffer क्रम result
 *
 *	Copies the user idea of the winकरोw size to the kernel. Traditionally
 *	this is just advisory inक्रमmation but क्रम the Linux console it
 *	actually has driver level meaning and triggers a VC resize.
 *
 *	Locking:
 *		Driver dependent. The शेष करो_resize method takes the
 *	tty termios mutex and ctrl_lock. The console takes its own lock
 *	then calls पूर्णांकo the शेष method.
 */

अटल पूर्णांक tiocswinsz(काष्ठा tty_काष्ठा *tty, काष्ठा winsize __user *arg)
अणु
	काष्ठा winsize पंचांगp_ws;
	अगर (copy_from_user(&पंचांगp_ws, arg, माप(*arg)))
		वापस -EFAULT;

	अगर (tty->ops->resize)
		वापस tty->ops->resize(tty, &पंचांगp_ws);
	अन्यथा
		वापस tty_करो_resize(tty, &पंचांगp_ws);
पूर्ण

/**
 *	tioccons	-	allow admin to move logical console
 *	@file: the file to become console
 *
 *	Allow the administrator to move the redirected console device
 *
 *	Locking: uses redirect_lock to guard the redirect inक्रमmation
 */

अटल पूर्णांक tioccons(काष्ठा file *file)
अणु
	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;
	अगर (file->f_op->ग_लिखो_iter == redirected_tty_ग_लिखो) अणु
		काष्ठा file *f;
		spin_lock(&redirect_lock);
		f = redirect;
		redirect = शून्य;
		spin_unlock(&redirect_lock);
		अगर (f)
			fput(f);
		वापस 0;
	पूर्ण
	अगर (file->f_op->ग_लिखो_iter != tty_ग_लिखो)
		वापस -ENOTTY;
	अगर (!(file->f_mode & FMODE_WRITE))
		वापस -EBADF;
	अगर (!(file->f_mode & FMODE_CAN_WRITE))
		वापस -EINVAL;
	spin_lock(&redirect_lock);
	अगर (redirect) अणु
		spin_unlock(&redirect_lock);
		वापस -EBUSY;
	पूर्ण
	redirect = get_file(file);
	spin_unlock(&redirect_lock);
	वापस 0;
पूर्ण

/**
 *	tiocsetd	-	set line discipline
 *	@tty: tty device
 *	@p: poपूर्णांकer to user data
 *
 *	Set the line discipline according to user request.
 *
 *	Locking: see tty_set_ldisc, this function is just a helper
 */

अटल पूर्णांक tiocsetd(काष्ठा tty_काष्ठा *tty, पूर्णांक __user *p)
अणु
	पूर्णांक disc;
	पूर्णांक ret;

	अगर (get_user(disc, p))
		वापस -EFAULT;

	ret = tty_set_ldisc(tty, disc);

	वापस ret;
पूर्ण

/**
 *	tiocgetd	-	get line discipline
 *	@tty: tty device
 *	@p: poपूर्णांकer to user data
 *
 *	Retrieves the line discipline id directly from the ldisc.
 *
 *	Locking: रुकोs क्रम ldisc reference (in हाल the line discipline
 *		is changing or the tty is being hungup)
 */

अटल पूर्णांक tiocgetd(काष्ठा tty_काष्ठा *tty, पूर्णांक __user *p)
अणु
	काष्ठा tty_ldisc *ld;
	पूर्णांक ret;

	ld = tty_ldisc_ref_रुको(tty);
	अगर (!ld)
		वापस -EIO;
	ret = put_user(ld->ops->num, p);
	tty_ldisc_deref(ld);
	वापस ret;
पूर्ण

/**
 *	send_अवरोध	-	perक्रमmed समय अवरोध
 *	@tty: device to अवरोध on
 *	@duration: समयout in mS
 *
 *	Perक्रमm a समयd अवरोध on hardware that lacks its own driver level
 *	समयd अवरोध functionality.
 *
 *	Locking:
 *		atomic_ग_लिखो_lock serializes
 *
 */

अटल पूर्णांक send_अवरोध(काष्ठा tty_काष्ठा *tty, अचिन्हित पूर्णांक duration)
अणु
	पूर्णांक retval;

	अगर (tty->ops->अवरोध_ctl == शून्य)
		वापस 0;

	अगर (tty->driver->flags & TTY_DRIVER_HARDWARE_BREAK)
		retval = tty->ops->अवरोध_ctl(tty, duration);
	अन्यथा अणु
		/* Do the work ourselves */
		अगर (tty_ग_लिखो_lock(tty, 0) < 0)
			वापस -EINTR;
		retval = tty->ops->अवरोध_ctl(tty, -1);
		अगर (retval)
			जाओ out;
		अगर (!संकेत_pending(current))
			msleep_पूर्णांकerruptible(duration);
		retval = tty->ops->अवरोध_ctl(tty, 0);
out:
		tty_ग_लिखो_unlock(tty);
		अगर (संकेत_pending(current))
			retval = -EINTR;
	पूर्ण
	वापस retval;
पूर्ण

/**
 *	tty_tiocmget		-	get modem status
 *	@tty: tty device
 *	@p: poपूर्णांकer to result
 *
 *	Obtain the modem status bits from the tty driver अगर the feature
 *	is supported. Return -ENOTTY अगर it is not available.
 *
 *	Locking: none (up to the driver)
 */

अटल पूर्णांक tty_tiocmget(काष्ठा tty_काष्ठा *tty, पूर्णांक __user *p)
अणु
	पूर्णांक retval = -ENOTTY;

	अगर (tty->ops->tiocmget) अणु
		retval = tty->ops->tiocmget(tty);

		अगर (retval >= 0)
			retval = put_user(retval, p);
	पूर्ण
	वापस retval;
पूर्ण

/**
 *	tty_tiocmset		-	set modem status
 *	@tty: tty device
 *	@cmd: command - clear bits, set bits or set all
 *	@p: poपूर्णांकer to desired bits
 *
 *	Set the modem status bits from the tty driver अगर the feature
 *	is supported. Return -ENOTTY अगर it is not available.
 *
 *	Locking: none (up to the driver)
 */

अटल पूर्णांक tty_tiocmset(काष्ठा tty_काष्ठा *tty, अचिन्हित पूर्णांक cmd,
	     अचिन्हित __user *p)
अणु
	पूर्णांक retval;
	अचिन्हित पूर्णांक set, clear, val;

	अगर (tty->ops->tiocmset == शून्य)
		वापस -ENOTTY;

	retval = get_user(val, p);
	अगर (retval)
		वापस retval;
	set = clear = 0;
	चयन (cmd) अणु
	हाल TIOCMBIS:
		set = val;
		अवरोध;
	हाल TIOCMBIC:
		clear = val;
		अवरोध;
	हाल TIOCMSET:
		set = val;
		clear = ~val;
		अवरोध;
	पूर्ण
	set &= TIOCM_DTR|TIOCM_RTS|TIOCM_OUT1|TIOCM_OUT2|TIOCM_LOOP;
	clear &= TIOCM_DTR|TIOCM_RTS|TIOCM_OUT1|TIOCM_OUT2|TIOCM_LOOP;
	वापस tty->ops->tiocmset(tty, set, clear);
पूर्ण

/**
 *	tty_get_icount		-	get tty statistics
 *	@tty: tty device
 *	@icount: output parameter
 *
 *	Gets a copy of the tty's icount statistics.
 *
 *	Locking: none (up to the driver)
 */
पूर्णांक tty_get_icount(काष्ठा tty_काष्ठा *tty,
		   काष्ठा serial_icounter_काष्ठा *icount)
अणु
	स_रखो(icount, 0, माप(*icount));

	अगर (tty->ops->get_icount)
		वापस tty->ops->get_icount(tty, icount);
	अन्यथा
		वापस -ENOTTY;
पूर्ण
EXPORT_SYMBOL_GPL(tty_get_icount);

अटल पूर्णांक tty_tiocgicount(काष्ठा tty_काष्ठा *tty, व्योम __user *arg)
अणु
	काष्ठा serial_icounter_काष्ठा icount;
	पूर्णांक retval;

	retval = tty_get_icount(tty, &icount);
	अगर (retval != 0)
		वापस retval;

	अगर (copy_to_user(arg, &icount, माप(icount)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक tty_set_serial(काष्ठा tty_काष्ठा *tty, काष्ठा serial_काष्ठा *ss)
अणु
	अक्षर comm[TASK_COMM_LEN];
	पूर्णांक flags;

	flags = ss->flags & ASYNC_DEPRECATED;

	अगर (flags)
		pr_warn_ratelimited("%s: '%s' is using deprecated serial flags (with no effect): %.8x\n",
				__func__, get_task_comm(comm, current), flags);

	अगर (!tty->ops->set_serial)
		वापस -ENOTTY;

	वापस tty->ops->set_serial(tty, ss);
पूर्ण

अटल पूर्णांक tty_tiocsserial(काष्ठा tty_काष्ठा *tty, काष्ठा serial_काष्ठा __user *ss)
अणु
	काष्ठा serial_काष्ठा v;

	अगर (copy_from_user(&v, ss, माप(*ss)))
		वापस -EFAULT;

	वापस tty_set_serial(tty, &v);
पूर्ण

अटल पूर्णांक tty_tiocgserial(काष्ठा tty_काष्ठा *tty, काष्ठा serial_काष्ठा __user *ss)
अणु
	काष्ठा serial_काष्ठा v;
	पूर्णांक err;

	स_रखो(&v, 0, माप(v));
	अगर (!tty->ops->get_serial)
		वापस -ENOTTY;
	err = tty->ops->get_serial(tty, &v);
	अगर (!err && copy_to_user(ss, &v, माप(v)))
		err = -EFAULT;
	वापस err;
पूर्ण

/*
 * अगर pty, वापस the slave side (real_tty)
 * otherwise, वापस self
 */
अटल काष्ठा tty_काष्ठा *tty_pair_get_tty(काष्ठा tty_काष्ठा *tty)
अणु
	अगर (tty->driver->type == TTY_DRIVER_TYPE_PTY &&
	    tty->driver->subtype == PTY_TYPE_MASTER)
		tty = tty->link;
	वापस tty;
पूर्ण

/*
 * Split this up, as gcc can choke on it otherwise..
 */
दीर्घ tty_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा tty_काष्ठा *tty = file_tty(file);
	काष्ठा tty_काष्ठा *real_tty;
	व्योम __user *p = (व्योम __user *)arg;
	पूर्णांक retval;
	काष्ठा tty_ldisc *ld;

	अगर (tty_paranoia_check(tty, file_inode(file), "tty_ioctl"))
		वापस -EINVAL;

	real_tty = tty_pair_get_tty(tty);

	/*
	 * Factor out some common prep work
	 */
	चयन (cmd) अणु
	हाल TIOCSETD:
	हाल TIOCSBRK:
	हाल TIOCCBRK:
	हाल TCSBRK:
	हाल TCSBRKP:
		retval = tty_check_change(tty);
		अगर (retval)
			वापस retval;
		अगर (cmd != TIOCCBRK) अणु
			tty_रुको_until_sent(tty, 0);
			अगर (संकेत_pending(current))
				वापस -EINTR;
		पूर्ण
		अवरोध;
	पूर्ण

	/*
	 *	Now करो the stuff.
	 */
	चयन (cmd) अणु
	हाल TIOCSTI:
		वापस tiocsti(tty, p);
	हाल TIOCGWINSZ:
		वापस tiocgwinsz(real_tty, p);
	हाल TIOCSWINSZ:
		वापस tiocswinsz(real_tty, p);
	हाल TIOCCONS:
		वापस real_tty != tty ? -EINVAL : tioccons(file);
	हाल TIOCEXCL:
		set_bit(TTY_EXCLUSIVE, &tty->flags);
		वापस 0;
	हाल TIOCNXCL:
		clear_bit(TTY_EXCLUSIVE, &tty->flags);
		वापस 0;
	हाल TIOCGEXCL:
	अणु
		पूर्णांक excl = test_bit(TTY_EXCLUSIVE, &tty->flags);
		वापस put_user(excl, (पूर्णांक __user *)p);
	पूर्ण
	हाल TIOCGETD:
		वापस tiocgetd(tty, p);
	हाल TIOCSETD:
		वापस tiocsetd(tty, p);
	हाल TIOCVHANGUP:
		अगर (!capable(CAP_SYS_ADMIN))
			वापस -EPERM;
		tty_vhangup(tty);
		वापस 0;
	हाल TIOCGDEV:
	अणु
		अचिन्हित पूर्णांक ret = new_encode_dev(tty_devnum(real_tty));
		वापस put_user(ret, (अचिन्हित पूर्णांक __user *)p);
	पूर्ण
	/*
	 * Break handling
	 */
	हाल TIOCSBRK:	/* Turn अवरोध on, unconditionally */
		अगर (tty->ops->अवरोध_ctl)
			वापस tty->ops->अवरोध_ctl(tty, -1);
		वापस 0;
	हाल TIOCCBRK:	/* Turn अवरोध off, unconditionally */
		अगर (tty->ops->अवरोध_ctl)
			वापस tty->ops->अवरोध_ctl(tty, 0);
		वापस 0;
	हाल TCSBRK:   /* SVID version: non-zero arg --> no अवरोध */
		/* non-zero arg means रुको क्रम all output data
		 * to be sent (perक्रमmed above) but करोn't send अवरोध.
		 * This is used by the tcdrain() termios function.
		 */
		अगर (!arg)
			वापस send_अवरोध(tty, 250);
		वापस 0;
	हाल TCSBRKP:	/* support क्रम POSIX tcsendअवरोध() */
		वापस send_अवरोध(tty, arg ? arg*100 : 250);

	हाल TIOCMGET:
		वापस tty_tiocmget(tty, p);
	हाल TIOCMSET:
	हाल TIOCMBIC:
	हाल TIOCMBIS:
		वापस tty_tiocmset(tty, cmd, p);
	हाल TIOCGICOUNT:
		वापस tty_tiocgicount(tty, p);
	हाल TCFLSH:
		चयन (arg) अणु
		हाल TCIFLUSH:
		हाल TCIOFLUSH:
		/* flush tty buffer and allow ldisc to process ioctl */
			tty_buffer_flush(tty, शून्य);
			अवरोध;
		पूर्ण
		अवरोध;
	हाल TIOCSSERIAL:
		वापस tty_tiocsserial(tty, p);
	हाल TIOCGSERIAL:
		वापस tty_tiocgserial(tty, p);
	हाल TIOCGPTPEER:
		/* Special because the काष्ठा file is needed */
		वापस pपंचांग_खोलो_peer(file, tty, (पूर्णांक)arg);
	शेष:
		retval = tty_jobctrl_ioctl(tty, real_tty, file, cmd, arg);
		अगर (retval != -ENOIOCTLCMD)
			वापस retval;
	पूर्ण
	अगर (tty->ops->ioctl) अणु
		retval = tty->ops->ioctl(tty, cmd, arg);
		अगर (retval != -ENOIOCTLCMD)
			वापस retval;
	पूर्ण
	ld = tty_ldisc_ref_रुको(tty);
	अगर (!ld)
		वापस hung_up_tty_ioctl(file, cmd, arg);
	retval = -EINVAL;
	अगर (ld->ops->ioctl) अणु
		retval = ld->ops->ioctl(tty, file, cmd, arg);
		अगर (retval == -ENOIOCTLCMD)
			retval = -ENOTTY;
	पूर्ण
	tty_ldisc_deref(ld);
	वापस retval;
पूर्ण

#अगर_घोषित CONFIG_COMPAT

काष्ठा serial_काष्ठा32 अणु
	compat_पूर्णांक_t    type;
	compat_पूर्णांक_t    line;
	compat_uपूर्णांक_t   port;
	compat_पूर्णांक_t    irq;
	compat_पूर्णांक_t    flags;
	compat_पूर्णांक_t    xmit_fअगरo_size;
	compat_पूर्णांक_t    custom_भागisor;
	compat_पूर्णांक_t    baud_base;
	अचिन्हित लघु  बंद_delay;
	अक्षर    io_type;
	अक्षर    reserved_अक्षर;
	compat_पूर्णांक_t    hub6;
	अचिन्हित लघु  closing_रुको; /* समय to रुको beक्रमe closing */
	अचिन्हित लघु  closing_रुको2; /* no दीर्घer used... */
	compat_uपूर्णांक_t   iomem_base;
	अचिन्हित लघु  iomem_reg_shअगरt;
	अचिन्हित पूर्णांक    port_high;
	/* compat_uदीर्घ_t  iomap_base FIXME */
	compat_पूर्णांक_t    reserved;
पूर्ण;

अटल पूर्णांक compat_tty_tiocsserial(काष्ठा tty_काष्ठा *tty,
		काष्ठा serial_काष्ठा32 __user *ss)
अणु
	काष्ठा serial_काष्ठा32 v32;
	काष्ठा serial_काष्ठा v;

	अगर (copy_from_user(&v32, ss, माप(*ss)))
		वापस -EFAULT;

	स_नकल(&v, &v32, दुरत्व(काष्ठा serial_काष्ठा32, iomem_base));
	v.iomem_base = compat_ptr(v32.iomem_base);
	v.iomem_reg_shअगरt = v32.iomem_reg_shअगरt;
	v.port_high = v32.port_high;
	v.iomap_base = 0;

	वापस tty_set_serial(tty, &v);
पूर्ण

अटल पूर्णांक compat_tty_tiocgserial(काष्ठा tty_काष्ठा *tty,
			काष्ठा serial_काष्ठा32 __user *ss)
अणु
	काष्ठा serial_काष्ठा32 v32;
	काष्ठा serial_काष्ठा v;
	पूर्णांक err;

	स_रखो(&v, 0, माप(v));
	स_रखो(&v32, 0, माप(v32));

	अगर (!tty->ops->get_serial)
		वापस -ENOTTY;
	err = tty->ops->get_serial(tty, &v);
	अगर (!err) अणु
		स_नकल(&v32, &v, दुरत्व(काष्ठा serial_काष्ठा32, iomem_base));
		v32.iomem_base = (अचिन्हित दीर्घ)v.iomem_base >> 32 ?
			0xfffffff : ptr_to_compat(v.iomem_base);
		v32.iomem_reg_shअगरt = v.iomem_reg_shअगरt;
		v32.port_high = v.port_high;
		अगर (copy_to_user(ss, &v32, माप(v32)))
			err = -EFAULT;
	पूर्ण
	वापस err;
पूर्ण
अटल दीर्घ tty_compat_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
				अचिन्हित दीर्घ arg)
अणु
	काष्ठा tty_काष्ठा *tty = file_tty(file);
	काष्ठा tty_ldisc *ld;
	पूर्णांक retval = -ENOIOCTLCMD;

	चयन (cmd) अणु
	हाल TIOCOUTQ:
	हाल TIOCSTI:
	हाल TIOCGWINSZ:
	हाल TIOCSWINSZ:
	हाल TIOCGEXCL:
	हाल TIOCGETD:
	हाल TIOCSETD:
	हाल TIOCGDEV:
	हाल TIOCMGET:
	हाल TIOCMSET:
	हाल TIOCMBIC:
	हाल TIOCMBIS:
	हाल TIOCGICOUNT:
	हाल TIOCGPGRP:
	हाल TIOCSPGRP:
	हाल TIOCGSID:
	हाल TIOCSERGETLSR:
	हाल TIOCGRS485:
	हाल TIOCSRS485:
#अगर_घोषित TIOCGETP
	हाल TIOCGETP:
	हाल TIOCSETP:
	हाल TIOCSETN:
#पूर्ण_अगर
#अगर_घोषित TIOCGETC
	हाल TIOCGETC:
	हाल TIOCSETC:
#पूर्ण_अगर
#अगर_घोषित TIOCGLTC
	हाल TIOCGLTC:
	हाल TIOCSLTC:
#पूर्ण_अगर
	हाल TCSETSF:
	हाल TCSETSW:
	हाल TCSETS:
	हाल TCGETS:
#अगर_घोषित TCGETS2
	हाल TCGETS2:
	हाल TCSETSF2:
	हाल TCSETSW2:
	हाल TCSETS2:
#पूर्ण_अगर
	हाल TCGETA:
	हाल TCSETAF:
	हाल TCSETAW:
	हाल TCSETA:
	हाल TIOCGLCKTRMIOS:
	हाल TIOCSLCKTRMIOS:
#अगर_घोषित TCGETX
	हाल TCGETX:
	हाल TCSETX:
	हाल TCSETXW:
	हाल TCSETXF:
#पूर्ण_अगर
	हाल TIOCGSOFTCAR:
	हाल TIOCSSOFTCAR:

	हाल PPPIOCGCHAN:
	हाल PPPIOCGUNIT:
		वापस tty_ioctl(file, cmd, (अचिन्हित दीर्घ)compat_ptr(arg));
	हाल TIOCCONS:
	हाल TIOCEXCL:
	हाल TIOCNXCL:
	हाल TIOCVHANGUP:
	हाल TIOCSBRK:
	हाल TIOCCBRK:
	हाल TCSBRK:
	हाल TCSBRKP:
	हाल TCFLSH:
	हाल TIOCGPTPEER:
	हाल TIOCNOTTY:
	हाल TIOCSCTTY:
	हाल TCXONC:
	हाल TIOCMIWAIT:
	हाल TIOCSERCONFIG:
		वापस tty_ioctl(file, cmd, arg);
	पूर्ण

	अगर (tty_paranoia_check(tty, file_inode(file), "tty_ioctl"))
		वापस -EINVAL;

	चयन (cmd) अणु
	हाल TIOCSSERIAL:
		वापस compat_tty_tiocsserial(tty, compat_ptr(arg));
	हाल TIOCGSERIAL:
		वापस compat_tty_tiocgserial(tty, compat_ptr(arg));
	पूर्ण
	अगर (tty->ops->compat_ioctl) अणु
		retval = tty->ops->compat_ioctl(tty, cmd, arg);
		अगर (retval != -ENOIOCTLCMD)
			वापस retval;
	पूर्ण

	ld = tty_ldisc_ref_रुको(tty);
	अगर (!ld)
		वापस hung_up_tty_compat_ioctl(file, cmd, arg);
	अगर (ld->ops->compat_ioctl)
		retval = ld->ops->compat_ioctl(tty, file, cmd, arg);
	अगर (retval == -ENOIOCTLCMD && ld->ops->ioctl)
		retval = ld->ops->ioctl(tty, file,
				(अचिन्हित दीर्घ)compat_ptr(cmd), arg);
	tty_ldisc_deref(ld);

	वापस retval;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक this_tty(स्थिर व्योम *t, काष्ठा file *file, अचिन्हित fd)
अणु
	अगर (likely(file->f_op->पढ़ो_iter != tty_पढ़ो))
		वापस 0;
	वापस file_tty(file) != t ? 0 : fd + 1;
पूर्ण
	
/*
 * This implements the "Secure Attention Key" ---  the idea is to
 * prevent trojan horses by समाप्तing all processes associated with this
 * tty when the user hits the "Secure Attention Key".  Required क्रम
 * super-paranoid applications --- see the Orange Book क्रम more details.
 *
 * This code could be nicer; ideally it should send a HUP, रुको a few
 * seconds, then send a INT, and then a KILL संकेत.  But you then
 * have to coordinate with the init process, since all processes associated
 * with the current tty must be dead beक्रमe the new getty is allowed
 * to spawn.
 *
 * Now, अगर it would be correct ;-/ The current code has a nasty hole -
 * it करोesn't catch files in flight. We may send the descriptor to ourselves
 * via AF_UNIX socket, बंद it and later fetch from socket. FIXME.
 *
 * Nasty bug: करो_SAK is being called in पूर्णांकerrupt context.  This can
 * deadlock.  We punt it up to process context.  AKPM - 16Mar2001
 */
व्योम __करो_SAK(काष्ठा tty_काष्ठा *tty)
अणु
#अगर_घोषित TTY_SOFT_SAK
	tty_hangup(tty);
#अन्यथा
	काष्ठा task_काष्ठा *g, *p;
	काष्ठा pid *session;
	पूर्णांक		i;
	अचिन्हित दीर्घ flags;

	अगर (!tty)
		वापस;

	spin_lock_irqsave(&tty->ctrl_lock, flags);
	session = get_pid(tty->session);
	spin_unlock_irqrestore(&tty->ctrl_lock, flags);

	tty_ldisc_flush(tty);

	tty_driver_flush_buffer(tty);

	पढ़ो_lock(&tasklist_lock);
	/* Kill the entire session */
	करो_each_pid_task(session, PIDTYPE_SID, p) अणु
		tty_notice(tty, "SAK: killed process %d (%s): by session\n",
			   task_pid_nr(p), p->comm);
		group_send_sig_info(SIGKILL, SEND_SIG_PRIV, p, PIDTYPE_SID);
	पूर्ण जबतक_each_pid_task(session, PIDTYPE_SID, p);

	/* Now समाप्त any processes that happen to have the tty खोलो */
	करो_each_thपढ़ो(g, p) अणु
		अगर (p->संकेत->tty == tty) अणु
			tty_notice(tty, "SAK: killed process %d (%s): by controlling tty\n",
				   task_pid_nr(p), p->comm);
			group_send_sig_info(SIGKILL, SEND_SIG_PRIV, p, PIDTYPE_SID);
			जारी;
		पूर्ण
		task_lock(p);
		i = iterate_fd(p->files, 0, this_tty, tty);
		अगर (i != 0) अणु
			tty_notice(tty, "SAK: killed process %d (%s): by fd#%d\n",
				   task_pid_nr(p), p->comm, i - 1);
			group_send_sig_info(SIGKILL, SEND_SIG_PRIV, p, PIDTYPE_SID);
		पूर्ण
		task_unlock(p);
	पूर्ण जबतक_each_thपढ़ो(g, p);
	पढ़ो_unlock(&tasklist_lock);
	put_pid(session);
#पूर्ण_अगर
पूर्ण

अटल व्योम करो_SAK_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा tty_काष्ठा *tty =
		container_of(work, काष्ठा tty_काष्ठा, SAK_work);
	__करो_SAK(tty);
पूर्ण

/*
 * The tq handling here is a little racy - tty->SAK_work may alपढ़ोy be queued.
 * Fortunately we करोn't need to worry, because अगर ->SAK_work is alपढ़ोy queued,
 * the values which we ग_लिखो to it will be identical to the values which it
 * alपढ़ोy has. --akpm
 */
व्योम करो_SAK(काष्ठा tty_काष्ठा *tty)
अणु
	अगर (!tty)
		वापस;
	schedule_work(&tty->SAK_work);
पूर्ण

EXPORT_SYMBOL(करो_SAK);

/* Must put_device() after it's unused! */
अटल काष्ठा device *tty_get_device(काष्ठा tty_काष्ठा *tty)
अणु
	dev_t devt = tty_devnum(tty);
	वापस class_find_device_by_devt(tty_class, devt);
पूर्ण


/*
 *	alloc_tty_काष्ठा
 *
 *	This subroutine allocates and initializes a tty काष्ठाure.
 *
 *	Locking: none - tty in question is not exposed at this poपूर्णांक
 */

काष्ठा tty_काष्ठा *alloc_tty_काष्ठा(काष्ठा tty_driver *driver, पूर्णांक idx)
अणु
	काष्ठा tty_काष्ठा *tty;

	tty = kzalloc(माप(*tty), GFP_KERNEL);
	अगर (!tty)
		वापस शून्य;

	kref_init(&tty->kref);
	tty->magic = TTY_MAGIC;
	अगर (tty_ldisc_init(tty)) अणु
		kमुक्त(tty);
		वापस शून्य;
	पूर्ण
	tty->session = शून्य;
	tty->pgrp = शून्य;
	mutex_init(&tty->legacy_mutex);
	mutex_init(&tty->throttle_mutex);
	init_rwsem(&tty->termios_rwsem);
	mutex_init(&tty->winsize_mutex);
	init_ldsem(&tty->ldisc_sem);
	init_रुकोqueue_head(&tty->ग_लिखो_रुको);
	init_रुकोqueue_head(&tty->पढ़ो_रुको);
	INIT_WORK(&tty->hangup_work, करो_tty_hangup);
	mutex_init(&tty->atomic_ग_लिखो_lock);
	spin_lock_init(&tty->ctrl_lock);
	spin_lock_init(&tty->flow_lock);
	spin_lock_init(&tty->files_lock);
	INIT_LIST_HEAD(&tty->tty_files);
	INIT_WORK(&tty->SAK_work, करो_SAK_work);

	tty->driver = driver;
	tty->ops = driver->ops;
	tty->index = idx;
	tty_line_name(driver, idx, tty->name);
	tty->dev = tty_get_device(tty);

	वापस tty;
पूर्ण

/**
 *	tty_put_अक्षर	-	ग_लिखो one अक्षरacter to a tty
 *	@tty: tty
 *	@ch: अक्षरacter
 *
 *	Write one byte to the tty using the provided put_अक्षर method
 *	अगर present. Returns the number of अक्षरacters successfully output.
 *
 *	Note: the specअगरic put_अक्षर operation in the driver layer may go
 *	away soon. Don't call it directly, use this method
 */

पूर्णांक tty_put_अक्षर(काष्ठा tty_काष्ठा *tty, अचिन्हित अक्षर ch)
अणु
	अगर (tty->ops->put_अक्षर)
		वापस tty->ops->put_अक्षर(tty, ch);
	वापस tty->ops->ग_लिखो(tty, &ch, 1);
पूर्ण
EXPORT_SYMBOL_GPL(tty_put_अक्षर);

काष्ठा class *tty_class;

अटल पूर्णांक tty_cdev_add(काष्ठा tty_driver *driver, dev_t dev,
		अचिन्हित पूर्णांक index, अचिन्हित पूर्णांक count)
अणु
	पूर्णांक err;

	/* init here, since reused cdevs cause crashes */
	driver->cdevs[index] = cdev_alloc();
	अगर (!driver->cdevs[index])
		वापस -ENOMEM;
	driver->cdevs[index]->ops = &tty_fops;
	driver->cdevs[index]->owner = driver->owner;
	err = cdev_add(driver->cdevs[index], dev, count);
	अगर (err)
		kobject_put(&driver->cdevs[index]->kobj);
	वापस err;
पूर्ण

/**
 *	tty_रेजिस्टर_device - रेजिस्टर a tty device
 *	@driver: the tty driver that describes the tty device
 *	@index: the index in the tty driver क्रम this tty device
 *	@device: a काष्ठा device that is associated with this tty device.
 *		This field is optional, अगर there is no known काष्ठा device
 *		क्रम this tty device it can be set to शून्य safely.
 *
 *	Returns a poपूर्णांकer to the काष्ठा device क्रम this tty device
 *	(or ERR_PTR(-EFOO) on error).
 *
 *	This call is required to be made to रेजिस्टर an inभागidual tty device
 *	अगर the tty driver's flags have the TTY_DRIVER_DYNAMIC_DEV bit set.  If
 *	that bit is not set, this function should not be called by a tty
 *	driver.
 *
 *	Locking: ??
 */

काष्ठा device *tty_रेजिस्टर_device(काष्ठा tty_driver *driver, अचिन्हित index,
				   काष्ठा device *device)
अणु
	वापस tty_रेजिस्टर_device_attr(driver, index, device, शून्य, शून्य);
पूर्ण
EXPORT_SYMBOL(tty_रेजिस्टर_device);

अटल व्योम tty_device_create_release(काष्ठा device *dev)
अणु
	dev_dbg(dev, "releasing...\n");
	kमुक्त(dev);
पूर्ण

/**
 *	tty_रेजिस्टर_device_attr - रेजिस्टर a tty device
 *	@driver: the tty driver that describes the tty device
 *	@index: the index in the tty driver क्रम this tty device
 *	@device: a काष्ठा device that is associated with this tty device.
 *		This field is optional, अगर there is no known काष्ठा device
 *		क्रम this tty device it can be set to शून्य safely.
 *	@drvdata: Driver data to be set to device.
 *	@attr_grp: Attribute group to be set on device.
 *
 *	Returns a poपूर्णांकer to the काष्ठा device क्रम this tty device
 *	(or ERR_PTR(-EFOO) on error).
 *
 *	This call is required to be made to रेजिस्टर an inभागidual tty device
 *	अगर the tty driver's flags have the TTY_DRIVER_DYNAMIC_DEV bit set.  If
 *	that bit is not set, this function should not be called by a tty
 *	driver.
 *
 *	Locking: ??
 */
काष्ठा device *tty_रेजिस्टर_device_attr(काष्ठा tty_driver *driver,
				   अचिन्हित index, काष्ठा device *device,
				   व्योम *drvdata,
				   स्थिर काष्ठा attribute_group **attr_grp)
अणु
	अक्षर name[64];
	dev_t devt = MKDEV(driver->major, driver->minor_start) + index;
	काष्ठा ktermios *tp;
	काष्ठा device *dev;
	पूर्णांक retval;

	अगर (index >= driver->num) अणु
		pr_err("%s: Attempt to register invalid tty line number (%d)\n",
		       driver->name, index);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	अगर (driver->type == TTY_DRIVER_TYPE_PTY)
		pty_line_name(driver, index, name);
	अन्यथा
		tty_line_name(driver, index, name);

	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (!dev)
		वापस ERR_PTR(-ENOMEM);

	dev->devt = devt;
	dev->class = tty_class;
	dev->parent = device;
	dev->release = tty_device_create_release;
	dev_set_name(dev, "%s", name);
	dev->groups = attr_grp;
	dev_set_drvdata(dev, drvdata);

	dev_set_uevent_suppress(dev, 1);

	retval = device_रेजिस्टर(dev);
	अगर (retval)
		जाओ err_put;

	अगर (!(driver->flags & TTY_DRIVER_DYNAMIC_ALLOC)) अणु
		/*
		 * Free any saved termios data so that the termios state is
		 * reset when reusing a minor number.
		 */
		tp = driver->termios[index];
		अगर (tp) अणु
			driver->termios[index] = शून्य;
			kमुक्त(tp);
		पूर्ण

		retval = tty_cdev_add(driver, devt, index, 1);
		अगर (retval)
			जाओ err_del;
	पूर्ण

	dev_set_uevent_suppress(dev, 0);
	kobject_uevent(&dev->kobj, KOBJ_ADD);

	वापस dev;

err_del:
	device_del(dev);
err_put:
	put_device(dev);

	वापस ERR_PTR(retval);
पूर्ण
EXPORT_SYMBOL_GPL(tty_रेजिस्टर_device_attr);

/**
 * 	tty_unरेजिस्टर_device - unरेजिस्टर a tty device
 * 	@driver: the tty driver that describes the tty device
 * 	@index: the index in the tty driver क्रम this tty device
 *
 * 	If a tty device is रेजिस्टरed with a call to tty_रेजिस्टर_device() then
 *	this function must be called when the tty device is gone.
 *
 *	Locking: ??
 */

व्योम tty_unरेजिस्टर_device(काष्ठा tty_driver *driver, अचिन्हित index)
अणु
	device_destroy(tty_class,
		MKDEV(driver->major, driver->minor_start) + index);
	अगर (!(driver->flags & TTY_DRIVER_DYNAMIC_ALLOC)) अणु
		cdev_del(driver->cdevs[index]);
		driver->cdevs[index] = शून्य;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(tty_unरेजिस्टर_device);

/**
 * __tty_alloc_driver -- allocate tty driver
 * @lines: count of lines this driver can handle at most
 * @owner: module which is responsible क्रम this driver
 * @flags: some of TTY_DRIVER_* flags, will be set in driver->flags
 *
 * This should not be called directly, some of the provided macros should be
 * used instead. Use IS_ERR and मित्रs on @retval.
 */
काष्ठा tty_driver *__tty_alloc_driver(अचिन्हित पूर्णांक lines, काष्ठा module *owner,
		अचिन्हित दीर्घ flags)
अणु
	काष्ठा tty_driver *driver;
	अचिन्हित पूर्णांक cdevs = 1;
	पूर्णांक err;

	अगर (!lines || (flags & TTY_DRIVER_UNNUMBERED_NODE && lines > 1))
		वापस ERR_PTR(-EINVAL);

	driver = kzalloc(माप(*driver), GFP_KERNEL);
	अगर (!driver)
		वापस ERR_PTR(-ENOMEM);

	kref_init(&driver->kref);
	driver->magic = TTY_DRIVER_MAGIC;
	driver->num = lines;
	driver->owner = owner;
	driver->flags = flags;

	अगर (!(flags & TTY_DRIVER_DEVPTS_MEM)) अणु
		driver->ttys = kसुस्मृति(lines, माप(*driver->ttys),
				GFP_KERNEL);
		driver->termios = kसुस्मृति(lines, माप(*driver->termios),
				GFP_KERNEL);
		अगर (!driver->ttys || !driver->termios) अणु
			err = -ENOMEM;
			जाओ err_मुक्त_all;
		पूर्ण
	पूर्ण

	अगर (!(flags & TTY_DRIVER_DYNAMIC_ALLOC)) अणु
		driver->ports = kसुस्मृति(lines, माप(*driver->ports),
				GFP_KERNEL);
		अगर (!driver->ports) अणु
			err = -ENOMEM;
			जाओ err_मुक्त_all;
		पूर्ण
		cdevs = lines;
	पूर्ण

	driver->cdevs = kसुस्मृति(cdevs, माप(*driver->cdevs), GFP_KERNEL);
	अगर (!driver->cdevs) अणु
		err = -ENOMEM;
		जाओ err_मुक्त_all;
	पूर्ण

	वापस driver;
err_मुक्त_all:
	kमुक्त(driver->ports);
	kमुक्त(driver->ttys);
	kमुक्त(driver->termios);
	kमुक्त(driver->cdevs);
	kमुक्त(driver);
	वापस ERR_PTR(err);
पूर्ण
EXPORT_SYMBOL(__tty_alloc_driver);

अटल व्योम deकाष्ठा_tty_driver(काष्ठा kref *kref)
अणु
	काष्ठा tty_driver *driver = container_of(kref, काष्ठा tty_driver, kref);
	पूर्णांक i;
	काष्ठा ktermios *tp;

	अगर (driver->flags & TTY_DRIVER_INSTALLED) अणु
		क्रम (i = 0; i < driver->num; i++) अणु
			tp = driver->termios[i];
			अगर (tp) अणु
				driver->termios[i] = शून्य;
				kमुक्त(tp);
			पूर्ण
			अगर (!(driver->flags & TTY_DRIVER_DYNAMIC_DEV))
				tty_unरेजिस्टर_device(driver, i);
		पूर्ण
		proc_tty_unरेजिस्टर_driver(driver);
		अगर (driver->flags & TTY_DRIVER_DYNAMIC_ALLOC)
			cdev_del(driver->cdevs[0]);
	पूर्ण
	kमुक्त(driver->cdevs);
	kमुक्त(driver->ports);
	kमुक्त(driver->termios);
	kमुक्त(driver->ttys);
	kमुक्त(driver);
पूर्ण

व्योम tty_driver_kref_put(काष्ठा tty_driver *driver)
अणु
	kref_put(&driver->kref, deकाष्ठा_tty_driver);
पूर्ण
EXPORT_SYMBOL(tty_driver_kref_put);

व्योम tty_set_operations(काष्ठा tty_driver *driver,
			स्थिर काष्ठा tty_operations *op)
अणु
	driver->ops = op;
पूर्ण;
EXPORT_SYMBOL(tty_set_operations);

व्योम put_tty_driver(काष्ठा tty_driver *d)
अणु
	tty_driver_kref_put(d);
पूर्ण
EXPORT_SYMBOL(put_tty_driver);

/*
 * Called by a tty driver to रेजिस्टर itself.
 */
पूर्णांक tty_रेजिस्टर_driver(काष्ठा tty_driver *driver)
अणु
	पूर्णांक error;
	पूर्णांक i;
	dev_t dev;
	काष्ठा device *d;

	अगर (!driver->major) अणु
		error = alloc_chrdev_region(&dev, driver->minor_start,
						driver->num, driver->name);
		अगर (!error) अणु
			driver->major = MAJOR(dev);
			driver->minor_start = MINOR(dev);
		पूर्ण
	पूर्ण अन्यथा अणु
		dev = MKDEV(driver->major, driver->minor_start);
		error = रेजिस्टर_chrdev_region(dev, driver->num, driver->name);
	पूर्ण
	अगर (error < 0)
		जाओ err;

	अगर (driver->flags & TTY_DRIVER_DYNAMIC_ALLOC) अणु
		error = tty_cdev_add(driver, dev, 0, driver->num);
		अगर (error)
			जाओ err_unreg_अक्षर;
	पूर्ण

	mutex_lock(&tty_mutex);
	list_add(&driver->tty_drivers, &tty_drivers);
	mutex_unlock(&tty_mutex);

	अगर (!(driver->flags & TTY_DRIVER_DYNAMIC_DEV)) अणु
		क्रम (i = 0; i < driver->num; i++) अणु
			d = tty_रेजिस्टर_device(driver, i, शून्य);
			अगर (IS_ERR(d)) अणु
				error = PTR_ERR(d);
				जाओ err_unreg_devs;
			पूर्ण
		पूर्ण
	पूर्ण
	proc_tty_रेजिस्टर_driver(driver);
	driver->flags |= TTY_DRIVER_INSTALLED;
	वापस 0;

err_unreg_devs:
	क्रम (i--; i >= 0; i--)
		tty_unरेजिस्टर_device(driver, i);

	mutex_lock(&tty_mutex);
	list_del(&driver->tty_drivers);
	mutex_unlock(&tty_mutex);

err_unreg_अक्षर:
	unरेजिस्टर_chrdev_region(dev, driver->num);
err:
	वापस error;
पूर्ण
EXPORT_SYMBOL(tty_रेजिस्टर_driver);

/*
 * Called by a tty driver to unरेजिस्टर itself.
 */
व्योम tty_unरेजिस्टर_driver(काष्ठा tty_driver *driver)
अणु
	unरेजिस्टर_chrdev_region(MKDEV(driver->major, driver->minor_start),
				driver->num);
	mutex_lock(&tty_mutex);
	list_del(&driver->tty_drivers);
	mutex_unlock(&tty_mutex);
पूर्ण
EXPORT_SYMBOL(tty_unरेजिस्टर_driver);

dev_t tty_devnum(काष्ठा tty_काष्ठा *tty)
अणु
	वापस MKDEV(tty->driver->major, tty->driver->minor_start) + tty->index;
पूर्ण
EXPORT_SYMBOL(tty_devnum);

व्योम tty_शेष_fops(काष्ठा file_operations *fops)
अणु
	*fops = tty_fops;
पूर्ण

अटल अक्षर *tty_devnode(काष्ठा device *dev, umode_t *mode)
अणु
	अगर (!mode)
		वापस शून्य;
	अगर (dev->devt == MKDEV(TTYAUX_MAJOR, 0) ||
	    dev->devt == MKDEV(TTYAUX_MAJOR, 2))
		*mode = 0666;
	वापस शून्य;
पूर्ण

अटल पूर्णांक __init tty_class_init(व्योम)
अणु
	tty_class = class_create(THIS_MODULE, "tty");
	अगर (IS_ERR(tty_class))
		वापस PTR_ERR(tty_class);
	tty_class->devnode = tty_devnode;
	वापस 0;
पूर्ण

postcore_initcall(tty_class_init);

/* 3/2004 jmc: why करो these devices exist? */
अटल काष्ठा cdev tty_cdev, console_cdev;

अटल sमाप_प्रकार show_cons_active(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा console *cs[16];
	पूर्णांक i = 0;
	काष्ठा console *c;
	sमाप_प्रकार count = 0;

	console_lock();
	क्रम_each_console(c) अणु
		अगर (!c->device)
			जारी;
		अगर (!c->ग_लिखो)
			जारी;
		अगर ((c->flags & CON_ENABLED) == 0)
			जारी;
		cs[i++] = c;
		अगर (i >= ARRAY_SIZE(cs))
			अवरोध;
	पूर्ण
	जबतक (i--) अणु
		पूर्णांक index = cs[i]->index;
		काष्ठा tty_driver *drv = cs[i]->device(cs[i], &index);

		/* करोn't resolve tty0 as some programs depend on it */
		अगर (drv && (cs[i]->index > 0 || drv->major != TTY_MAJOR))
			count += tty_line_name(drv, index, buf + count);
		अन्यथा
			count += प्र_लिखो(buf + count, "%s%d",
					 cs[i]->name, cs[i]->index);

		count += प्र_लिखो(buf + count, "%c", i ? ' ':'\n');
	पूर्ण
	console_unlock();

	वापस count;
पूर्ण
अटल DEVICE_ATTR(active, S_IRUGO, show_cons_active, शून्य);

अटल काष्ठा attribute *cons_dev_attrs[] = अणु
	&dev_attr_active.attr,
	शून्य
पूर्ण;

ATTRIBUTE_GROUPS(cons_dev);

अटल काष्ठा device *consdev;

व्योम console_sysfs_notअगरy(व्योम)
अणु
	अगर (consdev)
		sysfs_notअगरy(&consdev->kobj, शून्य, "active");
पूर्ण

/*
 * Ok, now we can initialize the rest of the tty devices and can count
 * on memory allocations, पूर्णांकerrupts etc..
 */
पूर्णांक __init tty_init(व्योम)
अणु
	tty_sysctl_init();
	cdev_init(&tty_cdev, &tty_fops);
	अगर (cdev_add(&tty_cdev, MKDEV(TTYAUX_MAJOR, 0), 1) ||
	    रेजिस्टर_chrdev_region(MKDEV(TTYAUX_MAJOR, 0), 1, "/dev/tty") < 0)
		panic("Couldn't register /dev/tty driver\n");
	device_create(tty_class, शून्य, MKDEV(TTYAUX_MAJOR, 0), शून्य, "tty");

	cdev_init(&console_cdev, &console_fops);
	अगर (cdev_add(&console_cdev, MKDEV(TTYAUX_MAJOR, 1), 1) ||
	    रेजिस्टर_chrdev_region(MKDEV(TTYAUX_MAJOR, 1), 1, "/dev/console") < 0)
		panic("Couldn't register /dev/console driver\n");
	consdev = device_create_with_groups(tty_class, शून्य,
					    MKDEV(TTYAUX_MAJOR, 1), शून्य,
					    cons_dev_groups, "console");
	अगर (IS_ERR(consdev))
		consdev = शून्य;

#अगर_घोषित CONFIG_VT
	vty_init(&console_fops);
#पूर्ण_अगर
	वापस 0;
पूर्ण

