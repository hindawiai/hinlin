<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * cxd2880_tnrdmd_dvbt.c
 * Sony CXD2880 DVB-T2/T tuner + demodulator driver
 * control functions क्रम DVB-T
 *
 * Copyright (C) 2016, 2017, 2018 Sony Semiconductor Solutions Corporation
 */

#समावेश <media/dvb_frontend.h>

#समावेश "cxd2880_tnrdmd_dvbt.h"
#समावेश "cxd2880_tnrdmd_dvbt_mon.h"

अटल स्थिर काष्ठा cxd2880_reg_value tune_dmd_setting_seq1[] = अणु
	अणु0x00, 0x00पूर्ण, अणु0x31, 0x01पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा cxd2880_reg_value tune_dmd_setting_seq2[] = अणु
	अणु0x00, 0x04पूर्ण, अणु0x5c, 0xfbपूर्ण, अणु0x00, 0x10पूर्ण, अणु0xa4, 0x03पूर्ण,
	अणु0x00, 0x14पूर्ण, अणु0xb0, 0x00पूर्ण, अणु0x00, 0x25पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा cxd2880_reg_value tune_dmd_setting_seq3[] = अणु
	अणु0x00, 0x12पूर्ण, अणु0x44, 0x00पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा cxd2880_reg_value tune_dmd_setting_seq4[] = अणु
	अणु0x00, 0x11पूर्ण, अणु0x87, 0xd2पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा cxd2880_reg_value tune_dmd_setting_seq5[] = अणु
	अणु0x00, 0x00पूर्ण, अणु0xfd, 0x01पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा cxd2880_reg_value sleep_dmd_setting_seq1[] = अणु
	अणु0x00, 0x04पूर्ण, अणु0x5c, 0xd8पूर्ण, अणु0x00, 0x10पूर्ण, अणु0xa4, 0x00पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा cxd2880_reg_value sleep_dmd_setting_seq2[] = अणु
	अणु0x00, 0x11पूर्ण, अणु0x87, 0x04पूर्ण,
पूर्ण;

अटल पूर्णांक x_tune_dvbt_demod_setting(काष्ठा cxd2880_tnrdmd
				     *tnr_dmd,
				     क्रमागत cxd2880_dtv_bandwidth
				     bandwidth,
				     क्रमागत cxd2880_tnrdmd_घड़ीmode
				     clk_mode)
अणु
	अटल स्थिर u8 clk_mode_ckffrq_a[2] = अणु 0x52, 0x49 पूर्ण;
	अटल स्थिर u8 clk_mode_ckffrq_b[2] = अणु 0x5d, 0x55 पूर्ण;
	अटल स्थिर u8 clk_mode_ckffrq_c[2] = अणु 0x60, 0x00 पूर्ण;
	अटल स्थिर u8 ratectl_margin[2] = अणु 0x01, 0xf0 पूर्ण;
	अटल स्थिर u8 maxclkcnt_a[3] = अणु 0x73, 0xca, 0x49 पूर्ण;
	अटल स्थिर u8 maxclkcnt_b[3] = अणु 0xc8, 0x13, 0xaa पूर्ण;
	अटल स्थिर u8 maxclkcnt_c[3] = अणु 0xdc, 0x6c, 0x00 पूर्ण;

	अटल स्थिर u8 bw8_nomi_ac[5] = अणु 0x15, 0x00, 0x00, 0x00, 0x00पूर्ण;
	अटल स्थिर u8 bw8_nomi_b[5] = अणु 0x14, 0x6a, 0xaa, 0xaa, 0xaaपूर्ण;
	अटल स्थिर u8 bw8_gtकरोfst_a[2] = अणु 0x01, 0x28 पूर्ण;
	अटल स्थिर u8 bw8_gtकरोfst_b[2] = अणु 0x11, 0x44 पूर्ण;
	अटल स्थिर u8 bw8_gtकरोfst_c[2] = अणु 0x15, 0x28 पूर्ण;
	अटल स्थिर u8 bw8_mrc_a[5] = अणु 0x30, 0x00, 0x00, 0x90, 0x00 पूर्ण;
	अटल स्थिर u8 bw8_mrc_b[5] = अणु 0x36, 0x71, 0x00, 0xa3, 0x55 पूर्ण;
	अटल स्थिर u8 bw8_mrc_c[5] = अणु 0x38, 0x00, 0x00, 0xa8, 0x00 पूर्ण;
	अटल स्थिर u8 bw8_notch[4] = अणु 0xb3, 0x00, 0x01, 0x02 पूर्ण;

	अटल स्थिर u8 bw7_nomi_ac[5] = अणु 0x18, 0x00, 0x00, 0x00, 0x00पूर्ण;
	अटल स्थिर u8 bw7_nomi_b[5] = अणु 0x17, 0x55, 0x55, 0x55, 0x55पूर्ण;
	अटल स्थिर u8 bw7_gtकरोfst_a[2] = अणु 0x12, 0x4c पूर्ण;
	अटल स्थिर u8 bw7_gtकरोfst_b[2] = अणु 0x1f, 0x15 पूर्ण;
	अटल स्थिर u8 bw7_gtकरोfst_c[2] = अणु 0x1f, 0xf8 पूर्ण;
	अटल स्थिर u8 bw7_mrc_a[5] = अणु 0x36, 0xdb, 0x00, 0xa4, 0x92 पूर्ण;
	अटल स्थिर u8 bw7_mrc_b[5] = अणु 0x3e, 0x38, 0x00, 0xba, 0xaa पूर्ण;
	अटल स्थिर u8 bw7_mrc_c[5] = अणु 0x40, 0x00, 0x00, 0xc0, 0x00 पूर्ण;
	अटल स्थिर u8 bw7_notch[4] = अणु 0xb8, 0x00, 0x00, 0x03 पूर्ण;

	अटल स्थिर u8 bw6_nomi_ac[5] = अणु 0x1c, 0x00, 0x00, 0x00, 0x00पूर्ण;
	अटल स्थिर u8 bw6_nomi_b[5] = अणु 0x1b, 0x38, 0xe3, 0x8e, 0x38पूर्ण;
	अटल स्थिर u8 bw6_gtकरोfst_a[2] = अणु 0x1f, 0xf8 पूर्ण;
	अटल स्थिर u8 bw6_gtकरोfst_b[2] = अणु 0x24, 0x43 पूर्ण;
	अटल स्थिर u8 bw6_gtकरोfst_c[2] = अणु 0x25, 0x4c पूर्ण;
	अटल स्थिर u8 bw6_mrc_a[5] = अणु 0x40, 0x00, 0x00, 0xc0, 0x00 पूर्ण;
	अटल स्थिर u8 bw6_mrc_b[5] = अणु 0x48, 0x97, 0x00, 0xd9, 0xc7 पूर्ण;
	अटल स्थिर u8 bw6_mrc_c[5] = अणु 0x4a, 0xaa, 0x00, 0xdf, 0xff पूर्ण;
	अटल स्थिर u8 bw6_notch[4] = अणु 0xbe, 0xab, 0x00, 0x03 पूर्ण;

	अटल स्थिर u8 bw5_nomi_ac[5] = अणु 0x21, 0x99, 0x99, 0x99, 0x99पूर्ण;
	अटल स्थिर u8 bw5_nomi_b[5] = अणु 0x20, 0xaa, 0xaa, 0xaa, 0xaaपूर्ण;
	अटल स्थिर u8 bw5_gtकरोfst_a[2] = अणु 0x26, 0x5d पूर्ण;
	अटल स्थिर u8 bw5_gtकरोfst_b[2] = अणु 0x2b, 0x84 पूर्ण;
	अटल स्थिर u8 bw5_gtकरोfst_c[2] = अणु 0x2c, 0xc2 पूर्ण;
	अटल स्थिर u8 bw5_mrc_a[5] = अणु 0x4c, 0xcc, 0x00, 0xe6, 0x66 पूर्ण;
	अटल स्थिर u8 bw5_mrc_b[5] = अणु 0x57, 0x1c, 0x01, 0x05, 0x55 पूर्ण;
	अटल स्थिर u8 bw5_mrc_c[5] = अणु 0x59, 0x99, 0x01, 0x0c, 0xcc पूर्ण;
	अटल स्थिर u8 bw5_notch[4] = अणु 0xc8, 0x01, 0x00, 0x03 पूर्ण;
	स्थिर u8 *data = शून्य;
	u8 sst_data;
	पूर्णांक ret;

	अगर (!tnr_dmd)
		वापस -EINVAL;

	ret = cxd2880_io_ग_लिखो_multi_regs(tnr_dmd->io,
					  CXD2880_IO_TGT_SYS,
					  tune_dmd_setting_seq1,
					  ARRAY_SIZE(tune_dmd_setting_seq1));
	अगर (ret)
		वापस ret;

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x04);
	अगर (ret)
		वापस ret;

	चयन (clk_mode) अणु
	हाल CXD2880_TNRDMD_CLOCKMODE_A:
		data = clk_mode_ckffrq_a;
		अवरोध;
	हाल CXD2880_TNRDMD_CLOCKMODE_B:
		data = clk_mode_ckffrq_b;
		अवरोध;
	हाल CXD2880_TNRDMD_CLOCKMODE_C:
		data = clk_mode_ckffrq_c;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ret = tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
				      CXD2880_IO_TGT_DMD,
				      0x65, data, 2);
	अगर (ret)
		वापस ret;

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x5d, 0x07);
	अगर (ret)
		वापस ret;

	अगर (tnr_dmd->भागer_mode != CXD2880_TNRDMD_DIVERMODE_SUB) अणु
		u8 data[2] = अणु 0x01, 0x01 पूर्ण;

		ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
					     CXD2880_IO_TGT_DMD,
					     0x00, 0x00);
		अगर (ret)
			वापस ret;

		ret = tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
					      CXD2880_IO_TGT_DMD,
					      0xce, data, 2);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = cxd2880_io_ग_लिखो_multi_regs(tnr_dmd->io,
					  CXD2880_IO_TGT_DMD,
					  tune_dmd_setting_seq2,
					  ARRAY_SIZE(tune_dmd_setting_seq2));
	अगर (ret)
		वापस ret;

	ret = tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
				      CXD2880_IO_TGT_DMD,
				      0xf0, ratectl_margin, 2);
	अगर (ret)
		वापस ret;

	अगर (tnr_dmd->भागer_mode == CXD2880_TNRDMD_DIVERMODE_MAIN ||
	    tnr_dmd->भागer_mode == CXD2880_TNRDMD_DIVERMODE_SUB) अणु
		ret = cxd2880_io_ग_लिखो_multi_regs(tnr_dmd->io,
						  CXD2880_IO_TGT_DMD,
						  tune_dmd_setting_seq3,
						  ARRAY_SIZE(tune_dmd_setting_seq3));
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (tnr_dmd->भागer_mode == CXD2880_TNRDMD_DIVERMODE_SUB) अणु
		ret = cxd2880_io_ग_लिखो_multi_regs(tnr_dmd->io,
						  CXD2880_IO_TGT_DMD,
						  tune_dmd_setting_seq4,
						  ARRAY_SIZE(tune_dmd_setting_seq4));
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (tnr_dmd->भागer_mode != CXD2880_TNRDMD_DIVERMODE_SUB) अणु
		ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
					     CXD2880_IO_TGT_DMD,
					     0x00, 0x04);
		अगर (ret)
			वापस ret;

		चयन (clk_mode) अणु
		हाल CXD2880_TNRDMD_CLOCKMODE_A:
			data = maxclkcnt_a;
			अवरोध;
		हाल CXD2880_TNRDMD_CLOCKMODE_B:
			data = maxclkcnt_b;
			अवरोध;
		हाल CXD2880_TNRDMD_CLOCKMODE_C:
			data = maxclkcnt_c;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		ret = tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
					      CXD2880_IO_TGT_DMD,
					      0x68, data, 3);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x04);
	अगर (ret)
		वापस ret;

	चयन (bandwidth) अणु
	हाल CXD2880_DTV_BW_8_MHZ:
		चयन (clk_mode) अणु
		हाल CXD2880_TNRDMD_CLOCKMODE_A:
		हाल CXD2880_TNRDMD_CLOCKMODE_C:
			data = bw8_nomi_ac;
			अवरोध;
		हाल CXD2880_TNRDMD_CLOCKMODE_B:
			data = bw8_nomi_b;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		ret = tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
					      CXD2880_IO_TGT_DMD,
					      0x60, data, 5);
		अगर (ret)
			वापस ret;

		ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
					     CXD2880_IO_TGT_DMD,
					     0x4a, 0x00);
		अगर (ret)
			वापस ret;

		चयन (clk_mode) अणु
		हाल CXD2880_TNRDMD_CLOCKMODE_A:
			data = bw8_gtकरोfst_a;
			अवरोध;
		हाल CXD2880_TNRDMD_CLOCKMODE_B:
			data = bw8_gtकरोfst_b;
			अवरोध;
		हाल CXD2880_TNRDMD_CLOCKMODE_C:
			data = bw8_gtकरोfst_c;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		ret = tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
					      CXD2880_IO_TGT_DMD,
					      0x7d, data, 2);
		अगर (ret)
			वापस ret;

		चयन (clk_mode) अणु
		हाल CXD2880_TNRDMD_CLOCKMODE_A:
		हाल CXD2880_TNRDMD_CLOCKMODE_B:
			sst_data = 0x35;
			अवरोध;
		हाल CXD2880_TNRDMD_CLOCKMODE_C:
			sst_data = 0x34;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
					     CXD2880_IO_TGT_DMD,
					     0x71, sst_data);
		अगर (ret)
			वापस ret;

		अगर (tnr_dmd->भागer_mode == CXD2880_TNRDMD_DIVERMODE_MAIN) अणु
			चयन (clk_mode) अणु
			हाल CXD2880_TNRDMD_CLOCKMODE_A:
				data = bw8_mrc_a;
				अवरोध;
			हाल CXD2880_TNRDMD_CLOCKMODE_B:
				data = bw8_mrc_b;
				अवरोध;
			हाल CXD2880_TNRDMD_CLOCKMODE_C:
				data = bw8_mrc_c;
				अवरोध;
			शेष:
				वापस -EINVAL;
			पूर्ण

			ret = tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
						      CXD2880_IO_TGT_DMD,
						      0x4b, &data[0], 2);
			अगर (ret)
				वापस ret;

			ret = tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
						      CXD2880_IO_TGT_DMD,
						      0x51, &data[2], 3);
			अगर (ret)
				वापस ret;
		पूर्ण

		ret = tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
					      CXD2880_IO_TGT_DMD,
					      0x72, &bw8_notch[0], 2);
		अगर (ret)
			वापस ret;

		ret = tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
					      CXD2880_IO_TGT_DMD,
					      0x6b, &bw8_notch[2], 2);
		अगर (ret)
			वापस ret;
		अवरोध;

	हाल CXD2880_DTV_BW_7_MHZ:
		चयन (clk_mode) अणु
		हाल CXD2880_TNRDMD_CLOCKMODE_A:
		हाल CXD2880_TNRDMD_CLOCKMODE_C:
			data = bw7_nomi_ac;
			अवरोध;
		हाल CXD2880_TNRDMD_CLOCKMODE_B:
			data = bw7_nomi_b;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		ret = tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
					      CXD2880_IO_TGT_DMD,
					      0x60, data, 5);
		अगर (ret)
			वापस ret;

		ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
					     CXD2880_IO_TGT_DMD,
					     0x4a, 0x02);
		अगर (ret)
			वापस ret;

		चयन (clk_mode) अणु
		हाल CXD2880_TNRDMD_CLOCKMODE_A:
			data = bw7_gtकरोfst_a;
			अवरोध;
		हाल CXD2880_TNRDMD_CLOCKMODE_B:
			data = bw7_gtकरोfst_b;
			अवरोध;
		हाल CXD2880_TNRDMD_CLOCKMODE_C:
			data = bw7_gtकरोfst_c;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		ret = tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
					      CXD2880_IO_TGT_DMD,
					      0x7d, data, 2);
		अगर (ret)
			वापस ret;

		चयन (clk_mode) अणु
		हाल CXD2880_TNRDMD_CLOCKMODE_A:
		हाल CXD2880_TNRDMD_CLOCKMODE_B:
			sst_data = 0x2f;
			अवरोध;
		हाल CXD2880_TNRDMD_CLOCKMODE_C:
			sst_data = 0x2e;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
					     CXD2880_IO_TGT_DMD,
					     0x71, sst_data);
		अगर (ret)
			वापस ret;

		अगर (tnr_dmd->भागer_mode == CXD2880_TNRDMD_DIVERMODE_MAIN) अणु
			चयन (clk_mode) अणु
			हाल CXD2880_TNRDMD_CLOCKMODE_A:
				data = bw7_mrc_a;
				अवरोध;
			हाल CXD2880_TNRDMD_CLOCKMODE_B:
				data = bw7_mrc_b;
				अवरोध;
			हाल CXD2880_TNRDMD_CLOCKMODE_C:
				data = bw7_mrc_c;
				अवरोध;
			शेष:
				वापस -EINVAL;
			पूर्ण

			ret = tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
						      CXD2880_IO_TGT_DMD,
						      0x4b, &data[0], 2);
			अगर (ret)
				वापस ret;

			ret = tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
						      CXD2880_IO_TGT_DMD,
						      0x51, &data[2], 3);
			अगर (ret)
				वापस ret;
		पूर्ण

		ret = tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
					      CXD2880_IO_TGT_DMD,
					      0x72, &bw7_notch[0], 2);
		अगर (ret)
			वापस ret;

		ret = tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
					      CXD2880_IO_TGT_DMD,
					      0x6b, &bw7_notch[2], 2);
		अगर (ret)
			वापस ret;
		अवरोध;

	हाल CXD2880_DTV_BW_6_MHZ:
		चयन (clk_mode) अणु
		हाल CXD2880_TNRDMD_CLOCKMODE_A:
		हाल CXD2880_TNRDMD_CLOCKMODE_C:
			data = bw6_nomi_ac;
			अवरोध;
		हाल CXD2880_TNRDMD_CLOCKMODE_B:
			data = bw6_nomi_b;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		ret = tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
					      CXD2880_IO_TGT_DMD,
					      0x60, data, 5);
		अगर (ret)
			वापस ret;

		ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
					     CXD2880_IO_TGT_DMD,
					     0x4a, 0x04);
		अगर (ret)
			वापस ret;

		चयन (clk_mode) अणु
		हाल CXD2880_TNRDMD_CLOCKMODE_A:
			data = bw6_gtकरोfst_a;
			अवरोध;
		हाल CXD2880_TNRDMD_CLOCKMODE_B:
			data = bw6_gtकरोfst_b;
			अवरोध;
		हाल CXD2880_TNRDMD_CLOCKMODE_C:
			data = bw6_gtकरोfst_c;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		ret = tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
					      CXD2880_IO_TGT_DMD,
					      0x7d, data, 2);
		अगर (ret)
			वापस ret;

		चयन (clk_mode) अणु
		हाल CXD2880_TNRDMD_CLOCKMODE_A:
		हाल CXD2880_TNRDMD_CLOCKMODE_C:
			sst_data = 0x29;
			अवरोध;
		हाल CXD2880_TNRDMD_CLOCKMODE_B:
			sst_data = 0x2a;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
					     CXD2880_IO_TGT_DMD,
					     0x71, sst_data);
		अगर (ret)
			वापस ret;

		अगर (tnr_dmd->भागer_mode == CXD2880_TNRDMD_DIVERMODE_MAIN) अणु
			चयन (clk_mode) अणु
			हाल CXD2880_TNRDMD_CLOCKMODE_A:
				data = bw6_mrc_a;
				अवरोध;
			हाल CXD2880_TNRDMD_CLOCKMODE_B:
				data = bw6_mrc_b;
				अवरोध;
			हाल CXD2880_TNRDMD_CLOCKMODE_C:
				data = bw6_mrc_c;
				अवरोध;
			शेष:
				वापस -EINVAL;
			पूर्ण

			ret = tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
						      CXD2880_IO_TGT_DMD,
						      0x4b, &data[0], 2);
			अगर (ret)
				वापस ret;

			ret = tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
						      CXD2880_IO_TGT_DMD,
						      0x51, &data[2], 3);
			अगर (ret)
				वापस ret;
		पूर्ण

		ret = tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
					      CXD2880_IO_TGT_DMD,
					      0x72, &bw6_notch[0], 2);
		अगर (ret)
			वापस ret;

		ret = tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
					      CXD2880_IO_TGT_DMD,
					      0x6b, &bw6_notch[2], 2);
		अगर (ret)
			वापस ret;
		अवरोध;

	हाल CXD2880_DTV_BW_5_MHZ:
		चयन (clk_mode) अणु
		हाल CXD2880_TNRDMD_CLOCKMODE_A:
		हाल CXD2880_TNRDMD_CLOCKMODE_C:
			data = bw5_nomi_ac;
			अवरोध;
		हाल CXD2880_TNRDMD_CLOCKMODE_B:
			data = bw5_nomi_b;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		ret = tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
					      CXD2880_IO_TGT_DMD,
					      0x60, data, 5);
		अगर (ret)
			वापस ret;

		ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
					     CXD2880_IO_TGT_DMD,
					     0x4a, 0x06);
		अगर (ret)
			वापस ret;

		चयन (clk_mode) अणु
		हाल CXD2880_TNRDMD_CLOCKMODE_A:
			data = bw5_gtकरोfst_a;
			अवरोध;
		हाल CXD2880_TNRDMD_CLOCKMODE_B:
			data = bw5_gtकरोfst_b;
			अवरोध;
		हाल CXD2880_TNRDMD_CLOCKMODE_C:
			data = bw5_gtकरोfst_c;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		ret = tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
					      CXD2880_IO_TGT_DMD,
					      0x7d, data, 2);
		अगर (ret)
			वापस ret;

		चयन (clk_mode) अणु
		हाल CXD2880_TNRDMD_CLOCKMODE_A:
		हाल CXD2880_TNRDMD_CLOCKMODE_B:
			sst_data = 0x24;
			अवरोध;
		हाल CXD2880_TNRDMD_CLOCKMODE_C:
			sst_data = 0x23;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
					     CXD2880_IO_TGT_DMD,
					     0x71, sst_data);
		अगर (ret)
			वापस ret;

		अगर (tnr_dmd->भागer_mode == CXD2880_TNRDMD_DIVERMODE_MAIN) अणु
			चयन (clk_mode) अणु
			हाल CXD2880_TNRDMD_CLOCKMODE_A:
				data = bw5_mrc_a;
				अवरोध;
			हाल CXD2880_TNRDMD_CLOCKMODE_B:
				data = bw5_mrc_b;
				अवरोध;
			हाल CXD2880_TNRDMD_CLOCKMODE_C:
				data = bw5_mrc_c;
				अवरोध;
			शेष:
				वापस -EINVAL;
			पूर्ण

			ret = tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
						      CXD2880_IO_TGT_DMD,
						      0x4b, &data[0], 2);
			अगर (ret)
				वापस ret;

			ret = tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
						      CXD2880_IO_TGT_DMD,
						      0x51, &data[2], 3);
			अगर (ret)
				वापस ret;
		पूर्ण

		ret = tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
					      CXD2880_IO_TGT_DMD,
					      0x72, &bw5_notch[0], 2);
		अगर (ret)
			वापस ret;

		ret = tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
					      CXD2880_IO_TGT_DMD,
					      0x6b, &bw5_notch[2], 2);
		अगर (ret)
			वापस ret;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस cxd2880_io_ग_लिखो_multi_regs(tnr_dmd->io,
					   CXD2880_IO_TGT_DMD,
					   tune_dmd_setting_seq5,
					   ARRAY_SIZE(tune_dmd_setting_seq5));
