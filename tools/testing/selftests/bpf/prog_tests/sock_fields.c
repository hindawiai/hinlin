<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2019 Facebook */

#समावेश <netinet/in.h>
#समावेश <arpa/inet.h>
#समावेश <unistd.h>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <त्रुटिसं.स>

#समावेश <bpf/bpf.h>
#समावेश <bpf/libbpf.h>
#समावेश <linux/compiler.h>

#समावेश "network_helpers.h"
#समावेश "cgroup_helpers.h"
#समावेश "test_progs.h"
#समावेश "bpf_rlimit.h"
#समावेश "test_sock_fields.skel.h"

क्रमागत bpf_linum_array_idx अणु
	EGRESS_LINUM_IDX,
	INGRESS_LINUM_IDX,
	__NR_BPF_LINUM_ARRAY_IDX,
पूर्ण;

काष्ठा bpf_spinlock_cnt अणु
	काष्ठा bpf_spin_lock lock;
	__u32 cnt;
पूर्ण;

#घोषणा PARENT_CGROUP	"/test-bpf-sock-fields"
#घोषणा CHILD_CGROUP	"/test-bpf-sock-fields/child"
#घोषणा DATA "Hello BPF!"
#घोषणा DATA_LEN माप(DATA)

अटल काष्ठा sockaddr_in6 srv_sa6, cli_sa6;
अटल पूर्णांक sk_pkt_out_cnt10_fd;
अटल काष्ठा test_sock_fields *skel;
अटल पूर्णांक sk_pkt_out_cnt_fd;
अटल __u64 parent_cg_id;
अटल __u64 child_cg_id;
अटल पूर्णांक linum_map_fd;
अटल __u32 duration;

अटल __u32 egress_linum_idx = EGRESS_LINUM_IDX;
अटल __u32 ingress_linum_idx = INGRESS_LINUM_IDX;

अटल व्योम prपूर्णांक_sk(स्थिर काष्ठा bpf_sock *sk, स्थिर अक्षर *prefix)
अणु
	अक्षर src_ip4[24], dst_ip4[24];
	अक्षर src_ip6[64], dst_ip6[64];

	inet_ntop(AF_INET, &sk->src_ip4, src_ip4, माप(src_ip4));
	inet_ntop(AF_INET6, &sk->src_ip6, src_ip6, माप(src_ip6));
	inet_ntop(AF_INET, &sk->dst_ip4, dst_ip4, माप(dst_ip4));
	inet_ntop(AF_INET6, &sk->dst_ip6, dst_ip6, माप(dst_ip6));

	म_लिखो("%s: state:%u bound_dev_if:%u family:%u type:%u protocol:%u mark:%u priority:%u "
	       "src_ip4:%x(%s) src_ip6:%x:%x:%x:%x(%s) src_port:%u "
	       "dst_ip4:%x(%s) dst_ip6:%x:%x:%x:%x(%s) dst_port:%u\n",
	       prefix,
	       sk->state, sk->bound_dev_अगर, sk->family, sk->type, sk->protocol,
	       sk->mark, sk->priority,
	       sk->src_ip4, src_ip4,
	       sk->src_ip6[0], sk->src_ip6[1], sk->src_ip6[2], sk->src_ip6[3],
	       src_ip6, sk->src_port,
	       sk->dst_ip4, dst_ip4,
	       sk->dst_ip6[0], sk->dst_ip6[1], sk->dst_ip6[2], sk->dst_ip6[3],
	       dst_ip6, ntohs(sk->dst_port));
पूर्ण

