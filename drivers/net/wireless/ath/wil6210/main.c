<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2012-2017 Qualcomm Atheros, Inc.
 * Copyright (c) 2018-2019, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/moduleparam.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/rtnetlink.h>

#समावेश "wil6210.h"
#समावेश "txrx.h"
#समावेश "txrx_edma.h"
#समावेश "wmi.h"
#समावेश "boot_loader.h"

#घोषणा WAIT_FOR_HALP_VOTE_MS 100
#घोषणा WAIT_FOR_SCAN_ABORT_MS 1000
#घोषणा WIL_DEFAULT_NUM_RX_STATUS_RINGS 1
#घोषणा WIL_BOARD_खाता_MAX_NAMELEN 128

bool debug_fw; /* = false; */
module_param(debug_fw, bool, 0444);
MODULE_PARM_DESC(debug_fw, " do not perform card reset. For FW debug");

अटल u8 oob_mode;
module_param(oob_mode, byte, 0444);
MODULE_PARM_DESC(oob_mode,
		 " enable out of the box (OOB) mode in FW, for diagnostics and certification");

bool no_fw_recovery;
module_param(no_fw_recovery, bool, 0644);
MODULE_PARM_DESC(no_fw_recovery, " disable automatic FW error recovery");

/* अगर not set via modparam, will be set to शेष value of 1/8 of
 * rx ring size during init flow
 */
अचिन्हित लघु rx_ring_overflow_thrsh = WIL6210_RX_HIGH_TRSH_INIT;
module_param(rx_ring_overflow_thrsh, uलघु, 0444);
MODULE_PARM_DESC(rx_ring_overflow_thrsh,
		 " RX ring overflow threshold in descriptors.");

/* We allow allocation of more than 1 page buffers to support large packets.
 * It is suboptimal behavior perक्रमmance wise in हाल MTU above page size.
 */
अचिन्हित पूर्णांक mtu_max = TXRX_BUF_LEN_DEFAULT - WIL_MAX_MPDU_OVERHEAD;
अटल पूर्णांक mtu_max_set(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp)
अणु
	पूर्णांक ret;

	/* sets mtu_max directly. no need to restore it in हाल of
	 * illegal value since we assume this will fail insmod
	 */
	ret = param_set_uपूर्णांक(val, kp);
	अगर (ret)
		वापस ret;

	अगर (mtu_max < 68 || mtu_max > WIL_MAX_ETH_MTU)
		ret = -EINVAL;

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा kernel_param_ops mtu_max_ops = अणु
	.set = mtu_max_set,
	.get = param_get_uपूर्णांक,
पूर्ण;

module_param_cb(mtu_max, &mtu_max_ops, &mtu_max, 0444);
MODULE_PARM_DESC(mtu_max, " Max MTU value.");

अटल uपूर्णांक rx_ring_order;
अटल uपूर्णांक tx_ring_order = WIL_TX_RING_SIZE_ORDER_DEFAULT;
अटल uपूर्णांक bcast_ring_order = WIL_BCAST_RING_SIZE_ORDER_DEFAULT;

अटल पूर्णांक ring_order_set(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp)
अणु
	पूर्णांक ret;
	uपूर्णांक x;

	ret = kstrtouपूर्णांक(val, 0, &x);
	अगर (ret)
		वापस ret;

	अगर ((x < WIL_RING_SIZE_ORDER_MIN) || (x > WIL_RING_SIZE_ORDER_MAX))
		वापस -EINVAL;

	*((uपूर्णांक *)kp->arg) = x;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा kernel_param_ops ring_order_ops = अणु
	.set = ring_order_set,
	.get = param_get_uपूर्णांक,
पूर्ण;

module_param_cb(rx_ring_order, &ring_order_ops, &rx_ring_order, 0444);
MODULE_PARM_DESC(rx_ring_order, " Rx ring order; size = 1 << order");
module_param_cb(tx_ring_order, &ring_order_ops, &tx_ring_order, 0444);
MODULE_PARM_DESC(tx_ring_order, " Tx ring order; size = 1 << order");
module_param_cb(bcast_ring_order, &ring_order_ops, &bcast_ring_order, 0444);
MODULE_PARM_DESC(bcast_ring_order, " Bcast ring order; size = 1 << order");

क्रमागत अणु
	WIL_BOOT_ERR,
	WIL_BOOT_VANILLA,
	WIL_BOOT_PRODUCTION,
	WIL_BOOT_DEVELOPMENT,
पूर्ण;

क्रमागत अणु
	WIL_SIG_STATUS_VANILLA = 0x0,
	WIL_SIG_STATUS_DEVELOPMENT = 0x1,
	WIL_SIG_STATUS_PRODUCTION = 0x2,
	WIL_SIG_STATUS_CORRUPTED_PRODUCTION = 0x3,
पूर्ण;

#घोषणा RST_DELAY (20) /* msec, क्रम loop in @wil_रुको_device_पढ़ोy */
#घोषणा RST_COUNT (1 + 1000/RST_DELAY) /* round up to be above 1 sec total */

#घोषणा PMU_READY_DELAY_MS (4) /* ms, क्रम sleep in @wil_रुको_device_पढ़ोy */

#घोषणा OTP_HW_DELAY (200) /* usec, loop in @wil_रुको_device_पढ़ोy_talyn_mb */
/* round up to be above 2 ms total */
#घोषणा OTP_HW_COUNT (1 + 2000 / OTP_HW_DELAY)

/*
 * Due to a hardware issue,
 * one has to पढ़ो/ग_लिखो to/from NIC in 32-bit chunks;
 * regular स_नकल_fromio and siblings will
 * not work on 64-bit platक्रमm - it uses 64-bit transactions
 *
 * Force 32-bit transactions to enable NIC on 64-bit platक्रमms
 *
 * To aव्योम byte swap on big endian host, __raw_अणुपढ़ो|ग_लिखोपूर्णl
 * should be used - अणुपढ़ो|ग_लिखोपूर्णl would swap bytes to provide
 * little endian on PCI value in host endianness.
 */
व्योम wil_स_नकल_fromio_32(व्योम *dst, स्थिर अस्थिर व्योम __iomem *src,
			  माप_प्रकार count)
अणु
	u32 *d = dst;
	स्थिर अस्थिर u32 __iomem *s = src;

	क्रम (; count >= 4; count -= 4)
		*d++ = __raw_पढ़ोl(s++);

	अगर (unlikely(count)) अणु
		/* count can be 1..3 */
		u32 पंचांगp = __raw_पढ़ोl(s);

		स_नकल(d, &पंचांगp, count);
	पूर्ण
पूर्ण

व्योम wil_स_नकल_toio_32(अस्थिर व्योम __iomem *dst, स्थिर व्योम *src,
			माप_प्रकार count)
अणु
	अस्थिर u32 __iomem *d = dst;
	स्थिर u32 *s = src;

	क्रम (; count >= 4; count -= 4)
		__raw_ग_लिखोl(*s++, d++);

	अगर (unlikely(count)) अणु
		/* count can be 1..3 */
		u32 पंचांगp = 0;

		स_नकल(&पंचांगp, s, count);
		__raw_ग_लिखोl(पंचांगp, d);
	पूर्ण
पूर्ण

/* Device memory access is prohibited जबतक reset or suspend.
 * wil_mem_access_lock protects accessing device memory in these हालs
 */
पूर्णांक wil_mem_access_lock(काष्ठा wil6210_priv *wil)
अणु
	अगर (!करोwn_पढ़ो_trylock(&wil->mem_lock))
		वापस -EBUSY;

	अगर (test_bit(wil_status_suspending, wil->status) ||
	    test_bit(wil_status_suspended, wil->status)) अणु
		up_पढ़ो(&wil->mem_lock);
		वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण

व्योम wil_mem_access_unlock(काष्ठा wil6210_priv *wil)
अणु
	up_पढ़ो(&wil->mem_lock);
पूर्ण

अटल व्योम wil_ring_fini_tx(काष्ठा wil6210_priv *wil, पूर्णांक id)
अणु
	काष्ठा wil_ring *ring = &wil->ring_tx[id];
	काष्ठा wil_ring_tx_data *txdata = &wil->ring_tx_data[id];

	lockdep_निश्चित_held(&wil->mutex);

	अगर (!ring->va)
		वापस;

	wil_dbg_misc(wil, "vring_fini_tx: id=%d\n", id);

	spin_lock_bh(&txdata->lock);
	txdata->करोt1x_खोलो = false;
	txdata->mid = U8_MAX;
	txdata->enabled = 0; /* no Tx can be in progress or start anew */
	spin_unlock_bh(&txdata->lock);
	/* napi_synchronize रुकोs क्रम completion of the current NAPI but will
	 * not prevent the next NAPI run.
	 * Add a memory barrier to guarantee that txdata->enabled is zeroed
	 * beक्रमe napi_synchronize so that the next scheduled NAPI will not
	 * handle this vring
	 */
	wmb();
	/* make sure NAPI won't touch this vring */
	अगर (test_bit(wil_status_napi_en, wil->status))
		napi_synchronize(&wil->napi_tx);

	wil->txrx_ops.ring_fini_tx(wil, ring);
पूर्ण

अटल bool wil_vअगर_is_connected(काष्ठा wil6210_priv *wil, u8 mid)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < wil->max_assoc_sta; i++) अणु
		अगर (wil->sta[i].mid == mid &&
		    wil->sta[i].status == wil_sta_connected)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम wil_disconnect_cid_complete(काष्ठा wil6210_vअगर *vअगर, पूर्णांक cid,
					u16 reason_code)
