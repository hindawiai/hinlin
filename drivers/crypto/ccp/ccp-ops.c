<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AMD Cryptographic Coprocessor (CCP) driver
 *
 * Copyright (C) 2013-2019 Advanced Micro Devices, Inc.
 *
 * Author: Tom Lendacky <thomas.lendacky@amd.com>
 * Author: Gary R Hook <gary.hook@amd.com>
 */

#समावेश <linux/dma-mapping.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <crypto/scatterwalk.h>
#समावेश <crypto/des.h>
#समावेश <linux/ccp.h>

#समावेश "ccp-dev.h"

/* SHA initial context values */
अटल स्थिर __be32 ccp_sha1_init[SHA1_DIGEST_SIZE / माप(__be32)] = अणु
	cpu_to_be32(SHA1_H0), cpu_to_be32(SHA1_H1),
	cpu_to_be32(SHA1_H2), cpu_to_be32(SHA1_H3),
	cpu_to_be32(SHA1_H4),
पूर्ण;

अटल स्थिर __be32 ccp_sha224_init[SHA256_DIGEST_SIZE / माप(__be32)] = अणु
	cpu_to_be32(SHA224_H0), cpu_to_be32(SHA224_H1),
	cpu_to_be32(SHA224_H2), cpu_to_be32(SHA224_H3),
	cpu_to_be32(SHA224_H4), cpu_to_be32(SHA224_H5),
	cpu_to_be32(SHA224_H6), cpu_to_be32(SHA224_H7),
पूर्ण;

अटल स्थिर __be32 ccp_sha256_init[SHA256_DIGEST_SIZE / माप(__be32)] = अणु
	cpu_to_be32(SHA256_H0), cpu_to_be32(SHA256_H1),
	cpu_to_be32(SHA256_H2), cpu_to_be32(SHA256_H3),
	cpu_to_be32(SHA256_H4), cpu_to_be32(SHA256_H5),
	cpu_to_be32(SHA256_H6), cpu_to_be32(SHA256_H7),
पूर्ण;

अटल स्थिर __be64 ccp_sha384_init[SHA512_DIGEST_SIZE / माप(__be64)] = अणु
	cpu_to_be64(SHA384_H0), cpu_to_be64(SHA384_H1),
	cpu_to_be64(SHA384_H2), cpu_to_be64(SHA384_H3),
	cpu_to_be64(SHA384_H4), cpu_to_be64(SHA384_H5),
	cpu_to_be64(SHA384_H6), cpu_to_be64(SHA384_H7),
पूर्ण;

अटल स्थिर __be64 ccp_sha512_init[SHA512_DIGEST_SIZE / माप(__be64)] = अणु
	cpu_to_be64(SHA512_H0), cpu_to_be64(SHA512_H1),
	cpu_to_be64(SHA512_H2), cpu_to_be64(SHA512_H3),
	cpu_to_be64(SHA512_H4), cpu_to_be64(SHA512_H5),
	cpu_to_be64(SHA512_H6), cpu_to_be64(SHA512_H7),
पूर्ण;

#घोषणा	CCP_NEW_JOBID(ccp)	((ccp->vdata->version == CCP_VERSION(3, 0)) ? \
					ccp_gen_jobid(ccp) : 0)

अटल u32 ccp_gen_jobid(काष्ठा ccp_device *ccp)
अणु
	वापस atomic_inc_वापस(&ccp->current_id) & CCP_JOBID_MASK;
पूर्ण

अटल व्योम ccp_sg_मुक्त(काष्ठा ccp_sg_workarea *wa)
अणु
	अगर (wa->dma_count)
		dma_unmap_sg(wa->dma_dev, wa->dma_sg_head, wa->nents, wa->dma_dir);

	wa->dma_count = 0;
पूर्ण

अटल पूर्णांक ccp_init_sg_workarea(काष्ठा ccp_sg_workarea *wa, काष्ठा device *dev,
				काष्ठा scatterlist *sg, u64 len,
				क्रमागत dma_data_direction dma_dir)
अणु
	स_रखो(wa, 0, माप(*wa));

	wa->sg = sg;
	अगर (!sg)
		वापस 0;

	wa->nents = sg_nents_क्रम_len(sg, len);
	अगर (wa->nents < 0)
		वापस wa->nents;

	wa->bytes_left = len;
	wa->sg_used = 0;

	अगर (len == 0)
		वापस 0;

	अगर (dma_dir == DMA_NONE)
		वापस 0;

	wa->dma_sg = sg;
	wa->dma_sg_head = sg;
	wa->dma_dev = dev;
	wa->dma_dir = dma_dir;
	wa->dma_count = dma_map_sg(dev, sg, wa->nents, dma_dir);
	अगर (!wa->dma_count)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल व्योम ccp_update_sg_workarea(काष्ठा ccp_sg_workarea *wa, अचिन्हित पूर्णांक len)
अणु
	अचिन्हित पूर्णांक nbytes = min_t(u64, len, wa->bytes_left);
	अचिन्हित पूर्णांक sg_combined_len = 0;

	अगर (!wa->sg)
		वापस;

	wa->sg_used += nbytes;
	wa->bytes_left -= nbytes;
	अगर (wa->sg_used == sg_dma_len(wa->dma_sg)) अणु
		/* Advance to the next DMA scatterlist entry */
		wa->dma_sg = sg_next(wa->dma_sg);

		/* In the हाल that the DMA mapped scatterlist has entries
		 * that have been merged, the non-DMA mapped scatterlist
		 * must be advanced multiple बार क्रम each merged entry.
		 * This ensures that the current non-DMA mapped entry
		 * corresponds to the current DMA mapped entry.
		 */
		करो अणु
			sg_combined_len += wa->sg->length;
			wa->sg = sg_next(wa->sg);
		पूर्ण जबतक (wa->sg_used > sg_combined_len);

		wa->sg_used = 0;
	पूर्ण
पूर्ण

अटल व्योम ccp_dm_मुक्त(काष्ठा ccp_dm_workarea *wa)
अणु
	अगर (wa->length <= CCP_DMAPOOL_MAX_SIZE) अणु
		अगर (wa->address)
			dma_pool_मुक्त(wa->dma_pool, wa->address,
				      wa->dma.address);
	पूर्ण अन्यथा अणु
		अगर (wa->dma.address)
			dma_unmap_single(wa->dev, wa->dma.address, wa->length,
					 wa->dma.dir);
		kमुक्त(wa->address);
	पूर्ण

	wa->address = शून्य;
	wa->dma.address = 0;
पूर्ण

अटल पूर्णांक ccp_init_dm_workarea(काष्ठा ccp_dm_workarea *wa,
				काष्ठा ccp_cmd_queue *cmd_q,
				अचिन्हित पूर्णांक len,
				क्रमागत dma_data_direction dir)
अणु
	स_रखो(wa, 0, माप(*wa));

	अगर (!len)
		वापस 0;

	wa->dev = cmd_q->ccp->dev;
	wa->length = len;

	अगर (len <= CCP_DMAPOOL_MAX_SIZE) अणु
		wa->dma_pool = cmd_q->dma_pool;

		wa->address = dma_pool_zalloc(wa->dma_pool, GFP_KERNEL,
					     &wa->dma.address);
		अगर (!wa->address)
			वापस -ENOMEM;

		wa->dma.length = CCP_DMAPOOL_MAX_SIZE;

	पूर्ण अन्यथा अणु
		wa->address = kzalloc(len, GFP_KERNEL);
		अगर (!wa->address)
			वापस -ENOMEM;

		wa->dma.address = dma_map_single(wa->dev, wa->address, len,
						 dir);
		अगर (dma_mapping_error(wa->dev, wa->dma.address))
			वापस -ENOMEM;

		wa->dma.length = len;
	पूर्ण
	wa->dma.dir = dir;

	वापस 0;
पूर्ण

अटल पूर्णांक ccp_set_dm_area(काष्ठा ccp_dm_workarea *wa, अचिन्हित पूर्णांक wa_offset,
			   काष्ठा scatterlist *sg, अचिन्हित पूर्णांक sg_offset,
			   अचिन्हित पूर्णांक len)
अणु
	WARN_ON(!wa->address);

	अगर (len > (wa->length - wa_offset))
		वापस -EINVAL;

	scatterwalk_map_and_copy(wa->address + wa_offset, sg, sg_offset, len,
				 0);
	वापस 0;
पूर्ण

अटल व्योम ccp_get_dm_area(काष्ठा ccp_dm_workarea *wa, अचिन्हित पूर्णांक wa_offset,
			    काष्ठा scatterlist *sg, अचिन्हित पूर्णांक sg_offset,
			    अचिन्हित पूर्णांक len)
अणु
	WARN_ON(!wa->address);

	scatterwalk_map_and_copy(wa->address + wa_offset, sg, sg_offset, len,
				 1);
पूर्ण

अटल पूर्णांक ccp_reverse_set_dm_area(काष्ठा ccp_dm_workarea *wa,
				   अचिन्हित पूर्णांक wa_offset,
				   काष्ठा scatterlist *sg,
				   अचिन्हित पूर्णांक sg_offset,
				   अचिन्हित पूर्णांक len)
अणु
	u8 *p, *q;
	पूर्णांक	rc;

	rc = ccp_set_dm_area(wa, wa_offset, sg, sg_offset, len);
	अगर (rc)
		वापस rc;

	p = wa->address + wa_offset;
	q = p + len - 1;
	जबतक (p < q) अणु
		*p = *p ^ *q;
		*q = *p ^ *q;
		*p = *p ^ *q;
		p++;
		q--;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम ccp_reverse_get_dm_area(काष्ठा ccp_dm_workarea *wa,
				    अचिन्हित पूर्णांक wa_offset,
				    काष्ठा scatterlist *sg,
				    अचिन्हित पूर्णांक sg_offset,
				    अचिन्हित पूर्णांक len)
अणु
	u8 *p, *q;

	p = wa->address + wa_offset;
	q = p + len - 1;
	जबतक (p < q) अणु
		*p = *p ^ *q;
		*q = *p ^ *q;
		*p = *p ^ *q;
		p++;
		q--;
	पूर्ण

	ccp_get_dm_area(wa, wa_offset, sg, sg_offset, len);
पूर्ण

अटल व्योम ccp_मुक्त_data(काष्ठा ccp_data *data, काष्ठा ccp_cmd_queue *cmd_q)
अणु
	ccp_dm_मुक्त(&data->dm_wa);
	ccp_sg_मुक्त(&data->sg_wa);
पूर्ण

अटल पूर्णांक ccp_init_data(काष्ठा ccp_data *data, काष्ठा ccp_cmd_queue *cmd_q,
			 काष्ठा scatterlist *sg, u64 sg_len,
			 अचिन्हित पूर्णांक dm_len,
			 क्रमागत dma_data_direction dir)
अणु
	पूर्णांक ret;

	स_रखो(data, 0, माप(*data));

	ret = ccp_init_sg_workarea(&data->sg_wa, cmd_q->ccp->dev, sg, sg_len,
				   dir);
	अगर (ret)
		जाओ e_err;

	ret = ccp_init_dm_workarea(&data->dm_wa, cmd_q, dm_len, dir);
	अगर (ret)
		जाओ e_err;

	वापस 0;

e_err:
	ccp_मुक्त_data(data, cmd_q);

	वापस ret;
पूर्ण

अटल अचिन्हित पूर्णांक ccp_queue_buf(काष्ठा ccp_data *data, अचिन्हित पूर्णांक from)
अणु
	काष्ठा ccp_sg_workarea *sg_wa = &data->sg_wa;
	काष्ठा ccp_dm_workarea *dm_wa = &data->dm_wa;
	अचिन्हित पूर्णांक buf_count, nbytes;

	/* Clear the buffer अगर setting it */
	अगर (!from)
		स_रखो(dm_wa->address, 0, dm_wa->length);

	अगर (!sg_wa->sg)
		वापस 0;

	/* Perक्रमm the copy operation
	 *   nbytes will always be <= अच_पूर्णांक_उच्च because dm_wa->length is
	 *   an अचिन्हित पूर्णांक
	 */
	nbytes = min_t(u64, sg_wa->bytes_left, dm_wa->length);
	scatterwalk_map_and_copy(dm_wa->address, sg_wa->sg, sg_wa->sg_used,
				 nbytes, from);

	/* Update the काष्ठाures and generate the count */
	buf_count = 0;
	जबतक (sg_wa->bytes_left && (buf_count < dm_wa->length)) अणु
		nbytes = min(sg_dma_len(sg_wa->dma_sg) - sg_wa->sg_used,
			     dm_wa->length - buf_count);
		nbytes = min_t(u64, sg_wa->bytes_left, nbytes);

		buf_count += nbytes;
		ccp_update_sg_workarea(sg_wa, nbytes);
	पूर्ण

	वापस buf_count;
