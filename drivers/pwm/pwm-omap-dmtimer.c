<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2015 Neil Armstrong <narmstrong@baylibre.com>
 * Copyright (c) 2014 Joachim Eastwood <manabian@gmail.com>
 * Copyright (c) 2012 NeilBrown <neilb@suse.de>
 * Heavily based on earlier code which is:
 * Copyright (c) 2010 Grant Erickson <marathon96@gmail.com>
 *
 * Also based on pwm-samsung.c
 *
 * Description:
 *   This file is the core OMAP support क्रम the generic, Linux
 *   PWM driver / controller, using the OMAP's dual-mode समयrs
 *   with a समयr counter that goes up. When it overflows it माला_लो
 *   reloaded with the load value and the pwm output goes up.
 *   When counter matches with match रेजिस्टर, the output goes करोwn.
 *   Reference Manual: https://www.ti.com/lit/ug/spruh73q/spruh73q.pdf
 *
 * Limitations:
 * - When PWM is stopped, समयr counter माला_लो stopped immediately. This
 *   करोesn't allow the current PWM period to complete and stops abruptly.
 * - When PWM is running and changing both duty cycle and period,
 *   we cannot prevent in software that the output might produce
 *   a period with mixed settings. Especially when period/duty_cyle
 *   is updated जबतक the pwm pin is high, current pwm period/duty_cycle
 *   can get updated as below based on the current समयr counter:
 *   	- period क्रम current cycle =  current_period + new period
 *   	- duty_cycle क्रम current period = current period + new duty_cycle.
 * - PWM OMAP DM समयr cannot change the polarity when pwm is active. When
 *   user requests a change in polarity when in active state:
 *	- PWM is stopped abruptly(without completing the current cycle)
 *	- Polarity is changed
 *	- A fresh cycle is started.
 */

#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <घड़ीsource/समयr-ti-dm.h>
#समावेश <linux/platक्रमm_data/dmसमयr-omap.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/pwm.h>
#समावेश <linux/slab.h>
#समावेश <linux/समय.स>

#घोषणा DM_TIMER_LOAD_MIN 0xfffffffe
#घोषणा DM_TIMER_MAX      0xffffffff

/**
 * काष्ठा pwm_omap_dmसमयr_chip - Structure representing a pwm chip
 *				  corresponding to omap dmसमयr.
 * @chip:		PWM chip काष्ठाure representing PWM controller
 * @mutex:		Mutex to protect pwm apply state
 * @dm_समयr:		Poपूर्णांकer to omap dm समयr.
 * @pdata:		Poपूर्णांकer to omap dm समयr ops.
 * @dm_समयr_pdev:	Poपूर्णांकer to omap dm समयr platक्रमm device
 */
काष्ठा pwm_omap_dmसमयr_chip अणु
	काष्ठा pwm_chip chip;
	/* Mutex to protect pwm apply state */
	काष्ठा mutex mutex;
	काष्ठा omap_dm_समयr *dm_समयr;
	स्थिर काष्ठा omap_dm_समयr_ops *pdata;
	काष्ठा platक्रमm_device *dm_समयr_pdev;
पूर्ण;

अटल अंतरभूत काष्ठा pwm_omap_dmसमयr_chip *
to_pwm_omap_dmसमयr_chip(काष्ठा pwm_chip *chip)
अणु
	वापस container_of(chip, काष्ठा pwm_omap_dmसमयr_chip, chip);
पूर्ण

/**
 * pwm_omap_dmसमयr_get_घड़ी_cycles() - Get घड़ी cycles in a समय frame
 * @clk_rate:	pwm समयr घड़ी rate
 * @ns:		समय frame in nano seconds.
 *
 * Return number of घड़ी cycles in a given period(ins ns).
 */
अटल u32 pwm_omap_dmसमयr_get_घड़ी_cycles(अचिन्हित दीर्घ clk_rate, पूर्णांक ns)
अणु
	वापस DIV_ROUND_CLOSEST_ULL((u64)clk_rate * ns, NSEC_PER_SEC);
