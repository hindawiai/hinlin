<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Copyright (C) 1992 obz under the linux copyright
 *
 *  Dynamic diacritical handling - aeb@cwi.nl - Dec 1993
 *  Dynamic keymap and string allocation - aeb@cwi.nl - May 1994
 *  Restrict VT चयनing via ioctl() - grअगर@cs.ucr.edu - Dec 1995
 *  Some code moved क्रम less code duplication - Andi Kleen - Mar 1997
 *  Check put/get_user, cleanups - acme@conectiva.com.br - Jun 2001
 */

#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/tty.h>
#समावेश <linux/समयr.h>
#समावेश <linux/kernel.h>
#समावेश <linux/compat.h>
#समावेश <linux/module.h>
#समावेश <linux/kd.h>
#समावेश <linux/vt.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/major.h>
#समावेश <linux/fs.h>
#समावेश <linux/console.h>
#समावेश <linux/consolemap.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/suspend.h>
#समावेश <linux/समयx.h>

#समावेश <यंत्र/पन.स>
#समावेश <linux/uaccess.h>

#समावेश <linux/nospec.h>

#समावेश <linux/kbd_kern.h>
#समावेश <linux/vt_kern.h>
#समावेश <linux/kbd_diacr.h>
#समावेश <linux/selection.h>

bool vt_करोnt_चयन;

अटल अंतरभूत bool vt_in_use(अचिन्हित पूर्णांक i)
अणु
	स्थिर काष्ठा vc_data *vc = vc_cons[i].d;

	/*
	 * console_lock must be held to prevent the vc from being deallocated
	 * जबतक we're checking whether it's in-use.
	 */
	WARN_CONSOLE_UNLOCKED();

	वापस vc && kref_पढ़ो(&vc->port.kref) > 1;
पूर्ण

अटल अंतरभूत bool vt_busy(पूर्णांक i)
अणु
	अगर (vt_in_use(i))
		वापस true;
	अगर (i == fg_console)
		वापस true;
	अगर (vc_is_sel(vc_cons[i].d))
		वापस true;

	वापस false;
पूर्ण

/*
 * Console (vt and kd) routines, as defined by USL SVR4 manual, and by
 * experimentation and study of X386 SYSV handling.
 *
 * One poपूर्णांक of dअगरference: SYSV vt's are /dev/vtX, which X >= 0, and
 * /dev/console is a separate ttyp. Under Linux, /dev/tty0 is /dev/console,
 * and the vc start at /dev/ttyX, X >= 1. We मुख्यtain that here, so we will
 * always treat our set of vt as numbered 1..MAX_NR_CONSOLES (corresponding to
 * ttys 0..MAX_NR_CONSOLES-1). Explicitly naming VT 0 is illegal, but using
 * /dev/tty0 (fg_console) as a target is legal, since an implicit aliasing
 * to the current console is करोne by the मुख्य ioctl code.
 */

#अगर_घोषित CONFIG_X86
#समावेश <यंत्र/syscalls.h>
#पूर्ण_अगर

अटल व्योम complete_change_console(काष्ठा vc_data *vc);

/*
 *	User space VT_EVENT handlers
 */

काष्ठा vt_event_रुको अणु
	काष्ठा list_head list;
	काष्ठा vt_event event;
	पूर्णांक करोne;
पूर्ण;

अटल LIST_HEAD(vt_events);
अटल DEFINE_SPINLOCK(vt_event_lock);
अटल DECLARE_WAIT_QUEUE_HEAD(vt_event_रुकोqueue);

/**
 *	vt_event_post
 *	@event: the event that occurred
 *	@old: old console
 *	@new: new console
 *
 *	Post an VT event to पूर्णांकerested VT handlers
 */

व्योम vt_event_post(अचिन्हित पूर्णांक event, अचिन्हित पूर्णांक old, अचिन्हित पूर्णांक new)
अणु
	काष्ठा list_head *pos, *head;
	अचिन्हित दीर्घ flags;
	पूर्णांक wake = 0;

	spin_lock_irqsave(&vt_event_lock, flags);
	head = &vt_events;

	list_क्रम_each(pos, head) अणु
		काष्ठा vt_event_रुको *ve = list_entry(pos,
						काष्ठा vt_event_रुको, list);
		अगर (!(ve->event.event & event))
			जारी;
		ve->event.event = event;
		/* kernel view is consoles 0..n-1, user space view is
		   console 1..n with 0 meaning current, so we must bias */
		ve->event.oldev = old + 1;
		ve->event.newev = new + 1;
		wake = 1;
		ve->करोne = 1;
	पूर्ण
	spin_unlock_irqrestore(&vt_event_lock, flags);
	अगर (wake)
		wake_up_पूर्णांकerruptible(&vt_event_रुकोqueue);
पूर्ण

अटल व्योम __vt_event_queue(काष्ठा vt_event_रुको *vw)
अणु
	अचिन्हित दीर्घ flags;
	/* Prepare the event */
	INIT_LIST_HEAD(&vw->list);
	vw->करोne = 0;
	/* Queue our event */
	spin_lock_irqsave(&vt_event_lock, flags);
	list_add(&vw->list, &vt_events);
	spin_unlock_irqrestore(&vt_event_lock, flags);
पूर्ण

अटल व्योम __vt_event_रुको(काष्ठा vt_event_रुको *vw)
अणु
	/* Wait क्रम it to pass */
	रुको_event_पूर्णांकerruptible(vt_event_रुकोqueue, vw->करोne);
पूर्ण

अटल व्योम __vt_event_dequeue(काष्ठा vt_event_रुको *vw)
अणु
	अचिन्हित दीर्घ flags;

	/* Dequeue it */
	spin_lock_irqsave(&vt_event_lock, flags);
	list_del(&vw->list);
	spin_unlock_irqrestore(&vt_event_lock, flags);
