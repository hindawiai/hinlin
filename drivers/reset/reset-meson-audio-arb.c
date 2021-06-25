<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR MIT)
// Copyright (c) 2018 BayLibre, SAS.
// Author: Jerome Brunet <jbrunet@baylibre.com>

#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/reset-controller.h>
#समावेश <linux/spinlock.h>

#समावेश <dt-bindings/reset/amlogic,meson-axg-audio-arb.h>

काष्ठा meson_audio_arb_data अणु
	काष्ठा reset_controller_dev rstc;
	व्योम __iomem *regs;
	काष्ठा clk *clk;
	स्थिर अचिन्हित पूर्णांक *reset_bits;
	spinlock_t lock;
पूर्ण;

काष्ठा meson_audio_arb_match_data अणु
	स्थिर अचिन्हित पूर्णांक *reset_bits;
	अचिन्हित पूर्णांक reset_num;
पूर्ण;

#घोषणा ARB_GENERAL_BIT	31

अटल स्थिर अचिन्हित पूर्णांक axg_audio_arb_reset_bits[] = अणु
	[AXG_ARB_TODDR_A]	= 0,
	[AXG_ARB_TODDR_B]	= 1,
	[AXG_ARB_TODDR_C]	= 2,
	[AXG_ARB_FRDDR_A]	= 4,
	[AXG_ARB_FRDDR_B]	= 5,
	[AXG_ARB_FRDDR_C]	= 6,
पूर्ण;

अटल स्थिर काष्ठा meson_audio_arb_match_data axg_audio_arb_match = अणु
	.reset_bits = axg_audio_arb_reset_bits,
	.reset_num = ARRAY_SIZE(axg_audio_arb_reset_bits),
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक sm1_audio_arb_reset_bits[] = अणु
	[AXG_ARB_TODDR_A]	= 0,
	[AXG_ARB_TODDR_B]	= 1,
	[AXG_ARB_TODDR_C]	= 2,
	[AXG_ARB_FRDDR_A]	= 4,
	[AXG_ARB_FRDDR_B]	= 5,
	[AXG_ARB_FRDDR_C]	= 6,
	[AXG_ARB_TODDR_D]	= 3,
	[AXG_ARB_FRDDR_D]	= 7,
पूर्ण;

अटल स्थिर काष्ठा meson_audio_arb_match_data sm1_audio_arb_match = अणु
	.reset_bits = sm1_audio_arb_reset_bits,
	.reset_num = ARRAY_SIZE(sm1_audio_arb_reset_bits),
पूर्ण;

अटल पूर्णांक meson_audio_arb_update(काष्ठा reset_controller_dev *rcdev,
				  अचिन्हित दीर्घ id, bool निश्चित)
अणु
	u32 val;
	काष्ठा meson_audio_arb_data *arb =
		container_of(rcdev, काष्ठा meson_audio_arb_data, rstc);

	spin_lock(&arb->lock);
	val = पढ़ोl(arb->regs);

	अगर (निश्चित)
		val &= ~BIT(arb->reset_bits[id]);
	अन्यथा
		val |= BIT(arb->reset_bits[id]);

	ग_लिखोl(val, arb->regs);
	spin_unlock(&arb->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक meson_audio_arb_status(काष्ठा reset_controller_dev *rcdev,
				  अचिन्हित दीर्घ id)
अणु
	u32 val;
	काष्ठा meson_audio_arb_data *arb =
		container_of(rcdev, काष्ठा meson_audio_arb_data, rstc);

	val = पढ़ोl(arb->regs);

	वापस !(val & BIT(arb->reset_bits[id]));
पूर्ण

अटल पूर्णांक meson_audio_arb_निश्चित(काष्ठा reset_controller_dev *rcdev,
				  अचिन्हित दीर्घ id)
अणु
	वापस meson_audio_arb_update(rcdev, id, true);
पूर्ण

अटल पूर्णांक meson_audio_arb_deनिश्चित(काष्ठा reset_controller_dev *rcdev,
				    अचिन्हित दीर्घ id)
अणु
	वापस meson_audio_arb_update(rcdev, id, false);
पूर्ण

अटल स्थिर काष्ठा reset_control_ops meson_audio_arb_rstc_ops = अणु
	.निश्चित = meson_audio_arb_निश्चित,
	.deनिश्चित = meson_audio_arb_deनिश्चित,
	.status = meson_audio_arb_status,
पूर्ण;

अटल स्थिर काष्ठा of_device_id meson_audio_arb_of_match[] = अणु
	अणु
		.compatible = "amlogic,meson-axg-audio-arb",
		.data = &axg_audio_arb_match,
	पूर्ण, अणु
		.compatible = "amlogic,meson-sm1-audio-arb",
		.data = &sm1_audio_arb_match,
	पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, meson_audio_arb_of_match);

अटल पूर्णांक meson_audio_arb_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा meson_audio_arb_data *arb = platक्रमm_get_drvdata(pdev);

	/* Disable all access */
	spin_lock(&arb->lock);
	ग_लिखोl(0, arb->regs);
	spin_unlock(&arb->lock);

	clk_disable_unprepare(arb->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक meson_audio_arb_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	स्थिर काष्ठा meson_audio_arb_match_data *data;
	काष्ठा meson_audio_arb_data *arb;
	काष्ठा resource *res;
	पूर्णांक ret;

	data = of_device_get_match_data(dev);
	अगर (!data)
		वापस -EINVAL;

	arb = devm_kzalloc(dev, माप(*arb), GFP_KERNEL);
	अगर (!arb)
		वापस -ENOMEM;
	platक्रमm_set_drvdata(pdev, arb);

	arb->clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(arb->clk)) अणु
		अगर (PTR_ERR(arb->clk) != -EPROBE_DEFER)
			dev_err(dev, "failed to get clock\n");
		वापस PTR_ERR(arb->clk);
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	arb->regs = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(arb->regs))
		वापस PTR_ERR(arb->regs);

	spin_lock_init(&arb->lock);
	arb->reset_bits = data->reset_bits;
	arb->rstc.nr_resets = data->reset_num;
	arb->rstc.ops = &meson_audio_arb_rstc_ops;
	arb->rstc.of_node = dev->of_node;
	arb->rstc.owner = THIS_MODULE;

	/*
	 * Enable general :
	 * In the initial state, all memory पूर्णांकerfaces are disabled
	 * and the general bit is on
	 */
	ret = clk_prepare_enable(arb->clk);
	अगर (ret) अणु
		dev_err(dev, "failed to enable arb clock\n");
		वापस ret;
	पूर्ण
	ग_लिखोl(BIT(ARB_GENERAL_BIT), arb->regs);

	/* Register reset controller */
	ret = devm_reset_controller_रेजिस्टर(dev, &arb->rstc);
	अगर (ret) अणु
		dev_err(dev, "failed to register arb reset controller\n");
		meson_audio_arb_हटाओ(pdev);
	पूर्ण

	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver meson_audio_arb_pdrv = अणु
	.probe = meson_audio_arb_probe,
	.हटाओ = meson_audio_arb_हटाओ,
	.driver = अणु
		.name = "meson-audio-arb-reset",
		.of_match_table = meson_audio_arb_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(meson_audio_arb_pdrv);

MODULE_DESCRIPTION("Amlogic A113 Audio Memory Arbiter");
MODULE_AUTHOR("Jerome Brunet <jbrunet@baylibre.com>");
MODULE_LICENSE("GPL v2");
