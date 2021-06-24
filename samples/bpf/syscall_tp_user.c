<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2017 Facebook
 */
#समावेश <मानकपन.स>
#समावेश <unistd.h>
#समावेश <fcntl.h>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <linux/perf_event.h>
#समावेश <त्रुटिसं.स>
#समावेश <sys/resource.h>
#समावेश <bpf/libbpf.h>
#समावेश <bpf/bpf.h>

/* This program verअगरies bpf attachment to tracepoपूर्णांक sys_enter_* and sys_निकास_*.
 * This requires kernel CONFIG_FTRACE_SYSCALLS to be set.
 */

अटल व्योम usage(स्थिर अक्षर *cmd)
अणु
	म_लिखो("USAGE: %s [-i num_progs] [-h]\n", cmd);
	म_लिखो("       -i num_progs      # number of progs of the test\n");
	म_लिखो("       -h                # help\n");
पूर्ण

अटल व्योम verअगरy_map(पूर्णांक map_id)
अणु
	__u32 key = 0;
	__u32 val;

	अगर (bpf_map_lookup_elem(map_id, &key, &val) != 0) अणु
		ख_लिखो(मानक_त्रुटि, "map_lookup failed: %s\n", म_त्रुटि(त्रुटि_सं));
		वापस;
	पूर्ण
	अगर (val == 0) अणु
		ख_लिखो(मानक_त्रुटि, "failed: map #%d returns value 0\n", map_id);
		वापस;
	पूर्ण
	val = 0;
	अगर (bpf_map_update_elem(map_id, &key, &val, BPF_ANY) != 0) अणु
		ख_लिखो(मानक_त्रुटि, "map_update failed: %s\n", म_त्रुटि(त्रुटि_सं));
		वापस;
	पूर्ण
पूर्ण

अटल पूर्णांक test(अक्षर *filename, पूर्णांक num_progs)
अणु
	पूर्णांक map0_fds[num_progs], map1_fds[num_progs], fd, i, j = 0;
	काष्ठा bpf_link *links[num_progs * 4];
	काष्ठा bpf_object *objs[num_progs];
	काष्ठा bpf_program *prog;

	क्रम (i = 0; i < num_progs; i++) अणु
		objs[i] = bpf_object__खोलो_file(filename, शून्य);
		अगर (libbpf_get_error(objs[i])) अणु
			ख_लिखो(मानक_त्रुटि, "opening BPF object file failed\n");
			objs[i] = शून्य;
			जाओ cleanup;
		पूर्ण

		/* load BPF program */
		अगर (bpf_object__load(objs[i])) अणु
			ख_लिखो(मानक_त्रुटि, "loading BPF object file failed\n");
			जाओ cleanup;
		पूर्ण

		map0_fds[i] = bpf_object__find_map_fd_by_name(objs[i],
							      "enter_open_map");
		map1_fds[i] = bpf_object__find_map_fd_by_name(objs[i],
							      "exit_open_map");
		अगर (map0_fds[i] < 0 || map1_fds[i] < 0) अणु
			ख_लिखो(मानक_त्रुटि, "finding a map in obj file failed\n");
			जाओ cleanup;
		पूर्ण

		bpf_object__क्रम_each_program(prog, objs[i]) अणु
			links[j] = bpf_program__attach(prog);
			अगर (libbpf_get_error(links[j])) अणु
				ख_लिखो(मानक_त्रुटि, "bpf_program__attach failed\n");
				links[j] = शून्य;
				जाओ cleanup;
			पूर्ण
			j++;
		पूर्ण
		म_लिखो("prog #%d: map ids %d %d\n", i, map0_fds[i], map1_fds[i]);
	पूर्ण

	/* current load_bpf_file has perf_event_खोलो शेष pid = -1
	 * and cpu = 0, which permits attached bpf execution on
	 * all cpus क्रम all pid's. bpf program execution ignores
	 * cpu affinity.
	 */
	/* trigger some "open" operations */
	fd = खोलो(filename, O_RDONLY);
	अगर (fd < 0) अणु
		ख_लिखो(मानक_त्रुटि, "open failed: %s\n", म_त्रुटि(त्रुटि_सं));
		वापस 1;
	पूर्ण
	बंद(fd);

	/* verअगरy the map */
	क्रम (i = 0; i < num_progs; i++) अणु
		verअगरy_map(map0_fds[i]);
		verअगरy_map(map1_fds[i]);
	पूर्ण

cleanup:
	क्रम (j--; j >= 0; j--)
		bpf_link__destroy(links[j]);

	क्रम (i--; i >= 0; i--)
		bpf_object__बंद(objs[i]);
	वापस 0;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	पूर्णांक opt, num_progs = 1;
	अक्षर filename[256];

	जबतक ((opt = getopt(argc, argv, "i:h")) != -1) अणु
		चयन (opt) अणु
		हाल 'i':
			num_progs = म_से_प(optarg);
			अवरोध;
		हाल 'h':
		शेष:
			usage(argv[0]);
			वापस 0;
		पूर्ण
	पूर्ण

	snम_लिखो(filename, माप(filename), "%s_kern.o", argv[0]);

	वापस test(filename, num_progs);
पूर्ण
