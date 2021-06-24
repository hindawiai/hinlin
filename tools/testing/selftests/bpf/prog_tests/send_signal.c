<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <test_progs.h>
#समावेश "test_send_signal_kern.skel.h"

अटल अस्थिर पूर्णांक sigusr1_received = 0;

अटल व्योम sigusr1_handler(पूर्णांक signum)
अणु
	sigusr1_received++;
पूर्ण

अटल व्योम test_send_संकेत_common(काष्ठा perf_event_attr *attr,
				    bool संकेत_thपढ़ो,
				    स्थिर अक्षर *test_name)
अणु
	काष्ठा test_send_संकेत_kern *skel;
	पूर्णांक pipe_c2p[2], pipe_p2c[2];
	पूर्णांक err = -1, pmu_fd = -1;
	__u32 duration = 0;
	अक्षर buf[256];
	pid_t pid;

	अगर (CHECK(pipe(pipe_c2p), test_name,
		  "pipe pipe_c2p error: %s\n", म_त्रुटि(त्रुटि_सं)))
		वापस;

	अगर (CHECK(pipe(pipe_p2c), test_name,
		  "pipe pipe_p2c error: %s\n", म_त्रुटि(त्रुटि_सं))) अणु
		बंद(pipe_c2p[0]);
		बंद(pipe_c2p[1]);
		वापस;
	पूर्ण

	pid = विभाजन();
	अगर (CHECK(pid < 0, test_name, "fork error: %s\n", म_त्रुटि(त्रुटि_सं))) अणु
		बंद(pipe_c2p[0]);
		बंद(pipe_c2p[1]);
		बंद(pipe_p2c[0]);
		बंद(pipe_p2c[1]);
		वापस;
	पूर्ण

	अगर (pid == 0) अणु
		/* install संकेत handler and notअगरy parent */
		संकेत(SIGUSR1, sigusr1_handler);

		बंद(pipe_c2p[0]); /* बंद पढ़ो */
		बंद(pipe_p2c[1]); /* बंद ग_लिखो */

		/* notअगरy parent संकेत handler is installed */
		CHECK(ग_लिखो(pipe_c2p[1], buf, 1) != 1, "pipe_write", "err %d\n", -त्रुटि_सं);

		/* make sure parent enabled bpf program to send_संकेत */
		CHECK(पढ़ो(pipe_p2c[0], buf, 1) != 1, "pipe_read", "err %d\n", -त्रुटि_सं);

		/* रुको a little क्रम संकेत handler */
		sleep(1);

		buf[0] = sigusr1_received ? '2' : '0';
		CHECK(ग_लिखो(pipe_c2p[1], buf, 1) != 1, "pipe_write", "err %d\n", -त्रुटि_सं);

		/* रुको क्रम parent notअगरication and निकास */
		CHECK(पढ़ो(pipe_p2c[0], buf, 1) != 1, "pipe_read", "err %d\n", -त्रुटि_सं);

		बंद(pipe_c2p[1]);
		बंद(pipe_p2c[0]);
		निकास(0);
	पूर्ण

	बंद(pipe_c2p[1]); /* बंद ग_लिखो */
	बंद(pipe_p2c[0]); /* बंद पढ़ो */

	skel = test_send_संकेत_kern__खोलो_and_load();
	अगर (CHECK(!skel, "skel_open_and_load", "skeleton open_and_load failed\n"))
		जाओ skel_खोलो_load_failure;

	अगर (!attr) अणु
		err = test_send_संकेत_kern__attach(skel);
		अगर (CHECK(err, "skel_attach", "skeleton attach failed\n")) अणु
			err = -1;
			जाओ destroy_skel;
		पूर्ण
	पूर्ण अन्यथा अणु
		pmu_fd = syscall(__NR_perf_event_खोलो, attr, pid, -1,
				 -1 /* group id */, 0 /* flags */);
		अगर (CHECK(pmu_fd < 0, test_name, "perf_event_open error: %s\n",
			म_त्रुटि(त्रुटि_सं))) अणु
			err = -1;
			जाओ destroy_skel;
		पूर्ण

		skel->links.send_संकेत_perf =
			bpf_program__attach_perf_event(skel->progs.send_संकेत_perf, pmu_fd);
		अगर (CHECK(IS_ERR(skel->links.send_संकेत_perf), "attach_perf_event",
			  "err %ld\n", PTR_ERR(skel->links.send_संकेत_perf)))
			जाओ disable_pmu;
	पूर्ण

	/* रुको until child संकेत handler installed */
	CHECK(पढ़ो(pipe_c2p[0], buf, 1) != 1, "pipe_read", "err %d\n", -त्रुटि_सं);

	/* trigger the bpf send_संकेत */
	skel->bss->pid = pid;
	skel->bss->sig = SIGUSR1;
	skel->bss->संकेत_thपढ़ो = संकेत_thपढ़ो;

	/* notअगरy child that bpf program can send_संकेत now */
	CHECK(ग_लिखो(pipe_p2c[1], buf, 1) != 1, "pipe_write", "err %d\n", -त्रुटि_सं);

	/* रुको क्रम result */
	err = पढ़ो(pipe_c2p[0], buf, 1);
	अगर (CHECK(err < 0, test_name, "reading pipe error: %s\n", म_त्रुटि(त्रुटि_सं)))
		जाओ disable_pmu;
	अगर (CHECK(err == 0, test_name, "reading pipe error: size 0\n")) अणु
		err = -1;
		जाओ disable_pmu;
	पूर्ण

	CHECK(buf[0] != '2', test_name, "incorrect result\n");

	/* notअगरy child safe to निकास */
	CHECK(ग_लिखो(pipe_p2c[1], buf, 1) != 1, "pipe_write", "err %d\n", -त्रुटि_सं);

