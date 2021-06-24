<शैली गुरु>
/* Copyright (c) 2017 Facebook
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of version 2 of the GNU General Public
 * License as published by the Free Software Foundation.
 *
 * Sample BPF program to set send and receive buffers to 150KB, sndcwnd clamp
 * to 100 packets and SYN and SYN_ACK RTOs to 10ms when both hosts are within
 * the same datacenter. For his example, we assume they are within the same
 * datacenter when the first 5.5 bytes of their IPv6 addresses are the same.
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
पूर्णांक bpf_clamp(काष्ठा bpf_sock_ops *skops)
अणु
	पूर्णांक bufsize = 150000;
	पूर्णांक to_init = 10;
	पूर्णांक clamp = 100;
	पूर्णांक rv = 0;
	पूर्णांक op;

	/* For testing purposes, only execute rest of BPF program
	 * अगर neither port numberis 55601
	 */
	अगर (bpf_ntohl(skops->remote_port) != 55601 && skops->local_port != 55601) अणु
		skops->reply = -1;
		वापस 0;
	पूर्ण

	op = (पूर्णांक) skops->op;

#अगर_घोषित DEBUG
	bpf_prपूर्णांकk("BPF command: %d\n", op);
#पूर्ण_अगर

	/* Check that both hosts are within same datacenter. For this example
	 * it is the हाल when the first 5.5 bytes of their IPv6 addresses are
	 * the same.
	 */
	अगर (skops->family == AF_INET6 &&
	    skops->local_ip6[0] == skops->remote_ip6[0] &&
	    (bpf_ntohl(skops->local_ip6[1]) & 0xfff00000) ==
	    (bpf_ntohl(skops->remote_ip6[1]) & 0xfff00000)) अणु
		चयन (op) अणु
		हाल BPF_SOCK_OPS_TIMEOUT_INIT:
			rv = to_init;
			अवरोध;
		हाल BPF_SOCK_OPS_TCP_CONNECT_CB:
			/* Set sndbuf and rcvbuf of active connections */
			rv = bpf_setsockopt(skops, SOL_SOCKET, SO_SNDBUF,
					    &bufsize, माप(bufsize));
			rv += bpf_setsockopt(skops, SOL_SOCKET,
					     SO_RCVBUF, &bufsize,
					     माप(bufsize));
			अवरोध;
		हाल BPF_SOCK_OPS_ACTIVE_ESTABLISHED_CB:
			rv = bpf_setsockopt(skops, SOL_TCP,
					    TCP_BPF_SNDCWND_CLAMP,
					    &clamp, माप(clamp));
			अवरोध;
		हाल BPF_SOCK_OPS_PASSIVE_ESTABLISHED_CB:
			/* Set sndbuf and rcvbuf of passive connections */
			rv = bpf_setsockopt(skops, SOL_TCP,
					    TCP_BPF_SNDCWND_CLAMP,
					    &clamp, माप(clamp));
			rv += bpf_setsockopt(skops, SOL_SOCKET,
					     SO_SNDBUF, &bufsize,
					     माप(bufsize));
			rv += bpf_setsockopt(skops, SOL_SOCKET,
					     SO_RCVBUF, &bufsize,
					     माप(bufsize));
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
