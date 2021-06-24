<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * sun4i-ss-core.c - hardware cryptographic accelerator क्रम Allwinner A20 SoC
 *
 * Copyright (C) 2013-2015 Corentin LABBE <clabbe.montjoie@gmail.com>
 *
 * Core file which रेजिस्टरs crypto algorithms supported by the SS.
 *
 * You could find a link क्रम the datasheet in Documentation/arm/sunxi.rst
 */
#समावेश <linux/clk.h>
#समावेश <linux/crypto.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <crypto/scatterwalk.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/reset.h>

#समावेश "sun4i-ss.h"

अटल स्थिर काष्ठा ss_variant ss_a10_variant = अणु
	.sha1_in_be = false,
पूर्ण;

अटल स्थिर काष्ठा ss_variant ss_a33_variant = अणु
	.sha1_in_be = true,
पूर्ण;

अटल काष्ठा sun4i_ss_alg_ढाँचा ss_algs[] = अणु
अणु       .type = CRYPTO_ALG_TYPE_AHASH,
	.mode = SS_OP_MD5,
	.alg.hash = अणु
		.init = sun4i_hash_init,
		.update = sun4i_hash_update,
		.final = sun4i_hash_final,
		.finup = sun4i_hash_finup,
		.digest = sun4i_hash_digest,
		.export = sun4i_hash_export_md5,
		.import = sun4i_hash_import_md5,
		.halg = अणु
			.digestsize = MD5_DIGEST_SIZE,
			.statesize = माप(काष्ठा md5_state),
			.base = अणु
				.cra_name = "md5",
				.cra_driver_name = "md5-sun4i-ss",
				.cra_priority = 300,
				.cra_alignmask = 3,
				.cra_blocksize = MD5_HMAC_BLOCK_SIZE,
				.cra_ctxsize = माप(काष्ठा sun4i_req_ctx),
				.cra_module = THIS_MODULE,
				.cra_init = sun4i_hash_crainit,
				.cra_निकास = sun4i_hash_craनिकास,
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण,
अणु       .type = CRYPTO_ALG_TYPE_AHASH,
	.mode = SS_OP_SHA1,
	.alg.hash = अणु
		.init = sun4i_hash_init,
		.update = sun4i_hash_update,
		.final = sun4i_hash_final,
		.finup = sun4i_hash_finup,
		.digest = sun4i_hash_digest,
		.export = sun4i_hash_export_sha1,
		.import = sun4i_hash_import_sha1,
		.halg = अणु
			.digestsize = SHA1_DIGEST_SIZE,
			.statesize = माप(काष्ठा sha1_state),
			.base = अणु
				.cra_name = "sha1",
				.cra_driver_name = "sha1-sun4i-ss",
				.cra_priority = 300,
				.cra_alignmask = 3,
				.cra_blocksize = SHA1_BLOCK_SIZE,
				.cra_ctxsize = माप(काष्ठा sun4i_req_ctx),
				.cra_module = THIS_MODULE,
				.cra_init = sun4i_hash_crainit,
				.cra_निकास = sun4i_hash_craनिकास,
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण,
अणु       .type = CRYPTO_ALG_TYPE_SKCIPHER,
	.alg.crypto = अणु
		.setkey         = sun4i_ss_aes_setkey,
		.encrypt        = sun4i_ss_cbc_aes_encrypt,
		.decrypt        = sun4i_ss_cbc_aes_decrypt,
		.min_keysize	= AES_MIN_KEY_SIZE,
		.max_keysize	= AES_MAX_KEY_SIZE,
		.ivsize		= AES_BLOCK_SIZE,
		.base = अणु
			.cra_name = "cbc(aes)",
			.cra_driver_name = "cbc-aes-sun4i-ss",
			.cra_priority = 300,
			.cra_blocksize = AES_BLOCK_SIZE,
			.cra_flags = CRYPTO_ALG_KERN_DRIVER_ONLY | CRYPTO_ALG_NEED_FALLBACK,
			.cra_ctxsize = माप(काष्ठा sun4i_tfm_ctx),
			.cra_module = THIS_MODULE,
			.cra_alignmask = 3,
			.cra_init = sun4i_ss_cipher_init,
			.cra_निकास = sun4i_ss_cipher_निकास,
		पूर्ण
	पूर्ण
पूर्ण,
अणु       .type = CRYPTO_ALG_TYPE_SKCIPHER,
	.alg.crypto = अणु
		.setkey         = sun4i_ss_aes_setkey,
		.encrypt        = sun4i_ss_ecb_aes_encrypt,
		.decrypt        = sun4i_ss_ecb_aes_decrypt,
		.min_keysize	= AES_MIN_KEY_SIZE,
		.max_keysize	= AES_MAX_KEY_SIZE,
		.base = अणु
			.cra_name = "ecb(aes)",
			.cra_driver_name = "ecb-aes-sun4i-ss",
			.cra_priority = 300,
			.cra_blocksize = AES_BLOCK_SIZE,
			.cra_flags = CRYPTO_ALG_KERN_DRIVER_ONLY | CRYPTO_ALG_NEED_FALLBACK,
			.cra_ctxsize = माप(काष्ठा sun4i_tfm_ctx),
			.cra_module = THIS_MODULE,
			.cra_alignmask = 3,
			.cra_init = sun4i_ss_cipher_init,
			.cra_निकास = sun4i_ss_cipher_निकास,
		पूर्ण
	पूर्ण
पूर्ण,
अणु       .type = CRYPTO_ALG_TYPE_SKCIPHER,
	.alg.crypto = अणु
		.setkey         = sun4i_ss_des_setkey,
		.encrypt        = sun4i_ss_cbc_des_encrypt,
		.decrypt        = sun4i_ss_cbc_des_decrypt,
		.min_keysize    = DES_KEY_SIZE,
		.max_keysize    = DES_KEY_SIZE,
		.ivsize         = DES_BLOCK_SIZE,
		.base = अणु
			.cra_name = "cbc(des)",
			.cra_driver_name = "cbc-des-sun4i-ss",
			.cra_priority = 300,
			.cra_blocksize = DES_BLOCK_SIZE,
			.cra_flags = CRYPTO_ALG_KERN_DRIVER_ONLY | CRYPTO_ALG_NEED_FALLBACK,
			.cra_ctxsize = माप(काष्ठा sun4i_req_ctx),
			.cra_module = THIS_MODULE,
			.cra_alignmask = 3,
			.cra_init = sun4i_ss_cipher_init,
			.cra_निकास = sun4i_ss_cipher_निकास,
		पूर्ण
	पूर्ण
पूर्ण,
अणु       .type = CRYPTO_ALG_TYPE_SKCIPHER,
	.alg.crypto = अणु
		.setkey         = sun4i_ss_des_setkey,
		.encrypt        = sun4i_ss_ecb_des_encrypt,
		.decrypt        = sun4i_ss_ecb_des_decrypt,
		.min_keysize    = DES_KEY_SIZE,
		.max_keysize    = DES_KEY_SIZE,
		.base = अणु
			.cra_name = "ecb(des)",
			.cra_driver_name = "ecb-des-sun4i-ss",
			.cra_priority = 300,
			.cra_blocksize = DES_BLOCK_SIZE,
			.cra_flags = CRYPTO_ALG_KERN_DRIVER_ONLY | CRYPTO_ALG_NEED_FALLBACK,
			.cra_ctxsize = माप(काष्ठा sun4i_req_ctx),
			.cra_module = THIS_MODULE,
			.cra_alignmask = 3,
			.cra_init = sun4i_ss_cipher_init,
			.cra_निकास = sun4i_ss_cipher_निकास,
		पूर्ण
	पूर्ण
पूर्ण,
अणु       .type = CRYPTO_ALG_TYPE_SKCIPHER,
	.alg.crypto = अणु
		.setkey         = sun4i_ss_des3_setkey,
		.encrypt        = sun4i_ss_cbc_des3_encrypt,
		.decrypt        = sun4i_ss_cbc_des3_decrypt,
		.min_keysize    = DES3_EDE_KEY_SIZE,
		.max_keysize    = DES3_EDE_KEY_SIZE,
		.ivsize         = DES3_EDE_BLOCK_SIZE,
		.base = अणु
			.cra_name = "cbc(des3_ede)",
			.cra_driver_name = "cbc-des3-sun4i-ss",
			.cra_priority = 300,
			.cra_blocksize = DES3_EDE_BLOCK_SIZE,
			.cra_flags = CRYPTO_ALG_KERN_DRIVER_ONLY | CRYPTO_ALG_NEED_FALLBACK,
			.cra_ctxsize = माप(काष्ठा sun4i_req_ctx),
			.cra_module = THIS_MODULE,
			.cra_alignmask = 3,
			.cra_init = sun4i_ss_cipher_init,
			.cra_निकास = sun4i_ss_cipher_निकास,
		पूर्ण
	पूर्ण
पूर्ण,
अणु       .type = CRYPTO_ALG_TYPE_SKCIPHER,
	.alg.crypto = अणु
		.setkey         = sun4i_ss_des3_setkey,
		.encrypt        = sun4i_ss_ecb_des3_encrypt,
		.decrypt        = sun4i_ss_ecb_des3_decrypt,
		.min_keysize    = DES3_EDE_KEY_SIZE,
		.max_keysize    = DES3_EDE_KEY_SIZE,
		.base = अणु
			.cra_name = "ecb(des3_ede)",
			.cra_driver_name = "ecb-des3-sun4i-ss",
			.cra_priority = 300,
			.cra_blocksize = DES3_EDE_BLOCK_SIZE,
			.cra_flags = CRYPTO_ALG_KERN_DRIVER_ONLY | CRYPTO_ALG_NEED_FALLBACK,
			.cra_ctxsize = माप(काष्ठा sun4i_req_ctx),
			.cra_module = THIS_MODULE,
			.cra_alignmask = 3,
			.cra_init = sun4i_ss_cipher_init,
			.cra_निकास = sun4i_ss_cipher_निकास,
		पूर्ण
	पूर्ण
पूर्ण,
#अगर_घोषित CONFIG_CRYPTO_DEV_SUN4I_SS_PRNG
अणु
	.type = CRYPTO_ALG_TYPE_RNG,
	.alg.rng = अणु
		.base = अणु
			.cra_name		= "stdrng",
			.cra_driver_name	= "sun4i_ss_rng",
			.cra_priority		= 300,
			.cra_ctxsize		= 0,
			.cra_module		= THIS_MODULE,
		पूर्ण,
		.generate               = sun4i_ss_prng_generate,
		.seed                   = sun4i_ss_prng_seed,
		.seedsize               = SS_SEED_LEN / BITS_PER_BYTE,
	पूर्ण
पूर्ण,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक sun4i_ss_dbgfs_पढ़ो(काष्ठा seq_file *seq, व्योम *v)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(ss_algs); i++) अणु
		अगर (!ss_algs[i].ss)
			जारी;
		चयन (ss_algs[i].type) अणु
		हाल CRYPTO_ALG_TYPE_SKCIPHER:
			seq_म_लिखो(seq, "%s %s reqs=%lu opti=%lu fallback=%lu tsize=%lu\n",
				   ss_algs[i].alg.crypto.base.cra_driver_name,
				   ss_algs[i].alg.crypto.base.cra_name,
				   ss_algs[i].stat_req, ss_algs[i].stat_opti, ss_algs[i].stat_fb,
				   ss_algs[i].stat_bytes);
			अवरोध;
		हाल CRYPTO_ALG_TYPE_RNG:
			seq_म_लिखो(seq, "%s %s reqs=%lu tsize=%lu\n",
				   ss_algs[i].alg.rng.base.cra_driver_name,
				   ss_algs[i].alg.rng.base.cra_name,
				   ss_algs[i].stat_req, ss_algs[i].stat_bytes);
			अवरोध;
		हाल CRYPTO_ALG_TYPE_AHASH:
			seq_म_लिखो(seq, "%s %s reqs=%lu\n",
				   ss_algs[i].alg.hash.halg.base.cra_driver_name,
				   ss_algs[i].alg.hash.halg.base.cra_name,
				   ss_algs[i].stat_req);
			अवरोध;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक sun4i_ss_dbgfs_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, sun4i_ss_dbgfs_पढ़ो, inode->i_निजी);
पूर्ण

अटल स्थिर काष्ठा file_operations sun4i_ss_debugfs_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = sun4i_ss_dbgfs_खोलो,
	.पढ़ो = seq_पढ़ो,
	.llseek = seq_lseek,
	.release = single_release,
पूर्ण;

/*
 * Power management strategy: The device is suspended unless a TFM exists क्रम
 * one of the algorithms proposed by this driver.
 */
अटल पूर्णांक sun4i_ss_pm_suspend(काष्ठा device *dev)
अणु
	काष्ठा sun4i_ss_ctx *ss = dev_get_drvdata(dev);

	reset_control_निश्चित(ss->reset);

	clk_disable_unprepare(ss->ssclk);
	clk_disable_unprepare(ss->busclk);
	वापस 0;
पूर्ण

अटल पूर्णांक sun4i_ss_pm_resume(काष्ठा device *dev)
अणु
	काष्ठा sun4i_ss_ctx *ss = dev_get_drvdata(dev);

	पूर्णांक err;

	err = clk_prepare_enable(ss->busclk);
	अगर (err) अणु
		dev_err(ss->dev, "Cannot prepare_enable busclk\n");
		जाओ err_enable;
	पूर्ण

	err = clk_prepare_enable(ss->ssclk);
	अगर (err) अणु
		dev_err(ss->dev, "Cannot prepare_enable ssclk\n");
		जाओ err_enable;
	पूर्ण

	err = reset_control_deनिश्चित(ss->reset);
	अगर (err) अणु
		dev_err(ss->dev, "Cannot deassert reset control\n");
		जाओ err_enable;
	पूर्ण

	वापस err;
err_enable:
	sun4i_ss_pm_suspend(dev);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops sun4i_ss_pm_ops = अणु
	SET_RUNTIME_PM_OPS(sun4i_ss_pm_suspend, sun4i_ss_pm_resume, शून्य)
पूर्ण;

/*
 * When घातer management is enabled, this function enables the PM and set the
 * device as suspended
 * When घातer management is disabled, this function just enables the device
 */
अटल पूर्णांक sun4i_ss_pm_init(काष्ठा sun4i_ss_ctx *ss)
अणु
	पूर्णांक err;

	pm_runसमय_use_स्वतःsuspend(ss->dev);
	pm_runसमय_set_स्वतःsuspend_delay(ss->dev, 2000);

	err = pm_runसमय_set_suspended(ss->dev);
	अगर (err)
		वापस err;
	pm_runसमय_enable(ss->dev);
	वापस err;
पूर्ण

अटल व्योम sun4i_ss_pm_निकास(काष्ठा sun4i_ss_ctx *ss)
अणु
	pm_runसमय_disable(ss->dev);
पूर्ण

अटल पूर्णांक sun4i_ss_probe(काष्ठा platक्रमm_device *pdev)
अणु
	u32 v;
	पूर्णांक err, i;
	अचिन्हित दीर्घ cr;
	स्थिर अचिन्हित दीर्घ cr_ahb = 24 * 1000 * 1000;
	स्थिर अचिन्हित दीर्घ cr_mod = 150 * 1000 * 1000;
	काष्ठा sun4i_ss_ctx *ss;

	अगर (!pdev->dev.of_node)
		वापस -ENODEV;

	ss = devm_kzalloc(&pdev->dev, माप(*ss), GFP_KERNEL);
	अगर (!ss)
		वापस -ENOMEM;

	ss->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(ss->base)) अणु
		dev_err(&pdev->dev, "Cannot request MMIO\n");
		वापस PTR_ERR(ss->base);
	पूर्ण

	ss->variant = of_device_get_match_data(&pdev->dev);
	अगर (!ss->variant) अणु
		dev_err(&pdev->dev, "Missing Security System variant\n");
		वापस -EINVAL;
	पूर्ण

	ss->ssclk = devm_clk_get(&pdev->dev, "mod");
	अगर (IS_ERR(ss->ssclk)) अणु
		err = PTR_ERR(ss->ssclk);
		dev_err(&pdev->dev, "Cannot get SS clock err=%d\n", err);
		वापस err;
	पूर्ण
	dev_dbg(&pdev->dev, "clock ss acquired\n");

	ss->busclk = devm_clk_get(&pdev->dev, "ahb");
	अगर (IS_ERR(ss->busclk)) अणु
		err = PTR_ERR(ss->busclk);
		dev_err(&pdev->dev, "Cannot get AHB SS clock err=%d\n", err);
		वापस err;
	पूर्ण
	dev_dbg(&pdev->dev, "clock ahb_ss acquired\n");

	ss->reset = devm_reset_control_get_optional(&pdev->dev, "ahb");
	अगर (IS_ERR(ss->reset))
		वापस PTR_ERR(ss->reset);
	अगर (!ss->reset)
		dev_info(&pdev->dev, "no reset control found\n");

	/*
	 * Check that घड़ी have the correct rates given in the datasheet
	 * Try to set the घड़ी to the maximum allowed
	 */
	err = clk_set_rate(ss->ssclk, cr_mod);
	अगर (err) अणु
		dev_err(&pdev->dev, "Cannot set clock rate to ssclk\n");
		वापस err;
	पूर्ण

	/*
	 * The only impact on घड़ीs below requirement are bad perक्रमmance,
	 * so करो not prपूर्णांक "errors"
	 * warn on Overघड़ीed घड़ीs
	 */
	cr = clk_get_rate(ss->busclk);
	अगर (cr >= cr_ahb)
		dev_dbg(&pdev->dev, "Clock bus %lu (%lu MHz) (must be >= %lu)\n",
			cr, cr / 1000000, cr_ahb);
	अन्यथा
		dev_warn(&pdev->dev, "Clock bus %lu (%lu MHz) (must be >= %lu)\n",
			 cr, cr / 1000000, cr_ahb);

	cr = clk_get_rate(ss->ssclk);
	अगर (cr <= cr_mod)
		अगर (cr < cr_mod)
			dev_warn(&pdev->dev, "Clock ss %lu (%lu MHz) (must be <= %lu)\n",
				 cr, cr / 1000000, cr_mod);
		अन्यथा
			dev_dbg(&pdev->dev, "Clock ss %lu (%lu MHz) (must be <= %lu)\n",
				cr, cr / 1000000, cr_mod);
	अन्यथा
		dev_warn(&pdev->dev, "Clock ss is at %lu (%lu MHz) (must be <= %lu)\n",
			 cr, cr / 1000000, cr_mod);

	ss->dev = &pdev->dev;
	platक्रमm_set_drvdata(pdev, ss);

	spin_lock_init(&ss->slock);

	err = sun4i_ss_pm_init(ss);
	अगर (err)
		वापस err;

	/*
	 * Datasheet named it "Die Bonding ID"
	 * I expect to be a sort of Security System Revision number.
	 * Since the A80 seems to have an other version of SS
	 * this info could be useful
	 */

	err = pm_runसमय_resume_and_get(ss->dev);
	अगर (err < 0)
		जाओ error_pm;

	ग_लिखोl(SS_ENABLED, ss->base + SS_CTL);
	v = पढ़ोl(ss->base + SS_CTL);
	v >>= 16;
	v &= 0x07;
	dev_info(&pdev->dev, "Die ID %d\n", v);
	ग_लिखोl(0, ss->base + SS_CTL);

	pm_runसमय_put_sync(ss->dev);

	क्रम (i = 0; i < ARRAY_SIZE(ss_algs); i++) अणु
		ss_algs[i].ss = ss;
		चयन (ss_algs[i].type) अणु
		हाल CRYPTO_ALG_TYPE_SKCIPHER:
			err = crypto_रेजिस्टर_skcipher(&ss_algs[i].alg.crypto);
			अगर (err) अणु
				dev_err(ss->dev, "Fail to register %s\n",
					ss_algs[i].alg.crypto.base.cra_name);
				जाओ error_alg;
			पूर्ण
			अवरोध;
		हाल CRYPTO_ALG_TYPE_AHASH:
			err = crypto_रेजिस्टर_ahash(&ss_algs[i].alg.hash);
			अगर (err) अणु
				dev_err(ss->dev, "Fail to register %s\n",
					ss_algs[i].alg.hash.halg.base.cra_name);
				जाओ error_alg;
			पूर्ण
			अवरोध;
		हाल CRYPTO_ALG_TYPE_RNG:
			err = crypto_रेजिस्टर_rng(&ss_algs[i].alg.rng);
			अगर (err) अणु
				dev_err(ss->dev, "Fail to register %s\n",
					ss_algs[i].alg.rng.base.cra_name);
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण

	/* Ignore error of debugfs */
	ss->dbgfs_dir = debugfs_create_dir("sun4i-ss", शून्य);
	ss->dbgfs_stats = debugfs_create_file("stats", 0444, ss->dbgfs_dir, ss,
					      &sun4i_ss_debugfs_fops);

	वापस 0;
error_alg:
	i--;
	क्रम (; i >= 0; i--) अणु
		चयन (ss_algs[i].type) अणु
		हाल CRYPTO_ALG_TYPE_SKCIPHER:
			crypto_unरेजिस्टर_skcipher(&ss_algs[i].alg.crypto);
			अवरोध;
		हाल CRYPTO_ALG_TYPE_AHASH:
			crypto_unरेजिस्टर_ahash(&ss_algs[i].alg.hash);
			अवरोध;
		हाल CRYPTO_ALG_TYPE_RNG:
			crypto_unरेजिस्टर_rng(&ss_algs[i].alg.rng);
			अवरोध;
		पूर्ण
	पूर्ण
error_pm:
	sun4i_ss_pm_निकास(ss);
	वापस err;
पूर्ण

अटल पूर्णांक sun4i_ss_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक i;
	काष्ठा sun4i_ss_ctx *ss = platक्रमm_get_drvdata(pdev);

	क्रम (i = 0; i < ARRAY_SIZE(ss_algs); i++) अणु
		चयन (ss_algs[i].type) अणु
		हाल CRYPTO_ALG_TYPE_SKCIPHER:
			crypto_unरेजिस्टर_skcipher(&ss_algs[i].alg.crypto);
			अवरोध;
		हाल CRYPTO_ALG_TYPE_AHASH:
			crypto_unरेजिस्टर_ahash(&ss_algs[i].alg.hash);
			अवरोध;
		हाल CRYPTO_ALG_TYPE_RNG:
			crypto_unरेजिस्टर_rng(&ss_algs[i].alg.rng);
			अवरोध;
		पूर्ण
	पूर्ण

	sun4i_ss_pm_निकास(ss);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id a20ss_crypto_of_match_table[] = अणु
	अणु .compatible = "allwinner,sun4i-a10-crypto",
	  .data = &ss_a10_variant
	पूर्ण,
	अणु .compatible = "allwinner,sun8i-a33-crypto",
	  .data = &ss_a33_variant
	पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, a20ss_crypto_of_match_table);

अटल काष्ठा platक्रमm_driver sun4i_ss_driver = अणु
	.probe          = sun4i_ss_probe,
	.हटाओ         = sun4i_ss_हटाओ,
	.driver         = अणु
		.name           = "sun4i-ss",
		.pm		= &sun4i_ss_pm_ops,
		.of_match_table	= a20ss_crypto_of_match_table,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(sun4i_ss_driver);

MODULE_ALIAS("platform:sun4i-ss");
MODULE_DESCRIPTION("Allwinner Security System cryptographic accelerator");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Corentin LABBE <clabbe.montjoie@gmail.com>");
