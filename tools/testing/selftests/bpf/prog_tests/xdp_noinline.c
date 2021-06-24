<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <test_progs.h>
#समावेश <network_helpers.h>
#समावेश "test_xdp_noinline.skel.h"

व्योम test_xdp_noअंतरभूत(व्योम)
अणु
	अचिन्हित पूर्णांक nr_cpus = bpf_num_possible_cpus();
	काष्ठा test_xdp_noअंतरभूत *skel;
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
	__u32 duration = 0, retval, size;
	पूर्णांक err, i;
	__u64 bytes = 0, pkts = 0;
	अक्षर buf[128];
	u32 *magic = (u32 *)buf;

	skel = test_xdp_noअंतरभूत__खोलो_and_load();
	अगर (CHECK(!skel, "skel_open_and_load", "failed\n"))
		वापस;

	bpf_map_update_elem(bpf_map__fd(skel->maps.vip_map), &key, &value, 0);
	bpf_map_update_elem(bpf_map__fd(skel->maps.ch_rings), &ch_key, &real_num, 0);
	bpf_map_update_elem(bpf_map__fd(skel->maps.reals), &real_num, &real_def, 0);

	err = bpf_prog_test_run(bpf_program__fd(skel->progs.balancer_ingress_v4),
				NUM_ITER, &pkt_v4, माप(pkt_v4),
				buf, &size, &retval, &duration);
	CHECK(err || retval != 1 || size != 54 ||
	      *magic != MAGIC_VAL, "ipv4",
	      "err %d errno %d retval %d size %d magic %x\n",
	      err, त्रुटि_सं, retval, size, *magic);

	err = bpf_prog_test_run(bpf_program__fd(skel->progs.balancer_ingress_v6),
				NUM_ITER, &pkt_v6, माप(pkt_v6),
				buf, &size, &retval, &duration);
	CHECK(err || retval != 1 || size != 74 ||
	      *magic != MAGIC_VAL, "ipv6",
	      "err %d errno %d retval %d size %d magic %x\n",
	      err, त्रुटि_सं, retval, size, *magic);

	bpf_map_lookup_elem(bpf_map__fd(skel->maps.stats), &stats_key, stats);
	क्रम (i = 0; i < nr_cpus; i++) अणु
		bytes += stats[i].bytes;
		pkts += stats[i].pkts;
	पूर्ण
	CHECK(bytes != MAGIC_BYTES * NUM_ITER * 2 || pkts != NUM_ITER * 2,
	      "stats", "bytes %lld pkts %lld\n",
	      (अचिन्हित दीर्घ दीर्घ)bytes, (अचिन्हित दीर्घ दीर्घ)pkts);
	test_xdp_noअंतरभूत__destroy(skel);
पूर्ण
