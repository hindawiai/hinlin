<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * JZ4780 EFUSE Memory Support driver
 *
 * Copyright (c) 2017 PrasannaKumar Muralidharan <prasannatsmkumar@gmail.com>
 * Copyright (c) 2020 H. Nikolaus Schaller <hns@goldelico.com>
 */

/*
 * Currently supports JZ4780 efuse which has 8K programmable bit.
 * Efuse is separated पूर्णांकo seven segments as below:
 *
 * -----------------------------------------------------------------------
 * | 64 bit | 128 bit | 128 bit | 3520 bit | 8 bit | 2296 bit | 2048 bit |
 * -----------------------------------------------------------------------
 *
 * The rom itself is accessed using a 9 bit address line and an 8 word wide bus
 * which पढ़ोs/ग_लिखोs based on strobes. The strobe is configured in the config
 * रेजिस्टर and is based on number of cycles of the bus घड़ी.
 *
 * Driver supports पढ़ो only as the ग_लिखोs are करोne in the Factory.
 */

#समावेश <linux/bitops.h>
#समावेश <linux/clk.h>
#समावेश <linux/module.h>
#समावेश <linux/nvmem-provider.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/समयr.h>

#घोषणा JZ_EFUCTRL		(0x0)	/* Control Register */
#घोषणा JZ_EFUCFG		(0x4)	/* Configure Register*/
#घोषणा JZ_EFUSTATE		(0x8)	/* Status Register */
#घोषणा JZ_EFUDATA(n)		(0xC + (n) * 4)

/* We पढ़ो 32 byte chunks to aव्योम complनिकासy in the driver. */
#घोषणा JZ_EFU_READ_SIZE 32

#घोषणा EFUCTRL_ADDR_MASK	0x3FF
#घोषणा EFUCTRL_ADDR_SHIFT	21
#घोषणा EFUCTRL_LEN_MASK	0x1F
#घोषणा EFUCTRL_LEN_SHIFT	16
#घोषणा EFUCTRL_PG_EN		BIT(15)
#घोषणा EFUCTRL_WR_EN		BIT(1)
#घोषणा EFUCTRL_RD_EN		BIT(0)

#घोषणा EFUCFG_INT_EN		BIT(31)
#घोषणा EFUCFG_RD_ADJ_MASK	0xF
#घोषणा EFUCFG_RD_ADJ_SHIFT	20
#घोषणा EFUCFG_RD_STR_MASK	0xF
#घोषणा EFUCFG_RD_STR_SHIFT	16
#घोषणा EFUCFG_WR_ADJ_MASK	0xF
#घोषणा EFUCFG_WR_ADJ_SHIFT	12
#घोषणा EFUCFG_WR_STR_MASK	0xFFF
#घोषणा EFUCFG_WR_STR_SHIFT	0

#घोषणा EFUSTATE_WR_DONE	BIT(1)
#घोषणा EFUSTATE_RD_DONE	BIT(0)

काष्ठा jz4780_efuse अणु
	काष्ठा device *dev;
	काष्ठा regmap *map;
	काष्ठा clk *clk;
पूर्ण;

/* मुख्य entry poपूर्णांक */
अटल पूर्णांक jz4780_efuse_पढ़ो(व्योम *context, अचिन्हित पूर्णांक offset,
			     व्योम *val, माप_प्रकार bytes)
अणु
	काष्ठा jz4780_efuse *efuse = context;

	जबतक (bytes > 0) अणु
		माप_प्रकार start = offset & ~(JZ_EFU_READ_SIZE - 1);
		माप_प्रकार chunk = min(bytes, (start + JZ_EFU_READ_SIZE)
				    - offset);
		अक्षर buf[JZ_EFU_READ_SIZE];
		अचिन्हित पूर्णांक पंचांगp;
		u32 ctrl;
		पूर्णांक ret;

		ctrl = (start << EFUCTRL_ADDR_SHIFT)
			| ((JZ_EFU_READ_SIZE - 1) << EFUCTRL_LEN_SHIFT)
			| EFUCTRL_RD_EN;

		regmap_update_bits(efuse->map, JZ_EFUCTRL,
				   (EFUCTRL_ADDR_MASK << EFUCTRL_ADDR_SHIFT) |
				   (EFUCTRL_LEN_MASK << EFUCTRL_LEN_SHIFT) |
				   EFUCTRL_PG_EN | EFUCTRL_WR_EN |
				   EFUCTRL_RD_EN,
				   ctrl);

		ret = regmap_पढ़ो_poll_समयout(efuse->map, JZ_EFUSTATE,
					       पंचांगp, पंचांगp & EFUSTATE_RD_DONE,
					       1 * MSEC_PER_SEC,
					       50 * MSEC_PER_SEC);
		अगर (ret < 0) अणु
			dev_err(efuse->dev, "Time out while reading efuse data");
			वापस ret;
		पूर्ण

		ret = regmap_bulk_पढ़ो(efuse->map, JZ_EFUDATA(0),
				       buf, JZ_EFU_READ_SIZE / माप(u32));
		अगर (ret < 0)
			वापस ret;

		स_नकल(val, &buf[offset - start], chunk);

		val += chunk;
		offset += chunk;
		bytes -= chunk;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा nvmem_config jz4780_efuse_nvmem_config = अणु
	.name = "jz4780-efuse",
	.size = 1024,
	.word_size = 1,
	.stride = 1,
	.owner = THIS_MODULE,
	.reg_पढ़ो = jz4780_efuse_पढ़ो,
पूर्ण;

अटल स्थिर काष्ठा regmap_config jz4780_efuse_regmap_config = अणु
	.reg_bits = 32,
	.val_bits = 32,
	.reg_stride = 4,
	.max_रेजिस्टर = JZ_EFUDATA(7),
पूर्ण;

अटल व्योम clk_disable_unprepare_helper(व्योम *घड़ी)
अणु
	clk_disable_unprepare(घड़ी);
पूर्ण

अटल पूर्णांक jz4780_efuse_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा nvmem_device *nvmem;
	काष्ठा jz4780_efuse *efuse;
	काष्ठा nvmem_config cfg;
	अचिन्हित दीर्घ clk_rate;
	अचिन्हित दीर्घ rd_adj;
	अचिन्हित दीर्घ rd_strobe;
	काष्ठा device *dev = &pdev->dev;
	व्योम __iomem *regs;
	पूर्णांक ret;

	efuse = devm_kzalloc(dev, माप(*efuse), GFP_KERNEL);
	अगर (!efuse)
		वापस -ENOMEM;

	regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(regs))
		वापस PTR_ERR(regs);

	efuse->map = devm_regmap_init_mmio(dev, regs,
					   &jz4780_efuse_regmap_config);
	अगर (IS_ERR(efuse->map))
		वापस PTR_ERR(efuse->map);

	efuse->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(efuse->clk))
		वापस PTR_ERR(efuse->clk);

	ret = clk_prepare_enable(efuse->clk);
	अगर (ret < 0)
		वापस ret;

	ret = devm_add_action_or_reset(&pdev->dev,
				       clk_disable_unprepare_helper,
				       efuse->clk);
	अगर (ret < 0)
		वापस ret;

	clk_rate = clk_get_rate(efuse->clk);

	efuse->dev = dev;

	/*
	 * rd_adj and rd_strobe are 4 bit values
	 * conditions:
	 *   bus clk_period * (rd_adj + 1) > 6.5ns
	 *   bus clk_period * (rd_adj + 5 + rd_strobe) > 35ns
	 *   i.e. rd_adj >= 6.5ns / clk_period
	 *   i.e. rd_strobe >= 35 ns / clk_period - 5 - rd_adj + 1
	 * स्थिरants:
	 *   1 / 6.5ns == 153846154 Hz
	 *   1 / 35ns == 28571429 Hz
	 */

	rd_adj = clk_rate / 153846154;
	rd_strobe = clk_rate / 28571429 - 5 - rd_adj + 1;

	अगर (rd_adj > EFUCFG_RD_ADJ_MASK ||
	    rd_strobe > EFUCFG_RD_STR_MASK) अणु
		dev_err(&pdev->dev, "Cannot set clock configuration\n");
		वापस -EINVAL;
	पूर्ण

	regmap_update_bits(efuse->map, JZ_EFUCFG,
			   (EFUCFG_RD_ADJ_MASK << EFUCFG_RD_ADJ_SHIFT) |
			   (EFUCFG_RD_STR_MASK << EFUCFG_RD_STR_SHIFT),
			   (rd_adj << EFUCFG_RD_ADJ_SHIFT) |
			   (rd_strobe << EFUCFG_RD_STR_SHIFT));

	cfg = jz4780_efuse_nvmem_config;
	cfg.dev = &pdev->dev;
	cfg.priv = efuse;

	nvmem = devm_nvmem_रेजिस्टर(dev, &cfg);

	वापस PTR_ERR_OR_ZERO(nvmem);
पूर्ण

अटल स्थिर काष्ठा of_device_id jz4780_efuse_match[] = अणु
	अणु .compatible = "ingenic,jz4780-efuse" पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, jz4780_efuse_match);

अटल काष्ठा platक्रमm_driver jz4780_efuse_driver = अणु
	.probe  = jz4780_efuse_probe,
	.driver = अणु
		.name = "jz4780-efuse",
		.of_match_table = jz4780_efuse_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(jz4780_efuse_driver);

MODULE_AUTHOR("PrasannaKumar Muralidharan <prasannatsmkumar@gmail.com>");
MODULE_AUTHOR("H. Nikolaus Schaller <hns@goldelico.com>");
MODULE_AUTHOR("Paul Cercueil <paul@crapouillou.net>");
MODULE_DESCRIPTION("Ingenic JZ4780 efuse driver");
MODULE_LICENSE("GPL v2");
