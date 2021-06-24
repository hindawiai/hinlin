<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/*
 * PWM controller driver क्रम Amlogic Meson SoCs.
 *
 * This PWM is only a set of Gates, Dividers and Counters:
 * PWM output is achieved by calculating a घड़ी that permits calculating
 * two periods (low and high). The counter then has to be set to चयन after
 * N cycles क्रम the first half period.
 * The hardware has no "polarity" setting. This driver reverses the period
 * cycles (the low length is inverted with the high length) क्रम
 * PWM_POLARITY_INVERSED. This means that .get_state cannot पढ़ो the polarity
 * from the hardware.
 * Setting the duty cycle will disable and re-enable the PWM output.
 * Disabling the PWM stops the output immediately (without रुकोing क्रम the
 * current period to complete first).
 *
 * The खुला S912 (GXM) datasheet contains some करोcumentation क्रम this PWM
 * controller starting on page 543:
 * https://dl.khadas.com/Hardware/VIM2/Datasheet/S912_Datasheet_V0.220170314खुलाversion-Wesion.pdf
 * An updated version of this IP block is found in S922X (G12B) SoCs. The
 * datasheet contains the description क्रम this IP block revision starting at
 * page 1084:
 * https://dn.odroid.com/S922X/ODROID-N2/Datasheet/S922X_Public_Datasheet_V0.2.pdf
 *
 * Copyright (c) 2016 BayLibre, SAS.
 * Author: Neil Armstrong <narmstrong@baylibre.com>
 * Copyright (C) 2014 Amlogic, Inc.
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/bits.h>
#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/math64.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pwm.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>

#घोषणा REG_PWM_A		0x0
#घोषणा REG_PWM_B		0x4
#घोषणा PWM_LOW_MASK		GENMASK(15, 0)
#घोषणा PWM_HIGH_MASK		GENMASK(31, 16)

#घोषणा REG_MISC_AB		0x8
#घोषणा MISC_B_CLK_EN		BIT(23)
#घोषणा MISC_A_CLK_EN		BIT(15)
#घोषणा MISC_CLK_DIV_MASK	0x7f
#घोषणा MISC_B_CLK_DIV_SHIFT	16
#घोषणा MISC_A_CLK_DIV_SHIFT	8
#घोषणा MISC_B_CLK_SEL_SHIFT	6
#घोषणा MISC_A_CLK_SEL_SHIFT	4
#घोषणा MISC_CLK_SEL_MASK	0x3
#घोषणा MISC_B_EN		BIT(1)
#घोषणा MISC_A_EN		BIT(0)

#घोषणा MESON_NUM_PWMS		2

अटल काष्ठा meson_pwm_channel_data अणु
	u8		reg_offset;
	u8		clk_sel_shअगरt;
	u8		clk_भाग_shअगरt;
	u32		clk_en_mask;
	u32		pwm_en_mask;
पूर्ण meson_pwm_per_channel_data[MESON_NUM_PWMS] = अणु
	अणु
		.reg_offset	= REG_PWM_A,
		.clk_sel_shअगरt	= MISC_A_CLK_SEL_SHIFT,
		.clk_भाग_shअगरt	= MISC_A_CLK_DIV_SHIFT,
		.clk_en_mask	= MISC_A_CLK_EN,
		.pwm_en_mask	= MISC_A_EN,
	पूर्ण,
	अणु
		.reg_offset	= REG_PWM_B,
		.clk_sel_shअगरt	= MISC_B_CLK_SEL_SHIFT,
		.clk_भाग_shअगरt	= MISC_B_CLK_DIV_SHIFT,
		.clk_en_mask	= MISC_B_CLK_EN,
		.pwm_en_mask	= MISC_B_EN,
	पूर्ण
पूर्ण;

काष्ठा meson_pwm_channel अणु
	अचिन्हित पूर्णांक hi;
	अचिन्हित पूर्णांक lo;
	u8 pre_भाग;

	काष्ठा clk *clk_parent;
	काष्ठा clk_mux mux;
	काष्ठा clk *clk;
पूर्ण;

काष्ठा meson_pwm_data अणु
	स्थिर अक्षर * स्थिर *parent_names;
	अचिन्हित पूर्णांक num_parents;
पूर्ण;

काष्ठा meson_pwm अणु
	काष्ठा pwm_chip chip;
	स्थिर काष्ठा meson_pwm_data *data;
	काष्ठा meson_pwm_channel channels[MESON_NUM_PWMS];
	व्योम __iomem *base;
	/*
	 * Protects रेजिस्टर (ग_लिखो) access to the REG_MISC_AB रेजिस्टर
	 * that is shared between the two PWMs.
	 */
	spinlock_t lock;
