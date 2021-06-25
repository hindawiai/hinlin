<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2020 Jesper Dangaard Brouer */

#समावेश <linux/अगर_link.h> /* beक्रमe test_progs.h, aव्योम bpf_util.h redefines */
#समावेश <test_progs.h>
#समावेश "test_check_mtu.skel.h"
#समावेश "network_helpers.h"

#समावेश <मानककोष.स>
#समावेश <पूर्णांकtypes.h>

#घोषणा IFINDEX_LO 1

अटल __u32 duration; /* Hपूर्णांक: needed क्रम CHECK macro */

अटल पूर्णांक पढ़ो_mtu_device_lo(व्योम)
अणु
	स्थिर अक्षर *filename = "/sys/class/net/lo/mtu";
	अक्षर buf[11] = अणुपूर्ण;
	पूर्णांक value, n, fd;

	fd = खोलो(filename, 0, O_RDONLY);
	अगर (fd == -1)
		वापस -1;

	n = पढ़ो(fd, buf, माप(buf));
	बंद(fd);

	अगर (n == -1)
		वापस -2;

	value = strtoimax(buf, शून्य, 10);
	अगर (त्रुटि_सं == दुस्फल)
		वापस -3;

	वापस value;
पूर्ण

अटल व्योम test_check_mtu_xdp_attach(व्योम)
अणु
	काष्ठा bpf_link_info link_info;
	__u32 link_info_len = माप(link_info);
	काष्ठा test_check_mtu *skel;
	काष्ठा bpf_program *prog;
	काष्ठा bpf_link *link;
	पूर्णांक err = 0;
	पूर्णांक fd;

	skel = test_check_mtu__खोलो_and_load();
	अगर (CHECK(!skel, "open and load skel", "failed"))
		वापस; /* Exit अगर e.g. helper unknown to kernel */

	prog = skel->progs.xdp_use_helper_basic;

	link = bpf_program__attach_xdp(prog, IFINDEX_LO);
	अगर (CHECK(IS_ERR(link), "link_attach", "failed: %ld\n", PTR_ERR(link)))
		जाओ out;
	skel->links.xdp_use_helper_basic = link;

	स_रखो(&link_info, 0, माप(link_info));
	fd = bpf_link__fd(link);
	err = bpf_obj_get_info_by_fd(fd, &link_info, &link_info_len);
	अगर (CHECK(err, "link_info", "failed: %d\n", err))
		जाओ out;

	CHECK(link_info.type != BPF_LINK_TYPE_XDP, "link_type",
	      "got %u != exp %u\n", link_info.type, BPF_LINK_TYPE_XDP);
	CHECK(link_info.xdp.अगरindex != IFINDEX_LO, "link_ifindex",
	      "got %u != exp %u\n", link_info.xdp.अगरindex, IFINDEX_LO);

	err = bpf_link__detach(link);
	CHECK(err, "link_detach", "failed %d\n", err);

out:
	test_check_mtu__destroy(skel);
पूर्ण

अटल व्योम test_check_mtu_run_xdp(काष्ठा test_check_mtu *skel,
				   काष्ठा bpf_program *prog,
				   __u32 mtu_expect)
अणु
	स्थिर अक्षर *prog_name = bpf_program__name(prog);
	पूर्णांक retval_expect = XDP_PASS;
	__u32 mtu_result = 0;
	अक्षर buf[256] = अणुपूर्ण;
	पूर्णांक err;
	काष्ठा bpf_prog_test_run_attr tattr = अणु
		.repeat = 1,
		.data_in = &pkt_v4,
		.data_size_in = माप(pkt_v4),
		.data_out = buf,
		.data_size_out = माप(buf),
		.prog_fd = bpf_program__fd(prog),
	पूर्ण;

	err = bpf_prog_test_run_xattr(&tattr);
	CHECK_ATTR(err != 0, "bpf_prog_test_run",
		   "prog_name:%s (err %d errno %d retval %d)\n",
		   prog_name, err, त्रुटि_सं, tattr.retval);

	CHECK(tattr.retval != retval_expect, "retval",
	      "progname:%s unexpected retval=%d expected=%d\n",
	      prog_name, tattr.retval, retval_expect);

	/* Extract MTU that BPF-prog got */
	mtu_result = skel->bss->global_bpf_mtu_xdp;
	ASSERT_EQ(mtu_result, mtu_expect, "MTU-compare-user");
पूर्ण


