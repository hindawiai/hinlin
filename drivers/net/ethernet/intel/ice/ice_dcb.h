<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (c) 2019, Intel Corporation. */

#अगर_अघोषित _ICE_DCB_H_
#घोषणा _ICE_DCB_H_

#समावेश "ice_type.h"

#घोषणा ICE_DCBX_STATUS_NOT_STARTED	0
#घोषणा ICE_DCBX_STATUS_IN_PROGRESS	1
#घोषणा ICE_DCBX_STATUS_DONE		2
#घोषणा ICE_DCBX_STATUS_DIS		7

#घोषणा ICE_TLV_TYPE_END		0
#घोषणा ICE_TLV_TYPE_ORG		127

#घोषणा ICE_IEEE_8021QAZ_OUI		0x0080C2
#घोषणा ICE_IEEE_SUBTYPE_ETS_CFG	9
#घोषणा ICE_IEEE_SUBTYPE_ETS_REC	10
#घोषणा ICE_IEEE_SUBTYPE_PFC_CFG	11
#घोषणा ICE_IEEE_SUBTYPE_APP_PRI	12

#घोषणा ICE_CEE_DCBX_OUI		0x001B21
#घोषणा ICE_CEE_DCBX_TYPE		2
#घोषणा ICE_CEE_SUBTYPE_PG_CFG		2
#घोषणा ICE_CEE_SUBTYPE_PFC_CFG		3
#घोषणा ICE_CEE_SUBTYPE_APP_PRI		4
#घोषणा ICE_CEE_MAX_FEAT_TYPE		3
/* Defines क्रम LLDP TLV header */
#घोषणा ICE_LLDP_TLV_LEN_S		0
#घोषणा ICE_LLDP_TLV_LEN_M		(0x01FF << ICE_LLDP_TLV_LEN_S)
#घोषणा ICE_LLDP_TLV_TYPE_S		9
#घोषणा ICE_LLDP_TLV_TYPE_M		(0x7F << ICE_LLDP_TLV_TYPE_S)
#घोषणा ICE_LLDP_TLV_SUBTYPE_S		0
#घोषणा ICE_LLDP_TLV_SUBTYPE_M		(0xFF << ICE_LLDP_TLV_SUBTYPE_S)
#घोषणा ICE_LLDP_TLV_OUI_S		8
#घोषणा ICE_LLDP_TLV_OUI_M		(0xFFFFFFUL << ICE_LLDP_TLV_OUI_S)

/* Defines क्रम IEEE ETS TLV */
#घोषणा ICE_IEEE_ETS_MAXTC_S	0
#घोषणा ICE_IEEE_ETS_MAXTC_M		(0x7 << ICE_IEEE_ETS_MAXTC_S)
#घोषणा ICE_IEEE_ETS_CBS_S		6
#घोषणा ICE_IEEE_ETS_CBS_M		BIT(ICE_IEEE_ETS_CBS_S)
#घोषणा ICE_IEEE_ETS_WILLING_S		7
#घोषणा ICE_IEEE_ETS_WILLING_M		BIT(ICE_IEEE_ETS_WILLING_S)
#घोषणा ICE_IEEE_ETS_PRIO_0_S		0
#घोषणा ICE_IEEE_ETS_PRIO_0_M		(0x7 << ICE_IEEE_ETS_PRIO_0_S)
#घोषणा ICE_IEEE_ETS_PRIO_1_S		4
#घोषणा ICE_IEEE_ETS_PRIO_1_M		(0x7 << ICE_IEEE_ETS_PRIO_1_S)
#घोषणा ICE_CEE_PGID_PRIO_0_S		0
#घोषणा ICE_CEE_PGID_PRIO_0_M		(0xF << ICE_CEE_PGID_PRIO_0_S)
#घोषणा ICE_CEE_PGID_PRIO_1_S		4
#घोषणा ICE_CEE_PGID_PRIO_1_M		(0xF << ICE_CEE_PGID_PRIO_1_S)
#घोषणा ICE_CEE_PGID_STRICT		15

/* Defines क्रम IEEE TSA types */
#घोषणा ICE_IEEE_TSA_STRICT		0
#घोषणा ICE_IEEE_TSA_ETS		2

/* Defines क्रम IEEE PFC TLV */
#घोषणा ICE_IEEE_PFC_CAP_S		0
#घोषणा ICE_IEEE_PFC_CAP_M		(0xF << ICE_IEEE_PFC_CAP_S)
#घोषणा ICE_IEEE_PFC_MBC_S		6
#घोषणा ICE_IEEE_PFC_MBC_M		BIT(ICE_IEEE_PFC_MBC_S)
#घोषणा ICE_IEEE_PFC_WILLING_S		7
#घोषणा ICE_IEEE_PFC_WILLING_M		BIT(ICE_IEEE_PFC_WILLING_S)

/* Defines क्रम IEEE APP TLV */
#घोषणा ICE_IEEE_APP_SEL_S		0
#घोषणा ICE_IEEE_APP_SEL_M		(0x7 << ICE_IEEE_APP_SEL_S)
#घोषणा ICE_IEEE_APP_PRIO_S		5
#घोषणा ICE_IEEE_APP_PRIO_M		(0x7 << ICE_IEEE_APP_PRIO_S)

/* TLV definitions क्रम preparing MIB */
#घोषणा ICE_IEEE_TLV_ID_ETS_CFG		3
#घोषणा ICE_IEEE_TLV_ID_ETS_REC		4
#घोषणा ICE_IEEE_TLV_ID_PFC_CFG		5
#घोषणा ICE_IEEE_TLV_ID_APP_PRI		6
#घोषणा ICE_TLV_ID_END_OF_LLDPPDU	7
#घोषणा ICE_TLV_ID_START		ICE_IEEE_TLV_ID_ETS_CFG

#घोषणा ICE_IEEE_ETS_TLV_LEN		25
#घोषणा ICE_IEEE_PFC_TLV_LEN		6
#घोषणा ICE_IEEE_APP_TLV_LEN		11

/* IEEE 802.1AB LLDP Organization specअगरic TLV */
काष्ठा ice_lldp_org_tlv अणु
	__be16 typelen;
	__be32 ouisubtype;
	u8 tlvinfo[];
पूर्ण __packed;

काष्ठा ice_cee_tlv_hdr अणु
	__be16 typelen;
	u8 operver;
	u8 maxver;
पूर्ण;

काष्ठा ice_cee_ctrl_tlv अणु
	काष्ठा ice_cee_tlv_hdr hdr;
	__be32 seqno;
	__be32 ackno;
पूर्ण;

काष्ठा ice_cee_feat_tlv अणु
	काष्ठा ice_cee_tlv_hdr hdr;
	u8 en_will_err; /* Bits: |En|Will|Err|Reserved(5)| */
#घोषणा ICE_CEE_FEAT_TLV_ENA_M		0x80
#घोषणा ICE_CEE_FEAT_TLV_WILLING_M	0x40
#घोषणा ICE_CEE_FEAT_TLV_ERR_M		0x20
	u8 subtype;
	u8 tlvinfo[];
पूर्ण;

काष्ठा ice_cee_app_prio अणु
	__be16 protocol;
	u8 upper_oui_sel; /* Bits: |Upper OUI(6)|Selector(2)| */
#घोषणा ICE_CEE_APP_SELECTOR_M	0x03
	__be16 lower_oui;
	u8 prio_map;
पूर्ण __packed;

क्रमागत ice_status
ice_aq_get_dcb_cfg(काष्ठा ice_hw *hw, u8 mib_type, u8 bridgetype,
		   काष्ठा ice_dcbx_cfg *dcbcfg);
क्रमागत ice_status ice_get_dcb_cfg(काष्ठा ice_port_info *pi);
क्रमागत ice_status ice_set_dcb_cfg(काष्ठा ice_port_info *pi);
क्रमागत ice_status ice_init_dcb(काष्ठा ice_hw *hw, bool enable_mib_change);
क्रमागत ice_status
ice_query_port_ets(काष्ठा ice_port_info *pi,
		   काष्ठा ice_aqc_port_ets_elem *buf, u16 buf_size,
		   काष्ठा ice_sq_cd *cmd_details);
#अगर_घोषित CONFIG_DCB
क्रमागत ice_status
ice_aq_stop_lldp(काष्ठा ice_hw *hw, bool shutकरोwn_lldp_agent, bool persist,
		 काष्ठा ice_sq_cd *cd);
क्रमागत ice_status
ice_aq_start_lldp(काष्ठा ice_hw *hw, bool persist, काष्ठा ice_sq_cd *cd);
क्रमागत ice_status
ice_aq_start_stop_dcbx(काष्ठा ice_hw *hw, bool start_dcbx_agent,
		       bool *dcbx_agent_status, काष्ठा ice_sq_cd *cd);
क्रमागत ice_status ice_cfg_lldp_mib_change(काष्ठा ice_hw *hw, bool ena_mib);
#अन्यथा /* CONFIG_DCB */
अटल अंतरभूत क्रमागत ice_status
ice_aq_stop_lldp(काष्ठा ice_hw __always_unused *hw,
		 bool __always_unused shutकरोwn_lldp_agent,
		 bool __always_unused persist,
		 काष्ठा ice_sq_cd __always_unused *cd)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत क्रमागत ice_status
ice_aq_start_lldp(काष्ठा ice_hw __always_unused *hw,
		  bool __always_unused persist,
		  काष्ठा ice_sq_cd __always_unused *cd)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत क्रमागत ice_status
ice_aq_start_stop_dcbx(काष्ठा ice_hw __always_unused *hw,
		       bool __always_unused start_dcbx_agent,
		       bool *dcbx_agent_status,
		       काष्ठा ice_sq_cd __always_unused *cd)
अणु
	*dcbx_agent_status = false;

	वापस 0;
पूर्ण

अटल अंतरभूत क्रमागत ice_status
ice_cfg_lldp_mib_change(काष्ठा ice_hw __always_unused *hw,
			bool __always_unused ena_mib)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_DCB */
#पूर्ण_अगर /* _ICE_DCB_H_ */
