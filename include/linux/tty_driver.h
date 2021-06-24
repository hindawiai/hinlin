<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_TTY_DRIVER_H
#घोषणा _LINUX_TTY_DRIVER_H

/*
 * This काष्ठाure defines the पूर्णांकerface between the low-level tty
 * driver and the tty routines.  The following routines can be
 * defined; unless noted otherwise, they are optional, and can be
 * filled in with a null poपूर्णांकer.
 *
 * काष्ठा tty_काष्ठा * (*lookup)(काष्ठा tty_driver *self, काष्ठा file *, पूर्णांक idx)
 *
 *	Return the tty device corresponding to idx, शून्य अगर there is not
 *	one currently in use and an ERR_PTR value on error. Called under
 *	tty_mutex (क्रम now!)
 *
 *	Optional method. Default behaviour is to use the ttys array
 *
 * पूर्णांक (*install)(काष्ठा tty_driver *self, काष्ठा tty_काष्ठा *tty)
 *
 *	Install a new tty पूर्णांकo the tty driver पूर्णांकernal tables. Used in
 *	conjunction with lookup and हटाओ methods.
 *
 *	Optional method. Default behaviour is to use the ttys array
 *
 * व्योम (*हटाओ)(काष्ठा tty_driver *self, काष्ठा tty_काष्ठा *tty)
 *
 *	Remove a बंदd tty from the tty driver पूर्णांकernal tables. Used in
 *	conjunction with lookup and हटाओ methods.
 *
 *	Optional method. Default behaviour is to use the ttys array
 *
 * पूर्णांक  (*खोलो)(काष्ठा tty_काष्ठा * tty, काष्ठा file * filp);
 *
 * 	This routine is called when a particular tty device is खोलोed.
 * 	This routine is mandatory; अगर this routine is not filled in,
 * 	the attempted खोलो will fail with ENODEV.
 *
 *	Required method. Called with tty lock held.
 *
 * व्योम (*बंद)(काष्ठा tty_काष्ठा * tty, काष्ठा file * filp);
 *
 * 	This routine is called when a particular tty device is बंदd.
 *	Note: called even अगर the corresponding खोलो() failed.
 *
 *	Required method. Called with tty lock held.
 *
 * व्योम (*shutकरोwn)(काष्ठा tty_काष्ठा * tty);
 *
 * 	This routine is called under the tty lock when a particular tty device
 *	is बंदd क्रम the last समय. It executes beक्रमe the tty resources
 *	are मुक्तd so may execute जबतक another function holds a tty kref.
 *
 * व्योम (*cleanup)(काष्ठा tty_काष्ठा * tty);
 *
 *	This routine is called asynchronously when a particular tty device
 *	is बंदd क्रम the last समय मुक्तing up the resources. This is
 *	actually the second part of shutकरोwn क्रम routines that might sleep.
 *
 *
 * पूर्णांक (*ग_लिखो)(काष्ठा tty_काष्ठा * tty,
 * 		 स्थिर अचिन्हित अक्षर *buf, पूर्णांक count);
 *
 * 	This routine is called by the kernel to ग_लिखो a series of
 * 	अक्षरacters to the tty device.  The अक्षरacters may come from
 * 	user space or kernel space.  This routine will वापस the
 *	number of अक्षरacters actually accepted क्रम writing.
 *
 *	Optional: Required क्रम writable devices.
 *
 * पूर्णांक (*put_अक्षर)(काष्ठा tty_काष्ठा *tty, अचिन्हित अक्षर ch);
 *
 * 	This routine is called by the kernel to ग_लिखो a single
 * 	अक्षरacter to the tty device.  If the kernel uses this routine,
 * 	it must call the flush_अक्षरs() routine (अगर defined) when it is
 * 	करोne stuffing अक्षरacters पूर्णांकo the driver.  If there is no room
 * 	in the queue, the अक्षरacter is ignored.
 *
 *	Optional: Kernel will use the ग_लिखो method अगर not provided.
 *
 *	Note: Do not call this function directly, call tty_put_अक्षर
 *
 * व्योम (*flush_अक्षरs)(काष्ठा tty_काष्ठा *tty);
 *
 * 	This routine is called by the kernel after it has written a
 * 	series of अक्षरacters to the tty device using put_अक्षर().  
 *
 *	Optional:
 *
 *	Note: Do not call this function directly, call tty_driver_flush_अक्षरs
 * 
 * पूर्णांक  (*ग_लिखो_room)(काष्ठा tty_काष्ठा *tty);
 *
 * 	This routine वापसs the numbers of अक्षरacters the tty driver
 * 	will accept क्रम queuing to be written.  This number is subject
 * 	to change as output buffers get emptied, or अगर the output flow
 *	control is acted.
 *
 *	Required अगर ग_लिखो method is provided अन्यथा not needed.
 *
 *	Note: Do not call this function directly, call tty_ग_लिखो_room
 * 
 * पूर्णांक  (*ioctl)(काष्ठा tty_काष्ठा *tty, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);
 *
 * 	This routine allows the tty driver to implement
 *	device-specअगरic ioctls.  If the ioctl number passed in cmd
 * 	is not recognized by the driver, it should वापस ENOIOCTLCMD.
 *
 *	Optional
 *
 * दीर्घ (*compat_ioctl)(काष्ठा tty_काष्ठा *tty,,
 * 	                अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);
 *
 * 	implement ioctl processing क्रम 32 bit process on 64 bit प्रणाली
 *
 *	Optional
 * 
 * व्योम (*set_termios)(काष्ठा tty_काष्ठा *tty, काष्ठा ktermios * old);
 *
 * 	This routine allows the tty driver to be notअगरied when
 * 	device's termios settings have changed.
 *
 *	Optional: Called under the termios lock
 *
 *
 * व्योम (*set_ldisc)(काष्ठा tty_काष्ठा *tty);
 *
 * 	This routine allows the tty driver to be notअगरied when the
 * 	device's termios settings have changed.
 *
 *	Optional: Called under BKL (currently)
 * 
 * व्योम (*throttle)(काष्ठा tty_काष्ठा * tty);
 *
 * 	This routine notअगरies the tty driver that input buffers क्रम
 * 	the line discipline are बंद to full, and it should somehow
 * 	संकेत that no more अक्षरacters should be sent to the tty.
 *
 *	Optional: Always invoke via tty_throttle(), called under the
 *	termios lock.
 * 
 * व्योम (*unthrottle)(काष्ठा tty_काष्ठा * tty);
 *
 * 	This routine notअगरies the tty drivers that it should संकेतs
 * 	that अक्षरacters can now be sent to the tty without fear of
 * 	overrunning the input buffers of the line disciplines.
 * 
 *	Optional: Always invoke via tty_unthrottle(), called under the
 *	termios lock.
 *
 * व्योम (*stop)(काष्ठा tty_काष्ठा *tty);
 *
 * 	This routine notअगरies the tty driver that it should stop
 * 	outputting अक्षरacters to the tty device.  
 *
 *	Called with ->flow_lock held. Serialized with start() method.
 *
 *	Optional:
 *
 *	Note: Call stop_tty not this method.
 * 
 * व्योम (*start)(काष्ठा tty_काष्ठा *tty);
 *
 * 	This routine notअगरies the tty driver that it resume sending
 *	अक्षरacters to the tty device.
 *
 *	Called with ->flow_lock held. Serialized with stop() method.
 *
 *	Optional:
 *
 *	Note: Call start_tty not this method.
 * 
 * व्योम (*hangup)(काष्ठा tty_काष्ठा *tty);
 *
 * 	This routine notअगरies the tty driver that it should hang up the
 * 	tty device.
 *
 *	Optional:
 *
 *	Called with tty lock held.
 *
 * पूर्णांक (*अवरोध_ctl)(काष्ठा tty_काष्ठा *tty, पूर्णांक state);
 *
 * 	This optional routine requests the tty driver to turn on or
 * 	off BREAK status on the RS-232 port.  If state is -1,
 * 	then the BREAK status should be turned on; अगर state is 0, then
 * 	BREAK should be turned off.
 *
 * 	If this routine is implemented, the high-level tty driver will
 * 	handle the following ioctls: TCSBRK, TCSBRKP, TIOCSBRK,
 * 	TIOCCBRK.
 *
 *	If the driver sets TTY_DRIVER_HARDWARE_BREAK then the पूर्णांकerface
 *	will also be called with actual बार and the hardware is expected
 *	to करो the delay work itself. 0 and -1 are still used क्रम on/off.
 *
 *	Optional: Required क्रम TCSBRK/BRKP/etc handling.
 *
 * व्योम (*रुको_until_sent)(काष्ठा tty_काष्ठा *tty, पूर्णांक समयout);
 * 
 * 	This routine रुकोs until the device has written out all of the
 * 	अक्षरacters in its transmitter FIFO.
 *
 *	Optional: If not provided the device is assumed to have no FIFO
 *
 *	Note: Usually correct to call tty_रुको_until_sent
 *
 * व्योम (*send_xअक्षर)(काष्ठा tty_काष्ठा *tty, अक्षर ch);
 *
 * 	This routine is used to send a high-priority XON/XOFF
 * 	अक्षरacter to the device.
 *
 *	Optional: If not provided then the ग_लिखो method is called under
 *	the atomic ग_लिखो lock to keep it serialized with the ldisc.
 *
 * पूर्णांक (*resize)(काष्ठा tty_काष्ठा *tty, काष्ठा winsize *ws)
 *
 *	Called when a termios request is issued which changes the
 *	requested terminal geometry.
 *
 *	Optional: the शेष action is to update the termios काष्ठाure
 *	without error. This is usually the correct behaviour. Drivers should
 *	not क्रमce errors here अगर they are not resizable objects (eg a serial
 *	line). See tty_करो_resize() अगर you need to wrap the standard method
 *	in your own logic - the usual हाल.
 *
 * पूर्णांक (*get_icount)(काष्ठा tty_काष्ठा *tty, काष्ठा serial_icounter *icount);
 *
 *	Called when the device receives a TIOCGICOUNT ioctl. Passed a kernel
 *	काष्ठाure to complete. This method is optional and will only be called
 *	अगर provided (otherwise ENOTTY will be वापसed).
 */

#समावेश <linux/export.h>
#समावेश <linux/fs.h>
#समावेश <linux/list.h>
#समावेश <linux/cdev.h>
#समावेश <linux/termios.h>
#समावेश <linux/seq_file.h>

काष्ठा tty_काष्ठा;
काष्ठा tty_driver;
काष्ठा serial_icounter_काष्ठा;
काष्ठा serial_काष्ठा;

काष्ठा tty_operations अणु
	काष्ठा tty_काष्ठा * (*lookup)(काष्ठा tty_driver *driver,
			काष्ठा file *filp, पूर्णांक idx);
	पूर्णांक  (*install)(काष्ठा tty_driver *driver, काष्ठा tty_काष्ठा *tty);
	व्योम (*हटाओ)(काष्ठा tty_driver *driver, काष्ठा tty_काष्ठा *tty);
	पूर्णांक  (*खोलो)(काष्ठा tty_काष्ठा * tty, काष्ठा file * filp);
	व्योम (*बंद)(काष्ठा tty_काष्ठा * tty, काष्ठा file * filp);
	व्योम (*shutकरोwn)(काष्ठा tty_काष्ठा *tty);
	व्योम (*cleanup)(काष्ठा tty_काष्ठा *tty);
	पूर्णांक  (*ग_लिखो)(काष्ठा tty_काष्ठा * tty,
		      स्थिर अचिन्हित अक्षर *buf, पूर्णांक count);
	पूर्णांक  (*put_अक्षर)(काष्ठा tty_काष्ठा *tty, अचिन्हित अक्षर ch);
	व्योम (*flush_अक्षरs)(काष्ठा tty_काष्ठा *tty);
	पूर्णांक  (*ग_लिखो_room)(काष्ठा tty_काष्ठा *tty);
	पूर्णांक  (*अक्षरs_in_buffer)(काष्ठा tty_काष्ठा *tty);
	पूर्णांक  (*ioctl)(काष्ठा tty_काष्ठा *tty,
		    अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);
	दीर्घ (*compat_ioctl)(काष्ठा tty_काष्ठा *tty,
			     अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);
	व्योम (*set_termios)(काष्ठा tty_काष्ठा *tty, काष्ठा ktermios * old);
	व्योम (*throttle)(काष्ठा tty_काष्ठा * tty);
	व्योम (*unthrottle)(काष्ठा tty_काष्ठा * tty);
	व्योम (*stop)(काष्ठा tty_काष्ठा *tty);
	व्योम (*start)(काष्ठा tty_काष्ठा *tty);
	व्योम (*hangup)(काष्ठा tty_काष्ठा *tty);
	पूर्णांक (*अवरोध_ctl)(काष्ठा tty_काष्ठा *tty, पूर्णांक state);
	व्योम (*flush_buffer)(काष्ठा tty_काष्ठा *tty);
	व्योम (*set_ldisc)(काष्ठा tty_काष्ठा *tty);
	व्योम (*रुको_until_sent)(काष्ठा tty_काष्ठा *tty, पूर्णांक समयout);
	व्योम (*send_xअक्षर)(काष्ठा tty_काष्ठा *tty, अक्षर ch);
	पूर्णांक (*tiocmget)(काष्ठा tty_काष्ठा *tty);
	पूर्णांक (*tiocmset)(काष्ठा tty_काष्ठा *tty,
			अचिन्हित पूर्णांक set, अचिन्हित पूर्णांक clear);
	पूर्णांक (*resize)(काष्ठा tty_काष्ठा *tty, काष्ठा winsize *ws);
	पूर्णांक (*get_icount)(काष्ठा tty_काष्ठा *tty,
				काष्ठा serial_icounter_काष्ठा *icount);
	पूर्णांक  (*get_serial)(काष्ठा tty_काष्ठा *tty, काष्ठा serial_काष्ठा *p);
	पूर्णांक  (*set_serial)(काष्ठा tty_काष्ठा *tty, काष्ठा serial_काष्ठा *p);
	व्योम (*show_fdinfo)(काष्ठा tty_काष्ठा *tty, काष्ठा seq_file *m);
