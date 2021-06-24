<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * mac80211 glue code क्रम mac80211 ST-Ericsson CW1200 drivers
 * DebugFS code
 *
 * Copyright (c) 2010, ST-Ericsson
 * Author: Dmitry Tarnyagin <dmitry.tarnyagin@lockless.no>
 */

#समावेश <linux/module.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/seq_file.h>
#समावेश "cw1200.h"
#समावेश "debug.h"
#समावेश "fwio.h"

/* join_status */
अटल स्थिर अक्षर * स्थिर cw1200_debug_join_status[] = अणु
	"passive",
	"monitor",
	"station (joining)",
	"station (not authenticated yet)",
	"station",
	"adhoc",
	"access point",
पूर्ण;

/* WSM_JOIN_PREAMBLE_... */
अटल स्थिर अक्षर * स्थिर cw1200_debug_preamble[] = अणु
	"long",
	"short",
	"long on 1 and 2 Mbps",
पूर्ण;


अटल स्थिर अक्षर * स्थिर cw1200_debug_link_id[] = अणु
	"OFF",
	"REQ",
	"SOFT",
	"HARD",
	"RESET",
	"RESET_REMAP",
पूर्ण;

अटल स्थिर अक्षर *cw1200_debug_mode(पूर्णांक mode)
अणु
	चयन (mode) अणु
	हाल NL80211_IFTYPE_UNSPECIFIED:
		वापस "unspecified";
	हाल NL80211_IFTYPE_MONITOR:
		वापस "monitor";
	हाल NL80211_IFTYPE_STATION:
		वापस "station";
	हाल NL80211_IFTYPE_ADHOC:
		वापस "adhoc";
	हाल NL80211_IFTYPE_MESH_POINT:
		वापस "mesh point";
	हाल NL80211_IFTYPE_AP:
		वापस "access point";
	हाल NL80211_IFTYPE_P2P_CLIENT:
		वापस "p2p client";
	हाल NL80211_IFTYPE_P2P_GO:
		वापस "p2p go";
	शेष:
		वापस "unsupported";
	पूर्ण
पूर्ण

अटल व्योम cw1200_queue_status_show(काष्ठा seq_file *seq,
				     काष्ठा cw1200_queue *q)
अणु
	पूर्णांक i;
	seq_म_लिखो(seq, "Queue       %d:\n", q->queue_id);
	seq_म_लिखो(seq, "  capacity: %zu\n", q->capacity);
	seq_म_लिखो(seq, "  queued:   %zu\n", q->num_queued);
	seq_म_लिखो(seq, "  pending:  %zu\n", q->num_pending);
	seq_म_लिखो(seq, "  sent:     %zu\n", q->num_sent);
	seq_म_लिखो(seq, "  locked:   %s\n", q->tx_locked_cnt ? "yes" : "no");
	seq_म_लिखो(seq, "  overfull: %s\n", q->overfull ? "yes" : "no");
	seq_माला_दो(seq,   "  link map: 0-> ");
	क्रम (i = 0; i < q->stats->map_capacity; ++i)
		seq_म_लिखो(seq, "%.2d ", q->link_map_cache[i]);
	seq_म_लिखो(seq, "<-%zu\n", q->stats->map_capacity);
पूर्ण

अटल व्योम cw1200_debug_prपूर्णांक_map(काष्ठा seq_file *seq,
				   काष्ठा cw1200_common *priv,
				   स्थिर अक्षर *label,
				   u32 map)
अणु
	पूर्णांक i;
	seq_म_लिखो(seq, "%s0-> ", label);
	क्रम (i = 0; i < priv->tx_queue_stats.map_capacity; ++i)
		seq_म_लिखो(seq, "%s ", (map & BIT(i)) ? "**" : "..");
	seq_म_लिखो(seq, "<-%zu\n", priv->tx_queue_stats.map_capacity - 1);
पूर्ण

अटल पूर्णांक cw1200_status_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	पूर्णांक i;
	काष्ठा list_head *item;
	काष्ठा cw1200_common *priv = seq->निजी;
	काष्ठा cw1200_debug_priv *d = priv->debug;

	seq_माला_दो(seq,   "CW1200 Wireless LAN driver status\n");
	seq_म_लिखो(seq, "Hardware:   %d.%d\n",
		   priv->wsm_caps.hw_id,
		   priv->wsm_caps.hw_subid);
	seq_म_लिखो(seq, "Firmware:   %s %d.%d\n",
		   cw1200_fw_types[priv->wsm_caps.fw_type],
		   priv->wsm_caps.fw_ver,
		   priv->wsm_caps.fw_build);
	seq_म_लिखो(seq, "FW API:     %d\n",
		   priv->wsm_caps.fw_api);
	seq_म_लिखो(seq, "FW caps:    0x%.4X\n",
		   priv->wsm_caps.fw_cap);
	seq_म_लिखो(seq, "FW label:  '%s'\n",
		   priv->wsm_caps.fw_label);
	seq_म_लिखो(seq, "Mode:       %s%s\n",
		   cw1200_debug_mode(priv->mode),
		   priv->listening ? " (listening)" : "");
	seq_म_लिखो(seq, "Join state: %s\n",
		   cw1200_debug_join_status[priv->join_status]);
	अगर (priv->channel)
		seq_म_लिखो(seq, "Channel:    %d%s\n",
			   priv->channel->hw_value,
			   priv->channel_चयन_in_progress ?
			   " (switching)" : "");
	अगर (priv->rx_filter.promiscuous)
		seq_माला_दो(seq,   "Filter:     promisc\n");
	अन्यथा अगर (priv->rx_filter.fcs)
		seq_माला_दो(seq,   "Filter:     fcs\n");
	अगर (priv->rx_filter.bssid)
		seq_माला_दो(seq,   "Filter:     bssid\n");
	अगर (!priv->disable_beacon_filter)
		seq_माला_दो(seq,   "Filter:     beacons\n");

	अगर (priv->enable_beacon ||
	    priv->mode == NL80211_IFTYPE_AP ||
	    priv->mode == NL80211_IFTYPE_ADHOC ||
	    priv->mode == NL80211_IFTYPE_MESH_POINT ||
	    priv->mode == NL80211_IFTYPE_P2P_GO)
		seq_म_लिखो(seq, "Beaconing:  %s\n",
			   priv->enable_beacon ?
			   "enabled" : "disabled");

	क्रम (i = 0; i < 4; ++i)
		seq_म_लिखो(seq, "EDCA(%d):    %d, %d, %d, %d, %d\n", i,
			   priv->edca.params[i].cwmin,
			   priv->edca.params[i].cwmax,
			   priv->edca.params[i].aअगरns,
			   priv->edca.params[i].txop_limit,
			   priv->edca.params[i].max_rx_lअगरeसमय);

	अगर (priv->join_status == CW1200_JOIN_STATUS_STA) अणु
		अटल स्थिर अक्षर *pm_mode = "unknown";
		चयन (priv->घातersave_mode.mode) अणु
		हाल WSM_PSM_ACTIVE:
			pm_mode = "off";
			अवरोध;
		हाल WSM_PSM_PS:
			pm_mode = "on";
			अवरोध;
		हाल WSM_PSM_FAST_PS:
			pm_mode = "dynamic";
			अवरोध;
		पूर्ण
		seq_म_लिखो(seq, "Preamble:   %s\n",
			   cw1200_debug_preamble[priv->association_mode.preamble]);
		seq_म_लिखो(seq, "AMPDU spcn: %d\n",
			   priv->association_mode.mpdu_start_spacing);
		seq_म_लिखो(seq, "Basic rate: 0x%.8X\n",
			   le32_to_cpu(priv->association_mode.basic_rate_set));
		seq_म_लिखो(seq, "Bss lost:   %d beacons\n",
			   priv->bss_params.beacon_lost_count);
		seq_म_लिखो(seq, "AID:        %d\n",
			   priv->bss_params.aid);
		seq_म_लिखो(seq, "Rates:      0x%.8X\n",
			   priv->bss_params.operational_rate_set);
		seq_म_लिखो(seq, "Powersave:  %s\n", pm_mode);
	पूर्ण
	seq_म_लिखो(seq, "HT:         %s\n",
		   cw1200_is_ht(&priv->ht_info) ? "on" : "off");
	अगर (cw1200_is_ht(&priv->ht_info)) अणु
		seq_म_लिखो(seq, "Greenfield: %s\n",
			   cw1200_ht_greenfield(&priv->ht_info) ? "yes" : "no");
		seq_म_लिखो(seq, "AMPDU dens: %d\n",
			   cw1200_ht_ampdu_density(&priv->ht_info));
	पूर्ण
	seq_म_लिखो(seq, "RSSI thold: %d\n",
		   priv->cqm_rssi_thold);
	seq_म_लिखो(seq, "RSSI hyst:  %d\n",
		   priv->cqm_rssi_hyst);
	seq_म_लिखो(seq, "Long retr:  %d\n",
		   priv->दीर्घ_frame_max_tx_count);
	seq_म_लिखो(seq, "Short retr: %d\n",
		   priv->लघु_frame_max_tx_count);
	spin_lock_bh(&priv->tx_policy_cache.lock);
	i = 0;
	list_क्रम_each(item, &priv->tx_policy_cache.used)
		++i;
	spin_unlock_bh(&priv->tx_policy_cache.lock);
	seq_म_लिखो(seq, "RC in use:  %d\n", i);

	seq_माला_दो(seq, "\n");
	क्रम (i = 0; i < 4; ++i) अणु
		cw1200_queue_status_show(seq, &priv->tx_queue[i]);
		seq_माला_दो(seq, "\n");
	पूर्ण

	cw1200_debug_prपूर्णांक_map(seq, priv, "Link map:   ",
			       priv->link_id_map);
	cw1200_debug_prपूर्णांक_map(seq, priv, "Asleep map: ",
			       priv->sta_asleep_mask);
	cw1200_debug_prपूर्णांक_map(seq, priv, "PSPOLL map: ",
			       priv->pspoll_mask);

	seq_माला_दो(seq, "\n");

	क्रम (i = 0; i < CW1200_MAX_STA_IN_AP_MODE; ++i) अणु
		अगर (priv->link_id_db[i].status) अणु
			seq_म_लिखो(seq, "Link %d:     %s, %pM\n",
				   i + 1,
				   cw1200_debug_link_id[priv->link_id_db[i].status],
				   priv->link_id_db[i].mac);
		पूर्ण
	पूर्ण

	seq_माला_दो(seq, "\n");

	seq_म_लिखो(seq, "BH status:  %s\n",
		   atomic_पढ़ो(&priv->bh_term) ? "terminated" : "alive");
	seq_म_लिखो(seq, "Pending RX: %d\n",
		   atomic_पढ़ो(&priv->bh_rx));
	seq_म_लिखो(seq, "Pending TX: %d\n",
		   atomic_पढ़ो(&priv->bh_tx));
	अगर (priv->bh_error)
		seq_म_लिखो(seq, "BH errcode: %d\n",
			   priv->bh_error);
	seq_म_लिखो(seq, "TX bufs:    %d x %d bytes\n",
		   priv->wsm_caps.input_buffers,
		   priv->wsm_caps.input_buffer_size);
	seq_म_लिखो(seq, "Used bufs:  %d\n",
		   priv->hw_bufs_used);
	seq_म_लिखो(seq, "Powermgmt:  %s\n",
		   priv->घातersave_enabled ? "on" : "off");
	seq_म_लिखो(seq, "Device:     %s\n",
		   priv->device_can_sleep ? "asleep" : "awake");

	spin_lock(&priv->wsm_cmd.lock);
	seq_म_लिखो(seq, "WSM status: %s\n",
		   priv->wsm_cmd.करोne ? "idle" : "active");
	seq_म_लिखो(seq, "WSM cmd:    0x%.4X (%td bytes)\n",
		   priv->wsm_cmd.cmd, priv->wsm_cmd.len);
	seq_म_लिखो(seq, "WSM retval: %d\n",
		   priv->wsm_cmd.ret);
	spin_unlock(&priv->wsm_cmd.lock);

	seq_म_लिखो(seq, "Datapath:   %s\n",
		   atomic_पढ़ो(&priv->tx_lock) ? "locked" : "unlocked");
	अगर (atomic_पढ़ो(&priv->tx_lock))
		seq_म_लिखो(seq, "TXlock cnt: %d\n",
			   atomic_पढ़ो(&priv->tx_lock));

	seq_म_लिखो(seq, "TXed:       %d\n",
		   d->tx);
	seq_म_लिखो(seq, "AGG TXed:   %d\n",
		   d->tx_agg);
	seq_म_लिखो(seq, "MULTI TXed: %d (%d)\n",
		   d->tx_multi, d->tx_multi_frames);
	seq_म_लिखो(seq, "RXed:       %d\n",
		   d->rx);
	seq_म_लिखो(seq, "AGG RXed:   %d\n",
		   d->rx_agg);
	seq_म_लिखो(seq, "TX miss:    %d\n",
		   d->tx_cache_miss);
	seq_म_लिखो(seq, "TX align:   %d\n",
		   d->tx_align);
	seq_म_लिखो(seq, "TX burst:   %d\n",
		   d->tx_burst);
	seq_म_लिखो(seq, "TX TTL:     %d\n",
		   d->tx_ttl);
	seq_म_लिखो(seq, "Scan:       %s\n",
		   atomic_पढ़ो(&priv->scan.in_progress) ? "active" : "idle");

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(cw1200_status);

अटल पूर्णांक cw1200_counters_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	पूर्णांक ret;
	काष्ठा cw1200_common *priv = seq->निजी;
	काष्ठा wsm_mib_counters_table counters;

	ret = wsm_get_counters_table(priv, &counters);
	अगर (ret)
		वापस ret;

#घोषणा PUT_COUNTER(tab, name) \
	seq_म_लिखो(seq, "%s:" tab "%d\n", #name, \
		__le32_to_cpu(counters.name))

	PUT_COUNTER("\t\t", plcp_errors);
	PUT_COUNTER("\t\t", fcs_errors);
	PUT_COUNTER("\t\t", tx_packets);
	PUT_COUNTER("\t\t", rx_packets);
	PUT_COUNTER("\t\t", rx_packet_errors);
	PUT_COUNTER("\t",   rx_decryption_failures);
	PUT_COUNTER("\t\t", rx_mic_failures);
	PUT_COUNTER("\t",   rx_no_key_failures);
	PUT_COUNTER("\t",   tx_multicast_frames);
	PUT_COUNTER("\t",   tx_frames_success);
	PUT_COUNTER("\t",   tx_frame_failures);
	PUT_COUNTER("\t",   tx_frames_retried);
	PUT_COUNTER("\t",   tx_frames_multi_retried);
	PUT_COUNTER("\t",   rx_frame_duplicates);
	PUT_COUNTER("\t\t", rts_success);
	PUT_COUNTER("\t\t", rts_failures);
	PUT_COUNTER("\t\t", ack_failures);
	PUT_COUNTER("\t",   rx_multicast_frames);
	PUT_COUNTER("\t",   rx_frames_success);
	PUT_COUNTER("\t",   rx_cmac_icv_errors);
	PUT_COUNTER("\t\t", rx_cmac_replays);
	PUT_COUNTER("\t",   rx_mgmt_ccmp_replays);

#अघोषित PUT_COUNTER

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(cw1200_counters);

अटल sमाप_प्रकार cw1200_wsm_dumps(काष्ठा file *file,
	स्थिर अक्षर __user *user_buf, माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा cw1200_common *priv = file->निजी_data;
	अक्षर buf[1];

	अगर (!count)
		वापस -EINVAL;
	अगर (copy_from_user(buf, user_buf, 1))
		वापस -EFAULT;

	अगर (buf[0] == '1')
		priv->wsm_enable_wsm_dumps = 1;
	अन्यथा
		priv->wsm_enable_wsm_dumps = 0;

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_wsm_dumps = अणु
	.खोलो = simple_खोलो,
	.ग_लिखो = cw1200_wsm_dumps,
	.llseek = शेष_llseek,
पूर्ण;

पूर्णांक cw1200_debug_init(काष्ठा cw1200_common *priv)
अणु
	पूर्णांक ret = -ENOMEM;
	काष्ठा cw1200_debug_priv *d = kzalloc(माप(काष्ठा cw1200_debug_priv),
			GFP_KERNEL);
	priv->debug = d;
	अगर (!d)
		वापस ret;

	d->debugfs_phy = debugfs_create_dir("cw1200",
					    priv->hw->wiphy->debugfsdir);
	debugfs_create_file("status", 0400, d->debugfs_phy, priv,
			    &cw1200_status_fops);
	debugfs_create_file("counters", 0400, d->debugfs_phy, priv,
			    &cw1200_counters_fops);
	debugfs_create_file("wsm_dumps", 0200, d->debugfs_phy, priv,
			    &fops_wsm_dumps);

	वापस 0;
पूर्ण

व्योम cw1200_debug_release(काष्ठा cw1200_common *priv)
अणु
	काष्ठा cw1200_debug_priv *d = priv->debug;
	अगर (d) अणु
		debugfs_हटाओ_recursive(d->debugfs_phy);
		priv->debug = शून्य;
		kमुक्त(d);
	पूर्ण
पूर्ण
