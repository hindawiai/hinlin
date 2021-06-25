<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <test_progs.h>
#समावेश "cgroup_helpers.h"
#समावेश "network_helpers.h"

काष्ठा tcp_rtt_storage अणु
	__u32 invoked;
	__u32 dsack_dups;
	__u32 delivered;
	__u32 delivered_ce;
	__u32 icsk_retransmits;
पूर्ण;

अटल व्योम send_byte(पूर्णांक fd)
अणु
	अक्षर b = 0x55;

	अगर (CHECK_FAIL(ग_लिखो(fd, &b, माप(b)) != 1))
		लिखो_त्रुटि("Failed to send single byte");
पूर्ण

अटल पूर्णांक रुको_क्रम_ack(पूर्णांक fd, पूर्णांक retries)
अणु
	काष्ठा tcp_info info;
	socklen_t optlen;
	पूर्णांक i, err;

	क्रम (i = 0; i < retries; i++) अणु
		optlen = माप(info);
		err = माला_लोockopt(fd, SOL_TCP, TCP_INFO, &info, &optlen);
		अगर (err < 0) अणु
			log_err("Failed to lookup TCP stats");
			वापस err;
		पूर्ण

		अगर (info.tcpi_unacked == 0)
			वापस 0;

		usleep(10);
	पूर्ण

	log_err("Did not receive ACK");
	वापस -1;
पूर्ण

अटल पूर्णांक verअगरy_sk(पूर्णांक map_fd, पूर्णांक client_fd, स्थिर अक्षर *msg, __u32 invoked,
		     __u32 dsack_dups, __u32 delivered, __u32 delivered_ce,
		     __u32 icsk_retransmits)
अणु
	पूर्णांक err = 0;
	काष्ठा tcp_rtt_storage val;

	अगर (CHECK_FAIL(bpf_map_lookup_elem(map_fd, &client_fd, &val) < 0)) अणु
		लिखो_त्रुटि("Failed to read socket storage");
		वापस -1;
	पूर्ण

	अगर (val.invoked != invoked) अणु
		log_err("%s: unexpected bpf_tcp_sock.invoked %d != %d",
			msg, val.invoked, invoked);
		err++;
	पूर्ण

	अगर (val.dsack_dups != dsack_dups) अणु
		log_err("%s: unexpected bpf_tcp_sock.dsack_dups %d != %d",
			msg, val.dsack_dups, dsack_dups);
		err++;
	पूर्ण

	अगर (val.delivered != delivered) अणु
		log_err("%s: unexpected bpf_tcp_sock.delivered %d != %d",
			msg, val.delivered, delivered);
		err++;
	पूर्ण

	अगर (val.delivered_ce != delivered_ce) अणु
		log_err("%s: unexpected bpf_tcp_sock.delivered_ce %d != %d",
			msg, val.delivered_ce, delivered_ce);
		err++;
	पूर्ण

	अगर (val.icsk_retransmits != icsk_retransmits) अणु
		log_err("%s: unexpected bpf_tcp_sock.icsk_retransmits %d != %d",
			msg, val.icsk_retransmits, icsk_retransmits);
		err++;
	पूर्ण

	वापस err;
पूर्ण


अटल पूर्णांक run_test(पूर्णांक cgroup_fd, पूर्णांक server_fd)
अणु
	काष्ठा bpf_prog_load_attr attr = अणु
		.prog_type = BPF_PROG_TYPE_SOCK_OPS,
		.file = "./tcp_rtt.o",
		.expected_attach_type = BPF_CGROUP_SOCK_OPS,
	पूर्ण;
	काष्ठा bpf_object *obj;
	काष्ठा bpf_map *map;
	पूर्णांक client_fd;
	पूर्णांक prog_fd;
	पूर्णांक map_fd;
	पूर्णांक err;

	err = bpf_prog_load_xattr(&attr, &obj, &prog_fd);
	अगर (err) अणु
		log_err("Failed to load BPF object");
		वापस -1;
	पूर्ण

	map = bpf_map__next(शून्य, obj);
	map_fd = bpf_map__fd(map);

	err = bpf_prog_attach(prog_fd, cgroup_fd, BPF_CGROUP_SOCK_OPS, 0);
	अगर (err) अणु
		log_err("Failed to attach BPF program");
		जाओ बंद_bpf_object;
	पूर्ण

	client_fd = connect_to_fd(server_fd, 0);
	अगर (client_fd < 0) अणु
		err = -1;
		जाओ बंद_bpf_object;
	पूर्ण

	err += verअगरy_sk(map_fd, client_fd, "syn-ack",
			 /*invoked=*/1,
			 /*dsack_dups=*/0,
			 /*delivered=*/1,
			 /*delivered_ce=*/0,
			 /*icsk_retransmits=*/0);

	send_byte(client_fd);
	अगर (रुको_क्रम_ack(client_fd, 100) < 0) अणु
		err = -1;
		जाओ बंद_client_fd;
	पूर्ण


	err += verअगरy_sk(map_fd, client_fd, "first payload byte",
			 /*invoked=*/2,
			 /*dsack_dups=*/0,
			 /*delivered=*/2,
			 /*delivered_ce=*/0,
			 /*icsk_retransmits=*/0);

बंद_client_fd:
	बंद(client_fd);

बंद_bpf_object:
	bpf_object__बंद(obj);
	वापस err;
पूर्ण

व्योम test_tcp_rtt(व्योम)
अणु
	पूर्णांक server_fd, cgroup_fd;

	cgroup_fd = test__join_cgroup("/tcp_rtt");
	अगर (CHECK_FAIL(cgroup_fd < 0))
		वापस;

	server_fd = start_server(AF_INET, SOCK_STREAM, शून्य, 0, 0);
	अगर (CHECK_FAIL(server_fd < 0))
		जाओ बंद_cgroup_fd;

	CHECK_FAIL(run_test(cgroup_fd, server_fd));

	बंद(server_fd);

बंद_cgroup_fd:
	बंद(cgroup_fd);
पूर्ण
