<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2013 - 2021 Intel Corporation. */

#समावेश "i40e_adminq.h"
#समावेश "i40e_prototype.h"
#समावेश "i40e_dcb.h"

/**
 * i40e_get_dcbx_status
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @status: Embedded DCBX Engine Status
 *
 * Get the DCBX status from the Firmware
 **/
i40e_status i40e_get_dcbx_status(काष्ठा i40e_hw *hw, u16 *status)
अणु
	u32 reg;

	अगर (!status)
		वापस I40E_ERR_PARAM;

	reg = rd32(hw, I40E_PRTDCB_GENS);
	*status = (u16)((reg & I40E_PRTDCB_GENS_DCBX_STATUS_MASK) >>
			I40E_PRTDCB_GENS_DCBX_STATUS_SHIFT);

	वापस 0;
पूर्ण

/**
 * i40e_parse_ieee_etscfg_tlv
 * @tlv: IEEE 802.1Qaz ETS CFG TLV
 * @dcbcfg: Local store to update ETS CFG data
 *
 * Parses IEEE 802.1Qaz ETS CFG TLV
 **/
अटल व्योम i40e_parse_ieee_etscfg_tlv(काष्ठा i40e_lldp_org_tlv *tlv,
				       काष्ठा i40e_dcbx_config *dcbcfg)
अणु
	काष्ठा i40e_dcb_ets_config *etscfg;
	u8 *buf = tlv->tlvinfo;
	u16 offset = 0;
	u8 priority;
	पूर्णांक i;

	/* First Octet post subtype
	 * --------------------------
	 * |will-|CBS  | Re-  | Max |
	 * |ing  |     |served| TCs |
	 * --------------------------
	 * |1bit | 1bit|3 bits|3bits|
	 */
	etscfg = &dcbcfg->etscfg;
	etscfg->willing = (u8)((buf[offset] & I40E_IEEE_ETS_WILLING_MASK) >>
			       I40E_IEEE_ETS_WILLING_SHIFT);
	etscfg->cbs = (u8)((buf[offset] & I40E_IEEE_ETS_CBS_MASK) >>
			   I40E_IEEE_ETS_CBS_SHIFT);
	etscfg->maxtcs = (u8)((buf[offset] & I40E_IEEE_ETS_MAXTC_MASK) >>
			      I40E_IEEE_ETS_MAXTC_SHIFT);

	/* Move offset to Priority Assignment Table */
	offset++;

	/* Priority Assignment Table (4 octets)
	 * Octets:|    1    |    2    |    3    |    4    |
	 *        -----------------------------------------
	 *        |pri0|pri1|pri2|pri3|pri4|pri5|pri6|pri7|
	 *        -----------------------------------------
	 *   Bits:|7  4|3  0|7  4|3  0|7  4|3  0|7  4|3  0|
	 *        -----------------------------------------
	 */
	क्रम (i = 0; i < 4; i++) अणु
		priority = (u8)((buf[offset] & I40E_IEEE_ETS_PRIO_1_MASK) >>
				I40E_IEEE_ETS_PRIO_1_SHIFT);
		etscfg->prioritytable[i * 2] =  priority;
		priority = (u8)((buf[offset] & I40E_IEEE_ETS_PRIO_0_MASK) >>
				I40E_IEEE_ETS_PRIO_0_SHIFT);
		etscfg->prioritytable[i * 2 + 1] = priority;
		offset++;
	पूर्ण

	/* TC Bandwidth Table (8 octets)
	 * Octets:| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |
	 *        ---------------------------------
	 *        |tc0|tc1|tc2|tc3|tc4|tc5|tc6|tc7|
	 *        ---------------------------------
	 */
	क्रम (i = 0; i < I40E_MAX_TRAFFIC_CLASS; i++)
		etscfg->tcbwtable[i] = buf[offset++];

	/* TSA Assignment Table (8 octets)
	 * Octets:| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |
	 *        ---------------------------------
	 *        |tc0|tc1|tc2|tc3|tc4|tc5|tc6|tc7|
	 *        ---------------------------------
	 */
	क्रम (i = 0; i < I40E_MAX_TRAFFIC_CLASS; i++)
		etscfg->tsatable[i] = buf[offset++];
पूर्ण

/**
 * i40e_parse_ieee_etsrec_tlv
 * @tlv: IEEE 802.1Qaz ETS REC TLV
 * @dcbcfg: Local store to update ETS REC data
 *
 * Parses IEEE 802.1Qaz ETS REC TLV
 **/
अटल व्योम i40e_parse_ieee_etsrec_tlv(काष्ठा i40e_lldp_org_tlv *tlv,
				       काष्ठा i40e_dcbx_config *dcbcfg)
अणु
	u8 *buf = tlv->tlvinfo;
	u16 offset = 0;
	u8 priority;
	पूर्णांक i;

	/* Move offset to priority table */
	offset++;

	/* Priority Assignment Table (4 octets)
	 * Octets:|    1    |    2    |    3    |    4    |
	 *        -----------------------------------------
	 *        |pri0|pri1|pri2|pri3|pri4|pri5|pri6|pri7|
	 *        -----------------------------------------
	 *   Bits:|7  4|3  0|7  4|3  0|7  4|3  0|7  4|3  0|
	 *        -----------------------------------------
	 */
	क्रम (i = 0; i < 4; i++) अणु
		priority = (u8)((buf[offset] & I40E_IEEE_ETS_PRIO_1_MASK) >>
				I40E_IEEE_ETS_PRIO_1_SHIFT);
		dcbcfg->etsrec.prioritytable[i*2] =  priority;
		priority = (u8)((buf[offset] & I40E_IEEE_ETS_PRIO_0_MASK) >>
				I40E_IEEE_ETS_PRIO_0_SHIFT);
		dcbcfg->etsrec.prioritytable[i*2 + 1] = priority;
		offset++;
	पूर्ण

	/* TC Bandwidth Table (8 octets)
	 * Octets:| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |
	 *        ---------------------------------
	 *        |tc0|tc1|tc2|tc3|tc4|tc5|tc6|tc7|
	 *        ---------------------------------
	 */
	क्रम (i = 0; i < I40E_MAX_TRAFFIC_CLASS; i++)
		dcbcfg->etsrec.tcbwtable[i] = buf[offset++];

	/* TSA Assignment Table (8 octets)
	 * Octets:| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |
	 *        ---------------------------------
	 *        |tc0|tc1|tc2|tc3|tc4|tc5|tc6|tc7|
	 *        ---------------------------------
	 */
	क्रम (i = 0; i < I40E_MAX_TRAFFIC_CLASS; i++)
		dcbcfg->etsrec.tsatable[i] = buf[offset++];
पूर्ण

/**
 * i40e_parse_ieee_pfccfg_tlv
 * @tlv: IEEE 802.1Qaz PFC CFG TLV
 * @dcbcfg: Local store to update PFC CFG data
 *
 * Parses IEEE 802.1Qaz PFC CFG TLV
 **/
अटल व्योम i40e_parse_ieee_pfccfg_tlv(काष्ठा i40e_lldp_org_tlv *tlv,
				       काष्ठा i40e_dcbx_config *dcbcfg)
अणु
	u8 *buf = tlv->tlvinfo;

	/* ----------------------------------------
	 * |will-|MBC  | Re-  | PFC |  PFC Enable  |
	 * |ing  |     |served| cap |              |
	 * -----------------------------------------
	 * |1bit | 1bit|2 bits|4bits| 1 octet      |
	 */
	dcbcfg->pfc.willing = (u8)((buf[0] & I40E_IEEE_PFC_WILLING_MASK) >>
				   I40E_IEEE_PFC_WILLING_SHIFT);
	dcbcfg->pfc.mbc = (u8)((buf[0] & I40E_IEEE_PFC_MBC_MASK) >>
			       I40E_IEEE_PFC_MBC_SHIFT);
	dcbcfg->pfc.pfccap = (u8)((buf[0] & I40E_IEEE_PFC_CAP_MASK) >>
				  I40E_IEEE_PFC_CAP_SHIFT);
	dcbcfg->pfc.pfcenable = buf[1];
पूर्ण

/**
 * i40e_parse_ieee_app_tlv
 * @tlv: IEEE 802.1Qaz APP TLV
 * @dcbcfg: Local store to update APP PRIO data
 *
 * Parses IEEE 802.1Qaz APP PRIO TLV
 **/
अटल व्योम i40e_parse_ieee_app_tlv(काष्ठा i40e_lldp_org_tlv *tlv,
				    काष्ठा i40e_dcbx_config *dcbcfg)
अणु
	u16 typelength;
	u16 offset = 0;
	u16 length;
	पूर्णांक i = 0;
	u8 *buf;

	typelength = ntohs(tlv->typelength);
	length = (u16)((typelength & I40E_LLDP_TLV_LEN_MASK) >>
		       I40E_LLDP_TLV_LEN_SHIFT);
	buf = tlv->tlvinfo;

	/* The App priority table starts 5 octets after TLV header */
	length -= (माप(tlv->ouisubtype) + 1);

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
	जबतक (offset < length) अणु
		dcbcfg->app[i].priority = (u8)((buf[offset] &
						I40E_IEEE_APP_PRIO_MASK) >>
					       I40E_IEEE_APP_PRIO_SHIFT);
		dcbcfg->app[i].selector = (u8)((buf[offset] &
						I40E_IEEE_APP_SEL_MASK) >>
					       I40E_IEEE_APP_SEL_SHIFT);
		dcbcfg->app[i].protocolid = (buf[offset + 1] << 0x8) |
					     buf[offset + 2];
		/* Move to next app */
		offset += 3;
		i++;
		अगर (i >= I40E_DCBX_MAX_APPS)
			अवरोध;
	पूर्ण

	dcbcfg->numapps = i;
पूर्ण

/**
 * i40e_parse_ieee_tlv
 * @tlv: IEEE 802.1Qaz TLV
 * @dcbcfg: Local store to update ETS REC data
 *
 * Get the TLV subtype and send it to parsing function
 * based on the subtype value
 **/
अटल व्योम i40e_parse_ieee_tlv(काष्ठा i40e_lldp_org_tlv *tlv,
				काष्ठा i40e_dcbx_config *dcbcfg)
अणु
	u32 ouisubtype;
	u8 subtype;

	ouisubtype = ntohl(tlv->ouisubtype);
	subtype = (u8)((ouisubtype & I40E_LLDP_TLV_SUBTYPE_MASK) >>
		       I40E_LLDP_TLV_SUBTYPE_SHIFT);
	चयन (subtype) अणु
	हाल I40E_IEEE_SUBTYPE_ETS_CFG:
		i40e_parse_ieee_etscfg_tlv(tlv, dcbcfg);
		अवरोध;
	हाल I40E_IEEE_SUBTYPE_ETS_REC:
		i40e_parse_ieee_etsrec_tlv(tlv, dcbcfg);
		अवरोध;
	हाल I40E_IEEE_SUBTYPE_PFC_CFG:
		i40e_parse_ieee_pfccfg_tlv(tlv, dcbcfg);
		अवरोध;
	हाल I40E_IEEE_SUBTYPE_APP_PRI:
		i40e_parse_ieee_app_tlv(tlv, dcbcfg);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/**
 * i40e_parse_cee_pgcfg_tlv
 * @tlv: CEE DCBX PG CFG TLV
 * @dcbcfg: Local store to update ETS CFG data
 *
 * Parses CEE DCBX PG CFG TLV
 **/
अटल व्योम i40e_parse_cee_pgcfg_tlv(काष्ठा i40e_cee_feat_tlv *tlv,
				     काष्ठा i40e_dcbx_config *dcbcfg)
