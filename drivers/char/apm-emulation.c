<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * bios-less APM driver क्रम ARM Linux
 *  Jamey Hicks <jamey@crl.dec.com>
 *  adapted from the APM BIOS driver क्रम Linux by Stephen Rothwell (sfr@linuxcare.com)
 *
 * APM 1.2 Reference:
 *   Intel Corporation, Microsoft Corporation. Advanced Power Management
 *   (APM) BIOS Interface Specअगरication, Revision 1.2, February 1996.
 *
 * This करोcument is available from Microsoft at:
 *    http://www.microsoft.com/whdc/archive/amp_12.mspx
 */
#समावेश <linux/module.h>
#समावेश <linux/poll.h>
#समावेश <linux/slab.h>
#समावेश <linux/mutex.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/apm_मूलप्रण.स>
#समावेश <linux/capability.h>
#समावेश <linux/sched.h>
#समावेश <linux/suspend.h>
#समावेश <linux/apm-emulation.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/init.h>
#समावेश <linux/completion.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/delay.h>

/*
 * One option can be changed at boot समय as follows:
 *	apm=on/off			enable/disable APM
 */

/*
 * Maximum number of events stored
 */
#घोषणा APM_MAX_EVENTS		16

काष्ठा apm_queue अणु
	अचिन्हित पूर्णांक		event_head;
	अचिन्हित पूर्णांक		event_tail;
	apm_event_t		events[APM_MAX_EVENTS];
पूर्ण;

/*
 * thपढ़ो states (क्रम thपढ़ोs using a writable /dev/apm_bios fd):
 *
 * SUSPEND_NONE:	nothing happening
 * SUSPEND_PENDING:	suspend event queued क्रम thपढ़ो and pending to be पढ़ो
 * SUSPEND_READ:	suspend event पढ़ो, pending acknowledgement
 * SUSPEND_ACKED:	acknowledgement received from thपढ़ो (via ioctl),
 *			रुकोing क्रम resume
 * SUSPEND_ACKTO:	acknowledgement समयout
 * SUSPEND_DONE:	thपढ़ो had acked suspend and is now notअगरied of
 *			resume
 *
 * SUSPEND_WAIT:	this thपढ़ो invoked suspend and is रुकोing क्रम resume
 *
 * A thपढ़ो migrates in one of three paths:
 *	NONE -1-> PENDING -2-> READ -3-> ACKED -4-> DONE -5-> NONE
 *				    -6-> ACKTO -7-> NONE
 *	NONE -8-> WAIT -9-> NONE
 *
 * While in PENDING or READ, the thपढ़ो is accounted क्रम in the
 * suspend_acks_pending counter.
 *
 * The transitions are invoked as follows:
 *	1: suspend event is संकेतled from the core PM code
 *	2: the suspend event is पढ़ो from the fd by the userspace thपढ़ो
 *	3: userspace thपढ़ो issues the APM_IOC_SUSPEND ioctl (as ack)
 *	4: core PM code संकेतs that we have resumed
 *	5: APM_IOC_SUSPEND ioctl वापसs
 *
 *	6: the notअगरier invoked from the core PM code समयd out रुकोing
 *	   क्रम all relevant threds to enter ACKED state and माला_दो those
 *	   that haven't पूर्णांकo ACKTO
 *	7: those thपढ़ोs issue APM_IOC_SUSPEND ioctl too late,
 *	   get an error
 *
 *	8: userspace thपढ़ो issues the APM_IOC_SUSPEND ioctl (to suspend),
 *	   ioctl code invokes pm_suspend()
 *	9: pm_suspend() वापसs indicating resume
 */
क्रमागत apm_suspend_state अणु
	SUSPEND_NONE,
	SUSPEND_PENDING,
	SUSPEND_READ,
	SUSPEND_ACKED,
	SUSPEND_ACKTO,
	SUSPEND_WAIT,
	SUSPEND_DONE,
पूर्ण;

/*
 * The per-file APM data
 */
काष्ठा apm_user अणु
	काष्ठा list_head	list;

	अचिन्हित पूर्णांक		suser: 1;
	अचिन्हित पूर्णांक		ग_लिखोr: 1;
	अचिन्हित पूर्णांक		पढ़ोer: 1;

	पूर्णांक			suspend_result;
	क्रमागत apm_suspend_state	suspend_state;

	काष्ठा apm_queue	queue;
पूर्ण;

/*
 * Local variables
 */
अटल atomic_t suspend_acks_pending = ATOMIC_INIT(0);
अटल atomic_t userspace_notअगरication_inhibit = ATOMIC_INIT(0);
अटल पूर्णांक apm_disabled;
अटल काष्ठा task_काष्ठा *kapmd_tsk;

अटल DECLARE_WAIT_QUEUE_HEAD(apm_रुकोqueue);
अटल DECLARE_WAIT_QUEUE_HEAD(apm_suspend_रुकोqueue);

/*
 * This is a list of everyone who has खोलोed /dev/apm_bios
 */
अटल DECLARE_RWSEM(user_list_lock);
अटल LIST_HEAD(apm_user_list);

/*
 * kapmd info.  kapmd provides us a process context to handle
 * "APM" events within - specअगरically necessary अगर we're going
 * to be suspending the प्रणाली.
 */
अटल DECLARE_WAIT_QUEUE_HEAD(kapmd_रुको);
अटल DEFINE_SPINLOCK(kapmd_queue_lock);
अटल काष्ठा apm_queue kapmd_queue;

अटल DEFINE_MUTEX(state_lock);

अटल स्थिर अक्षर driver_version[] = "1.13";	/* no spaces */



/*
 * Compatibility cruft until the IPAQ people move over to the new
 * पूर्णांकerface.
 */
अटल व्योम __apm_get_घातer_status(काष्ठा apm_घातer_info *info)
अणु
पूर्ण

/*
 * This allows machines to provide their own "apm get power status" function.
 */
व्योम (*apm_get_घातer_status)(काष्ठा apm_घातer_info *) = __apm_get_घातer_status;
EXPORT_SYMBOL(apm_get_घातer_status);


/*
 * APM event queue management.
 */
अटल अंतरभूत पूर्णांक queue_empty(काष्ठा apm_queue *q)
अणु
	वापस q->event_head == q->event_tail;
पूर्ण

अटल अंतरभूत apm_event_t queue_get_event(काष्ठा apm_queue *q)
अणु
	q->event_tail = (q->event_tail + 1) % APM_MAX_EVENTS;
	वापस q->events[q->event_tail];
पूर्ण

अटल व्योम queue_add_event(काष्ठा apm_queue *q, apm_event_t event)
अणु
	q->event_head = (q->event_head + 1) % APM_MAX_EVENTS;
	अगर (q->event_head == q->event_tail) अणु
		अटल पूर्णांक notअगरied;

		अगर (notअगरied++ == 0)
		    prपूर्णांकk(KERN_ERR "apm: an event queue overflowed\n");
		q->event_tail = (q->event_tail + 1) % APM_MAX_EVENTS;
	पूर्ण
	q->events[q->event_head] = event;
पूर्ण

अटल व्योम queue_event(apm_event_t event)
अणु
	काष्ठा apm_user *as;

	करोwn_पढ़ो(&user_list_lock);
	list_क्रम_each_entry(as, &apm_user_list, list) अणु
		अगर (as->पढ़ोer)
			queue_add_event(&as->queue, event);
	पूर्ण
	up_पढ़ो(&user_list_lock);
	wake_up_पूर्णांकerruptible(&apm_रुकोqueue);
पूर्ण

