<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Atlantic Network Driver
 *
 * Copyright (C) 2014-2019 aQuantia Corporation
 * Copyright (C) 2019-2020 Marvell International Ltd.
 */

/* File aq_hw.h: Declaration of असलtract पूर्णांकerface क्रम NIC hardware specअगरic
 * functions.
 */

#अगर_अघोषित AQ_HW_H
#घोषणा AQ_HW_H

#समावेश "aq_common.h"
#समावेश "aq_rss.h"
#समावेश "hw_atl/hw_atl_utils.h"

#घोषणा AQ_HW_MAC_COUNTER_HZ   312500000ll
#घोषणा AQ_HW_PHY_COUNTER_HZ   160000000ll

क्रमागत aq_tc_mode अणु
	AQ_TC_MODE_INVALID = -1,
	AQ_TC_MODE_8TCS,
	AQ_TC_MODE_4TCS,
पूर्ण;

#घोषणा AQ_RX_FIRST_LOC_FVLANID     0U
#घोषणा AQ_RX_LAST_LOC_FVLANID	   15U
#घोषणा AQ_RX_FIRST_LOC_FETHERT    16U
#घोषणा AQ_RX_LAST_LOC_FETHERT	   31U
#घोषणा AQ_RX_FIRST_LOC_FL3L4	   32U
#घोषणा AQ_RX_LAST_LOC_FL3L4	   39U
#घोषणा AQ_RX_MAX_RXNFC_LOC	   AQ_RX_LAST_LOC_FL3L4
#घोषणा AQ_VLAN_MAX_FILTERS   \
			(AQ_RX_LAST_LOC_FVLANID - AQ_RX_FIRST_LOC_FVLANID + 1U)
#घोषणा AQ_RX_QUEUE_NOT_ASSIGNED   0xFFU

#घोषणा AQ_FRAC_PER_NS 0x100000000LL

/* Used क्रम rate to Mbps conversion */
#घोषणा AQ_MBPS_DIVISOR         125000 /* 1000000 / 8 */

/* NIC H/W capabilities */
काष्ठा aq_hw_caps_s अणु
	u64 hw_features;
	u64 link_speed_msk;
	अचिन्हित पूर्णांक hw_priv_flags;
	u32 media_type;
	u32 rxds_max;
	u32 txds_max;
	u32 rxds_min;
	u32 txds_min;
	u32 txhwb_alignment;
	u32 irq_mask;
	u32 vecs;
	u32 mtu;
	u32 mac_regs_count;
	u32 hw_alive_check_addr;
	u8 msix_irqs;
	u8 tcs_max;
	u8 rxd_alignment;
	u8 rxd_size;
	u8 txd_alignment;
	u8 txd_size;
	u8 tx_rings;
	u8 rx_rings;
	bool flow_control;
	bool is_64_dma;
	bool op64bit;
	u32 quirks;
	u32 priv_data_len;
पूर्ण;

काष्ठा aq_hw_link_status_s अणु
	अचिन्हित पूर्णांक mbps;
	bool full_duplex;
	u32 lp_link_speed_msk;
	u32 lp_flow_control;
पूर्ण;

काष्ठा aq_stats_s अणु
	u64 uprc;
	u64 mprc;
	u64 bprc;
	u64 erpt;
	u64 uptc;
	u64 mptc;
	u64 bptc;
	u64 erpr;
	u64 mbtc;
	u64 bbtc;
	u64 mbrc;
	u64 bbrc;
	u64 ubrc;
	u64 ubtc;
	u64 dpc;
	u64 dma_pkt_rc;
	u64 dma_pkt_tc;
	u64 dma_oct_rc;
	u64 dma_oct_tc;
पूर्ण;

#घोषणा AQ_HW_IRQ_INVALID 0U
#घोषणा AQ_HW_IRQ_LEGACY  1U
#घोषणा AQ_HW_IRQ_MSI     2U
#घोषणा AQ_HW_IRQ_MSIX    3U

#घोषणा AQ_HW_SERVICE_IRQS   1U

#घोषणा AQ_HW_POWER_STATE_D0   0U
#घोषणा AQ_HW_POWER_STATE_D3   3U

#घोषणा AQ_HW_FLAG_STARTED     0x00000004U
#घोषणा AQ_HW_FLAG_STOPPING    0x00000008U
#घोषणा AQ_HW_FLAG_RESETTING   0x00000010U
#घोषणा AQ_HW_FLAG_CLOSING     0x00000020U
#घोषणा AQ_HW_PTP_AVAILABLE    0x01000000U
#घोषणा AQ_HW_LINK_DOWN        0x04000000U
#घोषणा AQ_HW_FLAG_ERR_UNPLUG  0x40000000U
#घोषणा AQ_HW_FLAG_ERR_HW      0x80000000U

#घोषणा AQ_HW_FLAG_ERRORS      (AQ_HW_FLAG_ERR_HW | AQ_HW_FLAG_ERR_UNPLUG)

#घोषणा AQ_NIC_FLAGS_IS_NOT_READY (AQ_NIC_FLAG_STOPPING | \
			AQ_NIC_FLAG_RESETTING | AQ_NIC_FLAG_CLOSING | \
			AQ_NIC_FLAG_ERR_UNPLUG | AQ_NIC_FLAG_ERR_HW)

#घोषणा AQ_NIC_FLAGS_IS_NOT_TX_READY (AQ_NIC_FLAGS_IS_NOT_READY | \
					AQ_NIC_LINK_DOWN)

#घोषणा AQ_HW_MEDIA_TYPE_TP    1U
#घोषणा AQ_HW_MEDIA_TYPE_FIBRE 2U

#घोषणा AQ_HW_TXD_MULTIPLE 8U
#घोषणा AQ_HW_RXD_MULTIPLE 8U

#घोषणा AQ_HW_QUEUES_MAX                32U
#घोषणा AQ_HW_MULTICAST_ADDRESS_MAX     32U

#घोषणा AQ_HW_PTP_TC                    2U

#घोषणा AQ_HW_LED_BLINK    0x2U
#घोषणा AQ_HW_LED_DEFAULT  0x0U

#घोषणा AQ_HW_MEDIA_DETECT_CNT 6000

क्रमागत aq_priv_flags अणु
	AQ_HW_LOOPBACK_DMA_SYS,
	AQ_HW_LOOPBACK_PKT_SYS,
	AQ_HW_LOOPBACK_DMA_NET,
	AQ_HW_LOOPBACK_PHYINT_SYS,
	AQ_HW_LOOPBACK_PHYEXT_SYS,
पूर्ण;

#घोषणा AQ_HW_LOOPBACK_MASK	(BIT(AQ_HW_LOOPBACK_DMA_SYS) |\
				 BIT(AQ_HW_LOOPBACK_PKT_SYS) |\
				 BIT(AQ_HW_LOOPBACK_DMA_NET) |\
				 BIT(AQ_HW_LOOPBACK_PHYINT_SYS) |\
				 BIT(AQ_HW_LOOPBACK_PHYEXT_SYS))

#घोषणा ATL_HW_CHIP_MIPS         0x00000001U
#घोषणा ATL_HW_CHIP_TPO2         0x00000002U
#घोषणा ATL_HW_CHIP_RPF2         0x00000004U
#घोषणा ATL_HW_CHIP_MPI_AQ       0x00000010U
#घोषणा ATL_HW_CHIP_ATLANTIC     0x00800000U
#घोषणा ATL_HW_CHIP_REVISION_A0  0x01000000U
#घोषणा ATL_HW_CHIP_REVISION_B0  0x02000000U
#घोषणा ATL_HW_CHIP_REVISION_B1  0x04000000U
#घोषणा ATL_HW_CHIP_ANTIGUA      0x08000000U

#घोषणा ATL_HW_IS_CHIP_FEATURE(_HW_, _F_) (!!(ATL_HW_CHIP_##_F_ & \
	(_HW_)->chip_features))

काष्ठा aq_hw_s अणु
	atomic_t flags;
	u8 rbl_enabled:1;
	काष्ठा aq_nic_cfg_s *aq_nic_cfg;
	स्थिर काष्ठा aq_fw_ops *aq_fw_ops;
	व्योम __iomem *mmio;
	काष्ठा aq_hw_link_status_s aq_link_status;
	काष्ठा hw_atl_utils_mbox mbox;
	काष्ठा hw_atl_stats_s last_stats;
	काष्ठा aq_stats_s curr_stats;
	u64 speed;
	u32 itr_tx;
	u32 itr_rx;
	अचिन्हित पूर्णांक chip_features;
	u32 fw_ver_actual;
	atomic_t dpc;
	u32 mbox_addr;
	u32 rpc_addr;
	u32 settings_addr;
	u32 rpc_tid;
	काष्ठा hw_atl_utils_fw_rpc rpc;
	s64 ptp_clk_offset;
	u16 phy_id;
	व्योम *priv;
पूर्ण;

काष्ठा aq_ring_s;
काष्ठा aq_ring_param_s;
काष्ठा sk_buff;
काष्ठा aq_rx_filter_l3l4;

काष्ठा aq_hw_ops अणु

	पूर्णांक (*hw_ring_tx_xmit)(काष्ठा aq_hw_s *self, काष्ठा aq_ring_s *aq_ring,
			       अचिन्हित पूर्णांक frags);

	पूर्णांक (*hw_ring_rx_receive)(काष्ठा aq_hw_s *self,
				  काष्ठा aq_ring_s *aq_ring);

	पूर्णांक (*hw_ring_rx_fill)(काष्ठा aq_hw_s *self, काष्ठा aq_ring_s *aq_ring,
			       अचिन्हित पूर्णांक sw_tail_old);

	पूर्णांक (*hw_ring_tx_head_update)(काष्ठा aq_hw_s *self,
				      काष्ठा aq_ring_s *aq_ring);

	पूर्णांक (*hw_set_mac_address)(काष्ठा aq_hw_s *self, u8 *mac_addr);

	पूर्णांक (*hw_soft_reset)(काष्ठा aq_hw_s *self);

	पूर्णांक (*hw_prepare)(काष्ठा aq_hw_s *self,
			  स्थिर काष्ठा aq_fw_ops **fw_ops);

	पूर्णांक (*hw_reset)(काष्ठा aq_hw_s *self);

	पूर्णांक (*hw_init)(काष्ठा aq_hw_s *self, u8 *mac_addr);

	पूर्णांक (*hw_start)(काष्ठा aq_hw_s *self);

	पूर्णांक (*hw_stop)(काष्ठा aq_hw_s *self);

	पूर्णांक (*hw_ring_tx_init)(काष्ठा aq_hw_s *self, काष्ठा aq_ring_s *aq_ring,
			       काष्ठा aq_ring_param_s *aq_ring_param);

	पूर्णांक (*hw_ring_tx_start)(काष्ठा aq_hw_s *self,
				काष्ठा aq_ring_s *aq_ring);

	पूर्णांक (*hw_ring_tx_stop)(काष्ठा aq_hw_s *self,
			       काष्ठा aq_ring_s *aq_ring);

	पूर्णांक (*hw_ring_rx_init)(काष्ठा aq_hw_s *self,
			       काष्ठा aq_ring_s *aq_ring,
			       काष्ठा aq_ring_param_s *aq_ring_param);

	पूर्णांक (*hw_ring_rx_start)(काष्ठा aq_hw_s *self,
				काष्ठा aq_ring_s *aq_ring);

	पूर्णांक (*hw_ring_rx_stop)(काष्ठा aq_hw_s *self,
			       काष्ठा aq_ring_s *aq_ring);

	पूर्णांक (*hw_irq_enable)(काष्ठा aq_hw_s *self, u64 mask);

	पूर्णांक (*hw_irq_disable)(काष्ठा aq_hw_s *self, u64 mask);

	पूर्णांक (*hw_irq_पढ़ो)(काष्ठा aq_hw_s *self, u64 *mask);

	पूर्णांक (*hw_packet_filter_set)(काष्ठा aq_hw_s *self,
				    अचिन्हित पूर्णांक packet_filter);

	पूर्णांक (*hw_filter_l3l4_set)(काष्ठा aq_hw_s *self,
				  काष्ठा aq_rx_filter_l3l4 *data);

	पूर्णांक (*hw_filter_l3l4_clear)(काष्ठा aq_hw_s *self,
				    काष्ठा aq_rx_filter_l3l4 *data);

	पूर्णांक (*hw_filter_l2_set)(काष्ठा aq_hw_s *self,
				काष्ठा aq_rx_filter_l2 *data);

	पूर्णांक (*hw_filter_l2_clear)(काष्ठा aq_hw_s *self,
				  काष्ठा aq_rx_filter_l2 *data);

	पूर्णांक (*hw_filter_vlan_set)(काष्ठा aq_hw_s *self,
				  काष्ठा aq_rx_filter_vlan *aq_vlans);

	पूर्णांक (*hw_filter_vlan_ctrl)(काष्ठा aq_hw_s *self, bool enable);

	पूर्णांक (*hw_multicast_list_set)(काष्ठा aq_hw_s *self,
				     u8 ar_mac[AQ_HW_MULTICAST_ADDRESS_MAX]
				     [ETH_ALEN],
				     u32 count);

	पूर्णांक (*hw_पूर्णांकerrupt_moderation_set)(काष्ठा aq_hw_s *self);

	पूर्णांक (*hw_rss_set)(काष्ठा aq_hw_s *self,
			  काष्ठा aq_rss_parameters *rss_params);

	पूर्णांक (*hw_rss_hash_set)(काष्ठा aq_hw_s *self,
			       काष्ठा aq_rss_parameters *rss_params);

	पूर्णांक (*hw_tc_rate_limit_set)(काष्ठा aq_hw_s *self);

	पूर्णांक (*hw_get_regs)(काष्ठा aq_hw_s *self,
			   स्थिर काष्ठा aq_hw_caps_s *aq_hw_caps,
			   u32 *regs_buff);

	काष्ठा aq_stats_s *(*hw_get_hw_stats)(काष्ठा aq_hw_s *self);

	u32 (*hw_get_fw_version)(काष्ठा aq_hw_s *self);

	पूर्णांक (*hw_set_offload)(काष्ठा aq_hw_s *self,
			      काष्ठा aq_nic_cfg_s *aq_nic_cfg);

	पूर्णांक (*hw_ring_hwts_rx_fill)(काष्ठा aq_hw_s *self,
				    काष्ठा aq_ring_s *aq_ring);

	पूर्णांक (*hw_ring_hwts_rx_receive)(काष्ठा aq_hw_s *self,
				       काष्ठा aq_ring_s *ring);

	व्योम (*hw_get_ptp_ts)(काष्ठा aq_hw_s *self, u64 *stamp);

	पूर्णांक (*hw_adj_घड़ी_freq)(काष्ठा aq_hw_s *self, s32 delta);

	पूर्णांक (*hw_adj_sys_घड़ी)(काष्ठा aq_hw_s *self, s64 delta);

	पूर्णांक (*hw_set_sys_घड़ी)(काष्ठा aq_hw_s *self, u64 समय, u64 ts);

	पूर्णांक (*hw_ts_to_sys_घड़ी)(काष्ठा aq_hw_s *self, u64 ts, u64 *समय);

	पूर्णांक (*hw_gpio_pulse)(काष्ठा aq_hw_s *self, u32 index, u64 start,
			     u32 period);

	पूर्णांक (*hw_extts_gpio_enable)(काष्ठा aq_hw_s *self, u32 index,
				    u32 enable);

	पूर्णांक (*hw_get_sync_ts)(काष्ठा aq_hw_s *self, u64 *ts);

	u16 (*rx_extract_ts)(काष्ठा aq_hw_s *self, u8 *p, अचिन्हित पूर्णांक len,
			     u64 *बारtamp);

	पूर्णांक (*extract_hwts)(काष्ठा aq_hw_s *self, u8 *p, अचिन्हित पूर्णांक len,
			    u64 *बारtamp);

	पूर्णांक (*hw_set_fc)(काष्ठा aq_hw_s *self, u32 fc, u32 tc);

	पूर्णांक (*hw_set_loopback)(काष्ठा aq_hw_s *self, u32 mode, bool enable);

	पूर्णांक (*hw_get_mac_temp)(काष्ठा aq_hw_s *self, u32 *temp);
