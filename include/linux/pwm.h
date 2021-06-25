<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_PWM_H
#घोषणा __LINUX_PWM_H

#समावेश <linux/err.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of.h>

काष्ठा pwm_capture;
काष्ठा seq_file;

काष्ठा pwm_chip;

/**
 * क्रमागत pwm_polarity - polarity of a PWM संकेत
 * @PWM_POLARITY_NORMAL: a high संकेत क्रम the duration of the duty-
 * cycle, followed by a low संकेत क्रम the reमुख्यder of the pulse
 * period
 * @PWM_POLARITY_INVERSED: a low संकेत क्रम the duration of the duty-
 * cycle, followed by a high संकेत क्रम the reमुख्यder of the pulse
 * period
 */
क्रमागत pwm_polarity अणु
	PWM_POLARITY_NORMAL,
	PWM_POLARITY_INVERSED,
पूर्ण;

/**
 * काष्ठा pwm_args - board-dependent PWM arguments
 * @period: reference period
 * @polarity: reference polarity
 *
 * This काष्ठाure describes board-dependent arguments attached to a PWM
 * device. These arguments are usually retrieved from the PWM lookup table or
 * device tree.
 *
 * Do not confuse this with the PWM state: PWM arguments represent the initial
 * configuration that users want to use on this PWM device rather than the
 * current PWM hardware state.
 */
काष्ठा pwm_args अणु
	u64 period;
	क्रमागत pwm_polarity polarity;
पूर्ण;

क्रमागत अणु
	PWMF_REQUESTED = 1 << 0,
	PWMF_EXPORTED = 1 << 1,
पूर्ण;

/*
 * काष्ठा pwm_state - state of a PWM channel
 * @period: PWM period (in nanoseconds)
 * @duty_cycle: PWM duty cycle (in nanoseconds)
 * @polarity: PWM polarity
 * @enabled: PWM enabled status
 */
काष्ठा pwm_state अणु
	u64 period;
	u64 duty_cycle;
	क्रमागत pwm_polarity polarity;
	bool enabled;
पूर्ण;

/**
 * काष्ठा pwm_device - PWM channel object
 * @label: name of the PWM device
 * @flags: flags associated with the PWM device
 * @hwpwm: per-chip relative index of the PWM device
 * @pwm: global index of the PWM device
 * @chip: PWM chip providing this PWM device
 * @chip_data: chip-निजी data associated with the PWM device
 * @args: PWM arguments
 * @state: last applied state
 * @last: last implemented state (क्रम PWM_DEBUG)
 */
काष्ठा pwm_device अणु
	स्थिर अक्षर *label;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक hwpwm;
	अचिन्हित पूर्णांक pwm;
	काष्ठा pwm_chip *chip;
	व्योम *chip_data;

	काष्ठा pwm_args args;
	काष्ठा pwm_state state;
	काष्ठा pwm_state last;
पूर्ण;

/**
 * pwm_get_state() - retrieve the current PWM state
 * @pwm: PWM device
 * @state: state to fill with the current PWM state
 *
 * The वापसed PWM state represents the state that was applied by a previous call to
 * pwm_apply_state(). Drivers may have to slightly tweak that state beक्रमe programming it to
 * hardware. If pwm_apply_state() was never called, this वापसs either the current hardware
 * state (अगर supported) or the शेष settings.
 */
अटल अंतरभूत व्योम pwm_get_state(स्थिर काष्ठा pwm_device *pwm,
				 काष्ठा pwm_state *state)
अणु
	*state = pwm->state;
पूर्ण

अटल अंतरभूत bool pwm_is_enabled(स्थिर काष्ठा pwm_device *pwm)
अणु
	काष्ठा pwm_state state;

	pwm_get_state(pwm, &state);

	वापस state.enabled;
पूर्ण

अटल अंतरभूत व्योम pwm_set_period(काष्ठा pwm_device *pwm, u64 period)
अणु
	अगर (pwm)
		pwm->state.period = period;
पूर्ण

अटल अंतरभूत u64 pwm_get_period(स्थिर काष्ठा pwm_device *pwm)
अणु
	काष्ठा pwm_state state;

	pwm_get_state(pwm, &state);

	वापस state.period;
पूर्ण

अटल अंतरभूत व्योम pwm_set_duty_cycle(काष्ठा pwm_device *pwm, अचिन्हित पूर्णांक duty)
अणु
	अगर (pwm)
		pwm->state.duty_cycle = duty;
पूर्ण

अटल अंतरभूत u64 pwm_get_duty_cycle(स्थिर काष्ठा pwm_device *pwm)
अणु
	काष्ठा pwm_state state;

	pwm_get_state(pwm, &state);

	वापस state.duty_cycle;
पूर्ण

अटल अंतरभूत क्रमागत pwm_polarity pwm_get_polarity(स्थिर काष्ठा pwm_device *pwm)
अणु
	काष्ठा pwm_state state;

	pwm_get_state(pwm, &state);

	वापस state.polarity;
पूर्ण

अटल अंतरभूत व्योम pwm_get_args(स्थिर काष्ठा pwm_device *pwm,
				काष्ठा pwm_args *args)
अणु
	*args = pwm->args;
पूर्ण

/**
 * pwm_init_state() - prepare a new state to be applied with pwm_apply_state()
 * @pwm: PWM device
 * @state: state to fill with the prepared PWM state
 *
 * This functions prepares a state that can later be tweaked and applied
 * to the PWM device with pwm_apply_state(). This is a convenient function
 * that first retrieves the current PWM state and the replaces the period
 * and polarity fields with the reference values defined in pwm->args.
 * Once the function वापसs, you can adjust the ->enabled and ->duty_cycle
 * fields according to your needs beक्रमe calling pwm_apply_state().
 *
 * ->duty_cycle is initially set to zero to aव्योम हालs where the current
 * ->duty_cycle value exceed the pwm_args->period one, which would trigger
 * an error अगर the user calls pwm_apply_state() without adjusting ->duty_cycle
 * first.
 */
अटल अंतरभूत व्योम pwm_init_state(स्थिर काष्ठा pwm_device *pwm,
				  काष्ठा pwm_state *state)
अणु
	काष्ठा pwm_args args;

	/* First get the current state. */
	pwm_get_state(pwm, state);

	/* Then fill it with the reference config */
	pwm_get_args(pwm, &args);

	state->period = args.period;
	state->polarity = args.polarity;
	state->duty_cycle = 0;
पूर्ण

/**
 * pwm_get_relative_duty_cycle() - Get a relative duty cycle value
 * @state: PWM state to extract the duty cycle from
 * @scale: target scale of the relative duty cycle
 *
 * This functions converts the असलolute duty cycle stored in @state (expressed
 * in nanosecond) पूर्णांकo a value relative to the period.
 *
 * For example अगर you want to get the duty_cycle expressed in percent, call:
 *
 * pwm_get_state(pwm, &state);
 * duty = pwm_get_relative_duty_cycle(&state, 100);
 */
अटल अंतरभूत अचिन्हित पूर्णांक
pwm_get_relative_duty_cycle(स्थिर काष्ठा pwm_state *state, अचिन्हित पूर्णांक scale)
अणु
	अगर (!state->period)
		वापस 0;

	वापस DIV_ROUND_CLOSEST_ULL((u64)state->duty_cycle * scale,
				     state->period);
पूर्ण

/**
 * pwm_set_relative_duty_cycle() - Set a relative duty cycle value
 * @state: PWM state to fill
 * @duty_cycle: relative duty cycle value
 * @scale: scale in which @duty_cycle is expressed
 *
 * This functions converts a relative पूर्णांकo an असलolute duty cycle (expressed
 * in nanoseconds), and माला_दो the result in state->duty_cycle.
 *
 * For example अगर you want to configure a 50% duty cycle, call:
 *
 * pwm_init_state(pwm, &state);
 * pwm_set_relative_duty_cycle(&state, 50, 100);
 * pwm_apply_state(pwm, &state);
 *
 * This functions वापसs -EINVAL अगर @duty_cycle and/or @scale are
 * inconsistent (@scale == 0 or @duty_cycle > @scale).
 */
अटल अंतरभूत पूर्णांक
pwm_set_relative_duty_cycle(काष्ठा pwm_state *state, अचिन्हित पूर्णांक duty_cycle,
			    अचिन्हित पूर्णांक scale)
अणु
	अगर (!scale || duty_cycle > scale)
		वापस -EINVAL;

	state->duty_cycle = DIV_ROUND_CLOSEST_ULL((u64)duty_cycle *
						  state->period,
						  scale);

	वापस 0;
पूर्ण

/**
 * काष्ठा pwm_ops - PWM controller operations
 * @request: optional hook क्रम requesting a PWM
 * @मुक्त: optional hook क्रम मुक्तing a PWM
 * @capture: capture and report PWM संकेत
 * @apply: atomically apply a new PWM config
 * @get_state: get the current PWM state. This function is only
 *	       called once per PWM device when the PWM chip is
 *	       रेजिस्टरed.
 * @owner: helps prevent removal of modules exporting active PWMs
 * @config: configure duty cycles and period length क्रम this PWM
 * @set_polarity: configure the polarity of this PWM
 * @enable: enable PWM output toggling
 * @disable: disable PWM output toggling
 */
काष्ठा pwm_ops अणु
	पूर्णांक (*request)(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm);
	व्योम (*मुक्त)(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm);
	पूर्णांक (*capture)(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm,
		       काष्ठा pwm_capture *result, अचिन्हित दीर्घ समयout);
	पूर्णांक (*apply)(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm,
		     स्थिर काष्ठा pwm_state *state);
	व्योम (*get_state)(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm,
			  काष्ठा pwm_state *state);
	काष्ठा module *owner;

	/* Only used by legacy drivers */
	पूर्णांक (*config)(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm,
		      पूर्णांक duty_ns, पूर्णांक period_ns);
	पूर्णांक (*set_polarity)(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm,
			    क्रमागत pwm_polarity polarity);
	पूर्णांक (*enable)(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm);
	व्योम (*disable)(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm);
पूर्ण;

/**
 * काष्ठा pwm_chip - असलtract a PWM controller
 * @dev: device providing the PWMs
 * @ops: callbacks क्रम this PWM controller
 * @base: number of first PWM controlled by this chip
 * @npwm: number of PWMs controlled by this chip
 * @of_xlate: request a PWM device given a device tree PWM specअगरier
 * @of_pwm_n_cells: number of cells expected in the device tree PWM specअगरier
 * @list: list node क्रम पूर्णांकernal use
 * @pwms: array of PWM devices allocated by the framework
 */
काष्ठा pwm_chip अणु
	काष्ठा device *dev;
	स्थिर काष्ठा pwm_ops *ops;
	पूर्णांक base;
	अचिन्हित पूर्णांक npwm;

	काष्ठा pwm_device * (*of_xlate)(काष्ठा pwm_chip *pc,
					स्थिर काष्ठा of_phandle_args *args);
	अचिन्हित पूर्णांक of_pwm_n_cells;

	/* only used पूर्णांकernally by the PWM framework */
	काष्ठा list_head list;
	काष्ठा pwm_device *pwms;
पूर्ण;

/**
 * काष्ठा pwm_capture - PWM capture data
 * @period: period of the PWM संकेत (in nanoseconds)
 * @duty_cycle: duty cycle of the PWM संकेत (in nanoseconds)
 */
काष्ठा pwm_capture अणु
	अचिन्हित पूर्णांक period;
	अचिन्हित पूर्णांक duty_cycle;
पूर्ण;

#अगर IS_ENABLED(CONFIG_PWM)
/* PWM user APIs */
काष्ठा pwm_device *pwm_request(पूर्णांक pwm_id, स्थिर अक्षर *label);
व्योम pwm_मुक्त(काष्ठा pwm_device *pwm);
पूर्णांक pwm_apply_state(काष्ठा pwm_device *pwm, स्थिर काष्ठा pwm_state *state);
पूर्णांक pwm_adjust_config(काष्ठा pwm_device *pwm);

/**
 * pwm_config() - change a PWM device configuration
 * @pwm: PWM device
 * @duty_ns: "on" समय (in nanoseconds)
 * @period_ns: duration (in nanoseconds) of one cycle
 *
 * Returns: 0 on success or a negative error code on failure.
 */
अटल अंतरभूत पूर्णांक pwm_config(काष्ठा pwm_device *pwm, पूर्णांक duty_ns,
			     पूर्णांक period_ns)
अणु
	काष्ठा pwm_state state;

	अगर (!pwm)
		वापस -EINVAL;

	अगर (duty_ns < 0 || period_ns < 0)
		वापस -EINVAL;

	pwm_get_state(pwm, &state);
	अगर (state.duty_cycle == duty_ns && state.period == period_ns)
		वापस 0;

	state.duty_cycle = duty_ns;
	state.period = period_ns;
	वापस pwm_apply_state(pwm, &state);
पूर्ण

/**
 * pwm_enable() - start a PWM output toggling
 * @pwm: PWM device
 *
 * Returns: 0 on success or a negative error code on failure.
 */
अटल अंतरभूत पूर्णांक pwm_enable(काष्ठा pwm_device *pwm)
अणु
	काष्ठा pwm_state state;

	अगर (!pwm)
		वापस -EINVAL;

	pwm_get_state(pwm, &state);
	अगर (state.enabled)
		वापस 0;

	state.enabled = true;
	वापस pwm_apply_state(pwm, &state);
पूर्ण

/**
 * pwm_disable() - stop a PWM output toggling
 * @pwm: PWM device
 */
अटल अंतरभूत व्योम pwm_disable(काष्ठा pwm_device *pwm)
अणु
	काष्ठा pwm_state state;

	अगर (!pwm)
		वापस;

	pwm_get_state(pwm, &state);
	अगर (!state.enabled)
		वापस;

	state.enabled = false;
	pwm_apply_state(pwm, &state);
पूर्ण

/* PWM provider APIs */
पूर्णांक pwm_capture(काष्ठा pwm_device *pwm, काष्ठा pwm_capture *result,
		अचिन्हित दीर्घ समयout);
पूर्णांक pwm_set_chip_data(काष्ठा pwm_device *pwm, व्योम *data);
व्योम *pwm_get_chip_data(काष्ठा pwm_device *pwm);

पूर्णांक pwmchip_add(काष्ठा pwm_chip *chip);
पूर्णांक pwmchip_हटाओ(काष्ठा pwm_chip *chip);
काष्ठा pwm_device *pwm_request_from_chip(काष्ठा pwm_chip *chip,
					 अचिन्हित पूर्णांक index,
					 स्थिर अक्षर *label);

काष्ठा pwm_device *of_pwm_xlate_with_flags(काष्ठा pwm_chip *pc,
		स्थिर काष्ठा of_phandle_args *args);

काष्ठा pwm_device *pwm_get(काष्ठा device *dev, स्थिर अक्षर *con_id);
काष्ठा pwm_device *of_pwm_get(काष्ठा device *dev, काष्ठा device_node *np,
			      स्थिर अक्षर *con_id);
व्योम pwm_put(काष्ठा pwm_device *pwm);

काष्ठा pwm_device *devm_pwm_get(काष्ठा device *dev, स्थिर अक्षर *con_id);
काष्ठा pwm_device *devm_of_pwm_get(काष्ठा device *dev, काष्ठा device_node *np,
				   स्थिर अक्षर *con_id);
काष्ठा pwm_device *devm_fwnode_pwm_get(काष्ठा device *dev,
				       काष्ठा fwnode_handle *fwnode,
				       स्थिर अक्षर *con_id);
व्योम devm_pwm_put(काष्ठा device *dev, काष्ठा pwm_device *pwm);
#अन्यथा
अटल अंतरभूत काष्ठा pwm_device *pwm_request(पूर्णांक pwm_id, स्थिर अक्षर *label)
अणु
	वापस ERR_PTR(-ENODEV);
पूर्ण

अटल अंतरभूत व्योम pwm_मुक्त(काष्ठा pwm_device *pwm)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक pwm_apply_state(काष्ठा pwm_device *pwm,
				  स्थिर काष्ठा pwm_state *state)
अणु
	वापस -ENOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक pwm_adjust_config(काष्ठा pwm_device *pwm)
अणु
	वापस -ENOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक pwm_config(काष्ठा pwm_device *pwm, पूर्णांक duty_ns,
			     पूर्णांक period_ns)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक pwm_capture(काष्ठा pwm_device *pwm,
			      काष्ठा pwm_capture *result,
			      अचिन्हित दीर्घ समयout)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक pwm_enable(काष्ठा pwm_device *pwm)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत व्योम pwm_disable(काष्ठा pwm_device *pwm)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक pwm_set_chip_data(काष्ठा pwm_device *pwm, व्योम *data)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत व्योम *pwm_get_chip_data(काष्ठा pwm_device *pwm)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक pwmchip_add(काष्ठा pwm_chip *chip)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक pwmchip_हटाओ(काष्ठा pwm_chip *chip)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत काष्ठा pwm_device *pwm_request_from_chip(काष्ठा pwm_chip *chip,
						       अचिन्हित पूर्णांक index,
						       स्थिर अक्षर *label)
अणु
	वापस ERR_PTR(-ENODEV);
पूर्ण

अटल अंतरभूत काष्ठा pwm_device *pwm_get(काष्ठा device *dev,
					 स्थिर अक्षर *consumer)
अणु
	वापस ERR_PTR(-ENODEV);
पूर्ण

अटल अंतरभूत काष्ठा pwm_device *of_pwm_get(काष्ठा device *dev,
					    काष्ठा device_node *np,
					    स्थिर अक्षर *con_id)
अणु
	वापस ERR_PTR(-ENODEV);
पूर्ण

