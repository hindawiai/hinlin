<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause-Clear
/*
 * Copyright (c) 2018-2019 The Linux Foundation. All rights reserved.
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/remoteproc.h>
#समावेश <linux/firmware.h>
#समावेश <linux/of.h>
#समावेश "core.h"
#समावेश "dp_tx.h"
#समावेश "dp_rx.h"
#समावेश "debug.h"
#समावेश "hif.h"
#समावेश "wow.h"

अचिन्हित पूर्णांक ath11k_debug_mask;
EXPORT_SYMBOL(ath11k_debug_mask);
module_param_named(debug_mask, ath11k_debug_mask, uपूर्णांक, 0644);
MODULE_PARM_DESC(debug_mask, "Debugging mask");

अटल अचिन्हित पूर्णांक ath11k_crypto_mode;
module_param_named(crypto_mode, ath11k_crypto_mode, uपूर्णांक, 0644);
MODULE_PARM_DESC(crypto_mode, "crypto mode: 0-hardware, 1-software");

/* frame mode values are mapped as per क्रमागत ath11k_hw_txrx_mode */
अचिन्हित पूर्णांक ath11k_frame_mode = ATH11K_HW_TXRX_NATIVE_WIFI;
module_param_named(frame_mode, ath11k_frame_mode, uपूर्णांक, 0644);
MODULE_PARM_DESC(frame_mode,
		 "Datapath frame mode (0: raw, 1: native wifi (default), 2: ethernet)");

