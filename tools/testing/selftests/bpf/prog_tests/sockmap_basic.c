<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2020 Cloudflare
#समावेश <error.h>
#समावेश <netinet/tcp.h>

#समावेश "test_progs.h"
#समावेश "test_skmsg_load_helpers.skel.h"
#समावेश "test_sockmap_update.skel.h"
#समावेश "test_sockmap_invalid_update.skel.h"
#समावेश "test_sockmap_skb_verdict_attach.skel.h"
#समावेश "bpf_iter_sockmap.skel.h"

#घोषणा TCP_REPAIR		19	/* TCP sock is under repair right now */

#घोषणा TCP_REPAIR_ON		1
#घोषणा TCP_REPAIR_OFF_NO_WP	-1	/* Turn off without winकरोw probes */

अटल पूर्णांक connected_socket_v4(व्योम)
अणु
	काष्ठा sockaddr_in addr = अणु
		.sin_family = AF_INET,
		.sin_port = htons(80),
		.sin_addr = अणु inet_addr("127.0.0.1") पूर्ण,
	पूर्ण;
	socklen_t len = माप(addr);
	पूर्णांक s, repair, err;

	s = socket(AF_INET, SOCK_STREAM, 0);
	अगर (CHECK_FAIL(s == -1))
		जाओ error;

	repair = TCP_REPAIR_ON;
	err = setsockopt(s, SOL_TCP, TCP_REPAIR, &repair, माप(repair));
	अगर (CHECK_FAIL(err))
		जाओ error;

	err = connect(s, (काष्ठा sockaddr *)&addr, len);
	अगर (CHECK_FAIL(err))
		जाओ error;

	repair = TCP_REPAIR_OFF_NO_WP;
	err = setsockopt(s, SOL_TCP, TCP_REPAIR, &repair, माप(repair));
	अगर (CHECK_FAIL(err))
		जाओ error;

	वापस s;
error:
	लिखो_त्रुटि(__func__);
	बंद(s);
	वापस -1;
पूर्ण

अटल व्योम compare_cookies(काष्ठा bpf_map *src, काष्ठा bpf_map *dst)
अणु
	__u32 i, max_entries = bpf_map__max_entries(src);
	पूर्णांक err, duration = 0, src_fd, dst_fd;

	src_fd = bpf_map__fd(src);
	dst_fd = bpf_map__fd(dst);

	क्रम (i = 0; i < max_entries; i++) अणु
		__u64 src_cookie, dst_cookie;

		err = bpf_map_lookup_elem(src_fd, &i, &src_cookie);
		अगर (err && त्रुटि_सं == ENOENT) अणु
			err = bpf_map_lookup_elem(dst_fd, &i, &dst_cookie);
			CHECK(!err, "map_lookup_elem(dst)", "element %u not deleted\n", i);
			CHECK(err && त्रुटि_सं != ENOENT, "map_lookup_elem(dst)", "%s\n",
			      म_त्रुटि(त्रुटि_सं));
			जारी;
		पूर्ण
		अगर (CHECK(err, "lookup_elem(src)", "%s\n", म_त्रुटि(त्रुटि_सं)))
			जारी;

		err = bpf_map_lookup_elem(dst_fd, &i, &dst_cookie);
		अगर (CHECK(err, "lookup_elem(dst)", "%s\n", म_त्रुटि(त्रुटि_सं)))
			जारी;

		CHECK(dst_cookie != src_cookie, "cookie mismatch",
		      "%llu != %llu (pos %u)\n", dst_cookie, src_cookie, i);
	पूर्ण
पूर्ण

/* Create a map, populate it with one socket, and मुक्त the map. */
अटल व्योम test_sockmap_create_update_मुक्त(क्रमागत bpf_map_type map_type)
अणु
	स्थिर पूर्णांक zero = 0;
	पूर्णांक s, map, err;

	s = connected_socket_v4();
	अगर (CHECK_FAIL(s == -1))
		वापस;

	map = bpf_create_map(map_type, माप(पूर्णांक), माप(पूर्णांक), 1, 0);
	अगर (CHECK_FAIL(map == -1)) अणु
		लिखो_त्रुटि("bpf_create_map");
		जाओ out;
	पूर्ण

	err = bpf_map_update_elem(map, &zero, &s, BPF_NOEXIST);
	अगर (CHECK_FAIL(err)) अणु
		लिखो_त्रुटि("bpf_map_update");
		जाओ out;
	पूर्ण

out:
	बंद(map);
	बंद(s);
पूर्ण

