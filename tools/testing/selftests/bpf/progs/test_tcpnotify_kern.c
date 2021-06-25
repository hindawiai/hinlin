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
#समावेश "test_tcpnotify.h"

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_ARRAY);
	__uपूर्णांक(max_entries, 4);
	__type(key, __u32);
	__type(value, काष्ठा tcpnotअगरy_globals);
पूर्ण global_map SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_PERF_EVENT_ARRAY);
	__uपूर्णांक(max_entries, 2);
	__uपूर्णांक(key_size, माप(पूर्णांक));
	__uपूर्णांक(value_size, माप(__u32));
पूर्ण perf_event_map SEC(".maps");

पूर्णांक _version SEC("version") = 1;

SEC("sockops")
पूर्णांक bpf_testcb(काष्ठा bpf_sock_ops *skops)
अणु
	पूर्णांक rv = -1;
	पूर्णांक op;

	op = (पूर्णांक) skops->op;

	अगर (bpf_ntohl(skops->remote_port) != TESTPORT) अणु
		skops->reply = -1;
		वापस 0;
	पूर्ण

	चयन (op) अणु
	हाल BPF_SOCK_OPS_TIMEOUT_INIT:
	हाल BPF_SOCK_OPS_RWND_INIT:
	हाल BPF_SOCK_OPS_NEEDS_ECN:
	हाल BPF_SOCK_OPS_BASE_RTT:
	हाल BPF_SOCK_OPS_RTO_CB:
		rv = 1;
		अवरोध;

	हाल BPF_SOCK_OPS_TCP_CONNECT_CB:
	हाल BPF_SOCK_OPS_TCP_LISTEN_CB:
	हाल BPF_SOCK_OPS_ACTIVE_ESTABLISHED_CB:
	हाल BPF_SOCK_OPS_PASSIVE_ESTABLISHED_CB:
		bpf_sock_ops_cb_flags_set(skops, (BPF_SOCK_OPS_RETRANS_CB_FLAG|
					  BPF_SOCK_OPS_RTO_CB_FLAG));
		rv = 1;
		अवरोध;
	हाल BPF_SOCK_OPS_RETRANS_CB: अणु
			__u32 key = 0;
			काष्ठा tcpnotअगरy_globals g, *gp;
			काष्ठा tcp_notअगरier msg = अणु
				.type = 0xde,
				.subtype = 0xad,
				.source = 0xbe,
				.hash = 0xef,
			पूर्ण;

			rv = 1;

			/* Update results */
			gp = bpf_map_lookup_elem(&global_map, &key);
			अगर (!gp)
				अवरोध;
			g = *gp;
			g.total_retrans = skops->total_retrans;
			g.ncalls++;
			bpf_map_update_elem(&global_map, &key, &g,
					    BPF_ANY);
			bpf_perf_event_output(skops, &perf_event_map,
					      BPF_F_CURRENT_CPU,
					      &msg, माप(msg));
		पूर्ण
		अवरोध;
	शेष:
		rv = -1;
	पूर्ण
	skops->reply = rv;
	वापस 1;
पूर्ण
अक्षर _license[] SEC("license") = "GPL";