पूर्ण;

अटल अंतरभूत काष्ठा meson_pwm *to_meson_pwm(काष्ठा pwm_chip *chip)
अणु
	वापस container_of(chip, काष्ठा meson_pwm, chip);
पूर्ण

अटल पूर्णांक meson_pwm_request(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm)
अणु
	काष्ठा meson_pwm *meson = to_meson_pwm(chip);
	काष्ठा meson_pwm_channel *channel;
	काष्ठा device *dev = chip->dev;
	पूर्णांक err;

	channel = pwm_get_chip_data(pwm);
	अगर (channel)
		वापस 0;

	channel = &meson->channels[pwm->hwpwm];

	अगर (channel->clk_parent) अणु
		err = clk_set_parent(channel->clk, channel->clk_parent);
		अगर (err < 0) अणु
			dev_err(dev, "failed to set parent %s for %s: %d\n",
				__clk_get_name(channel->clk_parent),
				__clk_get_name(channel->clk), err);
			वापस err;
		पूर्ण
	पूर्ण

	err = clk_prepare_enable(channel->clk);
	अगर (err < 0) अणु
		dev_err(dev, "failed to enable clock %s: %d\n",
			__clk_get_name(channel->clk), err);
		वापस err;
	पूर्ण

	वापस pwm_set_chip_data(pwm, channel);
पूर्ण

अटल व्योम meson_pwm_मुक्त(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm)
अणु
	काष्ठा meson_pwm_channel *channel = pwm_get_chip_data(pwm);

	अगर (channel)
		clk_disable_unprepare(channel->clk);
पूर्ण

अटल पूर्णांक meson_pwm_calc(काष्ठा meson_pwm *meson, काष्ठा pwm_device *pwm,
			  स्थिर काष्ठा pwm_state *state)
अणु
	काष्ठा meson_pwm_channel *channel = pwm_get_chip_data(pwm);
	अचिन्हित पूर्णांक duty, period, pre_भाग, cnt, duty_cnt;
	अचिन्हित दीर्घ fin_freq;

	duty = state->duty_cycle;
	period = state->period;

	अगर (state->polarity == PWM_POLARITY_INVERSED)
		duty = period - duty;

	fin_freq = clk_get_rate(channel->clk);
	अगर (fin_freq == 0) अणु
		dev_err(meson->chip.dev, "invalid source clock frequency\n");
		वापस -EINVAL;
	पूर्ण

	dev_dbg(meson->chip.dev, "fin_freq: %lu Hz\n", fin_freq);

	pre_भाग = भाग64_u64(fin_freq * (u64)period, NSEC_PER_SEC * 0xffffLL);
	अगर (pre_भाग > MISC_CLK_DIV_MASK) अणु
		dev_err(meson->chip.dev, "unable to get period pre_div\n");
		वापस -EINVAL;
	पूर्ण

	cnt = भाग64_u64(fin_freq * (u64)period, NSEC_PER_SEC * (pre_भाग + 1));
	अगर (cnt > 0xffff) अणु
		dev_err(meson->chip.dev, "unable to get period cnt\n");
		वापस -EINVAL;
	पूर्ण

	dev_dbg(meson->chip.dev, "period=%u pre_div=%u cnt=%u\n", period,
		pre_भाग, cnt);

	अगर (duty == period) अणु
		channel->pre_भाग = pre_भाग;
		channel->hi = cnt;
		channel->lo = 0;
	पूर्ण अन्यथा अगर (duty == 0) अणु
		channel->pre_भाग = pre_भाग;
		channel->hi = 0;
		channel->lo = cnt;
	पूर्ण अन्यथा अणु
		/* Then check is we can have the duty with the same pre_भाग */
		duty_cnt = भाग64_u64(fin_freq * (u64)duty,
				     NSEC_PER_SEC * (pre_भाग + 1));
		अगर (duty_cnt > 0xffff) अणु
			dev_err(meson->chip.dev, "unable to get duty cycle\n");
			वापस -EINVAL;
		पूर्ण

		dev_dbg(meson->chip.dev, "duty=%u pre_div=%u duty_cnt=%u\n",
			duty, pre_भाग, duty_cnt);

		channel->pre_भाग = pre_भाग;
		channel->hi = duty_cnt;
		channel->lo = cnt - duty_cnt;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम meson_pwm_enable(काष्ठा meson_pwm *meson, काष्ठा pwm_device *pwm)
