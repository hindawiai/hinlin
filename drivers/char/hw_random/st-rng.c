<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ST Ranकरोm Number Generator Driver ST's Platक्रमms
 *
 * Author: Pankaj Dev: <pankaj.dev@st.com>
 *         Lee Jones <lee.jones@linaro.org>
 *
 * Copyright (C) 2015 STMicroelectronics (R&D) Limited
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/hw_अक्रमom.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

/* Registers */
#घोषणा ST_RNG_STATUS_REG		0x20
#घोषणा ST_RNG_DATA_REG			0x24

/* Registers fields */
#घोषणा ST_RNG_STATUS_BAD_SEQUENCE	BIT(0)
#घोषणा ST_RNG_STATUS_BAD_ALTERन_अंकCE	BIT(1)
#घोषणा ST_RNG_STATUS_FIFO_FULL		BIT(5)

#घोषणा ST_RNG_SAMPLE_SIZE		2 /* 2 Byte (16bit) samples */
#घोषणा ST_RNG_FIFO_DEPTH		4
#घोषणा ST_RNG_FIFO_SIZE		(ST_RNG_FIFO_DEPTH * ST_RNG_SAMPLE_SIZE)

/*
 * Samples are करोcumented to be available every 0.667us, so in theory
 * the 4 sample deep FIFO should take 2.668us to fill.  However, during
 * thorough testing, it became apparent that filling the FIFO actually
 * takes बंदr to 12us.  We then multiply by 2 in order to account क्रम
 * the lack of udelay()'s reliability, suggested by Russell King.
 */
#घोषणा ST_RNG_FILL_FIFO_TIMEOUT	(12 * 2)

काष्ठा st_rng_data अणु
	व्योम __iomem	*base;
	काष्ठा clk	*clk;
	काष्ठा hwrng	ops;
पूर्ण;

अटल पूर्णांक st_rng_पढ़ो(काष्ठा hwrng *rng, व्योम *data, माप_प्रकार max, bool रुको)
अणु
	काष्ठा st_rng_data *ddata = (काष्ठा st_rng_data *)rng->priv;
	u32 status;
	पूर्णांक i;

	/* Wait until FIFO is full - max 4uS*/
	क्रम (i = 0; i < ST_RNG_FILL_FIFO_TIMEOUT; i++) अणु
		status = पढ़ोl_relaxed(ddata->base + ST_RNG_STATUS_REG);
		अगर (status & ST_RNG_STATUS_FIFO_FULL)
			अवरोध;
		udelay(1);
	पूर्ण

	अगर (i == ST_RNG_FILL_FIFO_TIMEOUT)
		वापस 0;

	क्रम (i = 0; i < ST_RNG_FIFO_SIZE && i < max; i += 2)
		*(u16 *)(data + i) =
			पढ़ोl_relaxed(ddata->base + ST_RNG_DATA_REG);

	वापस i;	/* No of bytes पढ़ो */
पूर्ण

अटल पूर्णांक st_rng_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा st_rng_data *ddata;
	काष्ठा clk *clk;
	व्योम __iomem *base;
	पूर्णांक ret;

	ddata = devm_kzalloc(&pdev->dev, माप(*ddata), GFP_KERNEL);
	अगर (!ddata)
		वापस -ENOMEM;

	base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(clk))
		वापस PTR_ERR(clk);

	ret = clk_prepare_enable(clk);
	अगर (ret)
		वापस ret;

	ddata->ops.priv	= (अचिन्हित दीर्घ)ddata;
	ddata->ops.पढ़ो	= st_rng_पढ़ो;
	ddata->ops.name	= pdev->name;
	ddata->base	= base;
	ddata->clk	= clk;

	dev_set_drvdata(&pdev->dev, ddata);

	ret = devm_hwrng_रेजिस्टर(&pdev->dev, &ddata->ops);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to register HW RNG\n");
		clk_disable_unprepare(clk);
		वापस ret;
	पूर्ण

	dev_info(&pdev->dev, "Successfully registered HW RNG\n");

	वापस 0;
पूर्ण

अटल पूर्णांक st_rng_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा st_rng_data *ddata = dev_get_drvdata(&pdev->dev);

	clk_disable_unprepare(ddata->clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id st_rng_match[] __maybe_unused = अणु
	अणु .compatible = "st,rng" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, st_rng_match);

अटल काष्ठा platक्रमm_driver st_rng_driver = अणु
	.driver = अणु
		.name = "st-hwrandom",
		.of_match_table = of_match_ptr(st_rng_match),
	पूर्ण,
	.probe = st_rng_probe,
	.हटाओ = st_rng_हटाओ
पूर्ण;

module_platक्रमm_driver(st_rng_driver);

MODULE_AUTHOR("Pankaj Dev <pankaj.dev@st.com>");
MODULE_LICENSE("GPL v2");
