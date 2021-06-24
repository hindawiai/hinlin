<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2018 Facebook

#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <unistd.h>

#समावेश <arpa/inet.h>
#समावेश <net/अगर.h>
#समावेश <netinet/in.h>
#समावेश <sys/socket.h>
#समावेश <sys/types.h>


#समावेश <bpf/bpf.h>
#समावेश <bpf/libbpf.h>

#समावेश "bpf_rlimit.h"
#समावेश "cgroup_helpers.h"

#घोषणा CGROUP_PATH		"/skb_cgroup_test"
#घोषणा NUM_CGROUP_LEVELS	4

/* RFC 4291, Section 2.7.1 */
#घोषणा LINKLOCAL_MULTICAST	"ff02::1"

अटल पूर्णांक mk_dst_addr(स्थिर अक्षर *ip, स्थिर अक्षर *अगरace,
		       काष्ठा sockaddr_in6 *dst)
अणु
	स_रखो(dst, 0, माप(*dst));

	dst->sin6_family = AF_INET6;
	dst->sin6_port = htons(1025);

	अगर (inet_pton(AF_INET6, ip, &dst->sin6_addr) != 1) अणु
		log_err("Invalid IPv6: %s", ip);
		वापस -1;
	पूर्ण

	dst->sin6_scope_id = अगर_nametoindex(अगरace);
	अगर (!dst->sin6_scope_id) अणु
		log_err("Failed to get index of iface: %s", अगरace);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक send_packet(स्थिर अक्षर *अगरace)
अणु
	काष्ठा sockaddr_in6 dst;
	अक्षर msg[] = "msg";
	पूर्णांक err = 0;
	पूर्णांक fd = -1;

	अगर (mk_dst_addr(LINKLOCAL_MULTICAST, अगरace, &dst))
		जाओ err;

	fd = socket(AF_INET6, SOCK_DGRAM, 0);
	अगर (fd == -1) अणु
		log_err("Failed to create UDP socket");
		जाओ err;
	पूर्ण

	अगर (sendto(fd, &msg, माप(msg), 0, (स्थिर काष्ठा sockaddr *)&dst,
		   माप(dst)) == -1) अणु
		log_err("Failed to send datagram");
		जाओ err;
	पूर्ण

	जाओ out;
err:
	err = -1;
out:
	अगर (fd >= 0)
		बंद(fd);
	वापस err;
पूर्ण

पूर्णांक get_map_fd_by_prog_id(पूर्णांक prog_id)
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
	info.map_ids = (__u64) (अचिन्हित दीर्घ) map_ids;

	अगर (bpf_obj_get_info_by_fd(prog_fd, &info, &info_len)) अणु
		log_err("Failed to get info by prog fd %d", prog_fd);
		जाओ err;
	पूर्ण

	अगर (!info.nr_map_ids) अणु
		log_err("No maps found for prog fd %d", prog_fd);
		जाओ err;
	पूर्ण

	map_fd = bpf_map_get_fd_by_id(map_ids[0]);
	अगर (map_fd < 0)
		log_err("Failed to get fd by map id %d", map_ids[0]);
err:
	अगर (prog_fd >= 0)
		बंद(prog_fd);
	वापस map_fd;
पूर्ण

पूर्णांक check_ancestor_cgroup_ids(पूर्णांक prog_id)
अणु
	__u64 actual_ids[NUM_CGROUP_LEVELS], expected_ids[NUM_CGROUP_LEVELS];
	__u32 level;
	पूर्णांक err = 0;
	पूर्णांक map_fd;

	expected_ids[0] = get_cgroup_id("/..");	/* root cgroup */
	expected_ids[1] = get_cgroup_id("");
	expected_ids[2] = get_cgroup_id(CGROUP_PATH);
	expected_ids[3] = 0; /* non-existent cgroup */

	map_fd = get_map_fd_by_prog_id(prog_id);
	अगर (map_fd < 0)
		जाओ err;

	क्रम (level = 0; level < NUM_CGROUP_LEVELS; ++level) अणु
		अगर (bpf_map_lookup_elem(map_fd, &level, &actual_ids[level])) अणु
			log_err("Failed to lookup key %d", level);
			जाओ err;
		पूर्ण
		अगर (actual_ids[level] != expected_ids[level]) अणु
			log_err("%llx (actual) != %llx (expected), level: %u\n",
				actual_ids[level], expected_ids[level], level);
			जाओ err;
		पूर्ण
	पूर्ण

	जाओ out;
err:
	err = -1;
out:
	अगर (map_fd >= 0)
		बंद(map_fd);
	वापस err;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	पूर्णांक cgfd = -1;
	पूर्णांक err = 0;

	अगर (argc < 3) अणु
		ख_लिखो(मानक_त्रुटि, "Usage: %s iface prog_id\n", argv[0]);
		निकास(निकास_त्रुटि);
	पूर्ण

	cgfd = cgroup_setup_and_join(CGROUP_PATH);
	अगर (cgfd < 0)
		जाओ err;

	अगर (send_packet(argv[1]))
		जाओ err;

	अगर (check_ancestor_cgroup_ids(म_से_प(argv[2])))
		जाओ err;

	जाओ out;
err:
	err = -1;
out:
	बंद(cgfd);
	cleanup_cgroup_environment();
	म_लिखो("[%s]\n", err ? "FAIL" : "PASS");
	वापस err;
पूर्ण
