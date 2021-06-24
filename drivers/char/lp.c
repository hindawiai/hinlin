<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Generic parallel prपूर्णांकer driver
 *
 * Copyright (C) 1992 by Jim Weigand and Linus Torvalds
 * Copyright (C) 1992,1993 by Michael K. Johnson
 * - Thanks much to Gunter Windau क्रम poपूर्णांकing out to me where the error
 *   checking ought to be.
 * Copyright (C) 1993 by Nigel Gamble (added पूर्णांकerrupt code)
 * Copyright (C) 1994 by Alan Cox (Modularised it)
 * LPCAREFUL, LPABORT, LPGETSTATUS added by Chris Metcalf, metcalf@lcs.mit.edu
 * Statistics and support क्रम slow prपूर्णांकers by Rob Janssen, rob@knoware.nl
 * "lp=" command line parameters added by Grant Guenther, grant@torque.net
 * lp_पढ़ो (Status पढ़ोback) support added by Carsten Gross,
 *                                             carsten@sol.wohnheim.uni-ulm.de
 * Support क्रम parport by Philip Blundell <philb@gnu.org>
 * Parport sharing hacking by Andrea Arcangeli
 * Fixed kernel_(to/from)_user memory copy to check क्रम errors
 * 				by Riccarकरो Facchetti <fizban@tin.it>
 * 22-JAN-1998  Added support क्रम devfs  Riअक्षरd Gooch <rgooch@atnf.csiro.au>
 * Redeचिन्हित पूर्णांकerrupt handling क्रम handle prपूर्णांकers with buggy handshake
 *				by Andrea Arcangeli, 11 May 1998
 * Full efficient handling of prपूर्णांकer with buggy irq handshake (now I have
 * understood the meaning of the strange handshake). This is करोne sending new
 * अक्षरacters अगर the पूर्णांकerrupt is just happened, even अगर the prपूर्णांकer say to
 * be still BUSY. This is needed at least with Epson Stylus Color. To enable
 * the new TRUST_IRQ mode पढ़ो the `LP OPTIMIZATION' section below...
 * Fixed the irq on the rising edge of the strobe हाल.
 * Obsoleted the CAREFUL flag since a prपूर्णांकer that करोesn' t work with
 * CAREFUL will block a bit after in lp_check_status().
 *				Andrea Arcangeli, 15 Oct 1998
 * Obsoleted and हटाओd all the lowlevel stuff implemented in the last
 * month to use the IEEE1284 functions (that handle the _new_ compatibilty
 * mode fine).
 */

/* This driver should, in theory, work with any parallel port that has an
 * appropriate low-level driver; all I/O is करोne through the parport
 * असलtraction layer.
 *
 * If this driver is built पूर्णांकo the kernel, you can configure it using the
 * kernel command-line.  For example:
 *
 *	lp=parport1,none,parport2	(bind lp0 to parport1, disable lp1 and
 *					 bind lp2 to parport2)
 *
 *	lp=स्वतः				(assign lp devices to all ports that
 *				         have prपूर्णांकers attached, as determined
 *					 by the IEEE-1284 स्वतःprobe)
 *
 *	lp=reset			(reset the prपूर्णांकer during
 *					 initialisation)
 *
 *	lp=off				(disable the prपूर्णांकer driver entirely)
 *
 * If the driver is loaded as a module, similar functionality is available
 * using module parameters.  The equivalent of the above commands would be:
 *
 *	# insmod lp.o parport=1,none,2
 *
 *	# insmod lp.o parport=स्वतः
 *
 *	# insmod lp.o reset=1
 */

/* COMPATIBILITY WITH OLD KERNELS
 *
 * Under Linux 2.0 and previous versions, lp devices were bound to ports at
 * particular I/O addresses, as follows:
 *
 *	lp0		0x3bc
 *	lp1		0x378
 *	lp2		0x278
 *
 * The new driver, by शेष, binds lp devices to parport devices as it
 * finds them.  This means that अगर you only have one port, it will be bound
 * to lp0 regardless of its I/O address.  If you need the old behaviour, you
 * can क्रमce it using the parameters described above.
 */

/*
 * The new पूर्णांकerrupt handling code take care of the buggy handshake
 * of some HP and Epson prपूर्णांकer:
 * ___
 * ACK    _______________    ___________
 *                       |__|
 * ____
 * BUSY   _________              _______
 *                 |____________|
 *
 * I discovered this using the prपूर्णांकer scanner that you can find at:
 *
 *	ftp://e-mind.com/pub/linux/pscan/
 *
 *					11 May 98, Andrea Arcangeli
 *
 * My prपूर्णांकer scanner run on an Epson Stylus Color show that such prपूर्णांकer
 * generates the irq on the _rising_ edge of the STROBE. Now lp handle
 * this हाल fine too.
 *
 *					15 Oct 1998, Andrea Arcangeli
 *
 * The so called `buggy' handshake is really the well करोcumented
 * compatibility mode IEEE1284 handshake. They changed the well known
 * Centronics handshake acking in the middle of busy expecting to not
 * अवरोध drivers or legacy application, जबतक they broken linux lp
 * until I fixed it reverse engineering the protocol by hand some
 * month ago...
 *
 *                                     14 Dec 1998, Andrea Arcangeli
 *
 * Copyright (C) 2000 by Tim Waugh (added LPSETTIMEOUT ioctl)
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/major.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/slab.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/delay.h>
#समावेश <linux/poll.h>
#समावेश <linux/console.h>
#समावेश <linux/device.h>
#समावेश <linux/रुको.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/mutex.h>
#समावेश <linux/compat.h>

