<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Atlantic Network Driver
 *
 * Copyright (C) 2014-2019 aQuantia Corporation
 * Copyright (C) 2019-2020 Marvell International Ltd.
 */

/* File aq_nic.h: Declaration of common code क्रम NIC. */

#अगर_अघोषित AQ_NIC_H
#घोषणा AQ_NIC_H

#समावेश <linux/ethtool.h>

#समावेश "aq_common.h"
#समावेश "aq_rss.h"
#समावेश "aq_hw.h"

काष्ठा aq_ring_s;
काष्ठा aq_hw_ops;
काष्ठा aq_fw_s;
काष्ठा aq_vec_s;
काष्ठा aq_macsec_cfg;
काष्ठा aq_ptp_s;
क्रमागत aq_rx_filter_type;

क्रमागत aq_fc_mode अणु
	AQ_NIC_FC_OFF = 0,
	AQ_NIC_FC_TX,
	AQ_NIC_FC_RX,
	AQ_NIC_FC_FULL,
पूर्ण;

काष्ठा aq_fc_info अणु
	क्रमागत aq_fc_mode req;
	क्रमागत aq_fc_mode cur;
पूर्ण;

काष्ठा aq_nic_cfg_s अणु
	स्थिर काष्ठा aq_hw_caps_s *aq_hw_caps;
	u64 features;
	u32 rxds;		/* rx ring size, descriptors # */
	u32 txds;		/* tx ring size, descriptors # */
	u32 vecs;		/* allocated rx/tx vectors */
	u32 link_irq_vec;
	u32 irq_type;
	u32 itr;
	u16 rx_itr;
	u16 tx_itr;
	u32 rxpageorder;
	u32 num_rss_queues;
	u32 mtu;
	काष्ठा aq_fc_info fc;
	u32 link_speed_msk;
	u32 wol;
	u8 is_vlan_rx_strip;
	u8 is_vlan_tx_insert;
	bool is_vlan_क्रमce_promisc;
	u16 is_mc_list_enabled;
	u16 mc_list_count;
	bool is_स्वतःneg;
	bool is_polling;
	bool is_rss;
	bool is_lro;
	bool is_qos;
	bool is_ptp;
	bool is_media_detect;
	पूर्णांक करोwnshअगरt_counter;
	क्रमागत aq_tc_mode tc_mode;
	u32 priv_flags;
	u8  tcs;
	u8 prio_tc_map[8];
	u32 tc_max_rate[AQ_CFG_TCS_MAX];
	अचिन्हित दीर्घ tc_min_rate_msk;
	u32 tc_min_rate[AQ_CFG_TCS_MAX];
	काष्ठा aq_rss_parameters aq_rss;
	u32 eee_speeds;
पूर्ण;

#घोषणा AQ_NIC_FLAG_STARTED     0x00000004U
#घोषणा AQ_NIC_FLAG_STOPPING    0x00000008U
#घोषणा AQ_NIC_FLAG_RESETTING   0x00000010U
#घोषणा AQ_NIC_FLAG_CLOSING     0x00000020U
#घोषणा AQ_NIC_PTP_DPATH_UP     0x02000000U
#घोषणा AQ_NIC_LINK_DOWN        0x04000000U
#घोषणा AQ_NIC_FLAG_ERR_UNPLUG  0x40000000U
#घोषणा AQ_NIC_FLAG_ERR_HW      0x80000000U

#घोषणा AQ_NIC_QUIRK_BAD_PTP    BIT(0)

#घोषणा AQ_NIC_WOL_MODES        (WAKE_MAGIC |\
				 WAKE_PHY)

#घोषणा AQ_NIC_CFG_RING_PER_TC(_NIC_CFG_) \
	(((_NIC_CFG_)->tc_mode == AQ_TC_MODE_4TCS) ? 8 : 4)

#घोषणा AQ_NIC_CFG_TCVEC2RING(_NIC_CFG_, _TC_, _VEC_) \
	((_TC_) * AQ_NIC_CFG_RING_PER_TC(_NIC_CFG_) + (_VEC_))

