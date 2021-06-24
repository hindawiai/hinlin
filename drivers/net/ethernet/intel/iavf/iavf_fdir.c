<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2020, Intel Corporation. */

/* flow director ethtool support क्रम iavf */

#समावेश "iavf.h"

#घोषणा GTPU_PORT	2152
#घोषणा NAT_T_ESP_PORT	4500
#घोषणा PFCP_PORT	8805

अटल स्थिर काष्ठा in6_addr ipv6_addr_full_mask = अणु
	.in6_u = अणु
		.u6_addr8 = अणु
			0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
			0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		पूर्ण
	पूर्ण
पूर्ण;

/**
 * iavf_pkt_udp_no_pay_len - the length of UDP packet without payload
 * @fltr: Flow Director filter data काष्ठाure
 */
अटल u16 iavf_pkt_udp_no_pay_len(काष्ठा iavf_fdir_fltr *fltr)
अणु
	वापस माप(काष्ठा ethhdr) +
	       (fltr->ip_ver == 4 ? माप(काष्ठा iphdr) : माप(काष्ठा ipv6hdr)) +
	       माप(काष्ठा udphdr);
पूर्ण

/**
 * iavf_fill_fdir_gtpu_hdr - fill the GTP-U protocol header
 * @fltr: Flow Director filter data काष्ठाure
 * @proto_hdrs: Flow Director protocol headers data काष्ठाure
 *
 * Returns 0 अगर the GTP-U protocol header is set successfully
 */
अटल पूर्णांक
iavf_fill_fdir_gtpu_hdr(काष्ठा iavf_fdir_fltr *fltr,
			काष्ठा virtchnl_proto_hdrs *proto_hdrs)
अणु
	काष्ठा virtchnl_proto_hdr *uhdr = &proto_hdrs->proto_hdr[proto_hdrs->count - 1];
	काष्ठा virtchnl_proto_hdr *ghdr = &proto_hdrs->proto_hdr[proto_hdrs->count++];
	काष्ठा virtchnl_proto_hdr *ehdr = शून्य; /* Extension Header अगर it exists */
	u16 adj_offs, hdr_offs;
	पूर्णांक i;

	VIRTCHNL_SET_PROTO_HDR_TYPE(ghdr, GTPU_IP);

	adj_offs = iavf_pkt_udp_no_pay_len(fltr);

	क्रम (i = 0; i < fltr->flex_cnt; i++) अणु
#घोषणा IAVF_GTPU_HDR_TEID_OFFS0	4
#घोषणा IAVF_GTPU_HDR_TEID_OFFS1	6
#घोषणा IAVF_GTPU_HDR_N_PDU_AND_NEXT_EXTHDR_OFFS	10
#घोषणा IAVF_GTPU_HDR_NEXT_EXTHDR_TYPE_MASK		0x00FF /* skip N_PDU */
/* PDU Session Container Extension Header (PSC) */
#घोषणा IAVF_GTPU_PSC_EXTHDR_TYPE			0x85
#घोषणा IAVF_GTPU_HDR_PSC_PDU_TYPE_AND_QFI_OFFS		13
#घोषणा IAVF_GTPU_HDR_PSC_PDU_QFI_MASK			0x3F /* skip Type */
#घोषणा IAVF_GTPU_EH_QFI_IDX				1

		अगर (fltr->flex_words[i].offset < adj_offs)
			वापस -EINVAL;

		hdr_offs = fltr->flex_words[i].offset - adj_offs;

		चयन (hdr_offs) अणु
		हाल IAVF_GTPU_HDR_TEID_OFFS0:
		हाल IAVF_GTPU_HDR_TEID_OFFS1: अणु
			__be16 *pay_word = (__be16 *)ghdr->buffer;

			pay_word[hdr_offs >> 1] = htons(fltr->flex_words[i].word);
			VIRTCHNL_ADD_PROTO_HDR_FIELD_BIT(ghdr, GTPU_IP, TEID);
			पूर्ण
			अवरोध;
		हाल IAVF_GTPU_HDR_N_PDU_AND_NEXT_EXTHDR_OFFS:
			अगर ((fltr->flex_words[i].word &
			     IAVF_GTPU_HDR_NEXT_EXTHDR_TYPE_MASK) !=
						IAVF_GTPU_PSC_EXTHDR_TYPE)
				वापस -EOPNOTSUPP;
			अगर (!ehdr)
				ehdr = &proto_hdrs->proto_hdr[proto_hdrs->count++];
			VIRTCHNL_SET_PROTO_HDR_TYPE(ehdr, GTPU_EH);
			अवरोध;
		हाल IAVF_GTPU_HDR_PSC_PDU_TYPE_AND_QFI_OFFS:
			अगर (!ehdr)
				वापस -EINVAL;
			ehdr->buffer[IAVF_GTPU_EH_QFI_IDX] =
					fltr->flex_words[i].word &
						IAVF_GTPU_HDR_PSC_PDU_QFI_MASK;
			VIRTCHNL_ADD_PROTO_HDR_FIELD_BIT(ehdr, GTPU_EH, QFI);
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	uhdr->field_selector = 0; /* The PF ignores the UDP header fields */

	वापस 0;
