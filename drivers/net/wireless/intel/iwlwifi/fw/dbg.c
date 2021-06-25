<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/*
 * Copyright (C) 2005-2014, 2018-2021 Intel Corporation
 * Copyright (C) 2013-2015 Intel Mobile Communications GmbH
 * Copyright (C) 2015-2017 Intel Deutschland GmbH
 */
#समावेश <linux/devcoredump.h>
#समावेश "iwl-drv.h"
#समावेश "runtime.h"
#समावेश "dbg.h"
#समावेश "debugfs.h"
#समावेश "iwl-io.h"
#समावेश "iwl-prph.h"
#समावेश "iwl-csr.h"

/**
 * काष्ठा iwl_fw_dump_ptrs - set of poपूर्णांकers needed क्रम the fw-error-dump
 *
 * @fwrt_ptr: poपूर्णांकer to the buffer coming from fwrt
 * @trans_ptr: poपूर्णांकer to काष्ठा %iwl_trans_dump_data which contains the
 *	transport's data.
 * @trans_len: length of the valid data in trans_ptr
 * @fwrt_len: length of the valid data in fwrt_ptr
 */
काष्ठा iwl_fw_dump_ptrs अणु
	काष्ठा iwl_trans_dump_data *trans_ptr;
	व्योम *fwrt_ptr;
	u32 fwrt_len;
पूर्ण;

#घोषणा RADIO_REG_MAX_READ 0x2ad
अटल व्योम iwl_पढ़ो_radio_regs(काष्ठा iwl_fw_runसमय *fwrt,
				काष्ठा iwl_fw_error_dump_data **dump_data)
अणु
	u8 *pos = (व्योम *)(*dump_data)->data;
	पूर्णांक i;

	IWL_DEBUG_INFO(fwrt, "WRT radio registers dump\n");

	अगर (!iwl_trans_grab_nic_access(fwrt->trans))
		वापस;

	(*dump_data)->type = cpu_to_le32(IWL_FW_ERROR_DUMP_RADIO_REG);
	(*dump_data)->len = cpu_to_le32(RADIO_REG_MAX_READ);

	क्रम (i = 0; i < RADIO_REG_MAX_READ; i++) अणु
		u32 rd_cmd = RADIO_RSP_RD_CMD;

		rd_cmd |= i << RADIO_RSP_ADDR_POS;
		iwl_ग_लिखो_prph_no_grab(fwrt->trans, RSP_RADIO_CMD, rd_cmd);
		*pos = (u8)iwl_पढ़ो_prph_no_grab(fwrt->trans, RSP_RADIO_RDDAT);

		pos++;
	पूर्ण

	*dump_data = iwl_fw_error_next_data(*dump_data);

	iwl_trans_release_nic_access(fwrt->trans);
पूर्ण

अटल व्योम iwl_fwrt_dump_rxf(काष्ठा iwl_fw_runसमय *fwrt,
			      काष्ठा iwl_fw_error_dump_data **dump_data,
			      पूर्णांक size, u32 offset, पूर्णांक fअगरo_num)
अणु
	काष्ठा iwl_fw_error_dump_fअगरo *fअगरo_hdr;
	u32 *fअगरo_data;
	u32 fअगरo_len;
	पूर्णांक i;

	fअगरo_hdr = (व्योम *)(*dump_data)->data;
	fअगरo_data = (व्योम *)fअगरo_hdr->data;
	fअगरo_len = size;

	/* No need to try to पढ़ो the data अगर the length is 0 */
	अगर (fअगरo_len == 0)
		वापस;

	/* Add a TLV क्रम the RXF */
	(*dump_data)->type = cpu_to_le32(IWL_FW_ERROR_DUMP_RXF);
	(*dump_data)->len = cpu_to_le32(fअगरo_len + माप(*fअगरo_hdr));

	fअगरo_hdr->fअगरo_num = cpu_to_le32(fअगरo_num);
	fअगरo_hdr->available_bytes =
		cpu_to_le32(iwl_trans_पढ़ो_prph(fwrt->trans,
						RXF_RD_D_SPACE + offset));
	fअगरo_hdr->wr_ptr =
		cpu_to_le32(iwl_trans_पढ़ो_prph(fwrt->trans,
						RXF_RD_WR_PTR + offset));
	fअगरo_hdr->rd_ptr =
		cpu_to_le32(iwl_trans_पढ़ो_prph(fwrt->trans,
						RXF_RD_RD_PTR + offset));
	fअगरo_hdr->fence_ptr =
		cpu_to_le32(iwl_trans_पढ़ो_prph(fwrt->trans,
						RXF_RD_FENCE_PTR + offset));
	fअगरo_hdr->fence_mode =
		cpu_to_le32(iwl_trans_पढ़ो_prph(fwrt->trans,
						RXF_SET_FENCE_MODE + offset));

	/* Lock fence */
	iwl_trans_ग_लिखो_prph(fwrt->trans, RXF_SET_FENCE_MODE + offset, 0x1);
	/* Set fence poपूर्णांकer to the same place like WR poपूर्णांकer */
	iwl_trans_ग_लिखो_prph(fwrt->trans, RXF_LD_WR2FENCE + offset, 0x1);
	/* Set fence offset */
	iwl_trans_ग_लिखो_prph(fwrt->trans,
			     RXF_LD_FENCE_OFFSET_ADDR + offset, 0x0);

	/* Read FIFO */
	fअगरo_len /= माप(u32); /* Size in DWORDS */
	क्रम (i = 0; i < fअगरo_len; i++)
		fअगरo_data[i] = iwl_trans_पढ़ो_prph(fwrt->trans,
						 RXF_FIFO_RD_FENCE_INC +
						 offset);
	*dump_data = iwl_fw_error_next_data(*dump_data);
पूर्ण

अटल व्योम iwl_fwrt_dump_txf(काष्ठा iwl_fw_runसमय *fwrt,
			      काष्ठा iwl_fw_error_dump_data **dump_data,
			      पूर्णांक size, u32 offset, पूर्णांक fअगरo_num)
अणु
	काष्ठा iwl_fw_error_dump_fअगरo *fअगरo_hdr;
	u32 *fअगरo_data;
	u32 fअगरo_len;
	पूर्णांक i;

	fअगरo_hdr = (व्योम *)(*dump_data)->data;
	fअगरo_data = (व्योम *)fअगरo_hdr->data;
	fअगरo_len = size;

	/* No need to try to पढ़ो the data अगर the length is 0 */
	अगर (fअगरo_len == 0)
		वापस;

	/* Add a TLV क्रम the FIFO */
	(*dump_data)->type = cpu_to_le32(IWL_FW_ERROR_DUMP_TXF);
	(*dump_data)->len = cpu_to_le32(fअगरo_len + माप(*fअगरo_hdr));

	fअगरo_hdr->fअगरo_num = cpu_to_le32(fअगरo_num);
	fअगरo_hdr->available_bytes =
		cpu_to_le32(iwl_trans_पढ़ो_prph(fwrt->trans,
						TXF_FIFO_ITEM_CNT + offset));
	fअगरo_hdr->wr_ptr =
		cpu_to_le32(iwl_trans_पढ़ो_prph(fwrt->trans,
						TXF_WR_PTR + offset));
	fअगरo_hdr->rd_ptr =
		cpu_to_le32(iwl_trans_पढ़ो_prph(fwrt->trans,
						TXF_RD_PTR + offset));
	fअगरo_hdr->fence_ptr =
		cpu_to_le32(iwl_trans_पढ़ो_prph(fwrt->trans,
						TXF_FENCE_PTR + offset));
	fअगरo_hdr->fence_mode =
		cpu_to_le32(iwl_trans_पढ़ो_prph(fwrt->trans,
						TXF_LOCK_FENCE + offset));

	/* Set the TXF_READ_MODIFY_ADDR to TXF_WR_PTR */
	iwl_trans_ग_लिखो_prph(fwrt->trans, TXF_READ_MODIFY_ADDR + offset,
			     TXF_WR_PTR + offset);

	/* Dummy-पढ़ो to advance the पढ़ो poपूर्णांकer to the head */
	iwl_trans_पढ़ो_prph(fwrt->trans, TXF_READ_MODIFY_DATA + offset);

	/* Read FIFO */
	fअगरo_len /= माप(u32); /* Size in DWORDS */
	क्रम (i = 0; i < fअगरo_len; i++)
		fअगरo_data[i] = iwl_trans_पढ़ो_prph(fwrt->trans,
						  TXF_READ_MODIFY_DATA +
						  offset);
	*dump_data = iwl_fw_error_next_data(*dump_data);
पूर्ण

अटल व्योम iwl_fw_dump_rxf(काष्ठा iwl_fw_runसमय *fwrt,
			    काष्ठा iwl_fw_error_dump_data **dump_data)
अणु
	काष्ठा iwl_fwrt_shared_mem_cfg *cfg = &fwrt->smem_cfg;

	IWL_DEBUG_INFO(fwrt, "WRT RX FIFO dump\n");

	अगर (!iwl_trans_grab_nic_access(fwrt->trans))
		वापस;

	अगर (iwl_fw_dbg_type_on(fwrt, IWL_FW_ERROR_DUMP_RXF)) अणु
		/* Pull RXF1 */
		iwl_fwrt_dump_rxf(fwrt, dump_data,
				  cfg->lmac[0].rxfअगरo1_size, 0, 0);
		/* Pull RXF2 */
		iwl_fwrt_dump_rxf(fwrt, dump_data, cfg->rxfअगरo2_size,
				  RXF_DIFF_FROM_PREV +
				  fwrt->trans->trans_cfg->umac_prph_offset, 1);
		/* Pull LMAC2 RXF1 */
		अगर (fwrt->smem_cfg.num_lmacs > 1)
			iwl_fwrt_dump_rxf(fwrt, dump_data,
					  cfg->lmac[1].rxfअगरo1_size,
					  LMAC2_PRPH_OFFSET, 2);
	पूर्ण

	iwl_trans_release_nic_access(fwrt->trans);
पूर्ण

अटल व्योम iwl_fw_dump_txf(काष्ठा iwl_fw_runसमय *fwrt,
			    काष्ठा iwl_fw_error_dump_data **dump_data)
अणु
	काष्ठा iwl_fw_error_dump_fअगरo *fअगरo_hdr;
	काष्ठा iwl_fwrt_shared_mem_cfg *cfg = &fwrt->smem_cfg;
	u32 *fअगरo_data;
	u32 fअगरo_len;
	पूर्णांक i, j;

	IWL_DEBUG_INFO(fwrt, "WRT TX FIFO dump\n");

	अगर (!iwl_trans_grab_nic_access(fwrt->trans))
		वापस;

	अगर (iwl_fw_dbg_type_on(fwrt, IWL_FW_ERROR_DUMP_TXF)) अणु
		/* Pull TXF data from LMAC1 */
		क्रम (i = 0; i < fwrt->smem_cfg.num_txfअगरo_entries; i++) अणु
			/* Mark the number of TXF we're pulling now */
			iwl_trans_ग_लिखो_prph(fwrt->trans, TXF_LARC_NUM, i);
			iwl_fwrt_dump_txf(fwrt, dump_data,
					  cfg->lmac[0].txfअगरo_size[i], 0, i);
		पूर्ण

		/* Pull TXF data from LMAC2 */
		अगर (fwrt->smem_cfg.num_lmacs > 1) अणु
			क्रम (i = 0; i < fwrt->smem_cfg.num_txfअगरo_entries;
			     i++) अणु
				/* Mark the number of TXF we're pulling now */
				iwl_trans_ग_लिखो_prph(fwrt->trans,
						     TXF_LARC_NUM +
						     LMAC2_PRPH_OFFSET, i);
				iwl_fwrt_dump_txf(fwrt, dump_data,
						  cfg->lmac[1].txfअगरo_size[i],
						  LMAC2_PRPH_OFFSET,
						  i + cfg->num_txfअगरo_entries);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (iwl_fw_dbg_type_on(fwrt, IWL_FW_ERROR_DUMP_INTERNAL_TXF) &&
	    fw_has_capa(&fwrt->fw->ucode_capa,
			IWL_UCODE_TLV_CAPA_EXTEND_SHARED_MEM_CFG)) अणु
		/* Pull UMAC पूर्णांकernal TXF data from all TXFs */
		क्रम (i = 0;
		     i < ARRAY_SIZE(fwrt->smem_cfg.पूर्णांकernal_txfअगरo_size);
		     i++) अणु
			fअगरo_hdr = (व्योम *)(*dump_data)->data;
			fअगरo_data = (व्योम *)fअगरo_hdr->data;
			fअगरo_len = fwrt->smem_cfg.पूर्णांकernal_txfअगरo_size[i];

			/* No need to try to पढ़ो the data अगर the length is 0 */
			अगर (fअगरo_len == 0)
				जारी;

			/* Add a TLV क्रम the पूर्णांकernal FIFOs */
			(*dump_data)->type =
				cpu_to_le32(IWL_FW_ERROR_DUMP_INTERNAL_TXF);
			(*dump_data)->len =
				cpu_to_le32(fअगरo_len + माप(*fअगरo_hdr));

			fअगरo_hdr->fअगरo_num = cpu_to_le32(i);

			/* Mark the number of TXF we're pulling now */
			iwl_trans_ग_लिखो_prph(fwrt->trans, TXF_CPU2_NUM, i +
				fwrt->smem_cfg.num_txfअगरo_entries);

			fअगरo_hdr->available_bytes =
				cpu_to_le32(iwl_trans_पढ़ो_prph(fwrt->trans,
								TXF_CPU2_FIFO_ITEM_CNT));
			fअगरo_hdr->wr_ptr =
				cpu_to_le32(iwl_trans_पढ़ो_prph(fwrt->trans,
								TXF_CPU2_WR_PTR));
			fअगरo_hdr->rd_ptr =
				cpu_to_le32(iwl_trans_पढ़ो_prph(fwrt->trans,
								TXF_CPU2_RD_PTR));
			fअगरo_hdr->fence_ptr =
				cpu_to_le32(iwl_trans_पढ़ो_prph(fwrt->trans,
								TXF_CPU2_FENCE_PTR));
			fअगरo_hdr->fence_mode =
				cpu_to_le32(iwl_trans_पढ़ो_prph(fwrt->trans,
								TXF_CPU2_LOCK_FENCE));

			/* Set TXF_CPU2_READ_MODIFY_ADDR to TXF_CPU2_WR_PTR */
			iwl_trans_ग_लिखो_prph(fwrt->trans,
					     TXF_CPU2_READ_MODIFY_ADDR,
					     TXF_CPU2_WR_PTR);

			/* Dummy-पढ़ो to advance the पढ़ो poपूर्णांकer to head */
			iwl_trans_पढ़ो_prph(fwrt->trans,
					    TXF_CPU2_READ_MODIFY_DATA);

			/* Read FIFO */
			fअगरo_len /= माप(u32); /* Size in DWORDS */
			क्रम (j = 0; j < fअगरo_len; j++)
				fअगरo_data[j] =
					iwl_trans_पढ़ो_prph(fwrt->trans,
							    TXF_CPU2_READ_MODIFY_DATA);
			*dump_data = iwl_fw_error_next_data(*dump_data);
		पूर्ण
	पूर्ण

	iwl_trans_release_nic_access(fwrt->trans);
पूर्ण

#घोषणा IWL8260_ICCM_OFFSET		0x44000 /* Only क्रम B-step */
#घोषणा IWL8260_ICCM_LEN		0xC000 /* Only क्रम B-step */

काष्ठा iwl_prph_range अणु
	u32 start, end;
पूर्ण;

