<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2000 - 2007 Jeff Dike (jdike@अणुlinux.पूर्णांकel,addtoitपूर्ण.com)
 */

#समावेश <मानककोष.स>
#समावेश <unistd.h>
#समावेश <त्रुटिसं.स>
#समावेश <sched.h>
#समावेश <संकेत.स>
#समावेश <termios.h>
#समावेश <sys/ioctl.h>
#समावेश "chan_user.h"
#समावेश <os.h>
#समावेश <um_दो_स्मृति.h>

व्योम generic_बंद(पूर्णांक fd, व्योम *unused)
अणु
	बंद(fd);
पूर्ण

पूर्णांक generic_पढ़ो(पूर्णांक fd, अक्षर *c_out, व्योम *unused)
अणु
	पूर्णांक n;

	n = पढ़ो(fd, c_out, माप(*c_out));
	अगर (n > 0)
		वापस n;
	अन्यथा अगर (n == 0)
		वापस -EIO;
	अन्यथा अगर (त्रुटि_सं == EAGAIN)
		वापस 0;
	वापस -त्रुटि_सं;
पूर्ण

/* XXX Trivial wrapper around ग_लिखो */

पूर्णांक generic_ग_लिखो(पूर्णांक fd, स्थिर अक्षर *buf, पूर्णांक n, व्योम *unused)
अणु
	पूर्णांक err;

	err = ग_लिखो(fd, buf, n);
	अगर (err > 0)
		वापस err;
	अन्यथा अगर (त्रुटि_सं == EAGAIN)
		वापस 0;
	अन्यथा अगर (err == 0)
		वापस -EIO;
	वापस -त्रुटि_सं;
पूर्ण

पूर्णांक generic_winकरोw_size(पूर्णांक fd, व्योम *unused, अचिन्हित लघु *rows_out,
			अचिन्हित लघु *cols_out)
अणु
	काष्ठा winsize size;
	पूर्णांक ret;

	अगर (ioctl(fd, TIOCGWINSZ, &size) < 0)
		वापस -त्रुटि_सं;

	ret = ((*rows_out != size.ws_row) || (*cols_out != size.ws_col));

	*rows_out = size.ws_row;
	*cols_out = size.ws_col;

	वापस ret;
पूर्ण

व्योम generic_मुक्त(व्योम *data)
अणु
	kमुक्त(data);
पूर्ण

पूर्णांक generic_console_ग_लिखो(पूर्णांक fd, स्थिर अक्षर *buf, पूर्णांक n)
अणु
	sigset_t old, no_sigio;
	काष्ठा termios save, new;
	पूर्णांक err;

	अगर (isatty(fd)) अणु
		sigemptyset(&no_sigio);
		sigaddset(&no_sigio, SIGIO);
		अगर (sigprocmask(SIG_BLOCK, &no_sigio, &old))
			जाओ error;

		CATCH_EINTR(err = tcgetattr(fd, &save));
		अगर (err)
			जाओ error;
		new = save;
		/*
		 * The terminal becomes a bit less raw, to handle \न also as
		 * "Carriage Return", not only as "New Line". Otherwise, the new
		 * line won't start at the first column.
		 */
		new.c_oflag |= OPOST;
		CATCH_EINTR(err = tcsetattr(fd, TCSAFLUSH, &new));
		अगर (err)
			जाओ error;
	पूर्ण
	err = generic_ग_लिखो(fd, buf, n, शून्य);
	/*
	 * Restore raw mode, in any हाल; we *must* ignore any error apart
	 * EINTR, except क्रम debug.
	 */
	अगर (isatty(fd)) अणु
		CATCH_EINTR(tcsetattr(fd, TCSAFLUSH, &save));
		sigprocmask(SIG_SETMASK, &old, शून्य);
	पूर्ण

	वापस err;
error:
	वापस -त्रुटि_सं;
पूर्ण

