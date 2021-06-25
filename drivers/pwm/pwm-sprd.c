<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2019 Spपढ़ोtrum Communications Inc.
 */

#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/math64.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pwm.h>

#घोषणा SPRD_PWM_PRESCALE	0x0
#घोषणा SPRD_PWM_MOD		0x4
#घोषणा SPRD_PWM_DUTY		0x8
#घोषणा SPRD_PWM_ENABLE		0x18

#घोषणा SPRD_PWM_MOD_MAX	GENMASK(7, 0)
#घोषणा SPRD_PWM_DUTY_MSK	GENMASK(15, 0)
#घोषणा SPRD_PWM_PRESCALE_MSK	GENMASK(7, 0)
#घोषणा SPRD_PWM_ENABLE_BIT	BIT(0)

#घोषणा SPRD_PWM_CHN_NUM	4
#घोषणा SPRD_PWM_REGS_SHIFT	5
#घोषणा SPRD_PWM_CHN_CLKS_NUM	2
#घोषणा SPRD_PWM_CHN_OUTPUT_CLK	1

काष्ठा sprd_pwm_chn अणु
	काष्ठा clk_bulk_data clks[SPRD_PWM_CHN_CLKS_NUM];
	u32 clk_rate;
पूर्ण;

काष्ठा sprd_pwm_chip अणु
	व्योम __iomem *base;
	काष्ठा device *dev;
	काष्ठा pwm_chip chip;
	पूर्णांक num_pwms;
	काष्ठा sprd_pwm_chn chn[SPRD_PWM_CHN_NUM];
पूर्ण;

/*
 * The list of घड़ीs required by PWM channels, and each channel has 2 घड़ीs:
 * enable घड़ी and pwm घड़ी.
 */
अटल स्थिर अक्षर * स्थिर sprd_pwm_clks[] = अणु
	"enable0", "pwm0",
	"enable1", "pwm1",
	"enable2", "pwm2",
	"enable3", "pwm3",
पूर्ण;

अटल u32 sprd_pwm_पढ़ो(काष्ठा sprd_pwm_chip *spc, u32 hwid, u32 reg)
अणु
	u32 offset = reg + (hwid << SPRD_PWM_REGS_SHIFT);

	वापस पढ़ोl_relaxed(spc->base + offset);
पूर्ण

अटल व्योम sprd_pwm_ग_लिखो(काष्ठा sprd_pwm_chip *spc, u32 hwid,
			   u32 reg, u32 val)
अणु
	u32 offset = reg + (hwid << SPRD_PWM_REGS_SHIFT);

	ग_लिखोl_relaxed(val, spc->base + offset);
पूर्ण

अटल व्योम sprd_pwm_get_state(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm,
			       काष्ठा pwm_state *state)
अणु
	काष्ठा sprd_pwm_chip *spc =
		container_of(chip, काष्ठा sprd_pwm_chip, chip);
	काष्ठा sprd_pwm_chn *chn = &spc->chn[pwm->hwpwm];
	u32 val, duty, prescale;
	u64 पंचांगp;
	पूर्णांक ret;

	/*
	 * The घड़ीs to PWM channel has to be enabled first beक्रमe
	 * पढ़ोing to the रेजिस्टरs.
	 */
	ret = clk_bulk_prepare_enable(SPRD_PWM_CHN_CLKS_NUM, chn->clks);
	अगर (ret) अणु
		dev_err(spc->dev, "failed to enable pwm%u clocks\n",
			pwm->hwpwm);
		वापस;
	पूर्ण

	val = sprd_pwm_पढ़ो(spc, pwm->hwpwm, SPRD_PWM_ENABLE);
	अगर (val & SPRD_PWM_ENABLE_BIT)
		state->enabled = true;
	अन्यथा
		state->enabled = false;

	/*
	 * The hardware provides a counter that is feed by the source घड़ी.
	 * The period length is (PRESCALE + 1) * MOD counter steps.
	 * The duty cycle length is (PRESCALE + 1) * DUTY counter steps.
	 * Thus the period_ns and duty_ns calculation क्रमmula should be:
	 * period_ns = NSEC_PER_SEC * (prescale + 1) * mod / clk_rate
	 * duty_ns = NSEC_PER_SEC * (prescale + 1) * duty / clk_rate
	 */
	val = sprd_pwm_पढ़ो(spc, pwm->hwpwm, SPRD_PWM_PRESCALE);
	prescale = val & SPRD_PWM_PRESCALE_MSK;
	पंचांगp = (prescale + 1) * NSEC_PER_SEC * SPRD_PWM_MOD_MAX;
	state->period = DIV_ROUND_CLOSEST_ULL(पंचांगp, chn->clk_rate);

	val = sprd_pwm_पढ़ो(spc, pwm->hwpwm, SPRD_PWM_DUTY);
	duty = val & SPRD_PWM_DUTY_MSK;
	पंचांगp = (prescale + 1) * NSEC_PER_SEC * duty;
	state->duty_cycle = DIV_ROUND_CLOSEST_ULL(पंचांगp, chn->clk_rate);

	/* Disable PWM घड़ीs अगर the PWM channel is not in enable state. */
	अगर (!state->enabled)
		clk_bulk_disable_unprepare(SPRD_PWM_CHN_CLKS_NUM, chn->clks);
