<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/*
 * Copyright (C) 2020 Google LLC.
 */

#समावेश <test_progs.h>
#समावेश <linux/सीमा.स>

#समावेश "bprm_opts.skel.h"
#समावेश "network_helpers.h"

#अगर_अघोषित __NR_pidfd_खोलो
#घोषणा __NR_pidfd_खोलो 434
#पूर्ण_अगर

अटल स्थिर अक्षर * स्थिर bash_envp[] = अणु "TMPDIR=shouldnotbeset", शून्य पूर्ण;

अटल अंतरभूत पूर्णांक sys_pidfd_खोलो(pid_t pid, अचिन्हित पूर्णांक flags)
अणु
	वापस syscall(__NR_pidfd_खोलो, pid, flags);
पूर्ण

अटल पूर्णांक update_storage(पूर्णांक map_fd, पूर्णांक secureexec)
अणु
	पूर्णांक task_fd, ret = 0;

	task_fd = sys_pidfd_खोलो(getpid(), 0);
	अगर (task_fd < 0)
		वापस त्रुटि_सं;

	ret = bpf_map_update_elem(map_fd, &task_fd, &secureexec, BPF_NOEXIST);
	अगर (ret)
		ret = त्रुटि_सं;

	बंद(task_fd);
	वापस ret;
पूर्ण

अटल पूर्णांक run_set_secureexec(पूर्णांक map_fd, पूर्णांक secureexec)
अणु
	पूर्णांक child_pid, child_status, ret, null_fd;

	child_pid = विभाजन();
	अगर (child_pid == 0) अणु
		null_fd = खोलो("/dev/null", O_WRONLY);
		अगर (null_fd == -1)
			निकास(त्रुटि_सं);
		dup2(null_fd, STDOUT_खाताNO);
		dup2(null_fd, STDERR_खाताNO);
		बंद(null_fd);

		/* Ensure that all executions from hereon are
		 * secure by setting a local storage which is पढ़ो by
		 * the bprm_creds_क्रम_exec hook and sets bprm->secureexec.
		 */
		ret = update_storage(map_fd, secureexec);
		अगर (ret)
			निकास(ret);

		/* If the binary is executed with securexec=1, the dynamic
		 * loader ingores and unsets certain variables like LD_PRELOAD,
		 * TMPसूची etc. TMPसूची is used here to simplअगरy the example, as
		 * LD_PRELOAD requires a real .so file.
		 *
		 * If the value of TMPसूची is set, the bash command वापसs 10
		 * and अगर the value is unset, it वापसs 20.
		 */
		execle("/bin/bash", "bash", "-c",
		       "[[ -z \"${TMPDIR}\" ]] || exit 10 && exit 20", शून्य,
		       bash_envp);
		निकास(त्रुटि_सं);
	पूर्ण अन्यथा अगर (child_pid > 0) अणु
		रुकोpid(child_pid, &child_status, 0);
		ret = WEXITSTATUS(child_status);

		/* If a secureexec occurred, the निकास status should be 20 */
		अगर (secureexec && ret == 20)
			वापस 0;

		/* If normal execution happened, the निकास code should be 10 */
		अगर (!secureexec && ret == 10)
			वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

व्योम test_test_bprm_opts(व्योम)
अणु
	पूर्णांक err, duration = 0;
	काष्ठा bprm_opts *skel = शून्य;

	skel = bprm_opts__खोलो_and_load();
	अगर (CHECK(!skel, "skel_load", "skeleton failed\n"))
		जाओ बंद_prog;

	err = bprm_opts__attach(skel);
	अगर (CHECK(err, "attach", "attach failed: %d\n", err))
		जाओ बंद_prog;

	/* Run the test with the secureexec bit unset */
	err = run_set_secureexec(bpf_map__fd(skel->maps.secure_exec_task_map),
				 0 /* secureexec */);
	अगर (CHECK(err, "run_set_secureexec:0", "err = %d\n", err))
		जाओ बंद_prog;

	/* Run the test with the secureexec bit set */
	err = run_set_secureexec(bpf_map__fd(skel->maps.secure_exec_task_map),
				 1 /* secureexec */);
	अगर (CHECK(err, "run_set_secureexec:1", "err = %d\n", err))
		जाओ बंद_prog;

बंद_prog:
	bprm_opts__destroy(skel);
पूर्ण
