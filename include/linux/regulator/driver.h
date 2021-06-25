<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * driver.h -- SoC Regulator driver support.
 *
 * Copyright (C) 2007, 2008 Wolfson Microelectronics PLC.
 *
 * Author: Liam Girdwood <lrg@slimlogic.co.uk>
 *
 * Regulator Driver Interface.
 */

#अगर_अघोषित __LINUX_REGULATOR_DRIVER_H_
#घोषणा __LINUX_REGULATOR_DRIVER_H_

#समावेश <linux/device.h>
#समावेश <linux/linear_range.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/ww_mutex.h>

काष्ठा gpio_desc;
काष्ठा regmap;
काष्ठा regulator_dev;
काष्ठा regulator_config;
काष्ठा regulator_init_data;
काष्ठा regulator_enable_gpio;

क्रमागत regulator_status अणु
	REGULATOR_STATUS_OFF,
	REGULATOR_STATUS_ON,
	REGULATOR_STATUS_ERROR,
	/* fast/normal/idle/standby are flavors of "on" */
	REGULATOR_STATUS_FAST,
	REGULATOR_STATUS_NORMAL,
	REGULATOR_STATUS_IDLE,
	REGULATOR_STATUS_STANDBY,
	/* The regulator is enabled but not regulating */
	REGULATOR_STATUS_BYPASS,
	/* in हाल that any other status करोesn't apply */
	REGULATOR_STATUS_UNDEFINED,
पूर्ण;

/* Initialize काष्ठा linear_range क्रम regulators */
#घोषणा REGULATOR_LINEAR_RANGE(_min_uV, _min_sel, _max_sel, _step_uV)	\
अणु									\
	.min		= _min_uV,					\
	.min_sel	= _min_sel,					\
	.max_sel	= _max_sel,					\
	.step		= _step_uV,					\
पूर्ण

/**
 * काष्ठा regulator_ops - regulator operations.
 *
 * @enable: Configure the regulator as enabled.
 * @disable: Configure the regulator as disabled.
 * @is_enabled: Return 1 अगर the regulator is enabled, 0 अगर not.
 *		May also वापस negative त्रुटि_सं.
 *
 * @set_voltage: Set the voltage क्रम the regulator within the range specअगरied.
 *               The driver should select the voltage बंदst to min_uV.
 * @set_voltage_sel: Set the voltage क्रम the regulator using the specअगरied
 *                   selector.
 * @map_voltage: Convert a voltage पूर्णांकo a selector
 * @get_voltage: Return the currently configured voltage क्रम the regulator;
 *                   वापस -ENOTRECOVERABLE अगर regulator can't be पढ़ो at
 *                   bootup and hasn't been set yet.
 * @get_voltage_sel: Return the currently configured voltage selector क्रम the
 *                   regulator; वापस -ENOTRECOVERABLE अगर regulator can't
 *                   be पढ़ो at bootup and hasn't been set yet.
 * @list_voltage: Return one of the supported voltages, in microvolts; zero
 *	अगर the selector indicates a voltage that is unusable on this प्रणाली;
 *	or negative त्रुटि_सं.  Selectors range from zero to one less than
 *	regulator_desc.n_voltages.  Voltages may be reported in any order.
 *
 * @set_current_limit: Configure a limit क्रम a current-limited regulator.
 *                     The driver should select the current बंदst to max_uA.
 * @get_current_limit: Get the configured limit क्रम a current-limited regulator.
 * @set_input_current_limit: Configure an input limit.
 *
 * @set_over_current_protection: Support capability of स्वतःmatically shutting
 *                               करोwn when detecting an over current event.
 *
 * @set_active_disअक्षरge: Set active disअक्षरge enable/disable of regulators.
 *
 * @set_mode: Set the configured operating mode क्रम the regulator.
 * @get_mode: Get the configured operating mode क्रम the regulator.
 * @get_error_flags: Get the current error(s) क्रम the regulator.
 * @get_status: Return actual (not as-configured) status of regulator, as a
 *	REGULATOR_STATUS value (or negative त्रुटि_सं)
 * @get_optimum_mode: Get the most efficient operating mode क्रम the regulator
 *                    when running with the specअगरied parameters.
 * @set_load: Set the load क्रम the regulator.
 *
 * @set_bypass: Set the regulator in bypass mode.
 * @get_bypass: Get the regulator bypass mode state.
 *
 * @enable_समय: Time taken क्रम the regulator voltage output voltage to
 *               stabilise after being enabled, in microseconds.
 * @set_ramp_delay: Set the ramp delay क्रम the regulator. The driver should
 *		select ramp delay equal to or less than(बंदst) ramp_delay.
 * @set_voltage_समय: Time taken क्रम the regulator voltage output voltage
 *               to stabilise after being set to a new value, in microseconds.
 *               The function receives the from and to voltage as input, it
 *               should वापस the worst हाल.
 * @set_voltage_समय_sel: Time taken क्रम the regulator voltage output voltage
 *               to stabilise after being set to a new value, in microseconds.
 *               The function receives the from and to voltage selector as
 *               input, it should वापस the worst हाल.
 * @set_soft_start: Enable soft start क्रम the regulator.
 *
 * @set_suspend_voltage: Set the voltage क्रम the regulator when the प्रणाली
 *                       is suspended.
 * @set_suspend_enable: Mark the regulator as enabled when the प्रणाली is
 *                      suspended.
 * @set_suspend_disable: Mark the regulator as disabled when the प्रणाली is
 *                       suspended.
 * @set_suspend_mode: Set the operating mode क्रम the regulator when the
 *                    प्रणाली is suspended.
 * @resume: Resume operation of suspended regulator.
 * @set_pull_करोwn: Configure the regulator to pull करोwn when the regulator
 *		   is disabled.
 *
 * This काष्ठा describes regulator operations which can be implemented by
 * regulator chip drivers.
 */
काष्ठा regulator_ops अणु

	/* क्रमागतerate supported voltages */
	पूर्णांक (*list_voltage) (काष्ठा regulator_dev *, अचिन्हित selector);

	/* get/set regulator voltage */
	पूर्णांक (*set_voltage) (काष्ठा regulator_dev *, पूर्णांक min_uV, पूर्णांक max_uV,
			    अचिन्हित *selector);
	पूर्णांक (*map_voltage)(काष्ठा regulator_dev *, पूर्णांक min_uV, पूर्णांक max_uV);
	पूर्णांक (*set_voltage_sel) (काष्ठा regulator_dev *, अचिन्हित selector);
	पूर्णांक (*get_voltage) (काष्ठा regulator_dev *);
	पूर्णांक (*get_voltage_sel) (काष्ठा regulator_dev *);

	/* get/set regulator current  */
	पूर्णांक (*set_current_limit) (काष्ठा regulator_dev *,
				 पूर्णांक min_uA, पूर्णांक max_uA);
	पूर्णांक (*get_current_limit) (काष्ठा regulator_dev *);

	पूर्णांक (*set_input_current_limit) (काष्ठा regulator_dev *, पूर्णांक lim_uA);
	पूर्णांक (*set_over_current_protection) (काष्ठा regulator_dev *);
	पूर्णांक (*set_active_disअक्षरge) (काष्ठा regulator_dev *, bool enable);

	/* enable/disable regulator */
	पूर्णांक (*enable) (काष्ठा regulator_dev *);
	पूर्णांक (*disable) (काष्ठा regulator_dev *);
	पूर्णांक (*is_enabled) (काष्ठा regulator_dev *);

	/* get/set regulator operating mode (defined in consumer.h) */
	पूर्णांक (*set_mode) (काष्ठा regulator_dev *, अचिन्हित पूर्णांक mode);
	अचिन्हित पूर्णांक (*get_mode) (काष्ठा regulator_dev *);

	/* retrieve current error flags on the regulator */
	पूर्णांक (*get_error_flags)(काष्ठा regulator_dev *, अचिन्हित पूर्णांक *flags);

	/* Time taken to enable or set voltage on the regulator */
	पूर्णांक (*enable_समय) (काष्ठा regulator_dev *);
	पूर्णांक (*set_ramp_delay) (काष्ठा regulator_dev *, पूर्णांक ramp_delay);
	पूर्णांक (*set_voltage_समय) (काष्ठा regulator_dev *, पूर्णांक old_uV,
				 पूर्णांक new_uV);
	पूर्णांक (*set_voltage_समय_sel) (काष्ठा regulator_dev *,
				     अचिन्हित पूर्णांक old_selector,
				     अचिन्हित पूर्णांक new_selector);

	पूर्णांक (*set_soft_start) (काष्ठा regulator_dev *);

	/* report regulator status ... most other accessors report
	 * control inमाला_दो, this reports results of combining inमाला_दो
	 * from Linux (and other sources) with the actual load.
	 * वापसs REGULATOR_STATUS_* or negative त्रुटि_सं.
	 */
	पूर्णांक (*get_status)(काष्ठा regulator_dev *);

	/* get most efficient regulator operating mode क्रम load */
	अचिन्हित पूर्णांक (*get_optimum_mode) (काष्ठा regulator_dev *, पूर्णांक input_uV,
					  पूर्णांक output_uV, पूर्णांक load_uA);
	/* set the load on the regulator */
	पूर्णांक (*set_load)(काष्ठा regulator_dev *, पूर्णांक load_uA);

	/* control and report on bypass mode */
	पूर्णांक (*set_bypass)(काष्ठा regulator_dev *dev, bool enable);
	पूर्णांक (*get_bypass)(काष्ठा regulator_dev *dev, bool *enable);

	/* the operations below are क्रम configuration of regulator state when
	 * its parent PMIC enters a global STANDBY/HIBERNATE state */

	/* set regulator suspend voltage */
	पूर्णांक (*set_suspend_voltage) (काष्ठा regulator_dev *, पूर्णांक uV);

	/* enable/disable regulator in suspend state */
	पूर्णांक (*set_suspend_enable) (काष्ठा regulator_dev *);
	पूर्णांक (*set_suspend_disable) (काष्ठा regulator_dev *);

	/* set regulator suspend operating mode (defined in consumer.h) */
	पूर्णांक (*set_suspend_mode) (काष्ठा regulator_dev *, अचिन्हित पूर्णांक mode);

	पूर्णांक (*resume)(काष्ठा regulator_dev *rdev);

	पूर्णांक (*set_pull_करोwn) (काष्ठा regulator_dev *);
पूर्ण;

/*
 * Regulators can either control voltage or current.
 */
क्रमागत regulator_type अणु
	REGULATOR_VOLTAGE,
	REGULATOR_CURRENT,
पूर्ण;

/**
 * काष्ठा regulator_desc - Static regulator descriptor
 *
 * Each regulator रेजिस्टरed with the core is described with a
 * काष्ठाure of this type and a काष्ठा regulator_config.  This
 * काष्ठाure contains the non-varying parts of the regulator
 * description.
 *
 * @name: Identअगरying name क्रम the regulator.
 * @supply_name: Identअगरying the regulator supply
 * @of_match: Name used to identअगरy regulator in DT.
 * @of_match_full_name: A flag to indicate that the of_match string, अगर
 *			present, should be matched against the node full_name.
 * @regulators_node: Name of node containing regulator definitions in DT.
 * @of_parse_cb: Optional callback called only अगर of_match is present.
 *               Will be called क्रम each regulator parsed from DT, during
 *               init_data parsing.
 *               The regulator_config passed as argument to the callback will
 *               be a copy of config passed to regulator_रेजिस्टर, valid only
 *               क्रम this particular call. Callback may मुक्तly change the
 *               config but it cannot store it क्रम later usage.
 *               Callback should वापस 0 on success or negative ERRNO
 *               indicating failure.
 * @id: Numerical identअगरier क्रम the regulator.
 * @ops: Regulator operations table.
 * @irq: Interrupt number क्रम the regulator.
 * @type: Indicates अगर the regulator is a voltage or current regulator.
 * @owner: Module providing the regulator, used क्रम refcounting.
 *
 * @continuous_voltage_range: Indicates अगर the regulator can set any
 *                            voltage within स्थिरrains range.
 * @n_voltages: Number of selectors available क्रम ops.list_voltage().
 * @n_current_limits: Number of selectors available क्रम current limits
 *
 * @min_uV: Voltage given by the lowest selector (अगर linear mapping)
 * @uV_step: Voltage increase with each selector (अगर linear mapping)
 * @linear_min_sel: Minimal selector क्रम starting linear mapping
 * @fixed_uV: Fixed voltage of rails.
 * @ramp_delay: Time to settle करोwn after voltage change (unit: uV/us)
 * @min_dropout_uV: The minimum dropout voltage this regulator can handle
 * @linear_ranges: A स्थिरant table of possible voltage ranges.
 * @linear_range_selectors: A स्थिरant table of voltage range selectors.
 *			    If pickable ranges are used each range must
 *			    have corresponding selector here.
 * @n_linear_ranges: Number of entries in the @linear_ranges (and in
 *		     linear_range_selectors अगर used) table(s).
 * @volt_table: Voltage mapping table (अगर table based mapping)
 * @curr_table: Current limit mapping table (अगर table based mapping)
 *
 * @vsel_range_reg: Register क्रम range selector when using pickable ranges
 *		    and ``regulator_map_*_voltage_*_pickable`` functions.
 * @vsel_range_mask: Mask क्रम रेजिस्टर bitfield used क्रम range selector
 * @vsel_reg: Register क्रम selector when using ``regulator_map_*_voltage_*``
 * @vsel_mask: Mask क्रम रेजिस्टर bitfield used क्रम selector
 * @vsel_step: Specअगरy the resolution of selector stepping when setting
 *	       voltage. If 0, then no stepping is करोne (requested selector is
 *	       set directly), अगर >0 then the regulator API will ramp the
 *	       voltage up/करोwn gradually each समय increasing/decreasing the
 *	       selector by the specअगरied step value.
 * @csel_reg: Register क्रम current limit selector using regmap set_current_limit
 * @csel_mask: Mask क्रम रेजिस्टर bitfield used क्रम current limit selector
 * @apply_reg: Register क्रम initiate voltage change on the output when
 *                using regulator_set_voltage_sel_regmap
 * @apply_bit: Register bitfield used क्रम initiate voltage change on the
 *                output when using regulator_set_voltage_sel_regmap
 * @enable_reg: Register क्रम control when using regmap enable/disable ops
 * @enable_mask: Mask क्रम control when using regmap enable/disable ops
 * @enable_val: Enabling value क्रम control when using regmap enable/disable ops
 * @disable_val: Disabling value क्रम control when using regmap enable/disable ops
 * @enable_is_inverted: A flag to indicate set enable_mask bits to disable
 *                      when using regulator_enable_regmap and मित्रs APIs.
 * @bypass_reg: Register क्रम control when using regmap set_bypass
 * @bypass_mask: Mask क्रम control when using regmap set_bypass
 * @bypass_val_on: Enabling value क्रम control when using regmap set_bypass
 * @bypass_val_off: Disabling value क्रम control when using regmap set_bypass
 * @active_disअक्षरge_off: Enabling value क्रम control when using regmap
 *			  set_active_disअक्षरge
 * @active_disअक्षरge_on: Disabling value क्रम control when using regmap
 *			 set_active_disअक्षरge
 * @active_disअक्षरge_mask: Mask क्रम control when using regmap
 *			   set_active_disअक्षरge
 * @active_disअक्षरge_reg: Register क्रम control when using regmap
 *			  set_active_disअक्षरge
 * @soft_start_reg: Register क्रम control when using regmap set_soft_start
 * @soft_start_mask: Mask क्रम control when using regmap set_soft_start
 * @soft_start_val_on: Enabling value क्रम control when using regmap
 *                     set_soft_start
 * @pull_करोwn_reg: Register क्रम control when using regmap set_pull_करोwn
 * @pull_करोwn_mask: Mask क्रम control when using regmap set_pull_करोwn
 * @pull_करोwn_val_on: Enabling value क्रम control when using regmap
 *                     set_pull_करोwn
 *
 * @enable_समय: Time taken क्रम initial enable of regulator (in uS).
 * @off_on_delay: guard समय (in uS), beक्रमe re-enabling a regulator
 *
 * @poll_enabled_समय: The polling पूर्णांकerval (in uS) to use जबतक checking that
 *                     the regulator was actually enabled. Max upto enable_समय.
 *
 * @of_map_mode: Maps a hardware mode defined in a DeviceTree to a standard mode
 */
