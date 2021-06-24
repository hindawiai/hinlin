<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2020 Facebook */

#घोषणा _GNU_SOURCE
#समावेश <netinet/in.h>
#समावेश <arpa/inet.h>
#समावेश <unistd.h>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <त्रुटिसं.स>
#समावेश <sched.h>
#समावेश <linux/compiler.h>
#समावेश <bpf/libbpf.h>

#समावेश "network_helpers.h"
#समावेश "test_progs.h"
#समावेश "test_btf_skc_cls_ingress.skel.h"

अटल काष्ठा test_btf_skc_cls_ingress *skel;
अटल काष्ठा sockaddr_in6 srv_sa6;
अटल __u32 duration;

#घोषणा PROG_PIN_खाता "/sys/fs/bpf/btf_skc_cls_ingress"

अटल पूर्णांक ग_लिखो_sysctl(स्थिर अक्षर *sysctl, स्थिर अक्षर *value)
अणु
	पूर्णांक fd, err, len;

	fd = खोलो(sysctl, O_WRONLY);
	अगर (CHECK(fd == -1, "open sysctl", "open(%s): %s (%d)\n",
		  sysctl, म_त्रुटि(त्रुटि_सं), त्रुटि_सं))
		वापस -1;

	len = म_माप(value);
	err = ग_लिखो(fd, value, len);
	बंद(fd);
	अगर (CHECK(err != len, "write sysctl",
		  "write(%s, %s, %d): err:%d %s (%d)\n",
		  sysctl, value, len, err, म_त्रुटि(त्रुटि_सं), त्रुटि_सं))
		वापस -1;

	वापस 0;
पूर्ण

अटल पूर्णांक prepare_netns(व्योम)
अणु
	अगर (CHECK(unshare(CLONE_NEWNET), "create netns",
		  "unshare(CLONE_NEWNET): %s (%d)",
		  म_त्रुटि(त्रुटि_सं), त्रुटि_सं))
		वापस -1;

	अगर (CHECK(प्रणाली("ip link set dev lo up"),
		  "ip link set dev lo up", "failed\n"))
		वापस -1;

	अगर (CHECK(प्रणाली("tc qdisc add dev lo clsact"),
		  "tc qdisc add dev lo clsact", "failed\n"))
		वापस -1;

	अगर (CHECK(प्रणाली("tc filter add dev lo ingress bpf direct-action object-pinned " PROG_PIN_खाता),
		  "install tc cls-prog at ingress", "failed\n"))
		वापस -1;

	/* Ensure 20 bytes options (i.e. in total 40 bytes tcp header) क्रम the
	 * bpf_tcp_gen_syncookie() helper.
	 */
	अगर (ग_लिखो_sysctl("/proc/sys/net/ipv4/tcp_window_scaling", "1") ||
	    ग_लिखो_sysctl("/proc/sys/net/ipv4/tcp_timestamps", "1") ||
	    ग_लिखो_sysctl("/proc/sys/net/ipv4/tcp_sack", "1"))
		वापस -1;

	वापस 0;
पूर्ण

अटल व्योम reset_test(व्योम)
अणु
	स_रखो(&skel->bss->srv_sa6, 0, माप(skel->bss->srv_sa6));
	skel->bss->listen_tp_sport = 0;
	skel->bss->req_sk_sport = 0;
	skel->bss->recv_cookie = 0;
	skel->bss->gen_cookie = 0;
	skel->bss->linum = 0;
पूर्ण

अटल व्योम prपूर्णांक_err_line(व्योम)
अणु
	अगर (skel->bss->linum)
		म_लिखो("bpf prog error at line %u\n", skel->bss->linum);
पूर्ण

अटल व्योम test_conn(व्योम)
अणु
	पूर्णांक listen_fd = -1, cli_fd = -1, err;
	socklen_t addrlen = माप(srv_sa6);
	पूर्णांक srv_port;

	अगर (ग_लिखो_sysctl("/proc/sys/net/ipv4/tcp_syncookies", "1"))
		वापस;

	listen_fd = start_server(AF_INET6, SOCK_STREAM, "::1", 0, 0);
	अगर (CHECK_FAIL(listen_fd == -1))
		वापस;

	err = माला_लोockname(listen_fd, (काष्ठा sockaddr *)&srv_sa6, &addrlen);
	अगर (CHECK(err, "getsockname(listen_fd)", "err:%d errno:%d\n", err,
		  त्रुटि_सं))
		जाओ करोne;
	स_नकल(&skel->bss->srv_sa6, &srv_sa6, माप(srv_sa6));
	srv_port = ntohs(srv_sa6.sin6_port);

	cli_fd = connect_to_fd(listen_fd, 0);
	अगर (CHECK_FAIL(cli_fd == -1))
		जाओ करोne;

	अगर (CHECK(skel->bss->listen_tp_sport != srv_port ||
		  skel->bss->req_sk_sport != srv_port,
		  "Unexpected sk src port",
		  "listen_tp_sport:%u req_sk_sport:%u expected:%u\n",
		  skel->bss->listen_tp_sport, skel->bss->req_sk_sport,
		  srv_port))
		जाओ करोne;

	अगर (CHECK(skel->bss->gen_cookie || skel->bss->recv_cookie,
		  "Unexpected syncookie states",
		  "gen_cookie:%u recv_cookie:%u\n",
		  skel->bss->gen_cookie, skel->bss->recv_cookie))
		जाओ करोne;

	CHECK(skel->bss->linum, "bpf prog detected error", "at line %u\n",
	      skel->bss->linum);