पूर्ण

अटल अचिन्हित पूर्णांक ccp_fill_queue_buf(काष्ठा ccp_data *data)
अणु
	वापस ccp_queue_buf(data, 0);
पूर्ण

अटल अचिन्हित पूर्णांक ccp_empty_queue_buf(काष्ठा ccp_data *data)
अणु
	वापस ccp_queue_buf(data, 1);
पूर्ण

अटल व्योम ccp_prepare_data(काष्ठा ccp_data *src, काष्ठा ccp_data *dst,
			     काष्ठा ccp_op *op, अचिन्हित पूर्णांक block_size,
			     bool blocksize_op)
अणु
	अचिन्हित पूर्णांक sg_src_len, sg_dst_len, op_len;

	/* The CCP can only DMA from/to one address each per operation. This
	 * requires that we find the smallest DMA area between the source
	 * and destination. The resulting len values will always be <= अच_पूर्णांक_उच्च
	 * because the dma length is an अचिन्हित पूर्णांक.
	 */
	sg_src_len = sg_dma_len(src->sg_wa.dma_sg) - src->sg_wa.sg_used;
	sg_src_len = min_t(u64, src->sg_wa.bytes_left, sg_src_len);

	अगर (dst) अणु
		sg_dst_len = sg_dma_len(dst->sg_wa.dma_sg) - dst->sg_wa.sg_used;
		sg_dst_len = min_t(u64, src->sg_wa.bytes_left, sg_dst_len);
		op_len = min(sg_src_len, sg_dst_len);
	पूर्ण अन्यथा अणु
		op_len = sg_src_len;
	पूर्ण

	/* The data operation length will be at least block_size in length
	 * or the smaller of available sg room reमुख्यing क्रम the source or
	 * the destination
	 */
	op_len = max(op_len, block_size);

	/* Unless we have to buffer data, there's no reason to रुको */
	op->soc = 0;

	अगर (sg_src_len < block_size) अणु
		/* Not enough data in the sg element, so it
		 * needs to be buffered पूर्णांकo a blocksize chunk
		 */
		पूर्णांक cp_len = ccp_fill_queue_buf(src);

		op->soc = 1;
		op->src.u.dma.address = src->dm_wa.dma.address;
		op->src.u.dma.offset = 0;
		op->src.u.dma.length = (blocksize_op) ? block_size : cp_len;
	पूर्ण अन्यथा अणु
		/* Enough data in the sg element, but we need to
		 * adjust क्रम any previously copied data
		 */
		op->src.u.dma.address = sg_dma_address(src->sg_wa.dma_sg);
		op->src.u.dma.offset = src->sg_wa.sg_used;
		op->src.u.dma.length = op_len & ~(block_size - 1);

		ccp_update_sg_workarea(&src->sg_wa, op->src.u.dma.length);
	पूर्ण

	अगर (dst) अणु
		अगर (sg_dst_len < block_size) अणु
			/* Not enough room in the sg element or we're on the
			 * last piece of data (when using padding), so the
			 * output needs to be buffered पूर्णांकo a blocksize chunk
			 */
			op->soc = 1;
			op->dst.u.dma.address = dst->dm_wa.dma.address;
			op->dst.u.dma.offset = 0;
			op->dst.u.dma.length = op->src.u.dma.length;
		पूर्ण अन्यथा अणु
			/* Enough room in the sg element, but we need to
			 * adjust क्रम any previously used area
			 */
			op->dst.u.dma.address = sg_dma_address(dst->sg_wa.dma_sg);
			op->dst.u.dma.offset = dst->sg_wa.sg_used;
			op->dst.u.dma.length = op->src.u.dma.length;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम ccp_process_data(काष्ठा ccp_data *src, काष्ठा ccp_data *dst,
			     काष्ठा ccp_op *op)
अणु
	op->init = 0;

	अगर (dst) अणु
		अगर (op->dst.u.dma.address == dst->dm_wa.dma.address)
			ccp_empty_queue_buf(dst);
		अन्यथा
			ccp_update_sg_workarea(&dst->sg_wa,
					       op->dst.u.dma.length);
	पूर्ण
पूर्ण

अटल पूर्णांक ccp_copy_to_from_sb(काष्ठा ccp_cmd_queue *cmd_q,
			       काष्ठा ccp_dm_workarea *wa, u32 jobid, u32 sb,
			       u32 byte_swap, bool from)
अणु
	काष्ठा ccp_op op;

	स_रखो(&op, 0, माप(op));

	op.cmd_q = cmd_q;
	op.jobid = jobid;
	op.eom = 1;

	अगर (from) अणु
		op.soc = 1;
		op.src.type = CCP_MEMTYPE_SB;
		op.src.u.sb = sb;
		op.dst.type = CCP_MEMTYPE_SYSTEM;
		op.dst.u.dma.address = wa->dma.address;
		op.dst.u.dma.length = wa->length;
	पूर्ण अन्यथा अणु
		op.src.type = CCP_MEMTYPE_SYSTEM;
		op.src.u.dma.address = wa->dma.address;
		op.src.u.dma.length = wa->length;
		op.dst.type = CCP_MEMTYPE_SB;
		op.dst.u.sb = sb;
	पूर्ण

	op.u.passthru.byte_swap = byte_swap;

	वापस cmd_q->ccp->vdata->perक्रमm->passthru(&op);
पूर्ण

अटल पूर्णांक ccp_copy_to_sb(काष्ठा ccp_cmd_queue *cmd_q,
			  काष्ठा ccp_dm_workarea *wa, u32 jobid, u32 sb,
			  u32 byte_swap)
अणु
	वापस ccp_copy_to_from_sb(cmd_q, wa, jobid, sb, byte_swap, false);
पूर्ण

अटल पूर्णांक ccp_copy_from_sb(काष्ठा ccp_cmd_queue *cmd_q,
			    काष्ठा ccp_dm_workarea *wa, u32 jobid, u32 sb,
			    u32 byte_swap)
अणु
	वापस ccp_copy_to_from_sb(cmd_q, wa, jobid, sb, byte_swap, true);
पूर्ण

अटल noअंतरभूत_क्रम_stack पूर्णांक
ccp_run_aes_cmac_cmd(काष्ठा ccp_cmd_queue *cmd_q, काष्ठा ccp_cmd *cmd)
अणु
	काष्ठा ccp_aes_engine *aes = &cmd->u.aes;
	काष्ठा ccp_dm_workarea key, ctx;
	काष्ठा ccp_data src;
	काष्ठा ccp_op op;
	अचिन्हित पूर्णांक dm_offset;
	पूर्णांक ret;

	अगर (!((aes->key_len == AES_KEYSIZE_128) ||
	      (aes->key_len == AES_KEYSIZE_192) ||
	      (aes->key_len == AES_KEYSIZE_256)))
		वापस -EINVAL;

	अगर (aes->src_len & (AES_BLOCK_SIZE - 1))
		वापस -EINVAL;

	अगर (aes->iv_len != AES_BLOCK_SIZE)
		वापस -EINVAL;

	अगर (!aes->key || !aes->iv || !aes->src)
		वापस -EINVAL;

	अगर (aes->cmac_final) अणु
		अगर (aes->cmac_key_len != AES_BLOCK_SIZE)
			वापस -EINVAL;

		अगर (!aes->cmac_key)
			वापस -EINVAL;
	पूर्ण

	BUILD_BUG_ON(CCP_AES_KEY_SB_COUNT != 1);
	BUILD_BUG_ON(CCP_AES_CTX_SB_COUNT != 1);

	ret = -EIO;
	स_रखो(&op, 0, माप(op));
	op.cmd_q = cmd_q;
	op.jobid = CCP_NEW_JOBID(cmd_q->ccp);
	op.sb_key = cmd_q->sb_key;
	op.sb_ctx = cmd_q->sb_ctx;
	op.init = 1;
	op.u.aes.type = aes->type;
	op.u.aes.mode = aes->mode;
	op.u.aes.action = aes->action;

	/* All supported key sizes fit in a single (32-byte) SB entry
	 * and must be in little endian क्रमmat. Use the 256-bit byte
	 * swap passthru option to convert from big endian to little
	 * endian.
	 */
	ret = ccp_init_dm_workarea(&key, cmd_q,
				   CCP_AES_KEY_SB_COUNT * CCP_SB_BYTES,
				   DMA_TO_DEVICE);
	अगर (ret)
		वापस ret;

	dm_offset = CCP_SB_BYTES - aes->key_len;
	ret = ccp_set_dm_area(&key, dm_offset, aes->key, 0, aes->key_len);
	अगर (ret)
		जाओ e_key;
	ret = ccp_copy_to_sb(cmd_q, &key, op.jobid, op.sb_key,
			     CCP_PASSTHRU_BYTESWAP_256BIT);
	अगर (ret) अणु
		cmd->engine_error = cmd_q->cmd_error;
		जाओ e_key;
	पूर्ण

	/* The AES context fits in a single (32-byte) SB entry and
	 * must be in little endian क्रमmat. Use the 256-bit byte swap
	 * passthru option to convert from big endian to little endian.
	 */
	ret = ccp_init_dm_workarea(&ctx, cmd_q,
				   CCP_AES_CTX_SB_COUNT * CCP_SB_BYTES,
				   DMA_BIसूचीECTIONAL);
	अगर (ret)
		जाओ e_key;

	dm_offset = CCP_SB_BYTES - AES_BLOCK_SIZE;
	ret = ccp_set_dm_area(&ctx, dm_offset, aes->iv, 0, aes->iv_len);
	अगर (ret)
		जाओ e_ctx;
	ret = ccp_copy_to_sb(cmd_q, &ctx, op.jobid, op.sb_ctx,
			     CCP_PASSTHRU_BYTESWAP_256BIT);
	अगर (ret) अणु
		cmd->engine_error = cmd_q->cmd_error;
		जाओ e_ctx;
	पूर्ण

	/* Send data to the CCP AES engine */
	ret = ccp_init_data(&src, cmd_q, aes->src, aes->src_len,
			    AES_BLOCK_SIZE, DMA_TO_DEVICE);
	अगर (ret)
		जाओ e_ctx;

	जबतक (src.sg_wa.bytes_left) अणु
		ccp_prepare_data(&src, शून्य, &op, AES_BLOCK_SIZE, true);
		अगर (aes->cmac_final && !src.sg_wa.bytes_left) अणु
			op.eom = 1;

			/* Push the K1/K2 key to the CCP now */
			ret = ccp_copy_from_sb(cmd_q, &ctx, op.jobid,
					       op.sb_ctx,
					       CCP_PASSTHRU_BYTESWAP_256BIT);
			अगर (ret) अणु
				cmd->engine_error = cmd_q->cmd_error;
				जाओ e_src;
			पूर्ण

			ret = ccp_set_dm_area(&ctx, 0, aes->cmac_key, 0,
					      aes->cmac_key_len);
			अगर (ret)
				जाओ e_src;
			ret = ccp_copy_to_sb(cmd_q, &ctx, op.jobid, op.sb_ctx,
					     CCP_PASSTHRU_BYTESWAP_256BIT);
			अगर (ret) अणु
				cmd->engine_error = cmd_q->cmd_error;
				जाओ e_src;
			पूर्ण
		पूर्ण

		ret = cmd_q->ccp->vdata->perक्रमm->aes(&op);
		अगर (ret) अणु
			cmd->engine_error = cmd_q->cmd_error;
			जाओ e_src;
		पूर्ण

		ccp_process_data(&src, शून्य, &op);
	पूर्ण

	/* Retrieve the AES context - convert from LE to BE using
	 * 32-byte (256-bit) byteswapping
	 */
	ret = ccp_copy_from_sb(cmd_q, &ctx, op.jobid, op.sb_ctx,
			       CCP_PASSTHRU_BYTESWAP_256BIT);
	अगर (ret) अणु
		cmd->engine_error = cmd_q->cmd_error;
		जाओ e_src;
	पूर्ण

	/* ...but we only need AES_BLOCK_SIZE bytes */
	dm_offset = CCP_SB_BYTES - AES_BLOCK_SIZE;
	ccp_get_dm_area(&ctx, dm_offset, aes->iv, 0, aes->iv_len);

e_src:
	ccp_मुक्त_data(&src, cmd_q);

e_ctx:
	ccp_dm_मुक्त(&ctx);

e_key:
	ccp_dm_मुक्त(&key);

	वापस ret;
पूर्ण

अटल noअंतरभूत_क्रम_stack पूर्णांक
ccp_run_aes_gcm_cmd(काष्ठा ccp_cmd_queue *cmd_q, काष्ठा ccp_cmd *cmd)
अणु
	काष्ठा ccp_aes_engine *aes = &cmd->u.aes;
	काष्ठा ccp_dm_workarea key, ctx, final_wa, tag;
	काष्ठा ccp_data src, dst;
	काष्ठा ccp_data aad;
	काष्ठा ccp_op op;
	अचिन्हित पूर्णांक dm_offset;
	अचिन्हित पूर्णांक authsize;
	अचिन्हित पूर्णांक jobid;
	अचिन्हित पूर्णांक ilen;
	bool in_place = true; /* Default value */
	__be64 *final;
	पूर्णांक ret;

	काष्ठा scatterlist *p_inp, sg_inp[2];
	काष्ठा scatterlist *p_tag, sg_tag[2];
	काष्ठा scatterlist *p_outp, sg_outp[2];
	काष्ठा scatterlist *p_aad;

	अगर (!aes->iv)
		वापस -EINVAL;

	अगर (!((aes->key_len == AES_KEYSIZE_128) ||
		(aes->key_len == AES_KEYSIZE_192) ||
		(aes->key_len == AES_KEYSIZE_256)))
		वापस -EINVAL;

	अगर (!aes->key) /* Gotta have a key SGL */
		वापस -EINVAL;

	/* Zero शेषs to 16 bytes, the maximum size */
	authsize = aes->authsize ? aes->authsize : AES_BLOCK_SIZE;
	चयन (authsize) अणु
	हाल 16:
	हाल 15:
	हाल 14:
	हाल 13:
	हाल 12:
	हाल 8:
	हाल 4:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* First, decompose the source buffer पूर्णांकo AAD & PT,
	 * and the destination buffer पूर्णांकo AAD, CT & tag, or
	 * the input पूर्णांकo CT & tag.
	 * It is expected that the input and output SGs will
	 * be valid, even अगर the AAD and input lengths are 0.
	 */
	p_aad = aes->src;
	p_inp = scatterwalk_ffwd(sg_inp, aes->src, aes->aad_len);
	p_outp = scatterwalk_ffwd(sg_outp, aes->dst, aes->aad_len);
	अगर (aes->action == CCP_AES_ACTION_ENCRYPT) अणु
		ilen = aes->src_len;
		p_tag = scatterwalk_ffwd(sg_tag, p_outp, ilen);
	पूर्ण अन्यथा अणु
		/* Input length क्रम decryption includes tag */
		ilen = aes->src_len - authsize;
		p_tag = scatterwalk_ffwd(sg_tag, p_inp, ilen);
	पूर्ण

	jobid = CCP_NEW_JOBID(cmd_q->ccp);

	स_रखो(&op, 0, माप(op));
	op.cmd_q = cmd_q;
	op.jobid = jobid;
	op.sb_key = cmd_q->sb_key; /* Pre-allocated */
	op.sb_ctx = cmd_q->sb_ctx; /* Pre-allocated */
	op.init = 1;
	op.u.aes.type = aes->type;

	/* Copy the key to the LSB */
	ret = ccp_init_dm_workarea(&key, cmd_q,
				   CCP_AES_CTX_SB_COUNT * CCP_SB_BYTES,
				   DMA_TO_DEVICE);
	अगर (ret)
		वापस ret;

	dm_offset = CCP_SB_BYTES - aes->key_len;
	ret = ccp_set_dm_area(&key, dm_offset, aes->key, 0, aes->key_len);
	अगर (ret)
		जाओ e_key;
	ret = ccp_copy_to_sb(cmd_q, &key, op.jobid, op.sb_key,
			     CCP_PASSTHRU_BYTESWAP_256BIT);
	अगर (ret) अणु
		cmd->engine_error = cmd_q->cmd_error;
		जाओ e_key;
	पूर्ण

	/* Copy the context (IV) to the LSB.
	 * There is an assumption here that the IV is 96 bits in length, plus
	 * a nonce of 32 bits. If no IV is present, use a zeroed buffer.
	 */
	ret = ccp_init_dm_workarea(&ctx, cmd_q,
				   CCP_AES_CTX_SB_COUNT * CCP_SB_BYTES,
				   DMA_BIसूचीECTIONAL);
	अगर (ret)
		जाओ e_key;

	dm_offset = CCP_AES_CTX_SB_COUNT * CCP_SB_BYTES - aes->iv_len;
	ret = ccp_set_dm_area(&ctx, dm_offset, aes->iv, 0, aes->iv_len);
	अगर (ret)
		जाओ e_ctx;

	ret = ccp_copy_to_sb(cmd_q, &ctx, op.jobid, op.sb_ctx,
			     CCP_PASSTHRU_BYTESWAP_256BIT);
	अगर (ret) अणु
		cmd->engine_error = cmd_q->cmd_error;
		जाओ e_ctx;
	पूर्ण

	op.init = 1;
	अगर (aes->aad_len > 0) अणु
		/* Step 1: Run a GHASH over the Additional Authenticated Data */
		ret = ccp_init_data(&aad, cmd_q, p_aad, aes->aad_len,
				    AES_BLOCK_SIZE,
				    DMA_TO_DEVICE);
		अगर (ret)
			जाओ e_ctx;

		op.u.aes.mode = CCP_AES_MODE_GHASH;
		op.u.aes.action = CCP_AES_GHASHAAD;

		जबतक (aad.sg_wa.bytes_left) अणु
			ccp_prepare_data(&aad, शून्य, &op, AES_BLOCK_SIZE, true);

			ret = cmd_q->ccp->vdata->perक्रमm->aes(&op);
			अगर (ret) अणु
				cmd->engine_error = cmd_q->cmd_error;
				जाओ e_aad;
			पूर्ण

			ccp_process_data(&aad, शून्य, &op);
			op.init = 0;
		पूर्ण
	पूर्ण

	op.u.aes.mode = CCP_AES_MODE_GCTR;
	op.u.aes.action = aes->action;

	अगर (ilen > 0) अणु
		/* Step 2: Run a GCTR over the plaपूर्णांकext */
		in_place = (sg_virt(p_inp) == sg_virt(p_outp)) ? true : false;

		ret = ccp_init_data(&src, cmd_q, p_inp, ilen,
				    AES_BLOCK_SIZE,
				    in_place ? DMA_BIसूचीECTIONAL
					     : DMA_TO_DEVICE);
		अगर (ret)
			जाओ e_ctx;

		अगर (in_place) अणु
			dst = src;
		पूर्ण अन्यथा अणु
			ret = ccp_init_data(&dst, cmd_q, p_outp, ilen,
					    AES_BLOCK_SIZE, DMA_FROM_DEVICE);
			अगर (ret)
				जाओ e_src;
		पूर्ण

		op.soc = 0;
		op.eom = 0;
		op.init = 1;
		जबतक (src.sg_wa.bytes_left) अणु
			ccp_prepare_data(&src, &dst, &op, AES_BLOCK_SIZE, true);
			अगर (!src.sg_wa.bytes_left) अणु
				अचिन्हित पूर्णांक nbytes = ilen % AES_BLOCK_SIZE;

				अगर (nbytes) अणु
					op.eom = 1;
					op.u.aes.size = (nbytes * 8) - 1;
				पूर्ण
			पूर्ण

			ret = cmd_q->ccp->vdata->perक्रमm->aes(&op);
			अगर (ret) अणु
				cmd->engine_error = cmd_q->cmd_error;
				जाओ e_dst;
			पूर्ण

			ccp_process_data(&src, &dst, &op);
			op.init = 0;
		पूर्ण
	पूर्ण

	/* Step 3: Update the IV portion of the context with the original IV */
	ret = ccp_copy_from_sb(cmd_q, &ctx, op.jobid, op.sb_ctx,
			       CCP_PASSTHRU_BYTESWAP_256BIT);
	अगर (ret) अणु
		cmd->engine_error = cmd_q->cmd_error;
		जाओ e_dst;
	पूर्ण

	ret = ccp_set_dm_area(&ctx, dm_offset, aes->iv, 0, aes->iv_len);
	अगर (ret)
		जाओ e_dst;

	ret = ccp_copy_to_sb(cmd_q, &ctx, op.jobid, op.sb_ctx,
			     CCP_PASSTHRU_BYTESWAP_256BIT);
	अगर (ret) अणु
		cmd->engine_error = cmd_q->cmd_error;
		जाओ e_dst;
	पूर्ण

	/* Step 4: Concatenate the lengths of the AAD and source, and
	 * hash that 16 byte buffer.
	 */
	ret = ccp_init_dm_workarea(&final_wa, cmd_q, AES_BLOCK_SIZE,
				   DMA_BIसूचीECTIONAL);
	अगर (ret)
		जाओ e_dst;
	final = (__be64 *)final_wa.address;
	final[0] = cpu_to_be64(aes->aad_len * 8);
	final[1] = cpu_to_be64(ilen * 8);

	स_रखो(&op, 0, माप(op));
	op.cmd_q = cmd_q;
	op.jobid = jobid;
	op.sb_key = cmd_q->sb_key; /* Pre-allocated */
	op.sb_ctx = cmd_q->sb_ctx; /* Pre-allocated */
	op.init = 1;
	op.u.aes.type = aes->type;
	op.u.aes.mode = CCP_AES_MODE_GHASH;
	op.u.aes.action = CCP_AES_GHASHFINAL;
	op.src.type = CCP_MEMTYPE_SYSTEM;
	op.src.u.dma.address = final_wa.dma.address;
	op.src.u.dma.length = AES_BLOCK_SIZE;
	op.dst.type = CCP_MEMTYPE_SYSTEM;
	op.dst.u.dma.address = final_wa.dma.address;
	op.dst.u.dma.length = AES_BLOCK_SIZE;
	op.eom = 1;
	op.u.aes.size = 0;
	ret = cmd_q->ccp->vdata->perक्रमm->aes(&op);
	अगर (ret)
		जाओ e_dst;

	अगर (aes->action == CCP_AES_ACTION_ENCRYPT) अणु
		/* Put the ciphered tag after the ciphertext. */
		ccp_get_dm_area(&final_wa, 0, p_tag, 0, authsize);
	पूर्ण अन्यथा अणु
		/* Does this ciphered tag match the input? */
		ret = ccp_init_dm_workarea(&tag, cmd_q, authsize,
					   DMA_BIसूचीECTIONAL);
		अगर (ret)
			जाओ e_tag;
		ret = ccp_set_dm_area(&tag, 0, p_tag, 0, authsize);
		अगर (ret)
			जाओ e_tag;

		ret = crypto_memneq(tag.address, final_wa.address,
				    authsize) ? -EBADMSG : 0;
		ccp_dm_मुक्त(&tag);
	पूर्ण

e_tag:
	ccp_dm_मुक्त(&final_wa);

e_dst:
	अगर (ilen > 0 && !in_place)
		ccp_मुक्त_data(&dst, cmd_q);

e_src:
	अगर (ilen > 0)
		ccp_मुक्त_data(&src, cmd_q);

e_aad:
	अगर (aes->aad_len)
		ccp_मुक्त_data(&aad, cmd_q);

e_ctx:
	ccp_dm_मुक्त(&ctx);

e_key:
	ccp_dm_मुक्त(&key);

	वापस ret;
पूर्ण

अटल noअंतरभूत_क्रम_stack पूर्णांक
ccp_run_aes_cmd(काष्ठा ccp_cmd_queue *cmd_q, काष्ठा ccp_cmd *cmd)
अणु
	काष्ठा ccp_aes_engine *aes = &cmd->u.aes;
	काष्ठा ccp_dm_workarea key, ctx;
	काष्ठा ccp_data src, dst;
	काष्ठा ccp_op op;
	अचिन्हित पूर्णांक dm_offset;
	bool in_place = false;
	पूर्णांक ret;

	अगर (!((aes->key_len == AES_KEYSIZE_128) ||
	      (aes->key_len == AES_KEYSIZE_192) ||
	      (aes->key_len == AES_KEYSIZE_256)))
		वापस -EINVAL;

	अगर (((aes->mode == CCP_AES_MODE_ECB) ||
	     (aes->mode == CCP_AES_MODE_CBC)) &&
	    (aes->src_len & (AES_BLOCK_SIZE - 1)))
		वापस -EINVAL;

	अगर (!aes->key || !aes->src || !aes->dst)
		वापस -EINVAL;

	अगर (aes->mode != CCP_AES_MODE_ECB) अणु
		अगर (aes->iv_len != AES_BLOCK_SIZE)
			वापस -EINVAL;

		अगर (!aes->iv)
			वापस -EINVAL;
	पूर्ण

	BUILD_BUG_ON(CCP_AES_KEY_SB_COUNT != 1);
	BUILD_BUG_ON(CCP_AES_CTX_SB_COUNT != 1);

	ret = -EIO;
	स_रखो(&op, 0, माप(op));
	op.cmd_q = cmd_q;
	op.jobid = CCP_NEW_JOBID(cmd_q->ccp);
	op.sb_key = cmd_q->sb_key;
	op.sb_ctx = cmd_q->sb_ctx;
	op.init = (aes->mode == CCP_AES_MODE_ECB) ? 0 : 1;
	op.u.aes.type = aes->type;
	op.u.aes.mode = aes->mode;
	op.u.aes.action = aes->action;

	/* All supported key sizes fit in a single (32-byte) SB entry
	 * and must be in little endian क्रमmat. Use the 256-bit byte
	 * swap passthru option to convert from big endian to little
	 * endian.
	 */
	ret = ccp_init_dm_workarea(&key, cmd_q,
				   CCP_AES_KEY_SB_COUNT * CCP_SB_BYTES,
				   DMA_TO_DEVICE);
	अगर (ret)
		वापस ret;

	dm_offset = CCP_SB_BYTES - aes->key_len;
	ret = ccp_set_dm_area(&key, dm_offset, aes->key, 0, aes->key_len);
	अगर (ret)
		जाओ e_key;
	ret = ccp_copy_to_sb(cmd_q, &key, op.jobid, op.sb_key,
			     CCP_PASSTHRU_BYTESWAP_256BIT);
	अगर (ret) अणु
		cmd->engine_error = cmd_q->cmd_error;
		जाओ e_key;
	पूर्ण

	/* The AES context fits in a single (32-byte) SB entry and
	 * must be in little endian क्रमmat. Use the 256-bit byte swap
	 * passthru option to convert from big endian to little endian.
	 */
	ret = ccp_init_dm_workarea(&ctx, cmd_q,
				   CCP_AES_CTX_SB_COUNT * CCP_SB_BYTES,
				   DMA_BIसूचीECTIONAL);
	अगर (ret)
		जाओ e_key;

	अगर (aes->mode != CCP_AES_MODE_ECB) अणु
		/* Load the AES context - convert to LE */
		dm_offset = CCP_SB_BYTES - AES_BLOCK_SIZE;
		ret = ccp_set_dm_area(&ctx, dm_offset, aes->iv, 0, aes->iv_len);
		अगर (ret)
			जाओ e_ctx;
		ret = ccp_copy_to_sb(cmd_q, &ctx, op.jobid, op.sb_ctx,
				     CCP_PASSTHRU_BYTESWAP_256BIT);
		अगर (ret) अणु
			cmd->engine_error = cmd_q->cmd_error;
			जाओ e_ctx;
		पूर्ण
	पूर्ण
	चयन (aes->mode) अणु
	हाल CCP_AES_MODE_CFB: /* CFB128 only */
	हाल CCP_AES_MODE_CTR:
		op.u.aes.size = AES_BLOCK_SIZE * BITS_PER_BYTE - 1;
		अवरोध;
	शेष:
		op.u.aes.size = 0;
	पूर्ण

	/* Prepare the input and output data workareas. For in-place
	 * operations we need to set the dma direction to BIसूचीECTIONAL
	 * and copy the src workarea to the dst workarea.
	 */
	अगर (sg_virt(aes->src) == sg_virt(aes->dst))
		in_place = true;

	ret = ccp_init_data(&src, cmd_q, aes->src, aes->src_len,
			    AES_BLOCK_SIZE,
			    in_place ? DMA_BIसूचीECTIONAL : DMA_TO_DEVICE);
	अगर (ret)
		जाओ e_ctx;

	अगर (in_place) अणु
		dst = src;
	पूर्ण अन्यथा अणु
		ret = ccp_init_data(&dst, cmd_q, aes->dst, aes->src_len,
				    AES_BLOCK_SIZE, DMA_FROM_DEVICE);
		अगर (ret)
			जाओ e_src;
	पूर्ण

	/* Send data to the CCP AES engine */
	जबतक (src.sg_wa.bytes_left) अणु
		ccp_prepare_data(&src, &dst, &op, AES_BLOCK_SIZE, true);
		अगर (!src.sg_wa.bytes_left) अणु
			op.eom = 1;

			/* Since we करोn't retrieve the AES context in ECB
			 * mode we have to रुको क्रम the operation to complete
			 * on the last piece of data
			 */
			अगर (aes->mode == CCP_AES_MODE_ECB)
				op.soc = 1;
		पूर्ण

		ret = cmd_q->ccp->vdata->perक्रमm->aes(&op);
		अगर (ret) अणु
			cmd->engine_error = cmd_q->cmd_error;
			जाओ e_dst;
		पूर्ण

		ccp_process_data(&src, &dst, &op);
	पूर्ण

	अगर (aes->mode != CCP_AES_MODE_ECB) अणु
		/* Retrieve the AES context - convert from LE to BE using
		 * 32-byte (256-bit) byteswapping
		 */
		ret = ccp_copy_from_sb(cmd_q, &ctx, op.jobid, op.sb_ctx,
				       CCP_PASSTHRU_BYTESWAP_256BIT);
		अगर (ret) अणु
			cmd->engine_error = cmd_q->cmd_error;
			जाओ e_dst;
		पूर्ण

		/* ...but we only need AES_BLOCK_SIZE bytes */
		dm_offset = CCP_SB_BYTES - AES_BLOCK_SIZE;
		ccp_get_dm_area(&ctx, dm_offset, aes->iv, 0, aes->iv_len);
	पूर्ण

e_dst:
	अगर (!in_place)
		ccp_मुक्त_data(&dst, cmd_q);

e_src:
	ccp_मुक्त_data(&src, cmd_q);

e_ctx:
	ccp_dm_मुक्त(&ctx);

e_key:
	ccp_dm_मुक्त(&key);

	वापस ret;
पूर्ण

अटल noअंतरभूत_क्रम_stack पूर्णांक
ccp_run_xts_aes_cmd(काष्ठा ccp_cmd_queue *cmd_q, काष्ठा ccp_cmd *cmd)
अणु
	काष्ठा ccp_xts_aes_engine *xts = &cmd->u.xts;
	काष्ठा ccp_dm_workarea key, ctx;
	काष्ठा ccp_data src, dst;
	काष्ठा ccp_op op;
	अचिन्हित पूर्णांक unit_size, dm_offset;
	bool in_place = false;
	अचिन्हित पूर्णांक sb_count;
	क्रमागत ccp_aes_type aestype;
	पूर्णांक ret;

	चयन (xts->unit_size) अणु
	हाल CCP_XTS_AES_UNIT_SIZE_16:
		unit_size = 16;
		अवरोध;
	हाल CCP_XTS_AES_UNIT_SIZE_512:
		unit_size = 512;
		अवरोध;
	हाल CCP_XTS_AES_UNIT_SIZE_1024:
		unit_size = 1024;
		अवरोध;
	हाल CCP_XTS_AES_UNIT_SIZE_2048:
		unit_size = 2048;
		अवरोध;
	हाल CCP_XTS_AES_UNIT_SIZE_4096:
		unit_size = 4096;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (xts->key_len == AES_KEYSIZE_128)
		aestype = CCP_AES_TYPE_128;
	अन्यथा अगर (xts->key_len == AES_KEYSIZE_256)
		aestype = CCP_AES_TYPE_256;
	अन्यथा
		वापस -EINVAL;

	अगर (!xts->final && (xts->src_len & (AES_BLOCK_SIZE - 1)))
		वापस -EINVAL;

	अगर (xts->iv_len != AES_BLOCK_SIZE)
		वापस -EINVAL;

	अगर (!xts->key || !xts->iv || !xts->src || !xts->dst)
		वापस -EINVAL;

	BUILD_BUG_ON(CCP_XTS_AES_KEY_SB_COUNT != 1);
	BUILD_BUG_ON(CCP_XTS_AES_CTX_SB_COUNT != 1);

	ret = -EIO;
	स_रखो(&op, 0, माप(op));
	op.cmd_q = cmd_q;
	op.jobid = CCP_NEW_JOBID(cmd_q->ccp);
	op.sb_key = cmd_q->sb_key;
	op.sb_ctx = cmd_q->sb_ctx;
	op.init = 1;
	op.u.xts.type = aestype;
	op.u.xts.action = xts->action;
	op.u.xts.unit_size = xts->unit_size;

	/* A version 3 device only supports 128-bit keys, which fits पूर्णांकo a
	 * single SB entry. A version 5 device uses a 512-bit vector, so two
	 * SB entries.
	 */
	अगर (cmd_q->ccp->vdata->version == CCP_VERSION(3, 0))
		sb_count = CCP_XTS_AES_KEY_SB_COUNT;
	अन्यथा
		sb_count = CCP5_XTS_AES_KEY_SB_COUNT;
	ret = ccp_init_dm_workarea(&key, cmd_q,
				   sb_count * CCP_SB_BYTES,
				   DMA_TO_DEVICE);
	अगर (ret)
		वापस ret;

	अगर (cmd_q->ccp->vdata->version == CCP_VERSION(3, 0)) अणु
		/* All supported key sizes must be in little endian क्रमmat.
		 * Use the 256-bit byte swap passthru option to convert from
		 * big endian to little endian.
		 */
		dm_offset = CCP_SB_BYTES - AES_KEYSIZE_128;
		ret = ccp_set_dm_area(&key, dm_offset, xts->key, 0, xts->key_len);
		अगर (ret)
			जाओ e_key;
		ret = ccp_set_dm_area(&key, 0, xts->key, xts->key_len, xts->key_len);
		अगर (ret)
			जाओ e_key;
	पूर्ण अन्यथा अणु
		/* Version 5 CCPs use a 512-bit space क्रम the key: each portion
		 * occupies 256 bits, or one entire slot, and is zero-padded.
		 */
		अचिन्हित पूर्णांक pad;

		dm_offset = CCP_SB_BYTES;
		pad = dm_offset - xts->key_len;
		ret = ccp_set_dm_area(&key, pad, xts->key, 0, xts->key_len);
		अगर (ret)
			जाओ e_key;
		ret = ccp_set_dm_area(&key, dm_offset + pad, xts->key,
				      xts->key_len, xts->key_len);
		अगर (ret)
			जाओ e_key;
	पूर्ण
	ret = ccp_copy_to_sb(cmd_q, &key, op.jobid, op.sb_key,
			     CCP_PASSTHRU_BYTESWAP_256BIT);
	अगर (ret) अणु
		cmd->engine_error = cmd_q->cmd_error;
		जाओ e_key;
	पूर्ण

	/* The AES context fits in a single (32-byte) SB entry and
	 * क्रम XTS is alपढ़ोy in little endian क्रमmat so no byte swapping
	 * is needed.
	 */
	ret = ccp_init_dm_workarea(&ctx, cmd_q,
				   CCP_XTS_AES_CTX_SB_COUNT * CCP_SB_BYTES,
				   DMA_BIसूचीECTIONAL);
	अगर (ret)
		जाओ e_key;

	ret = ccp_set_dm_area(&ctx, 0, xts->iv, 0, xts->iv_len);
	अगर (ret)
		जाओ e_ctx;
	ret = ccp_copy_to_sb(cmd_q, &ctx, op.jobid, op.sb_ctx,
			     CCP_PASSTHRU_BYTESWAP_NOOP);
	अगर (ret) अणु
		cmd->engine_error = cmd_q->cmd_error;
		जाओ e_ctx;
	पूर्ण

	/* Prepare the input and output data workareas. For in-place
	 * operations we need to set the dma direction to BIसूचीECTIONAL
	 * and copy the src workarea to the dst workarea.
	 */
	अगर (sg_virt(xts->src) == sg_virt(xts->dst))
		in_place = true;

	ret = ccp_init_data(&src, cmd_q, xts->src, xts->src_len,
			    unit_size,
			    in_place ? DMA_BIसूचीECTIONAL : DMA_TO_DEVICE);
	अगर (ret)
		जाओ e_ctx;

	अगर (in_place) अणु
		dst = src;
	पूर्ण अन्यथा अणु
		ret = ccp_init_data(&dst, cmd_q, xts->dst, xts->src_len,
				    unit_size, DMA_FROM_DEVICE);
		अगर (ret)
			जाओ e_src;
	पूर्ण

	/* Send data to the CCP AES engine */
	जबतक (src.sg_wa.bytes_left) अणु
		ccp_prepare_data(&src, &dst, &op, unit_size, true);
		अगर (!src.sg_wa.bytes_left)
			op.eom = 1;

		ret = cmd_q->ccp->vdata->perक्रमm->xts_aes(&op);
		अगर (ret) अणु
			cmd->engine_error = cmd_q->cmd_error;
			जाओ e_dst;
		पूर्ण

		ccp_process_data(&src, &dst, &op);
	पूर्ण

	/* Retrieve the AES context - convert from LE to BE using
	 * 32-byte (256-bit) byteswapping
	 */
	ret = ccp_copy_from_sb(cmd_q, &ctx, op.jobid, op.sb_ctx,
			       CCP_PASSTHRU_BYTESWAP_256BIT);
	अगर (ret) अणु
		cmd->engine_error = cmd_q->cmd_error;
		जाओ e_dst;
	पूर्ण

	/* ...but we only need AES_BLOCK_SIZE bytes */
	dm_offset = CCP_SB_BYTES - AES_BLOCK_SIZE;
	ccp_get_dm_area(&ctx, dm_offset, xts->iv, 0, xts->iv_len);

