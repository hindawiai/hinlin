<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2018 Facebook
// Copyright (c) 2019 Cloudflare

#समावेश <सीमा.स>
#समावेश <माला.स>
#समावेश <मानककोष.स>
#समावेश <unistd.h>

#समावेश <arpa/inet.h>
#समावेश <netinet/in.h>
#समावेश <sys/types.h>
#समावेश <sys/socket.h>

#समावेश <bpf/bpf.h>
#समावेश <bpf/libbpf.h>

#समावेश "bpf_rlimit.h"
#समावेश "cgroup_helpers.h"

अटल पूर्णांक start_server(स्थिर काष्ठा sockaddr *addr, socklen_t len)
अणु
	पूर्णांक fd;

	fd = socket(addr->sa_family, SOCK_STREAM, 0);
	अगर (fd == -1) अणु
		log_err("Failed to create server socket");
		जाओ out;
	पूर्ण

	अगर (bind(fd, addr, len) == -1) अणु
		log_err("Failed to bind server socket");
		जाओ बंद_out;
	पूर्ण

	अगर (listen(fd, 128) == -1) अणु
		log_err("Failed to listen on server socket");
		जाओ बंद_out;
	पूर्ण

	जाओ out;

बंद_out:
	बंद(fd);
	fd = -1;
out:
	वापस fd;
पूर्ण

अटल पूर्णांक connect_to_server(पूर्णांक server_fd)
अणु
	काष्ठा sockaddr_storage addr;
	socklen_t len = माप(addr);
	पूर्णांक fd = -1;

	अगर (माला_लोockname(server_fd, (काष्ठा sockaddr *)&addr, &len)) अणु
		log_err("Failed to get server addr");
		जाओ out;
	पूर्ण

	fd = socket(addr.ss_family, SOCK_STREAM, 0);
	अगर (fd == -1) अणु
		log_err("Failed to create client socket");
		जाओ out;
	पूर्ण

	अगर (connect(fd, (स्थिर काष्ठा sockaddr *)&addr, len) == -1) अणु
		log_err("Fail to connect to server");
		जाओ बंद_out;
	पूर्ण

	जाओ out;

बंद_out:
	बंद(fd);
	fd = -1;
out:
	वापस fd;
पूर्ण

अटल पूर्णांक get_map_fd_by_prog_id(पूर्णांक prog_id, bool *xdp)
अणु
	काष्ठा bpf_prog_info info = अणुपूर्ण;
	__u32 info_len = माप(info);
	__u32 map_ids[1];
	पूर्णांक prog_fd = -1;
	पूर्णांक map_fd = -1;

	prog_fd = bpf_prog_get_fd_by_id(prog_id);
	अगर (prog_fd < 0) अणु
		log_err("Failed to get fd by prog id %d", prog_id);
		जाओ err;
	पूर्ण

	info.nr_map_ids = 1;
	info.map_ids = (__u64)(अचिन्हित दीर्घ)map_ids;

	अगर (bpf_obj_get_info_by_fd(prog_fd, &info, &info_len)) अणु
		log_err("Failed to get info by prog fd %d", prog_fd);
		जाओ err;
	पूर्ण

	अगर (!info.nr_map_ids) अणु
		log_err("No maps found for prog fd %d", prog_fd);
		जाओ err;
	पूर्ण

	*xdp = info.type == BPF_PROG_TYPE_XDP;

	map_fd = bpf_map_get_fd_by_id(map_ids[0]);
	अगर (map_fd < 0)
		log_err("Failed to get fd by map id %d", map_ids[0]);
err:
	अगर (prog_fd >= 0)
		बंद(prog_fd);
	वापस map_fd;
पूर्ण

अटल पूर्णांक run_test(पूर्णांक server_fd, पूर्णांक results_fd, bool xdp)
अणु
	पूर्णांक client = -1, srv_client = -1;
	पूर्णांक ret = 0;
	__u32 key = 0;
	__u32 key_gen = 1;
	__u32 key_mss = 2;
	__u32 value = 0;
	__u32 value_gen = 0;
	__u32 value_mss = 0;

	अगर (bpf_map_update_elem(results_fd, &key, &value, 0) < 0) अणु
		log_err("Can't clear results");
		जाओ err;
	पूर्ण

	अगर (bpf_map_update_elem(results_fd, &key_gen, &value_gen, 0) < 0) अणु
		log_err("Can't clear results");
		जाओ err;
	पूर्ण

	अगर (bpf_map_update_elem(results_fd, &key_mss, &value_mss, 0) < 0) अणु
		log_err("Can't clear results");
		जाओ err;
	पूर्ण

	client = connect_to_server(server_fd);
	अगर (client == -1)
		जाओ err;

	srv_client = accept(server_fd, शून्य, 0);
	अगर (srv_client == -1) अणु
		log_err("Can't accept connection");
		जाओ err;
	पूर्ण

	अगर (bpf_map_lookup_elem(results_fd, &key, &value) < 0) अणु
		log_err("Can't lookup result");
		जाओ err;
	पूर्ण

	अगर (value == 0) अणु
		log_err("Didn't match syncookie: %u", value);
		जाओ err;
	पूर्ण

	अगर (bpf_map_lookup_elem(results_fd, &key_gen, &value_gen) < 0) अणु
		log_err("Can't lookup result");
		जाओ err;
	पूर्ण

	अगर (xdp && value_gen == 0) अणु
		// SYN packets करो not get passed through generic XDP, skip the
		// rest of the test.
		म_लिखो("Skipping XDP cookie check\n");
		जाओ out;
	पूर्ण

	अगर (bpf_map_lookup_elem(results_fd, &key_mss, &value_mss) < 0) अणु
		log_err("Can't lookup result");
		जाओ err;
	पूर्ण

	अगर (value != value_gen) अणु
		log_err("BPF generated cookie does not match kernel one");
		जाओ err;
	पूर्ण

	अगर (value_mss < 536 || value_mss > अच_लघु_उच्च) अणु
		log_err("Unexpected MSS retrieved");
		जाओ err;
	पूर्ण

	जाओ out;

err:
	ret = 1;
out:
	बंद(client);
	बंद(srv_client);
	वापस ret;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	काष्ठा sockaddr_in addr4;
	काष्ठा sockaddr_in6 addr6;
	पूर्णांक server = -1;
	पूर्णांक server_v6 = -1;
	पूर्णांक results = -1;
	पूर्णांक err = 0;
	bool xdp;

	अगर (argc < 2) अणु
		ख_लिखो(मानक_त्रुटि, "Usage: %s prog_id\n", argv[0]);
		निकास(1);
	पूर्ण

	results = get_map_fd_by_prog_id(म_से_प(argv[1]), &xdp);
	अगर (results < 0) अणु
		log_err("Can't get map");
		जाओ err;
	पूर्ण

	स_रखो(&addr4, 0, माप(addr4));
	addr4.sin_family = AF_INET;
	addr4.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	addr4.sin_port = 0;

	स_रखो(&addr6, 0, माप(addr6));
	addr6.sin6_family = AF_INET6;
	addr6.sin6_addr = in6addr_loopback;
	addr6.sin6_port = 0;

	server = start_server((स्थिर काष्ठा sockaddr *)&addr4, माप(addr4));
	अगर (server == -1)
		जाओ err;

	server_v6 = start_server((स्थिर काष्ठा sockaddr *)&addr6,
				 माप(addr6));
	अगर (server_v6 == -1)
		जाओ err;

	अगर (run_test(server, results, xdp))
		जाओ err;

	अगर (run_test(server_v6, results, xdp))
		जाओ err;

	म_लिखो("ok\n");
	जाओ out;
err:
	err = 1;
out:
	बंद(server);
	बंद(server_v6);
	बंद(results);
	वापस err;
पूर्ण