/*
 * UML SIGWINCH handling
 *
 * The poपूर्णांक of this is to handle SIGWINCH on consoles which have host
 * ttys and relay them inside UML to whatever might be running on the
 * console and cares about the winकरोw size (since SIGWINCH notअगरies
 * about terminal size changes).
 *
 * So, we have a separate thपढ़ो क्रम each host tty attached to a UML
 * device (side-issue - I'm annoyed that one thread can't have
 * multiple controlling ttys क्रम the purpose of handling SIGWINCH, but
 * I imagine there are other reasons that करोesn't make any sense).
 *
 * SIGWINCH can't be received synchronously, so you have to set up to
 * receive it as a संकेत.  That being the हाल, अगर you are going to
 * रुको क्रम it, it is convenient to sit in संक_रोको() and रुको क्रम
 * the संकेत to bounce you out of it (see below क्रम how we make sure
 * to निकास only on SIGWINCH).
 */

अटल व्योम winch_handler(पूर्णांक sig)
अणु
पूर्ण

काष्ठा winch_data अणु
	पूर्णांक pty_fd;
	पूर्णांक pipe_fd;
पूर्ण;

अटल पूर्णांक winch_thपढ़ो(व्योम *arg)
अणु
	काष्ठा winch_data *data = arg;
	sigset_t sigs;
	पूर्णांक pty_fd, pipe_fd;
	पूर्णांक count;
	अक्षर c = 1;

	pty_fd = data->pty_fd;
	pipe_fd = data->pipe_fd;
	count = ग_लिखो(pipe_fd, &c, माप(c));
	अगर (count != माप(c))
		prपूर्णांकk(UM_KERN_ERR "winch_thread : failed to write "
		       "synchronization byte, err = %d\n", -count);

	/*
	 * We are not using संक_छोड़ो on purpose, so करोn't fix it as I thought to
	 * करो! If using संक_छोड़ो, the संक_रोको() call below would not stop on
	 * SIGWINCH.
	 */

	संकेत(SIGWINCH, winch_handler);
	sigfillset(&sigs);
	/* Block all संकेतs possible. */
	अगर (sigprocmask(SIG_SETMASK, &sigs, शून्य) < 0) अणु
		prपूर्णांकk(UM_KERN_ERR "winch_thread : sigprocmask failed, "
		       "errno = %d\n", त्रुटि_सं);
		निकास(1);
	पूर्ण
	/* In संक_रोको(), block anything अन्यथा than SIGWINCH. */
	sigdअन्यथाt(&sigs, SIGWINCH);

	अगर (setsid() < 0) अणु
		prपूर्णांकk(UM_KERN_ERR "winch_thread : setsid failed, errno = %d\n",
		       त्रुटि_सं);
		निकास(1);
	पूर्ण

	अगर (ioctl(pty_fd, TIOCSCTTY, 0) < 0) अणु
		prपूर्णांकk(UM_KERN_ERR "winch_thread : TIOCSCTTY failed on "
		       "fd %d err = %d\n", pty_fd, त्रुटि_सं);
		निकास(1);
	पूर्ण

	अगर (tcsetpgrp(pty_fd, os_getpid()) < 0) अणु
		prपूर्णांकk(UM_KERN_ERR "winch_thread : tcsetpgrp failed on "
		       "fd %d err = %d\n", pty_fd, त्रुटि_सं);
		निकास(1);
	पूर्ण

	/*
	 * These are synchronization calls between various UML thपढ़ोs on the
	 * host - since they are not dअगरferent kernel thपढ़ोs, we cannot use
	 * kernel semaphores. We करोn't use SysV semaphores because they are
	 * persistent.
	 */
	count = पढ़ो(pipe_fd, &c, माप(c));
	अगर (count != माप(c))
		prपूर्णांकk(UM_KERN_ERR "winch_thread : failed to read "
		       "synchronization byte, err = %d\n", त्रुटि_सं);

	जबतक(1) अणु
		/*
		 * This will be पूर्णांकerrupted by SIGWINCH only, since
		 * other संकेतs are blocked.
		 */
		संक_रोको(&sigs);

		count = ग_लिखो(pipe_fd, &c, माप(c));
		अगर (count != माप(c))
			prपूर्णांकk(UM_KERN_ERR "winch_thread : write failed, "
			       "err = %d\n", त्रुटि_सं);
	पूर्ण
