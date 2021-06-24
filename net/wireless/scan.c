<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * cfg80211 scan result handling
 *
 * Copyright 2008 Johannes Berg <johannes@sipsolutions.net>
 * Copyright 2013-2014  Intel Mobile Communications GmbH
 * Copyright 2016	Intel Deutschland GmbH
 * Copyright (C) 2018-2020 Intel Corporation
 */
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/wireless.h>
#समावेश <linux/nl80211.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/crc32.h>
#समावेश <linux/bitfield.h>
#समावेश <net/arp.h>
#समावेश <net/cfg80211.h>
#समावेश <net/cfg80211-wext.h>
#समावेश <net/iw_handler.h>
#समावेश "core.h"
#समावेश "nl80211.h"
#समावेश "wext-compat.h"
#समावेश "rdev-ops.h"

/**
 * DOC: BSS tree/list काष्ठाure
 *
 * At the top level, the BSS list is kept in both a list in each
 * रेजिस्टरed device (@bss_list) as well as an RB-tree क्रम faster
 * lookup. In the RB-tree, entries can be looked up using their
 * channel, MESHID, MESHCONF (क्रम MBSSes) or channel, BSSID, SSID
 * क्रम other BSSes.
 *
 * Due to the possibility of hidden SSIDs, there's a second level
 * काष्ठाure, the "hidden_list" and "hidden_beacon_bss" poपूर्णांकer.
 * The hidden_list connects all BSSes beदीर्घing to a single AP
 * that has a hidden SSID, and connects beacon and probe response
 * entries. For a probe response entry क्रम a hidden SSID, the
 * hidden_beacon_bss poपूर्णांकer poपूर्णांकs to the BSS काष्ठा holding the
 * beacon's inक्रमmation.
 *
 * Reference counting is करोne क्रम all these references except क्रम
 * the hidden_list, so that a beacon BSS काष्ठा that is otherwise
 * not referenced has one reference क्रम being on the bss_list and
 * one क्रम each probe response entry that poपूर्णांकs to it using the
 * hidden_beacon_bss poपूर्णांकer. When a BSS काष्ठा that has such a
 * poपूर्णांकer is get/put, the refcount update is also propagated to
 * the referenced काष्ठा, this ensure that it cannot get हटाओd
 * जबतक somebody is using the probe response version.
 *
 * Note that the hidden_beacon_bss poपूर्णांकer never changes, due to
 * the reference counting. Thereक्रमe, no locking is needed क्रम
 * it.
 *
 * Also note that the hidden_beacon_bss poपूर्णांकer is only relevant
 * अगर the driver uses something other than the IEs, e.g. निजी
 * data stored in the BSS काष्ठा, since the beacon IEs are
 * also linked पूर्णांकo the probe response काष्ठा.
 */

/*
 * Limit the number of BSS entries stored in mac80211. Each one is
 * a bit over 4k at most, so this limits to roughly 4-5M of memory.
 * If somebody wants to really attack this though, they'd likely
 * use small beacons, and only one type of frame, limiting each of
 * the entries to a much smaller size (in order to generate more
 * entries in total, so overhead is bigger.)
 */
अटल पूर्णांक bss_entries_limit = 1000;
module_param(bss_entries_limit, पूर्णांक, 0644);
MODULE_PARM_DESC(bss_entries_limit,
                 "limit to number of scan BSS entries (per wiphy, default 1000)");

#घोषणा IEEE80211_SCAN_RESULT_EXPIRE	(30 * HZ)

/**
 * काष्ठा cfg80211_colocated_ap - colocated AP inक्रमmation
 *
 * @list: linked list to all colocated aPS
 * @bssid: BSSID of the reported AP
 * @ssid: SSID of the reported AP
 * @ssid_len: length of the ssid
 * @center_freq: frequency the reported AP is on
 * @unsolicited_probe: the reported AP is part of an ESS, where all the APs
 *	that operate in the same channel as the reported AP and that might be
 *	detected by a STA receiving this frame, are transmitting unsolicited
 *	Probe Response frames every 20 TUs
 * @oct_recommended: OCT is recommended to exchange MMPDUs with the reported AP
 * @same_ssid: the reported AP has the same SSID as the reporting AP
 * @multi_bss: the reported AP is part of a multiple BSSID set
 * @transmitted_bssid: the reported AP is the transmitting BSSID
 * @colocated_ess: all the APs that share the same ESS as the reported AP are
 *	colocated and can be discovered via legacy bands.
 * @लघु_ssid_valid: लघु_ssid is valid and can be used
 * @लघु_ssid: the लघु SSID क्रम this SSID
 */
काष्ठा cfg80211_colocated_ap अणु
	काष्ठा list_head list;
	u8 bssid[ETH_ALEN];
	u8 ssid[IEEE80211_MAX_SSID_LEN];
	माप_प्रकार ssid_len;
	u32 लघु_ssid;
	u32 center_freq;
	u8 unsolicited_probe:1,
	   oct_recommended:1,
	   same_ssid:1,
	   multi_bss:1,
	   transmitted_bssid:1,
	   colocated_ess:1,
	   लघु_ssid_valid:1;
पूर्ण;

अटल व्योम bss_मुक्त(काष्ठा cfg80211_पूर्णांकernal_bss *bss)
अणु
	काष्ठा cfg80211_bss_ies *ies;

	अगर (WARN_ON(atomic_पढ़ो(&bss->hold)))
		वापस;

	ies = (व्योम *)rcu_access_poपूर्णांकer(bss->pub.beacon_ies);
	अगर (ies && !bss->pub.hidden_beacon_bss)
		kमुक्त_rcu(ies, rcu_head);
	ies = (व्योम *)rcu_access_poपूर्णांकer(bss->pub.proberesp_ies);
	अगर (ies)
		kमुक्त_rcu(ies, rcu_head);

	/*
	 * This happens when the module is हटाओd, it करोesn't
	 * really matter any more save क्रम completeness
	 */
	अगर (!list_empty(&bss->hidden_list))
		list_del(&bss->hidden_list);

	kमुक्त(bss);
पूर्ण

अटल अंतरभूत व्योम bss_ref_get(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			       काष्ठा cfg80211_पूर्णांकernal_bss *bss)
अणु
	lockdep_निश्चित_held(&rdev->bss_lock);

	bss->refcount++;
	अगर (bss->pub.hidden_beacon_bss) अणु
		bss = container_of(bss->pub.hidden_beacon_bss,
				   काष्ठा cfg80211_पूर्णांकernal_bss,
				   pub);
		bss->refcount++;
	पूर्ण
	अगर (bss->pub.transmitted_bss) अणु
		bss = container_of(bss->pub.transmitted_bss,
				   काष्ठा cfg80211_पूर्णांकernal_bss,
				   pub);
		bss->refcount++;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम bss_ref_put(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			       काष्ठा cfg80211_पूर्णांकernal_bss *bss)
अणु
	lockdep_निश्चित_held(&rdev->bss_lock);

	अगर (bss->pub.hidden_beacon_bss) अणु
		काष्ठा cfg80211_पूर्णांकernal_bss *hbss;
		hbss = container_of(bss->pub.hidden_beacon_bss,
				    काष्ठा cfg80211_पूर्णांकernal_bss,
				    pub);
		hbss->refcount--;
		अगर (hbss->refcount == 0)
			bss_मुक्त(hbss);
	पूर्ण

	अगर (bss->pub.transmitted_bss) अणु
		काष्ठा cfg80211_पूर्णांकernal_bss *tbss;

		tbss = container_of(bss->pub.transmitted_bss,
				    काष्ठा cfg80211_पूर्णांकernal_bss,
				    pub);
		tbss->refcount--;
		अगर (tbss->refcount == 0)
			bss_मुक्त(tbss);
	पूर्ण

	bss->refcount--;
	अगर (bss->refcount == 0)
		bss_मुक्त(bss);
पूर्ण

अटल bool __cfg80211_unlink_bss(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				  काष्ठा cfg80211_पूर्णांकernal_bss *bss)
अणु
	lockdep_निश्चित_held(&rdev->bss_lock);

	अगर (!list_empty(&bss->hidden_list)) अणु
		/*
		 * करोn't हटाओ the beacon entry अगर it has
		 * probe responses associated with it
		 */
		अगर (!bss->pub.hidden_beacon_bss)
			वापस false;
		/*
		 * अगर it's a probe response entry अवरोध its
		 * link to the other entries in the group
		 */
		list_del_init(&bss->hidden_list);
	पूर्ण

	list_del_init(&bss->list);
	list_del_init(&bss->pub.nontrans_list);
	rb_erase(&bss->rbn, &rdev->bss_tree);
	rdev->bss_entries--;
	WARN_ONCE((rdev->bss_entries == 0) ^ list_empty(&rdev->bss_list),
		  "rdev bss entries[%d]/list[empty:%d] corruption\n",
		  rdev->bss_entries, list_empty(&rdev->bss_list));
	bss_ref_put(rdev, bss);
	वापस true;
पूर्ण

bool cfg80211_is_element_inherited(स्थिर काष्ठा element *elem,
				   स्थिर काष्ठा element *non_inherit_elem)
अणु
	u8 id_len, ext_id_len, i, loop_len, id;
	स्थिर u8 *list;

	अगर (elem->id == WLAN_EID_MULTIPLE_BSSID)
		वापस false;

	अगर (!non_inherit_elem || non_inherit_elem->datalen < 2)
		वापस true;

	/*
	 * non inheritance element क्रमmat is:
	 * ext ID (56) | IDs list len | list | extension IDs list len | list
	 * Both lists are optional. Both lengths are mandatory.
	 * This means valid length is:
	 * elem_len = 1 (extension ID) + 2 (list len fields) + list lengths
	 */
	id_len = non_inherit_elem->data[1];
	अगर (non_inherit_elem->datalen < 3 + id_len)
		वापस true;

	ext_id_len = non_inherit_elem->data[2 + id_len];
	अगर (non_inherit_elem->datalen < 3 + id_len + ext_id_len)
		वापस true;

	अगर (elem->id == WLAN_EID_EXTENSION) अणु
		अगर (!ext_id_len)
			वापस true;
		loop_len = ext_id_len;
		list = &non_inherit_elem->data[3 + id_len];
		id = elem->data[0];
	पूर्ण अन्यथा अणु
		अगर (!id_len)
			वापस true;
		loop_len = id_len;
		list = &non_inherit_elem->data[2];
		id = elem->id;
	पूर्ण

	क्रम (i = 0; i < loop_len; i++) अणु
		अगर (list[i] == id)
			वापस false;
	पूर्ण

	वापस true;
पूर्ण
EXPORT_SYMBOL(cfg80211_is_element_inherited);

अटल माप_प्रकार cfg80211_gen_new_ie(स्थिर u8 *ie, माप_प्रकार ielen,
				  स्थिर u8 *subelement, माप_प्रकार subie_len,
				  u8 *new_ie, gfp_t gfp)
अणु
	u8 *pos, *पंचांगp;
	स्थिर u8 *पंचांगp_old, *पंचांगp_new;
	स्थिर काष्ठा element *non_inherit_elem;
	u8 *sub_copy;

	/* copy subelement as we need to change its content to
	 * mark an ie after it is processed.
	 */
	sub_copy = kmemdup(subelement, subie_len, gfp);
	अगर (!sub_copy)
		वापस 0;

	pos = &new_ie[0];

	/* set new ssid */
	पंचांगp_new = cfg80211_find_ie(WLAN_EID_SSID, sub_copy, subie_len);
	अगर (पंचांगp_new) अणु
		स_नकल(pos, पंचांगp_new, पंचांगp_new[1] + 2);
		pos += (पंचांगp_new[1] + 2);
	पूर्ण

	/* get non inheritance list अगर exists */
	non_inherit_elem =
		cfg80211_find_ext_elem(WLAN_EID_EXT_NON_INHERITANCE,
				       sub_copy, subie_len);

	/* go through IEs in ie (skip SSID) and subelement,
	 * merge them पूर्णांकo new_ie
	 */
	पंचांगp_old = cfg80211_find_ie(WLAN_EID_SSID, ie, ielen);
	पंचांगp_old = (पंचांगp_old) ? पंचांगp_old + पंचांगp_old[1] + 2 : ie;

	जबतक (पंचांगp_old + पंचांगp_old[1] + 2 - ie <= ielen) अणु
		अगर (पंचांगp_old[0] == 0) अणु
			पंचांगp_old++;
			जारी;
		पूर्ण

		अगर (पंचांगp_old[0] == WLAN_EID_EXTENSION)
			पंचांगp = (u8 *)cfg80211_find_ext_ie(पंचांगp_old[2], sub_copy,
							 subie_len);
		अन्यथा
			पंचांगp = (u8 *)cfg80211_find_ie(पंचांगp_old[0], sub_copy,
						     subie_len);

		अगर (!पंचांगp) अणु
			स्थिर काष्ठा element *old_elem = (व्योम *)पंचांगp_old;

			/* ie in old ie but not in subelement */
			अगर (cfg80211_is_element_inherited(old_elem,
							  non_inherit_elem)) अणु
				स_नकल(pos, पंचांगp_old, पंचांगp_old[1] + 2);
				pos += पंचांगp_old[1] + 2;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* ie in transmitting ie also in subelement,
			 * copy from subelement and flag the ie in subelement
			 * as copied (by setting eid field to WLAN_EID_SSID,
			 * which is skipped anyway).
			 * For venकरोr ie, compare OUI + type + subType to
			 * determine अगर they are the same ie.
			 */
			अगर (पंचांगp_old[0] == WLAN_EID_VENDOR_SPECIFIC) अणु
				अगर (!स_भेद(पंचांगp_old + 2, पंचांगp + 2, 5)) अणु
					/* same venकरोr ie, copy from
					 * subelement
					 */
					स_नकल(pos, पंचांगp, पंचांगp[1] + 2);
					pos += पंचांगp[1] + 2;
					पंचांगp[0] = WLAN_EID_SSID;
				पूर्ण अन्यथा अणु
					स_नकल(pos, पंचांगp_old, पंचांगp_old[1] + 2);
					pos += पंचांगp_old[1] + 2;
				पूर्ण
			पूर्ण अन्यथा अणु
				/* copy ie from subelement पूर्णांकo new ie */
				स_नकल(pos, पंचांगp, पंचांगp[1] + 2);
				pos += पंचांगp[1] + 2;
				पंचांगp[0] = WLAN_EID_SSID;
			पूर्ण
		पूर्ण

		अगर (पंचांगp_old + पंचांगp_old[1] + 2 - ie == ielen)
			अवरोध;

		पंचांगp_old += पंचांगp_old[1] + 2;
	पूर्ण

	/* go through subelement again to check अगर there is any ie not
	 * copied to new ie, skip ssid, capability, bssid-index ie
	 */
	पंचांगp_new = sub_copy;
	जबतक (पंचांगp_new + पंचांगp_new[1] + 2 - sub_copy <= subie_len) अणु
		अगर (!(पंचांगp_new[0] == WLAN_EID_NON_TX_BSSID_CAP ||
		      पंचांगp_new[0] == WLAN_EID_SSID)) अणु
			स_नकल(pos, पंचांगp_new, पंचांगp_new[1] + 2);
			pos += पंचांगp_new[1] + 2;
		पूर्ण
		अगर (पंचांगp_new + पंचांगp_new[1] + 2 - sub_copy == subie_len)
			अवरोध;
		पंचांगp_new += पंचांगp_new[1] + 2;
	पूर्ण

	kमुक्त(sub_copy);
	वापस pos - new_ie;
पूर्ण

अटल bool is_bss(काष्ठा cfg80211_bss *a, स्थिर u8 *bssid,
		   स्थिर u8 *ssid, माप_प्रकार ssid_len)
