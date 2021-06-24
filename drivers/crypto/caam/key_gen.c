<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * CAAM/SEC 4.x functions क्रम handling key-generation jobs
 *
 * Copyright 2008-2011 Freescale Semiconductor, Inc.
 *
 */
#समावेश "compat.h"
#समावेश "jr.h"
#समावेश "error.h"
#समावेश "desc_constr.h"
#समावेश "key_gen.h"

व्योम split_key_करोne(काष्ठा device *dev, u32 *desc, u32 err,
			   व्योम *context)
अणु
	काष्ठा split_key_result *res = context;
	पूर्णांक ecode = 0;

	dev_dbg(dev, "%s %d: err 0x%x\n", __func__, __LINE__, err);

	अगर (err)
		ecode = caam_jr_strstatus(dev, err);

	res->err = ecode;

	complete(&res->completion);
पूर्ण
EXPORT_SYMBOL(split_key_करोne);
/*
get a split ipad/opad key

Split key generation-----------------------------------------------

[00] 0xb0810008    jobdesc: stidx=1 share=never len=8
[01] 0x04000014        key: class2->keyreg len=20
			@0xffe01000
[03] 0x84410014  operation: cls2-op sha1 hmac init dec
[04] 0x24940000     fअगरold: class2 msgdata-last2 len=0 imm
[05] 0xa4000001       jump: class2 local all ->1 [06]
[06] 0x64260028    fअगरostr: class2 mdsplit-jdk len=40
			@0xffe04000
*/
पूर्णांक gen_split_key(काष्ठा device *jrdev, u8 *key_out,
		  काष्ठा alginfo * स्थिर adata, स्थिर u8 *key_in, u32 keylen,
		  पूर्णांक max_keylen)
अणु
	u32 *desc;
	काष्ठा split_key_result result;
	dma_addr_t dma_addr;
	अचिन्हित पूर्णांक local_max;
	पूर्णांक ret = -ENOMEM;

	adata->keylen = split_key_len(adata->algtype & OP_ALG_ALGSEL_MASK);
	adata->keylen_pad = split_key_pad_len(adata->algtype &
					      OP_ALG_ALGSEL_MASK);
	local_max = max(keylen, adata->keylen_pad);

	dev_dbg(jrdev, "split keylen %d split keylen padded %d\n",
		adata->keylen, adata->keylen_pad);
	prपूर्णांक_hex_dump_debug("ctx.key@" __stringअगरy(__LINE__)": ",
			     DUMP_PREFIX_ADDRESS, 16, 4, key_in, keylen, 1);

	अगर (local_max > max_keylen)
		वापस -EINVAL;

	desc = kदो_स्मृति(CAAM_CMD_SZ * 6 + CAAM_PTR_SZ * 2, GFP_KERNEL | GFP_DMA);
	अगर (!desc) अणु
		dev_err(jrdev, "unable to allocate key input memory\n");
		वापस ret;
	पूर्ण

	स_नकल(key_out, key_in, keylen);

	dma_addr = dma_map_single(jrdev, key_out, local_max, DMA_BIसूचीECTIONAL);
	अगर (dma_mapping_error(jrdev, dma_addr)) अणु
		dev_err(jrdev, "unable to map key memory\n");
		जाओ out_मुक्त;
	पूर्ण

	init_job_desc(desc, 0);
	append_key(desc, dma_addr, keylen, CLASS_2 | KEY_DEST_CLASS_REG);

	/* Sets MDHA up पूर्णांकo an HMAC-INIT */
	append_operation(desc, (adata->algtype & OP_ALG_ALGSEL_MASK) |
			 OP_ALG_AAI_HMAC | OP_TYPE_CLASS2_ALG | OP_ALG_DECRYPT |
			 OP_ALG_AS_INIT);

	/*
	 * करो a FIFO_LOAD of zero, this will trigger the पूर्णांकernal key expansion
	 * पूर्णांकo both pads inside MDHA
	 */
	append_fअगरo_load_as_imm(desc, शून्य, 0, LDST_CLASS_2_CCB |
				FIFOLD_TYPE_MSG | FIFOLD_TYPE_LAST2);

	/*
	 * FIFO_STORE with the explicit split-key content store
	 * (0x26 output type)
	 */
	append_fअगरo_store(desc, dma_addr, adata->keylen,
			  LDST_CLASS_2_CCB | FIFOST_TYPE_SPLIT_KEK);

	prपूर्णांक_hex_dump_debug("jobdesc@"__stringअगरy(__LINE__)": ",
			     DUMP_PREFIX_ADDRESS, 16, 4, desc, desc_bytes(desc),
			     1);

	result.err = 0;
	init_completion(&result.completion);

	ret = caam_jr_enqueue(jrdev, desc, split_key_करोne, &result);
	अगर (ret == -EINPROGRESS) अणु
		/* in progress */
		रुको_क्रम_completion(&result.completion);
		ret = result.err;

		prपूर्णांक_hex_dump_debug("ctx.key@"__stringअगरy(__LINE__)": ",
				     DUMP_PREFIX_ADDRESS, 16, 4, key_out,
				     adata->keylen_pad, 1);
	पूर्ण

	dma_unmap_single(jrdev, dma_addr, local_max, DMA_BIसूचीECTIONAL);
out_मुक्त:
	kमुक्त(desc);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(gen_split_key);