#समावेश <linux/parport.h>
#अघोषित LP_STATS
#समावेश <linux/lp.h>

#समावेश <यंत्र/irq.h>
#समावेश <linux/uaccess.h>

/* अगर you have more than 8 prपूर्णांकers, remember to increase LP_NO */
#घोषणा LP_NO 8

अटल DEFINE_MUTEX(lp_mutex);
अटल काष्ठा lp_काष्ठा lp_table[LP_NO];
अटल पूर्णांक port_num[LP_NO];

अटल अचिन्हित पूर्णांक lp_count = 0;
अटल काष्ठा class *lp_class;

#अगर_घोषित CONFIG_LP_CONSOLE
अटल काष्ठा parport *console_रेजिस्टरed;
#पूर्ण_अगर /* CONFIG_LP_CONSOLE */

#अघोषित LP_DEBUG

/* Bits used to manage claiming the parport device */
#घोषणा LP_PREEMPT_REQUEST 1
#घोषणा LP_PARPORT_CLAIMED 2

/* --- low-level port access ----------------------------------- */

#घोषणा r_dtr(x)	(parport_पढ़ो_data(lp_table[(x)].dev->port))
#घोषणा r_str(x)	(parport_पढ़ो_status(lp_table[(x)].dev->port))
#घोषणा w_ctr(x,y)	करो अणु parport_ग_लिखो_control(lp_table[(x)].dev->port, (y)); पूर्ण जबतक (0)
#घोषणा w_dtr(x,y)	करो अणु parport_ग_लिखो_data(lp_table[(x)].dev->port, (y)); पूर्ण जबतक (0)

/* Claim the parport or block trying unless we've alपढ़ोy claimed it */
अटल व्योम lp_claim_parport_or_block(काष्ठा lp_काष्ठा *this_lp)
अणु
	अगर (!test_and_set_bit(LP_PARPORT_CLAIMED, &this_lp->bits)) अणु
		parport_claim_or_block(this_lp->dev);
	पूर्ण
पूर्ण

/* Claim the parport or block trying unless we've alपढ़ोy claimed it */
अटल व्योम lp_release_parport(काष्ठा lp_काष्ठा *this_lp)
अणु
	अगर (test_and_clear_bit(LP_PARPORT_CLAIMED, &this_lp->bits)) अणु
		parport_release(this_lp->dev);
	पूर्ण
पूर्ण



अटल पूर्णांक lp_preempt(व्योम *handle)
अणु
	काष्ठा lp_काष्ठा *this_lp = (काष्ठा lp_काष्ठा *)handle;
	set_bit(LP_PREEMPT_REQUEST, &this_lp->bits);
	वापस 1;
पूर्ण


/*
 * Try to negotiate to a new mode; अगर unsuccessful negotiate to
 * compatibility mode.  Return the mode we ended up in.
 */
अटल पूर्णांक lp_negotiate(काष्ठा parport *port, पूर्णांक mode)
अणु
	अगर (parport_negotiate(port, mode) != 0) अणु
		mode = IEEE1284_MODE_COMPAT;
		parport_negotiate(port, mode);
	पूर्ण

	वापस mode;
पूर्ण

अटल पूर्णांक lp_reset(पूर्णांक minor)
अणु
	पूर्णांक retval;
	lp_claim_parport_or_block(&lp_table[minor]);
	w_ctr(minor, LP_PSELECP);
	udelay(LP_DELAY);
	w_ctr(minor, LP_PSELECP | LP_PINITP);
	retval = r_str(minor);
	lp_release_parport(&lp_table[minor]);
	वापस retval;
पूर्ण

अटल व्योम lp_error(पूर्णांक minor)
अणु
	DEFINE_WAIT(रुको);
	पूर्णांक polling;

	अगर (LP_F(minor) & LP_ABORT)
		वापस;

	polling = lp_table[minor].dev->port->irq == PARPORT_IRQ_NONE;
	अगर (polling)
		lp_release_parport(&lp_table[minor]);
	prepare_to_रुको(&lp_table[minor].रुकोq, &रुको, TASK_INTERRUPTIBLE);
	schedule_समयout(LP_TIMEOUT_POLLED);
	finish_रुको(&lp_table[minor].रुकोq, &रुको);
	अगर (polling)
		lp_claim_parport_or_block(&lp_table[minor]);
	अन्यथा
		parport_yield_blocking(lp_table[minor].dev);
पूर्ण

अटल पूर्णांक lp_check_status(पूर्णांक minor)
अणु
	पूर्णांक error = 0;
	अचिन्हित पूर्णांक last = lp_table[minor].last_error;
	अचिन्हित अक्षर status = r_str(minor);
	अगर ((status & LP_PERRORP) && !(LP_F(minor) & LP_CAREFUL))
		/* No error. */
		last = 0;
	अन्यथा अगर ((status & LP_POUTPA)) अणु
		अगर (last != LP_POUTPA) अणु
			last = LP_POUTPA;
			prपूर्णांकk(KERN_INFO "lp%d out of paper\n", minor);
		पूर्ण
		error = -ENOSPC;
	पूर्ण अन्यथा अगर (!(status & LP_PSELECD)) अणु
		अगर (last != LP_PSELECD) अणु
			last = LP_PSELECD;
			prपूर्णांकk(KERN_INFO "lp%d off-line\n", minor);
		पूर्ण
		error = -EIO;
	पूर्ण अन्यथा अगर (!(status & LP_PERRORP)) अणु
		अगर (last != LP_PERRORP) अणु
			last = LP_PERRORP;
			prपूर्णांकk(KERN_INFO "lp%d on fire\n", minor);
		पूर्ण
		error = -EIO;
	पूर्ण अन्यथा अणु
		last = 0; /* Come here अगर LP_CAREFUL is set and no
			     errors are reported. */
	पूर्ण

	lp_table[minor].last_error = last;

	अगर (last != 0)
		lp_error(minor);

	वापस error;
पूर्ण

अटल पूर्णांक lp_रुको_पढ़ोy(पूर्णांक minor, पूर्णांक nonblock)
अणु
	पूर्णांक error = 0;

	/* If we're not in compatibility mode, we're पढ़ोy now! */
	अगर (lp_table[minor].current_mode != IEEE1284_MODE_COMPAT) अणु
		वापस 0;
	पूर्ण

	करो अणु
		error = lp_check_status(minor);
		अगर (error && (nonblock || (LP_F(minor) & LP_ABORT)))
			अवरोध;
		अगर (संकेत_pending(current)) अणु
			error = -EINTR;
			अवरोध;
		पूर्ण
	पूर्ण जबतक (error);
	वापस error;
पूर्ण

अटल sमाप_प्रकार lp_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
			माप_प्रकार count, loff_t *ppos)
अणु
	अचिन्हित पूर्णांक minor = iminor(file_inode(file));
	काष्ठा parport *port = lp_table[minor].dev->port;
	अक्षर *kbuf = lp_table[minor].lp_buffer;
	sमाप_प्रकार retv = 0;
	sमाप_प्रकार written;
	माप_प्रकार copy_size = count;
	पूर्णांक nonblock = ((file->f_flags & O_NONBLOCK) ||
			(LP_F(minor) & LP_ABORT));

#अगर_घोषित LP_STATS
	अगर (समय_after(jअगरfies, lp_table[minor].lastcall + LP_TIME(minor)))
		lp_table[minor].runअक्षरs = 0;

	lp_table[minor].lastcall = jअगरfies;
#पूर्ण_अगर

	/* Need to copy the data from user-space. */
	अगर (copy_size > LP_BUFFER_SIZE)
		copy_size = LP_BUFFER_SIZE;

	अगर (mutex_lock_पूर्णांकerruptible(&lp_table[minor].port_mutex))
		वापस -EINTR;

	अगर (copy_from_user(kbuf, buf, copy_size)) अणु
		retv = -EFAULT;
		जाओ out_unlock;
	पूर्ण

	/* Claim Parport or sleep until it becomes available
	 */
	lp_claim_parport_or_block(&lp_table[minor]);
	/* Go to the proper mode. */
	lp_table[minor].current_mode = lp_negotiate(port,
						    lp_table[minor].best_mode);

	parport_set_समयout(lp_table[minor].dev,
			    (nonblock ? PARPORT_INACTIVITY_O_NONBLOCK
			     : lp_table[minor].समयout));

	अगर ((retv = lp_रुको_पढ़ोy(minor, nonblock)) == 0)
	करो अणु
		/* Write the data. */
		written = parport_ग_लिखो(port, kbuf, copy_size);
		अगर (written > 0) अणु
			copy_size -= written;
			count -= written;
			buf  += written;
			retv += written;
		पूर्ण

		अगर (संकेत_pending(current)) अणु
			अगर (retv == 0)
				retv = -EINTR;

			अवरोध;
		पूर्ण

		अगर (copy_size > 0) अणु
			/* incomplete ग_लिखो -> check error ! */
			पूर्णांक error;

			parport_negotiate(lp_table[minor].dev->port,
					  IEEE1284_MODE_COMPAT);
			lp_table[minor].current_mode = IEEE1284_MODE_COMPAT;

			error = lp_रुको_पढ़ोy(minor, nonblock);

			अगर (error) अणु
				अगर (retv == 0)
					retv = error;
				अवरोध;
			पूर्ण अन्यथा अगर (nonblock) अणु
				अगर (retv == 0)
					retv = -EAGAIN;
				अवरोध;
			पूर्ण

			parport_yield_blocking(lp_table[minor].dev);
			lp_table[minor].current_mode
			  = lp_negotiate(port,
					 lp_table[minor].best_mode);

		पूर्ण अन्यथा अगर (need_resched())
			schedule();

		अगर (count) अणु
			copy_size = count;
			अगर (copy_size > LP_BUFFER_SIZE)
				copy_size = LP_BUFFER_SIZE;

			अगर (copy_from_user(kbuf, buf, copy_size)) अणु
				अगर (retv == 0)
					retv = -EFAULT;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण जबतक (count > 0);

	अगर (test_and_clear_bit(LP_PREEMPT_REQUEST,
			       &lp_table[minor].bits)) अणु
		prपूर्णांकk(KERN_INFO "lp%d releasing parport\n", minor);
		parport_negotiate(lp_table[minor].dev->port,
				  IEEE1284_MODE_COMPAT);
		lp_table[minor].current_mode = IEEE1284_MODE_COMPAT;
		lp_release_parport(&lp_table[minor]);
	पूर्ण
out_unlock:
	mutex_unlock(&lp_table[minor].port_mutex);

	वापस retv;
पूर्ण

#अगर_घोषित CONFIG_PARPORT_1284

