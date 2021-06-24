<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * caam - Freescale FSL CAAM support क्रम hw_अक्रमom
 *
 * Copyright 2011 Freescale Semiconductor, Inc.
 * Copyright 2018-2019 NXP
 *
 * Based on caamalg.c crypto API driver.
 *
 */

#समावेश <linux/hw_अक्रमom.h>
#समावेश <linux/completion.h>
#समावेश <linux/atomic.h>
#समावेश <linux/kfअगरo.h>

#समावेश "compat.h"

#समावेश "regs.h"
#समावेश "intern.h"
#समावेश "desc_constr.h"
#समावेश "jr.h"
#समावेश "error.h"

#घोषणा CAAM_RNG_MAX_FIFO_STORE_SIZE	16

/*
 * Length of used descriptors, see caam_init_desc()
 */
#घोषणा CAAM_RNG_DESC_LEN (CAAM_CMD_SZ +				\
			   CAAM_CMD_SZ +				\
			   CAAM_CMD_SZ + CAAM_PTR_SZ_MAX)

/* rng per-device context */
काष्ठा caam_rng_ctx अणु
	काष्ठा hwrng rng;
	काष्ठा device *jrdev;
	काष्ठा device *ctrldev;
	व्योम *desc_async;
	व्योम *desc_sync;
	काष्ठा work_काष्ठा worker;
	काष्ठा kfअगरo fअगरo;
पूर्ण;

काष्ठा caam_rng_job_ctx अणु
	काष्ठा completion *करोne;
	पूर्णांक *err;
पूर्ण;

अटल काष्ठा caam_rng_ctx *to_caam_rng_ctx(काष्ठा hwrng *r)
अणु
	वापस (काष्ठा caam_rng_ctx *)r->priv;
पूर्ण

अटल व्योम caam_rng_करोne(काष्ठा device *jrdev, u32 *desc, u32 err,
			  व्योम *context)
अणु
	काष्ठा caam_rng_job_ctx *jctx = context;

	अगर (err)
		*jctx->err = caam_jr_strstatus(jrdev, err);

	complete(jctx->करोne);
पूर्ण

अटल u32 *caam_init_desc(u32 *desc, dma_addr_t dst_dma)
अणु
	init_job_desc(desc, 0);	/* + 1 cmd_sz */
	/* Generate अक्रमom bytes: + 1 cmd_sz */
	append_operation(desc, OP_ALG_ALGSEL_RNG | OP_TYPE_CLASS1_ALG |
			 OP_ALG_PR_ON);
	/* Store bytes: + 1 cmd_sz + caam_ptr_sz  */
	append_fअगरo_store(desc, dst_dma,
			  CAAM_RNG_MAX_FIFO_STORE_SIZE, FIFOST_TYPE_RNGSTORE);

	prपूर्णांक_hex_dump_debug("rng job desc@: ", DUMP_PREFIX_ADDRESS,
			     16, 4, desc, desc_bytes(desc), 1);

	वापस desc;
पूर्ण

अटल पूर्णांक caam_rng_पढ़ो_one(काष्ठा device *jrdev,
			     व्योम *dst, पूर्णांक len,
			     व्योम *desc,
			     काष्ठा completion *करोne)
अणु
	dma_addr_t dst_dma;
	पूर्णांक err, ret = 0;
	काष्ठा caam_rng_job_ctx jctx = अणु
		.करोne = करोne,
		.err  = &ret,
	पूर्ण;

	len = CAAM_RNG_MAX_FIFO_STORE_SIZE;

	dst_dma = dma_map_single(jrdev, dst, len, DMA_FROM_DEVICE);
	अगर (dma_mapping_error(jrdev, dst_dma)) अणु
		dev_err(jrdev, "unable to map destination memory\n");
		वापस -ENOMEM;
	पूर्ण

	init_completion(करोne);
	err = caam_jr_enqueue(jrdev,
			      caam_init_desc(desc, dst_dma),
			      caam_rng_करोne, &jctx);
	अगर (err == -EINPROGRESS) अणु
		रुको_क्रम_completion(करोne);
		err = 0;
	पूर्ण

	dma_unmap_single(jrdev, dst_dma, len, DMA_FROM_DEVICE);

	वापस err ?: (ret ?: len);
पूर्ण

अटल व्योम caam_rng_fill_async(काष्ठा caam_rng_ctx *ctx)
अणु
	काष्ठा scatterlist sg[1];
	काष्ठा completion करोne;
	पूर्णांक len, nents;

	sg_init_table(sg, ARRAY_SIZE(sg));
	nents = kfअगरo_dma_in_prepare(&ctx->fअगरo, sg, ARRAY_SIZE(sg),
				     CAAM_RNG_MAX_FIFO_STORE_SIZE);
	अगर (!nents)
		वापस;

	len = caam_rng_पढ़ो_one(ctx->jrdev, sg_virt(&sg[0]),
				sg[0].length,
				ctx->desc_async,
				&करोne);
	अगर (len < 0)
		वापस;

	kfअगरo_dma_in_finish(&ctx->fअगरo, len);
पूर्ण

अटल व्योम caam_rng_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा caam_rng_ctx *ctx = container_of(work, काष्ठा caam_rng_ctx,
						worker);
	caam_rng_fill_async(ctx);
पूर्ण

अटल पूर्णांक caam_पढ़ो(काष्ठा hwrng *rng, व्योम *dst, माप_प्रकार max, bool रुको)
अणु
	काष्ठा caam_rng_ctx *ctx = to_caam_rng_ctx(rng);
	पूर्णांक out;

	अगर (रुको) अणु
		काष्ठा completion करोne;

		वापस caam_rng_पढ़ो_one(ctx->jrdev, dst, max,
					 ctx->desc_sync, &करोne);
	पूर्ण

	out = kfअगरo_out(&ctx->fअगरo, dst, max);
	अगर (kfअगरo_is_empty(&ctx->fअगरo))
		schedule_work(&ctx->worker);

	वापस out;
पूर्ण

अटल व्योम caam_cleanup(काष्ठा hwrng *rng)
अणु
	काष्ठा caam_rng_ctx *ctx = to_caam_rng_ctx(rng);

	flush_work(&ctx->worker);
	caam_jr_मुक्त(ctx->jrdev);
	kfअगरo_मुक्त(&ctx->fअगरo);
पूर्ण

अटल पूर्णांक caam_init(काष्ठा hwrng *rng)
अणु
	काष्ठा caam_rng_ctx *ctx = to_caam_rng_ctx(rng);
	पूर्णांक err;

	ctx->desc_sync = devm_kzalloc(ctx->ctrldev, CAAM_RNG_DESC_LEN,
				      GFP_DMA | GFP_KERNEL);
	अगर (!ctx->desc_sync)
		वापस -ENOMEM;

	ctx->desc_async = devm_kzalloc(ctx->ctrldev, CAAM_RNG_DESC_LEN,
				       GFP_DMA | GFP_KERNEL);
	अगर (!ctx->desc_async)
		वापस -ENOMEM;

	अगर (kfअगरo_alloc(&ctx->fअगरo, CAAM_RNG_MAX_FIFO_STORE_SIZE,
			GFP_DMA | GFP_KERNEL))
		वापस -ENOMEM;

	INIT_WORK(&ctx->worker, caam_rng_worker);

	ctx->jrdev = caam_jr_alloc();
	err = PTR_ERR_OR_ZERO(ctx->jrdev);
	अगर (err) अणु
		kfअगरo_मुक्त(&ctx->fअगरo);
		pr_err("Job Ring Device allocation for transform failed\n");
		वापस err;
	पूर्ण

	/*
	 * Fill async buffer to have early अक्रमomness data क्रम
	 * hw_अक्रमom
	 */
	caam_rng_fill_async(ctx);

	वापस 0;
पूर्ण

पूर्णांक caam_rng_init(काष्ठा device *ctrldev);

व्योम caam_rng_निकास(काष्ठा device *ctrldev)
अणु
	devres_release_group(ctrldev, caam_rng_init);
पूर्ण

पूर्णांक caam_rng_init(काष्ठा device *ctrldev)
अणु
	काष्ठा caam_rng_ctx *ctx;
	u32 rng_inst;
	काष्ठा caam_drv_निजी *priv = dev_get_drvdata(ctrldev);
	पूर्णांक ret;

	/* Check क्रम an instantiated RNG beक्रमe registration */
	अगर (priv->era < 10)
		rng_inst = (rd_reg32(&priv->ctrl->perfmon.cha_num_ls) &
			    CHA_ID_LS_RNG_MASK) >> CHA_ID_LS_RNG_SHIFT;
	अन्यथा
		rng_inst = rd_reg32(&priv->ctrl->vreg.rng) & CHA_VER_NUM_MASK;

	अगर (!rng_inst)
		वापस 0;

	अगर (!devres_खोलो_group(ctrldev, caam_rng_init, GFP_KERNEL))
		वापस -ENOMEM;

	ctx = devm_kzalloc(ctrldev, माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	ctx->ctrldev = ctrldev;

	ctx->rng.name    = "rng-caam";
	ctx->rng.init    = caam_init;
	ctx->rng.cleanup = caam_cleanup;
	ctx->rng.पढ़ो    = caam_पढ़ो;
	ctx->rng.priv    = (अचिन्हित दीर्घ)ctx;
	ctx->rng.quality = 1024;

	dev_info(ctrldev, "registering rng-caam\n");

	ret = devm_hwrng_रेजिस्टर(ctrldev, &ctx->rng);
	अगर (ret) अणु
		caam_rng_निकास(ctrldev);
		वापस ret;
	पूर्ण

	devres_बंद_group(ctrldev, caam_rng_init);
	वापस 0;
पूर्ण
