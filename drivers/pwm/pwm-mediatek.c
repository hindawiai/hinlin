<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * MediaTek Pulse Width Modulator driver
 *
 * Copyright (C) 2015 John Crispin <blogic@खोलोwrt.org>
 * Copyright (C) 2017 Zhi Mao <zhi.mao@mediatek.com>
 *
 */

#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/ioport.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/clk.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pwm.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>

/* PWM रेजिस्टरs and bits definitions */
#घोषणा PWMCON			0x00
#घोषणा PWMHDUR			0x04
#घोषणा PWMLDUR			0x08
#घोषणा PWMGDUR			0x0c
#घोषणा PWMWAVENUM		0x28
#घोषणा PWMDWIDTH		0x2c
#घोषणा PWM45DWIDTH_FIXUP	0x30
#घोषणा PWMTHRES		0x30
#घोषणा PWM45THRES_FIXUP	0x34
#घोषणा PWM_CK_26M_SEL		0x210

#घोषणा PWM_CLK_DIV_MAX		7

काष्ठा pwm_mediatek_of_data अणु
	अचिन्हित पूर्णांक num_pwms;
	bool pwm45_fixup;
	bool has_ck_26m_sel;
पूर्ण;

/**
 * काष्ठा pwm_mediatek_chip - काष्ठा representing PWM chip
 * @chip: linux PWM chip representation
 * @regs: base address of PWM chip
 * @clk_top: the top घड़ी generator
 * @clk_मुख्य: the घड़ी used by PWM core
 * @clk_pwms: the घड़ी used by each PWM channel
 * @clk_freq: the fix घड़ी frequency of legacy MIPS SoC
 * @soc: poपूर्णांकer to chip's platक्रमm data
 */
काष्ठा pwm_mediatek_chip अणु
	काष्ठा pwm_chip chip;
	व्योम __iomem *regs;
	काष्ठा clk *clk_top;
	काष्ठा clk *clk_मुख्य;
	काष्ठा clk **clk_pwms;
	स्थिर काष्ठा pwm_mediatek_of_data *soc;
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक pwm_mediatek_reg_offset[] = अणु
	0x0010, 0x0050, 0x0090, 0x00d0, 0x0110, 0x0150, 0x0190, 0x0220
पूर्ण;

अटल अंतरभूत काष्ठा pwm_mediatek_chip *
to_pwm_mediatek_chip(काष्ठा pwm_chip *chip)
अणु
	वापस container_of(chip, काष्ठा pwm_mediatek_chip, chip);
पूर्ण

अटल पूर्णांक pwm_mediatek_clk_enable(काष्ठा pwm_chip *chip,
				   काष्ठा pwm_device *pwm)
अणु
	काष्ठा pwm_mediatek_chip *pc = to_pwm_mediatek_chip(chip);
	पूर्णांक ret;

	ret = clk_prepare_enable(pc->clk_top);
	अगर (ret < 0)
		वापस ret;

	ret = clk_prepare_enable(pc->clk_मुख्य);
	अगर (ret < 0)
		जाओ disable_clk_top;

	ret = clk_prepare_enable(pc->clk_pwms[pwm->hwpwm]);
	अगर (ret < 0)
		जाओ disable_clk_मुख्य;

	वापस 0;

disable_clk_मुख्य:
	clk_disable_unprepare(pc->clk_मुख्य);
disable_clk_top:
	clk_disable_unprepare(pc->clk_top);

	वापस ret;
पूर्ण

अटल व्योम pwm_mediatek_clk_disable(काष्ठा pwm_chip *chip,
				     काष्ठा pwm_device *pwm)
अणु
	काष्ठा pwm_mediatek_chip *pc = to_pwm_mediatek_chip(chip);

	clk_disable_unprepare(pc->clk_pwms[pwm->hwpwm]);
	clk_disable_unprepare(pc->clk_मुख्य);
	clk_disable_unprepare(pc->clk_top);
पूर्ण

अटल अंतरभूत व्योम pwm_mediatek_ग_लिखोl(काष्ठा pwm_mediatek_chip *chip,
				       अचिन्हित पूर्णांक num, अचिन्हित पूर्णांक offset,
				       u32 value)
अणु
	ग_लिखोl(value, chip->regs + pwm_mediatek_reg_offset[num] + offset);
पूर्ण

अटल पूर्णांक pwm_mediatek_config(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm,
			       पूर्णांक duty_ns, पूर्णांक period_ns)
