<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2016 VMware
 * Copyright (c) 2016 Facebook
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of version 2 of the GNU General Public
 * License as published by the Free Software Foundation.
 */
#समावेश <मानकघोष.स>
#समावेश <माला.स>
#समावेश <arpa/inet.h>
#समावेश <linux/bpf.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/अगर_packet.h>
#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/types.h>
#समावेश <linux/socket.h>
#समावेश <linux/pkt_cls.h>
#समावेश <linux/erspan.h>
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_endian.h>

#घोषणा ERROR(ret) करो अणु\
		अक्षर fmt[] = "ERROR line:%d ret:%d\n";\
		bpf_trace_prपूर्णांकk(fmt, माप(fmt), __LINE__, ret); \
	पूर्ण जबतक (0)

पूर्णांक _version SEC("version") = 1;

काष्ठा geneve_opt अणु
	__be16	opt_class;
	__u8	type;
	__u8	length:5;
	__u8	r3:1;
	__u8	r2:1;
	__u8	r1:1;
	__u8	opt_data[8]; /* hard-coded to 8 byte */
पूर्ण;

काष्ठा vxlan_metadata अणु
	__u32     gbp;
पूर्ण;

SEC("gre_set_tunnel")
पूर्णांक _gre_set_tunnel(काष्ठा __sk_buff *skb)
अणु
	पूर्णांक ret;
	काष्ठा bpf_tunnel_key key;

	__builtin_स_रखो(&key, 0x0, माप(key));
	key.remote_ipv4 = 0xac100164; /* 172.16.1.100 */
	key.tunnel_id = 2;
	key.tunnel_tos = 0;
	key.tunnel_ttl = 64;

	ret = bpf_skb_set_tunnel_key(skb, &key, माप(key),
				     BPF_F_ZERO_CSUM_TX | BPF_F_SEQ_NUMBER);
	अगर (ret < 0) अणु
		ERROR(ret);
		वापस TC_ACT_SHOT;
	पूर्ण

	वापस TC_ACT_OK;
पूर्ण

SEC("gre_get_tunnel")
पूर्णांक _gre_get_tunnel(काष्ठा __sk_buff *skb)
अणु
	पूर्णांक ret;
	काष्ठा bpf_tunnel_key key;
	अक्षर fmt[] = "key %d remote ip 0x%x\n";

	ret = bpf_skb_get_tunnel_key(skb, &key, माप(key), 0);
	अगर (ret < 0) अणु
		ERROR(ret);
		वापस TC_ACT_SHOT;
	पूर्ण

	bpf_trace_prपूर्णांकk(fmt, माप(fmt), key.tunnel_id, key.remote_ipv4);
	वापस TC_ACT_OK;
पूर्ण

SEC("ip6gretap_set_tunnel")
पूर्णांक _ip6gretap_set_tunnel(काष्ठा __sk_buff *skb)
अणु
	काष्ठा bpf_tunnel_key key;
	पूर्णांक ret;

	__builtin_स_रखो(&key, 0x0, माप(key));
	key.remote_ipv6[3] = bpf_htonl(0x11); /* ::11 */
	key.tunnel_id = 2;
	key.tunnel_tos = 0;
	key.tunnel_ttl = 64;
	key.tunnel_label = 0xabcde;

	ret = bpf_skb_set_tunnel_key(skb, &key, माप(key),
				     BPF_F_TUNINFO_IPV6 | BPF_F_ZERO_CSUM_TX |
				     BPF_F_SEQ_NUMBER);
	अगर (ret < 0) अणु
		ERROR(ret);
		वापस TC_ACT_SHOT;
	पूर्ण

	वापस TC_ACT_OK;
पूर्ण

SEC("ip6gretap_get_tunnel")
पूर्णांक _ip6gretap_get_tunnel(काष्ठा __sk_buff *skb)
अणु
	अक्षर fmt[] = "key %d remote ip6 ::%x label %x\n";
	काष्ठा bpf_tunnel_key key;
	पूर्णांक ret;

	ret = bpf_skb_get_tunnel_key(skb, &key, माप(key),
				     BPF_F_TUNINFO_IPV6);
	अगर (ret < 0) अणु
		ERROR(ret);
		वापस TC_ACT_SHOT;
	पूर्ण

	bpf_trace_prपूर्णांकk(fmt, माप(fmt),
			 key.tunnel_id, key.remote_ipv6[3], key.tunnel_label);

	वापस TC_ACT_OK;
