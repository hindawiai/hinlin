<शैली गुरु>
/*
 * NXP Wireless LAN device driver: debugfs
 *
 * Copyright 2011-2020 NXP
 *
 * This software file (the "File") is distributed by NXP
 * under the terms of the GNU General Public License Version 2, June 1991
 * (the "License").  You may use, redistribute and/or modअगरy this File in
 * accordance with the terms and conditions of the License, a copy of which
 * is available by writing to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fअगरth Floor, Boston, MA 02110-1301 USA or on the
 * worldwide web at http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt.
 *
 * THE खाता IS DISTRIBUTED AS-IS, WITHOUT WARRANTY OF ANY KIND, AND THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE
 * ARE EXPRESSLY DISCLAIMED.  The License provides additional details about
 * this warranty disclaimer.
 */

#समावेश <linux/debugfs.h>

#समावेश "main.h"
#समावेश "11n.h"


अटल काष्ठा dentry *mwअगरiex_dfs_dir;

अटल अक्षर *bss_modes[] = अणु
	"UNSPECIFIED",
	"ADHOC",
	"STATION",
	"AP",
	"AP_VLAN",
	"WDS",
	"MONITOR",
	"MESH_POINT",
	"P2P_CLIENT",
	"P2P_GO",
	"P2P_DEVICE",
पूर्ण;

/*
 * Proc info file पढ़ो handler.
 *
 * This function is called when the 'info' file is खोलोed क्रम पढ़ोing.
 * It prपूर्णांकs the following driver related inक्रमmation -
 *      - Driver name
 *      - Driver version
 *      - Driver extended version
 *      - Interface name
 *      - BSS mode
 *      - Media state (connected or disconnected)
 *      - MAC address
 *      - Total number of Tx bytes
 *      - Total number of Rx bytes
 *      - Total number of Tx packets
 *      - Total number of Rx packets
 *      - Total number of dropped Tx packets
 *      - Total number of dropped Rx packets
 *      - Total number of corrupted Tx packets
 *      - Total number of corrupted Rx packets
 *      - Carrier status (on or off)
 *      - Tx queue status (started or stopped)
 *
 * For STA mode drivers, it also prपूर्णांकs the following extra -
 *      - ESSID
 *      - BSSID
 *      - Channel
 *      - Region code
 *      - Multicast count
 *      - Multicast addresses
 */
अटल sमाप_प्रकार
mwअगरiex_info_पढ़ो(काष्ठा file *file, अक्षर __user *ubuf,
		  माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा mwअगरiex_निजी *priv =
		(काष्ठा mwअगरiex_निजी *) file->निजी_data;
	काष्ठा net_device *netdev = priv->netdev;
	काष्ठा netdev_hw_addr *ha;
	काष्ठा netdev_queue *txq;
	अचिन्हित दीर्घ page = get_zeroed_page(GFP_KERNEL);
	अक्षर *p = (अक्षर *) page, fmt[64];
	काष्ठा mwअगरiex_bss_info info;
	sमाप_प्रकार ret;
	पूर्णांक i = 0;

	अगर (!p)
		वापस -ENOMEM;

	स_रखो(&info, 0, माप(info));
	ret = mwअगरiex_get_bss_info(priv, &info);
	अगर (ret)
		जाओ मुक्त_and_निकास;

	mwअगरiex_drv_get_driver_version(priv->adapter, fmt, माप(fmt) - 1);

	mwअगरiex_get_ver_ext(priv, 0);

	p += प्र_लिखो(p, "driver_name = " "\"mwifiex\"\n");
	p += प्र_लिखो(p, "driver_version = %s", fmt);
	p += प्र_लिखो(p, "\nverext = %s", priv->version_str);
	p += प्र_लिखो(p, "\ninterface_name=\"%s\"\n", netdev->name);

	अगर (info.bss_mode >= ARRAY_SIZE(bss_modes))
		p += प्र_लिखो(p, "bss_mode=\"%d\"\n", info.bss_mode);
	अन्यथा
		p += प्र_लिखो(p, "bss_mode=\"%s\"\n", bss_modes[info.bss_mode]);

	p += प्र_लिखो(p, "media_state=\"%s\"\n",
		     (!priv->media_connected ? "Disconnected" : "Connected"));
	p += प्र_लिखो(p, "mac_address=\"%pM\"\n", netdev->dev_addr);

	अगर (GET_BSS_ROLE(priv) == MWIFIEX_BSS_ROLE_STA) अणु
		p += प्र_लिखो(p, "multicast_count=\"%d\"\n",
			     netdev_mc_count(netdev));
		p += प्र_लिखो(p, "essid=\"%.*s\"\n", info.ssid.ssid_len,
			     info.ssid.ssid);
		p += प्र_लिखो(p, "bssid=\"%pM\"\n", info.bssid);
		p += प्र_लिखो(p, "channel=\"%d\"\n", (पूर्णांक) info.bss_chan);
		p += प्र_लिखो(p, "country_code = \"%s\"\n", info.country_code);
		p += प्र_लिखो(p, "region_code=\"0x%x\"\n",
			     priv->adapter->region_code);

		netdev_क्रम_each_mc_addr(ha, netdev)
			p += प्र_लिखो(p, "multicast_address[%d]=\"%pM\"\n",
					i++, ha->addr);
	पूर्ण

	p += प्र_लिखो(p, "num_tx_bytes = %lu\n", priv->stats.tx_bytes);
	p += प्र_लिखो(p, "num_rx_bytes = %lu\n", priv->stats.rx_bytes);
	p += प्र_लिखो(p, "num_tx_pkts = %lu\n", priv->stats.tx_packets);
	p += प्र_लिखो(p, "num_rx_pkts = %lu\n", priv->stats.rx_packets);
	p += प्र_लिखो(p, "num_tx_pkts_dropped = %lu\n", priv->stats.tx_dropped);
	p += प्र_लिखो(p, "num_rx_pkts_dropped = %lu\n", priv->stats.rx_dropped);
	p += प्र_लिखो(p, "num_tx_pkts_err = %lu\n", priv->stats.tx_errors);
	p += प्र_लिखो(p, "num_rx_pkts_err = %lu\n", priv->stats.rx_errors);
	p += प्र_लिखो(p, "carrier %s\n", ((netअगर_carrier_ok(priv->netdev))
					 ? "on" : "off"));
	p += प्र_लिखो(p, "tx queue");
	क्रम (i = 0; i < netdev->num_tx_queues; i++) अणु
		txq = netdev_get_tx_queue(netdev, i);
		p += प्र_लिखो(p, " %d:%s", i, netअगर_tx_queue_stopped(txq) ?
			     "stopped" : "started");
	पूर्ण
	p += प्र_लिखो(p, "\n");

	ret = simple_पढ़ो_from_buffer(ubuf, count, ppos, (अक्षर *) page,
				      (अचिन्हित दीर्घ) p - page);

मुक्त_and_निकास:
	मुक्त_page(page);
	वापस ret;
पूर्ण

/*
 * Proc getlog file पढ़ो handler.
 *
 * This function is called when the 'getlog' file is खोलोed क्रम पढ़ोing
 * It prपूर्णांकs the following log inक्रमmation -
 *      - Number of multicast Tx frames
 *      - Number of failed packets
 *      - Number of Tx retries
 *      - Number of multicast Tx retries
 *      - Number of duplicate frames
 *      - Number of RTS successes
 *      - Number of RTS failures
 *      - Number of ACK failures
 *      - Number of fragmented Rx frames
 *      - Number of multicast Rx frames
 *      - Number of FCS errors
 *      - Number of Tx frames
 *      - WEP ICV error counts
 *      - Number of received beacons
 *      - Number of missed beacons
 */
अटल sमाप_प्रकार
mwअगरiex_getlog_पढ़ो(काष्ठा file *file, अक्षर __user *ubuf,
		    माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा mwअगरiex_निजी *priv =
		(काष्ठा mwअगरiex_निजी *) file->निजी_data;
	अचिन्हित दीर्घ page = get_zeroed_page(GFP_KERNEL);
	अक्षर *p = (अक्षर *) page;
	sमाप_प्रकार ret;
	काष्ठा mwअगरiex_ds_get_stats stats;

	अगर (!p)
		वापस -ENOMEM;

	स_रखो(&stats, 0, माप(stats));
	ret = mwअगरiex_get_stats_info(priv, &stats);
	अगर (ret)
		जाओ मुक्त_and_निकास;

	p += प्र_लिखो(p, "\n"
		     "mcasttxframe     %u\n"
		     "failed           %u\n"
		     "retry            %u\n"
		     "multiretry       %u\n"
		     "framedup         %u\n"
		     "rtssuccess       %u\n"
		     "rtsfailure       %u\n"
		     "ackfailure       %u\n"
		     "rxfrag           %u\n"
		     "mcastrxframe     %u\n"
		     "fcserror         %u\n"
		     "txframe          %u\n"
		     "wepicverrcnt-1   %u\n"
		     "wepicverrcnt-2   %u\n"
		     "wepicverrcnt-3   %u\n"
		     "wepicverrcnt-4   %u\n"
		     "bcn_rcv_cnt   %u\n"
		     "bcn_miss_cnt   %u\n",
		     stats.mcast_tx_frame,
		     stats.failed,
		     stats.retry,
		     stats.multi_retry,
		     stats.frame_dup,
		     stats.rts_success,
		     stats.rts_failure,
		     stats.ack_failure,
		     stats.rx_frag,
		     stats.mcast_rx_frame,
		     stats.fcs_error,
		     stats.tx_frame,
		     stats.wep_icv_error[0],
		     stats.wep_icv_error[1],
		     stats.wep_icv_error[2],
		     stats.wep_icv_error[3],
		     stats.bcn_rcv_cnt,
		     stats.bcn_miss_cnt);


	ret = simple_पढ़ो_from_buffer(ubuf, count, ppos, (अक्षर *) page,
				      (अचिन्हित दीर्घ) p - page);

मुक्त_and_निकास:
	मुक्त_page(page);
	वापस ret;
पूर्ण

/* Sysfs histogram file पढ़ो handler.
 *
 * This function is called when the 'histogram' file is खोलोed क्रम पढ़ोing
 * It prपूर्णांकs the following histogram inक्रमmation -
 *      - Number of histogram samples
 *      - Receive packet number of each rx_rate
 *      - Receive packet number of each snr
 *      - Receive packet number of each nosie_flr
 *      - Receive packet number of each संकेत streath
 */
अटल sमाप_प्रकार
mwअगरiex_histogram_पढ़ो(काष्ठा file *file, अक्षर __user *ubuf,
		       माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा mwअगरiex_निजी *priv =
		(काष्ठा mwअगरiex_निजी *)file->निजी_data;
	sमाप_प्रकार ret;
	काष्ठा mwअगरiex_histogram_data *phist_data;
	पूर्णांक i, value;
	अचिन्हित दीर्घ page = get_zeroed_page(GFP_KERNEL);
	अक्षर *p = (अक्षर *)page;

	अगर (!p)
		वापस -ENOMEM;

	अगर (!priv || !priv->hist_data)
		वापस -EFAULT;
	phist_data = priv->hist_data;

	p += प्र_लिखो(p, "\n"
		     "total samples = %d\n",
		     atomic_पढ़ो(&phist_data->num_samples));

	p += प्र_लिखो(p,
		     "rx rates (in Mbps): 0=1M   1=2M 2=5.5M  3=11M   4=6M   5=9M  6=12M\n"
		     "7=18M  8=24M  9=36M  10=48M  11=54M 12-27=MCS0-15(BW20) 28-43=MCS0-15(BW40)\n");

	अगर (ISSUPP_11ACENABLED(priv->adapter->fw_cap_info)) अणु
		p += प्र_लिखो(p,
			     "44-53=MCS0-9(VHT:BW20) 54-63=MCS0-9(VHT:BW40) 64-73=MCS0-9(VHT:BW80)\n\n");
	पूर्ण अन्यथा अणु
		p += प्र_लिखो(p, "\n");
	पूर्ण

	क्रम (i = 0; i < MWIFIEX_MAX_RX_RATES; i++) अणु
		value = atomic_पढ़ो(&phist_data->rx_rate[i]);
		अगर (value)
			p += प्र_लिखो(p, "rx_rate[%02d] = %d\n", i, value);
	पूर्ण

	अगर (ISSUPP_11ACENABLED(priv->adapter->fw_cap_info)) अणु
		क्रम (i = MWIFIEX_MAX_RX_RATES; i < MWIFIEX_MAX_AC_RX_RATES;
		     i++) अणु
			value = atomic_पढ़ो(&phist_data->rx_rate[i]);
			अगर (value)
				p += प्र_लिखो(p, "rx_rate[%02d] = %d\n",
					   i, value);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < MWIFIEX_MAX_SNR; i++) अणु
		value =  atomic_पढ़ो(&phist_data->snr[i]);
		अगर (value)
			p += प्र_लिखो(p, "snr[%02ddB] = %d\n", i, value);
	पूर्ण
	क्रम (i = 0; i < MWIFIEX_MAX_NOISE_FLR; i++) अणु
		value = atomic_पढ़ो(&phist_data->noise_flr[i]);
		अगर (value)
			p += प्र_लिखो(p, "noise_flr[%02ddBm] = %d\n",
				(पूर्णांक)(i-128), value);
	पूर्ण
	क्रम (i = 0; i < MWIFIEX_MAX_SIG_STRENGTH; i++) अणु
		value = atomic_पढ़ो(&phist_data->sig_str[i]);
		अगर (value)
			p += प्र_लिखो(p, "sig_strength[-%02ddBm] = %d\n",
				i, value);
	पूर्ण

	ret = simple_पढ़ो_from_buffer(ubuf, count, ppos, (अक्षर *)page,
				      (अचिन्हित दीर्घ)p - page);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार
mwअगरiex_histogram_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *ubuf,
			माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा mwअगरiex_निजी *priv = (व्योम *)file->निजी_data;

	अगर (priv && priv->hist_data)
		mwअगरiex_hist_data_reset(priv);
	वापस 0;
पूर्ण

अटल काष्ठा mwअगरiex_debug_info info;

/*
 * Proc debug file पढ़ो handler.
 *
 * This function is called when the 'debug' file is खोलोed क्रम पढ़ोing
 * It prपूर्णांकs the following log inक्रमmation -
 *      - Interrupt count
 *      - WMM AC VO packets count
 *      - WMM AC VI packets count
 *      - WMM AC BE packets count
 *      - WMM AC BK packets count
 *      - Maximum Tx buffer size
 *      - Tx buffer size
 *      - Current Tx buffer size
 *      - Power Save mode
 *      - Power Save state
 *      - Deep Sleep status
 *      - Device wakeup required status
 *      - Number of wakeup tries
 *      - Host Sleep configured status
 *      - Host Sleep activated status
 *      - Number of Tx समयouts
 *      - Number of command समयouts
 *      - Last समयd out command ID
 *      - Last समयd out command action
 *      - Last command ID
 *      - Last command action
 *      - Last command index
 *      - Last command response ID
 *      - Last command response index
 *      - Last event
 *      - Last event index
 *      - Number of host to card command failures
 *      - Number of sleep confirm command failures
 *      - Number of host to card data failure
 *      - Number of deauthentication events
 *      - Number of disassociation events
 *      - Number of link lost events
 *      - Number of deauthentication commands
 *      - Number of association success commands
 *      - Number of association failure commands
 *      - Number of commands sent
 *      - Number of data packets sent
 *      - Number of command responses received
 *      - Number of events received
 *      - Tx BA stream table (TID, RA)
 *      - Rx reorder table (TID, TA, Start winकरोw, Winकरोw size, Buffer)
 */
अटल sमाप_प्रकार
mwअगरiex_debug_पढ़ो(काष्ठा file *file, अक्षर __user *ubuf,
		   माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा mwअगरiex_निजी *priv =
		(काष्ठा mwअगरiex_निजी *) file->निजी_data;
	अचिन्हित दीर्घ page = get_zeroed_page(GFP_KERNEL);
	अक्षर *p = (अक्षर *) page;
	sमाप_प्रकार ret;

	अगर (!p)
		वापस -ENOMEM;

	ret = mwअगरiex_get_debug_info(priv, &info);
	अगर (ret)
		जाओ मुक्त_and_निकास;

	p += mwअगरiex_debug_info_to_buffer(priv, p, &info);

	ret = simple_पढ़ो_from_buffer(ubuf, count, ppos, (अक्षर *) page,
				      (अचिन्हित दीर्घ) p - page);

मुक्त_and_निकास:
	मुक्त_page(page);
	वापस ret;
पूर्ण

अटल u32 saved_reg_type, saved_reg_offset, saved_reg_value;

/*
 * Proc regrdwr file ग_लिखो handler.
 *
 * This function is called when the 'regrdwr' file is खोलोed क्रम writing
 *
 * This function can be used to ग_लिखो to a रेजिस्टर.
 */
अटल sमाप_प्रकार
mwअगरiex_regrdwr_ग_लिखो(काष्ठा file *file,
		      स्थिर अक्षर __user *ubuf, माप_प्रकार count, loff_t *ppos)
अणु
	अक्षर *buf;
	पूर्णांक ret;
	u32 reg_type = 0, reg_offset = 0, reg_value = अच_पूर्णांक_उच्च;

	buf = memdup_user_nul(ubuf, min(count, (माप_प्रकार)(PAGE_SIZE - 1)));
	अगर (IS_ERR(buf))
		वापस PTR_ERR(buf);

	माला_पूछो(buf, "%u %x %x", &reg_type, &reg_offset, &reg_value);

	अगर (reg_type == 0 || reg_offset == 0) अणु
		ret = -EINVAL;
		जाओ करोne;
	पूर्ण अन्यथा अणु
		saved_reg_type = reg_type;
		saved_reg_offset = reg_offset;
		saved_reg_value = reg_value;
		ret = count;
	पूर्ण
करोne:
	kमुक्त(buf);
	वापस ret;
पूर्ण

/*
 * Proc regrdwr file पढ़ो handler.
 *
 * This function is called when the 'regrdwr' file is खोलोed क्रम पढ़ोing
 *
 * This function can be used to पढ़ो from a रेजिस्टर.
 */
अटल sमाप_प्रकार
mwअगरiex_regrdwr_पढ़ो(काष्ठा file *file, अक्षर __user *ubuf,
		     माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा mwअगरiex_निजी *priv =
		(काष्ठा mwअगरiex_निजी *) file->निजी_data;
	अचिन्हित दीर्घ addr = get_zeroed_page(GFP_KERNEL);
	अक्षर *buf = (अक्षर *) addr;
	पूर्णांक pos = 0, ret = 0;
	u32 reg_value;

	अगर (!buf)
		वापस -ENOMEM;

	अगर (!saved_reg_type) अणु
		/* No command has been given */
		pos += snम_लिखो(buf, PAGE_SIZE, "0");
		जाओ करोne;
	पूर्ण
	/* Set command has been given */
	अगर (saved_reg_value != अच_पूर्णांक_उच्च) अणु
		ret = mwअगरiex_reg_ग_लिखो(priv, saved_reg_type, saved_reg_offset,
					saved_reg_value);

		pos += snम_लिखो(buf, PAGE_SIZE, "%u 0x%x 0x%x\n",
				saved_reg_type, saved_reg_offset,
				saved_reg_value);

		ret = simple_पढ़ो_from_buffer(ubuf, count, ppos, buf, pos);

		जाओ करोne;
	पूर्ण
	/* Get command has been given */
	ret = mwअगरiex_reg_पढ़ो(priv, saved_reg_type,
			       saved_reg_offset, &reg_value);
	अगर (ret) अणु
		ret = -EINVAL;
		जाओ करोne;
	पूर्ण

	pos += snम_लिखो(buf, PAGE_SIZE, "%u 0x%x 0x%x\n", saved_reg_type,
			saved_reg_offset, reg_value);

	ret = simple_पढ़ो_from_buffer(ubuf, count, ppos, buf, pos);

करोne:
	मुक्त_page(addr);
	वापस ret;
पूर्ण

/* Proc debug_mask file पढ़ो handler.
 * This function is called when the 'debug_mask' file is खोलोed क्रम पढ़ोing
 * This function can be used पढ़ो driver debugging mask value.
 */
अटल sमाप_प्रकार
mwअगरiex_debug_mask_पढ़ो(काष्ठा file *file, अक्षर __user *ubuf,
			माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा mwअगरiex_निजी *priv =
		(काष्ठा mwअगरiex_निजी *)file->निजी_data;
	अचिन्हित दीर्घ page = get_zeroed_page(GFP_KERNEL);
	अक्षर *buf = (अक्षर *)page;
	माप_प्रकार ret = 0;
	पूर्णांक pos = 0;

	अगर (!buf)
		वापस -ENOMEM;

	pos += snम_लिखो(buf, PAGE_SIZE, "debug mask=0x%08x\n",
			priv->adapter->debug_mask);
	ret = simple_पढ़ो_from_buffer(ubuf, count, ppos, buf, pos);

	मुक्त_page(page);
	वापस ret;
पूर्ण

/* Proc debug_mask file पढ़ो handler.
 * This function is called when the 'debug_mask' file is खोलोed क्रम पढ़ोing
 * This function can be used पढ़ो driver debugging mask value.
 */
अटल sमाप_प्रकार
mwअगरiex_debug_mask_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *ubuf,
			 माप_प्रकार count, loff_t *ppos)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ debug_mask;
	काष्ठा mwअगरiex_निजी *priv = (व्योम *)file->निजी_data;
	अक्षर *buf;

	buf = memdup_user_nul(ubuf, min(count, (माप_प्रकार)(PAGE_SIZE - 1)));
	अगर (IS_ERR(buf))
		वापस PTR_ERR(buf);

	अगर (kम_से_अदीर्घ(buf, 0, &debug_mask)) अणु
		ret = -EINVAL;
		जाओ करोne;
	पूर्ण

	priv->adapter->debug_mask = debug_mask;
	ret = count;
करोne:
	kमुक्त(buf);
	वापस ret;
पूर्ण

/* debugfs verext file ग_लिखो handler.
 * This function is called when the 'verext' file is खोलोed क्रम ग_लिखो
 */
अटल sमाप_प्रकार
mwअगरiex_verext_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *ubuf,
		     माप_प्रकार count, loff_t *ppos)
अणु
	पूर्णांक ret;
	u32 versionstrsel;
	काष्ठा mwअगरiex_निजी *priv = (व्योम *)file->निजी_data;
	अक्षर buf[16];

	स_रखो(buf, 0, माप(buf));

	अगर (copy_from_user(&buf, ubuf, min_t(माप_प्रकार, माप(buf) - 1, count)))
		वापस -EFAULT;

	ret = kstrtou32(buf, 10, &versionstrsel);
	अगर (ret)
		वापस ret;

	priv->versionstrsel = versionstrsel;

	वापस count;
पूर्ण

/* Proc verext file पढ़ो handler.
 * This function is called when the 'verext' file is खोलोed क्रम पढ़ोing
 * This function can be used पढ़ो driver exteneed verion string.
 */
अटल sमाप_प्रकार
mwअगरiex_verext_पढ़ो(काष्ठा file *file, अक्षर __user *ubuf,
		    माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा mwअगरiex_निजी *priv =
		(काष्ठा mwअगरiex_निजी *)file->निजी_data;
	अक्षर buf[256];
	पूर्णांक ret;

	mwअगरiex_get_ver_ext(priv, priv->versionstrsel);
	ret = snम_लिखो(buf, माप(buf), "version string: %s\n",
		       priv->version_str);

	वापस simple_पढ़ो_from_buffer(ubuf, count, ppos, buf, ret);
पूर्ण

/* Proc memrw file ग_लिखो handler.
 * This function is called when the 'memrw' file is खोलोed क्रम writing
 * This function can be used to ग_लिखो to a memory location.
 */
अटल sमाप_प्रकार
mwअगरiex_memrw_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *ubuf, माप_प्रकार count,
		    loff_t *ppos)
अणु
	पूर्णांक ret;
	अक्षर cmd;
	काष्ठा mwअगरiex_ds_mem_rw mem_rw;
	u16 cmd_action;
	काष्ठा mwअगरiex_निजी *priv = (व्योम *)file->निजी_data;
	अक्षर *buf;

	buf = memdup_user_nul(ubuf, min(count, (माप_प्रकार)(PAGE_SIZE - 1)));
	अगर (IS_ERR(buf))
		वापस PTR_ERR(buf);

	ret = माला_पूछो(buf, "%c %x %x", &cmd, &mem_rw.addr, &mem_rw.value);
	अगर (ret != 3) अणु
		ret = -EINVAL;
		जाओ करोne;
	पूर्ण

	अगर ((cmd == 'r') || (cmd == 'R')) अणु
		cmd_action = HostCmd_ACT_GEN_GET;
		mem_rw.value = 0;
	पूर्ण अन्यथा अगर ((cmd == 'w') || (cmd == 'W')) अणु
		cmd_action = HostCmd_ACT_GEN_SET;
	पूर्ण अन्यथा अणु
		ret = -EINVAL;
		जाओ करोne;
	पूर्ण

	स_नकल(&priv->mem_rw, &mem_rw, माप(mem_rw));
	अगर (mwअगरiex_send_cmd(priv, HostCmd_CMD_MEM_ACCESS, cmd_action, 0,
			     &mem_rw, true))
		ret = -1;
	अन्यथा
		ret = count;

करोne:
	kमुक्त(buf);
	वापस ret;
पूर्ण

/* Proc memrw file पढ़ो handler.
 * This function is called when the 'memrw' file is खोलोed क्रम पढ़ोing
 * This function can be used to पढ़ो from a memory location.
 */
अटल sमाप_प्रकार
mwअगरiex_memrw_पढ़ो(काष्ठा file *file, अक्षर __user *ubuf,
		   माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा mwअगरiex_निजी *priv = (व्योम *)file->निजी_data;
	अचिन्हित दीर्घ addr = get_zeroed_page(GFP_KERNEL);
	अक्षर *buf = (अक्षर *)addr;
	पूर्णांक ret, pos = 0;

	अगर (!buf)
		वापस -ENOMEM;

	pos += snम_लिखो(buf, PAGE_SIZE, "0x%x 0x%x\n", priv->mem_rw.addr,
			priv->mem_rw.value);
	ret = simple_पढ़ो_from_buffer(ubuf, count, ppos, buf, pos);

	मुक्त_page(addr);
	वापस ret;
पूर्ण

अटल u32 saved_offset = -1, saved_bytes = -1;

/*
 * Proc rdeeprom file ग_लिखो handler.
 *
 * This function is called when the 'rdeeprom' file is खोलोed क्रम writing
 *
 * This function can be used to ग_लिखो to a RDEEPROM location.
 */
अटल sमाप_प्रकार
mwअगरiex_rdeeprom_ग_लिखो(काष्ठा file *file,
		       स्थिर अक्षर __user *ubuf, माप_प्रकार count, loff_t *ppos)
अणु
	अक्षर *buf;
	पूर्णांक ret = 0;
	पूर्णांक offset = -1, bytes = -1;

	buf = memdup_user_nul(ubuf, min(count, (माप_प्रकार)(PAGE_SIZE - 1)));
	अगर (IS_ERR(buf))
		वापस PTR_ERR(buf);

	माला_पूछो(buf, "%d %d", &offset, &bytes);

	अगर (offset == -1 || bytes == -1) अणु
		ret = -EINVAL;
		जाओ करोne;
	पूर्ण अन्यथा अणु
		saved_offset = offset;
		saved_bytes = bytes;
		ret = count;
	पूर्ण
करोne:
	kमुक्त(buf);
	वापस ret;
पूर्ण

/*
 * Proc rdeeprom पढ़ो ग_लिखो handler.
 *
 * This function is called when the 'rdeeprom' file is खोलोed क्रम पढ़ोing
 *
 * This function can be used to पढ़ो from a RDEEPROM location.
 */
अटल sमाप_प्रकार
mwअगरiex_rdeeprom_पढ़ो(काष्ठा file *file, अक्षर __user *ubuf,
		      माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा mwअगरiex_निजी *priv =
		(काष्ठा mwअगरiex_निजी *) file->निजी_data;
	अचिन्हित दीर्घ addr = get_zeroed_page(GFP_KERNEL);
	अक्षर *buf = (अक्षर *) addr;
	पूर्णांक pos, ret, i;
	u8 value[MAX_EEPROM_DATA];

	अगर (!buf)
		वापस -ENOMEM;

	अगर (saved_offset == -1) अणु
		/* No command has been given */
		pos = snम_लिखो(buf, PAGE_SIZE, "0");
		जाओ करोne;
	पूर्ण

	/* Get command has been given */
	ret = mwअगरiex_eeprom_पढ़ो(priv, (u16) saved_offset,
				  (u16) saved_bytes, value);
	अगर (ret) अणु
		ret = -EINVAL;
		जाओ out_मुक्त;
	पूर्ण

	pos = snम_लिखो(buf, PAGE_SIZE, "%d %d ", saved_offset, saved_bytes);

	क्रम (i = 0; i < saved_bytes; i++)
		pos += scnम_लिखो(buf + pos, PAGE_SIZE - pos, "%d ", value[i]);

करोne:
	ret = simple_पढ़ो_from_buffer(ubuf, count, ppos, buf, pos);
out_मुक्त:
	मुक्त_page(addr);
	वापस ret;
पूर्ण

/* Proc hscfg file ग_लिखो handler
 * This function can be used to configure the host sleep parameters.
 */
अटल sमाप_प्रकार
mwअगरiex_hscfg_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *ubuf,
		    माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा mwअगरiex_निजी *priv = (व्योम *)file->निजी_data;
	अक्षर *buf;
	पूर्णांक ret, arg_num;
	काष्ठा mwअगरiex_ds_hs_cfg hscfg;
	पूर्णांक conditions = HS_CFG_COND_DEF;
	u32 gpio = HS_CFG_GPIO_DEF, gap = HS_CFG_GAP_DEF;

	buf = memdup_user_nul(ubuf, min(count, (माप_प्रकार)(PAGE_SIZE - 1)));
	अगर (IS_ERR(buf))
		वापस PTR_ERR(buf);

	arg_num = माला_पूछो(buf, "%d %x %x", &conditions, &gpio, &gap);

	स_रखो(&hscfg, 0, माप(काष्ठा mwअगरiex_ds_hs_cfg));

	अगर (arg_num > 3) अणु
		mwअगरiex_dbg(priv->adapter, ERROR,
			    "Too many arguments\n");
		ret = -EINVAL;
		जाओ करोne;
	पूर्ण

	अगर (arg_num >= 1 && arg_num < 3)
		mwअगरiex_set_hs_params(priv, HostCmd_ACT_GEN_GET,
				      MWIFIEX_SYNC_CMD, &hscfg);

	अगर (arg_num) अणु
		अगर (conditions == HS_CFG_CANCEL) अणु
			mwअगरiex_cancel_hs(priv, MWIFIEX_ASYNC_CMD);
			ret = count;
			जाओ करोne;
		पूर्ण
		hscfg.conditions = conditions;
	पूर्ण
	अगर (arg_num >= 2)
		hscfg.gpio = gpio;
	अगर (arg_num == 3)
		hscfg.gap = gap;

	hscfg.is_invoke_hostcmd = false;
	mwअगरiex_set_hs_params(priv, HostCmd_ACT_GEN_SET,
			      MWIFIEX_SYNC_CMD, &hscfg);

	mwअगरiex_enable_hs(priv->adapter);
	clear_bit(MWIFIEX_IS_HS_ENABLING, &priv->adapter->work_flags);
	ret = count;
करोne:
	kमुक्त(buf);
	वापस ret;
पूर्ण

/* Proc hscfg file पढ़ो handler
 * This function can be used to पढ़ो host sleep configuration
 * parameters from driver.
 */
अटल sमाप_प्रकार
mwअगरiex_hscfg_पढ़ो(काष्ठा file *file, अक्षर __user *ubuf,
		   माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा mwअगरiex_निजी *priv = (व्योम *)file->निजी_data;
	अचिन्हित दीर्घ addr = get_zeroed_page(GFP_KERNEL);
	अक्षर *buf = (अक्षर *)addr;
	पूर्णांक pos, ret;
	काष्ठा mwअगरiex_ds_hs_cfg hscfg;

	अगर (!buf)
		वापस -ENOMEM;

	mwअगरiex_set_hs_params(priv, HostCmd_ACT_GEN_GET,
			      MWIFIEX_SYNC_CMD, &hscfg);

	pos = snम_लिखो(buf, PAGE_SIZE, "%u 0x%x 0x%x\n", hscfg.conditions,
		       hscfg.gpio, hscfg.gap);

	ret = simple_पढ़ो_from_buffer(ubuf, count, ppos, buf, pos);

	मुक्त_page(addr);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार
mwअगरiex_बारhare_coex_पढ़ो(काष्ठा file *file, अक्षर __user *ubuf,
			    माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा mwअगरiex_निजी *priv = file->निजी_data;
	अक्षर buf[3];
	bool बारhare_coex;
	पूर्णांक ret;
	अचिन्हित पूर्णांक len;

	अगर (priv->adapter->fw_api_ver != MWIFIEX_FW_V15)
		वापस -EOPNOTSUPP;

	ret = mwअगरiex_send_cmd(priv, HostCmd_CMD_ROBUST_COEX,
			       HostCmd_ACT_GEN_GET, 0, &बारhare_coex, true);
	अगर (ret)
		वापस ret;

	len = प्र_लिखो(buf, "%d\n", बारhare_coex);
	वापस simple_पढ़ो_from_buffer(ubuf, count, ppos, buf, len);
पूर्ण

अटल sमाप_प्रकार
mwअगरiex_बारhare_coex_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *ubuf,
			     माप_प्रकार count, loff_t *ppos)
अणु
	bool बारhare_coex;
	काष्ठा mwअगरiex_निजी *priv = file->निजी_data;
	अक्षर kbuf[16];
	पूर्णांक ret;

	अगर (priv->adapter->fw_api_ver != MWIFIEX_FW_V15)
		वापस -EOPNOTSUPP;

	स_रखो(kbuf, 0, माप(kbuf));

	अगर (copy_from_user(&kbuf, ubuf, min_t(माप_प्रकार, माप(kbuf) - 1, count)))
		वापस -EFAULT;

	अगर (strtobool(kbuf, &बारhare_coex))
		वापस -EINVAL;

	ret = mwअगरiex_send_cmd(priv, HostCmd_CMD_ROBUST_COEX,
			       HostCmd_ACT_GEN_SET, 0, &बारhare_coex, true);
	अगर (ret)
		वापस ret;
	अन्यथा
		वापस count;
पूर्ण

अटल sमाप_प्रकार
mwअगरiex_reset_ग_लिखो(काष्ठा file *file,
		    स्थिर अक्षर __user *ubuf, माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा mwअगरiex_निजी *priv = file->निजी_data;
	काष्ठा mwअगरiex_adapter *adapter = priv->adapter;
	bool result;
	पूर्णांक rc;

	rc = kstrtobool_from_user(ubuf, count, &result);
	अगर (rc)
		वापस rc;

	अगर (!result)
		वापस -EINVAL;

	अगर (adapter->अगर_ops.card_reset) अणु
		dev_info(adapter->dev, "Resetting per request\n");
		adapter->अगर_ops.card_reset(adapter);
	पूर्ण

	वापस count;
पूर्ण

#घोषणा MWIFIEX_DFS_ADD_खाता(name) करो अणु                                 \
	debugfs_create_file(#name, 0644, priv->dfs_dev_dir, priv,       \
			    &mwअगरiex_dfs_##name##_fops);                \
पूर्ण जबतक (0);

#घोषणा MWIFIEX_DFS_खाता_OPS(name)                                      \
अटल स्थिर काष्ठा file_operations mwअगरiex_dfs_##name##_fops = अणु       \
	.पढ़ो = mwअगरiex_##name##_पढ़ो,                                  \
	.ग_लिखो = mwअगरiex_##name##_ग_लिखो,                                \
	.खोलो = simple_खोलो,                                            \
पूर्ण;

#घोषणा MWIFIEX_DFS_खाता_READ_OPS(name)                                 \
अटल स्थिर काष्ठा file_operations mwअगरiex_dfs_##name##_fops = अणु       \
	.पढ़ो = mwअगरiex_##name##_पढ़ो,                                  \
	.खोलो = simple_खोलो,                                            \
पूर्ण;

#घोषणा MWIFIEX_DFS_खाता_WRITE_OPS(name)                                \
अटल स्थिर काष्ठा file_operations mwअगरiex_dfs_##name##_fops = अणु       \
	.ग_लिखो = mwअगरiex_##name##_ग_लिखो,                                \
	.खोलो = simple_खोलो,                                            \
पूर्ण;


MWIFIEX_DFS_खाता_READ_OPS(info);
MWIFIEX_DFS_खाता_READ_OPS(debug);
MWIFIEX_DFS_खाता_READ_OPS(getlog);
MWIFIEX_DFS_खाता_OPS(regrdwr);
MWIFIEX_DFS_खाता_OPS(rdeeprom);
MWIFIEX_DFS_खाता_OPS(memrw);
MWIFIEX_DFS_खाता_OPS(hscfg);
MWIFIEX_DFS_खाता_OPS(histogram);
MWIFIEX_DFS_खाता_OPS(debug_mask);
MWIFIEX_DFS_खाता_OPS(बारhare_coex);
MWIFIEX_DFS_खाता_WRITE_OPS(reset);
MWIFIEX_DFS_खाता_OPS(verext);

/*
 * This function creates the debug FS directory काष्ठाure and the files.
 */
व्योम
mwअगरiex_dev_debugfs_init(काष्ठा mwअगरiex_निजी *priv)
अणु
	अगर (!mwअगरiex_dfs_dir || !priv)
		वापस;

	priv->dfs_dev_dir = debugfs_create_dir(priv->netdev->name,
					       mwअगरiex_dfs_dir);

	अगर (!priv->dfs_dev_dir)
		वापस;

	MWIFIEX_DFS_ADD_खाता(info);
	MWIFIEX_DFS_ADD_खाता(debug);
	MWIFIEX_DFS_ADD_खाता(getlog);
	MWIFIEX_DFS_ADD_खाता(regrdwr);
	MWIFIEX_DFS_ADD_खाता(rdeeprom);

	MWIFIEX_DFS_ADD_खाता(memrw);
	MWIFIEX_DFS_ADD_खाता(hscfg);
	MWIFIEX_DFS_ADD_खाता(histogram);
	MWIFIEX_DFS_ADD_खाता(debug_mask);
	MWIFIEX_DFS_ADD_खाता(बारhare_coex);
	MWIFIEX_DFS_ADD_खाता(reset);
	MWIFIEX_DFS_ADD_खाता(verext);
पूर्ण

/*
 * This function हटाओs the debug FS directory काष्ठाure and the files.
 */
व्योम
mwअगरiex_dev_debugfs_हटाओ(काष्ठा mwअगरiex_निजी *priv)
अणु
	अगर (!priv)
		वापस;

	debugfs_हटाओ_recursive(priv->dfs_dev_dir);
पूर्ण

/*
 * This function creates the top level proc directory.
 */
व्योम
mwअगरiex_debugfs_init(व्योम)
अणु
	अगर (!mwअगरiex_dfs_dir)
		mwअगरiex_dfs_dir = debugfs_create_dir("mwifiex", शून्य);
पूर्ण

/*
 * This function हटाओs the top level proc directory.
 */
व्योम
mwअगरiex_debugfs_हटाओ(व्योम)
अणु
	debugfs_हटाओ(mwअगरiex_dfs_dir);
पूर्ण