e_dst:
	अगर (!in_place)
		ccp_मुक्त_data(&dst, cmd_q);

e_src:
	ccp_मुक्त_data(&src, cmd_q);

e_ctx:
	ccp_dm_मुक्त(&ctx);

e_key:
	ccp_dm_मुक्त(&key);

	वापस ret;
पूर्ण

अटल noअंतरभूत_क्रम_stack पूर्णांक
ccp_run_des3_cmd(काष्ठा ccp_cmd_queue *cmd_q, काष्ठा ccp_cmd *cmd)
अणु
	काष्ठा ccp_des3_engine *des3 = &cmd->u.des3;

	काष्ठा ccp_dm_workarea key, ctx;
	काष्ठा ccp_data src, dst;
	काष्ठा ccp_op op;
	अचिन्हित पूर्णांक dm_offset;
	अचिन्हित पूर्णांक len_singlekey;
	bool in_place = false;
	पूर्णांक ret;

	/* Error checks */
	अगर (cmd_q->ccp->vdata->version < CCP_VERSION(5, 0))
		वापस -EINVAL;

	अगर (!cmd_q->ccp->vdata->perक्रमm->des3)
		वापस -EINVAL;

	अगर (des3->key_len != DES3_EDE_KEY_SIZE)
		वापस -EINVAL;

	अगर (((des3->mode == CCP_DES3_MODE_ECB) ||
		(des3->mode == CCP_DES3_MODE_CBC)) &&
		(des3->src_len & (DES3_EDE_BLOCK_SIZE - 1)))
		वापस -EINVAL;

	अगर (!des3->key || !des3->src || !des3->dst)
		वापस -EINVAL;

	अगर (des3->mode != CCP_DES3_MODE_ECB) अणु
		अगर (des3->iv_len != DES3_EDE_BLOCK_SIZE)
			वापस -EINVAL;

		अगर (!des3->iv)
			वापस -EINVAL;
	पूर्ण

	/* Zero out all the fields of the command desc */
	स_रखो(&op, 0, माप(op));

	/* Set up the Function field */
	op.cmd_q = cmd_q;
	op.jobid = CCP_NEW_JOBID(cmd_q->ccp);
	op.sb_key = cmd_q->sb_key;

	op.init = (des3->mode == CCP_DES3_MODE_ECB) ? 0 : 1;
	op.u.des3.type = des3->type;
	op.u.des3.mode = des3->mode;
	op.u.des3.action = des3->action;

	/*
	 * All supported key sizes fit in a single (32-byte) KSB entry and
	 * (like AES) must be in little endian क्रमmat. Use the 256-bit byte
	 * swap passthru option to convert from big endian to little endian.
	 */
	ret = ccp_init_dm_workarea(&key, cmd_q,
				   CCP_DES3_KEY_SB_COUNT * CCP_SB_BYTES,
				   DMA_TO_DEVICE);
	अगर (ret)
		वापस ret;

	/*
	 * The contents of the key triplet are in the reverse order of what
	 * is required by the engine. Copy the 3 pieces inभागidually to put
	 * them where they beदीर्घ.
	 */
	dm_offset = CCP_SB_BYTES - des3->key_len; /* Basic offset */

	len_singlekey = des3->key_len / 3;
	ret = ccp_set_dm_area(&key, dm_offset + 2 * len_singlekey,
			      des3->key, 0, len_singlekey);
	अगर (ret)
		जाओ e_key;
	ret = ccp_set_dm_area(&key, dm_offset + len_singlekey,
			      des3->key, len_singlekey, len_singlekey);
	अगर (ret)
		जाओ e_key;
	ret = ccp_set_dm_area(&key, dm_offset,
			      des3->key, 2 * len_singlekey, len_singlekey);
	अगर (ret)
		जाओ e_key;

	/* Copy the key to the SB */
	ret = ccp_copy_to_sb(cmd_q, &key, op.jobid, op.sb_key,
			     CCP_PASSTHRU_BYTESWAP_256BIT);
	अगर (ret) अणु
		cmd->engine_error = cmd_q->cmd_error;
		जाओ e_key;
	पूर्ण

	/*
	 * The DES3 context fits in a single (32-byte) KSB entry and
	 * must be in little endian क्रमmat. Use the 256-bit byte swap
	 * passthru option to convert from big endian to little endian.
	 */
	अगर (des3->mode != CCP_DES3_MODE_ECB) अणु
		op.sb_ctx = cmd_q->sb_ctx;

		ret = ccp_init_dm_workarea(&ctx, cmd_q,
					   CCP_DES3_CTX_SB_COUNT * CCP_SB_BYTES,
					   DMA_BIसूचीECTIONAL);
		अगर (ret)
			जाओ e_key;

		/* Load the context पूर्णांकo the LSB */
		dm_offset = CCP_SB_BYTES - des3->iv_len;
		ret = ccp_set_dm_area(&ctx, dm_offset, des3->iv, 0,
				      des3->iv_len);
		अगर (ret)
			जाओ e_ctx;

		ret = ccp_copy_to_sb(cmd_q, &ctx, op.jobid, op.sb_ctx,
				     CCP_PASSTHRU_BYTESWAP_256BIT);
		अगर (ret) अणु
			cmd->engine_error = cmd_q->cmd_error;
			जाओ e_ctx;
		पूर्ण
	पूर्ण

	/*
	 * Prepare the input and output data workareas. For in-place
	 * operations we need to set the dma direction to BIसूचीECTIONAL
	 * and copy the src workarea to the dst workarea.
	 */
	अगर (sg_virt(des3->src) == sg_virt(des3->dst))
		in_place = true;

	ret = ccp_init_data(&src, cmd_q, des3->src, des3->src_len,
			DES3_EDE_BLOCK_SIZE,
			in_place ? DMA_BIसूचीECTIONAL : DMA_TO_DEVICE);
	अगर (ret)
		जाओ e_ctx;

	अगर (in_place)
		dst = src;
	अन्यथा अणु
		ret = ccp_init_data(&dst, cmd_q, des3->dst, des3->src_len,
				DES3_EDE_BLOCK_SIZE, DMA_FROM_DEVICE);
		अगर (ret)
			जाओ e_src;
	पूर्ण

	/* Send data to the CCP DES3 engine */
	जबतक (src.sg_wa.bytes_left) अणु
		ccp_prepare_data(&src, &dst, &op, DES3_EDE_BLOCK_SIZE, true);
		अगर (!src.sg_wa.bytes_left) अणु
			op.eom = 1;

			/* Since we करोn't retrieve the context in ECB mode
			 * we have to रुको क्रम the operation to complete
			 * on the last piece of data
			 */
			op.soc = 0;
		पूर्ण

		ret = cmd_q->ccp->vdata->perक्रमm->des3(&op);
		अगर (ret) अणु
			cmd->engine_error = cmd_q->cmd_error;
			जाओ e_dst;
		पूर्ण

		ccp_process_data(&src, &dst, &op);
	पूर्ण

	अगर (des3->mode != CCP_DES3_MODE_ECB) अणु
		/* Retrieve the context and make BE */
		ret = ccp_copy_from_sb(cmd_q, &ctx, op.jobid, op.sb_ctx,
				       CCP_PASSTHRU_BYTESWAP_256BIT);
		अगर (ret) अणु
			cmd->engine_error = cmd_q->cmd_error;
			जाओ e_dst;
		पूर्ण

		/* ...but we only need the last DES3_EDE_BLOCK_SIZE bytes */
		ccp_get_dm_area(&ctx, dm_offset, des3->iv, 0,
				DES3_EDE_BLOCK_SIZE);
	पूर्ण
e_dst:
	अगर (!in_place)
		ccp_मुक्त_data(&dst, cmd_q);

e_src:
	ccp_मुक्त_data(&src, cmd_q);

e_ctx:
	अगर (des3->mode != CCP_DES3_MODE_ECB)
		ccp_dm_मुक्त(&ctx);

e_key:
	ccp_dm_मुक्त(&key);

	वापस ret;
पूर्ण

