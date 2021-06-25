<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Copyright (C) 1991, 1992  Linus Torvalds
 */

#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/संकेत.स>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/sched/task.h>
#समावेश <linux/tty.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/uaccess.h>
#समावेश "tty.h"

अटल पूर्णांक is_ignored(पूर्णांक sig)
अणु
	वापस (sigismember(&current->blocked, sig) ||
		current->sighand->action[sig-1].sa.sa_handler == संक_छोड़ो);
पूर्ण

/**
 *	tty_check_change	-	check क्रम POSIX terminal changes
 *	@tty: tty to check
 *	@sig: संकेत to send
 *
 *	If we try to ग_लिखो to, or set the state of, a terminal and we're
 *	not in the क्रमeground, send a SIGTTOU.  If the संकेत is blocked or
 *	ignored, go ahead and perक्रमm the operation.  (POSIX 7.2)
 *
 *	Locking: ctrl_lock
 */
पूर्णांक __tty_check_change(काष्ठा tty_काष्ठा *tty, पूर्णांक sig)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा pid *pgrp, *tty_pgrp;
	पूर्णांक ret = 0;

	अगर (current->संकेत->tty != tty)
		वापस 0;

	rcu_पढ़ो_lock();
	pgrp = task_pgrp(current);

	spin_lock_irqsave(&tty->ctrl_lock, flags);
	tty_pgrp = tty->pgrp;
	spin_unlock_irqrestore(&tty->ctrl_lock, flags);

	अगर (tty_pgrp && pgrp != tty_pgrp) अणु
		अगर (is_ignored(sig)) अणु
			अगर (sig == SIGTTIN)
				ret = -EIO;
		पूर्ण अन्यथा अगर (is_current_pgrp_orphaned())
			ret = -EIO;
		अन्यथा अणु
			समाप्त_pgrp(pgrp, sig, 1);
			set_thपढ़ो_flag(TIF_SIGPENDING);
			ret = -ERESTARTSYS;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	अगर (!tty_pgrp)
		tty_warn(tty, "sig=%d, tty->pgrp == NULL!\n", sig);

	वापस ret;
पूर्ण

पूर्णांक tty_check_change(काष्ठा tty_काष्ठा *tty)
अणु
	वापस __tty_check_change(tty, SIGTTOU);
पूर्ण
EXPORT_SYMBOL(tty_check_change);

व्योम proc_clear_tty(काष्ठा task_काष्ठा *p)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा tty_काष्ठा *tty;

	spin_lock_irqsave(&p->sighand->siglock, flags);
	tty = p->संकेत->tty;
	p->संकेत->tty = शून्य;
	spin_unlock_irqrestore(&p->sighand->siglock, flags);
	tty_kref_put(tty);
पूर्ण

/**
 * proc_set_tty -  set the controlling terminal
 *	@tty: tty काष्ठाure
 *
 * Only callable by the session leader and only अगर it करोes not alपढ़ोy have
 * a controlling terminal.
 *
 * Caller must hold:  tty_lock()
 *		      a पढ़ोlock on tasklist_lock
 *		      sighand lock
 */
अटल व्योम __proc_set_tty(काष्ठा tty_काष्ठा *tty)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&tty->ctrl_lock, flags);
	/*
	 * The session and fg pgrp references will be non-शून्य अगर
	 * tiocsctty() is stealing the controlling tty
	 */
	put_pid(tty->session);
	put_pid(tty->pgrp);
	tty->pgrp = get_pid(task_pgrp(current));
	tty->session = get_pid(task_session(current));
	spin_unlock_irqrestore(&tty->ctrl_lock, flags);
	अगर (current->संकेत->tty) अणु
		tty_debug(tty, "current tty %s not NULL!!\n",
			  current->संकेत->tty->name);
		tty_kref_put(current->संकेत->tty);
	पूर्ण
	put_pid(current->संकेत->tty_old_pgrp);
	current->संकेत->tty = tty_kref_get(tty);
	current->संकेत->tty_old_pgrp = शून्य;
पूर्ण

अटल व्योम proc_set_tty(काष्ठा tty_काष्ठा *tty)
अणु
	spin_lock_irq(&current->sighand->siglock);
	__proc_set_tty(tty);
	spin_unlock_irq(&current->sighand->siglock);
पूर्ण

/*
 * Called by tty_खोलो() to set the controlling tty अगर applicable.
 */
व्योम tty_खोलो_proc_set_tty(काष्ठा file *filp, काष्ठा tty_काष्ठा *tty)
अणु
	पढ़ो_lock(&tasklist_lock);
	spin_lock_irq(&current->sighand->siglock);
	अगर (current->संकेत->leader &&
	    !current->संकेत->tty &&
	    tty->session == शून्य) अणु
		/*
		 * Don't let a process that only has ग_लिखो access to the tty
		 * obtain the privileges associated with having a tty as
		 * controlling terminal (being able to reखोलो it with full
		 * access through /dev/tty, being able to perक्रमm pushback).
		 * Many distributions set the group of all ttys to "tty" and
		 * grant ग_लिखो-only access to all terminals क्रम setgid tty
		 * binaries, which should not imply full privileges on all ttys.
		 *
		 * This could theoretically अवरोध old code that perक्रमms खोलो()
		 * on a ग_लिखो-only file descriptor. In that हाल, it might be
		 * necessary to also permit this अगर
		 * inode_permission(inode, MAY_READ) == 0.
		 */
		अगर (filp->f_mode & FMODE_READ)
			__proc_set_tty(tty);
	पूर्ण
	spin_unlock_irq(&current->sighand->siglock);
	पढ़ो_unlock(&tasklist_lock);
पूर्ण

काष्ठा tty_काष्ठा *get_current_tty(व्योम)
अणु
	काष्ठा tty_काष्ठा *tty;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&current->sighand->siglock, flags);
	tty = tty_kref_get(current->संकेत->tty);
	spin_unlock_irqrestore(&current->sighand->siglock, flags);
	वापस tty;
पूर्ण
EXPORT_SYMBOL_GPL(get_current_tty);

/*
 * Called from tty_release().
 */
व्योम session_clear_tty(काष्ठा pid *session)
अणु
	काष्ठा task_काष्ठा *p;

	करो_each_pid_task(session, PIDTYPE_SID, p) अणु
		proc_clear_tty(p);
	पूर्ण जबतक_each_pid_task(session, PIDTYPE_SID, p);
पूर्ण

/**
 *	tty_संकेत_session_leader	- sends SIGHUP to session leader
 *	@tty: controlling tty
 *	@निकास_session: अगर non-zero, संकेत all क्रमeground group processes
 *
 *	Send SIGHUP and SIGCONT to the session leader and its process group.
 *	Optionally, संकेत all processes in the क्रमeground process group.
 *
 *	Returns the number of processes in the session with this tty
 *	as their controlling terminal. This value is used to drop
 *	tty references क्रम those processes.
 */
पूर्णांक tty_संकेत_session_leader(काष्ठा tty_काष्ठा *tty, पूर्णांक निकास_session)
अणु
	काष्ठा task_काष्ठा *p;
	पूर्णांक refs = 0;
	काष्ठा pid *tty_pgrp = शून्य;

	पढ़ो_lock(&tasklist_lock);
	अगर (tty->session) अणु
		करो_each_pid_task(tty->session, PIDTYPE_SID, p) अणु
			spin_lock_irq(&p->sighand->siglock);
			अगर (p->संकेत->tty == tty) अणु
				p->संकेत->tty = शून्य;
				/*
				 * We defer the dereferences outside of
				 * the tasklist lock.
				 */
				refs++;
			पूर्ण
			अगर (!p->संकेत->leader) अणु
				spin_unlock_irq(&p->sighand->siglock);
				जारी;
			पूर्ण
			__group_send_sig_info(SIGHUP, SEND_SIG_PRIV, p);
			__group_send_sig_info(SIGCONT, SEND_SIG_PRIV, p);
			put_pid(p->संकेत->tty_old_pgrp);  /* A noop */
			spin_lock(&tty->ctrl_lock);
			tty_pgrp = get_pid(tty->pgrp);
			अगर (tty->pgrp)
				p->संकेत->tty_old_pgrp = get_pid(tty->pgrp);
			spin_unlock(&tty->ctrl_lock);
			spin_unlock_irq(&p->sighand->siglock);
		पूर्ण जबतक_each_pid_task(tty->session, PIDTYPE_SID, p);
	पूर्ण
	पढ़ो_unlock(&tasklist_lock);

	अगर (tty_pgrp) अणु
		अगर (निकास_session)
			समाप्त_pgrp(tty_pgrp, SIGHUP, निकास_session);
		put_pid(tty_pgrp);
	पूर्ण

	वापस refs;
