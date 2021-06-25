<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * cxd2880_tnrdmd_dvbt_mon.c
 * Sony CXD2880 DVB-T2/T tuner + demodulator driver
 * DVB-T monitor functions
 *
 * Copyright (C) 2016, 2017, 2018 Sony Semiconductor Solutions Corporation
 */

#समावेश "cxd2880_tnrdmd_mon.h"
#समावेश "cxd2880_tnrdmd_dvbt.h"
#समावेश "cxd2880_tnrdmd_dvbt_mon.h"

#समावेश <media/dvb_गणित.स>

अटल स्थिर पूर्णांक ref_dbm_1000[3][5] = अणु
	अणु-93000, -91000, -90000, -89000, -88000पूर्ण,
	अणु-87000, -85000, -84000, -83000, -82000पूर्ण,
	अणु-82000, -80000, -78000, -77000, -76000पूर्ण,
पूर्ण;

अटल पूर्णांक is_tps_locked(काष्ठा cxd2880_tnrdmd *tnr_dmd);

पूर्णांक cxd2880_tnrdmd_dvbt_mon_sync_stat(काष्ठा cxd2880_tnrdmd
				      *tnr_dmd, u8 *sync_stat,
				      u8 *ts_lock_stat,
				      u8 *unlock_detected)
अणु
	u8 rdata = 0x00;
	पूर्णांक ret;

	अगर (!tnr_dmd || !sync_stat || !ts_lock_stat || !unlock_detected)
		वापस -EINVAL;

	अगर (tnr_dmd->state != CXD2880_TNRDMD_STATE_ACTIVE)
		वापस -EINVAL;
	अगर (tnr_dmd->sys != CXD2880_DTV_SYS_DVBT)
		वापस -EINVAL;

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x0d);
	अगर (ret)
		वापस ret;

	ret = tnr_dmd->io->पढ़ो_regs(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x10, &rdata, 1);
	अगर (ret)
		वापस ret;

	*unlock_detected = (rdata & 0x10) ? 1 : 0;
	*sync_stat = rdata & 0x07;
	*ts_lock_stat = (rdata & 0x20) ? 1 : 0;

	अगर (*sync_stat == 0x07)
		वापस -EAGAIN;

	वापस ret;
पूर्ण

पूर्णांक cxd2880_tnrdmd_dvbt_mon_sync_stat_sub(काष्ठा cxd2880_tnrdmd
					  *tnr_dmd, u8 *sync_stat,
					  u8 *unlock_detected)
अणु
	u8 ts_lock_stat = 0;

	अगर (!tnr_dmd || !sync_stat || !unlock_detected)
		वापस -EINVAL;

	अगर (tnr_dmd->भागer_mode != CXD2880_TNRDMD_DIVERMODE_MAIN)
		वापस -EINVAL;

	वापस cxd2880_tnrdmd_dvbt_mon_sync_stat(tnr_dmd->भागer_sub,
						 sync_stat,
						 &ts_lock_stat,
						 unlock_detected);
पूर्ण

पूर्णांक cxd2880_tnrdmd_dvbt_mon_mode_guard(काष्ठा cxd2880_tnrdmd
				       *tnr_dmd,
				       क्रमागत cxd2880_dvbt_mode
				       *mode,
				       क्रमागत cxd2880_dvbt_guard
				       *guard)
अणु
	u8 rdata = 0x00;
	पूर्णांक ret;

	अगर (!tnr_dmd || !mode || !guard)
		वापस -EINVAL;

	अगर (tnr_dmd->state != CXD2880_TNRDMD_STATE_ACTIVE)
		वापस -EINVAL;

	अगर (tnr_dmd->sys != CXD2880_DTV_SYS_DVBT)
		वापस -EINVAL;

	ret = slvt_मुक्तze_reg(tnr_dmd);
	अगर (ret)
		वापस ret;

	ret = is_tps_locked(tnr_dmd);
	अगर (ret) अणु
		slvt_unमुक्तze_reg(tnr_dmd);

		अगर (tnr_dmd->भागer_mode == CXD2880_TNRDMD_DIVERMODE_MAIN)
			ret =
			    cxd2880_tnrdmd_dvbt_mon_mode_guard(tnr_dmd->भागer_sub,
							       mode, guard);

		वापस ret;
	पूर्ण

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x0d);
	अगर (ret) अणु
		slvt_unमुक्तze_reg(tnr_dmd);
		वापस ret;
	पूर्ण

	ret = tnr_dmd->io->पढ़ो_regs(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x1b, &rdata, 1);
	अगर (ret) अणु
		slvt_unमुक्तze_reg(tnr_dmd);
		वापस ret;
	पूर्ण

	slvt_unमुक्तze_reg(tnr_dmd);

	*mode = (क्रमागत cxd2880_dvbt_mode)((rdata >> 2) & 0x03);
	*guard = (क्रमागत cxd2880_dvbt_guard)(rdata & 0x03);

	वापस ret;
