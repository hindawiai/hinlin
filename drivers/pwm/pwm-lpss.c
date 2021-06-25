<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Intel Low Power Subप्रणाली PWM controller driver
 *
 * Copyright (C) 2014, Intel Corporation
 * Author: Mika Westerberg <mika.westerberg@linux.पूर्णांकel.com>
 * Author: Chew Kean Ho <kean.ho.chew@पूर्णांकel.com>
 * Author: Chang Rebecca Swee Fun <rebecca.swee.fun.chang@पूर्णांकel.com>
 * Author: Chew Chiau Ee <chiau.ee.chew@पूर्णांकel.com>
 * Author: Alan Cox <alan@linux.पूर्णांकel.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/समय.स>

#समावेश "pwm-lpss.h"

#घोषणा PWM				0x00000000
#घोषणा PWM_ENABLE			BIT(31)
#घोषणा PWM_SW_UPDATE			BIT(30)
#घोषणा PWM_BASE_UNIT_SHIFT		8
#घोषणा PWM_ON_TIME_DIV_MASK		0x000000ff

/* Size of each PWM रेजिस्टर space अगर multiple */
#घोषणा PWM_SIZE			0x400

अटल अंतरभूत काष्ठा pwm_lpss_chip *to_lpwm(काष्ठा pwm_chip *chip)
अणु
	वापस container_of(chip, काष्ठा pwm_lpss_chip, chip);
पूर्ण

अटल अंतरभूत u32 pwm_lpss_पढ़ो(स्थिर काष्ठा pwm_device *pwm)
अणु
	काष्ठा pwm_lpss_chip *lpwm = to_lpwm(pwm->chip);

	वापस पढ़ोl(lpwm->regs + pwm->hwpwm * PWM_SIZE + PWM);
पूर्ण

अटल अंतरभूत व्योम pwm_lpss_ग_लिखो(स्थिर काष्ठा pwm_device *pwm, u32 value)
अणु
	काष्ठा pwm_lpss_chip *lpwm = to_lpwm(pwm->chip);

	ग_लिखोl(value, lpwm->regs + pwm->hwpwm * PWM_SIZE + PWM);
पूर्ण

अटल पूर्णांक pwm_lpss_रुको_क्रम_update(काष्ठा pwm_device *pwm)
अणु
	काष्ठा pwm_lpss_chip *lpwm = to_lpwm(pwm->chip);
	स्थिर व्योम __iomem *addr = lpwm->regs + pwm->hwpwm * PWM_SIZE + PWM;
	स्थिर अचिन्हित पूर्णांक ms = 500 * USEC_PER_MSEC;
	u32 val;
	पूर्णांक err;

	/*
	 * PWM Configuration रेजिस्टर has SW_UPDATE bit that is set when a new
	 * configuration is written to the रेजिस्टर. The bit is स्वतःmatically
	 * cleared at the start of the next output cycle by the IP block.
	 *
	 * If one ग_लिखोs a new configuration to the रेजिस्टर जबतक it still has
	 * the bit enabled, PWM may मुक्तze. That is, जबतक one can still ग_लिखो
	 * to the रेजिस्टर, it won't have an effect. Thus, we try to sleep दीर्घ
	 * enough that the bit माला_लो cleared and make sure the bit is not
	 * enabled जबतक we update the configuration.
	 */
	err = पढ़ोl_poll_समयout(addr, val, !(val & PWM_SW_UPDATE), 40, ms);
	अगर (err)
		dev_err(pwm->chip->dev, "PWM_SW_UPDATE was not cleared\n");

	वापस err;
पूर्ण

अटल अंतरभूत पूर्णांक pwm_lpss_is_updating(काष्ठा pwm_device *pwm)
अणु
	अगर (pwm_lpss_पढ़ो(pwm) & PWM_SW_UPDATE) अणु
		dev_err(pwm->chip->dev, "PWM_SW_UPDATE is still set, skipping update\n");
		वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम pwm_lpss_prepare(काष्ठा pwm_lpss_chip *lpwm, काष्ठा pwm_device *pwm,
			     पूर्णांक duty_ns, पूर्णांक period_ns)
अणु
	अचिन्हित दीर्घ दीर्घ on_समय_भाग;
	अचिन्हित दीर्घ c = lpwm->info->clk_rate, base_unit_range;
	अचिन्हित दीर्घ दीर्घ base_unit, freq = NSEC_PER_SEC;
	u32 ctrl;

	करो_भाग(freq, period_ns);

	/*
	 * The equation is:
	 * base_unit = round(base_unit_range * freq / c)
	 */
	base_unit_range = BIT(lpwm->info->base_unit_bits);
	freq *= base_unit_range;

	base_unit = DIV_ROUND_CLOSEST_ULL(freq, c);
	/* base_unit must not be 0 and we also want to aव्योम overflowing it */
	base_unit = clamp_val(base_unit, 1, base_unit_range - 1);

	on_समय_भाग = 255ULL * duty_ns;
	करो_भाग(on_समय_भाग, period_ns);
	on_समय_भाग = 255ULL - on_समय_भाग;

	ctrl = pwm_lpss_पढ़ो(pwm);
	ctrl &= ~PWM_ON_TIME_DIV_MASK;
	ctrl &= ~((base_unit_range - 1) << PWM_BASE_UNIT_SHIFT);
	ctrl |= (u32) base_unit << PWM_BASE_UNIT_SHIFT;
	ctrl |= on_समय_भाग;

	pwm_lpss_ग_लिखो(pwm, ctrl);
	pwm_lpss_ग_लिखो(pwm, ctrl | PWM_SW_UPDATE);
पूर्ण