अटल noअंतरभूत_क्रम_stack पूर्णांक
ccp_run_sha_cmd(काष्ठा ccp_cmd_queue *cmd_q, काष्ठा ccp_cmd *cmd)
अणु
	काष्ठा ccp_sha_engine *sha = &cmd->u.sha;
	काष्ठा ccp_dm_workarea ctx;
	काष्ठा ccp_data src;
	काष्ठा ccp_op op;
	अचिन्हित पूर्णांक ioffset, ooffset;
	अचिन्हित पूर्णांक digest_size;
	पूर्णांक sb_count;
	स्थिर व्योम *init;
	u64 block_size;
	पूर्णांक ctx_size;
	पूर्णांक ret;

	चयन (sha->type) अणु
	हाल CCP_SHA_TYPE_1:
		अगर (sha->ctx_len < SHA1_DIGEST_SIZE)
			वापस -EINVAL;
		block_size = SHA1_BLOCK_SIZE;
		अवरोध;
	हाल CCP_SHA_TYPE_224:
		अगर (sha->ctx_len < SHA224_DIGEST_SIZE)
			वापस -EINVAL;
		block_size = SHA224_BLOCK_SIZE;
		अवरोध;
	हाल CCP_SHA_TYPE_256:
		अगर (sha->ctx_len < SHA256_DIGEST_SIZE)
			वापस -EINVAL;
		block_size = SHA256_BLOCK_SIZE;
		अवरोध;
	हाल CCP_SHA_TYPE_384:
		अगर (cmd_q->ccp->vdata->version < CCP_VERSION(4, 0)
		    || sha->ctx_len < SHA384_DIGEST_SIZE)
			वापस -EINVAL;
		block_size = SHA384_BLOCK_SIZE;
		अवरोध;
	हाल CCP_SHA_TYPE_512:
		अगर (cmd_q->ccp->vdata->version < CCP_VERSION(4, 0)
		    || sha->ctx_len < SHA512_DIGEST_SIZE)
			वापस -EINVAL;
		block_size = SHA512_BLOCK_SIZE;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (!sha->ctx)
		वापस -EINVAL;

	अगर (!sha->final && (sha->src_len & (block_size - 1)))
		वापस -EINVAL;

	/* The version 3 device can't handle zero-length input */
	अगर (cmd_q->ccp->vdata->version == CCP_VERSION(3, 0)) अणु

		अगर (!sha->src_len) अणु
			अचिन्हित पूर्णांक digest_len;
			स्थिर u8 *sha_zero;

			/* Not final, just वापस */
			अगर (!sha->final)
				वापस 0;

			/* CCP can't करो a zero length sha operation so the
			 * caller must buffer the data.
			 */
			अगर (sha->msg_bits)
				वापस -EINVAL;

			/* The CCP cannot perक्रमm zero-length sha operations
			 * so the caller is required to buffer data क्रम the
			 * final operation. However, a sha operation क्रम a
			 * message with a total length of zero is valid so
			 * known values are required to supply the result.
			 */
			चयन (sha->type) अणु
			हाल CCP_SHA_TYPE_1:
				sha_zero = sha1_zero_message_hash;
				digest_len = SHA1_DIGEST_SIZE;
				अवरोध;
			हाल CCP_SHA_TYPE_224:
				sha_zero = sha224_zero_message_hash;
				digest_len = SHA224_DIGEST_SIZE;
				अवरोध;
			हाल CCP_SHA_TYPE_256:
				sha_zero = sha256_zero_message_hash;
				digest_len = SHA256_DIGEST_SIZE;
				अवरोध;
			शेष:
				वापस -EINVAL;
			पूर्ण

			scatterwalk_map_and_copy((व्योम *)sha_zero, sha->ctx, 0,
						 digest_len, 1);

			वापस 0;
		पूर्ण
	पूर्ण

	/* Set variables used throughout */
	चयन (sha->type) अणु
	हाल CCP_SHA_TYPE_1:
		digest_size = SHA1_DIGEST_SIZE;
		init = (व्योम *) ccp_sha1_init;
		ctx_size = SHA1_DIGEST_SIZE;
		sb_count = 1;
		अगर (cmd_q->ccp->vdata->version != CCP_VERSION(3, 0))
			ooffset = ioffset = CCP_SB_BYTES - SHA1_DIGEST_SIZE;
		अन्यथा
			ooffset = ioffset = 0;
		अवरोध;
	हाल CCP_SHA_TYPE_224:
		digest_size = SHA224_DIGEST_SIZE;
		init = (व्योम *) ccp_sha224_init;
		ctx_size = SHA256_DIGEST_SIZE;
		sb_count = 1;
		ioffset = 0;
		अगर (cmd_q->ccp->vdata->version != CCP_VERSION(3, 0))
			ooffset = CCP_SB_BYTES - SHA224_DIGEST_SIZE;
		अन्यथा
			ooffset = 0;
		अवरोध;
	हाल CCP_SHA_TYPE_256:
		digest_size = SHA256_DIGEST_SIZE;
		init = (व्योम *) ccp_sha256_init;
		ctx_size = SHA256_DIGEST_SIZE;
		sb_count = 1;
		ooffset = ioffset = 0;
		अवरोध;
	हाल CCP_SHA_TYPE_384:
		digest_size = SHA384_DIGEST_SIZE;
		init = (व्योम *) ccp_sha384_init;
		ctx_size = SHA512_DIGEST_SIZE;
		sb_count = 2;
		ioffset = 0;
		ooffset = 2 * CCP_SB_BYTES - SHA384_DIGEST_SIZE;
		अवरोध;
	हाल CCP_SHA_TYPE_512:
		digest_size = SHA512_DIGEST_SIZE;
		init = (व्योम *) ccp_sha512_init;
		ctx_size = SHA512_DIGEST_SIZE;
		sb_count = 2;
		ooffset = ioffset = 0;
		अवरोध;
	शेष:
		ret = -EINVAL;
		जाओ e_data;
	पूर्ण

	/* For zero-length plaपूर्णांकext the src poपूर्णांकer is ignored;
	 * otherwise both parts must be valid
	 */
	अगर (sha->src_len && !sha->src)
		वापस -EINVAL;

	स_रखो(&op, 0, माप(op));
	op.cmd_q = cmd_q;
	op.jobid = CCP_NEW_JOBID(cmd_q->ccp);
	op.sb_ctx = cmd_q->sb_ctx; /* Pre-allocated */
	op.u.sha.type = sha->type;
	op.u.sha.msg_bits = sha->msg_bits;

	/* For SHA1/224/256 the context fits in a single (32-byte) SB entry;
	 * SHA384/512 require 2 adjacent SB slots, with the right half in the
	 * first slot, and the left half in the second. Each portion must then
	 * be in little endian क्रमmat: use the 256-bit byte swap option.
	 */
	ret = ccp_init_dm_workarea(&ctx, cmd_q, sb_count * CCP_SB_BYTES,
				   DMA_BIसूचीECTIONAL);
	अगर (ret)
		वापस ret;
	अगर (sha->first) अणु
		चयन (sha->type) अणु
		हाल CCP_SHA_TYPE_1:
		हाल CCP_SHA_TYPE_224:
		हाल CCP_SHA_TYPE_256:
			स_नकल(ctx.address + ioffset, init, ctx_size);
			अवरोध;
		हाल CCP_SHA_TYPE_384:
		हाल CCP_SHA_TYPE_512:
			स_नकल(ctx.address + ctx_size / 2, init,
			       ctx_size / 2);
			स_नकल(ctx.address, init + ctx_size / 2,
			       ctx_size / 2);
			अवरोध;
		शेष:
			ret = -EINVAL;
			जाओ e_ctx;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Restore the context */
		ret = ccp_set_dm_area(&ctx, 0, sha->ctx, 0,
				      sb_count * CCP_SB_BYTES);
		अगर (ret)
			जाओ e_ctx;
	पूर्ण

	ret = ccp_copy_to_sb(cmd_q, &ctx, op.jobid, op.sb_ctx,
			     CCP_PASSTHRU_BYTESWAP_256BIT);
	अगर (ret) अणु
		cmd->engine_error = cmd_q->cmd_error;
		जाओ e_ctx;
	पूर्ण

	अगर (sha->src) अणु
		/* Send data to the CCP SHA engine; block_size is set above */
		ret = ccp_init_data(&src, cmd_q, sha->src, sha->src_len,
				    block_size, DMA_TO_DEVICE);
		अगर (ret)
			जाओ e_ctx;

		जबतक (src.sg_wa.bytes_left) अणु
			ccp_prepare_data(&src, शून्य, &op, block_size, false);
			अगर (sha->final && !src.sg_wa.bytes_left)
				op.eom = 1;

			ret = cmd_q->ccp->vdata->perक्रमm->sha(&op);
			अगर (ret) अणु
				cmd->engine_error = cmd_q->cmd_error;
				जाओ e_data;
			पूर्ण

			ccp_process_data(&src, शून्य, &op);
		पूर्ण
	पूर्ण अन्यथा अणु
		op.eom = 1;
		ret = cmd_q->ccp->vdata->perक्रमm->sha(&op);
		अगर (ret) अणु
			cmd->engine_error = cmd_q->cmd_error;
			जाओ e_data;
		पूर्ण
	पूर्ण

	/* Retrieve the SHA context - convert from LE to BE using
	 * 32-byte (256-bit) byteswapping to BE
	 */
	ret = ccp_copy_from_sb(cmd_q, &ctx, op.jobid, op.sb_ctx,
			       CCP_PASSTHRU_BYTESWAP_256BIT);
	अगर (ret) अणु
		cmd->engine_error = cmd_q->cmd_error;
		जाओ e_data;
	पूर्ण

	अगर (sha->final) अणु
		/* Finishing up, so get the digest */
		चयन (sha->type) अणु
		हाल CCP_SHA_TYPE_1:
		हाल CCP_SHA_TYPE_224:
		हाल CCP_SHA_TYPE_256:
			ccp_get_dm_area(&ctx, ooffset,
					sha->ctx, 0,
					digest_size);
			अवरोध;
		हाल CCP_SHA_TYPE_384:
		हाल CCP_SHA_TYPE_512:
			ccp_get_dm_area(&ctx, 0,
					sha->ctx, LSB_ITEM_SIZE - ooffset,
					LSB_ITEM_SIZE);
			ccp_get_dm_area(&ctx, LSB_ITEM_SIZE + ooffset,
					sha->ctx, 0,
					LSB_ITEM_SIZE - ooffset);
			अवरोध;
		शेष:
			ret = -EINVAL;
			जाओ e_data;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Stash the context */
		ccp_get_dm_area(&ctx, 0, sha->ctx, 0,
				sb_count * CCP_SB_BYTES);
	पूर्ण

	अगर (sha->final && sha->opad) अणु
		/* HMAC operation, recursively perक्रमm final SHA */
		काष्ठा ccp_cmd hmac_cmd;
		काष्ठा scatterlist sg;
		u8 *hmac_buf;

		अगर (sha->opad_len != block_size) अणु
			ret = -EINVAL;
			जाओ e_data;
		पूर्ण

		hmac_buf = kदो_स्मृति(block_size + digest_size, GFP_KERNEL);
		अगर (!hmac_buf) अणु
			ret = -ENOMEM;
			जाओ e_data;
		पूर्ण
		sg_init_one(&sg, hmac_buf, block_size + digest_size);

		scatterwalk_map_and_copy(hmac_buf, sha->opad, 0, block_size, 0);
		चयन (sha->type) अणु
		हाल CCP_SHA_TYPE_1:
		हाल CCP_SHA_TYPE_224:
		हाल CCP_SHA_TYPE_256:
			स_नकल(hmac_buf + block_size,
			       ctx.address + ooffset,
			       digest_size);
			अवरोध;
		हाल CCP_SHA_TYPE_384:
		हाल CCP_SHA_TYPE_512:
			स_नकल(hmac_buf + block_size,
			       ctx.address + LSB_ITEM_SIZE + ooffset,
			       LSB_ITEM_SIZE);
			स_नकल(hmac_buf + block_size +
			       (LSB_ITEM_SIZE - ooffset),
			       ctx.address,
			       LSB_ITEM_SIZE);
			अवरोध;
		शेष:
			kमुक्त(hmac_buf);
			ret = -EINVAL;
			जाओ e_data;
		पूर्ण

		स_रखो(&hmac_cmd, 0, माप(hmac_cmd));
		hmac_cmd.engine = CCP_ENGINE_SHA;
		hmac_cmd.u.sha.type = sha->type;
		hmac_cmd.u.sha.ctx = sha->ctx;
		hmac_cmd.u.sha.ctx_len = sha->ctx_len;
		hmac_cmd.u.sha.src = &sg;
		hmac_cmd.u.sha.src_len = block_size + digest_size;
		hmac_cmd.u.sha.opad = शून्य;
		hmac_cmd.u.sha.opad_len = 0;
		hmac_cmd.u.sha.first = 1;
		hmac_cmd.u.sha.final = 1;
		hmac_cmd.u.sha.msg_bits = (block_size + digest_size) << 3;

		ret = ccp_run_sha_cmd(cmd_q, &hmac_cmd);
		अगर (ret)
			cmd->engine_error = hmac_cmd.engine_error;

		kमुक्त(hmac_buf);
	पूर्ण

e_data:
	अगर (sha->src)
		ccp_मुक्त_data(&src, cmd_q);

e_ctx:
	ccp_dm_मुक्त(&ctx);

	वापस ret;
पूर्ण

अटल noअंतरभूत_क्रम_stack पूर्णांक
ccp_run_rsa_cmd(काष्ठा ccp_cmd_queue *cmd_q, काष्ठा ccp_cmd *cmd)
अणु
	काष्ठा ccp_rsa_engine *rsa = &cmd->u.rsa;
	काष्ठा ccp_dm_workarea exp, src, dst;
	काष्ठा ccp_op op;
	अचिन्हित पूर्णांक sb_count, i_len, o_len;
	पूर्णांक ret;

	/* Check against the maximum allowable size, in bits */
	अगर (rsa->key_size > cmd_q->ccp->vdata->rsamax)
		वापस -EINVAL;

	अगर (!rsa->exp || !rsa->mod || !rsa->src || !rsa->dst)
		वापस -EINVAL;

	स_रखो(&op, 0, माप(op));
	op.cmd_q = cmd_q;
	op.jobid = CCP_NEW_JOBID(cmd_q->ccp);

	/* The RSA modulus must precede the message being acted upon, so
	 * it must be copied to a DMA area where the message and the
	 * modulus can be concatenated.  Thereक्रमe the input buffer
	 * length required is twice the output buffer length (which
	 * must be a multiple of 256-bits).  Compute o_len, i_len in bytes.
	 * Buffer sizes must be a multiple of 32 bytes; rounding up may be
	 * required.
	 */
	o_len = 32 * ((rsa->key_size + 255) / 256);
	i_len = o_len * 2;

	sb_count = 0;
	अगर (cmd_q->ccp->vdata->version < CCP_VERSION(5, 0)) अणु
		/* sb_count is the number of storage block slots required
		 * क्रम the modulus.
		 */
		sb_count = o_len / CCP_SB_BYTES;
		op.sb_key = cmd_q->ccp->vdata->perक्रमm->sballoc(cmd_q,
								sb_count);
		अगर (!op.sb_key)
			वापस -EIO;
	पूर्ण अन्यथा अणु
		/* A version 5 device allows a modulus size that will not fit
		 * in the LSB, so the command will transfer it from memory.
		 * Set the sb key to the शेष, even though it's not used.
		 */
		op.sb_key = cmd_q->sb_key;
	पूर्ण

	/* The RSA exponent must be in little endian क्रमmat. Reverse its
	 * byte order.
	 */
	ret = ccp_init_dm_workarea(&exp, cmd_q, o_len, DMA_TO_DEVICE);
	अगर (ret)
		जाओ e_sb;

	ret = ccp_reverse_set_dm_area(&exp, 0, rsa->exp, 0, rsa->exp_len);
	अगर (ret)
		जाओ e_exp;

	अगर (cmd_q->ccp->vdata->version < CCP_VERSION(5, 0)) अणु
		/* Copy the exponent to the local storage block, using
		 * as many 32-byte blocks as were allocated above. It's
		 * alपढ़ोy little endian, so no further change is required.
		 */
		ret = ccp_copy_to_sb(cmd_q, &exp, op.jobid, op.sb_key,
				     CCP_PASSTHRU_BYTESWAP_NOOP);
		अगर (ret) अणु
			cmd->engine_error = cmd_q->cmd_error;
			जाओ e_exp;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* The exponent can be retrieved from memory via DMA. */
		op.exp.u.dma.address = exp.dma.address;
		op.exp.u.dma.offset = 0;
	पूर्ण

	/* Concatenate the modulus and the message. Both the modulus and
	 * the opeअक्रमs must be in little endian क्रमmat.  Since the input
	 * is in big endian क्रमmat it must be converted.
	 */
	ret = ccp_init_dm_workarea(&src, cmd_q, i_len, DMA_TO_DEVICE);
	अगर (ret)
		जाओ e_exp;

	ret = ccp_reverse_set_dm_area(&src, 0, rsa->mod, 0, rsa->mod_len);
	अगर (ret)
		जाओ e_src;
	ret = ccp_reverse_set_dm_area(&src, o_len, rsa->src, 0, rsa->src_len);
	अगर (ret)
		जाओ e_src;

	/* Prepare the output area क्रम the operation */
	ret = ccp_init_dm_workarea(&dst, cmd_q, o_len, DMA_FROM_DEVICE);
	अगर (ret)
		जाओ e_src;

	op.soc = 1;
	op.src.u.dma.address = src.dma.address;
	op.src.u.dma.offset = 0;
	op.src.u.dma.length = i_len;
	op.dst.u.dma.address = dst.dma.address;
	op.dst.u.dma.offset = 0;
	op.dst.u.dma.length = o_len;

	op.u.rsa.mod_size = rsa->key_size;
	op.u.rsa.input_len = i_len;

	ret = cmd_q->ccp->vdata->perक्रमm->rsa(&op);
	अगर (ret) अणु
		cmd->engine_error = cmd_q->cmd_error;
		जाओ e_dst;
	पूर्ण

	ccp_reverse_get_dm_area(&dst, 0, rsa->dst, 0, rsa->mod_len);

