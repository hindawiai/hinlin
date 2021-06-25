<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * MFD driver क्रम TWL6040 audio device
 *
 * Authors:	Misael Lopez Cruz <misael.lopez@ti.com>
 *		Jorge Eduarकरो Candelaria <jorge.candelaria@ti.com>
 *		Peter Ujfalusi <peter.ujfalusi@ti.com>
 *
 * Copyright:	(C) 2011 Texas Instruments, Inc.
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/kernel.h>
#समावेश <linux/err.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/regmap.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/twl6040.h>
#समावेश <linux/regulator/consumer.h>

#घोषणा VIBRACTRL_MEMBER(reg) ((reg == TWL6040_REG_VIBCTLL) ? 0 : 1)
#घोषणा TWL6040_NUM_SUPPLIES	(2)

अटल स्थिर काष्ठा reg_शेष twl6040_शेषs[] = अणु
	अणु 0x01, 0x4B पूर्ण, /* REG_ASICID	(ro) */
	अणु 0x02, 0x00 पूर्ण, /* REG_ASICREV	(ro) */
	अणु 0x03, 0x00 पूर्ण, /* REG_INTID	*/
	अणु 0x04, 0x00 पूर्ण, /* REG_INTMR	*/
	अणु 0x05, 0x00 पूर्ण, /* REG_NCPCTRL	*/
	अणु 0x06, 0x00 पूर्ण, /* REG_LDOCTL	*/
	अणु 0x07, 0x60 पूर्ण, /* REG_HPPLLCTL	*/
	अणु 0x08, 0x00 पूर्ण, /* REG_LPPLLCTL	*/
	अणु 0x09, 0x4A पूर्ण, /* REG_LPPLLDIV	*/
	अणु 0x0A, 0x00 पूर्ण, /* REG_AMICBCTL	*/
	अणु 0x0B, 0x00 पूर्ण, /* REG_DMICBCTL	*/
	अणु 0x0C, 0x00 पूर्ण, /* REG_MICLCTL	*/
	अणु 0x0D, 0x00 पूर्ण, /* REG_MICRCTL	*/
	अणु 0x0E, 0x00 पूर्ण, /* REG_MICGAIN	*/
	अणु 0x0F, 0x1B पूर्ण, /* REG_LINEGAIN	*/
	अणु 0x10, 0x00 पूर्ण, /* REG_HSLCTL	*/
	अणु 0x11, 0x00 पूर्ण, /* REG_HSRCTL	*/
	अणु 0x12, 0x00 पूर्ण, /* REG_HSGAIN	*/
	अणु 0x13, 0x00 पूर्ण, /* REG_EARCTL	*/
	अणु 0x14, 0x00 पूर्ण, /* REG_HFLCTL	*/
	अणु 0x15, 0x00 पूर्ण, /* REG_HFLGAIN	*/
	अणु 0x16, 0x00 पूर्ण, /* REG_HFRCTL	*/
	अणु 0x17, 0x00 पूर्ण, /* REG_HFRGAIN	*/
	अणु 0x18, 0x00 पूर्ण, /* REG_VIBCTLL	*/
	अणु 0x19, 0x00 पूर्ण, /* REG_VIBDATL	*/
	अणु 0x1A, 0x00 पूर्ण, /* REG_VIBCTLR	*/
	अणु 0x1B, 0x00 पूर्ण, /* REG_VIBDATR	*/
	अणु 0x1C, 0x00 पूर्ण, /* REG_HKCTL1	*/
	अणु 0x1D, 0x00 पूर्ण, /* REG_HKCTL2	*/
	अणु 0x1E, 0x00 पूर्ण, /* REG_GPOCTL	*/
	अणु 0x1F, 0x00 पूर्ण, /* REG_ALB	*/
	अणु 0x20, 0x00 पूर्ण, /* REG_DLB	*/
	/* 0x28, REG_TRIM1 */
	/* 0x29, REG_TRIM2 */
	/* 0x2A, REG_TRIM3 */
	/* 0x2B, REG_HSOTRIM */
	/* 0x2C, REG_HFOTRIM */
	अणु 0x2D, 0x08 पूर्ण, /* REG_ACCCTL	*/
	अणु 0x2E, 0x00 पूर्ण, /* REG_STATUS	(ro) */