__acquires(&sta->tid_rx_lock) __releases(&sta->tid_rx_lock)
अणु
	uपूर्णांक i;
	काष्ठा wil6210_priv *wil = vअगर_to_wil(vअगर);
	काष्ठा net_device *ndev = vअगर_to_ndev(vअगर);
	काष्ठा wireless_dev *wdev = vअगर_to_wdev(vअगर);
	काष्ठा wil_sta_info *sta = &wil->sta[cid];
	पूर्णांक min_ring_id = wil_get_min_tx_ring_id(wil);

	might_sleep();
	wil_dbg_misc(wil,
		     "disconnect_cid_complete: CID %d, MID %d, status %d\n",
		     cid, sta->mid, sta->status);
	/* inक्रमm upper layers */
	अगर (sta->status != wil_sta_unused) अणु
		अगर (vअगर->mid != sta->mid) अणु
			wil_err(wil, "STA MID mismatch with VIF MID(%d)\n",
				vअगर->mid);
		पूर्ण

		चयन (wdev->अगरtype) अणु
		हाल NL80211_IFTYPE_AP:
		हाल NL80211_IFTYPE_P2P_GO:
			/* AP-like पूर्णांकerface */
			cfg80211_del_sta(ndev, sta->addr, GFP_KERNEL);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		sta->status = wil_sta_unused;
		sta->mid = U8_MAX;
	पूर्ण
	/* reorder buffers */
	क्रम (i = 0; i < WIL_STA_TID_NUM; i++) अणु
		काष्ठा wil_tid_ampdu_rx *r;

		spin_lock_bh(&sta->tid_rx_lock);

		r = sta->tid_rx[i];
		sta->tid_rx[i] = शून्य;
		wil_tid_ampdu_rx_मुक्त(wil, r);

		spin_unlock_bh(&sta->tid_rx_lock);
	पूर्ण
	/* crypto context */
	स_रखो(sta->tid_crypto_rx, 0, माप(sta->tid_crypto_rx));
	स_रखो(&sta->group_crypto_rx, 0, माप(sta->group_crypto_rx));
	/* release vrings */
	क्रम (i = min_ring_id; i < ARRAY_SIZE(wil->ring_tx); i++) अणु
		अगर (wil->ring2cid_tid[i][0] == cid)
			wil_ring_fini_tx(wil, i);
	पूर्ण
	/* statistics */
	स_रखो(&sta->stats, 0, माप(sta->stats));
	sta->stats.tx_latency_min_us = U32_MAX;
पूर्ण

अटल व्योम _wil6210_disconnect_complete(काष्ठा wil6210_vअगर *vअगर,
					 स्थिर u8 *bssid, u16 reason_code)
अणु
	काष्ठा wil6210_priv *wil = vअगर_to_wil(vअगर);
	पूर्णांक cid = -ENOENT;
	काष्ठा net_device *ndev;
	काष्ठा wireless_dev *wdev;

	ndev = vअगर_to_ndev(vअगर);
	wdev = vअगर_to_wdev(vअगर);

	might_sleep();
	wil_info(wil, "disconnect_complete: bssid=%pM, reason=%d\n",
		 bssid, reason_code);

	/* Cases are:
	 * - disconnect single STA, still connected
	 * - disconnect single STA, alपढ़ोy disconnected
	 * - disconnect all
	 *
	 * For "disconnect all", there are 3 options:
	 * - bssid == शून्य
	 * - bssid is broadcast address (ff:ff:ff:ff:ff:ff)
	 * - bssid is our MAC address
	 */
	अगर (bssid && !is_broadcast_ether_addr(bssid) &&
	    !ether_addr_equal_unaligned(ndev->dev_addr, bssid)) अणु
		cid = wil_find_cid(wil, vअगर->mid, bssid);
		wil_dbg_misc(wil,
			     "Disconnect complete %pM, CID=%d, reason=%d\n",
			     bssid, cid, reason_code);
		अगर (wil_cid_valid(wil, cid)) /* disconnect 1 peer */
			wil_disconnect_cid_complete(vअगर, cid, reason_code);
	पूर्ण अन्यथा अणु /* all */
		wil_dbg_misc(wil, "Disconnect complete all\n");
		क्रम (cid = 0; cid < wil->max_assoc_sta; cid++)
			wil_disconnect_cid_complete(vअगर, cid, reason_code);
	पूर्ण

	/* link state */
	चयन (wdev->अगरtype) अणु
	हाल NL80211_IFTYPE_STATION:
	हाल NL80211_IFTYPE_P2P_CLIENT:
		wil_bcast_fini(vअगर);
		wil_update_net_queues_bh(wil, vअगर, शून्य, true);
		netअगर_carrier_off(ndev);
		अगर (!wil_has_other_active_अगरaces(wil, ndev, false, true))
			wil6210_bus_request(wil, WIL_DEFAULT_BUS_REQUEST_KBPS);

		अगर (test_and_clear_bit(wil_vअगर_fwconnected, vअगर->status)) अणु
			atomic_dec(&wil->connected_vअगरs);
			cfg80211_disconnected(ndev, reason_code,
					      शून्य, 0,
					      vअगर->locally_generated_disc,
					      GFP_KERNEL);
			vअगर->locally_generated_disc = false;
		पूर्ण अन्यथा अगर (test_bit(wil_vअगर_fwconnecting, vअगर->status)) अणु
			cfg80211_connect_result(ndev, bssid, शून्य, 0, शून्य, 0,
						WLAN_STATUS_UNSPECIFIED_FAILURE,
						GFP_KERNEL);
			vअगर->bss = शून्य;
		पूर्ण
		clear_bit(wil_vअगर_fwconnecting, vअगर->status);
		clear_bit(wil_vअगर_ft_roam, vअगर->status);
		vअगर->ptk_rekey_state = WIL_REKEY_IDLE;

		अवरोध;
	हाल NL80211_IFTYPE_AP:
	हाल NL80211_IFTYPE_P2P_GO:
		अगर (!wil_vअगर_is_connected(wil, vअगर->mid)) अणु
			wil_update_net_queues_bh(wil, vअगर, शून्य, true);
			अगर (test_and_clear_bit(wil_vअगर_fwconnected,
					       vअगर->status))
				atomic_dec(&wil->connected_vअगरs);
		पूर्ण अन्यथा अणु
			wil_update_net_queues_bh(wil, vअगर, शून्य, false);
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक wil_disconnect_cid(काष्ठा wil6210_vअगर *vअगर, पूर्णांक cid,
			      u16 reason_code)
अणु
	काष्ठा wil6210_priv *wil = vअगर_to_wil(vअगर);
	काष्ठा wireless_dev *wdev = vअगर_to_wdev(vअगर);
	काष्ठा wil_sta_info *sta = &wil->sta[cid];
	bool del_sta = false;

	might_sleep();
	wil_dbg_misc(wil, "disconnect_cid: CID %d, MID %d, status %d\n",
		     cid, sta->mid, sta->status);

	अगर (sta->status == wil_sta_unused)
		वापस 0;

	अगर (vअगर->mid != sta->mid) अणु
		wil_err(wil, "STA MID mismatch with VIF MID(%d)\n", vअगर->mid);
		वापस -EINVAL;
	पूर्ण

	/* inक्रमm lower layers */
	अगर (wdev->अगरtype == NL80211_IFTYPE_AP && disable_ap_sme)
		del_sta = true;

	/* disconnect by sending command disconnect/del_sta and रुको
	 * synchronously क्रम WMI_DISCONNECT_EVENTID event.
	 */
	वापस wmi_disconnect_sta(vअगर, sta->addr, reason_code, del_sta);
पूर्ण

अटल व्योम _wil6210_disconnect(काष्ठा wil6210_vअगर *vअगर, स्थिर u8 *bssid,
				u16 reason_code)
अणु
	काष्ठा wil6210_priv *wil;
	काष्ठा net_device *ndev;
	पूर्णांक cid = -ENOENT;

	अगर (unlikely(!vअगर))
		वापस;

	wil = vअगर_to_wil(vअगर);
	ndev = vअगर_to_ndev(vअगर);

	might_sleep();
	wil_info(wil, "disconnect bssid=%pM, reason=%d\n", bssid, reason_code);

	/* Cases are:
	 * - disconnect single STA, still connected
	 * - disconnect single STA, alपढ़ोy disconnected
	 * - disconnect all
	 *
	 * For "disconnect all", there are 3 options:
	 * - bssid == शून्य
	 * - bssid is broadcast address (ff:ff:ff:ff:ff:ff)
	 * - bssid is our MAC address
	 */
	अगर (bssid && !is_broadcast_ether_addr(bssid) &&
	    !ether_addr_equal_unaligned(ndev->dev_addr, bssid)) अणु
		cid = wil_find_cid(wil, vअगर->mid, bssid);
		wil_dbg_misc(wil, "Disconnect %pM, CID=%d, reason=%d\n",
			     bssid, cid, reason_code);
		अगर (wil_cid_valid(wil, cid)) /* disconnect 1 peer */
			wil_disconnect_cid(vअगर, cid, reason_code);
	पूर्ण अन्यथा अणु /* all */
		wil_dbg_misc(wil, "Disconnect all\n");
		क्रम (cid = 0; cid < wil->max_assoc_sta; cid++)
			wil_disconnect_cid(vअगर, cid, reason_code);
	पूर्ण

	/* call event handler manually after processing wmi_call,
	 * to aव्योम deadlock - disconnect event handler acquires
	 * wil->mutex जबतक it is alपढ़ोy held here
	 */
	_wil6210_disconnect_complete(vअगर, bssid, reason_code);
पूर्ण

व्योम wil_disconnect_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा wil6210_vअगर *vअगर = container_of(work,
			काष्ठा wil6210_vअगर, disconnect_worker);
	काष्ठा wil6210_priv *wil = vअगर_to_wil(vअगर);
	काष्ठा net_device *ndev = vअगर_to_ndev(vअगर);
	पूर्णांक rc;
	काष्ठा अणु
		काष्ठा wmi_cmd_hdr wmi;
		काष्ठा wmi_disconnect_event evt;
	पूर्ण __packed reply;

	अगर (test_bit(wil_vअगर_fwconnected, vअगर->status))
		/* connect succeeded after all */
		वापस;

	अगर (!test_bit(wil_vअगर_fwconnecting, vअगर->status))
		/* alपढ़ोy disconnected */
		वापस;

	स_रखो(&reply, 0, माप(reply));

	rc = wmi_call(wil, WMI_DISCONNECT_CMDID, vअगर->mid, शून्य, 0,
		      WMI_DISCONNECT_EVENTID, &reply, माप(reply),
		      WIL6210_DISCONNECT_TO_MS);
	अगर (rc) अणु
		wil_err(wil, "disconnect error %d\n", rc);
		वापस;
	पूर्ण

	wil_update_net_queues_bh(wil, vअगर, शून्य, true);
	netअगर_carrier_off(ndev);
	cfg80211_connect_result(ndev, शून्य, शून्य, 0, शून्य, 0,
				WLAN_STATUS_UNSPECIFIED_FAILURE, GFP_KERNEL);
	clear_bit(wil_vअगर_fwconnecting, vअगर->status);
पूर्ण

अटल पूर्णांक wil_रुको_क्रम_recovery(काष्ठा wil6210_priv *wil)
अणु
	अगर (रुको_event_पूर्णांकerruptible(wil->wq, wil->recovery_state !=
				     fw_recovery_pending)) अणु
		wil_err(wil, "Interrupt, canceling recovery\n");
		वापस -ERESTARTSYS;
	पूर्ण
	अगर (wil->recovery_state != fw_recovery_running) अणु
		wil_info(wil, "Recovery cancelled\n");
		वापस -EINTR;
	पूर्ण
	wil_info(wil, "Proceed with recovery\n");
	वापस 0;