#अगर_घोषित CONFIG_CONSOLE_POLL
	पूर्णांक (*poll_init)(काष्ठा tty_driver *driver, पूर्णांक line, अक्षर *options);
	पूर्णांक (*poll_get_अक्षर)(काष्ठा tty_driver *driver, पूर्णांक line);
	व्योम (*poll_put_अक्षर)(काष्ठा tty_driver *driver, पूर्णांक line, अक्षर ch);
#पूर्ण_अगर
	पूर्णांक (*proc_show)(काष्ठा seq_file *, व्योम *);
पूर्ण __अक्रमomize_layout;

काष्ठा tty_driver अणु
	पूर्णांक	magic;		/* magic number क्रम this काष्ठाure */
	काष्ठा kref kref;	/* Reference management */
	काष्ठा cdev **cdevs;
	काष्ठा module	*owner;
	स्थिर अक्षर	*driver_name;
	स्थिर अक्षर	*name;
	पूर्णांक	name_base;	/* offset of prपूर्णांकed name */
	पूर्णांक	major;		/* major device number */
	पूर्णांक	minor_start;	/* start of minor device number */
	अचिन्हित पूर्णांक	num;	/* number of devices allocated */
	लघु	type;		/* type of tty driver */
	लघु	subtype;	/* subtype of tty driver */
	काष्ठा ktermios init_termios; /* Initial termios */
	अचिन्हित दीर्घ	flags;		/* tty driver flags */
	काष्ठा proc_dir_entry *proc_entry; /* /proc fs entry */
	काष्ठा tty_driver *other; /* only used क्रम the PTY driver */

	/*
	 * Poपूर्णांकer to the tty data काष्ठाures
	 */
	काष्ठा tty_काष्ठा **ttys;
	काष्ठा tty_port **ports;
	काष्ठा ktermios **termios;
	व्योम *driver_state;

	/*
	 * Driver methods
	 */

	स्थिर काष्ठा tty_operations *ops;
	काष्ठा list_head tty_drivers;
