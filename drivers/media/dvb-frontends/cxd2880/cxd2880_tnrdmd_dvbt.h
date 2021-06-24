<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * cxd2880_tnrdmd_dvbt.h
 * Sony CXD2880 DVB-T2/T tuner + demodulator driver
 * control पूर्णांकerface क्रम DVB-T
 *
 * Copyright (C) 2016, 2017, 2018 Sony Semiconductor Solutions Corporation
 */

#अगर_अघोषित CXD2880_TNRDMD_DVBT_H
#घोषणा CXD2880_TNRDMD_DVBT_H

#समावेश "cxd2880_common.h"
#समावेश "cxd2880_tnrdmd.h"

काष्ठा cxd2880_dvbt_tune_param अणु
	u32 center_freq_khz;
	क्रमागत cxd2880_dtv_bandwidth bandwidth;
	क्रमागत cxd2880_dvbt_profile profile;
पूर्ण;

पूर्णांक cxd2880_tnrdmd_dvbt_tune1(काष्ठा cxd2880_tnrdmd *tnr_dmd,
			      काष्ठा cxd2880_dvbt_tune_param
			      *tune_param);

पूर्णांक cxd2880_tnrdmd_dvbt_tune2(काष्ठा cxd2880_tnrdmd *tnr_dmd,
			      काष्ठा cxd2880_dvbt_tune_param
			      *tune_param);

पूर्णांक cxd2880_tnrdmd_dvbt_sleep_setting(काष्ठा cxd2880_tnrdmd
				      *tnr_dmd);

पूर्णांक cxd2880_tnrdmd_dvbt_check_demod_lock(काष्ठा cxd2880_tnrdmd
					 *tnr_dmd,
					 क्रमागत
					 cxd2880_tnrdmd_lock_result
					 *lock);

पूर्णांक cxd2880_tnrdmd_dvbt_check_ts_lock(काष्ठा cxd2880_tnrdmd
				      *tnr_dmd,
				      क्रमागत
				      cxd2880_tnrdmd_lock_result
				      *lock);

#पूर्ण_अगर
