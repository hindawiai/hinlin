<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

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

#घोषणा SERV6_IP_0		0xfaceb00c /* face:b00c:1234:5678::abcd */
#घोषणा SERV6_IP_1		0x12345678
#घोषणा SERV6_IP_2		0x00000000
#घोषणा SERV6_IP_3		0x0000abcd
#घोषणा SERV6_PORT		6060
#घोषणा SERV6_REWRITE_IP_0	0x00000000
#घोषणा SERV6_REWRITE_IP_1	0x00000000
#घोषणा SERV6_REWRITE_IP_2	0x00000000
#घोषणा SERV6_REWRITE_IP_3	0x00000001
#घोषणा SERV6_REWRITE_PORT	6666

#अगर_अघोषित IFNAMSIZ
#घोषणा IFNAMSIZ 16
#पूर्ण_अगर

अटल __अंतरभूत पूर्णांक bind_to_device(काष्ठा bpf_sock_addr *ctx)
अणु
	अक्षर veth1[IFNAMSIZ] = "test_sock_addr1";
	अक्षर veth2[IFNAMSIZ] = "test_sock_addr2";
	अक्षर missing[IFNAMSIZ] = "nonexistent_dev";
	अक्षर del_bind[IFNAMSIZ] = "";
	पूर्णांक veth1_idx, veth2_idx;

	अगर (bpf_setsockopt(ctx, SOL_SOCKET, SO_BINDTODEVICE,
			   &veth1, माप(veth1)))
		वापस 1;
	अगर (bpf_माला_लोockopt(ctx, SOL_SOCKET, SO_BINDTOIFINDEX,
			   &veth1_idx, माप(veth1_idx)) || !veth1_idx)
		वापस 1;
	अगर (bpf_setsockopt(ctx, SOL_SOCKET, SO_BINDTODEVICE,
			   &veth2, माप(veth2)))
		वापस 1;
	अगर (bpf_माला_लोockopt(ctx, SOL_SOCKET, SO_BINDTOIFINDEX,
			   &veth2_idx, माप(veth2_idx)) || !veth2_idx ||
	    veth1_idx == veth2_idx)
		वापस 1;
	अगर (bpf_setsockopt(ctx, SOL_SOCKET, SO_BINDTODEVICE,
			   &missing, माप(missing)) != -ENODEV)
		वापस 1;
	अगर (bpf_setsockopt(ctx, SOL_SOCKET, SO_BINDTOIFINDEX,
			   &veth1_idx, माप(veth1_idx)))
		वापस 1;
	अगर (bpf_setsockopt(ctx, SOL_SOCKET, SO_BINDTODEVICE,
			   &del_bind, माप(del_bind)))
		वापस 1;

	वापस 0;
पूर्ण

अटल __अंतरभूत पूर्णांक bind_reuseport(काष्ठा bpf_sock_addr *ctx)
अणु
	पूर्णांक val = 1;

	अगर (bpf_setsockopt(ctx, SOL_SOCKET, SO_REUSEPORT,
			   &val, माप(val)))
		वापस 1;
	अगर (bpf_माला_लोockopt(ctx, SOL_SOCKET, SO_REUSEPORT,
			   &val, माप(val)) || !val)
		वापस 1;
	val = 0;
	अगर (bpf_setsockopt(ctx, SOL_SOCKET, SO_REUSEPORT,
			   &val, माप(val)))
		वापस 1;
	अगर (bpf_माला_लोockopt(ctx, SOL_SOCKET, SO_REUSEPORT,
			   &val, माप(val)) || val)
		वापस 1;

	वापस 0;
पूर्ण

