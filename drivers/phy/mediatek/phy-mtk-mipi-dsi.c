<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2015 MediaTek Inc.
 */

#समावेश "phy-mtk-mipi-dsi.h"

अंतरभूत काष्ठा mtk_mipi_tx *mtk_mipi_tx_from_clk_hw(काष्ठा clk_hw *hw)
अणु
	वापस container_of(hw, काष्ठा mtk_mipi_tx, pll_hw);
पूर्ण

व्योम mtk_mipi_tx_clear_bits(काष्ठा mtk_mipi_tx *mipi_tx, u32 offset,
			    u32 bits)
अणु
	u32 temp = पढ़ोl(mipi_tx->regs + offset);

	ग_लिखोl(temp & ~bits, mipi_tx->regs + offset);
पूर्ण

व्योम mtk_mipi_tx_set_bits(काष्ठा mtk_mipi_tx *mipi_tx, u32 offset,
			  u32 bits)
अणु
	u32 temp = पढ़ोl(mipi_tx->regs + offset);

	ग_लिखोl(temp | bits, mipi_tx->regs + offset);
पूर्ण

व्योम mtk_mipi_tx_update_bits(काष्ठा mtk_mipi_tx *mipi_tx, u32 offset,
			     u32 mask, u32 data)
अणु
	u32 temp = पढ़ोl(mipi_tx->regs + offset);

	ग_लिखोl((temp & ~mask) | (data & mask), mipi_tx->regs + offset);
पूर्ण

पूर्णांक mtk_mipi_tx_pll_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			     अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा mtk_mipi_tx *mipi_tx = mtk_mipi_tx_from_clk_hw(hw);

	dev_dbg(mipi_tx->dev, "set rate: %lu Hz\n", rate);

	mipi_tx->data_rate = rate;

	वापस 0;
पूर्ण

अचिन्हित दीर्घ mtk_mipi_tx_pll_recalc_rate(काष्ठा clk_hw *hw,
					  अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा mtk_mipi_tx *mipi_tx = mtk_mipi_tx_from_clk_hw(hw);

	वापस mipi_tx->data_rate;
पूर्ण

अटल पूर्णांक mtk_mipi_tx_घातer_on(काष्ठा phy *phy)
अणु
	काष्ठा mtk_mipi_tx *mipi_tx = phy_get_drvdata(phy);
	पूर्णांक ret;

	/* Power up core and enable PLL */
	ret = clk_prepare_enable(mipi_tx->pll);
	अगर (ret < 0)
		वापस ret;

	/* Enable DSI Lane LDO outमाला_दो, disable pad tie low */
	mipi_tx->driver_data->mipi_tx_enable_संकेत(phy);
	वापस 0;
पूर्ण

अटल पूर्णांक mtk_mipi_tx_घातer_off(काष्ठा phy *phy)
अणु
	काष्ठा mtk_mipi_tx *mipi_tx = phy_get_drvdata(phy);

	/* Enable pad tie low, disable DSI Lane LDO outमाला_दो */
	mipi_tx->driver_data->mipi_tx_disable_संकेत(phy);

	/* Disable PLL and घातer करोwn core */
	clk_disable_unprepare(mipi_tx->pll);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा phy_ops mtk_mipi_tx_ops = अणु
	.घातer_on = mtk_mipi_tx_घातer_on,
	.घातer_off = mtk_mipi_tx_घातer_off,
	.owner = THIS_MODULE,
पूर्ण;

अटल व्योम mtk_mipi_tx_get_calibration_datal(काष्ठा mtk_mipi_tx *mipi_tx)
अणु
	काष्ठा nvmem_cell *cell;
	माप_प्रकार len;
	u32 *buf;

	cell = nvmem_cell_get(mipi_tx->dev, "calibration-data");
	अगर (IS_ERR(cell)) अणु
		dev_info(mipi_tx->dev, "can't get nvmem_cell_get, ignore it\n");
		वापस;
	पूर्ण
	buf = (u32 *)nvmem_cell_पढ़ो(cell, &len);
	nvmem_cell_put(cell);

	अगर (IS_ERR(buf)) अणु
		dev_info(mipi_tx->dev, "can't get data, ignore it\n");
		वापस;
	पूर्ण

	अगर (len < 3 * माप(u32)) अणु
		dev_info(mipi_tx->dev, "invalid calibration data\n");
		kमुक्त(buf);
		वापस;
	पूर्ण

	mipi_tx->rt_code[0] = ((buf[0] >> 6 & 0x1f) << 5) |
			       (buf[0] >> 11 & 0x1f);
	mipi_tx->rt_code[1] = ((buf[1] >> 27 & 0x1f) << 5) |
			       (buf[0] >> 1 & 0x1f);
	mipi_tx->rt_code[2] = ((buf[1] >> 17 & 0x1f) << 5) |
			       (buf[1] >> 22 & 0x1f);
	mipi_tx->rt_code[3] = ((buf[1] >> 7 & 0x1f) << 5) |
			       (buf[1] >> 12 & 0x1f);
	mipi_tx->rt_code[4] = ((buf[2] >> 27 & 0x1f) << 5) |
			       (buf[1] >> 2 & 0x1f);
	kमुक्त(buf);
पूर्ण

अटल पूर्णांक mtk_mipi_tx_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा mtk_mipi_tx *mipi_tx;
	काष्ठा resource *mem;
	स्थिर अक्षर *ref_clk_name;
	काष्ठा clk *ref_clk;
	काष्ठा clk_init_data clk_init = अणु
		.num_parents = 1,
		.parent_names = (स्थिर अक्षर * स्थिर *)&ref_clk_name,
		.flags = CLK_SET_RATE_GATE,
	पूर्ण;
	काष्ठा phy *phy;
	काष्ठा phy_provider *phy_provider;
	पूर्णांक ret;

	mipi_tx = devm_kzalloc(dev, माप(*mipi_tx), GFP_KERNEL);
	अगर (!mipi_tx)
		वापस -ENOMEM;

	mipi_tx->driver_data = of_device_get_match_data(dev);

	mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	mipi_tx->regs = devm_ioremap_resource(dev, mem);
	अगर (IS_ERR(mipi_tx->regs)) अणु
		ret = PTR_ERR(mipi_tx->regs);
		dev_err(dev, "Failed to get memory resource: %d\n", ret);
		वापस ret;
	पूर्ण

	ref_clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(ref_clk)) अणु
		ret = PTR_ERR(ref_clk);
		dev_err(dev, "Failed to get reference clock: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = of_property_पढ़ो_u32(dev->of_node, "drive-strength-microamp",
				   &mipi_tx->mipitx_drive);
	/* If can't get the "mipi_tx->mipitx_drive", set it शेष 0x8 */
	अगर (ret < 0)
		mipi_tx->mipitx_drive = 4600;

	/* check the mipitx_drive valid */
	अगर (mipi_tx->mipitx_drive > 6000 || mipi_tx->mipitx_drive < 3000) अणु
		dev_warn(dev, "drive-strength-microamp is invalid %d, not in 3000 ~ 6000\n",
			 mipi_tx->mipitx_drive);
		mipi_tx->mipitx_drive = clamp_val(mipi_tx->mipitx_drive, 3000,
						  6000);
	पूर्ण

	ref_clk_name = __clk_get_name(ref_clk);

	ret = of_property_पढ़ो_string(dev->of_node, "clock-output-names",
				      &clk_init.name);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to read clock-output-names: %d\n", ret);
		वापस ret;
	पूर्ण

	clk_init.ops = mipi_tx->driver_data->mipi_tx_clk_ops;

	mipi_tx->pll_hw.init = &clk_init;
	mipi_tx->pll = devm_clk_रेजिस्टर(dev, &mipi_tx->pll_hw);
	अगर (IS_ERR(mipi_tx->pll)) अणु
		ret = PTR_ERR(mipi_tx->pll);
		dev_err(dev, "Failed to register PLL: %d\n", ret);
		वापस ret;
	पूर्ण

	phy = devm_phy_create(dev, शून्य, &mtk_mipi_tx_ops);
	अगर (IS_ERR(phy)) अणु
		ret = PTR_ERR(phy);
		dev_err(dev, "Failed to create MIPI D-PHY: %d\n", ret);
		वापस ret;
	पूर्ण
	phy_set_drvdata(phy, mipi_tx);

	phy_provider = devm_of_phy_provider_रेजिस्टर(dev, of_phy_simple_xlate);
	अगर (IS_ERR(phy_provider)) अणु
		ret = PTR_ERR(phy_provider);
		वापस ret;
	पूर्ण

	mipi_tx->dev = dev;

	mtk_mipi_tx_get_calibration_datal(mipi_tx);

	वापस of_clk_add_provider(dev->of_node, of_clk_src_simple_get,
				   mipi_tx->pll);
पूर्ण

अटल पूर्णांक mtk_mipi_tx_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	of_clk_del_provider(pdev->dev.of_node);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id mtk_mipi_tx_match[] = अणु
	अणु .compatible = "mediatek,mt2701-mipi-tx",
	  .data = &mt2701_mipitx_data पूर्ण,
	अणु .compatible = "mediatek,mt8173-mipi-tx",
	  .data = &mt8173_mipitx_data पूर्ण,
	अणु .compatible = "mediatek,mt8183-mipi-tx",
	  .data = &mt8183_mipitx_data पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mtk_mipi_tx_match);

अटल काष्ठा platक्रमm_driver mtk_mipi_tx_driver = अणु
	.probe = mtk_mipi_tx_probe,
	.हटाओ = mtk_mipi_tx_हटाओ,
	.driver = अणु
		.name = "mediatek-mipi-tx",
		.of_match_table = mtk_mipi_tx_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(mtk_mipi_tx_driver);

MODULE_DESCRIPTION("MediaTek MIPI TX Driver");
MODULE_LICENSE("GPL v2");