अणु
	काष्ठा pwm_mediatek_chip *pc = to_pwm_mediatek_chip(chip);
	u32 clkभाग = 0, cnt_period, cnt_duty, reg_width = PWMDWIDTH,
	    reg_thres = PWMTHRES;
	u64 resolution;
	पूर्णांक ret;

	ret = pwm_mediatek_clk_enable(chip, pwm);

	अगर (ret < 0)
		वापस ret;

	/* Make sure we use the bus घड़ी and not the 26MHz घड़ी */
	अगर (pc->soc->has_ck_26m_sel)
		ग_लिखोl(0, pc->regs + PWM_CK_26M_SEL);

	/* Using resolution in picosecond माला_लो accuracy higher */
	resolution = (u64)NSEC_PER_SEC * 1000;
	करो_भाग(resolution, clk_get_rate(pc->clk_pwms[pwm->hwpwm]));

	cnt_period = DIV_ROUND_CLOSEST_ULL((u64)period_ns * 1000, resolution);
	जबतक (cnt_period > 8191) अणु
		resolution *= 2;
		clkभाग++;
		cnt_period = DIV_ROUND_CLOSEST_ULL((u64)period_ns * 1000,
						   resolution);
	पूर्ण

	अगर (clkभाग > PWM_CLK_DIV_MAX) अणु
		pwm_mediatek_clk_disable(chip, pwm);
		dev_err(chip->dev, "period %d not supported\n", period_ns);
		वापस -EINVAL;
	पूर्ण

	अगर (pc->soc->pwm45_fixup && pwm->hwpwm > 2) अणु
		/*
		 * PWM[4,5] has distinct offset क्रम PWMDWIDTH and PWMTHRES
		 * from the other PWMs on MT7623.
		 */
		reg_width = PWM45DWIDTH_FIXUP;
		reg_thres = PWM45THRES_FIXUP;
	पूर्ण

	cnt_duty = DIV_ROUND_CLOSEST_ULL((u64)duty_ns * 1000, resolution);
	pwm_mediatek_ग_लिखोl(pc, pwm->hwpwm, PWMCON, BIT(15) | clkभाग);
	pwm_mediatek_ग_लिखोl(pc, pwm->hwpwm, reg_width, cnt_period);
	pwm_mediatek_ग_लिखोl(pc, pwm->hwpwm, reg_thres, cnt_duty);

	pwm_mediatek_clk_disable(chip, pwm);

	वापस 0;
पूर्ण

अटल पूर्णांक pwm_mediatek_enable(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm)
अणु
	काष्ठा pwm_mediatek_chip *pc = to_pwm_mediatek_chip(chip);
	u32 value;
	पूर्णांक ret;

	ret = pwm_mediatek_clk_enable(chip, pwm);
	अगर (ret < 0)
		वापस ret;

	value = पढ़ोl(pc->regs);
	value |= BIT(pwm->hwpwm);
	ग_लिखोl(value, pc->regs);

	वापस 0;
पूर्ण

अटल व्योम pwm_mediatek_disable(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm)
अणु
	काष्ठा pwm_mediatek_chip *pc = to_pwm_mediatek_chip(chip);
	u32 value;

	value = पढ़ोl(pc->regs);
	value &= ~BIT(pwm->hwpwm);
	ग_लिखोl(value, pc->regs);

	pwm_mediatek_clk_disable(chip, pwm);
पूर्ण

अटल स्थिर काष्ठा pwm_ops pwm_mediatek_ops = अणु
	.config = pwm_mediatek_config,
	.enable = pwm_mediatek_enable,
	.disable = pwm_mediatek_disable,
	.owner = THIS_MODULE,
पूर्ण;

