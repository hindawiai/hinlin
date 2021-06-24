<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2019, Intel Corporation. */

#समावेश "ice_common.h"
#समावेश "ice_sched.h"
#समावेश "ice_dcb.h"

/**
 * ice_aq_get_lldp_mib
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @bridge_type: type of bridge requested
 * @mib_type: Local, Remote or both Local and Remote MIBs
 * @buf: poपूर्णांकer to the caller-supplied buffer to store the MIB block
 * @buf_size: size of the buffer (in bytes)
 * @local_len: length of the वापसed Local LLDP MIB
 * @remote_len: length of the वापसed Remote LLDP MIB
 * @cd: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * Requests the complete LLDP MIB (entire packet). (0x0A00)
 */
अटल क्रमागत ice_status
ice_aq_get_lldp_mib(काष्ठा ice_hw *hw, u8 bridge_type, u8 mib_type, व्योम *buf,
		    u16 buf_size, u16 *local_len, u16 *remote_len,
		    काष्ठा ice_sq_cd *cd)
अणु
	काष्ठा ice_aqc_lldp_get_mib *cmd;
	काष्ठा ice_aq_desc desc;
	क्रमागत ice_status status;

	cmd = &desc.params.lldp_get_mib;

	अगर (buf_size == 0 || !buf)
		वापस ICE_ERR_PARAM;

	ice_fill_dflt_direct_cmd_desc(&desc, ice_aqc_opc_lldp_get_mib);

	cmd->type = mib_type & ICE_AQ_LLDP_MIB_TYPE_M;
	cmd->type |= (bridge_type << ICE_AQ_LLDP_BRID_TYPE_S) &
		ICE_AQ_LLDP_BRID_TYPE_M;

	desc.datalen = cpu_to_le16(buf_size);

	status = ice_aq_send_cmd(hw, &desc, buf, buf_size, cd);
	अगर (!status) अणु
		अगर (local_len)
			*local_len = le16_to_cpu(cmd->local_len);
		अगर (remote_len)
			*remote_len = le16_to_cpu(cmd->remote_len);
	पूर्ण

	वापस status;
पूर्ण

/**
 * ice_aq_cfg_lldp_mib_change
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @ena_update: Enable or Disable event posting
 * @cd: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * Enable or Disable posting of an event on ARQ when LLDP MIB
 * associated with the पूर्णांकerface changes (0x0A01)
 */
अटल क्रमागत ice_status
ice_aq_cfg_lldp_mib_change(काष्ठा ice_hw *hw, bool ena_update,
			   काष्ठा ice_sq_cd *cd)
अणु
	काष्ठा ice_aqc_lldp_set_mib_change *cmd;
	काष्ठा ice_aq_desc desc;

	cmd = &desc.params.lldp_set_event;

	ice_fill_dflt_direct_cmd_desc(&desc, ice_aqc_opc_lldp_set_mib_change);

	अगर (!ena_update)
		cmd->command |= ICE_AQ_LLDP_MIB_UPDATE_DIS;

	वापस ice_aq_send_cmd(hw, &desc, शून्य, 0, cd);
पूर्ण

/**
 * ice_aq_stop_lldp
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @shutकरोwn_lldp_agent: True अगर LLDP Agent needs to be Shutकरोwn
 *			 False अगर LLDP Agent needs to be Stopped
 * @persist: True अगर Stop/Shutकरोwn of LLDP Agent needs to be persistent across
 *	     reboots
 * @cd: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * Stop or Shutकरोwn the embedded LLDP Agent (0x0A05)
 */
क्रमागत ice_status
ice_aq_stop_lldp(काष्ठा ice_hw *hw, bool shutकरोwn_lldp_agent, bool persist,
		 काष्ठा ice_sq_cd *cd)
अणु
	काष्ठा ice_aqc_lldp_stop *cmd;
	काष्ठा ice_aq_desc desc;

	cmd = &desc.params.lldp_stop;

	ice_fill_dflt_direct_cmd_desc(&desc, ice_aqc_opc_lldp_stop);

	अगर (shutकरोwn_lldp_agent)
		cmd->command |= ICE_AQ_LLDP_AGENT_SHUTDOWN;

	अगर (persist)
		cmd->command |= ICE_AQ_LLDP_AGENT_PERSIST_DIS;

	वापस ice_aq_send_cmd(hw, &desc, शून्य, 0, cd);
पूर्ण

/**
 * ice_aq_start_lldp
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @persist: True अगर Start of LLDP Agent needs to be persistent across reboots
 * @cd: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * Start the embedded LLDP Agent on all ports. (0x0A06)
 */
क्रमागत ice_status
ice_aq_start_lldp(काष्ठा ice_hw *hw, bool persist, काष्ठा ice_sq_cd *cd)
अणु
	काष्ठा ice_aqc_lldp_start *cmd;
	काष्ठा ice_aq_desc desc;

	cmd = &desc.params.lldp_start;

	ice_fill_dflt_direct_cmd_desc(&desc, ice_aqc_opc_lldp_start);

	cmd->command = ICE_AQ_LLDP_AGENT_START;

	अगर (persist)
		cmd->command |= ICE_AQ_LLDP_AGENT_PERSIST_ENA;

	वापस ice_aq_send_cmd(hw, &desc, शून्य, 0, cd);
पूर्ण

/**
 * ice_get_dcbx_status
 * @hw: poपूर्णांकer to the HW काष्ठा
 *
 * Get the DCBX status from the Firmware
 */
अटल u8 ice_get_dcbx_status(काष्ठा ice_hw *hw)
अणु
	u32 reg;

	reg = rd32(hw, PRTDCB_GENS);
	वापस (u8)((reg & PRTDCB_GENS_DCBX_STATUS_M) >>
		    PRTDCB_GENS_DCBX_STATUS_S);
पूर्ण

/**
 * ice_parse_ieee_ets_common_tlv
 * @buf: Data buffer to be parsed क्रम ETS CFG/REC data
 * @ets_cfg: Container to store parsed data
 *
 * Parses the common data of IEEE 802.1Qaz ETS CFG/REC TLV
 */
अटल व्योम
ice_parse_ieee_ets_common_tlv(u8 *buf, काष्ठा ice_dcb_ets_cfg *ets_cfg)
अणु
	u8 offset = 0;
	पूर्णांक i;

	/* Priority Assignment Table (4 octets)
	 * Octets:|    1    |    2    |    3    |    4    |
	 *        -----------------------------------------
	 *        |pri0|pri1|pri2|pri3|pri4|pri5|pri6|pri7|
	 *        -----------------------------------------
	 *   Bits:|7  4|3  0|7  4|3  0|7  4|3  0|7  4|3  0|
	 *        -----------------------------------------
	 */
	क्रम (i = 0; i < 4; i++) अणु
		ets_cfg->prio_table[i * 2] =
			((buf[offset] & ICE_IEEE_ETS_PRIO_1_M) >>
			 ICE_IEEE_ETS_PRIO_1_S);
		ets_cfg->prio_table[i * 2 + 1] =
			((buf[offset] & ICE_IEEE_ETS_PRIO_0_M) >>
			 ICE_IEEE_ETS_PRIO_0_S);
		offset++;
	पूर्ण

	/* TC Bandwidth Table (8 octets)
	 * Octets:| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |
	 *        ---------------------------------
	 *        |tc0|tc1|tc2|tc3|tc4|tc5|tc6|tc7|
	 *        ---------------------------------
	 *
	 * TSA Assignment Table (8 octets)
	 * Octets:| 9 | 10| 11| 12| 13| 14| 15| 16|
	 *        ---------------------------------
	 *        |tc0|tc1|tc2|tc3|tc4|tc5|tc6|tc7|
	 *        ---------------------------------
	 */
	ice_क्रम_each_traffic_class(i) अणु
		ets_cfg->tcbwtable[i] = buf[offset];
		ets_cfg->tsatable[i] = buf[ICE_MAX_TRAFFIC_CLASS + offset++];
	पूर्ण
पूर्ण

/**
 * ice_parse_ieee_etscfg_tlv
 * @tlv: IEEE 802.1Qaz ETS CFG TLV
 * @dcbcfg: Local store to update ETS CFG data
 *
 * Parses IEEE 802.1Qaz ETS CFG TLV
 */
अटल व्योम
ice_parse_ieee_etscfg_tlv(काष्ठा ice_lldp_org_tlv *tlv,
			  काष्ठा ice_dcbx_cfg *dcbcfg)
अणु
	काष्ठा ice_dcb_ets_cfg *etscfg;
	u8 *buf = tlv->tlvinfo;

	/* First Octet post subtype
	 * --------------------------
	 * |will-|CBS  | Re-  | Max |
	 * |ing  |     |served| TCs |
	 * --------------------------
	 * |1bit | 1bit|3 bits|3bits|
	 */
	etscfg = &dcbcfg->etscfg;
	etscfg->willing = ((buf[0] & ICE_IEEE_ETS_WILLING_M) >>
			   ICE_IEEE_ETS_WILLING_S);
	etscfg->cbs = ((buf[0] & ICE_IEEE_ETS_CBS_M) >> ICE_IEEE_ETS_CBS_S);
	etscfg->maxtcs = ((buf[0] & ICE_IEEE_ETS_MAXTC_M) >>
			  ICE_IEEE_ETS_MAXTC_S);

	/* Begin parsing at Priority Assignment Table (offset 1 in buf) */
	ice_parse_ieee_ets_common_tlv(&buf[1], etscfg);
पूर्ण

/**
 * ice_parse_ieee_etsrec_tlv
 * @tlv: IEEE 802.1Qaz ETS REC TLV
 * @dcbcfg: Local store to update ETS REC data
 *
 * Parses IEEE 802.1Qaz ETS REC TLV
 */
अटल व्योम
ice_parse_ieee_etsrec_tlv(काष्ठा ice_lldp_org_tlv *tlv,
			  काष्ठा ice_dcbx_cfg *dcbcfg)
अणु
	u8 *buf = tlv->tlvinfo;

	/* Begin parsing at Priority Assignment Table (offset 1 in buf) */
	ice_parse_ieee_ets_common_tlv(&buf[1], &dcbcfg->etsrec);
पूर्ण

/**
 * ice_parse_ieee_pfccfg_tlv
 * @tlv: IEEE 802.1Qaz PFC CFG TLV
 * @dcbcfg: Local store to update PFC CFG data
 *
 * Parses IEEE 802.1Qaz PFC CFG TLV
 */
अटल व्योम
ice_parse_ieee_pfccfg_tlv(काष्ठा ice_lldp_org_tlv *tlv,
			  काष्ठा ice_dcbx_cfg *dcbcfg)
अणु
	u8 *buf = tlv->tlvinfo;

	/* ----------------------------------------
	 * |will-|MBC  | Re-  | PFC |  PFC Enable  |
	 * |ing  |     |served| cap |              |
	 * -----------------------------------------
	 * |1bit | 1bit|2 bits|4bits| 1 octet      |
	 */
	dcbcfg->pfc.willing = ((buf[0] & ICE_IEEE_PFC_WILLING_M) >>
			       ICE_IEEE_PFC_WILLING_S);
	dcbcfg->pfc.mbc = ((buf[0] & ICE_IEEE_PFC_MBC_M) >> ICE_IEEE_PFC_MBC_S);
	dcbcfg->pfc.pfccap = ((buf[0] & ICE_IEEE_PFC_CAP_M) >>
			      ICE_IEEE_PFC_CAP_S);
	dcbcfg->pfc.pfcena = buf[1];
पूर्ण

/**
 * ice_parse_ieee_app_tlv
 * @tlv: IEEE 802.1Qaz APP TLV
 * @dcbcfg: Local store to update APP PRIO data
 *
 * Parses IEEE 802.1Qaz APP PRIO TLV
 */
अटल व्योम
ice_parse_ieee_app_tlv(काष्ठा ice_lldp_org_tlv *tlv,
		       काष्ठा ice_dcbx_cfg *dcbcfg)
अणु
	u16 offset = 0;
	u16 typelen;
	पूर्णांक i = 0;
	u16 len;
	u8 *buf;

	typelen = ntohs(tlv->typelen);
	len = ((typelen & ICE_LLDP_TLV_LEN_M) >> ICE_LLDP_TLV_LEN_S);
	buf = tlv->tlvinfo;

	/* Removing माप(ouisubtype) and reserved byte from len.
	 * Reमुख्यing len भाग 3 is number of APP TLVs.
	 */
	len -= (माप(tlv->ouisubtype) + 1);

	/* Move offset to App Priority Table */
	offset++;

	/* Application Priority Table (3 octets)
	 * Octets:|         1          |    2    |    3    |
	 *        -----------------------------------------
	 *        |Priority|Rsrvd| Sel |    Protocol ID    |
	 *        -----------------------------------------
	 *   Bits:|23    21|20 19|18 16|15                0|
	 *        -----------------------------------------
	 */
	जबतक (offset < len) अणु
		dcbcfg->app[i].priority = ((buf[offset] &
					    ICE_IEEE_APP_PRIO_M) >>
					   ICE_IEEE_APP_PRIO_S);
		dcbcfg->app[i].selector = ((buf[offset] &
					    ICE_IEEE_APP_SEL_M) >>
					   ICE_IEEE_APP_SEL_S);
		dcbcfg->app[i].prot_id = (buf[offset + 1] << 0x8) |
			buf[offset + 2];
		/* Move to next app */
		offset += 3;
		i++;
		अगर (i >= ICE_DCBX_MAX_APPS)
			अवरोध;
	पूर्ण

	dcbcfg->numapps = i;
पूर्ण

/**
 * ice_parse_ieee_tlv
 * @tlv: IEEE 802.1Qaz TLV
 * @dcbcfg: Local store to update ETS REC data
 *
 * Get the TLV subtype and send it to parsing function
 * based on the subtype value
 */
अटल व्योम
ice_parse_ieee_tlv(काष्ठा ice_lldp_org_tlv *tlv, काष्ठा ice_dcbx_cfg *dcbcfg)
अणु
	u32 ouisubtype;
	u8 subtype;

	ouisubtype = ntohl(tlv->ouisubtype);
	subtype = (u8)((ouisubtype & ICE_LLDP_TLV_SUBTYPE_M) >>
		       ICE_LLDP_TLV_SUBTYPE_S);
	चयन (subtype) अणु
	हाल ICE_IEEE_SUBTYPE_ETS_CFG:
		ice_parse_ieee_etscfg_tlv(tlv, dcbcfg);
		अवरोध;
	हाल ICE_IEEE_SUBTYPE_ETS_REC:
		ice_parse_ieee_etsrec_tlv(tlv, dcbcfg);
		अवरोध;
	हाल ICE_IEEE_SUBTYPE_PFC_CFG:
		ice_parse_ieee_pfccfg_tlv(tlv, dcbcfg);
		अवरोध;
	हाल ICE_IEEE_SUBTYPE_APP_PRI:
		ice_parse_ieee_app_tlv(tlv, dcbcfg);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/**
 * ice_parse_cee_pgcfg_tlv
 * @tlv: CEE DCBX PG CFG TLV
 * @dcbcfg: Local store to update ETS CFG data
 *
 * Parses CEE DCBX PG CFG TLV
 */