/* Status पढ़ोback conक्रमming to ieee1284 */
अटल sमाप_प्रकार lp_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
		       माप_प्रकार count, loff_t *ppos)
अणु
	DEFINE_WAIT(रुको);
	अचिन्हित पूर्णांक minor=iminor(file_inode(file));
	काष्ठा parport *port = lp_table[minor].dev->port;
	sमाप_प्रकार retval = 0;
	अक्षर *kbuf = lp_table[minor].lp_buffer;
	पूर्णांक nonblock = ((file->f_flags & O_NONBLOCK) ||
			(LP_F(minor) & LP_ABORT));

	अगर (count > LP_BUFFER_SIZE)
		count = LP_BUFFER_SIZE;

	अगर (mutex_lock_पूर्णांकerruptible(&lp_table[minor].port_mutex))
		वापस -EINTR;

	lp_claim_parport_or_block(&lp_table[minor]);

	parport_set_समयout(lp_table[minor].dev,
			    (nonblock ? PARPORT_INACTIVITY_O_NONBLOCK
			     : lp_table[minor].समयout));

	parport_negotiate(lp_table[minor].dev->port, IEEE1284_MODE_COMPAT);
	अगर (parport_negotiate(lp_table[minor].dev->port,
			      IEEE1284_MODE_NIBBLE)) अणु
		retval = -EIO;
		जाओ out;
	पूर्ण

	जबतक (retval == 0) अणु
		retval = parport_पढ़ो(port, kbuf, count);

		अगर (retval > 0)
			अवरोध;

		अगर (nonblock) अणु
			retval = -EAGAIN;
			अवरोध;
		पूर्ण

		/* Wait क्रम data. */

		अगर (lp_table[minor].dev->port->irq == PARPORT_IRQ_NONE) अणु
			parport_negotiate(lp_table[minor].dev->port,
					  IEEE1284_MODE_COMPAT);
			lp_error(minor);
			अगर (parport_negotiate(lp_table[minor].dev->port,
					      IEEE1284_MODE_NIBBLE)) अणु
				retval = -EIO;
				जाओ out;
			पूर्ण
		पूर्ण अन्यथा अणु
			prepare_to_रुको(&lp_table[minor].रुकोq, &रुको, TASK_INTERRUPTIBLE);
			schedule_समयout(LP_TIMEOUT_POLLED);
			finish_रुको(&lp_table[minor].रुकोq, &रुको);
		पूर्ण

		अगर (संकेत_pending(current)) अणु
			retval = -ERESTARTSYS;
			अवरोध;
		पूर्ण

		cond_resched();
	पूर्ण
	parport_negotiate(lp_table[minor].dev->port, IEEE1284_MODE_COMPAT);
 out:
	lp_release_parport(&lp_table[minor]);

	अगर (retval > 0 && copy_to_user(buf, kbuf, retval))
		retval = -EFAULT;

	mutex_unlock(&lp_table[minor].port_mutex);

	वापस retval;
पूर्ण

#पूर्ण_अगर /* IEEE 1284 support */

अटल पूर्णांक lp_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अचिन्हित पूर्णांक minor = iminor(inode);
	पूर्णांक ret = 0;

	mutex_lock(&lp_mutex);
	अगर (minor >= LP_NO) अणु
		ret = -ENXIO;
		जाओ out;
	पूर्ण
	अगर ((LP_F(minor) & LP_EXIST) == 0) अणु
		ret = -ENXIO;
		जाओ out;
	पूर्ण
	अगर (test_and_set_bit(LP_BUSY_BIT_POS, &LP_F(minor))) अणु
		ret = -EBUSY;
		जाओ out;
	पूर्ण
	/* If ABORTOPEN is set and the prपूर्णांकer is offline or out of paper,
	   we may still want to खोलो it to perक्रमm ioctl()s.  Thereक्रमe we
	   have commandeered O_NONBLOCK, even though it is being used in
	   a non-standard manner.  This is strictly a Linux hack, and
	   should most likely only ever be used by the tunelp application. */
	अगर ((LP_F(minor) & LP_ABORTOPEN) && !(file->f_flags & O_NONBLOCK)) अणु
		पूर्णांक status;
		lp_claim_parport_or_block(&lp_table[minor]);
		status = r_str(minor);
		lp_release_parport(&lp_table[minor]);
		अगर (status & LP_POUTPA) अणु
			prपूर्णांकk(KERN_INFO "lp%d out of paper\n", minor);
			LP_F(minor) &= ~LP_BUSY;
			ret = -ENOSPC;
			जाओ out;
		पूर्ण अन्यथा अगर (!(status & LP_PSELECD)) अणु
			prपूर्णांकk(KERN_INFO "lp%d off-line\n", minor);
			LP_F(minor) &= ~LP_BUSY;
			ret = -EIO;
			जाओ out;
		पूर्ण अन्यथा अगर (!(status & LP_PERRORP)) अणु
			prपूर्णांकk(KERN_ERR "lp%d printer error\n", minor);
			LP_F(minor) &= ~LP_BUSY;
			ret = -EIO;
			जाओ out;
		पूर्ण
	पूर्ण
	lp_table[minor].lp_buffer = kदो_स्मृति(LP_BUFFER_SIZE, GFP_KERNEL);
	अगर (!lp_table[minor].lp_buffer) अणु
		LP_F(minor) &= ~LP_BUSY;
		ret = -ENOMEM;
		जाओ out;
	पूर्ण
	/* Determine अगर the peripheral supports ECP mode */
	lp_claim_parport_or_block(&lp_table[minor]);
	अगर ((lp_table[minor].dev->port->modes & PARPORT_MODE_ECP) &&
	     !parport_negotiate(lp_table[minor].dev->port,
				 IEEE1284_MODE_ECP)) अणु
		prपूर्णांकk(KERN_INFO "lp%d: ECP mode\n", minor);
		lp_table[minor].best_mode = IEEE1284_MODE_ECP;
	पूर्ण अन्यथा अणु
		lp_table[minor].best_mode = IEEE1284_MODE_COMPAT;
	पूर्ण
	/* Leave peripheral in compatibility mode */
	parport_negotiate(lp_table[minor].dev->port, IEEE1284_MODE_COMPAT);
	lp_release_parport(&lp_table[minor]);
	lp_table[minor].current_mode = IEEE1284_MODE_COMPAT;
out:
	mutex_unlock(&lp_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक lp_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अचिन्हित पूर्णांक minor = iminor(inode);

	lp_claim_parport_or_block(&lp_table[minor]);
	parport_negotiate(lp_table[minor].dev->port, IEEE1284_MODE_COMPAT);
	lp_table[minor].current_mode = IEEE1284_MODE_COMPAT;
	lp_release_parport(&lp_table[minor]);
	kमुक्त(lp_table[minor].lp_buffer);
	lp_table[minor].lp_buffer = शून्य;
	LP_F(minor) &= ~LP_BUSY;
	वापस 0;
पूर्ण

अटल पूर्णांक lp_करो_ioctl(अचिन्हित पूर्णांक minor, अचिन्हित पूर्णांक cmd,
	अचिन्हित दीर्घ arg, व्योम __user *argp)
अणु
	पूर्णांक status;
	पूर्णांक retval = 0;

#अगर_घोषित LP_DEBUG
	prपूर्णांकk(KERN_DEBUG "lp%d ioctl, cmd: 0x%x, arg: 0x%lx\n", minor, cmd, arg);
#पूर्ण_अगर
	अगर (minor >= LP_NO)
		वापस -ENODEV;
	अगर ((LP_F(minor) & LP_EXIST) == 0)
		वापस -ENODEV;
	चयन (cmd) अणु
		हाल LPTIME:
			अगर (arg > अच_पूर्णांक_उच्च / HZ)
				वापस -EINVAL;
			LP_TIME(minor) = arg * HZ/100;
			अवरोध;
		हाल LPCHAR:
			LP_CHAR(minor) = arg;
			अवरोध;
		हाल LPABORT:
			अगर (arg)
				LP_F(minor) |= LP_ABORT;
			अन्यथा
				LP_F(minor) &= ~LP_ABORT;
			अवरोध;
		हाल LPABORTOPEN:
			अगर (arg)
				LP_F(minor) |= LP_ABORTOPEN;
			अन्यथा
				LP_F(minor) &= ~LP_ABORTOPEN;
			अवरोध;
		हाल LPCAREFUL:
			अगर (arg)
				LP_F(minor) |= LP_CAREFUL;
			अन्यथा
				LP_F(minor) &= ~LP_CAREFUL;
			अवरोध;
		हाल LPWAIT:
			LP_WAIT(minor) = arg;
			अवरोध;
		हाल LPSETIRQ:
			वापस -EINVAL;
		हाल LPGETIRQ:
			अगर (copy_to_user(argp, &LP_IRQ(minor),
					माप(पूर्णांक)))
				वापस -EFAULT;
			अवरोध;
		हाल LPGETSTATUS:
			अगर (mutex_lock_पूर्णांकerruptible(&lp_table[minor].port_mutex))
				वापस -EINTR;
			lp_claim_parport_or_block(&lp_table[minor]);
			status = r_str(minor);
			lp_release_parport(&lp_table[minor]);
			mutex_unlock(&lp_table[minor].port_mutex);

			अगर (copy_to_user(argp, &status, माप(पूर्णांक)))
				वापस -EFAULT;
			अवरोध;
		हाल LPRESET:
			lp_reset(minor);
			अवरोध;
#अगर_घोषित LP_STATS
		हाल LPGETSTATS:
			अगर (copy_to_user(argp, &LP_STAT(minor),
					माप(काष्ठा lp_stats)))
				वापस -EFAULT;
			अगर (capable(CAP_SYS_ADMIN))
				स_रखो(&LP_STAT(minor), 0,
						माप(काष्ठा lp_stats));
			अवरोध;
#पूर्ण_अगर
		हाल LPGETFLAGS:
			status = LP_F(minor);
			अगर (copy_to_user(argp, &status, माप(पूर्णांक)))
				वापस -EFAULT;
			अवरोध;

		शेष:
			retval = -EINVAL;
	पूर्ण
	वापस retval;
पूर्ण

अटल पूर्णांक lp_set_समयout(अचिन्हित पूर्णांक minor, s64 tv_sec, दीर्घ tv_usec)
अणु
	दीर्घ to_jअगरfies;

	/* Convert to jअगरfies, place in lp_table */
	अगर (tv_sec < 0 || tv_usec < 0)
		वापस -EINVAL;

	/*
	 * we used to not check, so let's not make this fatal,
	 * but deal with user space passing a 32-bit tv_nsec in
	 * a 64-bit field, capping the समयout to 1 second
	 * worth of microseconds, and capping the total at
	 * MAX_JIFFY_OFFSET.
	 */
	अगर (tv_usec > 999999)
		tv_usec = 999999;

	अगर (tv_sec >= MAX_SEC_IN_JIFFIES - 1) अणु
		to_jअगरfies = MAX_JIFFY_OFFSET;
	पूर्ण अन्यथा अणु
		to_jअगरfies = DIV_ROUND_UP(tv_usec, 1000000/HZ);
		to_jअगरfies += tv_sec * (दीर्घ) HZ;
	पूर्ण

	अगर (to_jअगरfies <= 0) अणु
		वापस -EINVAL;
	पूर्ण
	lp_table[minor].समयout = to_jअगरfies;
	वापस 0;
पूर्ण

अटल पूर्णांक lp_set_समयout32(अचिन्हित पूर्णांक minor, व्योम __user *arg)
अणु
	s32 karg[2];

	अगर (copy_from_user(karg, arg, माप(karg)))
		वापस -EFAULT;

	वापस lp_set_समयout(minor, karg[0], karg[1]);
पूर्ण

अटल पूर्णांक lp_set_समयout64(अचिन्हित पूर्णांक minor, व्योम __user *arg)
अणु
	s64 karg[2];

	अगर (copy_from_user(karg, arg, माप(karg)))
		वापस -EFAULT;

	/* sparc64 suseconds_t is 32-bit only */
	अगर (IS_ENABLED(CONFIG_SPARC64) && !in_compat_syscall())
		karg[1] >>= 32;

	वापस lp_set_समयout(minor, karg[0], karg[1]);
पूर्ण

अटल दीर्घ lp_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
			अचिन्हित दीर्घ arg)
