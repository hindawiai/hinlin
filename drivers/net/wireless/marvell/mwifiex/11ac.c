<शैली गुरु>
/*
 * NXP Wireless LAN device driver: 802.11ac
 *
 * Copyright 2011-2020 NXP
 *
 * This software file (the "File") is distributed by NXP
 * under the terms of the GNU General Public License Version 2, June 1991
 * (the "License").  You may use, redistribute and/or modअगरy this File in
 * accordance with the terms and conditions of the License, a copy of which
 * is available by writing to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fअगरth Floor, Boston, MA 02110-1301 USA or on the
 * worldwide web at http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt.
 *
 * THE खाता IS DISTRIBUTED AS-IS, WITHOUT WARRANTY OF ANY KIND, AND THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE
 * ARE EXPRESSLY DISCLAIMED.  The License provides additional details about
 * this warranty disclaimer.
 */

#समावेश "decl.h"
#समावेश "ioctl.h"
#समावेश "fw.h"
#समावेश "main.h"
#समावेश "11ac.h"

/* Tables of the MCS map to the highest data rate (in Mbps) supported
 * क्रम दीर्घ GI.
 */
अटल स्थिर u16 max_rate_lgi_80MHZ[8][3] = अणु
	अणु0x124, 0x15F, 0x186पूर्ण,	/* NSS = 1 */
	अणु0x249, 0x2BE, 0x30Cपूर्ण,  /* NSS = 2 */
	अणु0x36D, 0x41D, 0x492पूर्ण,  /* NSS = 3 */
	अणु0x492, 0x57C, 0x618पूर्ण,  /* NSS = 4 */
	अणु0x5B6, 0x6DB, 0x79Eपूर्ण,  /* NSS = 5 */
	अणु0x6DB, 0x83A, 0x0पूर्ण,    /* NSS = 6 */
	अणु0x7FF, 0x999, 0xAAAपूर्ण,  /* NSS = 7 */
	अणु0x924, 0xAF8, 0xC30पूर्ण   /* NSS = 8 */
पूर्ण;

अटल स्थिर u16 max_rate_lgi_160MHZ[8][3] = अणु
	अणु0x249, 0x2BE, 0x30Cपूर्ण,   /* NSS = 1 */
	अणु0x492, 0x57C, 0x618पूर्ण,   /* NSS = 2 */
	अणु0x6DB, 0x83A, 0x0पूर्ण,     /* NSS = 3 */
	अणु0x924, 0xAF8, 0xC30पूर्ण,   /* NSS = 4 */
	अणु0xB6D, 0xDB6, 0xF3Cपूर्ण,   /* NSS = 5 */
	अणु0xDB6, 0x1074, 0x1248पूर्ण, /* NSS = 6 */
	अणु0xFFF, 0x1332, 0x1554पूर्ण, /* NSS = 7 */
	अणु0x1248, 0x15F0, 0x1860पूर्ण /* NSS = 8 */
पूर्ण;

/* This function converts the 2-bit MCS map to the highest दीर्घ GI
 * VHT data rate.
 */
अटल u16
mwअगरiex_convert_mcsmap_to_maxrate(काष्ठा mwअगरiex_निजी *priv,
				  u8 bands, u16 mcs_map)
अणु
	u8 i, nss, mcs;
	u16 max_rate = 0;
	u32 usr_vht_cap_info = 0;
	काष्ठा mwअगरiex_adapter *adapter = priv->adapter;

	अगर (bands & BAND_AAC)
		usr_vht_cap_info = adapter->usr_करोt_11ac_dev_cap_a;
	अन्यथा
		usr_vht_cap_info = adapter->usr_करोt_11ac_dev_cap_bg;

	/* find the max NSS supported */
	nss = 1;
	क्रम (i = 1; i <= 8; i++) अणु
		mcs = GET_VHTNSSMCS(mcs_map, i);
		अगर (mcs < IEEE80211_VHT_MCS_NOT_SUPPORTED)
			nss = i;
	पूर्ण
	mcs = GET_VHTNSSMCS(mcs_map, nss);

	/* अगर mcs is 3, nss must be 1 (NSS = 1). Default mcs to MCS 0~9 */
	अगर (mcs == IEEE80211_VHT_MCS_NOT_SUPPORTED)
		mcs = IEEE80211_VHT_MCS_SUPPORT_0_9;

	अगर (GET_VHTCAP_CHWDSET(usr_vht_cap_info)) अणु
		/* support 160 MHz */
		max_rate = max_rate_lgi_160MHZ[nss - 1][mcs];
		अगर (!max_rate)
			/* MCS9 is not supported in NSS6 */
			max_rate = max_rate_lgi_160MHZ[nss - 1][mcs - 1];
	पूर्ण अन्यथा अणु
		max_rate = max_rate_lgi_80MHZ[nss - 1][mcs];
		अगर (!max_rate)
			/* MCS9 is not supported in NSS3 */
			max_rate = max_rate_lgi_80MHZ[nss - 1][mcs - 1];
	पूर्ण

	वापस max_rate;