पूर्ण

/**
 * iavf_fill_fdir_pfcp_hdr - fill the PFCP protocol header
 * @fltr: Flow Director filter data काष्ठाure
 * @proto_hdrs: Flow Director protocol headers data काष्ठाure
 *
 * Returns 0 अगर the PFCP protocol header is set successfully
 */
अटल पूर्णांक
iavf_fill_fdir_pfcp_hdr(काष्ठा iavf_fdir_fltr *fltr,
			काष्ठा virtchnl_proto_hdrs *proto_hdrs)
अणु
	काष्ठा virtchnl_proto_hdr *uhdr = &proto_hdrs->proto_hdr[proto_hdrs->count - 1];
	काष्ठा virtchnl_proto_hdr *hdr = &proto_hdrs->proto_hdr[proto_hdrs->count++];
	u16 adj_offs, hdr_offs;
	पूर्णांक i;

	VIRTCHNL_SET_PROTO_HDR_TYPE(hdr, PFCP);

	adj_offs = iavf_pkt_udp_no_pay_len(fltr);

	क्रम (i = 0; i < fltr->flex_cnt; i++) अणु
#घोषणा IAVF_PFCP_HDR_SFIELD_AND_MSG_TYPE_OFFS	0
		अगर (fltr->flex_words[i].offset < adj_offs)
			वापस -EINVAL;

		hdr_offs = fltr->flex_words[i].offset - adj_offs;

		चयन (hdr_offs) अणु
		हाल IAVF_PFCP_HDR_SFIELD_AND_MSG_TYPE_OFFS:
			hdr->buffer[0] = (fltr->flex_words[i].word >> 8) & 0xff;
			VIRTCHNL_ADD_PROTO_HDR_FIELD_BIT(hdr, PFCP, S_FIELD);
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	uhdr->field_selector = 0; /* The PF ignores the UDP header fields */

	वापस 0;
पूर्ण

/**
 * iavf_fill_fdir_nat_t_esp_hdr - fill the NAT-T-ESP protocol header
 * @fltr: Flow Director filter data काष्ठाure
 * @proto_hdrs: Flow Director protocol headers data काष्ठाure
 *
 * Returns 0 अगर the NAT-T-ESP protocol header is set successfully
 */
अटल पूर्णांक
iavf_fill_fdir_nat_t_esp_hdr(काष्ठा iavf_fdir_fltr *fltr,
			     काष्ठा virtchnl_proto_hdrs *proto_hdrs)
अणु
	काष्ठा virtchnl_proto_hdr *uhdr = &proto_hdrs->proto_hdr[proto_hdrs->count - 1];
	काष्ठा virtchnl_proto_hdr *hdr = &proto_hdrs->proto_hdr[proto_hdrs->count++];
	u16 adj_offs, hdr_offs;
	u32 spi = 0;
	पूर्णांक i;

	VIRTCHNL_SET_PROTO_HDR_TYPE(hdr, ESP);

	adj_offs = iavf_pkt_udp_no_pay_len(fltr);

	क्रम (i = 0; i < fltr->flex_cnt; i++) अणु
#घोषणा IAVF_NAT_T_ESP_SPI_OFFS0	0
#घोषणा IAVF_NAT_T_ESP_SPI_OFFS1	2
		अगर (fltr->flex_words[i].offset < adj_offs)
			वापस -EINVAL;

		hdr_offs = fltr->flex_words[i].offset - adj_offs;

		चयन (hdr_offs) अणु
		हाल IAVF_NAT_T_ESP_SPI_OFFS0:
			spi |= fltr->flex_words[i].word << 16;
			अवरोध;
		हाल IAVF_NAT_T_ESP_SPI_OFFS1:
			spi |= fltr->flex_words[i].word;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (!spi)
		वापस -EOPNOTSUPP; /* Not support IKE Header Format with SPI 0 */

	*(__be32 *)hdr->buffer = htonl(spi);
	VIRTCHNL_ADD_PROTO_HDR_FIELD_BIT(hdr, ESP, SPI);

	uhdr->field_selector = 0; /* The PF ignores the UDP header fields */

	वापस 0;
पूर्ण