अटल व्योम
ice_parse_cee_pgcfg_tlv(काष्ठा ice_cee_feat_tlv *tlv,
			काष्ठा ice_dcbx_cfg *dcbcfg)
अणु
	काष्ठा ice_dcb_ets_cfg *etscfg;
	u8 *buf = tlv->tlvinfo;
	u16 offset = 0;
	पूर्णांक i;

	etscfg = &dcbcfg->etscfg;

	अगर (tlv->en_will_err & ICE_CEE_FEAT_TLV_WILLING_M)
		etscfg->willing = 1;

	etscfg->cbs = 0;
	/* Priority Group Table (4 octets)
	 * Octets:|    1    |    2    |    3    |    4    |
	 *        -----------------------------------------
	 *        |pri0|pri1|pri2|pri3|pri4|pri5|pri6|pri7|
	 *        -----------------------------------------
	 *   Bits:|7  4|3  0|7  4|3  0|7  4|3  0|7  4|3  0|
	 *        -----------------------------------------
	 */
	क्रम (i = 0; i < 4; i++) अणु
		etscfg->prio_table[i * 2] =
			((buf[offset] & ICE_CEE_PGID_PRIO_1_M) >>
			 ICE_CEE_PGID_PRIO_1_S);
		etscfg->prio_table[i * 2 + 1] =
			((buf[offset] & ICE_CEE_PGID_PRIO_0_M) >>
			 ICE_CEE_PGID_PRIO_0_S);
		offset++;
	पूर्ण

	/* PG Percentage Table (8 octets)
	 * Octets:| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |
	 *        ---------------------------------
	 *        |pg0|pg1|pg2|pg3|pg4|pg5|pg6|pg7|
	 *        ---------------------------------
	 */
	ice_क्रम_each_traffic_class(i) अणु
		etscfg->tcbwtable[i] = buf[offset++];

		अगर (etscfg->prio_table[i] == ICE_CEE_PGID_STRICT)
			dcbcfg->etscfg.tsatable[i] = ICE_IEEE_TSA_STRICT;
		अन्यथा
			dcbcfg->etscfg.tsatable[i] = ICE_IEEE_TSA_ETS;
	पूर्ण

	/* Number of TCs supported (1 octet) */
	etscfg->maxtcs = buf[offset];
पूर्ण

/**
 * ice_parse_cee_pfccfg_tlv
 * @tlv: CEE DCBX PFC CFG TLV
 * @dcbcfg: Local store to update PFC CFG data
 *
 * Parses CEE DCBX PFC CFG TLV
 */
अटल व्योम
ice_parse_cee_pfccfg_tlv(काष्ठा ice_cee_feat_tlv *tlv,
			 काष्ठा ice_dcbx_cfg *dcbcfg)
अणु
	u8 *buf = tlv->tlvinfo;

	अगर (tlv->en_will_err & ICE_CEE_FEAT_TLV_WILLING_M)
		dcbcfg->pfc.willing = 1;

	/* ------------------------
	 * | PFC Enable | PFC TCs |
	 * ------------------------
	 * | 1 octet    | 1 octet |
	 */
	dcbcfg->pfc.pfcena = buf[0];
	dcbcfg->pfc.pfccap = buf[1];
पूर्ण

/**
 * ice_parse_cee_app_tlv
 * @tlv: CEE DCBX APP TLV
 * @dcbcfg: Local store to update APP PRIO data
 *
 * Parses CEE DCBX APP PRIO TLV
 */
अटल व्योम
ice_parse_cee_app_tlv(काष्ठा ice_cee_feat_tlv *tlv, काष्ठा ice_dcbx_cfg *dcbcfg)
अणु
	u16 len, typelen, offset = 0;
	काष्ठा ice_cee_app_prio *app;
	u8 i;

	typelen = ntohs(tlv->hdr.typelen);
	len = ((typelen & ICE_LLDP_TLV_LEN_M) >> ICE_LLDP_TLV_LEN_S);

	dcbcfg->numapps = len / माप(*app);
	अगर (!dcbcfg->numapps)
		वापस;
	अगर (dcbcfg->numapps > ICE_DCBX_MAX_APPS)
		dcbcfg->numapps = ICE_DCBX_MAX_APPS;

	क्रम (i = 0; i < dcbcfg->numapps; i++) अणु
		u8 up, selector;

		app = (काष्ठा ice_cee_app_prio *)(tlv->tlvinfo + offset);
		क्रम (up = 0; up < ICE_MAX_USER_PRIORITY; up++)
			अगर (app->prio_map & BIT(up))
				अवरोध;

		dcbcfg->app[i].priority = up;

		/* Get Selector from lower 2 bits, and convert to IEEE */
		selector = (app->upper_oui_sel & ICE_CEE_APP_SELECTOR_M);
		चयन (selector) अणु
		हाल ICE_CEE_APP_SEL_ETHTYPE:
			dcbcfg->app[i].selector = ICE_APP_SEL_ETHTYPE;
			अवरोध;
		हाल ICE_CEE_APP_SEL_TCPIP:
			dcbcfg->app[i].selector = ICE_APP_SEL_TCPIP;
			अवरोध;
		शेष:
			/* Keep selector as it is क्रम unknown types */
			dcbcfg->app[i].selector = selector;
		पूर्ण

		dcbcfg->app[i].prot_id = ntohs(app->protocol);
		/* Move to next app */
		offset += माप(*app);
	पूर्ण
पूर्ण

/**
 * ice_parse_cee_tlv
 * @tlv: CEE DCBX TLV
 * @dcbcfg: Local store to update DCBX config data
 *
 * Get the TLV subtype and send it to parsing function
 * based on the subtype value
 */
अटल व्योम
ice_parse_cee_tlv(काष्ठा ice_lldp_org_tlv *tlv, काष्ठा ice_dcbx_cfg *dcbcfg)
अणु
	काष्ठा ice_cee_feat_tlv *sub_tlv;
	u8 subtype, feat_tlv_count = 0;
	u16 len, tlvlen, typelen;
	u32 ouisubtype;

	ouisubtype = ntohl(tlv->ouisubtype);
	subtype = (u8)((ouisubtype & ICE_LLDP_TLV_SUBTYPE_M) >>
		       ICE_LLDP_TLV_SUBTYPE_S);
	/* Return अगर not CEE DCBX */
	अगर (subtype != ICE_CEE_DCBX_TYPE)
		वापस;

	typelen = ntohs(tlv->typelen);
	tlvlen = ((typelen & ICE_LLDP_TLV_LEN_M) >> ICE_LLDP_TLV_LEN_S);
	len = माप(tlv->typelen) + माप(ouisubtype) +
		माप(काष्ठा ice_cee_ctrl_tlv);
	/* Return अगर no CEE DCBX Feature TLVs */
	अगर (tlvlen <= len)
		वापस;

	sub_tlv = (काष्ठा ice_cee_feat_tlv *)((अक्षर *)tlv + len);
	जबतक (feat_tlv_count < ICE_CEE_MAX_FEAT_TYPE) अणु
		u16 sublen;

		typelen = ntohs(sub_tlv->hdr.typelen);
		sublen = ((typelen & ICE_LLDP_TLV_LEN_M) >> ICE_LLDP_TLV_LEN_S);
		subtype = (u8)((typelen & ICE_LLDP_TLV_TYPE_M) >>
			       ICE_LLDP_TLV_TYPE_S);
		चयन (subtype) अणु
		हाल ICE_CEE_SUBTYPE_PG_CFG:
			ice_parse_cee_pgcfg_tlv(sub_tlv, dcbcfg);
			अवरोध;
		हाल ICE_CEE_SUBTYPE_PFC_CFG:
			ice_parse_cee_pfccfg_tlv(sub_tlv, dcbcfg);
			अवरोध;
		हाल ICE_CEE_SUBTYPE_APP_PRI:
			ice_parse_cee_app_tlv(sub_tlv, dcbcfg);
			अवरोध;
		शेष:
			वापस;	/* Invalid Sub-type वापस */
		पूर्ण
		feat_tlv_count++;
		/* Move to next sub TLV */
		sub_tlv = (काष्ठा ice_cee_feat_tlv *)
			  ((अक्षर *)sub_tlv + माप(sub_tlv->hdr.typelen) +
			   sublen);
	पूर्ण
पूर्ण

/**
 * ice_parse_org_tlv
 * @tlv: Organization specअगरic TLV
 * @dcbcfg: Local store to update ETS REC data
 *
 * Currently only IEEE 802.1Qaz TLV is supported, all others
 * will be वापसed
 */
अटल व्योम
ice_parse_org_tlv(काष्ठा ice_lldp_org_tlv *tlv, काष्ठा ice_dcbx_cfg *dcbcfg)
अणु
	u32 ouisubtype;
	u32 oui;

	ouisubtype = ntohl(tlv->ouisubtype);
	oui = ((ouisubtype & ICE_LLDP_TLV_OUI_M) >> ICE_LLDP_TLV_OUI_S);
	चयन (oui) अणु
	हाल ICE_IEEE_8021QAZ_OUI:
		ice_parse_ieee_tlv(tlv, dcbcfg);
		अवरोध;
	हाल ICE_CEE_DCBX_OUI:
		ice_parse_cee_tlv(tlv, dcbcfg);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/**
 * ice_lldp_to_dcb_cfg
 * @lldpmib: LLDPDU to be parsed
 * @dcbcfg: store क्रम LLDPDU data
 *
 * Parse DCB configuration from the LLDPDU
 */
अटल क्रमागत ice_status
ice_lldp_to_dcb_cfg(u8 *lldpmib, काष्ठा ice_dcbx_cfg *dcbcfg)
अणु
	काष्ठा ice_lldp_org_tlv *tlv;
	क्रमागत ice_status ret = 0;
	u16 offset = 0;
	u16 typelen;
	u16 type;
	u16 len;

	अगर (!lldpmib || !dcbcfg)
		वापस ICE_ERR_PARAM;

	/* set to the start of LLDPDU */
	lldpmib += ETH_HLEN;
	tlv = (काष्ठा ice_lldp_org_tlv *)lldpmib;
	जबतक (1) अणु
		typelen = ntohs(tlv->typelen);
		type = ((typelen & ICE_LLDP_TLV_TYPE_M) >> ICE_LLDP_TLV_TYPE_S);
		len = ((typelen & ICE_LLDP_TLV_LEN_M) >> ICE_LLDP_TLV_LEN_S);
		offset += माप(typelen) + len;

		/* END TLV or beyond LLDPDU size */
		अगर (type == ICE_TLV_TYPE_END || offset > ICE_LLDPDU_SIZE)
			अवरोध;

		चयन (type) अणु
		हाल ICE_TLV_TYPE_ORG:
			ice_parse_org_tlv(tlv, dcbcfg);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		/* Move to next TLV */
		tlv = (काष्ठा ice_lldp_org_tlv *)
		      ((अक्षर *)tlv + माप(tlv->typelen) + len);
	पूर्ण

	वापस ret;
पूर्ण

/**
 * ice_aq_get_dcb_cfg
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @mib_type: MIB type क्रम the query
 * @bridgetype: bridge type क्रम the query (remote)
 * @dcbcfg: store क्रम LLDPDU data
 *
 * Query DCB configuration from the firmware
 */
क्रमागत ice_status
ice_aq_get_dcb_cfg(काष्ठा ice_hw *hw, u8 mib_type, u8 bridgetype,
		   काष्ठा ice_dcbx_cfg *dcbcfg)
अणु
	क्रमागत ice_status ret;
	u8 *lldpmib;

	/* Allocate the LLDPDU */
	lldpmib = devm_kzalloc(ice_hw_to_dev(hw), ICE_LLDPDU_SIZE, GFP_KERNEL);
	अगर (!lldpmib)
		वापस ICE_ERR_NO_MEMORY;

	ret = ice_aq_get_lldp_mib(hw, bridgetype, mib_type, (व्योम *)lldpmib,
				  ICE_LLDPDU_SIZE, शून्य, शून्य, शून्य);

	अगर (!ret)
		/* Parse LLDP MIB to get DCB configuration */
		ret = ice_lldp_to_dcb_cfg(lldpmib, dcbcfg);

	devm_kमुक्त(ice_hw_to_dev(hw), lldpmib);

	वापस ret;
पूर्ण

/**
 * ice_aq_start_stop_dcbx - Start/Stop DCBX service in FW
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @start_dcbx_agent: True अगर DCBX Agent needs to be started
 *		      False अगर DCBX Agent needs to be stopped
 * @dcbx_agent_status: FW indicates back the DCBX agent status
 *		       True अगर DCBX Agent is active
 *		       False अगर DCBX Agent is stopped
 * @cd: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * Start/Stop the embedded dcbx Agent. In हाल that this wrapper function
 * वापसs ICE_SUCCESS, caller will need to check अगर FW वापसs back the same
 * value as stated in dcbx_agent_status, and react accordingly. (0x0A09)
 */
क्रमागत ice_status
ice_aq_start_stop_dcbx(काष्ठा ice_hw *hw, bool start_dcbx_agent,
		       bool *dcbx_agent_status, काष्ठा ice_sq_cd *cd)
अणु
	काष्ठा ice_aqc_lldp_stop_start_specअगरic_agent *cmd;
	क्रमागत ice_status status;
	काष्ठा ice_aq_desc desc;
	u16 opcode;

	cmd = &desc.params.lldp_agent_ctrl;

	opcode = ice_aqc_opc_lldp_stop_start_specअगरic_agent;

	ice_fill_dflt_direct_cmd_desc(&desc, opcode);

	अगर (start_dcbx_agent)
		cmd->command = ICE_AQC_START_STOP_AGENT_START_DCBX;

	status = ice_aq_send_cmd(hw, &desc, शून्य, 0, cd);

	*dcbx_agent_status = false;

	अगर (!status &&
	    cmd->command == ICE_AQC_START_STOP_AGENT_START_DCBX)
		*dcbx_agent_status = true;

	वापस status;
पूर्ण

/**
 * ice_aq_get_cee_dcb_cfg
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @buff: response buffer that stores CEE operational configuration
 * @cd: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * Get CEE DCBX mode operational configuration from firmware (0x0A07)
 */
अटल क्रमागत ice_status
ice_aq_get_cee_dcb_cfg(काष्ठा ice_hw *hw,
		       काष्ठा ice_aqc_get_cee_dcb_cfg_resp *buff,
		       काष्ठा ice_sq_cd *cd)
अणु
	काष्ठा ice_aq_desc desc;

	ice_fill_dflt_direct_cmd_desc(&desc, ice_aqc_opc_get_cee_dcb_cfg);

	वापस ice_aq_send_cmd(hw, &desc, (व्योम *)buff, माप(*buff), cd);
पूर्ण

/**
 * ice_cee_to_dcb_cfg
 * @cee_cfg: poपूर्णांकer to CEE configuration काष्ठा
 * @pi: port inक्रमmation काष्ठाure
 *
 * Convert CEE configuration from firmware to DCB configuration
 */
अटल व्योम
ice_cee_to_dcb_cfg(काष्ठा ice_aqc_get_cee_dcb_cfg_resp *cee_cfg,
		   काष्ठा ice_port_info *pi)
अणु
	u32 status, tlv_status = le32_to_cpu(cee_cfg->tlv_status);
	u32 ice_aqc_cee_status_mask, ice_aqc_cee_status_shअगरt, j;
	u8 i, err, sync, oper, app_index, ice_app_sel_type;
	u16 app_prio = le16_to_cpu(cee_cfg->oper_app_prio);
	u16 ice_aqc_cee_app_mask, ice_aqc_cee_app_shअगरt;
	काष्ठा ice_dcbx_cfg *cmp_dcbcfg, *dcbcfg;
	u16 ice_app_prot_id_type;

	dcbcfg = &pi->qos_cfg.local_dcbx_cfg;
	dcbcfg->dcbx_mode = ICE_DCBX_MODE_CEE;
	dcbcfg->tlv_status = tlv_status;

	/* CEE PG data */
	dcbcfg->etscfg.maxtcs = cee_cfg->oper_num_tc;

	/* Note that the FW creates the oper_prio_tc nibbles reversed
	 * from those in the CEE Priority Group sub-TLV.
	 */
	क्रम (i = 0; i < ICE_MAX_TRAFFIC_CLASS / 2; i++) अणु
		dcbcfg->etscfg.prio_table[i * 2] =
			((cee_cfg->oper_prio_tc[i] & ICE_CEE_PGID_PRIO_0_M) >>
			 ICE_CEE_PGID_PRIO_0_S);
		dcbcfg->etscfg.prio_table[i * 2 + 1] =
			((cee_cfg->oper_prio_tc[i] & ICE_CEE_PGID_PRIO_1_M) >>
			 ICE_CEE_PGID_PRIO_1_S);
	पूर्ण

	ice_क्रम_each_traffic_class(i) अणु
		dcbcfg->etscfg.tcbwtable[i] = cee_cfg->oper_tc_bw[i];

		अगर (dcbcfg->etscfg.prio_table[i] == ICE_CEE_PGID_STRICT) अणु
			/* Map it to next empty TC */
			dcbcfg->etscfg.prio_table[i] = cee_cfg->oper_num_tc - 1;
			dcbcfg->etscfg.tsatable[i] = ICE_IEEE_TSA_STRICT;
		पूर्ण अन्यथा अणु
			dcbcfg->etscfg.tsatable[i] = ICE_IEEE_TSA_ETS;
		पूर्ण
	पूर्ण

	/* CEE PFC data */
	dcbcfg->pfc.pfcena = cee_cfg->oper_pfc_en;
	dcbcfg->pfc.pfccap = ICE_MAX_TRAFFIC_CLASS;

	/* CEE APP TLV data */
	अगर (dcbcfg->app_mode == ICE_DCBX_APPS_NON_WILLING)
		cmp_dcbcfg = &pi->qos_cfg.desired_dcbx_cfg;
	अन्यथा
		cmp_dcbcfg = &pi->qos_cfg.remote_dcbx_cfg;

	app_index = 0;
	क्रम (i = 0; i < 3; i++) अणु
		अगर (i == 0) अणु
			/* FCoE APP */
			ice_aqc_cee_status_mask = ICE_AQC_CEE_FCOE_STATUS_M;
			ice_aqc_cee_status_shअगरt = ICE_AQC_CEE_FCOE_STATUS_S;
			ice_aqc_cee_app_mask = ICE_AQC_CEE_APP_FCOE_M;
			ice_aqc_cee_app_shअगरt = ICE_AQC_CEE_APP_FCOE_S;
			ice_app_sel_type = ICE_APP_SEL_ETHTYPE;
			ice_app_prot_id_type = ETH_P_FCOE;
		पूर्ण अन्यथा अगर (i == 1) अणु
			/* iSCSI APP */
			ice_aqc_cee_status_mask = ICE_AQC_CEE_ISCSI_STATUS_M;
			ice_aqc_cee_status_shअगरt = ICE_AQC_CEE_ISCSI_STATUS_S;
			ice_aqc_cee_app_mask = ICE_AQC_CEE_APP_ISCSI_M;
			ice_aqc_cee_app_shअगरt = ICE_AQC_CEE_APP_ISCSI_S;
			ice_app_sel_type = ICE_APP_SEL_TCPIP;
			ice_app_prot_id_type = ISCSI_LISTEN_PORT;

			क्रम (j = 0; j < cmp_dcbcfg->numapps; j++) अणु
				u16 prot_id = cmp_dcbcfg->app[j].prot_id;
				u8 sel = cmp_dcbcfg->app[j].selector;

				अगर  (sel == ICE_APP_SEL_TCPIP &&
				     (prot_id == ISCSI_LISTEN_PORT ||
				      prot_id == ICE_APP_PROT_ID_ISCSI_860)) अणु
					ice_app_prot_id_type = prot_id;
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			/* FIP APP */
			ice_aqc_cee_status_mask = ICE_AQC_CEE_FIP_STATUS_M;
			ice_aqc_cee_status_shअगरt = ICE_AQC_CEE_FIP_STATUS_S;
			ice_aqc_cee_app_mask = ICE_AQC_CEE_APP_FIP_M;
			ice_aqc_cee_app_shअगरt = ICE_AQC_CEE_APP_FIP_S;
			ice_app_sel_type = ICE_APP_SEL_ETHTYPE;
			ice_app_prot_id_type = ETH_P_FIP;
		पूर्ण

		status = (tlv_status & ice_aqc_cee_status_mask) >>
			 ice_aqc_cee_status_shअगरt;
		err = (status & ICE_TLV_STATUS_ERR) ? 1 : 0;
		sync = (status & ICE_TLV_STATUS_SYNC) ? 1 : 0;
		oper = (status & ICE_TLV_STATUS_OPER) ? 1 : 0;
		/* Add FCoE/iSCSI/FIP APP अगर Error is False and
		 * Oper/Sync is True
		 */
		अगर (!err && sync && oper) अणु
			dcbcfg->app[app_index].priority =
				(app_prio & ice_aqc_cee_app_mask) >>
				ice_aqc_cee_app_shअगरt;
			dcbcfg->app[app_index].selector = ice_app_sel_type;
			dcbcfg->app[app_index].prot_id = ice_app_prot_id_type;
			app_index++;
		पूर्ण
	पूर्ण

	dcbcfg->numapps = app_index;
पूर्ण

/**
 * ice_get_ieee_or_cee_dcb_cfg
 * @pi: port inक्रमmation काष्ठाure
 * @dcbx_mode: mode of DCBX (IEEE or CEE)
 *
 * Get IEEE or CEE mode DCB configuration from the Firmware
 */
अटल क्रमागत ice_status
ice_get_ieee_or_cee_dcb_cfg(काष्ठा ice_port_info *pi, u8 dcbx_mode)
अणु
	काष्ठा ice_dcbx_cfg *dcbx_cfg = शून्य;
	क्रमागत ice_status ret;

	अगर (!pi)
		वापस ICE_ERR_PARAM;

	अगर (dcbx_mode == ICE_DCBX_MODE_IEEE)
		dcbx_cfg = &pi->qos_cfg.local_dcbx_cfg;
	अन्यथा अगर (dcbx_mode == ICE_DCBX_MODE_CEE)
		dcbx_cfg = &pi->qos_cfg.desired_dcbx_cfg;

	/* Get Local DCB Config in हाल of ICE_DCBX_MODE_IEEE
	 * or get CEE DCB Desired Config in हाल of ICE_DCBX_MODE_CEE
	 */
	ret = ice_aq_get_dcb_cfg(pi->hw, ICE_AQ_LLDP_MIB_LOCAL,
				 ICE_AQ_LLDP_BRID_TYPE_NEAREST_BRID, dcbx_cfg);
	अगर (ret)
		जाओ out;

	/* Get Remote DCB Config */
	dcbx_cfg = &pi->qos_cfg.remote_dcbx_cfg;
	ret = ice_aq_get_dcb_cfg(pi->hw, ICE_AQ_LLDP_MIB_REMOTE,
				 ICE_AQ_LLDP_BRID_TYPE_NEAREST_BRID, dcbx_cfg);
	/* Don't treat ENOENT as an error क्रम Remote MIBs */
	अगर (pi->hw->adminq.sq_last_status == ICE_AQ_RC_ENOENT)
		ret = 0;

