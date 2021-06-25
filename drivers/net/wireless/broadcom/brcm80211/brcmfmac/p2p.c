<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2012 Broadcom Corporation
 */
#समावेश <linux/slab.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/rtnetlink.h>
#समावेश <net/cfg80211.h>

#समावेश <brcmu_wअगरi.h>
#समावेश <brcmu_utils.h>
#समावेश <defs.h>
#समावेश "core.h"
#समावेश "debug.h"
#समावेश "fwil.h"
#समावेश "fwil_types.h"
#समावेश "p2p.h"
#समावेश "cfg80211.h"
#समावेश "feature.h"

/* parameters used क्रम p2p escan */
#घोषणा P2PAPI_SCAN_NPROBES 1
#घोषणा P2PAPI_SCAN_DWELL_TIME_MS 80
#घोषणा P2PAPI_SCAN_SOCIAL_DWELL_TIME_MS 40
#घोषणा P2PAPI_SCAN_HOME_TIME_MS 60
#घोषणा P2PAPI_SCAN_NPROBS_TIME_MS 30
#घोषणा P2PAPI_SCAN_AF_SEARCH_DWELL_TIME_MS 100
#घोषणा WL_SCAN_CONNECT_DWELL_TIME_MS 200
#घोषणा WL_SCAN_JOIN_PROBE_INTERVAL_MS 20

#घोषणा BRCMF_P2P_WILDCARD_SSID		"DIRECT-"
#घोषणा BRCMF_P2P_WILDCARD_SSID_LEN	(माप(BRCMF_P2P_WILDCARD_SSID) - 1)

#घोषणा SOCIAL_CHAN_1		1
#घोषणा SOCIAL_CHAN_2		6
#घोषणा SOCIAL_CHAN_3		11
#घोषणा IS_P2P_SOCIAL_CHANNEL(channel) ((channel == SOCIAL_CHAN_1) || \
					 (channel == SOCIAL_CHAN_2) || \
					 (channel == SOCIAL_CHAN_3))
#घोषणा BRCMF_P2P_TEMP_CHAN	SOCIAL_CHAN_3
#घोषणा SOCIAL_CHAN_CNT		3
#घोषणा AF_PEER_SEARCH_CNT	2

#घोषणा BRCMF_SCB_TIMEOUT_VALUE	20

#घोषणा P2P_VER			9	/* P2P version: 9=WiFi P2P v1.0 */
#घोषणा P2P_PUB_AF_CATEGORY	0x04
#घोषणा P2P_PUB_AF_ACTION	0x09
#घोषणा P2P_AF_CATEGORY		0x7f
#घोषणा P2P_OUI			"\x50\x6F\x9A"	/* P2P OUI */
#घोषणा P2P_OUI_LEN		3		/* P2P OUI length */

/* Action Frame Constants */
#घोषणा DOT11_ACTION_HDR_LEN	2	/* action frame category + action */
#घोषणा DOT11_ACTION_CAT_OFF	0	/* category offset */
#घोषणा DOT11_ACTION_ACT_OFF	1	/* action offset */

#घोषणा P2P_AF_DWELL_TIME		200
#घोषणा P2P_AF_MIN_DWELL_TIME		100
#घोषणा P2P_AF_MED_DWELL_TIME		400
#घोषणा P2P_AF_LONG_DWELL_TIME		1000
#घोषणा P2P_AF_TX_MAX_RETRY		5
#घोषणा P2P_AF_MAX_WAIT_TIME		msecs_to_jअगरfies(2000)
#घोषणा P2P_INVALID_CHANNEL		-1
#घोषणा P2P_CHANNEL_SYNC_RETRY		5
#घोषणा P2P_AF_FRM_SCAN_MAX_WAIT	msecs_to_jअगरfies(450)
#घोषणा P2P_DEFAULT_SLEEP_TIME_VSDB	200
#घोषणा P2P_AF_RETRY_DELAY_TIME		40

/* WiFi P2P Public Action Frame OUI Subtypes */
#घोषणा P2P_PAF_GON_REQ		0	/* Group Owner Negotiation Req */
#घोषणा P2P_PAF_GON_RSP		1	/* Group Owner Negotiation Rsp */
#घोषणा P2P_PAF_GON_CONF	2	/* Group Owner Negotiation Confirm */
#घोषणा P2P_PAF_INVITE_REQ	3	/* P2P Invitation Request */
#घोषणा P2P_PAF_INVITE_RSP	4	/* P2P Invitation Response */
#घोषणा P2P_PAF_DEVDIS_REQ	5	/* Device Discoverability Request */
#घोषणा P2P_PAF_DEVDIS_RSP	6	/* Device Discoverability Response */
#घोषणा P2P_PAF_PROVDIS_REQ	7	/* Provision Discovery Request */
#घोषणा P2P_PAF_PROVDIS_RSP	8	/* Provision Discovery Response */
#घोषणा P2P_PAF_SUBTYPE_INVALID	255	/* Invalid Subtype */

/* WiFi P2P Action Frame OUI Subtypes */
#घोषणा P2P_AF_NOTICE_OF_ABSENCE	0	/* Notice of Absence */
#घोषणा P2P_AF_PRESENCE_REQ		1	/* P2P Presence Request */
#घोषणा P2P_AF_PRESENCE_RSP		2	/* P2P Presence Response */
#घोषणा P2P_AF_GO_DISC_REQ		3	/* GO Discoverability Request */

/* P2P Service Discovery related */
#घोषणा P2PSD_ACTION_CATEGORY		0x04	/* Public action frame */
#घोषणा P2PSD_ACTION_ID_GAS_IREQ	0x0a	/* GAS Initial Request AF */
#घोषणा P2PSD_ACTION_ID_GAS_IRESP	0x0b	/* GAS Initial Response AF */
#घोषणा P2PSD_ACTION_ID_GAS_CREQ	0x0c	/* GAS Comback Request AF */
#घोषणा P2PSD_ACTION_ID_GAS_CRESP	0x0d	/* GAS Comback Response AF */

#घोषणा BRCMF_P2P_DISABLE_TIMEOUT	msecs_to_jअगरfies(500)

/* Mask क्रम retry counter of custom dwell समय */
#घोषणा CUSTOM_RETRY_MASK 0xff000000
/**
 * काष्ठा brcmf_p2p_disc_st_le - set discovery state in firmware.
 *
 * @state: requested discovery state (see क्रमागत brcmf_p2p_disc_state).
 * @chspec: channel parameter क्रम %WL_P2P_DISC_ST_LISTEN state.
 * @dwell: dwell समय in ms क्रम %WL_P2P_DISC_ST_LISTEN state.
 */
काष्ठा brcmf_p2p_disc_st_le अणु
	u8 state;
	__le16 chspec;
	__le16 dwell;
पूर्ण;

/**
 * क्रमागत brcmf_p2p_disc_state - P2P discovery state values
 *
 * @WL_P2P_DISC_ST_SCAN: P2P discovery with wildcard SSID and P2P IE.
 * @WL_P2P_DISC_ST_LISTEN: P2P discovery off-channel क्रम specअगरied समय.
 * @WL_P2P_DISC_ST_SEARCH: P2P discovery with P2P wildcard SSID and P2P IE.
 */
क्रमागत brcmf_p2p_disc_state अणु
	WL_P2P_DISC_ST_SCAN,
	WL_P2P_DISC_ST_LISTEN,
	WL_P2P_DISC_ST_SEARCH
पूर्ण;

/**
 * काष्ठा brcmf_p2p_scan_le - P2P specअगरic scan request.
 *
 * @type: type of scan method requested (values: 'E' or 'S').
 * @reserved: reserved (ignored).
 * @eparams: parameters used क्रम type 'E'.
 * @sparams: parameters used क्रम type 'S'.
 */
काष्ठा brcmf_p2p_scan_le अणु
	u8 type;
	u8 reserved[3];
	जोड़ अणु
		काष्ठा brcmf_escan_params_le eparams;
		काष्ठा brcmf_scan_params_le sparams;
	पूर्ण;
पूर्ण;

/**
 * काष्ठा brcmf_p2p_pub_act_frame - WiFi P2P Public Action Frame
 *
 * @category: P2P_PUB_AF_CATEGORY
 * @action: P2P_PUB_AF_ACTION
 * @oui: P2P_OUI
 * @oui_type: OUI type - P2P_VER
 * @subtype: OUI subtype - P2P_TYPE_*
 * @dialog_token: nonzero, identअगरies req/rsp transaction
 * @elts: Variable length inक्रमmation elements.
 */
काष्ठा brcmf_p2p_pub_act_frame अणु
	u8	category;
	u8	action;
	u8	oui[3];
	u8	oui_type;
	u8	subtype;
	u8	dialog_token;
	u8	elts[1];
पूर्ण;

/**
 * काष्ठा brcmf_p2p_action_frame - WiFi P2P Action Frame
 *
 * @category: P2P_AF_CATEGORY
 * @oui: OUI - P2P_OUI
 * @type: OUI Type - P2P_VER
 * @subtype: OUI Subtype - P2P_AF_*
 * @dialog_token: nonzero, identअगरies req/resp tranaction
 * @elts: Variable length inक्रमmation elements.
 */
काष्ठा brcmf_p2p_action_frame अणु
	u8	category;
	u8	oui[3];
	u8	type;
	u8	subtype;
	u8	dialog_token;
	u8	elts[1];
पूर्ण;

/**
 * काष्ठा brcmf_p2psd_gas_pub_act_frame - Wi-Fi GAS Public Action Frame
 *
 * @category: 0x04 Public Action Frame
 * @action: 0x6c Advertisement Protocol
 * @dialog_token: nonzero, identअगरies req/rsp transaction
 * @query_data: Query Data. SD gas ireq SD gas iresp
 */
काष्ठा brcmf_p2psd_gas_pub_act_frame अणु
	u8	category;
	u8	action;
	u8	dialog_token;
	u8	query_data[1];
पूर्ण;

/**
 * काष्ठा brcmf_config_af_params - Action Frame Parameters क्रम tx.
 *
 * @mpc_onoff: To make sure to send successfully action frame, we have to
 *             turn off mpc  0: off, 1: on,  (-1): करो nothing
 * @search_channel: 1: search peer's channel to send af
 * @extra_listen: keep the dwell समय to get af response frame.
 */
काष्ठा brcmf_config_af_params अणु
	s32 mpc_onoff;
	bool search_channel;
	bool extra_listen;
पूर्ण;

/**
 * brcmf_p2p_is_pub_action() - true अगर p2p खुला type frame.
 *
 * @frame: action frame data.
 * @frame_len: length of action frame data.
 *
 * Determine अगर action frame is p2p खुला action type
 */
अटल bool brcmf_p2p_is_pub_action(व्योम *frame, u32 frame_len)
अणु
	काष्ठा brcmf_p2p_pub_act_frame *pact_frm;

	अगर (frame == शून्य)
		वापस false;

	pact_frm = (काष्ठा brcmf_p2p_pub_act_frame *)frame;
	अगर (frame_len < माप(काष्ठा brcmf_p2p_pub_act_frame) - 1)
		वापस false;

	अगर (pact_frm->category == P2P_PUB_AF_CATEGORY &&
	    pact_frm->action == P2P_PUB_AF_ACTION &&
	    pact_frm->oui_type == P2P_VER &&
	    स_भेद(pact_frm->oui, P2P_OUI, P2P_OUI_LEN) == 0)
		वापस true;

	वापस false;
पूर्ण

/**
 * brcmf_p2p_is_p2p_action() - true अगर p2p action type frame.
 *
 * @frame: action frame data.
 * @frame_len: length of action frame data.
 *
 * Determine अगर action frame is p2p action type
 */
अटल bool brcmf_p2p_is_p2p_action(व्योम *frame, u32 frame_len)
अणु
	काष्ठा brcmf_p2p_action_frame *act_frm;

	अगर (frame == शून्य)
		वापस false;

	act_frm = (काष्ठा brcmf_p2p_action_frame *)frame;
	अगर (frame_len < माप(काष्ठा brcmf_p2p_action_frame) - 1)
		वापस false;

	अगर (act_frm->category == P2P_AF_CATEGORY &&
	    act_frm->type  == P2P_VER &&
	    स_भेद(act_frm->oui, P2P_OUI, P2P_OUI_LEN) == 0)
		वापस true;

	वापस false;
पूर्ण

/**
 * brcmf_p2p_is_gas_action() - true अगर p2p gas action type frame.
 *
 * @frame: action frame data.
 * @frame_len: length of action frame data.
 *
 * Determine अगर action frame is p2p gas action type
 */
अटल bool brcmf_p2p_is_gas_action(व्योम *frame, u32 frame_len)
अणु
	काष्ठा brcmf_p2psd_gas_pub_act_frame *sd_act_frm;

	अगर (frame == शून्य)
		वापस false;

	sd_act_frm = (काष्ठा brcmf_p2psd_gas_pub_act_frame *)frame;
	अगर (frame_len < माप(काष्ठा brcmf_p2psd_gas_pub_act_frame) - 1)
		वापस false;

	अगर (sd_act_frm->category != P2PSD_ACTION_CATEGORY)
		वापस false;

	अगर (sd_act_frm->action == P2PSD_ACTION_ID_GAS_IREQ ||
	    sd_act_frm->action == P2PSD_ACTION_ID_GAS_IRESP ||
	    sd_act_frm->action == P2PSD_ACTION_ID_GAS_CREQ ||
	    sd_act_frm->action == P2PSD_ACTION_ID_GAS_CRESP)
		वापस true;

	वापस false;
पूर्ण

/**
 * brcmf_p2p_prपूर्णांक_actframe() - debug prपूर्णांक routine.
 *
 * @tx: Received or to be transmitted
 * @frame: action frame data.
 * @frame_len: length of action frame data.
 *
 * Prपूर्णांक inक्रमmation about the p2p action frame
 */

#अगर_घोषित DEBUG

