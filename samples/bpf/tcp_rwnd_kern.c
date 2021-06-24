<शैली गुरु>
/* Copyright (c) 2017 Facebook
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of version 2 of the GNU General Public
 * License as published by the Free Software Foundation.
 *
 * BPF program to set initial receive winकरोw to 40 packets when using IPv6
 * and the first 5.5 bytes of the IPv6 addresses are not the same (in this
 * example that means both hosts are not the same datacenter).
 *
 * Use "bpftool cgroup attach $cg sock_ops $prog" to load this BPF program.
 */

#समावेश <uapi/linux/bpf.h>
#समावेश <uapi/linux/अगर_ether.h>
#समावेश <uapi/linux/अगर_packet.h>
#समावेश <uapi/linux/ip.h>
#समावेश <linux/socket.h>
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_endian.h>

#घोषणा DEBUG 1

SEC("sockops")
पूर्णांक bpf_rwnd(काष्ठा bpf_sock_ops *skops)
अणु
	पूर्णांक rv = -1;
	पूर्णांक op;

	/* For testing purposes, only execute rest of BPF program
	 * अगर neither port numberis 55601
	 */
	अगर (bpf_ntohl(skops->remote_port) !=
	    55601 && skops->local_port != 55601) अणु
		skops->reply = -1;
		वापस 1;
	पूर्ण

	op = (पूर्णांक) skops->op;

#अगर_घोषित DEBUG
	bpf_prपूर्णांकk("BPF command: %d\n", op);
#पूर्ण_अगर

	/* Check क्रम RWND_INIT operation and IPv6 addresses */
	अगर (op == BPF_SOCK_OPS_RWND_INIT &&
		skops->family == AF_INET6) अणु

		/* If the first 5.5 bytes of the IPv6 address are not the same
		 * then both hosts are not in the same datacenter
		 * so use a larger initial advertized winकरोw (40 packets)
		 */
		अगर (skops->local_ip6[0] != skops->remote_ip6[0] ||
		    (bpf_ntohl(skops->local_ip6[1]) & 0xfffff000) !=
		    (bpf_ntohl(skops->remote_ip6[1]) & 0xfffff000))
			rv = 40;
	पूर्ण
#अगर_घोषित DEBUG
	bpf_prपूर्णांकk("Returning %d\n", rv);
#पूर्ण_अगर
	skops->reply = rv;
	वापस 1;
पूर्ण
अक्षर _license[] SEC("license") = "GPL";