अटल व्योम prपूर्णांक_tp(स्थिर काष्ठा bpf_tcp_sock *tp, स्थिर अक्षर *prefix)
अणु
	म_लिखो("%s: snd_cwnd:%u srtt_us:%u rtt_min:%u snd_ssthresh:%u rcv_nxt:%u "
	       "snd_nxt:%u snd:una:%u mss_cache:%u ecn_flags:%u "
	       "rate_delivered:%u rate_interval_us:%u packets_out:%u "
	       "retrans_out:%u total_retrans:%u segs_in:%u data_segs_in:%u "
	       "segs_out:%u data_segs_out:%u lost_out:%u sacked_out:%u "
	       "bytes_received:%llu bytes_acked:%llu\n",
	       prefix,
	       tp->snd_cwnd, tp->srtt_us, tp->rtt_min, tp->snd_ssthresh,
	       tp->rcv_nxt, tp->snd_nxt, tp->snd_una, tp->mss_cache,
	       tp->ecn_flags, tp->rate_delivered, tp->rate_पूर्णांकerval_us,
	       tp->packets_out, tp->retrans_out, tp->total_retrans,
	       tp->segs_in, tp->data_segs_in, tp->segs_out,
	       tp->data_segs_out, tp->lost_out, tp->sacked_out,
	       tp->bytes_received, tp->bytes_acked);
पूर्ण

अटल व्योम check_result(व्योम)
अणु
	काष्ठा bpf_tcp_sock srv_tp, cli_tp, listen_tp;
	काष्ठा bpf_sock srv_sk, cli_sk, listen_sk;
	__u32 ingress_linum, egress_linum;
	पूर्णांक err;

	err = bpf_map_lookup_elem(linum_map_fd, &egress_linum_idx,
				  &egress_linum);
	CHECK(err == -1, "bpf_map_lookup_elem(linum_map_fd)",
	      "err:%d errno:%d\n", err, त्रुटि_सं);

	err = bpf_map_lookup_elem(linum_map_fd, &ingress_linum_idx,
				  &ingress_linum);
	CHECK(err == -1, "bpf_map_lookup_elem(linum_map_fd)",
	      "err:%d errno:%d\n", err, त्रुटि_सं);

	स_नकल(&srv_sk, &skel->bss->srv_sk, माप(srv_sk));
	स_नकल(&srv_tp, &skel->bss->srv_tp, माप(srv_tp));
	स_नकल(&cli_sk, &skel->bss->cli_sk, माप(cli_sk));
	स_नकल(&cli_tp, &skel->bss->cli_tp, माप(cli_tp));
	स_नकल(&listen_sk, &skel->bss->listen_sk, माप(listen_sk));
	स_नकल(&listen_tp, &skel->bss->listen_tp, माप(listen_tp));

	prपूर्णांक_sk(&listen_sk, "listen_sk");
	prपूर्णांक_sk(&srv_sk, "srv_sk");
	prपूर्णांक_sk(&cli_sk, "cli_sk");
	prपूर्णांक_tp(&listen_tp, "listen_tp");
	prपूर्णांक_tp(&srv_tp, "srv_tp");
	prपूर्णांक_tp(&cli_tp, "cli_tp");

	CHECK(listen_sk.state != 10 ||
	      listen_sk.family != AF_INET6 ||
	      listen_sk.protocol != IPPROTO_TCP ||
	      स_भेद(listen_sk.src_ip6, &in6addr_loopback,
		     माप(listen_sk.src_ip6)) ||
	      listen_sk.dst_ip6[0] || listen_sk.dst_ip6[1] ||
	      listen_sk.dst_ip6[2] || listen_sk.dst_ip6[3] ||
	      listen_sk.src_port != ntohs(srv_sa6.sin6_port) ||
	      listen_sk.dst_port,
	      "listen_sk",
	      "Unexpected. Check listen_sk output. ingress_linum:%u\n",
	      ingress_linum);

	CHECK(srv_sk.state == 10 ||
	      !srv_sk.state ||
	      srv_sk.family != AF_INET6 ||
	      srv_sk.protocol != IPPROTO_TCP ||
	      स_भेद(srv_sk.src_ip6, &in6addr_loopback,
		     माप(srv_sk.src_ip6)) ||
	      स_भेद(srv_sk.dst_ip6, &in6addr_loopback,
		     माप(srv_sk.dst_ip6)) ||
	      srv_sk.src_port != ntohs(srv_sa6.sin6_port) ||
	      srv_sk.dst_port != cli_sa6.sin6_port,
	      "srv_sk", "Unexpected. Check srv_sk output. egress_linum:%u\n",
	      egress_linum);

	CHECK(!skel->bss->lsndसमय, "srv_tp", "Unexpected lsndtime:0\n");

	CHECK(cli_sk.state == 10 ||
	      !cli_sk.state ||
	      cli_sk.family != AF_INET6 ||
	      cli_sk.protocol != IPPROTO_TCP ||
	      स_भेद(cli_sk.src_ip6, &in6addr_loopback,
		     माप(cli_sk.src_ip6)) ||
	      स_भेद(cli_sk.dst_ip6, &in6addr_loopback,
		     माप(cli_sk.dst_ip6)) ||
	      cli_sk.src_port != ntohs(cli_sa6.sin6_port) ||
	      cli_sk.dst_port != srv_sa6.sin6_port,
	      "cli_sk", "Unexpected. Check cli_sk output. egress_linum:%u\n",
	      egress_linum);

	CHECK(listen_tp.data_segs_out ||
	      listen_tp.data_segs_in ||
	      listen_tp.total_retrans ||
	      listen_tp.bytes_acked,
	      "listen_tp",
	      "Unexpected. Check listen_tp output. ingress_linum:%u\n",
	      ingress_linum);

	CHECK(srv_tp.data_segs_out != 2 ||
	      srv_tp.data_segs_in ||
	      srv_tp.snd_cwnd != 10 ||
	      srv_tp.total_retrans ||
	      srv_tp.bytes_acked < 2 * DATA_LEN,
	      "srv_tp", "Unexpected. Check srv_tp output. egress_linum:%u\n",
	      egress_linum);

	CHECK(cli_tp.data_segs_out ||
	      cli_tp.data_segs_in != 2 ||
	      cli_tp.snd_cwnd != 10 ||
	      cli_tp.total_retrans ||
	      cli_tp.bytes_received < 2 * DATA_LEN,
	      "cli_tp", "Unexpected. Check cli_tp output. egress_linum:%u\n",
	      egress_linum);

	CHECK(skel->bss->parent_cg_id != parent_cg_id,
	      "parent_cg_id", "%zu != %zu\n",
	      (माप_प्रकार)skel->bss->parent_cg_id, (माप_प्रकार)parent_cg_id);

	CHECK(skel->bss->child_cg_id != child_cg_id,
	      "child_cg_id", "%zu != %zu\n",
	       (माप_प्रकार)skel->bss->child_cg_id, (माप_प्रकार)child_cg_id);