अटल पूर्णांक pwm_mediatek_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pwm_mediatek_chip *pc;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	pc = devm_kzalloc(&pdev->dev, माप(*pc), GFP_KERNEL);
	अगर (!pc)
		वापस -ENOMEM;

	pc->soc = of_device_get_match_data(&pdev->dev);

	pc->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(pc->regs))
		वापस PTR_ERR(pc->regs);

	pc->clk_pwms = devm_kसुस्मृति(&pdev->dev, pc->soc->num_pwms,
				    माप(*pc->clk_pwms), GFP_KERNEL);
	अगर (!pc->clk_pwms)
		वापस -ENOMEM;

	pc->clk_top = devm_clk_get(&pdev->dev, "top");
	अगर (IS_ERR(pc->clk_top)) अणु
		dev_err(&pdev->dev, "clock: top fail: %ld\n",
			PTR_ERR(pc->clk_top));
		वापस PTR_ERR(pc->clk_top);
	पूर्ण

	pc->clk_मुख्य = devm_clk_get(&pdev->dev, "main");
	अगर (IS_ERR(pc->clk_मुख्य)) अणु
		dev_err(&pdev->dev, "clock: main fail: %ld\n",
			PTR_ERR(pc->clk_मुख्य));
		वापस PTR_ERR(pc->clk_मुख्य);
	पूर्ण

	क्रम (i = 0; i < pc->soc->num_pwms; i++) अणु
		अक्षर name[8];

		snम_लिखो(name, माप(name), "pwm%d", i + 1);

		pc->clk_pwms[i] = devm_clk_get(&pdev->dev, name);
		अगर (IS_ERR(pc->clk_pwms[i])) अणु
			dev_err(&pdev->dev, "clock: %s fail: %ld\n",
				name, PTR_ERR(pc->clk_pwms[i]));
			वापस PTR_ERR(pc->clk_pwms[i]);
		पूर्ण
	पूर्ण

	platक्रमm_set_drvdata(pdev, pc);

	pc->chip.dev = &pdev->dev;
	pc->chip.ops = &pwm_mediatek_ops;
	pc->chip.npwm = pc->soc->num_pwms;

	ret = pwmchip_add(&pc->chip);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "pwmchip_add() failed: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pwm_mediatek_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pwm_mediatek_chip *pc = platक्रमm_get_drvdata(pdev);

	वापस pwmchip_हटाओ(&pc->chip);
पूर्ण

अटल स्थिर काष्ठा pwm_mediatek_of_data mt2712_pwm_data = अणु
	.num_pwms = 8,
	.pwm45_fixup = false,
	.has_ck_26m_sel = false,
पूर्ण;

अटल स्थिर काष्ठा pwm_mediatek_of_data mt7622_pwm_data = अणु
	.num_pwms = 6,
	.pwm45_fixup = false,
	.has_ck_26m_sel = false,
पूर्ण;

अटल स्थिर काष्ठा pwm_mediatek_of_data mt7623_pwm_data = अणु
	.num_pwms = 5,
	.pwm45_fixup = true,
	.has_ck_26m_sel = false,
पूर्ण;

अटल स्थिर काष्ठा pwm_mediatek_of_data mt7628_pwm_data = अणु
	.num_pwms = 4,
	.pwm45_fixup = true,
	.has_ck_26m_sel = false,
पूर्ण;

अटल स्थिर काष्ठा pwm_mediatek_of_data mt7629_pwm_data = अणु
	.num_pwms = 1,
	.pwm45_fixup = false,
	.has_ck_26m_sel = false,
पूर्ण;

अटल स्थिर काष्ठा pwm_mediatek_of_data mt8183_pwm_data = अणु
	.num_pwms = 4,
	.pwm45_fixup = false,
	.has_ck_26m_sel = true,
पूर्ण;

अटल स्थिर काष्ठा pwm_mediatek_of_data mt8516_pwm_data = अणु
	.num_pwms = 5,
	.pwm45_fixup = false,
	.has_ck_26m_sel = true,
पूर्ण;

अटल स्थिर काष्ठा of_device_id pwm_mediatek_of_match[] = अणु
	अणु .compatible = "mediatek,mt2712-pwm", .data = &mt2712_pwm_data पूर्ण,
	अणु .compatible = "mediatek,mt7622-pwm", .data = &mt7622_pwm_data पूर्ण,
	अणु .compatible = "mediatek,mt7623-pwm", .data = &mt7623_pwm_data पूर्ण,
	अणु .compatible = "mediatek,mt7628-pwm", .data = &mt7628_pwm_data पूर्ण,
	अणु .compatible = "mediatek,mt7629-pwm", .data = &mt7629_pwm_data पूर्ण,
	अणु .compatible = "mediatek,mt8183-pwm", .data = &mt8183_pwm_data पूर्ण,
	अणु .compatible = "mediatek,mt8516-pwm", .data = &mt8516_pwm_data पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, pwm_mediatek_of_match);

अटल काष्ठा platक्रमm_driver pwm_mediatek_driver = अणु
	.driver = अणु
		.name = "pwm-mediatek",
		.of_match_table = pwm_mediatek_of_match,
	पूर्ण,
	.probe = pwm_mediatek_probe,
	.हटाओ = pwm_mediatek_हटाओ,
पूर्ण;
module_platक्रमm_driver(pwm_mediatek_driver);

MODULE_AUTHOR("John Crispin <blogic@openwrt.org>");
MODULE_LICENSE("GPL v2");
