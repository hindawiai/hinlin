<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/*
 * Copyright (C) 2012-2014, 2018-2020 Intel Corporation
 * Copyright (C) 2013-2014 Intel Mobile Communications GmbH
 * Copyright (C) 2015-2017 Intel Deutschland GmbH
 */
#समावेश <net/mac80211.h>

#समावेश "iwl-debug.h"
#समावेश "iwl-io.h"
#समावेश "iwl-prph.h"
#समावेश "iwl-csr.h"
#समावेश "mvm.h"
#समावेश "fw/api/rs.h"
#समावेश "fw/img.h"

/*
 * Will वापस 0 even अगर the cmd failed when RFKILL is निश्चितed unless
 * CMD_WANT_SKB is set in cmd->flags.
 */
पूर्णांक iwl_mvm_send_cmd(काष्ठा iwl_mvm *mvm, काष्ठा iwl_host_cmd *cmd)
अणु
	पूर्णांक ret;

#अगर defined(CONFIG_IWLWIFI_DEBUGFS) && defined(CONFIG_PM_SLEEP)
	अगर (WARN_ON(mvm->d3_test_active))
		वापस -EIO;
#पूर्ण_अगर

	/*
	 * Synchronous commands from this op-mode must hold
	 * the mutex, this ensures we करोn't try to send two
	 * (or more) synchronous commands at a समय.
	 */
	अगर (!(cmd->flags & CMD_ASYNC))
		lockdep_निश्चित_held(&mvm->mutex);

	ret = iwl_trans_send_cmd(mvm->trans, cmd);

	/*
	 * If the caller wants the SKB, then करोn't hide any problems, the
	 * caller might access the response buffer which will be शून्य अगर
	 * the command failed.
	 */
	अगर (cmd->flags & CMD_WANT_SKB)
		वापस ret;

	/*
	 * Silently ignore failures अगर RFKILL is निश्चितed or
	 * we are in suspend\लesume process
	 */
	अगर (!ret || ret == -ERFKILL || ret == -EHOSTDOWN)
		वापस 0;
	वापस ret;
पूर्ण

पूर्णांक iwl_mvm_send_cmd_pdu(काष्ठा iwl_mvm *mvm, u32 id,
			 u32 flags, u16 len, स्थिर व्योम *data)
अणु
	काष्ठा iwl_host_cmd cmd = अणु
		.id = id,
		.len = अणु len, पूर्ण,
		.data = अणु data, पूर्ण,
		.flags = flags,
	पूर्ण;

	वापस iwl_mvm_send_cmd(mvm, &cmd);
पूर्ण

/*
 * We assume that the caller set the status to the success value
 */
पूर्णांक iwl_mvm_send_cmd_status(काष्ठा iwl_mvm *mvm, काष्ठा iwl_host_cmd *cmd,
			    u32 *status)
अणु
	काष्ठा iwl_rx_packet *pkt;
	काष्ठा iwl_cmd_response *resp;
	पूर्णांक ret, resp_len;

	lockdep_निश्चित_held(&mvm->mutex);

#अगर defined(CONFIG_IWLWIFI_DEBUGFS) && defined(CONFIG_PM_SLEEP)
	अगर (WARN_ON(mvm->d3_test_active))
		वापस -EIO;
#पूर्ण_अगर

	/*
	 * Only synchronous commands can रुको क्रम status,
	 * we use WANT_SKB so the caller can't.
	 */
	अगर (WARN_ONCE(cmd->flags & (CMD_ASYNC | CMD_WANT_SKB),
		      "cmd flags %x", cmd->flags))
		वापस -EINVAL;

	cmd->flags |= CMD_WANT_SKB;

	ret = iwl_trans_send_cmd(mvm->trans, cmd);
	अगर (ret == -ERFKILL) अणु
		/*
		 * The command failed because of RFKILL, करोn't update
		 * the status, leave it as success and वापस 0.
		 */
		वापस 0;
	पूर्ण अन्यथा अगर (ret) अणु
		वापस ret;
	पूर्ण

	pkt = cmd->resp_pkt;

	resp_len = iwl_rx_packet_payload_len(pkt);
	अगर (WARN_ON_ONCE(resp_len != माप(*resp))) अणु
		ret = -EIO;
		जाओ out_मुक्त_resp;
	पूर्ण

	resp = (व्योम *)pkt->data;
	*status = le32_to_cpu(resp->status);
 out_मुक्त_resp:
	iwl_मुक्त_resp(cmd);
	वापस ret;
पूर्ण

/*
 * We assume that the caller set the status to the sucess value
 */
पूर्णांक iwl_mvm_send_cmd_pdu_status(काष्ठा iwl_mvm *mvm, u32 id, u16 len,
				स्थिर व्योम *data, u32 *status)
अणु
	काष्ठा iwl_host_cmd cmd = अणु
		.id = id,
		.len = अणु len, पूर्ण,
		.data = अणु data, पूर्ण,
	पूर्ण;

	वापस iwl_mvm_send_cmd_status(mvm, &cmd, status);
पूर्ण

#घोषणा IWL_DECLARE_RATE_INFO(r) \
	[IWL_RATE_##r##M_INDEX] = IWL_RATE_##r##M_PLCP

/*
 * Translate from fw_rate_index (IWL_RATE_XXM_INDEX) to PLCP
 */
अटल स्थिर u8 fw_rate_idx_to_plcp[IWL_RATE_COUNT] = अणु
	IWL_DECLARE_RATE_INFO(1),
	IWL_DECLARE_RATE_INFO(2),
	IWL_DECLARE_RATE_INFO(5),
	IWL_DECLARE_RATE_INFO(11),
	IWL_DECLARE_RATE_INFO(6),
	IWL_DECLARE_RATE_INFO(9),
	IWL_DECLARE_RATE_INFO(12),
	IWL_DECLARE_RATE_INFO(18),
	IWL_DECLARE_RATE_INFO(24),
	IWL_DECLARE_RATE_INFO(36),
	IWL_DECLARE_RATE_INFO(48),
	IWL_DECLARE_RATE_INFO(54),
पूर्ण;

पूर्णांक iwl_mvm_legacy_rate_to_mac80211_idx(u32 rate_n_flags,
					क्रमागत nl80211_band band)
अणु
	पूर्णांक rate = rate_n_flags & RATE_LEGACY_RATE_MSK;
	पूर्णांक idx;
	पूर्णांक band_offset = 0;

	/* Legacy rate क्रमmat, search क्रम match in table */
	अगर (band != NL80211_BAND_2GHZ)
		band_offset = IWL_FIRST_OFDM_RATE;
	क्रम (idx = band_offset; idx < IWL_RATE_COUNT_LEGACY; idx++)
		अगर (fw_rate_idx_to_plcp[idx] == rate)
			वापस idx - band_offset;

	वापस -1;
पूर्ण

u8 iwl_mvm_mac80211_idx_to_hwrate(पूर्णांक rate_idx)
अणु
	/* Get PLCP rate क्रम tx_cmd->rate_n_flags */
	वापस fw_rate_idx_to_plcp[rate_idx];
पूर्ण

u8 iwl_mvm_mac80211_ac_to_ucode_ac(क्रमागत ieee80211_ac_numbers ac)
अणु
	अटल स्थिर u8 mac80211_ac_to_ucode_ac[] = अणु
		AC_VO,
		AC_VI,
		AC_BE,
		AC_BK
	पूर्ण;

	वापस mac80211_ac_to_ucode_ac[ac];
पूर्ण

व्योम iwl_mvm_rx_fw_error(काष्ठा iwl_mvm *mvm, काष्ठा iwl_rx_cmd_buffer *rxb)
अणु
	काष्ठा iwl_rx_packet *pkt = rxb_addr(rxb);
	काष्ठा iwl_error_resp *err_resp = (व्योम *)pkt->data;

	IWL_ERR(mvm, "FW Error notification: type 0x%08X cmd_id 0x%02X\n",
		le32_to_cpu(err_resp->error_type), err_resp->cmd_id);
	IWL_ERR(mvm, "FW Error notification: seq 0x%04X service 0x%08X\n",
		le16_to_cpu(err_resp->bad_cmd_seq_num),
		le32_to_cpu(err_resp->error_service));
	IWL_ERR(mvm, "FW Error notification: timestamp 0x%016llX\n",
		le64_to_cpu(err_resp->बारtamp));
पूर्ण

/*
 * Returns the first antenna as ANT_[ABC], as defined in iwl-config.h.
 * The parameter should also be a combination of ANT_[ABC].
 */
u8 first_antenna(u8 mask)
अणु
	BUILD_BUG_ON(ANT_A != BIT(0)); /* using ffs is wrong अगर not */
	अगर (WARN_ON_ONCE(!mask)) /* ffs will वापस 0 अगर mask is zeroed */
		वापस BIT(0);
	वापस BIT(ffs(mask) - 1);
पूर्ण

/*
 * Toggles between TX antennas to send the probe request on.
 * Receives the biपंचांगask of valid TX antennas and the *index* used
 * क्रम the last TX, and वापसs the next valid *index* to use.
 * In order to set it in the tx_cmd, must करो BIT(idx).
 */
u8 iwl_mvm_next_antenna(काष्ठा iwl_mvm *mvm, u8 valid, u8 last_idx)
अणु
	u8 ind = last_idx;
	पूर्णांक i;

	क्रम (i = 0; i < MAX_ANT_NUM; i++) अणु
		ind = (ind + 1) % MAX_ANT_NUM;
		अगर (valid & BIT(ind))
			वापस ind;
	पूर्ण

	WARN_ONCE(1, "Failed to toggle between antennas 0x%x", valid);
	वापस last_idx;
पूर्ण

/*
 * Note: This काष्ठाure is पढ़ो from the device with IO accesses,
 * and the पढ़ोing alपढ़ोy करोes the endian conversion. As it is
 * पढ़ो with u32-sized accesses, any members with a dअगरferent size
 * need to be ordered correctly though!
 */
काष्ठा iwl_error_event_table_v1 अणु
	u32 valid;		/* (nonzero) valid, (0) log is empty */
	u32 error_id;		/* type of error */
	u32 pc;			/* program counter */
	u32 blink1;		/* branch link */
	u32 blink2;		/* branch link */
	u32 ilink1;		/* पूर्णांकerrupt link */
	u32 ilink2;		/* पूर्णांकerrupt link */
	u32 data1;		/* error-specअगरic data */
	u32 data2;		/* error-specअगरic data */
	u32 data3;		/* error-specअगरic data */
	u32 bcon_समय;		/* beacon समयr */
	u32 tsf_low;		/* network बारtamp function समयr */
	u32 tsf_hi;		/* network बारtamp function समयr */
	u32 gp1;		/* GP1 समयr रेजिस्टर */
	u32 gp2;		/* GP2 समयr रेजिस्टर */
	u32 gp3;		/* GP3 समयr रेजिस्टर */
	u32 ucode_ver;		/* uCode version */
	u32 hw_ver;		/* HW Silicon version */
	u32 brd_ver;		/* HW board version */
	u32 log_pc;		/* log program counter */
	u32 frame_ptr;		/* frame poपूर्णांकer */
	u32 stack_ptr;		/* stack poपूर्णांकer */
	u32 hcmd;		/* last host command header */
	u32 isr0;		/* isr status रेजिस्टर LMPM_NIC_ISR0:
				 * rxtx_flag */
	u32 isr1;		/* isr status रेजिस्टर LMPM_NIC_ISR1:
				 * host_flag */
	u32 isr2;		/* isr status रेजिस्टर LMPM_NIC_ISR2:
				 * enc_flag */
	u32 isr3;		/* isr status रेजिस्टर LMPM_NIC_ISR3:
				 * समय_flag */
	u32 isr4;		/* isr status रेजिस्टर LMPM_NIC_ISR4:
				 * wico पूर्णांकerrupt */
	u32 isr_pref;		/* isr status रेजिस्टर LMPM_NIC_PREF_STAT */
	u32 रुको_event;		/* रुको event() caller address */
	u32 l2p_control;	/* L2pControlField */
	u32 l2p_duration;	/* L2pDurationField */
	u32 l2p_mhvalid;	/* L2pMhValidBits */
	u32 l2p_addr_match;	/* L2pAddrMatchStat */
	u32 lmpm_pmg_sel;	/* indicate which घड़ीs are turned on
				 * (LMPM_PMG_SEL) */
	u32 u_बारtamp;	/* indicate when the date and समय of the
				 * compilation */
	u32 flow_handler;	/* FH पढ़ो/ग_लिखो poपूर्णांकers, RX credit */
पूर्ण __packed /* LOG_ERROR_TABLE_API_S_VER_1 */;

काष्ठा iwl_error_event_table अणु
	u32 valid;		/* (nonzero) valid, (0) log is empty */
	u32 error_id;		/* type of error */
	u32 trm_hw_status0;	/* TRM HW status */
	u32 trm_hw_status1;	/* TRM HW status */
	u32 blink2;		/* branch link */
	u32 ilink1;		/* पूर्णांकerrupt link */
	u32 ilink2;		/* पूर्णांकerrupt link */
	u32 data1;		/* error-specअगरic data */
	u32 data2;		/* error-specअगरic data */
	u32 data3;		/* error-specअगरic data */
	u32 bcon_समय;		/* beacon समयr */
	u32 tsf_low;		/* network बारtamp function समयr */
	u32 tsf_hi;		/* network बारtamp function समयr */
	u32 gp1;		/* GP1 समयr रेजिस्टर */
	u32 gp2;		/* GP2 समयr रेजिस्टर */
	u32 fw_rev_type;	/* firmware revision type */
	u32 major;		/* uCode version major */
	u32 minor;		/* uCode version minor */
	u32 hw_ver;		/* HW Silicon version */
	u32 brd_ver;		/* HW board version */
	u32 log_pc;		/* log program counter */
	u32 frame_ptr;		/* frame poपूर्णांकer */
	u32 stack_ptr;		/* stack poपूर्णांकer */
	u32 hcmd;		/* last host command header */
	u32 isr0;		/* isr status रेजिस्टर LMPM_NIC_ISR0:
				 * rxtx_flag */
	u32 isr1;		/* isr status रेजिस्टर LMPM_NIC_ISR1:
				 * host_flag */
	u32 isr2;		/* isr status रेजिस्टर LMPM_NIC_ISR2:
				 * enc_flag */
	u32 isr3;		/* isr status रेजिस्टर LMPM_NIC_ISR3:
				 * समय_flag */
	u32 isr4;		/* isr status रेजिस्टर LMPM_NIC_ISR4:
				 * wico पूर्णांकerrupt */
	u32 last_cmd_id;	/* last HCMD id handled by the firmware */
	u32 रुको_event;		/* रुको event() caller address */
	u32 l2p_control;	/* L2pControlField */
	u32 l2p_duration;	/* L2pDurationField */
	u32 l2p_mhvalid;	/* L2pMhValidBits */
	u32 l2p_addr_match;	/* L2pAddrMatchStat */
	u32 lmpm_pmg_sel;	/* indicate which घड़ीs are turned on
				 * (LMPM_PMG_SEL) */
	u32 u_बारtamp;	/* indicate when the date and समय of the
				 * compilation */
	u32 flow_handler;	/* FH पढ़ो/ग_लिखो poपूर्णांकers, RX credit */
पूर्ण __packed /* LOG_ERROR_TABLE_API_S_VER_3 */;

/*
 * UMAC error काष्ठा - relevant starting from family 8000 chip.
 * Note: This काष्ठाure is पढ़ो from the device with IO accesses,
 * and the पढ़ोing alपढ़ोy करोes the endian conversion. As it is
 * पढ़ो with u32-sized accesses, any members with a dअगरferent size
 * need to be ordered correctly though!
 */
काष्ठा iwl_umac_error_event_table अणु
	u32 valid;		/* (nonzero) valid, (0) log is empty */
	u32 error_id;		/* type of error */
	u32 blink1;		/* branch link */
	u32 blink2;		/* branch link */
	u32 ilink1;		/* पूर्णांकerrupt link */
	u32 ilink2;		/* पूर्णांकerrupt link */
	u32 data1;		/* error-specअगरic data */
	u32 data2;		/* error-specअगरic data */
	u32 data3;		/* error-specअगरic data */
	u32 umac_major;
	u32 umac_minor;
	u32 frame_poपूर्णांकer;	/* core रेजिस्टर 27*/
	u32 stack_poपूर्णांकer;	/* core रेजिस्टर 28 */
	u32 cmd_header;		/* latest host cmd sent to UMAC */
	u32 nic_isr_pref;	/* ISR status रेजिस्टर */
पूर्ण __packed;

#घोषणा ERROR_START_OFFSET  (1 * माप(u32))
#घोषणा ERROR_ELEM_SIZE     (7 * माप(u32))

अटल व्योम iwl_mvm_dump_umac_error_log(काष्ठा iwl_mvm *mvm)
अणु
	काष्ठा iwl_trans *trans = mvm->trans;
	काष्ठा iwl_umac_error_event_table table = अणुपूर्ण;
	u32 base = mvm->trans->dbg.umac_error_event_table;

	अगर (!base &&
	    !(mvm->trans->dbg.error_event_table_tlv_status &
	      IWL_ERROR_EVENT_TABLE_UMAC))
		वापस;

	iwl_trans_पढ़ो_mem_bytes(trans, base, &table, माप(table));

	अगर (table.valid)
		mvm->fwrt.dump.umac_err_id = table.error_id;

	अगर (ERROR_START_OFFSET <= table.valid * ERROR_ELEM_SIZE) अणु
		IWL_ERR(trans, "Start IWL Error Log Dump:\n");
		IWL_ERR(trans, "Status: 0x%08lX, count: %d\n",
			mvm->status, table.valid);
	पूर्ण

	IWL_ERR(mvm, "0x%08X | %s\n", table.error_id,
		iwl_fw_lookup_निश्चित_desc(table.error_id));
	IWL_ERR(mvm, "0x%08X | umac branchlink1\n", table.blink1);
	IWL_ERR(mvm, "0x%08X | umac branchlink2\n", table.blink2);
	IWL_ERR(mvm, "0x%08X | umac interruptlink1\n", table.ilink1);
	IWL_ERR(mvm, "0x%08X | umac interruptlink2\n", table.ilink2);
	IWL_ERR(mvm, "0x%08X | umac data1\n", table.data1);
	IWL_ERR(mvm, "0x%08X | umac data2\n", table.data2);
	IWL_ERR(mvm, "0x%08X | umac data3\n", table.data3);
	IWL_ERR(mvm, "0x%08X | umac major\n", table.umac_major);
	IWL_ERR(mvm, "0x%08X | umac minor\n", table.umac_minor);
	IWL_ERR(mvm, "0x%08X | frame pointer\n", table.frame_poपूर्णांकer);
	IWL_ERR(mvm, "0x%08X | stack pointer\n", table.stack_poपूर्णांकer);
	IWL_ERR(mvm, "0x%08X | last host cmd\n", table.cmd_header);
	IWL_ERR(mvm, "0x%08X | isr status reg\n", table.nic_isr_pref);
पूर्ण

अटल व्योम iwl_mvm_dump_lmac_error_log(काष्ठा iwl_mvm *mvm, u8 lmac_num)
अणु
	काष्ठा iwl_trans *trans = mvm->trans;
	काष्ठा iwl_error_event_table table = अणुपूर्ण;
	u32 val, base = mvm->trans->dbg.lmac_error_event_table[lmac_num];

	अगर (mvm->fwrt.cur_fw_img == IWL_UCODE_INIT) अणु
		अगर (!base)
			base = mvm->fw->init_errlog_ptr;
	पूर्ण अन्यथा अणु
		अगर (!base)
			base = mvm->fw->inst_errlog_ptr;
	पूर्ण

	अगर (base < 0x400000) अणु
		IWL_ERR(mvm,
			"Not valid error log pointer 0x%08X for %s uCode\n",
			base,
			(mvm->fwrt.cur_fw_img == IWL_UCODE_INIT)
			? "Init" : "RT");
		वापस;
	पूर्ण

	/* check अगर there is a HW error */
	val = iwl_trans_पढ़ो_mem32(trans, base);
	अगर (((val & ~0xf) == 0xa5a5a5a0) || ((val & ~0xf) == 0x5a5a5a50)) अणु
		पूर्णांक err;

		IWL_ERR(trans, "HW error, resetting before reading\n");

		/* reset the device */
		iwl_trans_sw_reset(trans);

		err = iwl_finish_nic_init(trans, trans->trans_cfg);
		अगर (err)
			वापस;
	पूर्ण

	iwl_trans_पढ़ो_mem_bytes(trans, base, &table, माप(table));

	अगर (table.valid)
		mvm->fwrt.dump.lmac_err_id[lmac_num] = table.error_id;

	अगर (ERROR_START_OFFSET <= table.valid * ERROR_ELEM_SIZE) अणु
		IWL_ERR(trans, "Start IWL Error Log Dump:\n");
		IWL_ERR(trans, "Status: 0x%08lX, count: %d\n",
			mvm->status, table.valid);
	पूर्ण

	/* Do not change this output - scripts rely on it */

	IWL_ERR(mvm, "Loaded firmware version: %s\n", mvm->fw->fw_version);

	IWL_ERR(mvm, "0x%08X | %-28s\n", table.error_id,
		iwl_fw_lookup_निश्चित_desc(table.error_id));
	IWL_ERR(mvm, "0x%08X | trm_hw_status0\n", table.trm_hw_status0);
	IWL_ERR(mvm, "0x%08X | trm_hw_status1\n", table.trm_hw_status1);
	IWL_ERR(mvm, "0x%08X | branchlink2\n", table.blink2);
	IWL_ERR(mvm, "0x%08X | interruptlink1\n", table.ilink1);
	IWL_ERR(mvm, "0x%08X | interruptlink2\n", table.ilink2);
	IWL_ERR(mvm, "0x%08X | data1\n", table.data1);
	IWL_ERR(mvm, "0x%08X | data2\n", table.data2);
	IWL_ERR(mvm, "0x%08X | data3\n", table.data3);
	IWL_ERR(mvm, "0x%08X | beacon time\n", table.bcon_समय);
	IWL_ERR(mvm, "0x%08X | tsf low\n", table.tsf_low);
	IWL_ERR(mvm, "0x%08X | tsf hi\n", table.tsf_hi);
	IWL_ERR(mvm, "0x%08X | time gp1\n", table.gp1);
	IWL_ERR(mvm, "0x%08X | time gp2\n", table.gp2);
	IWL_ERR(mvm, "0x%08X | uCode revision type\n", table.fw_rev_type);
	IWL_ERR(mvm, "0x%08X | uCode version major\n", table.major);
	IWL_ERR(mvm, "0x%08X | uCode version minor\n", table.minor);
	IWL_ERR(mvm, "0x%08X | hw version\n", table.hw_ver);
	IWL_ERR(mvm, "0x%08X | board version\n", table.brd_ver);
	IWL_ERR(mvm, "0x%08X | hcmd\n", table.hcmd);
	IWL_ERR(mvm, "0x%08X | isr0\n", table.isr0);
	IWL_ERR(mvm, "0x%08X | isr1\n", table.isr1);
	IWL_ERR(mvm, "0x%08X | isr2\n", table.isr2);
	IWL_ERR(mvm, "0x%08X | isr3\n", table.isr3);
	IWL_ERR(mvm, "0x%08X | isr4\n", table.isr4);
	IWL_ERR(mvm, "0x%08X | last cmd Id\n", table.last_cmd_id);
	IWL_ERR(mvm, "0x%08X | wait_event\n", table.रुको_event);
	IWL_ERR(mvm, "0x%08X | l2p_control\n", table.l2p_control);
	IWL_ERR(mvm, "0x%08X | l2p_duration\n", table.l2p_duration);
	IWL_ERR(mvm, "0x%08X | l2p_mhvalid\n", table.l2p_mhvalid);
	IWL_ERR(mvm, "0x%08X | l2p_addr_match\n", table.l2p_addr_match);
	IWL_ERR(mvm, "0x%08X | lmpm_pmg_sel\n", table.lmpm_pmg_sel);
	IWL_ERR(mvm, "0x%08X | timestamp\n", table.u_बारtamp);
	IWL_ERR(mvm, "0x%08X | flow_handler\n", table.flow_handler);
पूर्ण

अटल व्योम iwl_mvm_dump_iml_error_log(काष्ठा iwl_mvm *mvm)
अणु
	काष्ठा iwl_trans *trans = mvm->trans;
	u32 error, data1;

	अगर (mvm->trans->trans_cfg->device_family >= IWL_DEVICE_FAMILY_22000) अणु
		error = UMAG_SB_CPU_2_STATUS;
		data1 = UMAG_SB_CPU_1_STATUS;
	पूर्ण अन्यथा अगर (mvm->trans->trans_cfg->device_family >=
		   IWL_DEVICE_FAMILY_8000) अणु
		error = SB_CPU_2_STATUS;
		data1 = SB_CPU_1_STATUS;
	पूर्ण अन्यथा अणु
		वापस;
	पूर्ण

	error = iwl_पढ़ो_umac_prph(trans, UMAG_SB_CPU_2_STATUS);

	IWL_ERR(trans, "IML/ROM dump:\n");

	अगर (error & 0xFFFF0000)
		IWL_ERR(trans, "0x%04X | IML/ROM SYSASSERT\n", error >> 16);

	IWL_ERR(mvm, "0x%08X | IML/ROM error/state\n", error);
	IWL_ERR(mvm, "0x%08X | IML/ROM data1\n",
		iwl_पढ़ो_umac_prph(trans, data1));

	अगर (mvm->trans->trans_cfg->device_family >= IWL_DEVICE_FAMILY_22000)
		IWL_ERR(mvm, "0x%08X | IML/ROM WFPM_AUTH_KEY_0\n",
			iwl_पढ़ो_umac_prph(trans, SB_MODIFY_CFG_FLAG));
पूर्ण

व्योम iwl_mvm_dump_nic_error_log(काष्ठा iwl_mvm *mvm)
अणु
	अगर (!test_bit(STATUS_DEVICE_ENABLED, &mvm->trans->status)) अणु
		IWL_ERR(mvm,
			"DEVICE_ENABLED bit is not set. Aborting dump.\n");
		वापस;
	पूर्ण

	iwl_mvm_dump_lmac_error_log(mvm, 0);

	अगर (mvm->trans->dbg.lmac_error_event_table[1])
		iwl_mvm_dump_lmac_error_log(mvm, 1);

	iwl_mvm_dump_umac_error_log(mvm);

	iwl_mvm_dump_iml_error_log(mvm);

	iwl_fw_error_prपूर्णांक_fseq_regs(&mvm->fwrt);
पूर्ण

पूर्णांक iwl_mvm_reconfig_scd(काष्ठा iwl_mvm *mvm, पूर्णांक queue, पूर्णांक fअगरo, पूर्णांक sta_id,
			 पूर्णांक tid, पूर्णांक frame_limit, u16 ssn)
अणु
	काष्ठा iwl_scd_txq_cfg_cmd cmd = अणु
		.scd_queue = queue,
		.action = SCD_CFG_ENABLE_QUEUE,
		.winकरोw = frame_limit,
		.sta_id = sta_id,
		.ssn = cpu_to_le16(ssn),
		.tx_fअगरo = fअगरo,
		.aggregate = (queue >= IWL_MVM_DQA_MIN_DATA_QUEUE ||
			      queue == IWL_MVM_DQA_BSS_CLIENT_QUEUE),
		.tid = tid,
	पूर्ण;
	पूर्णांक ret;

	अगर (WARN_ON(iwl_mvm_has_new_tx_api(mvm)))
		वापस -EINVAL;

	अगर (WARN(mvm->queue_info[queue].tid_biपंचांगap == 0,
		 "Trying to reconfig unallocated queue %d\n", queue))
		वापस -ENXIO;

	IWL_DEBUG_TX_QUEUES(mvm, "Reconfig SCD for TXQ #%d\n", queue);

	ret = iwl_mvm_send_cmd_pdu(mvm, SCD_QUEUE_CFG, 0, माप(cmd), &cmd);
	WARN_ONCE(ret, "Failed to re-configure queue %d on FIFO %d, ret=%d\n",
		  queue, fअगरo, ret);

	वापस ret;
पूर्ण

/**
 * iwl_mvm_send_lq_cmd() - Send link quality command
 * @mvm: Driver data.
 * @lq: Link quality command to send.
 *
 * The link quality command is sent as the last step of station creation.
 * This is the special हाल in which init is set and we call a callback in
 * this हाल to clear the state indicating that station creation is in
 * progress.
 */
पूर्णांक iwl_mvm_send_lq_cmd(काष्ठा iwl_mvm *mvm, काष्ठा iwl_lq_cmd *lq)
अणु
	काष्ठा iwl_host_cmd cmd = अणु
		.id = LQ_CMD,
		.len = अणु माप(काष्ठा iwl_lq_cmd), पूर्ण,
		.flags = CMD_ASYNC,
		.data = अणु lq, पूर्ण,
	पूर्ण;

	अगर (WARN_ON(lq->sta_id == IWL_MVM_INVALID_STA ||
		    iwl_mvm_has_tlc_offload(mvm)))
		वापस -EINVAL;

	वापस iwl_mvm_send_cmd(mvm, &cmd);
पूर्ण

/**
 * iwl_mvm_update_smps - Get a request to change the SMPS mode
 * @mvm: Driver data.
 * @vअगर: Poपूर्णांकer to the ieee80211_vअगर काष्ठाure
 * @req_type: The part of the driver who call क्रम a change.
 * @smps_request: The request to change the SMPS mode.
 *
 * Get a requst to change the SMPS mode,
 * and change it according to all other requests in the driver.
 */
व्योम iwl_mvm_update_smps(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर,
			 क्रमागत iwl_mvm_smps_type_request req_type,
			 क्रमागत ieee80211_smps_mode smps_request)
अणु
	काष्ठा iwl_mvm_vअगर *mvmvअगर;
	क्रमागत ieee80211_smps_mode smps_mode;
	पूर्णांक i;

	lockdep_निश्चित_held(&mvm->mutex);

	/* SMPS is irrelevant क्रम NICs that करोn't have at least 2 RX antenna */
	अगर (num_of_ant(iwl_mvm_get_valid_rx_ant(mvm)) == 1)
		वापस;

	अगर (vअगर->type == NL80211_IFTYPE_AP)
		smps_mode = IEEE80211_SMPS_OFF;
	अन्यथा
		smps_mode = IEEE80211_SMPS_AUTOMATIC;

	mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	mvmvअगर->smps_requests[req_type] = smps_request;
	क्रम (i = 0; i < NUM_IWL_MVM_SMPS_REQ; i++) अणु
		अगर (mvmvअगर->smps_requests[i] == IEEE80211_SMPS_STATIC) अणु
			smps_mode = IEEE80211_SMPS_STATIC;
			अवरोध;
		पूर्ण
		अगर (mvmvअगर->smps_requests[i] == IEEE80211_SMPS_DYNAMIC)
			smps_mode = IEEE80211_SMPS_DYNAMIC;
	पूर्ण

	ieee80211_request_smps(vअगर, smps_mode);
पूर्ण

पूर्णांक iwl_mvm_request_statistics(काष्ठा iwl_mvm *mvm, bool clear)
अणु
	काष्ठा iwl_statistics_cmd scmd = अणु
		.flags = clear ? cpu_to_le32(IWL_STATISTICS_FLG_CLEAR) : 0,
	पूर्ण;
	काष्ठा iwl_host_cmd cmd = अणु
		.id = STATISTICS_CMD,
		.len[0] = माप(scmd),
		.data[0] = &scmd,
		.flags = CMD_WANT_SKB,
	पूर्ण;
	पूर्णांक ret;

	ret = iwl_mvm_send_cmd(mvm, &cmd);
	अगर (ret)
		वापस ret;

	iwl_mvm_handle_rx_statistics(mvm, cmd.resp_pkt);
	iwl_मुक्त_resp(&cmd);

	अगर (clear)
		iwl_mvm_accu_radio_stats(mvm);

	वापस 0;
पूर्ण

व्योम iwl_mvm_accu_radio_stats(काष्ठा iwl_mvm *mvm)
अणु
	mvm->accu_radio_stats.rx_समय += mvm->radio_stats.rx_समय;
	mvm->accu_radio_stats.tx_समय += mvm->radio_stats.tx_समय;
	mvm->accu_radio_stats.on_समय_rf += mvm->radio_stats.on_समय_rf;
	mvm->accu_radio_stats.on_समय_scan += mvm->radio_stats.on_समय_scan;
पूर्ण

अटल व्योम iwl_mvm_भागersity_iter(व्योम *_data, u8 *mac,
				   काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	bool *result = _data;
	पूर्णांक i;

	क्रम (i = 0; i < NUM_IWL_MVM_SMPS_REQ; i++) अणु
		अगर (mvmvअगर->smps_requests[i] == IEEE80211_SMPS_STATIC ||
		    mvmvअगर->smps_requests[i] == IEEE80211_SMPS_DYNAMIC)
			*result = false;
	पूर्ण
पूर्ण

bool iwl_mvm_rx_भागersity_allowed(काष्ठा iwl_mvm *mvm)
अणु
	bool result = true;

	lockdep_निश्चित_held(&mvm->mutex);

	अगर (num_of_ant(iwl_mvm_get_valid_rx_ant(mvm)) == 1)
		वापस false;

	अगर (mvm->cfg->rx_with_siso_भागersity)
		वापस false;

	ieee80211_iterate_active_पूर्णांकerfaces_atomic(
			mvm->hw, IEEE80211_IFACE_ITER_NORMAL,
			iwl_mvm_भागersity_iter, &result);

	वापस result;
पूर्ण

व्योम iwl_mvm_send_low_latency_cmd(काष्ठा iwl_mvm *mvm,
				  bool low_latency, u16 mac_id)
अणु
	काष्ठा iwl_mac_low_latency_cmd cmd = अणु
		.mac_id = cpu_to_le32(mac_id)
	पूर्ण;

	अगर (!fw_has_capa(&mvm->fw->ucode_capa,
			 IWL_UCODE_TLV_CAPA_DYNAMIC_QUOTA))
		वापस;

	अगर (low_latency) अणु
		/* currently we करोn't care about the direction */
		cmd.low_latency_rx = 1;
		cmd.low_latency_tx = 1;
	पूर्ण

	अगर (iwl_mvm_send_cmd_pdu(mvm, iwl_cmd_id(LOW_LATENCY_CMD,
						 MAC_CONF_GROUP, 0),
				 0, माप(cmd), &cmd))
		IWL_ERR(mvm, "Failed to send low latency command\n");
पूर्ण

पूर्णांक iwl_mvm_update_low_latency(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर,
			       bool low_latency,
			       क्रमागत iwl_mvm_low_latency_cause cause)
अणु
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	पूर्णांक res;
	bool prev;

	lockdep_निश्चित_held(&mvm->mutex);

	prev = iwl_mvm_vअगर_low_latency(mvmvअगर);
	iwl_mvm_vअगर_set_low_latency(mvmvअगर, low_latency, cause);

	low_latency = iwl_mvm_vअगर_low_latency(mvmvअगर);

	अगर (low_latency == prev)
		वापस 0;

	iwl_mvm_send_low_latency_cmd(mvm, low_latency, mvmvअगर->id);

	res = iwl_mvm_update_quotas(mvm, false, शून्य);
	अगर (res)
		वापस res;

	iwl_mvm_bt_coex_vअगर_change(mvm);

	वापस iwl_mvm_घातer_update_mac(mvm);
पूर्ण

काष्ठा iwl_mvm_low_latency_iter अणु
	bool result;
	bool result_per_band[NUM_NL80211_BANDS];
पूर्ण;

अटल व्योम iwl_mvm_ll_iter(व्योम *_data, u8 *mac, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा iwl_mvm_low_latency_iter *result = _data;
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	क्रमागत nl80211_band band;

	अगर (iwl_mvm_vअगर_low_latency(mvmvअगर)) अणु
		result->result = true;

		अगर (!mvmvअगर->phy_ctxt)
			वापस;

		band = mvmvअगर->phy_ctxt->channel->band;
		result->result_per_band[band] = true;
	पूर्ण
पूर्ण

bool iwl_mvm_low_latency(काष्ठा iwl_mvm *mvm)
अणु
	काष्ठा iwl_mvm_low_latency_iter data = अणुपूर्ण;

	ieee80211_iterate_active_पूर्णांकerfaces_atomic(
			mvm->hw, IEEE80211_IFACE_ITER_NORMAL,
			iwl_mvm_ll_iter, &data);

	वापस data.result;
पूर्ण

bool iwl_mvm_low_latency_band(काष्ठा iwl_mvm *mvm, क्रमागत nl80211_band band)
अणु
	काष्ठा iwl_mvm_low_latency_iter data = अणुपूर्ण;

	ieee80211_iterate_active_पूर्णांकerfaces_atomic(
			mvm->hw, IEEE80211_IFACE_ITER_NORMAL,
			iwl_mvm_ll_iter, &data);

	वापस data.result_per_band[band];
पूर्ण

काष्ठा iwl_bss_iter_data अणु
	काष्ठा ieee80211_vअगर *vअगर;
	bool error;
पूर्ण;

अटल व्योम iwl_mvm_bss_अगरace_iterator(व्योम *_data, u8 *mac,
				       काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा iwl_bss_iter_data *data = _data;

	अगर (vअगर->type != NL80211_IFTYPE_STATION || vअगर->p2p)
		वापस;

	अगर (data->vअगर) अणु
		data->error = true;
		वापस;
	पूर्ण

	data->vअगर = vअगर;
पूर्ण

काष्ठा ieee80211_vअगर *iwl_mvm_get_bss_vअगर(काष्ठा iwl_mvm *mvm)
अणु
	काष्ठा iwl_bss_iter_data bss_iter_data = अणुपूर्ण;

	ieee80211_iterate_active_पूर्णांकerfaces_atomic(
		mvm->hw, IEEE80211_IFACE_ITER_NORMAL,
		iwl_mvm_bss_अगरace_iterator, &bss_iter_data);

	अगर (bss_iter_data.error) अणु
		IWL_ERR(mvm, "More than one managed interface active!\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	वापस bss_iter_data.vअगर;
पूर्ण

काष्ठा iwl_bss_find_iter_data अणु
	काष्ठा ieee80211_vअगर *vअगर;
	u32 macid;
पूर्ण;

अटल व्योम iwl_mvm_bss_find_अगरace_iterator(व्योम *_data, u8 *mac,
					    काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा iwl_bss_find_iter_data *data = _data;
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);

	अगर (mvmvअगर->id == data->macid)
		data->vअगर = vअगर;
पूर्ण

काष्ठा ieee80211_vअगर *iwl_mvm_get_vअगर_by_macid(काष्ठा iwl_mvm *mvm, u32 macid)
अणु
	काष्ठा iwl_bss_find_iter_data data = अणु
		.macid = macid,
	पूर्ण;

	lockdep_निश्चित_held(&mvm->mutex);

	ieee80211_iterate_active_पूर्णांकerfaces_atomic(
		mvm->hw, IEEE80211_IFACE_ITER_NORMAL,
		iwl_mvm_bss_find_अगरace_iterator, &data);

	वापस data.vअगर;
पूर्ण

काष्ठा iwl_sta_iter_data अणु
	bool assoc;
पूर्ण;

अटल व्योम iwl_mvm_sta_अगरace_iterator(व्योम *_data, u8 *mac,
				       काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा iwl_sta_iter_data *data = _data;

	अगर (vअगर->type != NL80211_IFTYPE_STATION)
		वापस;

	अगर (vअगर->bss_conf.assoc)
		data->assoc = true;
पूर्ण

bool iwl_mvm_is_vअगर_assoc(काष्ठा iwl_mvm *mvm)
अणु
	काष्ठा iwl_sta_iter_data data = अणु
		.assoc = false,
	पूर्ण;

	ieee80211_iterate_active_पूर्णांकerfaces_atomic(mvm->hw,
						   IEEE80211_IFACE_ITER_NORMAL,
						   iwl_mvm_sta_अगरace_iterator,
						   &data);
	वापस data.assoc;
पूर्ण

अचिन्हित पूर्णांक iwl_mvm_get_wd_समयout(काष्ठा iwl_mvm *mvm,
				    काष्ठा ieee80211_vअगर *vअगर,
				    bool tdls, bool cmd_q)
अणु
	काष्ठा iwl_fw_dbg_trigger_tlv *trigger;
	काष्ठा iwl_fw_dbg_trigger_txq_समयr *txq_समयr;
	अचिन्हित पूर्णांक शेष_समयout = cmd_q ?
		IWL_DEF_WD_TIMEOUT :
		mvm->trans->trans_cfg->base_params->wd_समयout;

	अगर (!iwl_fw_dbg_trigger_enabled(mvm->fw, FW_DBG_TRIGGER_TXQ_TIMERS)) अणु
		/*
		 * We can't know when the station is asleep or awake, so we
		 * must disable the queue hang detection.
		 */
		अगर (fw_has_capa(&mvm->fw->ucode_capa,
				IWL_UCODE_TLV_CAPA_STA_PM_NOTIF) &&
		    vअगर && vअगर->type == NL80211_IFTYPE_AP)
			वापस IWL_WATCHDOG_DISABLED;
		वापस शेष_समयout;
	पूर्ण

	trigger = iwl_fw_dbg_get_trigger(mvm->fw, FW_DBG_TRIGGER_TXQ_TIMERS);
	txq_समयr = (व्योम *)trigger->data;

	अगर (tdls)
		वापस le32_to_cpu(txq_समयr->tdls);

	अगर (cmd_q)
		वापस le32_to_cpu(txq_समयr->command_queue);

	अगर (WARN_ON(!vअगर))
		वापस शेष_समयout;

	चयन (ieee80211_vअगर_type_p2p(vअगर)) अणु
	हाल NL80211_IFTYPE_ADHOC:
		वापस le32_to_cpu(txq_समयr->ibss);
	हाल NL80211_IFTYPE_STATION:
		वापस le32_to_cpu(txq_समयr->bss);
	हाल NL80211_IFTYPE_AP:
		वापस le32_to_cpu(txq_समयr->softap);
	हाल NL80211_IFTYPE_P2P_CLIENT:
		वापस le32_to_cpu(txq_समयr->p2p_client);
	हाल NL80211_IFTYPE_P2P_GO:
		वापस le32_to_cpu(txq_समयr->p2p_go);
	हाल NL80211_IFTYPE_P2P_DEVICE:
		वापस le32_to_cpu(txq_समयr->p2p_device);
	हाल NL80211_IFTYPE_MONITOR:
		वापस शेष_समयout;
	शेष:
		WARN_ON(1);
		वापस mvm->trans->trans_cfg->base_params->wd_समयout;
	पूर्ण
पूर्ण

व्योम iwl_mvm_connection_loss(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर,
			     स्थिर अक्षर *errmsg)
अणु
	काष्ठा iwl_fw_dbg_trigger_tlv *trig;
	काष्ठा iwl_fw_dbg_trigger_mlme *trig_mlme;

	trig = iwl_fw_dbg_trigger_on(&mvm->fwrt, ieee80211_vअगर_to_wdev(vअगर),
				     FW_DBG_TRIGGER_MLME);
	अगर (!trig)
		जाओ out;

	trig_mlme = (व्योम *)trig->data;

	अगर (trig_mlme->stop_connection_loss &&
	    --trig_mlme->stop_connection_loss)
		जाओ out;

	iwl_fw_dbg_collect_trig(&mvm->fwrt, trig, "%s", errmsg);

out:
	ieee80211_connection_loss(vअगर);
पूर्ण

व्योम iwl_mvm_event_frame_समयout_callback(काष्ठा iwl_mvm *mvm,
					  काष्ठा ieee80211_vअगर *vअगर,
					  स्थिर काष्ठा ieee80211_sta *sta,
					  u16 tid)
अणु
	काष्ठा iwl_fw_dbg_trigger_tlv *trig;
	काष्ठा iwl_fw_dbg_trigger_ba *ba_trig;

	trig = iwl_fw_dbg_trigger_on(&mvm->fwrt, ieee80211_vअगर_to_wdev(vअगर),
				     FW_DBG_TRIGGER_BA);
	अगर (!trig)
		वापस;

	ba_trig = (व्योम *)trig->data;

	अगर (!(le16_to_cpu(ba_trig->frame_समयout) & BIT(tid)))
		वापस;

	iwl_fw_dbg_collect_trig(&mvm->fwrt, trig,
				"Frame from %pM timed out, tid %d",
				sta->addr, tid);
पूर्ण

u8 iwl_mvm_tcm_load_percentage(u32 airसमय, u32 elapsed)
अणु
	अगर (!elapsed)
		वापस 0;

	वापस (100 * airसमय / elapsed) / USEC_PER_MSEC;
पूर्ण

अटल क्रमागत iwl_mvm_traffic_load
iwl_mvm_tcm_load(काष्ठा iwl_mvm *mvm, u32 airसमय, अचिन्हित दीर्घ elapsed)
अणु
	u8 load = iwl_mvm_tcm_load_percentage(airसमय, elapsed);

	अगर (load > IWL_MVM_TCM_LOAD_HIGH_THRESH)
		वापस IWL_MVM_TRAFFIC_HIGH;
	अगर (load > IWL_MVM_TCM_LOAD_MEDIUM_THRESH)
		वापस IWL_MVM_TRAFFIC_MEDIUM;

	वापस IWL_MVM_TRAFFIC_LOW;
पूर्ण

अटल व्योम iwl_mvm_tcm_iter(व्योम *_data, u8 *mac, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा iwl_mvm *mvm = _data;
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	bool low_latency, prev = mvmvअगर->low_latency & LOW_LATENCY_TRAFFIC;

	अगर (mvmvअगर->id >= NUM_MAC_INDEX_DRIVER)
		वापस;

	low_latency = mvm->tcm.result.low_latency[mvmvअगर->id];

	अगर (!mvm->tcm.result.change[mvmvअगर->id] &&
	    prev == low_latency) अणु
		iwl_mvm_update_quotas(mvm, false, शून्य);
		वापस;
	पूर्ण

	अगर (prev != low_latency) अणु
		/* this sends traffic load and updates quota as well */
		iwl_mvm_update_low_latency(mvm, vअगर, low_latency,
					   LOW_LATENCY_TRAFFIC);
	पूर्ण अन्यथा अणु
		iwl_mvm_update_quotas(mvm, false, शून्य);
	पूर्ण
पूर्ण

अटल व्योम iwl_mvm_tcm_results(काष्ठा iwl_mvm *mvm)
अणु
	mutex_lock(&mvm->mutex);

	ieee80211_iterate_active_पूर्णांकerfaces(
		mvm->hw, IEEE80211_IFACE_ITER_NORMAL,
		iwl_mvm_tcm_iter, mvm);

	अगर (fw_has_capa(&mvm->fw->ucode_capa, IWL_UCODE_TLV_CAPA_UMAC_SCAN))
		iwl_mvm_config_scan(mvm);

	mutex_unlock(&mvm->mutex);
पूर्ण

अटल व्योम iwl_mvm_tcm_uapsd_nonagg_detected_wk(काष्ठा work_काष्ठा *wk)
अणु
	काष्ठा iwl_mvm *mvm;
	काष्ठा iwl_mvm_vअगर *mvmvअगर;
	काष्ठा ieee80211_vअगर *vअगर;

	mvmvअगर = container_of(wk, काष्ठा iwl_mvm_vअगर,
			      uapsd_nonagg_detected_wk.work);
	vअगर = container_of((व्योम *)mvmvअगर, काष्ठा ieee80211_vअगर, drv_priv);
	mvm = mvmvअगर->mvm;

	अगर (mvm->tcm.data[mvmvअगर->id].खोलोed_rx_ba_sessions)
		वापस;

	/* remember that this AP is broken */
	स_नकल(mvm->uapsd_noagg_bssids[mvm->uapsd_noagg_bssid_ग_लिखो_idx].addr,
	       vअगर->bss_conf.bssid, ETH_ALEN);
	mvm->uapsd_noagg_bssid_ग_लिखो_idx++;
	अगर (mvm->uapsd_noagg_bssid_ग_लिखो_idx >= IWL_MVM_UAPSD_NOAGG_LIST_LEN)
		mvm->uapsd_noagg_bssid_ग_लिखो_idx = 0;

	iwl_mvm_connection_loss(mvm, vअगर,
				"AP isn't using AMPDU with uAPSD enabled");
पूर्ण

अटल व्योम iwl_mvm_uapsd_agg_disconnect(काष्ठा iwl_mvm *mvm,
					 काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);

	अगर (vअगर->type != NL80211_IFTYPE_STATION)
		वापस;

	अगर (!vअगर->bss_conf.assoc)
		वापस;

	अगर (!mvmvअगर->queue_params[IEEE80211_AC_VO].uapsd &&
	    !mvmvअगर->queue_params[IEEE80211_AC_VI].uapsd &&
	    !mvmvअगर->queue_params[IEEE80211_AC_BE].uapsd &&
	    !mvmvअगर->queue_params[IEEE80211_AC_BK].uapsd)
		वापस;

	अगर (mvm->tcm.data[mvmvअगर->id].uapsd_nonagg_detect.detected)
		वापस;

	mvm->tcm.data[mvmvअगर->id].uapsd_nonagg_detect.detected = true;
	IWL_INFO(mvm,
		 "detected AP should do aggregation but isn't, likely due to U-APSD\n");
	schedule_delayed_work(&mvmvअगर->uapsd_nonagg_detected_wk, 15 * HZ);
पूर्ण

अटल व्योम iwl_mvm_check_uapsd_agg_expected_tpt(काष्ठा iwl_mvm *mvm,
						 अचिन्हित पूर्णांक elapsed,
						 पूर्णांक mac)
अणु
	u64 bytes = mvm->tcm.data[mac].uapsd_nonagg_detect.rx_bytes;
	u64 tpt;
	अचिन्हित दीर्घ rate;
	काष्ठा ieee80211_vअगर *vअगर;

	rate = ewma_rate_पढ़ो(&mvm->tcm.data[mac].uapsd_nonagg_detect.rate);

	अगर (!rate || mvm->tcm.data[mac].खोलोed_rx_ba_sessions ||
	    mvm->tcm.data[mac].uapsd_nonagg_detect.detected)
		वापस;

	अगर (iwl_mvm_has_new_rx_api(mvm)) अणु
		tpt = 8 * bytes; /* kbps */
		करो_भाग(tpt, elapsed);
		rate *= 1000; /* kbps */
		अगर (tpt < 22 * rate / 100)
			वापस;
	पूर्ण अन्यथा अणु
		/*
		 * the rate here is actually the threshold, in 100Kbps units,
		 * so करो the needed conversion from bytes to 100Kbps:
		 * 100kb = bits / (100 * 1000),
		 * 100kbps = 100kb / (msecs / 1000) ==
		 *           (bits / (100 * 1000)) / (msecs / 1000) ==
		 *           bits / (100 * msecs)
		 */
		tpt = (8 * bytes);
		करो_भाग(tpt, elapsed * 100);
		अगर (tpt < rate)
			वापस;
	पूर्ण

	rcu_पढ़ो_lock();
	vअगर = rcu_dereference(mvm->vअगर_id_to_mac[mac]);
	अगर (vअगर)
		iwl_mvm_uapsd_agg_disconnect(mvm, vअगर);
	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम iwl_mvm_tcm_iterator(व्योम *_data, u8 *mac,
				 काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	u32 *band = _data;

	अगर (!mvmvअगर->phy_ctxt)
		वापस;

	band[mvmvअगर->id] = mvmvअगर->phy_ctxt->channel->band;
पूर्ण

अटल अचिन्हित दीर्घ iwl_mvm_calc_tcm_stats(काष्ठा iwl_mvm *mvm,
					    अचिन्हित दीर्घ ts,
					    bool handle_uapsd)
अणु
	अचिन्हित पूर्णांक elapsed = jअगरfies_to_msecs(ts - mvm->tcm.ts);
	अचिन्हित पूर्णांक uapsd_elapsed =
		jअगरfies_to_msecs(ts - mvm->tcm.uapsd_nonagg_ts);
	u32 total_airसमय = 0;
	u32 band_airसमय[NUM_NL80211_BANDS] = अणु0पूर्ण;
	u32 band[NUM_MAC_INDEX_DRIVER] = अणु0पूर्ण;
	पूर्णांक ac, mac, i;
	bool low_latency = false;
	क्रमागत iwl_mvm_traffic_load load, band_load;
	bool handle_ll = समय_after(ts, mvm->tcm.ll_ts + MVM_LL_PERIOD);

	अगर (handle_ll)
		mvm->tcm.ll_ts = ts;
	अगर (handle_uapsd)
		mvm->tcm.uapsd_nonagg_ts = ts;

	mvm->tcm.result.elapsed = elapsed;

	ieee80211_iterate_active_पूर्णांकerfaces_atomic(mvm->hw,
						   IEEE80211_IFACE_ITER_NORMAL,
						   iwl_mvm_tcm_iterator,
						   &band);

	क्रम (mac = 0; mac < NUM_MAC_INDEX_DRIVER; mac++) अणु
		काष्ठा iwl_mvm_tcm_mac *mdata = &mvm->tcm.data[mac];
		u32 vo_vi_pkts = 0;
		u32 airसमय = mdata->rx.airसमय + mdata->tx.airसमय;

		total_airसमय += airसमय;
		band_airसमय[band[mac]] += airसमय;

		load = iwl_mvm_tcm_load(mvm, airसमय, elapsed);
		mvm->tcm.result.change[mac] = load != mvm->tcm.result.load[mac];
		mvm->tcm.result.load[mac] = load;
		mvm->tcm.result.airसमय[mac] = airसमय;

		क्रम (ac = IEEE80211_AC_VO; ac <= IEEE80211_AC_VI; ac++)
			vo_vi_pkts += mdata->rx.pkts[ac] +
				      mdata->tx.pkts[ac];

		/* enable immediately with enough packets but defer disabling */
		अगर (vo_vi_pkts > IWL_MVM_TCM_LOWLAT_ENABLE_THRESH)
			mvm->tcm.result.low_latency[mac] = true;
		अन्यथा अगर (handle_ll)
			mvm->tcm.result.low_latency[mac] = false;

		अगर (handle_ll) अणु
			/* clear old data */
			स_रखो(&mdata->rx.pkts, 0, माप(mdata->rx.pkts));
			स_रखो(&mdata->tx.pkts, 0, माप(mdata->tx.pkts));
		पूर्ण
		low_latency |= mvm->tcm.result.low_latency[mac];

		अगर (!mvm->tcm.result.low_latency[mac] && handle_uapsd)
			iwl_mvm_check_uapsd_agg_expected_tpt(mvm, uapsd_elapsed,
							     mac);
		/* clear old data */
		अगर (handle_uapsd)
			mdata->uapsd_nonagg_detect.rx_bytes = 0;
		स_रखो(&mdata->rx.airसमय, 0, माप(mdata->rx.airसमय));
		स_रखो(&mdata->tx.airसमय, 0, माप(mdata->tx.airसमय));
	पूर्ण

	load = iwl_mvm_tcm_load(mvm, total_airसमय, elapsed);
	mvm->tcm.result.global_load = load;

	क्रम (i = 0; i < NUM_NL80211_BANDS; i++) अणु
		band_load = iwl_mvm_tcm_load(mvm, band_airसमय[i], elapsed);
		mvm->tcm.result.band_load[i] = band_load;
	पूर्ण

	/*
	 * If the current load isn't low we need to क्रमce re-evaluation
	 * in the TCM period, so that we can वापस to low load अगर there
	 * was no traffic at all (and thus iwl_mvm_recalc_tcm didn't get
	 * triggered by traffic).
	 */
	अगर (load != IWL_MVM_TRAFFIC_LOW)
		वापस MVM_TCM_PERIOD;
	/*
	 * If low-latency is active we need to क्रमce re-evaluation after
	 * (the दीर्घer) MVM_LL_PERIOD, so that we can disable low-latency
	 * when there's no traffic at all.
	 */
	अगर (low_latency)
		वापस MVM_LL_PERIOD;
	/*
	 * Otherwise, we करोn't need to run the work struct because we're
	 * in the शेष "idle" state - traffic indication is low (which
	 * also covers the "no traffic" हाल) and low-latency is disabled
	 * so there's no state that may need to be disabled when there's
	 * no traffic at all.
	 *
	 * Note that this has no impact on the regular scheduling of the
	 * updates triggered by traffic - those happen whenever one of the
	 * two समयouts expire (अगर there's traffic at all.)
	 */
	वापस 0;
पूर्ण

व्योम iwl_mvm_recalc_tcm(काष्ठा iwl_mvm *mvm)
अणु
	अचिन्हित दीर्घ ts = jअगरfies;
	bool handle_uapsd =
		समय_after(ts, mvm->tcm.uapsd_nonagg_ts +
			       msecs_to_jअगरfies(IWL_MVM_UAPSD_NONAGG_PERIOD));

	spin_lock(&mvm->tcm.lock);
	अगर (mvm->tcm.छोड़ोd || !समय_after(ts, mvm->tcm.ts + MVM_TCM_PERIOD)) अणु
		spin_unlock(&mvm->tcm.lock);
		वापस;
	पूर्ण
	spin_unlock(&mvm->tcm.lock);

	अगर (handle_uapsd && iwl_mvm_has_new_rx_api(mvm)) अणु
		mutex_lock(&mvm->mutex);
		अगर (iwl_mvm_request_statistics(mvm, true))
			handle_uapsd = false;
		mutex_unlock(&mvm->mutex);
	पूर्ण

	spin_lock(&mvm->tcm.lock);
	/* re-check अगर somebody अन्यथा won the recheck race */
	अगर (!mvm->tcm.छोड़ोd && समय_after(ts, mvm->tcm.ts + MVM_TCM_PERIOD)) अणु
		/* calculate statistics */
		अचिन्हित दीर्घ work_delay = iwl_mvm_calc_tcm_stats(mvm, ts,
								  handle_uapsd);

		/* the स_रखो needs to be visible beक्रमe the बारtamp */
		smp_mb();
		mvm->tcm.ts = ts;
		अगर (work_delay)
			schedule_delayed_work(&mvm->tcm.work, work_delay);
	पूर्ण
	spin_unlock(&mvm->tcm.lock);

	iwl_mvm_tcm_results(mvm);
पूर्ण

व्योम iwl_mvm_tcm_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *delayed_work = to_delayed_work(work);
	काष्ठा iwl_mvm *mvm = container_of(delayed_work, काष्ठा iwl_mvm,
					   tcm.work);

	iwl_mvm_recalc_tcm(mvm);
पूर्ण

व्योम iwl_mvm_छोड़ो_tcm(काष्ठा iwl_mvm *mvm, bool with_cancel)
अणु
	spin_lock_bh(&mvm->tcm.lock);
	mvm->tcm.छोड़ोd = true;
	spin_unlock_bh(&mvm->tcm.lock);
	अगर (with_cancel)
		cancel_delayed_work_sync(&mvm->tcm.work);
पूर्ण

व्योम iwl_mvm_resume_tcm(काष्ठा iwl_mvm *mvm)
अणु
	पूर्णांक mac;
	bool low_latency = false;

	spin_lock_bh(&mvm->tcm.lock);
	mvm->tcm.ts = jअगरfies;
	mvm->tcm.ll_ts = jअगरfies;
	क्रम (mac = 0; mac < NUM_MAC_INDEX_DRIVER; mac++) अणु
		काष्ठा iwl_mvm_tcm_mac *mdata = &mvm->tcm.data[mac];

		स_रखो(&mdata->rx.pkts, 0, माप(mdata->rx.pkts));
		स_रखो(&mdata->tx.pkts, 0, माप(mdata->tx.pkts));
		स_रखो(&mdata->rx.airसमय, 0, माप(mdata->rx.airसमय));
		स_रखो(&mdata->tx.airसमय, 0, माप(mdata->tx.airसमय));

		अगर (mvm->tcm.result.low_latency[mac])
			low_latency = true;
	पूर्ण
	/* The TCM data needs to be reset beक्रमe "paused" flag changes */
	smp_mb();
	mvm->tcm.छोड़ोd = false;

	/*
	 * अगर the current load is not low or low latency is active, क्रमce
	 * re-evaluation to cover the हाल of no traffic.
	 */
	अगर (mvm->tcm.result.global_load > IWL_MVM_TRAFFIC_LOW)
		schedule_delayed_work(&mvm->tcm.work, MVM_TCM_PERIOD);
	अन्यथा अगर (low_latency)
		schedule_delayed_work(&mvm->tcm.work, MVM_LL_PERIOD);

	spin_unlock_bh(&mvm->tcm.lock);
पूर्ण

व्योम iwl_mvm_tcm_add_vअगर(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);

	INIT_DELAYED_WORK(&mvmvअगर->uapsd_nonagg_detected_wk,
			  iwl_mvm_tcm_uapsd_nonagg_detected_wk);
पूर्ण

व्योम iwl_mvm_tcm_rm_vअगर(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);

	cancel_delayed_work_sync(&mvmvअगर->uapsd_nonagg_detected_wk);
पूर्ण

u32 iwl_mvm_get_sysसमय(काष्ठा iwl_mvm *mvm)
अणु
	u32 reg_addr = DEVICE_SYSTEM_TIME_REG;

	अगर (mvm->trans->trans_cfg->device_family >= IWL_DEVICE_FAMILY_22000 &&
	    mvm->trans->cfg->gp2_reg_addr)
		reg_addr = mvm->trans->cfg->gp2_reg_addr;

	वापस iwl_पढ़ो_prph(mvm->trans, reg_addr);
पूर्ण

व्योम iwl_mvm_get_sync_समय(काष्ठा iwl_mvm *mvm, u32 *gp2, u64 *bootसमय)
अणु
	bool ps_disabled;

	lockdep_निश्चित_held(&mvm->mutex);

	/* Disable घातer save when पढ़ोing GP2 */
	ps_disabled = mvm->ps_disabled;
	अगर (!ps_disabled) अणु
		mvm->ps_disabled = true;
		iwl_mvm_घातer_update_device(mvm);
	पूर्ण

	*gp2 = iwl_mvm_get_sysसमय(mvm);
	*bootसमय = kसमय_get_bootसमय_ns();

	अगर (!ps_disabled) अणु
		mvm->ps_disabled = ps_disabled;
		iwl_mvm_घातer_update_device(mvm);
	पूर्ण
पूर्ण