पूर्ण

अटल पूर्णांक x_sleep_dvbt_demod_setting(काष्ठा cxd2880_tnrdmd
						   *tnr_dmd)
अणु
	पूर्णांक ret;

	अगर (!tnr_dmd)
		वापस -EINVAL;

	ret = cxd2880_io_ग_लिखो_multi_regs(tnr_dmd->io,
					  CXD2880_IO_TGT_DMD,
					  sleep_dmd_setting_seq1,
					  ARRAY_SIZE(sleep_dmd_setting_seq1));
	अगर (ret)
		वापस ret;

	अगर (tnr_dmd->भागer_mode == CXD2880_TNRDMD_DIVERMODE_SUB)
		ret = cxd2880_io_ग_लिखो_multi_regs(tnr_dmd->io,
						  CXD2880_IO_TGT_DMD,
						  sleep_dmd_setting_seq2,
						  ARRAY_SIZE(sleep_dmd_setting_seq2));

	वापस ret;
पूर्ण

अटल पूर्णांक dvbt_set_profile(काष्ठा cxd2880_tnrdmd *tnr_dmd,
			    क्रमागत cxd2880_dvbt_profile profile)
अणु
	पूर्णांक ret;

	अगर (!tnr_dmd)
		वापस -EINVAL;

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x10);
	अगर (ret)
		वापस ret;

	वापस tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				      CXD2880_IO_TGT_DMD,
				      0x67,
				      (profile == CXD2880_DVBT_PROखाता_HP)
				      ? 0x00 : 0x01);
पूर्ण

पूर्णांक cxd2880_tnrdmd_dvbt_tune1(काष्ठा cxd2880_tnrdmd *tnr_dmd,
			      काष्ठा cxd2880_dvbt_tune_param
			      *tune_param)
अणु
	पूर्णांक ret;

	अगर (!tnr_dmd || !tune_param)
		वापस -EINVAL;

	अगर (tnr_dmd->भागer_mode == CXD2880_TNRDMD_DIVERMODE_SUB)
		वापस -EINVAL;

	अगर (tnr_dmd->state != CXD2880_TNRDMD_STATE_SLEEP &&
	    tnr_dmd->state != CXD2880_TNRDMD_STATE_ACTIVE)
		वापस -EINVAL;

	ret =
	    cxd2880_tnrdmd_common_tune_setting1(tnr_dmd, CXD2880_DTV_SYS_DVBT,
						tune_param->center_freq_khz,
						tune_param->bandwidth, 0, 0);
	अगर (ret)
		वापस ret;

	ret =
	    x_tune_dvbt_demod_setting(tnr_dmd, tune_param->bandwidth,
				      tnr_dmd->clk_mode);
	अगर (ret)
		वापस ret;

	अगर (tnr_dmd->भागer_mode == CXD2880_TNRDMD_DIVERMODE_MAIN) अणु
		ret =
		    x_tune_dvbt_demod_setting(tnr_dmd->भागer_sub,
					      tune_param->bandwidth,
					      tnr_dmd->भागer_sub->clk_mode);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस dvbt_set_profile(tnr_dmd, tune_param->profile);
पूर्ण

पूर्णांक cxd2880_tnrdmd_dvbt_tune2(काष्ठा cxd2880_tnrdmd *tnr_dmd,
			      काष्ठा cxd2880_dvbt_tune_param
			      *tune_param)
अणु
	पूर्णांक ret;

	अगर (!tnr_dmd || !tune_param)
		वापस -EINVAL;

	अगर (tnr_dmd->भागer_mode == CXD2880_TNRDMD_DIVERMODE_SUB)
		वापस -EINVAL;

	अगर (tnr_dmd->state != CXD2880_TNRDMD_STATE_SLEEP &&
	    tnr_dmd->state != CXD2880_TNRDMD_STATE_ACTIVE)
		वापस -EINVAL;

	ret =
	    cxd2880_tnrdmd_common_tune_setting2(tnr_dmd, CXD2880_DTV_SYS_DVBT,
						0);
	अगर (ret)
		वापस ret;

	tnr_dmd->state = CXD2880_TNRDMD_STATE_ACTIVE;
	tnr_dmd->frequency_khz = tune_param->center_freq_khz;
	tnr_dmd->sys = CXD2880_DTV_SYS_DVBT;
	tnr_dmd->bandwidth = tune_param->bandwidth;

	अगर (tnr_dmd->भागer_mode == CXD2880_TNRDMD_DIVERMODE_MAIN) अणु
		tnr_dmd->भागer_sub->state = CXD2880_TNRDMD_STATE_ACTIVE;
		tnr_dmd->भागer_sub->frequency_khz = tune_param->center_freq_khz;
		tnr_dmd->भागer_sub->sys = CXD2880_DTV_SYS_DVBT;
		tnr_dmd->भागer_sub->bandwidth = tune_param->bandwidth;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक cxd2880_tnrdmd_dvbt_sleep_setting(काष्ठा cxd2880_tnrdmd *tnr_dmd)