अणु
	काष्ठा meson_pwm_channel *channel = pwm_get_chip_data(pwm);
	काष्ठा meson_pwm_channel_data *channel_data;
	अचिन्हित दीर्घ flags;
	u32 value;

	channel_data = &meson_pwm_per_channel_data[pwm->hwpwm];

	spin_lock_irqsave(&meson->lock, flags);

	value = पढ़ोl(meson->base + REG_MISC_AB);
	value &= ~(MISC_CLK_DIV_MASK << channel_data->clk_भाग_shअगरt);
	value |= channel->pre_भाग << channel_data->clk_भाग_shअगरt;
	value |= channel_data->clk_en_mask;
	ग_लिखोl(value, meson->base + REG_MISC_AB);

	value = FIELD_PREP(PWM_HIGH_MASK, channel->hi) |
		FIELD_PREP(PWM_LOW_MASK, channel->lo);
	ग_लिखोl(value, meson->base + channel_data->reg_offset);

	value = पढ़ोl(meson->base + REG_MISC_AB);
	value |= channel_data->pwm_en_mask;
	ग_लिखोl(value, meson->base + REG_MISC_AB);

	spin_unlock_irqrestore(&meson->lock, flags);
पूर्ण

अटल व्योम meson_pwm_disable(काष्ठा meson_pwm *meson, काष्ठा pwm_device *pwm)
अणु
	अचिन्हित दीर्घ flags;
	u32 value;

	spin_lock_irqsave(&meson->lock, flags);

	value = पढ़ोl(meson->base + REG_MISC_AB);
	value &= ~meson_pwm_per_channel_data[pwm->hwpwm].pwm_en_mask;
	ग_लिखोl(value, meson->base + REG_MISC_AB);

	spin_unlock_irqrestore(&meson->lock, flags);
पूर्ण

अटल पूर्णांक meson_pwm_apply(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm,
			   स्थिर काष्ठा pwm_state *state)
अणु
	काष्ठा meson_pwm_channel *channel = pwm_get_chip_data(pwm);
	काष्ठा meson_pwm *meson = to_meson_pwm(chip);
	पूर्णांक err = 0;

	अगर (!state)
		वापस -EINVAL;

	अगर (!state->enabled) अणु
		अगर (state->polarity == PWM_POLARITY_INVERSED) अणु
			/*
			 * This IP block revision करोesn't have an "always high"
			 * setting which we can use क्रम "inverted disabled".
			 * Instead we achieve this using the same settings
			 * that we use a pre_भाग of 0 (to get the लघुest
			 * possible duration क्रम one "count") and
			 * "period == duty_cycle". This results in a संकेत
			 * which is LOW क्रम one "count", जबतक being HIGH क्रम
			 * the rest of the (so the संकेत is HIGH क्रम slightly
			 * less than 100% of the period, but this is the best
			 * we can achieve).
			 */
			channel->pre_भाग = 0;
			channel->hi = ~0;
			channel->lo = 0;

			meson_pwm_enable(meson, pwm);
		पूर्ण अन्यथा अणु
			meson_pwm_disable(meson, pwm);
		पूर्ण
	पूर्ण अन्यथा अणु
		err = meson_pwm_calc(meson, pwm, state);
		अगर (err < 0)
			वापस err;

		meson_pwm_enable(meson, pwm);
	पूर्ण

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक meson_pwm_cnt_to_ns(काष्ठा pwm_chip *chip,
					काष्ठा pwm_device *pwm, u32 cnt)