काष्ठा regulator_desc अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर *supply_name;
	स्थिर अक्षर *of_match;
	bool of_match_full_name;
	स्थिर अक्षर *regulators_node;
	पूर्णांक (*of_parse_cb)(काष्ठा device_node *,
			    स्थिर काष्ठा regulator_desc *,
			    काष्ठा regulator_config *);
	पूर्णांक id;
	अचिन्हित पूर्णांक continuous_voltage_range:1;
	अचिन्हित n_voltages;
	अचिन्हित पूर्णांक n_current_limits;
	स्थिर काष्ठा regulator_ops *ops;
	पूर्णांक irq;
	क्रमागत regulator_type type;
	काष्ठा module *owner;

	अचिन्हित पूर्णांक min_uV;
	अचिन्हित पूर्णांक uV_step;
	अचिन्हित पूर्णांक linear_min_sel;
	पूर्णांक fixed_uV;
	अचिन्हित पूर्णांक ramp_delay;
	पूर्णांक min_dropout_uV;

	स्थिर काष्ठा linear_range *linear_ranges;
	स्थिर अचिन्हित पूर्णांक *linear_range_selectors;

	पूर्णांक n_linear_ranges;

	स्थिर अचिन्हित पूर्णांक *volt_table;
	स्थिर अचिन्हित पूर्णांक *curr_table;

	अचिन्हित पूर्णांक vsel_range_reg;
	अचिन्हित पूर्णांक vsel_range_mask;
	अचिन्हित पूर्णांक vsel_reg;
	अचिन्हित पूर्णांक vsel_mask;
	अचिन्हित पूर्णांक vsel_step;
	अचिन्हित पूर्णांक csel_reg;
	अचिन्हित पूर्णांक csel_mask;
	अचिन्हित पूर्णांक apply_reg;
	अचिन्हित पूर्णांक apply_bit;
	अचिन्हित पूर्णांक enable_reg;
	अचिन्हित पूर्णांक enable_mask;
	अचिन्हित पूर्णांक enable_val;
	अचिन्हित पूर्णांक disable_val;
	bool enable_is_inverted;
	अचिन्हित पूर्णांक bypass_reg;
	अचिन्हित पूर्णांक bypass_mask;
	अचिन्हित पूर्णांक bypass_val_on;
	अचिन्हित पूर्णांक bypass_val_off;
	अचिन्हित पूर्णांक active_disअक्षरge_on;
	अचिन्हित पूर्णांक active_disअक्षरge_off;
	अचिन्हित पूर्णांक active_disअक्षरge_mask;
	अचिन्हित पूर्णांक active_disअक्षरge_reg;
	अचिन्हित पूर्णांक soft_start_reg;
	अचिन्हित पूर्णांक soft_start_mask;
	अचिन्हित पूर्णांक soft_start_val_on;
	अचिन्हित पूर्णांक pull_करोwn_reg;
	अचिन्हित पूर्णांक pull_करोwn_mask;
	अचिन्हित पूर्णांक pull_करोwn_val_on;
	अचिन्हित पूर्णांक ramp_reg;
	अचिन्हित पूर्णांक ramp_mask;
	स्थिर अचिन्हित पूर्णांक *ramp_delay_table;
	अचिन्हित पूर्णांक n_ramp_values;

	अचिन्हित पूर्णांक enable_समय;

	अचिन्हित पूर्णांक off_on_delay;

	अचिन्हित पूर्णांक poll_enabled_समय;

	अचिन्हित पूर्णांक (*of_map_mode)(अचिन्हित पूर्णांक mode);
