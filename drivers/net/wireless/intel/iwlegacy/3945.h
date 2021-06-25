<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/******************************************************************************
 *
 * Copyright(c) 2003 - 2011 Intel Corporation. All rights reserved.
 *
 * Contact Inक्रमmation:
 *  Intel Linux Wireless <ilw@linux.पूर्णांकel.com>
 * Intel Corporation, 5200 N.E. Elam Young Parkway, Hillsboro, OR 97124-6497
 *
 *****************************************************************************/

#अगर_अघोषित __il_3945_h__
#घोषणा __il_3945_h__

#समावेश <linux/pci.h>		/* क्रम काष्ठा pci_device_id */
#समावेश <linux/kernel.h>
#समावेश <net/ieee80211_radiotap.h>

/* Hardware specअगरic file defines the PCI IDs table क्रम that hardware module */
बाह्य स्थिर काष्ठा pci_device_id il3945_hw_card_ids[];

#समावेश "common.h"

बाह्य स्थिर काष्ठा il_ops il3945_ops;

/* Highest firmware API version supported */
#घोषणा IL3945_UCODE_API_MAX 2

/* Lowest firmware API version supported */
#घोषणा IL3945_UCODE_API_MIN 1

#घोषणा IL3945_FW_PRE	"iwlwifi-3945-"
#घोषणा _IL3945_MODULE_FIRMWARE(api) IL3945_FW_PRE #api ".ucode"
#घोषणा IL3945_MODULE_FIRMWARE(api) _IL3945_MODULE_FIRMWARE(api)

/* Default noise level to report when noise measurement is not available.
 *   This may be because we're:
 *   1)  Not associated (4965, no beacon stats being sent to driver)
 *   2)  Scanning (noise measurement करोes not apply to associated channel)
 *   3)  Receiving CCK (3945 delivers noise info only क्रम OFDM frames)
 * Use शेष noise value of -127 ... this is below the range of measurable
 *   Rx dBm क्रम either 3945 or 4965, so it can indicate "unmeasurable" to user.
 *   Also, -127 works better than 0 when averaging frames with/without
 *   noise info (e.g. averaging might be करोne in app); measured dBm values are
 *   always negative ... using a negative value as the शेष keeps all
 *   averages within an s8's (used in some apps) range of negative values. */
#घोषणा IL_NOISE_MEAS_NOT_AVAILABLE (-127)

/* Module parameters accessible from iwl-*.c */
बाह्य काष्ठा il_mod_params il3945_mod_params;

काष्ठा il3945_rate_scale_data अणु
	u64 data;
	s32 success_counter;
	s32 success_ratio;
	s32 counter;
	s32 average_tpt;
	अचिन्हित दीर्घ stamp;
पूर्ण;

काष्ठा il3945_rs_sta अणु
	spinlock_t lock;
	काष्ठा il_priv *il;
	s32 *expected_tpt;
	अचिन्हित दीर्घ last_partial_flush;
	अचिन्हित दीर्घ last_flush;
	u32 flush_समय;
	u32 last_tx_packets;
	u32 tx_packets;
	u8 tgg;
	u8 flush_pending;
	u8 start_rate;
	काष्ठा समयr_list rate_scale_flush;
	काष्ठा il3945_rate_scale_data win[RATE_COUNT_3945];

	/* used to be in sta_info */
	पूर्णांक last_txrate_idx;
पूर्ण;

/*
 * The common काष्ठा MUST be first because it is shared between
 * 3945 and 4965!
 */
काष्ठा il3945_sta_priv अणु
	काष्ठा il_station_priv_common common;
	काष्ठा il3945_rs_sta rs_sta;
पूर्ण;

क्रमागत il3945_antenna अणु
	IL_ANTENNA_DIVERSITY,
	IL_ANTENNA_MAIN,
	IL_ANTENNA_AUX
पूर्ण;

/*
 * RTS threshold here is total size [2347] minus 4 FCS bytes
 * Per spec:
 *   a value of 0 means RTS on all data/management packets
 *   a value > max MSDU size means no RTS
 * अन्यथा RTS क्रम data/management frames where MPDU is larger
 *   than RTS value.
 */
#घोषणा DEFAULT_RTS_THRESHOLD     2347U
#घोषणा MIN_RTS_THRESHOLD         0U
#घोषणा MAX_RTS_THRESHOLD         2347U
#घोषणा MAX_MSDU_SIZE		  2304U
#घोषणा MAX_MPDU_SIZE		  2346U
#घोषणा DEFAULT_BEACON_INTERVAL   100U
#घोषणा	DEFAULT_SHORT_RETRY_LIMIT 7U
#घोषणा	DEFAULT_LONG_RETRY_LIMIT  4U

#घोषणा IL_TX_FIFO_AC0	0
#घोषणा IL_TX_FIFO_AC1	1
#घोषणा IL_TX_FIFO_AC2	2
#घोषणा IL_TX_FIFO_AC3	3
#घोषणा IL_TX_FIFO_HCCA_1	5
#घोषणा IL_TX_FIFO_HCCA_2	6
#घोषणा IL_TX_FIFO_NONE	7

#घोषणा IEEE80211_DATA_LEN              2304
#घोषणा IEEE80211_4ADDR_LEN             30
#घोषणा IEEE80211_HLEN                  (IEEE80211_4ADDR_LEN)
#घोषणा IEEE80211_FRAME_LEN             (IEEE80211_DATA_LEN + IEEE80211_HLEN)

काष्ठा il3945_frame अणु
	जोड़ अणु
		काष्ठा ieee80211_hdr frame;
		काष्ठा il3945_tx_beacon_cmd beacon;
		u8 raw[IEEE80211_FRAME_LEN];
		u8 cmd[360];
	पूर्ण u;
	काष्ठा list_head list;
पूर्ण;

#घोषणा SUP_RATE_11A_MAX_NUM_CHANNELS  8
#घोषणा SUP_RATE_11B_MAX_NUM_CHANNELS  4
#घोषणा SUP_RATE_11G_MAX_NUM_CHANNELS  12

#घोषणा IL_SUPPORTED_RATES_IE_LEN         8

#घोषणा SCAN_INTERVAL 100

#घोषणा MAX_TID_COUNT        9

#घोषणा IL_INVALID_RATE     0xFF
#घोषणा IL_INVALID_VALUE    -1

#घोषणा STA_PS_STATUS_WAKE             0
#घोषणा STA_PS_STATUS_SLEEP            1

काष्ठा il3945_ibss_seq अणु
	u8 mac[ETH_ALEN];
	u16 seq_num;
	u16 frag_num;
	अचिन्हित दीर्घ packet_समय;
	काष्ठा list_head list;
पूर्ण;

#घोषणा IL_RX_HDR(x) ((काष्ठा il3945_rx_frame_hdr *)(\
		       x->u.rx_frame.stats.payload + \
		       x->u.rx_frame.stats.phy_count))
#घोषणा IL_RX_END(x) ((काष्ठा il3945_rx_frame_end *)(\
		       IL_RX_HDR(x)->payload + \
		       le16_to_cpu(IL_RX_HDR(x)->len)))
#घोषणा IL_RX_STATS(x) (&x->u.rx_frame.stats)
#घोषणा IL_RX_DATA(x) (IL_RX_HDR(x)->payload)

/******************************************************************************
 *
 * Functions implemented in iwl3945-base.c which are क्रमward declared here
 * क्रम use by iwl-*.c
 *
 *****************************************************************************/
पूर्णांक il3945_calc_db_from_ratio(पूर्णांक sig_ratio);
व्योम il3945_rx_replenish(व्योम *data);
व्योम il3945_rx_queue_reset(काष्ठा il_priv *il, काष्ठा il_rx_queue *rxq);
अचिन्हित पूर्णांक il3945_fill_beacon_frame(काष्ठा il_priv *il,
				      काष्ठा ieee80211_hdr *hdr, पूर्णांक left);
पूर्णांक il3945_dump_nic_event_log(काष्ठा il_priv *il, bool full_log, अक्षर **buf,
			      bool display);
व्योम il3945_dump_nic_error_log(काष्ठा il_priv *il);

/******************************************************************************
 *
 * Functions implemented in iwl-[34]*.c which are क्रमward declared here
 * क्रम use by iwl3945-base.c
 *
 * NOTE:  The implementation of these functions are hardware specअगरic
 * which is why they are in the hardware specअगरic files (vs. iwl-base.c)
 *
 * Naming convention --
 * il3945_         <-- Its part of iwlwअगरi (should be changed to il3945_)
 * il3945_hw_      <-- Hardware specअगरic (implemented in iwl-XXXX.c by all HW)
 * iwlXXXX_     <-- Hardware specअगरic (implemented in iwl-XXXX.c क्रम XXXX)
 * il3945_bg_      <-- Called from work queue context
 * il3945_mac_     <-- mac80211 callback
 *
 ****************************************************************************/