पूर्ण __अक्रमomize_layout;

बाह्य काष्ठा list_head tty_drivers;

बाह्य काष्ठा tty_driver *__tty_alloc_driver(अचिन्हित पूर्णांक lines,
		काष्ठा module *owner, अचिन्हित दीर्घ flags);
बाह्य व्योम put_tty_driver(काष्ठा tty_driver *driver);
बाह्य व्योम tty_set_operations(काष्ठा tty_driver *driver,
			स्थिर काष्ठा tty_operations *op);
बाह्य काष्ठा tty_driver *tty_find_polling_driver(अक्षर *name, पूर्णांक *line);

बाह्य व्योम tty_driver_kref_put(काष्ठा tty_driver *driver);

/* Use TTY_DRIVER_* flags below */
#घोषणा tty_alloc_driver(lines, flags) \
		__tty_alloc_driver(lines, THIS_MODULE, flags)

/*
 * DEPRECATED Do not use this in new code, use tty_alloc_driver instead.
 * (And change the वापस value checks.)
 */
अटल अंतरभूत काष्ठा tty_driver *alloc_tty_driver(अचिन्हित पूर्णांक lines)
अणु
	काष्ठा tty_driver *ret = tty_alloc_driver(lines, 0);
	अगर (IS_ERR(ret))
		वापस शून्य;
	वापस ret;
पूर्ण

अटल अंतरभूत काष्ठा tty_driver *tty_driver_kref_get(काष्ठा tty_driver *d)
अणु
	kref_get(&d->kref);
	वापस d;
पूर्ण