पूर्ण;

/**
 * काष्ठा regulator_config - Dynamic regulator descriptor
 *
 * Each regulator रेजिस्टरed with the core is described with a
 * काष्ठाure of this type and a काष्ठा regulator_desc.  This काष्ठाure
 * contains the runसमय variable parts of the regulator description.
 *
 * @dev: काष्ठा device क्रम the regulator
 * @init_data: platक्रमm provided init data, passed through by driver
 * @driver_data: निजी regulator data
 * @of_node: OpenFirmware node to parse क्रम device tree bindings (may be
 *           शून्य).
 * @regmap: regmap to use क्रम core regmap helpers अगर dev_get_regmap() is
 *          insufficient.
 * @ena_gpiod: GPIO controlling regulator enable.
 */
काष्ठा regulator_config अणु
	काष्ठा device *dev;
	स्थिर काष्ठा regulator_init_data *init_data;
	व्योम *driver_data;
	काष्ठा device_node *of_node;
	काष्ठा regmap *regmap;

	काष्ठा gpio_desc *ena_gpiod;
पूर्ण;

/*
 * काष्ठा coupling_desc
 *
 * Describes coupling of regulators. Each regulator should have
 * at least a poपूर्णांकer to itself in coupled_rdevs array.
 * When a new coupled regulator is resolved, n_resolved is
 * incremented.
 */
