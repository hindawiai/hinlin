<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Copyright (c) 1996, 2003 VIA Networking Technologies, Inc.
 * All rights reserved.
 *
 * File: card.h
 *
 * Purpose: Provide functions to setup NIC operation mode
 *
 * Author: Tevin Chen
 *
 * Date: May 21, 1996
 *
 */

#अगर_अघोषित __CARD_H__
#घोषणा __CARD_H__
#समावेश "device.h"

/* init card type */

#घोषणा CB_MAX_CHANNEL_24G	14
#घोषणा CB_MAX_CHANNEL_5G	42 /* add channel9(5045MHz), 41==>42 */
#घोषणा CB_MAX_CHANNEL		(CB_MAX_CHANNEL_24G + CB_MAX_CHANNEL_5G)

काष्ठा vnt_निजी;

पूर्णांक vnt_set_channel(काष्ठा vnt_निजी *priv, u32 connection_channel);
पूर्णांक vnt_set_rspinf(काष्ठा vnt_निजी *priv, u8 bb_type);
पूर्णांक vnt_update_अगरs(काष्ठा vnt_निजी *priv);
व्योम vnt_update_top_rates(काष्ठा vnt_निजी *priv);
bool vnt_ofdm_min_rate(काष्ठा vnt_निजी *priv);
पूर्णांक vnt_adjust_tsf(काष्ठा vnt_निजी *priv, u8 rx_rate,
		   u64 समय_stamp, u64 local_tsf);
bool vnt_get_current_tsf(काष्ठा vnt_निजी *priv, u64 *current_tsf);
bool vnt_clear_current_tsf(काष्ठा vnt_निजी *priv);
पूर्णांक vnt_reset_next_tbtt(काष्ठा vnt_निजी *priv, u16 beacon_पूर्णांकerval);
पूर्णांक vnt_update_next_tbtt(काष्ठा vnt_निजी *priv, u64 tsf,
			 u16 beacon_पूर्णांकerval);
u64 vnt_get_next_tbtt(u64 tsf, u16 beacon_पूर्णांकerval);
u64 vnt_get_tsf_offset(u8 rx_rate, u64 tsf1, u64 tsf2);
पूर्णांक vnt_radio_घातer_off(काष्ठा vnt_निजी *priv);
पूर्णांक vnt_radio_घातer_on(काष्ठा vnt_निजी *priv);
u8 vnt_get_pkt_type(काष्ठा vnt_निजी *priv);
पूर्णांक vnt_set_bss_mode(काष्ठा vnt_निजी *priv);

#पूर्ण_अगर /* __CARD_H__ */
