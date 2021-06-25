<शैली गुरु>
/*
 * NXP Wireless LAN device driver: management IE handling- setting and
 * deleting IE.
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

#समावेश "main.h"

/* This function checks अगर current IE index is used by any on other पूर्णांकerface.
 * Return: -1: yes, current IE index is used by someone अन्यथा.
 *          0: no, current IE index is NOT used by other पूर्णांकerface.
 */
अटल पूर्णांक
mwअगरiex_ie_index_used_by_other_पूर्णांकf(काष्ठा mwअगरiex_निजी *priv, u16 idx)
अणु
	पूर्णांक i;
	काष्ठा mwअगरiex_adapter *adapter = priv->adapter;
	काष्ठा mwअगरiex_ie *ie;

	क्रम (i = 0; i < adapter->priv_num; i++) अणु
		अगर (adapter->priv[i] != priv) अणु
			ie = &adapter->priv[i]->mgmt_ie[idx];
			अगर (ie->mgmt_subtype_mask && ie->ie_length)
				वापस -1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* Get unused IE index. This index will be used क्रम setting new IE */
अटल पूर्णांक
mwअगरiex_ie_get_स्वतःidx(काष्ठा mwअगरiex_निजी *priv, u16 subtype_mask,
		       काष्ठा mwअगरiex_ie *ie, u16 *index)
अणु
	u16 mask, len, i;

	क्रम (i = 0; i < priv->adapter->max_mgmt_ie_index; i++) अणु
		mask = le16_to_cpu(priv->mgmt_ie[i].mgmt_subtype_mask);
		len = le16_to_cpu(ie->ie_length);

		अगर (mask == MWIFIEX_AUTO_IDX_MASK)
			जारी;

		अगर (mask == subtype_mask) अणु
			अगर (len > IEEE_MAX_IE_SIZE)
				जारी;

			*index = i;
			वापस 0;
		पूर्ण

		अगर (!priv->mgmt_ie[i].ie_length) अणु
			अगर (mwअगरiex_ie_index_used_by_other_पूर्णांकf(priv, i))
				जारी;

			*index = i;
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -1;
पूर्ण

/* This function prepares IE data buffer क्रम command to be sent to FW */
अटल पूर्णांक
mwअगरiex_update_स्वतःindex_ies(काष्ठा mwअगरiex_निजी *priv,
			     काष्ठा mwअगरiex_ie_list *ie_list)
अणु
	u16 travel_len, index, mask;
	s16 input_len, tlv_len;
	काष्ठा mwअगरiex_ie *ie;
	u8 *पंचांगp;

	input_len = le16_to_cpu(ie_list->len);
	travel_len = माप(काष्ठा mwअगरiex_ie_types_header);

	ie_list->len = 0;

	जबतक (input_len >= माप(काष्ठा mwअगरiex_ie_types_header)) अणु
		ie = (काष्ठा mwअगरiex_ie *)(((u8 *)ie_list) + travel_len);
		tlv_len = le16_to_cpu(ie->ie_length);
		travel_len += tlv_len + MWIFIEX_IE_HDR_SIZE;

		अगर (input_len < tlv_len + MWIFIEX_IE_HDR_SIZE)
			वापस -1;
		index = le16_to_cpu(ie->ie_index);
		mask = le16_to_cpu(ie->mgmt_subtype_mask);

		अगर (index == MWIFIEX_AUTO_IDX_MASK) अणु
			/* स्वतःmatic addition */
			अगर (mwअगरiex_ie_get_स्वतःidx(priv, mask, ie, &index))
				वापस -1;
			अगर (index == MWIFIEX_AUTO_IDX_MASK)
				वापस -1;

			पंचांगp = (u8 *)&priv->mgmt_ie[index].ie_buffer;
			स_नकल(पंचांगp, &ie->ie_buffer, le16_to_cpu(ie->ie_length));
			priv->mgmt_ie[index].ie_length = ie->ie_length;
			priv->mgmt_ie[index].ie_index = cpu_to_le16(index);
			priv->mgmt_ie[index].mgmt_subtype_mask =
							cpu_to_le16(mask);

			ie->ie_index = cpu_to_le16(index);
		पूर्ण अन्यथा अणु
			अगर (mask != MWIFIEX_DELETE_MASK)
				वापस -1;
			/*
			 * Check अगर this index is being used on any
			 * other पूर्णांकerface.
			 */
			अगर (mwअगरiex_ie_index_used_by_other_पूर्णांकf(priv, index))
				वापस -1;

			ie->ie_length = 0;
			स_नकल(&priv->mgmt_ie[index], ie,
			       माप(काष्ठा mwअगरiex_ie));
		पूर्ण

		le16_unaligned_add_cpu(&ie_list->len,
				       le16_to_cpu(
					    priv->mgmt_ie[index].ie_length) +
				       MWIFIEX_IE_HDR_SIZE);
		input_len -= tlv_len + MWIFIEX_IE_HDR_SIZE;
	पूर्ण

	अगर (GET_BSS_ROLE(priv) == MWIFIEX_BSS_ROLE_UAP)
		वापस mwअगरiex_send_cmd(priv, HostCmd_CMD_UAP_SYS_CONFIG,
					HostCmd_ACT_GEN_SET,
					UAP_CUSTOM_IE_I, ie_list, true);

	वापस 0;
