<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/*
 * Copyright (C) 2017 Intel Deutschland GmbH
 * Copyright (C) 2019-2020 Intel Corporation
 */
#समावेश "iwl-drv.h"
#समावेश "runtime.h"
#समावेश "dbg.h"
#समावेश "debugfs.h"

#समावेश "fw/api/soc.h"
#समावेश "fw/api/commands.h"
#समावेश "fw/api/rx.h"
#समावेश "fw/api/datapath.h"

व्योम iwl_fw_runसमय_init(काष्ठा iwl_fw_runसमय *fwrt, काष्ठा iwl_trans *trans,
			स्थिर काष्ठा iwl_fw *fw,
			स्थिर काष्ठा iwl_fw_runसमय_ops *ops, व्योम *ops_ctx,
			काष्ठा dentry *dbgfs_dir)
अणु
	पूर्णांक i;

	स_रखो(fwrt, 0, माप(*fwrt));
	fwrt->trans = trans;
	fwrt->fw = fw;
	fwrt->dev = trans->dev;
	fwrt->dump.conf = FW_DBG_INVALID;
	fwrt->ops = ops;
	fwrt->ops_ctx = ops_ctx;
	क्रम (i = 0; i < IWL_FW_RUNTIME_DUMP_WK_NUM; i++) अणु
		fwrt->dump.wks[i].idx = i;
		INIT_DELAYED_WORK(&fwrt->dump.wks[i].wk, iwl_fw_error_dump_wk);
	पूर्ण
	iwl_fwrt_dbgfs_रेजिस्टर(fwrt, dbgfs_dir);
पूर्ण
IWL_EXPORT_SYMBOL(iwl_fw_runसमय_init);

व्योम iwl_fw_runसमय_suspend(काष्ठा iwl_fw_runसमय *fwrt)
अणु
	iwl_fw_suspend_बारtamp(fwrt);
	iwl_dbg_tlv_समय_poपूर्णांक(fwrt, IWL_FW_INI_TIME_POINT_HOST_D3_START, शून्य);
पूर्ण
IWL_EXPORT_SYMBOL(iwl_fw_runसमय_suspend);

व्योम iwl_fw_runसमय_resume(काष्ठा iwl_fw_runसमय *fwrt)
अणु
	iwl_dbg_tlv_समय_poपूर्णांक(fwrt, IWL_FW_INI_TIME_POINT_HOST_D3_END, शून्य);
	iwl_fw_resume_बारtamp(fwrt);
पूर्ण
IWL_EXPORT_SYMBOL(iwl_fw_runसमय_resume);

/* set device type and latency */
पूर्णांक iwl_set_soc_latency(काष्ठा iwl_fw_runसमय *fwrt)
अणु
	काष्ठा iwl_soc_configuration_cmd cmd = अणुपूर्ण;
	काष्ठा iwl_host_cmd hcmd = अणु
		.id = iwl_cmd_id(SOC_CONFIGURATION_CMD, SYSTEM_GROUP, 0),
		.data[0] = &cmd,
		.len[0] = माप(cmd),
	पूर्ण;
	पूर्णांक ret;

	/*
	 * In VER_1 of this command, the discrete value is considered
	 * an पूर्णांकeger; In VER_2, it's a biपंचांगask.  Since we have only 2
	 * values in VER_1, this is backwards-compatible with VER_2,
	 * as दीर्घ as we करोn't set any other bits.
	 */
	अगर (!fwrt->trans->trans_cfg->पूर्णांकegrated)
		cmd.flags = cpu_to_le32(SOC_CONFIG_CMD_FLAGS_DISCRETE);

	BUILD_BUG_ON(IWL_CFG_TRANS_LTR_DELAY_NONE !=
		     SOC_FLAGS_LTR_APPLY_DELAY_NONE);
	BUILD_BUG_ON(IWL_CFG_TRANS_LTR_DELAY_200US !=
		     SOC_FLAGS_LTR_APPLY_DELAY_200);
	BUILD_BUG_ON(IWL_CFG_TRANS_LTR_DELAY_2500US !=
		     SOC_FLAGS_LTR_APPLY_DELAY_2500);
	BUILD_BUG_ON(IWL_CFG_TRANS_LTR_DELAY_1820US !=
		     SOC_FLAGS_LTR_APPLY_DELAY_1820);

	अगर (fwrt->trans->trans_cfg->ltr_delay != IWL_CFG_TRANS_LTR_DELAY_NONE &&
	    !WARN_ON(!fwrt->trans->trans_cfg->पूर्णांकegrated))
		cmd.flags |= le32_encode_bits(fwrt->trans->trans_cfg->ltr_delay,
					      SOC_FLAGS_LTR_APPLY_DELAY_MASK);

	अगर (iwl_fw_lookup_cmd_ver(fwrt->fw, IWL_ALWAYS_LONG_GROUP,
				  SCAN_REQ_UMAC,
				  IWL_FW_CMD_VER_UNKNOWN) >= 2 &&
	    fwrt->trans->trans_cfg->low_latency_xtal)
		cmd.flags |= cpu_to_le32(SOC_CONFIG_CMD_FLAGS_LOW_LATENCY);

	cmd.latency = cpu_to_le32(fwrt->trans->trans_cfg->xtal_latency);

	ret = iwl_trans_send_cmd(fwrt->trans, &hcmd);
	अगर (ret)
		IWL_ERR(fwrt, "Failed to set soc latency: %d\n", ret);
	वापस ret;
पूर्ण
IWL_EXPORT_SYMBOL(iwl_set_soc_latency);

पूर्णांक iwl_configure_rxq(काष्ठा iwl_fw_runसमय *fwrt)
अणु
	पूर्णांक i, num_queues, size, ret;
	काष्ठा iwl_rfh_queue_config *cmd;
	काष्ठा iwl_host_cmd hcmd = अणु
		.id = WIDE_ID(DATA_PATH_GROUP, RFH_QUEUE_CONFIG_CMD),
		.dataflags[0] = IWL_HCMD_DFL_NOCOPY,
	पूर्ण;

	/*
	 * The शेष queue is configured via context info, so अगर we
	 * have a single queue, there's nothing to करो here.
	 */
	अगर (fwrt->trans->num_rx_queues == 1)
		वापस 0;

	अगर (fwrt->trans->trans_cfg->device_family < IWL_DEVICE_FAMILY_22000)
		वापस 0;

	/* skip the शेष queue */
	num_queues = fwrt->trans->num_rx_queues - 1;

	size = काष्ठा_size(cmd, data, num_queues);

	cmd = kzalloc(size, GFP_KERNEL);
	अगर (!cmd)
		वापस -ENOMEM;

	cmd->num_queues = num_queues;

	क्रम (i = 0; i < num_queues; i++) अणु
		काष्ठा iwl_trans_rxq_dma_data data;

		cmd->data[i].q_num = i + 1;
		iwl_trans_get_rxq_dma_data(fwrt->trans, i + 1, &data);

		cmd->data[i].fr_bd_cb = cpu_to_le64(data.fr_bd_cb);
		cmd->data[i].urbd_stts_wrptr =
			cpu_to_le64(data.urbd_stts_wrptr);
		cmd->data[i].ur_bd_cb = cpu_to_le64(data.ur_bd_cb);
		cmd->data[i].fr_bd_wid = cpu_to_le32(data.fr_bd_wid);
	पूर्ण

	hcmd.data[0] = cmd;
	hcmd.len[0] = size;

	ret = iwl_trans_send_cmd(fwrt->trans, &hcmd);

	kमुक्त(cmd);

	अगर (ret)
		IWL_ERR(fwrt, "Failed to configure RX queues: %d\n", ret);

	वापस ret;
पूर्ण
IWL_EXPORT_SYMBOL(iwl_configure_rxq);
