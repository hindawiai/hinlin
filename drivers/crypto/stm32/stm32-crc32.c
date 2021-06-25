<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) STMicroelectronics SA 2017
 * Author: Fabien Dessenne <fabien.dessenne@st.com>
 */

#समावेश <linux/bitrev.h>
#समावेश <linux/clk.h>
#समावेश <linux/crc32.h>
#समावेश <linux/crc32poly.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>

#समावेश <crypto/पूर्णांकernal/hash.h>

#समावेश <यंत्र/unaligned.h>

#घोषणा DRIVER_NAME             "stm32-crc32"
#घोषणा CHKSUM_DIGEST_SIZE      4
#घोषणा CHKSUM_BLOCK_SIZE       1

/* Registers */
#घोषणा CRC_DR                  0x00000000
#घोषणा CRC_CR                  0x00000008
#घोषणा CRC_INIT                0x00000010
#घोषणा CRC_POL                 0x00000014

/* Registers values */
#घोषणा CRC_CR_RESET            BIT(0)
#घोषणा CRC_CR_REV_IN_WORD      (BIT(6) | BIT(5))
#घोषणा CRC_CR_REV_IN_BYTE      BIT(5)
#घोषणा CRC_CR_REV_OUT          BIT(7)
#घोषणा CRC32C_INIT_DEFAULT     0xFFFFFFFF

#घोषणा CRC_AUTOSUSPEND_DELAY	50

अटल अचिन्हित पूर्णांक burst_size;
module_param(burst_size, uपूर्णांक, 0644);
MODULE_PARM_DESC(burst_size, "Select burst byte size (0 unlimited)");

काष्ठा sपंचांग32_crc अणु
	काष्ठा list_head list;
	काष्ठा device    *dev;
	व्योम __iomem     *regs;
	काष्ठा clk       *clk;
	spinlock_t       lock;
पूर्ण;

काष्ठा sपंचांग32_crc_list अणु
	काष्ठा list_head dev_list;
	spinlock_t       lock; /* protect dev_list */
पूर्ण;

अटल काष्ठा sपंचांग32_crc_list crc_list = अणु
	.dev_list = LIST_HEAD_INIT(crc_list.dev_list),
	.lock     = __SPIN_LOCK_UNLOCKED(crc_list.lock),
पूर्ण;

काष्ठा sपंचांग32_crc_ctx अणु
	u32 key;
	u32 poly;
पूर्ण;

काष्ठा sपंचांग32_crc_desc_ctx अणु
	u32    partial; /* crc32c: partial in first 4 bytes of that काष्ठा */
पूर्ण;

अटल पूर्णांक sपंचांग32_crc32_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा sपंचांग32_crc_ctx *mctx = crypto_tfm_ctx(tfm);

	mctx->key = 0;
	mctx->poly = CRC32_POLY_LE;
	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_crc32c_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा sपंचांग32_crc_ctx *mctx = crypto_tfm_ctx(tfm);

	mctx->key = CRC32C_INIT_DEFAULT;
	mctx->poly = CRC32C_POLY_LE;
	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_crc_setkey(काष्ठा crypto_shash *tfm, स्थिर u8 *key,
			    अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा sपंचांग32_crc_ctx *mctx = crypto_shash_ctx(tfm);

	अगर (keylen != माप(u32))
		वापस -EINVAL;

	mctx->key = get_unaligned_le32(key);
	वापस 0;
पूर्ण

अटल काष्ठा sपंचांग32_crc *sपंचांग32_crc_get_next_crc(व्योम)
अणु
	काष्ठा sपंचांग32_crc *crc;

	spin_lock_bh(&crc_list.lock);
	crc = list_first_entry(&crc_list.dev_list, काष्ठा sपंचांग32_crc, list);
	अगर (crc)
		list_move_tail(&crc->list, &crc_list.dev_list);
	spin_unlock_bh(&crc_list.lock);

	वापस crc;
पूर्ण

अटल पूर्णांक sपंचांग32_crc_init(काष्ठा shash_desc *desc)
अणु
	काष्ठा sपंचांग32_crc_desc_ctx *ctx = shash_desc_ctx(desc);
	काष्ठा sपंचांग32_crc_ctx *mctx = crypto_shash_ctx(desc->tfm);
	काष्ठा sपंचांग32_crc *crc;
	अचिन्हित दीर्घ flags;

	crc = sपंचांग32_crc_get_next_crc();
	अगर (!crc)
		वापस -ENODEV;

	pm_runसमय_get_sync(crc->dev);

	spin_lock_irqsave(&crc->lock, flags);

	/* Reset, set key, poly and configure in bit reverse mode */
	ग_लिखोl_relaxed(bitrev32(mctx->key), crc->regs + CRC_INIT);
	ग_लिखोl_relaxed(bitrev32(mctx->poly), crc->regs + CRC_POL);
	ग_लिखोl_relaxed(CRC_CR_RESET | CRC_CR_REV_IN_WORD | CRC_CR_REV_OUT,
		       crc->regs + CRC_CR);

	/* Store partial result */
	ctx->partial = पढ़ोl_relaxed(crc->regs + CRC_DR);

	spin_unlock_irqrestore(&crc->lock, flags);

	pm_runसमय_mark_last_busy(crc->dev);
	pm_runसमय_put_स्वतःsuspend(crc->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक burst_update(काष्ठा shash_desc *desc, स्थिर u8 *d8,
			माप_प्रकार length)
अणु
	काष्ठा sपंचांग32_crc_desc_ctx *ctx = shash_desc_ctx(desc);
	काष्ठा sपंचांग32_crc_ctx *mctx = crypto_shash_ctx(desc->tfm);
	काष्ठा sपंचांग32_crc *crc;

	crc = sपंचांग32_crc_get_next_crc();
	अगर (!crc)
		वापस -ENODEV;

	pm_runसमय_get_sync(crc->dev);

	अगर (!spin_trylock(&crc->lock)) अणु
		/* Hardware is busy, calculate crc32 by software */
		अगर (mctx->poly == CRC32_POLY_LE)
			ctx->partial = crc32_le(ctx->partial, d8, length);
		अन्यथा
			ctx->partial = __crc32c_le(ctx->partial, d8, length);

		जाओ pm_out;
	पूर्ण

	/*
	 * Restore previously calculated CRC क्रम this context as init value
	 * Restore polynomial configuration
	 * Configure in रेजिस्टर क्रम word input data,
	 * Configure out रेजिस्टर in reversed bit mode data.
	 */
	ग_लिखोl_relaxed(bitrev32(ctx->partial), crc->regs + CRC_INIT);
	ग_लिखोl_relaxed(bitrev32(mctx->poly), crc->regs + CRC_POL);
	ग_लिखोl_relaxed(CRC_CR_RESET | CRC_CR_REV_IN_WORD | CRC_CR_REV_OUT,
		       crc->regs + CRC_CR);

	अगर (d8 != PTR_ALIGN(d8, माप(u32))) अणु
		/* Configure क्रम byte data */
		ग_लिखोl_relaxed(CRC_CR_REV_IN_BYTE | CRC_CR_REV_OUT,
			       crc->regs + CRC_CR);
		जबतक (d8 != PTR_ALIGN(d8, माप(u32)) && length) अणु
			ग_लिखोb_relaxed(*d8++, crc->regs + CRC_DR);
			length--;
		पूर्ण
		/* Configure क्रम word data */
		ग_लिखोl_relaxed(CRC_CR_REV_IN_WORD | CRC_CR_REV_OUT,
			       crc->regs + CRC_CR);
	पूर्ण

	क्रम (; length >= माप(u32); d8 += माप(u32), length -= माप(u32))
		ग_लिखोl_relaxed(*((u32 *)d8), crc->regs + CRC_DR);

	अगर (length) अणु
		/* Configure क्रम byte data */
		ग_लिखोl_relaxed(CRC_CR_REV_IN_BYTE | CRC_CR_REV_OUT,
			       crc->regs + CRC_CR);
		जबतक (length--)
			ग_लिखोb_relaxed(*d8++, crc->regs + CRC_DR);
	पूर्ण

	/* Store partial result */
	ctx->partial = पढ़ोl_relaxed(crc->regs + CRC_DR);

	spin_unlock(&crc->lock);

pm_out:
	pm_runसमय_mark_last_busy(crc->dev);
	pm_runसमय_put_स्वतःsuspend(crc->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_crc_update(काष्ठा shash_desc *desc, स्थिर u8 *d8,
			    अचिन्हित पूर्णांक length)
अणु
	स्थिर अचिन्हित पूर्णांक burst_sz = burst_size;
	अचिन्हित पूर्णांक rem_sz;
	स्थिर u8 *cur;
	माप_प्रकार size;
	पूर्णांक ret;

	अगर (!burst_sz)
		वापस burst_update(desc, d8, length);

	/* Digest first bytes not 32bit aligned at first pass in the loop */
	size = min_t(माप_प्रकार, length, burst_sz + (माप_प्रकार)d8 -
				     ALIGN_DOWN((माप_प्रकार)d8, माप(u32)));
	क्रम (rem_sz = length, cur = d8; rem_sz;
	     rem_sz -= size, cur += size, size = min(rem_sz, burst_sz)) अणु
		ret = burst_update(desc, cur, size);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_crc_final(काष्ठा shash_desc *desc, u8 *out)
अणु
	काष्ठा sपंचांग32_crc_desc_ctx *ctx = shash_desc_ctx(desc);
	काष्ठा sपंचांग32_crc_ctx *mctx = crypto_shash_ctx(desc->tfm);

	/* Send computed CRC */
	put_unaligned_le32(mctx->poly == CRC32C_POLY_LE ?
			   ~ctx->partial : ctx->partial, out);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_crc_finup(काष्ठा shash_desc *desc, स्थिर u8 *data,
			   अचिन्हित पूर्णांक length, u8 *out)
अणु
	वापस sपंचांग32_crc_update(desc, data, length) ?:
	       sपंचांग32_crc_final(desc, out);
पूर्ण

अटल पूर्णांक sपंचांग32_crc_digest(काष्ठा shash_desc *desc, स्थिर u8 *data,
			    अचिन्हित पूर्णांक length, u8 *out)
अणु
	वापस sपंचांग32_crc_init(desc) ?: sपंचांग32_crc_finup(desc, data, length, out);
पूर्ण

अटल अचिन्हित पूर्णांक refcnt;
अटल DEFINE_MUTEX(refcnt_lock);
अटल काष्ठा shash_alg algs[] = अणु
	/* CRC-32 */
	अणु
		.setkey         = sपंचांग32_crc_setkey,
		.init           = sपंचांग32_crc_init,
		.update         = sपंचांग32_crc_update,
		.final          = sपंचांग32_crc_final,
		.finup          = sपंचांग32_crc_finup,
		.digest         = sपंचांग32_crc_digest,
		.descsize       = माप(काष्ठा sपंचांग32_crc_desc_ctx),
		.digestsize     = CHKSUM_DIGEST_SIZE,
		.base           = अणु
			.cra_name               = "crc32",
			.cra_driver_name        = DRIVER_NAME,
			.cra_priority           = 200,
			.cra_flags		= CRYPTO_ALG_OPTIONAL_KEY,
			.cra_blocksize          = CHKSUM_BLOCK_SIZE,
			.cra_alignmask          = 3,
			.cra_ctxsize            = माप(काष्ठा sपंचांग32_crc_ctx),
			.cra_module             = THIS_MODULE,
			.cra_init               = sपंचांग32_crc32_cra_init,
		पूर्ण
	पूर्ण,
	/* CRC-32Castagnoli */
	अणु
		.setkey         = sपंचांग32_crc_setkey,
		.init           = sपंचांग32_crc_init,
		.update         = sपंचांग32_crc_update,
		.final          = sपंचांग32_crc_final,
		.finup          = sपंचांग32_crc_finup,
		.digest         = sपंचांग32_crc_digest,
		.descsize       = माप(काष्ठा sपंचांग32_crc_desc_ctx),
		.digestsize     = CHKSUM_DIGEST_SIZE,
		.base           = अणु
			.cra_name               = "crc32c",
			.cra_driver_name        = DRIVER_NAME,
			.cra_priority           = 200,
			.cra_flags		= CRYPTO_ALG_OPTIONAL_KEY,
			.cra_blocksize          = CHKSUM_BLOCK_SIZE,
			.cra_alignmask          = 3,
			.cra_ctxsize            = माप(काष्ठा sपंचांग32_crc_ctx),
			.cra_module             = THIS_MODULE,
			.cra_init               = sपंचांग32_crc32c_cra_init,
		पूर्ण
	पूर्ण
पूर्ण;

अटल पूर्णांक sपंचांग32_crc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा sपंचांग32_crc *crc;
	पूर्णांक ret;

	crc = devm_kzalloc(dev, माप(*crc), GFP_KERNEL);
	अगर (!crc)
		वापस -ENOMEM;

	crc->dev = dev;

	crc->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(crc->regs)) अणु
		dev_err(dev, "Cannot map CRC IO\n");
		वापस PTR_ERR(crc->regs);
	पूर्ण

	crc->clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(crc->clk)) अणु
		dev_err(dev, "Could not get clock\n");
		वापस PTR_ERR(crc->clk);
	पूर्ण

	ret = clk_prepare_enable(crc->clk);
	अगर (ret) अणु
		dev_err(crc->dev, "Failed to enable clock\n");
		वापस ret;
	पूर्ण

	pm_runसमय_set_स्वतःsuspend_delay(dev, CRC_AUTOSUSPEND_DELAY);
	pm_runसमय_use_स्वतःsuspend(dev);

	pm_runसमय_get_noresume(dev);
	pm_runसमय_set_active(dev);
	pm_runसमय_irq_safe(dev);
	pm_runसमय_enable(dev);

	spin_lock_init(&crc->lock);

	platक्रमm_set_drvdata(pdev, crc);

	spin_lock(&crc_list.lock);
	list_add(&crc->list, &crc_list.dev_list);
	spin_unlock(&crc_list.lock);

	mutex_lock(&refcnt_lock);
	अगर (!refcnt) अणु
		ret = crypto_रेजिस्टर_shashes(algs, ARRAY_SIZE(algs));
		अगर (ret) अणु
			mutex_unlock(&refcnt_lock);
			dev_err(dev, "Failed to register\n");
			clk_disable_unprepare(crc->clk);
			वापस ret;
		पूर्ण
	पूर्ण
	refcnt++;
	mutex_unlock(&refcnt_lock);

	dev_info(dev, "Initialized\n");

	pm_runसमय_put_sync(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_crc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sपंचांग32_crc *crc = platक्रमm_get_drvdata(pdev);
	पूर्णांक ret = pm_runसमय_get_sync(crc->dev);

	अगर (ret < 0)
		वापस ret;

	spin_lock(&crc_list.lock);
	list_del(&crc->list);
	spin_unlock(&crc_list.lock);

	mutex_lock(&refcnt_lock);
	अगर (!--refcnt)
		crypto_unरेजिस्टर_shashes(algs, ARRAY_SIZE(algs));
	mutex_unlock(&refcnt_lock);

	pm_runसमय_disable(crc->dev);
	pm_runसमय_put_noidle(crc->dev);

	clk_disable_unprepare(crc->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused sपंचांग32_crc_suspend(काष्ठा device *dev)
अणु
	काष्ठा sपंचांग32_crc *crc = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = pm_runसमय_क्रमce_suspend(dev);
	अगर (ret)
		वापस ret;

	clk_unprepare(crc->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused sपंचांग32_crc_resume(काष्ठा device *dev)
अणु
	काष्ठा sपंचांग32_crc *crc = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = clk_prepare(crc->clk);
	अगर (ret) अणु
		dev_err(crc->dev, "Failed to prepare clock\n");
		वापस ret;
	पूर्ण

	वापस pm_runसमय_क्रमce_resume(dev);
पूर्ण

अटल पूर्णांक __maybe_unused sपंचांग32_crc_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा sपंचांग32_crc *crc = dev_get_drvdata(dev);

	clk_disable(crc->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused sपंचांग32_crc_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा sपंचांग32_crc *crc = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = clk_enable(crc->clk);
	अगर (ret) अणु
		dev_err(crc->dev, "Failed to enable clock\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops sपंचांग32_crc_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(sपंचांग32_crc_suspend,
				sपंचांग32_crc_resume)
	SET_RUNTIME_PM_OPS(sपंचांग32_crc_runसमय_suspend,
			   sपंचांग32_crc_runसमय_resume, शून्य)
पूर्ण;

अटल स्थिर काष्ठा of_device_id sपंचांग32_dt_ids[] = अणु
	अणु .compatible = "st,stm32f7-crc", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sपंचांग32_dt_ids);

अटल काष्ठा platक्रमm_driver sपंचांग32_crc_driver = अणु
	.probe  = sपंचांग32_crc_probe,
	.हटाओ = sपंचांग32_crc_हटाओ,
	.driver = अणु
		.name           = DRIVER_NAME,
		.pm		= &sपंचांग32_crc_pm_ops,
		.of_match_table = sपंचांग32_dt_ids,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(sपंचांग32_crc_driver);

MODULE_AUTHOR("Fabien Dessenne <fabien.dessenne@st.com>");
MODULE_DESCRIPTION("STMicrolectronics STM32 CRC32 hardware driver");
MODULE_LICENSE("GPL");
