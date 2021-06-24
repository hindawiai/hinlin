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

#समावेश "device.h"

#घोषणा MAX_KEY_TABLE       11

#घोषणा KEY_CTL_WEP         0x00
#घोषणा KEY_CTL_NONE        0x01
#घोषणा KEY_CTL_TKIP        0x02
#घोषणा KEY_CTL_CCMP        0x03

#घोषणा VNT_KEY_ONFLY_ALL	0x4000
#घोषणा VNT_KEY_ONFLY		0x8000
#घोषणा VNT_KEY_ALLGROUP	0x04
#घोषणा VNT_KEY_GROUP		0x40
#घोषणा VNT_KEY_PAIRWISE	VNT_KEY_ONFLY
#घोषणा VNT_KEY_GROUP_ADDRESS	(VNT_KEY_ALLGROUP | VNT_KEY_GROUP)
#घोषणा VNT_KEY_DEFAULTKEY	(VNT_KEY_GROUP_ADDRESS | VNT_KEY_ONFLY |\
				VNT_KEY_ONFLY_ALL)

पूर्णांक vnt_key_init_table(काष्ठा vnt_निजी *priv);

पूर्णांक vnt_set_keys(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_sta *sta,
		 काष्ठा ieee80211_vअगर *vअगर, काष्ठा ieee80211_key_conf *key);

#पूर्ण_अगर /* __KEY_H__ */