पूर्ण

/* Copy inभागidual custom IEs क्रम beacon, probe response and assoc response
 * and prepare single काष्ठाure क्रम IE setting.
 * This function also updates allocated IE indices from driver.
 */
अटल पूर्णांक
mwअगरiex_update_uap_custom_ie(काष्ठा mwअगरiex_निजी *priv,
			     काष्ठा mwअगरiex_ie *beacon_ie, u16 *beacon_idx,
			     काष्ठा mwअगरiex_ie *pr_ie, u16 *probe_idx,
			     काष्ठा mwअगरiex_ie *ar_ie, u16 *assoc_idx)
अणु
	काष्ठा mwअगरiex_ie_list *ap_custom_ie;
	u8 *pos;
	u16 len;
	पूर्णांक ret;

	ap_custom_ie = kzalloc(माप(*ap_custom_ie), GFP_KERNEL);
	अगर (!ap_custom_ie)
		वापस -ENOMEM;

	ap_custom_ie->type = cpu_to_le16(TLV_TYPE_MGMT_IE);
	pos = (u8 *)ap_custom_ie->ie_list;

	अगर (beacon_ie) अणु
		len = माप(काष्ठा mwअगरiex_ie) - IEEE_MAX_IE_SIZE +
		      le16_to_cpu(beacon_ie->ie_length);
		स_नकल(pos, beacon_ie, len);
		pos += len;
		le16_unaligned_add_cpu(&ap_custom_ie->len, len);
	पूर्ण
	अगर (pr_ie) अणु
		len = माप(काष्ठा mwअगरiex_ie) - IEEE_MAX_IE_SIZE +
		      le16_to_cpu(pr_ie->ie_length);
		स_नकल(pos, pr_ie, len);
		pos += len;
		le16_unaligned_add_cpu(&ap_custom_ie->len, len);
	पूर्ण
	अगर (ar_ie) अणु
		len = माप(काष्ठा mwअगरiex_ie) - IEEE_MAX_IE_SIZE +
		      le16_to_cpu(ar_ie->ie_length);
		स_नकल(pos, ar_ie, len);
		pos += len;
		le16_unaligned_add_cpu(&ap_custom_ie->len, len);
	पूर्ण

	ret = mwअगरiex_update_स्वतःindex_ies(priv, ap_custom_ie);

	pos = (u8 *)(&ap_custom_ie->ie_list[0].ie_index);
	अगर (beacon_ie && *beacon_idx == MWIFIEX_AUTO_IDX_MASK) अणु
		/* save beacon ie index after स्वतः-indexing */
		*beacon_idx = le16_to_cpu(ap_custom_ie->ie_list[0].ie_index);
		len = माप(*beacon_ie) - IEEE_MAX_IE_SIZE +
		      le16_to_cpu(beacon_ie->ie_length);
		pos += len;
	पूर्ण
	अगर (pr_ie && le16_to_cpu(pr_ie->ie_index) == MWIFIEX_AUTO_IDX_MASK) अणु
		/* save probe resp ie index after स्वतः-indexing */
		*probe_idx = *((u16 *)pos);
		len = माप(*pr_ie) - IEEE_MAX_IE_SIZE +
		      le16_to_cpu(pr_ie->ie_length);
		pos += len;
	पूर्ण
	अगर (ar_ie && le16_to_cpu(ar_ie->ie_index) == MWIFIEX_AUTO_IDX_MASK)
		/* save assoc resp ie index after स्वतः-indexing */
		*assoc_idx = *((u16 *)pos);

	kमुक्त(ap_custom_ie);
	वापस ret;
पूर्ण

/* This function checks अगर the venकरोr specअगरied IE is present in passed buffer
 * and copies it to mwअगरiex_ie काष्ठाure.
 * Function takes poपूर्णांकer to काष्ठा mwअगरiex_ie poपूर्णांकer as argument.
 * If the venकरोr specअगरied IE is present then memory is allocated क्रम
 * mwअगरiex_ie poपूर्णांकer and filled in with IE. Caller should take care of मुक्तing
 * this memory.
 */