अटल व्योम brcmf_p2p_prपूर्णांक_actframe(bool tx, व्योम *frame, u32 frame_len)
अणु
	काष्ठा brcmf_p2p_pub_act_frame *pact_frm;
	काष्ठा brcmf_p2p_action_frame *act_frm;
	काष्ठा brcmf_p2psd_gas_pub_act_frame *sd_act_frm;

	अगर (!frame || frame_len <= 2)
		वापस;

	अगर (brcmf_p2p_is_pub_action(frame, frame_len)) अणु
		pact_frm = (काष्ठा brcmf_p2p_pub_act_frame *)frame;
		चयन (pact_frm->subtype) अणु
		हाल P2P_PAF_GON_REQ:
			brcmf_dbg(TRACE, "%s P2P Group Owner Negotiation Req Frame\n",
				  (tx) ? "TX" : "RX");
			अवरोध;
		हाल P2P_PAF_GON_RSP:
			brcmf_dbg(TRACE, "%s P2P Group Owner Negotiation Rsp Frame\n",
				  (tx) ? "TX" : "RX");
			अवरोध;
		हाल P2P_PAF_GON_CONF:
			brcmf_dbg(TRACE, "%s P2P Group Owner Negotiation Confirm Frame\n",
				  (tx) ? "TX" : "RX");
			अवरोध;
		हाल P2P_PAF_INVITE_REQ:
			brcmf_dbg(TRACE, "%s P2P Invitation Request  Frame\n",
				  (tx) ? "TX" : "RX");
			अवरोध;
		हाल P2P_PAF_INVITE_RSP:
			brcmf_dbg(TRACE, "%s P2P Invitation Response Frame\n",
				  (tx) ? "TX" : "RX");
			अवरोध;
		हाल P2P_PAF_DEVDIS_REQ:
			brcmf_dbg(TRACE, "%s P2P Device Discoverability Request Frame\n",
				  (tx) ? "TX" : "RX");
			अवरोध;
		हाल P2P_PAF_DEVDIS_RSP:
			brcmf_dbg(TRACE, "%s P2P Device Discoverability Response Frame\n",
				  (tx) ? "TX" : "RX");
			अवरोध;
		हाल P2P_PAF_PROVDIS_REQ:
			brcmf_dbg(TRACE, "%s P2P Provision Discovery Request Frame\n",
				  (tx) ? "TX" : "RX");
			अवरोध;
		हाल P2P_PAF_PROVDIS_RSP:
			brcmf_dbg(TRACE, "%s P2P Provision Discovery Response Frame\n",
				  (tx) ? "TX" : "RX");
			अवरोध;
		शेष:
			brcmf_dbg(TRACE, "%s Unknown P2P Public Action Frame\n",
				  (tx) ? "TX" : "RX");
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (brcmf_p2p_is_p2p_action(frame, frame_len)) अणु
		act_frm = (काष्ठा brcmf_p2p_action_frame *)frame;
		चयन (act_frm->subtype) अणु
		हाल P2P_AF_NOTICE_OF_ABSENCE:
			brcmf_dbg(TRACE, "%s P2P Notice of Absence Frame\n",
				  (tx) ? "TX" : "RX");
			अवरोध;
		हाल P2P_AF_PRESENCE_REQ:
			brcmf_dbg(TRACE, "%s P2P Presence Request Frame\n",
				  (tx) ? "TX" : "RX");
			अवरोध;
		हाल P2P_AF_PRESENCE_RSP:
			brcmf_dbg(TRACE, "%s P2P Presence Response Frame\n",
				  (tx) ? "TX" : "RX");
			अवरोध;
		हाल P2P_AF_GO_DISC_REQ:
			brcmf_dbg(TRACE, "%s P2P Discoverability Request Frame\n",
				  (tx) ? "TX" : "RX");
			अवरोध;
		शेष:
			brcmf_dbg(TRACE, "%s Unknown P2P Action Frame\n",
				  (tx) ? "TX" : "RX");
		पूर्ण

	पूर्ण अन्यथा अगर (brcmf_p2p_is_gas_action(frame, frame_len)) अणु
		sd_act_frm = (काष्ठा brcmf_p2psd_gas_pub_act_frame *)frame;
		चयन (sd_act_frm->action) अणु
		हाल P2PSD_ACTION_ID_GAS_IREQ:
			brcmf_dbg(TRACE, "%s P2P GAS Initial Request\n",
				  (tx) ? "TX" : "RX");
			अवरोध;
		हाल P2PSD_ACTION_ID_GAS_IRESP:
			brcmf_dbg(TRACE, "%s P2P GAS Initial Response\n",
				  (tx) ? "TX" : "RX");
			अवरोध;
		हाल P2PSD_ACTION_ID_GAS_CREQ:
			brcmf_dbg(TRACE, "%s P2P GAS Comback Request\n",
				  (tx) ? "TX" : "RX");
			अवरोध;
		हाल P2PSD_ACTION_ID_GAS_CRESP:
			brcmf_dbg(TRACE, "%s P2P GAS Comback Response\n",
				  (tx) ? "TX" : "RX");
			अवरोध;
		शेष:
			brcmf_dbg(TRACE, "%s Unknown P2P GAS Frame\n",
				  (tx) ? "TX" : "RX");
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

#अन्यथा

अटल व्योम brcmf_p2p_prपूर्णांक_actframe(bool tx, व्योम *frame, u32 frame_len)
अणु
पूर्ण

#पूर्ण_अगर


/**
 * brcmf_p2p_set_firmware() - prepare firmware क्रम peer-to-peer operation.
 *
 * @अगरp: अगरp to use क्रम iovars (primary).
 * @p2p_mac: mac address to configure क्रम p2p_da_override
 */
अटल पूर्णांक brcmf_p2p_set_firmware(काष्ठा brcmf_अगर *अगरp, u8 *p2p_mac)
अणु
	काष्ठा brcmf_pub *drvr = अगरp->drvr;
	s32 ret = 0;

	brcmf_fil_cmd_पूर्णांक_set(अगरp, BRCMF_C_DOWN, 1);
	brcmf_fil_iovar_पूर्णांक_set(अगरp, "apsta", 1);
	brcmf_fil_cmd_पूर्णांक_set(अगरp, BRCMF_C_UP, 1);

	/* In हाल of COB type, firmware has शेष mac address
	 * After Initializing firmware, we have to set current mac address to
	 * firmware क्रम P2P device address. This must be करोne with discovery
	 * disabled.
	 */
	brcmf_fil_iovar_पूर्णांक_set(अगरp, "p2p_disc", 0);

	ret = brcmf_fil_iovar_data_set(अगरp, "p2p_da_override", p2p_mac,
				       ETH_ALEN);
	अगर (ret)
		bphy_err(drvr, "failed to update device address ret %d\n", ret);

	वापस ret;
पूर्ण

/**
 * brcmf_p2p_generate_bss_mac() - derive mac addresses क्रम P2P.
 *
 * @p2p: P2P specअगरic data.
 * @dev_addr: optional device address.
 *
 * P2P needs mac addresses क्रम P2P device and पूर्णांकerface. If no device
 * address it specअगरied, these are derived from a अक्रमom ethernet
 * address.
 */
अटल व्योम brcmf_p2p_generate_bss_mac(काष्ठा brcmf_p2p_info *p2p, u8 *dev_addr)
अणु
	काष्ठा brcmf_अगर *pri_अगरp = p2p->bss_idx[P2PAPI_BSSCFG_PRIMARY].vअगर->अगरp;
	bool अक्रमom_addr = false;
	bool local_admin = false;

	अगर (!dev_addr || is_zero_ether_addr(dev_addr)) अणु
		/* If the primary पूर्णांकerface address is alपढ़ोy locally
		 * administered, create a new अक्रमom address.
		 */
		अगर (pri_अगरp->mac_addr[0] & 0x02) अणु
			अक्रमom_addr = true;
		पूर्ण अन्यथा अणु
			dev_addr = pri_अगरp->mac_addr;
			local_admin = true;
		पूर्ण
	पूर्ण

	/* Generate the P2P Device Address obtaining a अक्रमom ethernet
	 * address with the locally administered bit set.
	 */
	अगर (अक्रमom_addr)
		eth_अक्रमom_addr(p2p->dev_addr);
	अन्यथा
		स_नकल(p2p->dev_addr, dev_addr, ETH_ALEN);

	अगर (local_admin)
		p2p->dev_addr[0] |= 0x02;

	/* Generate the P2P Interface Address.  If the discovery and connection
	 * BSSCFGs need to simultaneously co-exist, then this address must be
	 * dअगरferent from the P2P Device Address, but also locally administered.
	 */
	स_नकल(p2p->conn_पूर्णांक_addr, p2p->dev_addr, ETH_ALEN);
	p2p->conn_पूर्णांक_addr[0] |= 0x02;
	p2p->conn_पूर्णांक_addr[4] ^= 0x80;

	स_नकल(p2p->conn2_पूर्णांक_addr, p2p->dev_addr, ETH_ALEN);
	p2p->conn2_पूर्णांक_addr[0] |= 0x02;
	p2p->conn2_पूर्णांक_addr[4] ^= 0x90;
पूर्ण

/**
 * brcmf_p2p_scan_is_p2p_request() - is cfg80211 scan request a P2P scan.
 *
 * @request: the scan request as received from cfg80211.
 *
 * वापसs true अगर one of the ssids in the request matches the
 * P2P wildcard ssid; otherwise वापसs false.
 */
अटल bool brcmf_p2p_scan_is_p2p_request(काष्ठा cfg80211_scan_request *request)
अणु
	काष्ठा cfg80211_ssid *ssids = request->ssids;
	पूर्णांक i;

	क्रम (i = 0; i < request->n_ssids; i++) अणु
		अगर (ssids[i].ssid_len != BRCMF_P2P_WILDCARD_SSID_LEN)
			जारी;

		brcmf_dbg(INFO, "comparing ssid \"%s\"", ssids[i].ssid);
		अगर (!स_भेद(BRCMF_P2P_WILDCARD_SSID, ssids[i].ssid,
			    BRCMF_P2P_WILDCARD_SSID_LEN))
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

/**
 * brcmf_p2p_set_discover_state - set discover state in firmware.
 *
 * @अगरp: low-level पूर्णांकerface object.
 * @state: discover state to set.
 * @chanspec: channel parameters (क्रम state @WL_P2P_DISC_ST_LISTEN only).
 * @listen_ms: duration to listen (क्रम state @WL_P2P_DISC_ST_LISTEN only).
 */
अटल s32 brcmf_p2p_set_discover_state(काष्ठा brcmf_अगर *अगरp, u8 state,
					u16 chanspec, u16 listen_ms)
अणु
	काष्ठा brcmf_p2p_disc_st_le discover_state;
	s32 ret = 0;
	brcmf_dbg(TRACE, "enter\n");

	discover_state.state = state;
	discover_state.chspec = cpu_to_le16(chanspec);
	discover_state.dwell = cpu_to_le16(listen_ms);
	ret = brcmf_fil_bsscfg_data_set(अगरp, "p2p_state", &discover_state,
					माप(discover_state));
	वापस ret;
पूर्ण

/**
 * brcmf_p2p_deinit_discovery() - disable P2P device discovery.
 *
 * @p2p: P2P specअगरic data.
 *
 * Resets the discovery state and disables it in firmware.
 */
अटल s32 brcmf_p2p_deinit_discovery(काष्ठा brcmf_p2p_info *p2p)
अणु
	काष्ठा brcmf_cfg80211_vअगर *vअगर;

	brcmf_dbg(TRACE, "enter\n");

	/* Set the discovery state to SCAN */
	vअगर = p2p->bss_idx[P2PAPI_BSSCFG_DEVICE].vअगर;
	(व्योम)brcmf_p2p_set_discover_state(vअगर->अगरp, WL_P2P_DISC_ST_SCAN, 0, 0);

	/* Disable P2P discovery in the firmware */
	vअगर = p2p->bss_idx[P2PAPI_BSSCFG_PRIMARY].vअगर;
	(व्योम)brcmf_fil_iovar_पूर्णांक_set(vअगर->अगरp, "p2p_disc", 0);

	वापस 0;
पूर्ण

/**
 * brcmf_p2p_enable_discovery() - initialize and configure discovery.
 *
 * @p2p: P2P specअगरic data.
 *
 * Initializes the discovery device and configure the भव पूर्णांकerface.
 */
अटल पूर्णांक brcmf_p2p_enable_discovery(काष्ठा brcmf_p2p_info *p2p)
अणु
	काष्ठा brcmf_pub *drvr = p2p->cfg->pub;
	काष्ठा brcmf_cfg80211_vअगर *vअगर;
	s32 ret = 0;

	brcmf_dbg(TRACE, "enter\n");
	vअगर = p2p->bss_idx[P2PAPI_BSSCFG_DEVICE].vअगर;
	अगर (!vअगर) अणु
		bphy_err(drvr, "P2P config device not available\n");
		ret = -EPERM;
		जाओ निकास;
	पूर्ण

	अगर (test_bit(BRCMF_P2P_STATUS_ENABLED, &p2p->status)) अणु
		brcmf_dbg(INFO, "P2P config device already configured\n");
		जाओ निकास;
	पूर्ण

	/* Re-initialize P2P Discovery in the firmware */
	vअगर = p2p->bss_idx[P2PAPI_BSSCFG_PRIMARY].vअगर;
	ret = brcmf_fil_iovar_पूर्णांक_set(vअगर->अगरp, "p2p_disc", 1);
	अगर (ret < 0) अणु
		bphy_err(drvr, "set p2p_disc error\n");
		जाओ निकास;
	पूर्ण
	vअगर = p2p->bss_idx[P2PAPI_BSSCFG_DEVICE].vअगर;
	ret = brcmf_p2p_set_discover_state(vअगर->अगरp, WL_P2P_DISC_ST_SCAN, 0, 0);
	अगर (ret < 0) अणु
		bphy_err(drvr, "unable to set WL_P2P_DISC_ST_SCAN\n");
		जाओ निकास;
	पूर्ण

	/*
	 * Set wsec to any non-zero value in the discovery bsscfg
	 * to ensure our P2P probe responses have the privacy bit
	 * set in the 802.11 WPA IE. Some peer devices may not
	 * initiate WPS with us अगर this bit is not set.
	 */
	ret = brcmf_fil_bsscfg_पूर्णांक_set(vअगर->अगरp, "wsec", AES_ENABLED);
	अगर (ret < 0) अणु
		bphy_err(drvr, "wsec error %d\n", ret);
		जाओ निकास;
	पूर्ण

	set_bit(BRCMF_P2P_STATUS_ENABLED, &p2p->status);
निकास:
	वापस ret;
पूर्ण

/**
 * brcmf_p2p_escan() - initiate a P2P scan.
 *
 * @p2p: P2P specअगरic data.
 * @num_chans: number of channels to scan.
 * @chanspecs: channel parameters क्रम @num_chans channels.
 * @search_state: P2P discover state to use.
 * @bss_type: type of P2P bss.
 */
अटल s32 brcmf_p2p_escan(काष्ठा brcmf_p2p_info *p2p, u32 num_chans,
			   u16 chanspecs[], s32 search_state,
			   क्रमागत p2p_bss_type bss_type)
अणु
	काष्ठा brcmf_pub *drvr = p2p->cfg->pub;
	s32 ret = 0;
	s32 memsize = दुरत्व(काष्ठा brcmf_p2p_scan_le,
			       eparams.params_le.channel_list);
	s32 nprobes;
	s32 active;
	u32 i;
	u8 *memblk;
	काष्ठा brcmf_cfg80211_vअगर *vअगर;
	काष्ठा brcmf_p2p_scan_le *p2p_params;
	काष्ठा brcmf_scan_params_le *sparams;

	memsize += num_chans * माप(__le16);
	memblk = kzalloc(memsize, GFP_KERNEL);
	अगर (!memblk)
		वापस -ENOMEM;

	vअगर = p2p->bss_idx[bss_type].vअगर;
	अगर (vअगर == शून्य) अणु
		bphy_err(drvr, "no vif for bss type %d\n", bss_type);
		ret = -EINVAL;
		जाओ निकास;
	पूर्ण
	p2p_params = (काष्ठा brcmf_p2p_scan_le *)memblk;
	sparams = &p2p_params->eparams.params_le;

	चयन (search_state) अणु
	हाल WL_P2P_DISC_ST_SEARCH:
		/*
		 * If we in SEARCH STATE, we करोn't need to set SSID explictly
		 * because करोngle use P2P WILDCARD पूर्णांकernally by शेष, use
		 * null ssid, which it is alपढ़ोy due to kzalloc.
		 */
		अवरोध;
	हाल WL_P2P_DISC_ST_SCAN:
		/*
		 * wpa_supplicant has p2p_find command with type social or
		 * progressive. For progressive, we need to set the ssid to
		 * P2P WILDCARD because we just करो broadcast scan unless
		 * setting SSID.
		 */
		sparams->ssid_le.SSID_len =
				cpu_to_le32(BRCMF_P2P_WILDCARD_SSID_LEN);
		स_नकल(sparams->ssid_le.SSID, BRCMF_P2P_WILDCARD_SSID,
		       BRCMF_P2P_WILDCARD_SSID_LEN);
		अवरोध;
	शेष:
		bphy_err(drvr, " invalid search state %d\n", search_state);
		ret = -EINVAL;
		जाओ निकास;
	पूर्ण

	brcmf_p2p_set_discover_state(vअगर->अगरp, search_state, 0, 0);

	/*
	 * set p2p scan parameters.
	 */
	p2p_params->type = 'E';

	/* determine the scan engine parameters */
	sparams->bss_type = DOT11_BSSTYPE_ANY;
	sparams->scan_type = BRCMF_SCANTYPE_ACTIVE;

	eth_broadcast_addr(sparams->bssid);
	sparams->home_समय = cpu_to_le32(P2PAPI_SCAN_HOME_TIME_MS);

	/*
	 * SOCIAL_CHAN_CNT + 1 takes care of the Progressive scan
	 * supported by the supplicant.
	 */
	अगर (num_chans == SOCIAL_CHAN_CNT || num_chans == (SOCIAL_CHAN_CNT + 1))
		active = P2PAPI_SCAN_SOCIAL_DWELL_TIME_MS;
	अन्यथा अगर (num_chans == AF_PEER_SEARCH_CNT)
		active = P2PAPI_SCAN_AF_SEARCH_DWELL_TIME_MS;
	अन्यथा अगर (brcmf_get_vअगर_state_any(p2p->cfg, BRCMF_VIF_STATUS_CONNECTED))
		active = -1;
	अन्यथा
		active = P2PAPI_SCAN_DWELL_TIME_MS;

	/* Override scan params to find a peer क्रम a connection */
	अगर (num_chans == 1) अणु
		active = WL_SCAN_CONNECT_DWELL_TIME_MS;
		/* WAR to sync with presence period of VSDB GO.
		 * send probe request more frequently
		 */
		nprobes = active / WL_SCAN_JOIN_PROBE_INTERVAL_MS;
	पूर्ण अन्यथा अणु
		nprobes = active / P2PAPI_SCAN_NPROBS_TIME_MS;
	पूर्ण

	अगर (nprobes <= 0)
		nprobes = 1;

	brcmf_dbg(INFO, "nprobes # %d, active_time %d\n", nprobes, active);
	sparams->active_समय = cpu_to_le32(active);
	sparams->nprobes = cpu_to_le32(nprobes);
	sparams->passive_समय = cpu_to_le32(-1);
	sparams->channel_num = cpu_to_le32(num_chans &
					   BRCMF_SCAN_PARAMS_COUNT_MASK);
	क्रम (i = 0; i < num_chans; i++)
		sparams->channel_list[i] = cpu_to_le16(chanspecs[i]);

	/* set the escan specअगरic parameters */
	p2p_params->eparams.version = cpu_to_le32(BRCMF_ESCAN_REQ_VERSION);
	p2p_params->eparams.action =  cpu_to_le16(WL_ESCAN_ACTION_START);
	p2p_params->eparams.sync_id = cpu_to_le16(0x1234);
	/* perक्रमm p2p scan on primary device */
	ret = brcmf_fil_bsscfg_data_set(vअगर->अगरp, "p2p_scan", memblk, memsize);
	अगर (!ret)
		set_bit(BRCMF_SCAN_STATUS_BUSY, &p2p->cfg->scan_status);
निकास:
	kमुक्त(memblk);
	वापस ret;
पूर्ण

/**
 * brcmf_p2p_run_escan() - escan callback क्रम peer-to-peer.
 *
 * @cfg: driver निजी data क्रम cfg80211 पूर्णांकerface.
 * @अगरp: पूर्णांकerface control.
 * @request: scan request from cfg80211.
 *
 * Determines the P2P discovery state based to scan request parameters and
 * validates the channels in the request.
 */
अटल s32 brcmf_p2p_run_escan(काष्ठा brcmf_cfg80211_info *cfg,
			       काष्ठा brcmf_अगर *अगरp,
			       काष्ठा cfg80211_scan_request *request)
अणु
	काष्ठा brcmf_p2p_info *p2p = &cfg->p2p;
	काष्ठा brcmf_pub *drvr = cfg->pub;
	s32 err = 0;
	s32 search_state = WL_P2P_DISC_ST_SCAN;
	काष्ठा brcmf_cfg80211_vअगर *vअगर;
	काष्ठा net_device *dev = शून्य;
	पूर्णांक i, num_nodfs = 0;
	u16 *chanspecs;

	brcmf_dbg(TRACE, "enter\n");

	अगर (!request) अणु
		err = -EINVAL;
		जाओ निकास;
	पूर्ण

	अगर (request->n_channels) अणु
		chanspecs = kसुस्मृति(request->n_channels, माप(*chanspecs),
				    GFP_KERNEL);
		अगर (!chanspecs) अणु
			err = -ENOMEM;
			जाओ निकास;
		पूर्ण
		vअगर = p2p->bss_idx[P2PAPI_BSSCFG_CONNECTION].vअगर;
		अगर (vअगर)
			dev = vअगर->wdev.netdev;
		अगर (request->n_channels == 3 &&
		    request->channels[0]->hw_value == SOCIAL_CHAN_1 &&
		    request->channels[1]->hw_value == SOCIAL_CHAN_2 &&
		    request->channels[2]->hw_value == SOCIAL_CHAN_3) अणु
			/* SOCIAL CHANNELS 1, 6, 11 */
			search_state = WL_P2P_DISC_ST_SEARCH;
			brcmf_dbg(INFO, "P2P SEARCH PHASE START\n");
		पूर्ण अन्यथा अगर (dev != शून्य &&
			   vअगर->wdev.अगरtype == NL80211_IFTYPE_P2P_GO) अणु
			/* If you are alपढ़ोy a GO, then करो SEARCH only */
			brcmf_dbg(INFO, "Already a GO. Do SEARCH Only\n");
			search_state = WL_P2P_DISC_ST_SEARCH;
		पूर्ण अन्यथा अणु
			brcmf_dbg(INFO, "P2P SCAN STATE START\n");
		पूर्ण

		/*
		 * no P2P scanning on passive or DFS channels.
		 */
		क्रम (i = 0; i < request->n_channels; i++) अणु
			काष्ठा ieee80211_channel *chan = request->channels[i];

			अगर (chan->flags & (IEEE80211_CHAN_RADAR |
					   IEEE80211_CHAN_NO_IR))
				जारी;

			chanspecs[i] = channel_to_chanspec(&p2p->cfg->d11inf,
							   chan);
			brcmf_dbg(INFO, "%d: chan=%d, channel spec=%x\n",
				  num_nodfs, chan->hw_value, chanspecs[i]);
			num_nodfs++;
		पूर्ण
		err = brcmf_p2p_escan(p2p, num_nodfs, chanspecs, search_state,
				      P2PAPI_BSSCFG_DEVICE);
		kमुक्त(chanspecs);
	पूर्ण
निकास:
	अगर (err)
		bphy_err(drvr, "error (%d)\n", err);
	वापस err;
पूर्ण


/**
 * brcmf_p2p_find_listen_channel() - find listen channel in ie string.
 *
 * @ie: string of inक्रमmation elements.
 * @ie_len: length of string.
 *
 * Scan ie क्रम p2p ie and look क्रम attribute 6 channel. If available determine
 * channel and वापस it.
 */
अटल s32 brcmf_p2p_find_listen_channel(स्थिर u8 *ie, u32 ie_len)
अणु
	u8 channel_ie[5];
	s32 listen_channel;
	s32 err;

	err = cfg80211_get_p2p_attr(ie, ie_len,
				    IEEE80211_P2P_ATTR_LISTEN_CHANNEL,
				    channel_ie, माप(channel_ie));
	अगर (err < 0)
		वापस err;

	/* listen channel subel length क्रमmat:     */
	/* 3(country) + 1(op. class) + 1(chan num) */
	listen_channel = (s32)channel_ie[3 + 1];

	अगर (listen_channel == SOCIAL_CHAN_1 ||
	    listen_channel == SOCIAL_CHAN_2 ||
	    listen_channel == SOCIAL_CHAN_3) अणु
		brcmf_dbg(INFO, "Found my Listen Channel %d\n", listen_channel);
		वापस listen_channel;
	पूर्ण

	वापस -EPERM;
पूर्ण


/**
 * brcmf_p2p_scan_prep() - prepare scan based on request.
 *
 * @wiphy: wiphy device.
 * @request: scan request from cfg80211.
 * @vअगर: vअगर on which scan request is to be executed.
 *
 * Prepare the scan appropriately क्रम type of scan requested. Overrides the
 * escan .run() callback क्रम peer-to-peer scanning.
 */
पूर्णांक brcmf_p2p_scan_prep(काष्ठा wiphy *wiphy,
			काष्ठा cfg80211_scan_request *request,
			काष्ठा brcmf_cfg80211_vअगर *vअगर)
अणु
	काष्ठा brcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	काष्ठा brcmf_p2p_info *p2p = &cfg->p2p;
	पूर्णांक err;

	अगर (brcmf_p2p_scan_is_p2p_request(request)) अणु
		/* find my listen channel */
		err = brcmf_p2p_find_listen_channel(request->ie,
						    request->ie_len);
		अगर (err < 0)
			वापस err;

		p2p->afx_hdl.my_listen_chan = err;

		clear_bit(BRCMF_P2P_STATUS_GO_NEG_PHASE, &p2p->status);
		brcmf_dbg(INFO, "P2P: GO_NEG_PHASE status cleared\n");

		err = brcmf_p2p_enable_discovery(p2p);
		अगर (err)
			वापस err;

		/* override .run_escan() callback. */
		cfg->escan_info.run = brcmf_p2p_run_escan;
	पूर्ण
	वापस 0;
पूर्ण


/**
 * brcmf_p2p_discover_listen() - set firmware to discover listen state.
 *
 * @p2p: p2p device.
 * @channel: channel nr क्रम discover listen.
 * @duration: समय in ms to stay on channel.
 *
 */
अटल s32
brcmf_p2p_discover_listen(काष्ठा brcmf_p2p_info *p2p, u16 channel, u32 duration)
अणु
	काष्ठा brcmf_pub *drvr = p2p->cfg->pub;
	काष्ठा brcmf_cfg80211_vअगर *vअगर;
	काष्ठा brcmu_chan ch;
	s32 err = 0;

	vअगर = p2p->bss_idx[P2PAPI_BSSCFG_DEVICE].vअगर;
	अगर (!vअगर) अणु
		bphy_err(drvr, "Discovery is not set, so we have nothing to do\n");
		err = -EPERM;
		जाओ निकास;
	पूर्ण

	अगर (test_bit(BRCMF_P2P_STATUS_DISCOVER_LISTEN, &p2p->status)) अणु
		bphy_err(drvr, "Previous LISTEN is not completed yet\n");
		/* WAR: prevent cookie mismatch in wpa_supplicant वापस OK */
		जाओ निकास;
	पूर्ण

	ch.chnum = channel;
	ch.bw = BRCMU_CHAN_BW_20;
	p2p->cfg->d11inf.encchspec(&ch);
	err = brcmf_p2p_set_discover_state(vअगर->अगरp, WL_P2P_DISC_ST_LISTEN,
					   ch.chspec, (u16)duration);
	अगर (!err) अणु
		set_bit(BRCMF_P2P_STATUS_DISCOVER_LISTEN, &p2p->status);
		p2p->reमुख्य_on_channel_cookie++;
	पूर्ण
निकास:
	वापस err;
पूर्ण


/**
 * brcmf_p2p_reमुख्य_on_channel() - put device on channel and stay there.
 *
 * @wiphy: wiphy device.
 * @wdev: wireless device.
 * @channel: channel to stay on.
 * @duration: समय in ms to reमुख्य on channel.
 * @cookie: cookie.
 */
पूर्णांक brcmf_p2p_reमुख्य_on_channel(काष्ठा wiphy *wiphy, काष्ठा wireless_dev *wdev,
				काष्ठा ieee80211_channel *channel,
				अचिन्हित पूर्णांक duration, u64 *cookie)
अणु
	काष्ठा brcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	काष्ठा brcmf_p2p_info *p2p = &cfg->p2p;
	s32 err;
	u16 channel_nr;

	channel_nr = ieee80211_frequency_to_channel(channel->center_freq);
	brcmf_dbg(TRACE, "Enter, channel: %d, duration ms (%d)\n", channel_nr,
		  duration);

	err = brcmf_p2p_enable_discovery(p2p);
	अगर (err)
		जाओ निकास;
	err = brcmf_p2p_discover_listen(p2p, channel_nr, duration);
	अगर (err)
		जाओ निकास;

	स_नकल(&p2p->reमुख्य_on_channel, channel, माप(*channel));
	*cookie = p2p->reमुख्य_on_channel_cookie;
	cfg80211_पढ़ोy_on_channel(wdev, *cookie, channel, duration, GFP_KERNEL);

निकास:
	वापस err;
पूर्ण


