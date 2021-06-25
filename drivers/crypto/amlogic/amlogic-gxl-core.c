<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * amlgoic-core.c - hardware cryptographic offloader क्रम Amlogic GXL SoC
 *
 * Copyright (C) 2018-2019 Corentin Labbe <clabbe@baylibre.com>
 *
 * Core file which रेजिस्टरs crypto algorithms supported by the hardware.
 */
#समावेश <linux/clk.h>
#समावेश <linux/crypto.h>
#समावेश <linux/पन.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <crypto/पूर्णांकernal/skcipher.h>
#समावेश <linux/dma-mapping.h>

#समावेश "amlogic-gxl.h"

अटल irqवापस_t meson_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा meson_dev *mc = (काष्ठा meson_dev *)data;
	पूर्णांक flow;
	u32 p;

	क्रम (flow = 0; flow < MAXFLOW; flow++) अणु
		अगर (mc->irqs[flow] == irq) अणु
			p = पढ़ोl(mc->base + ((0x04 + flow) << 2));
			अगर (p) अणु
				ग_लिखोl_relaxed(0xF, mc->base + ((0x4 + flow) << 2));
				mc->chanlist[flow].status = 1;
				complete(&mc->chanlist[flow].complete);
				वापस IRQ_HANDLED;
			पूर्ण
			dev_err(mc->dev, "%s %d Got irq for flow %d but ctrl is empty\n", __func__, irq, flow);
		पूर्ण
	पूर्ण

	dev_err(mc->dev, "%s %d from unknown irq\n", __func__, irq);
	वापस IRQ_HANDLED;
पूर्ण

अटल काष्ठा meson_alg_ढाँचा mc_algs[] = अणु
अणु
	.type = CRYPTO_ALG_TYPE_SKCIPHER,
	.blockmode = MESON_OPMODE_CBC,
	.alg.skcipher = अणु
		.base = अणु
			.cra_name = "cbc(aes)",
			.cra_driver_name = "cbc-aes-gxl",
			.cra_priority = 400,
			.cra_blocksize = AES_BLOCK_SIZE,
			.cra_flags = CRYPTO_ALG_TYPE_SKCIPHER |
				CRYPTO_ALG_ASYNC | CRYPTO_ALG_ALLOCATES_MEMORY |
				CRYPTO_ALG_NEED_FALLBACK,
			.cra_ctxsize = माप(काष्ठा meson_cipher_tfm_ctx),
			.cra_module = THIS_MODULE,
			.cra_alignmask = 0xf,
			.cra_init = meson_cipher_init,
			.cra_निकास = meson_cipher_निकास,
		पूर्ण,
		.min_keysize	= AES_MIN_KEY_SIZE,
		.max_keysize	= AES_MAX_KEY_SIZE,
		.ivsize		= AES_BLOCK_SIZE,
		.setkey		= meson_aes_setkey,
		.encrypt	= meson_skencrypt,
		.decrypt	= meson_skdecrypt,
	पूर्ण
पूर्ण,
अणु
	.type = CRYPTO_ALG_TYPE_SKCIPHER,
	.blockmode = MESON_OPMODE_ECB,
	.alg.skcipher = अणु
		.base = अणु
			.cra_name = "ecb(aes)",
			.cra_driver_name = "ecb-aes-gxl",
			.cra_priority = 400,
			.cra_blocksize = AES_BLOCK_SIZE,
			.cra_flags = CRYPTO_ALG_TYPE_SKCIPHER |
				CRYPTO_ALG_ASYNC | CRYPTO_ALG_ALLOCATES_MEMORY |
				CRYPTO_ALG_NEED_FALLBACK,
			.cra_ctxsize = माप(काष्ठा meson_cipher_tfm_ctx),
			.cra_module = THIS_MODULE,
			.cra_alignmask = 0xf,
			.cra_init = meson_cipher_init,
			.cra_निकास = meson_cipher_निकास,
		पूर्ण,
		.min_keysize	= AES_MIN_KEY_SIZE,
		.max_keysize	= AES_MAX_KEY_SIZE,
		.setkey		= meson_aes_setkey,
		.encrypt	= meson_skencrypt,
		.decrypt	= meson_skdecrypt,
	पूर्ण