अटल स्थिर काष्ठा iwl_prph_range iwl_prph_dump_addr_comm[] = अणु
	अणु .start = 0x00a00000, .end = 0x00a00000 पूर्ण,
	अणु .start = 0x00a0000c, .end = 0x00a00024 पूर्ण,
	अणु .start = 0x00a0002c, .end = 0x00a0003c पूर्ण,
	अणु .start = 0x00a00410, .end = 0x00a00418 पूर्ण,
	अणु .start = 0x00a00420, .end = 0x00a00420 पूर्ण,
	अणु .start = 0x00a00428, .end = 0x00a00428 पूर्ण,
	अणु .start = 0x00a00430, .end = 0x00a0043c पूर्ण,
	अणु .start = 0x00a00444, .end = 0x00a00444 पूर्ण,
	अणु .start = 0x00a004c0, .end = 0x00a004cc पूर्ण,
	अणु .start = 0x00a004d8, .end = 0x00a004d8 पूर्ण,
	अणु .start = 0x00a004e0, .end = 0x00a004f0 पूर्ण,
	अणु .start = 0x00a00840, .end = 0x00a00840 पूर्ण,
	अणु .start = 0x00a00850, .end = 0x00a00858 पूर्ण,
	अणु .start = 0x00a01004, .end = 0x00a01008 पूर्ण,
	अणु .start = 0x00a01010, .end = 0x00a01010 पूर्ण,
	अणु .start = 0x00a01018, .end = 0x00a01018 पूर्ण,
	अणु .start = 0x00a01024, .end = 0x00a01024 पूर्ण,
	अणु .start = 0x00a0102c, .end = 0x00a01034 पूर्ण,
	अणु .start = 0x00a0103c, .end = 0x00a01040 पूर्ण,
	अणु .start = 0x00a01048, .end = 0x00a01094 पूर्ण,
	अणु .start = 0x00a01c00, .end = 0x00a01c20 पूर्ण,
	अणु .start = 0x00a01c58, .end = 0x00a01c58 पूर्ण,
	अणु .start = 0x00a01c7c, .end = 0x00a01c7c पूर्ण,
	अणु .start = 0x00a01c28, .end = 0x00a01c54 पूर्ण,
	अणु .start = 0x00a01c5c, .end = 0x00a01c5c पूर्ण,
	अणु .start = 0x00a01c60, .end = 0x00a01cdc पूर्ण,
	अणु .start = 0x00a01ce0, .end = 0x00a01d0c पूर्ण,
	अणु .start = 0x00a01d18, .end = 0x00a01d20 पूर्ण,
	अणु .start = 0x00a01d2c, .end = 0x00a01d30 पूर्ण,
	अणु .start = 0x00a01d40, .end = 0x00a01d5c पूर्ण,
	अणु .start = 0x00a01d80, .end = 0x00a01d80 पूर्ण,
	अणु .start = 0x00a01d98, .end = 0x00a01d9c पूर्ण,
	अणु .start = 0x00a01da8, .end = 0x00a01da8 पूर्ण,
	अणु .start = 0x00a01db8, .end = 0x00a01df4 पूर्ण,
	अणु .start = 0x00a01dc0, .end = 0x00a01dfc पूर्ण,
	अणु .start = 0x00a01e00, .end = 0x00a01e2c पूर्ण,
	अणु .start = 0x00a01e40, .end = 0x00a01e60 पूर्ण,
	अणु .start = 0x00a01e68, .end = 0x00a01e6c पूर्ण,
	अणु .start = 0x00a01e74, .end = 0x00a01e74 पूर्ण,
	अणु .start = 0x00a01e84, .end = 0x00a01e90 पूर्ण,
	अणु .start = 0x00a01e9c, .end = 0x00a01ec4 पूर्ण,
	अणु .start = 0x00a01ed0, .end = 0x00a01ee0 पूर्ण,
	अणु .start = 0x00a01f00, .end = 0x00a01f1c पूर्ण,
	अणु .start = 0x00a01f44, .end = 0x00a01ffc पूर्ण,
	अणु .start = 0x00a02000, .end = 0x00a02048 पूर्ण,
	अणु .start = 0x00a02068, .end = 0x00a020f0 पूर्ण,
	अणु .start = 0x00a02100, .end = 0x00a02118 पूर्ण,
	अणु .start = 0x00a02140, .end = 0x00a0214c पूर्ण,
	अणु .start = 0x00a02168, .end = 0x00a0218c पूर्ण,
	अणु .start = 0x00a021c0, .end = 0x00a021c0 पूर्ण,
	अणु .start = 0x00a02400, .end = 0x00a02410 पूर्ण,
	अणु .start = 0x00a02418, .end = 0x00a02420 पूर्ण,
	अणु .start = 0x00a02428, .end = 0x00a0242c पूर्ण,
	अणु .start = 0x00a02434, .end = 0x00a02434 पूर्ण,
	अणु .start = 0x00a02440, .end = 0x00a02460 पूर्ण,
	अणु .start = 0x00a02468, .end = 0x00a024b0 पूर्ण,
	अणु .start = 0x00a024c8, .end = 0x00a024cc पूर्ण,
	अणु .start = 0x00a02500, .end = 0x00a02504 पूर्ण,
	अणु .start = 0x00a0250c, .end = 0x00a02510 पूर्ण,
	अणु .start = 0x00a02540, .end = 0x00a02554 पूर्ण,
	अणु .start = 0x00a02580, .end = 0x00a025f4 पूर्ण,
	अणु .start = 0x00a02600, .end = 0x00a0260c पूर्ण,
	अणु .start = 0x00a02648, .end = 0x00a02650 पूर्ण,
	अणु .start = 0x00a02680, .end = 0x00a02680 पूर्ण,
	अणु .start = 0x00a026c0, .end = 0x00a026d0 पूर्ण,
	अणु .start = 0x00a02700, .end = 0x00a0270c पूर्ण,
	अणु .start = 0x00a02804, .end = 0x00a02804 पूर्ण,
	अणु .start = 0x00a02818, .end = 0x00a0281c पूर्ण,
	अणु .start = 0x00a02c00, .end = 0x00a02db4 पूर्ण,
	अणु .start = 0x00a02df4, .end = 0x00a02fb0 पूर्ण,
	अणु .start = 0x00a03000, .end = 0x00a03014 पूर्ण,
	अणु .start = 0x00a0301c, .end = 0x00a0302c पूर्ण,
	अणु .start = 0x00a03034, .end = 0x00a03038 पूर्ण,
	अणु .start = 0x00a03040, .end = 0x00a03048 पूर्ण,
	अणु .start = 0x00a03060, .end = 0x00a03068 पूर्ण,
	अणु .start = 0x00a03070, .end = 0x00a03074 पूर्ण,
	अणु .start = 0x00a0307c, .end = 0x00a0307c पूर्ण,
	अणु .start = 0x00a03080, .end = 0x00a03084 पूर्ण,
	अणु .start = 0x00a0308c, .end = 0x00a03090 पूर्ण,
	अणु .start = 0x00a03098, .end = 0x00a03098 पूर्ण,
	अणु .start = 0x00a030a0, .end = 0x00a030a0 पूर्ण,
	अणु .start = 0x00a030a8, .end = 0x00a030b4 पूर्ण,
	अणु .start = 0x00a030bc, .end = 0x00a030bc पूर्ण,
	अणु .start = 0x00a030c0, .end = 0x00a0312c पूर्ण,
	अणु .start = 0x00a03c00, .end = 0x00a03c5c पूर्ण,
	अणु .start = 0x00a04400, .end = 0x00a04454 पूर्ण,
	अणु .start = 0x00a04460, .end = 0x00a04474 पूर्ण,
	अणु .start = 0x00a044c0, .end = 0x00a044ec पूर्ण,
	अणु .start = 0x00a04500, .end = 0x00a04504 पूर्ण,
	अणु .start = 0x00a04510, .end = 0x00a04538 पूर्ण,
	अणु .start = 0x00a04540, .end = 0x00a04548 पूर्ण,
	अणु .start = 0x00a04560, .end = 0x00a0457c पूर्ण,
	अणु .start = 0x00a04590, .end = 0x00a04598 पूर्ण,
	अणु .start = 0x00a045c0, .end = 0x00a045f4 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा iwl_prph_range iwl_prph_dump_addr_9000[] = अणु
	अणु .start = 0x00a05c00, .end = 0x00a05c18 पूर्ण,
	अणु .start = 0x00a05400, .end = 0x00a056e8 पूर्ण,
	अणु .start = 0x00a08000, .end = 0x00a098bc पूर्ण,
	अणु .start = 0x00a02400, .end = 0x00a02758 पूर्ण,
	अणु .start = 0x00a04764, .end = 0x00a0476c पूर्ण,
	अणु .start = 0x00a04770, .end = 0x00a04774 पूर्ण,
	अणु .start = 0x00a04620, .end = 0x00a04624 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा iwl_prph_range iwl_prph_dump_addr_22000[] = अणु
	अणु .start = 0x00a00000, .end = 0x00a00000 पूर्ण,
	अणु .start = 0x00a0000c, .end = 0x00a00024 पूर्ण,
	अणु .start = 0x00a0002c, .end = 0x00a00034 पूर्ण,
	अणु .start = 0x00a0003c, .end = 0x00a0003c पूर्ण,
	अणु .start = 0x00a00410, .end = 0x00a00418 पूर्ण,
	अणु .start = 0x00a00420, .end = 0x00a00420 पूर्ण,
	अणु .start = 0x00a00428, .end = 0x00a00428 पूर्ण,
	अणु .start = 0x00a00430, .end = 0x00a0043c पूर्ण,
	अणु .start = 0x00a00444, .end = 0x00a00444 पूर्ण,
	अणु .start = 0x00a00840, .end = 0x00a00840 पूर्ण,
	अणु .start = 0x00a00850, .end = 0x00a00858 पूर्ण,
	अणु .start = 0x00a01004, .end = 0x00a01008 पूर्ण,
	अणु .start = 0x00a01010, .end = 0x00a01010 पूर्ण,
	अणु .start = 0x00a01018, .end = 0x00a01018 पूर्ण,
	अणु .start = 0x00a01024, .end = 0x00a01024 पूर्ण,
	अणु .start = 0x00a0102c, .end = 0x00a01034 पूर्ण,
	अणु .start = 0x00a0103c, .end = 0x00a01040 पूर्ण,
	अणु .start = 0x00a01048, .end = 0x00a01050 पूर्ण,
	अणु .start = 0x00a01058, .end = 0x00a01058 पूर्ण,
	अणु .start = 0x00a01060, .end = 0x00a01070 पूर्ण,
	अणु .start = 0x00a0108c, .end = 0x00a0108c पूर्ण,
	अणु .start = 0x00a01c20, .end = 0x00a01c28 पूर्ण,
	अणु .start = 0x00a01d10, .end = 0x00a01d10 पूर्ण,
	अणु .start = 0x00a01e28, .end = 0x00a01e2c पूर्ण,
	अणु .start = 0x00a01e60, .end = 0x00a01e60 पूर्ण,
	अणु .start = 0x00a01e80, .end = 0x00a01e80 पूर्ण,
	अणु .start = 0x00a01ea0, .end = 0x00a01ea0 पूर्ण,
	अणु .start = 0x00a02000, .end = 0x00a0201c पूर्ण,
	अणु .start = 0x00a02024, .end = 0x00a02024 पूर्ण,
	अणु .start = 0x00a02040, .end = 0x00a02048 पूर्ण,
	अणु .start = 0x00a020c0, .end = 0x00a020e0 पूर्ण,
	अणु .start = 0x00a02400, .end = 0x00a02404 पूर्ण,
	अणु .start = 0x00a0240c, .end = 0x00a02414 पूर्ण,
	अणु .start = 0x00a0241c, .end = 0x00a0243c पूर्ण,
	अणु .start = 0x00a02448, .end = 0x00a024bc पूर्ण,
	अणु .start = 0x00a024c4, .end = 0x00a024cc पूर्ण,
	अणु .start = 0x00a02508, .end = 0x00a02508 पूर्ण,
	अणु .start = 0x00a02510, .end = 0x00a02514 पूर्ण,
	अणु .start = 0x00a0251c, .end = 0x00a0251c पूर्ण,
	अणु .start = 0x00a0252c, .end = 0x00a0255c पूर्ण,
	अणु .start = 0x00a02564, .end = 0x00a025a0 पूर्ण,
	अणु .start = 0x00a025a8, .end = 0x00a025b4 पूर्ण,
	अणु .start = 0x00a025c0, .end = 0x00a025c0 पूर्ण,
	अणु .start = 0x00a025e8, .end = 0x00a025f4 पूर्ण,
	अणु .start = 0x00a02c08, .end = 0x00a02c18 पूर्ण,
	अणु .start = 0x00a02c2c, .end = 0x00a02c38 पूर्ण,
	अणु .start = 0x00a02c68, .end = 0x00a02c78 पूर्ण,
	अणु .start = 0x00a03000, .end = 0x00a03000 पूर्ण,
	अणु .start = 0x00a03010, .end = 0x00a03014 पूर्ण,
	अणु .start = 0x00a0301c, .end = 0x00a0302c पूर्ण,
	अणु .start = 0x00a03034, .end = 0x00a03038 पूर्ण,
	अणु .start = 0x00a03040, .end = 0x00a03044 पूर्ण,
	अणु .start = 0x00a03060, .end = 0x00a03068 पूर्ण,
	अणु .start = 0x00a03070, .end = 0x00a03070 पूर्ण,
	अणु .start = 0x00a0307c, .end = 0x00a03084 पूर्ण,
	अणु .start = 0x00a0308c, .end = 0x00a03090 पूर्ण,
	अणु .start = 0x00a03098, .end = 0x00a03098 पूर्ण,
	अणु .start = 0x00a030a0, .end = 0x00a030a0 पूर्ण,
	अणु .start = 0x00a030a8, .end = 0x00a030b4 पूर्ण,
	अणु .start = 0x00a030bc, .end = 0x00a030c0 पूर्ण,
	अणु .start = 0x00a030c8, .end = 0x00a030f4 पूर्ण,
	अणु .start = 0x00a03100, .end = 0x00a0312c पूर्ण,
	अणु .start = 0x00a03c00, .end = 0x00a03c5c पूर्ण,
	अणु .start = 0x00a04400, .end = 0x00a04454 पूर्ण,
	अणु .start = 0x00a04460, .end = 0x00a04474 पूर्ण,
	अणु .start = 0x00a044c0, .end = 0x00a044ec पूर्ण,
	अणु .start = 0x00a04500, .end = 0x00a04504 पूर्ण,
	अणु .start = 0x00a04510, .end = 0x00a04538 पूर्ण,
	अणु .start = 0x00a04540, .end = 0x00a04548 पूर्ण,
	अणु .start = 0x00a04560, .end = 0x00a04560 पूर्ण,
	अणु .start = 0x00a04570, .end = 0x00a0457c पूर्ण,
	अणु .start = 0x00a04590, .end = 0x00a04590 पूर्ण,
	अणु .start = 0x00a04598, .end = 0x00a04598 पूर्ण,
	अणु .start = 0x00a045c0, .end = 0x00a045f4 पूर्ण,
	अणु .start = 0x00a05c18, .end = 0x00a05c1c पूर्ण,
	अणु .start = 0x00a0c000, .end = 0x00a0c018 पूर्ण,
	अणु .start = 0x00a0c020, .end = 0x00a0c028 पूर्ण,
	अणु .start = 0x00a0c038, .end = 0x00a0c094 पूर्ण,
	अणु .start = 0x00a0c0c0, .end = 0x00a0c104 पूर्ण,
	अणु .start = 0x00a0c10c, .end = 0x00a0c118 पूर्ण,
	अणु .start = 0x00a0c150, .end = 0x00a0c174 पूर्ण,
	अणु .start = 0x00a0c17c, .end = 0x00a0c188 पूर्ण,
	अणु .start = 0x00a0c190, .end = 0x00a0c198 पूर्ण,
	अणु .start = 0x00a0c1a0, .end = 0x00a0c1a8 पूर्ण,
	अणु .start = 0x00a0c1b0, .end = 0x00a0c1b8 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा iwl_prph_range iwl_prph_dump_addr_ax210[] = अणु
	अणु .start = 0x00d03c00, .end = 0x00d03c64 पूर्ण,
	अणु .start = 0x00d05c18, .end = 0x00d05c1c पूर्ण,
	अणु .start = 0x00d0c000, .end = 0x00d0c174 पूर्ण,
पूर्ण;

अटल व्योम iwl_पढ़ो_prph_block(काष्ठा iwl_trans *trans, u32 start,
				u32 len_bytes, __le32 *data)
अणु
	u32 i;

	क्रम (i = 0; i < len_bytes; i += 4)
		*data++ = cpu_to_le32(iwl_पढ़ो_prph_no_grab(trans, start + i));
पूर्ण

अटल व्योम iwl_dump_prph(काष्ठा iwl_fw_runसमय *fwrt,
			  स्थिर काष्ठा iwl_prph_range *iwl_prph_dump_addr,
			  u32 range_len, व्योम *ptr)
अणु
	काष्ठा iwl_fw_error_dump_prph *prph;
	काष्ठा iwl_trans *trans = fwrt->trans;
	काष्ठा iwl_fw_error_dump_data **data =
		(काष्ठा iwl_fw_error_dump_data **)ptr;
	u32 i;

	अगर (!data)
		वापस;

	IWL_DEBUG_INFO(trans, "WRT PRPH dump\n");

	अगर (!iwl_trans_grab_nic_access(trans))
		वापस;

	क्रम (i = 0; i < range_len; i++) अणु
		/* The range includes both boundaries */
		पूर्णांक num_bytes_in_chunk = iwl_prph_dump_addr[i].end -
			 iwl_prph_dump_addr[i].start + 4;

		(*data)->type = cpu_to_le32(IWL_FW_ERROR_DUMP_PRPH);
		(*data)->len = cpu_to_le32(माप(*prph) +
					num_bytes_in_chunk);
		prph = (व्योम *)(*data)->data;
		prph->prph_start = cpu_to_le32(iwl_prph_dump_addr[i].start);

		iwl_पढ़ो_prph_block(trans, iwl_prph_dump_addr[i].start,
				    /* our range is inclusive, hence + 4 */
				    iwl_prph_dump_addr[i].end -
				    iwl_prph_dump_addr[i].start + 4,
				    (व्योम *)prph->data);

		*data = iwl_fw_error_next_data(*data);
	पूर्ण

	iwl_trans_release_nic_access(trans);
पूर्ण

/*
 * alloc_sgtable - allocates scallerlist table in the given size,
 * fills it with pages and वापसs it
 * @size: the size (in bytes) of the table
*/
अटल काष्ठा scatterlist *alloc_sgtable(पूर्णांक size)
अणु
	पूर्णांक alloc_size, nents, i;
	काष्ठा page *new_page;
	काष्ठा scatterlist *iter;
	काष्ठा scatterlist *table;

	nents = DIV_ROUND_UP(size, PAGE_SIZE);
	table = kसुस्मृति(nents, माप(*table), GFP_KERNEL);
	अगर (!table)
		वापस शून्य;
	sg_init_table(table, nents);
	iter = table;
	क्रम_each_sg(table, iter, sg_nents(table), i) अणु
		new_page = alloc_page(GFP_KERNEL);
		अगर (!new_page) अणु
			/* release all previous allocated pages in the table */
			iter = table;
			क्रम_each_sg(table, iter, sg_nents(table), i) अणु
				new_page = sg_page(iter);
				अगर (new_page)
					__मुक्त_page(new_page);
			पूर्ण
			kमुक्त(table);
			वापस शून्य;
		पूर्ण
		alloc_size = min_t(पूर्णांक, size, PAGE_SIZE);
		size -= PAGE_SIZE;
		sg_set_page(iter, new_page, alloc_size, 0);
	पूर्ण
	वापस table;
पूर्ण

अटल व्योम iwl_fw_get_prph_len(काष्ठा iwl_fw_runसमय *fwrt,
				स्थिर काष्ठा iwl_prph_range *iwl_prph_dump_addr,
				u32 range_len, व्योम *ptr)