पूर्ण

अटल पूर्णांक sprd_pwm_config(काष्ठा sprd_pwm_chip *spc, काष्ठा pwm_device *pwm,
			   पूर्णांक duty_ns, पूर्णांक period_ns)
अणु
	काष्ठा sprd_pwm_chn *chn = &spc->chn[pwm->hwpwm];
	u32 prescale, duty;
	u64 पंचांगp;

	/*
	 * The hardware provides a counter that is feed by the source घड़ी.
	 * The period length is (PRESCALE + 1) * MOD counter steps.
	 * The duty cycle length is (PRESCALE + 1) * DUTY counter steps.
	 *
	 * To keep the maths simple we're always using MOD = SPRD_PWM_MOD_MAX.
	 * The value क्रम PRESCALE is selected such that the resulting period
	 * माला_लो the maximal length not bigger than the requested one with the
	 * given settings (MOD = SPRD_PWM_MOD_MAX and input घड़ी).
	 */
	duty = duty_ns * SPRD_PWM_MOD_MAX / period_ns;

	पंचांगp = (u64)chn->clk_rate * period_ns;
	करो_भाग(पंचांगp, NSEC_PER_SEC);
	prescale = DIV_ROUND_CLOSEST_ULL(पंचांगp, SPRD_PWM_MOD_MAX) - 1;
	अगर (prescale > SPRD_PWM_PRESCALE_MSK)
		prescale = SPRD_PWM_PRESCALE_MSK;

	/*
	 * Note: Writing DUTY triggers the hardware to actually apply the
	 * values written to MOD and DUTY to the output, so must keep writing
	 * DUTY last.
	 *
	 * The hardware can ensures that current running period is completed
	 * beक्रमe changing a new configuration to aव्योम mixed settings.
	 */
	sprd_pwm_ग_लिखो(spc, pwm->hwpwm, SPRD_PWM_PRESCALE, prescale);
	sprd_pwm_ग_लिखो(spc, pwm->hwpwm, SPRD_PWM_MOD, SPRD_PWM_MOD_MAX);
	sprd_pwm_ग_लिखो(spc, pwm->hwpwm, SPRD_PWM_DUTY, duty);

	वापस 0;
पूर्ण

अटल पूर्णांक sprd_pwm_apply(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm,
			  स्थिर काष्ठा pwm_state *state)
