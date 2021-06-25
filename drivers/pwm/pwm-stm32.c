<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) STMicroelectronics 2016
 *
 * Author: Gerald Baeza <gerald.baeza@st.com>
 *
 * Inspired by समयr-sपंचांग32.c from Maxime Coquelin
 *             pwm-aपंचांगel.c from Bo Shen
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/mfd/sपंचांग32-समयrs.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pwm.h>

#घोषणा CCMR_CHANNEL_SHIFT 8
#घोषणा CCMR_CHANNEL_MASK  0xFF
#घोषणा MAX_BREAKINPUT 2

काष्ठा sपंचांग32_अवरोधinput अणु
	u32 index;
	u32 level;
	u32 filter;
पूर्ण;

काष्ठा sपंचांग32_pwm अणु
	काष्ठा pwm_chip chip;
	काष्ठा mutex lock; /* protect pwm config/enable */
	काष्ठा clk *clk;
	काष्ठा regmap *regmap;
	u32 max_arr;
	bool have_complementary_output;
	काष्ठा sपंचांग32_अवरोधinput अवरोधinमाला_दो[MAX_BREAKINPUT];
	अचिन्हित पूर्णांक num_अवरोधinमाला_दो;
	u32 capture[4] ____cacheline_aligned; /* DMA'able buffer */
पूर्ण;

अटल अंतरभूत काष्ठा sपंचांग32_pwm *to_sपंचांग32_pwm_dev(काष्ठा pwm_chip *chip)
अणु
	वापस container_of(chip, काष्ठा sपंचांग32_pwm, chip);
पूर्ण

अटल u32 active_channels(काष्ठा sपंचांग32_pwm *dev)
अणु
	u32 ccer;

	regmap_पढ़ो(dev->regmap, TIM_CCER, &ccer);

	वापस ccer & TIM_CCER_CCXE;
पूर्ण

अटल पूर्णांक ग_लिखो_ccrx(काष्ठा sपंचांग32_pwm *dev, पूर्णांक ch, u32 value)
अणु
	चयन (ch) अणु
	हाल 0:
		वापस regmap_ग_लिखो(dev->regmap, TIM_CCR1, value);
	हाल 1:
		वापस regmap_ग_लिखो(dev->regmap, TIM_CCR2, value);
	हाल 2:
		वापस regmap_ग_लिखो(dev->regmap, TIM_CCR3, value);
	हाल 3:
		वापस regmap_ग_लिखो(dev->regmap, TIM_CCR4, value);
	पूर्ण
	वापस -EINVAL;
पूर्ण

#घोषणा TIM_CCER_CC12P (TIM_CCER_CC1P | TIM_CCER_CC2P)
#घोषणा TIM_CCER_CC12E (TIM_CCER_CC1E | TIM_CCER_CC2E)
#घोषणा TIM_CCER_CC34P (TIM_CCER_CC3P | TIM_CCER_CC4P)
#घोषणा TIM_CCER_CC34E (TIM_CCER_CC3E | TIM_CCER_CC4E)

/*
 * Capture using PWM input mode:
 *                              ___          ___
 * TI[1, 2, 3 or 4]: ........._|   |________|
 *                             ^0  ^1       ^2
 *                              .   .        .
 *                              .   .        XXXXX
 *                              .   .   XXXXX     |
 *                              .  XXXXX     .    |
 *                            XXXXX .        .    |
 * COUNTER:        ______XXXXX  .   .        .    |_XXX
 *                 start^       .   .        .        ^stop
 *                      .       .   .        .
 *                      v       v   .        v
 *                                  v
 * CCR1/CCR3:       tx..........t0...........t2
 * CCR2/CCR4:       tx..............t1.........
 *
 * DMA burst transfer:          |            |
 *                              v            v
 * DMA buffer:                  अणु t0, tx पूर्ण   अणु t2, t1 पूर्ण
 * DMA करोne:                                 ^
 *
 * 0: IC1/3 snapchot on rising edge: counter value -> CCR1/CCR3
 *    + DMA transfer CCR[1/3] & CCR[2/4] values (t0, tx: करोesn't care)
 * 1: IC2/4 snapchot on falling edge: counter value -> CCR2/CCR4
 * 2: IC1/3 snapchot on rising edge: counter value -> CCR1/CCR3
 *    + DMA transfer CCR[1/3] & CCR[2/4] values (t2, t1)
 *
 * DMA करोne, compute:
 * - Period     = t2 - t0
 * - Duty cycle = t1 - t0
 */
अटल पूर्णांक sपंचांग32_pwm_raw_capture(काष्ठा sपंचांग32_pwm *priv, काष्ठा pwm_device *pwm,
				 अचिन्हित दीर्घ पंचांगo_ms, u32 *raw_prd,
				 u32 *raw_dty)
अणु
	काष्ठा device *parent = priv->chip.dev->parent;
	क्रमागत sपंचांग32_समयrs_dmas dma_id;
	u32 ccen, ccr;
	पूर्णांक ret;

	/* Ensure रेजिस्टरs have been updated, enable counter and capture */
	regmap_update_bits(priv->regmap, TIM_EGR, TIM_EGR_UG, TIM_EGR_UG);
	regmap_update_bits(priv->regmap, TIM_CR1, TIM_CR1_CEN, TIM_CR1_CEN);

	/* Use cc1 or cc3 DMA resp क्रम PWM input channels 1 & 2 or 3 & 4 */
	dma_id = pwm->hwpwm < 2 ? STM32_TIMERS_DMA_CH1 : STM32_TIMERS_DMA_CH3;
	ccen = pwm->hwpwm < 2 ? TIM_CCER_CC12E : TIM_CCER_CC34E;
	ccr = pwm->hwpwm < 2 ? TIM_CCR1 : TIM_CCR3;
	regmap_update_bits(priv->regmap, TIM_CCER, ccen, ccen);

	/*
	 * Timer DMA burst mode. Request 2 रेजिस्टरs, 2 bursts, to get both
	 * CCR1 & CCR2 (or CCR3 & CCR4) on each capture event.
	 * We'll get two capture snapchots: अणु CCR1, CCR2 पूर्ण, अणु CCR1, CCR2 पूर्ण
	 * or अणु CCR3, CCR4 पूर्ण, अणु CCR3, CCR4 पूर्ण
	 */
	ret = sपंचांग32_समयrs_dma_burst_पढ़ो(parent, priv->capture, dma_id, ccr, 2,
					  2, पंचांगo_ms);
	अगर (ret)
		जाओ stop;

	/* Period: t2 - t0 (take care of counter overflow) */
	अगर (priv->capture[0] <= priv->capture[2])
		*raw_prd = priv->capture[2] - priv->capture[0];
	अन्यथा
		*raw_prd = priv->max_arr - priv->capture[0] + priv->capture[2];

	/* Duty cycle capture requires at least two capture units */
	अगर (pwm->chip->npwm < 2)
		*raw_dty = 0;
	अन्यथा अगर (priv->capture[0] <= priv->capture[3])
		*raw_dty = priv->capture[3] - priv->capture[0];
	अन्यथा
		*raw_dty = priv->max_arr - priv->capture[0] + priv->capture[3];

	अगर (*raw_dty > *raw_prd) अणु
		/*
		 * Race beetween PWM input and DMA: it may happen
		 * falling edge triggers new capture on TI2/4 beक्रमe DMA
		 * had a chance to पढ़ो CCR2/4. It means capture[1]
		 * contains period + duty_cycle. So, subtract period.
		 */
		*raw_dty -= *raw_prd;
	पूर्ण

stop:
	regmap_update_bits(priv->regmap, TIM_CCER, ccen, 0);
	regmap_update_bits(priv->regmap, TIM_CR1, TIM_CR1_CEN, 0);

	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांग32_pwm_capture(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm,
			     काष्ठा pwm_capture *result, अचिन्हित दीर्घ पंचांगo_ms)
अणु
	काष्ठा sपंचांग32_pwm *priv = to_sपंचांग32_pwm_dev(chip);
	अचिन्हित दीर्घ दीर्घ prd, भाग, dty;
	अचिन्हित दीर्घ rate;
	अचिन्हित पूर्णांक psc = 0, icpsc, scale;
	u32 raw_prd = 0, raw_dty = 0;
	पूर्णांक ret = 0;

	mutex_lock(&priv->lock);

	अगर (active_channels(priv)) अणु
		ret = -EBUSY;
		जाओ unlock;
	पूर्ण

	ret = clk_enable(priv->clk);
	अगर (ret) अणु
		dev_err(priv->chip.dev, "failed to enable counter clock\n");
		जाओ unlock;
	पूर्ण

	rate = clk_get_rate(priv->clk);
	अगर (!rate) अणु
		ret = -EINVAL;
		जाओ clk_dis;
	पूर्ण

	/* prescaler: fit समयout winकरोw provided by upper layer */
	भाग = (अचिन्हित दीर्घ दीर्घ)rate * (अचिन्हित दीर्घ दीर्घ)पंचांगo_ms;
	करो_भाग(भाग, MSEC_PER_SEC);
	prd = भाग;
	जबतक ((भाग > priv->max_arr) && (psc < MAX_TIM_PSC)) अणु
		psc++;
		भाग = prd;
		करो_भाग(भाग, psc + 1);
	पूर्ण
	regmap_ग_लिखो(priv->regmap, TIM_ARR, priv->max_arr);
	regmap_ग_लिखो(priv->regmap, TIM_PSC, psc);

	/* Map TI1 or TI2 PWM input to IC1 & IC2 (or TI3/4 to IC3 & IC4) */
	regmap_update_bits(priv->regmap,
			   pwm->hwpwm < 2 ? TIM_CCMR1 : TIM_CCMR2,
			   TIM_CCMR_CC1S | TIM_CCMR_CC2S, pwm->hwpwm & 0x1 ?
			   TIM_CCMR_CC1S_TI2 | TIM_CCMR_CC2S_TI2 :
			   TIM_CCMR_CC1S_TI1 | TIM_CCMR_CC2S_TI1);

	/* Capture period on IC1/3 rising edge, duty cycle on IC2/4 falling. */
	regmap_update_bits(priv->regmap, TIM_CCER, pwm->hwpwm < 2 ?
			   TIM_CCER_CC12P : TIM_CCER_CC34P, pwm->hwpwm < 2 ?
			   TIM_CCER_CC2P : TIM_CCER_CC4P);

	ret = sपंचांग32_pwm_raw_capture(priv, pwm, पंचांगo_ms, &raw_prd, &raw_dty);
	अगर (ret)
		जाओ stop;

	/*
	 * Got a capture. Try to improve accuracy at high rates:
	 * - decrease counter घड़ी prescaler, scale up to max rate.
	 * - use input prescaler, capture once every /2 /4 or /8 edges.
	 */
	अगर (raw_prd) अणु
		u32 max_arr = priv->max_arr - 0x1000; /* arbitrary margin */

		scale = max_arr / min(max_arr, raw_prd);
	पूर्ण अन्यथा अणु
		scale = priv->max_arr; /* bellow resolution, use max scale */
	पूर्ण

	अगर (psc && scale > 1) अणु
		/* 2nd measure with new scale */
		psc /= scale;
		regmap_ग_लिखो(priv->regmap, TIM_PSC, psc);
		ret = sपंचांग32_pwm_raw_capture(priv, pwm, पंचांगo_ms, &raw_prd,
					    &raw_dty);
		अगर (ret)
			जाओ stop;
	पूर्ण

	/* Compute पूर्णांकermediate period not to exceed समयout at low rates */
	prd = (अचिन्हित दीर्घ दीर्घ)raw_prd * (psc + 1) * NSEC_PER_SEC;
	करो_भाग(prd, rate);

	क्रम (icpsc = 0; icpsc < MAX_TIM_ICPSC ; icpsc++) अणु
		/* input prescaler: also keep arbitrary margin */
		अगर (raw_prd >= (priv->max_arr - 0x1000) >> (icpsc + 1))
			अवरोध;
		अगर (prd >= (पंचांगo_ms * NSEC_PER_MSEC) >> (icpsc + 2))
			अवरोध;
	पूर्ण

	अगर (!icpsc)
		जाओ करोne;

	/* Last chance to improve period accuracy, using input prescaler */
	regmap_update_bits(priv->regmap,
			   pwm->hwpwm < 2 ? TIM_CCMR1 : TIM_CCMR2,
			   TIM_CCMR_IC1PSC | TIM_CCMR_IC2PSC,
			   FIELD_PREP(TIM_CCMR_IC1PSC, icpsc) |
			   FIELD_PREP(TIM_CCMR_IC2PSC, icpsc));

	ret = sपंचांग32_pwm_raw_capture(priv, pwm, पंचांगo_ms, &raw_prd, &raw_dty);
	अगर (ret)
		जाओ stop;

	अगर (raw_dty >= (raw_prd >> icpsc)) अणु
		/*
		 * We may fall here using input prescaler, when input
		 * capture starts on high side (beक्रमe falling edge).
		 * Example with icpsc to capture on each 4 events:
		 *
		 *       start   1st capture                     2nd capture
		 *         v     v                               v
		 *         ___   _____   _____   _____   _____   ____
		 * TI1..4     |__|    |__|    |__|    |__|    |__|
		 *            v  v    .  .    .  .    .       v  v
		 * icpsc1/3:  .  0    .  1    .  2    .  3    .  0
		 * icpsc2/4:  0       1       2       3       0
		 *            v  v                            v  v
		 * CCR1/3  ......t0..............................t2
		 * CCR2/4  ..t1..............................t1'...
		 *               .                            .  .
		 * Capture0:     .<----------------------------->.
		 * Capture1:     .<-------------------------->.  .
		 *               .                            .  .
		 * Period:       .<------>                    .  .
		 * Low side:                                  .<>.
		 *
		 * Result:
		 * - Period = Capture0 / icpsc
		 * - Duty = Period - Low side = Period - (Capture0 - Capture1)
		 */
		raw_dty = (raw_prd >> icpsc) - (raw_prd - raw_dty);
	पूर्ण

करोne:
	prd = (अचिन्हित दीर्घ दीर्घ)raw_prd * (psc + 1) * NSEC_PER_SEC;
	result->period = DIV_ROUND_UP_ULL(prd, rate << icpsc);
	dty = (अचिन्हित दीर्घ दीर्घ)raw_dty * (psc + 1) * NSEC_PER_SEC;
	result->duty_cycle = DIV_ROUND_UP_ULL(dty, rate);
stop:
	regmap_ग_लिखो(priv->regmap, TIM_CCER, 0);
	regmap_ग_लिखो(priv->regmap, pwm->hwpwm < 2 ? TIM_CCMR1 : TIM_CCMR2, 0);
	regmap_ग_लिखो(priv->regmap, TIM_PSC, 0);
clk_dis:
	clk_disable(priv->clk);
unlock:
	mutex_unlock(&priv->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांग32_pwm_config(काष्ठा sपंचांग32_pwm *priv, पूर्णांक ch,
			    पूर्णांक duty_ns, पूर्णांक period_ns)
अणु
	अचिन्हित दीर्घ दीर्घ prd, भाग, dty;
	अचिन्हित पूर्णांक prescaler = 0;
	u32 ccmr, mask, shअगरt;

	/* Period and prescaler values depends on घड़ी rate */
	भाग = (अचिन्हित दीर्घ दीर्घ)clk_get_rate(priv->clk) * period_ns;

	करो_भाग(भाग, NSEC_PER_SEC);
	prd = भाग;

	जबतक (भाग > priv->max_arr) अणु
		prescaler++;
		भाग = prd;
		करो_भाग(भाग, prescaler + 1);
	पूर्ण

	prd = भाग;

	अगर (prescaler > MAX_TIM_PSC)
		वापस -EINVAL;

	/*
	 * All channels share the same prescaler and counter so when two
	 * channels are active at the same समय we can't change them
	 */
	अगर (active_channels(priv) & ~(1 << ch * 4)) अणु
		u32 psc, arr;

		regmap_पढ़ो(priv->regmap, TIM_PSC, &psc);
		regmap_पढ़ो(priv->regmap, TIM_ARR, &arr);

		अगर ((psc != prescaler) || (arr != prd - 1))
			वापस -EBUSY;
	पूर्ण

	regmap_ग_लिखो(priv->regmap, TIM_PSC, prescaler);
	regmap_ग_लिखो(priv->regmap, TIM_ARR, prd - 1);
	regmap_update_bits(priv->regmap, TIM_CR1, TIM_CR1_ARPE, TIM_CR1_ARPE);

	/* Calculate the duty cycles */
	dty = prd * duty_ns;
	करो_भाग(dty, period_ns);

	ग_लिखो_ccrx(priv, ch, dty);

	/* Configure output mode */
	shअगरt = (ch & 0x1) * CCMR_CHANNEL_SHIFT;
	ccmr = (TIM_CCMR_PE | TIM_CCMR_M1) << shअगरt;
	mask = CCMR_CHANNEL_MASK << shअगरt;

	अगर (ch < 2)
		regmap_update_bits(priv->regmap, TIM_CCMR1, mask, ccmr);
	अन्यथा
		regmap_update_bits(priv->regmap, TIM_CCMR2, mask, ccmr);

	regmap_update_bits(priv->regmap, TIM_BDTR, TIM_BDTR_MOE, TIM_BDTR_MOE);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_pwm_set_polarity(काष्ठा sपंचांग32_pwm *priv, पूर्णांक ch,
				  क्रमागत pwm_polarity polarity)
अणु
	u32 mask;

	mask = TIM_CCER_CC1P << (ch * 4);
	अगर (priv->have_complementary_output)
		mask |= TIM_CCER_CC1NP << (ch * 4);

	regmap_update_bits(priv->regmap, TIM_CCER, mask,
			   polarity == PWM_POLARITY_NORMAL ? 0 : mask);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_pwm_enable(काष्ठा sपंचांग32_pwm *priv, पूर्णांक ch)
अणु
	u32 mask;
	पूर्णांक ret;

	ret = clk_enable(priv->clk);
	अगर (ret)
		वापस ret;

	/* Enable channel */
	mask = TIM_CCER_CC1E << (ch * 4);
	अगर (priv->have_complementary_output)
		mask |= TIM_CCER_CC1NE << (ch * 4);

	regmap_update_bits(priv->regmap, TIM_CCER, mask, mask);

	/* Make sure that रेजिस्टरs are updated */
	regmap_update_bits(priv->regmap, TIM_EGR, TIM_EGR_UG, TIM_EGR_UG);

	/* Enable controller */
	regmap_update_bits(priv->regmap, TIM_CR1, TIM_CR1_CEN, TIM_CR1_CEN);

	वापस 0;
पूर्ण

अटल व्योम sपंचांग32_pwm_disable(काष्ठा sपंचांग32_pwm *priv, पूर्णांक ch)
अणु
	u32 mask;

	/* Disable channel */
	mask = TIM_CCER_CC1E << (ch * 4);
	अगर (priv->have_complementary_output)
		mask |= TIM_CCER_CC1NE << (ch * 4);

	regmap_update_bits(priv->regmap, TIM_CCER, mask, 0);

	/* When all channels are disabled, we can disable the controller */
	अगर (!active_channels(priv))
		regmap_update_bits(priv->regmap, TIM_CR1, TIM_CR1_CEN, 0);

	clk_disable(priv->clk);
पूर्ण

अटल पूर्णांक sपंचांग32_pwm_apply(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm,
			   स्थिर काष्ठा pwm_state *state)
अणु
	bool enabled;
	काष्ठा sपंचांग32_pwm *priv = to_sपंचांग32_pwm_dev(chip);
	पूर्णांक ret;

	enabled = pwm->state.enabled;

	अगर (enabled && !state->enabled) अणु
		sपंचांग32_pwm_disable(priv, pwm->hwpwm);
		वापस 0;
	पूर्ण

	अगर (state->polarity != pwm->state.polarity)
		sपंचांग32_pwm_set_polarity(priv, pwm->hwpwm, state->polarity);

	ret = sपंचांग32_pwm_config(priv, pwm->hwpwm,
			       state->duty_cycle, state->period);
	अगर (ret)
		वापस ret;

	अगर (!enabled && state->enabled)
		ret = sपंचांग32_pwm_enable(priv, pwm->hwpwm);

	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांग32_pwm_apply_locked(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm,
				  स्थिर काष्ठा pwm_state *state)
अणु
	काष्ठा sपंचांग32_pwm *priv = to_sपंचांग32_pwm_dev(chip);
	पूर्णांक ret;

	/* protect common prescaler क्रम all active channels */
	mutex_lock(&priv->lock);
	ret = sपंचांग32_pwm_apply(chip, pwm, state);
	mutex_unlock(&priv->lock);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा pwm_ops sपंचांग32pwm_ops = अणु
	.owner = THIS_MODULE,
	.apply = sपंचांग32_pwm_apply_locked,
	.capture = IS_ENABLED(CONFIG_DMA_ENGINE) ? sपंचांग32_pwm_capture : शून्य,
पूर्ण;

अटल पूर्णांक sपंचांग32_pwm_set_अवरोधinput(काष्ठा sपंचांग32_pwm *priv,
				    स्थिर काष्ठा sपंचांग32_अवरोधinput *bi)
अणु
	u32 shअगरt = TIM_BDTR_BKF_SHIFT(bi->index);
	u32 bke = TIM_BDTR_BKE(bi->index);
	u32 bkp = TIM_BDTR_BKP(bi->index);
	u32 bkf = TIM_BDTR_BKF(bi->index);
	u32 mask = bkf | bkp | bke;
	u32 bdtr;

	bdtr = (bi->filter & TIM_BDTR_BKF_MASK) << shअगरt | bke;

	अगर (bi->level)
		bdtr |= bkp;

	regmap_update_bits(priv->regmap, TIM_BDTR, mask, bdtr);

	regmap_पढ़ो(priv->regmap, TIM_BDTR, &bdtr);

	वापस (bdtr & bke) ? 0 : -EINVAL;
पूर्ण

अटल पूर्णांक sपंचांग32_pwm_apply_अवरोधinमाला_दो(काष्ठा sपंचांग32_pwm *priv)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	क्रम (i = 0; i < priv->num_अवरोधinमाला_दो; i++) अणु
		ret = sपंचांग32_pwm_set_अवरोधinput(priv, &priv->अवरोधinमाला_दो[i]);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_pwm_probe_अवरोधinमाला_दो(काष्ठा sपंचांग32_pwm *priv,
				       काष्ठा device_node *np)
अणु
	पूर्णांक nb, ret, array_size;
	अचिन्हित पूर्णांक i;

	nb = of_property_count_elems_of_size(np, "st,breakinput",
					     माप(काष्ठा sपंचांग32_अवरोधinput));

	/*
	 * Because "st,breakinput" parameter is optional करो not make probe
	 * failed अगर it करोesn't exist.
	 */
	अगर (nb <= 0)
		वापस 0;

	अगर (nb > MAX_BREAKINPUT)
		वापस -EINVAL;

	priv->num_अवरोधinमाला_दो = nb;
	array_size = nb * माप(काष्ठा sपंचांग32_अवरोधinput) / माप(u32);
	ret = of_property_पढ़ो_u32_array(np, "st,breakinput",
					 (u32 *)priv->अवरोधinमाला_दो, array_size);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < priv->num_अवरोधinमाला_दो; i++) अणु
		अगर (priv->अवरोधinमाला_दो[i].index > 1 ||
		    priv->अवरोधinमाला_दो[i].level > 1 ||
		    priv->अवरोधinमाला_दो[i].filter > 15)
			वापस -EINVAL;
	पूर्ण

	वापस sपंचांग32_pwm_apply_अवरोधinमाला_दो(priv);
पूर्ण

अटल व्योम sपंचांग32_pwm_detect_complementary(काष्ठा sपंचांग32_pwm *priv)
अणु
	u32 ccer;

	/*
	 * If complementary bit करोesn't exist writing 1 will have no
	 * effect so we can detect it.
	 */
	regmap_update_bits(priv->regmap,
			   TIM_CCER, TIM_CCER_CC1NE, TIM_CCER_CC1NE);
	regmap_पढ़ो(priv->regmap, TIM_CCER, &ccer);
	regmap_update_bits(priv->regmap, TIM_CCER, TIM_CCER_CC1NE, 0);

	priv->have_complementary_output = (ccer != 0);
पूर्ण

अटल पूर्णांक sपंचांग32_pwm_detect_channels(काष्ठा sपंचांग32_pwm *priv)
अणु
	u32 ccer;
	पूर्णांक npwm = 0;

	/*
	 * If channels enable bits करोn't exist writing 1 will have no
	 * effect so we can detect and count them.
	 */
	regmap_update_bits(priv->regmap,
			   TIM_CCER, TIM_CCER_CCXE, TIM_CCER_CCXE);
	regmap_पढ़ो(priv->regmap, TIM_CCER, &ccer);
	regmap_update_bits(priv->regmap, TIM_CCER, TIM_CCER_CCXE, 0);

	अगर (ccer & TIM_CCER_CC1E)
		npwm++;

	अगर (ccer & TIM_CCER_CC2E)
		npwm++;

	अगर (ccer & TIM_CCER_CC3E)
		npwm++;

	अगर (ccer & TIM_CCER_CC4E)
		npwm++;

	वापस npwm;
पूर्ण

अटल पूर्णांक sपंचांग32_pwm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा sपंचांग32_समयrs *ddata = dev_get_drvdata(pdev->dev.parent);
	काष्ठा sपंचांग32_pwm *priv;
	पूर्णांक ret;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	mutex_init(&priv->lock);
	priv->regmap = ddata->regmap;
	priv->clk = ddata->clk;
	priv->max_arr = ddata->max_arr;
	priv->chip.of_xlate = of_pwm_xlate_with_flags;
	priv->chip.of_pwm_n_cells = 3;

	अगर (!priv->regmap || !priv->clk)
		वापस -EINVAL;

	ret = sपंचांग32_pwm_probe_अवरोधinमाला_दो(priv, np);
	अगर (ret)
		वापस ret;

	sपंचांग32_pwm_detect_complementary(priv);

	priv->chip.dev = dev;
	priv->chip.ops = &sपंचांग32pwm_ops;
	priv->chip.npwm = sपंचांग32_pwm_detect_channels(priv);

	ret = pwmchip_add(&priv->chip);
	अगर (ret < 0)
		वापस ret;

	platक्रमm_set_drvdata(pdev, priv);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_pwm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sपंचांग32_pwm *priv = platक्रमm_get_drvdata(pdev);
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < priv->chip.npwm; i++)
		pwm_disable(&priv->chip.pwms[i]);

	pwmchip_हटाओ(&priv->chip);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused sपंचांग32_pwm_suspend(काष्ठा device *dev)