अणु
	u32 *prph_len = (u32 *)ptr;
	पूर्णांक i, num_bytes_in_chunk;

	अगर (!prph_len)
		वापस;

	क्रम (i = 0; i < range_len; i++) अणु
		/* The range includes both boundaries */
		num_bytes_in_chunk =
			iwl_prph_dump_addr[i].end -
			iwl_prph_dump_addr[i].start + 4;

		*prph_len += माप(काष्ठा iwl_fw_error_dump_data) +
			माप(काष्ठा iwl_fw_error_dump_prph) +
			num_bytes_in_chunk;
	पूर्ण
पूर्ण

अटल व्योम iwl_fw_prph_handler(काष्ठा iwl_fw_runसमय *fwrt, व्योम *ptr,
				व्योम (*handler)(काष्ठा iwl_fw_runसमय *,
						स्थिर काष्ठा iwl_prph_range *,
						u32, व्योम *))
अणु
	u32 range_len;

	अगर (fwrt->trans->trans_cfg->device_family >= IWL_DEVICE_FAMILY_AX210) अणु
		range_len = ARRAY_SIZE(iwl_prph_dump_addr_ax210);
		handler(fwrt, iwl_prph_dump_addr_ax210, range_len, ptr);
	पूर्ण अन्यथा अगर (fwrt->trans->trans_cfg->device_family >=
		   IWL_DEVICE_FAMILY_22000) अणु
		range_len = ARRAY_SIZE(iwl_prph_dump_addr_22000);
		handler(fwrt, iwl_prph_dump_addr_22000, range_len, ptr);
	पूर्ण अन्यथा अणु
		range_len = ARRAY_SIZE(iwl_prph_dump_addr_comm);
		handler(fwrt, iwl_prph_dump_addr_comm, range_len, ptr);

		अगर (fwrt->trans->trans_cfg->mq_rx_supported) अणु
			range_len = ARRAY_SIZE(iwl_prph_dump_addr_9000);
			handler(fwrt, iwl_prph_dump_addr_9000, range_len, ptr);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम iwl_fw_dump_mem(काष्ठा iwl_fw_runसमय *fwrt,
			    काष्ठा iwl_fw_error_dump_data **dump_data,
			    u32 len, u32 ofs, u32 type)
अणु
	काष्ठा iwl_fw_error_dump_mem *dump_mem;

	अगर (!len)
		वापस;

	(*dump_data)->type = cpu_to_le32(IWL_FW_ERROR_DUMP_MEM);
	(*dump_data)->len = cpu_to_le32(len + माप(*dump_mem));
	dump_mem = (व्योम *)(*dump_data)->data;
	dump_mem->type = cpu_to_le32(type);
	dump_mem->offset = cpu_to_le32(ofs);
	iwl_trans_पढ़ो_mem_bytes(fwrt->trans, ofs, dump_mem->data, len);
	*dump_data = iwl_fw_error_next_data(*dump_data);

	IWL_DEBUG_INFO(fwrt, "WRT memory dump. Type=%u\n", dump_mem->type);
पूर्ण

#घोषणा ADD_LEN(len, item_len, स्थिर_len) \
	करो अणुमाप_प्रकार item = item_len; len += (!!item) * स्थिर_len + item; पूर्ण \
	जबतक (0)

अटल पूर्णांक iwl_fw_rxf_len(काष्ठा iwl_fw_runसमय *fwrt,
			  काष्ठा iwl_fwrt_shared_mem_cfg *mem_cfg)
अणु
	माप_प्रकार hdr_len = माप(काष्ठा iwl_fw_error_dump_data) +
			 माप(काष्ठा iwl_fw_error_dump_fअगरo);
	u32 fअगरo_len = 0;
	पूर्णांक i;

	अगर (!iwl_fw_dbg_type_on(fwrt, IWL_FW_ERROR_DUMP_RXF))
		वापस 0;

	/* Count RXF2 size */
	ADD_LEN(fअगरo_len, mem_cfg->rxfअगरo2_size, hdr_len);

	/* Count RXF1 sizes */
	अगर (WARN_ON(mem_cfg->num_lmacs > MAX_NUM_LMAC))
		mem_cfg->num_lmacs = MAX_NUM_LMAC;

	क्रम (i = 0; i < mem_cfg->num_lmacs; i++)
		ADD_LEN(fअगरo_len, mem_cfg->lmac[i].rxfअगरo1_size, hdr_len);

	वापस fअगरo_len;
पूर्ण

अटल पूर्णांक iwl_fw_txf_len(काष्ठा iwl_fw_runसमय *fwrt,
			  काष्ठा iwl_fwrt_shared_mem_cfg *mem_cfg)
अणु
	माप_प्रकार hdr_len = माप(काष्ठा iwl_fw_error_dump_data) +
			 माप(काष्ठा iwl_fw_error_dump_fअगरo);
	u32 fअगरo_len = 0;
	पूर्णांक i;

	अगर (!iwl_fw_dbg_type_on(fwrt, IWL_FW_ERROR_DUMP_TXF))
		जाओ dump_पूर्णांकernal_txf;

	/* Count TXF sizes */
	अगर (WARN_ON(mem_cfg->num_lmacs > MAX_NUM_LMAC))
		mem_cfg->num_lmacs = MAX_NUM_LMAC;

	क्रम (i = 0; i < mem_cfg->num_lmacs; i++) अणु
		पूर्णांक j;

		क्रम (j = 0; j < mem_cfg->num_txfअगरo_entries; j++)
			ADD_LEN(fअगरo_len, mem_cfg->lmac[i].txfअगरo_size[j],
				hdr_len);
	पूर्ण

dump_पूर्णांकernal_txf:
	अगर (!(iwl_fw_dbg_type_on(fwrt, IWL_FW_ERROR_DUMP_INTERNAL_TXF) &&
	      fw_has_capa(&fwrt->fw->ucode_capa,
			  IWL_UCODE_TLV_CAPA_EXTEND_SHARED_MEM_CFG)))
		जाओ out;

	क्रम (i = 0; i < ARRAY_SIZE(mem_cfg->पूर्णांकernal_txfअगरo_size); i++)
		ADD_LEN(fअगरo_len, mem_cfg->पूर्णांकernal_txfअगरo_size[i], hdr_len);

out:
	वापस fअगरo_len;
पूर्ण

अटल व्योम iwl_dump_paging(काष्ठा iwl_fw_runसमय *fwrt,
			    काष्ठा iwl_fw_error_dump_data **data)
अणु
	पूर्णांक i;

	IWL_DEBUG_INFO(fwrt, "WRT paging dump\n");
	क्रम (i = 1; i < fwrt->num_of_paging_blk + 1; i++) अणु
		काष्ठा iwl_fw_error_dump_paging *paging;
		काष्ठा page *pages =
			fwrt->fw_paging_db[i].fw_paging_block;
		dma_addr_t addr = fwrt->fw_paging_db[i].fw_paging_phys;

		(*data)->type = cpu_to_le32(IWL_FW_ERROR_DUMP_PAGING);
		(*data)->len = cpu_to_le32(माप(*paging) +
					     PAGING_BLOCK_SIZE);
		paging =  (व्योम *)(*data)->data;
		paging->index = cpu_to_le32(i);
		dma_sync_single_क्रम_cpu(fwrt->trans->dev, addr,
					PAGING_BLOCK_SIZE,
					DMA_BIसूचीECTIONAL);
		स_नकल(paging->data, page_address(pages),
		       PAGING_BLOCK_SIZE);
		dma_sync_single_क्रम_device(fwrt->trans->dev, addr,
					   PAGING_BLOCK_SIZE,
					   DMA_BIसूचीECTIONAL);
		(*data) = iwl_fw_error_next_data(*data);
	पूर्ण
पूर्ण

अटल काष्ठा iwl_fw_error_dump_file *
iwl_fw_error_dump_file(काष्ठा iwl_fw_runसमय *fwrt,
		       काष्ठा iwl_fw_dump_ptrs *fw_error_dump,
		       काष्ठा iwl_fwrt_dump_data *data)
अणु
	काष्ठा iwl_fw_error_dump_file *dump_file;
	काष्ठा iwl_fw_error_dump_data *dump_data;
	काष्ठा iwl_fw_error_dump_info *dump_info;
	काष्ठा iwl_fw_error_dump_smem_cfg *dump_smem_cfg;
	काष्ठा iwl_fw_error_dump_trigger_desc *dump_trig;
	u32 sram_len, sram_ofs;
	स्थिर काष्ठा iwl_fw_dbg_mem_seg_tlv *fw_mem = fwrt->fw->dbg.mem_tlv;
	काष्ठा iwl_fwrt_shared_mem_cfg *mem_cfg = &fwrt->smem_cfg;
	u32 file_len, fअगरo_len = 0, prph_len = 0, radio_len = 0;
	u32 smem_len = fwrt->fw->dbg.n_mem_tlv ? 0 : fwrt->trans->cfg->smem_len;
	u32 sram2_len = fwrt->fw->dbg.n_mem_tlv ?
				0 : fwrt->trans->cfg->dccm2_len;
	पूर्णांक i;

	/* SRAM - include stack CCM अगर driver knows the values क्रम it */
	अगर (!fwrt->trans->cfg->dccm_offset || !fwrt->trans->cfg->dccm_len) अणु
		स्थिर काष्ठा fw_img *img;

		अगर (fwrt->cur_fw_img >= IWL_UCODE_TYPE_MAX)
			वापस शून्य;
		img = &fwrt->fw->img[fwrt->cur_fw_img];
		sram_ofs = img->sec[IWL_UCODE_SECTION_DATA].offset;
		sram_len = img->sec[IWL_UCODE_SECTION_DATA].len;
	पूर्ण अन्यथा अणु
		sram_ofs = fwrt->trans->cfg->dccm_offset;
		sram_len = fwrt->trans->cfg->dccm_len;
	पूर्ण

	/* पढ़ोing RXF/TXF sizes */
	अगर (test_bit(STATUS_FW_ERROR, &fwrt->trans->status)) अणु
		fअगरo_len = iwl_fw_rxf_len(fwrt, mem_cfg);
		fअगरo_len += iwl_fw_txf_len(fwrt, mem_cfg);

		/* Make room क्रम PRPH रेजिस्टरs */
		अगर (iwl_fw_dbg_type_on(fwrt, IWL_FW_ERROR_DUMP_PRPH))
			iwl_fw_prph_handler(fwrt, &prph_len,
					    iwl_fw_get_prph_len);

		अगर (fwrt->trans->trans_cfg->device_family ==
		    IWL_DEVICE_FAMILY_7000 &&
		    iwl_fw_dbg_type_on(fwrt, IWL_FW_ERROR_DUMP_RADIO_REG))
			radio_len = माप(*dump_data) + RADIO_REG_MAX_READ;
	पूर्ण

	file_len = माप(*dump_file) + fअगरo_len + prph_len + radio_len;

	अगर (iwl_fw_dbg_type_on(fwrt, IWL_FW_ERROR_DUMP_DEV_FW_INFO))
		file_len += माप(*dump_data) + माप(*dump_info);
	अगर (iwl_fw_dbg_type_on(fwrt, IWL_FW_ERROR_DUMP_MEM_CFG))
		file_len += माप(*dump_data) + माप(*dump_smem_cfg);

	अगर (iwl_fw_dbg_type_on(fwrt, IWL_FW_ERROR_DUMP_MEM)) अणु
		माप_प्रकार hdr_len = माप(*dump_data) +
				 माप(काष्ठा iwl_fw_error_dump_mem);

		/* Dump SRAM only अगर no mem_tlvs */
		अगर (!fwrt->fw->dbg.n_mem_tlv)
			ADD_LEN(file_len, sram_len, hdr_len);

		/* Make room क्रम all mem types that exist */
		ADD_LEN(file_len, smem_len, hdr_len);
		ADD_LEN(file_len, sram2_len, hdr_len);

		क्रम (i = 0; i < fwrt->fw->dbg.n_mem_tlv; i++)
			ADD_LEN(file_len, le32_to_cpu(fw_mem[i].len), hdr_len);
	पूर्ण

	/* Make room क्रम fw's भव image pages, अगर it exists */
	अगर (iwl_fw_dbg_is_paging_enabled(fwrt))
		file_len += fwrt->num_of_paging_blk *
			(माप(*dump_data) +
			 माप(काष्ठा iwl_fw_error_dump_paging) +
			 PAGING_BLOCK_SIZE);

	अगर (iwl_fw_dbg_is_d3_debug_enabled(fwrt) && fwrt->dump.d3_debug_data) अणु
		file_len += माप(*dump_data) +
			fwrt->trans->cfg->d3_debug_data_length * 2;
	पूर्ण

	/* If we only want a monitor dump, reset the file length */
	अगर (data->monitor_only) अणु
		file_len = माप(*dump_file) + माप(*dump_data) * 2 +
			   माप(*dump_info) + माप(*dump_smem_cfg);
	पूर्ण

	अगर (iwl_fw_dbg_type_on(fwrt, IWL_FW_ERROR_DUMP_ERROR_INFO) &&
	    data->desc)
		file_len += माप(*dump_data) + माप(*dump_trig) +
			data->desc->len;

	dump_file = vzalloc(file_len);
	अगर (!dump_file)
		वापस शून्य;

	fw_error_dump->fwrt_ptr = dump_file;

	dump_file->barker = cpu_to_le32(IWL_FW_ERROR_DUMP_BARKER);
	dump_data = (व्योम *)dump_file->data;

	अगर (iwl_fw_dbg_type_on(fwrt, IWL_FW_ERROR_DUMP_DEV_FW_INFO)) अणु
		dump_data->type = cpu_to_le32(IWL_FW_ERROR_DUMP_DEV_FW_INFO);
		dump_data->len = cpu_to_le32(माप(*dump_info));
		dump_info = (व्योम *)dump_data->data;
		dump_info->hw_type =
			cpu_to_le32(CSR_HW_REV_TYPE(fwrt->trans->hw_rev));
		dump_info->hw_step =
			cpu_to_le32(CSR_HW_REV_STEP(fwrt->trans->hw_rev));
		स_नकल(dump_info->fw_human_पढ़ोable, fwrt->fw->human_पढ़ोable,
		       माप(dump_info->fw_human_पढ़ोable));
		म_नकलन(dump_info->dev_human_पढ़ोable, fwrt->trans->name,
			माप(dump_info->dev_human_पढ़ोable) - 1);
		म_नकलन(dump_info->bus_human_पढ़ोable, fwrt->dev->bus->name,
			माप(dump_info->bus_human_पढ़ोable) - 1);
		dump_info->num_of_lmacs = fwrt->smem_cfg.num_lmacs;
		dump_info->lmac_err_id[0] =
			cpu_to_le32(fwrt->dump.lmac_err_id[0]);
		अगर (fwrt->smem_cfg.num_lmacs > 1)
			dump_info->lmac_err_id[1] =
				cpu_to_le32(fwrt->dump.lmac_err_id[1]);
		dump_info->umac_err_id = cpu_to_le32(fwrt->dump.umac_err_id);

		dump_data = iwl_fw_error_next_data(dump_data);
	पूर्ण

	अगर (iwl_fw_dbg_type_on(fwrt, IWL_FW_ERROR_DUMP_MEM_CFG)) अणु
		/* Dump shared memory configuration */
		dump_data->type = cpu_to_le32(IWL_FW_ERROR_DUMP_MEM_CFG);
		dump_data->len = cpu_to_le32(माप(*dump_smem_cfg));
		dump_smem_cfg = (व्योम *)dump_data->data;
		dump_smem_cfg->num_lmacs = cpu_to_le32(mem_cfg->num_lmacs);
		dump_smem_cfg->num_txfअगरo_entries =
			cpu_to_le32(mem_cfg->num_txfअगरo_entries);
		क्रम (i = 0; i < MAX_NUM_LMAC; i++) अणु
			पूर्णांक j;
			u32 *txf_size = mem_cfg->lmac[i].txfअगरo_size;

			क्रम (j = 0; j < TX_FIFO_MAX_NUM; j++)
				dump_smem_cfg->lmac[i].txfअगरo_size[j] =
					cpu_to_le32(txf_size[j]);
			dump_smem_cfg->lmac[i].rxfअगरo1_size =
				cpu_to_le32(mem_cfg->lmac[i].rxfअगरo1_size);
		पूर्ण
		dump_smem_cfg->rxfअगरo2_size =
			cpu_to_le32(mem_cfg->rxfअगरo2_size);
		dump_smem_cfg->पूर्णांकernal_txfअगरo_addr =
			cpu_to_le32(mem_cfg->पूर्णांकernal_txfअगरo_addr);
		क्रम (i = 0; i < TX_FIFO_INTERNAL_MAX_NUM; i++) अणु
			dump_smem_cfg->पूर्णांकernal_txfअगरo_size[i] =
				cpu_to_le32(mem_cfg->पूर्णांकernal_txfअगरo_size[i]);
		पूर्ण

		dump_data = iwl_fw_error_next_data(dump_data);
	पूर्ण

	/* We only dump the FIFOs अगर the FW is in error state */
	अगर (fअगरo_len) अणु
		iwl_fw_dump_rxf(fwrt, &dump_data);
		iwl_fw_dump_txf(fwrt, &dump_data);
	पूर्ण

	अगर (radio_len)
		iwl_पढ़ो_radio_regs(fwrt, &dump_data);

	अगर (iwl_fw_dbg_type_on(fwrt, IWL_FW_ERROR_DUMP_ERROR_INFO) &&
	    data->desc) अणु
		dump_data->type = cpu_to_le32(IWL_FW_ERROR_DUMP_ERROR_INFO);
		dump_data->len = cpu_to_le32(माप(*dump_trig) +
					     data->desc->len);
		dump_trig = (व्योम *)dump_data->data;
		स_नकल(dump_trig, &data->desc->trig_desc,
		       माप(*dump_trig) + data->desc->len);

		dump_data = iwl_fw_error_next_data(dump_data);
	पूर्ण

	/* In हाल we only want monitor dump, skip to dump trasport data */
	अगर (data->monitor_only)
		जाओ out;

	अगर (iwl_fw_dbg_type_on(fwrt, IWL_FW_ERROR_DUMP_MEM)) अणु
		स्थिर काष्ठा iwl_fw_dbg_mem_seg_tlv *fw_dbg_mem =
			fwrt->fw->dbg.mem_tlv;

		अगर (!fwrt->fw->dbg.n_mem_tlv)
			iwl_fw_dump_mem(fwrt, &dump_data, sram_len, sram_ofs,
					IWL_FW_ERROR_DUMP_MEM_SRAM);

		क्रम (i = 0; i < fwrt->fw->dbg.n_mem_tlv; i++) अणु
			u32 len = le32_to_cpu(fw_dbg_mem[i].len);
			u32 ofs = le32_to_cpu(fw_dbg_mem[i].ofs);

			iwl_fw_dump_mem(fwrt, &dump_data, len, ofs,
					le32_to_cpu(fw_dbg_mem[i].data_type));
		पूर्ण

		iwl_fw_dump_mem(fwrt, &dump_data, smem_len,
				fwrt->trans->cfg->smem_offset,
				IWL_FW_ERROR_DUMP_MEM_SMEM);

		iwl_fw_dump_mem(fwrt, &dump_data, sram2_len,
				fwrt->trans->cfg->dccm2_offset,
				IWL_FW_ERROR_DUMP_MEM_SRAM);
	पूर्ण

	अगर (iwl_fw_dbg_is_d3_debug_enabled(fwrt) && fwrt->dump.d3_debug_data) अणु
		u32 addr = fwrt->trans->cfg->d3_debug_data_base_addr;
		माप_प्रकार data_size = fwrt->trans->cfg->d3_debug_data_length;

		dump_data->type = cpu_to_le32(IWL_FW_ERROR_DUMP_D3_DEBUG_DATA);
		dump_data->len = cpu_to_le32(data_size * 2);

		स_नकल(dump_data->data, fwrt->dump.d3_debug_data, data_size);

		kमुक्त(fwrt->dump.d3_debug_data);
		fwrt->dump.d3_debug_data = शून्य;

		iwl_trans_पढ़ो_mem_bytes(fwrt->trans, addr,
					 dump_data->data + data_size,
					 data_size);

		dump_data = iwl_fw_error_next_data(dump_data);
	पूर्ण

	/* Dump fw's भव image */
	अगर (iwl_fw_dbg_is_paging_enabled(fwrt))
		iwl_dump_paging(fwrt, &dump_data);

	अगर (prph_len)
		iwl_fw_prph_handler(fwrt, &dump_data, iwl_dump_prph);