पूर्ण

अटल व्योम
mwअगरiex_fill_vht_cap_info(काष्ठा mwअगरiex_निजी *priv,
			  काष्ठा ieee80211_vht_cap *vht_cap, u8 bands)
अणु
	काष्ठा mwअगरiex_adapter *adapter = priv->adapter;

	अगर (bands & BAND_A)
		vht_cap->vht_cap_info =
				cpu_to_le32(adapter->usr_करोt_11ac_dev_cap_a);
	अन्यथा
		vht_cap->vht_cap_info =
				cpu_to_le32(adapter->usr_करोt_11ac_dev_cap_bg);
पूर्ण

व्योम mwअगरiex_fill_vht_cap_tlv(काष्ठा mwअगरiex_निजी *priv,
			      काष्ठा ieee80211_vht_cap *vht_cap, u8 bands)
अणु
	काष्ठा mwअगरiex_adapter *adapter = priv->adapter;
	u16 mcs_map_user, mcs_map_resp, mcs_map_result;
	u16 mcs_user, mcs_resp, nss, पंचांगp;

	/* Fill VHT cap info */
	mwअगरiex_fill_vht_cap_info(priv, vht_cap, bands);

	/* rx MCS Set: find the minimum of the user rx mcs and ap rx mcs */
	mcs_map_user = GET_DEVRXMCSMAP(adapter->usr_करोt_11ac_mcs_support);
	mcs_map_resp = le16_to_cpu(vht_cap->supp_mcs.rx_mcs_map);
	mcs_map_result = 0;

	क्रम (nss = 1; nss <= 8; nss++) अणु
		mcs_user = GET_VHTNSSMCS(mcs_map_user, nss);
		mcs_resp = GET_VHTNSSMCS(mcs_map_resp, nss);

		अगर ((mcs_user == IEEE80211_VHT_MCS_NOT_SUPPORTED) ||
		    (mcs_resp == IEEE80211_VHT_MCS_NOT_SUPPORTED))
			SET_VHTNSSMCS(mcs_map_result, nss,
				      IEEE80211_VHT_MCS_NOT_SUPPORTED);
		अन्यथा
			SET_VHTNSSMCS(mcs_map_result, nss,
				      min(mcs_user, mcs_resp));
	पूर्ण

	vht_cap->supp_mcs.rx_mcs_map = cpu_to_le16(mcs_map_result);

	पंचांगp = mwअगरiex_convert_mcsmap_to_maxrate(priv, bands, mcs_map_result);
	vht_cap->supp_mcs.rx_highest = cpu_to_le16(पंचांगp);

	/* tx MCS Set: find the minimum of the user tx mcs and ap tx mcs */
	mcs_map_user = GET_DEVTXMCSMAP(adapter->usr_करोt_11ac_mcs_support);
	mcs_map_resp = le16_to_cpu(vht_cap->supp_mcs.tx_mcs_map);
	mcs_map_result = 0;

	क्रम (nss = 1; nss <= 8; nss++) अणु
		mcs_user = GET_VHTNSSMCS(mcs_map_user, nss);
		mcs_resp = GET_VHTNSSMCS(mcs_map_resp, nss);
		अगर ((mcs_user == IEEE80211_VHT_MCS_NOT_SUPPORTED) ||
		    (mcs_resp == IEEE80211_VHT_MCS_NOT_SUPPORTED))
			SET_VHTNSSMCS(mcs_map_result, nss,
				      IEEE80211_VHT_MCS_NOT_SUPPORTED);
		अन्यथा
			SET_VHTNSSMCS(mcs_map_result, nss,
				      min(mcs_user, mcs_resp));
	पूर्ण

	vht_cap->supp_mcs.tx_mcs_map = cpu_to_le16(mcs_map_result);

	पंचांगp = mwअगरiex_convert_mcsmap_to_maxrate(priv, bands, mcs_map_result);
	vht_cap->supp_mcs.tx_highest = cpu_to_le16(पंचांगp);

	वापस;
पूर्ण

पूर्णांक mwअगरiex_cmd_append_11ac_tlv(काष्ठा mwअगरiex_निजी *priv,
			     काष्ठा mwअगरiex_bssdescriptor *bss_desc,
			     u8 **buffer)
