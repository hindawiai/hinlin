<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2010 Broadcom
 * Copyright (C) 2012 Stephen Warren
 * Copyright (C) 2016 Neil Armstrong <narmstrong@baylibre.com>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/stringअगरy.h>
#समावेश <linux/regmap.h>
#समावेश <linux/mfd/syscon.h>

#समावेश <dt-bindings/घड़ी/oxsemi,ox810se.h>
#समावेश <dt-bindings/घड़ी/oxsemi,ox820.h>

/* Standard regmap gate घड़ीs */
काष्ठा clk_oxnas_gate अणु
	काष्ठा clk_hw hw;
	अचिन्हित पूर्णांक bit;
	काष्ठा regmap *regmap;
पूर्ण;

काष्ठा oxnas_stdclk_data अणु
	काष्ठा clk_hw_onecell_data *onecell_data;
	काष्ठा clk_oxnas_gate **gates;
	अचिन्हित पूर्णांक ngates;
	काष्ठा clk_oxnas_pll **plls;
	अचिन्हित पूर्णांक nplls;
पूर्ण;

/* Regmap offsets */
#घोषणा CLK_STAT_REGOFFSET	0x24
#घोषणा CLK_SET_REGOFFSET	0x2c
#घोषणा CLK_CLR_REGOFFSET	0x30

अटल अंतरभूत काष्ठा clk_oxnas_gate *to_clk_oxnas_gate(काष्ठा clk_hw *hw)
अणु
	वापस container_of(hw, काष्ठा clk_oxnas_gate, hw);
पूर्ण

अटल पूर्णांक oxnas_clk_gate_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_oxnas_gate *std = to_clk_oxnas_gate(hw);
	पूर्णांक ret;
	अचिन्हित पूर्णांक val;

	ret = regmap_पढ़ो(std->regmap, CLK_STAT_REGOFFSET, &val);
	अगर (ret < 0)
		वापस ret;

	वापस val & BIT(std->bit);
पूर्ण

अटल पूर्णांक oxnas_clk_gate_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_oxnas_gate *std = to_clk_oxnas_gate(hw);

	regmap_ग_लिखो(std->regmap, CLK_SET_REGOFFSET, BIT(std->bit));

	वापस 0;
पूर्ण

अटल व्योम oxnas_clk_gate_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_oxnas_gate *std = to_clk_oxnas_gate(hw);

	regmap_ग_लिखो(std->regmap, CLK_CLR_REGOFFSET, BIT(std->bit));
पूर्ण

अटल स्थिर काष्ठा clk_ops oxnas_clk_gate_ops = अणु
	.enable = oxnas_clk_gate_enable,
	.disable = oxnas_clk_gate_disable,
	.is_enabled = oxnas_clk_gate_is_enabled,
पूर्ण;

अटल स्थिर अक्षर *स्थिर osc_parents[] = अणु
	"oscillator",
पूर्ण;

अटल स्थिर अक्षर *स्थिर eth_parents[] = अणु
	"gmacclk",
पूर्ण;

#घोषणा OXNAS_GATE(_name, _bit, _parents)				\
काष्ठा clk_oxnas_gate _name = अणु						\
	.bit = (_bit),							\
	.hw.init = &(काष्ठा clk_init_data) अणु				\
		.name = #_name,						\
		.ops = &oxnas_clk_gate_ops,				\
		.parent_names = _parents,				\
		.num_parents = ARRAY_SIZE(_parents),			\
		.flags = (CLK_SET_RATE_PARENT | CLK_IGNORE_UNUSED),	\
	पूर्ण,								\
पूर्ण

अटल OXNAS_GATE(ox810se_leon, 0, osc_parents);
अटल OXNAS_GATE(ox810se_dma_sgdma, 1, osc_parents);
अटल OXNAS_GATE(ox810se_cipher, 2, osc_parents);
अटल OXNAS_GATE(ox810se_sata, 4, osc_parents);
अटल OXNAS_GATE(ox810se_audio, 5, osc_parents);
अटल OXNAS_GATE(ox810se_usbmph, 6, osc_parents);
अटल OXNAS_GATE(ox810se_etha, 7, eth_parents);
अटल OXNAS_GATE(ox810se_pciea, 8, osc_parents);
अटल OXNAS_GATE(ox810se_nand, 9, osc_parents);

अटल काष्ठा clk_oxnas_gate *ox810se_gates[] = अणु
	&ox810se_leon,
	&ox810se_dma_sgdma,
	&ox810se_cipher,
	&ox810se_sata,
	&ox810se_audio,
	&ox810se_usbmph,
	&ox810se_etha,
	&ox810se_pciea,
	&ox810se_nand,
पूर्ण;

अटल OXNAS_GATE(ox820_leon, 0, osc_parents);
अटल OXNAS_GATE(ox820_dma_sgdma, 1, osc_parents);
अटल OXNAS_GATE(ox820_cipher, 2, osc_parents);
अटल OXNAS_GATE(ox820_sd, 3, osc_parents);
अटल OXNAS_GATE(ox820_sata, 4, osc_parents);
अटल OXNAS_GATE(ox820_audio, 5, osc_parents);
अटल OXNAS_GATE(ox820_usbmph, 6, osc_parents);
अटल OXNAS_GATE(ox820_etha, 7, eth_parents);
अटल OXNAS_GATE(ox820_pciea, 8, osc_parents);
अटल OXNAS_GATE(ox820_nand, 9, osc_parents);
अटल OXNAS_GATE(ox820_ethb, 10, eth_parents);
अटल OXNAS_GATE(ox820_pcieb, 11, osc_parents);
अटल OXNAS_GATE(ox820_ref600, 12, osc_parents);
अटल OXNAS_GATE(ox820_usbdev, 13, osc_parents);

अटल काष्ठा clk_oxnas_gate *ox820_gates[] = अणु
	&ox820_leon,
	&ox820_dma_sgdma,
	&ox820_cipher,
	&ox820_sd,
	&ox820_sata,
	&ox820_audio,
	&ox820_usbmph,
	&ox820_etha,
	&ox820_pciea,
	&ox820_nand,
	&ox820_etha,
	&ox820_pciea,
	&ox820_ref600,
	&ox820_usbdev,
पूर्ण;

अटल काष्ठा clk_hw_onecell_data ox810se_hw_onecell_data = अणु
	.hws = अणु
		[CLK_810_LEON]	= &ox810se_leon.hw,
		[CLK_810_DMA_SGDMA]	= &ox810se_dma_sgdma.hw,
		[CLK_810_CIPHER]	= &ox810se_cipher.hw,
		[CLK_810_SATA]	= &ox810se_sata.hw,
		[CLK_810_AUDIO]	= &ox810se_audपन.सw,
		[CLK_810_USBMPH]	= &ox810se_usbmph.hw,
		[CLK_810_ETHA]	= &ox810se_etha.hw,
		[CLK_810_PCIEA]	= &ox810se_pciea.hw,
		[CLK_810_न_अंकD]	= &ox810se_nand.hw,
	पूर्ण,
	.num = ARRAY_SIZE(ox810se_gates),
पूर्ण;

अटल काष्ठा clk_hw_onecell_data ox820_hw_onecell_data = अणु
	.hws = अणु
		[CLK_820_LEON]	= &ox820_leon.hw,
		[CLK_820_DMA_SGDMA]	= &ox820_dma_sgdma.hw,
		[CLK_820_CIPHER]	= &ox820_cipher.hw,
		[CLK_820_SD]	= &ox820_sd.hw,
		[CLK_820_SATA]	= &ox820_sata.hw,
		[CLK_820_AUDIO]	= &ox820_audपन.सw,
		[CLK_820_USBMPH]	= &ox820_usbmph.hw,
		[CLK_820_ETHA]	= &ox820_etha.hw,
		[CLK_820_PCIEA]	= &ox820_pciea.hw,
		[CLK_820_न_अंकD]	= &ox820_nand.hw,
		[CLK_820_ETHB]	= &ox820_ethb.hw,
		[CLK_820_PCIEB]	= &ox820_pcieb.hw,
		[CLK_820_REF600]	= &ox820_ref600.hw,
		[CLK_820_USBDEV]	= &ox820_usbdev.hw,
	पूर्ण,
	.num = ARRAY_SIZE(ox820_gates),
पूर्ण;

अटल काष्ठा oxnas_stdclk_data ox810se_stdclk_data = अणु
	.onecell_data = &ox810se_hw_onecell_data,
	.gates = ox810se_gates,
	.ngates = ARRAY_SIZE(ox810se_gates),
पूर्ण;

अटल काष्ठा oxnas_stdclk_data ox820_stdclk_data = अणु
	.onecell_data = &ox820_hw_onecell_data,
	.gates = ox820_gates,
	.ngates = ARRAY_SIZE(ox820_gates),
पूर्ण;

अटल स्थिर काष्ठा of_device_id oxnas_stdclk_dt_ids[] = अणु
	अणु .compatible = "oxsemi,ox810se-stdclk", &ox810se_stdclk_data पूर्ण,
	अणु .compatible = "oxsemi,ox820-stdclk", &ox820_stdclk_data पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल पूर्णांक oxnas_stdclk_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	स्थिर काष्ठा oxnas_stdclk_data *data;
	स्थिर काष्ठा of_device_id *id;
	काष्ठा regmap *regmap;
	पूर्णांक ret;
	पूर्णांक i;

	id = of_match_device(oxnas_stdclk_dt_ids, &pdev->dev);
	अगर (!id)
		वापस -ENODEV;
	data = id->data;

	regmap = syscon_node_to_regmap(of_get_parent(np));
	अगर (IS_ERR(regmap)) अणु
		dev_err(&pdev->dev, "failed to have parent regmap\n");
		वापस PTR_ERR(regmap);
	पूर्ण

	क्रम (i = 0 ; i < data->ngates ; ++i)
		data->gates[i]->regmap = regmap;

	क्रम (i = 0; i < data->onecell_data->num; i++) अणु
		अगर (!data->onecell_data->hws[i])
			जारी;

		ret = devm_clk_hw_रेजिस्टर(&pdev->dev,
					   data->onecell_data->hws[i]);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस of_clk_add_hw_provider(np, of_clk_hw_onecell_get,
				      data->onecell_data);
पूर्ण

अटल काष्ठा platक्रमm_driver oxnas_stdclk_driver = अणु
	.probe = oxnas_stdclk_probe,
	.driver	= अणु
		.name = "oxnas-stdclk",
		.suppress_bind_attrs = true,
		.of_match_table = oxnas_stdclk_dt_ids,
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver(oxnas_stdclk_driver);