अटल स्थिर काष्ठा ath11k_hw_params ath11k_hw_params[] = अणु
	अणु
		.hw_rev = ATH11K_HW_IPQ8074,
		.name = "ipq8074 hw2.0",
		.fw = अणु
			.dir = "IPQ8074/hw2.0",
			.board_size = 256 * 1024,
			.cal_size = 256 * 1024,
		पूर्ण,
		.max_radios = 3,
		.bdf_addr = 0x4B0C0000,
		.hw_ops = &ipq8074_ops,
		.ring_mask = &ath11k_hw_ring_mask_ipq8074,
		.पूर्णांकernal_sleep_घड़ी = false,
		.regs = &ipq8074_regs,
		.qmi_service_ins_id = ATH11K_QMI_WLFW_SERVICE_INS_ID_V01_IPQ8074,
		.host_ce_config = ath11k_host_ce_config_ipq8074,
		.ce_count = 12,
		.target_ce_config = ath11k_target_ce_config_wlan_ipq8074,
		.target_ce_count = 11,
		.svc_to_ce_map = ath11k_target_service_to_ce_map_wlan_ipq8074,
		.svc_to_ce_map_len = 21,
		.single_pdev_only = false,
		.rxdma1_enable = true,
		.num_rxmda_per_pdev = 1,
		.rx_mac_buf_ring = false,
		.vdev_start_delay = false,
		.htt_peer_map_v2 = true,
		.tcl_0_only = false,
		.spectral_fft_sz = 2,

		.पूर्णांकerface_modes = BIT(NL80211_IFTYPE_STATION) |
					BIT(NL80211_IFTYPE_AP) |
					BIT(NL80211_IFTYPE_MESH_POINT),
		.supports_monitor = true,
		.supports_shaकरोw_regs = false,
		.idle_ps = false,
		.cold_boot_calib = true,
		.supports_suspend = false,
		.hal_desc_sz = माप(काष्ठा hal_rx_desc_ipq8074),
	पूर्ण,
	अणु
		.hw_rev = ATH11K_HW_IPQ6018_HW10,
		.name = "ipq6018 hw1.0",
		.fw = अणु
			.dir = "IPQ6018/hw1.0",
			.board_size = 256 * 1024,
			.cal_size = 256 * 1024,
		पूर्ण,
		.max_radios = 2,
		.bdf_addr = 0x4ABC0000,
		.hw_ops = &ipq6018_ops,
		.ring_mask = &ath11k_hw_ring_mask_ipq8074,
		.पूर्णांकernal_sleep_घड़ी = false,
		.regs = &ipq8074_regs,
		.qmi_service_ins_id = ATH11K_QMI_WLFW_SERVICE_INS_ID_V01_IPQ8074,
		.host_ce_config = ath11k_host_ce_config_ipq8074,
		.ce_count = 12,
		.target_ce_config = ath11k_target_ce_config_wlan_ipq8074,
		.target_ce_count = 11,
		.svc_to_ce_map = ath11k_target_service_to_ce_map_wlan_ipq6018,
		.svc_to_ce_map_len = 19,
		.single_pdev_only = false,
		.rxdma1_enable = true,
		.num_rxmda_per_pdev = 1,
		.rx_mac_buf_ring = false,
		.vdev_start_delay = false,
		.htt_peer_map_v2 = true,
		.tcl_0_only = false,
		.spectral_fft_sz = 4,

		.पूर्णांकerface_modes = BIT(NL80211_IFTYPE_STATION) |
					BIT(NL80211_IFTYPE_AP) |
					BIT(NL80211_IFTYPE_MESH_POINT),
		.supports_monitor = true,
		.supports_shaकरोw_regs = false,
		.idle_ps = false,
		.cold_boot_calib = true,
		.supports_suspend = false,
		.hal_desc_sz = माप(काष्ठा hal_rx_desc_ipq8074),
	पूर्ण,
	अणु
		.name = "qca6390 hw2.0",
		.hw_rev = ATH11K_HW_QCA6390_HW20,
		.fw = अणु
			.dir = "QCA6390/hw2.0",
			.board_size = 256 * 1024,
			.cal_size = 256 * 1024,
		पूर्ण,
		.max_radios = 3,
		.bdf_addr = 0x4B0C0000,
		.hw_ops = &qca6390_ops,
		.ring_mask = &ath11k_hw_ring_mask_qca6390,
		.पूर्णांकernal_sleep_घड़ी = true,
		.regs = &qca6390_regs,
		.qmi_service_ins_id = ATH11K_QMI_WLFW_SERVICE_INS_ID_V01_QCA6390,
		.host_ce_config = ath11k_host_ce_config_qca6390,
		.ce_count = 9,
		.target_ce_config = ath11k_target_ce_config_wlan_qca6390,
		.target_ce_count = 9,
		.svc_to_ce_map = ath11k_target_service_to_ce_map_wlan_qca6390,
		.svc_to_ce_map_len = 14,
		.single_pdev_only = true,
		.rxdma1_enable = false,
		.num_rxmda_per_pdev = 2,
		.rx_mac_buf_ring = true,
		.vdev_start_delay = true,
		.htt_peer_map_v2 = false,
		.tcl_0_only = true,
		.spectral_fft_sz = 0,

		.पूर्णांकerface_modes = BIT(NL80211_IFTYPE_STATION) |
					BIT(NL80211_IFTYPE_AP),
		.supports_monitor = false,
		.supports_shaकरोw_regs = true,
		.idle_ps = true,
		.cold_boot_calib = false,
		.supports_suspend = true,
		.hal_desc_sz = माप(काष्ठा hal_rx_desc_ipq8074),
	पूर्ण,
	अणु
		.name = "qcn9074 hw1.0",
		.hw_rev = ATH11K_HW_QCN9074_HW10,
		.fw = अणु
			.dir = "QCN9074/hw1.0",
			.board_size = 256 * 1024,
			.cal_size = 256 * 1024,
		पूर्ण,
		.max_radios = 1,
		.single_pdev_only = false,
		.qmi_service_ins_id = ATH11K_QMI_WLFW_SERVICE_INS_ID_V01_QCN9074,
		.hw_ops = &qcn9074_ops,
		.ring_mask = &ath11k_hw_ring_mask_qcn9074,
		.पूर्णांकernal_sleep_घड़ी = false,
		.regs = &qcn9074_regs,
		.host_ce_config = ath11k_host_ce_config_qcn9074,
		.ce_count = 6,
		.target_ce_config = ath11k_target_ce_config_wlan_qcn9074,
		.target_ce_count = 9,
		.svc_to_ce_map = ath11k_target_service_to_ce_map_wlan_qcn9074,
		.svc_to_ce_map_len = 18,
		.rxdma1_enable = true,
		.num_rxmda_per_pdev = 1,
		.rx_mac_buf_ring = false,
		.vdev_start_delay = false,
		.htt_peer_map_v2 = true,
		.tcl_0_only = false,
		.पूर्णांकerface_modes = BIT(NL80211_IFTYPE_STATION) |
					BIT(NL80211_IFTYPE_AP) |
					BIT(NL80211_IFTYPE_MESH_POINT),
		.supports_monitor = true,
		.supports_shaकरोw_regs = false,
		.idle_ps = false,
		.cold_boot_calib = false,
		.supports_suspend = false,
		.hal_desc_sz = माप(काष्ठा hal_rx_desc_qcn9074),
	पूर्ण,
पूर्ण;

