<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * JZ47xx SoCs TCU Operating System Timer driver
 *
 * Copyright (C) 2016 Maarten ter Huurne <maarten@treewalker.org>
 * Copyright (C) 2020 Paul Cercueil <paul@crapouillou.net>
 */

#समावेश <linux/clk.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/mfd/ingenic-tcu.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm.h>
#समावेश <linux/regmap.h>
#समावेश <linux/sched_घड़ी.h>

#घोषणा TCU_OST_TCSR_MASK	0xffc0
#घोषणा TCU_OST_TCSR_CNT_MD	BIT(15)

#घोषणा TCU_OST_CHANNEL		15

/*
 * The TCU_REG_OST_CNTअणुL,Rपूर्ण from <linux/mfd/ingenic-tcu.h> are only क्रम the
 * regmap; these are क्रम use with the __iomem poपूर्णांकer.
 */
#घोषणा OST_REG_CNTL		0x4
#घोषणा OST_REG_CNTH		0x8

काष्ठा ingenic_ost_soc_info अणु
	bool is64bit;
पूर्ण;

काष्ठा ingenic_ost अणु
	व्योम __iomem *regs;
	काष्ठा clk *clk;

	काष्ठा घड़ीsource cs;
पूर्ण;

अटल काष्ठा ingenic_ost *ingenic_ost;

अटल u64 notrace ingenic_ost_पढ़ो_cntl(व्योम)
अणु
	/* Read using __iomem poपूर्णांकer instead of regmap to aव्योम locking */
	वापस पढ़ोl(ingenic_ost->regs + OST_REG_CNTL);
पूर्ण

अटल u64 notrace ingenic_ost_पढ़ो_cnth(व्योम)
अणु
	/* Read using __iomem poपूर्णांकer instead of regmap to aव्योम locking */
	वापस पढ़ोl(ingenic_ost->regs + OST_REG_CNTH);
पूर्ण

अटल u64 notrace ingenic_ost_घड़ीsource_पढ़ोl(काष्ठा घड़ीsource *cs)
अणु
	वापस ingenic_ost_पढ़ो_cntl();
पूर्ण

अटल u64 notrace ingenic_ost_घड़ीsource_पढ़ोh(काष्ठा घड़ीsource *cs)
अणु
	वापस ingenic_ost_पढ़ो_cnth();
पूर्ण

अटल पूर्णांक __init ingenic_ost_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा ingenic_ost_soc_info *soc_info;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा ingenic_ost *ost;
	काष्ठा घड़ीsource *cs;
	काष्ठा regmap *map;
	अचिन्हित दीर्घ rate;
	पूर्णांक err;

	soc_info = device_get_match_data(dev);
	अगर (!soc_info)
		वापस -EINVAL;

	ost = devm_kzalloc(dev, माप(*ost), GFP_KERNEL);
	अगर (!ost)
		वापस -ENOMEM;

	ingenic_ost = ost;

	ost->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(ost->regs))
		वापस PTR_ERR(ost->regs);

	map = device_node_to_regmap(dev->parent->of_node);
	अगर (IS_ERR(map)) अणु
		dev_err(dev, "regmap not found");
		वापस PTR_ERR(map);
	पूर्ण

	ost->clk = devm_clk_get(dev, "ost");
	अगर (IS_ERR(ost->clk))
		वापस PTR_ERR(ost->clk);

	err = clk_prepare_enable(ost->clk);
	अगर (err)
		वापस err;

	/* Clear counter high/low रेजिस्टरs */
	अगर (soc_info->is64bit)
		regmap_ग_लिखो(map, TCU_REG_OST_CNTL, 0);
	regmap_ग_लिखो(map, TCU_REG_OST_CNTH, 0);

	/* Don't reset counter at compare value. */
	regmap_update_bits(map, TCU_REG_OST_TCSR,
			   TCU_OST_TCSR_MASK, TCU_OST_TCSR_CNT_MD);

	rate = clk_get_rate(ost->clk);

	/* Enable OST TCU channel */
	regmap_ग_लिखो(map, TCU_REG_TESR, BIT(TCU_OST_CHANNEL));

	cs = &ost->cs;
	cs->name	= "ingenic-ost";
	cs->rating	= 320;
	cs->flags	= CLOCK_SOURCE_IS_CONTINUOUS;
	cs->mask	= CLOCKSOURCE_MASK(32);

	अगर (soc_info->is64bit)
		cs->पढ़ो = ingenic_ost_घड़ीsource_पढ़ोl;
	अन्यथा
		cs->पढ़ो = ingenic_ost_घड़ीsource_पढ़ोh;

	err = घड़ीsource_रेजिस्टर_hz(cs, rate);
	अगर (err) अणु
		dev_err(dev, "clocksource registration failed");
		clk_disable_unprepare(ost->clk);
		वापस err;
	पूर्ण

	अगर (soc_info->is64bit)
		sched_घड़ी_रेजिस्टर(ingenic_ost_पढ़ो_cntl, 32, rate);
	अन्यथा
		sched_घड़ी_रेजिस्टर(ingenic_ost_पढ़ो_cnth, 32, rate);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused ingenic_ost_suspend(काष्ठा device *dev)
अणु
	काष्ठा ingenic_ost *ost = dev_get_drvdata(dev);

	clk_disable(ost->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused ingenic_ost_resume(काष्ठा device *dev)
अणु
	काष्ठा ingenic_ost *ost = dev_get_drvdata(dev);

	वापस clk_enable(ost->clk);
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops __maybe_unused ingenic_ost_pm_ops = अणु
	/* _noirq: We want the OST घड़ी to be gated last / ungated first */
	.suspend_noirq = ingenic_ost_suspend,
	.resume_noirq  = ingenic_ost_resume,
पूर्ण;

अटल स्थिर काष्ठा ingenic_ost_soc_info jz4725b_ost_soc_info = अणु
	.is64bit = false,
पूर्ण;

अटल स्थिर काष्ठा ingenic_ost_soc_info jz4760b_ost_soc_info = अणु
	.is64bit = true,
पूर्ण;

अटल स्थिर काष्ठा of_device_id ingenic_ost_of_match[] = अणु
	अणु .compatible = "ingenic,jz4725b-ost", .data = &jz4725b_ost_soc_info, पूर्ण,
	अणु .compatible = "ingenic,jz4760b-ost", .data = &jz4760b_ost_soc_info, पूर्ण,
	अणु .compatible = "ingenic,jz4770-ost", .data = &jz4760b_ost_soc_info, पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver ingenic_ost_driver = अणु
	.driver = अणु
		.name = "ingenic-ost",
#अगर_घोषित CONFIG_PM_SUSPEND
		.pm = &ingenic_ost_pm_ops,
#पूर्ण_अगर
		.of_match_table = ingenic_ost_of_match,
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver_probe(ingenic_ost_driver, ingenic_ost_probe);
