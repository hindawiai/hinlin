<शैली गुरु>
#समावेश <संकेत.स>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <unistd.h>
#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <माला.स>
#समावेश <मानकघोष.स>
#समावेश <sys/sysmacros.h>
#समावेश <sys/types.h>
#समावेश <sys/रुको.h>
#समावेश <sys/socket.h>
#समावेश <sys/स्थिति.स>
#समावेश <sys/mman.h>
#समावेश <sys/syscall.h>
#समावेश <sys/user.h>
#समावेश <sys/ioctl.h>
#समावेश <sys/ptrace.h>
#समावेश <sys/mount.h>
#समावेश <linux/सीमा.स>
#समावेश <linux/filter.h>
#समावेश <linux/seccomp.h>

#घोषणा ARRAY_SIZE(x) (माप(x) / माप(*(x)))

अटल पूर्णांक seccomp(अचिन्हित पूर्णांक op, अचिन्हित पूर्णांक flags, व्योम *args)
अणु
	त्रुटि_सं = 0;
	वापस syscall(__NR_seccomp, op, flags, args);
पूर्ण

अटल पूर्णांक send_fd(पूर्णांक sock, पूर्णांक fd)
अणु
	काष्ठा msghdr msg = अणुपूर्ण;
	काष्ठा cmsghdr *cmsg;
	अक्षर buf[CMSG_SPACE(माप(पूर्णांक))] = अणु0पूर्ण, c = 'c';
	काष्ठा iovec io = अणु
		.iov_base = &c,
		.iov_len = 1,
	पूर्ण;

	msg.msg_iov = &io;
	msg.msg_iovlen = 1;
	msg.msg_control = buf;
	msg.msg_controllen = माप(buf);
	cmsg = CMSG_FIRSTHDR(&msg);
	cmsg->cmsg_level = SOL_SOCKET;
	cmsg->cmsg_type = SCM_RIGHTS;
	cmsg->cmsg_len = CMSG_LEN(माप(पूर्णांक));
	*((पूर्णांक *)CMSG_DATA(cmsg)) = fd;
	msg.msg_controllen = cmsg->cmsg_len;

	अगर (sendmsg(sock, &msg, 0) < 0) अणु
		लिखो_त्रुटि("sendmsg");
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक recv_fd(पूर्णांक sock)
अणु
	काष्ठा msghdr msg = अणुपूर्ण;
	काष्ठा cmsghdr *cmsg;
	अक्षर buf[CMSG_SPACE(माप(पूर्णांक))] = अणु0पूर्ण, c = 'c';
	काष्ठा iovec io = अणु
		.iov_base = &c,
		.iov_len = 1,
	पूर्ण;

	msg.msg_iov = &io;
	msg.msg_iovlen = 1;
	msg.msg_control = buf;
	msg.msg_controllen = माप(buf);

	अगर (recvmsg(sock, &msg, 0) < 0) अणु
		लिखो_त्रुटि("recvmsg");
		वापस -1;
	पूर्ण

	cmsg = CMSG_FIRSTHDR(&msg);

	वापस *((पूर्णांक *)CMSG_DATA(cmsg));
पूर्ण

