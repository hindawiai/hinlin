<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2002 - 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 */

#समावेश <मानककोष.स>
#समावेश <unistd.h>
#समावेश <त्रुटिसं.स>
#समावेश <sched.h>
#समावेश <linux/सीमा.स>
#समावेश <sys/socket.h>
#समावेश <sys/रुको.h>
#समावेश <kern_util.h>
#समावेश <os.h>
#समावेश <um_दो_स्मृति.h>

काष्ठा helper_data अणु
	व्योम (*pre_exec)(व्योम*);
	व्योम *pre_data;
	अक्षर **argv;
	पूर्णांक fd;
	अक्षर *buf;
पूर्ण;

अटल पूर्णांक helper_child(व्योम *arg)
अणु
	काष्ठा helper_data *data = arg;
	अक्षर **argv = data->argv;
	पूर्णांक err, ret;

	अगर (data->pre_exec != शून्य)
		(*data->pre_exec)(data->pre_data);
	err = execvp_noalloc(data->buf, argv[0], argv);

	/* If the exec succeeds, we करोn't get here */
	CATCH_EINTR(ret = ग_लिखो(data->fd, &err, माप(err)));

	वापस 0;
पूर्ण

/* Returns either the pid of the child process we run or -E* on failure. */
पूर्णांक run_helper(व्योम (*pre_exec)(व्योम *), व्योम *pre_data, अक्षर **argv)
अणु
	काष्ठा helper_data data;
	अचिन्हित दीर्घ stack, sp;
	पूर्णांक pid, fds[2], ret, n;

	stack = alloc_stack(0, __cant_sleep());
	अगर (stack == 0)
		वापस -ENOMEM;

	ret = socketpair(AF_UNIX, SOCK_STREAM, 0, fds);
	अगर (ret < 0) अणु
		ret = -त्रुटि_सं;
		prपूर्णांकk(UM_KERN_ERR "run_helper : pipe failed, errno = %d\n",
		       त्रुटि_सं);
		जाओ out_मुक्त;
	पूर्ण

	ret = os_set_exec_बंद(fds[1]);
	अगर (ret < 0) अणु
		prपूर्णांकk(UM_KERN_ERR "run_helper : setting FD_CLOEXEC failed, "
		       "ret = %d\n", -ret);
		जाओ out_बंद;
	पूर्ण

	sp = stack + UM_KERN_PAGE_SIZE - माप(व्योम *);
	data.pre_exec = pre_exec;
	data.pre_data = pre_data;
	data.argv = argv;
	data.fd = fds[1];
	data.buf = __cant_sleep() ? uml_kदो_स्मृति(PATH_MAX, UM_GFP_ATOMIC) :
					uml_kदो_स्मृति(PATH_MAX, UM_GFP_KERNEL);
	pid = clone(helper_child, (व्योम *) sp, CLONE_VM, &data);
	अगर (pid < 0) अणु
		ret = -त्रुटि_सं;
		prपूर्णांकk(UM_KERN_ERR "run_helper : clone failed, errno = %d\n",
		       त्रुटि_सं);
		जाओ out_मुक्त2;
	पूर्ण

	बंद(fds[1]);
	fds[1] = -1;

	/*
	 * Read the त्रुटि_सं value from the child, अगर the exec failed, or get 0 अगर
	 * the exec succeeded because the pipe fd was set as बंद-on-exec.
	 */
	n = पढ़ो(fds[0], &ret, माप(ret));
	अगर (n == 0) अणु
		ret = pid;
	पूर्ण अन्यथा अणु
		अगर (n < 0) अणु
			n = -त्रुटि_सं;
			prपूर्णांकk(UM_KERN_ERR "run_helper : read on pipe failed, "
			       "ret = %d\n", -n);
			ret = n;
		पूर्ण
		CATCH_EINTR(रुकोpid(pid, शून्य, __WALL));
	पूर्ण

out_मुक्त2:
	kमुक्त(data.buf);
out_बंद:
	अगर (fds[1] != -1)
		बंद(fds[1]);
	बंद(fds[0]);
out_मुक्त:
	मुक्त_stack(stack, 0);
	वापस ret;
पूर्ण

पूर्णांक run_helper_thपढ़ो(पूर्णांक (*proc)(व्योम *), व्योम *arg, अचिन्हित पूर्णांक flags,
		      अचिन्हित दीर्घ *stack_out)
अणु
	अचिन्हित दीर्घ stack, sp;
	पूर्णांक pid, status, err;

	stack = alloc_stack(0, __cant_sleep());
	अगर (stack == 0)
		वापस -ENOMEM;

	sp = stack + UM_KERN_PAGE_SIZE - माप(व्योम *);
	pid = clone(proc, (व्योम *) sp, flags, arg);
	अगर (pid < 0) अणु
		err = -त्रुटि_सं;
		prपूर्णांकk(UM_KERN_ERR "run_helper_thread : clone failed, "
		       "errno = %d\n", त्रुटि_सं);
		वापस err;
	पूर्ण
	अगर (stack_out == शून्य) अणु
		CATCH_EINTR(pid = रुकोpid(pid, &status, __WALL));
		अगर (pid < 0) अणु
			err = -त्रुटि_सं;
			prपूर्णांकk(UM_KERN_ERR "run_helper_thread - wait failed, "
			       "errno = %d\n", त्रुटि_सं);
			pid = err;
		पूर्ण
		अगर (!WIFEXITED(status) || (WEXITSTATUS(status) != 0))
			prपूर्णांकk(UM_KERN_ERR "run_helper_thread - thread "
			       "returned status 0x%x\n", status);
		मुक्त_stack(stack, 0);
	पूर्ण अन्यथा
		*stack_out = stack;
	वापस pid;
पूर्ण

पूर्णांक helper_रुको(पूर्णांक pid)
अणु
	पूर्णांक ret, status;
	पूर्णांक wflags = __WALL;

	CATCH_EINTR(ret = रुकोpid(pid, &status, wflags));
	अगर (ret < 0) अणु
		prपूर्णांकk(UM_KERN_ERR "helper_wait : waitpid process %d failed, "
		       "errno = %d\n", pid, त्रुटि_सं);
		वापस -त्रुटि_सं;
	पूर्ण अन्यथा अगर (!WIFEXITED(status) || WEXITSTATUS(status) != 0) अणु
		prपूर्णांकk(UM_KERN_ERR "helper_wait : process %d exited with "
		       "status 0x%x\n", pid, status);
		वापस -ECHILD;
	पूर्ण अन्यथा
		वापस 0;
पूर्ण