पूर्ण

/**
 * pwm_omap_dmसमयr_start() - Start the pwm omap dm समयr in pwm mode
 * @omap:	Poपूर्णांकer to pwm omap dm समयr chip
 */
अटल व्योम pwm_omap_dmसमयr_start(काष्ठा pwm_omap_dmसमयr_chip *omap)
अणु
	/*
	 * According to OMAP 4 TRM section 22.2.4.10 the counter should be
	 * started at 0xFFFFFFFE when overflow and match is used to ensure
	 * that the PWM line is toggled on the first event.
	 *
	 * Note that omap_dm_समयr_enable/disable is क्रम रेजिस्टर access and
	 * not the समयr counter itself.
	 */
	omap->pdata->enable(omap->dm_समयr);
	omap->pdata->ग_लिखो_counter(omap->dm_समयr, DM_TIMER_LOAD_MIN);
	omap->pdata->disable(omap->dm_समयr);

	omap->pdata->start(omap->dm_समयr);
पूर्ण

/**
 * pwm_omap_dmसमयr_is_enabled() -  Detect अगर the pwm is enabled.
 * @omap:	Poपूर्णांकer to pwm omap dm समयr chip
 *
 * Return true अगर pwm is enabled अन्यथा false.
 */
अटल bool pwm_omap_dmसमयr_is_enabled(काष्ठा pwm_omap_dmसमयr_chip *omap)
अणु
	u32 status;

	status = omap->pdata->get_pwm_status(omap->dm_समयr);

	वापस !!(status & OMAP_TIMER_CTRL_ST);
पूर्ण

/**
 * pwm_omap_dmसमयr_polarity() -  Detect the polarity of pwm.
 * @omap:	Poपूर्णांकer to pwm omap dm समयr chip
 *
 * Return the polarity of pwm.
 */
अटल पूर्णांक pwm_omap_dmसमयr_polarity(काष्ठा pwm_omap_dmसमयr_chip *omap)
अणु
	u32 status;

	status = omap->pdata->get_pwm_status(omap->dm_समयr);

	वापस !!(status & OMAP_TIMER_CTRL_SCPWM);
पूर्ण

/**
 * pwm_omap_dmसमयr_config() - Update the configuration of pwm omap dm समयr
 * @chip:	Poपूर्णांकer to PWM controller
 * @pwm:	Poपूर्णांकer to PWM channel
 * @duty_ns:	New duty cycle in nano seconds
 * @period_ns:	New period in nano seconds
 *
 * Return 0 अगर successfully changed the period/duty_cycle अन्यथा appropriate
 * error.
 */
अटल पूर्णांक pwm_omap_dmसमयr_config(काष्ठा pwm_chip *chip,
				   काष्ठा pwm_device *pwm,
				   पूर्णांक duty_ns, पूर्णांक period_ns)
अणु
	काष्ठा pwm_omap_dmसमयr_chip *omap = to_pwm_omap_dmसमयr_chip(chip);
	u32 period_cycles, duty_cycles;
	u32 load_value, match_value;
	अचिन्हित दीर्घ clk_rate;
	काष्ठा clk *fclk;

	dev_dbg(chip->dev, "requested duty cycle: %d ns, period: %d ns\n",
		duty_ns, period_ns);

	अगर (duty_ns == pwm_get_duty_cycle(pwm) &&
	    period_ns == pwm_get_period(pwm))
		वापस 0;

	fclk = omap->pdata->get_fclk(omap->dm_समयr);
	अगर (!fclk) अणु
		dev_err(chip->dev, "invalid pmtimer fclk\n");
		वापस -EINVAL;
	पूर्ण

	clk_rate = clk_get_rate(fclk);
	अगर (!clk_rate) अणु
		dev_err(chip->dev, "invalid pmtimer fclk rate\n");
		वापस -EINVAL;
	पूर्ण

	dev_dbg(chip->dev, "clk rate: %luHz\n", clk_rate);

	/*
	 * Calculate the appropriate load and match values based on the
	 * specअगरied period and duty cycle. The load value determines the
	 * period समय and the match value determines the duty समय.
	 *
	 * The period lasts क्रम (DM_TIMER_MAX-load_value+1) घड़ी cycles.
	 * Similarly, the active समय lasts (match_value-load_value+1) cycles.
	 * The non-active समय is the reमुख्यder: (DM_TIMER_MAX-match_value)
	 * घड़ी cycles.
	 *
	 * NOTE: It is required that: load_value <= match_value < DM_TIMER_MAX
	 *
	 * References:
	 *   OMAP4430/60/70 TRM sections 22.2.4.10 and 22.2.4.11
	 *   AM335x Sitara TRM sections 20.1.3.5 and 20.1.3.6
	 */
	period_cycles = pwm_omap_dmसमयr_get_घड़ी_cycles(clk_rate, period_ns);
	duty_cycles = pwm_omap_dmसमयr_get_घड़ी_cycles(clk_rate, duty_ns);

	अगर (period_cycles < 2) अणु
		dev_info(chip->dev,
			 "period %d ns too short for clock rate %lu Hz\n",
			 period_ns, clk_rate);
		वापस -EINVAL;
	पूर्ण

	अगर (duty_cycles < 1) अणु
		dev_dbg(chip->dev,
			"duty cycle %d ns is too short for clock rate %lu Hz\n",
			duty_ns, clk_rate);
		dev_dbg(chip->dev, "using minimum of 1 clock cycle\n");
		duty_cycles = 1;
	पूर्ण अन्यथा अगर (duty_cycles >= period_cycles) अणु
		dev_dbg(chip->dev,
			"duty cycle %d ns is too long for period %d ns at clock rate %lu Hz\n",
			duty_ns, period_ns, clk_rate);
		dev_dbg(chip->dev, "using maximum of 1 clock cycle less than period\n");
		duty_cycles = period_cycles - 1;
	पूर्ण

	dev_dbg(chip->dev, "effective duty cycle: %lld ns, period: %lld ns\n",
		DIV_ROUND_CLOSEST_ULL((u64)NSEC_PER_SEC * duty_cycles,
				      clk_rate),
		DIV_ROUND_CLOSEST_ULL((u64)NSEC_PER_SEC * period_cycles,
				      clk_rate));

	load_value = (DM_TIMER_MAX - period_cycles) + 1;
	match_value = load_value + duty_cycles - 1;

	omap->pdata->set_load(omap->dm_समयr, load_value);
	omap->pdata->set_match(omap->dm_समयr, true, match_value);

	dev_dbg(chip->dev, "load value: %#08x (%d), match value: %#08x (%d)\n",
		load_value, load_value,	match_value, match_value);

	वापस 0;
पूर्ण

/**
 * pwm_omap_dmसमयr_set_polarity() - Changes the polarity of the pwm dm समयr.
 * @chip:	Poपूर्णांकer to PWM controller
 * @pwm:	Poपूर्णांकer to PWM channel
 * @polarity:	New pwm polarity to be set
 */
अटल व्योम pwm_omap_dmसमयr_set_polarity(काष्ठा pwm_chip *chip,
					  काष्ठा pwm_device *pwm,
					  क्रमागत pwm_polarity polarity)
अणु
	काष्ठा pwm_omap_dmसमयr_chip *omap = to_pwm_omap_dmसमयr_chip(chip);
	bool enabled;

	/* Disable the PWM beक्रमe changing the polarity. */
	enabled = pwm_omap_dmसमयr_is_enabled(omap);
	अगर (enabled)
		omap->pdata->stop(omap->dm_समयr);

	omap->pdata->set_pwm(omap->dm_समयr,
			     polarity == PWM_POLARITY_INVERSED,
			     true, OMAP_TIMER_TRIGGER_OVERFLOW_AND_COMPARE,
			     true);

	अगर (enabled)
		pwm_omap_dmसमयr_start(omap);
पूर्ण

