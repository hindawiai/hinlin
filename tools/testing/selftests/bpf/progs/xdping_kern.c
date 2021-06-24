<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2019, Oracle and/or its affiliates. All rights reserved. */

#घोषणा KBUILD_MODNAME "foo"
#समावेश <मानकघोष.स>
#समावेश <माला.स>
#समावेश <linux/bpf.h>
#समावेश <linux/icmp.h>
#समावेश <linux/in.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/अगर_packet.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/ip.h>

#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_endian.h>

#समावेश "xdping.h"

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_HASH);
	__uपूर्णांक(max_entries, 256);
	__type(key, __u32);
	__type(value, काष्ठा pinginfo);
पूर्ण ping_map SEC(".maps");

अटल __always_अंतरभूत व्योम swap_src_dst_mac(व्योम *data)
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

अटल __always_अंतरभूत __u16 csum_fold_helper(__wsum sum)
अणु
	sum = (sum & 0xffff) + (sum >> 16);
	वापस ~((sum & 0xffff) + (sum >> 16));
पूर्ण

अटल __always_अंतरभूत __u16 ipv4_csum(व्योम *data_start, पूर्णांक data_size)
अणु
	__wsum sum;

	sum = bpf_csum_dअगरf(0, 0, data_start, data_size, 0);
	वापस csum_fold_helper(sum);
पूर्ण

#घोषणा ICMP_ECHO_LEN		64

अटल __always_अंतरभूत पूर्णांक icmp_check(काष्ठा xdp_md *ctx, पूर्णांक type)
अणु
	व्योम *data_end = (व्योम *)(दीर्घ)ctx->data_end;
	व्योम *data = (व्योम *)(दीर्घ)ctx->data;
	काष्ठा ethhdr *eth = data;
	काष्ठा icmphdr *icmph;
	काष्ठा iphdr *iph;

	अगर (data + माप(*eth) + माप(*iph) + ICMP_ECHO_LEN > data_end)
		वापस XDP_PASS;

	अगर (eth->h_proto != bpf_htons(ETH_P_IP))
		वापस XDP_PASS;

	iph = data + माप(*eth);

	अगर (iph->protocol != IPPROTO_ICMP)
		वापस XDP_PASS;

	अगर (bpf_ntohs(iph->tot_len) - माप(*iph) != ICMP_ECHO_LEN)
		वापस XDP_PASS;

	icmph = data + माप(*eth) + माप(*iph);

	अगर (icmph->type != type)
		वापस XDP_PASS;

	वापस XDP_TX;
पूर्ण

SEC("xdpclient")
पूर्णांक xdping_client(काष्ठा xdp_md *ctx)
अणु
	व्योम *data_end = (व्योम *)(दीर्घ)ctx->data_end;
	व्योम *data = (व्योम *)(दीर्घ)ctx->data;
	काष्ठा pinginfo *pinginfo = शून्य;
	काष्ठा ethhdr *eth = data;
	काष्ठा icmphdr *icmph;
	काष्ठा iphdr *iph;
	__u64 recvसमय;
	__be32 raddr;
	__be16 seq;
	पूर्णांक ret;
	__u8 i;

	ret = icmp_check(ctx, ICMP_ECHOREPLY);

	अगर (ret != XDP_TX)
		वापस ret;

	iph = data + माप(*eth);
	icmph = data + माप(*eth) + माप(*iph);
	raddr = iph->saddr;

	/* Record समय reply received. */
	recvसमय = bpf_kसमय_get_ns();
	pinginfo = bpf_map_lookup_elem(&ping_map, &raddr);
	अगर (!pinginfo || pinginfo->seq != icmph->un.echo.sequence)
		वापस XDP_PASS;

	अगर (pinginfo->start) अणु
#आशय clang loop unroll(full)
		क्रम (i = 0; i < XDPING_MAX_COUNT; i++) अणु
			अगर (pinginfo->बार[i] == 0)
				अवरोध;
		पूर्ण
		/* verअगरier is fussy here... */
		अगर (i < XDPING_MAX_COUNT) अणु
			pinginfo->बार[i] = recvसमय -
					     pinginfo->start;
			pinginfo->start = 0;
			i++;
		पूर्ण
		/* No more space क्रम values? */
		अगर (i == pinginfo->count || i == XDPING_MAX_COUNT)
			वापस XDP_PASS;
	पूर्ण

	/* Now convert reply back पूर्णांकo echo request. */
	swap_src_dst_mac(data);
	iph->saddr = iph->daddr;
	iph->daddr = raddr;
	icmph->type = ICMP_ECHO;
	seq = bpf_htons(bpf_ntohs(icmph->un.echo.sequence) + 1);
	icmph->un.echo.sequence = seq;
	icmph->checksum = 0;
	icmph->checksum = ipv4_csum(icmph, ICMP_ECHO_LEN);

	pinginfo->seq = seq;
	pinginfo->start = bpf_kसमय_get_ns();

	वापस XDP_TX;
पूर्ण

SEC("xdpserver")
पूर्णांक xdping_server(काष्ठा xdp_md *ctx)
अणु
	व्योम *data_end = (व्योम *)(दीर्घ)ctx->data_end;
	व्योम *data = (व्योम *)(दीर्घ)ctx->data;
	काष्ठा ethhdr *eth = data;
	काष्ठा icmphdr *icmph;
	काष्ठा iphdr *iph;
	__be32 raddr;
	पूर्णांक ret;

	ret = icmp_check(ctx, ICMP_ECHO);

	अगर (ret != XDP_TX)
		वापस ret;

	iph = data + माप(*eth);
	icmph = data + माप(*eth) + माप(*iph);
	raddr = iph->saddr;

	/* Now convert request पूर्णांकo echo reply. */
	swap_src_dst_mac(data);
	iph->saddr = iph->daddr;
	iph->daddr = raddr;
	icmph->type = ICMP_ECHOREPLY;
	icmph->checksum = 0;
	icmph->checksum = ipv4_csum(icmph, ICMP_ECHO_LEN);

	वापस XDP_TX;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
