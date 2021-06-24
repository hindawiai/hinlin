<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/मानकघोष.स>
#समावेश <linux/bpf.h>
#समावेश <linux/in6.h>
#समावेश <sys/socket.h>

#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_endian.h>

#समावेश <bpf_sockopt_helpers.h>

#घोषणा SERV6_IP_0		0xfaceb00c /* face:b00c:1234:5678::abcd */
#घोषणा SERV6_IP_1		0x12345678
#घोषणा SERV6_IP_2		0x00000000
#घोषणा SERV6_IP_3		0x0000abcd
#घोषणा SERV6_PORT		6060

SEC("cgroup/recvmsg6")
पूर्णांक recvmsg6_prog(काष्ठा bpf_sock_addr *ctx)
अणु
	काष्ठा bpf_sock *sk;
	__u32 user_ip4;
	__u16 user_port;

	sk = ctx->sk;
	अगर (!sk)
		वापस 1;

	अगर (sk->family != AF_INET6)
		वापस 1;

	अगर (ctx->type != SOCK_STREAM && ctx->type != SOCK_DGRAM)
		वापस 1;

	अगर (!get_set_sk_priority(ctx))
		वापस 1;

	ctx->user_ip6[0] = bpf_htonl(SERV6_IP_0);
	ctx->user_ip6[1] = bpf_htonl(SERV6_IP_1);
	ctx->user_ip6[2] = bpf_htonl(SERV6_IP_2);
	ctx->user_ip6[3] = bpf_htonl(SERV6_IP_3);
	ctx->user_port = bpf_htons(SERV6_PORT);

	वापस 1;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
