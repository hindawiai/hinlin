<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * NXP LPC18xx State Configurable Timer - Pulse Width Modulator driver
 *
 * Copyright (c) 2015 Ariel D'Alessandro <ariel@vanguardiasur.com>
 *
 * Notes
 * =====
 * NXP LPC18xx provides a State Configurable Timer (SCT) which can be configured
 * as a Pulse Width Modulator.
 *
 * SCT supports 16 outमाला_दो, 16 events and 16 रेजिस्टरs. Each event will be
 * triggered when its related रेजिस्टर matches the SCT counter value, and it
 * will set or clear a selected output.
 *
 * One of the events is preselected to generate the period, thus the maximum
 * number of simultaneous channels is limited to 15. Notice that period is
 * global to all the channels, thus PWM driver will refuse setting dअगरferent
 * values to it, unless there's only one channel requested.
 */

#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pwm.h>

/* LPC18xx SCT रेजिस्टरs */
#घोषणा LPC18XX_PWM_CONFIG		0x000
#घोषणा LPC18XX_PWM_CONFIG_UNIFY	BIT(0)
#घोषणा LPC18XX_PWM_CONFIG_NORELOAD	BIT(7)

#घोषणा LPC18XX_PWM_CTRL		0x004
#घोषणा LPC18XX_PWM_CTRL_HALT		BIT(2)
#घोषणा LPC18XX_PWM_BIसूची		BIT(4)
#घोषणा LPC18XX_PWM_PRE_SHIFT		5
#घोषणा LPC18XX_PWM_PRE_MASK		(0xff << LPC18XX_PWM_PRE_SHIFT)
#घोषणा LPC18XX_PWM_PRE(x)		(x << LPC18XX_PWM_PRE_SHIFT)

#घोषणा LPC18XX_PWM_LIMIT		0x008

#घोषणा LPC18XX_PWM_RES_BASE		0x058
#घोषणा LPC18XX_PWM_RES_SHIFT(_ch)	(_ch * 2)
#घोषणा LPC18XX_PWM_RES(_ch, _action)	(_action << LPC18XX_PWM_RES_SHIFT(_ch))
#घोषणा LPC18XX_PWM_RES_MASK(_ch)	(0x3 << LPC18XX_PWM_RES_SHIFT(_ch))

#घोषणा LPC18XX_PWM_MATCH_BASE		0x100
#घोषणा LPC18XX_PWM_MATCH(_ch)		(LPC18XX_PWM_MATCH_BASE + _ch * 4)

#घोषणा LPC18XX_PWM_MATCHREL_BASE	0x200
#घोषणा LPC18XX_PWM_MATCHREL(_ch)	(LPC18XX_PWM_MATCHREL_BASE + _ch * 4)

#घोषणा LPC18XX_PWM_EVSTATEMSK_BASE	0x300
#घोषणा LPC18XX_PWM_EVSTATEMSK(_ch)	(LPC18XX_PWM_EVSTATEMSK_BASE + _ch * 8)
#घोषणा LPC18XX_PWM_EVSTATEMSK_ALL	0xffffffff

#घोषणा LPC18XX_PWM_EVCTRL_BASE		0x304
#घोषणा LPC18XX_PWM_EVCTRL(_ev)		(LPC18XX_PWM_EVCTRL_BASE + _ev * 8)

#घोषणा LPC18XX_PWM_EVCTRL_MATCH(_ch)	_ch

#घोषणा LPC18XX_PWM_EVCTRL_COMB_SHIFT	12
#घोषणा LPC18XX_PWM_EVCTRL_COMB_MATCH	(0x1 << LPC18XX_PWM_EVCTRL_COMB_SHIFT)

#घोषणा LPC18XX_PWM_OUTPUTSET_BASE	0x500
#घोषणा LPC18XX_PWM_OUTPUTSET(_ch)	(LPC18XX_PWM_OUTPUTSET_BASE + _ch * 8)

#घोषणा LPC18XX_PWM_OUTPUTCL_BASE	0x504
#घोषणा LPC18XX_PWM_OUTPUTCL(_ch)	(LPC18XX_PWM_OUTPUTCL_BASE + _ch * 8)

/* LPC18xx SCT unअगरied counter */
#घोषणा LPC18XX_PWM_TIMER_MAX		0xffffffff

/* LPC18xx SCT events */
#घोषणा LPC18XX_PWM_EVENT_PERIOD	0
#घोषणा LPC18XX_PWM_EVENT_MAX		16

