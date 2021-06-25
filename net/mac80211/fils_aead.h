<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * FILS AEAD क्रम (Re)Association Request/Response frames
 * Copyright 2016, Qualcomm Atheros, Inc.
 */

#अगर_अघोषित FILS_AEAD_H
#घोषणा FILS_AEAD_H

पूर्णांक fils_encrypt_assoc_req(काष्ठा sk_buff *skb,
			   काष्ठा ieee80211_mgd_assoc_data *assoc_data);
पूर्णांक fils_decrypt_assoc_resp(काष्ठा ieee80211_sub_अगर_data *sdata,
			    u8 *frame, माप_प्रकार *frame_len,
			    काष्ठा ieee80211_mgd_assoc_data *assoc_data);

#पूर्ण_अगर /* FILS_AEAD_H */
