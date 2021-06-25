<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2018 Facebook */

#समावेश <मानककोष.स>
#समावेश <unistd.h>
#समावेश <stdbool.h>
#समावेश <माला.स>
#समावेश <त्रुटिसं.स>
#समावेश <निश्चित.स>
#समावेश <fcntl.h>
#समावेश <linux/bpf.h>
#समावेश <linux/err.h>
#समावेश <linux/types.h>
#समावेश <linux/अगर_ether.h>
#समावेश <sys/types.h>
#समावेश <sys/epoll.h>
#समावेश <sys/socket.h>
#समावेश <netinet/in.h>
#समावेश <bpf/bpf.h>
#समावेश <bpf/libbpf.h>
#समावेश "bpf_rlimit.h"
#समावेश "bpf_util.h"

#समावेश "test_progs.h"
#समावेश "test_select_reuseport_common.h"

#घोषणा MAX_TEST_NAME 80
#घोषणा MIN_TCPHDR_LEN 20
#घोषणा UDPHDR_LEN 8

#घोषणा TCP_SYNCOOKIE_SYSCTL "/proc/sys/net/ipv4/tcp_syncookies"
#घोषणा TCP_FO_SYSCTL "/proc/sys/net/ipv4/tcp_fastopen"
#घोषणा REUSEPORT_ARRAY_SIZE 32

अटल पूर्णांक result_map, पंचांगp_index_ovr_map, linum_map, data_check_map;
अटल __u32 expected_results[NR_RESULTS];
अटल पूर्णांक sk_fds[REUSEPORT_ARRAY_SIZE];
अटल पूर्णांक reuseport_array = -1, outer_map = -1;
अटल क्रमागत bpf_map_type inner_map_type;
अटल पूर्णांक select_by_skb_data_prog;
अटल पूर्णांक saved_tcp_syncookie = -1;
अटल काष्ठा bpf_object *obj;
अटल पूर्णांक saved_tcp_fo = -1;
अटल __u32 index_zero;
अटल पूर्णांक epfd;

अटल जोड़ sa46 अणु
	काष्ठा sockaddr_in6 v6;
	काष्ठा sockaddr_in v4;
	sa_family_t family;
पूर्ण srv_sa;

#घोषणा RET_IF(condition, tag, क्रमmat...) (अणु				\
	अगर (CHECK_FAIL(condition)) अणु					\
		म_लिखो(tag " " क्रमmat);					\
		वापस;							\
	पूर्ण								\
पूर्ण)

#घोषणा RET_ERR(condition, tag, क्रमmat...) (अणु				\
	अगर (CHECK_FAIL(condition)) अणु					\
		म_लिखो(tag " " क्रमmat);					\
		वापस -1;						\
	पूर्ण								\
पूर्ण)

अटल पूर्णांक create_maps(क्रमागत bpf_map_type inner_type)
अणु
	काष्ठा bpf_create_map_attr attr = अणुपूर्ण;

	inner_map_type = inner_type;

	/* Creating reuseport_array */
	attr.name = "reuseport_array";
	attr.map_type = inner_type;
	attr.key_size = माप(__u32);
	attr.value_size = माप(__u32);
	attr.max_entries = REUSEPORT_ARRAY_SIZE;

	reuseport_array = bpf_create_map_xattr(&attr);
	RET_ERR(reuseport_array == -1, "creating reuseport_array",
		"reuseport_array:%d errno:%d\n", reuseport_array, त्रुटि_सं);

	/* Creating outer_map */
	attr.name = "outer_map";
	attr.map_type = BPF_MAP_TYPE_ARRAY_OF_MAPS;
	attr.key_size = माप(__u32);
	attr.value_size = माप(__u32);
	attr.max_entries = 1;
	attr.inner_map_fd = reuseport_array;
	outer_map = bpf_create_map_xattr(&attr);
	RET_ERR(outer_map == -1, "creating outer_map",
		"outer_map:%d errno:%d\n", outer_map, त्रुटि_सं);

	वापस 0;
पूर्ण

अटल पूर्णांक prepare_bpf_obj(व्योम)
अणु
	काष्ठा bpf_program *prog;
	काष्ठा bpf_map *map;
	पूर्णांक err;

	obj = bpf_object__खोलो("test_select_reuseport_kern.o");
	RET_ERR(IS_ERR_OR_शून्य(obj), "open test_select_reuseport_kern.o",
		"obj:%p PTR_ERR(obj):%ld\n", obj, PTR_ERR(obj));

	map = bpf_object__find_map_by_name(obj, "outer_map");
	RET_ERR(!map, "find outer_map", "!map\n");
	err = bpf_map__reuse_fd(map, outer_map);
	RET_ERR(err, "reuse outer_map", "err:%d\n", err);

	err = bpf_object__load(obj);
	RET_ERR(err, "load bpf_object", "err:%d\n", err);

	prog = bpf_program__next(शून्य, obj);
	RET_ERR(!prog, "get first bpf_program", "!prog\n");
	select_by_skb_data_prog = bpf_program__fd(prog);
	RET_ERR(select_by_skb_data_prog == -1, "get prog fd",
		"select_by_skb_data_prog:%d\n", select_by_skb_data_prog);

	map = bpf_object__find_map_by_name(obj, "result_map");
	RET_ERR(!map, "find result_map", "!map\n");
	result_map = bpf_map__fd(map);
	RET_ERR(result_map == -1, "get result_map fd",
		"result_map:%d\n", result_map);

	map = bpf_object__find_map_by_name(obj, "tmp_index_ovr_map");
	RET_ERR(!map, "find tmp_index_ovr_map\n", "!map");
	पंचांगp_index_ovr_map = bpf_map__fd(map);
	RET_ERR(पंचांगp_index_ovr_map == -1, "get tmp_index_ovr_map fd",
		"tmp_index_ovr_map:%d\n", पंचांगp_index_ovr_map);

	map = bpf_object__find_map_by_name(obj, "linum_map");
	RET_ERR(!map, "find linum_map", "!map\n");
	linum_map = bpf_map__fd(map);
	RET_ERR(linum_map == -1, "get linum_map fd",
		"linum_map:%d\n", linum_map);

	map = bpf_object__find_map_by_name(obj, "data_check_map");
	RET_ERR(!map, "find data_check_map", "!map\n");
	data_check_map = bpf_map__fd(map);
	RET_ERR(data_check_map == -1, "get data_check_map fd",
		"data_check_map:%d\n", data_check_map);

	वापस 0;
पूर्ण

अटल व्योम sa46_init_loopback(जोड़ sa46 *sa, sa_family_t family)
अणु
	स_रखो(sa, 0, माप(*sa));
	sa->family = family;
	अगर (sa->family == AF_INET6)
		sa->v6.sin6_addr = in6addr_loopback;
	अन्यथा
		sa->v4.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
पूर्ण

अटल व्योम sa46_init_inany(जोड़ sa46 *sa, sa_family_t family)
अणु
	स_रखो(sa, 0, माप(*sa));
	sa->family = family;
	अगर (sa->family == AF_INET6)
		sa->v6.sin6_addr = in6addr_any;
	अन्यथा
		sa->v4.sin_addr.s_addr = INADDR_ANY;
पूर्ण

अटल पूर्णांक पढ़ो_पूर्णांक_sysctl(स्थिर अक्षर *sysctl)
अणु
	अक्षर buf[16];
	पूर्णांक fd, ret;

	fd = खोलो(sysctl, 0);
	RET_ERR(fd == -1, "open(sysctl)",
		"sysctl:%s fd:%d errno:%d\n", sysctl, fd, त्रुटि_सं);

	ret = पढ़ो(fd, buf, माप(buf));
	RET_ERR(ret <= 0, "read(sysctl)",
		"sysctl:%s ret:%d errno:%d\n", sysctl, ret, त्रुटि_सं);

	बंद(fd);
	वापस म_से_प(buf);
पूर्ण

अटल पूर्णांक ग_लिखो_पूर्णांक_sysctl(स्थिर अक्षर *sysctl, पूर्णांक v)
अणु
	पूर्णांक fd, ret, size;
	अक्षर buf[16];

	fd = खोलो(sysctl, O_RDWR);
	RET_ERR(fd == -1, "open(sysctl)",
		"sysctl:%s fd:%d errno:%d\n", sysctl, fd, त्रुटि_सं);

	size = snम_लिखो(buf, माप(buf), "%d", v);
	ret = ग_लिखो(fd, buf, size);
	RET_ERR(ret != size, "write(sysctl)",
		"sysctl:%s ret:%d size:%d errno:%d\n",
		sysctl, ret, size, त्रुटि_सं);

	बंद(fd);
	वापस 0;
पूर्ण

अटल व्योम restore_sysctls(व्योम)
अणु
	अगर (saved_tcp_fo != -1)
		ग_लिखो_पूर्णांक_sysctl(TCP_FO_SYSCTL, saved_tcp_fo);
	अगर (saved_tcp_syncookie != -1)
		ग_लिखो_पूर्णांक_sysctl(TCP_SYNCOOKIE_SYSCTL, saved_tcp_syncookie);
पूर्ण

अटल पूर्णांक enable_fastखोलो(व्योम)
अणु
	पूर्णांक fo;

	fo = पढ़ो_पूर्णांक_sysctl(TCP_FO_SYSCTL);
	अगर (fo < 0)
		वापस -1;

	वापस ग_लिखो_पूर्णांक_sysctl(TCP_FO_SYSCTL, fo | 7);
पूर्ण

अटल पूर्णांक enable_syncookie(व्योम)
अणु
	वापस ग_लिखो_पूर्णांक_sysctl(TCP_SYNCOOKIE_SYSCTL, 2);
पूर्ण

अटल पूर्णांक disable_syncookie(व्योम)
अणु
	वापस ग_लिखो_पूर्णांक_sysctl(TCP_SYNCOOKIE_SYSCTL, 0);
पूर्ण

अटल दीर्घ get_linum(व्योम)
अणु
	__u32 linum;
	पूर्णांक err;

	err = bpf_map_lookup_elem(linum_map, &index_zero, &linum);
	RET_ERR(err == -1, "lookup_elem(linum_map)", "err:%d errno:%d\n",
		err, त्रुटि_सं);

	वापस linum;
पूर्ण

अटल व्योम check_data(पूर्णांक type, sa_family_t family, स्थिर काष्ठा cmd *cmd,
		       पूर्णांक cli_fd)
अणु
	काष्ठा data_check expected = अणुपूर्ण, result;
	जोड़ sa46 cli_sa;
	socklen_t addrlen;
	पूर्णांक err;

	addrlen = माप(cli_sa);
	err = माला_लोockname(cli_fd, (काष्ठा sockaddr *)&cli_sa,
			  &addrlen);
	RET_IF(err == -1, "getsockname(cli_fd)", "err:%d errno:%d\n",
	       err, त्रुटि_सं);

	err = bpf_map_lookup_elem(data_check_map, &index_zero, &result);
	RET_IF(err == -1, "lookup_elem(data_check_map)", "err:%d errno:%d\n",
	       err, त्रुटि_सं);

	अगर (type == SOCK_STREAM) अणु
		expected.len = MIN_TCPHDR_LEN;
		expected.ip_protocol = IPPROTO_TCP;
	पूर्ण अन्यथा अणु
		expected.len = UDPHDR_LEN;
		expected.ip_protocol = IPPROTO_UDP;
	पूर्ण

	अगर (family == AF_INET6) अणु
		expected.eth_protocol = htons(ETH_P_IPV6);
		expected.bind_inany = !srv_sa.v6.sin6_addr.s6_addr32[3] &&
			!srv_sa.v6.sin6_addr.s6_addr32[2] &&
			!srv_sa.v6.sin6_addr.s6_addr32[1] &&
			!srv_sa.v6.sin6_addr.s6_addr32[0];

		स_नकल(&expected.skb_addrs[0], cli_sa.v6.sin6_addr.s6_addr32,
		       माप(cli_sa.v6.sin6_addr));
		स_नकल(&expected.skb_addrs[4], &in6addr_loopback,
		       माप(in6addr_loopback));
		expected.skb_ports[0] = cli_sa.v6.sin6_port;
		expected.skb_ports[1] = srv_sa.v6.sin6_port;
	पूर्ण अन्यथा अणु
		expected.eth_protocol = htons(ETH_P_IP);
		expected.bind_inany = !srv_sa.v4.sin_addr.s_addr;

		expected.skb_addrs[0] = cli_sa.v4.sin_addr.s_addr;
		expected.skb_addrs[1] = htonl(INADDR_LOOPBACK);
		expected.skb_ports[0] = cli_sa.v4.sin_port;
		expected.skb_ports[1] = srv_sa.v4.sin_port;
	पूर्ण

	अगर (स_भेद(&result, &expected, दुरत्व(काष्ठा data_check,
						equal_check_end))) अणु
		म_लिखो("unexpected data_check\n");
		म_लिखो("  result: (0x%x, %u, %u)\n",
		       result.eth_protocol, result.ip_protocol,
		       result.bind_inany);
		म_लिखो("expected: (0x%x, %u, %u)\n",
		       expected.eth_protocol, expected.ip_protocol,
		       expected.bind_inany);
		RET_IF(1, "data_check result != expected",
		       "bpf_prog_linum:%ld\n", get_linum());
	पूर्ण

	RET_IF(!result.hash, "data_check result.hash empty",
	       "result.hash:%u", result.hash);

	expected.len += cmd ? माप(*cmd) : 0;
	अगर (type == SOCK_STREAM)
		RET_IF(expected.len > result.len, "expected.len > result.len",
		       "expected.len:%u result.len:%u bpf_prog_linum:%ld\n",
		       expected.len, result.len, get_linum());
	अन्यथा
		RET_IF(expected.len != result.len, "expected.len != result.len",
		       "expected.len:%u result.len:%u bpf_prog_linum:%ld\n",
		       expected.len, result.len, get_linum());
पूर्ण

अटल स्थिर अक्षर *result_to_str(क्रमागत result res)
अणु
	चयन (res) अणु
	हाल DROP_ERR_INNER_MAP:
		वापस "DROP_ERR_INNER_MAP";
	हाल DROP_ERR_SKB_DATA:
		वापस "DROP_ERR_SKB_DATA";
	हाल DROP_ERR_SK_SELECT_REUSEPORT:
		वापस "DROP_ERR_SK_SELECT_REUSEPORT";
	हाल DROP_MISC:
		वापस "DROP_MISC";
	हाल PASS:
		वापस "PASS";
	हाल PASS_ERR_SK_SELECT_REUSEPORT:
		वापस "PASS_ERR_SK_SELECT_REUSEPORT";
	शेष:
		वापस "UNKNOWN";
	पूर्ण
पूर्ण

अटल व्योम check_results(व्योम)
अणु
	__u32 results[NR_RESULTS];
	__u32 i, broken = 0;
	पूर्णांक err;

	क्रम (i = 0; i < NR_RESULTS; i++) अणु
		err = bpf_map_lookup_elem(result_map, &i, &results[i]);
		RET_IF(err == -1, "lookup_elem(result_map)",
		       "i:%u err:%d errno:%d\n", i, err, त्रुटि_सं);
	पूर्ण

	क्रम (i = 0; i < NR_RESULTS; i++) अणु
		अगर (results[i] != expected_results[i]) अणु
			broken = i;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (i == NR_RESULTS)
		वापस;

	म_लिखो("unexpected result\n");
	म_लिखो(" result: [");
	म_लिखो("%u", results[0]);
	क्रम (i = 1; i < NR_RESULTS; i++)
		म_लिखो(", %u", results[i]);
	म_लिखो("]\n");

	म_लिखो("expected: [");
	म_लिखो("%u", expected_results[0]);
	क्रम (i = 1; i < NR_RESULTS; i++)
		म_लिखो(", %u", expected_results[i]);
	म_लिखो("]\n");

	म_लिखो("mismatch on %s (bpf_prog_linum:%ld)\n", result_to_str(broken),
	       get_linum());

	CHECK_FAIL(true);
पूर्ण

अटल पूर्णांक send_data(पूर्णांक type, sa_family_t family, व्योम *data, माप_प्रकार len,
		     क्रमागत result expected)
अणु
	जोड़ sa46 cli_sa;
	पूर्णांक fd, err;

	fd = socket(family, type, 0);
	RET_ERR(fd == -1, "socket()", "fd:%d errno:%d\n", fd, त्रुटि_सं);

	sa46_init_loopback(&cli_sa, family);
	err = bind(fd, (काष्ठा sockaddr *)&cli_sa, माप(cli_sa));
	RET_ERR(fd == -1, "bind(cli_sa)", "err:%d errno:%d\n", err, त्रुटि_सं);

	err = sendto(fd, data, len, MSG_FASTOPEN, (काष्ठा sockaddr *)&srv_sa,
		     माप(srv_sa));
	RET_ERR(err != len && expected >= PASS,
		"sendto()", "family:%u err:%d errno:%d expected:%d\n",
		family, err, त्रुटि_सं, expected);

	वापस fd;
पूर्ण

अटल व्योम करो_test(पूर्णांक type, sa_family_t family, काष्ठा cmd *cmd,
		    क्रमागत result expected)
