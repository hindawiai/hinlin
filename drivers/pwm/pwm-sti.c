<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * PWM device driver क्रम ST SoCs
 *
 * Copyright (C) 2013-2016 STMicroelectronics (R&D) Limited
 *
 * Author: Ajit Pal Singh <ajitpal.singh@st.com>
 *         Lee Jones <lee.jones@linaro.org>
 */

#समावेश <linux/clk.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/math64.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pwm.h>
#समावेश <linux/regmap.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/समय.स>
#समावेश <linux/रुको.h>

#घोषणा PWM_OUT_VAL(x)	(0x00 + (4 * (x))) /* Device's Duty Cycle रेजिस्टर */
#घोषणा PWM_CPT_VAL(x)	(0x10 + (4 * (x))) /* Capture value */
#घोषणा PWM_CPT_EDGE(x) (0x30 + (4 * (x))) /* Edge to capture on */

#घोषणा STI_PWM_CTRL		0x50	/* Control/Config रेजिस्टर */
#घोषणा STI_INT_EN		0x54	/* Interrupt Enable/Disable रेजिस्टर */
#घोषणा STI_INT_STA		0x58	/* Interrupt Status रेजिस्टर */
#घोषणा PWM_INT_ACK		0x5c
#घोषणा PWM_PRESCALE_LOW_MASK	0x0f
#घोषणा PWM_PRESCALE_HIGH_MASK	0xf0
#घोषणा PWM_CPT_EDGE_MASK	0x03
#घोषणा PWM_INT_ACK_MASK	0x1ff

#घोषणा STI_MAX_CPT_DEVS	4
#घोषणा CPT_DC_MAX		0xff

/* Regfield IDs */
क्रमागत अणु
	/* Bits in PWM_CTRL*/
	PWMCLK_PRESCALE_LOW,
	PWMCLK_PRESCALE_HIGH,
	CPTCLK_PRESCALE,

	PWM_OUT_EN,
	PWM_CPT_EN,

	PWM_CPT_INT_EN,
	PWM_CPT_INT_STAT,

	/* Keep last */
	MAX_REGFIELDS
पूर्ण;

/*
 * Each capture input can be programmed to detect rising-edge, falling-edge,
 * either edge or neither egde.
 */
क्रमागत sti_cpt_edge अणु
	CPT_EDGE_DISABLED,
	CPT_EDGE_RISING,
	CPT_EDGE_FALLING,
	CPT_EDGE_BOTH,
पूर्ण;

काष्ठा sti_cpt_ddata अणु
	u32 snapshot[3];
	अचिन्हित पूर्णांक index;
	काष्ठा mutex lock;
	रुको_queue_head_t रुको;
पूर्ण;

काष्ठा sti_pwm_compat_data अणु
	स्थिर काष्ठा reg_field *reg_fields;
	अचिन्हित पूर्णांक pwm_num_devs;
	अचिन्हित पूर्णांक cpt_num_devs;
	अचिन्हित पूर्णांक max_pwm_cnt;
	अचिन्हित पूर्णांक max_prescale;
पूर्ण;

काष्ठा sti_pwm_chip अणु
	काष्ठा device *dev;
	काष्ठा clk *pwm_clk;
	काष्ठा clk *cpt_clk;
	काष्ठा regmap *regmap;
	काष्ठा sti_pwm_compat_data *cdata;
	काष्ठा regmap_field *prescale_low;
	काष्ठा regmap_field *prescale_high;
	काष्ठा regmap_field *pwm_out_en;
	काष्ठा regmap_field *pwm_cpt_en;
	काष्ठा regmap_field *pwm_cpt_पूर्णांक_en;
	काष्ठा regmap_field *pwm_cpt_पूर्णांक_stat;
	काष्ठा pwm_chip chip;
	काष्ठा pwm_device *cur;
	अचिन्हित दीर्घ configured;
	अचिन्हित पूर्णांक en_count;
	काष्ठा mutex sti_pwm_lock; /* To sync between enable/disable calls */
	व्योम __iomem *mmio;
पूर्ण;