पूर्ण;

काष्ठा aq_fw_ops अणु
	पूर्णांक (*init)(काष्ठा aq_hw_s *self);

	पूर्णांक (*deinit)(काष्ठा aq_hw_s *self);

	पूर्णांक (*reset)(काष्ठा aq_hw_s *self);

	पूर्णांक (*renegotiate)(काष्ठा aq_hw_s *self);

	पूर्णांक (*get_mac_permanent)(काष्ठा aq_hw_s *self, u8 *mac);

	पूर्णांक (*set_link_speed)(काष्ठा aq_hw_s *self, u32 speed);

	पूर्णांक (*set_state)(काष्ठा aq_hw_s *self,
			 क्रमागत hal_atl_utils_fw_state_e state);

	पूर्णांक (*update_link_status)(काष्ठा aq_hw_s *self);

	पूर्णांक (*update_stats)(काष्ठा aq_hw_s *self);

	पूर्णांक (*get_mac_temp)(काष्ठा aq_hw_s *self, पूर्णांक *temp);

	पूर्णांक (*get_phy_temp)(काष्ठा aq_hw_s *self, पूर्णांक *temp);

	u32 (*get_flow_control)(काष्ठा aq_hw_s *self, u32 *fcmode);

	पूर्णांक (*set_flow_control)(काष्ठा aq_hw_s *self);

	पूर्णांक (*led_control)(काष्ठा aq_hw_s *self, u32 mode);

	पूर्णांक (*set_phyloopback)(काष्ठा aq_hw_s *self, u32 mode, bool enable);

	पूर्णांक (*set_घातer)(काष्ठा aq_hw_s *self, अचिन्हित पूर्णांक घातer_state,
			 u8 *mac);

	पूर्णांक (*send_fw_request)(काष्ठा aq_hw_s *self,
			       स्थिर काष्ठा hw_fw_request_अगरace *fw_req,
			       माप_प्रकार size);

	व्योम (*enable_ptp)(काष्ठा aq_hw_s *self, पूर्णांक enable);

	व्योम (*adjust_ptp)(काष्ठा aq_hw_s *self, uपूर्णांक64_t adj);

	पूर्णांक (*set_eee_rate)(काष्ठा aq_hw_s *self, u32 speed);

	पूर्णांक (*get_eee_rate)(काष्ठा aq_hw_s *self, u32 *rate,
			    u32 *supported_rates);

	पूर्णांक (*set_करोwnshअगरt)(काष्ठा aq_hw_s *self, u32 counter);

	पूर्णांक (*set_media_detect)(काष्ठा aq_hw_s *self, bool enable);

	u32 (*get_link_capabilities)(काष्ठा aq_hw_s *self);

	पूर्णांक (*send_macsec_req)(काष्ठा aq_hw_s *self,
			       काष्ठा macsec_msg_fw_request *msg,
			       काष्ठा macsec_msg_fw_response *resp);
पूर्ण;

#पूर्ण_अगर /* AQ_HW_H */