/* tty driver magic number */
#घोषणा TTY_DRIVER_MAGIC		0x5402

/*
 * tty driver flags
 * 
 * TTY_DRIVER_RESET_TERMIOS --- requests the tty layer to reset the
 * 	termios setting when the last process has बंदd the device.
 * 	Used क्रम PTY's, in particular.
 * 
 * TTY_DRIVER_REAL_RAW --- अगर set, indicates that the driver will
 * 	guarantee never not to set any special अक्षरacter handling
 * 	flags अगर ((IGNBRK || (!BRKINT && !PARMRK)) && (IGNPAR ||
 * 	!INPCK)).  That is, अगर there is no reason क्रम the driver to
 * 	send notअगरications of parity and अवरोध अक्षरacters up to the
 * 	line driver, it won't करो so.  This allows the line driver to
 *	optimize क्रम this हाल अगर this flag is set.  (Note that there
 * 	is also a promise, अगर the above हाल is true, not to संकेत
 * 	overruns, either.)
 *
 * TTY_DRIVER_DYNAMIC_DEV --- अगर set, the inभागidual tty devices need
 *	to be रेजिस्टरed with a call to tty_रेजिस्टर_device() when the
 *	device is found in the प्रणाली and unरेजिस्टरed with a call to
 *	tty_unरेजिस्टर_device() so the devices will be show up
 *	properly in sysfs.  If not set, driver->num entries will be
 *	created by the tty core in sysfs when tty_रेजिस्टर_driver() is
 *	called.  This is to be used by drivers that have tty devices
 *	that can appear and disappear जबतक the मुख्य tty driver is
 *	रेजिस्टरed with the tty core.
 *
 * TTY_DRIVER_DEVPTS_MEM -- करोn't use the standard arrays, instead
 *	use dynamic memory keyed through the devpts fileप्रणाली.  This
 *	is only applicable to the pty driver.
 *
 * TTY_DRIVER_HARDWARE_BREAK -- hardware handles अवरोध संकेतs. Pass
 *	the requested समयout to the caller instead of using a simple
 *	on/off पूर्णांकerface.
 *
 * TTY_DRIVER_DYNAMIC_ALLOC -- करो not allocate काष्ठाures which are
 *	needed per line क्रम this driver as it would waste memory.
 *	The driver will take care.
 *
 * TTY_DRIVER_UNNUMBERED_NODE -- करो not create numbered /dev nodes. In
 *	other words create /dev/ttyprपूर्णांकk and not /dev/ttyprपूर्णांकk0.
 *	Applicable only when a driver क्रम a single tty device is
 *	being allocated.
 */
#घोषणा TTY_DRIVER_INSTALLED		0x0001
#घोषणा TTY_DRIVER_RESET_TERMIOS	0x0002
#घोषणा TTY_DRIVER_REAL_RAW		0x0004
#घोषणा TTY_DRIVER_DYNAMIC_DEV		0x0008
#घोषणा TTY_DRIVER_DEVPTS_MEM		0x0010
#घोषणा TTY_DRIVER_HARDWARE_BREAK	0x0020
#घोषणा TTY_DRIVER_DYNAMIC_ALLOC	0x0040
#घोषणा TTY_DRIVER_UNNUMBERED_NODE	0x0080

/* tty driver types */
#घोषणा TTY_DRIVER_TYPE_SYSTEM		0x0001
#घोषणा TTY_DRIVER_TYPE_CONSOLE		0x0002
#घोषणा TTY_DRIVER_TYPE_SERIAL		0x0003
#घोषणा TTY_DRIVER_TYPE_PTY		0x0004
#घोषणा TTY_DRIVER_TYPE_SCC		0x0005	/* scc driver */
#घोषणा TTY_DRIVER_TYPE_SYSCONS		0x0006

/* प्रणाली subtypes (magic, used by tty_io.c) */
#घोषणा SYSTEM_TYPE_TTY			0x0001
#घोषणा SYSTEM_TYPE_CONSOLE		0x0002
#घोषणा SYSTEM_TYPE_SYSCONS		0x0003
#घोषणा SYSTEM_TYPE_SYSPTMX		0x0004

/* pty subtypes (magic, used by tty_io.c) */
#घोषणा PTY_TYPE_MASTER			0x0001
#घोषणा PTY_TYPE_SLAVE			0x0002

/* serial subtype definitions */
#घोषणा SERIAL_TYPE_NORMAL	1

#पूर्ण_अगर /* #अगर_घोषित _LINUX_TTY_DRIVER_H */
