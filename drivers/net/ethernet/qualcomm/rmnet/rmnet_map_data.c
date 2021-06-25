<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2013-2018, The Linux Foundation. All rights reserved.
 *
 * RMNET Data MAP protocol
 */

#समावेश <linux/netdevice.h>
#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <net/ip6_checksum.h>
#समावेश "rmnet_config.h"
#समावेश "rmnet_map.h"
#समावेश "rmnet_private.h"

#घोषणा RMNET_MAP_DEAGGR_SPACING  64
#घोषणा RMNET_MAP_DEAGGR_HEADROOM (RMNET_MAP_DEAGGR_SPACING / 2)

अटल __sum16 *rmnet_map_get_csum_field(अचिन्हित अक्षर protocol,
					 स्थिर व्योम *txporthdr)
अणु
	__sum16 *check = शून्य;

	चयन (protocol) अणु
	हाल IPPROTO_TCP:
		check = &(((काष्ठा tcphdr *)txporthdr)->check);
		अवरोध;

	हाल IPPROTO_UDP:
		check = &(((काष्ठा udphdr *)txporthdr)->check);
		अवरोध;

	शेष:
		check = शून्य;
		अवरोध;
	पूर्ण

	वापस check;
पूर्ण

अटल पूर्णांक
rmnet_map_ipv4_dl_csum_trailer(काष्ठा sk_buff *skb,
			       काष्ठा rmnet_map_dl_csum_trailer *csum_trailer,
			       काष्ठा rmnet_priv *priv)
अणु
	__sum16 *csum_field, csum_temp, pseuकरो_csum, hdr_csum, ip_payload_csum;
	u16 csum_value, csum_value_final;
	काष्ठा iphdr *ip4h;
	व्योम *txporthdr;
	__be16 addend;

	ip4h = (काष्ठा iphdr *)(skb->data);
	अगर ((ntohs(ip4h->frag_off) & IP_MF) ||
	    ((ntohs(ip4h->frag_off) & IP_OFFSET) > 0)) अणु
		priv->stats.csum_fragmented_pkt++;
		वापस -EOPNOTSUPP;
	पूर्ण

	txporthdr = skb->data + ip4h->ihl * 4;

	csum_field = rmnet_map_get_csum_field(ip4h->protocol, txporthdr);

	अगर (!csum_field) अणु
		priv->stats.csum_err_invalid_transport++;
		वापस -EPROTONOSUPPORT;
	पूर्ण

	/* RFC 768 - Skip IPv4 UDP packets where sender checksum field is 0 */
	अगर (*csum_field == 0 && ip4h->protocol == IPPROTO_UDP) अणु
		priv->stats.csum_skipped++;
		वापस 0;
	पूर्ण

	csum_value = ~ntohs(csum_trailer->csum_value);
	hdr_csum = ~ip_fast_csum(ip4h, (पूर्णांक)ip4h->ihl);
	ip_payload_csum = csum16_sub((__क्रमce __sum16)csum_value,
				     (__क्रमce __be16)hdr_csum);

	pseuकरो_csum = ~csum_tcpudp_magic(ip4h->saddr, ip4h->daddr,
					 ntohs(ip4h->tot_len) - ip4h->ihl * 4,
					 ip4h->protocol, 0);
	addend = (__क्रमce __be16)ntohs((__क्रमce __be16)pseuकरो_csum);
	pseuकरो_csum = csum16_add(ip_payload_csum, addend);

	addend = (__क्रमce __be16)ntohs((__क्रमce __be16)*csum_field);
	csum_temp = ~csum16_sub(pseuकरो_csum, addend);
	csum_value_final = (__क्रमce u16)csum_temp;

	अगर (unlikely(csum_value_final == 0)) अणु
		चयन (ip4h->protocol) अणु
		हाल IPPROTO_UDP:
			/* RFC 768 - DL4 1's complement rule क्रम UDP csum 0 */
			csum_value_final = ~csum_value_final;
			अवरोध;

		हाल IPPROTO_TCP:
			/* DL4 Non-RFC compliant TCP checksum found */
			अगर (*csum_field == (__क्रमce __sum16)0xFFFF)
				csum_value_final = ~csum_value_final;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (csum_value_final == ntohs((__क्रमce __be16)*csum_field)) अणु
		priv->stats.csum_ok++;
		वापस 0;
	पूर्ण अन्यथा अणु
		priv->stats.csum_validation_failed++;
		वापस -EINVAL;
	पूर्ण
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
अटल पूर्णांक
rmnet_map_ipv6_dl_csum_trailer(काष्ठा sk_buff *skb,
			       काष्ठा rmnet_map_dl_csum_trailer *csum_trailer,
			       काष्ठा rmnet_priv *priv)
अणु
	__sum16 *csum_field, ip6_payload_csum, pseuकरो_csum, csum_temp;
	u16 csum_value, csum_value_final;
	__be16 ip6_hdr_csum, addend;
	काष्ठा ipv6hdr *ip6h;
	व्योम *txporthdr;
	u32 length;

	ip6h = (काष्ठा ipv6hdr *)(skb->data);

	txporthdr = skb->data + माप(काष्ठा ipv6hdr);
	csum_field = rmnet_map_get_csum_field(ip6h->nexthdr, txporthdr);

	अगर (!csum_field) अणु
		priv->stats.csum_err_invalid_transport++;
		वापस -EPROTONOSUPPORT;
	पूर्ण

	csum_value = ~ntohs(csum_trailer->csum_value);
	ip6_hdr_csum = (__क्रमce __be16)
			~ntohs((__क्रमce __be16)ip_compute_csum(ip6h,
			       (पूर्णांक)(txporthdr - (व्योम *)(skb->data))));
	ip6_payload_csum = csum16_sub((__क्रमce __sum16)csum_value,
				      ip6_hdr_csum);

	length = (ip6h->nexthdr == IPPROTO_UDP) ?
		 ntohs(((काष्ठा udphdr *)txporthdr)->len) :
		 ntohs(ip6h->payload_len);
	pseuकरो_csum = ~(csum_ipv6_magic(&ip6h->saddr, &ip6h->daddr,
			     length, ip6h->nexthdr, 0));
	addend = (__क्रमce __be16)ntohs((__क्रमce __be16)pseuकरो_csum);
	pseuकरो_csum = csum16_add(ip6_payload_csum, addend);

	addend = (__क्रमce __be16)ntohs((__क्रमce __be16)*csum_field);
	csum_temp = ~csum16_sub(pseuकरो_csum, addend);
	csum_value_final = (__क्रमce u16)csum_temp;

	अगर (unlikely(csum_value_final == 0)) अणु
		चयन (ip6h->nexthdr) अणु
		हाल IPPROTO_UDP:
			/* RFC 2460 section 8.1
			 * DL6 One's complement rule क्रम UDP checksum 0
			 */
			csum_value_final = ~csum_value_final;
			अवरोध;

		हाल IPPROTO_TCP:
			/* DL6 Non-RFC compliant TCP checksum found */
			अगर (*csum_field == (__क्रमce __sum16)0xFFFF)
				csum_value_final = ~csum_value_final;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (csum_value_final == ntohs((__क्रमce __be16)*csum_field)) अणु
		priv->stats.csum_ok++;
		वापस 0;
	पूर्ण अन्यथा अणु
		priv->stats.csum_validation_failed++;
		वापस -EINVAL;
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल व्योम rmnet_map_complement_ipv4_txporthdr_csum_field(व्योम *iphdr)
अणु
	काष्ठा iphdr *ip4h = (काष्ठा iphdr *)iphdr;
	व्योम *txphdr;
	u16 *csum;

	txphdr = iphdr + ip4h->ihl * 4;

	अगर (ip4h->protocol == IPPROTO_TCP || ip4h->protocol == IPPROTO_UDP) अणु
		csum = (u16 *)rmnet_map_get_csum_field(ip4h->protocol, txphdr);
		*csum = ~(*csum);
	पूर्ण
पूर्ण

अटल व्योम
rmnet_map_ipv4_ul_csum_header(व्योम *iphdr,
			      काष्ठा rmnet_map_ul_csum_header *ul_header,
			      काष्ठा sk_buff *skb)
अणु
	काष्ठा iphdr *ip4h = iphdr;
	u16 val;

	val = MAP_CSUM_UL_ENABLED_FLAG;
	अगर (ip4h->protocol == IPPROTO_UDP)
		val |= MAP_CSUM_UL_UDP_FLAG;
	val |= skb->csum_offset & MAP_CSUM_UL_OFFSET_MASK;

	ul_header->csum_start_offset = htons(skb_network_header_len(skb));
	ul_header->csum_info = htons(val);

	skb->ip_summed = CHECKSUM_NONE;

	rmnet_map_complement_ipv4_txporthdr_csum_field(iphdr);
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
अटल व्योम rmnet_map_complement_ipv6_txporthdr_csum_field(व्योम *ip6hdr)
अणु
	काष्ठा ipv6hdr *ip6h = (काष्ठा ipv6hdr *)ip6hdr;
	व्योम *txphdr;
	u16 *csum;

	txphdr = ip6hdr + माप(काष्ठा ipv6hdr);

	अगर (ip6h->nexthdr == IPPROTO_TCP || ip6h->nexthdr == IPPROTO_UDP) अणु
		csum = (u16 *)rmnet_map_get_csum_field(ip6h->nexthdr, txphdr);
		*csum = ~(*csum);
	पूर्ण
पूर्ण

अटल व्योम
rmnet_map_ipv6_ul_csum_header(व्योम *ip6hdr,
			      काष्ठा rmnet_map_ul_csum_header *ul_header,
			      काष्ठा sk_buff *skb)
अणु
	काष्ठा ipv6hdr *ip6h = ip6hdr;
	u16 val;

	val = MAP_CSUM_UL_ENABLED_FLAG;
	अगर (ip6h->nexthdr == IPPROTO_UDP)
		val |= MAP_CSUM_UL_UDP_FLAG;
	val |= skb->csum_offset & MAP_CSUM_UL_OFFSET_MASK;

	ul_header->csum_start_offset = htons(skb_network_header_len(skb));
	ul_header->csum_info = htons(val);

	skb->ip_summed = CHECKSUM_NONE;

	rmnet_map_complement_ipv6_txporthdr_csum_field(ip6hdr);
पूर्ण
#पूर्ण_अगर

/* Adds MAP header to front of skb->data
 * Padding is calculated and set appropriately in MAP header. Mux ID is
 * initialized to 0.
 */
काष्ठा rmnet_map_header *rmnet_map_add_map_header(काष्ठा sk_buff *skb,
						  पूर्णांक hdrlen, पूर्णांक pad)
अणु
	काष्ठा rmnet_map_header *map_header;
	u32 padding, map_datalen;
	u8 *padbytes;

	map_datalen = skb->len - hdrlen;
	map_header = (काष्ठा rmnet_map_header *)
			skb_push(skb, माप(काष्ठा rmnet_map_header));
	स_रखो(map_header, 0, माप(काष्ठा rmnet_map_header));

	अगर (pad == RMNET_MAP_NO_PAD_BYTES) अणु
		map_header->pkt_len = htons(map_datalen);
		वापस map_header;
	पूर्ण

	BUILD_BUG_ON(MAP_PAD_LEN_MASK < 3);
	padding = ALIGN(map_datalen, 4) - map_datalen;

	अगर (padding == 0)
		जाओ करोne;

	अगर (skb_tailroom(skb) < padding)
		वापस शून्य;

	padbytes = (u8 *)skb_put(skb, padding);
	स_रखो(padbytes, 0, padding);

करोne:
	map_header->pkt_len = htons(map_datalen + padding);
	/* This is a data packet, so the CMD bit is 0 */
	map_header->flags = padding & MAP_PAD_LEN_MASK;

	वापस map_header;
पूर्ण

/* Deaggregates a single packet
 * A whole new buffer is allocated क्रम each portion of an aggregated frame.
 * Caller should keep calling deaggregate() on the source skb until 0 is
 * वापसed, indicating that there are no more packets to deaggregate. Caller
 * is responsible क्रम मुक्तing the original skb.
 */
काष्ठा sk_buff *rmnet_map_deaggregate(काष्ठा sk_buff *skb,
				      काष्ठा rmnet_port *port)