अणु
	स्थिर काष्ठा cfg80211_bss_ies *ies;
	स्थिर u8 *ssidie;

	अगर (bssid && !ether_addr_equal(a->bssid, bssid))
		वापस false;

	अगर (!ssid)
		वापस true;

	ies = rcu_access_poपूर्णांकer(a->ies);
	अगर (!ies)
		वापस false;
	ssidie = cfg80211_find_ie(WLAN_EID_SSID, ies->data, ies->len);
	अगर (!ssidie)
		वापस false;
	अगर (ssidie[1] != ssid_len)
		वापस false;
	वापस स_भेद(ssidie + 2, ssid, ssid_len) == 0;
पूर्ण

अटल पूर्णांक
cfg80211_add_nontrans_list(काष्ठा cfg80211_bss *trans_bss,
			   काष्ठा cfg80211_bss *nontrans_bss)
अणु
	स्थिर u8 *ssid;
	माप_प्रकार ssid_len;
	काष्ठा cfg80211_bss *bss = शून्य;

	rcu_पढ़ो_lock();
	ssid = ieee80211_bss_get_ie(nontrans_bss, WLAN_EID_SSID);
	अगर (!ssid) अणु
		rcu_पढ़ो_unlock();
		वापस -EINVAL;
	पूर्ण
	ssid_len = ssid[1];
	ssid = ssid + 2;
	rcu_पढ़ो_unlock();

	/* check अगर nontrans_bss is in the list */
	list_क्रम_each_entry(bss, &trans_bss->nontrans_list, nontrans_list) अणु
		अगर (is_bss(bss, nontrans_bss->bssid, ssid, ssid_len))
			वापस 0;
	पूर्ण

	/* add to the list */
	list_add_tail(&nontrans_bss->nontrans_list, &trans_bss->nontrans_list);
	वापस 0;
पूर्ण

अटल व्योम __cfg80211_bss_expire(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				  अचिन्हित दीर्घ expire_समय)
अणु
	काष्ठा cfg80211_पूर्णांकernal_bss *bss, *पंचांगp;
	bool expired = false;

	lockdep_निश्चित_held(&rdev->bss_lock);

	list_क्रम_each_entry_safe(bss, पंचांगp, &rdev->bss_list, list) अणु
		अगर (atomic_पढ़ो(&bss->hold))
			जारी;
		अगर (!समय_after(expire_समय, bss->ts))
			जारी;

		अगर (__cfg80211_unlink_bss(rdev, bss))
			expired = true;
	पूर्ण

	अगर (expired)
		rdev->bss_generation++;
पूर्ण

अटल bool cfg80211_bss_expire_oldest(काष्ठा cfg80211_रेजिस्टरed_device *rdev)
अणु
	काष्ठा cfg80211_पूर्णांकernal_bss *bss, *oldest = शून्य;
	bool ret;

	lockdep_निश्चित_held(&rdev->bss_lock);

	list_क्रम_each_entry(bss, &rdev->bss_list, list) अणु
		अगर (atomic_पढ़ो(&bss->hold))
			जारी;

		अगर (!list_empty(&bss->hidden_list) &&
		    !bss->pub.hidden_beacon_bss)
			जारी;

		अगर (oldest && समय_beक्रमe(oldest->ts, bss->ts))
			जारी;
		oldest = bss;
	पूर्ण

	अगर (WARN_ON(!oldest))
		वापस false;

	/*
	 * The callers make sure to increase rdev->bss_generation अगर anything
	 * माला_लो हटाओd (and a new entry added), so there's no need to also करो
	 * it here.
	 */

	ret = __cfg80211_unlink_bss(rdev, oldest);
	WARN_ON(!ret);
	वापस ret;
पूर्ण

अटल u8 cfg80211_parse_bss_param(u8 data,
				   काष्ठा cfg80211_colocated_ap *coloc_ap)
अणु
	coloc_ap->oct_recommended =
		u8_get_bits(data, IEEE80211_RNR_TBTT_PARAMS_OCT_RECOMMENDED);
	coloc_ap->same_ssid =
		u8_get_bits(data, IEEE80211_RNR_TBTT_PARAMS_SAME_SSID);
	coloc_ap->multi_bss =
		u8_get_bits(data, IEEE80211_RNR_TBTT_PARAMS_MULTI_BSSID);
	coloc_ap->transmitted_bssid =
		u8_get_bits(data, IEEE80211_RNR_TBTT_PARAMS_TRANSMITTED_BSSID);
	coloc_ap->unsolicited_probe =
		u8_get_bits(data, IEEE80211_RNR_TBTT_PARAMS_PROBE_ACTIVE);
	coloc_ap->colocated_ess =
		u8_get_bits(data, IEEE80211_RNR_TBTT_PARAMS_COLOC_ESS);

	वापस u8_get_bits(data, IEEE80211_RNR_TBTT_PARAMS_COLOC_AP);
पूर्ण

अटल पूर्णांक cfg80211_calc_लघु_ssid(स्थिर काष्ठा cfg80211_bss_ies *ies,
				    स्थिर काष्ठा element **elem, u32 *s_ssid)
अणु

	*elem = cfg80211_find_elem(WLAN_EID_SSID, ies->data, ies->len);
	अगर (!*elem || (*elem)->datalen > IEEE80211_MAX_SSID_LEN)
		वापस -EINVAL;

	*s_ssid = ~crc32_le(~0, (*elem)->data, (*elem)->datalen);
	वापस 0;
पूर्ण

अटल व्योम cfg80211_मुक्त_coloc_ap_list(काष्ठा list_head *coloc_ap_list)
अणु
	काष्ठा cfg80211_colocated_ap *ap, *पंचांगp_ap;

	list_क्रम_each_entry_safe(ap, पंचांगp_ap, coloc_ap_list, list) अणु
		list_del(&ap->list);
		kमुक्त(ap);
	पूर्ण
पूर्ण

अटल पूर्णांक cfg80211_parse_ap_info(काष्ठा cfg80211_colocated_ap *entry,
				  स्थिर u8 *pos, u8 length,
				  स्थिर काष्ठा element *ssid_elem,
				  पूर्णांक s_ssid_पंचांगp)
अणु
	/* skip the TBTT offset */
	pos++;

	स_नकल(entry->bssid, pos, ETH_ALEN);
	pos += ETH_ALEN;

	अगर (length == IEEE80211_TBTT_INFO_OFFSET_BSSID_SSSID_BSS_PARAM) अणु
		स_नकल(&entry->लघु_ssid, pos,
		       माप(entry->लघु_ssid));
		entry->लघु_ssid_valid = true;
		pos += 4;
	पूर्ण

	/* skip non colocated APs */
	अगर (!cfg80211_parse_bss_param(*pos, entry))
		वापस -EINVAL;
	pos++;

	अगर (length == IEEE80211_TBTT_INFO_OFFSET_BSSID_BSS_PARAM) अणु
		/*
		 * no inक्रमmation about the लघु ssid. Consider the entry valid
		 * क्रम now. It would later be dropped in हाल there are explicit
		 * SSIDs that need to be matched
		 */
		अगर (!entry->same_ssid)
			वापस 0;
	पूर्ण

	अगर (entry->same_ssid) अणु
		entry->लघु_ssid = s_ssid_पंचांगp;
		entry->लघु_ssid_valid = true;

		/*
		 * This is safe because we validate datalen in
		 * cfg80211_parse_colocated_ap(), beक्रमe calling this
		 * function.
		 */
		स_नकल(&entry->ssid, &ssid_elem->data,
		       ssid_elem->datalen);
		entry->ssid_len = ssid_elem->datalen;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cfg80211_parse_colocated_ap(स्थिर काष्ठा cfg80211_bss_ies *ies,
				       काष्ठा list_head *list)
अणु
	काष्ठा ieee80211_neighbor_ap_info *ap_info;
	स्थिर काष्ठा element *elem, *ssid_elem;
	स्थिर u8 *pos, *end;
	u32 s_ssid_पंचांगp;
	पूर्णांक n_coloc = 0, ret;
	LIST_HEAD(ap_list);

	elem = cfg80211_find_elem(WLAN_EID_REDUCED_NEIGHBOR_REPORT, ies->data,
				  ies->len);
	अगर (!elem)
		वापस 0;

	pos = elem->data;
	end = pos + elem->datalen;

	ret = cfg80211_calc_लघु_ssid(ies, &ssid_elem, &s_ssid_पंचांगp);
	अगर (ret)
		वापस ret;

	/* RNR IE may contain more than one NEIGHBOR_AP_INFO */
	जबतक (pos + माप(*ap_info) <= end) अणु
		क्रमागत nl80211_band band;
		पूर्णांक freq;
		u8 length, i, count;

		ap_info = (व्योम *)pos;
		count = u8_get_bits(ap_info->tbtt_info_hdr,
				    IEEE80211_AP_INFO_TBTT_HDR_COUNT) + 1;
		length = ap_info->tbtt_info_len;

		pos += माप(*ap_info);

		अगर (!ieee80211_operating_class_to_band(ap_info->op_class,
						       &band))
			अवरोध;

		freq = ieee80211_channel_to_frequency(ap_info->channel, band);

		अगर (end - pos < count * ap_info->tbtt_info_len)
			अवरोध;

		/*
		 * TBTT info must include bss param + BSSID +
		 * (लघु SSID or same_ssid bit to be set).
		 * ignore other options, and move to the
		 * next AP info
		 */
		अगर (band != NL80211_BAND_6GHZ ||
		    (length != IEEE80211_TBTT_INFO_OFFSET_BSSID_BSS_PARAM &&
		     length < IEEE80211_TBTT_INFO_OFFSET_BSSID_SSSID_BSS_PARAM)) अणु
			pos += count * ap_info->tbtt_info_len;
			जारी;
		पूर्ण

		क्रम (i = 0; i < count; i++) अणु
			काष्ठा cfg80211_colocated_ap *entry;

			entry = kzalloc(माप(*entry) + IEEE80211_MAX_SSID_LEN,
					GFP_ATOMIC);

			अगर (!entry)
				अवरोध;

			entry->center_freq = freq;

			अगर (!cfg80211_parse_ap_info(entry, pos, length,
						    ssid_elem, s_ssid_पंचांगp)) अणु
				n_coloc++;
				list_add_tail(&entry->list, &ap_list);
			पूर्ण अन्यथा अणु
				kमुक्त(entry);
			पूर्ण

			pos += ap_info->tbtt_info_len;
		पूर्ण
	पूर्ण

	अगर (pos != end) अणु
		cfg80211_मुक्त_coloc_ap_list(&ap_list);
		वापस 0;
	पूर्ण

	list_splice_tail(&ap_list, list);
	वापस n_coloc;
पूर्ण

अटल  व्योम cfg80211_scan_req_add_chan(काष्ठा cfg80211_scan_request *request,
					काष्ठा ieee80211_channel *chan,
					bool add_to_6ghz)
अणु
	पूर्णांक i;
	u32 n_channels = request->n_channels;
	काष्ठा cfg80211_scan_6ghz_params *params =
		&request->scan_6ghz_params[request->n_6ghz_params];

	क्रम (i = 0; i < n_channels; i++) अणु
		अगर (request->channels[i] == chan) अणु
			अगर (add_to_6ghz)
				params->channel_idx = i;
			वापस;
		पूर्ण
	पूर्ण

	request->channels[n_channels] = chan;
	अगर (add_to_6ghz)
		request->scan_6ghz_params[request->n_6ghz_params].channel_idx =
			n_channels;

	request->n_channels++;
पूर्ण

अटल bool cfg80211_find_ssid_match(काष्ठा cfg80211_colocated_ap *ap,
				     काष्ठा cfg80211_scan_request *request)
अणु
	पूर्णांक i;
	u32 s_ssid;

	क्रम (i = 0; i < request->n_ssids; i++) अणु
		/* wildcard ssid in the scan request */
		अगर (!request->ssids[i].ssid_len)
			वापस true;

		अगर (ap->ssid_len &&
		    ap->ssid_len == request->ssids[i].ssid_len) अणु
			अगर (!स_भेद(request->ssids[i].ssid, ap->ssid,
				    ap->ssid_len))
				वापस true;
		पूर्ण अन्यथा अगर (ap->लघु_ssid_valid) अणु
			s_ssid = ~crc32_le(~0, request->ssids[i].ssid,
					   request->ssids[i].ssid_len);

			अगर (ap->लघु_ssid == s_ssid)
				वापस true;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक cfg80211_scan_6ghz(काष्ठा cfg80211_रेजिस्टरed_device *rdev)
अणु
	u8 i;
	काष्ठा cfg80211_colocated_ap *ap;
	पूर्णांक n_channels, count = 0, err;
	काष्ठा cfg80211_scan_request *request, *rdev_req = rdev->scan_req;
	LIST_HEAD(coloc_ap_list);
	bool need_scan_psc = true;
	स्थिर काष्ठा ieee80211_sband_अगरtype_data *अगरtd;

	rdev_req->scan_6ghz = true;

	अगर (!rdev->wiphy.bands[NL80211_BAND_6GHZ])
		वापस -EOPNOTSUPP;

	अगरtd = ieee80211_get_sband_अगरtype_data(rdev->wiphy.bands[NL80211_BAND_6GHZ],
					       rdev_req->wdev->अगरtype);
	अगर (!अगरtd || !अगरtd->he_cap.has_he)
		वापस -EOPNOTSUPP;

	n_channels = rdev->wiphy.bands[NL80211_BAND_6GHZ]->n_channels;

	अगर (rdev_req->flags & NL80211_SCAN_FLAG_COLOCATED_6GHZ) अणु
		काष्ठा cfg80211_पूर्णांकernal_bss *पूर्णांकbss;

		spin_lock_bh(&rdev->bss_lock);
		list_क्रम_each_entry(पूर्णांकbss, &rdev->bss_list, list) अणु
			काष्ठा cfg80211_bss *res = &पूर्णांकbss->pub;
			स्थिर काष्ठा cfg80211_bss_ies *ies;

			ies = rcu_access_poपूर्णांकer(res->ies);
			count += cfg80211_parse_colocated_ap(ies,
							     &coloc_ap_list);
		पूर्ण
		spin_unlock_bh(&rdev->bss_lock);
	पूर्ण

	request = kzalloc(काष्ठा_size(request, channels, n_channels) +
			  माप(*request->scan_6ghz_params) * count,
			  GFP_KERNEL);
	अगर (!request) अणु
		cfg80211_मुक्त_coloc_ap_list(&coloc_ap_list);
		वापस -ENOMEM;
	पूर्ण

	*request = *rdev_req;
	request->n_channels = 0;
	request->scan_6ghz_params =
		(व्योम *)&request->channels[n_channels];

	/*
	 * PSC channels should not be scanned in हाल of direct scan with 1 SSID
	 * and at least one of the reported co-located APs with same SSID
	 * indicating that all APs in the same ESS are co-located
	 */
	अगर (count && request->n_ssids == 1 && request->ssids[0].ssid_len) अणु
		list_क्रम_each_entry(ap, &coloc_ap_list, list) अणु
			अगर (ap->colocated_ess &&
			    cfg80211_find_ssid_match(ap, request)) अणु
				need_scan_psc = false;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * add to the scan request the channels that need to be scanned
	 * regardless of the collocated APs (PSC channels or all channels
	 * in हाल that NL80211_SCAN_FLAG_COLOCATED_6GHZ is not set)
	 */
	क्रम (i = 0; i < rdev_req->n_channels; i++) अणु
		अगर (rdev_req->channels[i]->band == NL80211_BAND_6GHZ &&
		    ((need_scan_psc &&
		      cfg80211_channel_is_psc(rdev_req->channels[i])) ||
		     !(rdev_req->flags & NL80211_SCAN_FLAG_COLOCATED_6GHZ))) अणु
			cfg80211_scan_req_add_chan(request,
						   rdev_req->channels[i],
						   false);
		पूर्ण
	पूर्ण

	अगर (!(rdev_req->flags & NL80211_SCAN_FLAG_COLOCATED_6GHZ))
		जाओ skip;

	list_क्रम_each_entry(ap, &coloc_ap_list, list) अणु
		bool found = false;
		काष्ठा cfg80211_scan_6ghz_params *scan_6ghz_params =
			&request->scan_6ghz_params[request->n_6ghz_params];
		काष्ठा ieee80211_channel *chan =
			ieee80211_get_channel(&rdev->wiphy, ap->center_freq);

		अगर (!chan || chan->flags & IEEE80211_CHAN_DISABLED)
			जारी;

		क्रम (i = 0; i < rdev_req->n_channels; i++) अणु
			अगर (rdev_req->channels[i] == chan)
				found = true;
		पूर्ण

		अगर (!found)
			जारी;

		अगर (request->n_ssids > 0 &&
		    !cfg80211_find_ssid_match(ap, request))
			जारी;

		cfg80211_scan_req_add_chan(request, chan, true);
		स_नकल(scan_6ghz_params->bssid, ap->bssid, ETH_ALEN);
		scan_6ghz_params->लघु_ssid = ap->लघु_ssid;
		scan_6ghz_params->लघु_ssid_valid = ap->लघु_ssid_valid;
		scan_6ghz_params->unsolicited_probe = ap->unsolicited_probe;

		/*
		 * If a PSC channel is added to the scan and 'need_scan_psc' is
		 * set to false, then all the APs that the scan logic is
		 * पूर्णांकerested with on the channel are collocated and thus there
		 * is no need to perक्रमm the initial PSC channel listen.
		 */
		अगर (cfg80211_channel_is_psc(chan) && !need_scan_psc)
			scan_6ghz_params->psc_no_listen = true;

		request->n_6ghz_params++;
	पूर्ण

skip:
	cfg80211_मुक्त_coloc_ap_list(&coloc_ap_list);

	अगर (request->n_channels) अणु
		काष्ठा cfg80211_scan_request *old = rdev->पूर्णांक_scan_req;

		rdev->पूर्णांक_scan_req = request;

		/*
		 * If this scan follows a previous scan, save the scan start
		 * info from the first part of the scan
		 */
		अगर (old)
			rdev->पूर्णांक_scan_req->info = old->info;

		err = rdev_scan(rdev, request);
		अगर (err) अणु
			rdev->पूर्णांक_scan_req = old;
			kमुक्त(request);
		पूर्ण अन्यथा अणु
			kमुक्त(old);
		पूर्ण

		वापस err;
	पूर्ण

	kमुक्त(request);
	वापस -EINVAL;
पूर्ण

पूर्णांक cfg80211_scan(काष्ठा cfg80211_रेजिस्टरed_device *rdev)
अणु
	काष्ठा cfg80211_scan_request *request;
	काष्ठा cfg80211_scan_request *rdev_req = rdev->scan_req;
	u32 n_channels = 0, idx, i;

	अगर (!(rdev->wiphy.flags & WIPHY_FLAG_SPLIT_SCAN_6GHZ))
		वापस rdev_scan(rdev, rdev_req);

	क्रम (i = 0; i < rdev_req->n_channels; i++) अणु
		अगर (rdev_req->channels[i]->band != NL80211_BAND_6GHZ)
			n_channels++;
	पूर्ण

	अगर (!n_channels)
		वापस cfg80211_scan_6ghz(rdev);

	request = kzalloc(काष्ठा_size(request, channels, n_channels),
			  GFP_KERNEL);
	अगर (!request)
		वापस -ENOMEM;

	*request = *rdev_req;
	request->n_channels = n_channels;

	क्रम (i = idx = 0; i < rdev_req->n_channels; i++) अणु
		अगर (rdev_req->channels[i]->band != NL80211_BAND_6GHZ)
			request->channels[idx++] = rdev_req->channels[i];
	पूर्ण

	rdev_req->scan_6ghz = false;
	rdev->पूर्णांक_scan_req = request;
	वापस rdev_scan(rdev, request);
पूर्ण

व्योम ___cfg80211_scan_करोne(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			   bool send_message)
अणु
	काष्ठा cfg80211_scan_request *request, *rdev_req;
	काष्ठा wireless_dev *wdev;
	काष्ठा sk_buff *msg;
#अगर_घोषित CONFIG_CFG80211_WEXT
	जोड़ iwreq_data wrqu;
#पूर्ण_अगर

	lockdep_निश्चित_held(&rdev->wiphy.mtx);

	अगर (rdev->scan_msg) अणु
		nl80211_send_scan_msg(rdev, rdev->scan_msg);
		rdev->scan_msg = शून्य;
		वापस;
	पूर्ण

	rdev_req = rdev->scan_req;
	अगर (!rdev_req)
		वापस;

	wdev = rdev_req->wdev;
	request = rdev->पूर्णांक_scan_req ? rdev->पूर्णांक_scan_req : rdev_req;

	अगर (wdev_running(wdev) &&
	    (rdev->wiphy.flags & WIPHY_FLAG_SPLIT_SCAN_6GHZ) &&
	    !rdev_req->scan_6ghz && !request->info.पातed &&
	    !cfg80211_scan_6ghz(rdev))
		वापस;

	/*
	 * This must be beक्रमe sending the other events!
	 * Otherwise, wpa_supplicant माला_लो completely confused with
	 * wext events.
	 */
	अगर (wdev->netdev)
		cfg80211_sme_scan_करोne(wdev->netdev);

	अगर (!request->info.पातed &&
	    request->flags & NL80211_SCAN_FLAG_FLUSH) अणु
		/* flush entries from previous scans */
		spin_lock_bh(&rdev->bss_lock);
		__cfg80211_bss_expire(rdev, request->scan_start);
		spin_unlock_bh(&rdev->bss_lock);
	पूर्ण

	msg = nl80211_build_scan_msg(rdev, wdev, request->info.पातed);

#अगर_घोषित CONFIG_CFG80211_WEXT
	अगर (wdev->netdev && !request->info.पातed) अणु
		स_रखो(&wrqu, 0, माप(wrqu));

		wireless_send_event(wdev->netdev, SIOCGIWSCAN, &wrqu, शून्य);
	पूर्ण
#पूर्ण_अगर

	अगर (wdev->netdev)
		dev_put(wdev->netdev);

	kमुक्त(rdev->पूर्णांक_scan_req);
	rdev->पूर्णांक_scan_req = शून्य;

	kमुक्त(rdev->scan_req);
	rdev->scan_req = शून्य;

	अगर (!send_message)
		rdev->scan_msg = msg;
	अन्यथा
		nl80211_send_scan_msg(rdev, msg);
पूर्ण

व्योम __cfg80211_scan_करोne(काष्ठा work_काष्ठा *wk)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev;

	rdev = container_of(wk, काष्ठा cfg80211_रेजिस्टरed_device,
			    scan_करोne_wk);

	wiphy_lock(&rdev->wiphy);
	___cfg80211_scan_करोne(rdev, true);
	wiphy_unlock(&rdev->wiphy);
पूर्ण

व्योम cfg80211_scan_करोne(काष्ठा cfg80211_scan_request *request,
			काष्ठा cfg80211_scan_info *info)
अणु
	काष्ठा cfg80211_scan_info old_info = request->info;

	trace_cfg80211_scan_करोne(request, info);
	WARN_ON(request != wiphy_to_rdev(request->wiphy)->scan_req &&
		request != wiphy_to_rdev(request->wiphy)->पूर्णांक_scan_req);

	request->info = *info;

	/*
	 * In हाल the scan is split, the scan_start_tsf and tsf_bssid should
	 * be of the first part. In such a हाल old_info.scan_start_tsf should
	 * be non zero.
	 */
	अगर (request->scan_6ghz && old_info.scan_start_tsf) अणु
		request->info.scan_start_tsf = old_info.scan_start_tsf;
		स_नकल(request->info.tsf_bssid, old_info.tsf_bssid,
		       माप(request->info.tsf_bssid));
	पूर्ण

	request->notअगरied = true;
	queue_work(cfg80211_wq, &wiphy_to_rdev(request->wiphy)->scan_करोne_wk);
पूर्ण
EXPORT_SYMBOL(cfg80211_scan_करोne);

व्योम cfg80211_add_sched_scan_req(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				 काष्ठा cfg80211_sched_scan_request *req)
अणु
	lockdep_निश्चित_held(&rdev->wiphy.mtx);

	list_add_rcu(&req->list, &rdev->sched_scan_req_list);
पूर्ण

अटल व्योम cfg80211_del_sched_scan_req(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
					काष्ठा cfg80211_sched_scan_request *req)
अणु
	lockdep_निश्चित_held(&rdev->wiphy.mtx);

	list_del_rcu(&req->list);
	kमुक्त_rcu(req, rcu_head);
पूर्ण

अटल काष्ठा cfg80211_sched_scan_request *
cfg80211_find_sched_scan_req(काष्ठा cfg80211_रेजिस्टरed_device *rdev, u64 reqid)
अणु
	काष्ठा cfg80211_sched_scan_request *pos;

	list_क्रम_each_entry_rcu(pos, &rdev->sched_scan_req_list, list,
				lockdep_is_held(&rdev->wiphy.mtx)) अणु
		अगर (pos->reqid == reqid)
			वापस pos;
	पूर्ण
	वापस शून्य;
पूर्ण

/*
 * Determines अगर a scheduled scan request can be handled. When a legacy
 * scheduled scan is running no other scheduled scan is allowed regardless
 * whether the request is क्रम legacy or multi-support scan. When a multi-support
 * scheduled scan is running a request क्रम legacy scan is not allowed. In this
 * हाल a request क्रम multi-support scan can be handled अगर resources are
 * available, ie. काष्ठा wiphy::max_sched_scan_reqs limit is not yet reached.
 */
पूर्णांक cfg80211_sched_scan_req_possible(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				     bool want_multi)
अणु
	काष्ठा cfg80211_sched_scan_request *pos;
	पूर्णांक i = 0;

	list_क्रम_each_entry(pos, &rdev->sched_scan_req_list, list) अणु
		/* request id zero means legacy in progress */
		अगर (!i && !pos->reqid)
			वापस -EINPROGRESS;
		i++;
	पूर्ण

	अगर (i) अणु
		/* no legacy allowed when multi request(s) are active */
		अगर (!want_multi)
			वापस -EINPROGRESS;

		/* resource limit reached */
		अगर (i == rdev->wiphy.max_sched_scan_reqs)
			वापस -ENOSPC;
	पूर्ण
	वापस 0;
पूर्ण

व्योम cfg80211_sched_scan_results_wk(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev;
	काष्ठा cfg80211_sched_scan_request *req, *पंचांगp;

	rdev = container_of(work, काष्ठा cfg80211_रेजिस्टरed_device,
			   sched_scan_res_wk);

	wiphy_lock(&rdev->wiphy);
	list_क्रम_each_entry_safe(req, पंचांगp, &rdev->sched_scan_req_list, list) अणु
		अगर (req->report_results) अणु
			req->report_results = false;
			अगर (req->flags & NL80211_SCAN_FLAG_FLUSH) अणु
				/* flush entries from previous scans */
				spin_lock_bh(&rdev->bss_lock);
				__cfg80211_bss_expire(rdev, req->scan_start);
				spin_unlock_bh(&rdev->bss_lock);
				req->scan_start = jअगरfies;
			पूर्ण
			nl80211_send_sched_scan(req,
						NL80211_CMD_SCHED_SCAN_RESULTS);
		पूर्ण
	पूर्ण
	wiphy_unlock(&rdev->wiphy);
पूर्ण

व्योम cfg80211_sched_scan_results(काष्ठा wiphy *wiphy, u64 reqid)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wiphy);
	काष्ठा cfg80211_sched_scan_request *request;

	trace_cfg80211_sched_scan_results(wiphy, reqid);
	/* ignore अगर we're not scanning */

	rcu_पढ़ो_lock();
	request = cfg80211_find_sched_scan_req(rdev, reqid);
	अगर (request) अणु
		request->report_results = true;
		queue_work(cfg80211_wq, &rdev->sched_scan_res_wk);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण
EXPORT_SYMBOL(cfg80211_sched_scan_results);

व्योम cfg80211_sched_scan_stopped_locked(काष्ठा wiphy *wiphy, u64 reqid)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wiphy);

	lockdep_निश्चित_held(&wiphy->mtx);

	trace_cfg80211_sched_scan_stopped(wiphy, reqid);

	__cfg80211_stop_sched_scan(rdev, reqid, true);
पूर्ण
EXPORT_SYMBOL(cfg80211_sched_scan_stopped_locked);

व्योम cfg80211_sched_scan_stopped(काष्ठा wiphy *wiphy, u64 reqid)
अणु
	wiphy_lock(wiphy);
	cfg80211_sched_scan_stopped_locked(wiphy, reqid);
	wiphy_unlock(wiphy);
पूर्ण
EXPORT_SYMBOL(cfg80211_sched_scan_stopped);

पूर्णांक cfg80211_stop_sched_scan_req(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				 काष्ठा cfg80211_sched_scan_request *req,
				 bool driver_initiated)
अणु
	lockdep_निश्चित_held(&rdev->wiphy.mtx);

	अगर (!driver_initiated) अणु
		पूर्णांक err = rdev_sched_scan_stop(rdev, req->dev, req->reqid);
		अगर (err)
			वापस err;
	पूर्ण

	nl80211_send_sched_scan(req, NL80211_CMD_SCHED_SCAN_STOPPED);

	cfg80211_del_sched_scan_req(rdev, req);

	वापस 0;
पूर्ण

पूर्णांक __cfg80211_stop_sched_scan(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			       u64 reqid, bool driver_initiated)
अणु
	काष्ठा cfg80211_sched_scan_request *sched_scan_req;

	lockdep_निश्चित_held(&rdev->wiphy.mtx);

	sched_scan_req = cfg80211_find_sched_scan_req(rdev, reqid);
	अगर (!sched_scan_req)
		वापस -ENOENT;

	वापस cfg80211_stop_sched_scan_req(rdev, sched_scan_req,
					    driver_initiated);
पूर्ण

व्योम cfg80211_bss_age(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
                      अचिन्हित दीर्घ age_secs)
अणु
	काष्ठा cfg80211_पूर्णांकernal_bss *bss;
	अचिन्हित दीर्घ age_jअगरfies = msecs_to_jअगरfies(age_secs * MSEC_PER_SEC);

	spin_lock_bh(&rdev->bss_lock);
	list_क्रम_each_entry(bss, &rdev->bss_list, list)
		bss->ts -= age_jअगरfies;
	spin_unlock_bh(&rdev->bss_lock);
पूर्ण

व्योम cfg80211_bss_expire(काष्ठा cfg80211_रेजिस्टरed_device *rdev)
अणु
	__cfg80211_bss_expire(rdev, jअगरfies - IEEE80211_SCAN_RESULT_EXPIRE);
पूर्ण

व्योम cfg80211_bss_flush(काष्ठा wiphy *wiphy)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wiphy);

	spin_lock_bh(&rdev->bss_lock);
	__cfg80211_bss_expire(rdev, jअगरfies);
	spin_unlock_bh(&rdev->bss_lock);
पूर्ण
EXPORT_SYMBOL(cfg80211_bss_flush);

स्थिर काष्ठा element *
cfg80211_find_elem_match(u8 eid, स्थिर u8 *ies, अचिन्हित पूर्णांक len,
			 स्थिर u8 *match, अचिन्हित पूर्णांक match_len,
			 अचिन्हित पूर्णांक match_offset)
अणु
	स्थिर काष्ठा element *elem;

	क्रम_each_element_id(elem, eid, ies, len) अणु
		अगर (elem->datalen >= match_offset + match_len &&
		    !स_भेद(elem->data + match_offset, match, match_len))
			वापस elem;
	पूर्ण

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(cfg80211_find_elem_match);

स्थिर काष्ठा element *cfg80211_find_venकरोr_elem(अचिन्हित पूर्णांक oui, पूर्णांक oui_type,
						स्थिर u8 *ies,
						अचिन्हित पूर्णांक len)