व्योम il3945_hw_handler_setup(काष्ठा il_priv *il);
व्योम il3945_hw_setup_deferred_work(काष्ठा il_priv *il);
व्योम il3945_hw_cancel_deferred_work(काष्ठा il_priv *il);
पूर्णांक il3945_hw_rxq_stop(काष्ठा il_priv *il);
पूर्णांक il3945_hw_set_hw_params(काष्ठा il_priv *il);
पूर्णांक il3945_hw_nic_init(काष्ठा il_priv *il);
पूर्णांक il3945_hw_nic_stop_master(काष्ठा il_priv *il);
व्योम il3945_hw_txq_ctx_मुक्त(काष्ठा il_priv *il);
व्योम il3945_hw_txq_ctx_stop(काष्ठा il_priv *il);
पूर्णांक il3945_hw_nic_reset(काष्ठा il_priv *il);
पूर्णांक il3945_hw_txq_attach_buf_to_tfd(काष्ठा il_priv *il, काष्ठा il_tx_queue *txq,
				    dma_addr_t addr, u16 len, u8 reset, u8 pad);
व्योम il3945_hw_txq_मुक्त_tfd(काष्ठा il_priv *il, काष्ठा il_tx_queue *txq);
पूर्णांक il3945_hw_get_temperature(काष्ठा il_priv *il);
पूर्णांक il3945_hw_tx_queue_init(काष्ठा il_priv *il, काष्ठा il_tx_queue *txq);
अचिन्हित पूर्णांक il3945_hw_get_beacon_cmd(काष्ठा il_priv *il,
				      काष्ठा il3945_frame *frame, u8 rate);
व्योम il3945_hw_build_tx_cmd_rate(काष्ठा il_priv *il, काष्ठा il_device_cmd *cmd,
				 काष्ठा ieee80211_tx_info *info,
				 काष्ठा ieee80211_hdr *hdr, पूर्णांक sta_id);
पूर्णांक il3945_hw_reg_send_txघातer(काष्ठा il_priv *il);
पूर्णांक il3945_hw_reg_set_txघातer(काष्ठा il_priv *il, s8 घातer);
व्योम il3945_hdl_stats(काष्ठा il_priv *il, काष्ठा il_rx_buf *rxb);
व्योम il3945_hdl_c_stats(काष्ठा il_priv *il, काष्ठा il_rx_buf *rxb);
व्योम il3945_disable_events(काष्ठा il_priv *il);
पूर्णांक il4965_get_temperature(स्थिर काष्ठा il_priv *il);
व्योम il3945_post_associate(काष्ठा il_priv *il);
व्योम il3945_config_ap(काष्ठा il_priv *il);

पूर्णांक il3945_commit_rxon(काष्ठा il_priv *il);

/**
 * il3945_hw_find_station - Find station id क्रम a given BSSID
 * @bssid: MAC address of station ID to find
 *
 * NOTE:  This should not be hardware specअगरic but the code has
 * not yet been merged पूर्णांकo a single common layer क्रम managing the
 * station tables.
 */
u8 il3945_hw_find_station(काष्ठा il_priv *il, स्थिर u8 *bssid);

__le32 il3945_get_antenna_flags(स्थिर काष्ठा il_priv *il);
पूर्णांक il3945_init_hw_rate_table(काष्ठा il_priv *il);
व्योम il3945_reg_txघातer_periodic(काष्ठा il_priv *il);
पूर्णांक il3945_txघातer_set_from_eeprom(काष्ठा il_priv *il);

पूर्णांक il3945_rs_next_rate(काष्ठा il_priv *il, पूर्णांक rate);

/* scanning */
पूर्णांक il3945_request_scan(काष्ठा il_priv *il, काष्ठा ieee80211_vअगर *vअगर);
व्योम il3945_post_scan(काष्ठा il_priv *il);

/* rates */
बाह्य स्थिर काष्ठा il3945_rate_info il3945_rates[RATE_COUNT_3945];

/* RSSI to dBm */
#घोषणा IL39_RSSI_OFFSET	95

/*
 * EEPROM related स्थिरants, क्रमागतs, and काष्ठाures.
 */
#घोषणा EEPROM_SKU_CAP_OP_MODE_MRC                      (1 << 7)