अणु
	काष्ठा mwअगरiex_ie_types_vhtcap *vht_cap;
	काष्ठा mwअगरiex_ie_types_oper_mode_ntf *oper_ntf;
	काष्ठा ieee_types_oper_mode_ntf *ieee_oper_ntf;
	काष्ठा mwअगरiex_ie_types_vht_oper *vht_op;
	काष्ठा mwअगरiex_adapter *adapter = priv->adapter;
	u8 supp_chwd_set;
	u32 usr_vht_cap_info;
	पूर्णांक ret_len = 0;

	अगर (bss_desc->bss_band & BAND_A)
		usr_vht_cap_info = adapter->usr_करोt_11ac_dev_cap_a;
	अन्यथा
		usr_vht_cap_info = adapter->usr_करोt_11ac_dev_cap_bg;

	/* VHT Capabilities IE */
	अगर (bss_desc->bcn_vht_cap) अणु
		vht_cap = (काष्ठा mwअगरiex_ie_types_vhtcap *)*buffer;
		स_रखो(vht_cap, 0, माप(*vht_cap));
		vht_cap->header.type = cpu_to_le16(WLAN_EID_VHT_CAPABILITY);
		vht_cap->header.len  =
				cpu_to_le16(माप(काष्ठा ieee80211_vht_cap));
		स_नकल((u8 *)vht_cap + माप(काष्ठा mwअगरiex_ie_types_header),
		       (u8 *)bss_desc->bcn_vht_cap,
		       le16_to_cpu(vht_cap->header.len));

		mwअगरiex_fill_vht_cap_tlv(priv, &vht_cap->vht_cap,
					 bss_desc->bss_band);
		*buffer += माप(*vht_cap);
		ret_len += माप(*vht_cap);
	पूर्ण

	/* VHT Operation IE */
	अगर (bss_desc->bcn_vht_oper) अणु
		अगर (priv->bss_mode == NL80211_IFTYPE_STATION) अणु
			vht_op = (काष्ठा mwअगरiex_ie_types_vht_oper *)*buffer;
			स_रखो(vht_op, 0, माप(*vht_op));
			vht_op->header.type =
					cpu_to_le16(WLAN_EID_VHT_OPERATION);
			vht_op->header.len  = cpu_to_le16(माप(*vht_op) -
				      माप(काष्ठा mwअगरiex_ie_types_header));
			स_नकल((u8 *)vht_op +
				माप(काष्ठा mwअगरiex_ie_types_header),
			       (u8 *)bss_desc->bcn_vht_oper,
			       le16_to_cpu(vht_op->header.len));

			/* negotiate the channel width and central freq
			 * and keep the central freq as the peer suggests
			 */
			supp_chwd_set = GET_VHTCAP_CHWDSET(usr_vht_cap_info);

			चयन (supp_chwd_set) अणु
			हाल 0:
				vht_op->chan_width =
				     min_t(u8, IEEE80211_VHT_CHANWIDTH_80MHZ,
					   bss_desc->bcn_vht_oper->chan_width);
				अवरोध;
			हाल 1:
				vht_op->chan_width =
				     min_t(u8, IEEE80211_VHT_CHANWIDTH_160MHZ,
					   bss_desc->bcn_vht_oper->chan_width);
				अवरोध;
			हाल 2:
				vht_op->chan_width =
				     min_t(u8, IEEE80211_VHT_CHANWIDTH_80P80MHZ,
					   bss_desc->bcn_vht_oper->chan_width);
				अवरोध;
			शेष:
				vht_op->chan_width =
				     IEEE80211_VHT_CHANWIDTH_USE_HT;
				अवरोध;
			पूर्ण

			*buffer += माप(*vht_op);
			ret_len += माप(*vht_op);
		पूर्ण
	पूर्ण

	/* Operating Mode Notअगरication IE */
	अगर (bss_desc->oper_mode) अणु
		ieee_oper_ntf = bss_desc->oper_mode;
		oper_ntf = (व्योम *)*buffer;
		स_रखो(oper_ntf, 0, माप(*oper_ntf));
		oper_ntf->header.type = cpu_to_le16(WLAN_EID_OPMODE_NOTIF);
		oper_ntf->header.len = cpu_to_le16(माप(u8));
		oper_ntf->oper_mode = ieee_oper_ntf->oper_mode;
		*buffer += माप(*oper_ntf);
		ret_len += माप(*oper_ntf);
	पूर्ण

	वापस ret_len;
पूर्ण

पूर्णांक mwअगरiex_cmd_11ac_cfg(काष्ठा mwअगरiex_निजी *priv,
			 काष्ठा host_cmd_ds_command *cmd, u16 cmd_action,
			 काष्ठा mwअगरiex_11ac_vht_cfg *cfg)