disable_pmu:
	बंद(pmu_fd);
destroy_skel:
	test_send_संकेत_kern__destroy(skel);
skel_खोलो_load_failure:
	बंद(pipe_c2p[0]);
	बंद(pipe_p2c[1]);
	रुको(शून्य);
पूर्ण

अटल व्योम test_send_संकेत_tracepoपूर्णांक(bool संकेत_thपढ़ो)
अणु
	test_send_संकेत_common(शून्य, संकेत_thपढ़ो, "tracepoint");
पूर्ण

अटल व्योम test_send_संकेत_perf(bool संकेत_thपढ़ो)
अणु
	काष्ठा perf_event_attr attr = अणु
		.sample_period = 1,
		.type = PERF_TYPE_SOFTWARE,
		.config = PERF_COUNT_SW_CPU_CLOCK,
	पूर्ण;

	test_send_संकेत_common(&attr, संकेत_thपढ़ो, "perf_sw_event");
पूर्ण

अटल व्योम test_send_संकेत_nmi(bool संकेत_thपढ़ो)
अणु
	काष्ठा perf_event_attr attr = अणु
		.sample_period = 1,
		.type = PERF_TYPE_HARDWARE,
		.config = PERF_COUNT_HW_CPU_CYCLES,
	पूर्ण;
	पूर्णांक pmu_fd;

	/* Some setups (e.g. भव machines) might run with hardware
	 * perf events disabled. If this is the हाल, skip this test.
	 */
	pmu_fd = syscall(__NR_perf_event_खोलो, &attr, 0 /* pid */,
			 -1 /* cpu */, -1 /* group_fd */, 0 /* flags */);
	अगर (pmu_fd == -1) अणु
		अगर (त्रुटि_सं == ENOENT) अणु
			म_लिखो("%s:SKIP:no PERF_COUNT_HW_CPU_CYCLES\n",
			       __func__);
			test__skip();
			वापस;
		पूर्ण
		/* Let the test fail with a more inक्रमmative message */
	पूर्ण अन्यथा अणु
		बंद(pmu_fd);
	पूर्ण

	test_send_संकेत_common(&attr, संकेत_thपढ़ो, "perf_hw_event");
पूर्ण

व्योम test_send_संकेत(व्योम)
अणु
	अगर (test__start_subtest("send_signal_tracepoint"))
		test_send_संकेत_tracepoपूर्णांक(false);
	अगर (test__start_subtest("send_signal_perf"))
		test_send_संकेत_perf(false);
	अगर (test__start_subtest("send_signal_nmi"))
		test_send_संकेत_nmi(false);
	अगर (test__start_subtest("send_signal_tracepoint_thread"))
		test_send_संकेत_tracepoपूर्णांक(true);
	अगर (test__start_subtest("send_signal_perf_thread"))
		test_send_संकेत_perf(true);
	अगर (test__start_subtest("send_signal_nmi_thread"))
		test_send_संकेत_nmi(true);
पूर्ण
