<शैली गुरु>
/*
 * Copyright (c) 2010-2011 Atheros Communications Inc.
 * Copyright (c) 2011 Qualcomm Atheros, Inc.
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#समावेश "testmode.h"
#समावेश "debug.h"

#समावेश <net/netlink.h>

क्रमागत ath6kl_पंचांग_attr अणु
	__ATH6KL_TM_ATTR_INVALID	= 0,
	ATH6KL_TM_ATTR_CMD		= 1,
	ATH6KL_TM_ATTR_DATA		= 2,

	/* keep last */
	__ATH6KL_TM_ATTR_AFTER_LAST,
	ATH6KL_TM_ATTR_MAX		= __ATH6KL_TM_ATTR_AFTER_LAST - 1,
पूर्ण;

क्रमागत ath6kl_पंचांग_cmd अणु
	ATH6KL_TM_CMD_TCMD		= 0,
	ATH6KL_TM_CMD_RX_REPORT		= 1,	/* not used anymore */
पूर्ण;

#घोषणा ATH6KL_TM_DATA_MAX_LEN		5000

अटल स्थिर काष्ठा nla_policy ath6kl_पंचांग_policy[ATH6KL_TM_ATTR_MAX + 1] = अणु
	[ATH6KL_TM_ATTR_CMD]		= अणु .type = NLA_U32 पूर्ण,
	[ATH6KL_TM_ATTR_DATA]		= अणु .type = NLA_BINARY,
					    .len = ATH6KL_TM_DATA_MAX_LEN पूर्ण,
पूर्ण;

व्योम ath6kl_पंचांग_rx_event(काष्ठा ath6kl *ar, व्योम *buf, माप_प्रकार buf_len)
अणु
	काष्ठा sk_buff *skb;

	अगर (!buf || buf_len == 0)
		वापस;

	skb = cfg80211_tesपंचांगode_alloc_event_skb(ar->wiphy, buf_len, GFP_KERNEL);
	अगर (!skb) अणु
		ath6kl_warn("failed to allocate testmode rx skb!\n");
		वापस;
	पूर्ण
	अगर (nla_put_u32(skb, ATH6KL_TM_ATTR_CMD, ATH6KL_TM_CMD_TCMD) ||
	    nla_put(skb, ATH6KL_TM_ATTR_DATA, buf_len, buf))
		जाओ nla_put_failure;
	cfg80211_tesपंचांगode_event(skb, GFP_KERNEL);
	वापस;

nla_put_failure:
	kमुक्त_skb(skb);
	ath6kl_warn("nla_put failed on testmode rx skb!\n");
पूर्ण

पूर्णांक ath6kl_पंचांग_cmd(काष्ठा wiphy *wiphy, काष्ठा wireless_dev *wdev,
		  व्योम *data, पूर्णांक len)
अणु
	काष्ठा ath6kl *ar = wiphy_priv(wiphy);
	काष्ठा nlattr *tb[ATH6KL_TM_ATTR_MAX + 1];
	पूर्णांक err, buf_len;
	व्योम *buf;

	err = nla_parse_deprecated(tb, ATH6KL_TM_ATTR_MAX, data, len,
				   ath6kl_पंचांग_policy, शून्य);
	अगर (err)
		वापस err;

	अगर (!tb[ATH6KL_TM_ATTR_CMD])
		वापस -EINVAL;

	चयन (nla_get_u32(tb[ATH6KL_TM_ATTR_CMD])) अणु
	हाल ATH6KL_TM_CMD_TCMD:
		अगर (!tb[ATH6KL_TM_ATTR_DATA])
			वापस -EINVAL;

		buf = nla_data(tb[ATH6KL_TM_ATTR_DATA]);
		buf_len = nla_len(tb[ATH6KL_TM_ATTR_DATA]);

		ath6kl_wmi_test_cmd(ar->wmi, buf, buf_len);

		वापस 0;

	हाल ATH6KL_TM_CMD_RX_REPORT:
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण
