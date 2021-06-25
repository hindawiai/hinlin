<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Arizona core driver
 *
 * Copyright 2012 Wolfson Microelectronics plc
 *
 * Author: Mark Brown <broonie@खोलोsource.wolfsonmicro.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/slab.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/platक्रमm_device.h>

#समावेश <linux/mfd/arizona/core.h>
#समावेश <linux/mfd/arizona/रेजिस्टरs.h>

#समावेश "arizona.h"

अटल स्थिर अक्षर * स्थिर wm5102_core_supplies[] = अणु
	"AVDD",
	"DBVDD1",
पूर्ण;

पूर्णांक arizona_clk32k_enable(काष्ठा arizona *arizona)
अणु
	पूर्णांक ret = 0;

	mutex_lock(&arizona->clk_lock);

	arizona->clk32k_ref++;

	अगर (arizona->clk32k_ref == 1) अणु
		चयन (arizona->pdata.clk32k_src) अणु
		हाल ARIZONA_32KZ_MCLK1:
			ret = pm_runसमय_get_sync(arizona->dev);
			अगर (ret != 0)
				जाओ err_ref;
			ret = clk_prepare_enable(arizona->mclk[ARIZONA_MCLK1]);
			अगर (ret != 0) अणु
				pm_runसमय_put_sync(arizona->dev);
				जाओ err_ref;
			पूर्ण
			अवरोध;
		हाल ARIZONA_32KZ_MCLK2:
			ret = clk_prepare_enable(arizona->mclk[ARIZONA_MCLK2]);
			अगर (ret != 0)
				जाओ err_ref;
			अवरोध;
		पूर्ण

		ret = regmap_update_bits(arizona->regmap, ARIZONA_CLOCK_32K_1,
					 ARIZONA_CLK_32K_ENA,
					 ARIZONA_CLK_32K_ENA);
	पूर्ण