/**
 * brcmf_p2p_notअगरy_listen_complete() - p2p listen has completed.
 *
 * @अगरp: पूर्णांकerfac control.
 * @e: event message. Not used, to make it usable क्रम fweh event dispatcher.
 * @data: payload of message. Not used.
 *
 */
पूर्णांक brcmf_p2p_notअगरy_listen_complete(काष्ठा brcmf_अगर *अगरp,
				     स्थिर काष्ठा brcmf_event_msg *e,
				     व्योम *data)
अणु
	काष्ठा brcmf_cfg80211_info *cfg = अगरp->drvr->config;
	काष्ठा brcmf_p2p_info *p2p = &cfg->p2p;

	brcmf_dbg(TRACE, "Enter\n");
	अगर (test_and_clear_bit(BRCMF_P2P_STATUS_DISCOVER_LISTEN,
			       &p2p->status)) अणु
		अगर (test_and_clear_bit(BRCMF_P2P_STATUS_WAITING_NEXT_AF_LISTEN,
				       &p2p->status)) अणु
			clear_bit(BRCMF_P2P_STATUS_WAITING_NEXT_ACT_FRAME,
				  &p2p->status);
			brcmf_dbg(INFO, "Listen DONE, wake up wait_next_af\n");
			complete(&p2p->रुको_next_af);
		पूर्ण

		cfg80211_reमुख्य_on_channel_expired(&अगरp->vअगर->wdev,
						   p2p->reमुख्य_on_channel_cookie,
						   &p2p->reमुख्य_on_channel,
						   GFP_KERNEL);
	पूर्ण
	वापस 0;
पूर्ण


/**
 * brcmf_p2p_cancel_reमुख्य_on_channel() - cancel p2p listen state.
 *
 * @अगरp: पूर्णांकerfac control.
 *
 */
व्योम brcmf_p2p_cancel_reमुख्य_on_channel(काष्ठा brcmf_अगर *अगरp)
अणु
	अगर (!अगरp)
		वापस;
	brcmf_p2p_set_discover_state(अगरp, WL_P2P_DISC_ST_SCAN, 0, 0);
	brcmf_p2p_notअगरy_listen_complete(अगरp, शून्य, शून्य);
पूर्ण


/**
 * brcmf_p2p_act_frm_search() - search function क्रम action frame.
 *
 * @p2p: p2p device.
 * @channel: channel on which action frame is to be trयंत्रitted.
 *
 * search function to reach at common channel to send action frame. When
 * channel is 0 then all social channels will be used to send af
 */
अटल s32 brcmf_p2p_act_frm_search(काष्ठा brcmf_p2p_info *p2p, u16 channel)
अणु
	काष्ठा brcmf_pub *drvr = p2p->cfg->pub;
	s32 err;
	u32 channel_cnt;
	u16 *शेष_chan_list;
	u32 i;
	काष्ठा brcmu_chan ch;

	brcmf_dbg(TRACE, "Enter\n");

	अगर (channel)
		channel_cnt = AF_PEER_SEARCH_CNT;
	अन्यथा
		channel_cnt = SOCIAL_CHAN_CNT;
	शेष_chan_list = kसुस्मृति(channel_cnt, माप(*शेष_chan_list),
				    GFP_KERNEL);
	अगर (शेष_chan_list == शून्य) अणु
		bphy_err(drvr, "channel list allocation failed\n");
		err = -ENOMEM;
		जाओ निकास;
	पूर्ण
	ch.bw = BRCMU_CHAN_BW_20;
	अगर (channel) अणु
		ch.chnum = channel;
		p2p->cfg->d11inf.encchspec(&ch);
		/* insert same channel to the chan_list */
		क्रम (i = 0; i < channel_cnt; i++)
			शेष_chan_list[i] = ch.chspec;
	पूर्ण अन्यथा अणु
		ch.chnum = SOCIAL_CHAN_1;
		p2p->cfg->d11inf.encchspec(&ch);
		शेष_chan_list[0] = ch.chspec;
		ch.chnum = SOCIAL_CHAN_2;
		p2p->cfg->d11inf.encchspec(&ch);
		शेष_chan_list[1] = ch.chspec;
		ch.chnum = SOCIAL_CHAN_3;
		p2p->cfg->d11inf.encchspec(&ch);
		शेष_chan_list[2] = ch.chspec;
	पूर्ण
	err = brcmf_p2p_escan(p2p, channel_cnt, शेष_chan_list,
			      WL_P2P_DISC_ST_SEARCH, P2PAPI_BSSCFG_DEVICE);
	kमुक्त(शेष_chan_list);
निकास:
	वापस err;
पूर्ण


/**
 * brcmf_p2p_afx_handler() - afx worker thपढ़ो.
 *
 * @work:
 *
 */
अटल व्योम brcmf_p2p_afx_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा afx_hdl *afx_hdl = container_of(work, काष्ठा afx_hdl, afx_work);
	काष्ठा brcmf_p2p_info *p2p = container_of(afx_hdl,
						  काष्ठा brcmf_p2p_info,
						  afx_hdl);
	काष्ठा brcmf_pub *drvr = p2p->cfg->pub;
	s32 err;

	अगर (!afx_hdl->is_active)
		वापस;

	अगर (afx_hdl->is_listen && afx_hdl->my_listen_chan)
		/* 100ms ~ 300ms */
		err = brcmf_p2p_discover_listen(p2p, afx_hdl->my_listen_chan,
						100 * (1 + pअक्रमom_u32() % 3));
	अन्यथा
		err = brcmf_p2p_act_frm_search(p2p, afx_hdl->peer_listen_chan);

	अगर (err) अणु
		bphy_err(drvr, "ERROR occurred! value is (%d)\n", err);
		अगर (test_bit(BRCMF_P2P_STATUS_FINDING_COMMON_CHANNEL,
			     &p2p->status))
			complete(&afx_hdl->act_frm_scan);
	पूर्ण
पूर्ण


/**
 * brcmf_p2p_af_searching_channel() - search channel.
 *
 * @p2p: p2p device info काष्ठा.
 *
 */
अटल s32 brcmf_p2p_af_searching_channel(काष्ठा brcmf_p2p_info *p2p)
अणु
	काष्ठा afx_hdl *afx_hdl = &p2p->afx_hdl;
	काष्ठा brcmf_cfg80211_vअगर *pri_vअगर;
	s32 retry;

	brcmf_dbg(TRACE, "Enter\n");

	pri_vअगर = p2p->bss_idx[P2PAPI_BSSCFG_PRIMARY].vअगर;

	reinit_completion(&afx_hdl->act_frm_scan);
	set_bit(BRCMF_P2P_STATUS_FINDING_COMMON_CHANNEL, &p2p->status);
	afx_hdl->is_active = true;
	afx_hdl->peer_chan = P2P_INVALID_CHANNEL;

	/* Loop to रुको until we find a peer's channel or the
	 * pending action frame tx is cancelled.
	 */
	retry = 0;
	जबतक ((retry < P2P_CHANNEL_SYNC_RETRY) &&
	       (afx_hdl->peer_chan == P2P_INVALID_CHANNEL)) अणु
		afx_hdl->is_listen = false;
		brcmf_dbg(TRACE, "Scheduling action frame for sending.. (%d)\n",
			  retry);
		/* search peer on peer's listen channel */
		schedule_work(&afx_hdl->afx_work);
		रुको_क्रम_completion_समयout(&afx_hdl->act_frm_scan,
					    P2P_AF_FRM_SCAN_MAX_WAIT);
		अगर ((afx_hdl->peer_chan != P2P_INVALID_CHANNEL) ||
		    (!test_bit(BRCMF_P2P_STATUS_FINDING_COMMON_CHANNEL,
			       &p2p->status)))
			अवरोध;

		अगर (afx_hdl->my_listen_chan) अणु
			brcmf_dbg(TRACE, "Scheduling listen peer, channel=%d\n",
				  afx_hdl->my_listen_chan);
			/* listen on my listen channel */
			afx_hdl->is_listen = true;
			schedule_work(&afx_hdl->afx_work);
			रुको_क्रम_completion_समयout(&afx_hdl->act_frm_scan,
						    P2P_AF_FRM_SCAN_MAX_WAIT);
		पूर्ण
		अगर ((afx_hdl->peer_chan != P2P_INVALID_CHANNEL) ||
		    (!test_bit(BRCMF_P2P_STATUS_FINDING_COMMON_CHANNEL,
			       &p2p->status)))
			अवरोध;
		retry++;

		/* अगर sta is connected or connecting, sleep क्रम a जबतक beक्रमe
		 * retry af tx or finding a peer
		 */
		अगर (test_bit(BRCMF_VIF_STATUS_CONNECTED, &pri_vअगर->sme_state) ||
		    test_bit(BRCMF_VIF_STATUS_CONNECTING, &pri_vअगर->sme_state))
			msleep(P2P_DEFAULT_SLEEP_TIME_VSDB);
	पूर्ण

	brcmf_dbg(TRACE, "Completed search/listen peer_chan=%d\n",
		  afx_hdl->peer_chan);
	afx_hdl->is_active = false;

	clear_bit(BRCMF_P2P_STATUS_FINDING_COMMON_CHANNEL, &p2p->status);

	वापस afx_hdl->peer_chan;
पूर्ण


/**
 * brcmf_p2p_scan_finding_common_channel() - was escan used क्रम finding channel
 *
 * @cfg: common configuration काष्ठा.
 * @bi: bss info काष्ठा, result from scan.
 *
 */
bool brcmf_p2p_scan_finding_common_channel(काष्ठा brcmf_cfg80211_info *cfg,
					   काष्ठा brcmf_bss_info_le *bi)

अणु
	काष्ठा brcmf_p2p_info *p2p = &cfg->p2p;
	काष्ठा afx_hdl *afx_hdl = &p2p->afx_hdl;
	काष्ठा brcmu_chan ch;
	u8 *ie;
	s32 err;
	u8 p2p_dev_addr[ETH_ALEN];

	अगर (!test_bit(BRCMF_P2P_STATUS_FINDING_COMMON_CHANNEL, &p2p->status))
		वापस false;

	अगर (bi == शून्य) अणु
		brcmf_dbg(TRACE, "ACTION FRAME SCAN Done\n");
		अगर (afx_hdl->peer_chan == P2P_INVALID_CHANNEL)
			complete(&afx_hdl->act_frm_scan);
		वापस true;
	पूर्ण

	ie = ((u8 *)bi) + le16_to_cpu(bi->ie_offset);
	स_रखो(p2p_dev_addr, 0, माप(p2p_dev_addr));
	err = cfg80211_get_p2p_attr(ie, le32_to_cpu(bi->ie_length),
				    IEEE80211_P2P_ATTR_DEVICE_INFO,
				    p2p_dev_addr, माप(p2p_dev_addr));
	अगर (err < 0)
		err = cfg80211_get_p2p_attr(ie, le32_to_cpu(bi->ie_length),
					    IEEE80211_P2P_ATTR_DEVICE_ID,
					    p2p_dev_addr, माप(p2p_dev_addr));
	अगर ((err >= 0) &&
	    (ether_addr_equal(p2p_dev_addr, afx_hdl->tx_dst_addr))) अणु
		अगर (!bi->ctl_ch) अणु
			ch.chspec = le16_to_cpu(bi->chanspec);
			cfg->d11inf.decchspec(&ch);
			bi->ctl_ch = ch.control_ch_num;
		पूर्ण
		afx_hdl->peer_chan = bi->ctl_ch;
		brcmf_dbg(TRACE, "ACTION FRAME SCAN : Peer %pM found, channel : %d\n",
			  afx_hdl->tx_dst_addr, afx_hdl->peer_chan);
		complete(&afx_hdl->act_frm_scan);
	पूर्ण
	वापस true;
पूर्ण

/**
 * brcmf_p2p_पात_action_frame() - पात action frame.
 *
 * @cfg: common configuration काष्ठा.
 *
 */
अटल s32 brcmf_p2p_पात_action_frame(काष्ठा brcmf_cfg80211_info *cfg)
अणु
	काष्ठा brcmf_p2p_info *p2p = &cfg->p2p;
	काष्ठा brcmf_cfg80211_vअगर *vअगर;
	s32 err;
	s32 पूर्णांक_val = 1;

	brcmf_dbg(TRACE, "Enter\n");

	vअगर = p2p->bss_idx[P2PAPI_BSSCFG_DEVICE].vअगर;
	err = brcmf_fil_bsscfg_data_set(vअगर->अगरp, "actframe_abort", &पूर्णांक_val,
					माप(s32));
	अगर (err)
		brcmf_err(" aborting action frame has failed (%d)\n", err);

	वापस err;
पूर्ण

/**
 * brcmf_p2p_stop_रुको_next_action_frame() - finish scan अगर af tx complete.
 *
 * @cfg: common configuration काष्ठा.
 *
 */
अटल व्योम
brcmf_p2p_stop_रुको_next_action_frame(काष्ठा brcmf_cfg80211_info *cfg)
अणु
	काष्ठा brcmf_p2p_info *p2p = &cfg->p2p;
	काष्ठा brcmf_अगर *अगरp = p2p->bss_idx[P2PAPI_BSSCFG_PRIMARY].vअगर->अगरp;
	s32 err;

	अगर (test_bit(BRCMF_P2P_STATUS_SENDING_ACT_FRAME, &p2p->status) &&
	    (test_bit(BRCMF_P2P_STATUS_ACTION_TX_COMPLETED, &p2p->status) ||
	     test_bit(BRCMF_P2P_STATUS_ACTION_TX_NOACK, &p2p->status))) अणु
		brcmf_dbg(TRACE, "*** Wake UP ** abort actframe iovar\n");
		/* अगर channel is not zero, "actfame" uses off channel scan.
		 * So पात scan क्रम off channel completion.
		 */
		अगर (p2p->af_sent_channel) अणु
			/* पात actframe using actframe_पात or पात scan */
			err = brcmf_p2p_पात_action_frame(cfg);
			अगर (err)
				brcmf_notअगरy_escan_complete(cfg, अगरp, true,
							    true);
		पूर्ण
	पूर्ण अन्यथा अगर (test_bit(BRCMF_P2P_STATUS_WAITING_NEXT_AF_LISTEN,
			    &p2p->status)) अणु
		brcmf_dbg(TRACE, "*** Wake UP ** abort listen for next af frame\n");
		/* So पात scan to cancel listen */
		brcmf_notअगरy_escan_complete(cfg, अगरp, true, true);
	पूर्ण
पूर्ण


/**
 * brcmf_p2p_gon_req_collision() - Check अगर go negotiaton collission
 *
 * @p2p: p2p device info काष्ठा.
 * @mac: MAC address.
 *
 * वापस true अगर recevied action frame is to be dropped.
 */