पूर्ण

SEC("erspan_set_tunnel")
पूर्णांक _erspan_set_tunnel(काष्ठा __sk_buff *skb)
अणु
	काष्ठा bpf_tunnel_key key;
	काष्ठा erspan_metadata md;
	पूर्णांक ret;

	__builtin_स_रखो(&key, 0x0, माप(key));
	key.remote_ipv4 = 0xac100164; /* 172.16.1.100 */
	key.tunnel_id = 2;
	key.tunnel_tos = 0;
	key.tunnel_ttl = 64;

	ret = bpf_skb_set_tunnel_key(skb, &key, माप(key),
				     BPF_F_ZERO_CSUM_TX);
	अगर (ret < 0) अणु
		ERROR(ret);
		वापस TC_ACT_SHOT;
	पूर्ण

	__builtin_स_रखो(&md, 0, माप(md));
#अगर_घोषित ERSPAN_V1
	md.version = 1;
	md.u.index = bpf_htonl(123);
#अन्यथा
	__u8 direction = 1;
	__u8 hwid = 7;

	md.version = 2;
	md.u.md2.dir = direction;
	md.u.md2.hwid = hwid & 0xf;
	md.u.md2.hwid_upper = (hwid >> 4) & 0x3;
#पूर्ण_अगर

	ret = bpf_skb_set_tunnel_opt(skb, &md, माप(md));
	अगर (ret < 0) अणु
		ERROR(ret);
		वापस TC_ACT_SHOT;
	पूर्ण

	वापस TC_ACT_OK;
पूर्ण

SEC("erspan_get_tunnel")
पूर्णांक _erspan_get_tunnel(काष्ठा __sk_buff *skb)
अणु
	अक्षर fmt[] = "key %d remote ip 0x%x erspan version %d\n";
	काष्ठा bpf_tunnel_key key;
	काष्ठा erspan_metadata md;
	__u32 index;
	पूर्णांक ret;

	ret = bpf_skb_get_tunnel_key(skb, &key, माप(key), 0);
	अगर (ret < 0) अणु
		ERROR(ret);
		वापस TC_ACT_SHOT;
	पूर्ण

	ret = bpf_skb_get_tunnel_opt(skb, &md, माप(md));
	अगर (ret < 0) अणु
		ERROR(ret);
		वापस TC_ACT_SHOT;
	पूर्ण

	bpf_trace_prपूर्णांकk(fmt, माप(fmt),
			key.tunnel_id, key.remote_ipv4, md.version);

#अगर_घोषित ERSPAN_V1
	अक्षर fmt2[] = "\tindex %x\n";

	index = bpf_ntohl(md.u.index);
	bpf_trace_prपूर्णांकk(fmt2, माप(fmt2), index);
#अन्यथा
	अक्षर fmt2[] = "\tdirection %d hwid %x timestamp %u\n";

	bpf_trace_prपूर्णांकk(fmt2, माप(fmt2),
			 md.u.md2.dir,
			 (md.u.md2.hwid_upper << 4) + md.u.md2.hwid,
			 bpf_ntohl(md.u.md2.बारtamp));
#पूर्ण_अगर

	वापस TC_ACT_OK;
पूर्ण

SEC("ip4ip6erspan_set_tunnel")
पूर्णांक _ip4ip6erspan_set_tunnel(काष्ठा __sk_buff *skb)
अणु
	काष्ठा bpf_tunnel_key key;
	काष्ठा erspan_metadata md;
	पूर्णांक ret;

	__builtin_स_रखो(&key, 0x0, माप(key));
	key.remote_ipv6[3] = bpf_htonl(0x11);
	key.tunnel_id = 2;
	key.tunnel_tos = 0;
	key.tunnel_ttl = 64;

	ret = bpf_skb_set_tunnel_key(skb, &key, माप(key),
				     BPF_F_TUNINFO_IPV6);
	अगर (ret < 0) अणु
		ERROR(ret);
		वापस TC_ACT_SHOT;
	पूर्ण

	__builtin_स_रखो(&md, 0, माप(md));

#अगर_घोषित ERSPAN_V1
	md.u.index = bpf_htonl(123);
	md.version = 1;
