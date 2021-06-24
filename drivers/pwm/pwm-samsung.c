<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2007 Ben Dooks
 * Copyright (c) 2008 Simtec Electronics
 *     Ben Dooks <ben@simtec.co.uk>, <ben-linux@fluff.org>
 * Copyright (c) 2013 Tomasz Figa <tomasz.figa@gmail.com>
 * Copyright (c) 2017 Samsung Electronics Co., Ltd.
 *
 * PWM driver क्रम Samsung SoCs
 */

#समावेश <linux/bitops.h>
#समावेश <linux/clk.h>
#समावेश <linux/export.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pwm.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/समय.स>

/* For काष्ठा samsung_समयr_variant and samsung_pwm_lock. */
#समावेश <घड़ीsource/samsung_pwm.h>

#घोषणा REG_TCFG0			0x00
#घोषणा REG_TCFG1			0x04
#घोषणा REG_TCON			0x08

#घोषणा REG_TCNTB(chan)			(0x0c + ((chan) * 0xc))
#घोषणा REG_TCMPB(chan)			(0x10 + ((chan) * 0xc))

#घोषणा TCFG0_PRESCALER_MASK		0xff
#घोषणा TCFG0_PRESCALER1_SHIFT		8

#घोषणा TCFG1_MUX_MASK			0xf
#घोषणा TCFG1_SHIFT(chan)		(4 * (chan))

/*
 * Each channel occupies 4 bits in TCON रेजिस्टर, but there is a gap of 4
 * bits (one channel) after channel 0, so channels have dअगरferent numbering
 * when accessing TCON रेजिस्टर. See to_tcon_channel() function.
 *
 * In addition, the location of स्वतःreload bit क्रम channel 4 (TCON channel 5)
 * in its set of bits is 2 as opposed to 3 क्रम other channels.
 */
#घोषणा TCON_START(chan)		BIT(4 * (chan) + 0)
#घोषणा TCON_MANUALUPDATE(chan)		BIT(4 * (chan) + 1)
#घोषणा TCON_INVERT(chan)		BIT(4 * (chan) + 2)
#घोषणा _TCON_AUTORELOAD(chan)		BIT(4 * (chan) + 3)
#घोषणा _TCON_AUTORELOAD4(chan)		BIT(4 * (chan) + 2)
#घोषणा TCON_AUTORELOAD(chan)		\
	((chan < 5) ? _TCON_AUTORELOAD(chan) : _TCON_AUTORELOAD4(chan))

/**
 * काष्ठा samsung_pwm_channel - निजी data of PWM channel
 * @period_ns:	current period in nanoseconds programmed to the hardware
 * @duty_ns:	current duty समय in nanoseconds programmed to the hardware
 * @tin_ns:	समय of one समयr tick in nanoseconds with current समयr rate
 */
काष्ठा samsung_pwm_channel अणु
	u32 period_ns;
	u32 duty_ns;
	u32 tin_ns;
पूर्ण;

/**
 * काष्ठा samsung_pwm_chip - निजी data of PWM chip
 * @chip:		generic PWM chip
 * @variant:		local copy of hardware variant data
 * @inverter_mask:	inverter status क्रम all channels - one bit per channel
 * @disabled_mask:	disabled status क्रम all channels - one bit per channel
 * @base:		base address of mapped PWM रेजिस्टरs
 * @base_clk:		base घड़ी used to drive the समयrs
 * @tclk0:		बाह्यal घड़ी 0 (can be ERR_PTR अगर not present)
 * @tclk1:		बाह्यal घड़ी 1 (can be ERR_PTR अगर not present)
 */
काष्ठा samsung_pwm_chip अणु
	काष्ठा pwm_chip chip;
	काष्ठा samsung_pwm_variant variant;
	u8 inverter_mask;
	u8 disabled_mask;

	व्योम __iomem *base;
	काष्ठा clk *base_clk;
	काष्ठा clk *tclk0;
	काष्ठा clk *tclk1;
पूर्ण;

#अगर_अघोषित CONFIG_CLKSRC_SAMSUNG_PWM
/*
 * PWM block is shared between pwm-samsung and samsung_pwm_समयr drivers
 * and some रेजिस्टरs need access synchronization. If both drivers are
 * compiled in, the spinlock is defined in the घड़ीsource driver,
 * otherwise following definition is used.
 *
 * Currently we करो not need any more complex synchronization method
 * because all the supported SoCs contain only one instance of the PWM
 * IP. Should this change, both drivers will need to be modअगरied to
 * properly synchronize accesses to particular instances.
 */
