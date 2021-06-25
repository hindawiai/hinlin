<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <test_progs.h>
#समावेश <network_helpers.h>
#समावेश <net/अगर.h>
#समावेश "test_xdp.skel.h"
#समावेश "test_xdp_bpf2bpf.skel.h"

काष्ठा meta अणु
	पूर्णांक अगरindex;
	पूर्णांक pkt_len;
पूर्ण;

अटल व्योम on_sample(व्योम *ctx, पूर्णांक cpu, व्योम *data, __u32 size)
अणु
	पूर्णांक duration = 0;
	काष्ठा meta *meta = (काष्ठा meta *)data;
	काष्ठा ipv4_packet *trace_pkt_v4 = data + माप(*meta);

	अगर (CHECK(size < माप(pkt_v4) + माप(*meta),
		  "check_size", "size %u < %zu\n",
		  size, माप(pkt_v4) + माप(*meta)))
		वापस;

	अगर (CHECK(meta->अगरindex != अगर_nametoindex("lo"), "check_meta_ifindex",
		  "meta->ifindex = %d\n", meta->अगरindex))
		वापस;

	अगर (CHECK(meta->pkt_len != माप(pkt_v4), "check_meta_pkt_len",
		  "meta->pkt_len = %zd\n", माप(pkt_v4)))
		वापस;

	अगर (CHECK(स_भेद(trace_pkt_v4, &pkt_v4, माप(pkt_v4)),
		  "check_packet_content", "content not the same\n"))
		वापस;

	*(bool *)ctx = true;
पूर्ण

व्योम test_xdp_bpf2bpf(व्योम)
अणु
	__u32 duration = 0, retval, size;
	अक्षर buf[128];
	पूर्णांक err, pkt_fd, map_fd;
	bool passed = false;
	काष्ठा iphdr *iph = (व्योम *)buf + माप(काष्ठा ethhdr);
	काष्ठा iptnl_info value4 = अणु.family = AF_INETपूर्ण;
	काष्ठा test_xdp *pkt_skel = शून्य;
	काष्ठा test_xdp_bpf2bpf *ftrace_skel = शून्य;
	काष्ठा vip key4 = अणु.protocol = 6, .family = AF_INETपूर्ण;
	काष्ठा bpf_program *prog;
	काष्ठा perf_buffer *pb = शून्य;
	काष्ठा perf_buffer_opts pb_opts = अणुपूर्ण;

	/* Load XDP program to पूर्णांकrospect */
	pkt_skel = test_xdp__खोलो_and_load();
	अगर (CHECK(!pkt_skel, "pkt_skel_load", "test_xdp skeleton failed\n"))
		वापस;

	pkt_fd = bpf_program__fd(pkt_skel->progs._xdp_tx_iptunnel);

	map_fd = bpf_map__fd(pkt_skel->maps.vip2tnl);
	bpf_map_update_elem(map_fd, &key4, &value4, 0);

	/* Load trace program */
	ftrace_skel = test_xdp_bpf2bpf__खोलो();
	अगर (CHECK(!ftrace_skel, "__open", "ftrace skeleton failed\n"))
		जाओ out;

	/* Demonstrate the bpf_program__set_attach_target() API rather than
	 * the load with options, i.e. opts.attach_prog_fd.
	 */
	prog = ftrace_skel->progs.trace_on_entry;
	bpf_program__set_expected_attach_type(prog, BPF_TRACE_FENTRY);
	bpf_program__set_attach_target(prog, pkt_fd, "_xdp_tx_iptunnel");

	prog = ftrace_skel->progs.trace_on_निकास;
	bpf_program__set_expected_attach_type(prog, BPF_TRACE_FEXIT);
	bpf_program__set_attach_target(prog, pkt_fd, "_xdp_tx_iptunnel");

	err = test_xdp_bpf2bpf__load(ftrace_skel);
	अगर (CHECK(err, "__load", "ftrace skeleton failed\n"))
		जाओ out;

	err = test_xdp_bpf2bpf__attach(ftrace_skel);
	अगर (CHECK(err, "ftrace_attach", "ftrace attach failed: %d\n", err))
		जाओ out;

	/* Set up perf buffer */
	pb_opts.sample_cb = on_sample;
	pb_opts.ctx = &passed;
	pb = perf_buffer__new(bpf_map__fd(ftrace_skel->maps.perf_buf_map),
			      1, &pb_opts);
	अगर (CHECK(IS_ERR(pb), "perf_buf__new", "err %ld\n", PTR_ERR(pb)))
		जाओ out;

	/* Run test program */
	err = bpf_prog_test_run(pkt_fd, 1, &pkt_v4, माप(pkt_v4),
				buf, &size, &retval, &duration);

	अगर (CHECK(err || retval != XDP_TX || size != 74 ||
		  iph->protocol != IPPROTO_IPIP, "ipv4",
		  "err %d errno %d retval %d size %d\n",
		  err, त्रुटि_सं, retval, size))
		जाओ out;

	/* Make sure bpf_xdp_output() was triggered and it sent the expected
	 * data to the perf ring buffer.
	 */
	err = perf_buffer__poll(pb, 100);
	अगर (CHECK(err < 0, "perf_buffer__poll", "err %d\n", err))
		जाओ out;

	CHECK_FAIL(!passed);

	/* Verअगरy test results */
	अगर (CHECK(ftrace_skel->bss->test_result_fentry != अगर_nametoindex("lo"),
		  "result", "fentry failed err %llu\n",
		  ftrace_skel->bss->test_result_fentry))
		जाओ out;

	CHECK(ftrace_skel->bss->test_result_fनिकास != XDP_TX, "result",
	      "fexit failed err %llu\n", ftrace_skel->bss->test_result_fनिकास);

out:
	अगर (pb)
		perf_buffer__मुक्त(pb);
	test_xdp__destroy(pkt_skel);
	test_xdp_bpf2bpf__destroy(ftrace_skel);
पूर्ण
