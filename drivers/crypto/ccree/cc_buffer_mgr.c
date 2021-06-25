<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (C) 2012-2019 ARM Limited (or its affiliates). */

#समावेश <crypto/पूर्णांकernal/aead.h>
#समावेश <crypto/authenc.h>
#समावेश <crypto/scatterwalk.h>
#समावेश <linux/dmapool.h>
#समावेश <linux/dma-mapping.h>

#समावेश "cc_buffer_mgr.h"
#समावेश "cc_lli_defs.h"
#समावेश "cc_cipher.h"
#समावेश "cc_hash.h"
#समावेश "cc_aead.h"

जोड़ buffer_array_entry अणु
	काष्ठा scatterlist *sgl;
	dma_addr_t buffer_dma;
पूर्ण;

काष्ठा buffer_array अणु
	अचिन्हित पूर्णांक num_of_buffers;
	जोड़ buffer_array_entry entry[MAX_NUM_OF_BUFFERS_IN_MLLI];
	अचिन्हित पूर्णांक offset[MAX_NUM_OF_BUFFERS_IN_MLLI];
	पूर्णांक nents[MAX_NUM_OF_BUFFERS_IN_MLLI];
	पूर्णांक total_data_len[MAX_NUM_OF_BUFFERS_IN_MLLI];
	bool is_last[MAX_NUM_OF_BUFFERS_IN_MLLI];
	u32 *mlli_nents[MAX_NUM_OF_BUFFERS_IN_MLLI];
पूर्ण;

अटल अंतरभूत अक्षर *cc_dma_buf_type(क्रमागत cc_req_dma_buf_type type)
अणु
	चयन (type) अणु
	हाल CC_DMA_BUF_शून्य:
		वापस "BUF_NULL";
	हाल CC_DMA_BUF_DLLI:
		वापस "BUF_DLLI";
	हाल CC_DMA_BUF_MLLI:
		वापस "BUF_MLLI";
	शेष:
		वापस "BUF_INVALID";
	पूर्ण
पूर्ण

/**
 * cc_copy_mac() - Copy MAC to temporary location
 *
 * @dev: device object
 * @req: aead request object
 * @dir: [IN] copy from/to sgl
 */
अटल व्योम cc_copy_mac(काष्ठा device *dev, काष्ठा aead_request *req,
			क्रमागत cc_sg_cpy_direct dir)
अणु
	काष्ठा aead_req_ctx *areq_ctx = aead_request_ctx(req);
	u32 skip = req->assoclen + req->cryptlen;

	cc_copy_sg_portion(dev, areq_ctx->backup_mac, req->src,
			   (skip - areq_ctx->req_authsize), skip, dir);
पूर्ण

/**
 * cc_get_sgl_nents() - Get scatterlist number of entries.
 *
 * @dev: Device object
 * @sg_list: SG list
 * @nbytes: [IN] Total SGL data bytes.
 * @lbytes: [OUT] Returns the amount of bytes at the last entry
 *
 * Return:
 * Number of entries in the scatterlist
 */
अटल अचिन्हित पूर्णांक cc_get_sgl_nents(काष्ठा device *dev,
				     काष्ठा scatterlist *sg_list,
				     अचिन्हित पूर्णांक nbytes, u32 *lbytes)
अणु
	अचिन्हित पूर्णांक nents = 0;

	*lbytes = 0;

	जबतक (nbytes && sg_list) अणु
		nents++;
		/* get the number of bytes in the last entry */
		*lbytes = nbytes;
		nbytes -= (sg_list->length > nbytes) ?
				nbytes : sg_list->length;
		sg_list = sg_next(sg_list);
	पूर्ण

	dev_dbg(dev, "nents %d last bytes %d\n", nents, *lbytes);
	वापस nents;
पूर्ण

/**
 * cc_copy_sg_portion() - Copy scatter list data,
 * from to_skip to end, to dest and vice versa
 *
 * @dev: Device object
 * @dest: Buffer to copy to/from
 * @sg: SG list
 * @to_skip: Number of bytes to skip beक्रमe copying
 * @end: Offset of last byte to copy
 * @direct: Transfer direction (true == from SG list to buffer, false == from
 *          buffer to SG list)
 */
व्योम cc_copy_sg_portion(काष्ठा device *dev, u8 *dest, काष्ठा scatterlist *sg,
			u32 to_skip, u32 end, क्रमागत cc_sg_cpy_direct direct)
अणु
	u32 nents;

	nents = sg_nents_क्रम_len(sg, end);
	sg_copy_buffer(sg, nents, dest, (end - to_skip + 1), to_skip,
		       (direct == CC_SG_TO_BUF));
पूर्ण

अटल पूर्णांक cc_render_buff_to_mlli(काष्ठा device *dev, dma_addr_t buff_dma,
				  u32 buff_size, u32 *curr_nents,
				  u32 **mlli_entry_pp)
अणु
	u32 *mlli_entry_p = *mlli_entry_pp;
	u32 new_nents;

	/* Verअगरy there is no memory overflow*/
	new_nents = (*curr_nents + buff_size / CC_MAX_MLLI_ENTRY_SIZE + 1);
	अगर (new_nents > MAX_NUM_OF_TOTAL_MLLI_ENTRIES) अणु
		dev_err(dev, "Too many mlli entries. current %d max %d\n",
			new_nents, MAX_NUM_OF_TOTAL_MLLI_ENTRIES);
		वापस -ENOMEM;
	पूर्ण

	/*handle buffer दीर्घer than 64 kbytes */
	जबतक (buff_size > CC_MAX_MLLI_ENTRY_SIZE) अणु
		cc_lli_set_addr(mlli_entry_p, buff_dma);
		cc_lli_set_size(mlli_entry_p, CC_MAX_MLLI_ENTRY_SIZE);
		dev_dbg(dev, "entry[%d]: single_buff=0x%08X size=%08X\n",
			*curr_nents, mlli_entry_p[LLI_WORD0_OFFSET],
			mlli_entry_p[LLI_WORD1_OFFSET]);
		buff_dma += CC_MAX_MLLI_ENTRY_SIZE;
		buff_size -= CC_MAX_MLLI_ENTRY_SIZE;
		mlli_entry_p = mlli_entry_p + 2;
		(*curr_nents)++;
	पूर्ण
	/*Last entry */
	cc_lli_set_addr(mlli_entry_p, buff_dma);
	cc_lli_set_size(mlli_entry_p, buff_size);
	dev_dbg(dev, "entry[%d]: single_buff=0x%08X size=%08X\n",
		*curr_nents, mlli_entry_p[LLI_WORD0_OFFSET],
		mlli_entry_p[LLI_WORD1_OFFSET]);
	mlli_entry_p = mlli_entry_p + 2;
	*mlli_entry_pp = mlli_entry_p;
	(*curr_nents)++;
	वापस 0;
पूर्ण

अटल पूर्णांक cc_render_sg_to_mlli(काष्ठा device *dev, काष्ठा scatterlist *sgl,
				u32 sgl_data_len, u32 sgl_offset,
				u32 *curr_nents, u32 **mlli_entry_pp)
अणु
	काष्ठा scatterlist *curr_sgl = sgl;
	u32 *mlli_entry_p = *mlli_entry_pp;
	s32 rc = 0;

	क्रम ( ; (curr_sgl && sgl_data_len);
	      curr_sgl = sg_next(curr_sgl)) अणु
		u32 entry_data_len =
			(sgl_data_len > sg_dma_len(curr_sgl) - sgl_offset) ?
				sg_dma_len(curr_sgl) - sgl_offset :
				sgl_data_len;
		sgl_data_len -= entry_data_len;
		rc = cc_render_buff_to_mlli(dev, sg_dma_address(curr_sgl) +
					    sgl_offset, entry_data_len,
					    curr_nents, &mlli_entry_p);
		अगर (rc)
			वापस rc;

		sgl_offset = 0;
	पूर्ण
	*mlli_entry_pp = mlli_entry_p;
	वापस 0;
पूर्ण

अटल पूर्णांक cc_generate_mlli(काष्ठा device *dev, काष्ठा buffer_array *sg_data,
			    काष्ठा mlli_params *mlli_params, gfp_t flags)
अणु
	u32 *mlli_p;
	u32 total_nents = 0, prev_total_nents = 0;
	पूर्णांक rc = 0, i;

	dev_dbg(dev, "NUM of SG's = %d\n", sg_data->num_of_buffers);

	/* Allocate memory from the poपूर्णांकed pool */
	mlli_params->mlli_virt_addr =
		dma_pool_alloc(mlli_params->curr_pool, flags,
			       &mlli_params->mlli_dma_addr);
	अगर (!mlli_params->mlli_virt_addr) अणु
		dev_err(dev, "dma_pool_alloc() failed\n");
		rc = -ENOMEM;
		जाओ build_mlli_निकास;
	पूर्ण
	/* Poपूर्णांक to start of MLLI */
	mlli_p = mlli_params->mlli_virt_addr;
	/* go over all SG's and link it to one MLLI table */
	क्रम (i = 0; i < sg_data->num_of_buffers; i++) अणु
		जोड़ buffer_array_entry *entry = &sg_data->entry[i];
		u32 tot_len = sg_data->total_data_len[i];
		u32 offset = sg_data->offset[i];

		rc = cc_render_sg_to_mlli(dev, entry->sgl, tot_len, offset,
					  &total_nents, &mlli_p);
		अगर (rc)
			वापस rc;

		/* set last bit in the current table */
		अगर (sg_data->mlli_nents[i]) अणु
			/*Calculate the current MLLI table length क्रम the
			 *length field in the descriptor
			 */
			*sg_data->mlli_nents[i] +=
				(total_nents - prev_total_nents);
			prev_total_nents = total_nents;
		पूर्ण
	पूर्ण

	/* Set MLLI size क्रम the bypass operation */
	mlli_params->mlli_len = (total_nents * LLI_ENTRY_BYTE_SIZE);

	dev_dbg(dev, "MLLI params: virt_addr=%pK dma_addr=%pad mlli_len=0x%X\n",
		mlli_params->mlli_virt_addr, &mlli_params->mlli_dma_addr,
		mlli_params->mlli_len);

build_mlli_निकास:
	वापस rc;
पूर्ण

अटल व्योम cc_add_sg_entry(काष्ठा device *dev, काष्ठा buffer_array *sgl_data,
			    अचिन्हित पूर्णांक nents, काष्ठा scatterlist *sgl,
			    अचिन्हित पूर्णांक data_len, अचिन्हित पूर्णांक data_offset,
			    bool is_last_table, u32 *mlli_nents)
अणु
	अचिन्हित पूर्णांक index = sgl_data->num_of_buffers;

	dev_dbg(dev, "index=%u nents=%u sgl=%pK data_len=0x%08X is_last=%d\n",
		index, nents, sgl, data_len, is_last_table);
	sgl_data->nents[index] = nents;
	sgl_data->entry[index].sgl = sgl;
	sgl_data->offset[index] = data_offset;
	sgl_data->total_data_len[index] = data_len;
	sgl_data->is_last[index] = is_last_table;
	sgl_data->mlli_nents[index] = mlli_nents;
	अगर (sgl_data->mlli_nents[index])
		*sgl_data->mlli_nents[index] = 0;
	sgl_data->num_of_buffers++;
पूर्ण

अटल पूर्णांक cc_map_sg(काष्ठा device *dev, काष्ठा scatterlist *sg,
		     अचिन्हित पूर्णांक nbytes, पूर्णांक direction, u32 *nents,
		     u32 max_sg_nents, u32 *lbytes, u32 *mapped_nents)
अणु
	पूर्णांक ret = 0;

	*nents = cc_get_sgl_nents(dev, sg, nbytes, lbytes);
	अगर (*nents > max_sg_nents) अणु
		*nents = 0;
		dev_err(dev, "Too many fragments. current %d max %d\n",
			*nents, max_sg_nents);
		वापस -ENOMEM;
	पूर्ण

	ret = dma_map_sg(dev, sg, *nents, direction);
	अगर (dma_mapping_error(dev, ret)) अणु
		*nents = 0;
		dev_err(dev, "dma_map_sg() sg buffer failed %d\n", ret);
		वापस -ENOMEM;
	पूर्ण

	*mapped_nents = ret;

	वापस 0;
पूर्ण

अटल पूर्णांक
cc_set_aead_conf_buf(काष्ठा device *dev, काष्ठा aead_req_ctx *areq_ctx,
		     u8 *config_data, काष्ठा buffer_array *sg_data,
		     अचिन्हित पूर्णांक assoclen)
अणु
	dev_dbg(dev, " handle additional data config set to DLLI\n");
	/* create sg क्रम the current buffer */
	sg_init_one(&areq_ctx->ccm_adata_sg, config_data,
		    AES_BLOCK_SIZE + areq_ctx->ccm_hdr_size);
	अगर (dma_map_sg(dev, &areq_ctx->ccm_adata_sg, 1, DMA_TO_DEVICE) != 1) अणु
		dev_err(dev, "dma_map_sg() config buffer failed\n");
		वापस -ENOMEM;
	पूर्ण
	dev_dbg(dev, "Mapped curr_buff: dma_address=%pad page=%p addr=%pK offset=%u length=%u\n",
		&sg_dma_address(&areq_ctx->ccm_adata_sg),
		sg_page(&areq_ctx->ccm_adata_sg),
		sg_virt(&areq_ctx->ccm_adata_sg),
		areq_ctx->ccm_adata_sg.offset, areq_ctx->ccm_adata_sg.length);
	/* prepare क्रम हाल of MLLI */
	अगर (assoclen > 0) अणु
		cc_add_sg_entry(dev, sg_data, 1, &areq_ctx->ccm_adata_sg,
				(AES_BLOCK_SIZE + areq_ctx->ccm_hdr_size),
				0, false, शून्य);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cc_set_hash_buf(काष्ठा device *dev, काष्ठा ahash_req_ctx *areq_ctx,
			   u8 *curr_buff, u32 curr_buff_cnt,
			   काष्ठा buffer_array *sg_data)
अणु
	dev_dbg(dev, " handle curr buff %x set to   DLLI\n", curr_buff_cnt);
	/* create sg क्रम the current buffer */
	sg_init_one(areq_ctx->buff_sg, curr_buff, curr_buff_cnt);
	अगर (dma_map_sg(dev, areq_ctx->buff_sg, 1, DMA_TO_DEVICE) != 1) अणु
		dev_err(dev, "dma_map_sg() src buffer failed\n");
		वापस -ENOMEM;
	पूर्ण
	dev_dbg(dev, "Mapped curr_buff: dma_address=%pad page=%p addr=%pK offset=%u length=%u\n",
		&sg_dma_address(areq_ctx->buff_sg), sg_page(areq_ctx->buff_sg),
		sg_virt(areq_ctx->buff_sg), areq_ctx->buff_sg->offset,
		areq_ctx->buff_sg->length);
	areq_ctx->data_dma_buf_type = CC_DMA_BUF_DLLI;
	areq_ctx->curr_sg = areq_ctx->buff_sg;
	areq_ctx->in_nents = 0;
	/* prepare क्रम हाल of MLLI */
	cc_add_sg_entry(dev, sg_data, 1, areq_ctx->buff_sg, curr_buff_cnt, 0,
			false, शून्य);
	वापस 0;
पूर्ण

व्योम cc_unmap_cipher_request(काष्ठा device *dev, व्योम *ctx,
				अचिन्हित पूर्णांक ivsize, काष्ठा scatterlist *src,
				काष्ठा scatterlist *dst)
अणु
	काष्ठा cipher_req_ctx *req_ctx = (काष्ठा cipher_req_ctx *)ctx;

	अगर (req_ctx->gen_ctx.iv_dma_addr) अणु
		dev_dbg(dev, "Unmapped iv: iv_dma_addr=%pad iv_size=%u\n",
			&req_ctx->gen_ctx.iv_dma_addr, ivsize);
		dma_unmap_single(dev, req_ctx->gen_ctx.iv_dma_addr,
				 ivsize, DMA_BIसूचीECTIONAL);
	पूर्ण
	/* Release pool */
	अगर (req_ctx->dma_buf_type == CC_DMA_BUF_MLLI &&
	    req_ctx->mlli_params.mlli_virt_addr) अणु
		dma_pool_मुक्त(req_ctx->mlli_params.curr_pool,
			      req_ctx->mlli_params.mlli_virt_addr,
			      req_ctx->mlli_params.mlli_dma_addr);
	पूर्ण

	dma_unmap_sg(dev, src, req_ctx->in_nents, DMA_BIसूचीECTIONAL);
	dev_dbg(dev, "Unmapped req->src=%pK\n", sg_virt(src));

	अगर (src != dst) अणु
		dma_unmap_sg(dev, dst, req_ctx->out_nents, DMA_BIसूचीECTIONAL);
		dev_dbg(dev, "Unmapped req->dst=%pK\n", sg_virt(dst));
	पूर्ण
पूर्ण

पूर्णांक cc_map_cipher_request(काष्ठा cc_drvdata *drvdata, व्योम *ctx,
			  अचिन्हित पूर्णांक ivsize, अचिन्हित पूर्णांक nbytes,
			  व्योम *info, काष्ठा scatterlist *src,
			  काष्ठा scatterlist *dst, gfp_t flags)
अणु
	काष्ठा cipher_req_ctx *req_ctx = (काष्ठा cipher_req_ctx *)ctx;
	काष्ठा mlli_params *mlli_params = &req_ctx->mlli_params;
	काष्ठा device *dev = drvdata_to_dev(drvdata);
	काष्ठा buffer_array sg_data;
	u32 dummy = 0;
	पूर्णांक rc = 0;
	u32 mapped_nents = 0;

	req_ctx->dma_buf_type = CC_DMA_BUF_DLLI;
	mlli_params->curr_pool = शून्य;
	sg_data.num_of_buffers = 0;

	/* Map IV buffer */
	अगर (ivsize) अणु
		dump_byte_array("iv", info, ivsize);
		req_ctx->gen_ctx.iv_dma_addr =
			dma_map_single(dev, info, ivsize, DMA_BIसूचीECTIONAL);
		अगर (dma_mapping_error(dev, req_ctx->gen_ctx.iv_dma_addr)) अणु
			dev_err(dev, "Mapping iv %u B at va=%pK for DMA failed\n",
				ivsize, info);
			वापस -ENOMEM;
		पूर्ण
		dev_dbg(dev, "Mapped iv %u B at va=%pK to dma=%pad\n",
			ivsize, info, &req_ctx->gen_ctx.iv_dma_addr);
	पूर्ण अन्यथा अणु
		req_ctx->gen_ctx.iv_dma_addr = 0;
	पूर्ण

	/* Map the src SGL */
	rc = cc_map_sg(dev, src, nbytes, DMA_BIसूचीECTIONAL, &req_ctx->in_nents,
		       LLI_MAX_NUM_OF_DATA_ENTRIES, &dummy, &mapped_nents);
	अगर (rc)
		जाओ cipher_निकास;
	अगर (mapped_nents > 1)
		req_ctx->dma_buf_type = CC_DMA_BUF_MLLI;

	अगर (src == dst) अणु
		/* Handle inplace operation */
		अगर (req_ctx->dma_buf_type == CC_DMA_BUF_MLLI) अणु
			req_ctx->out_nents = 0;
			cc_add_sg_entry(dev, &sg_data, req_ctx->in_nents, src,
					nbytes, 0, true,
					&req_ctx->in_mlli_nents);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Map the dst sg */
		rc = cc_map_sg(dev, dst, nbytes, DMA_BIसूचीECTIONAL,
			       &req_ctx->out_nents, LLI_MAX_NUM_OF_DATA_ENTRIES,
			       &dummy, &mapped_nents);
		अगर (rc)
			जाओ cipher_निकास;
		अगर (mapped_nents > 1)
			req_ctx->dma_buf_type = CC_DMA_BUF_MLLI;

		अगर (req_ctx->dma_buf_type == CC_DMA_BUF_MLLI) अणु
			cc_add_sg_entry(dev, &sg_data, req_ctx->in_nents, src,
					nbytes, 0, true,
					&req_ctx->in_mlli_nents);
			cc_add_sg_entry(dev, &sg_data, req_ctx->out_nents, dst,
					nbytes, 0, true,
					&req_ctx->out_mlli_nents);
		पूर्ण
	पूर्ण

	अगर (req_ctx->dma_buf_type == CC_DMA_BUF_MLLI) अणु
		mlli_params->curr_pool = drvdata->mlli_buffs_pool;
		rc = cc_generate_mlli(dev, &sg_data, mlli_params, flags);
		अगर (rc)
			जाओ cipher_निकास;
	पूर्ण

	dev_dbg(dev, "areq_ctx->dma_buf_type = %s\n",
		cc_dma_buf_type(req_ctx->dma_buf_type));

	वापस 0;

cipher_निकास:
	cc_unmap_cipher_request(dev, req_ctx, ivsize, src, dst);
	वापस rc;
पूर्ण

व्योम cc_unmap_aead_request(काष्ठा device *dev, काष्ठा aead_request *req)
अणु
	काष्ठा aead_req_ctx *areq_ctx = aead_request_ctx(req);
	अचिन्हित पूर्णांक hw_iv_size = areq_ctx->hw_iv_size;
	काष्ठा cc_drvdata *drvdata = dev_get_drvdata(dev);

	अगर (areq_ctx->mac_buf_dma_addr) अणु
		dma_unmap_single(dev, areq_ctx->mac_buf_dma_addr,
				 MAX_MAC_SIZE, DMA_BIसूचीECTIONAL);
	पूर्ण

	अगर (areq_ctx->cipher_mode == DRV_CIPHER_GCTR) अणु
		अगर (areq_ctx->hkey_dma_addr) अणु
			dma_unmap_single(dev, areq_ctx->hkey_dma_addr,
					 AES_BLOCK_SIZE, DMA_BIसूचीECTIONAL);
		पूर्ण

		अगर (areq_ctx->gcm_block_len_dma_addr) अणु
			dma_unmap_single(dev, areq_ctx->gcm_block_len_dma_addr,
					 AES_BLOCK_SIZE, DMA_TO_DEVICE);
		पूर्ण

		अगर (areq_ctx->gcm_iv_inc1_dma_addr) अणु
			dma_unmap_single(dev, areq_ctx->gcm_iv_inc1_dma_addr,
					 AES_BLOCK_SIZE, DMA_TO_DEVICE);
		पूर्ण

		अगर (areq_ctx->gcm_iv_inc2_dma_addr) अणु
			dma_unmap_single(dev, areq_ctx->gcm_iv_inc2_dma_addr,
					 AES_BLOCK_SIZE, DMA_TO_DEVICE);
		पूर्ण
	पूर्ण

	अगर (areq_ctx->ccm_hdr_size != ccm_header_size_null) अणु
		अगर (areq_ctx->ccm_iv0_dma_addr) अणु
			dma_unmap_single(dev, areq_ctx->ccm_iv0_dma_addr,
					 AES_BLOCK_SIZE, DMA_TO_DEVICE);
		पूर्ण

		dma_unmap_sg(dev, &areq_ctx->ccm_adata_sg, 1, DMA_TO_DEVICE);
	पूर्ण
	अगर (areq_ctx->gen_ctx.iv_dma_addr) अणु
		dma_unmap_single(dev, areq_ctx->gen_ctx.iv_dma_addr,
				 hw_iv_size, DMA_BIसूचीECTIONAL);
		kमुक्त_sensitive(areq_ctx->gen_ctx.iv);
	पूर्ण

	/* Release pool */
	अगर ((areq_ctx->assoc_buff_type == CC_DMA_BUF_MLLI ||
	     areq_ctx->data_buff_type == CC_DMA_BUF_MLLI) &&
	    (areq_ctx->mlli_params.mlli_virt_addr)) अणु
		dev_dbg(dev, "free MLLI buffer: dma=%pad virt=%pK\n",
			&areq_ctx->mlli_params.mlli_dma_addr,
			areq_ctx->mlli_params.mlli_virt_addr);
		dma_pool_मुक्त(areq_ctx->mlli_params.curr_pool,
			      areq_ctx->mlli_params.mlli_virt_addr,
			      areq_ctx->mlli_params.mlli_dma_addr);
	पूर्ण

	dev_dbg(dev, "Unmapping src sgl: req->src=%pK areq_ctx->src.nents=%u areq_ctx->assoc.nents=%u assoclen:%u cryptlen=%u\n",
		sg_virt(req->src), areq_ctx->src.nents, areq_ctx->assoc.nents,
		areq_ctx->assoclen, req->cryptlen);

	dma_unmap_sg(dev, req->src, areq_ctx->src.mapped_nents,
		     DMA_BIसूचीECTIONAL);
	अगर (req->src != req->dst) अणु
		dev_dbg(dev, "Unmapping dst sgl: req->dst=%pK\n",
			sg_virt(req->dst));
		dma_unmap_sg(dev, req->dst, areq_ctx->dst.mapped_nents,
			     DMA_BIसूचीECTIONAL);
	पूर्ण
	अगर (drvdata->coherent &&
	    areq_ctx->gen_ctx.op_type == DRV_CRYPTO_सूचीECTION_DECRYPT &&
	    req->src == req->dst) अणु
		/* copy back mac from temporary location to deal with possible
		 * data memory overriding that caused by cache coherence
		 * problem.
		 */
		cc_copy_mac(dev, req, CC_SG_FROM_BUF);
	पूर्ण
पूर्ण

अटल bool cc_is_icv_frag(अचिन्हित पूर्णांक sgl_nents, अचिन्हित पूर्णांक authsize,
			   u32 last_entry_data_size)
अणु
	वापस ((sgl_nents > 1) && (last_entry_data_size < authsize));
पूर्ण

अटल पूर्णांक cc_aead_chain_iv(काष्ठा cc_drvdata *drvdata,
			    काष्ठा aead_request *req,
			    काष्ठा buffer_array *sg_data,
			    bool is_last, bool करो_chain)
अणु
	काष्ठा aead_req_ctx *areq_ctx = aead_request_ctx(req);
	अचिन्हित पूर्णांक hw_iv_size = areq_ctx->hw_iv_size;
	काष्ठा device *dev = drvdata_to_dev(drvdata);
	gfp_t flags = cc_gfp_flags(&req->base);
	पूर्णांक rc = 0;

	अगर (!req->iv) अणु
		areq_ctx->gen_ctx.iv_dma_addr = 0;
		areq_ctx->gen_ctx.iv = शून्य;
		जाओ chain_iv_निकास;
	पूर्ण

	areq_ctx->gen_ctx.iv = kmemdup(req->iv, hw_iv_size, flags);
	अगर (!areq_ctx->gen_ctx.iv)
		वापस -ENOMEM;

	areq_ctx->gen_ctx.iv_dma_addr =
		dma_map_single(dev, areq_ctx->gen_ctx.iv, hw_iv_size,
			       DMA_BIसूचीECTIONAL);
	अगर (dma_mapping_error(dev, areq_ctx->gen_ctx.iv_dma_addr)) अणु
		dev_err(dev, "Mapping iv %u B at va=%pK for DMA failed\n",
			hw_iv_size, req->iv);
		kमुक्त_sensitive(areq_ctx->gen_ctx.iv);
		areq_ctx->gen_ctx.iv = शून्य;
		rc = -ENOMEM;
		जाओ chain_iv_निकास;
	पूर्ण

	dev_dbg(dev, "Mapped iv %u B at va=%pK to dma=%pad\n",
		hw_iv_size, req->iv, &areq_ctx->gen_ctx.iv_dma_addr);

chain_iv_निकास:
	वापस rc;
पूर्ण

अटल पूर्णांक cc_aead_chain_assoc(काष्ठा cc_drvdata *drvdata,
			       काष्ठा aead_request *req,
			       काष्ठा buffer_array *sg_data,
			       bool is_last, bool करो_chain)
अणु
	काष्ठा aead_req_ctx *areq_ctx = aead_request_ctx(req);
	पूर्णांक rc = 0;
	पूर्णांक mapped_nents = 0;
	काष्ठा device *dev = drvdata_to_dev(drvdata);

	अगर (!sg_data) अणु
		rc = -EINVAL;
		जाओ chain_assoc_निकास;
	पूर्ण

	अगर (areq_ctx->assoclen == 0) अणु
		areq_ctx->assoc_buff_type = CC_DMA_BUF_शून्य;
		areq_ctx->assoc.nents = 0;
		areq_ctx->assoc.mlli_nents = 0;
		dev_dbg(dev, "Chain assoc of length 0: buff_type=%s nents=%u\n",
			cc_dma_buf_type(areq_ctx->assoc_buff_type),
			areq_ctx->assoc.nents);
		जाओ chain_assoc_निकास;
	पूर्ण

	mapped_nents = sg_nents_क्रम_len(req->src, areq_ctx->assoclen);
	अगर (mapped_nents < 0)
		वापस mapped_nents;

	अगर (mapped_nents > LLI_MAX_NUM_OF_ASSOC_DATA_ENTRIES) अणु
		dev_err(dev, "Too many fragments. current %d max %d\n",
			mapped_nents, LLI_MAX_NUM_OF_ASSOC_DATA_ENTRIES);
		वापस -ENOMEM;
	पूर्ण
	areq_ctx->assoc.nents = mapped_nents;

	/* in CCM हाल we have additional entry क्रम
	 * ccm header configurations
	 */
	अगर (areq_ctx->ccm_hdr_size != ccm_header_size_null) अणु
		अगर ((mapped_nents + 1) > LLI_MAX_NUM_OF_ASSOC_DATA_ENTRIES) अणु
			dev_err(dev, "CCM case.Too many fragments. Current %d max %d\n",
				(areq_ctx->assoc.nents + 1),
				LLI_MAX_NUM_OF_ASSOC_DATA_ENTRIES);
			rc = -ENOMEM;
			जाओ chain_assoc_निकास;
		पूर्ण
	पूर्ण

	अगर (mapped_nents == 1 && areq_ctx->ccm_hdr_size == ccm_header_size_null)
		areq_ctx->assoc_buff_type = CC_DMA_BUF_DLLI;
	अन्यथा
		areq_ctx->assoc_buff_type = CC_DMA_BUF_MLLI;

	अगर (करो_chain || areq_ctx->assoc_buff_type == CC_DMA_BUF_MLLI) अणु
		dev_dbg(dev, "Chain assoc: buff_type=%s nents=%u\n",
			cc_dma_buf_type(areq_ctx->assoc_buff_type),
			areq_ctx->assoc.nents);
		cc_add_sg_entry(dev, sg_data, areq_ctx->assoc.nents, req->src,
				areq_ctx->assoclen, 0, is_last,
				&areq_ctx->assoc.mlli_nents);
		areq_ctx->assoc_buff_type = CC_DMA_BUF_MLLI;
	पूर्ण

chain_assoc_निकास:
	वापस rc;
पूर्ण

अटल व्योम cc_prepare_aead_data_dlli(काष्ठा aead_request *req,
				      u32 *src_last_bytes, u32 *dst_last_bytes)
अणु
	काष्ठा aead_req_ctx *areq_ctx = aead_request_ctx(req);
	क्रमागत drv_crypto_direction direct = areq_ctx->gen_ctx.op_type;
	अचिन्हित पूर्णांक authsize = areq_ctx->req_authsize;
	काष्ठा scatterlist *sg;
	sमाप_प्रकार offset;

	areq_ctx->is_icv_fragmented = false;

	अगर ((req->src == req->dst) || direct == DRV_CRYPTO_सूचीECTION_DECRYPT) अणु
		sg = areq_ctx->src_sgl;
		offset = *src_last_bytes - authsize;
	पूर्ण अन्यथा अणु
		sg = areq_ctx->dst_sgl;
		offset = *dst_last_bytes - authsize;
	पूर्ण

	areq_ctx->icv_dma_addr = sg_dma_address(sg) + offset;
	areq_ctx->icv_virt_addr = sg_virt(sg) + offset;
पूर्ण

अटल व्योम cc_prepare_aead_data_mlli(काष्ठा cc_drvdata *drvdata,
				      काष्ठा aead_request *req,
				      काष्ठा buffer_array *sg_data,
				      u32 *src_last_bytes, u32 *dst_last_bytes,
				      bool is_last_table)
अणु
	काष्ठा aead_req_ctx *areq_ctx = aead_request_ctx(req);
	क्रमागत drv_crypto_direction direct = areq_ctx->gen_ctx.op_type;
	अचिन्हित पूर्णांक authsize = areq_ctx->req_authsize;
	काष्ठा device *dev = drvdata_to_dev(drvdata);
	काष्ठा scatterlist *sg;

	अगर (req->src == req->dst) अणु
		/*INPLACE*/
		cc_add_sg_entry(dev, sg_data, areq_ctx->src.nents,
				areq_ctx->src_sgl, areq_ctx->cryptlen,
				areq_ctx->src_offset, is_last_table,
				&areq_ctx->src.mlli_nents);

		areq_ctx->is_icv_fragmented =
			cc_is_icv_frag(areq_ctx->src.nents, authsize,
				       *src_last_bytes);

		अगर (areq_ctx->is_icv_fragmented) अणु
			/* Backup happens only when ICV is fragmented, ICV
			 * verअगरication is made by CPU compare in order to
			 * simplअगरy MAC verअगरication upon request completion
			 */
			अगर (direct == DRV_CRYPTO_सूचीECTION_DECRYPT) अणु
				/* In coherent platक्रमms (e.g. ACP)
				 * alपढ़ोy copying ICV क्रम any
				 * INPLACE-DECRYPT operation, hence
				 * we must neglect this code.
				 */
				अगर (!drvdata->coherent)
					cc_copy_mac(dev, req, CC_SG_TO_BUF);

				areq_ctx->icv_virt_addr = areq_ctx->backup_mac;
			पूर्ण अन्यथा अणु
				areq_ctx->icv_virt_addr = areq_ctx->mac_buf;
				areq_ctx->icv_dma_addr =
					areq_ctx->mac_buf_dma_addr;
			पूर्ण
		पूर्ण अन्यथा अणु /* Contig. ICV */
			sg = &areq_ctx->src_sgl[areq_ctx->src.nents - 1];
			/*Should hanlde अगर the sg is not contig.*/
			areq_ctx->icv_dma_addr = sg_dma_address(sg) +
				(*src_last_bytes - authsize);
			areq_ctx->icv_virt_addr = sg_virt(sg) +
				(*src_last_bytes - authsize);
		पूर्ण

	पूर्ण अन्यथा अगर (direct == DRV_CRYPTO_सूचीECTION_DECRYPT) अणु
		/*NON-INPLACE and DECRYPT*/
		cc_add_sg_entry(dev, sg_data, areq_ctx->src.nents,
				areq_ctx->src_sgl, areq_ctx->cryptlen,
				areq_ctx->src_offset, is_last_table,
				&areq_ctx->src.mlli_nents);
		cc_add_sg_entry(dev, sg_data, areq_ctx->dst.nents,
				areq_ctx->dst_sgl, areq_ctx->cryptlen,
				areq_ctx->dst_offset, is_last_table,
				&areq_ctx->dst.mlli_nents);

		areq_ctx->is_icv_fragmented =
			cc_is_icv_frag(areq_ctx->src.nents, authsize,
				       *src_last_bytes);
		/* Backup happens only when ICV is fragmented, ICV

		 * verअगरication is made by CPU compare in order to simplअगरy
		 * MAC verअगरication upon request completion
		 */
		अगर (areq_ctx->is_icv_fragmented) अणु
			cc_copy_mac(dev, req, CC_SG_TO_BUF);
			areq_ctx->icv_virt_addr = areq_ctx->backup_mac;

		पूर्ण अन्यथा अणु /* Contig. ICV */
			sg = &areq_ctx->src_sgl[areq_ctx->src.nents - 1];
			/*Should hanlde अगर the sg is not contig.*/
			areq_ctx->icv_dma_addr = sg_dma_address(sg) +
				(*src_last_bytes - authsize);
			areq_ctx->icv_virt_addr = sg_virt(sg) +
				(*src_last_bytes - authsize);
		पूर्ण

	पूर्ण अन्यथा अणु
		/*NON-INPLACE and ENCRYPT*/
		cc_add_sg_entry(dev, sg_data, areq_ctx->dst.nents,
				areq_ctx->dst_sgl, areq_ctx->cryptlen,
				areq_ctx->dst_offset, is_last_table,
				&areq_ctx->dst.mlli_nents);
		cc_add_sg_entry(dev, sg_data, areq_ctx->src.nents,
				areq_ctx->src_sgl, areq_ctx->cryptlen,
				areq_ctx->src_offset, is_last_table,
				&areq_ctx->src.mlli_nents);

		areq_ctx->is_icv_fragmented =
			cc_is_icv_frag(areq_ctx->dst.nents, authsize,
				       *dst_last_bytes);

		अगर (!areq_ctx->is_icv_fragmented) अणु
			sg = &areq_ctx->dst_sgl[areq_ctx->dst.nents - 1];
			/* Contig. ICV */
			areq_ctx->icv_dma_addr = sg_dma_address(sg) +
				(*dst_last_bytes - authsize);
			areq_ctx->icv_virt_addr = sg_virt(sg) +
				(*dst_last_bytes - authsize);
		पूर्ण अन्यथा अणु
			areq_ctx->icv_dma_addr = areq_ctx->mac_buf_dma_addr;
			areq_ctx->icv_virt_addr = areq_ctx->mac_buf;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक cc_aead_chain_data(काष्ठा cc_drvdata *drvdata,
			      काष्ठा aead_request *req,
			      काष्ठा buffer_array *sg_data,
			      bool is_last_table, bool करो_chain)
अणु
	काष्ठा aead_req_ctx *areq_ctx = aead_request_ctx(req);
	काष्ठा device *dev = drvdata_to_dev(drvdata);
	क्रमागत drv_crypto_direction direct = areq_ctx->gen_ctx.op_type;
	अचिन्हित पूर्णांक authsize = areq_ctx->req_authsize;
	अचिन्हित पूर्णांक src_last_bytes = 0, dst_last_bytes = 0;
	पूर्णांक rc = 0;
	u32 src_mapped_nents = 0, dst_mapped_nents = 0;
	u32 offset = 0;
	/* non-inplace mode */
	अचिन्हित पूर्णांक size_क्रम_map = req->assoclen + req->cryptlen;
	u32 sg_index = 0;
	u32 माप_प्रकारo_skip = req->assoclen;
	काष्ठा scatterlist *sgl;

	offset = माप_प्रकारo_skip;

	अगर (!sg_data)
		वापस -EINVAL;

	areq_ctx->src_sgl = req->src;
	areq_ctx->dst_sgl = req->dst;

	size_क्रम_map += (direct == DRV_CRYPTO_सूचीECTION_ENCRYPT) ?
			authsize : 0;
	src_mapped_nents = cc_get_sgl_nents(dev, req->src, size_क्रम_map,
					    &src_last_bytes);
	sg_index = areq_ctx->src_sgl->length;
	//check where the data starts
	जबतक (src_mapped_nents && (sg_index <= माप_प्रकारo_skip)) अणु
		src_mapped_nents--;
		offset -= areq_ctx->src_sgl->length;
		sgl = sg_next(areq_ctx->src_sgl);
		अगर (!sgl)
			अवरोध;
		areq_ctx->src_sgl = sgl;
		sg_index += areq_ctx->src_sgl->length;
	पूर्ण
	अगर (src_mapped_nents > LLI_MAX_NUM_OF_DATA_ENTRIES) अणु
		dev_err(dev, "Too many fragments. current %d max %d\n",
			src_mapped_nents, LLI_MAX_NUM_OF_DATA_ENTRIES);
		वापस -ENOMEM;
	पूर्ण

	areq_ctx->src.nents = src_mapped_nents;

	areq_ctx->src_offset = offset;

	अगर (req->src != req->dst) अणु
		size_क्रम_map = req->assoclen + req->cryptlen;

		अगर (direct == DRV_CRYPTO_सूचीECTION_ENCRYPT)
			size_क्रम_map += authsize;
		अन्यथा
			size_क्रम_map -= authsize;

		rc = cc_map_sg(dev, req->dst, size_क्रम_map, DMA_BIसूचीECTIONAL,
			       &areq_ctx->dst.mapped_nents,
			       LLI_MAX_NUM_OF_DATA_ENTRIES, &dst_last_bytes,
			       &dst_mapped_nents);
		अगर (rc)
			जाओ chain_data_निकास;
	पूर्ण

	dst_mapped_nents = cc_get_sgl_nents(dev, req->dst, size_क्रम_map,
					    &dst_last_bytes);
	sg_index = areq_ctx->dst_sgl->length;
	offset = माप_प्रकारo_skip;

	//check where the data starts
	जबतक (dst_mapped_nents && sg_index <= माप_प्रकारo_skip) अणु
		dst_mapped_nents--;
		offset -= areq_ctx->dst_sgl->length;
		sgl = sg_next(areq_ctx->dst_sgl);
		अगर (!sgl)
			अवरोध;
		areq_ctx->dst_sgl = sgl;
		sg_index += areq_ctx->dst_sgl->length;
	पूर्ण
	अगर (dst_mapped_nents > LLI_MAX_NUM_OF_DATA_ENTRIES) अणु
		dev_err(dev, "Too many fragments. current %d max %d\n",
			dst_mapped_nents, LLI_MAX_NUM_OF_DATA_ENTRIES);
		वापस -ENOMEM;
	पूर्ण
	areq_ctx->dst.nents = dst_mapped_nents;
	areq_ctx->dst_offset = offset;
	अगर (src_mapped_nents > 1 ||
	    dst_mapped_nents  > 1 ||
	    करो_chain) अणु
		areq_ctx->data_buff_type = CC_DMA_BUF_MLLI;
		cc_prepare_aead_data_mlli(drvdata, req, sg_data,
					  &src_last_bytes, &dst_last_bytes,
					  is_last_table);
	पूर्ण अन्यथा अणु
		areq_ctx->data_buff_type = CC_DMA_BUF_DLLI;
		cc_prepare_aead_data_dlli(req, &src_last_bytes,
					  &dst_last_bytes);
	पूर्ण

