<शैली गुरु>
/*
 * Copyright (c) 2018, The Linux Foundation. All rights reserved.
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
 * OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#समावेश "wcn36xx.h"

काष्ठा fपंचांग_rsp_msg अणु
	u16 msg_id;
	u16 msg_body_length;
	u32 resp_status;
	u8 msg_response[];
पूर्ण __packed;

/* The request buffer of FTM which contains a byte of command and the request */
काष्ठा fपंचांग_payload अणु
	u16 fपंचांग_cmd_type;
	काष्ठा fपंचांग_rsp_msg fपंचांग_cmd_msg;
पूर्ण __packed;

#घोषणा MSG_GET_BUILD_RELEASE_NUMBER 0x32A2

#अगर_घोषित CONFIG_NL80211_TESTMODE
पूर्णांक wcn36xx_पंचांग_cmd(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
		   व्योम *data, पूर्णांक len);

#अन्यथा
अटल अंतरभूत पूर्णांक wcn36xx_पंचांग_cmd(काष्ठा ieee80211_hw *hw,
				 काष्ठा ieee80211_vअगर *vअगर,
				व्योम *data, पूर्णांक len)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर
