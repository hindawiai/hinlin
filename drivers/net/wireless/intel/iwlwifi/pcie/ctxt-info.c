<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/*
 * Copyright (C) 2017 Intel Deutschland GmbH
 * Copyright (C) 2018-2021 Intel Corporation
 */
#समावेश "iwl-trans.h"
#समावेश "iwl-fh.h"
#समावेश "iwl-context-info.h"
#समावेश "internal.h"
#समावेश "iwl-prph.h"

अटल व्योम *_iwl_pcie_ctxt_info_dma_alloc_coherent(काष्ठा iwl_trans *trans,
						    माप_प्रकार size,
						    dma_addr_t *phys,
						    पूर्णांक depth)
अणु
	व्योम *result;

	अगर (WARN(depth > 2,
		 "failed to allocate DMA memory not crossing 2^32 boundary"))
		वापस शून्य;

	result = dma_alloc_coherent(trans->dev, size, phys, GFP_KERNEL);

	अगर (!result)
		वापस शून्य;

	अगर (unlikely(iwl_txq_crosses_4g_boundary(*phys, size))) अणु
		व्योम *old = result;
		dma_addr_t oldphys = *phys;

		result = _iwl_pcie_ctxt_info_dma_alloc_coherent(trans, size,
								phys,
								depth + 1);
		dma_मुक्त_coherent(trans->dev, size, old, oldphys);
	पूर्ण

	वापस result;
पूर्ण

अटल व्योम *iwl_pcie_ctxt_info_dma_alloc_coherent(काष्ठा iwl_trans *trans,
						   माप_प्रकार size,
						   dma_addr_t *phys)
अणु
	वापस _iwl_pcie_ctxt_info_dma_alloc_coherent(trans, size, phys, 0);
पूर्ण

पूर्णांक iwl_pcie_ctxt_info_alloc_dma(काष्ठा iwl_trans *trans,
				 स्थिर व्योम *data, u32 len,
				 काष्ठा iwl_dram_data *dram)
अणु
	dram->block = iwl_pcie_ctxt_info_dma_alloc_coherent(trans, len,
							    &dram->physical);
	अगर (!dram->block)
		वापस -ENOMEM;

	dram->size = len;
	स_नकल(dram->block, data, len);

	वापस 0;
पूर्ण

व्योम iwl_pcie_ctxt_info_मुक्त_paging(काष्ठा iwl_trans *trans)
अणु
	काष्ठा iwl_self_init_dram *dram = &trans->init_dram;
	पूर्णांक i;

	अगर (!dram->paging) अणु
		WARN_ON(dram->paging_cnt);
		वापस;
	पूर्ण

	/* मुक्त paging*/
	क्रम (i = 0; i < dram->paging_cnt; i++)
		dma_मुक्त_coherent(trans->dev, dram->paging[i].size,
				  dram->paging[i].block,
				  dram->paging[i].physical);

	kमुक्त(dram->paging);
	dram->paging_cnt = 0;
	dram->paging = शून्य;
पूर्ण

पूर्णांक iwl_pcie_init_fw_sec(काष्ठा iwl_trans *trans,
			 स्थिर काष्ठा fw_img *fw,
			 काष्ठा iwl_context_info_dram *ctxt_dram)
अणु
	काष्ठा iwl_self_init_dram *dram = &trans->init_dram;
	पूर्णांक i, ret, lmac_cnt, umac_cnt, paging_cnt;

	अगर (WARN(dram->paging,
		 "paging shouldn't already be initialized (%d pages)\n",
		 dram->paging_cnt))
		iwl_pcie_ctxt_info_मुक्त_paging(trans);

	lmac_cnt = iwl_pcie_get_num_sections(fw, 0);
	/* add 1 due to separator */
	umac_cnt = iwl_pcie_get_num_sections(fw, lmac_cnt + 1);
	/* add 2 due to separators */
	paging_cnt = iwl_pcie_get_num_sections(fw, lmac_cnt + umac_cnt + 2);

	dram->fw = kसुस्मृति(umac_cnt + lmac_cnt, माप(*dram->fw), GFP_KERNEL);
	अगर (!dram->fw)
		वापस -ENOMEM;
	dram->paging = kसुस्मृति(paging_cnt, माप(*dram->paging), GFP_KERNEL);
	अगर (!dram->paging)
		वापस -ENOMEM;

	/* initialize lmac sections */
	क्रम (i = 0; i < lmac_cnt; i++) अणु
		ret = iwl_pcie_ctxt_info_alloc_dma(trans, fw->sec[i].data,
						   fw->sec[i].len,
						   &dram->fw[dram->fw_cnt]);
		अगर (ret)
			वापस ret;
		ctxt_dram->lmac_img[i] =
			cpu_to_le64(dram->fw[dram->fw_cnt].physical);
		dram->fw_cnt++;
	पूर्ण

	/* initialize umac sections */
	क्रम (i = 0; i < umac_cnt; i++) अणु
		/* access FW with +1 to make up क्रम lmac separator */
		ret = iwl_pcie_ctxt_info_alloc_dma(trans,
						   fw->sec[dram->fw_cnt + 1].data,
						   fw->sec[dram->fw_cnt + 1].len,
						   &dram->fw[dram->fw_cnt]);
		अगर (ret)
			वापस ret;
		ctxt_dram->umac_img[i] =
			cpu_to_le64(dram->fw[dram->fw_cnt].physical);
		dram->fw_cnt++;
	पूर्ण

	/*
	 * Initialize paging.
	 * Paging memory isn't stored in dram->fw as the umac and lmac - it is
	 * stored separately.
	 * This is since the timing of its release is dअगरferent -
	 * जबतक fw memory can be released on alive, the paging memory can be
	 * मुक्तd only when the device goes करोwn.
	 * Given that, the logic here in accessing the fw image is a bit
	 * dअगरferent - fw_cnt isn't changing so loop counter is added to it.
	 */
	क्रम (i = 0; i < paging_cnt; i++) अणु
		/* access FW with +2 to make up क्रम lmac & umac separators */
		पूर्णांक fw_idx = dram->fw_cnt + i + 2;

		ret = iwl_pcie_ctxt_info_alloc_dma(trans, fw->sec[fw_idx].data,
						   fw->sec[fw_idx].len,
						   &dram->paging[i]);
		अगर (ret)
			वापस ret;

		ctxt_dram->भव_img[i] =
			cpu_to_le64(dram->paging[i].physical);
		dram->paging_cnt++;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक iwl_pcie_ctxt_info_init(काष्ठा iwl_trans *trans,
			    स्थिर काष्ठा fw_img *fw)
