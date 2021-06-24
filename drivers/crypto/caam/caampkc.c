<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0+ OR BSD-3-Clause)
/*
 * caam - Freescale FSL CAAM support क्रम Public Key Cryptography
 *
 * Copyright 2016 Freescale Semiconductor, Inc.
 * Copyright 2018-2019 NXP
 *
 * There is no Shared Descriptor क्रम PKC so that the Job Descriptor must carry
 * all the desired key parameters, input and output poपूर्णांकers.
 */
#समावेश "compat.h"
#समावेश "regs.h"
#समावेश "intern.h"
#समावेश "jr.h"
#समावेश "error.h"
#समावेश "desc_constr.h"
#समावेश "sg_sw_sec4.h"
#समावेश "caampkc.h"

#घोषणा DESC_RSA_PUB_LEN	(2 * CAAM_CMD_SZ + SIZखातापूर्ण_RSA_PUB_PDB)
#घोषणा DESC_RSA_PRIV_F1_LEN	(2 * CAAM_CMD_SZ + \
				 SIZखातापूर्ण_RSA_PRIV_F1_PDB)
#घोषणा DESC_RSA_PRIV_F2_LEN	(2 * CAAM_CMD_SZ + \
				 SIZखातापूर्ण_RSA_PRIV_F2_PDB)
#घोषणा DESC_RSA_PRIV_F3_LEN	(2 * CAAM_CMD_SZ + \
				 SIZखातापूर्ण_RSA_PRIV_F3_PDB)
#घोषणा CAAM_RSA_MAX_INPUT_SIZE	512 /* क्रम a 4096-bit modulus */

/* buffer filled with zeros, used क्रम padding */
अटल u8 *zero_buffer;

/*
 * variable used to aव्योम द्विगुन मुक्त of resources in हाल
 * algorithm registration was unsuccessful
 */
अटल bool init_करोne;

काष्ठा caam_akcipher_alg अणु
	काष्ठा akcipher_alg akcipher;
	bool रेजिस्टरed;
पूर्ण;

अटल व्योम rsa_io_unmap(काष्ठा device *dev, काष्ठा rsa_edesc *edesc,
			 काष्ठा akcipher_request *req)
अणु
	काष्ठा caam_rsa_req_ctx *req_ctx = akcipher_request_ctx(req);

	dma_unmap_sg(dev, req->dst, edesc->dst_nents, DMA_FROM_DEVICE);
	dma_unmap_sg(dev, req_ctx->fixup_src, edesc->src_nents, DMA_TO_DEVICE);

	अगर (edesc->sec4_sg_bytes)
		dma_unmap_single(dev, edesc->sec4_sg_dma, edesc->sec4_sg_bytes,
				 DMA_TO_DEVICE);
पूर्ण

अटल व्योम rsa_pub_unmap(काष्ठा device *dev, काष्ठा rsa_edesc *edesc,
			  काष्ठा akcipher_request *req)
अणु
	काष्ठा crypto_akcipher *tfm = crypto_akcipher_reqtfm(req);
	काष्ठा caam_rsa_ctx *ctx = akcipher_tfm_ctx(tfm);
	काष्ठा caam_rsa_key *key = &ctx->key;
	काष्ठा rsa_pub_pdb *pdb = &edesc->pdb.pub;

	dma_unmap_single(dev, pdb->n_dma, key->n_sz, DMA_TO_DEVICE);
	dma_unmap_single(dev, pdb->e_dma, key->e_sz, DMA_TO_DEVICE);
पूर्ण

अटल व्योम rsa_priv_f1_unmap(काष्ठा device *dev, काष्ठा rsa_edesc *edesc,
			      काष्ठा akcipher_request *req)
अणु
	काष्ठा crypto_akcipher *tfm = crypto_akcipher_reqtfm(req);
	काष्ठा caam_rsa_ctx *ctx = akcipher_tfm_ctx(tfm);
	काष्ठा caam_rsa_key *key = &ctx->key;
	काष्ठा rsa_priv_f1_pdb *pdb = &edesc->pdb.priv_f1;

	dma_unmap_single(dev, pdb->n_dma, key->n_sz, DMA_TO_DEVICE);
	dma_unmap_single(dev, pdb->d_dma, key->d_sz, DMA_TO_DEVICE);
पूर्ण

अटल व्योम rsa_priv_f2_unmap(काष्ठा device *dev, काष्ठा rsa_edesc *edesc,
			      काष्ठा akcipher_request *req)
अणु
	काष्ठा crypto_akcipher *tfm = crypto_akcipher_reqtfm(req);
	काष्ठा caam_rsa_ctx *ctx = akcipher_tfm_ctx(tfm);
	काष्ठा caam_rsa_key *key = &ctx->key;
	काष्ठा rsa_priv_f2_pdb *pdb = &edesc->pdb.priv_f2;
	माप_प्रकार p_sz = key->p_sz;
	माप_प्रकार q_sz = key->q_sz;

	dma_unmap_single(dev, pdb->d_dma, key->d_sz, DMA_TO_DEVICE);
	dma_unmap_single(dev, pdb->p_dma, p_sz, DMA_TO_DEVICE);
	dma_unmap_single(dev, pdb->q_dma, q_sz, DMA_TO_DEVICE);
	dma_unmap_single(dev, pdb->पंचांगp1_dma, p_sz, DMA_BIसूचीECTIONAL);
	dma_unmap_single(dev, pdb->पंचांगp2_dma, q_sz, DMA_BIसूचीECTIONAL);
पूर्ण

अटल व्योम rsa_priv_f3_unmap(काष्ठा device *dev, काष्ठा rsa_edesc *edesc,
			      काष्ठा akcipher_request *req)
अणु
	काष्ठा crypto_akcipher *tfm = crypto_akcipher_reqtfm(req);
	काष्ठा caam_rsa_ctx *ctx = akcipher_tfm_ctx(tfm);
	काष्ठा caam_rsa_key *key = &ctx->key;
	काष्ठा rsa_priv_f3_pdb *pdb = &edesc->pdb.priv_f3;
	माप_प्रकार p_sz = key->p_sz;
	माप_प्रकार q_sz = key->q_sz;

	dma_unmap_single(dev, pdb->p_dma, p_sz, DMA_TO_DEVICE);
	dma_unmap_single(dev, pdb->q_dma, q_sz, DMA_TO_DEVICE);
	dma_unmap_single(dev, pdb->dp_dma, p_sz, DMA_TO_DEVICE);
	dma_unmap_single(dev, pdb->dq_dma, q_sz, DMA_TO_DEVICE);
	dma_unmap_single(dev, pdb->c_dma, p_sz, DMA_TO_DEVICE);
	dma_unmap_single(dev, pdb->पंचांगp1_dma, p_sz, DMA_BIसूचीECTIONAL);
	dma_unmap_single(dev, pdb->पंचांगp2_dma, q_sz, DMA_BIसूचीECTIONAL);
