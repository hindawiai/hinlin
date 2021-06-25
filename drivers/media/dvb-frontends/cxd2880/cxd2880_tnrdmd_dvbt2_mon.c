<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * cxd2880_tnrdmd_dvbt2_mon.c
 * Sony CXD2880 DVB-T2/T tuner + demodulator driver
 * DVB-T2 monitor functions
 *
 * Copyright (C) 2016, 2017, 2018 Sony Semiconductor Solutions Corporation
 */

#समावेश "cxd2880_tnrdmd_mon.h"
#समावेश "cxd2880_tnrdmd_dvbt2.h"
#समावेश "cxd2880_tnrdmd_dvbt2_mon.h"

#समावेश <media/dvb_गणित.स>

अटल स्थिर पूर्णांक ref_dbm_1000[4][8] = अणु
	अणु-96000, -95000, -94000, -93000, -92000, -92000, -98000, -97000पूर्ण,
	अणु-91000, -89000, -88000, -87000, -86000, -86000, -93000, -92000पूर्ण,
	अणु-86000, -85000, -83000, -82000, -81000, -80000, -89000, -88000पूर्ण,
	अणु-82000, -80000, -78000, -76000, -75000, -74000, -86000, -84000पूर्ण,
पूर्ण;

पूर्णांक cxd2880_tnrdmd_dvbt2_mon_sync_stat(काष्ठा cxd2880_tnrdmd
				       *tnr_dmd, u8 *sync_stat,
				       u8 *ts_lock_stat,
				       u8 *unlock_detected)
अणु
	u8 data;
	पूर्णांक ret;

	अगर (!tnr_dmd || !sync_stat || !ts_lock_stat || !unlock_detected)
		वापस -EINVAL;

	अगर (tnr_dmd->state != CXD2880_TNRDMD_STATE_ACTIVE)
		वापस -EINVAL;

	अगर (tnr_dmd->sys != CXD2880_DTV_SYS_DVBT2)
		वापस -EINVAL;

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x0b);
	अगर (ret)
		वापस ret;

	ret = tnr_dmd->io->पढ़ो_regs(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x10, &data, माप(data));
	अगर (ret)
		वापस ret;

	*sync_stat = data & 0x07;
	*ts_lock_stat = ((data & 0x20) ? 1 : 0);
	*unlock_detected = ((data & 0x10) ? 1 : 0);

	अगर (*sync_stat == 0x07)
		वापस -EAGAIN;

	वापस 0;
पूर्ण

पूर्णांक cxd2880_tnrdmd_dvbt2_mon_sync_stat_sub(काष्ठा cxd2880_tnrdmd
					   *tnr_dmd,
					   u8 *sync_stat,
					   u8 *unlock_detected)
अणु
	u8 ts_lock_stat = 0;

	अगर (!tnr_dmd || !sync_stat || !unlock_detected)
		वापस -EINVAL;

	अगर (tnr_dmd->भागer_mode != CXD2880_TNRDMD_DIVERMODE_MAIN)
		वापस -EINVAL;

	वापस cxd2880_tnrdmd_dvbt2_mon_sync_stat(tnr_dmd->भागer_sub,
						  sync_stat,
						  &ts_lock_stat,
						  unlock_detected);
पूर्ण

पूर्णांक cxd2880_tnrdmd_dvbt2_mon_carrier_offset(काष्ठा cxd2880_tnrdmd
					    *tnr_dmd, पूर्णांक *offset)
अणु
	u8 data[4];
	u32 ctl_val = 0;
	u8 sync_state = 0;
	u8 ts_lock = 0;
	u8 unlock_detected = 0;
	पूर्णांक ret;

	अगर (!tnr_dmd || !offset)
		वापस -EINVAL;

	अगर (tnr_dmd->state != CXD2880_TNRDMD_STATE_ACTIVE)
		वापस -EINVAL;

	अगर (tnr_dmd->sys != CXD2880_DTV_SYS_DVBT2)
		वापस -EINVAL;

	ret = slvt_मुक्तze_reg(tnr_dmd);
	अगर (ret)
		वापस ret;

	ret =
	    cxd2880_tnrdmd_dvbt2_mon_sync_stat(tnr_dmd, &sync_state,
					       &ts_lock,
					       &unlock_detected);
	अगर (ret) अणु
		slvt_unमुक्तze_reg(tnr_dmd);
		वापस ret;
	पूर्ण

	अगर (sync_state != 6) अणु
		slvt_unमुक्तze_reg(tnr_dmd);
		वापस -EAGAIN;
	पूर्ण

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x0b);
	अगर (ret) अणु
		slvt_unमुक्तze_reg(tnr_dmd);
		वापस ret;
	पूर्ण

	ret = tnr_dmd->io->पढ़ो_regs(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x30, data, माप(data));
	अगर (ret) अणु
		slvt_unमुक्तze_reg(tnr_dmd);
		वापस ret;
	पूर्ण

	slvt_unमुक्तze_reg(tnr_dmd);

	ctl_val =
	    ((data[0] & 0x0f) << 24) | (data[1] << 16) | (data[2] << 8)
	    | (data[3]);
	*offset = cxd2880_convert2s_complement(ctl_val, 28);

	चयन (tnr_dmd->bandwidth) अणु
	हाल CXD2880_DTV_BW_1_7_MHZ:
		*offset = -1 * ((*offset) / 582);
		अवरोध;
	हाल CXD2880_DTV_BW_5_MHZ:
	हाल CXD2880_DTV_BW_6_MHZ:
	हाल CXD2880_DTV_BW_7_MHZ:
	हाल CXD2880_DTV_BW_8_MHZ:
		*offset = -1 * ((*offset) * tnr_dmd->bandwidth / 940);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक cxd2880_tnrdmd_dvbt2_mon_carrier_offset_sub(काष्ठा
						cxd2880_tnrdmd
						*tnr_dmd,
						पूर्णांक *offset)
अणु
	अगर (!tnr_dmd || !offset)
		वापस -EINVAL;

	अगर (tnr_dmd->भागer_mode != CXD2880_TNRDMD_DIVERMODE_MAIN)
		वापस -EINVAL;

	वापस cxd2880_tnrdmd_dvbt2_mon_carrier_offset(tnr_dmd->भागer_sub,
						       offset);
पूर्ण

पूर्णांक cxd2880_tnrdmd_dvbt2_mon_l1_pre(काष्ठा cxd2880_tnrdmd *tnr_dmd,
				    काष्ठा cxd2880_dvbt2_l1pre
				    *l1_pre)
अणु
	u8 data[37];
	u8 sync_state = 0;
	u8 ts_lock = 0;
	u8 unlock_detected = 0;
	u8 version = 0;
	क्रमागत cxd2880_dvbt2_profile profile;
	पूर्णांक ret;

	अगर (!tnr_dmd || !l1_pre)
		वापस -EINVAL;

	अगर (tnr_dmd->भागer_mode == CXD2880_TNRDMD_DIVERMODE_SUB)
		वापस -EINVAL;

	अगर (tnr_dmd->state != CXD2880_TNRDMD_STATE_ACTIVE)
		वापस -EINVAL;

	अगर (tnr_dmd->sys != CXD2880_DTV_SYS_DVBT2)
		वापस -EINVAL;

	ret = slvt_मुक्तze_reg(tnr_dmd);
	अगर (ret)
		वापस ret;

	ret =
	    cxd2880_tnrdmd_dvbt2_mon_sync_stat(tnr_dmd, &sync_state,
					       &ts_lock,
					       &unlock_detected);
	अगर (ret) अणु
		slvt_unमुक्तze_reg(tnr_dmd);
		वापस ret;
	पूर्ण

	अगर (sync_state < 5) अणु
		अगर (tnr_dmd->भागer_mode ==
		    CXD2880_TNRDMD_DIVERMODE_MAIN) अणु
			ret =
			    cxd2880_tnrdmd_dvbt2_mon_sync_stat_sub
			    (tnr_dmd, &sync_state, &unlock_detected);
			अगर (ret) अणु
				slvt_unमुक्तze_reg(tnr_dmd);
				वापस ret;
			पूर्ण

			अगर (sync_state < 5) अणु
				slvt_unमुक्तze_reg(tnr_dmd);
				वापस -EAGAIN;
			पूर्ण
		पूर्ण अन्यथा अणु
			slvt_unमुक्तze_reg(tnr_dmd);
			वापस -EAGAIN;
		पूर्ण
	पूर्ण

	ret = cxd2880_tnrdmd_dvbt2_mon_profile(tnr_dmd, &profile);
	अगर (ret) अणु
		slvt_unमुक्तze_reg(tnr_dmd);
		वापस ret;
	पूर्ण

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x0b);
	अगर (ret) अणु
		slvt_unमुक्तze_reg(tnr_dmd);
		वापस ret;
	पूर्ण

	ret = tnr_dmd->io->पढ़ो_regs(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x61, data, माप(data));
	अगर (ret) अणु
		slvt_unमुक्तze_reg(tnr_dmd);
		वापस ret;
	पूर्ण
	slvt_unमुक्तze_reg(tnr_dmd);

	l1_pre->type = (क्रमागत cxd2880_dvbt2_l1pre_type)data[0];
	l1_pre->bw_ext = data[1] & 0x01;
	l1_pre->s1 = (क्रमागत cxd2880_dvbt2_s1)(data[2] & 0x07);
	l1_pre->s2 = data[3] & 0x0f;
	l1_pre->l1_rep = data[4] & 0x01;
	l1_pre->gi = (क्रमागत cxd2880_dvbt2_guard)(data[5] & 0x07);
	l1_pre->papr = (क्रमागत cxd2880_dvbt2_papr)(data[6] & 0x0f);
	l1_pre->mod =
	    (क्रमागत cxd2880_dvbt2_l1post_स्थिरell)(data[7] & 0x0f);
	l1_pre->cr = (क्रमागत cxd2880_dvbt2_l1post_cr)(data[8] & 0x03);
	l1_pre->fec =
	    (क्रमागत cxd2880_dvbt2_l1post_fec_type)(data[9] & 0x03);
	l1_pre->l1_post_size = (data[10] & 0x03) << 16;
	l1_pre->l1_post_size |= (data[11]) << 8;
	l1_pre->l1_post_size |= (data[12]);
	l1_pre->l1_post_info_size = (data[13] & 0x03) << 16;
	l1_pre->l1_post_info_size |= (data[14]) << 8;
	l1_pre->l1_post_info_size |= (data[15]);
	l1_pre->pp = (क्रमागत cxd2880_dvbt2_pp)(data[16] & 0x0f);
	l1_pre->tx_id_availability = data[17];
	l1_pre->cell_id = (data[18] << 8);
	l1_pre->cell_id |= (data[19]);
	l1_pre->network_id = (data[20] << 8);
	l1_pre->network_id |= (data[21]);
	l1_pre->sys_id = (data[22] << 8);
	l1_pre->sys_id |= (data[23]);
	l1_pre->num_frames = data[24];
	l1_pre->num_symbols = (data[25] & 0x0f) << 8;
	l1_pre->num_symbols |= data[26];
	l1_pre->regen = data[27] & 0x07;
	l1_pre->post_ext = data[28] & 0x01;
	l1_pre->num_rf_freqs = data[29] & 0x07;
	l1_pre->rf_idx = data[30] & 0x07;
	version = (data[31] & 0x03) << 2;
	version |= (data[32] & 0xc0) >> 6;
	l1_pre->t2_version = (क्रमागत cxd2880_dvbt2_version)version;
	l1_pre->l1_post_scrambled = (data[32] & 0x20) >> 5;
	l1_pre->t2_base_lite = (data[32] & 0x10) >> 4;
	l1_pre->crc32 = (data[33] << 24);
	l1_pre->crc32 |= (data[34] << 16);
	l1_pre->crc32 |= (data[35] << 8);
	l1_pre->crc32 |= data[36];

	अगर (profile == CXD2880_DVBT2_PROखाता_BASE) अणु
		चयन ((l1_pre->s2 >> 1)) अणु
		हाल CXD2880_DVBT2_BASE_S2_M1K_G_ANY:
			l1_pre->fft_mode = CXD2880_DVBT2_M1K;
			अवरोध;
		हाल CXD2880_DVBT2_BASE_S2_M2K_G_ANY:
			l1_pre->fft_mode = CXD2880_DVBT2_M2K;
			अवरोध;
		हाल CXD2880_DVBT2_BASE_S2_M4K_G_ANY:
			l1_pre->fft_mode = CXD2880_DVBT2_M4K;
			अवरोध;
		हाल CXD2880_DVBT2_BASE_S2_M8K_G_DVBT:
		हाल CXD2880_DVBT2_BASE_S2_M8K_G_DVBT2:
			l1_pre->fft_mode = CXD2880_DVBT2_M8K;
			अवरोध;
		हाल CXD2880_DVBT2_BASE_S2_M16K_G_ANY:
			l1_pre->fft_mode = CXD2880_DVBT2_M16K;
			अवरोध;
		हाल CXD2880_DVBT2_BASE_S2_M32K_G_DVBT:
		हाल CXD2880_DVBT2_BASE_S2_M32K_G_DVBT2:
			l1_pre->fft_mode = CXD2880_DVBT2_M32K;
			अवरोध;
		शेष:
			वापस -EAGAIN;
		पूर्ण
	पूर्ण अन्यथा अगर (profile == CXD2880_DVBT2_PROखाता_LITE) अणु
		चयन ((l1_pre->s2 >> 1)) अणु
		हाल CXD2880_DVBT2_LITE_S2_M2K_G_ANY:
			l1_pre->fft_mode = CXD2880_DVBT2_M2K;
			अवरोध;
		हाल CXD2880_DVBT2_LITE_S2_M4K_G_ANY:
			l1_pre->fft_mode = CXD2880_DVBT2_M4K;
			अवरोध;
		हाल CXD2880_DVBT2_LITE_S2_M8K_G_DVBT:
		हाल CXD2880_DVBT2_LITE_S2_M8K_G_DVBT2:
			l1_pre->fft_mode = CXD2880_DVBT2_M8K;
			अवरोध;
		हाल CXD2880_DVBT2_LITE_S2_M16K_G_DVBT:
		हाल CXD2880_DVBT2_LITE_S2_M16K_G_DVBT2:
			l1_pre->fft_mode = CXD2880_DVBT2_M16K;
			अवरोध;
		शेष:
			वापस -EAGAIN;
		पूर्ण
	पूर्ण अन्यथा अणु
		वापस -EAGAIN;
	पूर्ण

	l1_pre->mixed = l1_pre->s2 & 0x01;

	वापस ret;
पूर्ण

पूर्णांक cxd2880_tnrdmd_dvbt2_mon_version(काष्ठा cxd2880_tnrdmd
				     *tnr_dmd,
				     क्रमागत cxd2880_dvbt2_version
				     *ver)
अणु
	u8 data[2];
	u8 sync_state = 0;
	u8 ts_lock = 0;
	u8 unlock_detected = 0;
	u8 version = 0;
	पूर्णांक ret;

	अगर (!tnr_dmd || !ver)
		वापस -EINVAL;

	अगर (tnr_dmd->भागer_mode == CXD2880_TNRDMD_DIVERMODE_SUB)
		वापस -EINVAL;

	अगर (tnr_dmd->state != CXD2880_TNRDMD_STATE_ACTIVE)
		वापस -EINVAL;

	अगर (tnr_dmd->sys != CXD2880_DTV_SYS_DVBT2)
		वापस -EINVAL;

	ret = slvt_मुक्तze_reg(tnr_dmd);
	अगर (ret)
		वापस ret;

	ret =
	    cxd2880_tnrdmd_dvbt2_mon_sync_stat(tnr_dmd, &sync_state,
					       &ts_lock,
					       &unlock_detected);
	अगर (ret) अणु
		slvt_unमुक्तze_reg(tnr_dmd);
		वापस ret;
	पूर्ण

	अगर (sync_state < 5) अणु
		अगर (tnr_dmd->भागer_mode ==
		    CXD2880_TNRDMD_DIVERMODE_MAIN) अणु
			ret =
			    cxd2880_tnrdmd_dvbt2_mon_sync_stat_sub
			    (tnr_dmd, &sync_state, &unlock_detected);
			अगर (ret) अणु
				slvt_unमुक्तze_reg(tnr_dmd);
				वापस ret;
			पूर्ण

			अगर (sync_state < 5) अणु
				slvt_unमुक्तze_reg(tnr_dmd);
				वापस -EAGAIN;
			पूर्ण
		पूर्ण अन्यथा अणु
			slvt_unमुक्तze_reg(tnr_dmd);
			वापस -EAGAIN;
		पूर्ण
	पूर्ण

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x0b);
	अगर (ret) अणु
		slvt_unमुक्तze_reg(tnr_dmd);
		वापस ret;
	पूर्ण

	ret = tnr_dmd->io->पढ़ो_regs(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x80, data, माप(data));
	अगर (ret) अणु
		slvt_unमुक्तze_reg(tnr_dmd);
		वापस ret;
	पूर्ण

	slvt_unमुक्तze_reg(tnr_dmd);

	version = ((data[0] & 0x03) << 2);
	version |= ((data[1] & 0xc0) >> 6);
	*ver = (क्रमागत cxd2880_dvbt2_version)version;

	वापस ret;
पूर्ण

पूर्णांक cxd2880_tnrdmd_dvbt2_mon_ofdm(काष्ठा cxd2880_tnrdmd *tnr_dmd,
				  काष्ठा cxd2880_dvbt2_ofdm *ofdm)
अणु
	u8 data[5];
	u8 sync_state = 0;
	u8 ts_lock = 0;
	u8 unlock_detected = 0;
	पूर्णांक ret;

	अगर (!tnr_dmd || !ofdm)
		वापस -EINVAL;

	अगर (tnr_dmd->state != CXD2880_TNRDMD_STATE_ACTIVE)
		वापस -EINVAL;

	अगर (tnr_dmd->sys != CXD2880_DTV_SYS_DVBT2)
		वापस -EINVAL;

	ret = slvt_मुक्तze_reg(tnr_dmd);
	अगर (ret)
		वापस ret;

	ret =
	    cxd2880_tnrdmd_dvbt2_mon_sync_stat(tnr_dmd, &sync_state,
					       &ts_lock,
					       &unlock_detected);
	अगर (ret) अणु
		slvt_unमुक्तze_reg(tnr_dmd);
		वापस ret;
	पूर्ण

	अगर (sync_state != 6) अणु
		slvt_unमुक्तze_reg(tnr_dmd);

		ret = -EAGAIN;

		अगर (tnr_dmd->भागer_mode ==
		    CXD2880_TNRDMD_DIVERMODE_MAIN)
			ret =
			    cxd2880_tnrdmd_dvbt2_mon_ofdm(tnr_dmd->भागer_sub,
							  ofdm);

		वापस ret;
	पूर्ण

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x0b);
	अगर (ret) अणु
		slvt_unमुक्तze_reg(tnr_dmd);
		वापस ret;
	पूर्ण

	ret = tnr_dmd->io->पढ़ो_regs(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x1d, data, माप(data));
	अगर (ret) अणु
		slvt_unमुक्तze_reg(tnr_dmd);
		वापस ret;
	पूर्ण

	slvt_unमुक्तze_reg(tnr_dmd);

	ofdm->mixed = ((data[0] & 0x20) ? 1 : 0);
	ofdm->is_miso = ((data[0] & 0x10) >> 4);
	ofdm->mode = (क्रमागत cxd2880_dvbt2_mode)(data[0] & 0x07);
	ofdm->gi = (क्रमागत cxd2880_dvbt2_guard)((data[1] & 0x70) >> 4);
	ofdm->pp = (क्रमागत cxd2880_dvbt2_pp)(data[1] & 0x07);
	ofdm->bw_ext = (data[2] & 0x10) >> 4;
	ofdm->papr = (क्रमागत cxd2880_dvbt2_papr)(data[2] & 0x0f);
	ofdm->num_symbols = (data[3] << 8) | data[4];

	वापस 0;
पूर्ण

पूर्णांक cxd2880_tnrdmd_dvbt2_mon_data_plps(काष्ठा cxd2880_tnrdmd
				       *tnr_dmd, u8 *plp_ids,
				       u8 *num_plps)
अणु
	u8 l1_post_ok = 0;
	पूर्णांक ret;

	अगर (!tnr_dmd || !num_plps)
		वापस -EINVAL;

	अगर (tnr_dmd->भागer_mode == CXD2880_TNRDMD_DIVERMODE_SUB)
		वापस -EINVAL;

	अगर (tnr_dmd->state != CXD2880_TNRDMD_STATE_ACTIVE)
		वापस -EINVAL;

	अगर (tnr_dmd->sys != CXD2880_DTV_SYS_DVBT2)
		वापस -EINVAL;

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x0b);
	अगर (ret)
		वापस ret;

	ret = slvt_मुक्तze_reg(tnr_dmd);
	अगर (ret)
		वापस ret;

	ret = tnr_dmd->io->पढ़ो_regs(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x86, &l1_post_ok, 1);
	अगर (ret) अणु
		slvt_unमुक्तze_reg(tnr_dmd);
		वापस ret;
	पूर्ण

	अगर (!(l1_post_ok & 0x01)) अणु
		slvt_unमुक्तze_reg(tnr_dmd);
		वापस -EAGAIN;
	पूर्ण

	ret = tnr_dmd->io->पढ़ो_regs(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0xc1, num_plps, 1);
	अगर (ret) अणु
		slvt_unमुक्तze_reg(tnr_dmd);
		वापस ret;
	पूर्ण

	अगर (*num_plps == 0) अणु
		slvt_unमुक्तze_reg(tnr_dmd);
		वापस -EINVAL;
	पूर्ण

	अगर (!plp_ids) अणु
		slvt_unमुक्तze_reg(tnr_dmd);
		वापस 0;
	पूर्ण

	ret = tnr_dmd->io->पढ़ो_regs(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0xc2,
				     plp_ids,
				     ((*num_plps > 62) ?
				     62 : *num_plps));
	अगर (ret) अणु
		slvt_unमुक्तze_reg(tnr_dmd);
		वापस ret;
	पूर्ण

	अगर (*num_plps > 62) अणु
		ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
					     CXD2880_IO_TGT_DMD,
					     0x00, 0x0c);
		अगर (ret) अणु
			slvt_unमुक्तze_reg(tnr_dmd);
			वापस ret;
		पूर्ण

		ret = tnr_dmd->io->पढ़ो_regs(tnr_dmd->io,
					     CXD2880_IO_TGT_DMD,
					     0x10, plp_ids + 62,
					     *num_plps - 62);
		अगर (ret) अणु
			slvt_unमुक्तze_reg(tnr_dmd);
			वापस ret;
		पूर्ण
	पूर्ण

	slvt_unमुक्तze_reg(tnr_dmd);

	वापस 0;
पूर्ण

पूर्णांक cxd2880_tnrdmd_dvbt2_mon_active_plp(काष्ठा cxd2880_tnrdmd
					*tnr_dmd,
					क्रमागत
					cxd2880_dvbt2_plp_btype
					type,
					काष्ठा cxd2880_dvbt2_plp
					*plp_info)
अणु
	u8 data[20];
	u8 addr = 0;
	u8 index = 0;
	u8 l1_post_ok = 0;
	पूर्णांक ret;

	अगर (!tnr_dmd || !plp_info)
		वापस -EINVAL;

	अगर (tnr_dmd->भागer_mode == CXD2880_TNRDMD_DIVERMODE_SUB)
		वापस -EINVAL;

	अगर (tnr_dmd->state != CXD2880_TNRDMD_STATE_ACTIVE)
		वापस -EINVAL;

	अगर (tnr_dmd->sys != CXD2880_DTV_SYS_DVBT2)
		वापस -EINVAL;

	ret = slvt_मुक्तze_reg(tnr_dmd);
	अगर (ret)
		वापस ret;

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x0b);
	अगर (ret) अणु
		slvt_unमुक्तze_reg(tnr_dmd);
		वापस ret;
	पूर्ण

	ret = tnr_dmd->io->पढ़ो_regs(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x86, &l1_post_ok, 1);
	अगर (ret) अणु
		slvt_unमुक्तze_reg(tnr_dmd);
		वापस ret;
	पूर्ण

	अगर (!l1_post_ok) अणु
		slvt_unमुक्तze_reg(tnr_dmd);
		वापस -EAGAIN;
	पूर्ण

	अगर (type == CXD2880_DVBT2_PLP_COMMON)
		addr = 0xa9;
	अन्यथा
		addr = 0x96;

	ret = tnr_dmd->io->पढ़ो_regs(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     addr, data, माप(data));
	अगर (ret) अणु
		slvt_unमुक्तze_reg(tnr_dmd);
		वापस ret;
	पूर्ण

	slvt_unमुक्तze_reg(tnr_dmd);

	अगर (type == CXD2880_DVBT2_PLP_COMMON && !data[13])
		वापस -EAGAIN;

	plp_info->id = data[index++];
	plp_info->type =
	    (क्रमागत cxd2880_dvbt2_plp_type)(data[index++] & 0x07);
	plp_info->payload =
	    (क्रमागत cxd2880_dvbt2_plp_payload)(data[index++] & 0x1f);
	plp_info->ff = data[index++] & 0x01;
	plp_info->first_rf_idx = data[index++] & 0x07;
	plp_info->first_frm_idx = data[index++];
	plp_info->group_id = data[index++];
	plp_info->plp_cr =
	    (क्रमागत cxd2880_dvbt2_plp_code_rate)(data[index++] & 0x07);
	plp_info->स्थिरell =
	    (क्रमागत cxd2880_dvbt2_plp_स्थिरell)(data[index++] & 0x07);
	plp_info->rot = data[index++] & 0x01;
	plp_info->fec =
	    (क्रमागत cxd2880_dvbt2_plp_fec)(data[index++] & 0x03);
	plp_info->num_blocks_max = (data[index++] & 0x03) << 8;
	plp_info->num_blocks_max |= data[index++];
	plp_info->frm_पूर्णांक = data[index++];
	plp_info->til_len = data[index++];
	plp_info->til_type = data[index++] & 0x01;

	plp_info->in_band_a_flag = data[index++] & 0x01;
	plp_info->rsvd = data[index++] << 8;
	plp_info->rsvd |= data[index++];

	plp_info->in_band_b_flag =
	    (plp_info->rsvd & 0x8000) >> 15;
	plp_info->plp_mode =
	    (क्रमागत cxd2880_dvbt2_plp_mode)((plp_info->rsvd & 0x000c) >> 2);
	plp_info->अटल_flag = (plp_info->rsvd & 0x0002) >> 1;
	plp_info->अटल_padding_flag = plp_info->rsvd & 0x0001;
	plp_info->rsvd = (plp_info->rsvd & 0x7ff0) >> 4;

	वापस 0;
पूर्ण

पूर्णांक cxd2880_tnrdmd_dvbt2_mon_data_plp_error(काष्ठा cxd2880_tnrdmd
					    *tnr_dmd,
					    u8 *plp_error)
अणु
	u8 data;
	पूर्णांक ret;

	अगर (!tnr_dmd || !plp_error)
		वापस -EINVAL;

	अगर (tnr_dmd->भागer_mode == CXD2880_TNRDMD_DIVERMODE_SUB)
		वापस -EINVAL;

	अगर (tnr_dmd->state != CXD2880_TNRDMD_STATE_ACTIVE)
		वापस -EINVAL;

	अगर (tnr_dmd->sys != CXD2880_DTV_SYS_DVBT2)
		वापस -EINVAL;

	ret = slvt_मुक्तze_reg(tnr_dmd);
	अगर (ret)
		वापस ret;

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x0b);
	अगर (ret) अणु
		slvt_unमुक्तze_reg(tnr_dmd);
		वापस ret;
	पूर्ण

	ret = tnr_dmd->io->पढ़ो_regs(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x86, &data, 1);
	अगर (ret) अणु
		slvt_unमुक्तze_reg(tnr_dmd);
		वापस ret;
	पूर्ण

	अगर ((data & 0x01) == 0x00) अणु
		slvt_unमुक्तze_reg(tnr_dmd);
		वापस -EAGAIN;
	पूर्ण

	ret = tnr_dmd->io->पढ़ो_regs(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0xc0, &data, 1);
	अगर (ret) अणु
		slvt_unमुक्तze_reg(tnr_dmd);
		वापस ret;
	पूर्ण

	slvt_unमुक्तze_reg(tnr_dmd);

	*plp_error = data & 0x01;

	वापस 0;
पूर्ण

पूर्णांक cxd2880_tnrdmd_dvbt2_mon_l1_change(काष्ठा cxd2880_tnrdmd
				       *tnr_dmd, u8 *l1_change)
अणु
	u8 data;
	u8 sync_state = 0;
	u8 ts_lock = 0;
	u8 unlock_detected = 0;
	पूर्णांक ret;

	अगर (!tnr_dmd || !l1_change)
		वापस -EINVAL;

	अगर (tnr_dmd->भागer_mode == CXD2880_TNRDMD_DIVERMODE_SUB)
		वापस -EINVAL;

	अगर (tnr_dmd->state != CXD2880_TNRDMD_STATE_ACTIVE)
		वापस -EINVAL;

	अगर (tnr_dmd->sys != CXD2880_DTV_SYS_DVBT2)
		वापस -EINVAL;

	ret = slvt_मुक्तze_reg(tnr_dmd);
	अगर (ret)
		वापस ret;

	ret =
	    cxd2880_tnrdmd_dvbt2_mon_sync_stat(tnr_dmd, &sync_state,
					       &ts_lock,
					       &unlock_detected);
	अगर (ret) अणु
		slvt_unमुक्तze_reg(tnr_dmd);
		वापस ret;
	पूर्ण

	अगर (sync_state < 5) अणु
		अगर (tnr_dmd->भागer_mode ==
		    CXD2880_TNRDMD_DIVERMODE_MAIN) अणु
			ret =
			    cxd2880_tnrdmd_dvbt2_mon_sync_stat_sub
			    (tnr_dmd, &sync_state, &unlock_detected);
			अगर (ret) अणु
				slvt_unमुक्तze_reg(tnr_dmd);
				वापस ret;
			पूर्ण

			अगर (sync_state < 5) अणु
				slvt_unमुक्तze_reg(tnr_dmd);
				वापस -EAGAIN;
			पूर्ण
		पूर्ण अन्यथा अणु
			slvt_unमुक्तze_reg(tnr_dmd);
			वापस -EAGAIN;
		पूर्ण
	पूर्ण

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x0b);
	अगर (ret) अणु
		slvt_unमुक्तze_reg(tnr_dmd);
		वापस ret;
	पूर्ण

	ret = tnr_dmd->io->पढ़ो_regs(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x5f, &data, माप(data));
	अगर (ret) अणु
		slvt_unमुक्तze_reg(tnr_dmd);
		वापस ret;
	पूर्ण

	*l1_change = data & 0x01;
	अगर (*l1_change) अणु
		ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
					     CXD2880_IO_TGT_DMD,
					     0x00, 0x22);
		अगर (ret) अणु
			slvt_unमुक्तze_reg(tnr_dmd);
			वापस ret;
		पूर्ण

		ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
					     CXD2880_IO_TGT_DMD,
					     0x16, 0x01);
		अगर (ret) अणु
			slvt_unमुक्तze_reg(tnr_dmd);
			वापस ret;
		पूर्ण
	पूर्ण
	slvt_unमुक्तze_reg(tnr_dmd);

	वापस 0;
पूर्ण

पूर्णांक cxd2880_tnrdmd_dvbt2_mon_l1_post(काष्ठा cxd2880_tnrdmd
				     *tnr_dmd,
				     काष्ठा cxd2880_dvbt2_l1post
				     *l1_post)
अणु
	u8 data[16];
	पूर्णांक ret;

	अगर (!tnr_dmd || !l1_post)
		वापस -EINVAL;

	अगर (tnr_dmd->भागer_mode == CXD2880_TNRDMD_DIVERMODE_SUB)
		वापस -EINVAL;

	अगर (tnr_dmd->state != CXD2880_TNRDMD_STATE_ACTIVE)
		वापस -EINVAL;

	अगर (tnr_dmd->sys != CXD2880_DTV_SYS_DVBT2)
		वापस -EINVAL;

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x0b);
	अगर (ret)
		वापस ret;

	ret = tnr_dmd->io->पढ़ो_regs(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x86, data, माप(data));
	अगर (ret)
		वापस ret;

	अगर (!(data[0] & 0x01))
		वापस -EAGAIN;

	l1_post->sub_slices_per_frame = (data[1] & 0x7f) << 8;
	l1_post->sub_slices_per_frame |= data[2];
	l1_post->num_plps = data[3];
	l1_post->num_aux = data[4] & 0x0f;
	l1_post->aux_cfg_rfu = data[5];
	l1_post->rf_idx = data[6] & 0x07;
	l1_post->freq = data[7] << 24;
	l1_post->freq |= data[8] << 16;
	l1_post->freq |= data[9] << 8;
	l1_post->freq |= data[10];
	l1_post->fef_type = data[11] & 0x0f;
	l1_post->fef_length = data[12] << 16;
	l1_post->fef_length |= data[13] << 8;
	l1_post->fef_length |= data[14];
	l1_post->fef_पूर्णांकvl = data[15];

	वापस 0;
पूर्ण

पूर्णांक cxd2880_tnrdmd_dvbt2_mon_bbheader(काष्ठा cxd2880_tnrdmd
				      *tnr_dmd,
				      क्रमागत cxd2880_dvbt2_plp_btype
				      type,
				      काष्ठा cxd2880_dvbt2_bbheader
				      *bbheader)
अणु
	u8 sync_state = 0;
	u8 ts_lock = 0;
	u8 unlock_detected = 0;
	u8 data[14];
	u8 addr = 0;
	पूर्णांक ret;

	अगर (!tnr_dmd || !bbheader)
		वापस -EINVAL;

	अगर (tnr_dmd->भागer_mode == CXD2880_TNRDMD_DIVERMODE_SUB)
		वापस -EINVAL;

	अगर (tnr_dmd->state != CXD2880_TNRDMD_STATE_ACTIVE)
		वापस -EINVAL;

	अगर (tnr_dmd->sys != CXD2880_DTV_SYS_DVBT2)
		वापस -EINVAL;

	ret = slvt_मुक्तze_reg(tnr_dmd);
	अगर (ret)
		वापस ret;

	ret =
	    cxd2880_tnrdmd_dvbt2_mon_sync_stat(tnr_dmd, &sync_state,
						       &ts_lock,
						       &unlock_detected);
	अगर (ret) अणु
		slvt_unमुक्तze_reg(tnr_dmd);
		वापस ret;
	पूर्ण

	अगर (!ts_lock) अणु
		slvt_unमुक्तze_reg(tnr_dmd);
		वापस -EAGAIN;
	पूर्ण

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x0b);
	अगर (ret) अणु
		slvt_unमुक्तze_reg(tnr_dmd);
		वापस ret;
	पूर्ण

	अगर (type == CXD2880_DVBT2_PLP_COMMON) अणु
		u8 l1_post_ok;
		u8 data;

		ret = tnr_dmd->io->पढ़ो_regs(tnr_dmd->io,
					     CXD2880_IO_TGT_DMD,
					     0x86, &l1_post_ok, 1);
		अगर (ret) अणु
			slvt_unमुक्तze_reg(tnr_dmd);
			वापस ret;
		पूर्ण

		अगर (!(l1_post_ok & 0x01)) अणु
			slvt_unमुक्तze_reg(tnr_dmd);
			वापस -EAGAIN;
		पूर्ण

		ret = tnr_dmd->io->पढ़ो_regs(tnr_dmd->io,
					     CXD2880_IO_TGT_DMD,
					     0xb6, &data, 1);
		अगर (ret) अणु
			slvt_unमुक्तze_reg(tnr_dmd);
			वापस ret;
		पूर्ण

		अगर (data == 0) अणु
			slvt_unमुक्तze_reg(tnr_dmd);
			वापस -EAGAIN;
		पूर्ण
	पूर्ण

	अगर (type == CXD2880_DVBT2_PLP_COMMON)
		addr = 0x51;
	अन्यथा
		addr = 0x42;

	ret = tnr_dmd->io->पढ़ो_regs(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     addr, data, माप(data));
	अगर (ret) अणु
		slvt_unमुक्तze_reg(tnr_dmd);
		वापस ret;
	पूर्ण

	slvt_unमुक्तze_reg(tnr_dmd);

	bbheader->stream_input =
	    (क्रमागत cxd2880_dvbt2_stream)((data[0] >> 6) & 0x03);
	bbheader->is_single_input_stream = (data[0] >> 5) & 0x01;
	bbheader->is_स्थिरant_coding_modulation =
	    (data[0] >> 4) & 0x01;
	bbheader->issy_indicator = (data[0] >> 3) & 0x01;
	bbheader->null_packet_deletion = (data[0] >> 2) & 0x01;
	bbheader->ext = data[0] & 0x03;

	bbheader->input_stream_identअगरier = data[1];
	bbheader->plp_mode =
	    (data[3] & 0x01) ? CXD2880_DVBT2_PLP_MODE_HEM :
	    CXD2880_DVBT2_PLP_MODE_NM;
	bbheader->data_field_length = (data[4] << 8) | data[5];

	अगर (bbheader->plp_mode == CXD2880_DVBT2_PLP_MODE_NM) अणु
		bbheader->user_packet_length =
		    (data[6] << 8) | data[7];
		bbheader->sync_byte = data[8];
		bbheader->issy = 0;
	पूर्ण अन्यथा अणु
		bbheader->user_packet_length = 0;
		bbheader->sync_byte = 0;
		bbheader->issy =
		    (data[11] << 16) | (data[12] << 8) | data[13];
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक cxd2880_tnrdmd_dvbt2_mon_in_bandb_ts_rate(काष्ठा cxd2880_tnrdmd
					      *tnr_dmd,
					      क्रमागत
					      cxd2880_dvbt2_plp_btype
					      type,
					      u32 *ts_rate_bps)
अणु
	u8 sync_state = 0;
	u8 ts_lock = 0;
	u8 unlock_detected = 0;
	u8 l1_post_ok = 0;
	u8 data[4];
	u8 addr = 0;

	पूर्णांक ret;

	अगर (!tnr_dmd || !ts_rate_bps)
		वापस -EINVAL;

	अगर (tnr_dmd->भागer_mode == CXD2880_TNRDMD_DIVERMODE_SUB)
		वापस -EINVAL;

	अगर (tnr_dmd->state != CXD2880_TNRDMD_STATE_ACTIVE)
		वापस -EINVAL;

	अगर (tnr_dmd->sys != CXD2880_DTV_SYS_DVBT2)
		वापस -EINVAL;

	ret = slvt_मुक्तze_reg(tnr_dmd);
	अगर (ret)
		वापस ret;

	ret =
	    cxd2880_tnrdmd_dvbt2_mon_sync_stat(tnr_dmd, &sync_state,
					       &ts_lock,
					       &unlock_detected);
	अगर (ret) अणु
		slvt_unमुक्तze_reg(tnr_dmd);
		वापस ret;
	पूर्ण

	अगर (!ts_lock) अणु
		slvt_unमुक्तze_reg(tnr_dmd);
		वापस -EAGAIN;
	पूर्ण

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x0b);
	अगर (ret) अणु
		slvt_unमुक्तze_reg(tnr_dmd);
		वापस ret;
	पूर्ण

	ret = tnr_dmd->io->पढ़ो_regs(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x86, &l1_post_ok, 1);
	अगर (ret) अणु
		slvt_unमुक्तze_reg(tnr_dmd);
		वापस ret;
	पूर्ण

	अगर (!(l1_post_ok & 0x01)) अणु
		slvt_unमुक्तze_reg(tnr_dmd);
		वापस -EAGAIN;
	पूर्ण

	अगर (type == CXD2880_DVBT2_PLP_COMMON)
		addr = 0xba;
	अन्यथा
		addr = 0xa7;

	ret = tnr_dmd->io->पढ़ो_regs(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     addr, &data[0], 1);
	अगर (ret) अणु
		slvt_unमुक्तze_reg(tnr_dmd);
		वापस ret;
	पूर्ण

	अगर ((data[0] & 0x80) == 0x00) अणु
		slvt_unमुक्तze_reg(tnr_dmd);
		वापस -EAGAIN;
	पूर्ण

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x25);
	अगर (ret) अणु
		slvt_unमुक्तze_reg(tnr_dmd);
		वापस ret;
	पूर्ण

	अगर (type == CXD2880_DVBT2_PLP_COMMON)
		addr = 0xa6;
	अन्यथा
		addr = 0xaa;

	ret = tnr_dmd->io->पढ़ो_regs(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     addr, &data[0], 4);
	अगर (ret) अणु
		slvt_unमुक्तze_reg(tnr_dmd);
		वापस ret;
	पूर्ण

	*ts_rate_bps = ((data[0] & 0x07) << 24) | (data[1] << 16) |
		       (data[2] << 8) | data[3];

	वापस 0;