अटल DEFINE_SPINLOCK(samsung_pwm_lock);
#पूर्ण_अगर

अटल अंतरभूत
काष्ठा samsung_pwm_chip *to_samsung_pwm_chip(काष्ठा pwm_chip *chip)
अणु
	वापस container_of(chip, काष्ठा samsung_pwm_chip, chip);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक to_tcon_channel(अचिन्हित पूर्णांक channel)
अणु
	/* TCON रेजिस्टर has a gap of 4 bits (1 channel) after channel 0 */
	वापस (channel == 0) ? 0 : (channel + 1);
पूर्ण

अटल व्योम pwm_samsung_set_भागisor(काष्ठा samsung_pwm_chip *pwm,
				    अचिन्हित पूर्णांक channel, u8 भागisor)
अणु
	u8 shअगरt = TCFG1_SHIFT(channel);
	अचिन्हित दीर्घ flags;
	u32 reg;
	u8 bits;

	bits = (fls(भागisor) - 1) - pwm->variant.भाग_base;

	spin_lock_irqsave(&samsung_pwm_lock, flags);

	reg = पढ़ोl(pwm->base + REG_TCFG1);
	reg &= ~(TCFG1_MUX_MASK << shअगरt);
	reg |= bits << shअगरt;
	ग_लिखोl(reg, pwm->base + REG_TCFG1);

	spin_unlock_irqrestore(&samsung_pwm_lock, flags);
पूर्ण

अटल पूर्णांक pwm_samsung_is_tभाग(काष्ठा samsung_pwm_chip *chip, अचिन्हित पूर्णांक chan)
अणु
	काष्ठा samsung_pwm_variant *variant = &chip->variant;
	u32 reg;

	reg = पढ़ोl(chip->base + REG_TCFG1);
	reg >>= TCFG1_SHIFT(chan);
	reg &= TCFG1_MUX_MASK;

	वापस (BIT(reg) & variant->tclk_mask) == 0;
पूर्ण

अटल अचिन्हित दीर्घ pwm_samsung_get_tin_rate(काष्ठा samsung_pwm_chip *chip,
					      अचिन्हित पूर्णांक chan)
अणु
	अचिन्हित दीर्घ rate;
	u32 reg;

	rate = clk_get_rate(chip->base_clk);

	reg = पढ़ोl(chip->base + REG_TCFG0);
	अगर (chan >= 2)
		reg >>= TCFG0_PRESCALER1_SHIFT;
	reg &= TCFG0_PRESCALER_MASK;

	वापस rate / (reg + 1);
पूर्ण

अटल अचिन्हित दीर्घ pwm_samsung_calc_tin(काष्ठा samsung_pwm_chip *chip,
					  अचिन्हित पूर्णांक chan, अचिन्हित दीर्घ freq)
अणु
	काष्ठा samsung_pwm_variant *variant = &chip->variant;
	अचिन्हित दीर्घ rate;
	काष्ठा clk *clk;
	u8 भाग;

	अगर (!pwm_samsung_is_tभाग(chip, chan)) अणु
		clk = (chan < 2) ? chip->tclk0 : chip->tclk1;
		अगर (!IS_ERR(clk)) अणु
			rate = clk_get_rate(clk);
			अगर (rate)
				वापस rate;
		पूर्ण

		dev_warn(chip->chip.dev,
			"tclk of PWM %d is inoperational, using tdiv\n", chan);
	पूर्ण

	rate = pwm_samsung_get_tin_rate(chip, chan);
	dev_dbg(chip->chip.dev, "tin parent at %lu\n", rate);

	/*
	 * Compare minimum PWM frequency that can be achieved with possible
	 * भागider settings and choose the lowest भागisor that can generate
	 * frequencies lower than requested.
	 */
	अगर (variant->bits < 32) अणु
		/* Only क्रम s3c24xx */
		क्रम (भाग = variant->भाग_base; भाग < 4; ++भाग)
			अगर ((rate >> (variant->bits + भाग)) < freq)
				अवरोध;
	पूर्ण अन्यथा अणु
		/*
		 * Other variants have enough counter bits to generate any
		 * requested rate, so no need to check higher भागisors.
		 */
		भाग = variant->भाग_base;
	पूर्ण

	pwm_samsung_set_भागisor(chip, chan, BIT(भाग));

	वापस rate >> भाग;