पूर्ण

/**
 *	disassociate_ctty	-	disconnect controlling tty
 *	@on_निकास: true अगर निकासing so need to "hang up" the session
 *
 *	This function is typically called only by the session leader, when
 *	it wants to disassociate itself from its controlling tty.
 *
 *	It perक्रमms the following functions:
 *	(1)  Sends a SIGHUP and SIGCONT to the क्रमeground process group
 *	(2)  Clears the tty from being controlling the session
 *	(3)  Clears the controlling tty क्रम all processes in the
 *		session group.
 *
 *	The argument on_निकास is set to 1 अगर called when a process is
 *	निकासing; it is 0 अगर called by the ioctl TIOCNOTTY.
 *
 *	Locking:
 *		BTM is taken क्रम hysterical raisons, and held when
 *		  called from no_tty().
 *		  tty_mutex is taken to protect tty
 *		  ->siglock is taken to protect ->संकेत/->sighand
 *		  tasklist_lock is taken to walk process list क्रम sessions
 *		    ->siglock is taken to protect ->संकेत/->sighand
 */
व्योम disassociate_ctty(पूर्णांक on_निकास)
अणु
	काष्ठा tty_काष्ठा *tty;

	अगर (!current->संकेत->leader)
		वापस;

	tty = get_current_tty();
	अगर (tty) अणु
		अगर (on_निकास && tty->driver->type != TTY_DRIVER_TYPE_PTY) अणु
			tty_vhangup_session(tty);
		पूर्ण अन्यथा अणु
			काष्ठा pid *tty_pgrp = tty_get_pgrp(tty);

			अगर (tty_pgrp) अणु
				समाप्त_pgrp(tty_pgrp, SIGHUP, on_निकास);
				अगर (!on_निकास)
					समाप्त_pgrp(tty_pgrp, SIGCONT, on_निकास);
				put_pid(tty_pgrp);
			पूर्ण
		पूर्ण
		tty_kref_put(tty);

	पूर्ण अन्यथा अगर (on_निकास) अणु
		काष्ठा pid *old_pgrp;

		spin_lock_irq(&current->sighand->siglock);
		old_pgrp = current->संकेत->tty_old_pgrp;
		current->संकेत->tty_old_pgrp = शून्य;
		spin_unlock_irq(&current->sighand->siglock);
		अगर (old_pgrp) अणु
			समाप्त_pgrp(old_pgrp, SIGHUP, on_निकास);
			समाप्त_pgrp(old_pgrp, SIGCONT, on_निकास);
			put_pid(old_pgrp);
		पूर्ण
		वापस;
	पूर्ण

	spin_lock_irq(&current->sighand->siglock);
	put_pid(current->संकेत->tty_old_pgrp);
	current->संकेत->tty_old_pgrp = शून्य;
	tty = tty_kref_get(current->संकेत->tty);
	spin_unlock_irq(&current->sighand->siglock);

	अगर (tty) अणु
		अचिन्हित दीर्घ flags;

		tty_lock(tty);
		spin_lock_irqsave(&tty->ctrl_lock, flags);
		put_pid(tty->session);
		put_pid(tty->pgrp);
		tty->session = शून्य;
		tty->pgrp = शून्य;
		spin_unlock_irqrestore(&tty->ctrl_lock, flags);
		tty_unlock(tty);
		tty_kref_put(tty);
	पूर्ण

	/* Now clear संकेत->tty under the lock */
	पढ़ो_lock(&tasklist_lock);
	session_clear_tty(task_session(current));
	पढ़ो_unlock(&tasklist_lock);
पूर्ण

/*
 *
 *	no_tty	- Ensure the current process करोes not have a controlling tty
 */
व्योम no_tty(व्योम)
अणु
	/*
	 * FIXME: Review locking here. The tty_lock never covered any race
	 * between a new association and proc_clear_tty but possibly we need
	 * to protect against this anyway.
	 */
	काष्ठा task_काष्ठा *tsk = current;

	disassociate_ctty(0);
	proc_clear_tty(tsk);
पूर्ण

