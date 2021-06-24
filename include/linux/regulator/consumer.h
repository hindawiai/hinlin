<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * consumer.h -- SoC Regulator consumer support.
 *
 * Copyright (C) 2007, 2008 Wolfson Microelectronics PLC.
 *
 * Author: Liam Girdwood <lrg@slimlogic.co.uk>
 *
 * Regulator Consumer Interface.
 *
 * A Power Management Regulator framework क्रम SoC based devices.
 * Features:-
 *   o Voltage and current level control.
 *   o Operating mode control.
 *   o Regulator status.
 *   o sysfs entries क्रम showing client devices and status
 *
 * EXPERIMENTAL FEATURES:
 *   Dynamic Regulator operating Mode Switching (DRMS) - allows regulators
 *   to use most efficient operating mode depending upon voltage and load and
 *   is transparent to client drivers.
 *
 *   e.g. Devices x,y,z share regulator r. Device x and y draw 20mA each during
 *   IO and 1mA at idle. Device z draws 100mA when under load and 5mA when
 *   idling. Regulator r has > 90% efficiency in NORMAL mode at loads > 100mA
 *   but this drops rapidly to 60% when below 100mA. Regulator r has > 90%
 *   efficiency in IDLE mode at loads < 10mA. Thus regulator r will operate
 *   in normal mode क्रम loads > 10mA and in IDLE mode क्रम load <= 10mA.
 */

#अगर_अघोषित __LINUX_REGULATOR_CONSUMER_H_
#घोषणा __LINUX_REGULATOR_CONSUMER_H_

#समावेश <linux/err.h>
#समावेश <linux/suspend.h>

काष्ठा device;
काष्ठा notअगरier_block;
काष्ठा regmap;
काष्ठा regulator_dev;

/*
 * Regulator operating modes.
 *
 * Regulators can run in a variety of dअगरferent operating modes depending on
 * output load. This allows further प्रणाली घातer savings by selecting the
 * best (and most efficient) regulator mode क्रम a desired load.
 *
 * Most drivers will only care about NORMAL. The modes below are generic and
 * will probably not match the naming convention of your regulator data sheet
 * but should match the use हालs in the datasheet.
 *
 * In order of घातer efficiency (least efficient at top).
 *
 *  Mode       Description
 *  FAST       Regulator can handle fast changes in it's load.
 *             e.g. useful in CPU voltage & frequency scaling where
 *             load can quickly increase with CPU frequency increases.
 *
 *  NORMAL     Normal regulator घातer supply mode. Most drivers will
 *             use this mode.
 *
 *  IDLE       Regulator runs in a more efficient mode क्रम light
 *             loads. Can be used क्रम devices that have a low घातer
 *             requirement during periods of inactivity. This mode
 *             may be more noisy than NORMAL and may not be able
 *             to handle fast load चयनing.
 *
 *  STANDBY    Regulator runs in the most efficient mode क्रम very
 *             light loads. Can be used by devices when they are
 *             in a sleep/standby state. This mode is likely to be
 *             the most noisy and may not be able to handle fast load
 *             चयनing.
 *
 * NOTE: Most regulators will only support a subset of these modes. Some
 * will only just support NORMAL.
 *
 * These modes can be OR'ed together to make up a mask of valid रेजिस्टर modes.
 */

#घोषणा REGULATOR_MODE_INVALID			0x0
#घोषणा REGULATOR_MODE_FAST			0x1
#घोषणा REGULATOR_MODE_NORMAL			0x2
#घोषणा REGULATOR_MODE_IDLE			0x4
#घोषणा REGULATOR_MODE_STANDBY			0x8

/*
 * Regulator notअगरier events.
 *
 * UNDER_VOLTAGE  Regulator output is under voltage.
 * OVER_CURRENT   Regulator output current is too high.
 * REGULATION_OUT Regulator output is out of regulation.
 * FAIL           Regulator output has failed.
 * OVER_TEMP      Regulator over temp.
 * FORCE_DISABLE  Regulator क्रमcibly shut करोwn by software.
 * VOLTAGE_CHANGE Regulator voltage changed.
 *                Data passed is old voltage cast to (व्योम *).
 * DISABLE        Regulator was disabled.
 * PRE_VOLTAGE_CHANGE   Regulator is about to have voltage changed.
 *                      Data passed is "struct pre_voltage_change_data"
 * ABORT_VOLTAGE_CHANGE Regulator voltage change failed क्रम some reason.
 *                      Data passed is old voltage cast to (व्योम *).
 * PRE_DISABLE    Regulator is about to be disabled
 * ABORT_DISABLE  Regulator disable failed क्रम some reason
 *
 * NOTE: These events can be OR'ed together when passed पूर्णांकo handler.
 */

#घोषणा REGULATOR_EVENT_UNDER_VOLTAGE		0x01
#घोषणा REGULATOR_EVENT_OVER_CURRENT		0x02
#घोषणा REGULATOR_EVENT_REGULATION_OUT		0x04
#घोषणा REGULATOR_EVENT_FAIL			0x08
#घोषणा REGULATOR_EVENT_OVER_TEMP		0x10
#घोषणा REGULATOR_EVENT_FORCE_DISABLE		0x20
#घोषणा REGULATOR_EVENT_VOLTAGE_CHANGE		0x40
#घोषणा REGULATOR_EVENT_DISABLE			0x80
#घोषणा REGULATOR_EVENT_PRE_VOLTAGE_CHANGE	0x100
#घोषणा REGULATOR_EVENT_ABORT_VOLTAGE_CHANGE	0x200
#घोषणा REGULATOR_EVENT_PRE_DISABLE		0x400
#घोषणा REGULATOR_EVENT_ABORT_DISABLE		0x800
#घोषणा REGULATOR_EVENT_ENABLE			0x1000

/*
 * Regulator errors that can be queried using regulator_get_error_flags
 *
 * UNDER_VOLTAGE  Regulator output is under voltage.
 * OVER_CURRENT   Regulator output current is too high.
 * REGULATION_OUT Regulator output is out of regulation.
 * FAIL           Regulator output has failed.
 * OVER_TEMP      Regulator over temp.
 *
 * NOTE: These errors can be OR'ed together.
 */

#घोषणा REGULATOR_ERROR_UNDER_VOLTAGE		BIT(1)
#घोषणा REGULATOR_ERROR_OVER_CURRENT		BIT(2)
#घोषणा REGULATOR_ERROR_REGULATION_OUT		BIT(3)
#घोषणा REGULATOR_ERROR_FAIL			BIT(4)
#घोषणा REGULATOR_ERROR_OVER_TEMP		BIT(5)


/**
 * काष्ठा pre_voltage_change_data - Data sent with PRE_VOLTAGE_CHANGE event
 *
 * @old_uV: Current voltage beक्रमe change.
 * @min_uV: Min voltage we'll change to.
 * @max_uV: Max voltage we'll change to.
 */
काष्ठा pre_voltage_change_data अणु
	अचिन्हित दीर्घ old_uV;
	अचिन्हित दीर्घ min_uV;
	अचिन्हित दीर्घ max_uV;
पूर्ण;

काष्ठा regulator;

/**
 * काष्ठा regulator_bulk_data - Data used क्रम bulk regulator operations.
 *
 * @supply:   The name of the supply.  Initialised by the user beक्रमe
 *            using the bulk regulator APIs.
 * @consumer: The regulator consumer क्रम the supply.  This will be managed
 *            by the bulk API.
 *
 * The regulator APIs provide a series of regulator_bulk_() API calls as
 * a convenience to consumers which require multiple supplies.  This
 * काष्ठाure is used to manage data क्रम these calls.
 */
काष्ठा regulator_bulk_data अणु
	स्थिर अक्षर *supply;
	काष्ठा regulator *consumer;

	/* निजी: Internal use */
	पूर्णांक ret;
पूर्ण;

#अगर defined(CONFIG_REGULATOR)

/* regulator get and put */
काष्ठा regulator *__must_check regulator_get(काष्ठा device *dev,
					     स्थिर अक्षर *id);
काष्ठा regulator *__must_check devm_regulator_get(काष्ठा device *dev,
					     स्थिर अक्षर *id);
काष्ठा regulator *__must_check regulator_get_exclusive(काष्ठा device *dev,
						       स्थिर अक्षर *id);