पूर्ण

अटल पूर्णांक pwm_samsung_request(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm)
अणु
	काष्ठा samsung_pwm_chip *our_chip = to_samsung_pwm_chip(chip);
	काष्ठा samsung_pwm_channel *our_chan;

	अगर (!(our_chip->variant.output_mask & BIT(pwm->hwpwm))) अणु
		dev_warn(chip->dev,
			"tried to request PWM channel %d without output\n",
			pwm->hwpwm);
		वापस -EINVAL;
	पूर्ण

	our_chan = kzalloc(माप(*our_chan), GFP_KERNEL);
	अगर (!our_chan)
		वापस -ENOMEM;

	pwm_set_chip_data(pwm, our_chan);

	वापस 0;
पूर्ण

अटल व्योम pwm_samsung_मुक्त(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm)
अणु
	kमुक्त(pwm_get_chip_data(pwm));
पूर्ण

अटल पूर्णांक pwm_samsung_enable(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm)
अणु
	काष्ठा samsung_pwm_chip *our_chip = to_samsung_pwm_chip(chip);
	अचिन्हित पूर्णांक tcon_chan = to_tcon_channel(pwm->hwpwm);
	अचिन्हित दीर्घ flags;
	u32 tcon;

	spin_lock_irqsave(&samsung_pwm_lock, flags);

	tcon = पढ़ोl(our_chip->base + REG_TCON);

	tcon &= ~TCON_START(tcon_chan);
	tcon |= TCON_MANUALUPDATE(tcon_chan);
	ग_लिखोl(tcon, our_chip->base + REG_TCON);

	tcon &= ~TCON_MANUALUPDATE(tcon_chan);
	tcon |= TCON_START(tcon_chan) | TCON_AUTORELOAD(tcon_chan);
	ग_लिखोl(tcon, our_chip->base + REG_TCON);

	our_chip->disabled_mask &= ~BIT(pwm->hwpwm);

	spin_unlock_irqrestore(&samsung_pwm_lock, flags);

	वापस 0;
पूर्ण

अटल व्योम pwm_samsung_disable(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm)
अणु
	काष्ठा samsung_pwm_chip *our_chip = to_samsung_pwm_chip(chip);
	अचिन्हित पूर्णांक tcon_chan = to_tcon_channel(pwm->hwpwm);
	अचिन्हित दीर्घ flags;
	u32 tcon;

	spin_lock_irqsave(&samsung_pwm_lock, flags);

	tcon = पढ़ोl(our_chip->base + REG_TCON);
	tcon &= ~TCON_AUTORELOAD(tcon_chan);
	ग_लिखोl(tcon, our_chip->base + REG_TCON);

	our_chip->disabled_mask |= BIT(pwm->hwpwm);

	spin_unlock_irqrestore(&samsung_pwm_lock, flags);
पूर्ण

अटल व्योम pwm_samsung_manual_update(काष्ठा samsung_pwm_chip *chip,
				      काष्ठा pwm_device *pwm)
अणु
	अचिन्हित पूर्णांक tcon_chan = to_tcon_channel(pwm->hwpwm);
	u32 tcon;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&samsung_pwm_lock, flags);

	tcon = पढ़ोl(chip->base + REG_TCON);
	tcon |= TCON_MANUALUPDATE(tcon_chan);
	ग_लिखोl(tcon, chip->base + REG_TCON);

	tcon &= ~TCON_MANUALUPDATE(tcon_chan);
	ग_लिखोl(tcon, chip->base + REG_TCON);

	spin_unlock_irqrestore(&samsung_pwm_lock, flags);
पूर्ण

अटल पूर्णांक __pwm_samsung_config(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm,
				पूर्णांक duty_ns, पूर्णांक period_ns, bool क्रमce_period)
अणु
	काष्ठा samsung_pwm_chip *our_chip = to_samsung_pwm_chip(chip);
	काष्ठा samsung_pwm_channel *chan = pwm_get_chip_data(pwm);
	u32 tin_ns = chan->tin_ns, tcnt, tcmp, oldtcmp;

	/*
	 * We currently aव्योम using 64bit arithmetic by using the
	 * fact that anything faster than 1Hz is easily representable
	 * by 32bits.
	 */
	अगर (period_ns > NSEC_PER_SEC)
		वापस -दुस्फल;

	tcnt = पढ़ोl(our_chip->base + REG_TCNTB(pwm->hwpwm));
	oldtcmp = पढ़ोl(our_chip->base + REG_TCMPB(pwm->hwpwm));

	/* We need tick count क्रम calculation, not last tick. */
	++tcnt;

	/* Check to see अगर we are changing the घड़ी rate of the PWM. */
	अगर (chan->period_ns != period_ns || क्रमce_period) अणु
		अचिन्हित दीर्घ tin_rate;
		u32 period;

		period = NSEC_PER_SEC / period_ns;

		dev_dbg(our_chip->chip.dev, "duty_ns=%d, period_ns=%d (%u)\n",
						duty_ns, period_ns, period);

		tin_rate = pwm_samsung_calc_tin(our_chip, pwm->hwpwm, period);

		dev_dbg(our_chip->chip.dev, "tin_rate=%lu\n", tin_rate);

		tin_ns = NSEC_PER_SEC / tin_rate;
		tcnt = period_ns / tin_ns;
	पूर्ण

	/* Period is too लघु. */
	अगर (tcnt <= 1)
		वापस -दुस्फल;

	/* Note that counters count करोwn. */
	tcmp = duty_ns / tin_ns;

	/* 0% duty is not available */
	अगर (!tcmp)
		++tcmp;

	tcmp = tcnt - tcmp;

	/* Decrement to get tick numbers, instead of tick counts. */
	--tcnt;
	/* -1UL will give 100% duty. */
	--tcmp;

	dev_dbg(our_chip->chip.dev,
				"tin_ns=%u, tcmp=%u/%u\n", tin_ns, tcmp, tcnt);

	/* Update PWM रेजिस्टरs. */
	ग_लिखोl(tcnt, our_chip->base + REG_TCNTB(pwm->hwpwm));
	ग_लिखोl(tcmp, our_chip->base + REG_TCMPB(pwm->hwpwm));

	/*
	 * In हाल the PWM is currently at 100% duty cycle, क्रमce a manual
	 * update to prevent the संकेत staying high अगर the PWM is disabled
	 * लघुly afer this update (beक्रमe it स्वतःreloaded the new values).
	 */
	अगर (oldtcmp == (u32) -1) अणु
		dev_dbg(our_chip->chip.dev, "Forcing manual update");
		pwm_samsung_manual_update(our_chip, pwm);
	पूर्ण

	chan->period_ns = period_ns;
	chan->tin_ns = tin_ns;
	chan->duty_ns = duty_ns;

	वापस 0;
पूर्ण

अटल पूर्णांक pwm_samsung_config(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm,
			      पूर्णांक duty_ns, पूर्णांक period_ns)
अणु
	वापस __pwm_samsung_config(chip, pwm, duty_ns, period_ns, false);
पूर्ण

अटल व्योम pwm_samsung_set_invert(काष्ठा samsung_pwm_chip *chip,
				   अचिन्हित पूर्णांक channel, bool invert)
अणु
	अचिन्हित पूर्णांक tcon_chan = to_tcon_channel(channel);
	अचिन्हित दीर्घ flags;
	u32 tcon;

	spin_lock_irqsave(&samsung_pwm_lock, flags);

	tcon = पढ़ोl(chip->base + REG_TCON);

	अगर (invert) अणु
		chip->inverter_mask |= BIT(channel);
		tcon |= TCON_INVERT(tcon_chan);
	पूर्ण अन्यथा अणु
		chip->inverter_mask &= ~BIT(channel);
		tcon &= ~TCON_INVERT(tcon_chan);
	पूर्ण

	ग_लिखोl(tcon, chip->base + REG_TCON);

	spin_unlock_irqrestore(&samsung_pwm_lock, flags);
पूर्ण

अटल पूर्णांक pwm_samsung_set_polarity(काष्ठा pwm_chip *chip,
				    काष्ठा pwm_device *pwm,
				    क्रमागत pwm_polarity polarity)
