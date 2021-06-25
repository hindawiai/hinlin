<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Host AP driver Info Frame processing (part of hostap.o module) */

#समावेश <linux/अगर_arp.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/export.h>
#समावेश <linux/etherdevice.h>
#समावेश "hostap_wlan.h"
#समावेश "hostap.h"
#समावेश "hostap_ap.h"

/* Called only as a tasklet (software IRQ) */
अटल व्योम prism2_info_commtallies16(local_info_t *local, अचिन्हित अक्षर *buf,
				      पूर्णांक left)
अणु
	काष्ठा hfa384x_comm_tallies *tallies;

	अगर (left < माप(काष्ठा hfa384x_comm_tallies)) अणु
		prपूर्णांकk(KERN_DEBUG "%s: too short (len=%d) commtallies "
		       "info frame\n", local->dev->name, left);
		वापस;
	पूर्ण

	tallies = (काष्ठा hfa384x_comm_tallies *) buf;
#घोषणा ADD_COMM_TALLIES(name) \
local->comm_tallies.name += le16_to_cpu(tallies->name)
	ADD_COMM_TALLIES(tx_unicast_frames);
	ADD_COMM_TALLIES(tx_multicast_frames);
	ADD_COMM_TALLIES(tx_fragments);
	ADD_COMM_TALLIES(tx_unicast_octets);
	ADD_COMM_TALLIES(tx_multicast_octets);
	ADD_COMM_TALLIES(tx_deferred_transmissions);
	ADD_COMM_TALLIES(tx_single_retry_frames);
	ADD_COMM_TALLIES(tx_multiple_retry_frames);
	ADD_COMM_TALLIES(tx_retry_limit_exceeded);
	ADD_COMM_TALLIES(tx_discards);
	ADD_COMM_TALLIES(rx_unicast_frames);
	ADD_COMM_TALLIES(rx_multicast_frames);
	ADD_COMM_TALLIES(rx_fragments);
	ADD_COMM_TALLIES(rx_unicast_octets);
	ADD_COMM_TALLIES(rx_multicast_octets);
	ADD_COMM_TALLIES(rx_fcs_errors);
	ADD_COMM_TALLIES(rx_discards_no_buffer);
	ADD_COMM_TALLIES(tx_discards_wrong_sa);
	ADD_COMM_TALLIES(rx_discards_wep_undecryptable);
	ADD_COMM_TALLIES(rx_message_in_msg_fragments);
	ADD_COMM_TALLIES(rx_message_in_bad_msg_fragments);
#अघोषित ADD_COMM_TALLIES
पूर्ण


/* Called only as a tasklet (software IRQ) */
अटल व्योम prism2_info_commtallies32(local_info_t *local, अचिन्हित अक्षर *buf,
				      पूर्णांक left)
अणु
	काष्ठा hfa384x_comm_tallies32 *tallies;

	अगर (left < माप(काष्ठा hfa384x_comm_tallies32)) अणु
		prपूर्णांकk(KERN_DEBUG "%s: too short (len=%d) commtallies32 "
		       "info frame\n", local->dev->name, left);
		वापस;
	पूर्ण

	tallies = (काष्ठा hfa384x_comm_tallies32 *) buf;
#घोषणा ADD_COMM_TALLIES(name) \
local->comm_tallies.name += le32_to_cpu(tallies->name)
	ADD_COMM_TALLIES(tx_unicast_frames);
	ADD_COMM_TALLIES(tx_multicast_frames);
	ADD_COMM_TALLIES(tx_fragments);
	ADD_COMM_TALLIES(tx_unicast_octets);
	ADD_COMM_TALLIES(tx_multicast_octets);
	ADD_COMM_TALLIES(tx_deferred_transmissions);
	ADD_COMM_TALLIES(tx_single_retry_frames);
	ADD_COMM_TALLIES(tx_multiple_retry_frames);
	ADD_COMM_TALLIES(tx_retry_limit_exceeded);
	ADD_COMM_TALLIES(tx_discards);
	ADD_COMM_TALLIES(rx_unicast_frames);
	ADD_COMM_TALLIES(rx_multicast_frames);
	ADD_COMM_TALLIES(rx_fragments);
	ADD_COMM_TALLIES(rx_unicast_octets);
	ADD_COMM_TALLIES(rx_multicast_octets);
	ADD_COMM_TALLIES(rx_fcs_errors);
	ADD_COMM_TALLIES(rx_discards_no_buffer);
	ADD_COMM_TALLIES(tx_discards_wrong_sa);
	ADD_COMM_TALLIES(rx_discards_wep_undecryptable);
	ADD_COMM_TALLIES(rx_message_in_msg_fragments);
	ADD_COMM_TALLIES(rx_message_in_bad_msg_fragments);
#अघोषित ADD_COMM_TALLIES
पूर्ण


/* Called only as a tasklet (software IRQ) */
अटल व्योम prism2_info_commtallies(local_info_t *local, अचिन्हित अक्षर *buf,
				    पूर्णांक left)
अणु
	अगर (local->tallies32)
		prism2_info_commtallies32(local, buf, left);
	अन्यथा
		prism2_info_commtallies16(local, buf, left);
पूर्ण


#अगर_अघोषित PRISM2_NO_STATION_MODES
#अगर_अघोषित PRISM2_NO_DEBUG
अटल स्थिर अक्षर* hfa384x_linkstatus_str(u16 linkstatus)
अणु
	चयन (linkstatus) अणु
	हाल HFA384X_LINKSTATUS_CONNECTED:
		वापस "Connected";
	हाल HFA384X_LINKSTATUS_DISCONNECTED:
		वापस "Disconnected";
	हाल HFA384X_LINKSTATUS_AP_CHANGE:
		वापस "Access point change";
	हाल HFA384X_LINKSTATUS_AP_OUT_OF_RANGE:
		वापस "Access point out of range";
	हाल HFA384X_LINKSTATUS_AP_IN_RANGE:
		वापस "Access point in range";
	हाल HFA384X_LINKSTATUS_ASSOC_FAILED:
		वापस "Association failed";
	शेष:
		वापस "Unknown";
	पूर्ण
पूर्ण
#पूर्ण_अगर /* PRISM2_NO_DEBUG */


/* Called only as a tasklet (software IRQ) */
अटल व्योम prism2_info_linkstatus(local_info_t *local, अचिन्हित अक्षर *buf,
				    पूर्णांक left)
अणु
	u16 val;
	पूर्णांक non_sta_mode;

	/* Alloc new JoinRequests to occur since LinkStatus क्रम the previous
	 * has been received */
	local->last_join_समय = 0;

	अगर (left != 2) अणु
		prपूर्णांकk(KERN_DEBUG "%s: invalid linkstatus info frame "
		       "length %d\n", local->dev->name, left);
		वापस;
	पूर्ण

	non_sta_mode = local->iw_mode == IW_MODE_MASTER ||
		local->iw_mode == IW_MODE_REPEAT ||
		local->iw_mode == IW_MODE_MONITOR;

	val = buf[0] | (buf[1] << 8);
	अगर (!non_sta_mode || val != HFA384X_LINKSTATUS_DISCONNECTED) अणु
		PDEBUG(DEBUG_EXTRA, "%s: LinkStatus=%d (%s)\n",
		       local->dev->name, val, hfa384x_linkstatus_str(val));
	पूर्ण

	अगर (non_sta_mode) अणु
		netअगर_carrier_on(local->dev);
		netअगर_carrier_on(local->ddev);
		वापस;
	पूर्ण

	/* Get current BSSID later in scheduled task */
	set_bit(PRISM2_INFO_PENDING_LINKSTATUS, &local->pending_info);
	local->prev_link_status = val;
	schedule_work(&local->info_queue);
पूर्ण


अटल व्योम prism2_host_roaming(local_info_t *local)
अणु
	काष्ठा hfa384x_join_request req;
	काष्ठा net_device *dev = local->dev;
	काष्ठा hfa384x_hostscan_result *selected, *entry;
	पूर्णांक i;
	अचिन्हित दीर्घ flags;

	अगर (local->last_join_समय &&
	    समय_beक्रमe(jअगरfies, local->last_join_समय + 10 * HZ)) अणु
		PDEBUG(DEBUG_EXTRA, "%s: last join request has not yet been "
		       "completed - waiting for it before issuing new one\n",
		       dev->name);
		वापस;
	पूर्ण

	/* ScanResults are sorted: first ESS results in decreasing संकेत
	 * quality then IBSS results in similar order.
	 * Trivial roaming policy: just select the first entry.
	 * This could probably be improved by adding hysteresis to limit
	 * number of hanकरोffs, etc.
	 *
	 * Could करो periodic RID_SCANREQUEST or Inquire F101 to get new
	 * ScanResults */
	spin_lock_irqsave(&local->lock, flags);
	अगर (local->last_scan_results == शून्य ||
	    local->last_scan_results_count == 0) अणु
		spin_unlock_irqrestore(&local->lock, flags);
		PDEBUG(DEBUG_EXTRA, "%s: no scan results for host roaming\n",
		       dev->name);
		वापस;
	पूर्ण

	selected = &local->last_scan_results[0];

	अगर (local->preferred_ap[0] || local->preferred_ap[1] ||
	    local->preferred_ap[2] || local->preferred_ap[3] ||
	    local->preferred_ap[4] || local->preferred_ap[5]) अणु
		/* Try to find preferred AP */
		PDEBUG(DEBUG_EXTRA, "%s: Preferred AP BSSID %pM\n",
		       dev->name, local->preferred_ap);
		क्रम (i = 0; i < local->last_scan_results_count; i++) अणु
			entry = &local->last_scan_results[i];
			अगर (स_भेद(local->preferred_ap, entry->bssid, 6) == 0)
			अणु
				PDEBUG(DEBUG_EXTRA, "%s: using preferred AP "
				       "selection\n", dev->name);
				selected = entry;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	स_नकल(req.bssid, selected->bssid, ETH_ALEN);
	req.channel = selected->chid;
	spin_unlock_irqrestore(&local->lock, flags);

	PDEBUG(DEBUG_EXTRA, "%s: JoinRequest: BSSID=%pM"
	       " channel=%d\n",
	       dev->name, req.bssid, le16_to_cpu(req.channel));
	अगर (local->func->set_rid(dev, HFA384X_RID_JOINREQUEST, &req,
				 माप(req))) अणु
		prपूर्णांकk(KERN_DEBUG "%s: JoinRequest failed\n", dev->name);
	पूर्ण
	local->last_join_समय = jअगरfies;
पूर्ण


अटल व्योम hostap_report_scan_complete(local_info_t *local)
अणु
	जोड़ iwreq_data wrqu;

	/* Inक्रमm user space about new scan results (just empty event,
	 * SIOCGIWSCAN can be used to fetch data */
	wrqu.data.length = 0;
	wrqu.data.flags = 0;
	wireless_send_event(local->dev, SIOCGIWSCAN, &wrqu, शून्य);

	/* Allow SIOCGIWSCAN handling to occur since we have received
	 * scanning result */
	local->scan_बारtamp = 0;
पूर्ण


/* Called only as a tasklet (software IRQ) */
अटल व्योम prism2_info_scanresults(local_info_t *local, अचिन्हित अक्षर *buf,
				    पूर्णांक left)
अणु
	u16 *pos;
	पूर्णांक new_count, i;
	अचिन्हित दीर्घ flags;
	काष्ठा hfa384x_scan_result *res;
	काष्ठा hfa384x_hostscan_result *results, *prev;

	अगर (left < 4) अणु
		prपूर्णांकk(KERN_DEBUG "%s: invalid scanresult info frame "
		       "length %d\n", local->dev->name, left);
		वापस;
	पूर्ण

	pos = (u16 *) buf;
	pos++;
	pos++;
	left -= 4;

	new_count = left / माप(काष्ठा hfa384x_scan_result);
	results = kदो_स्मृति_array(new_count,
				माप(काष्ठा hfa384x_hostscan_result),
				GFP_ATOMIC);
	अगर (results == शून्य)
		वापस;

	/* Convert to hostscan result क्रमmat. */
	res = (काष्ठा hfa384x_scan_result *) pos;
	क्रम (i = 0; i < new_count; i++) अणु
		स_नकल(&results[i], &res[i],
		       माप(काष्ठा hfa384x_scan_result));
		results[i].atim = 0;
	पूर्ण

	spin_lock_irqsave(&local->lock, flags);
	local->last_scan_type = PRISM2_SCAN;
	prev = local->last_scan_results;
	local->last_scan_results = results;
	local->last_scan_results_count = new_count;
	spin_unlock_irqrestore(&local->lock, flags);
	kमुक्त(prev);

	hostap_report_scan_complete(local);

	/* Perक्रमm rest of ScanResults handling later in scheduled task */
	set_bit(PRISM2_INFO_PENDING_SCANRESULTS, &local->pending_info);
	schedule_work(&local->info_queue);
पूर्ण


/* Called only as a tasklet (software IRQ) */
अटल व्योम prism2_info_hostscanresults(local_info_t *local,
					अचिन्हित अक्षर *buf, पूर्णांक left)
अणु
	पूर्णांक i, result_size, copy_len, new_count;
	काष्ठा hfa384x_hostscan_result *results, *prev;
	अचिन्हित दीर्घ flags;
	__le16 *pos;
	u8 *ptr;

	wake_up_पूर्णांकerruptible(&local->hostscan_wq);

	अगर (left < 4) अणु
		prपूर्णांकk(KERN_DEBUG "%s: invalid hostscanresult info frame "
		       "length %d\n", local->dev->name, left);
		वापस;
	पूर्ण

	pos = (__le16 *) buf;
	copy_len = result_size = le16_to_cpu(*pos);
	अगर (result_size == 0) अणु
		prपूर्णांकk(KERN_DEBUG "%s: invalid result_size (0) in "
		       "hostscanresults\n", local->dev->name);
		वापस;
	पूर्ण
	अगर (copy_len > माप(काष्ठा hfa384x_hostscan_result))
		copy_len = माप(काष्ठा hfa384x_hostscan_result);

	pos++;
	pos++;
	left -= 4;
	ptr = (u8 *) pos;

	new_count = left / result_size;
	results = kसुस्मृति(new_count, माप(काष्ठा hfa384x_hostscan_result),
			  GFP_ATOMIC);
	अगर (results == शून्य)
		वापस;

	क्रम (i = 0; i < new_count; i++) अणु
		स_नकल(&results[i], ptr, copy_len);
		ptr += result_size;
		left -= result_size;
	पूर्ण

	अगर (left) अणु
		prपूर्णांकk(KERN_DEBUG "%s: short HostScan result entry (%d/%d)\n",
		       local->dev->name, left, result_size);
	पूर्ण

	spin_lock_irqsave(&local->lock, flags);
	local->last_scan_type = PRISM2_HOSTSCAN;
	prev = local->last_scan_results;
	local->last_scan_results = results;
	local->last_scan_results_count = new_count;
	spin_unlock_irqrestore(&local->lock, flags);
	kमुक्त(prev);

	hostap_report_scan_complete(local);
पूर्ण
#पूर्ण_अगर /* PRISM2_NO_STATION_MODES */


/* Called only as a tasklet (software IRQ) */
व्योम hostap_info_process(local_info_t *local, काष्ठा sk_buff *skb)
अणु
	काष्ठा hfa384x_info_frame *info;
	अचिन्हित अक्षर *buf;
	पूर्णांक left;
#अगर_अघोषित PRISM2_NO_DEBUG
	पूर्णांक i;
#पूर्ण_अगर /* PRISM2_NO_DEBUG */

	info = (काष्ठा hfa384x_info_frame *) skb->data;
	buf = skb->data + माप(*info);
	left = skb->len - माप(*info);

	चयन (le16_to_cpu(info->type)) अणु
	हाल HFA384X_INFO_COMMTALLIES:
		prism2_info_commtallies(local, buf, left);
		अवरोध;

#अगर_अघोषित PRISM2_NO_STATION_MODES
	हाल HFA384X_INFO_LINKSTATUS:
		prism2_info_linkstatus(local, buf, left);
		अवरोध;

	हाल HFA384X_INFO_SCANRESULTS:
		prism2_info_scanresults(local, buf, left);
		अवरोध;

	हाल HFA384X_INFO_HOSTSCANRESULTS:
		prism2_info_hostscanresults(local, buf, left);
		अवरोध;
#पूर्ण_अगर /* PRISM2_NO_STATION_MODES */

#अगर_अघोषित PRISM2_NO_DEBUG
	शेष:
		PDEBUG(DEBUG_EXTRA, "%s: INFO - len=%d type=0x%04x\n",
		       local->dev->name, le16_to_cpu(info->len),
		       le16_to_cpu(info->type));
		PDEBUG(DEBUG_EXTRA, "Unknown info frame:");
		क्रम (i = 0; i < (left < 100 ? left : 100); i++)
			PDEBUG2(DEBUG_EXTRA, " %02x", buf[i]);
		PDEBUG2(DEBUG_EXTRA, "\n");
		अवरोध;
#पूर्ण_अगर /* PRISM2_NO_DEBUG */
	पूर्ण
पूर्ण


#अगर_अघोषित PRISM2_NO_STATION_MODES
अटल व्योम handle_info_queue_linkstatus(local_info_t *local)
अणु
	पूर्णांक val = local->prev_link_status;
	पूर्णांक connected;
	जोड़ iwreq_data wrqu;

	connected =
		val == HFA384X_LINKSTATUS_CONNECTED ||
		val == HFA384X_LINKSTATUS_AP_CHANGE ||
		val == HFA384X_LINKSTATUS_AP_IN_RANGE;

	अगर (local->func->get_rid(local->dev, HFA384X_RID_CURRENTBSSID,
				 local->bssid, ETH_ALEN, 1) < 0) अणु
		prपूर्णांकk(KERN_DEBUG "%s: could not read CURRENTBSSID after "
		       "LinkStatus event\n", local->dev->name);
	पूर्ण अन्यथा अणु
		PDEBUG(DEBUG_EXTRA, "%s: LinkStatus: BSSID=%pM\n",
		       local->dev->name,
		       (अचिन्हित अक्षर *) local->bssid);
		अगर (local->wds_type & HOSTAP_WDS_AP_CLIENT)
			hostap_add_sta(local->ap, local->bssid);
	पूर्ण

	/* Get BSSID अगर we have a valid AP address */
	अगर (connected) अणु
		netअगर_carrier_on(local->dev);
		netअगर_carrier_on(local->ddev);
		स_नकल(wrqu.ap_addr.sa_data, local->bssid, ETH_ALEN);
	पूर्ण अन्यथा अणु
		netअगर_carrier_off(local->dev);
		netअगर_carrier_off(local->ddev);
		eth_zero_addr(wrqu.ap_addr.sa_data);
	पूर्ण
	wrqu.ap_addr.sa_family = ARPHRD_ETHER;

	/*
	 * Filter out sequential disconnect events in order not to cause a
	 * flood of SIOCGIWAP events that have a race condition with EAPOL
	 * frames and can confuse wpa_supplicant about the current association
	 * status.
	 */
	अगर (connected || local->prev_linkstatus_connected)
		wireless_send_event(local->dev, SIOCGIWAP, &wrqu, शून्य);
	local->prev_linkstatus_connected = connected;
पूर्ण


अटल व्योम handle_info_queue_scanresults(local_info_t *local)
अणु
	अगर (local->host_roaming == 1 && local->iw_mode == IW_MODE_INFRA)
		prism2_host_roaming(local);

	अगर (local->host_roaming == 2 && local->iw_mode == IW_MODE_INFRA &&
	    !is_zero_ether_addr(local->preferred_ap)) अणु
		/*
		 * Firmware seems to be getting पूर्णांकo odd state in host_roaming
		 * mode 2 when hostscan is used without join command, so try
		 * to fix this by re-joining the current AP. This करोes not
		 * actually trigger a new association अगर the current AP is
		 * still in the scan results.
		 */
		prism2_host_roaming(local);
	पूर्ण
पूर्ण


/* Called only as scheduled task after receiving info frames (used to aव्योम
 * pending too much समय in HW IRQ handler). */
अटल व्योम handle_info_queue(काष्ठा work_काष्ठा *work)
अणु
	local_info_t *local = container_of(work, local_info_t, info_queue);

	अगर (test_and_clear_bit(PRISM2_INFO_PENDING_LINKSTATUS,
			       &local->pending_info))
		handle_info_queue_linkstatus(local);

	अगर (test_and_clear_bit(PRISM2_INFO_PENDING_SCANRESULTS,
			       &local->pending_info))
		handle_info_queue_scanresults(local);
पूर्ण
#पूर्ण_अगर /* PRISM2_NO_STATION_MODES */


व्योम hostap_info_init(local_info_t *local)
अणु
	skb_queue_head_init(&local->info_list);
#अगर_अघोषित PRISM2_NO_STATION_MODES
	INIT_WORK(&local->info_queue, handle_info_queue);
#पूर्ण_अगर /* PRISM2_NO_STATION_MODES */
पूर्ण


EXPORT_SYMBOL(hostap_info_init);
EXPORT_SYMBOL(hostap_info_process);