अणु
	काष्ठा i40e_dcb_ets_config *etscfg;
	u8 *buf = tlv->tlvinfo;
	u16 offset = 0;
	u8 priority;
	पूर्णांक i;

	etscfg = &dcbcfg->etscfg;

	अगर (tlv->en_will_err & I40E_CEE_FEAT_TLV_WILLING_MASK)
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
		priority = (u8)((buf[offset] & I40E_CEE_PGID_PRIO_1_MASK) >>
				 I40E_CEE_PGID_PRIO_1_SHIFT);
		etscfg->prioritytable[i * 2] =  priority;
		priority = (u8)((buf[offset] & I40E_CEE_PGID_PRIO_0_MASK) >>
				 I40E_CEE_PGID_PRIO_0_SHIFT);
		etscfg->prioritytable[i * 2 + 1] = priority;
		offset++;
	पूर्ण

	/* PG Percentage Table (8 octets)
	 * Octets:| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |
	 *        ---------------------------------
	 *        |pg0|pg1|pg2|pg3|pg4|pg5|pg6|pg7|
	 *        ---------------------------------
	 */
	क्रम (i = 0; i < I40E_MAX_TRAFFIC_CLASS; i++)
		etscfg->tcbwtable[i] = buf[offset++];

	/* Number of TCs supported (1 octet) */
	etscfg->maxtcs = buf[offset];
पूर्ण

/**
 * i40e_parse_cee_pfccfg_tlv
 * @tlv: CEE DCBX PFC CFG TLV
 * @dcbcfg: Local store to update PFC CFG data
 *
 * Parses CEE DCBX PFC CFG TLV
 **/
अटल व्योम i40e_parse_cee_pfccfg_tlv(काष्ठा i40e_cee_feat_tlv *tlv,
				      काष्ठा i40e_dcbx_config *dcbcfg)
अणु
	u8 *buf = tlv->tlvinfo;

	अगर (tlv->en_will_err & I40E_CEE_FEAT_TLV_WILLING_MASK)
		dcbcfg->pfc.willing = 1;

	/* ------------------------
	 * | PFC Enable | PFC TCs |
	 * ------------------------
	 * | 1 octet    | 1 octet |
	 */
	dcbcfg->pfc.pfcenable = buf[0];
	dcbcfg->pfc.pfccap = buf[1];
पूर्ण

/**
 * i40e_parse_cee_app_tlv
 * @tlv: CEE DCBX APP TLV
 * @dcbcfg: Local store to update APP PRIO data
 *
 * Parses CEE DCBX APP PRIO TLV
 **/
अटल व्योम i40e_parse_cee_app_tlv(काष्ठा i40e_cee_feat_tlv *tlv,
				   काष्ठा i40e_dcbx_config *dcbcfg)
अणु
	u16 length, typelength, offset = 0;
	काष्ठा i40e_cee_app_prio *app;
	u8 i;

	typelength = ntohs(tlv->hdr.typelen);
	length = (u16)((typelength & I40E_LLDP_TLV_LEN_MASK) >>
		       I40E_LLDP_TLV_LEN_SHIFT);

	dcbcfg->numapps = length / माप(*app);

	अगर (!dcbcfg->numapps)
		वापस;
	अगर (dcbcfg->numapps > I40E_DCBX_MAX_APPS)
		dcbcfg->numapps = I40E_DCBX_MAX_APPS;

	क्रम (i = 0; i < dcbcfg->numapps; i++) अणु
		u8 up, selector;

		app = (काष्ठा i40e_cee_app_prio *)(tlv->tlvinfo + offset);
		क्रम (up = 0; up < I40E_MAX_USER_PRIORITY; up++) अणु
			अगर (app->prio_map & BIT(up))
				अवरोध;
		पूर्ण
		dcbcfg->app[i].priority = up;

		/* Get Selector from lower 2 bits, and convert to IEEE */
		selector = (app->upper_oui_sel & I40E_CEE_APP_SELECTOR_MASK);
		चयन (selector) अणु
		हाल I40E_CEE_APP_SEL_ETHTYPE:
			dcbcfg->app[i].selector = I40E_APP_SEL_ETHTYPE;
			अवरोध;
		हाल I40E_CEE_APP_SEL_TCPIP:
			dcbcfg->app[i].selector = I40E_APP_SEL_TCPIP;
			अवरोध;
		शेष:
			/* Keep selector as it is क्रम unknown types */
			dcbcfg->app[i].selector = selector;
		पूर्ण

		dcbcfg->app[i].protocolid = ntohs(app->protocol);
		/* Move to next app */
		offset += माप(*app);
	पूर्ण
पूर्ण

/**
 * i40e_parse_cee_tlv
 * @tlv: CEE DCBX TLV
 * @dcbcfg: Local store to update DCBX config data
 *
 * Get the TLV subtype and send it to parsing function
 * based on the subtype value
 **/
अटल व्योम i40e_parse_cee_tlv(काष्ठा i40e_lldp_org_tlv *tlv,
			       काष्ठा i40e_dcbx_config *dcbcfg)
अणु
	u16 len, tlvlen, sublen, typelength;
	काष्ठा i40e_cee_feat_tlv *sub_tlv;
	u8 subtype, feat_tlv_count = 0;
	u32 ouisubtype;

	ouisubtype = ntohl(tlv->ouisubtype);
	subtype = (u8)((ouisubtype & I40E_LLDP_TLV_SUBTYPE_MASK) >>
		       I40E_LLDP_TLV_SUBTYPE_SHIFT);
	/* Return अगर not CEE DCBX */
	अगर (subtype != I40E_CEE_DCBX_TYPE)
		वापस;

	typelength = ntohs(tlv->typelength);
	tlvlen = (u16)((typelength & I40E_LLDP_TLV_LEN_MASK) >>
			I40E_LLDP_TLV_LEN_SHIFT);
	len = माप(tlv->typelength) + माप(ouisubtype) +
	      माप(काष्ठा i40e_cee_ctrl_tlv);
	/* Return अगर no CEE DCBX Feature TLVs */
	अगर (tlvlen <= len)
		वापस;

	sub_tlv = (काष्ठा i40e_cee_feat_tlv *)((अक्षर *)tlv + len);
	जबतक (feat_tlv_count < I40E_CEE_MAX_FEAT_TYPE) अणु
		typelength = ntohs(sub_tlv->hdr.typelen);
		sublen = (u16)((typelength &
				I40E_LLDP_TLV_LEN_MASK) >>
				I40E_LLDP_TLV_LEN_SHIFT);
		subtype = (u8)((typelength & I40E_LLDP_TLV_TYPE_MASK) >>
				I40E_LLDP_TLV_TYPE_SHIFT);
		चयन (subtype) अणु
		हाल I40E_CEE_SUBTYPE_PG_CFG:
			i40e_parse_cee_pgcfg_tlv(sub_tlv, dcbcfg);
			अवरोध;
		हाल I40E_CEE_SUBTYPE_PFC_CFG:
			i40e_parse_cee_pfccfg_tlv(sub_tlv, dcbcfg);
			अवरोध;
		हाल I40E_CEE_SUBTYPE_APP_PRI:
			i40e_parse_cee_app_tlv(sub_tlv, dcbcfg);
			अवरोध;
		शेष:
			वापस; /* Invalid Sub-type वापस */
		पूर्ण
		feat_tlv_count++;
		/* Move to next sub TLV */
		sub_tlv = (काष्ठा i40e_cee_feat_tlv *)((अक्षर *)sub_tlv +
						माप(sub_tlv->hdr.typelen) +
						sublen);
	पूर्ण
पूर्ण

/**
 * i40e_parse_org_tlv
 * @tlv: Organization specअगरic TLV
 * @dcbcfg: Local store to update ETS REC data
 *
 * Currently only IEEE 802.1Qaz TLV is supported, all others
 * will be वापसed
 **/
अटल व्योम i40e_parse_org_tlv(काष्ठा i40e_lldp_org_tlv *tlv,
			       काष्ठा i40e_dcbx_config *dcbcfg)
अणु
	u32 ouisubtype;
	u32 oui;

	ouisubtype = ntohl(tlv->ouisubtype);
	oui = (u32)((ouisubtype & I40E_LLDP_TLV_OUI_MASK) >>
		    I40E_LLDP_TLV_OUI_SHIFT);
	चयन (oui) अणु
	हाल I40E_IEEE_8021QAZ_OUI:
		i40e_parse_ieee_tlv(tlv, dcbcfg);
		अवरोध;
	हाल I40E_CEE_DCBX_OUI:
		i40e_parse_cee_tlv(tlv, dcbcfg);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/**
 * i40e_lldp_to_dcb_config
 * @lldpmib: LLDPDU to be parsed
 * @dcbcfg: store क्रम LLDPDU data
 *
 * Parse DCB configuration from the LLDPDU
 **/
i40e_status i40e_lldp_to_dcb_config(u8 *lldpmib,
				    काष्ठा i40e_dcbx_config *dcbcfg)
अणु
	i40e_status ret = 0;
	काष्ठा i40e_lldp_org_tlv *tlv;
	u16 type;
	u16 length;
	u16 typelength;
	u16 offset = 0;

	अगर (!lldpmib || !dcbcfg)
		वापस I40E_ERR_PARAM;

	/* set to the start of LLDPDU */
	lldpmib += ETH_HLEN;
	tlv = (काष्ठा i40e_lldp_org_tlv *)lldpmib;
	जबतक (1) अणु
		typelength = ntohs(tlv->typelength);
		type = (u16)((typelength & I40E_LLDP_TLV_TYPE_MASK) >>
			     I40E_LLDP_TLV_TYPE_SHIFT);
		length = (u16)((typelength & I40E_LLDP_TLV_LEN_MASK) >>
			       I40E_LLDP_TLV_LEN_SHIFT);
		offset += माप(typelength) + length;

		/* END TLV or beyond LLDPDU size */
		अगर ((type == I40E_TLV_TYPE_END) || (offset > I40E_LLDPDU_SIZE))
			अवरोध;

		चयन (type) अणु
		हाल I40E_TLV_TYPE_ORG:
			i40e_parse_org_tlv(tlv, dcbcfg);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		/* Move to next TLV */
		tlv = (काष्ठा i40e_lldp_org_tlv *)((अक्षर *)tlv +
						    माप(tlv->typelength) +
						    length);
	पूर्ण

	वापस ret;
पूर्ण

/**
 * i40e_aq_get_dcb_config
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @mib_type: mib type क्रम the query
 * @bridgetype: bridge type क्रम the query (remote)
 * @dcbcfg: store क्रम LLDPDU data
 *
 * Query DCB configuration from the Firmware
 **/
i40e_status i40e_aq_get_dcb_config(काष्ठा i40e_hw *hw, u8 mib_type,
				   u8 bridgetype,
				   काष्ठा i40e_dcbx_config *dcbcfg)
अणु
	i40e_status ret = 0;
	काष्ठा i40e_virt_mem mem;
	u8 *lldpmib;

	/* Allocate the LLDPDU */
	ret = i40e_allocate_virt_mem(hw, &mem, I40E_LLDPDU_SIZE);
	अगर (ret)
		वापस ret;

	lldpmib = (u8 *)mem.va;
	ret = i40e_aq_get_lldp_mib(hw, bridgetype, mib_type,
				   (व्योम *)lldpmib, I40E_LLDPDU_SIZE,
				   शून्य, शून्य, शून्य);
	अगर (ret)
		जाओ मुक्त_mem;

	/* Parse LLDP MIB to get dcb configuration */
	ret = i40e_lldp_to_dcb_config(lldpmib, dcbcfg);

