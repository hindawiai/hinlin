<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <मानकपन.स>
#समावेश <fcntl.h>
#समावेश <poll.h>
#समावेश <समय.स>
#समावेश <संकेत.स>
#समावेश <bpf/libbpf.h>

अटल __u64 समय_get_ns(व्योम)
अणु
	काष्ठा बारpec ts;

	घड़ी_समय_लो(CLOCK_MONOTONIC, &ts);
	वापस ts.tv_sec * 1000000000ull + ts.tv_nsec;
पूर्ण

अटल __u64 start_समय;
अटल __u64 cnt;

#घोषणा MAX_CNT 100000ll

अटल व्योम prपूर्णांक_bpf_output(व्योम *ctx, पूर्णांक cpu, व्योम *data, __u32 size)
अणु
	काष्ठा अणु
		__u64 pid;
		__u64 cookie;
	पूर्ण *e = data;

	अगर (e->cookie != 0x12345678) अणु
		म_लिखो("BUG pid %llx cookie %llx sized %d\n",
		       e->pid, e->cookie, size);
		वापस;
	पूर्ण

	cnt++;

	अगर (cnt == MAX_CNT) अणु
		म_लिखो("recv %lld events per sec\n",
		       MAX_CNT * 1000000000ll / (समय_get_ns() - start_समय));
		वापस;
	पूर्ण
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	काष्ठा perf_buffer_opts pb_opts = अणुपूर्ण;
	काष्ठा bpf_link *link = शून्य;
	काष्ठा bpf_program *prog;
	काष्ठा perf_buffer *pb;
	काष्ठा bpf_object *obj;
	पूर्णांक map_fd, ret = 0;
	अक्षर filename[256];
	खाता *f;

	snम_लिखो(filename, माप(filename), "%s_kern.o", argv[0]);
	obj = bpf_object__खोलो_file(filename, शून्य);
	अगर (libbpf_get_error(obj)) अणु
		ख_लिखो(मानक_त्रुटि, "ERROR: opening BPF object file failed\n");
		वापस 0;
	पूर्ण

	/* load BPF program */
	अगर (bpf_object__load(obj)) अणु
		ख_लिखो(मानक_त्रुटि, "ERROR: loading BPF object file failed\n");
		जाओ cleanup;
	पूर्ण

	map_fd = bpf_object__find_map_fd_by_name(obj, "my_map");
	अगर (map_fd < 0) अणु
		ख_लिखो(मानक_त्रुटि, "ERROR: finding a map in obj file failed\n");
		जाओ cleanup;
	पूर्ण

	prog = bpf_object__find_program_by_name(obj, "bpf_prog1");
	अगर (libbpf_get_error(prog)) अणु
		ख_लिखो(मानक_त्रुटि, "ERROR: finding a prog in obj file failed\n");
		जाओ cleanup;
	पूर्ण

	link = bpf_program__attach(prog);
	अगर (libbpf_get_error(link)) अणु
		ख_लिखो(मानक_त्रुटि, "ERROR: bpf_program__attach failed\n");
		link = शून्य;
		जाओ cleanup;
	पूर्ण

	pb_opts.sample_cb = prपूर्णांक_bpf_output;
	pb = perf_buffer__new(map_fd, 8, &pb_opts);
	ret = libbpf_get_error(pb);
	अगर (ret) अणु
		म_लिखो("failed to setup perf_buffer: %d\n", ret);
		वापस 1;
	पूर्ण

	f = pखोलो("taskset 1 dd if=/dev/zero of=/dev/null", "r");
	(व्योम) f;

	start_समय = समय_get_ns();
	जबतक ((ret = perf_buffer__poll(pb, 1000)) >= 0 && cnt < MAX_CNT) अणु
	पूर्ण
	समाप्त(0, संक_विघ्न);

cleanup:
	bpf_link__destroy(link);
	bpf_object__बंद(obj);
	वापस ret;
पूर्ण