पूर्ण

पूर्णांक cxd2880_tnrdmd_dvbt2_mon_spectrum_sense(काष्ठा cxd2880_tnrdmd
					    *tnr_dmd,
					    क्रमागत
					    cxd2880_tnrdmd_spectrum_sense
					    *sense)
अणु
	u8 sync_state = 0;
	u8 ts_lock = 0;
	u8 early_unlock = 0;
	u8 data = 0;
	पूर्णांक ret;

	अगर (!tnr_dmd || !sense)
		वापस -EINVAL;

	अगर (tnr_dmd->state != CXD2880_TNRDMD_STATE_ACTIVE)
		वापस -EINVAL;

	अगर (tnr_dmd->sys != CXD2880_DTV_SYS_DVBT2)
		वापस -EINVAL;

	ret = slvt_मुक्तze_reg(tnr_dmd);
	अगर (ret)
		वापस ret;

	ret =
	    cxd2880_tnrdmd_dvbt2_mon_sync_stat(tnr_dmd, &sync_state, &ts_lock,
					       &early_unlock);
	अगर (ret) अणु
		slvt_unमुक्तze_reg(tnr_dmd);
		वापस ret;
	पूर्ण

	अगर (sync_state != 6) अणु
		slvt_unमुक्तze_reg(tnr_dmd);

		ret = -EAGAIN;

		अगर (tnr_dmd->भागer_mode == CXD2880_TNRDMD_DIVERMODE_MAIN)
			ret =
			    cxd2880_tnrdmd_dvbt2_mon_spectrum_sense(tnr_dmd->भागer_sub,
								    sense);

		वापस ret;
	पूर्ण

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x0b);
	अगर (ret) अणु
		slvt_unमुक्तze_reg(tnr_dmd);
		वापस ret;
	पूर्ण

	ret = tnr_dmd->io->पढ़ो_regs(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x2f, &data, माप(data));
	अगर (ret) अणु
		slvt_unमुक्तze_reg(tnr_dmd);
		वापस ret;
	पूर्ण

	slvt_unमुक्तze_reg(tnr_dmd);

	*sense =
	    (data & 0x01) ? CXD2880_TNRDMD_SPECTRUM_INV :
	    CXD2880_TNRDMD_SPECTRUM_NORMAL;

	वापस 0;
पूर्ण

अटल पूर्णांक dvbt2_पढ़ो_snr_reg(काष्ठा cxd2880_tnrdmd *tnr_dmd,
			      u16 *reg_value)
अणु
	u8 sync_state = 0;
	u8 ts_lock = 0;
	u8 unlock_detected = 0;
	u8 data[2];
	पूर्णांक ret;

	अगर (!tnr_dmd || !reg_value)
		वापस -EINVAL;

	ret = slvt_मुक्तze_reg(tnr_dmd);
	अगर (ret)
		वापस ret;

	ret =
	    cxd2880_tnrdmd_dvbt2_mon_sync_stat(tnr_dmd, &sync_state,
					       &ts_lock,
					       &unlock_detected);
	अगर (ret) अणु
		slvt_unमुक्तze_reg(tnr_dmd);
		वापस ret;
	पूर्ण

	अगर (sync_state != 6) अणु
		slvt_unमुक्तze_reg(tnr_dmd);
		वापस -EAGAIN;
	पूर्ण

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x0b);
	अगर (ret) अणु
		slvt_unमुक्तze_reg(tnr_dmd);
		वापस ret;
	पूर्ण

	ret = tnr_dmd->io->पढ़ो_regs(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x13, data, माप(data));
	अगर (ret) अणु
		slvt_unमुक्तze_reg(tnr_dmd);
		वापस ret;
	पूर्ण

	slvt_unमुक्तze_reg(tnr_dmd);

	*reg_value = (data[0] << 8) | data[1];

	वापस ret;
पूर्ण

अटल पूर्णांक dvbt2_calc_snr(काष्ठा cxd2880_tnrdmd *tnr_dmd,
			  u32 reg_value, पूर्णांक *snr)
अणु
	अगर (!tnr_dmd || !snr)
		वापस -EINVAL;

	अगर (reg_value == 0)
		वापस -EAGAIN;

	अगर (reg_value > 10876)
		reg_value = 10876;

	*snr = पूर्णांकlog10(reg_value) - पूर्णांकlog10(12600 - reg_value);
	*snr = (*snr + 839) / 1678 + 32000;

	वापस 0;
पूर्ण

पूर्णांक cxd2880_tnrdmd_dvbt2_mon_snr(काष्ठा cxd2880_tnrdmd *tnr_dmd,
				 पूर्णांक *snr)
अणु
	u16 reg_value = 0;
	पूर्णांक ret;

	अगर (!tnr_dmd || !snr)
		वापस -EINVAL;

	*snr = -1000 * 1000;

	अगर (tnr_dmd->भागer_mode == CXD2880_TNRDMD_DIVERMODE_SUB)
		वापस -EINVAL;

	अगर (tnr_dmd->state != CXD2880_TNRDMD_STATE_ACTIVE)
		वापस -EINVAL;

	अगर (tnr_dmd->sys != CXD2880_DTV_SYS_DVBT2)
		वापस -EINVAL;

	अगर (tnr_dmd->भागer_mode == CXD2880_TNRDMD_DIVERMODE_SINGLE) अणु
		ret = dvbt2_पढ़ो_snr_reg(tnr_dmd, &reg_value);
		अगर (ret)
			वापस ret;

		ret = dvbt2_calc_snr(tnr_dmd, reg_value, snr);
	पूर्ण अन्यथा अणु
		पूर्णांक snr_मुख्य = 0;
		पूर्णांक snr_sub = 0;

		ret =
		    cxd2880_tnrdmd_dvbt2_mon_snr_भागer(tnr_dmd, snr, &snr_मुख्य,
						       &snr_sub);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक cxd2880_tnrdmd_dvbt2_mon_snr_भागer(काष्ठा cxd2880_tnrdmd
				       *tnr_dmd, पूर्णांक *snr,
				       पूर्णांक *snr_मुख्य, पूर्णांक *snr_sub)
अणु
	u16 reg_value = 0;
	u32 reg_value_sum = 0;
	पूर्णांक ret;

	अगर (!tnr_dmd || !snr || !snr_मुख्य || !snr_sub)
		वापस -EINVAL;

	*snr = -1000 * 1000;
	*snr_मुख्य = -1000 * 1000;
	*snr_sub = -1000 * 1000;

	अगर (tnr_dmd->भागer_mode != CXD2880_TNRDMD_DIVERMODE_MAIN)
		वापस -EINVAL;

	अगर (tnr_dmd->state != CXD2880_TNRDMD_STATE_ACTIVE)
		वापस -EINVAL;

	अगर (tnr_dmd->sys != CXD2880_DTV_SYS_DVBT2)
		वापस -EINVAL;

	ret = dvbt2_पढ़ो_snr_reg(tnr_dmd, &reg_value);
	अगर (!ret) अणु
		ret = dvbt2_calc_snr(tnr_dmd, reg_value, snr_मुख्य);
		अगर (ret)
			reg_value = 0;
	पूर्ण अन्यथा अगर (ret == -EAGAIN) अणु
		reg_value = 0;
	पूर्ण अन्यथा अणु
		वापस ret;
	पूर्ण

	reg_value_sum += reg_value;

	ret = dvbt2_पढ़ो_snr_reg(tnr_dmd->भागer_sub, &reg_value);
	अगर (!ret) अणु
		ret = dvbt2_calc_snr(tnr_dmd->भागer_sub, reg_value, snr_sub);
		अगर (ret)
			reg_value = 0;
	पूर्ण अन्यथा अगर (ret == -EAGAIN) अणु
		reg_value = 0;
	पूर्ण अन्यथा अणु
		वापस ret;
	पूर्ण

	reg_value_sum += reg_value;

	वापस dvbt2_calc_snr(tnr_dmd, reg_value_sum, snr);
पूर्ण

पूर्णांक cxd2880_tnrdmd_dvbt2_mon_packet_error_number(काष्ठा
						 cxd2880_tnrdmd
						 *tnr_dmd,
						 u32 *pen)
अणु
	पूर्णांक ret;
	u8 data[3];

	अगर (!tnr_dmd || !pen)
		वापस -EINVAL;

	अगर (tnr_dmd->भागer_mode == CXD2880_TNRDMD_DIVERMODE_SUB)
		वापस -EINVAL;

	अगर (tnr_dmd->state != CXD2880_TNRDMD_STATE_ACTIVE)
		वापस -EINVAL;

	अगर (tnr_dmd->sys != CXD2880_DTV_SYS_DVBT2)
		वापस -EINVAL;

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x0b);
	अगर (ret)
		वापस ret;

	ret = tnr_dmd->io->पढ़ो_regs(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x39, data, माप(data));
	अगर (ret)
		वापस ret;

	अगर (!(data[0] & 0x01))
		वापस -EAGAIN;

	*pen = ((data[1] << 8) | data[2]);

	वापस ret;
पूर्ण

पूर्णांक cxd2880_tnrdmd_dvbt2_mon_sampling_offset(काष्ठा cxd2880_tnrdmd
					     *tnr_dmd, पूर्णांक *ppm)
अणु
	u8 ctl_val_reg[5];
	u8 nominal_rate_reg[5];
	u32 trl_ctl_val = 0;
	u32 trcg_nominal_rate = 0;
	पूर्णांक num;
	पूर्णांक den;
	पूर्णांक ret;
	u8 sync_state = 0;
	u8 ts_lock = 0;
	u8 unlock_detected = 0;
	s8 dअगरf_upper = 0;

	अगर (!tnr_dmd || !ppm)
		वापस -EINVAL;

	अगर (tnr_dmd->state != CXD2880_TNRDMD_STATE_ACTIVE)
		वापस -EINVAL;

	अगर (tnr_dmd->sys != CXD2880_DTV_SYS_DVBT2)
		वापस -EINVAL;

	ret = slvt_मुक्तze_reg(tnr_dmd);
	अगर (ret)
		वापस ret;

	ret =
	    cxd2880_tnrdmd_dvbt2_mon_sync_stat(tnr_dmd, &sync_state,
					       &ts_lock,
					       &unlock_detected);
	अगर (ret) अणु
		slvt_unमुक्तze_reg(tnr_dmd);
		वापस ret;
	पूर्ण

	अगर (sync_state != 6) अणु
		slvt_unमुक्तze_reg(tnr_dmd);
		वापस -EAGAIN;
	पूर्ण

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x0b);
	अगर (ret) अणु
		slvt_unमुक्तze_reg(tnr_dmd);
		वापस ret;
	पूर्ण

	ret = tnr_dmd->io->पढ़ो_regs(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x34, ctl_val_reg,
				     माप(ctl_val_reg));
	अगर (ret) अणु
		slvt_unमुक्तze_reg(tnr_dmd);
		वापस ret;
	पूर्ण

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x04);
	अगर (ret) अणु
		slvt_unमुक्तze_reg(tnr_dmd);
		वापस ret;
	पूर्ण

	ret = tnr_dmd->io->पढ़ो_regs(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x10, nominal_rate_reg,
				     माप(nominal_rate_reg));
	अगर (ret) अणु
		slvt_unमुक्तze_reg(tnr_dmd);
		वापस ret;
	पूर्ण

	slvt_unमुक्तze_reg(tnr_dmd);

	dअगरf_upper =
	    (ctl_val_reg[0] & 0x7f) - (nominal_rate_reg[0] & 0x7f);

	अगर (dअगरf_upper < -1 || dअगरf_upper > 1)
		वापस -EAGAIN;

	trl_ctl_val = ctl_val_reg[1] << 24;
	trl_ctl_val |= ctl_val_reg[2] << 16;
	trl_ctl_val |= ctl_val_reg[3] << 8;
	trl_ctl_val |= ctl_val_reg[4];

	trcg_nominal_rate = nominal_rate_reg[1] << 24;
	trcg_nominal_rate |= nominal_rate_reg[2] << 16;
	trcg_nominal_rate |= nominal_rate_reg[3] << 8;
	trcg_nominal_rate |= nominal_rate_reg[4];

	trl_ctl_val >>= 1;
	trcg_nominal_rate >>= 1;

	अगर (dअगरf_upper == 1)
		num =
		    (पूर्णांक)((trl_ctl_val + 0x80000000u) -
			  trcg_nominal_rate);
	अन्यथा अगर (dअगरf_upper == -1)
		num =
		    -(पूर्णांक)((trcg_nominal_rate + 0x80000000u) -
			   trl_ctl_val);
	अन्यथा
		num = (पूर्णांक)(trl_ctl_val - trcg_nominal_rate);

	den = (nominal_rate_reg[0] & 0x7f) << 24;
	den |= nominal_rate_reg[1] << 16;
	den |= nominal_rate_reg[2] << 8;
	den |= nominal_rate_reg[3];
	den = (den + (390625 / 2)) / 390625;

	den >>= 1;

	अगर (num >= 0)
		*ppm = (num + (den / 2)) / den;
	अन्यथा
		*ppm = (num - (den / 2)) / den;

	वापस 0;
पूर्ण

पूर्णांक cxd2880_tnrdmd_dvbt2_mon_sampling_offset_sub(काष्ठा
						 cxd2880_tnrdmd
						 *tnr_dmd,
						 पूर्णांक *ppm)
अणु
	अगर (!tnr_dmd || !ppm)
		वापस -EINVAL;

	अगर (tnr_dmd->भागer_mode != CXD2880_TNRDMD_DIVERMODE_MAIN)
		वापस -EINVAL;

	वापस cxd2880_tnrdmd_dvbt2_mon_sampling_offset(tnr_dmd->भागer_sub,
							ppm);
पूर्ण

पूर्णांक cxd2880_tnrdmd_dvbt2_mon_qam(काष्ठा cxd2880_tnrdmd *tnr_dmd,
				 क्रमागत cxd2880_dvbt2_plp_btype type,
				 क्रमागत cxd2880_dvbt2_plp_स्थिरell *qam)
अणु
	u8 data;
	u8 l1_post_ok = 0;
	पूर्णांक ret;

	अगर (!tnr_dmd || !qam)
		वापस -EINVAL;

	अगर (tnr_dmd->भागer_mode == CXD2880_TNRDMD_DIVERMODE_SUB)
		वापस -EINVAL;

	अगर (tnr_dmd->state != CXD2880_TNRDMD_STATE_ACTIVE)
		वापस -EINVAL;

	अगर (tnr_dmd->sys != CXD2880_DTV_SYS_DVBT2)
		वापस -EINVAL;

	ret = slvt_मुक्तze_reg(tnr_dmd);
	अगर (ret)
		वापस ret;

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x0b);
	अगर (ret) अणु
		slvt_unमुक्तze_reg(tnr_dmd);
		वापस ret;
	पूर्ण

	ret = tnr_dmd->io->पढ़ो_regs(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x86, &l1_post_ok, 1);
	अगर (ret) अणु
		slvt_unमुक्तze_reg(tnr_dmd);
		वापस ret;
	पूर्ण

	अगर (!(l1_post_ok & 0x01)) अणु
		slvt_unमुक्तze_reg(tnr_dmd);
		वापस -EAGAIN;
	पूर्ण

	अगर (type == CXD2880_DVBT2_PLP_COMMON) अणु
		ret = tnr_dmd->io->पढ़ो_regs(tnr_dmd->io,
					     CXD2880_IO_TGT_DMD,
					     0xb6, &data, 1);
		अगर (ret) अणु
			slvt_unमुक्तze_reg(tnr_dmd);
			वापस ret;
		पूर्ण

		अगर (data == 0) अणु
			slvt_unमुक्तze_reg(tnr_dmd);
			वापस -EAGAIN;
		पूर्ण

		ret = tnr_dmd->io->पढ़ो_regs(tnr_dmd->io,
					     CXD2880_IO_TGT_DMD,
					     0xb1, &data, 1);
		अगर (ret) अणु
			slvt_unमुक्तze_reg(tnr_dmd);
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = tnr_dmd->io->पढ़ो_regs(tnr_dmd->io,
					     CXD2880_IO_TGT_DMD,
					     0x9e, &data, 1);
		अगर (ret) अणु
			slvt_unमुक्तze_reg(tnr_dmd);
			वापस ret;
		पूर्ण
	पूर्ण

	slvt_unमुक्तze_reg(tnr_dmd);

	*qam = (क्रमागत cxd2880_dvbt2_plp_स्थिरell)(data & 0x07);

	वापस ret;
पूर्ण

पूर्णांक cxd2880_tnrdmd_dvbt2_mon_code_rate(काष्ठा cxd2880_tnrdmd
				       *tnr_dmd,
				       क्रमागत cxd2880_dvbt2_plp_btype
				       type,
				       क्रमागत
				       cxd2880_dvbt2_plp_code_rate
				       *code_rate)
अणु
	u8 data;
	u8 l1_post_ok = 0;
	पूर्णांक ret;

	अगर (!tnr_dmd || !code_rate)
		वापस -EINVAL;

	अगर (tnr_dmd->भागer_mode == CXD2880_TNRDMD_DIVERMODE_SUB)
		वापस -EINVAL;

	अगर (tnr_dmd->state != CXD2880_TNRDMD_STATE_ACTIVE)
		वापस -EINVAL;

	अगर (tnr_dmd->sys != CXD2880_DTV_SYS_DVBT2)
		वापस -EINVAL;

	ret = slvt_मुक्तze_reg(tnr_dmd);
	अगर (ret)
		वापस ret;

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x0b);
	अगर (ret) अणु
		slvt_unमुक्तze_reg(tnr_dmd);
		वापस ret;
	पूर्ण

	ret = tnr_dmd->io->पढ़ो_regs(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x86, &l1_post_ok, 1);
	अगर (ret) अणु
		slvt_unमुक्तze_reg(tnr_dmd);
		वापस ret;
	पूर्ण

	अगर (!(l1_post_ok & 0x01)) अणु
		slvt_unमुक्तze_reg(tnr_dmd);
		वापस -EAGAIN;
	पूर्ण

	अगर (type == CXD2880_DVBT2_PLP_COMMON) अणु
		ret = tnr_dmd->io->पढ़ो_regs(tnr_dmd->io,
					     CXD2880_IO_TGT_DMD,
					     0xb6, &data, 1);
		अगर (ret) अणु
			slvt_unमुक्तze_reg(tnr_dmd);
			वापस ret;
		पूर्ण

		अगर (data == 0) अणु
			slvt_unमुक्तze_reg(tnr_dmd);
			वापस -EAGAIN;
		पूर्ण

		ret = tnr_dmd->io->पढ़ो_regs(tnr_dmd->io,
					     CXD2880_IO_TGT_DMD,
					     0xb0, &data, 1);
		अगर (ret) अणु
			slvt_unमुक्तze_reg(tnr_dmd);
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = tnr_dmd->io->पढ़ो_regs(tnr_dmd->io,
					     CXD2880_IO_TGT_DMD,
					     0x9d, &data, 1);
		अगर (ret) अणु
			slvt_unमुक्तze_reg(tnr_dmd);
			वापस ret;
		पूर्ण
	पूर्ण

	slvt_unमुक्तze_reg(tnr_dmd);

	*code_rate = (क्रमागत cxd2880_dvbt2_plp_code_rate)(data & 0x07);

	वापस ret;
पूर्ण

पूर्णांक cxd2880_tnrdmd_dvbt2_mon_profile(काष्ठा cxd2880_tnrdmd
				     *tnr_dmd,
				     क्रमागत cxd2880_dvbt2_profile
				     *profile)
अणु
	u8 data;
	पूर्णांक ret;

	अगर (!tnr_dmd || !profile)
		वापस -EINVAL;

	अगर (tnr_dmd->state != CXD2880_TNRDMD_STATE_ACTIVE)
		वापस -EINVAL;

	अगर (tnr_dmd->sys != CXD2880_DTV_SYS_DVBT2)
		वापस -EINVAL;

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x0b);
	अगर (ret)
		वापस ret;

	ret = tnr_dmd->io->पढ़ो_regs(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x22, &data, माप(data));
	अगर (ret)
		वापस ret;

	अगर (data & 0x02) अणु
		अगर (data & 0x01)
			*profile = CXD2880_DVBT2_PROखाता_LITE;
		अन्यथा
			*profile = CXD2880_DVBT2_PROखाता_BASE;
	पूर्ण अन्यथा अणु
		ret = -EAGAIN;
		अगर (tnr_dmd->भागer_mode ==
		    CXD2880_TNRDMD_DIVERMODE_MAIN)
			ret =
			    cxd2880_tnrdmd_dvbt2_mon_profile(tnr_dmd->भागer_sub,
							     profile);

		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dvbt2_calc_ssi(काष्ठा cxd2880_tnrdmd *tnr_dmd,
			  पूर्णांक rf_lvl, u8 *ssi)
अणु
	क्रमागत cxd2880_dvbt2_plp_स्थिरell qam;
	क्रमागत cxd2880_dvbt2_plp_code_rate code_rate;
	पूर्णांक prel;
	पूर्णांक temp_ssi = 0;
	पूर्णांक ret;

	अगर (!tnr_dmd || !ssi)
		वापस -EINVAL;

	ret =
	    cxd2880_tnrdmd_dvbt2_mon_qam(tnr_dmd, CXD2880_DVBT2_PLP_DATA, &qam);
	अगर (ret)
		वापस ret;

	ret =
	    cxd2880_tnrdmd_dvbt2_mon_code_rate(tnr_dmd, CXD2880_DVBT2_PLP_DATA,
					       &code_rate);
	अगर (ret)
		वापस ret;

	अगर (code_rate > CXD2880_DVBT2_R2_5 || qam > CXD2880_DVBT2_QAM256)
		वापस -EINVAL;

	prel = rf_lvl - ref_dbm_1000[qam][code_rate];

	अगर (prel < -15000)
		temp_ssi = 0;
	अन्यथा अगर (prel < 0)
		temp_ssi = ((2 * (prel + 15000)) + 1500) / 3000;
	अन्यथा अगर (prel < 20000)
		temp_ssi = (((4 * prel) + 500) / 1000) + 10;
	अन्यथा अगर (prel < 35000)
		temp_ssi = (((2 * (prel - 20000)) + 1500) / 3000) + 90;
	अन्यथा
		temp_ssi = 100;

	*ssi = (temp_ssi > 100) ? 100 : (u8)temp_ssi;

	वापस ret;
पूर्ण

पूर्णांक cxd2880_tnrdmd_dvbt2_mon_ssi(काष्ठा cxd2880_tnrdmd *tnr_dmd,
				 u8 *ssi)
अणु
	पूर्णांक rf_lvl = 0;
	पूर्णांक ret;

	अगर (!tnr_dmd || !ssi)
		वापस -EINVAL;

	अगर (tnr_dmd->भागer_mode == CXD2880_TNRDMD_DIVERMODE_SUB)
		वापस -EINVAL;

	अगर (tnr_dmd->state != CXD2880_TNRDMD_STATE_ACTIVE)
		वापस -EINVAL;

	अगर (tnr_dmd->sys != CXD2880_DTV_SYS_DVBT2)
		वापस -EINVAL;

	ret = cxd2880_tnrdmd_mon_rf_lvl(tnr_dmd, &rf_lvl);
	अगर (ret)
		वापस ret;

	वापस dvbt2_calc_ssi(tnr_dmd, rf_lvl, ssi);
पूर्ण

पूर्णांक cxd2880_tnrdmd_dvbt2_mon_ssi_sub(काष्ठा cxd2880_tnrdmd
				     *tnr_dmd, u8 *ssi)
अणु
	पूर्णांक rf_lvl = 0;
	पूर्णांक ret;

	अगर (!tnr_dmd || !ssi)
		वापस -EINVAL;

	अगर (tnr_dmd->भागer_mode != CXD2880_TNRDMD_DIVERMODE_MAIN)
		वापस -EINVAL;

	अगर (tnr_dmd->state != CXD2880_TNRDMD_STATE_ACTIVE)
		वापस -EINVAL;

	अगर (tnr_dmd->sys != CXD2880_DTV_SYS_DVBT2)
		वापस -EINVAL;

	ret = cxd2880_tnrdmd_mon_rf_lvl(tnr_dmd->भागer_sub, &rf_lvl);
	अगर (ret)
		वापस ret;

	वापस dvbt2_calc_ssi(tnr_dmd, rf_lvl, ssi);
पूर्ण