मुक्त_mem:
	i40e_मुक्त_virt_mem(hw, &mem);
	वापस ret;
पूर्ण

/**
 * i40e_cee_to_dcb_v1_config
 * @cee_cfg: poपूर्णांकer to CEE v1 response configuration काष्ठा
 * @dcbcfg: DCB configuration काष्ठा
 *
 * Convert CEE v1 configuration from firmware to DCB configuration
 **/
अटल व्योम i40e_cee_to_dcb_v1_config(
			काष्ठा i40e_aqc_get_cee_dcb_cfg_v1_resp *cee_cfg,
			काष्ठा i40e_dcbx_config *dcbcfg)
अणु
	u16 status, tlv_status = le16_to_cpu(cee_cfg->tlv_status);
	u16 app_prio = le16_to_cpu(cee_cfg->oper_app_prio);
	u8 i, tc, err;

	/* CEE PG data to ETS config */
	dcbcfg->etscfg.maxtcs = cee_cfg->oper_num_tc;

	/* Note that the FW creates the oper_prio_tc nibbles reversed
	 * from those in the CEE Priority Group sub-TLV.
	 */
	क्रम (i = 0; i < 4; i++) अणु
		tc = (u8)((cee_cfg->oper_prio_tc[i] &
			 I40E_CEE_PGID_PRIO_0_MASK) >>
			 I40E_CEE_PGID_PRIO_0_SHIFT);
		dcbcfg->etscfg.prioritytable[i * 2] =  tc;
		tc = (u8)((cee_cfg->oper_prio_tc[i] &
			 I40E_CEE_PGID_PRIO_1_MASK) >>
			 I40E_CEE_PGID_PRIO_1_SHIFT);
		dcbcfg->etscfg.prioritytable[i*2 + 1] = tc;
	पूर्ण

	क्रम (i = 0; i < I40E_MAX_TRAFFIC_CLASS; i++)
		dcbcfg->etscfg.tcbwtable[i] = cee_cfg->oper_tc_bw[i];

	क्रम (i = 0; i < I40E_MAX_TRAFFIC_CLASS; i++) अणु
		अगर (dcbcfg->etscfg.prioritytable[i] == I40E_CEE_PGID_STRICT) अणु
			/* Map it to next empty TC */
			dcbcfg->etscfg.prioritytable[i] =
						cee_cfg->oper_num_tc - 1;
			dcbcfg->etscfg.tsatable[i] = I40E_IEEE_TSA_STRICT;
		पूर्ण अन्यथा अणु
			dcbcfg->etscfg.tsatable[i] = I40E_IEEE_TSA_ETS;
		पूर्ण
	पूर्ण

	/* CEE PFC data to ETS config */
	dcbcfg->pfc.pfcenable = cee_cfg->oper_pfc_en;
	dcbcfg->pfc.pfccap = I40E_MAX_TRAFFIC_CLASS;

	status = (tlv_status & I40E_AQC_CEE_APP_STATUS_MASK) >>
		  I40E_AQC_CEE_APP_STATUS_SHIFT;
	err = (status & I40E_TLV_STATUS_ERR) ? 1 : 0;
	/* Add APPs अगर Error is False */
	अगर (!err) अणु
		/* CEE operating configuration supports FCoE/iSCSI/FIP only */
		dcbcfg->numapps = I40E_CEE_OPER_MAX_APPS;

		/* FCoE APP */
		dcbcfg->app[0].priority =
			(app_prio & I40E_AQC_CEE_APP_FCOE_MASK) >>
			 I40E_AQC_CEE_APP_FCOE_SHIFT;
		dcbcfg->app[0].selector = I40E_APP_SEL_ETHTYPE;
		dcbcfg->app[0].protocolid = I40E_APP_PROTOID_FCOE;

		/* iSCSI APP */
		dcbcfg->app[1].priority =
			(app_prio & I40E_AQC_CEE_APP_ISCSI_MASK) >>
			 I40E_AQC_CEE_APP_ISCSI_SHIFT;
		dcbcfg->app[1].selector = I40E_APP_SEL_TCPIP;
		dcbcfg->app[1].protocolid = I40E_APP_PROTOID_ISCSI;

		/* FIP APP */
		dcbcfg->app[2].priority =
			(app_prio & I40E_AQC_CEE_APP_FIP_MASK) >>
			 I40E_AQC_CEE_APP_FIP_SHIFT;
		dcbcfg->app[2].selector = I40E_APP_SEL_ETHTYPE;
		dcbcfg->app[2].protocolid = I40E_APP_PROTOID_FIP;
	पूर्ण
पूर्ण

/**
 * i40e_cee_to_dcb_config
 * @cee_cfg: poपूर्णांकer to CEE configuration काष्ठा
 * @dcbcfg: DCB configuration काष्ठा
 *
 * Convert CEE configuration from firmware to DCB configuration
 **/
अटल व्योम i40e_cee_to_dcb_config(
				काष्ठा i40e_aqc_get_cee_dcb_cfg_resp *cee_cfg,
				काष्ठा i40e_dcbx_config *dcbcfg)
अणु
	u32 status, tlv_status = le32_to_cpu(cee_cfg->tlv_status);
	u16 app_prio = le16_to_cpu(cee_cfg->oper_app_prio);
	u8 i, tc, err, sync, oper;

	/* CEE PG data to ETS config */
	dcbcfg->etscfg.maxtcs = cee_cfg->oper_num_tc;

	/* Note that the FW creates the oper_prio_tc nibbles reversed
	 * from those in the CEE Priority Group sub-TLV.
	 */
	क्रम (i = 0; i < 4; i++) अणु
		tc = (u8)((cee_cfg->oper_prio_tc[i] &
			 I40E_CEE_PGID_PRIO_0_MASK) >>
			 I40E_CEE_PGID_PRIO_0_SHIFT);
		dcbcfg->etscfg.prioritytable[i * 2] =  tc;
		tc = (u8)((cee_cfg->oper_prio_tc[i] &
			 I40E_CEE_PGID_PRIO_1_MASK) >>
			 I40E_CEE_PGID_PRIO_1_SHIFT);
		dcbcfg->etscfg.prioritytable[i * 2 + 1] = tc;
	पूर्ण

	क्रम (i = 0; i < I40E_MAX_TRAFFIC_CLASS; i++)
		dcbcfg->etscfg.tcbwtable[i] = cee_cfg->oper_tc_bw[i];

	क्रम (i = 0; i < I40E_MAX_TRAFFIC_CLASS; i++) अणु
		अगर (dcbcfg->etscfg.prioritytable[i] == I40E_CEE_PGID_STRICT) अणु
			/* Map it to next empty TC */
			dcbcfg->etscfg.prioritytable[i] =
						cee_cfg->oper_num_tc - 1;
			dcbcfg->etscfg.tsatable[i] = I40E_IEEE_TSA_STRICT;
		पूर्ण अन्यथा अणु
			dcbcfg->etscfg.tsatable[i] = I40E_IEEE_TSA_ETS;
		पूर्ण
	पूर्ण

	/* CEE PFC data to ETS config */
	dcbcfg->pfc.pfcenable = cee_cfg->oper_pfc_en;
	dcbcfg->pfc.pfccap = I40E_MAX_TRAFFIC_CLASS;

	i = 0;
	status = (tlv_status & I40E_AQC_CEE_FCOE_STATUS_MASK) >>
		  I40E_AQC_CEE_FCOE_STATUS_SHIFT;
	err = (status & I40E_TLV_STATUS_ERR) ? 1 : 0;
	sync = (status & I40E_TLV_STATUS_SYNC) ? 1 : 0;
	oper = (status & I40E_TLV_STATUS_OPER) ? 1 : 0;
	/* Add FCoE APP अगर Error is False and Oper/Sync is True */
	अगर (!err && sync && oper) अणु
		/* FCoE APP */
		dcbcfg->app[i].priority =
			(app_prio & I40E_AQC_CEE_APP_FCOE_MASK) >>
			 I40E_AQC_CEE_APP_FCOE_SHIFT;
		dcbcfg->app[i].selector = I40E_APP_SEL_ETHTYPE;
		dcbcfg->app[i].protocolid = I40E_APP_PROTOID_FCOE;
		i++;
	पूर्ण

	status = (tlv_status & I40E_AQC_CEE_ISCSI_STATUS_MASK) >>
		  I40E_AQC_CEE_ISCSI_STATUS_SHIFT;
	err = (status & I40E_TLV_STATUS_ERR) ? 1 : 0;
	sync = (status & I40E_TLV_STATUS_SYNC) ? 1 : 0;
	oper = (status & I40E_TLV_STATUS_OPER) ? 1 : 0;
	/* Add iSCSI APP अगर Error is False and Oper/Sync is True */
	अगर (!err && sync && oper) अणु
		/* iSCSI APP */
		dcbcfg->app[i].priority =
			(app_prio & I40E_AQC_CEE_APP_ISCSI_MASK) >>
			 I40E_AQC_CEE_APP_ISCSI_SHIFT;
		dcbcfg->app[i].selector = I40E_APP_SEL_TCPIP;
		dcbcfg->app[i].protocolid = I40E_APP_PROTOID_ISCSI;
		i++;
	पूर्ण

	status = (tlv_status & I40E_AQC_CEE_FIP_STATUS_MASK) >>
		  I40E_AQC_CEE_FIP_STATUS_SHIFT;
	err = (status & I40E_TLV_STATUS_ERR) ? 1 : 0;
	sync = (status & I40E_TLV_STATUS_SYNC) ? 1 : 0;
	oper = (status & I40E_TLV_STATUS_OPER) ? 1 : 0;
	/* Add FIP APP अगर Error is False and Oper/Sync is True */
	अगर (!err && sync && oper) अणु
		/* FIP APP */
		dcbcfg->app[i].priority =
			(app_prio & I40E_AQC_CEE_APP_FIP_MASK) >>
			 I40E_AQC_CEE_APP_FIP_SHIFT;
		dcbcfg->app[i].selector = I40E_APP_SEL_ETHTYPE;
		dcbcfg->app[i].protocolid = I40E_APP_PROTOID_FIP;
		i++;
	पूर्ण
	dcbcfg->numapps = i;
पूर्ण

/**
 * i40e_get_ieee_dcb_config
 * @hw: poपूर्णांकer to the hw काष्ठा
 *
 * Get IEEE mode DCB configuration from the Firmware
 **/
अटल i40e_status i40e_get_ieee_dcb_config(काष्ठा i40e_hw *hw)
अणु
	i40e_status ret = 0;

	/* IEEE mode */
	hw->local_dcbx_config.dcbx_mode = I40E_DCBX_MODE_IEEE;
	/* Get Local DCB Config */
	ret = i40e_aq_get_dcb_config(hw, I40E_AQ_LLDP_MIB_LOCAL, 0,
				     &hw->local_dcbx_config);
	अगर (ret)
		जाओ out;

	/* Get Remote DCB Config */
	ret = i40e_aq_get_dcb_config(hw, I40E_AQ_LLDP_MIB_REMOTE,
				     I40E_AQ_LLDP_BRIDGE_TYPE_NEAREST_BRIDGE,
				     &hw->remote_dcbx_config);
	/* Don't treat ENOENT as an error क्रम Remote MIBs */
	अगर (hw->aq.asq_last_status == I40E_AQ_RC_ENOENT)
		ret = 0;

out:
	वापस ret;
पूर्ण

