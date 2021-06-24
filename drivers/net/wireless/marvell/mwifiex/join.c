<शैली गुरु>
/*
 * NXP Wireless LAN device driver: association and ad-hoc start/join
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
#समावेश "util.h"
#समावेश "fw.h"
#समावेश "main.h"
#समावेश "wmm.h"
#समावेश "11n.h"
#समावेश "11ac.h"

#घोषणा CAPINFO_MASK    (~(BIT(15) | BIT(14) | BIT(12) | BIT(11) | BIT(9)))

/*
 * Append a generic IE as a pass through TLV to a TLV buffer.
 *
 * This function is called from the network join command preparation routine.
 *
 * If the IE buffer has been setup by the application, this routine appends
 * the buffer as a pass through TLV type to the request.
 */
अटल पूर्णांक
mwअगरiex_cmd_append_generic_ie(काष्ठा mwअगरiex_निजी *priv, u8 **buffer)
अणु
	पूर्णांक ret_len = 0;
	काष्ठा mwअगरiex_ie_types_header ie_header;

	/* Null Checks */
	अगर (!buffer)
		वापस 0;
	अगर (!(*buffer))
		वापस 0;

	/*
	 * If there is a generic ie buffer setup, append it to the वापस
	 *   parameter buffer poपूर्णांकer.
	 */
	अगर (priv->gen_ie_buf_len) अणु
		mwअगरiex_dbg(priv->adapter, INFO,
			    "info: %s: append generic ie len %d to %p\n",
			    __func__, priv->gen_ie_buf_len, *buffer);

		/* Wrap the generic IE buffer with a pass through TLV type */
		ie_header.type = cpu_to_le16(TLV_TYPE_PASSTHROUGH);
		ie_header.len = cpu_to_le16(priv->gen_ie_buf_len);
		स_नकल(*buffer, &ie_header, माप(ie_header));

		/* Increment the वापस size and the वापस buffer poपूर्णांकer
		   param */
		*buffer += माप(ie_header);
		ret_len += माप(ie_header);

		/* Copy the generic IE buffer to the output buffer, advance
		   poपूर्णांकer */
		स_नकल(*buffer, priv->gen_ie_buf, priv->gen_ie_buf_len);

		/* Increment the वापस size and the वापस buffer poपूर्णांकer
		   param */
		*buffer += priv->gen_ie_buf_len;
		ret_len += priv->gen_ie_buf_len;

		/* Reset the generic IE buffer */
		priv->gen_ie_buf_len = 0;
	पूर्ण

	/* वापस the length appended to the buffer */
	वापस ret_len;
पूर्ण

/*
 * Append TSF tracking info from the scan table क्रम the target AP.
 *
 * This function is called from the network join command preparation routine.
 *
 * The TSF table TSF sent to the firmware contains two TSF values:
 *      - The TSF of the target AP from its previous beacon/probe response
 *      - The TSF बारtamp of our local MAC at the समय we observed the
 *        beacon/probe response.
 *
 * The firmware uses the बारtamp values to set an initial TSF value
 * in the MAC क्रम the new association after a reassociation attempt.
 */
अटल पूर्णांक
mwअगरiex_cmd_append_tsf_tlv(काष्ठा mwअगरiex_निजी *priv, u8 **buffer,
			   काष्ठा mwअगरiex_bssdescriptor *bss_desc)
अणु
	काष्ठा mwअगरiex_ie_types_tsf_बारtamp tsf_tlv;
	__le64 tsf_val;

	/* Null Checks */
	अगर (buffer == शून्य)
		वापस 0;
	अगर (*buffer == शून्य)
		वापस 0;

	स_रखो(&tsf_tlv, 0x00, माप(काष्ठा mwअगरiex_ie_types_tsf_बारtamp));

	tsf_tlv.header.type = cpu_to_le16(TLV_TYPE_TSFTIMESTAMP);
	tsf_tlv.header.len = cpu_to_le16(2 * माप(tsf_val));

	स_नकल(*buffer, &tsf_tlv, माप(tsf_tlv.header));
	*buffer += माप(tsf_tlv.header);

	/* TSF at the समय when beacon/probe_response was received */
	tsf_val = cpu_to_le64(bss_desc->fw_tsf);
	स_नकल(*buffer, &tsf_val, माप(tsf_val));
	*buffer += माप(tsf_val);

	tsf_val = cpu_to_le64(bss_desc->बारtamp);

	mwअगरiex_dbg(priv->adapter, INFO,
		    "info: %s: TSF offset calc: %016llx - %016llx\n",
		    __func__, bss_desc->बारtamp, bss_desc->fw_tsf);

	स_नकल(*buffer, &tsf_val, माप(tsf_val));
	*buffer += माप(tsf_val);

	वापस माप(tsf_tlv.header) + (2 * माप(tsf_val));
पूर्ण

/*
 * This function finds out the common rates between rate1 and rate2.
 *
 * It will fill common rates in rate1 as output अगर found.
 *
 * NOTE: Setting the MSB of the basic rates needs to be taken
 * care of, either beक्रमe or after calling this function.
 */
अटल पूर्णांक mwअगरiex_get_common_rates(काष्ठा mwअगरiex_निजी *priv, u8 *rate1,
				    u32 rate1_size, u8 *rate2, u32 rate2_size)
अणु
	पूर्णांक ret;
	u8 *ptr = rate1, *पंचांगp;
	u32 i, j;

	पंचांगp = kmemdup(rate1, rate1_size, GFP_KERNEL);
	अगर (!पंचांगp) अणु
		mwअगरiex_dbg(priv->adapter, ERROR, "failed to alloc tmp buf\n");
		वापस -ENOMEM;
	पूर्ण

	स_रखो(rate1, 0, rate1_size);

	क्रम (i = 0; i < rate2_size && rate2[i]; i++) अणु
		क्रम (j = 0; j < rate1_size && पंचांगp[j]; j++) अणु
			/* Check common rate, excluding the bit क्रम
			   basic rate */
			अगर ((rate2[i] & 0x7F) == (पंचांगp[j] & 0x7F)) अणु
				*rate1++ = पंचांगp[j];
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	mwअगरiex_dbg(priv->adapter, INFO, "info: Tx data rate set to %#x\n",
		    priv->data_rate);

	अगर (!priv->is_data_rate_स्वतः) अणु
		जबतक (*ptr) अणु
			अगर ((*ptr & 0x7f) == priv->data_rate) अणु
				ret = 0;
				जाओ करोne;
			पूर्ण
			ptr++;
		पूर्ण
		mwअगरiex_dbg(priv->adapter, ERROR,
			    "previously set fixed data rate %#x\t"
			    "is not compatible with the network\n",
			    priv->data_rate);

		ret = -1;
		जाओ करोne;
	पूर्ण

	ret = 0;
करोne:
	kमुक्त(पंचांगp);
	वापस ret;
पूर्ण

/*
 * This function creates the पूर्णांकersection of the rates supported by a
 * target BSS and our adapter settings क्रम use in an assoc/join command.
 */
अटल पूर्णांक
mwअगरiex_setup_rates_from_bssdesc(काष्ठा mwअगरiex_निजी *priv,
				 काष्ठा mwअगरiex_bssdescriptor *bss_desc,
				 u8 *out_rates, u32 *out_rates_size)
अणु
	u8 card_rates[MWIFIEX_SUPPORTED_RATES];
	u32 card_rates_size;

	/* Copy AP supported rates */
	स_नकल(out_rates, bss_desc->supported_rates, MWIFIEX_SUPPORTED_RATES);
	/* Get the STA supported rates */
	card_rates_size = mwअगरiex_get_active_data_rates(priv, card_rates);
	/* Get the common rates between AP and STA supported rates */
	अगर (mwअगरiex_get_common_rates(priv, out_rates, MWIFIEX_SUPPORTED_RATES,
				     card_rates, card_rates_size)) अणु
		*out_rates_size = 0;
		mwअगरiex_dbg(priv->adapter, ERROR,
			    "%s: cannot get common rates\n",
			    __func__);
		वापस -1;
	पूर्ण

	*out_rates_size =
		min_t(माप_प्रकार, म_माप(out_rates), MWIFIEX_SUPPORTED_RATES);

	वापस 0;
पूर्ण

/*
 * This function appends a WPS IE. It is called from the network join command
 * preparation routine.
 *
 * If the IE buffer has been setup by the application, this routine appends
 * the buffer as a WPS TLV type to the request.
 */
