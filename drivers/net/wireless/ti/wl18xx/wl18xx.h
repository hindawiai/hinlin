<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * This file is part of wl18xx
 *
 * Copyright (C) 2011 Texas Instruments Inc.
 */

#अगर_अघोषित __WL18XX_PRIV_H__
#घोषणा __WL18XX_PRIV_H__

#समावेश "conf.h"

/* minimum FW required क्रम driver */
#घोषणा WL18XX_CHIP_VER		8
#घोषणा WL18XX_IFTYPE_VER	9
#घोषणा WL18XX_MAJOR_VER	WLCORE_FW_VER_IGNORE
#घोषणा WL18XX_SUBTYPE_VER	WLCORE_FW_VER_IGNORE
#घोषणा WL18XX_MINOR_VER	58

#घोषणा WL18XX_CMD_MAX_SIZE          740

#घोषणा WL18XX_AGGR_BUFFER_SIZE		(13 * PAGE_SIZE)

#घोषणा WL18XX_NUM_TX_DESCRIPTORS 32
#घोषणा WL18XX_NUM_RX_DESCRIPTORS 32

#घोषणा WL18XX_NUM_MAC_ADDRESSES 2

#घोषणा WL18XX_RX_BA_MAX_SESSIONS 13

#घोषणा WL18XX_MAX_AP_STATIONS 10
#घोषणा WL18XX_MAX_LINKS 16

काष्ठा wl18xx_priv अणु
	/* buffer क्रम sending commands to FW */
	u8 cmd_buf[WL18XX_CMD_MAX_SIZE];

	काष्ठा wl18xx_priv_conf conf;

	/* Index of last released Tx desc in FW */
	u8 last_fw_rls_idx;

	/* number of keys requiring extra spare mem-blocks */
	पूर्णांक extra_spare_key_count;
पूर्ण;

#घोषणा WL18XX_FW_MAX_TX_STATUS_DESC 33

काष्ठा wl18xx_fw_status_priv अणु
	/*
	 * Index in released_tx_desc क्रम first byte that holds
	 * released tx host desc
	 */
	u8 fw_release_idx;

	/*
	 * Array of host Tx descriptors, where fw_release_idx
	 * indicated the first released idx.
	 */
	u8 released_tx_desc[WL18XX_FW_MAX_TX_STATUS_DESC];

	/* A biपंचांगap representing the currently suspended links. The suspend
	 * is लघु lived, क्रम multi-channel Tx requirements.
	 */
	__le32 link_suspend_biपंचांगap;

	/* packet threshold क्रम an "almost empty" AC,
	 * क्रम Tx schedulng purposes
	 */
	u8 tx_ac_threshold;

	/* number of packets to queue up क्रम a link in PS */
	u8 tx_ps_threshold;

	/* number of packet to queue up क्रम a suspended link */
	u8 tx_suspend_threshold;

	/* Should have less than this number of packets in queue of a slow
	 * link to qualअगरy as high priority link
	 */
	u8 tx_slow_link_prio_threshold;

	/* Should have less than this number of packets in queue of a fast
	 * link to qualअगरy as high priority link
	 */
	u8 tx_fast_link_prio_threshold;

	/* Should have less than this number of packets in queue of a slow
	 * link beक्रमe we stop queuing up packets क्रम it.
	 */
	u8 tx_slow_stop_threshold;

	/* Should have less than this number of packets in queue of a fast
	 * link beक्रमe we stop queuing up packets क्रम it.
	 */
	u8 tx_fast_stop_threshold;

	u8 padding[3];
पूर्ण;

काष्ठा wl18xx_fw_packet_counters अणु
	/* Cumulative counter of released packets per AC */
	u8 tx_released_pkts[NUM_TX_QUEUES];

	/* Cumulative counter of मुक्तd packets per HLID */
	u8 tx_lnk_मुक्त_pkts[WL18XX_MAX_LINKS];

	/* Cumulative counter of released Voice memory blocks */
	u8 tx_voice_released_blks;

	/* Tx rate of the last transmitted packet */
	u8 tx_last_rate;

	/* Tx rate or Tx rate estimate pre-calculated by fw in mbps units */
	u8 tx_last_rate_mbps;

	/* hlid क्रम which the rates were reported */
	u8 hlid;
पूर्ण __packed;

/* FW status रेजिस्टरs */
काष्ठा wl18xx_fw_status अणु
	__le32 पूर्णांकr;
	u8  fw_rx_counter;
	u8  drv_rx_counter;
	u8  reserved;
	u8  tx_results_counter;
	__le32 rx_pkt_descs[WL18XX_NUM_RX_DESCRIPTORS];

	__le32 fw_स_स्थानीय;

	/*
	 * A biपंचांगap (where each bit represents a single HLID)
	 * to indicate अगर the station is in PS mode.
	 */
	__le32 link_ps_biपंचांगap;

	/*
	 * A biपंचांगap (where each bit represents a single HLID) to indicate
	 * अगर the station is in Fast mode
	 */
	__le32 link_fast_biपंचांगap;

	/* Cumulative counter of total released mem blocks since FW-reset */
	__le32 total_released_blks;

	/* Size (in Memory Blocks) of TX pool */
	__le32 tx_total;

	काष्ठा wl18xx_fw_packet_counters counters;

	__le32 log_start_addr;

	/* Private status to be used by the lower drivers */
	काष्ठा wl18xx_fw_status_priv priv;
पूर्ण __packed;

#घोषणा WL18XX_PHY_VERSION_MAX_LEN 20

काष्ठा wl18xx_अटल_data_priv अणु
	अक्षर phy_version[WL18XX_PHY_VERSION_MAX_LEN];
पूर्ण;

काष्ठा wl18xx_clk_cfg अणु
	u32 n;
	u32 m;
	u32 p;
	u32 q;
	bool swallow;
पूर्ण;

क्रमागत अणु
	CLOCK_CONFIG_16_2_M	= 1,
	CLOCK_CONFIG_16_368_M,
	CLOCK_CONFIG_16_8_M,
	CLOCK_CONFIG_19_2_M,
	CLOCK_CONFIG_26_M,
	CLOCK_CONFIG_32_736_M,
	CLOCK_CONFIG_33_6_M,
	CLOCK_CONFIG_38_468_M,
	CLOCK_CONFIG_52_M,

	NUM_CLOCK_CONFIGS,
पूर्ण;

#पूर्ण_अगर /* __WL18XX_PRIV_H__ */