अणु
	पूर्णांक nev, srv_fd, cli_fd;
	काष्ठा epoll_event ev;
	काष्ठा cmd rcv_cmd;
	sमाप_प्रकार nपढ़ो;

	cli_fd = send_data(type, family, cmd, cmd ? माप(*cmd) : 0,
			   expected);
	अगर (cli_fd < 0)
		वापस;
	nev = epoll_रुको(epfd, &ev, 1, expected >= PASS ? 5 : 0);
	RET_IF((nev <= 0 && expected >= PASS) ||
	       (nev > 0 && expected < PASS),
	       "nev <> expected",
	       "nev:%d expected:%d type:%d family:%d data:(%d, %d)\n",
	       nev, expected, type, family,
	       cmd ? cmd->reuseport_index : -1,
	       cmd ? cmd->pass_on_failure : -1);
	check_results();
	check_data(type, family, cmd, cli_fd);

	अगर (expected < PASS)
		वापस;

	RET_IF(expected != PASS_ERR_SK_SELECT_REUSEPORT &&
	       cmd->reuseport_index != ev.data.u32,
	       "check cmd->reuseport_index",
	       "cmd:(%u, %u) ev.data.u32:%u\n",
	       cmd->pass_on_failure, cmd->reuseport_index, ev.data.u32);

	srv_fd = sk_fds[ev.data.u32];
	अगर (type == SOCK_STREAM) अणु
		पूर्णांक new_fd = accept(srv_fd, शून्य, 0);

		RET_IF(new_fd == -1, "accept(srv_fd)",
		       "ev.data.u32:%u new_fd:%d errno:%d\n",
		       ev.data.u32, new_fd, त्रुटि_सं);

		nपढ़ो = recv(new_fd, &rcv_cmd, माप(rcv_cmd), MSG_DONTWAIT);
		RET_IF(nपढ़ो != माप(rcv_cmd),
		       "recv(new_fd)",
		       "ev.data.u32:%u nread:%zd sizeof(rcv_cmd):%zu errno:%d\n",
		       ev.data.u32, nपढ़ो, माप(rcv_cmd), त्रुटि_सं);

		बंद(new_fd);
	पूर्ण अन्यथा अणु
		nपढ़ो = recv(srv_fd, &rcv_cmd, माप(rcv_cmd), MSG_DONTWAIT);
		RET_IF(nपढ़ो != माप(rcv_cmd),
		       "recv(sk_fds)",
		       "ev.data.u32:%u nread:%zd sizeof(rcv_cmd):%zu errno:%d\n",
		       ev.data.u32, nपढ़ो, माप(rcv_cmd), त्रुटि_सं);
	पूर्ण

	बंद(cli_fd);
पूर्ण

अटल व्योम test_err_inner_map(पूर्णांक type, sa_family_t family)
अणु
	काष्ठा cmd cmd = अणु
		.reuseport_index = 0,
		.pass_on_failure = 0,
	पूर्ण;

	expected_results[DROP_ERR_INNER_MAP]++;
	करो_test(type, family, &cmd, DROP_ERR_INNER_MAP);
पूर्ण

अटल व्योम test_err_skb_data(पूर्णांक type, sa_family_t family)
अणु
	expected_results[DROP_ERR_SKB_DATA]++;
	करो_test(type, family, शून्य, DROP_ERR_SKB_DATA);
पूर्ण

अटल व्योम test_err_sk_select_port(पूर्णांक type, sa_family_t family)
अणु
	काष्ठा cmd cmd = अणु
		.reuseport_index = REUSEPORT_ARRAY_SIZE,
		.pass_on_failure = 0,
	पूर्ण;

	expected_results[DROP_ERR_SK_SELECT_REUSEPORT]++;
	करो_test(type, family, &cmd, DROP_ERR_SK_SELECT_REUSEPORT);
पूर्ण

अटल व्योम test_pass(पूर्णांक type, sa_family_t family)
अणु
	काष्ठा cmd cmd;
	पूर्णांक i;

	cmd.pass_on_failure = 0;
	क्रम (i = 0; i < REUSEPORT_ARRAY_SIZE; i++) अणु
		expected_results[PASS]++;
		cmd.reuseport_index = i;
		करो_test(type, family, &cmd, PASS);
	पूर्ण
पूर्ण

अटल व्योम test_syncookie(पूर्णांक type, sa_family_t family)
अणु
	पूर्णांक err, पंचांगp_index = 1;
	काष्ठा cmd cmd = अणु
		.reuseport_index = 0,
		.pass_on_failure = 0,
	पूर्ण;

	/*
	 * +1 क्रम TCP-SYN and
	 * +1 क्रम the TCP-ACK (ack the syncookie)
	 */
	expected_results[PASS] += 2;
	enable_syncookie();
	/*
	 * Simulate TCP-SYN and TCP-ACK are handled by two dअगरferent sk:
	 * TCP-SYN: select sk_fds[पंचांगp_index = 1] पंचांगp_index is from the
	 *          पंचांगp_index_ovr_map
	 * TCP-ACK: select sk_fds[reuseport_index = 0] reuseport_index
	 *          is from the cmd.reuseport_index
	 */
	err = bpf_map_update_elem(पंचांगp_index_ovr_map, &index_zero,
				  &पंचांगp_index, BPF_ANY);
	RET_IF(err == -1, "update_elem(tmp_index_ovr_map, 0, 1)",
	       "err:%d errno:%d\n", err, त्रुटि_सं);
	करो_test(type, family, &cmd, PASS);
	err = bpf_map_lookup_elem(पंचांगp_index_ovr_map, &index_zero,
				  &पंचांगp_index);
	RET_IF(err == -1 || पंचांगp_index != -1,
	       "lookup_elem(tmp_index_ovr_map)",
	       "err:%d errno:%d tmp_index:%d\n",
	       err, त्रुटि_सं, पंचांगp_index);
	disable_syncookie();
पूर्ण

अटल व्योम test_pass_on_err(पूर्णांक type, sa_family_t family)
अणु
	काष्ठा cmd cmd = अणु
		.reuseport_index = REUSEPORT_ARRAY_SIZE,
		.pass_on_failure = 1,
	पूर्ण;

	expected_results[PASS_ERR_SK_SELECT_REUSEPORT] += 1;
	करो_test(type, family, &cmd, PASS_ERR_SK_SELECT_REUSEPORT);
पूर्ण

अटल व्योम test_detach_bpf(पूर्णांक type, sa_family_t family)
अणु
#अगर_घोषित SO_DETACH_REUSEPORT_BPF
	__u32 nr_run_beक्रमe = 0, nr_run_after = 0, पंचांगp, i;
	काष्ठा epoll_event ev;
	पूर्णांक cli_fd, err, nev;
	काष्ठा cmd cmd = अणुपूर्ण;
	पूर्णांक optvalue = 0;

	err = setsockopt(sk_fds[0], SOL_SOCKET, SO_DETACH_REUSEPORT_BPF,
			 &optvalue, माप(optvalue));
	RET_IF(err == -1, "setsockopt(SO_DETACH_REUSEPORT_BPF)",
	       "err:%d errno:%d\n", err, त्रुटि_सं);

	err = setsockopt(sk_fds[1], SOL_SOCKET, SO_DETACH_REUSEPORT_BPF,
			 &optvalue, माप(optvalue));
	RET_IF(err == 0 || त्रुटि_सं != ENOENT,
	       "setsockopt(SO_DETACH_REUSEPORT_BPF)",
	       "err:%d errno:%d\n", err, त्रुटि_सं);

	क्रम (i = 0; i < NR_RESULTS; i++) अणु
		err = bpf_map_lookup_elem(result_map, &i, &पंचांगp);
		RET_IF(err == -1, "lookup_elem(result_map)",
		       "i:%u err:%d errno:%d\n", i, err, त्रुटि_सं);
		nr_run_beक्रमe += पंचांगp;
	पूर्ण

	cli_fd = send_data(type, family, &cmd, माप(cmd), PASS);
	अगर (cli_fd < 0)
		वापस;
	nev = epoll_रुको(epfd, &ev, 1, 5);
	RET_IF(nev <= 0, "nev <= 0",
	       "nev:%d expected:1 type:%d family:%d data:(0, 0)\n",
	       nev,  type, family);

	क्रम (i = 0; i < NR_RESULTS; i++) अणु
		err = bpf_map_lookup_elem(result_map, &i, &पंचांगp);
		RET_IF(err == -1, "lookup_elem(result_map)",
		       "i:%u err:%d errno:%d\n", i, err, त्रुटि_सं);
		nr_run_after += पंचांगp;
	पूर्ण

	RET_IF(nr_run_beक्रमe != nr_run_after,
	       "nr_run_before != nr_run_after",
	       "nr_run_before:%u nr_run_after:%u\n",
	       nr_run_beक्रमe, nr_run_after);

	बंद(cli_fd);
#अन्यथा
	test__skip();
#पूर्ण_अगर
पूर्ण