अटल पूर्णांक
mwअगरiex_cmd_append_wps_ie(काष्ठा mwअगरiex_निजी *priv, u8 **buffer)
अणु
	पूर्णांक retLen = 0;
	काष्ठा mwअगरiex_ie_types_header ie_header;

	अगर (!buffer || !*buffer)
		वापस 0;

	/*
	 * If there is a wps ie buffer setup, append it to the वापस
	 * parameter buffer poपूर्णांकer.
	 */
	अगर (priv->wps_ie_len) अणु
		mwअगरiex_dbg(priv->adapter, CMD,
			    "cmd: append wps ie %d to %p\n",
			    priv->wps_ie_len, *buffer);

		/* Wrap the generic IE buffer with a pass through TLV type */
		ie_header.type = cpu_to_le16(TLV_TYPE_PASSTHROUGH);
		ie_header.len = cpu_to_le16(priv->wps_ie_len);
		स_नकल(*buffer, &ie_header, माप(ie_header));
		*buffer += माप(ie_header);
		retLen += माप(ie_header);

		स_नकल(*buffer, priv->wps_ie, priv->wps_ie_len);
		*buffer += priv->wps_ie_len;
		retLen += priv->wps_ie_len;

	पूर्ण

	kमुक्त(priv->wps_ie);
	priv->wps_ie_len = 0;
	वापस retLen;
पूर्ण

/*
 * This function appends a WAPI IE.
 *
 * This function is called from the network join command preparation routine.
 *
 * If the IE buffer has been setup by the application, this routine appends
 * the buffer as a WAPI TLV type to the request.
 */
अटल पूर्णांक
mwअगरiex_cmd_append_wapi_ie(काष्ठा mwअगरiex_निजी *priv, u8 **buffer)
अणु
	पूर्णांक retLen = 0;
	काष्ठा mwअगरiex_ie_types_header ie_header;

	/* Null Checks */
	अगर (buffer == शून्य)
		वापस 0;
	अगर (*buffer == शून्य)
		वापस 0;

	/*
	 * If there is a wapi ie buffer setup, append it to the वापस
	 *   parameter buffer poपूर्णांकer.
	 */
	अगर (priv->wapi_ie_len) अणु
		mwअगरiex_dbg(priv->adapter, CMD,
			    "cmd: append wapi ie %d to %p\n",
			    priv->wapi_ie_len, *buffer);

		/* Wrap the generic IE buffer with a pass through TLV type */
		ie_header.type = cpu_to_le16(TLV_TYPE_WAPI_IE);
		ie_header.len = cpu_to_le16(priv->wapi_ie_len);
		स_नकल(*buffer, &ie_header, माप(ie_header));

		/* Increment the वापस size and the वापस buffer poपूर्णांकer
		   param */
		*buffer += माप(ie_header);
		retLen += माप(ie_header);

		/* Copy the wapi IE buffer to the output buffer, advance
		   poपूर्णांकer */
		स_नकल(*buffer, priv->wapi_ie, priv->wapi_ie_len);

		/* Increment the वापस size and the वापस buffer poपूर्णांकer
		   param */
		*buffer += priv->wapi_ie_len;
		retLen += priv->wapi_ie_len;

	पूर्ण
	/* वापस the length appended to the buffer */
	वापस retLen;
पूर्ण

/*
 * This function appends rsn ie tlv क्रम wpa/wpa2 security modes.
 * It is called from the network join command preparation routine.
 */
अटल पूर्णांक mwअगरiex_append_rsn_ie_wpa_wpa2(काष्ठा mwअगरiex_निजी *priv,
					  u8 **buffer)
अणु
	काष्ठा mwअगरiex_ie_types_rsn_param_set *rsn_ie_tlv;
	पूर्णांक rsn_ie_len;

	अगर (!buffer || !(*buffer))
		वापस 0;

	rsn_ie_tlv = (काष्ठा mwअगरiex_ie_types_rsn_param_set *) (*buffer);
	rsn_ie_tlv->header.type = cpu_to_le16((u16) priv->wpa_ie[0]);
	rsn_ie_tlv->header.type = cpu_to_le16(
				 le16_to_cpu(rsn_ie_tlv->header.type) & 0x00FF);
	rsn_ie_tlv->header.len = cpu_to_le16((u16) priv->wpa_ie[1]);
	rsn_ie_tlv->header.len = cpu_to_le16(le16_to_cpu(rsn_ie_tlv->header.len)
							 & 0x00FF);
	अगर (le16_to_cpu(rsn_ie_tlv->header.len) <= (माप(priv->wpa_ie) - 2))
		स_नकल(rsn_ie_tlv->rsn_ie, &priv->wpa_ie[2],
		       le16_to_cpu(rsn_ie_tlv->header.len));
	अन्यथा
		वापस -1;

	rsn_ie_len = माप(rsn_ie_tlv->header) +
					le16_to_cpu(rsn_ie_tlv->header.len);
	*buffer += rsn_ie_len;

	वापस rsn_ie_len;
पूर्ण

/*
 * This function prepares command क्रम association.
 *
 * This sets the following parameters -
 *      - Peer MAC address
 *      - Listen पूर्णांकerval
 *      - Beacon पूर्णांकerval
 *      - Capability inक्रमmation
 *
 * ...and the following TLVs, as required -
 *      - SSID TLV
 *      - PHY TLV
 *      - SS TLV
 *      - Rates TLV
 *      - Authentication TLV
 *      - Channel TLV
 *      - WPA/WPA2 IE
 *      - 11n TLV
 *      - Venकरोr specअगरic TLV
 *      - WMM TLV
 *      - WAPI IE
 *      - Generic IE
 *      - TSF TLV
 *
 * Preparation also includes -
 *      - Setting command ID and proper size
 *      - Ensuring correct endian-ness
 */
पूर्णांक mwअगरiex_cmd_802_11_associate(काष्ठा mwअगरiex_निजी *priv,
				 काष्ठा host_cmd_ds_command *cmd,
				 काष्ठा mwअगरiex_bssdescriptor *bss_desc)