अटल bool
brcmf_p2p_gon_req_collision(काष्ठा brcmf_p2p_info *p2p, u8 *mac)
अणु
	काष्ठा brcmf_cfg80211_info *cfg = p2p->cfg;
	काष्ठा brcmf_अगर *अगरp;

	brcmf_dbg(TRACE, "Enter\n");

	अगर (!test_bit(BRCMF_P2P_STATUS_WAITING_NEXT_ACT_FRAME, &p2p->status) ||
	    !p2p->gon_req_action)
		वापस false;

	brcmf_dbg(TRACE, "GO Negotiation Request COLLISION !!!\n");
	/* अगर sa(peer) addr is less than da(my) addr, then this device
	 * process peer's gon request and block to send gon req.
	 * अगर not (sa addr > da addr),
	 * this device will process gon request and drop gon req of peer.
	 */
	अगरp = p2p->bss_idx[P2PAPI_BSSCFG_DEVICE].vअगर->अगरp;
	अगर (स_भेद(mac, अगरp->mac_addr, ETH_ALEN) < 0) अणु
		brcmf_dbg(INFO, "Block transmit gon req !!!\n");
		p2p->block_gon_req_tx = true;
		/* अगर we are finding a common channel क्रम sending af,
		 * करो not scan more to block to send current gon req
		 */
		अगर (test_and_clear_bit(BRCMF_P2P_STATUS_FINDING_COMMON_CHANNEL,
				       &p2p->status))
			complete(&p2p->afx_hdl.act_frm_scan);
		अगर (test_and_clear_bit(BRCMF_P2P_STATUS_WAITING_NEXT_ACT_FRAME,
				       &p2p->status))
			brcmf_p2p_stop_रुको_next_action_frame(cfg);
		वापस false;
	पूर्ण

	/* drop gon request of peer to process gon request by this device. */
	brcmf_dbg(INFO, "Drop received gon req !!!\n");

	वापस true;
पूर्ण


/**
 * brcmf_p2p_notअगरy_action_frame_rx() - received action frame.
 *
 * @अगरp: पूर्णांकerfac control.
 * @e: event message. Not used, to make it usable क्रम fweh event dispatcher.
 * @data: payload of message, containing action frame data.
 *
 */
पूर्णांक brcmf_p2p_notअगरy_action_frame_rx(काष्ठा brcmf_अगर *अगरp,
				     स्थिर काष्ठा brcmf_event_msg *e,
				     व्योम *data)
अणु
	काष्ठा brcmf_pub *drvr = अगरp->drvr;
	काष्ठा brcmf_cfg80211_info *cfg = drvr->config;
	काष्ठा brcmf_p2p_info *p2p = &cfg->p2p;
	काष्ठा afx_hdl *afx_hdl = &p2p->afx_hdl;
	काष्ठा wireless_dev *wdev;
	u32 mgmt_frame_len = e->datalen - माप(काष्ठा brcmf_rx_mgmt_data);
	काष्ठा brcmf_rx_mgmt_data *rxframe = (काष्ठा brcmf_rx_mgmt_data *)data;
	u8 *frame = (u8 *)(rxframe + 1);
	काष्ठा brcmf_p2p_pub_act_frame *act_frm;
	काष्ठा brcmf_p2psd_gas_pub_act_frame *sd_act_frm;
	काष्ठा brcmu_chan ch;
	काष्ठा ieee80211_mgmt *mgmt_frame;
	s32 freq;
	u16 mgmt_type;
	u8 action;

	अगर (e->datalen < माप(*rxframe)) अणु
		brcmf_dbg(SCAN, "Event data to small. Ignore\n");
		वापस 0;
	पूर्ण

	ch.chspec = be16_to_cpu(rxframe->chanspec);
	cfg->d11inf.decchspec(&ch);
	/* Check अगर wpa_supplicant has रेजिस्टरed क्रम this frame */
	brcmf_dbg(INFO, "ifp->vif->mgmt_rx_reg %04x\n", अगरp->vअगर->mgmt_rx_reg);
	mgmt_type = (IEEE80211_STYPE_ACTION & IEEE80211_FCTL_STYPE) >> 4;
	अगर ((अगरp->vअगर->mgmt_rx_reg & BIT(mgmt_type)) == 0)
		वापस 0;

	brcmf_p2p_prपूर्णांक_actframe(false, frame, mgmt_frame_len);

	action = P2P_PAF_SUBTYPE_INVALID;
	अगर (brcmf_p2p_is_pub_action(frame, mgmt_frame_len)) अणु
		act_frm = (काष्ठा brcmf_p2p_pub_act_frame *)frame;
		action = act_frm->subtype;
		अगर ((action == P2P_PAF_GON_REQ) &&
		    (brcmf_p2p_gon_req_collision(p2p, (u8 *)e->addr))) अणु
			अगर (test_bit(BRCMF_P2P_STATUS_FINDING_COMMON_CHANNEL,
				     &p2p->status) &&
			    (ether_addr_equal(afx_hdl->tx_dst_addr, e->addr))) अणु
				afx_hdl->peer_chan = ch.control_ch_num;
				brcmf_dbg(INFO, "GON request: Peer found, channel=%d\n",
					  afx_hdl->peer_chan);
				complete(&afx_hdl->act_frm_scan);
			पूर्ण
			वापस 0;
		पूर्ण
		/* After complete GO Negotiation, roll back to mpc mode */
		अगर ((action == P2P_PAF_GON_CONF) ||
		    (action == P2P_PAF_PROVDIS_RSP))
			brcmf_set_mpc(अगरp, 1);
		अगर (action == P2P_PAF_GON_CONF) अणु
			brcmf_dbg(TRACE, "P2P: GO_NEG_PHASE status cleared\n");
			clear_bit(BRCMF_P2P_STATUS_GO_NEG_PHASE, &p2p->status);
		पूर्ण
	पूर्ण अन्यथा अगर (brcmf_p2p_is_gas_action(frame, mgmt_frame_len)) अणु
		sd_act_frm = (काष्ठा brcmf_p2psd_gas_pub_act_frame *)frame;
		action = sd_act_frm->action;
	पूर्ण

	अगर (test_bit(BRCMF_P2P_STATUS_WAITING_NEXT_ACT_FRAME, &p2p->status) &&
	    (p2p->next_af_subtype == action)) अणु
		brcmf_dbg(TRACE, "We got a right next frame! (%d)\n", action);
		clear_bit(BRCMF_P2P_STATUS_WAITING_NEXT_ACT_FRAME,
			  &p2p->status);
		/* Stop रुकोing क्रम next AF. */
		brcmf_p2p_stop_रुको_next_action_frame(cfg);
	पूर्ण

	mgmt_frame = kzalloc(दुरत्व(काष्ठा ieee80211_mgmt, u) +
			     mgmt_frame_len, GFP_KERNEL);
	अगर (!mgmt_frame) अणु
		bphy_err(drvr, "No memory available for action frame\n");
		वापस -ENOMEM;
	पूर्ण
	स_नकल(mgmt_frame->da, अगरp->mac_addr, ETH_ALEN);
	brcmf_fil_cmd_data_get(अगरp, BRCMF_C_GET_BSSID, mgmt_frame->bssid,
			       ETH_ALEN);
	स_नकल(mgmt_frame->sa, e->addr, ETH_ALEN);
	mgmt_frame->frame_control = cpu_to_le16(IEEE80211_STYPE_ACTION);
	स_नकल(&mgmt_frame->u, frame, mgmt_frame_len);
	mgmt_frame_len += दुरत्व(काष्ठा ieee80211_mgmt, u);

	freq = ieee80211_channel_to_frequency(ch.control_ch_num,
					      ch.band == BRCMU_CHAN_BAND_2G ?
					      NL80211_BAND_2GHZ :
					      NL80211_BAND_5GHZ);

	wdev = &अगरp->vअगर->wdev;
	cfg80211_rx_mgmt(wdev, freq, 0, (u8 *)mgmt_frame, mgmt_frame_len, 0);

	kमुक्त(mgmt_frame);
	वापस 0;
पूर्ण


/**
 * brcmf_p2p_notअगरy_action_tx_complete() - transmit action frame complete
 *
 * @अगरp: पूर्णांकerfac control.
 * @e: event message. Not used, to make it usable क्रम fweh event dispatcher.
 * @data: not used.
 *
 */
पूर्णांक brcmf_p2p_notअगरy_action_tx_complete(काष्ठा brcmf_अगर *अगरp,
					स्थिर काष्ठा brcmf_event_msg *e,
					व्योम *data)
अणु
	काष्ठा brcmf_cfg80211_info *cfg = अगरp->drvr->config;
	काष्ठा brcmf_p2p_info *p2p = &cfg->p2p;

	brcmf_dbg(INFO, "Enter: event %s, status=%d\n",
		  e->event_code == BRCMF_E_ACTION_FRAME_OFF_CHAN_COMPLETE ?
		  "ACTION_FRAME_OFF_CHAN_COMPLETE" : "ACTION_FRAME_COMPLETE",
		  e->status);

	अगर (!test_bit(BRCMF_P2P_STATUS_SENDING_ACT_FRAME, &p2p->status))
		वापस 0;

	अगर (e->event_code == BRCMF_E_ACTION_FRAME_COMPLETE) अणु
		अगर (e->status == BRCMF_E_STATUS_SUCCESS) अणु
			set_bit(BRCMF_P2P_STATUS_ACTION_TX_COMPLETED,
				&p2p->status);
			अगर (!p2p->रुको_क्रम_offchan_complete)
				complete(&p2p->send_af_करोne);
		पूर्ण अन्यथा अणु
			set_bit(BRCMF_P2P_STATUS_ACTION_TX_NOACK, &p2p->status);
			/* If there is no ack, we करोn't need to रुको क्रम
			 * WLC_E_ACTION_FRAME_OFFCHAN_COMPLETE event
			 */
			brcmf_p2p_stop_रुको_next_action_frame(cfg);
		पूर्ण

	पूर्ण अन्यथा अणु
		complete(&p2p->send_af_करोne);
	पूर्ण
	वापस 0;
पूर्ण


/**
 * brcmf_p2p_tx_action_frame() - send action frame over fil.
 *
 * @p2p: p2p info काष्ठा क्रम vअगर.
 * @af_params: action frame data/info.
 *
 * Send an action frame immediately without करोing channel synchronization.
 *
 * This function रुकोs क्रम a completion event beक्रमe वापसing.
 * The WLC_E_ACTION_FRAME_COMPLETE event will be received when the action
 * frame is transmitted.
 */
अटल s32 brcmf_p2p_tx_action_frame(काष्ठा brcmf_p2p_info *p2p,
				     काष्ठा brcmf_fil_af_params_le *af_params)
अणु
	काष्ठा brcmf_pub *drvr = p2p->cfg->pub;
	काष्ठा brcmf_cfg80211_vअगर *vअगर;
	काष्ठा brcmf_p2p_action_frame *p2p_af;
	s32 err = 0;

	brcmf_dbg(TRACE, "Enter\n");

	reinit_completion(&p2p->send_af_करोne);
	clear_bit(BRCMF_P2P_STATUS_ACTION_TX_COMPLETED, &p2p->status);
	clear_bit(BRCMF_P2P_STATUS_ACTION_TX_NOACK, &p2p->status);

	/* check अगर it is a p2p_presence response */
	p2p_af = (काष्ठा brcmf_p2p_action_frame *)af_params->action_frame.data;
	अगर (p2p_af->subtype == P2P_AF_PRESENCE_RSP)
		vअगर = p2p->bss_idx[P2PAPI_BSSCFG_CONNECTION].vअगर;
	अन्यथा
		vअगर = p2p->bss_idx[P2PAPI_BSSCFG_DEVICE].vअगर;

	err = brcmf_fil_bsscfg_data_set(vअगर->अगरp, "actframe", af_params,
					माप(*af_params));
	अगर (err) अणु
		bphy_err(drvr, " sending action frame has failed\n");
		जाओ निकास;
	पूर्ण

	p2p->af_sent_channel = le32_to_cpu(af_params->channel);
	p2p->af_tx_sent_jअगरfies = jअगरfies;

	अगर (test_bit(BRCMF_P2P_STATUS_DISCOVER_LISTEN, &p2p->status) &&
	    p2p->af_sent_channel ==
	    ieee80211_frequency_to_channel(p2p->reमुख्य_on_channel.center_freq))
		p2p->रुको_क्रम_offchan_complete = false;
	अन्यथा
		p2p->रुको_क्रम_offchan_complete = true;

	brcmf_dbg(TRACE, "Waiting for %s tx completion event\n",
		  (p2p->रुको_क्रम_offchan_complete) ?
		   "off-channel" : "on-channel");

	रुको_क्रम_completion_समयout(&p2p->send_af_करोne, P2P_AF_MAX_WAIT_TIME);

	अगर (test_bit(BRCMF_P2P_STATUS_ACTION_TX_COMPLETED, &p2p->status)) अणु
		brcmf_dbg(TRACE, "TX action frame operation is success\n");
	पूर्ण अन्यथा अणु
		err = -EIO;
		brcmf_dbg(TRACE, "TX action frame operation has failed\n");
	पूर्ण
	/* clear status bit क्रम action tx */
	clear_bit(BRCMF_P2P_STATUS_ACTION_TX_COMPLETED, &p2p->status);
	clear_bit(BRCMF_P2P_STATUS_ACTION_TX_NOACK, &p2p->status);

निकास:
	वापस err;
पूर्ण


/**
 * brcmf_p2p_pub_af_tx() - खुला action frame tx routine.
 *
 * @cfg: driver निजी data क्रम cfg80211 पूर्णांकerface.
 * @af_params: action frame data/info.
 * @config_af_params: configuration data क्रम action frame.
 *
 * routine which transmits ation frame खुला type.
 */
अटल s32 brcmf_p2p_pub_af_tx(काष्ठा brcmf_cfg80211_info *cfg,
			       काष्ठा brcmf_fil_af_params_le *af_params,
			       काष्ठा brcmf_config_af_params *config_af_params)
