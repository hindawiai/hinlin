<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * linux/drivers/अक्षर/ppdev.c
 *
 * This is the code behind /dev/parport* -- it allows a user-space
 * application to use the parport subप्रणाली.
 *
 * Copyright (C) 1998-2000, 2002 Tim Waugh <tim@cyberelk.net>
 *
 * A /dev/parportx device node represents an arbitrary device
 * on port 'x'.  The following operations are possible:
 *
 * खोलो		करो nothing, set up शेष IEEE 1284 protocol to be COMPAT
 * बंद	release port and unरेजिस्टर device (अगर necessary)
 * ioctl
 *   EXCL	रेजिस्टर device exclusively (may fail)
 *   CLAIM	(रेजिस्टर device first समय) parport_claim_or_block
 *   RELEASE	parport_release
 *   SETMODE	set the IEEE 1284 protocol to use क्रम पढ़ो/ग_लिखो
 *   SETPHASE	set the IEEE 1284 phase of a particular mode.  Not to be
 *              confused with ioctl(fd, SETPHASER, &stun). ;-)
 *   DATAसूची	data_क्रमward / data_reverse
 *   WDATA	ग_लिखो_data
 *   RDATA	पढ़ो_data
 *   WCONTROL	ग_लिखो_control
 *   RCONTROL	पढ़ो_control
 *   FCONTROL	frob_control
 *   RSTATUS	पढ़ो_status
 *   NEGOT	parport_negotiate
 *   YIELD	parport_yield_blocking
 *   WCTLONIRQ	on पूर्णांकerrupt, set control lines
 *   CLRIRQ	clear (and वापस) पूर्णांकerrupt count
 *   SETTIME	sets device समयout (काष्ठा समयval)
 *   GETTIME	माला_लो device समयout (काष्ठा समयval)
 *   GETMODES	माला_लो hardware supported modes (अचिन्हित पूर्णांक)
 *   GETMODE	माला_लो the current IEEE1284 mode
 *   GETPHASE   माला_लो the current IEEE1284 phase
 *   GETFLAGS   माला_लो current (user-visible) flags
 *   SETFLAGS   sets current (user-visible) flags
 * पढ़ो/ग_लिखो	पढ़ो or ग_लिखो in current IEEE 1284 protocol
 * select	रुको क्रम पूर्णांकerrupt (in पढ़ोfds)
 *
 * Changes:
 * Added SETTIME/GETTIME ioctl, Fred Barnes, 1999.
 *
 * Arnalकरो Carvalho de Melo <acme@conectiva.com.br> 2000/08/25
 * - On error, copy_from_user and copy_to_user करो not वापस -EFAULT,
 *   They वापस the positive number of bytes *not* copied due to address
 *   space errors.
 *
 * Added GETMODES/GETMODE/GETPHASE ioctls, Fred Barnes <frmb2@ukc.ac.uk>, 03/01/2001.
 * Added GETFLAGS/SETFLAGS ioctls, Fred Barnes, 04/2001
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/device.h>
#समावेश <linux/ioctl.h>
#समावेश <linux/parport.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/poll.h>
#समावेश <linux/slab.h>
#समावेश <linux/major.h>
#समावेश <linux/ppdev.h>
#समावेश <linux/mutex.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/compat.h>

#घोषणा PP_VERSION "ppdev: user-space parallel port driver"
#घोषणा CHRDEV "ppdev"

काष्ठा pp_काष्ठा अणु
	काष्ठा pardevice *pdev;
	रुको_queue_head_t irq_रुको;
	atomic_t irqc;
	अचिन्हित पूर्णांक flags;
	पूर्णांक irqresponse;
	अचिन्हित अक्षर irqctl;
	काष्ठा ieee1284_info state;
	काष्ठा ieee1284_info saved_state;
	दीर्घ शेष_inactivity;
	पूर्णांक index;
पूर्ण;

/* should we use PARDEVICE_MAX here? */
अटल काष्ठा device *devices[PARPORT_MAX];

अटल DEFINE_IDA(ida_index);