#अन्यथा
	__u8 direction = 0;
	__u8 hwid = 17;

	md.version = 2;
	md.u.md2.dir = direction;
	md.u.md2.hwid = hwid & 0xf;
	md.u.md2.hwid_upper = (hwid >> 4) & 0x3;
#पूर्ण_अगर

	ret = bpf_skb_set_tunnel_opt(skb, &md, माप(md));
	अगर (ret < 0) अणु
		ERROR(ret);
		वापस TC_ACT_SHOT;
	पूर्ण

	वापस TC_ACT_OK;
पूर्ण

SEC("ip4ip6erspan_get_tunnel")
पूर्णांक _ip4ip6erspan_get_tunnel(काष्ठा __sk_buff *skb)
अणु
	अक्षर fmt[] = "ip6erspan get key %d remote ip6 ::%x erspan version %d\n";
	काष्ठा bpf_tunnel_key key;
	काष्ठा erspan_metadata md;
	__u32 index;
	पूर्णांक ret;

	ret = bpf_skb_get_tunnel_key(skb, &key, माप(key),
				     BPF_F_TUNINFO_IPV6);
	अगर (ret < 0) अणु
		ERROR(ret);
		वापस TC_ACT_SHOT;
	पूर्ण

	ret = bpf_skb_get_tunnel_opt(skb, &md, माप(md));
	अगर (ret < 0) अणु
		ERROR(ret);
		वापस TC_ACT_SHOT;
	पूर्ण

	bpf_trace_prपूर्णांकk(fmt, माप(fmt),
			key.tunnel_id, key.remote_ipv4, md.version);

#अगर_घोषित ERSPAN_V1
	अक्षर fmt2[] = "\tindex %x\n";

	index = bpf_ntohl(md.u.index);
	bpf_trace_prपूर्णांकk(fmt2, माप(fmt2), index);
#अन्यथा
	अक्षर fmt2[] = "\tdirection %d hwid %x timestamp %u\n";

	bpf_trace_prपूर्णांकk(fmt2, माप(fmt2),
			 md.u.md2.dir,
			 (md.u.md2.hwid_upper << 4) + md.u.md2.hwid,
			 bpf_ntohl(md.u.md2.बारtamp));
#पूर्ण_अगर

	वापस TC_ACT_OK;
पूर्ण

SEC("vxlan_set_tunnel")
पूर्णांक _vxlan_set_tunnel(काष्ठा __sk_buff *skb)
अणु
	पूर्णांक ret;
	काष्ठा bpf_tunnel_key key;
	काष्ठा vxlan_metadata md;

	__builtin_स_रखो(&key, 0x0, माप(key));
	key.remote_ipv4 = 0xac100164; /* 172.16.1.100 */
	key.tunnel_id = 2;
	key.tunnel_tos = 0;
	key.tunnel_ttl = 64;

	ret = bpf_skb_set_tunnel_key(skb, &key, माप(key),
				     BPF_F_ZERO_CSUM_TX);
	अगर (ret < 0) अणु
		ERROR(ret);
		वापस TC_ACT_SHOT;
	पूर्ण

	md.gbp = 0x800FF; /* Set VXLAN Group Policy extension */
	ret = bpf_skb_set_tunnel_opt(skb, &md, माप(md));
	अगर (ret < 0) अणु
		ERROR(ret);
		वापस TC_ACT_SHOT;
	पूर्ण

	वापस TC_ACT_OK;
पूर्ण

SEC("vxlan_get_tunnel")
पूर्णांक _vxlan_get_tunnel(काष्ठा __sk_buff *skb)
अणु
	पूर्णांक ret;
	काष्ठा bpf_tunnel_key key;
	काष्ठा vxlan_metadata md;
	अक्षर fmt[] = "key %d remote ip 0x%x vxlan gbp 0x%x\n";

	ret = bpf_skb_get_tunnel_key(skb, &key, माप(key), 0);
	अगर (ret < 0) अणु
		ERROR(ret);
		वापस TC_ACT_SHOT;
	पूर्ण

	ret = bpf_skb_get_tunnel_opt(skb, &md, माप(md));
	अगर (ret < 0) अणु
		ERROR(ret);
		वापस TC_ACT_SHOT;
	पूर्ण

	bpf_trace_prपूर्णांकk(fmt, माप(fmt),
			key.tunnel_id, key.remote_ipv4, md.gbp);

	वापस TC_ACT_OK;
पूर्ण