out:
	वापस ret;
पूर्ण

/**
 * ice_get_dcb_cfg
 * @pi: port inक्रमmation काष्ठाure
 *
 * Get DCB configuration from the Firmware
 */
क्रमागत ice_status ice_get_dcb_cfg(काष्ठा ice_port_info *pi)
अणु
	काष्ठा ice_aqc_get_cee_dcb_cfg_resp cee_cfg;
	काष्ठा ice_dcbx_cfg *dcbx_cfg;
	क्रमागत ice_status ret;

	अगर (!pi)
		वापस ICE_ERR_PARAM;

	ret = ice_aq_get_cee_dcb_cfg(pi->hw, &cee_cfg, शून्य);
	अगर (!ret) अणु
		/* CEE mode */
		ret = ice_get_ieee_or_cee_dcb_cfg(pi, ICE_DCBX_MODE_CEE);
		ice_cee_to_dcb_cfg(&cee_cfg, pi);
	पूर्ण अन्यथा अगर (pi->hw->adminq.sq_last_status == ICE_AQ_RC_ENOENT) अणु
		/* CEE mode not enabled try querying IEEE data */
		dcbx_cfg = &pi->qos_cfg.local_dcbx_cfg;
		dcbx_cfg->dcbx_mode = ICE_DCBX_MODE_IEEE;
		ret = ice_get_ieee_or_cee_dcb_cfg(pi, ICE_DCBX_MODE_IEEE);
	पूर्ण

	वापस ret;
पूर्ण

/**
 * ice_init_dcb
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @enable_mib_change: enable MIB change event
 *
 * Update DCB configuration from the Firmware
 */
क्रमागत ice_status ice_init_dcb(काष्ठा ice_hw *hw, bool enable_mib_change)
अणु
	काष्ठा ice_qos_cfg *qos_cfg = &hw->port_info->qos_cfg;
	क्रमागत ice_status ret = 0;

	अगर (!hw->func_caps.common_cap.dcb)
		वापस ICE_ERR_NOT_SUPPORTED;

	qos_cfg->is_sw_lldp = true;

	/* Get DCBX status */
	qos_cfg->dcbx_status = ice_get_dcbx_status(hw);

	अगर (qos_cfg->dcbx_status == ICE_DCBX_STATUS_DONE ||
	    qos_cfg->dcbx_status == ICE_DCBX_STATUS_IN_PROGRESS ||
	    qos_cfg->dcbx_status == ICE_DCBX_STATUS_NOT_STARTED) अणु
		/* Get current DCBX configuration */
		ret = ice_get_dcb_cfg(hw->port_info);
		अगर (ret)
			वापस ret;
		qos_cfg->is_sw_lldp = false;
	पूर्ण अन्यथा अगर (qos_cfg->dcbx_status == ICE_DCBX_STATUS_DIS) अणु
		वापस ICE_ERR_NOT_READY;
	पूर्ण

	/* Configure the LLDP MIB change event */
	अगर (enable_mib_change) अणु
		ret = ice_aq_cfg_lldp_mib_change(hw, true, शून्य);
		अगर (ret)
			qos_cfg->is_sw_lldp = true;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * ice_cfg_lldp_mib_change
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @ena_mib: enable/disable MIB change event
 *
 * Configure (disable/enable) MIB
 */
क्रमागत ice_status ice_cfg_lldp_mib_change(काष्ठा ice_hw *hw, bool ena_mib)
अणु
	काष्ठा ice_qos_cfg *qos_cfg = &hw->port_info->qos_cfg;
	क्रमागत ice_status ret;

	अगर (!hw->func_caps.common_cap.dcb)
		वापस ICE_ERR_NOT_SUPPORTED;

	/* Get DCBX status */
	qos_cfg->dcbx_status = ice_get_dcbx_status(hw);

	अगर (qos_cfg->dcbx_status == ICE_DCBX_STATUS_DIS)
		वापस ICE_ERR_NOT_READY;

	ret = ice_aq_cfg_lldp_mib_change(hw, ena_mib, शून्य);
	अगर (!ret)
		qos_cfg->is_sw_lldp = !ena_mib;

	वापस ret;
पूर्ण

/**
 * ice_add_ieee_ets_common_tlv
 * @buf: Data buffer to be populated with ice_dcb_ets_cfg data
 * @ets_cfg: Container क्रम ice_dcb_ets_cfg data
 *
 * Populate the TLV buffer with ice_dcb_ets_cfg data
 */
अटल व्योम
ice_add_ieee_ets_common_tlv(u8 *buf, काष्ठा ice_dcb_ets_cfg *ets_cfg)
अणु
	u8 priority0, priority1;
	u8 offset = 0;
	पूर्णांक i;

	/* Priority Assignment Table (4 octets)
	 * Octets:|    1    |    2    |    3    |    4    |
	 *        -----------------------------------------
	 *        |pri0|pri1|pri2|pri3|pri4|pri5|pri6|pri7|
	 *        -----------------------------------------
	 *   Bits:|7  4|3  0|7  4|3  0|7  4|3  0|7  4|3  0|
	 *        -----------------------------------------
	 */
	क्रम (i = 0; i < ICE_MAX_TRAFFIC_CLASS / 2; i++) अणु
		priority0 = ets_cfg->prio_table[i * 2] & 0xF;
		priority1 = ets_cfg->prio_table[i * 2 + 1] & 0xF;
		buf[offset] = (priority0 << ICE_IEEE_ETS_PRIO_1_S) | priority1;
		offset++;
	पूर्ण

	/* TC Bandwidth Table (8 octets)
	 * Octets:| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |
	 *        ---------------------------------
	 *        |tc0|tc1|tc2|tc3|tc4|tc5|tc6|tc7|
	 *        ---------------------------------
	 *
	 * TSA Assignment Table (8 octets)
	 * Octets:| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |
	 *        ---------------------------------
	 *        |tc0|tc1|tc2|tc3|tc4|tc5|tc6|tc7|
	 *        ---------------------------------
	 */
	ice_क्रम_each_traffic_class(i) अणु
		buf[offset] = ets_cfg->tcbwtable[i];
		buf[ICE_MAX_TRAFFIC_CLASS + offset] = ets_cfg->tsatable[i];
		offset++;
	पूर्ण
पूर्ण

/**
 * ice_add_ieee_ets_tlv - Prepare ETS TLV in IEEE क्रमmat
 * @tlv: Fill the ETS config data in IEEE क्रमmat
 * @dcbcfg: Local store which holds the DCB Config
 *
 * Prepare IEEE 802.1Qaz ETS CFG TLV
 */