अणु
	काष्ठा sपंचांग32_pwm *priv = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक i;
	u32 ccer, mask;

	/* Look क्रम active channels */
	ccer = active_channels(priv);

	क्रम (i = 0; i < priv->chip.npwm; i++) अणु
		mask = TIM_CCER_CC1E << (i * 4);
		अगर (ccer & mask) अणु
			dev_err(dev, "PWM %u still in use by consumer %s\n",
				i, priv->chip.pwms[i].label);
			वापस -EBUSY;
		पूर्ण
	पूर्ण

	वापस pinctrl_pm_select_sleep_state(dev);
पूर्ण

अटल पूर्णांक __maybe_unused sपंचांग32_pwm_resume(काष्ठा device *dev)
अणु
	काष्ठा sपंचांग32_pwm *priv = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = pinctrl_pm_select_शेष_state(dev);
	अगर (ret)
		वापस ret;

	/* restore अवरोधinput रेजिस्टरs that may have been lost in low घातer */
	वापस sपंचांग32_pwm_apply_अवरोधinमाला_दो(priv);
पूर्ण

अटल SIMPLE_DEV_PM_OPS(sपंचांग32_pwm_pm_ops, sपंचांग32_pwm_suspend, sपंचांग32_pwm_resume);

अटल स्थिर काष्ठा of_device_id sपंचांग32_pwm_of_match[] = अणु
	अणु .compatible = "st,stm32-pwm",	पूर्ण,
	अणु /* end node */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sपंचांग32_pwm_of_match);

अटल काष्ठा platक्रमm_driver sपंचांग32_pwm_driver = अणु
	.probe	= sपंचांग32_pwm_probe,
	.हटाओ	= sपंचांग32_pwm_हटाओ,
	.driver	= अणु
		.name = "stm32-pwm",
		.of_match_table = sपंचांग32_pwm_of_match,
		.pm = &sपंचांग32_pwm_pm_ops,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(sपंचांग32_pwm_driver);

MODULE_ALIAS("platform:stm32-pwm");
MODULE_DESCRIPTION("STMicroelectronics STM32 PWM driver");
MODULE_LICENSE("GPL v2");