/**
 * pwm_omap_dmसमयr_apply() - Changes the state of the pwm omap dm समयr.
 * @chip:	Poपूर्णांकer to PWM controller
 * @pwm:	Poपूर्णांकer to PWM channel
 * @state:	New state to apply
 *
 * Return 0 अगर successfully changed the state अन्यथा appropriate error.
 */
अटल पूर्णांक pwm_omap_dmसमयr_apply(काष्ठा pwm_chip *chip,
				  काष्ठा pwm_device *pwm,
				  स्थिर काष्ठा pwm_state *state)
अणु
	काष्ठा pwm_omap_dmसमयr_chip *omap = to_pwm_omap_dmसमयr_chip(chip);
	पूर्णांक ret = 0;

	mutex_lock(&omap->mutex);

	अगर (pwm_omap_dmसमयr_is_enabled(omap) && !state->enabled) अणु
		omap->pdata->stop(omap->dm_समयr);
		जाओ unlock_mutex;
	पूर्ण

	अगर (pwm_omap_dmसमयr_polarity(omap) != state->polarity)
		pwm_omap_dmसमयr_set_polarity(chip, pwm, state->polarity);

	ret = pwm_omap_dmसमयr_config(chip, pwm, state->duty_cycle,
				      state->period);
	अगर (ret)
		जाओ unlock_mutex;

	अगर (!pwm_omap_dmसमयr_is_enabled(omap) && state->enabled) अणु
		omap->pdata->set_pwm(omap->dm_समयr,
				     state->polarity == PWM_POLARITY_INVERSED,
				     true,
				     OMAP_TIMER_TRIGGER_OVERFLOW_AND_COMPARE,
				     true);
		pwm_omap_dmसमयr_start(omap);
	पूर्ण

unlock_mutex:
	mutex_unlock(&omap->mutex);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा pwm_ops pwm_omap_dmसमयr_ops = अणु
	.apply = pwm_omap_dmसमयr_apply,
	.owner = THIS_MODULE,
पूर्ण;

अटल पूर्णांक pwm_omap_dmसमयr_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा dmसमयr_platक्रमm_data *समयr_pdata;
	स्थिर काष्ठा omap_dm_समयr_ops *pdata;
	काष्ठा platक्रमm_device *समयr_pdev;
	काष्ठा pwm_omap_dmसमयr_chip *omap;
	काष्ठा omap_dm_समयr *dm_समयr;
	काष्ठा device_node *समयr;
	पूर्णांक ret = 0;
	u32 v;

	समयr = of_parse_phandle(np, "ti,timers", 0);
	अगर (!समयr)
		वापस -ENODEV;

	समयr_pdev = of_find_device_by_node(समयr);
	अगर (!समयr_pdev) अणु
		dev_err(&pdev->dev, "Unable to find Timer pdev\n");
		ret = -ENODEV;
		जाओ err_find_समयr_pdev;
	पूर्ण

	समयr_pdata = dev_get_platdata(&समयr_pdev->dev);
	अगर (!समयr_pdata) अणु
		dev_dbg(&pdev->dev,
			 "dmtimer pdata structure NULL, deferring probe\n");
		ret = -EPROBE_DEFER;
		जाओ err_platdata;
	पूर्ण

	pdata = समयr_pdata->समयr_ops;

	अगर (!pdata || !pdata->request_by_node ||
	    !pdata->मुक्त ||
	    !pdata->enable ||
	    !pdata->disable ||
	    !pdata->get_fclk ||
	    !pdata->start ||
	    !pdata->stop ||
	    !pdata->set_load ||
	    !pdata->set_match ||
	    !pdata->set_pwm ||
	    !pdata->get_pwm_status ||
	    !pdata->set_prescaler ||
	    !pdata->ग_लिखो_counter) अणु
		dev_err(&pdev->dev, "Incomplete dmtimer pdata structure\n");
		ret = -EINVAL;
		जाओ err_platdata;
	पूर्ण

	अगर (!of_get_property(समयr, "ti,timer-pwm", शून्य)) अणु
		dev_err(&pdev->dev, "Missing ti,timer-pwm capability\n");
		ret = -ENODEV;
		जाओ err_समयr_property;
	पूर्ण

	dm_समयr = pdata->request_by_node(समयr);
	अगर (!dm_समयr) अणु
		ret = -EPROBE_DEFER;
		जाओ err_request_समयr;
	पूर्ण

	omap = devm_kzalloc(&pdev->dev, माप(*omap), GFP_KERNEL);
	अगर (!omap) अणु
		ret = -ENOMEM;
		जाओ err_alloc_omap;
	पूर्ण

	omap->pdata = pdata;
	omap->dm_समयr = dm_समयr;
	omap->dm_समयr_pdev = समयr_pdev;

	/*
	 * Ensure that the समयr is stopped beक्रमe we allow PWM core to call
	 * pwm_enable.
	 */
	अगर (pm_runसमय_active(&omap->dm_समयr_pdev->dev))
		omap->pdata->stop(omap->dm_समयr);

	अगर (!of_property_पढ़ो_u32(pdev->dev.of_node, "ti,prescaler", &v))
		omap->pdata->set_prescaler(omap->dm_समयr, v);

	/* setup dmसमयr घड़ी source */
	अगर (!of_property_पढ़ो_u32(pdev->dev.of_node, "ti,clock-source", &v))
		omap->pdata->set_source(omap->dm_समयr, v);

	omap->chip.dev = &pdev->dev;
	omap->chip.ops = &pwm_omap_dmसमयr_ops;
	omap->chip.npwm = 1;
	omap->chip.of_xlate = of_pwm_xlate_with_flags;
	omap->chip.of_pwm_n_cells = 3;

	mutex_init(&omap->mutex);

	ret = pwmchip_add(&omap->chip);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "failed to register PWM\n");
		जाओ err_pwmchip_add;
	पूर्ण

	of_node_put(समयr);

	platक्रमm_set_drvdata(pdev, omap);

	वापस 0;

