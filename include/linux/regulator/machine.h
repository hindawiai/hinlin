<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * machine.h -- SoC Regulator support, machine/board driver API.
 *
 * Copyright (C) 2007, 2008 Wolfson Microelectronics PLC.
 *
 * Author: Liam Girdwood <lrg@slimlogic.co.uk>
 *
 * Regulator Machine/Board Interface.
 */

#अगर_अघोषित __LINUX_REGULATOR_MACHINE_H_
#घोषणा __LINUX_REGULATOR_MACHINE_H_

#समावेश <linux/regulator/consumer.h>
#समावेश <linux/suspend.h>

काष्ठा regulator;

/*
 * Regulator operation स्थिरraपूर्णांक flags. These flags are used to enable
 * certain regulator operations and can be OR'ed together.
 *
 * VOLTAGE:  Regulator output voltage can be changed by software on this
 *           board/machine.
 * CURRENT:  Regulator output current can be changed by software on this
 *           board/machine.
 * MODE:     Regulator operating mode can be changed by software on this
 *           board/machine.
 * STATUS:   Regulator can be enabled and disabled.
 * DRMS:     Dynamic Regulator Mode Switching is enabled क्रम this regulator.
 * BYPASS:   Regulator can be put पूर्णांकo bypass mode
 */

#घोषणा REGULATOR_CHANGE_VOLTAGE	0x1
#घोषणा REGULATOR_CHANGE_CURRENT	0x2
#घोषणा REGULATOR_CHANGE_MODE		0x4
#घोषणा REGULATOR_CHANGE_STATUS		0x8
#घोषणा REGULATOR_CHANGE_DRMS		0x10
#घोषणा REGULATOR_CHANGE_BYPASS		0x20

/*
 * operations in suspend mode
 * DO_NOTHING_IN_SUSPEND - the शेष value
 * DISABLE_IN_SUSPEND	- turn off regulator in suspend states
 * ENABLE_IN_SUSPEND	- keep regulator on in suspend states
 */
#घोषणा DO_NOTHING_IN_SUSPEND	0
#घोषणा DISABLE_IN_SUSPEND	1
#घोषणा ENABLE_IN_SUSPEND	2

/* Regulator active disअक्षरge flags */
क्रमागत regulator_active_disअक्षरge अणु
	REGULATOR_ACTIVE_DISCHARGE_DEFAULT,
	REGULATOR_ACTIVE_DISCHARGE_DISABLE,
	REGULATOR_ACTIVE_DISCHARGE_ENABLE,
पूर्ण;

/**
 * काष्ठा regulator_state - regulator state during low घातer प्रणाली states
 *
 * This describes a regulators state during a प्रणाली wide low घातer
 * state.  One of enabled or disabled must be set क्रम the
 * configuration to be applied.
 *
 * @uV: Default operating voltage during suspend, it can be adjusted
 *	among <min_uV, max_uV>.
 * @min_uV: Minimum suspend voltage may be set.
 * @max_uV: Maximum suspend voltage may be set.
 * @mode: Operating mode during suspend.
 * @enabled: operations during suspend.
 *	     - DO_NOTHING_IN_SUSPEND
 *	     - DISABLE_IN_SUSPEND
 *	     - ENABLE_IN_SUSPEND
 * @changeable: Is this state can be चयनed between enabled/disabled,
 */
काष्ठा regulator_state अणु
	पूर्णांक uV;
	पूर्णांक min_uV;
	पूर्णांक max_uV;
	अचिन्हित पूर्णांक mode;
	पूर्णांक enabled;
	bool changeable;
पूर्ण;

/**
 * काष्ठा regulation_स्थिरraपूर्णांकs - regulator operating स्थिरraपूर्णांकs.
 *
 * This काष्ठा describes regulator and board/machine specअगरic स्थिरraपूर्णांकs.
 *
 * @name: Descriptive name क्रम the स्थिरraपूर्णांकs, used क्रम display purposes.
 *
 * @min_uV: Smallest voltage consumers may set.
 * @max_uV: Largest voltage consumers may set.
 * @uV_offset: Offset applied to voltages from consumer to compensate क्रम
 *             voltage drops.
 *
 * @min_uA: Smallest current consumers may set.
 * @max_uA: Largest current consumers may set.
 * @ilim_uA: Maximum input current.
 * @प्रणाली_load: Load that isn't captured by any consumer requests.
 *
 * @max_spपढ़ो: Max possible spपढ़ो between coupled regulators
 * @max_uV_step: Max possible step change in voltage
 * @valid_modes_mask: Mask of modes which may be configured by consumers.
 * @valid_ops_mask: Operations which may be perक्रमmed by consumers.
 *
 * @always_on: Set अगर the regulator should never be disabled.
 * @boot_on: Set अगर the regulator is enabled when the प्रणाली is initially
 *           started.  If the regulator is not enabled by the hardware or
 *           bootloader then it will be enabled when the स्थिरraपूर्णांकs are
 *           applied.
 * @apply_uV: Apply the voltage स्थिरraपूर्णांक when initialising.
 * @ramp_disable: Disable ramp delay when initialising or when setting voltage.
 * @soft_start: Enable soft start so that voltage ramps slowly.
 * @pull_करोwn: Enable pull करोwn when regulator is disabled.
 * @over_current_protection: Auto disable on over current event.
 *
 * @input_uV: Input voltage क्रम regulator when supplied by another regulator.
 *
 * @state_disk: State क्रम regulator when प्रणाली is suspended in disk mode.
 * @state_mem: State क्रम regulator when प्रणाली is suspended in mem mode.
 * @state_standby: State क्रम regulator when प्रणाली is suspended in standby
 *                 mode.
 * @initial_state: Suspend state to set by शेष.
 * @initial_mode: Mode to set at startup.
 * @ramp_delay: Time to settle करोwn after voltage change (unit: uV/us)
 * @settling_समय: Time to settle करोwn after voltage change when voltage
 *		   change is non-linear (unit: microseconds).
 * @settling_समय_up: Time to settle करोwn after voltage increase when voltage
 *		      change is non-linear (unit: microseconds).
 * @settling_समय_करोwn : Time to settle करोwn after voltage decrease when
 *			 voltage change is non-linear (unit: microseconds).
 * @active_disअक्षरge: Enable/disable active disअक्षरge. The क्रमागत
 *		      regulator_active_disअक्षरge values are used क्रम
 *		      initialisation.
 * @enable_समय: Turn-on समय of the rails (unit: microseconds)
 */
