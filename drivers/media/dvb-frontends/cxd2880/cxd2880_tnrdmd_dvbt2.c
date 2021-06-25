<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * cxd2880_tnrdmd_dvbt2.c
 * Sony CXD2880 DVB-T2/T tuner + demodulator driver
 * control functions क्रम DVB-T2
 *
 * Copyright (C) 2016, 2017, 2018 Sony Semiconductor Solutions Corporation
 */

#समावेश <media/dvb_frontend.h>

#समावेश "cxd2880_tnrdmd_dvbt2.h"
#समावेश "cxd2880_tnrdmd_dvbt2_mon.h"

अटल स्थिर काष्ठा cxd2880_reg_value tune_dmd_setting_seq1[] = अणु
	अणु0x00, 0x00पूर्ण, अणु0x31, 0x02पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा cxd2880_reg_value tune_dmd_setting_seq2[] = अणु
	अणु0x00, 0x04पूर्ण, अणु0x5d, 0x0bपूर्ण,
पूर्ण;

अटल पूर्णांक x_tune_dvbt2_demod_setting(काष्ठा cxd2880_tnrdmd
				      *tnr_dmd,
				      क्रमागत cxd2880_dtv_bandwidth
				      bandwidth,
				      क्रमागत cxd2880_tnrdmd_घड़ीmode
				      clk_mode)
