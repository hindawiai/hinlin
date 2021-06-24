<शैली गुरु>
/* Copyright (c) 2016 John Fastabend <john.r.fastabend@पूर्णांकel.com>
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of version 2 of the GNU General Public
 * License as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License क्रम more details.
 */
#घोषणा KBUILD_MODNAME "foo"
#समावेश <uapi/linux/bpf.h>
#समावेश <linux/in.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/अगर_packet.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <bpf/bpf_helpers.h>

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_ARRAY);
	__type(key, पूर्णांक);
	__type(value, पूर्णांक);
	__uपूर्णांक(max_entries, 1);
पूर्ण tx_port SEC(".maps");

/* Count RX packets, as XDP bpf_prog करोesn't get direct TX-success
 * feedback.  Redirect TX errors can be caught via a tracepoपूर्णांक.
 */
काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_PERCPU_ARRAY);
	__type(key, u32);
	__type(value, दीर्घ);
	__uपूर्णांक(max_entries, 1);
पूर्ण rxcnt SEC(".maps");

अटल व्योम swap_src_dst_mac(व्योम *data)
अणु
	अचिन्हित लघु *p = data;
	अचिन्हित लघु dst[3];

	dst[0] = p[0];
	dst[1] = p[1];
	dst[2] = p[2];
	p[0] = p[3];
	p[1] = p[4];
	p[2] = p[5];
	p[3] = dst[0];
	p[4] = dst[1];
	p[5] = dst[2];
पूर्ण

SEC("xdp_redirect")
पूर्णांक xdp_redirect_prog(काष्ठा xdp_md *ctx)
अणु
	व्योम *data_end = (व्योम *)(दीर्घ)ctx->data_end;
	व्योम *data = (व्योम *)(दीर्घ)ctx->data;
	काष्ठा ethhdr *eth = data;
	पूर्णांक rc = XDP_DROP;
	पूर्णांक *अगरindex, port = 0;
	दीर्घ *value;
	u32 key = 0;
	u64 nh_off;

	nh_off = माप(*eth);
	अगर (data + nh_off > data_end)
		वापस rc;

	अगरindex = bpf_map_lookup_elem(&tx_port, &port);
	अगर (!अगरindex)
		वापस rc;

	value = bpf_map_lookup_elem(&rxcnt, &key);
	अगर (value)
		*value += 1;

	swap_src_dst_mac(data);
	वापस bpf_redirect(*अगरindex, 0);
पूर्ण

/* Redirect require an XDP bpf_prog loaded on the TX device */
SEC("xdp_redirect_dummy")
पूर्णांक xdp_redirect_dummy_prog(काष्ठा xdp_md *ctx)
अणु
	वापस XDP_PASS;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