err_ref:
	अगर (ret != 0)
		arizona->clk32k_ref--;

	mutex_unlock(&arizona->clk_lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(arizona_clk32k_enable);

पूर्णांक arizona_clk32k_disable(काष्ठा arizona *arizona)
अणु
	mutex_lock(&arizona->clk_lock);

	WARN_ON(arizona->clk32k_ref <= 0);

	arizona->clk32k_ref--;

	अगर (arizona->clk32k_ref == 0) अणु
		regmap_update_bits(arizona->regmap, ARIZONA_CLOCK_32K_1,
				   ARIZONA_CLK_32K_ENA, 0);

		चयन (arizona->pdata.clk32k_src) अणु
		हाल ARIZONA_32KZ_MCLK1:
			pm_runसमय_put_sync(arizona->dev);
			clk_disable_unprepare(arizona->mclk[ARIZONA_MCLK1]);
			अवरोध;
		हाल ARIZONA_32KZ_MCLK2:
			clk_disable_unprepare(arizona->mclk[ARIZONA_MCLK2]);
			अवरोध;
		पूर्ण
	पूर्ण

	mutex_unlock(&arizona->clk_lock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(arizona_clk32k_disable);

अटल irqवापस_t arizona_clkgen_err(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा arizona *arizona = data;

	dev_err(arizona->dev, "CLKGEN error\n");

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t arizona_underघड़ीed(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा arizona *arizona = data;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(arizona->regmap, ARIZONA_INTERRUPT_RAW_STATUS_8,
			  &val);
	अगर (ret != 0) अणु
		dev_err(arizona->dev, "Failed to read underclock status: %d\n",
			ret);
		वापस IRQ_NONE;
	पूर्ण

	अगर (val & ARIZONA_AIF3_UNDERCLOCKED_STS)
		dev_err(arizona->dev, "AIF3 underclocked\n");
	अगर (val & ARIZONA_AIF2_UNDERCLOCKED_STS)
		dev_err(arizona->dev, "AIF2 underclocked\n");
	अगर (val & ARIZONA_AIF1_UNDERCLOCKED_STS)
		dev_err(arizona->dev, "AIF1 underclocked\n");
	अगर (val & ARIZONA_ISRC3_UNDERCLOCKED_STS)
		dev_err(arizona->dev, "ISRC3 underclocked\n");
	अगर (val & ARIZONA_ISRC2_UNDERCLOCKED_STS)
		dev_err(arizona->dev, "ISRC2 underclocked\n");
	अगर (val & ARIZONA_ISRC1_UNDERCLOCKED_STS)
		dev_err(arizona->dev, "ISRC1 underclocked\n");
	अगर (val & ARIZONA_FX_UNDERCLOCKED_STS)
		dev_err(arizona->dev, "FX underclocked\n");
	अगर (val & ARIZONA_ASRC_UNDERCLOCKED_STS)
		dev_err(arizona->dev, "ASRC underclocked\n");
	अगर (val & ARIZONA_DAC_UNDERCLOCKED_STS)
		dev_err(arizona->dev, "DAC underclocked\n");
	अगर (val & ARIZONA_ADC_UNDERCLOCKED_STS)
		dev_err(arizona->dev, "ADC underclocked\n");
	अगर (val & ARIZONA_MIXER_UNDERCLOCKED_STS)
		dev_err(arizona->dev, "Mixer dropped sample\n");

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t arizona_overघड़ीed(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा arizona *arizona = data;
	अचिन्हित पूर्णांक val[3];
	पूर्णांक ret;

	ret = regmap_bulk_पढ़ो(arizona->regmap, ARIZONA_INTERRUPT_RAW_STATUS_6,
			       &val[0], 3);
	अगर (ret != 0) अणु
		dev_err(arizona->dev, "Failed to read overclock status: %d\n",
			ret);
		वापस IRQ_NONE;
	पूर्ण

	चयन (arizona->type) अणु
	हाल WM8998:
	हाल WM1814:
		/* Some bits are shअगरted on WM8998,
		 * rearrange to match the standard bit layout
		 */
		val[0] = ((val[0] & 0x60e0) >> 1) |
			 ((val[0] & 0x1e00) >> 2) |
			 (val[0] & 0x000f);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (val[0] & ARIZONA_PWM_OVERCLOCKED_STS)
		dev_err(arizona->dev, "PWM overclocked\n");
	अगर (val[0] & ARIZONA_FX_CORE_OVERCLOCKED_STS)
		dev_err(arizona->dev, "FX core overclocked\n");
	अगर (val[0] & ARIZONA_DAC_SYS_OVERCLOCKED_STS)
		dev_err(arizona->dev, "DAC SYS overclocked\n");
	अगर (val[0] & ARIZONA_DAC_WARP_OVERCLOCKED_STS)
		dev_err(arizona->dev, "DAC WARP overclocked\n");
	अगर (val[0] & ARIZONA_ADC_OVERCLOCKED_STS)
		dev_err(arizona->dev, "ADC overclocked\n");
	अगर (val[0] & ARIZONA_MIXER_OVERCLOCKED_STS)
		dev_err(arizona->dev, "Mixer overclocked\n");
	अगर (val[0] & ARIZONA_AIF3_SYNC_OVERCLOCKED_STS)
		dev_err(arizona->dev, "AIF3 overclocked\n");
	अगर (val[0] & ARIZONA_AIF2_SYNC_OVERCLOCKED_STS)
		dev_err(arizona->dev, "AIF2 overclocked\n");
	अगर (val[0] & ARIZONA_AIF1_SYNC_OVERCLOCKED_STS)
		dev_err(arizona->dev, "AIF1 overclocked\n");
	अगर (val[0] & ARIZONA_PAD_CTRL_OVERCLOCKED_STS)
		dev_err(arizona->dev, "Pad control overclocked\n");

	अगर (val[1] & ARIZONA_SLIMBUS_SUBSYS_OVERCLOCKED_STS)
		dev_err(arizona->dev, "Slimbus subsystem overclocked\n");
	अगर (val[1] & ARIZONA_SLIMBUS_ASYNC_OVERCLOCKED_STS)
		dev_err(arizona->dev, "Slimbus async overclocked\n");
	अगर (val[1] & ARIZONA_SLIMBUS_SYNC_OVERCLOCKED_STS)
		dev_err(arizona->dev, "Slimbus sync overclocked\n");
	अगर (val[1] & ARIZONA_ASRC_ASYNC_SYS_OVERCLOCKED_STS)
		dev_err(arizona->dev, "ASRC async system overclocked\n");
	अगर (val[1] & ARIZONA_ASRC_ASYNC_WARP_OVERCLOCKED_STS)
		dev_err(arizona->dev, "ASRC async WARP overclocked\n");
	अगर (val[1] & ARIZONA_ASRC_SYNC_SYS_OVERCLOCKED_STS)
		dev_err(arizona->dev, "ASRC sync system overclocked\n");
	अगर (val[1] & ARIZONA_ASRC_SYNC_WARP_OVERCLOCKED_STS)
		dev_err(arizona->dev, "ASRC sync WARP overclocked\n");
	अगर (val[1] & ARIZONA_ADSP2_1_OVERCLOCKED_STS)
		dev_err(arizona->dev, "DSP1 overclocked\n");
	अगर (val[1] & ARIZONA_ISRC3_OVERCLOCKED_STS)
		dev_err(arizona->dev, "ISRC3 overclocked\n");
	अगर (val[1] & ARIZONA_ISRC2_OVERCLOCKED_STS)
		dev_err(arizona->dev, "ISRC2 overclocked\n");
	अगर (val[1] & ARIZONA_ISRC1_OVERCLOCKED_STS)
		dev_err(arizona->dev, "ISRC1 overclocked\n");

	अगर (val[2] & ARIZONA_SPDIF_OVERCLOCKED_STS)
		dev_err(arizona->dev, "SPDIF overclocked\n");

	वापस IRQ_HANDLED;
पूर्ण

#घोषणा ARIZONA_REG_POLL_DELAY_US 7500

अटल अंतरभूत bool arizona_poll_reg_delay(kसमय_प्रकार समयout)
अणु
	अगर (kसमय_compare(kसमय_get(), समयout) > 0)
		वापस false;

	usleep_range(ARIZONA_REG_POLL_DELAY_US / 2, ARIZONA_REG_POLL_DELAY_US);

	वापस true;
पूर्ण

अटल पूर्णांक arizona_poll_reg(काष्ठा arizona *arizona,
			    पूर्णांक समयout_ms, अचिन्हित पूर्णांक reg,
			    अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक target)
अणु
	kसमय_प्रकार समयout = kसमय_add_us(kसमय_get(), समयout_ms * USEC_PER_MSEC);
	अचिन्हित पूर्णांक val = 0;
	पूर्णांक ret;

	करो अणु
		ret = regmap_पढ़ो(arizona->regmap, reg, &val);

		अगर ((val & mask) == target)
			वापस 0;
	पूर्ण जबतक (arizona_poll_reg_delay(समयout));

	अगर (ret) अणु
		dev_err(arizona->dev, "Failed polling reg 0x%x: %d\n",
			reg, ret);
		वापस ret;
	पूर्ण

	dev_err(arizona->dev, "Polling reg 0x%x timed out: %x\n", reg, val);
	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक arizona_रुको_क्रम_boot(काष्ठा arizona *arizona)
अणु
	पूर्णांक ret;

	/*
	 * We can't use an पूर्णांकerrupt as we need to runसमय resume to करो so,
	 * we won't race with the interrupt handler as it'll be blocked on
	 * runसमय resume.
	 */
	ret = arizona_poll_reg(arizona, 30, ARIZONA_INTERRUPT_RAW_STATUS_5,
			       ARIZONA_BOOT_DONE_STS, ARIZONA_BOOT_DONE_STS);

	अगर (!ret)
		regmap_ग_लिखो(arizona->regmap, ARIZONA_INTERRUPT_STATUS_5,
			     ARIZONA_BOOT_DONE_STS);

	pm_runसमय_mark_last_busy(arizona->dev);

	वापस ret;
पूर्ण

अटल अंतरभूत व्योम arizona_enable_reset(काष्ठा arizona *arizona)
अणु
	अगर (arizona->pdata.reset)
		gpiod_set_raw_value_cansleep(arizona->pdata.reset, 0);
पूर्ण

अटल व्योम arizona_disable_reset(काष्ठा arizona *arizona)
अणु
	अगर (arizona->pdata.reset) अणु
		चयन (arizona->type) अणु
		हाल WM5110:
		हाल WM8280:
			/* Meet requirements क्रम minimum reset duration */
			usleep_range(5000, 10000);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		gpiod_set_raw_value_cansleep(arizona->pdata.reset, 1);
		usleep_range(1000, 5000);
	पूर्ण
पूर्ण

काष्ठा arizona_sysclk_state अणु
	अचिन्हित पूर्णांक fll;
	अचिन्हित पूर्णांक sysclk;
पूर्ण;

अटल पूर्णांक arizona_enable_मुक्तrun_sysclk(काष्ठा arizona *arizona,
					 काष्ठा arizona_sysclk_state *state)
अणु
	पूर्णांक ret, err;

	/* Cache existing FLL and SYSCLK settings */
	ret = regmap_पढ़ो(arizona->regmap, ARIZONA_FLL1_CONTROL_1, &state->fll);
	अगर (ret) अणु
		dev_err(arizona->dev, "Failed to cache FLL settings: %d\n",
			ret);
		वापस ret;
	पूर्ण
	ret = regmap_पढ़ो(arizona->regmap, ARIZONA_SYSTEM_CLOCK_1,
			  &state->sysclk);
	अगर (ret) अणु
		dev_err(arizona->dev, "Failed to cache SYSCLK settings: %d\n",
			ret);
		वापस ret;
	पूर्ण

	/* Start up SYSCLK using the FLL in मुक्त running mode */
	ret = regmap_ग_लिखो(arizona->regmap, ARIZONA_FLL1_CONTROL_1,
			ARIZONA_FLL1_ENA | ARIZONA_FLL1_FREERUN);
	अगर (ret) अणु
		dev_err(arizona->dev,
			"Failed to start FLL in freerunning mode: %d\n",
			ret);
		वापस ret;
	पूर्ण
	ret = arizona_poll_reg(arizona, 180, ARIZONA_INTERRUPT_RAW_STATUS_5,
			       ARIZONA_FLL1_CLOCK_OK_STS,
			       ARIZONA_FLL1_CLOCK_OK_STS);
	अगर (ret)
		जाओ err_fll;

	ret = regmap_ग_लिखो(arizona->regmap, ARIZONA_SYSTEM_CLOCK_1, 0x0144);
	अगर (ret) अणु
		dev_err(arizona->dev, "Failed to start SYSCLK: %d\n", ret);
		जाओ err_fll;
	पूर्ण

	वापस 0;

err_fll:
	err = regmap_ग_लिखो(arizona->regmap, ARIZONA_FLL1_CONTROL_1, state->fll);
	अगर (err)
		dev_err(arizona->dev,
			"Failed to re-apply old FLL settings: %d\n", err);

	वापस ret;
पूर्ण

अटल पूर्णांक arizona_disable_मुक्तrun_sysclk(काष्ठा arizona *arizona,
					  काष्ठा arizona_sysclk_state *state)
अणु
	पूर्णांक ret;

	ret = regmap_ग_लिखो(arizona->regmap, ARIZONA_SYSTEM_CLOCK_1,
			   state->sysclk);
	अगर (ret) अणु
		dev_err(arizona->dev,
			"Failed to re-apply old SYSCLK settings: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = regmap_ग_लिखो(arizona->regmap, ARIZONA_FLL1_CONTROL_1, state->fll);
	अगर (ret) अणु
		dev_err(arizona->dev,
			"Failed to re-apply old FLL settings: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wm5102_apply_hardware_patch(काष्ठा arizona *arizona)
अणु
	काष्ठा arizona_sysclk_state state;
	पूर्णांक err, ret;

	ret = arizona_enable_मुक्तrun_sysclk(arizona, &state);
	अगर (ret)
		वापस ret;

	/* Start the ग_लिखो sequencer and रुको क्रम it to finish */
	ret = regmap_ग_लिखो(arizona->regmap, ARIZONA_WRITE_SEQUENCER_CTRL_0,
			   ARIZONA_WSEQ_ENA | ARIZONA_WSEQ_START | 160);
	अगर (ret) अणु
		dev_err(arizona->dev, "Failed to start write sequencer: %d\n",
			ret);
		जाओ err;
	पूर्ण

	ret = arizona_poll_reg(arizona, 30, ARIZONA_WRITE_SEQUENCER_CTRL_1,
			       ARIZONA_WSEQ_BUSY, 0);
	अगर (ret)
		regmap_ग_लिखो(arizona->regmap, ARIZONA_WRITE_SEQUENCER_CTRL_0,
			     ARIZONA_WSEQ_ABORT);

err:
	err = arizona_disable_मुक्तrun_sysclk(arizona, &state);

	वापस ret ?: err;
पूर्ण

/*
 * Register patch to some of the CODECs पूर्णांकernal ग_लिखो sequences
 * to ensure a clean निकास from the low घातer sleep state.
 */
अटल स्थिर काष्ठा reg_sequence wm5110_sleep_patch[] = अणु
	अणु 0x337A, 0xC100 पूर्ण,
	अणु 0x337B, 0x0041 पूर्ण,
	अणु 0x3300, 0xA210 पूर्ण,
	अणु 0x3301, 0x050C पूर्ण,
पूर्ण;

अटल पूर्णांक wm5110_apply_sleep_patch(काष्ठा arizona *arizona)
अणु
	काष्ठा arizona_sysclk_state state;
	पूर्णांक err, ret;

	ret = arizona_enable_मुक्तrun_sysclk(arizona, &state);
	अगर (ret)
		वापस ret;

	ret = regmap_multi_reg_ग_लिखो_bypassed(arizona->regmap,
					      wm5110_sleep_patch,
					      ARRAY_SIZE(wm5110_sleep_patch));

	err = arizona_disable_मुक्तrun_sysclk(arizona, &state);

	वापस ret ?: err;
पूर्ण

अटल पूर्णांक wm5102_clear_ग_लिखो_sequencer(काष्ठा arizona *arizona)
अणु
	पूर्णांक ret;

	ret = regmap_ग_लिखो(arizona->regmap, ARIZONA_WRITE_SEQUENCER_CTRL_3,
			   0x0);
	अगर (ret) अणु
		dev_err(arizona->dev,
			"Failed to clear write sequencer state: %d\n", ret);
		वापस ret;
	पूर्ण

	arizona_enable_reset(arizona);
	regulator_disable(arizona->dcvdd);

	msleep(20);

	ret = regulator_enable(arizona->dcvdd);
	अगर (ret) अणु
		dev_err(arizona->dev, "Failed to re-enable DCVDD: %d\n", ret);
		वापस ret;
	पूर्ण
	arizona_disable_reset(arizona);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक arizona_isolate_dcvdd(काष्ठा arizona *arizona)
अणु
	पूर्णांक ret;

	ret = regmap_update_bits(arizona->regmap,
				 ARIZONA_ISOLATION_CONTROL,
				 ARIZONA_ISOLATE_DCVDD1,
				 ARIZONA_ISOLATE_DCVDD1);
	अगर (ret != 0)
		dev_err(arizona->dev, "Failed to isolate DCVDD: %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक arizona_connect_dcvdd(काष्ठा arizona *arizona)
अणु
	पूर्णांक ret;

	ret = regmap_update_bits(arizona->regmap,
				 ARIZONA_ISOLATION_CONTROL,
				 ARIZONA_ISOLATE_DCVDD1, 0);
	अगर (ret != 0)
		dev_err(arizona->dev, "Failed to connect DCVDD: %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक arizona_is_jack_det_active(काष्ठा arizona *arizona)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(arizona->regmap, ARIZONA_JACK_DETECT_ANALOGUE, &val);
	अगर (ret) अणु
		dev_err(arizona->dev,
			"Failed to check jack det status: %d\n", ret);
		वापस ret;
	पूर्ण अन्यथा अगर (val & ARIZONA_JD1_ENA) अणु
		वापस 1;
	पूर्ण अन्यथा अणु
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक arizona_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा arizona *arizona = dev_get_drvdata(dev);
	पूर्णांक ret;

	dev_dbg(arizona->dev, "Leaving AoD mode\n");

	अगर (arizona->has_fully_घातered_off) अणु
		dev_dbg(arizona->dev, "Re-enabling core supplies\n");

		ret = regulator_bulk_enable(arizona->num_core_supplies,
					    arizona->core_supplies);
		अगर (ret) अणु
			dev_err(dev, "Failed to enable core supplies: %d\n",
				ret);
			वापस ret;
		पूर्ण
	पूर्ण

	ret = regulator_enable(arizona->dcvdd);
	अगर (ret != 0) अणु
		dev_err(arizona->dev, "Failed to enable DCVDD: %d\n", ret);
		अगर (arizona->has_fully_घातered_off)
			regulator_bulk_disable(arizona->num_core_supplies,
					       arizona->core_supplies);
		वापस ret;
	पूर्ण

	अगर (arizona->has_fully_घातered_off) अणु
		arizona_disable_reset(arizona);
		enable_irq(arizona->irq);
		arizona->has_fully_घातered_off = false;
	पूर्ण

	regcache_cache_only(arizona->regmap, false);

	चयन (arizona->type) अणु
	हाल WM5102:
		अगर (arizona->बाह्यal_dcvdd) अणु
			ret = arizona_connect_dcvdd(arizona);
			अगर (ret != 0)
				जाओ err;
		पूर्ण

		ret = wm5102_patch(arizona);
		अगर (ret != 0) अणु
			dev_err(arizona->dev, "Failed to apply patch: %d\n",
				ret);
			जाओ err;
		पूर्ण

		ret = wm5102_apply_hardware_patch(arizona);
		अगर (ret) अणु
			dev_err(arizona->dev,
				"Failed to apply hardware patch: %d\n",
				ret);
			जाओ err;
		पूर्ण
		अवरोध;
	हाल WM5110:
	हाल WM8280:
		ret = arizona_रुको_क्रम_boot(arizona);
		अगर (ret)
			जाओ err;

		अगर (arizona->बाह्यal_dcvdd) अणु
			ret = arizona_connect_dcvdd(arizona);
			अगर (ret != 0)
				जाओ err;
		पूर्ण अन्यथा अणु
			/*
			 * As this is only called क्रम the पूर्णांकernal regulator
			 * (where we know voltage ranges available) it is ok
			 * to request an exact range.
			 */
			ret = regulator_set_voltage(arizona->dcvdd,
						    1200000, 1200000);
			अगर (ret < 0) अणु
				dev_err(arizona->dev,
					"Failed to set resume voltage: %d\n",
					ret);
				जाओ err;
			पूर्ण
		पूर्ण

		ret = wm5110_apply_sleep_patch(arizona);
		अगर (ret) अणु
			dev_err(arizona->dev,
				"Failed to re-apply sleep patch: %d\n",
				ret);
			जाओ err;
		पूर्ण
		अवरोध;
	हाल WM1831:
	हाल CS47L24:
		ret = arizona_रुको_क्रम_boot(arizona);
		अगर (ret != 0)
			जाओ err;
		अवरोध;
	शेष:
		ret = arizona_रुको_क्रम_boot(arizona);
		अगर (ret != 0)
			जाओ err;

		अगर (arizona->बाह्यal_dcvdd) अणु
			ret = arizona_connect_dcvdd(arizona);
			अगर (ret != 0)
				जाओ err;
		पूर्ण
		अवरोध;
	पूर्ण

	ret = regcache_sync(arizona->regmap);
	अगर (ret != 0) अणु
		dev_err(arizona->dev, "Failed to restore register cache\n");
		जाओ err;
	पूर्ण

	वापस 0;

err:
	regcache_cache_only(arizona->regmap, true);
	regulator_disable(arizona->dcvdd);
	वापस ret;
पूर्ण

अटल पूर्णांक arizona_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा arizona *arizona = dev_get_drvdata(dev);
	पूर्णांक jd_active = 0;
	पूर्णांक ret;

	dev_dbg(arizona->dev, "Entering AoD mode\n");

	चयन (arizona->type) अणु
	हाल WM5110:
	हाल WM8280:
		jd_active = arizona_is_jack_det_active(arizona);
		अगर (jd_active < 0)
			वापस jd_active;

		अगर (arizona->बाह्यal_dcvdd) अणु
			ret = arizona_isolate_dcvdd(arizona);
			अगर (ret != 0)
				वापस ret;
		पूर्ण अन्यथा अणु
			/*
			 * As this is only called क्रम the पूर्णांकernal regulator
			 * (where we know voltage ranges available) it is ok
			 * to request an exact range.
			 */
			ret = regulator_set_voltage(arizona->dcvdd,
						    1175000, 1175000);
			अगर (ret < 0) अणु
				dev_err(arizona->dev,
					"Failed to set suspend voltage: %d\n",
					ret);
				वापस ret;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल WM5102:
		jd_active = arizona_is_jack_det_active(arizona);
		अगर (jd_active < 0)
			वापस jd_active;

		अगर (arizona->बाह्यal_dcvdd) अणु
			ret = arizona_isolate_dcvdd(arizona);
			अगर (ret != 0)
				वापस ret;
		पूर्ण

		अगर (!jd_active) अणु
			ret = regmap_ग_लिखो(arizona->regmap,
					   ARIZONA_WRITE_SEQUENCER_CTRL_3, 0x0);
			अगर (ret) अणु
				dev_err(arizona->dev,
					"Failed to clear write sequencer: %d\n",
					ret);
				वापस ret;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल WM1831:
	हाल CS47L24:
		अवरोध;
	शेष:
		jd_active = arizona_is_jack_det_active(arizona);
		अगर (jd_active < 0)
			वापस jd_active;

		अगर (arizona->बाह्यal_dcvdd) अणु
			ret = arizona_isolate_dcvdd(arizona);
			अगर (ret != 0)
				वापस ret;
		पूर्ण
		अवरोध;
	पूर्ण

	regcache_cache_only(arizona->regmap, true);
	regcache_mark_dirty(arizona->regmap);
	regulator_disable(arizona->dcvdd);

	/* Allow us to completely घातer करोwn अगर no jack detection */
	अगर (!jd_active) अणु
		dev_dbg(arizona->dev, "Fully powering off\n");

		arizona->has_fully_घातered_off = true;

		disable_irq_nosync(arizona->irq);
		arizona_enable_reset(arizona);
		regulator_bulk_disable(arizona->num_core_supplies,
				       arizona->core_supplies);
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक arizona_suspend(काष्ठा device *dev)
अणु
	काष्ठा arizona *arizona = dev_get_drvdata(dev);

	dev_dbg(arizona->dev, "Suspend, disabling IRQ\n");
	disable_irq(arizona->irq);

	वापस 0;
पूर्ण

अटल पूर्णांक arizona_suspend_noirq(काष्ठा device *dev)
अणु
	काष्ठा arizona *arizona = dev_get_drvdata(dev);

	dev_dbg(arizona->dev, "Late suspend, reenabling IRQ\n");
	enable_irq(arizona->irq);

	वापस 0;
पूर्ण

अटल पूर्णांक arizona_resume_noirq(काष्ठा device *dev)
अणु
	काष्ठा arizona *arizona = dev_get_drvdata(dev);

	dev_dbg(arizona->dev, "Early resume, disabling IRQ\n");
	disable_irq(arizona->irq);

	वापस 0;
पूर्ण

अटल पूर्णांक arizona_resume(काष्ठा device *dev)
अणु
	काष्ठा arizona *arizona = dev_get_drvdata(dev);

	dev_dbg(arizona->dev, "Resume, reenabling IRQ\n");
	enable_irq(arizona->irq);

	वापस 0;
पूर्ण
#पूर्ण_अगर

स्थिर काष्ठा dev_pm_ops arizona_pm_ops = अणु
	SET_RUNTIME_PM_OPS(arizona_runसमय_suspend,
			   arizona_runसमय_resume,
			   शून्य)
	SET_SYSTEM_SLEEP_PM_OPS(arizona_suspend, arizona_resume)
	SET_NOIRQ_SYSTEM_SLEEP_PM_OPS(arizona_suspend_noirq,
				      arizona_resume_noirq)
पूर्ण;
EXPORT_SYMBOL_GPL(arizona_pm_ops);

#अगर_घोषित CONFIG_OF
अटल पूर्णांक arizona_of_get_core_pdata(काष्ठा arizona *arizona)
अणु
	काष्ठा arizona_pdata *pdata = &arizona->pdata;
	पूर्णांक ret, i;

	/* Handle old non-standard DT binding */
	pdata->reset = devm_gpiod_get(arizona->dev, "wlf,reset", GPIOD_OUT_LOW);
	अगर (IS_ERR(pdata->reset)) अणु
		ret = PTR_ERR(pdata->reset);

		/*
		 * Reset missing will be caught when other binding is पढ़ो
		 * but all other errors imply this binding is in use but has
		 * encountered a problem so should be handled.
		 */
		अगर (ret == -EPROBE_DEFER)
			वापस ret;
		अन्यथा अगर (ret != -ENOENT && ret != -ENOSYS)
			dev_err(arizona->dev, "Reset GPIO malformed: %d\n",
				ret);

		pdata->reset = शून्य;
	पूर्ण

	ret = of_property_पढ़ो_u32_array(arizona->dev->of_node,
					 "wlf,gpio-defaults",
					 pdata->gpio_शेषs,
					 ARRAY_SIZE(pdata->gpio_शेषs));
	अगर (ret >= 0) अणु
		/*
		 * All values are literal except out of range values
		 * which are chip शेष, translate पूर्णांकo platक्रमm
		 * data which uses 0 as chip शेष and out of range
		 * as zero.
		 */
		क्रम (i = 0; i < ARRAY_SIZE(pdata->gpio_शेषs); i++) अणु
			अगर (pdata->gpio_शेषs[i] > 0xffff)
				pdata->gpio_शेषs[i] = 0;
			अन्यथा अगर (pdata->gpio_शेषs[i] == 0)
				pdata->gpio_शेषs[i] = 0x10000;
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_err(arizona->dev, "Failed to parse GPIO defaults: %d\n",
			ret);
	पूर्ण

	वापस 0;
पूर्ण

स्थिर काष्ठा of_device_id arizona_of_match[] = अणु
	अणु .compatible = "wlf,wm5102", .data = (व्योम *)WM5102 पूर्ण,
	अणु .compatible = "wlf,wm5110", .data = (व्योम *)WM5110 पूर्ण,
	अणु .compatible = "wlf,wm8280", .data = (व्योम *)WM8280 पूर्ण,
	अणु .compatible = "wlf,wm8997", .data = (व्योम *)WM8997 पूर्ण,
	अणु .compatible = "wlf,wm8998", .data = (व्योम *)WM8998 पूर्ण,
	अणु .compatible = "wlf,wm1814", .data = (व्योम *)WM1814 पूर्ण,
	अणु .compatible = "wlf,wm1831", .data = (व्योम *)WM1831 पूर्ण,
	अणु .compatible = "cirrus,cs47l24", .data = (व्योम *)CS47L24 पूर्ण,
	अणुपूर्ण,
पूर्ण;
EXPORT_SYMBOL_GPL(arizona_of_match);
#अन्यथा
अटल अंतरभूत पूर्णांक arizona_of_get_core_pdata(काष्ठा arizona *arizona)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा mfd_cell early_devs[] = अणु
	अणु .name = "arizona-ldo1" पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर wm5102_supplies[] = अणु
	"MICVDD",
	"DBVDD2",
	"DBVDD3",
	"CPVDD",
	"SPKVDDL",
	"SPKVDDR",
पूर्ण;

अटल स्थिर काष्ठा mfd_cell wm5102_devs[] = अणु
	अणु .name = "arizona-micsupp" पूर्ण,
	अणु .name = "arizona-gpio" पूर्ण,
	अणु .name = "arizona-haptics" पूर्ण,
	अणु .name = "arizona-pwm" पूर्ण,
	अणु
		.name = "wm5102-codec",
		.parent_supplies = wm5102_supplies,
		.num_parent_supplies = ARRAY_SIZE(wm5102_supplies),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell wm5110_devs[] = अणु
	अणु .name = "arizona-micsupp" पूर्ण,
	अणु .name = "arizona-gpio" पूर्ण,
	अणु .name = "arizona-haptics" पूर्ण,
	अणु .name = "arizona-pwm" पूर्ण,
	अणु
		.name = "wm5110-codec",
		.parent_supplies = wm5102_supplies,
		.num_parent_supplies = ARRAY_SIZE(wm5102_supplies),
	पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर cs47l24_supplies[] = अणु
	"MICVDD",
	"CPVDD",
	"SPKVDD",
पूर्ण;

अटल स्थिर काष्ठा mfd_cell cs47l24_devs[] = अणु
	अणु .name = "arizona-gpio" पूर्ण,
	अणु .name = "arizona-haptics" पूर्ण,
	अणु .name = "arizona-pwm" पूर्ण,
	अणु
		.name = "cs47l24-codec",
		.parent_supplies = cs47l24_supplies,
		.num_parent_supplies = ARRAY_SIZE(cs47l24_supplies),
	पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर wm8997_supplies[] = अणु
	"MICVDD",
	"DBVDD2",
	"CPVDD",
	"SPKVDD",
पूर्ण;

अटल स्थिर काष्ठा mfd_cell wm8997_devs[] = अणु
	अणु .name = "arizona-micsupp" पूर्ण,
	अणु .name = "arizona-gpio" पूर्ण,
	अणु .name = "arizona-haptics" पूर्ण,
	अणु .name = "arizona-pwm" पूर्ण,
	अणु
		.name = "wm8997-codec",
		.parent_supplies = wm8997_supplies,
		.num_parent_supplies = ARRAY_SIZE(wm8997_supplies),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell wm8998_devs[] = अणु
	अणु .name = "arizona-micsupp" पूर्ण,
	अणु .name = "arizona-gpio" पूर्ण,
	अणु .name = "arizona-haptics" पूर्ण,
	अणु .name = "arizona-pwm" पूर्ण,
	अणु
		.name = "wm8998-codec",
		.parent_supplies = wm5102_supplies,
		.num_parent_supplies = ARRAY_SIZE(wm5102_supplies),
	पूर्ण,
पूर्ण;

पूर्णांक arizona_dev_init(काष्ठा arizona *arizona)
अणु
	अटल स्थिर अक्षर * स्थिर mclk_name[] = अणु "mclk1", "mclk2" पूर्ण;
	काष्ठा device *dev = arizona->dev;
	स्थिर अक्षर *type_name = शून्य;
	अचिन्हित पूर्णांक reg, val;
	पूर्णांक (*apply_patch)(काष्ठा arizona *) = शून्य;
	स्थिर काष्ठा mfd_cell *subdevs = शून्य;
	पूर्णांक n_subdevs = 0, ret, i;

	dev_set_drvdata(arizona->dev, arizona);
	mutex_init(&arizona->clk_lock);

	अगर (dev_get_platdata(arizona->dev)) अणु
		स_नकल(&arizona->pdata, dev_get_platdata(arizona->dev),
		       माप(arizona->pdata));
	पूर्ण अन्यथा अणु
		ret = arizona_of_get_core_pdata(arizona);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	BUILD_BUG_ON(ARRAY_SIZE(arizona->mclk) != ARRAY_SIZE(mclk_name));
	क्रम (i = 0; i < ARRAY_SIZE(arizona->mclk); i++) अणु
		arizona->mclk[i] = devm_clk_get(arizona->dev, mclk_name[i]);
		अगर (IS_ERR(arizona->mclk[i])) अणु
			dev_info(arizona->dev, "Failed to get %s: %ld\n",
				 mclk_name[i], PTR_ERR(arizona->mclk[i]));
			arizona->mclk[i] = शून्य;
		पूर्ण
	पूर्ण

	regcache_cache_only(arizona->regmap, true);

	चयन (arizona->type) अणु
	हाल WM5102:
	हाल WM5110:
	हाल WM8280:
	हाल WM8997:
	हाल WM8998:
	हाल WM1814:
	हाल WM1831:
	हाल CS47L24:
		क्रम (i = 0; i < ARRAY_SIZE(wm5102_core_supplies); i++)
			arizona->core_supplies[i].supply
				= wm5102_core_supplies[i];
		arizona->num_core_supplies = ARRAY_SIZE(wm5102_core_supplies);
		अवरोध;
	शेष:
		dev_err(arizona->dev, "Unknown device type %d\n",
			arizona->type);
		वापस -ENODEV;
	पूर्ण

	/* Mark DCVDD as बाह्यal, LDO1 driver will clear अगर पूर्णांकernal */
	arizona->बाह्यal_dcvdd = true;

	चयन (arizona->type) अणु
	हाल WM1831:
	हाल CS47L24:
		अवरोध; /* No LDO1 regulator */
	शेष:
		ret = mfd_add_devices(arizona->dev, -1, early_devs,
				      ARRAY_SIZE(early_devs), शून्य, 0, शून्य);
		अगर (ret != 0) अणु
			dev_err(dev, "Failed to add early children: %d\n", ret);
			वापस ret;
		पूर्ण
		अवरोध;
	पूर्ण

	ret = devm_regulator_bulk_get(dev, arizona->num_core_supplies,
				      arizona->core_supplies);
	अगर (ret != 0) अणु
		dev_err(dev, "Failed to request core supplies: %d\n",
			ret);
		जाओ err_early;
	पूर्ण

	/**
	 * Don't use devres here because the only device we have to get
	 * against is the MFD device and DCVDD will likely be supplied by
	 * one of its children. Meaning that the regulator will be
	 * destroyed by the समय devres calls regulator put.
	 */
	arizona->dcvdd = regulator_get(arizona->dev, "DCVDD");
	अगर (IS_ERR(arizona->dcvdd)) अणु
		ret = PTR_ERR(arizona->dcvdd);
		dev_err(dev, "Failed to request DCVDD: %d\n", ret);
		जाओ err_early;
	पूर्ण

	अगर (!arizona->pdata.reset) अणु
		/* Start out with /RESET low to put the chip पूर्णांकo reset */
		arizona->pdata.reset = devm_gpiod_get(arizona->dev, "reset",
						      GPIOD_OUT_LOW);
		अगर (IS_ERR(arizona->pdata.reset)) अणु
			ret = PTR_ERR(arizona->pdata.reset);
			अगर (ret == -EPROBE_DEFER)
				जाओ err_dcvdd;

			dev_err(arizona->dev,
				"Reset GPIO missing/malformed: %d\n", ret);

			arizona->pdata.reset = शून्य;
		पूर्ण
	पूर्ण

	ret = regulator_bulk_enable(arizona->num_core_supplies,
				    arizona->core_supplies);
	अगर (ret != 0) अणु
		dev_err(dev, "Failed to enable core supplies: %d\n",
			ret);
		जाओ err_dcvdd;
	पूर्ण

	ret = regulator_enable(arizona->dcvdd);
	अगर (ret != 0) अणु
		dev_err(dev, "Failed to enable DCVDD: %d\n", ret);
		जाओ err_enable;
	पूर्ण

	arizona_disable_reset(arizona);

	regcache_cache_only(arizona->regmap, false);

	/* Verअगरy that this is a chip we know about */
	ret = regmap_पढ़ो(arizona->regmap, ARIZONA_SOFTWARE_RESET, &reg);
	अगर (ret != 0) अणु
		dev_err(dev, "Failed to read ID register: %d\n", ret);
		जाओ err_reset;
	पूर्ण

	चयन (reg) अणु
	हाल 0x5102:
	हाल 0x5110:
	हाल 0x6349:
	हाल 0x6363:
	हाल 0x8997:
		अवरोध;
	शेष:
		dev_err(arizona->dev, "Unknown device ID: %x\n", reg);
		ret = -ENODEV;
		जाओ err_reset;
	पूर्ण

	/* If we have a /RESET GPIO we'll alपढ़ोy be reset */
	अगर (!arizona->pdata.reset) अणु
		ret = regmap_ग_लिखो(arizona->regmap, ARIZONA_SOFTWARE_RESET, 0);
		अगर (ret != 0) अणु
			dev_err(dev, "Failed to reset device: %d\n", ret);
			जाओ err_reset;
		पूर्ण

		usleep_range(1000, 5000);
	पूर्ण

	/* Ensure device startup is complete */
	चयन (arizona->type) अणु
	हाल WM5102:
		ret = regmap_पढ़ो(arizona->regmap,
				  ARIZONA_WRITE_SEQUENCER_CTRL_3, &val);
		अगर (ret) अणु
			dev_err(dev,
				"Failed to check write sequencer state: %d\n",
				ret);
		पूर्ण अन्यथा अगर (val & 0x01) अणु
			ret = wm5102_clear_ग_लिखो_sequencer(arizona);
			अगर (ret)
				वापस ret;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	ret = arizona_रुको_क्रम_boot(arizona);
	अगर (ret) अणु
		dev_err(arizona->dev, "Device failed initial boot: %d\n", ret);
		जाओ err_reset;
	पूर्ण

	/* Read the device ID inक्रमmation & करो device specअगरic stuff */
	ret = regmap_पढ़ो(arizona->regmap, ARIZONA_SOFTWARE_RESET, &reg);
	अगर (ret != 0) अणु
		dev_err(dev, "Failed to read ID register: %d\n", ret);
		जाओ err_reset;
	पूर्ण

	ret = regmap_पढ़ो(arizona->regmap, ARIZONA_DEVICE_REVISION,
			  &arizona->rev);
	अगर (ret != 0) अणु
		dev_err(dev, "Failed to read revision register: %d\n", ret);
		जाओ err_reset;
	पूर्ण
	arizona->rev &= ARIZONA_DEVICE_REVISION_MASK;

	चयन (reg) अणु
	हाल 0x5102:
		अगर (IS_ENABLED(CONFIG_MFD_WM5102)) अणु
			type_name = "WM5102";
			अगर (arizona->type != WM5102) अणु
				dev_warn(arizona->dev,
					 "WM5102 registered as %d\n",
					 arizona->type);
				arizona->type = WM5102;
			पूर्ण

			apply_patch = wm5102_patch;
			arizona->rev &= 0x7;
			subdevs = wm5102_devs;
			n_subdevs = ARRAY_SIZE(wm5102_devs);
		पूर्ण
		अवरोध;
	हाल 0x5110:
		अगर (IS_ENABLED(CONFIG_MFD_WM5110)) अणु
			चयन (arizona->type) अणु
			हाल WM5110:
				type_name = "WM5110";
				अवरोध;
			हाल WM8280:
				type_name = "WM8280";
				अवरोध;
			शेष:
				type_name = "WM5110";
				dev_warn(arizona->dev,
					 "WM5110 registered as %d\n",
					 arizona->type);
				arizona->type = WM5110;
				अवरोध;
			पूर्ण

			apply_patch = wm5110_patch;
			subdevs = wm5110_devs;
			n_subdevs = ARRAY_SIZE(wm5110_devs);
		पूर्ण
		अवरोध;
	हाल 0x6363:
		अगर (IS_ENABLED(CONFIG_MFD_CS47L24)) अणु
			चयन (arizona->type) अणु
			हाल CS47L24:
				type_name = "CS47L24";
				अवरोध;

			हाल WM1831:
				type_name = "WM1831";
				अवरोध;

			शेष:
				dev_warn(arizona->dev,
					 "CS47L24 registered as %d\n",
					 arizona->type);
				arizona->type = CS47L24;
				अवरोध;
			पूर्ण

			apply_patch = cs47l24_patch;
			subdevs = cs47l24_devs;
			n_subdevs = ARRAY_SIZE(cs47l24_devs);
		पूर्ण
		अवरोध;
	हाल 0x8997:
		अगर (IS_ENABLED(CONFIG_MFD_WM8997)) अणु
			type_name = "WM8997";
			अगर (arizona->type != WM8997) अणु
				dev_warn(arizona->dev,
					 "WM8997 registered as %d\n",
					 arizona->type);
				arizona->type = WM8997;
			पूर्ण

			apply_patch = wm8997_patch;
			subdevs = wm8997_devs;
			n_subdevs = ARRAY_SIZE(wm8997_devs);
		पूर्ण
		अवरोध;
	हाल 0x6349:
		अगर (IS_ENABLED(CONFIG_MFD_WM8998)) अणु
			चयन (arizona->type) अणु
			हाल WM8998:
				type_name = "WM8998";
				अवरोध;

			हाल WM1814:
				type_name = "WM1814";
				अवरोध;

			शेष:
				type_name = "WM8998";
				dev_warn(arizona->dev,
					 "WM8998 registered as %d\n",
					 arizona->type);
				arizona->type = WM8998;
			पूर्ण

			apply_patch = wm8998_patch;
			subdevs = wm8998_devs;
			n_subdevs = ARRAY_SIZE(wm8998_devs);
		पूर्ण
		अवरोध;
	शेष:
		dev_err(arizona->dev, "Unknown device ID %x\n", reg);
		ret = -ENODEV;
		जाओ err_reset;
	पूर्ण

	अगर (!subdevs) अणु
		dev_err(arizona->dev,
			"No kernel support for device ID %x\n", reg);
		ret = -ENODEV;
		जाओ err_reset;
	पूर्ण

	dev_info(dev, "%s revision %c\n", type_name, arizona->rev + 'A');

	अगर (apply_patch) अणु
		ret = apply_patch(arizona);
		अगर (ret != 0) अणु
			dev_err(arizona->dev, "Failed to apply patch: %d\n",
				ret);
			जाओ err_reset;
		पूर्ण

		चयन (arizona->type) अणु
		हाल WM5102:
			ret = wm5102_apply_hardware_patch(arizona);
			अगर (ret) अणु
				dev_err(arizona->dev,
					"Failed to apply hardware patch: %d\n",
					ret);
				जाओ err_reset;
			पूर्ण
			अवरोध;
		हाल WM5110:
		हाल WM8280:
			ret = wm5110_apply_sleep_patch(arizona);
			अगर (ret) अणु
				dev_err(arizona->dev,
					"Failed to apply sleep patch: %d\n",
					ret);
				जाओ err_reset;
			पूर्ण
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(arizona->pdata.gpio_शेषs); i++) अणु
		अगर (!arizona->pdata.gpio_शेषs[i])
			जारी;

		regmap_ग_लिखो(arizona->regmap, ARIZONA_GPIO1_CTRL + i,
			     arizona->pdata.gpio_शेषs[i]);
	पूर्ण

	/* Chip शेष */
	अगर (!arizona->pdata.clk32k_src)
		arizona->pdata.clk32k_src = ARIZONA_32KZ_MCLK2;

	चयन (arizona->pdata.clk32k_src) अणु
	हाल ARIZONA_32KZ_MCLK1:
	हाल ARIZONA_32KZ_MCLK2:
		regmap_update_bits(arizona->regmap, ARIZONA_CLOCK_32K_1,
				   ARIZONA_CLK_32K_SRC_MASK,
				   arizona->pdata.clk32k_src - 1);
		arizona_clk32k_enable(arizona);
		अवरोध;
	हाल ARIZONA_32KZ_NONE:
		regmap_update_bits(arizona->regmap, ARIZONA_CLOCK_32K_1,
				   ARIZONA_CLK_32K_SRC_MASK, 2);
		अवरोध;
	शेष:
		dev_err(arizona->dev, "Invalid 32kHz clock source: %d\n",
			arizona->pdata.clk32k_src);
		ret = -EINVAL;
		जाओ err_reset;
	पूर्ण

	क्रम (i = 0; i < ARIZONA_MAX_MICBIAS; i++) अणु
		अगर (!arizona->pdata.micbias[i].mV &&
		    !arizona->pdata.micbias[i].bypass)
			जारी;

		/* Apply शेष क्रम bypass mode */
		अगर (!arizona->pdata.micbias[i].mV)
			arizona->pdata.micbias[i].mV = 2800;

		val = (arizona->pdata.micbias[i].mV - 1500) / 100;

		val <<= ARIZONA_MICB1_LVL_SHIFT;

		अगर (arizona->pdata.micbias[i].ext_cap)
			val |= ARIZONA_MICB1_EXT_CAP;

		अगर (arizona->pdata.micbias[i].disअक्षरge)
			val |= ARIZONA_MICB1_DISCH;

		अगर (arizona->pdata.micbias[i].soft_start)
			val |= ARIZONA_MICB1_RATE;

		अगर (arizona->pdata.micbias[i].bypass)
			val |= ARIZONA_MICB1_BYPASS;

		regmap_update_bits(arizona->regmap,
				   ARIZONA_MIC_BIAS_CTRL_1 + i,
				   ARIZONA_MICB1_LVL_MASK |
				   ARIZONA_MICB1_EXT_CAP |
				   ARIZONA_MICB1_DISCH |
				   ARIZONA_MICB1_BYPASS |
				   ARIZONA_MICB1_RATE, val);
	पूर्ण

	pm_runसमय_set_active(arizona->dev);
	pm_runसमय_enable(arizona->dev);

	/* Set up क्रम पूर्णांकerrupts */
	ret = arizona_irq_init(arizona);
	अगर (ret != 0)
		जाओ err_pm;

	pm_runसमय_set_स्वतःsuspend_delay(arizona->dev, 100);
	pm_runसमय_use_स्वतःsuspend(arizona->dev);

	arizona_request_irq(arizona, ARIZONA_IRQ_CLKGEN_ERR, "CLKGEN error",
			    arizona_clkgen_err, arizona);
	arizona_request_irq(arizona, ARIZONA_IRQ_OVERCLOCKED, "Overclocked",
			    arizona_overघड़ीed, arizona);
	arizona_request_irq(arizona, ARIZONA_IRQ_UNDERCLOCKED, "Underclocked",
			    arizona_underघड़ीed, arizona);

	ret = mfd_add_devices(arizona->dev, PLATFORM_DEVID_NONE,
			      subdevs, n_subdevs, शून्य, 0, शून्य);

	अगर (ret) अणु
		dev_err(arizona->dev, "Failed to add subdevices: %d\n", ret);
		जाओ err_irq;
	पूर्ण

	वापस 0;

err_irq:
	arizona_irq_निकास(arizona);
err_pm:
	pm_runसमय_disable(arizona->dev);

	चयन (arizona->pdata.clk32k_src) अणु
	हाल ARIZONA_32KZ_MCLK1:
	हाल ARIZONA_32KZ_MCLK2:
		arizona_clk32k_disable(arizona);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
err_reset:
	arizona_enable_reset(arizona);
	regulator_disable(arizona->dcvdd);
err_enable:
	regulator_bulk_disable(arizona->num_core_supplies,
			       arizona->core_supplies);
err_dcvdd:
	regulator_put(arizona->dcvdd);
err_early:
	mfd_हटाओ_devices(dev);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(arizona_dev_init);

पूर्णांक arizona_dev_निकास(काष्ठा arizona *arizona)
अणु
	disable_irq(arizona->irq);
	pm_runसमय_disable(arizona->dev);

	regulator_disable(arizona->dcvdd);
	regulator_put(arizona->dcvdd);

	चयन (arizona->pdata.clk32k_src) अणु
	हाल ARIZONA_32KZ_MCLK1:
	हाल ARIZONA_32KZ_MCLK2:
		arizona_clk32k_disable(arizona);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	mfd_हटाओ_devices(arizona->dev);
	arizona_मुक्त_irq(arizona, ARIZONA_IRQ_UNDERCLOCKED, arizona);
	arizona_मुक्त_irq(arizona, ARIZONA_IRQ_OVERCLOCKED, arizona);
	arizona_मुक्त_irq(arizona, ARIZONA_IRQ_CLKGEN_ERR, arizona);
	arizona_irq_निकास(arizona);
	arizona_enable_reset(arizona);

	regulator_bulk_disable(arizona->num_core_supplies,
			       arizona->core_supplies);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(arizona_dev_निकास);