काष्ठा regulator *__must_check devm_regulator_get_exclusive(काष्ठा device *dev,
							स्थिर अक्षर *id);
काष्ठा regulator *__must_check regulator_get_optional(काष्ठा device *dev,
						      स्थिर अक्षर *id);
काष्ठा regulator *__must_check devm_regulator_get_optional(काष्ठा device *dev,
							   स्थिर अक्षर *id);
व्योम regulator_put(काष्ठा regulator *regulator);
व्योम devm_regulator_put(काष्ठा regulator *regulator);

पूर्णांक regulator_रेजिस्टर_supply_alias(काष्ठा device *dev, स्थिर अक्षर *id,
				    काष्ठा device *alias_dev,
				    स्थिर अक्षर *alias_id);
व्योम regulator_unरेजिस्टर_supply_alias(काष्ठा device *dev, स्थिर अक्षर *id);

पूर्णांक regulator_bulk_रेजिस्टर_supply_alias(काष्ठा device *dev,
					 स्थिर अक्षर *स्थिर *id,
					 काष्ठा device *alias_dev,
					 स्थिर अक्षर *स्थिर *alias_id,
					 पूर्णांक num_id);
व्योम regulator_bulk_unरेजिस्टर_supply_alias(काष्ठा device *dev,
					    स्थिर अक्षर * स्थिर *id, पूर्णांक num_id);

पूर्णांक devm_regulator_रेजिस्टर_supply_alias(काष्ठा device *dev, स्थिर अक्षर *id,
					 काष्ठा device *alias_dev,
					 स्थिर अक्षर *alias_id);
व्योम devm_regulator_unरेजिस्टर_supply_alias(काष्ठा device *dev,
					    स्थिर अक्षर *id);

पूर्णांक devm_regulator_bulk_रेजिस्टर_supply_alias(काष्ठा device *dev,
					      स्थिर अक्षर *स्थिर *id,
					      काष्ठा device *alias_dev,
					      स्थिर अक्षर *स्थिर *alias_id,
					      पूर्णांक num_id);
व्योम devm_regulator_bulk_unरेजिस्टर_supply_alias(काष्ठा device *dev,
						 स्थिर अक्षर *स्थिर *id,
						 पूर्णांक num_id);

/* regulator output control and status */
पूर्णांक __must_check regulator_enable(काष्ठा regulator *regulator);
पूर्णांक regulator_disable(काष्ठा regulator *regulator);
पूर्णांक regulator_क्रमce_disable(काष्ठा regulator *regulator);
पूर्णांक regulator_is_enabled(काष्ठा regulator *regulator);
पूर्णांक regulator_disable_deferred(काष्ठा regulator *regulator, पूर्णांक ms);

पूर्णांक __must_check regulator_bulk_get(काष्ठा device *dev, पूर्णांक num_consumers,
				    काष्ठा regulator_bulk_data *consumers);
पूर्णांक __must_check devm_regulator_bulk_get(काष्ठा device *dev, पूर्णांक num_consumers,
					 काष्ठा regulator_bulk_data *consumers);
पूर्णांक __must_check regulator_bulk_enable(पूर्णांक num_consumers,
				       काष्ठा regulator_bulk_data *consumers);
पूर्णांक regulator_bulk_disable(पूर्णांक num_consumers,
			   काष्ठा regulator_bulk_data *consumers);
पूर्णांक regulator_bulk_क्रमce_disable(पूर्णांक num_consumers,
			   काष्ठा regulator_bulk_data *consumers);
व्योम regulator_bulk_मुक्त(पूर्णांक num_consumers,
			 काष्ठा regulator_bulk_data *consumers);

पूर्णांक regulator_count_voltages(काष्ठा regulator *regulator);
पूर्णांक regulator_list_voltage(काष्ठा regulator *regulator, अचिन्हित selector);
पूर्णांक regulator_is_supported_voltage(काष्ठा regulator *regulator,
				   पूर्णांक min_uV, पूर्णांक max_uV);
अचिन्हित पूर्णांक regulator_get_linear_step(काष्ठा regulator *regulator);
पूर्णांक regulator_set_voltage(काष्ठा regulator *regulator, पूर्णांक min_uV, पूर्णांक max_uV);
पूर्णांक regulator_set_voltage_समय(काष्ठा regulator *regulator,
			       पूर्णांक old_uV, पूर्णांक new_uV);
