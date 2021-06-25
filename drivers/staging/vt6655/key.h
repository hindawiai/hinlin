<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Copyright (c) 1996, 2003 VIA Networking Technologies, Inc.
 * All rights reserved.
 *
 * File: key.h
 *
 * Purpose: Implement functions क्रम 802.11i Key management
 *
 * Author: Jerry Chen
 *
 * Date: May 29, 2003
 *
 */

#अगर_अघोषित __KEY_H__
#घोषणा __KEY_H__

#समावेश <net/mac80211.h>

/*---------------------  Export Definitions -------------------------*/
#घोषणा MAX_GROUP_KEY       4
#घोषणा MAX_KEY_TABLE       11
#घोषणा MAX_KEY_LEN         32
#घोषणा AES_KEY_LEN         16

#घोषणा AUTHENTICATOR_KEY   0x10000000
#घोषणा USE_KEYRSC          0x20000000
#घोषणा PAIRWISE_KEY        0x40000000
#घोषणा TRANSMIT_KEY        0x80000000

#घोषणा GROUP_KEY           0x00000000

#घोषणा KEY_CTL_WEP         0x00
#घोषणा KEY_CTL_NONE        0x01
#घोषणा KEY_CTL_TKIP        0x02
#घोषणा KEY_CTL_CCMP        0x03
#घोषणा KEY_CTL_INVALID     0xFF

#घोषणा VNT_KEY_DEFAULTKEY	0x1
#घोषणा VNT_KEY_GROUP_ADDRESS	0x2
#घोषणा VNT_KEY_ALLGROUP	0x4
#घोषणा VNT_KEY_GROUP		0x40
#घोषणा VNT_KEY_PAIRWISE	0x00
#घोषणा VNT_KEY_ONFLY		0x8000
#घोषणा VNT_KEY_ONFLY_ALL	0x4000

काष्ठा vnt_निजी;

पूर्णांक vnt_set_keys(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_sta *sta,
		 काष्ठा ieee80211_vअगर *vअगर, काष्ठा ieee80211_key_conf *key);

#पूर्ण_अगर /* __KEY_H__ */