अणु
	काष्ठा host_cmd_ds_802_11_associate *assoc = &cmd->params.associate;
	काष्ठा mwअगरiex_ie_types_ssid_param_set *ssid_tlv;
	काष्ठा mwअगरiex_ie_types_phy_param_set *phy_tlv;
	काष्ठा mwअगरiex_ie_types_ss_param_set *ss_tlv;
	काष्ठा mwअगरiex_ie_types_rates_param_set *rates_tlv;
	काष्ठा mwअगरiex_ie_types_auth_type *auth_tlv;
	काष्ठा mwअगरiex_ie_types_chan_list_param_set *chan_tlv;
	u8 rates[MWIFIEX_SUPPORTED_RATES];
	u32 rates_size;
	u16 पंचांगp_cap;
	u8 *pos;
	पूर्णांक rsn_ie_len = 0;

	pos = (u8 *) assoc;

	cmd->command = cpu_to_le16(HostCmd_CMD_802_11_ASSOCIATE);

	/* Save so we know which BSS Desc to use in the response handler */
	priv->attempted_bss_desc = bss_desc;

	स_नकल(assoc->peer_sta_addr,
	       bss_desc->mac_address, माप(assoc->peer_sta_addr));
	pos += माप(assoc->peer_sta_addr);

	/* Set the listen पूर्णांकerval */
	assoc->listen_पूर्णांकerval = cpu_to_le16(priv->listen_पूर्णांकerval);
	/* Set the beacon period */
	assoc->beacon_period = cpu_to_le16(bss_desc->beacon_period);

	pos += माप(assoc->cap_info_biपंचांगap);
	pos += माप(assoc->listen_पूर्णांकerval);
	pos += माप(assoc->beacon_period);
	pos += माप(assoc->dtim_period);

	ssid_tlv = (काष्ठा mwअगरiex_ie_types_ssid_param_set *) pos;
	ssid_tlv->header.type = cpu_to_le16(WLAN_EID_SSID);
	ssid_tlv->header.len = cpu_to_le16((u16) bss_desc->ssid.ssid_len);
	स_नकल(ssid_tlv->ssid, bss_desc->ssid.ssid,
	       le16_to_cpu(ssid_tlv->header.len));
	pos += माप(ssid_tlv->header) + le16_to_cpu(ssid_tlv->header.len);

	phy_tlv = (काष्ठा mwअगरiex_ie_types_phy_param_set *) pos;
	phy_tlv->header.type = cpu_to_le16(WLAN_EID_DS_PARAMS);
	phy_tlv->header.len = cpu_to_le16(माप(phy_tlv->fh_ds.ds_param_set));
	स_नकल(&phy_tlv->fh_ds.ds_param_set,
	       &bss_desc->phy_param_set.ds_param_set.current_chan,
	       माप(phy_tlv->fh_ds.ds_param_set));
	pos += माप(phy_tlv->header) + le16_to_cpu(phy_tlv->header.len);

	ss_tlv = (काष्ठा mwअगरiex_ie_types_ss_param_set *) pos;
	ss_tlv->header.type = cpu_to_le16(WLAN_EID_CF_PARAMS);
	ss_tlv->header.len = cpu_to_le16(माप(ss_tlv->cf_ibss.cf_param_set));
	pos += माप(ss_tlv->header) + le16_to_cpu(ss_tlv->header.len);

	/* Get the common rates supported between the driver and the BSS Desc */
	अगर (mwअगरiex_setup_rates_from_bssdesc
	    (priv, bss_desc, rates, &rates_size))
		वापस -1;

	/* Save the data rates पूर्णांकo Current BSS state काष्ठाure */
	priv->curr_bss_params.num_of_rates = rates_size;
	स_नकल(&priv->curr_bss_params.data_rates, rates, rates_size);

	/* Setup the Rates TLV in the association command */
	rates_tlv = (काष्ठा mwअगरiex_ie_types_rates_param_set *) pos;
	rates_tlv->header.type = cpu_to_le16(WLAN_EID_SUPP_RATES);
	rates_tlv->header.len = cpu_to_le16((u16) rates_size);
	स_नकल(rates_tlv->rates, rates, rates_size);
	pos += माप(rates_tlv->header) + rates_size;
	mwअगरiex_dbg(priv->adapter, INFO, "info: ASSOC_CMD: rates size = %d\n",
		    rates_size);

	/* Add the Authentication type to be used क्रम Auth frames */
	auth_tlv = (काष्ठा mwअगरiex_ie_types_auth_type *) pos;
	auth_tlv->header.type = cpu_to_le16(TLV_TYPE_AUTH_TYPE);
	auth_tlv->header.len = cpu_to_le16(माप(auth_tlv->auth_type));
	अगर (priv->sec_info.wep_enabled)
		auth_tlv->auth_type = cpu_to_le16(
				(u16) priv->sec_info.authentication_mode);
	अन्यथा
		auth_tlv->auth_type = cpu_to_le16(NL80211_AUTHTYPE_OPEN_SYSTEM);

	pos += माप(auth_tlv->header) + le16_to_cpu(auth_tlv->header.len);

	अगर (IS_SUPPORT_MULTI_BANDS(priv->adapter) &&
	    !(ISSUPP_11NENABLED(priv->adapter->fw_cap_info) &&
	    (!bss_desc->disable_11n) &&
	    (priv->adapter->config_bands & BAND_GN ||
	     priv->adapter->config_bands & BAND_AN) &&
	    (bss_desc->bcn_ht_cap)
	    )
		) अणु
		/* Append a channel TLV क्रम the channel the attempted AP was
		   found on */
		chan_tlv = (काष्ठा mwअगरiex_ie_types_chan_list_param_set *) pos;
		chan_tlv->header.type = cpu_to_le16(TLV_TYPE_CHANLIST);
		chan_tlv->header.len =
			cpu_to_le16(माप(काष्ठा mwअगरiex_chan_scan_param_set));

		स_रखो(chan_tlv->chan_scan_param, 0x00,
		       माप(काष्ठा mwअगरiex_chan_scan_param_set));
		chan_tlv->chan_scan_param[0].chan_number =
			(bss_desc->phy_param_set.ds_param_set.current_chan);
		mwअगरiex_dbg(priv->adapter, INFO, "info: Assoc: TLV Chan = %d\n",
			    chan_tlv->chan_scan_param[0].chan_number);

		chan_tlv->chan_scan_param[0].radio_type =
			mwअगरiex_band_to_radio_type((u8) bss_desc->bss_band);

		mwअगरiex_dbg(priv->adapter, INFO, "info: Assoc: TLV Band = %d\n",
			    chan_tlv->chan_scan_param[0].radio_type);
		pos += माप(chan_tlv->header) +
			माप(काष्ठा mwअगरiex_chan_scan_param_set);
	पूर्ण

	अगर (!priv->wps.session_enable) अणु
		अगर (priv->sec_info.wpa_enabled || priv->sec_info.wpa2_enabled)
			rsn_ie_len = mwअगरiex_append_rsn_ie_wpa_wpa2(priv, &pos);

		अगर (rsn_ie_len == -1)
			वापस -1;
	पूर्ण

	अगर (ISSUPP_11NENABLED(priv->adapter->fw_cap_info) &&
	    (!bss_desc->disable_11n) &&
	    (priv->adapter->config_bands & BAND_GN ||
	     priv->adapter->config_bands & BAND_AN))
		mwअगरiex_cmd_append_11n_tlv(priv, bss_desc, &pos);

	अगर (ISSUPP_11ACENABLED(priv->adapter->fw_cap_info) &&
	    !bss_desc->disable_11n && !bss_desc->disable_11ac &&
	    priv->adapter->config_bands & BAND_AAC)
		mwअगरiex_cmd_append_11ac_tlv(priv, bss_desc, &pos);

	/* Append venकरोr specअगरic IE TLV */
	mwअगरiex_cmd_append_vsie_tlv(priv, MWIFIEX_VSIE_MASK_ASSOC, &pos);

	mwअगरiex_wmm_process_association_req(priv, &pos, &bss_desc->wmm_ie,
					    bss_desc->bcn_ht_cap);
	अगर (priv->sec_info.wapi_enabled && priv->wapi_ie_len)
		mwअगरiex_cmd_append_wapi_ie(priv, &pos);

	अगर (priv->wps.session_enable && priv->wps_ie_len)
		mwअगरiex_cmd_append_wps_ie(priv, &pos);

	mwअगरiex_cmd_append_generic_ie(priv, &pos);

	mwअगरiex_cmd_append_tsf_tlv(priv, &pos, bss_desc);

	mwअगरiex_11h_process_join(priv, &pos, bss_desc);

	cmd->size = cpu_to_le16((u16) (pos - (u8 *) assoc) + S_DS_GEN);

	/* Set the Capability info at last */
	पंचांगp_cap = bss_desc->cap_info_biपंचांगap;

	अगर (priv->adapter->config_bands == BAND_B)
		पंचांगp_cap &= ~WLAN_CAPABILITY_SHORT_SLOT_TIME;

	पंचांगp_cap &= CAPINFO_MASK;
	mwअगरiex_dbg(priv->adapter, INFO,
		    "info: ASSOC_CMD: tmp_cap=%4X CAPINFO_MASK=%4lX\n",
		    पंचांगp_cap, CAPINFO_MASK);
	assoc->cap_info_biपंचांगap = cpu_to_le16(पंचांगp_cap);

	वापस 0;
पूर्ण

अटल स्थिर अक्षर *assoc_failure_reason_to_str(u16 cap_info)
अणु
	चयन (cap_info) अणु
	हाल CONNECT_ERR_AUTH_ERR_STA_FAILURE:
		वापस "CONNECT_ERR_AUTH_ERR_STA_FAILURE";
	हाल CONNECT_ERR_AUTH_MSG_UNHANDLED:
		वापस "CONNECT_ERR_AUTH_MSG_UNHANDLED";
	हाल CONNECT_ERR_ASSOC_ERR_TIMEOUT:
		वापस "CONNECT_ERR_ASSOC_ERR_TIMEOUT";
	हाल CONNECT_ERR_ASSOC_ERR_AUTH_REFUSED:
		वापस "CONNECT_ERR_ASSOC_ERR_AUTH_REFUSED";
	हाल CONNECT_ERR_STA_FAILURE:
		वापस "CONNECT_ERR_STA_FAILURE";
	पूर्ण

	वापस "Unknown connect failure";
पूर्ण
/*
 * Association firmware command response handler
 *
 * The response buffer क्रम the association command has the following
 * memory layout.
 *
 * For हालs where an association response was not received (indicated
 * by the CapInfo and AId field):
 *
 *     .------------------------------------------------------------.
 *     |  Header(4 * माप(t_u16)):  Standard command response hdr |
 *     .------------------------------------------------------------.
 *     |  cap_info/Error Return(t_u16):                             |
 *     |           0xFFFF(-1): Internal error                       |
 *     |           0xFFFE(-2): Authentication unhandled message     |
 *     |           0xFFFD(-3): Authentication refused               |
 *     |           0xFFFC(-4): Timeout रुकोing क्रम AP response      |
 *     .------------------------------------------------------------.
 *     |  status_code(t_u16):                                       |
 *     |        If cap_info is -1:                                  |
 *     |           An पूर्णांकernal firmware failure prevented the       |
 *     |           command from being processed.  The status_code   |
 *     |           will be set to 1.                                |
 *     |                                                            |
 *     |        If cap_info is -2:                                  |
 *     |           An authentication frame was received but was     |
 *     |           not handled by the firmware.  IEEE Status        |
 *     |           code क्रम the failure is वापसed.                |
 *     |                                                            |
 *     |        If cap_info is -3:                                  |
 *     |           An authentication frame was received and the     |
 *     |           status_code is the IEEE Status reported in the   |
 *     |           response.                                        |
 *     |                                                            |
 *     |        If cap_info is -4:                                  |
 *     |           (1) Association response समयout                 |
 *     |           (2) Authentication response समयout              |
 *     .------------------------------------------------------------.
 *     |  a_id(t_u16): 0xFFFF                                       |
 *     .------------------------------------------------------------.
 *
 *
 * For हालs where an association response was received, the IEEE
 * standard association response frame is वापसed:
 *
 *     .------------------------------------------------------------.
 *     |  Header(4 * माप(t_u16)):  Standard command response hdr |
 *     .------------------------------------------------------------.
 *     |  cap_info(t_u16): IEEE Capability                          |
 *     .------------------------------------------------------------.
 *     |  status_code(t_u16): IEEE Status Code                      |
 *     .------------------------------------------------------------.
 *     |  a_id(t_u16): IEEE Association ID                          |
 *     .------------------------------------------------------------.
 *     |  IEEE IEs(variable): Any received IEs comprising the       |
 *     |                      reमुख्यing portion of a received       |
 *     |                      association response frame.           |
 *     .------------------------------------------------------------.
 *
 * For simplistic handling, the status_code field can be used to determine
 * an association success (0) or failure (non-zero).
 */
पूर्णांक mwअगरiex_ret_802_11_associate(काष्ठा mwअगरiex_निजी *priv,
			     काष्ठा host_cmd_ds_command *resp)
अणु
	काष्ठा mwअगरiex_adapter *adapter = priv->adapter;
	पूर्णांक ret = 0;
	काष्ठा ieee_types_assoc_rsp *assoc_rsp;
	काष्ठा mwअगरiex_bssdescriptor *bss_desc;
	bool enable_data = true;
	u16 cap_info, status_code, aid;
	स्थिर u8 *ie_ptr;
	काष्ठा ieee80211_ht_operation *assoc_resp_ht_oper;

	अगर (!priv->attempted_bss_desc) अणु
		mwअगरiex_dbg(priv->adapter, ERROR,
			    "ASSOC_RESP: failed, association terminated by host\n");
		जाओ करोne;
	पूर्ण

	assoc_rsp = (काष्ठा ieee_types_assoc_rsp *) &resp->params;

	cap_info = le16_to_cpu(assoc_rsp->cap_info_biपंचांगap);
	status_code = le16_to_cpu(assoc_rsp->status_code);
	aid = le16_to_cpu(assoc_rsp->a_id);

	अगर ((aid & (BIT(15) | BIT(14))) != (BIT(15) | BIT(14)))
		dev_err(priv->adapter->dev,
			"invalid AID value 0x%x; bits 15:14 not set\n",
			aid);

	aid &= ~(BIT(15) | BIT(14));

	priv->assoc_rsp_size = min(le16_to_cpu(resp->size) - S_DS_GEN,
				   माप(priv->assoc_rsp_buf));

	assoc_rsp->a_id = cpu_to_le16(aid);
	स_नकल(priv->assoc_rsp_buf, &resp->params, priv->assoc_rsp_size);

	अगर (status_code) अणु
		priv->adapter->dbg.num_cmd_assoc_failure++;
		mwअगरiex_dbg(priv->adapter, ERROR,
			    "ASSOC_RESP: failed,\t"
			    "status code=%d err=%#x a_id=%#x\n",
			    status_code, cap_info,
			    le16_to_cpu(assoc_rsp->a_id));

		mwअगरiex_dbg(priv->adapter, ERROR, "assoc failure: reason %s\n",
			    assoc_failure_reason_to_str(cap_info));
		अगर (cap_info == CONNECT_ERR_ASSOC_ERR_TIMEOUT) अणु
			अगर (status_code == MWIFIEX_ASSOC_CMD_FAILURE_AUTH) अणु
				ret = WLAN_STATUS_AUTH_TIMEOUT;
				mwअगरiex_dbg(priv->adapter, ERROR,
					    "ASSOC_RESP: AUTH timeout\n");
			पूर्ण अन्यथा अणु
				ret = WLAN_STATUS_UNSPECIFIED_FAILURE;
				mwअगरiex_dbg(priv->adapter, ERROR,
					    "ASSOC_RESP: UNSPECIFIED failure\n");
			पूर्ण
		पूर्ण अन्यथा अणु
			ret = status_code;
		पूर्ण

		जाओ करोne;
	पूर्ण

	/* Send a Media Connected event, according to the Spec */
	priv->media_connected = true;

	priv->adapter->ps_state = PS_STATE_AWAKE;
	priv->adapter->pps_uapsd_mode = false;
	priv->adapter->tx_lock_flag = false;

	/* Set the attempted BSSID Index to current */
	bss_desc = priv->attempted_bss_desc;

	mwअगरiex_dbg(priv->adapter, INFO, "info: ASSOC_RESP: %s\n",
		    bss_desc->ssid.ssid);

	/* Make a copy of current BSSID descriptor */
	स_नकल(&priv->curr_bss_params.bss_descriptor,
	       bss_desc, माप(काष्ठा mwअगरiex_bssdescriptor));

	/* Update curr_bss_params */
	priv->curr_bss_params.bss_descriptor.channel
		= bss_desc->phy_param_set.ds_param_set.current_chan;

	priv->curr_bss_params.band = (u8) bss_desc->bss_band;

	अगर (bss_desc->wmm_ie.vend_hdr.element_id == WLAN_EID_VENDOR_SPECIFIC)
		priv->curr_bss_params.wmm_enabled = true;
	अन्यथा
		priv->curr_bss_params.wmm_enabled = false;

	अगर ((priv->wmm_required || bss_desc->bcn_ht_cap) &&
	    priv->curr_bss_params.wmm_enabled)
		priv->wmm_enabled = true;
	अन्यथा
		priv->wmm_enabled = false;

	priv->curr_bss_params.wmm_uapsd_enabled = false;

	अगर (priv->wmm_enabled)
		priv->curr_bss_params.wmm_uapsd_enabled
			= ((bss_desc->wmm_ie.qos_info_biपंचांगap &
				IEEE80211_WMM_IE_AP_QOSINFO_UAPSD) ? 1 : 0);

	/* Store the bandwidth inक्रमmation from assoc response */
	ie_ptr = cfg80211_find_ie(WLAN_EID_HT_OPERATION, assoc_rsp->ie_buffer,
				  priv->assoc_rsp_size
				  - माप(काष्ठा ieee_types_assoc_rsp));
	अगर (ie_ptr) अणु
		assoc_resp_ht_oper = (काष्ठा ieee80211_ht_operation *)(ie_ptr
					+ माप(काष्ठा ieee_types_header));
		priv->assoc_resp_ht_param = assoc_resp_ht_oper->ht_param;
		priv->ht_param_present = true;
	पूर्ण अन्यथा अणु
		priv->ht_param_present = false;
	पूर्ण

	mwअगरiex_dbg(priv->adapter, INFO,
		    "info: ASSOC_RESP: curr_pkt_filter is %#x\n",
		    priv->curr_pkt_filter);
	अगर (priv->sec_info.wpa_enabled || priv->sec_info.wpa2_enabled)
		priv->wpa_is_gtk_set = false;

	अगर (priv->wmm_enabled) अणु
		/* Don't re-enable carrier until we get the WMM_GET_STATUS
		   event */
		enable_data = false;
	पूर्ण अन्यथा अणु
		/* Since WMM is not enabled, setup the queues with the
		   शेषs */
		mwअगरiex_wmm_setup_queue_priorities(priv, शून्य);
		mwअगरiex_wmm_setup_ac_करोwngrade(priv);
	पूर्ण

	अगर (enable_data)
		mwअगरiex_dbg(priv->adapter, INFO,
			    "info: post association, re-enabling data flow\n");

	/* Reset SNR/NF/RSSI values */
	priv->data_rssi_last = 0;
	priv->data_nf_last = 0;
	priv->data_rssi_avg = 0;
	priv->data_nf_avg = 0;
	priv->bcn_rssi_last = 0;
	priv->bcn_nf_last = 0;
	priv->bcn_rssi_avg = 0;
	priv->bcn_nf_avg = 0;
	priv->rxpd_rate = 0;
	priv->rxpd_htinfo = 0;

	mwअगरiex_save_curr_bcn(priv);

	priv->adapter->dbg.num_cmd_assoc_success++;

	mwअगरiex_dbg(priv->adapter, INFO, "info: ASSOC_RESP: associated\n");

	/* Add the ra_list here क्रम infra mode as there will be only 1 ra
	   always */
	mwअगरiex_ralist_add(priv,
			   priv->curr_bss_params.bss_descriptor.mac_address);

	अगर (!netअगर_carrier_ok(priv->netdev))
		netअगर_carrier_on(priv->netdev);
	mwअगरiex_wake_up_net_dev_queue(priv->netdev, adapter);

	अगर (priv->sec_info.wpa_enabled || priv->sec_info.wpa2_enabled)
		priv->scan_block = true;
	अन्यथा
		priv->port_खोलो = true;