अटल व्योम
ice_add_ieee_ets_tlv(काष्ठा ice_lldp_org_tlv *tlv, काष्ठा ice_dcbx_cfg *dcbcfg)
अणु
	काष्ठा ice_dcb_ets_cfg *etscfg;
	u8 *buf = tlv->tlvinfo;
	u8 maxtcwilling = 0;
	u32 ouisubtype;
	u16 typelen;

	typelen = ((ICE_TLV_TYPE_ORG << ICE_LLDP_TLV_TYPE_S) |
		   ICE_IEEE_ETS_TLV_LEN);
	tlv->typelen = htons(typelen);

	ouisubtype = ((ICE_IEEE_8021QAZ_OUI << ICE_LLDP_TLV_OUI_S) |
		      ICE_IEEE_SUBTYPE_ETS_CFG);
	tlv->ouisubtype = htonl(ouisubtype);

	/* First Octet post subtype
	 * --------------------------
	 * |will-|CBS  | Re-  | Max |
	 * |ing  |     |served| TCs |
	 * --------------------------
	 * |1bit | 1bit|3 bits|3bits|
	 */
	etscfg = &dcbcfg->etscfg;
	अगर (etscfg->willing)
		maxtcwilling = BIT(ICE_IEEE_ETS_WILLING_S);
	maxtcwilling |= etscfg->maxtcs & ICE_IEEE_ETS_MAXTC_M;
	buf[0] = maxtcwilling;

	/* Begin adding at Priority Assignment Table (offset 1 in buf) */
	ice_add_ieee_ets_common_tlv(&buf[1], etscfg);
पूर्ण

/**
 * ice_add_ieee_etsrec_tlv - Prepare ETS Recommended TLV in IEEE क्रमmat
 * @tlv: Fill ETS Recommended TLV in IEEE क्रमmat
 * @dcbcfg: Local store which holds the DCB Config
 *
 * Prepare IEEE 802.1Qaz ETS REC TLV
 */
अटल व्योम
ice_add_ieee_etsrec_tlv(काष्ठा ice_lldp_org_tlv *tlv,
			काष्ठा ice_dcbx_cfg *dcbcfg)
अणु
	काष्ठा ice_dcb_ets_cfg *etsrec;
	u8 *buf = tlv->tlvinfo;
	u32 ouisubtype;
	u16 typelen;

	typelen = ((ICE_TLV_TYPE_ORG << ICE_LLDP_TLV_TYPE_S) |
		   ICE_IEEE_ETS_TLV_LEN);
	tlv->typelen = htons(typelen);

	ouisubtype = ((ICE_IEEE_8021QAZ_OUI << ICE_LLDP_TLV_OUI_S) |
		      ICE_IEEE_SUBTYPE_ETS_REC);
	tlv->ouisubtype = htonl(ouisubtype);

	etsrec = &dcbcfg->etsrec;

	/* First Octet is reserved */
	/* Begin adding at Priority Assignment Table (offset 1 in buf) */
	ice_add_ieee_ets_common_tlv(&buf[1], etsrec);
पूर्ण

/**
 * ice_add_ieee_pfc_tlv - Prepare PFC TLV in IEEE क्रमmat
 * @tlv: Fill PFC TLV in IEEE क्रमmat
 * @dcbcfg: Local store which holds the PFC CFG data
 *
 * Prepare IEEE 802.1Qaz PFC CFG TLV
 */
अटल व्योम
ice_add_ieee_pfc_tlv(काष्ठा ice_lldp_org_tlv *tlv, काष्ठा ice_dcbx_cfg *dcbcfg)
अणु
	u8 *buf = tlv->tlvinfo;
	u32 ouisubtype;
	u16 typelen;

	typelen = ((ICE_TLV_TYPE_ORG << ICE_LLDP_TLV_TYPE_S) |
		   ICE_IEEE_PFC_TLV_LEN);
	tlv->typelen = htons(typelen);

	ouisubtype = ((ICE_IEEE_8021QAZ_OUI << ICE_LLDP_TLV_OUI_S) |
		      ICE_IEEE_SUBTYPE_PFC_CFG);
	tlv->ouisubtype = htonl(ouisubtype);

	/* ----------------------------------------
	 * |will-|MBC  | Re-  | PFC |  PFC Enable  |
	 * |ing  |     |served| cap |              |
	 * -----------------------------------------
	 * |1bit | 1bit|2 bits|4bits| 1 octet      |
	 */
	अगर (dcbcfg->pfc.willing)
		buf[0] = BIT(ICE_IEEE_PFC_WILLING_S);

	अगर (dcbcfg->pfc.mbc)
		buf[0] |= BIT(ICE_IEEE_PFC_MBC_S);

	buf[0] |= dcbcfg->pfc.pfccap & 0xF;
	buf[1] = dcbcfg->pfc.pfcena;
पूर्ण

/**
 * ice_add_ieee_app_pri_tlv -  Prepare APP TLV in IEEE क्रमmat
 * @tlv: Fill APP TLV in IEEE क्रमmat
 * @dcbcfg: Local store which holds the APP CFG data
 *
 * Prepare IEEE 802.1Qaz APP CFG TLV
 */
अटल व्योम
ice_add_ieee_app_pri_tlv(काष्ठा ice_lldp_org_tlv *tlv,
			 काष्ठा ice_dcbx_cfg *dcbcfg)
अणु
	u16 typelen, len, offset = 0;
	u8 priority, selector, i = 0;
	u8 *buf = tlv->tlvinfo;
	u32 ouisubtype;

	/* No APP TLVs then just वापस */
	अगर (dcbcfg->numapps == 0)
		वापस;
	ouisubtype = ((ICE_IEEE_8021QAZ_OUI << ICE_LLDP_TLV_OUI_S) |
		      ICE_IEEE_SUBTYPE_APP_PRI);
	tlv->ouisubtype = htonl(ouisubtype);

	/* Move offset to App Priority Table */
	offset++;
	/* Application Priority Table (3 octets)
	 * Octets:|         1          |    2    |    3    |
	 *        -----------------------------------------
	 *        |Priority|Rsrvd| Sel |    Protocol ID    |
	 *        -----------------------------------------
	 *   Bits:|23    21|20 19|18 16|15                0|
	 *        -----------------------------------------
	 */
	जबतक (i < dcbcfg->numapps) अणु
		priority = dcbcfg->app[i].priority & 0x7;
		selector = dcbcfg->app[i].selector & 0x7;
		buf[offset] = (priority << ICE_IEEE_APP_PRIO_S) | selector;
		buf[offset + 1] = (dcbcfg->app[i].prot_id >> 0x8) & 0xFF;
		buf[offset + 2] = dcbcfg->app[i].prot_id & 0xFF;
		/* Move to next app */
		offset += 3;
		i++;
		अगर (i >= ICE_DCBX_MAX_APPS)
			अवरोध;
	पूर्ण
	/* len includes size of ouisubtype + 1 reserved + 3*numapps */
	len = माप(tlv->ouisubtype) + 1 + (i * 3);
	typelen = ((ICE_TLV_TYPE_ORG << ICE_LLDP_TLV_TYPE_S) | (len & 0x1FF));
	tlv->typelen = htons(typelen);
पूर्ण

/**
 * ice_add_dcb_tlv - Add all IEEE TLVs
 * @tlv: Fill TLV data in IEEE क्रमmat
 * @dcbcfg: Local store which holds the DCB Config
 * @tlvid: Type of IEEE TLV
 *
 * Add tlv inक्रमmation
 */
अटल व्योम
ice_add_dcb_tlv(काष्ठा ice_lldp_org_tlv *tlv, काष्ठा ice_dcbx_cfg *dcbcfg,
		u16 tlvid)
अणु
	चयन (tlvid) अणु
	हाल ICE_IEEE_TLV_ID_ETS_CFG:
		ice_add_ieee_ets_tlv(tlv, dcbcfg);
		अवरोध;
	हाल ICE_IEEE_TLV_ID_ETS_REC:
		ice_add_ieee_etsrec_tlv(tlv, dcbcfg);
		अवरोध;
	हाल ICE_IEEE_TLV_ID_PFC_CFG:
		ice_add_ieee_pfc_tlv(tlv, dcbcfg);
		अवरोध;
	हाल ICE_IEEE_TLV_ID_APP_PRI:
		ice_add_ieee_app_pri_tlv(tlv, dcbcfg);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/**
 * ice_dcb_cfg_to_lldp - Convert DCB configuration to MIB क्रमmat
 * @lldpmib: poपूर्णांकer to the HW काष्ठा
 * @miblen: length of LLDP MIB
 * @dcbcfg: Local store which holds the DCB Config
 *
 * Convert the DCB configuration to MIB क्रमmat
 */
