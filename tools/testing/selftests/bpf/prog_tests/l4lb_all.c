<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <test_progs.h>
#समावेश <network_helpers.h>

अटल व्योम test_l4lb(स्थिर अक्षर *file)
अणु
	अचिन्हित पूर्णांक nr_cpus = bpf_num_possible_cpus();
	काष्ठा vip key = अणु.protocol = 6पूर्ण;
	काष्ठा vip_meta अणु
		__u32 flags;
		__u32 vip_num;
	पूर्ण value = अणु.vip_num = VIP_NUMपूर्ण;
	__u32 stats_key = VIP_NUM;
	काष्ठा vip_stats अणु
		__u64 bytes;
		__u64 pkts;
	पूर्ण stats[nr_cpus];
	काष्ठा real_definition अणु
		जोड़ अणु
			__be32 dst;
			__be32 dstv6[4];
		पूर्ण;
		__u8 flags;
	पूर्ण real_def = अणु.dst = MAGIC_VALपूर्ण;
	__u32 ch_key = 11, real_num = 3;
	__u32 duration, retval, size;
	पूर्णांक err, i, prog_fd, map_fd;
	__u64 bytes = 0, pkts = 0;
	काष्ठा bpf_object *obj;
	अक्षर buf[128];
	u32 *magic = (u32 *)buf;

	err = bpf_prog_load(file, BPF_PROG_TYPE_SCHED_CLS, &obj, &prog_fd);
	अगर (CHECK_FAIL(err))
		वापस;

	map_fd = bpf_find_map(__func__, obj, "vip_map");
	अगर (map_fd < 0)
		जाओ out;
	bpf_map_update_elem(map_fd, &key, &value, 0);

	map_fd = bpf_find_map(__func__, obj, "ch_rings");
	अगर (map_fd < 0)
		जाओ out;
	bpf_map_update_elem(map_fd, &ch_key, &real_num, 0);

	map_fd = bpf_find_map(__func__, obj, "reals");
	अगर (map_fd < 0)
		जाओ out;
	bpf_map_update_elem(map_fd, &real_num, &real_def, 0);

	err = bpf_prog_test_run(prog_fd, NUM_ITER, &pkt_v4, माप(pkt_v4),
				buf, &size, &retval, &duration);
	CHECK(err || retval != 7/*TC_ACT_REसूचीECT*/ || size != 54 ||
	      *magic != MAGIC_VAL, "ipv4",
	      "err %d errno %d retval %d size %d magic %x\n",
	      err, त्रुटि_सं, retval, size, *magic);

	err = bpf_prog_test_run(prog_fd, NUM_ITER, &pkt_v6, माप(pkt_v6),
				buf, &size, &retval, &duration);
	CHECK(err || retval != 7/*TC_ACT_REसूचीECT*/ || size != 74 ||
	      *magic != MAGIC_VAL, "ipv6",
	      "err %d errno %d retval %d size %d magic %x\n",
	      err, त्रुटि_सं, retval, size, *magic);

	map_fd = bpf_find_map(__func__, obj, "stats");
	अगर (map_fd < 0)
		जाओ out;
	bpf_map_lookup_elem(map_fd, &stats_key, stats);
	क्रम (i = 0; i < nr_cpus; i++) अणु
		bytes += stats[i].bytes;
		pkts += stats[i].pkts;
	पूर्ण
	अगर (CHECK_FAIL(bytes != MAGIC_BYTES * NUM_ITER * 2 ||
		       pkts != NUM_ITER * 2))
		म_लिखो("test_l4lb:FAIL:stats %lld %lld\n", bytes, pkts);
out:
	bpf_object__बंद(obj);
पूर्ण

व्योम test_l4lb_all(व्योम)
अणु
	अगर (test__start_subtest("l4lb_inline"))
		test_l4lb("test_l4lb.o");
	अगर (test__start_subtest("l4lb_noinline"))
		test_l4lb("test_l4lb_noinline.o");
पूर्ण