अणु
	अचिन्हित पूर्णांक minor;
	पूर्णांक ret;

	minor = iminor(file_inode(file));
	mutex_lock(&lp_mutex);
	चयन (cmd) अणु
	हाल LPSETTIMEOUT_OLD:
		अगर (BITS_PER_LONG == 32) अणु
			ret = lp_set_समयout32(minor, (व्योम __user *)arg);
			अवरोध;
		पूर्ण
		fallthrough;	/* क्रम 64-bit */
	हाल LPSETTIMEOUT_NEW:
		ret = lp_set_समयout64(minor, (व्योम __user *)arg);
		अवरोध;
	शेष:
		ret = lp_करो_ioctl(minor, cmd, arg, (व्योम __user *)arg);
		अवरोध;
	पूर्ण
	mutex_unlock(&lp_mutex);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_COMPAT
अटल दीर्घ lp_compat_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
			अचिन्हित दीर्घ arg)
अणु
	अचिन्हित पूर्णांक minor;
	पूर्णांक ret;

	minor = iminor(file_inode(file));
	mutex_lock(&lp_mutex);
	चयन (cmd) अणु
	हाल LPSETTIMEOUT_OLD:
		अगर (!COMPAT_USE_64BIT_TIME) अणु
			ret = lp_set_समयout32(minor, (व्योम __user *)arg);
			अवरोध;
		पूर्ण
		fallthrough;	/* क्रम x32 mode */
	हाल LPSETTIMEOUT_NEW:
		ret = lp_set_समयout64(minor, (व्योम __user *)arg);
		अवरोध;
#अगर_घोषित LP_STATS
	हाल LPGETSTATS:
		/* FIXME: add an implementation अगर you set LP_STATS */
		ret = -EINVAL;
		अवरोध;
#पूर्ण_अगर
	शेष:
		ret = lp_करो_ioctl(minor, cmd, arg, compat_ptr(arg));
		अवरोध;
	पूर्ण
	mutex_unlock(&lp_mutex);

	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा file_operations lp_fops = अणु
	.owner		= THIS_MODULE,
	.ग_लिखो		= lp_ग_लिखो,
	.unlocked_ioctl	= lp_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl	= lp_compat_ioctl,
#पूर्ण_अगर
	.खोलो		= lp_खोलो,
	.release	= lp_release,
#अगर_घोषित CONFIG_PARPORT_1284
	.पढ़ो		= lp_पढ़ो,
#पूर्ण_अगर
	.llseek		= noop_llseek,
पूर्ण;

/* --- support क्रम console on the line prपूर्णांकer ----------------- */

#अगर_घोषित CONFIG_LP_CONSOLE

#घोषणा CONSOLE_LP 0

/* If the prपूर्णांकer is out of paper, we can either lose the messages or
 * stall until the prपूर्णांकer is happy again.  Define CONSOLE_LP_STRICT
 * non-zero to get the latter behaviour. */
#घोषणा CONSOLE_LP_STRICT 1

/* The console must be locked when we get here. */

अटल व्योम lp_console_ग_लिखो(काष्ठा console *co, स्थिर अक्षर *s,
			     अचिन्हित count)