अणु
	अटल स्थिर u8 tsअगर_settings[2] = अणु 0x01, 0x01 पूर्ण;
	अटल स्थिर u8 init_settings[14] = अणु
		0x07, 0x06, 0x01, 0xf0,	0x00, 0x00, 0x04, 0xb0, 0x00, 0x00,
		0x09, 0x9c, 0x0e, 0x4c
	पूर्ण;
	अटल स्थिर u8 clk_mode_settings_a1[9] = अणु
		0x52, 0x49, 0x2c, 0x51,	0x51, 0x3d, 0x15, 0x29, 0x0c
	पूर्ण;

	अटल स्थिर u8 clk_mode_settings_b1[9] = अणु
		0x5d, 0x55, 0x32, 0x5c,	0x5c, 0x45, 0x17, 0x2e, 0x0d
	पूर्ण;

	अटल स्थिर u8 clk_mode_settings_c1[9] = अणु
		0x60, 0x00, 0x34, 0x5e,	0x5e, 0x47, 0x18, 0x2f, 0x0e
	पूर्ण;

	अटल स्थिर u8 clk_mode_settings_a2[13] = अणु
		0x04, 0xe7, 0x94, 0x92,	0x09, 0xcf, 0x7e, 0xd0, 0x49,
		0xcd, 0xcd, 0x1f, 0x5b
	पूर्ण;

	अटल स्थिर u8 clk_mode_settings_b2[13] = अणु
		0x05, 0x90, 0x27, 0x55,	0x0b, 0x20, 0x8f, 0xd6, 0xea,
		0xc8, 0xc8, 0x23, 0x91
	पूर्ण;

	अटल स्थिर u8 clk_mode_settings_c2[13] = अणु
		0x05, 0xb8, 0xd8, 0x00,	0x0b, 0x72, 0x93, 0xf3, 0x00,
		0xcd, 0xcd, 0x24, 0x95
	पूर्ण;

	अटल स्थिर u8 clk_mode_settings_a3[5] = अणु
		0x0b, 0x6a, 0xc9, 0x03, 0x33
	पूर्ण;
	अटल स्थिर u8 clk_mode_settings_b3[5] = अणु
		0x01, 0x02, 0xe4, 0x03, 0x39
	पूर्ण;
	अटल स्थिर u8 clk_mode_settings_c3[5] = अणु
		0x01, 0x02, 0xeb, 0x03, 0x3b
	पूर्ण;

	अटल स्थिर u8 gtकरोfst[2] = अणु 0x3f, 0xff पूर्ण;

	अटल स्थिर u8 bw8_gtकरोfst_a[2] = अणु 0x19, 0xd2 पूर्ण;
	अटल स्थिर u8 bw8_nomi_ac[6] = अणु 0x15, 0x00, 0x00, 0x00, 0x00, 0x00 पूर्ण;
	अटल स्थिर u8 bw8_nomi_b[6] = अणु 0x14, 0x6a, 0xaa, 0xaa, 0xab, 0x00 पूर्ण;
	अटल स्थिर u8 bw8_sst_a[2] = अणु 0x06, 0x2a पूर्ण;
	अटल स्थिर u8 bw8_sst_b[2] = अणु 0x06, 0x29 पूर्ण;
	अटल स्थिर u8 bw8_sst_c[2] = अणु 0x06, 0x28 पूर्ण;
	अटल स्थिर u8 bw8_mrc_a[9] = अणु
		0x28, 0x00, 0x50, 0x00, 0x60, 0x00, 0x00, 0x90, 0x00
	पूर्ण;
	अटल स्थिर u8 bw8_mrc_b[9] = अणु
		0x2d, 0x5e, 0x5a, 0xbd, 0x6c, 0xe3, 0x00, 0xa3, 0x55
	पूर्ण;
	अटल स्थिर u8 bw8_mrc_c[9] = अणु
		0x2e, 0xaa, 0x5d, 0x55, 0x70, 0x00, 0x00, 0xa8, 0x00
	पूर्ण;

	अटल स्थिर u8 bw7_nomi_ac[6] = अणु 0x18, 0x00, 0x00, 0x00, 0x00, 0x00 पूर्ण;
	अटल स्थिर u8 bw7_nomi_b[6] = अणु 0x17, 0x55, 0x55, 0x55, 0x55, 0x00 पूर्ण;
	अटल स्थिर u8 bw7_sst_a[2] = अणु 0x06, 0x23 पूर्ण;
	अटल स्थिर u8 bw7_sst_b[2] = अणु 0x06, 0x22 पूर्ण;
	अटल स्थिर u8 bw7_sst_c[2] = अणु 0x06, 0x21 पूर्ण;
	अटल स्थिर u8 bw7_mrc_a[9] = अणु
		0x2d, 0xb6, 0x5b, 0x6d,	0x6d, 0xb6, 0x00, 0xa4, 0x92
	पूर्ण;
	अटल स्थिर u8 bw7_mrc_b[9] = अणु
		0x33, 0xda, 0x67, 0xb4,	0x7c, 0x71, 0x00, 0xba, 0xaa
	पूर्ण;
	अटल स्थिर u8 bw7_mrc_c[9] = अणु
		0x35, 0x55, 0x6a, 0xaa,	0x80, 0x00, 0x00, 0xc0, 0x00
	पूर्ण;

	अटल स्थिर u8 bw6_nomi_ac[6] = अणु 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00 पूर्ण;
	अटल स्थिर u8 bw6_nomi_b[6] = अणु 0x1b, 0x38, 0xe3, 0x8e, 0x39, 0x00 पूर्ण;
	अटल स्थिर u8 bw6_sst_a[2] = अणु 0x06, 0x1c पूर्ण;
	अटल स्थिर u8 bw6_sst_b[2] = अणु 0x06, 0x1b पूर्ण;
	अटल स्थिर u8 bw6_sst_c[2] = अणु 0x06, 0x1a पूर्ण;
	अटल स्थिर u8 bw6_mrc_a[9] = अणु
		0x35, 0x55, 0x6a, 0xaa, 0x80, 0x00, 0x00, 0xc0, 0x00
	पूर्ण;
	अटल स्थिर u8 bw6_mrc_b[9] = अणु
		0x3c, 0x7e, 0x78, 0xfc,	0x91, 0x2f, 0x00, 0xd9, 0xc7
	पूर्ण;
	अटल स्थिर u8 bw6_mrc_c[9] = अणु
		0x3e, 0x38, 0x7c, 0x71,	0x95, 0x55, 0x00, 0xdf, 0xff
	पूर्ण;

	अटल स्थिर u8 bw5_nomi_ac[6] = अणु 0x21, 0x99, 0x99, 0x99, 0x9a, 0x00 पूर्ण;
	अटल स्थिर u8 bw5_nomi_b[6] = अणु 0x20, 0xaa, 0xaa, 0xaa, 0xab, 0x00 पूर्ण;
	अटल स्थिर u8 bw5_sst_a[2] = अणु 0x06, 0x15 पूर्ण;
	अटल स्थिर u8 bw5_sst_b[2] = अणु 0x06, 0x15 पूर्ण;
	अटल स्थिर u8 bw5_sst_c[2] = अणु 0x06, 0x14 पूर्ण;
	अटल स्थिर u8 bw5_mrc_a[9] = अणु
		0x40, 0x00, 0x6a, 0xaa, 0x80, 0x00, 0x00, 0xe6, 0x66
	पूर्ण;
	अटल स्थिर u8 bw5_mrc_b[9] = अणु
		0x48, 0x97, 0x78, 0xfc, 0x91, 0x2f, 0x01, 0x05, 0x55
	पूर्ण;
	अटल स्थिर u8 bw5_mrc_c[9] = अणु
		0x4a, 0xaa, 0x7c, 0x71, 0x95, 0x55, 0x01, 0x0c, 0xcc
	पूर्ण;

	अटल स्थिर u8 bw1_7_nomi_a[6] = अणु
		0x68, 0x0f, 0xa2, 0x32, 0xcf, 0x03
	पूर्ण;
	अटल स्थिर u8 bw1_7_nomi_c[6] = अणु
		0x68, 0x0f, 0xa2, 0x32, 0xcf, 0x03
	पूर्ण;
	अटल स्थिर u8 bw1_7_nomi_b[6] = अणु
		0x65, 0x2b, 0xa4, 0xcd, 0xd8, 0x03
	पूर्ण;
	अटल स्थिर u8 bw1_7_sst_a[2] = अणु 0x06, 0x0c पूर्ण;
	अटल स्थिर u8 bw1_7_sst_b[2] = अणु 0x06, 0x0c पूर्ण;
	अटल स्थिर u8 bw1_7_sst_c[2] = अणु 0x06, 0x0b पूर्ण;
	अटल स्थिर u8 bw1_7_mrc_a[9] = अणु
		0x40, 0x00, 0x6a, 0xaa,	0x80, 0x00, 0x02, 0xc9, 0x8f
	पूर्ण;
	अटल स्थिर u8 bw1_7_mrc_b[9] = अणु
		0x48, 0x97, 0x78, 0xfc, 0x91, 0x2f, 0x03, 0x29, 0x5d
	पूर्ण;
	अटल स्थिर u8 bw1_7_mrc_c[9] = अणु
		0x4a, 0xaa, 0x7c, 0x71,	0x95, 0x55, 0x03, 0x40, 0x7d
	पूर्ण;

	स्थिर u8 *data = शून्य;
	स्थिर u8 *data2 = शून्य;
	स्थिर u8 *data3 = शून्य;
	पूर्णांक ret;

	अगर (!tnr_dmd)
		वापस -EINVAL;

	ret = cxd2880_io_ग_लिखो_multi_regs(tnr_dmd->io,
					  CXD2880_IO_TGT_SYS,
					  tune_dmd_setting_seq1,
					  ARRAY_SIZE(tune_dmd_setting_seq1));
	अगर (ret)
		वापस ret;

	ret = cxd2880_io_ग_लिखो_multi_regs(tnr_dmd->io,
					  CXD2880_IO_TGT_DMD,
					  tune_dmd_setting_seq2,
					  ARRAY_SIZE(tune_dmd_setting_seq2));
	अगर (ret)
		वापस ret;

	अगर (tnr_dmd->भागer_mode != CXD2880_TNRDMD_DIVERMODE_SUB) अणु
		ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
					     CXD2880_IO_TGT_DMD,
					     0x00, 0x00);
		अगर (ret)
			वापस ret;

		ret = tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
					      CXD2880_IO_TGT_DMD,
					      0xce, tsअगर_settings, 2);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x20);
	अगर (ret)
		वापस ret;

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x8a, init_settings[0]);
	अगर (ret)
		वापस ret;

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x90, init_settings[1]);
	अगर (ret)
		वापस ret;

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x25);
	अगर (ret)
		वापस ret;

	ret = tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
				      CXD2880_IO_TGT_DMD,
				      0xf0, &init_settings[2], 2);
	अगर (ret)
		वापस ret;

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x2a);
	अगर (ret)
		वापस ret;

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0xdc, init_settings[4]);
	अगर (ret)
		वापस ret;

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0xde, init_settings[5]);
	अगर (ret)
		वापस ret;

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x2d);
	अगर (ret)
		वापस ret;

	ret = tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
				      CXD2880_IO_TGT_DMD,
				      0x73, &init_settings[6], 4);
	अगर (ret)
		वापस ret;

	ret = tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
				      CXD2880_IO_TGT_DMD,
				      0x8f, &init_settings[10], 4);
	अगर (ret)
		वापस ret;

	चयन (clk_mode) अणु
	हाल CXD2880_TNRDMD_CLOCKMODE_A:
		data = clk_mode_settings_a1;
		data2 = clk_mode_settings_a2;
		data3 = clk_mode_settings_a3;
		अवरोध;
	हाल CXD2880_TNRDMD_CLOCKMODE_B:
		data = clk_mode_settings_b1;
		data2 = clk_mode_settings_b2;
		data3 = clk_mode_settings_b3;
		अवरोध;
	हाल CXD2880_TNRDMD_CLOCKMODE_C:
		data = clk_mode_settings_c1;
		data2 = clk_mode_settings_c2;
		data3 = clk_mode_settings_c3;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x04);
	अगर (ret)
		वापस ret;

	ret = tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
				      CXD2880_IO_TGT_DMD,
				      0x1d, &data[0], 3);
	अगर (ret)
		वापस ret;

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x22, data[3]);
	अगर (ret)
		वापस ret;

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x24, data[4]);
	अगर (ret)
		वापस ret;

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x26, data[5]);
	अगर (ret)
		वापस ret;

	ret = tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
				      CXD2880_IO_TGT_DMD,
				      0x29, &data[6], 2);
	अगर (ret)
		वापस ret;

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x2d, data[8]);
	अगर (ret)
		वापस ret;

	अगर (tnr_dmd->भागer_mode != CXD2880_TNRDMD_DIVERMODE_SUB) अणु
		ret = tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
					      CXD2880_IO_TGT_DMD,
					      0x2e, &data2[0], 6);
		अगर (ret)
			वापस ret;

		ret = tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
					      CXD2880_IO_TGT_DMD,
					      0x35, &data2[6], 7);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
				      CXD2880_IO_TGT_DMD,
				      0x3c, &data3[0], 2);
	अगर (ret)
		वापस ret;

	ret = tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
				      CXD2880_IO_TGT_DMD,
				      0x56, &data3[2], 3);
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
					      0x10, data, 6);
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
		हाल CXD2880_TNRDMD_CLOCKMODE_C:
			data = gtकरोfst;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		ret = tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
					      CXD2880_IO_TGT_DMD,
					      0x19, data, 2);
		अगर (ret)
			वापस ret;

		चयन (clk_mode) अणु
		हाल CXD2880_TNRDMD_CLOCKMODE_A:
			data = bw8_sst_a;
			अवरोध;
		हाल CXD2880_TNRDMD_CLOCKMODE_B:
			data = bw8_sst_b;
			अवरोध;
		हाल CXD2880_TNRDMD_CLOCKMODE_C:
			data = bw8_sst_c;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		ret = tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
					      CXD2880_IO_TGT_DMD,
					      0x1b, data, 2);
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
						      0x4b, data, 9);
			अगर (ret)
				वापस ret;
		पूर्ण
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
					      0x10, data, 6);
		अगर (ret)
			वापस ret;

		ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
					     CXD2880_IO_TGT_DMD,
					     0x4a, 0x02);
		अगर (ret)
			वापस ret;

		ret = tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
					      CXD2880_IO_TGT_DMD,
					      0x19, gtकरोfst, 2);
		अगर (ret)
			वापस ret;

		चयन (clk_mode) अणु
		हाल CXD2880_TNRDMD_CLOCKMODE_A:
			data = bw7_sst_a;
			अवरोध;
		हाल CXD2880_TNRDMD_CLOCKMODE_B:
			data = bw7_sst_b;
			अवरोध;
		हाल CXD2880_TNRDMD_CLOCKMODE_C:
			data = bw7_sst_c;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		ret = tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
					      CXD2880_IO_TGT_DMD,
					      0x1b, data, 2);
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
						      0x4b, data, 9);
			अगर (ret)
				वापस ret;
		पूर्ण
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
					      0x10, data, 6);
		अगर (ret)
			वापस ret;

		ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
					     CXD2880_IO_TGT_DMD,
					     0x4a, 0x04);
		अगर (ret)
			वापस ret;

		ret = tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
					      CXD2880_IO_TGT_DMD,
					      0x19, gtकरोfst, 2);
		अगर (ret)
			वापस ret;

		चयन (clk_mode) अणु
		हाल CXD2880_TNRDMD_CLOCKMODE_A:
			data = bw6_sst_a;
			अवरोध;
		हाल CXD2880_TNRDMD_CLOCKMODE_B:
			data = bw6_sst_b;
			अवरोध;
		हाल CXD2880_TNRDMD_CLOCKMODE_C:
			data = bw6_sst_c;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		ret = tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
					      CXD2880_IO_TGT_DMD,
					      0x1b, data, 2);
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
						      0x4b, data, 9);
			अगर (ret)
				वापस ret;
		पूर्ण
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
					      0x10, data, 6);
		अगर (ret)
			वापस ret;

		ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
					     CXD2880_IO_TGT_DMD,
					     0x4a, 0x06);
		अगर (ret)
			वापस ret;

		ret = tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
					      CXD2880_IO_TGT_DMD,
					      0x19, gtकरोfst, 2);
		अगर (ret)
			वापस ret;

		चयन (clk_mode) अणु
		हाल CXD2880_TNRDMD_CLOCKMODE_A:
			data = bw5_sst_a;
			अवरोध;
		हाल CXD2880_TNRDMD_CLOCKMODE_B:
			data = bw5_sst_b;
			अवरोध;
		हाल CXD2880_TNRDMD_CLOCKMODE_C:
			data = bw5_sst_c;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		ret = tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
					      CXD2880_IO_TGT_DMD,
					      0x1b, data, 2);
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
						      0x4b, data, 9);
			अगर (ret)
				वापस ret;
		पूर्ण
		अवरोध;

	हाल CXD2880_DTV_BW_1_7_MHZ:

		चयन (clk_mode) अणु
		हाल CXD2880_TNRDMD_CLOCKMODE_A:
			data = bw1_7_nomi_a;
			अवरोध;
		हाल CXD2880_TNRDMD_CLOCKMODE_C:
			data = bw1_7_nomi_c;
			अवरोध;
		हाल CXD2880_TNRDMD_CLOCKMODE_B:
			data = bw1_7_nomi_b;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		ret = tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
					      CXD2880_IO_TGT_DMD,
					      0x10, data, 6);
		अगर (ret)
			वापस ret;

		ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
					     CXD2880_IO_TGT_DMD,
					     0x4a, 0x03);
		अगर (ret)
			वापस ret;

		ret = tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
					      CXD2880_IO_TGT_DMD,
					      0x19, gtकरोfst, 2);
		अगर (ret)
			वापस ret;

		चयन (clk_mode) अणु
		हाल CXD2880_TNRDMD_CLOCKMODE_A:
			data = bw1_7_sst_a;
			अवरोध;
		हाल CXD2880_TNRDMD_CLOCKMODE_B:
			data = bw1_7_sst_b;
			अवरोध;
		हाल CXD2880_TNRDMD_CLOCKMODE_C:
			data = bw1_7_sst_c;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		ret = tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
					      CXD2880_IO_TGT_DMD,
					      0x1b, data, 2);
		अगर (ret)
			वापस ret;

		अगर (tnr_dmd->भागer_mode == CXD2880_TNRDMD_DIVERMODE_MAIN) अणु
			चयन (clk_mode) अणु
			हाल CXD2880_TNRDMD_CLOCKMODE_A:
				data = bw1_7_mrc_a;
				अवरोध;
			हाल CXD2880_TNRDMD_CLOCKMODE_B:
				data = bw1_7_mrc_b;
				अवरोध;
			हाल CXD2880_TNRDMD_CLOCKMODE_C:
				data = bw1_7_mrc_c;
				अवरोध;
			शेष:
				वापस -EINVAL;
			पूर्ण

			ret = tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
						      CXD2880_IO_TGT_DMD,
						      0x4b, data, 9);
			अगर (ret)
				वापस ret;
		पूर्ण
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x00);
	अगर (ret)
		वापस ret;

	वापस tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				      CXD2880_IO_TGT_DMD,
				      0xfd, 0x01);
पूर्ण

अटल पूर्णांक x_sleep_dvbt2_demod_setting(काष्ठा cxd2880_tnrdmd
				       *tnr_dmd)
अणु
	अटल स्थिर u8 dअगरपूर्णांक_clip[] = अणु
		0, 1, 0, 2, 0, 4, 0, 8, 0, 16, 0, 32
	पूर्ण;
	पूर्णांक ret = 0;

	अगर (!tnr_dmd)
		वापस -EINVAL;

	अगर (tnr_dmd->भागer_mode == CXD2880_TNRDMD_DIVERMODE_MAIN) अणु
		ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
					     CXD2880_IO_TGT_DMD,
					     0x00, 0x1d);
		अगर (ret)
			वापस ret;

		ret = tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
					      CXD2880_IO_TGT_DMD,
					      0x47, dअगरपूर्णांक_clip, 12);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक dvbt2_set_profile(काष्ठा cxd2880_tnrdmd *tnr_dmd,
			     क्रमागत cxd2880_dvbt2_profile profile)
अणु
	u8 t2_mode_tune_mode = 0;
	u8 seq_not2_dसमय = 0;
	u8 dसमय1 = 0;
	u8 dसमय2 = 0;
	पूर्णांक ret;

	अगर (!tnr_dmd)
		वापस -EINVAL;

	चयन (tnr_dmd->clk_mode) अणु
	हाल CXD2880_TNRDMD_CLOCKMODE_A:
		dसमय1 = 0x27;
		dसमय2 = 0x0c;
		अवरोध;
	हाल CXD2880_TNRDMD_CLOCKMODE_B:
		dसमय1 = 0x2c;
		dसमय2 = 0x0d;
		अवरोध;
	हाल CXD2880_TNRDMD_CLOCKMODE_C:
		dसमय1 = 0x2e;
		dसमय2 = 0x0e;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (profile) अणु
	हाल CXD2880_DVBT2_PROखाता_BASE:
		t2_mode_tune_mode = 0x01;
		seq_not2_dसमय = dसमय2;
		अवरोध;

	हाल CXD2880_DVBT2_PROखाता_LITE:
		t2_mode_tune_mode = 0x05;
		seq_not2_dसमय = dसमय1;
		अवरोध;

	हाल CXD2880_DVBT2_PROखाता_ANY:
		t2_mode_tune_mode = 0x00;
		seq_not2_dसमय = dसमय1;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x2e);
	अगर (ret)
		वापस ret;

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x10, t2_mode_tune_mode);
	अगर (ret)
		वापस ret;

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x04);
	अगर (ret)
		वापस ret;

	वापस tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				      CXD2880_IO_TGT_DMD,
				      0x2c, seq_not2_dसमय);
