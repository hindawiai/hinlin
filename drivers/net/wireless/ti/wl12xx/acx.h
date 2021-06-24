<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * This file is part of wl12xx
 *
 * Copyright (C) 1998-2009, 2011 Texas Instruments. All rights reserved.
 * Copyright (C) 2008-2010 Nokia Corporation
 */

#अगर_अघोषित __WL12XX_ACX_H__
#घोषणा __WL12XX_ACX_H__

#समावेश "../wlcore/wlcore.h"
#समावेश "../wlcore/acx.h"

#घोषणा WL12XX_ACX_ALL_EVENTS_VECTOR	(WL1271_ACX_INTR_WATCHDOG      | \
					WL1271_ACX_INTR_INIT_COMPLETE | \
					WL1271_ACX_INTR_EVENT_A       | \
					WL1271_ACX_INTR_EVENT_B       | \
					WL1271_ACX_INTR_CMD_COMPLETE  | \
					WL1271_ACX_INTR_HW_AVAILABLE  | \
					WL1271_ACX_INTR_DATA)

#घोषणा WL12XX_INTR_MASK		(WL1271_ACX_INTR_WATCHDOG      | \
					WL1271_ACX_INTR_EVENT_A       | \
					WL1271_ACX_INTR_EVENT_B       | \
					WL1271_ACX_INTR_HW_AVAILABLE  | \
					WL1271_ACX_INTR_DATA)

काष्ठा wl1271_acx_host_config_biपंचांगap अणु
	काष्ठा acx_header header;

	__le32 host_cfg_biपंचांगap;
पूर्ण __packed;

काष्ठा wl12xx_acx_tx_statistics अणु
	__le32 पूर्णांकernal_desc_overflow;
पूर्ण  __packed;

काष्ठा wl12xx_acx_rx_statistics अणु
	__le32 out_of_mem;
	__le32 hdr_overflow;
	__le32 hw_stuck;
	__le32 dropped;
	__le32 fcs_err;
	__le32 xfr_hपूर्णांक_trig;
	__le32 path_reset;
	__le32 reset_counter;
पूर्ण __packed;

काष्ठा wl12xx_acx_dma_statistics अणु
	__le32 rx_requested;
	__le32 rx_errors;
	__le32 tx_requested;
	__le32 tx_errors;
पूर्ण  __packed;

काष्ठा wl12xx_acx_isr_statistics अणु
	/* host command complete */
	__le32 cmd_cmplt;

	/* fiqisr() */
	__le32 fiqs;

	/* (INT_STS_ND & INT_TRIG_RX_HEADER) */
	__le32 rx_headers;

	/* (INT_STS_ND & INT_TRIG_RX_CMPLT) */
	__le32 rx_completes;

	/* (INT_STS_ND & INT_TRIG_NO_RX_BUF) */
	__le32 rx_mem_overflow;

	/* (INT_STS_ND & INT_TRIG_S_RX_RDY) */
	__le32 rx_rdys;

	/* irqisr() */
	__le32 irqs;

	/* (INT_STS_ND & INT_TRIG_TX_PROC) */
	__le32 tx_procs;

	/* (INT_STS_ND & INT_TRIG_DECRYPT_DONE) */
	__le32 decrypt_करोne;

	/* (INT_STS_ND & INT_TRIG_DMA0) */
	__le32 dma0_करोne;

	/* (INT_STS_ND & INT_TRIG_DMA1) */
	__le32 dma1_करोne;

	/* (INT_STS_ND & INT_TRIG_TX_EXC_CMPLT) */
	__le32 tx_exch_complete;

	/* (INT_STS_ND & INT_TRIG_COMMAND) */
	__le32 commands;

	/* (INT_STS_ND & INT_TRIG_RX_PROC) */
	__le32 rx_procs;

	/* (INT_STS_ND & INT_TRIG_PM_802) */
	__le32 hw_pm_mode_changes;

	/* (INT_STS_ND & INT_TRIG_ACKNOWLEDGE) */
	__le32 host_acknowledges;

	/* (INT_STS_ND & INT_TRIG_PM_PCI) */
	__le32 pci_pm;

	/* (INT_STS_ND & INT_TRIG_ACM_WAKEUP) */
	__le32 wakeups;

	/* (INT_STS_ND & INT_TRIG_LOW_RSSI) */
	__le32 low_rssi;
पूर्ण __packed;

काष्ठा wl12xx_acx_wep_statistics अणु
	/* WEP address keys configured */
	__le32 addr_key_count;

	/* शेष keys configured */
	__le32 शेष_key_count;

	__le32 reserved;

	/* number of बार that WEP key not found on lookup */
	__le32 key_not_found;

	/* number of बार that WEP key decryption failed */
	__le32 decrypt_fail;

	/* WEP packets decrypted */
	__le32 packets;

	/* WEP decrypt पूर्णांकerrupts */
	__le32 पूर्णांकerrupt;
पूर्ण __packed;

#घोषणा ACX_MISSED_BEACONS_SPREAD 10

काष्ठा wl12xx_acx_pwr_statistics अणु
	/* the amount of enters पूर्णांकo घातer save mode (both PD & ELP) */
	__le32 ps_enter;

	/* the amount of enters पूर्णांकo ELP mode */
	__le32 elp_enter;

	/* the amount of missing beacon पूर्णांकerrupts to the host */
	__le32 missing_bcns;

	/* the amount of wake on host-access बार */
	__le32 wake_on_host;

	/* the amount of wake on समयr-expire */
	__le32 wake_on_समयr_exp;

	/* the number of packets that were transmitted with PS bit set */
	__le32 tx_with_ps;

	/* the number of packets that were transmitted with PS bit clear */
	__le32 tx_without_ps;

	/* the number of received beacons */
	__le32 rcvd_beacons;

	/* the number of entering पूर्णांकo PowerOn (घातer save off) */
	__le32 घातer_save_off;

	/* the number of entries पूर्णांकo घातer save mode */
	__le16 enable_ps;

	/*
	 * the number of निकासs from घातer save, not including failed PS
	 * transitions
	 */
	__le16 disable_ps;

	/*
	 * the number of बार the TSF counter was adjusted because
	 * of drअगरt
	 */
	__le32 fix_tsf_ps;

	/* Gives statistics about the spपढ़ो continuous missed beacons.
	 * The 16 LSB are dedicated क्रम the PS mode.
	 * The 16 MSB are dedicated क्रम the PS mode.
	 * cont_miss_bcns_spपढ़ो[0] - single missed beacon.
	 * cont_miss_bcns_spपढ़ो[1] - two continuous missed beacons.
	 * cont_miss_bcns_spपढ़ो[2] - three continuous missed beacons.
	 * ...
	 * cont_miss_bcns_spपढ़ो[9] - ten and more continuous missed beacons.
	*/
	__le32 cont_miss_bcns_spपढ़ो[ACX_MISSED_BEACONS_SPREAD];

	/* the number of beacons in awake mode */
	__le32 rcvd_awake_beacons;
पूर्ण __packed;

काष्ठा wl12xx_acx_mic_statistics अणु
	__le32 rx_pkts;
	__le32 calc_failure;
पूर्ण __packed;

काष्ठा wl12xx_acx_aes_statistics अणु
	__le32 encrypt_fail;
	__le32 decrypt_fail;
	__le32 encrypt_packets;
	__le32 decrypt_packets;
	__le32 encrypt_पूर्णांकerrupt;
	__le32 decrypt_पूर्णांकerrupt;
पूर्ण __packed;

काष्ठा wl12xx_acx_event_statistics अणु
	__le32 heart_beat;
	__le32 calibration;
	__le32 rx_mismatch;
	__le32 rx_mem_empty;
	__le32 rx_pool;
	__le32 oom_late;
	__le32 phy_transmit_error;
	__le32 tx_stuck;
पूर्ण __packed;

काष्ठा wl12xx_acx_ps_statistics अणु
	__le32 pspoll_समयouts;
	__le32 upsd_समयouts;
	__le32 upsd_max_spसमय;
	__le32 upsd_max_apturn;
	__le32 pspoll_max_apturn;
	__le32 pspoll_utilization;
	__le32 upsd_utilization;
पूर्ण __packed;

काष्ठा wl12xx_acx_rxpipe_statistics अणु
	__le32 rx_prep_beacon_drop;
	__le32 descr_host_पूर्णांक_trig_rx_data;
	__le32 beacon_buffer_thres_host_पूर्णांक_trig_rx_data;
	__le32 missed_beacon_host_पूर्णांक_trig_rx_data;
	__le32 tx_xfr_host_पूर्णांक_trig_rx_data;
पूर्ण __packed;

काष्ठा wl12xx_acx_statistics अणु
	काष्ठा acx_header header;

	काष्ठा wl12xx_acx_tx_statistics tx;
	काष्ठा wl12xx_acx_rx_statistics rx;
	काष्ठा wl12xx_acx_dma_statistics dma;
	काष्ठा wl12xx_acx_isr_statistics isr;
	काष्ठा wl12xx_acx_wep_statistics wep;
	काष्ठा wl12xx_acx_pwr_statistics pwr;
	काष्ठा wl12xx_acx_aes_statistics aes;
	काष्ठा wl12xx_acx_mic_statistics mic;
	काष्ठा wl12xx_acx_event_statistics event;
	काष्ठा wl12xx_acx_ps_statistics ps;
	काष्ठा wl12xx_acx_rxpipe_statistics rxpipe;
पूर्ण __packed;

पूर्णांक wl1271_acx_host_अगर_cfg_biपंचांगap(काष्ठा wl1271 *wl, u32 host_cfg_biपंचांगap);

#पूर्ण_अगर /* __WL12XX_ACX_H__ */