#घोषणा AQ_NIC_RING2QMAP(_NIC_, _ID_) \
	((_ID_) / AQ_NIC_CFG_RING_PER_TC(&(_NIC_)->aq_nic_cfg) * \
		(_NIC_)->aq_vecs + \
	((_ID_) % AQ_NIC_CFG_RING_PER_TC(&(_NIC_)->aq_nic_cfg)))

काष्ठा aq_hw_rx_fl2 अणु
	काष्ठा aq_rx_filter_vlan aq_vlans[AQ_VLAN_MAX_FILTERS];
पूर्ण;

काष्ठा aq_hw_rx_fl3l4 अणु
	u8 active_ipv4;
	u8 active_ipv6:2;
	u8 is_ipv6;
	u8 reserved_count;
पूर्ण;

काष्ठा aq_hw_rx_fltrs_s अणु
	काष्ठा hlist_head     filter_list;
	u16                   active_filters;
	काष्ठा aq_hw_rx_fl2   fl2;
	काष्ठा aq_hw_rx_fl3l4 fl3l4;
	/* filter ether type */
	u8 fet_reserved_count;
पूर्ण;

काष्ठा aq_nic_s अणु
	atomic_t flags;
	u32 msg_enable;
	काष्ठा aq_vec_s *aq_vec[AQ_CFG_VECS_MAX];
	काष्ठा aq_ring_s *aq_ring_tx[AQ_HW_QUEUES_MAX];
	काष्ठा aq_hw_s *aq_hw;
	काष्ठा net_device *ndev;
	अचिन्हित पूर्णांक aq_vecs;
	अचिन्हित पूर्णांक packet_filter;
	अचिन्हित पूर्णांक घातer_state;
	u8 port;
	स्थिर काष्ठा aq_hw_ops *aq_hw_ops;
	स्थिर काष्ठा aq_fw_ops *aq_fw_ops;
	काष्ठा aq_nic_cfg_s aq_nic_cfg;
	काष्ठा समयr_list service_समयr;
	काष्ठा work_काष्ठा service_task;
	काष्ठा समयr_list polling_समयr;
	काष्ठा aq_hw_link_status_s link_status;
	काष्ठा अणु
		u32 count;
		u8 ar[AQ_HW_MULTICAST_ADDRESS_MAX][ETH_ALEN];
	पूर्ण mc_list;
	/* Biपंचांगask of currently asचिन्हित vlans from linux */
	अचिन्हित दीर्घ active_vlans[BITS_TO_LONGS(VLAN_N_VID)];

	काष्ठा pci_dev *pdev;
	अचिन्हित पूर्णांक msix_entry_mask;
	u32 irqvecs;
	/* mutex to serialize FW पूर्णांकerface access operations */
	काष्ठा mutex fwreq_mutex;
#अगर IS_ENABLED(CONFIG_MACSEC)
	काष्ठा aq_macsec_cfg *macsec_cfg;
#पूर्ण_अगर
	/* PTP support */
	काष्ठा aq_ptp_s *aq_ptp;
	काष्ठा aq_hw_rx_fltrs_s aq_hw_rx_fltrs;
पूर्ण;

अटल अंतरभूत काष्ठा device *aq_nic_get_dev(काष्ठा aq_nic_s *self)
अणु
	वापस self->ndev->dev.parent;
पूर्ण

व्योम aq_nic_ndev_init(काष्ठा aq_nic_s *self);
काष्ठा aq_nic_s *aq_nic_alloc_hot(काष्ठा net_device *ndev);
व्योम aq_nic_set_tx_ring(काष्ठा aq_nic_s *self, अचिन्हित पूर्णांक idx,
			काष्ठा aq_ring_s *ring);