पूर्ण

व्योम wil_set_recovery_state(काष्ठा wil6210_priv *wil, पूर्णांक state)
अणु
	wil_dbg_misc(wil, "set_recovery_state: %d -> %d\n",
		     wil->recovery_state, state);

	wil->recovery_state = state;
	wake_up_पूर्णांकerruptible(&wil->wq);
पूर्ण

bool wil_is_recovery_blocked(काष्ठा wil6210_priv *wil)
अणु
	वापस no_fw_recovery && (wil->recovery_state == fw_recovery_pending);
पूर्ण

अटल व्योम wil_fw_error_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा wil6210_priv *wil = container_of(work, काष्ठा wil6210_priv,
						fw_error_worker);
	काष्ठा net_device *ndev = wil->मुख्य_ndev;
	काष्ठा wireless_dev *wdev;

	wil_dbg_misc(wil, "fw error worker\n");

	अगर (!ndev || !(ndev->flags & IFF_UP)) अणु
		wil_info(wil, "No recovery - interface is down\n");
		वापस;
	पूर्ण
	wdev = ndev->ieee80211_ptr;

	/* increment @recovery_count अगर less then WIL6210_FW_RECOVERY_TO
	 * passed since last recovery attempt
	 */
	अगर (समय_is_after_jअगरfies(wil->last_fw_recovery +
				  WIL6210_FW_RECOVERY_TO))
		wil->recovery_count++;
	अन्यथा
		wil->recovery_count = 1; /* fw was alive क्रम a दीर्घ समय */

	अगर (wil->recovery_count > WIL6210_FW_RECOVERY_RETRIES) अणु
		wil_err(wil, "too many recovery attempts (%d), giving up\n",
			wil->recovery_count);
		वापस;
	पूर्ण

	wil->last_fw_recovery = jअगरfies;

	wil_info(wil, "fw error recovery requested (try %d)...\n",
		 wil->recovery_count);
	अगर (!no_fw_recovery)
		wil->recovery_state = fw_recovery_running;
	अगर (wil_रुको_क्रम_recovery(wil) != 0)
		वापस;

	rtnl_lock();
	mutex_lock(&wil->mutex);
	/* Needs adaptation क्रम multiple VIFs
	 * need to go over all VIFs and consider the appropriate
	 * recovery because each one can have dअगरferent अगरtype.
	 */
	चयन (wdev->अगरtype) अणु
	हाल NL80211_IFTYPE_STATION:
	हाल NL80211_IFTYPE_P2P_CLIENT:
	हाल NL80211_IFTYPE_MONITOR:
		/* silent recovery, upper layers will see disconnect */
		__wil_करोwn(wil);
		__wil_up(wil);
		अवरोध;
	हाल NL80211_IFTYPE_AP:
	हाल NL80211_IFTYPE_P2P_GO:
		अगर (no_fw_recovery) /* upper layers करो recovery */
			अवरोध;
		/* silent recovery, upper layers will see disconnect */
		__wil_करोwn(wil);
		__wil_up(wil);
		mutex_unlock(&wil->mutex);
		wil_cfg80211_ap_recovery(wil);
		mutex_lock(&wil->mutex);
		wil_info(wil, "... completed\n");
		अवरोध;
	शेष:
		wil_err(wil, "No recovery - unknown interface type %d\n",
			wdev->अगरtype);
		अवरोध;
	पूर्ण

	mutex_unlock(&wil->mutex);
	rtnl_unlock();
पूर्ण

अटल पूर्णांक wil_find_मुक्त_ring(काष्ठा wil6210_priv *wil)
अणु
	पूर्णांक i;
	पूर्णांक min_ring_id = wil_get_min_tx_ring_id(wil);

	क्रम (i = min_ring_id; i < WIL6210_MAX_TX_RINGS; i++) अणु
		अगर (!wil->ring_tx[i].va)
			वापस i;
	पूर्ण
	वापस -EINVAL;
पूर्ण

पूर्णांक wil_ring_init_tx(काष्ठा wil6210_vअगर *vअगर, पूर्णांक cid)
अणु
	काष्ठा wil6210_priv *wil = vअगर_to_wil(vअगर);
	पूर्णांक rc = -EINVAL, ringid;

	अगर (cid < 0) अणु
		wil_err(wil, "No connection pending\n");
		जाओ out;
	पूर्ण
	ringid = wil_find_मुक्त_ring(wil);
	अगर (ringid < 0) अणु
		wil_err(wil, "No free vring found\n");
		जाओ out;
	पूर्ण

	wil_dbg_wmi(wil, "Configure for connection CID %d MID %d ring %d\n",
		    cid, vअगर->mid, ringid);

	rc = wil->txrx_ops.ring_init_tx(vअगर, ringid, 1 << tx_ring_order,
					cid, 0);
	अगर (rc)
		wil_err(wil, "init TX for CID %d MID %d vring %d failed\n",
			cid, vअगर->mid, ringid);

out:
	वापस rc;
पूर्ण

पूर्णांक wil_bcast_init(काष्ठा wil6210_vअगर *vअगर)
अणु
	काष्ठा wil6210_priv *wil = vअगर_to_wil(vअगर);
	पूर्णांक ri = vअगर->bcast_ring, rc;

	अगर (ri >= 0 && wil->ring_tx[ri].va)
		वापस 0;

	ri = wil_find_मुक्त_ring(wil);
	अगर (ri < 0)
		वापस ri;

	vअगर->bcast_ring = ri;
	rc = wil->txrx_ops.ring_init_bcast(vअगर, ri, 1 << bcast_ring_order);
	अगर (rc)
		vअगर->bcast_ring = -1;

	वापस rc;
पूर्ण

व्योम wil_bcast_fini(काष्ठा wil6210_vअगर *vअगर)
अणु
	काष्ठा wil6210_priv *wil = vअगर_to_wil(vअगर);
	पूर्णांक ri = vअगर->bcast_ring;

	अगर (ri < 0)
		वापस;

	vअगर->bcast_ring = -1;
	wil_ring_fini_tx(wil, ri);
पूर्ण

व्योम wil_bcast_fini_all(काष्ठा wil6210_priv *wil)
अणु
	पूर्णांक i;
	काष्ठा wil6210_vअगर *vअगर;

	क्रम (i = 0; i < GET_MAX_VIFS(wil); i++) अणु
		vअगर = wil->vअगरs[i];
		अगर (vअगर)
			wil_bcast_fini(vअगर);
	पूर्ण
पूर्ण

पूर्णांक wil_priv_init(काष्ठा wil6210_priv *wil)
अणु
	uपूर्णांक i;

	wil_dbg_misc(wil, "priv_init\n");

	स_रखो(wil->sta, 0, माप(wil->sta));
	क्रम (i = 0; i < WIL6210_MAX_CID; i++) अणु
		spin_lock_init(&wil->sta[i].tid_rx_lock);
		wil->sta[i].mid = U8_MAX;
	पूर्ण

	क्रम (i = 0; i < WIL6210_MAX_TX_RINGS; i++) अणु
		spin_lock_init(&wil->ring_tx_data[i].lock);
		wil->ring2cid_tid[i][0] = WIL6210_MAX_CID;
	पूर्ण

	mutex_init(&wil->mutex);
	mutex_init(&wil->vअगर_mutex);
	mutex_init(&wil->wmi_mutex);
	mutex_init(&wil->halp.lock);

	init_completion(&wil->wmi_पढ़ोy);
	init_completion(&wil->wmi_call);
	init_completion(&wil->halp.comp);

	INIT_WORK(&wil->wmi_event_worker, wmi_event_worker);
	INIT_WORK(&wil->fw_error_worker, wil_fw_error_worker);

	INIT_LIST_HEAD(&wil->pending_wmi_ev);
	spin_lock_init(&wil->wmi_ev_lock);
	spin_lock_init(&wil->net_queue_lock);
	spin_lock_init(&wil->eap_lock);

	init_रुकोqueue_head(&wil->wq);
	init_rwsem(&wil->mem_lock);

	wil->wmi_wq = create_singlethपढ़ो_workqueue(WIL_NAME "_wmi");
	अगर (!wil->wmi_wq)
		वापस -EAGAIN;

	wil->wq_service = create_singlethपढ़ो_workqueue(WIL_NAME "_service");
	अगर (!wil->wq_service)
		जाओ out_wmi_wq;

	wil->last_fw_recovery = jअगरfies;
	wil->tx_पूर्णांकerframe_समयout = WIL6210_ITR_TX_INTERFRAME_TIMEOUT_DEFAULT;
	wil->rx_पूर्णांकerframe_समयout = WIL6210_ITR_RX_INTERFRAME_TIMEOUT_DEFAULT;
	wil->tx_max_burst_duration = WIL6210_ITR_TX_MAX_BURST_DURATION_DEFAULT;
	wil->rx_max_burst_duration = WIL6210_ITR_RX_MAX_BURST_DURATION_DEFAULT;

	अगर (rx_ring_overflow_thrsh == WIL6210_RX_HIGH_TRSH_INIT)
		rx_ring_overflow_thrsh = WIL6210_RX_HIGH_TRSH_DEFAULT;

	wil->ps_profile =  WMI_PS_PROखाता_TYPE_DEFAULT;

	wil->wakeup_trigger = WMI_WAKEUP_TRIGGER_UCAST |
			      WMI_WAKEUP_TRIGGER_BCAST;
	स_रखो(&wil->suspend_stats, 0, माप(wil->suspend_stats));
	wil->ring_idle_trsh = 16;

	wil->reply_mid = U8_MAX;
	wil->max_vअगरs = 1;
	wil->max_assoc_sta = max_assoc_sta;

	/* edma configuration can be updated via debugfs beक्रमe allocation */
	wil->num_rx_status_rings = WIL_DEFAULT_NUM_RX_STATUS_RINGS;
	wil->tx_status_ring_order = WIL_TX_SRING_SIZE_ORDER_DEFAULT;

	/* Rx status ring size should be bigger than the number of RX buffers
	 * in order to prevent backpressure on the status ring, which may
	 * cause HW मुक्तze.
	 */
	wil->rx_status_ring_order = WIL_RX_SRING_SIZE_ORDER_DEFAULT;
	/* Number of RX buffer IDs should be bigger than the RX descriptor
	 * ring size as in HW reorder flow, the HW can consume additional
	 * buffers beक्रमe releasing the previous ones.
	 */
	wil->rx_buff_id_count = WIL_RX_BUFF_ARR_SIZE_DEFAULT;

	wil->amsdu_en = true;

	वापस 0;

out_wmi_wq:
	destroy_workqueue(wil->wmi_wq);

	वापस -EAGAIN;
पूर्ण

