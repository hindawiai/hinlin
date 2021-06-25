<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Freescale MXS On-Chip OTP driver
 *
 * Copyright (C) 2015 Stefan Wahren <stefan.wahren@i2se.com>
 *
 * Based on the driver from Huang Shijie and Christoph G. Baumann
 */
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/nvmem-provider.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/sपंचांगp_device.h>

/* OCOTP रेजिस्टरs and bits */

#घोषणा BM_OCOTP_CTRL_RD_BANK_OPEN	BIT(12)
#घोषणा BM_OCOTP_CTRL_ERROR		BIT(9)
#घोषणा BM_OCOTP_CTRL_BUSY		BIT(8)

#घोषणा OCOTP_TIMEOUT		10000
#घोषणा OCOTP_DATA_OFFSET	0x20

काष्ठा mxs_ocotp अणु
	काष्ठा clk *clk;
	व्योम __iomem *base;
	काष्ठा nvmem_device *nvmem;
पूर्ण;

अटल पूर्णांक mxs_ocotp_रुको(काष्ठा mxs_ocotp *otp)
अणु
	पूर्णांक समयout = OCOTP_TIMEOUT;
	अचिन्हित पूर्णांक status = 0;

	जबतक (समयout--) अणु
		status = पढ़ोl(otp->base);

		अगर (!(status & (BM_OCOTP_CTRL_BUSY | BM_OCOTP_CTRL_ERROR)))
			अवरोध;

		cpu_relax();
	पूर्ण

	अगर (status & BM_OCOTP_CTRL_BUSY)
		वापस -EBUSY;
	अन्यथा अगर (status & BM_OCOTP_CTRL_ERROR)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक mxs_ocotp_पढ़ो(व्योम *context, अचिन्हित पूर्णांक offset,
			  व्योम *val, माप_प्रकार bytes)
अणु
	काष्ठा mxs_ocotp *otp = context;
	u32 *buf = val;
	पूर्णांक ret;

	ret = clk_enable(otp->clk);
	अगर (ret)
		वापस ret;

	ग_लिखोl(BM_OCOTP_CTRL_ERROR, otp->base + STMP_OFFSET_REG_CLR);

	ret = mxs_ocotp_रुको(otp);
	अगर (ret)
		जाओ disable_clk;

	/* खोलो OCOTP banks क्रम पढ़ो */
	ग_लिखोl(BM_OCOTP_CTRL_RD_BANK_OPEN, otp->base + STMP_OFFSET_REG_SET);

	/* approximately रुको 33 hclk cycles */
	udelay(1);

	ret = mxs_ocotp_रुको(otp);
	अगर (ret)
		जाओ बंद_banks;

	जबतक (bytes) अणु
		अगर ((offset < OCOTP_DATA_OFFSET) || (offset % 16)) अणु
			/* fill up non-data रेजिस्टर */
			*buf++ = 0;
		पूर्ण अन्यथा अणु
			*buf++ = पढ़ोl(otp->base + offset);
		पूर्ण

		bytes -= 4;
		offset += 4;
	पूर्ण

बंद_banks:
	/* बंद banks क्रम घातer saving */
	ग_लिखोl(BM_OCOTP_CTRL_RD_BANK_OPEN, otp->base + STMP_OFFSET_REG_CLR);

disable_clk:
	clk_disable(otp->clk);

	वापस ret;
पूर्ण

अटल काष्ठा nvmem_config ocotp_config = अणु
	.name = "mxs-ocotp",
	.stride = 16,
	.word_size = 4,
	.reg_पढ़ो = mxs_ocotp_पढ़ो,
पूर्ण;

काष्ठा mxs_data अणु
	पूर्णांक size;
पूर्ण;

अटल स्थिर काष्ठा mxs_data imx23_data = अणु
	.size = 0x220,
पूर्ण;

अटल स्थिर काष्ठा mxs_data imx28_data = अणु
	.size = 0x2a0,
पूर्ण;

अटल स्थिर काष्ठा of_device_id mxs_ocotp_match[] = अणु
	अणु .compatible = "fsl,imx23-ocotp", .data = &imx23_data पूर्ण,
	अणु .compatible = "fsl,imx28-ocotp", .data = &imx28_data पूर्ण,
	अणु /* sentinel */पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mxs_ocotp_match);

अटल व्योम mxs_ocotp_action(व्योम *data)
अणु
	clk_unprepare(data);
पूर्ण

अटल पूर्णांक mxs_ocotp_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	स्थिर काष्ठा mxs_data *data;
	काष्ठा mxs_ocotp *otp;
	स्थिर काष्ठा of_device_id *match;
	पूर्णांक ret;

	match = of_match_device(dev->driver->of_match_table, dev);
	अगर (!match || !match->data)
		वापस -EINVAL;

	otp = devm_kzalloc(dev, माप(*otp), GFP_KERNEL);
	अगर (!otp)
		वापस -ENOMEM;

	otp->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(otp->base))
		वापस PTR_ERR(otp->base);

	otp->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(otp->clk))
		वापस PTR_ERR(otp->clk);

	ret = clk_prepare(otp->clk);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to prepare clk: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = devm_add_action_or_reset(&pdev->dev, mxs_ocotp_action, otp->clk);
	अगर (ret)
		वापस ret;

	data = match->data;

	ocotp_config.size = data->size;
	ocotp_config.priv = otp;
	ocotp_config.dev = dev;
	otp->nvmem = devm_nvmem_रेजिस्टर(dev, &ocotp_config);
	अगर (IS_ERR(otp->nvmem))
		वापस PTR_ERR(otp->nvmem);

	platक्रमm_set_drvdata(pdev, otp);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver mxs_ocotp_driver = अणु
	.probe = mxs_ocotp_probe,
	.driver = अणु
		.name = "mxs-ocotp",
		.of_match_table = mxs_ocotp_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(mxs_ocotp_driver);
MODULE_AUTHOR("Stefan Wahren <wahrenst@gmx.net");
MODULE_DESCRIPTION("driver for OCOTP in i.MX23/i.MX28");
MODULE_LICENSE("GPL v2");