पूर्णांक ath11k_core_suspend(काष्ठा ath11k_base *ab)
अणु
	पूर्णांक ret;

	अगर (!ab->hw_params.supports_suspend)
		वापस -EOPNOTSUPP;

	/* TODO: there can frames in queues so क्रम now add delay as a hack.
	 * Need to implement to handle and हटाओ this delay.
	 */
	msleep(500);

	ret = ath11k_dp_rx_pktlog_stop(ab, true);
	अगर (ret) अणु
		ath11k_warn(ab, "failed to stop dp rx (and timer) pktlog during suspend: %d\n",
			    ret);
		वापस ret;
	पूर्ण

	ret = ath11k_wow_enable(ab);
	अगर (ret) अणु
		ath11k_warn(ab, "failed to enable wow during suspend: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = ath11k_dp_rx_pktlog_stop(ab, false);
	अगर (ret) अणु
		ath11k_warn(ab, "failed to stop dp rx pktlog during suspend: %d\n",
			    ret);
		वापस ret;
	पूर्ण

	ath11k_ce_stop_shaकरोw_समयrs(ab);
	ath11k_dp_stop_shaकरोw_समयrs(ab);

	ath11k_hअगर_irq_disable(ab);
	ath11k_hअगर_ce_irq_disable(ab);

	ret = ath11k_hअगर_suspend(ab);
	अगर (ret) अणु
		ath11k_warn(ab, "failed to suspend hif: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ath11k_core_suspend);

पूर्णांक ath11k_core_resume(काष्ठा ath11k_base *ab)
अणु
	पूर्णांक ret;

	अगर (!ab->hw_params.supports_suspend)
		वापस -EOPNOTSUPP;

	ret = ath11k_hअगर_resume(ab);
	अगर (ret) अणु
		ath11k_warn(ab, "failed to resume hif during resume: %d\n", ret);
		वापस ret;
	पूर्ण

	ath11k_hअगर_ce_irq_enable(ab);
	ath11k_hअगर_irq_enable(ab);

	ret = ath11k_dp_rx_pktlog_start(ab);
	अगर (ret) अणु
		ath11k_warn(ab, "failed to start rx pktlog during resume: %d\n",
			    ret);
		वापस ret;
	पूर्ण

	ret = ath11k_wow_wakeup(ab);
	अगर (ret) अणु
		ath11k_warn(ab, "failed to wakeup wow during resume: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ath11k_core_resume);

पूर्णांक ath11k_core_check_dt(काष्ठा ath11k_base *ab)
अणु
	माप_प्रकार max_len = माप(ab->qmi.target.bdf_ext);
	स्थिर अक्षर *variant = शून्य;
	काष्ठा device_node *node;

	node = ab->dev->of_node;
	अगर (!node)
		वापस -ENOENT;

	of_property_पढ़ो_string(node, "qcom,ath11k-calibration-variant",
				&variant);
	अगर (!variant)
		वापस -ENODATA;

	अगर (strscpy(ab->qmi.target.bdf_ext, variant, max_len) < 0)
		ath11k_dbg(ab, ATH11K_DBG_BOOT,
			   "bdf variant string is longer than the buffer can accommodate (variant: %s)\n",
			    variant);

	वापस 0;
पूर्ण

अटल पूर्णांक ath11k_core_create_board_name(काष्ठा ath11k_base *ab, अक्षर *name,
					 माप_प्रकार name_len)
अणु
	/* म_माप(',variant=') + म_माप(ab->qmi.target.bdf_ext) */
	अक्षर variant[9 + ATH11K_QMI_BDF_EXT_STR_LENGTH] = अणु 0 पूर्ण;

	अगर (ab->qmi.target.bdf_ext[0] != '\0')
		scnम_लिखो(variant, माप(variant), ",variant=%s",
			  ab->qmi.target.bdf_ext);

	scnम_लिखो(name, name_len,
		  "bus=%s,qmi-chip-id=%d,qmi-board-id=%d%s",
		  ath11k_bus_str(ab->hअगर.bus),
		  ab->qmi.target.chip_id,
		  ab->qmi.target.board_id, variant);

	ath11k_dbg(ab, ATH11K_DBG_BOOT, "boot using board name '%s'\n", name);

	वापस 0;
पूर्ण

स्थिर काष्ठा firmware *ath11k_core_firmware_request(काष्ठा ath11k_base *ab,
						    स्थिर अक्षर *file)
अणु
	स्थिर काष्ठा firmware *fw;
	अक्षर path[100];
	पूर्णांक ret;

	अगर (file == शून्य)
		वापस ERR_PTR(-ENOENT);

	ath11k_core_create_firmware_path(ab, file, path, माप(path));

	ret = firmware_request_nowarn(&fw, path, ab->dev);
	अगर (ret)
		वापस ERR_PTR(ret);

	ath11k_dbg(ab, ATH11K_DBG_BOOT, "boot firmware request %s size %zu\n",
		   path, fw->size);

	वापस fw;
पूर्ण

व्योम ath11k_core_मुक्त_bdf(काष्ठा ath11k_base *ab, काष्ठा ath11k_board_data *bd)
अणु
	अगर (!IS_ERR(bd->fw))
		release_firmware(bd->fw);

	स_रखो(bd, 0, माप(*bd));
पूर्ण

अटल पूर्णांक ath11k_core_parse_bd_ie_board(काष्ठा ath11k_base *ab,
					 काष्ठा ath11k_board_data *bd,
					 स्थिर व्योम *buf, माप_प्रकार buf_len,
					 स्थिर अक्षर *boardname,
					 पूर्णांक bd_ie_type)
अणु
	स्थिर काष्ठा ath11k_fw_ie *hdr;
	bool name_match_found;
	पूर्णांक ret, board_ie_id;
	माप_प्रकार board_ie_len;
	स्थिर व्योम *board_ie_data;

	name_match_found = false;

	/* go through ATH11K_BD_IE_BOARD_ elements */
	जबतक (buf_len > माप(काष्ठा ath11k_fw_ie)) अणु
		hdr = buf;
		board_ie_id = le32_to_cpu(hdr->id);
		board_ie_len = le32_to_cpu(hdr->len);
		board_ie_data = hdr->data;

		buf_len -= माप(*hdr);
		buf += माप(*hdr);

		अगर (buf_len < ALIGN(board_ie_len, 4)) अणु
			ath11k_err(ab, "invalid ATH11K_BD_IE_BOARD length: %zu < %zu\n",
				   buf_len, ALIGN(board_ie_len, 4));
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		चयन (board_ie_id) अणु
		हाल ATH11K_BD_IE_BOARD_NAME:
			ath11k_dbg_dump(ab, ATH11K_DBG_BOOT, "board name", "",
					board_ie_data, board_ie_len);

			अगर (board_ie_len != म_माप(boardname))
				अवरोध;

			ret = स_भेद(board_ie_data, boardname, म_माप(boardname));
			अगर (ret)
				अवरोध;

			name_match_found = true;
			ath11k_dbg(ab, ATH11K_DBG_BOOT,
				   "boot found match for name '%s'",
				   boardname);
			अवरोध;
		हाल ATH11K_BD_IE_BOARD_DATA:
			अगर (!name_match_found)
				/* no match found */
				अवरोध;

			ath11k_dbg(ab, ATH11K_DBG_BOOT,
				   "boot found board data for '%s'", boardname);

			bd->data = board_ie_data;
			bd->len = board_ie_len;

			ret = 0;
			जाओ out;
		शेष:
			ath11k_warn(ab, "unknown ATH11K_BD_IE_BOARD found: %d\n",
				    board_ie_id);
			अवरोध;
		पूर्ण

		/* jump over the padding */
		board_ie_len = ALIGN(board_ie_len, 4);

		buf_len -= board_ie_len;
		buf += board_ie_len;
	पूर्ण

	/* no match found */
	ret = -ENOENT;

out:
	वापस ret;
पूर्ण

अटल पूर्णांक ath11k_core_fetch_board_data_api_n(काष्ठा ath11k_base *ab,
					      काष्ठा ath11k_board_data *bd,
					      स्थिर अक्षर *boardname)
अणु
	माप_प्रकार len, magic_len;
	स्थिर u8 *data;
	अक्षर *filename, filepath[100];
	माप_प्रकार ie_len;
	काष्ठा ath11k_fw_ie *hdr;
	पूर्णांक ret, ie_id;

	filename = ATH11K_BOARD_API2_खाता;

	अगर (!bd->fw)
		bd->fw = ath11k_core_firmware_request(ab, filename);

	अगर (IS_ERR(bd->fw))
		वापस PTR_ERR(bd->fw);

	data = bd->fw->data;
	len = bd->fw->size;

	ath11k_core_create_firmware_path(ab, filename,
					 filepath, माप(filepath));

	/* magic has extra null byte padded */
	magic_len = म_माप(ATH11K_BOARD_MAGIC) + 1;
	अगर (len < magic_len) अणु
		ath11k_err(ab, "failed to find magic value in %s, file too short: %zu\n",
			   filepath, len);
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	अगर (स_भेद(data, ATH11K_BOARD_MAGIC, magic_len)) अणु
		ath11k_err(ab, "found invalid board magic\n");
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	/* magic is padded to 4 bytes */
	magic_len = ALIGN(magic_len, 4);
	अगर (len < magic_len) अणु
		ath11k_err(ab, "failed: %s too small to contain board data, len: %zu\n",
			   filepath, len);
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	data += magic_len;
	len -= magic_len;

	जबतक (len > माप(काष्ठा ath11k_fw_ie)) अणु
		hdr = (काष्ठा ath11k_fw_ie *)data;
		ie_id = le32_to_cpu(hdr->id);
		ie_len = le32_to_cpu(hdr->len);

		len -= माप(*hdr);
		data = hdr->data;

		अगर (len < ALIGN(ie_len, 4)) अणु
			ath11k_err(ab, "invalid length for board ie_id %d ie_len %zu len %zu\n",
				   ie_id, ie_len, len);
			वापस -EINVAL;
		पूर्ण

		चयन (ie_id) अणु
		हाल ATH11K_BD_IE_BOARD:
			ret = ath11k_core_parse_bd_ie_board(ab, bd, data,
							    ie_len,
							    boardname,
							    ATH11K_BD_IE_BOARD);
			अगर (ret == -ENOENT)
				/* no match found, जारी */
				अवरोध;
			अन्यथा अगर (ret)
				/* there was an error, bail out */
				जाओ err;
			/* either found or error, so stop searching */
			जाओ out;
		पूर्ण

		/* jump over the padding */
		ie_len = ALIGN(ie_len, 4);

		len -= ie_len;
		data += ie_len;
	पूर्ण

out:
	अगर (!bd->data || !bd->len) अणु
		ath11k_err(ab,
			   "failed to fetch board data for %s from %s\n",
			   boardname, filepath);
		ret = -ENODATA;
		जाओ err;
	पूर्ण

	वापस 0;

err:
	ath11k_core_मुक्त_bdf(ab, bd);
	वापस ret;
पूर्ण

अटल पूर्णांक ath11k_core_fetch_board_data_api_1(काष्ठा ath11k_base *ab,
					      काष्ठा ath11k_board_data *bd)
अणु
	bd->fw = ath11k_core_firmware_request(ab, ATH11K_DEFAULT_BOARD_खाता);
	अगर (IS_ERR(bd->fw))
		वापस PTR_ERR(bd->fw);

	bd->data = bd->fw->data;
	bd->len = bd->fw->size;

	वापस 0;
पूर्ण

#घोषणा BOARD_NAME_SIZE 100
पूर्णांक ath11k_core_fetch_bdf(काष्ठा ath11k_base *ab, काष्ठा ath11k_board_data *bd)
अणु
	अक्षर boardname[BOARD_NAME_SIZE];
	पूर्णांक ret;

	ret = ath11k_core_create_board_name(ab, boardname, BOARD_NAME_SIZE);
	अगर (ret) अणु
		ath11k_err(ab, "failed to create board name: %d", ret);
		वापस ret;
	पूर्ण

	ab->bd_api = 2;
	ret = ath11k_core_fetch_board_data_api_n(ab, bd, boardname);
	अगर (!ret)
		जाओ success;

	ab->bd_api = 1;
	ret = ath11k_core_fetch_board_data_api_1(ab, bd);
	अगर (ret) अणु
		ath11k_err(ab, "failed to fetch board-2.bin or board.bin from %s\n",
			   ab->hw_params.fw.dir);
		वापस ret;
	पूर्ण

success:
	ath11k_dbg(ab, ATH11K_DBG_BOOT, "using board api %d\n", ab->bd_api);
	वापस 0;
पूर्ण

अटल व्योम ath11k_core_stop(काष्ठा ath11k_base *ab)
अणु
	अगर (!test_bit(ATH11K_FLAG_CRASH_FLUSH, &ab->dev_flags))
		ath11k_qmi_firmware_stop(ab);

	ath11k_hअगर_stop(ab);
	ath11k_wmi_detach(ab);
	ath11k_dp_pdev_reo_cleanup(ab);

	/* De-Init of components as needed */
पूर्ण

अटल पूर्णांक ath11k_core_soc_create(काष्ठा ath11k_base *ab)
अणु
	पूर्णांक ret;

	ret = ath11k_qmi_init_service(ab);
	अगर (ret) अणु
		ath11k_err(ab, "failed to initialize qmi :%d\n", ret);
		वापस ret;
	पूर्ण

	ret = ath11k_debugfs_soc_create(ab);
	अगर (ret) अणु
		ath11k_err(ab, "failed to create ath11k debugfs\n");
		जाओ err_qmi_deinit;
	पूर्ण

	ret = ath11k_hअगर_घातer_up(ab);
	अगर (ret) अणु
		ath11k_err(ab, "failed to power up :%d\n", ret);
		जाओ err_debugfs_reg;
	पूर्ण

	वापस 0;

err_debugfs_reg:
	ath11k_debugfs_soc_destroy(ab);
err_qmi_deinit:
	ath11k_qmi_deinit_service(ab);
	वापस ret;
पूर्ण

अटल व्योम ath11k_core_soc_destroy(काष्ठा ath11k_base *ab)
अणु
	ath11k_debugfs_soc_destroy(ab);
	ath11k_dp_मुक्त(ab);
	ath11k_reg_मुक्त(ab);
	ath11k_qmi_deinit_service(ab);
पूर्ण

अटल पूर्णांक ath11k_core_pdev_create(काष्ठा ath11k_base *ab)
अणु
	पूर्णांक ret;

	ret = ath11k_debugfs_pdev_create(ab);
	अगर (ret) अणु
		ath11k_err(ab, "failed to create core pdev debugfs: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = ath11k_mac_रेजिस्टर(ab);
	अगर (ret) अणु
		ath11k_err(ab, "failed register the radio with mac80211: %d\n", ret);
		जाओ err_pdev_debug;
	पूर्ण

	ret = ath11k_dp_pdev_alloc(ab);
	अगर (ret) अणु
		ath11k_err(ab, "failed to attach DP pdev: %d\n", ret);
		जाओ err_mac_unरेजिस्टर;
	पूर्ण

	ret = ath11k_thermal_रेजिस्टर(ab);
	अगर (ret) अणु
		ath11k_err(ab, "could not register thermal device: %d\n",
			   ret);
		जाओ err_dp_pdev_मुक्त;
	पूर्ण

	ret = ath11k_spectral_init(ab);
	अगर (ret) अणु
		ath11k_err(ab, "failed to init spectral %d\n", ret);
		जाओ err_thermal_unरेजिस्टर;
	पूर्ण

	वापस 0;

err_thermal_unरेजिस्टर:
	ath11k_thermal_unरेजिस्टर(ab);
err_dp_pdev_मुक्त:
	ath11k_dp_pdev_मुक्त(ab);
err_mac_unरेजिस्टर:
	ath11k_mac_unरेजिस्टर(ab);
err_pdev_debug:
	ath11k_debugfs_pdev_destroy(ab);

	वापस ret;
पूर्ण

अटल व्योम ath11k_core_pdev_destroy(काष्ठा ath11k_base *ab)
अणु
	ath11k_spectral_deinit(ab);
	ath11k_thermal_unरेजिस्टर(ab);
	ath11k_mac_unरेजिस्टर(ab);
	ath11k_hअगर_irq_disable(ab);
	ath11k_dp_pdev_मुक्त(ab);
	ath11k_debugfs_pdev_destroy(ab);
पूर्ण

अटल पूर्णांक ath11k_core_start(काष्ठा ath11k_base *ab,
			     क्रमागत ath11k_firmware_mode mode)
अणु
	पूर्णांक ret;

	ret = ath11k_qmi_firmware_start(ab, mode);
	अगर (ret) अणु
		ath11k_err(ab, "failed to attach wmi: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = ath11k_wmi_attach(ab);
	अगर (ret) अणु
		ath11k_err(ab, "failed to attach wmi: %d\n", ret);
		जाओ err_firmware_stop;
	पूर्ण

	ret = ath11k_htc_init(ab);
	अगर (ret) अणु
		ath11k_err(ab, "failed to init htc: %d\n", ret);
		जाओ err_wmi_detach;
	पूर्ण

	ret = ath11k_hअगर_start(ab);
	अगर (ret) अणु
		ath11k_err(ab, "failed to start HIF: %d\n", ret);
		जाओ err_wmi_detach;
	पूर्ण

	ret = ath11k_htc_रुको_target(&ab->htc);
	अगर (ret) अणु
		ath11k_err(ab, "failed to connect to HTC: %d\n", ret);
		जाओ err_hअगर_stop;
	पूर्ण

	ret = ath11k_dp_htt_connect(&ab->dp);
	अगर (ret) अणु
		ath11k_err(ab, "failed to connect to HTT: %d\n", ret);
		जाओ err_hअगर_stop;
	पूर्ण

	ret = ath11k_wmi_connect(ab);
	अगर (ret) अणु
		ath11k_err(ab, "failed to connect wmi: %d\n", ret);
		जाओ err_hअगर_stop;
	पूर्ण

	ret = ath11k_htc_start(&ab->htc);
	अगर (ret) अणु
		ath11k_err(ab, "failed to start HTC: %d\n", ret);
		जाओ err_hअगर_stop;
	पूर्ण

	ret = ath11k_wmi_रुको_क्रम_service_पढ़ोy(ab);
	अगर (ret) अणु
		ath11k_err(ab, "failed to receive wmi service ready event: %d\n",
			   ret);
		जाओ err_hअगर_stop;
	पूर्ण

	ret = ath11k_mac_allocate(ab);
	अगर (ret) अणु
		ath11k_err(ab, "failed to create new hw device with mac80211 :%d\n",
			   ret);
		जाओ err_hअगर_stop;
	पूर्ण

	ath11k_dp_pdev_pre_alloc(ab);

	ret = ath11k_dp_pdev_reo_setup(ab);
	अगर (ret) अणु
		ath11k_err(ab, "failed to initialize reo destination rings: %d\n", ret);
		जाओ err_mac_destroy;
	पूर्ण

	ret = ath11k_wmi_cmd_init(ab);
	अगर (ret) अणु
		ath11k_err(ab, "failed to send wmi init cmd: %d\n", ret);
		जाओ err_reo_cleanup;
	पूर्ण

	ret = ath11k_wmi_रुको_क्रम_unअगरied_पढ़ोy(ab);
	अगर (ret) अणु
		ath11k_err(ab, "failed to receive wmi unified ready event: %d\n",
			   ret);
		जाओ err_reo_cleanup;
	पूर्ण

	/* put hardware to DBS mode */
	अगर (ab->hw_params.single_pdev_only) अणु
		ret = ath11k_wmi_set_hw_mode(ab, WMI_HOST_HW_MODE_DBS);
		अगर (ret) अणु
			ath11k_err(ab, "failed to send dbs mode: %d\n", ret);
			जाओ err_hअगर_stop;
		पूर्ण
	पूर्ण

	ret = ath11k_dp_tx_htt_h2t_ver_req_msg(ab);
	अगर (ret) अणु
		ath11k_err(ab, "failed to send htt version request message: %d\n",
			   ret);
		जाओ err_reo_cleanup;
	पूर्ण

	वापस 0;

err_reo_cleanup:
	ath11k_dp_pdev_reo_cleanup(ab);
err_mac_destroy:
	ath11k_mac_destroy(ab);
err_hअगर_stop:
	ath11k_hअगर_stop(ab);
err_wmi_detach:
	ath11k_wmi_detach(ab);
err_firmware_stop:
	ath11k_qmi_firmware_stop(ab);

	वापस ret;
पूर्ण

पूर्णांक ath11k_core_qmi_firmware_पढ़ोy(काष्ठा ath11k_base *ab)
अणु
	पूर्णांक ret;

	ret = ath11k_ce_init_pipes(ab);
	अगर (ret) अणु
		ath11k_err(ab, "failed to initialize CE: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = ath11k_dp_alloc(ab);
	अगर (ret) अणु
		ath11k_err(ab, "failed to init DP: %d\n", ret);
		वापस ret;
	पूर्ण

	चयन (ath11k_crypto_mode) अणु
	हाल ATH11K_CRYPT_MODE_SW:
		set_bit(ATH11K_FLAG_HW_CRYPTO_DISABLED, &ab->dev_flags);
		set_bit(ATH11K_FLAG_RAW_MODE, &ab->dev_flags);
		अवरोध;
	हाल ATH11K_CRYPT_MODE_HW:
		clear_bit(ATH11K_FLAG_HW_CRYPTO_DISABLED, &ab->dev_flags);
		clear_bit(ATH11K_FLAG_RAW_MODE, &ab->dev_flags);
		अवरोध;
	शेष:
		ath11k_info(ab, "invalid crypto_mode: %d\n", ath11k_crypto_mode);
		वापस -EINVAL;
	पूर्ण

	अगर (ath11k_frame_mode == ATH11K_HW_TXRX_RAW)
		set_bit(ATH11K_FLAG_RAW_MODE, &ab->dev_flags);

	mutex_lock(&ab->core_lock);
	ret = ath11k_core_start(ab, ATH11K_FIRMWARE_MODE_NORMAL);
	अगर (ret) अणु
		ath11k_err(ab, "failed to start core: %d\n", ret);
		जाओ err_dp_मुक्त;
	पूर्ण

	ret = ath11k_core_pdev_create(ab);
	अगर (ret) अणु
		ath11k_err(ab, "failed to create pdev core: %d\n", ret);
		जाओ err_core_stop;
	पूर्ण
	ath11k_hअगर_irq_enable(ab);
	mutex_unlock(&ab->core_lock);

	वापस 0;

err_core_stop:
	ath11k_core_stop(ab);
	ath11k_mac_destroy(ab);
err_dp_मुक्त:
	ath11k_dp_मुक्त(ab);
	mutex_unlock(&ab->core_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक ath11k_core_reconfigure_on_crash(काष्ठा ath11k_base *ab)
अणु
	पूर्णांक ret;

	mutex_lock(&ab->core_lock);
	ath11k_thermal_unरेजिस्टर(ab);
	ath11k_hअगर_irq_disable(ab);
	ath11k_dp_pdev_मुक्त(ab);
	ath11k_spectral_deinit(ab);
	ath11k_hअगर_stop(ab);
	ath11k_wmi_detach(ab);
	ath11k_dp_pdev_reo_cleanup(ab);
	mutex_unlock(&ab->core_lock);

	ath11k_dp_मुक्त(ab);
	ath11k_hal_srng_deinit(ab);

	ab->मुक्त_vdev_map = (1LL << (ab->num_radios * TARGET_NUM_VDEVS)) - 1;

	ret = ath11k_hal_srng_init(ab);
	अगर (ret)
		वापस ret;

	clear_bit(ATH11K_FLAG_CRASH_FLUSH, &ab->dev_flags);

	ret = ath11k_core_qmi_firmware_पढ़ोy(ab);
	अगर (ret)
		जाओ err_hal_srng_deinit;

	clear_bit(ATH11K_FLAG_RECOVERY, &ab->dev_flags);

	वापस 0;

err_hal_srng_deinit:
	ath11k_hal_srng_deinit(ab);
	वापस ret;
पूर्ण

व्योम ath11k_core_halt(काष्ठा ath11k *ar)
अणु
	काष्ठा ath11k_base *ab = ar->ab;

	lockdep_निश्चित_held(&ar->conf_mutex);

	ar->num_created_vdevs = 0;
	ar->allocated_vdev_map = 0;

	ath11k_mac_scan_finish(ar);
	ath11k_mac_peer_cleanup_all(ar);
	cancel_delayed_work_sync(&ar->scan.समयout);
	cancel_work_sync(&ar->regd_update_work);

	rcu_assign_poपूर्णांकer(ab->pdevs_active[ar->pdev_idx], शून्य);
	synchronize_rcu();
	INIT_LIST_HEAD(&ar->arvअगरs);
	idr_init(&ar->txmgmt_idr);
पूर्ण

अटल व्योम ath11k_core_restart(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ath11k_base *ab = container_of(work, काष्ठा ath11k_base, restart_work);
	काष्ठा ath11k *ar;
	काष्ठा ath11k_pdev *pdev;
	पूर्णांक i, ret = 0;

	spin_lock_bh(&ab->base_lock);
	ab->stats.fw_crash_counter++;
	spin_unlock_bh(&ab->base_lock);

	क्रम (i = 0; i < ab->num_radios; i++) अणु
		pdev = &ab->pdevs[i];
		ar = pdev->ar;
		अगर (!ar || ar->state == ATH11K_STATE_OFF)
			जारी;

		ieee80211_stop_queues(ar->hw);
		ath11k_mac_drain_tx(ar);
		complete(&ar->scan.started);
		complete(&ar->scan.completed);
		complete(&ar->peer_assoc_करोne);
		complete(&ar->peer_delete_करोne);
		complete(&ar->install_key_करोne);
		complete(&ar->vdev_setup_करोne);
		complete(&ar->vdev_delete_करोne);
		complete(&ar->bss_survey_करोne);
		complete(&ar->thermal.wmi_sync);

		wake_up(&ar->dp.tx_empty_रुकोq);
		idr_क्रम_each(&ar->txmgmt_idr,
			     ath11k_mac_tx_mgmt_pending_मुक्त, ar);
		idr_destroy(&ar->txmgmt_idr);
	पूर्ण

	wake_up(&ab->wmi_ab.tx_credits_wq);
	wake_up(&ab->peer_mapping_wq);

	ret = ath11k_core_reconfigure_on_crash(ab);
	अगर (ret) अणु
		ath11k_err(ab, "failed to reconfigure driver on crash recovery\n");
		वापस;
	पूर्ण

	क्रम (i = 0; i < ab->num_radios; i++) अणु
		pdev = &ab->pdevs[i];
		ar = pdev->ar;
		अगर (!ar || ar->state == ATH11K_STATE_OFF)
			जारी;

		mutex_lock(&ar->conf_mutex);

		चयन (ar->state) अणु
		हाल ATH11K_STATE_ON:
			ar->state = ATH11K_STATE_RESTARTING;
			ath11k_core_halt(ar);
			ieee80211_restart_hw(ar->hw);
			अवरोध;
		हाल ATH11K_STATE_OFF:
			ath11k_warn(ab,
				    "cannot restart radio %d that hasn't been started\n",
				    i);
			अवरोध;
		हाल ATH11K_STATE_RESTARTING:
			अवरोध;
		हाल ATH11K_STATE_RESTARTED:
			ar->state = ATH11K_STATE_WEDGED;
			fallthrough;
		हाल ATH11K_STATE_WEDGED:
			ath11k_warn(ab,
				    "device is wedged, will not restart radio %d\n", i);
			अवरोध;
		पूर्ण
		mutex_unlock(&ar->conf_mutex);
	पूर्ण
	complete(&ab->driver_recovery);
पूर्ण

अटल पूर्णांक ath11k_init_hw_params(काष्ठा ath11k_base *ab)
अणु
	स्थिर काष्ठा ath11k_hw_params *hw_params = शून्य;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(ath11k_hw_params); i++) अणु
		hw_params = &ath11k_hw_params[i];

		अगर (hw_params->hw_rev == ab->hw_rev)
			अवरोध;
	पूर्ण

	अगर (i == ARRAY_SIZE(ath11k_hw_params)) अणु
		ath11k_err(ab, "Unsupported hardware version: 0x%x\n", ab->hw_rev);
		वापस -EINVAL;
	पूर्ण

	ab->hw_params = *hw_params;

	ath11k_info(ab, "%s\n", ab->hw_params.name);

	वापस 0;
पूर्ण

पूर्णांक ath11k_core_pre_init(काष्ठा ath11k_base *ab)
अणु
	पूर्णांक ret;

	ret = ath11k_init_hw_params(ab);
	अगर (ret) अणु
		ath11k_err(ab, "failed to get hw params: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ath11k_core_pre_init);

पूर्णांक ath11k_core_init(काष्ठा ath11k_base *ab)
अणु
	पूर्णांक ret;

	ret = ath11k_core_soc_create(ab);
	अगर (ret) अणु
		ath11k_err(ab, "failed to create soc core: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ath11k_core_init);

व्योम ath11k_core_deinit(काष्ठा ath11k_base *ab)
अणु
	mutex_lock(&ab->core_lock);

	ath11k_core_pdev_destroy(ab);
	ath11k_core_stop(ab);

	mutex_unlock(&ab->core_lock);

	ath11k_hअगर_घातer_करोwn(ab);
	ath11k_mac_destroy(ab);
	ath11k_core_soc_destroy(ab);
पूर्ण
EXPORT_SYMBOL(ath11k_core_deinit);

व्योम ath11k_core_मुक्त(काष्ठा ath11k_base *ab)
अणु
	kमुक्त(ab);
पूर्ण
EXPORT_SYMBOL(ath11k_core_मुक्त);

काष्ठा ath11k_base *ath11k_core_alloc(काष्ठा device *dev, माप_प्रकार priv_size,
				      क्रमागत ath11k_bus bus,
				      स्थिर काष्ठा ath11k_bus_params *bus_params)
अणु
	काष्ठा ath11k_base *ab;

	ab = kzalloc(माप(*ab) + priv_size, GFP_KERNEL);
	अगर (!ab)
		वापस शून्य;

	init_completion(&ab->driver_recovery);

	ab->workqueue = create_singlethपढ़ो_workqueue("ath11k_wq");
	अगर (!ab->workqueue)
		जाओ err_sc_मुक्त;

	mutex_init(&ab->core_lock);
	spin_lock_init(&ab->base_lock);

	INIT_LIST_HEAD(&ab->peers);
	init_रुकोqueue_head(&ab->peer_mapping_wq);
	init_रुकोqueue_head(&ab->wmi_ab.tx_credits_wq);
	init_रुकोqueue_head(&ab->qmi.cold_boot_रुकोq);
	INIT_WORK(&ab->restart_work, ath11k_core_restart);
	समयr_setup(&ab->rx_replenish_retry, ath11k_ce_rx_replenish_retry, 0);
	init_completion(&ab->htc_suspend);
	init_completion(&ab->wow.wakeup_completed);

	ab->dev = dev;
	ab->bus_params = *bus_params;
	ab->hअगर.bus = bus;

	वापस ab;

err_sc_मुक्त:
	kमुक्त(ab);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(ath11k_core_alloc);

MODULE_DESCRIPTION("Core module for Qualcomm Atheros 802.11ax wireless LAN cards.");
MODULE_LICENSE("Dual BSD/GPL");