out:
	dump_file->file_len = cpu_to_le32(file_len);
	वापस dump_file;
पूर्ण

/**
 * काष्ठा iwl_dump_ini_region_data - region data
 * @reg_tlv: region TLV
 * @dump_data: dump data
 */
काष्ठा iwl_dump_ini_region_data अणु
	काष्ठा iwl_ucode_tlv *reg_tlv;
	काष्ठा iwl_fwrt_dump_data *dump_data;
पूर्ण;

अटल पूर्णांक
iwl_dump_ini_prph_mac_iter(काष्ठा iwl_fw_runसमय *fwrt,
			   काष्ठा iwl_dump_ini_region_data *reg_data,
			   व्योम *range_ptr, पूर्णांक idx)
अणु
	काष्ठा iwl_fw_ini_region_tlv *reg = (व्योम *)reg_data->reg_tlv->data;
	काष्ठा iwl_fw_ini_error_dump_range *range = range_ptr;
	__le32 *val = range->data;
	u32 prph_val;
	u32 addr = le32_to_cpu(reg->addrs[idx]) +
		   le32_to_cpu(reg->dev_addr.offset);
	पूर्णांक i;

	range->पूर्णांकernal_base_addr = cpu_to_le32(addr);
	range->range_data_size = reg->dev_addr.size;
	क्रम (i = 0; i < le32_to_cpu(reg->dev_addr.size); i += 4) अणु
		prph_val = iwl_पढ़ो_prph(fwrt->trans, addr + i);
		अगर (prph_val == 0x5a5a5a5a)
			वापस -EBUSY;
		*val++ = cpu_to_le32(prph_val);
	पूर्ण

	वापस माप(*range) + le32_to_cpu(range->range_data_size);
पूर्ण

अटल पूर्णांक
iwl_dump_ini_prph_phy_iter(काष्ठा iwl_fw_runसमय *fwrt,
			   काष्ठा iwl_dump_ini_region_data *reg_data,
			   व्योम *range_ptr, पूर्णांक idx)
अणु
	काष्ठा iwl_fw_ini_region_tlv *reg = (व्योम *)reg_data->reg_tlv->data;
	काष्ठा iwl_fw_ini_error_dump_range *range = range_ptr;
	__le32 *val = range->data;
	u32 indirect_wr_addr = WMAL_INDRCT_RD_CMD1;
	u32 indirect_rd_addr = WMAL_MRSPF_1;
	u32 prph_val;
	u32 addr = le32_to_cpu(reg->addrs[idx]);
	u32 dphy_state;
	u32 dphy_addr;
	पूर्णांक i;

	range->पूर्णांकernal_base_addr = cpu_to_le32(addr);
	range->range_data_size = reg->dev_addr.size;

	अगर (fwrt->trans->trans_cfg->device_family < IWL_DEVICE_FAMILY_AX210)
		indirect_wr_addr = WMAL_INDRCT_CMD1;

	indirect_wr_addr += le32_to_cpu(reg->dev_addr.offset);
	indirect_rd_addr += le32_to_cpu(reg->dev_addr.offset);

	अगर (!iwl_trans_grab_nic_access(fwrt->trans))
		वापस -EBUSY;

	dphy_addr = (reg->dev_addr.offset) ? WFPM_LMAC2_PS_CTL_RW :
					     WFPM_LMAC1_PS_CTL_RW;
	dphy_state = iwl_पढ़ो_umac_prph_no_grab(fwrt->trans, dphy_addr);

	क्रम (i = 0; i < le32_to_cpu(reg->dev_addr.size); i += 4) अणु
		अगर (dphy_state == HBUS_TIMEOUT ||
		    (dphy_state & WFPM_PS_CTL_RW_PHYRF_PD_FSM_CURSTATE_MSK) !=
		    WFPM_PHYRF_STATE_ON) अणु
			*val++ = cpu_to_le32(WFPM_DPHY_OFF);
			जारी;
		पूर्ण

		iwl_ग_लिखो_prph_no_grab(fwrt->trans, indirect_wr_addr,
				       WMAL_INDRCT_CMD(addr + i));
		prph_val = iwl_पढ़ो_prph_no_grab(fwrt->trans,
						 indirect_rd_addr);
		*val++ = cpu_to_le32(prph_val);
	पूर्ण

	iwl_trans_release_nic_access(fwrt->trans);
	वापस माप(*range) + le32_to_cpu(range->range_data_size);
पूर्ण

अटल पूर्णांक iwl_dump_ini_csr_iter(काष्ठा iwl_fw_runसमय *fwrt,
				 काष्ठा iwl_dump_ini_region_data *reg_data,
				 व्योम *range_ptr, पूर्णांक idx)
अणु
	काष्ठा iwl_fw_ini_region_tlv *reg = (व्योम *)reg_data->reg_tlv->data;
	काष्ठा iwl_fw_ini_error_dump_range *range = range_ptr;
	__le32 *val = range->data;
	u32 addr = le32_to_cpu(reg->addrs[idx]) +
		   le32_to_cpu(reg->dev_addr.offset);
	पूर्णांक i;

	range->पूर्णांकernal_base_addr = cpu_to_le32(addr);
	range->range_data_size = reg->dev_addr.size;
	क्रम (i = 0; i < le32_to_cpu(reg->dev_addr.size); i += 4)
		*val++ = cpu_to_le32(iwl_trans_पढ़ो32(fwrt->trans, addr + i));

	वापस माप(*range) + le32_to_cpu(range->range_data_size);
पूर्ण

अटल पूर्णांक iwl_dump_ini_config_iter(काष्ठा iwl_fw_runसमय *fwrt,
				    काष्ठा iwl_dump_ini_region_data *reg_data,
				    व्योम *range_ptr, पूर्णांक idx)
अणु
	काष्ठा iwl_trans *trans = fwrt->trans;
	काष्ठा iwl_fw_ini_region_tlv *reg = (व्योम *)reg_data->reg_tlv->data;
	काष्ठा iwl_fw_ini_error_dump_range *range = range_ptr;
	__le32 *val = range->data;
	u32 addr = le32_to_cpu(reg->addrs[idx]) +
		   le32_to_cpu(reg->dev_addr.offset);
	पूर्णांक i;

	/* we shouldn't get here if the trans doesn't have पढ़ो_config32 */
	अगर (WARN_ON_ONCE(!trans->ops->पढ़ो_config32))
		वापस -EOPNOTSUPP;

	range->पूर्णांकernal_base_addr = cpu_to_le32(addr);
	range->range_data_size = reg->dev_addr.size;
	क्रम (i = 0; i < le32_to_cpu(reg->dev_addr.size); i += 4) अणु
		पूर्णांक ret;
		u32 पंचांगp;

		ret = trans->ops->पढ़ो_config32(trans, addr + i, &पंचांगp);
		अगर (ret < 0)
			वापस ret;

		*val++ = cpu_to_le32(पंचांगp);
	पूर्ण

	वापस माप(*range) + le32_to_cpu(range->range_data_size);
पूर्ण

अटल पूर्णांक iwl_dump_ini_dev_mem_iter(काष्ठा iwl_fw_runसमय *fwrt,
				     काष्ठा iwl_dump_ini_region_data *reg_data,
				     व्योम *range_ptr, पूर्णांक idx)
अणु
	काष्ठा iwl_fw_ini_region_tlv *reg = (व्योम *)reg_data->reg_tlv->data;
	काष्ठा iwl_fw_ini_error_dump_range *range = range_ptr;
	u32 addr = le32_to_cpu(reg->addrs[idx]) +
		   le32_to_cpu(reg->dev_addr.offset);

	range->पूर्णांकernal_base_addr = cpu_to_le32(addr);
	range->range_data_size = reg->dev_addr.size;
	iwl_trans_पढ़ो_mem_bytes(fwrt->trans, addr, range->data,
				 le32_to_cpu(reg->dev_addr.size));

	वापस माप(*range) + le32_to_cpu(range->range_data_size);
पूर्ण

अटल पूर्णांक _iwl_dump_ini_paging_iter(काष्ठा iwl_fw_runसमय *fwrt,
				     व्योम *range_ptr, पूर्णांक idx)
अणु
	काष्ठा page *page = fwrt->fw_paging_db[idx].fw_paging_block;
	काष्ठा iwl_fw_ini_error_dump_range *range = range_ptr;
	dma_addr_t addr = fwrt->fw_paging_db[idx].fw_paging_phys;
	u32 page_size = fwrt->fw_paging_db[idx].fw_paging_size;

	range->page_num = cpu_to_le32(idx);
	range->range_data_size = cpu_to_le32(page_size);
	dma_sync_single_क्रम_cpu(fwrt->trans->dev, addr,	page_size,
				DMA_BIसूचीECTIONAL);
	स_नकल(range->data, page_address(page), page_size);
	dma_sync_single_क्रम_device(fwrt->trans->dev, addr, page_size,
				   DMA_BIसूचीECTIONAL);

	वापस माप(*range) + le32_to_cpu(range->range_data_size);
पूर्ण

अटल पूर्णांक iwl_dump_ini_paging_iter(काष्ठा iwl_fw_runसमय *fwrt,
				    काष्ठा iwl_dump_ini_region_data *reg_data,
				    व्योम *range_ptr, पूर्णांक idx)
अणु
	काष्ठा iwl_fw_ini_error_dump_range *range;
	u32 page_size;

	/* all paged index start from 1 to skip CSS section */
	idx++;

	अगर (!fwrt->trans->trans_cfg->gen2)
		वापस _iwl_dump_ini_paging_iter(fwrt, range_ptr, idx);

	range = range_ptr;
	page_size = fwrt->trans->init_dram.paging[idx].size;

	range->page_num = cpu_to_le32(idx);
	range->range_data_size = cpu_to_le32(page_size);
	स_नकल(range->data, fwrt->trans->init_dram.paging[idx].block,
	       page_size);

	वापस माप(*range) + le32_to_cpu(range->range_data_size);
पूर्ण

अटल पूर्णांक
iwl_dump_ini_mon_dram_iter(काष्ठा iwl_fw_runसमय *fwrt,
			   काष्ठा iwl_dump_ini_region_data *reg_data,
			   व्योम *range_ptr, पूर्णांक idx)
अणु
	काष्ठा iwl_fw_ini_region_tlv *reg = (व्योम *)reg_data->reg_tlv->data;
	काष्ठा iwl_fw_ini_error_dump_range *range = range_ptr;
	काष्ठा iwl_dram_data *frag;
	u32 alloc_id = le32_to_cpu(reg->dram_alloc_id);

	frag = &fwrt->trans->dbg.fw_mon_ini[alloc_id].frags[idx];

	range->dram_base_addr = cpu_to_le64(frag->physical);
	range->range_data_size = cpu_to_le32(frag->size);

	स_नकल(range->data, frag->block, frag->size);

	वापस माप(*range) + le32_to_cpu(range->range_data_size);
पूर्ण

अटल पूर्णांक iwl_dump_ini_mon_smem_iter(काष्ठा iwl_fw_runसमय *fwrt,
				      काष्ठा iwl_dump_ini_region_data *reg_data,
				      व्योम *range_ptr, पूर्णांक idx)
अणु
	काष्ठा iwl_fw_ini_region_tlv *reg = (व्योम *)reg_data->reg_tlv->data;
	काष्ठा iwl_fw_ini_error_dump_range *range = range_ptr;
	u32 addr = le32_to_cpu(reg->पूर्णांकernal_buffer.base_addr);

	range->पूर्णांकernal_base_addr = cpu_to_le32(addr);
	range->range_data_size = reg->पूर्णांकernal_buffer.size;
	iwl_trans_पढ़ो_mem_bytes(fwrt->trans, addr, range->data,
				 le32_to_cpu(reg->पूर्णांकernal_buffer.size));

	वापस माप(*range) + le32_to_cpu(range->range_data_size);
पूर्ण

अटल bool iwl_ini_txf_iter(काष्ठा iwl_fw_runसमय *fwrt,
			     काष्ठा iwl_dump_ini_region_data *reg_data, पूर्णांक idx)
अणु
	काष्ठा iwl_fw_ini_region_tlv *reg = (व्योम *)reg_data->reg_tlv->data;
	काष्ठा iwl_txf_iter_data *iter = &fwrt->dump.txf_iter_data;
	काष्ठा iwl_fwrt_shared_mem_cfg *cfg = &fwrt->smem_cfg;
	पूर्णांक txf_num = cfg->num_txfअगरo_entries;
	पूर्णांक पूर्णांक_txf_num = ARRAY_SIZE(cfg->पूर्णांकernal_txfअगरo_size);
	u32 lmac_biपंचांगap = le32_to_cpu(reg->fअगरos.fid[0]);

	अगर (!idx) अणु
		अगर (le32_to_cpu(reg->fअगरos.offset) && cfg->num_lmacs == 1) अणु
			IWL_ERR(fwrt, "WRT: Invalid lmac offset 0x%x\n",
				le32_to_cpu(reg->fअगरos.offset));
			वापस false;
		पूर्ण

		iter->पूर्णांकernal_txf = 0;
		iter->fअगरo_size = 0;
		iter->fअगरo = -1;
		अगर (le32_to_cpu(reg->fअगरos.offset))
			iter->lmac = 1;
		अन्यथा
			iter->lmac = 0;
	पूर्ण

	अगर (!iter->पूर्णांकernal_txf) अणु
		क्रम (iter->fअगरo++; iter->fअगरo < txf_num; iter->fअगरo++) अणु
			iter->fअगरo_size =
				cfg->lmac[iter->lmac].txfअगरo_size[iter->fअगरo];
			अगर (iter->fअगरo_size && (lmac_biपंचांगap & BIT(iter->fअगरo)))
				वापस true;
		पूर्ण
		iter->fअगरo--;
	पूर्ण

	iter->पूर्णांकernal_txf = 1;

	अगर (!fw_has_capa(&fwrt->fw->ucode_capa,
			 IWL_UCODE_TLV_CAPA_EXTEND_SHARED_MEM_CFG))
		वापस false;

	क्रम (iter->fअगरo++; iter->fअगरo < पूर्णांक_txf_num + txf_num; iter->fअगरo++) अणु
		iter->fअगरo_size =
			cfg->पूर्णांकernal_txfअगरo_size[iter->fअगरo - txf_num];
		अगर (iter->fअगरo_size && (lmac_biपंचांगap & BIT(iter->fअगरo)))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक iwl_dump_ini_txf_iter(काष्ठा iwl_fw_runसमय *fwrt,
				 काष्ठा iwl_dump_ini_region_data *reg_data,
				 व्योम *range_ptr, पूर्णांक idx)
