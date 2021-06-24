<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Input device TTY line discipline
 *
 * Copyright (c) 1999-2002 Vojtech Pavlik
 *
 * This is a module that converts a tty line पूर्णांकo a much simpler
 * 'serial io port' असलtraction that the input device drivers use.
 */


#समावेश <linux/uaccess.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/serपन.स>
#समावेश <linux/tty.h>
#समावेश <linux/compat.h>

MODULE_AUTHOR("Vojtech Pavlik <vojtech@ucw.cz>");
MODULE_DESCRIPTION("Input device TTY line discipline");
MODULE_LICENSE("GPL");
MODULE_ALIAS_LDISC(N_MOUSE);

#घोषणा SERPORT_BUSY	1
#घोषणा SERPORT_ACTIVE	2
#घोषणा SERPORT_DEAD	3

काष्ठा serport अणु
	काष्ठा tty_काष्ठा *tty;
	रुको_queue_head_t रुको;
	काष्ठा serio *serio;
	काष्ठा serio_device_id id;
	spinlock_t lock;
	अचिन्हित दीर्घ flags;
पूर्ण;

/*
 * Callback functions from the serio code.
 */

अटल पूर्णांक serport_serio_ग_लिखो(काष्ठा serio *serio, अचिन्हित अक्षर data)
अणु
	काष्ठा serport *serport = serio->port_data;
	वापस -(serport->tty->ops->ग_लिखो(serport->tty, &data, 1) != 1);
पूर्ण

अटल पूर्णांक serport_serio_खोलो(काष्ठा serio *serio)
अणु
	काष्ठा serport *serport = serio->port_data;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&serport->lock, flags);
	set_bit(SERPORT_ACTIVE, &serport->flags);
	spin_unlock_irqrestore(&serport->lock, flags);

	वापस 0;
पूर्ण


अटल व्योम serport_serio_बंद(काष्ठा serio *serio)
अणु
	काष्ठा serport *serport = serio->port_data;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&serport->lock, flags);
	clear_bit(SERPORT_ACTIVE, &serport->flags);
	spin_unlock_irqrestore(&serport->lock, flags);
पूर्ण

/*
 * serport_ldisc_खोलो() is the routine that is called upon setting our line
 * discipline on a tty. It prepares the serio काष्ठा.
 */