/**
 * iavf_fill_fdir_udp_flex_pay_hdr - fill the UDP payload header
 * @fltr: Flow Director filter data काष्ठाure
 * @proto_hdrs: Flow Director protocol headers data काष्ठाure
 *
 * Returns 0 अगर the UDP payload defined protocol header is set successfully
 */
अटल पूर्णांक
iavf_fill_fdir_udp_flex_pay_hdr(काष्ठा iavf_fdir_fltr *fltr,
				काष्ठा virtchnl_proto_hdrs *proto_hdrs)
अणु
	पूर्णांक err;

	चयन (ntohs(fltr->ip_data.dst_port)) अणु
	हाल GTPU_PORT:
		err = iavf_fill_fdir_gtpu_hdr(fltr, proto_hdrs);
		अवरोध;
	हाल NAT_T_ESP_PORT:
		err = iavf_fill_fdir_nat_t_esp_hdr(fltr, proto_hdrs);
		अवरोध;
	हाल PFCP_PORT:
		err = iavf_fill_fdir_pfcp_hdr(fltr, proto_hdrs);
		अवरोध;
	शेष:
		err = -EOPNOTSUPP;
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

/**
 * iavf_fill_fdir_ip4_hdr - fill the IPv4 protocol header
 * @fltr: Flow Director filter data काष्ठाure
 * @proto_hdrs: Flow Director protocol headers data काष्ठाure
 *
 * Returns 0 अगर the IPv4 protocol header is set successfully
 */
अटल पूर्णांक
iavf_fill_fdir_ip4_hdr(काष्ठा iavf_fdir_fltr *fltr,
		       काष्ठा virtchnl_proto_hdrs *proto_hdrs)
अणु
	काष्ठा virtchnl_proto_hdr *hdr = &proto_hdrs->proto_hdr[proto_hdrs->count++];
	काष्ठा iphdr *iph = (काष्ठा iphdr *)hdr->buffer;

	VIRTCHNL_SET_PROTO_HDR_TYPE(hdr, IPV4);

	अगर (fltr->ip_mask.tos == U8_MAX) अणु
		iph->tos = fltr->ip_data.tos;
		VIRTCHNL_ADD_PROTO_HDR_FIELD_BIT(hdr, IPV4, DSCP);
	पूर्ण

	अगर (fltr->ip_mask.proto == U8_MAX) अणु
		iph->protocol = fltr->ip_data.proto;
		VIRTCHNL_ADD_PROTO_HDR_FIELD_BIT(hdr, IPV4, PROT);
	पूर्ण

	अगर (fltr->ip_mask.v4_addrs.src_ip == htonl(U32_MAX)) अणु
		iph->saddr = fltr->ip_data.v4_addrs.src_ip;
		VIRTCHNL_ADD_PROTO_HDR_FIELD_BIT(hdr, IPV4, SRC);
	पूर्ण

	अगर (fltr->ip_mask.v4_addrs.dst_ip == htonl(U32_MAX)) अणु
		iph->daddr = fltr->ip_data.v4_addrs.dst_ip;
		VIRTCHNL_ADD_PROTO_HDR_FIELD_BIT(hdr, IPV4, DST);
	पूर्ण

	fltr->ip_ver = 4;

	वापस 0;
पूर्ण

/**
 * iavf_fill_fdir_ip6_hdr - fill the IPv6 protocol header
 * @fltr: Flow Director filter data काष्ठाure
 * @proto_hdrs: Flow Director protocol headers data काष्ठाure
 *
 * Returns 0 अगर the IPv6 protocol header is set successfully
 */
अटल पूर्णांक
iavf_fill_fdir_ip6_hdr(काष्ठा iavf_fdir_fltr *fltr,
		       काष्ठा virtchnl_proto_hdrs *proto_hdrs)
अणु
	काष्ठा virtchnl_proto_hdr *hdr = &proto_hdrs->proto_hdr[proto_hdrs->count++];
	काष्ठा ipv6hdr *iph = (काष्ठा ipv6hdr *)hdr->buffer;

	VIRTCHNL_SET_PROTO_HDR_TYPE(hdr, IPV6);

	अगर (fltr->ip_mask.tclass == U8_MAX) अणु
		iph->priority = (fltr->ip_data.tclass >> 4) & 0xF;
		iph->flow_lbl[0] = (fltr->ip_data.tclass << 4) & 0xF0;
		VIRTCHNL_ADD_PROTO_HDR_FIELD_BIT(hdr, IPV6, TC);
	पूर्ण

	अगर (fltr->ip_mask.proto == U8_MAX) अणु
		iph->nexthdr = fltr->ip_data.proto;
		VIRTCHNL_ADD_PROTO_HDR_FIELD_BIT(hdr, IPV6, PROT);
	पूर्ण

	अगर (!स_भेद(&fltr->ip_mask.v6_addrs.src_ip, &ipv6_addr_full_mask,
		    माप(काष्ठा in6_addr))) अणु
		स_नकल(&iph->saddr, &fltr->ip_data.v6_addrs.src_ip,
		       माप(काष्ठा in6_addr));
		VIRTCHNL_ADD_PROTO_HDR_FIELD_BIT(hdr, IPV6, SRC);
	पूर्ण

	अगर (!स_भेद(&fltr->ip_mask.v6_addrs.dst_ip, &ipv6_addr_full_mask,
		    माप(काष्ठा in6_addr))) अणु
		स_नकल(&iph->daddr, &fltr->ip_data.v6_addrs.dst_ip,
		       माप(काष्ठा in6_addr));
		VIRTCHNL_ADD_PROTO_HDR_FIELD_BIT(hdr, IPV6, DST);
	पूर्ण

	fltr->ip_ver = 6;

	वापस 0;
पूर्ण

/**
 * iavf_fill_fdir_tcp_hdr - fill the TCP protocol header
 * @fltr: Flow Director filter data काष्ठाure
 * @proto_hdrs: Flow Director protocol headers data काष्ठाure
 *
 * Returns 0 अगर the TCP protocol header is set successfully
 */
अटल पूर्णांक
iavf_fill_fdir_tcp_hdr(काष्ठा iavf_fdir_fltr *fltr,
		       काष्ठा virtchnl_proto_hdrs *proto_hdrs)
अणु
	काष्ठा virtchnl_proto_hdr *hdr = &proto_hdrs->proto_hdr[proto_hdrs->count++];
	काष्ठा tcphdr *tcph = (काष्ठा tcphdr *)hdr->buffer;

	VIRTCHNL_SET_PROTO_HDR_TYPE(hdr, TCP);

	अगर (fltr->ip_mask.src_port == htons(U16_MAX)) अणु
		tcph->source = fltr->ip_data.src_port;
		VIRTCHNL_ADD_PROTO_HDR_FIELD_BIT(hdr, TCP, SRC_PORT);
	पूर्ण

	अगर (fltr->ip_mask.dst_port == htons(U16_MAX)) अणु
		tcph->dest = fltr->ip_data.dst_port;
		VIRTCHNL_ADD_PROTO_HDR_FIELD_BIT(hdr, TCP, DST_PORT);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * iavf_fill_fdir_udp_hdr - fill the UDP protocol header
 * @fltr: Flow Director filter data काष्ठाure
 * @proto_hdrs: Flow Director protocol headers data काष्ठाure
 *
 * Returns 0 अगर the UDP protocol header is set successfully
 */
अटल पूर्णांक
iavf_fill_fdir_udp_hdr(काष्ठा iavf_fdir_fltr *fltr,
		       काष्ठा virtchnl_proto_hdrs *proto_hdrs)
अणु
	काष्ठा virtchnl_proto_hdr *hdr = &proto_hdrs->proto_hdr[proto_hdrs->count++];
	काष्ठा udphdr *udph = (काष्ठा udphdr *)hdr->buffer;

	VIRTCHNL_SET_PROTO_HDR_TYPE(hdr, UDP);

	अगर (fltr->ip_mask.src_port == htons(U16_MAX)) अणु
		udph->source = fltr->ip_data.src_port;
		VIRTCHNL_ADD_PROTO_HDR_FIELD_BIT(hdr, UDP, SRC_PORT);
	पूर्ण

	अगर (fltr->ip_mask.dst_port == htons(U16_MAX)) अणु
		udph->dest = fltr->ip_data.dst_port;
		VIRTCHNL_ADD_PROTO_HDR_FIELD_BIT(hdr, UDP, DST_PORT);
	पूर्ण

	अगर (!fltr->flex_cnt)
		वापस 0;

	वापस iavf_fill_fdir_udp_flex_pay_hdr(fltr, proto_hdrs);
पूर्ण

/**
 * iavf_fill_fdir_sctp_hdr - fill the SCTP protocol header
 * @fltr: Flow Director filter data काष्ठाure
 * @proto_hdrs: Flow Director protocol headers data काष्ठाure
 *
 * Returns 0 अगर the SCTP protocol header is set successfully
 */
अटल पूर्णांक
iavf_fill_fdir_sctp_hdr(काष्ठा iavf_fdir_fltr *fltr,
			काष्ठा virtchnl_proto_hdrs *proto_hdrs)