अणु
	काष्ठा iwl_fw_ini_region_tlv *reg = (व्योम *)reg_data->reg_tlv->data;
	काष्ठा iwl_fw_ini_error_dump_range *range = range_ptr;
	काष्ठा iwl_txf_iter_data *iter = &fwrt->dump.txf_iter_data;
	काष्ठा iwl_fw_ini_error_dump_रेजिस्टर *reg_dump = (व्योम *)range->data;
	u32 offs = le32_to_cpu(reg->fअगरos.offset), addr;
	u32 रेजिस्टरs_num = iwl_tlv_array_len(reg_data->reg_tlv, reg, addrs);
	u32 रेजिस्टरs_size = रेजिस्टरs_num * माप(*reg_dump);
	__le32 *data;
	पूर्णांक i;

	अगर (!iwl_ini_txf_iter(fwrt, reg_data, idx))
		वापस -EIO;

	अगर (!iwl_trans_grab_nic_access(fwrt->trans))
		वापस -EBUSY;

	range->fअगरo_hdr.fअगरo_num = cpu_to_le32(iter->fअगरo);
	range->fअगरo_hdr.num_of_रेजिस्टरs = cpu_to_le32(रेजिस्टरs_num);
	range->range_data_size = cpu_to_le32(iter->fअगरo_size + रेजिस्टरs_size);

	iwl_ग_लिखो_prph_no_grab(fwrt->trans, TXF_LARC_NUM + offs, iter->fअगरo);

	/*
	 * पढ़ो txf रेजिस्टरs. क्रम each रेजिस्टर, ग_लिखो to the dump the
	 * रेजिस्टर address and its value
	 */
	क्रम (i = 0; i < रेजिस्टरs_num; i++) अणु
		addr = le32_to_cpu(reg->addrs[i]) + offs;

		reg_dump->addr = cpu_to_le32(addr);
		reg_dump->data = cpu_to_le32(iwl_पढ़ो_prph_no_grab(fwrt->trans,
								   addr));

		reg_dump++;
	पूर्ण

	अगर (reg->fअगरos.hdr_only) अणु
		range->range_data_size = cpu_to_le32(रेजिस्टरs_size);
		जाओ out;
	पूर्ण

	/* Set the TXF_READ_MODIFY_ADDR to TXF_WR_PTR */
	iwl_ग_लिखो_prph_no_grab(fwrt->trans, TXF_READ_MODIFY_ADDR + offs,
			       TXF_WR_PTR + offs);

	/* Dummy-पढ़ो to advance the पढ़ो poपूर्णांकer to the head */
	iwl_पढ़ो_prph_no_grab(fwrt->trans, TXF_READ_MODIFY_DATA + offs);

	/* Read FIFO */
	addr = TXF_READ_MODIFY_DATA + offs;
	data = (व्योम *)reg_dump;
	क्रम (i = 0; i < iter->fअगरo_size; i += माप(*data))
		*data++ = cpu_to_le32(iwl_पढ़ो_prph_no_grab(fwrt->trans, addr));

out:
	iwl_trans_release_nic_access(fwrt->trans);

	वापस माप(*range) + le32_to_cpu(range->range_data_size);
पूर्ण

काष्ठा iwl_ini_rxf_data अणु
	u32 fअगरo_num;
	u32 size;
	u32 offset;
पूर्ण;

अटल व्योम iwl_ini_get_rxf_data(काष्ठा iwl_fw_runसमय *fwrt,
				 काष्ठा iwl_dump_ini_region_data *reg_data,
				 काष्ठा iwl_ini_rxf_data *data)
अणु
	काष्ठा iwl_fw_ini_region_tlv *reg = (व्योम *)reg_data->reg_tlv->data;
	u32 fid1 = le32_to_cpu(reg->fअगरos.fid[0]);
	u32 fid2 = le32_to_cpu(reg->fअगरos.fid[1]);
	u8 fअगरo_idx;

	अगर (!data)
		वापस;

	/* make sure only one bit is set in only one fid */
	अगर (WARN_ONCE(hweight_दीर्घ(fid1) + hweight_दीर्घ(fid2) != 1,
		      "fid1=%x, fid2=%x\n", fid1, fid2))
		वापस;

	स_रखो(data, 0, माप(*data));

	अगर (fid1) अणु
		fअगरo_idx = ffs(fid1) - 1;
		अगर (WARN_ONCE(fअगरo_idx >= MAX_NUM_LMAC, "fifo_idx=%d\n",
			      fअगरo_idx))
			वापस;

		data->size = fwrt->smem_cfg.lmac[fअगरo_idx].rxfअगरo1_size;
		data->fअगरo_num = fअगरo_idx;
	पूर्ण अन्यथा अणु
		u8 max_idx;

		fअगरo_idx = ffs(fid2) - 1;
		अगर (iwl_fw_lookup_notअगर_ver(fwrt->fw, SYSTEM_GROUP,
					    SHARED_MEM_CFG_CMD, 0) <= 3)
			max_idx = 0;
		अन्यथा
			max_idx = 1;

		अगर (WARN_ONCE(fअगरo_idx > max_idx,
			      "invalid umac fifo idx %d", fअगरo_idx))
			वापस;

		/* use bit 31 to distinguish between umac and lmac rxf जबतक
		 * parsing the dump
		 */
		data->fअगरo_num = fअगरo_idx | IWL_RXF_UMAC_BIT;

		चयन (fअगरo_idx) अणु
		हाल 0:
			data->size = fwrt->smem_cfg.rxfअगरo2_size;
			data->offset = iwl_umac_prph(fwrt->trans,
						     RXF_DIFF_FROM_PREV);
			अवरोध;
		हाल 1:
			data->size = fwrt->smem_cfg.rxfअगरo2_control_size;
			data->offset = iwl_umac_prph(fwrt->trans,
						     RXF2C_DIFF_FROM_PREV);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक iwl_dump_ini_rxf_iter(काष्ठा iwl_fw_runसमय *fwrt,
				 काष्ठा iwl_dump_ini_region_data *reg_data,
				 व्योम *range_ptr, पूर्णांक idx)
अणु
	काष्ठा iwl_fw_ini_region_tlv *reg = (व्योम *)reg_data->reg_tlv->data;
	काष्ठा iwl_fw_ini_error_dump_range *range = range_ptr;
	काष्ठा iwl_ini_rxf_data rxf_data;
	काष्ठा iwl_fw_ini_error_dump_रेजिस्टर *reg_dump = (व्योम *)range->data;
	u32 offs = le32_to_cpu(reg->fअगरos.offset), addr;
	u32 रेजिस्टरs_num = iwl_tlv_array_len(reg_data->reg_tlv, reg, addrs);
	u32 रेजिस्टरs_size = रेजिस्टरs_num * माप(*reg_dump);
	__le32 *data;
	पूर्णांक i;

	iwl_ini_get_rxf_data(fwrt, reg_data, &rxf_data);
	अगर (!rxf_data.size)
		वापस -EIO;

	अगर (!iwl_trans_grab_nic_access(fwrt->trans))
		वापस -EBUSY;

	range->fअगरo_hdr.fअगरo_num = cpu_to_le32(rxf_data.fअगरo_num);
	range->fअगरo_hdr.num_of_रेजिस्टरs = cpu_to_le32(रेजिस्टरs_num);
	range->range_data_size = cpu_to_le32(rxf_data.size + रेजिस्टरs_size);

	/*
	 * पढ़ो rxf रेजिस्टरs. क्रम each रेजिस्टर, ग_लिखो to the dump the
	 * रेजिस्टर address and its value
	 */
	क्रम (i = 0; i < रेजिस्टरs_num; i++) अणु
		addr = le32_to_cpu(reg->addrs[i]) + offs;

		reg_dump->addr = cpu_to_le32(addr);
		reg_dump->data = cpu_to_le32(iwl_पढ़ो_prph_no_grab(fwrt->trans,
								   addr));

		reg_dump++;
	पूर्ण

	अगर (reg->fअगरos.hdr_only) अणु
		range->range_data_size = cpu_to_le32(रेजिस्टरs_size);
		जाओ out;
	पूर्ण

	offs = rxf_data.offset;

	/* Lock fence */
	iwl_ग_लिखो_prph_no_grab(fwrt->trans, RXF_SET_FENCE_MODE + offs, 0x1);
	/* Set fence poपूर्णांकer to the same place like WR poपूर्णांकer */
	iwl_ग_लिखो_prph_no_grab(fwrt->trans, RXF_LD_WR2FENCE + offs, 0x1);
	/* Set fence offset */
	iwl_ग_लिखो_prph_no_grab(fwrt->trans, RXF_LD_FENCE_OFFSET_ADDR + offs,
			       0x0);

	/* Read FIFO */
	addr =  RXF_FIFO_RD_FENCE_INC + offs;
	data = (व्योम *)reg_dump;
	क्रम (i = 0; i < rxf_data.size; i += माप(*data))
		*data++ = cpu_to_le32(iwl_पढ़ो_prph_no_grab(fwrt->trans, addr));

out:
	iwl_trans_release_nic_access(fwrt->trans);

	वापस माप(*range) + le32_to_cpu(range->range_data_size);
पूर्ण

अटल पूर्णांक
iwl_dump_ini_err_table_iter(काष्ठा iwl_fw_runसमय *fwrt,
			    काष्ठा iwl_dump_ini_region_data *reg_data,
			    व्योम *range_ptr, पूर्णांक idx)
अणु
	काष्ठा iwl_fw_ini_region_tlv *reg = (व्योम *)reg_data->reg_tlv->data;
	काष्ठा iwl_fw_ini_region_err_table *err_table = &reg->err_table;
	काष्ठा iwl_fw_ini_error_dump_range *range = range_ptr;
	u32 addr = le32_to_cpu(err_table->base_addr) +
		   le32_to_cpu(err_table->offset);

	range->पूर्णांकernal_base_addr = cpu_to_le32(addr);
	range->range_data_size = err_table->size;
	iwl_trans_पढ़ो_mem_bytes(fwrt->trans, addr, range->data,
				 le32_to_cpu(err_table->size));

	वापस माप(*range) + le32_to_cpu(range->range_data_size);
पूर्ण

अटल पूर्णांक
iwl_dump_ini_special_mem_iter(काष्ठा iwl_fw_runसमय *fwrt,
			      काष्ठा iwl_dump_ini_region_data *reg_data,
			      व्योम *range_ptr, पूर्णांक idx)
अणु
	काष्ठा iwl_fw_ini_region_tlv *reg = (व्योम *)reg_data->reg_tlv->data;
	काष्ठा iwl_fw_ini_region_special_device_memory *special_mem =
		&reg->special_mem;

	काष्ठा iwl_fw_ini_error_dump_range *range = range_ptr;
	u32 addr = le32_to_cpu(special_mem->base_addr) +
		   le32_to_cpu(special_mem->offset);

	range->पूर्णांकernal_base_addr = cpu_to_le32(addr);
	range->range_data_size = special_mem->size;
	iwl_trans_पढ़ो_mem_bytes(fwrt->trans, addr, range->data,
				 le32_to_cpu(special_mem->size));

	वापस माप(*range) + le32_to_cpu(range->range_data_size);
पूर्ण

अटल पूर्णांक iwl_dump_ini_fw_pkt_iter(काष्ठा iwl_fw_runसमय *fwrt,
				    काष्ठा iwl_dump_ini_region_data *reg_data,
				    व्योम *range_ptr, पूर्णांक idx)
अणु
	काष्ठा iwl_fw_ini_error_dump_range *range = range_ptr;
	काष्ठा iwl_rx_packet *pkt = reg_data->dump_data->fw_pkt;
	u32 pkt_len;

	अगर (!pkt)
		वापस -EIO;

	pkt_len = iwl_rx_packet_payload_len(pkt);

	स_नकल(&range->fw_pkt_hdr, &pkt->hdr, माप(range->fw_pkt_hdr));
	range->range_data_size = cpu_to_le32(pkt_len);

	स_नकल(range->data, pkt->data, pkt_len);

	वापस माप(*range) + le32_to_cpu(range->range_data_size);
पूर्ण

अटल व्योम *
iwl_dump_ini_mem_fill_header(काष्ठा iwl_fw_runसमय *fwrt,
			     काष्ठा iwl_dump_ini_region_data *reg_data,
			     व्योम *data)
अणु
	काष्ठा iwl_fw_ini_error_dump *dump = data;

	dump->header.version = cpu_to_le32(IWL_INI_DUMP_VER);

	वापस dump->ranges;
पूर्ण

/**
 * mask_apply_and_normalize - applies mask on val and normalize the result
 *
 * The normalization is based on the first set bit in the mask
 *
 * @val: value
 * @mask: mask to apply and to normalize with
 */
अटल u32 mask_apply_and_normalize(u32 val, u32 mask)
अणु
	वापस (val & mask) >> (ffs(mask) - 1);
पूर्ण

अटल __le32 iwl_get_mon_reg(काष्ठा iwl_fw_runसमय *fwrt, u32 alloc_id,
			      स्थिर काष्ठा iwl_fw_mon_reg *reg_info)
अणु
	u32 val, offs;

	/* The header addresses of DBGCi is calculate as follows:
	 * DBGC1 address + (0x100 * i)
	 */
	offs = (alloc_id - IWL_FW_INI_ALLOCATION_ID_DBGC1) * 0x100;

	अगर (!reg_info || !reg_info->addr || !reg_info->mask)
		वापस 0;

	val = iwl_पढ़ो_prph_no_grab(fwrt->trans, reg_info->addr + offs);

	वापस cpu_to_le32(mask_apply_and_normalize(val, reg_info->mask));
पूर्ण

अटल व्योम *
iwl_dump_ini_mon_fill_header(काष्ठा iwl_fw_runसमय *fwrt,
			     काष्ठा iwl_dump_ini_region_data *reg_data,
			     काष्ठा iwl_fw_ini_monitor_dump *data,
			     स्थिर काष्ठा iwl_fw_mon_regs *addrs)
अणु
	काष्ठा iwl_fw_ini_region_tlv *reg = (व्योम *)reg_data->reg_tlv->data;
	u32 alloc_id = le32_to_cpu(reg->dram_alloc_id);

	अगर (!iwl_trans_grab_nic_access(fwrt->trans)) अणु
		IWL_ERR(fwrt, "Failed to get monitor header\n");
		वापस शून्य;
	पूर्ण

	data->ग_लिखो_ptr = iwl_get_mon_reg(fwrt, alloc_id,
					  &addrs->ग_लिखो_ptr);
	अगर (fwrt->trans->trans_cfg->device_family >= IWL_DEVICE_FAMILY_AX210) अणु
		u32 wrt_ptr = le32_to_cpu(data->ग_लिखो_ptr);

		data->ग_लिखो_ptr = cpu_to_le32(wrt_ptr >> 2);
	पूर्ण
	data->cycle_cnt = iwl_get_mon_reg(fwrt, alloc_id,
					  &addrs->cycle_cnt);
	data->cur_frag = iwl_get_mon_reg(fwrt, alloc_id,
					 &addrs->cur_frag);

	iwl_trans_release_nic_access(fwrt->trans);

	data->header.version = cpu_to_le32(IWL_INI_DUMP_VER);

	वापस data->ranges;
पूर्ण

अटल व्योम *
iwl_dump_ini_mon_dram_fill_header(काष्ठा iwl_fw_runसमय *fwrt,
				  काष्ठा iwl_dump_ini_region_data *reg_data,
				  व्योम *data)
अणु
	काष्ठा iwl_fw_ini_monitor_dump *mon_dump = (व्योम *)data;

	वापस iwl_dump_ini_mon_fill_header(fwrt, reg_data, mon_dump,
					    &fwrt->trans->cfg->mon_dram_regs);
पूर्ण

अटल व्योम *
iwl_dump_ini_mon_smem_fill_header(काष्ठा iwl_fw_runसमय *fwrt,
				  काष्ठा iwl_dump_ini_region_data *reg_data,
				  व्योम *data)
अणु
	काष्ठा iwl_fw_ini_monitor_dump *mon_dump = (व्योम *)data;

	वापस iwl_dump_ini_mon_fill_header(fwrt, reg_data, mon_dump,
					    &fwrt->trans->cfg->mon_smem_regs);
पूर्ण

अटल व्योम *
iwl_dump_ini_err_table_fill_header(काष्ठा iwl_fw_runसमय *fwrt,
				   काष्ठा iwl_dump_ini_region_data *reg_data,
				   व्योम *data)
अणु
	काष्ठा iwl_fw_ini_region_tlv *reg = (व्योम *)reg_data->reg_tlv->data;
	काष्ठा iwl_fw_ini_err_table_dump *dump = data;

	dump->header.version = cpu_to_le32(IWL_INI_DUMP_VER);
	dump->version = reg->err_table.version;

	वापस dump->ranges;
पूर्ण

अटल व्योम *
iwl_dump_ini_special_mem_fill_header(काष्ठा iwl_fw_runसमय *fwrt,
				     काष्ठा iwl_dump_ini_region_data *reg_data,
				     व्योम *data)
अणु
	काष्ठा iwl_fw_ini_region_tlv *reg = (व्योम *)reg_data->reg_tlv->data;
	काष्ठा iwl_fw_ini_special_device_memory *dump = data;

	dump->header.version = cpu_to_le32(IWL_INI_DUMP_VER);
	dump->type = reg->special_mem.type;
	dump->version = reg->special_mem.version;

	वापस dump->ranges;
पूर्ण

अटल u32 iwl_dump_ini_mem_ranges(काष्ठा iwl_fw_runसमय *fwrt,
				   काष्ठा iwl_dump_ini_region_data *reg_data)
अणु
	काष्ठा iwl_fw_ini_region_tlv *reg = (व्योम *)reg_data->reg_tlv->data;

	वापस iwl_tlv_array_len(reg_data->reg_tlv, reg, addrs);
पूर्ण

अटल u32 iwl_dump_ini_paging_ranges(काष्ठा iwl_fw_runसमय *fwrt,
				      काष्ठा iwl_dump_ini_region_data *reg_data)
अणु
	अगर (fwrt->trans->trans_cfg->gen2) अणु
		अगर (fwrt->trans->init_dram.paging_cnt)
			वापस fwrt->trans->init_dram.paging_cnt - 1;
		अन्यथा
			वापस 0;
	पूर्ण

	वापस fwrt->num_of_paging_blk;
पूर्ण

अटल u32
iwl_dump_ini_mon_dram_ranges(काष्ठा iwl_fw_runसमय *fwrt,
			     काष्ठा iwl_dump_ini_region_data *reg_data)