/**
 * i40e_get_dcb_config
 * @hw: poपूर्णांकer to the hw काष्ठा
 *
 * Get DCB configuration from the Firmware
 **/
i40e_status i40e_get_dcb_config(काष्ठा i40e_hw *hw)
अणु
	i40e_status ret = 0;
	काष्ठा i40e_aqc_get_cee_dcb_cfg_resp cee_cfg;
	काष्ठा i40e_aqc_get_cee_dcb_cfg_v1_resp cee_v1_cfg;

	/* If Firmware version < v4.33 on X710/XL710, IEEE only */
	अगर ((hw->mac.type == I40E_MAC_XL710) &&
	    (((hw->aq.fw_maj_ver == 4) && (hw->aq.fw_min_ver < 33)) ||
	      (hw->aq.fw_maj_ver < 4)))
		वापस i40e_get_ieee_dcb_config(hw);

	/* If Firmware version == v4.33 on X710/XL710, use old CEE काष्ठा */
	अगर ((hw->mac.type == I40E_MAC_XL710) &&
	    ((hw->aq.fw_maj_ver == 4) && (hw->aq.fw_min_ver == 33))) अणु
		ret = i40e_aq_get_cee_dcb_config(hw, &cee_v1_cfg,
						 माप(cee_v1_cfg), शून्य);
		अगर (!ret) अणु
			/* CEE mode */
			hw->local_dcbx_config.dcbx_mode = I40E_DCBX_MODE_CEE;
			hw->local_dcbx_config.tlv_status =
					le16_to_cpu(cee_v1_cfg.tlv_status);
			i40e_cee_to_dcb_v1_config(&cee_v1_cfg,
						  &hw->local_dcbx_config);
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = i40e_aq_get_cee_dcb_config(hw, &cee_cfg,
						 माप(cee_cfg), शून्य);
		अगर (!ret) अणु
			/* CEE mode */
			hw->local_dcbx_config.dcbx_mode = I40E_DCBX_MODE_CEE;
			hw->local_dcbx_config.tlv_status =
					le32_to_cpu(cee_cfg.tlv_status);
			i40e_cee_to_dcb_config(&cee_cfg,
					       &hw->local_dcbx_config);
		पूर्ण
	पूर्ण

	/* CEE mode not enabled try querying IEEE data */
	अगर (hw->aq.asq_last_status == I40E_AQ_RC_ENOENT)
		वापस i40e_get_ieee_dcb_config(hw);

	अगर (ret)
		जाओ out;

	/* Get CEE DCB Desired Config */
	ret = i40e_aq_get_dcb_config(hw, I40E_AQ_LLDP_MIB_LOCAL, 0,
				     &hw->desired_dcbx_config);
	अगर (ret)
		जाओ out;

	/* Get Remote DCB Config */
	ret = i40e_aq_get_dcb_config(hw, I40E_AQ_LLDP_MIB_REMOTE,
				     I40E_AQ_LLDP_BRIDGE_TYPE_NEAREST_BRIDGE,
				     &hw->remote_dcbx_config);
	/* Don't treat ENOENT as an error क्रम Remote MIBs */
	अगर (hw->aq.asq_last_status == I40E_AQ_RC_ENOENT)
		ret = 0;

out:
	वापस ret;
पूर्ण

/**
 * i40e_init_dcb
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @enable_mib_change: enable mib change event
 *
 * Update DCB configuration from the Firmware
 **/
i40e_status i40e_init_dcb(काष्ठा i40e_hw *hw, bool enable_mib_change)
अणु
	i40e_status ret = 0;
	काष्ठा i40e_lldp_variables lldp_cfg;
	u8 adminstatus = 0;

	अगर (!hw->func_caps.dcb)
		वापस I40E_NOT_SUPPORTED;

	/* Read LLDP NVM area */
	अगर (hw->flags & I40E_HW_FLAG_FW_LLDP_PERSISTENT) अणु
		u8 offset = 0;

		अगर (hw->mac.type == I40E_MAC_XL710)
			offset = I40E_LLDP_CURRENT_STATUS_XL710_OFFSET;
		अन्यथा अगर (hw->mac.type == I40E_MAC_X722)
			offset = I40E_LLDP_CURRENT_STATUS_X722_OFFSET;
		अन्यथा
			वापस I40E_NOT_SUPPORTED;

		ret = i40e_पढ़ो_nvm_module_data(hw,
						I40E_SR_EMP_SR_SETTINGS_PTR,
						offset,
						I40E_LLDP_CURRENT_STATUS_OFFSET,
						I40E_LLDP_CURRENT_STATUS_SIZE,
						&lldp_cfg.adminstatus);
	पूर्ण अन्यथा अणु
		ret = i40e_पढ़ो_lldp_cfg(hw, &lldp_cfg);
	पूर्ण
	अगर (ret)
		वापस I40E_ERR_NOT_READY;

	/* Get the LLDP AdminStatus क्रम the current port */
	adminstatus = lldp_cfg.adminstatus >> (hw->port * 4);
	adminstatus &= 0xF;

	/* LLDP agent disabled */
	अगर (!adminstatus) अणु
		hw->dcbx_status = I40E_DCBX_STATUS_DISABLED;
		वापस I40E_ERR_NOT_READY;
	पूर्ण

	/* Get DCBX status */
	ret = i40e_get_dcbx_status(hw, &hw->dcbx_status);
	अगर (ret)
		वापस ret;

	/* Check the DCBX Status */
	अगर (hw->dcbx_status == I40E_DCBX_STATUS_DONE ||
	    hw->dcbx_status == I40E_DCBX_STATUS_IN_PROGRESS) अणु
		/* Get current DCBX configuration */
		ret = i40e_get_dcb_config(hw);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अगर (hw->dcbx_status == I40E_DCBX_STATUS_DISABLED) अणु
		वापस I40E_ERR_NOT_READY;
	पूर्ण

	/* Configure the LLDP MIB change event */
	अगर (enable_mib_change)
		ret = i40e_aq_cfg_lldp_mib_change_event(hw, true, शून्य);

	वापस ret;
पूर्ण

/**
 * i40e_get_fw_lldp_status
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @lldp_status: poपूर्णांकer to the status क्रमागत
 *
 * Get status of FW Link Layer Discovery Protocol (LLDP) Agent.
 * Status of agent is reported via @lldp_status parameter.
 **/
क्रमागत i40e_status_code
i40e_get_fw_lldp_status(काष्ठा i40e_hw *hw,
			क्रमागत i40e_get_fw_lldp_status_resp *lldp_status)
अणु
	काष्ठा i40e_virt_mem mem;
	i40e_status ret;
	u8 *lldpmib;

	अगर (!lldp_status)
		वापस I40E_ERR_PARAM;

	/* Allocate buffer क्रम the LLDPDU */
	ret = i40e_allocate_virt_mem(hw, &mem, I40E_LLDPDU_SIZE);
	अगर (ret)
		वापस ret;

	lldpmib = (u8 *)mem.va;
	ret = i40e_aq_get_lldp_mib(hw, 0, 0, (व्योम *)lldpmib,
				   I40E_LLDPDU_SIZE, शून्य, शून्य, शून्य);

	अगर (!ret) अणु
		*lldp_status = I40E_GET_FW_LLDP_STATUS_ENABLED;
	पूर्ण अन्यथा अगर (hw->aq.asq_last_status == I40E_AQ_RC_ENOENT) अणु
		/* MIB is not available yet but the agent is running */
		*lldp_status = I40E_GET_FW_LLDP_STATUS_ENABLED;
		ret = 0;
	पूर्ण अन्यथा अगर (hw->aq.asq_last_status == I40E_AQ_RC_EPERM) अणु
		*lldp_status = I40E_GET_FW_LLDP_STATUS_DISABLED;
		ret = 0;
	पूर्ण

	i40e_मुक्त_virt_mem(hw, &mem);
	वापस ret;
पूर्ण

/**
 * i40e_add_ieee_ets_tlv - Prepare ETS TLV in IEEE क्रमmat
 * @tlv: Fill the ETS config data in IEEE क्रमmat
 * @dcbcfg: Local store which holds the DCB Config
 *
 * Prepare IEEE 802.1Qaz ETS CFG TLV
 **/
अटल व्योम i40e_add_ieee_ets_tlv(काष्ठा i40e_lldp_org_tlv *tlv,
				  काष्ठा i40e_dcbx_config *dcbcfg)
अणु
	u8 priority0, priority1, maxtcwilling = 0;
	काष्ठा i40e_dcb_ets_config *etscfg;
	u16 offset = 0, typelength, i;
	u8 *buf = tlv->tlvinfo;
	u32 ouisubtype;

	typelength = (u16)((I40E_TLV_TYPE_ORG << I40E_LLDP_TLV_TYPE_SHIFT) |
			I40E_IEEE_ETS_TLV_LENGTH);
	tlv->typelength = htons(typelength);

	ouisubtype = (u32)((I40E_IEEE_8021QAZ_OUI << I40E_LLDP_TLV_OUI_SHIFT) |
			I40E_IEEE_SUBTYPE_ETS_CFG);
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
		maxtcwilling = BIT(I40E_IEEE_ETS_WILLING_SHIFT);
	maxtcwilling |= etscfg->maxtcs & I40E_IEEE_ETS_MAXTC_MASK;
	buf[offset] = maxtcwilling;

	/* Move offset to Priority Assignment Table */
	offset++;

	/* Priority Assignment Table (4 octets)
	 * Octets:|    1    |    2    |    3    |    4    |
	 *        -----------------------------------------
	 *        |pri0|pri1|pri2|pri3|pri4|pri5|pri6|pri7|
	 *        -----------------------------------------
	 *   Bits:|7  4|3  0|7  4|3  0|7  4|3  0|7  4|3  0|
	 *        -----------------------------------------
	 */
	क्रम (i = 0; i < 4; i++) अणु
		priority0 = etscfg->prioritytable[i * 2] & 0xF;
		priority1 = etscfg->prioritytable[i * 2 + 1] & 0xF;
		buf[offset] = (priority0 << I40E_IEEE_ETS_PRIO_1_SHIFT) |
				priority1;
		offset++;
	पूर्ण

	/* TC Bandwidth Table (8 octets)
	 * Octets:| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |
	 *        ---------------------------------
	 *        |tc0|tc1|tc2|tc3|tc4|tc5|tc6|tc7|
	 *        ---------------------------------
	 */
	क्रम (i = 0; i < I40E_MAX_TRAFFIC_CLASS; i++)
		buf[offset++] = etscfg->tcbwtable[i];

	/* TSA Assignment Table (8 octets)
	 * Octets:| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |
	 *        ---------------------------------
	 *        |tc0|tc1|tc2|tc3|tc4|tc5|tc6|tc7|
	 *        ---------------------------------
	 */
	क्रम (i = 0; i < I40E_MAX_TRAFFIC_CLASS; i++)
		buf[offset++] = etscfg->tsatable[i];
पूर्ण

/**
 * i40e_add_ieee_etsrec_tlv - Prepare ETS Recommended TLV in IEEE क्रमmat
 * @tlv: Fill ETS Recommended TLV in IEEE क्रमmat
 * @dcbcfg: Local store which holds the DCB Config
 *
 * Prepare IEEE 802.1Qaz ETS REC TLV
 **/
अटल व्योम i40e_add_ieee_etsrec_tlv(काष्ठा i40e_lldp_org_tlv *tlv,
				     काष्ठा i40e_dcbx_config *dcbcfg)
