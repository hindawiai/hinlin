<शैली गुरु>

/*
 * Copyright (c) 2011 Atheros Communications Inc.
 * Copyright (c) 2011-2012 Qualcomm Atheros, Inc.
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/moduleparam.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/export.h>
#समावेश <linux/of.h>
#समावेश <linux/mmc/sdio_func.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश "core.h"
#समावेश "cfg80211.h"
#समावेश "target.h"
#समावेश "debug.h"
#समावेश "hif-ops.h"
#समावेश "htc-ops.h"

अटल स्थिर काष्ठा ath6kl_hw hw_list[] = अणु
	अणु
		.id				= AR6003_HW_2_0_VERSION,
		.name				= "ar6003 hw 2.0",
		.dataset_patch_addr		= 0x57e884,
		.app_load_addr			= 0x543180,
		.board_ext_data_addr		= 0x57e500,
		.reserved_ram_size		= 6912,
		.refclk_hz			= 26000000,
		.uarttx_pin			= 8,
		.flags				= ATH6KL_HW_SDIO_CRC_ERROR_WAR,

		/* hw2.0 needs override address hardcoded */
		.app_start_override_addr	= 0x944C00,

		.fw = अणु
			.dir		= AR6003_HW_2_0_FW_सूची,
			.otp		= AR6003_HW_2_0_OTP_खाता,
			.fw		= AR6003_HW_2_0_FIRMWARE_खाता,
			.tcmd		= AR6003_HW_2_0_TCMD_FIRMWARE_खाता,
			.patch		= AR6003_HW_2_0_PATCH_खाता,
		पूर्ण,

		.fw_board		= AR6003_HW_2_0_BOARD_DATA_खाता,
		.fw_शेष_board	= AR6003_HW_2_0_DEFAULT_BOARD_DATA_खाता,
	पूर्ण,
	अणु
		.id				= AR6003_HW_2_1_1_VERSION,
		.name				= "ar6003 hw 2.1.1",
		.dataset_patch_addr		= 0x57ff74,
		.app_load_addr			= 0x1234,
		.board_ext_data_addr		= 0x542330,
		.reserved_ram_size		= 512,
		.refclk_hz			= 26000000,
		.uarttx_pin			= 8,
		.testscript_addr		= 0x57ef74,
		.flags				= ATH6KL_HW_SDIO_CRC_ERROR_WAR,

		.fw = अणु
			.dir		= AR6003_HW_2_1_1_FW_सूची,
			.otp		= AR6003_HW_2_1_1_OTP_खाता,
			.fw		= AR6003_HW_2_1_1_FIRMWARE_खाता,
			.tcmd		= AR6003_HW_2_1_1_TCMD_FIRMWARE_खाता,
			.patch		= AR6003_HW_2_1_1_PATCH_खाता,
			.utf		= AR6003_HW_2_1_1_UTF_FIRMWARE_खाता,
			.testscript	= AR6003_HW_2_1_1_TESTSCRIPT_खाता,
		पूर्ण,

		.fw_board		= AR6003_HW_2_1_1_BOARD_DATA_खाता,
		.fw_शेष_board = AR6003_HW_2_1_1_DEFAULT_BOARD_DATA_खाता,
	पूर्ण,
	अणु
		.id				= AR6004_HW_1_0_VERSION,
		.name				= "ar6004 hw 1.0",
		.dataset_patch_addr		= 0x57e884,
		.app_load_addr			= 0x1234,
		.board_ext_data_addr		= 0x437000,
		.reserved_ram_size		= 19456,
		.board_addr			= 0x433900,
		.refclk_hz			= 26000000,
		.uarttx_pin			= 11,
		.flags				= 0,

		.fw = अणु
			.dir		= AR6004_HW_1_0_FW_सूची,
			.fw		= AR6004_HW_1_0_FIRMWARE_खाता,
		पूर्ण,

		.fw_board		= AR6004_HW_1_0_BOARD_DATA_खाता,
		.fw_शेष_board	= AR6004_HW_1_0_DEFAULT_BOARD_DATA_खाता,
	पूर्ण,
	अणु
		.id				= AR6004_HW_1_1_VERSION,
		.name				= "ar6004 hw 1.1",
		.dataset_patch_addr		= 0x57e884,
		.app_load_addr			= 0x1234,
		.board_ext_data_addr		= 0x437000,
		.reserved_ram_size		= 11264,
		.board_addr			= 0x43d400,
		.refclk_hz			= 40000000,
		.uarttx_pin			= 11,
		.flags				= 0,
		.fw = अणु
			.dir		= AR6004_HW_1_1_FW_सूची,
			.fw		= AR6004_HW_1_1_FIRMWARE_खाता,
		पूर्ण,

		.fw_board		= AR6004_HW_1_1_BOARD_DATA_खाता,
		.fw_शेष_board	= AR6004_HW_1_1_DEFAULT_BOARD_DATA_खाता,
	पूर्ण,
	अणु
		.id				= AR6004_HW_1_2_VERSION,
		.name				= "ar6004 hw 1.2",
		.dataset_patch_addr		= 0x436ecc,
		.app_load_addr			= 0x1234,
		.board_ext_data_addr		= 0x437000,
		.reserved_ram_size		= 9216,
		.board_addr			= 0x435c00,
		.refclk_hz			= 40000000,
		.uarttx_pin			= 11,
		.flags				= 0,

		.fw = अणु
			.dir		= AR6004_HW_1_2_FW_सूची,
			.fw		= AR6004_HW_1_2_FIRMWARE_खाता,
		पूर्ण,
		.fw_board		= AR6004_HW_1_2_BOARD_DATA_खाता,
		.fw_शेष_board	= AR6004_HW_1_2_DEFAULT_BOARD_DATA_खाता,
	पूर्ण,
	अणु
		.id				= AR6004_HW_1_3_VERSION,
		.name				= "ar6004 hw 1.3",
		.dataset_patch_addr		= 0x437860,
		.app_load_addr			= 0x1234,
		.board_ext_data_addr		= 0x437000,
		.reserved_ram_size		= 7168,
		.board_addr			= 0x436400,
		.refclk_hz                      = 0,
		.uarttx_pin                     = 11,
		.flags				= 0,

		.fw = अणु
			.dir            = AR6004_HW_1_3_FW_सूची,
			.fw             = AR6004_HW_1_3_FIRMWARE_खाता,
			.tcmd	        = AR6004_HW_1_3_TCMD_FIRMWARE_खाता,
			.utf		= AR6004_HW_1_3_UTF_FIRMWARE_खाता,
			.testscript	= AR6004_HW_1_3_TESTSCRIPT_खाता,
		पूर्ण,

		.fw_board               = AR6004_HW_1_3_BOARD_DATA_खाता,
		.fw_शेष_board       = AR6004_HW_1_3_DEFAULT_BOARD_DATA_खाता,
	पूर्ण,
	अणु
		.id				= AR6004_HW_3_0_VERSION,
		.name				= "ar6004 hw 3.0",
		.dataset_patch_addr		= 0,
		.app_load_addr			= 0x1234,
		.board_ext_data_addr		= 0,
		.reserved_ram_size		= 7168,
		.board_addr			= 0x436400,
		.testscript_addr		= 0,
		.uarttx_pin			= 11,
		.flags				= 0,

		.fw = अणु
			.dir		= AR6004_HW_3_0_FW_सूची,
			.fw		= AR6004_HW_3_0_FIRMWARE_खाता,
			.tcmd	        = AR6004_HW_3_0_TCMD_FIRMWARE_खाता,
			.utf		= AR6004_HW_3_0_UTF_FIRMWARE_खाता,
			.testscript	= AR6004_HW_3_0_TESTSCRIPT_खाता,
		पूर्ण,

		.fw_board		= AR6004_HW_3_0_BOARD_DATA_खाता,
		.fw_शेष_board	= AR6004_HW_3_0_DEFAULT_BOARD_DATA_खाता,
	पूर्ण,
पूर्ण;

/*
 * Include definitions here that can be used to tune the WLAN module
 * behavior. Dअगरferent customers can tune the behavior as per their needs,
 * here.
 */

/*
 * This configuration item enable/disable keepalive support.
 * Keepalive support: In the असलence of any data traffic to AP, null
 * frames will be sent to the AP at periodic पूर्णांकerval, to keep the association
 * active. This configuration item defines the periodic पूर्णांकerval.
 * Use value of zero to disable keepalive support
 * Default: 60 seconds
 */
#घोषणा WLAN_CONFIG_KEEP_ALIVE_INTERVAL 60

/*
 * This configuration item sets the value of disconnect समयout
 * Firmware delays sending the disconnec event to the host क्रम this
 * समयout after is माला_लो disconnected from the current AP.
 * If the firmware successly roams within the disconnect समयout
 * it sends a new connect event
 */
#घोषणा WLAN_CONFIG_DISCONNECT_TIMEOUT 10


#घोषणा ATH6KL_DATA_OFFSET    64
काष्ठा sk_buff *ath6kl_buf_alloc(पूर्णांक size)
अणु
	काष्ठा sk_buff *skb;
	u16 reserved;

	/* Add chacheline space at front and back of buffer */
	reserved = roundup((2 * L1_CACHE_BYTES) + ATH6KL_DATA_OFFSET +
		   माप(काष्ठा htc_packet) + ATH6KL_HTC_ALIGN_BYTES, 4);
	skb = dev_alloc_skb(size + reserved);

	अगर (skb)
		skb_reserve(skb, reserved - L1_CACHE_BYTES);
	वापस skb;