अणु
	काष्ठा iwl_fw_ini_region_tlv *reg = (व्योम *)reg_data->reg_tlv->data;
	काष्ठा iwl_fw_mon *fw_mon;
	u32 ranges = 0, alloc_id = le32_to_cpu(reg->dram_alloc_id);
	पूर्णांक i;

	fw_mon = &fwrt->trans->dbg.fw_mon_ini[alloc_id];

	क्रम (i = 0; i < fw_mon->num_frags; i++) अणु
		अगर (!fw_mon->frags[i].size)
			अवरोध;

		ranges++;
	पूर्ण

	वापस ranges;
पूर्ण

अटल u32 iwl_dump_ini_txf_ranges(काष्ठा iwl_fw_runसमय *fwrt,
				   काष्ठा iwl_dump_ini_region_data *reg_data)
अणु
	u32 num_of_fअगरos = 0;

	जबतक (iwl_ini_txf_iter(fwrt, reg_data, num_of_fअगरos))
		num_of_fअगरos++;

	वापस num_of_fअगरos;
पूर्ण

अटल u32 iwl_dump_ini_single_range(काष्ठा iwl_fw_runसमय *fwrt,
				     काष्ठा iwl_dump_ini_region_data *reg_data)
अणु
	वापस 1;
पूर्ण

अटल u32 iwl_dump_ini_mem_get_size(काष्ठा iwl_fw_runसमय *fwrt,
				     काष्ठा iwl_dump_ini_region_data *reg_data)
अणु
	काष्ठा iwl_fw_ini_region_tlv *reg = (व्योम *)reg_data->reg_tlv->data;
	u32 size = le32_to_cpu(reg->dev_addr.size);
	u32 ranges = iwl_dump_ini_mem_ranges(fwrt, reg_data);

	अगर (!size || !ranges)
		वापस 0;

	वापस माप(काष्ठा iwl_fw_ini_error_dump) + ranges *
		(size + माप(काष्ठा iwl_fw_ini_error_dump_range));
पूर्ण

अटल u32
iwl_dump_ini_paging_get_size(काष्ठा iwl_fw_runसमय *fwrt,
			     काष्ठा iwl_dump_ini_region_data *reg_data)
अणु
	पूर्णांक i;
	u32 range_header_len = माप(काष्ठा iwl_fw_ini_error_dump_range);
	u32 size = माप(काष्ठा iwl_fw_ini_error_dump);

	/* start from 1 to skip CSS section */
	क्रम (i = 1; i <= iwl_dump_ini_paging_ranges(fwrt, reg_data); i++) अणु
		size += range_header_len;
		अगर (fwrt->trans->trans_cfg->gen2)
			size += fwrt->trans->init_dram.paging[i].size;
		अन्यथा
			size += fwrt->fw_paging_db[i].fw_paging_size;
	पूर्ण

	वापस size;
पूर्ण

अटल u32
iwl_dump_ini_mon_dram_get_size(काष्ठा iwl_fw_runसमय *fwrt,
			       काष्ठा iwl_dump_ini_region_data *reg_data)
अणु
	काष्ठा iwl_fw_ini_region_tlv *reg = (व्योम *)reg_data->reg_tlv->data;
	काष्ठा iwl_fw_mon *fw_mon;
	u32 size = 0, alloc_id = le32_to_cpu(reg->dram_alloc_id);
	पूर्णांक i;

	fw_mon = &fwrt->trans->dbg.fw_mon_ini[alloc_id];

	क्रम (i = 0; i < fw_mon->num_frags; i++) अणु
		काष्ठा iwl_dram_data *frag = &fw_mon->frags[i];

		अगर (!frag->size)
			अवरोध;

		size += माप(काष्ठा iwl_fw_ini_error_dump_range) + frag->size;
	पूर्ण

	अगर (size)
		size += माप(काष्ठा iwl_fw_ini_monitor_dump);

	वापस size;
पूर्ण

अटल u32
iwl_dump_ini_mon_smem_get_size(काष्ठा iwl_fw_runसमय *fwrt,
			       काष्ठा iwl_dump_ini_region_data *reg_data)
अणु
	काष्ठा iwl_fw_ini_region_tlv *reg = (व्योम *)reg_data->reg_tlv->data;
	u32 size;

	size = le32_to_cpu(reg->पूर्णांकernal_buffer.size);
	अगर (!size)
		वापस 0;

	size += माप(काष्ठा iwl_fw_ini_monitor_dump) +
		माप(काष्ठा iwl_fw_ini_error_dump_range);

	वापस size;
पूर्ण

अटल u32 iwl_dump_ini_txf_get_size(काष्ठा iwl_fw_runसमय *fwrt,
				     काष्ठा iwl_dump_ini_region_data *reg_data)
अणु
	काष्ठा iwl_fw_ini_region_tlv *reg = (व्योम *)reg_data->reg_tlv->data;
	काष्ठा iwl_txf_iter_data *iter = &fwrt->dump.txf_iter_data;
	u32 रेजिस्टरs_num = iwl_tlv_array_len(reg_data->reg_tlv, reg, addrs);
	u32 size = 0;
	u32 fअगरo_hdr = माप(काष्ठा iwl_fw_ini_error_dump_range) +
		       रेजिस्टरs_num *
		       माप(काष्ठा iwl_fw_ini_error_dump_रेजिस्टर);

	जबतक (iwl_ini_txf_iter(fwrt, reg_data, size)) अणु
		size += fअगरo_hdr;
		अगर (!reg->fअगरos.hdr_only)
			size += iter->fअगरo_size;
	पूर्ण

	अगर (!size)
		वापस 0;

	वापस size + माप(काष्ठा iwl_fw_ini_error_dump);
पूर्ण

अटल u32 iwl_dump_ini_rxf_get_size(काष्ठा iwl_fw_runसमय *fwrt,
				     काष्ठा iwl_dump_ini_region_data *reg_data)
अणु
	काष्ठा iwl_fw_ini_region_tlv *reg = (व्योम *)reg_data->reg_tlv->data;
	काष्ठा iwl_ini_rxf_data rx_data;
	u32 रेजिस्टरs_num = iwl_tlv_array_len(reg_data->reg_tlv, reg, addrs);
	u32 size = माप(काष्ठा iwl_fw_ini_error_dump) +
		माप(काष्ठा iwl_fw_ini_error_dump_range) +
		रेजिस्टरs_num * माप(काष्ठा iwl_fw_ini_error_dump_रेजिस्टर);

	अगर (reg->fअगरos.hdr_only)
		वापस size;

	iwl_ini_get_rxf_data(fwrt, reg_data, &rx_data);
	size += rx_data.size;

	वापस size;
पूर्ण

अटल u32
iwl_dump_ini_err_table_get_size(काष्ठा iwl_fw_runसमय *fwrt,
				काष्ठा iwl_dump_ini_region_data *reg_data)
अणु
	काष्ठा iwl_fw_ini_region_tlv *reg = (व्योम *)reg_data->reg_tlv->data;
	u32 size = le32_to_cpu(reg->err_table.size);

	अगर (size)
		size += माप(काष्ठा iwl_fw_ini_err_table_dump) +
			माप(काष्ठा iwl_fw_ini_error_dump_range);

	वापस size;
पूर्ण

अटल u32
iwl_dump_ini_special_mem_get_size(काष्ठा iwl_fw_runसमय *fwrt,
				  काष्ठा iwl_dump_ini_region_data *reg_data)
अणु
	काष्ठा iwl_fw_ini_region_tlv *reg = (व्योम *)reg_data->reg_tlv->data;
	u32 size = le32_to_cpu(reg->special_mem.size);

	अगर (size)
		size += माप(काष्ठा iwl_fw_ini_special_device_memory) +
			माप(काष्ठा iwl_fw_ini_error_dump_range);

	वापस size;
पूर्ण

अटल u32
iwl_dump_ini_fw_pkt_get_size(काष्ठा iwl_fw_runसमय *fwrt,
			     काष्ठा iwl_dump_ini_region_data *reg_data)
अणु
	u32 size = 0;

	अगर (!reg_data->dump_data->fw_pkt)
		वापस 0;

	size += iwl_rx_packet_payload_len(reg_data->dump_data->fw_pkt);
	अगर (size)
		size += माप(काष्ठा iwl_fw_ini_error_dump) +
			माप(काष्ठा iwl_fw_ini_error_dump_range);

	वापस size;
पूर्ण

/**
 * काष्ठा iwl_dump_ini_mem_ops - ini memory dump operations
 * @get_num_of_ranges: वापसs the number of memory ranges in the region.
 * @get_size: वापसs the total size of the region.
 * @fill_mem_hdr: fills region type specअगरic headers and वापसs poपूर्णांकer to
 *	the first range or शून्य अगर failed to fill headers.
 * @fill_range: copies a given memory range पूर्णांकo the dump.
 *	Returns the size of the range or negative error value otherwise.
 */
काष्ठा iwl_dump_ini_mem_ops अणु
	u32 (*get_num_of_ranges)(काष्ठा iwl_fw_runसमय *fwrt,
				 काष्ठा iwl_dump_ini_region_data *reg_data);
	u32 (*get_size)(काष्ठा iwl_fw_runसमय *fwrt,
			काष्ठा iwl_dump_ini_region_data *reg_data);
	व्योम *(*fill_mem_hdr)(काष्ठा iwl_fw_runसमय *fwrt,
			      काष्ठा iwl_dump_ini_region_data *reg_data,
			      व्योम *data);
	पूर्णांक (*fill_range)(काष्ठा iwl_fw_runसमय *fwrt,
			  काष्ठा iwl_dump_ini_region_data *reg_data,
			  व्योम *range, पूर्णांक idx);
पूर्ण;

/**
 * iwl_dump_ini_mem
 *
 * Creates a dump tlv and copy a memory region पूर्णांकo it.
 * Returns the size of the current dump tlv or 0 अगर failed
 *
 * @fwrt: fw runसमय काष्ठा
 * @list: list to add the dump tlv to
 * @reg_data: memory region
 * @ops: memory dump operations
 */
अटल u32 iwl_dump_ini_mem(काष्ठा iwl_fw_runसमय *fwrt, काष्ठा list_head *list,
			    काष्ठा iwl_dump_ini_region_data *reg_data,
			    स्थिर काष्ठा iwl_dump_ini_mem_ops *ops)
अणु
	काष्ठा iwl_fw_ini_region_tlv *reg = (व्योम *)reg_data->reg_tlv->data;
	काष्ठा iwl_fw_ini_dump_entry *entry;
	काष्ठा iwl_fw_error_dump_data *tlv;
	काष्ठा iwl_fw_ini_error_dump_header *header;
	u32 type = le32_to_cpu(reg->type), id = le32_to_cpu(reg->id);
	u32 num_of_ranges, i, size;
	व्योम *range;

	अगर (!ops->get_num_of_ranges || !ops->get_size || !ops->fill_mem_hdr ||
	    !ops->fill_range)
		वापस 0;

	size = ops->get_size(fwrt, reg_data);
	अगर (!size)
		वापस 0;

	entry = vzalloc(माप(*entry) + माप(*tlv) + size);
	अगर (!entry)
		वापस 0;

	entry->size = माप(*tlv) + size;

	tlv = (व्योम *)entry->data;
	tlv->type = reg->type;
	tlv->len = cpu_to_le32(size);

	IWL_DEBUG_FW(fwrt, "WRT: Collecting region: id=%d, type=%d\n", id,
		     type);

	num_of_ranges = ops->get_num_of_ranges(fwrt, reg_data);

	header = (व्योम *)tlv->data;
	header->region_id = reg->id;
	header->num_of_ranges = cpu_to_le32(num_of_ranges);
	header->name_len = cpu_to_le32(IWL_FW_INI_MAX_NAME);
	स_नकल(header->name, reg->name, IWL_FW_INI_MAX_NAME);

	range = ops->fill_mem_hdr(fwrt, reg_data, header);
	अगर (!range) अणु
		IWL_ERR(fwrt,
			"WRT: Failed to fill region header: id=%d, type=%d\n",
			id, type);
		जाओ out_err;
	पूर्ण

	क्रम (i = 0; i < num_of_ranges; i++) अणु
		पूर्णांक range_size = ops->fill_range(fwrt, reg_data, range, i);

		अगर (range_size < 0) अणु
			IWL_ERR(fwrt,
				"WRT: Failed to dump region: id=%d, type=%d\n",
				id, type);
			जाओ out_err;
		पूर्ण
		range = range + range_size;
	पूर्ण

	list_add_tail(&entry->list, list);

	वापस entry->size;

out_err:
	vमुक्त(entry);

	वापस 0;
पूर्ण

अटल u32 iwl_dump_ini_info(काष्ठा iwl_fw_runसमय *fwrt,
			     काष्ठा iwl_fw_ini_trigger_tlv *trigger,
			     काष्ठा list_head *list)
अणु
	काष्ठा iwl_fw_ini_dump_entry *entry;
	काष्ठा iwl_fw_error_dump_data *tlv;
	काष्ठा iwl_fw_ini_dump_info *dump;
	काष्ठा iwl_dbg_tlv_node *node;
	काष्ठा iwl_fw_ini_dump_cfg_name *cfg_name;
	u32 size = माप(*tlv) + माप(*dump);
	u32 num_of_cfg_names = 0;
	u32 hw_type;

	list_क्रम_each_entry(node, &fwrt->trans->dbg.debug_info_tlv_list, list) अणु
		size += माप(*cfg_name);
		num_of_cfg_names++;
	पूर्ण

	entry = vzalloc(माप(*entry) + size);
	अगर (!entry)
		वापस 0;

	entry->size = size;

	tlv = (व्योम *)entry->data;
	tlv->type = cpu_to_le32(IWL_INI_DUMP_INFO_TYPE);
	tlv->len = cpu_to_le32(size - माप(*tlv));

	dump = (व्योम *)tlv->data;

	dump->version = cpu_to_le32(IWL_INI_DUMP_VER);
	dump->समय_poपूर्णांक = trigger->समय_poपूर्णांक;
	dump->trigger_reason = trigger->trigger_reason;
	dump->बाह्यal_cfg_state =
		cpu_to_le32(fwrt->trans->dbg.बाह्यal_ini_cfg);

	dump->ver_type = cpu_to_le32(fwrt->dump.fw_ver.type);
	dump->ver_subtype = cpu_to_le32(fwrt->dump.fw_ver.subtype);

	dump->hw_step = cpu_to_le32(CSR_HW_REV_STEP(fwrt->trans->hw_rev));

	/*
	 * Several HWs all have type == 0x42, so we'll override this value
	 * according to the detected HW
	 */
	hw_type = CSR_HW_REV_TYPE(fwrt->trans->hw_rev);
	अगर (hw_type == IWL_AX210_HW_TYPE) अणु
		u32 prph_val = iwl_पढ़ो_prph(fwrt->trans, WFPM_OTP_CFG1_ADDR);
		u32 is_jacket = !!(prph_val & WFPM_OTP_CFG1_IS_JACKET_BIT);
		u32 is_cdb = !!(prph_val & WFPM_OTP_CFG1_IS_CDB_BIT);
		u32 masked_bits = is_jacket | (is_cdb << 1);

		/*
		 * The HW type depends on certain bits in this हाल, so add
		 * these bits to the HW type. We won't have collisions since we
		 * add these bits after the highest possible bit in the mask.
		 */
		hw_type |= masked_bits << IWL_AX210_HW_TYPE_ADDITION_SHIFT;
	पूर्ण
	dump->hw_type = cpu_to_le32(hw_type);

	dump->rf_id_flavor =
		cpu_to_le32(CSR_HW_RFID_FLAVOR(fwrt->trans->hw_rf_id));
	dump->rf_id_dash = cpu_to_le32(CSR_HW_RFID_DASH(fwrt->trans->hw_rf_id));
	dump->rf_id_step = cpu_to_le32(CSR_HW_RFID_STEP(fwrt->trans->hw_rf_id));
	dump->rf_id_type = cpu_to_le32(CSR_HW_RFID_TYPE(fwrt->trans->hw_rf_id));

	dump->lmac_major = cpu_to_le32(fwrt->dump.fw_ver.lmac_major);
	dump->lmac_minor = cpu_to_le32(fwrt->dump.fw_ver.lmac_minor);
	dump->umac_major = cpu_to_le32(fwrt->dump.fw_ver.umac_major);
	dump->umac_minor = cpu_to_le32(fwrt->dump.fw_ver.umac_minor);

	dump->fw_mon_mode = cpu_to_le32(fwrt->trans->dbg.ini_dest);
	dump->regions_mask = trigger->regions_mask &
			     ~cpu_to_le64(fwrt->trans->dbg.unsupported_region_msk);

	dump->build_tag_len = cpu_to_le32(माप(dump->build_tag));
	स_नकल(dump->build_tag, fwrt->fw->human_पढ़ोable,
	       माप(dump->build_tag));

	cfg_name = dump->cfg_names;
	dump->num_of_cfg_names = cpu_to_le32(num_of_cfg_names);
	list_क्रम_each_entry(node, &fwrt->trans->dbg.debug_info_tlv_list, list) अणु
		काष्ठा iwl_fw_ini_debug_info_tlv *debug_info =
			(व्योम *)node->tlv.data;

		cfg_name->image_type = debug_info->image_type;
		cfg_name->cfg_name_len =
			cpu_to_le32(IWL_FW_INI_MAX_CFG_NAME);
		स_नकल(cfg_name->cfg_name, debug_info->debug_cfg_name,
		       माप(cfg_name->cfg_name));
		cfg_name++;
	पूर्ण

	/* add dump info TLV to the beginning of the list since it needs to be
	 * the first TLV in the dump
	 */
	list_add(&entry->list, list);

	वापस entry->size;
पूर्ण

