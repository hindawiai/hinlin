<शैली गुरु>
/* Copyright (c) 2017 Facebook
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of version 2 of the GNU General Public
 * License as published by the Free Software Foundation.
 *
 * BPF program to set base_rtt to 80us when host is running TCP-NV and
 * both hosts are in the same datacenter (as determined by IPv6 prefix).
 *
 * Use "bpftool cgroup attach $cg sock_ops $prog" to load this BPF program.
 */

#समावेश <uapi/linux/bpf.h>
#समावेश <uapi/linux/tcp.h>
#समावेश <uapi/linux/अगर_ether.h>
#समावेश <uapi/linux/अगर_packet.h>
#समावेश <uapi/linux/ip.h>
#समावेश <linux/socket.h>
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_endian.h>

#घोषणा DEBUG 1

SEC("sockops")
पूर्णांक bpf_basertt(काष्ठा bpf_sock_ops *skops)
अणु
	अक्षर cong[20];
	अक्षर nv[] = "nv";
	पूर्णांक rv = 0, n;
	पूर्णांक op;

	op = (पूर्णांक) skops->op;

#अगर_घोषित DEBUG
	bpf_prपूर्णांकk("BPF command: %d\n", op);
#पूर्ण_अगर

	/* Check अगर both hosts are in the same datacenter. For this
	 * example they are अगर the 1st 5.5 bytes in the IPv6 address
	 * are the same.
	 */
	अगर (skops->family == AF_INET6 &&
	    skops->local_ip6[0] == skops->remote_ip6[0] &&
	    (bpf_ntohl(skops->local_ip6[1]) & 0xfff00000) ==
	    (bpf_ntohl(skops->remote_ip6[1]) & 0xfff00000)) अणु
		चयन (op) अणु
		हाल BPF_SOCK_OPS_BASE_RTT:
			n = bpf_माला_लोockopt(skops, SOL_TCP, TCP_CONGESTION,
					   cong, माप(cong));
			अगर (!n && !__builtin_स_भेद(cong, nv, माप(nv)+1)) अणु
				/* Set base_rtt to 80us */
				rv = 80;
			पूर्ण अन्यथा अगर (n) अणु
				rv = n;
			पूर्ण अन्यथा अणु
				rv = -1;
			पूर्ण
			अवरोध;
		शेष:
			rv = -1;
		पूर्ण
	पूर्ण अन्यथा अणु
		rv = -1;
	पूर्ण
#अगर_घोषित DEBUG
	bpf_prपूर्णांकk("Returning %d\n", rv);
#पूर्ण_अगर
	skops->reply = rv;
	वापस 1;
पूर्ण
अक्षर _license[] SEC("license") = "GPL";