अणु
	काष्ठा rmnet_map_header *maph;
	काष्ठा sk_buff *skbn;
	u32 packet_len;

	अगर (skb->len == 0)
		वापस शून्य;

	maph = (काष्ठा rmnet_map_header *)skb->data;
	packet_len = ntohs(maph->pkt_len) + माप(*maph);

	अगर (port->data_क्रमmat & RMNET_FLAGS_INGRESS_MAP_CKSUMV4)
		packet_len += माप(काष्ठा rmnet_map_dl_csum_trailer);

	अगर (((पूर्णांक)skb->len - (पूर्णांक)packet_len) < 0)
		वापस शून्य;

	/* Some hardware can send us empty frames. Catch them */
	अगर (!maph->pkt_len)
		वापस शून्य;

	skbn = alloc_skb(packet_len + RMNET_MAP_DEAGGR_SPACING, GFP_ATOMIC);
	अगर (!skbn)
		वापस शून्य;

	skb_reserve(skbn, RMNET_MAP_DEAGGR_HEADROOM);
	skb_put(skbn, packet_len);
	स_नकल(skbn->data, skb->data, packet_len);
	skb_pull(skb, packet_len);

	वापस skbn;
पूर्ण

/* Validates packet checksums. Function takes a poपूर्णांकer to
 * the beginning of a buffer which contains the IP payload +
 * padding + checksum trailer.
 * Only IPv4 and IPv6 are supported aदीर्घ with TCP & UDP.
 * Fragmented or tunneled packets are not supported.
 */
पूर्णांक rmnet_map_checksum_करोwnlink_packet(काष्ठा sk_buff *skb, u16 len)
अणु
	काष्ठा rmnet_priv *priv = netdev_priv(skb->dev);
	काष्ठा rmnet_map_dl_csum_trailer *csum_trailer;

	अगर (unlikely(!(skb->dev->features & NETIF_F_RXCSUM))) अणु
		priv->stats.csum_sw++;
		वापस -EOPNOTSUPP;
	पूर्ण

	csum_trailer = (काष्ठा rmnet_map_dl_csum_trailer *)(skb->data + len);

	अगर (!(csum_trailer->flags & MAP_CSUM_DL_VALID_FLAG)) अणु
		priv->stats.csum_valid_unset++;
		वापस -EINVAL;
	पूर्ण

	अगर (skb->protocol == htons(ETH_P_IP)) अणु
		वापस rmnet_map_ipv4_dl_csum_trailer(skb, csum_trailer, priv);
	पूर्ण अन्यथा अगर (skb->protocol == htons(ETH_P_IPV6)) अणु
#अगर IS_ENABLED(CONFIG_IPV6)
		वापस rmnet_map_ipv6_dl_csum_trailer(skb, csum_trailer, priv);
#अन्यथा
		priv->stats.csum_err_invalid_ip_version++;
		वापस -EPROTONOSUPPORT;
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		priv->stats.csum_err_invalid_ip_version++;
		वापस -EPROTONOSUPPORT;
	पूर्ण

	वापस 0;
पूर्ण

/* Generates UL checksum meta info header क्रम IPv4 and IPv6 over TCP and UDP
 * packets that are supported क्रम UL checksum offload.
 */
व्योम rmnet_map_checksum_uplink_packet(काष्ठा sk_buff *skb,
				      काष्ठा net_device *orig_dev)
अणु
	काष्ठा rmnet_priv *priv = netdev_priv(orig_dev);
	काष्ठा rmnet_map_ul_csum_header *ul_header;
	व्योम *iphdr;

	ul_header = (काष्ठा rmnet_map_ul_csum_header *)
		    skb_push(skb, माप(काष्ठा rmnet_map_ul_csum_header));

	अगर (unlikely(!(orig_dev->features &
		     (NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM))))
		जाओ sw_csum;

	अगर (skb->ip_summed == CHECKSUM_PARTIAL) अणु
		iphdr = (अक्षर *)ul_header +
			माप(काष्ठा rmnet_map_ul_csum_header);

		अगर (skb->protocol == htons(ETH_P_IP)) अणु
			rmnet_map_ipv4_ul_csum_header(iphdr, ul_header, skb);
			वापस;
		पूर्ण अन्यथा अगर (skb->protocol == htons(ETH_P_IPV6)) अणु
#अगर IS_ENABLED(CONFIG_IPV6)
			rmnet_map_ipv6_ul_csum_header(iphdr, ul_header, skb);
			वापस;
#अन्यथा
			priv->stats.csum_err_invalid_ip_version++;
			जाओ sw_csum;
#पूर्ण_अगर
		पूर्ण अन्यथा अणु
			priv->stats.csum_err_invalid_ip_version++;
		पूर्ण
	पूर्ण

sw_csum:
	स_रखो(ul_header, 0, माप(*ul_header));

	priv->stats.csum_sw++;
पूर्ण
