<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2013 Samsung Electronics Co., Ltd.
 * Author: Padmavathi Venna <padma.v@samsung.com>
 *
 * Common Clock Framework support क्रम Audio Subप्रणाली Clock Controller.
*/

#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>

#समावेश <dt-bindings/घड़ी/exynos-audss-clk.h>

अटल DEFINE_SPINLOCK(lock);
अटल व्योम __iomem *reg_base;
अटल काष्ठा clk_hw_onecell_data *clk_data;
/*
 * On Exynos5420 this will be a घड़ी which has to be enabled beक्रमe any
 * access to audss रेजिस्टरs. Typically a child of EPLL.
 *
 * On other platक्रमms this will be -ENODEV.
 */
अटल काष्ठा clk *epll;

#घोषणा ASS_CLK_SRC 0x0
#घोषणा ASS_CLK_DIV 0x4
#घोषणा ASS_CLK_GATE 0x8

अटल अचिन्हित दीर्घ reg_save[][2] = अणु
	अणु ASS_CLK_SRC,  0 पूर्ण,
	अणु ASS_CLK_DIV,  0 पूर्ण,
	अणु ASS_CLK_GATE, 0 पूर्ण,
पूर्ण;

अटल पूर्णांक __maybe_unused exynos_audss_clk_suspend(काष्ठा device *dev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(reg_save); i++)
		reg_save[i][1] = पढ़ोl(reg_base + reg_save[i][0]);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused exynos_audss_clk_resume(काष्ठा device *dev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(reg_save); i++)
		ग_लिखोl(reg_save[i][1], reg_base + reg_save[i][0]);

	वापस 0;
पूर्ण

काष्ठा exynos_audss_clk_drvdata अणु
	अचिन्हित पूर्णांक has_adma_clk:1;
	अचिन्हित पूर्णांक has_mst_clk:1;
	अचिन्हित पूर्णांक enable_epll:1;
	अचिन्हित पूर्णांक num_clks;
पूर्ण;

अटल स्थिर काष्ठा exynos_audss_clk_drvdata exynos4210_drvdata = अणु
	.num_clks	= EXYNOS_AUDSS_MAX_CLKS - 1,
	.enable_epll	= 1,
पूर्ण;

अटल स्थिर काष्ठा exynos_audss_clk_drvdata exynos5410_drvdata = अणु
	.num_clks	= EXYNOS_AUDSS_MAX_CLKS - 1,
	.has_mst_clk	= 1,
पूर्ण;

अटल स्थिर काष्ठा exynos_audss_clk_drvdata exynos5420_drvdata = अणु
	.num_clks	= EXYNOS_AUDSS_MAX_CLKS,
	.has_adma_clk	= 1,
	.enable_epll	= 1,
पूर्ण;

अटल स्थिर काष्ठा of_device_id exynos_audss_clk_of_match[] = अणु
	अणु
		.compatible	= "samsung,exynos4210-audss-clock",
		.data		= &exynos4210_drvdata,
	पूर्ण, अणु
		.compatible	= "samsung,exynos5250-audss-clock",
		.data		= &exynos4210_drvdata,
	पूर्ण, अणु
		.compatible	= "samsung,exynos5410-audss-clock",
		.data		= &exynos5410_drvdata,
	पूर्ण, अणु
		.compatible	= "samsung,exynos5420-audss-clock",
		.data		= &exynos5420_drvdata,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, exynos_audss_clk_of_match);

अटल व्योम exynos_audss_clk_tearकरोwn(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = EXYNOS_MOUT_AUDSS; i < EXYNOS_DOUT_SRP; i++) अणु
		अगर (!IS_ERR(clk_data->hws[i]))
			clk_hw_unरेजिस्टर_mux(clk_data->hws[i]);
	पूर्ण

	क्रम (; i < EXYNOS_SRP_CLK; i++) अणु
		अगर (!IS_ERR(clk_data->hws[i]))
			clk_hw_unरेजिस्टर_भागider(clk_data->hws[i]);
	पूर्ण

	क्रम (; i < clk_data->num; i++) अणु
		अगर (!IS_ERR(clk_data->hws[i]))
			clk_hw_unरेजिस्टर_gate(clk_data->hws[i]);
	पूर्ण
