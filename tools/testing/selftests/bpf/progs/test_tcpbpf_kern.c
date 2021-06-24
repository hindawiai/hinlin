<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <मानकघोष.स>
#समावेश <माला.स>
#समावेश <netinet/in.h>
#समावेश <linux/bpf.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/अगर_packet.h>
#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/types.h>
#समावेश <linux/socket.h>
#समावेश <linux/tcp.h>
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_endian.h>
#समावेश "bpf_tcp_helpers.h"
#समावेश "test_tcpbpf.h"

काष्ठा tcpbpf_globals global = अणुपूर्ण;
पूर्णांक _version SEC("version") = 1;

/**
 * SOL_TCP is defined in <netinet/tcp.h> जबतक
 * TCP_SAVED_SYN is defined in alपढ़ोy included <linux/tcp.h>
 */
#अगर_अघोषित SOL_TCP
#घोषणा SOL_TCP 6
#पूर्ण_अगर

अटल __always_अंतरभूत पूर्णांक get_tp_winकरोw_clamp(काष्ठा bpf_sock_ops *skops)
अणु
	काष्ठा bpf_sock *sk;
	काष्ठा tcp_sock *tp;

	sk = skops->sk;
	अगर (!sk)
		वापस -1;
	tp = bpf_skc_to_tcp_sock(sk);
	अगर (!tp)
		वापस -1;
	वापस tp->winकरोw_clamp;
पूर्ण

SEC("sockops")
पूर्णांक bpf_testcb(काष्ठा bpf_sock_ops *skops)
अणु
	अक्षर header[माप(काष्ठा ipv6hdr) + माप(काष्ठा tcphdr)];
	काष्ठा bpf_sock_ops *reuse = skops;
	काष्ठा tcphdr *thdr;
	पूर्णांक winकरोw_clamp = 9216;
	पूर्णांक good_call_rv = 0;
	पूर्णांक bad_call_rv = 0;
	पूर्णांक save_syn = 1;
	पूर्णांक rv = -1;
	पूर्णांक v = 0;
	पूर्णांक op;

	/* Test पढ़ोing fields in bpf_sock_ops using single रेजिस्टर */
	यंत्र अस्थिर (
		"%[reuse] = *(u32 *)(%[reuse] +96)"
		: [reuse] "+r"(reuse)
		:);

	यंत्र अस्थिर (
		"%[op] = *(u32 *)(%[skops] +96)"
		: [op] "+r"(op)
		: [skops] "r"(skops)
		:);

	यंत्र अस्थिर (
		"r9 = %[skops];\n"
		"r8 = *(u32 *)(r9 +164);\n"
		"*(u32 *)(r9 +164) = r8;\n"
		:: [skops] "r"(skops)
		: "r9", "r8");

	यंत्र अस्थिर (
		"r1 = %[skops];\n"
		"r1 = *(u64 *)(r1 +184);\n"
		"if r1 == 0 goto +1;\n"
		"r1 = *(u32 *)(r1 +4);\n"
		:: [skops] "r"(skops):"r1");

	यंत्र अस्थिर (
		"r9 = %[skops];\n"
		"r9 = *(u64 *)(r9 +184);\n"
		"if r9 == 0 goto +1;\n"
		"r9 = *(u32 *)(r9 +4);\n"
		:: [skops] "r"(skops):"r9");

	यंत्र अस्थिर (
		"r1 = %[skops];\n"
		"r2 = *(u64 *)(r1 +184);\n"
		"if r2 == 0 goto +1;\n"
		"r2 = *(u32 *)(r2 +4);\n"
		:: [skops] "r"(skops):"r1", "r2");

	op = (पूर्णांक) skops->op;

	global.event_map |= (1 << op);

	चयन (op) अणु
	हाल BPF_SOCK_OPS_TCP_CONNECT_CB:
		rv = bpf_setsockopt(skops, SOL_TCP, TCP_WINDOW_CLAMP,
				    &winकरोw_clamp, माप(winकरोw_clamp));
		global.winकरोw_clamp_client = get_tp_winकरोw_clamp(skops);
		अवरोध;
	हाल BPF_SOCK_OPS_ACTIVE_ESTABLISHED_CB:
		/* Test failure to set largest cb flag (assumes not defined) */
		global.bad_cb_test_rv = bpf_sock_ops_cb_flags_set(skops, 0x80);
		/* Set callback */
		global.good_cb_test_rv = bpf_sock_ops_cb_flags_set(skops,
						 BPF_SOCK_OPS_STATE_CB_FLAG);
		अवरोध;
	हाल BPF_SOCK_OPS_PASSIVE_ESTABLISHED_CB:
		skops->sk_txhash = 0x12345f;
		v = 0xff;
		rv = bpf_setsockopt(skops, SOL_IPV6, IPV6_TCLASS, &v,
				    माप(v));
		अगर (skops->family == AF_INET6) अणु
			v = bpf_माला_लोockopt(skops, IPPROTO_TCP, TCP_SAVED_SYN,
					   header, (माप(काष्ठा ipv6hdr) +
						    माप(काष्ठा tcphdr)));
			अगर (!v) अणु
				पूर्णांक offset = माप(काष्ठा ipv6hdr);

				thdr = (काष्ठा tcphdr *)(header + offset);
				v = thdr->syn;

				global.tcp_saved_syn = v;
			पूर्ण
		पूर्ण
		rv = bpf_setsockopt(skops, SOL_TCP, TCP_WINDOW_CLAMP,
				    &winकरोw_clamp, माप(winकरोw_clamp));

		global.winकरोw_clamp_server = get_tp_winकरोw_clamp(skops);
		अवरोध;
	हाल BPF_SOCK_OPS_RTO_CB:
		अवरोध;
	हाल BPF_SOCK_OPS_RETRANS_CB:
		अवरोध;
	हाल BPF_SOCK_OPS_STATE_CB:
		अगर (skops->args[1] == BPF_TCP_CLOSE) अणु
			अगर (skops->args[0] == BPF_TCP_LISTEN) अणु
				global.num_listen++;
			पूर्ण अन्यथा अणु
				global.total_retrans = skops->total_retrans;
				global.data_segs_in = skops->data_segs_in;
				global.data_segs_out = skops->data_segs_out;
				global.bytes_received = skops->bytes_received;
				global.bytes_acked = skops->bytes_acked;
			पूर्ण
			global.num_बंद_events++;
		पूर्ण
		अवरोध;
	हाल BPF_SOCK_OPS_TCP_LISTEN_CB:
		bpf_sock_ops_cb_flags_set(skops, BPF_SOCK_OPS_STATE_CB_FLAG);
		v = bpf_setsockopt(skops, IPPROTO_TCP, TCP_SAVE_SYN,
				   &save_syn, माप(save_syn));
		/* Update global map w/ result of setsock opt */
		global.tcp_save_syn = v;
		अवरोध;
	शेष:
		rv = -1;
	पूर्ण
	skops->reply = rv;
	वापस 1;
पूर्ण
अक्षर _license[] SEC("license") = "GPL";