अणु
	काष्ठा i40e_dcb_ets_config *etsrec;
	u16 offset = 0, typelength, i;
	u8 priority0, priority1;
	u8 *buf = tlv->tlvinfo;
	u32 ouisubtype;

	typelength = (u16)((I40E_TLV_TYPE_ORG << I40E_LLDP_TLV_TYPE_SHIFT) |
			I40E_IEEE_ETS_TLV_LENGTH);
	tlv->typelength = htons(typelength);

	ouisubtype = (u32)((I40E_IEEE_8021QAZ_OUI << I40E_LLDP_TLV_OUI_SHIFT) |
			I40E_IEEE_SUBTYPE_ETS_REC);
	tlv->ouisubtype = htonl(ouisubtype);

	etsrec = &dcbcfg->etsrec;
	/* First Octet is reserved */
	/* Move offset to Priority Assignment Table */
	offset++;

	/* Priority Assignment Table (4 octets)
	 * Octets:|    1    |    2    |    3    |    4    |
	 *        -----------------------------------------
	 *        |pri0|pri1|pri2|pri3|pri4|pri5|pri6|pri7|
	 *        -----------------------------------------
	 *   Bits:|7  4|3  0|7  4|3  0|7  4|3  0|7  4|3  0|
	 *        -----------------------------------------
	 */
	क्रम (i = 0; i < 4; i++) अणु
		priority0 = etsrec->prioritytable[i * 2] & 0xF;
		priority1 = etsrec->prioritytable[i * 2 + 1] & 0xF;
		buf[offset] = (priority0 << I40E_IEEE_ETS_PRIO_1_SHIFT) |
				priority1;
		offset++;
	पूर्ण

	/* TC Bandwidth Table (8 octets)
	 * Octets:| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |
	 *        ---------------------------------
	 *        |tc0|tc1|tc2|tc3|tc4|tc5|tc6|tc7|
	 *        ---------------------------------
	 */
	क्रम (i = 0; i < I40E_MAX_TRAFFIC_CLASS; i++)
		buf[offset++] = etsrec->tcbwtable[i];

	/* TSA Assignment Table (8 octets)
	 * Octets:| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |
	 *        ---------------------------------
	 *        |tc0|tc1|tc2|tc3|tc4|tc5|tc6|tc7|
	 *        ---------------------------------
	 */
	क्रम (i = 0; i < I40E_MAX_TRAFFIC_CLASS; i++)
		buf[offset++] = etsrec->tsatable[i];
पूर्ण

/**
 * i40e_add_ieee_pfc_tlv - Prepare PFC TLV in IEEE क्रमmat
 * @tlv: Fill PFC TLV in IEEE क्रमmat
 * @dcbcfg: Local store to get PFC CFG data
 *
 * Prepare IEEE 802.1Qaz PFC CFG TLV
 **/
अटल व्योम i40e_add_ieee_pfc_tlv(काष्ठा i40e_lldp_org_tlv *tlv,
				  काष्ठा i40e_dcbx_config *dcbcfg)
अणु
	u8 *buf = tlv->tlvinfo;
	u32 ouisubtype;
	u16 typelength;

	typelength = (u16)((I40E_TLV_TYPE_ORG << I40E_LLDP_TLV_TYPE_SHIFT) |
			I40E_IEEE_PFC_TLV_LENGTH);
	tlv->typelength = htons(typelength);

	ouisubtype = (u32)((I40E_IEEE_8021QAZ_OUI << I40E_LLDP_TLV_OUI_SHIFT) |
			I40E_IEEE_SUBTYPE_PFC_CFG);
	tlv->ouisubtype = htonl(ouisubtype);

	/* ----------------------------------------
	 * |will-|MBC  | Re-  | PFC |  PFC Enable  |
	 * |ing  |     |served| cap |              |
	 * -----------------------------------------
	 * |1bit | 1bit|2 bits|4bits| 1 octet      |
	 */
	अगर (dcbcfg->pfc.willing)
		buf[0] = BIT(I40E_IEEE_PFC_WILLING_SHIFT);

	अगर (dcbcfg->pfc.mbc)
		buf[0] |= BIT(I40E_IEEE_PFC_MBC_SHIFT);

	buf[0] |= dcbcfg->pfc.pfccap & 0xF;
	buf[1] = dcbcfg->pfc.pfcenable;
पूर्ण

/**
 * i40e_add_ieee_app_pri_tlv -  Prepare APP TLV in IEEE क्रमmat
 * @tlv: Fill APP TLV in IEEE क्रमmat
 * @dcbcfg: Local store to get APP CFG data
 *
 * Prepare IEEE 802.1Qaz APP CFG TLV
 **/
अटल व्योम i40e_add_ieee_app_pri_tlv(काष्ठा i40e_lldp_org_tlv *tlv,
				      काष्ठा i40e_dcbx_config *dcbcfg)
अणु
	u16 typelength, length, offset = 0;
	u8 priority, selector, i = 0;
	u8 *buf = tlv->tlvinfo;
	u32 ouisubtype;

	/* No APP TLVs then just वापस */
	अगर (dcbcfg->numapps == 0)
		वापस;
	ouisubtype = (u32)((I40E_IEEE_8021QAZ_OUI << I40E_LLDP_TLV_OUI_SHIFT) |
			I40E_IEEE_SUBTYPE_APP_PRI);
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
		buf[offset] = (priority << I40E_IEEE_APP_PRIO_SHIFT) | selector;
		buf[offset + 1] = (dcbcfg->app[i].protocolid >> 0x8) & 0xFF;
		buf[offset + 2] =  dcbcfg->app[i].protocolid & 0xFF;
		/* Move to next app */
		offset += 3;
		i++;
		अगर (i >= I40E_DCBX_MAX_APPS)
			अवरोध;
	पूर्ण
	/* length includes size of ouisubtype + 1 reserved + 3*numapps */
	length = माप(tlv->ouisubtype) + 1 + (i * 3);
	typelength = (u16)((I40E_TLV_TYPE_ORG << I40E_LLDP_TLV_TYPE_SHIFT) |
		(length & 0x1FF));
	tlv->typelength = htons(typelength);
पूर्ण

/**
 * i40e_add_dcb_tlv - Add all IEEE TLVs
 * @tlv: poपूर्णांकer to org tlv
 * @dcbcfg: poपूर्णांकer to modअगरied dcbx config काष्ठाure *
 * @tlvid: tlv id to be added
 * add tlv inक्रमmation
 **/
अटल व्योम i40e_add_dcb_tlv(काष्ठा i40e_lldp_org_tlv *tlv,
			     काष्ठा i40e_dcbx_config *dcbcfg,
			     u16 tlvid)
अणु
	चयन (tlvid) अणु
	हाल I40E_IEEE_TLV_ID_ETS_CFG:
		i40e_add_ieee_ets_tlv(tlv, dcbcfg);
		अवरोध;
	हाल I40E_IEEE_TLV_ID_ETS_REC:
		i40e_add_ieee_etsrec_tlv(tlv, dcbcfg);
		अवरोध;
	हाल I40E_IEEE_TLV_ID_PFC_CFG:
		i40e_add_ieee_pfc_tlv(tlv, dcbcfg);
		अवरोध;
	हाल I40E_IEEE_TLV_ID_APP_PRI:
		i40e_add_ieee_app_pri_tlv(tlv, dcbcfg);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/**
 * i40e_set_dcb_config - Set the local LLDP MIB to FW
 * @hw: poपूर्णांकer to the hw काष्ठा
 *
 * Set DCB configuration to the Firmware
 **/
i40e_status i40e_set_dcb_config(काष्ठा i40e_hw *hw)
अणु
	काष्ठा i40e_dcbx_config *dcbcfg;
	काष्ठा i40e_virt_mem mem;
	u8 mib_type, *lldpmib;
	i40e_status ret;
	u16 miblen;

	/* update the hw local config */
	dcbcfg = &hw->local_dcbx_config;
	/* Allocate the LLDPDU */
	ret = i40e_allocate_virt_mem(hw, &mem, I40E_LLDPDU_SIZE);
	अगर (ret)
		वापस ret;

	mib_type = SET_LOCAL_MIB_AC_TYPE_LOCAL_MIB;
	अगर (dcbcfg->app_mode == I40E_DCBX_APPS_NON_WILLING) अणु
		mib_type |= SET_LOCAL_MIB_AC_TYPE_NON_WILLING_APPS <<
			    SET_LOCAL_MIB_AC_TYPE_NON_WILLING_APPS_SHIFT;
	पूर्ण
	lldpmib = (u8 *)mem.va;
	i40e_dcb_config_to_lldp(lldpmib, &miblen, dcbcfg);
	ret = i40e_aq_set_lldp_mib(hw, mib_type, (व्योम *)lldpmib, miblen, शून्य);

	i40e_मुक्त_virt_mem(hw, &mem);
	वापस ret;
पूर्ण

/**
 * i40e_dcb_config_to_lldp - Convert Dcbconfig to MIB क्रमmat
 * @lldpmib: poपूर्णांकer to mib to be output
 * @miblen: poपूर्णांकer to u16 क्रम length of lldpmib
 * @dcbcfg: store क्रम LLDPDU data
 *
 * send DCB configuration to FW
 **/
i40e_status i40e_dcb_config_to_lldp(u8 *lldpmib, u16 *miblen,
				    काष्ठा i40e_dcbx_config *dcbcfg)
अणु
	u16 length, offset = 0, tlvid, typelength;
	काष्ठा i40e_lldp_org_tlv *tlv;

	tlv = (काष्ठा i40e_lldp_org_tlv *)lldpmib;
	tlvid = I40E_TLV_ID_START;
	करो अणु
		i40e_add_dcb_tlv(tlv, dcbcfg, tlvid++);
		typelength = ntohs(tlv->typelength);
		length = (u16)((typelength & I40E_LLDP_TLV_LEN_MASK) >>
				I40E_LLDP_TLV_LEN_SHIFT);
		अगर (length)
			offset += length + I40E_IEEE_TLV_HEADER_LENGTH;
		/* END TLV or beyond LLDPDU size */
		अगर (tlvid >= I40E_TLV_ID_END_OF_LLDPPDU ||
		    offset >= I40E_LLDPDU_SIZE)
			अवरोध;
		/* Move to next TLV */
		अगर (length)
			tlv = (काष्ठा i40e_lldp_org_tlv *)((अक्षर *)tlv +
			      माप(tlv->typelength) + length);
	पूर्ण जबतक (tlvid < I40E_TLV_ID_END_OF_LLDPPDU);
	*miblen = offset;
	वापस I40E_SUCCESS;
पूर्ण

/**
 * i40e_dcb_hw_rx_fअगरo_config
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @ets_mode: Strict Priority or Round Robin mode
 * @non_ets_mode: Strict Priority or Round Robin
 * @max_exponent: Exponent to calculate max refill credits
 * @lltc_map: Low latency TC biपंचांगap
 *
 * Configure HW Rx FIFO as part of DCB configuration.
 **/
व्योम i40e_dcb_hw_rx_fअगरo_config(काष्ठा i40e_hw *hw,
				क्रमागत i40e_dcb_arbiter_mode ets_mode,
				क्रमागत i40e_dcb_arbiter_mode non_ets_mode,
				u32 max_exponent,
				u8 lltc_map)
