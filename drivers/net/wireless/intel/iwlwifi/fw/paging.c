<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/*
 * Copyright (C) 2012-2014, 2018-2019 Intel Corporation
 * Copyright (C) 2013-2015 Intel Mobile Communications GmbH
 * Copyright (C) 2016-2017 Intel Deutschland GmbH
 */
#समावेश "iwl-drv.h"
#समावेश "runtime.h"
#समावेश "fw/api/commands.h"

व्योम iwl_मुक्त_fw_paging(काष्ठा iwl_fw_runसमय *fwrt)
अणु
	पूर्णांक i;

	अगर (!fwrt->fw_paging_db[0].fw_paging_block)
		वापस;

	क्रम (i = 0; i < NUM_OF_FW_PAGING_BLOCKS; i++) अणु
		काष्ठा iwl_fw_paging *paging = &fwrt->fw_paging_db[i];

		अगर (!paging->fw_paging_block) अणु
			IWL_DEBUG_FW(fwrt,
				     "Paging: block %d already freed, continue to next page\n",
				     i);

			जारी;
		पूर्ण
		dma_unmap_page(fwrt->trans->dev, paging->fw_paging_phys,
			       paging->fw_paging_size, DMA_BIसूचीECTIONAL);

		__मुक्त_pages(paging->fw_paging_block,
			     get_order(paging->fw_paging_size));
		paging->fw_paging_block = शून्य;
	पूर्ण

	स_रखो(fwrt->fw_paging_db, 0, माप(fwrt->fw_paging_db));
पूर्ण
IWL_EXPORT_SYMBOL(iwl_मुक्त_fw_paging);

अटल पूर्णांक iwl_alloc_fw_paging_mem(काष्ठा iwl_fw_runसमय *fwrt,
				   स्थिर काष्ठा fw_img *image)
अणु
	काष्ठा page *block;
	dma_addr_t phys = 0;
	पूर्णांक blk_idx, order, num_of_pages, size;

	अगर (fwrt->fw_paging_db[0].fw_paging_block)
		वापस 0;

	/* ensure BLOCK_2_EXP_SIZE is घातer of 2 of PAGING_BLOCK_SIZE */
	BUILD_BUG_ON(BIT(BLOCK_2_EXP_SIZE) != PAGING_BLOCK_SIZE);

	num_of_pages = image->paging_mem_size / FW_PAGING_SIZE;
	fwrt->num_of_paging_blk =
		DIV_ROUND_UP(num_of_pages, NUM_OF_PAGE_PER_GROUP);
	fwrt->num_of_pages_in_last_blk =
		num_of_pages -
		NUM_OF_PAGE_PER_GROUP * (fwrt->num_of_paging_blk - 1);

	IWL_DEBUG_FW(fwrt,
		     "Paging: allocating mem for %d paging blocks, each block holds 8 pages, last block holds %d pages\n",
		     fwrt->num_of_paging_blk,
		     fwrt->num_of_pages_in_last_blk);

	/*
	 * Allocate CSS and paging blocks in dram.
	 */
	क्रम (blk_idx = 0; blk_idx < fwrt->num_of_paging_blk + 1; blk_idx++) अणु
		/* For CSS allocate 4KB, क्रम others PAGING_BLOCK_SIZE (32K) */
		size = blk_idx ? PAGING_BLOCK_SIZE : FW_PAGING_SIZE;
		order = get_order(size);
		block = alloc_pages(GFP_KERNEL, order);
		अगर (!block) अणु
			/* मुक्त all the previous pages since we failed */
			iwl_मुक्त_fw_paging(fwrt);
			वापस -ENOMEM;
		पूर्ण

		fwrt->fw_paging_db[blk_idx].fw_paging_block = block;
		fwrt->fw_paging_db[blk_idx].fw_paging_size = size;

		phys = dma_map_page(fwrt->trans->dev, block, 0,
				    PAGE_SIZE << order,
				    DMA_BIसूचीECTIONAL);
		अगर (dma_mapping_error(fwrt->trans->dev, phys)) अणु
			/*
			 * मुक्त the previous pages and the current one
			 * since we failed to map_page.
			 */
			iwl_मुक्त_fw_paging(fwrt);
			वापस -ENOMEM;
		पूर्ण
		fwrt->fw_paging_db[blk_idx].fw_paging_phys = phys;

		अगर (!blk_idx)
			IWL_DEBUG_FW(fwrt,
				     "Paging: allocated 4K(CSS) bytes (order %d) for firmware paging.\n",
				     order);
		अन्यथा
			IWL_DEBUG_FW(fwrt,
				     "Paging: allocated 32K bytes (order %d) for firmware paging.\n",
				     order);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक iwl_fill_paging_mem(काष्ठा iwl_fw_runसमय *fwrt,
			       स्थिर काष्ठा fw_img *image)