/*
 * Mapping of a Tx घातer level, at factory calibration temperature,
 *   to a radio/DSP gain table idx.
 * One क्रम each of 5 "sample" घातer levels in each band.
 * v_det is measured at the factory, using the 3945's built-in घातer amplअगरier
 *   (PA) output voltage detector.  This same detector is used during Tx of
 *   दीर्घ packets in normal operation to provide feedback as to proper output
 *   level.
 * Data copied from EEPROM.
 * DO NOT ALTER THIS STRUCTURE!!!
 */
काष्ठा il3945_eeprom_txघातer_sample अणु
	u8 gain_idx;		/* idx पूर्णांकo घातer (gain) setup table ... */
	s8 घातer;		/* ... क्रम this pwr level क्रम this chnl group */
	u16 v_det;		/* PA output voltage */
पूर्ण __packed;

/*
 * Mappings of Tx घातer levels -> nominal radio/DSP gain table idxes.
 * One क्रम each channel group (a.k.a. "band") (1 क्रम BG, 4 क्रम A).
 * Tx घातer setup code पूर्णांकerpolates between the 5 "sample" घातer levels
 *    to determine the nominal setup क्रम a requested घातer level.
 * Data copied from EEPROM.
 * DO NOT ALTER THIS STRUCTURE!!!
 */
काष्ठा il3945_eeprom_txघातer_group अणु
	काष्ठा il3945_eeprom_txघातer_sample samples[5];	/* 5 घातer levels */
	s32 a, b, c, d, e;	/* coefficients क्रम voltage->घातer
				 * क्रमmula (चिन्हित) */
	s32 Fa, Fb, Fc, Fd, Fe;	/* these modअगरy coeffs based on
				 * frequency (चिन्हित) */
	s8 saturation_घातer;	/* highest घातer possible by h/w in this
				 * band */
	u8 group_channel;	/* "representative" channel # in this band */
	s16 temperature;	/* h/w temperature at factory calib this band
				 * (चिन्हित) */
पूर्ण __packed;

/*
 * Temperature-based Tx-घातer compensation data, not band-specअगरic.
 * These coefficients are use to modअगरy a/b/c/d/e coeffs based on
 *   dअगरference between current temperature and factory calib temperature.
 * Data copied from EEPROM.
 */
काष्ठा il3945_eeprom_temperature_corr अणु
	u32 Ta;
	u32 Tb;
	u32 Tc;
	u32 Td;
	u32 Te;
पूर्ण __packed;

/*
 * EEPROM map
 */
काष्ठा il3945_eeprom अणु
	u8 reserved0[16];
	u16 device_id;		/* असल.ofs: 16 */
	u8 reserved1[2];
	u16 pmc;		/* असल.ofs: 20 */
	u8 reserved2[20];
	u8 mac_address[6];	/* असल.ofs: 42 */
	u8 reserved3[58];
	u16 board_revision;	/* असल.ofs: 106 */
	u8 reserved4[11];
	u8 board_pba_number[9];	/* असल.ofs: 119 */
	u8 reserved5[8];
	u16 version;		/* असल.ofs: 136 */
	u8 sku_cap;		/* असल.ofs: 138 */
	u8 leds_mode;		/* असल.ofs: 139 */
	u16 oem_mode;
	u16 wowlan_mode;	/* असल.ofs: 142 */
	u16 leds_समय_पूर्णांकerval;	/* असल.ofs: 144 */
	u8 leds_off_समय;	/* असल.ofs: 146 */
	u8 leds_on_समय;	/* असल.ofs: 147 */
	u8 almgor_m_version;	/* असल.ofs: 148 */
	u8 antenna_चयन_type;	/* असल.ofs: 149 */
	u8 reserved6[42];
	u8 sku_id[4];		/* असल.ofs: 192 */

/*
 * Per-channel regulatory data.
 *
 * Each channel that *might* be supported by 3945 has a fixed location
 * in EEPROM containing EEPROM_CHANNEL_* usage flags (LSB) and max regulatory
 * txघातer (MSB).
 *
 * Entries immediately below are क्रम 20 MHz channel width.
 *
 * 2.4 GHz channels 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14
 */
	u16 band_1_count;	/* असल.ofs: 196 */
	काष्ठा il_eeprom_channel band_1_channels[14];	/* असल.ofs: 198 */

/*
 * 4.9 GHz channels 183, 184, 185, 187, 188, 189, 192, 196,
 * 5.0 GHz channels 7, 8, 11, 12, 16
 * (4915-5080MHz) (none of these is ever supported)
 */
	u16 band_2_count;	/* असल.ofs: 226 */
	काष्ठा il_eeprom_channel band_2_channels[13];	/* असल.ofs: 228 */

/*
 * 5.2 GHz channels 34, 36, 38, 40, 42, 44, 46, 48, 52, 56, 60, 64
 * (5170-5320MHz)
 */
	u16 band_3_count;	/* असल.ofs: 254 */
	काष्ठा il_eeprom_channel band_3_channels[12];	/* असल.ofs: 256 */

/*
 * 5.5 GHz channels 100, 104, 108, 112, 116, 120, 124, 128, 132, 136, 140
 * (5500-5700MHz)
 */
	u16 band_4_count;	/* असल.ofs: 280 */
	काष्ठा il_eeprom_channel band_4_channels[11];	/* असल.ofs: 282 */

/*
 * 5.7 GHz channels 145, 149, 153, 157, 161, 165
 * (5725-5825MHz)
 */
	u16 band_5_count;	/* असल.ofs: 304 */
	काष्ठा il_eeprom_channel band_5_channels[6];	/* असल.ofs: 306 */

	u8 reserved9[194];

/*
 * 3945 Txघातer calibration data.
 */
#घोषणा IL_NUM_TX_CALIB_GROUPS 5
	काष्ठा il3945_eeprom_txघातer_group groups[IL_NUM_TX_CALIB_GROUPS];
/* असल.ofs: 512 */
	काष्ठा il3945_eeprom_temperature_corr corrections;	/* असल.ofs: 832 */
	u8 reserved16[172];	/* fill out to full 1024 byte block */
पूर्ण __packed;

#घोषणा IL3945_EEPROM_IMG_SIZE 1024

/* End of EEPROM */

#घोषणा PCI_CFG_REV_ID_BIT_BASIC_SKU                (0x40)	/* bit 6    */
#घोषणा PCI_CFG_REV_ID_BIT_RTP                      (0x80)	/* bit 7    */

/* 4 DATA + 1 CMD. There are 2 HCCA queues that are not used. */
#घोषणा IL39_NUM_QUEUES        5
#घोषणा IL39_CMD_QUEUE_NUM	4

#घोषणा IL_DEFAULT_TX_RETRY  15

/*********************************************/

#घोषणा RFD_SIZE                              4
#घोषणा NUM_TFD_CHUNKS                        4

#घोषणा TFD_CTL_COUNT_SET(n)       (n << 24)
#घोषणा TFD_CTL_COUNT_GET(ctl)     ((ctl >> 24) & 7)
#घोषणा TFD_CTL_PAD_SET(n)         (n << 28)
#घोषणा TFD_CTL_PAD_GET(ctl)       (ctl >> 28)

/* Sizes and addresses क्रम inकाष्ठाion and data memory (SRAM) in
 * 3945's embedded processor.  Driver access is via HBUS_TARG_MEM_* regs. */
#घोषणा IL39_RTC_INST_LOWER_BOUND		(0x000000)
#घोषणा IL39_RTC_INST_UPPER_BOUND		(0x014000)

#घोषणा IL39_RTC_DATA_LOWER_BOUND		(0x800000)
#घोषणा IL39_RTC_DATA_UPPER_BOUND		(0x808000)

#घोषणा IL39_RTC_INST_SIZE (IL39_RTC_INST_UPPER_BOUND - \
				IL39_RTC_INST_LOWER_BOUND)
#घोषणा IL39_RTC_DATA_SIZE (IL39_RTC_DATA_UPPER_BOUND - \
				IL39_RTC_DATA_LOWER_BOUND)

#घोषणा IL39_MAX_INST_SIZE IL39_RTC_INST_SIZE
#घोषणा IL39_MAX_DATA_SIZE IL39_RTC_DATA_SIZE

/* Size of uCode inकाष्ठाion memory in bootstrap state machine */
#घोषणा IL39_MAX_BSM_SIZE IL39_RTC_INST_SIZE

अटल अंतरभूत पूर्णांक
il3945_hw_valid_rtc_data_addr(u32 addr)
अणु
	वापस (addr >= IL39_RTC_DATA_LOWER_BOUND &&
		addr < IL39_RTC_DATA_UPPER_BOUND);
पूर्ण

