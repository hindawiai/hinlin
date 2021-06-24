<शैली गुरु>
/* Copyright (c) 2017 Facebook
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of version 2 of the GNU General Public
 * License as published by the Free Software Foundation.
 *
 * BPF program to set initial receive winकरोw to 40 packets and send
 * and receive buffers to 1.5MB. This would usually be करोne after
 * करोing appropriate checks that indicate the hosts are far enough
 * away (i.e. large RTT).
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
पूर्णांक bpf_bufs(काष्ठा bpf_sock_ops *skops)
अणु
	पूर्णांक bufsize = 1500000;
	पूर्णांक rwnd_init = 40;
	पूर्णांक rv = 0;
	पूर्णांक op;

	/* For testing purposes, only execute rest of BPF program
	 * अगर neither port numberis 55601
	 */
	अगर (bpf_ntohl(skops->remote_port) != 55601 &&
	    skops->local_port != 55601) अणु
		skops->reply = -1;
		वापस 1;
	पूर्ण

	op = (पूर्णांक) skops->op;

#अगर_घोषित DEBUG
	bpf_prपूर्णांकk("Returning %d\n", rv);
#पूर्ण_अगर

	/* Usually there would be a check to insure the hosts are far
	 * from each other so it makes sense to increase buffer sizes
	 */
	चयन (op) अणु
	हाल BPF_SOCK_OPS_RWND_INIT:
		rv = rwnd_init;
		अवरोध;
	हाल BPF_SOCK_OPS_TCP_CONNECT_CB:
		/* Set sndbuf and rcvbuf of active connections */
		rv = bpf_setsockopt(skops, SOL_SOCKET, SO_SNDBUF, &bufsize,
				    माप(bufsize));
		rv += bpf_setsockopt(skops, SOL_SOCKET, SO_RCVBUF,
				     &bufsize, माप(bufsize));
		अवरोध;
	हाल BPF_SOCK_OPS_ACTIVE_ESTABLISHED_CB:
		/* Nothing to करो */
		अवरोध;
	हाल BPF_SOCK_OPS_PASSIVE_ESTABLISHED_CB:
		/* Set sndbuf and rcvbuf of passive connections */
		rv = bpf_setsockopt(skops, SOL_SOCKET, SO_SNDBUF, &bufsize,
				    माप(bufsize));
		rv += bpf_setsockopt(skops, SOL_SOCKET, SO_RCVBUF,
				     &bufsize, माप(bufsize));
		अवरोध;
	शेष:
		rv = -1;
	पूर्ण
#अगर_घोषित DEBUG
	bpf_prपूर्णांकk("Returning %d\n", rv);
#पूर्ण_अगर
	skops->reply = rv;
	वापस 1;
पूर्ण
अक्षर _license[] SEC("license") = "GPL";