करोne:
	/* Need to indicate IOCTL complete */
	अगर (adapter->curr_cmd->रुको_q_enabled) अणु
		अगर (ret)
			adapter->cmd_रुको_q.status = -1;
		अन्यथा
			adapter->cmd_रुको_q.status = 0;
	पूर्ण

	वापस ret;
पूर्ण

/*
 * This function prepares command क्रम ad-hoc start.
 *
 * Driver will fill up SSID, BSS mode, IBSS parameters, physical
 * parameters, probe delay, and capability inक्रमmation. Firmware
 * will fill up beacon period, basic rates and operational rates.
 *
 * In addition, the following TLVs are added -
 *      - Channel TLV
 *      - Venकरोr specअगरic IE
 *      - WPA/WPA2 IE
 *      - HT Capabilities IE
 *      - HT Inक्रमmation IE
 *
 * Preparation also includes -
 *      - Setting command ID and proper size
 *      - Ensuring correct endian-ness
 */
पूर्णांक
mwअगरiex_cmd_802_11_ad_hoc_start(काष्ठा mwअगरiex_निजी *priv,
				काष्ठा host_cmd_ds_command *cmd,
				काष्ठा cfg80211_ssid *req_ssid)
अणु
	पूर्णांक rsn_ie_len = 0;
	काष्ठा mwअगरiex_adapter *adapter = priv->adapter;
	काष्ठा host_cmd_ds_802_11_ad_hoc_start *adhoc_start =
		&cmd->params.adhoc_start;
	काष्ठा mwअगरiex_bssdescriptor *bss_desc;
	u32 cmd_append_size = 0;
	u32 i;
	u16 पंचांगp_cap;
	काष्ठा mwअगरiex_ie_types_chan_list_param_set *chan_tlv;
	u8 radio_type;

	काष्ठा mwअगरiex_ie_types_htcap *ht_cap;
	काष्ठा mwअगरiex_ie_types_htinfo *ht_info;
	u8 *pos = (u8 *) adhoc_start +
			माप(काष्ठा host_cmd_ds_802_11_ad_hoc_start);

	अगर (!adapter)
		वापस -1;

	cmd->command = cpu_to_le16(HostCmd_CMD_802_11_AD_HOC_START);

	bss_desc = &priv->curr_bss_params.bss_descriptor;
	priv->attempted_bss_desc = bss_desc;

	/*
	 * Fill in the parameters क्रम 2 data काष्ठाures:
	 *   1. काष्ठा host_cmd_ds_802_11_ad_hoc_start command
	 *   2. bss_desc
	 * Driver will fill up SSID, bss_mode,IBSS param, Physical Param,
	 * probe delay, and Cap info.
	 * Firmware will fill up beacon period, Basic rates
	 * and operational rates.
	 */

	स_रखो(adhoc_start->ssid, 0, IEEE80211_MAX_SSID_LEN);

	अगर (req_ssid->ssid_len > IEEE80211_MAX_SSID_LEN)
		req_ssid->ssid_len = IEEE80211_MAX_SSID_LEN;
	स_नकल(adhoc_start->ssid, req_ssid->ssid, req_ssid->ssid_len);

	mwअगरiex_dbg(adapter, INFO, "info: ADHOC_S_CMD: SSID = %s\n",
		    adhoc_start->ssid);

	स_रखो(bss_desc->ssid.ssid, 0, IEEE80211_MAX_SSID_LEN);
	स_नकल(bss_desc->ssid.ssid, req_ssid->ssid, req_ssid->ssid_len);

	bss_desc->ssid.ssid_len = req_ssid->ssid_len;

	/* Set the BSS mode */
	adhoc_start->bss_mode = HostCmd_BSS_MODE_IBSS;
	bss_desc->bss_mode = NL80211_IFTYPE_ADHOC;
	adhoc_start->beacon_period = cpu_to_le16(priv->beacon_period);
	bss_desc->beacon_period = priv->beacon_period;

	/* Set Physical param set */
/* Parameter IE Id */
#घोषणा DS_PARA_IE_ID   3
/* Parameter IE length */
#घोषणा DS_PARA_IE_LEN  1

	adhoc_start->phy_param_set.ds_param_set.element_id = DS_PARA_IE_ID;
	adhoc_start->phy_param_set.ds_param_set.len = DS_PARA_IE_LEN;

	अगर (!mwअगरiex_get_cfp(priv, adapter->adhoc_start_band,
			     (u16) priv->adhoc_channel, 0)) अणु
		काष्ठा mwअगरiex_chan_freq_घातer *cfp;
		cfp = mwअगरiex_get_cfp(priv, adapter->adhoc_start_band,
				      FIRST_VALID_CHANNEL, 0);
		अगर (cfp)
			priv->adhoc_channel = (u8) cfp->channel;
	पूर्ण

	अगर (!priv->adhoc_channel) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "ADHOC_S_CMD: adhoc_channel cannot be 0\n");
		वापस -1;
	पूर्ण

	mwअगरiex_dbg(adapter, INFO,
		    "info: ADHOC_S_CMD: creating ADHOC on channel %d\n",
		    priv->adhoc_channel);

	priv->curr_bss_params.bss_descriptor.channel = priv->adhoc_channel;
	priv->curr_bss_params.band = adapter->adhoc_start_band;

	bss_desc->channel = priv->adhoc_channel;
	adhoc_start->phy_param_set.ds_param_set.current_chan =
		priv->adhoc_channel;

	स_नकल(&bss_desc->phy_param_set, &adhoc_start->phy_param_set,
	       माप(जोड़ ieee_types_phy_param_set));

	/* Set IBSS param set */