अटल sमाप_प्रकार apm_पढ़ो(काष्ठा file *fp, अक्षर __user *buf, माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा apm_user *as = fp->निजी_data;
	apm_event_t event;
	पूर्णांक i = count, ret = 0;

	अगर (count < माप(apm_event_t))
		वापस -EINVAL;

	अगर (queue_empty(&as->queue) && fp->f_flags & O_NONBLOCK)
		वापस -EAGAIN;

	रुको_event_पूर्णांकerruptible(apm_रुकोqueue, !queue_empty(&as->queue));

	जबतक ((i >= माप(event)) && !queue_empty(&as->queue)) अणु
		event = queue_get_event(&as->queue);

		ret = -EFAULT;
		अगर (copy_to_user(buf, &event, माप(event)))
			अवरोध;

		mutex_lock(&state_lock);
		अगर (as->suspend_state == SUSPEND_PENDING &&
		    (event == APM_SYS_SUSPEND || event == APM_USER_SUSPEND))
			as->suspend_state = SUSPEND_READ;
		mutex_unlock(&state_lock);

		buf += माप(event);
		i -= माप(event);
	पूर्ण

	अगर (i < count)
		ret = count - i;

	वापस ret;
पूर्ण

अटल __poll_t apm_poll(काष्ठा file *fp, poll_table * रुको)
अणु
	काष्ठा apm_user *as = fp->निजी_data;

	poll_रुको(fp, &apm_रुकोqueue, रुको);
	वापस queue_empty(&as->queue) ? 0 : EPOLLIN | EPOLLRDNORM;
पूर्ण

/*
 * apm_ioctl - handle APM ioctl
 *
 * APM_IOC_SUSPEND
 *   This IOCTL is overloaded, and perक्रमms two functions.  It is used to:
 *     - initiate a suspend
 *     - acknowledge a suspend पढ़ो from /dev/apm_bios.
 *   Only when everyone who has खोलोed /dev/apm_bios with ग_लिखो permission
 *   has acknowledge करोes the actual suspend happen.
 */
अटल दीर्घ
apm_ioctl(काष्ठा file *filp, u_पूर्णांक cmd, u_दीर्घ arg)
अणु
	काष्ठा apm_user *as = filp->निजी_data;
	पूर्णांक err = -EINVAL;

	अगर (!as->suser || !as->ग_लिखोr)
		वापस -EPERM;

	चयन (cmd) अणु
	हाल APM_IOC_SUSPEND:
		mutex_lock(&state_lock);

		as->suspend_result = -EINTR;

		चयन (as->suspend_state) अणु
		हाल SUSPEND_READ:
			/*
			 * If we पढ़ो a suspend command from /dev/apm_bios,
			 * then the corresponding APM_IOC_SUSPEND ioctl is
			 * पूर्णांकerpreted as an acknowledge.
			 */
			as->suspend_state = SUSPEND_ACKED;
			atomic_dec(&suspend_acks_pending);
			mutex_unlock(&state_lock);

			/*
			 * suspend_acks_pending changed, the notअगरier needs to
			 * be woken up क्रम this
			 */
			wake_up(&apm_suspend_रुकोqueue);

			/*
			 * Wait क्रम the suspend/resume to complete.  If there
			 * are pending acknowledges, we रुको here क्रम them.
			 * रुको_event_मुक्तzable() is पूर्णांकerruptible and pending
			 * संकेत can cause busy looping.  We aren't करोing
			 * anything critical, chill a bit on each iteration.
			 */
			जबतक (रुको_event_मुक्तzable(apm_suspend_रुकोqueue,
					as->suspend_state != SUSPEND_ACKED))
				msleep(10);
			अवरोध;
		हाल SUSPEND_ACKTO:
			as->suspend_result = -ETIMEDOUT;
			mutex_unlock(&state_lock);
			अवरोध;
		शेष:
			as->suspend_state = SUSPEND_WAIT;
			mutex_unlock(&state_lock);

			/*
			 * Otherwise it is a request to suspend the प्रणाली.
			 * Just invoke pm_suspend(), we'll handle it from
			 * there via the notअगरier.
			 */
			as->suspend_result = pm_suspend(PM_SUSPEND_MEM);
		पूर्ण

		mutex_lock(&state_lock);
		err = as->suspend_result;
		as->suspend_state = SUSPEND_NONE;
		mutex_unlock(&state_lock);
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक apm_release(काष्ठा inode * inode, काष्ठा file * filp)
अणु
	काष्ठा apm_user *as = filp->निजी_data;

	filp->निजी_data = शून्य;

	करोwn_ग_लिखो(&user_list_lock);
	list_del(&as->list);
	up_ग_लिखो(&user_list_lock);

	/*
	 * We are now unhooked from the chain.  As far as new
	 * events are concerned, we no दीर्घer exist.
	 */
	mutex_lock(&state_lock);
	अगर (as->suspend_state == SUSPEND_PENDING ||
	    as->suspend_state == SUSPEND_READ)
		atomic_dec(&suspend_acks_pending);
	mutex_unlock(&state_lock);

	wake_up(&apm_suspend_रुकोqueue);

	kमुक्त(as);
	वापस 0;
पूर्ण

अटल पूर्णांक apm_खोलो(काष्ठा inode * inode, काष्ठा file * filp)
अणु
	काष्ठा apm_user *as;

	as = kzalloc(माप(*as), GFP_KERNEL);
	अगर (as) अणु
		/*
		 * XXX - this is a tiny bit broken, when we consider BSD
		 * process accounting. If the device is खोलोed by root, we
		 * instantly flag that we used superuser privs. Who knows,
		 * we might बंद the device immediately without करोing a
		 * privileged operation -- cevans
		 */
		as->suser = capable(CAP_SYS_ADMIN);
		as->ग_लिखोr = (filp->f_mode & FMODE_WRITE) == FMODE_WRITE;
		as->पढ़ोer = (filp->f_mode & FMODE_READ) == FMODE_READ;

		करोwn_ग_लिखो(&user_list_lock);
		list_add(&as->list, &apm_user_list);
		up_ग_लिखो(&user_list_lock);

		filp->निजी_data = as;
	पूर्ण

	वापस as ? 0 : -ENOMEM;
पूर्ण

अटल स्थिर काष्ठा file_operations apm_bios_fops = अणु
	.owner		= THIS_MODULE,
	.पढ़ो		= apm_पढ़ो,
	.poll		= apm_poll,
	.unlocked_ioctl	= apm_ioctl,
	.खोलो		= apm_खोलो,
	.release	= apm_release,
	.llseek		= noop_llseek,
पूर्ण;

अटल काष्ठा miscdevice apm_device = अणु
	.minor		= APM_MINOR_DEV,
	.name		= "apm_bios",
	.fops		= &apm_bios_fops
पूर्ण;


#अगर_घोषित CONFIG_PROC_FS
/*
 * Arguments, with symbols from linux/apm_मूलप्रण.स.
 *
 *   0) Linux driver version (this will change अगर क्रमmat changes)
 *   1) APM BIOS Version.  Usually 1.0, 1.1 or 1.2.
 *   2) APM flags from APM Installation Check (0x00):
 *	bit 0: APM_16_BIT_SUPPORT
 *	bit 1: APM_32_BIT_SUPPORT
 *	bit 2: APM_IDLE_SLOWS_CLOCK
 *	bit 3: APM_BIOS_DISABLED
 *	bit 4: APM_BIOS_DISENGAGED
 *   3) AC line status
 *	0x00: Off-line
 *	0x01: On-line
 *	0x02: On backup घातer (BIOS >= 1.1 only)
 *	0xff: Unknown
 *   4) Battery status
 *	0x00: High
 *	0x01: Low
 *	0x02: Critical
 *	0x03: Charging
 *	0x04: Selected battery not present (BIOS >= 1.2 only)
 *	0xff: Unknown
 *   5) Battery flag
 *	bit 0: High
 *	bit 1: Low
 *	bit 2: Critical
 *	bit 3: Charging
 *	bit 7: No प्रणाली battery
 *	0xff: Unknown
 *   6) Reमुख्यing battery lअगरe (percentage of अक्षरge):
 *	0-100: valid
 *	-1: Unknown
 *   7) Reमुख्यing battery lअगरe (समय units):
 *	Number of reमुख्यing minutes or seconds
 *	-1: Unknown
 *   8) min = minutes; sec = seconds
 */
अटल पूर्णांक proc_apm_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा apm_घातer_info info;
	अक्षर *units;

	info.ac_line_status = 0xff;
	info.battery_status = 0xff;
	info.battery_flag   = 0xff;
	info.battery_lअगरe   = -1;
	info.समय	    = -1;
	info.units	    = -1;

	अगर (apm_get_घातer_status)
		apm_get_घातer_status(&info);

	चयन (info.units) अणु
	शेष:	units = "?";	अवरोध;
	हाल 0: 	units = "min";	अवरोध;
	हाल 1: 	units = "sec";	अवरोध;
	पूर्ण

	seq_म_लिखो(m, "%s 1.2 0x%02x 0x%02x 0x%02x 0x%02x %d%% %d %s\n",
		     driver_version, APM_32_BIT_SUPPORT,
		     info.ac_line_status, info.battery_status,
		     info.battery_flag, info.battery_lअगरe,
		     info.समय, units);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक kapmd(व्योम *arg)
अणु
	करो अणु
		apm_event_t event;

		रुको_event_पूर्णांकerruptible(kapmd_रुको,
				!queue_empty(&kapmd_queue) || kthपढ़ो_should_stop());

		अगर (kthपढ़ो_should_stop())
			अवरोध;

		spin_lock_irq(&kapmd_queue_lock);
		event = 0;
		अगर (!queue_empty(&kapmd_queue))
			event = queue_get_event(&kapmd_queue);
		spin_unlock_irq(&kapmd_queue_lock);

		चयन (event) अणु
		हाल 0:
			अवरोध;

		हाल APM_LOW_BATTERY:
		हाल APM_POWER_STATUS_CHANGE:
			queue_event(event);
			अवरोध;

		हाल APM_USER_SUSPEND:
		हाल APM_SYS_SUSPEND:
			pm_suspend(PM_SUSPEND_MEM);
			अवरोध;

		हाल APM_CRITICAL_SUSPEND:
			atomic_inc(&userspace_notअगरication_inhibit);
			pm_suspend(PM_SUSPEND_MEM);
			atomic_dec(&userspace_notअगरication_inhibit);
			अवरोध;
		पूर्ण
	पूर्ण जबतक (1);

	वापस 0;
पूर्ण

अटल पूर्णांक apm_suspend_notअगरier(काष्ठा notअगरier_block *nb,
				अचिन्हित दीर्घ event,
				व्योम *dummy)
अणु
	काष्ठा apm_user *as;
	पूर्णांक err;
	अचिन्हित दीर्घ apm_event;

	/* लघु-cut emergency suspends */
	अगर (atomic_पढ़ो(&userspace_notअगरication_inhibit))
		वापस NOTIFY_DONE;

	चयन (event) अणु
	हाल PM_SUSPEND_PREPARE:
	हाल PM_HIBERNATION_PREPARE:
		apm_event = (event == PM_SUSPEND_PREPARE) ?
			APM_USER_SUSPEND : APM_USER_HIBERNATION;
		/*
		 * Queue an event to all "writer" users that we want
		 * to suspend and need their ack.
		 */
		mutex_lock(&state_lock);
		करोwn_पढ़ो(&user_list_lock);

		list_क्रम_each_entry(as, &apm_user_list, list) अणु
			अगर (as->suspend_state != SUSPEND_WAIT && as->पढ़ोer &&
			    as->ग_लिखोr && as->suser) अणु
				as->suspend_state = SUSPEND_PENDING;
				atomic_inc(&suspend_acks_pending);
				queue_add_event(&as->queue, apm_event);
			पूर्ण
		पूर्ण

		up_पढ़ो(&user_list_lock);
		mutex_unlock(&state_lock);
		wake_up_पूर्णांकerruptible(&apm_रुकोqueue);

		/*
		 * Wait क्रम the the suspend_acks_pending variable to drop to
		 * zero, meaning everybody acked the suspend event (or the
		 * process was समाप्तed.)
		 *
		 * If the app won't answer within a लघु जबतक we assume it
		 * locked up and ignore it.
		 */
		err = रुको_event_पूर्णांकerruptible_समयout(
			apm_suspend_रुकोqueue,
			atomic_पढ़ो(&suspend_acks_pending) == 0,
			5*HZ);

		/* समयd out */
		अगर (err == 0) अणु
			/*
			 * Move anybody who समयd out to "ack timeout" state.
			 *
			 * We could समय out and the userspace करोes the ACK
			 * right after we समय out but beक्रमe we enter the
			 * locked section here, but that's fine.
			 */
			mutex_lock(&state_lock);
			करोwn_पढ़ो(&user_list_lock);
			list_क्रम_each_entry(as, &apm_user_list, list) अणु
				अगर (as->suspend_state == SUSPEND_PENDING ||
				    as->suspend_state == SUSPEND_READ) अणु
					as->suspend_state = SUSPEND_ACKTO;
					atomic_dec(&suspend_acks_pending);
				पूर्ण
			पूर्ण
			up_पढ़ो(&user_list_lock);
			mutex_unlock(&state_lock);
		पूर्ण

		/* let suspend proceed */
		अगर (err >= 0)
			वापस NOTIFY_OK;

		/* पूर्णांकerrupted by संकेत */
		वापस notअगरier_from_त्रुटि_सं(err);

	हाल PM_POST_SUSPEND:
	हाल PM_POST_HIBERNATION:
		apm_event = (event == PM_POST_SUSPEND) ?
			APM_NORMAL_RESUME : APM_HIBERNATION_RESUME;
		/*
		 * Anyone on the APM queues will think we're still suspended.
		 * Send a message so everyone knows we're now awake again.
		 */
		queue_event(apm_event);

		/*
		 * Finally, wake up anyone who is sleeping on the suspend.
		 */
		mutex_lock(&state_lock);
		करोwn_पढ़ो(&user_list_lock);
		list_क्रम_each_entry(as, &apm_user_list, list) अणु
			अगर (as->suspend_state == SUSPEND_ACKED) अणु
				/*
				 * TODO: maybe grab error code, needs core
				 * changes to push the error to the notअगरier
				 * chain (could use the second parameter अगर
				 * implemented)
				 */
				as->suspend_result = 0;
				as->suspend_state = SUSPEND_DONE;
			पूर्ण
		पूर्ण
		up_पढ़ो(&user_list_lock);
		mutex_unlock(&state_lock);

		wake_up(&apm_suspend_रुकोqueue);
		वापस NOTIFY_OK;

	शेष:
		वापस NOTIFY_DONE;
	पूर्ण
पूर्ण

अटल काष्ठा notअगरier_block apm_notअगर_block = अणु
	.notअगरier_call = apm_suspend_notअगरier,
पूर्ण;

अटल पूर्णांक __init apm_init(व्योम)
अणु
	पूर्णांक ret;

	अगर (apm_disabled) अणु
		prपूर्णांकk(KERN_NOTICE "apm: disabled on user request.\n");
		वापस -ENODEV;
	पूर्ण

	kapmd_tsk = kthपढ़ो_create(kapmd, शून्य, "kapmd");
	अगर (IS_ERR(kapmd_tsk)) अणु
		ret = PTR_ERR(kapmd_tsk);
		kapmd_tsk = शून्य;
		जाओ out;
	पूर्ण
	wake_up_process(kapmd_tsk);

#अगर_घोषित CONFIG_PROC_FS
	proc_create_single("apm", 0, शून्य, proc_apm_show);
#पूर्ण_अगर

	ret = misc_रेजिस्टर(&apm_device);
	अगर (ret)
		जाओ out_stop;

	ret = रेजिस्टर_pm_notअगरier(&apm_notअगर_block);
	अगर (ret)
		जाओ out_unरेजिस्टर;

	वापस 0;

 out_unरेजिस्टर:
	misc_deरेजिस्टर(&apm_device);
 out_stop:
	हटाओ_proc_entry("apm", शून्य);
	kthपढ़ो_stop(kapmd_tsk);
 out:
	वापस ret;
पूर्ण

अटल व्योम __निकास apm_निकास(व्योम)
अणु
	unरेजिस्टर_pm_notअगरier(&apm_notअगर_block);
	misc_deरेजिस्टर(&apm_device);
	हटाओ_proc_entry("apm", शून्य);

	kthपढ़ो_stop(kapmd_tsk);
पूर्ण

module_init(apm_init);
module_निकास(apm_निकास);

MODULE_AUTHOR("Stephen Rothwell");
MODULE_DESCRIPTION("Advanced Power Management");
MODULE_LICENSE("GPL");

#अगर_अघोषित MODULE
अटल पूर्णांक __init apm_setup(अक्षर *str)
अणु
	जबतक ((str != शून्य) && (*str != '\0')) अणु
		अगर (म_भेदन(str, "off", 3) == 0)
			apm_disabled = 1;
		अगर (म_भेदन(str, "on", 2) == 0)
			apm_disabled = 0;
		str = म_अक्षर(str, ',');
		अगर (str != शून्य)
			str += म_अखोज(str, ", \t");
	पूर्ण
	वापस 1;
पूर्ण

__setup("apm=", apm_setup);
#पूर्ण_अगर

/**
 * apm_queue_event - queue an APM event क्रम kapmd
 * @event: APM event
 *
 * Queue an APM event क्रम kapmd to process and ultimately take the
 * appropriate action.  Only a subset of events are handled:
 *   %APM_LOW_BATTERY
 *   %APM_POWER_STATUS_CHANGE
 *   %APM_USER_SUSPEND
 *   %APM_SYS_SUSPEND
 *   %APM_CRITICAL_SUSPEND
 */
व्योम apm_queue_event(apm_event_t event)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&kapmd_queue_lock, flags);
	queue_add_event(&kapmd_queue, event);
	spin_unlock_irqrestore(&kapmd_queue_lock, flags);

	wake_up_पूर्णांकerruptible(&kapmd_रुको);
पूर्ण
EXPORT_SYMBOL(apm_queue_event);
