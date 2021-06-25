<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2010-2014, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/clk.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/types.h>
#समावेश <crypto/algapi.h>
#समावेश <crypto/पूर्णांकernal/hash.h>

#समावेश "core.h"
#समावेश "cipher.h"
#समावेश "sha.h"

#घोषणा QCE_MAJOR_VERSION5	0x05
#घोषणा QCE_QUEUE_LENGTH	1

अटल स्थिर काष्ठा qce_algo_ops *qce_ops[] = अणु
#अगर_घोषित CONFIG_CRYPTO_DEV_QCE_SKCIPHER
	&skcipher_ops,
#पूर्ण_अगर
#अगर_घोषित CONFIG_CRYPTO_DEV_QCE_SHA
	&ahash_ops,
#पूर्ण_अगर
पूर्ण;

अटल व्योम qce_unरेजिस्टर_algs(काष्ठा qce_device *qce)
अणु
	स्थिर काष्ठा qce_algo_ops *ops;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(qce_ops); i++) अणु
		ops = qce_ops[i];
		ops->unरेजिस्टर_algs(qce);
	पूर्ण
पूर्ण

अटल पूर्णांक qce_रेजिस्टर_algs(काष्ठा qce_device *qce)
अणु
	स्थिर काष्ठा qce_algo_ops *ops;
	पूर्णांक i, ret = -ENODEV;

	क्रम (i = 0; i < ARRAY_SIZE(qce_ops); i++) अणु
		ops = qce_ops[i];
		ret = ops->रेजिस्टर_algs(qce);
		अगर (ret)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक qce_handle_request(काष्ठा crypto_async_request *async_req)
अणु
	पूर्णांक ret = -EINVAL, i;
	स्थिर काष्ठा qce_algo_ops *ops;
	u32 type = crypto_tfm_alg_type(async_req->tfm);

	क्रम (i = 0; i < ARRAY_SIZE(qce_ops); i++) अणु
		ops = qce_ops[i];
		अगर (type != ops->type)
			जारी;
		ret = ops->async_req_handle(async_req);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक qce_handle_queue(काष्ठा qce_device *qce,
			    काष्ठा crypto_async_request *req)
अणु
	काष्ठा crypto_async_request *async_req, *backlog;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0, err;

	spin_lock_irqsave(&qce->lock, flags);

	अगर (req)
		ret = crypto_enqueue_request(&qce->queue, req);

	/* busy, करो not dequeue request */
	अगर (qce->req) अणु
		spin_unlock_irqrestore(&qce->lock, flags);
		वापस ret;
	पूर्ण

	backlog = crypto_get_backlog(&qce->queue);
	async_req = crypto_dequeue_request(&qce->queue);
	अगर (async_req)
		qce->req = async_req;

	spin_unlock_irqrestore(&qce->lock, flags);

	अगर (!async_req)
		वापस ret;

	अगर (backlog) अणु
		spin_lock_bh(&qce->lock);
		backlog->complete(backlog, -EINPROGRESS);
		spin_unlock_bh(&qce->lock);
	पूर्ण

	err = qce_handle_request(async_req);
	अगर (err) अणु
		qce->result = err;
		tasklet_schedule(&qce->करोne_tasklet);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम qce_tasklet_req_करोne(अचिन्हित दीर्घ data)
अणु
	काष्ठा qce_device *qce = (काष्ठा qce_device *)data;
	काष्ठा crypto_async_request *req;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&qce->lock, flags);
	req = qce->req;
	qce->req = शून्य;
	spin_unlock_irqrestore(&qce->lock, flags);

	अगर (req)
		req->complete(req, qce->result);

	qce_handle_queue(qce, शून्य);
पूर्ण

अटल पूर्णांक qce_async_request_enqueue(काष्ठा qce_device *qce,
				     काष्ठा crypto_async_request *req)
अणु
	वापस qce_handle_queue(qce, req);
पूर्ण

अटल व्योम qce_async_request_करोne(काष्ठा qce_device *qce, पूर्णांक ret)
अणु
	qce->result = ret;
	tasklet_schedule(&qce->करोne_tasklet);
पूर्ण

