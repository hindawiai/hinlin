<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * cxd2880_tnrdmd_dvbt2.h
 * Sony CXD2880 DVB-T2/T tuner + demodulator driver
 * control पूर्णांकerface क्रम DVB-T2
 *
 * Copyright (C) 2016, 2017, 2018 Sony Semiconductor Solutions Corporation
 */

#अगर_अघोषित CXD2880_TNRDMD_DVBT2_H
#घोषणा CXD2880_TNRDMD_DVBT2_H

#समावेश "cxd2880_common.h"
#समावेश "cxd2880_tnrdmd.h"

क्रमागत cxd2880_tnrdmd_dvbt2_tune_info अणु
	CXD2880_TNRDMD_DVBT2_TUNE_INFO_OK,
	CXD2880_TNRDMD_DVBT2_TUNE_INFO_INVALID_PLP_ID
पूर्ण;

काष्ठा cxd2880_dvbt2_tune_param अणु
	u32 center_freq_khz;
	क्रमागत cxd2880_dtv_bandwidth bandwidth;
	u16 data_plp_id;
	क्रमागत cxd2880_dvbt2_profile profile;
	क्रमागत cxd2880_tnrdmd_dvbt2_tune_info tune_info;
पूर्ण;

#घोषणा CXD2880_DVBT2_TUNE_PARAM_PLPID_AUTO  0xffff

पूर्णांक cxd2880_tnrdmd_dvbt2_tune1(काष्ठा cxd2880_tnrdmd *tnr_dmd,
			       काष्ठा cxd2880_dvbt2_tune_param
			       *tune_param);

पूर्णांक cxd2880_tnrdmd_dvbt2_tune2(काष्ठा cxd2880_tnrdmd *tnr_dmd,
			       काष्ठा cxd2880_dvbt2_tune_param
			       *tune_param);

पूर्णांक cxd2880_tnrdmd_dvbt2_sleep_setting(काष्ठा cxd2880_tnrdmd
				       *tnr_dmd);

पूर्णांक cxd2880_tnrdmd_dvbt2_check_demod_lock(काष्ठा cxd2880_tnrdmd
					  *tnr_dmd,
					  क्रमागत
					  cxd2880_tnrdmd_lock_result
					  *lock);

पूर्णांक cxd2880_tnrdmd_dvbt2_check_ts_lock(काष्ठा cxd2880_tnrdmd
				       *tnr_dmd,
				       क्रमागत
				       cxd2880_tnrdmd_lock_result
				       *lock);

पूर्णांक cxd2880_tnrdmd_dvbt2_set_plp_cfg(काष्ठा cxd2880_tnrdmd
				     *tnr_dmd, u8 स्वतः_plp,
				     u8 plp_id);

पूर्णांक cxd2880_tnrdmd_dvbt2_भागer_fef_setting(काष्ठा cxd2880_tnrdmd
					   *tnr_dmd);

पूर्णांक cxd2880_tnrdmd_dvbt2_check_l1post_valid(काष्ठा cxd2880_tnrdmd
					    *tnr_dmd,
					    u8 *l1_post_valid);

#पूर्ण_अगर