अणु
	काष्ठा brcmf_p2p_info *p2p = &cfg->p2p;
	काष्ठा brcmf_pub *drvr = cfg->pub;
	काष्ठा brcmf_fil_action_frame_le *action_frame;
	काष्ठा brcmf_p2p_pub_act_frame *act_frm;
	s32 err = 0;
	u16 ie_len;

	action_frame = &af_params->action_frame;
	act_frm = (काष्ठा brcmf_p2p_pub_act_frame *)(action_frame->data);

	config_af_params->extra_listen = true;

	चयन (act_frm->subtype) अणु
	हाल P2P_PAF_GON_REQ:
		brcmf_dbg(TRACE, "P2P: GO_NEG_PHASE status set\n");
		set_bit(BRCMF_P2P_STATUS_GO_NEG_PHASE, &p2p->status);
		config_af_params->mpc_onoff = 0;
		config_af_params->search_channel = true;
		p2p->next_af_subtype = act_frm->subtype + 1;
		p2p->gon_req_action = true;
		/* increase dwell समय to रुको क्रम RESP frame */
		af_params->dwell_समय = cpu_to_le32(P2P_AF_MED_DWELL_TIME);
		अवरोध;
	हाल P2P_PAF_GON_RSP:
		p2p->next_af_subtype = act_frm->subtype + 1;
		/* increase dwell समय to रुको क्रम CONF frame */
		af_params->dwell_समय = cpu_to_le32(P2P_AF_MED_DWELL_TIME);
		अवरोध;
	हाल P2P_PAF_GON_CONF:
		/* If we reached till GO Neg confirmation reset the filter */
		brcmf_dbg(TRACE, "P2P: GO_NEG_PHASE status cleared\n");
		clear_bit(BRCMF_P2P_STATUS_GO_NEG_PHASE, &p2p->status);
		/* turn on mpc again अगर go nego is करोne */
		config_af_params->mpc_onoff = 1;
		/* minimize dwell समय */
		af_params->dwell_समय = cpu_to_le32(P2P_AF_MIN_DWELL_TIME);
		config_af_params->extra_listen = false;
		अवरोध;
	हाल P2P_PAF_INVITE_REQ:
		config_af_params->search_channel = true;
		p2p->next_af_subtype = act_frm->subtype + 1;
		/* increase dwell समय */
		af_params->dwell_समय = cpu_to_le32(P2P_AF_MED_DWELL_TIME);
		अवरोध;
	हाल P2P_PAF_INVITE_RSP:
		/* minimize dwell समय */
		af_params->dwell_समय = cpu_to_le32(P2P_AF_MIN_DWELL_TIME);
		config_af_params->extra_listen = false;
		अवरोध;
	हाल P2P_PAF_DEVDIS_REQ:
		config_af_params->search_channel = true;
		p2p->next_af_subtype = act_frm->subtype + 1;
		/* maximize dwell समय to रुको क्रम RESP frame */
		af_params->dwell_समय = cpu_to_le32(P2P_AF_LONG_DWELL_TIME);
		अवरोध;
	हाल P2P_PAF_DEVDIS_RSP:
		/* minimize dwell समय */
		af_params->dwell_समय = cpu_to_le32(P2P_AF_MIN_DWELL_TIME);
		config_af_params->extra_listen = false;
		अवरोध;
	हाल P2P_PAF_PROVDIS_REQ:
		ie_len = le16_to_cpu(action_frame->len) -
			 दुरत्व(काष्ठा brcmf_p2p_pub_act_frame, elts);
		अगर (cfg80211_get_p2p_attr(&act_frm->elts[0], ie_len,
					  IEEE80211_P2P_ATTR_GROUP_ID,
					  शून्य, 0) < 0)
			config_af_params->search_channel = true;
		config_af_params->mpc_onoff = 0;
		p2p->next_af_subtype = act_frm->subtype + 1;
		/* increase dwell समय to रुको क्रम RESP frame */
		af_params->dwell_समय = cpu_to_le32(P2P_AF_MED_DWELL_TIME);
		अवरोध;
	हाल P2P_PAF_PROVDIS_RSP:
		/* wpa_supplicant send go nego req right after prov disc */
		p2p->next_af_subtype = P2P_PAF_GON_REQ;
		/* increase dwell समय to MED level */
		af_params->dwell_समय = cpu_to_le32(P2P_AF_MED_DWELL_TIME);
		config_af_params->extra_listen = false;
		अवरोध;
	शेष:
		bphy_err(drvr, "Unknown p2p pub act frame subtype: %d\n",
			 act_frm->subtype);
		err = -EINVAL;
	पूर्ण
	वापस err;
पूर्ण

अटल bool brcmf_p2p_check_dwell_overflow(u32 requested_dwell,
					   अचिन्हित दीर्घ dwell_jअगरfies)
अणु
	अगर ((requested_dwell & CUSTOM_RETRY_MASK) &&
	    (jअगरfies_to_msecs(jअगरfies - dwell_jअगरfies) >
	    (requested_dwell & ~CUSTOM_RETRY_MASK))) अणु
		brcmf_err("Action frame TX retry time over dwell time!\n");
		वापस true;
	पूर्ण
	वापस false;
पूर्ण
/**
 * brcmf_p2p_send_action_frame() - send action frame .
 *
 * @cfg: driver निजी data क्रम cfg80211 पूर्णांकerface.
 * @ndev: net device to transmit on.
 * @af_params: configuration data क्रम action frame.
 */
bool brcmf_p2p_send_action_frame(काष्ठा brcmf_cfg80211_info *cfg,
				 काष्ठा net_device *ndev,
				 काष्ठा brcmf_fil_af_params_le *af_params)
अणु
	काष्ठा brcmf_p2p_info *p2p = &cfg->p2p;
	काष्ठा brcmf_अगर *अगरp = netdev_priv(ndev);
	काष्ठा brcmf_fil_action_frame_le *action_frame;
	काष्ठा brcmf_config_af_params config_af_params;
	काष्ठा afx_hdl *afx_hdl = &p2p->afx_hdl;
	काष्ठा brcmf_pub *drvr = cfg->pub;
	u16 action_frame_len;
	bool ack = false;
	u8 category;
	u8 action;
	s32 tx_retry;
	s32 extra_listen_समय;
	uपूर्णांक delta_ms;
	अचिन्हित दीर्घ dwell_jअगरfies = 0;
	bool dwell_overflow = false;

	u32 requested_dwell = le32_to_cpu(af_params->dwell_समय);
	action_frame = &af_params->action_frame;
	action_frame_len = le16_to_cpu(action_frame->len);

	brcmf_p2p_prपूर्णांक_actframe(true, action_frame->data, action_frame_len);

	/* Add the शेष dwell समय. Dwell समय to stay off-channel */
	/* to रुको क्रम a response action frame after transmitting an  */
	/* GO Negotiation action frame                                */
	af_params->dwell_समय = cpu_to_le32(P2P_AF_DWELL_TIME);

	category = action_frame->data[DOT11_ACTION_CAT_OFF];
	action = action_frame->data[DOT11_ACTION_ACT_OFF];

	/* initialize variables */
	p2p->next_af_subtype = P2P_PAF_SUBTYPE_INVALID;
	p2p->gon_req_action = false;

	/* config parameters */
	config_af_params.mpc_onoff = -1;
	config_af_params.search_channel = false;
	config_af_params.extra_listen = false;

	अगर (brcmf_p2p_is_pub_action(action_frame->data, action_frame_len)) अणु
		/* p2p खुला action frame process */
		अगर (brcmf_p2p_pub_af_tx(cfg, af_params, &config_af_params)) अणु
			/* Just send unknown subtype frame with */
			/* शेष parameters.                  */
			bphy_err(drvr, "P2P Public action frame, unknown subtype.\n");
		पूर्ण
	पूर्ण अन्यथा अगर (brcmf_p2p_is_gas_action(action_frame->data,
					   action_frame_len)) अणु
		/* service discovery process */
		अगर (action == P2PSD_ACTION_ID_GAS_IREQ ||
		    action == P2PSD_ACTION_ID_GAS_CREQ) अणु
			/* configure service discovery query frame */
			config_af_params.search_channel = true;

			/* save next af suptype to cancel */
			/* reमुख्यing dwell समय           */
			p2p->next_af_subtype = action + 1;

			af_params->dwell_समय =
				cpu_to_le32(P2P_AF_MED_DWELL_TIME);
		पूर्ण अन्यथा अगर (action == P2PSD_ACTION_ID_GAS_IRESP ||
			   action == P2PSD_ACTION_ID_GAS_CRESP) अणु
			/* configure service discovery response frame */
			af_params->dwell_समय =
				cpu_to_le32(P2P_AF_MIN_DWELL_TIME);
		पूर्ण अन्यथा अणु
			bphy_err(drvr, "Unknown action type: %d\n", action);
			जाओ निकास;
		पूर्ण
	पूर्ण अन्यथा अगर (brcmf_p2p_is_p2p_action(action_frame->data,
					   action_frame_len)) अणु
		/* करो not configure anything. it will be */
		/* sent with a शेष configuration     */
	पूर्ण अन्यथा अणु
		bphy_err(drvr, "Unknown Frame: category 0x%x, action 0x%x\n",
			 category, action);
		वापस false;
	पूर्ण

	/* अगर connecting on primary अगरace, sleep क्रम a जबतक beक्रमe sending
	 * af tx क्रम VSDB
	 */
	अगर (test_bit(BRCMF_VIF_STATUS_CONNECTING,
		     &p2p->bss_idx[P2PAPI_BSSCFG_PRIMARY].vअगर->sme_state))
		msleep(50);

	/* अगर scan is ongoing, पात current scan. */
	अगर (test_bit(BRCMF_SCAN_STATUS_BUSY, &cfg->scan_status))
		brcmf_पात_scanning(cfg);

	स_नकल(afx_hdl->tx_dst_addr, action_frame->da, ETH_ALEN);

	/* To make sure to send successfully action frame, turn off mpc */
	अगर (config_af_params.mpc_onoff == 0)
		brcmf_set_mpc(अगरp, 0);

	/* set status and destination address beक्रमe sending af */
	अगर (p2p->next_af_subtype != P2P_PAF_SUBTYPE_INVALID) अणु
		/* set status to cancel the reमुख्यed dwell समय in rx process */
		set_bit(BRCMF_P2P_STATUS_WAITING_NEXT_ACT_FRAME, &p2p->status);
	पूर्ण

	p2p->af_sent_channel = 0;
	set_bit(BRCMF_P2P_STATUS_SENDING_ACT_FRAME, &p2p->status);
	/* validate channel and p2p ies */
	अगर (config_af_params.search_channel &&
	    IS_P2P_SOCIAL_CHANNEL(le32_to_cpu(af_params->channel)) &&
	    p2p->bss_idx[P2PAPI_BSSCFG_DEVICE].vअगर->saved_ie.probe_req_ie_len) अणु
		afx_hdl = &p2p->afx_hdl;
		afx_hdl->peer_listen_chan = le32_to_cpu(af_params->channel);

		अगर (brcmf_p2p_af_searching_channel(p2p) ==
							P2P_INVALID_CHANNEL) अणु
			bphy_err(drvr, "Couldn't find peer's channel.\n");
			जाओ निकास;
		पूर्ण

		/* Abort scan even क्रम VSDB scenarios. Scan माला_लो पातed in
		 * firmware but after the check of piggyback algorithm. To take
		 * care of current piggback algo, lets पात the scan here
		 * itself.
		 */
		brcmf_notअगरy_escan_complete(cfg, अगरp, true, true);

		/* update channel */
		af_params->channel = cpu_to_le32(afx_hdl->peer_chan);
	पूर्ण
	dwell_jअगरfies = jअगरfies;
	dwell_overflow = brcmf_p2p_check_dwell_overflow(requested_dwell,
							dwell_jअगरfies);

	tx_retry = 0;
	जबतक (!p2p->block_gon_req_tx &&
	       (!ack) && (tx_retry < P2P_AF_TX_MAX_RETRY) &&
		!dwell_overflow) अणु
		अगर (af_params->channel)
			msleep(P2P_AF_RETRY_DELAY_TIME);

		ack = !brcmf_p2p_tx_action_frame(p2p, af_params);
		tx_retry++;
		dwell_overflow = brcmf_p2p_check_dwell_overflow(requested_dwell,
								dwell_jअगरfies);
	पूर्ण
	अगर (!ack) अणु
		bphy_err(drvr, "Failed to send Action Frame(retry %d)\n",
			 tx_retry);
		clear_bit(BRCMF_P2P_STATUS_GO_NEG_PHASE, &p2p->status);
	पूर्ण

निकास:
	clear_bit(BRCMF_P2P_STATUS_SENDING_ACT_FRAME, &p2p->status);

	/* WAR: someबार करोngle करोes not keep the dwell समय of 'actframe'.
	 * अगर we coundn't get the next action response frame and करोngle करोes
	 * not keep the dwell समय, go to listen state again to get next action
	 * response frame.
	 */
	अगर (ack && config_af_params.extra_listen && !p2p->block_gon_req_tx &&
	    test_bit(BRCMF_P2P_STATUS_WAITING_NEXT_ACT_FRAME, &p2p->status) &&
	    p2p->af_sent_channel == afx_hdl->my_listen_chan) अणु
		delta_ms = jअगरfies_to_msecs(jअगरfies - p2p->af_tx_sent_jअगरfies);
		अगर (le32_to_cpu(af_params->dwell_समय) > delta_ms)
			extra_listen_समय = le32_to_cpu(af_params->dwell_समय) -
					    delta_ms;
		अन्यथा
			extra_listen_समय = 0;
		अगर (extra_listen_समय > 50) अणु
			set_bit(BRCMF_P2P_STATUS_WAITING_NEXT_AF_LISTEN,
				&p2p->status);
			brcmf_dbg(INFO, "Wait more time! actual af time:%d, calculated extra listen:%d\n",
				  le32_to_cpu(af_params->dwell_समय),
				  extra_listen_समय);
			extra_listen_समय += 100;
			अगर (!brcmf_p2p_discover_listen(p2p,
						       p2p->af_sent_channel,
						       extra_listen_समय)) अणु
				अचिन्हित दीर्घ duration;

				extra_listen_समय += 100;
				duration = msecs_to_jअगरfies(extra_listen_समय);
				रुको_क्रम_completion_समयout(&p2p->रुको_next_af,
							    duration);
			पूर्ण
			clear_bit(BRCMF_P2P_STATUS_WAITING_NEXT_AF_LISTEN,
				  &p2p->status);
		पूर्ण
	पूर्ण

	अगर (p2p->block_gon_req_tx) अणु
		/* अगर ack is true, supplicant will रुको more समय(100ms).
		 * so we will वापस it as a success to get more समय .
		 */
		p2p->block_gon_req_tx = false;
		ack = true;
	पूर्ण

	clear_bit(BRCMF_P2P_STATUS_WAITING_NEXT_ACT_FRAME, &p2p->status);
	/* अगर all करोne, turn mpc on again */
	अगर (config_af_params.mpc_onoff == 1)
		brcmf_set_mpc(अगरp, 1);

	वापस ack;
पूर्ण

/**
 * brcmf_p2p_notअगरy_rx_mgmt_p2p_probereq() - Event handler क्रम p2p probe req.
 *
 * @अगरp: पूर्णांकerface poपूर्णांकer क्रम which event was received.
 * @e: even message.
 * @data: payload of event message (probe request).
 */
