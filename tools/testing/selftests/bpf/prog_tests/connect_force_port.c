<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <test_progs.h>
#समावेश "cgroup_helpers.h"
#समावेश "network_helpers.h"

अटल पूर्णांक verअगरy_ports(पूर्णांक family, पूर्णांक fd,
			__u16 expected_local, __u16 expected_peer)
अणु
	काष्ठा sockaddr_storage addr;
	socklen_t len = माप(addr);
	__u16 port;

	अगर (माला_लोockname(fd, (काष्ठा sockaddr *)&addr, &len)) अणु
		log_err("Failed to get server addr");
		वापस -1;
	पूर्ण

	अगर (family == AF_INET)
		port = ((काष्ठा sockaddr_in *)&addr)->sin_port;
	अन्यथा
		port = ((काष्ठा sockaddr_in6 *)&addr)->sin6_port;

	अगर (ntohs(port) != expected_local) अणु
		log_err("Unexpected local port %d, expected %d", ntohs(port),
			expected_local);
		वापस -1;
	पूर्ण

	अगर (getpeername(fd, (काष्ठा sockaddr *)&addr, &len)) अणु
		log_err("Failed to get peer addr");
		वापस -1;
	पूर्ण

	अगर (family == AF_INET)
		port = ((काष्ठा sockaddr_in *)&addr)->sin_port;
	अन्यथा
		port = ((काष्ठा sockaddr_in6 *)&addr)->sin6_port;

	अगर (ntohs(port) != expected_peer) अणु
		log_err("Unexpected peer port %d, expected %d", ntohs(port),
			expected_peer);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक run_test(पूर्णांक cgroup_fd, पूर्णांक server_fd, पूर्णांक family, पूर्णांक type)
अणु
	bool v4 = family == AF_INET;
	__u16 expected_local_port = v4 ? 22222 : 22223;
	__u16 expected_peer_port = 60000;
	काष्ठा bpf_prog_load_attr attr = अणु
		.file = v4 ? "./connect_force_port4.o" :
			     "./connect_force_port6.o",
	पूर्ण;
	काष्ठा bpf_program *prog;
	काष्ठा bpf_object *obj;
	पूर्णांक xlate_fd, fd, err;
	__u32 duration = 0;

	err = bpf_prog_load_xattr(&attr, &obj, &xlate_fd);
	अगर (err) अणु
		log_err("Failed to load BPF object");
		वापस -1;
	पूर्ण

	prog = bpf_object__find_program_by_title(obj, v4 ?
						 "cgroup/connect4" :
						 "cgroup/connect6");
	अगर (CHECK(!prog, "find_prog", "connect prog not found\n")) अणु
		err = -EIO;
		जाओ बंद_bpf_object;
	पूर्ण

	err = bpf_prog_attach(bpf_program__fd(prog), cgroup_fd, v4 ?
			      BPF_CGROUP_INET4_CONNECT :
			      BPF_CGROUP_INET6_CONNECT, 0);
	अगर (err) अणु
		log_err("Failed to attach BPF program");
		जाओ बंद_bpf_object;
	पूर्ण

	prog = bpf_object__find_program_by_title(obj, v4 ?
						 "cgroup/getpeername4" :
						 "cgroup/getpeername6");
	अगर (CHECK(!prog, "find_prog", "getpeername prog not found\n")) अणु
		err = -EIO;
		जाओ बंद_bpf_object;
	पूर्ण

	err = bpf_prog_attach(bpf_program__fd(prog), cgroup_fd, v4 ?
			      BPF_CGROUP_INET4_GETPEERNAME :
			      BPF_CGROUP_INET6_GETPEERNAME, 0);
	अगर (err) अणु
		log_err("Failed to attach BPF program");
		जाओ बंद_bpf_object;
	पूर्ण

	prog = bpf_object__find_program_by_title(obj, v4 ?
						 "cgroup/getsockname4" :
						 "cgroup/getsockname6");
	अगर (CHECK(!prog, "find_prog", "getsockname prog not found\n")) अणु
		err = -EIO;
		जाओ बंद_bpf_object;
	पूर्ण

	err = bpf_prog_attach(bpf_program__fd(prog), cgroup_fd, v4 ?
			      BPF_CGROUP_INET4_GETSOCKNAME :
			      BPF_CGROUP_INET6_GETSOCKNAME, 0);
	अगर (err) अणु
		log_err("Failed to attach BPF program");
		जाओ बंद_bpf_object;
	पूर्ण

	fd = connect_to_fd(server_fd, 0);
	अगर (fd < 0) अणु
		err = -1;
		जाओ बंद_bpf_object;
	पूर्ण

	err = verअगरy_ports(family, fd, expected_local_port,
			   expected_peer_port);
	बंद(fd);

बंद_bpf_object:
	bpf_object__बंद(obj);
	वापस err;
पूर्ण

व्योम test_connect_क्रमce_port(व्योम)
अणु
	पूर्णांक server_fd, cgroup_fd;

	cgroup_fd = test__join_cgroup("/connect_force_port");
	अगर (CHECK_FAIL(cgroup_fd < 0))
		वापस;

	server_fd = start_server(AF_INET, SOCK_STREAM, शून्य, 60123, 0);
	अगर (CHECK_FAIL(server_fd < 0))
		जाओ बंद_cgroup_fd;
	CHECK_FAIL(run_test(cgroup_fd, server_fd, AF_INET, SOCK_STREAM));
	बंद(server_fd);

	server_fd = start_server(AF_INET6, SOCK_STREAM, शून्य, 60124, 0);
	अगर (CHECK_FAIL(server_fd < 0))
		जाओ बंद_cgroup_fd;
	CHECK_FAIL(run_test(cgroup_fd, server_fd, AF_INET6, SOCK_STREAM));
	बंद(server_fd);

	server_fd = start_server(AF_INET, SOCK_DGRAM, शून्य, 60123, 0);
	अगर (CHECK_FAIL(server_fd < 0))
		जाओ बंद_cgroup_fd;
	CHECK_FAIL(run_test(cgroup_fd, server_fd, AF_INET, SOCK_DGRAM));
	बंद(server_fd);

	server_fd = start_server(AF_INET6, SOCK_DGRAM, शून्य, 60124, 0);
	अगर (CHECK_FAIL(server_fd < 0))
		जाओ बंद_cgroup_fd;
	CHECK_FAIL(run_test(cgroup_fd, server_fd, AF_INET6, SOCK_DGRAM));
	बंद(server_fd);

बंद_cgroup_fd:
	बंद(cgroup_fd);
पूर्ण
