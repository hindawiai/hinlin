<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * coupler.h -- SoC Regulator support, coupler API.
 *
 * Regulator Coupler Interface.
 */

#अगर_अघोषित __LINUX_REGULATOR_COUPLER_H_
#घोषणा __LINUX_REGULATOR_COUPLER_H_

#समावेश <linux/kernel.h>
#समावेश <linux/suspend.h>

काष्ठा regulator_coupler;
काष्ठा regulator_dev;

/**
 * काष्ठा regulator_coupler - customized regulator's coupler
 *
 * Regulator's coupler allows to customize coupling algorithm.
 *
 * @list: couplers list entry
 * @attach_regulator: Callback invoked on creation of a coupled regulator,
 *                    couples are unresolved at this poपूर्णांक. The callee should
 *                    check that it could handle the regulator and वापस 0 on
 *                    success, -त्रुटि_सं on failure and 1 अगर given regulator is
 *                    not suitable क्रम this coupler (हाल of having multiple
 *                    regulators in a प्रणाली). Callback shall be implemented.
 * @detach_regulator: Callback invoked on deकाष्ठाion of a coupled regulator.
 *                    This callback is optional and could be शून्य.
 * @balance_voltage: Callback invoked when voltage of a coupled regulator is
 *                   changing. Called with all of the coupled rdev's being held
 *                   under "consumer lock". The callee should perक्रमm voltage
 *                   balancing, changing voltage of the coupled regulators as
 *                   needed. It's up to the coupler to verअगरy the voltage
 *                   beक्रमe changing it in hardware, i.e. coupler should
 *                   check consumer's min/max and etc. This callback is
 *                   optional and could be शून्य, in which हाल a generic
 *                   voltage balancer will be used.
 */
काष्ठा regulator_coupler अणु
	काष्ठा list_head list;

	पूर्णांक (*attach_regulator)(काष्ठा regulator_coupler *coupler,
				काष्ठा regulator_dev *rdev);
	पूर्णांक (*detach_regulator)(काष्ठा regulator_coupler *coupler,
				काष्ठा regulator_dev *rdev);
	पूर्णांक (*balance_voltage)(काष्ठा regulator_coupler *coupler,
			       काष्ठा regulator_dev *rdev,
			       suspend_state_t state);
पूर्ण;

#अगर_घोषित CONFIG_REGULATOR
पूर्णांक regulator_coupler_रेजिस्टर(काष्ठा regulator_coupler *coupler);
स्थिर अक्षर *rdev_get_name(काष्ठा regulator_dev *rdev);
पूर्णांक regulator_check_consumers(काष्ठा regulator_dev *rdev,
			      पूर्णांक *min_uV, पूर्णांक *max_uV,
			      suspend_state_t state);
पूर्णांक regulator_check_voltage(काष्ठा regulator_dev *rdev,
			    पूर्णांक *min_uV, पूर्णांक *max_uV);
पूर्णांक regulator_get_voltage_rdev(काष्ठा regulator_dev *rdev);
पूर्णांक regulator_set_voltage_rdev(काष्ठा regulator_dev *rdev,
			       पूर्णांक min_uV, पूर्णांक max_uV,
			       suspend_state_t state);
पूर्णांक regulator_करो_balance_voltage(काष्ठा regulator_dev *rdev,
				 suspend_state_t state, bool skip_coupled);
#अन्यथा
अटल अंतरभूत पूर्णांक regulator_coupler_रेजिस्टर(काष्ठा regulator_coupler *coupler)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत स्थिर अक्षर *rdev_get_name(काष्ठा regulator_dev *rdev)
अणु
	वापस शून्य;
पूर्ण
अटल अंतरभूत पूर्णांक regulator_check_consumers(काष्ठा regulator_dev *rdev,
					    पूर्णांक *min_uV, पूर्णांक *max_uV,
					    suspend_state_t state)
अणु
	वापस -EINVAL;
पूर्ण
अटल अंतरभूत पूर्णांक regulator_check_voltage(काष्ठा regulator_dev *rdev,
					  पूर्णांक *min_uV, पूर्णांक *max_uV)
अणु
	वापस -EINVAL;
पूर्ण
अटल अंतरभूत पूर्णांक regulator_get_voltage_rdev(काष्ठा regulator_dev *rdev)
अणु
	वापस -EINVAL;
पूर्ण
अटल अंतरभूत पूर्णांक regulator_set_voltage_rdev(काष्ठा regulator_dev *rdev,
					     पूर्णांक min_uV, पूर्णांक max_uV,
					     suspend_state_t state)
अणु
	वापस -EINVAL;
पूर्ण
अटल अंतरभूत पूर्णांक regulator_करो_balance_voltage(काष्ठा regulator_dev *rdev,
					       suspend_state_t state,
					       bool skip_coupled)
अणु
	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
