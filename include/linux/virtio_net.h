<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_VIRTIO_NET_H
#घोषणा _LINUX_VIRTIO_NET_H

#समावेश <linux/अगर_vlan.h>
#समावेश <uapi/linux/tcp.h>
#समावेश <uapi/linux/udp.h>
#समावेश <uapi/linux/virtio_net.h>

अटल अंतरभूत पूर्णांक virtio_net_hdr_set_proto(काष्ठा sk_buff *skb,
					   स्थिर काष्ठा virtio_net_hdr *hdr)
अणु
	चयन (hdr->gso_type & ~VIRTIO_NET_HDR_GSO_ECN) अणु
	हाल VIRTIO_NET_HDR_GSO_TCPV4:
	हाल VIRTIO_NET_HDR_GSO_UDP:
		skb->protocol = cpu_to_be16(ETH_P_IP);
		अवरोध;
	हाल VIRTIO_NET_HDR_GSO_TCPV6:
		skb->protocol = cpu_to_be16(ETH_P_IPV6);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक virtio_net_hdr_to_skb(काष्ठा sk_buff *skb,
					स्थिर काष्ठा virtio_net_hdr *hdr,
					bool little_endian)
अणु
	अचिन्हित पूर्णांक gso_type = 0;
	अचिन्हित पूर्णांक thlen = 0;
	अचिन्हित पूर्णांक p_off = 0;
	अचिन्हित पूर्णांक ip_proto;

	अगर (hdr->gso_type != VIRTIO_NET_HDR_GSO_NONE) अणु
		चयन (hdr->gso_type & ~VIRTIO_NET_HDR_GSO_ECN) अणु
		हाल VIRTIO_NET_HDR_GSO_TCPV4:
			gso_type = SKB_GSO_TCPV4;
			ip_proto = IPPROTO_TCP;
			thlen = माप(काष्ठा tcphdr);
			अवरोध;
		हाल VIRTIO_NET_HDR_GSO_TCPV6:
			gso_type = SKB_GSO_TCPV6;
			ip_proto = IPPROTO_TCP;
			thlen = माप(काष्ठा tcphdr);
			अवरोध;
		हाल VIRTIO_NET_HDR_GSO_UDP:
			gso_type = SKB_GSO_UDP;
			ip_proto = IPPROTO_UDP;
			thlen = माप(काष्ठा udphdr);
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		अगर (hdr->gso_type & VIRTIO_NET_HDR_GSO_ECN)
			gso_type |= SKB_GSO_TCP_ECN;

		अगर (hdr->gso_size == 0)
			वापस -EINVAL;
	पूर्ण

	skb_reset_mac_header(skb);

	अगर (hdr->flags & VIRTIO_NET_HDR_F_NEEDS_CSUM) अणु
		u32 start = __virtio16_to_cpu(little_endian, hdr->csum_start);
		u32 off = __virtio16_to_cpu(little_endian, hdr->csum_offset);
		u32 needed = start + max_t(u32, thlen, off + माप(__sum16));

		अगर (!pskb_may_pull(skb, needed))
			वापस -EINVAL;

		अगर (!skb_partial_csum_set(skb, start, off))
			वापस -EINVAL;

		p_off = skb_transport_offset(skb) + thlen;
		अगर (!pskb_may_pull(skb, p_off))
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		/* gso packets without NEEDS_CSUM करो not set transport_offset.
		 * probe and drop अगर करोes not match one of the above types.
		 */
		अगर (gso_type && skb->network_header) अणु
			काष्ठा flow_keys_basic keys;

			अगर (!skb->protocol) अणु
				__be16 protocol = dev_parse_header_protocol(skb);

				virtio_net_hdr_set_proto(skb, hdr);
				अगर (protocol && protocol != skb->protocol)
					वापस -EINVAL;
			पूर्ण
retry:
			अगर (!skb_flow_dissect_flow_keys_basic(शून्य, skb, &keys,
							      शून्य, 0, 0, 0,
							      0)) अणु
				/* UFO करोes not specअगरy ipv4 or 6: try both */
				अगर (gso_type & SKB_GSO_UDP &&
				    skb->protocol == htons(ETH_P_IP)) अणु
					skb->protocol = htons(ETH_P_IPV6);
					जाओ retry;
				पूर्ण
				वापस -EINVAL;
			पूर्ण

			p_off = keys.control.thoff + thlen;
			अगर (!pskb_may_pull(skb, p_off) ||
			    keys.basic.ip_proto != ip_proto)
				वापस -EINVAL;

			skb_set_transport_header(skb, keys.control.thoff);
		पूर्ण अन्यथा अगर (gso_type) अणु
			p_off = thlen;
			अगर (!pskb_may_pull(skb, p_off))
				वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (hdr->gso_type != VIRTIO_NET_HDR_GSO_NONE) अणु
		u16 gso_size = __virtio16_to_cpu(little_endian, hdr->gso_size);
		काष्ठा skb_shared_info *shinfo = skb_shinfo(skb);

		/* Too small packets are not really GSO ones. */
		अगर (skb->len - p_off > gso_size) अणु
			shinfo->gso_size = gso_size;
			shinfo->gso_type = gso_type;

			/* Header must be checked, and gso_segs computed. */
			shinfo->gso_type |= SKB_GSO_DODGY;
			shinfo->gso_segs = 0;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक virtio_net_hdr_from_skb(स्थिर काष्ठा sk_buff *skb,
					  काष्ठा virtio_net_hdr *hdr,
					  bool little_endian,
					  bool has_data_valid,
					  पूर्णांक vlan_hlen)
अणु
	स_रखो(hdr, 0, माप(*hdr));   /* no info leak */

	अगर (skb_is_gso(skb)) अणु
		काष्ठा skb_shared_info *sinfo = skb_shinfo(skb);

		/* This is a hपूर्णांक as to how much should be linear. */
		hdr->hdr_len = __cpu_to_virtio16(little_endian,
						 skb_headlen(skb));
		hdr->gso_size = __cpu_to_virtio16(little_endian,
						  sinfo->gso_size);
		अगर (sinfo->gso_type & SKB_GSO_TCPV4)
			hdr->gso_type = VIRTIO_NET_HDR_GSO_TCPV4;
		अन्यथा अगर (sinfo->gso_type & SKB_GSO_TCPV6)
			hdr->gso_type = VIRTIO_NET_HDR_GSO_TCPV6;
		अन्यथा
			वापस -EINVAL;
		अगर (sinfo->gso_type & SKB_GSO_TCP_ECN)
			hdr->gso_type |= VIRTIO_NET_HDR_GSO_ECN;
	पूर्ण अन्यथा
		hdr->gso_type = VIRTIO_NET_HDR_GSO_NONE;

	अगर (skb->ip_summed == CHECKSUM_PARTIAL) अणु
		hdr->flags = VIRTIO_NET_HDR_F_NEEDS_CSUM;
		hdr->csum_start = __cpu_to_virtio16(little_endian,
			skb_checksum_start_offset(skb) + vlan_hlen);
		hdr->csum_offset = __cpu_to_virtio16(little_endian,
				skb->csum_offset);
	पूर्ण अन्यथा अगर (has_data_valid &&
		   skb->ip_summed == CHECKSUM_UNNECESSARY) अणु
		hdr->flags = VIRTIO_NET_HDR_F_DATA_VALID;
	पूर्ण /* अन्यथा everything is zero */

	वापस 0;
पूर्ण

#पूर्ण_अगर /* _LINUX_VIRTIO_NET_H */
