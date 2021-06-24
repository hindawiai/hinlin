<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Support क्रम Marvell's Cryptographic Engine and Security Accelerator (CESA)
 * that can be found on the following platक्रमm: Orion, Kirkwood, Armada. This
 * driver supports the TDMA engine on platक्रमms on which it is available.
 *
 * Author: Boris Brezillon <boris.brezillon@मुक्त-electrons.com>
 * Author: Arnaud Ebalard <arno@natisbad.org>
 *
 * This work is based on an initial version written by
 * Sebastian Andrzej Siewior < sebastian at अवरोधpoपूर्णांक करोt cc >
 */

#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/genभाग.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/mbus.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/clk.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of_irq.h>

#समावेश "cesa.h"

/* Limit of the crypto queue beक्रमe reaching the backlog */
#घोषणा CESA_CRYPTO_DEFAULT_MAX_QLEN 128

काष्ठा mv_cesa_dev *cesa_dev;

काष्ठा crypto_async_request *
mv_cesa_dequeue_req_locked(काष्ठा mv_cesa_engine *engine,
			   काष्ठा crypto_async_request **backlog)
अणु
	काष्ठा crypto_async_request *req;

	*backlog = crypto_get_backlog(&engine->queue);
	req = crypto_dequeue_request(&engine->queue);

	अगर (!req)
		वापस शून्य;

	वापस req;
पूर्ण

अटल व्योम mv_cesa_rearm_engine(काष्ठा mv_cesa_engine *engine)
अणु
	काष्ठा crypto_async_request *req = शून्य, *backlog = शून्य;
	काष्ठा mv_cesa_ctx *ctx;


	spin_lock_bh(&engine->lock);
	अगर (!engine->req) अणु
		req = mv_cesa_dequeue_req_locked(engine, &backlog);
		engine->req = req;
	पूर्ण
	spin_unlock_bh(&engine->lock);

	अगर (!req)
		वापस;

	अगर (backlog)
		backlog->complete(backlog, -EINPROGRESS);

	ctx = crypto_tfm_ctx(req->tfm);
	ctx->ops->step(req);
पूर्ण

अटल पूर्णांक mv_cesa_std_process(काष्ठा mv_cesa_engine *engine, u32 status)
अणु
	काष्ठा crypto_async_request *req;
	काष्ठा mv_cesa_ctx *ctx;
	पूर्णांक res;

	req = engine->req;
	ctx = crypto_tfm_ctx(req->tfm);
	res = ctx->ops->process(req, status);

	अगर (res == 0) अणु
		ctx->ops->complete(req);
		mv_cesa_engine_enqueue_complete_request(engine, req);
	पूर्ण अन्यथा अगर (res == -EINPROGRESS) अणु
		ctx->ops->step(req);
	पूर्ण

	वापस res;
पूर्ण

अटल पूर्णांक mv_cesa_पूर्णांक_process(काष्ठा mv_cesa_engine *engine, u32 status)
अणु
	अगर (engine->chain.first && engine->chain.last)
		वापस mv_cesa_tdma_process(engine, status);

	वापस mv_cesa_std_process(engine, status);
पूर्ण

अटल अंतरभूत व्योम
mv_cesa_complete_req(काष्ठा mv_cesa_ctx *ctx, काष्ठा crypto_async_request *req,
		     पूर्णांक res)
अणु
	ctx->ops->cleanup(req);
	local_bh_disable();
	req->complete(req, res);
	local_bh_enable();
पूर्ण