अटल पूर्णांक qce_check_version(काष्ठा qce_device *qce)
अणु
	u32 major, minor, step;

	qce_get_version(qce, &major, &minor, &step);

	/*
	 * the driver करोes not support v5 with minor 0 because it has special
	 * alignment requirements.
	 */
	अगर (major != QCE_MAJOR_VERSION5 || minor == 0)
		वापस -ENODEV;

	qce->burst_size = QCE_BAM_BURST_SIZE;

	/*
	 * Rx and tx pipes are treated as a pair inside CE.
	 * Pipe pair number depends on the actual BAM dma pipe
	 * that is used क्रम transfers. The BAM dma pipes are passed
	 * from the device tree and used to derive the pipe pair
	 * id in the CE driver as follows.
	 * 	BAM dma pipes(rx, tx)		CE pipe pair id
	 *		0,1				0
	 *		2,3				1
	 *		4,5				2
	 *		6,7				3
	 *		...
	 */
	qce->pipe_pair_id = qce->dma.rxchan->chan_id >> 1;

	dev_dbg(qce->dev, "Crypto device found, version %d.%d.%d\n",
		major, minor, step);

	वापस 0;
पूर्ण

अटल पूर्णांक qce_crypto_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा qce_device *qce;
	पूर्णांक ret;

	qce = devm_kzalloc(dev, माप(*qce), GFP_KERNEL);
	अगर (!qce)
		वापस -ENOMEM;

	qce->dev = dev;
	platक्रमm_set_drvdata(pdev, qce);

	qce->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(qce->base))
		वापस PTR_ERR(qce->base);

	ret = dma_set_mask_and_coherent(dev, DMA_BIT_MASK(32));
	अगर (ret < 0)
		वापस ret;

	qce->core = devm_clk_get(qce->dev, "core");
	अगर (IS_ERR(qce->core))
		वापस PTR_ERR(qce->core);

	qce->अगरace = devm_clk_get(qce->dev, "iface");
	अगर (IS_ERR(qce->अगरace))
		वापस PTR_ERR(qce->अगरace);

	qce->bus = devm_clk_get(qce->dev, "bus");
	अगर (IS_ERR(qce->bus))
		वापस PTR_ERR(qce->bus);

	ret = clk_prepare_enable(qce->core);
	अगर (ret)
		वापस ret;

	ret = clk_prepare_enable(qce->अगरace);
	अगर (ret)
		जाओ err_clks_core;

	ret = clk_prepare_enable(qce->bus);
	अगर (ret)
		जाओ err_clks_अगरace;

	ret = qce_dma_request(qce->dev, &qce->dma);
	अगर (ret)
		जाओ err_clks;

	ret = qce_check_version(qce);
	अगर (ret)
		जाओ err_clks;

	spin_lock_init(&qce->lock);
	tasklet_init(&qce->करोne_tasklet, qce_tasklet_req_करोne,
		     (अचिन्हित दीर्घ)qce);
	crypto_init_queue(&qce->queue, QCE_QUEUE_LENGTH);

	qce->async_req_enqueue = qce_async_request_enqueue;
	qce->async_req_करोne = qce_async_request_करोne;

	ret = qce_रेजिस्टर_algs(qce);
	अगर (ret)
		जाओ err_dma;

	वापस 0;

err_dma:
	qce_dma_release(&qce->dma);
err_clks:
	clk_disable_unprepare(qce->bus);
err_clks_अगरace:
	clk_disable_unprepare(qce->अगरace);
err_clks_core:
	clk_disable_unprepare(qce->core);
	वापस ret;
पूर्ण

अटल पूर्णांक qce_crypto_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा qce_device *qce = platक्रमm_get_drvdata(pdev);

	tasklet_समाप्त(&qce->करोne_tasklet);
	qce_unरेजिस्टर_algs(qce);
	qce_dma_release(&qce->dma);
	clk_disable_unprepare(qce->bus);
	clk_disable_unprepare(qce->अगरace);
	clk_disable_unprepare(qce->core);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id qce_crypto_of_match[] = अणु
	अणु .compatible = "qcom,crypto-v5.1", पूर्ण,
	अणु .compatible = "qcom,crypto-v5.4", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, qce_crypto_of_match);

अटल काष्ठा platक्रमm_driver qce_crypto_driver = अणु
	.probe = qce_crypto_probe,
	.हटाओ = qce_crypto_हटाओ,
	.driver = अणु
		.name = KBUILD_MODNAME,
		.of_match_table = qce_crypto_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(qce_crypto_driver);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Qualcomm crypto engine driver");
MODULE_ALIAS("platform:" KBUILD_MODNAME);
MODULE_AUTHOR("The Linux Foundation");