अणु
	काष्ठा meson_pwm *meson = to_meson_pwm(chip);
	काष्ठा meson_pwm_channel *channel;
	अचिन्हित दीर्घ fin_freq;
	u32 fin_ns;

	/* to_meson_pwm() can only be used after .get_state() is called */
	channel = &meson->channels[pwm->hwpwm];

	fin_freq = clk_get_rate(channel->clk);
	अगर (fin_freq == 0)
		वापस 0;

	fin_ns = भाग_u64(NSEC_PER_SEC, fin_freq);

	वापस cnt * fin_ns * (channel->pre_भाग + 1);
पूर्ण

अटल व्योम meson_pwm_get_state(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm,
				काष्ठा pwm_state *state)
अणु
	काष्ठा meson_pwm *meson = to_meson_pwm(chip);
	काष्ठा meson_pwm_channel_data *channel_data;
	काष्ठा meson_pwm_channel *channel;
	u32 value, पंचांगp;

	अगर (!state)
		वापस;

	channel = &meson->channels[pwm->hwpwm];
	channel_data = &meson_pwm_per_channel_data[pwm->hwpwm];

	value = पढ़ोl(meson->base + REG_MISC_AB);

	पंचांगp = channel_data->pwm_en_mask | channel_data->clk_en_mask;
	state->enabled = (value & पंचांगp) == पंचांगp;

	पंचांगp = value >> channel_data->clk_भाग_shअगरt;
	channel->pre_भाग = FIELD_GET(MISC_CLK_DIV_MASK, पंचांगp);

	value = पढ़ोl(meson->base + channel_data->reg_offset);

	channel->lo = FIELD_GET(PWM_LOW_MASK, value);
	channel->hi = FIELD_GET(PWM_HIGH_MASK, value);

	अगर (channel->lo == 0) अणु
		state->period = meson_pwm_cnt_to_ns(chip, pwm, channel->hi);
		state->duty_cycle = state->period;
	पूर्ण अन्यथा अगर (channel->lo >= channel->hi) अणु
		state->period = meson_pwm_cnt_to_ns(chip, pwm,
						    channel->lo + channel->hi);
		state->duty_cycle = meson_pwm_cnt_to_ns(chip, pwm,
							channel->hi);
	पूर्ण अन्यथा अणु
		state->period = 0;
		state->duty_cycle = 0;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा pwm_ops meson_pwm_ops = अणु
	.request = meson_pwm_request,
	.मुक्त = meson_pwm_मुक्त,
	.apply = meson_pwm_apply,
	.get_state = meson_pwm_get_state,
	.owner = THIS_MODULE,
पूर्ण;

अटल स्थिर अक्षर * स्थिर pwm_meson8b_parent_names[] = अणु
	"xtal", "vid_pll", "fclk_div4", "fclk_div3"
पूर्ण;

अटल स्थिर काष्ठा meson_pwm_data pwm_meson8b_data = अणु
	.parent_names = pwm_meson8b_parent_names,
	.num_parents = ARRAY_SIZE(pwm_meson8b_parent_names),
पूर्ण;

अटल स्थिर अक्षर * स्थिर pwm_gxbb_parent_names[] = अणु
	"xtal", "hdmi_pll", "fclk_div4", "fclk_div3"
पूर्ण;

अटल स्थिर काष्ठा meson_pwm_data pwm_gxbb_data = अणु
	.parent_names = pwm_gxbb_parent_names,
	.num_parents = ARRAY_SIZE(pwm_gxbb_parent_names),
पूर्ण;

/*
 * Only the 2 first inमाला_दो of the GXBB AO PWMs are valid
 * The last 2 are grounded
 */
अटल स्थिर अक्षर * स्थिर pwm_gxbb_ao_parent_names[] = अणु
	"xtal", "clk81"
पूर्ण;

अटल स्थिर काष्ठा meson_pwm_data pwm_gxbb_ao_data = अणु
	.parent_names = pwm_gxbb_ao_parent_names,
	.num_parents = ARRAY_SIZE(pwm_gxbb_ao_parent_names),
पूर्ण;

अटल स्थिर अक्षर * स्थिर pwm_axg_ee_parent_names[] = अणु
	"xtal", "fclk_div5", "fclk_div4", "fclk_div3"
पूर्ण;

अटल स्थिर काष्ठा meson_pwm_data pwm_axg_ee_data = अणु
	.parent_names = pwm_axg_ee_parent_names,
	.num_parents = ARRAY_SIZE(pwm_axg_ee_parent_names),
पूर्ण;

अटल स्थिर अक्षर * स्थिर pwm_axg_ao_parent_names[] = अणु
	"aoclk81", "xtal", "fclk_div4", "fclk_div5"
पूर्ण;

अटल स्थिर काष्ठा meson_pwm_data pwm_axg_ao_data = अणु
	.parent_names = pwm_axg_ao_parent_names,
	.num_parents = ARRAY_SIZE(pwm_axg_ao_parent_names),
पूर्ण;

अटल स्थिर अक्षर * स्थिर pwm_g12a_ao_ab_parent_names[] = अणु
	"xtal", "aoclk81", "fclk_div4", "fclk_div5"
पूर्ण;

अटल स्थिर काष्ठा meson_pwm_data pwm_g12a_ao_ab_data = अणु
	.parent_names = pwm_g12a_ao_ab_parent_names,
	.num_parents = ARRAY_SIZE(pwm_g12a_ao_ab_parent_names),
पूर्ण;

अटल स्थिर अक्षर * स्थिर pwm_g12a_ao_cd_parent_names[] = अणु
	"xtal", "aoclk81",
पूर्ण;

अटल स्थिर काष्ठा meson_pwm_data pwm_g12a_ao_cd_data = अणु
	.parent_names = pwm_g12a_ao_cd_parent_names,
	.num_parents = ARRAY_SIZE(pwm_g12a_ao_cd_parent_names),
पूर्ण;

अटल स्थिर अक्षर * स्थिर pwm_g12a_ee_parent_names[] = अणु
	"xtal", "hdmi_pll", "fclk_div4", "fclk_div3"
पूर्ण;

अटल स्थिर काष्ठा meson_pwm_data pwm_g12a_ee_data = अणु
	.parent_names = pwm_g12a_ee_parent_names,
	.num_parents = ARRAY_SIZE(pwm_g12a_ee_parent_names),
पूर्ण;

अटल स्थिर काष्ठा of_device_id meson_pwm_matches[] = अणु
	अणु
		.compatible = "amlogic,meson8b-pwm",
		.data = &pwm_meson8b_data
	पूर्ण,
	अणु
		.compatible = "amlogic,meson-gxbb-pwm",
		.data = &pwm_gxbb_data
	पूर्ण,
	अणु
		.compatible = "amlogic,meson-gxbb-ao-pwm",
		.data = &pwm_gxbb_ao_data
	पूर्ण,
	अणु
		.compatible = "amlogic,meson-axg-ee-pwm",
		.data = &pwm_axg_ee_data
	पूर्ण,
	अणु
		.compatible = "amlogic,meson-axg-ao-pwm",
		.data = &pwm_axg_ao_data
	पूर्ण,
	अणु
		.compatible = "amlogic,meson-g12a-ee-pwm",
		.data = &pwm_g12a_ee_data
	पूर्ण,
	अणु
		.compatible = "amlogic,meson-g12a-ao-pwm-ab",
		.data = &pwm_g12a_ao_ab_data
	पूर्ण,
	अणु
		.compatible = "amlogic,meson-g12a-ao-pwm-cd",
		.data = &pwm_g12a_ao_cd_data
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, meson_pwm_matches);

अटल पूर्णांक meson_pwm_init_channels(काष्ठा meson_pwm *meson)
अणु
	काष्ठा device *dev = meson->chip.dev;
	काष्ठा clk_init_data init;
	अचिन्हित पूर्णांक i;
	अक्षर name[255];
	पूर्णांक err;

	क्रम (i = 0; i < meson->chip.npwm; i++) अणु
		काष्ठा meson_pwm_channel *channel = &meson->channels[i];

		snम_लिखो(name, माप(name), "%s#mux%u", dev_name(dev), i);

		init.name = name;
		init.ops = &clk_mux_ops;
		init.flags = 0;
		init.parent_names = meson->data->parent_names;
		init.num_parents = meson->data->num_parents;

		channel->mux.reg = meson->base + REG_MISC_AB;
		channel->mux.shअगरt =
				meson_pwm_per_channel_data[i].clk_sel_shअगरt;
		channel->mux.mask = MISC_CLK_SEL_MASK;
		channel->mux.flags = 0;
		channel->mux.lock = &meson->lock;
		channel->mux.table = शून्य;
		channel->mux.hw.init = &init;

		channel->clk = devm_clk_रेजिस्टर(dev, &channel->mux.hw);
		अगर (IS_ERR(channel->clk)) अणु
			err = PTR_ERR(channel->clk);
			dev_err(dev, "failed to register %s: %d\n", name, err);
			वापस err;
		पूर्ण

		snम_लिखो(name, माप(name), "clkin%u", i);

		channel->clk_parent = devm_clk_get_optional(dev, name);
		अगर (IS_ERR(channel->clk_parent))
			वापस PTR_ERR(channel->clk_parent);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक meson_pwm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा meson_pwm *meson;
	पूर्णांक err;

	meson = devm_kzalloc(&pdev->dev, माप(*meson), GFP_KERNEL);
	अगर (!meson)
		वापस -ENOMEM;

	meson->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(meson->base))
		वापस PTR_ERR(meson->base);

	spin_lock_init(&meson->lock);
	meson->chip.dev = &pdev->dev;
	meson->chip.ops = &meson_pwm_ops;
	meson->chip.npwm = MESON_NUM_PWMS;
	meson->chip.of_xlate = of_pwm_xlate_with_flags;
	meson->chip.of_pwm_n_cells = 3;

	meson->data = of_device_get_match_data(&pdev->dev);

	err = meson_pwm_init_channels(meson);
	अगर (err < 0)
		वापस err;

	err = pwmchip_add(&meson->chip);
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "failed to register PWM chip: %d\n", err);
		वापस err;
	पूर्ण

	platक्रमm_set_drvdata(pdev, meson);

	वापस 0;
पूर्ण

अटल पूर्णांक meson_pwm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा meson_pwm *meson = platक्रमm_get_drvdata(pdev);

	वापस pwmchip_हटाओ(&meson->chip);
पूर्ण

अटल काष्ठा platक्रमm_driver meson_pwm_driver = अणु
	.driver = अणु
		.name = "meson-pwm",
		.of_match_table = meson_pwm_matches,
	पूर्ण,
	.probe = meson_pwm_probe,
	.हटाओ = meson_pwm_हटाओ,
पूर्ण;
module_platक्रमm_driver(meson_pwm_driver);

MODULE_DESCRIPTION("Amlogic Meson PWM Generator driver");
MODULE_AUTHOR("Neil Armstrong <narmstrong@baylibre.com>");
MODULE_LICENSE("Dual BSD/GPL");
