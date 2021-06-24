<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * This file is part of wl1251
 *
 * Copyright (C) 2009 Nokia Corporation
 */

#समावेश "debugfs.h"

#समावेश <linux/skbuff.h>
#समावेश <linux/slab.h>

#समावेश "wl1251.h"
#समावेश "acx.h"
#समावेश "ps.h"

/* ms */
#घोषणा WL1251_DEBUGFS_STATS_LIFETIME 1000

/* debugfs macros idea from mac80211 */

#घोषणा DEBUGFS_READONLY_खाता(name, buflen, fmt, value...)		\
अटल sमाप_प्रकार name## _पढ़ो(काष्ठा file *file, अक्षर __user *userbuf,	\
			    माप_प्रकार count, loff_t *ppos)			\
अणु									\
	काष्ठा wl1251 *wl = file->निजी_data;				\
	अक्षर buf[buflen];						\
	पूर्णांक res;							\
									\
	res = scnम_लिखो(buf, buflen, fmt "\n", ##value);		\
	वापस simple_पढ़ो_from_buffer(userbuf, count, ppos, buf, res);	\
पूर्ण									\
									\
अटल स्थिर काष्ठा file_operations name## _ops = अणु			\
	.पढ़ो = name## _पढ़ो,						\
	.खोलो = simple_खोलो,						\
	.llseek	= generic_file_llseek,					\
पूर्ण;

#घोषणा DEBUGFS_ADD(name, parent)					\
	wl->debugfs.name = debugfs_create_file(#name, 0400, parent,	\
					       wl, &name## _ops)	\

#घोषणा DEBUGFS_DEL(name)						\
	करो अणु								\
		debugfs_हटाओ(wl->debugfs.name);			\
		wl->debugfs.name = शून्य;				\
	पूर्ण जबतक (0)

#घोषणा DEBUGFS_FWSTATS_खाता(sub, name, buflen, fmt)			\
अटल sमाप_प्रकार sub## _ ##name## _पढ़ो(काष्ठा file *file,		\
				      अक्षर __user *userbuf,		\
				      माप_प्रकार count, loff_t *ppos)	\
अणु									\
	काष्ठा wl1251 *wl = file->निजी_data;				\
	अक्षर buf[buflen];						\
	पूर्णांक res;							\
									\
	wl1251_debugfs_update_stats(wl);				\
									\
	res = scnम_लिखो(buf, buflen, fmt "\n",				\
			wl->stats.fw_stats->sub.name);			\
	वापस simple_पढ़ो_from_buffer(userbuf, count, ppos, buf, res);	\
पूर्ण									\
									\
अटल स्थिर काष्ठा file_operations sub## _ ##name## _ops = अणु		\
	.पढ़ो = sub## _ ##name## _पढ़ो,					\
	.खोलो = simple_खोलो,						\
	.llseek	= generic_file_llseek,					\
पूर्ण;

#घोषणा DEBUGFS_FWSTATS_ADD(sub, name)				\
	DEBUGFS_ADD(sub## _ ##name, wl->debugfs.fw_statistics)

#घोषणा DEBUGFS_FWSTATS_DEL(sub, name)				\
	DEBUGFS_DEL(sub## _ ##name)

अटल व्योम wl1251_debugfs_update_stats(काष्ठा wl1251 *wl)
अणु
	पूर्णांक ret;

	mutex_lock(&wl->mutex);

	ret = wl1251_ps_elp_wakeup(wl);
	अगर (ret < 0)
		जाओ out;

	अगर (wl->state == WL1251_STATE_ON &&
	    समय_after(jअगरfies, wl->stats.fw_stats_update +
		       msecs_to_jअगरfies(WL1251_DEBUGFS_STATS_LIFETIME))) अणु
		wl1251_acx_statistics(wl, wl->stats.fw_stats);
		wl->stats.fw_stats_update = jअगरfies;
	पूर्ण

	wl1251_ps_elp_sleep(wl);

out:
	mutex_unlock(&wl->mutex);
पूर्ण

DEBUGFS_FWSTATS_खाता(tx, पूर्णांकernal_desc_overflow, 20, "%u");

DEBUGFS_FWSTATS_खाता(rx, out_of_mem, 20, "%u");
DEBUGFS_FWSTATS_खाता(rx, hdr_overflow, 20, "%u");
DEBUGFS_FWSTATS_खाता(rx, hw_stuck, 20, "%u");
DEBUGFS_FWSTATS_खाता(rx, dropped, 20, "%u");
DEBUGFS_FWSTATS_खाता(rx, fcs_err, 20, "%u");
DEBUGFS_FWSTATS_खाता(rx, xfr_hपूर्णांक_trig, 20, "%u");
DEBUGFS_FWSTATS_खाता(rx, path_reset, 20, "%u");
DEBUGFS_FWSTATS_खाता(rx, reset_counter, 20, "%u");

DEBUGFS_FWSTATS_खाता(dma, rx_requested, 20, "%u");
DEBUGFS_FWSTATS_खाता(dma, rx_errors, 20, "%u");
DEBUGFS_FWSTATS_खाता(dma, tx_requested, 20, "%u");
DEBUGFS_FWSTATS_खाता(dma, tx_errors, 20, "%u");

DEBUGFS_FWSTATS_खाता(isr, cmd_cmplt, 20, "%u");
DEBUGFS_FWSTATS_खाता(isr, fiqs, 20, "%u");
DEBUGFS_FWSTATS_खाता(isr, rx_headers, 20, "%u");
DEBUGFS_FWSTATS_खाता(isr, rx_mem_overflow, 20, "%u");
DEBUGFS_FWSTATS_खाता(isr, rx_rdys, 20, "%u");
DEBUGFS_FWSTATS_खाता(isr, irqs, 20, "%u");
DEBUGFS_FWSTATS_खाता(isr, tx_procs, 20, "%u");
DEBUGFS_FWSTATS_खाता(isr, decrypt_करोne, 20, "%u");
DEBUGFS_FWSTATS_खाता(isr, dma0_करोne, 20, "%u");
DEBUGFS_FWSTATS_खाता(isr, dma1_करोne, 20, "%u");
DEBUGFS_FWSTATS_खाता(isr, tx_exch_complete, 20, "%u");
DEBUGFS_FWSTATS_खाता(isr, commands, 20, "%u");
DEBUGFS_FWSTATS_खाता(isr, rx_procs, 20, "%u");
DEBUGFS_FWSTATS_खाता(isr, hw_pm_mode_changes, 20, "%u");
DEBUGFS_FWSTATS_खाता(isr, host_acknowledges, 20, "%u");
DEBUGFS_FWSTATS_खाता(isr, pci_pm, 20, "%u");
DEBUGFS_FWSTATS_खाता(isr, wakeups, 20, "%u");
DEBUGFS_FWSTATS_खाता(isr, low_rssi, 20, "%u");

DEBUGFS_FWSTATS_खाता(wep, addr_key_count, 20, "%u");
DEBUGFS_FWSTATS_खाता(wep, शेष_key_count, 20, "%u");
/* skipping wep.reserved */
DEBUGFS_FWSTATS_खाता(wep, key_not_found, 20, "%u");
DEBUGFS_FWSTATS_खाता(wep, decrypt_fail, 20, "%u");
DEBUGFS_FWSTATS_खाता(wep, packets, 20, "%u");
DEBUGFS_FWSTATS_खाता(wep, पूर्णांकerrupt, 20, "%u");

DEBUGFS_FWSTATS_खाता(pwr, ps_enter, 20, "%u");
DEBUGFS_FWSTATS_खाता(pwr, elp_enter, 20, "%u");
DEBUGFS_FWSTATS_खाता(pwr, missing_bcns, 20, "%u");
DEBUGFS_FWSTATS_खाता(pwr, wake_on_host, 20, "%u");
DEBUGFS_FWSTATS_खाता(pwr, wake_on_समयr_exp, 20, "%u");
DEBUGFS_FWSTATS_खाता(pwr, tx_with_ps, 20, "%u");
DEBUGFS_FWSTATS_खाता(pwr, tx_without_ps, 20, "%u");
DEBUGFS_FWSTATS_खाता(pwr, rcvd_beacons, 20, "%u");
DEBUGFS_FWSTATS_खाता(pwr, घातer_save_off, 20, "%u");
DEBUGFS_FWSTATS_खाता(pwr, enable_ps, 20, "%u");
DEBUGFS_FWSTATS_खाता(pwr, disable_ps, 20, "%u");
DEBUGFS_FWSTATS_खाता(pwr, fix_tsf_ps, 20, "%u");
/* skipping cont_miss_bcns_spपढ़ो क्रम now */
DEBUGFS_FWSTATS_खाता(pwr, rcvd_awake_beacons, 20, "%u");

DEBUGFS_FWSTATS_खाता(mic, rx_pkts, 20, "%u");
DEBUGFS_FWSTATS_खाता(mic, calc_failure, 20, "%u");

DEBUGFS_FWSTATS_खाता(aes, encrypt_fail, 20, "%u");
DEBUGFS_FWSTATS_खाता(aes, decrypt_fail, 20, "%u");
DEBUGFS_FWSTATS_खाता(aes, encrypt_packets, 20, "%u");
DEBUGFS_FWSTATS_खाता(aes, decrypt_packets, 20, "%u");
DEBUGFS_FWSTATS_खाता(aes, encrypt_पूर्णांकerrupt, 20, "%u");
DEBUGFS_FWSTATS_खाता(aes, decrypt_पूर्णांकerrupt, 20, "%u");

DEBUGFS_FWSTATS_खाता(event, heart_beat, 20, "%u");
DEBUGFS_FWSTATS_खाता(event, calibration, 20, "%u");
DEBUGFS_FWSTATS_खाता(event, rx_mismatch, 20, "%u");
DEBUGFS_FWSTATS_खाता(event, rx_mem_empty, 20, "%u");
DEBUGFS_FWSTATS_खाता(event, rx_pool, 20, "%u");
DEBUGFS_FWSTATS_खाता(event, oom_late, 20, "%u");
DEBUGFS_FWSTATS_खाता(event, phy_transmit_error, 20, "%u");
DEBUGFS_FWSTATS_खाता(event, tx_stuck, 20, "%u");

DEBUGFS_FWSTATS_खाता(ps, pspoll_समयouts, 20, "%u");
DEBUGFS_FWSTATS_खाता(ps, upsd_समयouts, 20, "%u");
DEBUGFS_FWSTATS_खाता(ps, upsd_max_spसमय, 20, "%u");
DEBUGFS_FWSTATS_खाता(ps, upsd_max_apturn, 20, "%u");
DEBUGFS_FWSTATS_खाता(ps, pspoll_max_apturn, 20, "%u");
DEBUGFS_FWSTATS_खाता(ps, pspoll_utilization, 20, "%u");
DEBUGFS_FWSTATS_खाता(ps, upsd_utilization, 20, "%u");

DEBUGFS_FWSTATS_खाता(rxpipe, rx_prep_beacon_drop, 20, "%u");
DEBUGFS_FWSTATS_खाता(rxpipe, descr_host_पूर्णांक_trig_rx_data, 20, "%u");
DEBUGFS_FWSTATS_खाता(rxpipe, beacon_buffer_thres_host_पूर्णांक_trig_rx_data,
		     20, "%u");
DEBUGFS_FWSTATS_खाता(rxpipe, missed_beacon_host_पूर्णांक_trig_rx_data, 20, "%u");
DEBUGFS_FWSTATS_खाता(rxpipe, tx_xfr_host_पूर्णांक_trig_rx_data, 20, "%u");

DEBUGFS_READONLY_खाता(retry_count, 20, "%u", wl->stats.retry_count);
DEBUGFS_READONLY_खाता(excessive_retries, 20, "%u",
		      wl->stats.excessive_retries);

अटल sमाप_प्रकार tx_queue_len_पढ़ो(काष्ठा file *file, अक्षर __user *userbuf,
				 माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा wl1251 *wl = file->निजी_data;
	u32 queue_len;
	अक्षर buf[20];
	पूर्णांक res;

	queue_len = skb_queue_len(&wl->tx_queue);

	res = scnम_लिखो(buf, माप(buf), "%u\n", queue_len);
	वापस simple_पढ़ो_from_buffer(userbuf, count, ppos, buf, res);
पूर्ण

अटल स्थिर काष्ठा file_operations tx_queue_len_ops = अणु
	.पढ़ो = tx_queue_len_पढ़ो,
	.खोलो = simple_खोलो,
	.llseek = generic_file_llseek,
पूर्ण;

अटल sमाप_प्रकार tx_queue_status_पढ़ो(काष्ठा file *file, अक्षर __user *userbuf,
				    माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा wl1251 *wl = file->निजी_data;
	अक्षर buf[3], status;
	पूर्णांक len;

	अगर (wl->tx_queue_stopped)
		status = 's';
	अन्यथा
		status = 'r';

	len = scnम_लिखो(buf, माप(buf), "%c\n", status);
	वापस simple_पढ़ो_from_buffer(userbuf, count, ppos, buf, len);
पूर्ण

अटल स्थिर काष्ठा file_operations tx_queue_status_ops = अणु
	.पढ़ो = tx_queue_status_पढ़ो,
	.खोलो = simple_खोलो,
	.llseek = generic_file_llseek,
पूर्ण;

अटल व्योम wl1251_debugfs_delete_files(काष्ठा wl1251 *wl)
अणु
	DEBUGFS_FWSTATS_DEL(tx, पूर्णांकernal_desc_overflow);

	DEBUGFS_FWSTATS_DEL(rx, out_of_mem);
	DEBUGFS_FWSTATS_DEL(rx, hdr_overflow);
	DEBUGFS_FWSTATS_DEL(rx, hw_stuck);
	DEBUGFS_FWSTATS_DEL(rx, dropped);
	DEBUGFS_FWSTATS_DEL(rx, fcs_err);
	DEBUGFS_FWSTATS_DEL(rx, xfr_hपूर्णांक_trig);
	DEBUGFS_FWSTATS_DEL(rx, path_reset);
	DEBUGFS_FWSTATS_DEL(rx, reset_counter);

	DEBUGFS_FWSTATS_DEL(dma, rx_requested);
	DEBUGFS_FWSTATS_DEL(dma, rx_errors);
	DEBUGFS_FWSTATS_DEL(dma, tx_requested);
	DEBUGFS_FWSTATS_DEL(dma, tx_errors);

	DEBUGFS_FWSTATS_DEL(isr, cmd_cmplt);
	DEBUGFS_FWSTATS_DEL(isr, fiqs);
	DEBUGFS_FWSTATS_DEL(isr, rx_headers);
	DEBUGFS_FWSTATS_DEL(isr, rx_mem_overflow);
	DEBUGFS_FWSTATS_DEL(isr, rx_rdys);
	DEBUGFS_FWSTATS_DEL(isr, irqs);
	DEBUGFS_FWSTATS_DEL(isr, tx_procs);
	DEBUGFS_FWSTATS_DEL(isr, decrypt_करोne);
	DEBUGFS_FWSTATS_DEL(isr, dma0_करोne);
	DEBUGFS_FWSTATS_DEL(isr, dma1_करोne);
	DEBUGFS_FWSTATS_DEL(isr, tx_exch_complete);
	DEBUGFS_FWSTATS_DEL(isr, commands);
	DEBUGFS_FWSTATS_DEL(isr, rx_procs);
	DEBUGFS_FWSTATS_DEL(isr, hw_pm_mode_changes);
	DEBUGFS_FWSTATS_DEL(isr, host_acknowledges);
	DEBUGFS_FWSTATS_DEL(isr, pci_pm);
	DEBUGFS_FWSTATS_DEL(isr, wakeups);
	DEBUGFS_FWSTATS_DEL(isr, low_rssi);

	DEBUGFS_FWSTATS_DEL(wep, addr_key_count);
	DEBUGFS_FWSTATS_DEL(wep, शेष_key_count);
	/* skipping wep.reserved */
	DEBUGFS_FWSTATS_DEL(wep, key_not_found);
	DEBUGFS_FWSTATS_DEL(wep, decrypt_fail);
	DEBUGFS_FWSTATS_DEL(wep, packets);
	DEBUGFS_FWSTATS_DEL(wep, पूर्णांकerrupt);

	DEBUGFS_FWSTATS_DEL(pwr, ps_enter);
	DEBUGFS_FWSTATS_DEL(pwr, elp_enter);
	DEBUGFS_FWSTATS_DEL(pwr, missing_bcns);
	DEBUGFS_FWSTATS_DEL(pwr, wake_on_host);
	DEBUGFS_FWSTATS_DEL(pwr, wake_on_समयr_exp);
	DEBUGFS_FWSTATS_DEL(pwr, tx_with_ps);
	DEBUGFS_FWSTATS_DEL(pwr, tx_without_ps);
	DEBUGFS_FWSTATS_DEL(pwr, rcvd_beacons);
	DEBUGFS_FWSTATS_DEL(pwr, घातer_save_off);
	DEBUGFS_FWSTATS_DEL(pwr, enable_ps);
	DEBUGFS_FWSTATS_DEL(pwr, disable_ps);
	DEBUGFS_FWSTATS_DEL(pwr, fix_tsf_ps);
	/* skipping cont_miss_bcns_spपढ़ो क्रम now */
	DEBUGFS_FWSTATS_DEL(pwr, rcvd_awake_beacons);

	DEBUGFS_FWSTATS_DEL(mic, rx_pkts);
	DEBUGFS_FWSTATS_DEL(mic, calc_failure);

	DEBUGFS_FWSTATS_DEL(aes, encrypt_fail);
	DEBUGFS_FWSTATS_DEL(aes, decrypt_fail);
	DEBUGFS_FWSTATS_DEL(aes, encrypt_packets);
	DEBUGFS_FWSTATS_DEL(aes, decrypt_packets);
	DEBUGFS_FWSTATS_DEL(aes, encrypt_पूर्णांकerrupt);
	DEBUGFS_FWSTATS_DEL(aes, decrypt_पूर्णांकerrupt);

	DEBUGFS_FWSTATS_DEL(event, heart_beat);
	DEBUGFS_FWSTATS_DEL(event, calibration);
	DEBUGFS_FWSTATS_DEL(event, rx_mismatch);
	DEBUGFS_FWSTATS_DEL(event, rx_mem_empty);
	DEBUGFS_FWSTATS_DEL(event, rx_pool);
	DEBUGFS_FWSTATS_DEL(event, oom_late);
	DEBUGFS_FWSTATS_DEL(event, phy_transmit_error);
	DEBUGFS_FWSTATS_DEL(event, tx_stuck);

	DEBUGFS_FWSTATS_DEL(ps, pspoll_समयouts);
	DEBUGFS_FWSTATS_DEL(ps, upsd_समयouts);
	DEBUGFS_FWSTATS_DEL(ps, upsd_max_spसमय);
	DEBUGFS_FWSTATS_DEL(ps, upsd_max_apturn);
	DEBUGFS_FWSTATS_DEL(ps, pspoll_max_apturn);
	DEBUGFS_FWSTATS_DEL(ps, pspoll_utilization);
	DEBUGFS_FWSTATS_DEL(ps, upsd_utilization);

	DEBUGFS_FWSTATS_DEL(rxpipe, rx_prep_beacon_drop);
	DEBUGFS_FWSTATS_DEL(rxpipe, descr_host_पूर्णांक_trig_rx_data);
	DEBUGFS_FWSTATS_DEL(rxpipe, beacon_buffer_thres_host_पूर्णांक_trig_rx_data);
	DEBUGFS_FWSTATS_DEL(rxpipe, missed_beacon_host_पूर्णांक_trig_rx_data);
	DEBUGFS_FWSTATS_DEL(rxpipe, tx_xfr_host_पूर्णांक_trig_rx_data);

	DEBUGFS_DEL(tx_queue_len);
	DEBUGFS_DEL(tx_queue_status);
	DEBUGFS_DEL(retry_count);
	DEBUGFS_DEL(excessive_retries);
पूर्ण

अटल व्योम wl1251_debugfs_add_files(काष्ठा wl1251 *wl)
अणु
	DEBUGFS_FWSTATS_ADD(tx, पूर्णांकernal_desc_overflow);

	DEBUGFS_FWSTATS_ADD(rx, out_of_mem);
	DEBUGFS_FWSTATS_ADD(rx, hdr_overflow);
	DEBUGFS_FWSTATS_ADD(rx, hw_stuck);
	DEBUGFS_FWSTATS_ADD(rx, dropped);
	DEBUGFS_FWSTATS_ADD(rx, fcs_err);
	DEBUGFS_FWSTATS_ADD(rx, xfr_hपूर्णांक_trig);
	DEBUGFS_FWSTATS_ADD(rx, path_reset);
	DEBUGFS_FWSTATS_ADD(rx, reset_counter);

	DEBUGFS_FWSTATS_ADD(dma, rx_requested);
	DEBUGFS_FWSTATS_ADD(dma, rx_errors);
	DEBUGFS_FWSTATS_ADD(dma, tx_requested);
	DEBUGFS_FWSTATS_ADD(dma, tx_errors);

	DEBUGFS_FWSTATS_ADD(isr, cmd_cmplt);
	DEBUGFS_FWSTATS_ADD(isr, fiqs);
	DEBUGFS_FWSTATS_ADD(isr, rx_headers);
	DEBUGFS_FWSTATS_ADD(isr, rx_mem_overflow);
	DEBUGFS_FWSTATS_ADD(isr, rx_rdys);
	DEBUGFS_FWSTATS_ADD(isr, irqs);
	DEBUGFS_FWSTATS_ADD(isr, tx_procs);
	DEBUGFS_FWSTATS_ADD(isr, decrypt_करोne);
	DEBUGFS_FWSTATS_ADD(isr, dma0_करोne);
	DEBUGFS_FWSTATS_ADD(isr, dma1_करोne);
	DEBUGFS_FWSTATS_ADD(isr, tx_exch_complete);
	DEBUGFS_FWSTATS_ADD(isr, commands);
	DEBUGFS_FWSTATS_ADD(isr, rx_procs);
	DEBUGFS_FWSTATS_ADD(isr, hw_pm_mode_changes);
	DEBUGFS_FWSTATS_ADD(isr, host_acknowledges);
	DEBUGFS_FWSTATS_ADD(isr, pci_pm);
	DEBUGFS_FWSTATS_ADD(isr, wakeups);
	DEBUGFS_FWSTATS_ADD(isr, low_rssi);

	DEBUGFS_FWSTATS_ADD(wep, addr_key_count);
	DEBUGFS_FWSTATS_ADD(wep, शेष_key_count);
	/* skipping wep.reserved */
	DEBUGFS_FWSTATS_ADD(wep, key_not_found);
	DEBUGFS_FWSTATS_ADD(wep, decrypt_fail);
	DEBUGFS_FWSTATS_ADD(wep, packets);
	DEBUGFS_FWSTATS_ADD(wep, पूर्णांकerrupt);

	DEBUGFS_FWSTATS_ADD(pwr, ps_enter);
	DEBUGFS_FWSTATS_ADD(pwr, elp_enter);
	DEBUGFS_FWSTATS_ADD(pwr, missing_bcns);
	DEBUGFS_FWSTATS_ADD(pwr, wake_on_host);
	DEBUGFS_FWSTATS_ADD(pwr, wake_on_समयr_exp);
	DEBUGFS_FWSTATS_ADD(pwr, tx_with_ps);
	DEBUGFS_FWSTATS_ADD(pwr, tx_without_ps);
	DEBUGFS_FWSTATS_ADD(pwr, rcvd_beacons);
	DEBUGFS_FWSTATS_ADD(pwr, घातer_save_off);
	DEBUGFS_FWSTATS_ADD(pwr, enable_ps);
	DEBUGFS_FWSTATS_ADD(pwr, disable_ps);
	DEBUGFS_FWSTATS_ADD(pwr, fix_tsf_ps);
	/* skipping cont_miss_bcns_spपढ़ो क्रम now */
	DEBUGFS_FWSTATS_ADD(pwr, rcvd_awake_beacons);

	DEBUGFS_FWSTATS_ADD(mic, rx_pkts);
	DEBUGFS_FWSTATS_ADD(mic, calc_failure);

	DEBUGFS_FWSTATS_ADD(aes, encrypt_fail);
	DEBUGFS_FWSTATS_ADD(aes, decrypt_fail);
	DEBUGFS_FWSTATS_ADD(aes, encrypt_packets);
	DEBUGFS_FWSTATS_ADD(aes, decrypt_packets);
	DEBUGFS_FWSTATS_ADD(aes, encrypt_पूर्णांकerrupt);
	DEBUGFS_FWSTATS_ADD(aes, decrypt_पूर्णांकerrupt);

	DEBUGFS_FWSTATS_ADD(event, heart_beat);
	DEBUGFS_FWSTATS_ADD(event, calibration);
	DEBUGFS_FWSTATS_ADD(event, rx_mismatch);
	DEBUGFS_FWSTATS_ADD(event, rx_mem_empty);
	DEBUGFS_FWSTATS_ADD(event, rx_pool);
	DEBUGFS_FWSTATS_ADD(event, oom_late);
	DEBUGFS_FWSTATS_ADD(event, phy_transmit_error);
	DEBUGFS_FWSTATS_ADD(event, tx_stuck);

	DEBUGFS_FWSTATS_ADD(ps, pspoll_समयouts);
	DEBUGFS_FWSTATS_ADD(ps, upsd_समयouts);
	DEBUGFS_FWSTATS_ADD(ps, upsd_max_spसमय);
	DEBUGFS_FWSTATS_ADD(ps, upsd_max_apturn);
	DEBUGFS_FWSTATS_ADD(ps, pspoll_max_apturn);
	DEBUGFS_FWSTATS_ADD(ps, pspoll_utilization);
	DEBUGFS_FWSTATS_ADD(ps, upsd_utilization);

	DEBUGFS_FWSTATS_ADD(rxpipe, rx_prep_beacon_drop);
	DEBUGFS_FWSTATS_ADD(rxpipe, descr_host_पूर्णांक_trig_rx_data);
	DEBUGFS_FWSTATS_ADD(rxpipe, beacon_buffer_thres_host_पूर्णांक_trig_rx_data);
	DEBUGFS_FWSTATS_ADD(rxpipe, missed_beacon_host_पूर्णांक_trig_rx_data);
	DEBUGFS_FWSTATS_ADD(rxpipe, tx_xfr_host_पूर्णांक_trig_rx_data);

	DEBUGFS_ADD(tx_queue_len, wl->debugfs.rootdir);
	DEBUGFS_ADD(tx_queue_status, wl->debugfs.rootdir);
	DEBUGFS_ADD(retry_count, wl->debugfs.rootdir);
	DEBUGFS_ADD(excessive_retries, wl->debugfs.rootdir);
पूर्ण

व्योम wl1251_debugfs_reset(काष्ठा wl1251 *wl)
अणु
	अगर (wl->stats.fw_stats != शून्य)
		स_रखो(wl->stats.fw_stats, 0, माप(*wl->stats.fw_stats));
	wl->stats.retry_count = 0;
	wl->stats.excessive_retries = 0;
पूर्ण

पूर्णांक wl1251_debugfs_init(काष्ठा wl1251 *wl)
अणु
	wl->stats.fw_stats = kzalloc(माप(*wl->stats.fw_stats), GFP_KERNEL);
	अगर (!wl->stats.fw_stats)
		वापस -ENOMEM;

	wl->debugfs.rootdir = debugfs_create_dir(KBUILD_MODNAME, शून्य);

	wl->debugfs.fw_statistics = debugfs_create_dir("fw-statistics",
						       wl->debugfs.rootdir);

	wl->stats.fw_stats_update = jअगरfies;

	wl1251_debugfs_add_files(wl);

	वापस 0;
पूर्ण

व्योम wl1251_debugfs_निकास(काष्ठा wl1251 *wl)
अणु
	wl1251_debugfs_delete_files(wl);

	kमुक्त(wl->stats.fw_stats);
	wl->stats.fw_stats = शून्य;

	debugfs_हटाओ(wl->debugfs.fw_statistics);
	wl->debugfs.fw_statistics = शून्य;

	debugfs_हटाओ(wl->debugfs.rootdir);
	wl->debugfs.rootdir = शून्य;

पूर्ण
