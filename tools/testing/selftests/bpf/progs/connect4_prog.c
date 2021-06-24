<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2018 Facebook

#समावेश <माला.स>

#समावेश <linux/मानकघोष.स>
#समावेश <linux/bpf.h>
#समावेश <linux/in.h>
#समावेश <linux/in6.h>
#समावेश <sys/socket.h>
#समावेश <netinet/tcp.h>
#समावेश <linux/अगर.h>
#समावेश <त्रुटिसं.स>

#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_endian.h>

#घोषणा SRC_REWRITE_IP4		0x7f000004U
#घोषणा DST_REWRITE_IP4		0x7f000001U
#घोषणा DST_REWRITE_PORT4	4444

#अगर_अघोषित TCP_CA_NAME_MAX
#घोषणा TCP_CA_NAME_MAX 16
#पूर्ण_अगर

#अगर_अघोषित TCP_NOTSENT_LOWAT
#घोषणा TCP_NOTSENT_LOWAT 25
#पूर्ण_अगर

#अगर_अघोषित IFNAMSIZ
#घोषणा IFNAMSIZ 16
#पूर्ण_अगर

पूर्णांक _version SEC("version") = 1;

__attribute__ ((noअंतरभूत))
पूर्णांक करो_bind(काष्ठा bpf_sock_addr *ctx)
अणु
	काष्ठा sockaddr_in sa = अणुपूर्ण;

	sa.sin_family = AF_INET;
	sa.sin_port = bpf_htons(0);
	sa.sin_addr.s_addr = bpf_htonl(SRC_REWRITE_IP4);

	अगर (bpf_bind(ctx, (काष्ठा sockaddr *)&sa, माप(sa)) != 0)
		वापस 0;

	वापस 1;
पूर्ण

अटल __अंतरभूत पूर्णांक verअगरy_cc(काष्ठा bpf_sock_addr *ctx,
			      अक्षर expected[TCP_CA_NAME_MAX])
अणु
	अक्षर buf[TCP_CA_NAME_MAX];
	पूर्णांक i;

	अगर (bpf_माला_लोockopt(ctx, SOL_TCP, TCP_CONGESTION, &buf, माप(buf)))
		वापस 1;

	क्रम (i = 0; i < TCP_CA_NAME_MAX; i++) अणु
		अगर (buf[i] != expected[i])
			वापस 1;
		अगर (buf[i] == 0)
			अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल __अंतरभूत पूर्णांक set_cc(काष्ठा bpf_sock_addr *ctx)
अणु
	अक्षर reno[TCP_CA_NAME_MAX] = "reno";
	अक्षर cubic[TCP_CA_NAME_MAX] = "cubic";

	अगर (bpf_setsockopt(ctx, SOL_TCP, TCP_CONGESTION, &reno, माप(reno)))
		वापस 1;
	अगर (verअगरy_cc(ctx, reno))
		वापस 1;

	अगर (bpf_setsockopt(ctx, SOL_TCP, TCP_CONGESTION, &cubic, माप(cubic)))
		वापस 1;
	अगर (verअगरy_cc(ctx, cubic))
		वापस 1;

	वापस 0;
पूर्ण

अटल __अंतरभूत पूर्णांक bind_to_device(काष्ठा bpf_sock_addr *ctx)
अणु
	अक्षर veth1[IFNAMSIZ] = "test_sock_addr1";
	अक्षर veth2[IFNAMSIZ] = "test_sock_addr2";
	अक्षर missing[IFNAMSIZ] = "nonexistent_dev";
	अक्षर del_bind[IFNAMSIZ] = "";

	अगर (bpf_setsockopt(ctx, SOL_SOCKET, SO_BINDTODEVICE,
				&veth1, माप(veth1)))
		वापस 1;
	अगर (bpf_setsockopt(ctx, SOL_SOCKET, SO_BINDTODEVICE,
				&veth2, माप(veth2)))
		वापस 1;
	अगर (bpf_setsockopt(ctx, SOL_SOCKET, SO_BINDTODEVICE,
				&missing, माप(missing)) != -ENODEV)
		वापस 1;
	अगर (bpf_setsockopt(ctx, SOL_SOCKET, SO_BINDTODEVICE,
				&del_bind, माप(del_bind)))
		वापस 1;

	वापस 0;
