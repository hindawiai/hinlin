<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/*
 * Copyright (C) 2012-2014, 2018-2020 Intel Corporation
 * Copyright (C) 2013-2015 Intel Mobile Communications GmbH
 * Copyright (C) 2016-2017 Intel Deutschland GmbH
 */
#समावेश "iwl-drv.h"
#समावेश "runtime.h"
#समावेश "fw/api/commands.h"

अटल व्योम iwl_parse_shared_mem_22000(काष्ठा iwl_fw_runसमय *fwrt,
				       काष्ठा iwl_rx_packet *pkt)
अणु
	काष्ठा iwl_shared_mem_cfg *mem_cfg = (व्योम *)pkt->data;
	पूर्णांक i, lmac;
	पूर्णांक lmac_num = le32_to_cpu(mem_cfg->lmac_num);
	u8 api_ver = iwl_fw_lookup_notअगर_ver(fwrt->fw, SYSTEM_GROUP,
					     SHARED_MEM_CFG_CMD, 0);

	अगर (WARN_ON(lmac_num > ARRAY_SIZE(mem_cfg->lmac_smem)))
		वापस;

	fwrt->smem_cfg.num_lmacs = lmac_num;
	fwrt->smem_cfg.num_txfअगरo_entries =
		ARRAY_SIZE(mem_cfg->lmac_smem[0].txfअगरo_size);
	fwrt->smem_cfg.rxfअगरo2_size = le32_to_cpu(mem_cfg->rxfअगरo2_size);

	अगर (api_ver >= 4 &&
	    !WARN_ON_ONCE(iwl_rx_packet_payload_len(pkt) < माप(*mem_cfg))) अणु
		fwrt->smem_cfg.rxfअगरo2_control_size =
			le32_to_cpu(mem_cfg->rxfअगरo2_control_size);
	पूर्ण

	क्रम (lmac = 0; lmac < lmac_num; lmac++) अणु
		काष्ठा iwl_shared_mem_lmac_cfg *lmac_cfg =
			&mem_cfg->lmac_smem[lmac];

		क्रम (i = 0; i < ARRAY_SIZE(lmac_cfg->txfअगरo_size); i++)
			fwrt->smem_cfg.lmac[lmac].txfअगरo_size[i] =
				le32_to_cpu(lmac_cfg->txfअगरo_size[i]);
		fwrt->smem_cfg.lmac[lmac].rxfअगरo1_size =
			le32_to_cpu(lmac_cfg->rxfअगरo1_size);
	पूर्ण
पूर्ण

अटल व्योम iwl_parse_shared_mem(काष्ठा iwl_fw_runसमय *fwrt,
				 काष्ठा iwl_rx_packet *pkt)
अणु
	काष्ठा iwl_shared_mem_cfg_v2 *mem_cfg = (व्योम *)pkt->data;
	पूर्णांक i;

	fwrt->smem_cfg.num_lmacs = 1;

	fwrt->smem_cfg.num_txfअगरo_entries = ARRAY_SIZE(mem_cfg->txfअगरo_size);
	क्रम (i = 0; i < ARRAY_SIZE(mem_cfg->txfअगरo_size); i++)
		fwrt->smem_cfg.lmac[0].txfअगरo_size[i] =
			le32_to_cpu(mem_cfg->txfअगरo_size[i]);

	fwrt->smem_cfg.lmac[0].rxfअगरo1_size =
		le32_to_cpu(mem_cfg->rxfअगरo_size[0]);
	fwrt->smem_cfg.rxfअगरo2_size = le32_to_cpu(mem_cfg->rxfअगरo_size[1]);

	/* new API has more data, from rxfअगरo_addr field and on */
	अगर (fw_has_capa(&fwrt->fw->ucode_capa,
			IWL_UCODE_TLV_CAPA_EXTEND_SHARED_MEM_CFG)) अणु
		BUILD_BUG_ON(माप(fwrt->smem_cfg.पूर्णांकernal_txfअगरo_size) !=
			     माप(mem_cfg->पूर्णांकernal_txfअगरo_size));

		fwrt->smem_cfg.पूर्णांकernal_txfअगरo_addr =
			le32_to_cpu(mem_cfg->पूर्णांकernal_txfअगरo_addr);

		क्रम (i = 0;
		     i < ARRAY_SIZE(fwrt->smem_cfg.पूर्णांकernal_txfअगरo_size);
		     i++)
			fwrt->smem_cfg.पूर्णांकernal_txfअगरo_size[i] =
				le32_to_cpu(mem_cfg->पूर्णांकernal_txfअगरo_size[i]);
	पूर्ण
पूर्ण

व्योम iwl_get_shared_mem_conf(काष्ठा iwl_fw_runसमय *fwrt)
अणु
	काष्ठा iwl_host_cmd cmd = अणु
		.flags = CMD_WANT_SKB,
		.data = अणु शून्य, पूर्ण,
		.len = अणु 0, पूर्ण,
	पूर्ण;
	काष्ठा iwl_rx_packet *pkt;
	पूर्णांक ret;

	अगर (fw_has_capa(&fwrt->fw->ucode_capa,
			IWL_UCODE_TLV_CAPA_EXTEND_SHARED_MEM_CFG))
		cmd.id = iwl_cmd_id(SHARED_MEM_CFG_CMD, SYSTEM_GROUP, 0);
	अन्यथा
		cmd.id = SHARED_MEM_CFG;

	ret = iwl_trans_send_cmd(fwrt->trans, &cmd);

	अगर (ret) अणु
		WARN(ret != -ERFKILL,
		     "Could not send the SMEM command: %d\n", ret);
		वापस;
	पूर्ण

	pkt = cmd.resp_pkt;
	अगर (fwrt->trans->trans_cfg->device_family >= IWL_DEVICE_FAMILY_22000)
		iwl_parse_shared_mem_22000(fwrt, pkt);
	अन्यथा
		iwl_parse_shared_mem(fwrt, pkt);

	IWL_DEBUG_INFO(fwrt, "SHARED MEM CFG: got memory offsets/sizes\n");

	iwl_मुक्त_resp(&cmd);
पूर्ण
IWL_EXPORT_SYMBOL(iwl_get_shared_mem_conf);