/* pp_काष्ठा.flags bitfields */
#घोषणा PP_CLAIMED    (1<<0)
#घोषणा PP_EXCL       (1<<1)

/* Other स्थिरants */
#घोषणा PP_INTERRUPT_TIMEOUT (10 * HZ) /* 10s */
#घोषणा PP_BUFFER_SIZE 1024
#घोषणा PARDEVICE_MAX 8

अटल DEFINE_MUTEX(pp_करो_mutex);

/* define fixed sized ioctl cmd क्रम y2038 migration */
#घोषणा PPGETTIME32	_IOR(PP_IOCTL, 0x95, s32[2])
#घोषणा PPSETTIME32	_IOW(PP_IOCTL, 0x96, s32[2])
#घोषणा PPGETTIME64	_IOR(PP_IOCTL, 0x95, s64[2])
#घोषणा PPSETTIME64	_IOW(PP_IOCTL, 0x96, s64[2])

अटल अंतरभूत व्योम pp_enable_irq(काष्ठा pp_काष्ठा *pp)
अणु
	काष्ठा parport *port = pp->pdev->port;

	port->ops->enable_irq(port);
पूर्ण

अटल sमाप_प्रकार pp_पढ़ो(काष्ठा file *file, अक्षर __user *buf, माप_प्रकार count,
		       loff_t *ppos)
अणु
	अचिन्हित पूर्णांक minor = iminor(file_inode(file));
	काष्ठा pp_काष्ठा *pp = file->निजी_data;
	अक्षर *kbuffer;
	sमाप_प्रकार bytes_पढ़ो = 0;
	काष्ठा parport *pport;
	पूर्णांक mode;

	अगर (!(pp->flags & PP_CLAIMED)) अणु
		/* Don't have the port claimed */
		pr_debug(CHRDEV "%x: claim the port first\n", minor);
		वापस -EINVAL;
	पूर्ण

	/* Trivial हाल. */
	अगर (count == 0)
		वापस 0;

	kbuffer = kदो_स्मृति(min_t(माप_प्रकार, count, PP_BUFFER_SIZE), GFP_KERNEL);
	अगर (!kbuffer)
		वापस -ENOMEM;
	pport = pp->pdev->port;
	mode = pport->ieee1284.mode & ~(IEEE1284_DEVICEID | IEEE1284_ADDR);

	parport_set_समयout(pp->pdev,
			    (file->f_flags & O_NONBLOCK) ?
			    PARPORT_INACTIVITY_O_NONBLOCK :
			    pp->शेष_inactivity);

	जबतक (bytes_पढ़ो == 0) अणु
		sमाप_प्रकार need = min_t(अचिन्हित दीर्घ, count, PP_BUFFER_SIZE);

		अगर (mode == IEEE1284_MODE_EPP) अणु
			/* various specials क्रम EPP mode */
			पूर्णांक flags = 0;
			माप_प्रकार (*fn)(काष्ठा parport *, व्योम *, माप_प्रकार, पूर्णांक);

			अगर (pp->flags & PP_W91284PIC)
				flags |= PARPORT_W91284PIC;
			अगर (pp->flags & PP_FASTREAD)
				flags |= PARPORT_EPP_FAST;
			अगर (pport->ieee1284.mode & IEEE1284_ADDR)
				fn = pport->ops->epp_पढ़ो_addr;
			अन्यथा
				fn = pport->ops->epp_पढ़ो_data;
			bytes_पढ़ो = (*fn)(pport, kbuffer, need, flags);
		पूर्ण अन्यथा अणु
			bytes_पढ़ो = parport_पढ़ो(pport, kbuffer, need);
		पूर्ण

		अगर (bytes_पढ़ो != 0)
			अवरोध;

		अगर (file->f_flags & O_NONBLOCK) अणु
			bytes_पढ़ो = -EAGAIN;
			अवरोध;
		पूर्ण

		अगर (संकेत_pending(current)) अणु
			bytes_पढ़ो = -ERESTARTSYS;
			अवरोध;
		पूर्ण

		cond_resched();
	पूर्ण

	parport_set_समयout(pp->pdev, pp->शेष_inactivity);

	अगर (bytes_पढ़ो > 0 && copy_to_user(buf, kbuffer, bytes_पढ़ो))
		bytes_पढ़ो = -EFAULT;

	kमुक्त(kbuffer);
	pp_enable_irq(pp);
	वापस bytes_पढ़ो;
