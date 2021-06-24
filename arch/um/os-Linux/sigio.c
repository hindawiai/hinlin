<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2002 - 2008 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 */

#समावेश <unistd.h>
#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <poll.h>
#समावेश <pty.h>
#समावेश <sched.h>
#समावेश <संकेत.स>
#समावेश <माला.स>
#समावेश <kern_util.h>
#समावेश <init.h>
#समावेश <os.h>
#समावेश <sigपन.स>
#समावेश <um_दो_स्मृति.h>

/*
 * Protected by sigio_lock(), also used by sigio_cleanup, which is an
 * निकासcall.
 */
अटल पूर्णांक ग_लिखो_sigio_pid = -1;
अटल अचिन्हित दीर्घ ग_लिखो_sigio_stack;

/*
 * These arrays are initialized beक्रमe the sigio thपढ़ो is started, and
 * the descriptors बंदd after it is समाप्तed.  So, it can't see them change.
 * On the UML side, they are changed under the sigio_lock.
 */
#घोषणा SIGIO_FDS_INIT अणु-1, -1पूर्ण

अटल पूर्णांक ग_लिखो_sigio_fds[2] = SIGIO_FDS_INIT;
अटल पूर्णांक sigio_निजी[2] = SIGIO_FDS_INIT;

काष्ठा pollfds अणु
	काष्ठा pollfd *poll;
	पूर्णांक size;
	पूर्णांक used;
पूर्ण;

/*
 * Protected by sigio_lock().  Used by the sigio thपढ़ो, but the UML thपढ़ो
 * synchronizes with it.
 */
अटल काष्ठा pollfds current_poll;
अटल काष्ठा pollfds next_poll;
अटल काष्ठा pollfds all_sigio_fds;

अटल पूर्णांक ग_लिखो_sigio_thपढ़ो(व्योम *unused)
अणु
	काष्ठा pollfds *fds, पंचांगp;
	काष्ठा pollfd *p;
	पूर्णांक i, n, respond_fd;
	अक्षर c;

	os_fix_helper_संकेतs();
	fds = &current_poll;
	जबतक (1) अणु
		n = poll(fds->poll, fds->used, -1);
		अगर (n < 0) अणु
			अगर (त्रुटि_सं == EINTR)
				जारी;
			prपूर्णांकk(UM_KERN_ERR "write_sigio_thread : poll returned "
			       "%d, errno = %d\n", n, त्रुटि_सं);
		पूर्ण
		क्रम (i = 0; i < fds->used; i++) अणु
			p = &fds->poll[i];
			अगर (p->revents == 0)
				जारी;
			अगर (p->fd == sigio_निजी[1]) अणु
				CATCH_EINTR(n = पढ़ो(sigio_निजी[1], &c,
						     माप(c)));
				अगर (n != माप(c))
					prपूर्णांकk(UM_KERN_ERR
					       "write_sigio_thread : "
					       "read on socket failed, "
					       "err = %d\n", त्रुटि_सं);
				पंचांगp = current_poll;
				current_poll = next_poll;
				next_poll = पंचांगp;
				respond_fd = sigio_निजी[1];
			पूर्ण
			अन्यथा अणु
				respond_fd = ग_लिखो_sigio_fds[1];
				fds->used--;
				स_हटाओ(&fds->poll[i], &fds->poll[i + 1],
					(fds->used - i) * माप(*fds->poll));
			पूर्ण

			CATCH_EINTR(n = ग_लिखो(respond_fd, &c, माप(c)));
			अगर (n != माप(c))
				prपूर्णांकk(UM_KERN_ERR "write_sigio_thread : "
				       "write on socket failed, err = %d\n",
				       त्रुटि_सं);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक need_poll(काष्ठा pollfds *polls, पूर्णांक n)
