<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2015 Qualcomm Atheros, Inc.
 */

#समावेश "core.h"
#समावेश "wmi.h"
#समावेश "mac.h"
#समावेश "p2p.h"

अटल व्योम ath10k_p2p_noa_ie_fill(u8 *data, माप_प्रकार len,
				   स्थिर काष्ठा wmi_p2p_noa_info *noa)
अणु
	काष्ठा ieee80211_p2p_noa_attr *noa_attr;
	u8  ctwinकरोw_oppps = noa->ctwinकरोw_oppps;
	u8 ctwinकरोw = ctwinकरोw_oppps >> WMI_P2P_OPPPS_CTWINDOW_OFFSET;
	bool oppps = !!(ctwinकरोw_oppps & WMI_P2P_OPPPS_ENABLE_BIT);
	__le16 *noa_attr_len;
	u16 attr_len;
	u8 noa_descriptors = noa->num_descriptors;
	पूर्णांक i;

	/* P2P IE */
	data[0] = WLAN_EID_VENDOR_SPECIFIC;
	data[1] = len - 2;
	data[2] = (WLAN_OUI_WFA >> 16) & 0xff;
	data[3] = (WLAN_OUI_WFA >> 8) & 0xff;
	data[4] = (WLAN_OUI_WFA >> 0) & 0xff;
	data[5] = WLAN_OUI_TYPE_WFA_P2P;

	/* NOA ATTR */
	data[6] = IEEE80211_P2P_ATTR_ABSENCE_NOTICE;
	noa_attr_len = (__le16 *)&data[7]; /* 2 bytes */
	noa_attr = (काष्ठा ieee80211_p2p_noa_attr *)&data[9];

	noa_attr->index = noa->index;
	noa_attr->oppps_ctwinकरोw = ctwinकरोw;
	अगर (oppps)
		noa_attr->oppps_ctwinकरोw |= IEEE80211_P2P_OPPPS_ENABLE_BIT;

	क्रम (i = 0; i < noa_descriptors; i++) अणु
		noa_attr->desc[i].count =
			__le32_to_cpu(noa->descriptors[i].type_count);
		noa_attr->desc[i].duration = noa->descriptors[i].duration;
		noa_attr->desc[i].पूर्णांकerval = noa->descriptors[i].पूर्णांकerval;
		noa_attr->desc[i].start_समय = noa->descriptors[i].start_समय;
	पूर्ण

	attr_len = 2; /* index + oppps_ctwinकरोw */
	attr_len += noa_descriptors * माप(काष्ठा ieee80211_p2p_noa_desc);
	*noa_attr_len = __cpu_to_le16(attr_len);
पूर्ण

अटल माप_प्रकार ath10k_p2p_noa_ie_len_compute(स्थिर काष्ठा wmi_p2p_noa_info *noa)
अणु
	माप_प्रकार len = 0;

	अगर (!noa->num_descriptors &&
	    !(noa->ctwinकरोw_oppps & WMI_P2P_OPPPS_ENABLE_BIT))
		वापस 0;

	len += 1 + 1 + 4; /* EID + len + OUI */
	len += 1 + 2; /* noa attr + attr len */
	len += 1 + 1; /* index + oppps_ctwinकरोw */
	len += noa->num_descriptors * माप(काष्ठा ieee80211_p2p_noa_desc);

	वापस len;
पूर्ण

अटल व्योम ath10k_p2p_noa_ie_assign(काष्ठा ath10k_vअगर *arvअगर, व्योम *ie,
				     माप_प्रकार len)
अणु
	काष्ठा ath10k *ar = arvअगर->ar;

	lockdep_निश्चित_held(&ar->data_lock);

	kमुक्त(arvअगर->u.ap.noa_data);

	arvअगर->u.ap.noa_data = ie;
	arvअगर->u.ap.noa_len = len;
पूर्ण

अटल व्योम __ath10k_p2p_noa_update(काष्ठा ath10k_vअगर *arvअगर,
				    स्थिर काष्ठा wmi_p2p_noa_info *noa)
अणु
	काष्ठा ath10k *ar = arvअगर->ar;
	व्योम *ie;
	माप_प्रकार len;

	lockdep_निश्चित_held(&ar->data_lock);

	ath10k_p2p_noa_ie_assign(arvअगर, शून्य, 0);

	len = ath10k_p2p_noa_ie_len_compute(noa);
	अगर (!len)
		वापस;

	ie = kदो_स्मृति(len, GFP_ATOMIC);
	अगर (!ie)
		वापस;

	ath10k_p2p_noa_ie_fill(ie, len, noa);
	ath10k_p2p_noa_ie_assign(arvअगर, ie, len);
पूर्ण

व्योम ath10k_p2p_noa_update(काष्ठा ath10k_vअगर *arvअगर,
			   स्थिर काष्ठा wmi_p2p_noa_info *noa)
अणु
	काष्ठा ath10k *ar = arvअगर->ar;

	spin_lock_bh(&ar->data_lock);
	__ath10k_p2p_noa_update(arvअगर, noa);
	spin_unlock_bh(&ar->data_lock);
पूर्ण

काष्ठा ath10k_p2p_noa_arg अणु
	u32 vdev_id;
	स्थिर काष्ठा wmi_p2p_noa_info *noa;
पूर्ण;

अटल व्योम ath10k_p2p_noa_update_vdev_iter(व्योम *data, u8 *mac,
					    काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा ath10k_vअगर *arvअगर = (व्योम *)vअगर->drv_priv;
	काष्ठा ath10k_p2p_noa_arg *arg = data;

	अगर (arvअगर->vdev_id != arg->vdev_id)
		वापस;

	ath10k_p2p_noa_update(arvअगर, arg->noa);
पूर्ण

व्योम ath10k_p2p_noa_update_by_vdev_id(काष्ठा ath10k *ar, u32 vdev_id,
				      स्थिर काष्ठा wmi_p2p_noa_info *noa)
अणु
	काष्ठा ath10k_p2p_noa_arg arg = अणु
		.vdev_id = vdev_id,
		.noa = noa,
	पूर्ण;

	ieee80211_iterate_active_पूर्णांकerfaces_atomic(ar->hw,
						   ATH10K_ITER_NORMAL_FLAGS,
						   ath10k_p2p_noa_update_vdev_iter,
						   &arg);
पूर्ण
