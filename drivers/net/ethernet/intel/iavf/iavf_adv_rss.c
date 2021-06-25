<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2021, Intel Corporation. */

/* advanced RSS configuration ethtool support क्रम iavf */

#समावेश "iavf.h"

/**
 * iavf_fill_adv_rss_ip4_hdr - fill the IPv4 RSS protocol header
 * @hdr: the virtchnl message protocol header data काष्ठाure
 * @hash_flds: the RSS configuration protocol hash fields
 */
अटल व्योम
iavf_fill_adv_rss_ip4_hdr(काष्ठा virtchnl_proto_hdr *hdr, u64 hash_flds)
अणु
	VIRTCHNL_SET_PROTO_HDR_TYPE(hdr, IPV4);

	अगर (hash_flds & IAVF_ADV_RSS_HASH_FLD_IPV4_SA)
		VIRTCHNL_ADD_PROTO_HDR_FIELD_BIT(hdr, IPV4, SRC);

	अगर (hash_flds & IAVF_ADV_RSS_HASH_FLD_IPV4_DA)
		VIRTCHNL_ADD_PROTO_HDR_FIELD_BIT(hdr, IPV4, DST);
पूर्ण

/**
 * iavf_fill_adv_rss_ip6_hdr - fill the IPv6 RSS protocol header
 * @hdr: the virtchnl message protocol header data काष्ठाure
 * @hash_flds: the RSS configuration protocol hash fields
 */
अटल व्योम
iavf_fill_adv_rss_ip6_hdr(काष्ठा virtchnl_proto_hdr *hdr, u64 hash_flds)
अणु
	VIRTCHNL_SET_PROTO_HDR_TYPE(hdr, IPV6);

	अगर (hash_flds & IAVF_ADV_RSS_HASH_FLD_IPV6_SA)
		VIRTCHNL_ADD_PROTO_HDR_FIELD_BIT(hdr, IPV6, SRC);

	अगर (hash_flds & IAVF_ADV_RSS_HASH_FLD_IPV6_DA)
		VIRTCHNL_ADD_PROTO_HDR_FIELD_BIT(hdr, IPV6, DST);
पूर्ण

/**
 * iavf_fill_adv_rss_tcp_hdr - fill the TCP RSS protocol header
 * @hdr: the virtchnl message protocol header data काष्ठाure
 * @hash_flds: the RSS configuration protocol hash fields
 */
अटल व्योम
iavf_fill_adv_rss_tcp_hdr(काष्ठा virtchnl_proto_hdr *hdr, u64 hash_flds)
अणु
	VIRTCHNL_SET_PROTO_HDR_TYPE(hdr, TCP);

	अगर (hash_flds & IAVF_ADV_RSS_HASH_FLD_TCP_SRC_PORT)
		VIRTCHNL_ADD_PROTO_HDR_FIELD_BIT(hdr, TCP, SRC_PORT);

	अगर (hash_flds & IAVF_ADV_RSS_HASH_FLD_TCP_DST_PORT)
		VIRTCHNL_ADD_PROTO_HDR_FIELD_BIT(hdr, TCP, DST_PORT);
पूर्ण

/**
 * iavf_fill_adv_rss_udp_hdr - fill the UDP RSS protocol header
 * @hdr: the virtchnl message protocol header data काष्ठाure
 * @hash_flds: the RSS configuration protocol hash fields
 */
अटल व्योम
iavf_fill_adv_rss_udp_hdr(काष्ठा virtchnl_proto_hdr *hdr, u64 hash_flds)
अणु
	VIRTCHNL_SET_PROTO_HDR_TYPE(hdr, UDP);

	अगर (hash_flds & IAVF_ADV_RSS_HASH_FLD_UDP_SRC_PORT)
		VIRTCHNL_ADD_PROTO_HDR_FIELD_BIT(hdr, UDP, SRC_PORT);

	अगर (hash_flds & IAVF_ADV_RSS_HASH_FLD_UDP_DST_PORT)
		VIRTCHNL_ADD_PROTO_HDR_FIELD_BIT(hdr, UDP, DST_PORT);
पूर्ण

/**
 * iavf_fill_adv_rss_sctp_hdr - fill the SCTP RSS protocol header
 * @hdr: the virtchnl message protocol header data काष्ठाure
 * @hash_flds: the RSS configuration protocol hash fields
 */
अटल व्योम
iavf_fill_adv_rss_sctp_hdr(काष्ठा virtchnl_proto_hdr *hdr, u64 hash_flds)
अणु
	VIRTCHNL_SET_PROTO_HDR_TYPE(hdr, SCTP);

	अगर (hash_flds & IAVF_ADV_RSS_HASH_FLD_SCTP_SRC_PORT)
		VIRTCHNL_ADD_PROTO_HDR_FIELD_BIT(hdr, SCTP, SRC_PORT);

	अगर (hash_flds & IAVF_ADV_RSS_HASH_FLD_SCTP_DST_PORT)
		VIRTCHNL_ADD_PROTO_HDR_FIELD_BIT(hdr, SCTP, DST_PORT);
पूर्ण

/**
 * iavf_fill_adv_rss_cfg_msg - fill the RSS configuration पूर्णांकo virtchnl message
 * @rss_cfg: the virtchnl message to be filled with RSS configuration setting
 * @packet_hdrs: the RSS configuration protocol header types
 * @hash_flds: the RSS configuration protocol hash fields
 *
 * Returns 0 अगर the RSS configuration virtchnl message is filled successfully
 */
पूर्णांक
iavf_fill_adv_rss_cfg_msg(काष्ठा virtchnl_rss_cfg *rss_cfg,
			  u32 packet_hdrs, u64 hash_flds)