अटल पूर्णांक serport_ldisc_खोलो(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा serport *serport;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	serport = kzalloc(माप(काष्ठा serport), GFP_KERNEL);
	अगर (!serport)
		वापस -ENOMEM;

	serport->tty = tty;
	spin_lock_init(&serport->lock);
	init_रुकोqueue_head(&serport->रुको);

	tty->disc_data = serport;
	tty->receive_room = 256;
	set_bit(TTY_DO_WRITE_WAKEUP, &tty->flags);

	वापस 0;
पूर्ण

/*
 * serport_ldisc_बंद() is the opposite of serport_ldisc_खोलो()
 */

अटल व्योम serport_ldisc_बंद(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा serport *serport = (काष्ठा serport *) tty->disc_data;

	kमुक्त(serport);
पूर्ण

/*
 * serport_ldisc_receive() is called by the low level tty driver when अक्षरacters
 * are पढ़ोy क्रम us. We क्रमward the अक्षरacters and flags, one by one to the
 * 'interrupt' routine.
 */

अटल व्योम serport_ldisc_receive(काष्ठा tty_काष्ठा *tty, स्थिर अचिन्हित अक्षर *cp, अक्षर *fp, पूर्णांक count)
अणु
	काष्ठा serport *serport = (काष्ठा serport*) tty->disc_data;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक ch_flags = 0;
	पूर्णांक i;

	spin_lock_irqsave(&serport->lock, flags);

	अगर (!test_bit(SERPORT_ACTIVE, &serport->flags))
		जाओ out;

	क्रम (i = 0; i < count; i++) अणु
		अगर (fp) अणु
			चयन (fp[i]) अणु
			हाल TTY_FRAME:
				ch_flags = SERIO_FRAME;
				अवरोध;

			हाल TTY_PARITY:
				ch_flags = SERIO_PARITY;
				अवरोध;

			शेष:
				ch_flags = 0;
				अवरोध;
			पूर्ण
		पूर्ण

		serio_पूर्णांकerrupt(serport->serio, cp[i], ch_flags);
	पूर्ण

out:
	spin_unlock_irqrestore(&serport->lock, flags);
पूर्ण

/*
 * serport_ldisc_पढ़ो() just रुकोs indefinitely अगर everything goes well.
 * However, when the serio driver बंदs the serio port, it finishes,
 * वापसing 0 अक्षरacters.
 */

अटल sमाप_प्रकार serport_ldisc_पढ़ो(काष्ठा tty_काष्ठा * tty, काष्ठा file * file,
				  अचिन्हित अक्षर *kbuf, माप_प्रकार nr,
				  व्योम **cookie, अचिन्हित दीर्घ offset)
अणु
	काष्ठा serport *serport = (काष्ठा serport*) tty->disc_data;
	काष्ठा serio *serio;

	अगर (test_and_set_bit(SERPORT_BUSY, &serport->flags))
		वापस -EBUSY;

	serport->serio = serio = kzalloc(माप(काष्ठा serio), GFP_KERNEL);
	अगर (!serio)
		वापस -ENOMEM;

	strlcpy(serio->name, "Serial port", माप(serio->name));
	snम_लिखो(serio->phys, माप(serio->phys), "%s/serio0", tty_name(tty));
	serio->id = serport->id;
	serio->id.type = SERIO_RS232;
	serio->ग_लिखो = serport_serio_ग_लिखो;
	serio->खोलो = serport_serio_खोलो;
	serio->बंद = serport_serio_बंद;
	serio->port_data = serport;
	serio->dev.parent = tty->dev;

	serio_रेजिस्टर_port(serport->serio);
	prपूर्णांकk(KERN_INFO "serio: Serial port %s\n", tty_name(tty));

	रुको_event_पूर्णांकerruptible(serport->रुको, test_bit(SERPORT_DEAD, &serport->flags));
	serio_unरेजिस्टर_port(serport->serio);
	serport->serio = शून्य;

	clear_bit(SERPORT_DEAD, &serport->flags);
	clear_bit(SERPORT_BUSY, &serport->flags);

	वापस 0;
पूर्ण

अटल व्योम serport_set_type(काष्ठा tty_काष्ठा *tty, अचिन्हित दीर्घ type)
अणु
	काष्ठा serport *serport = tty->disc_data;

	serport->id.proto = type & 0x000000ff;
	serport->id.id    = (type & 0x0000ff00) >> 8;
	serport->id.extra = (type & 0x00ff0000) >> 16;
पूर्ण

/*
 * serport_ldisc_ioctl() allows to set the port protocol, and device ID
 */

अटल पूर्णांक serport_ldisc_ioctl(काष्ठा tty_काष्ठा *tty, काष्ठा file *file,
			       अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	अगर (cmd == SPIOCSTYPE) अणु
		अचिन्हित दीर्घ type;

		अगर (get_user(type, (अचिन्हित दीर्घ __user *) arg))
			वापस -EFAULT;

		serport_set_type(tty, type);
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

#अगर_घोषित CONFIG_COMPAT
#घोषणा COMPAT_SPIOCSTYPE	_IOW('q', 0x01, compat_uदीर्घ_t)
अटल पूर्णांक serport_ldisc_compat_ioctl(काष्ठा tty_काष्ठा *tty,
				       काष्ठा file *file,
				       अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	अगर (cmd == COMPAT_SPIOCSTYPE) अणु
		व्योम __user *uarg = compat_ptr(arg);
		compat_uदीर्घ_t compat_type;

		अगर (get_user(compat_type, (compat_uदीर्घ_t __user *)uarg))
			वापस -EFAULT;

		serport_set_type(tty, compat_type);
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक serport_ldisc_hangup(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा serport *serport = (काष्ठा serport *) tty->disc_data;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&serport->lock, flags);
	set_bit(SERPORT_DEAD, &serport->flags);
	spin_unlock_irqrestore(&serport->lock, flags);

	wake_up_पूर्णांकerruptible(&serport->रुको);
	वापस 0;
पूर्ण

अटल व्योम serport_ldisc_ग_लिखो_wakeup(काष्ठा tty_काष्ठा * tty)
अणु
	काष्ठा serport *serport = (काष्ठा serport *) tty->disc_data;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&serport->lock, flags);
	अगर (test_bit(SERPORT_ACTIVE, &serport->flags))
		serio_drv_ग_लिखो_wakeup(serport->serio);
	spin_unlock_irqrestore(&serport->lock, flags);
पूर्ण

/*
 * The line discipline काष्ठाure.
 */

अटल काष्ठा tty_ldisc_ops serport_ldisc = अणु
	.owner =	THIS_MODULE,
	.name =		"input",
	.खोलो =		serport_ldisc_खोलो,
	.बंद =	serport_ldisc_बंद,
	.पढ़ो =		serport_ldisc_पढ़ो,
	.ioctl =	serport_ldisc_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl =	serport_ldisc_compat_ioctl,
#पूर्ण_अगर
	.receive_buf =	serport_ldisc_receive,
	.hangup =	serport_ldisc_hangup,
	.ग_लिखो_wakeup =	serport_ldisc_ग_लिखो_wakeup
पूर्ण;

/*
 * The functions क्रम insering/removing us as a module.
 */

अटल पूर्णांक __init serport_init(व्योम)
अणु
	पूर्णांक retval;
	retval = tty_रेजिस्टर_ldisc(N_MOUSE, &serport_ldisc);
	अगर (retval)
		prपूर्णांकk(KERN_ERR "serport.c: Error registering line discipline.\n");

	वापस  retval;
पूर्ण

अटल व्योम __निकास serport_निकास(व्योम)
अणु
	tty_unरेजिस्टर_ldisc(N_MOUSE);
पूर्ण

module_init(serport_init);
module_निकास(serport_निकास);