अणु
	u32 reg = rd32(hw, I40E_PRTDCB_RETSC);

	reg &= ~I40E_PRTDCB_RETSC_ETS_MODE_MASK;
	reg |= ((u32)ets_mode << I40E_PRTDCB_RETSC_ETS_MODE_SHIFT) &
		I40E_PRTDCB_RETSC_ETS_MODE_MASK;

	reg &= ~I40E_PRTDCB_RETSC_NON_ETS_MODE_MASK;
	reg |= ((u32)non_ets_mode << I40E_PRTDCB_RETSC_NON_ETS_MODE_SHIFT) &
		I40E_PRTDCB_RETSC_NON_ETS_MODE_MASK;

	reg &= ~I40E_PRTDCB_RETSC_ETS_MAX_EXP_MASK;
	reg |= (max_exponent << I40E_PRTDCB_RETSC_ETS_MAX_EXP_SHIFT) &
		I40E_PRTDCB_RETSC_ETS_MAX_EXP_MASK;

	reg &= ~I40E_PRTDCB_RETSC_LLTC_MASK;
	reg |= (lltc_map << I40E_PRTDCB_RETSC_LLTC_SHIFT) &
		I40E_PRTDCB_RETSC_LLTC_MASK;
	wr32(hw, I40E_PRTDCB_RETSC, reg);
पूर्ण

/**
 * i40e_dcb_hw_rx_cmd_monitor_config
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @num_tc: Total number of traffic class
 * @num_ports: Total number of ports on device
 *
 * Configure HW Rx command monitor as part of DCB configuration.
 **/
व्योम i40e_dcb_hw_rx_cmd_monitor_config(काष्ठा i40e_hw *hw,
				       u8 num_tc, u8 num_ports)
अणु
	u32 threshold;
	u32 fअगरo_size;
	u32 reg;

	/* Set the threshold and fअगरo_size based on number of ports */
	चयन (num_ports) अणु
	हाल 1:
		threshold = I40E_DCB_1_PORT_THRESHOLD;
		fअगरo_size = I40E_DCB_1_PORT_FIFO_SIZE;
		अवरोध;
	हाल 2:
		अगर (num_tc > 4) अणु
			threshold = I40E_DCB_2_PORT_THRESHOLD_HIGH_NUM_TC;
			fअगरo_size = I40E_DCB_2_PORT_FIFO_SIZE_HIGH_NUM_TC;
		पूर्ण अन्यथा अणु
			threshold = I40E_DCB_2_PORT_THRESHOLD_LOW_NUM_TC;
			fअगरo_size = I40E_DCB_2_PORT_FIFO_SIZE_LOW_NUM_TC;
		पूर्ण
		अवरोध;
	हाल 4:
		अगर (num_tc > 4) अणु
			threshold = I40E_DCB_4_PORT_THRESHOLD_HIGH_NUM_TC;
			fअगरo_size = I40E_DCB_4_PORT_FIFO_SIZE_HIGH_NUM_TC;
		पूर्ण अन्यथा अणु
			threshold = I40E_DCB_4_PORT_THRESHOLD_LOW_NUM_TC;
			fअगरo_size = I40E_DCB_4_PORT_FIFO_SIZE_LOW_NUM_TC;
		पूर्ण
		अवरोध;
	शेष:
		i40e_debug(hw, I40E_DEBUG_DCB, "Invalid num_ports %u.\n",
			   (u32)num_ports);
		वापस;
	पूर्ण

	/* The hardware manual describes setting up of I40E_PRT_SWR_PM_THR
	 * based on the number of ports and traffic classes क्रम a given port as
	 * part of DCB configuration.
	 */
	reg = rd32(hw, I40E_PRT_SWR_PM_THR);
	reg &= ~I40E_PRT_SWR_PM_THR_THRESHOLD_MASK;
	reg |= (threshold << I40E_PRT_SWR_PM_THR_THRESHOLD_SHIFT) &
		I40E_PRT_SWR_PM_THR_THRESHOLD_MASK;
	wr32(hw, I40E_PRT_SWR_PM_THR, reg);

	reg = rd32(hw, I40E_PRTDCB_RPPMC);
	reg &= ~I40E_PRTDCB_RPPMC_RX_FIFO_SIZE_MASK;
	reg |= (fअगरo_size << I40E_PRTDCB_RPPMC_RX_FIFO_SIZE_SHIFT) &
		I40E_PRTDCB_RPPMC_RX_FIFO_SIZE_MASK;
	wr32(hw, I40E_PRTDCB_RPPMC, reg);
पूर्ण

/**
 * i40e_dcb_hw_pfc_config
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @pfc_en: Biपंचांगap of PFC enabled priorities
 * @prio_tc: priority to tc assignment indexed by priority
 *
 * Configure HW Priority Flow Controller as part of DCB configuration.
 **/
व्योम i40e_dcb_hw_pfc_config(काष्ठा i40e_hw *hw,
			    u8 pfc_en, u8 *prio_tc)
अणु
	u16 refresh_समय = (u16)I40E_DEFAULT_PAUSE_TIME / 2;
	u32 link_speed = hw->phy.link_info.link_speed;
	u8 first_pfc_prio = 0;
	u8 num_pfc_tc = 0;
	u8 tc2pfc = 0;
	u32 reg;
	u8 i;

	/* Get Number of PFC TCs and TC2PFC map */
	क्रम (i = 0; i < I40E_MAX_USER_PRIORITY; i++) अणु
		अगर (pfc_en & BIT(i)) अणु
			अगर (!first_pfc_prio)
				first_pfc_prio = i;
			/* Set bit क्रम the PFC TC */
			tc2pfc |= BIT(prio_tc[i]);
			num_pfc_tc++;
		पूर्ण
	पूर्ण

	चयन (link_speed) अणु
	हाल I40E_LINK_SPEED_10GB:
		reg = rd32(hw, I40E_PRTDCB_MFLCN);
		reg |= BIT(I40E_PRTDCB_MFLCN_DPF_SHIFT) &
			I40E_PRTDCB_MFLCN_DPF_MASK;
		reg &= ~I40E_PRTDCB_MFLCN_RFCE_MASK;
		reg &= ~I40E_PRTDCB_MFLCN_RPFCE_MASK;
		अगर (pfc_en) अणु
			reg |= BIT(I40E_PRTDCB_MFLCN_RPFCM_SHIFT) &
				I40E_PRTDCB_MFLCN_RPFCM_MASK;
			reg |= ((u32)pfc_en << I40E_PRTDCB_MFLCN_RPFCE_SHIFT) &
				I40E_PRTDCB_MFLCN_RPFCE_MASK;
		पूर्ण
		wr32(hw, I40E_PRTDCB_MFLCN, reg);

		reg = rd32(hw, I40E_PRTDCB_FCCFG);
		reg &= ~I40E_PRTDCB_FCCFG_TFCE_MASK;
		अगर (pfc_en)
			reg |= (I40E_DCB_PFC_ENABLED <<
				I40E_PRTDCB_FCCFG_TFCE_SHIFT) &
				I40E_PRTDCB_FCCFG_TFCE_MASK;
		wr32(hw, I40E_PRTDCB_FCCFG, reg);

		/* FCTTV and FCRTV to be set by शेष */
		अवरोध;
	हाल I40E_LINK_SPEED_40GB:
		reg = rd32(hw, I40E_PRTMAC_HSEC_CTL_RX_ENABLE_GPP);
		reg &= ~I40E_PRTMAC_HSEC_CTL_RX_ENABLE_GPP_MASK;
		wr32(hw, I40E_PRTMAC_HSEC_CTL_RX_ENABLE_GPP, reg);

		reg = rd32(hw, I40E_PRTMAC_HSEC_CTL_RX_ENABLE_PPP);
		reg &= ~I40E_PRTMAC_HSEC_CTL_RX_ENABLE_GPP_MASK;
		reg |= BIT(I40E_PRTMAC_HSEC_CTL_RX_ENABLE_PPP_SHIFT) &
			I40E_PRTMAC_HSEC_CTL_RX_ENABLE_PPP_MASK;
		wr32(hw, I40E_PRTMAC_HSEC_CTL_RX_ENABLE_PPP, reg);

		reg = rd32(hw, I40E_PRTMAC_HSEC_CTL_RX_PAUSE_ENABLE);
		reg &= ~I40E_PRTMAC_HSEC_CTL_RX_PAUSE_ENABLE_MASK;
		reg |= ((u32)pfc_en <<
			   I40E_PRTMAC_HSEC_CTL_RX_PAUSE_ENABLE_SHIFT) &
			I40E_PRTMAC_HSEC_CTL_RX_PAUSE_ENABLE_MASK;
		wr32(hw, I40E_PRTMAC_HSEC_CTL_RX_PAUSE_ENABLE, reg);

		reg = rd32(hw, I40E_PRTMAC_HSEC_CTL_TX_PAUSE_ENABLE);
		reg &= ~I40E_PRTMAC_HSEC_CTL_TX_PAUSE_ENABLE_MASK;
		reg |= ((u32)pfc_en <<
			   I40E_PRTMAC_HSEC_CTL_TX_PAUSE_ENABLE_SHIFT) &
			I40E_PRTMAC_HSEC_CTL_TX_PAUSE_ENABLE_MASK;
		wr32(hw, I40E_PRTMAC_HSEC_CTL_TX_PAUSE_ENABLE, reg);

		क्रम (i = 0; i < I40E_PRTMAC_HSEC_CTL_TX_PAUSE_REFRESH_TIMER_MAX_INDEX; i++) अणु
			reg = rd32(hw, I40E_PRTMAC_HSEC_CTL_TX_PAUSE_REFRESH_TIMER(i));
			reg &= ~I40E_PRTMAC_HSEC_CTL_TX_PAUSE_REFRESH_TIMER_MASK;
			अगर (pfc_en) अणु
				reg |= ((u32)refresh_समय <<
					I40E_PRTMAC_HSEC_CTL_TX_PAUSE_REFRESH_TIMER_SHIFT) &
					I40E_PRTMAC_HSEC_CTL_TX_PAUSE_REFRESH_TIMER_MASK;
			पूर्ण
			wr32(hw, I40E_PRTMAC_HSEC_CTL_TX_PAUSE_REFRESH_TIMER(i), reg);
		पूर्ण
		/* PRTMAC_HSEC_CTL_TX_PAUSE_QUANTA शेष value is 0xFFFF
		 * क्रम all user priorities
		 */
		अवरोध;
	पूर्ण

	reg = rd32(hw, I40E_PRTDCB_TC2PFC);
	reg &= ~I40E_PRTDCB_TC2PFC_TC2PFC_MASK;
	reg |= ((u32)tc2pfc << I40E_PRTDCB_TC2PFC_TC2PFC_SHIFT) &
		I40E_PRTDCB_TC2PFC_TC2PFC_MASK;
	wr32(hw, I40E_PRTDCB_TC2PFC, reg);

	reg = rd32(hw, I40E_PRTDCB_RUP);
	reg &= ~I40E_PRTDCB_RUP_NOVLANUP_MASK;
	reg |= ((u32)first_pfc_prio << I40E_PRTDCB_RUP_NOVLANUP_SHIFT) &
		 I40E_PRTDCB_RUP_NOVLANUP_MASK;
	wr32(hw, I40E_PRTDCB_RUP, reg);

	reg = rd32(hw, I40E_PRTDCB_TDPMC);
	reg &= ~I40E_PRTDCB_TDPMC_TCPM_MODE_MASK;
	अगर (num_pfc_tc > I40E_DCB_PFC_FORCED_NUM_TC) अणु
		reg |= BIT(I40E_PRTDCB_TDPMC_TCPM_MODE_SHIFT) &
			I40E_PRTDCB_TDPMC_TCPM_MODE_MASK;
	पूर्ण
	wr32(hw, I40E_PRTDCB_TDPMC, reg);

	reg = rd32(hw, I40E_PRTDCB_TCPMC);
	reg &= ~I40E_PRTDCB_TCPMC_TCPM_MODE_MASK;
	अगर (num_pfc_tc > I40E_DCB_PFC_FORCED_NUM_TC) अणु
		reg |= BIT(I40E_PRTDCB_TCPMC_TCPM_MODE_SHIFT) &
			I40E_PRTDCB_TCPMC_TCPM_MODE_MASK;
	पूर्ण
	wr32(hw, I40E_PRTDCB_TCPMC, reg);