पूर्ण

अटल sमाप_प्रकार pp_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
			माप_प्रकार count, loff_t *ppos)
अणु
	अचिन्हित पूर्णांक minor = iminor(file_inode(file));
	काष्ठा pp_काष्ठा *pp = file->निजी_data;
	अक्षर *kbuffer;
	sमाप_प्रकार bytes_written = 0;
	sमाप_प्रकार wrote;
	पूर्णांक mode;
	काष्ठा parport *pport;

	अगर (!(pp->flags & PP_CLAIMED)) अणु
		/* Don't have the port claimed */
		pr_debug(CHRDEV "%x: claim the port first\n", minor);
		वापस -EINVAL;
	पूर्ण

	kbuffer = kदो_स्मृति(min_t(माप_प्रकार, count, PP_BUFFER_SIZE), GFP_KERNEL);
	अगर (!kbuffer)
		वापस -ENOMEM;

	pport = pp->pdev->port;
	mode = pport->ieee1284.mode & ~(IEEE1284_DEVICEID | IEEE1284_ADDR);

	parport_set_समयout(pp->pdev,
			    (file->f_flags & O_NONBLOCK) ?
			    PARPORT_INACTIVITY_O_NONBLOCK :
			    pp->शेष_inactivity);

	जबतक (bytes_written < count) अणु
		sमाप_प्रकार n = min_t(अचिन्हित दीर्घ, count - bytes_written, PP_BUFFER_SIZE);

		अगर (copy_from_user(kbuffer, buf + bytes_written, n)) अणु
			bytes_written = -EFAULT;
			अवरोध;
		पूर्ण

		अगर ((pp->flags & PP_FASTWRITE) && (mode == IEEE1284_MODE_EPP)) अणु
			/* करो a fast EPP ग_लिखो */
			अगर (pport->ieee1284.mode & IEEE1284_ADDR) अणु
				wrote = pport->ops->epp_ग_लिखो_addr(pport,
					kbuffer, n, PARPORT_EPP_FAST);
			पूर्ण अन्यथा अणु
				wrote = pport->ops->epp_ग_लिखो_data(pport,
					kbuffer, n, PARPORT_EPP_FAST);
			पूर्ण
		पूर्ण अन्यथा अणु
			wrote = parport_ग_लिखो(pp->pdev->port, kbuffer, n);
		पूर्ण

		अगर (wrote <= 0) अणु
			अगर (!bytes_written)
				bytes_written = wrote;
			अवरोध;
		पूर्ण

		bytes_written += wrote;

		अगर (file->f_flags & O_NONBLOCK) अणु
			अगर (!bytes_written)
				bytes_written = -EAGAIN;
			अवरोध;
		पूर्ण

		अगर (संकेत_pending(current))
			अवरोध;

		cond_resched();
	पूर्ण

	parport_set_समयout(pp->pdev, pp->शेष_inactivity);

	kमुक्त(kbuffer);
	pp_enable_irq(pp);
	वापस bytes_written;
पूर्ण

अटल व्योम pp_irq(व्योम *निजी)
अणु
	काष्ठा pp_काष्ठा *pp = निजी;

	अगर (pp->irqresponse) अणु
		parport_ग_लिखो_control(pp->pdev->port, pp->irqctl);
		pp->irqresponse = 0;
	पूर्ण

	atomic_inc(&pp->irqc);
	wake_up_पूर्णांकerruptible(&pp->irq_रुको);
पूर्ण