अटल irqवापस_t mv_cesa_पूर्णांक(पूर्णांक irq, व्योम *priv)
अणु
	काष्ठा mv_cesa_engine *engine = priv;
	काष्ठा crypto_async_request *req;
	काष्ठा mv_cesa_ctx *ctx;
	u32 status, mask;
	irqवापस_t ret = IRQ_NONE;

	जबतक (true) अणु
		पूर्णांक res;

		mask = mv_cesa_get_पूर्णांक_mask(engine);
		status = पढ़ोl(engine->regs + CESA_SA_INT_STATUS);

		अगर (!(status & mask))
			अवरोध;

		/*
		 * TODO: aव्योम clearing the FPGA_INT_STATUS अगर this not
		 * relevant on some platक्रमms.
		 */
		ग_लिखोl(~status, engine->regs + CESA_SA_FPGA_INT_STATUS);
		ग_लिखोl(~status, engine->regs + CESA_SA_INT_STATUS);

		/* Process fetched requests */
		res = mv_cesa_पूर्णांक_process(engine, status & mask);
		ret = IRQ_HANDLED;

		spin_lock_bh(&engine->lock);
		req = engine->req;
		अगर (res != -EINPROGRESS)
			engine->req = शून्य;
		spin_unlock_bh(&engine->lock);

		ctx = crypto_tfm_ctx(req->tfm);

		अगर (res && res != -EINPROGRESS)
			mv_cesa_complete_req(ctx, req, res);

		/* Launch the next pending request */
		mv_cesa_rearm_engine(engine);

		/* Iterate over the complete queue */
		जबतक (true) अणु
			req = mv_cesa_engine_dequeue_complete_request(engine);
			अगर (!req)
				अवरोध;

			ctx = crypto_tfm_ctx(req->tfm);
			mv_cesa_complete_req(ctx, req, 0);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक mv_cesa_queue_req(काष्ठा crypto_async_request *req,
		      काष्ठा mv_cesa_req *creq)
अणु
	पूर्णांक ret;
	काष्ठा mv_cesa_engine *engine = creq->engine;

	spin_lock_bh(&engine->lock);
	ret = crypto_enqueue_request(&engine->queue, req);
	अगर ((mv_cesa_req_get_type(creq) == CESA_DMA_REQ) &&
	    (ret == -EINPROGRESS || ret == -EBUSY))
		mv_cesa_tdma_chain(engine, creq);
	spin_unlock_bh(&engine->lock);

	अगर (ret != -EINPROGRESS)
		वापस ret;

	mv_cesa_rearm_engine(engine);

	वापस -EINPROGRESS;
पूर्ण

अटल पूर्णांक mv_cesa_add_algs(काष्ठा mv_cesa_dev *cesa)
अणु
	पूर्णांक ret;
	पूर्णांक i, j;

	क्रम (i = 0; i < cesa->caps->ncipher_algs; i++) अणु
		ret = crypto_रेजिस्टर_skcipher(cesa->caps->cipher_algs[i]);
		अगर (ret)
			जाओ err_unरेजिस्टर_crypto;
	पूर्ण

	क्रम (i = 0; i < cesa->caps->nahash_algs; i++) अणु
		ret = crypto_रेजिस्टर_ahash(cesa->caps->ahash_algs[i]);
		अगर (ret)
			जाओ err_unरेजिस्टर_ahash;
	पूर्ण

	वापस 0;

err_unरेजिस्टर_ahash:
	क्रम (j = 0; j < i; j++)
		crypto_unरेजिस्टर_ahash(cesa->caps->ahash_algs[j]);
	i = cesa->caps->ncipher_algs;

err_unरेजिस्टर_crypto:
	क्रम (j = 0; j < i; j++)
		crypto_unरेजिस्टर_skcipher(cesa->caps->cipher_algs[j]);

	वापस ret;
पूर्ण

अटल व्योम mv_cesa_हटाओ_algs(काष्ठा mv_cesa_dev *cesa)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < cesa->caps->nahash_algs; i++)
		crypto_unरेजिस्टर_ahash(cesa->caps->ahash_algs[i]);

	क्रम (i = 0; i < cesa->caps->ncipher_algs; i++)
		crypto_unरेजिस्टर_skcipher(cesa->caps->cipher_algs[i]);
पूर्ण