पूर्ण

/* रेजिस्टर exynos_audss घड़ीs */
अटल पूर्णांक exynos_audss_clk_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर अक्षर *mout_audss_p[] = अणु"fin_pll", "fout_epll"पूर्ण;
	स्थिर अक्षर *mout_i2s_p[] = अणु"mout_audss", "cdclk0", "sclk_audio0"पूर्ण;
	स्थिर अक्षर *sclk_pcm_p = "sclk_pcm0";
	काष्ठा clk *pll_ref, *pll_in, *cdclk, *sclk_audio, *sclk_pcm_in;
	स्थिर काष्ठा exynos_audss_clk_drvdata *variant;
	काष्ठा clk_hw **clk_table;
	काष्ठा resource *res;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक i, ret = 0;

	variant = of_device_get_match_data(&pdev->dev);
	अगर (!variant)
		वापस -EINVAL;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	reg_base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(reg_base))
		वापस PTR_ERR(reg_base);

	epll = ERR_PTR(-ENODEV);

	clk_data = devm_kzalloc(dev,
				काष्ठा_size(clk_data, hws,
					    EXYNOS_AUDSS_MAX_CLKS),
				GFP_KERNEL);
	अगर (!clk_data)
		वापस -ENOMEM;

	clk_data->num = variant->num_clks;
	clk_table = clk_data->hws;

	pll_ref = devm_clk_get(dev, "pll_ref");
	pll_in = devm_clk_get(dev, "pll_in");
	अगर (!IS_ERR(pll_ref))
		mout_audss_p[0] = __clk_get_name(pll_ref);
	अगर (!IS_ERR(pll_in)) अणु
		mout_audss_p[1] = __clk_get_name(pll_in);

		अगर (variant->enable_epll) अणु
			epll = pll_in;

			ret = clk_prepare_enable(epll);
			अगर (ret) अणु
				dev_err(dev,
					"failed to prepare the epll clock\n");
				वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * Enable runसमय PM here to allow the घड़ी core using runसमय PM
	 * क्रम the रेजिस्टरed घड़ीs. Additionally, we increase the runसमय
	 * PM usage count beक्रमe रेजिस्टरing the घड़ीs, to prevent the
	 * घड़ी core from runसमय suspending the device.
	 */
	pm_runसमय_get_noresume(dev);
	pm_runसमय_set_active(dev);
	pm_runसमय_enable(dev);

	clk_table[EXYNOS_MOUT_AUDSS] = clk_hw_रेजिस्टर_mux(dev, "mout_audss",
				mout_audss_p, ARRAY_SIZE(mout_audss_p),
				CLK_SET_RATE_NO_REPARENT | CLK_SET_RATE_PARENT,
				reg_base + ASS_CLK_SRC, 0, 1, 0, &lock);

	cdclk = devm_clk_get(dev, "cdclk");
	sclk_audio = devm_clk_get(dev, "sclk_audio");
	अगर (!IS_ERR(cdclk))
		mout_i2s_p[1] = __clk_get_name(cdclk);
	अगर (!IS_ERR(sclk_audio))
		mout_i2s_p[2] = __clk_get_name(sclk_audio);
	clk_table[EXYNOS_MOUT_I2S] = clk_hw_रेजिस्टर_mux(dev, "mout_i2s",
				mout_i2s_p, ARRAY_SIZE(mout_i2s_p),
				CLK_SET_RATE_NO_REPARENT,
				reg_base + ASS_CLK_SRC, 2, 2, 0, &lock);

	clk_table[EXYNOS_DOUT_SRP] = clk_hw_रेजिस्टर_भागider(dev, "dout_srp",
				"mout_audss", CLK_SET_RATE_PARENT,
				reg_base + ASS_CLK_DIV, 0, 4, 0, &lock);

	clk_table[EXYNOS_DOUT_AUD_BUS] = clk_hw_रेजिस्टर_भागider(dev,
				"dout_aud_bus", "dout_srp", CLK_SET_RATE_PARENT,
				reg_base + ASS_CLK_DIV, 4, 4, 0, &lock);

	clk_table[EXYNOS_DOUT_I2S] = clk_hw_रेजिस्टर_भागider(dev, "dout_i2s",
				"mout_i2s", 0, reg_base + ASS_CLK_DIV, 8, 4, 0,
				&lock);

	clk_table[EXYNOS_SRP_CLK] = clk_hw_रेजिस्टर_gate(dev, "srp_clk",
				"dout_srp", CLK_SET_RATE_PARENT,
				reg_base + ASS_CLK_GATE, 0, 0, &lock);

	clk_table[EXYNOS_I2S_BUS] = clk_hw_रेजिस्टर_gate(dev, "i2s_bus",
				"dout_aud_bus", CLK_SET_RATE_PARENT,
				reg_base + ASS_CLK_GATE, 2, 0, &lock);

	clk_table[EXYNOS_SCLK_I2S] = clk_hw_रेजिस्टर_gate(dev, "sclk_i2s",
				"dout_i2s", CLK_SET_RATE_PARENT,
				reg_base + ASS_CLK_GATE, 3, 0, &lock);

	clk_table[EXYNOS_PCM_BUS] = clk_hw_रेजिस्टर_gate(dev, "pcm_bus",
				 "sclk_pcm", CLK_SET_RATE_PARENT,
				reg_base + ASS_CLK_GATE, 4, 0, &lock);

	sclk_pcm_in = devm_clk_get(dev, "sclk_pcm_in");
	अगर (!IS_ERR(sclk_pcm_in))
		sclk_pcm_p = __clk_get_name(sclk_pcm_in);
	clk_table[EXYNOS_SCLK_PCM] = clk_hw_रेजिस्टर_gate(dev, "sclk_pcm",
				sclk_pcm_p, CLK_SET_RATE_PARENT,
				reg_base + ASS_CLK_GATE, 5, 0, &lock);

	अगर (variant->has_adma_clk) अणु
		clk_table[EXYNOS_ADMA] = clk_hw_रेजिस्टर_gate(dev, "adma",
				"dout_srp", CLK_SET_RATE_PARENT,
				reg_base + ASS_CLK_GATE, 9, 0, &lock);
	पूर्ण

	क्रम (i = 0; i < clk_data->num; i++) अणु
		अगर (IS_ERR(clk_table[i])) अणु
			dev_err(dev, "failed to register clock %d\n", i);
			ret = PTR_ERR(clk_table[i]);
			जाओ unरेजिस्टर;
		पूर्ण
	पूर्ण

	ret = of_clk_add_hw_provider(dev->of_node, of_clk_hw_onecell_get,
				     clk_data);
	अगर (ret) अणु
		dev_err(dev, "failed to add clock provider\n");
		जाओ unरेजिस्टर;
	पूर्ण

	pm_runसमय_put_sync(dev);

	वापस 0;

unरेजिस्टर:
	exynos_audss_clk_tearकरोwn();
	pm_runसमय_put_sync(dev);
	pm_runसमय_disable(dev);

	अगर (!IS_ERR(epll))
		clk_disable_unprepare(epll);

	वापस ret;
पूर्ण

अटल पूर्णांक exynos_audss_clk_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	of_clk_del_provider(pdev->dev.of_node);

	exynos_audss_clk_tearकरोwn();
	pm_runसमय_disable(&pdev->dev);

	अगर (!IS_ERR(epll))
		clk_disable_unprepare(epll);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops exynos_audss_clk_pm_ops = अणु
	SET_RUNTIME_PM_OPS(exynos_audss_clk_suspend, exynos_audss_clk_resume,
			   शून्य)
	SET_LATE_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				     pm_runसमय_क्रमce_resume)
पूर्ण;

अटल काष्ठा platक्रमm_driver exynos_audss_clk_driver = अणु
	.driver	= अणु
		.name = "exynos-audss-clk",
		.of_match_table = exynos_audss_clk_of_match,
		.pm = &exynos_audss_clk_pm_ops,
	पूर्ण,
	.probe = exynos_audss_clk_probe,
	.हटाओ = exynos_audss_clk_हटाओ,
पूर्ण;

module_platक्रमm_driver(exynos_audss_clk_driver);

MODULE_AUTHOR("Padmavathi Venna <padma.v@samsung.com>");
MODULE_DESCRIPTION("Exynos Audio Subsystem Clock Controller");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:exynos-audss-clk");
