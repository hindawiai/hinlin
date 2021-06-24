<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Copyright (C) 1991, 1992, 1993, 1994  Linus Torvalds
 *
 * Modअगरied by Fred N. van Kempen, 01/29/93, to add line disciplines
 * which can be dynamically activated and de-activated by the line
 * discipline handling modules (like SLIP).
 */

#समावेश <linux/types.h>
#समावेश <linux/termios.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/kernel.h>
#समावेश <linux/major.h>
#समावेश <linux/tty.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/bitops.h>
#समावेश <linux/mutex.h>
#समावेश <linux/compat.h>
#समावेश "tty.h"

#समावेश <यंत्र/पन.स>
#समावेश <linux/uaccess.h>

#अघोषित TTY_DEBUG_WAIT_UNTIL_SENT

#अगर_घोषित TTY_DEBUG_WAIT_UNTIL_SENT
# define tty_debug_रुको_until_sent(tty, f, args...)    tty_debug(tty, f, ##args)
#अन्यथा
# define tty_debug_रुको_until_sent(tty, f, args...)    करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर

#अघोषित	DEBUG

/*
 * Internal flag options क्रम termios setting behavior
 */
#घोषणा TERMIOS_FLUSH	1
#घोषणा TERMIOS_WAIT	2
#घोषणा TERMIOS_TERMIO	4
#घोषणा TERMIOS_OLD	8


/**
 *	tty_अक्षरs_in_buffer	-	अक्षरacters pending
 *	@tty: terminal
 *
 *	Return the number of bytes of data in the device निजी
 *	output queue. If no निजी method is supplied there is assumed
 *	to be no queue on the device.
 */

पूर्णांक tty_अक्षरs_in_buffer(काष्ठा tty_काष्ठा *tty)
अणु
	अगर (tty->ops->अक्षरs_in_buffer)
		वापस tty->ops->अक्षरs_in_buffer(tty);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(tty_अक्षरs_in_buffer);

/**
 *	tty_ग_लिखो_room		-	ग_लिखो queue space
 *	@tty: terminal
 *
 *	Return the number of bytes that can be queued to this device
 *	at the present समय. The result should be treated as a guarantee
 *	and the driver cannot offer a value it later shrinks by more than
 *	the number of bytes written. If no method is provided 2K is always
 *	वापसed and data may be lost as there will be no flow control.
 */
 
पूर्णांक tty_ग_लिखो_room(काष्ठा tty_काष्ठा *tty)
अणु
	अगर (tty->ops->ग_लिखो_room)
		वापस tty->ops->ग_लिखो_room(tty);
	वापस 2048;
पूर्ण
EXPORT_SYMBOL(tty_ग_लिखो_room);

/**
 *	tty_driver_flush_buffer	-	discard पूर्णांकernal buffer
 *	@tty: terminal
 *
 *	Discard the पूर्णांकernal output buffer क्रम this device. If no method
 *	is provided then either the buffer cannot be hardware flushed or
 *	there is no buffer driver side.
 */
व्योम tty_driver_flush_buffer(काष्ठा tty_काष्ठा *tty)
अणु
	अगर (tty->ops->flush_buffer)
		tty->ops->flush_buffer(tty);
पूर्ण
EXPORT_SYMBOL(tty_driver_flush_buffer);

/**
 *	tty_throttle		-	flow control
 *	@tty: terminal
 *
 *	Indicate that a tty should stop transmitting data करोwn the stack.
 *	Takes the termios rwsem to protect against parallel throttle/unthrottle
 *	and also to ensure the driver can consistently reference its own
 *	termios data at this poपूर्णांक when implementing software flow control.
 */

व्योम tty_throttle(काष्ठा tty_काष्ठा *tty)
अणु
	करोwn_ग_लिखो(&tty->termios_rwsem);
	/* check TTY_THROTTLED first so it indicates our state */
	अगर (!test_and_set_bit(TTY_THROTTLED, &tty->flags) &&
	    tty->ops->throttle)
		tty->ops->throttle(tty);
	tty->flow_change = 0;
	up_ग_लिखो(&tty->termios_rwsem);
पूर्ण
EXPORT_SYMBOL(tty_throttle);

/**
 *	tty_unthrottle		-	flow control
 *	@tty: terminal
 *
 *	Indicate that a tty may जारी transmitting data करोwn the stack.
 *	Takes the termios rwsem to protect against parallel throttle/unthrottle
 *	and also to ensure the driver can consistently reference its own
 *	termios data at this poपूर्णांक when implementing software flow control.
 *
 *	Drivers should however remember that the stack can issue a throttle,
 *	then change flow control method, then unthrottle.
 */

व्योम tty_unthrottle(काष्ठा tty_काष्ठा *tty)
अणु
	करोwn_ग_लिखो(&tty->termios_rwsem);
	अगर (test_and_clear_bit(TTY_THROTTLED, &tty->flags) &&
	    tty->ops->unthrottle)
		tty->ops->unthrottle(tty);
	tty->flow_change = 0;
	up_ग_लिखो(&tty->termios_rwsem);
पूर्ण
EXPORT_SYMBOL(tty_unthrottle);

/**
 *	tty_throttle_safe	-	flow control
 *	@tty: terminal
 *
 *	Similar to tty_throttle() but will only attempt throttle
 *	अगर tty->flow_change is TTY_THROTTLE_SAFE. Prevents an accidental
 *	throttle due to race conditions when throttling is conditional
 *	on factors evaluated prior to throttling.
 *
 *	Returns 0 अगर tty is throttled (or was alपढ़ोy throttled)
 */

पूर्णांक tty_throttle_safe(काष्ठा tty_काष्ठा *tty)
अणु
	पूर्णांक ret = 0;

	mutex_lock(&tty->throttle_mutex);
	अगर (!tty_throttled(tty)) अणु
		अगर (tty->flow_change != TTY_THROTTLE_SAFE)
			ret = 1;
		अन्यथा अणु
			set_bit(TTY_THROTTLED, &tty->flags);
			अगर (tty->ops->throttle)
				tty->ops->throttle(tty);
		पूर्ण
	पूर्ण
	mutex_unlock(&tty->throttle_mutex);

	वापस ret;
पूर्ण

/**
 *	tty_unthrottle_safe	-	flow control
 *	@tty: terminal
 *
 *	Similar to tty_unthrottle() but will only attempt unthrottle
 *	अगर tty->flow_change is TTY_UNTHROTTLE_SAFE. Prevents an accidental
 *	unthrottle due to race conditions when unthrottling is conditional
 *	on factors evaluated prior to unthrottling.
 *
 *	Returns 0 अगर tty is unthrottled (or was alपढ़ोy unthrottled)
 */

पूर्णांक tty_unthrottle_safe(काष्ठा tty_काष्ठा *tty)
अणु
	पूर्णांक ret = 0;

	mutex_lock(&tty->throttle_mutex);
	अगर (tty_throttled(tty)) अणु
		अगर (tty->flow_change != TTY_UNTHROTTLE_SAFE)
			ret = 1;
		अन्यथा अणु
			clear_bit(TTY_THROTTLED, &tty->flags);
			अगर (tty->ops->unthrottle)
				tty->ops->unthrottle(tty);
		पूर्ण
	पूर्ण
	mutex_unlock(&tty->throttle_mutex);

	वापस ret;
पूर्ण

/**
 *	tty_रुको_until_sent	-	रुको क्रम I/O to finish
 *	@tty: tty we are रुकोing क्रम
 *	@समयout: how दीर्घ we will रुको
 *
 *	Wait क्रम अक्षरacters pending in a tty driver to hit the wire, or
 *	क्रम a समयout to occur (eg due to flow control)
 *
 *	Locking: none
 */

व्योम tty_रुको_until_sent(काष्ठा tty_काष्ठा *tty, दीर्घ समयout)
अणु
	tty_debug_रुको_until_sent(tty, "wait until sent, timeout=%ld\n", समयout);

	अगर (!समयout)
		समयout = MAX_SCHEDULE_TIMEOUT;

	समयout = रुको_event_पूर्णांकerruptible_समयout(tty->ग_लिखो_रुको,
			!tty_अक्षरs_in_buffer(tty), समयout);
	अगर (समयout <= 0)
		वापस;

	अगर (समयout == MAX_SCHEDULE_TIMEOUT)
		समयout = 0;

	अगर (tty->ops->रुको_until_sent)
		tty->ops->रुको_until_sent(tty, समयout);
पूर्ण
EXPORT_SYMBOL(tty_रुको_until_sent);


/*
 *		Termios Helper Methods
 */

अटल व्योम unset_locked_termios(काष्ठा tty_काष्ठा *tty, काष्ठा ktermios *old)
अणु
	काष्ठा ktermios *termios = &tty->termios;
	काष्ठा ktermios *locked  = &tty->termios_locked;
	पूर्णांक	i;

#घोषणा NOSET_MASK(x, y, z) (x = ((x) & ~(z)) | ((y) & (z)))

	NOSET_MASK(termios->c_अगरlag, old->c_अगरlag, locked->c_अगरlag);
	NOSET_MASK(termios->c_oflag, old->c_oflag, locked->c_oflag);
	NOSET_MASK(termios->c_cflag, old->c_cflag, locked->c_cflag);
	NOSET_MASK(termios->c_lflag, old->c_lflag, locked->c_lflag);
	termios->c_line = locked->c_line ? old->c_line : termios->c_line;
	क्रम (i = 0; i < NCCS; i++)
		termios->c_cc[i] = locked->c_cc[i] ?
			old->c_cc[i] : termios->c_cc[i];
	/* FIXME: What should we करो क्रम i/ospeed */
पूर्ण

/**
 *	tty_termios_copy_hw	-	copy hardware settings
 *	@new: New termios
 *	@old: Old termios
 *
 *	Propagate the hardware specअगरic terminal setting bits from
 *	the old termios काष्ठाure to the new one. This is used in हालs
 *	where the hardware करोes not support reconfiguration or as a helper
 *	in some हालs where only minimal reconfiguration is supported
 */

व्योम tty_termios_copy_hw(काष्ठा ktermios *new, काष्ठा ktermios *old)
अणु
	/* The bits a dumb device handles in software. Smart devices need
	   to always provide a set_termios method */
	new->c_cflag &= HUPCL | CREAD | CLOCAL;
	new->c_cflag |= old->c_cflag & ~(HUPCL | CREAD | CLOCAL);
	new->c_ispeed = old->c_ispeed;
	new->c_ospeed = old->c_ospeed;
पूर्ण
EXPORT_SYMBOL(tty_termios_copy_hw);

/**
 *	tty_termios_hw_change	-	check क्रम setting change
 *	@a: termios
 *	@b: termios to compare
 *
 *	Check अगर any of the bits that affect a dumb device have changed
 *	between the two termios काष्ठाures, or a speed change is needed.
 */

पूर्णांक tty_termios_hw_change(स्थिर काष्ठा ktermios *a, स्थिर काष्ठा ktermios *b)
अणु
	अगर (a->c_ispeed != b->c_ispeed || a->c_ospeed != b->c_ospeed)
		वापस 1;
	अगर ((a->c_cflag ^ b->c_cflag) & ~(HUPCL | CREAD | CLOCAL))
		वापस 1;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(tty_termios_hw_change);

/**
 *	tty_set_termios		-	update termios values
 *	@tty: tty to update
 *	@new_termios: desired new value
 *
 *	Perक्रमm updates to the termios values set on this terminal.
 *	A master pty's termios should never be set.
 *
 *	Locking: termios_rwsem
 */

पूर्णांक tty_set_termios(काष्ठा tty_काष्ठा *tty, काष्ठा ktermios *new_termios)
अणु
	काष्ठा ktermios old_termios;
	काष्ठा tty_ldisc *ld;

	WARN_ON(tty->driver->type == TTY_DRIVER_TYPE_PTY &&
		tty->driver->subtype == PTY_TYPE_MASTER);
	/*
	 *	Perक्रमm the actual termios पूर्णांकernal changes under lock.
	 */


	/* FIXME: we need to decide on some locking/ordering semantics
	   क्रम the set_termios notअगरication eventually */
	करोwn_ग_लिखो(&tty->termios_rwsem);
	old_termios = tty->termios;
	tty->termios = *new_termios;
	unset_locked_termios(tty, &old_termios);

	अगर (tty->ops->set_termios)
		tty->ops->set_termios(tty, &old_termios);
	अन्यथा
		tty_termios_copy_hw(&tty->termios, &old_termios);

	ld = tty_ldisc_ref(tty);
	अगर (ld != शून्य) अणु
		अगर (ld->ops->set_termios)
			ld->ops->set_termios(tty, &old_termios);
		tty_ldisc_deref(ld);
	पूर्ण
	up_ग_लिखो(&tty->termios_rwsem);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(tty_set_termios);

/**
 *	set_termios		-	set termios values क्रम a tty
 *	@tty: terminal device
 *	@arg: user data
 *	@opt: option inक्रमmation
 *
 *	Helper function to prepare termios data and run necessary other
 *	functions beक्रमe using tty_set_termios to करो the actual changes.
 *
 *	Locking:
 *		Called functions take ldisc and termios_rwsem locks
 */

अटल पूर्णांक set_termios(काष्ठा tty_काष्ठा *tty, व्योम __user *arg, पूर्णांक opt)
अणु
	काष्ठा ktermios पंचांगp_termios;
	काष्ठा tty_ldisc *ld;
	पूर्णांक retval = tty_check_change(tty);

	अगर (retval)
		वापस retval;

	करोwn_पढ़ो(&tty->termios_rwsem);
	पंचांगp_termios = tty->termios;
	up_पढ़ो(&tty->termios_rwsem);

	अगर (opt & TERMIOS_TERMIO) अणु
		अगर (user_termio_to_kernel_termios(&पंचांगp_termios,
						(काष्ठा termio __user *)arg))
			वापस -EFAULT;
#अगर_घोषित TCGETS2
	पूर्ण अन्यथा अगर (opt & TERMIOS_OLD) अणु
		अगर (user_termios_to_kernel_termios_1(&पंचांगp_termios,
						(काष्ठा termios __user *)arg))
			वापस -EFAULT;
	पूर्ण अन्यथा अणु
		अगर (user_termios_to_kernel_termios(&पंचांगp_termios,
						(काष्ठा termios2 __user *)arg))
			वापस -EFAULT;
	पूर्ण
#अन्यथा
	पूर्ण अन्यथा अगर (user_termios_to_kernel_termios(&पंचांगp_termios,
					(काष्ठा termios __user *)arg))
		वापस -EFAULT;
#पूर्ण_अगर

	/* If old style Bfoo values are used then load c_ispeed/c_ospeed
	 * with the real speed so its unconditionally usable */
	पंचांगp_termios.c_ispeed = tty_termios_input_baud_rate(&पंचांगp_termios);
	पंचांगp_termios.c_ospeed = tty_termios_baud_rate(&पंचांगp_termios);

	ld = tty_ldisc_ref(tty);

	अगर (ld != शून्य) अणु
		अगर ((opt & TERMIOS_FLUSH) && ld->ops->flush_buffer)
			ld->ops->flush_buffer(tty);
		tty_ldisc_deref(ld);
	पूर्ण

	अगर (opt & TERMIOS_WAIT) अणु
		tty_रुको_until_sent(tty, 0);
		अगर (संकेत_pending(current))
			वापस -ERESTARTSYS;
	पूर्ण

	tty_set_termios(tty, &पंचांगp_termios);

	/* FIXME: Arguably अगर पंचांगp_termios == tty->termios AND the
	   actual requested termios was not पंचांगp_termios then we may
	   want to वापस an error as no user requested change has
	   succeeded */
	वापस 0;
पूर्ण

अटल व्योम copy_termios(काष्ठा tty_काष्ठा *tty, काष्ठा ktermios *kterm)
अणु
	करोwn_पढ़ो(&tty->termios_rwsem);
	*kterm = tty->termios;
	up_पढ़ो(&tty->termios_rwsem);
पूर्ण

अटल व्योम copy_termios_locked(काष्ठा tty_काष्ठा *tty, काष्ठा ktermios *kterm)
अणु
	करोwn_पढ़ो(&tty->termios_rwsem);
	*kterm = tty->termios_locked;
	up_पढ़ो(&tty->termios_rwsem);
पूर्ण

अटल पूर्णांक get_termio(काष्ठा tty_काष्ठा *tty, काष्ठा termio __user *termio)
अणु
	काष्ठा ktermios kterm;
	copy_termios(tty, &kterm);
	अगर (kernel_termios_to_user_termio(termio, &kterm))
		वापस -EFAULT;
	वापस 0;
पूर्ण

#अगर_घोषित TIOCGETP
/*
 * These are deprecated, but there is limited support..
 *
 * The "sg_flags" translation is a joke..
 */
अटल पूर्णांक get_sgflags(काष्ठा tty_काष्ठा *tty)
अणु
	पूर्णांक flags = 0;

	अगर (!L_ICANON(tty)) अणु
		अगर (L_ISIG(tty))
			flags |= 0x02;		/* cअवरोध */
		अन्यथा
			flags |= 0x20;		/* raw */
	पूर्ण
	अगर (L_ECHO(tty))
		flags |= 0x08;			/* echo */
	अगर (O_OPOST(tty))
		अगर (O_ONLCR(tty))
			flags |= 0x10;		/* crmod */
	वापस flags;
पूर्ण

अटल पूर्णांक get_sgttyb(काष्ठा tty_काष्ठा *tty, काष्ठा sgttyb __user *sgttyb)
अणु
	काष्ठा sgttyb पंचांगp;

	करोwn_पढ़ो(&tty->termios_rwsem);
	पंचांगp.sg_ispeed = tty->termios.c_ispeed;
	पंचांगp.sg_ospeed = tty->termios.c_ospeed;
	पंचांगp.sg_erase = tty->termios.c_cc[VERASE];
	पंचांगp.sg_समाप्त = tty->termios.c_cc[VKILL];
	पंचांगp.sg_flags = get_sgflags(tty);
	up_पढ़ो(&tty->termios_rwsem);

	वापस copy_to_user(sgttyb, &पंचांगp, माप(पंचांगp)) ? -EFAULT : 0;
पूर्ण

अटल व्योम set_sgflags(काष्ठा ktermios *termios, पूर्णांक flags)
अणु
	termios->c_अगरlag = ICRNL | IXON;
	termios->c_oflag = 0;
	termios->c_lflag = ISIG | ICANON;
	अगर (flags & 0x02) अणु	/* cअवरोध */
		termios->c_अगरlag = 0;
		termios->c_lflag &= ~ICANON;
	पूर्ण
	अगर (flags & 0x08) अणु		/* echo */
		termios->c_lflag |= ECHO | ECHOE | ECHOK |
				    ECHOCTL | ECHOKE | IEXTEN;
	पूर्ण
	अगर (flags & 0x10) अणु		/* crmod */
		termios->c_oflag |= OPOST | ONLCR;
	पूर्ण
	अगर (flags & 0x20) अणु	/* raw */
		termios->c_अगरlag = 0;
		termios->c_lflag &= ~(ISIG | ICANON);
	पूर्ण
	अगर (!(termios->c_lflag & ICANON)) अणु
		termios->c_cc[VMIN] = 1;
		termios->c_cc[VTIME] = 0;
	पूर्ण
पूर्ण

/**
 *	set_sgttyb		-	set legacy terminal values
 *	@tty: tty काष्ठाure
 *	@sgttyb: poपूर्णांकer to old style terminal काष्ठाure
 *
 *	Updates a terminal from the legacy BSD style terminal inक्रमmation
 *	काष्ठाure.
 *
 *	Locking: termios_rwsem
 */

अटल पूर्णांक set_sgttyb(काष्ठा tty_काष्ठा *tty, काष्ठा sgttyb __user *sgttyb)
अणु
	पूर्णांक retval;
	काष्ठा sgttyb पंचांगp;
	काष्ठा ktermios termios;

	retval = tty_check_change(tty);
	अगर (retval)
		वापस retval;

	अगर (copy_from_user(&पंचांगp, sgttyb, माप(पंचांगp)))
		वापस -EFAULT;

	करोwn_ग_लिखो(&tty->termios_rwsem);
	termios = tty->termios;
	termios.c_cc[VERASE] = पंचांगp.sg_erase;
	termios.c_cc[VKILL] = पंचांगp.sg_समाप्त;
	set_sgflags(&termios, पंचांगp.sg_flags);
	/* Try and encode पूर्णांकo Bfoo क्रमmat */
#अगर_घोषित BOTHER
	tty_termios_encode_baud_rate(&termios, termios.c_ispeed,
						termios.c_ospeed);
#पूर्ण_अगर
	up_ग_लिखो(&tty->termios_rwsem);
	tty_set_termios(tty, &termios);
	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित TIOCGETC
अटल पूर्णांक get_tअक्षरs(काष्ठा tty_काष्ठा *tty, काष्ठा tअक्षरs __user *tअक्षरs)
अणु
	काष्ठा tअक्षरs पंचांगp;

	करोwn_पढ़ो(&tty->termios_rwsem);
	पंचांगp.t_पूर्णांकrc = tty->termios.c_cc[VINTR];
	पंचांगp.t_quitc = tty->termios.c_cc[VQUIT];
	पंचांगp.t_startc = tty->termios.c_cc[VSTART];
	पंचांगp.t_stopc = tty->termios.c_cc[VSTOP];
	पंचांगp.t_eofc = tty->termios.c_cc[Vखातापूर्ण];
	पंचांगp.t_brkc = tty->termios.c_cc[VEOL2];	/* what is brkc anyway? */
	up_पढ़ो(&tty->termios_rwsem);
	वापस copy_to_user(tअक्षरs, &पंचांगp, माप(पंचांगp)) ? -EFAULT : 0;
पूर्ण

