<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * cxd2880_tnrdmd_dvbt_mon.h
 * Sony CXD2880 DVB-T2/T tuner + demodulator driver
 * DVB-T monitor पूर्णांकerface
 *
 * Copyright (C) 2016, 2017, 2018 Sony Semiconductor Solutions Corporation
 */

#अगर_अघोषित CXD2880_TNRDMD_DVBT_MON_H
#घोषणा CXD2880_TNRDMD_DVBT_MON_H

#समावेश "cxd2880_tnrdmd.h"
#समावेश "cxd2880_dvbt.h"

पूर्णांक cxd2880_tnrdmd_dvbt_mon_sync_stat(काष्ठा cxd2880_tnrdmd
				      *tnr_dmd, u8 *sync_stat,
				      u8 *ts_lock_stat,
				      u8 *unlock_detected);

पूर्णांक cxd2880_tnrdmd_dvbt_mon_sync_stat_sub(काष्ठा cxd2880_tnrdmd
					  *tnr_dmd, u8 *sync_stat,
					  u8 *unlock_detected);

पूर्णांक cxd2880_tnrdmd_dvbt_mon_mode_guard(काष्ठा cxd2880_tnrdmd
				       *tnr_dmd,
				       क्रमागत cxd2880_dvbt_mode
				       *mode,
				       क्रमागत cxd2880_dvbt_guard
				       *guard);

पूर्णांक cxd2880_tnrdmd_dvbt_mon_carrier_offset(काष्ठा cxd2880_tnrdmd
					   *tnr_dmd, पूर्णांक *offset);

पूर्णांक cxd2880_tnrdmd_dvbt_mon_carrier_offset_sub(काष्ठा
					       cxd2880_tnrdmd
					       *tnr_dmd,
					       पूर्णांक *offset);

पूर्णांक cxd2880_tnrdmd_dvbt_mon_tps_info(काष्ठा cxd2880_tnrdmd
				     *tnr_dmd,
				     काष्ठा cxd2880_dvbt_tpsinfo
				     *info);

पूर्णांक cxd2880_tnrdmd_dvbt_mon_packet_error_number(काष्ठा
						cxd2880_tnrdmd
						*tnr_dmd,
						u32 *pen);

पूर्णांक cxd2880_tnrdmd_dvbt_mon_spectrum_sense(काष्ठा cxd2880_tnrdmd
					   *tnr_dmd,
					   क्रमागत
					   cxd2880_tnrdmd_spectrum_sense
					   *sense);

पूर्णांक cxd2880_tnrdmd_dvbt_mon_snr(काष्ठा cxd2880_tnrdmd *tnr_dmd,
				पूर्णांक *snr);

पूर्णांक cxd2880_tnrdmd_dvbt_mon_snr_भागer(काष्ठा cxd2880_tnrdmd
				      *tnr_dmd, पूर्णांक *snr,
				      पूर्णांक *snr_मुख्य, पूर्णांक *snr_sub);

पूर्णांक cxd2880_tnrdmd_dvbt_mon_sampling_offset(काष्ठा cxd2880_tnrdmd
					    *tnr_dmd, पूर्णांक *ppm);

पूर्णांक cxd2880_tnrdmd_dvbt_mon_sampling_offset_sub(काष्ठा
						cxd2880_tnrdmd
						*tnr_dmd,
						पूर्णांक *ppm);

पूर्णांक cxd2880_tnrdmd_dvbt_mon_ssi(काष्ठा cxd2880_tnrdmd *tnr_dmd,
				u8 *ssi);

पूर्णांक cxd2880_tnrdmd_dvbt_mon_ssi_sub(काष्ठा cxd2880_tnrdmd *tnr_dmd,
				    u8 *ssi);

#पूर्ण_अगर