/* IBSS parameter IE Id */
#घोषणा IBSS_PARA_IE_ID   6
/* IBSS parameter IE length */
#घोषणा IBSS_PARA_IE_LEN  2

	adhoc_start->ss_param_set.ibss_param_set.element_id = IBSS_PARA_IE_ID;
	adhoc_start->ss_param_set.ibss_param_set.len = IBSS_PARA_IE_LEN;
	adhoc_start->ss_param_set.ibss_param_set.atim_winकरोw
					= cpu_to_le16(priv->atim_winकरोw);
	स_नकल(&bss_desc->ss_param_set, &adhoc_start->ss_param_set,
	       माप(जोड़ ieee_types_ss_param_set));

	/* Set Capability info */
	bss_desc->cap_info_biपंचांगap |= WLAN_CAPABILITY_IBSS;
	पंचांगp_cap = WLAN_CAPABILITY_IBSS;

	/* Set up privacy in bss_desc */
	अगर (priv->sec_info.encryption_mode) अणु
		/* Ad-Hoc capability privacy on */
		mwअगरiex_dbg(adapter, INFO,
			    "info: ADHOC_S_CMD: wep_status set privacy to WEP\n");
		bss_desc->privacy = MWIFIEX_802_11_PRIV_FILTER_8021X_WEP;
		पंचांगp_cap |= WLAN_CAPABILITY_PRIVACY;
	पूर्ण अन्यथा अणु
		mwअगरiex_dbg(adapter, INFO,
			    "info: ADHOC_S_CMD: wep_status NOT set,\t"
			    "setting privacy to ACCEPT ALL\n");
		bss_desc->privacy = MWIFIEX_802_11_PRIV_FILTER_ACCEPT_ALL;
	पूर्ण

	स_रखो(adhoc_start->data_rate, 0, माप(adhoc_start->data_rate));
	mwअगरiex_get_active_data_rates(priv, adhoc_start->data_rate);
	अगर ((adapter->adhoc_start_band & BAND_G) &&
	    (priv->curr_pkt_filter & HostCmd_ACT_MAC_ADHOC_G_PROTECTION_ON)) अणु
		अगर (mwअगरiex_send_cmd(priv, HostCmd_CMD_MAC_CONTROL,
				     HostCmd_ACT_GEN_SET, 0,
				     &priv->curr_pkt_filter, false)) अणु
			mwअगरiex_dbg(adapter, ERROR,
				    "ADHOC_S_CMD: G Protection config failed\n");
			वापस -1;
		पूर्ण
	पूर्ण
	/* Find the last non zero */
	क्रम (i = 0; i < माप(adhoc_start->data_rate); i++)
		अगर (!adhoc_start->data_rate[i])
			अवरोध;

	priv->curr_bss_params.num_of_rates = i;

	/* Copy the ad-hoc creating rates पूर्णांकo Current BSS rate काष्ठाure */
	स_नकल(&priv->curr_bss_params.data_rates,
	       &adhoc_start->data_rate, priv->curr_bss_params.num_of_rates);

	mwअगरiex_dbg(adapter, INFO, "info: ADHOC_S_CMD: rates=%4ph\n",
		    adhoc_start->data_rate);

	mwअगरiex_dbg(adapter, INFO, "info: ADHOC_S_CMD: AD-HOC Start command is ready\n");

	अगर (IS_SUPPORT_MULTI_BANDS(adapter)) अणु
		/* Append a channel TLV */
		chan_tlv = (काष्ठा mwअगरiex_ie_types_chan_list_param_set *) pos;
		chan_tlv->header.type = cpu_to_le16(TLV_TYPE_CHANLIST);
		chan_tlv->header.len =
			cpu_to_le16(माप(काष्ठा mwअगरiex_chan_scan_param_set));

		स_रखो(chan_tlv->chan_scan_param, 0x00,
		       माप(काष्ठा mwअगरiex_chan_scan_param_set));
		chan_tlv->chan_scan_param[0].chan_number =
			(u8) priv->curr_bss_params.bss_descriptor.channel;

		mwअगरiex_dbg(adapter, INFO, "info: ADHOC_S_CMD: TLV Chan = %d\n",
			    chan_tlv->chan_scan_param[0].chan_number);

		chan_tlv->chan_scan_param[0].radio_type
		       = mwअगरiex_band_to_radio_type(priv->curr_bss_params.band);
		अगर (adapter->adhoc_start_band & BAND_GN ||
		    adapter->adhoc_start_band & BAND_AN) अणु
			अगर (adapter->sec_chan_offset ==
					    IEEE80211_HT_PARAM_CHA_SEC_ABOVE)
				chan_tlv->chan_scan_param[0].radio_type |=
					(IEEE80211_HT_PARAM_CHA_SEC_ABOVE << 4);
			अन्यथा अगर (adapter->sec_chan_offset ==
					    IEEE80211_HT_PARAM_CHA_SEC_BELOW)
				chan_tlv->chan_scan_param[0].radio_type |=
					(IEEE80211_HT_PARAM_CHA_SEC_BELOW << 4);
		पूर्ण
		mwअगरiex_dbg(adapter, INFO, "info: ADHOC_S_CMD: TLV Band = %d\n",
			    chan_tlv->chan_scan_param[0].radio_type);
		pos += माप(chan_tlv->header) +
			माप(काष्ठा mwअगरiex_chan_scan_param_set);
		cmd_append_size +=
			माप(chan_tlv->header) +
			माप(काष्ठा mwअगरiex_chan_scan_param_set);
	पूर्ण

	/* Append venकरोr specअगरic IE TLV */
	cmd_append_size += mwअगरiex_cmd_append_vsie_tlv(priv,
				MWIFIEX_VSIE_MASK_ADHOC, &pos);

	अगर (priv->sec_info.wpa_enabled) अणु
		rsn_ie_len = mwअगरiex_append_rsn_ie_wpa_wpa2(priv, &pos);
		अगर (rsn_ie_len == -1)
			वापस -1;
		cmd_append_size += rsn_ie_len;
	पूर्ण

	अगर (adapter->adhoc_11n_enabled) अणु
		/* Fill HT CAPABILITY */
		ht_cap = (काष्ठा mwअगरiex_ie_types_htcap *) pos;
		स_रखो(ht_cap, 0, माप(काष्ठा mwअगरiex_ie_types_htcap));
		ht_cap->header.type = cpu_to_le16(WLAN_EID_HT_CAPABILITY);
		ht_cap->header.len =
		       cpu_to_le16(माप(काष्ठा ieee80211_ht_cap));
		radio_type = mwअगरiex_band_to_radio_type(
					priv->adapter->config_bands);
		mwअगरiex_fill_cap_info(priv, radio_type, &ht_cap->ht_cap);

		अगर (adapter->sec_chan_offset ==
					IEEE80211_HT_PARAM_CHA_SEC_NONE) अणु
			u16 पंचांगp_ht_cap;

			पंचांगp_ht_cap = le16_to_cpu(ht_cap->ht_cap.cap_info);
			पंचांगp_ht_cap &= ~IEEE80211_HT_CAP_SUP_WIDTH_20_40;
			पंचांगp_ht_cap &= ~IEEE80211_HT_CAP_SGI_40;
			ht_cap->ht_cap.cap_info = cpu_to_le16(पंचांगp_ht_cap);
		पूर्ण

		pos += माप(काष्ठा mwअगरiex_ie_types_htcap);
		cmd_append_size += माप(काष्ठा mwअगरiex_ie_types_htcap);

		/* Fill HT INFORMATION */
		ht_info = (काष्ठा mwअगरiex_ie_types_htinfo *) pos;
		स_रखो(ht_info, 0, माप(काष्ठा mwअगरiex_ie_types_htinfo));
		ht_info->header.type = cpu_to_le16(WLAN_EID_HT_OPERATION);
		ht_info->header.len =
			cpu_to_le16(माप(काष्ठा ieee80211_ht_operation));

		ht_info->ht_oper.primary_chan =
			(u8) priv->curr_bss_params.bss_descriptor.channel;
		अगर (adapter->sec_chan_offset) अणु
			ht_info->ht_oper.ht_param = adapter->sec_chan_offset;
			ht_info->ht_oper.ht_param |=
					IEEE80211_HT_PARAM_CHAN_WIDTH_ANY;
		पूर्ण
		ht_info->ht_oper.operation_mode =
		     cpu_to_le16(IEEE80211_HT_OP_MODE_NON_GF_STA_PRSNT);
		ht_info->ht_oper.basic_set[0] = 0xff;
		pos += माप(काष्ठा mwअगरiex_ie_types_htinfo);
		cmd_append_size +=
				माप(काष्ठा mwअगरiex_ie_types_htinfo);
	पूर्ण

	cmd->size =
		cpu_to_le16((u16)(माप(काष्ठा host_cmd_ds_802_11_ad_hoc_start)
				  + S_DS_GEN + cmd_append_size));

	अगर (adapter->adhoc_start_band == BAND_B)
		पंचांगp_cap &= ~WLAN_CAPABILITY_SHORT_SLOT_TIME;
	अन्यथा
		पंचांगp_cap |= WLAN_CAPABILITY_SHORT_SLOT_TIME;

	adhoc_start->cap_info_biपंचांगap = cpu_to_le16(पंचांगp_cap);

	वापस 0;
पूर्ण

/*
 * This function prepares command क्रम ad-hoc join.
 *
 * Most of the parameters are set up by copying from the target BSS descriptor
 * from the scan response.
 *
 * In addition, the following TLVs are added -
 *      - Channel TLV
 *      - Venकरोr specअगरic IE
 *      - WPA/WPA2 IE
 *      - 11n IE
 *
 * Preparation also includes -
 *      - Setting command ID and proper size
 *      - Ensuring correct endian-ness
 */
पूर्णांक
mwअगरiex_cmd_802_11_ad_hoc_join(काष्ठा mwअगरiex_निजी *priv,
			       काष्ठा host_cmd_ds_command *cmd,
			       काष्ठा mwअगरiex_bssdescriptor *bss_desc)
अणु
	पूर्णांक rsn_ie_len = 0;
	काष्ठा host_cmd_ds_802_11_ad_hoc_join *adhoc_join =
		&cmd->params.adhoc_join;
	काष्ठा mwअगरiex_ie_types_chan_list_param_set *chan_tlv;
	u32 cmd_append_size = 0;
	u16 पंचांगp_cap;
	u32 i, rates_size = 0;
	u16 curr_pkt_filter;
	u8 *pos =
		(u8 *) adhoc_join +
		माप(काष्ठा host_cmd_ds_802_11_ad_hoc_join);

