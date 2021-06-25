<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * This file is part of wlcore
 *
 * Copyright (C) 2011 Texas Instruments Inc.
 */

#अगर_अघोषित __WLCORE_HW_OPS_H__
#घोषणा __WLCORE_HW_OPS_H__

#समावेश "wlcore.h"
#समावेश "rx.h"

अटल अंतरभूत u32
wlcore_hw_calc_tx_blocks(काष्ठा wl1271 *wl, u32 len, u32 spare_blks)
अणु
	अगर (!wl->ops->calc_tx_blocks)
		BUG_ON(1);

	वापस wl->ops->calc_tx_blocks(wl, len, spare_blks);
पूर्ण

अटल अंतरभूत व्योम
wlcore_hw_set_tx_desc_blocks(काष्ठा wl1271 *wl, काष्ठा wl1271_tx_hw_descr *desc,
			     u32 blks, u32 spare_blks)
अणु
	अगर (!wl->ops->set_tx_desc_blocks)
		BUG_ON(1);

	वापस wl->ops->set_tx_desc_blocks(wl, desc, blks, spare_blks);
पूर्ण

अटल अंतरभूत व्योम
wlcore_hw_set_tx_desc_data_len(काष्ठा wl1271 *wl,
			       काष्ठा wl1271_tx_hw_descr *desc,
			       काष्ठा sk_buff *skb)
अणु
	अगर (!wl->ops->set_tx_desc_data_len)
		BUG_ON(1);

	wl->ops->set_tx_desc_data_len(wl, desc, skb);
पूर्ण

अटल अंतरभूत क्रमागत wl_rx_buf_align
wlcore_hw_get_rx_buf_align(काष्ठा wl1271 *wl, u32 rx_desc)
अणु

	अगर (!wl->ops->get_rx_buf_align)
		BUG_ON(1);

	वापस wl->ops->get_rx_buf_align(wl, rx_desc);
पूर्ण

अटल अंतरभूत पूर्णांक
wlcore_hw_prepare_पढ़ो(काष्ठा wl1271 *wl, u32 rx_desc, u32 len)
अणु
	अगर (wl->ops->prepare_पढ़ो)
		वापस wl->ops->prepare_पढ़ो(wl, rx_desc, len);

	वापस 0;
पूर्ण

अटल अंतरभूत u32
wlcore_hw_get_rx_packet_len(काष्ठा wl1271 *wl, व्योम *rx_data, u32 data_len)
अणु
	अगर (!wl->ops->get_rx_packet_len)
		BUG_ON(1);

	वापस wl->ops->get_rx_packet_len(wl, rx_data, data_len);
पूर्ण

अटल अंतरभूत पूर्णांक wlcore_hw_tx_delayed_compl(काष्ठा wl1271 *wl)
अणु
	अगर (wl->ops->tx_delayed_compl)
		वापस wl->ops->tx_delayed_compl(wl);

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम wlcore_hw_tx_immediate_compl(काष्ठा wl1271 *wl)
अणु
	अगर (wl->ops->tx_immediate_compl)
		wl->ops->tx_immediate_compl(wl);
पूर्ण

अटल अंतरभूत पूर्णांक
wlcore_hw_init_vअगर(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर)
अणु
	अगर (wl->ops->init_vअगर)
		वापस wl->ops->init_vअगर(wl, wlvअगर);

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम
wlcore_hw_convert_fw_status(काष्ठा wl1271 *wl, व्योम *raw_fw_status,
			    काष्ठा wl_fw_status *fw_status)
अणु
	BUG_ON(!wl->ops->convert_fw_status);

	wl->ops->convert_fw_status(wl, raw_fw_status, fw_status);
पूर्ण

अटल अंतरभूत u32
wlcore_hw_sta_get_ap_rate_mask(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर)
अणु
	अगर (!wl->ops->sta_get_ap_rate_mask)
		BUG_ON(1);

	वापस wl->ops->sta_get_ap_rate_mask(wl, wlvअगर);
पूर्ण

अटल अंतरभूत पूर्णांक wlcore_identअगरy_fw(काष्ठा wl1271 *wl)
अणु
	अगर (wl->ops->identअगरy_fw)
		वापस wl->ops->identअगरy_fw(wl);

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम
wlcore_hw_set_tx_desc_csum(काष्ठा wl1271 *wl,
			   काष्ठा wl1271_tx_hw_descr *desc,
			   काष्ठा sk_buff *skb)
अणु
	अगर (!wl->ops->set_tx_desc_csum)
		BUG_ON(1);

	wl->ops->set_tx_desc_csum(wl, desc, skb);
पूर्ण

अटल अंतरभूत व्योम
wlcore_hw_set_rx_csum(काष्ठा wl1271 *wl,
		      काष्ठा wl1271_rx_descriptor *desc,
		      काष्ठा sk_buff *skb)
अणु
	अगर (wl->ops->set_rx_csum)
		wl->ops->set_rx_csum(wl, desc, skb);
पूर्ण

अटल अंतरभूत u32
wlcore_hw_ap_get_mimo_wide_rate_mask(काष्ठा wl1271 *wl,
				     काष्ठा wl12xx_vअगर *wlvअगर)
अणु
	अगर (wl->ops->ap_get_mimo_wide_rate_mask)
		वापस wl->ops->ap_get_mimo_wide_rate_mask(wl, wlvअगर);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
wlcore_debugfs_init(काष्ठा wl1271 *wl, काष्ठा dentry *rootdir)
अणु
	अगर (wl->ops->debugfs_init)
		वापस wl->ops->debugfs_init(wl, rootdir);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
