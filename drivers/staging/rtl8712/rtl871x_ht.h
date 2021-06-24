<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2010 Realtek Corporation. All rights reserved.
 *
 * Modअगरications क्रम inclusion पूर्णांकo the Linux staging tree are
 * Copyright(c) 2010 Larry Finger. All rights reserved.
 *
 * Contact inक्रमmation:
 * WLAN FAE <wlanfae@realtek.com>
 * Larry Finger <Larry.Finger@lwfinger.net>
 *
 ******************************************************************************/
#अगर_अघोषित _RTL871X_HT_H_
#घोषणा _RTL871X_HT_H_

#समावेश "osdep_service.h"
#समावेश "wifi.h"

काष्ठा ht_priv अणु
	अचिन्हित पूर्णांक	ht_option;
	अचिन्हित पूर्णांक	ampdu_enable;/*क्रम enable Tx A-MPDU*/
	अचिन्हित अक्षर	baddbareq_issued[16];
	अचिन्हित पूर्णांक	tx_amsdu_enable;/*क्रम enable Tx A-MSDU */
	अचिन्हित पूर्णांक	tx_amdsu_maxlen; /* 1: 8k, 0:4k ; शेष:8k, क्रम tx */
	अचिन्हित पूर्णांक	rx_ampdu_maxlen; /* क्रम rx reordering ctrl win_sz,
					  * updated when join_callback.
					  */
	काष्ठा ieee80211_ht_cap ht_cap;
पूर्ण;

#पूर्ण_अगर	/*_RTL871X_HT_H_ */