करोne:
	अगर (listen_fd != -1)
		बंद(listen_fd);
	अगर (cli_fd != -1)
		बंद(cli_fd);
पूर्ण

अटल व्योम test_syncookie(व्योम)
अणु
	पूर्णांक listen_fd = -1, cli_fd = -1, err;
	socklen_t addrlen = माप(srv_sa6);
	पूर्णांक srv_port;

	/* Enक्रमce syncookie mode */
	अगर (ग_लिखो_sysctl("/proc/sys/net/ipv4/tcp_syncookies", "2"))
		वापस;

	listen_fd = start_server(AF_INET6, SOCK_STREAM, "::1", 0, 0);
	अगर (CHECK_FAIL(listen_fd == -1))
		वापस;

	err = माला_लोockname(listen_fd, (काष्ठा sockaddr *)&srv_sa6, &addrlen);
	अगर (CHECK(err, "getsockname(listen_fd)", "err:%d errno:%d\n", err,
		  त्रुटि_सं))
		जाओ करोne;
	स_नकल(&skel->bss->srv_sa6, &srv_sa6, माप(srv_sa6));
	srv_port = ntohs(srv_sa6.sin6_port);

	cli_fd = connect_to_fd(listen_fd, 0);
	अगर (CHECK_FAIL(cli_fd == -1))
		जाओ करोne;

	अगर (CHECK(skel->bss->listen_tp_sport != srv_port,
		  "Unexpected tp src port",
		  "listen_tp_sport:%u expected:%u\n",
		  skel->bss->listen_tp_sport, srv_port))
		जाओ करोne;

	अगर (CHECK(skel->bss->req_sk_sport,
		  "Unexpected req_sk src port",
		  "req_sk_sport:%u expected:0\n",
		   skel->bss->req_sk_sport))
		जाओ करोne;

	अगर (CHECK(!skel->bss->gen_cookie ||
		  skel->bss->gen_cookie != skel->bss->recv_cookie,
		  "Unexpected syncookie states",
		  "gen_cookie:%u recv_cookie:%u\n",
		  skel->bss->gen_cookie, skel->bss->recv_cookie))
		जाओ करोne;

	CHECK(skel->bss->linum, "bpf prog detected error", "at line %u\n",
	      skel->bss->linum);

करोne:
	अगर (listen_fd != -1)
		बंद(listen_fd);
	अगर (cli_fd != -1)
		बंद(cli_fd);
पूर्ण

काष्ठा test अणु
	स्थिर अक्षर *desc;
	व्योम (*run)(व्योम);
पूर्ण;

#घोषणा DEF_TEST(name) अणु #name, test_##name पूर्ण
अटल काष्ठा test tests[] = अणु
	DEF_TEST(conn),
	DEF_TEST(syncookie),
पूर्ण;

व्योम test_btf_skc_cls_ingress(व्योम)
अणु
	पूर्णांक i, err;

	skel = test_btf_skc_cls_ingress__खोलो_and_load();
	अगर (CHECK(!skel, "test_btf_skc_cls_ingress__open_and_load", "failed\n"))
		वापस;

	err = bpf_program__pin(skel->progs.cls_ingress, PROG_PIN_खाता);
	अगर (CHECK(err, "bpf_program__pin",
		  "cannot pin bpf prog to %s. err:%d\n", PROG_PIN_खाता, err)) अणु
		test_btf_skc_cls_ingress__destroy(skel);
		वापस;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(tests); i++) अणु
		अगर (!test__start_subtest(tests[i].desc))
			जारी;

		अगर (prepare_netns())
			अवरोध;

		tests[i].run();

		prपूर्णांक_err_line();
		reset_test();
	पूर्ण

	bpf_program__unpin(skel->progs.cls_ingress, PROG_PIN_खाता);
	test_btf_skc_cls_ingress__destroy(skel);
पूर्ण