अटल व्योम prepare_sk_fds(पूर्णांक type, sa_family_t family, bool inany)
अणु
	स्थिर पूर्णांक first = REUSEPORT_ARRAY_SIZE - 1;
	पूर्णांक i, err, optval = 1;
	काष्ठा epoll_event ev;
	socklen_t addrlen;

	अगर (inany)
		sa46_init_inany(&srv_sa, family);
	अन्यथा
		sa46_init_loopback(&srv_sa, family);
	addrlen = माप(srv_sa);

	/*
	 * The sk_fds[] is filled from the back such that the order
	 * is exactly opposite to the (काष्ठा sock_reuseport *)reuse->socks[].
	 */
	क्रम (i = first; i >= 0; i--) अणु
		sk_fds[i] = socket(family, type, 0);
		RET_IF(sk_fds[i] == -1, "socket()", "sk_fds[%d]:%d errno:%d\n",
		       i, sk_fds[i], त्रुटि_सं);
		err = setsockopt(sk_fds[i], SOL_SOCKET, SO_REUSEPORT,
				 &optval, माप(optval));
		RET_IF(err == -1, "setsockopt(SO_REUSEPORT)",
		       "sk_fds[%d] err:%d errno:%d\n",
		       i, err, त्रुटि_सं);

		अगर (i == first) अणु
			err = setsockopt(sk_fds[i], SOL_SOCKET,
					 SO_ATTACH_REUSEPORT_EBPF,
					 &select_by_skb_data_prog,
					 माप(select_by_skb_data_prog));
			RET_IF(err == -1, "setsockopt(SO_ATTACH_REUEPORT_EBPF)",
			       "err:%d errno:%d\n", err, त्रुटि_सं);
		पूर्ण

		err = bind(sk_fds[i], (काष्ठा sockaddr *)&srv_sa, addrlen);
		RET_IF(err == -1, "bind()", "sk_fds[%d] err:%d errno:%d\n",
		       i, err, त्रुटि_सं);

		अगर (type == SOCK_STREAM) अणु
			err = listen(sk_fds[i], 10);
			RET_IF(err == -1, "listen()",
			       "sk_fds[%d] err:%d errno:%d\n",
			       i, err, त्रुटि_सं);
		पूर्ण

		err = bpf_map_update_elem(reuseport_array, &i, &sk_fds[i],
					  BPF_NOEXIST);
		RET_IF(err == -1, "update_elem(reuseport_array)",
		       "sk_fds[%d] err:%d errno:%d\n", i, err, त्रुटि_सं);

		अगर (i == first) अणु
			socklen_t addrlen = माप(srv_sa);

			err = माला_लोockname(sk_fds[i], (काष्ठा sockaddr *)&srv_sa,
					  &addrlen);
			RET_IF(err == -1, "getsockname()",
			       "sk_fds[%d] err:%d errno:%d\n", i, err, त्रुटि_सं);
		पूर्ण
	पूर्ण

	epfd = epoll_create(1);
	RET_IF(epfd == -1, "epoll_create(1)",
	       "epfd:%d errno:%d\n", epfd, त्रुटि_सं);

	ev.events = EPOLLIN;
	क्रम (i = 0; i < REUSEPORT_ARRAY_SIZE; i++) अणु
		ev.data.u32 = i;
		err = epoll_ctl(epfd, EPOLL_CTL_ADD, sk_fds[i], &ev);
		RET_IF(err, "epoll_ctl(EPOLL_CTL_ADD)", "sk_fds[%d]\n", i);
	पूर्ण
पूर्ण

अटल व्योम setup_per_test(पूर्णांक type, sa_family_t family, bool inany,
			   bool no_inner_map)
अणु
	पूर्णांक ovr = -1, err;

	prepare_sk_fds(type, family, inany);
	err = bpf_map_update_elem(पंचांगp_index_ovr_map, &index_zero, &ovr,
				  BPF_ANY);
	RET_IF(err == -1, "update_elem(tmp_index_ovr_map, 0, -1)",
	       "err:%d errno:%d\n", err, त्रुटि_सं);

	/* Install reuseport_array to outer_map? */
	अगर (no_inner_map)
		वापस;

	err = bpf_map_update_elem(outer_map, &index_zero, &reuseport_array,
				  BPF_ANY);
	RET_IF(err == -1, "update_elem(outer_map, 0, reuseport_array)",
	       "err:%d errno:%d\n", err, त्रुटि_सं);
पूर्ण

अटल व्योम cleanup_per_test(bool no_inner_map)
अणु
	पूर्णांक i, err, zero = 0;

	स_रखो(expected_results, 0, माप(expected_results));

	क्रम (i = 0; i < NR_RESULTS; i++) अणु
		err = bpf_map_update_elem(result_map, &i, &zero, BPF_ANY);
		RET_IF(err, "reset elem in result_map",
		       "i:%u err:%d errno:%d\n", i, err, त्रुटि_सं);
	पूर्ण

	err = bpf_map_update_elem(linum_map, &zero, &zero, BPF_ANY);
	RET_IF(err, "reset line number in linum_map", "err:%d errno:%d\n",
	       err, त्रुटि_सं);

	क्रम (i = 0; i < REUSEPORT_ARRAY_SIZE; i++)
		बंद(sk_fds[i]);
	बंद(epfd);

	/* Delete reuseport_array from outer_map? */
	अगर (no_inner_map)
		वापस;

	err = bpf_map_delete_elem(outer_map, &index_zero);
	RET_IF(err == -1, "delete_elem(outer_map)",
	       "err:%d errno:%d\n", err, त्रुटि_सं);
पूर्ण

अटल व्योम cleanup(व्योम)
अणु
	अगर (outer_map != -1) अणु
		बंद(outer_map);
		outer_map = -1;
	पूर्ण

	अगर (reuseport_array != -1) अणु
		बंद(reuseport_array);
		reuseport_array = -1;
	पूर्ण

	अगर (obj) अणु
		bpf_object__बंद(obj);
		obj = शून्य;
	पूर्ण

	स_रखो(expected_results, 0, माप(expected_results));
पूर्ण