अटल पूर्णांक रेजिस्टर_device(पूर्णांक minor, काष्ठा pp_काष्ठा *pp)
अणु
	काष्ठा parport *port;
	काष्ठा pardevice *pdev = शून्य;
	अक्षर *name;
	काष्ठा pardev_cb ppdev_cb;
	पूर्णांक rc = 0, index;

	name = kaप्र_लिखो(GFP_KERNEL, CHRDEV "%x", minor);
	अगर (name == शून्य)
		वापस -ENOMEM;

	port = parport_find_number(minor);
	अगर (!port) अणु
		pr_warn("%s: no associated port!\n", name);
		rc = -ENXIO;
		जाओ err;
	पूर्ण

	index = ida_simple_get(&ida_index, 0, 0, GFP_KERNEL);
	स_रखो(&ppdev_cb, 0, माप(ppdev_cb));
	ppdev_cb.irq_func = pp_irq;
	ppdev_cb.flags = (pp->flags & PP_EXCL) ? PARPORT_FLAG_EXCL : 0;
	ppdev_cb.निजी = pp;
	pdev = parport_रेजिस्टर_dev_model(port, name, &ppdev_cb, index);
	parport_put_port(port);

	अगर (!pdev) अणु
		pr_warn("%s: failed to register device!\n", name);
		rc = -ENXIO;
		ida_simple_हटाओ(&ida_index, index);
		जाओ err;
	पूर्ण

	pp->pdev = pdev;
	pp->index = index;
	dev_dbg(&pdev->dev, "registered pardevice\n");
err:
	kमुक्त(name);
	वापस rc;
पूर्ण

अटल क्रमागत ieee1284_phase init_phase(पूर्णांक mode)
अणु
	चयन (mode & ~(IEEE1284_DEVICEID
			 | IEEE1284_ADDR)) अणु
	हाल IEEE1284_MODE_NIBBLE:
	हाल IEEE1284_MODE_BYTE:
		वापस IEEE1284_PH_REV_IDLE;
	पूर्ण
	वापस IEEE1284_PH_FWD_IDLE;
पूर्ण

अटल पूर्णांक pp_set_समयout(काष्ठा pardevice *pdev, दीर्घ tv_sec, पूर्णांक tv_usec)
अणु
	दीर्घ to_jअगरfies;

	अगर ((tv_sec < 0) || (tv_usec < 0))
		वापस -EINVAL;

	to_jअगरfies = usecs_to_jअगरfies(tv_usec);
	to_jअगरfies += tv_sec * HZ;
	अगर (to_jअगरfies <= 0)
		वापस -EINVAL;

	pdev->समयout = to_jअगरfies;
	वापस 0;
पूर्ण

अटल पूर्णांक pp_करो_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	अचिन्हित पूर्णांक minor = iminor(file_inode(file));
	काष्ठा pp_काष्ठा *pp = file->निजी_data;
	काष्ठा parport *port;
	व्योम __user *argp = (व्योम __user *)arg;
	काष्ठा ieee1284_info *info;
	अचिन्हित अक्षर reg;
	अचिन्हित अक्षर mask;
	पूर्णांक mode;
	s32 समय32[2];
	s64 समय64[2];
	काष्ठा बारpec64 ts;
	पूर्णांक ret;

	/* First handle the हालs that करोn't take arguments. */
	चयन (cmd) अणु
	हाल PPCLAIM:
	    अणु
		अगर (pp->flags & PP_CLAIMED) अणु
			dev_dbg(&pp->pdev->dev, "you've already got it!\n");
			वापस -EINVAL;
		पूर्ण

		/* Deferred device registration. */
		अगर (!pp->pdev) अणु
			पूर्णांक err = रेजिस्टर_device(minor, pp);

			अगर (err)
				वापस err;
		पूर्ण

		ret = parport_claim_or_block(pp->pdev);
		अगर (ret < 0)
			वापस ret;

		pp->flags |= PP_CLAIMED;

		/* For पूर्णांकerrupt-reporting to work, we need to be
		 * inक्रमmed of each पूर्णांकerrupt. */
		pp_enable_irq(pp);

		/* We may need to fix up the state machine. */
		info = &pp->pdev->port->ieee1284;
		pp->saved_state.mode = info->mode;
		pp->saved_state.phase = info->phase;
		info->mode = pp->state.mode;
		info->phase = pp->state.phase;
		pp->शेष_inactivity = parport_set_समयout(pp->pdev, 0);
		parport_set_समयout(pp->pdev, pp->शेष_inactivity);

		वापस 0;
	    पूर्ण
	हाल PPEXCL:
		अगर (pp->pdev) अणु
			dev_dbg(&pp->pdev->dev,
				"too late for PPEXCL; already registered\n");
			अगर (pp->flags & PP_EXCL)
				/* But it's not really an error. */
				वापस 0;
			/* There's no chance of making the driver happy. */
			वापस -EINVAL;
		पूर्ण

		/* Just remember to रेजिस्टर the device exclusively
		 * when we finally करो the registration. */
		pp->flags |= PP_EXCL;
		वापस 0;
	हाल PPSETMODE:
	    अणु
		पूर्णांक mode;

		अगर (copy_from_user(&mode, argp, माप(mode)))
			वापस -EFAULT;
		/* FIXME: validate mode */
		pp->state.mode = mode;
		pp->state.phase = init_phase(mode);

		अगर (pp->flags & PP_CLAIMED) अणु
			pp->pdev->port->ieee1284.mode = mode;
			pp->pdev->port->ieee1284.phase = pp->state.phase;
		पूर्ण

		वापस 0;
	    पूर्ण
	हाल PPGETMODE:
	    अणु
		पूर्णांक mode;

		अगर (pp->flags & PP_CLAIMED)
			mode = pp->pdev->port->ieee1284.mode;
		अन्यथा
			mode = pp->state.mode;

		अगर (copy_to_user(argp, &mode, माप(mode)))
			वापस -EFAULT;
		वापस 0;
	    पूर्ण
	हाल PPSETPHASE:
	    अणु
		पूर्णांक phase;

		अगर (copy_from_user(&phase, argp, माप(phase)))
			वापस -EFAULT;

		/* FIXME: validate phase */
		pp->state.phase = phase;

		अगर (pp->flags & PP_CLAIMED)
			pp->pdev->port->ieee1284.phase = phase;

		वापस 0;
	    पूर्ण
	हाल PPGETPHASE:
	    अणु
		पूर्णांक phase;

		अगर (pp->flags & PP_CLAIMED)
			phase = pp->pdev->port->ieee1284.phase;
		अन्यथा
			phase = pp->state.phase;
		अगर (copy_to_user(argp, &phase, माप(phase)))
			वापस -EFAULT;
		वापस 0;
	    पूर्ण
	हाल PPGETMODES:
	    अणु
		अचिन्हित पूर्णांक modes;

		port = parport_find_number(minor);
		अगर (!port)
			वापस -ENODEV;

		modes = port->modes;
		parport_put_port(port);
		अगर (copy_to_user(argp, &modes, माप(modes)))
			वापस -EFAULT;
		वापस 0;
	    पूर्ण
	हाल PPSETFLAGS:
	    अणु
		पूर्णांक uflags;

		अगर (copy_from_user(&uflags, argp, माप(uflags)))
			वापस -EFAULT;
		pp->flags &= ~PP_FLAGMASK;
		pp->flags |= (uflags & PP_FLAGMASK);
		वापस 0;
	    पूर्ण
	हाल PPGETFLAGS:
	    अणु
		पूर्णांक uflags;

		uflags = pp->flags & PP_FLAGMASK;
		अगर (copy_to_user(argp, &uflags, माप(uflags)))
			वापस -EFAULT;
		वापस 0;
	    पूर्ण
	पूर्ण	/* end चयन() */

	/* Everything अन्यथा requires the port to be claimed, so check
	 * that now. */
	अगर ((pp->flags & PP_CLAIMED) == 0) अणु
		pr_debug(CHRDEV "%x: claim the port first\n", minor);
		वापस -EINVAL;
	पूर्ण

	port = pp->pdev->port;
	चयन (cmd) अणु
	हाल PPRSTATUS:
		reg = parport_पढ़ो_status(port);
		अगर (copy_to_user(argp, &reg, माप(reg)))
			वापस -EFAULT;
		वापस 0;
	हाल PPRDATA:
		reg = parport_पढ़ो_data(port);
		अगर (copy_to_user(argp, &reg, माप(reg)))
			वापस -EFAULT;
		वापस 0;
	हाल PPRCONTROL:
		reg = parport_पढ़ो_control(port);
		अगर (copy_to_user(argp, &reg, माप(reg)))
			वापस -EFAULT;
		वापस 0;
	हाल PPYIELD:
		parport_yield_blocking(pp->pdev);
		वापस 0;

	हाल PPRELEASE:
		/* Save the state machine's state. */
		info = &pp->pdev->port->ieee1284;
		pp->state.mode = info->mode;
		pp->state.phase = info->phase;
		info->mode = pp->saved_state.mode;
		info->phase = pp->saved_state.phase;
		parport_release(pp->pdev);
		pp->flags &= ~PP_CLAIMED;
		वापस 0;

	हाल PPWCONTROL:
		अगर (copy_from_user(&reg, argp, माप(reg)))
			वापस -EFAULT;
		parport_ग_लिखो_control(port, reg);
		वापस 0;

	हाल PPWDATA:
		अगर (copy_from_user(&reg, argp, माप(reg)))
			वापस -EFAULT;
		parport_ग_लिखो_data(port, reg);
		वापस 0;

	हाल PPFCONTROL:
		अगर (copy_from_user(&mask, argp,
				   माप(mask)))
			वापस -EFAULT;
		अगर (copy_from_user(&reg, 1 + (अचिन्हित अक्षर __user *) arg,
				   माप(reg)))
			वापस -EFAULT;
		parport_frob_control(port, mask, reg);
		वापस 0;

	हाल PPDATAसूची:
		अगर (copy_from_user(&mode, argp, माप(mode)))
			वापस -EFAULT;
		अगर (mode)
			port->ops->data_reverse(port);
		अन्यथा
			port->ops->data_क्रमward(port);
		वापस 0;

	हाल PPNEGOT:
		अगर (copy_from_user(&mode, argp, माप(mode)))
			वापस -EFAULT;
		चयन ((ret = parport_negotiate(port, mode))) अणु
		हाल 0: अवरोध;
		हाल -1: /* handshake failed, peripheral not IEEE 1284 */
			ret = -EIO;
			अवरोध;
		हाल 1:  /* handshake succeeded, peripheral rejected mode */
			ret = -ENXIO;
			अवरोध;
		पूर्ण
		pp_enable_irq(pp);
		वापस ret;

	हाल PPWCTLONIRQ:
		अगर (copy_from_user(&reg, argp, माप(reg)))
			वापस -EFAULT;

		/* Remember what to set the control lines to, क्रम next
		 * समय we get an पूर्णांकerrupt. */
		pp->irqctl = reg;
		pp->irqresponse = 1;
		वापस 0;

	हाल PPCLRIRQ:
		ret = atomic_पढ़ो(&pp->irqc);
		अगर (copy_to_user(argp, &ret, माप(ret)))
			वापस -EFAULT;
		atomic_sub(ret, &pp->irqc);
		वापस 0;

	हाल PPSETTIME32:
		अगर (copy_from_user(समय32, argp, माप(समय32)))
			वापस -EFAULT;

		अगर ((समय32[0] < 0) || (समय32[1] < 0))
			वापस -EINVAL;

		वापस pp_set_समयout(pp->pdev, समय32[0], समय32[1]);

	हाल PPSETTIME64:
		अगर (copy_from_user(समय64, argp, माप(समय64)))
			वापस -EFAULT;

		अगर ((समय64[0] < 0) || (समय64[1] < 0))
			वापस -EINVAL;

		अगर (IS_ENABLED(CONFIG_SPARC64) && !in_compat_syscall())
			समय64[1] >>= 32;

		वापस pp_set_समयout(pp->pdev, समय64[0], समय64[1]);

	हाल PPGETTIME32:
		jअगरfies_to_बारpec64(pp->pdev->समयout, &ts);
		समय32[0] = ts.tv_sec;
		समय32[1] = ts.tv_nsec / NSEC_PER_USEC;

		अगर (copy_to_user(argp, समय32, माप(समय32)))
			वापस -EFAULT;

		वापस 0;

	हाल PPGETTIME64:
		jअगरfies_to_बारpec64(pp->pdev->समयout, &ts);
		समय64[0] = ts.tv_sec;
		समय64[1] = ts.tv_nsec / NSEC_PER_USEC;

		अगर (IS_ENABLED(CONFIG_SPARC64) && !in_compat_syscall())
			समय64[1] <<= 32;

		अगर (copy_to_user(argp, समय64, माप(समय64)))
			वापस -EFAULT;

		वापस 0;

	शेष:
		dev_dbg(&pp->pdev->dev, "What? (cmd=0x%x)\n", cmd);
		वापस -EINVAL;
	पूर्ण

	/* Keep the compiler happy */
	वापस 0;
