<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Amlogic Meson6, Meson8 and Meson8b eFuse Driver
 *
 * Copyright (c) 2017 Martin Blumenstingl <martin.blumenstingl@googlemail.com>
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/bitops.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/module.h>
#समावेश <linux/nvmem-provider.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/sizes.h>
#समावेश <linux/slab.h>

#घोषणा MESON_MX_EFUSE_CNTL1					0x04
#घोषणा MESON_MX_EFUSE_CNTL1_PD_ENABLE				BIT(27)
#घोषणा MESON_MX_EFUSE_CNTL1_AUTO_RD_BUSY			BIT(26)
#घोषणा MESON_MX_EFUSE_CNTL1_AUTO_RD_START			BIT(25)
#घोषणा MESON_MX_EFUSE_CNTL1_AUTO_RD_ENABLE			BIT(24)
#घोषणा MESON_MX_EFUSE_CNTL1_BYTE_WR_DATA			GENMASK(23, 16)
#घोषणा MESON_MX_EFUSE_CNTL1_AUTO_WR_BUSY			BIT(14)
#घोषणा MESON_MX_EFUSE_CNTL1_AUTO_WR_START			BIT(13)
#घोषणा MESON_MX_EFUSE_CNTL1_AUTO_WR_ENABLE			BIT(12)
#घोषणा MESON_MX_EFUSE_CNTL1_BYTE_ADDR_SET			BIT(11)
#घोषणा MESON_MX_EFUSE_CNTL1_BYTE_ADDR_MASK			GENMASK(10, 0)

#घोषणा MESON_MX_EFUSE_CNTL2					0x08

#घोषणा MESON_MX_EFUSE_CNTL4					0x10
#घोषणा MESON_MX_EFUSE_CNTL4_ENCRYPT_ENABLE			BIT(10)

काष्ठा meson_mx_efuse_platक्रमm_data अणु
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक word_size;
पूर्ण;

काष्ठा meson_mx_efuse अणु
	व्योम __iomem *base;
	काष्ठा clk *core_clk;
	काष्ठा nvmem_device *nvmem;
	काष्ठा nvmem_config config;
पूर्ण;

अटल व्योम meson_mx_efuse_mask_bits(काष्ठा meson_mx_efuse *efuse, u32 reg,
				     u32 mask, u32 set)
अणु
	u32 data;

	data = पढ़ोl(efuse->base + reg);
	data &= ~mask;
	data |= (set & mask);

	ग_लिखोl(data, efuse->base + reg);
पूर्ण

अटल पूर्णांक meson_mx_efuse_hw_enable(काष्ठा meson_mx_efuse *efuse)
अणु
	पूर्णांक err;

	err = clk_prepare_enable(efuse->core_clk);
	अगर (err)
		वापस err;

	/* घातer up the efuse */
	meson_mx_efuse_mask_bits(efuse, MESON_MX_EFUSE_CNTL1,
				 MESON_MX_EFUSE_CNTL1_PD_ENABLE, 0);

	meson_mx_efuse_mask_bits(efuse, MESON_MX_EFUSE_CNTL4,
				 MESON_MX_EFUSE_CNTL4_ENCRYPT_ENABLE, 0);

	वापस 0;
पूर्ण

अटल व्योम meson_mx_efuse_hw_disable(काष्ठा meson_mx_efuse *efuse)
अणु
	meson_mx_efuse_mask_bits(efuse, MESON_MX_EFUSE_CNTL1,
				 MESON_MX_EFUSE_CNTL1_PD_ENABLE,
				 MESON_MX_EFUSE_CNTL1_PD_ENABLE);

	clk_disable_unprepare(efuse->core_clk);
पूर्ण

अटल पूर्णांक meson_mx_efuse_पढ़ो_addr(काष्ठा meson_mx_efuse *efuse,
				    अचिन्हित पूर्णांक addr, u32 *value)
अणु
	पूर्णांक err;
	u32 regval;

	/* ग_लिखो the address to पढ़ो */
	regval = FIELD_PREP(MESON_MX_EFUSE_CNTL1_BYTE_ADDR_MASK, addr);
	meson_mx_efuse_mask_bits(efuse, MESON_MX_EFUSE_CNTL1,
				 MESON_MX_EFUSE_CNTL1_BYTE_ADDR_MASK, regval);

	/* inक्रमm the hardware that we changed the address */
	meson_mx_efuse_mask_bits(efuse, MESON_MX_EFUSE_CNTL1,
				 MESON_MX_EFUSE_CNTL1_BYTE_ADDR_SET,
				 MESON_MX_EFUSE_CNTL1_BYTE_ADDR_SET);
	meson_mx_efuse_mask_bits(efuse, MESON_MX_EFUSE_CNTL1,
				 MESON_MX_EFUSE_CNTL1_BYTE_ADDR_SET, 0);

	/* start the पढ़ो process */
	meson_mx_efuse_mask_bits(efuse, MESON_MX_EFUSE_CNTL1,
				 MESON_MX_EFUSE_CNTL1_AUTO_RD_START,
				 MESON_MX_EFUSE_CNTL1_AUTO_RD_START);
	meson_mx_efuse_mask_bits(efuse, MESON_MX_EFUSE_CNTL1,
				 MESON_MX_EFUSE_CNTL1_AUTO_RD_START, 0);

	/*
	 * perक्रमm a dummy पढ़ो to ensure that the HW has the RD_BUSY bit set
	 * when polling क्रम the status below.
	 */
	पढ़ोl(efuse->base + MESON_MX_EFUSE_CNTL1);

	err = पढ़ोl_poll_समयout_atomic(efuse->base + MESON_MX_EFUSE_CNTL1,
			regval,
			(!(regval & MESON_MX_EFUSE_CNTL1_AUTO_RD_BUSY)),
			1, 1000);
	अगर (err) अणु
		dev_err(efuse->config.dev,
			"Timeout while reading efuse address %u\n", addr);
		वापस err;
	पूर्ण

	*value = पढ़ोl(efuse->base + MESON_MX_EFUSE_CNTL2);

	वापस 0;
पूर्ण

अटल पूर्णांक meson_mx_efuse_पढ़ो(व्योम *context, अचिन्हित पूर्णांक offset,
			       व्योम *buf, माप_प्रकार bytes)
अणु
	काष्ठा meson_mx_efuse *efuse = context;
	u32 पंचांगp;
	पूर्णांक err, i, addr;

	err = meson_mx_efuse_hw_enable(efuse);
	अगर (err)
		वापस err;

	meson_mx_efuse_mask_bits(efuse, MESON_MX_EFUSE_CNTL1,
				 MESON_MX_EFUSE_CNTL1_AUTO_RD_ENABLE,
				 MESON_MX_EFUSE_CNTL1_AUTO_RD_ENABLE);

	क्रम (i = 0; i < bytes; i += efuse->config.word_size) अणु
		addr = (offset + i) / efuse->config.word_size;

		err = meson_mx_efuse_पढ़ो_addr(efuse, addr, &पंचांगp);
		अगर (err)
			अवरोध;

		स_नकल(buf + i, &पंचांगp,
		       min_t(माप_प्रकार, bytes - i, efuse->config.word_size));
	पूर्ण

	meson_mx_efuse_mask_bits(efuse, MESON_MX_EFUSE_CNTL1,
				 MESON_MX_EFUSE_CNTL1_AUTO_RD_ENABLE, 0);

	meson_mx_efuse_hw_disable(efuse);

	वापस err;
पूर्ण

अटल स्थिर काष्ठा meson_mx_efuse_platक्रमm_data meson6_efuse_data = अणु
	.name = "meson6-efuse",
	.word_size = 1,
पूर्ण;

अटल स्थिर काष्ठा meson_mx_efuse_platक्रमm_data meson8_efuse_data = अणु
	.name = "meson8-efuse",
	.word_size = 4,
पूर्ण;

अटल स्थिर काष्ठा meson_mx_efuse_platक्रमm_data meson8b_efuse_data = अणु
	.name = "meson8b-efuse",
	.word_size = 4,
पूर्ण;

अटल स्थिर काष्ठा of_device_id meson_mx_efuse_match[] = अणु
	अणु .compatible = "amlogic,meson6-efuse", .data = &meson6_efuse_data पूर्ण,
	अणु .compatible = "amlogic,meson8-efuse", .data = &meson8_efuse_data पूर्ण,
	अणु .compatible = "amlogic,meson8b-efuse", .data = &meson8b_efuse_data पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, meson_mx_efuse_match);

अटल पूर्णांक meson_mx_efuse_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा meson_mx_efuse_platक्रमm_data *drvdata;
	काष्ठा meson_mx_efuse *efuse;
	काष्ठा resource *res;

	drvdata = of_device_get_match_data(&pdev->dev);
	अगर (!drvdata)
		वापस -EINVAL;

	efuse = devm_kzalloc(&pdev->dev, माप(*efuse), GFP_KERNEL);
	अगर (!efuse)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	efuse->base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(efuse->base))
		वापस PTR_ERR(efuse->base);

	efuse->config.name = devm_kstrdup(&pdev->dev, drvdata->name,
					  GFP_KERNEL);
	efuse->config.owner = THIS_MODULE;
	efuse->config.dev = &pdev->dev;
	efuse->config.priv = efuse;
	efuse->config.stride = drvdata->word_size;
	efuse->config.word_size = drvdata->word_size;
	efuse->config.size = SZ_512;
	efuse->config.पढ़ो_only = true;
	efuse->config.reg_पढ़ो = meson_mx_efuse_पढ़ो;

	efuse->core_clk = devm_clk_get(&pdev->dev, "core");
	अगर (IS_ERR(efuse->core_clk)) अणु
		dev_err(&pdev->dev, "Failed to get core clock\n");
		वापस PTR_ERR(efuse->core_clk);
	पूर्ण

	efuse->nvmem = devm_nvmem_रेजिस्टर(&pdev->dev, &efuse->config);

	वापस PTR_ERR_OR_ZERO(efuse->nvmem);
पूर्ण

अटल काष्ठा platक्रमm_driver meson_mx_efuse_driver = अणु
	.probe = meson_mx_efuse_probe,
	.driver = अणु
		.name = "meson-mx-efuse",
		.of_match_table = meson_mx_efuse_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(meson_mx_efuse_driver);

MODULE_AUTHOR("Martin Blumenstingl <martin.blumenstingl@googlemail.com>");
MODULE_DESCRIPTION("Amlogic Meson MX eFuse NVMEM driver");
MODULE_LICENSE("GPL v2");
