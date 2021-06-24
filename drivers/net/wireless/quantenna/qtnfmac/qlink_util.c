<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/* Copyright (c) 2015-2016 Quantenna Communications. All rights reserved. */

#समावेश <linux/nl80211.h>

#समावेश "qlink_util.h"

u16 qlink_अगरace_type_to_nl_mask(u16 qlink_type)
अणु
	u16 result = 0;

	चयन (qlink_type) अणु
	हाल QLINK_IFTYPE_AP:
		result |= BIT(NL80211_IFTYPE_AP);
		अवरोध;
	हाल QLINK_IFTYPE_STATION:
		result |= BIT(NL80211_IFTYPE_STATION);
		अवरोध;
	हाल QLINK_IFTYPE_ADHOC:
		result |= BIT(NL80211_IFTYPE_ADHOC);
		अवरोध;
	हाल QLINK_IFTYPE_MONITOR:
		result |= BIT(NL80211_IFTYPE_MONITOR);
		अवरोध;
	हाल QLINK_IFTYPE_WDS:
		result |= BIT(NL80211_IFTYPE_WDS);
		अवरोध;
	हाल QLINK_IFTYPE_AP_VLAN:
		result |= BIT(NL80211_IFTYPE_AP_VLAN);
		अवरोध;
	पूर्ण

	वापस result;
पूर्ण

u8 qlink_chan_width_mask_to_nl(u16 qlink_mask)
अणु
	u8 result = 0;

	अगर (qlink_mask & BIT(QLINK_CHAN_WIDTH_5))
		result |= BIT(NL80211_CHAN_WIDTH_5);

	अगर (qlink_mask & BIT(QLINK_CHAN_WIDTH_10))
		result |= BIT(NL80211_CHAN_WIDTH_10);

	अगर (qlink_mask & BIT(QLINK_CHAN_WIDTH_20_NOHT))
		result |= BIT(NL80211_CHAN_WIDTH_20_NOHT);

	अगर (qlink_mask & BIT(QLINK_CHAN_WIDTH_20))
		result |= BIT(NL80211_CHAN_WIDTH_20);

	अगर (qlink_mask & BIT(QLINK_CHAN_WIDTH_40))
		result |= BIT(NL80211_CHAN_WIDTH_40);

	अगर (qlink_mask & BIT(QLINK_CHAN_WIDTH_80))
		result |= BIT(NL80211_CHAN_WIDTH_80);

	अगर (qlink_mask & BIT(QLINK_CHAN_WIDTH_80P80))
		result |= BIT(NL80211_CHAN_WIDTH_80P80);

	अगर (qlink_mask & BIT(QLINK_CHAN_WIDTH_160))
		result |= BIT(NL80211_CHAN_WIDTH_160);

	वापस result;
पूर्ण

अटल क्रमागत nl80211_chan_width qlink_chanwidth_to_nl(u8 qlw)
अणु
	चयन (qlw) अणु
	हाल QLINK_CHAN_WIDTH_20_NOHT:
		वापस NL80211_CHAN_WIDTH_20_NOHT;
	हाल QLINK_CHAN_WIDTH_20:
		वापस NL80211_CHAN_WIDTH_20;
	हाल QLINK_CHAN_WIDTH_40:
		वापस NL80211_CHAN_WIDTH_40;
	हाल QLINK_CHAN_WIDTH_80:
		वापस NL80211_CHAN_WIDTH_80;
	हाल QLINK_CHAN_WIDTH_80P80:
		वापस NL80211_CHAN_WIDTH_80P80;
	हाल QLINK_CHAN_WIDTH_160:
		वापस NL80211_CHAN_WIDTH_160;
	हाल QLINK_CHAN_WIDTH_5:
		वापस NL80211_CHAN_WIDTH_5;
	हाल QLINK_CHAN_WIDTH_10:
		वापस NL80211_CHAN_WIDTH_10;
	शेष:
		वापस -1;
	पूर्ण
पूर्ण

अटल u8 qlink_chanwidth_nl_to_qlink(क्रमागत nl80211_chan_width nlwidth)
अणु
	चयन (nlwidth) अणु
	हाल NL80211_CHAN_WIDTH_20_NOHT:
		वापस QLINK_CHAN_WIDTH_20_NOHT;
	हाल NL80211_CHAN_WIDTH_20:
		वापस QLINK_CHAN_WIDTH_20;
	हाल NL80211_CHAN_WIDTH_40:
		वापस QLINK_CHAN_WIDTH_40;
	हाल NL80211_CHAN_WIDTH_80:
		वापस QLINK_CHAN_WIDTH_80;
	हाल NL80211_CHAN_WIDTH_80P80:
		वापस QLINK_CHAN_WIDTH_80P80;
	हाल NL80211_CHAN_WIDTH_160:
		वापस QLINK_CHAN_WIDTH_160;
	हाल NL80211_CHAN_WIDTH_5:
		वापस QLINK_CHAN_WIDTH_5;
	हाल NL80211_CHAN_WIDTH_10:
		वापस QLINK_CHAN_WIDTH_10;
	शेष:
		वापस -1;
	पूर्ण
पूर्ण

व्योम qlink_chandef_q2cfg(काष्ठा wiphy *wiphy,
			 स्थिर काष्ठा qlink_chandef *qch,
			 काष्ठा cfg80211_chan_def *chdef)
अणु
	काष्ठा ieee80211_channel *chan;

	chan = ieee80211_get_channel(wiphy, le16_to_cpu(qch->chan.center_freq));

	chdef->chan = chan;
	chdef->center_freq1 = le16_to_cpu(qch->center_freq1);
	chdef->center_freq2 = le16_to_cpu(qch->center_freq2);
	chdef->width = qlink_chanwidth_to_nl(qch->width);
	chdef->edmg.bw_config = 0;
	chdef->edmg.channels = 0;
पूर्ण

व्योम qlink_chandef_cfg2q(स्थिर काष्ठा cfg80211_chan_def *chdef,
			 काष्ठा qlink_chandef *qch)
अणु
	काष्ठा ieee80211_channel *chan = chdef->chan;

	qch->chan.hw_value = cpu_to_le16(chan->hw_value);
	qch->chan.center_freq = cpu_to_le16(chan->center_freq);
	qch->chan.flags = cpu_to_le32(chan->flags);

	qch->center_freq1 = cpu_to_le16(chdef->center_freq1);
	qch->center_freq2 = cpu_to_le16(chdef->center_freq2);
	qch->width = qlink_chanwidth_nl_to_qlink(chdef->width);
पूर्ण

क्रमागत qlink_hidden_ssid qlink_hidden_ssid_nl2q(क्रमागत nl80211_hidden_ssid nl_val)
अणु
	चयन (nl_val) अणु
	हाल NL80211_HIDDEN_SSID_ZERO_LEN:
		वापस QLINK_HIDDEN_SSID_ZERO_LEN;
	हाल NL80211_HIDDEN_SSID_ZERO_CONTENTS:
		वापस QLINK_HIDDEN_SSID_ZERO_CONTENTS;
	हाल NL80211_HIDDEN_SSID_NOT_IN_USE:
	शेष:
		वापस QLINK_HIDDEN_SSID_NOT_IN_USE;
	पूर्ण
पूर्ण

bool qtnf_utils_is_bit_set(स्थिर u8 *arr, अचिन्हित पूर्णांक bit,
			   अचिन्हित पूर्णांक arr_max_len)
अणु
	अचिन्हित पूर्णांक idx = bit / BITS_PER_BYTE;
	u8 mask = 1 << (bit - (idx * BITS_PER_BYTE));

	अगर (idx >= arr_max_len)
		वापस false;

	वापस arr[idx] & mask;
पूर्ण

व्योम qlink_acl_data_cfg2q(स्थिर काष्ठा cfg80211_acl_data *acl,
			  काष्ठा qlink_acl_data *qacl)
अणु
	चयन (acl->acl_policy) अणु
	हाल NL80211_ACL_POLICY_ACCEPT_UNLESS_LISTED:
		qacl->policy =
			cpu_to_le32(QLINK_ACL_POLICY_ACCEPT_UNLESS_LISTED);
		अवरोध;
	हाल NL80211_ACL_POLICY_DENY_UNLESS_LISTED:
		qacl->policy = cpu_to_le32(QLINK_ACL_POLICY_DENY_UNLESS_LISTED);
		अवरोध;
	पूर्ण

	qacl->num_entries = cpu_to_le32(acl->n_acl_entries);
	स_नकल(qacl->mac_addrs, acl->mac_addrs,
	       acl->n_acl_entries * माप(*qacl->mac_addrs));
पूर्ण

क्रमागत qlink_band qlink_utils_band_cfg2q(क्रमागत nl80211_band band)
अणु
	चयन (band) अणु
	हाल NL80211_BAND_2GHZ:
		वापस QLINK_BAND_2GHZ;
	हाल NL80211_BAND_5GHZ:
		वापस QLINK_BAND_5GHZ;
	हाल NL80211_BAND_60GHZ:
		वापस QLINK_BAND_60GHZ;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

क्रमागत qlink_dfs_state qlink_utils_dfs_state_cfg2q(क्रमागत nl80211_dfs_state state)
अणु
	चयन (state) अणु
	हाल NL80211_DFS_USABLE:
		वापस QLINK_DFS_USABLE;
	हाल NL80211_DFS_AVAILABLE:
		वापस QLINK_DFS_AVAILABLE;
	हाल NL80211_DFS_UNAVAILABLE:
	शेष:
		वापस QLINK_DFS_UNAVAILABLE;
	पूर्ण
पूर्ण

u32 qlink_utils_chflags_cfg2q(u32 cfgflags)
अणु
	u32 flags = 0;

	अगर (cfgflags & IEEE80211_CHAN_DISABLED)
		flags |= QLINK_CHAN_DISABLED;

	अगर (cfgflags & IEEE80211_CHAN_NO_IR)
		flags |= QLINK_CHAN_NO_IR;

	अगर (cfgflags & IEEE80211_CHAN_RADAR)
		flags |= QLINK_CHAN_RADAR;

	अगर (cfgflags & IEEE80211_CHAN_NO_HT40PLUS)
		flags |= QLINK_CHAN_NO_HT40PLUS;

	अगर (cfgflags & IEEE80211_CHAN_NO_HT40MINUS)
		flags |= QLINK_CHAN_NO_HT40MINUS;

	अगर (cfgflags & IEEE80211_CHAN_NO_80MHZ)
		flags |= QLINK_CHAN_NO_80MHZ;

	अगर (cfgflags & IEEE80211_CHAN_NO_160MHZ)
		flags |= QLINK_CHAN_NO_160MHZ;

	वापस flags;
पूर्ण

अटल u32 qtnf_reg_rule_flags_parse(u32 qflags)
अणु
	u32 flags = 0;

	अगर (qflags & QLINK_RRF_NO_OFDM)
		flags |= NL80211_RRF_NO_OFDM;

	अगर (qflags & QLINK_RRF_NO_CCK)
		flags |= NL80211_RRF_NO_CCK;

	अगर (qflags & QLINK_RRF_NO_INDOOR)
		flags |= NL80211_RRF_NO_INDOOR;

	अगर (qflags & QLINK_RRF_NO_OUTDOOR)
		flags |= NL80211_RRF_NO_OUTDOOR;

	अगर (qflags & QLINK_RRF_DFS)
		flags |= NL80211_RRF_DFS;

	अगर (qflags & QLINK_RRF_PTP_ONLY)
		flags |= NL80211_RRF_PTP_ONLY;

	अगर (qflags & QLINK_RRF_PTMP_ONLY)
		flags |= NL80211_RRF_PTMP_ONLY;

	अगर (qflags & QLINK_RRF_NO_IR)
		flags |= NL80211_RRF_NO_IR;

	अगर (qflags & QLINK_RRF_AUTO_BW)
		flags |= NL80211_RRF_AUTO_BW;

	अगर (qflags & QLINK_RRF_IR_CONCURRENT)
		flags |= NL80211_RRF_IR_CONCURRENT;

	अगर (qflags & QLINK_RRF_NO_HT40MINUS)
		flags |= NL80211_RRF_NO_HT40MINUS;

	अगर (qflags & QLINK_RRF_NO_HT40PLUS)
		flags |= NL80211_RRF_NO_HT40PLUS;

	अगर (qflags & QLINK_RRF_NO_80MHZ)
		flags |= NL80211_RRF_NO_80MHZ;

	अगर (qflags & QLINK_RRF_NO_160MHZ)
		flags |= NL80211_RRF_NO_160MHZ;

	वापस flags;
पूर्ण

व्योम qlink_utils_regrule_q2nl(काष्ठा ieee80211_reg_rule *rule,
			      स्थिर काष्ठा qlink_tlv_reg_rule *tlv)
अणु
	rule->freq_range.start_freq_khz = le32_to_cpu(tlv->start_freq_khz);
	rule->freq_range.end_freq_khz = le32_to_cpu(tlv->end_freq_khz);
	rule->freq_range.max_bandwidth_khz =
		le32_to_cpu(tlv->max_bandwidth_khz);
	rule->घातer_rule.max_antenna_gain = le32_to_cpu(tlv->max_antenna_gain);
	rule->घातer_rule.max_eirp = le32_to_cpu(tlv->max_eirp);
	rule->dfs_cac_ms = le32_to_cpu(tlv->dfs_cac_ms);
	rule->flags = qtnf_reg_rule_flags_parse(le32_to_cpu(tlv->flags));
पूर्ण
