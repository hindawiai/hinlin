<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/*
 * Copyright (C) 2020 Google LLC.
 */

#समावेश <यंत्र-generic/त्रुटि_सं-base.h>
#समावेश <sys/स्थिति.स>
#समावेश <test_progs.h>
#समावेश <linux/सीमा.स>

#समावेश "local_storage.skel.h"
#समावेश "network_helpers.h"

#अगर_अघोषित __NR_pidfd_खोलो
#घोषणा __NR_pidfd_खोलो 434
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक sys_pidfd_खोलो(pid_t pid, अचिन्हित पूर्णांक flags)
अणु
	वापस syscall(__NR_pidfd_खोलो, pid, flags);
पूर्ण

अटल अचिन्हित पूर्णांक duration;

#घोषणा TEST_STORAGE_VALUE 0xbeefdead

काष्ठा storage अणु
	व्योम *inode;
	अचिन्हित पूर्णांक value;
	/* Lock ensures that spin locked versions of local stoage operations
	 * also work, most operations in this tests are still single thपढ़ोed
	 */
	काष्ठा bpf_spin_lock lock;
पूर्ण;

/* Fork and exec the provided rm binary and वापस the निकास code of the
 * विभाजनed process and its pid.
 */
अटल पूर्णांक run_self_unlink(पूर्णांक *monitored_pid, स्थिर अक्षर *rm_path)
अणु
	पूर्णांक child_pid, child_status, ret;
	पूर्णांक null_fd;

	child_pid = विभाजन();
	अगर (child_pid == 0) अणु
		null_fd = खोलो("/dev/null", O_WRONLY);
		dup2(null_fd, STDOUT_खाताNO);
		dup2(null_fd, STDERR_खाताNO);
		बंद(null_fd);

		*monitored_pid = getpid();
		/* Use the copied /usr/bin/rm to delete itself
		 * /पंचांगp/copy_of_rm /पंचांगp/copy_of_rm.
		 */
		ret = execlp(rm_path, rm_path, rm_path, शून्य);
		अगर (ret)
			निकास(त्रुटि_सं);
	पूर्ण अन्यथा अगर (child_pid > 0) अणु
		रुकोpid(child_pid, &child_status, 0);
		वापस WEXITSTATUS(child_status);
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल bool check_syscall_operations(पूर्णांक map_fd, पूर्णांक obj_fd)
अणु
	काष्ठा storage val = अणु .value = TEST_STORAGE_VALUE, .lock = अणु 0 पूर्ण पूर्ण,
		       lookup_val = अणु .value = 0, .lock = अणु 0 पूर्ण पूर्ण;
	पूर्णांक err;

	/* Looking up an existing element should fail initially */
	err = bpf_map_lookup_elem_flags(map_fd, &obj_fd, &lookup_val,
					BPF_F_LOCK);
	अगर (CHECK(!err || त्रुटि_सं != ENOENT, "bpf_map_lookup_elem",
		  "err:%d errno:%d\n", err, त्रुटि_सं))
		वापस false;

	/* Create a new element */
	err = bpf_map_update_elem(map_fd, &obj_fd, &val,
				  BPF_NOEXIST | BPF_F_LOCK);
	अगर (CHECK(err < 0, "bpf_map_update_elem", "err:%d errno:%d\n", err,
		  त्रुटि_सं))
		वापस false;

	/* Lookup the newly created element */
	err = bpf_map_lookup_elem_flags(map_fd, &obj_fd, &lookup_val,
					BPF_F_LOCK);
	अगर (CHECK(err < 0, "bpf_map_lookup_elem", "err:%d errno:%d", err,
		  त्रुटि_सं))
		वापस false;

	/* Check the value of the newly created element */
	अगर (CHECK(lookup_val.value != val.value, "bpf_map_lookup_elem",
		  "value got = %x errno:%d", lookup_val.value, val.value))
		वापस false;

	err = bpf_map_delete_elem(map_fd, &obj_fd);
	अगर (CHECK(err, "bpf_map_delete_elem()", "err:%d errno:%d\n", err,
		  त्रुटि_सं))
		वापस false;

	/* The lookup should fail, now that the element has been deleted */
	err = bpf_map_lookup_elem_flags(map_fd, &obj_fd, &lookup_val,
					BPF_F_LOCK);
	अगर (CHECK(!err || त्रुटि_सं != ENOENT, "bpf_map_lookup_elem",
		  "err:%d errno:%d\n", err, त्रुटि_सं))
		वापस false;

	वापस true;
पूर्ण

व्योम test_test_local_storage(व्योम)
अणु
	अक्षर पंचांगp_dir_path[] = "/tmp/local_storageXXXXXX";
	पूर्णांक err, serv_sk = -1, task_fd = -1, rm_fd = -1;
	काष्ठा local_storage *skel = शून्य;
	अक्षर पंचांगp_exec_path[64];
	अक्षर cmd[256];

	skel = local_storage__खोलो_and_load();
	अगर (CHECK(!skel, "skel_load", "lsm skeleton failed\n"))
		जाओ बंद_prog;

	err = local_storage__attach(skel);
	अगर (CHECK(err, "attach", "lsm attach failed: %d\n", err))
		जाओ बंद_prog;

	task_fd = sys_pidfd_खोलो(getpid(), 0);
	अगर (CHECK(task_fd < 0, "pidfd_open",
		  "failed to get pidfd err:%d, errno:%d", task_fd, त्रुटि_सं))
		जाओ बंद_prog;

	अगर (!check_syscall_operations(bpf_map__fd(skel->maps.task_storage_map),
				      task_fd))
		जाओ बंद_prog;

	अगर (CHECK(!mkdtemp(पंचांगp_dir_path), "mkdtemp",
		  "unable to create tmpdir: %d\n", त्रुटि_सं))
		जाओ बंद_prog;

	snम_लिखो(पंचांगp_exec_path, माप(पंचांगp_exec_path), "%s/copy_of_rm",
		 पंचांगp_dir_path);
	snम_लिखो(cmd, माप(cmd), "cp /bin/rm %s", पंचांगp_exec_path);
	अगर (CHECK_FAIL(प्रणाली(cmd)))
		जाओ बंद_prog_सूची_हटाओ;

	rm_fd = खोलो(पंचांगp_exec_path, O_RDONLY);
	अगर (CHECK(rm_fd < 0, "open", "failed to open %s err:%d, errno:%d",
		  पंचांगp_exec_path, rm_fd, त्रुटि_सं))
		जाओ बंद_prog_सूची_हटाओ;

	अगर (!check_syscall_operations(bpf_map__fd(skel->maps.inode_storage_map),
				      rm_fd))
		जाओ बंद_prog_सूची_हटाओ;

	/* Sets skel->bss->monitored_pid to the pid of the विभाजनed child
	 * विभाजनs a child process that executes पंचांगp_exec_path and tries to
	 * unlink its executable. This operation should be denied by the loaded
	 * LSM program.
	 */
	err = run_self_unlink(&skel->bss->monitored_pid, पंचांगp_exec_path);
	अगर (CHECK(err != EPERM, "run_self_unlink", "err %d want EPERM\n", err))
		जाओ बंद_prog_सूची_हटाओ;

	/* Set the process being monitored to be the current process */
	skel->bss->monitored_pid = getpid();

	/* Move copy_of_rm to a new location so that it triggers the
	 * inode_नाम LSM hook with a new_dentry that has a शून्य inode ptr.
	 */
	snम_लिखो(cmd, माप(cmd), "mv %s/copy_of_rm %s/check_null_ptr",
		 पंचांगp_dir_path, पंचांगp_dir_path);
	अगर (CHECK_FAIL(प्रणाली(cmd)))
		जाओ बंद_prog_सूची_हटाओ;

	CHECK(skel->data->inode_storage_result != 0, "inode_storage_result",
	      "inode_local_storage not set\n");

	serv_sk = start_server(AF_INET6, SOCK_STREAM, शून्य, 0, 0);
	अगर (CHECK(serv_sk < 0, "start_server", "failed to start server\n"))
		जाओ बंद_prog_सूची_हटाओ;

	CHECK(skel->data->sk_storage_result != 0, "sk_storage_result",
	      "sk_local_storage not set\n");

	अगर (!check_syscall_operations(bpf_map__fd(skel->maps.sk_storage_map),
				      serv_sk))
		जाओ बंद_prog_सूची_हटाओ;

बंद_prog_सूची_हटाओ:
	snम_लिखो(cmd, माप(cmd), "rm -rf %s", पंचांगp_dir_path);
	प्रणाली(cmd);
बंद_prog:
	बंद(serv_sk);
	बंद(rm_fd);
	बंद(task_fd);
	local_storage__destroy(skel);
पूर्ण
