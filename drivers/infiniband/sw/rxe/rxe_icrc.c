<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/*
 * Copyright (c) 2016 Mellanox Technologies Ltd. All rights reserved.
 * Copyright (c) 2015 System Fabric Works, Inc. All rights reserved.
 */

#समावेश "rxe.h"
#समावेश "rxe_loc.h"

/* Compute a partial ICRC क्रम all the IB transport headers. */
u32 rxe_icrc_hdr(काष्ठा rxe_pkt_info *pkt, काष्ठा sk_buff *skb)
अणु
	अचिन्हित पूर्णांक bth_offset = 0;
	काष्ठा iphdr *ip4h = शून्य;
	काष्ठा ipv6hdr *ip6h = शून्य;
	काष्ठा udphdr *udph;
	काष्ठा rxe_bth *bth;
	पूर्णांक crc;
	पूर्णांक length;
	पूर्णांक hdr_size = माप(काष्ठा udphdr) +
		(skb->protocol == htons(ETH_P_IP) ?
		माप(काष्ठा iphdr) : माप(काष्ठा ipv6hdr));
	/* pseuकरो header buffer size is calculate using ipv6 header size since
	 * it is bigger than ipv4
	 */
	u8 pshdr[माप(काष्ठा udphdr) +
		माप(काष्ठा ipv6hdr) +
		RXE_BTH_BYTES];

	/* This seed is the result of computing a CRC with a seed of
	 * 0xfffffff and 8 bytes of 0xff representing a masked LRH.
	 */
	crc = 0xdebb20e3;

	अगर (skb->protocol == htons(ETH_P_IP)) अणु /* IPv4 */
		स_नकल(pshdr, ip_hdr(skb), hdr_size);
		ip4h = (काष्ठा iphdr *)pshdr;
		udph = (काष्ठा udphdr *)(ip4h + 1);

		ip4h->ttl = 0xff;
		ip4h->check = CSUM_MANGLED_0;
		ip4h->tos = 0xff;
	पूर्ण अन्यथा अणु				/* IPv6 */
		स_नकल(pshdr, ipv6_hdr(skb), hdr_size);
		ip6h = (काष्ठा ipv6hdr *)pshdr;
		udph = (काष्ठा udphdr *)(ip6h + 1);

		स_रखो(ip6h->flow_lbl, 0xff, माप(ip6h->flow_lbl));
		ip6h->priority = 0xf;
		ip6h->hop_limit = 0xff;
	पूर्ण
	udph->check = CSUM_MANGLED_0;

	bth_offset += hdr_size;

	स_नकल(&pshdr[bth_offset], pkt->hdr, RXE_BTH_BYTES);
	bth = (काष्ठा rxe_bth *)&pshdr[bth_offset];

	/* exclude bth.resv8a */
	bth->qpn |= cpu_to_be32(~BTH_QPN_MASK);

	length = hdr_size + RXE_BTH_BYTES;
	crc = rxe_crc32(pkt->rxe, crc, pshdr, length);

	/* And finish to compute the CRC on the reमुख्यder of the headers. */
	crc = rxe_crc32(pkt->rxe, crc, pkt->hdr + RXE_BTH_BYTES,
			rxe_opcode[pkt->opcode].length - RXE_BTH_BYTES);
	वापस crc;
पूर्ण