पूर्ण

व्योम ath6kl_init_profile_info(काष्ठा ath6kl_vअगर *vअगर)
अणु
	vअगर->ssid_len = 0;
	स_रखो(vअगर->ssid, 0, माप(vअगर->ssid));

	vअगर->करोt11_auth_mode = OPEN_AUTH;
	vअगर->auth_mode = NONE_AUTH;
	vअगर->prwise_crypto = NONE_CRYPT;
	vअगर->prwise_crypto_len = 0;
	vअगर->grp_crypto = NONE_CRYPT;
	vअगर->grp_crypto_len = 0;
	स_रखो(vअगर->wep_key_list, 0, माप(vअगर->wep_key_list));
	स_रखो(vअगर->req_bssid, 0, माप(vअगर->req_bssid));
	स_रखो(vअगर->bssid, 0, माप(vअगर->bssid));
	vअगर->bss_ch = 0;
पूर्ण

अटल पूर्णांक ath6kl_set_host_app_area(काष्ठा ath6kl *ar)
अणु
	u32 address, data;
	काष्ठा host_app_area host_app_area;

	/* Fetch the address of the host_app_area_s
	 * instance in the host पूर्णांकerest area */
	address = ath6kl_get_hi_item_addr(ar, HI_ITEM(hi_app_host_पूर्णांकerest));
	address = TARG_VTOP(ar->target_type, address);

	अगर (ath6kl_diag_पढ़ो32(ar, address, &data))
		वापस -EIO;

	address = TARG_VTOP(ar->target_type, data);
	host_app_area.wmi_protocol_ver = cpu_to_le32(WMI_PROTOCOL_VERSION);
	अगर (ath6kl_diag_ग_लिखो(ar, address, (u8 *) &host_app_area,
			      माप(काष्ठा host_app_area)))
		वापस -EIO;

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम set_ac2_ep_map(काष्ठा ath6kl *ar,
				  u8 ac,
				  क्रमागत htc_endpoपूर्णांक_id ep)
अणु
	ar->ac2ep_map[ac] = ep;
	ar->ep2ac_map[ep] = ac;
पूर्ण

/* connect to a service */
अटल पूर्णांक ath6kl_connectservice(काष्ठा ath6kl *ar,
				 काष्ठा htc_service_connect_req  *con_req,
				 अक्षर *desc)
अणु
	पूर्णांक status;
	काष्ठा htc_service_connect_resp response;

	स_रखो(&response, 0, माप(response));

	status = ath6kl_htc_conn_service(ar->htc_target, con_req, &response);
	अगर (status) अणु
		ath6kl_err("failed to connect to %s service status:%d\n",
			   desc, status);
		वापस status;
	पूर्ण

	चयन (con_req->svc_id) अणु
	हाल WMI_CONTROL_SVC:
		अगर (test_bit(WMI_ENABLED, &ar->flag))
			ath6kl_wmi_set_control_ep(ar->wmi, response.endpoपूर्णांक);
		ar->ctrl_ep = response.endpoपूर्णांक;
		अवरोध;
	हाल WMI_DATA_BE_SVC:
		set_ac2_ep_map(ar, WMM_AC_BE, response.endpoपूर्णांक);
		अवरोध;
	हाल WMI_DATA_BK_SVC:
		set_ac2_ep_map(ar, WMM_AC_BK, response.endpoपूर्णांक);
		अवरोध;
	हाल WMI_DATA_VI_SVC:
		set_ac2_ep_map(ar, WMM_AC_VI, response.endpoपूर्णांक);
		अवरोध;
	हाल WMI_DATA_VO_SVC:
		set_ac2_ep_map(ar, WMM_AC_VO, response.endpoपूर्णांक);
		अवरोध;
	शेष:
		ath6kl_err("service id is not mapped %d\n", con_req->svc_id);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath6kl_init_service_ep(काष्ठा ath6kl *ar)
अणु
	काष्ठा htc_service_connect_req connect;

	स_रखो(&connect, 0, माप(connect));

	/* these fields are the same क्रम all service endpoपूर्णांकs */
	connect.ep_cb.tx_comp_multi = ath6kl_tx_complete;
	connect.ep_cb.rx = ath6kl_rx;
	connect.ep_cb.rx_refill = ath6kl_rx_refill;
	connect.ep_cb.tx_full = ath6kl_tx_queue_full;

	/*
	 * Set the max queue depth so that our ath6kl_tx_queue_full handler
	 * माला_लो called.
	*/
	connect.max_txq_depth = MAX_DEFAULT_SEND_QUEUE_DEPTH;
	connect.ep_cb.rx_refill_thresh = ATH6KL_MAX_RX_BUFFERS / 4;
	अगर (!connect.ep_cb.rx_refill_thresh)
		connect.ep_cb.rx_refill_thresh++;

	/* connect to control service */
	connect.svc_id = WMI_CONTROL_SVC;
	अगर (ath6kl_connectservice(ar, &connect, "WMI CONTROL"))
		वापस -EIO;

	connect.flags |= HTC_FLGS_TX_BNDL_PAD_EN;

	/*
	 * Limit the HTC message size on the send path, although e can
	 * receive A-MSDU frames of 4K, we will only send ethernet-sized
	 * (802.3) frames on the send path.
	 */
	connect.max_rxmsg_sz = WMI_MAX_TX_DATA_FRAME_LENGTH;

	/*
	 * To reduce the amount of committed memory क्रम larger A_MSDU
	 * frames, use the recv-alloc threshold mechanism क्रम larger
	 * packets.
	 */
	connect.ep_cb.rx_alloc_thresh = ATH6KL_BUFFER_SIZE;
	connect.ep_cb.rx_allocthresh = ath6kl_alloc_amsdu_rxbuf;

	/*
	 * For the reमुख्यing data services set the connection flag to
	 * reduce dribbling, अगर configured to करो so.
	 */
	connect.conn_flags |= HTC_CONN_FLGS_REDUCE_CRED_DRIB;
	connect.conn_flags &= ~HTC_CONN_FLGS_THRESH_MASK;
	connect.conn_flags |= HTC_CONN_FLGS_THRESH_LVL_HALF;

	connect.svc_id = WMI_DATA_BE_SVC;

	अगर (ath6kl_connectservice(ar, &connect, "WMI DATA BE"))
		वापस -EIO;

	/* connect to back-ground map this to WMI LOW_PRI */
	connect.svc_id = WMI_DATA_BK_SVC;
	अगर (ath6kl_connectservice(ar, &connect, "WMI DATA BK"))
		वापस -EIO;

	/* connect to Video service, map this to HI PRI */
	connect.svc_id = WMI_DATA_VI_SVC;
	अगर (ath6kl_connectservice(ar, &connect, "WMI DATA VI"))
		वापस -EIO;

	/*
	 * Connect to VO service, this is currently not mapped to a WMI
	 * priority stream due to historical reasons. WMI originally
	 * defined 3 priorities over 3 mailboxes We can change this when
	 * WMI is reworked so that priorities are not dependent on
	 * mailboxes.
	 */
	connect.svc_id = WMI_DATA_VO_SVC;
	अगर (ath6kl_connectservice(ar, &connect, "WMI DATA VO"))
		वापस -EIO;

	वापस 0;
पूर्ण

व्योम ath6kl_init_control_info(काष्ठा ath6kl_vअगर *vअगर)
अणु
	ath6kl_init_profile_info(vअगर);
	vअगर->def_txkey_index = 0;
	स_रखो(vअगर->wep_key_list, 0, माप(vअगर->wep_key_list));
	vअगर->ch_hपूर्णांक = 0;
पूर्ण

/*
 * Set HTC/Mbox operational parameters, this can only be called when the
 * target is in the BMI phase.
 */
अटल पूर्णांक ath6kl_set_htc_params(काष्ठा ath6kl *ar, u32 mbox_isr_yield_val,
				 u8 htc_ctrl_buf)
अणु
	पूर्णांक status;
	u32 blk_size;

	blk_size = ar->mbox_info.block_size;

	अगर (htc_ctrl_buf)
		blk_size |=  ((u32)htc_ctrl_buf) << 16;

	/* set the host पूर्णांकerest area क्रम the block size */
	status = ath6kl_bmi_ग_लिखो_hi32(ar, hi_mbox_io_block_sz, blk_size);
	अगर (status) अणु
		ath6kl_err("bmi_write_memory for IO block size failed\n");
		जाओ out;
	पूर्ण

	ath6kl_dbg(ATH6KL_DBG_TRC, "block size set: %d (target addr:0x%X)\n",
		   blk_size,
		   ath6kl_get_hi_item_addr(ar, HI_ITEM(hi_mbox_io_block_sz)));

	अगर (mbox_isr_yield_val) अणु
		/* set the host पूर्णांकerest area क्रम the mbox ISR yield limit */
		status = ath6kl_bmi_ग_लिखो_hi32(ar, hi_mbox_isr_yield_limit,
					       mbox_isr_yield_val);
		अगर (status) अणु
			ath6kl_err("bmi_write_memory for yield limit failed\n");
			जाओ out;
		पूर्ण
	पूर्ण

