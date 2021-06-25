<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (C) 2020 Xiphera Ltd. */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/hw_अक्रमom.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/delay.h>

#घोषणा CONTROL_REG			0x00000000
#घोषणा STATUS_REG			0x00000004
#घोषणा RAND_REG			0x00000000

#घोषणा HOST_TO_TRNG_RESET		0x00000001
#घोषणा HOST_TO_TRNG_RELEASE_RESET	0x00000002
#घोषणा HOST_TO_TRNG_ENABLE		0x80000000
#घोषणा HOST_TO_TRNG_ZEROIZE		0x80000004
#घोषणा HOST_TO_TRNG_ACK_ZEROIZE	0x80000008
#घोषणा HOST_TO_TRNG_READ		0x8000000F

/* trng statuses */
#घोषणा TRNG_ACK_RESET			0x000000AC
#घोषणा TRNG_SUCCESSFUL_STARTUP		0x00000057
#घोषणा TRNG_FAILED_STARTUP		0x000000FA
#घोषणा TRNG_NEW_RAND_AVAILABLE		0x000000ED

काष्ठा xiphera_trng अणु
	व्योम __iomem *mem;
	काष्ठा hwrng rng;
पूर्ण;

अटल पूर्णांक xiphera_trng_पढ़ो(काष्ठा hwrng *rng, व्योम *buf, माप_प्रकार max, bool रुको)
अणु
	काष्ठा xiphera_trng *trng = container_of(rng, काष्ठा xiphera_trng, rng);
	पूर्णांक ret = 0;

	जबतक (max >= माप(u32)) अणु
		/* check क्रम data */
		अगर (पढ़ोl(trng->mem + STATUS_REG) == TRNG_NEW_RAND_AVAILABLE) अणु
			*(u32 *)buf = पढ़ोl(trng->mem + RAND_REG);
			/*
			 * Inक्रमm the trng of the पढ़ो
			 * and re-enable it to produce a new अक्रमom number
			 */
			ग_लिखोl(HOST_TO_TRNG_READ, trng->mem + CONTROL_REG);
			ग_लिखोl(HOST_TO_TRNG_ENABLE, trng->mem + CONTROL_REG);
			ret += माप(u32);
			buf += माप(u32);
			max -= माप(u32);
		पूर्ण अन्यथा अणु
			अवरोध;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक xiphera_trng_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;
	काष्ठा xiphera_trng *trng;
	काष्ठा device *dev = &pdev->dev;

	trng = devm_kzalloc(dev, माप(*trng), GFP_KERNEL);
	अगर (!trng)
		वापस -ENOMEM;

	trng->mem = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(trng->mem))
		वापस PTR_ERR(trng->mem);

	/*
	 * the trng needs to be reset first which might not happen in समय,
	 * hence we incorporate a small delay to ensure proper behaviour
	 */
	ग_लिखोl(HOST_TO_TRNG_RESET, trng->mem + CONTROL_REG);
	usleep_range(100, 200);

	अगर (पढ़ोl(trng->mem + STATUS_REG) != TRNG_ACK_RESET) अणु
		/*
		 * there is a small chance the trng is just not पढ़ोy yet,
		 * so we try one more समय. If the second समय fails, we give up
		 */
		usleep_range(100, 200);
		अगर (पढ़ोl(trng->mem + STATUS_REG) != TRNG_ACK_RESET) अणु
			dev_err(dev, "failed to reset the trng ip\n");
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	/*
	 * once again, to ensure proper behaviour we sleep
	 * क्रम a जबतक after zeroizing the trng
	 */
	ग_लिखोl(HOST_TO_TRNG_RELEASE_RESET, trng->mem + CONTROL_REG);
	ग_लिखोl(HOST_TO_TRNG_ENABLE, trng->mem + CONTROL_REG);
	ग_लिखोl(HOST_TO_TRNG_ZEROIZE, trng->mem + CONTROL_REG);
	msleep(20);

	अगर (पढ़ोl(trng->mem + STATUS_REG) != TRNG_SUCCESSFUL_STARTUP) अणु
		/* diagnose the reason क्रम the failure */
		अगर (पढ़ोl(trng->mem + STATUS_REG) == TRNG_FAILED_STARTUP) अणु
			dev_err(dev, "trng ip startup-tests failed\n");
			वापस -ENODEV;
		पूर्ण
		dev_err(dev, "startup-tests yielded no response\n");
		वापस -ENODEV;
	पूर्ण

	ग_लिखोl(HOST_TO_TRNG_ACK_ZEROIZE, trng->mem + CONTROL_REG);

	trng->rng.name = pdev->name;
	trng->rng.पढ़ो = xiphera_trng_पढ़ो;
	trng->rng.quality = 900;

	ret = devm_hwrng_रेजिस्टर(dev, &trng->rng);
	अगर (ret) अणु
		dev_err(dev, "failed to register rng device: %d\n", ret);
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, trng);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id xiphera_trng_of_match[] = अणु
	अणु .compatible = "xiphera,xip8001b-trng", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, xiphera_trng_of_match);

अटल काष्ठा platक्रमm_driver xiphera_trng_driver = अणु
	.driver = अणु
		.name = "xiphera-trng",
		.of_match_table	= xiphera_trng_of_match,
	पूर्ण,
	.probe = xiphera_trng_probe,
पूर्ण;

module_platक्रमm_driver(xiphera_trng_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Atte Tommiska");
MODULE_DESCRIPTION("Xiphera FPGA-based true random number generator driver");
