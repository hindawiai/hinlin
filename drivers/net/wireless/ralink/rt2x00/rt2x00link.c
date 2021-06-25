<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
	Copyright (C) 2004 - 2009 Ivo van Doorn <IvDoorn@gmail.com>
	<http://rt2x00.serialmonkey.com>

 */

/*
	Module: rt2x00lib
	Abstract: rt2x00 generic link tuning routines.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>

#समावेश "rt2x00.h"
#समावेश "rt2x00lib.h"

/*
 * When we lack RSSI inक्रमmation वापस something less then -80 to
 * tell the driver to tune the device to maximum sensitivity.
 */
#घोषणा DEFAULT_RSSI		-128

अटल अंतरभूत पूर्णांक rt2x00link_get_avg_rssi(काष्ठा ewma_rssi *ewma)
अणु
	अचिन्हित दीर्घ avg;

	avg = ewma_rssi_पढ़ो(ewma);
	अगर (avg)
		वापस -avg;

	वापस DEFAULT_RSSI;
पूर्ण

अटल पूर्णांक rt2x00link_antenna_get_link_rssi(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	काष्ठा link_ant *ant = &rt2x00dev->link.ant;

	अगर (rt2x00dev->link.qual.rx_success)
		वापस rt2x00link_get_avg_rssi(&ant->rssi_ant);

	वापस DEFAULT_RSSI;
पूर्ण

अटल पूर्णांक rt2x00link_antenna_get_rssi_history(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	काष्ठा link_ant *ant = &rt2x00dev->link.ant;

	अगर (ant->rssi_history)
		वापस ant->rssi_history;
	वापस DEFAULT_RSSI;
पूर्ण

अटल व्योम rt2x00link_antenna_update_rssi_history(काष्ठा rt2x00_dev *rt2x00dev,
						   पूर्णांक rssi)
अणु
	काष्ठा link_ant *ant = &rt2x00dev->link.ant;
	ant->rssi_history = rssi;
पूर्ण

अटल व्योम rt2x00link_antenna_reset(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	ewma_rssi_init(&rt2x00dev->link.ant.rssi_ant);
पूर्ण

अटल व्योम rt2x00lib_antenna_भागersity_sample(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	काष्ठा link_ant *ant = &rt2x00dev->link.ant;
	काष्ठा antenna_setup new_ant;
	पूर्णांक other_antenna;

	पूर्णांक sample_current = rt2x00link_antenna_get_link_rssi(rt2x00dev);
	पूर्णांक sample_other = rt2x00link_antenna_get_rssi_history(rt2x00dev);

	स_नकल(&new_ant, &ant->active, माप(new_ant));

	/*
	 * We are करोne sampling. Now we should evaluate the results.
	 */
	ant->flags &= ~ANTENNA_MODE_SAMPLE;

	/*
	 * During the last period we have sampled the RSSI
	 * from both antennas. It now is समय to determine
	 * which antenna demonstrated the best perक्रमmance.
	 * When we are alपढ़ोy on the antenna with the best
	 * perक्रमmance, just create a good starting poपूर्णांक
	 * क्रम the history and we are करोne.
	 */
	अगर (sample_current >= sample_other) अणु
		rt2x00link_antenna_update_rssi_history(rt2x00dev,
			sample_current);
		वापस;
	पूर्ण

	other_antenna = (ant->active.rx == ANTENNA_A) ? ANTENNA_B : ANTENNA_A;

	अगर (ant->flags & ANTENNA_RX_DIVERSITY)
		new_ant.rx = other_antenna;

	अगर (ant->flags & ANTENNA_TX_DIVERSITY)
		new_ant.tx = other_antenna;

	rt2x00lib_config_antenna(rt2x00dev, new_ant);
पूर्ण

अटल व्योम rt2x00lib_antenna_भागersity_eval(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	काष्ठा link_ant *ant = &rt2x00dev->link.ant;
	काष्ठा antenna_setup new_ant;
	पूर्णांक rssi_curr;
	पूर्णांक rssi_old;

	स_नकल(&new_ant, &ant->active, माप(new_ant));

	/*
	 * Get current RSSI value aदीर्घ with the historical value,
	 * after that update the history with the current value.
	 */
	rssi_curr = rt2x00link_antenna_get_link_rssi(rt2x00dev);
	rssi_old = rt2x00link_antenna_get_rssi_history(rt2x00dev);
	rt2x00link_antenna_update_rssi_history(rt2x00dev, rssi_curr);

	/*
	 * Legacy driver indicates that we should swap antenna's
	 * when the dअगरference in RSSI is greater that 5. This
	 * also should be करोne when the RSSI was actually better
	 * then the previous sample.
	 * When the dअगरference exceeds the threshold we should
	 * sample the rssi from the other antenna to make a valid
	 * comparison between the 2 antennas.
	 */
	अगर (असल(rssi_curr - rssi_old) < 5)
		वापस;

	ant->flags |= ANTENNA_MODE_SAMPLE;

	अगर (ant->flags & ANTENNA_RX_DIVERSITY)
		new_ant.rx = (new_ant.rx == ANTENNA_A) ? ANTENNA_B : ANTENNA_A;

	अगर (ant->flags & ANTENNA_TX_DIVERSITY)
		new_ant.tx = (new_ant.tx == ANTENNA_A) ? ANTENNA_B : ANTENNA_A;

	rt2x00lib_config_antenna(rt2x00dev, new_ant);
पूर्ण

अटल bool rt2x00lib_antenna_भागersity(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	काष्ठा link_ant *ant = &rt2x00dev->link.ant;

	/*
	 * Determine अगर software भागersity is enabled क्रम
	 * either the TX or RX antenna (or both).
	 */
	अगर (!(ant->flags & ANTENNA_RX_DIVERSITY) &&
	    !(ant->flags & ANTENNA_TX_DIVERSITY)) अणु
		ant->flags = 0;
		वापस true;
	पूर्ण

	/*
	 * If we have only sampled the data over the last period
	 * we should now harvest the data. Otherwise just evaluate
	 * the data. The latter should only be perक्रमmed once
	 * every 2 seconds.
	 */
	अगर (ant->flags & ANTENNA_MODE_SAMPLE) अणु
		rt2x00lib_antenna_भागersity_sample(rt2x00dev);
		वापस true;
	पूर्ण अन्यथा अगर (rt2x00dev->link.count & 1) अणु
		rt2x00lib_antenna_भागersity_eval(rt2x00dev);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

व्योम rt2x00link_update_stats(काष्ठा rt2x00_dev *rt2x00dev,
			     काष्ठा sk_buff *skb,
			     काष्ठा rxकरोne_entry_desc *rxdesc)
अणु
	काष्ठा link *link = &rt2x00dev->link;
	काष्ठा link_qual *qual = &rt2x00dev->link.qual;
	काष्ठा link_ant *ant = &rt2x00dev->link.ant;
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)skb->data;

	/*
	 * No need to update the stats क्रम !=STA पूर्णांकerfaces
	 */
	अगर (!rt2x00dev->पूर्णांकf_sta_count)
		वापस;

	/*
	 * Frame was received successfully since non-succesfull
	 * frames would have been dropped by the hardware.
	 */
	qual->rx_success++;

	/*
	 * We are only पूर्णांकerested in quality statistics from
	 * beacons which came from the BSS which we are
	 * associated with.
	 */
	अगर (!ieee80211_is_beacon(hdr->frame_control) ||
	    !(rxdesc->dev_flags & RXDONE_MY_BSS))
		वापस;

	/*
	 * Update global RSSI
	 */
	ewma_rssi_add(&link->avg_rssi, -rxdesc->rssi);

	/*
	 * Update antenna RSSI
	 */
	ewma_rssi_add(&ant->rssi_ant, -rxdesc->rssi);
पूर्ण

व्योम rt2x00link_start_tuner(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	काष्ठा link *link = &rt2x00dev->link;

	/*
	 * Single monitor mode पूर्णांकerfaces should never have
	 * work with link tuners.
	 */
	अगर (!rt2x00dev->पूर्णांकf_ap_count && !rt2x00dev->पूर्णांकf_sta_count)
		वापस;

	/*
	 * While scanning, link tuning is disabled. By शेष
	 * the most sensitive settings will be used to make sure
	 * that all beacons and probe responses will be received
	 * during the scan.
	 */
	अगर (test_bit(DEVICE_STATE_SCANNING, &rt2x00dev->flags))
		वापस;

	rt2x00link_reset_tuner(rt2x00dev, false);

	अगर (test_bit(DEVICE_STATE_PRESENT, &rt2x00dev->flags))
		ieee80211_queue_delayed_work(rt2x00dev->hw,
					     &link->work, LINK_TUNE_INTERVAL);
पूर्ण

व्योम rt2x00link_stop_tuner(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	cancel_delayed_work_sync(&rt2x00dev->link.work);
पूर्ण

व्योम rt2x00link_reset_tuner(काष्ठा rt2x00_dev *rt2x00dev, bool antenna)
अणु
	काष्ठा link_qual *qual = &rt2x00dev->link.qual;
	u8 vgc_level = qual->vgc_level_reg;

	अगर (!test_bit(DEVICE_STATE_ENABLED_RADIO, &rt2x00dev->flags))
		वापस;

	/*
	 * Reset link inक्रमmation.
	 * Both the currently active vgc level as well as
	 * the link tuner counter should be reset. Resetting
	 * the counter is important क्रम devices where the
	 * device should only perक्रमm link tuning during the
	 * first minute after being enabled.
	 */
	rt2x00dev->link.count = 0;
	स_रखो(qual, 0, माप(*qual));
	ewma_rssi_init(&rt2x00dev->link.avg_rssi);

	/*
	 * Restore the VGC level as stored in the रेजिस्टरs,
	 * the driver can use this to determine अगर the रेजिस्टर
	 * must be updated during reset or not.
	 */
	qual->vgc_level_reg = vgc_level;

	/*
	 * Reset the link tuner.
	 */
	rt2x00dev->ops->lib->reset_tuner(rt2x00dev, qual);

	अगर (antenna)
		rt2x00link_antenna_reset(rt2x00dev);
पूर्ण

अटल व्योम rt2x00link_reset_qual(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	काष्ठा link_qual *qual = &rt2x00dev->link.qual;

	qual->rx_success = 0;
	qual->rx_failed = 0;
	qual->tx_success = 0;
	qual->tx_failed = 0;
पूर्ण

अटल व्योम rt2x00link_tuner_sta(काष्ठा rt2x00_dev *rt2x00dev, काष्ठा link *link)
अणु
	काष्ठा link_qual *qual = &rt2x00dev->link.qual;

	/*
	 * Update statistics.
	 */
	rt2x00dev->ops->lib->link_stats(rt2x00dev, qual);
	rt2x00dev->low_level_stats.करोt11FCSErrorCount += qual->rx_failed;

	/*
	 * Update quality RSSI क्रम link tuning,
	 * when we have received some frames and we managed to
	 * collect the RSSI data we could use this. Otherwise we
	 * must fallback to the शेष RSSI value.
	 */
	अगर (!qual->rx_success)
		qual->rssi = DEFAULT_RSSI;
	अन्यथा
		qual->rssi = rt2x00link_get_avg_rssi(&link->avg_rssi);

	/*
	 * Check अगर link tuning is supported by the hardware, some hardware
	 * करो not support link tuning at all, जबतक other devices can disable
	 * the feature from the EEPROM.
	 */
	अगर (rt2x00_has_cap_link_tuning(rt2x00dev))
		rt2x00dev->ops->lib->link_tuner(rt2x00dev, qual, link->count);

	/*
	 * Send a संकेत to the led to update the led संकेत strength.
	 */
	rt2x00leds_led_quality(rt2x00dev, qual->rssi);

	/*
	 * Evaluate antenna setup, make this the last step when
	 * rt2x00lib_antenna_भागersity made changes the quality
	 * statistics will be reset.
	 */
	अगर (rt2x00lib_antenna_भागersity(rt2x00dev))
		rt2x00link_reset_qual(rt2x00dev);
पूर्ण

अटल व्योम rt2x00link_tuner(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rt2x00_dev *rt2x00dev =
	    container_of(work, काष्ठा rt2x00_dev, link.work.work);
	काष्ठा link *link = &rt2x00dev->link;

	/*
	 * When the radio is shutting करोwn we should
	 * immediately cease all link tuning.
	 */
	अगर (!test_bit(DEVICE_STATE_ENABLED_RADIO, &rt2x00dev->flags) ||
	    test_bit(DEVICE_STATE_SCANNING, &rt2x00dev->flags))
		वापस;

	/* Do not race with rt2x00mac_config(). */
	mutex_lock(&rt2x00dev->conf_mutex);

	अगर (rt2x00dev->पूर्णांकf_sta_count)
		rt2x00link_tuner_sta(rt2x00dev, link);

	अगर (rt2x00dev->ops->lib->gain_calibration &&
	    (link->count % (AGC_SECONDS / LINK_TUNE_SECONDS)) == 0)
		rt2x00dev->ops->lib->gain_calibration(rt2x00dev);

	अगर (rt2x00dev->ops->lib->vco_calibration &&
	    rt2x00_has_cap_vco_recalibration(rt2x00dev) &&
	    (link->count % (VCO_SECONDS / LINK_TUNE_SECONDS)) == 0)
		rt2x00dev->ops->lib->vco_calibration(rt2x00dev);

	mutex_unlock(&rt2x00dev->conf_mutex);

	/*
	 * Increase tuner counter, and reschedule the next link tuner run.
	 */
	link->count++;

	अगर (test_bit(DEVICE_STATE_PRESENT, &rt2x00dev->flags))
		ieee80211_queue_delayed_work(rt2x00dev->hw,
					     &link->work, LINK_TUNE_INTERVAL);
पूर्ण

व्योम rt2x00link_start_watchकरोg(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	काष्ठा link *link = &rt2x00dev->link;

	अगर (test_bit(DEVICE_STATE_PRESENT, &rt2x00dev->flags) &&
	    rt2x00dev->ops->lib->watchकरोg && !link->watchकरोg_disabled)
		ieee80211_queue_delayed_work(rt2x00dev->hw,
					     &link->watchकरोg_work,
					     link->watchकरोg_पूर्णांकerval);
पूर्ण

व्योम rt2x00link_stop_watchकरोg(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	cancel_delayed_work_sync(&rt2x00dev->link.watchकरोg_work);
पूर्ण

अटल व्योम rt2x00link_watchकरोg(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rt2x00_dev *rt2x00dev =
	    container_of(work, काष्ठा rt2x00_dev, link.watchकरोg_work.work);
	काष्ठा link *link = &rt2x00dev->link;

	/*
	 * When the radio is shutting करोwn we should
	 * immediately cease the watchकरोg monitoring.
	 */
	अगर (!test_bit(DEVICE_STATE_ENABLED_RADIO, &rt2x00dev->flags))
		वापस;

	rt2x00dev->ops->lib->watchकरोg(rt2x00dev);

	अगर (test_bit(DEVICE_STATE_PRESENT, &rt2x00dev->flags))
		ieee80211_queue_delayed_work(rt2x00dev->hw,
					     &link->watchकरोg_work,
					     link->watchकरोg_पूर्णांकerval);
पूर्ण

व्योम rt2x00link_रेजिस्टर(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	काष्ठा link *link = &rt2x00dev->link;

	INIT_DELAYED_WORK(&link->work, rt2x00link_tuner);
	INIT_DELAYED_WORK(&link->watchकरोg_work, rt2x00link_watchकरोg);

	अगर (link->watchकरोg_पूर्णांकerval == 0)
		link->watchकरोg_पूर्णांकerval = WATCHDOG_INTERVAL;
पूर्ण
