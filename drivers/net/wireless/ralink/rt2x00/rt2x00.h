<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
	Copyright (C) 2010 Willow Garage <http://www.willowgarage.com>
	Copyright (C) 2004 - 2010 Ivo van Doorn <IvDoorn@gmail.com>
	Copyright (C) 2004 - 2009 Gertjan van Wingerde <gwingerde@gmail.com>
	<http://rt2x00.serialmonkey.com>

 */

/*
	Module: rt2x00
	Abstract: rt2x00 global inक्रमmation.
 */

#अगर_अघोषित RT2X00_H
#घोषणा RT2X00_H

#समावेश <linux/bitops.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/firmware.h>
#समावेश <linux/leds.h>
#समावेश <linux/mutex.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/kfअगरo.h>
#समावेश <linux/hrसमयr.h>
#समावेश <linux/average.h>
#समावेश <linux/usb.h>
#समावेश <linux/clk.h>

#समावेश <net/mac80211.h>

#समावेश "rt2x00debug.h"
#समावेश "rt2x00dump.h"
#समावेश "rt2x00leds.h"
#समावेश "rt2x00reg.h"
#समावेश "rt2x00queue.h"

/*
 * Module inक्रमmation.
 */
#घोषणा DRV_VERSION	"2.3.0"
#घोषणा DRV_PROJECT	"http://rt2x00.serialmonkey.com"

/* Debug definitions.
 * Debug output has to be enabled during compile समय.
 */
#अगर_घोषित CONFIG_RT2X00_DEBUG
#घोषणा DEBUG
#पूर्ण_अगर /* CONFIG_RT2X00_DEBUG */

/* Utility prपूर्णांकing macros
 * rt2x00_probe_err is क्रम messages when rt2x00_dev is uninitialized
 */
#घोषणा rt2x00_probe_err(fmt, ...)					\
	prपूर्णांकk(KERN_ERR KBUILD_MODNAME ": %s: Error - " fmt,		\
	       __func__, ##__VA_ARGS__)
#घोषणा rt2x00_err(dev, fmt, ...)					\
	wiphy_err_ratelimited((dev)->hw->wiphy, "%s: Error - " fmt,	\
		  __func__, ##__VA_ARGS__)
#घोषणा rt2x00_warn(dev, fmt, ...)					\
	wiphy_warn_ratelimited((dev)->hw->wiphy, "%s: Warning - " fmt,	\
		   __func__, ##__VA_ARGS__)
#घोषणा rt2x00_info(dev, fmt, ...)					\
	wiphy_info((dev)->hw->wiphy, "%s: Info - " fmt,			\
		   __func__, ##__VA_ARGS__)

/* Various debug levels */
#घोषणा rt2x00_dbg(dev, fmt, ...)					\
	wiphy_dbg((dev)->hw->wiphy, "%s: Debug - " fmt,			\
		  __func__, ##__VA_ARGS__)
#घोषणा rt2x00_eeprom_dbg(dev, fmt, ...)				\
	wiphy_dbg((dev)->hw->wiphy, "%s: EEPROM recovery - " fmt,	\
		  __func__, ##__VA_ARGS__)

/*
 * Duration calculations
 * The rate variable passed is: 100kbs.
 * To convert from bytes to bits we multiply size with 8,
 * then the size is multiplied with 10 to make the
 * real rate -> rate argument correction.
 */
#घोषणा GET_DURATION(__size, __rate)	(((__size) * 8 * 10) / (__rate))
#घोषणा GET_DURATION_RES(__size, __rate)(((__size) * 8 * 10) % (__rate))

/*
 * Determine the number of L2 padding bytes required between the header and
 * the payload.
 */
#घोषणा L2PAD_SIZE(__hdrlen)	(-(__hdrlen) & 3)

/*
 * Determine the alignment requirement,
 * to make sure the 802.11 payload is padded to a 4-byte boundrary
 * we must determine the address of the payload and calculate the
 * amount of bytes needed to move the data.
 */
#घोषणा ALIGN_SIZE(__skb, __header) \
	(((अचिन्हित दीर्घ)((__skb)->data + (__header))) & 3)

/*
 * Constants क्रम extra TX headroom क्रम alignment purposes.
 */
#घोषणा RT2X00_ALIGN_SIZE	4 /* Only whole frame needs alignment */
#घोषणा RT2X00_L2PAD_SIZE	8 /* Both header & payload need alignment */

/*
 * Standard timing and size defines.
 * These values should follow the ieee80211 specअगरications.
 */
#घोषणा ACK_SIZE		14
#घोषणा IEEE80211_HEADER	24
#घोषणा PLCP			48
#घोषणा BEACON			100
#घोषणा PREAMBLE		144
#घोषणा SHORT_PREAMBLE		72
#घोषणा SLOT_TIME		20
#घोषणा SHORT_SLOT_TIME		9
#घोषणा SIFS			10
#घोषणा PIFS			(SIFS + SLOT_TIME)
#घोषणा SHORT_PIFS		(SIFS + SHORT_SLOT_TIME)
#घोषणा DIFS			(PIFS + SLOT_TIME)
#घोषणा SHORT_DIFS		(SHORT_PIFS + SHORT_SLOT_TIME)
#घोषणा EIFS			(SIFS + DIFS + \
				  GET_DURATION(IEEE80211_HEADER + ACK_SIZE, 10))
#घोषणा SHORT_EIFS		(SIFS + SHORT_DIFS + \
				  GET_DURATION(IEEE80211_HEADER + ACK_SIZE, 10))

क्रमागत rt2x00_chip_पूर्णांकf अणु
	RT2X00_CHIP_INTF_PCI,
	RT2X00_CHIP_INTF_PCIE,
	RT2X00_CHIP_INTF_USB,
	RT2X00_CHIP_INTF_SOC,
पूर्ण;

/*
 * Chipset identअगरication
 * The chipset on the device is composed of a RT and RF chip.
 * The chipset combination is important क्रम determining device capabilities.
 */
काष्ठा rt2x00_chip अणु
	u16 rt;
#घोषणा RT2460		0x2460
#घोषणा RT2560		0x2560
#घोषणा RT2570		0x2570
#घोषणा RT2661		0x2661
#घोषणा RT2573		0x2573
#घोषणा RT2860		0x2860	/* 2.4GHz */
#घोषणा RT2872		0x2872	/* WSOC */
#घोषणा RT2883		0x2883	/* WSOC */
#घोषणा RT3070		0x3070
#घोषणा RT3071		0x3071
#घोषणा RT3090		0x3090	/* 2.4GHz PCIe */
#घोषणा RT3290		0x3290
#घोषणा RT3352		0x3352  /* WSOC */
#घोषणा RT3390		0x3390
#घोषणा RT3572		0x3572
#घोषणा RT3593		0x3593
#घोषणा RT3883		0x3883	/* WSOC */
#घोषणा RT5350		0x5350  /* WSOC 2.4GHz */
#घोषणा RT5390		0x5390  /* 2.4GHz */
#घोषणा RT5392		0x5392  /* 2.4GHz */
#घोषणा RT5592		0x5592
#घोषणा RT6352		0x6352  /* WSOC 2.4GHz */

	u16 rf;
	u16 rev;

	क्रमागत rt2x00_chip_पूर्णांकf पूर्णांकf;
पूर्ण;

/*
 * RF रेजिस्टर values that beदीर्घ to a particular channel.
 */
काष्ठा rf_channel अणु
	पूर्णांक channel;
	u32 rf1;
	u32 rf2;
	u32 rf3;
	u32 rf4;
पूर्ण;

/*
 * Inक्रमmation काष्ठाure क्रम channel survey.
 */
काष्ठा rt2x00_chan_survey अणु
	u64 समय_idle;
	u64 समय_busy;
	u64 समय_ext_busy;
पूर्ण;

/*
 * Channel inक्रमmation काष्ठाure
 */
काष्ठा channel_info अणु
	अचिन्हित पूर्णांक flags;
#घोषणा GEOGRAPHY_ALLOWED	0x00000001

	लघु max_घातer;
	लघु शेष_घातer1;
	लघु शेष_घातer2;
	लघु शेष_घातer3;
पूर्ण;

/*
 * Antenna setup values.
 */
काष्ठा antenna_setup अणु
	क्रमागत antenna rx;
	क्रमागत antenna tx;
	u8 rx_chain_num;
	u8 tx_chain_num;
पूर्ण;

/*
 * Quality statistics about the currently active link.
 */
काष्ठा link_qual अणु
	/*
	 * Statistics required क्रम Link tuning by driver
	 * The rssi value is provided by rt2x00lib during the
	 * link_tuner() callback function.
	 * The false_cca field is filled during the link_stats()
	 * callback function and could be used during the
	 * link_tuner() callback function.
	 */
	पूर्णांक rssi;
	पूर्णांक false_cca;

	/*
	 * VGC levels
	 * Hardware driver will tune the VGC level during each call
	 * to the link_tuner() callback function. This vgc_level is
	 * is determined based on the link quality statistics like
	 * average RSSI and the false CCA count.
	 *
	 * In some हालs the drivers need to dअगरferentiate between
	 * the currently "desired" VGC level and the level configured
	 * in the hardware. The latter is important to reduce the
	 * number of BBP रेजिस्टर पढ़ोs to reduce रेजिस्टर access
	 * overhead. For this reason we store both values here.
	 */
	u8 vgc_level;
	u8 vgc_level_reg;

	/*
	 * Statistics required क्रम Signal quality calculation.
	 * These fields might be changed during the link_stats()
	 * callback function.
	 */
	पूर्णांक rx_success;
	पूर्णांक rx_failed;
	पूर्णांक tx_success;
	पूर्णांक tx_failed;
पूर्ण;

DECLARE_EWMA(rssi, 10, 8)

/*
 * Antenna settings about the currently active link.
 */
काष्ठा link_ant अणु
	/*
	 * Antenna flags
	 */
	अचिन्हित पूर्णांक flags;
#घोषणा ANTENNA_RX_DIVERSITY	0x00000001
#घोषणा ANTENNA_TX_DIVERSITY	0x00000002
#घोषणा ANTENNA_MODE_SAMPLE	0x00000004

	/*
	 * Currently active TX/RX antenna setup.
	 * When software भागersity is used, this will indicate
	 * which antenna is actually used at this समय.
	 */
	काष्ठा antenna_setup active;

	/*
	 * RSSI history inक्रमmation क्रम the antenna.
	 * Used to determine when to चयन antenna
	 * when using software भागersity.
	 */
	पूर्णांक rssi_history;

	/*
	 * Current RSSI average of the currently active antenna.
	 * Similar to the avg_rssi in the link_qual काष्ठाure
	 * this value is updated by using the walking average.
	 */
	काष्ठा ewma_rssi rssi_ant;
पूर्ण;

/*
 * To optimize the quality of the link we need to store
 * the quality of received frames and periodically
 * optimize the link.
 */
काष्ठा link अणु
	/*
	 * Link tuner counter
	 * The number of बार the link has been tuned
	 * since the radio has been चयनed on.
	 */
	u32 count;

	/*
	 * Quality measurement values.
	 */
	काष्ठा link_qual qual;

	/*
	 * TX/RX antenna setup.
	 */
	काष्ठा link_ant ant;

	/*
	 * Currently active average RSSI value
	 */
	काष्ठा ewma_rssi avg_rssi;

	/*
	 * Work काष्ठाure क्रम scheduling periodic link tuning.
	 */
	काष्ठा delayed_work work;

	/*
	 * Work काष्ठाure क्रम scheduling periodic watchकरोg monitoring.
	 * This work must be scheduled on the kernel workqueue, जबतक
	 * all other work काष्ठाures must be queued on the mac80211
	 * workqueue. This guarantees that the watchकरोg can schedule
	 * other work काष्ठाures and रुको क्रम their completion in order
	 * to bring the device/driver back पूर्णांकo the desired state.
	 */
	काष्ठा delayed_work watchकरोg_work;
	अचिन्हित पूर्णांक watchकरोg_पूर्णांकerval;
	bool watchकरोg_disabled;

	/*
	 * Work काष्ठाure क्रम scheduling periodic AGC adjusपंचांगents.
	 */
	काष्ठा delayed_work agc_work;

	/*
	 * Work काष्ठाure क्रम scheduling periodic VCO calibration.
	 */
	काष्ठा delayed_work vco_work;
पूर्ण;

क्रमागत rt2x00_delayed_flags अणु
	DELAYED_UPDATE_BEACON,
पूर्ण;

/*
 * Interface काष्ठाure
 * Per पूर्णांकerface configuration details, this काष्ठाure
 * is allocated as the निजी data क्रम ieee80211_vअगर.
 */
काष्ठा rt2x00_पूर्णांकf अणु
	/*
	 * beacon->skb must be रक्षित with the mutex.
	 */
	काष्ठा mutex beacon_skb_mutex;

	/*
	 * Entry in the beacon queue which beदीर्घs to
	 * this पूर्णांकerface. Each पूर्णांकerface has its own
	 * dedicated beacon entry.
	 */
	काष्ठा queue_entry *beacon;
	bool enable_beacon;

	/*
	 * Actions that needed rescheduling.
	 */
	अचिन्हित दीर्घ delayed_flags;

	/*
	 * Software sequence counter, this is only required
	 * क्रम hardware which करोesn't support hardware
	 * sequence counting.
	 */
	atomic_t seqno;
पूर्ण;

अटल अंतरभूत काष्ठा rt2x00_पूर्णांकf* vअगर_to_पूर्णांकf(काष्ठा ieee80211_vअगर *vअगर)
अणु
	वापस (काष्ठा rt2x00_पूर्णांकf *)vअगर->drv_priv;
पूर्ण

/**
 * काष्ठा hw_mode_spec: Hardware specअगरications काष्ठाure
 *
 * Details about the supported modes, rates and channels
 * of a particular chipset. This is used by rt2x00lib
 * to build the ieee80211_hw_mode array क्रम mac80211.
 *
 * @supported_bands: Biपंचांगask contained the supported bands (2.4GHz, 5.2GHz).
 * @supported_rates: Rate types which are supported (CCK, OFDM).
 * @num_channels: Number of supported channels. This is used as array size
 *	क्रम @tx_घातer_a, @tx_घातer_bg and @channels.
 * @channels: Device/chipset specअगरic channel values (See &काष्ठा rf_channel).
 * @channels_info: Additional inक्रमmation क्रम channels (See &काष्ठा channel_info).
 * @ht: Driver HT Capabilities (See &ieee80211_sta_ht_cap).
 */
काष्ठा hw_mode_spec अणु
	अचिन्हित पूर्णांक supported_bands;
#घोषणा SUPPORT_BAND_2GHZ	0x00000001
#घोषणा SUPPORT_BAND_5GHZ	0x00000002

	अचिन्हित पूर्णांक supported_rates;
#घोषणा SUPPORT_RATE_CCK	0x00000001
#घोषणा SUPPORT_RATE_OFDM	0x00000002

	अचिन्हित पूर्णांक num_channels;
	स्थिर काष्ठा rf_channel *channels;
	स्थिर काष्ठा channel_info *channels_info;

	काष्ठा ieee80211_sta_ht_cap ht;
पूर्ण;

/*
 * Configuration काष्ठाure wrapper around the
 * mac80211 configuration काष्ठाure.
 * When mac80211 configures the driver, rt2x00lib
 * can precalculate values which are equal क्रम all
 * rt2x00 drivers. Those values can be stored in here.
 */
काष्ठा rt2x00lib_conf अणु
	काष्ठा ieee80211_conf *conf;

	काष्ठा rf_channel rf;
	काष्ठा channel_info channel;
पूर्ण;

/*
 * Configuration काष्ठाure क्रम erp settings.
 */
काष्ठा rt2x00lib_erp अणु
	पूर्णांक लघु_preamble;
	पूर्णांक cts_protection;

	u32 basic_rates;

	पूर्णांक slot_समय;

	लघु sअगरs;
	लघु pअगरs;
	लघु dअगरs;
	लघु eअगरs;

	u16 beacon_पूर्णांक;
	u16 ht_opmode;
पूर्ण;

/*
 * Configuration काष्ठाure क्रम hardware encryption.
 */
काष्ठा rt2x00lib_crypto अणु
	क्रमागत cipher cipher;

	क्रमागत set_key_cmd cmd;
	स्थिर u8 *address;

	u32 bssidx;

	u8 key[16];
	u8 tx_mic[8];
	u8 rx_mic[8];

	पूर्णांक wcid;
पूर्ण;

/*
 * Configuration काष्ठाure wrapper around the
 * rt2x00 पूर्णांकerface configuration handler.
 */
काष्ठा rt2x00पूर्णांकf_conf अणु
	/*
	 * Interface type
	 */
	क्रमागत nl80211_अगरtype type;

	/*
	 * TSF sync value, this is dependent on the operation type.
	 */
	क्रमागत tsf_sync sync;

	/*
	 * The MAC and BSSID addresses are simple array of bytes,
	 * these arrays are little endian, so when sending the addresses
	 * to the drivers, copy the it पूर्णांकo a endian-चिन्हित variable.
	 *
	 * Note that all devices (except rt2500usb) have 32 bits
	 * रेजिस्टर word sizes. This means that whatever variable we
	 * pass _must_ be a multiple of 32 bits. Otherwise the device
	 * might not accept what we are sending to it.
	 * This will also make it easier क्रम the driver to ग_लिखो
	 * the data to the device.
	 */
	__le32 mac[2];
	__le32 bssid[2];
पूर्ण;

/*
 * Private काष्ठाure क्रम storing STA details
 * wcid: Wireless Client ID
 */
काष्ठा rt2x00_sta अणु
	पूर्णांक wcid;
पूर्ण;

अटल अंतरभूत काष्ठा rt2x00_sta* sta_to_rt2x00_sta(काष्ठा ieee80211_sta *sta)
अणु
	वापस (काष्ठा rt2x00_sta *)sta->drv_priv;
पूर्ण

/*
 * rt2x00lib callback functions.
 */
काष्ठा rt2x00lib_ops अणु
	/*
	 * Interrupt handlers.
	 */
	irq_handler_t irq_handler;

	/*
	 * TX status tasklet handler.
	 */
	व्योम (*txstatus_tasklet) (काष्ठा tasklet_काष्ठा *t);
	व्योम (*pretbtt_tasklet) (काष्ठा tasklet_काष्ठा *t);
	व्योम (*tbtt_tasklet) (काष्ठा tasklet_काष्ठा *t);
	व्योम (*rxकरोne_tasklet) (काष्ठा tasklet_काष्ठा *t);
	व्योम (*स्वतःwake_tasklet) (काष्ठा tasklet_काष्ठा *t);

	/*
	 * Device init handlers.
	 */
	पूर्णांक (*probe_hw) (काष्ठा rt2x00_dev *rt2x00dev);
	अक्षर *(*get_firmware_name) (काष्ठा rt2x00_dev *rt2x00dev);
	पूर्णांक (*check_firmware) (काष्ठा rt2x00_dev *rt2x00dev,
			       स्थिर u8 *data, स्थिर माप_प्रकार len);
	पूर्णांक (*load_firmware) (काष्ठा rt2x00_dev *rt2x00dev,
			      स्थिर u8 *data, स्थिर माप_प्रकार len);

	/*
	 * Device initialization/deinitialization handlers.
	 */
	पूर्णांक (*initialize) (काष्ठा rt2x00_dev *rt2x00dev);
	व्योम (*uninitialize) (काष्ठा rt2x00_dev *rt2x00dev);

	/*
	 * queue initialization handlers
	 */
	bool (*get_entry_state) (काष्ठा queue_entry *entry);
	व्योम (*clear_entry) (काष्ठा queue_entry *entry);

	/*
	 * Radio control handlers.
	 */
	पूर्णांक (*set_device_state) (काष्ठा rt2x00_dev *rt2x00dev,
				 क्रमागत dev_state state);
	पूर्णांक (*rfसमाप्त_poll) (काष्ठा rt2x00_dev *rt2x00dev);
	व्योम (*link_stats) (काष्ठा rt2x00_dev *rt2x00dev,
			    काष्ठा link_qual *qual);
	व्योम (*reset_tuner) (काष्ठा rt2x00_dev *rt2x00dev,
			     काष्ठा link_qual *qual);
	व्योम (*link_tuner) (काष्ठा rt2x00_dev *rt2x00dev,
			    काष्ठा link_qual *qual, स्थिर u32 count);
	व्योम (*gain_calibration) (काष्ठा rt2x00_dev *rt2x00dev);
	व्योम (*vco_calibration) (काष्ठा rt2x00_dev *rt2x00dev);

	/*
	 * Data queue handlers.
	 */
	व्योम (*watchकरोg) (काष्ठा rt2x00_dev *rt2x00dev);
	व्योम (*start_queue) (काष्ठा data_queue *queue);
	व्योम (*kick_queue) (काष्ठा data_queue *queue);
	व्योम (*stop_queue) (काष्ठा data_queue *queue);
	व्योम (*flush_queue) (काष्ठा data_queue *queue, bool drop);
	व्योम (*tx_dma_करोne) (काष्ठा queue_entry *entry);

	/*
	 * TX control handlers
	 */
	व्योम (*ग_लिखो_tx_desc) (काष्ठा queue_entry *entry,
			       काष्ठा txentry_desc *txdesc);
	व्योम (*ग_लिखो_tx_data) (काष्ठा queue_entry *entry,
			       काष्ठा txentry_desc *txdesc);
	व्योम (*ग_लिखो_beacon) (काष्ठा queue_entry *entry,
			      काष्ठा txentry_desc *txdesc);
	व्योम (*clear_beacon) (काष्ठा queue_entry *entry);
	पूर्णांक (*get_tx_data_len) (काष्ठा queue_entry *entry);

	/*
	 * RX control handlers
	 */
	व्योम (*fill_rxकरोne) (काष्ठा queue_entry *entry,
			     काष्ठा rxकरोne_entry_desc *rxdesc);

	/*
	 * Configuration handlers.
	 */
	पूर्णांक (*config_shared_key) (काष्ठा rt2x00_dev *rt2x00dev,
				  काष्ठा rt2x00lib_crypto *crypto,
				  काष्ठा ieee80211_key_conf *key);
	पूर्णांक (*config_pairwise_key) (काष्ठा rt2x00_dev *rt2x00dev,
				    काष्ठा rt2x00lib_crypto *crypto,
				    काष्ठा ieee80211_key_conf *key);
	व्योम (*config_filter) (काष्ठा rt2x00_dev *rt2x00dev,
			       स्थिर अचिन्हित पूर्णांक filter_flags);
	व्योम (*config_पूर्णांकf) (काष्ठा rt2x00_dev *rt2x00dev,
			     काष्ठा rt2x00_पूर्णांकf *पूर्णांकf,
			     काष्ठा rt2x00पूर्णांकf_conf *conf,
			     स्थिर अचिन्हित पूर्णांक flags);
#घोषणा CONFIG_UPDATE_TYPE		( 1 << 1 )
#घोषणा CONFIG_UPDATE_MAC		( 1 << 2 )
#घोषणा CONFIG_UPDATE_BSSID		( 1 << 3 )

	व्योम (*config_erp) (काष्ठा rt2x00_dev *rt2x00dev,
			    काष्ठा rt2x00lib_erp *erp,
			    u32 changed);
	व्योम (*config_ant) (काष्ठा rt2x00_dev *rt2x00dev,
			    काष्ठा antenna_setup *ant);
	व्योम (*config) (काष्ठा rt2x00_dev *rt2x00dev,
			काष्ठा rt2x00lib_conf *libconf,
			स्थिर अचिन्हित पूर्णांक changed_flags);
	व्योम (*pre_reset_hw) (काष्ठा rt2x00_dev *rt2x00dev);
	पूर्णांक (*sta_add) (काष्ठा rt2x00_dev *rt2x00dev,
			काष्ठा ieee80211_vअगर *vअगर,
			काष्ठा ieee80211_sta *sta);
	पूर्णांक (*sta_हटाओ) (काष्ठा rt2x00_dev *rt2x00dev,
			   काष्ठा ieee80211_sta *sta);
पूर्ण;

/*
 * rt2x00 driver callback operation काष्ठाure.
 */
काष्ठा rt2x00_ops अणु
	स्थिर अक्षर *name;
	स्थिर अचिन्हित पूर्णांक drv_data_size;
	स्थिर अचिन्हित पूर्णांक max_ap_पूर्णांकf;
	स्थिर अचिन्हित पूर्णांक eeprom_size;
	स्थिर अचिन्हित पूर्णांक rf_size;
	स्थिर अचिन्हित पूर्णांक tx_queues;
	व्योम (*queue_init)(काष्ठा data_queue *queue);
	स्थिर काष्ठा rt2x00lib_ops *lib;
	स्थिर व्योम *drv;
	स्थिर काष्ठा ieee80211_ops *hw;
#अगर_घोषित CONFIG_RT2X00_LIB_DEBUGFS
	स्थिर काष्ठा rt2x00debug *debugfs;
#पूर्ण_अगर /* CONFIG_RT2X00_LIB_DEBUGFS */
पूर्ण;

/*
 * rt2x00 state flags
 */
क्रमागत rt2x00_state_flags अणु
	/*
	 * Device flags
	 */
	DEVICE_STATE_PRESENT,
	DEVICE_STATE_REGISTERED_HW,
	DEVICE_STATE_INITIALIZED,
	DEVICE_STATE_STARTED,
	DEVICE_STATE_ENABLED_RADIO,
	DEVICE_STATE_SCANNING,
	DEVICE_STATE_FLUSHING,
	DEVICE_STATE_RESET,

	/*
	 * Driver configuration
	 */
	CONFIG_CHANNEL_HT40,
	CONFIG_POWERSAVING,
	CONFIG_HT_DISABLED,
	CONFIG_MONITORING,

	/*
	 * Mark we currently are sequentially पढ़ोing TX_STA_FIFO रेजिस्टर
	 * FIXME: this is क्रम only rt2800usb, should go to निजी data
	 */
	TX_STATUS_READING,
पूर्ण;

/*
 * rt2x00 capability flags
 */
क्रमागत rt2x00_capability_flags अणु
	/*
	 * Requirements
	 */
	REQUIRE_FIRMWARE,
	REQUIRE_BEACON_GUARD,
	REQUIRE_ATIM_QUEUE,
	REQUIRE_DMA,
	REQUIRE_COPY_IV,
	REQUIRE_L2PAD,
	REQUIRE_TXSTATUS_FIFO,
	REQUIRE_TASKLET_CONTEXT,
	REQUIRE_SW_SEQNO,
	REQUIRE_HT_TX_DESC,
	REQUIRE_PS_AUTOWAKE,
	REQUIRE_DELAYED_RFKILL,

	/*
	 * Capabilities
	 */
	CAPABILITY_HW_BUTTON,
	CAPABILITY_HW_CRYPTO,
	CAPABILITY_POWER_LIMIT,
	CAPABILITY_CONTROL_FILTERS,
	CAPABILITY_CONTROL_FILTER_PSPOLL,
	CAPABILITY_PRE_TBTT_INTERRUPT,
	CAPABILITY_LINK_TUNING,
	CAPABILITY_FRAME_TYPE,
	CAPABILITY_RF_SEQUENCE,
	CAPABILITY_EXTERNAL_LNA_A,
	CAPABILITY_EXTERNAL_LNA_BG,
	CAPABILITY_DOUBLE_ANTENNA,
	CAPABILITY_BT_COEXIST,
	CAPABILITY_VCO_RECALIBRATION,
	CAPABILITY_EXTERNAL_PA_TX0,
	CAPABILITY_EXTERNAL_PA_TX1,
	CAPABILITY_RESTART_HW,
पूर्ण;

/*
 * Interface combinations
 */
क्रमागत अणु
	IF_COMB_AP = 0,
	NUM_IF_COMB,
पूर्ण;

/*
 * rt2x00 device काष्ठाure.
 */
काष्ठा rt2x00_dev अणु
	/*
	 * Device काष्ठाure.
	 * The काष्ठाure stored in here depends on the
	 * प्रणाली bus (PCI or USB).
	 * When accessing this variable, the rt2x00dev_अणुpci,usbपूर्ण
	 * macros should be used क्रम correct typecasting.
	 */
	काष्ठा device *dev;

	/*
	 * Callback functions.
	 */
	स्थिर काष्ठा rt2x00_ops *ops;

	/*
	 * Driver data.
	 */
	व्योम *drv_data;

	/*
	 * IEEE80211 control काष्ठाure.
	 */
	काष्ठा ieee80211_hw *hw;
	काष्ठा ieee80211_supported_band bands[NUM_NL80211_BANDS];
	काष्ठा rt2x00_chan_survey *chan_survey;
	क्रमागत nl80211_band curr_band;
	पूर्णांक curr_freq;

	/*
	 * If enabled, the debugfs पूर्णांकerface काष्ठाures
	 * required क्रम deregistration of debugfs.
	 */
#अगर_घोषित CONFIG_RT2X00_LIB_DEBUGFS
	काष्ठा rt2x00debug_पूर्णांकf *debugfs_पूर्णांकf;
#पूर्ण_अगर /* CONFIG_RT2X00_LIB_DEBUGFS */

	/*
	 * LED काष्ठाure क्रम changing the LED status
	 * by mac8011 or the kernel.
	 */
#अगर_घोषित CONFIG_RT2X00_LIB_LEDS
	काष्ठा rt2x00_led led_radio;
	काष्ठा rt2x00_led led_assoc;
	काष्ठा rt2x00_led led_qual;
	u16 led_mcu_reg;
#पूर्ण_अगर /* CONFIG_RT2X00_LIB_LEDS */

	/*
	 * Device state flags.
	 * In these flags the current status is stored.
	 * Access to these flags should occur atomically.
	 */
	अचिन्हित दीर्घ flags;

	/*
	 * Device capabiltiy flags.
	 * In these flags the device/driver capabilities are stored.
	 * Access to these flags should occur non-atomically.
	 */
	अचिन्हित दीर्घ cap_flags;

	/*
	 * Device inक्रमmation, Bus IRQ and name (PCI, SoC)
	 */
	पूर्णांक irq;
	स्थिर अक्षर *name;

	/*
	 * Chipset identअगरication.
	 */
	काष्ठा rt2x00_chip chip;

	/*
	 * hw capability specअगरications.
	 */
	काष्ठा hw_mode_spec spec;

	/*
	 * This is the शेष TX/RX antenna setup as indicated
	 * by the device's EEPROM.
	 */
	काष्ठा antenna_setup शेष_ant;

	/*
	 * Register poपूर्णांकers
	 * csr.base: CSR base रेजिस्टर address. (PCI)
	 * csr.cache: CSR cache क्रम usb_control_msg. (USB)
	 */
	जोड़ csr अणु
		व्योम __iomem *base;
		व्योम *cache;
	पूर्ण csr;

	/*
	 * Mutex to protect रेजिस्टर accesses.
	 * For PCI and USB devices it protects against concurrent indirect
	 * रेजिस्टर access (BBP, RF, MCU) since accessing those
	 * रेजिस्टरs require multiple calls to the CSR रेजिस्टरs.
	 * For USB devices it also protects the csr_cache since that
	 * field is used क्रम normal CSR access and it cannot support
	 * multiple callers simultaneously.
	 */
	काष्ठा mutex csr_mutex;

	/*
	 * Mutex to synchronize config and link tuner.
	 */
	काष्ठा mutex conf_mutex;
	/*
	 * Current packet filter configuration क्रम the device.
	 * This contains all currently active FIF_* flags send
	 * to us by mac80211 during configure_filter().
	 */
	अचिन्हित पूर्णांक packet_filter;

	/*
	 * Interface details:
	 *  - Open ap पूर्णांकerface count.
	 *  - Open sta पूर्णांकerface count.
	 *  - Association count.
	 *  - Beaconing enabled count.
	 */
	अचिन्हित पूर्णांक पूर्णांकf_ap_count;
	अचिन्हित पूर्णांक पूर्णांकf_sta_count;
	अचिन्हित पूर्णांक पूर्णांकf_associated;
	अचिन्हित पूर्णांक पूर्णांकf_beaconing;

	/*
	 * Interface combinations
	 */
	काष्ठा ieee80211_अगरace_limit अगर_limits_ap;
	काष्ठा ieee80211_अगरace_combination अगर_combinations[NUM_IF_COMB];

	/*
	 * Link quality
	 */
	काष्ठा link link;

	/*
	 * EEPROM data.
	 */
	__le16 *eeprom;

	/*
	 * Active RF रेजिस्टर values.
	 * These are stored here so we करोn't need
	 * to पढ़ो the rf रेजिस्टरs and can directly
	 * use this value instead.
	 * This field should be accessed by using
	 * rt2x00_rf_पढ़ो() and rt2x00_rf_ग_लिखो().
	 */
	u32 *rf;

	/*
	 * LNA gain
	 */
	लघु lna_gain;

	/*
	 * Current TX घातer value.
	 */
	u16 tx_घातer;

	/*
	 * Current retry values.
	 */
	u8 लघु_retry;
	u8 दीर्घ_retry;

	/*
	 * Rssi <-> Dbm offset
	 */
	u8 rssi_offset;

	/*
	 * Frequency offset.
	 */
	u8 freq_offset;

	/*
	 * Association id.
	 */
	u16 aid;

	/*
	 * Beacon पूर्णांकerval.
	 */
	u16 beacon_पूर्णांक;

	/**
	 * Timestamp of last received beacon
	 */
	अचिन्हित दीर्घ last_beacon;

	/*
	 * Low level statistics which will have
	 * to be kept up to date जबतक device is running.
	 */
	काष्ठा ieee80211_low_level_stats low_level_stats;

	/**
	 * Work queue क्रम all work which should not be placed
	 * on the mac80211 workqueue (because of dependencies
	 * between various work काष्ठाures).
	 */
	काष्ठा workqueue_काष्ठा *workqueue;

	/*
	 * Scheduled work.
	 * NOTE: पूर्णांकf_work will use ieee80211_iterate_active_पूर्णांकerfaces()
	 * which means it cannot be placed on the hw->workqueue
	 * due to RTNL locking requirements.
	 */
	काष्ठा work_काष्ठा पूर्णांकf_work;

	/**
	 * Scheduled work क्रम TX/RX करोne handling (USB devices)
	 */
	काष्ठा work_काष्ठा rxकरोne_work;
	काष्ठा work_काष्ठा txकरोne_work;

	/*
	 * Powersaving work
	 */
	काष्ठा delayed_work स्वतःwakeup_work;
	काष्ठा work_काष्ठा sleep_work;

	/*
	 * Data queue arrays क्रम RX, TX, Beacon and ATIM.
	 */
	अचिन्हित पूर्णांक data_queues;
	काष्ठा data_queue *rx;
	काष्ठा data_queue *tx;
	काष्ठा data_queue *bcn;
	काष्ठा data_queue *atim;

	/*
	 * Firmware image.
	 */
	स्थिर काष्ठा firmware *fw;

	/*
	 * FIFO क्रम storing tx status reports between isr and tasklet.
	 */
	DECLARE_KFIFO_PTR(txstatus_fअगरo, u32);

	/*
	 * Timer to ensure tx status reports are पढ़ो (rt2800usb).
	 */
	काष्ठा hrसमयr txstatus_समयr;

	/*
	 * Tasklet क्रम processing tx status reports (rt2800pci).
	 */
	काष्ठा tasklet_काष्ठा txstatus_tasklet;
	काष्ठा tasklet_काष्ठा pretbtt_tasklet;
	काष्ठा tasklet_काष्ठा tbtt_tasklet;
	काष्ठा tasklet_काष्ठा rxकरोne_tasklet;
	काष्ठा tasklet_काष्ठा स्वतःwake_tasklet;

	/*
	 * Used क्रम VCO periodic calibration.
	 */
	पूर्णांक rf_channel;

	/*
	 * Protect the पूर्णांकerrupt mask रेजिस्टर.
	 */
	spinlock_t irqmask_lock;

	/*
	 * List of BlockAckReq TX entries that need driver BlockAck processing.
	 */
	काष्ठा list_head bar_list;
	spinlock_t bar_list_lock;

	/* Extra TX headroom required क्रम alignment purposes. */
	अचिन्हित पूर्णांक extra_tx_headroom;

	काष्ठा usb_anchor *anchor;
	अचिन्हित पूर्णांक num_proto_errs;

	/* Clock क्रम System On Chip devices. */
	काष्ठा clk *clk;
पूर्ण;

काष्ठा rt2x00_bar_list_entry अणु
	काष्ठा list_head list;
	काष्ठा rcu_head head;

	काष्ठा queue_entry *entry;
	पूर्णांक block_acked;

	/* Relevant parts of the IEEE80211 BAR header */
	__u8 ra[6];
	__u8 ta[6];
	__le16 control;
	__le16 start_seq_num;
पूर्ण;

/*
 * Register defines.
 * Some रेजिस्टरs require multiple attempts beक्रमe success,
 * in those हालs REGISTER_BUSY_COUNT attempts should be
 * taken with a REGISTER_BUSY_DELAY पूर्णांकerval. Due to USB
 * bus delays, we करो not have to loop so many बार to रुको
 * क्रम valid रेजिस्टर value on that bus.
 */
#घोषणा REGISTER_BUSY_COUNT	100
#घोषणा REGISTER_USB_BUSY_COUNT 20
#घोषणा REGISTER_BUSY_DELAY	100

/*
 * Generic RF access.
 * The RF is being accessed by word index.
 */
अटल अंतरभूत u32 rt2x00_rf_पढ़ो(काष्ठा rt2x00_dev *rt2x00dev,
				 स्थिर अचिन्हित पूर्णांक word)
अणु
	BUG_ON(word < 1 || word > rt2x00dev->ops->rf_size / माप(u32));
	वापस rt2x00dev->rf[word - 1];
पूर्ण

अटल अंतरभूत व्योम rt2x00_rf_ग_लिखो(काष्ठा rt2x00_dev *rt2x00dev,
				   स्थिर अचिन्हित पूर्णांक word, u32 data)
अणु
	BUG_ON(word < 1 || word > rt2x00dev->ops->rf_size / माप(u32));
	rt2x00dev->rf[word - 1] = data;
पूर्ण

/*
 * Generic EEPROM access. The EEPROM is being accessed by word or byte index.
 */
अटल अंतरभूत व्योम *rt2x00_eeprom_addr(काष्ठा rt2x00_dev *rt2x00dev,
				       स्थिर अचिन्हित पूर्णांक word)
अणु
	वापस (व्योम *)&rt2x00dev->eeprom[word];
पूर्ण

अटल अंतरभूत u16 rt2x00_eeprom_पढ़ो(काष्ठा rt2x00_dev *rt2x00dev,
				     स्थिर अचिन्हित पूर्णांक word)
अणु
	वापस le16_to_cpu(rt2x00dev->eeprom[word]);
पूर्ण

अटल अंतरभूत व्योम rt2x00_eeprom_ग_लिखो(काष्ठा rt2x00_dev *rt2x00dev,
				       स्थिर अचिन्हित पूर्णांक word, u16 data)
अणु
	rt2x00dev->eeprom[word] = cpu_to_le16(data);
पूर्ण

अटल अंतरभूत u8 rt2x00_eeprom_byte(काष्ठा rt2x00_dev *rt2x00dev,
				    स्थिर अचिन्हित पूर्णांक byte)
अणु
	वापस *(((u8 *)rt2x00dev->eeprom) + byte);
पूर्ण

/*
 * Chipset handlers
 */
अटल अंतरभूत व्योम rt2x00_set_chip(काष्ठा rt2x00_dev *rt2x00dev,
				   स्थिर u16 rt, स्थिर u16 rf, स्थिर u16 rev)
अणु
	rt2x00dev->chip.rt = rt;
	rt2x00dev->chip.rf = rf;
	rt2x00dev->chip.rev = rev;

	rt2x00_info(rt2x00dev, "Chipset detected - rt: %04x, rf: %04x, rev: %04x\n",
		    rt2x00dev->chip.rt, rt2x00dev->chip.rf,
		    rt2x00dev->chip.rev);
पूर्ण

अटल अंतरभूत व्योम rt2x00_set_rt(काष्ठा rt2x00_dev *rt2x00dev,
				 स्थिर u16 rt, स्थिर u16 rev)
अणु
	rt2x00dev->chip.rt = rt;
	rt2x00dev->chip.rev = rev;

	rt2x00_info(rt2x00dev, "RT chipset %04x, rev %04x detected\n",
		    rt2x00dev->chip.rt, rt2x00dev->chip.rev);
पूर्ण

अटल अंतरभूत व्योम rt2x00_set_rf(काष्ठा rt2x00_dev *rt2x00dev, स्थिर u16 rf)
अणु
	rt2x00dev->chip.rf = rf;

	rt2x00_info(rt2x00dev, "RF chipset %04x detected\n",
		    rt2x00dev->chip.rf);
पूर्ण

अटल अंतरभूत bool rt2x00_rt(काष्ठा rt2x00_dev *rt2x00dev, स्थिर u16 rt)
अणु
	वापस (rt2x00dev->chip.rt == rt);
पूर्ण

अटल अंतरभूत bool rt2x00_rf(काष्ठा rt2x00_dev *rt2x00dev, स्थिर u16 rf)
अणु
	वापस (rt2x00dev->chip.rf == rf);
पूर्ण

अटल अंतरभूत u16 rt2x00_rev(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	वापस rt2x00dev->chip.rev;
पूर्ण

अटल अंतरभूत bool rt2x00_rt_rev(काष्ठा rt2x00_dev *rt2x00dev,
				 स्थिर u16 rt, स्थिर u16 rev)
अणु
	वापस (rt2x00_rt(rt2x00dev, rt) && rt2x00_rev(rt2x00dev) == rev);
पूर्ण

अटल अंतरभूत bool rt2x00_rt_rev_lt(काष्ठा rt2x00_dev *rt2x00dev,
				    स्थिर u16 rt, स्थिर u16 rev)
अणु
	वापस (rt2x00_rt(rt2x00dev, rt) && rt2x00_rev(rt2x00dev) < rev);
पूर्ण

अटल अंतरभूत bool rt2x00_rt_rev_gte(काष्ठा rt2x00_dev *rt2x00dev,
				     स्थिर u16 rt, स्थिर u16 rev)
अणु
	वापस (rt2x00_rt(rt2x00dev, rt) && rt2x00_rev(rt2x00dev) >= rev);
पूर्ण

अटल अंतरभूत व्योम rt2x00_set_chip_पूर्णांकf(काष्ठा rt2x00_dev *rt2x00dev,
					क्रमागत rt2x00_chip_पूर्णांकf पूर्णांकf)
अणु
	rt2x00dev->chip.पूर्णांकf = पूर्णांकf;
पूर्ण

अटल अंतरभूत bool rt2x00_पूर्णांकf(काष्ठा rt2x00_dev *rt2x00dev,
			       क्रमागत rt2x00_chip_पूर्णांकf पूर्णांकf)
अणु
	वापस (rt2x00dev->chip.पूर्णांकf == पूर्णांकf);
पूर्ण

अटल अंतरभूत bool rt2x00_is_pci(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	वापस rt2x00_पूर्णांकf(rt2x00dev, RT2X00_CHIP_INTF_PCI) ||
	       rt2x00_पूर्णांकf(rt2x00dev, RT2X00_CHIP_INTF_PCIE);
पूर्ण

अटल अंतरभूत bool rt2x00_is_pcie(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	वापस rt2x00_पूर्णांकf(rt2x00dev, RT2X00_CHIP_INTF_PCIE);
पूर्ण

अटल अंतरभूत bool rt2x00_is_usb(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	वापस rt2x00_पूर्णांकf(rt2x00dev, RT2X00_CHIP_INTF_USB);
पूर्ण

अटल अंतरभूत bool rt2x00_is_soc(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	वापस rt2x00_पूर्णांकf(rt2x00dev, RT2X00_CHIP_INTF_SOC);
पूर्ण

/* Helpers क्रम capability flags */

अटल अंतरभूत bool
rt2x00_has_cap_flag(काष्ठा rt2x00_dev *rt2x00dev,
		    क्रमागत rt2x00_capability_flags cap_flag)
अणु
	वापस test_bit(cap_flag, &rt2x00dev->cap_flags);
पूर्ण

अटल अंतरभूत bool
rt2x00_has_cap_hw_crypto(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	वापस rt2x00_has_cap_flag(rt2x00dev, CAPABILITY_HW_CRYPTO);
पूर्ण

अटल अंतरभूत bool
rt2x00_has_cap_घातer_limit(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	वापस rt2x00_has_cap_flag(rt2x00dev, CAPABILITY_POWER_LIMIT);
पूर्ण

अटल अंतरभूत bool
rt2x00_has_cap_control_filters(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	वापस rt2x00_has_cap_flag(rt2x00dev, CAPABILITY_CONTROL_FILTERS);
पूर्ण

अटल अंतरभूत bool
rt2x00_has_cap_control_filter_pspoll(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	वापस rt2x00_has_cap_flag(rt2x00dev, CAPABILITY_CONTROL_FILTER_PSPOLL);
पूर्ण

अटल अंतरभूत bool
rt2x00_has_cap_pre_tbtt_पूर्णांकerrupt(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	वापस rt2x00_has_cap_flag(rt2x00dev, CAPABILITY_PRE_TBTT_INTERRUPT);
पूर्ण

अटल अंतरभूत bool
rt2x00_has_cap_link_tuning(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	वापस rt2x00_has_cap_flag(rt2x00dev, CAPABILITY_LINK_TUNING);
पूर्ण

अटल अंतरभूत bool
rt2x00_has_cap_frame_type(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	वापस rt2x00_has_cap_flag(rt2x00dev, CAPABILITY_FRAME_TYPE);
पूर्ण

अटल अंतरभूत bool
rt2x00_has_cap_rf_sequence(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	वापस rt2x00_has_cap_flag(rt2x00dev, CAPABILITY_RF_SEQUENCE);
पूर्ण

अटल अंतरभूत bool
rt2x00_has_cap_बाह्यal_lna_a(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	वापस rt2x00_has_cap_flag(rt2x00dev, CAPABILITY_EXTERNAL_LNA_A);
पूर्ण

अटल अंतरभूत bool
rt2x00_has_cap_बाह्यal_lna_bg(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	वापस rt2x00_has_cap_flag(rt2x00dev, CAPABILITY_EXTERNAL_LNA_BG);
पूर्ण

अटल अंतरभूत bool
rt2x00_has_cap_द्विगुन_antenna(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	वापस rt2x00_has_cap_flag(rt2x00dev, CAPABILITY_DOUBLE_ANTENNA);
पूर्ण

अटल अंतरभूत bool
rt2x00_has_cap_bt_coexist(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	वापस rt2x00_has_cap_flag(rt2x00dev, CAPABILITY_BT_COEXIST);
पूर्ण

अटल अंतरभूत bool
rt2x00_has_cap_vco_recalibration(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	वापस rt2x00_has_cap_flag(rt2x00dev, CAPABILITY_VCO_RECALIBRATION);
पूर्ण

अटल अंतरभूत bool
rt2x00_has_cap_restart_hw(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	वापस rt2x00_has_cap_flag(rt2x00dev, CAPABILITY_RESTART_HW);
पूर्ण

/**
 * rt2x00queue_map_txskb - Map a skb पूर्णांकo DMA क्रम TX purposes.
 * @entry: Poपूर्णांकer to &काष्ठा queue_entry
 *
 * Returns -ENOMEM अगर mapping fail, 0 otherwise.
 */
पूर्णांक rt2x00queue_map_txskb(काष्ठा queue_entry *entry);

/**
 * rt2x00queue_unmap_skb - Unmap a skb from DMA.
 * @entry: Poपूर्णांकer to &काष्ठा queue_entry
 */
व्योम rt2x00queue_unmap_skb(काष्ठा queue_entry *entry);

/**
 * rt2x00queue_get_tx_queue - Convert tx queue index to queue poपूर्णांकer
 * @rt2x00dev: Poपूर्णांकer to &काष्ठा rt2x00_dev.
 * @queue: rt2x00 queue index (see &क्रमागत data_queue_qid).
 *
 * Returns शून्य क्रम non tx queues.
 */
अटल अंतरभूत काष्ठा data_queue *
rt2x00queue_get_tx_queue(काष्ठा rt2x00_dev *rt2x00dev,
			 स्थिर क्रमागत data_queue_qid queue)
अणु
	अगर (queue < rt2x00dev->ops->tx_queues && rt2x00dev->tx)
		वापस &rt2x00dev->tx[queue];

	अगर (queue == QID_ATIM)
		वापस rt2x00dev->atim;

	वापस शून्य;
पूर्ण

/**
 * rt2x00queue_get_entry - Get queue entry where the given index poपूर्णांकs to.
 * @queue: Poपूर्णांकer to &काष्ठा data_queue from where we obtain the entry.
 * @index: Index identअगरier क्रम obtaining the correct index.
 */
काष्ठा queue_entry *rt2x00queue_get_entry(काष्ठा data_queue *queue,
					  क्रमागत queue_index index);

/**
 * rt2x00queue_छोड़ो_queue - Pause a data queue
 * @queue: Poपूर्णांकer to &काष्ठा data_queue.
 *
 * This function will छोड़ो the data queue locally, preventing
 * new frames to be added to the queue (जबतक the hardware is
 * still allowed to run).
 */
व्योम rt2x00queue_छोड़ो_queue(काष्ठा data_queue *queue);

/**
 * rt2x00queue_unछोड़ो_queue - unछोड़ो a data queue
 * @queue: Poपूर्णांकer to &काष्ठा data_queue.
 *
 * This function will unछोड़ो the data queue locally, allowing
 * new frames to be added to the queue again.
 */
व्योम rt2x00queue_unछोड़ो_queue(काष्ठा data_queue *queue);

/**
 * rt2x00queue_start_queue - Start a data queue
 * @queue: Poपूर्णांकer to &काष्ठा data_queue.
 *
 * This function will start handling all pending frames in the queue.
 */
व्योम rt2x00queue_start_queue(काष्ठा data_queue *queue);

/**
 * rt2x00queue_stop_queue - Halt a data queue
 * @queue: Poपूर्णांकer to &काष्ठा data_queue.
 *
 * This function will stop all pending frames in the queue.
 */
व्योम rt2x00queue_stop_queue(काष्ठा data_queue *queue);

/**
 * rt2x00queue_flush_queue - Flush a data queue
 * @queue: Poपूर्णांकer to &काष्ठा data_queue.
 * @drop: True to drop all pending frames.
 *
 * This function will flush the queue. After this call
 * the queue is guaranteed to be empty.
 */
व्योम rt2x00queue_flush_queue(काष्ठा data_queue *queue, bool drop);

/**
 * rt2x00queue_start_queues - Start all data queues
 * @rt2x00dev: Poपूर्णांकer to &काष्ठा rt2x00_dev.
 *
 * This function will loop through all available queues to start them
 */
व्योम rt2x00queue_start_queues(काष्ठा rt2x00_dev *rt2x00dev);

/**
 * rt2x00queue_stop_queues - Halt all data queues
 * @rt2x00dev: Poपूर्णांकer to &काष्ठा rt2x00_dev.
 *
 * This function will loop through all available queues to stop
 * any pending frames.
 */
व्योम rt2x00queue_stop_queues(काष्ठा rt2x00_dev *rt2x00dev);

/**
 * rt2x00queue_flush_queues - Flush all data queues
 * @rt2x00dev: Poपूर्णांकer to &काष्ठा rt2x00_dev.
 * @drop: True to drop all pending frames.
 *
 * This function will loop through all available queues to flush
 * any pending frames.
 */
व्योम rt2x00queue_flush_queues(काष्ठा rt2x00_dev *rt2x00dev, bool drop);

/*
 * Debugfs handlers.
 */
/**
 * rt2x00debug_dump_frame - Dump a frame to userspace through debugfs.
 * @rt2x00dev: Poपूर्णांकer to &काष्ठा rt2x00_dev.
 * @type: The type of frame that is being dumped.
 * @entry: The queue entry containing the frame to be dumped.
 */
#अगर_घोषित CONFIG_RT2X00_LIB_DEBUGFS
व्योम rt2x00debug_dump_frame(काष्ठा rt2x00_dev *rt2x00dev,
			    क्रमागत rt2x00_dump_type type, काष्ठा queue_entry *entry);
#अन्यथा
अटल अंतरभूत व्योम rt2x00debug_dump_frame(काष्ठा rt2x00_dev *rt2x00dev,
					  क्रमागत rt2x00_dump_type type,
					  काष्ठा queue_entry *entry)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_RT2X00_LIB_DEBUGFS */

/*
 * Utility functions.
 */
u32 rt2x00lib_get_bssidx(काष्ठा rt2x00_dev *rt2x00dev,
			 काष्ठा ieee80211_vअगर *vअगर);
व्योम rt2x00lib_set_mac_address(काष्ठा rt2x00_dev *rt2x00dev, u8 *eeprom_mac_addr);

/*
 * Interrupt context handlers.
 */
व्योम rt2x00lib_beaconकरोne(काष्ठा rt2x00_dev *rt2x00dev);
व्योम rt2x00lib_pretbtt(काष्ठा rt2x00_dev *rt2x00dev);
व्योम rt2x00lib_dmastart(काष्ठा queue_entry *entry);
व्योम rt2x00lib_dmaकरोne(काष्ठा queue_entry *entry);
व्योम rt2x00lib_txकरोne(काष्ठा queue_entry *entry,
		      काष्ठा txकरोne_entry_desc *txdesc);
व्योम rt2x00lib_txकरोne_nomatch(काष्ठा queue_entry *entry,
			      काष्ठा txकरोne_entry_desc *txdesc);
व्योम rt2x00lib_txकरोne_noinfo(काष्ठा queue_entry *entry, u32 status);
व्योम rt2x00lib_rxकरोne(काष्ठा queue_entry *entry, gfp_t gfp);

/*
 * mac80211 handlers.
 */
व्योम rt2x00mac_tx(काष्ठा ieee80211_hw *hw,
		  काष्ठा ieee80211_tx_control *control,
		  काष्ठा sk_buff *skb);
पूर्णांक rt2x00mac_start(काष्ठा ieee80211_hw *hw);
व्योम rt2x00mac_stop(काष्ठा ieee80211_hw *hw);
व्योम rt2x00mac_reconfig_complete(काष्ठा ieee80211_hw *hw,
				 क्रमागत ieee80211_reconfig_type reconfig_type);
पूर्णांक rt2x00mac_add_पूर्णांकerface(काष्ठा ieee80211_hw *hw,
			    काष्ठा ieee80211_vअगर *vअगर);
व्योम rt2x00mac_हटाओ_पूर्णांकerface(काष्ठा ieee80211_hw *hw,
				काष्ठा ieee80211_vअगर *vअगर);
पूर्णांक rt2x00mac_config(काष्ठा ieee80211_hw *hw, u32 changed);
व्योम rt2x00mac_configure_filter(काष्ठा ieee80211_hw *hw,
				अचिन्हित पूर्णांक changed_flags,
				अचिन्हित पूर्णांक *total_flags,
				u64 multicast);
पूर्णांक rt2x00mac_set_tim(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_sta *sta,
		      bool set);
#अगर_घोषित CONFIG_RT2X00_LIB_CRYPTO
पूर्णांक rt2x00mac_set_key(काष्ठा ieee80211_hw *hw, क्रमागत set_key_cmd cmd,
		      काष्ठा ieee80211_vअगर *vअगर, काष्ठा ieee80211_sta *sta,
		      काष्ठा ieee80211_key_conf *key);
#अन्यथा
#घोषणा rt2x00mac_set_key	शून्य
#पूर्ण_अगर /* CONFIG_RT2X00_LIB_CRYPTO */
व्योम rt2x00mac_sw_scan_start(काष्ठा ieee80211_hw *hw,
			     काष्ठा ieee80211_vअगर *vअगर,
			     स्थिर u8 *mac_addr);
व्योम rt2x00mac_sw_scan_complete(काष्ठा ieee80211_hw *hw,
				काष्ठा ieee80211_vअगर *vअगर);
पूर्णांक rt2x00mac_get_stats(काष्ठा ieee80211_hw *hw,
			काष्ठा ieee80211_low_level_stats *stats);
व्योम rt2x00mac_bss_info_changed(काष्ठा ieee80211_hw *hw,
				काष्ठा ieee80211_vअगर *vअगर,
				काष्ठा ieee80211_bss_conf *bss_conf,
				u32 changes);
पूर्णांक rt2x00mac_conf_tx(काष्ठा ieee80211_hw *hw,
		      काष्ठा ieee80211_vअगर *vअगर, u16 queue,
		      स्थिर काष्ठा ieee80211_tx_queue_params *params);
व्योम rt2x00mac_rfसमाप्त_poll(काष्ठा ieee80211_hw *hw);
व्योम rt2x00mac_flush(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
		     u32 queues, bool drop);
पूर्णांक rt2x00mac_set_antenna(काष्ठा ieee80211_hw *hw, u32 tx_ant, u32 rx_ant);
पूर्णांक rt2x00mac_get_antenna(काष्ठा ieee80211_hw *hw, u32 *tx_ant, u32 *rx_ant);
व्योम rt2x00mac_get_ringparam(काष्ठा ieee80211_hw *hw,
			     u32 *tx, u32 *tx_max, u32 *rx, u32 *rx_max);
bool rt2x00mac_tx_frames_pending(काष्ठा ieee80211_hw *hw);

/*
 * Driver allocation handlers.
 */
पूर्णांक rt2x00lib_probe_dev(काष्ठा rt2x00_dev *rt2x00dev);
व्योम rt2x00lib_हटाओ_dev(काष्ठा rt2x00_dev *rt2x00dev);

पूर्णांक rt2x00lib_suspend(काष्ठा rt2x00_dev *rt2x00dev);
पूर्णांक rt2x00lib_resume(काष्ठा rt2x00_dev *rt2x00dev);

#पूर्ण_अगर /* RT2X00_H */