पूर्ण

/**
 *	vt_event_रुको		-	रुको क्रम an event
 *	@vw: our event
 *
 *	Waits क्रम an event to occur which completes our vt_event_रुको
 *	काष्ठाure. On वापस the काष्ठाure has wv->करोne set to 1 क्रम success
 *	or 0 अगर some event such as a संकेत ended the रुको.
 */

अटल व्योम vt_event_रुको(काष्ठा vt_event_रुको *vw)
अणु
	__vt_event_queue(vw);
	__vt_event_रुको(vw);
	__vt_event_dequeue(vw);
पूर्ण

/**
 *	vt_event_रुको_ioctl	-	event ioctl handler
 *	@event: argument to ioctl (the event)
 *
 *	Implement the VT_WAITEVENT ioctl using the VT event पूर्णांकerface
 */

अटल पूर्णांक vt_event_रुको_ioctl(काष्ठा vt_event __user *event)
अणु
	काष्ठा vt_event_रुको vw;

	अगर (copy_from_user(&vw.event, event, माप(काष्ठा vt_event)))
		वापस -EFAULT;
	/* Highest supported event क्रम now */
	अगर (vw.event.event & ~VT_MAX_EVENT)
		वापस -EINVAL;

	vt_event_रुको(&vw);
	/* If it occurred report it */
	अगर (vw.करोne) अणु
		अगर (copy_to_user(event, &vw.event, माप(काष्ठा vt_event)))
			वापस -EFAULT;
		वापस 0;
	पूर्ण
	वापस -EINTR;
पूर्ण

/**
 *	vt_रुकोactive	-	active console रुको
 *	@n: new console
 *
 *	Helper क्रम event रुकोs. Used to implement the legacy
 *	event रुकोing ioctls in terms of events
 */

पूर्णांक vt_रुकोactive(पूर्णांक n)
अणु
	काष्ठा vt_event_रुको vw;
	करो अणु
		vw.event.event = VT_EVENT_SWITCH;
		__vt_event_queue(&vw);
		अगर (n == fg_console + 1) अणु
			__vt_event_dequeue(&vw);
			अवरोध;
		पूर्ण
		__vt_event_रुको(&vw);
		__vt_event_dequeue(&vw);
		अगर (vw.करोne == 0)
			वापस -EINTR;
	पूर्ण जबतक (vw.event.newev != n);
	वापस 0;
पूर्ण

/*
 * these are the valid i/o ports we're allowed to change. they map all the
 * video ports
 */
#घोषणा GPFIRST 0x3b4
#घोषणा GPLAST 0x3df
#घोषणा GPNUM (GPLAST - GPFIRST + 1)

/*
 * currently, setting the mode from KD_TEXT to KD_GRAPHICS करोesn't करो a whole
 * lot. i'm not sure अगर it should करो any restoration of modes or what...
 *
 * XXX It should at least call पूर्णांकo the driver, fbdev's definitely need to
 * restore their engine state. --BenH
 */
अटल पूर्णांक vt_kdseपंचांगode(काष्ठा vc_data *vc, अचिन्हित दीर्घ mode)
अणु
	चयन (mode) अणु
	हाल KD_GRAPHICS:
		अवरोध;
	हाल KD_TEXT0:
	हाल KD_TEXT1:
		mode = KD_TEXT;
		fallthrough;
	हाल KD_TEXT:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* FIXME: this needs the console lock extending */
	अगर (vc->vc_mode == mode)
		वापस 0;

	vc->vc_mode = mode;
	अगर (vc->vc_num != fg_console)
		वापस 0;

	/* explicitly blank/unblank the screen अगर चयनing modes */
	console_lock();
	अगर (mode == KD_TEXT)
		करो_unblank_screen(1);
	अन्यथा
		करो_blank_screen(1);
	console_unlock();

	वापस 0;
पूर्ण

अटल पूर्णांक vt_k_ioctl(काष्ठा tty_काष्ठा *tty, अचिन्हित पूर्णांक cmd,
		अचिन्हित दीर्घ arg, bool perm)
अणु
	काष्ठा vc_data *vc = tty->driver_data;
	व्योम __user *up = (व्योम __user *)arg;
	अचिन्हित पूर्णांक console = vc->vc_num;
	पूर्णांक ret;

	चयन (cmd) अणु
	हाल KIOCSOUND:
		अगर (!perm)
			वापस -EPERM;
		/*
		 * The use of PIT_TICK_RATE is historic, it used to be
		 * the platक्रमm-dependent CLOCK_TICK_RATE between 2.6.12
		 * and 2.6.36, which was a minor but unक्रमtunate ABI
		 * change. kd_mksound is locked by the input layer.
		 */
		अगर (arg)
			arg = PIT_TICK_RATE / arg;
		kd_mksound(arg, 0);
		अवरोध;

	हाल KDMKTONE:
		अगर (!perm)
			वापस -EPERM;
	अणु
		अचिन्हित पूर्णांक ticks, count;

		/*
		 * Generate the tone क्रम the appropriate number of ticks.
		 * If the समय is zero, turn off sound ourselves.
		 */
		ticks = msecs_to_jअगरfies((arg >> 16) & 0xffff);
		count = ticks ? (arg & 0xffff) : 0;
		अगर (count)
			count = PIT_TICK_RATE / count;
		kd_mksound(count, ticks);
		अवरोध;
	पूर्ण

	हाल KDGKBTYPE:
		/*
		 * this is naथ/ve.
		 */
		वापस put_user(KB_101, (अक्षर __user *)arg);

		/*
		 * These cannot be implemented on any machine that implements
		 * ioperm() in user level (such as Alpha PCs) or not at all.
		 *
		 * XXX: you should never use these, just call ioperm directly..
		 */
#अगर_घोषित CONFIG_X86
	हाल KDADDIO:
	हाल KDDELIO:
		/*
		 * KDADDIO and KDDELIO may be able to add ports beyond what
		 * we reject here, but to be safe...
		 *
		 * These are locked पूर्णांकernally via sys_ioperm
		 */
		अगर (arg < GPFIRST || arg > GPLAST)
			वापस -EINVAL;

		वापस ksys_ioperm(arg, 1, (cmd == KDADDIO)) ? -ENXIO : 0;

	हाल KDENABIO:
	हाल KDDISABIO:
		वापस ksys_ioperm(GPFIRST, GPNUM,
				  (cmd == KDENABIO)) ? -ENXIO : 0;
#पूर्ण_अगर

	/* Linux m68k/i386 पूर्णांकerface क्रम setting the keyboard delay/repeat rate */

	हाल KDKBDREP:
	अणु
		काष्ठा kbd_repeat kbrep;

		अगर (!capable(CAP_SYS_TTY_CONFIG))
			वापस -EPERM;

		अगर (copy_from_user(&kbrep, up, माप(काष्ठा kbd_repeat)))
			वापस -EFAULT;

		ret = kbd_rate(&kbrep);
		अगर (ret)
			वापस ret;
		अगर (copy_to_user(up, &kbrep, माप(काष्ठा kbd_repeat)))
			वापस -EFAULT;
		अवरोध;
	पूर्ण

	हाल KDSETMODE:
		अगर (!perm)
			वापस -EPERM;

		वापस vt_kdseपंचांगode(vc, arg);

	हाल KDGETMODE:
		वापस put_user(vc->vc_mode, (पूर्णांक __user *)arg);

	हाल KDMAPDISP:
	हाल KDUNMAPDISP:
		/*
		 * these work like a combination of mmap and KDENABIO.
		 * this could be easily finished.
		 */
		वापस -EINVAL;

	हाल KDSKBMODE:
		अगर (!perm)
			वापस -EPERM;
		ret = vt_करो_kdskbmode(console, arg);
		अगर (ret)
			वापस ret;
		tty_ldisc_flush(tty);
		अवरोध;

	हाल KDGKBMODE:
		वापस put_user(vt_करो_kdgkbmode(console), (पूर्णांक __user *)arg);

	/* this could be folded पूर्णांकo KDSKBMODE, but क्रम compatibility
	   reasons it is not so easy to fold KDGKBMETA पूर्णांकo KDGKBMODE */
	हाल KDSKBMETA:
		वापस vt_करो_kdskbmeta(console, arg);

	हाल KDGKBMETA:
		/* FIXME: should review whether this is worth locking */
		वापस put_user(vt_करो_kdgkbmeta(console), (पूर्णांक __user *)arg);

	हाल KDGETKEYCODE:
	हाल KDSETKEYCODE:
		अगर(!capable(CAP_SYS_TTY_CONFIG))
			perm = 0;
		वापस vt_करो_kbkeycode_ioctl(cmd, up, perm);

	हाल KDGKBENT:
	हाल KDSKBENT:
		वापस vt_करो_kdsk_ioctl(cmd, up, perm, console);

	हाल KDGKBSENT:
	हाल KDSKBSENT:
		वापस vt_करो_kdgkb_ioctl(cmd, up, perm);

	/* Diacritical processing. Handled in keyboard.c as it has
	   to operate on the keyboard locks and काष्ठाures */
	हाल KDGKBDIACR:
	हाल KDGKBDIACRUC:
	हाल KDSKBDIACR:
	हाल KDSKBDIACRUC:
		वापस vt_करो_diacrit(cmd, up, perm);

	/* the ioctls below पढ़ो/set the flags usually shown in the leds */
	/* करोn't use them - they will go away without warning */
	हाल KDGKBLED:
	हाल KDSKBLED:
	हाल KDGETLED:
	हाल KDSETLED:
		वापस vt_करो_kdskled(console, cmd, arg, perm);

	/*
	 * A process can indicate its willingness to accept संकेतs
	 * generated by pressing an appropriate key combination.
	 * Thus, one can have a daemon that e.g. spawns a new console
	 * upon a keypress and then changes to it.
	 * See also the kbrequest field of inittab(5).
	 */
	हाल KDSIGACCEPT:
		अगर (!perm || !capable(CAP_KILL))
			वापस -EPERM;
		अगर (!valid_संकेत(arg) || arg < 1 || arg == SIGKILL)
			वापस -EINVAL;

		spin_lock_irq(&vt_spawn_con.lock);
		put_pid(vt_spawn_con.pid);
		vt_spawn_con.pid = get_pid(task_pid(current));
		vt_spawn_con.sig = arg;
		spin_unlock_irq(&vt_spawn_con.lock);
		अवरोध;

	हाल KDFONTOP: अणु
		काष्ठा console_font_op op;

		अगर (copy_from_user(&op, up, माप(op)))
			वापस -EFAULT;
		अगर (!perm && op.op != KD_FONT_OP_GET)
			वापस -EPERM;
		ret = con_font_op(vc, &op);
		अगर (ret)
			वापस ret;
		अगर (copy_to_user(up, &op, माप(op)))
			वापस -EFAULT;
		अवरोध;
	पूर्ण

	शेष:
		वापस -ENOIOCTLCMD;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक करो_unimap_ioctl(पूर्णांक cmd, काष्ठा unimapdesc __user *user_ud,
		bool perm, काष्ठा vc_data *vc)