पूर्ण;

अटल काष्ठा reg_sequence twl6040_patch[] = अणु
	/*
	 * Select I2C bus access to dual access रेजिस्टरs
	 * Interrupt रेजिस्टर is cleared on पढ़ो
	 * Select fast mode क्रम i2c (400KHz)
	 */
	अणु TWL6040_REG_ACCCTL,
		TWL6040_I2CSEL | TWL6040_INTCLRMODE | TWL6040_I2CMODE(1) पूर्ण,
पूर्ण;


अटल bool twl6040_has_vibra(काष्ठा device_node *parent)
अणु
	काष्ठा device_node *node;

	node = of_get_child_by_name(parent, "vibra");
	अगर (node) अणु
		of_node_put(node);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

पूर्णांक twl6040_reg_पढ़ो(काष्ठा twl6040 *twl6040, अचिन्हित पूर्णांक reg)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक val;

	ret = regmap_पढ़ो(twl6040->regmap, reg, &val);
	अगर (ret < 0)
		वापस ret;

	वापस val;
पूर्ण
EXPORT_SYMBOL(twl6040_reg_पढ़ो);

पूर्णांक twl6040_reg_ग_लिखो(काष्ठा twl6040 *twl6040, अचिन्हित पूर्णांक reg, u8 val)
अणु
	पूर्णांक ret;

	ret = regmap_ग_लिखो(twl6040->regmap, reg, val);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(twl6040_reg_ग_लिखो);

पूर्णांक twl6040_set_bits(काष्ठा twl6040 *twl6040, अचिन्हित पूर्णांक reg, u8 mask)
अणु
	वापस regmap_update_bits(twl6040->regmap, reg, mask, mask);
पूर्ण
EXPORT_SYMBOL(twl6040_set_bits);

पूर्णांक twl6040_clear_bits(काष्ठा twl6040 *twl6040, अचिन्हित पूर्णांक reg, u8 mask)
अणु
	वापस regmap_update_bits(twl6040->regmap, reg, mask, 0);
पूर्ण
EXPORT_SYMBOL(twl6040_clear_bits);

/* twl6040 codec manual घातer-up sequence */
अटल पूर्णांक twl6040_घातer_up_manual(काष्ठा twl6040 *twl6040)
अणु
	u8 lकरोctl, ncpctl, lppllctl;
	पूर्णांक ret;

	/* enable high-side LDO, reference प्रणाली and पूर्णांकernal oscillator */
	lकरोctl = TWL6040_HSLDOENA | TWL6040_REFENA | TWL6040_OSCENA;
	ret = twl6040_reg_ग_लिखो(twl6040, TWL6040_REG_LDOCTL, lकरोctl);
	अगर (ret)
		वापस ret;
	usleep_range(10000, 10500);

	/* enable negative अक्षरge pump */
	ncpctl = TWL6040_NCPENA;
	ret = twl6040_reg_ग_लिखो(twl6040, TWL6040_REG_NCPCTL, ncpctl);
	अगर (ret)
		जाओ ncp_err;
	usleep_range(1000, 1500);

	/* enable low-side LDO */
	lकरोctl |= TWL6040_LSLDOENA;
	ret = twl6040_reg_ग_लिखो(twl6040, TWL6040_REG_LDOCTL, lकरोctl);
	अगर (ret)
		जाओ lslकरो_err;
	usleep_range(1000, 1500);

	/* enable low-घातer PLL */
	lppllctl = TWL6040_LPLLENA;
	ret = twl6040_reg_ग_लिखो(twl6040, TWL6040_REG_LPPLLCTL, lppllctl);
	अगर (ret)
		जाओ lppll_err;
	usleep_range(5000, 5500);

	/* disable पूर्णांकernal oscillator */
	lकरोctl &= ~TWL6040_OSCENA;
	ret = twl6040_reg_ग_लिखो(twl6040, TWL6040_REG_LDOCTL, lकरोctl);
	अगर (ret)
		जाओ osc_err;

	वापस 0;

osc_err:
	lppllctl &= ~TWL6040_LPLLENA;
	twl6040_reg_ग_लिखो(twl6040, TWL6040_REG_LPPLLCTL, lppllctl);
lppll_err:
	lकरोctl &= ~TWL6040_LSLDOENA;
	twl6040_reg_ग_लिखो(twl6040, TWL6040_REG_LDOCTL, lकरोctl);
lslकरो_err:
	ncpctl &= ~TWL6040_NCPENA;
	twl6040_reg_ग_लिखो(twl6040, TWL6040_REG_NCPCTL, ncpctl);
ncp_err:
	lकरोctl &= ~(TWL6040_HSLDOENA | TWL6040_REFENA | TWL6040_OSCENA);
	twl6040_reg_ग_लिखो(twl6040, TWL6040_REG_LDOCTL, lकरोctl);

	dev_err(twl6040->dev, "manual power-up failed\n");
	वापस ret;
पूर्ण

/* twl6040 manual घातer-करोwn sequence */
अटल व्योम twl6040_घातer_करोwn_manual(काष्ठा twl6040 *twl6040)
अणु
	u8 ncpctl, lकरोctl, lppllctl;

	ncpctl = twl6040_reg_पढ़ो(twl6040, TWL6040_REG_NCPCTL);
	lकरोctl = twl6040_reg_पढ़ो(twl6040, TWL6040_REG_LDOCTL);
	lppllctl = twl6040_reg_पढ़ो(twl6040, TWL6040_REG_LPPLLCTL);

	/* enable पूर्णांकernal oscillator */
	lकरोctl |= TWL6040_OSCENA;
	twl6040_reg_ग_लिखो(twl6040, TWL6040_REG_LDOCTL, lकरोctl);
	usleep_range(1000, 1500);

	/* disable low-घातer PLL */
	lppllctl &= ~TWL6040_LPLLENA;
	twl6040_reg_ग_लिखो(twl6040, TWL6040_REG_LPPLLCTL, lppllctl);

	/* disable low-side LDO */
	lकरोctl &= ~TWL6040_LSLDOENA;
	twl6040_reg_ग_लिखो(twl6040, TWL6040_REG_LDOCTL, lकरोctl);

	/* disable negative अक्षरge pump */
	ncpctl &= ~TWL6040_NCPENA;
	twl6040_reg_ग_लिखो(twl6040, TWL6040_REG_NCPCTL, ncpctl);

	/* disable high-side LDO, reference प्रणाली and पूर्णांकernal oscillator */
	lकरोctl &= ~(TWL6040_HSLDOENA | TWL6040_REFENA | TWL6040_OSCENA);
	twl6040_reg_ग_लिखो(twl6040, TWL6040_REG_LDOCTL, lकरोctl);
पूर्ण

अटल irqवापस_t twl6040_पढ़ोyपूर्णांक_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा twl6040 *twl6040 = data;

	complete(&twl6040->पढ़ोy);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t twl6040_thपूर्णांक_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा twl6040 *twl6040 = data;
	u8 status;

	status = twl6040_reg_पढ़ो(twl6040, TWL6040_REG_STATUS);
	अगर (status & TWL6040_TSHUTDET) अणु
		dev_warn(twl6040->dev, "Thermal shutdown, powering-off");
		twl6040_घातer(twl6040, 0);
	पूर्ण अन्यथा अणु
		dev_warn(twl6040->dev, "Leaving thermal shutdown, powering-on");
		twl6040_घातer(twl6040, 1);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक twl6040_घातer_up_स्वतःmatic(काष्ठा twl6040 *twl6040)
अणु
	पूर्णांक समय_left;

	gpio_set_value(twl6040->audpwron, 1);

	समय_left = रुको_क्रम_completion_समयout(&twl6040->पढ़ोy,
						msecs_to_jअगरfies(144));
	अगर (!समय_left) अणु
		u8 पूर्णांकid;

		dev_warn(twl6040->dev, "timeout waiting for READYINT\n");
		पूर्णांकid = twl6040_reg_पढ़ो(twl6040, TWL6040_REG_INTID);
		अगर (!(पूर्णांकid & TWL6040_READYINT)) अणु
			dev_err(twl6040->dev, "automatic power-up failed\n");
			gpio_set_value(twl6040->audpwron, 0);
			वापस -ETIMEDOUT;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक twl6040_घातer(काष्ठा twl6040 *twl6040, पूर्णांक on)
अणु
	पूर्णांक ret = 0;

	mutex_lock(&twl6040->mutex);

	अगर (on) अणु
		/* alपढ़ोy घातered-up */
		अगर (twl6040->घातer_count++)
			जाओ out;

		ret = clk_prepare_enable(twl6040->clk32k);
		अगर (ret) अणु
			twl6040->घातer_count = 0;
			जाओ out;
		पूर्ण

		/* Allow ग_लिखोs to the chip */
		regcache_cache_only(twl6040->regmap, false);

		अगर (gpio_is_valid(twl6040->audpwron)) अणु
			/* use स्वतःmatic घातer-up sequence */
			ret = twl6040_घातer_up_स्वतःmatic(twl6040);
			अगर (ret) अणु
				clk_disable_unprepare(twl6040->clk32k);
				twl6040->घातer_count = 0;
				जाओ out;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* use manual घातer-up sequence */
			ret = twl6040_घातer_up_manual(twl6040);
			अगर (ret) अणु
				clk_disable_unprepare(twl6040->clk32k);
				twl6040->घातer_count = 0;
				जाओ out;
			पूर्ण
		पूर्ण

		/*
		 * Register access can produce errors after घातer-up unless we
		 * रुको at least 8ms based on measurements on duovero.
		 */
		usleep_range(10000, 12000);

		/* Sync with the HW */
		ret = regcache_sync(twl6040->regmap);
		अगर (ret) अणु
			dev_err(twl6040->dev, "Failed to sync with the HW: %i\n",
				ret);
			जाओ out;
		पूर्ण

		/* Default PLL configuration after घातer up */
		twl6040->pll = TWL6040_SYSCLK_SEL_LPPLL;
		twl6040->sysclk_rate = 19200000;
	पूर्ण अन्यथा अणु
		/* alपढ़ोy घातered-करोwn */
		अगर (!twl6040->घातer_count) अणु
			dev_err(twl6040->dev,
				"device is already powered-off\n");
			ret = -EPERM;
			जाओ out;
		पूर्ण

		अगर (--twl6040->घातer_count)
			जाओ out;

		अगर (gpio_is_valid(twl6040->audpwron)) अणु
			/* use AUDPWRON line */
			gpio_set_value(twl6040->audpwron, 0);

			/* घातer-करोwn sequence latency */
			usleep_range(500, 700);
		पूर्ण अन्यथा अणु
			/* use manual घातer-करोwn sequence */
			twl6040_घातer_करोwn_manual(twl6040);
		पूर्ण

		/* Set regmap to cache only and mark it as dirty */
		regcache_cache_only(twl6040->regmap, true);
		regcache_mark_dirty(twl6040->regmap);

		twl6040->sysclk_rate = 0;

		अगर (twl6040->pll == TWL6040_SYSCLK_SEL_HPPLL) अणु
			clk_disable_unprepare(twl6040->mclk);
			twl6040->mclk_rate = 0;
		पूर्ण

		clk_disable_unprepare(twl6040->clk32k);
	पूर्ण

out:
	mutex_unlock(&twl6040->mutex);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(twl6040_घातer);

पूर्णांक twl6040_set_pll(काष्ठा twl6040 *twl6040, पूर्णांक pll_id,
		    अचिन्हित पूर्णांक freq_in, अचिन्हित पूर्णांक freq_out)
अणु
	u8 hppllctl, lppllctl;
	पूर्णांक ret = 0;

	mutex_lock(&twl6040->mutex);

	hppllctl = twl6040_reg_पढ़ो(twl6040, TWL6040_REG_HPPLLCTL);
	lppllctl = twl6040_reg_पढ़ो(twl6040, TWL6040_REG_LPPLLCTL);

	/* Force full reconfiguration when चयनing between PLL */
	अगर (pll_id != twl6040->pll) अणु
		twl6040->sysclk_rate = 0;
		twl6040->mclk_rate = 0;
	पूर्ण

	चयन (pll_id) अणु
	हाल TWL6040_SYSCLK_SEL_LPPLL:
		/* low-घातer PLL भागider */
		/* Change the sysclk configuration only अगर it has been canged */
		अगर (twl6040->sysclk_rate != freq_out) अणु
			चयन (freq_out) अणु
			हाल 17640000:
				lppllctl |= TWL6040_LPLLFIN;
				अवरोध;
			हाल 19200000:
				lppllctl &= ~TWL6040_LPLLFIN;
				अवरोध;
			शेष:
				dev_err(twl6040->dev,
					"freq_out %d not supported\n",
					freq_out);
				ret = -EINVAL;
				जाओ pll_out;
			पूर्ण
			twl6040_reg_ग_लिखो(twl6040, TWL6040_REG_LPPLLCTL,
					  lppllctl);
		पूर्ण

		/* The PLL in use has not been change, we can निकास */
		अगर (twl6040->pll == pll_id)
			अवरोध;

		चयन (freq_in) अणु
		हाल 32768:
			lppllctl |= TWL6040_LPLLENA;
			twl6040_reg_ग_लिखो(twl6040, TWL6040_REG_LPPLLCTL,
					  lppllctl);
			mdelay(5);
			lppllctl &= ~TWL6040_HPLLSEL;
			twl6040_reg_ग_लिखो(twl6040, TWL6040_REG_LPPLLCTL,
					  lppllctl);
			hppllctl &= ~TWL6040_HPLLENA;
			twl6040_reg_ग_लिखो(twl6040, TWL6040_REG_HPPLLCTL,
					  hppllctl);
			अवरोध;
		शेष:
			dev_err(twl6040->dev,
				"freq_in %d not supported\n", freq_in);
			ret = -EINVAL;
			जाओ pll_out;
		पूर्ण

		clk_disable_unprepare(twl6040->mclk);
		अवरोध;
	हाल TWL6040_SYSCLK_SEL_HPPLL:
		/* high-perक्रमmance PLL can provide only 19.2 MHz */
		अगर (freq_out != 19200000) अणु
			dev_err(twl6040->dev,
				"freq_out %d not supported\n", freq_out);
			ret = -EINVAL;
			जाओ pll_out;
		पूर्ण

		अगर (twl6040->mclk_rate != freq_in) अणु
			hppllctl &= ~TWL6040_MCLK_MSK;

			चयन (freq_in) अणु
			हाल 12000000:
				/* PLL enabled, active mode */
				hppllctl |= TWL6040_MCLK_12000KHZ |
					    TWL6040_HPLLENA;
				अवरोध;
			हाल 19200000:
				/* PLL enabled, bypass mode */
				hppllctl |= TWL6040_MCLK_19200KHZ |
					    TWL6040_HPLLBP | TWL6040_HPLLENA;
				अवरोध;
			हाल 26000000:
				/* PLL enabled, active mode */
				hppllctl |= TWL6040_MCLK_26000KHZ |
					    TWL6040_HPLLENA;
				अवरोध;
			हाल 38400000:
				/* PLL enabled, bypass mode */
				hppllctl |= TWL6040_MCLK_38400KHZ |
					    TWL6040_HPLLBP | TWL6040_HPLLENA;
				अवरोध;
			शेष:
				dev_err(twl6040->dev,
					"freq_in %d not supported\n", freq_in);
				ret = -EINVAL;
				जाओ pll_out;
			पूर्ण

			/* When चयनing to HPPLL, enable the mclk first */
			अगर (pll_id != twl6040->pll)
				clk_prepare_enable(twl6040->mclk);
			/*
			 * enable घड़ी slicer to ensure input waveक्रमm is
			 * square
			 */
			hppllctl |= TWL6040_HPLLSQRENA;

			twl6040_reg_ग_लिखो(twl6040, TWL6040_REG_HPPLLCTL,
					  hppllctl);
			usleep_range(500, 700);
			lppllctl |= TWL6040_HPLLSEL;
			twl6040_reg_ग_लिखो(twl6040, TWL6040_REG_LPPLLCTL,
					  lppllctl);
			lppllctl &= ~TWL6040_LPLLENA;
			twl6040_reg_ग_लिखो(twl6040, TWL6040_REG_LPPLLCTL,
					  lppllctl);

			twl6040->mclk_rate = freq_in;
		पूर्ण
		अवरोध;
	शेष:
		dev_err(twl6040->dev, "unknown pll id %d\n", pll_id);
		ret = -EINVAL;
		जाओ pll_out;
	पूर्ण

	twl6040->sysclk_rate = freq_out;
	twl6040->pll = pll_id;