chain_data_निकास:
	वापस rc;
पूर्ण

अटल व्योम cc_update_aead_mlli_nents(काष्ठा cc_drvdata *drvdata,
				      काष्ठा aead_request *req)
अणु
	काष्ठा aead_req_ctx *areq_ctx = aead_request_ctx(req);
	u32 curr_mlli_size = 0;

	अगर (areq_ctx->assoc_buff_type == CC_DMA_BUF_MLLI) अणु
		areq_ctx->assoc.sram_addr = drvdata->mlli_sram_addr;
		curr_mlli_size = areq_ctx->assoc.mlli_nents *
						LLI_ENTRY_BYTE_SIZE;
	पूर्ण

	अगर (areq_ctx->data_buff_type == CC_DMA_BUF_MLLI) अणु
		/*Inplace हाल dst nents equal to src nents*/
		अगर (req->src == req->dst) अणु
			areq_ctx->dst.mlli_nents = areq_ctx->src.mlli_nents;
			areq_ctx->src.sram_addr = drvdata->mlli_sram_addr +
								curr_mlli_size;
			areq_ctx->dst.sram_addr = areq_ctx->src.sram_addr;
			अगर (!areq_ctx->is_single_pass)
				areq_ctx->assoc.mlli_nents +=
					areq_ctx->src.mlli_nents;
		पूर्ण अन्यथा अणु
			अगर (areq_ctx->gen_ctx.op_type ==
					DRV_CRYPTO_सूचीECTION_DECRYPT) अणु
				areq_ctx->src.sram_addr =
						drvdata->mlli_sram_addr +
								curr_mlli_size;
				areq_ctx->dst.sram_addr =
						areq_ctx->src.sram_addr +
						areq_ctx->src.mlli_nents *
						LLI_ENTRY_BYTE_SIZE;
				अगर (!areq_ctx->is_single_pass)
					areq_ctx->assoc.mlli_nents +=
						areq_ctx->src.mlli_nents;
			पूर्ण अन्यथा अणु
				areq_ctx->dst.sram_addr =
						drvdata->mlli_sram_addr +
								curr_mlli_size;
				areq_ctx->src.sram_addr =
						areq_ctx->dst.sram_addr +
						areq_ctx->dst.mlli_nents *
						LLI_ENTRY_BYTE_SIZE;
				अगर (!areq_ctx->is_single_pass)
					areq_ctx->assoc.mlli_nents +=
						areq_ctx->dst.mlli_nents;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक cc_map_aead_request(काष्ठा cc_drvdata *drvdata, काष्ठा aead_request *req)
अणु
	काष्ठा aead_req_ctx *areq_ctx = aead_request_ctx(req);
	काष्ठा mlli_params *mlli_params = &areq_ctx->mlli_params;
	काष्ठा device *dev = drvdata_to_dev(drvdata);
	काष्ठा buffer_array sg_data;
	अचिन्हित पूर्णांक authsize = areq_ctx->req_authsize;
	पूर्णांक rc = 0;
	dma_addr_t dma_addr;
	u32 mapped_nents = 0;
	u32 dummy = 0; /*used क्रम the assoc data fragments */
	u32 माप_प्रकारo_map;
	gfp_t flags = cc_gfp_flags(&req->base);

	mlli_params->curr_pool = शून्य;
	sg_data.num_of_buffers = 0;

	/* copy mac to a temporary location to deal with possible
	 * data memory overriding that caused by cache coherence problem.
	 */
	अगर (drvdata->coherent &&
	    areq_ctx->gen_ctx.op_type == DRV_CRYPTO_सूचीECTION_DECRYPT &&
	    req->src == req->dst)
		cc_copy_mac(dev, req, CC_SG_TO_BUF);

	/* cacluate the size क्रम cipher हटाओ ICV in decrypt*/
	areq_ctx->cryptlen = (areq_ctx->gen_ctx.op_type ==
				 DRV_CRYPTO_सूचीECTION_ENCRYPT) ?
				req->cryptlen :
				(req->cryptlen - authsize);

	dma_addr = dma_map_single(dev, areq_ctx->mac_buf, MAX_MAC_SIZE,
				  DMA_BIसूचीECTIONAL);
	अगर (dma_mapping_error(dev, dma_addr)) अणु
		dev_err(dev, "Mapping mac_buf %u B at va=%pK for DMA failed\n",
			MAX_MAC_SIZE, areq_ctx->mac_buf);
		rc = -ENOMEM;
		जाओ aead_map_failure;
	पूर्ण
	areq_ctx->mac_buf_dma_addr = dma_addr;

	अगर (areq_ctx->ccm_hdr_size != ccm_header_size_null) अणु
		व्योम *addr = areq_ctx->ccm_config + CCM_CTR_COUNT_0_OFFSET;

		dma_addr = dma_map_single(dev, addr, AES_BLOCK_SIZE,
					  DMA_TO_DEVICE);

		अगर (dma_mapping_error(dev, dma_addr)) अणु
			dev_err(dev, "Mapping mac_buf %u B at va=%pK for DMA failed\n",
				AES_BLOCK_SIZE, addr);
			areq_ctx->ccm_iv0_dma_addr = 0;
			rc = -ENOMEM;
			जाओ aead_map_failure;
		पूर्ण
		areq_ctx->ccm_iv0_dma_addr = dma_addr;

		rc = cc_set_aead_conf_buf(dev, areq_ctx, areq_ctx->ccm_config,
					  &sg_data, areq_ctx->assoclen);
		अगर (rc)
			जाओ aead_map_failure;
	पूर्ण

	अगर (areq_ctx->cipher_mode == DRV_CIPHER_GCTR) अणु
		dma_addr = dma_map_single(dev, areq_ctx->hkey, AES_BLOCK_SIZE,
					  DMA_BIसूचीECTIONAL);
		अगर (dma_mapping_error(dev, dma_addr)) अणु
			dev_err(dev, "Mapping hkey %u B at va=%pK for DMA failed\n",
				AES_BLOCK_SIZE, areq_ctx->hkey);
			rc = -ENOMEM;
			जाओ aead_map_failure;
		पूर्ण
		areq_ctx->hkey_dma_addr = dma_addr;

		dma_addr = dma_map_single(dev, &areq_ctx->gcm_len_block,
					  AES_BLOCK_SIZE, DMA_TO_DEVICE);
		अगर (dma_mapping_error(dev, dma_addr)) अणु
			dev_err(dev, "Mapping gcm_len_block %u B at va=%pK for DMA failed\n",
				AES_BLOCK_SIZE, &areq_ctx->gcm_len_block);
			rc = -ENOMEM;
			जाओ aead_map_failure;
		पूर्ण
		areq_ctx->gcm_block_len_dma_addr = dma_addr;

		dma_addr = dma_map_single(dev, areq_ctx->gcm_iv_inc1,
					  AES_BLOCK_SIZE, DMA_TO_DEVICE);

		अगर (dma_mapping_error(dev, dma_addr)) अणु
			dev_err(dev, "Mapping gcm_iv_inc1 %u B at va=%pK for DMA failed\n",
				AES_BLOCK_SIZE, (areq_ctx->gcm_iv_inc1));
			areq_ctx->gcm_iv_inc1_dma_addr = 0;
			rc = -ENOMEM;
			जाओ aead_map_failure;
		पूर्ण
		areq_ctx->gcm_iv_inc1_dma_addr = dma_addr;

		dma_addr = dma_map_single(dev, areq_ctx->gcm_iv_inc2,
					  AES_BLOCK_SIZE, DMA_TO_DEVICE);

		अगर (dma_mapping_error(dev, dma_addr)) अणु
			dev_err(dev, "Mapping gcm_iv_inc2 %u B at va=%pK for DMA failed\n",
				AES_BLOCK_SIZE, (areq_ctx->gcm_iv_inc2));
			areq_ctx->gcm_iv_inc2_dma_addr = 0;
			rc = -ENOMEM;
			जाओ aead_map_failure;
		पूर्ण
		areq_ctx->gcm_iv_inc2_dma_addr = dma_addr;
	पूर्ण

	माप_प्रकारo_map = req->cryptlen + req->assoclen;
	/* If we करो in-place encryption, we also need the auth tag */
	अगर ((areq_ctx->gen_ctx.op_type == DRV_CRYPTO_सूचीECTION_ENCRYPT) &&
	   (req->src == req->dst)) अणु
		माप_प्रकारo_map += authsize;
	पूर्ण

	rc = cc_map_sg(dev, req->src, माप_प्रकारo_map, DMA_BIसूचीECTIONAL,
		       &areq_ctx->src.mapped_nents,
		       (LLI_MAX_NUM_OF_ASSOC_DATA_ENTRIES +
			LLI_MAX_NUM_OF_DATA_ENTRIES),
		       &dummy, &mapped_nents);
	अगर (rc)
		जाओ aead_map_failure;

	अगर (areq_ctx->is_single_pass) अणु
		/*
		 * Create MLLI table क्रम:
		 *   (1) Assoc. data
		 *   (2) Src/Dst SGLs
		 *   Note: IV is contg. buffer (not an SGL)
		 */
		rc = cc_aead_chain_assoc(drvdata, req, &sg_data, true, false);
		अगर (rc)
			जाओ aead_map_failure;
		rc = cc_aead_chain_iv(drvdata, req, &sg_data, true, false);
		अगर (rc)
			जाओ aead_map_failure;
		rc = cc_aead_chain_data(drvdata, req, &sg_data, true, false);
		अगर (rc)
			जाओ aead_map_failure;
	पूर्ण अन्यथा अणु /* DOUBLE-PASS flow */
		/*
		 * Prepare MLLI table(s) in this order:
		 *
		 * If ENCRYPT/DECRYPT (inplace):
		 *   (1) MLLI table क्रम assoc
		 *   (2) IV entry (chained right after end of assoc)
		 *   (3) MLLI क्रम src/dst (inplace operation)
		 *
		 * If ENCRYPT (non-inplace)
		 *   (1) MLLI table क्रम assoc
		 *   (2) IV entry (chained right after end of assoc)
		 *   (3) MLLI क्रम dst
		 *   (4) MLLI क्रम src
		 *
		 * If DECRYPT (non-inplace)
		 *   (1) MLLI table क्रम assoc
		 *   (2) IV entry (chained right after end of assoc)
		 *   (3) MLLI क्रम src
		 *   (4) MLLI क्रम dst
		 */
		rc = cc_aead_chain_assoc(drvdata, req, &sg_data, false, true);
		अगर (rc)
			जाओ aead_map_failure;
		rc = cc_aead_chain_iv(drvdata, req, &sg_data, false, true);
		अगर (rc)
			जाओ aead_map_failure;
		rc = cc_aead_chain_data(drvdata, req, &sg_data, true, true);
		अगर (rc)
			जाओ aead_map_failure;
	पूर्ण

	/* Mlli support -start building the MLLI according to the above
	 * results
	 */
	अगर (areq_ctx->assoc_buff_type == CC_DMA_BUF_MLLI ||
	    areq_ctx->data_buff_type == CC_DMA_BUF_MLLI) अणु
		mlli_params->curr_pool = drvdata->mlli_buffs_pool;
		rc = cc_generate_mlli(dev, &sg_data, mlli_params, flags);
		अगर (rc)
			जाओ aead_map_failure;

		cc_update_aead_mlli_nents(drvdata, req);
		dev_dbg(dev, "assoc params mn %d\n",
			areq_ctx->assoc.mlli_nents);
		dev_dbg(dev, "src params mn %d\n", areq_ctx->src.mlli_nents);
		dev_dbg(dev, "dst params mn %d\n", areq_ctx->dst.mlli_nents);
	पूर्ण
	वापस 0;