अटल अंतरभूत व्योम pwm_put(काष्ठा pwm_device *pwm)
अणु
पूर्ण

अटल अंतरभूत काष्ठा pwm_device *devm_pwm_get(काष्ठा device *dev,
					      स्थिर अक्षर *consumer)
अणु
	वापस ERR_PTR(-ENODEV);
पूर्ण

अटल अंतरभूत काष्ठा pwm_device *devm_of_pwm_get(काष्ठा device *dev,
						 काष्ठा device_node *np,
						 स्थिर अक्षर *con_id)
अणु
	वापस ERR_PTR(-ENODEV);
पूर्ण

अटल अंतरभूत काष्ठा pwm_device *
devm_fwnode_pwm_get(काष्ठा device *dev, काष्ठा fwnode_handle *fwnode,
		    स्थिर अक्षर *con_id)
अणु
	वापस ERR_PTR(-ENODEV);
पूर्ण

अटल अंतरभूत व्योम devm_pwm_put(काष्ठा device *dev, काष्ठा pwm_device *pwm)
अणु
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत व्योम pwm_apply_args(काष्ठा pwm_device *pwm)
अणु
	काष्ठा pwm_state state = अणु पूर्ण;

	/*
	 * PWM users calling pwm_apply_args() expect to have a fresh config
	 * where the polarity and period are set according to pwm_args info.
	 * The problem is, polarity can only be changed when the PWM is
	 * disabled.
	 *
	 * PWM drivers supporting hardware पढ़ोout may declare the PWM device
	 * as enabled, and prevent polarity setting, which changes from the
	 * existing behavior, where all PWM devices are declared as disabled
	 * at startup (even अगर they are actually enabled), thus authorizing
	 * polarity setting.
	 *
	 * To fulfill this requirement, we apply a new state which disables
	 * the PWM device and set the reference period and polarity config.
	 *
	 * Note that PWM users requiring a smooth hanकरोver between the
	 * bootloader and the kernel (like critical regulators controlled by
	 * PWM devices) will have to चयन to the atomic API and aव्योम calling
	 * pwm_apply_args().
	 */

	state.enabled = false;
	state.polarity = pwm->args.polarity;
	state.period = pwm->args.period;

	pwm_apply_state(pwm, &state);
पूर्ण

काष्ठा pwm_lookup अणु
	काष्ठा list_head list;
	स्थिर अक्षर *provider;
	अचिन्हित पूर्णांक index;
	स्थिर अक्षर *dev_id;
	स्थिर अक्षर *con_id;
	अचिन्हित पूर्णांक period;
	क्रमागत pwm_polarity polarity;
	स्थिर अक्षर *module; /* optional, may be शून्य */
पूर्ण;

#घोषणा PWM_LOOKUP_WITH_MODULE(_provider, _index, _dev_id, _con_id,	\
			       _period, _polarity, _module)		\
	अणु								\
		.provider = _provider,					\
		.index = _index,					\
		.dev_id = _dev_id,					\
		.con_id = _con_id,					\
		.period = _period,					\
		.polarity = _polarity,					\
		.module = _module,					\
	पूर्ण

#घोषणा PWM_LOOKUP(_provider, _index, _dev_id, _con_id, _period, _polarity) \
	PWM_LOOKUP_WITH_MODULE(_provider, _index, _dev_id, _con_id, _period, \
			       _polarity, शून्य)

#अगर IS_ENABLED(CONFIG_PWM)
व्योम pwm_add_table(काष्ठा pwm_lookup *table, माप_प्रकार num);
व्योम pwm_हटाओ_table(काष्ठा pwm_lookup *table, माप_प्रकार num);
#अन्यथा
अटल अंतरभूत व्योम pwm_add_table(काष्ठा pwm_lookup *table, माप_प्रकार num)
अणु
पूर्ण

अटल अंतरभूत व्योम pwm_हटाओ_table(काष्ठा pwm_lookup *table, माप_प्रकार num)
अणु
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PWM_SYSFS
व्योम pwmchip_sysfs_export(काष्ठा pwm_chip *chip);
व्योम pwmchip_sysfs_unexport(काष्ठा pwm_chip *chip);
#अन्यथा
अटल अंतरभूत व्योम pwmchip_sysfs_export(काष्ठा pwm_chip *chip)
अणु
पूर्ण

अटल अंतरभूत व्योम pwmchip_sysfs_unexport(काष्ठा pwm_chip *chip)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_PWM_SYSFS */

#पूर्ण_अगर /* __LINUX_PWM_H */