pll_out:
	mutex_unlock(&twl6040->mutex);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(twl6040_set_pll);

पूर्णांक twl6040_get_pll(काष्ठा twl6040 *twl6040)
अणु
	अगर (twl6040->घातer_count)
		वापस twl6040->pll;
	अन्यथा
		वापस -ENODEV;
पूर्ण
EXPORT_SYMBOL(twl6040_get_pll);

अचिन्हित पूर्णांक twl6040_get_sysclk(काष्ठा twl6040 *twl6040)
अणु
	वापस twl6040->sysclk_rate;
पूर्ण
EXPORT_SYMBOL(twl6040_get_sysclk);

/* Get the combined status of the vibra control रेजिस्टर */
पूर्णांक twl6040_get_vibralr_status(काष्ठा twl6040 *twl6040)
अणु
	अचिन्हित पूर्णांक reg;
	पूर्णांक ret;
	u8 status;

	ret = regmap_पढ़ो(twl6040->regmap, TWL6040_REG_VIBCTLL, &reg);
	अगर (ret != 0)
		वापस ret;
	status = reg;

	ret = regmap_पढ़ो(twl6040->regmap, TWL6040_REG_VIBCTLR, &reg);
	अगर (ret != 0)
		वापस ret;
	status |= reg;

	status &= (TWL6040_VIBENA | TWL6040_VIBSEL);

	वापस status;
पूर्ण
EXPORT_SYMBOL(twl6040_get_vibralr_status);

अटल काष्ठा resource twl6040_vibra_rsrc[] = अणु
	अणु
		.flags = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा resource twl6040_codec_rsrc[] = अणु
	अणु
		.flags = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल bool twl6040_पढ़ोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	/* Register 0 is not पढ़ोable */
	अगर (!reg)
		वापस false;
	वापस true;
पूर्ण

अटल bool twl6040_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल TWL6040_REG_ASICID:
	हाल TWL6040_REG_ASICREV:
	हाल TWL6040_REG_INTID:
	हाल TWL6040_REG_LPPLLCTL:
	हाल TWL6040_REG_HPPLLCTL:
	हाल TWL6040_REG_STATUS:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool twl6040_ग_लिखोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल TWL6040_REG_ASICID:
	हाल TWL6040_REG_ASICREV:
	हाल TWL6040_REG_STATUS:
		वापस false;
	शेष:
		वापस true;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regmap_config twl6040_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.reg_शेषs = twl6040_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(twl6040_शेषs),

	.max_रेजिस्टर = TWL6040_REG_STATUS, /* 0x2e */

	.पढ़ोable_reg = twl6040_पढ़ोable_reg,
	.अस्थिर_reg = twl6040_अस्थिर_reg,
	.ग_लिखोable_reg = twl6040_ग_लिखोable_reg,

	.cache_type = REGCACHE_RBTREE,
	.use_single_पढ़ो = true,
	.use_single_ग_लिखो = true,
पूर्ण;

अटल स्थिर काष्ठा regmap_irq twl6040_irqs[] = अणु
	अणु .reg_offset = 0, .mask = TWL6040_THINT, पूर्ण,
	अणु .reg_offset = 0, .mask = TWL6040_PLUGINT | TWL6040_UNPLUGINT, पूर्ण,
	अणु .reg_offset = 0, .mask = TWL6040_HOOKINT, पूर्ण,
	अणु .reg_offset = 0, .mask = TWL6040_HFINT, पूर्ण,
	अणु .reg_offset = 0, .mask = TWL6040_VIBINT, पूर्ण,
	अणु .reg_offset = 0, .mask = TWL6040_READYINT, पूर्ण,
पूर्ण;

अटल काष्ठा regmap_irq_chip twl6040_irq_chip = अणु
	.name = "twl6040",
	.irqs = twl6040_irqs,
	.num_irqs = ARRAY_SIZE(twl6040_irqs),

	.num_regs = 1,
	.status_base = TWL6040_REG_INTID,
	.mask_base = TWL6040_REG_INTMR,
पूर्ण;

