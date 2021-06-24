<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Platक्रमm data क्रम ST STA32x ASoC codec driver.
 *
 * Copyright: 2011 Raumfeld GmbH
 * Author: Johannes Stezenbach <js@sig21.net>
 */
#अगर_अघोषित __LINUX_SND__STA32X_H
#घोषणा __LINUX_SND__STA32X_H

#घोषणा STA32X_OCFG_2CH		0
#घोषणा STA32X_OCFG_2_1CH	1
#घोषणा STA32X_OCFG_1CH		3

#घोषणा STA32X_OM_CH1		0
#घोषणा STA32X_OM_CH2		1
#घोषणा STA32X_OM_CH3		2

#घोषणा STA32X_THERMAL_ADJUSTMENT_ENABLE	1
#घोषणा STA32X_THERMAL_RECOVERY_ENABLE		2

काष्ठा sta32x_platक्रमm_data अणु
	u8 output_conf;
	u8 ch1_output_mapping;
	u8 ch2_output_mapping;
	u8 ch3_output_mapping;
	पूर्णांक needs_esd_watchकरोg;
	u8 drop_compensation_ns;
	अचिन्हित पूर्णांक thermal_warning_recovery:1;
	अचिन्हित पूर्णांक thermal_warning_adjusपंचांगent:1;
	अचिन्हित पूर्णांक fault_detect_recovery:1;
	अचिन्हित पूर्णांक max_घातer_use_mpcc:1;
	अचिन्हित पूर्णांक max_घातer_correction:1;
	अचिन्हित पूर्णांक am_reduction_mode:1;
	अचिन्हित पूर्णांक odd_pwm_speed_mode:1;
	अचिन्हित पूर्णांक invalid_input_detect_mute:1;
पूर्ण;

#पूर्ण_अगर /* __LINUX_SND__STA32X_H */
