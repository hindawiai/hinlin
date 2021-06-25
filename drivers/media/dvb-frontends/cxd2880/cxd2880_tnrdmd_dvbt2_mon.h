<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * cxd2880_tnrdmd_dvbt2_mon.h
 * Sony CXD2880 DVB-T2/T tuner + demodulator driver
 * DVB-T2 monitor पूर्णांकerface
 *
 * Copyright (C) 2016, 2017, 2018 Sony Semiconductor Solutions Corporation
 */

#अगर_अघोषित CXD2880_TNRDMD_DVBT2_MON_H
#घोषणा CXD2880_TNRDMD_DVBT2_MON_H

#समावेश "cxd2880_tnrdmd.h"
#समावेश "cxd2880_dvbt2.h"

पूर्णांक cxd2880_tnrdmd_dvbt2_mon_sync_stat(काष्ठा cxd2880_tnrdmd
				       *tnr_dmd, u8 *sync_stat,
				       u8 *ts_lock_stat,
				       u8 *unlock_detected);

पूर्णांक cxd2880_tnrdmd_dvbt2_mon_sync_stat_sub(काष्ठा cxd2880_tnrdmd
					   *tnr_dmd,
					   u8 *sync_stat,
					   u8 *unlock_detected);

पूर्णांक cxd2880_tnrdmd_dvbt2_mon_carrier_offset(काष्ठा cxd2880_tnrdmd
					    *tnr_dmd, पूर्णांक *offset);

पूर्णांक cxd2880_tnrdmd_dvbt2_mon_carrier_offset_sub(काष्ठा
						cxd2880_tnrdmd
						*tnr_dmd,
						पूर्णांक *offset);

पूर्णांक cxd2880_tnrdmd_dvbt2_mon_l1_pre(काष्ठा cxd2880_tnrdmd *tnr_dmd,
				    काष्ठा cxd2880_dvbt2_l1pre
				    *l1_pre);

पूर्णांक cxd2880_tnrdmd_dvbt2_mon_version(काष्ठा cxd2880_tnrdmd
				     *tnr_dmd,
				     क्रमागत cxd2880_dvbt2_version
				     *ver);

पूर्णांक cxd2880_tnrdmd_dvbt2_mon_ofdm(काष्ठा cxd2880_tnrdmd *tnr_dmd,
				  काष्ठा cxd2880_dvbt2_ofdm *ofdm);

पूर्णांक cxd2880_tnrdmd_dvbt2_mon_data_plps(काष्ठा cxd2880_tnrdmd
				       *tnr_dmd, u8 *plp_ids,
				       u8 *num_plps);

पूर्णांक cxd2880_tnrdmd_dvbt2_mon_active_plp(काष्ठा cxd2880_tnrdmd
					*tnr_dmd,
					क्रमागत
					cxd2880_dvbt2_plp_btype
					type,
					काष्ठा cxd2880_dvbt2_plp
					*plp_info);

पूर्णांक cxd2880_tnrdmd_dvbt2_mon_data_plp_error(काष्ठा cxd2880_tnrdmd
					    *tnr_dmd,
					    u8 *plp_error);

पूर्णांक cxd2880_tnrdmd_dvbt2_mon_l1_change(काष्ठा cxd2880_tnrdmd
				       *tnr_dmd, u8 *l1_change);

पूर्णांक cxd2880_tnrdmd_dvbt2_mon_l1_post(काष्ठा cxd2880_tnrdmd
				     *tnr_dmd,
				     काष्ठा cxd2880_dvbt2_l1post
				     *l1_post);

पूर्णांक cxd2880_tnrdmd_dvbt2_mon_bbheader(काष्ठा cxd2880_tnrdmd
				      *tnr_dmd,
				      क्रमागत cxd2880_dvbt2_plp_btype
				      type,
				      काष्ठा cxd2880_dvbt2_bbheader
				      *bbheader);

पूर्णांक cxd2880_tnrdmd_dvbt2_mon_in_bandb_ts_rate(काष्ठा cxd2880_tnrdmd
					      *tnr_dmd,
					      क्रमागत
					      cxd2880_dvbt2_plp_btype
					      type,
					      u32 *ts_rate_bps);

पूर्णांक cxd2880_tnrdmd_dvbt2_mon_spectrum_sense(काष्ठा cxd2880_tnrdmd
					    *tnr_dmd,
					    क्रमागत
					    cxd2880_tnrdmd_spectrum_sense
					    *sense);

पूर्णांक cxd2880_tnrdmd_dvbt2_mon_snr(काष्ठा cxd2880_tnrdmd *tnr_dmd,
				 पूर्णांक *snr);

पूर्णांक cxd2880_tnrdmd_dvbt2_mon_snr_भागer(काष्ठा cxd2880_tnrdmd
				       *tnr_dmd, पूर्णांक *snr,
				       पूर्णांक *snr_मुख्य,
				       पूर्णांक *snr_sub);

पूर्णांक cxd2880_tnrdmd_dvbt2_mon_packet_error_number(काष्ठा
						 cxd2880_tnrdmd
						 *tnr_dmd,
						 u32 *pen);

पूर्णांक cxd2880_tnrdmd_dvbt2_mon_sampling_offset(काष्ठा cxd2880_tnrdmd
					     *tnr_dmd, पूर्णांक *ppm);

पूर्णांक cxd2880_tnrdmd_dvbt2_mon_sampling_offset_sub(काष्ठा
						 cxd2880_tnrdmd
						 *tnr_dmd,
						 पूर्णांक *ppm);

पूर्णांक cxd2880_tnrdmd_dvbt2_mon_qam(काष्ठा cxd2880_tnrdmd *tnr_dmd,
				 क्रमागत cxd2880_dvbt2_plp_btype type,
				 क्रमागत cxd2880_dvbt2_plp_स्थिरell
				 *qam);

पूर्णांक cxd2880_tnrdmd_dvbt2_mon_code_rate(काष्ठा cxd2880_tnrdmd
				       *tnr_dmd,
				       क्रमागत cxd2880_dvbt2_plp_btype
				       type,
				       क्रमागत
				       cxd2880_dvbt2_plp_code_rate
				       *code_rate);

पूर्णांक cxd2880_tnrdmd_dvbt2_mon_profile(काष्ठा cxd2880_tnrdmd
				     *tnr_dmd,
				     क्रमागत cxd2880_dvbt2_profile
				     *profile);

पूर्णांक cxd2880_tnrdmd_dvbt2_mon_ssi(काष्ठा cxd2880_tnrdmd *tnr_dmd,
				 u8 *ssi);

पूर्णांक cxd2880_tnrdmd_dvbt2_mon_ssi_sub(काष्ठा cxd2880_tnrdmd
				     *tnr_dmd, u8 *ssi);

#पूर्ण_अगर
