<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/* Copyright (c) 2015-2016 Quantenna Communications. All rights reserved. */

#अगर_अघोषित _QTN_FMAC_QLINK_UTIL_H_
#घोषणा _QTN_FMAC_QLINK_UTIL_H_

#समावेश <linux/types.h>
#समावेश <linux/skbuff.h>
#समावेश <net/cfg80211.h>

#समावेश "qlink.h"

अटल अंतरभूत व्योम
qtnf_cmd_skb_put_buffer(काष्ठा sk_buff *skb, स्थिर u8 *buf_src, माप_प्रकार len)
अणु
	skb_put_data(skb, buf_src, len);
पूर्ण

अटल अंतरभूत व्योम qtnf_cmd_skb_put_tlv_arr(काष्ठा sk_buff *skb,
					    u16 tlv_id, स्थिर u8 arr[],
					    माप_प्रकार arr_len)
अणु
	काष्ठा qlink_tlv_hdr *hdr;

	hdr = skb_put(skb, माप(*hdr) + round_up(arr_len, QLINK_ALIGN));
	hdr->type = cpu_to_le16(tlv_id);
	hdr->len = cpu_to_le16(arr_len);
	स_नकल(hdr->val, arr, arr_len);
पूर्ण

अटल अंतरभूत व्योम qtnf_cmd_skb_put_tlv_u32(काष्ठा sk_buff *skb,
					    u16 tlv_id, u32 value)
अणु
	काष्ठा qlink_tlv_hdr *hdr = skb_put(skb, माप(*hdr) + माप(value));
	__le32 पंचांगp = cpu_to_le32(value);

	hdr->type = cpu_to_le16(tlv_id);
	hdr->len = cpu_to_le16(माप(value));
	स_नकल(hdr->val, &पंचांगp, माप(पंचांगp));
पूर्ण

u16 qlink_अगरace_type_to_nl_mask(u16 qlink_type);
u8 qlink_chan_width_mask_to_nl(u16 qlink_mask);
व्योम qlink_chandef_q2cfg(काष्ठा wiphy *wiphy,
			 स्थिर काष्ठा qlink_chandef *qch,
			 काष्ठा cfg80211_chan_def *chdef);
व्योम qlink_chandef_cfg2q(स्थिर काष्ठा cfg80211_chan_def *chdef,
			 काष्ठा qlink_chandef *qch);
क्रमागत qlink_hidden_ssid qlink_hidden_ssid_nl2q(क्रमागत nl80211_hidden_ssid nl_val);
bool qtnf_utils_is_bit_set(स्थिर u8 *arr, अचिन्हित पूर्णांक bit,
			   अचिन्हित पूर्णांक arr_max_len);
व्योम qlink_acl_data_cfg2q(स्थिर काष्ठा cfg80211_acl_data *acl,
			  काष्ठा qlink_acl_data *qacl);
क्रमागत qlink_band qlink_utils_band_cfg2q(क्रमागत nl80211_band band);
क्रमागत qlink_dfs_state qlink_utils_dfs_state_cfg2q(क्रमागत nl80211_dfs_state state);
u32 qlink_utils_chflags_cfg2q(u32 cfgflags);
व्योम qlink_utils_regrule_q2nl(काष्ठा ieee80211_reg_rule *rule,
			      स्थिर काष्ठा qlink_tlv_reg_rule *tlv_rule);

#घोषणा qlink_क्रम_each_tlv(_tlv, _start, _datalen)			\
	क्रम (_tlv = (स्थिर काष्ठा qlink_tlv_hdr *)(_start);		\
	     (स्थिर u8 *)(_start) + (_datalen) - (स्थिर u8 *)_tlv >=	\
		(पूर्णांक)माप(*_tlv) &&					\
	     (स्थिर u8 *)(_start) + (_datalen) - (स्थिर u8 *)_tlv >=	\
		(पूर्णांक)माप(*_tlv) + le16_to_cpu(_tlv->len);		\
	     _tlv = (स्थिर काष्ठा qlink_tlv_hdr *)(_tlv->val +		\
		round_up(le16_to_cpu(_tlv->len), QLINK_ALIGN)))

#घोषणा qlink_tlv_parsing_ok(_tlv_last, _start, _datalen)	\
	((स्थिर u8 *)(_tlv_last) == \
		(स्थिर u8 *)(_start) + round_up(_datalen, QLINK_ALIGN))

#पूर्ण_अगर /* _QTN_FMAC_QLINK_UTIL_H_ */
