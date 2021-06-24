<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * This file is part of wl12xx
 *
 * Copyright (C) 2009 Nokia Corporation
 * Copyright (C) 2011-2012 Texas Instruments
 */

#समावेश "../wlcore/debugfs.h"
#समावेश "../wlcore/wlcore.h"

#समावेश "wl12xx.h"
#समावेश "acx.h"
#समावेश "debugfs.h"

#घोषणा WL12XX_DEBUGFS_FWSTATS_खाता(a, b, c) \
	DEBUGFS_FWSTATS_खाता(a, b, c, wl12xx_acx_statistics)

WL12XX_DEBUGFS_FWSTATS_खाता(tx, पूर्णांकernal_desc_overflow, "%u");

WL12XX_DEBUGFS_FWSTATS_खाता(rx, out_of_mem, "%u");
WL12XX_DEBUGFS_FWSTATS_खाता(rx, hdr_overflow, "%u");
WL12XX_DEBUGFS_FWSTATS_खाता(rx, hw_stuck, "%u");
WL12XX_DEBUGFS_FWSTATS_खाता(rx, dropped, "%u");
WL12XX_DEBUGFS_FWSTATS_खाता(rx, fcs_err, "%u");
WL12XX_DEBUGFS_FWSTATS_खाता(rx, xfr_hपूर्णांक_trig, "%u");
WL12XX_DEBUGFS_FWSTATS_खाता(rx, path_reset, "%u");
WL12XX_DEBUGFS_FWSTATS_खाता(rx, reset_counter, "%u");

WL12XX_DEBUGFS_FWSTATS_खाता(dma, rx_requested, "%u");
WL12XX_DEBUGFS_FWSTATS_खाता(dma, rx_errors, "%u");
WL12XX_DEBUGFS_FWSTATS_खाता(dma, tx_requested, "%u");
WL12XX_DEBUGFS_FWSTATS_खाता(dma, tx_errors, "%u");

WL12XX_DEBUGFS_FWSTATS_खाता(isr, cmd_cmplt, "%u");
WL12XX_DEBUGFS_FWSTATS_खाता(isr, fiqs, "%u");
WL12XX_DEBUGFS_FWSTATS_खाता(isr, rx_headers, "%u");
WL12XX_DEBUGFS_FWSTATS_खाता(isr, rx_mem_overflow, "%u");
WL12XX_DEBUGFS_FWSTATS_खाता(isr, rx_rdys, "%u");
WL12XX_DEBUGFS_FWSTATS_खाता(isr, irqs, "%u");
WL12XX_DEBUGFS_FWSTATS_खाता(isr, tx_procs, "%u");
WL12XX_DEBUGFS_FWSTATS_खाता(isr, decrypt_करोne, "%u");
WL12XX_DEBUGFS_FWSTATS_खाता(isr, dma0_करोne, "%u");
WL12XX_DEBUGFS_FWSTATS_खाता(isr, dma1_करोne, "%u");
WL12XX_DEBUGFS_FWSTATS_खाता(isr, tx_exch_complete, "%u");
WL12XX_DEBUGFS_FWSTATS_खाता(isr, commands, "%u");
WL12XX_DEBUGFS_FWSTATS_खाता(isr, rx_procs, "%u");
WL12XX_DEBUGFS_FWSTATS_खाता(isr, hw_pm_mode_changes, "%u");
WL12XX_DEBUGFS_FWSTATS_खाता(isr, host_acknowledges, "%u");
WL12XX_DEBUGFS_FWSTATS_खाता(isr, pci_pm, "%u");
WL12XX_DEBUGFS_FWSTATS_खाता(isr, wakeups, "%u");
WL12XX_DEBUGFS_FWSTATS_खाता(isr, low_rssi, "%u");

WL12XX_DEBUGFS_FWSTATS_खाता(wep, addr_key_count, "%u");
WL12XX_DEBUGFS_FWSTATS_खाता(wep, शेष_key_count, "%u");
/* skipping wep.reserved */
WL12XX_DEBUGFS_FWSTATS_खाता(wep, key_not_found, "%u");
WL12XX_DEBUGFS_FWSTATS_खाता(wep, decrypt_fail, "%u");
WL12XX_DEBUGFS_FWSTATS_खाता(wep, packets, "%u");
WL12XX_DEBUGFS_FWSTATS_खाता(wep, पूर्णांकerrupt, "%u");

WL12XX_DEBUGFS_FWSTATS_खाता(pwr, ps_enter, "%u");
WL12XX_DEBUGFS_FWSTATS_खाता(pwr, elp_enter, "%u");
WL12XX_DEBUGFS_FWSTATS_खाता(pwr, missing_bcns, "%u");
WL12XX_DEBUGFS_FWSTATS_खाता(pwr, wake_on_host, "%u");
WL12XX_DEBUGFS_FWSTATS_खाता(pwr, wake_on_समयr_exp, "%u");
WL12XX_DEBUGFS_FWSTATS_खाता(pwr, tx_with_ps, "%u");
WL12XX_DEBUGFS_FWSTATS_खाता(pwr, tx_without_ps, "%u");
WL12XX_DEBUGFS_FWSTATS_खाता(pwr, rcvd_beacons, "%u");
WL12XX_DEBUGFS_FWSTATS_खाता(pwr, घातer_save_off, "%u");
WL12XX_DEBUGFS_FWSTATS_खाता(pwr, enable_ps, "%u");
WL12XX_DEBUGFS_FWSTATS_खाता(pwr, disable_ps, "%u");
WL12XX_DEBUGFS_FWSTATS_खाता(pwr, fix_tsf_ps, "%u");
/* skipping cont_miss_bcns_spपढ़ो क्रम now */
WL12XX_DEBUGFS_FWSTATS_खाता(pwr, rcvd_awake_beacons, "%u");

WL12XX_DEBUGFS_FWSTATS_खाता(mic, rx_pkts, "%u");
WL12XX_DEBUGFS_FWSTATS_खाता(mic, calc_failure, "%u");

WL12XX_DEBUGFS_FWSTATS_खाता(aes, encrypt_fail, "%u");
WL12XX_DEBUGFS_FWSTATS_खाता(aes, decrypt_fail, "%u");
WL12XX_DEBUGFS_FWSTATS_खाता(aes, encrypt_packets, "%u");
WL12XX_DEBUGFS_FWSTATS_खाता(aes, decrypt_packets, "%u");
WL12XX_DEBUGFS_FWSTATS_खाता(aes, encrypt_पूर्णांकerrupt, "%u");
WL12XX_DEBUGFS_FWSTATS_खाता(aes, decrypt_पूर्णांकerrupt, "%u");

WL12XX_DEBUGFS_FWSTATS_खाता(event, heart_beat, "%u");
WL12XX_DEBUGFS_FWSTATS_खाता(event, calibration, "%u");
WL12XX_DEBUGFS_FWSTATS_खाता(event, rx_mismatch, "%u");
WL12XX_DEBUGFS_FWSTATS_खाता(event, rx_mem_empty, "%u");
WL12XX_DEBUGFS_FWSTATS_खाता(event, rx_pool, "%u");
WL12XX_DEBUGFS_FWSTATS_खाता(event, oom_late, "%u");
WL12XX_DEBUGFS_FWSTATS_खाता(event, phy_transmit_error, "%u");
WL12XX_DEBUGFS_FWSTATS_खाता(event, tx_stuck, "%u");

WL12XX_DEBUGFS_FWSTATS_खाता(ps, pspoll_समयouts, "%u");
WL12XX_DEBUGFS_FWSTATS_खाता(ps, upsd_समयouts, "%u");
WL12XX_DEBUGFS_FWSTATS_खाता(ps, upsd_max_spसमय, "%u");
WL12XX_DEBUGFS_FWSTATS_खाता(ps, upsd_max_apturn, "%u");
WL12XX_DEBUGFS_FWSTATS_खाता(ps, pspoll_max_apturn, "%u");
WL12XX_DEBUGFS_FWSTATS_खाता(ps, pspoll_utilization, "%u");
WL12XX_DEBUGFS_FWSTATS_खाता(ps, upsd_utilization, "%u");

WL12XX_DEBUGFS_FWSTATS_खाता(rxpipe, rx_prep_beacon_drop, "%u");
WL12XX_DEBUGFS_FWSTATS_खाता(rxpipe, descr_host_पूर्णांक_trig_rx_data, "%u");
WL12XX_DEBUGFS_FWSTATS_खाता(rxpipe, beacon_buffer_thres_host_पूर्णांक_trig_rx_data,
			    "%u");
WL12XX_DEBUGFS_FWSTATS_खाता(rxpipe, missed_beacon_host_पूर्णांक_trig_rx_data, "%u");
WL12XX_DEBUGFS_FWSTATS_खाता(rxpipe, tx_xfr_host_पूर्णांक_trig_rx_data, "%u");

पूर्णांक wl12xx_debugfs_add_files(काष्ठा wl1271 *wl,
			     काष्ठा dentry *rootdir)
अणु
	काष्ठा dentry *stats, *moddir;

	moddir = debugfs_create_dir(KBUILD_MODNAME, rootdir);
	stats = debugfs_create_dir("fw_stats", moddir);

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

	वापस 0;
पूर्ण