s32 brcmf_p2p_notअगरy_rx_mgmt_p2p_probereq(काष्ठा brcmf_अगर *अगरp,
					  स्थिर काष्ठा brcmf_event_msg *e,
					  व्योम *data)
अणु
	काष्ठा brcmf_cfg80211_info *cfg = अगरp->drvr->config;
	काष्ठा brcmf_p2p_info *p2p = &cfg->p2p;
	काष्ठा afx_hdl *afx_hdl = &p2p->afx_hdl;
	काष्ठा brcmf_cfg80211_vअगर *vअगर = अगरp->vअगर;
	काष्ठा brcmf_rx_mgmt_data *rxframe = (काष्ठा brcmf_rx_mgmt_data *)data;
	काष्ठा brcmu_chan ch;
	u8 *mgmt_frame;
	u32 mgmt_frame_len;
	s32 freq;
	u16 mgmt_type;

	brcmf_dbg(INFO, "Enter: event %d reason %d\n", e->event_code,
		  e->reason);

	अगर (e->datalen < माप(*rxframe)) अणु
		brcmf_dbg(SCAN, "Event data to small. Ignore\n");
		वापस 0;
	पूर्ण

	ch.chspec = be16_to_cpu(rxframe->chanspec);
	cfg->d11inf.decchspec(&ch);

	अगर (test_bit(BRCMF_P2P_STATUS_FINDING_COMMON_CHANNEL, &p2p->status) &&
	    (ether_addr_equal(afx_hdl->tx_dst_addr, e->addr))) अणु
		afx_hdl->peer_chan = ch.control_ch_num;
		brcmf_dbg(INFO, "PROBE REQUEST: Peer found, channel=%d\n",
			  afx_hdl->peer_chan);
		complete(&afx_hdl->act_frm_scan);
	पूर्ण

	/* Firmware sends us two proberesponses क्रम each idx one. At the */
	/* moment anything but bsscfgidx 0 is passed up to supplicant    */
	अगर (e->bsscfgidx == 0)
		वापस 0;

	/* Filter any P2P probe reqs arriving during the GO-NEG Phase */
	अगर (test_bit(BRCMF_P2P_STATUS_GO_NEG_PHASE, &p2p->status)) अणु
		brcmf_dbg(INFO, "Filtering P2P probe_req in GO-NEG phase\n");
		वापस 0;
	पूर्ण

	/* Check अगर wpa_supplicant has रेजिस्टरed क्रम this frame */
	brcmf_dbg(INFO, "vif->mgmt_rx_reg %04x\n", vअगर->mgmt_rx_reg);
	mgmt_type = (IEEE80211_STYPE_PROBE_REQ & IEEE80211_FCTL_STYPE) >> 4;
	अगर ((vअगर->mgmt_rx_reg & BIT(mgmt_type)) == 0)
		वापस 0;

	mgmt_frame = (u8 *)(rxframe + 1);
	mgmt_frame_len = e->datalen - माप(*rxframe);
	freq = ieee80211_channel_to_frequency(ch.control_ch_num,
					      ch.band == BRCMU_CHAN_BAND_2G ?
					      NL80211_BAND_2GHZ :
					      NL80211_BAND_5GHZ);

	cfg80211_rx_mgmt(&vअगर->wdev, freq, 0, mgmt_frame, mgmt_frame_len, 0);

	brcmf_dbg(INFO, "mgmt_frame_len (%d) , e->datalen (%d), chanspec (%04x), freq (%d)\n",
		  mgmt_frame_len, e->datalen, ch.chspec, freq);

	वापस 0;
पूर्ण


/**
 * brcmf_p2p_get_current_chanspec() - Get current operation channel.
 *
 * @p2p: P2P specअगरic data.
 * @chanspec: chanspec to be वापसed.
 */
अटल व्योम brcmf_p2p_get_current_chanspec(काष्ठा brcmf_p2p_info *p2p,
					   u16 *chanspec)
अणु
	काष्ठा brcmf_अगर *अगरp;
	u8 mac_addr[ETH_ALEN];
	काष्ठा brcmu_chan ch;
	काष्ठा brcmf_bss_info_le *bi;
	u8 *buf;

	अगरp = p2p->bss_idx[P2PAPI_BSSCFG_PRIMARY].vअगर->अगरp;

	अगर (brcmf_fil_cmd_data_get(अगरp, BRCMF_C_GET_BSSID, mac_addr,
				   ETH_ALEN) == 0) अणु
		buf = kzalloc(WL_BSS_INFO_MAX, GFP_KERNEL);
		अगर (buf != शून्य) अणु
			*(__le32 *)buf = cpu_to_le32(WL_BSS_INFO_MAX);
			अगर (brcmf_fil_cmd_data_get(अगरp, BRCMF_C_GET_BSS_INFO,
						   buf, WL_BSS_INFO_MAX) == 0) अणु
				bi = (काष्ठा brcmf_bss_info_le *)(buf + 4);
				*chanspec = le16_to_cpu(bi->chanspec);
				kमुक्त(buf);
				वापस;
			पूर्ण
			kमुक्त(buf);
		पूर्ण
	पूर्ण
	/* Use शेष channel क्रम P2P */
	ch.chnum = BRCMF_P2P_TEMP_CHAN;
	ch.bw = BRCMU_CHAN_BW_20;
	p2p->cfg->d11inf.encchspec(&ch);
	*chanspec = ch.chspec;
पूर्ण

/**
 * Change a P2P Role.
 * @cfg: driver निजी data क्रम cfg80211 पूर्णांकerface.
 * @अगर_type: पूर्णांकerface type.
 * Returns 0 अगर success.
 */
पूर्णांक brcmf_p2p_अगरchange(काष्ठा brcmf_cfg80211_info *cfg,
		       क्रमागत brcmf_fil_p2p_अगर_types अगर_type)
अणु
	काष्ठा brcmf_p2p_info *p2p = &cfg->p2p;
	काष्ठा brcmf_pub *drvr = cfg->pub;
	काष्ठा brcmf_cfg80211_vअगर *vअगर;
	काष्ठा brcmf_fil_p2p_अगर_le अगर_request;
	s32 err;
	u16 chanspec;

	brcmf_dbg(TRACE, "Enter\n");

	vअगर = p2p->bss_idx[P2PAPI_BSSCFG_PRIMARY].vअगर;
	अगर (!vअगर) अणु
		bphy_err(drvr, "vif for P2PAPI_BSSCFG_PRIMARY does not exist\n");
		वापस -EPERM;
	पूर्ण
	brcmf_notअगरy_escan_complete(cfg, vअगर->अगरp, true, true);
	vअगर = p2p->bss_idx[P2PAPI_BSSCFG_CONNECTION].vअगर;
	अगर (!vअगर) अणु
		bphy_err(drvr, "vif for P2PAPI_BSSCFG_CONNECTION does not exist\n");
		वापस -EPERM;
	पूर्ण
	brcmf_set_mpc(vअगर->अगरp, 0);

	/* In concurrency हाल, STA may be alपढ़ोy associated in a particular */
	/* channel. so retrieve the current channel of primary पूर्णांकerface and  */
	/* then start the भव पूर्णांकerface on that.                          */
	brcmf_p2p_get_current_chanspec(p2p, &chanspec);

	अगर_request.type = cpu_to_le16((u16)अगर_type);
	अगर_request.chspec = cpu_to_le16(chanspec);
	स_नकल(अगर_request.addr, p2p->conn_पूर्णांक_addr, माप(अगर_request.addr));

	brcmf_cfg80211_arm_vअगर_event(cfg, vअगर);
	err = brcmf_fil_iovar_data_set(vअगर->अगरp, "p2p_ifupd", &अगर_request,
				       माप(अगर_request));
	अगर (err) अणु
		bphy_err(drvr, "p2p_ifupd FAILED, err=%d\n", err);
		brcmf_cfg80211_arm_vअगर_event(cfg, शून्य);
		वापस err;
	पूर्ण
	err = brcmf_cfg80211_रुको_vअगर_event(cfg, BRCMF_E_IF_CHANGE,
					    BRCMF_VIF_EVENT_TIMEOUT);
	brcmf_cfg80211_arm_vअगर_event(cfg, शून्य);
	अगर (!err)  अणु
		bphy_err(drvr, "No BRCMF_E_IF_CHANGE event received\n");
		वापस -EIO;
	पूर्ण

	err = brcmf_fil_cmd_पूर्णांक_set(vअगर->अगरp, BRCMF_C_SET_SCB_TIMEOUT,
				    BRCMF_SCB_TIMEOUT_VALUE);

	वापस err;
पूर्ण

अटल पूर्णांक brcmf_p2p_request_p2p_अगर(काष्ठा brcmf_p2p_info *p2p,
				    काष्ठा brcmf_अगर *अगरp, u8 ea[ETH_ALEN],
				    क्रमागत brcmf_fil_p2p_अगर_types अगरtype)
अणु
	काष्ठा brcmf_fil_p2p_अगर_le अगर_request;
	पूर्णांक err;
	u16 chanspec;

	/* we need a शेष channel */
	brcmf_p2p_get_current_chanspec(p2p, &chanspec);

	/* fill the firmware request */
	स_नकल(अगर_request.addr, ea, ETH_ALEN);
	अगर_request.type = cpu_to_le16((u16)अगरtype);
	अगर_request.chspec = cpu_to_le16(chanspec);

	err = brcmf_fil_iovar_data_set(अगरp, "p2p_ifadd", &अगर_request,
				       माप(अगर_request));

	वापस err;
पूर्ण

अटल पूर्णांक brcmf_p2p_disable_p2p_अगर(काष्ठा brcmf_cfg80211_vअगर *vअगर)
अणु
	काष्ठा brcmf_cfg80211_info *cfg = wdev_to_cfg(&vअगर->wdev);
	काष्ठा net_device *pri_ndev = cfg_to_ndev(cfg);
	काष्ठा brcmf_अगर *अगरp = netdev_priv(pri_ndev);
	u8 *addr = vअगर->wdev.netdev->dev_addr;

	वापस brcmf_fil_iovar_data_set(अगरp, "p2p_ifdis", addr, ETH_ALEN);
पूर्ण

अटल पूर्णांक brcmf_p2p_release_p2p_अगर(काष्ठा brcmf_cfg80211_vअगर *vअगर)
अणु
	काष्ठा brcmf_cfg80211_info *cfg = wdev_to_cfg(&vअगर->wdev);
	काष्ठा net_device *pri_ndev = cfg_to_ndev(cfg);
	काष्ठा brcmf_अगर *अगरp = netdev_priv(pri_ndev);
	u8 *addr = vअगर->wdev.netdev->dev_addr;

	वापस brcmf_fil_iovar_data_set(अगरp, "p2p_ifdel", addr, ETH_ALEN);
पूर्ण

/**
 * brcmf_p2p_create_p2pdev() - create a P2P_DEVICE भव पूर्णांकerface.
 *
 * @p2p: P2P specअगरic data.
 * @wiphy: wiphy device of new पूर्णांकerface.
 * @addr: mac address क्रम this new पूर्णांकerface.
 */
अटल काष्ठा wireless_dev *brcmf_p2p_create_p2pdev(काष्ठा brcmf_p2p_info *p2p,
						    काष्ठा wiphy *wiphy,
						    u8 *addr)
अणु
	काष्ठा brcmf_pub *drvr = p2p->cfg->pub;
	काष्ठा brcmf_cfg80211_vअगर *p2p_vअगर;
	काष्ठा brcmf_अगर *p2p_अगरp;
	काष्ठा brcmf_अगर *pri_अगरp;
	पूर्णांक err;
	u32 bsscfgidx;

	अगर (p2p->bss_idx[P2PAPI_BSSCFG_DEVICE].vअगर)
		वापस ERR_PTR(-ENOSPC);

	p2p_vअगर = brcmf_alloc_vअगर(p2p->cfg, NL80211_IFTYPE_P2P_DEVICE);
	अगर (IS_ERR(p2p_vअगर)) अणु
		bphy_err(drvr, "could not create discovery vif\n");
		वापस (काष्ठा wireless_dev *)p2p_vअगर;
	पूर्ण

	pri_अगरp = p2p->bss_idx[P2PAPI_BSSCFG_PRIMARY].vअगर->अगरp;

	/* firmware requires unique mac address क्रम p2pdev पूर्णांकerface */
	अगर (addr && ether_addr_equal(addr, pri_अगरp->mac_addr)) अणु
		bphy_err(drvr, "discovery vif must be different from primary interface\n");
		err = -EINVAL;
		जाओ fail;
	पूर्ण

	brcmf_p2p_generate_bss_mac(p2p, addr);
	brcmf_p2p_set_firmware(pri_अगरp, p2p->dev_addr);

	brcmf_cfg80211_arm_vअगर_event(p2p->cfg, p2p_vअगर);
	brcmf_fweh_p2pdev_setup(pri_अगरp, true);

	/* Initialize P2P Discovery in the firmware */
	err = brcmf_fil_iovar_पूर्णांक_set(pri_अगरp, "p2p_disc", 1);
	अगर (err < 0) अणु
		bphy_err(drvr, "set p2p_disc error\n");
		brcmf_fweh_p2pdev_setup(pri_अगरp, false);
		brcmf_cfg80211_arm_vअगर_event(p2p->cfg, शून्य);
		जाओ fail;
	पूर्ण

	/* रुको क्रम firmware event */
	err = brcmf_cfg80211_रुको_vअगर_event(p2p->cfg, BRCMF_E_IF_ADD,
					    BRCMF_VIF_EVENT_TIMEOUT);
	brcmf_cfg80211_arm_vअगर_event(p2p->cfg, शून्य);
	brcmf_fweh_p2pdev_setup(pri_अगरp, false);
	अगर (!err) अणु
		bphy_err(drvr, "timeout occurred\n");
		err = -EIO;
		जाओ fail;
	पूर्ण

	/* discovery पूर्णांकerface created */
	p2p_अगरp = p2p_vअगर->अगरp;
	p2p->bss_idx[P2PAPI_BSSCFG_DEVICE].vअगर = p2p_vअगर;
	स_नकल(p2p_अगरp->mac_addr, p2p->dev_addr, ETH_ALEN);
	स_नकल(&p2p_vअगर->wdev.address, p2p->dev_addr, माप(p2p->dev_addr));

	/* verअगरy bsscfg index क्रम P2P discovery */
	err = brcmf_fil_iovar_पूर्णांक_get(pri_अगरp, "p2p_dev", &bsscfgidx);
	अगर (err < 0) अणु
		bphy_err(drvr, "retrieving discover bsscfg index failed\n");
		जाओ fail;
	पूर्ण

	WARN_ON(p2p_अगरp->bsscfgidx != bsscfgidx);

	init_completion(&p2p->send_af_करोne);
	INIT_WORK(&p2p->afx_hdl.afx_work, brcmf_p2p_afx_handler);
	init_completion(&p2p->afx_hdl.act_frm_scan);
	init_completion(&p2p->रुको_next_af);

	वापस &p2p_vअगर->wdev;

