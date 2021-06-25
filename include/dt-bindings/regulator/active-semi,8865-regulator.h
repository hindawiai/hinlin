<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Device Tree binding स्थिरants क्रम the ACT8865 PMIC regulators
 */

#अगर_अघोषित _DT_BINDINGS_REGULATOR_ACT8865_H
#घोषणा _DT_BINDINGS_REGULATOR_ACT8865_H

/*
 * These स्थिरants should be used to specअगरy regulator modes in device tree क्रम
 * ACT8865 regulators as follows:
 * ACT8865_REGULATOR_MODE_FIXED:	It is specअगरic to DCDC regulators and it
 *					specअगरies the usage of fixed-frequency
 *					PWM.
 *
 * ACT8865_REGULATOR_MODE_NORMAL:	It is specअगरic to LDO regulators and it
 *					specअगरies the usage of normal mode.
 *
 * ACT8865_REGULATOR_MODE_LOWPOWER:	For DCDC and LDO regulators; it specअगरy
 *					the usage of proprietary घातer-saving
 *					mode.
 */

#घोषणा ACT8865_REGULATOR_MODE_FIXED		1
#घोषणा ACT8865_REGULATOR_MODE_NORMAL		2
#घोषणा ACT8865_REGULATOR_MODE_LOWPOWER	3

#पूर्ण_अगर
