<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/*
 * Copyright (C) 2018-2021 Intel Corporation
 */
#समावेश "iwl-trans.h"
#समावेश "iwl-fh.h"
#समावेश "iwl-context-info-gen3.h"
#समावेश "internal.h"
#समावेश "iwl-prph.h"

अटल व्योम
iwl_pcie_ctxt_info_dbg_enable(काष्ठा iwl_trans *trans,
			      काष्ठा iwl_prph_scratch_hwm_cfg *dbg_cfg,
			      u32 *control_flags)
अणु
	क्रमागत iwl_fw_ini_allocation_id alloc_id = IWL_FW_INI_ALLOCATION_ID_DBGC1;
	काष्ठा iwl_fw_ini_allocation_tlv *fw_mon_cfg;
	u32 dbg_flags = 0;

	अगर (!iwl_trans_dbg_ini_valid(trans)) अणु
		काष्ठा iwl_dram_data *fw_mon = &trans->dbg.fw_mon;

		iwl_pcie_alloc_fw_monitor(trans, 0);

		अगर (fw_mon->size) अणु
			dbg_flags |= IWL_PRPH_SCRATCH_EDBG_DEST_DRAM;

			IWL_DEBUG_FW(trans,
				     "WRT: Applying DRAM buffer destination\n");

			dbg_cfg->hwm_base_addr = cpu_to_le64(fw_mon->physical);
			dbg_cfg->hwm_size = cpu_to_le32(fw_mon->size);
		पूर्ण

		जाओ out;
	पूर्ण

	fw_mon_cfg = &trans->dbg.fw_mon_cfg[alloc_id];

	चयन (le32_to_cpu(fw_mon_cfg->buf_location)) अणु
	हाल IWL_FW_INI_LOCATION_SRAM_PATH:
		dbg_flags |= IWL_PRPH_SCRATCH_EDBG_DEST_INTERNAL;
		IWL_DEBUG_FW(trans,
				"WRT: Applying SMEM buffer destination\n");
		अवरोध;

	हाल IWL_FW_INI_LOCATION_NPK_PATH:
		dbg_flags |= IWL_PRPH_SCRATCH_EDBG_DEST_TB22DTF;
		IWL_DEBUG_FW(trans,
			     "WRT: Applying NPK buffer destination\n");
		अवरोध;

	हाल IWL_FW_INI_LOCATION_DRAM_PATH:
		अगर (trans->dbg.fw_mon_ini[alloc_id].num_frags) अणु
			काष्ठा iwl_dram_data *frag =
				&trans->dbg.fw_mon_ini[alloc_id].frags[0];
			dbg_flags |= IWL_PRPH_SCRATCH_EDBG_DEST_DRAM;
			dbg_cfg->hwm_base_addr = cpu_to_le64(frag->physical);
			dbg_cfg->hwm_size = cpu_to_le32(frag->size);
			IWL_DEBUG_FW(trans,
				     "WRT: Applying DRAM destination (alloc_id=%u, num_frags=%u)\n",
				     alloc_id,
				     trans->dbg.fw_mon_ini[alloc_id].num_frags);
		पूर्ण
		अवरोध;
	शेष:
		IWL_ERR(trans, "WRT: Invalid buffer destination\n");
	पूर्ण
out:
	अगर (dbg_flags)
		*control_flags |= IWL_PRPH_SCRATCH_EARLY_DEBUG_EN | dbg_flags;
पूर्ण

पूर्णांक iwl_pcie_ctxt_info_gen3_init(काष्ठा iwl_trans *trans,
				 स्थिर काष्ठा fw_img *fw)