पूर्ण

/* RSA Job Completion handler */
अटल व्योम rsa_pub_करोne(काष्ठा device *dev, u32 *desc, u32 err, व्योम *context)
अणु
	काष्ठा akcipher_request *req = context;
	काष्ठा caam_rsa_req_ctx *req_ctx = akcipher_request_ctx(req);
	काष्ठा caam_drv_निजी_jr *jrp = dev_get_drvdata(dev);
	काष्ठा rsa_edesc *edesc;
	पूर्णांक ecode = 0;
	bool has_bklog;

	अगर (err)
		ecode = caam_jr_strstatus(dev, err);

	edesc = req_ctx->edesc;
	has_bklog = edesc->bklog;

	rsa_pub_unmap(dev, edesc, req);
	rsa_io_unmap(dev, edesc, req);
	kमुक्त(edesc);

	/*
	 * If no backlog flag, the completion of the request is करोne
	 * by CAAM, not crypto engine.
	 */
	अगर (!has_bklog)
		akcipher_request_complete(req, ecode);
	अन्यथा
		crypto_finalize_akcipher_request(jrp->engine, req, ecode);
पूर्ण

अटल व्योम rsa_priv_f_करोne(काष्ठा device *dev, u32 *desc, u32 err,
			    व्योम *context)
अणु
	काष्ठा akcipher_request *req = context;
	काष्ठा crypto_akcipher *tfm = crypto_akcipher_reqtfm(req);
	काष्ठा caam_drv_निजी_jr *jrp = dev_get_drvdata(dev);
	काष्ठा caam_rsa_ctx *ctx = akcipher_tfm_ctx(tfm);
	काष्ठा caam_rsa_key *key = &ctx->key;
	काष्ठा caam_rsa_req_ctx *req_ctx = akcipher_request_ctx(req);
	काष्ठा rsa_edesc *edesc;
	पूर्णांक ecode = 0;
	bool has_bklog;

	अगर (err)
		ecode = caam_jr_strstatus(dev, err);

	edesc = req_ctx->edesc;
	has_bklog = edesc->bklog;

	चयन (key->priv_क्रमm) अणु
	हाल FORM1:
		rsa_priv_f1_unmap(dev, edesc, req);
		अवरोध;
	हाल FORM2:
		rsa_priv_f2_unmap(dev, edesc, req);
		अवरोध;
	हाल FORM3:
		rsa_priv_f3_unmap(dev, edesc, req);
	पूर्ण

	rsa_io_unmap(dev, edesc, req);
	kमुक्त(edesc);

	/*
	 * If no backlog flag, the completion of the request is करोne
	 * by CAAM, not crypto engine.
	 */
	अगर (!has_bklog)
		akcipher_request_complete(req, ecode);
	अन्यथा
		crypto_finalize_akcipher_request(jrp->engine, req, ecode);
पूर्ण

/**
 * caam_rsa_count_leading_zeros - Count leading zeros, need it to strip,
 *                                from a given scatterlist
 *
 * @sgl   : scatterlist to count zeros from
 * @nbytes: number of zeros, in bytes, to strip
 * @flags : operation flags
 */
अटल पूर्णांक caam_rsa_count_leading_zeros(काष्ठा scatterlist *sgl,
					अचिन्हित पूर्णांक nbytes,
					अचिन्हित पूर्णांक flags)
अणु
	काष्ठा sg_mapping_iter miter;
	पूर्णांक lzeros, ents;
	अचिन्हित पूर्णांक len;
	अचिन्हित पूर्णांक tbytes = nbytes;
	स्थिर u8 *buff;

	ents = sg_nents_क्रम_len(sgl, nbytes);
	अगर (ents < 0)
		वापस ents;

	sg_miter_start(&miter, sgl, ents, SG_MITER_FROM_SG | flags);

	lzeros = 0;
	len = 0;
	जबतक (nbytes > 0) अणु
		/* करो not strip more than given bytes */
		जबतक (len && !*buff && lzeros < nbytes) अणु
			lzeros++;
			len--;
			buff++;
		पूर्ण

		अगर (len && *buff)
			अवरोध;

		sg_miter_next(&miter);
		buff = miter.addr;
		len = miter.length;

		nbytes -= lzeros;
		lzeros = 0;
	पूर्ण

	miter.consumed = lzeros;
	sg_miter_stop(&miter);
	nbytes -= lzeros;

	वापस tbytes - nbytes;
पूर्ण

अटल काष्ठा rsa_edesc *rsa_edesc_alloc(काष्ठा akcipher_request *req,
					 माप_प्रकार desclen)
अणु
	काष्ठा crypto_akcipher *tfm = crypto_akcipher_reqtfm(req);
	काष्ठा caam_rsa_ctx *ctx = akcipher_tfm_ctx(tfm);
	काष्ठा device *dev = ctx->dev;
	काष्ठा caam_rsa_req_ctx *req_ctx = akcipher_request_ctx(req);
	काष्ठा caam_rsa_key *key = &ctx->key;
	काष्ठा rsa_edesc *edesc;
	gfp_t flags = (req->base.flags & CRYPTO_TFM_REQ_MAY_SLEEP) ?
		       GFP_KERNEL : GFP_ATOMIC;
	पूर्णांक sg_flags = (flags == GFP_ATOMIC) ? SG_MITER_ATOMIC : 0;
	पूर्णांक sec4_sg_index, sec4_sg_len = 0, sec4_sg_bytes;
	पूर्णांक src_nents, dst_nents;
	पूर्णांक mapped_src_nents, mapped_dst_nents;
	अचिन्हित पूर्णांक dअगरf_size = 0;
	पूर्णांक lzeros;

	अगर (req->src_len > key->n_sz) अणु
		/*
		 * strip leading zeros and
		 * वापस the number of zeros to skip
		 */
		lzeros = caam_rsa_count_leading_zeros(req->src, req->src_len -
						      key->n_sz, sg_flags);
		अगर (lzeros < 0)
			वापस ERR_PTR(lzeros);

		req_ctx->fixup_src = scatterwalk_ffwd(req_ctx->src, req->src,
						      lzeros);
		req_ctx->fixup_src_len = req->src_len - lzeros;
	पूर्ण अन्यथा अणु
		/*
		 * input src is less then n key modulus,
		 * so there will be zero padding
		 */
		dअगरf_size = key->n_sz - req->src_len;
		req_ctx->fixup_src = req->src;
		req_ctx->fixup_src_len = req->src_len;
	पूर्ण

	src_nents = sg_nents_क्रम_len(req_ctx->fixup_src,
				     req_ctx->fixup_src_len);
	dst_nents = sg_nents_क्रम_len(req->dst, req->dst_len);

	mapped_src_nents = dma_map_sg(dev, req_ctx->fixup_src, src_nents,
				      DMA_TO_DEVICE);
	अगर (unlikely(!mapped_src_nents)) अणु
		dev_err(dev, "unable to map source\n");
		वापस ERR_PTR(-ENOMEM);
	पूर्ण
	mapped_dst_nents = dma_map_sg(dev, req->dst, dst_nents,
				      DMA_FROM_DEVICE);
	अगर (unlikely(!mapped_dst_nents)) अणु
		dev_err(dev, "unable to map destination\n");
		जाओ src_fail;
	पूर्ण

	अगर (!dअगरf_size && mapped_src_nents == 1)
		sec4_sg_len = 0; /* no need क्रम an input hw s/g table */
	अन्यथा
		sec4_sg_len = mapped_src_nents + !!dअगरf_size;
	sec4_sg_index = sec4_sg_len;

	अगर (mapped_dst_nents > 1)
		sec4_sg_len += pad_sg_nents(mapped_dst_nents);
	अन्यथा
		sec4_sg_len = pad_sg_nents(sec4_sg_len);

	sec4_sg_bytes = sec4_sg_len * माप(काष्ठा sec4_sg_entry);

	/* allocate space क्रम base edesc, hw desc commands and link tables */
	edesc = kzalloc(माप(*edesc) + desclen + sec4_sg_bytes,
			GFP_DMA | flags);
	अगर (!edesc)
		जाओ dst_fail;

	edesc->sec4_sg = (व्योम *)edesc + माप(*edesc) + desclen;
	अगर (dअगरf_size)
		dma_to_sec4_sg_one(edesc->sec4_sg, ctx->padding_dma, dअगरf_size,
				   0);

	अगर (sec4_sg_index)
		sg_to_sec4_sg_last(req_ctx->fixup_src, req_ctx->fixup_src_len,
				   edesc->sec4_sg + !!dअगरf_size, 0);

	अगर (mapped_dst_nents > 1)
		sg_to_sec4_sg_last(req->dst, req->dst_len,
				   edesc->sec4_sg + sec4_sg_index, 0);

	/* Save nents क्रम later use in Job Descriptor */
	edesc->src_nents = src_nents;
	edesc->dst_nents = dst_nents;

	req_ctx->edesc = edesc;

	अगर (!sec4_sg_bytes)
		वापस edesc;

	edesc->mapped_src_nents = mapped_src_nents;
	edesc->mapped_dst_nents = mapped_dst_nents;

	edesc->sec4_sg_dma = dma_map_single(dev, edesc->sec4_sg,
					    sec4_sg_bytes, DMA_TO_DEVICE);
	अगर (dma_mapping_error(dev, edesc->sec4_sg_dma)) अणु
		dev_err(dev, "unable to map S/G table\n");
		जाओ sec4_sg_fail;
	पूर्ण

	edesc->sec4_sg_bytes = sec4_sg_bytes;

	prपूर्णांक_hex_dump_debug("caampkc sec4_sg@" __stringअगरy(__LINE__) ": ",
			     DUMP_PREFIX_ADDRESS, 16, 4, edesc->sec4_sg,
			     edesc->sec4_sg_bytes, 1);

	वापस edesc;

sec4_sg_fail:
	kमुक्त(edesc);
dst_fail:
	dma_unmap_sg(dev, req->dst, dst_nents, DMA_FROM_DEVICE);
src_fail:
	dma_unmap_sg(dev, req_ctx->fixup_src, src_nents, DMA_TO_DEVICE);
	वापस ERR_PTR(-ENOMEM);
पूर्ण

अटल पूर्णांक akcipher_करो_one_req(काष्ठा crypto_engine *engine, व्योम *areq)
अणु
	काष्ठा akcipher_request *req = container_of(areq,
						    काष्ठा akcipher_request,
						    base);
	काष्ठा crypto_akcipher *tfm = crypto_akcipher_reqtfm(req);
	काष्ठा caam_rsa_req_ctx *req_ctx = akcipher_request_ctx(req);
	काष्ठा caam_rsa_ctx *ctx = akcipher_tfm_ctx(tfm);
	काष्ठा device *jrdev = ctx->dev;
	u32 *desc = req_ctx->edesc->hw_desc;
	पूर्णांक ret;

	req_ctx->edesc->bklog = true;

	ret = caam_jr_enqueue(jrdev, desc, req_ctx->akcipher_op_करोne, req);

	अगर (ret != -EINPROGRESS) अणु
		rsa_pub_unmap(jrdev, req_ctx->edesc, req);
		rsa_io_unmap(jrdev, req_ctx->edesc, req);
		kमुक्त(req_ctx->edesc);
	पूर्ण अन्यथा अणु
		ret = 0;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक set_rsa_pub_pdb(काष्ठा akcipher_request *req,
			   काष्ठा rsa_edesc *edesc)
अणु
	काष्ठा crypto_akcipher *tfm = crypto_akcipher_reqtfm(req);
	काष्ठा caam_rsa_req_ctx *req_ctx = akcipher_request_ctx(req);
	काष्ठा caam_rsa_ctx *ctx = akcipher_tfm_ctx(tfm);
	काष्ठा caam_rsa_key *key = &ctx->key;
	काष्ठा device *dev = ctx->dev;
	काष्ठा rsa_pub_pdb *pdb = &edesc->pdb.pub;
	पूर्णांक sec4_sg_index = 0;

	pdb->n_dma = dma_map_single(dev, key->n, key->n_sz, DMA_TO_DEVICE);
	अगर (dma_mapping_error(dev, pdb->n_dma)) अणु
		dev_err(dev, "Unable to map RSA modulus memory\n");
		वापस -ENOMEM;
	पूर्ण

	pdb->e_dma = dma_map_single(dev, key->e, key->e_sz, DMA_TO_DEVICE);
	अगर (dma_mapping_error(dev, pdb->e_dma)) अणु
		dev_err(dev, "Unable to map RSA public exponent memory\n");
		dma_unmap_single(dev, pdb->n_dma, key->n_sz, DMA_TO_DEVICE);
		वापस -ENOMEM;
	पूर्ण

	अगर (edesc->mapped_src_nents > 1) अणु
		pdb->sgf |= RSA_PDB_SGF_F;
		pdb->f_dma = edesc->sec4_sg_dma;
		sec4_sg_index += edesc->mapped_src_nents;
	पूर्ण अन्यथा अणु
		pdb->f_dma = sg_dma_address(req_ctx->fixup_src);
	पूर्ण

	अगर (edesc->mapped_dst_nents > 1) अणु
		pdb->sgf |= RSA_PDB_SGF_G;
		pdb->g_dma = edesc->sec4_sg_dma +
			     sec4_sg_index * माप(काष्ठा sec4_sg_entry);
	पूर्ण अन्यथा अणु
		pdb->g_dma = sg_dma_address(req->dst);
	पूर्ण

	pdb->sgf |= (key->e_sz << RSA_PDB_E_SHIFT) | key->n_sz;
	pdb->f_len = req_ctx->fixup_src_len;

	वापस 0;
पूर्ण

अटल पूर्णांक set_rsa_priv_f1_pdb(काष्ठा akcipher_request *req,
			       काष्ठा rsa_edesc *edesc)
अणु
	काष्ठा crypto_akcipher *tfm = crypto_akcipher_reqtfm(req);
	काष्ठा caam_rsa_ctx *ctx = akcipher_tfm_ctx(tfm);
	काष्ठा caam_rsa_key *key = &ctx->key;
	काष्ठा device *dev = ctx->dev;
	काष्ठा rsa_priv_f1_pdb *pdb = &edesc->pdb.priv_f1;
	पूर्णांक sec4_sg_index = 0;

	pdb->n_dma = dma_map_single(dev, key->n, key->n_sz, DMA_TO_DEVICE);
	अगर (dma_mapping_error(dev, pdb->n_dma)) अणु
		dev_err(dev, "Unable to map modulus memory\n");
		वापस -ENOMEM;
	पूर्ण

	pdb->d_dma = dma_map_single(dev, key->d, key->d_sz, DMA_TO_DEVICE);
	अगर (dma_mapping_error(dev, pdb->d_dma)) अणु
		dev_err(dev, "Unable to map RSA private exponent memory\n");
		dma_unmap_single(dev, pdb->n_dma, key->n_sz, DMA_TO_DEVICE);
		वापस -ENOMEM;
	पूर्ण

	अगर (edesc->mapped_src_nents > 1) अणु
		pdb->sgf |= RSA_PRIV_PDB_SGF_G;
		pdb->g_dma = edesc->sec4_sg_dma;
		sec4_sg_index += edesc->mapped_src_nents;

	पूर्ण अन्यथा अणु
		काष्ठा caam_rsa_req_ctx *req_ctx = akcipher_request_ctx(req);

		pdb->g_dma = sg_dma_address(req_ctx->fixup_src);
	पूर्ण

	अगर (edesc->mapped_dst_nents > 1) अणु
		pdb->sgf |= RSA_PRIV_PDB_SGF_F;
		pdb->f_dma = edesc->sec4_sg_dma +
			     sec4_sg_index * माप(काष्ठा sec4_sg_entry);
	पूर्ण अन्यथा अणु
		pdb->f_dma = sg_dma_address(req->dst);
	पूर्ण

	pdb->sgf |= (key->d_sz << RSA_PDB_D_SHIFT) | key->n_sz;

	वापस 0;
पूर्ण

अटल पूर्णांक set_rsa_priv_f2_pdb(काष्ठा akcipher_request *req,
			       काष्ठा rsa_edesc *edesc)
अणु
	काष्ठा crypto_akcipher *tfm = crypto_akcipher_reqtfm(req);
	काष्ठा caam_rsa_ctx *ctx = akcipher_tfm_ctx(tfm);
	काष्ठा caam_rsa_key *key = &ctx->key;
	काष्ठा device *dev = ctx->dev;
	काष्ठा rsa_priv_f2_pdb *pdb = &edesc->pdb.priv_f2;
	पूर्णांक sec4_sg_index = 0;
	माप_प्रकार p_sz = key->p_sz;
	माप_प्रकार q_sz = key->q_sz;

	pdb->d_dma = dma_map_single(dev, key->d, key->d_sz, DMA_TO_DEVICE);
	अगर (dma_mapping_error(dev, pdb->d_dma)) अणु
		dev_err(dev, "Unable to map RSA private exponent memory\n");
		वापस -ENOMEM;
	पूर्ण

	pdb->p_dma = dma_map_single(dev, key->p, p_sz, DMA_TO_DEVICE);
	अगर (dma_mapping_error(dev, pdb->p_dma)) अणु
		dev_err(dev, "Unable to map RSA prime factor p memory\n");
		जाओ unmap_d;
	पूर्ण

	pdb->q_dma = dma_map_single(dev, key->q, q_sz, DMA_TO_DEVICE);
	अगर (dma_mapping_error(dev, pdb->q_dma)) अणु
		dev_err(dev, "Unable to map RSA prime factor q memory\n");
		जाओ unmap_p;
	पूर्ण

	pdb->पंचांगp1_dma = dma_map_single(dev, key->पंचांगp1, p_sz, DMA_BIसूचीECTIONAL);
	अगर (dma_mapping_error(dev, pdb->पंचांगp1_dma)) अणु
		dev_err(dev, "Unable to map RSA tmp1 memory\n");
		जाओ unmap_q;
	पूर्ण

	pdb->पंचांगp2_dma = dma_map_single(dev, key->पंचांगp2, q_sz, DMA_BIसूचीECTIONAL);
	अगर (dma_mapping_error(dev, pdb->पंचांगp2_dma)) अणु
		dev_err(dev, "Unable to map RSA tmp2 memory\n");
		जाओ unmap_पंचांगp1;
	पूर्ण

	अगर (edesc->mapped_src_nents > 1) अणु
		pdb->sgf |= RSA_PRIV_PDB_SGF_G;
		pdb->g_dma = edesc->sec4_sg_dma;
		sec4_sg_index += edesc->mapped_src_nents;
	पूर्ण अन्यथा अणु
		काष्ठा caam_rsa_req_ctx *req_ctx = akcipher_request_ctx(req);

		pdb->g_dma = sg_dma_address(req_ctx->fixup_src);
	पूर्ण

	अगर (edesc->mapped_dst_nents > 1) अणु
		pdb->sgf |= RSA_PRIV_PDB_SGF_F;
		pdb->f_dma = edesc->sec4_sg_dma +
			     sec4_sg_index * माप(काष्ठा sec4_sg_entry);
	पूर्ण अन्यथा अणु
		pdb->f_dma = sg_dma_address(req->dst);
	पूर्ण

	pdb->sgf |= (key->d_sz << RSA_PDB_D_SHIFT) | key->n_sz;
	pdb->p_q_len = (q_sz << RSA_PDB_Q_SHIFT) | p_sz;

	वापस 0;

unmap_पंचांगp1:
	dma_unmap_single(dev, pdb->पंचांगp1_dma, p_sz, DMA_BIसूचीECTIONAL);
unmap_q:
	dma_unmap_single(dev, pdb->q_dma, q_sz, DMA_TO_DEVICE);
unmap_p:
	dma_unmap_single(dev, pdb->p_dma, p_sz, DMA_TO_DEVICE);
unmap_d:
	dma_unmap_single(dev, pdb->d_dma, key->d_sz, DMA_TO_DEVICE);

	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक set_rsa_priv_f3_pdb(काष्ठा akcipher_request *req,
			       काष्ठा rsa_edesc *edesc)
अणु
	काष्ठा crypto_akcipher *tfm = crypto_akcipher_reqtfm(req);
	काष्ठा caam_rsa_ctx *ctx = akcipher_tfm_ctx(tfm);
	काष्ठा caam_rsa_key *key = &ctx->key;
	काष्ठा device *dev = ctx->dev;
	काष्ठा rsa_priv_f3_pdb *pdb = &edesc->pdb.priv_f3;
	पूर्णांक sec4_sg_index = 0;
	माप_प्रकार p_sz = key->p_sz;
	माप_प्रकार q_sz = key->q_sz;

	pdb->p_dma = dma_map_single(dev, key->p, p_sz, DMA_TO_DEVICE);
	अगर (dma_mapping_error(dev, pdb->p_dma)) अणु
		dev_err(dev, "Unable to map RSA prime factor p memory\n");
		वापस -ENOMEM;
	पूर्ण

	pdb->q_dma = dma_map_single(dev, key->q, q_sz, DMA_TO_DEVICE);
	अगर (dma_mapping_error(dev, pdb->q_dma)) अणु
		dev_err(dev, "Unable to map RSA prime factor q memory\n");
		जाओ unmap_p;
	पूर्ण

	pdb->dp_dma = dma_map_single(dev, key->dp, p_sz, DMA_TO_DEVICE);
	अगर (dma_mapping_error(dev, pdb->dp_dma)) अणु
		dev_err(dev, "Unable to map RSA exponent dp memory\n");
		जाओ unmap_q;
	पूर्ण

	pdb->dq_dma = dma_map_single(dev, key->dq, q_sz, DMA_TO_DEVICE);
	अगर (dma_mapping_error(dev, pdb->dq_dma)) अणु
		dev_err(dev, "Unable to map RSA exponent dq memory\n");
		जाओ unmap_dp;
	पूर्ण

	pdb->c_dma = dma_map_single(dev, key->qinv, p_sz, DMA_TO_DEVICE);
	अगर (dma_mapping_error(dev, pdb->c_dma)) अणु
		dev_err(dev, "Unable to map RSA CRT coefficient qinv memory\n");
		जाओ unmap_dq;
	पूर्ण

	pdb->पंचांगp1_dma = dma_map_single(dev, key->पंचांगp1, p_sz, DMA_BIसूचीECTIONAL);
	अगर (dma_mapping_error(dev, pdb->पंचांगp1_dma)) अणु
		dev_err(dev, "Unable to map RSA tmp1 memory\n");
		जाओ unmap_qinv;
	पूर्ण

	pdb->पंचांगp2_dma = dma_map_single(dev, key->पंचांगp2, q_sz, DMA_BIसूचीECTIONAL);
	अगर (dma_mapping_error(dev, pdb->पंचांगp2_dma)) अणु
		dev_err(dev, "Unable to map RSA tmp2 memory\n");
		जाओ unmap_पंचांगp1;
	पूर्ण

	अगर (edesc->mapped_src_nents > 1) अणु
		pdb->sgf |= RSA_PRIV_PDB_SGF_G;
		pdb->g_dma = edesc->sec4_sg_dma;
		sec4_sg_index += edesc->mapped_src_nents;
	पूर्ण अन्यथा अणु
		काष्ठा caam_rsa_req_ctx *req_ctx = akcipher_request_ctx(req);

		pdb->g_dma = sg_dma_address(req_ctx->fixup_src);
	पूर्ण

	अगर (edesc->mapped_dst_nents > 1) अणु
		pdb->sgf |= RSA_PRIV_PDB_SGF_F;
		pdb->f_dma = edesc->sec4_sg_dma +
			     sec4_sg_index * माप(काष्ठा sec4_sg_entry);
	पूर्ण अन्यथा अणु
		pdb->f_dma = sg_dma_address(req->dst);
	पूर्ण

	pdb->sgf |= key->n_sz;
	pdb->p_q_len = (q_sz << RSA_PDB_Q_SHIFT) | p_sz;

	वापस 0;

unmap_पंचांगp1:
	dma_unmap_single(dev, pdb->पंचांगp1_dma, p_sz, DMA_BIसूचीECTIONAL);
unmap_qinv:
	dma_unmap_single(dev, pdb->c_dma, p_sz, DMA_TO_DEVICE);
unmap_dq:
	dma_unmap_single(dev, pdb->dq_dma, q_sz, DMA_TO_DEVICE);
unmap_dp:
	dma_unmap_single(dev, pdb->dp_dma, p_sz, DMA_TO_DEVICE);
unmap_q:
	dma_unmap_single(dev, pdb->q_dma, q_sz, DMA_TO_DEVICE);
unmap_p:
	dma_unmap_single(dev, pdb->p_dma, p_sz, DMA_TO_DEVICE);

	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक akcipher_enqueue_req(काष्ठा device *jrdev,
				व्योम (*cbk)(काष्ठा device *jrdev, u32 *desc,
					    u32 err, व्योम *context),
				काष्ठा akcipher_request *req)
अणु
	काष्ठा caam_drv_निजी_jr *jrpriv = dev_get_drvdata(jrdev);
	काष्ठा crypto_akcipher *tfm = crypto_akcipher_reqtfm(req);
	काष्ठा caam_rsa_ctx *ctx = akcipher_tfm_ctx(tfm);
	काष्ठा caam_rsa_key *key = &ctx->key;
	काष्ठा caam_rsa_req_ctx *req_ctx = akcipher_request_ctx(req);
	काष्ठा rsa_edesc *edesc = req_ctx->edesc;
	u32 *desc = edesc->hw_desc;
	पूर्णांक ret;

	req_ctx->akcipher_op_करोne = cbk;
	/*
	 * Only the backlog request are sent to crypto-engine since the others
	 * can be handled by CAAM, अगर मुक्त, especially since JR has up to 1024
	 * entries (more than the 10 entries from crypto-engine).
	 */
	अगर (req->base.flags & CRYPTO_TFM_REQ_MAY_BACKLOG)
		ret = crypto_transfer_akcipher_request_to_engine(jrpriv->engine,
								 req);
	अन्यथा
		ret = caam_jr_enqueue(jrdev, desc, cbk, req);

	अगर ((ret != -EINPROGRESS) && (ret != -EBUSY)) अणु
		चयन (key->priv_क्रमm) अणु
		हाल FORM1:
			rsa_priv_f1_unmap(jrdev, edesc, req);
			अवरोध;
		हाल FORM2:
			rsa_priv_f2_unmap(jrdev, edesc, req);
			अवरोध;
		हाल FORM3:
			rsa_priv_f3_unmap(jrdev, edesc, req);
			अवरोध;
		शेष:
			rsa_pub_unmap(jrdev, edesc, req);
		पूर्ण
		rsa_io_unmap(jrdev, edesc, req);
		kमुक्त(edesc);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक caam_rsa_enc(काष्ठा akcipher_request *req)