पूर्ण

अटल पूर्णांक winch_tramp(पूर्णांक fd, काष्ठा tty_port *port, पूर्णांक *fd_out,
		       अचिन्हित दीर्घ *stack_out)
अणु
	काष्ठा winch_data data;
	पूर्णांक fds[2], n, err;
	अक्षर c;

	err = os_pipe(fds, 1, 1);
	अगर (err < 0) अणु
		prपूर्णांकk(UM_KERN_ERR "winch_tramp : os_pipe failed, err = %d\n",
		       -err);
		जाओ out;
	पूर्ण

	data = ((काष्ठा winch_data) अणु .pty_fd 		= fd,
				      .pipe_fd 		= fds[1] पूर्ण );
	/*
	 * CLONE_खाताS so this thपढ़ो करोesn't hold खोलो files which are खोलो
	 * now, but later बंदd in a dअगरferent thपढ़ो.  This is a
	 * problem with /dev/net/tun, which अगर held खोलो by this
	 * thपढ़ो, prevents the TUN/TAP device from being reused.
	 */
	err = run_helper_thपढ़ो(winch_thपढ़ो, &data, CLONE_खाताS, stack_out);
	अगर (err < 0) अणु
		prपूर्णांकk(UM_KERN_ERR "fork of winch_thread failed - errno = %d\n",
		       -err);
		जाओ out_बंद;
	पूर्ण

	*fd_out = fds[0];
	n = पढ़ो(fds[0], &c, माप(c));
	अगर (n != माप(c)) अणु
		prपूर्णांकk(UM_KERN_ERR "winch_tramp : failed to read "
		       "synchronization byte\n");
		prपूर्णांकk(UM_KERN_ERR "read failed, err = %d\n", त्रुटि_सं);
		prपूर्णांकk(UM_KERN_ERR "fd %d will not support SIGWINCH\n", fd);
		err = -EINVAL;
		जाओ out_बंद;
	पूर्ण

	अगर (os_set_fd_block(*fd_out, 0)) अणु
		prपूर्णांकk(UM_KERN_ERR "winch_tramp: failed to set thread_fd "
		       "non-blocking.\n");
		जाओ out_बंद;
	पूर्ण

	वापस err;

 out_बंद:
	बंद(fds[1]);
	बंद(fds[0]);
 out:
	वापस err;
पूर्ण

व्योम रेजिस्टर_winch(पूर्णांक fd, काष्ठा tty_port *port)
अणु
	अचिन्हित दीर्घ stack;
	पूर्णांक pid, thपढ़ो, count, thपढ़ो_fd = -1;
	अक्षर c = 1;

	अगर (!isatty(fd))
		वापस;

	pid = tcgetpgrp(fd);
	अगर (is_skas_winch(pid, fd, port)) अणु
		रेजिस्टर_winch_irq(-1, fd, -1, port, 0);
		वापस;
	पूर्ण

	अगर (pid == -1) अणु
		thपढ़ो = winch_tramp(fd, port, &thपढ़ो_fd, &stack);
		अगर (thपढ़ो < 0)
			वापस;

		रेजिस्टर_winch_irq(thपढ़ो_fd, fd, thपढ़ो, port, stack);

		count = ग_लिखो(thपढ़ो_fd, &c, माप(c));
		अगर (count != माप(c))
			prपूर्णांकk(UM_KERN_ERR "register_winch : failed to write "
			       "synchronization byte, err = %d\n", त्रुटि_सं);
	पूर्ण
पूर्ण
