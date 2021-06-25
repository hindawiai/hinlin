<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Platक्रमm data क्रम ST STA350 ASoC codec driver.
 *
 * Copyright: 2014 Raumfeld GmbH
 * Author: Sven Bअक्रमau <info@bअक्रमau.biz>
 */
#अगर_अघोषित __LINUX_SND__STA350_H
#घोषणा __LINUX_SND__STA350_H

#घोषणा STA350_OCFG_2CH		0
#घोषणा STA350_OCFG_2_1CH	1
#घोषणा STA350_OCFG_1CH		3

#घोषणा STA350_OM_CH1		0
#घोषणा STA350_OM_CH2		1
#घोषणा STA350_OM_CH3		2

#घोषणा STA350_THERMAL_ADJUSTMENT_ENABLE	1
#घोषणा STA350_THERMAL_RECOVERY_ENABLE		2
#घोषणा STA350_FAULT_DETECT_RECOVERY_BYPASS	1

#घोषणा STA350_FFX_PM_DROP_COMP			0
#घोषणा STA350_FFX_PM_TAPERED_COMP		1
#घोषणा STA350_FFX_PM_FULL_POWER		2
#घोषणा STA350_FFX_PM_VARIABLE_DROP_COMP	3


काष्ठा sta350_platक्रमm_data अणु
	u8 output_conf;
	u8 ch1_output_mapping;
	u8 ch2_output_mapping;
	u8 ch3_output_mapping;
	u8 ffx_घातer_output_mode;
	u8 drop_compensation_ns;
	u8 घातerकरोwn_delay_भागider;
	अचिन्हित पूर्णांक thermal_warning_recovery:1;
	अचिन्हित पूर्णांक thermal_warning_adjusपंचांगent:1;
	अचिन्हित पूर्णांक fault_detect_recovery:1;
	अचिन्हित पूर्णांक oc_warning_adjusपंचांगent:1;
	अचिन्हित पूर्णांक max_घातer_use_mpcc:1;
	अचिन्हित पूर्णांक max_घातer_correction:1;
	अचिन्हित पूर्णांक am_reduction_mode:1;
	अचिन्हित पूर्णांक odd_pwm_speed_mode:1;
	अचिन्हित पूर्णांक distortion_compensation:1;
	अचिन्हित पूर्णांक invalid_input_detect_mute:1;
	अचिन्हित पूर्णांक activate_mute_output:1;
	अचिन्हित पूर्णांक bridge_immediate_off:1;
	अचिन्हित पूर्णांक noise_shape_dc_cut:1;
	अचिन्हित पूर्णांक घातerकरोwn_master_vol:1;
पूर्ण;

#पूर्ण_अगर /* __LINUX_SND__STA350_H */
