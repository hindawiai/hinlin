<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
* Simple driver क्रम Texas Instruments LM3630A LED Flash driver chip
* Copyright (C) 2012 Texas Instruments
*/

#अगर_अघोषित __LINUX_LM3630A_H
#घोषणा __LINUX_LM3630A_H

#घोषणा LM3630A_NAME "lm3630a_bl"

क्रमागत lm3630a_pwm_ctrl अणु
	LM3630A_PWM_DISABLE = 0x00,
	LM3630A_PWM_BANK_A,
	LM3630A_PWM_BANK_B,
	LM3630A_PWM_BANK_ALL,
	LM3630A_PWM_BANK_A_ACT_LOW = 0x05,
	LM3630A_PWM_BANK_B_ACT_LOW,
	LM3630A_PWM_BANK_ALL_ACT_LOW,
पूर्ण;

क्रमागत lm3630a_leda_ctrl अणु
	LM3630A_LEDA_DISABLE = 0x00,
	LM3630A_LEDA_ENABLE = 0x04,
	LM3630A_LEDA_ENABLE_LINEAR = 0x14,
पूर्ण;

क्रमागत lm3630a_ledb_ctrl अणु
	LM3630A_LEDB_DISABLE = 0x00,
	LM3630A_LEDB_ON_A = 0x01,
	LM3630A_LEDB_ENABLE = 0x02,
	LM3630A_LEDB_ENABLE_LINEAR = 0x0A,
पूर्ण;

#घोषणा LM3630A_MAX_BRIGHTNESS 255
/*
 *@leda_label    : optional led a label.
 *@leda_init_brt : led a init brightness. 4~255
 *@leda_max_brt  : led a max brightness.  4~255
 *@leda_ctrl     : led a disable, enable linear, enable exponential
 *@ledb_label    : optional led b label.
 *@ledb_init_brt : led b init brightness. 4~255
 *@ledb_max_brt  : led b max brightness.  4~255
 *@ledb_ctrl     : led b disable, enable linear, enable exponential
 *@pwm_period    : pwm period
 *@pwm_ctrl      : pwm disable, bank a or b, active high or low
 */
काष्ठा lm3630a_platक्रमm_data अणु

	/* led a config.  */
	स्थिर अक्षर *leda_label;
	पूर्णांक leda_init_brt;
	पूर्णांक leda_max_brt;
	क्रमागत lm3630a_leda_ctrl leda_ctrl;
	/* led b config. */
	स्थिर अक्षर *ledb_label;
	पूर्णांक ledb_init_brt;
	पूर्णांक ledb_max_brt;
	क्रमागत lm3630a_ledb_ctrl ledb_ctrl;
	/* pwm config. */
	अचिन्हित पूर्णांक pwm_period;
	क्रमागत lm3630a_pwm_ctrl pwm_ctrl;
पूर्ण;

#पूर्ण_अगर /* __LINUX_LM3630A_H */
