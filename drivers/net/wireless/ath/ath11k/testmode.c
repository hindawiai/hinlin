<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause-Clear
/*
 * Copyright (c) 2018-2019 The Linux Foundation. All rights reserved.
 */

#समावेश "testmode.h"
#समावेश <net/netlink.h>
#समावेश "debug.h"
#समावेश "wmi.h"
#समावेश "hw.h"
#समावेश "core.h"
#समावेश "testmode_i.h"

अटल स्थिर काष्ठा nla_policy ath11k_पंचांग_policy[ATH11K_TM_ATTR_MAX + 1] = अणु
	[ATH11K_TM_ATTR_CMD]		= अणु .type = NLA_U32 पूर्ण,
	[ATH11K_TM_ATTR_DATA]		= अणु .type = NLA_BINARY,
					    .len = ATH11K_TM_DATA_MAX_LEN पूर्ण,
	[ATH11K_TM_ATTR_WMI_CMDID]	= अणु .type = NLA_U32 पूर्ण,
	[ATH11K_TM_ATTR_VERSION_MAJOR]	= अणु .type = NLA_U32 पूर्ण,
	[ATH11K_TM_ATTR_VERSION_MINOR]	= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

/* Returns true अगर callee consumes the skb and the skb should be discarded.
 * Returns false अगर skb is not used. Does not sleep.
 */
bool ath11k_पंचांग_event_wmi(काष्ठा ath11k *ar, u32 cmd_id, काष्ठा sk_buff *skb)
अणु
	काष्ठा sk_buff *nl_skb;
	bool consumed;
	पूर्णांक ret;

	ath11k_dbg(ar->ab, ATH11K_DBG_TESTMODE,
		   "testmode event wmi cmd_id %d skb %pK skb->len %d\n",
		   cmd_id, skb, skb->len);

	ath11k_dbg_dump(ar->ab, ATH11K_DBG_TESTMODE, शून्य, "", skb->data, skb->len);

	spin_lock_bh(&ar->data_lock);

	consumed = true;

	nl_skb = cfg80211_tesपंचांगode_alloc_event_skb(ar->hw->wiphy,
						   2 * माप(u32) + skb->len,
						   GFP_ATOMIC);
	अगर (!nl_skb) अणु
		ath11k_warn(ar->ab,
			    "failed to allocate skb for testmode wmi event\n");
		जाओ out;
	पूर्ण

	ret = nla_put_u32(nl_skb, ATH11K_TM_ATTR_CMD, ATH11K_TM_CMD_WMI);
	अगर (ret) अणु
		ath11k_warn(ar->ab,
			    "failed to put testmode wmi event cmd attribute: %d\n",
			    ret);
		kमुक्त_skb(nl_skb);
		जाओ out;
	पूर्ण

	ret = nla_put_u32(nl_skb, ATH11K_TM_ATTR_WMI_CMDID, cmd_id);
	अगर (ret) अणु
		ath11k_warn(ar->ab,
			    "failed to put testmode wmi even cmd_id: %d\n",
			    ret);
		kमुक्त_skb(nl_skb);
		जाओ out;
	पूर्ण

	ret = nla_put(nl_skb, ATH11K_TM_ATTR_DATA, skb->len, skb->data);
	अगर (ret) अणु
		ath11k_warn(ar->ab,
			    "failed to copy skb to testmode wmi event: %d\n",
			    ret);
		kमुक्त_skb(nl_skb);
		जाओ out;
	पूर्ण

	cfg80211_tesपंचांगode_event(nl_skb, GFP_ATOMIC);

out:
	spin_unlock_bh(&ar->data_lock);

	वापस consumed;
पूर्ण