अटल काष्ठा skcipher_alg *orion_cipher_algs[] = अणु
	&mv_cesa_ecb_des_alg,
	&mv_cesa_cbc_des_alg,
	&mv_cesa_ecb_des3_ede_alg,
	&mv_cesa_cbc_des3_ede_alg,
	&mv_cesa_ecb_aes_alg,
	&mv_cesa_cbc_aes_alg,
पूर्ण;

अटल काष्ठा ahash_alg *orion_ahash_algs[] = अणु
	&mv_md5_alg,
	&mv_sha1_alg,
	&mv_ahmac_md5_alg,
	&mv_ahmac_sha1_alg,
पूर्ण;

अटल काष्ठा skcipher_alg *armada_370_cipher_algs[] = अणु
	&mv_cesa_ecb_des_alg,
	&mv_cesa_cbc_des_alg,
	&mv_cesa_ecb_des3_ede_alg,
	&mv_cesa_cbc_des3_ede_alg,
	&mv_cesa_ecb_aes_alg,
	&mv_cesa_cbc_aes_alg,
पूर्ण;

अटल काष्ठा ahash_alg *armada_370_ahash_algs[] = अणु
	&mv_md5_alg,
	&mv_sha1_alg,
	&mv_sha256_alg,
	&mv_ahmac_md5_alg,
	&mv_ahmac_sha1_alg,
	&mv_ahmac_sha256_alg,
पूर्ण;

अटल स्थिर काष्ठा mv_cesa_caps orion_caps = अणु
	.nengines = 1,
	.cipher_algs = orion_cipher_algs,
	.ncipher_algs = ARRAY_SIZE(orion_cipher_algs),
	.ahash_algs = orion_ahash_algs,
	.nahash_algs = ARRAY_SIZE(orion_ahash_algs),
	.has_tdma = false,
पूर्ण;

अटल स्थिर काष्ठा mv_cesa_caps kirkwood_caps = अणु
	.nengines = 1,
	.cipher_algs = orion_cipher_algs,
	.ncipher_algs = ARRAY_SIZE(orion_cipher_algs),
	.ahash_algs = orion_ahash_algs,
	.nahash_algs = ARRAY_SIZE(orion_ahash_algs),
	.has_tdma = true,
पूर्ण;

अटल स्थिर काष्ठा mv_cesa_caps armada_370_caps = अणु
	.nengines = 1,
	.cipher_algs = armada_370_cipher_algs,
	.ncipher_algs = ARRAY_SIZE(armada_370_cipher_algs),
	.ahash_algs = armada_370_ahash_algs,
	.nahash_algs = ARRAY_SIZE(armada_370_ahash_algs),
	.has_tdma = true,
पूर्ण;

अटल स्थिर काष्ठा mv_cesa_caps armada_xp_caps = अणु
	.nengines = 2,
	.cipher_algs = armada_370_cipher_algs,
	.ncipher_algs = ARRAY_SIZE(armada_370_cipher_algs),
	.ahash_algs = armada_370_ahash_algs,
	.nahash_algs = ARRAY_SIZE(armada_370_ahash_algs),
	.has_tdma = true,
पूर्ण;

अटल स्थिर काष्ठा of_device_id mv_cesa_of_match_table[] = अणु
	अणु .compatible = "marvell,orion-crypto", .data = &orion_caps पूर्ण,
	अणु .compatible = "marvell,kirkwood-crypto", .data = &kirkwood_caps पूर्ण,
	अणु .compatible = "marvell,dove-crypto", .data = &kirkwood_caps पूर्ण,
	अणु .compatible = "marvell,armada-370-crypto", .data = &armada_370_caps पूर्ण,
	अणु .compatible = "marvell,armada-xp-crypto", .data = &armada_xp_caps पूर्ण,
	अणु .compatible = "marvell,armada-375-crypto", .data = &armada_xp_caps पूर्ण,
	अणु .compatible = "marvell,armada-38x-crypto", .data = &armada_xp_caps पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mv_cesa_of_match_table);

अटल व्योम
mv_cesa_conf_mbus_winकरोws(काष्ठा mv_cesa_engine *engine,
			  स्थिर काष्ठा mbus_dram_target_info *dram)
अणु
	व्योम __iomem *iobase = engine->regs;
	पूर्णांक i;

	क्रम (i = 0; i < 4; i++) अणु
		ग_लिखोl(0, iobase + CESA_TDMA_WINDOW_CTRL(i));
		ग_लिखोl(0, iobase + CESA_TDMA_WINDOW_BASE(i));
	पूर्ण

	क्रम (i = 0; i < dram->num_cs; i++) अणु
		स्थिर काष्ठा mbus_dram_winकरोw *cs = dram->cs + i;

		ग_लिखोl(((cs->size - 1) & 0xffff0000) |
		       (cs->mbus_attr << 8) |
		       (dram->mbus_dram_target_id << 4) | 1,
		       iobase + CESA_TDMA_WINDOW_CTRL(i));
		ग_लिखोl(cs->base, iobase + CESA_TDMA_WINDOW_BASE(i));
	पूर्ण
पूर्ण

अटल पूर्णांक mv_cesa_dev_dma_init(काष्ठा mv_cesa_dev *cesa)
अणु
	काष्ठा device *dev = cesa->dev;
	काष्ठा mv_cesa_dev_dma *dma;

	अगर (!cesa->caps->has_tdma)
		वापस 0;

	dma = devm_kzalloc(dev, माप(*dma), GFP_KERNEL);
	अगर (!dma)
		वापस -ENOMEM;

	dma->tdma_desc_pool = dmam_pool_create("tdma_desc", dev,
					माप(काष्ठा mv_cesa_tdma_desc),
					16, 0);
	अगर (!dma->tdma_desc_pool)
		वापस -ENOMEM;

	dma->op_pool = dmam_pool_create("cesa_op", dev,
					माप(काष्ठा mv_cesa_op_ctx), 16, 0);
	अगर (!dma->op_pool)
		वापस -ENOMEM;

	dma->cache_pool = dmam_pool_create("cesa_cache", dev,
					   CESA_MAX_HASH_BLOCK_SIZE, 1, 0);
	अगर (!dma->cache_pool)
		वापस -ENOMEM;

	dma->padding_pool = dmam_pool_create("cesa_padding", dev, 72, 1, 0);
	अगर (!dma->padding_pool)
		वापस -ENOMEM;

	cesa->dma = dma;

	वापस 0;
पूर्ण

अटल पूर्णांक mv_cesa_get_sram(काष्ठा platक्रमm_device *pdev, पूर्णांक idx)
अणु
	काष्ठा mv_cesa_dev *cesa = platक्रमm_get_drvdata(pdev);
	काष्ठा mv_cesa_engine *engine = &cesa->engines[idx];
	स्थिर अक्षर *res_name = "sram";
	काष्ठा resource *res;

	engine->pool = of_gen_pool_get(cesa->dev->of_node,
				       "marvell,crypto-srams", idx);
	अगर (engine->pool) अणु
		engine->sram_pool = gen_pool_dma_alloc(engine->pool,
						       cesa->sram_size,
						       &engine->sram_dma);
		अगर (engine->sram_pool)
			वापस 0;

		engine->pool = शून्य;
		वापस -ENOMEM;
	पूर्ण

	अगर (cesa->caps->nengines > 1) अणु
		अगर (!idx)
			res_name = "sram0";
		अन्यथा
			res_name = "sram1";
	पूर्ण

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM,
					   res_name);
	अगर (!res || resource_size(res) < cesa->sram_size)
		वापस -EINVAL;

	engine->sram = devm_ioremap_resource(cesa->dev, res);
	अगर (IS_ERR(engine->sram))
		वापस PTR_ERR(engine->sram);

	engine->sram_dma = dma_map_resource(cesa->dev, res->start,
					    cesa->sram_size,
					    DMA_BIसूचीECTIONAL, 0);
	अगर (dma_mapping_error(cesa->dev, engine->sram_dma))
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल व्योम mv_cesa_put_sram(काष्ठा platक्रमm_device *pdev, पूर्णांक idx)
अणु
	काष्ठा mv_cesa_dev *cesa = platक्रमm_get_drvdata(pdev);
	काष्ठा mv_cesa_engine *engine = &cesa->engines[idx];

	अगर (engine->pool)
		gen_pool_मुक्त(engine->pool, (अचिन्हित दीर्घ)engine->sram_pool,
			      cesa->sram_size);
	अन्यथा
		dma_unmap_resource(cesa->dev, engine->sram_dma,
				   cesa->sram_size, DMA_BIसूचीECTIONAL, 0);