काष्ठा coupling_desc अणु
	काष्ठा regulator_dev **coupled_rdevs;
	काष्ठा regulator_coupler *coupler;
	पूर्णांक n_resolved;
	पूर्णांक n_coupled;
पूर्ण;

/*
 * काष्ठा regulator_dev
 *
 * Voltage / Current regulator class device. One क्रम each
 * regulator.
 *
 * This should *not* be used directly by anything except the regulator
 * core and notअगरication injection (which should take the mutex and करो
 * no other direct access).
 */
काष्ठा regulator_dev अणु
	स्थिर काष्ठा regulator_desc *desc;
	पूर्णांक exclusive;
	u32 use_count;
	u32 खोलो_count;
	u32 bypass_count;

	/* lists we beदीर्घ to */
	काष्ठा list_head list; /* list of all regulators */

	/* lists we own */
	काष्ठा list_head consumer_list; /* consumers we supply */

	काष्ठा coupling_desc coupling_desc;

	काष्ठा blocking_notअगरier_head notअगरier;
	काष्ठा ww_mutex mutex; /* consumer lock */
	काष्ठा task_काष्ठा *mutex_owner;
	पूर्णांक ref_cnt;
	काष्ठा module *owner;
	काष्ठा device dev;
	काष्ठा regulation_स्थिरraपूर्णांकs *स्थिरraपूर्णांकs;
	काष्ठा regulator *supply;	/* क्रम tree */
	स्थिर अक्षर *supply_name;
	काष्ठा regmap *regmap;

	काष्ठा delayed_work disable_work;

	व्योम *reg_data;		/* regulator_dev data */

	काष्ठा dentry *debugfs;

	काष्ठा regulator_enable_gpio *ena_pin;
	अचिन्हित पूर्णांक ena_gpio_state:1;

	अचिन्हित पूर्णांक is_चयन:1;

	/* समय when this regulator was disabled last समय */
	kसमय_प्रकार last_off;
पूर्ण;

काष्ठा regulator_dev *
regulator_रेजिस्टर(स्थिर काष्ठा regulator_desc *regulator_desc,
		   स्थिर काष्ठा regulator_config *config);
काष्ठा regulator_dev *
devm_regulator_रेजिस्टर(काष्ठा device *dev,
			स्थिर काष्ठा regulator_desc *regulator_desc,
			स्थिर काष्ठा regulator_config *config);
व्योम regulator_unरेजिस्टर(काष्ठा regulator_dev *rdev);
व्योम devm_regulator_unरेजिस्टर(काष्ठा device *dev, काष्ठा regulator_dev *rdev);

पूर्णांक regulator_notअगरier_call_chain(काष्ठा regulator_dev *rdev,
				  अचिन्हित दीर्घ event, व्योम *data);

व्योम *rdev_get_drvdata(काष्ठा regulator_dev *rdev);
काष्ठा device *rdev_get_dev(काष्ठा regulator_dev *rdev);
काष्ठा regmap *rdev_get_regmap(काष्ठा regulator_dev *rdev);
पूर्णांक rdev_get_id(काष्ठा regulator_dev *rdev);

पूर्णांक regulator_mode_to_status(अचिन्हित पूर्णांक);

पूर्णांक regulator_list_voltage_linear(काष्ठा regulator_dev *rdev,
				  अचिन्हित पूर्णांक selector);
पूर्णांक regulator_list_voltage_pickable_linear_range(काष्ठा regulator_dev *rdev,
						   अचिन्हित पूर्णांक selector);
पूर्णांक regulator_list_voltage_linear_range(काष्ठा regulator_dev *rdev,
					अचिन्हित पूर्णांक selector);
पूर्णांक regulator_list_voltage_table(काष्ठा regulator_dev *rdev,
				  अचिन्हित पूर्णांक selector);
पूर्णांक regulator_map_voltage_linear(काष्ठा regulator_dev *rdev,
				  पूर्णांक min_uV, पूर्णांक max_uV);
पूर्णांक regulator_map_voltage_pickable_linear_range(काष्ठा regulator_dev *rdev,
						  पूर्णांक min_uV, पूर्णांक max_uV);
पूर्णांक regulator_map_voltage_linear_range(काष्ठा regulator_dev *rdev,
				       पूर्णांक min_uV, पूर्णांक max_uV);
पूर्णांक regulator_map_voltage_iterate(काष्ठा regulator_dev *rdev,
				  पूर्णांक min_uV, पूर्णांक max_uV);
पूर्णांक regulator_map_voltage_ascend(काष्ठा regulator_dev *rdev,
				  पूर्णांक min_uV, पूर्णांक max_uV);
पूर्णांक regulator_get_voltage_sel_pickable_regmap(काष्ठा regulator_dev *rdev);
पूर्णांक regulator_set_voltage_sel_pickable_regmap(काष्ठा regulator_dev *rdev,
						अचिन्हित पूर्णांक sel);
पूर्णांक regulator_get_voltage_sel_regmap(काष्ठा regulator_dev *rdev);
पूर्णांक regulator_set_voltage_sel_regmap(काष्ठा regulator_dev *rdev, अचिन्हित sel);
पूर्णांक regulator_is_enabled_regmap(काष्ठा regulator_dev *rdev);
पूर्णांक regulator_enable_regmap(काष्ठा regulator_dev *rdev);
पूर्णांक regulator_disable_regmap(काष्ठा regulator_dev *rdev);
पूर्णांक regulator_set_voltage_समय_sel(काष्ठा regulator_dev *rdev,
				   अचिन्हित पूर्णांक old_selector,
				   अचिन्हित पूर्णांक new_selector);
पूर्णांक regulator_set_bypass_regmap(काष्ठा regulator_dev *rdev, bool enable);
पूर्णांक regulator_get_bypass_regmap(काष्ठा regulator_dev *rdev, bool *enable);
पूर्णांक regulator_set_soft_start_regmap(काष्ठा regulator_dev *rdev);
पूर्णांक regulator_set_pull_करोwn_regmap(काष्ठा regulator_dev *rdev);

पूर्णांक regulator_set_active_disअक्षरge_regmap(काष्ठा regulator_dev *rdev,
					  bool enable);
पूर्णांक regulator_set_current_limit_regmap(काष्ठा regulator_dev *rdev,
				       पूर्णांक min_uA, पूर्णांक max_uA);
पूर्णांक regulator_get_current_limit_regmap(काष्ठा regulator_dev *rdev);
व्योम *regulator_get_init_drvdata(काष्ठा regulator_init_data *reg_init_data);
पूर्णांक regulator_set_ramp_delay_regmap(काष्ठा regulator_dev *rdev, पूर्णांक ramp_delay);

/*
 * Helper functions पूर्णांकended to be used by regulator drivers prior रेजिस्टरing
 * their regulators.
 */
पूर्णांक regulator_desc_list_voltage_linear_range(स्थिर काष्ठा regulator_desc *desc,
					     अचिन्हित पूर्णांक selector);

पूर्णांक regulator_desc_list_voltage_linear(स्थिर काष्ठा regulator_desc *desc,
				       अचिन्हित पूर्णांक selector);
#पूर्ण_अगर