अटल पूर्णांक set_tअक्षरs(काष्ठा tty_काष्ठा *tty, काष्ठा tअक्षरs __user *tअक्षरs)
अणु
	काष्ठा tअक्षरs पंचांगp;

	अगर (copy_from_user(&पंचांगp, tअक्षरs, माप(पंचांगp)))
		वापस -EFAULT;
	करोwn_ग_लिखो(&tty->termios_rwsem);
	tty->termios.c_cc[VINTR] = पंचांगp.t_पूर्णांकrc;
	tty->termios.c_cc[VQUIT] = पंचांगp.t_quitc;
	tty->termios.c_cc[VSTART] = पंचांगp.t_startc;
	tty->termios.c_cc[VSTOP] = पंचांगp.t_stopc;
	tty->termios.c_cc[Vखातापूर्ण] = पंचांगp.t_eofc;
	tty->termios.c_cc[VEOL2] = पंचांगp.t_brkc;	/* what is brkc anyway? */
	up_ग_लिखो(&tty->termios_rwsem);
	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित TIOCGLTC
अटल पूर्णांक get_ltअक्षरs(काष्ठा tty_काष्ठा *tty, काष्ठा ltअक्षरs __user *ltअक्षरs)
अणु
	काष्ठा ltअक्षरs पंचांगp;

	करोwn_पढ़ो(&tty->termios_rwsem);
	पंचांगp.t_suspc = tty->termios.c_cc[VSUSP];
	/* what is dsuspc anyway? */
	पंचांगp.t_dsuspc = tty->termios.c_cc[VSUSP];
	पंचांगp.t_rprntc = tty->termios.c_cc[VREPRINT];
	/* what is flushc anyway? */
	पंचांगp.t_flushc = tty->termios.c_cc[VEOL2];
	पंचांगp.t_werasc = tty->termios.c_cc[VWERASE];
	पंचांगp.t_lnextc = tty->termios.c_cc[VLNEXT];
	up_पढ़ो(&tty->termios_rwsem);
	वापस copy_to_user(ltअक्षरs, &पंचांगp, माप(पंचांगp)) ? -EFAULT : 0;
पूर्ण

अटल पूर्णांक set_ltअक्षरs(काष्ठा tty_काष्ठा *tty, काष्ठा ltअक्षरs __user *ltअक्षरs)
अणु
	काष्ठा ltअक्षरs पंचांगp;

	अगर (copy_from_user(&पंचांगp, ltअक्षरs, माप(पंचांगp)))
		वापस -EFAULT;

	करोwn_ग_लिखो(&tty->termios_rwsem);
	tty->termios.c_cc[VSUSP] = पंचांगp.t_suspc;
	/* what is dsuspc anyway? */
	tty->termios.c_cc[VEOL2] = पंचांगp.t_dsuspc;
	tty->termios.c_cc[VREPRINT] = पंचांगp.t_rprntc;
	/* what is flushc anyway? */
	tty->termios.c_cc[VEOL2] = पंचांगp.t_flushc;
	tty->termios.c_cc[VWERASE] = पंचांगp.t_werasc;
	tty->termios.c_cc[VLNEXT] = पंचांगp.t_lnextc;
	up_ग_लिखो(&tty->termios_rwsem);
	वापस 0;
पूर्ण
#पूर्ण_अगर

/**
 *	tty_change_softcar	-	carrier change ioctl helper
 *	@tty: tty to update
 *	@arg: enable/disable CLOCAL
 *
 *	Perक्रमm a change to the CLOCAL state and call पूर्णांकo the driver
 *	layer to make it visible. All करोne with the termios rwsem
 */

अटल पूर्णांक tty_change_softcar(काष्ठा tty_काष्ठा *tty, पूर्णांक arg)
अणु
	पूर्णांक ret = 0;
	पूर्णांक bit = arg ? CLOCAL : 0;
	काष्ठा ktermios old;

	करोwn_ग_लिखो(&tty->termios_rwsem);
	old = tty->termios;
	tty->termios.c_cflag &= ~CLOCAL;
	tty->termios.c_cflag |= bit;
	अगर (tty->ops->set_termios)
		tty->ops->set_termios(tty, &old);
	अगर (C_CLOCAL(tty) != bit)
		ret = -EINVAL;
	up_ग_लिखो(&tty->termios_rwsem);
	वापस ret;
पूर्ण

/**
 *	tty_mode_ioctl		-	mode related ioctls
 *	@tty: tty क्रम the ioctl
 *	@file: file poपूर्णांकer क्रम the tty
 *	@cmd: command
 *	@arg: ioctl argument
 *
 *	Perक्रमm non line discipline specअगरic mode control ioctls. This
 *	is deचिन्हित to be called by line disciplines to ensure they provide
 *	consistent mode setting.
 */

पूर्णांक tty_mode_ioctl(काष्ठा tty_काष्ठा *tty, काष्ठा file *file,
			अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा tty_काष्ठा *real_tty;
	व्योम __user *p = (व्योम __user *)arg;
	पूर्णांक ret = 0;
	काष्ठा ktermios kterm;

	BUG_ON(file == शून्य);

	अगर (tty->driver->type == TTY_DRIVER_TYPE_PTY &&
	    tty->driver->subtype == PTY_TYPE_MASTER)
		real_tty = tty->link;
	अन्यथा
		real_tty = tty;

	चयन (cmd) अणु
#अगर_घोषित TIOCGETP
	हाल TIOCGETP:
		वापस get_sgttyb(real_tty, (काष्ठा sgttyb __user *) arg);
	हाल TIOCSETP:
	हाल TIOCSETN:
		वापस set_sgttyb(real_tty, (काष्ठा sgttyb __user *) arg);
#पूर्ण_अगर
#अगर_घोषित TIOCGETC
	हाल TIOCGETC:
		वापस get_tअक्षरs(real_tty, p);
	हाल TIOCSETC:
		वापस set_tअक्षरs(real_tty, p);
#पूर्ण_अगर
#अगर_घोषित TIOCGLTC
	हाल TIOCGLTC:
		वापस get_ltअक्षरs(real_tty, p);
	हाल TIOCSLTC:
		वापस set_ltअक्षरs(real_tty, p);
#पूर्ण_अगर
	हाल TCSETSF:
		वापस set_termios(real_tty, p,  TERMIOS_FLUSH | TERMIOS_WAIT | TERMIOS_OLD);
	हाल TCSETSW:
		वापस set_termios(real_tty, p, TERMIOS_WAIT | TERMIOS_OLD);
	हाल TCSETS:
		वापस set_termios(real_tty, p, TERMIOS_OLD);
#अगर_अघोषित TCGETS2
	हाल TCGETS:
		copy_termios(real_tty, &kterm);
		अगर (kernel_termios_to_user_termios((काष्ठा termios __user *)arg, &kterm))
			ret = -EFAULT;
		वापस ret;
#अन्यथा
	हाल TCGETS:
		copy_termios(real_tty, &kterm);
		अगर (kernel_termios_to_user_termios_1((काष्ठा termios __user *)arg, &kterm))
			ret = -EFAULT;
		वापस ret;
	हाल TCGETS2:
		copy_termios(real_tty, &kterm);
		अगर (kernel_termios_to_user_termios((काष्ठा termios2 __user *)arg, &kterm))
			ret = -EFAULT;
		वापस ret;
	हाल TCSETSF2:
		वापस set_termios(real_tty, p,  TERMIOS_FLUSH | TERMIOS_WAIT);
	हाल TCSETSW2:
		वापस set_termios(real_tty, p, TERMIOS_WAIT);
	हाल TCSETS2:
		वापस set_termios(real_tty, p, 0);
#पूर्ण_अगर
	हाल TCGETA:
		वापस get_termio(real_tty, p);
	हाल TCSETAF:
		वापस set_termios(real_tty, p, TERMIOS_FLUSH | TERMIOS_WAIT | TERMIOS_TERMIO);
	हाल TCSETAW:
		वापस set_termios(real_tty, p, TERMIOS_WAIT | TERMIOS_TERMIO);
	हाल TCSETA:
		वापस set_termios(real_tty, p, TERMIOS_TERMIO);
#अगर_अघोषित TCGETS2
	हाल TIOCGLCKTRMIOS:
		copy_termios_locked(real_tty, &kterm);
		अगर (kernel_termios_to_user_termios((काष्ठा termios __user *)arg, &kterm))
			ret = -EFAULT;
		वापस ret;
	हाल TIOCSLCKTRMIOS:
		अगर (!capable(CAP_SYS_ADMIN))
			वापस -EPERM;
		copy_termios_locked(real_tty, &kterm);
		अगर (user_termios_to_kernel_termios(&kterm,
					       (काष्ठा termios __user *) arg))
			वापस -EFAULT;
		करोwn_ग_लिखो(&real_tty->termios_rwsem);
		real_tty->termios_locked = kterm;
		up_ग_लिखो(&real_tty->termios_rwsem);
		वापस 0;
#अन्यथा
	हाल TIOCGLCKTRMIOS:
		copy_termios_locked(real_tty, &kterm);
		अगर (kernel_termios_to_user_termios_1((काष्ठा termios __user *)arg, &kterm))
			ret = -EFAULT;
		वापस ret;
	हाल TIOCSLCKTRMIOS:
		अगर (!capable(CAP_SYS_ADMIN))
			वापस -EPERM;
		copy_termios_locked(real_tty, &kterm);
		अगर (user_termios_to_kernel_termios_1(&kterm,
					       (काष्ठा termios __user *) arg))
			वापस -EFAULT;
		करोwn_ग_लिखो(&real_tty->termios_rwsem);
		real_tty->termios_locked = kterm;
		up_ग_लिखो(&real_tty->termios_rwsem);
		वापस ret;
#पूर्ण_अगर
#अगर_घोषित TCGETX
	हाल TCGETX:
	हाल TCSETX:
	हाल TCSETXW:
	हाल TCSETXF:
		वापस -ENOTTY;
#पूर्ण_अगर
	हाल TIOCGSOFTCAR:
		copy_termios(real_tty, &kterm);
		ret = put_user((kterm.c_cflag & CLOCAL) ? 1 : 0,
						(पूर्णांक __user *)arg);
		वापस ret;
	हाल TIOCSSOFTCAR:
		अगर (get_user(arg, (अचिन्हित पूर्णांक __user *) arg))
			वापस -EFAULT;
		वापस tty_change_softcar(real_tty, arg);
	शेष:
		वापस -ENOIOCTLCMD;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(tty_mode_ioctl);


/* Caller guarantees ldisc reference is held */
अटल पूर्णांक __tty_perक्रमm_flush(काष्ठा tty_काष्ठा *tty, अचिन्हित दीर्घ arg)
अणु
	काष्ठा tty_ldisc *ld = tty->ldisc;

	चयन (arg) अणु
	हाल TCIFLUSH:
		अगर (ld && ld->ops->flush_buffer) अणु
			ld->ops->flush_buffer(tty);
			tty_unthrottle(tty);
		पूर्ण
		अवरोध;
	हाल TCIOFLUSH:
		अगर (ld && ld->ops->flush_buffer) अणु
			ld->ops->flush_buffer(tty);
			tty_unthrottle(tty);
		पूर्ण
		fallthrough;
	हाल TCOFLUSH:
		tty_driver_flush_buffer(tty);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक tty_perक्रमm_flush(काष्ठा tty_काष्ठा *tty, अचिन्हित दीर्घ arg)
अणु
	काष्ठा tty_ldisc *ld;
	पूर्णांक retval = tty_check_change(tty);
	अगर (retval)
		वापस retval;

	ld = tty_ldisc_ref_रुको(tty);
	retval = __tty_perक्रमm_flush(tty, arg);
	अगर (ld)
		tty_ldisc_deref(ld);
	वापस retval;
पूर्ण
EXPORT_SYMBOL_GPL(tty_perक्रमm_flush);

पूर्णांक n_tty_ioctl_helper(काष्ठा tty_काष्ठा *tty, काष्ठा file *file,
		       अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	पूर्णांक retval;

	चयन (cmd) अणु
	हाल TCXONC:
		retval = tty_check_change(tty);
		अगर (retval)
			वापस retval;
		चयन (arg) अणु
		हाल TCOOFF:
			spin_lock_irq(&tty->flow_lock);
			अगर (!tty->flow_stopped) अणु
				tty->flow_stopped = 1;
				__stop_tty(tty);
			पूर्ण
			spin_unlock_irq(&tty->flow_lock);
			अवरोध;
		हाल TCOON:
			spin_lock_irq(&tty->flow_lock);
			अगर (tty->flow_stopped) अणु
				tty->flow_stopped = 0;
				__start_tty(tty);
			पूर्ण
			spin_unlock_irq(&tty->flow_lock);
			अवरोध;
		हाल TCIOFF:
			अगर (STOP_CHAR(tty) != __DISABLED_CHAR)
				retval = tty_send_xअक्षर(tty, STOP_CHAR(tty));
			अवरोध;
		हाल TCION:
			अगर (START_CHAR(tty) != __DISABLED_CHAR)
				retval = tty_send_xअक्षर(tty, START_CHAR(tty));
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		वापस retval;
	हाल TCFLSH:
		retval = tty_check_change(tty);
		अगर (retval)
			वापस retval;
		वापस __tty_perक्रमm_flush(tty, arg);
	शेष:
		/* Try the mode commands */
		वापस tty_mode_ioctl(tty, file, cmd, arg);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(n_tty_ioctl_helper);
