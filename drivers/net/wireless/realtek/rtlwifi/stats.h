<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2009-2012  Realtek Corporation.*/

#अगर_अघोषित __RTL_STATS_H__
#घोषणा __RTL_STATS_H__

#घोषणा	PHY_RSSI_SLID_WIN_MAX			100
#घोषणा	PHY_LINKQUALITY_SLID_WIN_MAX		20
#घोषणा	PHY_BEACON_RSSI_SLID_WIN_MAX		10

/* Rx smooth factor */
#घोषणा	RX_SMOOTH_FACTOR			20

u8 rtl_query_rxpwrpercentage(s8 antघातer);
u8 rtl_evm_db_to_percentage(s8 value);
दीर्घ rtl_संकेत_scale_mapping(काष्ठा ieee80211_hw *hw, दीर्घ currsig);
व्योम rtl_process_phyinfo(काष्ठा ieee80211_hw *hw, u8 *buffer,
			 काष्ठा rtl_stats *pstatus);

#पूर्ण_अगर