पूर्ण

अटल व्योम check_sk_pkt_out_cnt(पूर्णांक accept_fd, पूर्णांक cli_fd)
अणु
	काष्ठा bpf_spinlock_cnt pkt_out_cnt = अणुपूर्ण, pkt_out_cnt10 = अणुपूर्ण;
	पूर्णांक err;

	pkt_out_cnt.cnt = ~0;
	pkt_out_cnt10.cnt = ~0;
	err = bpf_map_lookup_elem(sk_pkt_out_cnt_fd, &accept_fd, &pkt_out_cnt);
	अगर (!err)
		err = bpf_map_lookup_elem(sk_pkt_out_cnt10_fd, &accept_fd,
					  &pkt_out_cnt10);

	/* The bpf prog only counts क्रम fullsock and
	 * passive connection did not become fullsock until 3WHS
	 * had been finished, so the bpf prog only counted two data
	 * packet out.
	 */
	CHECK(err || pkt_out_cnt.cnt < 0xeB9F + 2 ||
	      pkt_out_cnt10.cnt < 0xeB9F + 20,
	      "bpf_map_lookup_elem(sk_pkt_out_cnt, &accept_fd)",
	      "err:%d errno:%d pkt_out_cnt:%u pkt_out_cnt10:%u\n",
	      err, त्रुटि_सं, pkt_out_cnt.cnt, pkt_out_cnt10.cnt);

	pkt_out_cnt.cnt = ~0;
	pkt_out_cnt10.cnt = ~0;
	err = bpf_map_lookup_elem(sk_pkt_out_cnt_fd, &cli_fd, &pkt_out_cnt);
	अगर (!err)
		err = bpf_map_lookup_elem(sk_pkt_out_cnt10_fd, &cli_fd,
					  &pkt_out_cnt10);
	/* Active connection is fullsock from the beginning.
	 * 1 SYN and 1 ACK during 3WHS
	 * 2 Acks on data packet.
	 *
	 * The bpf_prog initialized it to 0xeB9F.
	 */
	CHECK(err || pkt_out_cnt.cnt < 0xeB9F + 4 ||
	      pkt_out_cnt10.cnt < 0xeB9F + 40,
	      "bpf_map_lookup_elem(sk_pkt_out_cnt, &cli_fd)",
	      "err:%d errno:%d pkt_out_cnt:%u pkt_out_cnt10:%u\n",
	      err, त्रुटि_सं, pkt_out_cnt.cnt, pkt_out_cnt10.cnt);