पूर्ण

अटल दीर्घ pp_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	दीर्घ ret;

	mutex_lock(&pp_करो_mutex);
	ret = pp_करो_ioctl(file, cmd, arg);
	mutex_unlock(&pp_करो_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक pp_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अचिन्हित पूर्णांक minor = iminor(inode);
	काष्ठा pp_काष्ठा *pp;

	अगर (minor >= PARPORT_MAX)
		वापस -ENXIO;

	pp = kदो_स्मृति(माप(काष्ठा pp_काष्ठा), GFP_KERNEL);
	अगर (!pp)
		वापस -ENOMEM;

	pp->state.mode = IEEE1284_MODE_COMPAT;
	pp->state.phase = init_phase(pp->state.mode);
	pp->flags = 0;
	pp->irqresponse = 0;
	atomic_set(&pp->irqc, 0);
	init_रुकोqueue_head(&pp->irq_रुको);

	/* Defer the actual device registration until the first claim.
	 * That way, we know whether or not the driver wants to have
	 * exclusive access to the port (PPEXCL).
	 */
	pp->pdev = शून्य;
	file->निजी_data = pp;

	वापस 0;
पूर्ण

अटल पूर्णांक pp_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अचिन्हित पूर्णांक minor = iminor(inode);
	काष्ठा pp_काष्ठा *pp = file->निजी_data;
	पूर्णांक compat_negot;

	compat_negot = 0;
	अगर (!(pp->flags & PP_CLAIMED) && pp->pdev &&
	    (pp->state.mode != IEEE1284_MODE_COMPAT)) अणु
		काष्ठा ieee1284_info *info;

		/* parport released, but not in compatibility mode */
		parport_claim_or_block(pp->pdev);
		pp->flags |= PP_CLAIMED;
		info = &pp->pdev->port->ieee1284;
		pp->saved_state.mode = info->mode;
		pp->saved_state.phase = info->phase;
		info->mode = pp->state.mode;
		info->phase = pp->state.phase;
		compat_negot = 1;
	पूर्ण अन्यथा अगर ((pp->flags & PP_CLAIMED) && pp->pdev &&
	    (pp->pdev->port->ieee1284.mode != IEEE1284_MODE_COMPAT)) अणु
		compat_negot = 2;
	पूर्ण
	अगर (compat_negot) अणु
		parport_negotiate(pp->pdev->port, IEEE1284_MODE_COMPAT);
		dev_dbg(&pp->pdev->dev,
			"negotiated back to compatibility mode because user-space forgot\n");
	पूर्ण

	अगर ((pp->flags & PP_CLAIMED) && pp->pdev) अणु
		काष्ठा ieee1284_info *info;

		info = &pp->pdev->port->ieee1284;
		pp->state.mode = info->mode;
		pp->state.phase = info->phase;
		info->mode = pp->saved_state.mode;
		info->phase = pp->saved_state.phase;
		parport_release(pp->pdev);
		अगर (compat_negot != 1) अणु
			pr_debug(CHRDEV "%x: released pardevice "
				"because user-space forgot\n", minor);
		पूर्ण
	पूर्ण

	अगर (pp->pdev) अणु
		parport_unरेजिस्टर_device(pp->pdev);
		ida_simple_हटाओ(&ida_index, pp->index);
		pp->pdev = शून्य;
		pr_debug(CHRDEV "%x: unregistered pardevice\n", minor);
	पूर्ण

	kमुक्त(pp);

	वापस 0;
पूर्ण

/* No kernel lock held - fine */
अटल __poll_t pp_poll(काष्ठा file *file, poll_table *रुको)
अणु
	काष्ठा pp_काष्ठा *pp = file->निजी_data;
	__poll_t mask = 0;

	poll_रुको(file, &pp->irq_रुको, रुको);
	अगर (atomic_पढ़ो(&pp->irqc))
		mask |= EPOLLIN | EPOLLRDNORM;

	वापस mask;
पूर्ण

अटल काष्ठा class *ppdev_class;

अटल स्थिर काष्ठा file_operations pp_fops = अणु
	.owner		= THIS_MODULE,
	.llseek		= no_llseek,
	.पढ़ो		= pp_पढ़ो,
	.ग_लिखो		= pp_ग_लिखो,
	.poll		= pp_poll,
	.unlocked_ioctl	= pp_ioctl,
	.compat_ioctl   = compat_ptr_ioctl,
	.खोलो		= pp_खोलो,
	.release	= pp_release,
पूर्ण;

अटल व्योम pp_attach(काष्ठा parport *port)
अणु
	काष्ठा device *ret;

	अगर (devices[port->number])
		वापस;

	ret = device_create(ppdev_class, port->dev,
			    MKDEV(PP_MAJOR, port->number), शून्य,
			    "parport%d", port->number);
	अगर (IS_ERR(ret)) अणु
		pr_err("Failed to create device parport%d\n",
		       port->number);
		वापस;
	पूर्ण
	devices[port->number] = ret;
पूर्ण

अटल व्योम pp_detach(काष्ठा parport *port)
अणु
	अगर (!devices[port->number])
		वापस;

	device_destroy(ppdev_class, MKDEV(PP_MAJOR, port->number));
	devices[port->number] = शून्य;
पूर्ण

अटल पूर्णांक pp_probe(काष्ठा pardevice *par_dev)
अणु
	काष्ठा device_driver *drv = par_dev->dev.driver;
	पूर्णांक len = म_माप(drv->name);

	अगर (म_भेदन(par_dev->name, drv->name, len))
		वापस -ENODEV;

	वापस 0;
पूर्ण

अटल काष्ठा parport_driver pp_driver = अणु
	.name		= CHRDEV,
	.probe		= pp_probe,
	.match_port	= pp_attach,
	.detach		= pp_detach,
	.devmodel	= true,
पूर्ण;

अटल पूर्णांक __init ppdev_init(व्योम)
अणु
	पूर्णांक err = 0;

	अगर (रेजिस्टर_chrdev(PP_MAJOR, CHRDEV, &pp_fops)) अणु
		pr_warn(CHRDEV ": unable to get major %d\n", PP_MAJOR);
		वापस -EIO;
	पूर्ण
	ppdev_class = class_create(THIS_MODULE, CHRDEV);
	अगर (IS_ERR(ppdev_class)) अणु
		err = PTR_ERR(ppdev_class);
		जाओ out_chrdev;
	पूर्ण
	err = parport_रेजिस्टर_driver(&pp_driver);
	अगर (err < 0) अणु
		pr_warn(CHRDEV ": unable to register with parport\n");
		जाओ out_class;
	पूर्ण

	pr_info(PP_VERSION "\n");
	जाओ out;

out_class:
	class_destroy(ppdev_class);
out_chrdev:
	unरेजिस्टर_chrdev(PP_MAJOR, CHRDEV);
out:
	वापस err;
पूर्ण

अटल व्योम __निकास ppdev_cleanup(व्योम)
अणु
	/* Clean up all parport stuff */
	parport_unरेजिस्टर_driver(&pp_driver);
	class_destroy(ppdev_class);
	unरेजिस्टर_chrdev(PP_MAJOR, CHRDEV);
पूर्ण

module_init(ppdev_init);
module_निकास(ppdev_cleanup);

MODULE_LICENSE("GPL");
MODULE_ALIAS_CHARDEV_MAJOR(PP_MAJOR);