व्योम wil6210_bus_request(काष्ठा wil6210_priv *wil, u32 kbps)
अणु
	अगर (wil->platक्रमm_ops.bus_request) अणु
		wil->bus_request_kbps = kbps;
		wil->platक्रमm_ops.bus_request(wil->platक्रमm_handle, kbps);
	पूर्ण
पूर्ण

/**
 * wil6210_disconnect - disconnect one connection
 * @vअगर: भव पूर्णांकerface context
 * @bssid: peer to disconnect, शून्य to disconnect all
 * @reason_code: Reason code क्रम the Disassociation frame
 *
 * Disconnect and release associated resources. Issue WMI
 * command(s) to trigger MAC disconnect. When command was issued
 * successfully, call the wil6210_disconnect_complete function
 * to handle the event synchronously
 */
व्योम wil6210_disconnect(काष्ठा wil6210_vअगर *vअगर, स्थिर u8 *bssid,
			u16 reason_code)
अणु
	काष्ठा wil6210_priv *wil = vअगर_to_wil(vअगर);

	wil_dbg_misc(wil, "disconnecting\n");

	del_समयr_sync(&vअगर->connect_समयr);
	_wil6210_disconnect(vअगर, bssid, reason_code);
पूर्ण

/**
 * wil6210_disconnect_complete - handle disconnect event
 * @vअगर: भव पूर्णांकerface context
 * @bssid: peer to disconnect, शून्य to disconnect all
 * @reason_code: Reason code क्रम the Disassociation frame
 *
 * Release associated resources and indicate upper layers the
 * connection is terminated.
 */
व्योम wil6210_disconnect_complete(काष्ठा wil6210_vअगर *vअगर, स्थिर u8 *bssid,
				 u16 reason_code)
अणु
	काष्ठा wil6210_priv *wil = vअगर_to_wil(vअगर);

	wil_dbg_misc(wil, "got disconnect\n");

	del_समयr_sync(&vअगर->connect_समयr);
	_wil6210_disconnect_complete(vअगर, bssid, reason_code);
पूर्ण

व्योम wil_priv_deinit(काष्ठा wil6210_priv *wil)
अणु
	wil_dbg_misc(wil, "priv_deinit\n");

	wil_set_recovery_state(wil, fw_recovery_idle);
	cancel_work_sync(&wil->fw_error_worker);
	wmi_event_flush(wil);
	destroy_workqueue(wil->wq_service);
	destroy_workqueue(wil->wmi_wq);
	kमुक्त(wil->brd_info);
पूर्ण

अटल व्योम wil_shutकरोwn_bl(काष्ठा wil6210_priv *wil)
अणु
	u32 val;

	wil_s(wil, RGF_USER_BL +
	      दुरत्व(काष्ठा bl_dedicated_रेजिस्टरs_v1,
		       bl_shutकरोwn_handshake), BL_SHUTDOWN_HS_GRTD);

	usleep_range(100, 150);

	val = wil_r(wil, RGF_USER_BL +
		    दुरत्व(काष्ठा bl_dedicated_रेजिस्टरs_v1,
			     bl_shutकरोwn_handshake));
	अगर (val & BL_SHUTDOWN_HS_RTD) अणु
		wil_dbg_misc(wil, "BL is ready for halt\n");
		वापस;
	पूर्ण

	wil_err(wil, "BL did not report ready for halt\n");
पूर्ण

/* this क्रमmat is used by ARC embedded CPU क्रम inकाष्ठाion memory */
अटल अंतरभूत u32 ARC_me_imm32(u32 d)
अणु
	वापस ((d & 0xffff0000) >> 16) | ((d & 0x0000ffff) << 16);
पूर्ण

/* defines access to पूर्णांकerrupt vectors क्रम wil_मुक्तze_bl */
#घोषणा ARC_IRQ_VECTOR_OFFSET(N)	((N) * 8)
/* ARC दीर्घ jump inकाष्ठाion */
#घोषणा ARC_JAL_INST			(0x20200f80)

अटल व्योम wil_मुक्तze_bl(काष्ठा wil6210_priv *wil)
अणु
	u32 jal, upc, saved;
	u32 ivt3 = ARC_IRQ_VECTOR_OFFSET(3);

	jal = wil_r(wil, wil->iccm_base + ivt3);
	अगर (jal != ARC_me_imm32(ARC_JAL_INST)) अणु
		wil_dbg_misc(wil, "invalid IVT entry found, skipping\n");
		वापस;
	पूर्ण

	/* prevent the target from entering deep sleep
	 * and disabling memory access
	 */
	saved = wil_r(wil, RGF_USER_USAGE_8);
	wil_w(wil, RGF_USER_USAGE_8, saved | BIT_USER_PREVENT_DEEP_SLEEP);
	usleep_range(20, 25); /* let the BL process the bit */

	/* redirect to endless loop in the INT_L1 context and let it trap */
	wil_w(wil, wil->iccm_base + ivt3 + 4, ARC_me_imm32(ivt3));
	usleep_range(20, 25); /* let the BL get पूर्णांकo the trap */

	/* verअगरy the BL is frozen */
	upc = wil_r(wil, RGF_USER_CPU_PC);
	अगर (upc < ivt3 || (upc > (ivt3 + 8)))
		wil_dbg_misc(wil, "BL freeze failed, PC=0x%08X\n", upc);

	wil_w(wil, RGF_USER_USAGE_8, saved);
पूर्ण

अटल व्योम wil_bl_prepare_halt(काष्ठा wil6210_priv *wil)
अणु
	u32 पंचांगp, ver;

	/* beक्रमe halting device CPU driver must make sure BL is not accessing
	 * host memory. This is करोne dअगरferently depending on BL version:
	 * 1. For very old BL versions the procedure is skipped
	 * (not supported).
	 * 2. For old BL version we use a special trick to मुक्तze the BL
	 * 3. For new BL versions we shutकरोwn the BL using handshake procedure.
	 */
	पंचांगp = wil_r(wil, RGF_USER_BL +
		    दुरत्व(काष्ठा bl_dedicated_रेजिस्टरs_v0,
			     boot_loader_काष्ठा_version));
	अगर (!पंचांगp) अणु
		wil_dbg_misc(wil, "old BL, skipping halt preparation\n");
		वापस;
	पूर्ण

	पंचांगp = wil_r(wil, RGF_USER_BL +
		    दुरत्व(काष्ठा bl_dedicated_रेजिस्टरs_v1,
			     bl_shutकरोwn_handshake));
	ver = BL_SHUTDOWN_HS_PROT_VER(पंचांगp);

	अगर (ver > 0)
		wil_shutकरोwn_bl(wil);
	अन्यथा
		wil_मुक्तze_bl(wil);
पूर्ण

अटल अंतरभूत व्योम wil_halt_cpu(काष्ठा wil6210_priv *wil)
अणु
	अगर (wil->hw_version >= HW_VER_TALYN_MB) अणु
		wil_w(wil, RGF_USER_USER_CPU_0_TALYN_MB,
		      BIT_USER_USER_CPU_MAN_RST);
		wil_w(wil, RGF_USER_MAC_CPU_0_TALYN_MB,
		      BIT_USER_MAC_CPU_MAN_RST);
	पूर्ण अन्यथा अणु
		wil_w(wil, RGF_USER_USER_CPU_0, BIT_USER_USER_CPU_MAN_RST);
		wil_w(wil, RGF_USER_MAC_CPU_0,  BIT_USER_MAC_CPU_MAN_RST);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम wil_release_cpu(काष्ठा wil6210_priv *wil)
अणु
	/* Start CPU */
	अगर (wil->hw_version >= HW_VER_TALYN_MB)
		wil_w(wil, RGF_USER_USER_CPU_0_TALYN_MB, 1);
	अन्यथा
		wil_w(wil, RGF_USER_USER_CPU_0, 1);
पूर्ण

अटल व्योम wil_set_oob_mode(काष्ठा wil6210_priv *wil, u8 mode)
अणु
	wil_info(wil, "oob_mode to %d\n", mode);
	चयन (mode) अणु
	हाल 0:
		wil_c(wil, RGF_USER_USAGE_6, BIT_USER_OOB_MODE |
		      BIT_USER_OOB_R2_MODE);
		अवरोध;
	हाल 1:
		wil_c(wil, RGF_USER_USAGE_6, BIT_USER_OOB_R2_MODE);
		wil_s(wil, RGF_USER_USAGE_6, BIT_USER_OOB_MODE);
		अवरोध;
	हाल 2:
		wil_c(wil, RGF_USER_USAGE_6, BIT_USER_OOB_MODE);
		wil_s(wil, RGF_USER_USAGE_6, BIT_USER_OOB_R2_MODE);
		अवरोध;
	शेष:
		wil_err(wil, "invalid oob_mode: %d\n", mode);
	पूर्ण
पूर्ण

अटल पूर्णांक wil_रुको_device_पढ़ोy(काष्ठा wil6210_priv *wil, पूर्णांक no_flash)
अणु
	पूर्णांक delay = 0;
	u32 x, x1 = 0;

	/* रुको until device पढ़ोy. */
	अगर (no_flash) अणु
		msleep(PMU_READY_DELAY_MS);

		wil_dbg_misc(wil, "Reset completed\n");
	पूर्ण अन्यथा अणु
		करो अणु
			msleep(RST_DELAY);
			x = wil_r(wil, RGF_USER_BL +
				  दुरत्व(काष्ठा bl_dedicated_रेजिस्टरs_v0,
					   boot_loader_पढ़ोy));
			अगर (x1 != x) अणु
				wil_dbg_misc(wil, "BL.ready 0x%08x => 0x%08x\n",
					     x1, x);
				x1 = x;
			पूर्ण
			अगर (delay++ > RST_COUNT) अणु
				wil_err(wil, "Reset not completed, bl.ready 0x%08x\n",
					x);
				वापस -ETIME;
			पूर्ण
		पूर्ण जबतक (x != BL_READY);

		wil_dbg_misc(wil, "Reset completed in %d ms\n",
			     delay * RST_DELAY);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wil_रुको_device_पढ़ोy_talyn_mb(काष्ठा wil6210_priv *wil)
अणु
	u32 otp_hw;
	u8 signature_status;
	bool otp_signature_err;
	bool hw_section_करोne;
	u32 otp_qc_secured;
	पूर्णांक delay = 0;

	/* Wait क्रम OTP signature test to complete */
	usleep_range(2000, 2200);

	wil->boot_config = WIL_BOOT_ERR;

	/* Poll until OTP signature status is valid.
	 * In vanilla and development modes, when signature test is complete
	 * HW sets BIT_OTP_SIGNATURE_ERR_TALYN_MB.
	 * In production mode BIT_OTP_SIGNATURE_ERR_TALYN_MB reमुख्यs 0, poll
	 * क्रम signature status change to 2 or 3.
	 */
	करो अणु
		otp_hw = wil_r(wil, RGF_USER_OTP_HW_RD_MACHINE_1);
		signature_status = WIL_GET_BITS(otp_hw, 8, 9);
		otp_signature_err = otp_hw & BIT_OTP_SIGNATURE_ERR_TALYN_MB;

		अगर (otp_signature_err &&
		    signature_status == WIL_SIG_STATUS_VANILLA) अणु
			wil->boot_config = WIL_BOOT_VANILLA;
			अवरोध;
		पूर्ण
		अगर (otp_signature_err &&
		    signature_status == WIL_SIG_STATUS_DEVELOPMENT) अणु
			wil->boot_config = WIL_BOOT_DEVELOPMENT;
			अवरोध;
		पूर्ण
		अगर (!otp_signature_err &&
		    signature_status == WIL_SIG_STATUS_PRODUCTION) अणु
			wil->boot_config = WIL_BOOT_PRODUCTION;
			अवरोध;
		पूर्ण
		अगर  (!otp_signature_err &&
		     signature_status ==
		     WIL_SIG_STATUS_CORRUPTED_PRODUCTION) अणु
			/* Unrecognized OTP signature found. Possibly a
			 * corrupted production signature, access control
			 * is applied as in production mode, thereक्रमe
			 * करो not fail
			 */
			wil->boot_config = WIL_BOOT_PRODUCTION;
			अवरोध;
		पूर्ण
		अगर (delay++ > OTP_HW_COUNT)
			अवरोध;

		usleep_range(OTP_HW_DELAY, OTP_HW_DELAY + 10);
	पूर्ण जबतक (!otp_signature_err && signature_status == 0);

	अगर (wil->boot_config == WIL_BOOT_ERR) अणु
		wil_err(wil,
			"invalid boot config, signature_status %d otp_signature_err %d\n",
			signature_status, otp_signature_err);
		वापस -ETIME;
	पूर्ण

	wil_dbg_misc(wil,
		     "signature test done in %d usec, otp_hw 0x%x, boot_config %d\n",
		     delay * OTP_HW_DELAY, otp_hw, wil->boot_config);

	अगर (wil->boot_config == WIL_BOOT_VANILLA)
		/* Assuming not SPI boot (currently not supported) */
		जाओ out;

	hw_section_करोne = otp_hw & BIT_OTP_HW_SECTION_DONE_TALYN_MB;
	delay = 0;

	जबतक (!hw_section_करोne) अणु
		msleep(RST_DELAY);

		otp_hw = wil_r(wil, RGF_USER_OTP_HW_RD_MACHINE_1);
		hw_section_करोne = otp_hw & BIT_OTP_HW_SECTION_DONE_TALYN_MB;

		अगर (delay++ > RST_COUNT) अणु
			wil_err(wil, "TO waiting for hw_section_done\n");
			वापस -ETIME;
		पूर्ण
	पूर्ण

	wil_dbg_misc(wil, "HW section done in %d ms\n", delay * RST_DELAY);

	otp_qc_secured = wil_r(wil, RGF_OTP_QC_SECURED);
	wil->secured_boot = otp_qc_secured & BIT_BOOT_FROM_ROM ? 1 : 0;
	wil_dbg_misc(wil, "secured boot is %sabled\n",
		     wil->secured_boot ? "en" : "dis");

out:
	wil_dbg_misc(wil, "Reset completed\n");

	वापस 0;
पूर्ण

अटल पूर्णांक wil_target_reset(काष्ठा wil6210_priv *wil, पूर्णांक no_flash)
अणु
	u32 x;
	पूर्णांक rc;

	wil_dbg_misc(wil, "Resetting \"%s\"...\n", wil->hw_name);

	अगर (wil->hw_version < HW_VER_TALYN) अणु
		/* Clear MAC link up */
		wil_s(wil, RGF_HP_CTRL, BIT(15));
		wil_s(wil, RGF_USER_CLKS_CTL_SW_RST_MASK_0,
		      BIT_HPAL_PERST_FROM_PAD);
		wil_s(wil, RGF_USER_CLKS_CTL_SW_RST_MASK_0, BIT_CAR_PERST_RST);
	पूर्ण

	wil_halt_cpu(wil);

	अगर (!no_flash) अणु
		/* clear all boot loader "ready" bits */
		wil_w(wil, RGF_USER_BL +
		      दुरत्व(काष्ठा bl_dedicated_रेजिस्टरs_v0,
			       boot_loader_पढ़ोy), 0);
		/* this should be safe to ग_लिखो even with old BLs */
		wil_w(wil, RGF_USER_BL +
		      दुरत्व(काष्ठा bl_dedicated_रेजिस्टरs_v1,
			       bl_shutकरोwn_handshake), 0);
	पूर्ण
	/* Clear Fw Download notअगरication */
	wil_c(wil, RGF_USER_USAGE_6, BIT(0));

	wil_s(wil, RGF_CAF_OSC_CONTROL, BIT_CAF_OSC_XTAL_EN);
	/* XTAL stabilization should take about 3ms */
	usleep_range(5000, 7000);
	x = wil_r(wil, RGF_CAF_PLL_LOCK_STATUS);
	अगर (!(x & BIT_CAF_OSC_DIG_XTAL_STABLE)) अणु
		wil_err(wil, "Xtal stabilization timeout\n"
			"RGF_CAF_PLL_LOCK_STATUS = 0x%08x\n", x);
		वापस -ETIME;
	पूर्ण
	/* चयन 10k to XTAL*/
	wil_c(wil, RGF_USER_SPARROW_M_4, BIT_SPARROW_M_4_SEL_SLEEP_OR_REF);
	/* 40 MHz */
	wil_c(wil, RGF_USER_CLKS_CTL_0, BIT_USER_CLKS_CAR_AHB_SW_SEL);

	wil_w(wil, RGF_USER_CLKS_CTL_EXT_SW_RST_VEC_0, 0x3ff81f);
	wil_w(wil, RGF_USER_CLKS_CTL_EXT_SW_RST_VEC_1, 0xf);

	अगर (wil->hw_version >= HW_VER_TALYN_MB) अणु
		wil_w(wil, RGF_USER_CLKS_CTL_SW_RST_VEC_2, 0x7e000000);
		wil_w(wil, RGF_USER_CLKS_CTL_SW_RST_VEC_1, 0x0000003f);
		wil_w(wil, RGF_USER_CLKS_CTL_SW_RST_VEC_3, 0xc00000f0);
		wil_w(wil, RGF_USER_CLKS_CTL_SW_RST_VEC_0, 0xffe7fe00);
	पूर्ण अन्यथा अणु
		wil_w(wil, RGF_USER_CLKS_CTL_SW_RST_VEC_2, 0xfe000000);
		wil_w(wil, RGF_USER_CLKS_CTL_SW_RST_VEC_1, 0x0000003f);
		wil_w(wil, RGF_USER_CLKS_CTL_SW_RST_VEC_3, 0x000000f0);
		wil_w(wil, RGF_USER_CLKS_CTL_SW_RST_VEC_0, 0xffe7fe00);
	पूर्ण

	wil_w(wil, RGF_USER_CLKS_CTL_EXT_SW_RST_VEC_0, 0x0);
	wil_w(wil, RGF_USER_CLKS_CTL_EXT_SW_RST_VEC_1, 0x0);

	wil_w(wil, RGF_USER_CLKS_CTL_SW_RST_VEC_3, 0);
	wil_w(wil, RGF_USER_CLKS_CTL_SW_RST_VEC_2, 0);
	wil_w(wil, RGF_USER_CLKS_CTL_SW_RST_VEC_1, 0);
	wil_w(wil, RGF_USER_CLKS_CTL_SW_RST_VEC_0, 0);

	wil_w(wil, RGF_USER_CLKS_CTL_SW_RST_VEC_3, 0x00000003);
	/* reset A2 PCIE AHB */
	wil_w(wil, RGF_USER_CLKS_CTL_SW_RST_VEC_2, 0x00008000);

	wil_w(wil, RGF_USER_CLKS_CTL_SW_RST_VEC_0, 0);

	अगर (wil->hw_version == HW_VER_TALYN_MB)
		rc = wil_रुको_device_पढ़ोy_talyn_mb(wil);
	अन्यथा
		rc = wil_रुको_device_पढ़ोy(wil, no_flash);
	अगर (rc)
		वापस rc;

	wil_c(wil, RGF_USER_CLKS_CTL_0, BIT_USER_CLKS_RST_PWGD);

	/* enable fix क्रम HW bug related to the SA/DA swap in AP Rx */
	wil_s(wil, RGF_DMA_OFUL_NID_0, BIT_DMA_OFUL_NID_0_RX_EXT_TR_EN |
	      BIT_DMA_OFUL_NID_0_RX_EXT_A3_SRC);

	अगर (wil->hw_version < HW_VER_TALYN_MB && no_flash) अणु
		/* Reset OTP HW vectors to fit 40MHz */
		wil_w(wil, RGF_USER_XPM_IFC_RD_TIME1, 0x60001);
		wil_w(wil, RGF_USER_XPM_IFC_RD_TIME2, 0x20027);
		wil_w(wil, RGF_USER_XPM_IFC_RD_TIME3, 0x1);
		wil_w(wil, RGF_USER_XPM_IFC_RD_TIME4, 0x20027);
		wil_w(wil, RGF_USER_XPM_IFC_RD_TIME5, 0x30003);
		wil_w(wil, RGF_USER_XPM_IFC_RD_TIME6, 0x20002);
		wil_w(wil, RGF_USER_XPM_IFC_RD_TIME7, 0x60001);
		wil_w(wil, RGF_USER_XPM_IFC_RD_TIME8, 0x60001);
		wil_w(wil, RGF_USER_XPM_IFC_RD_TIME9, 0x60001);
		wil_w(wil, RGF_USER_XPM_IFC_RD_TIME10, 0x60001);
		wil_w(wil, RGF_USER_XPM_RD_DOUT_SAMPLE_TIME, 0x57);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम wil_collect_fw_info(काष्ठा wil6210_priv *wil)
अणु
	काष्ठा wiphy *wiphy = wil_to_wiphy(wil);
	u8 retry_लघु;
	पूर्णांक rc;

	wil_refresh_fw_capabilities(wil);

	rc = wmi_get_mgmt_retry(wil, &retry_लघु);
	अगर (!rc) अणु
		wiphy->retry_लघु = retry_लघु;
		wil_dbg_misc(wil, "FW retry_short: %d\n", retry_लघु);
	पूर्ण
पूर्ण