अटल पूर्णांक ath11k_पंचांग_cmd_get_version(काष्ठा ath11k *ar, काष्ठा nlattr *tb[])
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक ret;

	ath11k_dbg(ar->ab, ATH11K_DBG_TESTMODE,
		   "testmode cmd get version_major %d version_minor %d\n",
		   ATH11K_TESTMODE_VERSION_MAJOR,
		   ATH11K_TESTMODE_VERSION_MINOR);

	skb = cfg80211_tesपंचांगode_alloc_reply_skb(ar->hw->wiphy,
						nla_total_size(माप(u32)));
	अगर (!skb)
		वापस -ENOMEM;

	ret = nla_put_u32(skb, ATH11K_TM_ATTR_VERSION_MAJOR,
			  ATH11K_TESTMODE_VERSION_MAJOR);
	अगर (ret) अणु
		kमुक्त_skb(skb);
		वापस ret;
	पूर्ण

	ret = nla_put_u32(skb, ATH11K_TM_ATTR_VERSION_MINOR,
			  ATH11K_TESTMODE_VERSION_MINOR);
	अगर (ret) अणु
		kमुक्त_skb(skb);
		वापस ret;
	पूर्ण

	वापस cfg80211_tesपंचांगode_reply(skb);
पूर्ण

अटल पूर्णांक ath11k_पंचांग_cmd_wmi(काष्ठा ath11k *ar, काष्ठा nlattr *tb[])
अणु
	काष्ठा ath11k_pdev_wmi *wmi = ar->wmi;
	काष्ठा sk_buff *skb;
	u32 cmd_id, buf_len;
	पूर्णांक ret;
	व्योम *buf;

	mutex_lock(&ar->conf_mutex);

	अगर (ar->state != ATH11K_STATE_ON) अणु
		ret = -ENETDOWN;
		जाओ out;
	पूर्ण

	अगर (!tb[ATH11K_TM_ATTR_DATA]) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (!tb[ATH11K_TM_ATTR_WMI_CMDID]) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	buf = nla_data(tb[ATH11K_TM_ATTR_DATA]);
	buf_len = nla_len(tb[ATH11K_TM_ATTR_DATA]);
	cmd_id = nla_get_u32(tb[ATH11K_TM_ATTR_WMI_CMDID]);

	ath11k_dbg(ar->ab, ATH11K_DBG_TESTMODE,
		   "testmode cmd wmi cmd_id %d buf %pK buf_len %d\n",
		   cmd_id, buf, buf_len);

	ath11k_dbg_dump(ar->ab, ATH11K_DBG_TESTMODE, शून्य, "", buf, buf_len);

	skb = ath11k_wmi_alloc_skb(wmi->wmi_ab, buf_len);
	अगर (!skb) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	स_नकल(skb->data, buf, buf_len);

	ret = ath11k_wmi_cmd_send(wmi, skb, cmd_id);
	अगर (ret) अणु
		dev_kमुक्त_skb(skb);
		ath11k_warn(ar->ab, "failed to transmit wmi command (testmode): %d\n",
			    ret);
		जाओ out;
	पूर्ण

	ret = 0;

out:
	mutex_unlock(&ar->conf_mutex);
	वापस ret;
पूर्ण

पूर्णांक ath11k_पंचांग_cmd(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
		  व्योम *data, पूर्णांक len)
अणु
	काष्ठा ath11k *ar = hw->priv;
	काष्ठा nlattr *tb[ATH11K_TM_ATTR_MAX + 1];
	पूर्णांक ret;

	ret = nla_parse(tb, ATH11K_TM_ATTR_MAX, data, len, ath11k_पंचांग_policy,
			शून्य);
	अगर (ret)
		वापस ret;

	अगर (!tb[ATH11K_TM_ATTR_CMD])
		वापस -EINVAL;

	चयन (nla_get_u32(tb[ATH11K_TM_ATTR_CMD])) अणु
	हाल ATH11K_TM_CMD_GET_VERSION:
		वापस ath11k_पंचांग_cmd_get_version(ar, tb);
	हाल ATH11K_TM_CMD_WMI:
		वापस ath11k_पंचांग_cmd_wmi(ar, tb);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण
