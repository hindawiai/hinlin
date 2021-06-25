<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
	Copyright (C) 2004 - 2009 Ivo van Doorn <IvDoorn@gmail.com>
	Copyright (C) 2004 - 2009 Gertjan van Wingerde <gwingerde@gmail.com>
	<http://rt2x00.serialmonkey.com>

 */

/*
	Module: rt2x00lib
	Abstract: Data काष्ठाures and definitions क्रम the rt2x00lib module.
 */

#अगर_अघोषित RT2X00LIB_H
#घोषणा RT2X00LIB_H

/*
 * Interval defines
 */
#घोषणा WATCHDOG_INTERVAL	round_jअगरfies_relative(HZ)
#घोषणा LINK_TUNE_SECONDS	1
#घोषणा LINK_TUNE_INTERVAL	round_jअगरfies_relative(LINK_TUNE_SECONDS * HZ)
#घोषणा AGC_SECONDS		4
#घोषणा VCO_SECONDS		10

/*
 * rt2x00_rate: Per rate device inक्रमmation
 */
काष्ठा rt2x00_rate अणु
	अचिन्हित लघु flags;
#घोषणा DEV_RATE_CCK			0x0001
#घोषणा DEV_RATE_OFDM			0x0002
#घोषणा DEV_RATE_SHORT_PREAMBLE		0x0004

	अचिन्हित लघु bitrate; /* In 100kbit/s */
	अचिन्हित लघु ratemask;

	अचिन्हित लघु plcp;
	अचिन्हित लघु mcs;
पूर्ण;

बाह्य स्थिर काष्ठा rt2x00_rate rt2x00_supported_rates[12];

अटल अंतरभूत स्थिर काष्ठा rt2x00_rate *rt2x00_get_rate(स्थिर u16 hw_value)
अणु
	वापस &rt2x00_supported_rates[hw_value & 0xff];
पूर्ण

#घोषणा RATE_MCS(__mode, __mcs) \
	((((__mode) & 0x00ff) << 8) | ((__mcs) & 0x00ff))

अटल अंतरभूत पूर्णांक rt2x00_get_rate_mcs(स्थिर u16 mcs_value)
अणु
	वापस (mcs_value & 0x00ff);
पूर्ण

/*
 * Radio control handlers.
 */
पूर्णांक rt2x00lib_enable_radio(काष्ठा rt2x00_dev *rt2x00dev);
व्योम rt2x00lib_disable_radio(काष्ठा rt2x00_dev *rt2x00dev);

/*
 * Initialization handlers.
 */
पूर्णांक rt2x00lib_start(काष्ठा rt2x00_dev *rt2x00dev);
व्योम rt2x00lib_stop(काष्ठा rt2x00_dev *rt2x00dev);

/*
 * Configuration handlers.
 */
व्योम rt2x00lib_config_पूर्णांकf(काष्ठा rt2x00_dev *rt2x00dev,
			   काष्ठा rt2x00_पूर्णांकf *पूर्णांकf,
			   क्रमागत nl80211_अगरtype type,
			   स्थिर u8 *mac, स्थिर u8 *bssid);
व्योम rt2x00lib_config_erp(काष्ठा rt2x00_dev *rt2x00dev,
			  काष्ठा rt2x00_पूर्णांकf *पूर्णांकf,
			  काष्ठा ieee80211_bss_conf *conf,
			  u32 changed);
व्योम rt2x00lib_config_antenna(काष्ठा rt2x00_dev *rt2x00dev,
			      काष्ठा antenna_setup ant);
व्योम rt2x00lib_config(काष्ठा rt2x00_dev *rt2x00dev,
		      काष्ठा ieee80211_conf *conf,
		      स्थिर अचिन्हित पूर्णांक changed_flags);

/**
 * DOC: Queue handlers
 */

/**
 * rt2x00queue_alloc_rxskb - allocate a skb क्रम RX purposes.
 * @entry: The entry क्रम which the skb will be applicable.
 */
काष्ठा sk_buff *rt2x00queue_alloc_rxskb(काष्ठा queue_entry *entry, gfp_t gfp);

/**
 * rt2x00queue_मुक्त_skb - मुक्त a skb
 * @entry: The entry क्रम which the skb will be applicable.
 */
व्योम rt2x00queue_मुक्त_skb(काष्ठा queue_entry *entry);

/**
 * rt2x00queue_align_frame - Align 802.11 frame to 4-byte boundary
 * @skb: The skb to align
 *
 * Align the start of the 802.11 frame to a 4-byte boundary, this could
 * mean the payload is not aligned properly though.
 */
व्योम rt2x00queue_align_frame(काष्ठा sk_buff *skb);

/**
 * rt2x00queue_insert_l2pad - Align 802.11 header & payload to 4-byte boundary
 * @skb: The skb to align
 * @header_length: Length of 802.11 header
 *
 * Apply L2 padding to align both header and payload to 4-byte boundary
 */
व्योम rt2x00queue_insert_l2pad(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक header_length);

/**
 * rt2x00queue_insert_l2pad - Remove L2 padding from 802.11 frame
 * @skb: The skb to align
 * @header_length: Length of 802.11 header
 *
 * Remove L2 padding used to align both header and payload to 4-byte boundary,
 * by removing the L2 padding the header will no दीर्घer be 4-byte aligned.
 */
व्योम rt2x00queue_हटाओ_l2pad(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक header_length);

/**
 * rt2x00queue_ग_लिखो_tx_frame - Write TX frame to hardware
 * @queue: Queue over which the frame should be send
 * @skb: The skb to send
 * @local: frame is not from mac80211
 */
पूर्णांक rt2x00queue_ग_लिखो_tx_frame(काष्ठा data_queue *queue, काष्ठा sk_buff *skb,
			       काष्ठा ieee80211_sta *sta, bool local);

/**
 * rt2x00queue_update_beacon - Send new beacon from mac80211
 *	to hardware. Handles locking by itself (mutex).
 * @rt2x00dev: Poपूर्णांकer to &काष्ठा rt2x00_dev.
 * @vअगर: Interface क्रम which the beacon should be updated.
 */
पूर्णांक rt2x00queue_update_beacon(काष्ठा rt2x00_dev *rt2x00dev,
			      काष्ठा ieee80211_vअगर *vअगर);

/**
 * rt2x00queue_update_beacon_locked - Send new beacon from mac80211
 *	to hardware. Caller needs to ensure locking.
 * @rt2x00dev: Poपूर्णांकer to &काष्ठा rt2x00_dev.
 * @vअगर: Interface क्रम which the beacon should be updated.
 */
पूर्णांक rt2x00queue_update_beacon_locked(काष्ठा rt2x00_dev *rt2x00dev,
				     काष्ठा ieee80211_vअगर *vअगर);

/**
 * rt2x00queue_clear_beacon - Clear beacon in hardware
 * @rt2x00dev: Poपूर्णांकer to &काष्ठा rt2x00_dev.
 * @vअगर: Interface क्रम which the beacon should be updated.
 */
पूर्णांक rt2x00queue_clear_beacon(काष्ठा rt2x00_dev *rt2x00dev,
			     काष्ठा ieee80211_vअगर *vअगर);

/**
 * rt2x00queue_index_inc - Index incrementation function
 * @entry: Queue entry (&काष्ठा queue_entry) to perक्रमm the action on.
 * @index: Index type (&क्रमागत queue_index) to perक्रमm the action on.
 *
 * This function will increase the requested index on the entry's queue,
 * it will grab the appropriate locks and handle queue overflow events by
 * resetting the index to the start of the queue.
 */
व्योम rt2x00queue_index_inc(काष्ठा queue_entry *entry, क्रमागत queue_index index);

/**
 * rt2x00queue_init_queues - Initialize all data queues
 * @rt2x00dev: Poपूर्णांकer to &काष्ठा rt2x00_dev.
 *
 * This function will loop through all available queues to clear all
 * index numbers and set the queue entry to the correct initialization
 * state.
 */
व्योम rt2x00queue_init_queues(काष्ठा rt2x00_dev *rt2x00dev);

पूर्णांक rt2x00queue_initialize(काष्ठा rt2x00_dev *rt2x00dev);
व्योम rt2x00queue_uninitialize(काष्ठा rt2x00_dev *rt2x00dev);
पूर्णांक rt2x00queue_allocate(काष्ठा rt2x00_dev *rt2x00dev);
व्योम rt2x00queue_मुक्त(काष्ठा rt2x00_dev *rt2x00dev);

/**
 * rt2x00link_update_stats - Update link statistics from RX frame
 * @rt2x00dev: Poपूर्णांकer to &काष्ठा rt2x00_dev.
 * @skb: Received frame
 * @rxdesc: Received frame descriptor
 *
 * Update link statistics based on the inक्रमmation from the
 * received frame descriptor.
 */
व्योम rt2x00link_update_stats(काष्ठा rt2x00_dev *rt2x00dev,
			     काष्ठा sk_buff *skb,
			     काष्ठा rxकरोne_entry_desc *rxdesc);

/**
 * rt2x00link_start_tuner - Start periodic link tuner work
 * @rt2x00dev: Poपूर्णांकer to &काष्ठा rt2x00_dev.
 *
 * This start the link tuner periodic work, this work will
 * be executed periodically until &rt2x00link_stop_tuner has
 * been called.
 */
व्योम rt2x00link_start_tuner(काष्ठा rt2x00_dev *rt2x00dev);

/**
 * rt2x00link_stop_tuner - Stop periodic link tuner work
 * @rt2x00dev: Poपूर्णांकer to &काष्ठा rt2x00_dev.
 *
 * After this function completed the link tuner will not
 * be running until &rt2x00link_start_tuner is called.
 */
व्योम rt2x00link_stop_tuner(काष्ठा rt2x00_dev *rt2x00dev);

/**
 * rt2x00link_reset_tuner - Reset periodic link tuner work
 * @rt2x00dev: Poपूर्णांकer to &काष्ठा rt2x00_dev.
 * @antenna: Should the antenna tuning also be reset
 *
 * The VGC limit configured in the hardware will be reset to 0
 * which क्रमces the driver to rediscover the correct value क्रम
 * the current association. This is needed when configuration
 * options have changed which could drastically change the
 * SNR level or link quality (i.e. changing the antenna setting).
 *
 * Resetting the link tuner will also cause the periodic work counter
 * to be reset. Any driver which has a fixed limit on the number
 * of rounds the link tuner is supposed to work will accept the
 * tuner actions again अगर this limit was previously reached.
 *
 * If @antenna is set to true a the software antenna भागersity
 * tuning will also be reset.
 */
व्योम rt2x00link_reset_tuner(काष्ठा rt2x00_dev *rt2x00dev, bool antenna);

/**
 * rt2x00link_start_watchकरोg - Start periodic watchकरोg monitoring
 * @rt2x00dev: Poपूर्णांकer to &काष्ठा rt2x00_dev.
 *
 * This start the watchकरोg periodic work, this work will
 *be executed periodically until &rt2x00link_stop_watchकरोg has
 * been called.
 */
व्योम rt2x00link_start_watchकरोg(काष्ठा rt2x00_dev *rt2x00dev);

/**
 * rt2x00link_stop_watchकरोg - Stop periodic watchकरोg monitoring
 * @rt2x00dev: Poपूर्णांकer to &काष्ठा rt2x00_dev.
 *
 * After this function completed the watchकरोg monitoring will not
 * be running until &rt2x00link_start_watchकरोg is called.
 */
व्योम rt2x00link_stop_watchकरोg(काष्ठा rt2x00_dev *rt2x00dev);

/**
 * rt2x00link_रेजिस्टर - Initialize link tuning & watchकरोg functionality
 * @rt2x00dev: Poपूर्णांकer to &काष्ठा rt2x00_dev.
 *
 * Initialize work काष्ठाure and all link tuning and watchकरोg related
 * parameters. This will not start the periodic work itself.
 */
व्योम rt2x00link_रेजिस्टर(काष्ठा rt2x00_dev *rt2x00dev);

/*
 * Firmware handlers.
 */
#अगर_घोषित CONFIG_RT2X00_LIB_FIRMWARE
पूर्णांक rt2x00lib_load_firmware(काष्ठा rt2x00_dev *rt2x00dev);
व्योम rt2x00lib_मुक्त_firmware(काष्ठा rt2x00_dev *rt2x00dev);
#अन्यथा
अटल अंतरभूत पूर्णांक rt2x00lib_load_firmware(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम rt2x00lib_मुक्त_firmware(काष्ठा rt2x00_dev *rt2x00dev)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_RT2X00_LIB_FIRMWARE */

/*
 * Debugfs handlers.
 */
#अगर_घोषित CONFIG_RT2X00_LIB_DEBUGFS
व्योम rt2x00debug_रेजिस्टर(काष्ठा rt2x00_dev *rt2x00dev);
व्योम rt2x00debug_deरेजिस्टर(काष्ठा rt2x00_dev *rt2x00dev);
व्योम rt2x00debug_update_crypto(काष्ठा rt2x00_dev *rt2x00dev,
			       काष्ठा rxकरोne_entry_desc *rxdesc);
#अन्यथा
अटल अंतरभूत व्योम rt2x00debug_रेजिस्टर(काष्ठा rt2x00_dev *rt2x00dev)
अणु
पूर्ण

अटल अंतरभूत व्योम rt2x00debug_deरेजिस्टर(काष्ठा rt2x00_dev *rt2x00dev)
अणु
पूर्ण

अटल अंतरभूत व्योम rt2x00debug_update_crypto(काष्ठा rt2x00_dev *rt2x00dev,
					     काष्ठा rxकरोne_entry_desc *rxdesc)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_RT2X00_LIB_DEBUGFS */

/*
 * Crypto handlers.
 */
#अगर_घोषित CONFIG_RT2X00_LIB_CRYPTO
क्रमागत cipher rt2x00crypto_key_to_cipher(काष्ठा ieee80211_key_conf *key);
व्योम rt2x00crypto_create_tx_descriptor(काष्ठा rt2x00_dev *rt2x00dev,
				       काष्ठा sk_buff *skb,
				       काष्ठा txentry_desc *txdesc);
अचिन्हित पूर्णांक rt2x00crypto_tx_overhead(काष्ठा rt2x00_dev *rt2x00dev,
				      काष्ठा sk_buff *skb);
व्योम rt2x00crypto_tx_copy_iv(काष्ठा sk_buff *skb,
			     काष्ठा txentry_desc *txdesc);
व्योम rt2x00crypto_tx_हटाओ_iv(काष्ठा sk_buff *skb,
			       काष्ठा txentry_desc *txdesc);
व्योम rt2x00crypto_tx_insert_iv(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक header_length);
व्योम rt2x00crypto_rx_insert_iv(काष्ठा sk_buff *skb,
			       अचिन्हित पूर्णांक header_length,
			       काष्ठा rxकरोne_entry_desc *rxdesc);
#अन्यथा
अटल अंतरभूत क्रमागत cipher rt2x00crypto_key_to_cipher(काष्ठा ieee80211_key_conf *key)
अणु
	वापस CIPHER_NONE;
पूर्ण

अटल अंतरभूत व्योम rt2x00crypto_create_tx_descriptor(काष्ठा rt2x00_dev *rt2x00dev,
						     काष्ठा sk_buff *skb,
						     काष्ठा txentry_desc *txdesc)
अणु
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक rt2x00crypto_tx_overhead(काष्ठा rt2x00_dev *rt2x00dev,
						    काष्ठा sk_buff *skb)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम rt2x00crypto_tx_copy_iv(काष्ठा sk_buff *skb,
					   काष्ठा txentry_desc *txdesc)
अणु
पूर्ण

अटल अंतरभूत व्योम rt2x00crypto_tx_हटाओ_iv(काष्ठा sk_buff *skb,
					     काष्ठा txentry_desc *txdesc)
अणु
पूर्ण

अटल अंतरभूत व्योम rt2x00crypto_tx_insert_iv(काष्ठा sk_buff *skb,
					     अचिन्हित पूर्णांक header_length)
अणु
पूर्ण

अटल अंतरभूत व्योम rt2x00crypto_rx_insert_iv(काष्ठा sk_buff *skb,
					     अचिन्हित पूर्णांक header_length,
					     काष्ठा rxकरोne_entry_desc *rxdesc)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_RT2X00_LIB_CRYPTO */

/*
 * RFसमाप्त handlers.
 */
अटल अंतरभूत व्योम rt2x00rfसमाप्त_रेजिस्टर(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	अगर (test_bit(CAPABILITY_HW_BUTTON, &rt2x00dev->cap_flags))
		wiphy_rfसमाप्त_start_polling(rt2x00dev->hw->wiphy);
पूर्ण

अटल अंतरभूत व्योम rt2x00rfसमाप्त_unरेजिस्टर(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	अगर (test_bit(CAPABILITY_HW_BUTTON, &rt2x00dev->cap_flags))
		wiphy_rfसमाप्त_stop_polling(rt2x00dev->hw->wiphy);
पूर्ण

/*
 * LED handlers
 */
#अगर_घोषित CONFIG_RT2X00_LIB_LEDS
व्योम rt2x00leds_led_quality(काष्ठा rt2x00_dev *rt2x00dev, पूर्णांक rssi);
व्योम rt2x00led_led_activity(काष्ठा rt2x00_dev *rt2x00dev, bool enabled);
व्योम rt2x00leds_led_assoc(काष्ठा rt2x00_dev *rt2x00dev, bool enabled);
व्योम rt2x00leds_led_radio(काष्ठा rt2x00_dev *rt2x00dev, bool enabled);
व्योम rt2x00leds_रेजिस्टर(काष्ठा rt2x00_dev *rt2x00dev);
व्योम rt2x00leds_unरेजिस्टर(काष्ठा rt2x00_dev *rt2x00dev);
व्योम rt2x00leds_suspend(काष्ठा rt2x00_dev *rt2x00dev);
व्योम rt2x00leds_resume(काष्ठा rt2x00_dev *rt2x00dev);
#अन्यथा
अटल अंतरभूत व्योम rt2x00leds_led_quality(काष्ठा rt2x00_dev *rt2x00dev,
					  पूर्णांक rssi)
अणु
पूर्ण

अटल अंतरभूत व्योम rt2x00led_led_activity(काष्ठा rt2x00_dev *rt2x00dev,
					  bool enabled)
अणु
पूर्ण

अटल अंतरभूत व्योम rt2x00leds_led_assoc(काष्ठा rt2x00_dev *rt2x00dev,
					bool enabled)
अणु
पूर्ण

अटल अंतरभूत व्योम rt2x00leds_led_radio(काष्ठा rt2x00_dev *rt2x00dev,
					bool enabled)
अणु
पूर्ण

अटल अंतरभूत व्योम rt2x00leds_रेजिस्टर(काष्ठा rt2x00_dev *rt2x00dev)
अणु
पूर्ण

अटल अंतरभूत व्योम rt2x00leds_unरेजिस्टर(काष्ठा rt2x00_dev *rt2x00dev)
अणु
पूर्ण

अटल अंतरभूत व्योम rt2x00leds_suspend(काष्ठा rt2x00_dev *rt2x00dev)
अणु
पूर्ण

अटल अंतरभूत व्योम rt2x00leds_resume(काष्ठा rt2x00_dev *rt2x00dev)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_RT2X00_LIB_LEDS */

#पूर्ण_अगर /* RT2X00LIB_H */