अणु
	काष्ठा crypto_akcipher *tfm = crypto_akcipher_reqtfm(req);
	काष्ठा caam_rsa_ctx *ctx = akcipher_tfm_ctx(tfm);
	काष्ठा caam_rsa_key *key = &ctx->key;
	काष्ठा device *jrdev = ctx->dev;
	काष्ठा rsa_edesc *edesc;
	पूर्णांक ret;

	अगर (unlikely(!key->n || !key->e))
		वापस -EINVAL;

	अगर (req->dst_len < key->n_sz) अणु
		req->dst_len = key->n_sz;
		dev_err(jrdev, "Output buffer length less than parameter n\n");
		वापस -EOVERFLOW;
	पूर्ण

	/* Allocate extended descriptor */
	edesc = rsa_edesc_alloc(req, DESC_RSA_PUB_LEN);
	अगर (IS_ERR(edesc))
		वापस PTR_ERR(edesc);

	/* Set RSA Encrypt Protocol Data Block */
	ret = set_rsa_pub_pdb(req, edesc);
	अगर (ret)
		जाओ init_fail;

	/* Initialize Job Descriptor */
	init_rsa_pub_desc(edesc->hw_desc, &edesc->pdb.pub);

	वापस akcipher_enqueue_req(jrdev, rsa_pub_करोne, req);

init_fail:
	rsa_io_unmap(jrdev, edesc, req);
	kमुक्त(edesc);
	वापस ret;
पूर्ण

अटल पूर्णांक caam_rsa_dec_priv_f1(काष्ठा akcipher_request *req)
अणु
	काष्ठा crypto_akcipher *tfm = crypto_akcipher_reqtfm(req);
	काष्ठा caam_rsa_ctx *ctx = akcipher_tfm_ctx(tfm);
	काष्ठा device *jrdev = ctx->dev;
	काष्ठा rsa_edesc *edesc;
	पूर्णांक ret;

	/* Allocate extended descriptor */
	edesc = rsa_edesc_alloc(req, DESC_RSA_PRIV_F1_LEN);
	अगर (IS_ERR(edesc))
		वापस PTR_ERR(edesc);

	/* Set RSA Decrypt Protocol Data Block - Private Key Form #1 */
	ret = set_rsa_priv_f1_pdb(req, edesc);
	अगर (ret)
		जाओ init_fail;

	/* Initialize Job Descriptor */
	init_rsa_priv_f1_desc(edesc->hw_desc, &edesc->pdb.priv_f1);

	वापस akcipher_enqueue_req(jrdev, rsa_priv_f_करोne, req);

init_fail:
	rsa_io_unmap(jrdev, edesc, req);
	kमुक्त(edesc);
	वापस ret;
पूर्ण

अटल पूर्णांक caam_rsa_dec_priv_f2(काष्ठा akcipher_request *req)
अणु
	काष्ठा crypto_akcipher *tfm = crypto_akcipher_reqtfm(req);
	काष्ठा caam_rsa_ctx *ctx = akcipher_tfm_ctx(tfm);
	काष्ठा device *jrdev = ctx->dev;
	काष्ठा rsa_edesc *edesc;
	पूर्णांक ret;

	/* Allocate extended descriptor */
	edesc = rsa_edesc_alloc(req, DESC_RSA_PRIV_F2_LEN);
	अगर (IS_ERR(edesc))
		वापस PTR_ERR(edesc);

	/* Set RSA Decrypt Protocol Data Block - Private Key Form #2 */
	ret = set_rsa_priv_f2_pdb(req, edesc);
	अगर (ret)
		जाओ init_fail;

	/* Initialize Job Descriptor */
	init_rsa_priv_f2_desc(edesc->hw_desc, &edesc->pdb.priv_f2);

	वापस akcipher_enqueue_req(jrdev, rsa_priv_f_करोne, req);

init_fail:
	rsa_io_unmap(jrdev, edesc, req);
	kमुक्त(edesc);
	वापस ret;
पूर्ण

अटल पूर्णांक caam_rsa_dec_priv_f3(काष्ठा akcipher_request *req)
अणु
	काष्ठा crypto_akcipher *tfm = crypto_akcipher_reqtfm(req);
	काष्ठा caam_rsa_ctx *ctx = akcipher_tfm_ctx(tfm);
	काष्ठा device *jrdev = ctx->dev;
	काष्ठा rsa_edesc *edesc;
	पूर्णांक ret;

	/* Allocate extended descriptor */
	edesc = rsa_edesc_alloc(req, DESC_RSA_PRIV_F3_LEN);
	अगर (IS_ERR(edesc))
		वापस PTR_ERR(edesc);

	/* Set RSA Decrypt Protocol Data Block - Private Key Form #3 */
	ret = set_rsa_priv_f3_pdb(req, edesc);
	अगर (ret)
		जाओ init_fail;

	/* Initialize Job Descriptor */
	init_rsa_priv_f3_desc(edesc->hw_desc, &edesc->pdb.priv_f3);

	वापस akcipher_enqueue_req(jrdev, rsa_priv_f_करोne, req);

init_fail:
	rsa_io_unmap(jrdev, edesc, req);
	kमुक्त(edesc);
	वापस ret;
पूर्ण

अटल पूर्णांक caam_rsa_dec(काष्ठा akcipher_request *req)
अणु
	काष्ठा crypto_akcipher *tfm = crypto_akcipher_reqtfm(req);
	काष्ठा caam_rsa_ctx *ctx = akcipher_tfm_ctx(tfm);
	काष्ठा caam_rsa_key *key = &ctx->key;
	पूर्णांक ret;

	अगर (unlikely(!key->n || !key->d))
		वापस -EINVAL;

	अगर (req->dst_len < key->n_sz) अणु
		req->dst_len = key->n_sz;
		dev_err(ctx->dev, "Output buffer length less than parameter n\n");
		वापस -EOVERFLOW;
	पूर्ण

	अगर (key->priv_क्रमm == FORM3)
		ret = caam_rsa_dec_priv_f3(req);
	अन्यथा अगर (key->priv_क्रमm == FORM2)
		ret = caam_rsa_dec_priv_f2(req);
	अन्यथा
		ret = caam_rsa_dec_priv_f1(req);

	वापस ret;
पूर्ण

अटल व्योम caam_rsa_मुक्त_key(काष्ठा caam_rsa_key *key)
अणु
	kमुक्त_sensitive(key->d);
	kमुक्त_sensitive(key->p);
	kमुक्त_sensitive(key->q);
	kमुक्त_sensitive(key->dp);
	kमुक्त_sensitive(key->dq);
	kमुक्त_sensitive(key->qinv);
	kमुक्त_sensitive(key->पंचांगp1);
	kमुक्त_sensitive(key->पंचांगp2);
	kमुक्त(key->e);
	kमुक्त(key->n);
	स_रखो(key, 0, माप(*key));
पूर्ण

