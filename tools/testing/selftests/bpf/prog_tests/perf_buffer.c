<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#घोषणा _GNU_SOURCE
#समावेश <pthपढ़ो.h>
#समावेश <sched.h>
#समावेश <sys/socket.h>
#समावेश <test_progs.h>
#समावेश "test_perf_buffer.skel.h"
#समावेश "bpf/libbpf_internal.h"

अटल पूर्णांक duration;

/* AddressSanitizer someबार crashes due to data dereference below, due to
 * this being mmap()'ed memory. Disable instrumentation with
 * no_sanitize_address attribute
 */
__attribute__((no_sanitize_address))
अटल व्योम on_sample(व्योम *ctx, पूर्णांक cpu, व्योम *data, __u32 size)
अणु
	पूर्णांक cpu_data = *(पूर्णांक *)data, duration = 0;
	cpu_set_t *cpu_seen = ctx;

	अगर (cpu_data != cpu)
		CHECK(cpu_data != cpu, "check_cpu_data",
		      "cpu_data %d != cpu %d\n", cpu_data, cpu);

	CPU_SET(cpu, cpu_seen);
पूर्ण

पूर्णांक trigger_on_cpu(पूर्णांक cpu)
अणु
	cpu_set_t cpu_set;
	पूर्णांक err;

	CPU_ZERO(&cpu_set);
	CPU_SET(cpu, &cpu_set);

	err = pthपढ़ो_setaffinity_np(pthपढ़ो_self(), माप(cpu_set), &cpu_set);
	अगर (err && CHECK(err, "set_affinity", "cpu #%d, err %d\n", cpu, err))
		वापस err;

	usleep(1);

	वापस 0;
पूर्ण

व्योम test_perf_buffer(व्योम)
अणु
	पूर्णांक err, on_len, nr_on_cpus = 0, nr_cpus, i;
	काष्ठा perf_buffer_opts pb_opts = अणुपूर्ण;
	काष्ठा test_perf_buffer *skel;
	cpu_set_t cpu_seen;
	काष्ठा perf_buffer *pb;
	पूर्णांक last_fd = -1, fd;
	bool *online;

	nr_cpus = libbpf_num_possible_cpus();
	अगर (CHECK(nr_cpus < 0, "nr_cpus", "err %d\n", nr_cpus))
		वापस;

	err = parse_cpu_mask_file("/sys/devices/system/cpu/online",
				  &online, &on_len);
	अगर (CHECK(err, "nr_on_cpus", "err %d\n", err))
		वापस;

	क्रम (i = 0; i < on_len; i++)
		अगर (online[i])
			nr_on_cpus++;

	/* load program */
	skel = test_perf_buffer__खोलो_and_load();
	अगर (CHECK(!skel, "skel_load", "skeleton open/load failed\n"))
		जाओ out_बंद;

	/* attach probe */
	err = test_perf_buffer__attach(skel);
	अगर (CHECK(err, "attach_kprobe", "err %d\n", err))
		जाओ out_बंद;

	/* set up perf buffer */
	pb_opts.sample_cb = on_sample;
	pb_opts.ctx = &cpu_seen;
	pb = perf_buffer__new(bpf_map__fd(skel->maps.perf_buf_map), 1, &pb_opts);
	अगर (CHECK(IS_ERR(pb), "perf_buf__new", "err %ld\n", PTR_ERR(pb)))
		जाओ out_बंद;

	CHECK(perf_buffer__epoll_fd(pb) < 0, "epoll_fd",
	      "bad fd: %d\n", perf_buffer__epoll_fd(pb));

	/* trigger kprobe on every CPU */
	CPU_ZERO(&cpu_seen);
	क्रम (i = 0; i < nr_cpus; i++) अणु
		अगर (i >= on_len || !online[i]) अणु
			म_लिखो("skipping offline CPU #%d\n", i);
			जारी;
		पूर्ण

		अगर (trigger_on_cpu(i))
			जाओ out_बंद;
	पूर्ण

	/* पढ़ो perf buffer */
	err = perf_buffer__poll(pb, 100);
	अगर (CHECK(err < 0, "perf_buffer__poll", "err %d\n", err))
		जाओ out_मुक्त_pb;

	अगर (CHECK(CPU_COUNT(&cpu_seen) != nr_on_cpus, "seen_cpu_cnt",
		  "expect %d, seen %d\n", nr_on_cpus, CPU_COUNT(&cpu_seen)))
		जाओ out_मुक्त_pb;

	अगर (CHECK(perf_buffer__buffer_cnt(pb) != nr_cpus, "buf_cnt",
		  "got %zu, expected %d\n", perf_buffer__buffer_cnt(pb), nr_cpus))
		जाओ out_बंद;

	क्रम (i = 0; i < nr_cpus; i++) अणु
		अगर (i >= on_len || !online[i])
			जारी;

		fd = perf_buffer__buffer_fd(pb, i);
		CHECK(fd < 0 || last_fd == fd, "fd_check", "last fd %d == fd %d\n", last_fd, fd);
		last_fd = fd;

		err = perf_buffer__consume_buffer(pb, i);
		अगर (CHECK(err, "drain_buf", "cpu %d, err %d\n", i, err))
			जाओ out_बंद;

		CPU_CLR(i, &cpu_seen);
		अगर (trigger_on_cpu(i))
			जाओ out_बंद;

		err = perf_buffer__consume_buffer(pb, i);
		अगर (CHECK(err, "consume_buf", "cpu %d, err %d\n", i, err))
			जाओ out_बंद;

		अगर (CHECK(!CPU_ISSET(i, &cpu_seen), "cpu_seen", "cpu %d not seen\n", i))
			जाओ out_बंद;
	पूर्ण

out_मुक्त_pb:
	perf_buffer__मुक्त(pb);
out_बंद:
	test_perf_buffer__destroy(skel);
	मुक्त(online);
पूर्ण