पूर्ण

पूर्णांक cxd2880_tnrdmd_dvbt_mon_carrier_offset(काष्ठा cxd2880_tnrdmd
					   *tnr_dmd, पूर्णांक *offset)
अणु
	u8 rdata[4];
	u32 ctl_val = 0;
	पूर्णांक ret;

	अगर (!tnr_dmd || !offset)
		वापस -EINVAL;

	अगर (tnr_dmd->state != CXD2880_TNRDMD_STATE_ACTIVE)
		वापस -EINVAL;

	अगर (tnr_dmd->sys != CXD2880_DTV_SYS_DVBT)
		वापस -EINVAL;

	ret = slvt_मुक्तze_reg(tnr_dmd);
	अगर (ret)
		वापस ret;

	ret = is_tps_locked(tnr_dmd);
	अगर (ret) अणु
		slvt_unमुक्तze_reg(tnr_dmd);
		वापस ret;
	पूर्ण

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x0d);
	अगर (ret) अणु
		slvt_unमुक्तze_reg(tnr_dmd);
		वापस ret;
	पूर्ण

	ret = tnr_dmd->io->पढ़ो_regs(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x1d, rdata, 4);
	अगर (ret) अणु
		slvt_unमुक्तze_reg(tnr_dmd);
		वापस ret;
	पूर्ण

	slvt_unमुक्तze_reg(tnr_dmd);

	ctl_val =
	    ((rdata[0] & 0x1f) << 24) | (rdata[1] << 16) | (rdata[2] << 8) |
	    (rdata[3]);
	*offset = cxd2880_convert2s_complement(ctl_val, 29);
	*offset = -1 * ((*offset) * tnr_dmd->bandwidth / 235);

	वापस ret;
पूर्ण

पूर्णांक cxd2880_tnrdmd_dvbt_mon_carrier_offset_sub(काष्ठा
					       cxd2880_tnrdmd
					       *tnr_dmd,
					       पूर्णांक *offset)
अणु
	अगर (!tnr_dmd || !offset)
		वापस -EINVAL;

	अगर (tnr_dmd->भागer_mode != CXD2880_TNRDMD_DIVERMODE_MAIN)
		वापस -EINVAL;

	वापस cxd2880_tnrdmd_dvbt_mon_carrier_offset(tnr_dmd->भागer_sub,
						      offset);
पूर्ण

पूर्णांक cxd2880_tnrdmd_dvbt_mon_tps_info(काष्ठा cxd2880_tnrdmd
				     *tnr_dmd,
				     काष्ठा cxd2880_dvbt_tpsinfo
				     *info)
अणु
	u8 rdata[7];
	u8 cell_id_ok = 0;
	पूर्णांक ret;

	अगर (!tnr_dmd || !info)
		वापस -EINVAL;

	अगर (tnr_dmd->state != CXD2880_TNRDMD_STATE_ACTIVE)
		वापस -EINVAL;

	अगर (tnr_dmd->sys != CXD2880_DTV_SYS_DVBT)
		वापस -EINVAL;

	ret = slvt_मुक्तze_reg(tnr_dmd);
	अगर (ret)
		वापस ret;

	ret = is_tps_locked(tnr_dmd);
	अगर (ret) अणु
		slvt_unमुक्तze_reg(tnr_dmd);

		अगर (tnr_dmd->भागer_mode == CXD2880_TNRDMD_DIVERMODE_MAIN)
			ret =
			    cxd2880_tnrdmd_dvbt_mon_tps_info(tnr_dmd->भागer_sub,
							     info);

		वापस ret;
	पूर्ण

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x0d);
	अगर (ret) अणु
		slvt_unमुक्तze_reg(tnr_dmd);
		वापस ret;
	पूर्ण

	ret = tnr_dmd->io->पढ़ो_regs(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x29, rdata, 7);
	अगर (ret) अणु
		slvt_unमुक्तze_reg(tnr_dmd);
		वापस ret;
	पूर्ण

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x11);
	अगर (ret) अणु
		slvt_unमुक्तze_reg(tnr_dmd);
		वापस ret;
	पूर्ण

	ret = tnr_dmd->io->पढ़ो_regs(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0xd5, &cell_id_ok, 1);
	अगर (ret) अणु
		slvt_unमुक्तze_reg(tnr_dmd);
		वापस ret;
	पूर्ण

	slvt_unमुक्तze_reg(tnr_dmd);

	info->स्थिरellation =
	    (क्रमागत cxd2880_dvbt_स्थिरellation)((rdata[0] >> 6) & 0x03);
	info->hierarchy = (क्रमागत cxd2880_dvbt_hierarchy)((rdata[0] >> 3) & 0x07);
	info->rate_hp = (क्रमागत cxd2880_dvbt_coderate)(rdata[0] & 0x07);
	info->rate_lp = (क्रमागत cxd2880_dvbt_coderate)((rdata[1] >> 5) & 0x07);
	info->guard = (क्रमागत cxd2880_dvbt_guard)((rdata[1] >> 3) & 0x03);
	info->mode = (क्रमागत cxd2880_dvbt_mode)((rdata[1] >> 1) & 0x03);
	info->fnum = (rdata[2] >> 6) & 0x03;
	info->length_indicator = rdata[2] & 0x3f;
	info->cell_id = (rdata[3] << 8) | rdata[4];
	info->reserved_even = rdata[5] & 0x3f;
	info->reserved_odd = rdata[6] & 0x3f;

	info->cell_id_ok = cell_id_ok & 0x01;

	वापस ret;
पूर्ण

पूर्णांक cxd2880_tnrdmd_dvbt_mon_packet_error_number(काष्ठा
						cxd2880_tnrdmd
						*tnr_dmd,
						u32 *pen)
अणु
	u8 rdata[3];
	पूर्णांक ret;

	अगर (!tnr_dmd || !pen)
		वापस -EINVAL;

	अगर (tnr_dmd->भागer_mode == CXD2880_TNRDMD_DIVERMODE_SUB)
		वापस -EINVAL;

	अगर (tnr_dmd->state != CXD2880_TNRDMD_STATE_ACTIVE)
		वापस -EINVAL;

	अगर (tnr_dmd->sys != CXD2880_DTV_SYS_DVBT)
		वापस -EINVAL;

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x0d);
	अगर (ret)
		वापस ret;

	ret = tnr_dmd->io->पढ़ो_regs(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x26, rdata, 3);
	अगर (ret)
		वापस ret;

	अगर (!(rdata[0] & 0x01))
		वापस -EAGAIN;

	*pen = (rdata[1] << 8) | rdata[2];

	वापस ret;
पूर्ण

पूर्णांक cxd2880_tnrdmd_dvbt_mon_spectrum_sense(काष्ठा cxd2880_tnrdmd
					   *tnr_dmd,
					    क्रमागत
					    cxd2880_tnrdmd_spectrum_sense
					    *sense)
अणु
	u8 data = 0;
	पूर्णांक ret;

	अगर (!tnr_dmd || !sense)
		वापस -EINVAL;

	अगर (tnr_dmd->state != CXD2880_TNRDMD_STATE_ACTIVE)
		वापस -EINVAL;

	अगर (tnr_dmd->sys != CXD2880_DTV_SYS_DVBT)
		वापस -EINVAL;

	ret = slvt_मुक्तze_reg(tnr_dmd);
	अगर (ret)
		वापस ret;

	ret = is_tps_locked(tnr_dmd);
	अगर (ret) अणु
		slvt_unमुक्तze_reg(tnr_dmd);

		अगर (tnr_dmd->भागer_mode == CXD2880_TNRDMD_DIVERMODE_MAIN)
			ret = cxd2880_tnrdmd_dvbt_mon_spectrum_sense(tnr_dmd->भागer_sub,
								     sense);

		वापस ret;
	पूर्ण

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x0d);
	अगर (ret) अणु
		slvt_unमुक्तze_reg(tnr_dmd);
		वापस ret;
	पूर्ण

	ret = tnr_dmd->io->पढ़ो_regs(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x1c, &data, माप(data));
	अगर (ret) अणु
		slvt_unमुक्तze_reg(tnr_dmd);
		वापस ret;
	पूर्ण

	slvt_unमुक्तze_reg(tnr_dmd);

	*sense =
	    (data & 0x01) ? CXD2880_TNRDMD_SPECTRUM_INV :
	    CXD2880_TNRDMD_SPECTRUM_NORMAL;

	वापस ret;
पूर्ण

अटल पूर्णांक dvbt_पढ़ो_snr_reg(काष्ठा cxd2880_tnrdmd *tnr_dmd,
			     u16 *reg_value)
अणु
	u8 rdata[2];
	पूर्णांक ret;

	अगर (!tnr_dmd || !reg_value)
		वापस -EINVAL;

	ret = slvt_मुक्तze_reg(tnr_dmd);
	अगर (ret)
		वापस ret;

	ret = is_tps_locked(tnr_dmd);
	अगर (ret) अणु
		slvt_unमुक्तze_reg(tnr_dmd);
		वापस ret;
	पूर्ण

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x0d);
	अगर (ret) अणु
		slvt_unमुक्तze_reg(tnr_dmd);
		वापस ret;
	पूर्ण

	ret = tnr_dmd->io->पढ़ो_regs(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x13, rdata, 2);
	अगर (ret) अणु
		slvt_unमुक्तze_reg(tnr_dmd);
		वापस ret;
	पूर्ण

	slvt_unमुक्तze_reg(tnr_dmd);

	*reg_value = (rdata[0] << 8) | rdata[1];

	वापस ret;
पूर्ण

अटल पूर्णांक dvbt_calc_snr(काष्ठा cxd2880_tnrdmd *tnr_dmd,
			 u32 reg_value, पूर्णांक *snr)
अणु
	अगर (!tnr_dmd || !snr)
		वापस -EINVAL;

	अगर (reg_value == 0)
		वापस -EAGAIN;

	अगर (reg_value > 4996)
		reg_value = 4996;

	*snr = पूर्णांकlog10(reg_value) - पूर्णांकlog10(5350 - reg_value);
	*snr = (*snr + 839) / 1678 + 28500;

	वापस 0;
पूर्ण

