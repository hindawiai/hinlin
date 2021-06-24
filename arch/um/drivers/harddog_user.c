<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2002 - 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 */

#समावेश <मानकपन.स>
#समावेश <unistd.h>
#समावेश <त्रुटिसं.स>
#समावेश <os.h>

काष्ठा करोg_data अणु
	पूर्णांक मानक_निवेश_fd;
	पूर्णांक मानक_निकास_fd;
	पूर्णांक बंद_me[2];
पूर्ण;

अटल व्योम pre_exec(व्योम *d)
अणु
	काष्ठा करोg_data *data = d;

	dup2(data->मानक_निवेश_fd, 0);
	dup2(data->मानक_निकास_fd, 1);
	dup2(data->मानक_निकास_fd, 2);
	बंद(data->मानक_निवेश_fd);
	बंद(data->मानक_निकास_fd);
	बंद(data->बंद_me[0]);
	बंद(data->बंद_me[1]);
पूर्ण

पूर्णांक start_watchकरोg(पूर्णांक *in_fd_ret, पूर्णांक *out_fd_ret, अक्षर *sock)
अणु
	काष्ठा करोg_data data;
	पूर्णांक in_fds[2], out_fds[2], pid, n, err;
	अक्षर pid_buf[माप("nnnnnnn\0")], c;
	अक्षर *pid_args[] = अणु "/usr/bin/uml_watchdog", "-pid", pid_buf, शून्य पूर्ण;
	अक्षर *mconsole_args[] = अणु "/usr/bin/uml_watchdog", "-mconsole", शून्य,
				  शून्य पूर्ण;
	अक्षर **args = शून्य;

	err = os_pipe(in_fds, 1, 0);
	अगर (err < 0) अणु
		prपूर्णांकk("harddog_open - os_pipe failed, err = %d\n", -err);
		जाओ out;
	पूर्ण

	err = os_pipe(out_fds, 1, 0);
	अगर (err < 0) अणु
		prपूर्णांकk("harddog_open - os_pipe failed, err = %d\n", -err);
		जाओ out_बंद_in;
	पूर्ण

	data.मानक_निवेश_fd = out_fds[0];
	data.मानक_निकास_fd = in_fds[1];
	data.बंद_me[0] = out_fds[1];
	data.बंद_me[1] = in_fds[0];

	अगर (sock != शून्य) अणु
		mconsole_args[2] = sock;
		args = mconsole_args;
	पूर्ण
	अन्यथा अणु
		/* XXX The os_getpid() is not SMP correct */
		प्र_लिखो(pid_buf, "%d", os_getpid());
		args = pid_args;
	पूर्ण

	pid = run_helper(pre_exec, &data, args);

	बंद(out_fds[0]);
	बंद(in_fds[1]);

	अगर (pid < 0) अणु
		err = -pid;
		prपूर्णांकk("harddog_open - run_helper failed, errno = %d\n", -err);
		जाओ out_बंद_out;
	पूर्ण

	n = पढ़ो(in_fds[0], &c, माप(c));
	अगर (n == 0) अणु
		prपूर्णांकk("harddog_open - EOF on watchdog pipe\n");
		helper_रुको(pid);
		err = -EIO;
		जाओ out_बंद_out;
	पूर्ण
	अन्यथा अगर (n < 0) अणु
		prपूर्णांकk("harddog_open - read of watchdog pipe failed, "
		       "err = %d\n", त्रुटि_सं);
		helper_रुको(pid);
		err = n;
		जाओ out_बंद_out;
	पूर्ण
	*in_fd_ret = in_fds[0];
	*out_fd_ret = out_fds[1];
	वापस 0;

 out_बंद_in:
	बंद(in_fds[0]);
	बंद(in_fds[1]);
 out_बंद_out:
	बंद(out_fds[0]);
	बंद(out_fds[1]);
 out:
	वापस err;
पूर्ण

व्योम stop_watchकरोg(पूर्णांक in_fd, पूर्णांक out_fd)
अणु
	बंद(in_fd);
	बंद(out_fd);
पूर्ण

पूर्णांक ping_watchकरोg(पूर्णांक fd)
अणु
	पूर्णांक n;
	अक्षर c = '\n';

	n = ग_लिखो(fd, &c, माप(c));
	अगर (n != माप(c)) अणु
		prपूर्णांकk("ping_watchdog - write failed, ret = %d, err = %d\n",
		       n, त्रुटि_सं);
		अगर (n < 0)
			वापस n;
		वापस -EIO;
	पूर्ण
	वापस 1;

पूर्ण