अटल स्थिर काष्ठा reg_field sti_pwm_regfields[MAX_REGFIELDS] = अणु
	[PWMCLK_PRESCALE_LOW] = REG_FIELD(STI_PWM_CTRL, 0, 3),
	[PWMCLK_PRESCALE_HIGH] = REG_FIELD(STI_PWM_CTRL, 11, 14),
	[CPTCLK_PRESCALE] = REG_FIELD(STI_PWM_CTRL, 4, 8),
	[PWM_OUT_EN] = REG_FIELD(STI_PWM_CTRL, 9, 9),
	[PWM_CPT_EN] = REG_FIELD(STI_PWM_CTRL, 10, 10),
	[PWM_CPT_INT_EN] = REG_FIELD(STI_INT_EN, 1, 4),
	[PWM_CPT_INT_STAT] = REG_FIELD(STI_INT_STA, 1, 4),
पूर्ण;

अटल अंतरभूत काष्ठा sti_pwm_chip *to_sti_pwmchip(काष्ठा pwm_chip *chip)
अणु
	वापस container_of(chip, काष्ठा sti_pwm_chip, chip);
पूर्ण

/*
 * Calculate the prescaler value corresponding to the period.
 */
अटल पूर्णांक sti_pwm_get_prescale(काष्ठा sti_pwm_chip *pc, अचिन्हित दीर्घ period,
				अचिन्हित पूर्णांक *prescale)
अणु
	काष्ठा sti_pwm_compat_data *cdata = pc->cdata;
	अचिन्हित दीर्घ clk_rate;
	अचिन्हित दीर्घ value;
	अचिन्हित पूर्णांक ps;

	clk_rate = clk_get_rate(pc->pwm_clk);
	अगर (!clk_rate) अणु
		dev_err(pc->dev, "failed to get clock rate\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * prescale = ((period_ns * clk_rate) / (10^9 * (max_pwm_cnt + 1)) - 1
	 */
	value = NSEC_PER_SEC / clk_rate;
	value *= cdata->max_pwm_cnt + 1;

	अगर (period % value)
		वापस -EINVAL;

	ps  = period / value - 1;
	अगर (ps > cdata->max_prescale)
		वापस -EINVAL;

	*prescale = ps;

	वापस 0;
पूर्ण

/*
 * For STiH4xx PWM IP, the PWM period is fixed to 256 local घड़ी cycles. The
 * only way to change the period (apart from changing the PWM input घड़ी) is
 * to change the PWM घड़ी prescaler.
 *
 * The prescaler is of 8 bits, so 256 prescaler values and hence 256 possible
 * period values are supported (क्रम a particular घड़ी rate). The requested
 * period will be applied only अगर it matches one of these 256 values.
 */
अटल पूर्णांक sti_pwm_config(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm,
			  पूर्णांक duty_ns, पूर्णांक period_ns)
अणु
	काष्ठा sti_pwm_chip *pc = to_sti_pwmchip(chip);
	काष्ठा sti_pwm_compat_data *cdata = pc->cdata;
	अचिन्हित पूर्णांक ncfg, value, prescale = 0;
	काष्ठा pwm_device *cur = pc->cur;
	काष्ठा device *dev = pc->dev;
	bool period_same = false;
	पूर्णांक ret;

	ncfg = hweight_दीर्घ(pc->configured);
	अगर (ncfg)
		period_same = (period_ns == pwm_get_period(cur));

	/*
	 * Allow configuration changes अगर one of the following conditions
	 * satisfy.
	 * 1. No devices have been configured.
	 * 2. Only one device has been configured and the new request is क्रम
	 *    the same device.
	 * 3. Only one device has been configured and the new request is क्रम
	 *    a new device and period of the new device is same as the current
	 *    configured period.
	 * 4. More than one devices are configured and period of the new
	 *    requestis the same as the current period.
	 */
	अगर (!ncfg ||
	    ((ncfg == 1) && (pwm->hwpwm == cur->hwpwm)) ||
	    ((ncfg == 1) && (pwm->hwpwm != cur->hwpwm) && period_same) ||
	    ((ncfg > 1) && period_same)) अणु
		/* Enable घड़ी beक्रमe writing to PWM रेजिस्टरs. */
		ret = clk_enable(pc->pwm_clk);
		अगर (ret)
			वापस ret;

		ret = clk_enable(pc->cpt_clk);
		अगर (ret)
			वापस ret;

		अगर (!period_same) अणु
			ret = sti_pwm_get_prescale(pc, period_ns, &prescale);
			अगर (ret)
				जाओ clk_dis;

			value = prescale & PWM_PRESCALE_LOW_MASK;

			ret = regmap_field_ग_लिखो(pc->prescale_low, value);
			अगर (ret)
				जाओ clk_dis;

			value = (prescale & PWM_PRESCALE_HIGH_MASK) >> 4;

			ret = regmap_field_ग_लिखो(pc->prescale_high, value);
			अगर (ret)
				जाओ clk_dis;
		पूर्ण

		/*
		 * When PWMVal == 0, PWM pulse = 1 local घड़ी cycle.
		 * When PWMVal == max_pwm_count,
		 * PWM pulse = (max_pwm_count + 1) local cycles,
		 * that is continuous pulse: संकेत never goes low.
		 */
		value = cdata->max_pwm_cnt * duty_ns / period_ns;

		ret = regmap_ग_लिखो(pc->regmap, PWM_OUT_VAL(pwm->hwpwm), value);
		अगर (ret)
			जाओ clk_dis;

		ret = regmap_field_ग_लिखो(pc->pwm_cpt_पूर्णांक_en, 0);

		set_bit(pwm->hwpwm, &pc->configured);
		pc->cur = pwm;

		dev_dbg(dev, "prescale:%u, period:%i, duty:%i, value:%u\n",
			prescale, period_ns, duty_ns, value);
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

clk_dis:
	clk_disable(pc->pwm_clk);
	clk_disable(pc->cpt_clk);
	वापस ret;
पूर्ण

अटल पूर्णांक sti_pwm_enable(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm)
अणु
	काष्ठा sti_pwm_chip *pc = to_sti_pwmchip(chip);
	काष्ठा device *dev = pc->dev;
	पूर्णांक ret = 0;

	/*
	 * Since we have a common enable क्रम all PWM devices, करो not enable अगर
	 * alपढ़ोy enabled.
	 */
	mutex_lock(&pc->sti_pwm_lock);

	अगर (!pc->en_count) अणु
		ret = clk_enable(pc->pwm_clk);
		अगर (ret)
			जाओ out;

		ret = clk_enable(pc->cpt_clk);
		अगर (ret)
			जाओ out;

		ret = regmap_field_ग_लिखो(pc->pwm_out_en, 1);
		अगर (ret) अणु
			dev_err(dev, "failed to enable PWM device %u: %d\n",
				pwm->hwpwm, ret);
			जाओ out;
		पूर्ण
	पूर्ण

	pc->en_count++;

out:
	mutex_unlock(&pc->sti_pwm_lock);
	वापस ret;
पूर्ण

अटल व्योम sti_pwm_disable(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm)
अणु
	काष्ठा sti_pwm_chip *pc = to_sti_pwmchip(chip);

	mutex_lock(&pc->sti_pwm_lock);

	अगर (--pc->en_count) अणु
		mutex_unlock(&pc->sti_pwm_lock);
		वापस;
	पूर्ण

	regmap_field_ग_लिखो(pc->pwm_out_en, 0);

	clk_disable(pc->pwm_clk);
	clk_disable(pc->cpt_clk);

	mutex_unlock(&pc->sti_pwm_lock);
पूर्ण

अटल व्योम sti_pwm_मुक्त(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm)
अणु
	काष्ठा sti_pwm_chip *pc = to_sti_pwmchip(chip);

	clear_bit(pwm->hwpwm, &pc->configured);
पूर्ण

अटल पूर्णांक sti_pwm_capture(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm,
			   काष्ठा pwm_capture *result, अचिन्हित दीर्घ समयout)
अणु
	काष्ठा sti_pwm_chip *pc = to_sti_pwmchip(chip);
	काष्ठा sti_pwm_compat_data *cdata = pc->cdata;
	काष्ठा sti_cpt_ddata *ddata = pwm_get_chip_data(pwm);
	काष्ठा device *dev = pc->dev;
	अचिन्हित पूर्णांक effective_ticks;
	अचिन्हित दीर्घ दीर्घ high, low;
	पूर्णांक ret;

	अगर (pwm->hwpwm >= cdata->cpt_num_devs) अणु
		dev_err(dev, "device %u is not valid\n", pwm->hwpwm);
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&ddata->lock);
	ddata->index = 0;

	/* Prepare capture measurement */
	regmap_ग_लिखो(pc->regmap, PWM_CPT_EDGE(pwm->hwpwm), CPT_EDGE_RISING);
	regmap_field_ग_लिखो(pc->pwm_cpt_पूर्णांक_en, BIT(pwm->hwpwm));

	/* Enable capture */
	ret = regmap_field_ग_लिखो(pc->pwm_cpt_en, 1);
	अगर (ret) अणु
		dev_err(dev, "failed to enable PWM capture %u: %d\n",
			pwm->hwpwm, ret);
		जाओ out;
	पूर्ण

	ret = रुको_event_पूर्णांकerruptible_समयout(ddata->रुको, ddata->index > 1,
					       msecs_to_jअगरfies(समयout));

	regmap_ग_लिखो(pc->regmap, PWM_CPT_EDGE(pwm->hwpwm), CPT_EDGE_DISABLED);

	अगर (ret == -ERESTARTSYS)
		जाओ out;

	चयन (ddata->index) अणु
	हाल 0:
	हाल 1:
		/*
		 * Getting here could mean:
		 *  - input संकेत is स्थिरant of less than 1 Hz
		 *  - there is no input संकेत at all
		 *
		 * In such हाल the frequency is rounded करोwn to 0
		 */
		result->period = 0;
		result->duty_cycle = 0;

		अवरोध;

	हाल 2:
		/* We have everying we need */
		high = ddata->snapshot[1] - ddata->snapshot[0];
		low = ddata->snapshot[2] - ddata->snapshot[1];

		effective_ticks = clk_get_rate(pc->cpt_clk);

		result->period = (high + low) * NSEC_PER_SEC;
		result->period /= effective_ticks;

		result->duty_cycle = high * NSEC_PER_SEC;
		result->duty_cycle /= effective_ticks;

		अवरोध;

	शेष:
		dev_err(dev, "internal error\n");
		अवरोध;
	पूर्ण