अटल व्योम caam_rsa_drop_leading_zeros(स्थिर u8 **ptr, माप_प्रकार *nbytes)
अणु
	जबतक (!**ptr && *nbytes) अणु
		(*ptr)++;
		(*nbytes)--;
	पूर्ण
पूर्ण

/**
 * caam_पढ़ो_rsa_crt - Used क्रम पढ़ोing dP, dQ, qInv CRT members.
 * dP, dQ and qInv could decode to less than corresponding p, q length, as the
 * BER-encoding requires that the minimum number of bytes be used to encode the
 * पूर्णांकeger. dP, dQ, qInv decoded values have to be zero-padded to appropriate
 * length.
 *
 * @ptr   : poपूर्णांकer to अणुdP, dQ, qInvपूर्ण CRT member
 * @nbytes: length in bytes of अणुdP, dQ, qInvपूर्ण CRT member
 * @dstlen: length in bytes of corresponding p or q prime factor
 */
अटल u8 *caam_पढ़ो_rsa_crt(स्थिर u8 *ptr, माप_प्रकार nbytes, माप_प्रकार dstlen)
अणु
	u8 *dst;

	caam_rsa_drop_leading_zeros(&ptr, &nbytes);
	अगर (!nbytes)
		वापस शून्य;

	dst = kzalloc(dstlen, GFP_DMA | GFP_KERNEL);
	अगर (!dst)
		वापस शून्य;

	स_नकल(dst + (dstlen - nbytes), ptr, nbytes);

	वापस dst;
पूर्ण

/**
 * caam_पढ़ो_raw_data - Read a raw byte stream as a positive पूर्णांकeger.
 * The function skips buffer's leading zeros, copies the reमुख्यed data
 * to a buffer allocated in the GFP_DMA | GFP_KERNEL zone and वापसs
 * the address of the new buffer.
 *
 * @buf   : The data to पढ़ो
 * @nbytes: The amount of data to पढ़ो
 */
अटल अंतरभूत u8 *caam_पढ़ो_raw_data(स्थिर u8 *buf, माप_प्रकार *nbytes)
अणु

	caam_rsa_drop_leading_zeros(&buf, nbytes);
	अगर (!*nbytes)
		वापस शून्य;

	वापस kmemdup(buf, *nbytes, GFP_DMA | GFP_KERNEL);
पूर्ण

अटल पूर्णांक caam_rsa_check_key_length(अचिन्हित पूर्णांक len)
अणु
	अगर (len > 4096)
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल पूर्णांक caam_rsa_set_pub_key(काष्ठा crypto_akcipher *tfm, स्थिर व्योम *key,
				अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा caam_rsa_ctx *ctx = akcipher_tfm_ctx(tfm);
	काष्ठा rsa_key raw_key = अणुशून्यपूर्ण;
	काष्ठा caam_rsa_key *rsa_key = &ctx->key;
	पूर्णांक ret;

	/* Free the old RSA key अगर any */
	caam_rsa_मुक्त_key(rsa_key);

	ret = rsa_parse_pub_key(&raw_key, key, keylen);
	अगर (ret)
		वापस ret;

	/* Copy key in DMA zone */
	rsa_key->e = kmemdup(raw_key.e, raw_key.e_sz, GFP_DMA | GFP_KERNEL);
	अगर (!rsa_key->e)
		जाओ err;

	/*
	 * Skip leading zeros and copy the positive पूर्णांकeger to a buffer
	 * allocated in the GFP_DMA | GFP_KERNEL zone. The decryption descriptor
	 * expects a positive पूर्णांकeger क्रम the RSA modulus and uses its length as
	 * decryption output length.
	 */
	rsa_key->n = caam_पढ़ो_raw_data(raw_key.n, &raw_key.n_sz);
	अगर (!rsa_key->n)
		जाओ err;

	अगर (caam_rsa_check_key_length(raw_key.n_sz << 3)) अणु
		caam_rsa_मुक्त_key(rsa_key);
		वापस -EINVAL;
	पूर्ण

	rsa_key->e_sz = raw_key.e_sz;
	rsa_key->n_sz = raw_key.n_sz;

	वापस 0;
err:
	caam_rsa_मुक्त_key(rsa_key);
	वापस -ENOMEM;
पूर्ण

अटल व्योम caam_rsa_set_priv_key_क्रमm(काष्ठा caam_rsa_ctx *ctx,
				       काष्ठा rsa_key *raw_key)
अणु
	काष्ठा caam_rsa_key *rsa_key = &ctx->key;
	माप_प्रकार p_sz = raw_key->p_sz;
	माप_प्रकार q_sz = raw_key->q_sz;

	rsa_key->p = caam_पढ़ो_raw_data(raw_key->p, &p_sz);
	अगर (!rsa_key->p)
		वापस;
	rsa_key->p_sz = p_sz;

	rsa_key->q = caam_पढ़ो_raw_data(raw_key->q, &q_sz);
	अगर (!rsa_key->q)
		जाओ मुक्त_p;
	rsa_key->q_sz = q_sz;

	rsa_key->पंचांगp1 = kzalloc(raw_key->p_sz, GFP_DMA | GFP_KERNEL);
	अगर (!rsa_key->पंचांगp1)
		जाओ मुक्त_q;

	rsa_key->पंचांगp2 = kzalloc(raw_key->q_sz, GFP_DMA | GFP_KERNEL);
	अगर (!rsa_key->पंचांगp2)
		जाओ मुक्त_पंचांगp1;

	rsa_key->priv_क्रमm = FORM2;

	rsa_key->dp = caam_पढ़ो_rsa_crt(raw_key->dp, raw_key->dp_sz, p_sz);
	अगर (!rsa_key->dp)
		जाओ मुक्त_पंचांगp2;

	rsa_key->dq = caam_पढ़ो_rsa_crt(raw_key->dq, raw_key->dq_sz, q_sz);
	अगर (!rsa_key->dq)
		जाओ मुक्त_dp;

	rsa_key->qinv = caam_पढ़ो_rsa_crt(raw_key->qinv, raw_key->qinv_sz,
					  q_sz);
	अगर (!rsa_key->qinv)
		जाओ मुक्त_dq;

	rsa_key->priv_क्रमm = FORM3;

	वापस;

मुक्त_dq:
	kमुक्त_sensitive(rsa_key->dq);
मुक्त_dp:
	kमुक्त_sensitive(rsa_key->dp);
मुक्त_पंचांगp2:
	kमुक्त_sensitive(rsa_key->पंचांगp2);
मुक्त_पंचांगp1:
	kमुक्त_sensitive(rsa_key->पंचांगp1);
मुक्त_q:
	kमुक्त_sensitive(rsa_key->q);
मुक्त_p:
	kमुक्त_sensitive(rsa_key->p);
पूर्ण

अटल पूर्णांक caam_rsa_set_priv_key(काष्ठा crypto_akcipher *tfm, स्थिर व्योम *key,
				 अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा caam_rsa_ctx *ctx = akcipher_tfm_ctx(tfm);
	काष्ठा rsa_key raw_key = अणुशून्यपूर्ण;
	काष्ठा caam_rsa_key *rsa_key = &ctx->key;
	पूर्णांक ret;

	/* Free the old RSA key अगर any */
	caam_rsa_मुक्त_key(rsa_key);

	ret = rsa_parse_priv_key(&raw_key, key, keylen);
	अगर (ret)
		वापस ret;

	/* Copy key in DMA zone */
	rsa_key->d = kmemdup(raw_key.d, raw_key.d_sz, GFP_DMA | GFP_KERNEL);
	अगर (!rsa_key->d)
		जाओ err;

	rsa_key->e = kmemdup(raw_key.e, raw_key.e_sz, GFP_DMA | GFP_KERNEL);
	अगर (!rsa_key->e)
		जाओ err;

	/*
	 * Skip leading zeros and copy the positive पूर्णांकeger to a buffer
	 * allocated in the GFP_DMA | GFP_KERNEL zone. The decryption descriptor
	 * expects a positive पूर्णांकeger क्रम the RSA modulus and uses its length as
	 * decryption output length.
	 */
	rsa_key->n = caam_पढ़ो_raw_data(raw_key.n, &raw_key.n_sz);
	अगर (!rsa_key->n)
		जाओ err;

	अगर (caam_rsa_check_key_length(raw_key.n_sz << 3)) अणु
		caam_rsa_मुक्त_key(rsa_key);
		वापस -EINVAL;
	पूर्ण

	rsa_key->d_sz = raw_key.d_sz;
	rsa_key->e_sz = raw_key.e_sz;
	rsa_key->n_sz = raw_key.n_sz;

	caam_rsa_set_priv_key_क्रमm(ctx, &raw_key);

	वापस 0;

err:
	caam_rsa_मुक्त_key(rsa_key);
	वापस -ENOMEM;
पूर्ण

अटल अचिन्हित पूर्णांक caam_rsa_max_size(काष्ठा crypto_akcipher *tfm)
अणु
	काष्ठा caam_rsa_ctx *ctx = akcipher_tfm_ctx(tfm);

	वापस ctx->key.n_sz;
पूर्ण

/* Per session pkc's driver context creation function */
अटल पूर्णांक caam_rsa_init_tfm(काष्ठा crypto_akcipher *tfm)
अणु
	काष्ठा caam_rsa_ctx *ctx = akcipher_tfm_ctx(tfm);

	ctx->dev = caam_jr_alloc();

	अगर (IS_ERR(ctx->dev)) अणु
		pr_err("Job Ring Device allocation for transform failed\n");
		वापस PTR_ERR(ctx->dev);
	पूर्ण

	ctx->padding_dma = dma_map_single(ctx->dev, zero_buffer,
					  CAAM_RSA_MAX_INPUT_SIZE - 1,
					  DMA_TO_DEVICE);
	अगर (dma_mapping_error(ctx->dev, ctx->padding_dma)) अणु
		dev_err(ctx->dev, "unable to map padding\n");
		caam_jr_मुक्त(ctx->dev);
		वापस -ENOMEM;
	पूर्ण

	ctx->enginectx.op.करो_one_request = akcipher_करो_one_req;

	वापस 0;
पूर्ण

/* Per session pkc's driver context cleanup function */
अटल व्योम caam_rsa_निकास_tfm(काष्ठा crypto_akcipher *tfm)
अणु
	काष्ठा caam_rsa_ctx *ctx = akcipher_tfm_ctx(tfm);
	काष्ठा caam_rsa_key *key = &ctx->key;

	dma_unmap_single(ctx->dev, ctx->padding_dma, CAAM_RSA_MAX_INPUT_SIZE -
			 1, DMA_TO_DEVICE);
	caam_rsa_मुक्त_key(key);
	caam_jr_मुक्त(ctx->dev);
पूर्ण

अटल काष्ठा caam_akcipher_alg caam_rsa = अणु
	.akcipher = अणु
		.encrypt = caam_rsa_enc,
		.decrypt = caam_rsa_dec,
		.set_pub_key = caam_rsa_set_pub_key,
		.set_priv_key = caam_rsa_set_priv_key,
		.max_size = caam_rsa_max_size,
		.init = caam_rsa_init_tfm,
		.निकास = caam_rsa_निकास_tfm,
		.reqsize = माप(काष्ठा caam_rsa_req_ctx),
		.base = अणु
			.cra_name = "rsa",
			.cra_driver_name = "rsa-caam",
			.cra_priority = 3000,
			.cra_module = THIS_MODULE,
			.cra_ctxsize = माप(काष्ठा caam_rsa_ctx),
		पूर्ण,
	पूर्ण
पूर्ण;

/* Public Key Cryptography module initialization handler */
पूर्णांक caam_pkc_init(काष्ठा device *ctrldev)
अणु
	काष्ठा caam_drv_निजी *priv = dev_get_drvdata(ctrldev);
	u32 pk_inst;
	पूर्णांक err;
	init_करोne = false;

	/* Determine खुला key hardware accelerator presence. */
	अगर (priv->era < 10)
		pk_inst = (rd_reg32(&priv->ctrl->perfmon.cha_num_ls) &
			   CHA_ID_LS_PK_MASK) >> CHA_ID_LS_PK_SHIFT;
	अन्यथा
		pk_inst = rd_reg32(&priv->ctrl->vreg.pkha) & CHA_VER_NUM_MASK;

	/* Do not रेजिस्टर algorithms अगर PKHA is not present. */
	अगर (!pk_inst)
		वापस 0;

	/* allocate zero buffer, used क्रम padding input */
	zero_buffer = kzalloc(CAAM_RSA_MAX_INPUT_SIZE - 1, GFP_DMA |
			      GFP_KERNEL);
	अगर (!zero_buffer)
		वापस -ENOMEM;

	err = crypto_रेजिस्टर_akcipher(&caam_rsa.akcipher);

	अगर (err) अणु
		kमुक्त(zero_buffer);
		dev_warn(ctrldev, "%s alg registration failed\n",
			 caam_rsa.akcipher.base.cra_driver_name);
	पूर्ण अन्यथा अणु
		init_करोne = true;
		caam_rsa.रेजिस्टरed = true;
		dev_info(ctrldev, "caam pkc algorithms registered in /proc/crypto\n");
	पूर्ण

	वापस err;
पूर्ण

व्योम caam_pkc_निकास(व्योम)
अणु
	अगर (!init_करोne)
		वापस;

	अगर (caam_rsa.रेजिस्टरed)
		crypto_unरेजिस्टर_akcipher(&caam_rsa.akcipher);

	kमुक्त(zero_buffer);
पूर्ण
