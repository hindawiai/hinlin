<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2018 Facebook
 *
 * BPF program to स्वतःmatically reflect TOS option from received syn packet
 *
 * Use "bpftool cgroup attach $cg sock_ops $prog" to load this BPF program.
 */

#समावेश <uapi/linux/bpf.h>
#समावेश <uapi/linux/tcp.h>
#समावेश <uapi/linux/अगर_ether.h>
#समावेश <uapi/linux/अगर_packet.h>
#समावेश <uapi/linux/ip.h>
#समावेश <uapi/linux/ipv6.h>
#समावेश <uapi/linux/in.h>
#समावेश <linux/socket.h>
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_endian.h>

#घोषणा DEBUG 1

SEC("sockops")
पूर्णांक bpf_basertt(काष्ठा bpf_sock_ops *skops)
अणु
	अक्षर header[माप(काष्ठा ipv6hdr)];
	काष्ठा ipv6hdr *hdr6;
	काष्ठा iphdr *hdr;
	पूर्णांक hdr_size = 0;
	पूर्णांक save_syn = 1;
	पूर्णांक tos = 0;
	पूर्णांक rv = 0;
	पूर्णांक op;

	op = (पूर्णांक) skops->op;

#अगर_घोषित DEBUG
	bpf_prपूर्णांकk("BPF command: %d\n", op);
#पूर्ण_अगर
	चयन (op) अणु
	हाल BPF_SOCK_OPS_TCP_LISTEN_CB:
		rv = bpf_setsockopt(skops, SOL_TCP, TCP_SAVE_SYN,
				   &save_syn, माप(save_syn));
		अवरोध;
	हाल BPF_SOCK_OPS_PASSIVE_ESTABLISHED_CB:
		अगर (skops->family == AF_INET)
			hdr_size = माप(काष्ठा iphdr);
		अन्यथा
			hdr_size = माप(काष्ठा ipv6hdr);
		rv = bpf_माला_लोockopt(skops, SOL_TCP, TCP_SAVED_SYN,
				    header, hdr_size);
		अगर (!rv) अणु
			अगर (skops->family == AF_INET) अणु
				hdr = (काष्ठा iphdr *) header;
				tos = hdr->tos;
				अगर (tos != 0)
					bpf_setsockopt(skops, SOL_IP, IP_TOS,
						       &tos, माप(tos));
			पूर्ण अन्यथा अणु
				hdr6 = (काष्ठा ipv6hdr *) header;
				tos = ((hdr6->priority) << 4 |
				       (hdr6->flow_lbl[0]) >>  4);
				अगर (tos)
					bpf_setsockopt(skops, SOL_IPV6,
						       IPV6_TCLASS,
						       &tos, माप(tos));
			पूर्ण
			rv = 0;
		पूर्ण
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