पूर्ण

/**
 * i40e_dcb_hw_set_num_tc
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @num_tc: number of traffic classes
 *
 * Configure number of traffic classes in HW
 **/
व्योम i40e_dcb_hw_set_num_tc(काष्ठा i40e_hw *hw, u8 num_tc)
अणु
	u32 reg = rd32(hw, I40E_PRTDCB_GENC);

	reg &= ~I40E_PRTDCB_GENC_NUMTC_MASK;
	reg |= ((u32)num_tc << I40E_PRTDCB_GENC_NUMTC_SHIFT) &
		I40E_PRTDCB_GENC_NUMTC_MASK;
	wr32(hw, I40E_PRTDCB_GENC, reg);
पूर्ण

/**
 * i40e_dcb_hw_get_num_tc
 * @hw: poपूर्णांकer to the hw काष्ठा
 *
 * Returns number of traffic classes configured in HW
 **/
u8 i40e_dcb_hw_get_num_tc(काष्ठा i40e_hw *hw)
अणु
	u32 reg = rd32(hw, I40E_PRTDCB_GENC);

	वापस (u8)((reg & I40E_PRTDCB_GENC_NUMTC_MASK) >>
		I40E_PRTDCB_GENC_NUMTC_SHIFT);
पूर्ण

/**
 * i40e_dcb_hw_rx_ets_bw_config
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @bw_share: Bandwidth share indexed per traffic class
 * @mode: Strict Priority or Round Robin mode between UP sharing same
 * traffic class
 * @prio_type: TC is ETS enabled or strict priority
 *
 * Configure HW Rx ETS bandwidth as part of DCB configuration.
 **/
व्योम i40e_dcb_hw_rx_ets_bw_config(काष्ठा i40e_hw *hw, u8 *bw_share,
				  u8 *mode, u8 *prio_type)
अणु
	u32 reg;
	u8 i;

	क्रम (i = 0; i <= I40E_PRTDCB_RETSTCC_MAX_INDEX; i++) अणु
		reg = rd32(hw, I40E_PRTDCB_RETSTCC(i));
		reg &= ~(I40E_PRTDCB_RETSTCC_BWSHARE_MASK     |
			 I40E_PRTDCB_RETSTCC_UPINTC_MODE_MASK |
			 I40E_PRTDCB_RETSTCC_ETSTC_SHIFT);
		reg |= ((u32)bw_share[i] << I40E_PRTDCB_RETSTCC_BWSHARE_SHIFT) &
			 I40E_PRTDCB_RETSTCC_BWSHARE_MASK;
		reg |= ((u32)mode[i] << I40E_PRTDCB_RETSTCC_UPINTC_MODE_SHIFT) &
			 I40E_PRTDCB_RETSTCC_UPINTC_MODE_MASK;
		reg |= ((u32)prio_type[i] << I40E_PRTDCB_RETSTCC_ETSTC_SHIFT) &
			 I40E_PRTDCB_RETSTCC_ETSTC_MASK;
		wr32(hw, I40E_PRTDCB_RETSTCC(i), reg);
	पूर्ण
पूर्ण

/**
 * i40e_dcb_hw_rx_up2tc_config
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @prio_tc: priority to tc assignment indexed by priority
 *
 * Configure HW Rx UP2TC map as part of DCB configuration.
 **/
व्योम i40e_dcb_hw_rx_up2tc_config(काष्ठा i40e_hw *hw, u8 *prio_tc)
अणु
	u32 reg = rd32(hw, I40E_PRTDCB_RUP2TC);
#घोषणा I40E_UP2TC_REG(val, i) \
		(((val) << I40E_PRTDCB_RUP2TC_UP##i##TC_SHIFT) & \
		  I40E_PRTDCB_RUP2TC_UP##i##TC_MASK)

	reg |= I40E_UP2TC_REG(prio_tc[0], 0);
	reg |= I40E_UP2TC_REG(prio_tc[1], 1);
	reg |= I40E_UP2TC_REG(prio_tc[2], 2);
	reg |= I40E_UP2TC_REG(prio_tc[3], 3);
	reg |= I40E_UP2TC_REG(prio_tc[4], 4);
	reg |= I40E_UP2TC_REG(prio_tc[5], 5);
	reg |= I40E_UP2TC_REG(prio_tc[6], 6);
	reg |= I40E_UP2TC_REG(prio_tc[7], 7);

	wr32(hw, I40E_PRTDCB_RUP2TC, reg);
पूर्ण

/**
 * i40e_dcb_hw_calculate_pool_sizes - configure dcb pool sizes
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @num_ports: Number of available ports on the device
 * @eee_enabled: EEE enabled क्रम the given port
 * @pfc_en: Bit map of PFC enabled traffic classes
 * @mfs_tc: Array of max frame size क्रम each traffic class
 * @pb_cfg: poपूर्णांकer to packet buffer configuration
 *
 * Calculate the shared and dedicated per TC pool sizes,
 * watermarks and threshold values.
 **/
व्योम i40e_dcb_hw_calculate_pool_sizes(काष्ठा i40e_hw *hw,
				      u8 num_ports, bool eee_enabled,
				      u8 pfc_en, u32 *mfs_tc,
				      काष्ठा i40e_rx_pb_config *pb_cfg)
अणु
	u32 pool_size[I40E_MAX_TRAFFIC_CLASS];
	u32 high_wm[I40E_MAX_TRAFFIC_CLASS];
	u32 low_wm[I40E_MAX_TRAFFIC_CLASS];
	u32 total_pool_size = 0;
	पूर्णांक shared_pool_size; /* Need चिन्हित variable */
	u32 port_pb_size;
	u32 mfs_max = 0;
	u32 pcirtt;
	u8 i;

	/* Get the MFS(max) क्रम the port */
	क्रम (i = 0; i < I40E_MAX_TRAFFIC_CLASS; i++) अणु
		अगर (mfs_tc[i] > mfs_max)
			mfs_max = mfs_tc[i];
	पूर्ण

	pcirtt = I40E_BT2B(I40E_PCIRTT_LINK_SPEED_10G);

	/* Calculate effective Rx PB size per port */
	port_pb_size = I40E_DEVICE_RPB_SIZE / num_ports;
	अगर (eee_enabled)
		port_pb_size -= I40E_BT2B(I40E_EEE_TX_LPI_EXIT_TIME);
	port_pb_size -= mfs_max;

	/* Step 1 Calculating tc pool/shared pool sizes and watermarks */
	क्रम (i = 0; i < I40E_MAX_TRAFFIC_CLASS; i++) अणु
		अगर (pfc_en & BIT(i)) अणु
			low_wm[i] = (I40E_DCB_WATERMARK_START_FACTOR *
				     mfs_tc[i]) + pcirtt;
			high_wm[i] = low_wm[i];
			high_wm[i] += ((mfs_max > I40E_MAX_FRAME_SIZE)
					? mfs_max : I40E_MAX_FRAME_SIZE);
			pool_size[i] = high_wm[i];
			pool_size[i] += I40E_BT2B(I40E_STD_DV_TC(mfs_max,
								mfs_tc[i]));
		पूर्ण अन्यथा अणु
			low_wm[i] = 0;
			pool_size[i] = (I40E_DCB_WATERMARK_START_FACTOR *
					mfs_tc[i]) + pcirtt;
			high_wm[i] = pool_size[i];
		पूर्ण
		total_pool_size += pool_size[i];
	पूर्ण

	shared_pool_size = port_pb_size - total_pool_size;
	अगर (shared_pool_size > 0) अणु
		pb_cfg->shared_pool_size = shared_pool_size;
		pb_cfg->shared_pool_high_wm = shared_pool_size;
		pb_cfg->shared_pool_low_wm = 0;
		क्रम (i = 0; i < I40E_MAX_TRAFFIC_CLASS; i++) अणु
			pb_cfg->shared_pool_low_thresh[i] = 0;
			pb_cfg->shared_pool_high_thresh[i] = shared_pool_size;
			pb_cfg->tc_pool_size[i] = pool_size[i];
			pb_cfg->tc_pool_high_wm[i] = high_wm[i];
			pb_cfg->tc_pool_low_wm[i] = low_wm[i];
		पूर्ण

	पूर्ण अन्यथा अणु
		i40e_debug(hw, I40E_DEBUG_DCB,
			   "The shared pool size for the port is negative %d.\n",
			   shared_pool_size);
	पूर्ण
पूर्ण

/**
 * i40e_dcb_hw_rx_pb_config
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @old_pb_cfg: Existing Rx Packet buffer configuration
 * @new_pb_cfg: New Rx Packet buffer configuration
 *
 * Program the Rx Packet Buffer रेजिस्टरs.
 **/
व्योम i40e_dcb_hw_rx_pb_config(काष्ठा i40e_hw *hw,
			      काष्ठा i40e_rx_pb_config *old_pb_cfg,
			      काष्ठा i40e_rx_pb_config *new_pb_cfg)
अणु
	u32 old_val;
	u32 new_val;
	u32 reg;
	u8 i;

	/* The Rx Packet buffer रेजिस्टर programming needs to be करोne in a
	 * certain order and the following code is based on that
	 * requirement.
	 */

	/* Program the shared pool low water mark per port अगर decreasing */
	old_val = old_pb_cfg->shared_pool_low_wm;
	new_val = new_pb_cfg->shared_pool_low_wm;
	अगर (new_val < old_val) अणु
		reg = rd32(hw, I40E_PRTRPB_SLW);
		reg &= ~I40E_PRTRPB_SLW_SLW_MASK;
		reg |= (new_val << I40E_PRTRPB_SLW_SLW_SHIFT) &
			I40E_PRTRPB_SLW_SLW_MASK;
		wr32(hw, I40E_PRTRPB_SLW, reg);
	पूर्ण

	/* Program the shared pool low threshold and tc pool
	 * low water mark per TC that are decreasing.
	 */
	क्रम (i = 0; i < I40E_MAX_TRAFFIC_CLASS; i++) अणु
		old_val = old_pb_cfg->shared_pool_low_thresh[i];
		new_val = new_pb_cfg->shared_pool_low_thresh[i];
		अगर (new_val < old_val) अणु
			reg = rd32(hw, I40E_PRTRPB_SLT(i));
			reg &= ~I40E_PRTRPB_SLT_SLT_TCN_MASK;
			reg |= (new_val << I40E_PRTRPB_SLT_SLT_TCN_SHIFT) &
				I40E_PRTRPB_SLT_SLT_TCN_MASK;
			wr32(hw, I40E_PRTRPB_SLT(i), reg);
		पूर्ण

		old_val = old_pb_cfg->tc_pool_low_wm[i];
		new_val = new_pb_cfg->tc_pool_low_wm[i];
		अगर (new_val < old_val) अणु
			reg = rd32(hw, I40E_PRTRPB_DLW(i));
			reg &= ~I40E_PRTRPB_DLW_DLW_TCN_MASK;
			reg |= (new_val << I40E_PRTRPB_DLW_DLW_TCN_SHIFT) &
				I40E_PRTRPB_DLW_DLW_TCN_MASK;
			wr32(hw, I40E_PRTRPB_DLW(i), reg);
		पूर्ण
	पूर्ण

	/* Program the shared pool high water mark per port अगर decreasing */
	old_val = old_pb_cfg->shared_pool_high_wm;
	new_val = new_pb_cfg->shared_pool_high_wm;
	अगर (new_val < old_val) अणु
		reg = rd32(hw, I40E_PRTRPB_SHW);
		reg &= ~I40E_PRTRPB_SHW_SHW_MASK;
		reg |= (new_val << I40E_PRTRPB_SHW_SHW_SHIFT) &
			I40E_PRTRPB_SHW_SHW_MASK;
		wr32(hw, I40E_PRTRPB_SHW, reg);
	पूर्ण

	/* Program the shared pool high threshold and tc pool
	 * high water mark per TC that are decreasing.
	 */
	क्रम (i = 0; i < I40E_MAX_TRAFFIC_CLASS; i++) अणु
		old_val = old_pb_cfg->shared_pool_high_thresh[i];
		new_val = new_pb_cfg->shared_pool_high_thresh[i];
		अगर (new_val < old_val) अणु
			reg = rd32(hw, I40E_PRTRPB_SHT(i));
			reg &= ~I40E_PRTRPB_SHT_SHT_TCN_MASK;
			reg |= (new_val << I40E_PRTRPB_SHT_SHT_TCN_SHIFT) &
				I40E_PRTRPB_SHT_SHT_TCN_MASK;
			wr32(hw, I40E_PRTRPB_SHT(i), reg);
		पूर्ण

		old_val = old_pb_cfg->tc_pool_high_wm[i];
		new_val = new_pb_cfg->tc_pool_high_wm[i];
		अगर (new_val < old_val) अणु
			reg = rd32(hw, I40E_PRTRPB_DHW(i));
			reg &= ~I40E_PRTRPB_DHW_DHW_TCN_MASK;
			reg |= (new_val << I40E_PRTRPB_DHW_DHW_TCN_SHIFT) &
				I40E_PRTRPB_DHW_DHW_TCN_MASK;
			wr32(hw, I40E_PRTRPB_DHW(i), reg);
		पूर्ण
	पूर्ण

	/* Write Dedicated Pool Sizes per TC */
	क्रम (i = 0; i < I40E_MAX_TRAFFIC_CLASS; i++) अणु
		new_val = new_pb_cfg->tc_pool_size[i];
		reg = rd32(hw, I40E_PRTRPB_DPS(i));
		reg &= ~I40E_PRTRPB_DPS_DPS_TCN_MASK;
		reg |= (new_val << I40E_PRTRPB_DPS_DPS_TCN_SHIFT) &
			I40E_PRTRPB_DPS_DPS_TCN_MASK;
		wr32(hw, I40E_PRTRPB_DPS(i), reg);
	पूर्ण

	/* Write Shared Pool Size per port */
	new_val = new_pb_cfg->shared_pool_size;
	reg = rd32(hw, I40E_PRTRPB_SPS);
	reg &= ~I40E_PRTRPB_SPS_SPS_MASK;
	reg |= (new_val << I40E_PRTRPB_SPS_SPS_SHIFT) &
		I40E_PRTRPB_SPS_SPS_MASK;
	wr32(hw, I40E_PRTRPB_SPS, reg);

	/* Program the shared pool low water mark per port अगर increasing */
	old_val = old_pb_cfg->shared_pool_low_wm;
	new_val = new_pb_cfg->shared_pool_low_wm;
	अगर (new_val > old_val) अणु
		reg = rd32(hw, I40E_PRTRPB_SLW);
		reg &= ~I40E_PRTRPB_SLW_SLW_MASK;
		reg |= (new_val << I40E_PRTRPB_SLW_SLW_SHIFT) &
			I40E_PRTRPB_SLW_SLW_MASK;
		wr32(hw, I40E_PRTRPB_SLW, reg);
	पूर्ण

	/* Program the shared pool low threshold and tc pool
	 * low water mark per TC that are increasing.
	 */
	क्रम (i = 0; i < I40E_MAX_TRAFFIC_CLASS; i++) अणु
		old_val = old_pb_cfg->shared_pool_low_thresh[i];
		new_val = new_pb_cfg->shared_pool_low_thresh[i];
		अगर (new_val > old_val) अणु
			reg = rd32(hw, I40E_PRTRPB_SLT(i));
			reg &= ~I40E_PRTRPB_SLT_SLT_TCN_MASK;
			reg |= (new_val << I40E_PRTRPB_SLT_SLT_TCN_SHIFT) &
				I40E_PRTRPB_SLT_SLT_TCN_MASK;
			wr32(hw, I40E_PRTRPB_SLT(i), reg);
		पूर्ण

		old_val = old_pb_cfg->tc_pool_low_wm[i];
		new_val = new_pb_cfg->tc_pool_low_wm[i];
		अगर (new_val > old_val) अणु
			reg = rd32(hw, I40E_PRTRPB_DLW(i));
			reg &= ~I40E_PRTRPB_DLW_DLW_TCN_MASK;
			reg |= (new_val << I40E_PRTRPB_DLW_DLW_TCN_SHIFT) &
				I40E_PRTRPB_DLW_DLW_TCN_MASK;
			wr32(hw, I40E_PRTRPB_DLW(i), reg);
		पूर्ण
	पूर्ण

	/* Program the shared pool high water mark per port अगर increasing */
	old_val = old_pb_cfg->shared_pool_high_wm;
	new_val = new_pb_cfg->shared_pool_high_wm;
	अगर (new_val > old_val) अणु
		reg = rd32(hw, I40E_PRTRPB_SHW);
		reg &= ~I40E_PRTRPB_SHW_SHW_MASK;
		reg |= (new_val << I40E_PRTRPB_SHW_SHW_SHIFT) &
			I40E_PRTRPB_SHW_SHW_MASK;
		wr32(hw, I40E_PRTRPB_SHW, reg);
	पूर्ण

	/* Program the shared pool high threshold and tc pool
	 * high water mark per TC that are increasing.
	 */
	क्रम (i = 0; i < I40E_MAX_TRAFFIC_CLASS; i++) अणु
		old_val = old_pb_cfg->shared_pool_high_thresh[i];
		new_val = new_pb_cfg->shared_pool_high_thresh[i];
		अगर (new_val > old_val) अणु
			reg = rd32(hw, I40E_PRTRPB_SHT(i));
			reg &= ~I40E_PRTRPB_SHT_SHT_TCN_MASK;
			reg |= (new_val << I40E_PRTRPB_SHT_SHT_TCN_SHIFT) &
				I40E_PRTRPB_SHT_SHT_TCN_MASK;
			wr32(hw, I40E_PRTRPB_SHT(i), reg);
		पूर्ण

		old_val = old_pb_cfg->tc_pool_high_wm[i];
		new_val = new_pb_cfg->tc_pool_high_wm[i];
		अगर (new_val > old_val) अणु
			reg = rd32(hw, I40E_PRTRPB_DHW(i));
			reg &= ~I40E_PRTRPB_DHW_DHW_TCN_MASK;
			reg |= (new_val << I40E_PRTRPB_DHW_DHW_TCN_SHIFT) &
				I40E_PRTRPB_DHW_DHW_TCN_MASK;
			wr32(hw, I40E_PRTRPB_DHW(i), reg);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * _i40e_पढ़ो_lldp_cfg - generic पढ़ो of LLDP Configuration data from NVM
 * @hw: poपूर्णांकer to the HW काष्ठाure
 * @lldp_cfg: poपूर्णांकer to hold lldp configuration variables
 * @module: address of the module poपूर्णांकer
 * @word_offset: offset of LLDP configuration
 *
 * Reads the LLDP configuration data from NVM using passed addresses
 **/
अटल i40e_status _i40e_पढ़ो_lldp_cfg(काष्ठा i40e_hw *hw,
				       काष्ठा i40e_lldp_variables *lldp_cfg,
				       u8 module, u32 word_offset)
अणु
	u32 address, offset = (2 * word_offset);
	i40e_status ret;
	__le16 raw_mem;
	u16 mem;

	ret = i40e_acquire_nvm(hw, I40E_RESOURCE_READ);
	अगर (ret)
		वापस ret;

	ret = i40e_aq_पढ़ो_nvm(hw, 0x0, module * 2, माप(raw_mem), &raw_mem,
			       true, शून्य);
	i40e_release_nvm(hw);
	अगर (ret)
		वापस ret;

	mem = le16_to_cpu(raw_mem);
	/* Check अगर this poपूर्णांकer needs to be पढ़ो in word size or 4K sector
	 * units.
	 */
	अगर (mem & I40E_PTR_TYPE)
		address = (0x7FFF & mem) * 4096;
	अन्यथा
		address = (0x7FFF & mem) * 2;

	ret = i40e_acquire_nvm(hw, I40E_RESOURCE_READ);
	अगर (ret)
		जाओ err_lldp_cfg;

	ret = i40e_aq_पढ़ो_nvm(hw, module, offset, माप(raw_mem), &raw_mem,
			       true, शून्य);
	i40e_release_nvm(hw);
	अगर (ret)
		वापस ret;

	mem = le16_to_cpu(raw_mem);
	offset = mem + word_offset;
	offset *= 2;

	ret = i40e_acquire_nvm(hw, I40E_RESOURCE_READ);
	अगर (ret)
		जाओ err_lldp_cfg;

	ret = i40e_aq_पढ़ो_nvm(hw, 0, address + offset,
			       माप(काष्ठा i40e_lldp_variables), lldp_cfg,
			       true, शून्य);
	i40e_release_nvm(hw);

err_lldp_cfg:
	वापस ret;
पूर्ण

/**
 * i40e_पढ़ो_lldp_cfg - पढ़ो LLDP Configuration data from NVM
 * @hw: poपूर्णांकer to the HW काष्ठाure
 * @lldp_cfg: poपूर्णांकer to hold lldp configuration variables
 *
 * Reads the LLDP configuration data from NVM
 **/
i40e_status i40e_पढ़ो_lldp_cfg(काष्ठा i40e_hw *hw,
			       काष्ठा i40e_lldp_variables *lldp_cfg)
अणु
	i40e_status ret = 0;
	u32 mem;

	अगर (!lldp_cfg)
		वापस I40E_ERR_PARAM;

	ret = i40e_acquire_nvm(hw, I40E_RESOURCE_READ);
	अगर (ret)
		वापस ret;

	ret = i40e_aq_पढ़ो_nvm(hw, I40E_SR_NVM_CONTROL_WORD, 0, माप(mem),
			       &mem, true, शून्य);
	i40e_release_nvm(hw);
	अगर (ret)
		वापस ret;

	/* Read a bit that holds inक्रमmation whether we are running flat or
	 * काष्ठाured NVM image. Flat image has LLDP configuration in shaकरोw
	 * ram, so there is a need to pass dअगरferent addresses क्रम both हालs.
	 */
	अगर (mem & I40E_SR_NVM_MAP_STRUCTURE_TYPE) अणु
		/* Flat NVM हाल */
		ret = _i40e_पढ़ो_lldp_cfg(hw, lldp_cfg, I40E_SR_EMP_MODULE_PTR,
					  I40E_SR_LLDP_CFG_PTR);
	पूर्ण अन्यथा अणु
		/* Good old काष्ठाured NVM image */
		ret = _i40e_पढ़ो_lldp_cfg(hw, lldp_cfg, I40E_EMP_MODULE_PTR,
					  I40E_NVM_LLDP_CFG_PTR);
	पूर्ण

	वापस ret;
पूर्ण