पूर्ण

अटल पूर्णांक mv_cesa_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा mv_cesa_caps *caps = &orion_caps;
	स्थिर काष्ठा mbus_dram_target_info *dram;
	स्थिर काष्ठा of_device_id *match;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा mv_cesa_dev *cesa;
	काष्ठा mv_cesa_engine *engines;
	पूर्णांक irq, ret, i, cpu;
	u32 sram_size;

	अगर (cesa_dev) अणु
		dev_err(&pdev->dev, "Only one CESA device authorized\n");
		वापस -EEXIST;
	पूर्ण

	अगर (dev->of_node) अणु
		match = of_match_node(mv_cesa_of_match_table, dev->of_node);
		अगर (!match || !match->data)
			वापस -ENOTSUPP;

		caps = match->data;
	पूर्ण

	cesa = devm_kzalloc(dev, माप(*cesa), GFP_KERNEL);
	अगर (!cesa)
		वापस -ENOMEM;

	cesa->caps = caps;
	cesa->dev = dev;

	sram_size = CESA_SA_DEFAULT_SRAM_SIZE;
	of_property_पढ़ो_u32(cesa->dev->of_node, "marvell,crypto-sram-size",
			     &sram_size);
	अगर (sram_size < CESA_SA_MIN_SRAM_SIZE)
		sram_size = CESA_SA_MIN_SRAM_SIZE;

	cesa->sram_size = sram_size;
	cesa->engines = devm_kसुस्मृति(dev, caps->nengines, माप(*engines),
				     GFP_KERNEL);
	अगर (!cesa->engines)
		वापस -ENOMEM;

	spin_lock_init(&cesa->lock);

	cesa->regs = devm_platक्रमm_ioremap_resource_byname(pdev, "regs");
	अगर (IS_ERR(cesa->regs))
		वापस PTR_ERR(cesa->regs);

	ret = mv_cesa_dev_dma_init(cesa);
	अगर (ret)
		वापस ret;

	dram = mv_mbus_dram_info_nooverlap();

	platक्रमm_set_drvdata(pdev, cesa);

	क्रम (i = 0; i < caps->nengines; i++) अणु
		काष्ठा mv_cesa_engine *engine = &cesa->engines[i];
		अक्षर res_name[7];

		engine->id = i;
		spin_lock_init(&engine->lock);

		ret = mv_cesa_get_sram(pdev, i);
		अगर (ret)
			जाओ err_cleanup;

		irq = platक्रमm_get_irq(pdev, i);
		अगर (irq < 0) अणु
			ret = irq;
			जाओ err_cleanup;
		पूर्ण

		engine->irq = irq;

		/*
		 * Not all platक्रमms can gate the CESA घड़ीs: करो not complain
		 * अगर the घड़ी करोes not exist.
		 */
		snम_लिखो(res_name, माप(res_name), "cesa%d", i);
		engine->clk = devm_clk_get(dev, res_name);
		अगर (IS_ERR(engine->clk)) अणु
			engine->clk = devm_clk_get(dev, शून्य);
			अगर (IS_ERR(engine->clk))
				engine->clk = शून्य;
		पूर्ण

		snम_लिखो(res_name, माप(res_name), "cesaz%d", i);
		engine->zclk = devm_clk_get(dev, res_name);
		अगर (IS_ERR(engine->zclk))
			engine->zclk = शून्य;

		ret = clk_prepare_enable(engine->clk);
		अगर (ret)
			जाओ err_cleanup;

		ret = clk_prepare_enable(engine->zclk);
		अगर (ret)
			जाओ err_cleanup;

		engine->regs = cesa->regs + CESA_ENGINE_OFF(i);

		अगर (dram && cesa->caps->has_tdma)
			mv_cesa_conf_mbus_winकरोws(engine, dram);

		ग_लिखोl(0, engine->regs + CESA_SA_INT_STATUS);
		ग_लिखोl(CESA_SA_CFG_STOP_DIG_ERR,
		       engine->regs + CESA_SA_CFG);
		ग_लिखोl(engine->sram_dma & CESA_SA_SRAM_MSK,
		       engine->regs + CESA_SA_DESC_P0);

		ret = devm_request_thपढ़ोed_irq(dev, irq, शून्य, mv_cesa_पूर्णांक,
						IRQF_ONESHOT,
						dev_name(&pdev->dev),
						engine);
		अगर (ret)
			जाओ err_cleanup;

		/* Set affinity */
		cpu = cpumask_local_spपढ़ो(engine->id, NUMA_NO_NODE);
		irq_set_affinity_hपूर्णांक(irq, get_cpu_mask(cpu));

		crypto_init_queue(&engine->queue, CESA_CRYPTO_DEFAULT_MAX_QLEN);
		atomic_set(&engine->load, 0);
		INIT_LIST_HEAD(&engine->complete_queue);
	पूर्ण

	cesa_dev = cesa;

	ret = mv_cesa_add_algs(cesa);
	अगर (ret) अणु
		cesa_dev = शून्य;
		जाओ err_cleanup;
	पूर्ण

	dev_info(dev, "CESA device successfully registered\n");

	वापस 0;

err_cleanup:
	क्रम (i = 0; i < caps->nengines; i++) अणु
		clk_disable_unprepare(cesa->engines[i].zclk);
		clk_disable_unprepare(cesa->engines[i].clk);
		mv_cesa_put_sram(pdev, i);
		अगर (cesa->engines[i].irq > 0)
			irq_set_affinity_hपूर्णांक(cesa->engines[i].irq, शून्य);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक mv_cesa_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mv_cesa_dev *cesa = platक्रमm_get_drvdata(pdev);
	पूर्णांक i;

	mv_cesa_हटाओ_algs(cesa);

	क्रम (i = 0; i < cesa->caps->nengines; i++) अणु
		clk_disable_unprepare(cesa->engines[i].zclk);
		clk_disable_unprepare(cesa->engines[i].clk);
		mv_cesa_put_sram(pdev, i);
		irq_set_affinity_hपूर्णांक(cesa->engines[i].irq, शून्य);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id mv_cesa_plat_id_table[] = अणु
	अणु .name = "mv_crypto" पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, mv_cesa_plat_id_table);

अटल काष्ठा platक्रमm_driver marvell_cesa = अणु
	.probe		= mv_cesa_probe,
	.हटाओ		= mv_cesa_हटाओ,
	.id_table	= mv_cesa_plat_id_table,
	.driver		= अणु
		.name	= "marvell-cesa",
		.of_match_table = mv_cesa_of_match_table,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(marvell_cesa);

MODULE_ALIAS("platform:mv_crypto");
MODULE_AUTHOR("Boris Brezillon <boris.brezillon@free-electrons.com>");
MODULE_AUTHOR("Arnaud Ebalard <arno@natisbad.org>");
MODULE_DESCRIPTION("Support for Marvell's cryptographic engine");
MODULE_LICENSE("GPL v2");