अणु
	काष्ठा samsung_pwm_chip *our_chip = to_samsung_pwm_chip(chip);
	bool invert = (polarity == PWM_POLARITY_NORMAL);

	/* Inverted means normal in the hardware. */
	pwm_samsung_set_invert(our_chip, pwm->hwpwm, invert);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pwm_ops pwm_samsung_ops = अणु
	.request	= pwm_samsung_request,
	.मुक्त		= pwm_samsung_मुक्त,
	.enable		= pwm_samsung_enable,
	.disable	= pwm_samsung_disable,
	.config		= pwm_samsung_config,
	.set_polarity	= pwm_samsung_set_polarity,
	.owner		= THIS_MODULE,
पूर्ण;

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा samsung_pwm_variant s3c24xx_variant = अणु
	.bits		= 16,
	.भाग_base	= 1,
	.has_tपूर्णांक_cstat	= false,
	.tclk_mask	= BIT(4),
पूर्ण;

अटल स्थिर काष्ठा samsung_pwm_variant s3c64xx_variant = अणु
	.bits		= 32,
	.भाग_base	= 0,
	.has_tपूर्णांक_cstat	= true,
	.tclk_mask	= BIT(7) | BIT(6) | BIT(5),
पूर्ण;

अटल स्थिर काष्ठा samsung_pwm_variant s5p64x0_variant = अणु
	.bits		= 32,
	.भाग_base	= 0,
	.has_tपूर्णांक_cstat	= true,
	.tclk_mask	= 0,
पूर्ण;

अटल स्थिर काष्ठा samsung_pwm_variant s5pc100_variant = अणु
	.bits		= 32,
	.भाग_base	= 0,
	.has_tपूर्णांक_cstat	= true,
	.tclk_mask	= BIT(5),
पूर्ण;

अटल स्थिर काष्ठा of_device_id samsung_pwm_matches[] = अणु
	अणु .compatible = "samsung,s3c2410-pwm", .data = &s3c24xx_variant पूर्ण,
	अणु .compatible = "samsung,s3c6400-pwm", .data = &s3c64xx_variant पूर्ण,
	अणु .compatible = "samsung,s5p6440-pwm", .data = &s5p64x0_variant पूर्ण,
	अणु .compatible = "samsung,s5pc100-pwm", .data = &s5pc100_variant पूर्ण,
	अणु .compatible = "samsung,exynos4210-pwm", .data = &s5p64x0_variant पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, samsung_pwm_matches);

अटल पूर्णांक pwm_samsung_parse_dt(काष्ठा samsung_pwm_chip *chip)
अणु
	काष्ठा device_node *np = chip->chip.dev->of_node;
	स्थिर काष्ठा of_device_id *match;
	काष्ठा property *prop;
	स्थिर __be32 *cur;
	u32 val;

	match = of_match_node(samsung_pwm_matches, np);
	अगर (!match)
		वापस -ENODEV;

	स_नकल(&chip->variant, match->data, माप(chip->variant));

	of_property_क्रम_each_u32(np, "samsung,pwm-outputs", prop, cur, val) अणु
		अगर (val >= SAMSUNG_PWM_NUM) अणु
			dev_err(chip->chip.dev,
				"%s: invalid channel index in samsung,pwm-outputs property\n",
								__func__);
			जारी;
		पूर्ण
		chip->variant.output_mask |= BIT(val);
	पूर्ण

	वापस 0;
पूर्ण
#अन्यथा
अटल पूर्णांक pwm_samsung_parse_dt(काष्ठा samsung_pwm_chip *chip)
अणु
	वापस -ENODEV;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक pwm_samsung_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा samsung_pwm_chip *chip;
	अचिन्हित पूर्णांक chan;
	पूर्णांक ret;

	chip = devm_kzalloc(&pdev->dev, माप(*chip), GFP_KERNEL);
	अगर (chip == शून्य)
		वापस -ENOMEM;

	chip->chip.dev = &pdev->dev;
	chip->chip.ops = &pwm_samsung_ops;
	chip->chip.npwm = SAMSUNG_PWM_NUM;
	chip->inverter_mask = BIT(SAMSUNG_PWM_NUM) - 1;

	अगर (IS_ENABLED(CONFIG_OF) && pdev->dev.of_node) अणु
		ret = pwm_samsung_parse_dt(chip);
		अगर (ret)
			वापस ret;

		chip->chip.of_xlate = of_pwm_xlate_with_flags;
		chip->chip.of_pwm_n_cells = 3;
	पूर्ण अन्यथा अणु
		अगर (!pdev->dev.platक्रमm_data) अणु
			dev_err(&pdev->dev, "no platform data specified\n");
			वापस -EINVAL;
		पूर्ण

		स_नकल(&chip->variant, pdev->dev.platक्रमm_data,
							माप(chip->variant));
	पूर्ण

	chip->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(chip->base))
		वापस PTR_ERR(chip->base);

	chip->base_clk = devm_clk_get(&pdev->dev, "timers");
	अगर (IS_ERR(chip->base_clk)) अणु
		dev_err(dev, "failed to get timer base clk\n");
		वापस PTR_ERR(chip->base_clk);
	पूर्ण

	ret = clk_prepare_enable(chip->base_clk);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to enable base clock\n");
		वापस ret;
	पूर्ण

	क्रम (chan = 0; chan < SAMSUNG_PWM_NUM; ++chan)
		अगर (chip->variant.output_mask & BIT(chan))
			pwm_samsung_set_invert(chip, chan, true);

	/* Following घड़ीs are optional. */
	chip->tclk0 = devm_clk_get(&pdev->dev, "pwm-tclk0");
	chip->tclk1 = devm_clk_get(&pdev->dev, "pwm-tclk1");

	platक्रमm_set_drvdata(pdev, chip);

	ret = pwmchip_add(&chip->chip);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to register PWM chip\n");
		clk_disable_unprepare(chip->base_clk);
		वापस ret;
	पूर्ण

	dev_dbg(dev, "base_clk at %lu, tclk0 at %lu, tclk1 at %lu\n",
		clk_get_rate(chip->base_clk),
		!IS_ERR(chip->tclk0) ? clk_get_rate(chip->tclk0) : 0,
		!IS_ERR(chip->tclk1) ? clk_get_rate(chip->tclk1) : 0);

	वापस 0;
पूर्ण

अटल पूर्णांक pwm_samsung_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा samsung_pwm_chip *chip = platक्रमm_get_drvdata(pdev);
	पूर्णांक ret;

	ret = pwmchip_हटाओ(&chip->chip);
	अगर (ret < 0)
		वापस ret;

	clk_disable_unprepare(chip->base_clk);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक pwm_samsung_resume(काष्ठा device *dev)
अणु
	काष्ठा samsung_pwm_chip *our_chip = dev_get_drvdata(dev);
	काष्ठा pwm_chip *chip = &our_chip->chip;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < SAMSUNG_PWM_NUM; i++) अणु
		काष्ठा pwm_device *pwm = &chip->pwms[i];
		काष्ठा samsung_pwm_channel *chan = pwm_get_chip_data(pwm);

		अगर (!chan)
			जारी;

		अगर (our_chip->variant.output_mask & BIT(i))
			pwm_samsung_set_invert(our_chip, i,
					our_chip->inverter_mask & BIT(i));

		अगर (chan->period_ns) अणु
			__pwm_samsung_config(chip, pwm, chan->duty_ns,
					     chan->period_ns, true);
			/* needed to make PWM disable work on Odroid-XU3 */
			pwm_samsung_manual_update(our_chip, pwm);
		पूर्ण

		अगर (our_chip->disabled_mask & BIT(i))
			pwm_samsung_disable(chip, pwm);
		अन्यथा
			pwm_samsung_enable(chip, pwm);
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(pwm_samsung_pm_ops, शून्य, pwm_samsung_resume);

अटल काष्ठा platक्रमm_driver pwm_samsung_driver = अणु
	.driver		= अणु
		.name	= "samsung-pwm",
		.pm	= &pwm_samsung_pm_ops,
		.of_match_table = of_match_ptr(samsung_pwm_matches),
	पूर्ण,
	.probe		= pwm_samsung_probe,
	.हटाओ		= pwm_samsung_हटाओ,
पूर्ण;
module_platक्रमm_driver(pwm_samsung_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Tomasz Figa <tomasz.figa@gmail.com>");
MODULE_ALIAS("platform:samsung-pwm");