अणु
	पूर्णांक ret;

	अगर (!tnr_dmd)
		वापस -EINVAL;

	अगर (tnr_dmd->भागer_mode == CXD2880_TNRDMD_DIVERMODE_SUB)
		वापस -EINVAL;

	अगर (tnr_dmd->state != CXD2880_TNRDMD_STATE_SLEEP &&
	    tnr_dmd->state != CXD2880_TNRDMD_STATE_ACTIVE)
		वापस -EINVAL;

	ret = x_sleep_dvbt_demod_setting(tnr_dmd);
	अगर (ret)
		वापस ret;

	अगर (tnr_dmd->भागer_mode == CXD2880_TNRDMD_DIVERMODE_MAIN)
		ret = x_sleep_dvbt_demod_setting(tnr_dmd->भागer_sub);

	वापस ret;
पूर्ण

पूर्णांक cxd2880_tnrdmd_dvbt_check_demod_lock(काष्ठा cxd2880_tnrdmd
					 *tnr_dmd,
					 क्रमागत
					 cxd2880_tnrdmd_lock_result
					 *lock)
अणु
	पूर्णांक ret;

	u8 sync_stat = 0;
	u8 ts_lock = 0;
	u8 unlock_detected = 0;
	u8 unlock_detected_sub = 0;

	अगर (!tnr_dmd || !lock)
		वापस -EINVAL;

	अगर (tnr_dmd->भागer_mode == CXD2880_TNRDMD_DIVERMODE_SUB)
		वापस -EINVAL;

	अगर (tnr_dmd->state != CXD2880_TNRDMD_STATE_ACTIVE)
		वापस -EINVAL;

	ret =
	    cxd2880_tnrdmd_dvbt_mon_sync_stat(tnr_dmd, &sync_stat, &ts_lock,
					      &unlock_detected);
	अगर (ret)
		वापस ret;

	अगर (tnr_dmd->भागer_mode == CXD2880_TNRDMD_DIVERMODE_SINGLE) अणु
		अगर (sync_stat == 6)
			*lock = CXD2880_TNRDMD_LOCK_RESULT_LOCKED;
		अन्यथा अगर (unlock_detected)
			*lock = CXD2880_TNRDMD_LOCK_RESULT_UNLOCKED;
		अन्यथा
			*lock = CXD2880_TNRDMD_LOCK_RESULT_NOTDETECT;

		वापस ret;
	पूर्ण

	अगर (sync_stat == 6) अणु
		*lock = CXD2880_TNRDMD_LOCK_RESULT_LOCKED;
		वापस ret;
	पूर्ण

	ret =
	    cxd2880_tnrdmd_dvbt_mon_sync_stat_sub(tnr_dmd, &sync_stat,
						  &unlock_detected_sub);
	अगर (ret)
		वापस ret;

	अगर (sync_stat == 6)
		*lock = CXD2880_TNRDMD_LOCK_RESULT_LOCKED;
	अन्यथा अगर (unlock_detected && unlock_detected_sub)
		*lock = CXD2880_TNRDMD_LOCK_RESULT_UNLOCKED;
	अन्यथा
		*lock = CXD2880_TNRDMD_LOCK_RESULT_NOTDETECT;

	वापस ret;