अणु
	काष्ठा virtchnl_proto_hdr *hdr = &proto_hdrs->proto_hdr[proto_hdrs->count++];
	काष्ठा sctphdr *sctph = (काष्ठा sctphdr *)hdr->buffer;

	VIRTCHNL_SET_PROTO_HDR_TYPE(hdr, SCTP);

	अगर (fltr->ip_mask.src_port == htons(U16_MAX)) अणु
		sctph->source = fltr->ip_data.src_port;
		VIRTCHNL_ADD_PROTO_HDR_FIELD_BIT(hdr, SCTP, SRC_PORT);
	पूर्ण

	अगर (fltr->ip_mask.dst_port == htons(U16_MAX)) अणु
		sctph->dest = fltr->ip_data.dst_port;
		VIRTCHNL_ADD_PROTO_HDR_FIELD_BIT(hdr, SCTP, DST_PORT);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * iavf_fill_fdir_ah_hdr - fill the AH protocol header
 * @fltr: Flow Director filter data काष्ठाure
 * @proto_hdrs: Flow Director protocol headers data काष्ठाure
 *
 * Returns 0 अगर the AH protocol header is set successfully
 */
अटल पूर्णांक
iavf_fill_fdir_ah_hdr(काष्ठा iavf_fdir_fltr *fltr,
		      काष्ठा virtchnl_proto_hdrs *proto_hdrs)
अणु
	काष्ठा virtchnl_proto_hdr *hdr = &proto_hdrs->proto_hdr[proto_hdrs->count++];
	काष्ठा ip_auth_hdr *ah = (काष्ठा ip_auth_hdr *)hdr->buffer;

	VIRTCHNL_SET_PROTO_HDR_TYPE(hdr, AH);

	अगर (fltr->ip_mask.spi == htonl(U32_MAX)) अणु
		ah->spi = fltr->ip_data.spi;
		VIRTCHNL_ADD_PROTO_HDR_FIELD_BIT(hdr, AH, SPI);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * iavf_fill_fdir_esp_hdr - fill the ESP protocol header
 * @fltr: Flow Director filter data काष्ठाure
 * @proto_hdrs: Flow Director protocol headers data काष्ठाure
 *
 * Returns 0 अगर the ESP protocol header is set successfully
 */
अटल पूर्णांक
iavf_fill_fdir_esp_hdr(काष्ठा iavf_fdir_fltr *fltr,
		       काष्ठा virtchnl_proto_hdrs *proto_hdrs)
अणु
	काष्ठा virtchnl_proto_hdr *hdr = &proto_hdrs->proto_hdr[proto_hdrs->count++];
	काष्ठा ip_esp_hdr *esph = (काष्ठा ip_esp_hdr *)hdr->buffer;

	VIRTCHNL_SET_PROTO_HDR_TYPE(hdr, ESP);

	अगर (fltr->ip_mask.spi == htonl(U32_MAX)) अणु
		esph->spi = fltr->ip_data.spi;
		VIRTCHNL_ADD_PROTO_HDR_FIELD_BIT(hdr, ESP, SPI);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * iavf_fill_fdir_l4_hdr - fill the L4 protocol header
 * @fltr: Flow Director filter data काष्ठाure
 * @proto_hdrs: Flow Director protocol headers data काष्ठाure
 *
 * Returns 0 अगर the L4 protocol header is set successfully
 */
अटल पूर्णांक
iavf_fill_fdir_l4_hdr(काष्ठा iavf_fdir_fltr *fltr,
		      काष्ठा virtchnl_proto_hdrs *proto_hdrs)
अणु
	काष्ठा virtchnl_proto_hdr *hdr;
	__be32 *l4_4_data;

	अगर (!fltr->ip_mask.proto) /* IPv4/IPv6 header only */
		वापस 0;

	hdr = &proto_hdrs->proto_hdr[proto_hdrs->count++];
	l4_4_data = (__be32 *)hdr->buffer;

	/* L2TPv3 over IP with 'Session ID' */
	अगर (fltr->ip_data.proto == 115 && fltr->ip_mask.l4_header == htonl(U32_MAX)) अणु
		VIRTCHNL_SET_PROTO_HDR_TYPE(hdr, L2TPV3);
		VIRTCHNL_ADD_PROTO_HDR_FIELD_BIT(hdr, L2TPV3, SESS_ID);

		*l4_4_data = fltr->ip_data.l4_header;
	पूर्ण अन्यथा अणु
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * iavf_fill_fdir_eth_hdr - fill the Ethernet protocol header
 * @fltr: Flow Director filter data काष्ठाure
 * @proto_hdrs: Flow Director protocol headers data काष्ठाure
 *
 * Returns 0 अगर the Ethernet protocol header is set successfully
 */
अटल पूर्णांक
iavf_fill_fdir_eth_hdr(काष्ठा iavf_fdir_fltr *fltr,
		       काष्ठा virtchnl_proto_hdrs *proto_hdrs)
अणु
	काष्ठा virtchnl_proto_hdr *hdr = &proto_hdrs->proto_hdr[proto_hdrs->count++];
	काष्ठा ethhdr *ehdr = (काष्ठा ethhdr *)hdr->buffer;

	VIRTCHNL_SET_PROTO_HDR_TYPE(hdr, ETH);

	अगर (fltr->eth_mask.etype == htons(U16_MAX)) अणु
		अगर (fltr->eth_data.etype == htons(ETH_P_IP) ||
		    fltr->eth_data.etype == htons(ETH_P_IPV6))
			वापस -EOPNOTSUPP;

		ehdr->h_proto = fltr->eth_data.etype;
		VIRTCHNL_ADD_PROTO_HDR_FIELD_BIT(hdr, ETH, ETHERTYPE);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * iavf_fill_fdir_add_msg - fill the Flow Director filter पूर्णांकo virtchnl message
 * @adapter: poपूर्णांकer to the VF adapter काष्ठाure
 * @fltr: Flow Director filter data काष्ठाure
 *
 * Returns 0 अगर the add Flow Director virtchnl message is filled successfully
 */
पूर्णांक iavf_fill_fdir_add_msg(काष्ठा iavf_adapter *adapter, काष्ठा iavf_fdir_fltr *fltr)
अणु
	काष्ठा virtchnl_fdir_add *vc_msg = &fltr->vc_add_msg;
	काष्ठा virtchnl_proto_hdrs *proto_hdrs;
	पूर्णांक err;

	proto_hdrs = &vc_msg->rule_cfg.proto_hdrs;

	err = iavf_fill_fdir_eth_hdr(fltr, proto_hdrs); /* L2 always exists */
	अगर (err)
		वापस err;

	चयन (fltr->flow_type) अणु
	हाल IAVF_Fसूची_FLOW_IPV4_TCP:
		err = iavf_fill_fdir_ip4_hdr(fltr, proto_hdrs) |
		      iavf_fill_fdir_tcp_hdr(fltr, proto_hdrs);
		अवरोध;
	हाल IAVF_Fसूची_FLOW_IPV4_UDP:
		err = iavf_fill_fdir_ip4_hdr(fltr, proto_hdrs) |
		      iavf_fill_fdir_udp_hdr(fltr, proto_hdrs);
		अवरोध;
	हाल IAVF_Fसूची_FLOW_IPV4_SCTP:
		err = iavf_fill_fdir_ip4_hdr(fltr, proto_hdrs) |
		      iavf_fill_fdir_sctp_hdr(fltr, proto_hdrs);
		अवरोध;
	हाल IAVF_Fसूची_FLOW_IPV4_AH:
		err = iavf_fill_fdir_ip4_hdr(fltr, proto_hdrs) |
		      iavf_fill_fdir_ah_hdr(fltr, proto_hdrs);
		अवरोध;
	हाल IAVF_Fसूची_FLOW_IPV4_ESP:
		err = iavf_fill_fdir_ip4_hdr(fltr, proto_hdrs) |
		      iavf_fill_fdir_esp_hdr(fltr, proto_hdrs);
		अवरोध;
	हाल IAVF_Fसूची_FLOW_IPV4_OTHER:
		err = iavf_fill_fdir_ip4_hdr(fltr, proto_hdrs) |
		      iavf_fill_fdir_l4_hdr(fltr, proto_hdrs);
		अवरोध;
	हाल IAVF_Fसूची_FLOW_IPV6_TCP:
		err = iavf_fill_fdir_ip6_hdr(fltr, proto_hdrs) |
		      iavf_fill_fdir_tcp_hdr(fltr, proto_hdrs);
		अवरोध;
	हाल IAVF_Fसूची_FLOW_IPV6_UDP:
		err = iavf_fill_fdir_ip6_hdr(fltr, proto_hdrs) |
		      iavf_fill_fdir_udp_hdr(fltr, proto_hdrs);
		अवरोध;
	हाल IAVF_Fसूची_FLOW_IPV6_SCTP:
		err = iavf_fill_fdir_ip6_hdr(fltr, proto_hdrs) |
		      iavf_fill_fdir_sctp_hdr(fltr, proto_hdrs);
		अवरोध;
	हाल IAVF_Fसूची_FLOW_IPV6_AH:
		err = iavf_fill_fdir_ip6_hdr(fltr, proto_hdrs) |
		      iavf_fill_fdir_ah_hdr(fltr, proto_hdrs);
		अवरोध;
	हाल IAVF_Fसूची_FLOW_IPV6_ESP:
		err = iavf_fill_fdir_ip6_hdr(fltr, proto_hdrs) |
		      iavf_fill_fdir_esp_hdr(fltr, proto_hdrs);
		अवरोध;
	हाल IAVF_Fसूची_FLOW_IPV6_OTHER:
		err = iavf_fill_fdir_ip6_hdr(fltr, proto_hdrs) |
		      iavf_fill_fdir_l4_hdr(fltr, proto_hdrs);
		अवरोध;
	हाल IAVF_Fसूची_FLOW_NON_IP_L2:
		अवरोध;
	शेष:
		err = -EINVAL;
		अवरोध;
	पूर्ण

	अगर (err)
		वापस err;

	vc_msg->vsi_id = adapter->vsi.id;
	vc_msg->rule_cfg.action_set.count = 1;
	vc_msg->rule_cfg.action_set.actions[0].type = fltr->action;
	vc_msg->rule_cfg.action_set.actions[0].act_conf.queue.index = fltr->q_index;

	वापस 0;
