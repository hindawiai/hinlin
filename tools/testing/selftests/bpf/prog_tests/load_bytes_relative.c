<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

/*
 * Copyright 2020 Google LLC.
 */

#समावेश <test_progs.h>
#समावेश <network_helpers.h>

व्योम test_load_bytes_relative(व्योम)
अणु
	पूर्णांक server_fd, cgroup_fd, prog_fd, map_fd, client_fd;
	पूर्णांक err;
	काष्ठा bpf_object *obj;
	काष्ठा bpf_program *prog;
	काष्ठा bpf_map *test_result;
	__u32 duration = 0;

	__u32 map_key = 0;
	__u32 map_value = 0;

	cgroup_fd = test__join_cgroup("/load_bytes_relative");
	अगर (CHECK_FAIL(cgroup_fd < 0))
		वापस;

	server_fd = start_server(AF_INET, SOCK_STREAM, शून्य, 0, 0);
	अगर (CHECK_FAIL(server_fd < 0))
		जाओ बंद_cgroup_fd;

	err = bpf_prog_load("./load_bytes_relative.o", BPF_PROG_TYPE_CGROUP_SKB,
			    &obj, &prog_fd);
	अगर (CHECK_FAIL(err))
		जाओ बंद_server_fd;

	test_result = bpf_object__find_map_by_name(obj, "test_result");
	अगर (CHECK_FAIL(!test_result))
		जाओ बंद_bpf_object;

	map_fd = bpf_map__fd(test_result);
	अगर (map_fd < 0)
		जाओ बंद_bpf_object;

	prog = bpf_object__find_program_by_name(obj, "load_bytes_relative");
	अगर (CHECK_FAIL(!prog))
		जाओ बंद_bpf_object;

	err = bpf_prog_attach(prog_fd, cgroup_fd, BPF_CGROUP_INET_EGRESS,
			      BPF_F_ALLOW_MULTI);
	अगर (CHECK_FAIL(err))
		जाओ बंद_bpf_object;

	client_fd = connect_to_fd(server_fd, 0);
	अगर (CHECK_FAIL(client_fd < 0))
		जाओ बंद_bpf_object;
	बंद(client_fd);

	err = bpf_map_lookup_elem(map_fd, &map_key, &map_value);
	अगर (CHECK_FAIL(err))
		जाओ बंद_bpf_object;

	CHECK(map_value != 1, "bpf", "bpf program returned failure");

बंद_bpf_object:
	bpf_object__बंद(obj);

बंद_server_fd:
	बंद(server_fd);

बंद_cgroup_fd:
	बंद(cgroup_fd);
पूर्ण