अटल पूर्णांक user_trap_syscall(पूर्णांक nr, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा sock_filter filter[] = अणु
		BPF_STMT(BPF_LD+BPF_W+BPF_ABS,
			दुरत्व(काष्ठा seccomp_data, nr)),
		BPF_JUMP(BPF_JMP+BPF_JEQ+BPF_K, nr, 0, 1),
		BPF_STMT(BPF_RET+BPF_K, SECCOMP_RET_USER_NOTIF),
		BPF_STMT(BPF_RET+BPF_K, SECCOMP_RET_ALLOW),
	पूर्ण;

	काष्ठा sock_fprog prog = अणु
		.len = (अचिन्हित लघु)ARRAY_SIZE(filter),
		.filter = filter,
	पूर्ण;

	वापस seccomp(SECCOMP_SET_MODE_FILTER, flags, &prog);
पूर्ण

अटल पूर्णांक handle_req(काष्ठा seccomp_notअगर *req,
		      काष्ठा seccomp_notअगर_resp *resp, पूर्णांक listener)
अणु
	अक्षर path[PATH_MAX], source[PATH_MAX], target[PATH_MAX];
	पूर्णांक ret = -1, mem;

	resp->id = req->id;
	resp->error = -EPERM;
	resp->val = 0;

	अगर (req->data.nr != __NR_mount) अणु
		ख_लिखो(मानक_त्रुटि, "huh? trapped something besides mount? %d\n", req->data.nr);
		वापस -1;
	पूर्ण

	/* Only allow bind mounts. */
	अगर (!(req->data.args[3] & MS_BIND))
		वापस 0;

	/*
	 * Ok, let's read the task's memory to see where they wanted their
	 * mount to go.
	 */
	snम_लिखो(path, माप(path), "/proc/%d/mem", req->pid);
	mem = खोलो(path, O_RDONLY);
	अगर (mem < 0) अणु
		लिखो_त्रुटि("open mem");
		वापस -1;
	पूर्ण

	/*
	 * Now we aव्योम a TOCTOU: we referred to a pid by its pid, but since
	 * the pid that made the syscall may have died, we need to confirm that
	 * the pid is still valid after we खोलो its /proc/pid/mem file. We can
	 * ask the listener fd this as follows.
	 *
	 * Note that this check should occur *after* any task-specअगरic
	 * resources are खोलोed, to make sure that the task has not died and
	 * we're not wrongly reading someone else's state in order to make
	 * decisions.
	 */
	अगर (ioctl(listener, SECCOMP_IOCTL_NOTIF_ID_VALID, &req->id) < 0) अणु
		ख_लिखो(मानक_त्रुटि, "task died before we could map its memory\n");
		जाओ out;
	पूर्ण

	/*
	 * Phew, we've got the right /proc/pid/mem. Now we can पढ़ो it. Note
	 * that to aव्योम another TOCTOU, we should पढ़ो all of the poपूर्णांकer args
	 * beक्रमe we decide to allow the syscall.
	 */
	अगर (lseek(mem, req->data.args[0], शुरू_से) < 0) अणु
		लिखो_त्रुटि("seek");
		जाओ out;
	पूर्ण

	ret = पढ़ो(mem, source, माप(source));
	अगर (ret < 0) अणु
		लिखो_त्रुटि("read");
		जाओ out;
	पूर्ण

	अगर (lseek(mem, req->data.args[1], शुरू_से) < 0) अणु
		लिखो_त्रुटि("seek");
		जाओ out;
	पूर्ण

	ret = पढ़ो(mem, target, माप(target));
	अगर (ret < 0) अणु
		लिखो_त्रुटि("read");
		जाओ out;
	पूर्ण

	/*
	 * Our policy is to only allow bind mounts inside /पंचांगp. This isn't very
	 * पूर्णांकeresting, because we could करो unprivlieged bind mounts with user
	 * namespaces alपढ़ोy, but you get the idea.
	 */
	अगर (!म_भेदन(source, "/tmp/", 5) && !म_भेदन(target, "/tmp/", 5)) अणु
		अगर (mount(source, target, शून्य, req->data.args[3], शून्य) < 0) अणु
			ret = -1;
			लिखो_त्रुटि("actual mount");
			जाओ out;
		पूर्ण
		resp->error = 0;
	पूर्ण

	/* Even अगर we didn't allow it because of policy, generating the
	 * response was be a success, because we want to tell the worker EPERM.
	 */
	ret = 0;

out:
	बंद(mem);
	वापस ret;
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	पूर्णांक sk_pair[2], ret = 1, status, listener;
	pid_t worker = 0 , tracer = 0;

	अगर (socketpair(PF_LOCAL, SOCK_SEQPACKET, 0, sk_pair) < 0) अणु
		लिखो_त्रुटि("socketpair");
		वापस 1;
	पूर्ण

	worker = विभाजन();
	अगर (worker < 0) अणु
		लिखो_त्रुटि("fork");
		जाओ बंद_pair;
	पूर्ण

	अगर (worker == 0) अणु
		listener = user_trap_syscall(__NR_mount,
					     SECCOMP_FILTER_FLAG_NEW_LISTENER);
		अगर (listener < 0) अणु
			लिखो_त्रुटि("seccomp");
			निकास(1);
		पूर्ण

		/*
		 * Drop privileges. We definitely can't mount as uid 1000.
		 */
		अगर (setuid(1000) < 0) अणु
			लिखो_त्रुटि("setuid");
			निकास(1);
		पूर्ण

		/*
		 * Send the listener to the parent; also serves as
		 * synchronization.
		 */
		अगर (send_fd(sk_pair[1], listener) < 0)
			निकास(1);
		बंद(listener);

		अगर (सूची_गढ़ो("/tmp/foo", 0755) < 0) अणु
			लिखो_त्रुटि("mkdir");
			निकास(1);
		पूर्ण

		/*
		 * Try a bad mount just क्रम grins.
		 */
		अगर (mount("/dev/sda", "/tmp/foo", शून्य, 0, शून्य) != -1) अणु
			ख_लिखो(मानक_त्रुटि, "huh? mounted /dev/sda?\n");
			निकास(1);
		पूर्ण

		अगर (त्रुटि_सं != EPERM) अणु
			लिखो_त्रुटि("bad error from mount");
			निकास(1);
		पूर्ण

		/*
		 * Ok, we expect this one to succeed.
		 */
		अगर (mount("/tmp/foo", "/tmp/foo", शून्य, MS_BIND, शून्य) < 0) अणु
			लिखो_त्रुटि("mount");
			निकास(1);
		पूर्ण

		निकास(0);
	पूर्ण

	/*
	 * Get the listener from the child.
	 */
	listener = recv_fd(sk_pair[0]);
	अगर (listener < 0)
		जाओ out_समाप्त;

	/*
	 * Fork a task to handle the requests. This isn't strictly necessary,
	 * but it makes the particular writing of this sample easier, since we
	 * can just रुको ofr the tracee to निकास and समाप्त the tracer.
	 */
	tracer = विभाजन();
	अगर (tracer < 0) अणु
		लिखो_त्रुटि("fork");
		जाओ out_समाप्त;
	पूर्ण

	अगर (tracer == 0) अणु
		काष्ठा seccomp_notअगर *req;
		काष्ठा seccomp_notअगर_resp *resp;
		काष्ठा seccomp_notअगर_sizes sizes;

		अगर (seccomp(SECCOMP_GET_NOTIF_SIZES, 0, &sizes) < 0) अणु
			लिखो_त्रुटि("seccomp(GET_NOTIF_SIZES)");
			जाओ out_बंद;
		पूर्ण

		req = दो_स्मृति(sizes.seccomp_notअगर);
		अगर (!req)
			जाओ out_बंद;

		resp = दो_स्मृति(sizes.seccomp_notअगर_resp);
		अगर (!resp)
			जाओ out_req;
		स_रखो(resp, 0, sizes.seccomp_notअगर_resp);

		जबतक (1) अणु
			स_रखो(req, 0, sizes.seccomp_notअगर);
			अगर (ioctl(listener, SECCOMP_IOCTL_NOTIF_RECV, req)) अणु
				लिखो_त्रुटि("ioctl recv");
				जाओ out_resp;
			पूर्ण

			अगर (handle_req(req, resp, listener) < 0)
				जाओ out_resp;

			/*
			 * ENOENT here means that the task may have gotten a
			 * संकेत and restarted the syscall. It's up to the
			 * handler to decide what to करो in this हाल, but क्रम
			 * the sample code, we just ignore it. Probably
			 * something better should happen, like unकरोing the
			 * mount, or keeping track of the args to make sure we
			 * करोn't करो it again.
			 */
			अगर (ioctl(listener, SECCOMP_IOCTL_NOTIF_SEND, resp) < 0 &&
			    त्रुटि_सं != ENOENT) अणु
				लिखो_त्रुटि("ioctl send");
				जाओ out_resp;
			पूर्ण
		पूर्ण
out_resp:
		मुक्त(resp);
out_req:
		मुक्त(req);
out_बंद:
		बंद(listener);
		निकास(1);
	पूर्ण

	बंद(listener);

	अगर (रुकोpid(worker, &status, 0) != worker) अणु
		लिखो_त्रुटि("waitpid");
		जाओ out_समाप्त;
	पूर्ण

	अगर (umount2("/tmp/foo", MNT_DETACH) < 0 && त्रुटि_सं != EINVAL) अणु
		लिखो_त्रुटि("umount2");
		जाओ out_समाप्त;
	पूर्ण

	अगर (हटाओ("/tmp/foo") < 0 && त्रुटि_सं != ENOENT) अणु
		लिखो_त्रुटि("remove");
		निकास(1);
	पूर्ण

	अगर (!WIFEXITED(status) || WEXITSTATUS(status)) अणु
		ख_लिखो(मानक_त्रुटि, "worker exited nonzero\n");
		जाओ out_समाप्त;
	पूर्ण

	ret = 0;

out_समाप्त:
	अगर (tracer > 0)
		समाप्त(tracer, SIGKILL);
	अगर (worker > 0)
		समाप्त(worker, SIGKILL);

बंद_pair:
	बंद(sk_pair[0]);
	बंद(sk_pair[1]);
	वापस ret;
पूर्ण