अटल व्योम test_check_mtu_xdp(__u32 mtu, __u32 अगरindex)
अणु
	काष्ठा test_check_mtu *skel;
	पूर्णांक err;

	skel = test_check_mtu__खोलो();
	अगर (CHECK(!skel, "skel_open", "failed"))
		वापस;

	/* Update "constants" in BPF-prog *BEFORE* libbpf load */
	skel->rodata->GLOBAL_USER_MTU = mtu;
	skel->rodata->GLOBAL_USER_IFINDEX = अगरindex;

	err = test_check_mtu__load(skel);
	अगर (CHECK(err, "skel_load", "failed: %d\n", err))
		जाओ cleanup;

	test_check_mtu_run_xdp(skel, skel->progs.xdp_use_helper, mtu);
	test_check_mtu_run_xdp(skel, skel->progs.xdp_exceed_mtu, mtu);
	test_check_mtu_run_xdp(skel, skel->progs.xdp_minus_delta, mtu);
	test_check_mtu_run_xdp(skel, skel->progs.xdp_input_len, mtu);
	test_check_mtu_run_xdp(skel, skel->progs.xdp_input_len_exceed, mtu);

cleanup:
	test_check_mtu__destroy(skel);
पूर्ण

अटल व्योम test_check_mtu_run_tc(काष्ठा test_check_mtu *skel,
				  काष्ठा bpf_program *prog,
				  __u32 mtu_expect)
अणु
	स्थिर अक्षर *prog_name = bpf_program__name(prog);
	पूर्णांक retval_expect = BPF_OK;
	__u32 mtu_result = 0;
	अक्षर buf[256] = अणुपूर्ण;
	पूर्णांक err;
	काष्ठा bpf_prog_test_run_attr tattr = अणु
		.repeat = 1,
		.data_in = &pkt_v4,
		.data_size_in = माप(pkt_v4),
		.data_out = buf,
		.data_size_out = माप(buf),
		.prog_fd = bpf_program__fd(prog),
	पूर्ण;

	err = bpf_prog_test_run_xattr(&tattr);
	CHECK_ATTR(err != 0, "bpf_prog_test_run",
		   "prog_name:%s (err %d errno %d retval %d)\n",
		   prog_name, err, त्रुटि_सं, tattr.retval);

	CHECK(tattr.retval != retval_expect, "retval",
	      "progname:%s unexpected retval=%d expected=%d\n",
	      prog_name, tattr.retval, retval_expect);

	/* Extract MTU that BPF-prog got */
	mtu_result = skel->bss->global_bpf_mtu_tc;
	ASSERT_EQ(mtu_result, mtu_expect, "MTU-compare-user");
पूर्ण


अटल व्योम test_check_mtu_tc(__u32 mtu, __u32 अगरindex)
अणु
	काष्ठा test_check_mtu *skel;
	पूर्णांक err;

	skel = test_check_mtu__खोलो();
	अगर (CHECK(!skel, "skel_open", "failed"))
		वापस;

	/* Update "constants" in BPF-prog *BEFORE* libbpf load */
	skel->rodata->GLOBAL_USER_MTU = mtu;
	skel->rodata->GLOBAL_USER_IFINDEX = अगरindex;

	err = test_check_mtu__load(skel);
	अगर (CHECK(err, "skel_load", "failed: %d\n", err))
		जाओ cleanup;

	test_check_mtu_run_tc(skel, skel->progs.tc_use_helper, mtu);
	test_check_mtu_run_tc(skel, skel->progs.tc_exceed_mtu, mtu);
	test_check_mtu_run_tc(skel, skel->progs.tc_exceed_mtu_da, mtu);
	test_check_mtu_run_tc(skel, skel->progs.tc_minus_delta, mtu);
	test_check_mtu_run_tc(skel, skel->progs.tc_input_len, mtu);
	test_check_mtu_run_tc(skel, skel->progs.tc_input_len_exceed, mtu);
cleanup:
	test_check_mtu__destroy(skel);
पूर्ण

व्योम test_check_mtu(व्योम)
अणु
	__u32 mtu_lo;

	अगर (test__start_subtest("bpf_check_mtu XDP-attach"))
		test_check_mtu_xdp_attach();

	mtu_lo = पढ़ो_mtu_device_lo();
	अगर (CHECK(mtu_lo < 0, "reading MTU value", "failed (err:%d)", mtu_lo))
		वापस;

	अगर (test__start_subtest("bpf_check_mtu XDP-run"))
		test_check_mtu_xdp(mtu_lo, 0);

	अगर (test__start_subtest("bpf_check_mtu XDP-run ifindex-lookup"))
		test_check_mtu_xdp(mtu_lo, IFINDEX_LO);

	अगर (test__start_subtest("bpf_check_mtu TC-run"))
		test_check_mtu_tc(mtu_lo, 0);

	अगर (test__start_subtest("bpf_check_mtu TC-run ifindex-lookup"))
		test_check_mtu_tc(mtu_lo, IFINDEX_LO);
पूर्ण