out:
	वापस status;
पूर्ण

अटल पूर्णांक ath6kl_target_config_wlan_params(काष्ठा ath6kl *ar, पूर्णांक idx)
अणु
	पूर्णांक ret;

	/*
	 * Configure the device क्रम rx करोt11 header rules. "0,0" are the
	 * शेष values. Required अगर checksum offload is needed. Set
	 * RxMetaVersion to 2.
	 */
	ret = ath6kl_wmi_set_rx_frame_क्रमmat_cmd(ar->wmi, idx,
						 ar->rx_meta_ver, 0, 0);
	अगर (ret) अणु
		ath6kl_err("unable to set the rx frame format: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (ar->conf_flags & ATH6KL_CONF_IGNORE_PS_FAIL_EVT_IN_SCAN) अणु
		ret = ath6kl_wmi_pmparams_cmd(ar->wmi, idx, 0, 1, 0, 0, 1,
					      IGNORE_PS_FAIL_DURING_SCAN);
		अगर (ret) अणु
			ath6kl_err("unable to set power save fail event policy: %d\n",
				   ret);
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (!(ar->conf_flags & ATH6KL_CONF_IGNORE_ERP_BARKER)) अणु
		ret = ath6kl_wmi_set_lpreamble_cmd(ar->wmi, idx, 0,
						   WMI_FOLLOW_BARKER_IN_ERP);
		अगर (ret) अणु
			ath6kl_err("unable to set barker preamble policy: %d\n",
				   ret);
			वापस ret;
		पूर्ण
	पूर्ण

	ret = ath6kl_wmi_set_keepalive_cmd(ar->wmi, idx,
					   WLAN_CONFIG_KEEP_ALIVE_INTERVAL);
	अगर (ret) अणु
		ath6kl_err("unable to set keep alive interval: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = ath6kl_wmi_disस_समयout_cmd(ar->wmi, idx,
					 WLAN_CONFIG_DISCONNECT_TIMEOUT);
	अगर (ret) अणु
		ath6kl_err("unable to set disconnect timeout: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (!(ar->conf_flags & ATH6KL_CONF_ENABLE_TX_BURST)) अणु
		ret = ath6kl_wmi_set_wmm_txop(ar->wmi, idx, WMI_TXOP_DISABLED);
		अगर (ret) अणु
			ath6kl_err("unable to set txop bursting: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (ar->p2p && (ar->vअगर_max == 1 || idx)) अणु
		ret = ath6kl_wmi_info_req_cmd(ar->wmi, idx,
					      P2P_FLAG_CAPABILITIES_REQ |
					      P2P_FLAG_MACADDR_REQ |
					      P2P_FLAG_HMODEL_REQ);
		अगर (ret) अणु
			ath6kl_dbg(ATH6KL_DBG_TRC,
				   "failed to request P2P capabilities (%d) - assuming P2P not supported\n",
				   ret);
			ar->p2p = false;
		पूर्ण
	पूर्ण

	अगर (ar->p2p && (ar->vअगर_max == 1 || idx)) अणु
		/* Enable Probe Request reporting क्रम P2P */
		ret = ath6kl_wmi_probe_report_req_cmd(ar->wmi, idx, true);
		अगर (ret) अणु
			ath6kl_dbg(ATH6KL_DBG_TRC,
				   "failed to enable Probe Request reporting (%d)\n",
				   ret);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक ath6kl_configure_target(काष्ठा ath6kl *ar)
अणु
	u32 param, ram_reserved_size;
	u8 fw_अगरtype, fw_mode = 0, fw_submode = 0;
	पूर्णांक i, status;

	param = !!(ar->conf_flags & ATH6KL_CONF_UART_DEBUG);
	अगर (ath6kl_bmi_ग_लिखो_hi32(ar, hi_serial_enable, param)) अणु
		ath6kl_err("bmi_write_memory for uart debug failed\n");
		वापस -EIO;
	पूर्ण

	/*
	 * Note: Even though the firmware पूर्णांकerface type is
	 * chosen as BSS_STA क्रम all three पूर्णांकerfaces, can
	 * be configured to IBSS/AP as दीर्घ as the fw submode
	 * reमुख्यs normal mode (0 - AP, STA and IBSS). But
	 * due to an target निश्चित in firmware only one पूर्णांकerface is
	 * configured क्रम now.
	 */
	fw_अगरtype = HI_OPTION_FW_MODE_BSS_STA;

	क्रम (i = 0; i < ar->vअगर_max; i++)
		fw_mode |= fw_अगरtype << (i * HI_OPTION_FW_MODE_BITS);

	/*
	 * Submodes when fw करोes not support dynamic पूर्णांकerface
	 * चयनing:
	 *		vअगर[0] - AP/STA/IBSS
	 *		vअगर[1] - "P2P dev"/"P2P GO"/"P2P Client"
	 *		vअगर[2] - "P2P dev"/"P2P GO"/"P2P Client"
	 * Otherwise, All the पूर्णांकerface are initialized to p2p dev.
	 */

	अगर (test_bit(ATH6KL_FW_CAPABILITY_STA_P2PDEV_DUPLEX,
		     ar->fw_capabilities)) अणु
		क्रम (i = 0; i < ar->vअगर_max; i++)
			fw_submode |= HI_OPTION_FW_SUBMODE_P2PDEV <<
				(i * HI_OPTION_FW_SUBMODE_BITS);
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < ar->max_norm_अगरace; i++)
			fw_submode |= HI_OPTION_FW_SUBMODE_NONE <<
				(i * HI_OPTION_FW_SUBMODE_BITS);

		क्रम (i = ar->max_norm_अगरace; i < ar->vअगर_max; i++)
			fw_submode |= HI_OPTION_FW_SUBMODE_P2PDEV <<
				(i * HI_OPTION_FW_SUBMODE_BITS);

		अगर (ar->p2p && ar->vअगर_max == 1)
			fw_submode = HI_OPTION_FW_SUBMODE_P2PDEV;
	पूर्ण

	अगर (ath6kl_bmi_ग_लिखो_hi32(ar, hi_app_host_पूर्णांकerest,
				  HTC_PROTOCOL_VERSION) != 0) अणु
		ath6kl_err("bmi_write_memory for htc version failed\n");
		वापस -EIO;
	पूर्ण

	/* set the firmware mode to STA/IBSS/AP */
	param = 0;

	अगर (ath6kl_bmi_पढ़ो_hi32(ar, hi_option_flag, &param) != 0) अणु
		ath6kl_err("bmi_read_memory for setting fwmode failed\n");
		वापस -EIO;
	पूर्ण

	param |= (ar->vअगर_max << HI_OPTION_NUM_DEV_SHIFT);
	param |= fw_mode << HI_OPTION_FW_MODE_SHIFT;
	param |= fw_submode << HI_OPTION_FW_SUBMODE_SHIFT;

	param |= (0 << HI_OPTION_MAC_ADDR_METHOD_SHIFT);
	param |= (0 << HI_OPTION_FW_BRIDGE_SHIFT);

	अगर (ath6kl_bmi_ग_लिखो_hi32(ar, hi_option_flag, param) != 0) अणु
		ath6kl_err("bmi_write_memory for setting fwmode failed\n");
		वापस -EIO;
	पूर्ण

	ath6kl_dbg(ATH6KL_DBG_TRC, "firmware mode set\n");

	/*
	 * Hardcode the address use क्रम the extended board data
	 * Ideally this should be pre-allocate by the OS at boot समय
	 * But since it is a new feature and board data is loaded
	 * at init समय, we have to workaround this from host.
	 * It is dअगरficult to patch the firmware boot code,
	 * but possible in theory.
	 */

	अगर ((ar->target_type == TARGET_TYPE_AR6003) ||
	    (ar->version.target_ver == AR6004_HW_1_3_VERSION) ||
	    (ar->version.target_ver == AR6004_HW_3_0_VERSION)) अणु
		param = ar->hw.board_ext_data_addr;
		ram_reserved_size = ar->hw.reserved_ram_size;

		अगर (ath6kl_bmi_ग_लिखो_hi32(ar, hi_board_ext_data, param) != 0) अणु
			ath6kl_err("bmi_write_memory for hi_board_ext_data failed\n");
			वापस -EIO;
		पूर्ण

		अगर (ath6kl_bmi_ग_लिखो_hi32(ar, hi_end_ram_reserve_sz,
					  ram_reserved_size) != 0) अणु
			ath6kl_err("bmi_write_memory for hi_end_ram_reserve_sz failed\n");
			वापस -EIO;
		पूर्ण
	पूर्ण

	/* set the block size क्रम the target */
	अगर (ath6kl_set_htc_params(ar, MBOX_YIELD_LIMIT, 0))
		/* use शेष number of control buffers */
		वापस -EIO;

	/* Configure GPIO AR600x UART */
	status = ath6kl_bmi_ग_लिखो_hi32(ar, hi_dbg_uart_txpin,
				       ar->hw.uarttx_pin);
	अगर (status)
		वापस status;

	/* Only set the baud rate अगर we're actually करोing debug */
	अगर (ar->conf_flags & ATH6KL_CONF_UART_DEBUG) अणु
		status = ath6kl_bmi_ग_लिखो_hi32(ar, hi_desired_baud_rate,
					       ar->hw.uarttx_rate);
		अगर (status)
			वापस status;
	पूर्ण

	/* Configure target refclk_hz */
	अगर (ar->hw.refclk_hz != 0) अणु
		status = ath6kl_bmi_ग_लिखो_hi32(ar, hi_refclk_hz,
					       ar->hw.refclk_hz);
		अगर (status)
			वापस status;
	पूर्ण

	वापस 0;
पूर्ण

/* firmware upload */
अटल पूर्णांक ath6kl_get_fw(काष्ठा ath6kl *ar, स्थिर अक्षर *filename,
			 u8 **fw, माप_प्रकार *fw_len)
अणु
	स्थिर काष्ठा firmware *fw_entry;
	पूर्णांक ret;

	ret = request_firmware(&fw_entry, filename, ar->dev);
	अगर (ret)
		वापस ret;

	*fw_len = fw_entry->size;
	*fw = kmemdup(fw_entry->data, fw_entry->size, GFP_KERNEL);

	अगर (*fw == शून्य)
		ret = -ENOMEM;

	release_firmware(fw_entry);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_OF
/*
 * Check the device tree क्रम a board-id and use it to स्थिरruct
 * the pathname to the firmware file.  Used (क्रम now) to find a
 * fallback to the "bdata.bin" file--typically a symlink to the
 * appropriate board-specअगरic file.
 */
अटल bool check_device_tree(काष्ठा ath6kl *ar)
अणु
	अटल स्थिर अक्षर *board_id_prop = "atheros,board-id";
	काष्ठा device_node *node;
	अक्षर board_filename[64];
	स्थिर अक्षर *board_id;
	पूर्णांक ret;

	क्रम_each_compatible_node(node, शून्य, "atheros,ath6kl") अणु
		board_id = of_get_property(node, board_id_prop, शून्य);
		अगर (board_id == शून्य) अणु
			ath6kl_warn("No \"%s\" property on %pOFn node.\n",
				    board_id_prop, node);
			जारी;
		पूर्ण
		snम_लिखो(board_filename, माप(board_filename),
			 "%s/bdata.%s.bin", ar->hw.fw.dir, board_id);

		ret = ath6kl_get_fw(ar, board_filename, &ar->fw_board,
				    &ar->fw_board_len);
		अगर (ret) अणु
			ath6kl_err("Failed to get DT board file %s: %d\n",
				   board_filename, ret);
			जारी;
		पूर्ण
		of_node_put(node);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण
#अन्यथा
अटल bool check_device_tree(काष्ठा ath6kl *ar)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर /* CONFIG_OF */

अटल पूर्णांक ath6kl_fetch_board_file(काष्ठा ath6kl *ar)
अणु
	स्थिर अक्षर *filename;
	पूर्णांक ret;

	अगर (ar->fw_board != शून्य)
		वापस 0;

	अगर (WARN_ON(ar->hw.fw_board == शून्य))
		वापस -EINVAL;

	filename = ar->hw.fw_board;

	ret = ath6kl_get_fw(ar, filename, &ar->fw_board,
			    &ar->fw_board_len);
	अगर (ret == 0) अणु
		/* managed to get proper board file */
		वापस 0;
	पूर्ण

	अगर (check_device_tree(ar)) अणु
		/* got board file from device tree */
		वापस 0;
	पूर्ण

	/* there was no proper board file, try to use शेष instead */
	ath6kl_warn("Failed to get board file %s (%d), trying to find default board file.\n",
		    filename, ret);

	filename = ar->hw.fw_शेष_board;

	ret = ath6kl_get_fw(ar, filename, &ar->fw_board,
			    &ar->fw_board_len);
	अगर (ret) अणु
		ath6kl_err("Failed to get default board file %s: %d\n",
			   filename, ret);
		वापस ret;
	पूर्ण

	ath6kl_warn("WARNING! No proper board file was not found, instead using a default board file.\n");
	ath6kl_warn("Most likely your hardware won't work as specified. Install correct board file!\n");

	वापस 0;
पूर्ण

अटल पूर्णांक ath6kl_fetch_otp_file(काष्ठा ath6kl *ar)
अणु
	अक्षर filename[100];
	पूर्णांक ret;

	अगर (ar->fw_otp != शून्य)
		वापस 0;

	अगर (ar->hw.fw.otp == शून्य) अणु
		ath6kl_dbg(ATH6KL_DBG_BOOT,
			   "no OTP file configured for this hw\n");
		वापस 0;
	पूर्ण

	snम_लिखो(filename, माप(filename), "%s/%s",
		 ar->hw.fw.dir, ar->hw.fw.otp);

	ret = ath6kl_get_fw(ar, filename, &ar->fw_otp,
			    &ar->fw_otp_len);
	अगर (ret) अणु
		ath6kl_err("Failed to get OTP file %s: %d\n",
			   filename, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath6kl_fetch_tesपंचांगode_file(काष्ठा ath6kl *ar)
अणु
	अक्षर filename[100];
	पूर्णांक ret;

	अगर (ar->tesपंचांगode == 0)
		वापस 0;

	ath6kl_dbg(ATH6KL_DBG_BOOT, "testmode %d\n", ar->tesपंचांगode);

	अगर (ar->tesपंचांगode == 2) अणु
		अगर (ar->hw.fw.utf == शून्य) अणु
			ath6kl_warn("testmode 2 not supported\n");
			वापस -EOPNOTSUPP;
		पूर्ण

		snम_लिखो(filename, माप(filename), "%s/%s",
			 ar->hw.fw.dir, ar->hw.fw.utf);
	पूर्ण अन्यथा अणु
		अगर (ar->hw.fw.tcmd == शून्य) अणु
			ath6kl_warn("testmode 1 not supported\n");
			वापस -EOPNOTSUPP;
		पूर्ण

		snम_लिखो(filename, माप(filename), "%s/%s",
			 ar->hw.fw.dir, ar->hw.fw.tcmd);
	पूर्ण

	set_bit(TESTMODE, &ar->flag);

	ret = ath6kl_get_fw(ar, filename, &ar->fw, &ar->fw_len);
	अगर (ret) अणु
		ath6kl_err("Failed to get testmode %d firmware file %s: %d\n",
			   ar->tesपंचांगode, filename, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath6kl_fetch_fw_file(काष्ठा ath6kl *ar)
अणु
	अक्षर filename[100];
	पूर्णांक ret;

	अगर (ar->fw != शून्य)
		वापस 0;

	/* FIXME: हटाओ WARN_ON() as we won't support FW API 1 क्रम दीर्घ */
	अगर (WARN_ON(ar->hw.fw.fw == शून्य))
		वापस -EINVAL;

	snम_लिखो(filename, माप(filename), "%s/%s",
		 ar->hw.fw.dir, ar->hw.fw.fw);

	ret = ath6kl_get_fw(ar, filename, &ar->fw, &ar->fw_len);
	अगर (ret) अणु
		ath6kl_err("Failed to get firmware file %s: %d\n",
			   filename, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath6kl_fetch_patch_file(काष्ठा ath6kl *ar)
अणु
	अक्षर filename[100];
	पूर्णांक ret;

	अगर (ar->fw_patch != शून्य)
		वापस 0;

	अगर (ar->hw.fw.patch == शून्य)
		वापस 0;

	snम_लिखो(filename, माप(filename), "%s/%s",
		 ar->hw.fw.dir, ar->hw.fw.patch);

	ret = ath6kl_get_fw(ar, filename, &ar->fw_patch,
			    &ar->fw_patch_len);
	अगर (ret) अणु
		ath6kl_err("Failed to get patch file %s: %d\n",
			   filename, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath6kl_fetch_testscript_file(काष्ठा ath6kl *ar)
अणु
	अक्षर filename[100];
	पूर्णांक ret;

	अगर (ar->tesपंचांगode != 2)
		वापस 0;

	अगर (ar->fw_testscript != शून्य)
		वापस 0;

	अगर (ar->hw.fw.testscript == शून्य)
		वापस 0;

	snम_लिखो(filename, माप(filename), "%s/%s",
		 ar->hw.fw.dir, ar->hw.fw.testscript);

	ret = ath6kl_get_fw(ar, filename, &ar->fw_testscript,
				&ar->fw_testscript_len);
	अगर (ret) अणु
		ath6kl_err("Failed to get testscript file %s: %d\n",
			   filename, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath6kl_fetch_fw_api1(काष्ठा ath6kl *ar)
अणु
	पूर्णांक ret;

	ret = ath6kl_fetch_otp_file(ar);
	अगर (ret)
		वापस ret;

	ret = ath6kl_fetch_fw_file(ar);
	अगर (ret)
		वापस ret;

	ret = ath6kl_fetch_patch_file(ar);
	अगर (ret)
		वापस ret;

	ret = ath6kl_fetch_testscript_file(ar);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक ath6kl_fetch_fw_apin(काष्ठा ath6kl *ar, स्थिर अक्षर *name)
अणु
	माप_प्रकार magic_len, len, ie_len;
	स्थिर काष्ठा firmware *fw;
	काष्ठा ath6kl_fw_ie *hdr;
	अक्षर filename[100];
	स्थिर u8 *data;
	पूर्णांक ret, ie_id, i, index, bit;
	__le32 *val;

	snम_लिखो(filename, माप(filename), "%s/%s", ar->hw.fw.dir, name);

	ret = request_firmware(&fw, filename, ar->dev);
	अगर (ret) अणु
		ath6kl_err("Failed request firmware, rv: %d\n", ret);
		वापस ret;
	पूर्ण

	data = fw->data;
	len = fw->size;

	/* magic also includes the null byte, check that as well */
	magic_len = म_माप(ATH6KL_FIRMWARE_MAGIC) + 1;

	अगर (len < magic_len) अणु
		ath6kl_err("Magic length is invalid, len: %zd  magic_len: %zd\n",
			   len, magic_len);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (स_भेद(data, ATH6KL_FIRMWARE_MAGIC, magic_len) != 0) अणु
		ath6kl_err("Magic is invalid, magic_len: %zd\n",
			   magic_len);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	len -= magic_len;
	data += magic_len;

	/* loop elements */
	जबतक (len > माप(काष्ठा ath6kl_fw_ie)) अणु
		/* hdr is unaligned! */
		hdr = (काष्ठा ath6kl_fw_ie *) data;

		ie_id = le32_to_cpup(&hdr->id);
		ie_len = le32_to_cpup(&hdr->len);

		len -= माप(*hdr);
		data += माप(*hdr);

		ath6kl_dbg(ATH6KL_DBG_BOOT, "ie-id: %d  len: %zd (0x%zx)\n",
			   ie_id, ie_len, ie_len);

		अगर (len < ie_len) अणु
			ath6kl_err("IE len is invalid, len: %zd  ie_len: %zd  ie-id: %d\n",
				   len, ie_len, ie_id);
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		चयन (ie_id) अणु
		हाल ATH6KL_FW_IE_FW_VERSION:
			strlcpy(ar->wiphy->fw_version, data,
				min(माप(ar->wiphy->fw_version), ie_len+1));

			ath6kl_dbg(ATH6KL_DBG_BOOT,
				   "found fw version %s\n",
				    ar->wiphy->fw_version);
			अवरोध;
		हाल ATH6KL_FW_IE_OTP_IMAGE:
			ath6kl_dbg(ATH6KL_DBG_BOOT, "found otp image ie (%zd B)\n",
				   ie_len);

			ar->fw_otp = kmemdup(data, ie_len, GFP_KERNEL);

			अगर (ar->fw_otp == शून्य) अणु
				ath6kl_err("fw_otp cannot be allocated\n");
				ret = -ENOMEM;
				जाओ out;
			पूर्ण

			ar->fw_otp_len = ie_len;
			अवरोध;
		हाल ATH6KL_FW_IE_FW_IMAGE:
			ath6kl_dbg(ATH6KL_DBG_BOOT, "found fw image ie (%zd B)\n",
				   ie_len);

			/* in tesपंचांगode we alपढ़ोy might have a fw file */
			अगर (ar->fw != शून्य)
				अवरोध;

			ar->fw = vदो_स्मृति(ie_len);

			अगर (ar->fw == शून्य) अणु
				ath6kl_err("fw storage cannot be allocated, len: %zd\n", ie_len);
				ret = -ENOMEM;
				जाओ out;
			पूर्ण

			स_नकल(ar->fw, data, ie_len);
			ar->fw_len = ie_len;
			अवरोध;
		हाल ATH6KL_FW_IE_PATCH_IMAGE:
			ath6kl_dbg(ATH6KL_DBG_BOOT, "found patch image ie (%zd B)\n",
				   ie_len);

			ar->fw_patch = kmemdup(data, ie_len, GFP_KERNEL);

			अगर (ar->fw_patch == शून्य) अणु
				ath6kl_err("fw_patch storage cannot be allocated, len: %zd\n", ie_len);
				ret = -ENOMEM;
				जाओ out;
			पूर्ण

			ar->fw_patch_len = ie_len;
			अवरोध;
		हाल ATH6KL_FW_IE_RESERVED_RAM_SIZE:
			val = (__le32 *) data;
			ar->hw.reserved_ram_size = le32_to_cpup(val);

			ath6kl_dbg(ATH6KL_DBG_BOOT,
				   "found reserved ram size ie %d\n",
				   ar->hw.reserved_ram_size);
			अवरोध;
		हाल ATH6KL_FW_IE_CAPABILITIES:
			ath6kl_dbg(ATH6KL_DBG_BOOT,
				   "found firmware capabilities ie (%zd B)\n",
				   ie_len);

			क्रम (i = 0; i < ATH6KL_FW_CAPABILITY_MAX; i++) अणु
				index = i / 8;
				bit = i % 8;

				अगर (index == ie_len)
					अवरोध;

				अगर (data[index] & (1 << bit))
					__set_bit(i, ar->fw_capabilities);
			पूर्ण

			ath6kl_dbg_dump(ATH6KL_DBG_BOOT, "capabilities", "",
					ar->fw_capabilities,
					माप(ar->fw_capabilities));
			अवरोध;
		हाल ATH6KL_FW_IE_PATCH_ADDR:
			अगर (ie_len != माप(*val))
				अवरोध;

			val = (__le32 *) data;
			ar->hw.dataset_patch_addr = le32_to_cpup(val);

			ath6kl_dbg(ATH6KL_DBG_BOOT,
				   "found patch address ie 0x%x\n",
				   ar->hw.dataset_patch_addr);
			अवरोध;
		हाल ATH6KL_FW_IE_BOARD_ADDR:
			अगर (ie_len != माप(*val))
				अवरोध;

			val = (__le32 *) data;
			ar->hw.board_addr = le32_to_cpup(val);

			ath6kl_dbg(ATH6KL_DBG_BOOT,
				   "found board address ie 0x%x\n",
				   ar->hw.board_addr);
			अवरोध;
		हाल ATH6KL_FW_IE_VIF_MAX:
			अगर (ie_len != माप(*val))
				अवरोध;

			val = (__le32 *) data;
			ar->vअगर_max = min_t(अचिन्हित पूर्णांक, le32_to_cpup(val),
					    ATH6KL_VIF_MAX);

			अगर (ar->vअगर_max > 1 && !ar->p2p)
				ar->max_norm_अगरace = 2;

			ath6kl_dbg(ATH6KL_DBG_BOOT,
				   "found vif max ie %d\n", ar->vअगर_max);
			अवरोध;
		शेष:
			ath6kl_dbg(ATH6KL_DBG_BOOT, "Unknown fw ie: %u\n",
				   le32_to_cpup(&hdr->id));
			अवरोध;
		पूर्ण

		len -= ie_len;
		data += ie_len;
	पूर्ण

	ret = 0;
out:
	release_firmware(fw);

	वापस ret;
पूर्ण

पूर्णांक ath6kl_init_fetch_firmwares(काष्ठा ath6kl *ar)
अणु
	पूर्णांक ret;

	ret = ath6kl_fetch_board_file(ar);
	अगर (ret)
		वापस ret;

	ret = ath6kl_fetch_tesपंचांगode_file(ar);
	अगर (ret)
		वापस ret;

	ret = ath6kl_fetch_fw_apin(ar, ATH6KL_FW_API5_खाता);
	अगर (ret == 0) अणु
		ar->fw_api = 5;
		जाओ out;
	पूर्ण

	ret = ath6kl_fetch_fw_apin(ar, ATH6KL_FW_API4_खाता);
	अगर (ret == 0) अणु
		ar->fw_api = 4;
		जाओ out;
	पूर्ण

	ret = ath6kl_fetch_fw_apin(ar, ATH6KL_FW_API3_खाता);
	अगर (ret == 0) अणु
		ar->fw_api = 3;
		जाओ out;
	पूर्ण

	ret = ath6kl_fetch_fw_apin(ar, ATH6KL_FW_API2_खाता);
	अगर (ret == 0) अणु
		ar->fw_api = 2;
		जाओ out;
	पूर्ण

	ret = ath6kl_fetch_fw_api1(ar);
	अगर (ret)
		वापस ret;

	ar->fw_api = 1;

out:
	ath6kl_dbg(ATH6KL_DBG_BOOT, "using fw api %d\n", ar->fw_api);

	वापस 0;
पूर्ण

अटल पूर्णांक ath6kl_upload_board_file(काष्ठा ath6kl *ar)
अणु
	u32 board_address, board_ext_address, param;
	u32 board_data_size, board_ext_data_size;
	पूर्णांक ret;

	अगर (WARN_ON(ar->fw_board == शून्य))
		वापस -ENOENT;

	/*
	 * Determine where in Target RAM to ग_लिखो Board Data.
	 * For AR6004, host determine Target RAM address क्रम
	 * writing board data.
	 */
	अगर (ar->hw.board_addr != 0) अणु
		board_address = ar->hw.board_addr;
		ath6kl_bmi_ग_लिखो_hi32(ar, hi_board_data,
				      board_address);
	पूर्ण अन्यथा अणु
		ret = ath6kl_bmi_पढ़ो_hi32(ar, hi_board_data, &board_address);
		अगर (ret) अणु
			ath6kl_err("Failed to get board file target address.\n");
			वापस ret;
		पूर्ण
	पूर्ण

	/* determine where in target ram to ग_लिखो extended board data */
	ret = ath6kl_bmi_पढ़ो_hi32(ar, hi_board_ext_data, &board_ext_address);
	अगर (ret) अणु
		ath6kl_err("Failed to get extended board file target address.\n");
		वापस ret;
	पूर्ण

	अगर (ar->target_type == TARGET_TYPE_AR6003 &&
	    board_ext_address == 0) अणु
		ath6kl_err("Failed to get board file target address.\n");
		वापस -EINVAL;
	पूर्ण

	चयन (ar->target_type) अणु
	हाल TARGET_TYPE_AR6003:
		board_data_size = AR6003_BOARD_DATA_SZ;
		board_ext_data_size = AR6003_BOARD_EXT_DATA_SZ;
		अगर (ar->fw_board_len > (board_data_size + board_ext_data_size))
			board_ext_data_size = AR6003_BOARD_EXT_DATA_SZ_V2;
		अवरोध;
	हाल TARGET_TYPE_AR6004:
		board_data_size = AR6004_BOARD_DATA_SZ;
		board_ext_data_size = AR6004_BOARD_EXT_DATA_SZ;
		अवरोध;
	शेष:
		WARN_ON(1);
		वापस -EINVAL;
	पूर्ण

	अगर (board_ext_address &&
	    ar->fw_board_len == (board_data_size + board_ext_data_size)) अणु
		/* ग_लिखो extended board data */
		ath6kl_dbg(ATH6KL_DBG_BOOT,
			   "writing extended board data to 0x%x (%d B)\n",
			   board_ext_address, board_ext_data_size);

		ret = ath6kl_bmi_ग_लिखो(ar, board_ext_address,
				       ar->fw_board + board_data_size,
				       board_ext_data_size);
		अगर (ret) अणु
			ath6kl_err("Failed to write extended board data: %d\n",
				   ret);
			वापस ret;
		पूर्ण

		/* record that extended board data is initialized */
		param = (board_ext_data_size << 16) | 1;

		ath6kl_bmi_ग_लिखो_hi32(ar, hi_board_ext_data_config, param);
	पूर्ण

	अगर (ar->fw_board_len < board_data_size) अणु
		ath6kl_err("Too small board file: %zu\n", ar->fw_board_len);
		ret = -EINVAL;
		वापस ret;
	पूर्ण

	ath6kl_dbg(ATH6KL_DBG_BOOT, "writing board file to 0x%x (%d B)\n",
		   board_address, board_data_size);

	ret = ath6kl_bmi_ग_लिखो(ar, board_address, ar->fw_board,
			       board_data_size);

	अगर (ret) अणु
		ath6kl_err("Board file bmi write failed: %d\n", ret);
		वापस ret;
	पूर्ण

	/* record the fact that Board Data IS initialized */
	अगर ((ar->version.target_ver == AR6004_HW_1_3_VERSION) ||
	    (ar->version.target_ver == AR6004_HW_3_0_VERSION))
		param = board_data_size;
	अन्यथा
		param = 1;

	ath6kl_bmi_ग_लिखो_hi32(ar, hi_board_data_initialized, param);

	वापस ret;
पूर्ण

अटल पूर्णांक ath6kl_upload_otp(काष्ठा ath6kl *ar)
अणु
	u32 address, param;
	bool from_hw = false;
	पूर्णांक ret;

	अगर (ar->fw_otp == शून्य)
		वापस 0;

	address = ar->hw.app_load_addr;

	ath6kl_dbg(ATH6KL_DBG_BOOT, "writing otp to 0x%x (%zd B)\n", address,
		   ar->fw_otp_len);

	ret = ath6kl_bmi_fast_करोwnload(ar, address, ar->fw_otp,
				       ar->fw_otp_len);
	अगर (ret) अणु
		ath6kl_err("Failed to upload OTP file: %d\n", ret);
		वापस ret;
	पूर्ण

	/* पढ़ो firmware start address */
	ret = ath6kl_bmi_पढ़ो_hi32(ar, hi_app_start, &address);

	अगर (ret) अणु
		ath6kl_err("Failed to read hi_app_start: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (ar->hw.app_start_override_addr == 0) अणु
		ar->hw.app_start_override_addr = address;
		from_hw = true;
	पूर्ण

	ath6kl_dbg(ATH6KL_DBG_BOOT, "app_start_override_addr%s 0x%x\n",
		   from_hw ? " (from hw)" : "",
		   ar->hw.app_start_override_addr);

	/* execute the OTP code */
	ath6kl_dbg(ATH6KL_DBG_BOOT, "executing OTP at 0x%x\n",
		   ar->hw.app_start_override_addr);
	param = 0;
	ath6kl_bmi_execute(ar, ar->hw.app_start_override_addr, &param);

	वापस ret;
पूर्ण

अटल पूर्णांक ath6kl_upload_firmware(काष्ठा ath6kl *ar)
अणु
	u32 address;
	पूर्णांक ret;

	अगर (WARN_ON(ar->fw == शून्य))
		वापस 0;

	address = ar->hw.app_load_addr;

	ath6kl_dbg(ATH6KL_DBG_BOOT, "writing firmware to 0x%x (%zd B)\n",
		   address, ar->fw_len);

	ret = ath6kl_bmi_fast_करोwnload(ar, address, ar->fw, ar->fw_len);

	अगर (ret) अणु
		ath6kl_err("Failed to write firmware: %d\n", ret);
		वापस ret;
	पूर्ण

	/*
	 * Set starting address क्रम firmware
	 * Don't need to setup app_start override addr on AR6004
	 */
	अगर (ar->target_type != TARGET_TYPE_AR6004) अणु
		address = ar->hw.app_start_override_addr;
		ath6kl_bmi_set_app_start(ar, address);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक ath6kl_upload_patch(काष्ठा ath6kl *ar)
अणु
	u32 address;
	पूर्णांक ret;

	अगर (ar->fw_patch == शून्य)
		वापस 0;

	address = ar->hw.dataset_patch_addr;

	ath6kl_dbg(ATH6KL_DBG_BOOT, "writing patch to 0x%x (%zd B)\n",
		   address, ar->fw_patch_len);

	ret = ath6kl_bmi_ग_लिखो(ar, address, ar->fw_patch, ar->fw_patch_len);
	अगर (ret) अणु
		ath6kl_err("Failed to write patch file: %d\n", ret);
		वापस ret;
	पूर्ण

	ath6kl_bmi_ग_लिखो_hi32(ar, hi_dset_list_head, address);

	वापस 0;
पूर्ण

अटल पूर्णांक ath6kl_upload_testscript(काष्ठा ath6kl *ar)
अणु
	u32 address;
	पूर्णांक ret;

	अगर (ar->tesपंचांगode != 2)
		वापस 0;

	अगर (ar->fw_testscript == शून्य)
		वापस 0;

	address = ar->hw.testscript_addr;

	ath6kl_dbg(ATH6KL_DBG_BOOT, "writing testscript to 0x%x (%zd B)\n",
		   address, ar->fw_testscript_len);

	ret = ath6kl_bmi_ग_लिखो(ar, address, ar->fw_testscript,
		ar->fw_testscript_len);
	अगर (ret) अणु
		ath6kl_err("Failed to write testscript file: %d\n", ret);
		वापस ret;
	पूर्ण

	ath6kl_bmi_ग_लिखो_hi32(ar, hi_ota_testscript, address);

	अगर ((ar->version.target_ver != AR6004_HW_1_3_VERSION) &&
	    (ar->version.target_ver != AR6004_HW_3_0_VERSION))
		ath6kl_bmi_ग_लिखो_hi32(ar, hi_end_ram_reserve_sz, 4096);

	ath6kl_bmi_ग_लिखो_hi32(ar, hi_test_apps_related, 1);

	वापस 0;
पूर्ण

अटल पूर्णांक ath6kl_init_upload(काष्ठा ath6kl *ar)
अणु
	u32 param, options, sleep, address;
	पूर्णांक status = 0;

	अगर (ar->target_type != TARGET_TYPE_AR6003 &&
	    ar->target_type != TARGET_TYPE_AR6004)
		वापस -EINVAL;

	/* temporarily disable प्रणाली sleep */
	address = MBOX_BASE_ADDRESS + LOCAL_SCRATCH_ADDRESS;
	status = ath6kl_bmi_reg_पढ़ो(ar, address, &param);
	अगर (status)
		वापस status;

	options = param;

	param |= ATH6KL_OPTION_SLEEP_DISABLE;
	status = ath6kl_bmi_reg_ग_लिखो(ar, address, param);
	अगर (status)
		वापस status;

	address = RTC_BASE_ADDRESS + SYSTEM_SLEEP_ADDRESS;
	status = ath6kl_bmi_reg_पढ़ो(ar, address, &param);
	अगर (status)
		वापस status;

	sleep = param;

	param |= SM(SYSTEM_SLEEP_DISABLE, 1);
	status = ath6kl_bmi_reg_ग_लिखो(ar, address, param);
	अगर (status)
		वापस status;

	ath6kl_dbg(ATH6KL_DBG_TRC, "old options: %d, old sleep: %d\n",
		   options, sleep);

	/* program analog PLL रेजिस्टर */
	/* no need to control 40/44MHz घड़ी on AR6004 */
	अगर (ar->target_type != TARGET_TYPE_AR6004) अणु
		status = ath6kl_bmi_reg_ग_लिखो(ar, ATH6KL_ANALOG_PLL_REGISTER,
					      0xF9104001);

		अगर (status)
			वापस status;

		/* Run at 80/88MHz by शेष */
		param = SM(CPU_CLOCK_STANDARD, 1);

		address = RTC_BASE_ADDRESS + CPU_CLOCK_ADDRESS;
		status = ath6kl_bmi_reg_ग_लिखो(ar, address, param);
		अगर (status)
			वापस status;
	पूर्ण

	param = 0;
	address = RTC_BASE_ADDRESS + LPO_CAL_ADDRESS;
	param = SM(LPO_CAL_ENABLE, 1);
	status = ath6kl_bmi_reg_ग_लिखो(ar, address, param);
	अगर (status)
		वापस status;

	/* WAR to aव्योम SDIO CRC err */
	अगर (ar->hw.flags & ATH6KL_HW_SDIO_CRC_ERROR_WAR) अणु
		ath6kl_err("temporary war to avoid sdio crc error\n");

		param = 0x28;
		address = GPIO_BASE_ADDRESS + GPIO_PIN9_ADDRESS;
		status = ath6kl_bmi_reg_ग_लिखो(ar, address, param);
		अगर (status)
			वापस status;

		param = 0x20;

		address = GPIO_BASE_ADDRESS + GPIO_PIN10_ADDRESS;
		status = ath6kl_bmi_reg_ग_लिखो(ar, address, param);
		अगर (status)
			वापस status;

		address = GPIO_BASE_ADDRESS + GPIO_PIN11_ADDRESS;
		status = ath6kl_bmi_reg_ग_लिखो(ar, address, param);
		अगर (status)
			वापस status;

		address = GPIO_BASE_ADDRESS + GPIO_PIN12_ADDRESS;
		status = ath6kl_bmi_reg_ग_लिखो(ar, address, param);
		अगर (status)
			वापस status;

		address = GPIO_BASE_ADDRESS + GPIO_PIN13_ADDRESS;
		status = ath6kl_bmi_reg_ग_लिखो(ar, address, param);
		अगर (status)
			वापस status;
	पूर्ण

	/* ग_लिखो EEPROM data to Target RAM */
	status = ath6kl_upload_board_file(ar);
	अगर (status)
		वापस status;

	/* transfer One समय Programmable data */
	status = ath6kl_upload_otp(ar);
	अगर (status)
		वापस status;

	/* Download Target firmware */
	status = ath6kl_upload_firmware(ar);
	अगर (status)
		वापस status;

	status = ath6kl_upload_patch(ar);
	अगर (status)
		वापस status;

	/* Download the test script */
	status = ath6kl_upload_testscript(ar);
	अगर (status)
		वापस status;

	/* Restore प्रणाली sleep */
	address = RTC_BASE_ADDRESS + SYSTEM_SLEEP_ADDRESS;
	status = ath6kl_bmi_reg_ग_लिखो(ar, address, sleep);
	अगर (status)
		वापस status;

	address = MBOX_BASE_ADDRESS + LOCAL_SCRATCH_ADDRESS;
	param = options | 0x20;
	status = ath6kl_bmi_reg_ग_लिखो(ar, address, param);
	अगर (status)
		वापस status;

	वापस status;
पूर्ण

पूर्णांक ath6kl_init_hw_params(काष्ठा ath6kl *ar)
अणु
	स्थिर काष्ठा ath6kl_hw *hw;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(hw_list); i++) अणु
		hw = &hw_list[i];

		अगर (hw->id == ar->version.target_ver)
			अवरोध;
	पूर्ण

	अगर (i == ARRAY_SIZE(hw_list)) अणु
		ath6kl_err("Unsupported hardware version: 0x%x\n",
			   ar->version.target_ver);
		वापस -EINVAL;
	पूर्ण

	ar->hw = *hw;

	ath6kl_dbg(ATH6KL_DBG_BOOT,
		   "target_ver 0x%x target_type 0x%x dataset_patch 0x%x app_load_addr 0x%x\n",
		   ar->version.target_ver, ar->target_type,
		   ar->hw.dataset_patch_addr, ar->hw.app_load_addr);
	ath6kl_dbg(ATH6KL_DBG_BOOT,
		   "app_start_override_addr 0x%x board_ext_data_addr 0x%x reserved_ram_size 0x%x",
		   ar->hw.app_start_override_addr, ar->hw.board_ext_data_addr,
		   ar->hw.reserved_ram_size);
	ath6kl_dbg(ATH6KL_DBG_BOOT,
		   "refclk_hz %d uarttx_pin %d",
		   ar->hw.refclk_hz, ar->hw.uarttx_pin);

	वापस 0;
पूर्ण

अटल स्थिर अक्षर *ath6kl_init_get_hअगर_name(क्रमागत ath6kl_hअगर_type type)
अणु
	चयन (type) अणु
	हाल ATH6KL_HIF_TYPE_SDIO:
		वापस "sdio";
	हाल ATH6KL_HIF_TYPE_USB:
		वापस "usb";
	पूर्ण

	वापस शून्य;
पूर्ण


अटल स्थिर काष्ठा fw_capa_str_map अणु
	पूर्णांक id;
	स्थिर अक्षर *name;
पूर्ण fw_capa_map[] = अणु
	अणु ATH6KL_FW_CAPABILITY_HOST_P2P, "host-p2p" पूर्ण,
	अणु ATH6KL_FW_CAPABILITY_SCHED_SCAN, "sched-scan" पूर्ण,
	अणु ATH6KL_FW_CAPABILITY_STA_P2PDEV_DUPLEX, "sta-p2pdev-duplex" पूर्ण,
	अणु ATH6KL_FW_CAPABILITY_INACTIVITY_TIMEOUT, "inactivity-timeout" पूर्ण,
	अणु ATH6KL_FW_CAPABILITY_RSN_CAP_OVERRIDE, "rsn-cap-override" पूर्ण,
	अणु ATH6KL_FW_CAPABILITY_WOW_MULTICAST_FILTER, "wow-mc-filter" पूर्ण,
	अणु ATH6KL_FW_CAPABILITY_BMISS_ENHANCE, "bmiss-enhance" पूर्ण,
	अणु ATH6KL_FW_CAPABILITY_SCHED_SCAN_MATCH_LIST, "sscan-match-list" पूर्ण,
	अणु ATH6KL_FW_CAPABILITY_RSSI_SCAN_THOLD, "rssi-scan-thold" पूर्ण,
	अणु ATH6KL_FW_CAPABILITY_CUSTOM_MAC_ADDR, "custom-mac-addr" पूर्ण,
	अणु ATH6KL_FW_CAPABILITY_TX_ERR_NOTIFY, "tx-err-notify" पूर्ण,
	अणु ATH6KL_FW_CAPABILITY_REGDOMAIN, "regdomain" पूर्ण,
	अणु ATH6KL_FW_CAPABILITY_SCHED_SCAN_V2, "sched-scan-v2" पूर्ण,
	अणु ATH6KL_FW_CAPABILITY_HEART_BEAT_POLL, "hb-poll" पूर्ण,
	अणु ATH6KL_FW_CAPABILITY_64BIT_RATES, "64bit-rates" पूर्ण,
	अणु ATH6KL_FW_CAPABILITY_AP_INACTIVITY_MINS, "ap-inactivity-mins" पूर्ण,
	अणु ATH6KL_FW_CAPABILITY_MAP_LP_ENDPOINT, "map-lp-endpoint" पूर्ण,
	अणु ATH6KL_FW_CAPABILITY_RATETABLE_MCS15, "ratetable-mcs15" पूर्ण,
	अणु ATH6KL_FW_CAPABILITY_NO_IP_CHECKSUM, "no-ip-checksum" पूर्ण,
पूर्ण;

अटल स्थिर अक्षर *ath6kl_init_get_fw_capa_name(अचिन्हित पूर्णांक id)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(fw_capa_map); i++) अणु
		अगर (fw_capa_map[i].id == id)
			वापस fw_capa_map[i].name;
	पूर्ण

	वापस "<unknown>";
पूर्ण

अटल व्योम ath6kl_init_get_fwcaps(काष्ठा ath6kl *ar, अक्षर *buf, माप_प्रकार buf_len)
अणु
	u8 *data = (u8 *) ar->fw_capabilities;
	माप_प्रकार trunc_len, len = 0;
	पूर्णांक i, index, bit;
	अक्षर *trunc = "...";

	क्रम (i = 0; i < ATH6KL_FW_CAPABILITY_MAX; i++) अणु
		index = i / 8;
		bit = i % 8;

		अगर (index >= माप(ar->fw_capabilities) * 4)
			अवरोध;

		अगर (buf_len - len < 4) अणु
			ath6kl_warn("firmware capability buffer too small!\n");

			/* add "..." to the end of string */
			trunc_len = म_माप(trunc) + 1;
			म_नकलन(buf + buf_len - trunc_len, trunc, trunc_len);

			वापस;
		पूर्ण

		अगर (data[index] & (1 << bit)) अणु
			len += scnम_लिखो(buf + len, buf_len - len, "%s,",
					    ath6kl_init_get_fw_capa_name(i));
		पूर्ण
	पूर्ण

	/* overग_लिखो the last comma */
	अगर (len > 0)
		len--;

	buf[len] = '\0';
पूर्ण

अटल पूर्णांक ath6kl_init_hw_reset(काष्ठा ath6kl *ar)
अणु
	ath6kl_dbg(ATH6KL_DBG_BOOT, "cold resetting the device");

	वापस ath6kl_diag_ग_लिखो32(ar, RESET_CONTROL_ADDRESS,
				   cpu_to_le32(RESET_CONTROL_COLD_RST));
पूर्ण

अटल पूर्णांक __ath6kl_init_hw_start(काष्ठा ath6kl *ar)
अणु
	दीर्घ समयleft;
	पूर्णांक ret, i;
	अक्षर buf[200];

	ath6kl_dbg(ATH6KL_DBG_BOOT, "hw start\n");

	ret = ath6kl_hअगर_घातer_on(ar);
	अगर (ret)
		वापस ret;

	ret = ath6kl_configure_target(ar);
	अगर (ret)
		जाओ err_घातer_off;

	ret = ath6kl_init_upload(ar);
	अगर (ret)
		जाओ err_घातer_off;

	/* Do we need to finish the BMI phase */
	ret = ath6kl_bmi_करोne(ar);
	अगर (ret)
		जाओ err_घातer_off;

	/*
	 * The reason we have to रुको क्रम the target here is that the
	 * driver layer has to init BMI in order to set the host block
	 * size.
	 */
	ret = ath6kl_htc_रुको_target(ar->htc_target);

	अगर (ret == -ETIMEDOUT) अणु
		/*
		 * Most likely USB target is in odd state after reboot and
		 * needs a reset. A cold reset makes the whole device
		 * disappear from USB bus and initialisation starts from
		 * beginning.
		 */
		ath6kl_warn("htc wait target timed out, resetting device\n");
		ath6kl_init_hw_reset(ar);
		जाओ err_घातer_off;
	पूर्ण अन्यथा अगर (ret) अणु
		ath6kl_err("htc wait target failed: %d\n", ret);
		जाओ err_घातer_off;
	पूर्ण

	ret = ath6kl_init_service_ep(ar);
	अगर (ret) अणु
		ath6kl_err("Endpoint service initialization failed: %d\n", ret);
		जाओ err_cleanup_scatter;
	पूर्ण

	/* setup credit distribution */
	ath6kl_htc_credit_setup(ar->htc_target, &ar->credit_state_info);

	/* start HTC */
	ret = ath6kl_htc_start(ar->htc_target);
	अगर (ret) अणु
		/* FIXME: call this */
		ath6kl_cookie_cleanup(ar);
		जाओ err_cleanup_scatter;
	पूर्ण

	/* Wait क्रम Wmi event to be पढ़ोy */
	समयleft = रुको_event_पूर्णांकerruptible_समयout(ar->event_wq,
						    test_bit(WMI_READY,
							     &ar->flag),
						    WMI_TIMEOUT);
	अगर (समयleft <= 0) अणु
		clear_bit(WMI_READY, &ar->flag);
		ath6kl_err("wmi is not ready or wait was interrupted: %ld\n",
			   समयleft);
		ret = -EIO;
		जाओ err_htc_stop;
	पूर्ण

	ath6kl_dbg(ATH6KL_DBG_BOOT, "firmware booted\n");

	अगर (test_and_clear_bit(FIRST_BOOT, &ar->flag)) अणु
		ath6kl_info("%s %s fw %s api %d%s\n",
			    ar->hw.name,
			    ath6kl_init_get_hअगर_name(ar->hअगर_type),
			    ar->wiphy->fw_version,
			    ar->fw_api,
			    test_bit(TESTMODE, &ar->flag) ? " testmode" : "");
		ath6kl_init_get_fwcaps(ar, buf, माप(buf));
		ath6kl_info("firmware supports: %s\n", buf);
	पूर्ण

	अगर (ar->version.abi_ver != ATH6KL_ABI_VERSION) अणु
		ath6kl_err("abi version mismatch: host(0x%x), target(0x%x)\n",
			   ATH6KL_ABI_VERSION, ar->version.abi_ver);
		ret = -EIO;
		जाओ err_htc_stop;
	पूर्ण

	ath6kl_dbg(ATH6KL_DBG_TRC, "%s: wmi is ready\n", __func__);

	/* communicate the wmi protocol verision to the target */
	/* FIXME: वापस error */
	अगर ((ath6kl_set_host_app_area(ar)) != 0)
		ath6kl_err("unable to set the host app area\n");

	क्रम (i = 0; i < ar->vअगर_max; i++) अणु
		ret = ath6kl_target_config_wlan_params(ar, i);
		अगर (ret)
			जाओ err_htc_stop;
	पूर्ण

	वापस 0;

err_htc_stop:
	ath6kl_htc_stop(ar->htc_target);
err_cleanup_scatter:
	ath6kl_hअगर_cleanup_scatter(ar);
err_घातer_off:
	ath6kl_hअगर_घातer_off(ar);

	वापस ret;
पूर्ण

पूर्णांक ath6kl_init_hw_start(काष्ठा ath6kl *ar)
अणु
	पूर्णांक err;

	err = __ath6kl_init_hw_start(ar);
	अगर (err)
		वापस err;
	ar->state = ATH6KL_STATE_ON;
	वापस 0;
पूर्ण

अटल पूर्णांक __ath6kl_init_hw_stop(काष्ठा ath6kl *ar)
अणु
	पूर्णांक ret;

	ath6kl_dbg(ATH6KL_DBG_BOOT, "hw stop\n");

	ath6kl_htc_stop(ar->htc_target);

	ath6kl_hअगर_stop(ar);

	ath6kl_bmi_reset(ar);

	ret = ath6kl_hअगर_घातer_off(ar);
	अगर (ret)
		ath6kl_warn("failed to power off hif: %d\n", ret);

	वापस 0;
पूर्ण

पूर्णांक ath6kl_init_hw_stop(काष्ठा ath6kl *ar)
अणु
	पूर्णांक err;

	err = __ath6kl_init_hw_stop(ar);
	अगर (err)
		वापस err;
	ar->state = ATH6KL_STATE_OFF;
	वापस 0;
पूर्ण

व्योम ath6kl_init_hw_restart(काष्ठा ath6kl *ar)
अणु
	clear_bit(WMI_READY, &ar->flag);

	ath6kl_cfg80211_stop_all(ar);

	अगर (__ath6kl_init_hw_stop(ar)) अणु
		ath6kl_dbg(ATH6KL_DBG_RECOVERY, "Failed to stop during fw error recovery\n");
		वापस;
	पूर्ण

	अगर (__ath6kl_init_hw_start(ar)) अणु
		ath6kl_dbg(ATH6KL_DBG_RECOVERY, "Failed to restart during fw error recovery\n");
		वापस;
	पूर्ण
पूर्ण

व्योम ath6kl_stop_txrx(काष्ठा ath6kl *ar)
अणु
	काष्ठा ath6kl_vअगर *vअगर, *पंचांगp_vअगर;
	पूर्णांक i;

	set_bit(DESTROY_IN_PROGRESS, &ar->flag);

	अगर (करोwn_पूर्णांकerruptible(&ar->sem)) अणु
		ath6kl_err("down_interruptible failed\n");
		वापस;
	पूर्ण

	क्रम (i = 0; i < AP_MAX_NUM_STA; i++)
		aggr_reset_state(ar->sta_list[i].aggr_conn);

	spin_lock_bh(&ar->list_lock);
	list_क्रम_each_entry_safe(vअगर, पंचांगp_vअगर, &ar->vअगर_list, list) अणु
		list_del(&vअगर->list);
		spin_unlock_bh(&ar->list_lock);
		ath6kl_cfg80211_vअगर_stop(vअगर, test_bit(WMI_READY, &ar->flag));
		rtnl_lock();
		wiphy_lock(ar->wiphy);
		ath6kl_cfg80211_vअगर_cleanup(vअगर);
		wiphy_unlock(ar->wiphy);
		rtnl_unlock();
		spin_lock_bh(&ar->list_lock);
	पूर्ण
	spin_unlock_bh(&ar->list_lock);

	clear_bit(WMI_READY, &ar->flag);

	अगर (ar->fw_recovery.enable)
		del_समयr_sync(&ar->fw_recovery.hb_समयr);

	/*
	 * After wmi_shuकरोwn all WMI events will be dropped. We
	 * need to cleanup the buffers allocated in AP mode and
	 * give disconnect notअगरication to stack, which usually
	 * happens in the disconnect_event. Simulate the disconnect
	 * event by calling the function directly. Someबार
	 * disconnect_event will be received when the debug logs
	 * are collected.
	 */
	ath6kl_wmi_shutकरोwn(ar->wmi);

	clear_bit(WMI_ENABLED, &ar->flag);
	अगर (ar->htc_target) अणु
		ath6kl_dbg(ATH6KL_DBG_TRC, "%s: shut down htc\n", __func__);
		ath6kl_htc_stop(ar->htc_target);
	पूर्ण

	/*
	 * Try to reset the device अगर we can. The driver may have been
	 * configure NOT to reset the target during a debug session.
	 */
	ath6kl_init_hw_reset(ar);

	up(&ar->sem);
पूर्ण
EXPORT_SYMBOL(ath6kl_stop_txrx);