wlcore_handle_अटल_data(काष्ठा wl1271 *wl, व्योम *अटल_data)
अणु
	अगर (wl->ops->handle_अटल_data)
		वापस wl->ops->handle_अटल_data(wl, अटल_data);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
wlcore_hw_get_spare_blocks(काष्ठा wl1271 *wl, bool is_gem)
अणु
	अगर (!wl->ops->get_spare_blocks)
		BUG_ON(1);

	वापस wl->ops->get_spare_blocks(wl, is_gem);
पूर्ण

अटल अंतरभूत पूर्णांक
wlcore_hw_set_key(काष्ठा wl1271 *wl, क्रमागत set_key_cmd cmd,
		  काष्ठा ieee80211_vअगर *vअगर,
		  काष्ठा ieee80211_sta *sta,
		  काष्ठा ieee80211_key_conf *key_conf)
अणु
	अगर (!wl->ops->set_key)
		BUG_ON(1);

	वापस wl->ops->set_key(wl, cmd, vअगर, sta, key_conf);
पूर्ण

अटल अंतरभूत u32
wlcore_hw_pre_pkt_send(काष्ठा wl1271 *wl, u32 buf_offset, u32 last_len)
अणु
	अगर (wl->ops->pre_pkt_send)
		वापस wl->ops->pre_pkt_send(wl, buf_offset, last_len);

	वापस buf_offset;
पूर्ण

अटल अंतरभूत व्योम
wlcore_hw_sta_rc_update(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर)
अणु
	अगर (wl->ops->sta_rc_update)
		wl->ops->sta_rc_update(wl, wlvअगर);
पूर्ण

अटल अंतरभूत पूर्णांक
wlcore_hw_पूर्णांकerrupt_notअगरy(काष्ठा wl1271 *wl, bool action)
अणु
	अगर (wl->ops->पूर्णांकerrupt_notअगरy)
		वापस wl->ops->पूर्णांकerrupt_notअगरy(wl, action);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
wlcore_hw_rx_ba_filter(काष्ठा wl1271 *wl, bool action)
अणु
	अगर (wl->ops->rx_ba_filter)
		वापस wl->ops->rx_ba_filter(wl, action);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
wlcore_hw_ap_sleep(काष्ठा wl1271 *wl)
अणु
	अगर (wl->ops->ap_sleep)
		वापस wl->ops->ap_sleep(wl);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
wlcore_hw_set_peer_cap(काष्ठा wl1271 *wl,
		       काष्ठा ieee80211_sta_ht_cap *ht_cap,
		       bool allow_ht_operation,
		       u32 rate_set, u8 hlid)
अणु
	अगर (wl->ops->set_peer_cap)
		वापस wl->ops->set_peer_cap(wl, ht_cap, allow_ht_operation,
					     rate_set, hlid);

	वापस 0;
पूर्ण

अटल अंतरभूत u32
wlcore_hw_convert_hwaddr(काष्ठा wl1271 *wl, u32 hwaddr)
अणु
	अगर (!wl->ops->convert_hwaddr)
		BUG_ON(1);

	वापस wl->ops->convert_hwaddr(wl, hwaddr);
पूर्ण

अटल अंतरभूत bool
wlcore_hw_lnk_high_prio(काष्ठा wl1271 *wl, u8 hlid,
			काष्ठा wl1271_link *lnk)
अणु
	अगर (!wl->ops->lnk_high_prio)
		BUG_ON(1);

	वापस wl->ops->lnk_high_prio(wl, hlid, lnk);
पूर्ण

अटल अंतरभूत bool
wlcore_hw_lnk_low_prio(काष्ठा wl1271 *wl, u8 hlid,
		       काष्ठा wl1271_link *lnk)
अणु
	अगर (!wl->ops->lnk_low_prio)
		BUG_ON(1);

	वापस wl->ops->lnk_low_prio(wl, hlid, lnk);
पूर्ण

अटल अंतरभूत पूर्णांक
wlcore_smart_config_start(काष्ठा wl1271 *wl, u32 group_biपंचांगap)
अणु
	अगर (!wl->ops->smart_config_start)
		वापस -EINVAL;

	वापस wl->ops->smart_config_start(wl, group_biपंचांगap);
पूर्ण

अटल अंतरभूत पूर्णांक
wlcore_smart_config_stop(काष्ठा wl1271 *wl)
अणु
	अगर (!wl->ops->smart_config_stop)
		वापस -EINVAL;

	वापस wl->ops->smart_config_stop(wl);
पूर्ण

अटल अंतरभूत पूर्णांक
wlcore_smart_config_set_group_key(काष्ठा wl1271 *wl, u16 group_id,
				  u8 key_len, u8 *key)
अणु
	अगर (!wl->ops->smart_config_set_group_key)
		वापस -EINVAL;

	वापस wl->ops->smart_config_set_group_key(wl, group_id, key_len, key);
पूर्ण

अटल अंतरभूत पूर्णांक
wlcore_hw_set_cac(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर, bool start)
अणु
	अगर (!wl->ops->set_cac)
		वापस -EINVAL;

	वापस wl->ops->set_cac(wl, wlvअगर, start);
पूर्ण

अटल अंतरभूत पूर्णांक
wlcore_hw_dfs_master_restart(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर)
अणु
	अगर (!wl->ops->dfs_master_restart)
		वापस -EINVAL;

	वापस wl->ops->dfs_master_restart(wl, wlvअगर);
पूर्ण
#पूर्ण_अगर