पूर्ण

अटल पूर्णांक init_sk_storage(पूर्णांक sk_fd, __u32 pkt_out_cnt)
अणु
	काष्ठा bpf_spinlock_cnt scnt = अणुपूर्ण;
	पूर्णांक err;

	scnt.cnt = pkt_out_cnt;
	err = bpf_map_update_elem(sk_pkt_out_cnt_fd, &sk_fd, &scnt,
				  BPF_NOEXIST);
	अगर (CHECK(err, "bpf_map_update_elem(sk_pkt_out_cnt_fd)",
		  "err:%d errno:%d\n", err, त्रुटि_सं))
		वापस err;

	err = bpf_map_update_elem(sk_pkt_out_cnt10_fd, &sk_fd, &scnt,
				  BPF_NOEXIST);
	अगर (CHECK(err, "bpf_map_update_elem(sk_pkt_out_cnt10_fd)",
		  "err:%d errno:%d\n", err, त्रुटि_सं))
		वापस err;

	वापस 0;
पूर्ण

अटल व्योम test(व्योम)
अणु
	पूर्णांक listen_fd = -1, cli_fd = -1, accept_fd = -1, err, i;
	socklen_t addrlen = माप(काष्ठा sockaddr_in6);
	अक्षर buf[DATA_LEN];

	/* Prepare listen_fd */
	listen_fd = start_server(AF_INET6, SOCK_STREAM, "::1", 0, 0);
	/* start_server() has logged the error details */
	अगर (CHECK_FAIL(listen_fd == -1))
		जाओ करोne;

	err = माला_लोockname(listen_fd, (काष्ठा sockaddr *)&srv_sa6, &addrlen);
	अगर (CHECK(err, "getsockname(listen_fd)", "err:%d errno:%d\n", err,
		  त्रुटि_सं))
		जाओ करोne;
	स_नकल(&skel->bss->srv_sa6, &srv_sa6, माप(srv_sa6));

	cli_fd = connect_to_fd(listen_fd, 0);
	अगर (CHECK_FAIL(cli_fd == -1))
		जाओ करोne;

	err = माला_लोockname(cli_fd, (काष्ठा sockaddr *)&cli_sa6, &addrlen);
	अगर (CHECK(err, "getsockname(cli_fd)", "err:%d errno:%d\n",
		  err, त्रुटि_सं))
		जाओ करोne;

	accept_fd = accept(listen_fd, शून्य, शून्य);
	अगर (CHECK(accept_fd == -1, "accept(listen_fd)",
		  "accept_fd:%d errno:%d\n",
		  accept_fd, त्रुटि_सं))
		जाओ करोne;

	अगर (init_sk_storage(accept_fd, 0xeB9F))
		जाओ करोne;

	क्रम (i = 0; i < 2; i++) अणु
		/* Send some data from accept_fd to cli_fd.
		 * MSG_EOR to stop kernel from coalescing two pkts.
		 */
		err = send(accept_fd, DATA, DATA_LEN, MSG_EOR);
		अगर (CHECK(err != DATA_LEN, "send(accept_fd)",
			  "err:%d errno:%d\n", err, त्रुटि_सं))
			जाओ करोne;

		err = recv(cli_fd, buf, DATA_LEN, 0);
		अगर (CHECK(err != DATA_LEN, "recv(cli_fd)", "err:%d errno:%d\n",
			  err, त्रुटि_सं))
			जाओ करोne;
	पूर्ण

	shutकरोwn(cli_fd, SHUT_WR);
	err = recv(accept_fd, buf, 1, 0);
	अगर (CHECK(err, "recv(accept_fd) for fin", "err:%d errno:%d\n",
		  err, त्रुटि_सं))
		जाओ करोne;
	shutकरोwn(accept_fd, SHUT_WR);
	err = recv(cli_fd, buf, 1, 0);
	अगर (CHECK(err, "recv(cli_fd) for fin", "err:%d errno:%d\n",
		  err, त्रुटि_सं))
		जाओ करोne;
	check_sk_pkt_out_cnt(accept_fd, cli_fd);
	check_result();

करोne:
	अगर (accept_fd != -1)
		बंद(accept_fd);
	अगर (cli_fd != -1)
		बंद(cli_fd);
	अगर (listen_fd != -1)
		बंद(listen_fd);
पूर्ण

व्योम test_sock_fields(व्योम)
अणु
	काष्ठा bpf_link *egress_link = शून्य, *ingress_link = शून्य;
	पूर्णांक parent_cg_fd = -1, child_cg_fd = -1;

	/* Create a cgroup, get fd, and join it */
	parent_cg_fd = test__join_cgroup(PARENT_CGROUP);
	अगर (CHECK_FAIL(parent_cg_fd < 0))
		वापस;
	parent_cg_id = get_cgroup_id(PARENT_CGROUP);
	अगर (CHECK_FAIL(!parent_cg_id))
		जाओ करोne;

	child_cg_fd = test__join_cgroup(CHILD_CGROUP);
	अगर (CHECK_FAIL(child_cg_fd < 0))
		जाओ करोne;
	child_cg_id = get_cgroup_id(CHILD_CGROUP);
	अगर (CHECK_FAIL(!child_cg_id))
		जाओ करोne;

	skel = test_sock_fields__खोलो_and_load();
	अगर (CHECK(!skel, "test_sock_fields__open_and_load", "failed\n"))
		जाओ करोne;

	egress_link = bpf_program__attach_cgroup(skel->progs.egress_पढ़ो_sock_fields,
						 child_cg_fd);
	अगर (CHECK(IS_ERR(egress_link), "attach_cgroup(egress)", "err:%ld\n",
		  PTR_ERR(egress_link)))
		जाओ करोne;

	ingress_link = bpf_program__attach_cgroup(skel->progs.ingress_पढ़ो_sock_fields,
						  child_cg_fd);
	अगर (CHECK(IS_ERR(ingress_link), "attach_cgroup(ingress)", "err:%ld\n",
		  PTR_ERR(ingress_link)))
		जाओ करोne;

	linum_map_fd = bpf_map__fd(skel->maps.linum_map);
	sk_pkt_out_cnt_fd = bpf_map__fd(skel->maps.sk_pkt_out_cnt);
	sk_pkt_out_cnt10_fd = bpf_map__fd(skel->maps.sk_pkt_out_cnt10);

	test();

करोne:
	bpf_link__destroy(egress_link);
	bpf_link__destroy(ingress_link);
	test_sock_fields__destroy(skel);
	अगर (child_cg_fd != -1)
		बंद(child_cg_fd);
	अगर (parent_cg_fd != -1)
		बंद(parent_cg_fd);
पूर्ण