पूर्णांक cxd2880_tnrdmd_dvbt_mon_snr(काष्ठा cxd2880_tnrdmd *tnr_dmd,
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

	अगर (tnr_dmd->sys != CXD2880_DTV_SYS_DVBT)
		वापस -EINVAL;

	अगर (tnr_dmd->भागer_mode == CXD2880_TNRDMD_DIVERMODE_SINGLE) अणु
		ret = dvbt_पढ़ो_snr_reg(tnr_dmd, &reg_value);
		अगर (ret)
			वापस ret;

		ret = dvbt_calc_snr(tnr_dmd, reg_value, snr);
	पूर्ण अन्यथा अणु
		पूर्णांक snr_मुख्य = 0;
		पूर्णांक snr_sub = 0;

		ret =
		    cxd2880_tnrdmd_dvbt_mon_snr_भागer(tnr_dmd, snr, &snr_मुख्य,
						      &snr_sub);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक cxd2880_tnrdmd_dvbt_mon_snr_भागer(काष्ठा cxd2880_tnrdmd
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

	अगर (tnr_dmd->sys != CXD2880_DTV_SYS_DVBT)
		वापस -EINVAL;

	ret = dvbt_पढ़ो_snr_reg(tnr_dmd, &reg_value);
	अगर (!ret) अणु
		ret = dvbt_calc_snr(tnr_dmd, reg_value, snr_मुख्य);
		अगर (ret)
			reg_value = 0;
	पूर्ण अन्यथा अगर (ret == -EAGAIN) अणु
		reg_value = 0;
	पूर्ण अन्यथा अणु
		वापस ret;
	पूर्ण

	reg_value_sum += reg_value;

	ret = dvbt_पढ़ो_snr_reg(tnr_dmd->भागer_sub, &reg_value);
	अगर (!ret) अणु
		ret = dvbt_calc_snr(tnr_dmd->भागer_sub, reg_value, snr_sub);
		अगर (ret)
			reg_value = 0;
	पूर्ण अन्यथा अगर (ret == -EAGAIN) अणु
		reg_value = 0;
	पूर्ण अन्यथा अणु
		वापस ret;
	पूर्ण

	reg_value_sum += reg_value;

	वापस dvbt_calc_snr(tnr_dmd, reg_value_sum, snr);
पूर्ण

पूर्णांक cxd2880_tnrdmd_dvbt_mon_sampling_offset(काष्ठा cxd2880_tnrdmd
					    *tnr_dmd, पूर्णांक *ppm)
अणु
	u8 ctl_val_reg[5];
	u8 nominal_rate_reg[5];
	u32 trl_ctl_val = 0;
	u32 trcg_nominal_rate = 0;
	पूर्णांक num;
	पूर्णांक den;
	s8 dअगरf_upper = 0;
	पूर्णांक ret;

	अगर (!tnr_dmd || !ppm)
		वापस -EINVAL;

	अगर (tnr_dmd->state != CXD2880_TNRDMD_STATE_ACTIVE)
		वापस -EINVAL;

	अगर (tnr_dmd->sys != CXD2880_DTV_SYS_DVBT)
		वापस -EINVAL;

	ret = slvt_मुक्तze_reg(tnr_dmd);
	अगर (ret)
		वापस ret;

	ret = is_tps_locked(tnr_dmd);
	अगर (ret) अणु
		slvt_unमुक्तze_reg(tnr_dmd);
		वापस ret;
	पूर्ण

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x0d);
	अगर (ret) अणु
		slvt_unमुक्तze_reg(tnr_dmd);
		वापस ret;
	पूर्ण

	ret = tnr_dmd->io->पढ़ो_regs(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x21, ctl_val_reg,
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
				     0x60, nominal_rate_reg,
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

	वापस ret;
पूर्ण

पूर्णांक cxd2880_tnrdmd_dvbt_mon_sampling_offset_sub(काष्ठा
						cxd2880_tnrdmd
						*tnr_dmd, पूर्णांक *ppm)
अणु
	अगर (!tnr_dmd || !ppm)
		वापस -EINVAL;

	अगर (tnr_dmd->भागer_mode != CXD2880_TNRDMD_DIVERMODE_MAIN)
		वापस -EINVAL;

	वापस cxd2880_tnrdmd_dvbt_mon_sampling_offset(tnr_dmd->भागer_sub, ppm);
पूर्ण

अटल पूर्णांक dvbt_calc_ssi(काष्ठा cxd2880_tnrdmd *tnr_dmd,
			 पूर्णांक rf_lvl, u8 *ssi)
अणु
	काष्ठा cxd2880_dvbt_tpsinfo tps;
	पूर्णांक prel;
	पूर्णांक temp_ssi = 0;
	पूर्णांक ret;

	अगर (!tnr_dmd || !ssi)
		वापस -EINVAL;

	ret = cxd2880_tnrdmd_dvbt_mon_tps_info(tnr_dmd, &tps);
	अगर (ret)
		वापस ret;

	अगर (tps.स्थिरellation >= CXD2880_DVBT_CONSTELLATION_RESERVED_3 ||
	    tps.rate_hp >= CXD2880_DVBT_CODERATE_RESERVED_5)
		वापस -EINVAL;

	prel = rf_lvl - ref_dbm_1000[tps.स्थिरellation][tps.rate_hp];

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

पूर्णांक cxd2880_tnrdmd_dvbt_mon_ssi(काष्ठा cxd2880_tnrdmd *tnr_dmd,
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

	अगर (tnr_dmd->sys != CXD2880_DTV_SYS_DVBT)
		वापस -EINVAL;

	ret = cxd2880_tnrdmd_mon_rf_lvl(tnr_dmd, &rf_lvl);
	अगर (ret)
		वापस ret;

	वापस dvbt_calc_ssi(tnr_dmd, rf_lvl, ssi);
पूर्ण

पूर्णांक cxd2880_tnrdmd_dvbt_mon_ssi_sub(काष्ठा cxd2880_tnrdmd *tnr_dmd,
				    u8 *ssi)
अणु
	पूर्णांक rf_lvl = 0;
	पूर्णांक ret;

	अगर (!tnr_dmd || !ssi)
		वापस -EINVAL;

	अगर (tnr_dmd->भागer_mode != CXD2880_TNRDMD_DIVERMODE_MAIN)
		वापस -EINVAL;

	अगर (tnr_dmd->state != CXD2880_TNRDMD_STATE_ACTIVE)
		वापस -EINVAL;

	अगर (tnr_dmd->sys != CXD2880_DTV_SYS_DVBT)
		वापस -EINVAL;

	ret = cxd2880_tnrdmd_mon_rf_lvl(tnr_dmd->भागer_sub, &rf_lvl);
	अगर (ret)
		वापस ret;

	वापस dvbt_calc_ssi(tnr_dmd, rf_lvl, ssi);
पूर्ण

अटल पूर्णांक is_tps_locked(काष्ठा cxd2880_tnrdmd *tnr_dmd)
अणु
	u8 sync = 0;
	u8 tslock = 0;
	u8 early_unlock = 0;
	पूर्णांक ret;

	अगर (!tnr_dmd)
		वापस -EINVAL;

	ret =
	    cxd2880_tnrdmd_dvbt_mon_sync_stat(tnr_dmd, &sync, &tslock,
					      &early_unlock);
	अगर (ret)
		वापस ret;

	अगर (sync != 6)
		वापस -EAGAIN;

	वापस 0;
पूर्ण