अटल स्थिर काष्ठा iwl_dump_ini_mem_ops iwl_dump_ini_region_ops[] = अणु
	[IWL_FW_INI_REGION_INVALID] = अणुपूर्ण,
	[IWL_FW_INI_REGION_INTERNAL_BUFFER] = अणु
		.get_num_of_ranges = iwl_dump_ini_single_range,
		.get_size = iwl_dump_ini_mon_smem_get_size,
		.fill_mem_hdr = iwl_dump_ini_mon_smem_fill_header,
		.fill_range = iwl_dump_ini_mon_smem_iter,
	पूर्ण,
	[IWL_FW_INI_REGION_DRAM_BUFFER] = अणु
		.get_num_of_ranges = iwl_dump_ini_mon_dram_ranges,
		.get_size = iwl_dump_ini_mon_dram_get_size,
		.fill_mem_hdr = iwl_dump_ini_mon_dram_fill_header,
		.fill_range = iwl_dump_ini_mon_dram_iter,
	पूर्ण,
	[IWL_FW_INI_REGION_TXF] = अणु
		.get_num_of_ranges = iwl_dump_ini_txf_ranges,
		.get_size = iwl_dump_ini_txf_get_size,
		.fill_mem_hdr = iwl_dump_ini_mem_fill_header,
		.fill_range = iwl_dump_ini_txf_iter,
	पूर्ण,
	[IWL_FW_INI_REGION_RXF] = अणु
		.get_num_of_ranges = iwl_dump_ini_single_range,
		.get_size = iwl_dump_ini_rxf_get_size,
		.fill_mem_hdr = iwl_dump_ini_mem_fill_header,
		.fill_range = iwl_dump_ini_rxf_iter,
	पूर्ण,
	[IWL_FW_INI_REGION_LMAC_ERROR_TABLE] = अणु
		.get_num_of_ranges = iwl_dump_ini_single_range,
		.get_size = iwl_dump_ini_err_table_get_size,
		.fill_mem_hdr = iwl_dump_ini_err_table_fill_header,
		.fill_range = iwl_dump_ini_err_table_iter,
	पूर्ण,
	[IWL_FW_INI_REGION_UMAC_ERROR_TABLE] = अणु
		.get_num_of_ranges = iwl_dump_ini_single_range,
		.get_size = iwl_dump_ini_err_table_get_size,
		.fill_mem_hdr = iwl_dump_ini_err_table_fill_header,
		.fill_range = iwl_dump_ini_err_table_iter,
	पूर्ण,
	[IWL_FW_INI_REGION_RSP_OR_NOTIF] = अणु
		.get_num_of_ranges = iwl_dump_ini_single_range,
		.get_size = iwl_dump_ini_fw_pkt_get_size,
		.fill_mem_hdr = iwl_dump_ini_mem_fill_header,
		.fill_range = iwl_dump_ini_fw_pkt_iter,
	पूर्ण,
	[IWL_FW_INI_REGION_DEVICE_MEMORY] = अणु
		.get_num_of_ranges = iwl_dump_ini_mem_ranges,
		.get_size = iwl_dump_ini_mem_get_size,
		.fill_mem_hdr = iwl_dump_ini_mem_fill_header,
		.fill_range = iwl_dump_ini_dev_mem_iter,
	पूर्ण,
	[IWL_FW_INI_REGION_PERIPHERY_MAC] = अणु
		.get_num_of_ranges = iwl_dump_ini_mem_ranges,
		.get_size = iwl_dump_ini_mem_get_size,
		.fill_mem_hdr = iwl_dump_ini_mem_fill_header,
		.fill_range = iwl_dump_ini_prph_mac_iter,
	पूर्ण,
	[IWL_FW_INI_REGION_PERIPHERY_PHY] = अणु
		.get_num_of_ranges = iwl_dump_ini_mem_ranges,
		.get_size = iwl_dump_ini_mem_get_size,
		.fill_mem_hdr = iwl_dump_ini_mem_fill_header,
		.fill_range = iwl_dump_ini_prph_phy_iter,
	पूर्ण,
	[IWL_FW_INI_REGION_PERIPHERY_AUX] = अणुपूर्ण,
	[IWL_FW_INI_REGION_PAGING] = अणु
		.fill_mem_hdr = iwl_dump_ini_mem_fill_header,
		.get_num_of_ranges = iwl_dump_ini_paging_ranges,
		.get_size = iwl_dump_ini_paging_get_size,
		.fill_range = iwl_dump_ini_paging_iter,
	पूर्ण,
	[IWL_FW_INI_REGION_CSR] = अणु
		.get_num_of_ranges = iwl_dump_ini_mem_ranges,
		.get_size = iwl_dump_ini_mem_get_size,
		.fill_mem_hdr = iwl_dump_ini_mem_fill_header,
		.fill_range = iwl_dump_ini_csr_iter,
	पूर्ण,
	[IWL_FW_INI_REGION_DRAM_IMR] = अणुपूर्ण,
	[IWL_FW_INI_REGION_PCI_IOSF_CONFIG] = अणु
		.get_num_of_ranges = iwl_dump_ini_mem_ranges,
		.get_size = iwl_dump_ini_mem_get_size,
		.fill_mem_hdr = iwl_dump_ini_mem_fill_header,
		.fill_range = iwl_dump_ini_config_iter,
	पूर्ण,
	[IWL_FW_INI_REGION_SPECIAL_DEVICE_MEMORY] = अणु
		.get_num_of_ranges = iwl_dump_ini_single_range,
		.get_size = iwl_dump_ini_special_mem_get_size,
		.fill_mem_hdr = iwl_dump_ini_special_mem_fill_header,
		.fill_range = iwl_dump_ini_special_mem_iter,
	पूर्ण,
पूर्ण;

अटल u32 iwl_dump_ini_trigger(काष्ठा iwl_fw_runसमय *fwrt,
				काष्ठा iwl_fwrt_dump_data *dump_data,
				काष्ठा list_head *list)
अणु
	काष्ठा iwl_fw_ini_trigger_tlv *trigger = dump_data->trig;
	क्रमागत iwl_fw_ini_समय_poपूर्णांक tp_id = le32_to_cpu(trigger->समय_poपूर्णांक);
	काष्ठा iwl_dump_ini_region_data reg_data = अणु
		.dump_data = dump_data,
	पूर्ण;
	पूर्णांक i;
	u32 size = 0;
	u64 regions_mask = le64_to_cpu(trigger->regions_mask) &
			   ~(fwrt->trans->dbg.unsupported_region_msk);

	BUILD_BUG_ON(माप(trigger->regions_mask) != माप(regions_mask));
	BUILD_BUG_ON((माप(trigger->regions_mask) * BITS_PER_BYTE) <
		     ARRAY_SIZE(fwrt->trans->dbg.active_regions));

	क्रम (i = 0; i < ARRAY_SIZE(fwrt->trans->dbg.active_regions); i++) अणु
		u32 reg_type;
		काष्ठा iwl_fw_ini_region_tlv *reg;

		अगर (!(BIT_ULL(i) & regions_mask))
			जारी;

		reg_data.reg_tlv = fwrt->trans->dbg.active_regions[i];
		अगर (!reg_data.reg_tlv) अणु
			IWL_WARN(fwrt,
				 "WRT: Unassigned region id %d, skipping\n", i);
			जारी;
		पूर्ण

		reg = (व्योम *)reg_data.reg_tlv->data;
		reg_type = le32_to_cpu(reg->type);
		अगर (reg_type >= ARRAY_SIZE(iwl_dump_ini_region_ops))
			जारी;

		अगर (reg_type == IWL_FW_INI_REGION_PERIPHERY_PHY &&
		    tp_id != IWL_FW_INI_TIME_POINT_FW_ASSERT) अणु
			IWL_WARN(fwrt,
				 "WRT: trying to collect phy prph at time point: %d, skipping\n",
				 tp_id);
			जारी;
		पूर्ण

		size += iwl_dump_ini_mem(fwrt, list, &reg_data,
					 &iwl_dump_ini_region_ops[reg_type]);
	पूर्ण

	अगर (size)
		size += iwl_dump_ini_info(fwrt, trigger, list);

	वापस size;
पूर्ण

अटल bool iwl_fw_ini_trigger_on(काष्ठा iwl_fw_runसमय *fwrt,
				  काष्ठा iwl_fw_ini_trigger_tlv *trig)
अणु
	क्रमागत iwl_fw_ini_समय_poपूर्णांक tp_id = le32_to_cpu(trig->समय_poपूर्णांक);
	u32 usec = le32_to_cpu(trig->ignore_consec);

	अगर (!iwl_trans_dbg_ini_valid(fwrt->trans) ||
	    tp_id == IWL_FW_INI_TIME_POINT_INVALID ||
	    tp_id >= IWL_FW_INI_TIME_POINT_NUM ||
	    iwl_fw_dbg_no_trig_winकरोw(fwrt, tp_id, usec))
		वापस false;

	वापस true;
पूर्ण

अटल u32 iwl_dump_ini_file_gen(काष्ठा iwl_fw_runसमय *fwrt,
				 काष्ठा iwl_fwrt_dump_data *dump_data,
				 काष्ठा list_head *list)
अणु
	काष्ठा iwl_fw_ini_trigger_tlv *trigger = dump_data->trig;
	काष्ठा iwl_fw_ini_dump_entry *entry;
	काष्ठा iwl_fw_ini_dump_file_hdr *hdr;
	u32 size;

	अगर (!trigger || !iwl_fw_ini_trigger_on(fwrt, trigger) ||
	    !le64_to_cpu(trigger->regions_mask))
		वापस 0;

	entry = vzalloc(माप(*entry) + माप(*hdr));
	अगर (!entry)
		वापस 0;

	entry->size = माप(*hdr);

	size = iwl_dump_ini_trigger(fwrt, dump_data, list);
	अगर (!size) अणु
		vमुक्त(entry);
		वापस 0;
	पूर्ण

	hdr = (व्योम *)entry->data;
	hdr->barker = cpu_to_le32(IWL_FW_INI_ERROR_DUMP_BARKER);
	hdr->file_len = cpu_to_le32(size + entry->size);

	list_add(&entry->list, list);

	वापस le32_to_cpu(hdr->file_len);
पूर्ण

अटल अंतरभूत व्योम iwl_fw_मुक्त_dump_desc(काष्ठा iwl_fw_runसमय *fwrt,
					 स्थिर काष्ठा iwl_fw_dump_desc *desc)
अणु
	अगर (desc && desc != &iwl_dump_desc_निश्चित)
		kमुक्त(desc);

	fwrt->dump.lmac_err_id[0] = 0;
	अगर (fwrt->smem_cfg.num_lmacs > 1)
		fwrt->dump.lmac_err_id[1] = 0;
	fwrt->dump.umac_err_id = 0;
पूर्ण

अटल व्योम iwl_fw_error_dump(काष्ठा iwl_fw_runसमय *fwrt,
			      काष्ठा iwl_fwrt_dump_data *dump_data)
अणु
	काष्ठा iwl_fw_dump_ptrs fw_error_dump = अणुपूर्ण;
	काष्ठा iwl_fw_error_dump_file *dump_file;
	काष्ठा scatterlist *sg_dump_data;
	u32 file_len;
	u32 dump_mask = fwrt->fw->dbg.dump_mask;

	dump_file = iwl_fw_error_dump_file(fwrt, &fw_error_dump, dump_data);
	अगर (!dump_file)
		वापस;

	अगर (dump_data->monitor_only)
		dump_mask &= IWL_FW_ERROR_DUMP_FW_MONITOR;

	fw_error_dump.trans_ptr = iwl_trans_dump_data(fwrt->trans, dump_mask);
	file_len = le32_to_cpu(dump_file->file_len);
	fw_error_dump.fwrt_len = file_len;

	अगर (fw_error_dump.trans_ptr) अणु
		file_len += fw_error_dump.trans_ptr->len;
		dump_file->file_len = cpu_to_le32(file_len);
	पूर्ण

	sg_dump_data = alloc_sgtable(file_len);
	अगर (sg_dump_data) अणु
		sg_pcopy_from_buffer(sg_dump_data,
				     sg_nents(sg_dump_data),
				     fw_error_dump.fwrt_ptr,
				     fw_error_dump.fwrt_len, 0);
		अगर (fw_error_dump.trans_ptr)
			sg_pcopy_from_buffer(sg_dump_data,
					     sg_nents(sg_dump_data),
					     fw_error_dump.trans_ptr->data,
					     fw_error_dump.trans_ptr->len,
					     fw_error_dump.fwrt_len);
		dev_coredumpsg(fwrt->trans->dev, sg_dump_data, file_len,
			       GFP_KERNEL);
	पूर्ण
	vमुक्त(fw_error_dump.fwrt_ptr);
	vमुक्त(fw_error_dump.trans_ptr);
पूर्ण

अटल व्योम iwl_dump_ini_list_मुक्त(काष्ठा list_head *list)
अणु
	जबतक (!list_empty(list)) अणु
		काष्ठा iwl_fw_ini_dump_entry *entry =
			list_entry(list->next, typeof(*entry), list);

		list_del(&entry->list);
		vमुक्त(entry);
	पूर्ण
पूर्ण

अटल व्योम iwl_fw_error_dump_data_मुक्त(काष्ठा iwl_fwrt_dump_data *dump_data)
अणु
	dump_data->trig = शून्य;
	kमुक्त(dump_data->fw_pkt);
	dump_data->fw_pkt = शून्य;
पूर्ण

अटल व्योम iwl_fw_error_ini_dump(काष्ठा iwl_fw_runसमय *fwrt,
				  काष्ठा iwl_fwrt_dump_data *dump_data)
अणु
	काष्ठा list_head dump_list = LIST_HEAD_INIT(dump_list);
	काष्ठा scatterlist *sg_dump_data;
	u32 file_len = iwl_dump_ini_file_gen(fwrt, dump_data, &dump_list);

	अगर (!file_len)
		वापस;

	sg_dump_data = alloc_sgtable(file_len);
	अगर (sg_dump_data) अणु
		काष्ठा iwl_fw_ini_dump_entry *entry;
		पूर्णांक sg_entries = sg_nents(sg_dump_data);
		u32 offs = 0;

		list_क्रम_each_entry(entry, &dump_list, list) अणु
			sg_pcopy_from_buffer(sg_dump_data, sg_entries,
					     entry->data, entry->size, offs);
			offs += entry->size;
		पूर्ण
		dev_coredumpsg(fwrt->trans->dev, sg_dump_data, file_len,
			       GFP_KERNEL);
	पूर्ण
	iwl_dump_ini_list_मुक्त(&dump_list);
पूर्ण

स्थिर काष्ठा iwl_fw_dump_desc iwl_dump_desc_निश्चित = अणु
	.trig_desc = अणु
		.type = cpu_to_le32(FW_DBG_TRIGGER_FW_ASSERT),
	पूर्ण,
पूर्ण;
IWL_EXPORT_SYMBOL(iwl_dump_desc_निश्चित);

पूर्णांक iwl_fw_dbg_collect_desc(काष्ठा iwl_fw_runसमय *fwrt,
			    स्थिर काष्ठा iwl_fw_dump_desc *desc,
			    bool monitor_only,
			    अचिन्हित पूर्णांक delay)
अणु
	काष्ठा iwl_fwrt_wk_data *wk_data;
	अचिन्हित दीर्घ idx;

	अगर (iwl_trans_dbg_ini_valid(fwrt->trans)) अणु
		iwl_fw_मुक्त_dump_desc(fwrt, desc);
		वापस 0;
	पूर्ण

	/*
	 * Check there is an available worker.
	 * ffz वापस value is undefined अगर no zero exists,
	 * so check against ~0UL first.
	 */
	अगर (fwrt->dump.active_wks == ~0UL)
		वापस -EBUSY;

	idx = ffz(fwrt->dump.active_wks);

	अगर (idx >= IWL_FW_RUNTIME_DUMP_WK_NUM ||
	    test_and_set_bit(fwrt->dump.wks[idx].idx, &fwrt->dump.active_wks))
		वापस -EBUSY;

	wk_data = &fwrt->dump.wks[idx];

	अगर (WARN_ON(wk_data->dump_data.desc))
		iwl_fw_मुक्त_dump_desc(fwrt, wk_data->dump_data.desc);

	wk_data->dump_data.desc = desc;
	wk_data->dump_data.monitor_only = monitor_only;

	IWL_WARN(fwrt, "Collecting data: trigger %d fired.\n",
		 le32_to_cpu(desc->trig_desc.type));

	schedule_delayed_work(&wk_data->wk, usecs_to_jअगरfies(delay));

	वापस 0;
पूर्ण
IWL_EXPORT_SYMBOL(iwl_fw_dbg_collect_desc);

पूर्णांक iwl_fw_dbg_error_collect(काष्ठा iwl_fw_runसमय *fwrt,
			     क्रमागत iwl_fw_dbg_trigger trig_type)
अणु
	अगर (!test_bit(STATUS_DEVICE_ENABLED, &fwrt->trans->status))
		वापस -EIO;

	अगर (iwl_trans_dbg_ini_valid(fwrt->trans)) अणु
		अगर (trig_type != FW_DBG_TRIGGER_ALIVE_TIMEOUT &&
		    trig_type != FW_DBG_TRIGGER_DRIVER)
			वापस -EIO;

		iwl_dbg_tlv_समय_poपूर्णांक(fwrt,
				       IWL_FW_INI_TIME_POINT_HOST_ALIVE_TIMEOUT,
				       शून्य);
	पूर्ण अन्यथा अणु
		काष्ठा iwl_fw_dump_desc *iwl_dump_error_desc;
		पूर्णांक ret;

		iwl_dump_error_desc =
			kदो_स्मृति(माप(*iwl_dump_error_desc), GFP_KERNEL);

		अगर (!iwl_dump_error_desc)
			वापस -ENOMEM;

		iwl_dump_error_desc->trig_desc.type = cpu_to_le32(trig_type);
		iwl_dump_error_desc->len = 0;

		ret = iwl_fw_dbg_collect_desc(fwrt, iwl_dump_error_desc,
					      false, 0);
		अगर (ret) अणु
			kमुक्त(iwl_dump_error_desc);
			वापस ret;
		पूर्ण
	पूर्ण

	iwl_trans_sync_nmi(fwrt->trans);

	वापस 0;