aead_map_failure:
	cc_unmap_aead_request(dev, req);
	वापस rc;
पूर्ण

पूर्णांक cc_map_hash_request_final(काष्ठा cc_drvdata *drvdata, व्योम *ctx,
			      काष्ठा scatterlist *src, अचिन्हित पूर्णांक nbytes,
			      bool करो_update, gfp_t flags)
अणु
	काष्ठा ahash_req_ctx *areq_ctx = (काष्ठा ahash_req_ctx *)ctx;
	काष्ठा device *dev = drvdata_to_dev(drvdata);
	u8 *curr_buff = cc_hash_buf(areq_ctx);
	u32 *curr_buff_cnt = cc_hash_buf_cnt(areq_ctx);
	काष्ठा mlli_params *mlli_params = &areq_ctx->mlli_params;
	काष्ठा buffer_array sg_data;
	पूर्णांक rc = 0;
	u32 dummy = 0;
	u32 mapped_nents = 0;

	dev_dbg(dev, "final params : curr_buff=%pK curr_buff_cnt=0x%X nbytes = 0x%X src=%pK curr_index=%u\n",
		curr_buff, *curr_buff_cnt, nbytes, src, areq_ctx->buff_index);
	/* Init the type of the dma buffer */
	areq_ctx->data_dma_buf_type = CC_DMA_BUF_शून्य;
	mlli_params->curr_pool = शून्य;
	sg_data.num_of_buffers = 0;
	areq_ctx->in_nents = 0;

	अगर (nbytes == 0 && *curr_buff_cnt == 0) अणु
		/* nothing to करो */
		वापस 0;
	पूर्ण

	/* map the previous buffer */
	अगर (*curr_buff_cnt) अणु
		rc = cc_set_hash_buf(dev, areq_ctx, curr_buff, *curr_buff_cnt,
				     &sg_data);
		अगर (rc)
			वापस rc;
	पूर्ण

	अगर (src && nbytes > 0 && करो_update) अणु
		rc = cc_map_sg(dev, src, nbytes, DMA_TO_DEVICE,
			       &areq_ctx->in_nents, LLI_MAX_NUM_OF_DATA_ENTRIES,
			       &dummy, &mapped_nents);
		अगर (rc)
			जाओ unmap_curr_buff;
		अगर (src && mapped_nents == 1 &&
		    areq_ctx->data_dma_buf_type == CC_DMA_BUF_शून्य) अणु
			स_नकल(areq_ctx->buff_sg, src,
			       माप(काष्ठा scatterlist));
			areq_ctx->buff_sg->length = nbytes;
			areq_ctx->curr_sg = areq_ctx->buff_sg;
			areq_ctx->data_dma_buf_type = CC_DMA_BUF_DLLI;
		पूर्ण अन्यथा अणु
			areq_ctx->data_dma_buf_type = CC_DMA_BUF_MLLI;
		पूर्ण
	पूर्ण

	/*build mlli */
	अगर (areq_ctx->data_dma_buf_type == CC_DMA_BUF_MLLI) अणु
		mlli_params->curr_pool = drvdata->mlli_buffs_pool;
		/* add the src data to the sg_data */
		cc_add_sg_entry(dev, &sg_data, areq_ctx->in_nents, src, nbytes,
				0, true, &areq_ctx->mlli_nents);
		rc = cc_generate_mlli(dev, &sg_data, mlli_params, flags);
		अगर (rc)
			जाओ fail_unmap_din;
	पूर्ण
	/* change the buffer index क्रम the unmap function */
	areq_ctx->buff_index = (areq_ctx->buff_index ^ 1);
	dev_dbg(dev, "areq_ctx->data_dma_buf_type = %s\n",
		cc_dma_buf_type(areq_ctx->data_dma_buf_type));
	वापस 0;

fail_unmap_din:
	dma_unmap_sg(dev, src, areq_ctx->in_nents, DMA_TO_DEVICE);

unmap_curr_buff:
	अगर (*curr_buff_cnt)
		dma_unmap_sg(dev, areq_ctx->buff_sg, 1, DMA_TO_DEVICE);

	वापस rc;
