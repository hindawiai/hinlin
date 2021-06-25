<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2020 Facebook */

#समावेश <sys/types.h>
#समावेश <bpf/bpf.h>
#समावेश <bpf/libbpf.h>
#समावेश "test_progs.h"
#समावेश "network_helpers.h"
#समावेश "test_sk_storage_trace_itself.skel.h"
#समावेश "test_sk_storage_tracing.skel.h"

#घोषणा LO_ADDR6 "::1"
#घोषणा TEST_COMM "test_progs"

काष्ठा sk_stg अणु
	__u32 pid;
	__u32 last_notबंद_state;
	अक्षर comm[16];
पूर्ण;

अटल काष्ठा test_sk_storage_tracing *skel;
अटल __u32 duration;
अटल pid_t my_pid;

अटल पूर्णांक check_sk_stg(पूर्णांक sk_fd, __u32 expected_state)
अणु
	काष्ठा sk_stg sk_stg;
	पूर्णांक err;

	err = bpf_map_lookup_elem(bpf_map__fd(skel->maps.sk_stg_map), &sk_fd,
				  &sk_stg);
	अगर (!ASSERT_OK(err, "map_lookup(sk_stg_map)"))
		वापस -1;

	अगर (!ASSERT_EQ(sk_stg.last_notबंद_state, expected_state,
		       "last_notclose_state"))
		वापस -1;

	अगर (!ASSERT_EQ(sk_stg.pid, my_pid, "pid"))
		वापस -1;

	अगर (!ASSERT_STREQ(sk_stg.comm, skel->bss->task_comm, "task_comm"))
		वापस -1;

	वापस 0;
पूर्ण

अटल व्योम करो_test(व्योम)
अणु
	पूर्णांक listen_fd = -1, passive_fd = -1, active_fd = -1, value = 1, err;
	अक्षर abyte;

	listen_fd = start_server(AF_INET6, SOCK_STREAM, LO_ADDR6, 0, 0);
	अगर (CHECK(listen_fd == -1, "start_server",
		  "listen_fd:%d errno:%d\n", listen_fd, त्रुटि_सं))
		वापस;

	active_fd = connect_to_fd(listen_fd, 0);
	अगर (CHECK(active_fd == -1, "connect_to_fd", "active_fd:%d errno:%d\n",
		  active_fd, त्रुटि_सं))
		जाओ out;

	err = bpf_map_update_elem(bpf_map__fd(skel->maps.del_sk_stg_map),
				  &active_fd, &value, 0);
	अगर (!ASSERT_OK(err, "map_update(del_sk_stg_map)"))
		जाओ out;

	passive_fd = accept(listen_fd, शून्य, 0);
	अगर (CHECK(passive_fd == -1, "accept", "passive_fd:%d errno:%d\n",
		  passive_fd, त्रुटि_सं))
		जाओ out;

	shutकरोwn(active_fd, SHUT_WR);
	err = पढ़ो(passive_fd, &abyte, 1);
	अगर (!ASSERT_OK(err, "read(passive_fd)"))
		जाओ out;

	shutकरोwn(passive_fd, SHUT_WR);
	err = पढ़ो(active_fd, &abyte, 1);
	अगर (!ASSERT_OK(err, "read(active_fd)"))
		जाओ out;

	err = bpf_map_lookup_elem(bpf_map__fd(skel->maps.del_sk_stg_map),
				  &active_fd, &value);
	अगर (!ASSERT_ERR(err, "map_lookup(del_sk_stg_map)"))
		जाओ out;

	err = check_sk_stg(listen_fd, BPF_TCP_LISTEN);
	अगर (!ASSERT_OK(err, "listen_fd sk_stg"))
		जाओ out;

	err = check_sk_stg(active_fd, BPF_TCP_FIN_WAIT2);
	अगर (!ASSERT_OK(err, "active_fd sk_stg"))
		जाओ out;

	err = check_sk_stg(passive_fd, BPF_TCP_LAST_ACK);
	ASSERT_OK(err, "passive_fd sk_stg");

out:
	अगर (active_fd != -1)
		बंद(active_fd);
	अगर (passive_fd != -1)
		बंद(passive_fd);
	अगर (listen_fd != -1)
		बंद(listen_fd);
पूर्ण

व्योम test_sk_storage_tracing(व्योम)
अणु
	काष्ठा test_sk_storage_trace_itself *skel_itself;
	पूर्णांक err;

	my_pid = getpid();

	skel_itself = test_sk_storage_trace_itself__खोलो_and_load();

	अगर (!ASSERT_शून्य(skel_itself, "test_sk_storage_trace_itself")) अणु
		test_sk_storage_trace_itself__destroy(skel_itself);
		वापस;
	पूर्ण

	skel = test_sk_storage_tracing__खोलो_and_load();
	अगर (!ASSERT_OK_PTR(skel, "test_sk_storage_tracing"))
		वापस;

	err = test_sk_storage_tracing__attach(skel);
	अगर (!ASSERT_OK(err, "test_sk_storage_tracing__attach")) अणु
		test_sk_storage_tracing__destroy(skel);
		वापस;
	पूर्ण

	करो_test();

	test_sk_storage_tracing__destroy(skel);
पूर्ण