अटल पूर्णांक twl6040_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा device_node *node = client->dev.of_node;
	काष्ठा twl6040 *twl6040;
	काष्ठा mfd_cell *cell = शून्य;
	पूर्णांक irq, ret, children = 0;

	अगर (!node) अणु
		dev_err(&client->dev, "of node is missing\n");
		वापस -EINVAL;
	पूर्ण

	/* In order to operate correctly we need valid पूर्णांकerrupt config */
	अगर (!client->irq) अणु
		dev_err(&client->dev, "Invalid IRQ configuration\n");
		वापस -EINVAL;
	पूर्ण

	twl6040 = devm_kzalloc(&client->dev, माप(काष्ठा twl6040),
			       GFP_KERNEL);
	अगर (!twl6040)
		वापस -ENOMEM;

	twl6040->regmap = devm_regmap_init_i2c(client, &twl6040_regmap_config);
	अगर (IS_ERR(twl6040->regmap))
		वापस PTR_ERR(twl6040->regmap);

	i2c_set_clientdata(client, twl6040);

	twl6040->clk32k = devm_clk_get(&client->dev, "clk32k");
	अगर (IS_ERR(twl6040->clk32k)) अणु
		अगर (PTR_ERR(twl6040->clk32k) == -EPROBE_DEFER)
			वापस -EPROBE_DEFER;
		dev_dbg(&client->dev, "clk32k is not handled\n");
		twl6040->clk32k = शून्य;
	पूर्ण

	twl6040->mclk = devm_clk_get(&client->dev, "mclk");
	अगर (IS_ERR(twl6040->mclk)) अणु
		अगर (PTR_ERR(twl6040->mclk) == -EPROBE_DEFER)
			वापस -EPROBE_DEFER;
		dev_dbg(&client->dev, "mclk is not handled\n");
		twl6040->mclk = शून्य;
	पूर्ण

	twl6040->supplies[0].supply = "vio";
	twl6040->supplies[1].supply = "v2v1";
	ret = devm_regulator_bulk_get(&client->dev, TWL6040_NUM_SUPPLIES,
				      twl6040->supplies);
	अगर (ret != 0) अणु
		dev_err(&client->dev, "Failed to get supplies: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = regulator_bulk_enable(TWL6040_NUM_SUPPLIES, twl6040->supplies);
	अगर (ret != 0) अणु
		dev_err(&client->dev, "Failed to enable supplies: %d\n", ret);
		वापस ret;
	पूर्ण

	twl6040->dev = &client->dev;
	twl6040->irq = client->irq;

	mutex_init(&twl6040->mutex);
	init_completion(&twl6040->पढ़ोy);

	regmap_रेजिस्टर_patch(twl6040->regmap, twl6040_patch,
			      ARRAY_SIZE(twl6040_patch));

	twl6040->rev = twl6040_reg_पढ़ो(twl6040, TWL6040_REG_ASICREV);
	अगर (twl6040->rev < 0) अणु
		dev_err(&client->dev, "Failed to read revision register: %d\n",
			twl6040->rev);
		ret = twl6040->rev;
		जाओ gpio_err;
	पूर्ण

	/* ERRATA: Automatic घातer-up is not possible in ES1.0 */
	अगर (twl6040_get_revid(twl6040) > TWL6040_REV_ES1_0)
		twl6040->audpwron = of_get_named_gpio(node,
						      "ti,audpwron-gpio", 0);
	अन्यथा
		twl6040->audpwron = -EINVAL;

	अगर (gpio_is_valid(twl6040->audpwron)) अणु
		ret = devm_gpio_request_one(&client->dev, twl6040->audpwron,
					    GPIOF_OUT_INIT_LOW, "audpwron");
		अगर (ret)
			जाओ gpio_err;

		/* Clear any pending पूर्णांकerrupt */
		twl6040_reg_पढ़ो(twl6040, TWL6040_REG_INTID);
	पूर्ण

	ret = regmap_add_irq_chip(twl6040->regmap, twl6040->irq, IRQF_ONESHOT,
				  0, &twl6040_irq_chip, &twl6040->irq_data);
	अगर (ret < 0)
		जाओ gpio_err;

	twl6040->irq_पढ़ोy = regmap_irq_get_virq(twl6040->irq_data,
						 TWL6040_IRQ_READY);
	twl6040->irq_th = regmap_irq_get_virq(twl6040->irq_data,
					      TWL6040_IRQ_TH);

	ret = devm_request_thपढ़ोed_irq(twl6040->dev, twl6040->irq_पढ़ोy, शून्य,
					twl6040_पढ़ोyपूर्णांक_handler, IRQF_ONESHOT,
					"twl6040_irq_ready", twl6040);
	अगर (ret) अणु
		dev_err(twl6040->dev, "READY IRQ request failed: %d\n", ret);
		जाओ पढ़ोyirq_err;
	पूर्ण

	ret = devm_request_thपढ़ोed_irq(twl6040->dev, twl6040->irq_th, शून्य,
					twl6040_thपूर्णांक_handler, IRQF_ONESHOT,
					"twl6040_irq_th", twl6040);
	अगर (ret) अणु
		dev_err(twl6040->dev, "Thermal IRQ request failed: %d\n", ret);
		जाओ पढ़ोyirq_err;
	पूर्ण

	/*
	 * The मुख्य functionality of twl6040 to provide audio on OMAP4+ प्रणालीs.
	 * We can add the ASoC codec child whenever this driver has been loaded.
	 */
	irq = regmap_irq_get_virq(twl6040->irq_data, TWL6040_IRQ_PLUG);
	cell = &twl6040->cells[children];
	cell->name = "twl6040-codec";
	twl6040_codec_rsrc[0].start = irq;
	twl6040_codec_rsrc[0].end = irq;
	cell->resources = twl6040_codec_rsrc;
	cell->num_resources = ARRAY_SIZE(twl6040_codec_rsrc);
	children++;

	/* Vibra input driver support */
	अगर (twl6040_has_vibra(node)) अणु
		irq = regmap_irq_get_virq(twl6040->irq_data, TWL6040_IRQ_VIB);

		cell = &twl6040->cells[children];
		cell->name = "twl6040-vibra";
		twl6040_vibra_rsrc[0].start = irq;
		twl6040_vibra_rsrc[0].end = irq;
		cell->resources = twl6040_vibra_rsrc;
		cell->num_resources = ARRAY_SIZE(twl6040_vibra_rsrc);
		children++;
	पूर्ण

	/* GPO support */
	cell = &twl6040->cells[children];
	cell->name = "twl6040-gpo";
	children++;

	/* PDM घड़ी support  */
	cell = &twl6040->cells[children];
	cell->name = "twl6040-pdmclk";
	children++;

	/* The chip is घातered करोwn so mark regmap to cache only and dirty */
	regcache_cache_only(twl6040->regmap, true);
	regcache_mark_dirty(twl6040->regmap);

	ret = mfd_add_devices(&client->dev, -1, twl6040->cells, children,
			      शून्य, 0, शून्य);
	अगर (ret)
		जाओ पढ़ोyirq_err;

	वापस 0;

पढ़ोyirq_err:
	regmap_del_irq_chip(twl6040->irq, twl6040->irq_data);
gpio_err:
	regulator_bulk_disable(TWL6040_NUM_SUPPLIES, twl6040->supplies);
	वापस ret;
पूर्ण

अटल पूर्णांक twl6040_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा twl6040 *twl6040 = i2c_get_clientdata(client);

	अगर (twl6040->घातer_count)
		twl6040_घातer(twl6040, 0);

	regmap_del_irq_chip(twl6040->irq, twl6040->irq_data);

	mfd_हटाओ_devices(&client->dev);

	regulator_bulk_disable(TWL6040_NUM_SUPPLIES, twl6040->supplies);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id twl6040_i2c_id[] = अणु
	अणु "twl6040", 0, पूर्ण,
	अणु "twl6041", 0, पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, twl6040_i2c_id);

अटल काष्ठा i2c_driver twl6040_driver = अणु
	.driver = अणु
		.name = "twl6040",
	पूर्ण,
	.probe		= twl6040_probe,
	.हटाओ		= twl6040_हटाओ,
	.id_table	= twl6040_i2c_id,
पूर्ण;

module_i2c_driver(twl6040_driver);

MODULE_DESCRIPTION("TWL6040 MFD");
MODULE_AUTHOR("Misael Lopez Cruz <misael.lopez@ti.com>");
MODULE_AUTHOR("Jorge Eduardo Candelaria <jorge.candelaria@ti.com>");
MODULE_LICENSE("GPL");