अणु
	काष्ठा iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	काष्ठा iwl_context_info_gen3 *ctxt_info_gen3;
	काष्ठा iwl_prph_scratch *prph_scratch;
	काष्ठा iwl_prph_scratch_ctrl_cfg *prph_sc_ctrl;
	काष्ठा iwl_prph_info *prph_info;
	व्योम *iml_img;
	u32 control_flags = 0;
	पूर्णांक ret;
	पूर्णांक cmdq_size = max_t(u32, IWL_CMD_QUEUE_SIZE,
			      trans->cfg->min_txq_size);

	चयन (trans_pcie->rx_buf_size) अणु
	हाल IWL_AMSDU_DEF:
		वापस -EINVAL;
	हाल IWL_AMSDU_2K:
		अवरोध;
	हाल IWL_AMSDU_4K:
		control_flags |= IWL_PRPH_SCRATCH_RB_SIZE_4K;
		अवरोध;
	हाल IWL_AMSDU_8K:
		control_flags |= IWL_PRPH_SCRATCH_RB_SIZE_4K;
		/* अगर firmware supports the ext size, tell it */
		control_flags |= IWL_PRPH_SCRATCH_RB_SIZE_EXT_8K;
		अवरोध;
	हाल IWL_AMSDU_12K:
		control_flags |= IWL_PRPH_SCRATCH_RB_SIZE_4K;
		/* अगर firmware supports the ext size, tell it */
		control_flags |= IWL_PRPH_SCRATCH_RB_SIZE_EXT_16K;
		अवरोध;
	पूर्ण

	/* Allocate prph scratch */
	prph_scratch = dma_alloc_coherent(trans->dev, माप(*prph_scratch),
					  &trans_pcie->prph_scratch_dma_addr,
					  GFP_KERNEL);
	अगर (!prph_scratch)
		वापस -ENOMEM;

	prph_sc_ctrl = &prph_scratch->ctrl_cfg;

	prph_sc_ctrl->version.version = 0;
	prph_sc_ctrl->version.mac_id =
		cpu_to_le16((u16)iwl_पढ़ो32(trans, CSR_HW_REV));
	prph_sc_ctrl->version.size = cpu_to_le16(माप(*prph_scratch) / 4);

	control_flags |= IWL_PRPH_SCRATCH_MTR_MODE;
	control_flags |= IWL_PRPH_MTR_FORMAT_256B & IWL_PRPH_SCRATCH_MTR_FORMAT;

	/* initialize RX शेष queue */
	prph_sc_ctrl->rbd_cfg.मुक्त_rbd_addr =
		cpu_to_le64(trans_pcie->rxq->bd_dma);

	iwl_pcie_ctxt_info_dbg_enable(trans, &prph_sc_ctrl->hwm_cfg,
				      &control_flags);
	prph_sc_ctrl->control.control_flags = cpu_to_le32(control_flags);

	/* allocate ucode sections in dram and set addresses */
	ret = iwl_pcie_init_fw_sec(trans, fw, &prph_scratch->dram);
	अगर (ret)
		जाओ err_मुक्त_prph_scratch;


	/* Allocate prph inक्रमmation
	 * currently we करोn't assign to the prph info anything, but it would get
	 * asचिन्हित later */
	prph_info = dma_alloc_coherent(trans->dev, माप(*prph_info),
				       &trans_pcie->prph_info_dma_addr,
				       GFP_KERNEL);
	अगर (!prph_info) अणु
		ret = -ENOMEM;
		जाओ err_मुक्त_prph_scratch;
	पूर्ण

	/* Allocate context info */
	ctxt_info_gen3 = dma_alloc_coherent(trans->dev,
					    माप(*ctxt_info_gen3),
					    &trans_pcie->ctxt_info_dma_addr,
					    GFP_KERNEL);
	अगर (!ctxt_info_gen3) अणु
		ret = -ENOMEM;
		जाओ err_मुक्त_prph_info;
	पूर्ण

	ctxt_info_gen3->prph_info_base_addr =
		cpu_to_le64(trans_pcie->prph_info_dma_addr);
	ctxt_info_gen3->prph_scratch_base_addr =
		cpu_to_le64(trans_pcie->prph_scratch_dma_addr);
	ctxt_info_gen3->prph_scratch_size =
		cpu_to_le32(माप(*prph_scratch));
	ctxt_info_gen3->cr_head_idx_arr_base_addr =
		cpu_to_le64(trans_pcie->rxq->rb_stts_dma);
	ctxt_info_gen3->tr_tail_idx_arr_base_addr =
		cpu_to_le64(trans_pcie->rxq->tr_tail_dma);
	ctxt_info_gen3->cr_tail_idx_arr_base_addr =
		cpu_to_le64(trans_pcie->rxq->cr_tail_dma);
	ctxt_info_gen3->cr_idx_arr_size =
		cpu_to_le16(IWL_NUM_OF_COMPLETION_RINGS);
	ctxt_info_gen3->tr_idx_arr_size =
		cpu_to_le16(IWL_NUM_OF_TRANSFER_RINGS);
	ctxt_info_gen3->mtr_base_addr =
		cpu_to_le64(trans->txqs.txq[trans->txqs.cmd.q_id]->dma_addr);
	ctxt_info_gen3->mcr_base_addr =
		cpu_to_le64(trans_pcie->rxq->used_bd_dma);
	ctxt_info_gen3->mtr_size =
		cpu_to_le16(TFD_QUEUE_CB_SIZE(cmdq_size));
	ctxt_info_gen3->mcr_size =
		cpu_to_le16(RX_QUEUE_CB_SIZE(trans->cfg->num_rbds));

	trans_pcie->ctxt_info_gen3 = ctxt_info_gen3;
	trans_pcie->prph_info = prph_info;
	trans_pcie->prph_scratch = prph_scratch;

	/* Allocate IML */
	iml_img = dma_alloc_coherent(trans->dev, trans->iml_len,
				     &trans_pcie->iml_dma_addr, GFP_KERNEL);
	अगर (!iml_img) अणु
		ret = -ENOMEM;
		जाओ err_मुक्त_ctxt_info;
	पूर्ण

	स_नकल(iml_img, trans->iml, trans->iml_len);

	iwl_enable_fw_load_पूर्णांक_ctx_info(trans);

	/* kick FW self load */
	iwl_ग_लिखो64(trans, CSR_CTXT_INFO_ADDR,
		    trans_pcie->ctxt_info_dma_addr);
	iwl_ग_लिखो64(trans, CSR_IML_DATA_ADDR,
		    trans_pcie->iml_dma_addr);
	iwl_ग_लिखो32(trans, CSR_IML_SIZE_ADDR, trans->iml_len);

	iwl_set_bit(trans, CSR_CTXT_INFO_BOOT_CTRL,
		    CSR_AUTO_FUNC_BOOT_ENA);

	वापस 0;

err_मुक्त_ctxt_info:
	dma_मुक्त_coherent(trans->dev, माप(*trans_pcie->ctxt_info_gen3),
			  trans_pcie->ctxt_info_gen3,
			  trans_pcie->ctxt_info_dma_addr);
	trans_pcie->ctxt_info_gen3 = शून्य;
err_मुक्त_prph_info:
	dma_मुक्त_coherent(trans->dev,
			  माप(*prph_info),
			prph_info,
			trans_pcie->prph_info_dma_addr);

err_मुक्त_prph_scratch:
	dma_मुक्त_coherent(trans->dev,
			  माप(*prph_scratch),
			prph_scratch,
			trans_pcie->prph_scratch_dma_addr);
	वापस ret;

पूर्ण

व्योम iwl_pcie_ctxt_info_gen3_मुक्त(काष्ठा iwl_trans *trans)
अणु
	काष्ठा iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);

	अगर (!trans_pcie->ctxt_info_gen3)
		वापस;

	dma_मुक्त_coherent(trans->dev, माप(*trans_pcie->ctxt_info_gen3),
			  trans_pcie->ctxt_info_gen3,
			  trans_pcie->ctxt_info_dma_addr);
	trans_pcie->ctxt_info_dma_addr = 0;
	trans_pcie->ctxt_info_gen3 = शून्य;

	iwl_pcie_ctxt_info_मुक्त_fw_img(trans);

	dma_मुक्त_coherent(trans->dev, माप(*trans_pcie->prph_scratch),
			  trans_pcie->prph_scratch,
			  trans_pcie->prph_scratch_dma_addr);
	trans_pcie->prph_scratch_dma_addr = 0;
	trans_pcie->prph_scratch = शून्य;

	dma_मुक्त_coherent(trans->dev, माप(*trans_pcie->prph_info),
			  trans_pcie->prph_info,
			  trans_pcie->prph_info_dma_addr);
	trans_pcie->prph_info_dma_addr = 0;
	trans_pcie->prph_info = शून्य;
पूर्ण

पूर्णांक iwl_trans_pcie_ctx_info_gen3_set_pnvm(काष्ठा iwl_trans *trans,
					  स्थिर व्योम *data, u32 len)
अणु
	काष्ठा iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	काष्ठा iwl_prph_scratch_ctrl_cfg *prph_sc_ctrl =
		&trans_pcie->prph_scratch->ctrl_cfg;
	पूर्णांक ret;

	अगर (trans->trans_cfg->device_family < IWL_DEVICE_FAMILY_AX210)
		वापस 0;

	/* only allocate the DRAM अगर not allocated yet */
	अगर (!trans->pnvm_loaded) अणु
		अगर (WARN_ON(prph_sc_ctrl->pnvm_cfg.pnvm_size))
			वापस -EBUSY;

		ret = iwl_pcie_ctxt_info_alloc_dma(trans, data, len,
						   &trans_pcie->pnvm_dram);
		अगर (ret < 0) अणु
			IWL_DEBUG_FW(trans, "Failed to allocate PNVM DMA %d.\n",
				     ret);
			वापस ret;
		पूर्ण
	पूर्ण

	prph_sc_ctrl->pnvm_cfg.pnvm_base_addr =
		cpu_to_le64(trans_pcie->pnvm_dram.physical);
	prph_sc_ctrl->pnvm_cfg.pnvm_size =
		cpu_to_le32(trans_pcie->pnvm_dram.size);

	वापस 0;
पूर्ण