पूर्ण

अटल __अंतरभूत पूर्णांक set_keepalive(काष्ठा bpf_sock_addr *ctx)
अणु
	पूर्णांक zero = 0, one = 1;

	अगर (bpf_setsockopt(ctx, SOL_SOCKET, SO_KEEPALIVE, &one, माप(one)))
		वापस 1;
	अगर (ctx->type == SOCK_STREAM) अणु
		अगर (bpf_setsockopt(ctx, SOL_TCP, TCP_KEEPIDLE, &one, माप(one)))
			वापस 1;
		अगर (bpf_setsockopt(ctx, SOL_TCP, TCP_KEEPINTVL, &one, माप(one)))
			वापस 1;
		अगर (bpf_setsockopt(ctx, SOL_TCP, TCP_KEEPCNT, &one, माप(one)))
			वापस 1;
		अगर (bpf_setsockopt(ctx, SOL_TCP, TCP_SYNCNT, &one, माप(one)))
			वापस 1;
		अगर (bpf_setsockopt(ctx, SOL_TCP, TCP_USER_TIMEOUT, &one, माप(one)))
			वापस 1;
	पूर्ण
	अगर (bpf_setsockopt(ctx, SOL_SOCKET, SO_KEEPALIVE, &zero, माप(zero)))
		वापस 1;

	वापस 0;
पूर्ण

अटल __अंतरभूत पूर्णांक set_notsent_lowat(काष्ठा bpf_sock_addr *ctx)
अणु
	पूर्णांक lowat = 65535;

	अगर (ctx->type == SOCK_STREAM) अणु
		अगर (bpf_setsockopt(ctx, SOL_TCP, TCP_NOTSENT_LOWAT, &lowat, माप(lowat)))
			वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

SEC("cgroup/connect4")
पूर्णांक connect_v4_prog(काष्ठा bpf_sock_addr *ctx)
अणु
	काष्ठा bpf_sock_tuple tuple = अणुपूर्ण;
	काष्ठा bpf_sock *sk;

	/* Verअगरy that new destination is available. */
	स_रखो(&tuple.ipv4.saddr, 0, माप(tuple.ipv4.saddr));
	स_रखो(&tuple.ipv4.sport, 0, माप(tuple.ipv4.sport));

	tuple.ipv4.daddr = bpf_htonl(DST_REWRITE_IP4);
	tuple.ipv4.dport = bpf_htons(DST_REWRITE_PORT4);

	/* Bind to device and unbind it. */
	अगर (bind_to_device(ctx))
		वापस 0;

	अगर (set_keepalive(ctx))
		वापस 0;

	अगर (set_notsent_lowat(ctx))
		वापस 0;

	अगर (ctx->type != SOCK_STREAM && ctx->type != SOCK_DGRAM)
		वापस 0;
	अन्यथा अगर (ctx->type == SOCK_STREAM)
		sk = bpf_sk_lookup_tcp(ctx, &tuple, माप(tuple.ipv4),
				       BPF_F_CURRENT_NETNS, 0);
	अन्यथा
		sk = bpf_sk_lookup_udp(ctx, &tuple, माप(tuple.ipv4),
				       BPF_F_CURRENT_NETNS, 0);

	अगर (!sk)
		वापस 0;

	अगर (sk->src_ip4 != tuple.ipv4.daddr ||
	    sk->src_port != DST_REWRITE_PORT4) अणु
		bpf_sk_release(sk);
		वापस 0;
	पूर्ण

	bpf_sk_release(sk);

	/* Reग_लिखो congestion control. */
	अगर (ctx->type == SOCK_STREAM && set_cc(ctx))
		वापस 0;

	/* Reग_लिखो destination. */
	ctx->user_ip4 = bpf_htonl(DST_REWRITE_IP4);
	ctx->user_port = bpf_htons(DST_REWRITE_PORT4);

	वापस करो_bind(ctx) ? 1 : 0;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