/* Use G protection */
#घोषणा USE_G_PROTECTION        0x02
	अगर (bss_desc->erp_flags & USE_G_PROTECTION) अणु
		curr_pkt_filter =
			priv->
			curr_pkt_filter | HostCmd_ACT_MAC_ADHOC_G_PROTECTION_ON;

		अगर (mwअगरiex_send_cmd(priv, HostCmd_CMD_MAC_CONTROL,
				     HostCmd_ACT_GEN_SET, 0,
				     &curr_pkt_filter, false)) अणु
			mwअगरiex_dbg(priv->adapter, ERROR,
				    "ADHOC_J_CMD: G Protection config failed\n");
			वापस -1;
		पूर्ण
	पूर्ण

	priv->attempted_bss_desc = bss_desc;

	cmd->command = cpu_to_le16(HostCmd_CMD_802_11_AD_HOC_JOIN);

	adhoc_join->bss_descriptor.bss_mode = HostCmd_BSS_MODE_IBSS;

	adhoc_join->bss_descriptor.beacon_period
		= cpu_to_le16(bss_desc->beacon_period);

	स_नकल(&adhoc_join->bss_descriptor.bssid,
	       &bss_desc->mac_address, ETH_ALEN);

	स_नकल(&adhoc_join->bss_descriptor.ssid,
	       &bss_desc->ssid.ssid, bss_desc->ssid.ssid_len);

	स_नकल(&adhoc_join->bss_descriptor.phy_param_set,
	       &bss_desc->phy_param_set,
	       माप(जोड़ ieee_types_phy_param_set));

	स_नकल(&adhoc_join->bss_descriptor.ss_param_set,
	       &bss_desc->ss_param_set, माप(जोड़ ieee_types_ss_param_set));

	पंचांगp_cap = bss_desc->cap_info_biपंचांगap;

	पंचांगp_cap &= CAPINFO_MASK;

	mwअगरiex_dbg(priv->adapter, INFO,
		    "info: ADHOC_J_CMD: tmp_cap=%4X CAPINFO_MASK=%4lX\n",
		    पंचांगp_cap, CAPINFO_MASK);

	/* Inक्रमmation on BSSID descriptor passed to FW */
	mwअगरiex_dbg(priv->adapter, INFO,
		    "info: ADHOC_J_CMD: BSSID=%pM, SSID='%s'\n",
		    adhoc_join->bss_descriptor.bssid,
		    adhoc_join->bss_descriptor.ssid);

	क्रम (i = 0; i < MWIFIEX_SUPPORTED_RATES &&
		    bss_desc->supported_rates[i]; i++)
		;
	rates_size = i;

	/* Copy Data Rates from the Rates recorded in scan response */
	स_रखो(adhoc_join->bss_descriptor.data_rates, 0,
	       माप(adhoc_join->bss_descriptor.data_rates));
	स_नकल(adhoc_join->bss_descriptor.data_rates,
	       bss_desc->supported_rates, rates_size);

	/* Copy the adhoc join rates पूर्णांकo Current BSS state काष्ठाure */
	priv->curr_bss_params.num_of_rates = rates_size;
	स_नकल(&priv->curr_bss_params.data_rates, bss_desc->supported_rates,
	       rates_size);

	/* Copy the channel inक्रमmation */
	priv->curr_bss_params.bss_descriptor.channel = bss_desc->channel;
	priv->curr_bss_params.band = (u8) bss_desc->bss_band;

	अगर (priv->sec_info.wep_enabled || priv->sec_info.wpa_enabled)
		पंचांगp_cap |= WLAN_CAPABILITY_PRIVACY;

	अगर (IS_SUPPORT_MULTI_BANDS(priv->adapter)) अणु
		/* Append a channel TLV */
		chan_tlv = (काष्ठा mwअगरiex_ie_types_chan_list_param_set *) pos;
		chan_tlv->header.type = cpu_to_le16(TLV_TYPE_CHANLIST);
		chan_tlv->header.len =
			cpu_to_le16(माप(काष्ठा mwअगरiex_chan_scan_param_set));

		स_रखो(chan_tlv->chan_scan_param, 0x00,
		       माप(काष्ठा mwअगरiex_chan_scan_param_set));
		chan_tlv->chan_scan_param[0].chan_number =
			(bss_desc->phy_param_set.ds_param_set.current_chan);
		mwअगरiex_dbg(priv->adapter, INFO, "info: ADHOC_J_CMD: TLV Chan=%d\n",
			    chan_tlv->chan_scan_param[0].chan_number);

		chan_tlv->chan_scan_param[0].radio_type =
			mwअगरiex_band_to_radio_type((u8) bss_desc->bss_band);

		mwअगरiex_dbg(priv->adapter, INFO, "info: ADHOC_J_CMD: TLV Band=%d\n",
			    chan_tlv->chan_scan_param[0].radio_type);
		pos += माप(chan_tlv->header) +
				माप(काष्ठा mwअगरiex_chan_scan_param_set);
		cmd_append_size += माप(chan_tlv->header) +
				माप(काष्ठा mwअगरiex_chan_scan_param_set);
	पूर्ण

	अगर (priv->sec_info.wpa_enabled)
		rsn_ie_len = mwअगरiex_append_rsn_ie_wpa_wpa2(priv, &pos);
	अगर (rsn_ie_len == -1)
		वापस -1;
	cmd_append_size += rsn_ie_len;

	अगर (ISSUPP_11NENABLED(priv->adapter->fw_cap_info))
		cmd_append_size += mwअगरiex_cmd_append_11n_tlv(priv,
			bss_desc, &pos);

	/* Append venकरोr specअगरic IE TLV */
	cmd_append_size += mwअगरiex_cmd_append_vsie_tlv(priv,
			MWIFIEX_VSIE_MASK_ADHOC, &pos);

	cmd->size = cpu_to_le16
		((u16) (माप(काष्ठा host_cmd_ds_802_11_ad_hoc_join)
			+ S_DS_GEN + cmd_append_size));

	adhoc_join->bss_descriptor.cap_info_biपंचांगap = cpu_to_le16(पंचांगp_cap);

	वापस 0;
पूर्ण

/*
 * This function handles the command response of ad-hoc start and
 * ad-hoc join.
 *
 * The function generates a device-connected event to notअगरy
 * the applications, in हाल of successful ad-hoc start/join, and
 * saves the beacon buffer.
 */
पूर्णांक mwअगरiex_ret_802_11_ad_hoc(काष्ठा mwअगरiex_निजी *priv,
			      काष्ठा host_cmd_ds_command *resp)
अणु
	पूर्णांक ret = 0;
	काष्ठा mwअगरiex_adapter *adapter = priv->adapter;
	काष्ठा host_cmd_ds_802_11_ad_hoc_start_result *start_result =
				&resp->params.start_result;
	काष्ठा host_cmd_ds_802_11_ad_hoc_join_result *join_result =
				&resp->params.join_result;
	काष्ठा mwअगरiex_bssdescriptor *bss_desc;
	u16 cmd = le16_to_cpu(resp->command);
	u8 result;

	अगर (!priv->attempted_bss_desc) अणु
		mwअगरiex_dbg(priv->adapter, ERROR,
			    "ADHOC_RESP: failed, association terminated by host\n");
		जाओ करोne;
	पूर्ण

	अगर (cmd == HostCmd_CMD_802_11_AD_HOC_START)
		result = start_result->result;
	अन्यथा
		result = join_result->result;

	bss_desc = priv->attempted_bss_desc;

	/* Join result code 0 --> SUCCESS */
	अगर (result) अणु
		mwअगरiex_dbg(priv->adapter, ERROR, "ADHOC_RESP: failed\n");
		अगर (priv->media_connected)
			mwअगरiex_reset_connect_state(priv, result, true);

		स_रखो(&priv->curr_bss_params.bss_descriptor,
		       0x00, माप(काष्ठा mwअगरiex_bssdescriptor));

		ret = -1;
		जाओ करोne;
	पूर्ण

	/* Send a Media Connected event, according to the Spec */
	priv->media_connected = true;

	अगर (le16_to_cpu(resp->command) == HostCmd_CMD_802_11_AD_HOC_START) अणु
		mwअगरiex_dbg(priv->adapter, INFO, "info: ADHOC_S_RESP %s\n",
			    bss_desc->ssid.ssid);

		/* Update the created network descriptor with the new BSSID */
		स_नकल(bss_desc->mac_address,
		       start_result->bssid, ETH_ALEN);

		priv->adhoc_state = ADHOC_STARTED;
	पूर्ण अन्यथा अणु
		/*
		 * Now the join cmd should be successful.
		 * If BSSID has changed use SSID to compare instead of BSSID
		 */
		mwअगरiex_dbg(priv->adapter, INFO,
			    "info: ADHOC_J_RESP %s\n",
			    bss_desc->ssid.ssid);

		/*
		 * Make a copy of current BSSID descriptor, only needed क्रम
		 * join since the current descriptor is alपढ़ोy being used
		 * क्रम adhoc start
		 */
		स_नकल(&priv->curr_bss_params.bss_descriptor,
		       bss_desc, माप(काष्ठा mwअगरiex_bssdescriptor));

		priv->adhoc_state = ADHOC_JOINED;
	पूर्ण

	mwअगरiex_dbg(priv->adapter, INFO, "info: ADHOC_RESP: channel = %d\n",
		    priv->adhoc_channel);
	mwअगरiex_dbg(priv->adapter, INFO, "info: ADHOC_RESP: BSSID = %pM\n",
		    priv->curr_bss_params.bss_descriptor.mac_address);

	अगर (!netअगर_carrier_ok(priv->netdev))
		netअगर_carrier_on(priv->netdev);
	mwअगरiex_wake_up_net_dev_queue(priv->netdev, adapter);

	mwअगरiex_save_curr_bcn(priv);

करोne:
	/* Need to indicate IOCTL complete */
	अगर (adapter->curr_cmd->रुको_q_enabled) अणु
		अगर (ret)
			adapter->cmd_रुको_q.status = -1;
		अन्यथा
			adapter->cmd_रुको_q.status = 0;

	पूर्ण

	वापस ret;