अटल अंतरभूत व्योम pwm_lpss_cond_enable(काष्ठा pwm_device *pwm, bool cond)
अणु
	अगर (cond)
		pwm_lpss_ग_लिखो(pwm, pwm_lpss_पढ़ो(pwm) | PWM_ENABLE);
पूर्ण

अटल पूर्णांक pwm_lpss_prepare_enable(काष्ठा pwm_lpss_chip *lpwm,
				   काष्ठा pwm_device *pwm,
				   स्थिर काष्ठा pwm_state *state)
अणु
	पूर्णांक ret;

	ret = pwm_lpss_is_updating(pwm);
	अगर (ret)
		वापस ret;

	pwm_lpss_prepare(lpwm, pwm, state->duty_cycle, state->period);
	pwm_lpss_cond_enable(pwm, lpwm->info->bypass == false);
	ret = pwm_lpss_रुको_क्रम_update(pwm);
	अगर (ret)
		वापस ret;

	pwm_lpss_cond_enable(pwm, lpwm->info->bypass == true);
	वापस 0;
पूर्ण

अटल पूर्णांक pwm_lpss_apply(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm,
			  स्थिर काष्ठा pwm_state *state)
अणु
	काष्ठा pwm_lpss_chip *lpwm = to_lpwm(chip);
	पूर्णांक ret = 0;

	अगर (state->enabled) अणु
		अगर (!pwm_is_enabled(pwm)) अणु
			pm_runसमय_get_sync(chip->dev);
			ret = pwm_lpss_prepare_enable(lpwm, pwm, state);
			अगर (ret)
				pm_runसमय_put(chip->dev);
		पूर्ण अन्यथा अणु
			ret = pwm_lpss_prepare_enable(lpwm, pwm, state);
		पूर्ण
	पूर्ण अन्यथा अगर (pwm_is_enabled(pwm)) अणु
		pwm_lpss_ग_लिखो(pwm, pwm_lpss_पढ़ो(pwm) & ~PWM_ENABLE);
		pm_runसमय_put(chip->dev);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम pwm_lpss_get_state(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm,
			       काष्ठा pwm_state *state)
अणु
	काष्ठा pwm_lpss_chip *lpwm = to_lpwm(chip);
	अचिन्हित दीर्घ base_unit_range;
	अचिन्हित दीर्घ दीर्घ base_unit, freq, on_समय_भाग;
	u32 ctrl;

	pm_runसमय_get_sync(chip->dev);

	base_unit_range = BIT(lpwm->info->base_unit_bits);

	ctrl = pwm_lpss_पढ़ो(pwm);
	on_समय_भाग = 255 - (ctrl & PWM_ON_TIME_DIV_MASK);
	base_unit = (ctrl >> PWM_BASE_UNIT_SHIFT) & (base_unit_range - 1);

	freq = base_unit * lpwm->info->clk_rate;
	करो_भाग(freq, base_unit_range);
	अगर (freq == 0)
		state->period = NSEC_PER_SEC;
	अन्यथा
		state->period = NSEC_PER_SEC / (अचिन्हित दीर्घ)freq;

	on_समय_भाग *= state->period;
	करो_भाग(on_समय_भाग, 255);
	state->duty_cycle = on_समय_भाग;

	state->polarity = PWM_POLARITY_NORMAL;
	state->enabled = !!(ctrl & PWM_ENABLE);

	pm_runसमय_put(chip->dev);
पूर्ण

अटल स्थिर काष्ठा pwm_ops pwm_lpss_ops = अणु
	.apply = pwm_lpss_apply,
	.get_state = pwm_lpss_get_state,
	.owner = THIS_MODULE,
पूर्ण;

काष्ठा pwm_lpss_chip *pwm_lpss_probe(काष्ठा device *dev, काष्ठा resource *r,
				     स्थिर काष्ठा pwm_lpss_boardinfo *info)
अणु
	काष्ठा pwm_lpss_chip *lpwm;
	अचिन्हित दीर्घ c;
	पूर्णांक i, ret;
	u32 ctrl;

	अगर (WARN_ON(info->npwm > MAX_PWMS))
		वापस ERR_PTR(-ENODEV);

	lpwm = devm_kzalloc(dev, माप(*lpwm), GFP_KERNEL);
	अगर (!lpwm)
		वापस ERR_PTR(-ENOMEM);

	lpwm->regs = devm_ioremap_resource(dev, r);
	अगर (IS_ERR(lpwm->regs))
		वापस ERR_CAST(lpwm->regs);

	lpwm->info = info;

	c = lpwm->info->clk_rate;
	अगर (!c)
		वापस ERR_PTR(-EINVAL);

	lpwm->chip.dev = dev;
	lpwm->chip.ops = &pwm_lpss_ops;
	lpwm->chip.npwm = info->npwm;

	ret = pwmchip_add(&lpwm->chip);
	अगर (ret) अणु
		dev_err(dev, "failed to add PWM chip: %d\n", ret);
		वापस ERR_PTR(ret);
	पूर्ण

	क्रम (i = 0; i < lpwm->info->npwm; i++) अणु
		ctrl = pwm_lpss_पढ़ो(&lpwm->chip.pwms[i]);
		अगर (ctrl & PWM_ENABLE)
			pm_runसमय_get(dev);
	पूर्ण

	वापस lpwm;
पूर्ण
EXPORT_SYMBOL_GPL(pwm_lpss_probe);

पूर्णांक pwm_lpss_हटाओ(काष्ठा pwm_lpss_chip *lpwm)
अणु
	वापस pwmchip_हटाओ(&lpwm->chip);
पूर्ण
EXPORT_SYMBOL_GPL(pwm_lpss_हटाओ);

MODULE_DESCRIPTION("PWM driver for Intel LPSS");
MODULE_AUTHOR("Mika Westerberg <mika.westerberg@linux.intel.com>");
MODULE_LICENSE("GPL v2");