/* SCT conflict resolution */
क्रमागत lpc18xx_pwm_res_action अणु
	LPC18XX_PWM_RES_NONE,
	LPC18XX_PWM_RES_SET,
	LPC18XX_PWM_RES_CLEAR,
	LPC18XX_PWM_RES_TOGGLE,
पूर्ण;

काष्ठा lpc18xx_pwm_data अणु
	अचिन्हित पूर्णांक duty_event;
पूर्ण;

काष्ठा lpc18xx_pwm_chip अणु
	काष्ठा device *dev;
	काष्ठा pwm_chip chip;
	व्योम __iomem *base;
	काष्ठा clk *pwm_clk;
	अचिन्हित दीर्घ clk_rate;
	अचिन्हित पूर्णांक period_ns;
	अचिन्हित पूर्णांक min_period_ns;
	अचिन्हित पूर्णांक max_period_ns;
	अचिन्हित पूर्णांक period_event;
	अचिन्हित दीर्घ event_map;
	काष्ठा mutex res_lock;
	काष्ठा mutex period_lock;
पूर्ण;

अटल अंतरभूत काष्ठा lpc18xx_pwm_chip *
to_lpc18xx_pwm_chip(काष्ठा pwm_chip *chip)
अणु
	वापस container_of(chip, काष्ठा lpc18xx_pwm_chip, chip);
पूर्ण

अटल अंतरभूत व्योम lpc18xx_pwm_ग_लिखोl(काष्ठा lpc18xx_pwm_chip *lpc18xx_pwm,
				      u32 reg, u32 val)
अणु
	ग_लिखोl(val, lpc18xx_pwm->base + reg);
पूर्ण

अटल अंतरभूत u32 lpc18xx_pwm_पढ़ोl(काष्ठा lpc18xx_pwm_chip *lpc18xx_pwm,
				    u32 reg)
अणु
	वापस पढ़ोl(lpc18xx_pwm->base + reg);
पूर्ण

अटल व्योम lpc18xx_pwm_set_conflict_res(काष्ठा lpc18xx_pwm_chip *lpc18xx_pwm,
					 काष्ठा pwm_device *pwm,
					 क्रमागत lpc18xx_pwm_res_action action)
अणु
	u32 val;

	mutex_lock(&lpc18xx_pwm->res_lock);

	/*
	 * Simultaneous set and clear may happen on an output, that is the हाल
	 * when duty_ns == period_ns. LPC18xx SCT allows to set a conflict
	 * resolution action to be taken in such a हाल.
	 */
	val = lpc18xx_pwm_पढ़ोl(lpc18xx_pwm, LPC18XX_PWM_RES_BASE);
	val &= ~LPC18XX_PWM_RES_MASK(pwm->hwpwm);
	val |= LPC18XX_PWM_RES(pwm->hwpwm, action);
	lpc18xx_pwm_ग_लिखोl(lpc18xx_pwm, LPC18XX_PWM_RES_BASE, val);

	mutex_unlock(&lpc18xx_pwm->res_lock);
पूर्ण

अटल व्योम lpc18xx_pwm_config_period(काष्ठा pwm_chip *chip, पूर्णांक period_ns)
अणु
	काष्ठा lpc18xx_pwm_chip *lpc18xx_pwm = to_lpc18xx_pwm_chip(chip);
	u64 val;

	val = (u64)period_ns * lpc18xx_pwm->clk_rate;
	करो_भाग(val, NSEC_PER_SEC);

	lpc18xx_pwm_ग_लिखोl(lpc18xx_pwm,
			   LPC18XX_PWM_MATCH(lpc18xx_pwm->period_event),
			   (u32)val - 1);

	lpc18xx_pwm_ग_लिखोl(lpc18xx_pwm,
			   LPC18XX_PWM_MATCHREL(lpc18xx_pwm->period_event),
			   (u32)val - 1);
पूर्ण

अटल व्योम lpc18xx_pwm_config_duty(काष्ठा pwm_chip *chip,
				    काष्ठा pwm_device *pwm, पूर्णांक duty_ns)
अणु
	काष्ठा lpc18xx_pwm_chip *lpc18xx_pwm = to_lpc18xx_pwm_chip(chip);
	काष्ठा lpc18xx_pwm_data *lpc18xx_data = pwm_get_chip_data(pwm);
	u64 val;

	val = (u64)duty_ns * lpc18xx_pwm->clk_rate;
	करो_भाग(val, NSEC_PER_SEC);

	lpc18xx_pwm_ग_लिखोl(lpc18xx_pwm,
			   LPC18XX_PWM_MATCH(lpc18xx_data->duty_event),
			   (u32)val);

	lpc18xx_pwm_ग_लिखोl(lpc18xx_pwm,
			   LPC18XX_PWM_MATCHREL(lpc18xx_data->duty_event),
			   (u32)val);
पूर्ण

अटल पूर्णांक lpc18xx_pwm_config(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm,
			      पूर्णांक duty_ns, पूर्णांक period_ns)
अणु
	काष्ठा lpc18xx_pwm_chip *lpc18xx_pwm = to_lpc18xx_pwm_chip(chip);
	पूर्णांक requested_events, i;

	अगर (period_ns < lpc18xx_pwm->min_period_ns ||
	    period_ns > lpc18xx_pwm->max_period_ns) अणु
		dev_err(chip->dev, "period %d not in range\n", period_ns);
		वापस -दुस्फल;
	पूर्ण

	mutex_lock(&lpc18xx_pwm->period_lock);

	requested_events = biपंचांगap_weight(&lpc18xx_pwm->event_map,
					 LPC18XX_PWM_EVENT_MAX);

	/*
	 * The PWM supports only a single period क्रम all PWM channels.
	 * Once the period is set, it can only be changed अगर no more than one
	 * channel is requested at that moment.
	 */
	अगर (requested_events > 2 && lpc18xx_pwm->period_ns != period_ns &&
	    lpc18xx_pwm->period_ns) अणु
		dev_err(chip->dev, "conflicting period requested for PWM %u\n",
			pwm->hwpwm);
		mutex_unlock(&lpc18xx_pwm->period_lock);
		वापस -EBUSY;
	पूर्ण

	अगर ((requested_events <= 2 && lpc18xx_pwm->period_ns != period_ns) ||
	    !lpc18xx_pwm->period_ns) अणु
		lpc18xx_pwm->period_ns = period_ns;
		क्रम (i = 0; i < chip->npwm; i++)
			pwm_set_period(&chip->pwms[i], period_ns);
		lpc18xx_pwm_config_period(chip, period_ns);
	पूर्ण

	mutex_unlock(&lpc18xx_pwm->period_lock);

	lpc18xx_pwm_config_duty(chip, pwm, duty_ns);

	वापस 0;
पूर्ण

अटल पूर्णांक lpc18xx_pwm_set_polarity(काष्ठा pwm_chip *chip,
				    काष्ठा pwm_device *pwm,
				    क्रमागत pwm_polarity polarity)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक lpc18xx_pwm_enable(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm)
अणु
	काष्ठा lpc18xx_pwm_chip *lpc18xx_pwm = to_lpc18xx_pwm_chip(chip);
	काष्ठा lpc18xx_pwm_data *lpc18xx_data = pwm_get_chip_data(pwm);
	क्रमागत lpc18xx_pwm_res_action res_action;
	अचिन्हित पूर्णांक set_event, clear_event;

	lpc18xx_pwm_ग_लिखोl(lpc18xx_pwm,
			   LPC18XX_PWM_EVCTRL(lpc18xx_data->duty_event),
			   LPC18XX_PWM_EVCTRL_MATCH(lpc18xx_data->duty_event) |
			   LPC18XX_PWM_EVCTRL_COMB_MATCH);

	lpc18xx_pwm_ग_लिखोl(lpc18xx_pwm,
			   LPC18XX_PWM_EVSTATEMSK(lpc18xx_data->duty_event),
			   LPC18XX_PWM_EVSTATEMSK_ALL);

	अगर (pwm_get_polarity(pwm) == PWM_POLARITY_NORMAL) अणु
		set_event = lpc18xx_pwm->period_event;
		clear_event = lpc18xx_data->duty_event;
		res_action = LPC18XX_PWM_RES_SET;
	पूर्ण अन्यथा अणु
		set_event = lpc18xx_data->duty_event;
		clear_event = lpc18xx_pwm->period_event;
		res_action = LPC18XX_PWM_RES_CLEAR;
	पूर्ण

	lpc18xx_pwm_ग_लिखोl(lpc18xx_pwm, LPC18XX_PWM_OUTPUTSET(pwm->hwpwm),
			   BIT(set_event));
	lpc18xx_pwm_ग_लिखोl(lpc18xx_pwm, LPC18XX_PWM_OUTPUTCL(pwm->hwpwm),
			   BIT(clear_event));
	lpc18xx_pwm_set_conflict_res(lpc18xx_pwm, pwm, res_action);

	वापस 0;
पूर्ण

अटल व्योम lpc18xx_pwm_disable(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm)
अणु
	काष्ठा lpc18xx_pwm_chip *lpc18xx_pwm = to_lpc18xx_pwm_chip(chip);
	काष्ठा lpc18xx_pwm_data *lpc18xx_data = pwm_get_chip_data(pwm);

	lpc18xx_pwm_ग_लिखोl(lpc18xx_pwm,
			   LPC18XX_PWM_EVCTRL(lpc18xx_data->duty_event), 0);
	lpc18xx_pwm_ग_लिखोl(lpc18xx_pwm, LPC18XX_PWM_OUTPUTSET(pwm->hwpwm), 0);
	lpc18xx_pwm_ग_लिखोl(lpc18xx_pwm, LPC18XX_PWM_OUTPUTCL(pwm->hwpwm), 0);
पूर्ण

अटल पूर्णांक lpc18xx_pwm_request(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm)
अणु
	काष्ठा lpc18xx_pwm_chip *lpc18xx_pwm = to_lpc18xx_pwm_chip(chip);
	काष्ठा lpc18xx_pwm_data *lpc18xx_data = pwm_get_chip_data(pwm);
	अचिन्हित दीर्घ event;

	event = find_first_zero_bit(&lpc18xx_pwm->event_map,
				    LPC18XX_PWM_EVENT_MAX);

	अगर (event >= LPC18XX_PWM_EVENT_MAX) अणु
		dev_err(lpc18xx_pwm->dev,
			"maximum number of simultaneous channels reached\n");
		वापस -EBUSY;
	पूर्ण

	set_bit(event, &lpc18xx_pwm->event_map);
	lpc18xx_data->duty_event = event;

	वापस 0;
पूर्ण

अटल व्योम lpc18xx_pwm_मुक्त(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm)
अणु
	काष्ठा lpc18xx_pwm_chip *lpc18xx_pwm = to_lpc18xx_pwm_chip(chip);
	काष्ठा lpc18xx_pwm_data *lpc18xx_data = pwm_get_chip_data(pwm);

	clear_bit(lpc18xx_data->duty_event, &lpc18xx_pwm->event_map);
पूर्ण

अटल स्थिर काष्ठा pwm_ops lpc18xx_pwm_ops = अणु
	.config = lpc18xx_pwm_config,
	.set_polarity = lpc18xx_pwm_set_polarity,
	.enable = lpc18xx_pwm_enable,
	.disable = lpc18xx_pwm_disable,
	.request = lpc18xx_pwm_request,
	.मुक्त = lpc18xx_pwm_मुक्त,
	.owner = THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा of_device_id lpc18xx_pwm_of_match[] = अणु
	अणु .compatible = "nxp,lpc1850-sct-pwm" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, lpc18xx_pwm_of_match);