पूर्ण

पूर्णांक cxd2880_tnrdmd_dvbt2_tune1(काष्ठा cxd2880_tnrdmd *tnr_dmd,
			       काष्ठा cxd2880_dvbt2_tune_param
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

	अगर (tnr_dmd->भागer_mode == CXD2880_TNRDMD_DIVERMODE_MAIN &&
	    tune_param->profile == CXD2880_DVBT2_PROखाता_ANY)
		वापस -ENOTTY;

	ret =
	    cxd2880_tnrdmd_common_tune_setting1(tnr_dmd, CXD2880_DTV_SYS_DVBT2,
						tune_param->center_freq_khz,
						tune_param->bandwidth, 0, 0);
	अगर (ret)
		वापस ret;

	ret =
	    x_tune_dvbt2_demod_setting(tnr_dmd, tune_param->bandwidth,
				       tnr_dmd->clk_mode);
	अगर (ret)
		वापस ret;

	अगर (tnr_dmd->भागer_mode == CXD2880_TNRDMD_DIVERMODE_MAIN) अणु
		ret =
		    x_tune_dvbt2_demod_setting(tnr_dmd->भागer_sub,
					       tune_param->bandwidth,
					       tnr_dmd->भागer_sub->clk_mode);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = dvbt2_set_profile(tnr_dmd, tune_param->profile);
	अगर (ret)
		वापस ret;

	अगर (tnr_dmd->भागer_mode == CXD2880_TNRDMD_DIVERMODE_MAIN) अणु
		ret =
		    dvbt2_set_profile(tnr_dmd->भागer_sub, tune_param->profile);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (tune_param->data_plp_id == CXD2880_DVBT2_TUNE_PARAM_PLPID_AUTO)
		ret = cxd2880_tnrdmd_dvbt2_set_plp_cfg(tnr_dmd, 1, 0);
	अन्यथा
		ret =
		    cxd2880_tnrdmd_dvbt2_set_plp_cfg(tnr_dmd, 0,
					     (u8)(tune_param->data_plp_id));

	वापस ret;
पूर्ण

पूर्णांक cxd2880_tnrdmd_dvbt2_tune2(काष्ठा cxd2880_tnrdmd *tnr_dmd,
			       काष्ठा cxd2880_dvbt2_tune_param
			       *tune_param)
अणु
	u8 en_fef_पूर्णांकmtnt_ctrl = 1;
	पूर्णांक ret;

	अगर (!tnr_dmd || !tune_param)
		वापस -EINVAL;

	अगर (tnr_dmd->भागer_mode == CXD2880_TNRDMD_DIVERMODE_SUB)
		वापस -EINVAL;

	अगर (tnr_dmd->state != CXD2880_TNRDMD_STATE_SLEEP &&
	    tnr_dmd->state != CXD2880_TNRDMD_STATE_ACTIVE)
		वापस -EINVAL;

	चयन (tune_param->profile) अणु
	हाल CXD2880_DVBT2_PROखाता_BASE:
		en_fef_पूर्णांकmtnt_ctrl = tnr_dmd->en_fef_पूर्णांकmtnt_base;
		अवरोध;
	हाल CXD2880_DVBT2_PROखाता_LITE:
		en_fef_पूर्णांकmtnt_ctrl = tnr_dmd->en_fef_पूर्णांकmtnt_lite;
		अवरोध;
	हाल CXD2880_DVBT2_PROखाता_ANY:
		अगर (tnr_dmd->en_fef_पूर्णांकmtnt_base &&
		    tnr_dmd->en_fef_पूर्णांकmtnt_lite)
			en_fef_पूर्णांकmtnt_ctrl = 1;
		अन्यथा
			en_fef_पूर्णांकmtnt_ctrl = 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ret =
	    cxd2880_tnrdmd_common_tune_setting2(tnr_dmd,
						CXD2880_DTV_SYS_DVBT2,
						en_fef_पूर्णांकmtnt_ctrl);
	अगर (ret)
		वापस ret;

	tnr_dmd->state = CXD2880_TNRDMD_STATE_ACTIVE;
	tnr_dmd->frequency_khz = tune_param->center_freq_khz;
	tnr_dmd->sys = CXD2880_DTV_SYS_DVBT2;
	tnr_dmd->bandwidth = tune_param->bandwidth;

	अगर (tnr_dmd->भागer_mode == CXD2880_TNRDMD_DIVERMODE_MAIN) अणु
		tnr_dmd->भागer_sub->state = CXD2880_TNRDMD_STATE_ACTIVE;
		tnr_dmd->भागer_sub->frequency_khz = tune_param->center_freq_khz;
		tnr_dmd->भागer_sub->sys = CXD2880_DTV_SYS_DVBT2;
		tnr_dmd->भागer_sub->bandwidth = tune_param->bandwidth;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक cxd2880_tnrdmd_dvbt2_sleep_setting(काष्ठा cxd2880_tnrdmd
				       *tnr_dmd)
अणु
	पूर्णांक ret;

	अगर (!tnr_dmd)
		वापस -EINVAL;

	अगर (tnr_dmd->भागer_mode == CXD2880_TNRDMD_DIVERMODE_SUB)
		वापस -EINVAL;

	अगर (tnr_dmd->state != CXD2880_TNRDMD_STATE_SLEEP &&
	    tnr_dmd->state != CXD2880_TNRDMD_STATE_ACTIVE)
		वापस -EINVAL;

	ret = x_sleep_dvbt2_demod_setting(tnr_dmd);
	अगर (ret)
		वापस ret;

	अगर (tnr_dmd->भागer_mode == CXD2880_TNRDMD_DIVERMODE_MAIN)
		ret = x_sleep_dvbt2_demod_setting(tnr_dmd->भागer_sub);

	वापस ret;
पूर्ण

पूर्णांक cxd2880_tnrdmd_dvbt2_check_demod_lock(काष्ठा cxd2880_tnrdmd
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
	    cxd2880_tnrdmd_dvbt2_mon_sync_stat(tnr_dmd, &sync_stat, &ts_lock,
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
	    cxd2880_tnrdmd_dvbt2_mon_sync_stat_sub(tnr_dmd, &sync_stat,
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

पूर्णांक cxd2880_tnrdmd_dvbt2_check_ts_lock(काष्ठा cxd2880_tnrdmd
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
	    cxd2880_tnrdmd_dvbt2_mon_sync_stat(tnr_dmd, &sync_stat, &ts_lock,
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
	    cxd2880_tnrdmd_dvbt2_mon_sync_stat_sub(tnr_dmd, &sync_stat,
						   &unlock_detected_sub);
	अगर (ret)
		वापस ret;

	अगर (unlock_detected && unlock_detected_sub)
		*lock = CXD2880_TNRDMD_LOCK_RESULT_UNLOCKED;
	अन्यथा
		*lock = CXD2880_TNRDMD_LOCK_RESULT_NOTDETECT;

	वापस ret;
पूर्ण

पूर्णांक cxd2880_tnrdmd_dvbt2_set_plp_cfg(काष्ठा cxd2880_tnrdmd
				     *tnr_dmd, u8 स्वतः_plp,
				     u8 plp_id)
अणु
	पूर्णांक ret;

	अगर (!tnr_dmd)
		वापस -EINVAL;

	अगर (tnr_dmd->भागer_mode == CXD2880_TNRDMD_DIVERMODE_SUB)
		वापस -EINVAL;

	अगर (tnr_dmd->state != CXD2880_TNRDMD_STATE_SLEEP &&
	    tnr_dmd->state != CXD2880_TNRDMD_STATE_ACTIVE)
		वापस -EINVAL;

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x23);
	अगर (ret)
		वापस ret;

	अगर (!स्वतः_plp) अणु
		ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
					     CXD2880_IO_TGT_DMD,
					     0xaf, plp_id);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				      CXD2880_IO_TGT_DMD,
				      0xad, स्वतः_plp ? 0x00 : 0x01);
पूर्ण

पूर्णांक cxd2880_tnrdmd_dvbt2_भागer_fef_setting(काष्ठा cxd2880_tnrdmd
					   *tnr_dmd)
अणु
	काष्ठा cxd2880_dvbt2_ofdm ofdm;
	अटल स्थिर u8 data[] = अणु 0, 8, 0, 16, 0, 32, 0, 64, 0, 128, 1, 0पूर्ण;
	पूर्णांक ret;

	अगर (!tnr_dmd)
		वापस -EINVAL;

	अगर (tnr_dmd->भागer_mode == CXD2880_TNRDMD_DIVERMODE_SUB)
		वापस -EINVAL;

	अगर (tnr_dmd->state != CXD2880_TNRDMD_STATE_ACTIVE)
		वापस -EINVAL;

	अगर (tnr_dmd->भागer_mode == CXD2880_TNRDMD_DIVERMODE_SINGLE)
		वापस 0;

	ret = cxd2880_tnrdmd_dvbt2_mon_ofdm(tnr_dmd, &ofdm);
	अगर (ret)
		वापस ret;

	अगर (!ofdm.mixed)
		वापस 0;

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x1d);
	अगर (ret)
		वापस ret;

	वापस tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
				       CXD2880_IO_TGT_DMD,
				       0x47, data, 12);
पूर्ण

पूर्णांक cxd2880_tnrdmd_dvbt2_check_l1post_valid(काष्ठा cxd2880_tnrdmd
					    *tnr_dmd,
					    u8 *l1_post_valid)
अणु
	पूर्णांक ret;

	u8 data;

	अगर (!tnr_dmd || !l1_post_valid)
		वापस -EINVAL;

	अगर (tnr_dmd->भागer_mode == CXD2880_TNRDMD_DIVERMODE_SUB)
		वापस -EINVAL;

	अगर (tnr_dmd->state != CXD2880_TNRDMD_STATE_SLEEP &&
	    tnr_dmd->state != CXD2880_TNRDMD_STATE_ACTIVE)
		वापस -EINVAL;

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x0b);
	अगर (ret)
		वापस ret;

	ret = tnr_dmd->io->पढ़ो_regs(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x86, &data, 1);
	अगर (ret)
		वापस ret;

	*l1_post_valid = data & 0x01;

	वापस ret;
पूर्ण