व्योम wil_refresh_fw_capabilities(काष्ठा wil6210_priv *wil)
अणु
	काष्ठा wiphy *wiphy = wil_to_wiphy(wil);
	पूर्णांक features;

	wil->keep_radio_on_during_sleep =
		test_bit(WIL_PLATFORM_CAPA_RADIO_ON_IN_SUSPEND,
			 wil->platक्रमm_capa) &&
		test_bit(WMI_FW_CAPABILITY_D3_SUSPEND, wil->fw_capabilities);

	wil_info(wil, "keep_radio_on_during_sleep (%d)\n",
		 wil->keep_radio_on_during_sleep);

	अगर (test_bit(WMI_FW_CAPABILITY_RSSI_REPORTING, wil->fw_capabilities))
		wiphy->संकेत_type = CFG80211_SIGNAL_TYPE_MBM;
	अन्यथा
		wiphy->संकेत_type = CFG80211_SIGNAL_TYPE_UNSPEC;

	अगर (test_bit(WMI_FW_CAPABILITY_PNO, wil->fw_capabilities)) अणु
		wiphy->max_sched_scan_reqs = 1;
		wiphy->max_sched_scan_ssids = WMI_MAX_PNO_SSID_NUM;
		wiphy->max_match_sets = WMI_MAX_PNO_SSID_NUM;
		wiphy->max_sched_scan_ie_len = WMI_MAX_IE_LEN;
		wiphy->max_sched_scan_plans = WMI_MAX_PLANS_NUM;
	पूर्ण

	अगर (test_bit(WMI_FW_CAPABILITY_TX_REQ_EXT, wil->fw_capabilities))
		wiphy->flags |= WIPHY_FLAG_OFFCHAN_TX;

	अगर (wil->platक्रमm_ops.set_features) अणु
		features = (test_bit(WMI_FW_CAPABILITY_REF_CLOCK_CONTROL,
				     wil->fw_capabilities) &&
			    test_bit(WIL_PLATFORM_CAPA_EXT_CLK,
				     wil->platक्रमm_capa)) ?
			BIT(WIL_PLATFORM_FEATURE_FW_EXT_CLK_CONTROL) : 0;

		अगर (wil->n_msi == 3)
			features |= BIT(WIL_PLATFORM_FEATURE_TRIPLE_MSI);

		wil->platक्रमm_ops.set_features(wil->platक्रमm_handle, features);
	पूर्ण

	अगर (test_bit(WMI_FW_CAPABILITY_BACK_WIN_SIZE_64,
		     wil->fw_capabilities)) अणु
		wil->max_agg_wsize = WIL_MAX_AGG_WSIZE_64;
		wil->max_ampdu_size = WIL_MAX_AMPDU_SIZE_128;
	पूर्ण अन्यथा अणु
		wil->max_agg_wsize = WIL_MAX_AGG_WSIZE;
		wil->max_ampdu_size = WIL_MAX_AMPDU_SIZE;
	पूर्ण

	update_supported_bands(wil);
पूर्ण

व्योम wil_mbox_ring_le2cpus(काष्ठा wil6210_mbox_ring *r)
अणु
	le32_to_cpus(&r->base);
	le16_to_cpus(&r->entry_size);
	le16_to_cpus(&r->size);
	le32_to_cpus(&r->tail);
	le32_to_cpus(&r->head);
पूर्ण

/* स्थिरruct actual board file name to use */
व्योम wil_get_board_file(काष्ठा wil6210_priv *wil, अक्षर *buf, माप_प्रकार len)
अणु
	स्थिर अक्षर *board_file;
	स्थिर अक्षर *wil_talyn_fw_name = fपंचांग_mode ? WIL_FW_NAME_FTM_TALYN :
			      WIL_FW_NAME_TALYN;

	अगर (wil->board_file) अणु
		board_file = wil->board_file;
	पूर्ण अन्यथा अणु
		/* If specअगरic FW file is used क्रम Talyn,
		 * use specअगरic board file
		 */
		अगर (म_भेद(wil->wil_fw_name, wil_talyn_fw_name) == 0)
			board_file = WIL_BRD_NAME_TALYN;
		अन्यथा
			board_file = WIL_BOARD_खाता_NAME;
	पूर्ण

	strlcpy(buf, board_file, len);
पूर्ण

अटल पूर्णांक wil_get_bl_info(काष्ठा wil6210_priv *wil)
अणु
	काष्ठा net_device *ndev = wil->मुख्य_ndev;
	काष्ठा wiphy *wiphy = wil_to_wiphy(wil);
	जोड़ अणु
		काष्ठा bl_dedicated_रेजिस्टरs_v0 bl0;
		काष्ठा bl_dedicated_रेजिस्टरs_v1 bl1;
	पूर्ण bl;
	u32 bl_ver;
	u8 *mac;
	u16 rf_status;

	wil_स_नकल_fromio_32(&bl, wil->csr + HOSTADDR(RGF_USER_BL),
			     माप(bl));
	bl_ver = le32_to_cpu(bl.bl0.boot_loader_काष्ठा_version);
	mac = bl.bl0.mac_address;

	अगर (bl_ver == 0) अणु
		le32_to_cpus(&bl.bl0.rf_type);
		le32_to_cpus(&bl.bl0.baseband_type);
		rf_status = 0; /* actually, unknown */
		wil_info(wil,
			 "Boot Loader struct v%d: MAC = %pM RF = 0x%08x bband = 0x%08x\n",
			 bl_ver, mac,
			 bl.bl0.rf_type, bl.bl0.baseband_type);
		wil_info(wil, "Boot Loader build unknown for struct v0\n");
	पूर्ण अन्यथा अणु
		le16_to_cpus(&bl.bl1.rf_type);
		rf_status = le16_to_cpu(bl.bl1.rf_status);
		le32_to_cpus(&bl.bl1.baseband_type);
		le16_to_cpus(&bl.bl1.bl_version_subminor);
		le16_to_cpus(&bl.bl1.bl_version_build);
		wil_info(wil,
			 "Boot Loader struct v%d: MAC = %pM RF = 0x%04x (status 0x%04x) bband = 0x%08x\n",
			 bl_ver, mac,
			 bl.bl1.rf_type, rf_status,
			 bl.bl1.baseband_type);
		wil_info(wil, "Boot Loader build %d.%d.%d.%d\n",
			 bl.bl1.bl_version_major, bl.bl1.bl_version_minor,
			 bl.bl1.bl_version_subminor, bl.bl1.bl_version_build);
	पूर्ण

	अगर (!is_valid_ether_addr(mac)) अणु
		wil_err(wil, "BL: Invalid MAC %pM\n", mac);
		वापस -EINVAL;
	पूर्ण

	ether_addr_copy(ndev->perm_addr, mac);
	ether_addr_copy(wiphy->perm_addr, mac);
	अगर (!is_valid_ether_addr(ndev->dev_addr))
		ether_addr_copy(ndev->dev_addr, mac);

	अगर (rf_status) अणु/* bad RF cable? */
		wil_err(wil, "RF communication error 0x%04x",
			rf_status);
		वापस -EAGAIN;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम wil_bl_crash_info(काष्ठा wil6210_priv *wil, bool is_err)
अणु
	u32 bl_निश्चित_code, bl_निश्चित_blink, bl_magic_number;
	u32 bl_ver = wil_r(wil, RGF_USER_BL +
			   दुरत्व(काष्ठा bl_dedicated_रेजिस्टरs_v0,
				    boot_loader_काष्ठा_version));

	अगर (bl_ver < 2)
		वापस;

	bl_निश्चित_code = wil_r(wil, RGF_USER_BL +
			       दुरत्व(काष्ठा bl_dedicated_रेजिस्टरs_v1,
					bl_निश्चित_code));
	bl_निश्चित_blink = wil_r(wil, RGF_USER_BL +
				दुरत्व(काष्ठा bl_dedicated_रेजिस्टरs_v1,
					 bl_निश्चित_blink));
	bl_magic_number = wil_r(wil, RGF_USER_BL +
				दुरत्व(काष्ठा bl_dedicated_रेजिस्टरs_v1,
					 bl_magic_number));

	अगर (is_err) अणु
		wil_err(wil,
			"BL assert code 0x%08x blink 0x%08x magic 0x%08x\n",
			bl_निश्चित_code, bl_निश्चित_blink, bl_magic_number);
	पूर्ण अन्यथा अणु
		wil_dbg_misc(wil,
			     "BL assert code 0x%08x blink 0x%08x magic 0x%08x\n",
			     bl_निश्चित_code, bl_निश्चित_blink, bl_magic_number);
	पूर्ण
पूर्ण

अटल पूर्णांक wil_get_otp_info(काष्ठा wil6210_priv *wil)
अणु
	काष्ठा net_device *ndev = wil->मुख्य_ndev;
	काष्ठा wiphy *wiphy = wil_to_wiphy(wil);
	u8 mac[8];
	पूर्णांक mac_addr;

	/* OEM MAC has precedence */
	mac_addr = RGF_OTP_OEM_MAC;
	wil_स_नकल_fromio_32(mac, wil->csr + HOSTADDR(mac_addr), माप(mac));

	अगर (is_valid_ether_addr(mac)) अणु
		wil_info(wil, "using OEM MAC %pM\n", mac);
	पूर्ण अन्यथा अणु
		अगर (wil->hw_version >= HW_VER_TALYN_MB)
			mac_addr = RGF_OTP_MAC_TALYN_MB;
		अन्यथा
			mac_addr = RGF_OTP_MAC;

		wil_स_नकल_fromio_32(mac, wil->csr + HOSTADDR(mac_addr),
				     माप(mac));
	पूर्ण

	अगर (!is_valid_ether_addr(mac)) अणु
		wil_err(wil, "Invalid MAC %pM\n", mac);
		वापस -EINVAL;
	पूर्ण

	ether_addr_copy(ndev->perm_addr, mac);
	ether_addr_copy(wiphy->perm_addr, mac);
	अगर (!is_valid_ether_addr(ndev->dev_addr))
		ether_addr_copy(ndev->dev_addr, mac);

	वापस 0;
पूर्ण

अटल पूर्णांक wil_रुको_क्रम_fw_पढ़ोy(काष्ठा wil6210_priv *wil)
अणु
	uदीर्घ to = msecs_to_jअगरfies(2000);
	uदीर्घ left = रुको_क्रम_completion_समयout(&wil->wmi_पढ़ोy, to);

	अगर (0 == left) अणु
		wil_err(wil, "Firmware not ready\n");
		वापस -ETIME;
	पूर्ण अन्यथा अणु
		wil_info(wil, "FW ready after %d ms. HW version 0x%08x\n",
			 jअगरfies_to_msecs(to-left), wil->hw_version);
	पूर्ण
	वापस 0;
