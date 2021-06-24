<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * max8973-regulator.h -- MAXIM 8973 regulator
 *
 * Interface क्रम regulator driver क्रम MAXIM 8973 DC-DC step-करोwn
 * चयनing regulator.
 *
 * Copyright (C) 2012 NVIDIA Corporation

 * Author: Laxman Dewangan <ldewangan@nvidia.com>
 */

#अगर_अघोषित __LINUX_REGULATOR_MAX8973_H
#घोषणा __LINUX_REGULATOR_MAX8973_H

/*
 * Control flags क्रम configuration of the device.
 * Client need to pass this inक्रमmation with ORed
 */
#घोषणा MAX8973_CONTROL_REMOTE_SENSE_ENABLE			0x00000001
#घोषणा MAX8973_CONTROL_FALLING_SLEW_RATE_ENABLE		0x00000002
#घोषणा MAX8973_CONTROL_OUTPUT_ACTIVE_DISCH_ENABLE		0x00000004
#घोषणा MAX8973_CONTROL_BIAS_ENABLE				0x00000008
#घोषणा MAX8973_CONTROL_PULL_DOWN_ENABLE			0x00000010
#घोषणा MAX8973_CONTROL_FREQ_SHIFT_9PER_ENABLE			0x00000020

#घोषणा MAX8973_CONTROL_CLKADV_TRIP_DISABLED			0x00000000
#घोषणा MAX8973_CONTROL_CLKADV_TRIP_75mV_PER_US			0x00010000
#घोषणा MAX8973_CONTROL_CLKADV_TRIP_150mV_PER_US		0x00020000
#घोषणा MAX8973_CONTROL_CLKADV_TRIP_75mV_PER_US_HIST_DIS	0x00030000

#घोषणा MAX8973_CONTROL_INDUCTOR_VALUE_NOMINAL			0x00000000
#घोषणा MAX8973_CONTROL_INDUCTOR_VALUE_MINUS_30_PER		0x00100000
#घोषणा MAX8973_CONTROL_INDUCTOR_VALUE_PLUS_30_PER		0x00200000
#घोषणा MAX8973_CONTROL_INDUCTOR_VALUE_PLUS_60_PER		0x00300000

/*
 * काष्ठा max8973_regulator_platक्रमm_data - max8973 regulator platक्रमm data.
 *
 * @reg_init_data: The regulator init data.
 * @control_flags: Control flags which are ORed value of above flags to
 *		configure device.
 * @junction_temp_warning: Junction temp in millicelcius on which warning need
 *			   to be set. Thermal functionality is only supported on
 *			   MAX77621. The threshold warning supported by MAX77621
 *			   are 120C and 140C.
 * @enable_ext_control: Enable the voltage enable/disable through बाह्यal
 *		control संकेत from EN input pin. If it is false then
 *		voltage output will be enabled/disabled through EN bit of
 *		device रेजिस्टर.
 * @enable_gpio: Enable GPIO. If EN pin is controlled through GPIO from host
 *		then GPIO number can be provided. If no GPIO controlled then
 *		it should be -1.
 * @dvs_gpio: GPIO क्रम dvs. It should be -1 अगर this is tied with fixed logic.
 * @dvs_def_state: Default state of dvs. 1 अगर it is high अन्यथा 0.
 */
काष्ठा max8973_regulator_platक्रमm_data अणु
	काष्ठा regulator_init_data *reg_init_data;
	अचिन्हित दीर्घ control_flags;
	अचिन्हित दीर्घ junction_temp_warning;
	bool enable_ext_control;
	पूर्णांक enable_gpio;
	पूर्णांक dvs_gpio;
	अचिन्हित dvs_def_state:1;
पूर्ण;

#पूर्ण_अगर /* __LINUX_REGULATOR_MAX8973_H */