पूर्ण

पूर्णांक cxd2880_tnrdmd_dvbt_check_ts_lock(काष्ठा cxd2880_tnrdmd
				      *tnr_dmd,
				      क्रमागत
				      cxd2880_tnrdmd_lock_result
				      *lock)
अणु
	पूर्णांक ret;

	u8 sync_stat = 0;
	u8 ts_lock = 0;
	u8 unlock_detected = 0;
	u8 unlock_detected_sub = 0;

	अगर (!tnr_dmd || !lock)
		वापस -EINVAL;

	अगर (tnr_dmd->भागer_mode == CXD2880_TNRDMD_DIVERMODE_SUB)
		वापस -EINVAL;

	अगर (tnr_dmd->state != CXD2880_TNRDMD_STATE_ACTIVE)
		वापस -EINVAL;

	ret =
	    cxd2880_tnrdmd_dvbt_mon_sync_stat(tnr_dmd, &sync_stat, &ts_lock,
					      &unlock_detected);
	अगर (ret)
		वापस ret;

	अगर (tnr_dmd->भागer_mode == CXD2880_TNRDMD_DIVERMODE_SINGLE) अणु
		अगर (ts_lock)
			*lock = CXD2880_TNRDMD_LOCK_RESULT_LOCKED;
		अन्यथा अगर (unlock_detected)
			*lock = CXD2880_TNRDMD_LOCK_RESULT_UNLOCKED;
		अन्यथा
			*lock = CXD2880_TNRDMD_LOCK_RESULT_NOTDETECT;

		वापस ret;
	पूर्ण

	अगर (ts_lock) अणु
		*lock = CXD2880_TNRDMD_LOCK_RESULT_LOCKED;
		वापस ret;
	पूर्ण अन्यथा अगर (!unlock_detected) अणु
		*lock = CXD2880_TNRDMD_LOCK_RESULT_NOTDETECT;
		वापस ret;
	पूर्ण

	ret =
	    cxd2880_tnrdmd_dvbt_mon_sync_stat_sub(tnr_dmd, &sync_stat,
						  &unlock_detected_sub);
	अगर (ret)
		वापस ret;

	अगर (unlock_detected && unlock_detected_sub)
		*lock = CXD2880_TNRDMD_LOCK_RESULT_UNLOCKED;
	अन्यथा
		*lock = CXD2880_TNRDMD_LOCK_RESULT_NOTDETECT;

	वापस ret;
पूर्ण
