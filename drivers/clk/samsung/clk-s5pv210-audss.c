<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2014 Tomasz Figa <t.figa@samsung.com>
 *
 * Based on Exynos Audio Subप्रणाली Clock Controller driver:
 *
 * Copyright (c) 2013 Samsung Electronics Co., Ltd.
 * Author: Padmavathi Venna <padma.v@samsung.com>
 *
 * Driver क्रम Audio Subप्रणाली Clock Controller of S5PV210-compatible SoCs.
*/

#समावेश <linux/पन.स>
#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/of_address.h>
#समावेश <linux/syscore_ops.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <dt-bindings/घड़ी/s5pv210-audss.h>

अटल DEFINE_SPINLOCK(lock);
अटल व्योम __iomem *reg_base;
अटल काष्ठा clk_hw_onecell_data *clk_data;

#घोषणा ASS_CLK_SRC 0x0
#घोषणा ASS_CLK_DIV 0x4
#घोषणा ASS_CLK_GATE 0x8

#अगर_घोषित CONFIG_PM_SLEEP
अटल अचिन्हित दीर्घ reg_save[][2] = अणु
	अणुASS_CLK_SRC,  0पूर्ण,
	अणुASS_CLK_DIV,  0पूर्ण,
	अणुASS_CLK_GATE, 0पूर्ण,
पूर्ण;

अटल पूर्णांक s5pv210_audss_clk_suspend(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(reg_save); i++)
		reg_save[i][1] = पढ़ोl(reg_base + reg_save[i][0]);

	वापस 0;
पूर्ण

अटल व्योम s5pv210_audss_clk_resume(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(reg_save); i++)
		ग_लिखोl(reg_save[i][1], reg_base + reg_save[i][0]);
पूर्ण

अटल काष्ठा syscore_ops s5pv210_audss_clk_syscore_ops = अणु
	.suspend	= s5pv210_audss_clk_suspend,
	.resume		= s5pv210_audss_clk_resume,
पूर्ण;
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

/* रेजिस्टर s5pv210_audss घड़ीs */
अटल पूर्णांक s5pv210_audss_clk_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक i, ret = 0;
	काष्ठा resource *res;
	स्थिर अक्षर *mout_audss_p[2];
	स्थिर अक्षर *mout_i2s_p[3];
	स्थिर अक्षर *hclk_p;
	काष्ठा clk_hw **clk_table;
	काष्ठा clk *hclk, *pll_ref, *pll_in, *cdclk, *sclk_audio;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	reg_base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(reg_base))
		वापस PTR_ERR(reg_base);

	clk_data = devm_kzalloc(&pdev->dev,
				काष्ठा_size(clk_data, hws, AUDSS_MAX_CLKS),
				GFP_KERNEL);

	अगर (!clk_data)
		वापस -ENOMEM;

	clk_data->num = AUDSS_MAX_CLKS;
	clk_table = clk_data->hws;

	hclk = devm_clk_get(&pdev->dev, "hclk");
	अगर (IS_ERR(hclk)) अणु
		dev_err(&pdev->dev, "failed to get hclk clock\n");
		वापस PTR_ERR(hclk);
	पूर्ण

	pll_in = devm_clk_get(&pdev->dev, "fout_epll");
	अगर (IS_ERR(pll_in)) अणु
		dev_err(&pdev->dev, "failed to get fout_epll clock\n");
		वापस PTR_ERR(pll_in);
	पूर्ण

	sclk_audio = devm_clk_get(&pdev->dev, "sclk_audio0");
	अगर (IS_ERR(sclk_audio)) अणु
		dev_err(&pdev->dev, "failed to get sclk_audio0 clock\n");
		वापस PTR_ERR(sclk_audio);
	पूर्ण

	/* iiscdclk0 is an optional बाह्यal I2S codec घड़ी */
	cdclk = devm_clk_get(&pdev->dev, "iiscdclk0");
	pll_ref = devm_clk_get(&pdev->dev, "xxti");

	अगर (!IS_ERR(pll_ref))
		mout_audss_p[0] = __clk_get_name(pll_ref);
	अन्यथा
		mout_audss_p[0] = "xxti";
	mout_audss_p[1] = __clk_get_name(pll_in);
	clk_table[CLK_MOUT_AUDSS] = clk_hw_रेजिस्टर_mux(शून्य, "mout_audss",
				mout_audss_p, ARRAY_SIZE(mout_audss_p),
				CLK_SET_RATE_NO_REPARENT,
				reg_base + ASS_CLK_SRC, 0, 1, 0, &lock);

	mout_i2s_p[0] = "mout_audss";
	अगर (!IS_ERR(cdclk))
		mout_i2s_p[1] = __clk_get_name(cdclk);
	अन्यथा
		mout_i2s_p[1] = "iiscdclk0";
	mout_i2s_p[2] = __clk_get_name(sclk_audio);
	clk_table[CLK_MOUT_I2S_A] = clk_hw_रेजिस्टर_mux(शून्य, "mout_i2s_audss",
				mout_i2s_p, ARRAY_SIZE(mout_i2s_p),
				CLK_SET_RATE_NO_REPARENT,
				reg_base + ASS_CLK_SRC, 2, 2, 0, &lock);

	clk_table[CLK_DOUT_AUD_BUS] = clk_hw_रेजिस्टर_भागider(शून्य,
				"dout_aud_bus", "mout_audss", 0,
				reg_base + ASS_CLK_DIV, 0, 4, 0, &lock);
	clk_table[CLK_DOUT_I2S_A] = clk_hw_रेजिस्टर_भागider(शून्य,
				"dout_i2s_audss", "mout_i2s_audss", 0,
				reg_base + ASS_CLK_DIV, 4, 4, 0, &lock);

	clk_table[CLK_I2S] = clk_hw_रेजिस्टर_gate(शून्य, "i2s_audss",
				"dout_i2s_audss", CLK_SET_RATE_PARENT,
				reg_base + ASS_CLK_GATE, 6, 0, &lock);

	hclk_p = __clk_get_name(hclk);

	clk_table[CLK_HCLK_I2S] = clk_hw_रेजिस्टर_gate(शून्य, "hclk_i2s_audss",
				hclk_p, CLK_IGNORE_UNUSED,
				reg_base + ASS_CLK_GATE, 5, 0, &lock);
	clk_table[CLK_HCLK_UART] = clk_hw_रेजिस्टर_gate(शून्य, "hclk_uart_audss",
				hclk_p, CLK_IGNORE_UNUSED,
				reg_base + ASS_CLK_GATE, 4, 0, &lock);
	clk_table[CLK_HCLK_HWA] = clk_hw_रेजिस्टर_gate(शून्य, "hclk_hwa_audss",
				hclk_p, CLK_IGNORE_UNUSED,
				reg_base + ASS_CLK_GATE, 3, 0, &lock);
	clk_table[CLK_HCLK_DMA] = clk_hw_रेजिस्टर_gate(शून्य, "hclk_dma_audss",
				hclk_p, CLK_IGNORE_UNUSED,
				reg_base + ASS_CLK_GATE, 2, 0, &lock);
	clk_table[CLK_HCLK_BUF] = clk_hw_रेजिस्टर_gate(शून्य, "hclk_buf_audss",
				hclk_p, CLK_IGNORE_UNUSED,
				reg_base + ASS_CLK_GATE, 1, 0, &lock);
	clk_table[CLK_HCLK_RP] = clk_hw_रेजिस्टर_gate(शून्य, "hclk_rp_audss",
				hclk_p, CLK_IGNORE_UNUSED,
				reg_base + ASS_CLK_GATE, 0, 0, &lock);

	क्रम (i = 0; i < clk_data->num; i++) अणु
		अगर (IS_ERR(clk_table[i])) अणु
			dev_err(&pdev->dev, "failed to register clock %d\n", i);
			ret = PTR_ERR(clk_table[i]);
			जाओ unरेजिस्टर;
		पूर्ण
	पूर्ण

	ret = of_clk_add_hw_provider(pdev->dev.of_node, of_clk_hw_onecell_get,
				     clk_data);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to add clock provider\n");
		जाओ unरेजिस्टर;
	पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
	रेजिस्टर_syscore_ops(&s5pv210_audss_clk_syscore_ops);
#पूर्ण_अगर

	वापस 0;

unरेजिस्टर:
	क्रम (i = 0; i < clk_data->num; i++) अणु
		अगर (!IS_ERR(clk_table[i]))
			clk_hw_unरेजिस्टर(clk_table[i]);
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id s5pv210_audss_clk_of_match[] = अणु
	अणु .compatible = "samsung,s5pv210-audss-clock", पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver s5pv210_audss_clk_driver = अणु
	.driver	= अणु
		.name = "s5pv210-audss-clk",
		.suppress_bind_attrs = true,
		.of_match_table = s5pv210_audss_clk_of_match,
	पूर्ण,
	.probe = s5pv210_audss_clk_probe,
पूर्ण;

अटल पूर्णांक __init s5pv210_audss_clk_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&s5pv210_audss_clk_driver);
पूर्ण
core_initcall(s5pv210_audss_clk_init);