अणु
	काष्ठा pollfd *new;

	अगर (n <= polls->size)
		वापस 0;

	new = uml_kदो_स्मृति(n * माप(काष्ठा pollfd), UM_GFP_ATOMIC);
	अगर (new == शून्य) अणु
		prपूर्णांकk(UM_KERN_ERR "need_poll : failed to allocate new "
		       "pollfds\n");
		वापस -ENOMEM;
	पूर्ण

	स_नकल(new, polls->poll, polls->used * माप(काष्ठा pollfd));
	kमुक्त(polls->poll);

	polls->poll = new;
	polls->size = n;
	वापस 0;
पूर्ण

/*
 * Must be called with sigio_lock held, because it's needed by the marked
 * critical section.
 */
अटल व्योम update_thपढ़ो(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक n;
	अक्षर c;

	flags = set_संकेतs_trace(0);
	CATCH_EINTR(n = ग_लिखो(sigio_निजी[0], &c, माप(c)));
	अगर (n != माप(c)) अणु
		prपूर्णांकk(UM_KERN_ERR "update_thread : write failed, err = %d\n",
		       त्रुटि_सं);
		जाओ fail;
	पूर्ण

	CATCH_EINTR(n = पढ़ो(sigio_निजी[0], &c, माप(c)));
	अगर (n != माप(c)) अणु
		prपूर्णांकk(UM_KERN_ERR "update_thread : read failed, err = %d\n",
		       त्रुटि_सं);
		जाओ fail;
	पूर्ण

	set_संकेतs_trace(flags);
	वापस;
 fail:
	/* Critical section start */
	अगर (ग_लिखो_sigio_pid != -1) अणु
		os_समाप्त_process(ग_लिखो_sigio_pid, 1);
		मुक्त_stack(ग_लिखो_sigio_stack, 0);
	पूर्ण
	ग_लिखो_sigio_pid = -1;
	बंद(sigio_निजी[0]);
	बंद(sigio_निजी[1]);
	बंद(ग_लिखो_sigio_fds[0]);
	बंद(ग_लिखो_sigio_fds[1]);
	/* Critical section end */
	set_संकेतs_trace(flags);
पूर्ण

पूर्णांक __add_sigio_fd(पूर्णांक fd)
अणु
	काष्ठा pollfd *p;
	पूर्णांक err, i, n;

	क्रम (i = 0; i < all_sigio_fds.used; i++) अणु
		अगर (all_sigio_fds.poll[i].fd == fd)
			अवरोध;
	पूर्ण
	अगर (i == all_sigio_fds.used)
		वापस -ENOSPC;

	p = &all_sigio_fds.poll[i];

	क्रम (i = 0; i < current_poll.used; i++) अणु
		अगर (current_poll.poll[i].fd == fd)
			वापस 0;
	पूर्ण

	n = current_poll.used;
	err = need_poll(&next_poll, n + 1);
	अगर (err)
		वापस err;

	स_नकल(next_poll.poll, current_poll.poll,
	       current_poll.used * माप(काष्ठा pollfd));
	next_poll.poll[n] = *p;
	next_poll.used = n + 1;
	update_thपढ़ो();

	वापस 0;
पूर्ण


पूर्णांक add_sigio_fd(पूर्णांक fd)
अणु
	पूर्णांक err;

	sigio_lock();
	err = __add_sigio_fd(fd);
	sigio_unlock();

	वापस err;
पूर्ण

पूर्णांक __ignore_sigio_fd(पूर्णांक fd)
अणु
	काष्ठा pollfd *p;
	पूर्णांक err, i, n = 0;

	/*
	 * This is called from निकासcalls अन्यथाwhere in UML - अगर
	 * sigio_cleanup has alपढ़ोy run, then update_thपढ़ो will hang
	 * or fail because the thपढ़ो is no दीर्घer running.
	 */
	अगर (ग_लिखो_sigio_pid == -1)
		वापस -EIO;

	क्रम (i = 0; i < current_poll.used; i++) अणु
		अगर (current_poll.poll[i].fd == fd)
			अवरोध;
	पूर्ण
	अगर (i == current_poll.used)
		वापस -ENOENT;

	err = need_poll(&next_poll, current_poll.used - 1);
	अगर (err)
		वापस err;

	क्रम (i = 0; i < current_poll.used; i++) अणु
		p = &current_poll.poll[i];
		अगर (p->fd != fd)
			next_poll.poll[n++] = *p;
	पूर्ण
	next_poll.used = current_poll.used - 1;

	update_thपढ़ो();

	वापस 0;
पूर्ण

पूर्णांक ignore_sigio_fd(पूर्णांक fd)
अणु
	पूर्णांक err;

	sigio_lock();
	err = __ignore_sigio_fd(fd);
	sigio_unlock();

	वापस err;
पूर्ण

अटल काष्ठा pollfd *setup_initial_poll(पूर्णांक fd)
अणु
	काष्ठा pollfd *p;

	p = uml_kदो_स्मृति(माप(काष्ठा pollfd), UM_GFP_KERNEL);
	अगर (p == शून्य) अणु
		prपूर्णांकk(UM_KERN_ERR "setup_initial_poll : failed to allocate "
		       "poll\n");
		वापस शून्य;
	पूर्ण
	*p = ((काष्ठा pollfd) अणु .fd		= fd,
				.events 	= POLLIN,
				.revents 	= 0 पूर्ण);
	वापस p;
पूर्ण

अटल व्योम ग_लिखो_sigio_workaround(व्योम)
अणु
	काष्ठा pollfd *p;
	पूर्णांक err;
	पूर्णांक l_ग_लिखो_sigio_fds[2];
	पूर्णांक l_sigio_निजी[2];
	पूर्णांक l_ग_लिखो_sigio_pid;

	/* We call this *tons* of बार - and most ones we must just fail. */
	sigio_lock();
	l_ग_लिखो_sigio_pid = ग_लिखो_sigio_pid;
	sigio_unlock();

	अगर (l_ग_लिखो_sigio_pid != -1)
		वापस;

	err = os_pipe(l_ग_लिखो_sigio_fds, 1, 1);
	अगर (err < 0) अणु
		prपूर्णांकk(UM_KERN_ERR "write_sigio_workaround - os_pipe 1 failed, "
		       "err = %d\n", -err);
		वापस;
	पूर्ण
	err = os_pipe(l_sigio_निजी, 1, 1);
	अगर (err < 0) अणु
		prपूर्णांकk(UM_KERN_ERR "write_sigio_workaround - os_pipe 2 failed, "
		       "err = %d\n", -err);
		जाओ out_बंद1;
	पूर्ण

	p = setup_initial_poll(l_sigio_निजी[1]);
	अगर (!p)
		जाओ out_बंद2;

	sigio_lock();

	/*
	 * Did we race? Don't try to optimize this, please, it's not so likely
	 * to happen, and no more than once at the boot.
	 */
	अगर (ग_लिखो_sigio_pid != -1)
		जाओ out_मुक्त;

	current_poll = ((काष्ठा pollfds) अणु .poll 	= p,
					   .used 	= 1,
					   .size 	= 1 पूर्ण);

	अगर (ग_लिखो_sigio_irq(l_ग_लिखो_sigio_fds[0]))
		जाओ out_clear_poll;

	स_नकल(ग_लिखो_sigio_fds, l_ग_लिखो_sigio_fds, माप(l_ग_लिखो_sigio_fds));
	स_नकल(sigio_निजी, l_sigio_निजी, माप(l_sigio_निजी));

	ग_लिखो_sigio_pid = run_helper_thपढ़ो(ग_लिखो_sigio_thपढ़ो, शून्य,
					    CLONE_खाताS | CLONE_VM,
					    &ग_लिखो_sigio_stack);

	अगर (ग_लिखो_sigio_pid < 0)
		जाओ out_clear;

	sigio_unlock();
	वापस;

out_clear:
	ग_लिखो_sigio_pid = -1;
	ग_लिखो_sigio_fds[0] = -1;
	ग_लिखो_sigio_fds[1] = -1;
	sigio_निजी[0] = -1;
	sigio_निजी[1] = -1;
out_clear_poll:
	current_poll = ((काष्ठा pollfds) अणु .poll	= शून्य,
					   .size	= 0,
					   .used	= 0 पूर्ण);
out_मुक्त:
	sigio_unlock();
	kमुक्त(p);
out_बंद2:
	बंद(l_sigio_निजी[0]);
	बंद(l_sigio_निजी[1]);
out_बंद1:
	बंद(l_ग_लिखो_sigio_fds[0]);
	बंद(l_ग_लिखो_sigio_fds[1]);
पूर्ण

व्योम sigio_broken(पूर्णांक fd)
अणु
	पूर्णांक err;

	ग_लिखो_sigio_workaround();

	sigio_lock();
	err = need_poll(&all_sigio_fds, all_sigio_fds.used + 1);
	अगर (err) अणु
		prपूर्णांकk(UM_KERN_ERR "maybe_sigio_broken - failed to add pollfd "
		       "for descriptor %d\n", fd);
		जाओ out;
	पूर्ण

	all_sigio_fds.poll[all_sigio_fds.used++] =
		((काष्ठा pollfd) अणु .fd  	= fd,
				   .events 	= POLLIN,
				   .revents 	= 0 पूर्ण);
out:
	sigio_unlock();
पूर्ण

/* Changed during early boot */
अटल पूर्णांक pty_output_sigio;

व्योम maybe_sigio_broken(पूर्णांक fd)
अणु
	अगर (!isatty(fd))
		वापस;

	अगर (pty_output_sigio)
		वापस;

	sigio_broken(fd);
पूर्ण

अटल व्योम sigio_cleanup(व्योम)
अणु
	अगर (ग_लिखो_sigio_pid == -1)
		वापस;

	os_समाप्त_process(ग_लिखो_sigio_pid, 1);
	मुक्त_stack(ग_लिखो_sigio_stack, 0);
	ग_लिखो_sigio_pid = -1;
पूर्ण

__uml_निकासcall(sigio_cleanup);

/* Used as a flag during SIGIO testing early in boot */
अटल पूर्णांक got_sigio;

अटल व्योम __init handler(पूर्णांक sig)
अणु
	got_sigio = 1;
पूर्ण

काष्ठा खोलोpty_arg अणु
	पूर्णांक master;
	पूर्णांक slave;
	पूर्णांक err;
पूर्ण;

अटल व्योम खोलोpty_cb(व्योम *arg)
अणु
	काष्ठा खोलोpty_arg *info = arg;

	info->err = 0;
	अगर (खोलोpty(&info->master, &info->slave, शून्य, शून्य, शून्य))
		info->err = -त्रुटि_सं;
पूर्ण

अटल पूर्णांक async_pty(पूर्णांक master, पूर्णांक slave)
अणु
	पूर्णांक flags;

	flags = fcntl(master, F_GETFL);
	अगर (flags < 0)
		वापस -त्रुटि_सं;

	अगर ((fcntl(master, F_SETFL, flags | O_NONBLOCK | O_ASYNC) < 0) ||
	    (fcntl(master, F_SETOWN, os_getpid()) < 0))
		वापस -त्रुटि_सं;

	अगर ((fcntl(slave, F_SETFL, flags | O_NONBLOCK) < 0))
		वापस -त्रुटि_सं;

	वापस 0;
पूर्ण

अटल व्योम __init check_one_sigio(व्योम (*proc)(पूर्णांक, पूर्णांक))
अणु
	काष्ठा sigaction old, new;
	काष्ठा खोलोpty_arg pty = अणु .master = -1, .slave = -1 पूर्ण;
	पूर्णांक master, slave, err;

	initial_thपढ़ो_cb(खोलोpty_cb, &pty);
	अगर (pty.err) अणु
		prपूर्णांकk(UM_KERN_ERR "check_one_sigio failed, errno = %d\n",
		       -pty.err);
		वापस;
	पूर्ण

	master = pty.master;
	slave = pty.slave;

	अगर ((master == -1) || (slave == -1)) अणु
		prपूर्णांकk(UM_KERN_ERR "check_one_sigio failed to allocate a "
		       "pty\n");
		वापस;
	पूर्ण

	/* Not now, but complain so we now where we failed. */
	err = raw(master);
	अगर (err < 0) अणु
		prपूर्णांकk(UM_KERN_ERR "check_one_sigio : raw failed, errno = %d\n",
		      -err);
		वापस;
	पूर्ण

	err = async_pty(master, slave);
	अगर (err < 0) अणु
		prपूर्णांकk(UM_KERN_ERR "check_one_sigio : sigio_async failed, "
		       "err = %d\n", -err);
		वापस;
	पूर्ण

	अगर (sigaction(SIGIO, शून्य, &old) < 0) अणु
		prपूर्णांकk(UM_KERN_ERR "check_one_sigio : sigaction 1 failed, "
		       "errno = %d\n", त्रुटि_सं);
		वापस;
	पूर्ण

	new = old;
	new.sa_handler = handler;
	अगर (sigaction(SIGIO, &new, शून्य) < 0) अणु
		prपूर्णांकk(UM_KERN_ERR "check_one_sigio : sigaction 2 failed, "
		       "errno = %d\n", त्रुटि_सं);
		वापस;
	पूर्ण

	got_sigio = 0;
	(*proc)(master, slave);

	बंद(master);
	बंद(slave);

	अगर (sigaction(SIGIO, &old, शून्य) < 0)
		prपूर्णांकk(UM_KERN_ERR "check_one_sigio : sigaction 3 failed, "
		       "errno = %d\n", त्रुटि_सं);
पूर्ण

अटल व्योम tty_output(पूर्णांक master, पूर्णांक slave)
अणु
	पूर्णांक n;
	अक्षर buf[512];

	prपूर्णांकk(UM_KERN_INFO "Checking that host ptys support output SIGIO...");

	स_रखो(buf, 0, माप(buf));

	जबतक (ग_लिखो(master, buf, माप(buf)) > 0) ;
	अगर (त्रुटि_सं != EAGAIN)
		prपूर्णांकk(UM_KERN_ERR "tty_output : write failed, errno = %d\n",
		       त्रुटि_सं);
	जबतक (((n = पढ़ो(slave, buf, माप(buf))) > 0) &&
	       !(अणु barrier(); got_sigio; पूर्ण))
		;

	अगर (got_sigio) अणु
		prपूर्णांकk(UM_KERN_CONT "Yes\n");
		pty_output_sigio = 1;
	पूर्ण अन्यथा अगर (n == -EAGAIN)
		prपूर्णांकk(UM_KERN_CONT "No, enabling workaround\n");
	अन्यथा
		prपूर्णांकk(UM_KERN_CONT "tty_output : read failed, err = %d\n", n);
पूर्ण

अटल व्योम __init check_sigio(व्योम)
अणु
	अगर ((access("/dev/ptmx", R_OK) < 0) &&
	    (access("/dev/ptyp0", R_OK) < 0)) अणु
		prपूर्णांकk(UM_KERN_WARNING "No pseudo-terminals available - "
		       "skipping pty SIGIO check\n");
		वापस;
	पूर्ण
	check_one_sigio(tty_output);
पूर्ण

/* Here because it only करोes the SIGIO testing क्रम now */
व्योम __init os_check_bugs(व्योम)
अणु
	check_sigio();
पूर्ण
