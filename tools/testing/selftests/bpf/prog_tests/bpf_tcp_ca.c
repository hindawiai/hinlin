<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2019 Facebook */

#समावेश <linux/err.h>
#समावेश <netinet/tcp.h>
#समावेश <test_progs.h>
#समावेश "bpf_dctcp.skel.h"
#समावेश "bpf_cubic.skel.h"
#समावेश "bpf_tcp_nogpl.skel.h"

#घोषणा min(a, b) ((a) < (b) ? (a) : (b))

अटल स्थिर अचिन्हित पूर्णांक total_bytes = 10 * 1024 * 1024;
अटल स्थिर काष्ठा समयval समयo_sec = अणु .tv_sec = 10 पूर्ण;
अटल स्थिर माप_प्रकार समयo_optlen = माप(समयo_sec);
अटल पूर्णांक expected_stg = 0xeB9F;
अटल पूर्णांक stop, duration;

अटल पूर्णांक समय_रखोo(पूर्णांक fd)
अणु
	पूर्णांक err;

	err = setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, &समयo_sec,
			 समयo_optlen);
	अगर (CHECK(err == -1, "setsockopt(fd, SO_RCVTIMEO)", "errno:%d\n",
		  त्रुटि_सं))
		वापस -1;

	err = setsockopt(fd, SOL_SOCKET, SO_SNDTIMEO, &समयo_sec,
			 समयo_optlen);
	अगर (CHECK(err == -1, "setsockopt(fd, SO_SNDTIMEO)", "errno:%d\n",
		  त्रुटि_सं))
		वापस -1;

	वापस 0;
पूर्ण

अटल पूर्णांक settcpca(पूर्णांक fd, स्थिर अक्षर *tcp_ca)
अणु
	पूर्णांक err;

	err = setsockopt(fd, IPPROTO_TCP, TCP_CONGESTION, tcp_ca, म_माप(tcp_ca));
	अगर (CHECK(err == -1, "setsockopt(fd, TCP_CONGESTION)", "errno:%d\n",
		  त्रुटि_सं))
		वापस -1;

	वापस 0;
पूर्ण

अटल व्योम *server(व्योम *arg)
अणु
	पूर्णांक lfd = (पूर्णांक)(दीर्घ)arg, err = 0, fd;
	sमाप_प्रकार nr_sent = 0, bytes = 0;
	अक्षर batch[1500];

	fd = accept(lfd, शून्य, शून्य);
	जबतक (fd == -1) अणु
		अगर (त्रुटि_सं == EINTR)
			जारी;
		err = -त्रुटि_सं;
		जाओ करोne;
	पूर्ण

	अगर (समय_रखोo(fd)) अणु
		err = -त्रुटि_सं;
		जाओ करोne;
	पूर्ण

	जबतक (bytes < total_bytes && !READ_ONCE(stop)) अणु
		nr_sent = send(fd, &batch,
			       min(total_bytes - bytes, माप(batch)), 0);
		अगर (nr_sent == -1 && त्रुटि_सं == EINTR)
			जारी;
		अगर (nr_sent == -1) अणु
			err = -त्रुटि_सं;
			अवरोध;
		पूर्ण
		bytes += nr_sent;
	पूर्ण

	CHECK(bytes != total_bytes, "send", "%zd != %u nr_sent:%zd errno:%d\n",
	      bytes, total_bytes, nr_sent, त्रुटि_सं);

