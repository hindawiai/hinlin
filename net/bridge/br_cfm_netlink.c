<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later

#समावेश <net/genetlink.h>

#समावेश "br_private.h"
#समावेश "br_private_cfm.h"

अटल स्थिर काष्ठा nla_policy
br_cfm_mep_create_policy[IFLA_BRIDGE_CFM_MEP_CREATE_MAX + 1] = अणु
	[IFLA_BRIDGE_CFM_MEP_CREATE_UNSPEC]	= अणु .type = NLA_REJECT पूर्ण,
	[IFLA_BRIDGE_CFM_MEP_CREATE_INSTANCE]	= अणु .type = NLA_U32 पूर्ण,
	[IFLA_BRIDGE_CFM_MEP_CREATE_DOMAIN]	= अणु .type = NLA_U32 पूर्ण,
	[IFLA_BRIDGE_CFM_MEP_CREATE_सूचीECTION]	= अणु .type = NLA_U32 पूर्ण,
	[IFLA_BRIDGE_CFM_MEP_CREATE_IFINDEX]	= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nla_policy
br_cfm_mep_delete_policy[IFLA_BRIDGE_CFM_MEP_DELETE_MAX + 1] = अणु
	[IFLA_BRIDGE_CFM_MEP_DELETE_UNSPEC]	= अणु .type = NLA_REJECT पूर्ण,
	[IFLA_BRIDGE_CFM_MEP_DELETE_INSTANCE]	= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nla_policy
br_cfm_mep_config_policy[IFLA_BRIDGE_CFM_MEP_CONFIG_MAX + 1] = अणु
	[IFLA_BRIDGE_CFM_MEP_CONFIG_UNSPEC]	 = अणु .type = NLA_REJECT पूर्ण,
	[IFLA_BRIDGE_CFM_MEP_CONFIG_INSTANCE]	 = अणु .type = NLA_U32 पूर्ण,
	[IFLA_BRIDGE_CFM_MEP_CONFIG_UNICAST_MAC] = NLA_POLICY_ETH_ADDR,
	[IFLA_BRIDGE_CFM_MEP_CONFIG_MDLEVEL]	 = NLA_POLICY_MAX(NLA_U32, 7),
	[IFLA_BRIDGE_CFM_MEP_CONFIG_MEPID]	 = NLA_POLICY_MAX(NLA_U32, 0x1FFF),
पूर्ण;

अटल स्थिर काष्ठा nla_policy
br_cfm_cc_config_policy[IFLA_BRIDGE_CFM_CC_CONFIG_MAX + 1] = अणु
	[IFLA_BRIDGE_CFM_CC_CONFIG_UNSPEC]	 = अणु .type = NLA_REJECT पूर्ण,
	[IFLA_BRIDGE_CFM_CC_CONFIG_INSTANCE]	 = अणु .type = NLA_U32 पूर्ण,
	[IFLA_BRIDGE_CFM_CC_CONFIG_ENABLE]	 = अणु .type = NLA_U32 पूर्ण,
	[IFLA_BRIDGE_CFM_CC_CONFIG_EXP_INTERVAL] = अणु .type = NLA_U32 पूर्ण,
	[IFLA_BRIDGE_CFM_CC_CONFIG_EXP_MAID]	 = अणु
	.type = NLA_BINARY, .len = CFM_MAID_LENGTH पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nla_policy
br_cfm_cc_peer_mep_policy[IFLA_BRIDGE_CFM_CC_PEER_MEP_MAX + 1] = अणु
	[IFLA_BRIDGE_CFM_CC_PEER_MEP_UNSPEC]	= अणु .type = NLA_REJECT पूर्ण,
	[IFLA_BRIDGE_CFM_CC_PEER_MEP_INSTANCE]	= अणु .type = NLA_U32 पूर्ण,
	[IFLA_BRIDGE_CFM_CC_PEER_MEPID]		= NLA_POLICY_MAX(NLA_U32, 0x1FFF),
पूर्ण;

अटल स्थिर काष्ठा nla_policy
br_cfm_cc_rdi_policy[IFLA_BRIDGE_CFM_CC_RDI_MAX + 1] = अणु
	[IFLA_BRIDGE_CFM_CC_RDI_UNSPEC]		= अणु .type = NLA_REJECT पूर्ण,
	[IFLA_BRIDGE_CFM_CC_RDI_INSTANCE]	= अणु .type = NLA_U32 पूर्ण,
	[IFLA_BRIDGE_CFM_CC_RDI_RDI]		= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nla_policy
br_cfm_cc_ccm_tx_policy[IFLA_BRIDGE_CFM_CC_CCM_TX_MAX + 1] = अणु
	[IFLA_BRIDGE_CFM_CC_CCM_TX_UNSPEC]	   = अणु .type = NLA_REJECT पूर्ण,
	[IFLA_BRIDGE_CFM_CC_CCM_TX_INSTANCE]	   = अणु .type = NLA_U32 पूर्ण,
	[IFLA_BRIDGE_CFM_CC_CCM_TX_DMAC]	   = NLA_POLICY_ETH_ADDR,
	[IFLA_BRIDGE_CFM_CC_CCM_TX_SEQ_NO_UPDATE]  = अणु .type = NLA_U32 पूर्ण,
	[IFLA_BRIDGE_CFM_CC_CCM_TX_PERIOD]	   = अणु .type = NLA_U32 पूर्ण,
	[IFLA_BRIDGE_CFM_CC_CCM_TX_IF_TLV]	   = अणु .type = NLA_U32 पूर्ण,
	[IFLA_BRIDGE_CFM_CC_CCM_TX_IF_TLV_VALUE]   = अणु .type = NLA_U8 पूर्ण,
	[IFLA_BRIDGE_CFM_CC_CCM_TX_PORT_TLV]	   = अणु .type = NLA_U32 पूर्ण,
	[IFLA_BRIDGE_CFM_CC_CCM_TX_PORT_TLV_VALUE] = अणु .type = NLA_U8 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nla_policy
br_cfm_policy[IFLA_BRIDGE_CFM_MAX + 1] = अणु
	[IFLA_BRIDGE_CFM_UNSPEC]		= अणु .type = NLA_REJECT पूर्ण,
	[IFLA_BRIDGE_CFM_MEP_CREATE]		=
				NLA_POLICY_NESTED(br_cfm_mep_create_policy),
	[IFLA_BRIDGE_CFM_MEP_DELETE]		=
				NLA_POLICY_NESTED(br_cfm_mep_delete_policy),
	[IFLA_BRIDGE_CFM_MEP_CONFIG]		=
				NLA_POLICY_NESTED(br_cfm_mep_config_policy),
	[IFLA_BRIDGE_CFM_CC_CONFIG]		=
				NLA_POLICY_NESTED(br_cfm_cc_config_policy),
	[IFLA_BRIDGE_CFM_CC_PEER_MEP_ADD]	=
				NLA_POLICY_NESTED(br_cfm_cc_peer_mep_policy),
	[IFLA_BRIDGE_CFM_CC_PEER_MEP_REMOVE]	=
				NLA_POLICY_NESTED(br_cfm_cc_peer_mep_policy),
	[IFLA_BRIDGE_CFM_CC_RDI]		=
				NLA_POLICY_NESTED(br_cfm_cc_rdi_policy),
	[IFLA_BRIDGE_CFM_CC_CCM_TX]		=
				NLA_POLICY_NESTED(br_cfm_cc_ccm_tx_policy),
पूर्ण;