अटल __अंतरभूत पूर्णांक misc_opts(काष्ठा bpf_sock_addr *ctx, पूर्णांक opt)
अणु
	पूर्णांक old, पंचांगp, new = 0xeb9f;

	/* Socket in test हाल has guarantee that old never equals to new. */
	अगर (bpf_माला_लोockopt(ctx, SOL_SOCKET, opt, &old, माप(old)) ||
	    old == new)
		वापस 1;
	अगर (bpf_setsockopt(ctx, SOL_SOCKET, opt, &new, माप(new)))
		वापस 1;
	अगर (bpf_माला_लोockopt(ctx, SOL_SOCKET, opt, &पंचांगp, माप(पंचांगp)) ||
	    पंचांगp != new)
		वापस 1;
	अगर (bpf_setsockopt(ctx, SOL_SOCKET, opt, &old, माप(old)))
		वापस 1;

	वापस 0;
पूर्ण

SEC("cgroup/bind6")
पूर्णांक bind_v6_prog(काष्ठा bpf_sock_addr *ctx)
अणु
	काष्ठा bpf_sock *sk;
	__u32 user_ip6;
	__u16 user_port;
	पूर्णांक i;

	sk = ctx->sk;
	अगर (!sk)
		वापस 0;

	अगर (sk->family != AF_INET6)
		वापस 0;

	अगर (ctx->type != SOCK_STREAM && ctx->type != SOCK_DGRAM)
		वापस 0;

	अगर (ctx->user_ip6[0] != bpf_htonl(SERV6_IP_0) ||
	    ctx->user_ip6[1] != bpf_htonl(SERV6_IP_1) ||
	    ctx->user_ip6[2] != bpf_htonl(SERV6_IP_2) ||
	    ctx->user_ip6[3] != bpf_htonl(SERV6_IP_3) ||
	    ctx->user_port != bpf_htons(SERV6_PORT))
		वापस 0;

	// u8 narrow loads:
	क्रम (i = 0; i < 4; i++) अणु
		user_ip6 = 0;
		user_ip6 |= ((अस्थिर __u8 *)&ctx->user_ip6[i])[0] << 0;
		user_ip6 |= ((अस्थिर __u8 *)&ctx->user_ip6[i])[1] << 8;
		user_ip6 |= ((अस्थिर __u8 *)&ctx->user_ip6[i])[2] << 16;
		user_ip6 |= ((अस्थिर __u8 *)&ctx->user_ip6[i])[3] << 24;
		अगर (ctx->user_ip6[i] != user_ip6)
			वापस 0;
	पूर्ण

	user_port = 0;
	user_port |= ((अस्थिर __u8 *)&ctx->user_port)[0] << 0;
	user_port |= ((अस्थिर __u8 *)&ctx->user_port)[1] << 8;
	अगर (ctx->user_port != user_port)
		वापस 0;

	// u16 narrow loads:
	क्रम (i = 0; i < 4; i++) अणु
		user_ip6 = 0;
		user_ip6 |= ((अस्थिर __u16 *)&ctx->user_ip6[i])[0] << 0;
		user_ip6 |= ((अस्थिर __u16 *)&ctx->user_ip6[i])[1] << 16;
		अगर (ctx->user_ip6[i] != user_ip6)
			वापस 0;
	पूर्ण

	/* Bind to device and unbind it. */
	अगर (bind_to_device(ctx))
		वापस 0;

	/* Test क्रम misc socket options. */
	अगर (misc_opts(ctx, SO_MARK) || misc_opts(ctx, SO_PRIORITY))
		वापस 0;

	/* Set reuseport and unset */
	अगर (bind_reuseport(ctx))
		वापस 0;

	ctx->user_ip6[0] = bpf_htonl(SERV6_REWRITE_IP_0);
	ctx->user_ip6[1] = bpf_htonl(SERV6_REWRITE_IP_1);
	ctx->user_ip6[2] = bpf_htonl(SERV6_REWRITE_IP_2);
	ctx->user_ip6[3] = bpf_htonl(SERV6_REWRITE_IP_3);
	ctx->user_port = bpf_htons(SERV6_REWRITE_PORT);

	वापस 1;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