अणु
	पूर्णांक sec_idx, idx, ret;
	u32 offset = 0;

	/*
	 * find where is the paging image start poपूर्णांक:
	 * अगर CPU2 exist and it's in paging क्रमmat, then the image looks like:
	 * CPU1 sections (2 or more)
	 * CPU1_CPU2_SEPARATOR_SECTION delimiter - separate between CPU1 to CPU2
	 * CPU2 sections (not paged)
	 * PAGING_SEPARATOR_SECTION delimiter - separate between CPU2
	 * non paged to CPU2 paging sec
	 * CPU2 paging CSS
	 * CPU2 paging image (including inकाष्ठाion and data)
	 */
	क्रम (sec_idx = 0; sec_idx < image->num_sec; sec_idx++) अणु
		अगर (image->sec[sec_idx].offset == PAGING_SEPARATOR_SECTION) अणु
			sec_idx++;
			अवरोध;
		पूर्ण
	पूर्ण

	/*
	 * If paging is enabled there should be at least 2 more sections left
	 * (one क्रम CSS and one क्रम Paging data)
	 */
	अगर (sec_idx >= image->num_sec - 1) अणु
		IWL_ERR(fwrt, "Paging: Missing CSS and/or paging sections\n");
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	/* copy the CSS block to the dram */
	IWL_DEBUG_FW(fwrt, "Paging: load paging CSS to FW, sec = %d\n",
		     sec_idx);

	अगर (image->sec[sec_idx].len > fwrt->fw_paging_db[0].fw_paging_size) अणु
		IWL_ERR(fwrt, "CSS block is larger than paging size\n");
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	स_नकल(page_address(fwrt->fw_paging_db[0].fw_paging_block),
	       image->sec[sec_idx].data,
	       image->sec[sec_idx].len);
	dma_sync_single_क्रम_device(fwrt->trans->dev,
				   fwrt->fw_paging_db[0].fw_paging_phys,
				   fwrt->fw_paging_db[0].fw_paging_size,
				   DMA_BIसूचीECTIONAL);

	IWL_DEBUG_FW(fwrt,
		     "Paging: copied %d CSS bytes to first block\n",
		     fwrt->fw_paging_db[0].fw_paging_size);

	sec_idx++;

	/*
	 * Copy the paging blocks to the dram.  The loop index starts
	 * from 1 since the CSS block (index 0) was alपढ़ोy copied to
	 * dram.  We use num_of_paging_blk + 1 to account क्रम that.
	 */
	क्रम (idx = 1; idx < fwrt->num_of_paging_blk + 1; idx++) अणु
		काष्ठा iwl_fw_paging *block = &fwrt->fw_paging_db[idx];
		पूर्णांक reमुख्यing = image->sec[sec_idx].len - offset;
		पूर्णांक len = block->fw_paging_size;

		/*
		 * For the last block, we copy all that is reमुख्यing,
		 * क्रम all other blocks, we copy fw_paging_size at a
		 * समय. */
		अगर (idx == fwrt->num_of_paging_blk) अणु
			len = reमुख्यing;
			अगर (reमुख्यing !=
			    fwrt->num_of_pages_in_last_blk * FW_PAGING_SIZE) अणु
				IWL_ERR(fwrt,
					"Paging: last block contains more data than expected %d\n",
					reमुख्यing);
				ret = -EINVAL;
				जाओ err;
			पूर्ण
		पूर्ण अन्यथा अगर (block->fw_paging_size > reमुख्यing) अणु
			IWL_ERR(fwrt,
				"Paging: not enough data in other in block %d (%d)\n",
				idx, reमुख्यing);
			ret = -EINVAL;
			जाओ err;
		पूर्ण

		स_नकल(page_address(block->fw_paging_block),
		       image->sec[sec_idx].data + offset, len);
		dma_sync_single_क्रम_device(fwrt->trans->dev,
					   block->fw_paging_phys,
					   block->fw_paging_size,
					   DMA_BIसूचीECTIONAL);

		IWL_DEBUG_FW(fwrt,
			     "Paging: copied %d paging bytes to block %d\n",
			     len, idx);

		offset += block->fw_paging_size;
	पूर्ण

	वापस 0;