अणु
	काष्ठा pardevice *dev = lp_table[CONSOLE_LP].dev;
	काष्ठा parport *port = dev->port;
	sमाप_प्रकार written;

	अगर (parport_claim(dev))
		/* Nothing we can करो. */
		वापस;

	parport_set_समयout(dev, 0);

	/* Go to compatibility mode. */
	parport_negotiate(port, IEEE1284_MODE_COMPAT);

	करो अणु
		/* Write the data, converting LF->CRLF as we go. */
		sमाप_प्रकार canग_लिखो = count;
		अक्षर *lf = स_प्रथम(s, '\n', count);
		अगर (lf)
			canग_लिखो = lf - s;

		अगर (canग_लिखो > 0) अणु
			written = parport_ग_लिखो(port, s, canग_लिखो);

			अगर (written <= 0)
				जारी;

			s += written;
			count -= written;
			canग_लिखो -= written;
		पूर्ण

		अगर (lf && canग_लिखो <= 0) अणु
			स्थिर अक्षर *crlf = "\r\n";
			पूर्णांक i = 2;

			/* Dodge the original '\n', and put '\r\n' instead. */
			s++;
			count--;
			करो अणु
				written = parport_ग_लिखो(port, crlf, i);
				अगर (written > 0) अणु
					i -= written;
					crlf += written;
				पूर्ण
			पूर्ण जबतक (i > 0 && (CONSOLE_LP_STRICT || written > 0));
		पूर्ण
	पूर्ण जबतक (count > 0 && (CONSOLE_LP_STRICT || written > 0));

	parport_release(dev);
पूर्ण

अटल काष्ठा console lpcons = अणु
	.name		= "lp",
	.ग_लिखो		= lp_console_ग_लिखो,
	.flags		= CON_PRINTBUFFER,
पूर्ण;

#पूर्ण_अगर /* console on line prपूर्णांकer */

/* --- initialisation code ------------------------------------- */

अटल पूर्णांक parport_nr[LP_NO] = अणु [0 ... LP_NO-1] = LP_PARPORT_UNSPEC पूर्ण;
अटल अक्षर *parport[LP_NO];
अटल bool reset;

module_param_array(parport, अक्षरp, शून्य, 0);
module_param(reset, bool, 0);

#अगर_अघोषित MODULE
अटल पूर्णांक __init lp_setup(अक्षर *str)
अणु
	अटल पूर्णांक parport_ptr;
	पूर्णांक x;

	अगर (get_option(&str, &x)) अणु
		अगर (x == 0) अणु
			/* disable driver on "lp=" or "lp=0" */
			parport_nr[0] = LP_PARPORT_OFF;
		पूर्ण अन्यथा अणु
			prपूर्णांकk(KERN_WARNING "warning: 'lp=0x%x' is deprecated, ignored\n", x);
			वापस 0;
		पूर्ण
	पूर्ण अन्यथा अगर (!म_भेदन(str, "parport", 7)) अणु
		पूर्णांक n = simple_म_से_अदीर्घ(str+7, शून्य, 10);
		अगर (parport_ptr < LP_NO)
			parport_nr[parport_ptr++] = n;
		अन्यथा
			prपूर्णांकk(KERN_INFO "lp: too many ports, %s ignored.\n",
			       str);
	पूर्ण अन्यथा अगर (!म_भेद(str, "auto")) अणु
		parport_nr[0] = LP_PARPORT_AUTO;
	पूर्ण अन्यथा अगर (!म_भेद(str, "none")) अणु
		अगर (parport_ptr < LP_NO)
			parport_nr[parport_ptr++] = LP_PARPORT_NONE;
		अन्यथा
			prपूर्णांकk(KERN_INFO "lp: too many ports, %s ignored.\n",
			       str);
	पूर्ण अन्यथा अगर (!म_भेद(str, "reset")) अणु
		reset = true;
	पूर्ण
	वापस 1;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक lp_रेजिस्टर(पूर्णांक nr, काष्ठा parport *port)
अणु
	काष्ठा pardev_cb ppdev_cb;

	स_रखो(&ppdev_cb, 0, माप(ppdev_cb));
	ppdev_cb.preempt = lp_preempt;
	ppdev_cb.निजी = &lp_table[nr];
	lp_table[nr].dev = parport_रेजिस्टर_dev_model(port, "lp",
						      &ppdev_cb, nr);
	अगर (lp_table[nr].dev == शून्य)
		वापस 1;
	lp_table[nr].flags |= LP_EXIST;

	अगर (reset)
		lp_reset(nr);

	device_create(lp_class, port->dev, MKDEV(LP_MAJOR, nr), शून्य,
		      "lp%d", nr);

	prपूर्णांकk(KERN_INFO "lp%d: using %s (%s).\n", nr, port->name,
	       (port->irq == PARPORT_IRQ_NONE)?"polling":"interrupt-driven");

#अगर_घोषित CONFIG_LP_CONSOLE
	अगर (!nr) अणु
		अगर (port->modes & PARPORT_MODE_SAFEININT) अणु
			रेजिस्टर_console(&lpcons);
			console_रेजिस्टरed = port;
			prपूर्णांकk(KERN_INFO "lp%d: console ready\n", CONSOLE_LP);
		पूर्ण अन्यथा
			prपूर्णांकk(KERN_ERR "lp%d: cannot run console on %s\n",
			       CONSOLE_LP, port->name);
	पूर्ण
#पूर्ण_अगर
	port_num[nr] = port->number;

	वापस 0;
पूर्ण

अटल व्योम lp_attach(काष्ठा parport *port)
अणु
	अचिन्हित पूर्णांक i;

	चयन (parport_nr[0]) अणु
	हाल LP_PARPORT_UNSPEC:
	हाल LP_PARPORT_AUTO:
		अगर (parport_nr[0] == LP_PARPORT_AUTO &&
		    port->probe_info[0].class != PARPORT_CLASS_PRINTER)
			वापस;
		अगर (lp_count == LP_NO) अणु
			prपूर्णांकk(KERN_INFO "lp: ignoring parallel port (max. %d)\n",LP_NO);
			वापस;
		पूर्ण
		क्रम (i = 0; i < LP_NO; i++)
			अगर (port_num[i] == -1)
				अवरोध;

		अगर (!lp_रेजिस्टर(i, port))
			lp_count++;
		अवरोध;

	शेष:
		क्रम (i = 0; i < LP_NO; i++) अणु
			अगर (port->number == parport_nr[i]) अणु
				अगर (!lp_रेजिस्टर(i, port))
					lp_count++;
				अवरोध;
			पूर्ण
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम lp_detach(काष्ठा parport *port)
अणु
	पूर्णांक n;

	/* Write this some day. */
