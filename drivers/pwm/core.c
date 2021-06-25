<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Generic pwmlib implementation
 *
 * Copyright (C) 2011 Sascha Hauer <s.hauer@pengutronix.de>
 * Copyright (C) 2011-2012 Avionic Design GmbH
 */

#समावेश <linux/acpi.h>
#समावेश <linux/module.h>
#समावेश <linux/pwm.h>
#समावेश <linux/radix-tree.h>
#समावेश <linux/list.h>
#समावेश <linux/mutex.h>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/device.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/seq_file.h>

#समावेश <dt-bindings/pwm/pwm.h>

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/pwm.h>

#घोषणा MAX_PWMS 1024

अटल DEFINE_MUTEX(pwm_lookup_lock);
अटल LIST_HEAD(pwm_lookup_list);
अटल DEFINE_MUTEX(pwm_lock);
अटल LIST_HEAD(pwm_chips);
अटल DECLARE_BITMAP(allocated_pwms, MAX_PWMS);
अटल RADIX_TREE(pwm_tree, GFP_KERNEL);

अटल काष्ठा pwm_device *pwm_to_device(अचिन्हित पूर्णांक pwm)
अणु
	वापस radix_tree_lookup(&pwm_tree, pwm);
पूर्ण

अटल पूर्णांक alloc_pwms(अचिन्हित पूर्णांक count)
अणु
	अचिन्हित पूर्णांक start;

	start = biपंचांगap_find_next_zero_area(allocated_pwms, MAX_PWMS, 0,
					   count, 0);

	अगर (start + count > MAX_PWMS)
		वापस -ENOSPC;

	वापस start;
पूर्ण

अटल व्योम मुक्त_pwms(काष्ठा pwm_chip *chip)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < chip->npwm; i++) अणु
		काष्ठा pwm_device *pwm = &chip->pwms[i];

		radix_tree_delete(&pwm_tree, pwm->pwm);
	पूर्ण

	biपंचांगap_clear(allocated_pwms, chip->base, chip->npwm);

	kमुक्त(chip->pwms);
	chip->pwms = शून्य;
पूर्ण

अटल काष्ठा pwm_chip *pwmchip_find_by_name(स्थिर अक्षर *name)
अणु
	काष्ठा pwm_chip *chip;

	अगर (!name)
		वापस शून्य;

	mutex_lock(&pwm_lock);

	list_क्रम_each_entry(chip, &pwm_chips, list) अणु
		स्थिर अक्षर *chip_name = dev_name(chip->dev);

		अगर (chip_name && म_भेद(chip_name, name) == 0) अणु
			mutex_unlock(&pwm_lock);
			वापस chip;
		पूर्ण
	पूर्ण

	mutex_unlock(&pwm_lock);

	वापस शून्य;
पूर्ण

अटल पूर्णांक pwm_device_request(काष्ठा pwm_device *pwm, स्थिर अक्षर *label)
अणु
	पूर्णांक err;

	अगर (test_bit(PWMF_REQUESTED, &pwm->flags))
		वापस -EBUSY;

	अगर (!try_module_get(pwm->chip->ops->owner))
		वापस -ENODEV;

	अगर (pwm->chip->ops->request) अणु
		err = pwm->chip->ops->request(pwm->chip, pwm);
		अगर (err) अणु
			module_put(pwm->chip->ops->owner);
			वापस err;
		पूर्ण
	पूर्ण

	अगर (pwm->chip->ops->get_state) अणु
		pwm->chip->ops->get_state(pwm->chip, pwm, &pwm->state);
		trace_pwm_get(pwm, &pwm->state);

		अगर (IS_ENABLED(CONFIG_PWM_DEBUG))
			pwm->last = pwm->state;
	पूर्ण

	set_bit(PWMF_REQUESTED, &pwm->flags);
	pwm->label = label;

	वापस 0;
पूर्ण

काष्ठा pwm_device *
of_pwm_xlate_with_flags(काष्ठा pwm_chip *pc, स्थिर काष्ठा of_phandle_args *args)
अणु
	काष्ठा pwm_device *pwm;

	/* check, whether the driver supports a third cell क्रम flags */
	अगर (pc->of_pwm_n_cells < 3)
		वापस ERR_PTR(-EINVAL);

	/* flags in the third cell are optional */
	अगर (args->args_count < 2)
		वापस ERR_PTR(-EINVAL);

	अगर (args->args[0] >= pc->npwm)
		वापस ERR_PTR(-EINVAL);

	pwm = pwm_request_from_chip(pc, args->args[0], शून्य);
	अगर (IS_ERR(pwm))
		वापस pwm;

	pwm->args.period = args->args[1];
	pwm->args.polarity = PWM_POLARITY_NORMAL;

	अगर (args->args_count > 2 && args->args[2] & PWM_POLARITY_INVERTED)
		pwm->args.polarity = PWM_POLARITY_INVERSED;

	वापस pwm;
पूर्ण
EXPORT_SYMBOL_GPL(of_pwm_xlate_with_flags);

अटल काष्ठा pwm_device *
of_pwm_simple_xlate(काष्ठा pwm_chip *pc, स्थिर काष्ठा of_phandle_args *args)
अणु
	काष्ठा pwm_device *pwm;

	/* sanity check driver support */
	अगर (pc->of_pwm_n_cells < 2)
		वापस ERR_PTR(-EINVAL);

	/* all cells are required */
	अगर (args->args_count != pc->of_pwm_n_cells)
		वापस ERR_PTR(-EINVAL);

	अगर (args->args[0] >= pc->npwm)
		वापस ERR_PTR(-EINVAL);

	pwm = pwm_request_from_chip(pc, args->args[0], शून्य);
	अगर (IS_ERR(pwm))
		वापस pwm;

	pwm->args.period = args->args[1];

	वापस pwm;
पूर्ण

अटल व्योम of_pwmchip_add(काष्ठा pwm_chip *chip)
अणु
	अगर (!chip->dev || !chip->dev->of_node)
		वापस;

	अगर (!chip->of_xlate) अणु
		chip->of_xlate = of_pwm_simple_xlate;
		chip->of_pwm_n_cells = 2;
	पूर्ण

	of_node_get(chip->dev->of_node);
पूर्ण

अटल व्योम of_pwmchip_हटाओ(काष्ठा pwm_chip *chip)
अणु
	अगर (chip->dev)
		of_node_put(chip->dev->of_node);
पूर्ण

/**
 * pwm_set_chip_data() - set निजी chip data क्रम a PWM
 * @pwm: PWM device
 * @data: poपूर्णांकer to chip-specअगरic data
 *
 * Returns: 0 on success or a negative error code on failure.
 */
पूर्णांक pwm_set_chip_data(काष्ठा pwm_device *pwm, व्योम *data)
अणु
	अगर (!pwm)
		वापस -EINVAL;

	pwm->chip_data = data;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(pwm_set_chip_data);

/**
 * pwm_get_chip_data() - get निजी chip data क्रम a PWM
 * @pwm: PWM device
 *
 * Returns: A poपूर्णांकer to the chip-निजी data क्रम the PWM device.
 */
व्योम *pwm_get_chip_data(काष्ठा pwm_device *pwm)
अणु
	वापस pwm ? pwm->chip_data : शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(pwm_get_chip_data);

अटल bool pwm_ops_check(स्थिर काष्ठा pwm_chip *chip)
अणु

	स्थिर काष्ठा pwm_ops *ops = chip->ops;

	/* driver supports legacy, non-atomic operation */
	अगर (ops->config && ops->enable && ops->disable) अणु
		अगर (IS_ENABLED(CONFIG_PWM_DEBUG))
			dev_warn(chip->dev,
				 "Driver needs updating to atomic API\n");

		वापस true;
	पूर्ण

	अगर (!ops->apply)
		वापस false;

	अगर (IS_ENABLED(CONFIG_PWM_DEBUG) && !ops->get_state)
		dev_warn(chip->dev,
			 "Please implement the .get_state() callback\n");

	वापस true;
पूर्ण

/**
 * pwmchip_add() - रेजिस्टर a new PWM chip
 * @chip: the PWM chip to add
 *
 * Register a new PWM chip.
 *
 * Returns: 0 on success or a negative error code on failure.
 */
पूर्णांक pwmchip_add(काष्ठा pwm_chip *chip)
अणु
	काष्ठा pwm_device *pwm;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	अगर (!chip || !chip->dev || !chip->ops || !chip->npwm)
		वापस -EINVAL;

	अगर (!pwm_ops_check(chip))
		वापस -EINVAL;

	mutex_lock(&pwm_lock);

	ret = alloc_pwms(chip->npwm);
	अगर (ret < 0)
		जाओ out;

	chip->base = ret;

	chip->pwms = kसुस्मृति(chip->npwm, माप(*pwm), GFP_KERNEL);
	अगर (!chip->pwms) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < chip->npwm; i++) अणु
		pwm = &chip->pwms[i];

		pwm->chip = chip;
		pwm->pwm = chip->base + i;
		pwm->hwpwm = i;

		radix_tree_insert(&pwm_tree, pwm->pwm, pwm);
	पूर्ण

	biपंचांगap_set(allocated_pwms, chip->base, chip->npwm);

	INIT_LIST_HEAD(&chip->list);
	list_add(&chip->list, &pwm_chips);

	ret = 0;

	अगर (IS_ENABLED(CONFIG_OF))
		of_pwmchip_add(chip);

out:
	mutex_unlock(&pwm_lock);

	अगर (!ret)
		pwmchip_sysfs_export(chip);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(pwmchip_add);

/**
 * pwmchip_हटाओ() - हटाओ a PWM chip
 * @chip: the PWM chip to हटाओ
 *
 * Removes a PWM chip. This function may वापस busy अगर the PWM chip provides
 * a PWM device that is still requested.
 *
 * Returns: 0 on success or a negative error code on failure.
 */
पूर्णांक pwmchip_हटाओ(काष्ठा pwm_chip *chip)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक ret = 0;

	pwmchip_sysfs_unexport(chip);

	mutex_lock(&pwm_lock);

	क्रम (i = 0; i < chip->npwm; i++) अणु
		काष्ठा pwm_device *pwm = &chip->pwms[i];

		अगर (test_bit(PWMF_REQUESTED, &pwm->flags)) अणु
			ret = -EBUSY;
			जाओ out;
		पूर्ण
	पूर्ण

	list_del_init(&chip->list);

	अगर (IS_ENABLED(CONFIG_OF))
		of_pwmchip_हटाओ(chip);

	मुक्त_pwms(chip);

out:
	mutex_unlock(&pwm_lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(pwmchip_हटाओ);

/**
 * pwm_request() - request a PWM device
 * @pwm: global PWM device index
 * @label: PWM device label
 *
 * This function is deprecated, use pwm_get() instead.
 *
 * Returns: A poपूर्णांकer to a PWM device or an ERR_PTR()-encoded error code on
 * failure.
 */
काष्ठा pwm_device *pwm_request(पूर्णांक pwm, स्थिर अक्षर *label)
अणु
	काष्ठा pwm_device *dev;
	पूर्णांक err;

	अगर (pwm < 0 || pwm >= MAX_PWMS)
		वापस ERR_PTR(-EINVAL);

	mutex_lock(&pwm_lock);

	dev = pwm_to_device(pwm);
	अगर (!dev) अणु
		dev = ERR_PTR(-EPROBE_DEFER);
		जाओ out;
	पूर्ण

	err = pwm_device_request(dev, label);
	अगर (err < 0)
		dev = ERR_PTR(err);

out:
	mutex_unlock(&pwm_lock);

	वापस dev;
पूर्ण
EXPORT_SYMBOL_GPL(pwm_request);

/**
 * pwm_request_from_chip() - request a PWM device relative to a PWM chip
 * @chip: PWM chip
 * @index: per-chip index of the PWM to request
 * @label: a literal description string of this PWM
 *
 * Returns: A poपूर्णांकer to the PWM device at the given index of the given PWM
 * chip. A negative error code is वापसed अगर the index is not valid क्रम the
 * specअगरied PWM chip or अगर the PWM device cannot be requested.
 */
काष्ठा pwm_device *pwm_request_from_chip(काष्ठा pwm_chip *chip,
					 अचिन्हित पूर्णांक index,
					 स्थिर अक्षर *label)
अणु
	काष्ठा pwm_device *pwm;
	पूर्णांक err;

	अगर (!chip || index >= chip->npwm)
		वापस ERR_PTR(-EINVAL);

	mutex_lock(&pwm_lock);
	pwm = &chip->pwms[index];

	err = pwm_device_request(pwm, label);
	अगर (err < 0)
		pwm = ERR_PTR(err);

	mutex_unlock(&pwm_lock);
	वापस pwm;
पूर्ण
EXPORT_SYMBOL_GPL(pwm_request_from_chip);

/**
 * pwm_मुक्त() - मुक्त a PWM device
 * @pwm: PWM device
 *
 * This function is deprecated, use pwm_put() instead.
 */
व्योम pwm_मुक्त(काष्ठा pwm_device *pwm)
अणु
	pwm_put(pwm);
पूर्ण
EXPORT_SYMBOL_GPL(pwm_मुक्त);

अटल व्योम pwm_apply_state_debug(काष्ठा pwm_device *pwm,
				  स्थिर काष्ठा pwm_state *state)
अणु
	काष्ठा pwm_state *last = &pwm->last;
	काष्ठा pwm_chip *chip = pwm->chip;
	काष्ठा pwm_state s1, s2;
	पूर्णांक err;

	अगर (!IS_ENABLED(CONFIG_PWM_DEBUG))
		वापस;

	/* No reasonable diagnosis possible without .get_state() */
	अगर (!chip->ops->get_state)
		वापस;

	/*
	 * *state was just applied. Read out the hardware state and करो some
	 * checks.
	 */

	chip->ops->get_state(chip, pwm, &s1);
	trace_pwm_get(pwm, &s1);

	/*
	 * The lowlevel driver either ignored .polarity (which is a bug) or as
	 * best efक्रमt inverted .polarity and fixed .duty_cycle respectively.
	 * Unकरो this inversion and fixup क्रम further tests.
	 */
	अगर (s1.enabled && s1.polarity != state->polarity) अणु
		s2.polarity = state->polarity;
		s2.duty_cycle = s1.period - s1.duty_cycle;
		s2.period = s1.period;
		s2.enabled = s1.enabled;
	पूर्ण अन्यथा अणु
		s2 = s1;
	पूर्ण

	अगर (s2.polarity != state->polarity &&
	    state->duty_cycle < state->period)
		dev_warn(chip->dev, ".apply ignored .polarity\n");

	अगर (state->enabled &&
	    last->polarity == state->polarity &&
	    last->period > s2.period &&
	    last->period <= state->period)
		dev_warn(chip->dev,
			 ".apply didn't pick the best available period (requested: %llu, applied: %llu, possible: %llu)\n",
			 state->period, s2.period, last->period);

	अगर (state->enabled && state->period < s2.period)
		dev_warn(chip->dev,
			 ".apply is supposed to round down period (requested: %llu, applied: %llu)\n",
			 state->period, s2.period);

	अगर (state->enabled &&
	    last->polarity == state->polarity &&
	    last->period == s2.period &&
	    last->duty_cycle > s2.duty_cycle &&
	    last->duty_cycle <= state->duty_cycle)
		dev_warn(chip->dev,
			 ".apply didn't pick the best available duty cycle (requested: %llu/%llu, applied: %llu/%llu, possible: %llu/%llu)\n",
			 state->duty_cycle, state->period,
			 s2.duty_cycle, s2.period,
			 last->duty_cycle, last->period);

	अगर (state->enabled && state->duty_cycle < s2.duty_cycle)
		dev_warn(chip->dev,
			 ".apply is supposed to round down duty_cycle (requested: %llu/%llu, applied: %llu/%llu)\n",
			 state->duty_cycle, state->period,
			 s2.duty_cycle, s2.period);

	अगर (!state->enabled && s2.enabled && s2.duty_cycle > 0)
		dev_warn(chip->dev,
			 "requested disabled, but yielded enabled with duty > 0\n");

	/* reapply the state that the driver reported being configured. */
	err = chip->ops->apply(chip, pwm, &s1);
	अगर (err) अणु
		*last = s1;
		dev_err(chip->dev, "failed to reapply current setting\n");
		वापस;
	पूर्ण

	trace_pwm_apply(pwm, &s1);

	chip->ops->get_state(chip, pwm, last);
	trace_pwm_get(pwm, last);

	/* reapplication of the current state should give an exact match */
	अगर (s1.enabled != last->enabled ||
	    s1.polarity != last->polarity ||
	    (s1.enabled && s1.period != last->period) ||
	    (s1.enabled && s1.duty_cycle != last->duty_cycle)) अणु
		dev_err(chip->dev,
			".apply is not idempotent (ena=%d pol=%d %llu/%llu) -> (ena=%d pol=%d %llu/%llu)\n",
			s1.enabled, s1.polarity, s1.duty_cycle, s1.period,
			last->enabled, last->polarity, last->duty_cycle,
			last->period);
	पूर्ण
पूर्ण

/**
 * pwm_apply_state() - atomically apply a new state to a PWM device
 * @pwm: PWM device
 * @state: new state to apply
 */
पूर्णांक pwm_apply_state(काष्ठा pwm_device *pwm, स्थिर काष्ठा pwm_state *state)
अणु
	काष्ठा pwm_chip *chip;
	पूर्णांक err;

	अगर (!pwm || !state || !state->period ||
	    state->duty_cycle > state->period)
		वापस -EINVAL;

	chip = pwm->chip;

	अगर (state->period == pwm->state.period &&
	    state->duty_cycle == pwm->state.duty_cycle &&
	    state->polarity == pwm->state.polarity &&
	    state->enabled == pwm->state.enabled)
		वापस 0;

	अगर (chip->ops->apply) अणु
		err = chip->ops->apply(chip, pwm, state);
		अगर (err)
			वापस err;

		trace_pwm_apply(pwm, state);

		pwm->state = *state;

		/*
		 * only करो this after pwm->state was applied as some
		 * implementations of .get_state depend on this
		 */
		pwm_apply_state_debug(pwm, state);
	पूर्ण अन्यथा अणु
		/*
		 * FIXME: restore the initial state in हाल of error.
		 */
		अगर (state->polarity != pwm->state.polarity) अणु
			अगर (!chip->ops->set_polarity)
				वापस -EINVAL;

			/*
			 * Changing the polarity of a running PWM is
			 * only allowed when the PWM driver implements
			 * ->apply().
			 */
			अगर (pwm->state.enabled) अणु
				chip->ops->disable(chip, pwm);
				pwm->state.enabled = false;
			पूर्ण

			err = chip->ops->set_polarity(chip, pwm,
						      state->polarity);
			अगर (err)
				वापस err;

			pwm->state.polarity = state->polarity;
		पूर्ण

		अगर (state->period != pwm->state.period ||
		    state->duty_cycle != pwm->state.duty_cycle) अणु
			err = chip->ops->config(pwm->chip, pwm,
						state->duty_cycle,
						state->period);
			अगर (err)
				वापस err;

			pwm->state.duty_cycle = state->duty_cycle;
			pwm->state.period = state->period;
		पूर्ण

		अगर (state->enabled != pwm->state.enabled) अणु
			अगर (state->enabled) अणु
				err = chip->ops->enable(chip, pwm);
				अगर (err)
					वापस err;
			पूर्ण अन्यथा अणु
				chip->ops->disable(chip, pwm);
			पूर्ण

			pwm->state.enabled = state->enabled;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(pwm_apply_state);

/**
 * pwm_capture() - capture and report a PWM संकेत
 * @pwm: PWM device
 * @result: काष्ठाure to fill with capture result
 * @समयout: समय to रुको, in milliseconds, beक्रमe giving up on capture
 *
 * Returns: 0 on success or a negative error code on failure.
 */
पूर्णांक pwm_capture(काष्ठा pwm_device *pwm, काष्ठा pwm_capture *result,
		अचिन्हित दीर्घ समयout)
अणु
	पूर्णांक err;

	अगर (!pwm || !pwm->chip->ops)
		वापस -EINVAL;

	अगर (!pwm->chip->ops->capture)
		वापस -ENOSYS;

	mutex_lock(&pwm_lock);
	err = pwm->chip->ops->capture(pwm->chip, pwm, result, समयout);
	mutex_unlock(&pwm_lock);

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(pwm_capture);

/**
 * pwm_adjust_config() - adjust the current PWM config to the PWM arguments
 * @pwm: PWM device
 *
 * This function will adjust the PWM config to the PWM arguments provided
 * by the DT or PWM lookup table. This is particularly useful to adapt
 * the bootloader config to the Linux one.
 */
पूर्णांक pwm_adjust_config(काष्ठा pwm_device *pwm)
अणु
	काष्ठा pwm_state state;
	काष्ठा pwm_args pargs;

	pwm_get_args(pwm, &pargs);
	pwm_get_state(pwm, &state);

	/*
	 * If the current period is zero it means that either the PWM driver
	 * करोes not support initial state retrieval or the PWM has not yet
	 * been configured.
	 *
	 * In either हाल, we setup the new period and polarity, and assign a
	 * duty cycle of 0.
	 */
	अगर (!state.period) अणु
		state.duty_cycle = 0;
		state.period = pargs.period;
		state.polarity = pargs.polarity;

		वापस pwm_apply_state(pwm, &state);
	पूर्ण

	/*
	 * Adjust the PWM duty cycle/period based on the period value provided
	 * in PWM args.
	 */
	अगर (pargs.period != state.period) अणु
		u64 dutycycle = (u64)state.duty_cycle * pargs.period;

		करो_भाग(dutycycle, state.period);
		state.duty_cycle = dutycycle;
		state.period = pargs.period;
	पूर्ण

	/*
	 * If the polarity changed, we should also change the duty cycle.
	 */
	अगर (pargs.polarity != state.polarity) अणु
		state.polarity = pargs.polarity;
		state.duty_cycle = state.period - state.duty_cycle;
	पूर्ण

	वापस pwm_apply_state(pwm, &state);
पूर्ण
EXPORT_SYMBOL_GPL(pwm_adjust_config);

अटल काष्ठा pwm_chip *of_node_to_pwmchip(काष्ठा device_node *np)
अणु
	काष्ठा pwm_chip *chip;

	mutex_lock(&pwm_lock);

	list_क्रम_each_entry(chip, &pwm_chips, list)
		अगर (chip->dev && chip->dev->of_node == np) अणु
			mutex_unlock(&pwm_lock);
			वापस chip;
		पूर्ण

	mutex_unlock(&pwm_lock);

	वापस ERR_PTR(-EPROBE_DEFER);
पूर्ण

अटल काष्ठा device_link *pwm_device_link_add(काष्ठा device *dev,
					       काष्ठा pwm_device *pwm)
अणु
	काष्ठा device_link *dl;

	अगर (!dev) अणु
		/*
		 * No device क्रम the PWM consumer has been provided. It may
		 * impact the PM sequence ordering: the PWM supplier may get
		 * suspended beक्रमe the consumer.
		 */
		dev_warn(pwm->chip->dev,
			 "No consumer device specified to create a link to\n");
		वापस शून्य;
	पूर्ण

	dl = device_link_add(dev, pwm->chip->dev, DL_FLAG_AUTOREMOVE_CONSUMER);
	अगर (!dl) अणु
		dev_err(dev, "failed to create device link to %s\n",
			dev_name(pwm->chip->dev));
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	वापस dl;
पूर्ण

/**
 * of_pwm_get() - request a PWM via the PWM framework
 * @dev: device क्रम PWM consumer
 * @np: device node to get the PWM from
 * @con_id: consumer name
 *
 * Returns the PWM device parsed from the phandle and index specअगरied in the
 * "pwms" property of a device tree node or a negative error-code on failure.
 * Values parsed from the device tree are stored in the वापसed PWM device
 * object.
 *
 * If con_id is शून्य, the first PWM device listed in the "pwms" property will
 * be requested. Otherwise the "pwm-names" property is used to करो a reverse
 * lookup of the PWM index. This also means that the "pwm-names" property
 * becomes mandatory क्रम devices that look up the PWM device via the con_id
 * parameter.
 *
 * Returns: A poपूर्णांकer to the requested PWM device or an ERR_PTR()-encoded
 * error code on failure.
 */
काष्ठा pwm_device *of_pwm_get(काष्ठा device *dev, काष्ठा device_node *np,
			      स्थिर अक्षर *con_id)
अणु
	काष्ठा pwm_device *pwm = शून्य;
	काष्ठा of_phandle_args args;
	काष्ठा device_link *dl;
	काष्ठा pwm_chip *pc;
	पूर्णांक index = 0;
	पूर्णांक err;

	अगर (con_id) अणु
		index = of_property_match_string(np, "pwm-names", con_id);
		अगर (index < 0)
			वापस ERR_PTR(index);
	पूर्ण

	err = of_parse_phandle_with_args(np, "pwms", "#pwm-cells", index,
					 &args);
	अगर (err) अणु
		pr_err("%s(): can't parse \"pwms\" property\n", __func__);
		वापस ERR_PTR(err);
	पूर्ण

	pc = of_node_to_pwmchip(args.np);
	अगर (IS_ERR(pc)) अणु
		अगर (PTR_ERR(pc) != -EPROBE_DEFER)
			pr_err("%s(): PWM chip not found\n", __func__);

		pwm = ERR_CAST(pc);
		जाओ put;
	पूर्ण

	pwm = pc->of_xlate(pc, &args);
	अगर (IS_ERR(pwm))
		जाओ put;

	dl = pwm_device_link_add(dev, pwm);
	अगर (IS_ERR(dl)) अणु
		/* of_xlate ended up calling pwm_request_from_chip() */
		pwm_मुक्त(pwm);
		pwm = ERR_CAST(dl);
		जाओ put;
	पूर्ण

	/*
	 * If a consumer name was not given, try to look it up from the
	 * "pwm-names" property अगर it exists. Otherwise use the name of
	 * the user device node.
	 */
	अगर (!con_id) अणु
		err = of_property_पढ़ो_string_index(np, "pwm-names", index,
						    &con_id);
		अगर (err < 0)
			con_id = np->name;
	पूर्ण

	pwm->label = con_id;

put:
	of_node_put(args.np);

	वापस pwm;
पूर्ण
EXPORT_SYMBOL_GPL(of_pwm_get);

#अगर IS_ENABLED(CONFIG_ACPI)
अटल काष्ठा pwm_chip *device_to_pwmchip(काष्ठा device *dev)
अणु
	काष्ठा pwm_chip *chip;

	mutex_lock(&pwm_lock);

	list_क्रम_each_entry(chip, &pwm_chips, list) अणु
		काष्ठा acpi_device *adev = ACPI_COMPANION(chip->dev);

		अगर ((chip->dev == dev) || (adev && &adev->dev == dev)) अणु
			mutex_unlock(&pwm_lock);
			वापस chip;
		पूर्ण
	पूर्ण

	mutex_unlock(&pwm_lock);

	वापस ERR_PTR(-EPROBE_DEFER);
पूर्ण
#पूर्ण_अगर

/**
 * acpi_pwm_get() - request a PWM via parsing "pwms" property in ACPI
 * @fwnode: firmware node to get the "pwm" property from
 *
 * Returns the PWM device parsed from the fwnode and index specअगरied in the
 * "pwms" property or a negative error-code on failure.
 * Values parsed from the device tree are stored in the वापसed PWM device
 * object.
 *
 * This is analogous to of_pwm_get() except con_id is not yet supported.
 * ACPI entries must look like
 * Package () अणु"pwms", Package ()
 *     अणु <PWM device reference>, <PWM index>, <PWM period> [, <PWM flags>]पूर्णपूर्ण
 *
 * Returns: A poपूर्णांकer to the requested PWM device or an ERR_PTR()-encoded
 * error code on failure.
 */
अटल काष्ठा pwm_device *acpi_pwm_get(काष्ठा fwnode_handle *fwnode)
अणु
	काष्ठा pwm_device *pwm = ERR_PTR(-ENODEV);
#अगर IS_ENABLED(CONFIG_ACPI)
	काष्ठा fwnode_reference_args args;
	काष्ठा acpi_device *acpi;
	काष्ठा pwm_chip *chip;
	पूर्णांक ret;

	स_रखो(&args, 0, माप(args));

	ret = __acpi_node_get_property_reference(fwnode, "pwms", 0, 3, &args);
	अगर (ret < 0)
		वापस ERR_PTR(ret);

	acpi = to_acpi_device_node(args.fwnode);
	अगर (!acpi)
		वापस ERR_PTR(-EINVAL);

	अगर (args.nargs < 2)
		वापस ERR_PTR(-EPROTO);

	chip = device_to_pwmchip(&acpi->dev);
	अगर (IS_ERR(chip))
		वापस ERR_CAST(chip);

	pwm = pwm_request_from_chip(chip, args.args[0], शून्य);
	अगर (IS_ERR(pwm))
		वापस pwm;

	pwm->args.period = args.args[1];
	pwm->args.polarity = PWM_POLARITY_NORMAL;

	अगर (args.nargs > 2 && args.args[2] & PWM_POLARITY_INVERTED)
		pwm->args.polarity = PWM_POLARITY_INVERSED;
#पूर्ण_अगर

	वापस pwm;
पूर्ण

/**
 * pwm_add_table() - रेजिस्टर PWM device consumers
 * @table: array of consumers to रेजिस्टर
 * @num: number of consumers in table
 */
व्योम pwm_add_table(काष्ठा pwm_lookup *table, माप_प्रकार num)
अणु
	mutex_lock(&pwm_lookup_lock);

	जबतक (num--) अणु
		list_add_tail(&table->list, &pwm_lookup_list);
		table++;
	पूर्ण

	mutex_unlock(&pwm_lookup_lock);
पूर्ण

/**
 * pwm_हटाओ_table() - unरेजिस्टर PWM device consumers
 * @table: array of consumers to unरेजिस्टर
 * @num: number of consumers in table
 */
व्योम pwm_हटाओ_table(काष्ठा pwm_lookup *table, माप_प्रकार num)
अणु
	mutex_lock(&pwm_lookup_lock);

	जबतक (num--) अणु
		list_del(&table->list);
		table++;
	पूर्ण

	mutex_unlock(&pwm_lookup_lock);
पूर्ण

/**
 * pwm_get() - look up and request a PWM device
 * @dev: device क्रम PWM consumer
 * @con_id: consumer name
 *
 * Lookup is first attempted using DT. If the device was not instantiated from
 * a device tree, a PWM chip and a relative index is looked up via a table
 * supplied by board setup code (see pwm_add_table()).
 *
 * Once a PWM chip has been found the specअगरied PWM device will be requested
 * and is पढ़ोy to be used.
 *
 * Returns: A poपूर्णांकer to the requested PWM device or an ERR_PTR()-encoded
 * error code on failure.
 */
काष्ठा pwm_device *pwm_get(काष्ठा device *dev, स्थिर अक्षर *con_id)
अणु
	स्थिर अक्षर *dev_id = dev ? dev_name(dev) : शून्य;
	काष्ठा pwm_device *pwm;
	काष्ठा pwm_chip *chip;
	काष्ठा device_link *dl;
	अचिन्हित पूर्णांक best = 0;
	काष्ठा pwm_lookup *p, *chosen = शून्य;
	अचिन्हित पूर्णांक match;
	पूर्णांक err;

	/* look up via DT first */
	अगर (IS_ENABLED(CONFIG_OF) && dev && dev->of_node)
		वापस of_pwm_get(dev, dev->of_node, con_id);

	/* then lookup via ACPI */
	अगर (dev && is_acpi_node(dev->fwnode)) अणु
		pwm = acpi_pwm_get(dev->fwnode);
		अगर (!IS_ERR(pwm) || PTR_ERR(pwm) != -ENOENT)
			वापस pwm;
	पूर्ण

	/*
	 * We look up the provider in the अटल table typically provided by
	 * board setup code. We first try to lookup the consumer device by
	 * name. If the consumer device was passed in as शून्य or अगर no match
	 * was found, we try to find the consumer by directly looking it up
	 * by name.
	 *
	 * If a match is found, the provider PWM chip is looked up by name
	 * and a PWM device is requested using the PWM device per-chip index.
	 *
	 * The lookup algorithm was shamelessly taken from the घड़ी
	 * framework:
	 *
	 * We करो slightly fuzzy matching here:
	 *  An entry with a शून्य ID is assumed to be a wildcard.
	 *  If an entry has a device ID, it must match
	 *  If an entry has a connection ID, it must match
	 * Then we take the most specअगरic entry - with the following order
	 * of precedence: dev+con > dev only > con only.
	 */
	mutex_lock(&pwm_lookup_lock);

	list_क्रम_each_entry(p, &pwm_lookup_list, list) अणु
		match = 0;

		अगर (p->dev_id) अणु
			अगर (!dev_id || म_भेद(p->dev_id, dev_id))
				जारी;

			match += 2;
		पूर्ण

		अगर (p->con_id) अणु
			अगर (!con_id || म_भेद(p->con_id, con_id))
				जारी;

			match += 1;
		पूर्ण

		अगर (match > best) अणु
			chosen = p;

			अगर (match != 3)
				best = match;
			अन्यथा
				अवरोध;
		पूर्ण
	पूर्ण

	mutex_unlock(&pwm_lookup_lock);

	अगर (!chosen)
		वापस ERR_PTR(-ENODEV);

	chip = pwmchip_find_by_name(chosen->provider);

	/*
	 * If the lookup entry specअगरies a module, load the module and retry
	 * the PWM chip lookup. This can be used to work around driver load
	 * ordering issues अगर driver's can't be made to properly support the
	 * deferred probe mechanism.
	 */
	अगर (!chip && chosen->module) अणु
		err = request_module(chosen->module);
		अगर (err == 0)
			chip = pwmchip_find_by_name(chosen->provider);
	पूर्ण

	अगर (!chip)
		वापस ERR_PTR(-EPROBE_DEFER);

	pwm = pwm_request_from_chip(chip, chosen->index, con_id ?: dev_id);
	अगर (IS_ERR(pwm))
		वापस pwm;

	dl = pwm_device_link_add(dev, pwm);
	अगर (IS_ERR(dl)) अणु
		pwm_मुक्त(pwm);
		वापस ERR_CAST(dl);
	पूर्ण

	pwm->args.period = chosen->period;
	pwm->args.polarity = chosen->polarity;

	वापस pwm;
पूर्ण
EXPORT_SYMBOL_GPL(pwm_get);

/**
 * pwm_put() - release a PWM device
 * @pwm: PWM device
 */
व्योम pwm_put(काष्ठा pwm_device *pwm)
अणु
	अगर (!pwm)
		वापस;

	mutex_lock(&pwm_lock);

	अगर (!test_and_clear_bit(PWMF_REQUESTED, &pwm->flags)) अणु
		pr_warn("PWM device already freed\n");
		जाओ out;
	पूर्ण

	अगर (pwm->chip->ops->मुक्त)
		pwm->chip->ops->मुक्त(pwm->chip, pwm);

	pwm_set_chip_data(pwm, शून्य);
	pwm->label = शून्य;

	module_put(pwm->chip->ops->owner);
out:
	mutex_unlock(&pwm_lock);
पूर्ण
EXPORT_SYMBOL_GPL(pwm_put);

अटल व्योम devm_pwm_release(काष्ठा device *dev, व्योम *res)
अणु
	pwm_put(*(काष्ठा pwm_device **)res);
पूर्ण

/**
 * devm_pwm_get() - resource managed pwm_get()
 * @dev: device क्रम PWM consumer
 * @con_id: consumer name
 *
 * This function perक्रमms like pwm_get() but the acquired PWM device will
 * स्वतःmatically be released on driver detach.
 *
 * Returns: A poपूर्णांकer to the requested PWM device or an ERR_PTR()-encoded
 * error code on failure.
 */
काष्ठा pwm_device *devm_pwm_get(काष्ठा device *dev, स्थिर अक्षर *con_id)
अणु
	काष्ठा pwm_device **ptr, *pwm;

	ptr = devres_alloc(devm_pwm_release, माप(*ptr), GFP_KERNEL);
	अगर (!ptr)
		वापस ERR_PTR(-ENOMEM);

	pwm = pwm_get(dev, con_id);
	अगर (!IS_ERR(pwm)) अणु
		*ptr = pwm;
		devres_add(dev, ptr);
	पूर्ण अन्यथा अणु
		devres_मुक्त(ptr);
	पूर्ण

	वापस pwm;
पूर्ण
EXPORT_SYMBOL_GPL(devm_pwm_get);

/**
 * devm_of_pwm_get() - resource managed of_pwm_get()
 * @dev: device क्रम PWM consumer
 * @np: device node to get the PWM from
 * @con_id: consumer name
 *
 * This function perक्रमms like of_pwm_get() but the acquired PWM device will
 * स्वतःmatically be released on driver detach.
 *
 * Returns: A poपूर्णांकer to the requested PWM device or an ERR_PTR()-encoded
 * error code on failure.
 */
काष्ठा pwm_device *devm_of_pwm_get(काष्ठा device *dev, काष्ठा device_node *np,
				   स्थिर अक्षर *con_id)
अणु
	काष्ठा pwm_device **ptr, *pwm;

	ptr = devres_alloc(devm_pwm_release, माप(*ptr), GFP_KERNEL);
	अगर (!ptr)
		वापस ERR_PTR(-ENOMEM);

	pwm = of_pwm_get(dev, np, con_id);
	अगर (!IS_ERR(pwm)) अणु
		*ptr = pwm;
		devres_add(dev, ptr);
	पूर्ण अन्यथा अणु
		devres_मुक्त(ptr);
	पूर्ण

	वापस pwm;
पूर्ण
EXPORT_SYMBOL_GPL(devm_of_pwm_get);

/**
 * devm_fwnode_pwm_get() - request a resource managed PWM from firmware node
 * @dev: device क्रम PWM consumer
 * @fwnode: firmware node to get the PWM from
 * @con_id: consumer name
 *
 * Returns the PWM device parsed from the firmware node. See of_pwm_get() and
 * acpi_pwm_get() क्रम a detailed description.
 *
 * Returns: A poपूर्णांकer to the requested PWM device or an ERR_PTR()-encoded
 * error code on failure.
 */
काष्ठा pwm_device *devm_fwnode_pwm_get(काष्ठा device *dev,
				       काष्ठा fwnode_handle *fwnode,
				       स्थिर अक्षर *con_id)
अणु
	काष्ठा pwm_device **ptr, *pwm = ERR_PTR(-ENODEV);

	ptr = devres_alloc(devm_pwm_release, माप(*ptr), GFP_KERNEL);
	अगर (!ptr)
		वापस ERR_PTR(-ENOMEM);

	अगर (is_of_node(fwnode))
		pwm = of_pwm_get(dev, to_of_node(fwnode), con_id);
	अन्यथा अगर (is_acpi_node(fwnode))
		pwm = acpi_pwm_get(fwnode);

	अगर (!IS_ERR(pwm)) अणु
		*ptr = pwm;
		devres_add(dev, ptr);
	पूर्ण अन्यथा अणु
		devres_मुक्त(ptr);
	पूर्ण

	वापस pwm;
पूर्ण
EXPORT_SYMBOL_GPL(devm_fwnode_pwm_get);

अटल पूर्णांक devm_pwm_match(काष्ठा device *dev, व्योम *res, व्योम *data)
अणु
	काष्ठा pwm_device **p = res;

	अगर (WARN_ON(!p || !*p))
		वापस 0;

	वापस *p == data;
पूर्ण

/**
 * devm_pwm_put() - resource managed pwm_put()
 * @dev: device क्रम PWM consumer
 * @pwm: PWM device
 *
 * Release a PWM previously allocated using devm_pwm_get(). Calling this
 * function is usually not needed because devm-allocated resources are
 * स्वतःmatically released on driver detach.
 */
व्योम devm_pwm_put(काष्ठा device *dev, काष्ठा pwm_device *pwm)
अणु
	WARN_ON(devres_release(dev, devm_pwm_release, devm_pwm_match, pwm));
पूर्ण
EXPORT_SYMBOL_GPL(devm_pwm_put);

#अगर_घोषित CONFIG_DEBUG_FS
अटल व्योम pwm_dbg_show(काष्ठा pwm_chip *chip, काष्ठा seq_file *s)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < chip->npwm; i++) अणु
		काष्ठा pwm_device *pwm = &chip->pwms[i];
		काष्ठा pwm_state state;

		pwm_get_state(pwm, &state);

		seq_म_लिखो(s, " pwm-%-3d (%-20.20s):", i, pwm->label);

		अगर (test_bit(PWMF_REQUESTED, &pwm->flags))
			seq_माला_दो(s, " requested");

		अगर (state.enabled)
			seq_माला_दो(s, " enabled");

		seq_म_लिखो(s, " period: %llu ns", state.period);
		seq_म_लिखो(s, " duty: %llu ns", state.duty_cycle);
		seq_म_लिखो(s, " polarity: %s",
			   state.polarity ? "inverse" : "normal");

		seq_माला_दो(s, "\n");
	पूर्ण
पूर्ण

अटल व्योम *pwm_seq_start(काष्ठा seq_file *s, loff_t *pos)
अणु
	mutex_lock(&pwm_lock);
	s->निजी = "";

	वापस seq_list_start(&pwm_chips, *pos);
पूर्ण

अटल व्योम *pwm_seq_next(काष्ठा seq_file *s, व्योम *v, loff_t *pos)
अणु
	s->निजी = "\n";

	वापस seq_list_next(v, &pwm_chips, pos);
पूर्ण

अटल व्योम pwm_seq_stop(काष्ठा seq_file *s, व्योम *v)
अणु
	mutex_unlock(&pwm_lock);
पूर्ण

अटल पूर्णांक pwm_seq_show(काष्ठा seq_file *s, व्योम *v)
अणु
	काष्ठा pwm_chip *chip = list_entry(v, काष्ठा pwm_chip, list);

	seq_म_लिखो(s, "%s%s/%s, %d PWM device%s\n", (अक्षर *)s->निजी,
		   chip->dev->bus ? chip->dev->bus->name : "no-bus",
		   dev_name(chip->dev), chip->npwm,
		   (chip->npwm != 1) ? "s" : "");

	pwm_dbg_show(chip, s);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations pwm_debugfs_sops = अणु
	.start = pwm_seq_start,
	.next = pwm_seq_next,
	.stop = pwm_seq_stop,
	.show = pwm_seq_show,
पूर्ण;

DEFINE_SEQ_ATTRIBUTE(pwm_debugfs);

अटल पूर्णांक __init pwm_debugfs_init(व्योम)
अणु
	debugfs_create_file("pwm", S_IFREG | 0444, शून्य, शून्य,
			    &pwm_debugfs_fops);

	वापस 0;
पूर्ण
subsys_initcall(pwm_debugfs_init);
#पूर्ण_अगर /* CONFIG_DEBUG_FS */
