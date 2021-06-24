<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * This driver provides regmap to access to analog part of audio codec
 * found on Allwinner A23, A31s, A33, H3 and A64 Socs
 *
 * Copyright 2016 Chen-Yu Tsai <wens@csie.org>
 * Copyright (C) 2018 Vasily Khoruzhick <anarsoul@gmail.com>
 */

#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>

#समावेश "sun8i-adda-pr-regmap.h"

/* Analog control रेजिस्टर access bits */
#घोषणा ADDA_PR			0x0		/* PRCM base + 0x1c0 */
#घोषणा ADDA_PR_RESET			BIT(28)
#घोषणा ADDA_PR_WRITE			BIT(24)
#घोषणा ADDA_PR_ADDR_SHIFT		16
#घोषणा ADDA_PR_ADDR_MASK		GENMASK(4, 0)
#घोषणा ADDA_PR_DATA_IN_SHIFT		8
#घोषणा ADDA_PR_DATA_IN_MASK		GENMASK(7, 0)
#घोषणा ADDA_PR_DATA_OUT_SHIFT		0
#घोषणा ADDA_PR_DATA_OUT_MASK		GENMASK(7, 0)

/* regmap access bits */
अटल पूर्णांक adda_reg_पढ़ो(व्योम *context, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक *val)
अणु
	व्योम __iomem *base = (व्योम __iomem *)context;
	u32 पंचांगp;

	/* De-निश्चित reset */
	ग_लिखोl(पढ़ोl(base) | ADDA_PR_RESET, base);

	/* Clear ग_लिखो bit */
	ग_लिखोl(पढ़ोl(base) & ~ADDA_PR_WRITE, base);

	/* Set रेजिस्टर address */
	पंचांगp = पढ़ोl(base);
	पंचांगp &= ~(ADDA_PR_ADDR_MASK << ADDA_PR_ADDR_SHIFT);
	पंचांगp |= (reg & ADDA_PR_ADDR_MASK) << ADDA_PR_ADDR_SHIFT;
	ग_लिखोl(पंचांगp, base);

	/* Read back value */
	*val = पढ़ोl(base) & ADDA_PR_DATA_OUT_MASK;

	वापस 0;
पूर्ण

अटल पूर्णांक adda_reg_ग_लिखो(व्योम *context, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक val)
अणु
	व्योम __iomem *base = (व्योम __iomem *)context;
	u32 पंचांगp;

	/* De-निश्चित reset */
	ग_लिखोl(पढ़ोl(base) | ADDA_PR_RESET, base);

	/* Set रेजिस्टर address */
	पंचांगp = पढ़ोl(base);
	पंचांगp &= ~(ADDA_PR_ADDR_MASK << ADDA_PR_ADDR_SHIFT);
	पंचांगp |= (reg & ADDA_PR_ADDR_MASK) << ADDA_PR_ADDR_SHIFT;
	ग_लिखोl(पंचांगp, base);

	/* Set data to ग_लिखो */
	पंचांगp = पढ़ोl(base);
	पंचांगp &= ~(ADDA_PR_DATA_IN_MASK << ADDA_PR_DATA_IN_SHIFT);
	पंचांगp |= (val & ADDA_PR_DATA_IN_MASK) << ADDA_PR_DATA_IN_SHIFT;
	ग_लिखोl(पंचांगp, base);

	/* Set ग_लिखो bit to संकेत a ग_लिखो */
	ग_लिखोl(पढ़ोl(base) | ADDA_PR_WRITE, base);

	/* Clear ग_लिखो bit */
	ग_लिखोl(पढ़ोl(base) & ~ADDA_PR_WRITE, base);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा regmap_config adda_pr_regmap_cfg = अणु
	.name		= "adda-pr",
	.reg_bits	= 5,
	.reg_stride	= 1,
	.val_bits	= 8,
	.reg_पढ़ो	= adda_reg_पढ़ो,
	.reg_ग_लिखो	= adda_reg_ग_लिखो,
	.fast_io	= true,
	.max_रेजिस्टर	= 31,
पूर्ण;

काष्ठा regmap *sun8i_adda_pr_regmap_init(काष्ठा device *dev,
					 व्योम __iomem *base)
अणु
	वापस devm_regmap_init(dev, शून्य, base, &adda_pr_regmap_cfg);
पूर्ण
EXPORT_SYMBOL_GPL(sun8i_adda_pr_regmap_init);

MODULE_DESCRIPTION("Allwinner analog audio codec regmap driver");
MODULE_AUTHOR("Vasily Khoruzhick <anarsoul@gmail.com>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:sunxi-adda-pr");