e_dst:
	ccp_dm_मुक्त(&dst);

e_src:
	ccp_dm_मुक्त(&src);

e_exp:
	ccp_dm_मुक्त(&exp);

e_sb:
	अगर (sb_count)
		cmd_q->ccp->vdata->perक्रमm->sbमुक्त(cmd_q, op.sb_key, sb_count);

	वापस ret;
पूर्ण

अटल noअंतरभूत_क्रम_stack पूर्णांक
ccp_run_passthru_cmd(काष्ठा ccp_cmd_queue *cmd_q, काष्ठा ccp_cmd *cmd)
अणु
	काष्ठा ccp_passthru_engine *pt = &cmd->u.passthru;
	काष्ठा ccp_dm_workarea mask;
	काष्ठा ccp_data src, dst;
	काष्ठा ccp_op op;
	bool in_place = false;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret = 0;

	अगर (!pt->final && (pt->src_len & (CCP_PASSTHRU_BLOCKSIZE - 1)))
		वापस -EINVAL;

	अगर (!pt->src || !pt->dst)
		वापस -EINVAL;

	अगर (pt->bit_mod != CCP_PASSTHRU_BITWISE_NOOP) अणु
		अगर (pt->mask_len != CCP_PASSTHRU_MASKSIZE)
			वापस -EINVAL;
		अगर (!pt->mask)
			वापस -EINVAL;
	पूर्ण

	BUILD_BUG_ON(CCP_PASSTHRU_SB_COUNT != 1);

	स_रखो(&op, 0, माप(op));
	op.cmd_q = cmd_q;
	op.jobid = CCP_NEW_JOBID(cmd_q->ccp);

	अगर (pt->bit_mod != CCP_PASSTHRU_BITWISE_NOOP) अणु
		/* Load the mask */
		op.sb_key = cmd_q->sb_key;

		ret = ccp_init_dm_workarea(&mask, cmd_q,
					   CCP_PASSTHRU_SB_COUNT *
					   CCP_SB_BYTES,
					   DMA_TO_DEVICE);
		अगर (ret)
			वापस ret;

		ret = ccp_set_dm_area(&mask, 0, pt->mask, 0, pt->mask_len);
		अगर (ret)
			जाओ e_mask;
		ret = ccp_copy_to_sb(cmd_q, &mask, op.jobid, op.sb_key,
				     CCP_PASSTHRU_BYTESWAP_NOOP);
		अगर (ret) अणु
			cmd->engine_error = cmd_q->cmd_error;
			जाओ e_mask;
		पूर्ण
	पूर्ण

	/* Prepare the input and output data workareas. For in-place
	 * operations we need to set the dma direction to BIसूचीECTIONAL
	 * and copy the src workarea to the dst workarea.
	 */
	अगर (sg_virt(pt->src) == sg_virt(pt->dst))
		in_place = true;

	ret = ccp_init_data(&src, cmd_q, pt->src, pt->src_len,
			    CCP_PASSTHRU_MASKSIZE,
			    in_place ? DMA_BIसूचीECTIONAL : DMA_TO_DEVICE);
	अगर (ret)
		जाओ e_mask;

	अगर (in_place) अणु
		dst = src;
	पूर्ण अन्यथा अणु
		ret = ccp_init_data(&dst, cmd_q, pt->dst, pt->src_len,
				    CCP_PASSTHRU_MASKSIZE, DMA_FROM_DEVICE);
		अगर (ret)
			जाओ e_src;
	पूर्ण

	/* Send data to the CCP Passthru engine
	 *   Because the CCP engine works on a single source and destination
	 *   dma address at a समय, each entry in the source scatterlist
	 *   (after the dma_map_sg call) must be less than or equal to the
	 *   (reमुख्यing) length in the destination scatterlist entry and the
	 *   length must be a multiple of CCP_PASSTHRU_BLOCKSIZE
	 */
	dst.sg_wa.sg_used = 0;
	क्रम (i = 1; i <= src.sg_wa.dma_count; i++) अणु
		अगर (!dst.sg_wa.sg ||
		    (sg_dma_len(dst.sg_wa.sg) < sg_dma_len(src.sg_wa.sg))) अणु
			ret = -EINVAL;
			जाओ e_dst;
		पूर्ण

		अगर (i == src.sg_wa.dma_count) अणु
			op.eom = 1;
			op.soc = 1;
		पूर्ण

		op.src.type = CCP_MEMTYPE_SYSTEM;
		op.src.u.dma.address = sg_dma_address(src.sg_wa.sg);
		op.src.u.dma.offset = 0;
		op.src.u.dma.length = sg_dma_len(src.sg_wa.sg);

		op.dst.type = CCP_MEMTYPE_SYSTEM;
		op.dst.u.dma.address = sg_dma_address(dst.sg_wa.sg);
		op.dst.u.dma.offset = dst.sg_wa.sg_used;
		op.dst.u.dma.length = op.src.u.dma.length;

		ret = cmd_q->ccp->vdata->perक्रमm->passthru(&op);
		अगर (ret) अणु
			cmd->engine_error = cmd_q->cmd_error;
			जाओ e_dst;
		पूर्ण

		dst.sg_wa.sg_used += sg_dma_len(src.sg_wa.sg);
		अगर (dst.sg_wa.sg_used == sg_dma_len(dst.sg_wa.sg)) अणु
			dst.sg_wa.sg = sg_next(dst.sg_wa.sg);
			dst.sg_wa.sg_used = 0;
		पूर्ण
		src.sg_wa.sg = sg_next(src.sg_wa.sg);
	पूर्ण

e_dst:
	अगर (!in_place)
		ccp_मुक्त_data(&dst, cmd_q);

e_src:
	ccp_मुक्त_data(&src, cmd_q);

e_mask:
	अगर (pt->bit_mod != CCP_PASSTHRU_BITWISE_NOOP)
		ccp_dm_मुक्त(&mask);

	वापस ret;
पूर्ण

अटल noअंतरभूत_क्रम_stack पूर्णांक
ccp_run_passthru_nomap_cmd(काष्ठा ccp_cmd_queue *cmd_q,
				      काष्ठा ccp_cmd *cmd)
अणु
	काष्ठा ccp_passthru_nomap_engine *pt = &cmd->u.passthru_nomap;
	काष्ठा ccp_dm_workarea mask;
	काष्ठा ccp_op op;
	पूर्णांक ret;

	अगर (!pt->final && (pt->src_len & (CCP_PASSTHRU_BLOCKSIZE - 1)))
		वापस -EINVAL;

	अगर (!pt->src_dma || !pt->dst_dma)
		वापस -EINVAL;

	अगर (pt->bit_mod != CCP_PASSTHRU_BITWISE_NOOP) अणु
		अगर (pt->mask_len != CCP_PASSTHRU_MASKSIZE)
			वापस -EINVAL;
		अगर (!pt->mask)
			वापस -EINVAL;
	पूर्ण

	BUILD_BUG_ON(CCP_PASSTHRU_SB_COUNT != 1);

	स_रखो(&op, 0, माप(op));
	op.cmd_q = cmd_q;
	op.jobid = CCP_NEW_JOBID(cmd_q->ccp);

	अगर (pt->bit_mod != CCP_PASSTHRU_BITWISE_NOOP) अणु
		/* Load the mask */
		op.sb_key = cmd_q->sb_key;

		mask.length = pt->mask_len;
		mask.dma.address = pt->mask;
		mask.dma.length = pt->mask_len;

		ret = ccp_copy_to_sb(cmd_q, &mask, op.jobid, op.sb_key,
				     CCP_PASSTHRU_BYTESWAP_NOOP);
		अगर (ret) अणु
			cmd->engine_error = cmd_q->cmd_error;
			वापस ret;
		पूर्ण
	पूर्ण

	/* Send data to the CCP Passthru engine */
	op.eom = 1;
	op.soc = 1;

	op.src.type = CCP_MEMTYPE_SYSTEM;
	op.src.u.dma.address = pt->src_dma;
	op.src.u.dma.offset = 0;
	op.src.u.dma.length = pt->src_len;

	op.dst.type = CCP_MEMTYPE_SYSTEM;
	op.dst.u.dma.address = pt->dst_dma;
	op.dst.u.dma.offset = 0;
	op.dst.u.dma.length = pt->src_len;

	ret = cmd_q->ccp->vdata->perक्रमm->passthru(&op);
	अगर (ret)
		cmd->engine_error = cmd_q->cmd_error;

	वापस ret;
पूर्ण

अटल पूर्णांक ccp_run_ecc_mm_cmd(काष्ठा ccp_cmd_queue *cmd_q, काष्ठा ccp_cmd *cmd)
अणु
	काष्ठा ccp_ecc_engine *ecc = &cmd->u.ecc;
	काष्ठा ccp_dm_workarea src, dst;
	काष्ठा ccp_op op;
	पूर्णांक ret;
	u8 *save;

	अगर (!ecc->u.mm.opeअक्रम_1 ||
	    (ecc->u.mm.opeअक्रम_1_len > CCP_ECC_MODULUS_BYTES))
		वापस -EINVAL;

	अगर (ecc->function != CCP_ECC_FUNCTION_MINV_384BIT)
		अगर (!ecc->u.mm.opeअक्रम_2 ||
		    (ecc->u.mm.opeअक्रम_2_len > CCP_ECC_MODULUS_BYTES))
			वापस -EINVAL;

	अगर (!ecc->u.mm.result ||
	    (ecc->u.mm.result_len < CCP_ECC_MODULUS_BYTES))
		वापस -EINVAL;

	स_रखो(&op, 0, माप(op));
	op.cmd_q = cmd_q;
	op.jobid = CCP_NEW_JOBID(cmd_q->ccp);

	/* Concatenate the modulus and the opeअक्रमs. Both the modulus and
	 * the opeअक्रमs must be in little endian क्रमmat.  Since the input
	 * is in big endian क्रमmat it must be converted and placed in a
	 * fixed length buffer.
	 */
	ret = ccp_init_dm_workarea(&src, cmd_q, CCP_ECC_SRC_BUF_SIZE,
				   DMA_TO_DEVICE);
	अगर (ret)
		वापस ret;

	/* Save the workarea address since it is updated in order to perक्रमm
	 * the concatenation
	 */
	save = src.address;

	/* Copy the ECC modulus */
	ret = ccp_reverse_set_dm_area(&src, 0, ecc->mod, 0, ecc->mod_len);
	अगर (ret)
		जाओ e_src;
	src.address += CCP_ECC_OPERAND_SIZE;

	/* Copy the first opeअक्रम */
	ret = ccp_reverse_set_dm_area(&src, 0, ecc->u.mm.opeअक्रम_1, 0,
				      ecc->u.mm.opeअक्रम_1_len);
	अगर (ret)
		जाओ e_src;
	src.address += CCP_ECC_OPERAND_SIZE;

	अगर (ecc->function != CCP_ECC_FUNCTION_MINV_384BIT) अणु
		/* Copy the second opeअक्रम */
		ret = ccp_reverse_set_dm_area(&src, 0, ecc->u.mm.opeअक्रम_2, 0,
					      ecc->u.mm.opeअक्रम_2_len);
		अगर (ret)
			जाओ e_src;
		src.address += CCP_ECC_OPERAND_SIZE;
	पूर्ण

	/* Restore the workarea address */
	src.address = save;

	/* Prepare the output area क्रम the operation */
	ret = ccp_init_dm_workarea(&dst, cmd_q, CCP_ECC_DST_BUF_SIZE,
				   DMA_FROM_DEVICE);
	अगर (ret)
		जाओ e_src;

	op.soc = 1;
	op.src.u.dma.address = src.dma.address;
	op.src.u.dma.offset = 0;
	op.src.u.dma.length = src.length;
	op.dst.u.dma.address = dst.dma.address;
	op.dst.u.dma.offset = 0;
	op.dst.u.dma.length = dst.length;

	op.u.ecc.function = cmd->u.ecc.function;

	ret = cmd_q->ccp->vdata->perक्रमm->ecc(&op);
	अगर (ret) अणु
		cmd->engine_error = cmd_q->cmd_error;
		जाओ e_dst;
	पूर्ण

	ecc->ecc_result = le16_to_cpup(
		(स्थिर __le16 *)(dst.address + CCP_ECC_RESULT_OFFSET));
	अगर (!(ecc->ecc_result & CCP_ECC_RESULT_SUCCESS)) अणु
		ret = -EIO;
		जाओ e_dst;
	पूर्ण

	/* Save the ECC result */
	ccp_reverse_get_dm_area(&dst, 0, ecc->u.mm.result, 0,
				CCP_ECC_MODULUS_BYTES);

