<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#घोषणा _GNU_SOURCE
#समावेश <pthपढ़ो.h>
#समावेश <पूर्णांकtypes.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <unistd.h>
#समावेश <यंत्र/types.h>
#समावेश <sys/syscall.h>
#समावेश <त्रुटिसं.स>
#समावेश <माला.स>
#समावेश <linux/bpf.h>
#समावेश <sys/socket.h>
#समावेश <bpf/bpf.h>
#समावेश <bpf/libbpf.h>
#समावेश <sys/ioctl.h>
#समावेश <linux/rtnetlink.h>
#समावेश <संकेत.स>
#समावेश <linux/perf_event.h>
#समावेश <linux/err.h>

#समावेश "bpf_rlimit.h"
#समावेश "bpf_util.h"
#समावेश "cgroup_helpers.h"

#समावेश "test_tcpnotify.h"
#समावेश "trace_helpers.h"

#घोषणा SOCKET_BUFFER_SIZE (getpagesize() < 8192L ? getpagesize() : 8192L)

pthपढ़ो_t tid;
पूर्णांक rx_callbacks;

अटल व्योम dummyfn(व्योम *ctx, पूर्णांक cpu, व्योम *data, __u32 size)
अणु
	काष्ठा tcp_notअगरier *t = data;

	अगर (t->type != 0xde || t->subtype != 0xad ||
	    t->source != 0xbe || t->hash != 0xef)
		वापस;
	rx_callbacks++;
पूर्ण

व्योम tcp_notअगरier_poller(काष्ठा perf_buffer *pb)
अणु
	पूर्णांक err;

	जबतक (1) अणु
		err = perf_buffer__poll(pb, 100);
		अगर (err < 0 && err != -EINTR) अणु
			म_लिखो("failed perf_buffer__poll: %d\n", err);
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम *poller_thपढ़ो(व्योम *arg)
अणु
	काष्ठा perf_buffer *pb = arg;

	tcp_notअगरier_poller(pb);
	वापस arg;
पूर्ण

पूर्णांक verअगरy_result(स्थिर काष्ठा tcpnotअगरy_globals *result)
अणु
	वापस (result->ncalls > 0 && result->ncalls == rx_callbacks ? 0 : 1);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	स्थिर अक्षर *file = "test_tcpnotify_kern.o";
	काष्ठा bpf_map *perf_map, *global_map;
	काष्ठा perf_buffer_opts pb_opts = अणुपूर्ण;
	काष्ठा tcpnotअगरy_globals g = अणु0पूर्ण;
	काष्ठा perf_buffer *pb = शून्य;
	स्थिर अक्षर *cg_path = "/foo";
	पूर्णांक prog_fd, rv, cg_fd = -1;
	पूर्णांक error = निकास_त्रुटि;
	काष्ठा bpf_object *obj;
	अक्षर test_script[80];
	cpu_set_t cpuset;
	__u32 key = 0;

	CPU_ZERO(&cpuset);
	CPU_SET(0, &cpuset);
	pthपढ़ो_setaffinity_np(pthपढ़ो_self(), माप(cpu_set_t), &cpuset);

	cg_fd = cgroup_setup_and_join(cg_path);
	अगर (cg_fd < 0)
		जाओ err;

	अगर (bpf_prog_load(file, BPF_PROG_TYPE_SOCK_OPS, &obj, &prog_fd)) अणु
		म_लिखो("FAILED: load_bpf_file failed for: %s\n", file);
		जाओ err;
	पूर्ण

	rv = bpf_prog_attach(prog_fd, cg_fd, BPF_CGROUP_SOCK_OPS, 0);
	अगर (rv) अणु
		म_लिखो("FAILED: bpf_prog_attach: %d (%s)\n",
		       error, म_त्रुटि(त्रुटि_सं));
		जाओ err;
	पूर्ण

	perf_map = bpf_object__find_map_by_name(obj, "perf_event_map");
	अगर (!perf_map) अणु
		म_लिखो("FAIL:map '%s' not found\n", "perf_event_map");
		जाओ err;
	पूर्ण

	global_map = bpf_object__find_map_by_name(obj, "global_map");
	अगर (!global_map) अणु
		म_लिखो("FAIL:map '%s' not found\n", "global_map");
		वापस -1;
	पूर्ण

	pb_opts.sample_cb = dummyfn;
	pb = perf_buffer__new(bpf_map__fd(perf_map), 8, &pb_opts);
	अगर (IS_ERR(pb))
		जाओ err;

	pthपढ़ो_create(&tid, शून्य, poller_thपढ़ो, pb);

	प्र_लिखो(test_script,
		"iptables -A INPUT -p tcp --dport %d -j DROP",
		TESTPORT);
	अगर (प्रणाली(test_script)) अणु
		म_लिखो("FAILED: execute command: %s, err %d\n", test_script, -त्रुटि_सं);
		जाओ err;
	पूर्ण

	प्र_लिखो(test_script,
		"nc 127.0.0.1 %d < /etc/passwd > /dev/null 2>&1 ",
		TESTPORT);
	अगर (प्रणाली(test_script))
		म_लिखो("execute command: %s, err %d\n", test_script, -त्रुटि_सं);

	प्र_लिखो(test_script,
		"iptables -D INPUT -p tcp --dport %d -j DROP",
		TESTPORT);
	अगर (प्रणाली(test_script)) अणु
		म_लिखो("FAILED: execute command: %s, err %d\n", test_script, -त्रुटि_सं);
		जाओ err;
	पूर्ण

	rv = bpf_map_lookup_elem(bpf_map__fd(global_map), &key, &g);
	अगर (rv != 0) अणु
		म_लिखो("FAILED: bpf_map_lookup_elem returns %d\n", rv);
		जाओ err;
	पूर्ण

	sleep(10);

	अगर (verअगरy_result(&g)) अणु
		म_लिखो("FAILED: Wrong stats Expected %d calls, got %d\n",
			g.ncalls, rx_callbacks);
		जाओ err;
	पूर्ण

	म_लिखो("PASSED!\n");
	error = 0;
err:
	bpf_prog_detach(cg_fd, BPF_CGROUP_SOCK_OPS);
	बंद(cg_fd);
	cleanup_cgroup_environment();
	अगर (!IS_ERR_OR_शून्य(pb))
		perf_buffer__मुक्त(pb);
	वापस error;
पूर्ण
