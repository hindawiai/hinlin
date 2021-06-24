<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <test_progs.h>
#समावेश <network_helpers.h>

काष्ठा meta अणु
	पूर्णांक अगरindex;
	__u32 cb32_0;
	__u8 cb8_0;
पूर्ण;

अटल जोड़ अणु
	__u32 cb32[5];
	__u8 cb8[20];
पूर्ण cb = अणु
	.cb32[0] = 0x81828384,
पूर्ण;

अटल व्योम on_sample(व्योम *ctx, पूर्णांक cpu, व्योम *data, __u32 size)
अणु
	काष्ठा meta *meta = (काष्ठा meta *)data;
	काष्ठा ipv6_packet *pkt_v6 = data + माप(*meta);
	पूर्णांक duration = 0;

	अगर (CHECK(size != 72 + माप(*meta), "check_size", "size %u != %zu\n",
		  size, 72 + माप(*meta)))
		वापस;
	अगर (CHECK(meta->अगरindex != 1, "check_meta_ifindex",
		  "meta->ifindex = %d\n", meta->अगरindex))
		/* spurious kमुक्त_skb not on loopback device */
		वापस;
	अगर (CHECK(meta->cb8_0 != cb.cb8[0], "check_cb8_0", "cb8_0 %x != %x\n",
		  meta->cb8_0, cb.cb8[0]))
		वापस;
	अगर (CHECK(meta->cb32_0 != cb.cb32[0], "check_cb32_0",
		  "cb32_0 %x != %x\n",
		  meta->cb32_0, cb.cb32[0]))
		वापस;
	अगर (CHECK(pkt_v6->eth.h_proto != 0xdd86, "check_eth",
		  "h_proto %x\n", pkt_v6->eth.h_proto))
		वापस;
	अगर (CHECK(pkt_v6->iph.nexthdr != 6, "check_ip",
		  "iph.nexthdr %x\n", pkt_v6->iph.nexthdr))
		वापस;
	अगर (CHECK(pkt_v6->tcp.करोff != 5, "check_tcp",
		  "tcp.doff %x\n", pkt_v6->tcp.करोff))
		वापस;

	*(bool *)ctx = true;
पूर्ण

व्योम test_kमुक्त_skb(व्योम)
अणु
	काष्ठा __sk_buff skb = अणुपूर्ण;
	काष्ठा bpf_prog_test_run_attr tattr = अणु
		.data_in = &pkt_v6,
		.data_size_in = माप(pkt_v6),
		.ctx_in = &skb,
		.ctx_size_in = माप(skb),
	पूर्ण;
	काष्ठा bpf_prog_load_attr attr = अणु
		.file = "./kfree_skb.o",
	पूर्ण;

	काष्ठा bpf_link *link = शून्य, *link_fentry = शून्य, *link_fनिकास = शून्य;
	काष्ठा bpf_map *perf_buf_map, *global_data;
	काष्ठा bpf_program *prog, *fentry, *fनिकास;
	काष्ठा bpf_object *obj, *obj2 = शून्य;
	काष्ठा perf_buffer_opts pb_opts = अणुपूर्ण;
	काष्ठा perf_buffer *pb = शून्य;
	पूर्णांक err, kमुक्त_skb_fd;
	bool passed = false;
	__u32 duration = 0;
	स्थिर पूर्णांक zero = 0;
	bool test_ok[2];

	err = bpf_prog_load("./test_pkt_access.o", BPF_PROG_TYPE_SCHED_CLS,
			    &obj, &tattr.prog_fd);
	अगर (CHECK(err, "prog_load sched cls", "err %d errno %d\n", err, त्रुटि_सं))
		वापस;

	err = bpf_prog_load_xattr(&attr, &obj2, &kमुक्त_skb_fd);
	अगर (CHECK(err, "prog_load raw tp", "err %d errno %d\n", err, त्रुटि_सं))
		जाओ बंद_prog;

	prog = bpf_object__find_program_by_title(obj2, "tp_btf/kfree_skb");
	अगर (CHECK(!prog, "find_prog", "prog kfree_skb not found\n"))
		जाओ बंद_prog;
	fentry = bpf_object__find_program_by_title(obj2, "fentry/eth_type_trans");
	अगर (CHECK(!fentry, "find_prog", "prog eth_type_trans not found\n"))
		जाओ बंद_prog;
	fनिकास = bpf_object__find_program_by_title(obj2, "fexit/eth_type_trans");
	अगर (CHECK(!fनिकास, "find_prog", "prog eth_type_trans not found\n"))
		जाओ बंद_prog;

	global_data = bpf_object__find_map_by_name(obj2, "kfree_sk.bss");
	अगर (CHECK(!global_data, "find global data", "not found\n"))
		जाओ बंद_prog;

	link = bpf_program__attach_raw_tracepoपूर्णांक(prog, शून्य);
	अगर (CHECK(IS_ERR(link), "attach_raw_tp", "err %ld\n", PTR_ERR(link)))
		जाओ बंद_prog;
	link_fentry = bpf_program__attach_trace(fentry);
	अगर (CHECK(IS_ERR(link_fentry), "attach fentry", "err %ld\n",
		  PTR_ERR(link_fentry)))
		जाओ बंद_prog;
	link_fनिकास = bpf_program__attach_trace(fनिकास);
	अगर (CHECK(IS_ERR(link_fनिकास), "attach fexit", "err %ld\n",
		  PTR_ERR(link_fनिकास)))
		जाओ बंद_prog;

	perf_buf_map = bpf_object__find_map_by_name(obj2, "perf_buf_map");
	अगर (CHECK(!perf_buf_map, "find_perf_buf_map", "not found\n"))
		जाओ बंद_prog;

	/* set up perf buffer */
	pb_opts.sample_cb = on_sample;
	pb_opts.ctx = &passed;
	pb = perf_buffer__new(bpf_map__fd(perf_buf_map), 1, &pb_opts);
	अगर (CHECK(IS_ERR(pb), "perf_buf__new", "err %ld\n", PTR_ERR(pb)))
		जाओ बंद_prog;

	स_नकल(skb.cb, &cb, माप(cb));
	err = bpf_prog_test_run_xattr(&tattr);
	duration = tattr.duration;
	CHECK(err || tattr.retval, "ipv6",
	      "err %d errno %d retval %d duration %d\n",
	      err, त्रुटि_सं, tattr.retval, duration);

	/* पढ़ो perf buffer */
	err = perf_buffer__poll(pb, 100);
	अगर (CHECK(err < 0, "perf_buffer__poll", "err %d\n", err))
		जाओ बंद_prog;

	/* make sure kमुक्त_skb program was triggered
	 * and it sent expected skb पूर्णांकo ring buffer
	 */
	ASSERT_TRUE(passed, "passed");

	err = bpf_map_lookup_elem(bpf_map__fd(global_data), &zero, test_ok);
	अगर (CHECK(err, "get_result",
		  "failed to get output data: %d\n", err))
		जाओ बंद_prog;

	CHECK_FAIL(!test_ok[0] || !test_ok[1]);
बंद_prog:
	perf_buffer__मुक्त(pb);
	अगर (!IS_ERR_OR_शून्य(link))
		bpf_link__destroy(link);
	अगर (!IS_ERR_OR_शून्य(link_fentry))
		bpf_link__destroy(link_fentry);
	अगर (!IS_ERR_OR_शून्य(link_fनिकास))
		bpf_link__destroy(link_fनिकास);
	bpf_object__बंद(obj);
	bpf_object__बंद(obj2);
पूर्ण
