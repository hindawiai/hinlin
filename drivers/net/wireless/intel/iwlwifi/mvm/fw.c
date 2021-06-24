<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/*
 * Copyright (C) 2012-2014, 2018-2021 Intel Corporation
 * Copyright (C) 2013-2015 Intel Mobile Communications GmbH
 * Copyright (C) 2016-2017 Intel Deutschland GmbH
 */
#समावेश <net/mac80211.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/dmi.h>

#समावेश "iwl-trans.h"
#समावेश "iwl-op-mode.h"
#समावेश "fw/img.h"
#समावेश "iwl-debug.h"
#समावेश "iwl-csr.h" /* क्रम iwl_mvm_rx_card_state_notअगर */
#समावेश "iwl-io.h" /* क्रम iwl_mvm_rx_card_state_notअगर */
#समावेश "iwl-prph.h"
#समावेश "fw/acpi.h"
#समावेश "fw/pnvm.h"

#समावेश "mvm.h"
#समावेश "fw/dbg.h"
#समावेश "iwl-phy-db.h"
#समावेश "iwl-modparams.h"
#समावेश "iwl-nvm-parse.h"

#घोषणा MVM_UCODE_ALIVE_TIMEOUT	(HZ)
#घोषणा MVM_UCODE_CALIB_TIMEOUT	(2 * HZ)

#घोषणा UCODE_VALID_OK	cpu_to_le32(0x1)

#घोषणा IWL_PPAG_MASK 3
#घोषणा IWL_PPAG_ETSI_MASK BIT(0)

काष्ठा iwl_mvm_alive_data अणु
	bool valid;
	u32 scd_base_addr;
पूर्ण;

अटल पूर्णांक iwl_send_tx_ant_cfg(काष्ठा iwl_mvm *mvm, u8 valid_tx_ant)
अणु
	काष्ठा iwl_tx_ant_cfg_cmd tx_ant_cmd = अणु
		.valid = cpu_to_le32(valid_tx_ant),
	पूर्ण;

	IWL_DEBUG_FW(mvm, "select valid tx ant: %u\n", valid_tx_ant);
	वापस iwl_mvm_send_cmd_pdu(mvm, TX_ANT_CONFIGURATION_CMD, 0,
				    माप(tx_ant_cmd), &tx_ant_cmd);
पूर्ण

अटल पूर्णांक iwl_send_rss_cfg_cmd(काष्ठा iwl_mvm *mvm)
अणु
	पूर्णांक i;
	काष्ठा iwl_rss_config_cmd cmd = अणु
		.flags = cpu_to_le32(IWL_RSS_ENABLE),
		.hash_mask = BIT(IWL_RSS_HASH_TYPE_IPV4_TCP) |
			     BIT(IWL_RSS_HASH_TYPE_IPV4_UDP) |
			     BIT(IWL_RSS_HASH_TYPE_IPV4_PAYLOAD) |
			     BIT(IWL_RSS_HASH_TYPE_IPV6_TCP) |
			     BIT(IWL_RSS_HASH_TYPE_IPV6_UDP) |
			     BIT(IWL_RSS_HASH_TYPE_IPV6_PAYLOAD),
	पूर्ण;

	अगर (mvm->trans->num_rx_queues == 1)
		वापस 0;

	/* Do not direct RSS traffic to Q 0 which is our fallback queue */
	क्रम (i = 0; i < ARRAY_SIZE(cmd.indirection_table); i++)
		cmd.indirection_table[i] =
			1 + (i % (mvm->trans->num_rx_queues - 1));
	netdev_rss_key_fill(cmd.secret_key, माप(cmd.secret_key));

	वापस iwl_mvm_send_cmd_pdu(mvm, RSS_CONFIG_CMD, 0, माप(cmd), &cmd);
पूर्ण

अटल पूर्णांक iwl_mvm_send_dqa_cmd(काष्ठा iwl_mvm *mvm)
अणु
	काष्ठा iwl_dqa_enable_cmd dqa_cmd = अणु
		.cmd_queue = cpu_to_le32(IWL_MVM_DQA_CMD_QUEUE),
	पूर्ण;
	u32 cmd_id = iwl_cmd_id(DQA_ENABLE_CMD, DATA_PATH_GROUP, 0);
	पूर्णांक ret;

	ret = iwl_mvm_send_cmd_pdu(mvm, cmd_id, 0, माप(dqa_cmd), &dqa_cmd);
	अगर (ret)
		IWL_ERR(mvm, "Failed to send DQA enabling command: %d\n", ret);
	अन्यथा
		IWL_DEBUG_FW(mvm, "Working in DQA mode\n");

	वापस ret;
पूर्ण

व्योम iwl_mvm_mfu_निश्चित_dump_notअगर(काष्ठा iwl_mvm *mvm,
				   काष्ठा iwl_rx_cmd_buffer *rxb)
अणु
	काष्ठा iwl_rx_packet *pkt = rxb_addr(rxb);
	काष्ठा iwl_mfu_निश्चित_dump_notअगर *mfu_dump_notअगर = (व्योम *)pkt->data;
	__le32 *dump_data = mfu_dump_notअगर->data;
	पूर्णांक n_words = le32_to_cpu(mfu_dump_notअगर->data_size) / माप(__le32);
	पूर्णांक i;

	अगर (mfu_dump_notअगर->index_num == 0)
		IWL_INFO(mvm, "MFUART assert id 0x%x occurred\n",
			 le32_to_cpu(mfu_dump_notअगर->निश्चित_id));

	क्रम (i = 0; i < n_words; i++)
		IWL_DEBUG_INFO(mvm,
			       "MFUART assert dump, dword %u: 0x%08x\n",
			       le16_to_cpu(mfu_dump_notअगर->index_num) *
			       n_words + i,
			       le32_to_cpu(dump_data[i]));
पूर्ण

अटल bool iwl_alive_fn(काष्ठा iwl_notअगर_रुको_data *notअगर_रुको,
			 काष्ठा iwl_rx_packet *pkt, व्योम *data)
अणु
	अचिन्हित पूर्णांक pkt_len = iwl_rx_packet_payload_len(pkt);
	काष्ठा iwl_mvm *mvm =
		container_of(notअगर_रुको, काष्ठा iwl_mvm, notअगर_रुको);
	काष्ठा iwl_mvm_alive_data *alive_data = data;
	काष्ठा iwl_umac_alive *umac;
	काष्ठा iwl_lmac_alive *lmac1;
	काष्ठा iwl_lmac_alive *lmac2 = शून्य;
	u16 status;
	u32 lmac_error_event_table, umac_error_table;

	/*
	 * For v5 and above, we can check the version, क्रम older
	 * versions we need to check the size.
	 */
	अगर (iwl_fw_lookup_notअगर_ver(mvm->fw, LEGACY_GROUP,
				    UCODE_ALIVE_NTFY, 0) == 5) अणु
		काष्ठा iwl_alive_ntf_v5 *palive;

		अगर (pkt_len < माप(*palive))
			वापस false;

		palive = (व्योम *)pkt->data;
		umac = &palive->umac_data;
		lmac1 = &palive->lmac_data[0];
		lmac2 = &palive->lmac_data[1];
		status = le16_to_cpu(palive->status);

		mvm->trans->sku_id[0] = le32_to_cpu(palive->sku_id.data[0]);
		mvm->trans->sku_id[1] = le32_to_cpu(palive->sku_id.data[1]);
		mvm->trans->sku_id[2] = le32_to_cpu(palive->sku_id.data[2]);

		IWL_DEBUG_FW(mvm, "Got sku_id: 0x0%x 0x0%x 0x0%x\n",
			     mvm->trans->sku_id[0],
			     mvm->trans->sku_id[1],
			     mvm->trans->sku_id[2]);
	पूर्ण अन्यथा अगर (iwl_rx_packet_payload_len(pkt) == माप(काष्ठा iwl_alive_ntf_v4)) अणु
		काष्ठा iwl_alive_ntf_v4 *palive;

		अगर (pkt_len < माप(*palive))
			वापस false;

		palive = (व्योम *)pkt->data;
		umac = &palive->umac_data;
		lmac1 = &palive->lmac_data[0];
		lmac2 = &palive->lmac_data[1];
		status = le16_to_cpu(palive->status);
	पूर्ण अन्यथा अगर (iwl_rx_packet_payload_len(pkt) ==
		   माप(काष्ठा iwl_alive_ntf_v3)) अणु
		काष्ठा iwl_alive_ntf_v3 *palive3;

		अगर (pkt_len < माप(*palive3))
			वापस false;

		palive3 = (व्योम *)pkt->data;
		umac = &palive3->umac_data;
		lmac1 = &palive3->lmac_data;
		status = le16_to_cpu(palive3->status);
	पूर्ण अन्यथा अणु
		WARN(1, "unsupported alive notification (size %d)\n",
		     iwl_rx_packet_payload_len(pkt));
		/* get समयout later */
		वापस false;
	पूर्ण

	lmac_error_event_table =
		le32_to_cpu(lmac1->dbg_ptrs.error_event_table_ptr);
	iwl_fw_lmac1_set_alive_err_table(mvm->trans, lmac_error_event_table);

	अगर (lmac2)
		mvm->trans->dbg.lmac_error_event_table[1] =
			le32_to_cpu(lmac2->dbg_ptrs.error_event_table_ptr);

	umac_error_table = le32_to_cpu(umac->dbg_ptrs.error_info_addr) &
							~FW_ADDR_CACHE_CONTROL;

	अगर (umac_error_table) अणु
		अगर (umac_error_table >=
		    mvm->trans->cfg->min_umac_error_event_table) अणु
			iwl_fw_umac_set_alive_err_table(mvm->trans,
							umac_error_table);
		पूर्ण अन्यथा अणु
			IWL_ERR(mvm,
				"Not valid error log pointer 0x%08X for %s uCode\n",
				umac_error_table,
				(mvm->fwrt.cur_fw_img == IWL_UCODE_INIT) ?
				"Init" : "RT");
		पूर्ण
	पूर्ण

	alive_data->scd_base_addr = le32_to_cpu(lmac1->dbg_ptrs.scd_base_ptr);
	alive_data->valid = status == IWL_ALIVE_STATUS_OK;

	IWL_DEBUG_FW(mvm,
		     "Alive ucode status 0x%04x revision 0x%01X 0x%01X\n",
		     status, lmac1->ver_type, lmac1->ver_subtype);

	अगर (lmac2)
		IWL_DEBUG_FW(mvm, "Alive ucode CDB\n");

	IWL_DEBUG_FW(mvm,
		     "UMAC version: Major - 0x%x, Minor - 0x%x\n",
		     le32_to_cpu(umac->umac_major),
		     le32_to_cpu(umac->umac_minor));

	iwl_fwrt_update_fw_versions(&mvm->fwrt, lmac1, umac);

	वापस true;
