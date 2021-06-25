<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/drivers/अक्षर/ttyprपूर्णांकk.c
 *
 *  Copyright (C) 2010  Samo Pogacnik
 */

/*
 * This pseuकरो device allows user to make prपूर्णांकk messages. It is possible
 * to store "console" messages अंतरभूत with kernel messages क्रम better analyses
 * of the boot process, क्रम example.
 */

#समावेश <linux/device.h>
#समावेश <linux/serial.h>
#समावेश <linux/tty.h>
#समावेश <linux/module.h>
#समावेश <linux/spinlock.h>

काष्ठा ttyprपूर्णांकk_port अणु
	काष्ठा tty_port port;
	spinlock_t spinlock;
पूर्ण;

अटल काष्ठा ttyprपूर्णांकk_port tpk_port;

/*
 * Our simple preक्रमmatting supports transparent output of (समय-stamped)
 * prपूर्णांकk messages (also suitable क्रम logging service):
 * - any cr is replaced by nl
 * - adds a ttyprपूर्णांकk source tag in front of each line
 * - too दीर्घ message is fragmented, with '\'nl between fragments
 * - TPK_STR_SIZE isn't really the ग_लिखो_room limiting factor, because
 *   it is emptied on the fly during preक्रमmatting.
 */
#घोषणा TPK_STR_SIZE 508 /* should be bigger then max expected line length */
#घोषणा TPK_MAX_ROOM 4096 /* we could assume 4K क्रम instance */
#घोषणा TPK_PREFIX KERN_SOH __stringअगरy(CONFIG_TTY_PRINTK_LEVEL)

अटल पूर्णांक tpk_curr;

अटल अक्षर tpk_buffer[TPK_STR_SIZE + 4];

अटल व्योम tpk_flush(व्योम)
अणु
	अगर (tpk_curr > 0) अणु
		tpk_buffer[tpk_curr] = '\0';
		prपूर्णांकk(TPK_PREFIX "[U] %s\n", tpk_buffer);
		tpk_curr = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक tpk_prपूर्णांकk(स्थिर अचिन्हित अक्षर *buf, पूर्णांक count)
अणु
	पूर्णांक i = tpk_curr;

	अगर (buf == शून्य) अणु
		tpk_flush();
		वापस i;
	पूर्ण

	क्रम (i = 0; i < count; i++) अणु
		अगर (tpk_curr >= TPK_STR_SIZE) अणु
			/* end of पंचांगp buffer reached: cut the message in two */
			tpk_buffer[tpk_curr++] = '\\';
			tpk_flush();
		पूर्ण

		चयन (buf[i]) अणु
		हाल '\r':
			tpk_flush();
			अगर ((i + 1) < count && buf[i + 1] == '\n')
				i++;
			अवरोध;
		हाल '\n':
			tpk_flush();
			अवरोध;
		शेष:
			tpk_buffer[tpk_curr++] = buf[i];
			अवरोध;
		पूर्ण
	पूर्ण

	वापस count;
पूर्ण

/*
 * TTY operations खोलो function.
 */
अटल पूर्णांक tpk_खोलो(काष्ठा tty_काष्ठा *tty, काष्ठा file *filp)
अणु
	tty->driver_data = &tpk_port;

	वापस tty_port_खोलो(&tpk_port.port, tty, filp);
पूर्ण

/*
 * TTY operations बंद function.
 */
अटल व्योम tpk_बंद(काष्ठा tty_काष्ठा *tty, काष्ठा file *filp)
अणु
	काष्ठा ttyprपूर्णांकk_port *tpkp = tty->driver_data;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&tpkp->spinlock, flags);
	/* flush tpk_prपूर्णांकk buffer */
	tpk_prपूर्णांकk(शून्य, 0);
	spin_unlock_irqrestore(&tpkp->spinlock, flags);

	tty_port_बंद(&tpkp->port, tty, filp);
पूर्ण

/*
 * TTY operations ग_लिखो function.
 */
अटल पूर्णांक tpk_ग_लिखो(काष्ठा tty_काष्ठा *tty,
		स्थिर अचिन्हित अक्षर *buf, पूर्णांक count)
अणु
	काष्ठा ttyprपूर्णांकk_port *tpkp = tty->driver_data;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;


	/* exclusive use of tpk_prपूर्णांकk within this tty */
	spin_lock_irqsave(&tpkp->spinlock, flags);
	ret = tpk_prपूर्णांकk(buf, count);
	spin_unlock_irqrestore(&tpkp->spinlock, flags);

	वापस ret;
पूर्ण

/*
 * TTY operations ग_लिखो_room function.
 */
अटल पूर्णांक tpk_ग_लिखो_room(काष्ठा tty_काष्ठा *tty)
अणु
	वापस TPK_MAX_ROOM;
पूर्ण

/*
 * TTY operations ioctl function.
 */
अटल पूर्णांक tpk_ioctl(काष्ठा tty_काष्ठा *tty,
			अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा ttyprपूर्णांकk_port *tpkp = tty->driver_data;

	अगर (!tpkp)
		वापस -EINVAL;

	चयन (cmd) अणु
	/* Stop TIOCCONS */
	हाल TIOCCONS:
		वापस -EOPNOTSUPP;
	शेष:
		वापस -ENOIOCTLCMD;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * TTY operations hangup function.
 */
अटल व्योम tpk_hangup(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा ttyprपूर्णांकk_port *tpkp = tty->driver_data;

	tty_port_hangup(&tpkp->port);
पूर्ण

अटल स्थिर काष्ठा tty_operations ttyprपूर्णांकk_ops = अणु
	.खोलो = tpk_खोलो,
	.बंद = tpk_बंद,
	.ग_लिखो = tpk_ग_लिखो,
	.ग_लिखो_room = tpk_ग_लिखो_room,
	.ioctl = tpk_ioctl,
	.hangup = tpk_hangup,
पूर्ण;

अटल स्थिर काष्ठा tty_port_operations null_ops = अणु पूर्ण;

अटल काष्ठा tty_driver *ttyprपूर्णांकk_driver;

अटल पूर्णांक __init ttyprपूर्णांकk_init(व्योम)
अणु
	पूर्णांक ret;

	spin_lock_init(&tpk_port.spinlock);

	ttyprपूर्णांकk_driver = tty_alloc_driver(1,
			TTY_DRIVER_RESET_TERMIOS |
			TTY_DRIVER_REAL_RAW |
			TTY_DRIVER_UNNUMBERED_NODE);
	अगर (IS_ERR(ttyprपूर्णांकk_driver))
		वापस PTR_ERR(ttyprपूर्णांकk_driver);

	tty_port_init(&tpk_port.port);
	tpk_port.port.ops = &null_ops;

	ttyprपूर्णांकk_driver->driver_name = "ttyprintk";
	ttyprपूर्णांकk_driver->name = "ttyprintk";
	ttyprपूर्णांकk_driver->major = TTYAUX_MAJOR;
	ttyprपूर्णांकk_driver->minor_start = 3;
	ttyprपूर्णांकk_driver->type = TTY_DRIVER_TYPE_CONSOLE;
	ttyprपूर्णांकk_driver->init_termios = tty_std_termios;
	ttyprपूर्णांकk_driver->init_termios.c_oflag = OPOST | OCRNL | ONOCR | ONLRET;
	tty_set_operations(ttyprपूर्णांकk_driver, &ttyprपूर्णांकk_ops);
	tty_port_link_device(&tpk_port.port, ttyprपूर्णांकk_driver, 0);

	ret = tty_रेजिस्टर_driver(ttyprपूर्णांकk_driver);
	अगर (ret < 0) अणु
		prपूर्णांकk(KERN_ERR "Couldn't register ttyprintk driver\n");
		जाओ error;
	पूर्ण

	वापस 0;

error:
	put_tty_driver(ttyprपूर्णांकk_driver);
	tty_port_destroy(&tpk_port.port);
	वापस ret;
पूर्ण

अटल व्योम __निकास ttyprपूर्णांकk_निकास(व्योम)
अणु
	tty_unरेजिस्टर_driver(ttyprपूर्णांकk_driver);
	put_tty_driver(ttyprपूर्णांकk_driver);
	tty_port_destroy(&tpk_port.port);
पूर्ण

device_initcall(ttyprपूर्णांकk_init);
module_निकास(ttyprपूर्णांकk_निकास);

MODULE_LICENSE("GPL");
