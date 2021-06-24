<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * exynos-rng.c - Ranकरोm Number Generator driver क्रम the Exynos
 *
 * Copyright (c) 2017 Krzysztof Kozlowski <krzk@kernel.org>
 *
 * Loosely based on old driver from drivers/अक्षर/hw_अक्रमom/exynos-rng.c:
 * Copyright (C) 2012 Samsung Electronics
 * Jonghwa Lee <jonghwa3.lee@samsung.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/crypto.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <crypto/पूर्णांकernal/rng.h>

#घोषणा EXYNOS_RNG_CONTROL		0x0
#घोषणा EXYNOS_RNG_STATUS		0x10

#घोषणा EXYNOS_RNG_SEED_CONF		0x14
#घोषणा EXYNOS_RNG_GEN_PRNG	        BIT(1)

#घोषणा EXYNOS_RNG_SEED_BASE		0x140
#घोषणा EXYNOS_RNG_SEED(n)		(EXYNOS_RNG_SEED_BASE + (n * 0x4))
#घोषणा EXYNOS_RNG_OUT_BASE		0x160
#घोषणा EXYNOS_RNG_OUT(n)		(EXYNOS_RNG_OUT_BASE + (n * 0x4))

/* EXYNOS_RNG_CONTROL bit fields */
#घोषणा EXYNOS_RNG_CONTROL_START	0x18
/* EXYNOS_RNG_STATUS bit fields */
#घोषणा EXYNOS_RNG_STATUS_SEED_SETTING_DONE	BIT(1)
#घोषणा EXYNOS_RNG_STATUS_RNG_DONE		BIT(5)

/* Five seed and output रेजिस्टरs, each 4 bytes */
#घोषणा EXYNOS_RNG_SEED_REGS		5
#घोषणा EXYNOS_RNG_SEED_SIZE		(EXYNOS_RNG_SEED_REGS * 4)

क्रमागत exynos_prng_type अणु
	EXYNOS_PRNG_UNKNOWN = 0,
	EXYNOS_PRNG_EXYNOS4,
	EXYNOS_PRNG_EXYNOS5,
पूर्ण;

/*
 * Driver re-seeds itself with generated अक्रमom numbers to hinder
 * backtracking of the original seed.
 *
 * Time क्रम next re-seed in ms.
 */
#घोषणा EXYNOS_RNG_RESEED_TIME		1000
#घोषणा EXYNOS_RNG_RESEED_BYTES		65536

/*
 * In polling mode, करो not रुको infinitely क्रम the engine to finish the work.
 */
#घोषणा EXYNOS_RNG_WAIT_RETRIES		100

/* Context क्रम crypto */
काष्ठा exynos_rng_ctx अणु
	काष्ठा exynos_rng_dev		*rng;
पूर्ण;

/* Device associated memory */
काष्ठा exynos_rng_dev अणु
	काष्ठा device			*dev;
	क्रमागत exynos_prng_type		type;
	व्योम __iomem			*mem;
	काष्ठा clk			*clk;
	काष्ठा mutex 			lock;
	/* Generated numbers stored क्रम seeding during resume */
	u8				seed_save[EXYNOS_RNG_SEED_SIZE];
	अचिन्हित पूर्णांक			seed_save_len;
	/* Time of last seeding in jअगरfies */
	अचिन्हित दीर्घ			last_seeding;
	/* Bytes generated since last seeding */
	अचिन्हित दीर्घ			bytes_seeding;
पूर्ण;

अटल काष्ठा exynos_rng_dev *exynos_rng_dev;

अटल u32 exynos_rng_पढ़ोl(काष्ठा exynos_rng_dev *rng, u32 offset)
अणु
	वापस पढ़ोl_relaxed(rng->mem + offset);
पूर्ण

अटल व्योम exynos_rng_ग_लिखोl(काष्ठा exynos_rng_dev *rng, u32 val, u32 offset)
अणु
	ग_लिखोl_relaxed(val, rng->mem + offset);
पूर्ण

अटल पूर्णांक exynos_rng_set_seed(काष्ठा exynos_rng_dev *rng,
			       स्थिर u8 *seed, अचिन्हित पूर्णांक slen)
अणु
	u32 val;
	पूर्णांक i;

	/* Round seed length because loop iterates over full रेजिस्टर size */
	slen = ALIGN_DOWN(slen, 4);

	अगर (slen < EXYNOS_RNG_SEED_SIZE)
		वापस -EINVAL;

	क्रम (i = 0; i < slen ; i += 4) अणु
		अचिन्हित पूर्णांक seed_reg = (i / 4) % EXYNOS_RNG_SEED_REGS;

		val = seed[i] << 24;
		val |= seed[i + 1] << 16;
		val |= seed[i + 2] << 8;
		val |= seed[i + 3] << 0;

		exynos_rng_ग_लिखोl(rng, val, EXYNOS_RNG_SEED(seed_reg));
	पूर्ण

	val = exynos_rng_पढ़ोl(rng, EXYNOS_RNG_STATUS);
	अगर (!(val & EXYNOS_RNG_STATUS_SEED_SETTING_DONE)) अणु
		dev_warn(rng->dev, "Seed setting not finished\n");
		वापस -EIO;
	पूर्ण

	rng->last_seeding = jअगरfies;
	rng->bytes_seeding = 0;

	वापस 0;