पूर्ण

अटल bool iwl_रुको_init_complete(काष्ठा iwl_notअगर_रुको_data *notअगर_रुको,
				   काष्ठा iwl_rx_packet *pkt, व्योम *data)
अणु
	WARN_ON(pkt->hdr.cmd != INIT_COMPLETE_NOTIF);

	वापस true;
पूर्ण

अटल bool iwl_रुको_phy_db_entry(काष्ठा iwl_notअगर_रुको_data *notअगर_रुको,
				  काष्ठा iwl_rx_packet *pkt, व्योम *data)
अणु
	काष्ठा iwl_phy_db *phy_db = data;

	अगर (pkt->hdr.cmd != CALIB_RES_NOTIF_PHY_DB) अणु
		WARN_ON(pkt->hdr.cmd != INIT_COMPLETE_NOTIF);
		वापस true;
	पूर्ण

	WARN_ON(iwl_phy_db_set_section(phy_db, pkt));

	वापस false;
पूर्ण

अटल पूर्णांक iwl_mvm_load_ucode_रुको_alive(काष्ठा iwl_mvm *mvm,
					 क्रमागत iwl_ucode_type ucode_type)
अणु
	काष्ठा iwl_notअगरication_रुको alive_रुको;
	काष्ठा iwl_mvm_alive_data alive_data = अणुपूर्ण;
	स्थिर काष्ठा fw_img *fw;
	पूर्णांक ret;
	क्रमागत iwl_ucode_type old_type = mvm->fwrt.cur_fw_img;
	अटल स्थिर u16 alive_cmd[] = अणु UCODE_ALIVE_NTFY पूर्ण;
	bool run_in_rfसमाप्त =
		ucode_type == IWL_UCODE_INIT || iwl_mvm_has_unअगरied_ucode(mvm);

	अगर (ucode_type == IWL_UCODE_REGULAR &&
	    iwl_fw_dbg_conf_usnअगरfer(mvm->fw, FW_DBG_START_FROM_ALIVE) &&
	    !(fw_has_capa(&mvm->fw->ucode_capa,
			  IWL_UCODE_TLV_CAPA_USNIFFER_UNIFIED)))
		fw = iwl_get_ucode_image(mvm->fw, IWL_UCODE_REGULAR_USNIFFER);
	अन्यथा
		fw = iwl_get_ucode_image(mvm->fw, ucode_type);
	अगर (WARN_ON(!fw))
		वापस -EINVAL;
	iwl_fw_set_current_image(&mvm->fwrt, ucode_type);
	clear_bit(IWL_MVM_STATUS_FIRMWARE_RUNNING, &mvm->status);

	iwl_init_notअगरication_रुको(&mvm->notअगर_रुको, &alive_रुको,
				   alive_cmd, ARRAY_SIZE(alive_cmd),
				   iwl_alive_fn, &alive_data);

	/*
	 * We want to load the INIT firmware even in RFKILL
	 * For the unअगरied firmware हाल, the ucode_type is not
	 * INIT, but we still need to run it.
	 */
	ret = iwl_trans_start_fw(mvm->trans, fw, run_in_rfसमाप्त);
	अगर (ret) अणु
		iwl_fw_set_current_image(&mvm->fwrt, old_type);
		iwl_हटाओ_notअगरication(&mvm->notअगर_रुको, &alive_रुको);
		वापस ret;
	पूर्ण

	/*
	 * Some things may run in the background now, but we
	 * just रुको क्रम the ALIVE notअगरication here.
	 */
	ret = iwl_रुको_notअगरication(&mvm->notअगर_रुको, &alive_रुको,
				    MVM_UCODE_ALIVE_TIMEOUT);
	अगर (ret) अणु
		काष्ठा iwl_trans *trans = mvm->trans;

		अगर (trans->trans_cfg->device_family >=
					IWL_DEVICE_FAMILY_22000) अणु
			IWL_ERR(mvm,
				"SecBoot CPU1 Status: 0x%x, CPU2 Status: 0x%x\n",
				iwl_पढ़ो_umac_prph(trans, UMAG_SB_CPU_1_STATUS),
				iwl_पढ़ो_umac_prph(trans,
						   UMAG_SB_CPU_2_STATUS));
			IWL_ERR(mvm, "UMAC PC: 0x%x\n",
				iwl_पढ़ो_umac_prph(trans,
						   UREG_UMAC_CURRENT_PC));
			IWL_ERR(mvm, "LMAC PC: 0x%x\n",
				iwl_पढ़ो_umac_prph(trans,
						   UREG_LMAC1_CURRENT_PC));
			अगर (iwl_mvm_is_cdb_supported(mvm))
				IWL_ERR(mvm, "LMAC2 PC: 0x%x\n",
					iwl_पढ़ो_umac_prph(trans,
						UREG_LMAC2_CURRENT_PC));
		पूर्ण अन्यथा अगर (trans->trans_cfg->device_family >=
			   IWL_DEVICE_FAMILY_8000) अणु
			IWL_ERR(mvm,
				"SecBoot CPU1 Status: 0x%x, CPU2 Status: 0x%x\n",
				iwl_पढ़ो_prph(trans, SB_CPU_1_STATUS),
				iwl_पढ़ो_prph(trans, SB_CPU_2_STATUS));
		पूर्ण

		अगर (ret == -ETIMEDOUT)
			iwl_fw_dbg_error_collect(&mvm->fwrt,
						 FW_DBG_TRIGGER_ALIVE_TIMEOUT);

		iwl_fw_set_current_image(&mvm->fwrt, old_type);
		वापस ret;
	पूर्ण

	अगर (!alive_data.valid) अणु
		IWL_ERR(mvm, "Loaded ucode is not valid!\n");
		iwl_fw_set_current_image(&mvm->fwrt, old_type);
		वापस -EIO;
	पूर्ण

	ret = iwl_pnvm_load(mvm->trans, &mvm->notअगर_रुको);
	अगर (ret) अणु
		IWL_ERR(mvm, "Timeout waiting for PNVM load!\n");
		iwl_fw_set_current_image(&mvm->fwrt, old_type);
		वापस ret;
	पूर्ण

	iwl_trans_fw_alive(mvm->trans, alive_data.scd_base_addr);

	/*
	 * Note: all the queues are enabled as part of the पूर्णांकerface
	 * initialization, but in firmware restart scenarios they
	 * could be stopped, so wake them up. In firmware restart,
	 * mac80211 will have the queues stopped as well until the
	 * reconfiguration completes. During normal startup, they
	 * will be empty.
	 */

	स_रखो(&mvm->queue_info, 0, माप(mvm->queue_info));
	/*
	 * Set a 'fake' TID क्रम the command queue, since we use the
	 * hweight() of the tid_biपंचांगap as a refcount now. Not that
	 * we ever even consider the command queue as one we might
	 * want to reuse, but be safe nevertheless.
	 */
	mvm->queue_info[IWL_MVM_DQA_CMD_QUEUE].tid_biपंचांगap =
		BIT(IWL_MAX_TID_COUNT + 2);

	set_bit(IWL_MVM_STATUS_FIRMWARE_RUNNING, &mvm->status);
#अगर_घोषित CONFIG_IWLWIFI_DEBUGFS
	iwl_fw_set_dbg_rec_on(&mvm->fwrt);
#पूर्ण_अगर

	/*
	 * All the BSSes in the BSS table include the GP2 in the प्रणाली
	 * at the beacon Rx समय, this is of course no दीर्घer relevant
	 * since we are resetting the firmware.
	 * Purge all the BSS table.
	 */
	cfg80211_bss_flush(mvm->hw->wiphy);

	वापस 0;
पूर्ण

अटल पूर्णांक iwl_run_unअगरied_mvm_ucode(काष्ठा iwl_mvm *mvm)
अणु
	काष्ठा iwl_notअगरication_रुको init_रुको;
	काष्ठा iwl_nvm_access_complete_cmd nvm_complete = अणुपूर्ण;
	काष्ठा iwl_init_extended_cfg_cmd init_cfg = अणु
		.init_flags = cpu_to_le32(BIT(IWL_INIT_NVM)),
	पूर्ण;
	अटल स्थिर u16 init_complete[] = अणु
		INIT_COMPLETE_NOTIF,
	पूर्ण;
	पूर्णांक ret;

	अगर (mvm->trans->cfg->tx_with_siso_भागersity)
		init_cfg.init_flags |= cpu_to_le32(BIT(IWL_INIT_PHY));

	lockdep_निश्चित_held(&mvm->mutex);

	mvm->rfसमाप्त_safe_init_करोne = false;

	iwl_init_notअगरication_रुको(&mvm->notअगर_रुको,
				   &init_रुको,
				   init_complete,
				   ARRAY_SIZE(init_complete),
				   iwl_रुको_init_complete,
				   शून्य);

	iwl_dbg_tlv_समय_poपूर्णांक(&mvm->fwrt, IWL_FW_INI_TIME_POINT_EARLY, शून्य);

	/* Will also start the device */
	ret = iwl_mvm_load_ucode_रुको_alive(mvm, IWL_UCODE_REGULAR);
	अगर (ret) अणु
		IWL_ERR(mvm, "Failed to start RT ucode: %d\n", ret);
		जाओ error;
	पूर्ण
	iwl_dbg_tlv_समय_poपूर्णांक(&mvm->fwrt, IWL_FW_INI_TIME_POINT_AFTER_ALIVE,
			       शून्य);

	/* Send init config command to mark that we are sending NVM access
	 * commands
	 */
	ret = iwl_mvm_send_cmd_pdu(mvm, WIDE_ID(SYSTEM_GROUP,
						INIT_EXTENDED_CFG_CMD),
				   CMD_SEND_IN_RFKILL,
				   माप(init_cfg), &init_cfg);
	अगर (ret) अणु
		IWL_ERR(mvm, "Failed to run init config command: %d\n",
			ret);
		जाओ error;
	पूर्ण

	/* Load NVM to NIC अगर needed */
	अगर (mvm->nvm_file_name) अणु
		ret = iwl_पढ़ो_बाह्यal_nvm(mvm->trans, mvm->nvm_file_name,
					    mvm->nvm_sections);
		अगर (ret)
			जाओ error;
		ret = iwl_mvm_load_nvm_to_nic(mvm);
		अगर (ret)
			जाओ error;
	पूर्ण

	अगर (IWL_MVM_PARSE_NVM && !mvm->nvm_data) अणु
		ret = iwl_nvm_init(mvm);
		अगर (ret) अणु
			IWL_ERR(mvm, "Failed to read NVM: %d\n", ret);
			जाओ error;
		पूर्ण
	पूर्ण

	ret = iwl_mvm_send_cmd_pdu(mvm, WIDE_ID(REGULATORY_AND_NVM_GROUP,
						NVM_ACCESS_COMPLETE),
				   CMD_SEND_IN_RFKILL,
				   माप(nvm_complete), &nvm_complete);
	अगर (ret) अणु
		IWL_ERR(mvm, "Failed to run complete NVM access: %d\n",
			ret);
		जाओ error;
	पूर्ण

	/* We रुको क्रम the INIT complete notअगरication */
	ret = iwl_रुको_notअगरication(&mvm->notअगर_रुको, &init_रुको,
				    MVM_UCODE_ALIVE_TIMEOUT);
	अगर (ret)
		वापस ret;

	/* Read the NVM only at driver load समय, no need to करो this twice */
	अगर (!IWL_MVM_PARSE_NVM && !mvm->nvm_data) अणु
		mvm->nvm_data = iwl_get_nvm(mvm->trans, mvm->fw);
		अगर (IS_ERR(mvm->nvm_data)) अणु
			ret = PTR_ERR(mvm->nvm_data);
			mvm->nvm_data = शून्य;
			IWL_ERR(mvm, "Failed to read NVM: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	mvm->rfसमाप्त_safe_init_करोne = true;

	वापस 0;

error:
	iwl_हटाओ_notअगरication(&mvm->notअगर_रुको, &init_रुको);
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_ACPI
अटल व्योम iwl_mvm_phy_filter_init(काष्ठा iwl_mvm *mvm,
				    काष्ठा iwl_phy_specअगरic_cfg *phy_filters)
अणु
	/*
	 * TODO: पढ़ो specअगरic phy config from BIOS
	 * ACPI table क्रम this feature has not been defined yet,
	 * so क्रम now we use hardcoded values.
	 */

	अगर (IWL_MVM_PHY_FILTER_CHAIN_A) अणु
		phy_filters->filter_cfg_chain_a =
			cpu_to_le32(IWL_MVM_PHY_FILTER_CHAIN_A);
	पूर्ण
	अगर (IWL_MVM_PHY_FILTER_CHAIN_B) अणु
		phy_filters->filter_cfg_chain_b =
			cpu_to_le32(IWL_MVM_PHY_FILTER_CHAIN_B);
	पूर्ण
	अगर (IWL_MVM_PHY_FILTER_CHAIN_C) अणु
		phy_filters->filter_cfg_chain_c =
			cpu_to_le32(IWL_MVM_PHY_FILTER_CHAIN_C);
	पूर्ण
	अगर (IWL_MVM_PHY_FILTER_CHAIN_D) अणु
		phy_filters->filter_cfg_chain_d =
			cpu_to_le32(IWL_MVM_PHY_FILTER_CHAIN_D);
	पूर्ण
पूर्ण

#अन्यथा /* CONFIG_ACPI */

अटल व्योम iwl_mvm_phy_filter_init(काष्ठा iwl_mvm *mvm,
				    काष्ठा iwl_phy_specअगरic_cfg *phy_filters)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_ACPI */

अटल पूर्णांक iwl_send_phy_cfg_cmd(काष्ठा iwl_mvm *mvm)
अणु
	काष्ठा iwl_phy_cfg_cmd_v3 phy_cfg_cmd;
	क्रमागत iwl_ucode_type ucode_type = mvm->fwrt.cur_fw_img;
	काष्ठा iwl_phy_specअगरic_cfg phy_filters = अणुपूर्ण;
	u8 cmd_ver;
	माप_प्रकार cmd_size;

	अगर (iwl_mvm_has_unअगरied_ucode(mvm) &&
	    !mvm->trans->cfg->tx_with_siso_भागersity)
		वापस 0;

	अगर (mvm->trans->cfg->tx_with_siso_भागersity) अणु
		/*
		 * TODO: currently we करोn't set the antenna but letting the NIC
		 * to decide which antenna to use. This should come from BIOS.
		 */
		phy_cfg_cmd.phy_cfg =
			cpu_to_le32(FW_PHY_CFG_CHAIN_SAD_ENABLED);
	पूर्ण

	/* Set parameters */
	phy_cfg_cmd.phy_cfg = cpu_to_le32(iwl_mvm_get_phy_config(mvm));

	/* set flags extra PHY configuration flags from the device's cfg */
	phy_cfg_cmd.phy_cfg |=
		cpu_to_le32(mvm->trans->trans_cfg->extra_phy_cfg_flags);

	phy_cfg_cmd.calib_control.event_trigger =
		mvm->fw->शेष_calib[ucode_type].event_trigger;
	phy_cfg_cmd.calib_control.flow_trigger =
		mvm->fw->शेष_calib[ucode_type].flow_trigger;

	cmd_ver = iwl_fw_lookup_cmd_ver(mvm->fw, IWL_ALWAYS_LONG_GROUP,
					PHY_CONFIGURATION_CMD,
					IWL_FW_CMD_VER_UNKNOWN);
	अगर (cmd_ver == 3) अणु
		iwl_mvm_phy_filter_init(mvm, &phy_filters);
		स_नकल(&phy_cfg_cmd.phy_specअगरic_cfg, &phy_filters,
		       माप(काष्ठा iwl_phy_specअगरic_cfg));
	पूर्ण

	IWL_DEBUG_INFO(mvm, "Sending Phy CFG command: 0x%x\n",
		       phy_cfg_cmd.phy_cfg);
	cmd_size = (cmd_ver == 3) ? माप(काष्ठा iwl_phy_cfg_cmd_v3) :
				    माप(काष्ठा iwl_phy_cfg_cmd_v1);
	वापस iwl_mvm_send_cmd_pdu(mvm, PHY_CONFIGURATION_CMD, 0,
				    cmd_size, &phy_cfg_cmd);
पूर्ण

पूर्णांक iwl_run_init_mvm_ucode(काष्ठा iwl_mvm *mvm)
अणु
	काष्ठा iwl_notअगरication_रुको calib_रुको;
	अटल स्थिर u16 init_complete[] = अणु
		INIT_COMPLETE_NOTIF,
		CALIB_RES_NOTIF_PHY_DB
	पूर्ण;
	पूर्णांक ret;

	अगर (iwl_mvm_has_unअगरied_ucode(mvm))
		वापस iwl_run_unअगरied_mvm_ucode(mvm);

	lockdep_निश्चित_held(&mvm->mutex);

	mvm->rfसमाप्त_safe_init_करोne = false;

	iwl_init_notअगरication_रुको(&mvm->notअगर_रुको,
				   &calib_रुको,
				   init_complete,
				   ARRAY_SIZE(init_complete),
				   iwl_रुको_phy_db_entry,
				   mvm->phy_db);

	iwl_dbg_tlv_समय_poपूर्णांक(&mvm->fwrt, IWL_FW_INI_TIME_POINT_EARLY, शून्य);

	/* Will also start the device */
	ret = iwl_mvm_load_ucode_रुको_alive(mvm, IWL_UCODE_INIT);
	अगर (ret) अणु
		IWL_ERR(mvm, "Failed to start INIT ucode: %d\n", ret);
		जाओ हटाओ_notअगर;
	पूर्ण

	अगर (mvm->trans->trans_cfg->device_family < IWL_DEVICE_FAMILY_8000) अणु
		ret = iwl_mvm_send_bt_init_conf(mvm);
		अगर (ret)
			जाओ हटाओ_notअगर;
	पूर्ण

	/* Read the NVM only at driver load समय, no need to करो this twice */
	अगर (!mvm->nvm_data) अणु
		ret = iwl_nvm_init(mvm);
		अगर (ret) अणु
			IWL_ERR(mvm, "Failed to read NVM: %d\n", ret);
			जाओ हटाओ_notअगर;
		पूर्ण
	पूर्ण

	/* In हाल we पढ़ो the NVM from बाह्यal file, load it to the NIC */
	अगर (mvm->nvm_file_name) अणु
		ret = iwl_mvm_load_nvm_to_nic(mvm);
		अगर (ret)
			जाओ हटाओ_notअगर;
	पूर्ण

	WARN_ONCE(mvm->nvm_data->nvm_version < mvm->trans->cfg->nvm_ver,
		  "Too old NVM version (0x%0x, required = 0x%0x)",
		  mvm->nvm_data->nvm_version, mvm->trans->cfg->nvm_ver);

	/*
	 * पात after पढ़ोing the nvm in हाल RF Kill is on, we will complete
	 * the init seq later when RF समाप्त will चयन to off
	 */
	अगर (iwl_mvm_is_radio_hw_समाप्तed(mvm)) अणु
		IWL_DEBUG_RF_KILL(mvm,
				  "jump over all phy activities due to RF kill\n");
		जाओ हटाओ_notअगर;
	पूर्ण

	mvm->rfसमाप्त_safe_init_करोne = true;

	/* Send TX valid antennas beक्रमe triggering calibrations */
	ret = iwl_send_tx_ant_cfg(mvm, iwl_mvm_get_valid_tx_ant(mvm));
	अगर (ret)
		जाओ हटाओ_notअगर;

	ret = iwl_send_phy_cfg_cmd(mvm);
	अगर (ret) अणु
		IWL_ERR(mvm, "Failed to run INIT calibrations: %d\n",
			ret);
		जाओ हटाओ_notअगर;
	पूर्ण

	/*
	 * Some things may run in the background now, but we
	 * just रुको क्रम the calibration complete notअगरication.
	 */
	ret = iwl_रुको_notअगरication(&mvm->notअगर_रुको, &calib_रुको,
				    MVM_UCODE_CALIB_TIMEOUT);
	अगर (!ret)
		जाओ out;

	अगर (iwl_mvm_is_radio_hw_समाप्तed(mvm)) अणु
		IWL_DEBUG_RF_KILL(mvm, "RFKILL while calibrating.\n");
		ret = 0;
	पूर्ण अन्यथा अणु
		IWL_ERR(mvm, "Failed to run INIT calibrations: %d\n",
			ret);
	पूर्ण

	जाओ out;

हटाओ_notअगर:
	iwl_हटाओ_notअगरication(&mvm->notअगर_रुको, &calib_रुको);
out:
	mvm->rfसमाप्त_safe_init_करोne = false;
	अगर (iwlmvm_mod_params.init_dbg && !mvm->nvm_data) अणु
		/* we want to debug INIT and we have no NVM - fake */
		mvm->nvm_data = kzalloc(माप(काष्ठा iwl_nvm_data) +
					माप(काष्ठा ieee80211_channel) +
					माप(काष्ठा ieee80211_rate),
					GFP_KERNEL);
		अगर (!mvm->nvm_data)
			वापस -ENOMEM;
		mvm->nvm_data->bands[0].channels = mvm->nvm_data->channels;
		mvm->nvm_data->bands[0].n_channels = 1;
		mvm->nvm_data->bands[0].n_bitrates = 1;
		mvm->nvm_data->bands[0].bitrates =
			(व्योम *)mvm->nvm_data->channels + 1;
		mvm->nvm_data->bands[0].bitrates->hw_value = 10;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक iwl_mvm_config_ltr(काष्ठा iwl_mvm *mvm)
अणु
	काष्ठा iwl_ltr_config_cmd cmd = अणु
		.flags = cpu_to_le32(LTR_CFG_FLAG_FEATURE_ENABLE),
	पूर्ण;

	अगर (!mvm->trans->ltr_enabled)
		वापस 0;

	वापस iwl_mvm_send_cmd_pdu(mvm, LTR_CONFIG, 0,
				    माप(cmd), &cmd);
पूर्ण

#अगर_घोषित CONFIG_ACPI
पूर्णांक iwl_mvm_sar_select_profile(काष्ठा iwl_mvm *mvm, पूर्णांक prof_a, पूर्णांक prof_b)
अणु
	काष्ठा iwl_dev_tx_घातer_cmd cmd = अणु
		.common.set_mode = cpu_to_le32(IWL_TX_POWER_MODE_SET_CHAINS),
	पूर्ण;
	__le16 *per_chain;
	पूर्णांक ret;
	u16 len = 0;
	u32 n_subbands;
	u8 cmd_ver = iwl_fw_lookup_cmd_ver(mvm->fw, LONG_GROUP,
					   REDUCE_TX_POWER_CMD,
					   IWL_FW_CMD_VER_UNKNOWN);

	अगर (cmd_ver == 6) अणु
		len = माप(cmd.v6);
		n_subbands = IWL_NUM_SUB_BANDS_V2;
		per_chain = cmd.v6.per_chain[0][0];
	पूर्ण अन्यथा अगर (fw_has_api(&mvm->fw->ucode_capa,
			      IWL_UCODE_TLV_API_REDUCE_TX_POWER)) अणु
		len = माप(cmd.v5);
		n_subbands = IWL_NUM_SUB_BANDS_V1;
		per_chain = cmd.v5.per_chain[0][0];
	पूर्ण अन्यथा अगर (fw_has_capa(&mvm->fw->ucode_capa,
			       IWL_UCODE_TLV_CAPA_TX_POWER_ACK)) अणु
		len = माप(cmd.v4);
		n_subbands = IWL_NUM_SUB_BANDS_V1;
		per_chain = cmd.v4.per_chain[0][0];
	पूर्ण अन्यथा अणु
		len = माप(cmd.v3);
		n_subbands = IWL_NUM_SUB_BANDS_V1;
		per_chain = cmd.v3.per_chain[0][0];
	पूर्ण

	/* all काष्ठाs have the same common part, add it */
	len += माप(cmd.common);

	ret = iwl_sar_select_profile(&mvm->fwrt, per_chain, ACPI_SAR_NUM_TABLES,
				     n_subbands, prof_a, prof_b);

	/* वापस on error or अगर the profile is disabled (positive number) */
	अगर (ret)
		वापस ret;

	IWL_DEBUG_RADIO(mvm, "Sending REDUCE_TX_POWER_CMD per chain\n");
	वापस iwl_mvm_send_cmd_pdu(mvm, REDUCE_TX_POWER_CMD, 0, len, &cmd);
पूर्ण

पूर्णांक iwl_mvm_get_sar_geo_profile(काष्ठा iwl_mvm *mvm)
अणु
	जोड़ iwl_geo_tx_घातer_profiles_cmd geo_tx_cmd;
	काष्ठा iwl_geo_tx_घातer_profiles_resp *resp;
	u16 len;
	पूर्णांक ret;
	काष्ठा iwl_host_cmd cmd;
	u8 cmd_ver = iwl_fw_lookup_cmd_ver(mvm->fw, PHY_OPS_GROUP,
					   GEO_TX_POWER_LIMIT,
					   IWL_FW_CMD_VER_UNKNOWN);

	/* the ops field is at the same spot क्रम all versions, so set in v1 */
	geo_tx_cmd.v1.ops =
		cpu_to_le32(IWL_PER_CHAIN_OFFSET_GET_CURRENT_TABLE);

	अगर (cmd_ver == 3)
		len = माप(geo_tx_cmd.v3);
	अन्यथा अगर (fw_has_api(&mvm->fwrt.fw->ucode_capa,
			    IWL_UCODE_TLV_API_SAR_TABLE_VER))
		len = माप(geo_tx_cmd.v2);
	अन्यथा
		len = माप(geo_tx_cmd.v1);

	अगर (!iwl_sar_geo_support(&mvm->fwrt))
		वापस -EOPNOTSUPP;

	cmd = (काष्ठा iwl_host_cmd)अणु
		.id =  WIDE_ID(PHY_OPS_GROUP, GEO_TX_POWER_LIMIT),
		.len = अणु len, पूर्ण,
		.flags = CMD_WANT_SKB,
		.data = अणु &geo_tx_cmd पूर्ण,
	पूर्ण;

	ret = iwl_mvm_send_cmd(mvm, &cmd);
	अगर (ret) अणु
		IWL_ERR(mvm, "Failed to get geographic profile info %d\n", ret);
		वापस ret;
	पूर्ण

	resp = (व्योम *)cmd.resp_pkt->data;
	ret = le32_to_cpu(resp->profile_idx);

	अगर (WARN_ON(ret > ACPI_NUM_GEO_PROखाताS))
		ret = -EIO;

	iwl_मुक्त_resp(&cmd);
	वापस ret;
पूर्ण

अटल पूर्णांक iwl_mvm_sar_geo_init(काष्ठा iwl_mvm *mvm)
अणु
	जोड़ iwl_geo_tx_घातer_profiles_cmd cmd;
	u16 len;
	u32 n_bands;
	पूर्णांक ret;
	u8 cmd_ver = iwl_fw_lookup_cmd_ver(mvm->fw, PHY_OPS_GROUP,
					   GEO_TX_POWER_LIMIT,
					   IWL_FW_CMD_VER_UNKNOWN);

	BUILD_BUG_ON(दुरत्व(काष्ठा iwl_geo_tx_घातer_profiles_cmd_v1, ops) !=
		     दुरत्व(काष्ठा iwl_geo_tx_घातer_profiles_cmd_v2, ops) ||
		     दुरत्व(काष्ठा iwl_geo_tx_घातer_profiles_cmd_v2, ops) !=
		     दुरत्व(काष्ठा iwl_geo_tx_घातer_profiles_cmd_v3, ops));
	/* the ops field is at the same spot क्रम all versions, so set in v1 */
	cmd.v1.ops = cpu_to_le32(IWL_PER_CHAIN_OFFSET_SET_TABLES);

	अगर (cmd_ver == 3) अणु
		len = माप(cmd.v3);
		n_bands = ARRAY_SIZE(cmd.v3.table[0]);
	पूर्ण अन्यथा अगर (fw_has_api(&mvm->fwrt.fw->ucode_capa,
			      IWL_UCODE_TLV_API_SAR_TABLE_VER)) अणु
		len = माप(cmd.v2);
		n_bands = ARRAY_SIZE(cmd.v2.table[0]);
	पूर्ण अन्यथा अणु
		len = माप(cmd.v1);
		n_bands = ARRAY_SIZE(cmd.v1.table[0]);
	पूर्ण

	BUILD_BUG_ON(दुरत्व(काष्ठा iwl_geo_tx_घातer_profiles_cmd_v1, table) !=
		     दुरत्व(काष्ठा iwl_geo_tx_घातer_profiles_cmd_v2, table) ||
		     दुरत्व(काष्ठा iwl_geo_tx_घातer_profiles_cmd_v2, table) !=
		     दुरत्व(काष्ठा iwl_geo_tx_घातer_profiles_cmd_v3, table));
	/* the table is at the same position क्रम all versions, so set use v1 */
	ret = iwl_sar_geo_init(&mvm->fwrt, &cmd.v1.table[0][0], n_bands);

	/*
	 * It is a valid scenario to not support SAR, or miss wgds table,
	 * but in that हाल there is no need to send the command.
	 */
	अगर (ret)
		वापस 0;

	/*
	 * Set the revision on versions that contain it.
	 * This must be करोne after calling iwl_sar_geo_init().
	 */
	अगर (cmd_ver == 3)
		cmd.v3.table_revision = cpu_to_le32(mvm->fwrt.geo_rev);
	अन्यथा अगर (fw_has_api(&mvm->fwrt.fw->ucode_capa,
			    IWL_UCODE_TLV_API_SAR_TABLE_VER))
		cmd.v2.table_revision = cpu_to_le32(mvm->fwrt.geo_rev);

	वापस iwl_mvm_send_cmd_pdu(mvm,
				    WIDE_ID(PHY_OPS_GROUP, GEO_TX_POWER_LIMIT),
				    0, len, &cmd);
पूर्ण

अटल पूर्णांक iwl_mvm_get_ppag_table(काष्ठा iwl_mvm *mvm)
अणु
	जोड़ acpi_object *wअगरi_pkg, *data, *flags;
	पूर्णांक i, j, ret, tbl_rev, num_sub_bands;
	पूर्णांक idx = 2;
	s8 *gain;

	/*
	 * The 'flags' field is the same in v1 and in v2 so we can just
	 * use v1 to access it.
	 */
	mvm->fwrt.ppag_table.v1.flags = cpu_to_le32(0);

	data = iwl_acpi_get_object(mvm->dev, ACPI_PPAG_METHOD);
	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	/* try to पढ़ो ppag table rev 2 or 1 (both have the same data size) */
	wअगरi_pkg = iwl_acpi_get_wअगरi_pkg(mvm->dev, data,
					 ACPI_PPAG_WIFI_DATA_SIZE_V2, &tbl_rev);
	अगर (!IS_ERR(wअगरi_pkg)) अणु
		अगर (tbl_rev == 1 || tbl_rev == 2) अणु
			num_sub_bands = IWL_NUM_SUB_BANDS_V2;
			gain = mvm->fwrt.ppag_table.v2.gain[0];
			mvm->fwrt.ppag_ver = tbl_rev;
			IWL_DEBUG_RADIO(mvm,
					"Reading PPAG table v2 (tbl_rev=%d)\n",
					tbl_rev);
			जाओ पढ़ो_table;
		पूर्ण अन्यथा अणु
			ret = -EINVAL;
			जाओ out_मुक्त;
		पूर्ण
	पूर्ण

	/* try to पढ़ो ppag table revision 0 */
	wअगरi_pkg = iwl_acpi_get_wअगरi_pkg(mvm->dev, data,
					 ACPI_PPAG_WIFI_DATA_SIZE_V1, &tbl_rev);
	अगर (!IS_ERR(wअगरi_pkg)) अणु
		अगर (tbl_rev != 0) अणु
			ret = -EINVAL;
			जाओ out_मुक्त;
		पूर्ण
		num_sub_bands = IWL_NUM_SUB_BANDS_V1;
		gain = mvm->fwrt.ppag_table.v1.gain[0];
		mvm->fwrt.ppag_ver = 0;
		IWL_DEBUG_RADIO(mvm, "Reading PPAG table v1 (tbl_rev=0)\n");
		जाओ पढ़ो_table;
	पूर्ण
	ret = PTR_ERR(wअगरi_pkg);
	जाओ out_मुक्त;

पढ़ो_table:
	flags = &wअगरi_pkg->package.elements[1];

	अगर (flags->type != ACPI_TYPE_INTEGER) अणु
		ret = -EINVAL;
		जाओ out_मुक्त;
	पूर्ण

	mvm->fwrt.ppag_table.v1.flags = cpu_to_le32(flags->पूर्णांकeger.value &
						    IWL_PPAG_MASK);

	अगर (!mvm->fwrt.ppag_table.v1.flags) अणु
		ret = 0;
		जाओ out_मुक्त;
	पूर्ण

	/*
	 * पढ़ो, verअगरy gain values and save them पूर्णांकo the PPAG table.
	 * first sub-band (j=0) corresponds to Low-Band (2.4GHz), and the
	 * following sub-bands to High-Band (5GHz).
	 */
	क्रम (i = 0; i < IWL_NUM_CHAIN_LIMITS; i++) अणु
		क्रम (j = 0; j < num_sub_bands; j++) अणु
			जोड़ acpi_object *ent;

			ent = &wअगरi_pkg->package.elements[idx++];
			अगर (ent->type != ACPI_TYPE_INTEGER) अणु
				ret = -EINVAL;
				जाओ out_मुक्त;
			पूर्ण

			gain[i * num_sub_bands + j] = ent->पूर्णांकeger.value;

			अगर ((j == 0 &&
			     (gain[i * num_sub_bands + j] > ACPI_PPAG_MAX_LB ||
			      gain[i * num_sub_bands + j] < ACPI_PPAG_MIN_LB)) ||
			    (j != 0 &&
			     (gain[i * num_sub_bands + j] > ACPI_PPAG_MAX_HB ||
			      gain[i * num_sub_bands + j] < ACPI_PPAG_MIN_HB))) अणु
				mvm->fwrt.ppag_table.v1.flags = cpu_to_le32(0);
				ret = -EINVAL;
				जाओ out_मुक्त;
			पूर्ण
		पूर्ण
	पूर्ण

	ret = 0;
out_मुक्त:
	kमुक्त(data);
	वापस ret;
पूर्ण

पूर्णांक iwl_mvm_ppag_send_cmd(काष्ठा iwl_mvm *mvm)
अणु
	u8 cmd_ver;
	पूर्णांक i, j, ret, num_sub_bands, cmd_size;
	s8 *gain;

	अगर (!fw_has_capa(&mvm->fw->ucode_capa, IWL_UCODE_TLV_CAPA_SET_PPAG)) अणु
		IWL_DEBUG_RADIO(mvm,
				"PPAG capability not supported by FW, command not sent.\n");
		वापस 0;
	पूर्ण
	अगर (!mvm->fwrt.ppag_table.v1.flags) अणु
		IWL_DEBUG_RADIO(mvm, "PPAG not enabled, command not sent.\n");
		वापस 0;
	पूर्ण

	cmd_ver = iwl_fw_lookup_cmd_ver(mvm->fw, PHY_OPS_GROUP,
					PER_PLATFORM_ANT_GAIN_CMD,
					IWL_FW_CMD_VER_UNKNOWN);
	अगर (cmd_ver == 1) अणु
		num_sub_bands = IWL_NUM_SUB_BANDS_V1;
		gain = mvm->fwrt.ppag_table.v1.gain[0];
		cmd_size = माप(mvm->fwrt.ppag_table.v1);
		अगर (mvm->fwrt.ppag_ver == 1 || mvm->fwrt.ppag_ver == 2) अणु
			IWL_DEBUG_RADIO(mvm,
					"PPAG table rev is %d but FW supports v1, sending truncated table\n",
					mvm->fwrt.ppag_ver);
			mvm->fwrt.ppag_table.v1.flags &=
				cpu_to_le32(IWL_PPAG_ETSI_MASK);
		पूर्ण
	पूर्ण अन्यथा अगर (cmd_ver == 2 || cmd_ver == 3) अणु
		num_sub_bands = IWL_NUM_SUB_BANDS_V2;
		gain = mvm->fwrt.ppag_table.v2.gain[0];
		cmd_size = माप(mvm->fwrt.ppag_table.v2);
		अगर (mvm->fwrt.ppag_ver == 0) अणु
			IWL_DEBUG_RADIO(mvm,
					"PPAG table is v1 but FW supports v2, sending padded table\n");
		पूर्ण अन्यथा अगर (cmd_ver == 2 && mvm->fwrt.ppag_ver == 2) अणु
			IWL_DEBUG_RADIO(mvm,
					"PPAG table is v3 but FW supports v2, sending partial bitmap.\n");
			mvm->fwrt.ppag_table.v1.flags &=
				cpu_to_le32(IWL_PPAG_ETSI_MASK);
		पूर्ण
	पूर्ण अन्यथा अणु
		IWL_DEBUG_RADIO(mvm, "Unsupported PPAG command version\n");
		वापस 0;
	पूर्ण

	क्रम (i = 0; i < IWL_NUM_CHAIN_LIMITS; i++) अणु
		क्रम (j = 0; j < num_sub_bands; j++) अणु
			IWL_DEBUG_RADIO(mvm,
					"PPAG table: chain[%d] band[%d]: gain = %d\n",
					i, j, gain[i * num_sub_bands + j]);
		पूर्ण
	पूर्ण
	IWL_DEBUG_RADIO(mvm, "Sending PER_PLATFORM_ANT_GAIN_CMD\n");
	ret = iwl_mvm_send_cmd_pdu(mvm, WIDE_ID(PHY_OPS_GROUP,
						PER_PLATFORM_ANT_GAIN_CMD),
				   0, cmd_size, &mvm->fwrt.ppag_table);
	अगर (ret < 0)
		IWL_ERR(mvm, "failed to send PER_PLATFORM_ANT_GAIN_CMD (%d)\n",
			ret);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा dmi_प्रणाली_id dmi_ppag_approved_list[] = अणु
	अणु .ident = "HP",
	  .matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "HP"),
		पूर्ण,
	पूर्ण,
	अणु .ident = "SAMSUNG",
	  .matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "SAMSUNG ELECTRONICS CO., LTD"),
		पूर्ण,
	पूर्ण,
	अणु .ident = "MSFT",
	  .matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Microsoft Corporation"),
		पूर्ण,
	पूर्ण,
	अणु .ident = "ASUS",
	  .matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "ASUSTek COMPUTER INC."),
		पूर्ण,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक iwl_mvm_ppag_init(काष्ठा iwl_mvm *mvm)
अणु
	पूर्णांक ret;

	ret = iwl_mvm_get_ppag_table(mvm);
	अगर (ret < 0) अणु
		IWL_DEBUG_RADIO(mvm,
				"PPAG BIOS table invalid or unavailable. (%d)\n",
				ret);
		वापस 0;
	पूर्ण

	अगर (!dmi_check_प्रणाली(dmi_ppag_approved_list)) अणु
		IWL_DEBUG_RADIO(mvm,
				"System vendor '%s' is not in the approved list, disabling PPAG.\n",
				dmi_get_प्रणाली_info(DMI_SYS_VENDOR));
		mvm->fwrt.ppag_table.v1.flags = cpu_to_le32(0);
		वापस 0;
	पूर्ण

	वापस iwl_mvm_ppag_send_cmd(mvm);
पूर्ण

अटल व्योम iwl_mvm_tas_init(काष्ठा iwl_mvm *mvm)
अणु
	पूर्णांक ret;
	काष्ठा iwl_tas_config_cmd cmd = अणुपूर्ण;
	पूर्णांक list_size;

	BUILD_BUG_ON(ARRAY_SIZE(cmd.block_list_array) <
		     APCI_WTAS_BLACK_LIST_MAX);

	अगर (!fw_has_capa(&mvm->fw->ucode_capa, IWL_UCODE_TLV_CAPA_TAS_CFG)) अणु
		IWL_DEBUG_RADIO(mvm, "TAS not enabled in FW\n");
		वापस;
	पूर्ण

	ret = iwl_acpi_get_tas(&mvm->fwrt, cmd.block_list_array, &list_size);
	अगर (ret < 0) अणु
		IWL_DEBUG_RADIO(mvm,
				"TAS table invalid or unavailable. (%d)\n",
				ret);
		वापस;
	पूर्ण

	अगर (list_size < 0)
		वापस;

	/* list size अगर TAS enabled can only be non-negative */
	cmd.block_list_size = cpu_to_le32((u32)list_size);

	ret = iwl_mvm_send_cmd_pdu(mvm, WIDE_ID(REGULATORY_AND_NVM_GROUP,
						TAS_CONFIG),
				   0, माप(cmd), &cmd);
	अगर (ret < 0)
		IWL_DEBUG_RADIO(mvm, "failed to send TAS_CONFIG (%d)\n", ret);
पूर्ण

अटल u8 iwl_mvm_eval_dsm_rfi(काष्ठा iwl_mvm *mvm)
अणु
	u8 value;
	पूर्णांक ret = iwl_acpi_get_dsm_u8((&mvm->fwrt)->dev, 0, DSM_RFI_FUNC_ENABLE,
				      &iwl_rfi_guid, &value);

	अगर (ret < 0) अणु
		IWL_DEBUG_RADIO(mvm, "Failed to get DSM RFI, ret=%d\n", ret);

	पूर्ण अन्यथा अगर (value >= DSM_VALUE_RFI_MAX) अणु
		IWL_DEBUG_RADIO(mvm, "DSM RFI got invalid value, ret=%d\n",
				value);

	पूर्ण अन्यथा अगर (value == DSM_VALUE_RFI_ENABLE) अणु
		IWL_DEBUG_RADIO(mvm, "DSM RFI is evaluated to enable\n");
		वापस DSM_VALUE_RFI_ENABLE;
	पूर्ण

	IWL_DEBUG_RADIO(mvm, "DSM RFI is disabled\n");

	/* शेष behaviour is disabled */
	वापस DSM_VALUE_RFI_DISABLE;
पूर्ण

अटल व्योम iwl_mvm_lari_cfg(काष्ठा iwl_mvm *mvm)
अणु
	पूर्णांक cmd_ret;
	काष्ठा iwl_lari_config_change_cmd_v3 cmd = अणुपूर्ण;

	cmd.config_biपंचांगap = iwl_acpi_get_lari_config_biपंचांगap(&mvm->fwrt);

	/* apply more config masks here */

	अगर (cmd.config_biपंचांगap) अणु
		माप_प्रकार cmd_size;
		u8 cmd_ver = iwl_fw_lookup_cmd_ver(mvm->fw,
						   REGULATORY_AND_NVM_GROUP,
						   LARI_CONFIG_CHANGE, 1);
		अगर (cmd_ver == 3)
			cmd_size = माप(काष्ठा iwl_lari_config_change_cmd_v3);
		अन्यथा अगर (cmd_ver == 2)
			cmd_size = माप(काष्ठा iwl_lari_config_change_cmd_v2);
		अन्यथा
			cmd_size = माप(काष्ठा iwl_lari_config_change_cmd_v1);

		IWL_DEBUG_RADIO(mvm,
				"sending LARI_CONFIG_CHANGE, config_bitmap=0x%x\n",
				le32_to_cpu(cmd.config_biपंचांगap));
		cmd_ret = iwl_mvm_send_cmd_pdu(mvm,
					       WIDE_ID(REGULATORY_AND_NVM_GROUP,
						       LARI_CONFIG_CHANGE),
					       0, cmd_size, &cmd);
		अगर (cmd_ret < 0)
			IWL_DEBUG_RADIO(mvm,
					"Failed to send LARI_CONFIG_CHANGE (%d)\n",
					cmd_ret);
	पूर्ण
पूर्ण
#अन्यथा /* CONFIG_ACPI */

अंतरभूत पूर्णांक iwl_mvm_sar_select_profile(काष्ठा iwl_mvm *mvm,
				      पूर्णांक prof_a, पूर्णांक prof_b)
अणु
	वापस -ENOENT;
पूर्ण

अंतरभूत पूर्णांक iwl_mvm_get_sar_geo_profile(काष्ठा iwl_mvm *mvm)
अणु
	वापस -ENOENT;
पूर्ण

अटल पूर्णांक iwl_mvm_sar_geo_init(काष्ठा iwl_mvm *mvm)
अणु
	वापस 0;
पूर्ण

पूर्णांक iwl_mvm_ppag_send_cmd(काष्ठा iwl_mvm *mvm)
अणु
	वापस -ENOENT;
पूर्ण

अटल पूर्णांक iwl_mvm_ppag_init(काष्ठा iwl_mvm *mvm)
अणु
	वापस 0;
पूर्ण

अटल व्योम iwl_mvm_tas_init(काष्ठा iwl_mvm *mvm)
अणु
पूर्ण

अटल व्योम iwl_mvm_lari_cfg(काष्ठा iwl_mvm *mvm)
अणु
पूर्ण

अटल u8 iwl_mvm_eval_dsm_rfi(काष्ठा iwl_mvm *mvm)
अणु
	वापस DSM_VALUE_RFI_DISABLE;
पूर्ण
#पूर्ण_अगर /* CONFIG_ACPI */

व्योम iwl_mvm_send_recovery_cmd(काष्ठा iwl_mvm *mvm, u32 flags)
अणु
	u32 error_log_size = mvm->fw->ucode_capa.error_log_size;
	पूर्णांक ret;
	u32 resp;

	काष्ठा iwl_fw_error_recovery_cmd recovery_cmd = अणु
		.flags = cpu_to_le32(flags),
		.buf_size = 0,
	पूर्ण;
	काष्ठा iwl_host_cmd host_cmd = अणु
		.id = WIDE_ID(SYSTEM_GROUP, FW_ERROR_RECOVERY_CMD),
		.flags = CMD_WANT_SKB,
		.data = अणु&recovery_cmd, पूर्ण,
		.len = अणुमाप(recovery_cmd), पूर्ण,
	पूर्ण;

	/* no error log was defined in TLV */
	अगर (!error_log_size)
		वापस;

	अगर (flags & ERROR_RECOVERY_UPDATE_DB) अणु
		/* no buf was allocated जबतक HW reset */
		अगर (!mvm->error_recovery_buf)
			वापस;

		host_cmd.data[1] = mvm->error_recovery_buf;
		host_cmd.len[1] =  error_log_size;
		host_cmd.dataflags[1] = IWL_HCMD_DFL_NOCOPY;
		recovery_cmd.buf_size = cpu_to_le32(error_log_size);
	पूर्ण

	ret = iwl_mvm_send_cmd(mvm, &host_cmd);
	kमुक्त(mvm->error_recovery_buf);
	mvm->error_recovery_buf = शून्य;

	अगर (ret) अणु
		IWL_ERR(mvm, "Failed to send recovery cmd %d\n", ret);
		वापस;
	पूर्ण

	/* skb respond is only relevant in ERROR_RECOVERY_UPDATE_DB */
	अगर (flags & ERROR_RECOVERY_UPDATE_DB) अणु
		resp = le32_to_cpu(*(__le32 *)host_cmd.resp_pkt->data);
		अगर (resp)
			IWL_ERR(mvm,
				"Failed to send recovery cmd blob was invalid %d\n",
				resp);
	पूर्ण
पूर्ण

अटल पूर्णांक iwl_mvm_sar_init(काष्ठा iwl_mvm *mvm)
अणु
	पूर्णांक ret;

	ret = iwl_sar_get_wrds_table(&mvm->fwrt);
	अगर (ret < 0) अणु
		IWL_DEBUG_RADIO(mvm,
				"WRDS SAR BIOS table invalid or unavailable. (%d)\n",
				ret);
		/*
		 * If not available, करोn't fail and don't bother with EWRD.
		 * Return 1 to tell that we can't use WGDS either.
		 */
		वापस 1;
	पूर्ण

	ret = iwl_sar_get_ewrd_table(&mvm->fwrt);
	/* अगर EWRD is not available, we can still use WRDS, so करोn't fail */
	अगर (ret < 0)
		IWL_DEBUG_RADIO(mvm,
				"EWRD SAR BIOS table invalid or unavailable. (%d)\n",
				ret);

	वापस iwl_mvm_sar_select_profile(mvm, 1, 1);
पूर्ण

अटल पूर्णांक iwl_mvm_load_rt_fw(काष्ठा iwl_mvm *mvm)
अणु
	पूर्णांक ret;

	अगर (iwl_mvm_has_unअगरied_ucode(mvm))
		वापस iwl_run_unअगरied_mvm_ucode(mvm);

	WARN_ON(!mvm->nvm_data);
	ret = iwl_run_init_mvm_ucode(mvm);

	अगर (ret) अणु
		IWL_ERR(mvm, "Failed to run INIT ucode: %d\n", ret);

		अगर (iwlmvm_mod_params.init_dbg)
			वापस 0;
		वापस ret;
	पूर्ण

	iwl_fw_dbg_stop_sync(&mvm->fwrt);
	iwl_trans_stop_device(mvm->trans);
	ret = iwl_trans_start_hw(mvm->trans);
	अगर (ret)
		वापस ret;

	mvm->rfसमाप्त_safe_init_करोne = false;
	ret = iwl_mvm_load_ucode_रुको_alive(mvm, IWL_UCODE_REGULAR);
	अगर (ret)
		वापस ret;

	mvm->rfसमाप्त_safe_init_करोne = true;

	iwl_dbg_tlv_समय_poपूर्णांक(&mvm->fwrt, IWL_FW_INI_TIME_POINT_AFTER_ALIVE,
			       शून्य);

	वापस iwl_init_paging(&mvm->fwrt, mvm->fwrt.cur_fw_img);
पूर्ण

पूर्णांक iwl_mvm_up(काष्ठा iwl_mvm *mvm)
अणु
	पूर्णांक ret, i;
	काष्ठा ieee80211_channel *chan;
	काष्ठा cfg80211_chan_def chandef;
	काष्ठा ieee80211_supported_band *sband = शून्य;

	lockdep_निश्चित_held(&mvm->mutex);

	ret = iwl_trans_start_hw(mvm->trans);
	अगर (ret)
		वापस ret;

	ret = iwl_mvm_load_rt_fw(mvm);
	अगर (ret) अणु
		IWL_ERR(mvm, "Failed to start RT ucode: %d\n", ret);
		अगर (ret != -ERFKILL)
			iwl_fw_dbg_error_collect(&mvm->fwrt,
						 FW_DBG_TRIGGER_DRIVER);
		जाओ error;
	पूर्ण

	iwl_get_shared_mem_conf(&mvm->fwrt);

	ret = iwl_mvm_sf_update(mvm, शून्य, false);
	अगर (ret)
		IWL_ERR(mvm, "Failed to initialize Smart Fifo\n");

	अगर (!iwl_trans_dbg_ini_valid(mvm->trans)) अणु
		mvm->fwrt.dump.conf = FW_DBG_INVALID;
		/* अगर we have a destination, assume EARLY START */
		अगर (mvm->fw->dbg.dest_tlv)
			mvm->fwrt.dump.conf = FW_DBG_START_FROM_ALIVE;
		iwl_fw_start_dbg_conf(&mvm->fwrt, FW_DBG_START_FROM_ALIVE);
	पूर्ण

	ret = iwl_send_tx_ant_cfg(mvm, iwl_mvm_get_valid_tx_ant(mvm));
	अगर (ret)
		जाओ error;

	अगर (!iwl_mvm_has_unअगरied_ucode(mvm)) अणु
		/* Send phy db control command and then phy db calibration */
		ret = iwl_send_phy_db_data(mvm->phy_db);
		अगर (ret)
			जाओ error;
	पूर्ण

	ret = iwl_send_phy_cfg_cmd(mvm);
	अगर (ret)
		जाओ error;

	ret = iwl_mvm_send_bt_init_conf(mvm);
	अगर (ret)
		जाओ error;

	अगर (fw_has_capa(&mvm->fw->ucode_capa,
			IWL_UCODE_TLV_CAPA_SOC_LATENCY_SUPPORT)) अणु
		ret = iwl_set_soc_latency(&mvm->fwrt);
		अगर (ret)
			जाओ error;
	पूर्ण

	/* Init RSS configuration */
	ret = iwl_configure_rxq(&mvm->fwrt);
	अगर (ret)
		जाओ error;

	अगर (iwl_mvm_has_new_rx_api(mvm)) अणु
		ret = iwl_send_rss_cfg_cmd(mvm);
		अगर (ret) अणु
			IWL_ERR(mvm, "Failed to configure RSS queues: %d\n",
				ret);
			जाओ error;
		पूर्ण
	पूर्ण

	/* init the fw <-> mac80211 STA mapping */
	क्रम (i = 0; i < mvm->fw->ucode_capa.num_stations; i++)
		RCU_INIT_POINTER(mvm->fw_id_to_mac_id[i], शून्य);

	mvm->tdls_cs.peer.sta_id = IWL_MVM_INVALID_STA;

	/* reset quota debouncing buffer - 0xff will yield invalid data */
	स_रखो(&mvm->last_quota_cmd, 0xff, माप(mvm->last_quota_cmd));

	अगर (fw_has_capa(&mvm->fw->ucode_capa, IWL_UCODE_TLV_CAPA_DQA_SUPPORT)) अणु
		ret = iwl_mvm_send_dqa_cmd(mvm);
		अगर (ret)
			जाओ error;
	पूर्ण

	/*
	 * Add auxiliary station क्रम scanning.
	 * Newer versions of this command implies that the fw uses
	 * पूर्णांकernal aux station क्रम all aux activities that करोn't
	 * requires a dedicated data queue.
	 */
	अगर (iwl_fw_lookup_cmd_ver(mvm->fw, LONG_GROUP,
				  ADD_STA,
				  0) < 12) अणु
		 /*
		  * In old version the aux station uses mac id like other
		  * station and not lmac id
		  */
		ret = iwl_mvm_add_aux_sta(mvm, MAC_INDEX_AUX);
		अगर (ret)
			जाओ error;
	पूर्ण

	/* Add all the PHY contexts */
	i = 0;
	जबतक (!sband && i < NUM_NL80211_BANDS)
		sband = mvm->hw->wiphy->bands[i++];

	अगर (WARN_ON_ONCE(!sband))
		जाओ error;

	chan = &sband->channels[0];

	cfg80211_chandef_create(&chandef, chan, NL80211_CHAN_NO_HT);
	क्रम (i = 0; i < NUM_PHY_CTX; i++) अणु
		/*
		 * The channel used here isn't relevant as it's
		 * going to be overwritten in the other flows.
		 * For now use the first channel we have.
		 */
		ret = iwl_mvm_phy_ctxt_add(mvm, &mvm->phy_ctxts[i],
					   &chandef, 1, 1);
		अगर (ret)
			जाओ error;
	पूर्ण

	अगर (iwl_mvm_is_tt_in_fw(mvm)) अणु
		/* in order to give the responsibility of ct-समाप्त and
		 * TX backoff to FW we need to send empty temperature reporting
		 * cmd during init समय
		 */
		iwl_mvm_send_temp_report_ths_cmd(mvm);
	पूर्ण अन्यथा अणु
		/* Initialize tx backoffs to the minimal possible */
		iwl_mvm_tt_tx_backoff(mvm, 0);
	पूर्ण

#अगर_घोषित CONFIG_THERMAL
	/* TODO: पढ़ो the budget from BIOS / Platक्रमm NVM */

	/*
	 * In हाल there is no budget from BIOS / Platक्रमm NVM the शेष
	 * budget should be 2000mW (cooling state 0).
	 */
	अगर (iwl_mvm_is_ctdp_supported(mvm)) अणु
		ret = iwl_mvm_ctdp_command(mvm, CTDP_CMD_OPERATION_START,
					   mvm->cooling_dev.cur_state);
		अगर (ret)
			जाओ error;
	पूर्ण
#पूर्ण_अगर

	अगर (!fw_has_capa(&mvm->fw->ucode_capa, IWL_UCODE_TLV_CAPA_SET_LTR_GEN2))
		WARN_ON(iwl_mvm_config_ltr(mvm));

	ret = iwl_mvm_घातer_update_device(mvm);
	अगर (ret)
		जाओ error;

	iwl_mvm_lari_cfg(mvm);
	/*
	 * RTNL is not taken during Ct-समाप्त, but we करोn't need to scan/Tx
	 * anyway, so करोn't init MCC.
	 */
	अगर (!test_bit(IWL_MVM_STATUS_HW_CTKILL, &mvm->status)) अणु
		ret = iwl_mvm_init_mcc(mvm);
		अगर (ret)
			जाओ error;
	पूर्ण

	अगर (fw_has_capa(&mvm->fw->ucode_capa, IWL_UCODE_TLV_CAPA_UMAC_SCAN)) अणु
		mvm->scan_type = IWL_SCAN_TYPE_NOT_SET;
		mvm->hb_scan_type = IWL_SCAN_TYPE_NOT_SET;
		ret = iwl_mvm_config_scan(mvm);
		अगर (ret)
			जाओ error;
	पूर्ण

	अगर (test_bit(IWL_MVM_STATUS_IN_HW_RESTART, &mvm->status))
		iwl_mvm_send_recovery_cmd(mvm, ERROR_RECOVERY_UPDATE_DB);

	अगर (iwl_acpi_get_eckv(mvm->dev, &mvm->ext_घड़ी_valid))
		IWL_DEBUG_INFO(mvm, "ECKV table doesn't exist in BIOS\n");

	ret = iwl_mvm_ppag_init(mvm);
	अगर (ret)
		जाओ error;

	ret = iwl_mvm_sar_init(mvm);
	अगर (ret == 0) अणु
		ret = iwl_mvm_sar_geo_init(mvm);
	पूर्ण अन्यथा अगर (ret == -ENOENT && !iwl_sar_get_wgds_table(&mvm->fwrt)) अणु
		/*
		 * If basic SAR is not available, we check क्रम WGDS,
		 * which should *not* be available either.  If it is
		 * available, issue an error, because we can't use SAR
		 * Geo without basic SAR.
		 */
		IWL_ERR(mvm, "BIOS contains WGDS but no WRDS\n");
	पूर्ण

	अगर (ret < 0)
		जाओ error;

	iwl_mvm_tas_init(mvm);
	iwl_mvm_leds_sync(mvm);

	iwl_mvm_fपंचांग_initiator_smooth_config(mvm);

	अगर (fw_has_capa(&mvm->fw->ucode_capa,
			IWL_UCODE_TLV_CAPA_RFIM_SUPPORT)) अणु
		अगर (iwl_mvm_eval_dsm_rfi(mvm) == DSM_VALUE_RFI_ENABLE)
			iwl_rfi_send_config_cmd(mvm, शून्य);
	पूर्ण

	IWL_DEBUG_INFO(mvm, "RT uCode started.\n");
	वापस 0;
 error:
	अगर (!iwlmvm_mod_params.init_dbg || !ret)
		iwl_mvm_stop_device(mvm);
	वापस ret;
पूर्ण

पूर्णांक iwl_mvm_load_d3_fw(काष्ठा iwl_mvm *mvm)
अणु
	पूर्णांक ret, i;

	lockdep_निश्चित_held(&mvm->mutex);

	ret = iwl_trans_start_hw(mvm->trans);
	अगर (ret)
		वापस ret;

	ret = iwl_mvm_load_ucode_रुको_alive(mvm, IWL_UCODE_WOWLAN);
	अगर (ret) अणु
		IWL_ERR(mvm, "Failed to start WoWLAN firmware: %d\n", ret);
		जाओ error;
	पूर्ण

	ret = iwl_send_tx_ant_cfg(mvm, iwl_mvm_get_valid_tx_ant(mvm));
	अगर (ret)
		जाओ error;

	/* Send phy db control command and then phy db calibration*/
	ret = iwl_send_phy_db_data(mvm->phy_db);
	अगर (ret)
		जाओ error;

	ret = iwl_send_phy_cfg_cmd(mvm);
	अगर (ret)
		जाओ error;

	/* init the fw <-> mac80211 STA mapping */
	क्रम (i = 0; i < mvm->fw->ucode_capa.num_stations; i++)
		RCU_INIT_POINTER(mvm->fw_id_to_mac_id[i], शून्य);

	अगर (iwl_fw_lookup_cmd_ver(mvm->fw, LONG_GROUP,
				  ADD_STA,
				  0) < 12) अणु
		/*
		 * Add auxiliary station क्रम scanning.
		 * Newer versions of this command implies that the fw uses
		 * पूर्णांकernal aux station क्रम all aux activities that करोn't
		 * requires a dedicated data queue.
		 * In old version the aux station uses mac id like other
		 * station and not lmac id
		 */
		ret = iwl_mvm_add_aux_sta(mvm, MAC_INDEX_AUX);
		अगर (ret)
			जाओ error;
	पूर्ण

	वापस 0;
 error:
	iwl_mvm_stop_device(mvm);
	वापस ret;
पूर्ण

व्योम iwl_mvm_rx_card_state_notअगर(काष्ठा iwl_mvm *mvm,
				 काष्ठा iwl_rx_cmd_buffer *rxb)
अणु
	काष्ठा iwl_rx_packet *pkt = rxb_addr(rxb);
	काष्ठा iwl_card_state_notअगर *card_state_notअगर = (व्योम *)pkt->data;
	u32 flags = le32_to_cpu(card_state_notअगर->flags);

	IWL_DEBUG_RF_KILL(mvm, "Card state received: HW:%s SW:%s CT:%s\n",
			  (flags & HW_CARD_DISABLED) ? "Kill" : "On",
			  (flags & SW_CARD_DISABLED) ? "Kill" : "On",
			  (flags & CT_KILL_CARD_DISABLED) ?
			  "Reached" : "Not reached");
पूर्ण

व्योम iwl_mvm_rx_mfuart_notअगर(काष्ठा iwl_mvm *mvm,
			     काष्ठा iwl_rx_cmd_buffer *rxb)
अणु
	काष्ठा iwl_rx_packet *pkt = rxb_addr(rxb);
	काष्ठा iwl_mfuart_load_notअगर *mfuart_notअगर = (व्योम *)pkt->data;

	IWL_DEBUG_INFO(mvm,
		       "MFUART: installed ver: 0x%08x, external ver: 0x%08x, status: 0x%08x, duration: 0x%08x\n",
		       le32_to_cpu(mfuart_notअगर->installed_ver),
		       le32_to_cpu(mfuart_notअगर->बाह्यal_ver),
		       le32_to_cpu(mfuart_notअगर->status),
		       le32_to_cpu(mfuart_notअगर->duration));

	अगर (iwl_rx_packet_payload_len(pkt) == माप(*mfuart_notअगर))
		IWL_DEBUG_INFO(mvm,
			       "MFUART: image size: 0x%08x\n",
			       le32_to_cpu(mfuart_notअगर->image_size));
पूर्ण