अटल व्योम test_skmsg_helpers(क्रमागत bpf_map_type map_type)
अणु
	काष्ठा test_skmsg_load_helpers *skel;
	पूर्णांक err, map, verdict;

	skel = test_skmsg_load_helpers__खोलो_and_load();
	अगर (CHECK_FAIL(!skel)) अणु
		लिखो_त्रुटि("test_skmsg_load_helpers__open_and_load");
		वापस;
	पूर्ण

	verdict = bpf_program__fd(skel->progs.prog_msg_verdict);
	map = bpf_map__fd(skel->maps.sock_map);

	err = bpf_prog_attach(verdict, map, BPF_SK_MSG_VERDICT, 0);
	अगर (CHECK_FAIL(err)) अणु
		लिखो_त्रुटि("bpf_prog_attach");
		जाओ out;
	पूर्ण

	err = bpf_prog_detach2(verdict, map, BPF_SK_MSG_VERDICT);
	अगर (CHECK_FAIL(err)) अणु
		लिखो_त्रुटि("bpf_prog_detach2");
		जाओ out;
	पूर्ण
out:
	test_skmsg_load_helpers__destroy(skel);
पूर्ण

अटल व्योम test_sockmap_update(क्रमागत bpf_map_type map_type)
अणु
	काष्ठा bpf_prog_test_run_attr tattr;
	पूर्णांक err, prog, src, duration = 0;
	काष्ठा test_sockmap_update *skel;
	काष्ठा bpf_map *dst_map;
	स्थिर __u32 zero = 0;
	अक्षर dummy[14] = अणु0पूर्ण;
	__s64 sk;

	sk = connected_socket_v4();
	अगर (CHECK(sk == -1, "connected_socket_v4", "cannot connect\n"))
		वापस;

	skel = test_sockmap_update__खोलो_and_load();
	अगर (CHECK(!skel, "open_and_load", "cannot load skeleton\n"))
		जाओ बंद_sk;

	prog = bpf_program__fd(skel->progs.copy_sock_map);
	src = bpf_map__fd(skel->maps.src);
	अगर (map_type == BPF_MAP_TYPE_SOCKMAP)
		dst_map = skel->maps.dst_sock_map;
	अन्यथा
		dst_map = skel->maps.dst_sock_hash;

	err = bpf_map_update_elem(src, &zero, &sk, BPF_NOEXIST);
	अगर (CHECK(err, "update_elem(src)", "errno=%u\n", त्रुटि_सं))
		जाओ out;

	tattr = (काष्ठा bpf_prog_test_run_attr)अणु
		.prog_fd = prog,
		.repeat = 1,
		.data_in = dummy,
		.data_size_in = माप(dummy),
	पूर्ण;

	err = bpf_prog_test_run_xattr(&tattr);
	अगर (CHECK_ATTR(err || !tattr.retval, "bpf_prog_test_run",
		       "errno=%u retval=%u\n", त्रुटि_सं, tattr.retval))
		जाओ out;

	compare_cookies(skel->maps.src, dst_map);

out:
	test_sockmap_update__destroy(skel);
बंद_sk:
	बंद(sk);
पूर्ण

अटल व्योम test_sockmap_invalid_update(व्योम)
अणु
	काष्ठा test_sockmap_invalid_update *skel;
	पूर्णांक duration = 0;

	skel = test_sockmap_invalid_update__खोलो_and_load();
	अगर (CHECK(skel, "open_and_load", "verifier accepted map_update\n"))
		test_sockmap_invalid_update__destroy(skel);
पूर्ण

अटल व्योम test_sockmap_copy(क्रमागत bpf_map_type map_type)
अणु
	DECLARE_LIBBPF_OPTS(bpf_iter_attach_opts, opts);
	पूर्णांक err, len, src_fd, iter_fd, duration = 0;
	जोड़ bpf_iter_link_info linfo = अणुपूर्ण;
	__u32 i, num_sockets, num_elems;
	काष्ठा bpf_iter_sockmap *skel;
	__s64 *sock_fd = शून्य;
	काष्ठा bpf_link *link;
	काष्ठा bpf_map *src;
	अक्षर buf[64];

	skel = bpf_iter_sockmap__खोलो_and_load();
	अगर (CHECK(!skel, "bpf_iter_sockmap__open_and_load", "skeleton open_and_load failed\n"))
		वापस;

	अगर (map_type == BPF_MAP_TYPE_SOCKMAP) अणु
		src = skel->maps.sockmap;
		num_elems = bpf_map__max_entries(src);
		num_sockets = num_elems - 1;
	पूर्ण अन्यथा अणु
		src = skel->maps.sockhash;
		num_elems = bpf_map__max_entries(src) - 1;
		num_sockets = num_elems;
	पूर्ण

	sock_fd = सुस्मृति(num_sockets, माप(*sock_fd));
	अगर (CHECK(!sock_fd, "calloc(sock_fd)", "failed to allocate\n"))
		जाओ out;

	क्रम (i = 0; i < num_sockets; i++)
		sock_fd[i] = -1;

	src_fd = bpf_map__fd(src);

	क्रम (i = 0; i < num_sockets; i++) अणु
		sock_fd[i] = connected_socket_v4();
		अगर (CHECK(sock_fd[i] == -1, "connected_socket_v4", "cannot connect\n"))
			जाओ out;

		err = bpf_map_update_elem(src_fd, &i, &sock_fd[i], BPF_NOEXIST);
		अगर (CHECK(err, "map_update", "failed: %s\n", म_त्रुटि(त्रुटि_सं)))
			जाओ out;
	पूर्ण

	linfo.map.map_fd = src_fd;
	opts.link_info = &linfo;
	opts.link_info_len = माप(linfo);
	link = bpf_program__attach_iter(skel->progs.copy, &opts);
	अगर (CHECK(IS_ERR(link), "attach_iter", "attach_iter failed\n"))
		जाओ out;

	iter_fd = bpf_iter_create(bpf_link__fd(link));
	अगर (CHECK(iter_fd < 0, "create_iter", "create_iter failed\n"))
		जाओ मुक्त_link;

	/* करो some tests */
	जबतक ((len = पढ़ो(iter_fd, buf, माप(buf))) > 0)
		;
	अगर (CHECK(len < 0, "read", "failed: %s\n", म_त्रुटि(त्रुटि_सं)))
		जाओ बंद_iter;

	/* test results */
	अगर (CHECK(skel->bss->elems != num_elems, "elems", "got %u expected %u\n",
		  skel->bss->elems, num_elems))
		जाओ बंद_iter;

	अगर (CHECK(skel->bss->socks != num_sockets, "socks", "got %u expected %u\n",
		  skel->bss->socks, num_sockets))
		जाओ बंद_iter;

	compare_cookies(src, skel->maps.dst);