SEC("ip6vxlan_set_tunnel")
पूर्णांक _ip6vxlan_set_tunnel(काष्ठा __sk_buff *skb)
अणु
	काष्ठा bpf_tunnel_key key;
	पूर्णांक ret;

	__builtin_स_रखो(&key, 0x0, माप(key));
	key.remote_ipv6[3] = bpf_htonl(0x11); /* ::11 */
	key.tunnel_id = 22;
	key.tunnel_tos = 0;
	key.tunnel_ttl = 64;

	ret = bpf_skb_set_tunnel_key(skb, &key, माप(key),
				     BPF_F_TUNINFO_IPV6);
	अगर (ret < 0) अणु
		ERROR(ret);
		वापस TC_ACT_SHOT;
	पूर्ण

	वापस TC_ACT_OK;
पूर्ण

SEC("ip6vxlan_get_tunnel")
पूर्णांक _ip6vxlan_get_tunnel(काष्ठा __sk_buff *skb)
अणु
	अक्षर fmt[] = "key %d remote ip6 ::%x label %x\n";
	काष्ठा bpf_tunnel_key key;
	पूर्णांक ret;

	ret = bpf_skb_get_tunnel_key(skb, &key, माप(key),
				     BPF_F_TUNINFO_IPV6);
	अगर (ret < 0) अणु
		ERROR(ret);
		वापस TC_ACT_SHOT;
	पूर्ण

	bpf_trace_prपूर्णांकk(fmt, माप(fmt),
			 key.tunnel_id, key.remote_ipv6[3], key.tunnel_label);

	वापस TC_ACT_OK;
पूर्ण

SEC("geneve_set_tunnel")
पूर्णांक _geneve_set_tunnel(काष्ठा __sk_buff *skb)
अणु
	पूर्णांक ret;
	काष्ठा bpf_tunnel_key key;
	काष्ठा geneve_opt gopt;

	__builtin_स_रखो(&key, 0x0, माप(key));
	key.remote_ipv4 = 0xac100164; /* 172.16.1.100 */
	key.tunnel_id = 2;
	key.tunnel_tos = 0;
	key.tunnel_ttl = 64;

	__builtin_स_रखो(&gopt, 0x0, माप(gopt));
	gopt.opt_class = bpf_htons(0x102); /* Open Virtual Networking (OVN) */
	gopt.type = 0x08;
	gopt.r1 = 0;
	gopt.r2 = 0;
	gopt.r3 = 0;
	gopt.length = 2; /* 4-byte multiple */
	*(पूर्णांक *) &gopt.opt_data = bpf_htonl(0xdeadbeef);

	ret = bpf_skb_set_tunnel_key(skb, &key, माप(key),
				     BPF_F_ZERO_CSUM_TX);
	अगर (ret < 0) अणु
		ERROR(ret);
		वापस TC_ACT_SHOT;
	पूर्ण

	ret = bpf_skb_set_tunnel_opt(skb, &gopt, माप(gopt));
	अगर (ret < 0) अणु
		ERROR(ret);
		वापस TC_ACT_SHOT;
	पूर्ण

	वापस TC_ACT_OK;
पूर्ण

SEC("geneve_get_tunnel")
पूर्णांक _geneve_get_tunnel(काष्ठा __sk_buff *skb)
अणु
	पूर्णांक ret;
	काष्ठा bpf_tunnel_key key;
	काष्ठा geneve_opt gopt;
	अक्षर fmt[] = "key %d remote ip 0x%x geneve class 0x%x\n";

	ret = bpf_skb_get_tunnel_key(skb, &key, माप(key), 0);
	अगर (ret < 0) अणु
		ERROR(ret);
		वापस TC_ACT_SHOT;
	पूर्ण

	ret = bpf_skb_get_tunnel_opt(skb, &gopt, माप(gopt));
	अगर (ret < 0)
		gopt.opt_class = 0;

	bpf_trace_prपूर्णांकk(fmt, माप(fmt),
			key.tunnel_id, key.remote_ipv4, gopt.opt_class);
	वापस TC_ACT_OK;
पूर्ण

SEC("ip6geneve_set_tunnel")
पूर्णांक _ip6geneve_set_tunnel(काष्ठा __sk_buff *skb)
अणु
	काष्ठा bpf_tunnel_key key;
	काष्ठा geneve_opt gopt;
	पूर्णांक ret;

	__builtin_स_रखो(&key, 0x0, माप(key));
	key.remote_ipv6[3] = bpf_htonl(0x11); /* ::11 */
	key.tunnel_id = 22;
	key.tunnel_tos = 0;
	key.tunnel_ttl = 64;

	ret = bpf_skb_set_tunnel_key(skb, &key, माप(key),
				     BPF_F_TUNINFO_IPV6);
	अगर (ret < 0) अणु
		ERROR(ret);
		वापस TC_ACT_SHOT;
	पूर्ण

	__builtin_स_रखो(&gopt, 0x0, माप(gopt));
	gopt.opt_class = bpf_htons(0x102); /* Open Virtual Networking (OVN) */
	gopt.type = 0x08;
	gopt.r1 = 0;
	gopt.r2 = 0;
	gopt.r3 = 0;
	gopt.length = 2; /* 4-byte multiple */
	*(पूर्णांक *) &gopt.opt_data = bpf_htonl(0xfeedbeef);

	ret = bpf_skb_set_tunnel_opt(skb, &gopt, माप(gopt));
	अगर (ret < 0) अणु
		ERROR(ret);
		वापस TC_ACT_SHOT;
	पूर्ण

	वापस TC_ACT_OK;
पूर्ण

SEC("ip6geneve_get_tunnel")
पूर्णांक _ip6geneve_get_tunnel(काष्ठा __sk_buff *skb)
अणु
	अक्षर fmt[] = "key %d remote ip 0x%x geneve class 0x%x\n";
	काष्ठा bpf_tunnel_key key;
	काष्ठा geneve_opt gopt;
	पूर्णांक ret;

	ret = bpf_skb_get_tunnel_key(skb, &key, माप(key),
				     BPF_F_TUNINFO_IPV6);
	अगर (ret < 0) अणु
		ERROR(ret);
		वापस TC_ACT_SHOT;
	पूर्ण

	ret = bpf_skb_get_tunnel_opt(skb, &gopt, माप(gopt));
	अगर (ret < 0)
		gopt.opt_class = 0;

	bpf_trace_prपूर्णांकk(fmt, माप(fmt),
			key.tunnel_id, key.remote_ipv4, gopt.opt_class);

	वापस TC_ACT_OK;
पूर्ण

SEC("ipip_set_tunnel")
पूर्णांक _ipip_set_tunnel(काष्ठा __sk_buff *skb)
अणु
	काष्ठा bpf_tunnel_key key = अणुपूर्ण;
	व्योम *data = (व्योम *)(दीर्घ)skb->data;
	काष्ठा iphdr *iph = data;
	व्योम *data_end = (व्योम *)(दीर्घ)skb->data_end;
	पूर्णांक ret;

	/* single length check */
	अगर (data + माप(*iph) > data_end) अणु
		ERROR(1);
		वापस TC_ACT_SHOT;
	पूर्ण

	key.tunnel_ttl = 64;
	अगर (iph->protocol == IPPROTO_ICMP) अणु
		key.remote_ipv4 = 0xac100164; /* 172.16.1.100 */
	पूर्ण

	ret = bpf_skb_set_tunnel_key(skb, &key, माप(key), 0);
	अगर (ret < 0) अणु
		ERROR(ret);
		वापस TC_ACT_SHOT;
	पूर्ण

	वापस TC_ACT_OK;
पूर्ण

SEC("ipip_get_tunnel")
पूर्णांक _ipip_get_tunnel(काष्ठा __sk_buff *skb)
अणु
	पूर्णांक ret;
	काष्ठा bpf_tunnel_key key;
	अक्षर fmt[] = "remote ip 0x%x\n";

	ret = bpf_skb_get_tunnel_key(skb, &key, माप(key), 0);
	अगर (ret < 0) अणु
		ERROR(ret);
		वापस TC_ACT_SHOT;
	पूर्ण

	bpf_trace_prपूर्णांकk(fmt, माप(fmt), key.remote_ipv4);
	वापस TC_ACT_OK;
पूर्ण

