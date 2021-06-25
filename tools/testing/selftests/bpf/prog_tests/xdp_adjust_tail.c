<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <test_progs.h>
#समावेश <network_helpers.h>

व्योम test_xdp_adjust_tail_shrink(व्योम)
अणु
	स्थिर अक्षर *file = "./test_xdp_adjust_tail_shrink.o";
	__u32 duration, retval, size, expect_sz;
	काष्ठा bpf_object *obj;
	पूर्णांक err, prog_fd;
	अक्षर buf[128];

	err = bpf_prog_load(file, BPF_PROG_TYPE_XDP, &obj, &prog_fd);
	अगर (CHECK_FAIL(err))
		वापस;

	err = bpf_prog_test_run(prog_fd, 1, &pkt_v4, माप(pkt_v4),
				buf, &size, &retval, &duration);

	CHECK(err || retval != XDP_DROP,
	      "ipv4", "err %d errno %d retval %d size %d\n",
	      err, त्रुटि_सं, retval, size);

	expect_sz = माप(pkt_v6) - 20;  /* Test shrink with 20 bytes */
	err = bpf_prog_test_run(prog_fd, 1, &pkt_v6, माप(pkt_v6),
				buf, &size, &retval, &duration);
	CHECK(err || retval != XDP_TX || size != expect_sz,
	      "ipv6", "err %d errno %d retval %d size %d expect-size %d\n",
	      err, त्रुटि_सं, retval, size, expect_sz);
	bpf_object__बंद(obj);
पूर्ण

व्योम test_xdp_adjust_tail_grow(व्योम)
अणु
	स्थिर अक्षर *file = "./test_xdp_adjust_tail_grow.o";
	काष्ठा bpf_object *obj;
	अक्षर buf[4096]; /* aव्योम segfault: large buf to hold grow results */
	__u32 duration, retval, size, expect_sz;
	पूर्णांक err, prog_fd;

	err = bpf_prog_load(file, BPF_PROG_TYPE_XDP, &obj, &prog_fd);
	अगर (CHECK_FAIL(err))
		वापस;

	err = bpf_prog_test_run(prog_fd, 1, &pkt_v4, माप(pkt_v4),
				buf, &size, &retval, &duration);
	CHECK(err || retval != XDP_DROP,
	      "ipv4", "err %d errno %d retval %d size %d\n",
	      err, त्रुटि_सं, retval, size);

	expect_sz = माप(pkt_v6) + 40; /* Test grow with 40 bytes */
	err = bpf_prog_test_run(prog_fd, 1, &pkt_v6, माप(pkt_v6) /* 74 */,
				buf, &size, &retval, &duration);
	CHECK(err || retval != XDP_TX || size != expect_sz,
	      "ipv6", "err %d errno %d retval %d size %d expect-size %d\n",
	      err, त्रुटि_सं, retval, size, expect_sz);

	bpf_object__बंद(obj);
पूर्ण

व्योम test_xdp_adjust_tail_grow2(व्योम)
अणु
	स्थिर अक्षर *file = "./test_xdp_adjust_tail_grow.o";
	अक्षर buf[4096]; /* aव्योम segfault: large buf to hold grow results */
	पूर्णांक tailroom = 320; /* SKB_DATA_ALIGN(माप(काष्ठा skb_shared_info))*/;
	काष्ठा bpf_object *obj;
	पूर्णांक err, cnt, i;
	पूर्णांक max_grow;

	काष्ठा bpf_prog_test_run_attr tattr = अणु
		.repeat		= 1,
		.data_in	= &buf,
		.data_out	= &buf,
		.data_size_in	= 0, /* Per test */
		.data_size_out	= 0, /* Per test */
	पूर्ण;

	err = bpf_prog_load(file, BPF_PROG_TYPE_XDP, &obj, &tattr.prog_fd);
	अगर (CHECK_ATTR(err, "load", "err %d errno %d\n", err, त्रुटि_सं))
		वापस;

	/* Test हाल-64 */
	स_रखो(buf, 1, माप(buf));
	tattr.data_size_in  =  64; /* Determine test हाल via pkt size */
	tattr.data_size_out = 128; /* Limit copy_size */
	/* Kernel side alloc packet memory area that is zero init */
	err = bpf_prog_test_run_xattr(&tattr);

	CHECK_ATTR(त्रुटि_सं != ENOSPC /* Due limit copy_size in bpf_test_finish */
		   || tattr.retval != XDP_TX
		   || tattr.data_size_out != 192, /* Expected grow size */
		   "case-64",
		   "err %d errno %d retval %d size %d\n",
		   err, त्रुटि_सं, tattr.retval, tattr.data_size_out);

	/* Extra checks क्रम data contents */
	CHECK_ATTR(tattr.data_size_out != 192
		   || buf[0]   != 1 ||  buf[63]  != 1  /*  0-63  स_रखो to 1 */
		   || buf[64]  != 0 ||  buf[127] != 0  /* 64-127 स_रखो to 0 */
		   || buf[128] != 1 ||  buf[191] != 1, /*128-191 स_रखो to 1 */
		   "case-64-data",
		   "err %d errno %d retval %d size %d\n",
		   err, त्रुटि_सं, tattr.retval, tattr.data_size_out);

	/* Test हाल-128 */
	स_रखो(buf, 2, माप(buf));
	tattr.data_size_in  = 128; /* Determine test हाल via pkt size */
	tattr.data_size_out = माप(buf);   /* Copy everything */
	err = bpf_prog_test_run_xattr(&tattr);

	max_grow = 4096 - XDP_PACKET_HEADROOM -	tailroom; /* 3520 */
	CHECK_ATTR(err
		   || tattr.retval != XDP_TX
		   || tattr.data_size_out != max_grow,/* Expect max grow size */
		   "case-128",
		   "err %d errno %d retval %d size %d expect-size %d\n",
		   err, त्रुटि_सं, tattr.retval, tattr.data_size_out, max_grow);

	/* Extra checks क्रम data content: Count grow size, will contain zeros */
	क्रम (i = 0, cnt = 0; i < माप(buf); i++) अणु
		अगर (buf[i] == 0)
			cnt++;
	पूर्ण
	CHECK_ATTR((cnt != (max_grow - tattr.data_size_in)) /* Grow increase */
		   || tattr.data_size_out != max_grow, /* Total grow size */
		   "case-128-data",
		   "err %d errno %d retval %d size %d grow-size %d\n",
		   err, त्रुटि_सं, tattr.retval, tattr.data_size_out, cnt);

	bpf_object__बंद(obj);
पूर्ण

व्योम test_xdp_adjust_tail(व्योम)
अणु
	अगर (test__start_subtest("xdp_adjust_tail_shrink"))
		test_xdp_adjust_tail_shrink();
	अगर (test__start_subtest("xdp_adjust_tail_grow"))
		test_xdp_adjust_tail_grow();
	अगर (test__start_subtest("xdp_adjust_tail_grow2"))
		test_xdp_adjust_tail_grow2();
पूर्ण