बंद_iter:
	बंद(iter_fd);
मुक्त_link:
	bpf_link__destroy(link);
out:
	क्रम (i = 0; sock_fd && i < num_sockets; i++)
		अगर (sock_fd[i] >= 0)
			बंद(sock_fd[i]);
	अगर (sock_fd)
		मुक्त(sock_fd);
	bpf_iter_sockmap__destroy(skel);
पूर्ण

अटल व्योम test_sockmap_skb_verdict_attach(क्रमागत bpf_attach_type first,
					    क्रमागत bpf_attach_type second)
अणु
	काष्ठा test_sockmap_skb_verdict_attach *skel;
	पूर्णांक err, map, verdict;

	skel = test_sockmap_skb_verdict_attach__खोलो_and_load();
	अगर (CHECK_FAIL(!skel)) अणु
		लिखो_त्रुटि("test_sockmap_skb_verdict_attach__open_and_load");
		वापस;
	पूर्ण

	verdict = bpf_program__fd(skel->progs.prog_skb_verdict);
	map = bpf_map__fd(skel->maps.sock_map);

	err = bpf_prog_attach(verdict, map, first, 0);
	अगर (CHECK_FAIL(err)) अणु
		लिखो_त्रुटि("bpf_prog_attach");
		जाओ out;
	पूर्ण

	err = bpf_prog_attach(verdict, map, second, 0);
	निश्चित(err == -1 && त्रुटि_सं == EBUSY);

	err = bpf_prog_detach2(verdict, map, first);
	अगर (CHECK_FAIL(err)) अणु
		लिखो_त्रुटि("bpf_prog_detach2");
		जाओ out;
	पूर्ण
out:
	test_sockmap_skb_verdict_attach__destroy(skel);
पूर्ण

व्योम test_sockmap_basic(व्योम)
अणु
	अगर (test__start_subtest("sockmap create_update_free"))
		test_sockmap_create_update_मुक्त(BPF_MAP_TYPE_SOCKMAP);
	अगर (test__start_subtest("sockhash create_update_free"))
		test_sockmap_create_update_मुक्त(BPF_MAP_TYPE_SOCKHASH);
	अगर (test__start_subtest("sockmap sk_msg load helpers"))
		test_skmsg_helpers(BPF_MAP_TYPE_SOCKMAP);
	अगर (test__start_subtest("sockhash sk_msg load helpers"))
		test_skmsg_helpers(BPF_MAP_TYPE_SOCKHASH);
	अगर (test__start_subtest("sockmap update"))
		test_sockmap_update(BPF_MAP_TYPE_SOCKMAP);
	अगर (test__start_subtest("sockhash update"))
		test_sockmap_update(BPF_MAP_TYPE_SOCKHASH);
	अगर (test__start_subtest("sockmap update in unsafe context"))
		test_sockmap_invalid_update();
	अगर (test__start_subtest("sockmap copy"))
		test_sockmap_copy(BPF_MAP_TYPE_SOCKMAP);
	अगर (test__start_subtest("sockhash copy"))
		test_sockmap_copy(BPF_MAP_TYPE_SOCKHASH);
	अगर (test__start_subtest("sockmap skb_verdict attach")) अणु
		test_sockmap_skb_verdict_attach(BPF_SK_SKB_VERDICT,
						BPF_SK_SKB_STREAM_VERDICT);
		test_sockmap_skb_verdict_attach(BPF_SK_SKB_STREAM_VERDICT,
						BPF_SK_SKB_VERDICT);
	पूर्ण
पूर्ण