err:
	iwl_मुक्त_fw_paging(fwrt);
	वापस ret;
पूर्ण

अटल पूर्णांक iwl_save_fw_paging(काष्ठा iwl_fw_runसमय *fwrt,
			      स्थिर काष्ठा fw_img *fw)
अणु
	पूर्णांक ret;

	ret = iwl_alloc_fw_paging_mem(fwrt, fw);
	अगर (ret)
		वापस ret;

	वापस iwl_fill_paging_mem(fwrt, fw);
पूर्ण

/* send paging cmd to FW in हाल CPU2 has paging image */
अटल पूर्णांक iwl_send_paging_cmd(काष्ठा iwl_fw_runसमय *fwrt,
			       स्थिर काष्ठा fw_img *fw)
अणु
	काष्ठा iwl_fw_paging_cmd paging_cmd = अणु
		.flags = cpu_to_le32(PAGING_CMD_IS_SECURED |
				     PAGING_CMD_IS_ENABLED |
				     (fwrt->num_of_pages_in_last_blk <<
				      PAGING_CMD_NUM_OF_PAGES_IN_LAST_GRP_POS)),
		.block_size = cpu_to_le32(BLOCK_2_EXP_SIZE),
		.block_num = cpu_to_le32(fwrt->num_of_paging_blk),
	पूर्ण;
	काष्ठा iwl_host_cmd hcmd = अणु
		.id = iwl_cmd_id(FW_PAGING_BLOCK_CMD, IWL_ALWAYS_LONG_GROUP, 0),
		.len = अणु माप(paging_cmd), पूर्ण,
		.data = अणु &paging_cmd, पूर्ण,
	पूर्ण;
	पूर्णांक blk_idx;

	/* loop क्रम क्रम all paging blocks + CSS block */
	क्रम (blk_idx = 0; blk_idx < fwrt->num_of_paging_blk + 1; blk_idx++) अणु
		dma_addr_t addr = fwrt->fw_paging_db[blk_idx].fw_paging_phys;
		__le32 phy_addr;

		addr = addr >> PAGE_2_EXP_SIZE;
		phy_addr = cpu_to_le32(addr);
		paging_cmd.device_phy_addr[blk_idx] = phy_addr;
	पूर्ण

	वापस iwl_trans_send_cmd(fwrt->trans, &hcmd);
पूर्ण

पूर्णांक iwl_init_paging(काष्ठा iwl_fw_runसमय *fwrt, क्रमागत iwl_ucode_type type)
अणु
	स्थिर काष्ठा fw_img *fw = &fwrt->fw->img[type];
	पूर्णांक ret;

	अगर (fwrt->trans->trans_cfg->gen2)
		वापस 0;

	/*
	 * Configure and operate fw paging mechanism.
	 * The driver configures the paging flow only once.
	 * The CPU2 paging image is included in the IWL_UCODE_INIT image.
	 */
	अगर (!fw->paging_mem_size)
		वापस 0;

	ret = iwl_save_fw_paging(fwrt, fw);
	अगर (ret) अणु
		IWL_ERR(fwrt, "failed to save the FW paging image\n");
		वापस ret;
	पूर्ण

	ret = iwl_send_paging_cmd(fwrt, fw);
	अगर (ret) अणु
		IWL_ERR(fwrt, "failed to send the paging cmd\n");
		iwl_मुक्त_fw_paging(fwrt);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
IWL_EXPORT_SYMBOL(iwl_init_paging);
