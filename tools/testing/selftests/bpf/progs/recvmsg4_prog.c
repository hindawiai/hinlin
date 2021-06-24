<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/मानकघोष.स>
#समावेश <linux/bpf.h>
#समावेश <linux/in.h>
#समावेश <sys/socket.h>

#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_endian.h>

#समावेश <bpf_sockopt_helpers.h>

#घोषणा SERV4_IP		0xc0a801feU /* 192.168.1.254 */
#घोषणा SERV4_PORT		4040

SEC("cgroup/recvmsg4")
पूर्णांक recvmsg4_prog(काष्ठा bpf_sock_addr *ctx)
अणु
	काष्ठा bpf_sock *sk;
	__u32 user_ip4;
	__u16 user_port;

	sk = ctx->sk;
	अगर (!sk)
		वापस 1;

	अगर (sk->family != AF_INET)
		वापस 1;

	अगर (ctx->type != SOCK_STREAM && ctx->type != SOCK_DGRAM)
		वापस 1;

	अगर (!get_set_sk_priority(ctx))
		वापस 1;

	ctx->user_ip4 = bpf_htonl(SERV4_IP);
	ctx->user_port = bpf_htons(SERV4_PORT);

	वापस 1;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