पूर्ण

/*
 * This function associates to a specअगरic BSS discovered in a scan.
 *
 * It clears any past association response stored क्रम application
 * retrieval and calls the command preparation routine to send the
 * command to firmware.
 */
पूर्णांक mwअगरiex_associate(काष्ठा mwअगरiex_निजी *priv,
		      काष्ठा mwअगरiex_bssdescriptor *bss_desc)
अणु
	/* Return error अगर the adapter is not STA role or table entry
	 * is not marked as infra.
	 */
	अगर ((GET_BSS_ROLE(priv) != MWIFIEX_BSS_ROLE_STA) ||
	    (bss_desc->bss_mode != NL80211_IFTYPE_STATION))
		वापस -1;

	अगर (ISSUPP_11ACENABLED(priv->adapter->fw_cap_info) &&
	    !bss_desc->disable_11n && !bss_desc->disable_11ac &&
	    priv->adapter->config_bands & BAND_AAC)
		mwअगरiex_set_11ac_ba_params(priv);
	अन्यथा
		mwअगरiex_set_ba_params(priv);

	/* Clear any past association response stored क्रम application
	   retrieval */
	priv->assoc_rsp_size = 0;

	वापस mwअगरiex_send_cmd(priv, HostCmd_CMD_802_11_ASSOCIATE,
				HostCmd_ACT_GEN_SET, 0, bss_desc, true);
पूर्ण

/*
 * This function starts an ad-hoc network.
 *
 * It calls the command preparation routine to send the command to firmware.
 */
पूर्णांक
mwअगरiex_adhoc_start(काष्ठा mwअगरiex_निजी *priv,
		    काष्ठा cfg80211_ssid *adhoc_ssid)
अणु
	mwअगरiex_dbg(priv->adapter, INFO, "info: Adhoc Channel = %d\n",
		    priv->adhoc_channel);
	mwअगरiex_dbg(priv->adapter, INFO, "info: curr_bss_params.channel = %d\n",
		    priv->curr_bss_params.bss_descriptor.channel);
	mwअगरiex_dbg(priv->adapter, INFO, "info: curr_bss_params.band = %d\n",
		    priv->curr_bss_params.band);

	अगर (ISSUPP_11ACENABLED(priv->adapter->fw_cap_info) &&
	    priv->adapter->config_bands & BAND_AAC)
		mwअगरiex_set_11ac_ba_params(priv);
	अन्यथा
		mwअगरiex_set_ba_params(priv);

	वापस mwअगरiex_send_cmd(priv, HostCmd_CMD_802_11_AD_HOC_START,
				HostCmd_ACT_GEN_SET, 0, adhoc_ssid, true);
पूर्ण

/*
 * This function joins an ad-hoc network found in a previous scan.
 *
 * It calls the command preparation routine to send the command to firmware,
 * अगर alपढ़ोy not connected to the requested SSID.
 */
पूर्णांक mwअगरiex_adhoc_join(काष्ठा mwअगरiex_निजी *priv,
		       काष्ठा mwअगरiex_bssdescriptor *bss_desc)
अणु
	mwअगरiex_dbg(priv->adapter, INFO,
		    "info: adhoc join: curr_bss ssid =%s\n",
		    priv->curr_bss_params.bss_descriptor.ssid.ssid);
	mwअगरiex_dbg(priv->adapter, INFO,
		    "info: adhoc join: curr_bss ssid_len =%u\n",
		    priv->curr_bss_params.bss_descriptor.ssid.ssid_len);
	mwअगरiex_dbg(priv->adapter, INFO, "info: adhoc join: ssid =%s\n",
		    bss_desc->ssid.ssid);
	mwअगरiex_dbg(priv->adapter, INFO, "info: adhoc join: ssid_len =%u\n",
		    bss_desc->ssid.ssid_len);

	/* Check अगर the requested SSID is alपढ़ोy joined */
	अगर (priv->curr_bss_params.bss_descriptor.ssid.ssid_len &&
	    !mwअगरiex_ssid_cmp(&bss_desc->ssid,
			      &priv->curr_bss_params.bss_descriptor.ssid) &&
	    (priv->curr_bss_params.bss_descriptor.bss_mode ==
							NL80211_IFTYPE_ADHOC)) अणु
		mwअगरiex_dbg(priv->adapter, INFO,
			    "info: ADHOC_J_CMD: new ad-hoc SSID\t"
			    "is the same as current; not attempting to re-join\n");
		वापस -1;
	पूर्ण

	अगर (ISSUPP_11ACENABLED(priv->adapter->fw_cap_info) &&
	    !bss_desc->disable_11n && !bss_desc->disable_11ac &&
	    priv->adapter->config_bands & BAND_AAC)
		mwअगरiex_set_11ac_ba_params(priv);
	अन्यथा
		mwअगरiex_set_ba_params(priv);

	mwअगरiex_dbg(priv->adapter, INFO,
		    "info: curr_bss_params.channel = %d\n",
		    priv->curr_bss_params.bss_descriptor.channel);
	mwअगरiex_dbg(priv->adapter, INFO,
		    "info: curr_bss_params.band = %c\n",
		    priv->curr_bss_params.band);

	वापस mwअगरiex_send_cmd(priv, HostCmd_CMD_802_11_AD_HOC_JOIN,
				HostCmd_ACT_GEN_SET, 0, bss_desc, true);
पूर्ण

/*
 * This function deauthenticates/disconnects from infra network by sending
 * deauthentication request.
 */
अटल पूर्णांक mwअगरiex_deauthenticate_infra(काष्ठा mwअगरiex_निजी *priv, u8 *mac)
अणु
	u8 mac_address[ETH_ALEN];
	पूर्णांक ret;

	अगर (!mac || is_zero_ether_addr(mac))
		स_नकल(mac_address,
		       priv->curr_bss_params.bss_descriptor.mac_address,
		       ETH_ALEN);
	अन्यथा
		स_नकल(mac_address, mac, ETH_ALEN);

	ret = mwअगरiex_send_cmd(priv, HostCmd_CMD_802_11_DEAUTHENTICATE,
			       HostCmd_ACT_GEN_SET, 0, mac_address, true);

	वापस ret;
पूर्ण

/*
 * This function deauthenticates/disconnects from a BSS.
 *
 * In हाल of infra made, it sends deauthentication request, and
 * in हाल of ad-hoc mode, a stop network request is sent to the firmware.
 * In AP mode, a command to stop bss is sent to firmware.
 */
पूर्णांक mwअगरiex_deauthenticate(काष्ठा mwअगरiex_निजी *priv, u8 *mac)
अणु
	पूर्णांक ret = 0;

	अगर (!priv->media_connected)
		वापस 0;

	चयन (priv->bss_mode) अणु
	हाल NL80211_IFTYPE_STATION:
	हाल NL80211_IFTYPE_P2P_CLIENT:
		ret = mwअगरiex_deauthenticate_infra(priv, mac);
		अगर (ret)
			cfg80211_disconnected(priv->netdev, 0, शून्य, 0,
					      true, GFP_KERNEL);
		अवरोध;
	हाल NL80211_IFTYPE_ADHOC:
		वापस mwअगरiex_send_cmd(priv, HostCmd_CMD_802_11_AD_HOC_STOP,
					HostCmd_ACT_GEN_SET, 0, शून्य, true);
	हाल NL80211_IFTYPE_AP:
		वापस mwअगरiex_send_cmd(priv, HostCmd_CMD_UAP_BSS_STOP,
					HostCmd_ACT_GEN_SET, 0, शून्य, true);
	शेष:
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

/* This function deauthenticates/disconnects from all BSS. */
व्योम mwअगरiex_deauthenticate_all(काष्ठा mwअगरiex_adapter *adapter)
अणु
	काष्ठा mwअगरiex_निजी *priv;
	पूर्णांक i;

	क्रम (i = 0; i < adapter->priv_num; i++) अणु
		priv = adapter->priv[i];
		अगर (priv)
			mwअगरiex_deauthenticate(priv, शून्य);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(mwअगरiex_deauthenticate_all);

/*
 * This function converts band to radio type used in channel TLV.
 */
u8
mwअगरiex_band_to_radio_type(u8 band)
अणु
	चयन (band) अणु
	हाल BAND_A:
	हाल BAND_AN:
	हाल BAND_A | BAND_AN:
	हाल BAND_A | BAND_AN | BAND_AAC:
		वापस HostCmd_SCAN_RADIO_TYPE_A;
	हाल BAND_B:
	हाल BAND_G:
	हाल BAND_B | BAND_G:
	शेष:
		वापस HostCmd_SCAN_RADIO_TYPE_BG;
	पूर्ण
पूर्ण