SEC("ipip6_set_tunnel")
पूर्णांक _ipip6_set_tunnel(काष्ठा __sk_buff *skb)
अणु
	काष्ठा bpf_tunnel_key key = अणुपूर्ण;
	व्योम *data = (व्योम *)(दीर्घ)skb->data;
	काष्ठा iphdr *iph = data;
	व्योम *data_end = (व्योम *)(दीर्घ)skb->data_end;
	पूर्णांक ret;

	/* single length check */
	अगर (data + माप(*iph) > data_end) अणु
		ERROR(1);
		वापस TC_ACT_SHOT;
	पूर्ण

	__builtin_स_रखो(&key, 0x0, माप(key));
	key.tunnel_ttl = 64;
	अगर (iph->protocol == IPPROTO_ICMP) अणु
		key.remote_ipv6[3] = bpf_htonl(0x11); /* ::11 */
	पूर्ण

	ret = bpf_skb_set_tunnel_key(skb, &key, माप(key),
				     BPF_F_TUNINFO_IPV6);
	अगर (ret < 0) अणु
		ERROR(ret);
		वापस TC_ACT_SHOT;
	पूर्ण

	वापस TC_ACT_OK;
पूर्ण

SEC("ipip6_get_tunnel")
पूर्णांक _ipip6_get_tunnel(काष्ठा __sk_buff *skb)
अणु
	पूर्णांक ret;
	काष्ठा bpf_tunnel_key key;
	अक्षर fmt[] = "remote ip6 %x::%x\n";

	ret = bpf_skb_get_tunnel_key(skb, &key, माप(key),
				     BPF_F_TUNINFO_IPV6);
	अगर (ret < 0) अणु
		ERROR(ret);
		वापस TC_ACT_SHOT;
	पूर्ण

	bpf_trace_prपूर्णांकk(fmt, माप(fmt), bpf_htonl(key.remote_ipv6[0]),
			 bpf_htonl(key.remote_ipv6[3]));
	वापस TC_ACT_OK;
पूर्ण

SEC("ip6ip6_set_tunnel")
पूर्णांक _ip6ip6_set_tunnel(काष्ठा __sk_buff *skb)
अणु
	काष्ठा bpf_tunnel_key key = अणुपूर्ण;
	व्योम *data = (व्योम *)(दीर्घ)skb->data;
	काष्ठा ipv6hdr *iph = data;
	व्योम *data_end = (व्योम *)(दीर्घ)skb->data_end;
	पूर्णांक ret;

	/* single length check */
	अगर (data + माप(*iph) > data_end) अणु
		ERROR(1);
		वापस TC_ACT_SHOT;
	पूर्ण

	key.tunnel_ttl = 64;
	अगर (iph->nexthdr == 58 /* NEXTHDR_ICMP */) अणु
		key.remote_ipv6[3] = bpf_htonl(0x11); /* ::11 */
	पूर्ण

	ret = bpf_skb_set_tunnel_key(skb, &key, माप(key),
				     BPF_F_TUNINFO_IPV6);
	अगर (ret < 0) अणु
		ERROR(ret);
		वापस TC_ACT_SHOT;
	पूर्ण

	वापस TC_ACT_OK;
पूर्ण

SEC("ip6ip6_get_tunnel")
पूर्णांक _ip6ip6_get_tunnel(काष्ठा __sk_buff *skb)
अणु
	पूर्णांक ret;
	काष्ठा bpf_tunnel_key key;
	अक्षर fmt[] = "remote ip6 %x::%x\n";

	ret = bpf_skb_get_tunnel_key(skb, &key, माप(key),
				     BPF_F_TUNINFO_IPV6);
	अगर (ret < 0) अणु
		ERROR(ret);
		वापस TC_ACT_SHOT;
	पूर्ण

	bpf_trace_prपूर्णांकk(fmt, माप(fmt), bpf_htonl(key.remote_ipv6[0]),
			 bpf_htonl(key.remote_ipv6[3]));
	वापस TC_ACT_OK;
पूर्ण

SEC("xfrm_get_state")
पूर्णांक _xfrm_get_state(काष्ठा __sk_buff *skb)
अणु
	काष्ठा bpf_xfrm_state x;
	अक्षर fmt[] = "reqid %d spi 0x%x remote ip 0x%x\n";
	पूर्णांक ret;

	ret = bpf_skb_get_xfrm_state(skb, 0, &x, माप(x), 0);
	अगर (ret < 0)
		वापस TC_ACT_OK;

	bpf_trace_prपूर्णांकk(fmt, माप(fmt), x.reqid, bpf_ntohl(x.spi),
			 bpf_ntohl(x.remote_ipv4));
	वापस TC_ACT_OK;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