अणु
	काष्ठा host_cmd_11ac_vht_cfg *vhtcfg = &cmd->params.vht_cfg;

	cmd->command = cpu_to_le16(HostCmd_CMD_11AC_CFG);
	cmd->size = cpu_to_le16(माप(काष्ठा host_cmd_11ac_vht_cfg) +
				S_DS_GEN);
	vhtcfg->action = cpu_to_le16(cmd_action);
	vhtcfg->band_config = cfg->band_config;
	vhtcfg->misc_config = cfg->misc_config;
	vhtcfg->cap_info = cpu_to_le32(cfg->cap_info);
	vhtcfg->mcs_tx_set = cpu_to_le32(cfg->mcs_tx_set);
	vhtcfg->mcs_rx_set = cpu_to_le32(cfg->mcs_rx_set);

	वापस 0;
पूर्ण

/* This function initializes the BlockACK setup inक्रमmation क्रम given
 * mwअगरiex_निजी काष्ठाure क्रम 11ac enabled networks.
 */
व्योम mwअगरiex_set_11ac_ba_params(काष्ठा mwअगरiex_निजी *priv)
अणु
	priv->add_ba_param.समयout = MWIFIEX_DEFAULT_BLOCK_ACK_TIMEOUT;

	अगर (GET_BSS_ROLE(priv) == MWIFIEX_BSS_ROLE_UAP) अणु
		priv->add_ba_param.tx_win_size =
					   MWIFIEX_11AC_UAP_AMPDU_DEF_TXWINSIZE;
		priv->add_ba_param.rx_win_size =
					   MWIFIEX_11AC_UAP_AMPDU_DEF_RXWINSIZE;
	पूर्ण अन्यथा अणु
		priv->add_ba_param.tx_win_size =
					   MWIFIEX_11AC_STA_AMPDU_DEF_TXWINSIZE;
		priv->add_ba_param.rx_win_size =
					   MWIFIEX_11AC_STA_AMPDU_DEF_RXWINSIZE;
	पूर्ण

	वापस;
पूर्ण

bool mwअगरiex_is_bss_in_11ac_mode(काष्ठा mwअगरiex_निजी *priv)
अणु
	काष्ठा mwअगरiex_bssdescriptor *bss_desc;
	काष्ठा ieee80211_vht_operation *vht_oper;

	bss_desc = &priv->curr_bss_params.bss_descriptor;
	vht_oper = bss_desc->bcn_vht_oper;

	अगर (!bss_desc->bcn_vht_cap || !vht_oper)
		वापस false;

	अगर (vht_oper->chan_width == IEEE80211_VHT_CHANWIDTH_USE_HT)
		वापस false;

	वापस true;
पूर्ण

u8 mwअगरiex_get_center_freq_index(काष्ठा mwअगरiex_निजी *priv, u8 band,
				 u32 pri_chan, u8 chan_bw)
अणु
	u8 center_freq_idx = 0;

	अगर (band & BAND_AAC) अणु
		चयन (pri_chan) अणु
		हाल 36:
		हाल 40:
		हाल 44:
		हाल 48:
			अगर (chan_bw == IEEE80211_VHT_CHANWIDTH_80MHZ)
				center_freq_idx = 42;
			अवरोध;
		हाल 52:
		हाल 56:
		हाल 60:
		हाल 64:
			अगर (chan_bw == IEEE80211_VHT_CHANWIDTH_80MHZ)
				center_freq_idx = 58;
			अन्यथा अगर (chan_bw == IEEE80211_VHT_CHANWIDTH_160MHZ)
				center_freq_idx = 50;
			अवरोध;
		हाल 100:
		हाल 104:
		हाल 108:
		हाल 112:
			अगर (chan_bw == IEEE80211_VHT_CHANWIDTH_80MHZ)
				center_freq_idx = 106;
			अवरोध;
		हाल 116:
		हाल 120:
		हाल 124:
		हाल 128:
			अगर (chan_bw == IEEE80211_VHT_CHANWIDTH_80MHZ)
				center_freq_idx = 122;
			अन्यथा अगर (chan_bw == IEEE80211_VHT_CHANWIDTH_160MHZ)
				center_freq_idx = 114;
			अवरोध;
		हाल 132:
		हाल 136:
		हाल 140:
		हाल 144:
			अगर (chan_bw == IEEE80211_VHT_CHANWIDTH_80MHZ)
				center_freq_idx = 138;
			अवरोध;
		हाल 149:
		हाल 153:
		हाल 157:
		हाल 161:
			अगर (chan_bw == IEEE80211_VHT_CHANWIDTH_80MHZ)
				center_freq_idx = 155;
			अवरोध;
		शेष:
			center_freq_idx = 42;
		पूर्ण
	पूर्ण

	वापस center_freq_idx;
पूर्ण