करोne:
	अगर (fd != -1)
		बंद(fd);
	अगर (err) अणु
		WRITE_ONCE(stop, 1);
		वापस ERR_PTR(err);
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम करो_test(स्थिर अक्षर *tcp_ca, स्थिर काष्ठा bpf_map *sk_stg_map)
अणु
	काष्ठा sockaddr_in6 sa6 = अणुपूर्ण;
	sमाप_प्रकार nr_recv = 0, bytes = 0;
	पूर्णांक lfd = -1, fd = -1;
	pthपढ़ो_t srv_thपढ़ो;
	socklen_t addrlen = माप(sa6);
	व्योम *thपढ़ो_ret;
	अक्षर batch[1500];
	पूर्णांक err;

	WRITE_ONCE(stop, 0);

	lfd = socket(AF_INET6, SOCK_STREAM, 0);
	अगर (CHECK(lfd == -1, "socket", "errno:%d\n", त्रुटि_सं))
		वापस;
	fd = socket(AF_INET6, SOCK_STREAM, 0);
	अगर (CHECK(fd == -1, "socket", "errno:%d\n", त्रुटि_सं)) अणु
		बंद(lfd);
		वापस;
	पूर्ण

	अगर (settcpca(lfd, tcp_ca) || settcpca(fd, tcp_ca) ||
	    समय_रखोo(lfd) || समय_रखोo(fd))
		जाओ करोne;

	/* bind, listen and start server thपढ़ो to accept */
	sa6.sin6_family = AF_INET6;
	sa6.sin6_addr = in6addr_loopback;
	err = bind(lfd, (काष्ठा sockaddr *)&sa6, addrlen);
	अगर (CHECK(err == -1, "bind", "errno:%d\n", त्रुटि_सं))
		जाओ करोne;
	err = माला_लोockname(lfd, (काष्ठा sockaddr *)&sa6, &addrlen);
	अगर (CHECK(err == -1, "getsockname", "errno:%d\n", त्रुटि_सं))
		जाओ करोne;
	err = listen(lfd, 1);
	अगर (CHECK(err == -1, "listen", "errno:%d\n", त्रुटि_सं))
		जाओ करोne;

	अगर (sk_stg_map) अणु
		err = bpf_map_update_elem(bpf_map__fd(sk_stg_map), &fd,
					  &expected_stg, BPF_NOEXIST);
		अगर (CHECK(err, "bpf_map_update_elem(sk_stg_map)",
			  "err:%d errno:%d\n", err, त्रुटि_सं))
			जाओ करोne;
	पूर्ण

	/* connect to server */
	err = connect(fd, (काष्ठा sockaddr *)&sa6, addrlen);
	अगर (CHECK(err == -1, "connect", "errno:%d\n", त्रुटि_सं))
		जाओ करोne;

	अगर (sk_stg_map) अणु
		पूर्णांक पंचांगp_stg;

		err = bpf_map_lookup_elem(bpf_map__fd(sk_stg_map), &fd,
					  &पंचांगp_stg);
		अगर (CHECK(!err || त्रुटि_सं != ENOENT,
			  "bpf_map_lookup_elem(sk_stg_map)",
			  "err:%d errno:%d\n", err, त्रुटि_सं))
			जाओ करोne;
	पूर्ण

	err = pthपढ़ो_create(&srv_thपढ़ो, शून्य, server, (व्योम *)(दीर्घ)lfd);
	अगर (CHECK(err != 0, "pthread_create", "err:%d errno:%d\n", err, त्रुटि_सं))
		जाओ करोne;

	/* recv total_bytes */
	जबतक (bytes < total_bytes && !READ_ONCE(stop)) अणु
		nr_recv = recv(fd, &batch,
			       min(total_bytes - bytes, माप(batch)), 0);
		अगर (nr_recv == -1 && त्रुटि_सं == EINTR)
			जारी;
		अगर (nr_recv == -1)
			अवरोध;
		bytes += nr_recv;
	पूर्ण

	CHECK(bytes != total_bytes, "recv", "%zd != %u nr_recv:%zd errno:%d\n",
	      bytes, total_bytes, nr_recv, त्रुटि_सं);

	WRITE_ONCE(stop, 1);
	pthपढ़ो_join(srv_thपढ़ो, &thपढ़ो_ret);
	CHECK(IS_ERR(thपढ़ो_ret), "pthread_join", "thread_ret:%ld",
	      PTR_ERR(thपढ़ो_ret));
