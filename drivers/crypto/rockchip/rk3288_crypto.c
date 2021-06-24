<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Crypto acceleration support क्रम Rockchip RK3288
 *
 * Copyright (c) 2015, Fuzhou Rockchip Electronics Co., Ltd
 *
 * Author: Zain Wang <zain.wang@rock-chips.com>
 *
 * Some ideas are from marvell-cesa.c and s5p-sss.c driver.
 */

#समावेश "rk3288_crypto.h"
#समावेश <linux/dma-mapping.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of.h>
#समावेश <linux/clk.h>
#समावेश <linux/crypto.h>
#समावेश <linux/reset.h>

अटल पूर्णांक rk_crypto_enable_clk(काष्ठा rk_crypto_info *dev)
अणु
	पूर्णांक err;

	err = clk_prepare_enable(dev->sclk);
	अगर (err) अणु
		dev_err(dev->dev, "[%s:%d], Couldn't enable clock sclk\n",
			__func__, __LINE__);
		जाओ err_वापस;
	पूर्ण
	err = clk_prepare_enable(dev->aclk);
	अगर (err) अणु
		dev_err(dev->dev, "[%s:%d], Couldn't enable clock aclk\n",
			__func__, __LINE__);
		जाओ err_aclk;
	पूर्ण
	err = clk_prepare_enable(dev->hclk);
	अगर (err) अणु
		dev_err(dev->dev, "[%s:%d], Couldn't enable clock hclk\n",
			__func__, __LINE__);
		जाओ err_hclk;
	पूर्ण
	err = clk_prepare_enable(dev->dmaclk);
	अगर (err) अणु
		dev_err(dev->dev, "[%s:%d], Couldn't enable clock dmaclk\n",
			__func__, __LINE__);
		जाओ err_dmaclk;
	पूर्ण
	वापस err;
err_dmaclk:
	clk_disable_unprepare(dev->hclk);
err_hclk:
	clk_disable_unprepare(dev->aclk);
err_aclk:
	clk_disable_unprepare(dev->sclk);
err_वापस:
	वापस err;
पूर्ण

अटल व्योम rk_crypto_disable_clk(काष्ठा rk_crypto_info *dev)
अणु
	clk_disable_unprepare(dev->dmaclk);
	clk_disable_unprepare(dev->hclk);
	clk_disable_unprepare(dev->aclk);
	clk_disable_unprepare(dev->sclk);
पूर्ण

अटल पूर्णांक check_alignment(काष्ठा scatterlist *sg_src,
			   काष्ठा scatterlist *sg_dst,
			   पूर्णांक align_mask)
अणु
	पूर्णांक in, out, align;

	in = IS_ALIGNED((uपूर्णांक32_t)sg_src->offset, 4) &&
	     IS_ALIGNED((uपूर्णांक32_t)sg_src->length, align_mask);
	अगर (!sg_dst)
		वापस in;
	out = IS_ALIGNED((uपूर्णांक32_t)sg_dst->offset, 4) &&
	      IS_ALIGNED((uपूर्णांक32_t)sg_dst->length, align_mask);
	align = in && out;

	वापस (align && (sg_src->length == sg_dst->length));
पूर्ण

अटल पूर्णांक rk_load_data(काष्ठा rk_crypto_info *dev,
			काष्ठा scatterlist *sg_src,
			काष्ठा scatterlist *sg_dst)
अणु
	अचिन्हित पूर्णांक count;

	dev->aligned = dev->aligned ?
		check_alignment(sg_src, sg_dst, dev->align_size) :
		dev->aligned;
	अगर (dev->aligned) अणु
		count = min(dev->left_bytes, sg_src->length);
		dev->left_bytes -= count;

		अगर (!dma_map_sg(dev->dev, sg_src, 1, DMA_TO_DEVICE)) अणु
			dev_err(dev->dev, "[%s:%d] dma_map_sg(src)  error\n",
				__func__, __LINE__);
			वापस -EINVAL;
		पूर्ण
		dev->addr_in = sg_dma_address(sg_src);

		अगर (sg_dst) अणु
			अगर (!dma_map_sg(dev->dev, sg_dst, 1, DMA_FROM_DEVICE)) अणु
				dev_err(dev->dev,
					"[%s:%d] dma_map_sg(dst)  error\n",
					__func__, __LINE__);
				dma_unmap_sg(dev->dev, sg_src, 1,
					     DMA_TO_DEVICE);
				वापस -EINVAL;
			पूर्ण
			dev->addr_out = sg_dma_address(sg_dst);
		पूर्ण
	पूर्ण अन्यथा अणु
		count = (dev->left_bytes > PAGE_SIZE) ?
			PAGE_SIZE : dev->left_bytes;

		अगर (!sg_pcopy_to_buffer(dev->first, dev->src_nents,
					dev->addr_vir, count,
					dev->total - dev->left_bytes)) अणु
			dev_err(dev->dev, "[%s:%d] pcopy err\n",
				__func__, __LINE__);
			वापस -EINVAL;
		पूर्ण
		dev->left_bytes -= count;
		sg_init_one(&dev->sg_पंचांगp, dev->addr_vir, count);
		अगर (!dma_map_sg(dev->dev, &dev->sg_पंचांगp, 1, DMA_TO_DEVICE)) अणु
			dev_err(dev->dev, "[%s:%d] dma_map_sg(sg_tmp)  error\n",
				__func__, __LINE__);
			वापस -ENOMEM;
		पूर्ण
		dev->addr_in = sg_dma_address(&dev->sg_पंचांगp);

		अगर (sg_dst) अणु
			अगर (!dma_map_sg(dev->dev, &dev->sg_पंचांगp, 1,
					DMA_FROM_DEVICE)) अणु
				dev_err(dev->dev,
					"[%s:%d] dma_map_sg(sg_tmp)  error\n",
					__func__, __LINE__);
				dma_unmap_sg(dev->dev, &dev->sg_पंचांगp, 1,
					     DMA_TO_DEVICE);
				वापस -ENOMEM;
			पूर्ण
			dev->addr_out = sg_dma_address(&dev->sg_पंचांगp);
		पूर्ण
	पूर्ण
	dev->count = count;
	वापस 0;
पूर्ण

अटल व्योम rk_unload_data(काष्ठा rk_crypto_info *dev)
अणु
	काष्ठा scatterlist *sg_in, *sg_out;

	sg_in = dev->aligned ? dev->sg_src : &dev->sg_पंचांगp;
	dma_unmap_sg(dev->dev, sg_in, 1, DMA_TO_DEVICE);

	अगर (dev->sg_dst) अणु
		sg_out = dev->aligned ? dev->sg_dst : &dev->sg_पंचांगp;
		dma_unmap_sg(dev->dev, sg_out, 1, DMA_FROM_DEVICE);
	पूर्ण
पूर्ण

अटल irqवापस_t rk_crypto_irq_handle(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा rk_crypto_info *dev  = platक्रमm_get_drvdata(dev_id);
	u32 पूर्णांकerrupt_status;

	spin_lock(&dev->lock);
	पूर्णांकerrupt_status = CRYPTO_READ(dev, RK_CRYPTO_INTSTS);
	CRYPTO_WRITE(dev, RK_CRYPTO_INTSTS, पूर्णांकerrupt_status);

	अगर (पूर्णांकerrupt_status & 0x0a) अणु
		dev_warn(dev->dev, "DMA Error\n");
		dev->err = -EFAULT;
	पूर्ण
	tasklet_schedule(&dev->करोne_task);

	spin_unlock(&dev->lock);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक rk_crypto_enqueue(काष्ठा rk_crypto_info *dev,
			      काष्ठा crypto_async_request *async_req)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&dev->lock, flags);
	ret = crypto_enqueue_request(&dev->queue, async_req);
	अगर (dev->busy) अणु
		spin_unlock_irqrestore(&dev->lock, flags);
		वापस ret;
	पूर्ण
	dev->busy = true;
	spin_unlock_irqrestore(&dev->lock, flags);
	tasklet_schedule(&dev->queue_task);

	वापस ret;
पूर्ण

अटल व्योम rk_crypto_queue_task_cb(अचिन्हित दीर्घ data)
अणु
	काष्ठा rk_crypto_info *dev = (काष्ठा rk_crypto_info *)data;
	काष्ठा crypto_async_request *async_req, *backlog;
	अचिन्हित दीर्घ flags;
	पूर्णांक err = 0;

	dev->err = 0;
	spin_lock_irqsave(&dev->lock, flags);
	backlog   = crypto_get_backlog(&dev->queue);
	async_req = crypto_dequeue_request(&dev->queue);

	अगर (!async_req) अणु
		dev->busy = false;
		spin_unlock_irqrestore(&dev->lock, flags);
		वापस;
	पूर्ण
	spin_unlock_irqrestore(&dev->lock, flags);

	अगर (backlog) अणु
		backlog->complete(backlog, -EINPROGRESS);
		backlog = शून्य;
	पूर्ण

	dev->async_req = async_req;
	err = dev->start(dev);
	अगर (err)
		dev->complete(dev->async_req, err);
पूर्ण

अटल व्योम rk_crypto_करोne_task_cb(अचिन्हित दीर्घ data)
अणु
	काष्ठा rk_crypto_info *dev = (काष्ठा rk_crypto_info *)data;

	अगर (dev->err) अणु
		dev->complete(dev->async_req, dev->err);
		वापस;
	पूर्ण

	dev->err = dev->update(dev);
	अगर (dev->err)
		dev->complete(dev->async_req, dev->err);
पूर्ण

अटल काष्ठा rk_crypto_पंचांगp *rk_cipher_algs[] = अणु
	&rk_ecb_aes_alg,
	&rk_cbc_aes_alg,
	&rk_ecb_des_alg,
	&rk_cbc_des_alg,
	&rk_ecb_des3_ede_alg,
	&rk_cbc_des3_ede_alg,
	&rk_ahash_sha1,
	&rk_ahash_sha256,
	&rk_ahash_md5,
पूर्ण;

अटल पूर्णांक rk_crypto_रेजिस्टर(काष्ठा rk_crypto_info *crypto_info)
अणु
	अचिन्हित पूर्णांक i, k;
	पूर्णांक err = 0;

	क्रम (i = 0; i < ARRAY_SIZE(rk_cipher_algs); i++) अणु
		rk_cipher_algs[i]->dev = crypto_info;
		अगर (rk_cipher_algs[i]->type == ALG_TYPE_CIPHER)
			err = crypto_रेजिस्टर_skcipher(
					&rk_cipher_algs[i]->alg.skcipher);
		अन्यथा
			err = crypto_रेजिस्टर_ahash(
					&rk_cipher_algs[i]->alg.hash);
		अगर (err)
			जाओ err_cipher_algs;
	पूर्ण
	वापस 0;

err_cipher_algs:
	क्रम (k = 0; k < i; k++) अणु
		अगर (rk_cipher_algs[i]->type == ALG_TYPE_CIPHER)
			crypto_unरेजिस्टर_skcipher(&rk_cipher_algs[k]->alg.skcipher);
		अन्यथा
			crypto_unरेजिस्टर_ahash(&rk_cipher_algs[i]->alg.hash);
	पूर्ण
	वापस err;
पूर्ण

अटल व्योम rk_crypto_unरेजिस्टर(व्योम)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(rk_cipher_algs); i++) अणु
		अगर (rk_cipher_algs[i]->type == ALG_TYPE_CIPHER)
			crypto_unरेजिस्टर_skcipher(&rk_cipher_algs[i]->alg.skcipher);
		अन्यथा
			crypto_unरेजिस्टर_ahash(&rk_cipher_algs[i]->alg.hash);
	पूर्ण
पूर्ण

अटल व्योम rk_crypto_action(व्योम *data)
अणु
	काष्ठा rk_crypto_info *crypto_info = data;

	reset_control_निश्चित(crypto_info->rst);
पूर्ण

अटल स्थिर काष्ठा of_device_id crypto_of_id_table[] = अणु
	अणु .compatible = "rockchip,rk3288-crypto" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, crypto_of_id_table);