out:
	/* Disable capture */
	regmap_field_ग_लिखो(pc->pwm_cpt_en, 0);

	mutex_unlock(&ddata->lock);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा pwm_ops sti_pwm_ops = अणु
	.capture = sti_pwm_capture,
	.config = sti_pwm_config,
	.enable = sti_pwm_enable,
	.disable = sti_pwm_disable,
	.मुक्त = sti_pwm_मुक्त,
	.owner = THIS_MODULE,
पूर्ण;

अटल irqवापस_t sti_pwm_पूर्णांकerrupt(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा sti_pwm_chip *pc = data;
	काष्ठा device *dev = pc->dev;
	काष्ठा sti_cpt_ddata *ddata;
	पूर्णांक devicक्रमागत;
	अचिन्हित पूर्णांक cpt_पूर्णांक_stat;
	अचिन्हित पूर्णांक reg;
	पूर्णांक ret = IRQ_NONE;

	ret = regmap_field_पढ़ो(pc->pwm_cpt_पूर्णांक_stat, &cpt_पूर्णांक_stat);
	अगर (ret)
		वापस ret;

	जबतक (cpt_पूर्णांक_stat) अणु
		devicक्रमागत = ffs(cpt_पूर्णांक_stat) - 1;

		ddata = pwm_get_chip_data(&pc->chip.pwms[devicक्रमागत]);

		/*
		 * Capture input:
		 *    _______                   _______
		 *   |       |                 |       |
		 * __|       |_________________|       |________
		 *   ^0      ^1                ^2
		 *
		 * Capture start by the first available rising edge. When a
		 * capture event occurs, capture value (CPT_VALx) is stored,
		 * index incremented, capture edge changed.
		 *
		 * After the capture, अगर the index > 1, we have collected the
		 * necessary data so we संकेत the thपढ़ो रुकोing क्रम it and
		 * disable the capture by setting capture edge to none
		 */

		regmap_पढ़ो(pc->regmap,
			    PWM_CPT_VAL(devicक्रमागत),
			    &ddata->snapshot[ddata->index]);

		चयन (ddata->index) अणु
		हाल 0:
		हाल 1:
			regmap_पढ़ो(pc->regmap, PWM_CPT_EDGE(devicक्रमागत), &reg);
			reg ^= PWM_CPT_EDGE_MASK;
			regmap_ग_लिखो(pc->regmap, PWM_CPT_EDGE(devicक्रमागत), reg);

			ddata->index++;
			अवरोध;

		हाल 2:
			regmap_ग_लिखो(pc->regmap,
				     PWM_CPT_EDGE(devicक्रमागत),
				     CPT_EDGE_DISABLED);
			wake_up(&ddata->रुको);
			अवरोध;

		शेष:
			dev_err(dev, "Internal error\n");
		पूर्ण

		cpt_पूर्णांक_stat &= ~BIT_MASK(devicक्रमागत);

		ret = IRQ_HANDLED;
	पूर्ण

	/* Just ACK everything */
	regmap_ग_लिखो(pc->regmap, PWM_INT_ACK, PWM_INT_ACK_MASK);

	वापस ret;
पूर्ण

अटल पूर्णांक sti_pwm_probe_dt(काष्ठा sti_pwm_chip *pc)
अणु
	काष्ठा device *dev = pc->dev;
	स्थिर काष्ठा reg_field *reg_fields;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा sti_pwm_compat_data *cdata = pc->cdata;
	u32 num_devs;
	पूर्णांक ret;

	ret = of_property_पढ़ो_u32(np, "st,pwm-num-chan", &num_devs);
	अगर (!ret)
		cdata->pwm_num_devs = num_devs;

	ret = of_property_पढ़ो_u32(np, "st,capture-num-chan", &num_devs);
	अगर (!ret)
		cdata->cpt_num_devs = num_devs;

	अगर (!cdata->pwm_num_devs && !cdata->cpt_num_devs) अणु
		dev_err(dev, "No channels configured\n");
		वापस -EINVAL;
	पूर्ण

	reg_fields = cdata->reg_fields;

	pc->prescale_low = devm_regmap_field_alloc(dev, pc->regmap,
					reg_fields[PWMCLK_PRESCALE_LOW]);
	अगर (IS_ERR(pc->prescale_low))
		वापस PTR_ERR(pc->prescale_low);

	pc->prescale_high = devm_regmap_field_alloc(dev, pc->regmap,
					reg_fields[PWMCLK_PRESCALE_HIGH]);
	अगर (IS_ERR(pc->prescale_high))
		वापस PTR_ERR(pc->prescale_high);

	pc->pwm_out_en = devm_regmap_field_alloc(dev, pc->regmap,
						 reg_fields[PWM_OUT_EN]);
	अगर (IS_ERR(pc->pwm_out_en))
		वापस PTR_ERR(pc->pwm_out_en);

	pc->pwm_cpt_en = devm_regmap_field_alloc(dev, pc->regmap,
						 reg_fields[PWM_CPT_EN]);
	अगर (IS_ERR(pc->pwm_cpt_en))
		वापस PTR_ERR(pc->pwm_cpt_en);

	pc->pwm_cpt_पूर्णांक_en = devm_regmap_field_alloc(dev, pc->regmap,
						reg_fields[PWM_CPT_INT_EN]);
	अगर (IS_ERR(pc->pwm_cpt_पूर्णांक_en))
		वापस PTR_ERR(pc->pwm_cpt_पूर्णांक_en);

	pc->pwm_cpt_पूर्णांक_stat = devm_regmap_field_alloc(dev, pc->regmap,
						reg_fields[PWM_CPT_INT_STAT]);
	अगर (PTR_ERR_OR_ZERO(pc->pwm_cpt_पूर्णांक_stat))
		वापस PTR_ERR(pc->pwm_cpt_पूर्णांक_stat);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा regmap_config sti_pwm_regmap_config = अणु
	.reg_bits = 32,
	.val_bits = 32,
	.reg_stride = 4,
पूर्ण;

अटल पूर्णांक sti_pwm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा sti_pwm_compat_data *cdata;
	काष्ठा sti_pwm_chip *pc;
	अचिन्हित पूर्णांक i;
	पूर्णांक irq, ret;

	pc = devm_kzalloc(dev, माप(*pc), GFP_KERNEL);
	अगर (!pc)
		वापस -ENOMEM;

	cdata = devm_kzalloc(dev, माप(*cdata), GFP_KERNEL);
	अगर (!cdata)
		वापस -ENOMEM;

	pc->mmio = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(pc->mmio))
		वापस PTR_ERR(pc->mmio);

	pc->regmap = devm_regmap_init_mmio(dev, pc->mmio,
					   &sti_pwm_regmap_config);
	अगर (IS_ERR(pc->regmap))
		वापस PTR_ERR(pc->regmap);

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	ret = devm_request_irq(&pdev->dev, irq, sti_pwm_पूर्णांकerrupt, 0,
			       pdev->name, pc);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Failed to request IRQ\n");
		वापस ret;
	पूर्ण

	/*
	 * Setup PWM data with शेष values: some values could be replaced
	 * with specअगरic ones provided from Device Tree.
	 */
	cdata->reg_fields = sti_pwm_regfields;
	cdata->max_prescale = 0xff;
	cdata->max_pwm_cnt = 255;
	cdata->pwm_num_devs = 0;
	cdata->cpt_num_devs = 0;

	pc->cdata = cdata;
	pc->dev = dev;
	pc->en_count = 0;
	mutex_init(&pc->sti_pwm_lock);

	ret = sti_pwm_probe_dt(pc);
	अगर (ret)
		वापस ret;

	अगर (cdata->pwm_num_devs) अणु
		pc->pwm_clk = of_clk_get_by_name(dev->of_node, "pwm");
		अगर (IS_ERR(pc->pwm_clk)) अणु
			dev_err(dev, "failed to get PWM clock\n");
			वापस PTR_ERR(pc->pwm_clk);
		पूर्ण

		ret = clk_prepare(pc->pwm_clk);
		अगर (ret) अणु
			dev_err(dev, "failed to prepare clock\n");
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (cdata->cpt_num_devs) अणु
		pc->cpt_clk = of_clk_get_by_name(dev->of_node, "capture");
		अगर (IS_ERR(pc->cpt_clk)) अणु
			dev_err(dev, "failed to get PWM capture clock\n");
			वापस PTR_ERR(pc->cpt_clk);
		पूर्ण

		ret = clk_prepare(pc->cpt_clk);
		अगर (ret) अणु
			dev_err(dev, "failed to prepare clock\n");
			वापस ret;
		पूर्ण
	पूर्ण

	pc->chip.dev = dev;
	pc->chip.ops = &sti_pwm_ops;
	pc->chip.npwm = pc->cdata->pwm_num_devs;

	ret = pwmchip_add(&pc->chip);
	अगर (ret < 0) अणु
		clk_unprepare(pc->pwm_clk);
		clk_unprepare(pc->cpt_clk);
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < cdata->cpt_num_devs; i++) अणु
		काष्ठा sti_cpt_ddata *ddata;

		ddata = devm_kzalloc(dev, माप(*ddata), GFP_KERNEL);
		अगर (!ddata)
			वापस -ENOMEM;

		init_रुकोqueue_head(&ddata->रुको);
		mutex_init(&ddata->lock);

		pwm_set_chip_data(&pc->chip.pwms[i], ddata);
	पूर्ण

	platक्रमm_set_drvdata(pdev, pc);

	वापस 0;
पूर्ण

अटल पूर्णांक sti_pwm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sti_pwm_chip *pc = platक्रमm_get_drvdata(pdev);

	pwmchip_हटाओ(&pc->chip);

	clk_unprepare(pc->pwm_clk);
	clk_unprepare(pc->cpt_clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id sti_pwm_of_match[] = अणु
	अणु .compatible = "st,sti-pwm", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sti_pwm_of_match);

अटल काष्ठा platक्रमm_driver sti_pwm_driver = अणु
	.driver = अणु
		.name = "sti-pwm",
		.of_match_table = sti_pwm_of_match,
	पूर्ण,
	.probe = sti_pwm_probe,
	.हटाओ = sti_pwm_हटाओ,
पूर्ण;
module_platक्रमm_driver(sti_pwm_driver);

MODULE_AUTHOR("Ajit Pal Singh <ajitpal.singh@st.com>");
MODULE_DESCRIPTION("STMicroelectronics ST PWM driver");
MODULE_LICENSE("GPL");
