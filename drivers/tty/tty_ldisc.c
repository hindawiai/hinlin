<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kmod.h>
#समावेश <linux/sched.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_driver.h>
#समावेश <linux/file.h>
#समावेश <linux/mm.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/poll.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/रुको.h>
#समावेश <linux/bitops.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/ratelimit.h>
#समावेश "tty.h"

#अघोषित LDISC_DEBUG_HANGUP

#अगर_घोषित LDISC_DEBUG_HANGUP
#घोषणा tty_ldisc_debug(tty, f, args...)	tty_debug(tty, f, ##args)
#अन्यथा
#घोषणा tty_ldisc_debug(tty, f, args...)
#पूर्ण_अगर

/* lockdep nested classes क्रम tty->ldisc_sem */
क्रमागत अणु
	LDISC_SEM_NORMAL,
	LDISC_SEM_OTHER,
पूर्ण;


/*
 *	This guards the refcounted line discipline lists. The lock
 *	must be taken with irqs off because there are hangup path
 *	callers who will करो ldisc lookups and cannot sleep.
 */

अटल DEFINE_RAW_SPINLOCK(tty_ldiscs_lock);
/* Line disc dispatch table */
अटल काष्ठा tty_ldisc_ops *tty_ldiscs[NR_LDISCS];

/**
 *	tty_रेजिस्टर_ldisc	-	install a line discipline
 *	@disc: ldisc number
 *	@new_ldisc: poपूर्णांकer to the ldisc object
 *
 *	Installs a new line discipline पूर्णांकo the kernel. The discipline
 *	is set up as unreferenced and then made available to the kernel
 *	from this poपूर्णांक onwards.
 *
 *	Locking:
 *		takes tty_ldiscs_lock to guard against ldisc races
 */

पूर्णांक tty_रेजिस्टर_ldisc(पूर्णांक disc, काष्ठा tty_ldisc_ops *new_ldisc)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	अगर (disc < N_TTY || disc >= NR_LDISCS)
		वापस -EINVAL;

	raw_spin_lock_irqsave(&tty_ldiscs_lock, flags);
	tty_ldiscs[disc] = new_ldisc;
	new_ldisc->num = disc;
	new_ldisc->refcount = 0;
	raw_spin_unlock_irqrestore(&tty_ldiscs_lock, flags);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(tty_रेजिस्टर_ldisc);

/**
 *	tty_unरेजिस्टर_ldisc	-	unload a line discipline
 *	@disc: ldisc number
 *
 *	Remove a line discipline from the kernel providing it is not
 *	currently in use.
 *
 *	Locking:
 *		takes tty_ldiscs_lock to guard against ldisc races
 */

पूर्णांक tty_unरेजिस्टर_ldisc(पूर्णांक disc)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	अगर (disc < N_TTY || disc >= NR_LDISCS)
		वापस -EINVAL;

	raw_spin_lock_irqsave(&tty_ldiscs_lock, flags);
	अगर (tty_ldiscs[disc]->refcount)
		ret = -EBUSY;
	अन्यथा
		tty_ldiscs[disc] = शून्य;
	raw_spin_unlock_irqrestore(&tty_ldiscs_lock, flags);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(tty_unरेजिस्टर_ldisc);

अटल काष्ठा tty_ldisc_ops *get_lकरोps(पूर्णांक disc)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा tty_ldisc_ops *lकरोps, *ret;

	raw_spin_lock_irqsave(&tty_ldiscs_lock, flags);
	ret = ERR_PTR(-EINVAL);
	lकरोps = tty_ldiscs[disc];
	अगर (lकरोps) अणु
		ret = ERR_PTR(-EAGAIN);
		अगर (try_module_get(lकरोps->owner)) अणु
			lकरोps->refcount++;
			ret = lकरोps;
		पूर्ण
	पूर्ण
	raw_spin_unlock_irqrestore(&tty_ldiscs_lock, flags);
	वापस ret;
पूर्ण

अटल व्योम put_lकरोps(काष्ठा tty_ldisc_ops *lकरोps)
अणु
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&tty_ldiscs_lock, flags);
	lकरोps->refcount--;
	module_put(lकरोps->owner);
	raw_spin_unlock_irqrestore(&tty_ldiscs_lock, flags);
पूर्ण

अटल पूर्णांक tty_ldisc_स्वतःload = IS_BUILTIN(CONFIG_LDISC_AUTOLOAD);
/**
 *	tty_ldisc_get		-	take a reference to an ldisc
 *	@tty: tty device
 *	@disc: ldisc number
 *
 *	Takes a reference to a line discipline. Deals with refcounts and
 *	module locking counts.
 *
 *	Returns: -EINVAL अगर the discipline index is not [N_TTY..NR_LDISCS] or
 *			 अगर the discipline is not रेजिस्टरed
 *		 -EAGAIN अगर request_module() failed to load or रेजिस्टर the
 *			 discipline
 *		 -ENOMEM अगर allocation failure
 *
 *		 Otherwise, वापसs a poपूर्णांकer to the discipline and bumps the
 *		 ref count
 *
 *	Locking:
 *		takes tty_ldiscs_lock to guard against ldisc races
 */

अटल काष्ठा tty_ldisc *tty_ldisc_get(काष्ठा tty_काष्ठा *tty, पूर्णांक disc)
अणु
	काष्ठा tty_ldisc *ld;
	काष्ठा tty_ldisc_ops *lकरोps;

	अगर (disc < N_TTY || disc >= NR_LDISCS)
		वापस ERR_PTR(-EINVAL);

	/*
	 * Get the ldisc ops - we may need to request them to be loaded
	 * dynamically and try again.
	 */
	lकरोps = get_lकरोps(disc);
	अगर (IS_ERR(lकरोps)) अणु
		अगर (!capable(CAP_SYS_MODULE) && !tty_ldisc_स्वतःload)
			वापस ERR_PTR(-EPERM);
		request_module("tty-ldisc-%d", disc);
		lकरोps = get_lकरोps(disc);
		अगर (IS_ERR(lकरोps))
			वापस ERR_CAST(lकरोps);
	पूर्ण

	/*
	 * There is no way to handle allocation failure of only 16 bytes.
	 * Let's simplअगरy error handling and save more memory.
	 */
	ld = kदो_स्मृति(माप(काष्ठा tty_ldisc), GFP_KERNEL | __GFP_NOFAIL);
	ld->ops = lकरोps;
	ld->tty = tty;

	वापस ld;
पूर्ण

/*
 *	tty_ldisc_put		-	release the ldisc
 *
 *	Complement of tty_ldisc_get().
 */
अटल व्योम tty_ldisc_put(काष्ठा tty_ldisc *ld)
अणु
	अगर (WARN_ON_ONCE(!ld))
		वापस;

	put_lकरोps(ld->ops);
	kमुक्त(ld);
पूर्ण

अटल व्योम *tty_ldiscs_seq_start(काष्ठा seq_file *m, loff_t *pos)
अणु
	वापस (*pos < NR_LDISCS) ? pos : शून्य;
पूर्ण

अटल व्योम *tty_ldiscs_seq_next(काष्ठा seq_file *m, व्योम *v, loff_t *pos)
अणु
	(*pos)++;
	वापस (*pos < NR_LDISCS) ? pos : शून्य;
पूर्ण

अटल व्योम tty_ldiscs_seq_stop(काष्ठा seq_file *m, व्योम *v)
अणु
पूर्ण

अटल पूर्णांक tty_ldiscs_seq_show(काष्ठा seq_file *m, व्योम *v)
अणु
	पूर्णांक i = *(loff_t *)v;
	काष्ठा tty_ldisc_ops *lकरोps;

	lकरोps = get_lकरोps(i);
	अगर (IS_ERR(lकरोps))
		वापस 0;
	seq_म_लिखो(m, "%-10s %2d\n", lकरोps->name ? lकरोps->name : "???", i);
	put_lकरोps(lकरोps);
	वापस 0;
पूर्ण

स्थिर काष्ठा seq_operations tty_ldiscs_seq_ops = अणु
	.start	= tty_ldiscs_seq_start,
	.next	= tty_ldiscs_seq_next,
	.stop	= tty_ldiscs_seq_stop,
	.show	= tty_ldiscs_seq_show,
पूर्ण;

/**
 *	tty_ldisc_ref_रुको	-	रुको क्रम the tty ldisc
 *	@tty: tty device
 *
 *	Dereference the line discipline क्रम the terminal and take a
 *	reference to it. If the line discipline is in flux then
 *	रुको patiently until it changes.
 *
 *	Returns: शून्य अगर the tty has been hungup and not re-खोलोed with
 *		 a new file descriptor, otherwise valid ldisc reference
 *
 *	Note 1: Must not be called from an IRQ/समयr context. The caller
 *	must also be careful not to hold other locks that will deadlock
 *	against a discipline change, such as an existing ldisc reference
 *	(which we check क्रम)
 *
 *	Note 2: a file_operations routine (पढ़ो/poll/ग_लिखो) should use this
 *	function to रुको क्रम any ldisc lअगरeसमय events to finish.
 */

काष्ठा tty_ldisc *tty_ldisc_ref_रुको(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा tty_ldisc *ld;

	ldsem_करोwn_पढ़ो(&tty->ldisc_sem, MAX_SCHEDULE_TIMEOUT);
	ld = tty->ldisc;
	अगर (!ld)
		ldsem_up_पढ़ो(&tty->ldisc_sem);
	वापस ld;
पूर्ण
EXPORT_SYMBOL_GPL(tty_ldisc_ref_रुको);

/**
 *	tty_ldisc_ref		-	get the tty ldisc
 *	@tty: tty device
 *
 *	Dereference the line discipline क्रम the terminal and take a
 *	reference to it. If the line discipline is in flux then
 *	वापस शून्य. Can be called from IRQ and समयr functions.
 */

काष्ठा tty_ldisc *tty_ldisc_ref(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा tty_ldisc *ld = शून्य;

	अगर (ldsem_करोwn_पढ़ो_trylock(&tty->ldisc_sem)) अणु
		ld = tty->ldisc;
		अगर (!ld)
			ldsem_up_पढ़ो(&tty->ldisc_sem);
	पूर्ण
	वापस ld;
पूर्ण
EXPORT_SYMBOL_GPL(tty_ldisc_ref);

/**
 *	tty_ldisc_deref		-	मुक्त a tty ldisc reference
 *	@ld: reference to मुक्त up
 *
 *	Unकरोes the effect of tty_ldisc_ref or tty_ldisc_ref_रुको. May
 *	be called in IRQ context.
 */

व्योम tty_ldisc_deref(काष्ठा tty_ldisc *ld)
अणु
	ldsem_up_पढ़ो(&ld->tty->ldisc_sem);
पूर्ण
EXPORT_SYMBOL_GPL(tty_ldisc_deref);


अटल अंतरभूत पूर्णांक
__tty_ldisc_lock(काष्ठा tty_काष्ठा *tty, अचिन्हित दीर्घ समयout)
अणु
	वापस ldsem_करोwn_ग_लिखो(&tty->ldisc_sem, समयout);
पूर्ण

अटल अंतरभूत पूर्णांक
__tty_ldisc_lock_nested(काष्ठा tty_काष्ठा *tty, अचिन्हित दीर्घ समयout)
अणु
	वापस ldsem_करोwn_ग_लिखो_nested(&tty->ldisc_sem,
				       LDISC_SEM_OTHER, समयout);
पूर्ण

अटल अंतरभूत व्योम __tty_ldisc_unlock(काष्ठा tty_काष्ठा *tty)
अणु
	ldsem_up_ग_लिखो(&tty->ldisc_sem);
पूर्ण

पूर्णांक tty_ldisc_lock(काष्ठा tty_काष्ठा *tty, अचिन्हित दीर्घ समयout)
अणु
	पूर्णांक ret;

	/* Kindly asking blocked पढ़ोers to release the पढ़ो side */
	set_bit(TTY_LDISC_CHANGING, &tty->flags);
	wake_up_पूर्णांकerruptible_all(&tty->पढ़ो_रुको);
	wake_up_पूर्णांकerruptible_all(&tty->ग_लिखो_रुको);

	ret = __tty_ldisc_lock(tty, समयout);
	अगर (!ret)
		वापस -EBUSY;
	set_bit(TTY_LDISC_HALTED, &tty->flags);
	वापस 0;
पूर्ण

व्योम tty_ldisc_unlock(काष्ठा tty_काष्ठा *tty)
अणु
	clear_bit(TTY_LDISC_HALTED, &tty->flags);
	/* Can be cleared here - ldisc_unlock will wake up ग_लिखोrs firstly */
	clear_bit(TTY_LDISC_CHANGING, &tty->flags);
	__tty_ldisc_unlock(tty);
पूर्ण

अटल पूर्णांक
tty_ldisc_lock_pair_समयout(काष्ठा tty_काष्ठा *tty, काष्ठा tty_काष्ठा *tty2,
			    अचिन्हित दीर्घ समयout)
अणु
	पूर्णांक ret;

	अगर (tty < tty2) अणु
		ret = __tty_ldisc_lock(tty, समयout);
		अगर (ret) अणु
			ret = __tty_ldisc_lock_nested(tty2, समयout);
			अगर (!ret)
				__tty_ldisc_unlock(tty);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* अगर this is possible, it has lots of implications */
		WARN_ON_ONCE(tty == tty2);
		अगर (tty2 && tty != tty2) अणु
			ret = __tty_ldisc_lock(tty2, समयout);
			अगर (ret) अणु
				ret = __tty_ldisc_lock_nested(tty, समयout);
				अगर (!ret)
					__tty_ldisc_unlock(tty2);
			पूर्ण
		पूर्ण अन्यथा
			ret = __tty_ldisc_lock(tty, समयout);
	पूर्ण

	अगर (!ret)
		वापस -EBUSY;

	set_bit(TTY_LDISC_HALTED, &tty->flags);
	अगर (tty2)
		set_bit(TTY_LDISC_HALTED, &tty2->flags);
	वापस 0;
पूर्ण

अटल व्योम tty_ldisc_lock_pair(काष्ठा tty_काष्ठा *tty, काष्ठा tty_काष्ठा *tty2)
अणु
	tty_ldisc_lock_pair_समयout(tty, tty2, MAX_SCHEDULE_TIMEOUT);
पूर्ण

अटल व्योम tty_ldisc_unlock_pair(काष्ठा tty_काष्ठा *tty,
				  काष्ठा tty_काष्ठा *tty2)
अणु
	__tty_ldisc_unlock(tty);
	अगर (tty2)
		__tty_ldisc_unlock(tty2);
पूर्ण

/**
 *	tty_ldisc_flush	-	flush line discipline queue
 *	@tty: tty
 *
 *	Flush the line discipline queue (अगर any) and the tty flip buffers
 *	क्रम this tty.
 */

व्योम tty_ldisc_flush(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा tty_ldisc *ld = tty_ldisc_ref(tty);

	tty_buffer_flush(tty, ld);
	अगर (ld)
		tty_ldisc_deref(ld);
पूर्ण
EXPORT_SYMBOL_GPL(tty_ldisc_flush);

/**
 *	tty_set_termios_ldisc		-	set ldisc field
 *	@tty: tty काष्ठाure
 *	@disc: line discipline number
 *
 *	This is probably overसमाप्त क्रम real world processors but
 *	they are not on hot paths so a little discipline won't करो
 *	any harm.
 *
 *	The line discipline-related tty_काष्ठा fields are reset to
 *	prevent the ldisc driver from re-using stale inक्रमmation क्रम
 *	the new ldisc instance.
 *
 *	Locking: takes termios_rwsem
 */

अटल व्योम tty_set_termios_ldisc(काष्ठा tty_काष्ठा *tty, पूर्णांक disc)
अणु
	करोwn_ग_लिखो(&tty->termios_rwsem);
	tty->termios.c_line = disc;
	up_ग_लिखो(&tty->termios_rwsem);

	tty->disc_data = शून्य;
	tty->receive_room = 0;
पूर्ण

/**
 *	tty_ldisc_खोलो		-	खोलो a line discipline
 *	@tty: tty we are खोलोing the ldisc on
 *	@ld: discipline to खोलो
 *
 *	A helper खोलोing method. Also a convenient debugging and check
 *	poपूर्णांक.
 *
 *	Locking: always called with BTM alपढ़ोy held.
 */

अटल पूर्णांक tty_ldisc_खोलो(काष्ठा tty_काष्ठा *tty, काष्ठा tty_ldisc *ld)
अणु
	WARN_ON(test_and_set_bit(TTY_LDISC_OPEN, &tty->flags));
	अगर (ld->ops->खोलो) अणु
		पूर्णांक ret;
		/* BTM here locks versus a hangup event */
		ret = ld->ops->खोलो(tty);
		अगर (ret)
			clear_bit(TTY_LDISC_OPEN, &tty->flags);

		tty_ldisc_debug(tty, "%p: opened\n", ld);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

/**
 *	tty_ldisc_बंद		-	बंद a line discipline
 *	@tty: tty we are खोलोing the ldisc on
 *	@ld: discipline to बंद
 *
 *	A helper बंद method. Also a convenient debugging and check
 *	poपूर्णांक.
 */

अटल व्योम tty_ldisc_बंद(काष्ठा tty_काष्ठा *tty, काष्ठा tty_ldisc *ld)
अणु
	lockdep_निश्चित_held_ग_लिखो(&tty->ldisc_sem);
	WARN_ON(!test_bit(TTY_LDISC_OPEN, &tty->flags));
	clear_bit(TTY_LDISC_OPEN, &tty->flags);
	अगर (ld->ops->बंद)
		ld->ops->बंद(tty);
	tty_ldisc_debug(tty, "%p: closed\n", ld);
पूर्ण

/**
 *	tty_ldisc_failto	-	helper क्रम ldisc failback
 *	@tty: tty to खोलो the ldisc on
 *	@ld: ldisc we are trying to fail back to
 *
 *	Helper to try and recover a tty when चयनing back to the old
 *	ldisc fails and we need something attached.
 */

अटल पूर्णांक tty_ldisc_failto(काष्ठा tty_काष्ठा *tty, पूर्णांक ld)
अणु
	काष्ठा tty_ldisc *disc = tty_ldisc_get(tty, ld);
	पूर्णांक r;

	lockdep_निश्चित_held_ग_लिखो(&tty->ldisc_sem);
	अगर (IS_ERR(disc))
		वापस PTR_ERR(disc);
	tty->ldisc = disc;
	tty_set_termios_ldisc(tty, ld);
	r = tty_ldisc_खोलो(tty, disc);
	अगर (r < 0)
		tty_ldisc_put(disc);
	वापस r;
पूर्ण

/**
 *	tty_ldisc_restore	-	helper क्रम tty ldisc change
 *	@tty: tty to recover
 *	@old: previous ldisc
 *
 *	Restore the previous line discipline or N_TTY when a line discipline
 *	change fails due to an खोलो error
 */

अटल व्योम tty_ldisc_restore(काष्ठा tty_काष्ठा *tty, काष्ठा tty_ldisc *old)
अणु
	/* There is an outstanding reference here so this is safe */
	अगर (tty_ldisc_failto(tty, old->ops->num) < 0) अणु
		स्थिर अक्षर *name = tty_name(tty);

		pr_warn("Falling back ldisc for %s.\n", name);
		/*
		 * The traditional behaviour is to fall back to N_TTY, we
		 * want to aव्योम falling back to N_शून्य unless we have no
		 * choice to aव्योम the risk of अवरोधing anything
		 */
		अगर (tty_ldisc_failto(tty, N_TTY) < 0 &&
		    tty_ldisc_failto(tty, N_शून्य) < 0)
			panic("Couldn't open N_NULL ldisc for %s.", name);
	पूर्ण
पूर्ण

/**
 *	tty_set_ldisc		-	set line discipline
 *	@tty: the terminal to set
 *	@disc: the line discipline number
 *
 *	Set the discipline of a tty line. Must be called from a process
 *	context. The ldisc change logic has to protect itself against any
 *	overlapping ldisc change (including on the other end of pty pairs),
 *	the बंद of one side of a tty/pty pair, and eventually hangup.
 */

पूर्णांक tty_set_ldisc(काष्ठा tty_काष्ठा *tty, पूर्णांक disc)
अणु
	पूर्णांक retval;
	काष्ठा tty_ldisc *old_ldisc, *new_ldisc;

	new_ldisc = tty_ldisc_get(tty, disc);
	अगर (IS_ERR(new_ldisc))
		वापस PTR_ERR(new_ldisc);

	tty_lock(tty);
	retval = tty_ldisc_lock(tty, 5 * HZ);
	अगर (retval)
		जाओ err;

	अगर (!tty->ldisc) अणु
		retval = -EIO;
		जाओ out;
	पूर्ण

	/* Check the no-op हाल */
	अगर (tty->ldisc->ops->num == disc)
		जाओ out;

	अगर (test_bit(TTY_HUPPED, &tty->flags)) अणु
		/* We were raced by hangup */
		retval = -EIO;
		जाओ out;
	पूर्ण

	old_ldisc = tty->ldisc;

	/* Shutकरोwn the old discipline. */
	tty_ldisc_बंद(tty, old_ldisc);

	/* Now set up the new line discipline. */
	tty->ldisc = new_ldisc;
	tty_set_termios_ldisc(tty, disc);

	retval = tty_ldisc_खोलो(tty, new_ldisc);
	अगर (retval < 0) अणु
		/* Back to the old one or N_TTY अगर we can't */
		tty_ldisc_put(new_ldisc);
		tty_ldisc_restore(tty, old_ldisc);
	पूर्ण

	अगर (tty->ldisc->ops->num != old_ldisc->ops->num && tty->ops->set_ldisc) अणु
		करोwn_पढ़ो(&tty->termios_rwsem);
		tty->ops->set_ldisc(tty);
		up_पढ़ो(&tty->termios_rwsem);
	पूर्ण

	/*
	 * At this poपूर्णांक we hold a reference to the new ldisc and a
	 * reference to the old ldisc, or we hold two references to
	 * the old ldisc (अगर it was restored as part of error cleanup
	 * above). In either हाल, releasing a single reference from
	 * the old ldisc is correct.
	 */
	new_ldisc = old_ldisc;
out:
	tty_ldisc_unlock(tty);

	/*
	 * Restart the work queue in हाल no अक्षरacters kick it off. Safe अगर
	 * alपढ़ोy running
	 */
	tty_buffer_restart_work(tty->port);
err:
	tty_ldisc_put(new_ldisc);	/* drop the extra reference */
	tty_unlock(tty);
	वापस retval;
पूर्ण
EXPORT_SYMBOL_GPL(tty_set_ldisc);

/**
 *	tty_ldisc_समाप्त	-	tearकरोwn ldisc
 *	@tty: tty being released
 *
 *	Perक्रमm final बंद of the ldisc and reset tty->ldisc
 */
अटल व्योम tty_ldisc_समाप्त(काष्ठा tty_काष्ठा *tty)
अणु
	lockdep_निश्चित_held_ग_लिखो(&tty->ldisc_sem);
	अगर (!tty->ldisc)
		वापस;
	/*
	 * Now समाप्त off the ldisc
	 */
	tty_ldisc_बंद(tty, tty->ldisc);
	tty_ldisc_put(tty->ldisc);
	/* Force an oops अगर we mess this up */
	tty->ldisc = शून्य;
पूर्ण

/**
 *	tty_reset_termios	-	reset terminal state
 *	@tty: tty to reset
 *
 *	Restore a terminal to the driver शेष state.
 */

अटल व्योम tty_reset_termios(काष्ठा tty_काष्ठा *tty)
अणु
	करोwn_ग_लिखो(&tty->termios_rwsem);
	tty->termios = tty->driver->init_termios;
	tty->termios.c_ispeed = tty_termios_input_baud_rate(&tty->termios);
	tty->termios.c_ospeed = tty_termios_baud_rate(&tty->termios);
	up_ग_लिखो(&tty->termios_rwsem);
पूर्ण


/**
 *	tty_ldisc_reinit	-	reinitialise the tty ldisc
 *	@tty: tty to reinit
 *	@disc: line discipline to reinitialize
 *
 *	Completely reinitialize the line discipline state, by closing the
 *	current instance, अगर there is one, and खोलोing a new instance. If
 *	an error occurs खोलोing the new non-N_TTY instance, the instance
 *	is dropped and tty->ldisc reset to शून्य. The caller can then retry
 *	with N_TTY instead.
 *
 *	Returns 0 अगर successful, otherwise error code < 0
 */

पूर्णांक tty_ldisc_reinit(काष्ठा tty_काष्ठा *tty, पूर्णांक disc)
अणु
	काष्ठा tty_ldisc *ld;
	पूर्णांक retval;

	lockdep_निश्चित_held_ग_लिखो(&tty->ldisc_sem);
	ld = tty_ldisc_get(tty, disc);
	अगर (IS_ERR(ld)) अणु
		BUG_ON(disc == N_TTY);
		वापस PTR_ERR(ld);
	पूर्ण

	अगर (tty->ldisc) अणु
		tty_ldisc_बंद(tty, tty->ldisc);
		tty_ldisc_put(tty->ldisc);
	पूर्ण

	/* चयन the line discipline */
	tty->ldisc = ld;
	tty_set_termios_ldisc(tty, disc);
	retval = tty_ldisc_खोलो(tty, tty->ldisc);
	अगर (retval) अणु
		tty_ldisc_put(tty->ldisc);
		tty->ldisc = शून्य;
	पूर्ण
	वापस retval;
पूर्ण

/**
 *	tty_ldisc_hangup		-	hangup ldisc reset
 *	@tty: tty being hung up
 *	@reinit: whether to re-initialise the tty
 *
 *	Some tty devices reset their termios when they receive a hangup
 *	event. In that situation we must also चयन back to N_TTY properly
 *	beक्रमe we reset the termios data.
 *
 *	Locking: We can take the ldisc mutex as the rest of the code is
 *	careful to allow क्रम this.
 *
 *	In the pty pair हाल this occurs in the बंद() path of the
 *	tty itself so we must be careful about locking rules.
 */

व्योम tty_ldisc_hangup(काष्ठा tty_काष्ठा *tty, bool reinit)
अणु
	काष्ठा tty_ldisc *ld;

	tty_ldisc_debug(tty, "%p: hangup\n", tty->ldisc);

	ld = tty_ldisc_ref(tty);
	अगर (ld != शून्य) अणु
		अगर (ld->ops->flush_buffer)
			ld->ops->flush_buffer(tty);
		tty_driver_flush_buffer(tty);
		अगर ((test_bit(TTY_DO_WRITE_WAKEUP, &tty->flags)) &&
		    ld->ops->ग_लिखो_wakeup)
			ld->ops->ग_लिखो_wakeup(tty);
		अगर (ld->ops->hangup)
			ld->ops->hangup(tty);
		tty_ldisc_deref(ld);
	पूर्ण

	wake_up_पूर्णांकerruptible_poll(&tty->ग_लिखो_रुको, EPOLLOUT);
	wake_up_पूर्णांकerruptible_poll(&tty->पढ़ो_रुको, EPOLLIN);

	/*
	 * Shutकरोwn the current line discipline, and reset it to
	 * N_TTY अगर need be.
	 *
	 * Aव्योम racing set_ldisc or tty_ldisc_release
	 */
	tty_ldisc_lock(tty, MAX_SCHEDULE_TIMEOUT);

	अगर (tty->driver->flags & TTY_DRIVER_RESET_TERMIOS)
		tty_reset_termios(tty);

	अगर (tty->ldisc) अणु
		अगर (reinit) अणु
			अगर (tty_ldisc_reinit(tty, tty->termios.c_line) < 0 &&
			    tty_ldisc_reinit(tty, N_TTY) < 0)
				WARN_ON(tty_ldisc_reinit(tty, N_शून्य) < 0);
		पूर्ण अन्यथा
			tty_ldisc_समाप्त(tty);
	पूर्ण
	tty_ldisc_unlock(tty);
पूर्ण

/**
 *	tty_ldisc_setup			-	खोलो line discipline
 *	@tty: tty being shut करोwn
 *	@o_tty: pair tty क्रम pty/tty pairs
 *
 *	Called during the initial खोलो of a tty/pty pair in order to set up the
 *	line disciplines and bind them to the tty. This has no locking issues
 *	as the device isn't yet active.
 */

पूर्णांक tty_ldisc_setup(काष्ठा tty_काष्ठा *tty, काष्ठा tty_काष्ठा *o_tty)
अणु
	पूर्णांक retval = tty_ldisc_खोलो(tty, tty->ldisc);

	अगर (retval)
		वापस retval;

	अगर (o_tty) अणु
		/*
		 * Called without o_tty->ldisc_sem held, as o_tty has been
		 * just allocated and no one has a reference to it.
		 */
		retval = tty_ldisc_खोलो(o_tty, o_tty->ldisc);
		अगर (retval) अणु
			tty_ldisc_बंद(tty, tty->ldisc);
			वापस retval;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/**
 *	tty_ldisc_release		-	release line discipline
 *	@tty: tty being shut करोwn (or one end of pty pair)
 *
 *	Called during the final बंद of a tty or a pty pair in order to shut
 *	करोwn the line discpline layer. On निकास, each tty's ldisc is शून्य.
 */

व्योम tty_ldisc_release(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा tty_काष्ठा *o_tty = tty->link;

	/*
	 * Shutकरोwn this line discipline. As this is the final बंद,
	 * it करोes not race with the set_ldisc code path.
	 */

	tty_ldisc_lock_pair(tty, o_tty);
	tty_ldisc_समाप्त(tty);
	अगर (o_tty)
		tty_ldisc_समाप्त(o_tty);
	tty_ldisc_unlock_pair(tty, o_tty);

	/*
	 * And the memory resources reमुख्यing (buffers, termios) will be
	 * disposed of when the kref hits zero
	 */

	tty_ldisc_debug(tty, "released\n");
पूर्ण
EXPORT_SYMBOL_GPL(tty_ldisc_release);

/**
 *	tty_ldisc_init		-	ldisc setup क्रम new tty
 *	@tty: tty being allocated
 *
 *	Set up the line discipline objects क्रम a newly allocated tty. Note that
 *	the tty काष्ठाure is not completely set up when this call is made.
 */

पूर्णांक tty_ldisc_init(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा tty_ldisc *ld = tty_ldisc_get(tty, N_TTY);

	अगर (IS_ERR(ld))
		वापस PTR_ERR(ld);
	tty->ldisc = ld;
	वापस 0;
पूर्ण

/**
 *	tty_ldisc_deinit	-	ldisc cleanup क्रम new tty
 *	@tty: tty that was allocated recently
 *
 *	The tty काष्ठाure must not becompletely set up (tty_ldisc_setup) when
 *      this call is made.
 */
व्योम tty_ldisc_deinit(काष्ठा tty_काष्ठा *tty)
अणु
	/* no ldisc_sem, tty is being destroyed */
	अगर (tty->ldisc)
		tty_ldisc_put(tty->ldisc);
	tty->ldisc = शून्य;
पूर्ण

अटल काष्ठा ctl_table tty_table[] = अणु
	अणु
		.procname	= "ldisc_autoload",
		.data		= &tty_ldisc_स्वतःload,
		.maxlen		= माप(tty_ldisc_स्वतःload),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
		.extra1		= SYSCTL_ZERO,
		.extra2		= SYSCTL_ONE,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा ctl_table tty_dir_table[] = अणु
	अणु
		.procname	= "tty",
		.mode		= 0555,
		.child		= tty_table,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा ctl_table tty_root_table[] = अणु
	अणु
		.procname	= "dev",
		.mode		= 0555,
		.child		= tty_dir_table,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

व्योम tty_sysctl_init(व्योम)
अणु
	रेजिस्टर_sysctl_table(tty_root_table);
पूर्ण