अटल व्योम
ice_dcb_cfg_to_lldp(u8 *lldpmib, u16 *miblen, काष्ठा ice_dcbx_cfg *dcbcfg)
अणु
	u16 len, offset = 0, tlvid = ICE_TLV_ID_START;
	काष्ठा ice_lldp_org_tlv *tlv;
	u16 typelen;

	tlv = (काष्ठा ice_lldp_org_tlv *)lldpmib;
	जबतक (1) अणु
		ice_add_dcb_tlv(tlv, dcbcfg, tlvid++);
		typelen = ntohs(tlv->typelen);
		len = (typelen & ICE_LLDP_TLV_LEN_M) >> ICE_LLDP_TLV_LEN_S;
		अगर (len)
			offset += len + 2;
		/* END TLV or beyond LLDPDU size */
		अगर (tlvid >= ICE_TLV_ID_END_OF_LLDPPDU ||
		    offset > ICE_LLDPDU_SIZE)
			अवरोध;
		/* Move to next TLV */
		अगर (len)
			tlv = (काष्ठा ice_lldp_org_tlv *)
				((अक्षर *)tlv + माप(tlv->typelen) + len);
	पूर्ण
	*miblen = offset;
पूर्ण

/**
 * ice_set_dcb_cfg - Set the local LLDP MIB to FW
 * @pi: port inक्रमmation काष्ठाure
 *
 * Set DCB configuration to the Firmware
 */
क्रमागत ice_status ice_set_dcb_cfg(काष्ठा ice_port_info *pi)
अणु
	u8 mib_type, *lldpmib = शून्य;
	काष्ठा ice_dcbx_cfg *dcbcfg;
	क्रमागत ice_status ret;
	काष्ठा ice_hw *hw;
	u16 miblen;

	अगर (!pi)
		वापस ICE_ERR_PARAM;

	hw = pi->hw;

	/* update the HW local config */
	dcbcfg = &pi->qos_cfg.local_dcbx_cfg;
	/* Allocate the LLDPDU */
	lldpmib = devm_kzalloc(ice_hw_to_dev(hw), ICE_LLDPDU_SIZE, GFP_KERNEL);
	अगर (!lldpmib)
		वापस ICE_ERR_NO_MEMORY;

	mib_type = SET_LOCAL_MIB_TYPE_LOCAL_MIB;
	अगर (dcbcfg->app_mode == ICE_DCBX_APPS_NON_WILLING)
		mib_type |= SET_LOCAL_MIB_TYPE_CEE_NON_WILLING;

	ice_dcb_cfg_to_lldp(lldpmib, &miblen, dcbcfg);
	ret = ice_aq_set_lldp_mib(hw, mib_type, (व्योम *)lldpmib, miblen,
				  शून्य);

	devm_kमुक्त(ice_hw_to_dev(hw), lldpmib);

	वापस ret;
पूर्ण

/**
 * ice_aq_query_port_ets - query port ETS configuration
 * @pi: port inक्रमmation काष्ठाure
 * @buf: poपूर्णांकer to buffer
 * @buf_size: buffer size in bytes
 * @cd: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * query current port ETS configuration
 */
अटल क्रमागत ice_status
ice_aq_query_port_ets(काष्ठा ice_port_info *pi,
		      काष्ठा ice_aqc_port_ets_elem *buf, u16 buf_size,
		      काष्ठा ice_sq_cd *cd)
अणु
	काष्ठा ice_aqc_query_port_ets *cmd;
	काष्ठा ice_aq_desc desc;
	क्रमागत ice_status status;

	अगर (!pi)
		वापस ICE_ERR_PARAM;
	cmd = &desc.params.port_ets;
	ice_fill_dflt_direct_cmd_desc(&desc, ice_aqc_opc_query_port_ets);
	cmd->port_teid = pi->root->info.node_teid;

	status = ice_aq_send_cmd(pi->hw, &desc, buf, buf_size, cd);
	वापस status;
पूर्ण

/**
 * ice_update_port_tc_tree_cfg - update TC tree configuration
 * @pi: port inक्रमmation काष्ठाure
 * @buf: poपूर्णांकer to buffer
 *
 * update the SW DB with the new TC changes
 */
अटल क्रमागत ice_status
ice_update_port_tc_tree_cfg(काष्ठा ice_port_info *pi,
			    काष्ठा ice_aqc_port_ets_elem *buf)
अणु
	काष्ठा ice_sched_node *node, *tc_node;
	काष्ठा ice_aqc_txsched_elem_data elem;
	क्रमागत ice_status status = 0;
	u32 teid1, teid2;
	u8 i, j;

	अगर (!pi)
		वापस ICE_ERR_PARAM;
	/* suspend the missing TC nodes */
	क्रम (i = 0; i < pi->root->num_children; i++) अणु
		teid1 = le32_to_cpu(pi->root->children[i]->info.node_teid);
		ice_क्रम_each_traffic_class(j) अणु
			teid2 = le32_to_cpu(buf->tc_node_teid[j]);
			अगर (teid1 == teid2)
				अवरोध;
		पूर्ण
		अगर (j < ICE_MAX_TRAFFIC_CLASS)
			जारी;
		/* TC is missing */
		pi->root->children[i]->in_use = false;
	पूर्ण
	/* add the new TC nodes */
	ice_क्रम_each_traffic_class(j) अणु
		teid2 = le32_to_cpu(buf->tc_node_teid[j]);
		अगर (teid2 == ICE_INVAL_TEID)
			जारी;
		/* Is it alपढ़ोy present in the tree ? */
		क्रम (i = 0; i < pi->root->num_children; i++) अणु
			tc_node = pi->root->children[i];
			अगर (!tc_node)
				जारी;
			teid1 = le32_to_cpu(tc_node->info.node_teid);
			अगर (teid1 == teid2) अणु
				tc_node->tc_num = j;
				tc_node->in_use = true;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (i < pi->root->num_children)
			जारी;
		/* new TC */
		status = ice_sched_query_elem(pi->hw, teid2, &elem);
		अगर (!status)
			status = ice_sched_add_node(pi, 1, &elem);
		अगर (status)
			अवरोध;
		/* update the TC number */
		node = ice_sched_find_node_by_teid(pi->root, teid2);
		अगर (node)
			node->tc_num = j;
	पूर्ण
	वापस status;
पूर्ण

/**
 * ice_query_port_ets - query port ETS configuration
 * @pi: port inक्रमmation काष्ठाure
 * @buf: poपूर्णांकer to buffer
 * @buf_size: buffer size in bytes
 * @cd: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * query current port ETS configuration and update the
 * SW DB with the TC changes
 */
क्रमागत ice_status
ice_query_port_ets(काष्ठा ice_port_info *pi,
		   काष्ठा ice_aqc_port_ets_elem *buf, u16 buf_size,
		   काष्ठा ice_sq_cd *cd)
अणु
	क्रमागत ice_status status;

	mutex_lock(&pi->sched_lock);
	status = ice_aq_query_port_ets(pi, buf, buf_size, cd);
	अगर (!status)
		status = ice_update_port_tc_tree_cfg(pi, buf);
	mutex_unlock(&pi->sched_lock);
	वापस status;
पूर्ण