करोne:
	बंद(lfd);
	बंद(fd);
पूर्ण

अटल व्योम test_cubic(व्योम)
अणु
	काष्ठा bpf_cubic *cubic_skel;
	काष्ठा bpf_link *link;

	cubic_skel = bpf_cubic__खोलो_and_load();
	अगर (CHECK(!cubic_skel, "bpf_cubic__open_and_load", "failed\n"))
		वापस;

	link = bpf_map__attach_काष्ठा_ops(cubic_skel->maps.cubic);
	अगर (CHECK(IS_ERR(link), "bpf_map__attach_struct_ops", "err:%ld\n",
		  PTR_ERR(link))) अणु
		bpf_cubic__destroy(cubic_skel);
		वापस;
	पूर्ण

	करो_test("bpf_cubic", शून्य);

	bpf_link__destroy(link);
	bpf_cubic__destroy(cubic_skel);
पूर्ण

अटल व्योम test_dctcp(व्योम)
अणु
	काष्ठा bpf_dctcp *dctcp_skel;
	काष्ठा bpf_link *link;

	dctcp_skel = bpf_dctcp__खोलो_and_load();
	अगर (CHECK(!dctcp_skel, "bpf_dctcp__open_and_load", "failed\n"))
		वापस;

	link = bpf_map__attach_काष्ठा_ops(dctcp_skel->maps.dctcp);
	अगर (CHECK(IS_ERR(link), "bpf_map__attach_struct_ops", "err:%ld\n",
		  PTR_ERR(link))) अणु
		bpf_dctcp__destroy(dctcp_skel);
		वापस;
	पूर्ण

	करो_test("bpf_dctcp", dctcp_skel->maps.sk_stg_map);
	CHECK(dctcp_skel->bss->stg_result != expected_stg,
	      "Unexpected stg_result", "stg_result (%x) != expected_stg (%x)\n",
	      dctcp_skel->bss->stg_result, expected_stg);

	bpf_link__destroy(link);
	bpf_dctcp__destroy(dctcp_skel);
पूर्ण

अटल अक्षर *err_str;
अटल bool found;

अटल पूर्णांक libbpf_debug_prपूर्णांक(क्रमागत libbpf_prपूर्णांक_level level,
			      स्थिर अक्षर *क्रमmat, बहु_सूची args)
अणु
	अक्षर *log_buf;

	अगर (level != LIBBPF_WARN ||
	    म_भेद(क्रमmat, "libbpf: \n%s\n")) अणु
		भ_लिखो(क्रमmat, args);
		वापस 0;
	पूर्ण

	log_buf = बहु_तर्क(args, अक्षर *);
	अगर (!log_buf)
		जाओ out;
	अगर (err_str && म_माला(log_buf, err_str) != शून्य)
		found = true;
out:
	म_लिखो(क्रमmat, log_buf);
	वापस 0;
पूर्ण

अटल व्योम test_invalid_license(व्योम)
अणु
	libbpf_prपूर्णांक_fn_t old_prपूर्णांक_fn;
	काष्ठा bpf_tcp_nogpl *skel;

	err_str = "struct ops programs must have a GPL compatible license";
	found = false;
	old_prपूर्णांक_fn = libbpf_set_prपूर्णांक(libbpf_debug_prपूर्णांक);

	skel = bpf_tcp_nogpl__खोलो_and_load();
	ASSERT_शून्य(skel, "bpf_tcp_nogpl");
	ASSERT_EQ(found, true, "expected_err_msg");

	bpf_tcp_nogpl__destroy(skel);
	libbpf_set_prपूर्णांक(old_prपूर्णांक_fn);
पूर्ण

व्योम test_bpf_tcp_ca(व्योम)
अणु
	अगर (test__start_subtest("dctcp"))
		test_dctcp();
	अगर (test__start_subtest("cubic"))
		test_cubic();
	अगर (test__start_subtest("invalid_license"))
		test_invalid_license();
पूर्ण