अणु
	स्थिर काष्ठा element *elem;
	u8 match[] = अणु oui >> 16, oui >> 8, oui, oui_type पूर्ण;
	पूर्णांक match_len = (oui_type < 0) ? 3 : माप(match);

	अगर (WARN_ON(oui_type > 0xff))
		वापस शून्य;

	elem = cfg80211_find_elem_match(WLAN_EID_VENDOR_SPECIFIC, ies, len,
					match, match_len, 0);

	अगर (!elem || elem->datalen < 4)
		वापस शून्य;

	वापस elem;
पूर्ण
EXPORT_SYMBOL(cfg80211_find_venकरोr_elem);

/**
 * क्रमागत bss_compare_mode - BSS compare mode
 * @BSS_CMP_REGULAR: regular compare mode (क्रम insertion and normal find)
 * @BSS_CMP_HIDE_ZLEN: find hidden SSID with zero-length mode
 * @BSS_CMP_HIDE_NUL: find hidden SSID with NUL-ed out mode
 */
क्रमागत bss_compare_mode अणु
	BSS_CMP_REGULAR,
	BSS_CMP_HIDE_ZLEN,
	BSS_CMP_HIDE_NUL,
पूर्ण;

अटल पूर्णांक cmp_bss(काष्ठा cfg80211_bss *a,
		   काष्ठा cfg80211_bss *b,
		   क्रमागत bss_compare_mode mode)
अणु
	स्थिर काष्ठा cfg80211_bss_ies *a_ies, *b_ies;
	स्थिर u8 *ie1 = शून्य;
	स्थिर u8 *ie2 = शून्य;
	पूर्णांक i, r;

	अगर (a->channel != b->channel)
		वापस b->channel->center_freq - a->channel->center_freq;

	a_ies = rcu_access_poपूर्णांकer(a->ies);
	अगर (!a_ies)
		वापस -1;
	b_ies = rcu_access_poपूर्णांकer(b->ies);
	अगर (!b_ies)
		वापस 1;

	अगर (WLAN_CAPABILITY_IS_STA_BSS(a->capability))
		ie1 = cfg80211_find_ie(WLAN_EID_MESH_ID,
				       a_ies->data, a_ies->len);
	अगर (WLAN_CAPABILITY_IS_STA_BSS(b->capability))
		ie2 = cfg80211_find_ie(WLAN_EID_MESH_ID,
				       b_ies->data, b_ies->len);
	अगर (ie1 && ie2) अणु
		पूर्णांक mesh_id_cmp;

		अगर (ie1[1] == ie2[1])
			mesh_id_cmp = स_भेद(ie1 + 2, ie2 + 2, ie1[1]);
		अन्यथा
			mesh_id_cmp = ie2[1] - ie1[1];

		ie1 = cfg80211_find_ie(WLAN_EID_MESH_CONFIG,
				       a_ies->data, a_ies->len);
		ie2 = cfg80211_find_ie(WLAN_EID_MESH_CONFIG,
				       b_ies->data, b_ies->len);
		अगर (ie1 && ie2) अणु
			अगर (mesh_id_cmp)
				वापस mesh_id_cmp;
			अगर (ie1[1] != ie2[1])
				वापस ie2[1] - ie1[1];
			वापस स_भेद(ie1 + 2, ie2 + 2, ie1[1]);
		पूर्ण
	पूर्ण

	r = स_भेद(a->bssid, b->bssid, माप(a->bssid));
	अगर (r)
		वापस r;

	ie1 = cfg80211_find_ie(WLAN_EID_SSID, a_ies->data, a_ies->len);
	ie2 = cfg80211_find_ie(WLAN_EID_SSID, b_ies->data, b_ies->len);

	अगर (!ie1 && !ie2)
		वापस 0;

	/*
	 * Note that with "hide_ssid", the function वापसs a match अगर
	 * the alपढ़ोy-present BSS ("b") is a hidden SSID beacon क्रम
	 * the new BSS ("a").
	 */

	/* sort missing IE beक्रमe (left of) present IE */
	अगर (!ie1)
		वापस -1;
	अगर (!ie2)
		वापस 1;

	चयन (mode) अणु
	हाल BSS_CMP_HIDE_ZLEN:
		/*
		 * In ZLEN mode we assume the BSS entry we're
		 * looking क्रम has a zero-length SSID. So अगर
		 * the one we're looking at right now has that,
		 * वापस 0. Otherwise, वापस the dअगरference
		 * in length, but since we're looking क्रम the
		 * 0-length it's really equivalent to वापसing
		 * the length of the one we're looking at.
		 *
		 * No content comparison is needed as we assume
		 * the content length is zero.
		 */
		वापस ie2[1];
	हाल BSS_CMP_REGULAR:
	शेष:
		/* sort by length first, then by contents */
		अगर (ie1[1] != ie2[1])
			वापस ie2[1] - ie1[1];
		वापस स_भेद(ie1 + 2, ie2 + 2, ie1[1]);
	हाल BSS_CMP_HIDE_NUL:
		अगर (ie1[1] != ie2[1])
			वापस ie2[1] - ie1[1];
		/* this is equivalent to स_भेद(zeroes, ie2 + 2, len) */
		क्रम (i = 0; i < ie2[1]; i++)
			अगर (ie2[i + 2])
				वापस -1;
		वापस 0;
	पूर्ण
पूर्ण

अटल bool cfg80211_bss_type_match(u16 capability,
				    क्रमागत nl80211_band band,
				    क्रमागत ieee80211_bss_type bss_type)
अणु
	bool ret = true;
	u16 mask, val;

	अगर (bss_type == IEEE80211_BSS_TYPE_ANY)
		वापस ret;

	अगर (band == NL80211_BAND_60GHZ) अणु
		mask = WLAN_CAPABILITY_DMG_TYPE_MASK;
		चयन (bss_type) अणु
		हाल IEEE80211_BSS_TYPE_ESS:
			val = WLAN_CAPABILITY_DMG_TYPE_AP;
			अवरोध;
		हाल IEEE80211_BSS_TYPE_PBSS:
			val = WLAN_CAPABILITY_DMG_TYPE_PBSS;
			अवरोध;
		हाल IEEE80211_BSS_TYPE_IBSS:
			val = WLAN_CAPABILITY_DMG_TYPE_IBSS;
			अवरोध;
		शेष:
			वापस false;
		पूर्ण
	पूर्ण अन्यथा अणु
		mask = WLAN_CAPABILITY_ESS | WLAN_CAPABILITY_IBSS;
		चयन (bss_type) अणु
		हाल IEEE80211_BSS_TYPE_ESS:
			val = WLAN_CAPABILITY_ESS;
			अवरोध;
		हाल IEEE80211_BSS_TYPE_IBSS:
			val = WLAN_CAPABILITY_IBSS;
			अवरोध;
		हाल IEEE80211_BSS_TYPE_MBSS:
			val = 0;
			अवरोध;
		शेष:
			वापस false;
		पूर्ण
	पूर्ण

	ret = ((capability & mask) == val);
	वापस ret;
पूर्ण

/* Returned bss is reference counted and must be cleaned up appropriately. */
काष्ठा cfg80211_bss *cfg80211_get_bss(काष्ठा wiphy *wiphy,
				      काष्ठा ieee80211_channel *channel,
				      स्थिर u8 *bssid,
				      स्थिर u8 *ssid, माप_प्रकार ssid_len,
				      क्रमागत ieee80211_bss_type bss_type,
				      क्रमागत ieee80211_privacy privacy)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wiphy);
	काष्ठा cfg80211_पूर्णांकernal_bss *bss, *res = शून्य;
	अचिन्हित दीर्घ now = jअगरfies;
	पूर्णांक bss_privacy;

	trace_cfg80211_get_bss(wiphy, channel, bssid, ssid, ssid_len, bss_type,
			       privacy);

	spin_lock_bh(&rdev->bss_lock);

	list_क्रम_each_entry(bss, &rdev->bss_list, list) अणु
		अगर (!cfg80211_bss_type_match(bss->pub.capability,
					     bss->pub.channel->band, bss_type))
			जारी;

		bss_privacy = (bss->pub.capability & WLAN_CAPABILITY_PRIVACY);
		अगर ((privacy == IEEE80211_PRIVACY_ON && !bss_privacy) ||
		    (privacy == IEEE80211_PRIVACY_OFF && bss_privacy))
			जारी;
		अगर (channel && bss->pub.channel != channel)
			जारी;
		अगर (!is_valid_ether_addr(bss->pub.bssid))
			जारी;
		/* Don't get expired BSS काष्ठाs */
		अगर (समय_after(now, bss->ts + IEEE80211_SCAN_RESULT_EXPIRE) &&
		    !atomic_पढ़ो(&bss->hold))
			जारी;
		अगर (is_bss(&bss->pub, bssid, ssid, ssid_len)) अणु
			res = bss;
			bss_ref_get(rdev, res);
			अवरोध;
		पूर्ण
	पूर्ण

	spin_unlock_bh(&rdev->bss_lock);
	अगर (!res)
		वापस शून्य;
	trace_cfg80211_वापस_bss(&res->pub);
	वापस &res->pub;
पूर्ण
EXPORT_SYMBOL(cfg80211_get_bss);

अटल व्योम rb_insert_bss(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			  काष्ठा cfg80211_पूर्णांकernal_bss *bss)
अणु
	काष्ठा rb_node **p = &rdev->bss_tree.rb_node;
	काष्ठा rb_node *parent = शून्य;
	काष्ठा cfg80211_पूर्णांकernal_bss *tbss;
	पूर्णांक cmp;

	जबतक (*p) अणु
		parent = *p;
		tbss = rb_entry(parent, काष्ठा cfg80211_पूर्णांकernal_bss, rbn);

		cmp = cmp_bss(&bss->pub, &tbss->pub, BSS_CMP_REGULAR);

		अगर (WARN_ON(!cmp)) अणु
			/* will sort of leak this BSS */
			वापस;
		पूर्ण

		अगर (cmp < 0)
			p = &(*p)->rb_left;
		अन्यथा
			p = &(*p)->rb_right;
	पूर्ण

	rb_link_node(&bss->rbn, parent, p);
	rb_insert_color(&bss->rbn, &rdev->bss_tree);
पूर्ण

अटल काष्ठा cfg80211_पूर्णांकernal_bss *
rb_find_bss(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
	    काष्ठा cfg80211_पूर्णांकernal_bss *res,
	    क्रमागत bss_compare_mode mode)
अणु
	काष्ठा rb_node *n = rdev->bss_tree.rb_node;
	काष्ठा cfg80211_पूर्णांकernal_bss *bss;
	पूर्णांक r;

	जबतक (n) अणु
		bss = rb_entry(n, काष्ठा cfg80211_पूर्णांकernal_bss, rbn);
		r = cmp_bss(&res->pub, &bss->pub, mode);

		अगर (r == 0)
			वापस bss;
		अन्यथा अगर (r < 0)
			n = n->rb_left;
		अन्यथा
			n = n->rb_right;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल bool cfg80211_combine_bsses(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				   काष्ठा cfg80211_पूर्णांकernal_bss *new)
अणु
	स्थिर काष्ठा cfg80211_bss_ies *ies;
	काष्ठा cfg80211_पूर्णांकernal_bss *bss;
	स्थिर u8 *ie;
	पूर्णांक i, ssidlen;
	u8 fold = 0;
	u32 n_entries = 0;

	ies = rcu_access_poपूर्णांकer(new->pub.beacon_ies);
	अगर (WARN_ON(!ies))
		वापस false;

	ie = cfg80211_find_ie(WLAN_EID_SSID, ies->data, ies->len);
	अगर (!ie) अणु
		/* nothing to करो */
		वापस true;
	पूर्ण

	ssidlen = ie[1];
	क्रम (i = 0; i < ssidlen; i++)
		fold |= ie[2 + i];

	अगर (fold) अणु
		/* not a hidden SSID */
		वापस true;
	पूर्ण

	/* This is the bad part ... */

	list_क्रम_each_entry(bss, &rdev->bss_list, list) अणु
		/*
		 * we're iterating all the entries anyway, so take the
		 * opportunity to validate the list length accounting
		 */
		n_entries++;

		अगर (!ether_addr_equal(bss->pub.bssid, new->pub.bssid))
			जारी;
		अगर (bss->pub.channel != new->pub.channel)
			जारी;
		अगर (bss->pub.scan_width != new->pub.scan_width)
			जारी;
		अगर (rcu_access_poपूर्णांकer(bss->pub.beacon_ies))
			जारी;
		ies = rcu_access_poपूर्णांकer(bss->pub.ies);
		अगर (!ies)
			जारी;
		ie = cfg80211_find_ie(WLAN_EID_SSID, ies->data, ies->len);
		अगर (!ie)
			जारी;
		अगर (ssidlen && ie[1] != ssidlen)
			जारी;
		अगर (WARN_ON_ONCE(bss->pub.hidden_beacon_bss))
			जारी;
		अगर (WARN_ON_ONCE(!list_empty(&bss->hidden_list)))
			list_del(&bss->hidden_list);
		/* combine them */
		list_add(&bss->hidden_list, &new->hidden_list);
		bss->pub.hidden_beacon_bss = &new->pub;
		new->refcount += bss->refcount;
		rcu_assign_poपूर्णांकer(bss->pub.beacon_ies,
				   new->pub.beacon_ies);
	पूर्ण

	WARN_ONCE(n_entries != rdev->bss_entries,
		  "rdev bss entries[%d]/list[len:%d] corruption\n",
		  rdev->bss_entries, n_entries);

	वापस true;
पूर्ण

काष्ठा cfg80211_non_tx_bss अणु
	काष्ठा cfg80211_bss *tx_bss;
	u8 max_bssid_indicator;
	u8 bssid_index;
पूर्ण;

अटल bool
cfg80211_update_known_bss(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			  काष्ठा cfg80211_पूर्णांकernal_bss *known,
			  काष्ठा cfg80211_पूर्णांकernal_bss *new,
			  bool संकेत_valid)
अणु
	lockdep_निश्चित_held(&rdev->bss_lock);

	/* Update IEs */
	अगर (rcu_access_poपूर्णांकer(new->pub.proberesp_ies)) अणु
		स्थिर काष्ठा cfg80211_bss_ies *old;

		old = rcu_access_poपूर्णांकer(known->pub.proberesp_ies);

		rcu_assign_poपूर्णांकer(known->pub.proberesp_ies,
				   new->pub.proberesp_ies);
		/* Override possible earlier Beacon frame IEs */
		rcu_assign_poपूर्णांकer(known->pub.ies,
				   new->pub.proberesp_ies);
		अगर (old)
			kमुक्त_rcu((काष्ठा cfg80211_bss_ies *)old, rcu_head);
	पूर्ण अन्यथा अगर (rcu_access_poपूर्णांकer(new->pub.beacon_ies)) अणु
		स्थिर काष्ठा cfg80211_bss_ies *old;
		काष्ठा cfg80211_पूर्णांकernal_bss *bss;

		अगर (known->pub.hidden_beacon_bss &&
		    !list_empty(&known->hidden_list)) अणु
			स्थिर काष्ठा cfg80211_bss_ies *f;

			/* The known BSS काष्ठा is one of the probe
			 * response members of a group, but we're
			 * receiving a beacon (beacon_ies in the new
			 * bss is used). This can only mean that the
			 * AP changed its beacon from not having an
			 * SSID to showing it, which is confusing so
			 * drop this inक्रमmation.
			 */

			f = rcu_access_poपूर्णांकer(new->pub.beacon_ies);
			kमुक्त_rcu((काष्ठा cfg80211_bss_ies *)f, rcu_head);
			वापस false;
		पूर्ण

		old = rcu_access_poपूर्णांकer(known->pub.beacon_ies);

		rcu_assign_poपूर्णांकer(known->pub.beacon_ies, new->pub.beacon_ies);

		/* Override IEs अगर they were from a beacon beक्रमe */
		अगर (old == rcu_access_poपूर्णांकer(known->pub.ies))
			rcu_assign_poपूर्णांकer(known->pub.ies, new->pub.beacon_ies);

		/* Assign beacon IEs to all sub entries */
		list_क्रम_each_entry(bss, &known->hidden_list, hidden_list) अणु
			स्थिर काष्ठा cfg80211_bss_ies *ies;

			ies = rcu_access_poपूर्णांकer(bss->pub.beacon_ies);
			WARN_ON(ies != old);

			rcu_assign_poपूर्णांकer(bss->pub.beacon_ies,
					   new->pub.beacon_ies);
		पूर्ण

		अगर (old)
			kमुक्त_rcu((काष्ठा cfg80211_bss_ies *)old, rcu_head);
	पूर्ण

	known->pub.beacon_पूर्णांकerval = new->pub.beacon_पूर्णांकerval;

	/* करोn't update the संकेत अगर beacon was heard on
	 * adjacent channel.
	 */
	अगर (संकेत_valid)
		known->pub.संकेत = new->pub.संकेत;
	known->pub.capability = new->pub.capability;
	known->ts = new->ts;
	known->ts_bootसमय = new->ts_bootसमय;
	known->parent_tsf = new->parent_tsf;
	known->pub.chains = new->pub.chains;
	स_नकल(known->pub.chain_संकेत, new->pub.chain_संकेत,
	       IEEE80211_MAX_CHAINS);
	ether_addr_copy(known->parent_bssid, new->parent_bssid);
	known->pub.max_bssid_indicator = new->pub.max_bssid_indicator;
	known->pub.bssid_index = new->pub.bssid_index;

	वापस true;
पूर्ण

/* Returned bss is reference counted and must be cleaned up appropriately. */
काष्ठा cfg80211_पूर्णांकernal_bss *
cfg80211_bss_update(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
		    काष्ठा cfg80211_पूर्णांकernal_bss *पंचांगp,
		    bool संकेत_valid, अचिन्हित दीर्घ ts)
अणु
	काष्ठा cfg80211_पूर्णांकernal_bss *found = शून्य;

	अगर (WARN_ON(!पंचांगp->pub.channel))
		वापस शून्य;

	पंचांगp->ts = ts;

	spin_lock_bh(&rdev->bss_lock);

	अगर (WARN_ON(!rcu_access_poपूर्णांकer(पंचांगp->pub.ies))) अणु
		spin_unlock_bh(&rdev->bss_lock);
		वापस शून्य;
	पूर्ण

	found = rb_find_bss(rdev, पंचांगp, BSS_CMP_REGULAR);

	अगर (found) अणु
		अगर (!cfg80211_update_known_bss(rdev, found, पंचांगp, संकेत_valid))
			जाओ drop;
	पूर्ण अन्यथा अणु
		काष्ठा cfg80211_पूर्णांकernal_bss *new;
		काष्ठा cfg80211_पूर्णांकernal_bss *hidden;
		काष्ठा cfg80211_bss_ies *ies;

		/*
		 * create a copy -- the "res" variable that is passed in
		 * is allocated on the stack since it's not needed in the
		 * more common हाल of an update
		 */
		new = kzalloc(माप(*new) + rdev->wiphy.bss_priv_size,
			      GFP_ATOMIC);
		अगर (!new) अणु
			ies = (व्योम *)rcu_dereference(पंचांगp->pub.beacon_ies);
			अगर (ies)
				kमुक्त_rcu(ies, rcu_head);
			ies = (व्योम *)rcu_dereference(पंचांगp->pub.proberesp_ies);
			अगर (ies)
				kमुक्त_rcu(ies, rcu_head);
			जाओ drop;
		पूर्ण
		स_नकल(new, पंचांगp, माप(*new));
		new->refcount = 1;
		INIT_LIST_HEAD(&new->hidden_list);
		INIT_LIST_HEAD(&new->pub.nontrans_list);

		अगर (rcu_access_poपूर्णांकer(पंचांगp->pub.proberesp_ies)) अणु
			hidden = rb_find_bss(rdev, पंचांगp, BSS_CMP_HIDE_ZLEN);
			अगर (!hidden)
				hidden = rb_find_bss(rdev, पंचांगp,
						     BSS_CMP_HIDE_NUL);
			अगर (hidden) अणु
				new->pub.hidden_beacon_bss = &hidden->pub;
				list_add(&new->hidden_list,
					 &hidden->hidden_list);
				hidden->refcount++;
				rcu_assign_poपूर्णांकer(new->pub.beacon_ies,
						   hidden->pub.beacon_ies);
			पूर्ण
		पूर्ण अन्यथा अणु
			/*
			 * Ok so we found a beacon, and करोn't have an entry. If
			 * it's a beacon with hidden SSID, we might be in क्रम an
			 * expensive search क्रम any probe responses that should
			 * be grouped with this beacon क्रम updates ...
			 */
			अगर (!cfg80211_combine_bsses(rdev, new)) अणु
				kमुक्त(new);
				जाओ drop;
			पूर्ण
		पूर्ण

		अगर (rdev->bss_entries >= bss_entries_limit &&
		    !cfg80211_bss_expire_oldest(rdev)) अणु
			अगर (!list_empty(&new->hidden_list))
				list_del(&new->hidden_list);
			kमुक्त(new);
			जाओ drop;
		पूर्ण

		/* This must be beक्रमe the call to bss_ref_get */
		अगर (पंचांगp->pub.transmitted_bss) अणु
			काष्ठा cfg80211_पूर्णांकernal_bss *pbss =
				container_of(पंचांगp->pub.transmitted_bss,
					     काष्ठा cfg80211_पूर्णांकernal_bss,
					     pub);

			new->pub.transmitted_bss = पंचांगp->pub.transmitted_bss;
			bss_ref_get(rdev, pbss);
		पूर्ण

		list_add_tail(&new->list, &rdev->bss_list);
		rdev->bss_entries++;
		rb_insert_bss(rdev, new);
		found = new;
	पूर्ण

	rdev->bss_generation++;
	bss_ref_get(rdev, found);
	spin_unlock_bh(&rdev->bss_lock);

	वापस found;
 drop:
	spin_unlock_bh(&rdev->bss_lock);
	वापस शून्य;
पूर्ण

/*
 * Update RX channel inक्रमmation based on the available frame payload
 * inक्रमmation. This is मुख्यly क्रम the 2.4 GHz band where frames can be received
 * from neighboring channels and the Beacon frames use the DSSS Parameter Set
 * element to indicate the current (transmitting) channel, but this might also
 * be needed on other bands अगर RX frequency करोes not match with the actual
 * operating channel of a BSS.
 */
अटल काष्ठा ieee80211_channel *
cfg80211_get_bss_channel(काष्ठा wiphy *wiphy, स्थिर u8 *ie, माप_प्रकार ielen,
			 काष्ठा ieee80211_channel *channel,
			 क्रमागत nl80211_bss_scan_width scan_width)
अणु
	स्थिर u8 *पंचांगp;
	u32 freq;
	पूर्णांक channel_number = -1;
	काष्ठा ieee80211_channel *alt_channel;

	अगर (channel->band == NL80211_BAND_S1GHZ) अणु
		पंचांगp = cfg80211_find_ie(WLAN_EID_S1G_OPERATION, ie, ielen);
		अगर (पंचांगp && पंचांगp[1] >= माप(काष्ठा ieee80211_s1g_oper_ie)) अणु
			काष्ठा ieee80211_s1g_oper_ie *s1gop = (व्योम *)(पंचांगp + 2);

			channel_number = s1gop->primary_ch;
		पूर्ण
	पूर्ण अन्यथा अणु
		पंचांगp = cfg80211_find_ie(WLAN_EID_DS_PARAMS, ie, ielen);
		अगर (पंचांगp && पंचांगp[1] == 1) अणु
			channel_number = पंचांगp[2];
		पूर्ण अन्यथा अणु
			पंचांगp = cfg80211_find_ie(WLAN_EID_HT_OPERATION, ie, ielen);
			अगर (पंचांगp && पंचांगp[1] >= माप(काष्ठा ieee80211_ht_operation)) अणु
				काष्ठा ieee80211_ht_operation *htop = (व्योम *)(पंचांगp + 2);

				channel_number = htop->primary_chan;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (channel_number < 0) अणु
		/* No channel inक्रमmation in frame payload */
		वापस channel;
	पूर्ण

	freq = ieee80211_channel_to_freq_khz(channel_number, channel->band);
	alt_channel = ieee80211_get_channel_khz(wiphy, freq);
	अगर (!alt_channel) अणु
		अगर (channel->band == NL80211_BAND_2GHZ) अणु
			/*
			 * Better not allow unexpected channels when that could
			 * be going beyond the 1-11 range (e.g., discovering
			 * BSS on channel 12 when radio is configured क्रम
			 * channel 11.
			 */
			वापस शून्य;
		पूर्ण

		/* No match क्रम the payload channel number - ignore it */
		वापस channel;
	पूर्ण

	अगर (scan_width == NL80211_BSS_CHAN_WIDTH_10 ||
	    scan_width == NL80211_BSS_CHAN_WIDTH_5) अणु
		/*
		 * Ignore channel number in 5 and 10 MHz channels where there
		 * may not be an n:1 or 1:n mapping between frequencies and
		 * channel numbers.
		 */
		वापस channel;
	पूर्ण

	/*
	 * Use the channel determined through the payload channel number
	 * instead of the RX channel reported by the driver.
	 */
	अगर (alt_channel->flags & IEEE80211_CHAN_DISABLED)
		वापस शून्य;
	वापस alt_channel;
पूर्ण

/* Returned bss is reference counted and must be cleaned up appropriately. */
अटल काष्ठा cfg80211_bss *
cfg80211_inक्रमm_single_bss_data(काष्ठा wiphy *wiphy,
				काष्ठा cfg80211_inक्रमm_bss *data,
				क्रमागत cfg80211_bss_frame_type ftype,
				स्थिर u8 *bssid, u64 tsf, u16 capability,
				u16 beacon_पूर्णांकerval, स्थिर u8 *ie, माप_प्रकार ielen,
				काष्ठा cfg80211_non_tx_bss *non_tx_data,
				gfp_t gfp)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wiphy);
	काष्ठा cfg80211_bss_ies *ies;
	काष्ठा ieee80211_channel *channel;
	काष्ठा cfg80211_पूर्णांकernal_bss पंचांगp = अणुपूर्ण, *res;
	पूर्णांक bss_type;
	bool संकेत_valid;
	अचिन्हित दीर्घ ts;

	अगर (WARN_ON(!wiphy))
		वापस शून्य;

	अगर (WARN_ON(wiphy->संकेत_type == CFG80211_SIGNAL_TYPE_UNSPEC &&
		    (data->संकेत < 0 || data->संकेत > 100)))
		वापस शून्य;

	channel = cfg80211_get_bss_channel(wiphy, ie, ielen, data->chan,
					   data->scan_width);
	अगर (!channel)
		वापस शून्य;

	स_नकल(पंचांगp.pub.bssid, bssid, ETH_ALEN);
	पंचांगp.pub.channel = channel;
	पंचांगp.pub.scan_width = data->scan_width;
	पंचांगp.pub.संकेत = data->संकेत;
	पंचांगp.pub.beacon_पूर्णांकerval = beacon_पूर्णांकerval;
	पंचांगp.pub.capability = capability;
	पंचांगp.ts_bootसमय = data->bootसमय_ns;
	पंचांगp.parent_tsf = data->parent_tsf;
	ether_addr_copy(पंचांगp.parent_bssid, data->parent_bssid);

	अगर (non_tx_data) अणु
		पंचांगp.pub.transmitted_bss = non_tx_data->tx_bss;
		ts = bss_from_pub(non_tx_data->tx_bss)->ts;
		पंचांगp.pub.bssid_index = non_tx_data->bssid_index;
		पंचांगp.pub.max_bssid_indicator = non_tx_data->max_bssid_indicator;
	पूर्ण अन्यथा अणु
		ts = jअगरfies;
	पूर्ण

	/*
	 * If we करो not know here whether the IEs are from a Beacon or Probe
	 * Response frame, we need to pick one of the options and only use it
	 * with the driver that करोes not provide the full Beacon/Probe Response
	 * frame. Use Beacon frame poपूर्णांकer to aव्योम indicating that this should
	 * override the IEs poपूर्णांकer should we have received an earlier
	 * indication of Probe Response data.
	 */
	ies = kzalloc(माप(*ies) + ielen, gfp);
	अगर (!ies)
		वापस शून्य;
	ies->len = ielen;
	ies->tsf = tsf;
	ies->from_beacon = false;
	स_नकल(ies->data, ie, ielen);

	चयन (ftype) अणु
	हाल CFG80211_BSS_FTYPE_BEACON:
		ies->from_beacon = true;
		fallthrough;
	हाल CFG80211_BSS_FTYPE_UNKNOWN:
		rcu_assign_poपूर्णांकer(पंचांगp.pub.beacon_ies, ies);
		अवरोध;
	हाल CFG80211_BSS_FTYPE_PRESP:
		rcu_assign_poपूर्णांकer(पंचांगp.pub.proberesp_ies, ies);
		अवरोध;
	पूर्ण
	rcu_assign_poपूर्णांकer(पंचांगp.pub.ies, ies);

	संकेत_valid = data->chan == channel;
	res = cfg80211_bss_update(wiphy_to_rdev(wiphy), &पंचांगp, संकेत_valid, ts);
	अगर (!res)
		वापस शून्य;

	अगर (channel->band == NL80211_BAND_60GHZ) अणु
		bss_type = res->pub.capability & WLAN_CAPABILITY_DMG_TYPE_MASK;
		अगर (bss_type == WLAN_CAPABILITY_DMG_TYPE_AP ||
		    bss_type == WLAN_CAPABILITY_DMG_TYPE_PBSS)
			regulatory_hपूर्णांक_found_beacon(wiphy, channel, gfp);
	पूर्ण अन्यथा अणु
		अगर (res->pub.capability & WLAN_CAPABILITY_ESS)
			regulatory_hपूर्णांक_found_beacon(wiphy, channel, gfp);
	पूर्ण

	अगर (non_tx_data) अणु
		/* this is a nontransmitting bss, we need to add it to
		 * transmitting bss' list अगर it is not there
		 */
		अगर (cfg80211_add_nontrans_list(non_tx_data->tx_bss,
					       &res->pub)) अणु
			अगर (__cfg80211_unlink_bss(rdev, res))
				rdev->bss_generation++;
		पूर्ण
	पूर्ण

	trace_cfg80211_वापस_bss(&res->pub);
	/* cfg80211_bss_update gives us a referenced result */
	वापस &res->pub;
पूर्ण

अटल स्थिर काष्ठा element
*cfg80211_get_profile_continuation(स्थिर u8 *ie, माप_प्रकार ielen,
				   स्थिर काष्ठा element *mbssid_elem,
				   स्थिर काष्ठा element *sub_elem)
अणु
	स्थिर u8 *mbssid_end = mbssid_elem->data + mbssid_elem->datalen;
	स्थिर काष्ठा element *next_mbssid;
	स्थिर काष्ठा element *next_sub;

	next_mbssid = cfg80211_find_elem(WLAN_EID_MULTIPLE_BSSID,
					 mbssid_end,
					 ielen - (mbssid_end - ie));

	/*
	 * If it is not the last subelement in current MBSSID IE or there isn't
	 * a next MBSSID IE - profile is complete.
	*/
	अगर ((sub_elem->data + sub_elem->datalen < mbssid_end - 1) ||
	    !next_mbssid)
		वापस शून्य;

	/* For any length error, just वापस शून्य */

	अगर (next_mbssid->datalen < 4)
		वापस शून्य;

	next_sub = (व्योम *)&next_mbssid->data[1];

	अगर (next_mbssid->data + next_mbssid->datalen <
	    next_sub->data + next_sub->datalen)
		वापस शून्य;

	अगर (next_sub->id != 0 || next_sub->datalen < 2)
		वापस शून्य;

	/*
	 * Check अगर the first element in the next sub element is a start
	 * of a new profile
	 */
	वापस next_sub->data[0] == WLAN_EID_NON_TX_BSSID_CAP ?
	       शून्य : next_mbssid;
पूर्ण

माप_प्रकार cfg80211_merge_profile(स्थिर u8 *ie, माप_प्रकार ielen,
			      स्थिर काष्ठा element *mbssid_elem,
			      स्थिर काष्ठा element *sub_elem,
			      u8 *merged_ie, माप_प्रकार max_copy_len)
अणु
	माप_प्रकार copied_len = sub_elem->datalen;
	स्थिर काष्ठा element *next_mbssid;

	अगर (sub_elem->datalen > max_copy_len)
		वापस 0;

	स_नकल(merged_ie, sub_elem->data, sub_elem->datalen);

	जबतक ((next_mbssid = cfg80211_get_profile_continuation(ie, ielen,
								mbssid_elem,
								sub_elem))) अणु
		स्थिर काष्ठा element *next_sub = (व्योम *)&next_mbssid->data[1];

		अगर (copied_len + next_sub->datalen > max_copy_len)
			अवरोध;
		स_नकल(merged_ie + copied_len, next_sub->data,
		       next_sub->datalen);
		copied_len += next_sub->datalen;
	पूर्ण

	वापस copied_len;
पूर्ण
EXPORT_SYMBOL(cfg80211_merge_profile);

अटल व्योम cfg80211_parse_mbssid_data(काष्ठा wiphy *wiphy,
				       काष्ठा cfg80211_inक्रमm_bss *data,
				       क्रमागत cfg80211_bss_frame_type ftype,
				       स्थिर u8 *bssid, u64 tsf,
				       u16 beacon_पूर्णांकerval, स्थिर u8 *ie,
				       माप_प्रकार ielen,
				       काष्ठा cfg80211_non_tx_bss *non_tx_data,
				       gfp_t gfp)
अणु
	स्थिर u8 *mbssid_index_ie;
	स्थिर काष्ठा element *elem, *sub;
	माप_प्रकार new_ie_len;
	u8 new_bssid[ETH_ALEN];
	u8 *new_ie, *profile;
	u64 seen_indices = 0;
	u16 capability;
	काष्ठा cfg80211_bss *bss;

	अगर (!non_tx_data)
		वापस;
	अगर (!cfg80211_find_ie(WLAN_EID_MULTIPLE_BSSID, ie, ielen))
		वापस;
	अगर (!wiphy->support_mbssid)
		वापस;
	अगर (wiphy->support_only_he_mbssid &&
	    !cfg80211_find_ext_ie(WLAN_EID_EXT_HE_CAPABILITY, ie, ielen))
		वापस;

	new_ie = kदो_स्मृति(IEEE80211_MAX_DATA_LEN, gfp);
	अगर (!new_ie)
		वापस;

	profile = kदो_स्मृति(ielen, gfp);
	अगर (!profile)
		जाओ out;

	क्रम_each_element_id(elem, WLAN_EID_MULTIPLE_BSSID, ie, ielen) अणु
		अगर (elem->datalen < 4)
			जारी;
		क्रम_each_element(sub, elem->data + 1, elem->datalen - 1) अणु
			u8 profile_len;

			अगर (sub->id != 0 || sub->datalen < 4) अणु
				/* not a valid BSS profile */
				जारी;
			पूर्ण

			अगर (sub->data[0] != WLAN_EID_NON_TX_BSSID_CAP ||
			    sub->data[1] != 2) अणु
				/* The first element within the Nontransmitted
				 * BSSID Profile is not the Nontransmitted
				 * BSSID Capability element.
				 */
				जारी;
			पूर्ण

			स_रखो(profile, 0, ielen);
			profile_len = cfg80211_merge_profile(ie, ielen,
							     elem,
							     sub,
							     profile,
							     ielen);

			/* found a Nontransmitted BSSID Profile */
			mbssid_index_ie = cfg80211_find_ie
				(WLAN_EID_MULTI_BSSID_IDX,
				 profile, profile_len);
			अगर (!mbssid_index_ie || mbssid_index_ie[1] < 1 ||
			    mbssid_index_ie[2] == 0 ||
			    mbssid_index_ie[2] > 46) अणु
				/* No valid Multiple BSSID-Index element */
				जारी;
			पूर्ण

			अगर (seen_indices & BIT_ULL(mbssid_index_ie[2]))
				/* We करोn't support legacy split of a profile */
				net_dbg_ratelimited("Partial info for BSSID index %d\n",
						    mbssid_index_ie[2]);

			seen_indices |= BIT_ULL(mbssid_index_ie[2]);

			non_tx_data->bssid_index = mbssid_index_ie[2];
			non_tx_data->max_bssid_indicator = elem->data[0];

			cfg80211_gen_new_bssid(bssid,
					       non_tx_data->max_bssid_indicator,
					       non_tx_data->bssid_index,
					       new_bssid);
			स_रखो(new_ie, 0, IEEE80211_MAX_DATA_LEN);
			new_ie_len = cfg80211_gen_new_ie(ie, ielen,
							 profile,
							 profile_len, new_ie,
							 gfp);
			अगर (!new_ie_len)
				जारी;

			capability = get_unaligned_le16(profile + 2);
			bss = cfg80211_inक्रमm_single_bss_data(wiphy, data,
							      ftype,
							      new_bssid, tsf,
							      capability,
							      beacon_पूर्णांकerval,
							      new_ie,
							      new_ie_len,
							      non_tx_data,
							      gfp);
			अगर (!bss)
				अवरोध;
			cfg80211_put_bss(wiphy, bss);
		पूर्ण
	पूर्ण

out:
	kमुक्त(new_ie);
	kमुक्त(profile);
पूर्ण

काष्ठा cfg80211_bss *
cfg80211_inक्रमm_bss_data(काष्ठा wiphy *wiphy,
			 काष्ठा cfg80211_inक्रमm_bss *data,
			 क्रमागत cfg80211_bss_frame_type ftype,
			 स्थिर u8 *bssid, u64 tsf, u16 capability,
			 u16 beacon_पूर्णांकerval, स्थिर u8 *ie, माप_प्रकार ielen,
			 gfp_t gfp)
अणु
	काष्ठा cfg80211_bss *res;
	काष्ठा cfg80211_non_tx_bss non_tx_data;

	res = cfg80211_inक्रमm_single_bss_data(wiphy, data, ftype, bssid, tsf,
					      capability, beacon_पूर्णांकerval, ie,
					      ielen, शून्य, gfp);
	अगर (!res)
		वापस शून्य;
	non_tx_data.tx_bss = res;
	cfg80211_parse_mbssid_data(wiphy, data, ftype, bssid, tsf,
				   beacon_पूर्णांकerval, ie, ielen, &non_tx_data,
				   gfp);
	वापस res;
पूर्ण
EXPORT_SYMBOL(cfg80211_inक्रमm_bss_data);

अटल व्योम
cfg80211_parse_mbssid_frame_data(काष्ठा wiphy *wiphy,
				 काष्ठा cfg80211_inक्रमm_bss *data,
				 काष्ठा ieee80211_mgmt *mgmt, माप_प्रकार len,
				 काष्ठा cfg80211_non_tx_bss *non_tx_data,
				 gfp_t gfp)
अणु
	क्रमागत cfg80211_bss_frame_type ftype;
	स्थिर u8 *ie = mgmt->u.probe_resp.variable;
	माप_प्रकार ielen = len - दुरत्व(काष्ठा ieee80211_mgmt,
				      u.probe_resp.variable);

	ftype = ieee80211_is_beacon(mgmt->frame_control) ?
		CFG80211_BSS_FTYPE_BEACON : CFG80211_BSS_FTYPE_PRESP;

	cfg80211_parse_mbssid_data(wiphy, data, ftype, mgmt->bssid,
				   le64_to_cpu(mgmt->u.probe_resp.बारtamp),
				   le16_to_cpu(mgmt->u.probe_resp.beacon_पूर्णांक),
				   ie, ielen, non_tx_data, gfp);
पूर्ण

अटल व्योम
cfg80211_update_notlisted_nontrans(काष्ठा wiphy *wiphy,
				   काष्ठा cfg80211_bss *nontrans_bss,
				   काष्ठा ieee80211_mgmt *mgmt, माप_प्रकार len)
अणु
	u8 *ie, *new_ie, *pos;
	स्थिर u8 *nontrans_ssid, *trans_ssid, *mbssid;
	माप_प्रकार ielen = len - दुरत्व(काष्ठा ieee80211_mgmt,
				      u.probe_resp.variable);
	माप_प्रकार new_ie_len;
	काष्ठा cfg80211_bss_ies *new_ies;
	स्थिर काष्ठा cfg80211_bss_ies *old;
	u8 cpy_len;

	lockdep_निश्चित_held(&wiphy_to_rdev(wiphy)->bss_lock);

	ie = mgmt->u.probe_resp.variable;

	new_ie_len = ielen;
	trans_ssid = cfg80211_find_ie(WLAN_EID_SSID, ie, ielen);
	अगर (!trans_ssid)
		वापस;
	new_ie_len -= trans_ssid[1];
	mbssid = cfg80211_find_ie(WLAN_EID_MULTIPLE_BSSID, ie, ielen);
	/*
	 * It's not valid to have the MBSSID element beक्रमe SSID
	 * ignore अगर that happens - the code below assumes it is
	 * after (जबतक copying things inbetween).
	 */
	अगर (!mbssid || mbssid < trans_ssid)
		वापस;
	new_ie_len -= mbssid[1];

	nontrans_ssid = ieee80211_bss_get_ie(nontrans_bss, WLAN_EID_SSID);
	अगर (!nontrans_ssid)
		वापस;

	new_ie_len += nontrans_ssid[1];

	/* generate new ie क्रम nontrans BSS
	 * 1. replace SSID with nontrans BSS' SSID
	 * 2. skip MBSSID IE
	 */
	new_ie = kzalloc(new_ie_len, GFP_ATOMIC);
	अगर (!new_ie)
		वापस;

	new_ies = kzalloc(माप(*new_ies) + new_ie_len, GFP_ATOMIC);
	अगर (!new_ies)
		जाओ out_मुक्त;

	pos = new_ie;

	/* copy the nontransmitted SSID */
	cpy_len = nontrans_ssid[1] + 2;
	स_नकल(pos, nontrans_ssid, cpy_len);
	pos += cpy_len;
	/* copy the IEs between SSID and MBSSID */
	cpy_len = trans_ssid[1] + 2;
	स_नकल(pos, (trans_ssid + cpy_len), (mbssid - (trans_ssid + cpy_len)));
	pos += (mbssid - (trans_ssid + cpy_len));
	/* copy the IEs after MBSSID */
	cpy_len = mbssid[1] + 2;
	स_नकल(pos, mbssid + cpy_len, ((ie + ielen) - (mbssid + cpy_len)));

	/* update ie */
	new_ies->len = new_ie_len;
	new_ies->tsf = le64_to_cpu(mgmt->u.probe_resp.बारtamp);
	new_ies->from_beacon = ieee80211_is_beacon(mgmt->frame_control);
	स_नकल(new_ies->data, new_ie, new_ie_len);
	अगर (ieee80211_is_probe_resp(mgmt->frame_control)) अणु
		old = rcu_access_poपूर्णांकer(nontrans_bss->proberesp_ies);
		rcu_assign_poपूर्णांकer(nontrans_bss->proberesp_ies, new_ies);
		rcu_assign_poपूर्णांकer(nontrans_bss->ies, new_ies);
		अगर (old)
			kमुक्त_rcu((काष्ठा cfg80211_bss_ies *)old, rcu_head);
	पूर्ण अन्यथा अणु
		old = rcu_access_poपूर्णांकer(nontrans_bss->beacon_ies);
		rcu_assign_poपूर्णांकer(nontrans_bss->beacon_ies, new_ies);
		rcu_assign_poपूर्णांकer(nontrans_bss->ies, new_ies);
		अगर (old)
			kमुक्त_rcu((काष्ठा cfg80211_bss_ies *)old, rcu_head);
	पूर्ण

out_मुक्त:
	kमुक्त(new_ie);
पूर्ण

/* cfg80211_inक्रमm_bss_width_frame helper */
अटल काष्ठा cfg80211_bss *
cfg80211_inक्रमm_single_bss_frame_data(काष्ठा wiphy *wiphy,
				      काष्ठा cfg80211_inक्रमm_bss *data,
				      काष्ठा ieee80211_mgmt *mgmt, माप_प्रकार len,
				      gfp_t gfp)
अणु
	काष्ठा cfg80211_पूर्णांकernal_bss पंचांगp = अणुपूर्ण, *res;
	काष्ठा cfg80211_bss_ies *ies;
	काष्ठा ieee80211_channel *channel;
	bool संकेत_valid;
	काष्ठा ieee80211_ext *ext = शून्य;
	u8 *bssid, *variable;
	u16 capability, beacon_पूर्णांक;
	माप_प्रकार ielen, min_hdr_len = दुरत्व(काष्ठा ieee80211_mgmt,
					     u.probe_resp.variable);
	पूर्णांक bss_type;

	BUILD_BUG_ON(दुरत्व(काष्ठा ieee80211_mgmt, u.probe_resp.variable) !=
			दुरत्व(काष्ठा ieee80211_mgmt, u.beacon.variable));

	trace_cfg80211_inक्रमm_bss_frame(wiphy, data, mgmt, len);

	अगर (WARN_ON(!mgmt))
		वापस शून्य;

	अगर (WARN_ON(!wiphy))
		वापस शून्य;

	अगर (WARN_ON(wiphy->संकेत_type == CFG80211_SIGNAL_TYPE_UNSPEC &&
		    (data->संकेत < 0 || data->संकेत > 100)))
		वापस शून्य;

	अगर (ieee80211_is_s1g_beacon(mgmt->frame_control)) अणु
		ext = (व्योम *) mgmt;
		min_hdr_len = दुरत्व(काष्ठा ieee80211_ext, u.s1g_beacon);
		अगर (ieee80211_is_s1g_लघु_beacon(mgmt->frame_control))
			min_hdr_len = दुरत्व(काष्ठा ieee80211_ext,
					       u.s1g_लघु_beacon.variable);
	पूर्ण

	अगर (WARN_ON(len < min_hdr_len))
		वापस शून्य;

	ielen = len - min_hdr_len;
	variable = mgmt->u.probe_resp.variable;
	अगर (ext) अणु
		अगर (ieee80211_is_s1g_लघु_beacon(mgmt->frame_control))
			variable = ext->u.s1g_लघु_beacon.variable;
		अन्यथा
			variable = ext->u.s1g_beacon.variable;
	पूर्ण

	channel = cfg80211_get_bss_channel(wiphy, variable,
					   ielen, data->chan, data->scan_width);
	अगर (!channel)
		वापस शून्य;

	अगर (ext) अणु
		स्थिर काष्ठा ieee80211_s1g_bcn_compat_ie *compat;
		स्थिर काष्ठा element *elem;

		elem = cfg80211_find_elem(WLAN_EID_S1G_BCN_COMPAT,
					  variable, ielen);
		अगर (!elem)
			वापस शून्य;
		अगर (elem->datalen < माप(*compat))
			वापस शून्य;
		compat = (व्योम *)elem->data;
		bssid = ext->u.s1g_beacon.sa;
		capability = le16_to_cpu(compat->compat_info);
		beacon_पूर्णांक = le16_to_cpu(compat->beacon_पूर्णांक);
	पूर्ण अन्यथा अणु
		bssid = mgmt->bssid;
		beacon_पूर्णांक = le16_to_cpu(mgmt->u.probe_resp.beacon_पूर्णांक);
		capability = le16_to_cpu(mgmt->u.probe_resp.capab_info);
	पूर्ण

	ies = kzalloc(माप(*ies) + ielen, gfp);
	अगर (!ies)
		वापस शून्य;
	ies->len = ielen;
	ies->tsf = le64_to_cpu(mgmt->u.probe_resp.बारtamp);
	ies->from_beacon = ieee80211_is_beacon(mgmt->frame_control) ||
			   ieee80211_is_s1g_beacon(mgmt->frame_control);
	स_नकल(ies->data, variable, ielen);

	अगर (ieee80211_is_probe_resp(mgmt->frame_control))
		rcu_assign_poपूर्णांकer(पंचांगp.pub.proberesp_ies, ies);
	अन्यथा
		rcu_assign_poपूर्णांकer(पंचांगp.pub.beacon_ies, ies);
	rcu_assign_poपूर्णांकer(पंचांगp.pub.ies, ies);

	स_नकल(पंचांगp.pub.bssid, bssid, ETH_ALEN);
	पंचांगp.pub.beacon_पूर्णांकerval = beacon_पूर्णांक;
	पंचांगp.pub.capability = capability;
	पंचांगp.pub.channel = channel;
	पंचांगp.pub.scan_width = data->scan_width;
	पंचांगp.pub.संकेत = data->संकेत;
	पंचांगp.ts_bootसमय = data->bootसमय_ns;
	पंचांगp.parent_tsf = data->parent_tsf;
	पंचांगp.pub.chains = data->chains;
	स_नकल(पंचांगp.pub.chain_संकेत, data->chain_संकेत, IEEE80211_MAX_CHAINS);
	ether_addr_copy(पंचांगp.parent_bssid, data->parent_bssid);

	संकेत_valid = data->chan == channel;
	res = cfg80211_bss_update(wiphy_to_rdev(wiphy), &पंचांगp, संकेत_valid,
				  jअगरfies);
	अगर (!res)
		वापस शून्य;

	अगर (channel->band == NL80211_BAND_60GHZ) अणु
		bss_type = res->pub.capability & WLAN_CAPABILITY_DMG_TYPE_MASK;
		अगर (bss_type == WLAN_CAPABILITY_DMG_TYPE_AP ||
		    bss_type == WLAN_CAPABILITY_DMG_TYPE_PBSS)
			regulatory_hपूर्णांक_found_beacon(wiphy, channel, gfp);
	पूर्ण अन्यथा अणु
		अगर (res->pub.capability & WLAN_CAPABILITY_ESS)
			regulatory_hपूर्णांक_found_beacon(wiphy, channel, gfp);
	पूर्ण

	trace_cfg80211_वापस_bss(&res->pub);
	/* cfg80211_bss_update gives us a referenced result */
	वापस &res->pub;
पूर्ण

काष्ठा cfg80211_bss *
cfg80211_inक्रमm_bss_frame_data(काष्ठा wiphy *wiphy,
			       काष्ठा cfg80211_inक्रमm_bss *data,
			       काष्ठा ieee80211_mgmt *mgmt, माप_प्रकार len,
			       gfp_t gfp)
अणु
	काष्ठा cfg80211_bss *res, *पंचांगp_bss;
	स्थिर u8 *ie = mgmt->u.probe_resp.variable;
	स्थिर काष्ठा cfg80211_bss_ies *ies1, *ies2;
	माप_प्रकार ielen = len - दुरत्व(काष्ठा ieee80211_mgmt,
				      u.probe_resp.variable);
	काष्ठा cfg80211_non_tx_bss non_tx_data;

	res = cfg80211_inक्रमm_single_bss_frame_data(wiphy, data, mgmt,
						    len, gfp);
	अगर (!res || !wiphy->support_mbssid ||
	    !cfg80211_find_ie(WLAN_EID_MULTIPLE_BSSID, ie, ielen))
		वापस res;
	अगर (wiphy->support_only_he_mbssid &&
	    !cfg80211_find_ext_ie(WLAN_EID_EXT_HE_CAPABILITY, ie, ielen))
		वापस res;

	non_tx_data.tx_bss = res;
	/* process each non-transmitting bss */
	cfg80211_parse_mbssid_frame_data(wiphy, data, mgmt, len,
					 &non_tx_data, gfp);

	spin_lock_bh(&wiphy_to_rdev(wiphy)->bss_lock);

	/* check अगर the res has other nontransmitting bss which is not
	 * in MBSSID IE
	 */
	ies1 = rcu_access_poपूर्णांकer(res->ies);

	/* go through nontrans_list, अगर the बारtamp of the BSS is
	 * earlier than the बारtamp of the transmitting BSS then
	 * update it
	 */
	list_क्रम_each_entry(पंचांगp_bss, &res->nontrans_list,
			    nontrans_list) अणु
		ies2 = rcu_access_poपूर्णांकer(पंचांगp_bss->ies);
		अगर (ies2->tsf < ies1->tsf)
			cfg80211_update_notlisted_nontrans(wiphy, पंचांगp_bss,
							   mgmt, len);
	पूर्ण
	spin_unlock_bh(&wiphy_to_rdev(wiphy)->bss_lock);

	वापस res;
पूर्ण
EXPORT_SYMBOL(cfg80211_inक्रमm_bss_frame_data);

व्योम cfg80211_ref_bss(काष्ठा wiphy *wiphy, काष्ठा cfg80211_bss *pub)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wiphy);
	काष्ठा cfg80211_पूर्णांकernal_bss *bss;

	अगर (!pub)
		वापस;

	bss = container_of(pub, काष्ठा cfg80211_पूर्णांकernal_bss, pub);

	spin_lock_bh(&rdev->bss_lock);
	bss_ref_get(rdev, bss);
	spin_unlock_bh(&rdev->bss_lock);
पूर्ण
EXPORT_SYMBOL(cfg80211_ref_bss);

व्योम cfg80211_put_bss(काष्ठा wiphy *wiphy, काष्ठा cfg80211_bss *pub)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wiphy);
	काष्ठा cfg80211_पूर्णांकernal_bss *bss;

	अगर (!pub)
		वापस;

	bss = container_of(pub, काष्ठा cfg80211_पूर्णांकernal_bss, pub);

	spin_lock_bh(&rdev->bss_lock);
	bss_ref_put(rdev, bss);
	spin_unlock_bh(&rdev->bss_lock);
पूर्ण
EXPORT_SYMBOL(cfg80211_put_bss);

व्योम cfg80211_unlink_bss(काष्ठा wiphy *wiphy, काष्ठा cfg80211_bss *pub)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wiphy);
	काष्ठा cfg80211_पूर्णांकernal_bss *bss, *पंचांगp1;
	काष्ठा cfg80211_bss *nontrans_bss, *पंचांगp;

	अगर (WARN_ON(!pub))
		वापस;

	bss = container_of(pub, काष्ठा cfg80211_पूर्णांकernal_bss, pub);

	spin_lock_bh(&rdev->bss_lock);
	अगर (list_empty(&bss->list))
		जाओ out;

	list_क्रम_each_entry_safe(nontrans_bss, पंचांगp,
				 &pub->nontrans_list,
				 nontrans_list) अणु
		पंचांगp1 = container_of(nontrans_bss,
				    काष्ठा cfg80211_पूर्णांकernal_bss, pub);
		अगर (__cfg80211_unlink_bss(rdev, पंचांगp1))
			rdev->bss_generation++;
	पूर्ण

	अगर (__cfg80211_unlink_bss(rdev, bss))
		rdev->bss_generation++;
out:
	spin_unlock_bh(&rdev->bss_lock);
पूर्ण
EXPORT_SYMBOL(cfg80211_unlink_bss);

व्योम cfg80211_bss_iter(काष्ठा wiphy *wiphy,
		       काष्ठा cfg80211_chan_def *chandef,
		       व्योम (*iter)(काष्ठा wiphy *wiphy,
				    काष्ठा cfg80211_bss *bss,
				    व्योम *data),
		       व्योम *iter_data)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wiphy);
	काष्ठा cfg80211_पूर्णांकernal_bss *bss;

	spin_lock_bh(&rdev->bss_lock);

	list_क्रम_each_entry(bss, &rdev->bss_list, list) अणु
		अगर (!chandef || cfg80211_is_sub_chan(chandef, bss->pub.channel))
			iter(wiphy, &bss->pub, iter_data);
	पूर्ण

	spin_unlock_bh(&rdev->bss_lock);
पूर्ण
EXPORT_SYMBOL(cfg80211_bss_iter);

व्योम cfg80211_update_assoc_bss_entry(काष्ठा wireless_dev *wdev,
				     काष्ठा ieee80211_channel *chan)
अणु
	काष्ठा wiphy *wiphy = wdev->wiphy;
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wiphy);
	काष्ठा cfg80211_पूर्णांकernal_bss *cbss = wdev->current_bss;
	काष्ठा cfg80211_पूर्णांकernal_bss *new = शून्य;
	काष्ठा cfg80211_पूर्णांकernal_bss *bss;
	काष्ठा cfg80211_bss *nontrans_bss;
	काष्ठा cfg80211_bss *पंचांगp;

	spin_lock_bh(&rdev->bss_lock);

	/*
	 * Some APs use CSA also क्रम bandwidth changes, i.e., without actually
	 * changing the control channel, so no need to update in such a हाल.
	 */
	अगर (cbss->pub.channel == chan)
		जाओ करोne;

	/* use transmitting bss */
	अगर (cbss->pub.transmitted_bss)
		cbss = container_of(cbss->pub.transmitted_bss,
				    काष्ठा cfg80211_पूर्णांकernal_bss,
				    pub);

	cbss->pub.channel = chan;

	list_क्रम_each_entry(bss, &rdev->bss_list, list) अणु
		अगर (!cfg80211_bss_type_match(bss->pub.capability,
					     bss->pub.channel->band,
					     wdev->conn_bss_type))
			जारी;

		अगर (bss == cbss)
			जारी;

		अगर (!cmp_bss(&bss->pub, &cbss->pub, BSS_CMP_REGULAR)) अणु
			new = bss;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (new) अणु
		/* to save समय, update IEs क्रम transmitting bss only */
		अगर (cfg80211_update_known_bss(rdev, cbss, new, false)) अणु
			new->pub.proberesp_ies = शून्य;
			new->pub.beacon_ies = शून्य;
		पूर्ण

		list_क्रम_each_entry_safe(nontrans_bss, पंचांगp,
					 &new->pub.nontrans_list,
					 nontrans_list) अणु
			bss = container_of(nontrans_bss,
					   काष्ठा cfg80211_पूर्णांकernal_bss, pub);
			अगर (__cfg80211_unlink_bss(rdev, bss))
				rdev->bss_generation++;
		पूर्ण

		WARN_ON(atomic_पढ़ो(&new->hold));
		अगर (!WARN_ON(!__cfg80211_unlink_bss(rdev, new)))
			rdev->bss_generation++;
	पूर्ण

	rb_erase(&cbss->rbn, &rdev->bss_tree);
	rb_insert_bss(rdev, cbss);
	rdev->bss_generation++;

	list_क्रम_each_entry_safe(nontrans_bss, पंचांगp,
				 &cbss->pub.nontrans_list,
				 nontrans_list) अणु
		bss = container_of(nontrans_bss,
				   काष्ठा cfg80211_पूर्णांकernal_bss, pub);
		bss->pub.channel = chan;
		rb_erase(&bss->rbn, &rdev->bss_tree);
		rb_insert_bss(rdev, bss);
		rdev->bss_generation++;
	पूर्ण

करोne:
	spin_unlock_bh(&rdev->bss_lock);
पूर्ण

#अगर_घोषित CONFIG_CFG80211_WEXT
अटल काष्ठा cfg80211_रेजिस्टरed_device *
cfg80211_get_dev_from_अगरindex(काष्ठा net *net, पूर्णांक अगरindex)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev;
	काष्ठा net_device *dev;

	ASSERT_RTNL();

	dev = dev_get_by_index(net, अगरindex);
	अगर (!dev)
		वापस ERR_PTR(-ENODEV);
	अगर (dev->ieee80211_ptr)
		rdev = wiphy_to_rdev(dev->ieee80211_ptr->wiphy);
	अन्यथा
		rdev = ERR_PTR(-ENODEV);
	dev_put(dev);
	वापस rdev;
पूर्ण

पूर्णांक cfg80211_wext_siwscan(काष्ठा net_device *dev,
			  काष्ठा iw_request_info *info,
			  जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev;
	काष्ठा wiphy *wiphy;
	काष्ठा iw_scan_req *wreq = शून्य;
	काष्ठा cfg80211_scan_request *creq = शून्य;
	पूर्णांक i, err, n_channels = 0;
	क्रमागत nl80211_band band;

	अगर (!netअगर_running(dev))
		वापस -ENETDOWN;

	अगर (wrqu->data.length == माप(काष्ठा iw_scan_req))
		wreq = (काष्ठा iw_scan_req *)extra;

	rdev = cfg80211_get_dev_from_अगरindex(dev_net(dev), dev->अगरindex);

	अगर (IS_ERR(rdev))
		वापस PTR_ERR(rdev);

	अगर (rdev->scan_req || rdev->scan_msg) अणु
		err = -EBUSY;
		जाओ out;
	पूर्ण

	wiphy = &rdev->wiphy;

	/* Determine number of channels, needed to allocate creq */
	अगर (wreq && wreq->num_channels)
		n_channels = wreq->num_channels;
	अन्यथा
		n_channels = ieee80211_get_num_supported_channels(wiphy);

	creq = kzalloc(माप(*creq) + माप(काष्ठा cfg80211_ssid) +
		       n_channels * माप(व्योम *),
		       GFP_ATOMIC);
	अगर (!creq) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	creq->wiphy = wiphy;
	creq->wdev = dev->ieee80211_ptr;
	/* SSIDs come after channels */
	creq->ssids = (व्योम *)&creq->channels[n_channels];
	creq->n_channels = n_channels;
	creq->n_ssids = 1;
	creq->scan_start = jअगरfies;

	/* translate "Scan on frequencies" request */
	i = 0;
	क्रम (band = 0; band < NUM_NL80211_BANDS; band++) अणु
		पूर्णांक j;

		अगर (!wiphy->bands[band])
			जारी;

		क्रम (j = 0; j < wiphy->bands[band]->n_channels; j++) अणु
			/* ignore disabled channels */
			अगर (wiphy->bands[band]->channels[j].flags &
						IEEE80211_CHAN_DISABLED)
				जारी;

			/* If we have a wireless request काष्ठाure and the
			 * wireless request specअगरies frequencies, then search
			 * क्रम the matching hardware channel.
			 */
			अगर (wreq && wreq->num_channels) अणु
				पूर्णांक k;
				पूर्णांक wiphy_freq = wiphy->bands[band]->channels[j].center_freq;
				क्रम (k = 0; k < wreq->num_channels; k++) अणु
					काष्ठा iw_freq *freq =
						&wreq->channel_list[k];
					पूर्णांक wext_freq =
						cfg80211_wext_freq(freq);

					अगर (wext_freq == wiphy_freq)
						जाओ wext_freq_found;
				पूर्ण
				जाओ wext_freq_not_found;
			पूर्ण

		wext_freq_found:
			creq->channels[i] = &wiphy->bands[band]->channels[j];
			i++;
		wext_freq_not_found: ;
		पूर्ण
	पूर्ण
	/* No channels found? */
	अगर (!i) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण

	/* Set real number of channels specअगरied in creq->channels[] */
	creq->n_channels = i;

	/* translate "Scan for SSID" request */
	अगर (wreq) अणु
		अगर (wrqu->data.flags & IW_SCAN_THIS_ESSID) अणु
			अगर (wreq->essid_len > IEEE80211_MAX_SSID_LEN) अणु
				err = -EINVAL;
				जाओ out;
			पूर्ण
			स_नकल(creq->ssids[0].ssid, wreq->essid, wreq->essid_len);
			creq->ssids[0].ssid_len = wreq->essid_len;
		पूर्ण
		अगर (wreq->scan_type == IW_SCAN_TYPE_PASSIVE)
			creq->n_ssids = 0;
	पूर्ण

	क्रम (i = 0; i < NUM_NL80211_BANDS; i++)
		अगर (wiphy->bands[i])
			creq->rates[i] = (1 << wiphy->bands[i]->n_bitrates) - 1;

	eth_broadcast_addr(creq->bssid);

	wiphy_lock(&rdev->wiphy);

	rdev->scan_req = creq;
	err = rdev_scan(rdev, creq);
	अगर (err) अणु
		rdev->scan_req = शून्य;
		/* creq will be मुक्तd below */
	पूर्ण अन्यथा अणु
		nl80211_send_scan_start(rdev, dev->ieee80211_ptr);
		/* creq now owned by driver */
		creq = शून्य;
		dev_hold(dev);
	पूर्ण
	wiphy_unlock(&rdev->wiphy);
 out:
	kमुक्त(creq);
	वापस err;
पूर्ण
EXPORT_WEXT_HANDLER(cfg80211_wext_siwscan);

अटल अक्षर *ieee80211_scan_add_ies(काष्ठा iw_request_info *info,
				    स्थिर काष्ठा cfg80211_bss_ies *ies,
				    अक्षर *current_ev, अक्षर *end_buf)
अणु
	स्थिर u8 *pos, *end, *next;
	काष्ठा iw_event iwe;

	अगर (!ies)
		वापस current_ev;

	/*
	 * If needed, fragment the IEs buffer (at IE boundaries) पूर्णांकo लघु
	 * enough fragments to fit पूर्णांकo IW_GENERIC_IE_MAX octet messages.
	 */
	pos = ies->data;
	end = pos + ies->len;

	जबतक (end - pos > IW_GENERIC_IE_MAX) अणु
		next = pos + 2 + pos[1];
		जबतक (next + 2 + next[1] - pos < IW_GENERIC_IE_MAX)
			next = next + 2 + next[1];

		स_रखो(&iwe, 0, माप(iwe));
		iwe.cmd = IWEVGENIE;
		iwe.u.data.length = next - pos;
		current_ev = iwe_stream_add_poपूर्णांक_check(info, current_ev,
							end_buf, &iwe,
							(व्योम *)pos);
		अगर (IS_ERR(current_ev))
			वापस current_ev;
		pos = next;
	पूर्ण

	अगर (end > pos) अणु
		स_रखो(&iwe, 0, माप(iwe));
		iwe.cmd = IWEVGENIE;
		iwe.u.data.length = end - pos;
		current_ev = iwe_stream_add_poपूर्णांक_check(info, current_ev,
							end_buf, &iwe,
							(व्योम *)pos);
		अगर (IS_ERR(current_ev))
			वापस current_ev;
	पूर्ण

	वापस current_ev;
पूर्ण

अटल अक्षर *
ieee80211_bss(काष्ठा wiphy *wiphy, काष्ठा iw_request_info *info,
	      काष्ठा cfg80211_पूर्णांकernal_bss *bss, अक्षर *current_ev,
	      अक्षर *end_buf)
अणु
	स्थिर काष्ठा cfg80211_bss_ies *ies;
	काष्ठा iw_event iwe;
	स्थिर u8 *ie;
	u8 buf[50];
	u8 *cfg, *p, *पंचांगp;
	पूर्णांक rem, i, sig;
	bool ismesh = false;

	स_रखो(&iwe, 0, माप(iwe));
	iwe.cmd = SIOCGIWAP;
	iwe.u.ap_addr.sa_family = ARPHRD_ETHER;
	स_नकल(iwe.u.ap_addr.sa_data, bss->pub.bssid, ETH_ALEN);
	current_ev = iwe_stream_add_event_check(info, current_ev, end_buf, &iwe,
						IW_EV_ADDR_LEN);
	अगर (IS_ERR(current_ev))
		वापस current_ev;

	स_रखो(&iwe, 0, माप(iwe));
	iwe.cmd = SIOCGIWFREQ;
	iwe.u.freq.m = ieee80211_frequency_to_channel(bss->pub.channel->center_freq);
	iwe.u.freq.e = 0;
	current_ev = iwe_stream_add_event_check(info, current_ev, end_buf, &iwe,
						IW_EV_FREQ_LEN);
	अगर (IS_ERR(current_ev))
		वापस current_ev;

	स_रखो(&iwe, 0, माप(iwe));
	iwe.cmd = SIOCGIWFREQ;
	iwe.u.freq.m = bss->pub.channel->center_freq;
	iwe.u.freq.e = 6;
	current_ev = iwe_stream_add_event_check(info, current_ev, end_buf, &iwe,
						IW_EV_FREQ_LEN);
	अगर (IS_ERR(current_ev))
		वापस current_ev;

	अगर (wiphy->संकेत_type != CFG80211_SIGNAL_TYPE_NONE) अणु
		स_रखो(&iwe, 0, माप(iwe));
		iwe.cmd = IWEVQUAL;
		iwe.u.qual.updated = IW_QUAL_LEVEL_UPDATED |
				     IW_QUAL_NOISE_INVALID |
				     IW_QUAL_QUAL_UPDATED;
		चयन (wiphy->संकेत_type) अणु
		हाल CFG80211_SIGNAL_TYPE_MBM:
			sig = bss->pub.संकेत / 100;
			iwe.u.qual.level = sig;
			iwe.u.qual.updated |= IW_QUAL_DBM;
			अगर (sig < -110)		/* rather bad */
				sig = -110;
			अन्यथा अगर (sig > -40)	/* perfect */
				sig = -40;
			/* will give a range of 0 .. 70 */
			iwe.u.qual.qual = sig + 110;
			अवरोध;
		हाल CFG80211_SIGNAL_TYPE_UNSPEC:
			iwe.u.qual.level = bss->pub.संकेत;
			/* will give range 0 .. 100 */
			iwe.u.qual.qual = bss->pub.संकेत;
			अवरोध;
		शेष:
			/* not reached */
			अवरोध;
		पूर्ण
		current_ev = iwe_stream_add_event_check(info, current_ev,
							end_buf, &iwe,
							IW_EV_QUAL_LEN);
		अगर (IS_ERR(current_ev))
			वापस current_ev;
	पूर्ण

	स_रखो(&iwe, 0, माप(iwe));
	iwe.cmd = SIOCGIWENCODE;
	अगर (bss->pub.capability & WLAN_CAPABILITY_PRIVACY)
		iwe.u.data.flags = IW_ENCODE_ENABLED | IW_ENCODE_NOKEY;
	अन्यथा
		iwe.u.data.flags = IW_ENCODE_DISABLED;
	iwe.u.data.length = 0;
	current_ev = iwe_stream_add_poपूर्णांक_check(info, current_ev, end_buf,
						&iwe, "");
	अगर (IS_ERR(current_ev))
		वापस current_ev;

	rcu_पढ़ो_lock();
	ies = rcu_dereference(bss->pub.ies);
	rem = ies->len;
	ie = ies->data;

	जबतक (rem >= 2) अणु
		/* invalid data */
		अगर (ie[1] > rem - 2)
			अवरोध;

		चयन (ie[0]) अणु
		हाल WLAN_EID_SSID:
			स_रखो(&iwe, 0, माप(iwe));
			iwe.cmd = SIOCGIWESSID;
			iwe.u.data.length = ie[1];
			iwe.u.data.flags = 1;
			current_ev = iwe_stream_add_poपूर्णांक_check(info,
								current_ev,
								end_buf, &iwe,
								(u8 *)ie + 2);
			अगर (IS_ERR(current_ev))
				जाओ unlock;
			अवरोध;
		हाल WLAN_EID_MESH_ID:
			स_रखो(&iwe, 0, माप(iwe));
			iwe.cmd = SIOCGIWESSID;
			iwe.u.data.length = ie[1];
			iwe.u.data.flags = 1;
			current_ev = iwe_stream_add_poपूर्णांक_check(info,
								current_ev,
								end_buf, &iwe,
								(u8 *)ie + 2);
			अगर (IS_ERR(current_ev))
				जाओ unlock;
			अवरोध;
		हाल WLAN_EID_MESH_CONFIG:
			ismesh = true;
			अगर (ie[1] != माप(काष्ठा ieee80211_meshconf_ie))
				अवरोध;
			cfg = (u8 *)ie + 2;
			स_रखो(&iwe, 0, माप(iwe));
			iwe.cmd = IWEVCUSTOM;
			प्र_लिखो(buf, "Mesh Network Path Selection Protocol ID: "
				"0x%02X", cfg[0]);
			iwe.u.data.length = म_माप(buf);
			current_ev = iwe_stream_add_poपूर्णांक_check(info,
								current_ev,
								end_buf,
								&iwe, buf);
			अगर (IS_ERR(current_ev))
				जाओ unlock;
			प्र_लिखो(buf, "Path Selection Metric ID: 0x%02X",
				cfg[1]);
			iwe.u.data.length = म_माप(buf);
			current_ev = iwe_stream_add_poपूर्णांक_check(info,
								current_ev,
								end_buf,
								&iwe, buf);
			अगर (IS_ERR(current_ev))
				जाओ unlock;
			प्र_लिखो(buf, "Congestion Control Mode ID: 0x%02X",
				cfg[2]);
			iwe.u.data.length = म_माप(buf);
			current_ev = iwe_stream_add_poपूर्णांक_check(info,
								current_ev,
								end_buf,
								&iwe, buf);
			अगर (IS_ERR(current_ev))
				जाओ unlock;
			प्र_लिखो(buf, "Synchronization ID: 0x%02X", cfg[3]);
			iwe.u.data.length = म_माप(buf);
			current_ev = iwe_stream_add_poपूर्णांक_check(info,
								current_ev,
								end_buf,
								&iwe, buf);
			अगर (IS_ERR(current_ev))
				जाओ unlock;
			प्र_लिखो(buf, "Authentication ID: 0x%02X", cfg[4]);
			iwe.u.data.length = म_माप(buf);
			current_ev = iwe_stream_add_poपूर्णांक_check(info,
								current_ev,
								end_buf,
								&iwe, buf);
			अगर (IS_ERR(current_ev))
				जाओ unlock;
			प्र_लिखो(buf, "Formation Info: 0x%02X", cfg[5]);
			iwe.u.data.length = म_माप(buf);
			current_ev = iwe_stream_add_poपूर्णांक_check(info,
								current_ev,
								end_buf,
								&iwe, buf);
			अगर (IS_ERR(current_ev))
				जाओ unlock;
			प्र_लिखो(buf, "Capabilities: 0x%02X", cfg[6]);
			iwe.u.data.length = म_माप(buf);
			current_ev = iwe_stream_add_poपूर्णांक_check(info,
								current_ev,
								end_buf,
								&iwe, buf);
			अगर (IS_ERR(current_ev))
				जाओ unlock;
			अवरोध;
		हाल WLAN_EID_SUPP_RATES:
		हाल WLAN_EID_EXT_SUPP_RATES:
			/* display all supported rates in पढ़ोable क्रमmat */
			p = current_ev + iwe_stream_lcp_len(info);

			स_रखो(&iwe, 0, माप(iwe));
			iwe.cmd = SIOCGIWRATE;
			/* Those two flags are ignored... */
			iwe.u.bitrate.fixed = iwe.u.bitrate.disabled = 0;

			क्रम (i = 0; i < ie[1]; i++) अणु
				iwe.u.bitrate.value =
					((ie[i + 2] & 0x7f) * 500000);
				पंचांगp = p;
				p = iwe_stream_add_value(info, current_ev, p,
							 end_buf, &iwe,
							 IW_EV_PARAM_LEN);
				अगर (p == पंचांगp) अणु
					current_ev = ERR_PTR(-E2BIG);
					जाओ unlock;
				पूर्ण
			पूर्ण
			current_ev = p;
			अवरोध;
		पूर्ण
		rem -= ie[1] + 2;
		ie += ie[1] + 2;
	पूर्ण

	अगर (bss->pub.capability & (WLAN_CAPABILITY_ESS | WLAN_CAPABILITY_IBSS) ||
	    ismesh) अणु
		स_रखो(&iwe, 0, माप(iwe));
		iwe.cmd = SIOCGIWMODE;
		अगर (ismesh)
			iwe.u.mode = IW_MODE_MESH;
		अन्यथा अगर (bss->pub.capability & WLAN_CAPABILITY_ESS)
			iwe.u.mode = IW_MODE_MASTER;
		अन्यथा
			iwe.u.mode = IW_MODE_ADHOC;
		current_ev = iwe_stream_add_event_check(info, current_ev,
							end_buf, &iwe,
							IW_EV_UINT_LEN);
		अगर (IS_ERR(current_ev))
			जाओ unlock;
	पूर्ण

	स_रखो(&iwe, 0, माप(iwe));
	iwe.cmd = IWEVCUSTOM;
	प्र_लिखो(buf, "tsf=%016llx", (अचिन्हित दीर्घ दीर्घ)(ies->tsf));
	iwe.u.data.length = म_माप(buf);
	current_ev = iwe_stream_add_poपूर्णांक_check(info, current_ev, end_buf,
						&iwe, buf);
	अगर (IS_ERR(current_ev))
		जाओ unlock;
	स_रखो(&iwe, 0, माप(iwe));
	iwe.cmd = IWEVCUSTOM;
	प्र_लिखो(buf, " Last beacon: %ums ago",
		elapsed_jअगरfies_msecs(bss->ts));
	iwe.u.data.length = म_माप(buf);
	current_ev = iwe_stream_add_poपूर्णांक_check(info, current_ev,
						end_buf, &iwe, buf);
	अगर (IS_ERR(current_ev))
		जाओ unlock;

	current_ev = ieee80211_scan_add_ies(info, ies, current_ev, end_buf);

 unlock:
	rcu_पढ़ो_unlock();
	वापस current_ev;
पूर्ण


अटल पूर्णांक ieee80211_scan_results(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				  काष्ठा iw_request_info *info,
				  अक्षर *buf, माप_प्रकार len)
अणु
	अक्षर *current_ev = buf;
	अक्षर *end_buf = buf + len;
	काष्ठा cfg80211_पूर्णांकernal_bss *bss;
	पूर्णांक err = 0;

	spin_lock_bh(&rdev->bss_lock);
	cfg80211_bss_expire(rdev);

	list_क्रम_each_entry(bss, &rdev->bss_list, list) अणु
		अगर (buf + len - current_ev <= IW_EV_ADDR_LEN) अणु
			err = -E2BIG;
			अवरोध;
		पूर्ण
		current_ev = ieee80211_bss(&rdev->wiphy, info, bss,
					   current_ev, end_buf);
		अगर (IS_ERR(current_ev)) अणु
			err = PTR_ERR(current_ev);
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&rdev->bss_lock);

	अगर (err)
		वापस err;
	वापस current_ev - buf;
पूर्ण


पूर्णांक cfg80211_wext_giwscan(काष्ठा net_device *dev,
			  काष्ठा iw_request_info *info,
			  काष्ठा iw_poपूर्णांक *data, अक्षर *extra)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev;
	पूर्णांक res;

	अगर (!netअगर_running(dev))
		वापस -ENETDOWN;

	rdev = cfg80211_get_dev_from_अगरindex(dev_net(dev), dev->अगरindex);

	अगर (IS_ERR(rdev))
		वापस PTR_ERR(rdev);

	अगर (rdev->scan_req || rdev->scan_msg)
		वापस -EAGAIN;

	res = ieee80211_scan_results(rdev, info, extra, data->length);
	data->length = 0;
	अगर (res >= 0) अणु
		data->length = res;
		res = 0;
	पूर्ण

	वापस res;
पूर्ण
EXPORT_WEXT_HANDLER(cfg80211_wext_giwscan);
#पूर्ण_अगर