अटल स्थिर अक्षर *maptype_str(क्रमागत bpf_map_type type)
अणु
	चयन (type) अणु
	हाल BPF_MAP_TYPE_REUSEPORT_SOCKARRAY:
		वापस "reuseport_sockarray";
	हाल BPF_MAP_TYPE_SOCKMAP:
		वापस "sockmap";
	हाल BPF_MAP_TYPE_SOCKHASH:
		वापस "sockhash";
	शेष:
		वापस "unknown";
	पूर्ण
पूर्ण

अटल स्थिर अक्षर *family_str(sa_family_t family)
अणु
	चयन (family) अणु
	हाल AF_INET:
		वापस "IPv4";
	हाल AF_INET6:
		वापस "IPv6";
	शेष:
		वापस "unknown";
	पूर्ण
पूर्ण

अटल स्थिर अक्षर *sotype_str(पूर्णांक sotype)
अणु
	चयन (sotype) अणु
	हाल SOCK_STREAM:
		वापस "TCP";
	हाल SOCK_DGRAM:
		वापस "UDP";
	शेष:
		वापस "unknown";
	पूर्ण
पूर्ण

#घोषणा TEST_INIT(fn_, ...) अणु .fn = fn_, .name = #fn_, __VA_ARGS__ पूर्ण

अटल व्योम test_config(पूर्णांक sotype, sa_family_t family, bool inany)
अणु
	स्थिर काष्ठा test अणु
		व्योम (*fn)(पूर्णांक sotype, sa_family_t family);
		स्थिर अक्षर *name;
		bool no_inner_map;
		पूर्णांक need_sotype;
	पूर्ण tests[] = अणु
		TEST_INIT(test_err_inner_map,
			  .no_inner_map = true),
		TEST_INIT(test_err_skb_data),
		TEST_INIT(test_err_sk_select_port),
		TEST_INIT(test_pass),
		TEST_INIT(test_syncookie,
			  .need_sotype = SOCK_STREAM),
		TEST_INIT(test_pass_on_err),
		TEST_INIT(test_detach_bpf),
	पूर्ण;
	अक्षर s[MAX_TEST_NAME];
	स्थिर काष्ठा test *t;

	क्रम (t = tests; t < tests + ARRAY_SIZE(tests); t++) अणु
		अगर (t->need_sotype && t->need_sotype != sotype)
			जारी; /* test not compatible with socket type */

		snम_लिखो(s, माप(s), "%s %s/%s %s %s",
			 maptype_str(inner_map_type),
			 family_str(family), sotype_str(sotype),
			 inany ? "INANY" : "LOOPBACK", t->name);

		अगर (!test__start_subtest(s))
			जारी;

		setup_per_test(sotype, family, inany, t->no_inner_map);
		t->fn(sotype, family);
		cleanup_per_test(t->no_inner_map);
	पूर्ण
पूर्ण

#घोषणा BIND_Iन_अंकY true

अटल व्योम test_all(व्योम)
अणु
	स्थिर काष्ठा config अणु
		पूर्णांक sotype;
		sa_family_t family;
		bool inany;
	पूर्ण configs[] = अणु
		अणु SOCK_STREAM, AF_INET पूर्ण,
		अणु SOCK_STREAM, AF_INET, BIND_Iन_अंकY पूर्ण,
		अणु SOCK_STREAM, AF_INET6 पूर्ण,
		अणु SOCK_STREAM, AF_INET6, BIND_Iन_अंकY पूर्ण,
		अणु SOCK_DGRAM, AF_INET पूर्ण,
		अणु SOCK_DGRAM, AF_INET6 पूर्ण,
	पूर्ण;
	स्थिर काष्ठा config *c;

	क्रम (c = configs; c < configs + ARRAY_SIZE(configs); c++)
		test_config(c->sotype, c->family, c->inany);
पूर्ण

व्योम test_map_type(क्रमागत bpf_map_type mt)
अणु
	अगर (create_maps(mt))
		जाओ out;
	अगर (prepare_bpf_obj())
		जाओ out;

	test_all();
out:
	cleanup();
पूर्ण

व्योम test_select_reuseport(व्योम)
अणु
	saved_tcp_fo = पढ़ो_पूर्णांक_sysctl(TCP_FO_SYSCTL);
	अगर (saved_tcp_fo < 0)
		जाओ out;
	saved_tcp_syncookie = पढ़ो_पूर्णांक_sysctl(TCP_SYNCOOKIE_SYSCTL);
	अगर (saved_tcp_syncookie < 0)
		जाओ out;

	अगर (enable_fastखोलो())
		जाओ out;
	अगर (disable_syncookie())
		जाओ out;

	test_map_type(BPF_MAP_TYPE_REUSEPORT_SOCKARRAY);
	test_map_type(BPF_MAP_TYPE_SOCKMAP);
	test_map_type(BPF_MAP_TYPE_SOCKHASH);
out:
	restore_sysctls();
पूर्ण
