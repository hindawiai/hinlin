<शैली गुरु>
/*
 * Copyright (c) 2004-2007 Reyk Floeter <reyk@खोलोbsd.org>
 * Copyright (c) 2006-2007 Nick Kossअगरidis <mickflemm@gmail.com>
 *
 * Permission to use, copy, modअगरy, and distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#अगर_अघोषित _ATH5K_H
#घोषणा _ATH5K_H

/* TODO: Clean up channel debugging (करोesn't work anyway) and start
 * working on reg. control code using all available eeprom inक्रमmation
 * (rev. engineering needed) */
#घोषणा CHAN_DEBUG	0

#समावेश <linux/पन.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/types.h>
#समावेश <linux/average.h>
#समावेश <linux/leds.h>
#समावेश <net/mac80211.h>
#समावेश <net/cfg80211.h>

/* RX/TX descriptor hw काष्ठाs
 * TODO: Driver part should only see sw काष्ठाs */
#समावेश "desc.h"

/* EEPROM काष्ठाs/offsets
 * TODO: Make a more generic काष्ठा (eg. add more stuff to ath5k_capabilities)
 * and clean up common bits, then पूर्णांकroduce set/get functions in eeprom.c */
#समावेश "eeprom.h"
#समावेश "debug.h"
#समावेश "../ath.h"
#समावेश "ani.h"

/* PCI IDs */
#घोषणा PCI_DEVICE_ID_ATHEROS_AR5210		0x0007 /* AR5210 */
#घोषणा PCI_DEVICE_ID_ATHEROS_AR5311		0x0011 /* AR5311 */
#घोषणा PCI_DEVICE_ID_ATHEROS_AR5211		0x0012 /* AR5211 */
#घोषणा PCI_DEVICE_ID_ATHEROS_AR5212		0x0013 /* AR5212 */
#घोषणा PCI_DEVICE_ID_3COM_3CRDAG675		0x0013 /* 3CRDAG675 (Atheros AR5212) */
#घोषणा PCI_DEVICE_ID_3COM_2_3CRPAG175		0x0013 /* 3CRPAG175 (Atheros AR5212) */
#घोषणा PCI_DEVICE_ID_ATHEROS_AR5210_AP		0x0207 /* AR5210 (Early) */
#घोषणा PCI_DEVICE_ID_ATHEROS_AR5212_IBM	0x1014 /* AR5212 (IBM MiniPCI) */
#घोषणा PCI_DEVICE_ID_ATHEROS_AR5210_DEFAULT	0x1107 /* AR5210 (no eeprom) */
#घोषणा PCI_DEVICE_ID_ATHEROS_AR5212_DEFAULT	0x1113 /* AR5212 (no eeprom) */
#घोषणा PCI_DEVICE_ID_ATHEROS_AR5211_DEFAULT	0x1112 /* AR5211 (no eeprom) */
#घोषणा PCI_DEVICE_ID_ATHEROS_AR5212_FPGA	0xf013 /* AR5212 (emulation board) */
#घोषणा PCI_DEVICE_ID_ATHEROS_AR5211_LEGACY	0xff12 /* AR5211 (emulation board) */
#घोषणा PCI_DEVICE_ID_ATHEROS_AR5211_FPGA11B	0xf11b /* AR5211 (emulation board) */
#घोषणा PCI_DEVICE_ID_ATHEROS_AR5312_REV2	0x0052 /* AR5312 WMAC (AP31) */
#घोषणा PCI_DEVICE_ID_ATHEROS_AR5312_REV7	0x0057 /* AR5312 WMAC (AP30-040) */
#घोषणा PCI_DEVICE_ID_ATHEROS_AR5312_REV8	0x0058 /* AR5312 WMAC (AP43-030) */
#घोषणा PCI_DEVICE_ID_ATHEROS_AR5212_0014	0x0014 /* AR5212 compatible */
#घोषणा PCI_DEVICE_ID_ATHEROS_AR5212_0015	0x0015 /* AR5212 compatible */
#घोषणा PCI_DEVICE_ID_ATHEROS_AR5212_0016	0x0016 /* AR5212 compatible */
#घोषणा PCI_DEVICE_ID_ATHEROS_AR5212_0017	0x0017 /* AR5212 compatible */
#घोषणा PCI_DEVICE_ID_ATHEROS_AR5212_0018	0x0018 /* AR5212 compatible */
#घोषणा PCI_DEVICE_ID_ATHEROS_AR5212_0019	0x0019 /* AR5212 compatible */
#घोषणा PCI_DEVICE_ID_ATHEROS_AR2413		0x001a /* AR2413 (Grअगरfin-lite) */
#घोषणा PCI_DEVICE_ID_ATHEROS_AR5413		0x001b /* AR5413 (Eagle) */
#घोषणा PCI_DEVICE_ID_ATHEROS_AR5424		0x001c /* AR5424 (Conकरोr PCI-E) */
#घोषणा PCI_DEVICE_ID_ATHEROS_AR5416		0x0023 /* AR5416 */
#घोषणा PCI_DEVICE_ID_ATHEROS_AR5418		0x0024 /* AR5418 */

/****************************\
  GENERIC DRIVER DEFINITIONS
\****************************/

#घोषणा ATH5K_PRINTF(fmt, ...)						\
	pr_warn("%s: " fmt, __func__, ##__VA_ARGS__)

व्योम __म_लिखो(3, 4)
_ath5k_prपूर्णांकk(स्थिर काष्ठा ath5k_hw *ah, स्थिर अक्षर *level,
	      स्थिर अक्षर *fmt, ...);

#घोषणा ATH5K_PRINTK(_sc, _level, _fmt, ...)				\
	_ath5k_prपूर्णांकk(_sc, _level, _fmt, ##__VA_ARGS__)

#घोषणा ATH5K_PRINTK_LIMIT(_sc, _level, _fmt, ...)			\
करो अणु									\
	अगर (net_ratelimit())						\
		ATH5K_PRINTK(_sc, _level, _fmt, ##__VA_ARGS__); 	\
पूर्ण जबतक (0)

#घोषणा ATH5K_INFO(_sc, _fmt, ...)					\
	ATH5K_PRINTK(_sc, KERN_INFO, _fmt, ##__VA_ARGS__)

#घोषणा ATH5K_WARN(_sc, _fmt, ...)					\
	ATH5K_PRINTK_LIMIT(_sc, KERN_WARNING, _fmt, ##__VA_ARGS__)

#घोषणा ATH5K_ERR(_sc, _fmt, ...)					\
	ATH5K_PRINTK_LIMIT(_sc, KERN_ERR, _fmt, ##__VA_ARGS__)

/*
 * AR5K REGISTER ACCESS
 */

/* Some macros to पढ़ो/ग_लिखो fields */

/* First shअगरt, then mask */
#घोषणा AR5K_REG_SM(_val, _flags)					\
	(((_val) << _flags##_S) & (_flags))

/* First mask, then shअगरt */
#घोषणा AR5K_REG_MS(_val, _flags)					\
	(((_val) & (_flags)) >> _flags##_S)

/* Some रेजिस्टरs can hold multiple values of पूर्णांकerest. For this
 * reason when we want to ग_लिखो to these रेजिस्टरs we must first
 * retrieve the values which we करो not want to clear (lets call this
 * old_data) and then set the रेजिस्टर with this and our new_value:
 * ( old_data | new_value) */
#घोषणा AR5K_REG_WRITE_BITS(ah, _reg, _flags, _val)			\
	ath5k_hw_reg_ग_लिखो(ah, (ath5k_hw_reg_पढ़ो(ah, _reg) & ~(_flags)) | \
	    (((_val) << _flags##_S) & (_flags)), _reg)

#घोषणा AR5K_REG_MASKED_BITS(ah, _reg, _flags, _mask)			\
	ath5k_hw_reg_ग_लिखो(ah, (ath5k_hw_reg_पढ़ो(ah, _reg) &		\
			(_mask)) | (_flags), _reg)

#घोषणा AR5K_REG_ENABLE_BITS(ah, _reg, _flags)				\
	ath5k_hw_reg_ग_लिखो(ah, ath5k_hw_reg_पढ़ो(ah, _reg) | (_flags), _reg)

#घोषणा AR5K_REG_DISABLE_BITS(ah, _reg, _flags)			\
	ath5k_hw_reg_ग_लिखो(ah, ath5k_hw_reg_पढ़ो(ah, _reg) & ~(_flags), _reg)

/* Access QCU रेजिस्टरs per queue */
#घोषणा AR5K_REG_READ_Q(ah, _reg, _queue)				\
	(ath5k_hw_reg_पढ़ो(ah, _reg) & (1 << _queue))			\

#घोषणा AR5K_REG_WRITE_Q(ah, _reg, _queue)				\
	ath5k_hw_reg_ग_लिखो(ah, (1 << _queue), _reg)

#घोषणा AR5K_Q_ENABLE_BITS(_reg, _queue) करो अणु				\
	_reg |= 1 << _queue;						\
पूर्ण जबतक (0)

#घोषणा AR5K_Q_DISABLE_BITS(_reg, _queue) करो अणु				\
	_reg &= ~(1 << _queue);						\
पूर्ण जबतक (0)

/* Used जबतक writing initvals */
#घोषणा AR5K_REG_WAIT(_i) करो अणु						\
	अगर (_i % 64)							\
		udelay(1);						\
पूर्ण जबतक (0)

/*
 * Some tunable values (these should be changeable by the user)
 * TODO: Make use of them and add more options OR use debug/configfs
 */
#घोषणा AR5K_TUNE_DMA_BEACON_RESP		2
#घोषणा AR5K_TUNE_SW_BEACON_RESP		10
#घोषणा AR5K_TUNE_ADDITIONAL_SWBA_BACKOFF	0
#घोषणा AR5K_TUNE_MIN_TX_FIFO_THRES		1
#घोषणा AR5K_TUNE_MAX_TX_FIFO_THRES	((IEEE80211_MAX_FRAME_LEN / 64) + 1)
#घोषणा AR5K_TUNE_REGISTER_TIMEOUT		20000
/* Register क्रम RSSI threshold has a mask of 0xff, so 255 seems to
 * be the max value. */
#घोषणा AR5K_TUNE_RSSI_THRES			129
/* This must be set when setting the RSSI threshold otherwise it can
 * prevent a reset. If AR5K_RSSI_THR is पढ़ो after writing to it
 * the BMISS_THRES will be seen as 0, seems hardware करोesn't keep
 * track of it. Max value depends on hardware. For AR5210 this is just 7.
 * For AR5211+ this seems to be up to 255. */
#घोषणा AR5K_TUNE_BMISS_THRES			7
#घोषणा AR5K_TUNE_REGISTER_DWELL_TIME		20000
#घोषणा AR5K_TUNE_BEACON_INTERVAL		100
#घोषणा AR5K_TUNE_AIFS				2
#घोषणा AR5K_TUNE_AIFS_11B			2
#घोषणा AR5K_TUNE_AIFS_XR			0
#घोषणा AR5K_TUNE_CWMIN				15
#घोषणा AR5K_TUNE_CWMIN_11B			31
#घोषणा AR5K_TUNE_CWMIN_XR			3
#घोषणा AR5K_TUNE_CWMAX				1023
#घोषणा AR5K_TUNE_CWMAX_11B			1023
#घोषणा AR5K_TUNE_CWMAX_XR			7
#घोषणा AR5K_TUNE_NOISE_FLOOR			-72
#घोषणा AR5K_TUNE_CCA_MAX_GOOD_VALUE		-95
#घोषणा AR5K_TUNE_MAX_TXPOWER			63
#घोषणा AR5K_TUNE_DEFAULT_TXPOWER		25
#घोषणा AR5K_TUNE_TPC_TXPOWER			false
#घोषणा ATH5K_TUNE_CALIBRATION_INTERVAL_FULL    60000   /* 60 sec */
#घोषणा	ATH5K_TUNE_CALIBRATION_INTERVAL_SHORT	10000	/* 10 sec */
#घोषणा ATH5K_TUNE_CALIBRATION_INTERVAL_ANI	1000	/* 1 sec */
#घोषणा ATH5K_TX_COMPLETE_POLL_INT		3000	/* 3 sec */

#घोषणा AR5K_INIT_CARR_SENSE_EN			1

/*Swap RX/TX Descriptor क्रम big endian archs*/
#अगर defined(__BIG_ENDIAN)
#घोषणा AR5K_INIT_CFG	(		\
	AR5K_CFG_SWTD | AR5K_CFG_SWRD	\
)
#अन्यथा
#घोषणा AR5K_INIT_CFG	0x00000000
#पूर्ण_अगर

/* Initial values */
#घोषणा	AR5K_INIT_CYCRSSI_THR1			2

/* Tx retry limit शेषs from standard */
#घोषणा AR5K_INIT_RETRY_SHORT			7
#घोषणा AR5K_INIT_RETRY_LONG			4

/* Slot समय */
#घोषणा AR5K_INIT_SLOT_TIME_TURBO		6
#घोषणा AR5K_INIT_SLOT_TIME_DEFAULT		9
#घोषणा	AR5K_INIT_SLOT_TIME_HALF_RATE		13
#घोषणा	AR5K_INIT_SLOT_TIME_QUARTER_RATE	21
#घोषणा	AR5K_INIT_SLOT_TIME_B			20
#घोषणा AR5K_SLOT_TIME_MAX			0xffff

/* SIFS */
#घोषणा	AR5K_INIT_SIFS_TURBO			6
#घोषणा	AR5K_INIT_SIFS_DEFAULT_BG		10
#घोषणा	AR5K_INIT_SIFS_DEFAULT_A		16
#घोषणा	AR5K_INIT_SIFS_HALF_RATE		32
#घोषणा AR5K_INIT_SIFS_QUARTER_RATE		64

/* Used to calculate tx समय क्रम non 5/10/40MHz
 * operation */
/* It's preamble समय + संकेत समय (16 + 4) */
#घोषणा	AR5K_INIT_OFDM_PREAMPLE_TIME		20
/* Preamble समय क्रम 40MHz (turbo) operation (min ?) */
#घोषणा	AR5K_INIT_OFDM_PREAMBLE_TIME_MIN	14
#घोषणा	AR5K_INIT_OFDM_SYMBOL_TIME		4
#घोषणा	AR5K_INIT_OFDM_PLCP_BITS		22

/* Rx latency क्रम 5 and 10MHz operation (max ?) */
#घोषणा AR5K_INIT_RX_LAT_MAX			63
/* Tx latencies from initvals (5212 only but no problem
 * because we only tweak them on 5212) */
#घोषणा	AR5K_INIT_TX_LAT_A			54
#घोषणा	AR5K_INIT_TX_LAT_BG			384
/* Tx latency क्रम 40MHz (turbo) operation (min ?) */
#घोषणा	AR5K_INIT_TX_LAT_MIN			32
/* Default Tx/Rx latencies (same क्रम 5211)*/
#घोषणा AR5K_INIT_TX_LATENCY_5210		54
#घोषणा	AR5K_INIT_RX_LATENCY_5210		29

/* Tx frame to Tx data start delay */
#घोषणा AR5K_INIT_TXF2TXD_START_DEFAULT		14
#घोषणा AR5K_INIT_TXF2TXD_START_DELAY_10MHZ	12
#घोषणा AR5K_INIT_TXF2TXD_START_DELAY_5MHZ	13

/* We need to increase PHY चयन and agc settling समय
 * on turbo mode */
#घोषणा	AR5K_SWITCH_SETTLING			5760
#घोषणा	AR5K_SWITCH_SETTLING_TURBO		7168

#घोषणा	AR5K_AGC_SETTLING			28
/* 38 on 5210 but shouldn't matter */
#घोषणा	AR5K_AGC_SETTLING_TURBO			37



/*****************************\
* GENERIC CHIPSET DEFINITIONS *
\*****************************/

/**
 * क्रमागत ath5k_version - MAC Chips
 * @AR5K_AR5210: AR5210 (Crete)
 * @AR5K_AR5211: AR5211 (Oahu/Maui)
 * @AR5K_AR5212: AR5212 (Venice) and newer
 */
क्रमागत ath5k_version अणु
	AR5K_AR5210	= 0,
	AR5K_AR5211	= 1,
	AR5K_AR5212	= 2,
पूर्ण;

/**
 * क्रमागत ath5k_radio - PHY Chips
 * @AR5K_RF5110: RF5110 (Fez)
 * @AR5K_RF5111: RF5111 (Sombrero)
 * @AR5K_RF5112: RF2112/5112(A) (Derby/Derby2)
 * @AR5K_RF2413: RF2413/2414 (Grअगरfin/Grअगरfin-Lite)
 * @AR5K_RF5413: RF5413/5414/5424 (Eagle/Conकरोr)
 * @AR5K_RF2316: RF2315/2316 (Cobra SoC)
 * @AR5K_RF2317: RF2317 (Spider SoC)
 * @AR5K_RF2425: RF2425/2417 (Swan/Nalla)
 */
क्रमागत ath5k_radio अणु
	AR5K_RF5110	= 0,
	AR5K_RF5111	= 1,
	AR5K_RF5112	= 2,
	AR5K_RF2413	= 3,
	AR5K_RF5413	= 4,
	AR5K_RF2316	= 5,
	AR5K_RF2317	= 6,
	AR5K_RF2425	= 7,
पूर्ण;

/*
 * Common silicon revision/version values
 */

#घोषणा AR5K_SREV_UNKNOWN	0xffff

#घोषणा AR5K_SREV_AR5210	0x00 /* Crete */
#घोषणा AR5K_SREV_AR5311	0x10 /* Maui 1 */
#घोषणा AR5K_SREV_AR5311A	0x20 /* Maui 2 */
#घोषणा AR5K_SREV_AR5311B	0x30 /* Spirit */
#घोषणा AR5K_SREV_AR5211	0x40 /* Oahu */
#घोषणा AR5K_SREV_AR5212	0x50 /* Venice */
#घोषणा AR5K_SREV_AR5312_R2	0x52 /* AP31 */
#घोषणा AR5K_SREV_AR5212_V4	0x54 /* ??? */
#घोषणा AR5K_SREV_AR5213	0x55 /* ??? */
#घोषणा AR5K_SREV_AR5312_R7	0x57 /* AP30 */
#घोषणा AR5K_SREV_AR2313_R8	0x58 /* AP43 */
#घोषणा AR5K_SREV_AR5213A	0x59 /* Hainan */
#घोषणा AR5K_SREV_AR2413	0x78 /* Grअगरfin lite */
#घोषणा AR5K_SREV_AR2414	0x70 /* Grअगरfin */
#घोषणा AR5K_SREV_AR2315_R6	0x86 /* AP51-Light */
#घोषणा AR5K_SREV_AR2315_R7	0x87 /* AP51-Full */
#घोषणा AR5K_SREV_AR5424	0x90 /* Conकरोr */
#घोषणा AR5K_SREV_AR2317_R1	0x90 /* AP61-Light */
#घोषणा AR5K_SREV_AR2317_R2	0x91 /* AP61-Full */
#घोषणा AR5K_SREV_AR5413	0xa4 /* Eagle lite */
#घोषणा AR5K_SREV_AR5414	0xa0 /* Eagle */
#घोषणा AR5K_SREV_AR2415	0xb0 /* Talon */
#घोषणा AR5K_SREV_AR5416	0xc0 /* PCI-E */
#घोषणा AR5K_SREV_AR5418	0xca /* PCI-E */
#घोषणा AR5K_SREV_AR2425	0xe0 /* Swan */
#घोषणा AR5K_SREV_AR2417	0xf0 /* Nala */

#घोषणा AR5K_SREV_RAD_5110	0x00
#घोषणा AR5K_SREV_RAD_5111	0x10
#घोषणा AR5K_SREV_RAD_5111A	0x15
#घोषणा AR5K_SREV_RAD_2111	0x20
#घोषणा AR5K_SREV_RAD_5112	0x30
#घोषणा AR5K_SREV_RAD_5112A	0x35
#घोषणा	AR5K_SREV_RAD_5112B	0x36
#घोषणा AR5K_SREV_RAD_2112	0x40
#घोषणा AR5K_SREV_RAD_2112A	0x45
#घोषणा	AR5K_SREV_RAD_2112B	0x46
#घोषणा AR5K_SREV_RAD_2413	0x50
#घोषणा AR5K_SREV_RAD_5413	0x60
#घोषणा AR5K_SREV_RAD_2316	0x70 /* Cobra SoC */
#घोषणा AR5K_SREV_RAD_2317	0x80
#घोषणा AR5K_SREV_RAD_5424	0xa0 /* Mostly same as 5413 */
#घोषणा AR5K_SREV_RAD_2425	0xa2
#घोषणा AR5K_SREV_RAD_5133	0xc0

#घोषणा AR5K_SREV_PHY_5211	0x30
#घोषणा AR5K_SREV_PHY_5212	0x41
#घोषणा	AR5K_SREV_PHY_5212A	0x42
#घोषणा AR5K_SREV_PHY_5212B	0x43
#घोषणा AR5K_SREV_PHY_2413	0x45
#घोषणा AR5K_SREV_PHY_5413	0x61
#घोषणा AR5K_SREV_PHY_2425	0x70

/* TODO add support to mac80211 क्रम venकरोr-specअगरic rates and modes */

/**
 * DOC: Atheros XR
 *
 * Some of this inक्रमmation is based on Documentation from:
 *
 * http://madwअगरi-project.org/wiki/ChipsetFeatures/SuperAG
 *
 * Atheros' eXtended Range - range enhancing extension is a modulation scheme
 * that is supposed to द्विगुन the link distance between an Atheros XR-enabled
 * client device with an Atheros XR-enabled access poपूर्णांक. This is achieved
 * by increasing the receiver sensitivity up to, -105dBm, which is about 20dB
 * above what the 802.11 specअगरications demand. In addition, new (proprietary)
 * data rates are पूर्णांकroduced: 3, 2, 1, 0.5 and 0.25 MBit/s.
 *
 * Please note that can you either use XR or TURBO but you cannot use both,
 * they are exclusive.
 *
 * Also note that we करो not plan to support XR mode at least क्रम now. You can
 * get a mode similar to XR by using 5MHz bwmode.
 */


/**
 * DOC: Atheros SuperAG
 *
 * In addition to XR we have another modulation scheme called TURBO mode
 * that is supposed to provide a throughput transmission speed up to 40Mbit/s
 * -60Mbit/s at a 108Mbit/s संकेतing rate achieved through the bonding of two
 * 54Mbit/s 802.11g channels. To use this feature both ends must support it.
 * There is also a distinction between "static" and "dynamic" turbo modes:
 *
 * - Static: is the dumb version: devices set to this mode stick to it until
 *     the mode is turned off.
 *
 * - Dynamic: is the पूर्णांकelligent version, the network decides itself अगर it
 *     is ok to use turbo. As soon as traffic is detected on adjacent channels
 *     (which would get used in turbo mode), or when a non-turbo station joins
 *     the network, turbo mode won't be used until the situation changes again.
 *     Dynamic mode is achieved by Atheros' Adaptive Radio (AR) feature which
 *     monitors the used radio band in order to decide whether turbo mode may
 *     be used or not.
 *
 * This article claims Super G sticks to bonding of channels 5 and 6 क्रम
 * USA:
 *
 * https://www.pcworld.com/article/id,113428-page,1/article.hपंचांगl
 *
 * The channel bonding seems to be driver specअगरic though.
 *
 * In addition to TURBO modes we also have the following features क्रम even
 * greater speed-up:
 *
 * - Bursting: allows multiple frames to be sent at once, rather than pausing
 *     after each frame. Bursting is a standards-compliant feature that can be
 *     used with any Access Poपूर्णांक.
 *
 * - Fast frames: increases the amount of inक्रमmation that can be sent per
 *     frame, also resulting in a reduction of transmission overhead. It is a
 *     proprietary feature that needs to be supported by the Access Poपूर्णांक.
 *
 * - Compression: data frames are compressed in real समय using a Lempel Ziv
 *     algorithm. This is करोne transparently. Once this feature is enabled,
 *     compression and decompression takes place inside the chipset, without
 *     putting additional load on the host CPU.
 *
 * As with XR we also करोn't plan to support SuperAG features क्रम now. You can
 * get a mode similar to TURBO by using 40MHz bwmode.
 */


/**
 * क्रमागत ath5k_driver_mode - PHY operation mode
 * @AR5K_MODE_11A: 802.11a
 * @AR5K_MODE_11B: 802.11b
 * @AR5K_MODE_11G: 801.11g
 * @AR5K_MODE_MAX: Used क्रम boundary checks
 *
 * Do not change the order here, we use these as
 * array indices and it also maps EEPROM काष्ठाures.
 */
क्रमागत ath5k_driver_mode अणु
	AR5K_MODE_11A		=	0,
	AR5K_MODE_11B		=	1,
	AR5K_MODE_11G		=	2,
	AR5K_MODE_MAX		=	3
पूर्ण;

/**
 * क्रमागत ath5k_ant_mode - Antenna operation mode
 * @AR5K_ANTMODE_DEFAULT: Default antenna setup
 * @AR5K_ANTMODE_FIXED_A: Only antenna A is present
 * @AR5K_ANTMODE_FIXED_B: Only antenna B is present
 * @AR5K_ANTMODE_SINGLE_AP: STA locked on a single ap
 * @AR5K_ANTMODE_SECTOR_AP: AP with tx antenna set on tx desc
 * @AR5K_ANTMODE_SECTOR_STA: STA with tx antenna set on tx desc
 * @AR5K_ANTMODE_DEBUG: Debug mode -A -> Rx, B-> Tx-
 * @AR5K_ANTMODE_MAX: Used क्रम boundary checks
 *
 * For more infos on antenna control check out phy.c
 */
क्रमागत ath5k_ant_mode अणु
	AR5K_ANTMODE_DEFAULT	= 0,
	AR5K_ANTMODE_FIXED_A	= 1,
	AR5K_ANTMODE_FIXED_B	= 2,
	AR5K_ANTMODE_SINGLE_AP	= 3,
	AR5K_ANTMODE_SECTOR_AP	= 4,
	AR5K_ANTMODE_SECTOR_STA	= 5,
	AR5K_ANTMODE_DEBUG	= 6,
	AR5K_ANTMODE_MAX,
पूर्ण;

/**
 * क्रमागत ath5k_bw_mode - Bandwidth operation mode
 * @AR5K_BWMODE_DEFAULT: 20MHz, शेष operation
 * @AR5K_BWMODE_5MHZ: Quarter rate
 * @AR5K_BWMODE_10MHZ: Half rate
 * @AR5K_BWMODE_40MHZ: Turbo
 */
क्रमागत ath5k_bw_mode अणु
	AR5K_BWMODE_DEFAULT	= 0,
	AR5K_BWMODE_5MHZ	= 1,
	AR5K_BWMODE_10MHZ	= 2,
	AR5K_BWMODE_40MHZ	= 3
पूर्ण;



/****************\
  TX DEFINITIONS
\****************/

/**
 * काष्ठा ath5k_tx_status - TX Status descriptor
 * @ts_seqnum: Sequence number
 * @ts_tstamp: Timestamp
 * @ts_status: Status code
 * @ts_final_idx: Final transmission series index
 * @ts_final_retry: Final retry count
 * @ts_rssi: RSSI क्रम received ACK
 * @ts_लघुretry: Short retry count
 * @ts_virtcol: Virtual collision count
 * @ts_antenna: Antenna used
 *
 * TX status descriptor माला_लो filled by the hw
 * on each transmission attempt.
 */
काष्ठा ath5k_tx_status अणु
	u16	ts_seqnum;
	u16	ts_tstamp;
	u8	ts_status;
	u8	ts_final_idx;
	u8	ts_final_retry;
	s8	ts_rssi;
	u8	ts_लघुretry;
	u8	ts_virtcol;
	u8	ts_antenna;
पूर्ण;

#घोषणा AR5K_TXSTAT_ALTRATE	0x80
#घोषणा AR5K_TXERR_XRETRY	0x01
#घोषणा AR5K_TXERR_FILT		0x02
#घोषणा AR5K_TXERR_FIFO		0x04

/**
 * क्रमागत ath5k_tx_queue - Queue types used to classअगरy tx queues.
 * @AR5K_TX_QUEUE_INACTIVE: q is unused -- see ath5k_hw_release_tx_queue
 * @AR5K_TX_QUEUE_DATA: A normal data queue
 * @AR5K_TX_QUEUE_BEACON: The beacon queue
 * @AR5K_TX_QUEUE_CAB: The after-beacon queue
 * @AR5K_TX_QUEUE_UAPSD: Unscheduled Automatic Power Save Delivery queue
 */
क्रमागत ath5k_tx_queue अणु
	AR5K_TX_QUEUE_INACTIVE = 0,
	AR5K_TX_QUEUE_DATA,
	AR5K_TX_QUEUE_BEACON,
	AR5K_TX_QUEUE_CAB,
	AR5K_TX_QUEUE_UAPSD,
पूर्ण;

#घोषणा	AR5K_NUM_TX_QUEUES		10
#घोषणा	AR5K_NUM_TX_QUEUES_NOQCU	2

/**
 * क्रमागत ath5k_tx_queue_subtype - Queue sub-types to classअगरy normal data queues
 * @AR5K_WME_AC_BK: Background traffic
 * @AR5K_WME_AC_BE: Best-efक्रमt (normal) traffic
 * @AR5K_WME_AC_VI: Video traffic
 * @AR5K_WME_AC_VO: Voice traffic
 *
 * These are the 4 Access Categories as defined in
 * WME spec. 0 is the lowest priority and 4 is the
 * highest. Normal data that hasn't been classअगरied
 * goes to the Best Efक्रमt AC.
 */
क्रमागत ath5k_tx_queue_subtype अणु
	AR5K_WME_AC_BK = 0,
	AR5K_WME_AC_BE,
	AR5K_WME_AC_VI,
	AR5K_WME_AC_VO,
पूर्ण;

/**
 * क्रमागत ath5k_tx_queue_id - Queue ID numbers as वापसed by the hw functions
 * @AR5K_TX_QUEUE_ID_NOQCU_DATA: Data queue on AR5210 (no QCU available)
 * @AR5K_TX_QUEUE_ID_NOQCU_BEACON: Beacon queue on AR5210 (no QCU available)
 * @AR5K_TX_QUEUE_ID_DATA_MIN: Data queue min index
 * @AR5K_TX_QUEUE_ID_DATA_MAX: Data queue max index
 * @AR5K_TX_QUEUE_ID_CAB: Content after beacon queue
 * @AR5K_TX_QUEUE_ID_BEACON: Beacon queue
 * @AR5K_TX_QUEUE_ID_UAPSD: Urgent Automatic Power Save Delivery,
 *
 * Each number represents a hw queue. If hw करोes not support hw queues
 * (eg 5210) all data goes in one queue.
 */
क्रमागत ath5k_tx_queue_id अणु
	AR5K_TX_QUEUE_ID_NOQCU_DATA	= 0,
	AR5K_TX_QUEUE_ID_NOQCU_BEACON	= 1,
	AR5K_TX_QUEUE_ID_DATA_MIN	= 0,
	AR5K_TX_QUEUE_ID_DATA_MAX	= 3,
	AR5K_TX_QUEUE_ID_UAPSD		= 7,
	AR5K_TX_QUEUE_ID_CAB		= 8,
	AR5K_TX_QUEUE_ID_BEACON		= 9,
पूर्ण;

/*
 * Flags to set hw queue's parameters...
 */
#घोषणा AR5K_TXQ_FLAG_TXOKINT_ENABLE		0x0001	/* Enable TXOK पूर्णांकerrupt */
#घोषणा AR5K_TXQ_FLAG_TXERRINT_ENABLE		0x0002	/* Enable TXERR पूर्णांकerrupt */
#घोषणा AR5K_TXQ_FLAG_TXEOLINT_ENABLE		0x0004	/* Enable TXEOL पूर्णांकerrupt -not used- */
#घोषणा AR5K_TXQ_FLAG_TXDESCINT_ENABLE		0x0008	/* Enable TXDESC पूर्णांकerrupt -not used- */
#घोषणा AR5K_TXQ_FLAG_TXURNINT_ENABLE		0x0010	/* Enable TXURN पूर्णांकerrupt */
#घोषणा AR5K_TXQ_FLAG_CBRORNINT_ENABLE		0x0020	/* Enable CBRORN पूर्णांकerrupt */
#घोषणा AR5K_TXQ_FLAG_CBRURNINT_ENABLE		0x0040	/* Enable CBRURN पूर्णांकerrupt */
#घोषणा AR5K_TXQ_FLAG_QTRIGINT_ENABLE		0x0080	/* Enable QTRIG पूर्णांकerrupt */
#घोषणा AR5K_TXQ_FLAG_TXNOFRMINT_ENABLE		0x0100	/* Enable TXNOFRM पूर्णांकerrupt */
#घोषणा AR5K_TXQ_FLAG_BACKOFF_DISABLE		0x0200	/* Disable अक्रमom post-backoff */
#घोषणा AR5K_TXQ_FLAG_RDYTIME_EXP_POLICY_ENABLE	0x0300	/* Enable पढ़ोy समय expiry policy (?)*/
#घोषणा AR5K_TXQ_FLAG_FRAG_BURST_BACKOFF_ENABLE	0x0800	/* Enable backoff जबतक bursting */
#घोषणा AR5K_TXQ_FLAG_POST_FR_BKOFF_DIS		0x1000	/* Disable backoff जबतक bursting */
#घोषणा AR5K_TXQ_FLAG_COMPRESSION_ENABLE	0x2000	/* Enable hw compression -not implemented-*/

/**
 * काष्ठा ath5k_txq - Transmit queue state
 * @qnum: Hardware q number
 * @link: Link ptr in last TX desc
 * @q: Transmit queue (&काष्ठा list_head)
 * @lock: Lock on q and link
 * @setup: Is the queue configured
 * @txq_len:Number of queued buffers
 * @txq_max: Max allowed num of queued buffers
 * @txq_poll_mark: Used to check अगर queue got stuck
 * @txq_stuck: Queue stuck counter
 *
 * One of these exists क्रम each hardware transmit queue.
 * Packets sent to us from above are asचिन्हित to queues based
 * on their priority.  Not all devices support a complete set
 * of hardware transmit queues. For those devices the array
 * sc_ac2q will map multiple priorities to fewer hardware queues
 * (typically all to one hardware queue).
 */
काष्ठा ath5k_txq अणु
	अचिन्हित पूर्णांक		qnum;
	u32			*link;
	काष्ठा list_head	q;
	spinlock_t		lock;
	bool			setup;
	पूर्णांक			txq_len;
	पूर्णांक			txq_max;
	bool			txq_poll_mark;
	अचिन्हित पूर्णांक		txq_stuck;
पूर्ण;

/**
 * काष्ठा ath5k_txq_info - A काष्ठा to hold TX queue's parameters
 * @tqi_type: One of क्रमागत ath5k_tx_queue
 * @tqi_subtype: One of क्रमागत ath5k_tx_queue_subtype
 * @tqi_flags: TX queue flags (see above)
 * @tqi_aअगरs: Arbitrated Inter-frame Space
 * @tqi_cw_min: Minimum Contention Winकरोw
 * @tqi_cw_max: Maximum Contention Winकरोw
 * @tqi_cbr_period: Constant bit rate period
 * @tqi_पढ़ोy_समय: Time queue रुकोs after an event when RDYTIME is enabled
 */
काष्ठा ath5k_txq_info अणु
	क्रमागत ath5k_tx_queue tqi_type;
	क्रमागत ath5k_tx_queue_subtype tqi_subtype;
	u16	tqi_flags;
	u8	tqi_aअगरs;
	u16	tqi_cw_min;
	u16	tqi_cw_max;
	u32	tqi_cbr_period;
	u32	tqi_cbr_overflow_limit;
	u32	tqi_burst_समय;
	u32	tqi_पढ़ोy_समय;
पूर्ण;

/**
 * क्रमागत ath5k_pkt_type - Transmit packet types
 * @AR5K_PKT_TYPE_NORMAL: Normal data
 * @AR5K_PKT_TYPE_ATIM: ATIM
 * @AR5K_PKT_TYPE_PSPOLL: PS-Poll
 * @AR5K_PKT_TYPE_BEACON: Beacon
 * @AR5K_PKT_TYPE_PROBE_RESP: Probe response
 * @AR5K_PKT_TYPE_PIFS: PIFS
 * Used on tx control descriptor
 */
क्रमागत ath5k_pkt_type अणु
	AR5K_PKT_TYPE_NORMAL		= 0,
	AR5K_PKT_TYPE_ATIM		= 1,
	AR5K_PKT_TYPE_PSPOLL		= 2,
	AR5K_PKT_TYPE_BEACON		= 3,
	AR5K_PKT_TYPE_PROBE_RESP	= 4,
	AR5K_PKT_TYPE_PIFS		= 5,
पूर्ण;

/*
 * TX घातer and TPC settings
 */
#घोषणा AR5K_TXPOWER_OFDM(_r, _v)	(			\
	((0 & 1) << ((_v) + 6)) |				\
	(((ah->ah_txघातer.txp_rates_घातer_table[(_r)]) & 0x3f) << (_v))	\
)

#घोषणा AR5K_TXPOWER_CCK(_r, _v)	(			\
	(ah->ah_txघातer.txp_rates_घातer_table[(_r)] & 0x3f) << (_v)	\
)



/****************\
  RX DEFINITIONS
\****************/

/**
 * काष्ठा ath5k_rx_status - RX Status descriptor
 * @rs_datalen: Data length
 * @rs_tstamp: Timestamp
 * @rs_status: Status code
 * @rs_phyerr: PHY error mask
 * @rs_rssi: RSSI in 0.5dbm units
 * @rs_keyix: Index to the key used क्रम decrypting
 * @rs_rate: Rate used to decode the frame
 * @rs_antenna: Antenna used to receive the frame
 * @rs_more: Indicates this is a frame fragment (Fast frames)
 */
काष्ठा ath5k_rx_status अणु
	u16	rs_datalen;
	u16	rs_tstamp;
	u8	rs_status;
	u8	rs_phyerr;
	s8	rs_rssi;
	u8	rs_keyix;
	u8	rs_rate;
	u8	rs_antenna;
	u8	rs_more;
पूर्ण;

#घोषणा AR5K_RXERR_CRC		0x01
#घोषणा AR5K_RXERR_PHY		0x02
#घोषणा AR5K_RXERR_FIFO		0x04
#घोषणा AR5K_RXERR_DECRYPT	0x08
#घोषणा AR5K_RXERR_MIC		0x10
#घोषणा AR5K_RXKEYIX_INVALID	((u8) -1)
#घोषणा AR5K_TXKEYIX_INVALID	((u32) -1)


/**************************\
 BEACON TIMERS DEFINITIONS
\**************************/

#घोषणा AR5K_BEACON_PERIOD	0x0000ffff
#घोषणा AR5K_BEACON_ENA		0x00800000 /*enable beacon xmit*/
#घोषणा AR5K_BEACON_RESET_TSF	0x01000000 /*क्रमce a TSF reset*/


/*
 * TSF to TU conversion:
 *
 * TSF is a 64bit value in usec (microseconds).
 * TU is a 32bit value and defined by IEEE802.11 (page 6) as "A measurement of
 * समय equal to 1024 usec", so it's roughly milliseconds (usec / 1024).
 */
#घोषणा TSF_TO_TU(_tsf) (u32)((_tsf) >> 10)



/*******************************\
  GAIN OPTIMIZATION DEFINITIONS
\*******************************/

/**
 * क्रमागत ath5k_rfgain - RF Gain optimization engine state
 * @AR5K_RFGAIN_INACTIVE: Engine disabled
 * @AR5K_RFGAIN_ACTIVE: Probe active
 * @AR5K_RFGAIN_READ_REQUESTED: Probe requested
 * @AR5K_RFGAIN_NEED_CHANGE: Gain_F needs change
 */
क्रमागत ath5k_rfgain अणु
	AR5K_RFGAIN_INACTIVE = 0,
	AR5K_RFGAIN_ACTIVE,
	AR5K_RFGAIN_READ_REQUESTED,
	AR5K_RFGAIN_NEED_CHANGE,
पूर्ण;

/**
 * काष्ठा ath5k_gain - RF Gain optimization engine state data
 * @g_step_idx: Current step index
 * @g_current: Current gain
 * @g_target: Target gain
 * @g_low: Low gain boundary
 * @g_high: High gain boundary
 * @g_f_corr: Gain_F correction
 * @g_state: One of क्रमागत ath5k_rfgain
 */
काष्ठा ath5k_gain अणु
	u8			g_step_idx;
	u8			g_current;
	u8			g_target;
	u8			g_low;
	u8			g_high;
	u8			g_f_corr;
	u8			g_state;
पूर्ण;



/********************\
  COMMON DEFINITIONS
\********************/

#घोषणा AR5K_SLOT_TIME_9	396
#घोषणा AR5K_SLOT_TIME_20	880
#घोषणा AR5K_SLOT_TIME_MAX	0xffff

/**
 * काष्ठा ath5k_athchan_2ghz - 2GHz to 5GHZ map क्रम RF5111
 * @a2_flags: Channel flags (पूर्णांकernal)
 * @a2_athchan: HW channel number (पूर्णांकernal)
 *
 * This काष्ठाure is used to map 2GHz channels to
 * 5GHz Atheros channels on 2111 frequency converter
 * that comes together with RF5111
 * TODO: Clean up
 */
काष्ठा ath5k_athchan_2ghz अणु
	u32	a2_flags;
	u16	a2_athchan;
पूर्ण;

/**
 * क्रमागत ath5k_dmasize -  DMA size definitions (2^(n+2))
 * @AR5K_DMASIZE_4B: 4Bytes
 * @AR5K_DMASIZE_8B: 8Bytes
 * @AR5K_DMASIZE_16B: 16Bytes
 * @AR5K_DMASIZE_32B: 32Bytes
 * @AR5K_DMASIZE_64B: 64Bytes (Default)
 * @AR5K_DMASIZE_128B: 128Bytes
 * @AR5K_DMASIZE_256B: 256Bytes
 * @AR5K_DMASIZE_512B: 512Bytes
 *
 * These are used to set DMA burst size on hw
 *
 * Note: Some platक्रमms can't handle more than 4Bytes
 * be careful on embedded boards.
 */
क्रमागत ath5k_dmasize अणु
	AR5K_DMASIZE_4B	= 0,
	AR5K_DMASIZE_8B,
	AR5K_DMASIZE_16B,
	AR5K_DMASIZE_32B,
	AR5K_DMASIZE_64B,
	AR5K_DMASIZE_128B,
	AR5K_DMASIZE_256B,
	AR5K_DMASIZE_512B
पूर्ण;



/******************\
  RATE DEFINITIONS
\******************/

/**
 * DOC: Rate codes
 *
 * Seems the ar5xxx hardware supports up to 32 rates, indexed by 1-32.
 *
 * The rate code is used to get the RX rate or set the TX rate on the
 * hardware descriptors. It is also used क्रम पूर्णांकernal modulation control
 * and settings.
 *
 * This is the hardware rate map we are aware of (hपंचांगl unमित्रly):
 *
 * Rate code	Rate (Kbps)
 * ---------	-----------
 * 0x01		 3000 (XR)
 * 0x02		 1000 (XR)
 * 0x03		  250 (XR)
 * 0x04 - 05	-Reserved-
 * 0x06		 2000 (XR)
 * 0x07		  500 (XR)
 * 0x08		48000 (OFDM)
 * 0x09		24000 (OFDM)
 * 0x0A		12000 (OFDM)
 * 0x0B		 6000 (OFDM)
 * 0x0C		54000 (OFDM)
 * 0x0D		36000 (OFDM)
 * 0x0E		18000 (OFDM)
 * 0x0F		 9000 (OFDM)
 * 0x10 - 17	-Reserved-
 * 0x18		11000L (CCK)
 * 0x19		 5500L (CCK)
 * 0x1A		 2000L (CCK)
 * 0x1B		 1000L (CCK)
 * 0x1C		11000S (CCK)
 * 0x1D		 5500S (CCK)
 * 0x1E		 2000S (CCK)
 * 0x1F		-Reserved-
 *
 * "S" indicates CCK rates with लघु preamble and "L" with दीर्घ preamble.
 *
 * AR5211 has dअगरferent rate codes क्रम CCK (802.11B) rates. It only uses the
 * lowest 4 bits, so they are the same as above with a 0xF mask.
 * (0xB, 0xA, 0x9 and 0x8 क्रम 1M, 2M, 5.5M and 11M).
 * We handle this in ath5k_setup_bands().
 */
#घोषणा AR5K_MAX_RATES 32

/* B */
#घोषणा ATH5K_RATE_CODE_1M	0x1B
#घोषणा ATH5K_RATE_CODE_2M	0x1A
#घोषणा ATH5K_RATE_CODE_5_5M	0x19
#घोषणा ATH5K_RATE_CODE_11M	0x18
/* A and G */
#घोषणा ATH5K_RATE_CODE_6M	0x0B
#घोषणा ATH5K_RATE_CODE_9M	0x0F
#घोषणा ATH5K_RATE_CODE_12M	0x0A
#घोषणा ATH5K_RATE_CODE_18M	0x0E
#घोषणा ATH5K_RATE_CODE_24M	0x09
#घोषणा ATH5K_RATE_CODE_36M	0x0D
#घोषणा ATH5K_RATE_CODE_48M	0x08
#घोषणा ATH5K_RATE_CODE_54M	0x0C

/* Adding this flag to rate_code on B rates
 * enables लघु preamble */
#घोषणा AR5K_SET_SHORT_PREAMBLE 0x04

/*
 * Crypto definitions
 */

#घोषणा AR5K_KEYCACHE_SIZE	8
बाह्य bool ath5k_modparam_nohwcrypt;

/***********************\
 HW RELATED DEFINITIONS
\***********************/

/*
 * Misc definitions
 */
#घोषणा	AR5K_RSSI_EP_MULTIPLIER	(1 << 7)

#घोषणा AR5K_ASSERT_ENTRY(_e, _s) करो अणु		\
	अगर (_e >= _s)				\
		वापस false;			\
पूर्ण जबतक (0)

/*
 * Hardware पूर्णांकerrupt असलtraction
 */

/**
 * क्रमागत ath5k_पूर्णांक - Hardware पूर्णांकerrupt masks helpers
 * @AR5K_INT_RXOK: Frame successfully received
 * @AR5K_INT_RXDESC: Request RX descriptor/Read RX descriptor
 * @AR5K_INT_RXERR: Frame reception failed
 * @AR5K_INT_RXNOFRM: No frame received within a specअगरied समय period
 * @AR5K_INT_RXEOL: Reached "End Of List", means we need more RX descriptors
 * @AR5K_INT_RXORN: Indicates we got RX FIFO overrun. Note that Rx overrun is
 *		not always fatal, on some chips we can जारी operation
 *		without resetting the card, that's why %AR5K_INT_FATAL is not
 *		common क्रम all chips.
 * @AR5K_INT_RX_ALL: Mask to identअगरy all RX related पूर्णांकerrupts
 *
 * @AR5K_INT_TXOK: Frame transmission success
 * @AR5K_INT_TXDESC: Request TX descriptor/Read TX status descriptor
 * @AR5K_INT_TXERR: Frame transmission failure
 * @AR5K_INT_TXEOL: Received End Of List क्रम VEOL (Virtual End Of List). The
 *		Queue Control Unit (QCU) संकेतs an EOL पूर्णांकerrupt only अगर a
 *		descriptor's LinkPtr is शून्य. For more details, refer to:
 *		"http://www.freepatentsonline.com/20030225739.html"
 * @AR5K_INT_TXNOFRM: No frame was transmitted within a specअगरied समय period
 * @AR5K_INT_TXURN: Indicates we got TX FIFO underrun. In such हाल we should
 *		increase the TX trigger threshold.
 * @AR5K_INT_TX_ALL: Mask to identअगरy all TX related पूर्णांकerrupts
 *
 * @AR5K_INT_MIB: Indicates the either Management Inक्रमmation Base counters or
 *		one of the PHY error counters reached the maximum value and
 *		should be पढ़ो and cleared.
 * @AR5K_INT_SWI: Software triggered पूर्णांकerrupt.
 * @AR5K_INT_RXPHY: RX PHY Error
 * @AR5K_INT_RXKCM: RX Key cache miss
 * @AR5K_INT_SWBA: SoftWare Beacon Alert - indicates its समय to send a
 *		beacon that must be handled in software. The alternative is अगर
 *		you have VEOL support, in that हाल you let the hardware deal
 *		with things.
 * @AR5K_INT_BRSSI: Beacon received with an RSSI value below our threshold
 * @AR5K_INT_BMISS: If in STA mode this indicates we have stopped seeing
 *		beacons from the AP have associated with, we should probably
 *		try to reassociate. When in IBSS mode this might mean we have
 *		not received any beacons from any local stations. Note that
 *		every station in an IBSS schedules to send beacons at the
 *		Target Beacon Transmission Time (TBTT) with a अक्रमom backoff.
 * @AR5K_INT_BNR: Beacon queue got triggered (DMA beacon alert) जबतक empty.
 * @AR5K_INT_TIM: Beacon with local station's TIM bit set
 * @AR5K_INT_DTIM: Beacon with DTIM bit and zero DTIM count received
 * @AR5K_INT_DTIM_SYNC: DTIM sync lost
 * @AR5K_INT_GPIO: GPIO पूर्णांकerrupt is used क्रम RF Kill चयनes connected to
 *		our GPIO pins.
 * @AR5K_INT_BCN_TIMEOUT: Beacon समयout, we रुकोed after TBTT but got noting
 * @AR5K_INT_CAB_TIMEOUT: We रुकोed क्रम CAB traffic after the beacon but got
 *		nothing or an incomplete CAB frame sequence.
 * @AR5K_INT_QCBRORN: A queue got it's CBR counter expired
 * @AR5K_INT_QCBRURN: A queue got triggered wile empty
 * @AR5K_INT_QTRIG: A queue got triggered
 *
 * @AR5K_INT_FATAL: Fatal errors were encountered, typically caused by bus/DMA
 *		errors. Indicates we need to reset the card.
 * @AR5K_INT_GLOBAL: Used to clear and set the IER
 * @AR5K_INT_NOCARD: Signals the card has been हटाओd
 * @AR5K_INT_COMMON: Common पूर्णांकerrupts shared among MACs with the same
 *		bit value
 *
 * These are mapped to take advantage of some common bits
 * between the MACs, to be able to set पूर्णांकr properties
 * easier. Some of them are not used yet inside hw.c. Most map
 * to the respective hw पूर्णांकerrupt value as they are common among dअगरferent
 * MACs.
 */
क्रमागत ath5k_पूर्णांक अणु
	AR5K_INT_RXOK	= 0x00000001,
	AR5K_INT_RXDESC	= 0x00000002,
	AR5K_INT_RXERR	= 0x00000004,
	AR5K_INT_RXNOFRM = 0x00000008,
	AR5K_INT_RXEOL	= 0x00000010,
	AR5K_INT_RXORN	= 0x00000020,
	AR5K_INT_TXOK	= 0x00000040,
	AR5K_INT_TXDESC	= 0x00000080,
	AR5K_INT_TXERR	= 0x00000100,
	AR5K_INT_TXNOFRM = 0x00000200,
	AR5K_INT_TXEOL	= 0x00000400,
	AR5K_INT_TXURN	= 0x00000800,
	AR5K_INT_MIB	= 0x00001000,
	AR5K_INT_SWI	= 0x00002000,
	AR5K_INT_RXPHY	= 0x00004000,
	AR5K_INT_RXKCM	= 0x00008000,
	AR5K_INT_SWBA	= 0x00010000,
	AR5K_INT_BRSSI	= 0x00020000,
	AR5K_INT_BMISS	= 0x00040000,
	AR5K_INT_FATAL	= 0x00080000, /* Non common */
	AR5K_INT_BNR	= 0x00100000, /* Non common */
	AR5K_INT_TIM	= 0x00200000, /* Non common */
	AR5K_INT_DTIM	= 0x00400000, /* Non common */
	AR5K_INT_DTIM_SYNC =	0x00800000, /* Non common */
	AR5K_INT_GPIO	=	0x01000000,
	AR5K_INT_BCN_TIMEOUT =	0x02000000, /* Non common */
	AR5K_INT_CAB_TIMEOUT =	0x04000000, /* Non common */
	AR5K_INT_QCBRORN =	0x08000000, /* Non common */
	AR5K_INT_QCBRURN =	0x10000000, /* Non common */
	AR5K_INT_QTRIG	=	0x20000000, /* Non common */
	AR5K_INT_GLOBAL =	0x80000000,

	AR5K_INT_TX_ALL = AR5K_INT_TXOK
		| AR5K_INT_TXDESC
		| AR5K_INT_TXERR
		| AR5K_INT_TXNOFRM
		| AR5K_INT_TXEOL
		| AR5K_INT_TXURN,

	AR5K_INT_RX_ALL = AR5K_INT_RXOK
		| AR5K_INT_RXDESC
		| AR5K_INT_RXERR
		| AR5K_INT_RXNOFRM
		| AR5K_INT_RXEOL
		| AR5K_INT_RXORN,

	AR5K_INT_COMMON  = AR5K_INT_RXOK
		| AR5K_INT_RXDESC
		| AR5K_INT_RXERR
		| AR5K_INT_RXNOFRM
		| AR5K_INT_RXEOL
		| AR5K_INT_RXORN
		| AR5K_INT_TXOK
		| AR5K_INT_TXDESC
		| AR5K_INT_TXERR
		| AR5K_INT_TXNOFRM
		| AR5K_INT_TXEOL
		| AR5K_INT_TXURN
		| AR5K_INT_MIB
		| AR5K_INT_SWI
		| AR5K_INT_RXPHY
		| AR5K_INT_RXKCM
		| AR5K_INT_SWBA
		| AR5K_INT_BRSSI
		| AR5K_INT_BMISS
		| AR5K_INT_GPIO
		| AR5K_INT_GLOBAL,

	AR5K_INT_NOCARD	= 0xffffffff
पूर्ण;

/**
 * क्रमागत ath5k_calibration_mask - Mask which calibration is active at the moment
 * @AR5K_CALIBRATION_FULL: Full calibration (AGC + SHORT)
 * @AR5K_CALIBRATION_SHORT: Short calibration (NF + I/Q)
 * @AR5K_CALIBRATION_NF: Noise Floor calibration
 * @AR5K_CALIBRATION_ANI: Adaptive Noise Immunity
 */
क्रमागत ath5k_calibration_mask अणु
	AR5K_CALIBRATION_FULL = 0x01,
	AR5K_CALIBRATION_SHORT = 0x02,
	AR5K_CALIBRATION_NF = 0x04,
	AR5K_CALIBRATION_ANI = 0x08,
पूर्ण;

/**
 * क्रमागत ath5k_घातer_mode - Power management modes
 * @AR5K_PM_UNDEFINED: Undefined
 * @AR5K_PM_AUTO: Allow card to sleep अगर possible
 * @AR5K_PM_AWAKE: Force card to wake up
 * @AR5K_PM_FULL_SLEEP: Force card to full sleep (DANGEROUS)
 * @AR5K_PM_NETWORK_SLEEP: Allow to sleep क्रम a specअगरied duration
 *
 * Currently only PM_AWAKE is used, FULL_SLEEP and NETWORK_SLEEP/AUTO
 * are also known to have problems on some cards. This is not a big
 * problem though because we can have almost the same effect as
 * FULL_SLEEP by putting card on warm reset (it's almost घातered करोwn).
 */
क्रमागत ath5k_घातer_mode अणु
	AR5K_PM_UNDEFINED = 0,
	AR5K_PM_AUTO,
	AR5K_PM_AWAKE,
	AR5K_PM_FULL_SLEEP,
	AR5K_PM_NETWORK_SLEEP,
पूर्ण;

/*
 * These match net80211 definitions (not used in
 * mac80211).
 * TODO: Clean this up
 */
#घोषणा AR5K_LED_INIT	0 /*IEEE80211_S_INIT*/
#घोषणा AR5K_LED_SCAN	1 /*IEEE80211_S_SCAN*/
#घोषणा AR5K_LED_AUTH	2 /*IEEE80211_S_AUTH*/
#घोषणा AR5K_LED_ASSOC	3 /*IEEE80211_S_ASSOC*/
#घोषणा AR5K_LED_RUN	4 /*IEEE80211_S_RUN*/

/* GPIO-controlled software LED */
#घोषणा AR5K_SOFTLED_PIN	0
#घोषणा AR5K_SOFTLED_ON		0
#घोषणा AR5K_SOFTLED_OFF	1


/* XXX: we *may* move cap_range stuff to काष्ठा wiphy */
काष्ठा ath5k_capabilities अणु
	/*
	 * Supported PHY modes
	 * (ie. AR5K_MODE_11A, AR5K_MODE_11B, ...)
	 */
	DECLARE_BITMAP(cap_mode, AR5K_MODE_MAX);

	/*
	 * Frequency range (without regulation restrictions)
	 */
	काष्ठा अणु
		u16	range_2ghz_min;
		u16	range_2ghz_max;
		u16	range_5ghz_min;
		u16	range_5ghz_max;
	पूर्ण cap_range;

	/*
	 * Values stored in the EEPROM (some of them...)
	 */
	काष्ठा ath5k_eeprom_info	cap_eeprom;

	/*
	 * Queue inक्रमmation
	 */
	काष्ठा अणु
		u8	q_tx_num;
	पूर्ण cap_queues;

	bool cap_has_phyerr_counters;
	bool cap_has_mrr_support;
	bool cap_needs_2GHz_ovr;
पूर्ण;

/* size of noise न्यूनमान history (keep it a घातer of two) */
#घोषणा ATH5K_NF_CAL_HIST_MAX	8
काष्ठा ath5k_nfcal_hist अणु
	s16 index;				/* current index पूर्णांकo nfval */
	s16 nfval[ATH5K_NF_CAL_HIST_MAX];	/* last few noise न्यूनमानs */
पूर्ण;

#घोषणा ATH5K_LED_MAX_NAME_LEN 31

/*
 * State क्रम LED triggers
 */
काष्ठा ath5k_led अणु
	अक्षर name[ATH5K_LED_MAX_NAME_LEN + 1];	/* name of the LED in sysfs */
	काष्ठा ath5k_hw *ah;			/* driver state */
	काष्ठा led_classdev led_dev;		/* led classdev */
पूर्ण;

/* Rfसमाप्त */
काष्ठा ath5k_rfसमाप्त अणु
	/* GPIO PIN क्रम rfसमाप्त */
	u16 gpio;
	/* polarity of rfसमाप्त GPIO PIN */
	bool polarity;
	/* RFKILL toggle tasklet */
	काष्ठा tasklet_काष्ठा toggleq;
पूर्ण;

/* statistics */
काष्ठा ath5k_statistics अणु
	/* antenna use */
	अचिन्हित पूर्णांक antenna_rx[5];	/* frames count per antenna RX */
	अचिन्हित पूर्णांक antenna_tx[5];	/* frames count per antenna TX */

	/* frame errors */
	अचिन्हित पूर्णांक rx_all_count;	/* all RX frames, including errors */
	अचिन्हित पूर्णांक tx_all_count;	/* all TX frames, including errors */
	अचिन्हित पूर्णांक rx_bytes_count;	/* all RX bytes, including errored pkts
					 * and the MAC headers क्रम each packet
					 */
	अचिन्हित पूर्णांक tx_bytes_count;	/* all TX bytes, including errored pkts
					 * and the MAC headers and padding क्रम
					 * each packet.
					 */
	अचिन्हित पूर्णांक rxerr_crc;
	अचिन्हित पूर्णांक rxerr_phy;
	अचिन्हित पूर्णांक rxerr_phy_code[32];
	अचिन्हित पूर्णांक rxerr_fअगरo;
	अचिन्हित पूर्णांक rxerr_decrypt;
	अचिन्हित पूर्णांक rxerr_mic;
	अचिन्हित पूर्णांक rxerr_proc;
	अचिन्हित पूर्णांक rxerr_jumbo;
	अचिन्हित पूर्णांक txerr_retry;
	अचिन्हित पूर्णांक txerr_fअगरo;
	अचिन्हित पूर्णांक txerr_filt;

	/* MIB counters */
	अचिन्हित पूर्णांक ack_fail;
	अचिन्हित पूर्णांक rts_fail;
	अचिन्हित पूर्णांक rts_ok;
	अचिन्हित पूर्णांक fcs_error;
	अचिन्हित पूर्णांक beacons;

	अचिन्हित पूर्णांक mib_पूर्णांकr;
	अचिन्हित पूर्णांक rxorn_पूर्णांकr;
	अचिन्हित पूर्णांक rxeol_पूर्णांकr;
पूर्ण;

/*
 * Misc defines
 */

#घोषणा AR5K_MAX_GPIO		10
#घोषणा AR5K_MAX_RF_BANKS	8

#अगर CHAN_DEBUG
#घोषणा ATH_CHAN_MAX	(26 + 26 + 26 + 200 + 200)
#अन्यथा
#घोषणा ATH_CHAN_MAX	(14 + 14 + 14 + 252 + 20)
#पूर्ण_अगर

#घोषणा	ATH_RXBUF	40		/* number of RX buffers */
#घोषणा	ATH_TXBUF	200		/* number of TX buffers */
#घोषणा ATH_BCBUF	4		/* number of beacon buffers */
#घोषणा ATH5K_TXQ_LEN_MAX	(ATH_TXBUF / 4)		/* bufs per queue */
#घोषणा ATH5K_TXQ_LEN_LOW	(ATH5K_TXQ_LEN_MAX / 2)	/* low mark */

DECLARE_EWMA(beacon_rssi, 10, 8)

/* Driver state associated with an instance of a device */
काष्ठा ath5k_hw अणु
	काष्ठा ath_common       common;

	काष्ठा pci_dev		*pdev;
	काष्ठा device		*dev;		/* क्रम dma mapping */
	पूर्णांक irq;
	u16 devid;
	व्योम __iomem		*iobase;	/* address of the device */
	काष्ठा mutex		lock;		/* dev-level lock */
	काष्ठा ieee80211_hw	*hw;		/* IEEE 802.11 common */
	काष्ठा ieee80211_supported_band sbands[NUM_NL80211_BANDS];
	काष्ठा ieee80211_channel channels[ATH_CHAN_MAX];
	काष्ठा ieee80211_rate	rates[NUM_NL80211_BANDS][AR5K_MAX_RATES];
	s8			rate_idx[NUM_NL80211_BANDS][AR5K_MAX_RATES];
	क्रमागत nl80211_अगरtype	opmode;

#अगर_घोषित CONFIG_ATH5K_DEBUG
	काष्ठा ath5k_dbg_info	debug;		/* debug info */
#पूर्ण_अगर /* CONFIG_ATH5K_DEBUG */

	काष्ठा ath5k_buf	*bufptr;	/* allocated buffer ptr */
	काष्ठा ath5k_desc	*desc;		/* TX/RX descriptors */
	dma_addr_t		desc_daddr;	/* DMA (physical) address */
	माप_प्रकार			desc_len;	/* size of TX/RX descriptors */

	DECLARE_BITMAP(status, 4);
#घोषणा ATH_STAT_INVALID	0		/* disable hardware accesses */
#घोषणा ATH_STAT_LEDSOFT	2		/* enable LED gpio status */
#घोषणा ATH_STAT_STARTED	3		/* खोलोed & irqs enabled */
#घोषणा ATH_STAT_RESET		4		/* hw reset */

	अचिन्हित पूर्णांक		filter_flags;	/* HW flags, AR5K_RX_FILTER_* */
	अचिन्हित पूर्णांक		fअगर_filter_flags; /* Current FIF_* filter flags */
	काष्ठा ieee80211_channel *curchan;	/* current h/w channel */

	u16			nvअगरs;

	क्रमागत ath5k_पूर्णांक		imask;		/* पूर्णांकerrupt mask copy */

	spinlock_t		irqlock;
	bool			rx_pending;	/* rx tasklet pending */
	bool			tx_pending;	/* tx tasklet pending */

	u8			bssidmask[ETH_ALEN];

	अचिन्हित पूर्णांक		led_pin,	/* GPIO pin क्रम driving LED */
				led_on;		/* pin setting क्रम LED on */

	काष्ठा work_काष्ठा	reset_work;	/* deferred chip reset */
	काष्ठा work_काष्ठा	calib_work;	/* deferred phy calibration */

	काष्ठा list_head	rxbuf;		/* receive buffer */
	spinlock_t		rxbuflock;
	u32			*rxlink;	/* link ptr in last RX desc */
	काष्ठा tasklet_काष्ठा	rxtq;		/* rx पूर्णांकr tasklet */
	काष्ठा ath5k_led	rx_led;		/* rx led */

	काष्ठा list_head	txbuf;		/* transmit buffer */
	spinlock_t		txbuflock;
	अचिन्हित पूर्णांक		txbuf_len;	/* buf count in txbuf list */
	काष्ठा ath5k_txq	txqs[AR5K_NUM_TX_QUEUES];	/* tx queues */
	काष्ठा tasklet_काष्ठा	txtq;		/* tx पूर्णांकr tasklet */
	काष्ठा ath5k_led	tx_led;		/* tx led */

	काष्ठा ath5k_rfसमाप्त	rf_समाप्त;

	spinlock_t		block;		/* protects beacon */
	काष्ठा tasklet_काष्ठा	beacontq;	/* beacon पूर्णांकr tasklet */
	काष्ठा list_head	bcbuf;		/* beacon buffer */
	काष्ठा ieee80211_vअगर	*bslot[ATH_BCBUF];
	u16			num_ap_vअगरs;
	u16			num_adhoc_vअगरs;
	u16			num_mesh_vअगरs;
	अचिन्हित पूर्णांक		bhalq,		/* SW q क्रम outgoing beacons */
				bmisscount,	/* missed beacon transmits */
				bपूर्णांकval,	/* beacon पूर्णांकerval in TU */
				bsent;
	अचिन्हित पूर्णांक		nexttbtt;	/* next beacon समय in TU */
	काष्ठा ath5k_txq	*cabq;		/* content after beacon */

	bool			assoc;		/* associate state */
	bool			enable_beacon;	/* true अगर beacons are on */

	काष्ठा ath5k_statistics	stats;

	काष्ठा ath5k_ani_state	ani_state;
	काष्ठा tasklet_काष्ठा	ani_tasklet;	/* ANI calibration */

	काष्ठा delayed_work	tx_complete_work;

	काष्ठा survey_info	survey;		/* collected survey info */

	क्रमागत ath5k_पूर्णांक		ah_imr;

	काष्ठा ieee80211_channel *ah_current_channel;
	bool			ah_iq_cal_needed;
	bool			ah_single_chip;

	क्रमागत ath5k_version	ah_version;
	क्रमागत ath5k_radio	ah_radio;
	u32			ah_mac_srev;
	u16			ah_mac_version;
	u16			ah_phy_revision;
	u16			ah_radio_5ghz_revision;
	u16			ah_radio_2ghz_revision;

#घोषणा ah_modes		ah_capabilities.cap_mode
#घोषणा ah_ee_version		ah_capabilities.cap_eeprom.ee_version

	u8			ah_retry_दीर्घ;
	u8			ah_retry_लघु;

	bool			ah_use_32khz_घड़ी;

	u8			ah_coverage_class;
	bool			ah_ack_bitrate_high;
	u8			ah_bwmode;
	bool			ah_लघु_slot;

	/* Antenna Control */
	u32			ah_ant_ctl[AR5K_EEPROM_N_MODES][AR5K_ANT_MAX];
	u8			ah_ant_mode;
	u8			ah_tx_ant;
	u8			ah_def_ant;

	काष्ठा ath5k_capabilities ah_capabilities;

	काष्ठा ath5k_txq_info	ah_txq[AR5K_NUM_TX_QUEUES];
	u32			ah_txq_status;
	u32			ah_txq_imr_txok;
	u32			ah_txq_imr_txerr;
	u32			ah_txq_imr_txurn;
	u32			ah_txq_imr_txdesc;
	u32			ah_txq_imr_txeol;
	u32			ah_txq_imr_cbrorn;
	u32			ah_txq_imr_cbrurn;
	u32			ah_txq_imr_qtrig;
	u32			ah_txq_imr_nofrm;

	u32			ah_txq_isr_txok_all;
	u32			ah_txq_isr_txurn;
	u32			ah_txq_isr_qcborn;
	u32			ah_txq_isr_qcburn;
	u32			ah_txq_isr_qtrig;

	u32			*ah_rf_banks;
	माप_प्रकार			ah_rf_banks_size;
	माप_प्रकार			ah_rf_regs_count;
	काष्ठा ath5k_gain	ah_gain;
	u8			ah_offset[AR5K_MAX_RF_BANKS];


	काष्ठा अणु
		/* Temporary tables used क्रम पूर्णांकerpolation */
		u8		पंचांगpL[AR5K_EEPROM_N_PD_GAINS]
					[AR5K_EEPROM_POWER_TABLE_SIZE];
		u8		पंचांगpR[AR5K_EEPROM_N_PD_GAINS]
					[AR5K_EEPROM_POWER_TABLE_SIZE];
		u8		txp_pd_table[AR5K_EEPROM_POWER_TABLE_SIZE * 2];
		u16		txp_rates_घातer_table[AR5K_MAX_RATES];
		u8		txp_min_idx;
		bool		txp_tpc;
		/* Values in 0.25dB units */
		s16		txp_min_pwr;
		s16		txp_max_pwr;
		s16		txp_cur_pwr;
		/* Values in 0.5dB units */
		s16		txp_offset;
		s16		txp_ofdm;
		s16		txp_cck_ofdm_gainf_delta;
		/* Value in dB units */
		s16		txp_cck_ofdm_pwr_delta;
		bool		txp_setup;
		पूर्णांक		txp_requested;	/* Requested tx घातer in dBm */
	पूर्ण ah_txघातer;

	काष्ठा ath5k_nfcal_hist ah_nfcal_hist;

	/* average beacon RSSI in our BSS (used by ANI) */
	काष्ठा ewma_beacon_rssi	ah_beacon_rssi_avg;

	/* noise न्यूनमान from last periodic calibration */
	s32			ah_noise_न्यूनमान;

	/* Calibration बारtamp */
	अचिन्हित दीर्घ		ah_cal_next_full;
	अचिन्हित दीर्घ		ah_cal_next_लघु;
	अचिन्हित दीर्घ		ah_cal_next_ani;

	/* Calibration mask */
	u8			ah_cal_mask;

	/*
	 * Function poपूर्णांकers
	 */
	पूर्णांक (*ah_setup_tx_desc)(काष्ठा ath5k_hw *, काष्ठा ath5k_desc *,
		अचिन्हित पूर्णांक, अचिन्हित पूर्णांक, पूर्णांक, क्रमागत ath5k_pkt_type,
		अचिन्हित पूर्णांक, अचिन्हित पूर्णांक, अचिन्हित पूर्णांक, अचिन्हित पूर्णांक,
		अचिन्हित पूर्णांक, अचिन्हित पूर्णांक, अचिन्हित पूर्णांक, अचिन्हित पूर्णांक);
	पूर्णांक (*ah_proc_tx_desc)(काष्ठा ath5k_hw *, काष्ठा ath5k_desc *,
		काष्ठा ath5k_tx_status *);
	पूर्णांक (*ah_proc_rx_desc)(काष्ठा ath5k_hw *, काष्ठा ath5k_desc *,
		काष्ठा ath5k_rx_status *);
पूर्ण;

काष्ठा ath_bus_ops अणु
	क्रमागत ath_bus_type ath_bus_type;
	व्योम (*पढ़ो_cachesize)(काष्ठा ath_common *common, पूर्णांक *csz);
	bool (*eeprom_पढ़ो)(काष्ठा ath_common *common, u32 off, u16 *data);
	पूर्णांक (*eeprom_पढ़ो_mac)(काष्ठा ath5k_hw *ah, u8 *mac);
पूर्ण;

/*
 * Prototypes
 */
बाह्य स्थिर काष्ठा ieee80211_ops ath5k_hw_ops;

/* Initialization and detach functions */
पूर्णांक ath5k_hw_init(काष्ठा ath5k_hw *ah);
व्योम ath5k_hw_deinit(काष्ठा ath5k_hw *ah);

पूर्णांक ath5k_sysfs_रेजिस्टर(काष्ठा ath5k_hw *ah);
व्योम ath5k_sysfs_unरेजिस्टर(काष्ठा ath5k_hw *ah);

/*Chip id helper functions */
पूर्णांक ath5k_hw_पढ़ो_srev(काष्ठा ath5k_hw *ah);

/* LED functions */
पूर्णांक ath5k_init_leds(काष्ठा ath5k_hw *ah);
व्योम ath5k_led_enable(काष्ठा ath5k_hw *ah);
व्योम ath5k_led_off(काष्ठा ath5k_hw *ah);
व्योम ath5k_unरेजिस्टर_leds(काष्ठा ath5k_hw *ah);


/* Reset Functions */
पूर्णांक ath5k_hw_nic_wakeup(काष्ठा ath5k_hw *ah, काष्ठा ieee80211_channel *channel);
पूर्णांक ath5k_hw_on_hold(काष्ठा ath5k_hw *ah);
पूर्णांक ath5k_hw_reset(काष्ठा ath5k_hw *ah, क्रमागत nl80211_अगरtype op_mode,
	   काष्ठा ieee80211_channel *channel, bool fast, bool skip_pcu);
पूर्णांक ath5k_hw_रेजिस्टर_समयout(काष्ठा ath5k_hw *ah, u32 reg, u32 flag, u32 val,
			      bool is_set);
/* Power management functions */


/* Clock rate related functions */
अचिन्हित पूर्णांक ath5k_hw_htoघड़ी(काष्ठा ath5k_hw *ah, अचिन्हित पूर्णांक usec);
अचिन्हित पूर्णांक ath5k_hw_घड़ीtoh(काष्ठा ath5k_hw *ah, अचिन्हित पूर्णांक घड़ी);
व्योम ath5k_hw_set_घड़ीrate(काष्ठा ath5k_hw *ah);


/* DMA Related Functions */
व्योम ath5k_hw_start_rx_dma(काष्ठा ath5k_hw *ah);
u32 ath5k_hw_get_rxdp(काष्ठा ath5k_hw *ah);
पूर्णांक ath5k_hw_set_rxdp(काष्ठा ath5k_hw *ah, u32 phys_addr);
पूर्णांक ath5k_hw_start_tx_dma(काष्ठा ath5k_hw *ah, अचिन्हित पूर्णांक queue);
पूर्णांक ath5k_hw_stop_beacon_queue(काष्ठा ath5k_hw *ah, अचिन्हित पूर्णांक queue);
u32 ath5k_hw_get_txdp(काष्ठा ath5k_hw *ah, अचिन्हित पूर्णांक queue);
पूर्णांक ath5k_hw_set_txdp(काष्ठा ath5k_hw *ah, अचिन्हित पूर्णांक queue,
				u32 phys_addr);
पूर्णांक ath5k_hw_update_tx_triglevel(काष्ठा ath5k_hw *ah, bool increase);
/* Interrupt handling */
bool ath5k_hw_is_पूर्णांकr_pending(काष्ठा ath5k_hw *ah);
पूर्णांक ath5k_hw_get_isr(काष्ठा ath5k_hw *ah, क्रमागत ath5k_पूर्णांक *पूर्णांकerrupt_mask);
क्रमागत ath5k_पूर्णांक ath5k_hw_set_imr(काष्ठा ath5k_hw *ah, क्रमागत ath5k_पूर्णांक new_mask);
व्योम ath5k_hw_update_mib_counters(काष्ठा ath5k_hw *ah);
/* Init/Stop functions */
व्योम ath5k_hw_dma_init(काष्ठा ath5k_hw *ah);
पूर्णांक ath5k_hw_dma_stop(काष्ठा ath5k_hw *ah);

/* EEPROM access functions */
पूर्णांक ath5k_eeprom_init(काष्ठा ath5k_hw *ah);
व्योम ath5k_eeprom_detach(काष्ठा ath5k_hw *ah);
पूर्णांक ath5k_eeprom_mode_from_channel(काष्ठा ath5k_hw *ah,
		काष्ठा ieee80211_channel *channel);

/* Protocol Control Unit Functions */
/* Helpers */
पूर्णांक ath5k_hw_get_frame_duration(काष्ठा ath5k_hw *ah, क्रमागत nl80211_band band,
		पूर्णांक len, काष्ठा ieee80211_rate *rate, bool लघुpre);
अचिन्हित पूर्णांक ath5k_hw_get_शेष_slotसमय(काष्ठा ath5k_hw *ah);
अचिन्हित पूर्णांक ath5k_hw_get_शेष_sअगरs(काष्ठा ath5k_hw *ah);
पूर्णांक ath5k_hw_set_opmode(काष्ठा ath5k_hw *ah, क्रमागत nl80211_अगरtype opmode);
व्योम ath5k_hw_set_coverage_class(काष्ठा ath5k_hw *ah, u8 coverage_class);
/* RX filter control*/
पूर्णांक ath5k_hw_set_lladdr(काष्ठा ath5k_hw *ah, स्थिर u8 *mac);
व्योम ath5k_hw_set_bssid(काष्ठा ath5k_hw *ah);
व्योम ath5k_hw_set_bssid_mask(काष्ठा ath5k_hw *ah, स्थिर u8 *mask);
व्योम ath5k_hw_set_mcast_filter(काष्ठा ath5k_hw *ah, u32 filter0, u32 filter1);
u32 ath5k_hw_get_rx_filter(काष्ठा ath5k_hw *ah);
व्योम ath5k_hw_set_rx_filter(काष्ठा ath5k_hw *ah, u32 filter);
/* Receive (DRU) start/stop functions */
व्योम ath5k_hw_start_rx_pcu(काष्ठा ath5k_hw *ah);
व्योम ath5k_hw_stop_rx_pcu(काष्ठा ath5k_hw *ah);
/* Beacon control functions */
u64 ath5k_hw_get_tsf64(काष्ठा ath5k_hw *ah);
व्योम ath5k_hw_set_tsf64(काष्ठा ath5k_hw *ah, u64 tsf64);
व्योम ath5k_hw_reset_tsf(काष्ठा ath5k_hw *ah);
व्योम ath5k_hw_init_beacon_समयrs(काष्ठा ath5k_hw *ah, u32 next_beacon,
							u32 पूर्णांकerval);
bool ath5k_hw_check_beacon_समयrs(काष्ठा ath5k_hw *ah, पूर्णांक पूर्णांकval);
/* Init function */
व्योम ath5k_hw_pcu_init(काष्ठा ath5k_hw *ah, क्रमागत nl80211_अगरtype op_mode);

/* Queue Control Unit, DFS Control Unit Functions */
पूर्णांक ath5k_hw_get_tx_queueprops(काष्ठा ath5k_hw *ah, पूर्णांक queue,
			       काष्ठा ath5k_txq_info *queue_info);
पूर्णांक ath5k_hw_set_tx_queueprops(काष्ठा ath5k_hw *ah, पूर्णांक queue,
			       स्थिर काष्ठा ath5k_txq_info *queue_info);
पूर्णांक ath5k_hw_setup_tx_queue(काष्ठा ath5k_hw *ah,
			    क्रमागत ath5k_tx_queue queue_type,
			    काष्ठा ath5k_txq_info *queue_info);
व्योम ath5k_hw_set_tx_retry_limits(काष्ठा ath5k_hw *ah,
				  अचिन्हित पूर्णांक queue);
u32 ath5k_hw_num_tx_pending(काष्ठा ath5k_hw *ah, अचिन्हित पूर्णांक queue);
व्योम ath5k_hw_release_tx_queue(काष्ठा ath5k_hw *ah, अचिन्हित पूर्णांक queue);
पूर्णांक ath5k_hw_reset_tx_queue(काष्ठा ath5k_hw *ah, अचिन्हित पूर्णांक queue);
पूर्णांक ath5k_hw_set_अगरs_पूर्णांकervals(काष्ठा ath5k_hw *ah, अचिन्हित पूर्णांक slot_समय);
/* Init function */
पूर्णांक ath5k_hw_init_queues(काष्ठा ath5k_hw *ah);

/* Hardware Descriptor Functions */
पूर्णांक ath5k_hw_init_desc_functions(काष्ठा ath5k_hw *ah);
पूर्णांक ath5k_hw_setup_rx_desc(काष्ठा ath5k_hw *ah, काष्ठा ath5k_desc *desc,
			   u32 size, अचिन्हित पूर्णांक flags);
पूर्णांक ath5k_hw_setup_mrr_tx_desc(काष्ठा ath5k_hw *ah, काष्ठा ath5k_desc *desc,
	अचिन्हित पूर्णांक tx_rate1, u_पूर्णांक tx_tries1, u_पूर्णांक tx_rate2,
	u_पूर्णांक tx_tries2, अचिन्हित पूर्णांक tx_rate3, u_पूर्णांक tx_tries3);


/* GPIO Functions */
व्योम ath5k_hw_set_ledstate(काष्ठा ath5k_hw *ah, अचिन्हित पूर्णांक state);
पूर्णांक ath5k_hw_set_gpio_input(काष्ठा ath5k_hw *ah, u32 gpio);
पूर्णांक ath5k_hw_set_gpio_output(काष्ठा ath5k_hw *ah, u32 gpio);
u32 ath5k_hw_get_gpio(काष्ठा ath5k_hw *ah, u32 gpio);
पूर्णांक ath5k_hw_set_gpio(काष्ठा ath5k_hw *ah, u32 gpio, u32 val);
व्योम ath5k_hw_set_gpio_पूर्णांकr(काष्ठा ath5k_hw *ah, अचिन्हित पूर्णांक gpio,
			    u32 पूर्णांकerrupt_level);


/* RFसमाप्त Functions */
व्योम ath5k_rfसमाप्त_hw_start(काष्ठा ath5k_hw *ah);
व्योम ath5k_rfसमाप्त_hw_stop(काष्ठा ath5k_hw *ah);


/* Misc functions TODO: Cleanup */
पूर्णांक ath5k_hw_set_capabilities(काष्ठा ath5k_hw *ah);
पूर्णांक ath5k_hw_enable_pspoll(काष्ठा ath5k_hw *ah, u8 *bssid, u16 assoc_id);
पूर्णांक ath5k_hw_disable_pspoll(काष्ठा ath5k_hw *ah);


/* Initial रेजिस्टर settings functions */
पूर्णांक ath5k_hw_ग_लिखो_initvals(काष्ठा ath5k_hw *ah, u8 mode, bool change_channel);


/* PHY functions */
/* Misc PHY functions */
u16 ath5k_hw_radio_revision(काष्ठा ath5k_hw *ah, क्रमागत nl80211_band band);
पूर्णांक ath5k_hw_phy_disable(काष्ठा ath5k_hw *ah);
/* Gain_F optimization */
क्रमागत ath5k_rfgain ath5k_hw_gainf_calibrate(काष्ठा ath5k_hw *ah);
पूर्णांक ath5k_hw_rfgain_opt_init(काष्ठा ath5k_hw *ah);
/* PHY/RF channel functions */
bool ath5k_channel_ok(काष्ठा ath5k_hw *ah, काष्ठा ieee80211_channel *channel);
/* PHY calibration */
व्योम ath5k_hw_init_nfcal_hist(काष्ठा ath5k_hw *ah);
पूर्णांक ath5k_hw_phy_calibrate(काष्ठा ath5k_hw *ah,
			   काष्ठा ieee80211_channel *channel);
व्योम ath5k_hw_update_noise_न्यूनमान(काष्ठा ath5k_hw *ah);
/* Spur mitigation */
bool ath5k_hw_chan_has_spur_noise(काष्ठा ath5k_hw *ah,
				  काष्ठा ieee80211_channel *channel);
/* Antenna control */
व्योम ath5k_hw_set_antenna_mode(काष्ठा ath5k_hw *ah, u8 ant_mode);
व्योम ath5k_hw_set_antenna_चयन(काष्ठा ath5k_hw *ah, u8 ee_mode);
/* TX घातer setup */
पूर्णांक ath5k_hw_set_txघातer_limit(काष्ठा ath5k_hw *ah, u8 txघातer);
/* Init function */
पूर्णांक ath5k_hw_phy_init(काष्ठा ath5k_hw *ah, काष्ठा ieee80211_channel *channel,
				u8 mode, bool fast);

/*
 * Functions used पूर्णांकernally
 */

अटल अंतरभूत काष्ठा ath_common *ath5k_hw_common(काष्ठा ath5k_hw *ah)
अणु
	वापस &ah->common;
पूर्ण

अटल अंतरभूत काष्ठा ath_regulatory *ath5k_hw_regulatory(काष्ठा ath5k_hw *ah)
अणु
	वापस &(ath5k_hw_common(ah)->regulatory);
पूर्ण

#अगर_घोषित CONFIG_ATH5K_AHB
#घोषणा AR5K_AR2315_PCI_BASE	((व्योम __iomem *)0xb0100000)

अटल अंतरभूत व्योम __iomem *ath5k_ahb_reg(काष्ठा ath5k_hw *ah, u16 reg)
अणु
	/* On AR2315 and AR2317 the PCI घड़ी करोमुख्य रेजिस्टरs
	 * are outside of the WMAC रेजिस्टर space */
	अगर (unlikely((reg >= 0x4000) && (reg < 0x5000) &&
	    (ah->ah_mac_srev >= AR5K_SREV_AR2315_R6)))
		वापस AR5K_AR2315_PCI_BASE + reg;

	वापस ah->iobase + reg;
पूर्ण

अटल अंतरभूत u32 ath5k_hw_reg_पढ़ो(काष्ठा ath5k_hw *ah, u16 reg)
अणु
	वापस ioपढ़ो32(ath5k_ahb_reg(ah, reg));
पूर्ण

अटल अंतरभूत व्योम ath5k_hw_reg_ग_लिखो(काष्ठा ath5k_hw *ah, u32 val, u16 reg)
अणु
	ioग_लिखो32(val, ath5k_ahb_reg(ah, reg));
पूर्ण

#अन्यथा

अटल अंतरभूत u32 ath5k_hw_reg_पढ़ो(काष्ठा ath5k_hw *ah, u16 reg)
अणु
	वापस ioपढ़ो32(ah->iobase + reg);
पूर्ण

अटल अंतरभूत व्योम ath5k_hw_reg_ग_लिखो(काष्ठा ath5k_hw *ah, u32 val, u16 reg)
अणु
	ioग_लिखो32(val, ah->iobase + reg);
पूर्ण

#पूर्ण_अगर

अटल अंतरभूत क्रमागत ath_bus_type ath5k_get_bus_type(काष्ठा ath5k_hw *ah)
अणु
	वापस ath5k_hw_common(ah)->bus_ops->ath_bus_type;
पूर्ण

अटल अंतरभूत व्योम ath5k_पढ़ो_cachesize(काष्ठा ath_common *common, पूर्णांक *csz)
अणु
	common->bus_ops->पढ़ो_cachesize(common, csz);
पूर्ण

अटल अंतरभूत bool ath5k_hw_nvram_पढ़ो(काष्ठा ath5k_hw *ah, u32 off, u16 *data)
अणु
	काष्ठा ath_common *common = ath5k_hw_common(ah);
	वापस common->bus_ops->eeprom_पढ़ो(common, off, data);
पूर्ण

अटल अंतरभूत u32 ath5k_hw_bitswap(u32 val, अचिन्हित पूर्णांक bits)
अणु
	u32 retval = 0, bit, i;

	क्रम (i = 0; i < bits; i++) अणु
		bit = (val >> i) & 1;
		retval = (retval << 1) | bit;
	पूर्ण

	वापस retval;
पूर्ण

#पूर्ण_अगर