काष्ठा net_device *aq_nic_get_ndev(काष्ठा aq_nic_s *self);
पूर्णांक aq_nic_init(काष्ठा aq_nic_s *self);
व्योम aq_nic_cfg_start(काष्ठा aq_nic_s *self);
पूर्णांक aq_nic_ndev_रेजिस्टर(काष्ठा aq_nic_s *self);
व्योम aq_nic_ndev_मुक्त(काष्ठा aq_nic_s *self);
पूर्णांक aq_nic_start(काष्ठा aq_nic_s *self);
अचिन्हित पूर्णांक aq_nic_map_skb(काष्ठा aq_nic_s *self, काष्ठा sk_buff *skb,
			    काष्ठा aq_ring_s *ring);
पूर्णांक aq_nic_xmit(काष्ठा aq_nic_s *self, काष्ठा sk_buff *skb);
पूर्णांक aq_nic_get_regs(काष्ठा aq_nic_s *self, काष्ठा ethtool_regs *regs, व्योम *p);
पूर्णांक aq_nic_get_regs_count(काष्ठा aq_nic_s *self);
u64 *aq_nic_get_stats(काष्ठा aq_nic_s *self, u64 *data);
पूर्णांक aq_nic_stop(काष्ठा aq_nic_s *self);
व्योम aq_nic_deinit(काष्ठा aq_nic_s *self, bool link_करोwn);
व्योम aq_nic_set_घातer(काष्ठा aq_nic_s *self);
व्योम aq_nic_मुक्त_hot_resources(काष्ठा aq_nic_s *self);
व्योम aq_nic_मुक्त_vectors(काष्ठा aq_nic_s *self);
पूर्णांक aq_nic_पुनः_स्मृति_vectors(काष्ठा aq_nic_s *self);
पूर्णांक aq_nic_set_mtu(काष्ठा aq_nic_s *self, पूर्णांक new_mtu);
पूर्णांक aq_nic_set_mac(काष्ठा aq_nic_s *self, काष्ठा net_device *ndev);
पूर्णांक aq_nic_set_packet_filter(काष्ठा aq_nic_s *self, अचिन्हित पूर्णांक flags);
पूर्णांक aq_nic_set_multicast_list(काष्ठा aq_nic_s *self, काष्ठा net_device *ndev);
अचिन्हित पूर्णांक aq_nic_get_link_speed(काष्ठा aq_nic_s *self);
व्योम aq_nic_get_link_ksettings(काष्ठा aq_nic_s *self,
			       काष्ठा ethtool_link_ksettings *cmd);
पूर्णांक aq_nic_set_link_ksettings(काष्ठा aq_nic_s *self,
			      स्थिर काष्ठा ethtool_link_ksettings *cmd);
काष्ठा aq_nic_cfg_s *aq_nic_get_cfg(काष्ठा aq_nic_s *self);
u32 aq_nic_get_fw_version(काष्ठा aq_nic_s *self);
पूर्णांक aq_nic_set_loopback(काष्ठा aq_nic_s *self);
पूर्णांक aq_nic_set_करोwnshअगरt(काष्ठा aq_nic_s *self, पूर्णांक val);
पूर्णांक aq_nic_set_media_detect(काष्ठा aq_nic_s *self, पूर्णांक val);
पूर्णांक aq_nic_update_पूर्णांकerrupt_moderation_settings(काष्ठा aq_nic_s *self);
व्योम aq_nic_shutकरोwn(काष्ठा aq_nic_s *self);
u8 aq_nic_reserve_filter(काष्ठा aq_nic_s *self, क्रमागत aq_rx_filter_type type);
व्योम aq_nic_release_filter(काष्ठा aq_nic_s *self, क्रमागत aq_rx_filter_type type,
			   u32 location);
पूर्णांक aq_nic_setup_tc_mqprio(काष्ठा aq_nic_s *self, u32 tcs, u8 *prio_tc_map);
पूर्णांक aq_nic_setup_tc_max_rate(काष्ठा aq_nic_s *self, स्थिर अचिन्हित पूर्णांक tc,
			     स्थिर u32 max_rate);
पूर्णांक aq_nic_setup_tc_min_rate(काष्ठा aq_nic_s *self, स्थिर अचिन्हित पूर्णांक tc,
			     स्थिर u32 min_rate);
#पूर्ण_अगर /* AQ_NIC_H */