अटल पूर्णांक br_mep_create_parse(काष्ठा net_bridge *br, काष्ठा nlattr *attr,
			       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nlattr *tb[IFLA_BRIDGE_CFM_MEP_CREATE_MAX + 1];
	काष्ठा br_cfm_mep_create create;
	u32 instance;
	पूर्णांक err;

	err = nla_parse_nested(tb, IFLA_BRIDGE_CFM_MEP_CREATE_MAX, attr,
			       br_cfm_mep_create_policy, extack);
	अगर (err)
		वापस err;

	अगर (!tb[IFLA_BRIDGE_CFM_MEP_CREATE_INSTANCE]) अणु
		NL_SET_ERR_MSG_MOD(extack, "Missing INSTANCE attribute");
		वापस -EINVAL;
	पूर्ण
	अगर (!tb[IFLA_BRIDGE_CFM_MEP_CREATE_DOMAIN]) अणु
		NL_SET_ERR_MSG_MOD(extack, "Missing DOMAIN attribute");
		वापस -EINVAL;
	पूर्ण
	अगर (!tb[IFLA_BRIDGE_CFM_MEP_CREATE_सूचीECTION]) अणु
		NL_SET_ERR_MSG_MOD(extack, "Missing DIRECTION attribute");
		वापस -EINVAL;
	पूर्ण
	अगर (!tb[IFLA_BRIDGE_CFM_MEP_CREATE_IFINDEX]) अणु
		NL_SET_ERR_MSG_MOD(extack, "Missing IFINDEX attribute");
		वापस -EINVAL;
	पूर्ण

	स_रखो(&create, 0, माप(create));

	instance =  nla_get_u32(tb[IFLA_BRIDGE_CFM_MEP_CREATE_INSTANCE]);
	create.करोमुख्य = nla_get_u32(tb[IFLA_BRIDGE_CFM_MEP_CREATE_DOMAIN]);
	create.direction = nla_get_u32(tb[IFLA_BRIDGE_CFM_MEP_CREATE_सूचीECTION]);
	create.अगरindex = nla_get_u32(tb[IFLA_BRIDGE_CFM_MEP_CREATE_IFINDEX]);

	वापस br_cfm_mep_create(br, instance, &create, extack);
पूर्ण

अटल पूर्णांक br_mep_delete_parse(काष्ठा net_bridge *br, काष्ठा nlattr *attr,
			       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nlattr *tb[IFLA_BRIDGE_CFM_MEP_DELETE_MAX + 1];
	u32 instance;
	पूर्णांक err;

	err = nla_parse_nested(tb, IFLA_BRIDGE_CFM_MEP_DELETE_MAX, attr,
			       br_cfm_mep_delete_policy, extack);
	अगर (err)
		वापस err;

	अगर (!tb[IFLA_BRIDGE_CFM_MEP_DELETE_INSTANCE]) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "Missing INSTANCE attribute");
		वापस -EINVAL;
	पूर्ण

	instance =  nla_get_u32(tb[IFLA_BRIDGE_CFM_MEP_DELETE_INSTANCE]);

	वापस br_cfm_mep_delete(br, instance, extack);
पूर्ण

अटल पूर्णांक br_mep_config_parse(काष्ठा net_bridge *br, काष्ठा nlattr *attr,
			       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nlattr *tb[IFLA_BRIDGE_CFM_MEP_CONFIG_MAX + 1];
	काष्ठा br_cfm_mep_config config;
	u32 instance;
	पूर्णांक err;

	err = nla_parse_nested(tb, IFLA_BRIDGE_CFM_MEP_CONFIG_MAX, attr,
			       br_cfm_mep_config_policy, extack);
	अगर (err)
		वापस err;

	अगर (!tb[IFLA_BRIDGE_CFM_MEP_CONFIG_INSTANCE]) अणु
		NL_SET_ERR_MSG_MOD(extack, "Missing INSTANCE attribute");
		वापस -EINVAL;
	पूर्ण
	अगर (!tb[IFLA_BRIDGE_CFM_MEP_CONFIG_UNICAST_MAC]) अणु
		NL_SET_ERR_MSG_MOD(extack, "Missing UNICAST_MAC attribute");
		वापस -EINVAL;
	पूर्ण
	अगर (!tb[IFLA_BRIDGE_CFM_MEP_CONFIG_MDLEVEL]) अणु
		NL_SET_ERR_MSG_MOD(extack, "Missing MDLEVEL attribute");
		वापस -EINVAL;
	पूर्ण
	अगर (!tb[IFLA_BRIDGE_CFM_MEP_CONFIG_MEPID]) अणु
		NL_SET_ERR_MSG_MOD(extack, "Missing MEPID attribute");
		वापस -EINVAL;
	पूर्ण

	स_रखो(&config, 0, माप(config));

	instance =  nla_get_u32(tb[IFLA_BRIDGE_CFM_MEP_CONFIG_INSTANCE]);
	nla_स_नकल(&config.unicast_mac.addr,
		   tb[IFLA_BRIDGE_CFM_MEP_CONFIG_UNICAST_MAC],
		   माप(config.unicast_mac.addr));
	config.mdlevel = nla_get_u32(tb[IFLA_BRIDGE_CFM_MEP_CONFIG_MDLEVEL]);
	config.mepid = nla_get_u32(tb[IFLA_BRIDGE_CFM_MEP_CONFIG_MEPID]);

	वापस br_cfm_mep_config_set(br, instance, &config, extack);
पूर्ण

अटल पूर्णांक br_cc_config_parse(काष्ठा net_bridge *br, काष्ठा nlattr *attr,
			      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nlattr *tb[IFLA_BRIDGE_CFM_CC_CONFIG_MAX + 1];
	काष्ठा br_cfm_cc_config config;
	u32 instance;
	पूर्णांक err;

	err = nla_parse_nested(tb, IFLA_BRIDGE_CFM_CC_CONFIG_MAX, attr,
			       br_cfm_cc_config_policy, extack);
	अगर (err)
		वापस err;

	अगर (!tb[IFLA_BRIDGE_CFM_CC_CONFIG_INSTANCE]) अणु
		NL_SET_ERR_MSG_MOD(extack, "Missing INSTANCE attribute");
		वापस -EINVAL;
	पूर्ण
	अगर (!tb[IFLA_BRIDGE_CFM_CC_CONFIG_ENABLE]) अणु
		NL_SET_ERR_MSG_MOD(extack, "Missing ENABLE attribute");
		वापस -EINVAL;
	पूर्ण
	अगर (!tb[IFLA_BRIDGE_CFM_CC_CONFIG_EXP_INTERVAL]) अणु
		NL_SET_ERR_MSG_MOD(extack, "Missing INTERVAL attribute");
		वापस -EINVAL;
	पूर्ण
	अगर (!tb[IFLA_BRIDGE_CFM_CC_CONFIG_EXP_MAID]) अणु
		NL_SET_ERR_MSG_MOD(extack, "Missing MAID attribute");
		वापस -EINVAL;
	पूर्ण

	स_रखो(&config, 0, माप(config));

	instance =  nla_get_u32(tb[IFLA_BRIDGE_CFM_CC_CONFIG_INSTANCE]);
	config.enable = nla_get_u32(tb[IFLA_BRIDGE_CFM_CC_CONFIG_ENABLE]);
	config.exp_पूर्णांकerval = nla_get_u32(tb[IFLA_BRIDGE_CFM_CC_CONFIG_EXP_INTERVAL]);
	nla_स_नकल(&config.exp_maid.data, tb[IFLA_BRIDGE_CFM_CC_CONFIG_EXP_MAID],
		   माप(config.exp_maid.data));

	वापस br_cfm_cc_config_set(br, instance, &config, extack);
पूर्ण

अटल पूर्णांक br_cc_peer_mep_add_parse(काष्ठा net_bridge *br, काष्ठा nlattr *attr,
				    काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nlattr *tb[IFLA_BRIDGE_CFM_CC_PEER_MEP_MAX + 1];
	u32 instance, peer_mep_id;
	पूर्णांक err;

	err = nla_parse_nested(tb, IFLA_BRIDGE_CFM_CC_PEER_MEP_MAX, attr,
			       br_cfm_cc_peer_mep_policy, extack);
	अगर (err)
		वापस err;

	अगर (!tb[IFLA_BRIDGE_CFM_CC_PEER_MEP_INSTANCE]) अणु
		NL_SET_ERR_MSG_MOD(extack, "Missing INSTANCE attribute");
		वापस -EINVAL;
	पूर्ण
	अगर (!tb[IFLA_BRIDGE_CFM_CC_PEER_MEPID]) अणु
		NL_SET_ERR_MSG_MOD(extack, "Missing PEER_MEP_ID attribute");
		वापस -EINVAL;
	पूर्ण

	instance =  nla_get_u32(tb[IFLA_BRIDGE_CFM_CC_PEER_MEP_INSTANCE]);
	peer_mep_id =  nla_get_u32(tb[IFLA_BRIDGE_CFM_CC_PEER_MEPID]);

	वापस br_cfm_cc_peer_mep_add(br, instance, peer_mep_id, extack);
पूर्ण

अटल पूर्णांक br_cc_peer_mep_हटाओ_parse(काष्ठा net_bridge *br, काष्ठा nlattr *attr,
				       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nlattr *tb[IFLA_BRIDGE_CFM_CC_PEER_MEP_MAX + 1];
	u32 instance, peer_mep_id;
	पूर्णांक err;

	err = nla_parse_nested(tb, IFLA_BRIDGE_CFM_CC_PEER_MEP_MAX, attr,
			       br_cfm_cc_peer_mep_policy, extack);
	अगर (err)
		वापस err;

	अगर (!tb[IFLA_BRIDGE_CFM_CC_PEER_MEP_INSTANCE]) अणु
		NL_SET_ERR_MSG_MOD(extack, "Missing INSTANCE attribute");
		वापस -EINVAL;
	पूर्ण
	अगर (!tb[IFLA_BRIDGE_CFM_CC_PEER_MEPID]) अणु
		NL_SET_ERR_MSG_MOD(extack, "Missing PEER_MEP_ID attribute");
		वापस -EINVAL;
	पूर्ण

	instance =  nla_get_u32(tb[IFLA_BRIDGE_CFM_CC_PEER_MEP_INSTANCE]);
	peer_mep_id =  nla_get_u32(tb[IFLA_BRIDGE_CFM_CC_PEER_MEPID]);

	वापस br_cfm_cc_peer_mep_हटाओ(br, instance, peer_mep_id, extack);
पूर्ण

अटल पूर्णांक br_cc_rdi_parse(काष्ठा net_bridge *br, काष्ठा nlattr *attr,
			   काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nlattr *tb[IFLA_BRIDGE_CFM_CC_RDI_MAX + 1];
	u32 instance, rdi;
	पूर्णांक err;

	err = nla_parse_nested(tb, IFLA_BRIDGE_CFM_CC_RDI_MAX, attr,
			       br_cfm_cc_rdi_policy, extack);
	अगर (err)
		वापस err;

	अगर (!tb[IFLA_BRIDGE_CFM_CC_RDI_INSTANCE]) अणु
		NL_SET_ERR_MSG_MOD(extack, "Missing INSTANCE attribute");
		वापस -EINVAL;
	पूर्ण
	अगर (!tb[IFLA_BRIDGE_CFM_CC_RDI_RDI]) अणु
		NL_SET_ERR_MSG_MOD(extack, "Missing RDI attribute");
		वापस -EINVAL;
	पूर्ण

	instance =  nla_get_u32(tb[IFLA_BRIDGE_CFM_CC_RDI_INSTANCE]);
	rdi =  nla_get_u32(tb[IFLA_BRIDGE_CFM_CC_RDI_RDI]);

	वापस br_cfm_cc_rdi_set(br, instance, rdi, extack);
पूर्ण

अटल पूर्णांक br_cc_ccm_tx_parse(काष्ठा net_bridge *br, काष्ठा nlattr *attr,
			      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nlattr *tb[IFLA_BRIDGE_CFM_CC_CCM_TX_MAX + 1];
	काष्ठा br_cfm_cc_ccm_tx_info tx_info;
	u32 instance;
	पूर्णांक err;

	err = nla_parse_nested(tb, IFLA_BRIDGE_CFM_CC_CCM_TX_MAX, attr,
			       br_cfm_cc_ccm_tx_policy, extack);
	अगर (err)
		वापस err;

	अगर (!tb[IFLA_BRIDGE_CFM_CC_CCM_TX_INSTANCE]) अणु
		NL_SET_ERR_MSG_MOD(extack, "Missing INSTANCE attribute");
		वापस -EINVAL;
	पूर्ण
	अगर (!tb[IFLA_BRIDGE_CFM_CC_CCM_TX_DMAC]) अणु
		NL_SET_ERR_MSG_MOD(extack, "Missing DMAC attribute");
		वापस -EINVAL;
	पूर्ण
	अगर (!tb[IFLA_BRIDGE_CFM_CC_CCM_TX_SEQ_NO_UPDATE]) अणु
		NL_SET_ERR_MSG_MOD(extack, "Missing SEQ_NO_UPDATE attribute");
		वापस -EINVAL;
	पूर्ण
	अगर (!tb[IFLA_BRIDGE_CFM_CC_CCM_TX_PERIOD]) अणु
		NL_SET_ERR_MSG_MOD(extack, "Missing PERIOD attribute");
		वापस -EINVAL;
	पूर्ण
	अगर (!tb[IFLA_BRIDGE_CFM_CC_CCM_TX_IF_TLV]) अणु
		NL_SET_ERR_MSG_MOD(extack, "Missing IF_TLV attribute");
		वापस -EINVAL;
	पूर्ण
	अगर (!tb[IFLA_BRIDGE_CFM_CC_CCM_TX_IF_TLV_VALUE]) अणु
		NL_SET_ERR_MSG_MOD(extack, "Missing IF_TLV_VALUE attribute");
		वापस -EINVAL;
	पूर्ण
	अगर (!tb[IFLA_BRIDGE_CFM_CC_CCM_TX_PORT_TLV]) अणु
		NL_SET_ERR_MSG_MOD(extack, "Missing PORT_TLV attribute");
		वापस -EINVAL;
	पूर्ण
	अगर (!tb[IFLA_BRIDGE_CFM_CC_CCM_TX_PORT_TLV_VALUE]) अणु
		NL_SET_ERR_MSG_MOD(extack, "Missing PORT_TLV_VALUE attribute");
		वापस -EINVAL;
	पूर्ण

	स_रखो(&tx_info, 0, माप(tx_info));

	instance = nla_get_u32(tb[IFLA_BRIDGE_CFM_CC_RDI_INSTANCE]);
	nla_स_नकल(&tx_info.dmac.addr,
		   tb[IFLA_BRIDGE_CFM_CC_CCM_TX_DMAC],
		   माप(tx_info.dmac.addr));
	tx_info.seq_no_update = nla_get_u32(tb[IFLA_BRIDGE_CFM_CC_CCM_TX_SEQ_NO_UPDATE]);
	tx_info.period = nla_get_u32(tb[IFLA_BRIDGE_CFM_CC_CCM_TX_PERIOD]);
	tx_info.अगर_tlv = nla_get_u32(tb[IFLA_BRIDGE_CFM_CC_CCM_TX_IF_TLV]);
	tx_info.अगर_tlv_value = nla_get_u8(tb[IFLA_BRIDGE_CFM_CC_CCM_TX_IF_TLV_VALUE]);
	tx_info.port_tlv = nla_get_u32(tb[IFLA_BRIDGE_CFM_CC_CCM_TX_PORT_TLV]);
	tx_info.port_tlv_value = nla_get_u8(tb[IFLA_BRIDGE_CFM_CC_CCM_TX_PORT_TLV_VALUE]);

	वापस br_cfm_cc_ccm_tx(br, instance, &tx_info, extack);
पूर्ण

पूर्णांक br_cfm_parse(काष्ठा net_bridge *br, काष्ठा net_bridge_port *p,
		 काष्ठा nlattr *attr, पूर्णांक cmd, काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nlattr *tb[IFLA_BRIDGE_CFM_MAX + 1];
	पूर्णांक err;

	/* When this function is called क्रम a port then the br poपूर्णांकer is
	 * invalid, thereक्रम set the br to poपूर्णांक correctly
	 */
	अगर (p)
		br = p->br;

	err = nla_parse_nested(tb, IFLA_BRIDGE_CFM_MAX, attr,
			       br_cfm_policy, extack);
	अगर (err)
		वापस err;

	अगर (tb[IFLA_BRIDGE_CFM_MEP_CREATE]) अणु
		err = br_mep_create_parse(br, tb[IFLA_BRIDGE_CFM_MEP_CREATE],
					  extack);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (tb[IFLA_BRIDGE_CFM_MEP_DELETE]) अणु
		err = br_mep_delete_parse(br, tb[IFLA_BRIDGE_CFM_MEP_DELETE],
					  extack);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (tb[IFLA_BRIDGE_CFM_MEP_CONFIG]) अणु
		err = br_mep_config_parse(br, tb[IFLA_BRIDGE_CFM_MEP_CONFIG],
					  extack);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (tb[IFLA_BRIDGE_CFM_CC_CONFIG]) अणु
		err = br_cc_config_parse(br, tb[IFLA_BRIDGE_CFM_CC_CONFIG],
					 extack);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (tb[IFLA_BRIDGE_CFM_CC_PEER_MEP_ADD]) अणु
		err = br_cc_peer_mep_add_parse(br, tb[IFLA_BRIDGE_CFM_CC_PEER_MEP_ADD],
					       extack);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (tb[IFLA_BRIDGE_CFM_CC_PEER_MEP_REMOVE]) अणु
		err = br_cc_peer_mep_हटाओ_parse(br, tb[IFLA_BRIDGE_CFM_CC_PEER_MEP_REMOVE],
						  extack);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (tb[IFLA_BRIDGE_CFM_CC_RDI]) अणु
		err = br_cc_rdi_parse(br, tb[IFLA_BRIDGE_CFM_CC_RDI],
				      extack);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (tb[IFLA_BRIDGE_CFM_CC_CCM_TX]) अणु
		err = br_cc_ccm_tx_parse(br, tb[IFLA_BRIDGE_CFM_CC_CCM_TX],
					 extack);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक br_cfm_config_fill_info(काष्ठा sk_buff *skb, काष्ठा net_bridge *br)
अणु
	काष्ठा br_cfm_peer_mep *peer_mep;
	काष्ठा br_cfm_mep *mep;
	काष्ठा nlattr *tb;

	hlist_क्रम_each_entry_rcu(mep, &br->mep_list, head) अणु
		tb = nla_nest_start(skb, IFLA_BRIDGE_CFM_MEP_CREATE_INFO);
		अगर (!tb)
			जाओ nla_info_failure;

		अगर (nla_put_u32(skb, IFLA_BRIDGE_CFM_MEP_CREATE_INSTANCE,
				mep->instance))
			जाओ nla_put_failure;

		अगर (nla_put_u32(skb, IFLA_BRIDGE_CFM_MEP_CREATE_DOMAIN,
				mep->create.करोमुख्य))
			जाओ nla_put_failure;

		अगर (nla_put_u32(skb, IFLA_BRIDGE_CFM_MEP_CREATE_सूचीECTION,
				mep->create.direction))
			जाओ nla_put_failure;

		अगर (nla_put_u32(skb, IFLA_BRIDGE_CFM_MEP_CREATE_IFINDEX,
				mep->create.अगरindex))
			जाओ nla_put_failure;

		nla_nest_end(skb, tb);

		tb = nla_nest_start(skb, IFLA_BRIDGE_CFM_MEP_CONFIG_INFO);

		अगर (!tb)
			जाओ nla_info_failure;

		अगर (nla_put_u32(skb, IFLA_BRIDGE_CFM_MEP_CONFIG_INSTANCE,
				mep->instance))
			जाओ nla_put_failure;

		अगर (nla_put(skb, IFLA_BRIDGE_CFM_MEP_CONFIG_UNICAST_MAC,
			    माप(mep->config.unicast_mac.addr),
			    mep->config.unicast_mac.addr))
			जाओ nla_put_failure;

		अगर (nla_put_u32(skb, IFLA_BRIDGE_CFM_MEP_CONFIG_MDLEVEL,
				mep->config.mdlevel))
			जाओ nla_put_failure;

		अगर (nla_put_u32(skb, IFLA_BRIDGE_CFM_MEP_CONFIG_MEPID,
				mep->config.mepid))
			जाओ nla_put_failure;

		nla_nest_end(skb, tb);

		tb = nla_nest_start(skb, IFLA_BRIDGE_CFM_CC_CONFIG_INFO);

		अगर (!tb)
			जाओ nla_info_failure;

		अगर (nla_put_u32(skb, IFLA_BRIDGE_CFM_CC_CONFIG_INSTANCE,
				mep->instance))
			जाओ nla_put_failure;

		अगर (nla_put_u32(skb, IFLA_BRIDGE_CFM_CC_CONFIG_ENABLE,
				mep->cc_config.enable))
			जाओ nla_put_failure;

		अगर (nla_put_u32(skb, IFLA_BRIDGE_CFM_CC_CONFIG_EXP_INTERVAL,
				mep->cc_config.exp_पूर्णांकerval))
			जाओ nla_put_failure;

		अगर (nla_put(skb, IFLA_BRIDGE_CFM_CC_CONFIG_EXP_MAID,
			    माप(mep->cc_config.exp_maid.data),
			    mep->cc_config.exp_maid.data))
			जाओ nla_put_failure;

		nla_nest_end(skb, tb);

		tb = nla_nest_start(skb, IFLA_BRIDGE_CFM_CC_RDI_INFO);

		अगर (!tb)
			जाओ nla_info_failure;

		अगर (nla_put_u32(skb, IFLA_BRIDGE_CFM_CC_RDI_INSTANCE,
				mep->instance))
			जाओ nla_put_failure;

		अगर (nla_put_u32(skb, IFLA_BRIDGE_CFM_CC_RDI_RDI,
				mep->rdi))
			जाओ nla_put_failure;

		nla_nest_end(skb, tb);

		tb = nla_nest_start(skb, IFLA_BRIDGE_CFM_CC_CCM_TX_INFO);

		अगर (!tb)
			जाओ nla_info_failure;

		अगर (nla_put_u32(skb, IFLA_BRIDGE_CFM_CC_CCM_TX_INSTANCE,
				mep->instance))
			जाओ nla_put_failure;

		अगर (nla_put(skb, IFLA_BRIDGE_CFM_CC_CCM_TX_DMAC,
			    माप(mep->cc_ccm_tx_info.dmac),
			    mep->cc_ccm_tx_info.dmac.addr))
			जाओ nla_put_failure;

		अगर (nla_put_u32(skb, IFLA_BRIDGE_CFM_CC_CCM_TX_SEQ_NO_UPDATE,
				mep->cc_ccm_tx_info.seq_no_update))
			जाओ nla_put_failure;

		अगर (nla_put_u32(skb, IFLA_BRIDGE_CFM_CC_CCM_TX_PERIOD,
				mep->cc_ccm_tx_info.period))
			जाओ nla_put_failure;

		अगर (nla_put_u32(skb, IFLA_BRIDGE_CFM_CC_CCM_TX_IF_TLV,
				mep->cc_ccm_tx_info.अगर_tlv))
			जाओ nla_put_failure;

		अगर (nla_put_u8(skb, IFLA_BRIDGE_CFM_CC_CCM_TX_IF_TLV_VALUE,
			       mep->cc_ccm_tx_info.अगर_tlv_value))
			जाओ nla_put_failure;

		अगर (nla_put_u32(skb, IFLA_BRIDGE_CFM_CC_CCM_TX_PORT_TLV,
				mep->cc_ccm_tx_info.port_tlv))
			जाओ nla_put_failure;

		अगर (nla_put_u8(skb, IFLA_BRIDGE_CFM_CC_CCM_TX_PORT_TLV_VALUE,
			       mep->cc_ccm_tx_info.port_tlv_value))
			जाओ nla_put_failure;

		nla_nest_end(skb, tb);

		hlist_क्रम_each_entry_rcu(peer_mep, &mep->peer_mep_list, head) अणु
			tb = nla_nest_start(skb,
					    IFLA_BRIDGE_CFM_CC_PEER_MEP_INFO);

			अगर (!tb)
				जाओ nla_info_failure;

			अगर (nla_put_u32(skb,
					IFLA_BRIDGE_CFM_CC_PEER_MEP_INSTANCE,
					mep->instance))
				जाओ nla_put_failure;

			अगर (nla_put_u32(skb, IFLA_BRIDGE_CFM_CC_PEER_MEPID,
					peer_mep->mepid))
				जाओ nla_put_failure;

			nla_nest_end(skb, tb);
		पूर्ण
	पूर्ण

	वापस 0;

nla_put_failure:
	nla_nest_cancel(skb, tb);

nla_info_failure:
	वापस -EMSGSIZE;
पूर्ण

पूर्णांक br_cfm_status_fill_info(काष्ठा sk_buff *skb,
			    काष्ठा net_bridge *br,
			    bool getlink)
अणु
	काष्ठा br_cfm_peer_mep *peer_mep;
	काष्ठा br_cfm_mep *mep;
	काष्ठा nlattr *tb;

	hlist_क्रम_each_entry_rcu(mep, &br->mep_list, head) अणु
		tb = nla_nest_start(skb, IFLA_BRIDGE_CFM_MEP_STATUS_INFO);
		अगर (!tb)
			जाओ nla_info_failure;

		अगर (nla_put_u32(skb, IFLA_BRIDGE_CFM_MEP_STATUS_INSTANCE,
				mep->instance))
			जाओ nla_put_failure;

		अगर (nla_put_u32(skb,
				IFLA_BRIDGE_CFM_MEP_STATUS_OPCODE_UNEXP_SEEN,
				mep->status.opcode_unexp_seen))
			जाओ nla_put_failure;

		अगर (nla_put_u32(skb,
				IFLA_BRIDGE_CFM_MEP_STATUS_VERSION_UNEXP_SEEN,
				mep->status.version_unexp_seen))
			जाओ nla_put_failure;

		अगर (nla_put_u32(skb,
				IFLA_BRIDGE_CFM_MEP_STATUS_RX_LEVEL_LOW_SEEN,
				mep->status.rx_level_low_seen))
			जाओ nla_put_failure;

		/* Only clear अगर this is a GETLINK */
		अगर (getlink) अणु
			/* Clear all 'seen' indications */
			mep->status.opcode_unexp_seen = false;
			mep->status.version_unexp_seen = false;
			mep->status.rx_level_low_seen = false;
		पूर्ण

		nla_nest_end(skb, tb);

		hlist_क्रम_each_entry_rcu(peer_mep, &mep->peer_mep_list, head) अणु
			tb = nla_nest_start(skb,
					    IFLA_BRIDGE_CFM_CC_PEER_STATUS_INFO);
			अगर (!tb)
				जाओ nla_info_failure;

			अगर (nla_put_u32(skb,
					IFLA_BRIDGE_CFM_CC_PEER_STATUS_INSTANCE,
					mep->instance))
				जाओ nla_put_failure;

			अगर (nla_put_u32(skb,
					IFLA_BRIDGE_CFM_CC_PEER_STATUS_PEER_MEPID,
					peer_mep->mepid))
				जाओ nla_put_failure;

			अगर (nla_put_u32(skb,
					IFLA_BRIDGE_CFM_CC_PEER_STATUS_CCM_DEFECT,
					peer_mep->cc_status.ccm_defect))
				जाओ nla_put_failure;

			अगर (nla_put_u32(skb, IFLA_BRIDGE_CFM_CC_PEER_STATUS_RDI,
					peer_mep->cc_status.rdi))
				जाओ nla_put_failure;

			अगर (nla_put_u8(skb,
				       IFLA_BRIDGE_CFM_CC_PEER_STATUS_PORT_TLV_VALUE,
				       peer_mep->cc_status.port_tlv_value))
				जाओ nla_put_failure;

			अगर (nla_put_u8(skb,
				       IFLA_BRIDGE_CFM_CC_PEER_STATUS_IF_TLV_VALUE,
				       peer_mep->cc_status.अगर_tlv_value))
				जाओ nla_put_failure;

			अगर (nla_put_u32(skb,
					IFLA_BRIDGE_CFM_CC_PEER_STATUS_SEEN,
					peer_mep->cc_status.seen))
				जाओ nla_put_failure;

			अगर (nla_put_u32(skb,
					IFLA_BRIDGE_CFM_CC_PEER_STATUS_TLV_SEEN,
					peer_mep->cc_status.tlv_seen))
				जाओ nla_put_failure;

			अगर (nla_put_u32(skb,
					IFLA_BRIDGE_CFM_CC_PEER_STATUS_SEQ_UNEXP_SEEN,
					peer_mep->cc_status.seq_unexp_seen))
				जाओ nla_put_failure;

			अगर (getlink) अणु /* Only clear अगर this is a GETLINK */
				/* Clear all 'seen' indications */
				peer_mep->cc_status.seen = false;
				peer_mep->cc_status.tlv_seen = false;
				peer_mep->cc_status.seq_unexp_seen = false;
			पूर्ण

			nla_nest_end(skb, tb);
		पूर्ण
	पूर्ण

	वापस 0;

nla_put_failure:
	nla_nest_cancel(skb, tb);

nla_info_failure:
	वापस -EMSGSIZE;
पूर्ण