पूर्ण
IWL_EXPORT_SYMBOL(iwl_fw_dbg_error_collect);

पूर्णांक iwl_fw_dbg_collect(काष्ठा iwl_fw_runसमय *fwrt,
		       क्रमागत iwl_fw_dbg_trigger trig,
		       स्थिर अक्षर *str, माप_प्रकार len,
		       काष्ठा iwl_fw_dbg_trigger_tlv *trigger)
अणु
	काष्ठा iwl_fw_dump_desc *desc;
	अचिन्हित पूर्णांक delay = 0;
	bool monitor_only = false;

	अगर (trigger) अणु
		u16 occurrences = le16_to_cpu(trigger->occurrences) - 1;

		अगर (!le16_to_cpu(trigger->occurrences))
			वापस 0;

		अगर (trigger->flags & IWL_FW_DBG_FORCE_RESTART) अणु
			IWL_WARN(fwrt, "Force restart: trigger %d fired.\n",
				 trig);
			iwl_क्रमce_nmi(fwrt->trans);
			वापस 0;
		पूर्ण

		trigger->occurrences = cpu_to_le16(occurrences);
		monitor_only = trigger->mode & IWL_FW_DBG_TRIGGER_MONITOR_ONLY;

		/* convert msec to usec */
		delay = le32_to_cpu(trigger->stop_delay) * USEC_PER_MSEC;
	पूर्ण

	desc = kzalloc(माप(*desc) + len, GFP_ATOMIC);
	अगर (!desc)
		वापस -ENOMEM;


	desc->len = len;
	desc->trig_desc.type = cpu_to_le32(trig);
	स_नकल(desc->trig_desc.data, str, len);

	वापस iwl_fw_dbg_collect_desc(fwrt, desc, monitor_only, delay);
पूर्ण
IWL_EXPORT_SYMBOL(iwl_fw_dbg_collect);

पूर्णांक iwl_fw_dbg_ini_collect(काष्ठा iwl_fw_runसमय *fwrt,
			   काष्ठा iwl_fwrt_dump_data *dump_data)
अणु
	काष्ठा iwl_fw_ini_trigger_tlv *trig = dump_data->trig;
	क्रमागत iwl_fw_ini_समय_poपूर्णांक tp_id = le32_to_cpu(trig->समय_poपूर्णांक);
	u32 occur, delay;
	अचिन्हित दीर्घ idx;

	अगर (!iwl_fw_ini_trigger_on(fwrt, trig)) अणु
		IWL_WARN(fwrt, "WRT: Trigger %d is not active, aborting dump\n",
			 tp_id);
		वापस -EINVAL;
	पूर्ण

	delay = le32_to_cpu(trig->dump_delay);
	occur = le32_to_cpu(trig->occurrences);
	अगर (!occur)
		वापस 0;

	trig->occurrences = cpu_to_le32(--occur);

	/* Check there is an available worker.
	 * ffz वापस value is undefined अगर no zero exists,
	 * so check against ~0UL first.
	 */
	अगर (fwrt->dump.active_wks == ~0UL)
		वापस -EBUSY;

	idx = ffz(fwrt->dump.active_wks);

	अगर (idx >= IWL_FW_RUNTIME_DUMP_WK_NUM ||
	    test_and_set_bit(fwrt->dump.wks[idx].idx, &fwrt->dump.active_wks))
		वापस -EBUSY;

	fwrt->dump.wks[idx].dump_data = *dump_data;

	IWL_WARN(fwrt,
		 "WRT: Collecting data: ini trigger %d fired (delay=%dms).\n",
		 tp_id, (u32)(delay / USEC_PER_MSEC));

	schedule_delayed_work(&fwrt->dump.wks[idx].wk, usecs_to_jअगरfies(delay));

	वापस 0;
पूर्ण

पूर्णांक iwl_fw_dbg_collect_trig(काष्ठा iwl_fw_runसमय *fwrt,
			    काष्ठा iwl_fw_dbg_trigger_tlv *trigger,
			    स्थिर अक्षर *fmt, ...)
अणु
	पूर्णांक ret, len = 0;
	अक्षर buf[64];

	अगर (iwl_trans_dbg_ini_valid(fwrt->trans))
		वापस 0;

	अगर (fmt) अणु
		बहु_सूची ap;

		buf[माप(buf) - 1] = '\0';

		बहु_शुरू(ap, fmt);
		vsnम_लिखो(buf, माप(buf), fmt, ap);
		बहु_पूर्ण(ap);

		/* check क्रम truncation */
		अगर (WARN_ON_ONCE(buf[माप(buf) - 1]))
			buf[माप(buf) - 1] = '\0';

		len = म_माप(buf) + 1;
	पूर्ण

	ret = iwl_fw_dbg_collect(fwrt, le32_to_cpu(trigger->id), buf, len,
				 trigger);

	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण
IWL_EXPORT_SYMBOL(iwl_fw_dbg_collect_trig);

पूर्णांक iwl_fw_start_dbg_conf(काष्ठा iwl_fw_runसमय *fwrt, u8 conf_id)
अणु
	u8 *ptr;
	पूर्णांक ret;
	पूर्णांक i;

	अगर (WARN_ONCE(conf_id >= ARRAY_SIZE(fwrt->fw->dbg.conf_tlv),
		      "Invalid configuration %d\n", conf_id))
		वापस -EINVAL;

	/* EARLY START - firmware's configuration is hard coded */
	अगर ((!fwrt->fw->dbg.conf_tlv[conf_id] ||
	     !fwrt->fw->dbg.conf_tlv[conf_id]->num_of_hcmds) &&
	    conf_id == FW_DBG_START_FROM_ALIVE)
		वापस 0;

	अगर (!fwrt->fw->dbg.conf_tlv[conf_id])
		वापस -EINVAL;

	अगर (fwrt->dump.conf != FW_DBG_INVALID)
		IWL_INFO(fwrt, "FW already configured (%d) - re-configuring\n",
			 fwrt->dump.conf);

	/* Send all HCMDs क्रम configuring the FW debug */
	ptr = (व्योम *)&fwrt->fw->dbg.conf_tlv[conf_id]->hcmd;
	क्रम (i = 0; i < fwrt->fw->dbg.conf_tlv[conf_id]->num_of_hcmds; i++) अणु
		काष्ठा iwl_fw_dbg_conf_hcmd *cmd = (व्योम *)ptr;
		काष्ठा iwl_host_cmd hcmd = अणु
			.id = cmd->id,
			.len = अणु le16_to_cpu(cmd->len), पूर्ण,
			.data = अणु cmd->data, पूर्ण,
		पूर्ण;

		ret = iwl_trans_send_cmd(fwrt->trans, &hcmd);
		अगर (ret)
			वापस ret;

		ptr += माप(*cmd);
		ptr += le16_to_cpu(cmd->len);
	पूर्ण

	fwrt->dump.conf = conf_id;

	वापस 0;
पूर्ण
IWL_EXPORT_SYMBOL(iwl_fw_start_dbg_conf);

/* this function assumes dump_start was called beक्रमehand and dump_end will be
 * called afterwards
 */
अटल व्योम iwl_fw_dbg_collect_sync(काष्ठा iwl_fw_runसमय *fwrt, u8 wk_idx)
अणु
	काष्ठा iwl_fw_dbg_params params = अणु0पूर्ण;
	काष्ठा iwl_fwrt_dump_data *dump_data =
		&fwrt->dump.wks[wk_idx].dump_data;

	अगर (!test_bit(wk_idx, &fwrt->dump.active_wks))
		वापस;

	अगर (!test_bit(STATUS_DEVICE_ENABLED, &fwrt->trans->status)) अणु
		IWL_ERR(fwrt, "Device is not enabled - cannot dump error\n");
		जाओ out;
	पूर्ण

	/* there's no poपूर्णांक in fw dump अगर the bus is dead */
	अगर (test_bit(STATUS_TRANS_DEAD, &fwrt->trans->status)) अणु
		IWL_ERR(fwrt, "Skip fw error dump since bus is dead\n");
		जाओ out;
	पूर्ण

	iwl_fw_dbg_stop_restart_recording(fwrt, &params, true);

	IWL_DEBUG_FW_INFO(fwrt, "WRT: Data collection start\n");
	अगर (iwl_trans_dbg_ini_valid(fwrt->trans))
		iwl_fw_error_ini_dump(fwrt, &fwrt->dump.wks[wk_idx].dump_data);
	अन्यथा
		iwl_fw_error_dump(fwrt, &fwrt->dump.wks[wk_idx].dump_data);
	IWL_DEBUG_FW_INFO(fwrt, "WRT: Data collection done\n");

	iwl_fw_dbg_stop_restart_recording(fwrt, &params, false);

out:
	अगर (iwl_trans_dbg_ini_valid(fwrt->trans)) अणु
		iwl_fw_error_dump_data_मुक्त(dump_data);
	पूर्ण अन्यथा अणु
		iwl_fw_मुक्त_dump_desc(fwrt, dump_data->desc);
		dump_data->desc = शून्य;
	पूर्ण

	clear_bit(wk_idx, &fwrt->dump.active_wks);
पूर्ण

व्योम iwl_fw_error_dump_wk(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा iwl_fwrt_wk_data *wks =
		container_of(work, typeof(*wks), wk.work);
	काष्ठा iwl_fw_runसमय *fwrt =
		container_of(wks, typeof(*fwrt), dump.wks[wks->idx]);

	/* assumes the op mode mutex is locked in dump_start since
	 * iwl_fw_dbg_collect_sync can't run in parallel
	 */
	अगर (fwrt->ops && fwrt->ops->dump_start &&
	    fwrt->ops->dump_start(fwrt->ops_ctx))
		वापस;

	iwl_fw_dbg_collect_sync(fwrt, wks->idx);

	अगर (fwrt->ops && fwrt->ops->dump_end)
		fwrt->ops->dump_end(fwrt->ops_ctx);
पूर्ण

व्योम iwl_fw_dbg_पढ़ो_d3_debug_data(काष्ठा iwl_fw_runसमय *fwrt)
अणु
	स्थिर काष्ठा iwl_cfg *cfg = fwrt->trans->cfg;

	अगर (!iwl_fw_dbg_is_d3_debug_enabled(fwrt))
		वापस;

	अगर (!fwrt->dump.d3_debug_data) अणु
		fwrt->dump.d3_debug_data = kदो_स्मृति(cfg->d3_debug_data_length,
						   GFP_KERNEL);
		अगर (!fwrt->dump.d3_debug_data) अणु
			IWL_ERR(fwrt,
				"failed to allocate memory for D3 debug data\n");
			वापस;
		पूर्ण
	पूर्ण

	/* अगर the buffer holds previous debug data it is overwritten */
	iwl_trans_पढ़ो_mem_bytes(fwrt->trans, cfg->d3_debug_data_base_addr,
				 fwrt->dump.d3_debug_data,
				 cfg->d3_debug_data_length);
पूर्ण
IWL_EXPORT_SYMBOL(iwl_fw_dbg_पढ़ो_d3_debug_data);

व्योम iwl_fw_dbg_stop_sync(काष्ठा iwl_fw_runसमय *fwrt)
अणु
	पूर्णांक i;

	iwl_dbg_tlv_del_समयrs(fwrt->trans);
	क्रम (i = 0; i < IWL_FW_RUNTIME_DUMP_WK_NUM; i++)
		iwl_fw_dbg_collect_sync(fwrt, i);

	iwl_fw_dbg_stop_restart_recording(fwrt, शून्य, true);
पूर्ण
IWL_EXPORT_SYMBOL(iwl_fw_dbg_stop_sync);

#घोषणा FSEQ_REG(x) अणु .addr = (x), .str = #x, पूर्ण

व्योम iwl_fw_error_prपूर्णांक_fseq_regs(काष्ठा iwl_fw_runसमय *fwrt)
अणु
	काष्ठा iwl_trans *trans = fwrt->trans;
	पूर्णांक i;
	काष्ठा अणु
		u32 addr;
		स्थिर अक्षर *str;
	पूर्ण fseq_regs[] = अणु
		FSEQ_REG(FSEQ_ERROR_CODE),
		FSEQ_REG(FSEQ_TOP_INIT_VERSION),
		FSEQ_REG(FSEQ_CNVIO_INIT_VERSION),
		FSEQ_REG(FSEQ_OTP_VERSION),
		FSEQ_REG(FSEQ_TOP_CONTENT_VERSION),
		FSEQ_REG(FSEQ_ALIVE_TOKEN),
		FSEQ_REG(FSEQ_CNVI_ID),
		FSEQ_REG(FSEQ_CNVR_ID),
		FSEQ_REG(CNVI_AUX_MISC_CHIP),
		FSEQ_REG(CNVR_AUX_MISC_CHIP),
		FSEQ_REG(CNVR_SCU_SD_REGS_SD_REG_DIG_DCDC_VTRIM),
		FSEQ_REG(CNVR_SCU_SD_REGS_SD_REG_ACTIVE_VDIG_MIRROR),
	पूर्ण;

	अगर (!iwl_trans_grab_nic_access(trans))
		वापस;

	IWL_ERR(fwrt, "Fseq Registers:\n");

	क्रम (i = 0; i < ARRAY_SIZE(fseq_regs); i++)
		IWL_ERR(fwrt, "0x%08X | %s\n",
			iwl_पढ़ो_prph_no_grab(trans, fseq_regs[i].addr),
			fseq_regs[i].str);

	iwl_trans_release_nic_access(trans);
पूर्ण
IWL_EXPORT_SYMBOL(iwl_fw_error_prपूर्णांक_fseq_regs);

अटल पूर्णांक iwl_fw_dbg_suspend_resume_hcmd(काष्ठा iwl_trans *trans, bool suspend)
अणु
	काष्ठा iwl_dbg_suspend_resume_cmd cmd = अणु
		.operation = suspend ?
			cpu_to_le32(DBGC_SUSPEND_CMD) :
			cpu_to_le32(DBGC_RESUME_CMD),
	पूर्ण;
	काष्ठा iwl_host_cmd hcmd = अणु
		.id = WIDE_ID(DEBUG_GROUP, DBGC_SUSPEND_RESUME),
		.data[0] = &cmd,
		.len[0] = माप(cmd),
	पूर्ण;

	वापस iwl_trans_send_cmd(trans, &hcmd);
पूर्ण

अटल व्योम iwl_fw_dbg_stop_recording(काष्ठा iwl_trans *trans,
				      काष्ठा iwl_fw_dbg_params *params)
अणु
	अगर (trans->trans_cfg->device_family == IWL_DEVICE_FAMILY_7000) अणु
		iwl_set_bits_prph(trans, MON_BUFF_SAMPLE_CTL, 0x100);
		वापस;
	पूर्ण

	अगर (params) अणु
		params->in_sample = iwl_पढ़ो_umac_prph(trans, DBGC_IN_SAMPLE);
		params->out_ctrl = iwl_पढ़ो_umac_prph(trans, DBGC_OUT_CTRL);
	पूर्ण

	iwl_ग_लिखो_umac_prph(trans, DBGC_IN_SAMPLE, 0);
	/* रुको क्रम the DBGC to finish writing the पूर्णांकernal buffer to DRAM to
	 * aव्योम halting the HW जबतक writing
	 */
	usleep_range(700, 1000);
	iwl_ग_लिखो_umac_prph(trans, DBGC_OUT_CTRL, 0);
पूर्ण

अटल पूर्णांक iwl_fw_dbg_restart_recording(काष्ठा iwl_trans *trans,
					काष्ठा iwl_fw_dbg_params *params)
अणु
	अगर (!params)
		वापस -EIO;

	अगर (trans->trans_cfg->device_family == IWL_DEVICE_FAMILY_7000) अणु
		iwl_clear_bits_prph(trans, MON_BUFF_SAMPLE_CTL, 0x100);
		iwl_clear_bits_prph(trans, MON_BUFF_SAMPLE_CTL, 0x1);
		iwl_set_bits_prph(trans, MON_BUFF_SAMPLE_CTL, 0x1);
	पूर्ण अन्यथा अणु
		iwl_ग_लिखो_umac_prph(trans, DBGC_IN_SAMPLE, params->in_sample);
		iwl_ग_लिखो_umac_prph(trans, DBGC_OUT_CTRL, params->out_ctrl);
	पूर्ण

	वापस 0;
पूर्ण

व्योम iwl_fw_dbg_stop_restart_recording(काष्ठा iwl_fw_runसमय *fwrt,
				       काष्ठा iwl_fw_dbg_params *params,
				       bool stop)
अणु
	पूर्णांक ret __maybe_unused = 0;

	अगर (test_bit(STATUS_FW_ERROR, &fwrt->trans->status))
		वापस;

	अगर (fw_has_capa(&fwrt->fw->ucode_capa,
			IWL_UCODE_TLV_CAPA_DBG_SUSPEND_RESUME_CMD_SUPP))
		ret = iwl_fw_dbg_suspend_resume_hcmd(fwrt->trans, stop);
	अन्यथा अगर (stop)
		iwl_fw_dbg_stop_recording(fwrt->trans, params);
	अन्यथा
		ret = iwl_fw_dbg_restart_recording(fwrt->trans, params);
#अगर_घोषित CONFIG_IWLWIFI_DEBUGFS
	अगर (!ret) अणु
		अगर (stop)
			fwrt->trans->dbg.rec_on = false;
		अन्यथा
			iwl_fw_set_dbg_rec_on(fwrt);
	पूर्ण
#पूर्ण_अगर
पूर्ण
IWL_EXPORT_SYMBOL(iwl_fw_dbg_stop_restart_recording);
