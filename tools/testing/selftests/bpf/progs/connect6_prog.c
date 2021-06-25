<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2018 Facebook

#समावेश <माला.स>

#समावेश <linux/मानकघोष.स>
#समावेश <linux/bpf.h>
#समावेश <linux/in.h>
#समावेश <linux/in6.h>
#समावेश <sys/socket.h>

#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_endian.h>

#घोषणा SRC_REWRITE_IP6_0	0
#घोषणा SRC_REWRITE_IP6_1	0
#घोषणा SRC_REWRITE_IP6_2	0
#घोषणा SRC_REWRITE_IP6_3	6

#घोषणा DST_REWRITE_IP6_0	0
#घोषणा DST_REWRITE_IP6_1	0
#घोषणा DST_REWRITE_IP6_2	0
#घोषणा DST_REWRITE_IP6_3	1

#घोषणा DST_REWRITE_PORT6	6666

पूर्णांक _version SEC("version") = 1;

SEC("cgroup/connect6")
पूर्णांक connect_v6_prog(काष्ठा bpf_sock_addr *ctx)
अणु
	काष्ठा bpf_sock_tuple tuple = अणुपूर्ण;
	काष्ठा sockaddr_in6 sa;
	काष्ठा bpf_sock *sk;

	/* Verअगरy that new destination is available. */
	स_रखो(&tuple.ipv6.saddr, 0, माप(tuple.ipv6.saddr));
	स_रखो(&tuple.ipv6.sport, 0, माप(tuple.ipv6.sport));

	tuple.ipv6.daddr[0] = bpf_htonl(DST_REWRITE_IP6_0);
	tuple.ipv6.daddr[1] = bpf_htonl(DST_REWRITE_IP6_1);
	tuple.ipv6.daddr[2] = bpf_htonl(DST_REWRITE_IP6_2);
	tuple.ipv6.daddr[3] = bpf_htonl(DST_REWRITE_IP6_3);

	tuple.ipv6.dport = bpf_htons(DST_REWRITE_PORT6);

	अगर (ctx->type != SOCK_STREAM && ctx->type != SOCK_DGRAM)
		वापस 0;
	अन्यथा अगर (ctx->type == SOCK_STREAM)
		sk = bpf_sk_lookup_tcp(ctx, &tuple, माप(tuple.ipv6),
				       BPF_F_CURRENT_NETNS, 0);
	अन्यथा
		sk = bpf_sk_lookup_udp(ctx, &tuple, माप(tuple.ipv6),
				       BPF_F_CURRENT_NETNS, 0);

	अगर (!sk)
		वापस 0;

	अगर (sk->src_ip6[0] != tuple.ipv6.daddr[0] ||
	    sk->src_ip6[1] != tuple.ipv6.daddr[1] ||
	    sk->src_ip6[2] != tuple.ipv6.daddr[2] ||
	    sk->src_ip6[3] != tuple.ipv6.daddr[3] ||
	    sk->src_port != DST_REWRITE_PORT6) अणु
		bpf_sk_release(sk);
		वापस 0;
	पूर्ण

	bpf_sk_release(sk);

	/* Reग_लिखो destination. */
	ctx->user_ip6[0] = bpf_htonl(DST_REWRITE_IP6_0);
	ctx->user_ip6[1] = bpf_htonl(DST_REWRITE_IP6_1);
	ctx->user_ip6[2] = bpf_htonl(DST_REWRITE_IP6_2);
	ctx->user_ip6[3] = bpf_htonl(DST_REWRITE_IP6_3);

	ctx->user_port = bpf_htons(DST_REWRITE_PORT6);

	/* Reग_लिखो source. */
	स_रखो(&sa, 0, माप(sa));

	sa.sin6_family = AF_INET6;
	sa.sin6_port = bpf_htons(0);

	sa.sin6_addr.s6_addr32[0] = bpf_htonl(SRC_REWRITE_IP6_0);
	sa.sin6_addr.s6_addr32[1] = bpf_htonl(SRC_REWRITE_IP6_1);
	sa.sin6_addr.s6_addr32[2] = bpf_htonl(SRC_REWRITE_IP6_2);
	sa.sin6_addr.s6_addr32[3] = bpf_htonl(SRC_REWRITE_IP6_3);

	अगर (bpf_bind(ctx, (काष्ठा sockaddr *)&sa, माप(sa)) != 0)
		वापस 0;

	वापस 1;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
