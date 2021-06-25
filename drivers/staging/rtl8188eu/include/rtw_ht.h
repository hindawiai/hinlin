<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#अगर_अघोषित _RTW_HT_H_
#घोषणा _RTW_HT_H_

#समावेश <linux/ieee80211.h>

काष्ठा ht_priv अणु
	u32	ht_option;
	u32	ampdu_enable;/* क्रम enable Tx A-MPDU */
	u8	bwmode;/*  */
	u8	ch_offset;/* PRIME_CHNL_OFFSET */
	u8	sgi;/* लघु GI */

	/* क्रम processing Tx A-MPDU */
	u8	agg_enable_biपंचांगap;
	u8	candidate_tid_biपंचांगap;

	काष्ठा ieee80211_ht_cap ht_cap;
पूर्ण;

#पूर्ण_अगर	/* _RTL871X_HT_H_ */
