<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2018 Facebook

#समावेश <linux/मानकघोष.स>
#समावेश <linux/bpf.h>
#समावेश <sys/socket.h>

#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_endian.h>

#समावेश <bpf_sockopt_helpers.h>

#घोषणा SRC1_IP4		0xAC100001U /* 172.16.0.1 */
#घोषणा SRC2_IP4		0x00000000U
#घोषणा SRC_REWRITE_IP4		0x7f000004U
#घोषणा DST_IP4			0xC0A801FEU /* 192.168.1.254 */
#घोषणा DST_REWRITE_IP4		0x7f000001U
#घोषणा DST_PORT		4040
#घोषणा DST_REWRITE_PORT4	4444

पूर्णांक _version SEC("version") = 1;

SEC("cgroup/sendmsg4")
पूर्णांक sendmsg_v4_prog(काष्ठा bpf_sock_addr *ctx)
अणु
	पूर्णांक prio;

	अगर (ctx->type != SOCK_DGRAM)
		वापस 0;

	अगर (!get_set_sk_priority(ctx))
		वापस 0;

	/* Reग_लिखो source. */
	अगर (ctx->msg_src_ip4 == bpf_htonl(SRC1_IP4) ||
	    ctx->msg_src_ip4 == bpf_htonl(SRC2_IP4)) अणु
		ctx->msg_src_ip4 = bpf_htonl(SRC_REWRITE_IP4);
	पूर्ण अन्यथा अणु
		/* Unexpected source. Reject sendmsg. */
		वापस 0;
	पूर्ण

	/* Reग_लिखो destination. */
	अगर ((ctx->user_ip4 >> 24) == (bpf_htonl(DST_IP4) >> 24) &&
	     ctx->user_port == bpf_htons(DST_PORT)) अणु
		ctx->user_ip4 = bpf_htonl(DST_REWRITE_IP4);
		ctx->user_port = bpf_htons(DST_REWRITE_PORT4);
	पूर्ण अन्यथा अणु
		/* Unexpected source. Reject sendmsg. */
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
