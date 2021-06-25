<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * This file is part of wl12xx
 *
 * Copyright (C) 2011 Texas Instruments Inc.
 */

#अगर_अघोषित __WL12XX_PRIV_H__
#घोषणा __WL12XX_PRIV_H__

#समावेश "conf.h"

/* WiLink 6/7 chip IDs */
#घोषणा CHIP_ID_127X_PG10              (0x04030101)
#घोषणा CHIP_ID_127X_PG20              (0x04030111)
#घोषणा CHIP_ID_128X_PG10              (0x05030101)
#घोषणा CHIP_ID_128X_PG20              (0x05030111)

/* FW chip version क्रम wl127x */
#घोषणा WL127X_CHIP_VER		6
/* minimum single-role FW version क्रम wl127x */
#घोषणा WL127X_IFTYPE_SR_VER	3
#घोषणा WL127X_MAJOR_SR_VER	10
#घोषणा WL127X_SUBTYPE_SR_VER	WLCORE_FW_VER_IGNORE
#घोषणा WL127X_MINOR_SR_VER	133
/* minimum multi-role FW version क्रम wl127x */
#घोषणा WL127X_IFTYPE_MR_VER	5
#घोषणा WL127X_MAJOR_MR_VER	7
#घोषणा WL127X_SUBTYPE_MR_VER	WLCORE_FW_VER_IGNORE
#घोषणा WL127X_MINOR_MR_VER	42

/* FW chip version क्रम wl128x */
#घोषणा WL128X_CHIP_VER		7
/* minimum single-role FW version क्रम wl128x */
#घोषणा WL128X_IFTYPE_SR_VER	3
#घोषणा WL128X_MAJOR_SR_VER	10
#घोषणा WL128X_SUBTYPE_SR_VER	WLCORE_FW_VER_IGNORE
#घोषणा WL128X_MINOR_SR_VER	133
/* minimum multi-role FW version क्रम wl128x */
#घोषणा WL128X_IFTYPE_MR_VER	5
#घोषणा WL128X_MAJOR_MR_VER	7
#घोषणा WL128X_SUBTYPE_MR_VER	WLCORE_FW_VER_IGNORE
#घोषणा WL128X_MINOR_MR_VER	42

#घोषणा WL12XX_AGGR_BUFFER_SIZE	(4 * PAGE_SIZE)

#घोषणा WL12XX_NUM_TX_DESCRIPTORS 16
#घोषणा WL12XX_NUM_RX_DESCRIPTORS 8

#घोषणा WL12XX_NUM_MAC_ADDRESSES 2

#घोषणा WL12XX_RX_BA_MAX_SESSIONS 3

#घोषणा WL12XX_MAX_AP_STATIONS 8
#घोषणा WL12XX_MAX_LINKS 12

काष्ठा wl127x_rx_mem_pool_addr अणु
	u32 addr;
	u32 addr_extra;
पूर्ण;

काष्ठा wl12xx_priv अणु
	काष्ठा wl12xx_priv_conf conf;

	पूर्णांक ref_घड़ी;
	पूर्णांक tcxo_घड़ी;

	काष्ठा wl127x_rx_mem_pool_addr *rx_mem_addr;
पूर्ण;

/* Reference घड़ी values */
क्रमागत अणु
	WL12XX_REFCLOCK_19	= 0, /* 19.2 MHz */
	WL12XX_REFCLOCK_26	= 1, /* 26 MHz */
	WL12XX_REFCLOCK_38	= 2, /* 38.4 MHz */
	WL12XX_REFCLOCK_52	= 3, /* 52 MHz */
	WL12XX_REFCLOCK_38_XTAL = 4, /* 38.4 MHz, XTAL */
	WL12XX_REFCLOCK_26_XTAL = 5, /* 26 MHz, XTAL */
पूर्ण;

/* TCXO घड़ी values */
क्रमागत अणु
	WL12XX_TCXOCLOCK_19_2	= 0, /* 19.2MHz */
	WL12XX_TCXOCLOCK_26	= 1, /* 26 MHz */
	WL12XX_TCXOCLOCK_38_4	= 2, /* 38.4MHz */
	WL12XX_TCXOCLOCK_52	= 3, /* 52 MHz */
	WL12XX_TCXOCLOCK_16_368	= 4, /* 16.368 MHz */
	WL12XX_TCXOCLOCK_32_736	= 5, /* 32.736 MHz */
	WL12XX_TCXOCLOCK_16_8	= 6, /* 16.8 MHz */
	WL12XX_TCXOCLOCK_33_6	= 7, /* 33.6 MHz */
पूर्ण;

काष्ठा wl12xx_घड़ी अणु
	u32	freq;
	bool	xtal;
	u8	hw_idx;
पूर्ण;

काष्ठा wl12xx_fw_packet_counters अणु
	/* Cumulative counter of released packets per AC */
	u8 tx_released_pkts[NUM_TX_QUEUES];

	/* Cumulative counter of मुक्तd packets per HLID */
	u8 tx_lnk_मुक्त_pkts[WL12XX_MAX_LINKS];

	/* Cumulative counter of released Voice memory blocks */
	u8 tx_voice_released_blks;

	/* Tx rate of the last transmitted packet */
	u8 tx_last_rate;

	u8 padding[2];
पूर्ण __packed;

/* FW status रेजिस्टरs */
काष्ठा wl12xx_fw_status अणु
	__le32 पूर्णांकr;
	u8  fw_rx_counter;
	u8  drv_rx_counter;
	u8  reserved;
	u8  tx_results_counter;
	__le32 rx_pkt_descs[WL12XX_NUM_RX_DESCRIPTORS];

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

	काष्ठा wl12xx_fw_packet_counters counters;

	__le32 log_start_addr;
पूर्ण __packed;

#पूर्ण_अगर /* __WL12XX_PRIV_H__ */