err_pwmchip_add:

	/*
	 * *omap is allocated using devm_kzalloc,
	 * so no मुक्त necessary here
	 */
err_alloc_omap:

	pdata->मुक्त(dm_समयr);
err_request_समयr:

err_समयr_property:
err_platdata:

	put_device(&समयr_pdev->dev);
err_find_समयr_pdev:

	of_node_put(समयr);

	वापस ret;
पूर्ण

अटल पूर्णांक pwm_omap_dmसमयr_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pwm_omap_dmसमयr_chip *omap = platक्रमm_get_drvdata(pdev);
	पूर्णांक ret;

	ret = pwmchip_हटाओ(&omap->chip);
	अगर (ret)
		वापस ret;

	अगर (pm_runसमय_active(&omap->dm_समयr_pdev->dev))
		omap->pdata->stop(omap->dm_समयr);

	omap->pdata->मुक्त(omap->dm_समयr);

	put_device(&omap->dm_समयr_pdev->dev);

	mutex_destroy(&omap->mutex);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id pwm_omap_dmसमयr_of_match[] = अणु
	अणु.compatible = "ti,omap-dmtimer-pwm"पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, pwm_omap_dmसमयr_of_match);

अटल काष्ठा platक्रमm_driver pwm_omap_dmसमयr_driver = अणु
	.driver = अणु
		.name = "omap-dmtimer-pwm",
		.of_match_table = of_match_ptr(pwm_omap_dmसमयr_of_match),
	पूर्ण,
	.probe = pwm_omap_dmसमयr_probe,
	.हटाओ	= pwm_omap_dmसमयr_हटाओ,
पूर्ण;
module_platक्रमm_driver(pwm_omap_dmसमयr_driver);

MODULE_AUTHOR("Grant Erickson <marathon96@gmail.com>");
MODULE_AUTHOR("NeilBrown <neilb@suse.de>");
MODULE_AUTHOR("Neil Armstrong <narmstrong@baylibre.com>");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("OMAP PWM Driver using Dual-mode Timers");