अटल पूर्णांक rk_crypto_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा rk_crypto_info *crypto_info;
	पूर्णांक err = 0;

	crypto_info = devm_kzalloc(&pdev->dev,
				   माप(*crypto_info), GFP_KERNEL);
	अगर (!crypto_info) अणु
		err = -ENOMEM;
		जाओ err_crypto;
	पूर्ण

	crypto_info->rst = devm_reset_control_get(dev, "crypto-rst");
	अगर (IS_ERR(crypto_info->rst)) अणु
		err = PTR_ERR(crypto_info->rst);
		जाओ err_crypto;
	पूर्ण

	reset_control_निश्चित(crypto_info->rst);
	usleep_range(10, 20);
	reset_control_deनिश्चित(crypto_info->rst);

	err = devm_add_action_or_reset(dev, rk_crypto_action, crypto_info);
	अगर (err)
		जाओ err_crypto;

	spin_lock_init(&crypto_info->lock);

	crypto_info->reg = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(crypto_info->reg)) अणु
		err = PTR_ERR(crypto_info->reg);
		जाओ err_crypto;
	पूर्ण

	crypto_info->aclk = devm_clk_get(&pdev->dev, "aclk");
	अगर (IS_ERR(crypto_info->aclk)) अणु
		err = PTR_ERR(crypto_info->aclk);
		जाओ err_crypto;
	पूर्ण

	crypto_info->hclk = devm_clk_get(&pdev->dev, "hclk");
	अगर (IS_ERR(crypto_info->hclk)) अणु
		err = PTR_ERR(crypto_info->hclk);
		जाओ err_crypto;
	पूर्ण

	crypto_info->sclk = devm_clk_get(&pdev->dev, "sclk");
	अगर (IS_ERR(crypto_info->sclk)) अणु
		err = PTR_ERR(crypto_info->sclk);
		जाओ err_crypto;
	पूर्ण

	crypto_info->dmaclk = devm_clk_get(&pdev->dev, "apb_pclk");
	अगर (IS_ERR(crypto_info->dmaclk)) अणु
		err = PTR_ERR(crypto_info->dmaclk);
		जाओ err_crypto;
	पूर्ण

	crypto_info->irq = platक्रमm_get_irq(pdev, 0);
	अगर (crypto_info->irq < 0) अणु
		dev_warn(crypto_info->dev,
			 "control Interrupt is not available.\n");
		err = crypto_info->irq;
		जाओ err_crypto;
	पूर्ण

	err = devm_request_irq(&pdev->dev, crypto_info->irq,
			       rk_crypto_irq_handle, IRQF_SHARED,
			       "rk-crypto", pdev);

	अगर (err) अणु
		dev_err(crypto_info->dev, "irq request failed.\n");
		जाओ err_crypto;
	पूर्ण

	crypto_info->dev = &pdev->dev;
	platक्रमm_set_drvdata(pdev, crypto_info);

	tasklet_init(&crypto_info->queue_task,
		     rk_crypto_queue_task_cb, (अचिन्हित दीर्घ)crypto_info);
	tasklet_init(&crypto_info->करोne_task,
		     rk_crypto_करोne_task_cb, (अचिन्हित दीर्घ)crypto_info);
	crypto_init_queue(&crypto_info->queue, 50);

	crypto_info->enable_clk = rk_crypto_enable_clk;
	crypto_info->disable_clk = rk_crypto_disable_clk;
	crypto_info->load_data = rk_load_data;
	crypto_info->unload_data = rk_unload_data;
	crypto_info->enqueue = rk_crypto_enqueue;
	crypto_info->busy = false;

	err = rk_crypto_रेजिस्टर(crypto_info);
	अगर (err) अणु
		dev_err(dev, "err in register alg");
		जाओ err_रेजिस्टर_alg;
	पूर्ण

	dev_info(dev, "Crypto Accelerator successfully registered\n");
	वापस 0;

err_रेजिस्टर_alg:
	tasklet_समाप्त(&crypto_info->queue_task);
	tasklet_समाप्त(&crypto_info->करोne_task);
err_crypto:
	वापस err;
पूर्ण

अटल पूर्णांक rk_crypto_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rk_crypto_info *crypto_पंचांगp = platक्रमm_get_drvdata(pdev);

	rk_crypto_unरेजिस्टर();
	tasklet_समाप्त(&crypto_पंचांगp->करोne_task);
	tasklet_समाप्त(&crypto_पंचांगp->queue_task);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver crypto_driver = अणु
	.probe		= rk_crypto_probe,
	.हटाओ		= rk_crypto_हटाओ,
	.driver		= अणु
		.name	= "rk3288-crypto",
		.of_match_table	= crypto_of_id_table,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(crypto_driver);

MODULE_AUTHOR("Zain Wang <zain.wang@rock-chips.com>");
MODULE_DESCRIPTION("Support for Rockchip's cryptographic engine");
MODULE_LICENSE("GPL");