अटल पूर्णांक lpc18xx_pwm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा lpc18xx_pwm_chip *lpc18xx_pwm;
	काष्ठा pwm_device *pwm;
	पूर्णांक ret, i;
	u64 val;

	lpc18xx_pwm = devm_kzalloc(&pdev->dev, माप(*lpc18xx_pwm),
				   GFP_KERNEL);
	अगर (!lpc18xx_pwm)
		वापस -ENOMEM;

	lpc18xx_pwm->dev = &pdev->dev;

	lpc18xx_pwm->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(lpc18xx_pwm->base))
		वापस PTR_ERR(lpc18xx_pwm->base);

	lpc18xx_pwm->pwm_clk = devm_clk_get(&pdev->dev, "pwm");
	अगर (IS_ERR(lpc18xx_pwm->pwm_clk)) अणु
		dev_err(&pdev->dev, "failed to get pwm clock\n");
		वापस PTR_ERR(lpc18xx_pwm->pwm_clk);
	पूर्ण

	ret = clk_prepare_enable(lpc18xx_pwm->pwm_clk);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "could not prepare or enable pwm clock\n");
		वापस ret;
	पूर्ण

	lpc18xx_pwm->clk_rate = clk_get_rate(lpc18xx_pwm->pwm_clk);
	अगर (!lpc18xx_pwm->clk_rate) अणु
		dev_err(&pdev->dev, "pwm clock has no frequency\n");
		ret = -EINVAL;
		जाओ disable_pwmclk;
	पूर्ण

	mutex_init(&lpc18xx_pwm->res_lock);
	mutex_init(&lpc18xx_pwm->period_lock);

	val = (u64)NSEC_PER_SEC * LPC18XX_PWM_TIMER_MAX;
	करो_भाग(val, lpc18xx_pwm->clk_rate);
	lpc18xx_pwm->max_period_ns = val;

	lpc18xx_pwm->min_period_ns = DIV_ROUND_UP(NSEC_PER_SEC,
						  lpc18xx_pwm->clk_rate);

	lpc18xx_pwm->chip.dev = &pdev->dev;
	lpc18xx_pwm->chip.ops = &lpc18xx_pwm_ops;
	lpc18xx_pwm->chip.npwm = 16;
	lpc18xx_pwm->chip.of_xlate = of_pwm_xlate_with_flags;
	lpc18xx_pwm->chip.of_pwm_n_cells = 3;

	/* SCT counter must be in unअगरy (32 bit) mode */
	lpc18xx_pwm_ग_लिखोl(lpc18xx_pwm, LPC18XX_PWM_CONFIG,
			   LPC18XX_PWM_CONFIG_UNIFY);

	/*
	 * Everyसमय the समयr counter reaches the period value, the related
	 * event will be triggered and the counter reset to 0.
	 */
	set_bit(LPC18XX_PWM_EVENT_PERIOD, &lpc18xx_pwm->event_map);
	lpc18xx_pwm->period_event = LPC18XX_PWM_EVENT_PERIOD;

	lpc18xx_pwm_ग_लिखोl(lpc18xx_pwm,
			   LPC18XX_PWM_EVSTATEMSK(lpc18xx_pwm->period_event),
			   LPC18XX_PWM_EVSTATEMSK_ALL);

	val = LPC18XX_PWM_EVCTRL_MATCH(lpc18xx_pwm->period_event) |
	      LPC18XX_PWM_EVCTRL_COMB_MATCH;
	lpc18xx_pwm_ग_लिखोl(lpc18xx_pwm,
			   LPC18XX_PWM_EVCTRL(lpc18xx_pwm->period_event), val);

	lpc18xx_pwm_ग_लिखोl(lpc18xx_pwm, LPC18XX_PWM_LIMIT,
			   BIT(lpc18xx_pwm->period_event));

	ret = pwmchip_add(&lpc18xx_pwm->chip);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "pwmchip_add failed: %d\n", ret);
		जाओ disable_pwmclk;
	पूर्ण

	क्रम (i = 0; i < lpc18xx_pwm->chip.npwm; i++) अणु
		काष्ठा lpc18xx_pwm_data *data;

		pwm = &lpc18xx_pwm->chip.pwms[i];

		data = devm_kzalloc(lpc18xx_pwm->dev, माप(*data),
				    GFP_KERNEL);
		अगर (!data) अणु
			ret = -ENOMEM;
			जाओ हटाओ_pwmchip;
		पूर्ण

		pwm_set_chip_data(pwm, data);
	पूर्ण

	platक्रमm_set_drvdata(pdev, lpc18xx_pwm);

	val = lpc18xx_pwm_पढ़ोl(lpc18xx_pwm, LPC18XX_PWM_CTRL);
	val &= ~LPC18XX_PWM_BIसूची;
	val &= ~LPC18XX_PWM_CTRL_HALT;
	val &= ~LPC18XX_PWM_PRE_MASK;
	val |= LPC18XX_PWM_PRE(0);
	lpc18xx_pwm_ग_लिखोl(lpc18xx_pwm, LPC18XX_PWM_CTRL, val);

	वापस 0;

हटाओ_pwmchip:
	pwmchip_हटाओ(&lpc18xx_pwm->chip);
disable_pwmclk:
	clk_disable_unprepare(lpc18xx_pwm->pwm_clk);
	वापस ret;
पूर्ण

अटल पूर्णांक lpc18xx_pwm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा lpc18xx_pwm_chip *lpc18xx_pwm = platक्रमm_get_drvdata(pdev);
	u32 val;

	pwmchip_हटाओ(&lpc18xx_pwm->chip);

	val = lpc18xx_pwm_पढ़ोl(lpc18xx_pwm, LPC18XX_PWM_CTRL);
	lpc18xx_pwm_ग_लिखोl(lpc18xx_pwm, LPC18XX_PWM_CTRL,
			   val | LPC18XX_PWM_CTRL_HALT);

	clk_disable_unprepare(lpc18xx_pwm->pwm_clk);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver lpc18xx_pwm_driver = अणु
	.driver = अणु
		.name = "lpc18xx-sct-pwm",
		.of_match_table = lpc18xx_pwm_of_match,
	पूर्ण,
	.probe = lpc18xx_pwm_probe,
	.हटाओ = lpc18xx_pwm_हटाओ,
पूर्ण;
module_platक्रमm_driver(lpc18xx_pwm_driver);

MODULE_AUTHOR("Ariel D'Alessandro <ariel@vanguardiasur.com.ar>");
MODULE_DESCRIPTION("NXP LPC18xx PWM driver");
MODULE_LICENSE("GPL v2");