/* Base physical address of il3945_shared is provided to FH39_TSSR_CBB_BASE
 * and &il3945_shared.rx_पढ़ो_ptr[0] is provided to FH39_RCSR_RPTR_ADDR(0) */
काष्ठा il3945_shared अणु
	__le32 tx_base_ptr[8];
पूर्ण __packed;

/************************************/
/* iwl3945 Flow Handler Definitions */
/************************************/

/**
 * This I/O area is directly पढ़ो/writable by driver (e.g. Linux uses ग_लिखोl())
 * Addresses are offsets from device's PCI hardware base address.
 */
#घोषणा FH39_MEM_LOWER_BOUND                   (0x0800)
#घोषणा FH39_MEM_UPPER_BOUND                   (0x1000)

#घोषणा FH39_CBCC_TBL		(FH39_MEM_LOWER_BOUND + 0x140)
#घोषणा FH39_TFDB_TBL		(FH39_MEM_LOWER_BOUND + 0x180)
#घोषणा FH39_RCSR_TBL		(FH39_MEM_LOWER_BOUND + 0x400)
#घोषणा FH39_RSSR_TBL		(FH39_MEM_LOWER_BOUND + 0x4c0)
#घोषणा FH39_TCSR_TBL		(FH39_MEM_LOWER_BOUND + 0x500)
#घोषणा FH39_TSSR_TBL		(FH39_MEM_LOWER_BOUND + 0x680)

/* TFDB (Transmit Frame Buffer Descriptor) */
#घोषणा FH39_TFDB(_ch, buf)			(FH39_TFDB_TBL + \
						 ((_ch) * 2 + (buf)) * 0x28)
#घोषणा FH39_TFDB_CHNL_BUF_CTRL_REG(_ch)	(FH39_TFDB_TBL + 0x50 * (_ch))

/* CBCC channel is [0,2] */
#घोषणा FH39_CBCC(_ch)		(FH39_CBCC_TBL + (_ch) * 0x8)
#घोषणा FH39_CBCC_CTRL(_ch)	(FH39_CBCC(_ch) + 0x00)
#घोषणा FH39_CBCC_BASE(_ch)	(FH39_CBCC(_ch) + 0x04)

/* RCSR channel is [0,2] */
#घोषणा FH39_RCSR(_ch)			(FH39_RCSR_TBL + (_ch) * 0x40)
#घोषणा FH39_RCSR_CONFIG(_ch)		(FH39_RCSR(_ch) + 0x00)
#घोषणा FH39_RCSR_RBD_BASE(_ch)		(FH39_RCSR(_ch) + 0x04)
#घोषणा FH39_RCSR_WPTR(_ch)		(FH39_RCSR(_ch) + 0x20)
#घोषणा FH39_RCSR_RPTR_ADDR(_ch)	(FH39_RCSR(_ch) + 0x24)

#घोषणा FH39_RSCSR_CHNL0_WPTR		(FH39_RCSR_WPTR(0))

/* RSSR */
#घोषणा FH39_RSSR_CTRL			(FH39_RSSR_TBL + 0x000)
#घोषणा FH39_RSSR_STATUS		(FH39_RSSR_TBL + 0x004)

/* TCSR */
#घोषणा FH39_TCSR(_ch)			(FH39_TCSR_TBL + (_ch) * 0x20)
#घोषणा FH39_TCSR_CONFIG(_ch)		(FH39_TCSR(_ch) + 0x00)
#घोषणा FH39_TCSR_CREDIT(_ch)		(FH39_TCSR(_ch) + 0x04)
#घोषणा FH39_TCSR_BUFF_STTS(_ch)	(FH39_TCSR(_ch) + 0x08)

/* TSSR */
#घोषणा FH39_TSSR_CBB_BASE        (FH39_TSSR_TBL + 0x000)
#घोषणा FH39_TSSR_MSG_CONFIG      (FH39_TSSR_TBL + 0x008)
#घोषणा FH39_TSSR_TX_STATUS       (FH39_TSSR_TBL + 0x010)

/* DBM */

#घोषणा FH39_SRVC_CHNL                            (6)

#घोषणा FH39_RCSR_RX_CONFIG_REG_POS_RBDC_SIZE     (20)
#घोषणा FH39_RCSR_RX_CONFIG_REG_POS_IRQ_RBTH      (4)

#घोषणा FH39_RCSR_RX_CONFIG_REG_BIT_WR_STTS_EN    (0x08000000)

#घोषणा FH39_RCSR_RX_CONFIG_REG_VAL_DMA_CHNL_EN_ENABLE        (0x80000000)

#घोषणा FH39_RCSR_RX_CONFIG_REG_VAL_RDRBD_EN_ENABLE           (0x20000000)

#घोषणा FH39_RCSR_RX_CONFIG_REG_VAL_MAX_FRAG_SIZE_128		(0x01000000)

#घोषणा FH39_RCSR_RX_CONFIG_REG_VAL_IRQ_DEST_INT_HOST		(0x00001000)

#घोषणा FH39_RCSR_RX_CONFIG_REG_VAL_MSG_MODE_FH			(0x00000000)

#घोषणा FH39_TCSR_TX_CONFIG_REG_VAL_MSG_MODE_TXF		(0x00000000)
#घोषणा FH39_TCSR_TX_CONFIG_REG_VAL_MSG_MODE_DRIVER		(0x00000001)

#घोषणा FH39_TCSR_TX_CONFIG_REG_VAL_DMA_CREDIT_DISABLE_VAL	(0x00000000)
#घोषणा FH39_TCSR_TX_CONFIG_REG_VAL_DMA_CREDIT_ENABLE_VAL	(0x00000008)

#घोषणा FH39_TCSR_TX_CONFIG_REG_VAL_CIRQ_HOST_IFTFD		(0x00200000)

#घोषणा FH39_TCSR_TX_CONFIG_REG_VAL_CIRQ_RTC_NOINT		(0x00000000)

#घोषणा FH39_TCSR_TX_CONFIG_REG_VAL_DMA_CHNL_PAUSE		(0x00000000)
#घोषणा FH39_TCSR_TX_CONFIG_REG_VAL_DMA_CHNL_ENABLE		(0x80000000)

#घोषणा FH39_TCSR_CHNL_TX_BUF_STS_REG_VAL_TFDB_VALID		(0x00004000)

#घोषणा FH39_TCSR_CHNL_TX_BUF_STS_REG_BIT_TFDB_WPTR		(0x00000001)

#घोषणा FH39_TSSR_TX_MSG_CONFIG_REG_VAL_SNOOP_RD_TXPD_ON	(0xFF000000)
#घोषणा FH39_TSSR_TX_MSG_CONFIG_REG_VAL_ORDER_RD_TXPD_ON	(0x00FF0000)

#घोषणा FH39_TSSR_TX_MSG_CONFIG_REG_VAL_MAX_FRAG_SIZE_128B	(0x00000400)

#घोषणा FH39_TSSR_TX_MSG_CONFIG_REG_VAL_SNOOP_RD_TFD_ON		(0x00000100)
#घोषणा FH39_TSSR_TX_MSG_CONFIG_REG_VAL_ORDER_RD_CBB_ON		(0x00000080)

#घोषणा FH39_TSSR_TX_MSG_CONFIG_REG_VAL_ORDER_RSP_WAIT_TH	(0x00000020)
#घोषणा FH39_TSSR_TX_MSG_CONFIG_REG_VAL_RSP_WAIT_TH		(0x00000005)

#घोषणा FH39_TSSR_TX_STATUS_REG_BIT_BUFS_EMPTY(_ch)	(BIT(_ch) << 24)
#घोषणा FH39_TSSR_TX_STATUS_REG_BIT_NO_PEND_REQ(_ch)	(BIT(_ch) << 16)

#घोषणा FH39_TSSR_TX_STATUS_REG_MSK_CHNL_IDLE(_ch) \
	(FH39_TSSR_TX_STATUS_REG_BIT_BUFS_EMPTY(_ch) | \
	 FH39_TSSR_TX_STATUS_REG_BIT_NO_PEND_REQ(_ch))

#घोषणा FH39_RSSR_CHNL0_RX_STATUS_CHNL_IDLE			(0x01000000)

काष्ठा il3945_tfd_tb अणु
	__le32 addr;
	__le32 len;
पूर्ण __packed;

काष्ठा il3945_tfd अणु
	__le32 control_flags;
	काष्ठा il3945_tfd_tb tbs[4];
	u8 __pad[28];
पूर्ण __packed;

#अगर_घोषित CONFIG_IWLEGACY_DEBUGFS
बाह्य स्थिर काष्ठा il_debugfs_ops il3945_debugfs_ops;
#पूर्ण_अगर

#पूर्ण_अगर
