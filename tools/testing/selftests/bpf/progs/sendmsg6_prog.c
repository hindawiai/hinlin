<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2018 Facebook

#समावेश <linux/मानकघोष.स>
#समावेश <linux/bpf.h>
#समावेश <sys/socket.h>

#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_endian.h>

#समावेश <bpf_sockopt_helpers.h>

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

SEC("cgroup/sendmsg6")
पूर्णांक sendmsg_v6_prog(काष्ठा bpf_sock_addr *ctx)
अणु
	अगर (ctx->type != SOCK_DGRAM)
		वापस 0;

	अगर (!get_set_sk_priority(ctx))
		वापस 0;

	/* Reग_लिखो source. */
	अगर (ctx->msg_src_ip6[3] == bpf_htonl(1) ||
	    ctx->msg_src_ip6[3] == bpf_htonl(0)) अणु
		ctx->msg_src_ip6[0] = bpf_htonl(SRC_REWRITE_IP6_0);
		ctx->msg_src_ip6[1] = bpf_htonl(SRC_REWRITE_IP6_1);
		ctx->msg_src_ip6[2] = bpf_htonl(SRC_REWRITE_IP6_2);
		ctx->msg_src_ip6[3] = bpf_htonl(SRC_REWRITE_IP6_3);
	पूर्ण अन्यथा अणु
		/* Unexpected source. Reject sendmsg. */
		वापस 0;
	पूर्ण

	/* Reग_लिखो destination. */
	अगर (ctx->user_ip6[0] == bpf_htonl(0xFACEB00C)) अणु
		ctx->user_ip6[0] = bpf_htonl(DST_REWRITE_IP6_0);
		ctx->user_ip6[1] = bpf_htonl(DST_REWRITE_IP6_1);
		ctx->user_ip6[2] = bpf_htonl(DST_REWRITE_IP6_2);
		ctx->user_ip6[3] = bpf_htonl(DST_REWRITE_IP6_3);

		ctx->user_port = bpf_htons(DST_REWRITE_PORT6);
	पूर्ण अन्यथा अणु
		/* Unexpected destination. Reject sendmsg. */
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