पूर्ण

व्योम wil_पात_scan(काष्ठा wil6210_vअगर *vअगर, bool sync)
अणु
	काष्ठा wil6210_priv *wil = vअगर_to_wil(vअगर);
	पूर्णांक rc;
	काष्ठा cfg80211_scan_info info = अणु
		.पातed = true,
	पूर्ण;

	lockdep_निश्चित_held(&wil->vअगर_mutex);

	अगर (!vअगर->scan_request)
		वापस;

	wil_dbg_misc(wil, "Abort scan_request 0x%p\n", vअगर->scan_request);
	del_समयr_sync(&vअगर->scan_समयr);
	mutex_unlock(&wil->vअगर_mutex);
	rc = wmi_पात_scan(vअगर);
	अगर (!rc && sync)
		रुको_event_पूर्णांकerruptible_समयout(wil->wq, !vअगर->scan_request,
						 msecs_to_jअगरfies(
						 WAIT_FOR_SCAN_ABORT_MS));

	mutex_lock(&wil->vअगर_mutex);
	अगर (vअगर->scan_request) अणु
		cfg80211_scan_करोne(vअगर->scan_request, &info);
		vअगर->scan_request = शून्य;
	पूर्ण
पूर्ण

व्योम wil_पात_scan_all_vअगरs(काष्ठा wil6210_priv *wil, bool sync)
अणु
	पूर्णांक i;

	lockdep_निश्चित_held(&wil->vअगर_mutex);

	क्रम (i = 0; i < GET_MAX_VIFS(wil); i++) अणु
		काष्ठा wil6210_vअगर *vअगर = wil->vअगरs[i];

		अगर (vअगर)
			wil_पात_scan(vअगर, sync);
	पूर्ण
पूर्ण

पूर्णांक wil_ps_update(काष्ठा wil6210_priv *wil, क्रमागत wmi_ps_profile_type ps_profile)
अणु
	पूर्णांक rc;

	अगर (!test_bit(WMI_FW_CAPABILITY_PS_CONFIG, wil->fw_capabilities)) अणु
		wil_err(wil, "set_power_mgmt not supported\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	rc  = wmi_ps_dev_profile_cfg(wil, ps_profile);
	अगर (rc)
		wil_err(wil, "wmi_ps_dev_profile_cfg failed (%d)\n", rc);
	अन्यथा
		wil->ps_profile = ps_profile;

	वापस rc;
पूर्ण

अटल व्योम wil_pre_fw_config(काष्ठा wil6210_priv *wil)
अणु
	wil_clear_fw_log_addr(wil);
	/* Mark FW as loaded from host */
	wil_s(wil, RGF_USER_USAGE_6, 1);

	/* clear any पूर्णांकerrupts which on-card-firmware
	 * may have set
	 */
	wil6210_clear_irq(wil);
	/* CAF_ICR - clear and mask */
	/* it is W1C, clear by writing back same value */
	अगर (wil->hw_version < HW_VER_TALYN_MB) अणु
		wil_s(wil, RGF_CAF_ICR + दुरत्व(काष्ठा RGF_ICR, ICR), 0);
		wil_w(wil, RGF_CAF_ICR + दुरत्व(काष्ठा RGF_ICR, IMV), ~0);
	पूर्ण
	/* clear PAL_UNIT_ICR (potential D0->D3 leftover)
	 * In Talyn-MB host cannot access this रेजिस्टर due to
	 * access control, hence PAL_UNIT_ICR is cleared by the FW
	 */
	अगर (wil->hw_version < HW_VER_TALYN_MB)
		wil_s(wil, RGF_PAL_UNIT_ICR + दुरत्व(काष्ठा RGF_ICR, ICR),
		      0);

	अगर (wil->fw_calib_result > 0) अणु
		__le32 val = cpu_to_le32(wil->fw_calib_result |
						(CALIB_RESULT_SIGNATURE << 8));
		wil_w(wil, RGF_USER_FW_CALIB_RESULT, (u32 __क्रमce)val);
	पूर्ण
पूर्ण

अटल पूर्णांक wil_restore_vअगरs(काष्ठा wil6210_priv *wil)
अणु
	काष्ठा wil6210_vअगर *vअगर;
	काष्ठा net_device *ndev;
	काष्ठा wireless_dev *wdev;
	पूर्णांक i, rc;

	क्रम (i = 0; i < GET_MAX_VIFS(wil); i++) अणु
		vअगर = wil->vअगरs[i];
		अगर (!vअगर)
			जारी;
		vअगर->ap_isolate = 0;
		अगर (vअगर->mid) अणु
			ndev = vअगर_to_ndev(vअगर);
			wdev = vअगर_to_wdev(vअगर);
			rc = wmi_port_allocate(wil, vअगर->mid, ndev->dev_addr,
					       wdev->अगरtype);
			अगर (rc) अणु
				wil_err(wil, "fail to restore VIF %d type %d, rc %d\n",
					i, wdev->अगरtype, rc);
				वापस rc;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Clear FW and ucode log start addr to indicate FW log is not पढ़ोy. The host
 * driver clears the addresses beक्रमe FW starts and FW initializes the address
 * when it is पढ़ोy to send logs.
 */
व्योम wil_clear_fw_log_addr(काष्ठा wil6210_priv *wil)
अणु
	/* FW log addr */
	wil_w(wil, RGF_USER_USAGE_1, 0);
	/* ucode log addr */
	wil_w(wil, RGF_USER_USAGE_2, 0);
	wil_dbg_misc(wil, "Cleared FW and ucode log address");
पूर्ण

/*
 * We reset all the काष्ठाures, and we reset the UMAC.
 * After calling this routine, you're expected to reload
 * the firmware.
 */
पूर्णांक wil_reset(काष्ठा wil6210_priv *wil, bool load_fw)
अणु
	पूर्णांक rc, i;
	अचिन्हित दीर्घ status_flags = BIT(wil_status_resetting);
	पूर्णांक no_flash;
	काष्ठा wil6210_vअगर *vअगर;

	wil_dbg_misc(wil, "reset\n");

	WARN_ON(!mutex_is_locked(&wil->mutex));
	WARN_ON(test_bit(wil_status_napi_en, wil->status));

	अगर (debug_fw) अणु
		अटल स्थिर u8 mac[ETH_ALEN] = अणु
			0x00, 0xde, 0xad, 0x12, 0x34, 0x56,
		पूर्ण;
		काष्ठा net_device *ndev = wil->मुख्य_ndev;

		ether_addr_copy(ndev->perm_addr, mac);
		ether_addr_copy(ndev->dev_addr, ndev->perm_addr);
		वापस 0;
	पूर्ण

	अगर (wil->hw_version == HW_VER_UNKNOWN)
		वापस -ENODEV;

	अगर (test_bit(WIL_PLATFORM_CAPA_T_PWR_ON_0, wil->platक्रमm_capa) &&
	    wil->hw_version < HW_VER_TALYN_MB) अणु
		wil_dbg_misc(wil, "Notify FW to set T_POWER_ON=0\n");
		wil_s(wil, RGF_USER_USAGE_8, BIT_USER_SUPPORT_T_POWER_ON_0);
	पूर्ण

	अगर (test_bit(WIL_PLATFORM_CAPA_EXT_CLK, wil->platक्रमm_capa)) अणु
		wil_dbg_misc(wil, "Notify FW on ext clock configuration\n");
		wil_s(wil, RGF_USER_USAGE_8, BIT_USER_EXT_CLK);
	पूर्ण

	अगर (wil->platक्रमm_ops.notअगरy) अणु
		rc = wil->platक्रमm_ops.notअगरy(wil->platक्रमm_handle,
					      WIL_PLATFORM_EVT_PRE_RESET);
		अगर (rc)
			wil_err(wil, "PRE_RESET platform notify failed, rc %d\n",
				rc);
	पूर्ण

	set_bit(wil_status_resetting, wil->status);
	mutex_lock(&wil->vअगर_mutex);
	wil_पात_scan_all_vअगरs(wil, false);
	mutex_unlock(&wil->vअगर_mutex);

	क्रम (i = 0; i < GET_MAX_VIFS(wil); i++) अणु
		vअगर = wil->vअगरs[i];
		अगर (vअगर) अणु
			cancel_work_sync(&vअगर->disconnect_worker);
			wil6210_disconnect(vअगर, शून्य,
					   WLAN_REASON_DEAUTH_LEAVING);
			vअगर->ptk_rekey_state = WIL_REKEY_IDLE;
		पूर्ण
	पूर्ण
	wil_bcast_fini_all(wil);

	/* Disable device led beक्रमe reset*/
	wmi_led_cfg(wil, false);

	करोwn_ग_लिखो(&wil->mem_lock);

	/* prevent NAPI from being scheduled and prevent wmi commands */
	mutex_lock(&wil->wmi_mutex);
	अगर (test_bit(wil_status_suspending, wil->status))
		status_flags |= BIT(wil_status_suspending);
	biपंचांगap_and(wil->status, wil->status, &status_flags,
		   wil_status_last);
	wil_dbg_misc(wil, "wil->status (0x%lx)\n", *wil->status);
	mutex_unlock(&wil->wmi_mutex);

	wil_mask_irq(wil);

	wmi_event_flush(wil);

	flush_workqueue(wil->wq_service);
	flush_workqueue(wil->wmi_wq);

	no_flash = test_bit(hw_capa_no_flash, wil->hw_capa);
	अगर (!no_flash)
		wil_bl_crash_info(wil, false);
	wil_disable_irq(wil);
	rc = wil_target_reset(wil, no_flash);
	wil6210_clear_irq(wil);
	wil_enable_irq(wil);
	wil->txrx_ops.rx_fini(wil);
	wil->txrx_ops.tx_fini(wil);
	अगर (rc) अणु
		अगर (!no_flash)
			wil_bl_crash_info(wil, true);
		जाओ out;
	पूर्ण

	अगर (no_flash) अणु
		rc = wil_get_otp_info(wil);
	पूर्ण अन्यथा अणु
		rc = wil_get_bl_info(wil);
		अगर (rc == -EAGAIN && !load_fw)
			/* ignore RF error अगर not going up */
			rc = 0;
	पूर्ण
	अगर (rc)
		जाओ out;

	wil_set_oob_mode(wil, oob_mode);
	अगर (load_fw) अणु
		अक्षर board_file[WIL_BOARD_खाता_MAX_NAMELEN];

		अगर  (wil->secured_boot) अणु
			wil_err(wil, "secured boot is not supported\n");
			up_ग_लिखो(&wil->mem_lock);
			वापस -ENOTSUPP;
		पूर्ण

		board_file[0] = '\0';
		wil_get_board_file(wil, board_file, माप(board_file));
		wil_info(wil, "Use firmware <%s> + board <%s>\n",
			 wil->wil_fw_name, board_file);

		अगर (!no_flash)
			wil_bl_prepare_halt(wil);

		wil_halt_cpu(wil);
		स_रखो(wil->fw_version, 0, माप(wil->fw_version));
		/* Loading f/w from the file */
		rc = wil_request_firmware(wil, wil->wil_fw_name, true);
		अगर (rc)
			जाओ out;
		अगर (wil->num_of_brd_entries)
			rc = wil_request_board(wil, board_file);
		अन्यथा
			rc = wil_request_firmware(wil, board_file, true);
		अगर (rc)
			जाओ out;

		wil_pre_fw_config(wil);
		wil_release_cpu(wil);
	पूर्ण

	/* init after reset */
	reinit_completion(&wil->wmi_पढ़ोy);
	reinit_completion(&wil->wmi_call);
	reinit_completion(&wil->halp.comp);

	clear_bit(wil_status_resetting, wil->status);

	up_ग_लिखो(&wil->mem_lock);

	अगर (load_fw) अणु
		wil_unmask_irq(wil);

		/* we just started MAC, रुको क्रम FW पढ़ोy */
		rc = wil_रुको_क्रम_fw_पढ़ोy(wil);
		अगर (rc)
			वापस rc;

		/* check FW is responsive */
		rc = wmi_echo(wil);
		अगर (rc) अणु
			wil_err(wil, "wmi_echo failed, rc %d\n", rc);
			वापस rc;
		पूर्ण

		wil->txrx_ops.configure_पूर्णांकerrupt_moderation(wil);

		/* Enable OFU rdy valid bug fix, to prevent hang in oful34_rx
		 * जबतक there is back-pressure from Host during RX
		 */
		अगर (wil->hw_version >= HW_VER_TALYN_MB)
			wil_s(wil, RGF_DMA_MISC_CTL,
			      BIT_OFUL34_RDY_VALID_BUG_FIX_EN);

		rc = wil_restore_vअगरs(wil);
		अगर (rc) अणु
			wil_err(wil, "failed to restore vifs, rc %d\n", rc);
			वापस rc;
		पूर्ण

		wil_collect_fw_info(wil);

		अगर (wil->ps_profile != WMI_PS_PROखाता_TYPE_DEFAULT)
			wil_ps_update(wil, wil->ps_profile);

		अगर (wil->platक्रमm_ops.notअगरy) अणु
			rc = wil->platक्रमm_ops.notअगरy(wil->platक्रमm_handle,
						      WIL_PLATFORM_EVT_FW_RDY);
			अगर (rc) अणु
				wil_err(wil, "FW_RDY notify failed, rc %d\n",
					rc);
				rc = 0;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस rc;

out:
	up_ग_लिखो(&wil->mem_lock);
	clear_bit(wil_status_resetting, wil->status);
	वापस rc;
पूर्ण

व्योम wil_fw_error_recovery(काष्ठा wil6210_priv *wil)
अणु
	wil_dbg_misc(wil, "starting fw error recovery\n");

	अगर (test_bit(wil_status_resetting, wil->status)) अणु
		wil_info(wil, "Reset already in progress\n");
		वापस;
	पूर्ण

	wil->recovery_state = fw_recovery_pending;
	schedule_work(&wil->fw_error_worker);
पूर्ण

पूर्णांक __wil_up(काष्ठा wil6210_priv *wil)
अणु
	काष्ठा net_device *ndev = wil->मुख्य_ndev;
	काष्ठा wireless_dev *wdev = ndev->ieee80211_ptr;
	पूर्णांक rc;

	WARN_ON(!mutex_is_locked(&wil->mutex));

	rc = wil_reset(wil, true);
	अगर (rc)
		वापस rc;

	/* Rx RING. After MAC and beacon */
	अगर (rx_ring_order == 0)
		rx_ring_order = wil->hw_version < HW_VER_TALYN_MB ?
			WIL_RX_RING_SIZE_ORDER_DEFAULT :
			WIL_RX_RING_SIZE_ORDER_TALYN_DEFAULT;

	rc = wil->txrx_ops.rx_init(wil, rx_ring_order);
	अगर (rc)
		वापस rc;

	rc = wil->txrx_ops.tx_init(wil);
	अगर (rc)
		वापस rc;

	चयन (wdev->अगरtype) अणु
	हाल NL80211_IFTYPE_STATION:
		wil_dbg_misc(wil, "type: STATION\n");
		ndev->type = ARPHRD_ETHER;
		अवरोध;
	हाल NL80211_IFTYPE_AP:
		wil_dbg_misc(wil, "type: AP\n");
		ndev->type = ARPHRD_ETHER;
		अवरोध;
	हाल NL80211_IFTYPE_P2P_CLIENT:
		wil_dbg_misc(wil, "type: P2P_CLIENT\n");
		ndev->type = ARPHRD_ETHER;
		अवरोध;
	हाल NL80211_IFTYPE_P2P_GO:
		wil_dbg_misc(wil, "type: P2P_GO\n");
		ndev->type = ARPHRD_ETHER;
		अवरोध;
	हाल NL80211_IFTYPE_MONITOR:
		wil_dbg_misc(wil, "type: Monitor\n");
		ndev->type = ARPHRD_IEEE80211_RADIOTAP;
		/* ARPHRD_IEEE80211 or ARPHRD_IEEE80211_RADIOTAP ? */
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	/* MAC address - pre-requisite क्रम other commands */
	wmi_set_mac_address(wil, ndev->dev_addr);

	wil_dbg_misc(wil, "NAPI enable\n");
	napi_enable(&wil->napi_rx);
	napi_enable(&wil->napi_tx);
	set_bit(wil_status_napi_en, wil->status);

	wil6210_bus_request(wil, WIL_DEFAULT_BUS_REQUEST_KBPS);

	वापस 0;
पूर्ण

पूर्णांक wil_up(काष्ठा wil6210_priv *wil)
अणु
	पूर्णांक rc;

	wil_dbg_misc(wil, "up\n");

	mutex_lock(&wil->mutex);
	rc = __wil_up(wil);
	mutex_unlock(&wil->mutex);

	वापस rc;
पूर्ण

पूर्णांक __wil_करोwn(काष्ठा wil6210_priv *wil)
अणु
	पूर्णांक rc;
	WARN_ON(!mutex_is_locked(&wil->mutex));

	set_bit(wil_status_resetting, wil->status);

	wil6210_bus_request(wil, 0);

	wil_disable_irq(wil);
	अगर (test_and_clear_bit(wil_status_napi_en, wil->status)) अणु
		napi_disable(&wil->napi_rx);
		napi_disable(&wil->napi_tx);
		wil_dbg_misc(wil, "NAPI disable\n");
	पूर्ण
	wil_enable_irq(wil);

	mutex_lock(&wil->vअगर_mutex);
	wil_p2p_stop_radio_operations(wil);
	wil_पात_scan_all_vअगरs(wil, false);
	mutex_unlock(&wil->vअगर_mutex);

	rc = wil_reset(wil, false);

	वापस rc;
पूर्ण

पूर्णांक wil_करोwn(काष्ठा wil6210_priv *wil)
अणु
	पूर्णांक rc;

	wil_dbg_misc(wil, "down\n");

	wil_set_recovery_state(wil, fw_recovery_idle);
	mutex_lock(&wil->mutex);
	rc = __wil_करोwn(wil);
	mutex_unlock(&wil->mutex);

	वापस rc;
पूर्ण

पूर्णांक wil_find_cid(काष्ठा wil6210_priv *wil, u8 mid, स्थिर u8 *mac)
अणु
	पूर्णांक i;
	पूर्णांक rc = -ENOENT;

	क्रम (i = 0; i < wil->max_assoc_sta; i++) अणु
		अगर (wil->sta[i].mid == mid &&
		    wil->sta[i].status != wil_sta_unused &&
		    ether_addr_equal(wil->sta[i].addr, mac)) अणु
			rc = i;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस rc;
पूर्ण

व्योम wil_halp_vote(काष्ठा wil6210_priv *wil)
अणु
	अचिन्हित दीर्घ rc;
	अचिन्हित दीर्घ to_jअगरfies = msecs_to_jअगरfies(WAIT_FOR_HALP_VOTE_MS);

	अगर (wil->hw_version >= HW_VER_TALYN_MB)
		वापस;

	mutex_lock(&wil->halp.lock);

	wil_dbg_irq(wil, "halp_vote: start, HALP ref_cnt (%d)\n",
		    wil->halp.ref_cnt);

	अगर (++wil->halp.ref_cnt == 1) अणु
		reinit_completion(&wil->halp.comp);
		/* mark to IRQ context to handle HALP ICR */
		wil->halp.handle_icr = true;
		wil6210_set_halp(wil);
		rc = रुको_क्रम_completion_समयout(&wil->halp.comp, to_jअगरfies);
		अगर (!rc) अणु
			wil_err(wil, "HALP vote timed out\n");
			/* Mask HALP as करोne in हाल the पूर्णांकerrupt is उठाओd */
			wil->halp.handle_icr = false;
			wil6210_mask_halp(wil);
		पूर्ण अन्यथा अणु
			wil_dbg_irq(wil,
				    "halp_vote: HALP vote completed after %d ms\n",
				    jअगरfies_to_msecs(to_jअगरfies - rc));
		पूर्ण
	पूर्ण

	wil_dbg_irq(wil, "halp_vote: end, HALP ref_cnt (%d)\n",
		    wil->halp.ref_cnt);

	mutex_unlock(&wil->halp.lock);
पूर्ण

व्योम wil_halp_unvote(काष्ठा wil6210_priv *wil)
अणु
	अगर (wil->hw_version >= HW_VER_TALYN_MB)
		वापस;

	WARN_ON(wil->halp.ref_cnt == 0);

	mutex_lock(&wil->halp.lock);

	wil_dbg_irq(wil, "halp_unvote: start, HALP ref_cnt (%d)\n",
		    wil->halp.ref_cnt);

	अगर (--wil->halp.ref_cnt == 0) अणु
		wil6210_clear_halp(wil);
		wil_dbg_irq(wil, "HALP unvote\n");
	पूर्ण

	wil_dbg_irq(wil, "halp_unvote:end, HALP ref_cnt (%d)\n",
		    wil->halp.ref_cnt);

	mutex_unlock(&wil->halp.lock);
पूर्ण

व्योम wil_init_txrx_ops(काष्ठा wil6210_priv *wil)
अणु
	अगर (wil->use_enhanced_dma_hw)
		wil_init_txrx_ops_edma(wil);
	अन्यथा
		wil_init_txrx_ops_legacy_dma(wil);
पूर्ण