पूर्ण,
पूर्ण;

#अगर_घोषित CONFIG_CRYPTO_DEV_AMLOGIC_GXL_DEBUG
अटल पूर्णांक meson_debugfs_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा meson_dev *mc = seq->निजी;
	पूर्णांक i;

	क्रम (i = 0; i < MAXFLOW; i++)
		seq_म_लिखो(seq, "Channel %d: nreq %lu\n", i, mc->chanlist[i].stat_req);

	क्रम (i = 0; i < ARRAY_SIZE(mc_algs); i++) अणु
		चयन (mc_algs[i].type) अणु
		हाल CRYPTO_ALG_TYPE_SKCIPHER:
			seq_म_लिखो(seq, "%s %s %lu %lu\n",
				   mc_algs[i].alg.skcipher.base.cra_driver_name,
				   mc_algs[i].alg.skcipher.base.cra_name,
				   mc_algs[i].stat_req, mc_algs[i].stat_fb);
			अवरोध;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(meson_debugfs);
#पूर्ण_अगर

अटल व्योम meson_मुक्त_chanlist(काष्ठा meson_dev *mc, पूर्णांक i)
अणु
	जबतक (i >= 0) अणु
		crypto_engine_निकास(mc->chanlist[i].engine);
		अगर (mc->chanlist[i].tl)
			dma_मुक्त_coherent(mc->dev, माप(काष्ठा meson_desc) * MAXDESC,
					  mc->chanlist[i].tl,
					  mc->chanlist[i].t_phy);
		i--;
	पूर्ण
पूर्ण

/*
 * Allocate the channel list काष्ठाure
 */
अटल पूर्णांक meson_allocate_chanlist(काष्ठा meson_dev *mc)
अणु
	पूर्णांक i, err;

	mc->chanlist = devm_kसुस्मृति(mc->dev, MAXFLOW,
				    माप(काष्ठा meson_flow), GFP_KERNEL);
	अगर (!mc->chanlist)
		वापस -ENOMEM;

	क्रम (i = 0; i < MAXFLOW; i++) अणु
		init_completion(&mc->chanlist[i].complete);

		mc->chanlist[i].engine = crypto_engine_alloc_init(mc->dev, true);
		अगर (!mc->chanlist[i].engine) अणु
			dev_err(mc->dev, "Cannot allocate engine\n");
			i--;
			err = -ENOMEM;
			जाओ error_engine;
		पूर्ण
		err = crypto_engine_start(mc->chanlist[i].engine);
		अगर (err) अणु
			dev_err(mc->dev, "Cannot start engine\n");
			जाओ error_engine;
		पूर्ण
		mc->chanlist[i].tl = dma_alloc_coherent(mc->dev,
							माप(काष्ठा meson_desc) * MAXDESC,
							&mc->chanlist[i].t_phy,
							GFP_KERNEL);
		अगर (!mc->chanlist[i].tl) अणु
			err = -ENOMEM;
			जाओ error_engine;
		पूर्ण
	पूर्ण
	वापस 0;
error_engine:
	meson_मुक्त_chanlist(mc, i);
	वापस err;
पूर्ण

अटल पूर्णांक meson_रेजिस्टर_algs(काष्ठा meson_dev *mc)
अणु
	पूर्णांक err, i;

	क्रम (i = 0; i < ARRAY_SIZE(mc_algs); i++) अणु
		mc_algs[i].mc = mc;
		चयन (mc_algs[i].type) अणु
		हाल CRYPTO_ALG_TYPE_SKCIPHER:
			err = crypto_रेजिस्टर_skcipher(&mc_algs[i].alg.skcipher);
			अगर (err) अणु
				dev_err(mc->dev, "Fail to register %s\n",
					mc_algs[i].alg.skcipher.base.cra_name);
				mc_algs[i].mc = शून्य;
				वापस err;
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम meson_unरेजिस्टर_algs(काष्ठा meson_dev *mc)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(mc_algs); i++) अणु
		अगर (!mc_algs[i].mc)
			जारी;
		चयन (mc_algs[i].type) अणु
		हाल CRYPTO_ALG_TYPE_SKCIPHER:
			crypto_unरेजिस्टर_skcipher(&mc_algs[i].alg.skcipher);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक meson_crypto_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा meson_dev *mc;
	पूर्णांक err, i;

	mc = devm_kzalloc(&pdev->dev, माप(*mc), GFP_KERNEL);
	अगर (!mc)
		वापस -ENOMEM;

	mc->dev = &pdev->dev;
	platक्रमm_set_drvdata(pdev, mc);

	mc->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(mc->base)) अणु
		err = PTR_ERR(mc->base);
		dev_err(&pdev->dev, "Cannot request MMIO err=%d\n", err);
		वापस err;
	पूर्ण
	mc->busclk = devm_clk_get(&pdev->dev, "blkmv");
	अगर (IS_ERR(mc->busclk)) अणु
		err = PTR_ERR(mc->busclk);
		dev_err(&pdev->dev, "Cannot get core clock err=%d\n", err);
		वापस err;
	पूर्ण

	mc->irqs = devm_kसुस्मृति(mc->dev, MAXFLOW, माप(पूर्णांक), GFP_KERNEL);
	क्रम (i = 0; i < MAXFLOW; i++) अणु
		mc->irqs[i] = platक्रमm_get_irq(pdev, i);
		अगर (mc->irqs[i] < 0)
			वापस mc->irqs[i];

		err = devm_request_irq(&pdev->dev, mc->irqs[i], meson_irq_handler, 0,
				       "gxl-crypto", mc);
		अगर (err < 0) अणु
			dev_err(mc->dev, "Cannot request IRQ for flow %d\n", i);
			वापस err;
		पूर्ण
	पूर्ण

	err = clk_prepare_enable(mc->busclk);
	अगर (err != 0) अणु
		dev_err(&pdev->dev, "Cannot prepare_enable busclk\n");
		वापस err;
	पूर्ण

	err = meson_allocate_chanlist(mc);
	अगर (err)
		जाओ error_flow;

	err = meson_रेजिस्टर_algs(mc);
	अगर (err)
		जाओ error_alg;

#अगर_घोषित CONFIG_CRYPTO_DEV_AMLOGIC_GXL_DEBUG
	mc->dbgfs_dir = debugfs_create_dir("gxl-crypto", शून्य);
	debugfs_create_file("stats", 0444, mc->dbgfs_dir, mc, &meson_debugfs_fops);
#पूर्ण_अगर

	वापस 0;
error_alg:
	meson_unरेजिस्टर_algs(mc);
error_flow:
	meson_मुक्त_chanlist(mc, MAXFLOW - 1);
	clk_disable_unprepare(mc->busclk);
	वापस err;
पूर्ण

अटल पूर्णांक meson_crypto_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा meson_dev *mc = platक्रमm_get_drvdata(pdev);

#अगर_घोषित CONFIG_CRYPTO_DEV_AMLOGIC_GXL_DEBUG
	debugfs_हटाओ_recursive(mc->dbgfs_dir);
#पूर्ण_अगर

	meson_unरेजिस्टर_algs(mc);

	meson_मुक्त_chanlist(mc, MAXFLOW - 1);

	clk_disable_unprepare(mc->busclk);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id meson_crypto_of_match_table[] = अणु
	अणु .compatible = "amlogic,gxl-crypto", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, meson_crypto_of_match_table);

अटल काष्ठा platक्रमm_driver meson_crypto_driver = अणु
	.probe		 = meson_crypto_probe,
	.हटाओ		 = meson_crypto_हटाओ,
	.driver		 = अणु
		.name		   = "gxl-crypto",
		.of_match_table	= meson_crypto_of_match_table,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(meson_crypto_driver);

MODULE_DESCRIPTION("Amlogic GXL cryptographic offloader");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Corentin Labbe <clabbe@baylibre.com>");
