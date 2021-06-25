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
#अगर_अघोषित __il_core_h__
#घोषणा __il_core_h__

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>		/* क्रम काष्ठा pci_device_id */
#समावेश <linux/kernel.h>
#समावेश <linux/leds.h>
#समावेश <linux/रुको.h>
#समावेश <linux/पन.स>
#समावेश <net/mac80211.h>
#समावेश <net/ieee80211_radiotap.h>

#समावेश "commands.h"
#समावेश "csr.h"
#समावेश "prph.h"

काष्ठा il_host_cmd;
काष्ठा il_cmd;
काष्ठा il_tx_queue;

#घोषणा IL_ERR(f, a...) dev_err(&il->pci_dev->dev, f, ## a)
#घोषणा IL_WARN(f, a...) dev_warn(&il->pci_dev->dev, f, ## a)
#घोषणा IL_WARN_ONCE(f, a...) dev_warn_once(&il->pci_dev->dev, f, ## a)
#घोषणा IL_INFO(f, a...) dev_info(&il->pci_dev->dev, f, ## a)

#घोषणा RX_QUEUE_SIZE                         256
#घोषणा RX_QUEUE_MASK                         255
#घोषणा RX_QUEUE_SIZE_LOG                     8

/*
 * RX related काष्ठाures and functions
 */
#घोषणा RX_FREE_BUFFERS 64
#घोषणा RX_LOW_WATERMARK 8

#घोषणा U32_PAD(n)		((4-(n))&0x3)

/* CT-KILL स्थिरants */
#घोषणा CT_KILL_THRESHOLD_LEGACY   110	/* in Celsius */

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

काष्ठा il_rx_buf अणु
	dma_addr_t page_dma;
	काष्ठा page *page;
	काष्ठा list_head list;
पूर्ण;

#घोषणा rxb_addr(r) page_address(r->page)

/* defined below */
काष्ठा il_device_cmd;

काष्ठा il_cmd_meta अणु
	/* only क्रम SYNC commands, अगरf the reply skb is wanted */
	काष्ठा il_host_cmd *source;
	/*
	 * only क्रम ASYNC commands
	 * (which is somewhat stupid -- look at common.c क्रम instance
	 * which duplicates a bunch of code because the callback isn't
	 * invoked क्रम SYNC commands, अगर it were and its result passed
	 * through it would be simpler...)
	 */
	व्योम (*callback) (काष्ठा il_priv *il, काष्ठा il_device_cmd *cmd,
			  काष्ठा il_rx_pkt *pkt);

	/* The CMD_SIZE_HUGE flag bit indicates that the command
	 * काष्ठाure is stored at the end of the shared queue memory. */
	u32 flags;

	 DEFINE_DMA_UNMAP_ADDR(mapping);
	 DEFINE_DMA_UNMAP_LEN(len);
पूर्ण;

/*
 * Generic queue काष्ठाure
 *
 * Contains common data क्रम Rx and Tx queues
 */
काष्ठा il_queue अणु
	पूर्णांक n_bd;		/* number of BDs in this queue */
	पूर्णांक ग_लिखो_ptr;		/* 1-st empty entry (idx) host_w */
	पूर्णांक पढ़ो_ptr;		/* last used entry (idx) host_r */
	/* use क्रम monitoring and recovering the stuck queue */
	dma_addr_t dma_addr;	/* physical addr क्रम BD's */
	पूर्णांक n_win;		/* safe queue win */
	u32 id;
	पूर्णांक low_mark;		/* low watermark, resume queue अगर मुक्त
				 * space more than this */
	पूर्णांक high_mark;		/* high watermark, stop queue अगर मुक्त
				 * space less than this */
पूर्ण;

/**
 * काष्ठा il_tx_queue - Tx Queue क्रम DMA
 * @q: generic Rx/Tx queue descriptor
 * @bd: base of circular buffer of TFDs
 * @cmd: array of command/TX buffer poपूर्णांकers
 * @meta: array of meta data क्रम each command/tx buffer
 * @dma_addr_cmd: physical address of cmd/tx buffer array
 * @skbs: array of per-TFD socket buffer poपूर्णांकers
 * @समय_stamp: समय (in jअगरfies) of last पढ़ो_ptr change
 * @need_update: indicates need to update पढ़ो/ग_लिखो idx
 * @sched_retry: indicates queue is high-throughput aggregation (HT AGG) enabled
 *
 * A Tx queue consists of circular buffer of BDs (a.k.a. TFDs, transmit frame
 * descriptors) and required locking काष्ठाures.
 */
#घोषणा TFD_TX_CMD_SLOTS 256
#घोषणा TFD_CMD_SLOTS 32

काष्ठा il_tx_queue अणु
	काष्ठा il_queue q;
	व्योम *tfds;
	काष्ठा il_device_cmd **cmd;
	काष्ठा il_cmd_meta *meta;
	काष्ठा sk_buff **skbs;
	अचिन्हित दीर्घ समय_stamp;
	u8 need_update;
	u8 sched_retry;
	u8 active;
	u8 swq_id;
पूर्ण;

/*
 * EEPROM access समय values:
 *
 * Driver initiates EEPROM पढ़ो by writing byte address << 1 to CSR_EEPROM_REG.
 * Driver then polls CSR_EEPROM_REG क्रम CSR_EEPROM_REG_READ_VALID_MSK (0x1).
 * When polling, रुको 10 uSec between polling loops, up to a maximum 5000 uSec.
 * Driver पढ़ोs 16-bit value from bits 31-16 of CSR_EEPROM_REG.
 */
#घोषणा IL_EEPROM_ACCESS_TIMEOUT	5000	/* uSec */

#घोषणा IL_EEPROM_SEM_TIMEOUT		10	/* microseconds */
#घोषणा IL_EEPROM_SEM_RETRY_LIMIT	1000	/* number of attempts (not समय) */

/*
 * Regulatory channel usage flags in EEPROM काष्ठा il4965_eeprom_channel.flags.
 *
 * IBSS and/or AP operation is allowed *only* on those channels with
 * (VALID && IBSS && ACTIVE && !RADAR).  This restriction is in place because
 * RADAR detection is not supported by the 4965 driver, but is a
 * requirement क्रम establishing a new network क्रम legal operation on channels
 * requiring RADAR detection or restricting ACTIVE scanning.
 *
 * NOTE:  "WIDE" flag करोes not indicate anything about "HT40" 40 MHz channels.
 *        It only indicates that 20 MHz channel use is supported; HT40 channel
 *        usage is indicated by a separate set of regulatory flags क्रम each
 *        HT40 channel pair.
 *
 * NOTE:  Using a channel inappropriately will result in a uCode error!
 */
#घोषणा IL_NUM_TX_CALIB_GROUPS 5
क्रमागत अणु
	EEPROM_CHANNEL_VALID = (1 << 0),	/* usable क्रम this SKU/geo */
	EEPROM_CHANNEL_IBSS = (1 << 1),	/* usable as an IBSS channel */
	/* Bit 2 Reserved */
	EEPROM_CHANNEL_ACTIVE = (1 << 3),	/* active scanning allowed */
	EEPROM_CHANNEL_RADAR = (1 << 4),	/* radar detection required */
	EEPROM_CHANNEL_WIDE = (1 << 5),	/* 20 MHz channel okay */
	/* Bit 6 Reserved (was Narrow Channel) */
	EEPROM_CHANNEL_DFS = (1 << 7),	/* dynamic freq selection candidate */
पूर्ण;

/* SKU Capabilities */
/* 3945 only */
#घोषणा EEPROM_SKU_CAP_SW_RF_KILL_ENABLE                (1 << 0)
#घोषणा EEPROM_SKU_CAP_HW_RF_KILL_ENABLE                (1 << 1)

/* *regulatory* channel data क्रमmat in eeprom, one क्रम each channel.
 * There are separate entries क्रम HT40 (40 MHz) vs. normal (20 MHz) channels. */
काष्ठा il_eeprom_channel अणु
	u8 flags;		/* EEPROM_CHANNEL_* flags copied from EEPROM */
	s8 max_घातer_avg;	/* max घातer (dBm) on this chnl, limit 31 */
पूर्ण __packed;

/* 3945 Specअगरic */
#घोषणा EEPROM_3945_EEPROM_VERSION	(0x2f)

/* 4965 has two radio transmitters (and 3 radio receivers) */
#घोषणा EEPROM_TX_POWER_TX_CHAINS      (2)

/* 4965 has room क्रम up to 8 sets of txघातer calibration data */
#घोषणा EEPROM_TX_POWER_BANDS          (8)

/* 4965 factory calibration measures txघातer gain settings क्रम
 * each of 3 target output levels */
#घोषणा EEPROM_TX_POWER_MEASUREMENTS   (3)

/* 4965 Specअगरic */
/* 4965 driver करोes not work with txघातer calibration version < 5 */
#घोषणा EEPROM_4965_TX_POWER_VERSION    (5)
#घोषणा EEPROM_4965_EEPROM_VERSION	(0x2f)
#घोषणा EEPROM_4965_CALIB_VERSION_OFFSET       (2*0xB6)	/* 2 bytes */
#घोषणा EEPROM_4965_CALIB_TXPOWER_OFFSET       (2*0xE8)	/* 48  bytes */
#घोषणा EEPROM_4965_BOARD_REVISION             (2*0x4F)	/* 2 bytes */
#घोषणा EEPROM_4965_BOARD_PBA                  (2*0x56+1)	/* 9 bytes */

/* 2.4 GHz */
बाह्य स्थिर u8 il_eeprom_band_1[14];

/*
 * factory calibration data क्रम one txघातer level, on one channel,
 * measured on one of the 2 tx chains (radio transmitter and associated
 * antenna).  EEPROM contains:
 *
 * 1)  Temperature (degrees Celsius) of device when measurement was made.
 *
 * 2)  Gain table idx used to achieve the target measurement घातer.
 *     This refers to the "well-known" gain tables (see 4965.h).
 *
 * 3)  Actual measured output घातer, in half-dBm ("34" = 17 dBm).
 *
 * 4)  RF घातer amplअगरier detector level measurement (not used).
 */
काष्ठा il_eeprom_calib_measure अणु
	u8 temperature;		/* Device temperature (Celsius) */
	u8 gain_idx;		/* Index पूर्णांकo gain table */
	u8 actual_घात;		/* Measured RF output घातer, half-dBm */
	s8 pa_det;		/* Power amp detector level (not used) */
पूर्ण __packed;

/*
 * measurement set क्रम one channel.  EEPROM contains:
 *
 * 1)  Channel number measured
 *
 * 2)  Measurements क्रम each of 3 घातer levels क्रम each of 2 radio transmitters
 *     (a.k.a. "tx chains") (6 measurements altogether)
 */
काष्ठा il_eeprom_calib_ch_info अणु
	u8 ch_num;
	काष्ठा il_eeprom_calib_measure
	    measurements[EEPROM_TX_POWER_TX_CHAINS]
	    [EEPROM_TX_POWER_MEASUREMENTS];
पूर्ण __packed;

/*
 * txघातer subband info.
 *
 * For each frequency subband, EEPROM contains the following:
 *
 * 1)  First and last channels within range of the subband.  "0" values
 *     indicate that this sample set is not being used.
 *
 * 2)  Sample measurement sets क्रम 2 channels बंद to the range endpoपूर्णांकs.
 */
काष्ठा il_eeprom_calib_subband_info अणु
	u8 ch_from;		/* channel number of lowest channel in subband */
	u8 ch_to;		/* channel number of highest channel in subband */
	काष्ठा il_eeprom_calib_ch_info ch1;
	काष्ठा il_eeprom_calib_ch_info ch2;
पूर्ण __packed;

/*
 * txघातer calibration info.  EEPROM contains:
 *
 * 1)  Factory-measured saturation घातer levels (maximum levels at which
 *     tx घातer amplअगरier can output a संकेत without too much distortion).
 *     There is one level क्रम 2.4 GHz band and one क्रम 5 GHz band.  These
 *     values apply to all channels within each of the bands.
 *
 * 2)  Factory-measured घातer supply voltage level.  This is assumed to be
 *     स्थिरant (i.e. same value applies to all channels/bands) जबतक the
 *     factory measurements are being made.
 *
 * 3)  Up to 8 sets of factory-measured txघातer calibration values.
 *     These are क्रम dअगरferent frequency ranges, since txघातer gain
 *     अक्षरacteristics of the analog radio circuitry vary with frequency.
 *
 *     Not all sets need to be filled with data;
 *     काष्ठा il_eeprom_calib_subband_info contains range of channels
 *     (0 अगर unused) क्रम each set of data.
 */
काष्ठा il_eeprom_calib_info अणु
	u8 saturation_घातer24;	/* half-dBm (e.g. "34" = 17 dBm) */
	u8 saturation_घातer52;	/* half-dBm */
	__le16 voltage;		/* चिन्हित */
	काष्ठा il_eeprom_calib_subband_info band_info[EEPROM_TX_POWER_BANDS];
पूर्ण __packed;

/* General */
#घोषणा EEPROM_DEVICE_ID                    (2*0x08)	/* 2 bytes */
#घोषणा EEPROM_MAC_ADDRESS                  (2*0x15)	/* 6  bytes */
#घोषणा EEPROM_BOARD_REVISION               (2*0x35)	/* 2  bytes */
#घोषणा EEPROM_BOARD_PBA_NUMBER             (2*0x3B+1)	/* 9  bytes */
#घोषणा EEPROM_VERSION                      (2*0x44)	/* 2  bytes */
#घोषणा EEPROM_SKU_CAP                      (2*0x45)	/* 2  bytes */
#घोषणा EEPROM_OEM_MODE                     (2*0x46)	/* 2  bytes */
#घोषणा EEPROM_WOWLAN_MODE                  (2*0x47)	/* 2  bytes */
#घोषणा EEPROM_RADIO_CONFIG                 (2*0x48)	/* 2  bytes */
#घोषणा EEPROM_NUM_MAC_ADDRESS              (2*0x4C)	/* 2  bytes */

/* The following masks are to be applied on EEPROM_RADIO_CONFIG */
#घोषणा EEPROM_RF_CFG_TYPE_MSK(x)   (x & 0x3)	/* bits 0-1   */
#घोषणा EEPROM_RF_CFG_STEP_MSK(x)   ((x >> 2)  & 0x3)	/* bits 2-3   */
#घोषणा EEPROM_RF_CFG_DASH_MSK(x)   ((x >> 4)  & 0x3)	/* bits 4-5   */
#घोषणा EEPROM_RF_CFG_PNUM_MSK(x)   ((x >> 6)  & 0x3)	/* bits 6-7   */
#घोषणा EEPROM_RF_CFG_TX_ANT_MSK(x) ((x >> 8)  & 0xF)	/* bits 8-11  */
#घोषणा EEPROM_RF_CFG_RX_ANT_MSK(x) ((x >> 12) & 0xF)	/* bits 12-15 */

#घोषणा EEPROM_3945_RF_CFG_TYPE_MAX  0x0
#घोषणा EEPROM_4965_RF_CFG_TYPE_MAX  0x1

/*
 * Per-channel regulatory data.
 *
 * Each channel that *might* be supported by iwl has a fixed location
 * in EEPROM containing EEPROM_CHANNEL_* usage flags (LSB) and max regulatory
 * txघातer (MSB).
 *
 * Entries immediately below are क्रम 20 MHz channel width.  HT40 (40 MHz)
 * channels (only क्रम 4965, not supported by 3945) appear later in the EEPROM.
 *
 * 2.4 GHz channels 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14
 */
#घोषणा EEPROM_REGULATORY_SKU_ID            (2*0x60)	/* 4  bytes */
#घोषणा EEPROM_REGULATORY_BAND_1            (2*0x62)	/* 2  bytes */
#घोषणा EEPROM_REGULATORY_BAND_1_CHANNELS   (2*0x63)	/* 28 bytes */

/*
 * 4.9 GHz channels 183, 184, 185, 187, 188, 189, 192, 196,
 * 5.0 GHz channels 7, 8, 11, 12, 16
 * (4915-5080MHz) (none of these is ever supported)
 */
#घोषणा EEPROM_REGULATORY_BAND_2            (2*0x71)	/* 2  bytes */
#घोषणा EEPROM_REGULATORY_BAND_2_CHANNELS   (2*0x72)	/* 26 bytes */

/*
 * 5.2 GHz channels 34, 36, 38, 40, 42, 44, 46, 48, 52, 56, 60, 64
 * (5170-5320MHz)
 */
#घोषणा EEPROM_REGULATORY_BAND_3            (2*0x7F)	/* 2  bytes */
#घोषणा EEPROM_REGULATORY_BAND_3_CHANNELS   (2*0x80)	/* 24 bytes */

/*
 * 5.5 GHz channels 100, 104, 108, 112, 116, 120, 124, 128, 132, 136, 140
 * (5500-5700MHz)
 */
#घोषणा EEPROM_REGULATORY_BAND_4            (2*0x8C)	/* 2  bytes */
#घोषणा EEPROM_REGULATORY_BAND_4_CHANNELS   (2*0x8D)	/* 22 bytes */

/*
 * 5.7 GHz channels 145, 149, 153, 157, 161, 165
 * (5725-5825MHz)
 */
#घोषणा EEPROM_REGULATORY_BAND_5            (2*0x98)	/* 2  bytes */
#घोषणा EEPROM_REGULATORY_BAND_5_CHANNELS   (2*0x99)	/* 12 bytes */

/*
 * 2.4 GHz HT40 channels 1 (5), 2 (6), 3 (7), 4 (8), 5 (9), 6 (10), 7 (11)
 *
 * The channel listed is the center of the lower 20 MHz half of the channel.
 * The overall center frequency is actually 2 channels (10 MHz) above that,
 * and the upper half of each HT40 channel is centered 4 channels (20 MHz) away
 * from the lower half; e.g. the upper half of HT40 channel 1 is channel 5,
 * and the overall HT40 channel width centers on channel 3.
 *
 * NOTE:  The RXON command uses 20 MHz channel numbers to specअगरy the
 *        control channel to which to tune.  RXON also specअगरies whether the
 *        control channel is the upper or lower half of a HT40 channel.
 *
 * NOTE:  4965 करोes not support HT40 channels on 2.4 GHz.
 */
#घोषणा EEPROM_4965_REGULATORY_BAND_24_HT40_CHANNELS (2*0xA0)	/* 14 bytes */

/*
 * 5.2 GHz HT40 channels 36 (40), 44 (48), 52 (56), 60 (64),
 * 100 (104), 108 (112), 116 (120), 124 (128), 132 (136), 149 (153), 157 (161)
 */
#घोषणा EEPROM_4965_REGULATORY_BAND_52_HT40_CHANNELS (2*0xA8)	/* 22 bytes */

#घोषणा EEPROM_REGULATORY_BAND_NO_HT40			(0)

पूर्णांक il_eeprom_init(काष्ठा il_priv *il);
व्योम il_eeprom_मुक्त(काष्ठा il_priv *il);
स्थिर u8 *il_eeprom_query_addr(स्थिर काष्ठा il_priv *il, माप_प्रकार offset);
u16 il_eeprom_query16(स्थिर काष्ठा il_priv *il, माप_प्रकार offset);
पूर्णांक il_init_channel_map(काष्ठा il_priv *il);
व्योम il_मुक्त_channel_map(काष्ठा il_priv *il);
स्थिर काष्ठा il_channel_info *il_get_channel_info(स्थिर काष्ठा il_priv *il,
						  क्रमागत nl80211_band band,
						  u16 channel);

#घोषणा IL_NUM_SCAN_RATES         (2)

काष्ठा il4965_channel_tgd_info अणु
	u8 type;
	s8 max_घातer;
पूर्ण;

काष्ठा il4965_channel_tgh_info अणु
	s64 last_radar_समय;
पूर्ण;

#घोषणा IL4965_MAX_RATE (33)

काष्ठा il3945_clip_group अणु
	/* maximum घातer level to prevent clipping क्रम each rate, derived by
	 *   us from this band's saturation घातer in EEPROM */
	स्थिर s8 clip_घातers[IL_MAX_RATES];
पूर्ण;

/* current Tx घातer values to use, one क्रम each rate क्रम each channel.
 * requested घातer is limited by:
 * -- regulatory EEPROM limits क्रम this channel
 * -- hardware capabilities (clip-घातers)
 * -- spectrum management
 * -- user preference (e.g. iwconfig)
 * when requested घातer is set, base घातer idx must also be set. */
काष्ठा il3945_channel_घातer_info अणु
	काष्ठा il3945_tx_घातer tpc;	/* actual radio and DSP gain settings */
	s8 घातer_table_idx;	/* actual (compenst'd) idx पूर्णांकo gain table */
	s8 base_घातer_idx;	/* gain idx क्रम घातer at factory temp. */
	s8 requested_घातer;	/* घातer (dBm) requested क्रम this chnl/rate */
पूर्ण;

/* current scan Tx घातer values to use, one क्रम each scan rate क्रम each
 * channel. */
काष्ठा il3945_scan_घातer_info अणु
	काष्ठा il3945_tx_घातer tpc;	/* actual radio and DSP gain settings */
	s8 घातer_table_idx;	/* actual (compenst'd) idx पूर्णांकo gain table */
	s8 requested_घातer;	/* scan pwr (dBm) requested क्रम chnl/rate */
पूर्ण;

/*
 * One क्रम each channel, holds all channel setup data
 * Some of the fields (e.g. eeprom and flags/max_घातer_avg) are redundant
 *     with one another!
 */
काष्ठा il_channel_info अणु
	काष्ठा il4965_channel_tgd_info tgd;
	काष्ठा il4965_channel_tgh_info tgh;
	काष्ठा il_eeprom_channel eeprom;	/* EEPROM regulatory limit */
	काष्ठा il_eeprom_channel ht40_eeprom;	/* EEPROM regulatory limit क्रम
						 * HT40 channel */

	u8 channel;		/* channel number */
	u8 flags;		/* flags copied from EEPROM */
	s8 max_घातer_avg;	/* (dBm) regul. eeprom, normal Tx, any rate */
	s8 curr_txघात;		/* (dBm) regulatory/spectrum/user (not h/w) limit */
	s8 min_घातer;		/* always 0 */
	s8 scan_घातer;		/* (dBm) regul. eeprom, direct scans, any rate */

	u8 group_idx;		/* 0-4, maps channel to group1/2/3/4/5 */
	u8 band_idx;		/* 0-4, maps channel to band1/2/3/4/5 */
	क्रमागत nl80211_band band;

	/* HT40 channel info */
	s8 ht40_max_घातer_avg;	/* (dBm) regul. eeprom, normal Tx, any rate */
	u8 ht40_flags;		/* flags copied from EEPROM */
	u8 ht40_extension_channel;	/* HT_IE_EXT_CHANNEL_* */

	/* Radio/DSP gain settings क्रम each "normal" data Tx rate.
	 * These include, in addition to RF and DSP gain, a few fields क्रम
	 *   remembering/modअगरying gain settings (idxes). */
	काष्ठा il3945_channel_घातer_info घातer_info[IL4965_MAX_RATE];

	/* Radio/DSP gain settings क्रम each scan rate, क्रम directed scans. */
	काष्ठा il3945_scan_घातer_info scan_pwr_info[IL_NUM_SCAN_RATES];
पूर्ण;

#घोषणा IL_TX_FIFO_BK		0	/* shared */
#घोषणा IL_TX_FIFO_BE		1
#घोषणा IL_TX_FIFO_VI		2	/* shared */
#घोषणा IL_TX_FIFO_VO		3
#घोषणा IL_TX_FIFO_UNUSED	-1

/* Minimum number of queues. MAX_NUM is defined in hw specअगरic files.
 * Set the minimum to accommodate the 4 standard TX queues, 1 command
 * queue, 2 (unused) HCCA queues, and 4 HT queues (one क्रम each AC) */
#घोषणा IL_MIN_NUM_QUEUES	10

#घोषणा IL_DEFAULT_CMD_QUEUE_NUM	4

#घोषणा IEEE80211_DATA_LEN              2304
#घोषणा IEEE80211_4ADDR_LEN             30
#घोषणा IEEE80211_HLEN                  (IEEE80211_4ADDR_LEN)
#घोषणा IEEE80211_FRAME_LEN             (IEEE80211_DATA_LEN + IEEE80211_HLEN)

काष्ठा il_frame अणु
	जोड़ अणु
		काष्ठा ieee80211_hdr frame;
		काष्ठा il_tx_beacon_cmd beacon;
		u8 raw[IEEE80211_FRAME_LEN];
		u8 cmd[360];
	पूर्ण u;
	काष्ठा list_head list;
पूर्ण;

क्रमागत अणु
	CMD_SYNC = 0,
	CMD_SIZE_NORMAL = 0,
	CMD_NO_SKB = 0,
	CMD_SIZE_HUGE = (1 << 0),
	CMD_ASYNC = (1 << 1),
	CMD_WANT_SKB = (1 << 2),
	CMD_MAPPED = (1 << 3),
पूर्ण;

#घोषणा DEF_CMD_PAYLOAD_SIZE 320

/**
 * काष्ठा il_device_cmd
 *
 * For allocation of the command and tx queues, this establishes the overall
 * size of the largest command we send to uCode, except क्रम a scan command
 * (which is relatively huge; space is allocated separately).
 */
काष्ठा il_device_cmd अणु
	काष्ठा il_cmd_header hdr;	/* uCode API */
	जोड़ अणु
		u32 flags;
		u8 val8;
		u16 val16;
		u32 val32;
		काष्ठा il_tx_cmd tx;
		u8 payload[DEF_CMD_PAYLOAD_SIZE];
	पूर्ण __packed cmd;
पूर्ण __packed;

#घोषणा TFD_MAX_PAYLOAD_SIZE (माप(काष्ठा il_device_cmd))

काष्ठा il_host_cmd अणु
	स्थिर व्योम *data;
	अचिन्हित दीर्घ reply_page;
	व्योम (*callback) (काष्ठा il_priv *il, काष्ठा il_device_cmd *cmd,
			  काष्ठा il_rx_pkt *pkt);
	u32 flags;
	u16 len;
	u8 id;
पूर्ण;

#घोषणा SUP_RATE_11A_MAX_NUM_CHANNELS  8
#घोषणा SUP_RATE_11B_MAX_NUM_CHANNELS  4
#घोषणा SUP_RATE_11G_MAX_NUM_CHANNELS  12

/**
 * काष्ठा il_rx_queue - Rx queue
 * @bd: driver's poपूर्णांकer to buffer of receive buffer descriptors (rbd)
 * @bd_dma: bus address of buffer of receive buffer descriptors (rbd)
 * @पढ़ो: Shared idx to newest available Rx buffer
 * @ग_लिखो: Shared idx to oldest written Rx packet
 * @मुक्त_count: Number of pre-allocated buffers in rx_मुक्त
 * @rx_मुक्त: list of मुक्त SKBs क्रम use
 * @rx_used: List of Rx buffers with no SKB
 * @need_update: flag to indicate we need to update पढ़ो/ग_लिखो idx
 * @rb_stts: driver's poपूर्णांकer to receive buffer status
 * @rb_stts_dma: bus address of receive buffer status
 *
 * NOTE:  rx_मुक्त and rx_used are used as a FIFO क्रम il_rx_bufs
 */
काष्ठा il_rx_queue अणु
	__le32 *bd;
	dma_addr_t bd_dma;
	काष्ठा il_rx_buf pool[RX_QUEUE_SIZE + RX_FREE_BUFFERS];
	काष्ठा il_rx_buf *queue[RX_QUEUE_SIZE];
	u32 पढ़ो;
	u32 ग_लिखो;
	u32 मुक्त_count;
	u32 ग_लिखो_actual;
	काष्ठा list_head rx_मुक्त;
	काष्ठा list_head rx_used;
	पूर्णांक need_update;
	काष्ठा il_rb_status *rb_stts;
	dma_addr_t rb_stts_dma;
	spinlock_t lock;
पूर्ण;

#घोषणा IL_SUPPORTED_RATES_IE_LEN         8

#घोषणा MAX_TID_COUNT        9

#घोषणा IL_INVALID_RATE     0xFF
#घोषणा IL_INVALID_VALUE    -1

/**
 * काष्ठा il_ht_agg -- aggregation status जबतक रुकोing क्रम block-ack
 * @txq_id: Tx queue used क्रम Tx attempt
 * @frame_count: # frames attempted by Tx command
 * @रुको_क्रम_ba: Expect block-ack beक्रमe next Tx reply
 * @start_idx: Index of 1st Transmit Frame Descriptor (TFD) in Tx win
 * @biपंचांगap0: Low order biपंचांगap, one bit क्रम each frame pending ACK in Tx win
 * @biपंचांगap1: High order, one bit क्रम each frame pending ACK in Tx win
 * @rate_n_flags: Rate at which Tx was attempted
 *
 * If C_TX indicates that aggregation was attempted, driver must रुको
 * क्रम block ack (N_COMPRESSED_BA).  This काष्ठा stores tx reply info
 * until block ack arrives.
 */
काष्ठा il_ht_agg अणु
	u16 txq_id;
	u16 frame_count;
	u16 रुको_क्रम_ba;
	u16 start_idx;
	u64 biपंचांगap;
	u32 rate_n_flags;
#घोषणा IL_AGG_OFF 0
#घोषणा IL_AGG_ON 1
#घोषणा IL_EMPTYING_HW_QUEUE_ADDBA 2
#घोषणा IL_EMPTYING_HW_QUEUE_DELBA 3
	u8 state;
पूर्ण;

काष्ठा il_tid_data अणु
	u16 seq_number;		/* 4965 only */
	u16 tfds_in_queue;
	काष्ठा il_ht_agg agg;
पूर्ण;

काष्ठा il_hw_key अणु
	u32 cipher;
	पूर्णांक keylen;
	u8 keyidx;
	u8 key[32];
पूर्ण;

जोड़ il_ht_rate_supp अणु
	u16 rates;
	काष्ठा अणु
		u8 siso_rate;
		u8 mimo_rate;
	पूर्ण;
पूर्ण;

#घोषणा CFG_HT_RX_AMPDU_FACTOR_8K   (0x0)
#घोषणा CFG_HT_RX_AMPDU_FACTOR_16K  (0x1)
#घोषणा CFG_HT_RX_AMPDU_FACTOR_32K  (0x2)
#घोषणा CFG_HT_RX_AMPDU_FACTOR_64K  (0x3)
#घोषणा CFG_HT_RX_AMPDU_FACTOR_DEF  CFG_HT_RX_AMPDU_FACTOR_64K
#घोषणा CFG_HT_RX_AMPDU_FACTOR_MAX  CFG_HT_RX_AMPDU_FACTOR_64K
#घोषणा CFG_HT_RX_AMPDU_FACTOR_MIN  CFG_HT_RX_AMPDU_FACTOR_8K

/*
 * Maximal MPDU density क्रम TX aggregation
 * 4 - 2us density
 * 5 - 4us density
 * 6 - 8us density
 * 7 - 16us density
 */
#घोषणा CFG_HT_MPDU_DENSITY_2USEC   (0x4)
#घोषणा CFG_HT_MPDU_DENSITY_4USEC   (0x5)
#घोषणा CFG_HT_MPDU_DENSITY_8USEC   (0x6)
#घोषणा CFG_HT_MPDU_DENSITY_16USEC  (0x7)
#घोषणा CFG_HT_MPDU_DENSITY_DEF CFG_HT_MPDU_DENSITY_4USEC
#घोषणा CFG_HT_MPDU_DENSITY_MAX CFG_HT_MPDU_DENSITY_16USEC
#घोषणा CFG_HT_MPDU_DENSITY_MIN     (0x1)

काष्ठा il_ht_config अणु
	bool single_chain_sufficient;
	क्रमागत ieee80211_smps_mode smps;	/* current smps mode */
पूर्ण;

/* QoS काष्ठाures */
काष्ठा il_qos_info अणु
	पूर्णांक qos_active;
	काष्ठा il_qosparam_cmd def_qos_parm;
पूर्ण;

/*
 * Structure should be accessed with sta_lock held. When station addition
 * is in progress (IL_STA_UCODE_INPROGRESS) it is possible to access only
 * the commands (il_addsta_cmd and il_link_quality_cmd) without
 * sta_lock held.
 */
काष्ठा il_station_entry अणु
	काष्ठा il_addsta_cmd sta;
	काष्ठा il_tid_data tid[MAX_TID_COUNT];
	u8 used;
	काष्ठा il_hw_key keyinfo;
	काष्ठा il_link_quality_cmd *lq;
पूर्ण;

काष्ठा il_station_priv_common अणु
	u8 sta_id;
पूर्ण;

/**
 * काष्ठा il_vअगर_priv - driver's ilate per-पूर्णांकerface inक्रमmation
 *
 * When mac80211 allocates a भव पूर्णांकerface, it can allocate
 * space क्रम us to put data पूर्णांकo.
 */
काष्ठा il_vअगर_priv अणु
	u8 ibss_bssid_sta_id;
पूर्ण;

/* one क्रम each uCode image (inst/data, boot/init/runसमय) */
काष्ठा fw_desc अणु
	व्योम *v_addr;		/* access by driver */
	dma_addr_t p_addr;	/* access by card's busmaster DMA */
	u32 len;		/* bytes */
पूर्ण;

/* uCode file layout */
काष्ठा il_ucode_header अणु
	__le32 ver;		/* major/minor/API/serial */
	काष्ठा अणु
		__le32 inst_size;	/* bytes of runसमय code */
		__le32 data_size;	/* bytes of runसमय data */
		__le32 init_size;	/* bytes of init code */
		__le32 init_data_size;	/* bytes of init data */
		__le32 boot_size;	/* bytes of bootstrap code */
		u8 data[0];	/* in same order as sizes */
	पूर्ण v1;
पूर्ण;

काष्ठा il4965_ibss_seq अणु
	u8 mac[ETH_ALEN];
	u16 seq_num;
	u16 frag_num;
	अचिन्हित दीर्घ packet_समय;
	काष्ठा list_head list;
पूर्ण;

काष्ठा il_sensitivity_ranges अणु
	u16 min_nrg_cck;
	u16 max_nrg_cck;

	u16 nrg_th_cck;
	u16 nrg_th_ofdm;

	u16 स्वतः_corr_min_ofdm;
	u16 स्वतः_corr_min_ofdm_mrc;
	u16 स्वतः_corr_min_ofdm_x1;
	u16 स्वतः_corr_min_ofdm_mrc_x1;

	u16 स्वतः_corr_max_ofdm;
	u16 स्वतः_corr_max_ofdm_mrc;
	u16 स्वतः_corr_max_ofdm_x1;
	u16 स्वतः_corr_max_ofdm_mrc_x1;

	u16 स्वतः_corr_max_cck;
	u16 स्वतः_corr_max_cck_mrc;
	u16 स्वतः_corr_min_cck;
	u16 स्वतः_corr_min_cck_mrc;

	u16 barker_corr_th_min;
	u16 barker_corr_th_min_mrc;
	u16 nrg_th_cca;
पूर्ण;

/**
 * काष्ठा il_hw_params
 * @bcast_id: f/w broadcast station ID
 * @max_txq_num: Max # Tx queues supported
 * @dma_chnl_num: Number of Tx DMA/FIFO channels
 * @scd_bc_tbls_size: size of scheduler byte count tables
 * @tfd_size: TFD size
 * @tx/rx_chains_num: Number of TX/RX chains
 * @valid_tx/rx_ant: usable antennas
 * @max_rxq_size: Max # Rx frames in Rx queue (must be घातer-of-2)
 * @max_rxq_log: Log-base-2 of max_rxq_size
 * @rx_page_order: Rx buffer page order
 * @rx_wrt_ptr_reg: FHअणु39पूर्ण_RSCSR_CHNL0_WPTR
 * @max_stations:
 * @ht40_channel: is 40MHz width possible in band 2.4
 * BIT(NL80211_BAND_5GHZ) BIT(NL80211_BAND_5GHZ)
 * @sw_crypto: 0 क्रम hw, 1 क्रम sw
 * @max_xxx_size: क्रम ucode uses
 * @ct_समाप्त_threshold: temperature threshold
 * @beacon_समय_प्रकारsf_bits: number of valid tsf bits क्रम beacon समय
 * @काष्ठा il_sensitivity_ranges: range of sensitivity values
 */
काष्ठा il_hw_params अणु
	u8 bcast_id;
	u8 max_txq_num;
	u8 dma_chnl_num;
	u16 scd_bc_tbls_size;
	u32 tfd_size;
	u8 tx_chains_num;
	u8 rx_chains_num;
	u8 valid_tx_ant;
	u8 valid_rx_ant;
	u16 max_rxq_size;
	u16 max_rxq_log;
	u32 rx_page_order;
	u32 rx_wrt_ptr_reg;
	u8 max_stations;
	u8 ht40_channel;
	u8 max_beacon_itrvl;	/* in 1024 ms */
	u32 max_inst_size;
	u32 max_data_size;
	u32 max_bsm_size;
	u32 ct_समाप्त_threshold;	/* value in hw-dependent units */
	u16 beacon_समय_प्रकारsf_bits;
	स्थिर काष्ठा il_sensitivity_ranges *sens;
पूर्ण;

/******************************************************************************
 *
 * Functions implemented in core module which are क्रमward declared here
 * क्रम use by iwl-[4-5].c
 *
 * NOTE:  The implementation of these functions are not hardware specअगरic
 * which is why they are in the core module files.
 *
 * Naming convention --
 * il_         <-- Is part of iwlwअगरi
 * iwlXXXX_     <-- Hardware specअगरic (implemented in iwl-XXXX.c क्रम XXXX)
 * il4965_bg_      <-- Called from work queue context
 * il4965_mac_     <-- mac80211 callback
 *
 ****************************************************************************/
व्योम il4965_update_chain_flags(काष्ठा il_priv *il);
बाह्य स्थिर u8 il_bcast_addr[ETH_ALEN];
पूर्णांक il_queue_space(स्थिर काष्ठा il_queue *q);
अटल अंतरभूत पूर्णांक
il_queue_used(स्थिर काष्ठा il_queue *q, पूर्णांक i)
अणु
	वापस q->ग_लिखो_ptr >= q->पढ़ो_ptr ? (i >= q->पढ़ो_ptr &&
					      i < q->ग_लिखो_ptr) : !(i <
								    q->पढ़ो_ptr
								    && i >=
								    q->
								    ग_लिखो_ptr);
पूर्ण

अटल अंतरभूत u8
il_get_cmd_idx(काष्ठा il_queue *q, u32 idx, पूर्णांक is_huge)
अणु
	/*
	 * This is क्रम init calibration result and scan command which
	 * required buffer > TFD_MAX_PAYLOAD_SIZE,
	 * the big buffer at end of command array
	 */
	अगर (is_huge)
		वापस q->n_win;	/* must be घातer of 2 */

	/* Otherwise, use normal size buffers */
	वापस idx & (q->n_win - 1);
पूर्ण

काष्ठा il_dma_ptr अणु
	dma_addr_t dma;
	व्योम *addr;
	माप_प्रकार size;
पूर्ण;

#घोषणा IL_OPERATION_MODE_AUTO     0
#घोषणा IL_OPERATION_MODE_HT_ONLY  1
#घोषणा IL_OPERATION_MODE_MIXED    2
#घोषणा IL_OPERATION_MODE_20MHZ    3

#घोषणा IL_TX_CRC_SIZE 4
#घोषणा IL_TX_DELIMITER_SIZE 4

#घोषणा TX_POWER_IL_ILLEGAL_VOLTAGE -10000

/* Sensitivity and chain noise calibration */
#घोषणा INITIALIZATION_VALUE		0xFFFF
#घोषणा IL4965_CAL_NUM_BEACONS		20
#घोषणा IL_CAL_NUM_BEACONS		16
#घोषणा MAXIMUM_ALLOWED_PATHLOSS	15

#घोषणा CHAIN_NOISE_MAX_DELTA_GAIN_CODE 3

#घोषणा MAX_FA_OFDM  50
#घोषणा MIN_FA_OFDM  5
#घोषणा MAX_FA_CCK   50
#घोषणा MIN_FA_CCK   5

#घोषणा AUTO_CORR_STEP_OFDM       1

#घोषणा AUTO_CORR_STEP_CCK     3
#घोषणा AUTO_CORR_MAX_TH_CCK   160

#घोषणा NRG_DIFF               2
#घोषणा NRG_STEP_CCK           2
#घोषणा NRG_MARGIN             8
#घोषणा MAX_NUMBER_CCK_NO_FA 100

#घोषणा AUTO_CORR_CCK_MIN_VAL_DEF    (125)

#घोषणा CHAIN_A             0
#घोषणा CHAIN_B             1
#घोषणा CHAIN_C             2
#घोषणा CHAIN_NOISE_DELTA_GAIN_INIT_VAL 4
#घोषणा ALL_BAND_FILTER			0xFF00
#घोषणा IN_BAND_FILTER			0xFF
#घोषणा MIN_AVERAGE_NOISE_MAX_VALUE	0xFFFFFFFF

#घोषणा NRG_NUM_PREV_STAT_L     20
#घोषणा NUM_RX_CHAINS           3

क्रमागत il4965_false_alarm_state अणु
	IL_FA_TOO_MANY = 0,
	IL_FA_TOO_FEW = 1,
	IL_FA_GOOD_RANGE = 2,
पूर्ण;

क्रमागत il4965_chain_noise_state अणु
	IL_CHAIN_NOISE_ALIVE = 0,	/* must be 0 */
	IL_CHAIN_NOISE_ACCUMULATE,
	IL_CHAIN_NOISE_CALIBRATED,
	IL_CHAIN_NOISE_DONE,
पूर्ण;

क्रमागत ucode_type अणु
	UCODE_NONE = 0,
	UCODE_INIT,
	UCODE_RT
पूर्ण;

/* Sensitivity calib data */
काष्ठा il_sensitivity_data अणु
	u32 स्वतः_corr_ofdm;
	u32 स्वतः_corr_ofdm_mrc;
	u32 स्वतः_corr_ofdm_x1;
	u32 स्वतः_corr_ofdm_mrc_x1;
	u32 स्वतः_corr_cck;
	u32 स्वतः_corr_cck_mrc;

	u32 last_bad_plcp_cnt_ofdm;
	u32 last_fa_cnt_ofdm;
	u32 last_bad_plcp_cnt_cck;
	u32 last_fa_cnt_cck;

	u32 nrg_curr_state;
	u32 nrg_prev_state;
	u32 nrg_value[10];
	u8 nrg_silence_rssi[NRG_NUM_PREV_STAT_L];
	u32 nrg_silence_ref;
	u32 nrg_energy_idx;
	u32 nrg_silence_idx;
	u32 nrg_th_cck;
	s32 nrg_स्वतः_corr_silence_dअगरf;
	u32 num_in_cck_no_fa;
	u32 nrg_th_ofdm;

	u16 barker_corr_th_min;
	u16 barker_corr_th_min_mrc;
	u16 nrg_th_cca;
पूर्ण;

/* Chain noise (dअगरferential Rx gain) calib data */
काष्ठा il_chain_noise_data अणु
	u32 active_chains;
	u32 chain_noise_a;
	u32 chain_noise_b;
	u32 chain_noise_c;
	u32 chain_संकेत_a;
	u32 chain_संकेत_b;
	u32 chain_संकेत_c;
	u16 beacon_count;
	u8 disconn_array[NUM_RX_CHAINS];
	u8 delta_gain_code[NUM_RX_CHAINS];
	u8 radio_ग_लिखो;
	u8 state;
पूर्ण;

#घोषणा	EEPROM_SEM_TIMEOUT 10	/* milliseconds */
#घोषणा EEPROM_SEM_RETRY_LIMIT 1000	/* number of attempts (not समय) */

#घोषणा IL_TRAFFIC_ENTRIES	(256)
#घोषणा IL_TRAFFIC_ENTRY_SIZE  (64)

क्रमागत अणु
	MEASUREMENT_READY = (1 << 0),
	MEASUREMENT_ACTIVE = (1 << 1),
पूर्ण;

/* पूर्णांकerrupt stats */
काष्ठा isr_stats अणु
	u32 hw;
	u32 sw;
	u32 err_code;
	u32 sch;
	u32 alive;
	u32 rfसमाप्त;
	u32 ctसमाप्त;
	u32 wakeup;
	u32 rx;
	u32 handlers[IL_CN_MAX];
	u32 tx;
	u32 unhandled;
पूर्ण;

/* management stats */
क्रमागत il_mgmt_stats अणु
	MANAGEMENT_ASSOC_REQ = 0,
	MANAGEMENT_ASSOC_RESP,
	MANAGEMENT_REASSOC_REQ,
	MANAGEMENT_REASSOC_RESP,
	MANAGEMENT_PROBE_REQ,
	MANAGEMENT_PROBE_RESP,
	MANAGEMENT_BEACON,
	MANAGEMENT_ATIM,
	MANAGEMENT_DISASSOC,
	MANAGEMENT_AUTH,
	MANAGEMENT_DEAUTH,
	MANAGEMENT_ACTION,
	MANAGEMENT_MAX,
पूर्ण;
/* control stats */
क्रमागत il_ctrl_stats अणु
	CONTROL_BACK_REQ = 0,
	CONTROL_BACK,
	CONTROL_PSPOLL,
	CONTROL_RTS,
	CONTROL_CTS,
	CONTROL_ACK,
	CONTROL_CFEND,
	CONTROL_CFENDACK,
	CONTROL_MAX,
पूर्ण;

काष्ठा traffic_stats अणु
#अगर_घोषित CONFIG_IWLEGACY_DEBUGFS
	u32 mgmt[MANAGEMENT_MAX];
	u32 ctrl[CONTROL_MAX];
	u32 data_cnt;
	u64 data_bytes;
#पूर्ण_अगर
पूर्ण;

/*
 * host पूर्णांकerrupt समयout value
 * used with setting पूर्णांकerrupt coalescing समयr
 * the CSR_INT_COALESCING is an 8 bit रेजिस्टर in 32-usec unit
 *
 * शेष पूर्णांकerrupt coalescing समयr is 64 x 32 = 2048 usecs
 * शेष पूर्णांकerrupt coalescing calibration समयr is 16 x 32 = 512 usecs
 */
#घोषणा IL_HOST_INT_TIMEOUT_MAX	(0xFF)
#घोषणा IL_HOST_INT_TIMEOUT_DEF	(0x40)
#घोषणा IL_HOST_INT_TIMEOUT_MIN	(0x0)
#घोषणा IL_HOST_INT_CALIB_TIMEOUT_MAX	(0xFF)
#घोषणा IL_HOST_INT_CALIB_TIMEOUT_DEF	(0x10)
#घोषणा IL_HOST_INT_CALIB_TIMEOUT_MIN	(0x0)

#घोषणा IL_DELAY_NEXT_FORCE_FW_RELOAD (HZ*5)

/* TX queue watchकरोg समयouts in mSecs */
#घोषणा IL_DEF_WD_TIMEOUT	(2000)
#घोषणा IL_LONG_WD_TIMEOUT	(10000)
#घोषणा IL_MAX_WD_TIMEOUT	(120000)

काष्ठा il_क्रमce_reset अणु
	पूर्णांक reset_request_count;
	पूर्णांक reset_success_count;
	पूर्णांक reset_reject_count;
	अचिन्हित दीर्घ reset_duration;
	अचिन्हित दीर्घ last_क्रमce_reset_jअगरfies;
पूर्ण;

/* extend beacon समय क्रमmat bit shअगरting  */
/*
 * क्रम _3945 devices
 * bits 31:24 - extended
 * bits 23:0  - पूर्णांकerval
 */
#घोषणा IL3945_EXT_BEACON_TIME_POS	24
/*
 * क्रम _4965 devices
 * bits 31:22 - extended
 * bits 21:0  - पूर्णांकerval
 */
#घोषणा IL4965_EXT_BEACON_TIME_POS	22

काष्ठा il_rxon_context अणु
	काष्ठा ieee80211_vअगर *vअगर;
पूर्ण;

काष्ठा il_घातer_mgr अणु
	काष्ठा il_घातertable_cmd sleep_cmd;
	काष्ठा il_घातertable_cmd sleep_cmd_next;
	पूर्णांक debug_sleep_level_override;
	bool pci_pm;
	bool ps_disabled;
पूर्ण;

काष्ठा il_priv अणु
	काष्ठा ieee80211_hw *hw;
	काष्ठा ieee80211_channel *ieee_channels;
	काष्ठा ieee80211_rate *ieee_rates;

	काष्ठा il_cfg *cfg;
	स्थिर काष्ठा il_ops *ops;
#अगर_घोषित CONFIG_IWLEGACY_DEBUGFS
	स्थिर काष्ठा il_debugfs_ops *debugfs_ops;
#पूर्ण_अगर

	/* temporary frame storage list */
	काष्ठा list_head मुक्त_frames;
	पूर्णांक frames_count;

	क्रमागत nl80211_band band;
	पूर्णांक alloc_rxb_page;

	व्योम (*handlers[IL_CN_MAX]) (काष्ठा il_priv *il,
				     काष्ठा il_rx_buf *rxb);

	काष्ठा ieee80211_supported_band bands[NUM_NL80211_BANDS];

	/* spectrum measurement report caching */
	काष्ठा il_spectrum_notअगरication measure_report;
	u8 measurement_status;

	/* ucode beacon समय */
	u32 ucode_beacon_समय;
	पूर्णांक missed_beacon_threshold;

	/* track IBSS manager (last beacon) status */
	u32 ibss_manager;

	/* क्रमce reset */
	काष्ठा il_क्रमce_reset क्रमce_reset;

	/* we allocate array of il_channel_info क्रम NIC's valid channels.
	 *    Access via channel # using indirect idx array */
	काष्ठा il_channel_info *channel_info;	/* channel info array */
	u8 channel_count;	/* # of channels */

	/* thermal calibration */
	s32 temperature;	/* degrees Kelvin */
	s32 last_temperature;

	/* Scan related variables */
	अचिन्हित दीर्घ scan_start;
	अचिन्हित दीर्घ scan_start_tsf;
	व्योम *scan_cmd;
	क्रमागत nl80211_band scan_band;
	काष्ठा cfg80211_scan_request *scan_request;
	काष्ठा ieee80211_vअगर *scan_vअगर;
	u8 scan_tx_ant[NUM_NL80211_BANDS];
	u8 mgmt_tx_ant;

	/* spinlock */
	spinlock_t lock;	/* protect general shared data */
	spinlock_t hcmd_lock;	/* protect hcmd */
	spinlock_t reg_lock;	/* protect hw रेजिस्टर access */
	काष्ठा mutex mutex;

	/* basic pci-network driver stuff */
	काष्ठा pci_dev *pci_dev;

	/* pci hardware address support */
	व्योम __iomem *hw_base;
	u32 hw_rev;
	u32 hw_wa_rev;
	u8 rev_id;

	/* command queue number */
	u8 cmd_queue;

	/* max number of station keys */
	u8 sta_key_max_num;

	/* EEPROM MAC addresses */
	काष्ठा mac_address addresses[1];

	/* uCode images, save to reload in हाल of failure */
	पूर्णांक fw_idx;		/* firmware we're trying to load */
	u32 ucode_ver;		/* version of ucode, copy of
				   il_ucode.ver */
	काष्ठा fw_desc ucode_code;	/* runसमय inst */
	काष्ठा fw_desc ucode_data;	/* runसमय data original */
	काष्ठा fw_desc ucode_data_backup;	/* runसमय data save/restore */
	काष्ठा fw_desc ucode_init;	/* initialization inst */
	काष्ठा fw_desc ucode_init_data;	/* initialization data */
	काष्ठा fw_desc ucode_boot;	/* bootstrap inst */
	क्रमागत ucode_type ucode_type;
	u8 ucode_ग_लिखो_complete;	/* the image ग_लिखो is complete */
	अक्षर firmware_name[25];

	काष्ठा ieee80211_vअगर *vअगर;

	काष्ठा il_qos_info qos_data;

	काष्ठा अणु
		bool enabled;
		bool is_40mhz;
		bool non_gf_sta_present;
		u8 protection;
		u8 extension_chan_offset;
	पूर्ण ht;

	/*
	 * We declare this स्थिर so it can only be
	 * changed via explicit cast within the
	 * routines that actually update the physical
	 * hardware.
	 */
	स्थिर काष्ठा il_rxon_cmd active;
	काष्ठा il_rxon_cmd staging;

	काष्ठा il_rxon_समय_cmd timing;

	__le16 चयन_channel;

	/* 1st responses from initialize and runसमय uCode images.
	 * _4965's initialize alive response contains some calibration data. */
	काष्ठा il_init_alive_resp card_alive_init;
	काष्ठा il_alive_resp card_alive;

	u16 active_rate;

	u8 start_calib;
	काष्ठा il_sensitivity_data sensitivity_data;
	काष्ठा il_chain_noise_data chain_noise_data;
	__le16 sensitivity_tbl[HD_TBL_SIZE];

	काष्ठा il_ht_config current_ht_config;

	/* Rate scaling data */
	u8 retry_rate;

	रुको_queue_head_t रुको_command_queue;

	पूर्णांक activity_समयr_active;

	/* Rx and Tx DMA processing queues */
	काष्ठा il_rx_queue rxq;
	काष्ठा il_tx_queue *txq;
	अचिन्हित दीर्घ txq_ctx_active_msk;
	काष्ठा il_dma_ptr kw;	/* keep warm address */
	काष्ठा il_dma_ptr scd_bc_tbls;

	u32 scd_base_addr;	/* scheduler sram base address */

	अचिन्हित दीर्घ status;

	/* counts mgmt, ctl, and data packets */
	काष्ठा traffic_stats tx_stats;
	काष्ठा traffic_stats rx_stats;

	/* counts पूर्णांकerrupts */
	काष्ठा isr_stats isr_stats;

	काष्ठा il_घातer_mgr घातer_data;

	/* context inक्रमmation */
	u8 bssid[ETH_ALEN];	/* used only on 3945 but filled by core */

	/* station table variables */

	/* Note: अगर lock and sta_lock are needed, lock must be acquired first */
	spinlock_t sta_lock;
	पूर्णांक num_stations;
	काष्ठा il_station_entry stations[IL_STATION_COUNT];
	अचिन्हित दीर्घ ucode_key_table;

	/* queue refcounts */
#घोषणा IL_MAX_HW_QUEUES	32
	अचिन्हित दीर्घ queue_stopped[BITS_TO_LONGS(IL_MAX_HW_QUEUES)];
#घोषणा IL_STOP_REASON_PASSIVE	0
	अचिन्हित दीर्घ stop_reason;
	/* क्रम each AC */
	atomic_t queue_stop_count[4];

	/* Indication अगर ieee80211_ops->खोलो has been called */
	u8 is_खोलो;

	u8 mac80211_रेजिस्टरed;

	/* eeprom -- this is in the card's little endian byte order */
	u8 *eeprom;
	काष्ठा il_eeprom_calib_info *calib_info;

	क्रमागत nl80211_अगरtype iw_mode;

	/* Last Rx'd beacon बारtamp */
	u64 बारtamp;

	जोड़ अणु
#अगर IS_ENABLED(CONFIG_IWL3945)
		काष्ठा अणु
			व्योम *shared_virt;
			dma_addr_t shared_phys;

			काष्ठा delayed_work thermal_periodic;
			काष्ठा delayed_work rfसमाप्त_poll;

			काष्ठा il3945_notअगर_stats stats;
#अगर_घोषित CONFIG_IWLEGACY_DEBUGFS
			काष्ठा il3945_notअगर_stats accum_stats;
			काष्ठा il3945_notअगर_stats delta_stats;
			काष्ठा il3945_notअगर_stats max_delta;
#पूर्ण_अगर

			u32 sta_supp_rates;
			पूर्णांक last_rx_rssi;	/* From Rx packet stats */

			/* Rx'd packet timing inक्रमmation */
			u32 last_beacon_समय;
			u64 last_tsf;

			/*
			 * each calibration channel group in the
			 * EEPROM has a derived clip setting क्रम
			 * each rate.
			 */
			स्थिर काष्ठा il3945_clip_group clip_groups[5];

		पूर्ण _3945;
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_IWL4965)
		काष्ठा अणु
			काष्ठा il_rx_phy_res last_phy_res;
			bool last_phy_res_valid;
			u32 ampdu_ref;

			काष्ठा completion firmware_loading_complete;

			/*
			 * chain noise reset and gain commands are the
			 * two extra calibration commands follows the standard
			 * phy calibration commands
			 */
			u8 phy_calib_chain_noise_reset_cmd;
			u8 phy_calib_chain_noise_gain_cmd;

			u8 key_mapping_keys;
			काष्ठा il_wep_key wep_keys[WEP_KEYS_MAX];

			काष्ठा il_notअगर_stats stats;
#अगर_घोषित CONFIG_IWLEGACY_DEBUGFS
			काष्ठा il_notअगर_stats accum_stats;
			काष्ठा il_notअगर_stats delta_stats;
			काष्ठा il_notअगर_stats max_delta;
#पूर्ण_अगर

		पूर्ण _4965;
#पूर्ण_अगर
	पूर्ण;

	काष्ठा il_hw_params hw_params;

	u32 पूर्णांकa_mask;

	काष्ठा workqueue_काष्ठा *workqueue;

	काष्ठा work_काष्ठा restart;
	काष्ठा work_काष्ठा scan_completed;
	काष्ठा work_काष्ठा rx_replenish;
	काष्ठा work_काष्ठा पात_scan;

	bool beacon_enabled;
	काष्ठा sk_buff *beacon_skb;

	काष्ठा work_काष्ठा tx_flush;

	काष्ठा tasklet_काष्ठा irq_tasklet;

	काष्ठा delayed_work init_alive_start;
	काष्ठा delayed_work alive_start;
	काष्ठा delayed_work scan_check;

	/* TX Power */
	s8 tx_घातer_user_lmt;
	s8 tx_घातer_device_lmt;
	s8 tx_घातer_next;

#अगर_घोषित CONFIG_IWLEGACY_DEBUG
	/* debugging info */
	u32 debug_level;	/* per device debugging will override global
				   il_debug_level अगर set */
#पूर्ण_अगर				/* CONFIG_IWLEGACY_DEBUG */
#अगर_घोषित CONFIG_IWLEGACY_DEBUGFS
	/* debugfs */
	u16 tx_traffic_idx;
	u16 rx_traffic_idx;
	u8 *tx_traffic;
	u8 *rx_traffic;
	काष्ठा dentry *debugfs_dir;
	u32 dbgfs_sram_offset, dbgfs_sram_len;
	bool disable_ht40;
#पूर्ण_अगर				/* CONFIG_IWLEGACY_DEBUGFS */

	काष्ठा work_काष्ठा txघातer_work;
	bool disable_sens_cal;
	bool disable_chain_noise_cal;
	bool disable_tx_घातer_cal;
	काष्ठा work_काष्ठा run_समय_calib_work;
	काष्ठा समयr_list stats_periodic;
	काष्ठा समयr_list watchकरोg;
	bool hw_पढ़ोy;

	काष्ठा led_classdev led;
	अचिन्हित दीर्घ blink_on, blink_off;
	bool led_रेजिस्टरed;
पूर्ण;				/*il_priv */

अटल अंतरभूत व्योम
il_txq_ctx_activate(काष्ठा il_priv *il, पूर्णांक txq_id)
अणु
	set_bit(txq_id, &il->txq_ctx_active_msk);
पूर्ण

अटल अंतरभूत व्योम
il_txq_ctx_deactivate(काष्ठा il_priv *il, पूर्णांक txq_id)
अणु
	clear_bit(txq_id, &il->txq_ctx_active_msk);
पूर्ण

अटल अंतरभूत पूर्णांक
il_is_associated(काष्ठा il_priv *il)
अणु
	वापस (il->active.filter_flags & RXON_FILTER_ASSOC_MSK) ? 1 : 0;
पूर्ण

अटल अंतरभूत पूर्णांक
il_is_any_associated(काष्ठा il_priv *il)
अणु
	वापस il_is_associated(il);
पूर्ण

अटल अंतरभूत पूर्णांक
il_is_channel_valid(स्थिर काष्ठा il_channel_info *ch_info)
अणु
	अगर (ch_info == शून्य)
		वापस 0;
	वापस (ch_info->flags & EEPROM_CHANNEL_VALID) ? 1 : 0;
पूर्ण

अटल अंतरभूत पूर्णांक
il_is_channel_radar(स्थिर काष्ठा il_channel_info *ch_info)
अणु
	वापस (ch_info->flags & EEPROM_CHANNEL_RADAR) ? 1 : 0;
पूर्ण

अटल अंतरभूत u8
il_is_channel_a_band(स्थिर काष्ठा il_channel_info *ch_info)
अणु
	वापस ch_info->band == NL80211_BAND_5GHZ;
पूर्ण

अटल अंतरभूत पूर्णांक
il_is_channel_passive(स्थिर काष्ठा il_channel_info *ch)
अणु
	वापस (!(ch->flags & EEPROM_CHANNEL_ACTIVE)) ? 1 : 0;
पूर्ण

अटल अंतरभूत पूर्णांक
il_is_channel_ibss(स्थिर काष्ठा il_channel_info *ch)
अणु
	वापस (ch->flags & EEPROM_CHANNEL_IBSS) ? 1 : 0;
पूर्ण

अटल अंतरभूत व्योम
__il_मुक्त_pages(काष्ठा il_priv *il, काष्ठा page *page)
अणु
	__मुक्त_pages(page, il->hw_params.rx_page_order);
	il->alloc_rxb_page--;
पूर्ण

अटल अंतरभूत व्योम
il_मुक्त_pages(काष्ठा il_priv *il, अचिन्हित दीर्घ page)
अणु
	मुक्त_pages(page, il->hw_params.rx_page_order);
	il->alloc_rxb_page--;
पूर्ण

#घोषणा IWLWIFI_VERSION "in-tree:"
#घोषणा DRV_COPYRIGHT	"Copyright(c) 2003-2011 Intel Corporation"
#घोषणा DRV_AUTHOR     "<ilw@linux.intel.com>"

#घोषणा IL_PCI_DEVICE(dev, subdev, cfg) \
	.venकरोr = PCI_VENDOR_ID_INTEL,  .device = (dev), \
	.subvenकरोr = PCI_ANY_ID, .subdevice = (subdev), \
	.driver_data = (kernel_uदीर्घ_t)&(cfg)

#घोषणा TIME_UNIT		1024

#घोषणा IL_SKU_G       0x1
#घोषणा IL_SKU_A       0x2
#घोषणा IL_SKU_N       0x8

#घोषणा IL_CMD(x) हाल x: वापस #x

/* Size of one Rx buffer in host DRAM */
#घोषणा IL_RX_BUF_SIZE_3K (3 * 1000)	/* 3945 only */
#घोषणा IL_RX_BUF_SIZE_4K (4 * 1024)
#घोषणा IL_RX_BUF_SIZE_8K (8 * 1024)

#अगर_घोषित CONFIG_IWLEGACY_DEBUGFS
काष्ठा il_debugfs_ops अणु
	sमाप_प्रकार(*rx_stats_पढ़ो) (काष्ठा file *file, अक्षर __user *user_buf,
				 माप_प्रकार count, loff_t *ppos);
	sमाप_प्रकार(*tx_stats_पढ़ो) (काष्ठा file *file, अक्षर __user *user_buf,
				 माप_प्रकार count, loff_t *ppos);
	sमाप_प्रकार(*general_stats_पढ़ो) (काष्ठा file *file,
				      अक्षर __user *user_buf, माप_प्रकार count,
				      loff_t *ppos);
पूर्ण;
#पूर्ण_अगर

काष्ठा il_ops अणु
	/* Handling TX */
	व्योम (*txq_update_byte_cnt_tbl) (काष्ठा il_priv *il,
					 काष्ठा il_tx_queue *txq,
					 u16 byte_cnt);
	पूर्णांक (*txq_attach_buf_to_tfd) (काष्ठा il_priv *il,
				      काष्ठा il_tx_queue *txq, dma_addr_t addr,
				      u16 len, u8 reset, u8 pad);
	व्योम (*txq_मुक्त_tfd) (काष्ठा il_priv *il, काष्ठा il_tx_queue *txq);
	पूर्णांक (*txq_init) (काष्ठा il_priv *il, काष्ठा il_tx_queue *txq);
	/* alive notअगरication after init uCode load */
	व्योम (*init_alive_start) (काष्ठा il_priv *il);
	/* check validity of rtc data address */
	पूर्णांक (*is_valid_rtc_data_addr) (u32 addr);
	/* 1st ucode load */
	पूर्णांक (*load_ucode) (काष्ठा il_priv *il);

	व्योम (*dump_nic_error_log) (काष्ठा il_priv *il);
	पूर्णांक (*dump_fh) (काष्ठा il_priv *il, अक्षर **buf, bool display);
	पूर्णांक (*set_channel_चयन) (काष्ठा il_priv *il,
				   काष्ठा ieee80211_channel_चयन *ch_चयन);
	/* घातer management */
	पूर्णांक (*apm_init) (काष्ठा il_priv *il);

	/* tx घातer */
	पूर्णांक (*send_tx_घातer) (काष्ठा il_priv *il);
	व्योम (*update_chain_flags) (काष्ठा il_priv *il);

	/* eeprom operations */
	पूर्णांक (*eeprom_acquire_semaphore) (काष्ठा il_priv *il);
	व्योम (*eeprom_release_semaphore) (काष्ठा il_priv *il);

	पूर्णांक (*rxon_assoc) (काष्ठा il_priv *il);
	पूर्णांक (*commit_rxon) (काष्ठा il_priv *il);
	व्योम (*set_rxon_chain) (काष्ठा il_priv *il);

	u16(*get_hcmd_size) (u8 cmd_id, u16 len);
	u16(*build_addsta_hcmd) (स्थिर काष्ठा il_addsta_cmd *cmd, u8 *data);

	पूर्णांक (*request_scan) (काष्ठा il_priv *il, काष्ठा ieee80211_vअगर *vअगर);
	व्योम (*post_scan) (काष्ठा il_priv *il);
	व्योम (*post_associate) (काष्ठा il_priv *il);
	व्योम (*config_ap) (काष्ठा il_priv *il);
	/* station management */
	पूर्णांक (*update_bcast_stations) (काष्ठा il_priv *il);
	पूर्णांक (*manage_ibss_station) (काष्ठा il_priv *il,
				    काष्ठा ieee80211_vअगर *vअगर, bool add);

	पूर्णांक (*send_led_cmd) (काष्ठा il_priv *il, काष्ठा il_led_cmd *led_cmd);
पूर्ण;

काष्ठा il_mod_params अणु
	पूर्णांक sw_crypto;		/* def: 0 = using hardware encryption */
	पूर्णांक disable_hw_scan;	/* def: 0 = use h/w scan */
	पूर्णांक num_of_queues;	/* def: HW dependent */
	पूर्णांक disable_11n;	/* def: 0 = 11n capabilities enabled */
	पूर्णांक amsdu_size_8K;	/* def: 0 = disable 8K amsdu size */
	पूर्णांक antenna;		/* def: 0 = both antennas (use भागersity) */
	पूर्णांक restart_fw;		/* def: 1 = restart firmware */
पूर्ण;

#घोषणा IL_LED_SOLID 11
#घोषणा IL_DEF_LED_INTRVL cpu_to_le32(1000)

#घोषणा IL_LED_ACTIVITY       (0<<1)
#घोषणा IL_LED_LINK           (1<<1)

/*
 * LED mode
 *    IL_LED_DEFAULT:  use device शेष
 *    IL_LED_RF_STATE: turn LED on/off based on RF state
 *			LED ON  = RF ON
 *			LED OFF = RF OFF
 *    IL_LED_BLINK:    adjust led blink rate based on blink table
 */
क्रमागत il_led_mode अणु
	IL_LED_DEFAULT,
	IL_LED_RF_STATE,
	IL_LED_BLINK,
पूर्ण;

व्योम il_leds_init(काष्ठा il_priv *il);
व्योम il_leds_निकास(काष्ठा il_priv *il);

/**
 * काष्ठा il_cfg
 * @fw_name_pre: Firmware filename prefix. The api version and extension
 *	(.ucode) will be added to filename beक्रमe loading from disk. The
 *	filename is स्थिरructed as fw_name_pre<api>.ucode.
 * @ucode_api_max: Highest version of uCode API supported by driver.
 * @ucode_api_min: Lowest version of uCode API supported by driver.
 * @scan_antennas: available antenna क्रम scan operation
 * @led_mode: 0=blinking, 1=On(RF On)/Off(RF Off)
 *
 * We enable the driver to be backward compatible wrt API version. The
 * driver specअगरies which APIs it supports (with @ucode_api_max being the
 * highest and @ucode_api_min the lowest). Firmware will only be loaded अगर
 * it has a supported API version. The firmware's API version will be
 * stored in @il_priv, enabling the driver to make runसमय changes based
 * on firmware version used.
 *
 * For example,
 * अगर (IL_UCODE_API(il->ucode_ver) >= 2) अणु
 *	Driver पूर्णांकeracts with Firmware API version >= 2.
 * पूर्ण अन्यथा अणु
 *	Driver पूर्णांकeracts with Firmware API version 1.
 * पूर्ण
 *
 * The ideal usage of this infraकाष्ठाure is to treat a new ucode API
 * release as a new hardware revision. That is, through utilizing the
 * il_hcmd_utils_ops etc. we accommodate dअगरferent command काष्ठाures
 * and flows between hardware versions as well as their API
 * versions.
 *
 */
काष्ठा il_cfg अणु
	/* params specअगरic to an inभागidual device within a device family */
	स्थिर अक्षर *name;
	स्थिर अक्षर *fw_name_pre;
	स्थिर अचिन्हित पूर्णांक ucode_api_max;
	स्थिर अचिन्हित पूर्णांक ucode_api_min;
	u8 valid_tx_ant;
	u8 valid_rx_ant;
	अचिन्हित पूर्णांक sku;
	u16 eeprom_ver;
	u16 eeprom_calib_ver;
	/* module based parameters which can be set from modprobe cmd */
	स्थिर काष्ठा il_mod_params *mod_params;
	/* params not likely to change within a device family */
	काष्ठा il_base_params *base_params;
	/* params likely to change within a device family */
	u8 scan_rx_antennas[NUM_NL80211_BANDS];
	क्रमागत il_led_mode led_mode;

	पूर्णांक eeprom_size;
	पूर्णांक num_of_queues;		/* def: HW dependent */
	पूर्णांक num_of_ampdu_queues;	/* def: HW dependent */
	/* क्रम il_apm_init() */
	u32 pll_cfg_val;
	bool set_l0s;
	bool use_bsm;

	u16 led_compensation;
	पूर्णांक chain_noise_num_beacons;
	अचिन्हित पूर्णांक wd_समयout;
	bool temperature_kelvin;
	स्थिर bool ucode_tracing;
	स्थिर bool sensitivity_calib_by_driver;
	स्थिर bool chain_noise_calib_by_driver;

	स्थिर u32 regulatory_bands[7];
पूर्ण;

/***************************
 *   L i b                 *
 ***************************/

पूर्णांक il_mac_conf_tx(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
		   u16 queue, स्थिर काष्ठा ieee80211_tx_queue_params *params);
पूर्णांक il_mac_tx_last_beacon(काष्ठा ieee80211_hw *hw);

व्योम il_set_rxon_hwcrypto(काष्ठा il_priv *il, पूर्णांक hw_decrypt);
पूर्णांक il_check_rxon_cmd(काष्ठा il_priv *il);
पूर्णांक il_full_rxon_required(काष्ठा il_priv *il);
पूर्णांक il_set_rxon_channel(काष्ठा il_priv *il, काष्ठा ieee80211_channel *ch);
व्योम il_set_flags_क्रम_band(काष्ठा il_priv *il, क्रमागत nl80211_band band,
			   काष्ठा ieee80211_vअगर *vअगर);
u8 il_get_single_channel_number(काष्ठा il_priv *il, क्रमागत nl80211_band band);
व्योम il_set_rxon_ht(काष्ठा il_priv *il, काष्ठा il_ht_config *ht_conf);
bool il_is_ht40_tx_allowed(काष्ठा il_priv *il,
			   काष्ठा ieee80211_sta_ht_cap *ht_cap);
व्योम il_connection_init_rx_config(काष्ठा il_priv *il);
व्योम il_set_rate(काष्ठा il_priv *il);
पूर्णांक il_set_decrypted_flag(काष्ठा il_priv *il, काष्ठा ieee80211_hdr *hdr,
			  u32 decrypt_res, काष्ठा ieee80211_rx_status *stats);
व्योम il_irq_handle_error(काष्ठा il_priv *il);
पूर्णांक il_mac_add_पूर्णांकerface(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर);
व्योम il_mac_हटाओ_पूर्णांकerface(काष्ठा ieee80211_hw *hw,
			     काष्ठा ieee80211_vअगर *vअगर);
पूर्णांक il_mac_change_पूर्णांकerface(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
			    क्रमागत nl80211_अगरtype newtype, bool newp2p);
व्योम il_mac_flush(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
		  u32 queues, bool drop);
पूर्णांक il_alloc_txq_mem(काष्ठा il_priv *il);
व्योम il_मुक्त_txq_mem(काष्ठा il_priv *il);

#अगर_घोषित CONFIG_IWLEGACY_DEBUGFS
व्योम il_update_stats(काष्ठा il_priv *il, bool is_tx, __le16 fc, u16 len);
#अन्यथा
अटल अंतरभूत व्योम
il_update_stats(काष्ठा il_priv *il, bool is_tx, __le16 fc, u16 len)
अणु
पूर्ण
#पूर्ण_अगर

/*****************************************************
 * Handlers
 ***************************************************/
व्योम il_hdl_pm_sleep(काष्ठा il_priv *il, काष्ठा il_rx_buf *rxb);
व्योम il_hdl_pm_debug_stats(काष्ठा il_priv *il, काष्ठा il_rx_buf *rxb);
व्योम il_hdl_error(काष्ठा il_priv *il, काष्ठा il_rx_buf *rxb);
व्योम il_hdl_csa(काष्ठा il_priv *il, काष्ठा il_rx_buf *rxb);

/*****************************************************
* RX
******************************************************/
व्योम il_cmd_queue_unmap(काष्ठा il_priv *il);
व्योम il_cmd_queue_मुक्त(काष्ठा il_priv *il);
पूर्णांक il_rx_queue_alloc(काष्ठा il_priv *il);
व्योम il_rx_queue_update_ग_लिखो_ptr(काष्ठा il_priv *il, काष्ठा il_rx_queue *q);
पूर्णांक il_rx_queue_space(स्थिर काष्ठा il_rx_queue *q);
व्योम il_tx_cmd_complete(काष्ठा il_priv *il, काष्ठा il_rx_buf *rxb);

व्योम il_hdl_spectrum_measurement(काष्ठा il_priv *il, काष्ठा il_rx_buf *rxb);
व्योम il_recover_from_stats(काष्ठा il_priv *il, काष्ठा il_rx_pkt *pkt);
व्योम il_chचयन_करोne(काष्ठा il_priv *il, bool is_success);

/*****************************************************
* TX
******************************************************/
व्योम il_txq_update_ग_लिखो_ptr(काष्ठा il_priv *il, काष्ठा il_tx_queue *txq);
पूर्णांक il_tx_queue_init(काष्ठा il_priv *il, u32 txq_id);
व्योम il_tx_queue_reset(काष्ठा il_priv *il, u32 txq_id);
व्योम il_tx_queue_unmap(काष्ठा il_priv *il, पूर्णांक txq_id);
व्योम il_tx_queue_मुक्त(काष्ठा il_priv *il, पूर्णांक txq_id);
व्योम il_setup_watchकरोg(काष्ठा il_priv *il);
/*****************************************************
 * TX घातer
 ****************************************************/
पूर्णांक il_set_tx_घातer(काष्ठा il_priv *il, s8 tx_घातer, bool क्रमce);

/*******************************************************************************
 * Rate
 ******************************************************************************/

u8 il_get_lowest_plcp(काष्ठा il_priv *il);

/*******************************************************************************
 * Scanning
 ******************************************************************************/
व्योम il_init_scan_params(काष्ठा il_priv *il);
पूर्णांक il_scan_cancel(काष्ठा il_priv *il);
पूर्णांक il_scan_cancel_समयout(काष्ठा il_priv *il, अचिन्हित दीर्घ ms);
व्योम il_क्रमce_scan_end(काष्ठा il_priv *il);
पूर्णांक il_mac_hw_scan(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
		   काष्ठा ieee80211_scan_request *hw_req);
व्योम il_पूर्णांकernal_लघु_hw_scan(काष्ठा il_priv *il);
पूर्णांक il_क्रमce_reset(काष्ठा il_priv *il, bool बाह्यal);
u16 il_fill_probe_req(काष्ठा il_priv *il, काष्ठा ieee80211_mgmt *frame,
		      स्थिर u8 *ta, स्थिर u8 *ie, पूर्णांक ie_len, पूर्णांक left);
व्योम il_setup_rx_scan_handlers(काष्ठा il_priv *il);
u16 il_get_active_dwell_समय(काष्ठा il_priv *il, क्रमागत nl80211_band band,
			     u8 n_probes);
u16 il_get_passive_dwell_समय(काष्ठा il_priv *il, क्रमागत nl80211_band band,
			      काष्ठा ieee80211_vअगर *vअगर);
व्योम il_setup_scan_deferred_work(काष्ठा il_priv *il);
व्योम il_cancel_scan_deferred_work(काष्ठा il_priv *il);

/* For faster active scanning, scan will move to the next channel अगर fewer than
 * PLCP_QUIET_THRESH packets are heard on this channel within
 * ACTIVE_QUIET_TIME after sending probe request.  This लघुens the dwell
 * समय अगर it's a quiet channel (nothing responded to our probe, and there's
 * no other traffic).
 * Disable "quiet" feature by setting PLCP_QUIET_THRESH to 0. */
#घोषणा IL_ACTIVE_QUIET_TIME       cpu_to_le16(10)	/* msec */
#घोषणा IL_PLCP_QUIET_THRESH       cpu_to_le16(1)	/* packets */

#घोषणा IL_SCAN_CHECK_WATCHDOG		(HZ * 7)

/*****************************************************
 *   S e n d i n g     H o s t     C o m m a n d s   *
 *****************************************************/

स्थिर अक्षर *il_get_cmd_string(u8 cmd);
पूर्णांक __must_check il_send_cmd_sync(काष्ठा il_priv *il, काष्ठा il_host_cmd *cmd);
पूर्णांक il_send_cmd(काष्ठा il_priv *il, काष्ठा il_host_cmd *cmd);
पूर्णांक __must_check il_send_cmd_pdu(काष्ठा il_priv *il, u8 id, u16 len,
				 स्थिर व्योम *data);
पूर्णांक il_send_cmd_pdu_async(काष्ठा il_priv *il, u8 id, u16 len, स्थिर व्योम *data,
			  व्योम (*callback) (काष्ठा il_priv *il,
					    काष्ठा il_device_cmd *cmd,
					    काष्ठा il_rx_pkt *pkt));

पूर्णांक il_enqueue_hcmd(काष्ठा il_priv *il, काष्ठा il_host_cmd *cmd);

/*****************************************************
 * PCI						     *
 *****************************************************/

व्योम il_bg_watchकरोg(काष्ठा समयr_list *t);
u32 il_usecs_to_beacons(काष्ठा il_priv *il, u32 usec, u32 beacon_पूर्णांकerval);
__le32 il_add_beacon_समय(काष्ठा il_priv *il, u32 base, u32 adकरोn,
			  u32 beacon_पूर्णांकerval);

#अगर_घोषित CONFIG_PM_SLEEP
बाह्य स्थिर काष्ठा dev_pm_ops il_pm_ops;

#घोषणा IL_LEGACY_PM_OPS	(&il_pm_ops)

#अन्यथा /* !CONFIG_PM_SLEEP */

#घोषणा IL_LEGACY_PM_OPS	शून्य

#पूर्ण_अगर /* !CONFIG_PM_SLEEP */

/*****************************************************
*  Error Handling Debugging
******************************************************/
व्योम il4965_dump_nic_error_log(काष्ठा il_priv *il);
#अगर_घोषित CONFIG_IWLEGACY_DEBUG
व्योम il_prपूर्णांक_rx_config_cmd(काष्ठा il_priv *il);
#अन्यथा
अटल अंतरभूत व्योम
il_prपूर्णांक_rx_config_cmd(काष्ठा il_priv *il)
अणु
पूर्ण
#पूर्ण_अगर

व्योम il_clear_isr_stats(काष्ठा il_priv *il);

/*****************************************************
*  GEOS
******************************************************/
पूर्णांक il_init_geos(काष्ठा il_priv *il);
व्योम il_मुक्त_geos(काष्ठा il_priv *il);

/*************** DRIVER STATUS FUNCTIONS   *****/

#घोषणा S_HCMD_ACTIVE	0	/* host command in progress */
/* 1 is unused (used to be S_HCMD_SYNC_ACTIVE) */
#घोषणा S_INT_ENABLED	2
#घोषणा S_RFKILL	3
#घोषणा S_CT_KILL		4
#घोषणा S_INIT		5
#घोषणा S_ALIVE		6
#घोषणा S_READY		7
#घोषणा S_TEMPERATURE	8
#घोषणा S_GEO_CONFIGURED	9
#घोषणा S_EXIT_PENDING	10
#घोषणा S_STATS		12
#घोषणा S_SCANNING		13
#घोषणा S_SCAN_ABORTING	14
#घोषणा S_SCAN_HW		15
#घोषणा S_POWER_PMI	16
#घोषणा S_FW_ERROR		17
#घोषणा S_CHANNEL_SWITCH_PENDING 18

अटल अंतरभूत पूर्णांक
il_is_पढ़ोy(काष्ठा il_priv *il)
अणु
	/* The adapter is 'ready' अगर READY and GEO_CONFIGURED bits are
	 * set but EXIT_PENDING is not */
	वापस test_bit(S_READY, &il->status) &&
	    test_bit(S_GEO_CONFIGURED, &il->status) &&
	    !test_bit(S_EXIT_PENDING, &il->status);
पूर्ण

अटल अंतरभूत पूर्णांक
il_is_alive(काष्ठा il_priv *il)
अणु
	वापस test_bit(S_ALIVE, &il->status);
पूर्ण

अटल अंतरभूत पूर्णांक
il_is_init(काष्ठा il_priv *il)
अणु
	वापस test_bit(S_INIT, &il->status);
पूर्ण

अटल अंतरभूत पूर्णांक
il_is_rfसमाप्त(काष्ठा il_priv *il)
अणु
	वापस test_bit(S_RFKILL, &il->status);
पूर्ण

अटल अंतरभूत पूर्णांक
il_is_ctसमाप्त(काष्ठा il_priv *il)
अणु
	वापस test_bit(S_CT_KILL, &il->status);
पूर्ण

अटल अंतरभूत पूर्णांक
il_is_पढ़ोy_rf(काष्ठा il_priv *il)
अणु

	अगर (il_is_rfसमाप्त(il))
		वापस 0;

	वापस il_is_पढ़ोy(il);
पूर्ण

व्योम il_send_bt_config(काष्ठा il_priv *il);
पूर्णांक il_send_stats_request(काष्ठा il_priv *il, u8 flags, bool clear);
व्योम il_apm_stop(काष्ठा il_priv *il);
व्योम _il_apm_stop(काष्ठा il_priv *il);

पूर्णांक il_apm_init(काष्ठा il_priv *il);

पूर्णांक il_send_rxon_timing(काष्ठा il_priv *il);

अटल अंतरभूत पूर्णांक
il_send_rxon_assoc(काष्ठा il_priv *il)
अणु
	वापस il->ops->rxon_assoc(il);
पूर्ण

अटल अंतरभूत पूर्णांक
il_commit_rxon(काष्ठा il_priv *il)
अणु
	वापस il->ops->commit_rxon(il);
पूर्ण

अटल अंतरभूत स्थिर काष्ठा ieee80211_supported_band *
il_get_hw_mode(काष्ठा il_priv *il, क्रमागत nl80211_band band)
अणु
	वापस il->hw->wiphy->bands[band];
पूर्ण

/* mac80211 handlers */
पूर्णांक il_mac_config(काष्ठा ieee80211_hw *hw, u32 changed);
व्योम il_mac_reset_tsf(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर);
व्योम il_mac_bss_info_changed(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
			     काष्ठा ieee80211_bss_conf *bss_conf, u32 changes);
व्योम il_tx_cmd_protection(काष्ठा il_priv *il, काष्ठा ieee80211_tx_info *info,
			  __le16 fc, __le32 *tx_flags);

irqवापस_t il_isr(पूर्णांक irq, व्योम *data);

व्योम il_set_bit(काष्ठा il_priv *p, u32 r, u32 m);
व्योम il_clear_bit(काष्ठा il_priv *p, u32 r, u32 m);
bool _il_grab_nic_access(काष्ठा il_priv *il);
पूर्णांक _il_poll_bit(काष्ठा il_priv *il, u32 addr, u32 bits, u32 mask, पूर्णांक समयout);
पूर्णांक il_poll_bit(काष्ठा il_priv *il, u32 addr, u32 mask, पूर्णांक समयout);
u32 il_rd_prph(काष्ठा il_priv *il, u32 reg);
व्योम il_wr_prph(काष्ठा il_priv *il, u32 addr, u32 val);
u32 il_पढ़ो_targ_mem(काष्ठा il_priv *il, u32 addr);
व्योम il_ग_लिखो_targ_mem(काष्ठा il_priv *il, u32 addr, u32 val);

अटल अंतरभूत bool il_need_reclaim(काष्ठा il_priv *il, काष्ठा il_rx_pkt *pkt)
अणु
	/* Reclaim a command buffer only अगर this packet is a response
	 * to a (driver-originated) command. If the packet (e.g. Rx frame)
	 * originated from uCode, there is no command buffer to reclaim.
	 * Ucode should set SEQ_RX_FRAME bit अगर ucode-originated, but
	 * apparently a few करोn't get set; catch them here.
	 */
	वापस !(pkt->hdr.sequence & SEQ_RX_FRAME) &&
	       pkt->hdr.cmd != N_STATS && pkt->hdr.cmd != C_TX &&
	       pkt->hdr.cmd != N_RX_PHY && pkt->hdr.cmd != N_RX &&
	       pkt->hdr.cmd != N_RX_MPDU && pkt->hdr.cmd != N_COMPRESSED_BA;
पूर्ण

अटल अंतरभूत व्योम
_il_ग_लिखो8(काष्ठा il_priv *il, u32 ofs, u8 val)
अणु
	ग_लिखोb(val, il->hw_base + ofs);
पूर्ण
#घोषणा il_ग_लिखो8(il, ofs, val) _il_ग_लिखो8(il, ofs, val)

अटल अंतरभूत व्योम
_il_wr(काष्ठा il_priv *il, u32 ofs, u32 val)
अणु
	ग_लिखोl(val, il->hw_base + ofs);
पूर्ण

अटल अंतरभूत u32
_il_rd(काष्ठा il_priv *il, u32 ofs)
अणु
	वापस पढ़ोl(il->hw_base + ofs);
पूर्ण

अटल अंतरभूत व्योम
_il_clear_bit(काष्ठा il_priv *il, u32 reg, u32 mask)
अणु
	_il_wr(il, reg, _il_rd(il, reg) & ~mask);
पूर्ण

अटल अंतरभूत व्योम
_il_set_bit(काष्ठा il_priv *il, u32 reg, u32 mask)
अणु
	_il_wr(il, reg, _il_rd(il, reg) | mask);
पूर्ण

अटल अंतरभूत व्योम
_il_release_nic_access(काष्ठा il_priv *il)
अणु
	_il_clear_bit(il, CSR_GP_CNTRL, CSR_GP_CNTRL_REG_FLAG_MAC_ACCESS_REQ);
पूर्ण

अटल अंतरभूत u32
il_rd(काष्ठा il_priv *il, u32 reg)
अणु
	u32 value;
	अचिन्हित दीर्घ reg_flags;

	spin_lock_irqsave(&il->reg_lock, reg_flags);
	_il_grab_nic_access(il);
	value = _il_rd(il, reg);
	_il_release_nic_access(il);
	spin_unlock_irqrestore(&il->reg_lock, reg_flags);
	वापस value;
पूर्ण

अटल अंतरभूत व्योम
il_wr(काष्ठा il_priv *il, u32 reg, u32 value)
अणु
	अचिन्हित दीर्घ reg_flags;

	spin_lock_irqsave(&il->reg_lock, reg_flags);
	अगर (likely(_il_grab_nic_access(il))) अणु
		_il_wr(il, reg, value);
		_il_release_nic_access(il);
	पूर्ण
	spin_unlock_irqrestore(&il->reg_lock, reg_flags);
पूर्ण

अटल अंतरभूत u32
_il_rd_prph(काष्ठा il_priv *il, u32 reg)
अणु
	_il_wr(il, HBUS_TARG_PRPH_RADDR, reg | (3 << 24));
	वापस _il_rd(il, HBUS_TARG_PRPH_RDAT);
पूर्ण

अटल अंतरभूत व्योम
_il_wr_prph(काष्ठा il_priv *il, u32 addr, u32 val)
अणु
	_il_wr(il, HBUS_TARG_PRPH_WADDR, ((addr & 0x0000FFFF) | (3 << 24)));
	_il_wr(il, HBUS_TARG_PRPH_WDAT, val);
पूर्ण

अटल अंतरभूत व्योम
il_set_bits_prph(काष्ठा il_priv *il, u32 reg, u32 mask)
अणु
	अचिन्हित दीर्घ reg_flags;

	spin_lock_irqsave(&il->reg_lock, reg_flags);
	अगर (likely(_il_grab_nic_access(il))) अणु
		_il_wr_prph(il, reg, (_il_rd_prph(il, reg) | mask));
		_il_release_nic_access(il);
	पूर्ण
	spin_unlock_irqrestore(&il->reg_lock, reg_flags);
पूर्ण

अटल अंतरभूत व्योम
il_set_bits_mask_prph(काष्ठा il_priv *il, u32 reg, u32 bits, u32 mask)
अणु
	अचिन्हित दीर्घ reg_flags;

	spin_lock_irqsave(&il->reg_lock, reg_flags);
	अगर (likely(_il_grab_nic_access(il))) अणु
		_il_wr_prph(il, reg, ((_il_rd_prph(il, reg) & mask) | bits));
		_il_release_nic_access(il);
	पूर्ण
	spin_unlock_irqrestore(&il->reg_lock, reg_flags);
पूर्ण

अटल अंतरभूत व्योम
il_clear_bits_prph(काष्ठा il_priv *il, u32 reg, u32 mask)
अणु
	अचिन्हित दीर्घ reg_flags;
	u32 val;

	spin_lock_irqsave(&il->reg_lock, reg_flags);
	अगर (likely(_il_grab_nic_access(il))) अणु
		val = _il_rd_prph(il, reg);
		_il_wr_prph(il, reg, (val & ~mask));
		_il_release_nic_access(il);
	पूर्ण
	spin_unlock_irqrestore(&il->reg_lock, reg_flags);
पूर्ण

#घोषणा HW_KEY_DYNAMIC 0
#घोषणा HW_KEY_DEFAULT 1

#घोषणा IL_STA_DRIVER_ACTIVE BIT(0)	/* driver entry is active */
#घोषणा IL_STA_UCODE_ACTIVE  BIT(1)	/* ucode entry is active */
#घोषणा IL_STA_UCODE_INPROGRESS  BIT(2)	/* ucode entry is in process of
					   being activated */
#घोषणा IL_STA_LOCAL BIT(3)	/* station state not directed by mac80211;
				   (this is क्रम the IBSS BSSID stations) */
#घोषणा IL_STA_BCAST BIT(4)	/* this station is the special bcast station */

व्योम il_restore_stations(काष्ठा il_priv *il);
व्योम il_clear_ucode_stations(काष्ठा il_priv *il);
व्योम il_dealloc_bcast_stations(काष्ठा il_priv *il);
पूर्णांक il_get_मुक्त_ucode_key_idx(काष्ठा il_priv *il);
पूर्णांक il_send_add_sta(काष्ठा il_priv *il, काष्ठा il_addsta_cmd *sta, u8 flags);
पूर्णांक il_add_station_common(काष्ठा il_priv *il, स्थिर u8 *addr, bool is_ap,
			  काष्ठा ieee80211_sta *sta, u8 *sta_id_r);
पूर्णांक il_हटाओ_station(काष्ठा il_priv *il, स्थिर u8 sta_id, स्थिर u8 * addr);
पूर्णांक il_mac_sta_हटाओ(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
		      काष्ठा ieee80211_sta *sta);

u8 il_prep_station(काष्ठा il_priv *il, स्थिर u8 *addr, bool is_ap,
		   काष्ठा ieee80211_sta *sta);

पूर्णांक il_send_lq_cmd(काष्ठा il_priv *il, काष्ठा il_link_quality_cmd *lq,
		   u8 flags, bool init);

/**
 * il_clear_driver_stations - clear knowledge of all stations from driver
 * @il: iwl il काष्ठा
 *
 * This is called during il_करोwn() to make sure that in the हाल
 * we're coming there from a hardware restart mac80211 will be
 * able to reconfigure stations -- अगर we're getting there in the
 * normal करोwn flow then the stations will alपढ़ोy be cleared.
 */
अटल अंतरभूत व्योम
il_clear_driver_stations(काष्ठा il_priv *il)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&il->sta_lock, flags);
	स_रखो(il->stations, 0, माप(il->stations));
	il->num_stations = 0;
	il->ucode_key_table = 0;
	spin_unlock_irqrestore(&il->sta_lock, flags);
पूर्ण

अटल अंतरभूत पूर्णांक
il_sta_id(काष्ठा ieee80211_sta *sta)
अणु
	अगर (WARN_ON(!sta))
		वापस IL_INVALID_STATION;

	वापस ((काष्ठा il_station_priv_common *)sta->drv_priv)->sta_id;
पूर्ण

/**
 * il_sta_id_or_broadcast - वापस sta_id or broadcast sta
 * @il: iwl il
 * @context: the current context
 * @sta: mac80211 station
 *
 * In certain circumstances mac80211 passes a station poपूर्णांकer
 * that may be %शून्य, क्रम example during TX or key setup. In
 * that हाल, we need to use the broadcast station, so this
 * अंतरभूत wraps that pattern.
 */
अटल अंतरभूत पूर्णांक
il_sta_id_or_broadcast(काष्ठा il_priv *il, काष्ठा ieee80211_sta *sta)
अणु
	पूर्णांक sta_id;

	अगर (!sta)
		वापस il->hw_params.bcast_id;

	sta_id = il_sta_id(sta);

	/*
	 * mac80211 should not be passing a partially
	 * initialised station!
	 */
	WARN_ON(sta_id == IL_INVALID_STATION);

	वापस sta_id;
पूर्ण

/**
 * il_queue_inc_wrap - increment queue idx, wrap back to beginning
 * @idx -- current idx
 * @n_bd -- total number of entries in queue (must be घातer of 2)
 */
अटल अंतरभूत पूर्णांक
il_queue_inc_wrap(पूर्णांक idx, पूर्णांक n_bd)
अणु
	वापस ++idx & (n_bd - 1);
पूर्ण

/**
 * il_queue_dec_wrap - decrement queue idx, wrap back to end
 * @idx -- current idx
 * @n_bd -- total number of entries in queue (must be घातer of 2)
 */
अटल अंतरभूत पूर्णांक
il_queue_dec_wrap(पूर्णांक idx, पूर्णांक n_bd)
अणु
	वापस --idx & (n_bd - 1);
पूर्ण

/* TODO: Move fw_desc functions to iwl-pci.ko */
अटल अंतरभूत व्योम
il_मुक्त_fw_desc(काष्ठा pci_dev *pci_dev, काष्ठा fw_desc *desc)
अणु
	अगर (desc->v_addr)
		dma_मुक्त_coherent(&pci_dev->dev, desc->len, desc->v_addr,
				  desc->p_addr);
	desc->v_addr = शून्य;
	desc->len = 0;
पूर्ण

अटल अंतरभूत पूर्णांक
il_alloc_fw_desc(काष्ठा pci_dev *pci_dev, काष्ठा fw_desc *desc)
अणु
	अगर (!desc->len) अणु
		desc->v_addr = शून्य;
		वापस -EINVAL;
	पूर्ण

	desc->v_addr = dma_alloc_coherent(&pci_dev->dev, desc->len,
					  &desc->p_addr, GFP_KERNEL);
	वापस (desc->v_addr != शून्य) ? 0 : -ENOMEM;
पूर्ण

/*
 * we have 8 bits used like this:
 *
 * 7 6 5 4 3 2 1 0
 * | | | | | | | |
 * | | | | | | +-+-------- AC queue (0-3)
 * | | | | | |
 * | +-+-+-+-+------------ HW queue ID
 * |
 * +---------------------- unused
 */
अटल अंतरभूत व्योम
il_set_swq_id(काष्ठा il_tx_queue *txq, u8 ac, u8 hwq)
अणु
	BUG_ON(ac > 3);		/* only have 2 bits */
	BUG_ON(hwq > 31);	/* only use 5 bits */

	txq->swq_id = (hwq << 2) | ac;
पूर्ण

अटल अंतरभूत व्योम
_il_wake_queue(काष्ठा il_priv *il, u8 ac)
अणु
	अगर (atomic_dec_वापस(&il->queue_stop_count[ac]) <= 0)
		ieee80211_wake_queue(il->hw, ac);
पूर्ण

अटल अंतरभूत व्योम
_il_stop_queue(काष्ठा il_priv *il, u8 ac)
अणु
	अगर (atomic_inc_वापस(&il->queue_stop_count[ac]) > 0)
		ieee80211_stop_queue(il->hw, ac);
पूर्ण
अटल अंतरभूत व्योम
il_wake_queue(काष्ठा il_priv *il, काष्ठा il_tx_queue *txq)
अणु
	u8 queue = txq->swq_id;
	u8 ac = queue & 3;
	u8 hwq = (queue >> 2) & 0x1f;

	अगर (test_and_clear_bit(hwq, il->queue_stopped))
		_il_wake_queue(il, ac);
पूर्ण

अटल अंतरभूत व्योम
il_stop_queue(काष्ठा il_priv *il, काष्ठा il_tx_queue *txq)
अणु
	u8 queue = txq->swq_id;
	u8 ac = queue & 3;
	u8 hwq = (queue >> 2) & 0x1f;

	अगर (!test_and_set_bit(hwq, il->queue_stopped))
		_il_stop_queue(il, ac);
पूर्ण

अटल अंतरभूत व्योम
il_wake_queues_by_reason(काष्ठा il_priv *il, पूर्णांक reason)
अणु
	u8 ac;

	अगर (test_and_clear_bit(reason, &il->stop_reason))
		क्रम (ac = 0; ac < 4; ac++)
			_il_wake_queue(il, ac);
पूर्ण

अटल अंतरभूत व्योम
il_stop_queues_by_reason(काष्ठा il_priv *il, पूर्णांक reason)
अणु
	u8 ac;

	अगर (!test_and_set_bit(reason, &il->stop_reason))
		क्रम (ac = 0; ac < 4; ac++)
			_il_stop_queue(il, ac);
पूर्ण

#अगर_घोषित ieee80211_stop_queue
#अघोषित ieee80211_stop_queue
#पूर्ण_अगर

#घोषणा ieee80211_stop_queue DO_NOT_USE_ieee80211_stop_queue

#अगर_घोषित ieee80211_wake_queue
#अघोषित ieee80211_wake_queue
#पूर्ण_अगर

#घोषणा ieee80211_wake_queue DO_NOT_USE_ieee80211_wake_queue

अटल अंतरभूत व्योम
il_disable_पूर्णांकerrupts(काष्ठा il_priv *il)
अणु
	clear_bit(S_INT_ENABLED, &il->status);

	/* disable पूर्णांकerrupts from uCode/NIC to host */
	_il_wr(il, CSR_INT_MASK, 0x00000000);

	/* acknowledge/clear/reset any पूर्णांकerrupts still pending
	 * from uCode or flow handler (Rx/Tx DMA) */
	_il_wr(il, CSR_INT, 0xffffffff);
	_il_wr(il, CSR_FH_INT_STATUS, 0xffffffff);
पूर्ण

अटल अंतरभूत व्योम
il_enable_rfसमाप्त_पूर्णांक(काष्ठा il_priv *il)
अणु
	_il_wr(il, CSR_INT_MASK, CSR_INT_BIT_RF_KILL);
पूर्ण

अटल अंतरभूत व्योम
il_enable_पूर्णांकerrupts(काष्ठा il_priv *il)
अणु
	set_bit(S_INT_ENABLED, &il->status);
	_il_wr(il, CSR_INT_MASK, il->पूर्णांकa_mask);
पूर्ण

/**
 * il_beacon_समय_mask_low - mask of lower 32 bit of beacon समय
 * @il -- poपूर्णांकer to il_priv data काष्ठाure
 * @tsf_bits -- number of bits need to shअगरt क्रम masking)
 */
अटल अंतरभूत u32
il_beacon_समय_mask_low(काष्ठा il_priv *il, u16 tsf_bits)
अणु
	वापस (1 << tsf_bits) - 1;
पूर्ण

/**
 * il_beacon_समय_mask_high - mask of higher 32 bit of beacon समय
 * @il -- poपूर्णांकer to il_priv data काष्ठाure
 * @tsf_bits -- number of bits need to shअगरt क्रम masking)
 */
अटल अंतरभूत u32
il_beacon_समय_mask_high(काष्ठा il_priv *il, u16 tsf_bits)
अणु
	वापस ((1 << (32 - tsf_bits)) - 1) << tsf_bits;
पूर्ण

/**
 * काष्ठा il_rb_status - reseve buffer status host memory mapped FH रेजिस्टरs
 *
 * @बंदd_rb_num [0:11] - Indicates the idx of the RB which was बंदd
 * @बंदd_fr_num [0:11] - Indicates the idx of the RX Frame which was बंदd
 * @finished_rb_num [0:11] - Indicates the idx of the current RB
 *			     in which the last frame was written to
 * @finished_fr_num [0:11] - Indicates the idx of the RX Frame
 *			     which was transferred
 */
काष्ठा il_rb_status अणु
	__le16 बंदd_rb_num;
	__le16 बंदd_fr_num;
	__le16 finished_rb_num;
	__le16 finished_fr_nam;
	__le32 __unused;	/* 3945 only */
पूर्ण __packed;

#घोषणा TFD_QUEUE_SIZE_MAX      256
#घोषणा TFD_QUEUE_SIZE_BC_DUP	64
#घोषणा TFD_QUEUE_BC_SIZE	(TFD_QUEUE_SIZE_MAX + TFD_QUEUE_SIZE_BC_DUP)
#घोषणा IL_TX_DMA_MASK		DMA_BIT_MASK(36)
#घोषणा IL_NUM_OF_TBS		20

अटल अंतरभूत u8
il_get_dma_hi_addr(dma_addr_t addr)
अणु
	वापस (माप(addr) > माप(u32) ? (addr >> 16) >> 16 : 0) & 0xF;
पूर्ण

/**
 * काष्ठा il_tfd_tb transmit buffer descriptor within transmit frame descriptor
 *
 * This काष्ठाure contains dma address and length of transmission address
 *
 * @lo: low [31:0] portion of the dma address of TX buffer every even is
 *	unaligned on 16 bit boundary
 * @hi_n_len: 0-3 [35:32] portion of dma
 *	      4-15 length of the tx buffer
 */
काष्ठा il_tfd_tb अणु
	__le32 lo;
	__le16 hi_n_len;
पूर्ण __packed;

/**
 * काष्ठा il_tfd
 *
 * Transmit Frame Descriptor (TFD)
 *
 * @ __reserved1[3] reserved
 * @ num_tbs 0-4 number of active tbs
 *	     5   reserved
 * 	     6-7 padding (not used)
 * @ tbs[20]	transmit frame buffer descriptors
 * @ __pad	padding
 *
 * Each Tx queue uses a circular buffer of 256 TFDs stored in host DRAM.
 * Both driver and device share these circular buffers, each of which must be
 * contiguous 256 TFDs x 128 bytes-per-TFD = 32 KBytes
 *
 * Driver must indicate the physical address of the base of each
 * circular buffer via the FH49_MEM_CBBC_QUEUE रेजिस्टरs.
 *
 * Each TFD contains poपूर्णांकer/size inक्रमmation क्रम up to 20 data buffers
 * in host DRAM.  These buffers collectively contain the (one) frame described
 * by the TFD.  Each buffer must be a single contiguous block of memory within
 * itself, but buffers may be scattered in host DRAM.  Each buffer has max size
 * of (4K - 4).  The concatenates all of a TFD's buffers पूर्णांकo a single
 * Tx frame, up to 8 KBytes in size.
 *
 * A maximum of 255 (not 256!) TFDs may be on a queue रुकोing क्रम Tx.
 */
काष्ठा il_tfd अणु
	u8 __reserved1[3];
	u8 num_tbs;
	काष्ठा il_tfd_tb tbs[IL_NUM_OF_TBS];
	__le32 __pad;
पूर्ण __packed;
/* PCI रेजिस्टरs */
#घोषणा PCI_CFG_RETRY_TIMEOUT	0x041

काष्ठा il_rate_info अणु
	u8 plcp;		/* uCode API:  RATE_6M_PLCP, etc. */
	u8 plcp_siso;		/* uCode API:  RATE_SISO_6M_PLCP, etc. */
	u8 plcp_mimo2;		/* uCode API:  RATE_MIMO2_6M_PLCP, etc. */
	u8 ieee;		/* MAC header:  RATE_6M_IEEE, etc. */
	u8 prev_ieee;		/* previous rate in IEEE speeds */
	u8 next_ieee;		/* next rate in IEEE speeds */
	u8 prev_rs;		/* previous rate used in rs algo */
	u8 next_rs;		/* next rate used in rs algo */
	u8 prev_rs_tgg;		/* previous rate used in TGG rs algo */
	u8 next_rs_tgg;		/* next rate used in TGG rs algo */
पूर्ण;

काष्ठा il3945_rate_info अणु
	u8 plcp;		/* uCode API:  RATE_6M_PLCP, etc. */
	u8 ieee;		/* MAC header:  RATE_6M_IEEE, etc. */
	u8 prev_ieee;		/* previous rate in IEEE speeds */
	u8 next_ieee;		/* next rate in IEEE speeds */
	u8 prev_rs;		/* previous rate used in rs algo */
	u8 next_rs;		/* next rate used in rs algo */
	u8 prev_rs_tgg;		/* previous rate used in TGG rs algo */
	u8 next_rs_tgg;		/* next rate used in TGG rs algo */
	u8 table_rs_idx;	/* idx in rate scale table cmd */
	u8 prev_table_rs;	/* prev in rate table cmd */
पूर्ण;

/*
 * These serve as idxes पूर्णांकo
 * काष्ठा il_rate_info il_rates[RATE_COUNT];
 */
क्रमागत अणु
	RATE_1M_IDX = 0,
	RATE_2M_IDX,
	RATE_5M_IDX,
	RATE_11M_IDX,
	RATE_6M_IDX,
	RATE_9M_IDX,
	RATE_12M_IDX,
	RATE_18M_IDX,
	RATE_24M_IDX,
	RATE_36M_IDX,
	RATE_48M_IDX,
	RATE_54M_IDX,
	RATE_60M_IDX,
	RATE_COUNT,
	RATE_COUNT_LEGACY = RATE_COUNT - 1,	/* Excluding 60M */
	RATE_COUNT_3945 = RATE_COUNT - 1,
	RATE_INVM_IDX = RATE_COUNT,
	RATE_INVALID = RATE_COUNT,
पूर्ण;

क्रमागत अणु
	RATE_6M_IDX_TBL = 0,
	RATE_9M_IDX_TBL,
	RATE_12M_IDX_TBL,
	RATE_18M_IDX_TBL,
	RATE_24M_IDX_TBL,
	RATE_36M_IDX_TBL,
	RATE_48M_IDX_TBL,
	RATE_54M_IDX_TBL,
	RATE_1M_IDX_TBL,
	RATE_2M_IDX_TBL,
	RATE_5M_IDX_TBL,
	RATE_11M_IDX_TBL,
	RATE_INVM_IDX_TBL = RATE_INVM_IDX - 1,
पूर्ण;

क्रमागत अणु
	IL_FIRST_OFDM_RATE = RATE_6M_IDX,
	IL39_LAST_OFDM_RATE = RATE_54M_IDX,
	IL_LAST_OFDM_RATE = RATE_60M_IDX,
	IL_FIRST_CCK_RATE = RATE_1M_IDX,
	IL_LAST_CCK_RATE = RATE_11M_IDX,
पूर्ण;

/* #घोषणा vs. क्रमागत to keep from शेषing to 'large integer' */
#घोषणा	RATE_6M_MASK   (1 << RATE_6M_IDX)
#घोषणा	RATE_9M_MASK   (1 << RATE_9M_IDX)
#घोषणा	RATE_12M_MASK  (1 << RATE_12M_IDX)
#घोषणा	RATE_18M_MASK  (1 << RATE_18M_IDX)
#घोषणा	RATE_24M_MASK  (1 << RATE_24M_IDX)
#घोषणा	RATE_36M_MASK  (1 << RATE_36M_IDX)
#घोषणा	RATE_48M_MASK  (1 << RATE_48M_IDX)
#घोषणा	RATE_54M_MASK  (1 << RATE_54M_IDX)
#घोषणा RATE_60M_MASK  (1 << RATE_60M_IDX)
#घोषणा	RATE_1M_MASK   (1 << RATE_1M_IDX)
#घोषणा	RATE_2M_MASK   (1 << RATE_2M_IDX)
#घोषणा	RATE_5M_MASK   (1 << RATE_5M_IDX)
#घोषणा	RATE_11M_MASK  (1 << RATE_11M_IDX)

/* uCode API values क्रम legacy bit rates, both OFDM and CCK */
क्रमागत अणु
	RATE_6M_PLCP = 13,
	RATE_9M_PLCP = 15,
	RATE_12M_PLCP = 5,
	RATE_18M_PLCP = 7,
	RATE_24M_PLCP = 9,
	RATE_36M_PLCP = 11,
	RATE_48M_PLCP = 1,
	RATE_54M_PLCP = 3,
	RATE_60M_PLCP = 3,	/*FIXME:RS:should be हटाओd */
	RATE_1M_PLCP = 10,
	RATE_2M_PLCP = 20,
	RATE_5M_PLCP = 55,
	RATE_11M_PLCP = 110,
	/*FIXME:RS:add RATE_LEGACY_INVM_PLCP = 0, */
पूर्ण;

/* uCode API values क्रम OFDM high-throughput (HT) bit rates */
क्रमागत अणु
	RATE_SISO_6M_PLCP = 0,
	RATE_SISO_12M_PLCP = 1,
	RATE_SISO_18M_PLCP = 2,
	RATE_SISO_24M_PLCP = 3,
	RATE_SISO_36M_PLCP = 4,
	RATE_SISO_48M_PLCP = 5,
	RATE_SISO_54M_PLCP = 6,
	RATE_SISO_60M_PLCP = 7,
	RATE_MIMO2_6M_PLCP = 0x8,
	RATE_MIMO2_12M_PLCP = 0x9,
	RATE_MIMO2_18M_PLCP = 0xa,
	RATE_MIMO2_24M_PLCP = 0xb,
	RATE_MIMO2_36M_PLCP = 0xc,
	RATE_MIMO2_48M_PLCP = 0xd,
	RATE_MIMO2_54M_PLCP = 0xe,
	RATE_MIMO2_60M_PLCP = 0xf,
	RATE_SISO_INVM_PLCP,
	RATE_MIMO2_INVM_PLCP = RATE_SISO_INVM_PLCP,
पूर्ण;

/* MAC header values क्रम bit rates */
क्रमागत अणु
	RATE_6M_IEEE = 12,
	RATE_9M_IEEE = 18,
	RATE_12M_IEEE = 24,
	RATE_18M_IEEE = 36,
	RATE_24M_IEEE = 48,
	RATE_36M_IEEE = 72,
	RATE_48M_IEEE = 96,
	RATE_54M_IEEE = 108,
	RATE_60M_IEEE = 120,
	RATE_1M_IEEE = 2,
	RATE_2M_IEEE = 4,
	RATE_5M_IEEE = 11,
	RATE_11M_IEEE = 22,
पूर्ण;

#घोषणा IL_CCK_BASIC_RATES_MASK    \
	(RATE_1M_MASK          | \
	RATE_2M_MASK)

#घोषणा IL_CCK_RATES_MASK          \
	(IL_CCK_BASIC_RATES_MASK  | \
	RATE_5M_MASK          | \
	RATE_11M_MASK)

#घोषणा IL_OFDM_BASIC_RATES_MASK   \
	(RATE_6M_MASK         | \
	RATE_12M_MASK         | \
	RATE_24M_MASK)

#घोषणा IL_OFDM_RATES_MASK         \
	(IL_OFDM_BASIC_RATES_MASK | \
	RATE_9M_MASK          | \
	RATE_18M_MASK         | \
	RATE_36M_MASK         | \
	RATE_48M_MASK         | \
	RATE_54M_MASK)

#घोषणा IL_BASIC_RATES_MASK         \
	(IL_OFDM_BASIC_RATES_MASK | \
	 IL_CCK_BASIC_RATES_MASK)

#घोषणा RATES_MASK ((1 << RATE_COUNT) - 1)
#घोषणा RATES_MASK_3945 ((1 << RATE_COUNT_3945) - 1)

#घोषणा IL_INVALID_VALUE    -1

#घोषणा IL_MIN_RSSI_VAL                 -100
#घोषणा IL_MAX_RSSI_VAL                    0

/* These values specअगरy how many Tx frame attempts beक्रमe
 * searching क्रम a new modulation mode */
#घोषणा IL_LEGACY_FAILURE_LIMIT	160
#घोषणा IL_LEGACY_SUCCESS_LIMIT	480
#घोषणा IL_LEGACY_TBL_COUNT		160

#घोषणा IL_NONE_LEGACY_FAILURE_LIMIT	400
#घोषणा IL_NONE_LEGACY_SUCCESS_LIMIT	4500
#घोषणा IL_NONE_LEGACY_TBL_COUNT	1500

/* Success ratio (ACKed / attempted tx frames) values (perfect is 128 * 100) */
#घोषणा IL_RS_GOOD_RATIO		12800	/* 100% */
#घोषणा RATE_SCALE_SWITCH		10880	/*  85% */
#घोषणा RATE_HIGH_TH		10880	/*  85% */
#घोषणा RATE_INCREASE_TH		6400	/*  50% */
#घोषणा RATE_DECREASE_TH		1920	/*  15% */

/* possible actions when in legacy mode */
#घोषणा IL_LEGACY_SWITCH_ANTENNA1      0
#घोषणा IL_LEGACY_SWITCH_ANTENNA2      1
#घोषणा IL_LEGACY_SWITCH_SISO          2
#घोषणा IL_LEGACY_SWITCH_MIMO2_AB      3
#घोषणा IL_LEGACY_SWITCH_MIMO2_AC      4
#घोषणा IL_LEGACY_SWITCH_MIMO2_BC      5

/* possible actions when in siso mode */
#घोषणा IL_SISO_SWITCH_ANTENNA1        0
#घोषणा IL_SISO_SWITCH_ANTENNA2        1
#घोषणा IL_SISO_SWITCH_MIMO2_AB        2
#घोषणा IL_SISO_SWITCH_MIMO2_AC        3
#घोषणा IL_SISO_SWITCH_MIMO2_BC        4
#घोषणा IL_SISO_SWITCH_GI              5

/* possible actions when in mimo mode */
#घोषणा IL_MIMO2_SWITCH_ANTENNA1       0
#घोषणा IL_MIMO2_SWITCH_ANTENNA2       1
#घोषणा IL_MIMO2_SWITCH_SISO_A         2
#घोषणा IL_MIMO2_SWITCH_SISO_B         3
#घोषणा IL_MIMO2_SWITCH_SISO_C         4
#घोषणा IL_MIMO2_SWITCH_GI             5

#घोषणा IL_MAX_SEARCH IL_MIMO2_SWITCH_GI

#घोषणा IL_ACTION_LIMIT		3	/* # possible actions */

#घोषणा LQ_SIZE		2	/* 2 mode tables:  "Active" and "Search" */

/* load per tid defines क्रम A-MPDU activation */
#घोषणा IL_AGG_TPT_THREHOLD	0
#घोषणा IL_AGG_LOAD_THRESHOLD	10
#घोषणा IL_AGG_ALL_TID		0xff
#घोषणा TID_QUEUE_CELL_SPACING	50	/*mS */
#घोषणा TID_QUEUE_MAX_SIZE	20
#घोषणा TID_ROUND_VALUE		5	/* mS */
#घोषणा TID_MAX_LOAD_COUNT	8

#घोषणा TID_MAX_TIME_DIFF ((TID_QUEUE_MAX_SIZE - 1) * TID_QUEUE_CELL_SPACING)
#घोषणा TIME_WRAP_AROUND(x, y) (((y) > (x)) ? (y) - (x) : (0-(x)) + (y))

बाह्य स्थिर काष्ठा il_rate_info il_rates[RATE_COUNT];

क्रमागत il_table_type अणु
	LQ_NONE,
	LQ_G,			/* legacy types */
	LQ_A,
	LQ_SISO,		/* high-throughput types */
	LQ_MIMO2,
	LQ_MAX,
पूर्ण;

#घोषणा is_legacy(tbl) ((tbl) == LQ_G || (tbl) == LQ_A)
#घोषणा is_siso(tbl) ((tbl) == LQ_SISO)
#घोषणा is_mimo2(tbl) ((tbl) == LQ_MIMO2)
#घोषणा is_mimo(tbl) (is_mimo2(tbl))
#घोषणा is_Ht(tbl) (is_siso(tbl) || is_mimo(tbl))
#घोषणा is_a_band(tbl) ((tbl) == LQ_A)
#घोषणा is_g_and(tbl) ((tbl) == LQ_G)

#घोषणा	ANT_NONE	0x0
#घोषणा	ANT_A		BIT(0)
#घोषणा	ANT_B		BIT(1)
#घोषणा	ANT_AB		(ANT_A | ANT_B)
#घोषणा ANT_C		BIT(2)
#घोषणा	ANT_AC		(ANT_A | ANT_C)
#घोषणा ANT_BC		(ANT_B | ANT_C)
#घोषणा ANT_ABC		(ANT_AB | ANT_C)

#घोषणा IL_MAX_MCS_DISPLAY_SIZE	12

काष्ठा il_rate_mcs_info अणु
	अक्षर mbps[IL_MAX_MCS_DISPLAY_SIZE];
	अक्षर mcs[IL_MAX_MCS_DISPLAY_SIZE];
पूर्ण;

/**
 * काष्ठा il_rate_scale_data -- tx success history क्रम one rate
 */
काष्ठा il_rate_scale_data अणु
	u64 data;		/* biपंचांगap of successful frames */
	s32 success_counter;	/* number of frames successful */
	s32 success_ratio;	/* per-cent * 128  */
	s32 counter;		/* number of frames attempted */
	s32 average_tpt;	/* success ratio * expected throughput */
	अचिन्हित दीर्घ stamp;
पूर्ण;

/**
 * काष्ठा il_scale_tbl_info -- tx params and success history क्रम all rates
 *
 * There are two of these in काष्ठा il_lq_sta,
 * one क्रम "active", and one क्रम "search".
 */
काष्ठा il_scale_tbl_info अणु
	क्रमागत il_table_type lq_type;
	u8 ant_type;
	u8 is_SGI;		/* 1 = लघु guard पूर्णांकerval */
	u8 is_ht40;		/* 1 = 40 MHz channel width */
	u8 is_dup;		/* 1 = duplicated data streams */
	u8 action;		/* change modulation; IL_[LEGACY/SISO/MIMO]_SWITCH_* */
	u8 max_search;		/* maximun number of tables we can search */
	s32 *expected_tpt;	/* throughput metrics; expected_tpt_G, etc. */
	u32 current_rate;	/* rate_n_flags, uCode API क्रमmat */
	काष्ठा il_rate_scale_data win[RATE_COUNT];	/* rate histories */
पूर्ण;

काष्ठा il_traffic_load अणु
	अचिन्हित दीर्घ समय_stamp;	/* age of the oldest stats */
	u32 packet_count[TID_QUEUE_MAX_SIZE];	/* packet count in this समय
						 * slice */
	u32 total;		/* total num of packets during the
				 * last TID_MAX_TIME_DIFF */
	u8 queue_count;		/* number of queues that has
				 * been used since the last cleanup */
	u8 head;		/* start of the circular buffer */
पूर्ण;

/**
 * काष्ठा il_lq_sta -- driver's rate scaling ilate काष्ठाure
 *
 * Poपूर्णांकer to this माला_लो passed back and क्रमth between driver and mac80211.
 */
काष्ठा il_lq_sta अणु
	u8 active_tbl;		/* idx of active table, range 0-1 */
	u8 enable_counter;	/* indicates HT mode */
	u8 stay_in_tbl;		/* 1: disallow, 0: allow search क्रम new mode */
	u8 search_better_tbl;	/* 1: currently trying alternate mode */
	s32 last_tpt;

	/* The following determine when to search क्रम a new mode */
	u32 table_count_limit;
	u32 max_failure_limit;	/* # failed frames beक्रमe new search */
	u32 max_success_limit;	/* # successful frames beक्रमe new search */
	u32 table_count;
	u32 total_failed;	/* total failed frames, any/all rates */
	u32 total_success;	/* total successful frames, any/all rates */
	u64 flush_समयr;	/* समय staying in mode beक्रमe new search */

	u8 action_counter;	/* # mode-चयन actions tried */
	u8 is_green;
	u8 is_dup;
	क्रमागत nl80211_band band;

	/* The following are biपंचांगaps of rates; RATE_6M_MASK, etc. */
	u32 supp_rates;
	u16 active_legacy_rate;
	u16 active_siso_rate;
	u16 active_mimo2_rate;
	s8 max_rate_idx;	/* Max rate set by user */
	u8 missed_rate_counter;

	काष्ठा il_link_quality_cmd lq;
	काष्ठा il_scale_tbl_info lq_info[LQ_SIZE];	/* "active", "search" */
	काष्ठा il_traffic_load load[TID_MAX_LOAD_COUNT];
	u8 tx_agg_tid_en;
#अगर_घोषित CONFIG_MAC80211_DEBUGFS
	u32 dbg_fixed_rate;
#पूर्ण_अगर
	काष्ठा il_priv *drv;

	/* used to be in sta_info */
	पूर्णांक last_txrate_idx;
	/* last tx rate_n_flags */
	u32 last_rate_n_flags;
	/* packets destined क्रम this STA are aggregated */
	u8 is_agg;
पूर्ण;

/*
 * il_station_priv: Driver's ilate station inक्रमmation
 *
 * When mac80211 creates a station it reserves some space (hw->sta_data_size)
 * in the काष्ठाure क्रम use by driver. This काष्ठाure is places in that
 * space.
 *
 * The common काष्ठा MUST be first because it is shared between
 * 3945 and 4965!
 */
काष्ठा il_station_priv अणु
	काष्ठा il_station_priv_common common;
	काष्ठा il_lq_sta lq_sta;
	atomic_t pending_frames;
	bool client;
	bool asleep;
पूर्ण;

अटल अंतरभूत u8
il4965_num_of_ant(u8 m)
अणु
	वापस !!(m & ANT_A) + !!(m & ANT_B) + !!(m & ANT_C);
पूर्ण

अटल अंतरभूत u8
il4965_first_antenna(u8 mask)
अणु
	अगर (mask & ANT_A)
		वापस ANT_A;
	अगर (mask & ANT_B)
		वापस ANT_B;
	वापस ANT_C;
पूर्ण

/**
 * il3945_rate_scale_init - Initialize the rate scale table based on assoc info
 *
 * The specअगरic throughput table used is based on the type of network
 * the associated with, including A, B, G, and G w/ TGG protection
 */
व्योम il3945_rate_scale_init(काष्ठा ieee80211_hw *hw, s32 sta_id);

/* Initialize station's rate scaling inक्रमmation after adding station */
व्योम il4965_rs_rate_init(काष्ठा il_priv *il, काष्ठा ieee80211_sta *sta,
			 u8 sta_id);
व्योम il3945_rs_rate_init(काष्ठा il_priv *il, काष्ठा ieee80211_sta *sta,
			 u8 sta_id);

/**
 * il_rate_control_रेजिस्टर - Register the rate control algorithm callbacks
 *
 * Since the rate control algorithm is hardware specअगरic, there is no need
 * or reason to place it as a stand alone module.  The driver can call
 * il_rate_control_रेजिस्टर in order to रेजिस्टर the rate control callbacks
 * with the mac80211 subप्रणाली.  This should be perक्रमmed prior to calling
 * ieee80211_रेजिस्टर_hw
 *
 */
पूर्णांक il4965_rate_control_रेजिस्टर(व्योम);
पूर्णांक il3945_rate_control_रेजिस्टर(व्योम);

/**
 * il_rate_control_unरेजिस्टर - Unरेजिस्टर the rate control callbacks
 *
 * This should be called after calling ieee80211_unरेजिस्टर_hw, but beक्रमe
 * the driver is unloaded.
 */
व्योम il4965_rate_control_unरेजिस्टर(व्योम);
व्योम il3945_rate_control_unरेजिस्टर(व्योम);

पूर्णांक il_घातer_update_mode(काष्ठा il_priv *il, bool क्रमce);
व्योम il_घातer_initialize(काष्ठा il_priv *il);

बाह्य u32 il_debug_level;

#अगर_घोषित CONFIG_IWLEGACY_DEBUG
/*
 * il_get_debug_level: Return active debug level क्रम device
 *
 * Using sysfs it is possible to set per device debug level. This debug
 * level will be used अगर set, otherwise the global debug level which can be
 * set via module parameter is used.
 */
अटल अंतरभूत u32
il_get_debug_level(काष्ठा il_priv *il)
अणु
	अगर (il->debug_level)
		वापस il->debug_level;
	अन्यथा
		वापस il_debug_level;
पूर्ण
#अन्यथा
अटल अंतरभूत u32
il_get_debug_level(काष्ठा il_priv *il)
अणु
	वापस il_debug_level;
पूर्ण
#पूर्ण_अगर

#घोषणा il_prपूर्णांक_hex_error(il, p, len)					\
करो अणु									\
	prपूर्णांक_hex_dump(KERN_ERR, "iwl data: ",				\
		       DUMP_PREFIX_OFFSET, 16, 1, p, len, 1);		\
पूर्ण जबतक (0)

#अगर_घोषित CONFIG_IWLEGACY_DEBUG
#घोषणा IL_DBG(level, fmt, args...)					\
करो अणु									\
	अगर (il_get_debug_level(il) & level)				\
		dev_err(&il->hw->wiphy->dev, "%s " fmt, __func__,	\
			 ##args);					\
पूर्ण जबतक (0)

#घोषणा il_prपूर्णांक_hex_dump(il, level, p, len)				\
करो अणु									\
	अगर (il_get_debug_level(il) & level)				\
		prपूर्णांक_hex_dump(KERN_DEBUG, "iwl data: ",		\
			       DUMP_PREFIX_OFFSET, 16, 1, p, len, 1);	\
पूर्ण जबतक (0)

#अन्यथा
#घोषणा IL_DBG(level, fmt, args...) no_prपूर्णांकk(fmt, ##args)
अटल अंतरभूत व्योम
il_prपूर्णांक_hex_dump(काष्ठा il_priv *il, पूर्णांक level, स्थिर व्योम *p, u32 len)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_IWLEGACY_DEBUG */

#अगर_घोषित CONFIG_IWLEGACY_DEBUGFS
व्योम il_dbgfs_रेजिस्टर(काष्ठा il_priv *il, स्थिर अक्षर *name);
व्योम il_dbgfs_unरेजिस्टर(काष्ठा il_priv *il);
#अन्यथा
अटल अंतरभूत व्योम il_dbgfs_रेजिस्टर(काष्ठा il_priv *il, स्थिर अक्षर *name)
अणु
पूर्ण

अटल अंतरभूत व्योम
il_dbgfs_unरेजिस्टर(काष्ठा il_priv *il)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_IWLEGACY_DEBUGFS */

/*
 * To use the debug प्रणाली:
 *
 * If you are defining a new debug classअगरication, simply add it to the #घोषणा
 * list here in the क्रमm of
 *
 * #घोषणा IL_DL_xxxx VALUE
 *
 * where xxxx should be the name of the classअगरication (क्रम example, WEP).
 *
 * You then need to either add a IL_xxxx_DEBUG() macro definition क्रम your
 * classअगरication, or use IL_DBG(IL_DL_xxxx, ...) whenever you want
 * to send output to that classअगरication.
 *
 * The active debug levels can be accessed via files
 *
 *	/sys/module/iwl4965/parameters/debug
 *	/sys/module/iwl3945/parameters/debug
 *	/sys/class/net/wlan0/device/debug_level
 *
 * when CONFIG_IWLEGACY_DEBUG=y.
 */

/* 0x0000000F - 0x00000001 */
#घोषणा IL_DL_INFO		(1 << 0)
#घोषणा IL_DL_MAC80211		(1 << 1)
#घोषणा IL_DL_HCMD		(1 << 2)
#घोषणा IL_DL_STATE		(1 << 3)
/* 0x000000F0 - 0x00000010 */
#घोषणा IL_DL_MACDUMP		(1 << 4)
#घोषणा IL_DL_HCMD_DUMP		(1 << 5)
#घोषणा IL_DL_EEPROM		(1 << 6)
#घोषणा IL_DL_RADIO		(1 << 7)
/* 0x00000F00 - 0x00000100 */
#घोषणा IL_DL_POWER		(1 << 8)
#घोषणा IL_DL_TEMP		(1 << 9)
#घोषणा IL_DL_NOTIF		(1 << 10)
#घोषणा IL_DL_SCAN		(1 << 11)
/* 0x0000F000 - 0x00001000 */
#घोषणा IL_DL_ASSOC		(1 << 12)
#घोषणा IL_DL_DROP		(1 << 13)
#घोषणा IL_DL_TXPOWER		(1 << 14)
#घोषणा IL_DL_AP		(1 << 15)
/* 0x000F0000 - 0x00010000 */
#घोषणा IL_DL_FW		(1 << 16)
#घोषणा IL_DL_RF_KILL		(1 << 17)
#घोषणा IL_DL_FW_ERRORS		(1 << 18)
#घोषणा IL_DL_LED		(1 << 19)
/* 0x00F00000 - 0x00100000 */
#घोषणा IL_DL_RATE		(1 << 20)
#घोषणा IL_DL_CALIB		(1 << 21)
#घोषणा IL_DL_WEP		(1 << 22)
#घोषणा IL_DL_TX		(1 << 23)
/* 0x0F000000 - 0x01000000 */
#घोषणा IL_DL_RX		(1 << 24)
#घोषणा IL_DL_ISR		(1 << 25)
#घोषणा IL_DL_HT		(1 << 26)
/* 0xF0000000 - 0x10000000 */
#घोषणा IL_DL_11H		(1 << 28)
#घोषणा IL_DL_STATS		(1 << 29)
#घोषणा IL_DL_TX_REPLY		(1 << 30)
#घोषणा IL_DL_QOS		(1 << 31)

#घोषणा D_INFO(f, a...)		IL_DBG(IL_DL_INFO, f, ## a)
#घोषणा D_MAC80211(f, a...)	IL_DBG(IL_DL_MAC80211, f, ## a)
#घोषणा D_MACDUMP(f, a...)	IL_DBG(IL_DL_MACDUMP, f, ## a)
#घोषणा D_TEMP(f, a...)		IL_DBG(IL_DL_TEMP, f, ## a)
#घोषणा D_SCAN(f, a...)		IL_DBG(IL_DL_SCAN, f, ## a)
#घोषणा D_RX(f, a...)		IL_DBG(IL_DL_RX, f, ## a)
#घोषणा D_TX(f, a...)		IL_DBG(IL_DL_TX, f, ## a)
#घोषणा D_ISR(f, a...)		IL_DBG(IL_DL_ISR, f, ## a)
#घोषणा D_LED(f, a...)		IL_DBG(IL_DL_LED, f, ## a)
#घोषणा D_WEP(f, a...)		IL_DBG(IL_DL_WEP, f, ## a)
#घोषणा D_HC(f, a...)		IL_DBG(IL_DL_HCMD, f, ## a)
#घोषणा D_HC_DUMP(f, a...)	IL_DBG(IL_DL_HCMD_DUMP, f, ## a)
#घोषणा D_EEPROM(f, a...)	IL_DBG(IL_DL_EEPROM, f, ## a)
#घोषणा D_CALIB(f, a...)	IL_DBG(IL_DL_CALIB, f, ## a)
#घोषणा D_FW(f, a...)		IL_DBG(IL_DL_FW, f, ## a)
#घोषणा D_RF_KILL(f, a...)	IL_DBG(IL_DL_RF_KILL, f, ## a)
#घोषणा D_DROP(f, a...)		IL_DBG(IL_DL_DROP, f, ## a)
#घोषणा D_AP(f, a...)		IL_DBG(IL_DL_AP, f, ## a)
#घोषणा D_TXPOWER(f, a...)	IL_DBG(IL_DL_TXPOWER, f, ## a)
#घोषणा D_RATE(f, a...)		IL_DBG(IL_DL_RATE, f, ## a)
#घोषणा D_NOTIF(f, a...)	IL_DBG(IL_DL_NOTIF, f, ## a)
#घोषणा D_ASSOC(f, a...)	IL_DBG(IL_DL_ASSOC, f, ## a)
#घोषणा D_HT(f, a...)		IL_DBG(IL_DL_HT, f, ## a)
#घोषणा D_STATS(f, a...)	IL_DBG(IL_DL_STATS, f, ## a)
#घोषणा D_TX_REPLY(f, a...)	IL_DBG(IL_DL_TX_REPLY, f, ## a)
#घोषणा D_QOS(f, a...)		IL_DBG(IL_DL_QOS, f, ## a)
#घोषणा D_RADIO(f, a...)	IL_DBG(IL_DL_RADIO, f, ## a)
#घोषणा D_POWER(f, a...)	IL_DBG(IL_DL_POWER, f, ## a)
#घोषणा D_11H(f, a...)		IL_DBG(IL_DL_11H, f, ## a)

#पूर्ण_अगर /* __il_core_h__ */