पूर्ण

/**
 * iavf_fdir_flow_proto_name - get the flow protocol name
 * @flow_type: Flow Director filter flow type
 **/
अटल स्थिर अक्षर *iavf_fdir_flow_proto_name(क्रमागत iavf_fdir_flow_type flow_type)
अणु
	चयन (flow_type) अणु
	हाल IAVF_Fसूची_FLOW_IPV4_TCP:
	हाल IAVF_Fसूची_FLOW_IPV6_TCP:
		वापस "TCP";
	हाल IAVF_Fसूची_FLOW_IPV4_UDP:
	हाल IAVF_Fसूची_FLOW_IPV6_UDP:
		वापस "UDP";
	हाल IAVF_Fसूची_FLOW_IPV4_SCTP:
	हाल IAVF_Fसूची_FLOW_IPV6_SCTP:
		वापस "SCTP";
	हाल IAVF_Fसूची_FLOW_IPV4_AH:
	हाल IAVF_Fसूची_FLOW_IPV6_AH:
		वापस "AH";
	हाल IAVF_Fसूची_FLOW_IPV4_ESP:
	हाल IAVF_Fसूची_FLOW_IPV6_ESP:
		वापस "ESP";
	हाल IAVF_Fसूची_FLOW_IPV4_OTHER:
	हाल IAVF_Fसूची_FLOW_IPV6_OTHER:
		वापस "Other";
	हाल IAVF_Fसूची_FLOW_NON_IP_L2:
		वापस "Ethernet";
	शेष:
		वापस शून्य;
	पूर्ण
पूर्ण

/**
 * iavf_prपूर्णांक_fdir_fltr
 * @adapter: adapter काष्ठाure
 * @fltr: Flow Director filter to prपूर्णांक
 *
 * Prपूर्णांक the Flow Director filter
 **/
व्योम iavf_prपूर्णांक_fdir_fltr(काष्ठा iavf_adapter *adapter, काष्ठा iavf_fdir_fltr *fltr)
अणु
	स्थिर अक्षर *proto = iavf_fdir_flow_proto_name(fltr->flow_type);

	अगर (!proto)
		वापस;

	चयन (fltr->flow_type) अणु
	हाल IAVF_Fसूची_FLOW_IPV4_TCP:
	हाल IAVF_Fसूची_FLOW_IPV4_UDP:
	हाल IAVF_Fसूची_FLOW_IPV4_SCTP:
		dev_info(&adapter->pdev->dev, "Rule ID: %u dst_ip: %pI4 src_ip %pI4 %s: dst_port %hu src_port %hu\n",
			 fltr->loc,
			 &fltr->ip_data.v4_addrs.dst_ip,
			 &fltr->ip_data.v4_addrs.src_ip,
			 proto,
			 ntohs(fltr->ip_data.dst_port),
			 ntohs(fltr->ip_data.src_port));
		अवरोध;
	हाल IAVF_Fसूची_FLOW_IPV4_AH:
	हाल IAVF_Fसूची_FLOW_IPV4_ESP:
		dev_info(&adapter->pdev->dev, "Rule ID: %u dst_ip: %pI4 src_ip %pI4 %s: SPI %u\n",
			 fltr->loc,
			 &fltr->ip_data.v4_addrs.dst_ip,
			 &fltr->ip_data.v4_addrs.src_ip,
			 proto,
			 ntohl(fltr->ip_data.spi));
		अवरोध;
	हाल IAVF_Fसूची_FLOW_IPV4_OTHER:
		dev_info(&adapter->pdev->dev, "Rule ID: %u dst_ip: %pI4 src_ip %pI4 proto: %u L4_bytes: 0x%x\n",
			 fltr->loc,
			 &fltr->ip_data.v4_addrs.dst_ip,
			 &fltr->ip_data.v4_addrs.src_ip,
			 fltr->ip_data.proto,
			 ntohl(fltr->ip_data.l4_header));
		अवरोध;
	हाल IAVF_Fसूची_FLOW_IPV6_TCP:
	हाल IAVF_Fसूची_FLOW_IPV6_UDP:
	हाल IAVF_Fसूची_FLOW_IPV6_SCTP:
		dev_info(&adapter->pdev->dev, "Rule ID: %u dst_ip: %pI6 src_ip %pI6 %s: dst_port %hu src_port %hu\n",
			 fltr->loc,
			 &fltr->ip_data.v6_addrs.dst_ip,
			 &fltr->ip_data.v6_addrs.src_ip,
			 proto,
			 ntohs(fltr->ip_data.dst_port),
			 ntohs(fltr->ip_data.src_port));
		अवरोध;
	हाल IAVF_Fसूची_FLOW_IPV6_AH:
	हाल IAVF_Fसूची_FLOW_IPV6_ESP:
		dev_info(&adapter->pdev->dev, "Rule ID: %u dst_ip: %pI6 src_ip %pI6 %s: SPI %u\n",
			 fltr->loc,
			 &fltr->ip_data.v6_addrs.dst_ip,
			 &fltr->ip_data.v6_addrs.src_ip,
			 proto,
			 ntohl(fltr->ip_data.spi));
		अवरोध;
	हाल IAVF_Fसूची_FLOW_IPV6_OTHER:
		dev_info(&adapter->pdev->dev, "Rule ID: %u dst_ip: %pI6 src_ip %pI6 proto: %u L4_bytes: 0x%x\n",
			 fltr->loc,
			 &fltr->ip_data.v6_addrs.dst_ip,
			 &fltr->ip_data.v6_addrs.src_ip,
			 fltr->ip_data.proto,
			 ntohl(fltr->ip_data.l4_header));
		अवरोध;
	हाल IAVF_Fसूची_FLOW_NON_IP_L2:
		dev_info(&adapter->pdev->dev, "Rule ID: %u eth_type: 0x%x\n",
			 fltr->loc,
			 ntohs(fltr->eth_data.etype));
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/**
 * iavf_fdir_is_dup_fltr - test अगर filter is alपढ़ोy in list
 * @adapter: poपूर्णांकer to the VF adapter काष्ठाure
 * @fltr: Flow Director filter data काष्ठाure
 *
 * Returns true अगर the filter is found in the list
 */
bool iavf_fdir_is_dup_fltr(काष्ठा iavf_adapter *adapter, काष्ठा iavf_fdir_fltr *fltr)
अणु
	काष्ठा iavf_fdir_fltr *पंचांगp;

	list_क्रम_each_entry(पंचांगp, &adapter->fdir_list_head, list) अणु
		अगर (पंचांगp->flow_type != fltr->flow_type)
			जारी;

		अगर (!स_भेद(&पंचांगp->eth_data, &fltr->eth_data,
			    माप(fltr->eth_data)) &&
		    !स_भेद(&पंचांगp->ip_data, &fltr->ip_data,
			    माप(fltr->ip_data)) &&
		    !स_भेद(&पंचांगp->ext_data, &fltr->ext_data,
			    माप(fltr->ext_data)))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

/**
 * iavf_find_fdir_fltr_by_loc - find filter with location
 * @adapter: poपूर्णांकer to the VF adapter काष्ठाure
 * @loc: location to find.
 *
 * Returns poपूर्णांकer to Flow Director filter अगर found or null
 */
काष्ठा iavf_fdir_fltr *iavf_find_fdir_fltr_by_loc(काष्ठा iavf_adapter *adapter, u32 loc)
अणु
	काष्ठा iavf_fdir_fltr *rule;

	list_क्रम_each_entry(rule, &adapter->fdir_list_head, list)
		अगर (rule->loc == loc)
			वापस rule;

	वापस शून्य;
पूर्ण

/**
 * iavf_fdir_list_add_fltr - add a new node to the flow director filter list
 * @adapter: poपूर्णांकer to the VF adapter काष्ठाure
 * @fltr: filter node to add to काष्ठाure
 */
व्योम iavf_fdir_list_add_fltr(काष्ठा iavf_adapter *adapter, काष्ठा iavf_fdir_fltr *fltr)
अणु
	काष्ठा iavf_fdir_fltr *rule, *parent = शून्य;

	list_क्रम_each_entry(rule, &adapter->fdir_list_head, list) अणु
		अगर (rule->loc >= fltr->loc)
			अवरोध;
		parent = rule;
	पूर्ण

	अगर (parent)
		list_add(&fltr->list, &parent->list);
	अन्यथा
		list_add(&fltr->list, &adapter->fdir_list_head);
पूर्ण