fail:
	brcmf_मुक्त_vअगर(p2p_vअगर);
	वापस ERR_PTR(err);
पूर्ण

अटल पूर्णांक brcmf_p2p_get_conn_idx(काष्ठा brcmf_cfg80211_info *cfg)
अणु
	पूर्णांक i;
	काष्ठा brcmf_अगर *अगरp = netdev_priv(cfg_to_ndev(cfg));

	अगर (!अगरp)
		वापस -ENODEV;

	क्रम (i = P2PAPI_BSSCFG_CONNECTION; i < P2PAPI_BSSCFG_MAX; i++) अणु
		अगर (!cfg->p2p.bss_idx[i].vअगर) अणु
			अगर (i == P2PAPI_BSSCFG_CONNECTION2 &&
			    !(brcmf_feat_is_enabled(अगरp, BRCMF_FEAT_RSDB))) अणु
				brcmf_err("Multi p2p not supported");
				वापस -EIO;
			पूर्ण
			वापस i;
		पूर्ण
	पूर्ण
	वापस -EIO;
पूर्ण

/**
 * brcmf_p2p_add_vअगर() - create a new P2P भव पूर्णांकerface.
 *
 * @wiphy: wiphy device of new पूर्णांकerface.
 * @name: name of the new पूर्णांकerface.
 * @name_assign_type: origin of the पूर्णांकerface name
 * @type: nl80211 पूर्णांकerface type.
 * @params: contains mac address क्रम P2P device.
 */
काष्ठा wireless_dev *brcmf_p2p_add_vअगर(काष्ठा wiphy *wiphy, स्थिर अक्षर *name,
				       अचिन्हित अक्षर name_assign_type,
				       क्रमागत nl80211_अगरtype type,
				       काष्ठा vअगर_params *params)
अणु
	काष्ठा brcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	काष्ठा brcmf_अगर *अगरp = netdev_priv(cfg_to_ndev(cfg));
	काष्ठा brcmf_pub *drvr = cfg->pub;
	काष्ठा brcmf_cfg80211_vअगर *vअगर;
	क्रमागत brcmf_fil_p2p_अगर_types अगरtype;
	पूर्णांक err = 0;
	पूर्णांक connidx;
	u8 *p2p_पूर्णांकf_addr;

	अगर (brcmf_cfg80211_vअगर_event_armed(cfg))
		वापस ERR_PTR(-EBUSY);

	brcmf_dbg(INFO, "adding vif \"%s\" (type=%d)\n", name, type);

	चयन (type) अणु
	हाल NL80211_IFTYPE_P2P_CLIENT:
		अगरtype = BRCMF_FIL_P2P_IF_CLIENT;
		अवरोध;
	हाल NL80211_IFTYPE_P2P_GO:
		अगरtype = BRCMF_FIL_P2P_IF_GO;
		अवरोध;
	हाल NL80211_IFTYPE_P2P_DEVICE:
		वापस brcmf_p2p_create_p2pdev(&cfg->p2p, wiphy,
					       params->macaddr);
	शेष:
		वापस ERR_PTR(-EOPNOTSUPP);
	पूर्ण

	vअगर = brcmf_alloc_vअगर(cfg, type);
	अगर (IS_ERR(vअगर))
		वापस (काष्ठा wireless_dev *)vअगर;
	brcmf_cfg80211_arm_vअगर_event(cfg, vअगर);

	connidx = brcmf_p2p_get_conn_idx(cfg);

	अगर (connidx == P2PAPI_BSSCFG_CONNECTION)
		p2p_पूर्णांकf_addr = cfg->p2p.conn_पूर्णांक_addr;
	अन्यथा अगर (connidx == P2PAPI_BSSCFG_CONNECTION2)
		p2p_पूर्णांकf_addr = cfg->p2p.conn2_पूर्णांक_addr;
	अन्यथा
		err = -EINVAL;

	अगर (!err)
		err =  brcmf_p2p_request_p2p_अगर(&cfg->p2p, अगरp,
						p2p_पूर्णांकf_addr, अगरtype);

	अगर (err) अणु
		brcmf_err("request p2p interface failed\n");
		brcmf_cfg80211_arm_vअगर_event(cfg, शून्य);
		जाओ fail;
	पूर्ण

	/* रुको क्रम firmware event */
	err = brcmf_cfg80211_रुको_vअगर_event(cfg, BRCMF_E_IF_ADD,
					    BRCMF_VIF_EVENT_TIMEOUT);
	brcmf_cfg80211_arm_vअगर_event(cfg, शून्य);
	अगर (!err) अणु
		bphy_err(drvr, "timeout occurred\n");
		err = -EIO;
		जाओ fail;
	पूर्ण

	/* पूर्णांकerface created in firmware */
	अगरp = vअगर->अगरp;
	अगर (!अगरp) अणु
		bphy_err(drvr, "no if pointer provided\n");
		err = -ENOENT;
		जाओ fail;
	पूर्ण

	म_नकलन(अगरp->ndev->name, name, माप(अगरp->ndev->name) - 1);
	अगरp->ndev->name_assign_type = name_assign_type;
	err = brcmf_net_attach(अगरp, true);
	अगर (err) अणु
		bphy_err(drvr, "Registering netdevice failed\n");
		मुक्त_netdev(अगरp->ndev);
		जाओ fail;
	पूर्ण

	cfg->p2p.bss_idx[connidx].vअगर = vअगर;
	/* Disable firmware roaming क्रम P2P पूर्णांकerface  */
	brcmf_fil_iovar_पूर्णांक_set(अगरp, "roam_off", 1);
	अगर (अगरtype == BRCMF_FIL_P2P_IF_GO) अणु
		/* set station समयout क्रम p2p */
		brcmf_fil_cmd_पूर्णांक_set(अगरp, BRCMF_C_SET_SCB_TIMEOUT,
				      BRCMF_SCB_TIMEOUT_VALUE);
	पूर्ण
	वापस &अगरp->vअगर->wdev;

fail:
	brcmf_मुक्त_vअगर(vअगर);
	वापस ERR_PTR(err);
पूर्ण

/**
 * brcmf_p2p_del_vअगर() - delete a P2P भव पूर्णांकerface.
 *
 * @wiphy: wiphy device of पूर्णांकerface.
 * @wdev: wireless device of पूर्णांकerface.
 */
पूर्णांक brcmf_p2p_del_vअगर(काष्ठा wiphy *wiphy, काष्ठा wireless_dev *wdev)
अणु
	काष्ठा brcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	काष्ठा brcmf_p2p_info *p2p = &cfg->p2p;
	काष्ठा brcmf_cfg80211_vअगर *vअगर;
	क्रमागत nl80211_अगरtype अगरtype;
	bool रुको_क्रम_disable = false;
	पूर्णांक err;

	brcmf_dbg(TRACE, "delete P2P vif\n");
	vअगर = container_of(wdev, काष्ठा brcmf_cfg80211_vअगर, wdev);

	अगरtype = vअगर->wdev.अगरtype;
	brcmf_cfg80211_arm_vअगर_event(cfg, vअगर);
	चयन (अगरtype) अणु
	हाल NL80211_IFTYPE_P2P_CLIENT:
		अगर (test_bit(BRCMF_VIF_STATUS_DISCONNECTING, &vअगर->sme_state))
			रुको_क्रम_disable = true;
		अवरोध;

	हाल NL80211_IFTYPE_P2P_GO:
		अगर (!brcmf_p2p_disable_p2p_अगर(vअगर))
			रुको_क्रम_disable = true;
		अवरोध;

	हाल NL80211_IFTYPE_P2P_DEVICE:
		अगर (!p2p->bss_idx[P2PAPI_BSSCFG_DEVICE].vअगर)
			वापस 0;
		brcmf_p2p_cancel_reमुख्य_on_channel(vअगर->अगरp);
		brcmf_p2p_deinit_discovery(p2p);
		अवरोध;

	शेष:
		वापस -ENOTSUPP;
	पूर्ण

	clear_bit(BRCMF_P2P_STATUS_GO_NEG_PHASE, &p2p->status);
	brcmf_dbg(INFO, "P2P: GO_NEG_PHASE status cleared\n");

	अगर (रुको_क्रम_disable)
		रुको_क्रम_completion_समयout(&cfg->vअगर_disabled,
					    BRCMF_P2P_DISABLE_TIMEOUT);

	err = 0;
	अगर (अगरtype != NL80211_IFTYPE_P2P_DEVICE) अणु
		brcmf_vअगर_clear_mgmt_ies(vअगर);
		err = brcmf_p2p_release_p2p_अगर(vअगर);
	पूर्ण
	अगर (!err) अणु
		/* रुको क्रम firmware event */
		err = brcmf_cfg80211_रुको_vअगर_event(cfg, BRCMF_E_IF_DEL,
						    BRCMF_VIF_EVENT_TIMEOUT);
		अगर (!err)
			err = -EIO;
		अन्यथा
			err = 0;
	पूर्ण
	brcmf_हटाओ_पूर्णांकerface(vअगर->अगरp, true);

	brcmf_cfg80211_arm_vअगर_event(cfg, शून्य);
	अगर (अगरtype != NL80211_IFTYPE_P2P_DEVICE)
		p2p->bss_idx[P2PAPI_BSSCFG_CONNECTION].vअगर = शून्य;

	वापस err;
पूर्ण

व्योम brcmf_p2p_अगरp_हटाओd(काष्ठा brcmf_अगर *अगरp, bool locked)
अणु
	काष्ठा brcmf_cfg80211_info *cfg;
	काष्ठा brcmf_cfg80211_vअगर *vअगर;

	brcmf_dbg(INFO, "P2P: device interface removed\n");
	vअगर = अगरp->vअगर;
	cfg = wdev_to_cfg(&vअगर->wdev);
	cfg->p2p.bss_idx[P2PAPI_BSSCFG_DEVICE].vअगर = शून्य;
	अगर (!locked) अणु
		rtnl_lock();
		wiphy_lock(cfg->wiphy);
		cfg80211_unरेजिस्टर_wdev(&vअगर->wdev);
		wiphy_unlock(cfg->wiphy);
		rtnl_unlock();
	पूर्ण अन्यथा अणु
		cfg80211_unरेजिस्टर_wdev(&vअगर->wdev);
	पूर्ण
	brcmf_मुक्त_vअगर(vअगर);
पूर्ण

पूर्णांक brcmf_p2p_start_device(काष्ठा wiphy *wiphy, काष्ठा wireless_dev *wdev)
अणु
	काष्ठा brcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	काष्ठा brcmf_p2p_info *p2p = &cfg->p2p;
	काष्ठा brcmf_cfg80211_vअगर *vअगर;
	पूर्णांक err;

	vअगर = container_of(wdev, काष्ठा brcmf_cfg80211_vअगर, wdev);
	mutex_lock(&cfg->usr_sync);
	err = brcmf_p2p_enable_discovery(p2p);
	अगर (!err)
		set_bit(BRCMF_VIF_STATUS_READY, &vअगर->sme_state);
	mutex_unlock(&cfg->usr_sync);
	वापस err;
पूर्ण

व्योम brcmf_p2p_stop_device(काष्ठा wiphy *wiphy, काष्ठा wireless_dev *wdev)
अणु
	काष्ठा brcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	काष्ठा brcmf_p2p_info *p2p = &cfg->p2p;
	काष्ठा brcmf_cfg80211_vअगर *vअगर;

	vअगर = container_of(wdev, काष्ठा brcmf_cfg80211_vअगर, wdev);
	/* This call can be result of the unरेजिस्टर_wdev call. In that हाल
	 * we करोnt want to करो anything anymore. Just वापस. The config vअगर
	 * will have been cleared at this poपूर्णांक.
	 */
	अगर (p2p->bss_idx[P2PAPI_BSSCFG_DEVICE].vअगर == vअगर) अणु
		mutex_lock(&cfg->usr_sync);
		/* Set the discovery state to SCAN */
		(व्योम)brcmf_p2p_set_discover_state(vअगर->अगरp,
						   WL_P2P_DISC_ST_SCAN, 0, 0);
		brcmf_पात_scanning(cfg);
		clear_bit(BRCMF_VIF_STATUS_READY, &vअगर->sme_state);
		mutex_unlock(&cfg->usr_sync);
	पूर्ण
पूर्ण

/**
 * brcmf_p2p_attach() - attach क्रम P2P.
 *
 * @cfg: driver निजी data क्रम cfg80211 पूर्णांकerface.
 * @p2pdev_क्रमced: create p2p device पूर्णांकerface at attach.
 */
s32 brcmf_p2p_attach(काष्ठा brcmf_cfg80211_info *cfg, bool p2pdev_क्रमced)
अणु
	काष्ठा brcmf_pub *drvr = cfg->pub;
	काष्ठा brcmf_p2p_info *p2p;
	काष्ठा brcmf_अगर *pri_अगरp;
	s32 err = 0;
	व्योम *err_ptr;

	p2p = &cfg->p2p;
	p2p->cfg = cfg;

	pri_अगरp = brcmf_get_अगरp(cfg->pub, 0);
	p2p->bss_idx[P2PAPI_BSSCFG_PRIMARY].vअगर = pri_अगरp->vअगर;

	अगर (p2pdev_क्रमced) अणु
		err_ptr = brcmf_p2p_create_p2pdev(p2p, शून्य, शून्य);
		अगर (IS_ERR(err_ptr)) अणु
			bphy_err(drvr, "P2P device creation failed.\n");
			err = PTR_ERR(err_ptr);
		पूर्ण
	पूर्ण अन्यथा अणु
		p2p->p2pdev_dynamically = true;
	पूर्ण
	वापस err;
पूर्ण

/**
 * brcmf_p2p_detach() - detach P2P.
 *
 * @p2p: P2P specअगरic data.
 */
व्योम brcmf_p2p_detach(काष्ठा brcmf_p2p_info *p2p)
अणु
	काष्ठा brcmf_cfg80211_vअगर *vअगर;

	vअगर = p2p->bss_idx[P2PAPI_BSSCFG_DEVICE].vअगर;
	अगर (vअगर != शून्य) अणु
		brcmf_p2p_cancel_reमुख्य_on_channel(vअगर->अगरp);
		brcmf_p2p_deinit_discovery(p2p);
		brcmf_हटाओ_पूर्णांकerface(vअगर->अगरp, false);
	पूर्ण
	/* just set it all to zero */
	स_रखो(p2p, 0, माप(*p2p));
पूर्ण