अणु
	काष्ठा sprd_pwm_chip *spc =
		container_of(chip, काष्ठा sprd_pwm_chip, chip);
	काष्ठा sprd_pwm_chn *chn = &spc->chn[pwm->hwpwm];
	काष्ठा pwm_state *cstate = &pwm->state;
	पूर्णांक ret;

	अगर (state->polarity != PWM_POLARITY_NORMAL)
		वापस -EINVAL;

	अगर (state->enabled) अणु
		अगर (!cstate->enabled) अणु
			/*
			 * The घड़ीs to PWM channel has to be enabled first
			 * beक्रमe writing to the रेजिस्टरs.
			 */
			ret = clk_bulk_prepare_enable(SPRD_PWM_CHN_CLKS_NUM,
						      chn->clks);
			अगर (ret) अणु
				dev_err(spc->dev,
					"failed to enable pwm%u clocks\n",
					pwm->hwpwm);
				वापस ret;
			पूर्ण
		पूर्ण

		अगर (state->period != cstate->period ||
		    state->duty_cycle != cstate->duty_cycle) अणु
			ret = sprd_pwm_config(spc, pwm, state->duty_cycle,
					      state->period);
			अगर (ret)
				वापस ret;
		पूर्ण

		sprd_pwm_ग_लिखो(spc, pwm->hwpwm, SPRD_PWM_ENABLE, 1);
	पूर्ण अन्यथा अगर (cstate->enabled) अणु
		/*
		 * Note: After setting SPRD_PWM_ENABLE to zero, the controller
		 * will not रुको क्रम current period to be completed, instead it
		 * will stop the PWM channel immediately.
		 */
		sprd_pwm_ग_लिखो(spc, pwm->hwpwm, SPRD_PWM_ENABLE, 0);

		clk_bulk_disable_unprepare(SPRD_PWM_CHN_CLKS_NUM, chn->clks);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pwm_ops sprd_pwm_ops = अणु
	.apply = sprd_pwm_apply,
	.get_state = sprd_pwm_get_state,
	.owner = THIS_MODULE,
पूर्ण;

अटल पूर्णांक sprd_pwm_clk_init(काष्ठा sprd_pwm_chip *spc)
अणु
	काष्ठा clk *clk_pwm;
	पूर्णांक ret, i;

	क्रम (i = 0; i < SPRD_PWM_CHN_NUM; i++) अणु
		काष्ठा sprd_pwm_chn *chn = &spc->chn[i];
		पूर्णांक j;

		क्रम (j = 0; j < SPRD_PWM_CHN_CLKS_NUM; ++j)
			chn->clks[j].id =
				sprd_pwm_clks[i * SPRD_PWM_CHN_CLKS_NUM + j];

		ret = devm_clk_bulk_get(spc->dev, SPRD_PWM_CHN_CLKS_NUM,
					chn->clks);
		अगर (ret) अणु
			अगर (ret == -ENOENT)
				अवरोध;

			वापस dev_err_probe(spc->dev, ret,
					     "failed to get channel clocks\n");
		पूर्ण

		clk_pwm = chn->clks[SPRD_PWM_CHN_OUTPUT_CLK].clk;
		chn->clk_rate = clk_get_rate(clk_pwm);
	पूर्ण

	अगर (!i) अणु
		dev_err(spc->dev, "no available PWM channels\n");
		वापस -ENODEV;
	पूर्ण

	spc->num_pwms = i;

	वापस 0;
पूर्ण

अटल पूर्णांक sprd_pwm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sprd_pwm_chip *spc;
	पूर्णांक ret;

	spc = devm_kzalloc(&pdev->dev, माप(*spc), GFP_KERNEL);
	अगर (!spc)
		वापस -ENOMEM;

	spc->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(spc->base))
		वापस PTR_ERR(spc->base);

	spc->dev = &pdev->dev;
	platक्रमm_set_drvdata(pdev, spc);

	ret = sprd_pwm_clk_init(spc);
	अगर (ret)
		वापस ret;

	spc->chip.dev = &pdev->dev;
	spc->chip.ops = &sprd_pwm_ops;
	spc->chip.npwm = spc->num_pwms;

	ret = pwmchip_add(&spc->chip);
	अगर (ret)
		dev_err(&pdev->dev, "failed to add PWM chip\n");

	वापस ret;
पूर्ण

अटल पूर्णांक sprd_pwm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sprd_pwm_chip *spc = platक्रमm_get_drvdata(pdev);

	वापस pwmchip_हटाओ(&spc->chip);
पूर्ण

अटल स्थिर काष्ठा of_device_id sprd_pwm_of_match[] = अणु
	अणु .compatible = "sprd,ums512-pwm", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sprd_pwm_of_match);

अटल काष्ठा platक्रमm_driver sprd_pwm_driver = अणु
	.driver = अणु
		.name = "sprd-pwm",
		.of_match_table = sprd_pwm_of_match,
	पूर्ण,
	.probe = sprd_pwm_probe,
	.हटाओ = sprd_pwm_हटाओ,
पूर्ण;

module_platक्रमm_driver(sprd_pwm_driver);

MODULE_DESCRIPTION("Spreadtrum PWM Driver");
MODULE_LICENSE("GPL v2");