e_dst:
	ccp_dm_मुक्त(&dst);

e_src:
	ccp_dm_मुक्त(&src);

	वापस ret;
पूर्ण

अटल पूर्णांक ccp_run_ecc_pm_cmd(काष्ठा ccp_cmd_queue *cmd_q, काष्ठा ccp_cmd *cmd)
अणु
	काष्ठा ccp_ecc_engine *ecc = &cmd->u.ecc;
	काष्ठा ccp_dm_workarea src, dst;
	काष्ठा ccp_op op;
	पूर्णांक ret;
	u8 *save;

	अगर (!ecc->u.pm.poपूर्णांक_1.x ||
	    (ecc->u.pm.poपूर्णांक_1.x_len > CCP_ECC_MODULUS_BYTES) ||
	    !ecc->u.pm.poपूर्णांक_1.y ||
	    (ecc->u.pm.poपूर्णांक_1.y_len > CCP_ECC_MODULUS_BYTES))
		वापस -EINVAL;

	अगर (ecc->function == CCP_ECC_FUNCTION_PADD_384BIT) अणु
		अगर (!ecc->u.pm.poपूर्णांक_2.x ||
		    (ecc->u.pm.poपूर्णांक_2.x_len > CCP_ECC_MODULUS_BYTES) ||
		    !ecc->u.pm.poपूर्णांक_2.y ||
		    (ecc->u.pm.poपूर्णांक_2.y_len > CCP_ECC_MODULUS_BYTES))
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		अगर (!ecc->u.pm.करोमुख्य_a ||
		    (ecc->u.pm.करोमुख्य_a_len > CCP_ECC_MODULUS_BYTES))
			वापस -EINVAL;

		अगर (ecc->function == CCP_ECC_FUNCTION_PMUL_384BIT)
			अगर (!ecc->u.pm.scalar ||
			    (ecc->u.pm.scalar_len > CCP_ECC_MODULUS_BYTES))
				वापस -EINVAL;
	पूर्ण

	अगर (!ecc->u.pm.result.x ||
	    (ecc->u.pm.result.x_len < CCP_ECC_MODULUS_BYTES) ||
	    !ecc->u.pm.result.y ||
	    (ecc->u.pm.result.y_len < CCP_ECC_MODULUS_BYTES))
		वापस -EINVAL;

	स_रखो(&op, 0, माप(op));
	op.cmd_q = cmd_q;
	op.jobid = CCP_NEW_JOBID(cmd_q->ccp);

	/* Concatenate the modulus and the opeअक्रमs. Both the modulus and
	 * the opeअक्रमs must be in little endian क्रमmat.  Since the input
	 * is in big endian क्रमmat it must be converted and placed in a
	 * fixed length buffer.
	 */
	ret = ccp_init_dm_workarea(&src, cmd_q, CCP_ECC_SRC_BUF_SIZE,
				   DMA_TO_DEVICE);
	अगर (ret)
		वापस ret;

	/* Save the workarea address since it is updated in order to perक्रमm
	 * the concatenation
	 */
	save = src.address;

	/* Copy the ECC modulus */
	ret = ccp_reverse_set_dm_area(&src, 0, ecc->mod, 0, ecc->mod_len);
	अगर (ret)
		जाओ e_src;
	src.address += CCP_ECC_OPERAND_SIZE;

	/* Copy the first poपूर्णांक X and Y coordinate */
	ret = ccp_reverse_set_dm_area(&src, 0, ecc->u.pm.poपूर्णांक_1.x, 0,
				      ecc->u.pm.poपूर्णांक_1.x_len);
	अगर (ret)
		जाओ e_src;
	src.address += CCP_ECC_OPERAND_SIZE;
	ret = ccp_reverse_set_dm_area(&src, 0, ecc->u.pm.poपूर्णांक_1.y, 0,
				      ecc->u.pm.poपूर्णांक_1.y_len);
	अगर (ret)
		जाओ e_src;
	src.address += CCP_ECC_OPERAND_SIZE;

	/* Set the first poपूर्णांक Z coordinate to 1 */
	*src.address = 0x01;
	src.address += CCP_ECC_OPERAND_SIZE;

	अगर (ecc->function == CCP_ECC_FUNCTION_PADD_384BIT) अणु
		/* Copy the second poपूर्णांक X and Y coordinate */
		ret = ccp_reverse_set_dm_area(&src, 0, ecc->u.pm.poपूर्णांक_2.x, 0,
					      ecc->u.pm.poपूर्णांक_2.x_len);
		अगर (ret)
			जाओ e_src;
		src.address += CCP_ECC_OPERAND_SIZE;
		ret = ccp_reverse_set_dm_area(&src, 0, ecc->u.pm.poपूर्णांक_2.y, 0,
					      ecc->u.pm.poपूर्णांक_2.y_len);
		अगर (ret)
			जाओ e_src;
		src.address += CCP_ECC_OPERAND_SIZE;

		/* Set the second poपूर्णांक Z coordinate to 1 */
		*src.address = 0x01;
		src.address += CCP_ECC_OPERAND_SIZE;
	पूर्ण अन्यथा अणु
		/* Copy the Doमुख्य "a" parameter */
		ret = ccp_reverse_set_dm_area(&src, 0, ecc->u.pm.करोमुख्य_a, 0,
					      ecc->u.pm.करोमुख्य_a_len);
		अगर (ret)
			जाओ e_src;
		src.address += CCP_ECC_OPERAND_SIZE;

		अगर (ecc->function == CCP_ECC_FUNCTION_PMUL_384BIT) अणु
			/* Copy the scalar value */
			ret = ccp_reverse_set_dm_area(&src, 0,
						      ecc->u.pm.scalar, 0,
						      ecc->u.pm.scalar_len);
			अगर (ret)
				जाओ e_src;
			src.address += CCP_ECC_OPERAND_SIZE;
		पूर्ण
	पूर्ण

	/* Restore the workarea address */
	src.address = save;

	/* Prepare the output area क्रम the operation */
	ret = ccp_init_dm_workarea(&dst, cmd_q, CCP_ECC_DST_BUF_SIZE,
				   DMA_FROM_DEVICE);
	अगर (ret)
		जाओ e_src;

	op.soc = 1;
	op.src.u.dma.address = src.dma.address;
	op.src.u.dma.offset = 0;
	op.src.u.dma.length = src.length;
	op.dst.u.dma.address = dst.dma.address;
	op.dst.u.dma.offset = 0;
	op.dst.u.dma.length = dst.length;

	op.u.ecc.function = cmd->u.ecc.function;

	ret = cmd_q->ccp->vdata->perक्रमm->ecc(&op);
	अगर (ret) अणु
		cmd->engine_error = cmd_q->cmd_error;
		जाओ e_dst;
	पूर्ण

	ecc->ecc_result = le16_to_cpup(
		(स्थिर __le16 *)(dst.address + CCP_ECC_RESULT_OFFSET));
	अगर (!(ecc->ecc_result & CCP_ECC_RESULT_SUCCESS)) अणु
		ret = -EIO;
		जाओ e_dst;
	पूर्ण

	/* Save the workarea address since it is updated as we walk through
	 * to copy the poपूर्णांक math result
	 */
	save = dst.address;

	/* Save the ECC result X and Y coordinates */
	ccp_reverse_get_dm_area(&dst, 0, ecc->u.pm.result.x, 0,
				CCP_ECC_MODULUS_BYTES);
	dst.address += CCP_ECC_OUTPUT_SIZE;
	ccp_reverse_get_dm_area(&dst, 0, ecc->u.pm.result.y, 0,
				CCP_ECC_MODULUS_BYTES);

	/* Restore the workarea address */
	dst.address = save;

e_dst:
	ccp_dm_मुक्त(&dst);

e_src:
	ccp_dm_मुक्त(&src);

	वापस ret;
पूर्ण

अटल noअंतरभूत_क्रम_stack पूर्णांक
ccp_run_ecc_cmd(काष्ठा ccp_cmd_queue *cmd_q, काष्ठा ccp_cmd *cmd)
अणु
	काष्ठा ccp_ecc_engine *ecc = &cmd->u.ecc;

	ecc->ecc_result = 0;

	अगर (!ecc->mod ||
	    (ecc->mod_len > CCP_ECC_MODULUS_BYTES))
		वापस -EINVAL;

	चयन (ecc->function) अणु
	हाल CCP_ECC_FUNCTION_MMUL_384BIT:
	हाल CCP_ECC_FUNCTION_MADD_384BIT:
	हाल CCP_ECC_FUNCTION_MINV_384BIT:
		वापस ccp_run_ecc_mm_cmd(cmd_q, cmd);

	हाल CCP_ECC_FUNCTION_PADD_384BIT:
	हाल CCP_ECC_FUNCTION_PMUL_384BIT:
	हाल CCP_ECC_FUNCTION_PDBL_384BIT:
		वापस ccp_run_ecc_pm_cmd(cmd_q, cmd);

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

पूर्णांक ccp_run_cmd(काष्ठा ccp_cmd_queue *cmd_q, काष्ठा ccp_cmd *cmd)
अणु
	पूर्णांक ret;

	cmd->engine_error = 0;
	cmd_q->cmd_error = 0;
	cmd_q->पूर्णांक_rcvd = 0;
	cmd_q->मुक्त_slots = cmd_q->ccp->vdata->perक्रमm->get_मुक्त_slots(cmd_q);

	चयन (cmd->engine) अणु
	हाल CCP_ENGINE_AES:
		चयन (cmd->u.aes.mode) अणु
		हाल CCP_AES_MODE_CMAC:
			ret = ccp_run_aes_cmac_cmd(cmd_q, cmd);
			अवरोध;
		हाल CCP_AES_MODE_GCM:
			ret = ccp_run_aes_gcm_cmd(cmd_q, cmd);
			अवरोध;
		शेष:
			ret = ccp_run_aes_cmd(cmd_q, cmd);
			अवरोध;
		पूर्ण
		अवरोध;
	हाल CCP_ENGINE_XTS_AES_128:
		ret = ccp_run_xts_aes_cmd(cmd_q, cmd);
		अवरोध;
	हाल CCP_ENGINE_DES3:
		ret = ccp_run_des3_cmd(cmd_q, cmd);
		अवरोध;
	हाल CCP_ENGINE_SHA:
		ret = ccp_run_sha_cmd(cmd_q, cmd);
		अवरोध;
	हाल CCP_ENGINE_RSA:
		ret = ccp_run_rsa_cmd(cmd_q, cmd);
		अवरोध;
	हाल CCP_ENGINE_PASSTHRU:
		अगर (cmd->flags & CCP_CMD_PASSTHRU_NO_DMA_MAP)
			ret = ccp_run_passthru_nomap_cmd(cmd_q, cmd);
		अन्यथा
			ret = ccp_run_passthru_cmd(cmd_q, cmd);
		अवरोध;
	हाल CCP_ENGINE_ECC:
		ret = ccp_run_ecc_cmd(cmd_q, cmd);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण
