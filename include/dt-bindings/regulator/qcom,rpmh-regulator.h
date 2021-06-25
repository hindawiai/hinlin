<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (c) 2018, The Linux Foundation. All rights reserved. */

#अगर_अघोषित __QCOM_RPMH_REGULATOR_H
#घोषणा __QCOM_RPMH_REGULATOR_H

/*
 * These mode स्थिरants may be used to specअगरy modes क्रम various RPMh regulator
 * device tree properties (e.g. regulator-initial-mode).  Each type of regulator
 * supports a subset of the possible modes.
 *
 * %RPMH_REGULATOR_MODE_RET:	Retention mode in which only an extremely small
 *				load current is allowed.  This mode is supported
 *				by LDO and SMPS type regulators.
 * %RPMH_REGULATOR_MODE_LPM:	Low घातer mode in which a small load current is
 *				allowed.  This mode corresponds to PFM क्रम SMPS
 *				and BOB type regulators.  This mode is supported
 *				by LDO, HFSMPS, BOB, and PMIC4 FTSMPS type
 *				regulators.
 * %RPMH_REGULATOR_MODE_AUTO:	Auto mode in which the regulator hardware
 *				स्वतःmatically चयनes between LPM and HPM based
 *				upon the real-समय load current.  This mode is
 *				supported by HFSMPS, BOB, and PMIC4 FTSMPS type
 *				regulators.
 * %RPMH_REGULATOR_MODE_HPM:	High घातer mode in which the full rated current
 *				of the regulator is allowed.  This mode
 *				corresponds to PWM क्रम SMPS and BOB type
 *				regulators.  This mode is supported by all types
 *				of regulators.
 */
#घोषणा RPMH_REGULATOR_MODE_RET		0
#घोषणा RPMH_REGULATOR_MODE_LPM		1
#घोषणा RPMH_REGULATOR_MODE_AUTO	2
#घोषणा RPMH_REGULATOR_MODE_HPM		3

#पूर्ण_अगर
