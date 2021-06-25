<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2016 Sargun Dhillon <sargun@sargun.me>
 */

#घोषणा _GNU_SOURCE
#समावेश <मानकपन.स>
#समावेश <unistd.h>
#समावेश <bpf/bpf.h>
#समावेश <bpf/libbpf.h>
#समावेश "cgroup_helpers.h"

#घोषणा CGROUP_PATH		"/my-cgroup"

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	pid_t remote_pid, local_pid = getpid();
	काष्ठा bpf_link *link = शून्य;
	काष्ठा bpf_program *prog;
	पूर्णांक cg2, idx = 0, rc = 1;
	काष्ठा bpf_object *obj;
	अक्षर filename[256];
	पूर्णांक map_fd[2];

	snम_लिखो(filename, माप(filename), "%s_kern.o", argv[0]);
	obj = bpf_object__खोलो_file(filename, शून्य);
	अगर (libbpf_get_error(obj)) अणु
		ख_लिखो(मानक_त्रुटि, "ERROR: opening BPF object file failed\n");
		वापस 0;
	पूर्ण

	prog = bpf_object__find_program_by_name(obj, "bpf_prog1");
	अगर (!prog) अणु
		म_लिखो("finding a prog in obj file failed\n");
		जाओ cleanup;
	पूर्ण

	/* load BPF program */
	अगर (bpf_object__load(obj)) अणु
		ख_लिखो(मानक_त्रुटि, "ERROR: loading BPF object file failed\n");
		जाओ cleanup;
	पूर्ण

	map_fd[0] = bpf_object__find_map_fd_by_name(obj, "cgroup_map");
	map_fd[1] = bpf_object__find_map_fd_by_name(obj, "perf_map");
	अगर (map_fd[0] < 0 || map_fd[1] < 0) अणु
		ख_लिखो(मानक_त्रुटि, "ERROR: finding a map in obj file failed\n");
		जाओ cleanup;
	पूर्ण

	link = bpf_program__attach(prog);
	अगर (libbpf_get_error(link)) अणु
		ख_लिखो(मानक_त्रुटि, "ERROR: bpf_program__attach failed\n");
		link = शून्य;
		जाओ cleanup;
	पूर्ण

	अगर (setup_cgroup_environment())
		जाओ err;

	cg2 = create_and_get_cgroup(CGROUP_PATH);

	अगर (cg2 < 0)
		जाओ err;

	अगर (bpf_map_update_elem(map_fd[0], &idx, &cg2, BPF_ANY)) अणु
		log_err("Adding target cgroup to map");
		जाओ err;
	पूर्ण

	अगर (join_cgroup(CGROUP_PATH))
		जाओ err;

	/*
	 * The installed helper program catched the sync call, and should
	 * ग_लिखो it to the map.
	 */

	sync();
	bpf_map_lookup_elem(map_fd[1], &idx, &remote_pid);

	अगर (local_pid != remote_pid) अणु
		ख_लिखो(मानक_त्रुटि,
			"BPF Helper didn't write correct PID to map, but: %d\n",
			remote_pid);
		जाओ err;
	पूर्ण

	/* Verअगरy the negative scenario; leave the cgroup */
	अगर (join_cgroup("/"))
		जाओ err;

	remote_pid = 0;
	bpf_map_update_elem(map_fd[1], &idx, &remote_pid, BPF_ANY);

	sync();
	bpf_map_lookup_elem(map_fd[1], &idx, &remote_pid);

	अगर (local_pid == remote_pid) अणु
		ख_लिखो(मानक_त्रुटि, "BPF cgroup negative test did not work\n");
		जाओ err;
	पूर्ण

	rc = 0;

err:
	बंद(cg2);
	cleanup_cgroup_environment();

cleanup:
	bpf_link__destroy(link);
	bpf_object__बंद(obj);
	वापस rc;
पूर्ण