अणु
	काष्ठा unimapdesc पंचांगp;

	अगर (copy_from_user(&पंचांगp, user_ud, माप पंचांगp))
		वापस -EFAULT;
	चयन (cmd) अणु
	हाल PIO_UNIMAP:
		अगर (!perm)
			वापस -EPERM;
		वापस con_set_unimap(vc, पंचांगp.entry_ct, पंचांगp.entries);
	हाल GIO_UNIMAP:
		अगर (!perm && fg_console != vc->vc_num)
			वापस -EPERM;
		वापस con_get_unimap(vc, पंचांगp.entry_ct, &(user_ud->entry_ct),
				पंचांगp.entries);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक vt_io_ioctl(काष्ठा vc_data *vc, अचिन्हित पूर्णांक cmd, व्योम __user *up,
		bool perm)
अणु
	चयन (cmd) अणु
	हाल PIO_CMAP:
		अगर (!perm)
			वापस -EPERM;
		वापस con_set_cmap(up);

	हाल GIO_CMAP:
		वापस con_get_cmap(up);

	हाल PIO_SCRNMAP:
		अगर (!perm)
			वापस -EPERM;
		वापस con_set_trans_old(up);

	हाल GIO_SCRNMAP:
		वापस con_get_trans_old(up);

	हाल PIO_UNISCRNMAP:
		अगर (!perm)
			वापस -EPERM;
		वापस con_set_trans_new(up);

	हाल GIO_UNISCRNMAP:
		वापस con_get_trans_new(up);

	हाल PIO_UNIMAPCLR:
		अगर (!perm)
			वापस -EPERM;
		con_clear_unimap(vc);
		अवरोध;

	हाल PIO_UNIMAP:
	हाल GIO_UNIMAP:
		वापस करो_unimap_ioctl(cmd, up, perm, vc);

	शेष:
		वापस -ENOIOCTLCMD;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vt_reldisp(काष्ठा vc_data *vc, अचिन्हित पूर्णांक swtch)
अणु
	पूर्णांक newvt, ret;

	अगर (vc->vt_mode.mode != VT_PROCESS)
		वापस -EINVAL;

	/* Switched-to response */
	अगर (vc->vt_newvt < 0) अणु
		 /* If it's just an ACK, ignore it */
		वापस swtch == VT_ACKACQ ? 0 : -EINVAL;
	पूर्ण

	/* Switching-from response */
	अगर (swtch == 0) अणु
		/* Switch disallowed, so क्रमget we were trying to करो it. */
		vc->vt_newvt = -1;
		वापस 0;
	पूर्ण

	/* The current vt has been released, so complete the चयन. */
	newvt = vc->vt_newvt;
	vc->vt_newvt = -1;
	ret = vc_allocate(newvt);
	अगर (ret)
		वापस ret;

	/*
	 * When we actually करो the console चयन, make sure we are atomic with
	 * respect to other console चयनes..
	 */
	complete_change_console(vc_cons[newvt].d);

	वापस 0;
पूर्ण

अटल पूर्णांक vt_setactivate(काष्ठा vt_setactivate __user *sa)
अणु
	काष्ठा vt_setactivate vsa;
	काष्ठा vc_data *nvc;
	पूर्णांक ret;

	अगर (copy_from_user(&vsa, sa, माप(vsa)))
		वापस -EFAULT;
	अगर (vsa.console == 0 || vsa.console > MAX_NR_CONSOLES)
		वापस -ENXIO;

	vsa.console = array_index_nospec(vsa.console, MAX_NR_CONSOLES + 1);
	vsa.console--;
	console_lock();
	ret = vc_allocate(vsa.console);
	अगर (ret) अणु
		console_unlock();
		वापस ret;
	पूर्ण

	/*
	 * This is safe providing we करोn't drop the console sem between
	 * vc_allocate and finishing referencing nvc.
	 */
	nvc = vc_cons[vsa.console].d;
	nvc->vt_mode = vsa.mode;
	nvc->vt_mode.frsig = 0;
	put_pid(nvc->vt_pid);
	nvc->vt_pid = get_pid(task_pid(current));
	console_unlock();

	/* Commence चयन and lock */
	/* Review set_console locks */
	set_console(vsa.console);

	वापस 0;
पूर्ण

/* deallocate a single console, अगर possible (leave 0) */
अटल पूर्णांक vt_disallocate(अचिन्हित पूर्णांक vc_num)
अणु
	काष्ठा vc_data *vc = शून्य;
	पूर्णांक ret = 0;

	console_lock();
	अगर (vt_busy(vc_num))
		ret = -EBUSY;
	अन्यथा अगर (vc_num)
		vc = vc_deallocate(vc_num);
	console_unlock();

	अगर (vc && vc_num >= MIN_NR_CONSOLES)
		tty_port_put(&vc->port);

	वापस ret;
पूर्ण

/* deallocate all unused consoles, but leave 0 */
अटल व्योम vt_disallocate_all(व्योम)
अणु
	काष्ठा vc_data *vc[MAX_NR_CONSOLES];
	पूर्णांक i;

	console_lock();
	क्रम (i = 1; i < MAX_NR_CONSOLES; i++)
		अगर (!vt_busy(i))
			vc[i] = vc_deallocate(i);
		अन्यथा
			vc[i] = शून्य;
	console_unlock();

	क्रम (i = 1; i < MAX_NR_CONSOLES; i++) अणु
		अगर (vc[i] && i >= MIN_NR_CONSOLES)
			tty_port_put(&vc[i]->port);
	पूर्ण
पूर्ण

अटल पूर्णांक vt_resizex(काष्ठा vc_data *vc, काष्ठा vt_consize __user *cs)
अणु
	काष्ठा vt_consize v;
	पूर्णांक i;

	अगर (copy_from_user(&v, cs, माप(काष्ठा vt_consize)))
		वापस -EFAULT;

	/* FIXME: Should check the copies properly */
	अगर (!v.v_vlin)
		v.v_vlin = vc->vc_scan_lines;

	अगर (v.v_clin) अणु
		पूर्णांक rows = v.v_vlin / v.v_clin;
		अगर (v.v_rows != rows) अणु
			अगर (v.v_rows) /* Parameters करोn't add up */
				वापस -EINVAL;
			v.v_rows = rows;
		पूर्ण
	पूर्ण

	अगर (v.v_vcol && v.v_ccol) अणु
		पूर्णांक cols = v.v_vcol / v.v_ccol;
		अगर (v.v_cols != cols) अणु
			अगर (v.v_cols)
				वापस -EINVAL;
			v.v_cols = cols;
		पूर्ण
	पूर्ण

	अगर (v.v_clin > 32)
		वापस -EINVAL;

	क्रम (i = 0; i < MAX_NR_CONSOLES; i++) अणु
		काष्ठा vc_data *vcp;

		अगर (!vc_cons[i].d)
			जारी;
		console_lock();
		vcp = vc_cons[i].d;
		अगर (vcp) अणु
			पूर्णांक ret;
			पूर्णांक save_scan_lines = vcp->vc_scan_lines;
			पूर्णांक save_cell_height = vcp->vc_cell_height;

			अगर (v.v_vlin)
				vcp->vc_scan_lines = v.v_vlin;
			अगर (v.v_clin)
				vcp->vc_cell_height = v.v_clin;
			vcp->vc_resize_user = 1;
			ret = vc_resize(vcp, v.v_cols, v.v_rows);
			अगर (ret) अणु
				vcp->vc_scan_lines = save_scan_lines;
				vcp->vc_cell_height = save_cell_height;
				console_unlock();
				वापस ret;
			पूर्ण
		पूर्ण
		console_unlock();
	पूर्ण

	वापस 0;
पूर्ण

/*
 * We handle the console-specअगरic ioctl's here.  We allow the
 * capability to modअगरy any console, not just the fg_console.
 */
पूर्णांक vt_ioctl(काष्ठा tty_काष्ठा *tty,
	     अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा vc_data *vc = tty->driver_data;
	व्योम __user *up = (व्योम __user *)arg;
	पूर्णांक i, perm;
	पूर्णांक ret;

	/*
	 * To have permissions to करो most of the vt ioctls, we either have
	 * to be the owner of the tty, or have CAP_SYS_TTY_CONFIG.
	 */
	perm = 0;
	अगर (current->संकेत->tty == tty || capable(CAP_SYS_TTY_CONFIG))
		perm = 1;

	ret = vt_k_ioctl(tty, cmd, arg, perm);
	अगर (ret != -ENOIOCTLCMD)
		वापस ret;

	ret = vt_io_ioctl(vc, cmd, up, perm);
	अगर (ret != -ENOIOCTLCMD)
		वापस ret;

	चयन (cmd) अणु
	हाल TIOCLINUX:
		वापस tioclinux(tty, arg);
	हाल VT_SETMODE:
	अणु
		काष्ठा vt_mode पंचांगp;

		अगर (!perm)
			वापस -EPERM;
		अगर (copy_from_user(&पंचांगp, up, माप(काष्ठा vt_mode)))
			वापस -EFAULT;
		अगर (पंचांगp.mode != VT_AUTO && पंचांगp.mode != VT_PROCESS)
			वापस -EINVAL;

		console_lock();
		vc->vt_mode = पंचांगp;
		/* the frsig is ignored, so we set it to 0 */
		vc->vt_mode.frsig = 0;
		put_pid(vc->vt_pid);
		vc->vt_pid = get_pid(task_pid(current));
		/* no चयन is required -- saw@shade.msu.ru */
		vc->vt_newvt = -1;
		console_unlock();
		अवरोध;
	पूर्ण

	हाल VT_GETMODE:
	अणु
		काष्ठा vt_mode पंचांगp;
		पूर्णांक rc;

		console_lock();
		स_नकल(&पंचांगp, &vc->vt_mode, माप(काष्ठा vt_mode));
		console_unlock();

		rc = copy_to_user(up, &पंचांगp, माप(काष्ठा vt_mode));
		अगर (rc)
			वापस -EFAULT;
		अवरोध;
	पूर्ण

	/*
	 * Returns global vt state. Note that VT 0 is always खोलो, since
	 * it's an alias for the current VT, and people can't use it here.
	 * We cannot वापस state क्रम more than 16 VTs, since v_state is लघु.
	 */
	हाल VT_GETSTATE:
	अणु
		काष्ठा vt_stat __user *vtstat = up;
		अचिन्हित लघु state, mask;

		अगर (put_user(fg_console + 1, &vtstat->v_active))
			वापस -EFAULT;

		state = 1;	/* /dev/tty0 is always खोलो */
		console_lock(); /* required by vt_in_use() */
		क्रम (i = 0, mask = 2; i < MAX_NR_CONSOLES && mask;
				++i, mask <<= 1)
			अगर (vt_in_use(i))
				state |= mask;
		console_unlock();
		वापस put_user(state, &vtstat->v_state);
	पूर्ण

	/*
	 * Returns the first available (non-खोलोed) console.
	 */
	हाल VT_OPENQRY:
		console_lock(); /* required by vt_in_use() */
		क्रम (i = 0; i < MAX_NR_CONSOLES; ++i)
			अगर (!vt_in_use(i))
				अवरोध;
		console_unlock();
		i = i < MAX_NR_CONSOLES ? (i+1) : -1;
		वापस put_user(i, (पूर्णांक __user *)arg);

	/*
	 * ioctl(fd, VT_ACTIVATE, num) will cause us to चयन to vt # num,
	 * with num >= 1 (चयनes to vt 0, our console, are not allowed, just
	 * to preserve sanity).
	 */
	हाल VT_ACTIVATE:
		अगर (!perm)
			वापस -EPERM;
		अगर (arg == 0 || arg > MAX_NR_CONSOLES)
			वापस -ENXIO;

		arg--;
		console_lock();
		ret = vc_allocate(arg);
		console_unlock();
		अगर (ret)
			वापस ret;
		set_console(arg);
		अवरोध;

	हाल VT_SETACTIVATE:
		अगर (!perm)
			वापस -EPERM;

		वापस vt_setactivate(up);

	/*
	 * रुको until the specअगरied VT has been activated
	 */
	हाल VT_WAITACTIVE:
		अगर (!perm)
			वापस -EPERM;
		अगर (arg == 0 || arg > MAX_NR_CONSOLES)
			वापस -ENXIO;
		वापस vt_रुकोactive(arg);

	/*
	 * If a vt is under process control, the kernel will not चयन to it
	 * immediately, but postpone the operation until the process calls this
	 * ioctl, allowing the चयन to complete.
	 *
	 * According to the X sources this is the behavior:
	 *	0:	pending चयन-from not OK
	 *	1:	pending चयन-from OK
	 *	2:	completed चयन-to OK
	 */
	हाल VT_RELDISP:
		अगर (!perm)
			वापस -EPERM;

		console_lock();
		ret = vt_reldisp(vc, arg);
		console_unlock();

		वापस ret;


	 /*
	  * Disallocate memory associated to VT (but leave VT1)
	  */
	 हाल VT_DISALLOCATE:
		अगर (arg > MAX_NR_CONSOLES)
			वापस -ENXIO;

		अगर (arg == 0)
			vt_disallocate_all();
		अन्यथा
			वापस vt_disallocate(--arg);
		अवरोध;

	हाल VT_RESIZE:
	अणु
		काष्ठा vt_sizes __user *vtsizes = up;
		काष्ठा vc_data *vc;
		uलघु ll,cc;

		अगर (!perm)
			वापस -EPERM;
		अगर (get_user(ll, &vtsizes->v_rows) ||
		    get_user(cc, &vtsizes->v_cols))
			वापस -EFAULT;

		console_lock();
		क्रम (i = 0; i < MAX_NR_CONSOLES; i++) अणु
			vc = vc_cons[i].d;

			अगर (vc) अणु
				vc->vc_resize_user = 1;
				/* FIXME: review v tty lock */
				vc_resize(vc_cons[i].d, cc, ll);
			पूर्ण
		पूर्ण
		console_unlock();
		अवरोध;
	पूर्ण

	हाल VT_RESIZEX:
		अगर (!perm)
			वापस -EPERM;

		वापस vt_resizex(vc, up);

	हाल VT_LOCKSWITCH:
		अगर (!capable(CAP_SYS_TTY_CONFIG))
			वापस -EPERM;
		vt_करोnt_चयन = true;
		अवरोध;
	हाल VT_UNLOCKSWITCH:
		अगर (!capable(CAP_SYS_TTY_CONFIG))
			वापस -EPERM;
		vt_करोnt_चयन = false;
		अवरोध;
	हाल VT_GETHIFONTMASK:
		वापस put_user(vc->vc_hi_font_mask,
					(अचिन्हित लघु __user *)arg);
	हाल VT_WAITEVENT:
		वापस vt_event_रुको_ioctl((काष्ठा vt_event __user *)arg);
	शेष:
		वापस -ENOIOCTLCMD;
	पूर्ण

	वापस 0;
पूर्ण

व्योम reset_vc(काष्ठा vc_data *vc)
अणु
	vc->vc_mode = KD_TEXT;
	vt_reset_unicode(vc->vc_num);
	vc->vt_mode.mode = VT_AUTO;
	vc->vt_mode.रुकोv = 0;
	vc->vt_mode.relsig = 0;
	vc->vt_mode.acqsig = 0;
	vc->vt_mode.frsig = 0;
	put_pid(vc->vt_pid);
	vc->vt_pid = शून्य;
	vc->vt_newvt = -1;
	reset_palette(vc);
पूर्ण

व्योम vc_SAK(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा vc *vc_con =
		container_of(work, काष्ठा vc, SAK_work);
	काष्ठा vc_data *vc;
	काष्ठा tty_काष्ठा *tty;

	console_lock();
	vc = vc_con->d;
	अगर (vc) अणु
		/* FIXME: review tty ref counting */
		tty = vc->port.tty;
		/*
		 * SAK should also work in all raw modes and reset
		 * them properly.
		 */
		अगर (tty)
			__करो_SAK(tty);
		reset_vc(vc);
	पूर्ण
	console_unlock();
पूर्ण

#अगर_घोषित CONFIG_COMPAT

काष्ठा compat_console_font_op अणु
	compat_uपूर्णांक_t op;        /* operation code KD_FONT_OP_* */
	compat_uपूर्णांक_t flags;     /* KD_FONT_FLAG_* */
	compat_uपूर्णांक_t width, height;     /* font size */
	compat_uपूर्णांक_t अक्षरcount;
	compat_caddr_t data;    /* font data with height fixed to 32 */
पूर्ण;

अटल अंतरभूत पूर्णांक
compat_kdfontop_ioctl(काष्ठा compat_console_font_op __user *fontop,
			 पूर्णांक perm, काष्ठा console_font_op *op, काष्ठा vc_data *vc)
अणु
	पूर्णांक i;

	अगर (copy_from_user(op, fontop, माप(काष्ठा compat_console_font_op)))
		वापस -EFAULT;
	अगर (!perm && op->op != KD_FONT_OP_GET)
		वापस -EPERM;
	op->data = compat_ptr(((काष्ठा compat_console_font_op *)op)->data);
	i = con_font_op(vc, op);
	अगर (i)
		वापस i;
	((काष्ठा compat_console_font_op *)op)->data = (अचिन्हित दीर्घ)op->data;
	अगर (copy_to_user(fontop, op, माप(काष्ठा compat_console_font_op)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

काष्ठा compat_unimapdesc अणु
	अचिन्हित लघु entry_ct;
	compat_caddr_t entries;
पूर्ण;

अटल अंतरभूत पूर्णांक
compat_unimap_ioctl(अचिन्हित पूर्णांक cmd, काष्ठा compat_unimapdesc __user *user_ud,
			 पूर्णांक perm, काष्ठा vc_data *vc)
अणु
	काष्ठा compat_unimapdesc पंचांगp;
	काष्ठा unipair __user *पंचांगp_entries;

	अगर (copy_from_user(&पंचांगp, user_ud, माप पंचांगp))
		वापस -EFAULT;
	पंचांगp_entries = compat_ptr(पंचांगp.entries);
	चयन (cmd) अणु
	हाल PIO_UNIMAP:
		अगर (!perm)
			वापस -EPERM;
		वापस con_set_unimap(vc, पंचांगp.entry_ct, पंचांगp_entries);
	हाल GIO_UNIMAP:
		अगर (!perm && fg_console != vc->vc_num)
			वापस -EPERM;
		वापस con_get_unimap(vc, पंचांगp.entry_ct, &(user_ud->entry_ct), पंचांगp_entries);
	पूर्ण
	वापस 0;
पूर्ण

दीर्घ vt_compat_ioctl(काष्ठा tty_काष्ठा *tty,
	     अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा vc_data *vc = tty->driver_data;
	काष्ठा console_font_op op;	/* used in multiple places here */
	व्योम __user *up = compat_ptr(arg);
	पूर्णांक perm;

	/*
	 * To have permissions to करो most of the vt ioctls, we either have
	 * to be the owner of the tty, or have CAP_SYS_TTY_CONFIG.
	 */
	perm = 0;
	अगर (current->संकेत->tty == tty || capable(CAP_SYS_TTY_CONFIG))
		perm = 1;

	चयन (cmd) अणु
	/*
	 * these need special handlers क्रम incompatible data काष्ठाures
	 */

	हाल KDFONTOP:
		वापस compat_kdfontop_ioctl(up, perm, &op, vc);

	हाल PIO_UNIMAP:
	हाल GIO_UNIMAP:
		वापस compat_unimap_ioctl(cmd, up, perm, vc);

	/*
	 * all these treat 'arg' as an पूर्णांकeger
	 */
	हाल KIOCSOUND:
	हाल KDMKTONE:
#अगर_घोषित CONFIG_X86
	हाल KDADDIO:
	हाल KDDELIO:
#पूर्ण_अगर
	हाल KDSETMODE:
	हाल KDMAPDISP:
	हाल KDUNMAPDISP:
	हाल KDSKBMODE:
	हाल KDSKBMETA:
	हाल KDSKBLED:
	हाल KDSETLED:
	हाल KDSIGACCEPT:
	हाल VT_ACTIVATE:
	हाल VT_WAITACTIVE:
	हाल VT_RELDISP:
	हाल VT_DISALLOCATE:
	हाल VT_RESIZE:
	हाल VT_RESIZEX:
		वापस vt_ioctl(tty, cmd, arg);

	/*
	 * the rest has a compatible data काष्ठाure behind arg,
	 * but we have to convert it to a proper 64 bit poपूर्णांकer.
	 */
	शेष:
		वापस vt_ioctl(tty, cmd, (अचिन्हित दीर्घ)up);
	पूर्ण
पूर्ण


#पूर्ण_अगर /* CONFIG_COMPAT */


/*
 * Perक्रमms the back end of a vt चयन. Called under the console
 * semaphore.
 */
अटल व्योम complete_change_console(काष्ठा vc_data *vc)
अणु
	अचिन्हित अक्षर old_vc_mode;
	पूर्णांक old = fg_console;

	last_console = fg_console;

	/*
	 * If we're चयनing, we could be going from KD_GRAPHICS to
	 * KD_TEXT mode or vice versa, which means we need to blank or
	 * unblank the screen later.
	 */
	old_vc_mode = vc_cons[fg_console].d->vc_mode;
	चयन_screen(vc);

	/*
	 * This can't appear below a successful समाप्त_pid().  If it did,
	 * then the *blank_screen operation could occur जबतक X, having
	 * received acqsig, is waking up on another processor.  This
	 * condition can lead to overlapping accesses to the VGA range
	 * and the framebuffer (causing प्रणाली lockups).
	 *
	 * To account क्रम this we duplicate this code below only अगर the
	 * controlling process is gone and we've called reset_vc.
	 */
	अगर (old_vc_mode != vc->vc_mode) अणु
		अगर (vc->vc_mode == KD_TEXT)
			करो_unblank_screen(1);
		अन्यथा
			करो_blank_screen(1);
	पूर्ण

	/*
	 * If this new console is under process control, send it a संकेत
	 * telling it that it has acquired. Also check अगर it has died and
	 * clean up (similar to logic employed in change_console())
	 */
	अगर (vc->vt_mode.mode == VT_PROCESS) अणु
		/*
		 * Send the संकेत as privileged - समाप्त_pid() will
		 * tell us अगर the process has gone or something अन्यथा
		 * is awry
		 */
		अगर (समाप्त_pid(vc->vt_pid, vc->vt_mode.acqsig, 1) != 0) अणु
		/*
		 * The controlling process has died, so we revert back to
		 * normal operation. In this हाल, we'll also change back
		 * to KD_TEXT mode. I'm not sure अगर this is strictly correct
		 * but it saves the agony when the X server dies and the screen
		 * reमुख्यs blanked due to KD_GRAPHICS! It would be nice to करो
		 * this outside of VT_PROCESS but there is no single process
		 * to account क्रम and tracking tty count may be undesirable.
		 */
			reset_vc(vc);

			अगर (old_vc_mode != vc->vc_mode) अणु
				अगर (vc->vc_mode == KD_TEXT)
					करो_unblank_screen(1);
				अन्यथा
					करो_blank_screen(1);
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * Wake anyone रुकोing क्रम their VT to activate
	 */
	vt_event_post(VT_EVENT_SWITCH, old, vc->vc_num);
	वापस;
पूर्ण

/*
 * Perक्रमms the front-end of a vt चयन
 */
व्योम change_console(काष्ठा vc_data *new_vc)
अणु
	काष्ठा vc_data *vc;

	अगर (!new_vc || new_vc->vc_num == fg_console || vt_करोnt_चयन)
		वापस;

	/*
	 * If this vt is in process mode, then we need to handshake with
	 * that process beक्रमe चयनing. Essentially, we store where that
	 * vt wants to चयन to and रुको क्रम it to tell us when it's करोne
	 * (via VT_RELDISP ioctl).
	 *
	 * We also check to see अगर the controlling process still exists.
	 * If it करोesn't, we reset this vt to स्वतः mode and जारी.
	 * This is a cheap way to track process control. The worst thing
	 * that can happen is: we send a संकेत to a process, it dies, and
	 * the चयन माला_लो "lost" रुकोing क्रम a response; hopefully, the
	 * user will try again, we'll detect the process is gone (unless
	 * the user रुकोs just the right amount of समय :-) and revert the
	 * vt to स्वतः control.
	 */
	vc = vc_cons[fg_console].d;
	अगर (vc->vt_mode.mode == VT_PROCESS) अणु
		/*
		 * Send the संकेत as privileged - समाप्त_pid() will
		 * tell us अगर the process has gone or something अन्यथा
		 * is awry.
		 *
		 * We need to set vt_newvt *beक्रमe* sending the संकेत or we
		 * have a race.
		 */
		vc->vt_newvt = new_vc->vc_num;
		अगर (समाप्त_pid(vc->vt_pid, vc->vt_mode.relsig, 1) == 0) अणु
			/*
			 * It worked. Mark the vt to चयन to and
			 * वापस. The process needs to send us a
			 * VT_RELDISP ioctl to complete the चयन.
			 */
			वापस;
		पूर्ण

		/*
		 * The controlling process has died, so we revert back to
		 * normal operation. In this हाल, we'll also change back
		 * to KD_TEXT mode. I'm not sure अगर this is strictly correct
		 * but it saves the agony when the X server dies and the screen
		 * reमुख्यs blanked due to KD_GRAPHICS! It would be nice to करो
		 * this outside of VT_PROCESS but there is no single process
		 * to account क्रम and tracking tty count may be undesirable.
		 */
		reset_vc(vc);

		/*
		 * Fall through to normal (VT_AUTO) handling of the चयन...
		 */
	पूर्ण

	/*
	 * Ignore all चयनes in KD_GRAPHICS+VT_AUTO mode
	 */
	अगर (vc->vc_mode == KD_GRAPHICS)
		वापस;

	complete_change_console(new_vc);
पूर्ण

/* Perक्रमm a kernel triggered VT चयन क्रम suspend/resume */

अटल पूर्णांक disable_vt_चयन;

पूर्णांक vt_move_to_console(अचिन्हित पूर्णांक vt, पूर्णांक alloc)
अणु
	पूर्णांक prev;

	console_lock();
	/* Graphics mode - up to X */
	अगर (disable_vt_चयन) अणु
		console_unlock();
		वापस 0;
	पूर्ण
	prev = fg_console;

	अगर (alloc && vc_allocate(vt)) अणु
		/* we can't have a मुक्त VC क्रम now. Too bad,
		 * we करोn't want to mess the screen क्रम now. */
		console_unlock();
		वापस -ENOSPC;
	पूर्ण

	अगर (set_console(vt)) अणु
		/*
		 * We're unable to चयन to the SUSPEND_CONSOLE.
		 * Let the calling function know so it can decide
		 * what to करो.
		 */
		console_unlock();
		वापस -EIO;
	पूर्ण
	console_unlock();
	अगर (vt_रुकोactive(vt + 1)) अणु
		pr_debug("Suspend: Can't switch VCs.");
		वापस -EINTR;
	पूर्ण
	वापस prev;
पूर्ण

/*
 * Normally during a suspend, we allocate a new console and चयन to it.
 * When we resume, we चयन back to the original console.  This चयन
 * can be slow, so on प्रणालीs where the framebuffer can handle restoration
 * of video रेजिस्टरs anyways, there's little poपूर्णांक in करोing the console
 * चयन.  This function allows you to disable it by passing it '0'.
 */
व्योम pm_set_vt_चयन(पूर्णांक करो_चयन)
अणु
	console_lock();
	disable_vt_चयन = !करो_चयन;
	console_unlock();
पूर्ण
EXPORT_SYMBOL(pm_set_vt_चयन);