/**
 *	tiocsctty	-	set controlling tty
 *	@tty: tty काष्ठाure
 *	@file: file काष्ठाure used to check permissions
 *	@arg: user argument
 *
 *	This ioctl is used to manage job control. It permits a session
 *	leader to set this tty as the controlling tty क्रम the session.
 *
 *	Locking:
 *		Takes tty_lock() to serialize proc_set_tty() क्रम this tty
 *		Takes tasklist_lock पूर्णांकernally to walk sessions
 *		Takes ->siglock() when updating संकेत->tty
 */
अटल पूर्णांक tiocsctty(काष्ठा tty_काष्ठा *tty, काष्ठा file *file, पूर्णांक arg)
अणु
	पूर्णांक ret = 0;

	tty_lock(tty);
	पढ़ो_lock(&tasklist_lock);

	अगर (current->संकेत->leader && (task_session(current) == tty->session))
		जाओ unlock;

	/*
	 * The process must be a session leader and
	 * not have a controlling tty alपढ़ोy.
	 */
	अगर (!current->संकेत->leader || current->संकेत->tty) अणु
		ret = -EPERM;
		जाओ unlock;
	पूर्ण

	अगर (tty->session) अणु
		/*
		 * This tty is alपढ़ोy the controlling
		 * tty क्रम another session group!
		 */
		अगर (arg == 1 && capable(CAP_SYS_ADMIN)) अणु
			/*
			 * Steal it away
			 */
			session_clear_tty(tty->session);
		पूर्ण अन्यथा अणु
			ret = -EPERM;
			जाओ unlock;
		पूर्ण
	पूर्ण

	/* See the comment in tty_खोलो_proc_set_tty(). */
	अगर ((file->f_mode & FMODE_READ) == 0 && !capable(CAP_SYS_ADMIN)) अणु
		ret = -EPERM;
		जाओ unlock;
	पूर्ण

	proc_set_tty(tty);
unlock:
	पढ़ो_unlock(&tasklist_lock);
	tty_unlock(tty);
	वापस ret;
पूर्ण

/**
 *	tty_get_pgrp	-	वापस a ref counted pgrp pid
 *	@tty: tty to पढ़ो
 *
 *	Returns a refcounted instance of the pid काष्ठा क्रम the process
 *	group controlling the tty.
 */
काष्ठा pid *tty_get_pgrp(काष्ठा tty_काष्ठा *tty)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा pid *pgrp;

	spin_lock_irqsave(&tty->ctrl_lock, flags);
	pgrp = get_pid(tty->pgrp);
	spin_unlock_irqrestore(&tty->ctrl_lock, flags);

	वापस pgrp;
पूर्ण
EXPORT_SYMBOL_GPL(tty_get_pgrp);

/*
 * This checks not only the pgrp, but falls back on the pid अगर no
 * satisfactory pgrp is found. I dunno - gdb करोesn't work correctly
 * without this...
 *
 * The caller must hold rcu lock or the tasklist lock.
 */
अटल काष्ठा pid *session_of_pgrp(काष्ठा pid *pgrp)
अणु
	काष्ठा task_काष्ठा *p;
	काष्ठा pid *sid = शून्य;

	p = pid_task(pgrp, PIDTYPE_PGID);
	अगर (p == शून्य)
		p = pid_task(pgrp, PIDTYPE_PID);
	अगर (p != शून्य)
		sid = task_session(p);

	वापस sid;
पूर्ण

/**
 *	tiocgpgrp		-	get process group
 *	@tty: tty passed by user
 *	@real_tty: tty side of the tty passed by the user अगर a pty अन्यथा the tty
 *	@p: वापसed pid
 *
 *	Obtain the process group of the tty. If there is no process group
 *	वापस an error.
 *
 *	Locking: none. Reference to current->संकेत->tty is safe.
 */
अटल पूर्णांक tiocgpgrp(काष्ठा tty_काष्ठा *tty, काष्ठा tty_काष्ठा *real_tty, pid_t __user *p)
अणु
	काष्ठा pid *pid;
	पूर्णांक ret;
	/*
	 * (tty == real_tty) is a cheap way of
	 * testing अगर the tty is NOT a master pty.
	 */
	अगर (tty == real_tty && current->संकेत->tty != real_tty)
		वापस -ENOTTY;
	pid = tty_get_pgrp(real_tty);
	ret =  put_user(pid_vnr(pid), p);
	put_pid(pid);
	वापस ret;
पूर्ण

/**
 *	tiocspgrp		-	attempt to set process group
 *	@tty: tty passed by user
 *	@real_tty: tty side device matching tty passed by user
 *	@p: pid poपूर्णांकer
 *
 *	Set the process group of the tty to the session passed. Only
 *	permitted where the tty session is our session.
 *
 *	Locking: RCU, ctrl lock
 */
अटल पूर्णांक tiocspgrp(काष्ठा tty_काष्ठा *tty, काष्ठा tty_काष्ठा *real_tty, pid_t __user *p)
अणु
	काष्ठा pid *pgrp;
	pid_t pgrp_nr;
	पूर्णांक retval = tty_check_change(real_tty);

	अगर (retval == -EIO)
		वापस -ENOTTY;
	अगर (retval)
		वापस retval;

	अगर (get_user(pgrp_nr, p))
		वापस -EFAULT;
	अगर (pgrp_nr < 0)
		वापस -EINVAL;

	spin_lock_irq(&real_tty->ctrl_lock);
	अगर (!current->संकेत->tty ||
	    (current->संकेत->tty != real_tty) ||
	    (real_tty->session != task_session(current))) अणु
		retval = -ENOTTY;
		जाओ out_unlock_ctrl;
	पूर्ण
	rcu_पढ़ो_lock();
	pgrp = find_vpid(pgrp_nr);
	retval = -ESRCH;
	अगर (!pgrp)
		जाओ out_unlock;
	retval = -EPERM;
	अगर (session_of_pgrp(pgrp) != task_session(current))
		जाओ out_unlock;
	retval = 0;
	put_pid(real_tty->pgrp);
	real_tty->pgrp = get_pid(pgrp);
out_unlock:
	rcu_पढ़ो_unlock();
out_unlock_ctrl:
	spin_unlock_irq(&real_tty->ctrl_lock);
	वापस retval;
पूर्ण

/**
 *	tiocgsid		-	get session id
 *	@tty: tty passed by user
 *	@real_tty: tty side of the tty passed by the user अगर a pty अन्यथा the tty
 *	@p: poपूर्णांकer to वापसed session id
 *
 *	Obtain the session id of the tty. If there is no session
 *	वापस an error.
 */
अटल पूर्णांक tiocgsid(काष्ठा tty_काष्ठा *tty, काष्ठा tty_काष्ठा *real_tty, pid_t __user *p)
अणु
	अचिन्हित दीर्घ flags;
	pid_t sid;

	/*
	 * (tty == real_tty) is a cheap way of
	 * testing अगर the tty is NOT a master pty.
	 */
	अगर (tty == real_tty && current->संकेत->tty != real_tty)
		वापस -ENOTTY;

	spin_lock_irqsave(&real_tty->ctrl_lock, flags);
	अगर (!real_tty->session)
		जाओ err;
	sid = pid_vnr(real_tty->session);
	spin_unlock_irqrestore(&real_tty->ctrl_lock, flags);

	वापस put_user(sid, p);

err:
	spin_unlock_irqrestore(&real_tty->ctrl_lock, flags);
	वापस -ENOTTY;
पूर्ण

/*
 * Called from tty_ioctl(). If tty is a pty then real_tty is the slave side,
 * अगर not then tty == real_tty.
 */
दीर्घ tty_jobctrl_ioctl(काष्ठा tty_काष्ठा *tty, काष्ठा tty_काष्ठा *real_tty,
		       काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	व्योम __user *p = (व्योम __user *)arg;

	चयन (cmd) अणु
	हाल TIOCNOTTY:
		अगर (current->संकेत->tty != tty)
			वापस -ENOTTY;
		no_tty();
		वापस 0;
	हाल TIOCSCTTY:
		वापस tiocsctty(real_tty, file, arg);
	हाल TIOCGPGRP:
		वापस tiocgpgrp(tty, real_tty, p);
	हाल TIOCSPGRP:
		वापस tiocspgrp(tty, real_tty, p);
	हाल TIOCGSID:
		वापस tiocgsid(tty, real_tty, p);
	पूर्ण
	वापस -ENOIOCTLCMD;
पूर्ण