अटल पूर्णांक mwअगरiex_update_vs_ie(स्थिर u8 *ies, पूर्णांक ies_len,
				काष्ठा mwअगरiex_ie **ie_ptr, u16 mask,
				अचिन्हित पूर्णांक oui, u8 oui_type)
अणु
	काष्ठा ieee_types_header *vs_ie;
	काष्ठा mwअगरiex_ie *ie = *ie_ptr;
	स्थिर u8 *venकरोr_ie;

	venकरोr_ie = cfg80211_find_venकरोr_ie(oui, oui_type, ies, ies_len);
	अगर (venकरोr_ie) अणु
		अगर (!*ie_ptr) अणु
			*ie_ptr = kzalloc(माप(काष्ठा mwअगरiex_ie),
					  GFP_KERNEL);
			अगर (!*ie_ptr)
				वापस -ENOMEM;
			ie = *ie_ptr;
		पूर्ण

		vs_ie = (काष्ठा ieee_types_header *)venकरोr_ie;
		अगर (le16_to_cpu(ie->ie_length) + vs_ie->len + 2 >
			IEEE_MAX_IE_SIZE)
			वापस -EINVAL;
		स_नकल(ie->ie_buffer + le16_to_cpu(ie->ie_length),
		       vs_ie, vs_ie->len + 2);
		le16_unaligned_add_cpu(&ie->ie_length, vs_ie->len + 2);
		ie->mgmt_subtype_mask = cpu_to_le16(mask);
		ie->ie_index = cpu_to_le16(MWIFIEX_AUTO_IDX_MASK);
	पूर्ण

	*ie_ptr = ie;
	वापस 0;
पूर्ण

/* This function parses beacon IEs, probe response IEs, association response IEs
 * from cfg80211_ap_settings->beacon and sets these IE to FW.
 */
अटल पूर्णांक mwअगरiex_set_mgmt_beacon_data_ies(काष्ठा mwअगरiex_निजी *priv,
					    काष्ठा cfg80211_beacon_data *data)
अणु
	काष्ठा mwअगरiex_ie *beacon_ie = शून्य, *pr_ie = शून्य, *ar_ie = शून्य;
	u16 beacon_idx = MWIFIEX_AUTO_IDX_MASK, pr_idx = MWIFIEX_AUTO_IDX_MASK;
	u16 ar_idx = MWIFIEX_AUTO_IDX_MASK;
	पूर्णांक ret = 0;

	अगर (data->beacon_ies && data->beacon_ies_len) अणु
		mwअगरiex_update_vs_ie(data->beacon_ies, data->beacon_ies_len,
				     &beacon_ie, MGMT_MASK_BEACON,
				     WLAN_OUI_MICROSOFT,
				     WLAN_OUI_TYPE_MICROSOFT_WPS);
		mwअगरiex_update_vs_ie(data->beacon_ies, data->beacon_ies_len,
				     &beacon_ie, MGMT_MASK_BEACON,
				     WLAN_OUI_WFA, WLAN_OUI_TYPE_WFA_P2P);
	पूर्ण

	अगर (data->proberesp_ies && data->proberesp_ies_len) अणु
		mwअगरiex_update_vs_ie(data->proberesp_ies,
				     data->proberesp_ies_len, &pr_ie,
				     MGMT_MASK_PROBE_RESP, WLAN_OUI_MICROSOFT,
				     WLAN_OUI_TYPE_MICROSOFT_WPS);
		mwअगरiex_update_vs_ie(data->proberesp_ies,
				     data->proberesp_ies_len, &pr_ie,
				     MGMT_MASK_PROBE_RESP,
				     WLAN_OUI_WFA, WLAN_OUI_TYPE_WFA_P2P);
	पूर्ण

	अगर (data->assocresp_ies && data->assocresp_ies_len) अणु
		mwअगरiex_update_vs_ie(data->assocresp_ies,
				     data->assocresp_ies_len, &ar_ie,
				     MGMT_MASK_ASSOC_RESP |
				     MGMT_MASK_REASSOC_RESP,
				     WLAN_OUI_MICROSOFT,
				     WLAN_OUI_TYPE_MICROSOFT_WPS);
		mwअगरiex_update_vs_ie(data->assocresp_ies,
				     data->assocresp_ies_len, &ar_ie,
				     MGMT_MASK_ASSOC_RESP |
				     MGMT_MASK_REASSOC_RESP, WLAN_OUI_WFA,
				     WLAN_OUI_TYPE_WFA_P2P);
	पूर्ण

	अगर (beacon_ie || pr_ie || ar_ie) अणु
		ret = mwअगरiex_update_uap_custom_ie(priv, beacon_ie,
						   &beacon_idx, pr_ie,
						   &pr_idx, ar_ie, &ar_idx);
		अगर (ret)
			जाओ करोne;
	पूर्ण

	priv->beacon_idx = beacon_idx;
	priv->proberesp_idx = pr_idx;
	priv->assocresp_idx = ar_idx;

करोne:
	kमुक्त(beacon_ie);
	kमुक्त(pr_ie);
	kमुक्त(ar_ie);

	वापस ret;
पूर्ण

/* This function parses  head and tail IEs, from cfg80211_beacon_data and sets
 * these IE to FW.
 */
अटल पूर्णांक mwअगरiex_uap_parse_tail_ies(काष्ठा mwअगरiex_निजी *priv,
				      काष्ठा cfg80211_beacon_data *info)
अणु
	काष्ठा mwअगरiex_ie *gen_ie;
	काष्ठा ieee_types_header *hdr;
	काष्ठा ieee80211_venकरोr_ie *venकरोrhdr;
	u16 gen_idx = MWIFIEX_AUTO_IDX_MASK, ie_len = 0;
	पूर्णांक left_len, parsed_len = 0;
	अचिन्हित पूर्णांक token_len;
	पूर्णांक err = 0;

	अगर (!info->tail || !info->tail_len)
		वापस 0;

	gen_ie = kzalloc(माप(*gen_ie), GFP_KERNEL);
	अगर (!gen_ie)
		वापस -ENOMEM;

	left_len = info->tail_len;

	/* Many IEs are generated in FW by parsing bss configuration.
	 * Let's not add them here; अन्यथा we may end up duplicating these IEs
	 */
	जबतक (left_len > माप(काष्ठा ieee_types_header)) अणु
		hdr = (व्योम *)(info->tail + parsed_len);
		token_len = hdr->len + माप(काष्ठा ieee_types_header);
		अगर (token_len > left_len) अणु
			err = -EINVAL;
			जाओ out;
		पूर्ण

		चयन (hdr->element_id) अणु
		हाल WLAN_EID_SSID:
		हाल WLAN_EID_SUPP_RATES:
		हाल WLAN_EID_COUNTRY:
		हाल WLAN_EID_PWR_CONSTRAINT:
		हाल WLAN_EID_ERP_INFO:
		हाल WLAN_EID_EXT_SUPP_RATES:
		हाल WLAN_EID_HT_CAPABILITY:
		हाल WLAN_EID_HT_OPERATION:
		हाल WLAN_EID_VHT_CAPABILITY:
		हाल WLAN_EID_VHT_OPERATION:
			अवरोध;
		हाल WLAN_EID_VENDOR_SPECIFIC:
			/* Skip only Microsoft WMM IE */
			अगर (cfg80211_find_venकरोr_ie(WLAN_OUI_MICROSOFT,
						    WLAN_OUI_TYPE_MICROSOFT_WMM,
						    (स्थिर u8 *)hdr,
						    token_len))
				अवरोध;
			fallthrough;
		शेष:
			अगर (ie_len + token_len > IEEE_MAX_IE_SIZE) अणु
				err = -EINVAL;
				जाओ out;
			पूर्ण
			स_नकल(gen_ie->ie_buffer + ie_len, hdr, token_len);
			ie_len += token_len;
			अवरोध;
		पूर्ण
		left_len -= token_len;
		parsed_len += token_len;
	पूर्ण

	/* parse only WPA venकरोr IE from tail, WMM IE is configured by
	 * bss_config command
	 */
	venकरोrhdr = (व्योम *)cfg80211_find_venकरोr_ie(WLAN_OUI_MICROSOFT,
						    WLAN_OUI_TYPE_MICROSOFT_WPA,
						    info->tail, info->tail_len);
	अगर (venकरोrhdr) अणु
		token_len = venकरोrhdr->len + माप(काष्ठा ieee_types_header);
		अगर (ie_len + token_len > IEEE_MAX_IE_SIZE) अणु
			err = -EINVAL;
			जाओ out;
		पूर्ण
		स_नकल(gen_ie->ie_buffer + ie_len, venकरोrhdr, token_len);
		ie_len += token_len;
	पूर्ण

	अगर (!ie_len)
		जाओ out;

	gen_ie->ie_index = cpu_to_le16(gen_idx);
	gen_ie->mgmt_subtype_mask = cpu_to_le16(MGMT_MASK_BEACON |
						MGMT_MASK_PROBE_RESP |
						MGMT_MASK_ASSOC_RESP);
	gen_ie->ie_length = cpu_to_le16(ie_len);

	अगर (mwअगरiex_update_uap_custom_ie(priv, gen_ie, &gen_idx, शून्य, शून्य,
					 शून्य, शून्य)) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण

	priv->gen_idx = gen_idx;

 out:
	kमुक्त(gen_ie);
	वापस err;
पूर्ण

/* This function parses dअगरferent IEs-head & tail IEs, beacon IEs,
 * probe response IEs, association response IEs from cfg80211_ap_settings
 * function and sets these IE to FW.
 */
पूर्णांक mwअगरiex_set_mgmt_ies(काष्ठा mwअगरiex_निजी *priv,
			 काष्ठा cfg80211_beacon_data *info)
अणु
	पूर्णांक ret;

	ret = mwअगरiex_uap_parse_tail_ies(priv, info);

	अगर (ret)
		वापस ret;

	वापस mwअगरiex_set_mgmt_beacon_data_ies(priv, info);
पूर्ण

/* This function हटाओs management IE set */
पूर्णांक mwअगरiex_del_mgmt_ies(काष्ठा mwअगरiex_निजी *priv)
अणु
	काष्ठा mwअगरiex_ie *beacon_ie = शून्य, *pr_ie = शून्य;
	काष्ठा mwअगरiex_ie *ar_ie = शून्य, *gen_ie = शून्य;
	पूर्णांक ret = 0;

	अगर (priv->gen_idx != MWIFIEX_AUTO_IDX_MASK) अणु
		gen_ie = kदो_स्मृति(माप(*gen_ie), GFP_KERNEL);
		अगर (!gen_ie)
			वापस -ENOMEM;

		gen_ie->ie_index = cpu_to_le16(priv->gen_idx);
		gen_ie->mgmt_subtype_mask = cpu_to_le16(MWIFIEX_DELETE_MASK);
		gen_ie->ie_length = 0;
		अगर (mwअगरiex_update_uap_custom_ie(priv, gen_ie, &priv->gen_idx,
						 शून्य, &priv->proberesp_idx,
						 शून्य, &priv->assocresp_idx)) अणु
			ret = -1;
			जाओ करोne;
		पूर्ण

		priv->gen_idx = MWIFIEX_AUTO_IDX_MASK;
	पूर्ण

	अगर (priv->beacon_idx != MWIFIEX_AUTO_IDX_MASK) अणु
		beacon_ie = kदो_स्मृति(माप(काष्ठा mwअगरiex_ie), GFP_KERNEL);
		अगर (!beacon_ie) अणु
			ret = -ENOMEM;
			जाओ करोne;
		पूर्ण
		beacon_ie->ie_index = cpu_to_le16(priv->beacon_idx);
		beacon_ie->mgmt_subtype_mask = cpu_to_le16(MWIFIEX_DELETE_MASK);
		beacon_ie->ie_length = 0;
	पूर्ण
	अगर (priv->proberesp_idx != MWIFIEX_AUTO_IDX_MASK) अणु
		pr_ie = kदो_स्मृति(माप(काष्ठा mwअगरiex_ie), GFP_KERNEL);
		अगर (!pr_ie) अणु
			ret = -ENOMEM;
			जाओ करोne;
		पूर्ण
		pr_ie->ie_index = cpu_to_le16(priv->proberesp_idx);
		pr_ie->mgmt_subtype_mask = cpu_to_le16(MWIFIEX_DELETE_MASK);
		pr_ie->ie_length = 0;
	पूर्ण
	अगर (priv->assocresp_idx != MWIFIEX_AUTO_IDX_MASK) अणु
		ar_ie = kदो_स्मृति(माप(काष्ठा mwअगरiex_ie), GFP_KERNEL);
		अगर (!ar_ie) अणु
			ret = -ENOMEM;
			जाओ करोne;
		पूर्ण
		ar_ie->ie_index = cpu_to_le16(priv->assocresp_idx);
		ar_ie->mgmt_subtype_mask = cpu_to_le16(MWIFIEX_DELETE_MASK);
		ar_ie->ie_length = 0;
	पूर्ण

	अगर (beacon_ie || pr_ie || ar_ie)
		ret = mwअगरiex_update_uap_custom_ie(priv,
						   beacon_ie, &priv->beacon_idx,
						   pr_ie, &priv->proberesp_idx,
						   ar_ie, &priv->assocresp_idx);

करोne:
	kमुक्त(gen_ie);
	kमुक्त(beacon_ie);
	kमुक्त(pr_ie);
	kमुक्त(ar_ie);

	वापस ret;
पूर्ण