#अगर_घोषित CONFIG_LP_CONSOLE
	अगर (console_रेजिस्टरed == port) अणु
		unरेजिस्टर_console(&lpcons);
		console_रेजिस्टरed = शून्य;
	पूर्ण
#पूर्ण_अगर /* CONFIG_LP_CONSOLE */

	क्रम (n = 0; n < LP_NO; n++) अणु
		अगर (port_num[n] == port->number) अणु
			port_num[n] = -1;
			lp_count--;
			device_destroy(lp_class, MKDEV(LP_MAJOR, n));
			parport_unरेजिस्टर_device(lp_table[n].dev);
		पूर्ण
	पूर्ण
पूर्ण

अटल काष्ठा parport_driver lp_driver = अणु
	.name = "lp",
	.match_port = lp_attach,
	.detach = lp_detach,
	.devmodel = true,
पूर्ण;

अटल पूर्णांक __init lp_init(व्योम)
अणु
	पूर्णांक i, err = 0;

	अगर (parport_nr[0] == LP_PARPORT_OFF)
		वापस 0;

	क्रम (i = 0; i < LP_NO; i++) अणु
		lp_table[i].dev = शून्य;
		lp_table[i].flags = 0;
		lp_table[i].अक्षरs = LP_INIT_CHAR;
		lp_table[i].समय = LP_INIT_TIME;
		lp_table[i].रुको = LP_INIT_WAIT;
		lp_table[i].lp_buffer = शून्य;
#अगर_घोषित LP_STATS
		lp_table[i].lastcall = 0;
		lp_table[i].runअक्षरs = 0;
		स_रखो(&lp_table[i].stats, 0, माप(काष्ठा lp_stats));
#पूर्ण_अगर
		lp_table[i].last_error = 0;
		init_रुकोqueue_head(&lp_table[i].रुकोq);
		init_रुकोqueue_head(&lp_table[i].dataq);
		mutex_init(&lp_table[i].port_mutex);
		lp_table[i].समयout = 10 * HZ;
		port_num[i] = -1;
	पूर्ण

	अगर (रेजिस्टर_chrdev(LP_MAJOR, "lp", &lp_fops)) अणु
		prपूर्णांकk(KERN_ERR "lp: unable to get major %d\n", LP_MAJOR);
		वापस -EIO;
	पूर्ण

	lp_class = class_create(THIS_MODULE, "printer");
	अगर (IS_ERR(lp_class)) अणु
		err = PTR_ERR(lp_class);
		जाओ out_reg;
	पूर्ण

	अगर (parport_रेजिस्टर_driver(&lp_driver)) अणु
		prपूर्णांकk(KERN_ERR "lp: unable to register with parport\n");
		err = -EIO;
		जाओ out_class;
	पूर्ण

	अगर (!lp_count) अणु
		prपूर्णांकk(KERN_INFO "lp: driver loaded but no devices found\n");
#अगर_अघोषित CONFIG_PARPORT_1284
		अगर (parport_nr[0] == LP_PARPORT_AUTO)
			prपूर्णांकk(KERN_INFO "lp: (is IEEE 1284 support enabled?)\n");
#पूर्ण_अगर
	पूर्ण

	वापस 0;

out_class:
	class_destroy(lp_class);
out_reg:
	unरेजिस्टर_chrdev(LP_MAJOR, "lp");
	वापस err;
पूर्ण

अटल पूर्णांक __init lp_init_module(व्योम)
अणु
	अगर (parport[0]) अणु
		/* The user gave some parameters.  Let's see what they were.  */
		अगर (!म_भेदन(parport[0], "auto", 4))
			parport_nr[0] = LP_PARPORT_AUTO;
		अन्यथा अणु
			पूर्णांक n;
			क्रम (n = 0; n < LP_NO && parport[n]; n++) अणु
				अगर (!म_भेदन(parport[n], "none", 4))
					parport_nr[n] = LP_PARPORT_NONE;
				अन्यथा अणु
					अक्षर *ep;
					अचिन्हित दीर्घ r = simple_म_से_अदीर्घ(parport[n], &ep, 0);
					अगर (ep != parport[n])
						parport_nr[n] = r;
					अन्यथा अणु
						prपूर्णांकk(KERN_ERR "lp: bad port specifier `%s'\n", parport[n]);
						वापस -ENODEV;
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	वापस lp_init();
पूर्ण

अटल व्योम lp_cleanup_module(व्योम)
अणु
	parport_unरेजिस्टर_driver(&lp_driver);

#अगर_घोषित CONFIG_LP_CONSOLE
	unरेजिस्टर_console(&lpcons);
#पूर्ण_अगर

	unरेजिस्टर_chrdev(LP_MAJOR, "lp");
	class_destroy(lp_class);
पूर्ण

__setup("lp=", lp_setup);
module_init(lp_init_module);
module_निकास(lp_cleanup_module);

MODULE_ALIAS_CHARDEV_MAJOR(LP_MAJOR);
MODULE_LICENSE("GPL");