पूर्णांक regulator_get_voltage(काष्ठा regulator *regulator);
पूर्णांक regulator_sync_voltage(काष्ठा regulator *regulator);
पूर्णांक regulator_set_current_limit(काष्ठा regulator *regulator,
			       पूर्णांक min_uA, पूर्णांक max_uA);
पूर्णांक regulator_get_current_limit(काष्ठा regulator *regulator);

पूर्णांक regulator_set_mode(काष्ठा regulator *regulator, अचिन्हित पूर्णांक mode);
अचिन्हित पूर्णांक regulator_get_mode(काष्ठा regulator *regulator);
पूर्णांक regulator_get_error_flags(काष्ठा regulator *regulator,
				अचिन्हित पूर्णांक *flags);
पूर्णांक regulator_set_load(काष्ठा regulator *regulator, पूर्णांक load_uA);

पूर्णांक regulator_allow_bypass(काष्ठा regulator *regulator, bool allow);

काष्ठा regmap *regulator_get_regmap(काष्ठा regulator *regulator);
पूर्णांक regulator_get_hardware_vsel_रेजिस्टर(काष्ठा regulator *regulator,
					 अचिन्हित *vsel_reg,
					 अचिन्हित *vsel_mask);
पूर्णांक regulator_list_hardware_vsel(काष्ठा regulator *regulator,
				 अचिन्हित selector);

/* regulator notअगरier block */
पूर्णांक regulator_रेजिस्टर_notअगरier(काष्ठा regulator *regulator,
			      काष्ठा notअगरier_block *nb);
पूर्णांक devm_regulator_रेजिस्टर_notअगरier(काष्ठा regulator *regulator,
				     काष्ठा notअगरier_block *nb);
पूर्णांक regulator_unरेजिस्टर_notअगरier(काष्ठा regulator *regulator,
				काष्ठा notअगरier_block *nb);
व्योम devm_regulator_unरेजिस्टर_notअगरier(काष्ठा regulator *regulator,
					काष्ठा notअगरier_block *nb);

/* regulator suspend */
पूर्णांक regulator_suspend_enable(काष्ठा regulator_dev *rdev,
			     suspend_state_t state);
पूर्णांक regulator_suspend_disable(काष्ठा regulator_dev *rdev,
			      suspend_state_t state);
पूर्णांक regulator_set_suspend_voltage(काष्ठा regulator *regulator, पूर्णांक min_uV,
				  पूर्णांक max_uV, suspend_state_t state);

/* driver data - core करोesn't touch */
व्योम *regulator_get_drvdata(काष्ठा regulator *regulator);
व्योम regulator_set_drvdata(काष्ठा regulator *regulator, व्योम *data);

/* misc helpers */

व्योम regulator_bulk_set_supply_names(काष्ठा regulator_bulk_data *consumers,
				     स्थिर अक्षर *स्थिर *supply_names,
				     अचिन्हित पूर्णांक num_supplies);

bool regulator_is_equal(काष्ठा regulator *reg1, काष्ठा regulator *reg2);

#अन्यथा

/*
 * Make sure client drivers will still build on प्रणालीs with no software
 * controllable voltage or current regulators.
 */
अटल अंतरभूत काष्ठा regulator *__must_check regulator_get(काष्ठा device *dev,
	स्थिर अक्षर *id)
अणु
	/* Nothing except the stubbed out regulator API should be
	 * looking at the value except to check अगर it is an error
	 * value. Drivers are मुक्त to handle शून्य specअगरically by
	 * skipping all regulator API calls, but they करोn't have to.
	 * Drivers which करोn't, should make sure they properly handle
	 * corner हालs of the API, such as regulator_get_voltage()
	 * वापसing 0.
	 */
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा regulator *__must_check
devm_regulator_get(काष्ठा device *dev, स्थिर अक्षर *id)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा regulator *__must_check
regulator_get_exclusive(काष्ठा device *dev, स्थिर अक्षर *id)
अणु
	वापस ERR_PTR(-ENODEV);
पूर्ण

अटल अंतरभूत काष्ठा regulator *__must_check
devm_regulator_get_exclusive(काष्ठा device *dev, स्थिर अक्षर *id)
अणु
	वापस ERR_PTR(-ENODEV);
पूर्ण

अटल अंतरभूत काष्ठा regulator *__must_check
regulator_get_optional(काष्ठा device *dev, स्थिर अक्षर *id)
अणु
	वापस ERR_PTR(-ENODEV);
पूर्ण


अटल अंतरभूत काष्ठा regulator *__must_check
devm_regulator_get_optional(काष्ठा device *dev, स्थिर अक्षर *id)
अणु
	वापस ERR_PTR(-ENODEV);
पूर्ण

अटल अंतरभूत व्योम regulator_put(काष्ठा regulator *regulator)
अणु
पूर्ण

अटल अंतरभूत व्योम devm_regulator_put(काष्ठा regulator *regulator)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक regulator_रेजिस्टर_supply_alias(काष्ठा device *dev,
						  स्थिर अक्षर *id,
						  काष्ठा device *alias_dev,
						  स्थिर अक्षर *alias_id)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम regulator_unरेजिस्टर_supply_alias(काष्ठा device *dev,
						    स्थिर अक्षर *id)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक regulator_bulk_रेजिस्टर_supply_alias(काष्ठा device *dev,
						स्थिर अक्षर *स्थिर *id,
						काष्ठा device *alias_dev,
						स्थिर अक्षर * स्थिर *alias_id,
						पूर्णांक num_id)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम regulator_bulk_unरेजिस्टर_supply_alias(काष्ठा device *dev,
						स्थिर अक्षर * स्थिर *id,
						पूर्णांक num_id)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक devm_regulator_रेजिस्टर_supply_alias(काष्ठा device *dev,
						       स्थिर अक्षर *id,
						       काष्ठा device *alias_dev,
						       स्थिर अक्षर *alias_id)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम devm_regulator_unरेजिस्टर_supply_alias(काष्ठा device *dev,
							  स्थिर अक्षर *id)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक devm_regulator_bulk_रेजिस्टर_supply_alias(काष्ठा device *dev,
						स्थिर अक्षर *स्थिर *id,
						काष्ठा device *alias_dev,
						स्थिर अक्षर *स्थिर *alias_id,
						पूर्णांक num_id)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम devm_regulator_bulk_unरेजिस्टर_supply_alias(
	काष्ठा device *dev, स्थिर अक्षर *स्थिर *id, पूर्णांक num_id)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक regulator_enable(काष्ठा regulator *regulator)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक regulator_disable(काष्ठा regulator *regulator)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक regulator_क्रमce_disable(काष्ठा regulator *regulator)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक regulator_disable_deferred(काष्ठा regulator *regulator,
					     पूर्णांक ms)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक regulator_is_enabled(काष्ठा regulator *regulator)
अणु
	वापस 1;
पूर्ण

अटल अंतरभूत पूर्णांक regulator_bulk_get(काष्ठा device *dev,
				     पूर्णांक num_consumers,
				     काष्ठा regulator_bulk_data *consumers)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक devm_regulator_bulk_get(काष्ठा device *dev, पूर्णांक num_consumers,
					  काष्ठा regulator_bulk_data *consumers)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक regulator_bulk_enable(पूर्णांक num_consumers,
					काष्ठा regulator_bulk_data *consumers)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक regulator_bulk_disable(पूर्णांक num_consumers,
					 काष्ठा regulator_bulk_data *consumers)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक regulator_bulk_क्रमce_disable(पूर्णांक num_consumers,
					काष्ठा regulator_bulk_data *consumers)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम regulator_bulk_मुक्त(पूर्णांक num_consumers,
				       काष्ठा regulator_bulk_data *consumers)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक regulator_set_voltage(काष्ठा regulator *regulator,
					पूर्णांक min_uV, पूर्णांक max_uV)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक regulator_set_voltage_समय(काष्ठा regulator *regulator,
					     पूर्णांक old_uV, पूर्णांक new_uV)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक regulator_get_voltage(काष्ठा regulator *regulator)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक regulator_sync_voltage(काष्ठा regulator *regulator)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक regulator_is_supported_voltage(काष्ठा regulator *regulator,
				   पूर्णांक min_uV, पूर्णांक max_uV)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक regulator_get_linear_step(काष्ठा regulator *regulator)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक regulator_set_current_limit(काष्ठा regulator *regulator,
					     पूर्णांक min_uA, पूर्णांक max_uA)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक regulator_get_current_limit(काष्ठा regulator *regulator)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक regulator_set_mode(काष्ठा regulator *regulator,
	अचिन्हित पूर्णांक mode)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक regulator_get_mode(काष्ठा regulator *regulator)
अणु
	वापस REGULATOR_MODE_NORMAL;
पूर्ण

अटल अंतरभूत पूर्णांक regulator_get_error_flags(काष्ठा regulator *regulator,
					    अचिन्हित पूर्णांक *flags)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक regulator_set_load(काष्ठा regulator *regulator, पूर्णांक load_uA)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक regulator_allow_bypass(काष्ठा regulator *regulator,
					 bool allow)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा regmap *regulator_get_regmap(काष्ठा regulator *regulator)
अणु
	वापस ERR_PTR(-EOPNOTSUPP);
पूर्ण

अटल अंतरभूत पूर्णांक regulator_get_hardware_vsel_रेजिस्टर(काष्ठा regulator *regulator,
						       अचिन्हित *vsel_reg,
						       अचिन्हित *vsel_mask)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक regulator_list_hardware_vsel(काष्ठा regulator *regulator,
					       अचिन्हित selector)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक regulator_रेजिस्टर_notअगरier(काष्ठा regulator *regulator,
			      काष्ठा notअगरier_block *nb)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक devm_regulator_रेजिस्टर_notअगरier(काष्ठा regulator *regulator,
						   काष्ठा notअगरier_block *nb)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक regulator_unरेजिस्टर_notअगरier(काष्ठा regulator *regulator,
				काष्ठा notअगरier_block *nb)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक devm_regulator_unरेजिस्टर_notअगरier(काष्ठा regulator *regulator,
						     काष्ठा notअगरier_block *nb)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक regulator_suspend_enable(काष्ठा regulator_dev *rdev,
					   suspend_state_t state)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक regulator_suspend_disable(काष्ठा regulator_dev *rdev,
					    suspend_state_t state)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक regulator_set_suspend_voltage(काष्ठा regulator *regulator,
						पूर्णांक min_uV, पूर्णांक max_uV,
						suspend_state_t state)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत व्योम *regulator_get_drvdata(काष्ठा regulator *regulator)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम regulator_set_drvdata(काष्ठा regulator *regulator,
	व्योम *data)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक regulator_count_voltages(काष्ठा regulator *regulator)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक regulator_list_voltage(काष्ठा regulator *regulator, अचिन्हित selector)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत व्योम
regulator_bulk_set_supply_names(काष्ठा regulator_bulk_data *consumers,
				स्थिर अक्षर *स्थिर *supply_names,
				अचिन्हित पूर्णांक num_supplies)
अणु
पूर्ण

अटल अंतरभूत bool
regulator_is_equal(काष्ठा regulator *reg1, काष्ठा regulator *reg2)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक regulator_set_voltage_triplet(काष्ठा regulator *regulator,
						पूर्णांक min_uV, पूर्णांक target_uV,
						पूर्णांक max_uV)
अणु
	अगर (regulator_set_voltage(regulator, target_uV, max_uV) == 0)
		वापस 0;

	वापस regulator_set_voltage(regulator, min_uV, max_uV);
पूर्ण

अटल अंतरभूत पूर्णांक regulator_set_voltage_tol(काष्ठा regulator *regulator,
					    पूर्णांक new_uV, पूर्णांक tol_uV)
अणु
	अगर (regulator_set_voltage(regulator, new_uV, new_uV + tol_uV) == 0)
		वापस 0;
	अन्यथा
		वापस regulator_set_voltage(regulator,
					     new_uV - tol_uV, new_uV + tol_uV);
पूर्ण

अटल अंतरभूत पूर्णांक regulator_is_supported_voltage_tol(काष्ठा regulator *regulator,
						     पूर्णांक target_uV, पूर्णांक tol_uV)
अणु
	वापस regulator_is_supported_voltage(regulator,
					      target_uV - tol_uV,
					      target_uV + tol_uV);
पूर्ण

#पूर्ण_अगर