अणु
	काष्ठा iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	काष्ठा iwl_context_info *ctxt_info;
	काष्ठा iwl_context_info_rbd_cfg *rx_cfg;
	u32 control_flags = 0, rb_size;
	dma_addr_t phys;
	पूर्णांक ret;

	ctxt_info = iwl_pcie_ctxt_info_dma_alloc_coherent(trans,
							  माप(*ctxt_info),
							  &phys);
	अगर (!ctxt_info)
		वापस -ENOMEM;

	trans_pcie->ctxt_info_dma_addr = phys;

	ctxt_info->version.version = 0;
	ctxt_info->version.mac_id =
		cpu_to_le16((u16)iwl_पढ़ो32(trans, CSR_HW_REV));
	/* size is in DWs */
	ctxt_info->version.size = cpu_to_le16(माप(*ctxt_info) / 4);

	चयन (trans_pcie->rx_buf_size) अणु
	हाल IWL_AMSDU_2K:
		rb_size = IWL_CTXT_INFO_RB_SIZE_2K;
		अवरोध;
	हाल IWL_AMSDU_4K:
		rb_size = IWL_CTXT_INFO_RB_SIZE_4K;
		अवरोध;
	हाल IWL_AMSDU_8K:
		rb_size = IWL_CTXT_INFO_RB_SIZE_8K;
		अवरोध;
	हाल IWL_AMSDU_12K:
		rb_size = IWL_CTXT_INFO_RB_SIZE_16K;
		अवरोध;
	शेष:
		WARN_ON(1);
		rb_size = IWL_CTXT_INFO_RB_SIZE_4K;
	पूर्ण

	WARN_ON(RX_QUEUE_CB_SIZE(trans->cfg->num_rbds) > 12);
	control_flags = IWL_CTXT_INFO_TFD_FORMAT_LONG;
	control_flags |=
		u32_encode_bits(RX_QUEUE_CB_SIZE(trans->cfg->num_rbds),
				IWL_CTXT_INFO_RB_CB_SIZE);
	control_flags |= u32_encode_bits(rb_size, IWL_CTXT_INFO_RB_SIZE);
	ctxt_info->control.control_flags = cpu_to_le32(control_flags);

	/* initialize RX शेष queue */
	rx_cfg = &ctxt_info->rbd_cfg;
	rx_cfg->मुक्त_rbd_addr = cpu_to_le64(trans_pcie->rxq->bd_dma);
	rx_cfg->used_rbd_addr = cpu_to_le64(trans_pcie->rxq->used_bd_dma);
	rx_cfg->status_wr_ptr = cpu_to_le64(trans_pcie->rxq->rb_stts_dma);

	/* initialize TX command queue */
	ctxt_info->hcmd_cfg.cmd_queue_addr =
		cpu_to_le64(trans->txqs.txq[trans->txqs.cmd.q_id]->dma_addr);
	ctxt_info->hcmd_cfg.cmd_queue_size =
		TFD_QUEUE_CB_SIZE(IWL_CMD_QUEUE_SIZE);

	/* allocate ucode sections in dram and set addresses */
	ret = iwl_pcie_init_fw_sec(trans, fw, &ctxt_info->dram);
	अगर (ret) अणु
		dma_मुक्त_coherent(trans->dev, माप(*trans_pcie->ctxt_info),
				  ctxt_info, trans_pcie->ctxt_info_dma_addr);
		वापस ret;
	पूर्ण

	trans_pcie->ctxt_info = ctxt_info;

	iwl_enable_fw_load_पूर्णांक_ctx_info(trans);

	/* Configure debug, अगर exists */
	अगर (iwl_pcie_dbg_on(trans))
		iwl_pcie_apply_destination(trans);

	/* kick FW self load */
	iwl_ग_लिखो64(trans, CSR_CTXT_INFO_BA, trans_pcie->ctxt_info_dma_addr);

	/* Context info will be released upon alive or failure to get one */

	वापस 0;
पूर्ण

व्योम iwl_pcie_ctxt_info_मुक्त(काष्ठा iwl_trans *trans)
अणु
	काष्ठा iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);

	अगर (!trans_pcie->ctxt_info)
		वापस;

	dma_मुक्त_coherent(trans->dev, माप(*trans_pcie->ctxt_info),
			  trans_pcie->ctxt_info,
			  trans_pcie->ctxt_info_dma_addr);
	trans_pcie->ctxt_info_dma_addr = 0;
	trans_pcie->ctxt_info = शून्य;

	iwl_pcie_ctxt_info_मुक्त_fw_img(trans);
पूर्ण