पूर्ण

/*
 * Start the engine and poll क्रम finish.  Then पढ़ो from output रेजिस्टरs
 * filling the 'dst' buffer up to 'dlen' bytes or up to size of generated
 * अक्रमom data (EXYNOS_RNG_SEED_SIZE).
 *
 * On success: वापस 0 and store number of पढ़ो bytes under 'read' address.
 * On error: वापस -ERRNO.
 */
अटल पूर्णांक exynos_rng_get_अक्रमom(काष्ठा exynos_rng_dev *rng,
				 u8 *dst, अचिन्हित पूर्णांक dlen,
				 अचिन्हित पूर्णांक *पढ़ो)
अणु
	पूर्णांक retry = EXYNOS_RNG_WAIT_RETRIES;

	अगर (rng->type == EXYNOS_PRNG_EXYNOS4) अणु
		exynos_rng_ग_लिखोl(rng, EXYNOS_RNG_CONTROL_START,
				  EXYNOS_RNG_CONTROL);
	पूर्ण अन्यथा अगर (rng->type == EXYNOS_PRNG_EXYNOS5) अणु
		exynos_rng_ग_लिखोl(rng, EXYNOS_RNG_GEN_PRNG,
				  EXYNOS_RNG_SEED_CONF);
	पूर्ण

	जबतक (!(exynos_rng_पढ़ोl(rng,
			EXYNOS_RNG_STATUS) & EXYNOS_RNG_STATUS_RNG_DONE) && --retry)
		cpu_relax();

	अगर (!retry)
		वापस -ETIMEDOUT;

	/* Clear status bit */
	exynos_rng_ग_लिखोl(rng, EXYNOS_RNG_STATUS_RNG_DONE,
			  EXYNOS_RNG_STATUS);
	*पढ़ो = min_t(माप_प्रकार, dlen, EXYNOS_RNG_SEED_SIZE);
	स_नकल_fromio(dst, rng->mem + EXYNOS_RNG_OUT_BASE, *पढ़ो);
	rng->bytes_seeding += *पढ़ो;

	वापस 0;
पूर्ण

/* Re-seed itself from समय to समय */
अटल व्योम exynos_rng_reseed(काष्ठा exynos_rng_dev *rng)
अणु
	अचिन्हित दीर्घ next_seeding = rng->last_seeding + \
				     msecs_to_jअगरfies(EXYNOS_RNG_RESEED_TIME);
	अचिन्हित दीर्घ now = jअगरfies;
	अचिन्हित पूर्णांक पढ़ो = 0;
	u8 seed[EXYNOS_RNG_SEED_SIZE];

	अगर (समय_beक्रमe(now, next_seeding) &&
	    rng->bytes_seeding < EXYNOS_RNG_RESEED_BYTES)
		वापस;

	अगर (exynos_rng_get_अक्रमom(rng, seed, माप(seed), &पढ़ो))
		वापस;

	exynos_rng_set_seed(rng, seed, पढ़ो);

	/* Let others करो some of their job. */
	mutex_unlock(&rng->lock);
	mutex_lock(&rng->lock);
पूर्ण

अटल पूर्णांक exynos_rng_generate(काष्ठा crypto_rng *tfm,
			       स्थिर u8 *src, अचिन्हित पूर्णांक slen,
			       u8 *dst, अचिन्हित पूर्णांक dlen)
अणु
	काष्ठा exynos_rng_ctx *ctx = crypto_rng_ctx(tfm);
	काष्ठा exynos_rng_dev *rng = ctx->rng;
	अचिन्हित पूर्णांक पढ़ो = 0;
	पूर्णांक ret;

	ret = clk_prepare_enable(rng->clk);
	अगर (ret)
		वापस ret;

	mutex_lock(&rng->lock);
	करो अणु
		ret = exynos_rng_get_अक्रमom(rng, dst, dlen, &पढ़ो);
		अगर (ret)
			अवरोध;

		dlen -= पढ़ो;
		dst += पढ़ो;

		exynos_rng_reseed(rng);
	पूर्ण जबतक (dlen > 0);
	mutex_unlock(&rng->lock);

	clk_disable_unprepare(rng->clk);

	वापस ret;
पूर्ण

अटल पूर्णांक exynos_rng_seed(काष्ठा crypto_rng *tfm, स्थिर u8 *seed,
			   अचिन्हित पूर्णांक slen)
अणु
	काष्ठा exynos_rng_ctx *ctx = crypto_rng_ctx(tfm);
	काष्ठा exynos_rng_dev *rng = ctx->rng;
	पूर्णांक ret;

	ret = clk_prepare_enable(rng->clk);
	अगर (ret)
		वापस ret;

	mutex_lock(&rng->lock);
	ret = exynos_rng_set_seed(ctx->rng, seed, slen);
	mutex_unlock(&rng->lock);

	clk_disable_unprepare(rng->clk);

	वापस ret;
पूर्ण

अटल पूर्णांक exynos_rng_kcapi_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा exynos_rng_ctx *ctx = crypto_tfm_ctx(tfm);

	ctx->rng = exynos_rng_dev;

	वापस 0;
पूर्ण

अटल काष्ठा rng_alg exynos_rng_alg = अणु
	.generate		= exynos_rng_generate,
	.seed			= exynos_rng_seed,
	.seedsize		= EXYNOS_RNG_SEED_SIZE,
	.base			= अणु
		.cra_name		= "stdrng",
		.cra_driver_name	= "exynos_rng",
		.cra_priority		= 300,
		.cra_ctxsize		= माप(काष्ठा exynos_rng_ctx),
		.cra_module		= THIS_MODULE,
		.cra_init		= exynos_rng_kcapi_init,
	पूर्ण
पूर्ण;

अटल पूर्णांक exynos_rng_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा exynos_rng_dev *rng;
	पूर्णांक ret;

	अगर (exynos_rng_dev)
		वापस -EEXIST;

	rng = devm_kzalloc(&pdev->dev, माप(*rng), GFP_KERNEL);
	अगर (!rng)
		वापस -ENOMEM;

	rng->type = (क्रमागत exynos_prng_type)of_device_get_match_data(&pdev->dev);

	mutex_init(&rng->lock);

	rng->dev = &pdev->dev;
	rng->clk = devm_clk_get(&pdev->dev, "secss");
	अगर (IS_ERR(rng->clk)) अणु
		dev_err(&pdev->dev, "Couldn't get clock.\n");
		वापस PTR_ERR(rng->clk);
	पूर्ण

	rng->mem = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(rng->mem))
		वापस PTR_ERR(rng->mem);

	platक्रमm_set_drvdata(pdev, rng);

	exynos_rng_dev = rng;

	ret = crypto_रेजिस्टर_rng(&exynos_rng_alg);
	अगर (ret) अणु
		dev_err(&pdev->dev,
			"Couldn't register rng crypto alg: %d\n", ret);
		exynos_rng_dev = शून्य;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक exynos_rng_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	crypto_unरेजिस्टर_rng(&exynos_rng_alg);

	exynos_rng_dev = शून्य;

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused exynos_rng_suspend(काष्ठा device *dev)
अणु
	काष्ठा exynos_rng_dev *rng = dev_get_drvdata(dev);
	पूर्णांक ret;

	/* If we were never seeded then after resume it will be the same */
	अगर (!rng->last_seeding)
		वापस 0;

	rng->seed_save_len = 0;
	ret = clk_prepare_enable(rng->clk);
	अगर (ret)
		वापस ret;

	mutex_lock(&rng->lock);

	/* Get new अक्रमom numbers and store them क्रम seeding on resume. */
	exynos_rng_get_अक्रमom(rng, rng->seed_save, माप(rng->seed_save),
			      &(rng->seed_save_len));

	mutex_unlock(&rng->lock);

	dev_dbg(rng->dev, "Stored %u bytes for seeding on system resume\n",
		rng->seed_save_len);

	clk_disable_unprepare(rng->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused exynos_rng_resume(काष्ठा device *dev)
अणु
	काष्ठा exynos_rng_dev *rng = dev_get_drvdata(dev);
	पूर्णांक ret;

	/* Never seeded so nothing to करो */
	अगर (!rng->last_seeding)
		वापस 0;

	ret = clk_prepare_enable(rng->clk);
	अगर (ret)
		वापस ret;

	mutex_lock(&rng->lock);

	ret = exynos_rng_set_seed(rng, rng->seed_save, rng->seed_save_len);

	mutex_unlock(&rng->lock);

	clk_disable_unprepare(rng->clk);

	वापस ret;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(exynos_rng_pm_ops, exynos_rng_suspend,
			 exynos_rng_resume);

अटल स्थिर काष्ठा of_device_id exynos_rng_dt_match[] = अणु
	अणु
		.compatible = "samsung,exynos4-rng",
		.data = (स्थिर व्योम *)EXYNOS_PRNG_EXYNOS4,
	पूर्ण, अणु
		.compatible = "samsung,exynos5250-prng",
		.data = (स्थिर व्योम *)EXYNOS_PRNG_EXYNOS5,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, exynos_rng_dt_match);

अटल काष्ठा platक्रमm_driver exynos_rng_driver = अणु
	.driver		= अणु
		.name	= "exynos-rng",
		.pm	= &exynos_rng_pm_ops,
		.of_match_table = exynos_rng_dt_match,
	पूर्ण,
	.probe		= exynos_rng_probe,
	.हटाओ		= exynos_rng_हटाओ,
पूर्ण;

module_platक्रमm_driver(exynos_rng_driver);

MODULE_DESCRIPTION("Exynos H/W Random Number Generator driver");
MODULE_AUTHOR("Krzysztof Kozlowski <krzk@kernel.org>");
MODULE_LICENSE("GPL v2");