अणु
	काष्ठा virtchnl_proto_hdrs *proto_hdrs = &rss_cfg->proto_hdrs;
	काष्ठा virtchnl_proto_hdr *hdr;

	rss_cfg->rss_algorithm = VIRTCHNL_RSS_ALG_TOEPLITZ_ASYMMETRIC;

	proto_hdrs->tunnel_level = 0;	/* always outer layer */

	hdr = &proto_hdrs->proto_hdr[proto_hdrs->count++];
	चयन (packet_hdrs & IAVF_ADV_RSS_FLOW_SEG_HDR_L3) अणु
	हाल IAVF_ADV_RSS_FLOW_SEG_HDR_IPV4:
		iavf_fill_adv_rss_ip4_hdr(hdr, hash_flds);
		अवरोध;
	हाल IAVF_ADV_RSS_FLOW_SEG_HDR_IPV6:
		iavf_fill_adv_rss_ip6_hdr(hdr, hash_flds);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	hdr = &proto_hdrs->proto_hdr[proto_hdrs->count++];
	चयन (packet_hdrs & IAVF_ADV_RSS_FLOW_SEG_HDR_L4) अणु
	हाल IAVF_ADV_RSS_FLOW_SEG_HDR_TCP:
		iavf_fill_adv_rss_tcp_hdr(hdr, hash_flds);
		अवरोध;
	हाल IAVF_ADV_RSS_FLOW_SEG_HDR_UDP:
		iavf_fill_adv_rss_udp_hdr(hdr, hash_flds);
		अवरोध;
	हाल IAVF_ADV_RSS_FLOW_SEG_HDR_SCTP:
		iavf_fill_adv_rss_sctp_hdr(hdr, hash_flds);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * iavf_find_adv_rss_cfg_by_hdrs - find RSS configuration with header type
 * @adapter: poपूर्णांकer to the VF adapter काष्ठाure
 * @packet_hdrs: protocol header type to find.
 *
 * Returns poपूर्णांकer to advance RSS configuration अगर found or null
 */
काष्ठा iavf_adv_rss *
iavf_find_adv_rss_cfg_by_hdrs(काष्ठा iavf_adapter *adapter, u32 packet_hdrs)
अणु
	काष्ठा iavf_adv_rss *rss;

	list_क्रम_each_entry(rss, &adapter->adv_rss_list_head, list)
		अगर (rss->packet_hdrs == packet_hdrs)
			वापस rss;

	वापस शून्य;
पूर्ण

/**
 * iavf_prपूर्णांक_adv_rss_cfg
 * @adapter: poपूर्णांकer to the VF adapter काष्ठाure
 * @rss: poपूर्णांकer to the advance RSS configuration to prपूर्णांक
 * @action: the string description about how to handle the RSS
 * @result: the string description about the virtchnl result
 *
 * Prपूर्णांक the advance RSS configuration
 **/
व्योम
iavf_prपूर्णांक_adv_rss_cfg(काष्ठा iavf_adapter *adapter, काष्ठा iavf_adv_rss *rss,
		       स्थिर अक्षर *action, स्थिर अक्षर *result)
अणु
	u32 packet_hdrs = rss->packet_hdrs;
	u64 hash_flds = rss->hash_flds;
	अटल अक्षर hash_opt[300];
	स्थिर अक्षर *proto;

	अगर (packet_hdrs & IAVF_ADV_RSS_FLOW_SEG_HDR_TCP)
		proto = "TCP";
	अन्यथा अगर (packet_hdrs & IAVF_ADV_RSS_FLOW_SEG_HDR_UDP)
		proto = "UDP";
	अन्यथा अगर (packet_hdrs & IAVF_ADV_RSS_FLOW_SEG_HDR_SCTP)
		proto = "SCTP";
	अन्यथा
		वापस;

	स_रखो(hash_opt, 0, माप(hash_opt));

	म_जोड़ो(hash_opt, proto);
	अगर (packet_hdrs & IAVF_ADV_RSS_FLOW_SEG_HDR_IPV4)
		म_जोड़ो(hash_opt, "v4 ");
	अन्यथा
		म_जोड़ो(hash_opt, "v6 ");

	अगर (hash_flds & (IAVF_ADV_RSS_HASH_FLD_IPV4_SA |
			 IAVF_ADV_RSS_HASH_FLD_IPV6_SA))
		म_जोड़ो(hash_opt, "IP SA,");
	अगर (hash_flds & (IAVF_ADV_RSS_HASH_FLD_IPV4_DA |
			 IAVF_ADV_RSS_HASH_FLD_IPV6_DA))
		म_जोड़ो(hash_opt, "IP DA,");
	अगर (hash_flds & (IAVF_ADV_RSS_HASH_FLD_TCP_SRC_PORT |
			 IAVF_ADV_RSS_HASH_FLD_UDP_SRC_PORT |
			 IAVF_ADV_RSS_HASH_FLD_SCTP_SRC_PORT))
		म_जोड़ो(hash_opt, "src port,");
	अगर (hash_flds & (IAVF_ADV_RSS_HASH_FLD_TCP_DST_PORT |
			 IAVF_ADV_RSS_HASH_FLD_UDP_DST_PORT |
			 IAVF_ADV_RSS_HASH_FLD_SCTP_DST_PORT))
		म_जोड़ो(hash_opt, "dst port,");

	अगर (!action)
		action = "";

	अगर (!result)
		result = "";

	dev_info(&adapter->pdev->dev, "%s %s %s\n", action, hash_opt, result);
पूर्ण
