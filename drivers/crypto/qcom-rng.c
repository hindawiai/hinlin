<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2017-18 Linaro Limited
//
// Based on msm-rng.c and करोwnstream driver

#समावेश <crypto/पूर्णांकernal/rng.h>
#समावेश <linux/acpi.h>
#समावेश <linux/clk.h>
#समावेश <linux/crypto.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>

/* Device specअगरic रेजिस्टर offsets */
#घोषणा PRNG_DATA_OUT		0x0000
#घोषणा PRNG_STATUS		0x0004
#घोषणा PRNG_LFSR_CFG		0x0100
#घोषणा PRNG_CONFIG		0x0104

/* Device specअगरic रेजिस्टर masks and config values */
#घोषणा PRNG_LFSR_CFG_MASK	0x0000ffff
#घोषणा PRNG_LFSR_CFG_CLOCKS	0x0000dddd
#घोषणा PRNG_CONFIG_HW_ENABLE	BIT(1)
#घोषणा PRNG_STATUS_DATA_AVAIL	BIT(0)

#घोषणा WORD_SZ			4

काष्ठा qcom_rng अणु
	काष्ठा mutex lock;
	व्योम __iomem *base;
	काष्ठा clk *clk;
	अचिन्हित पूर्णांक skip_init;
पूर्ण;

काष्ठा qcom_rng_ctx अणु
	काष्ठा qcom_rng *rng;
पूर्ण;

अटल काष्ठा qcom_rng *qcom_rng_dev;

अटल पूर्णांक qcom_rng_पढ़ो(काष्ठा qcom_rng *rng, u8 *data, अचिन्हित पूर्णांक max)
अणु
	अचिन्हित पूर्णांक currsize = 0;
	u32 val;

	/* पढ़ो अक्रमom data from hardware */
	करो अणु
		val = पढ़ोl_relaxed(rng->base + PRNG_STATUS);
		अगर (!(val & PRNG_STATUS_DATA_AVAIL))
			अवरोध;

		val = पढ़ोl_relaxed(rng->base + PRNG_DATA_OUT);
		अगर (!val)
			अवरोध;

		अगर ((max - currsize) >= WORD_SZ) अणु
			स_नकल(data, &val, WORD_SZ);
			data += WORD_SZ;
			currsize += WORD_SZ;
		पूर्ण अन्यथा अणु
			/* copy only reमुख्यing bytes */
			स_नकल(data, &val, max - currsize);
			अवरोध;
		पूर्ण
	पूर्ण जबतक (currsize < max);

	वापस currsize;
पूर्ण

अटल पूर्णांक qcom_rng_generate(काष्ठा crypto_rng *tfm,
			     स्थिर u8 *src, अचिन्हित पूर्णांक slen,
			     u8 *dstn, अचिन्हित पूर्णांक dlen)
अणु
	काष्ठा qcom_rng_ctx *ctx = crypto_rng_ctx(tfm);
	काष्ठा qcom_rng *rng = ctx->rng;
	पूर्णांक ret;

	ret = clk_prepare_enable(rng->clk);
	अगर (ret)
		वापस ret;

	mutex_lock(&rng->lock);

	ret = qcom_rng_पढ़ो(rng, dstn, dlen);

	mutex_unlock(&rng->lock);
	clk_disable_unprepare(rng->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक qcom_rng_seed(काष्ठा crypto_rng *tfm, स्थिर u8 *seed,
			 अचिन्हित पूर्णांक slen)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक qcom_rng_enable(काष्ठा qcom_rng *rng)
अणु
	u32 val;
	पूर्णांक ret;

	ret = clk_prepare_enable(rng->clk);
	अगर (ret)
		वापस ret;

	/* Enable PRNG only अगर it is not alपढ़ोy enabled */
	val = पढ़ोl_relaxed(rng->base + PRNG_CONFIG);
	अगर (val & PRNG_CONFIG_HW_ENABLE)
		जाओ alपढ़ोy_enabled;

	val = पढ़ोl_relaxed(rng->base + PRNG_LFSR_CFG);
	val &= ~PRNG_LFSR_CFG_MASK;
	val |= PRNG_LFSR_CFG_CLOCKS;
	ग_लिखोl(val, rng->base + PRNG_LFSR_CFG);

	val = पढ़ोl_relaxed(rng->base + PRNG_CONFIG);
	val |= PRNG_CONFIG_HW_ENABLE;
	ग_लिखोl(val, rng->base + PRNG_CONFIG);

alपढ़ोy_enabled:
	clk_disable_unprepare(rng->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक qcom_rng_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा qcom_rng_ctx *ctx = crypto_tfm_ctx(tfm);

	ctx->rng = qcom_rng_dev;

	अगर (!ctx->rng->skip_init)
		वापस qcom_rng_enable(ctx->rng);

	वापस 0;
पूर्ण

अटल काष्ठा rng_alg qcom_rng_alg = अणु
	.generate	= qcom_rng_generate,
	.seed		= qcom_rng_seed,
	.seedsize	= 0,
	.base		= अणु
		.cra_name		= "stdrng",
		.cra_driver_name	= "qcom-rng",
		.cra_flags		= CRYPTO_ALG_TYPE_RNG,
		.cra_priority		= 300,
		.cra_ctxsize		= माप(काष्ठा qcom_rng_ctx),
		.cra_module		= THIS_MODULE,
		.cra_init		= qcom_rng_init,
	पूर्ण
पूर्ण;

अटल पूर्णांक qcom_rng_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा qcom_rng *rng;
	पूर्णांक ret;

	rng = devm_kzalloc(&pdev->dev, माप(*rng), GFP_KERNEL);
	अगर (!rng)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, rng);
	mutex_init(&rng->lock);

	rng->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(rng->base))
		वापस PTR_ERR(rng->base);

	/* ACPI प्रणालीs have clk alपढ़ोy on, so skip clk_get */
	अगर (!has_acpi_companion(&pdev->dev)) अणु
		rng->clk = devm_clk_get(&pdev->dev, "core");
		अगर (IS_ERR(rng->clk))
			वापस PTR_ERR(rng->clk);
	पूर्ण


	rng->skip_init = (अचिन्हित दीर्घ)device_get_match_data(&pdev->dev);

	qcom_rng_dev = rng;
	ret = crypto_रेजिस्टर_rng(&qcom_rng_alg);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Register crypto rng failed: %d\n", ret);
		qcom_rng_dev = शून्य;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक qcom_rng_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	crypto_unरेजिस्टर_rng(&qcom_rng_alg);

	qcom_rng_dev = शून्य;

	वापस 0;
पूर्ण

#अगर IS_ENABLED(CONFIG_ACPI)
अटल स्थिर काष्ठा acpi_device_id qcom_rng_acpi_match[] = अणु
	अणु .id = "QCOM8160", .driver_data = 1 पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, qcom_rng_acpi_match);
#पूर्ण_अगर

अटल स्थिर काष्ठा of_device_id qcom_rng_of_match[] = अणु
	अणु .compatible = "qcom,prng", .data = (व्योम *)0पूर्ण,
	अणु .compatible = "qcom,prng-ee", .data = (व्योम *)1पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, qcom_rng_of_match);

अटल काष्ठा platक्रमm_driver qcom_rng_driver = अणु
	.probe = qcom_rng_probe,
	.हटाओ =  qcom_rng_हटाओ,
	.driver = अणु
		.name = KBUILD_MODNAME,
		.of_match_table = of_match_ptr(qcom_rng_of_match),
		.acpi_match_table = ACPI_PTR(qcom_rng_acpi_match),
	पूर्ण
पूर्ण;
module_platक्रमm_driver(qcom_rng_driver);

MODULE_ALIAS("platform:" KBUILD_MODNAME);
MODULE_DESCRIPTION("Qualcomm random number generator driver");
MODULE_LICENSE("GPL v2");