पूर्ण

पूर्णांक cc_map_hash_request_update(काष्ठा cc_drvdata *drvdata, व्योम *ctx,
			       काष्ठा scatterlist *src, अचिन्हित पूर्णांक nbytes,
			       अचिन्हित पूर्णांक block_size, gfp_t flags)
अणु
	काष्ठा ahash_req_ctx *areq_ctx = (काष्ठा ahash_req_ctx *)ctx;
	काष्ठा device *dev = drvdata_to_dev(drvdata);
	u8 *curr_buff = cc_hash_buf(areq_ctx);
	u32 *curr_buff_cnt = cc_hash_buf_cnt(areq_ctx);
	u8 *next_buff = cc_next_buf(areq_ctx);
	u32 *next_buff_cnt = cc_next_buf_cnt(areq_ctx);
	काष्ठा mlli_params *mlli_params = &areq_ctx->mlli_params;
	अचिन्हित पूर्णांक update_data_len;
	u32 total_in_len = nbytes + *curr_buff_cnt;
	काष्ठा buffer_array sg_data;
	अचिन्हित पूर्णांक swap_index = 0;
	पूर्णांक rc = 0;
	u32 dummy = 0;
	u32 mapped_nents = 0;

	dev_dbg(dev, " update params : curr_buff=%pK curr_buff_cnt=0x%X nbytes=0x%X src=%pK curr_index=%u\n",
		curr_buff, *curr_buff_cnt, nbytes, src, areq_ctx->buff_index);
	/* Init the type of the dma buffer */
	areq_ctx->data_dma_buf_type = CC_DMA_BUF_शून्य;
	mlli_params->curr_pool = शून्य;
	areq_ctx->curr_sg = शून्य;
	sg_data.num_of_buffers = 0;
	areq_ctx->in_nents = 0;

	अगर (total_in_len < block_size) अणु
		dev_dbg(dev, " less than one block: curr_buff=%pK *curr_buff_cnt=0x%X copy_to=%pK\n",
			curr_buff, *curr_buff_cnt, &curr_buff[*curr_buff_cnt]);
		areq_ctx->in_nents = sg_nents_क्रम_len(src, nbytes);
		sg_copy_to_buffer(src, areq_ctx->in_nents,
				  &curr_buff[*curr_buff_cnt], nbytes);
		*curr_buff_cnt += nbytes;
		वापस 1;
	पूर्ण

	/* Calculate the residue size*/
	*next_buff_cnt = total_in_len & (block_size - 1);
	/* update data len */
	update_data_len = total_in_len - *next_buff_cnt;

	dev_dbg(dev, " temp length : *next_buff_cnt=0x%X update_data_len=0x%X\n",
		*next_buff_cnt, update_data_len);

	/* Copy the new residue to next buffer */
	अगर (*next_buff_cnt) अणु
		dev_dbg(dev, " handle residue: next buff %pK skip data %u residue %u\n",
			next_buff, (update_data_len - *curr_buff_cnt),
			*next_buff_cnt);
		cc_copy_sg_portion(dev, next_buff, src,
				   (update_data_len - *curr_buff_cnt),
				   nbytes, CC_SG_TO_BUF);
		/* change the buffer index क्रम next operation */
		swap_index = 1;
	पूर्ण

	अगर (*curr_buff_cnt) अणु
		rc = cc_set_hash_buf(dev, areq_ctx, curr_buff, *curr_buff_cnt,
				     &sg_data);
		अगर (rc)
			वापस rc;
		/* change the buffer index क्रम next operation */
		swap_index = 1;
	पूर्ण

	अगर (update_data_len > *curr_buff_cnt) अणु
		rc = cc_map_sg(dev, src, (update_data_len - *curr_buff_cnt),
			       DMA_TO_DEVICE, &areq_ctx->in_nents,
			       LLI_MAX_NUM_OF_DATA_ENTRIES, &dummy,
			       &mapped_nents);
		अगर (rc)
			जाओ unmap_curr_buff;
		अगर (mapped_nents == 1 &&
		    areq_ctx->data_dma_buf_type == CC_DMA_BUF_शून्य) अणु
			/* only one entry in the SG and no previous data */
			स_नकल(areq_ctx->buff_sg, src,
			       माप(काष्ठा scatterlist));
			areq_ctx->buff_sg->length = update_data_len;
			areq_ctx->data_dma_buf_type = CC_DMA_BUF_DLLI;
			areq_ctx->curr_sg = areq_ctx->buff_sg;
		पूर्ण अन्यथा अणु
			areq_ctx->data_dma_buf_type = CC_DMA_BUF_MLLI;
		पूर्ण
	पूर्ण

	अगर (areq_ctx->data_dma_buf_type == CC_DMA_BUF_MLLI) अणु
		mlli_params->curr_pool = drvdata->mlli_buffs_pool;
		/* add the src data to the sg_data */
		cc_add_sg_entry(dev, &sg_data, areq_ctx->in_nents, src,
				(update_data_len - *curr_buff_cnt), 0, true,
				&areq_ctx->mlli_nents);
		rc = cc_generate_mlli(dev, &sg_data, mlli_params, flags);
		अगर (rc)
			जाओ fail_unmap_din;
	पूर्ण
	areq_ctx->buff_index = (areq_ctx->buff_index ^ swap_index);

	वापस 0;

fail_unmap_din:
	dma_unmap_sg(dev, src, areq_ctx->in_nents, DMA_TO_DEVICE);

unmap_curr_buff:
	अगर (*curr_buff_cnt)
		dma_unmap_sg(dev, areq_ctx->buff_sg, 1, DMA_TO_DEVICE);

	वापस rc;
पूर्ण

व्योम cc_unmap_hash_request(काष्ठा device *dev, व्योम *ctx,
			   काष्ठा scatterlist *src, bool करो_revert)
अणु
	काष्ठा ahash_req_ctx *areq_ctx = (काष्ठा ahash_req_ctx *)ctx;
	u32 *prev_len = cc_next_buf_cnt(areq_ctx);

	/*In हाल a pool was set, a table was
	 *allocated and should be released
	 */
	अगर (areq_ctx->mlli_params.curr_pool) अणु
		dev_dbg(dev, "free MLLI buffer: dma=%pad virt=%pK\n",
			&areq_ctx->mlli_params.mlli_dma_addr,
			areq_ctx->mlli_params.mlli_virt_addr);
		dma_pool_मुक्त(areq_ctx->mlli_params.curr_pool,
			      areq_ctx->mlli_params.mlli_virt_addr,
			      areq_ctx->mlli_params.mlli_dma_addr);
	पूर्ण

	अगर (src && areq_ctx->in_nents) अणु
		dev_dbg(dev, "Unmapped sg src: virt=%pK dma=%pad len=0x%X\n",
			sg_virt(src), &sg_dma_address(src), sg_dma_len(src));
		dma_unmap_sg(dev, src,
			     areq_ctx->in_nents, DMA_TO_DEVICE);
	पूर्ण

	अगर (*prev_len) अणु
		dev_dbg(dev, "Unmapped buffer: areq_ctx->buff_sg=%pK dma=%pad len 0x%X\n",
			sg_virt(areq_ctx->buff_sg),
			&sg_dma_address(areq_ctx->buff_sg),
			sg_dma_len(areq_ctx->buff_sg));
		dma_unmap_sg(dev, areq_ctx->buff_sg, 1, DMA_TO_DEVICE);
		अगर (!करो_revert) अणु
			/* clean the previous data length क्रम update
			 * operation
			 */
			*prev_len = 0;
		पूर्ण अन्यथा अणु
			areq_ctx->buff_index ^= 1;
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक cc_buffer_mgr_init(काष्ठा cc_drvdata *drvdata)
अणु
	काष्ठा device *dev = drvdata_to_dev(drvdata);

	drvdata->mlli_buffs_pool =
		dma_pool_create("dx_single_mlli_tables", dev,
				MAX_NUM_OF_TOTAL_MLLI_ENTRIES *
				LLI_ENTRY_BYTE_SIZE,
				MLLI_TABLE_MIN_ALIGNMENT, 0);

	अगर (!drvdata->mlli_buffs_pool)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

पूर्णांक cc_buffer_mgr_fini(काष्ठा cc_drvdata *drvdata)
अणु
	dma_pool_destroy(drvdata->mlli_buffs_pool);
	वापस 0;
पूर्ण
