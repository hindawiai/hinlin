<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2019 HiSilicon Limited. */

#समावेश <linux/acpi.h>
#समावेश <linux/crypto.h>
#समावेश <linux/err.h>
#समावेश <linux/hw_अक्रमom.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/अक्रमom.h>
#समावेश <crypto/पूर्णांकernal/rng.h>

#घोषणा HISI_TRNG_REG		0x00F0
#घोषणा HISI_TRNG_BYTES		4
#घोषणा HISI_TRNG_QUALITY	512
#घोषणा HISI_TRNG_VERSION	0x01B8
#घोषणा HISI_TRNG_VER_V1	GENMASK(31, 0)
#घोषणा SLEEP_US		10
#घोषणा TIMEOUT_US		10000
#घोषणा SW_DRBG_NUM_SHIFT	2
#घोषणा SW_DRBG_KEY_BASE	0x082C
#घोषणा SW_DRBG_SEED(n)         (SW_DRBG_KEY_BASE - ((n) << SW_DRBG_NUM_SHIFT))
#घोषणा SW_DRBG_SEED_REGS_NUM	12
#घोषणा SW_DRBG_SEED_SIZE	48
#घोषणा SW_DRBG_BLOCKS		0x0830
#घोषणा SW_DRBG_INIT		0x0834
#घोषणा SW_DRBG_GEN		0x083c
#घोषणा SW_DRBG_STATUS		0x0840
#घोषणा SW_DRBG_BLOCKS_NUM	4095
#घोषणा SW_DRBG_DATA_BASE	0x0850
#घोषणा SW_DRBG_DATA_NUM	4
#घोषणा SW_DRBG_DATA(n)		(SW_DRBG_DATA_BASE - ((n) << SW_DRBG_NUM_SHIFT))
#घोषणा SW_DRBG_BYTES		16
#घोषणा SW_DRBG_ENABLE_SHIFT	12
#घोषणा SEED_SHIFT_24		24
#घोषणा SEED_SHIFT_16		16
#घोषणा SEED_SHIFT_8		8

काष्ठा hisi_trng_list अणु
	काष्ठा mutex lock;
	काष्ठा list_head list;
	bool is_init;
पूर्ण;

काष्ठा hisi_trng अणु
	व्योम __iomem *base;
	काष्ठा hisi_trng_list *trng_list;
	काष्ठा list_head list;
	काष्ठा hwrng rng;
	u32 ver;
	bool is_used;
	काष्ठा mutex mutex;
पूर्ण;

काष्ठा hisi_trng_ctx अणु
	काष्ठा hisi_trng *trng;
पूर्ण;

अटल atomic_t trng_active_devs;
अटल काष्ठा hisi_trng_list trng_devices;

अटल व्योम hisi_trng_set_seed(काष्ठा hisi_trng *trng, स्थिर u8 *seed)
अणु
	u32 val, seed_reg, i;

	क्रम (i = 0; i < SW_DRBG_SEED_SIZE;
	     i += SW_DRBG_SEED_SIZE / SW_DRBG_SEED_REGS_NUM) अणु
		val = seed[i] << SEED_SHIFT_24;
		val |= seed[i + 1UL] << SEED_SHIFT_16;
		val |= seed[i + 2UL] << SEED_SHIFT_8;
		val |= seed[i + 3UL];

		seed_reg = (i >> SW_DRBG_NUM_SHIFT) % SW_DRBG_SEED_REGS_NUM;
		ग_लिखोl(val, trng->base + SW_DRBG_SEED(seed_reg));
	पूर्ण
पूर्ण

अटल पूर्णांक hisi_trng_seed(काष्ठा crypto_rng *tfm, स्थिर u8 *seed,
			  अचिन्हित पूर्णांक slen)
अणु
	काष्ठा hisi_trng_ctx *ctx = crypto_rng_ctx(tfm);
	काष्ठा hisi_trng *trng = ctx->trng;
	u32 val = 0;
	पूर्णांक ret = 0;

	अगर (slen < SW_DRBG_SEED_SIZE) अणु
		pr_err("slen(%u) is not matched with trng(%d)\n", slen,
			SW_DRBG_SEED_SIZE);
		वापस -EINVAL;
	पूर्ण

	ग_लिखोl(0x0, trng->base + SW_DRBG_BLOCKS);
	hisi_trng_set_seed(trng, seed);

	ग_लिखोl(SW_DRBG_BLOCKS_NUM | (0x1 << SW_DRBG_ENABLE_SHIFT),
	       trng->base + SW_DRBG_BLOCKS);
	ग_लिखोl(0x1, trng->base + SW_DRBG_INIT);

	ret = पढ़ोl_relaxed_poll_समयout(trng->base + SW_DRBG_STATUS,
					val, val & BIT(0), SLEEP_US, TIMEOUT_US);
	अगर (ret)
		pr_err("fail to init trng(%d)\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक hisi_trng_generate(काष्ठा crypto_rng *tfm, स्थिर u8 *src,
			      अचिन्हित पूर्णांक slen, u8 *dstn, अचिन्हित पूर्णांक dlen)
अणु
	काष्ठा hisi_trng_ctx *ctx = crypto_rng_ctx(tfm);
	काष्ठा hisi_trng *trng = ctx->trng;
	u32 data[SW_DRBG_DATA_NUM];
	u32 currsize = 0;
	u32 val = 0;
	पूर्णांक ret;
	u32 i;

	अगर (dlen > SW_DRBG_BLOCKS_NUM * SW_DRBG_BYTES || dlen == 0) अणु
		pr_err("dlen(%d) exceeds limit(%d)!\n", dlen,
			SW_DRBG_BLOCKS_NUM * SW_DRBG_BYTES);
		वापस -EINVAL;
	पूर्ण

	करो अणु
		ret = पढ़ोl_relaxed_poll_समयout(trng->base + SW_DRBG_STATUS,
		     val, val & BIT(1), SLEEP_US, TIMEOUT_US);
		अगर (ret) अणु
			pr_err("fail to generate random number(%d)!\n", ret);
			अवरोध;
		पूर्ण

		क्रम (i = 0; i < SW_DRBG_DATA_NUM; i++)
			data[i] = पढ़ोl(trng->base + SW_DRBG_DATA(i));

		अगर (dlen - currsize >= SW_DRBG_BYTES) अणु
			स_नकल(dstn + currsize, data, SW_DRBG_BYTES);
			currsize += SW_DRBG_BYTES;
		पूर्ण अन्यथा अणु
			स_नकल(dstn + currsize, data, dlen - currsize);
			currsize = dlen;
		पूर्ण

		ग_लिखोl(0x1, trng->base + SW_DRBG_GEN);
	पूर्ण जबतक (currsize < dlen);

	वापस ret;
पूर्ण

अटल पूर्णांक hisi_trng_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा hisi_trng_ctx *ctx = crypto_tfm_ctx(tfm);
	काष्ठा hisi_trng *trng;
	पूर्णांक ret = -EBUSY;

	mutex_lock(&trng_devices.lock);
	list_क्रम_each_entry(trng, &trng_devices.list, list) अणु
		अगर (!trng->is_used) अणु
			trng->is_used = true;
			ctx->trng = trng;
			ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&trng_devices.lock);

	वापस ret;
पूर्ण

अटल व्योम hisi_trng_निकास(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा hisi_trng_ctx *ctx = crypto_tfm_ctx(tfm);

	mutex_lock(&trng_devices.lock);
	ctx->trng->is_used = false;
	mutex_unlock(&trng_devices.lock);
पूर्ण

अटल पूर्णांक hisi_trng_पढ़ो(काष्ठा hwrng *rng, व्योम *buf, माप_प्रकार max, bool रुको)
अणु
	काष्ठा hisi_trng *trng;
	पूर्णांक currsize = 0;
	u32 val = 0;
	u32 ret;

	trng = container_of(rng, काष्ठा hisi_trng, rng);

	करो अणु
		ret = पढ़ोl_poll_समयout(trng->base + HISI_TRNG_REG, val,
					 val, SLEEP_US, TIMEOUT_US);
		अगर (ret)
			वापस currsize;

		अगर (max - currsize >= HISI_TRNG_BYTES) अणु
			स_नकल(buf + currsize, &val, HISI_TRNG_BYTES);
			currsize += HISI_TRNG_BYTES;
			अगर (currsize == max)
				वापस currsize;
			जारी;
		पूर्ण

		/* copy reमुख्यing bytes */
		स_नकल(buf + currsize, &val, max - currsize);
		currsize = max;
	पूर्ण जबतक (currsize < max);

	वापस currsize;
पूर्ण

अटल काष्ठा rng_alg hisi_trng_alg = अणु
	.generate = hisi_trng_generate,
	.seed =	hisi_trng_seed,
	.seedsize = SW_DRBG_SEED_SIZE,
	.base = अणु
		.cra_name = "stdrng",
		.cra_driver_name = "hisi_stdrng",
		.cra_priority = 300,
		.cra_ctxsize = माप(काष्ठा hisi_trng_ctx),
		.cra_module = THIS_MODULE,
		.cra_init = hisi_trng_init,
		.cra_निकास = hisi_trng_निकास,
	पूर्ण,
पूर्ण;

अटल व्योम hisi_trng_add_to_list(काष्ठा hisi_trng *trng)
अणु
	mutex_lock(&trng_devices.lock);
	list_add_tail(&trng->list, &trng_devices.list);
	mutex_unlock(&trng_devices.lock);
पूर्ण

अटल पूर्णांक hisi_trng_del_from_list(काष्ठा hisi_trng *trng)
अणु
	पूर्णांक ret = -EBUSY;

	mutex_lock(&trng_devices.lock);
	अगर (!trng->is_used) अणु
		list_del(&trng->list);
		ret = 0;
	पूर्ण
	mutex_unlock(&trng_devices.lock);

	वापस ret;
पूर्ण

अटल पूर्णांक hisi_trng_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा hisi_trng *trng;
	पूर्णांक ret;

	trng = devm_kzalloc(&pdev->dev, माप(*trng), GFP_KERNEL);
	अगर (!trng)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, trng);

	trng->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(trng->base))
		वापस PTR_ERR(trng->base);

	trng->is_used = false;
	trng->ver = पढ़ोl(trng->base + HISI_TRNG_VERSION);
	अगर (!trng_devices.is_init) अणु
		INIT_LIST_HEAD(&trng_devices.list);
		mutex_init(&trng_devices.lock);
		trng_devices.is_init = true;
	पूर्ण

	hisi_trng_add_to_list(trng);
	अगर (trng->ver != HISI_TRNG_VER_V1 &&
	    atomic_inc_वापस(&trng_active_devs) == 1) अणु
		ret = crypto_रेजिस्टर_rng(&hisi_trng_alg);
		अगर (ret) अणु
			dev_err(&pdev->dev,
				"failed to register crypto(%d)\n", ret);
			atomic_dec_वापस(&trng_active_devs);
			जाओ err_हटाओ_from_list;
		पूर्ण
	पूर्ण

	trng->rng.name = pdev->name;
	trng->rng.पढ़ो = hisi_trng_पढ़ो;
	trng->rng.quality = HISI_TRNG_QUALITY;
	ret = devm_hwrng_रेजिस्टर(&pdev->dev, &trng->rng);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to register hwrng: %d!\n", ret);
		जाओ err_crypto_unरेजिस्टर;
	पूर्ण

	वापस ret;

err_crypto_unरेजिस्टर:
	अगर (trng->ver != HISI_TRNG_VER_V1 &&
	    atomic_dec_वापस(&trng_active_devs) == 0)
		crypto_unरेजिस्टर_rng(&hisi_trng_alg);

err_हटाओ_from_list:
	hisi_trng_del_from_list(trng);
	वापस ret;
पूर्ण

अटल पूर्णांक hisi_trng_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा hisi_trng *trng = platक्रमm_get_drvdata(pdev);

	/* Wait until the task is finished */
	जबतक (hisi_trng_del_from_list(trng))
		;

	अगर (trng->ver != HISI_TRNG_VER_V1 &&
	    atomic_dec_वापस(&trng_active_devs) == 0)
		crypto_unरेजिस्टर_rng(&hisi_trng_alg);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा acpi_device_id hisi_trng_acpi_match[] = अणु
	अणु "HISI02B3", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, hisi_trng_acpi_match);

अटल काष्ठा platक्रमm_driver hisi_trng_driver = अणु
	.probe		= hisi_trng_probe,
	.हटाओ         = hisi_trng_हटाओ,
	.driver		= अणु
		.name	= "hisi-trng-v2",
		.acpi_match_table = ACPI_PTR(hisi_trng_acpi_match),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(hisi_trng_driver);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Weili Qian <qianweili@huawei.com>");
MODULE_AUTHOR("Zaibo Xu <xuzaibo@huawei.com>");
MODULE_DESCRIPTION("HiSilicon true random number generator V2 driver");
