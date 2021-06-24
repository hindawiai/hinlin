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

#समावेश "core.h"

#अगर_घोषित CONFIG_NL80211_TESTMODE

व्योम ath6kl_पंचांग_rx_event(काष्ठा ath6kl *ar, व्योम *buf, माप_प्रकार buf_len);
पूर्णांक ath6kl_पंचांग_cmd(काष्ठा wiphy *wiphy, काष्ठा wireless_dev *wdev,
		  व्योम *data, पूर्णांक len);

#अन्यथा

अटल अंतरभूत व्योम ath6kl_पंचांग_rx_event(काष्ठा ath6kl *ar, व्योम *buf,
				      माप_प्रकार buf_len)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक ath6kl_पंचांग_cmd(काष्ठा wiphy *wiphy,
				काष्ठा wireless_dev *wdev,
				व्योम *data, पूर्णांक len)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर
