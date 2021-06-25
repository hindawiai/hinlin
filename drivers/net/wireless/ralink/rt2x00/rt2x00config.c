<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
	Copyright (C) 2004 - 2009 Ivo van Doorn <IvDoorn@gmail.com>
	<http://rt2x00.serialmonkey.com>

 */

/*
	Module: rt2x00lib
	Abstract: rt2x00 generic configuration routines.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>

#समावेश "rt2x00.h"
#समावेश "rt2x00lib.h"

व्योम rt2x00lib_config_पूर्णांकf(काष्ठा rt2x00_dev *rt2x00dev,
			   काष्ठा rt2x00_पूर्णांकf *पूर्णांकf,
			   क्रमागत nl80211_अगरtype type,
			   स्थिर u8 *mac, स्थिर u8 *bssid)
अणु
	काष्ठा rt2x00पूर्णांकf_conf conf;
	अचिन्हित पूर्णांक flags = 0;

	conf.type = type;

	चयन (type) अणु
	हाल NL80211_IFTYPE_ADHOC:
		conf.sync = TSF_SYNC_ADHOC;
		अवरोध;
	हाल NL80211_IFTYPE_AP:
	हाल NL80211_IFTYPE_MESH_POINT:
		conf.sync = TSF_SYNC_AP_NONE;
		अवरोध;
	हाल NL80211_IFTYPE_STATION:
		conf.sync = TSF_SYNC_INFRA;
		अवरोध;
	शेष:
		conf.sync = TSF_SYNC_NONE;
		अवरोध;
	पूर्ण

	/*
	 * Note that when शून्य is passed as address we will send
	 * 00:00:00:00:00 to the device to clear the address.
	 * This will prevent the device being confused when it wants
	 * to ACK frames or considers itself associated.
	 */
	स_रखो(conf.mac, 0, माप(conf.mac));
	अगर (mac)
		स_नकल(conf.mac, mac, ETH_ALEN);

	स_रखो(conf.bssid, 0, माप(conf.bssid));
	अगर (bssid)
		स_नकल(conf.bssid, bssid, ETH_ALEN);

	flags |= CONFIG_UPDATE_TYPE;
	अगर (mac || (!rt2x00dev->पूर्णांकf_ap_count && !rt2x00dev->पूर्णांकf_sta_count))
		flags |= CONFIG_UPDATE_MAC;
	अगर (bssid || (!rt2x00dev->पूर्णांकf_ap_count && !rt2x00dev->पूर्णांकf_sta_count))
		flags |= CONFIG_UPDATE_BSSID;

	rt2x00dev->ops->lib->config_पूर्णांकf(rt2x00dev, पूर्णांकf, &conf, flags);
पूर्ण

व्योम rt2x00lib_config_erp(काष्ठा rt2x00_dev *rt2x00dev,
			  काष्ठा rt2x00_पूर्णांकf *पूर्णांकf,
			  काष्ठा ieee80211_bss_conf *bss_conf,
			  u32 changed)
अणु
	काष्ठा rt2x00lib_erp erp;

	स_रखो(&erp, 0, माप(erp));

	erp.लघु_preamble = bss_conf->use_लघु_preamble;
	erp.cts_protection = bss_conf->use_cts_prot;

	erp.slot_समय = bss_conf->use_लघु_slot ? SHORT_SLOT_TIME : SLOT_TIME;
	erp.sअगरs = SIFS;
	erp.pअगरs = bss_conf->use_लघु_slot ? SHORT_PIFS : PIFS;
	erp.dअगरs = bss_conf->use_लघु_slot ? SHORT_DIFS : DIFS;
	erp.eअगरs = bss_conf->use_लघु_slot ? SHORT_EIFS : EIFS;

	erp.basic_rates = bss_conf->basic_rates;
	erp.beacon_पूर्णांक = bss_conf->beacon_पूर्णांक;

	/* Update the AID, this is needed क्रम dynamic PS support */
	rt2x00dev->aid = bss_conf->assoc ? bss_conf->aid : 0;
	rt2x00dev->last_beacon = bss_conf->sync_tsf;

	/* Update global beacon पूर्णांकerval समय, this is needed क्रम PS support */
	rt2x00dev->beacon_पूर्णांक = bss_conf->beacon_पूर्णांक;

	अगर (changed & BSS_CHANGED_HT)
		erp.ht_opmode = bss_conf->ht_operation_mode;

	rt2x00dev->ops->lib->config_erp(rt2x00dev, &erp, changed);
पूर्ण

व्योम rt2x00lib_config_antenna(काष्ठा rt2x00_dev *rt2x00dev,
			      काष्ठा antenna_setup config)
अणु
	काष्ठा link_ant *ant = &rt2x00dev->link.ant;
	काष्ठा antenna_setup *def = &rt2x00dev->शेष_ant;
	काष्ठा antenna_setup *active = &rt2x00dev->link.ant.active;

	/*
	 * When the caller tries to send the SW भागersity,
	 * we must update the ANTENNA_RX_DIVERSITY flag to
	 * enable the antenna भागersity in the link tuner.
	 *
	 * Secondly, we must guarentee we never send the
	 * software antenna भागersity command to the driver.
	 */
	अगर (!(ant->flags & ANTENNA_RX_DIVERSITY)) अणु
		अगर (config.rx == ANTENNA_SW_DIVERSITY) अणु
			ant->flags |= ANTENNA_RX_DIVERSITY;

			अगर (def->rx == ANTENNA_SW_DIVERSITY)
				config.rx = ANTENNA_B;
			अन्यथा
				config.rx = def->rx;
		पूर्ण
	पूर्ण अन्यथा अगर (config.rx == ANTENNA_SW_DIVERSITY)
		config.rx = active->rx;

	अगर (!(ant->flags & ANTENNA_TX_DIVERSITY)) अणु
		अगर (config.tx == ANTENNA_SW_DIVERSITY) अणु
			ant->flags |= ANTENNA_TX_DIVERSITY;

			अगर (def->tx == ANTENNA_SW_DIVERSITY)
				config.tx = ANTENNA_B;
			अन्यथा
				config.tx = def->tx;
		पूर्ण
	पूर्ण अन्यथा अगर (config.tx == ANTENNA_SW_DIVERSITY)
		config.tx = active->tx;

	/*
	 * Antenna setup changes require the RX to be disabled,
	 * अन्यथा the changes will be ignored by the device.
	 */
	अगर (test_bit(DEVICE_STATE_ENABLED_RADIO, &rt2x00dev->flags))
		rt2x00queue_stop_queue(rt2x00dev->rx);

	/*
	 * Write new antenna setup to device and reset the link tuner.
	 * The latter is required since we need to recalibrate the
	 * noise-sensitivity ratio क्रम the new setup.
	 */
	rt2x00dev->ops->lib->config_ant(rt2x00dev, &config);

	rt2x00link_reset_tuner(rt2x00dev, true);

	स_नकल(active, &config, माप(config));

	अगर (test_bit(DEVICE_STATE_ENABLED_RADIO, &rt2x00dev->flags))
		rt2x00queue_start_queue(rt2x00dev->rx);
पूर्ण

अटल u16 rt2x00ht_center_channel(काष्ठा rt2x00_dev *rt2x00dev,
				   काष्ठा ieee80211_conf *conf)
अणु
	काष्ठा hw_mode_spec *spec = &rt2x00dev->spec;
	पूर्णांक center_channel;
	u16 i;

	/*
	 * Initialize center channel to current channel.
	 */
	center_channel = spec->channels[conf->chandef.chan->hw_value].channel;

	/*
	 * Adjust center channel to HT40+ and HT40- operation.
	 */
	अगर (conf_is_ht40_plus(conf))
		center_channel += 2;
	अन्यथा अगर (conf_is_ht40_minus(conf))
		center_channel -= (center_channel == 14) ? 1 : 2;

	क्रम (i = 0; i < spec->num_channels; i++)
		अगर (spec->channels[i].channel == center_channel)
			वापस i;

	WARN_ON(1);
	वापस conf->chandef.chan->hw_value;
पूर्ण

व्योम rt2x00lib_config(काष्ठा rt2x00_dev *rt2x00dev,
		      काष्ठा ieee80211_conf *conf,
		      अचिन्हित पूर्णांक ieee80211_flags)
अणु
	काष्ठा rt2x00lib_conf libconf;
	u16 hw_value;
	u16 स्वतःwake_समयout;
	u16 beacon_पूर्णांक;
	u16 beacon_dअगरf;

	स_रखो(&libconf, 0, माप(libconf));

	libconf.conf = conf;

	अगर (ieee80211_flags & IEEE80211_CONF_CHANGE_CHANNEL) अणु
		अगर (!conf_is_ht(conf))
			set_bit(CONFIG_HT_DISABLED, &rt2x00dev->flags);
		अन्यथा
			clear_bit(CONFIG_HT_DISABLED, &rt2x00dev->flags);

		अगर (conf_is_ht40(conf)) अणु
			set_bit(CONFIG_CHANNEL_HT40, &rt2x00dev->flags);
			hw_value = rt2x00ht_center_channel(rt2x00dev, conf);
		पूर्ण अन्यथा अणु
			clear_bit(CONFIG_CHANNEL_HT40, &rt2x00dev->flags);
			hw_value = conf->chandef.chan->hw_value;
		पूर्ण

		स_नकल(&libconf.rf,
		       &rt2x00dev->spec.channels[hw_value],
		       माप(libconf.rf));

		स_नकल(&libconf.channel,
		       &rt2x00dev->spec.channels_info[hw_value],
		       माप(libconf.channel));

		/* Used क्रम VCO periodic calibration */
		rt2x00dev->rf_channel = libconf.rf.channel;
	पूर्ण

	अगर (rt2x00_has_cap_flag(rt2x00dev, REQUIRE_PS_AUTOWAKE) &&
	    (ieee80211_flags & IEEE80211_CONF_CHANGE_PS))
		cancel_delayed_work_sync(&rt2x00dev->स्वतःwakeup_work);

	/*
	 * Start configuration.
	 */
	rt2x00dev->ops->lib->config(rt2x00dev, &libconf, ieee80211_flags);

	अगर (conf->flags & IEEE80211_CONF_PS)
		set_bit(CONFIG_POWERSAVING, &rt2x00dev->flags);
	अन्यथा
		clear_bit(CONFIG_POWERSAVING, &rt2x00dev->flags);

	अगर (conf->flags & IEEE80211_CONF_MONITOR)
		set_bit(CONFIG_MONITORING, &rt2x00dev->flags);
	अन्यथा
		clear_bit(CONFIG_MONITORING, &rt2x00dev->flags);

	rt2x00dev->curr_band = conf->chandef.chan->band;
	rt2x00dev->curr_freq = conf->chandef.chan->center_freq;
	rt2x00dev->tx_घातer = conf->घातer_level;
	rt2x00dev->लघु_retry = conf->लघु_frame_max_tx_count;
	rt2x00dev->दीर्घ_retry = conf->दीर्घ_frame_max_tx_count;

	/*
	 * Some configuration changes affect the link quality
	 * which means we need to reset the link tuner.
	 */
	अगर (ieee80211_flags & IEEE80211_CONF_CHANGE_CHANNEL)
		rt2x00link_reset_tuner(rt2x00dev, false);

	अगर (test_bit(DEVICE_STATE_PRESENT, &rt2x00dev->flags) &&
	    rt2x00_has_cap_flag(rt2x00dev, REQUIRE_PS_AUTOWAKE) &&
	    (ieee80211_flags & IEEE80211_CONF_CHANGE_PS) &&
	    (conf->flags & IEEE80211_CONF_PS)) अणु
		beacon_dअगरf = (दीर्घ)jअगरfies - (दीर्घ)rt2x00dev->last_beacon;
		beacon_पूर्णांक = msecs_to_jअगरfies(rt2x00dev->beacon_पूर्णांक);

		अगर (beacon_dअगरf > beacon_पूर्णांक)
			beacon_dअगरf = 0;

		स्वतःwake_समयout = (conf->ps_dtim_period * beacon_पूर्णांक) - beacon_dअगरf;
		queue_delayed_work(rt2x00dev->workqueue,
				   &rt2x00dev->स्वतःwakeup_work,
				   स्वतःwake_समयout - 15);
	पूर्ण
पूर्ण