काष्ठा regulation_स्थिरraपूर्णांकs अणु

	स्थिर अक्षर *name;

	/* voltage output range (inclusive) - क्रम voltage control */
	पूर्णांक min_uV;
	पूर्णांक max_uV;

	पूर्णांक uV_offset;

	/* current output range (inclusive) - क्रम current control */
	पूर्णांक min_uA;
	पूर्णांक max_uA;
	पूर्णांक ilim_uA;

	पूर्णांक प्रणाली_load;

	/* used क्रम coupled regulators */
	u32 *max_spपढ़ो;

	/* used क्रम changing voltage in steps */
	पूर्णांक max_uV_step;

	/* valid regulator operating modes क्रम this machine */
	अचिन्हित पूर्णांक valid_modes_mask;

	/* valid operations क्रम regulator on this machine */
	अचिन्हित पूर्णांक valid_ops_mask;

	/* regulator input voltage - only अगर supply is another regulator */
	पूर्णांक input_uV;

	/* regulator suspend states क्रम global PMIC STANDBY/HIBERNATE */
	काष्ठा regulator_state state_disk;
	काष्ठा regulator_state state_mem;
	काष्ठा regulator_state state_standby;
	suspend_state_t initial_state; /* suspend state to set at init */

	/* mode to set on startup */
	अचिन्हित पूर्णांक initial_mode;

	अचिन्हित पूर्णांक ramp_delay;
	अचिन्हित पूर्णांक settling_समय;
	अचिन्हित पूर्णांक settling_समय_up;
	अचिन्हित पूर्णांक settling_समय_करोwn;
	अचिन्हित पूर्णांक enable_समय;

	अचिन्हित पूर्णांक active_disअक्षरge;

	/* स्थिरraपूर्णांक flags */
	अचिन्हित always_on:1;	/* regulator never off when प्रणाली is on */
	अचिन्हित boot_on:1;	/* bootloader/firmware enabled regulator */
	अचिन्हित apply_uV:1;	/* apply uV स्थिरraपूर्णांक अगर min == max */
	अचिन्हित ramp_disable:1; /* disable ramp delay */
	अचिन्हित soft_start:1;	/* ramp voltage slowly */
	अचिन्हित pull_करोwn:1;	/* pull करोwn resistor when regulator off */
	अचिन्हित over_current_protection:1; /* स्वतः disable on over current */
पूर्ण;

/**
 * काष्ठा regulator_consumer_supply - supply -> device mapping
 *
 * This maps a supply name to a device. Use of dev_name allows support क्रम
 * buses which make काष्ठा device available late such as I2C.
 *
 * @dev_name: Result of dev_name() क्रम the consumer.
 * @supply: Name क्रम the supply.
 */
काष्ठा regulator_consumer_supply अणु
	स्थिर अक्षर *dev_name;   /* dev_name() क्रम consumer */
	स्थिर अक्षर *supply;	/* consumer supply - e.g. "vcc" */
पूर्ण;

/* Initialize काष्ठा regulator_consumer_supply */
#घोषणा REGULATOR_SUPPLY(_name, _dev_name)			\
अणु								\
	.supply		= _name,				\
	.dev_name	= _dev_name,				\
पूर्ण

/**
 * काष्ठा regulator_init_data - regulator platक्रमm initialisation data.
 *
 * Initialisation स्थिरraपूर्णांकs, our supply and consumers supplies.
 *
 * @supply_regulator: Parent regulator.  Specअगरied using the regulator name
 *                    as it appears in the name field in sysfs, which can
 *                    be explicitly set using the स्थिरraपूर्णांकs field 'name'.
 *
 * @स्थिरraपूर्णांकs: Constraपूर्णांकs.  These must be specअगरied क्रम the regulator to
 *               be usable.
 * @num_consumer_supplies: Number of consumer device supplies.
 * @consumer_supplies: Consumer device supply configuration.
 *
 * @regulator_init: Callback invoked when the regulator has been रेजिस्टरed.
 * @driver_data: Data passed to regulator_init.
 */
काष्ठा regulator_init_data अणु
	स्थिर अक्षर *supply_regulator;        /* or शून्य क्रम प्रणाली supply */

	काष्ठा regulation_स्थिरraपूर्णांकs स्थिरraपूर्णांकs;

	पूर्णांक num_consumer_supplies;
	काष्ठा regulator_consumer_supply *consumer_supplies;

	/* optional regulator machine specअगरic init */
	पूर्णांक (*regulator_init)(व्योम *driver_data);
	व्योम *driver_data;	/* core करोes not touch this */
पूर्ण;

#अगर_घोषित CONFIG_REGULATOR
व्योम regulator_has_full_स्थिरraपूर्णांकs(व्योम);
#अन्यथा
अटल अंतरभूत व्योम regulator_has_full_स्थिरraपूर्णांकs(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक regulator_suspend_prepare(suspend_state_t state)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक regulator_suspend_finish(व्योम)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर
