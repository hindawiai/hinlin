<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * cxd2880_tnrdmd.c
 * Sony CXD2880 DVB-T2/T tuner + demodulator driver
 * common control functions
 *
 * Copyright (C) 2016, 2017, 2018 Sony Semiconductor Solutions Corporation
 */

#समावेश <media/dvb_frontend.h>
#समावेश "cxd2880_common.h"
#समावेश "cxd2880_tnrdmd.h"
#समावेश "cxd2880_tnrdmd_mon.h"
#समावेश "cxd2880_tnrdmd_dvbt.h"
#समावेश "cxd2880_tnrdmd_dvbt2.h"

अटल स्थिर काष्ठा cxd2880_reg_value p_init1_seq[] = अणु
	अणु0x11, 0x16पूर्ण, अणु0x00, 0x10पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा cxd2880_reg_value rf_init1_seq1[] = अणु
	अणु0x4f, 0x18पूर्ण, अणु0x61, 0x00पूर्ण, अणु0x71, 0x00पूर्ण, अणु0x9d, 0x01पूर्ण,
	अणु0x7d, 0x02पूर्ण, अणु0x8f, 0x01पूर्ण, अणु0x8b, 0xc6पूर्ण, अणु0x9a, 0x03पूर्ण,
	अणु0x1c, 0x00पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा cxd2880_reg_value rf_init1_seq2[] = अणु
	अणु0xb9, 0x07पूर्ण, अणु0x33, 0x01पूर्ण, अणु0xc1, 0x01पूर्ण, अणु0xc4, 0x1eपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा cxd2880_reg_value rf_init1_seq3[] = अणु
	अणु0x00, 0x10पूर्ण, अणु0x51, 0x01पूर्ण, अणु0xc5, 0x07पूर्ण, अणु0x00, 0x11पूर्ण,
	अणु0x70, 0xe9पूर्ण, अणु0x76, 0x0aपूर्ण, अणु0x78, 0x32पूर्ण, अणु0x7a, 0x46पूर्ण,
	अणु0x7c, 0x86पूर्ण, अणु0x7e, 0xa4पूर्ण, अणु0x00, 0x10पूर्ण, अणु0xe1, 0x01पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा cxd2880_reg_value rf_init1_seq4[] = अणु
	अणु0x15, 0x00पूर्ण, अणु0x00, 0x16पूर्ण
पूर्ण;

अटल स्थिर काष्ठा cxd2880_reg_value rf_init1_seq5[] = अणु
	अणु0x00, 0x00पूर्ण, अणु0x25, 0x00पूर्ण
पूर्ण;

अटल स्थिर काष्ठा cxd2880_reg_value rf_init1_seq6[] = अणु
	अणु0x02, 0x00पूर्ण, अणु0x00, 0x00पूर्ण, अणु0x21, 0x01पूर्ण, अणु0x00, 0xe1पूर्ण,
	अणु0x8f, 0x16पूर्ण, अणु0x67, 0x60पूर्ण, अणु0x6a, 0x0fपूर्ण, अणु0x6c, 0x17पूर्ण
पूर्ण;

अटल स्थिर काष्ठा cxd2880_reg_value rf_init1_seq7[] = अणु
	अणु0x00, 0xe2पूर्ण, अणु0x41, 0xa0पूर्ण, अणु0x4b, 0x68पूर्ण, अणु0x00, 0x00पूर्ण,
	अणु0x21, 0x00पूर्ण, अणु0x10, 0x01पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा cxd2880_reg_value rf_init1_seq8[] = अणु
	अणु0x00, 0x10पूर्ण, अणु0x25, 0x01पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा cxd2880_reg_value rf_init1_seq9[] = अणु
	अणु0x00, 0x10पूर्ण, अणु0x14, 0x01पूर्ण, अणु0x00, 0x00पूर्ण, अणु0x26, 0x00पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा cxd2880_reg_value rf_init2_seq1[] = अणु
	अणु0x00, 0x14पूर्ण, अणु0x1b, 0x01पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा cxd2880_reg_value rf_init2_seq2[] = अणु
	अणु0x00, 0x00पूर्ण, अणु0x21, 0x01पूर्ण, अणु0x00, 0xe1पूर्ण, अणु0xd3, 0x00पूर्ण,
	अणु0x00, 0x00पूर्ण, अणु0x21, 0x00पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा cxd2880_reg_value x_tune1_seq1[] = अणु
	अणु0x00, 0x00पूर्ण, अणु0x10, 0x01पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा cxd2880_reg_value x_tune1_seq2[] = अणु
	अणु0x62, 0x00पूर्ण, अणु0x00, 0x15पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा cxd2880_reg_value x_tune2_seq1[] = अणु
	अणु0x00, 0x1aपूर्ण, अणु0x29, 0x01पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा cxd2880_reg_value x_tune2_seq2[] = अणु
	अणु0x62, 0x01पूर्ण, अणु0x00, 0x11पूर्ण, अणु0x2d, 0x00पूर्ण, अणु0x2f, 0x00पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा cxd2880_reg_value x_tune2_seq3[] = अणु
	अणु0x00, 0x00पूर्ण, अणु0x10, 0x00पूर्ण, अणु0x21, 0x01पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा cxd2880_reg_value x_tune2_seq4[] = अणु
	अणु0x00, 0xe1पूर्ण, अणु0x8a, 0x87पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा cxd2880_reg_value x_tune2_seq5[] = अणु
	अणु0x00, 0x00पूर्ण, अणु0x21, 0x00पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा cxd2880_reg_value x_tune3_seq[] = अणु
	अणु0x00, 0x00पूर्ण, अणु0x21, 0x01पूर्ण, अणु0x00, 0xe2पूर्ण, अणु0x41, 0xa0पूर्ण,
	अणु0x00, 0x00पूर्ण, अणु0x21, 0x00पूर्ण, अणु0xfe, 0x01पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा cxd2880_reg_value x_tune4_seq[] = अणु
	अणु0x00, 0x00पूर्ण, अणु0xfe, 0x01पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा cxd2880_reg_value x_sleep1_seq[] = अणु
	अणु0x00, 0x00पूर्ण, अणु0x57, 0x03पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा cxd2880_reg_value x_sleep2_seq1[] = अणु
	अणु0x00, 0x2dपूर्ण, अणु0xb1, 0x01पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा cxd2880_reg_value x_sleep2_seq2[] = अणु
	अणु0x00, 0x10पूर्ण, अणु0xf4, 0x00पूर्ण, अणु0xf3, 0x00पूर्ण, अणु0xf2, 0x00पूर्ण,
	अणु0xf1, 0x00पूर्ण, अणु0xf0, 0x00पूर्ण, अणु0xef, 0x00पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा cxd2880_reg_value x_sleep3_seq[] = अणु
	अणु0x00, 0x00पूर्ण, अणु0xfd, 0x00पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा cxd2880_reg_value x_sleep4_seq[] = अणु
	अणु0x00, 0x00पूर्ण, अणु0x21, 0x01पूर्ण, अणु0x00, 0xe2पूर्ण, अणु0x41, 0x00पूर्ण,
	अणु0x00, 0x00पूर्ण, अणु0x21, 0x00पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा cxd2880_reg_value spll_reset_seq1[] = अणु
	अणु0x00, 0x10पूर्ण, अणु0x29, 0x01पूर्ण, अणु0x28, 0x01पूर्ण, अणु0x27, 0x01पूर्ण,
	अणु0x26, 0x01पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा cxd2880_reg_value spll_reset_seq2[] = अणु
	अणु0x00, 0x00पूर्ण, अणु0x10, 0x00पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा cxd2880_reg_value spll_reset_seq3[] = अणु
	अणु0x00, 0x00पूर्ण, अणु0x27, 0x00पूर्ण, अणु0x22, 0x01पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा cxd2880_reg_value spll_reset_seq4[] = अणु
	अणु0x00, 0x00पूर्ण, अणु0x27, 0x01पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा cxd2880_reg_value spll_reset_seq5[] = अणु
	अणु0x00, 0x00पूर्ण, अणु0x10, 0x01पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा cxd2880_reg_value t_घातer_x_seq1[] = अणु
	अणु0x00, 0x10पूर्ण, अणु0x29, 0x01पूर्ण, अणु0x28, 0x01पूर्ण, अणु0x27, 0x01पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा cxd2880_reg_value t_घातer_x_seq2[] = अणु
	अणु0x00, 0x00पूर्ण, अणु0x10, 0x00पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा cxd2880_reg_value t_घातer_x_seq3[] = अणु
	अणु0x00, 0x00पूर्ण, अणु0x27, 0x00पूर्ण, अणु0x25, 0x01पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा cxd2880_reg_value t_घातer_x_seq4[] = अणु
	अणु0x00, 0x00पूर्ण, अणु0x2a, 0x00पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा cxd2880_reg_value t_घातer_x_seq5[] = अणु
	अणु0x00, 0x00पूर्ण, अणु0x25, 0x00पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा cxd2880_reg_value t_घातer_x_seq6[] = अणु
	अणु0x00, 0x00पूर्ण, अणु0x27, 0x01पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा cxd2880_reg_value t_घातer_x_seq7[] = अणु
	अणु0x00, 0x00पूर्ण, अणु0x10, 0x01पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा cxd2880_reg_value set_ts_pin_seq[] = अणु
	अणु0x50, 0x3fपूर्ण, अणु0x52, 0x1fपूर्ण,

पूर्ण;

अटल स्थिर काष्ठा cxd2880_reg_value set_ts_output_seq1[] = अणु
	अणु0x00, 0x00पूर्ण, अणु0x52, 0x00पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा cxd2880_reg_value set_ts_output_seq2[] = अणु
	अणु0x00, 0x00पूर्ण, अणु0xc3, 0x00पूर्ण,

पूर्ण;

अटल स्थिर काष्ठा cxd2880_reg_value set_ts_output_seq3[] = अणु
	अणु0x00, 0x00पूर्ण, अणु0xc3, 0x01पूर्ण,

पूर्ण;

अटल स्थिर काष्ठा cxd2880_reg_value set_ts_output_seq4[] = अणु
	अणु0x00, 0x00पूर्ण, अणु0x52, 0x1fपूर्ण,

पूर्ण;

अटल पूर्णांक p_init1(काष्ठा cxd2880_tnrdmd *tnr_dmd)
अणु
	u8 data = 0;
	पूर्णांक ret;

	अगर (!tnr_dmd)
		वापस -EINVAL;

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x00, 0x00);
	अगर (ret)
		वापस ret;

	अगर (tnr_dmd->भागer_mode == CXD2880_TNRDMD_DIVERMODE_SINGLE ||
	    tnr_dmd->भागer_mode == CXD2880_TNRDMD_DIVERMODE_MAIN) अणु
		चयन (tnr_dmd->create_param.ts_output_अगर) अणु
		हाल CXD2880_TNRDMD_TSOUT_IF_TS:
			data = 0x00;
			अवरोध;
		हाल CXD2880_TNRDMD_TSOUT_IF_SPI:
			data = 0x01;
			अवरोध;
		हाल CXD2880_TNRDMD_TSOUT_IF_SDIO:
			data = 0x02;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
					     CXD2880_IO_TGT_SYS,
					     0x10, data);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = cxd2880_io_ग_लिखो_multi_regs(tnr_dmd->io,
					  CXD2880_IO_TGT_SYS,
					  p_init1_seq,
					  ARRAY_SIZE(p_init1_seq));
	अगर (ret)
		वापस ret;

	चयन (tnr_dmd->chip_id) अणु
	हाल CXD2880_TNRDMD_CHIP_ID_CXD2880_ES1_0X:
		data = 0x1a;
		अवरोध;
	हाल CXD2880_TNRDMD_CHIP_ID_CXD2880_ES1_11:
		data = 0x16;
		अवरोध;
	शेष:
		वापस -ENOTTY;
	पूर्ण

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x10, data);
	अगर (ret)
		वापस ret;

	अगर (tnr_dmd->create_param.en_पूर्णांकernal_lकरो)
		data = 0x01;
	अन्यथा
		data = 0x00;

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x11, data);
	अगर (ret)
		वापस ret;
	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x13, data);
	अगर (ret)
		वापस ret;

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x00, 0x00);
	अगर (ret)
		वापस ret;
	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x12, data);
	अगर (ret)
		वापस ret;

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x00, 0x10);
	अगर (ret)
		वापस ret;

	चयन (tnr_dmd->chip_id) अणु
	हाल CXD2880_TNRDMD_CHIP_ID_CXD2880_ES1_0X:
		data = 0x01;
		अवरोध;
	हाल CXD2880_TNRDMD_CHIP_ID_CXD2880_ES1_11:
		data = 0x00;
		अवरोध;
	शेष:
		वापस -ENOTTY;
	पूर्ण

	वापस tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				      CXD2880_IO_TGT_SYS,
				      0x69, data);
पूर्ण

अटल पूर्णांक p_init2(काष्ठा cxd2880_tnrdmd *tnr_dmd)
अणु
	u8 data[6] = अणु 0 पूर्ण;
	पूर्णांक ret;

	अगर (!tnr_dmd)
		वापस -EINVAL;

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x00, 0x00);
	अगर (ret)
		वापस ret;
	data[0] = tnr_dmd->create_param.xosc_cap;
	data[1] = tnr_dmd->create_param.xosc_i;
	चयन (tnr_dmd->create_param.xtal_share_type) अणु
	हाल CXD2880_TNRDMD_XTAL_SHARE_NONE:
		data[2] = 0x01;
		data[3] = 0x00;
		अवरोध;
	हाल CXD2880_TNRDMD_XTAL_SHARE_EXTREF:
		data[2] = 0x00;
		data[3] = 0x00;
		अवरोध;
	हाल CXD2880_TNRDMD_XTAL_SHARE_MASTER:
		data[2] = 0x01;
		data[3] = 0x01;
		अवरोध;
	हाल CXD2880_TNRDMD_XTAL_SHARE_SLAVE:
		data[2] = 0x00;
		data[3] = 0x01;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	data[4] = 0x06;
	data[5] = 0x00;

	वापस tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
				       CXD2880_IO_TGT_SYS,
				       0x13, data, 6);
पूर्ण

अटल पूर्णांक p_init3(काष्ठा cxd2880_tnrdmd *tnr_dmd)
अणु
	u8 data[2] = अणु 0 पूर्ण;
	पूर्णांक ret;

	अगर (!tnr_dmd)
		वापस -EINVAL;

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x00, 0x00);
	अगर (ret)
		वापस ret;

	चयन (tnr_dmd->भागer_mode) अणु
	हाल CXD2880_TNRDMD_DIVERMODE_SINGLE:
		data[0] = 0x00;
		अवरोध;
	हाल CXD2880_TNRDMD_DIVERMODE_MAIN:
		data[0] = 0x03;
		अवरोध;
	हाल CXD2880_TNRDMD_DIVERMODE_SUB:
		data[0] = 0x02;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	data[1] = 0x01;

	वापस tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
				       CXD2880_IO_TGT_SYS,
				       0x1f, data, 2);
पूर्ण

अटल पूर्णांक rf_init1(काष्ठा cxd2880_tnrdmd *tnr_dmd)
अणु
	u8 data[8] = अणु 0 पूर्ण;
	अटल स्थिर u8 rf_init1_cdata1[40] = अणु
		0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05,
		0x05, 0x05, 0x04, 0x04, 0x04, 0x03, 0x03,
		0x03, 0x04, 0x04, 0x05, 0x05, 0x05, 0x02,
		0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
		0x02, 0x03, 0x02, 0x01, 0x01, 0x01, 0x02,
		0x02, 0x03, 0x04, 0x04, 0x04
	पूर्ण;

	अटल स्थिर u8 rf_init1_cdata2[5] = अणु0xff, 0x00, 0x00, 0x00, 0x00पूर्ण;
	अटल स्थिर u8 rf_init1_cdata3[80] = अणु
		0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00,
		0x01, 0x00, 0x02, 0x00, 0x63, 0x00, 0x00,
		0x00, 0x03, 0x00, 0x04, 0x00, 0x04, 0x00,
		0x06, 0x00, 0x06, 0x00, 0x08, 0x00, 0x09,
		0x00, 0x0b, 0x00, 0x0b, 0x00, 0x0d, 0x00,
		0x0d, 0x00, 0x0f, 0x00, 0x0f, 0x00, 0x0f,
		0x00, 0x10, 0x00, 0x79, 0x00, 0x00, 0x00,
		0x02, 0x00, 0x00, 0x00, 0x03, 0x00, 0x01,
		0x00, 0x03, 0x00, 0x03, 0x00, 0x03, 0x00,
		0x04, 0x00, 0x04, 0x00, 0x06, 0x00, 0x05,
		0x00, 0x07, 0x00, 0x07, 0x00, 0x08, 0x00,
		0x0a, 0x03, 0xe0
	पूर्ण;

	अटल स्थिर u8 rf_init1_cdata4[8] = अणु
		0x20, 0x20, 0x30, 0x41, 0x50, 0x5f, 0x6f, 0x80
	पूर्ण;

	अटल स्थिर u8 rf_init1_cdata5[50] = अणु
		0x00, 0x09, 0x00, 0x08, 0x00, 0x07, 0x00,
		0x06, 0x00, 0x05, 0x00, 0x03, 0x00, 0x02,
		0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00,
		0x06, 0x00, 0x08, 0x00, 0x08, 0x00, 0x0c,
		0x00, 0x0c, 0x00, 0x0d, 0x00, 0x0f, 0x00,
		0x0e, 0x00, 0x0e, 0x00, 0x10, 0x00, 0x0f,
		0x00, 0x0e, 0x00, 0x10, 0x00, 0x0f, 0x00,
		0x0e
	पूर्ण;

	u8 addr = 0;
	पूर्णांक ret;

	अगर (!tnr_dmd)
		वापस -EINVAL;

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x00, 0x00);
	अगर (ret)
		वापस ret;
	data[0] = 0x01;
	data[1] = 0x00;
	data[2] = 0x01;
	ret = tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
				      CXD2880_IO_TGT_SYS,
				      0x21, data, 3);
	अगर (ret)
		वापस ret;

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x00, 0x10);
	अगर (ret)
		वापस ret;
	data[0] = 0x01;
	data[1] = 0x01;
	ret = tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
				      CXD2880_IO_TGT_SYS,
				      0x17, data, 2);
	अगर (ret)
		वापस ret;

	अगर (tnr_dmd->create_param.stationary_use) अणु
		ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
					     CXD2880_IO_TGT_SYS,
					     0x1a, 0x06);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = cxd2880_io_ग_लिखो_multi_regs(tnr_dmd->io,
					  CXD2880_IO_TGT_SYS,
					  rf_init1_seq1,
					  ARRAY_SIZE(rf_init1_seq1));
	अगर (ret)
		वापस ret;

	data[0] = 0x00;
	अगर (tnr_dmd->create_param.is_cxd2881gg &&
	    tnr_dmd->create_param.xtal_share_type ==
		CXD2880_TNRDMD_XTAL_SHARE_SLAVE)
		data[1] = 0x00;
	अन्यथा
		data[1] = 0x1f;
	data[2] = 0x0a;
	ret = tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
				      CXD2880_IO_TGT_SYS,
				      0xb5, data, 3);
	अगर (ret)
		वापस ret;

	ret = cxd2880_io_ग_लिखो_multi_regs(tnr_dmd->io,
					  CXD2880_IO_TGT_SYS,
					  rf_init1_seq2,
					  ARRAY_SIZE(rf_init1_seq2));
	अगर (ret)
		वापस ret;

	अगर (tnr_dmd->chip_id == CXD2880_TNRDMD_CHIP_ID_CXD2880_ES1_0X) अणु
		data[0] = 0x34;
		data[1] = 0x2c;
	पूर्ण अन्यथा अणु
		data[0] = 0x2f;
		data[1] = 0x25;
	पूर्ण
	data[2] = 0x15;
	data[3] = 0x19;
	data[4] = 0x1b;
	data[5] = 0x15;
	data[6] = 0x19;
	data[7] = 0x1b;
	ret = tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
				      CXD2880_IO_TGT_SYS,
				      0xd9, data, 8);
	अगर (ret)
		वापस ret;

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x00, 0x11);
	अगर (ret)
		वापस ret;
	data[0] = 0x6c;
	data[1] = 0x10;
	data[2] = 0xa6;
	ret = tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
				      CXD2880_IO_TGT_SYS,
				      0x44, data, 3);
	अगर (ret)
		वापस ret;
	data[0] = 0x16;
	data[1] = 0xa8;
	ret = tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
				      CXD2880_IO_TGT_SYS,
				      0x50, data, 2);
	अगर (ret)
		वापस ret;
	data[0] = 0x00;
	data[1] = 0x22;
	data[2] = 0x00;
	data[3] = 0x88;
	ret = tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
				      CXD2880_IO_TGT_SYS,
				      0x62, data, 4);
	अगर (ret)
		वापस ret;
	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x74, 0x75);
	अगर (ret)
		वापस ret;
	ret = tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
				      CXD2880_IO_TGT_SYS,
				      0x7f, rf_init1_cdata1, 40);
	अगर (ret)
		वापस ret;

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x00, 0x16);
	अगर (ret)
		वापस ret;
	data[0] = 0x00;
	data[1] = 0x71;
	ret = tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
				      CXD2880_IO_TGT_SYS,
				      0x10, data, 2);
	अगर (ret)
		वापस ret;
	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x23, 0x89);
	अगर (ret)
		वापस ret;

	ret = tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
				      CXD2880_IO_TGT_SYS,
				      0x27, rf_init1_cdata2, 5);
	अगर (ret)
		वापस ret;

	ret = tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
				      CXD2880_IO_TGT_SYS,
				      0x3a, rf_init1_cdata3, 80);
	अगर (ret)
		वापस ret;

	data[0] = 0x03;
	data[1] = 0xe0;
	ret = tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
				      CXD2880_IO_TGT_SYS,
				      0xbc, data, 2);
	अगर (ret)
		वापस ret;

	ret = cxd2880_io_ग_लिखो_multi_regs(tnr_dmd->io,
					  CXD2880_IO_TGT_SYS,
					  rf_init1_seq3,
					  ARRAY_SIZE(rf_init1_seq3));
	अगर (ret)
		वापस ret;

	अगर (tnr_dmd->create_param.stationary_use) अणु
		data[0] = 0x06;
		data[1] = 0x07;
		data[2] = 0x1a;
	पूर्ण अन्यथा अणु
		data[0] = 0x00;
		data[1] = 0x08;
		data[2] = 0x19;
	पूर्ण
	data[3] = 0x0e;
	data[4] = 0x09;
	data[5] = 0x0e;

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x00, 0x12);
	अगर (ret)
		वापस ret;
	क्रम (addr = 0x10; addr < 0x9f; addr += 6) अणु
		अगर (tnr_dmd->lna_thrs_tbl_air) अणु
			u8 idx = 0;

			idx = (addr - 0x10) / 6;
			data[0] =
			    tnr_dmd->lna_thrs_tbl_air->thrs[idx].off_on;
			data[1] =
			    tnr_dmd->lna_thrs_tbl_air->thrs[idx].on_off;
		पूर्ण
		ret = tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
					      CXD2880_IO_TGT_SYS,
					      addr, data, 6);
		अगर (ret)
			वापस ret;
	पूर्ण

	data[0] = 0x00;
	data[1] = 0x08;
	अगर (tnr_dmd->create_param.stationary_use)
		data[2] = 0x1a;
	अन्यथा
		data[2] = 0x19;
	data[3] = 0x0e;
	data[4] = 0x09;
	data[5] = 0x0e;

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x00, 0x13);
	अगर (ret)
		वापस ret;
	क्रम (addr = 0x10; addr < 0xcf; addr += 6) अणु
		अगर (tnr_dmd->lna_thrs_tbl_cable) अणु
			u8 idx = 0;

			idx = (addr - 0x10) / 6;
			data[0] =
			    tnr_dmd->lna_thrs_tbl_cable->thrs[idx].off_on;
			data[1] =
			    tnr_dmd->lna_thrs_tbl_cable->thrs[idx].on_off;
		पूर्ण
		ret = tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
					      CXD2880_IO_TGT_SYS,
					      addr, data, 6);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x00, 0x11);
	अगर (ret)
		वापस ret;
	data[0] = 0x08;
	data[1] = 0x09;
	ret = tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
				      CXD2880_IO_TGT_SYS,
				      0xbd, data, 2);
	अगर (ret)
		वापस ret;
	data[0] = 0x08;
	data[1] = 0x09;
	ret = tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
				      CXD2880_IO_TGT_SYS,
				      0xc4, data, 2);
	अगर (ret)
		वापस ret;

	ret = tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
				      CXD2880_IO_TGT_SYS,
				      0xc9, rf_init1_cdata4, 8);
	अगर (ret)
		वापस ret;

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x00, 0x14);
	अगर (ret)
		वापस ret;
	data[0] = 0x15;
	data[1] = 0x18;
	data[2] = 0x00;
	ret = tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
				      CXD2880_IO_TGT_SYS,
				      0x10, data, 3);
	अगर (ret)
		वापस ret;

	ret = cxd2880_io_ग_लिखो_multi_regs(tnr_dmd->io,
					  CXD2880_IO_TGT_SYS,
					  rf_init1_seq4,
					  ARRAY_SIZE(rf_init1_seq4));
	अगर (ret)
		वापस ret;

	ret = tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
				      CXD2880_IO_TGT_SYS,
				      0x12, rf_init1_cdata5, 50);
	अगर (ret)
		वापस ret;

	usleep_range(1000, 2000);

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x00, 0x0a);
	अगर (ret)
		वापस ret;
	ret = tnr_dmd->io->पढ़ो_regs(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x10, data, 1);
	अगर (ret)
		वापस ret;
	अगर ((data[0] & 0x01) == 0x00)
		वापस -EINVAL;

	ret = cxd2880_io_ग_लिखो_multi_regs(tnr_dmd->io,
					  CXD2880_IO_TGT_SYS,
					  rf_init1_seq5,
					  ARRAY_SIZE(rf_init1_seq5));
	अगर (ret)
		वापस ret;

	usleep_range(1000, 2000);

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x00, 0x0a);
	अगर (ret)
		वापस ret;
	ret = tnr_dmd->io->पढ़ो_regs(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x11, data, 1);
	अगर (ret)
		वापस ret;
	अगर ((data[0] & 0x01) == 0x00)
		वापस -EINVAL;

	ret = cxd2880_io_ग_लिखो_multi_regs(tnr_dmd->io,
					  CXD2880_IO_TGT_DMD,
					  rf_init1_seq6,
					  ARRAY_SIZE(rf_init1_seq6));
	अगर (ret)
		वापस ret;

	data[0] = 0x00;
	data[1] = 0xfe;
	data[2] = 0xee;
	ret = tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
				      CXD2880_IO_TGT_DMD,
				      0x6e, data, 3);
	अगर (ret)
		वापस ret;
	data[0] = 0xa1;
	data[1] = 0x8b;
	ret = tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
				      CXD2880_IO_TGT_DMD,
				      0x8d, data, 2);
	अगर (ret)
		वापस ret;
	data[0] = 0x08;
	data[1] = 0x09;
	ret = tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
				      CXD2880_IO_TGT_DMD,
				      0x77, data, 2);
	अगर (ret)
		वापस ret;

	अगर (tnr_dmd->create_param.stationary_use) अणु
		ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
					     CXD2880_IO_TGT_DMD,
					     0x80, 0xaa);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = cxd2880_io_ग_लिखो_multi_regs(tnr_dmd->io,
					  CXD2880_IO_TGT_DMD,
					  rf_init1_seq7,
					  ARRAY_SIZE(rf_init1_seq7));
	अगर (ret)
		वापस ret;

	ret = cxd2880_io_ग_लिखो_multi_regs(tnr_dmd->io,
					  CXD2880_IO_TGT_SYS,
					  rf_init1_seq8,
					  ARRAY_SIZE(rf_init1_seq8));
	अगर (ret)
		वापस ret;

	usleep_range(1000, 2000);

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x00, 0x1a);
	अगर (ret)
		वापस ret;
	ret = tnr_dmd->io->पढ़ो_regs(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x10, data, 1);
	अगर (ret)
		वापस ret;
	अगर ((data[0] & 0x01) == 0x00)
		वापस -EINVAL;

	वापस cxd2880_io_ग_लिखो_multi_regs(tnr_dmd->io,
					   CXD2880_IO_TGT_SYS,
					   rf_init1_seq9,
					   ARRAY_SIZE(rf_init1_seq9));
पूर्ण

अटल पूर्णांक rf_init2(काष्ठा cxd2880_tnrdmd *tnr_dmd)
अणु
	u8 data[5] = अणु 0 पूर्ण;
	पूर्णांक ret;

	अगर (!tnr_dmd)
		वापस -EINVAL;

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x00, 0x10);
	अगर (ret)
		वापस ret;
	data[0] = 0x40;
	data[1] = 0x40;
	ret = tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
				      CXD2880_IO_TGT_SYS,
				      0xea, data, 2);
	अगर (ret)
		वापस ret;

	usleep_range(1000, 2000);

	data[0] = 0x00;
	अगर (tnr_dmd->chip_id == CXD2880_TNRDMD_CHIP_ID_CXD2880_ES1_0X)
		data[1] = 0x00;
	अन्यथा
		data[1] = 0x01;
	data[2] = 0x01;
	data[3] = 0x03;
	ret = tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
				      CXD2880_IO_TGT_SYS,
				      0x30, data, 4);
	अगर (ret)
		वापस ret;

	ret = cxd2880_io_ग_लिखो_multi_regs(tnr_dmd->io,
					  CXD2880_IO_TGT_SYS,
					  rf_init2_seq1,
					  ARRAY_SIZE(rf_init2_seq1));
	अगर (ret)
		वापस ret;

	वापस cxd2880_io_ग_लिखो_multi_regs(tnr_dmd->io,
					   CXD2880_IO_TGT_DMD,
					   rf_init2_seq2,
					   ARRAY_SIZE(rf_init2_seq2));
पूर्ण

अटल पूर्णांक x_tune1(काष्ठा cxd2880_tnrdmd *tnr_dmd,
		   क्रमागत cxd2880_dtv_sys sys, u32 freq_khz,
		   क्रमागत cxd2880_dtv_bandwidth bandwidth,
		   u8 is_cable, पूर्णांक shअगरt_frequency_khz)
अणु
	u8 data[11] = अणु 0 पूर्ण;
	पूर्णांक ret;

	अगर (!tnr_dmd)
		वापस -EINVAL;

	ret = cxd2880_io_ग_लिखो_multi_regs(tnr_dmd->io,
					  CXD2880_IO_TGT_DMD,
					  x_tune1_seq1,
					  ARRAY_SIZE(x_tune1_seq1));
	अगर (ret)
		वापस ret;

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x00, 0x10);
	अगर (ret)
		वापस ret;

	data[2] = 0x0e;
	data[4] = 0x03;
	ret = tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
				      CXD2880_IO_TGT_SYS,
				      0xe7, data, 5);
	अगर (ret)
		वापस ret;

	data[0] = 0x1f;
	data[1] = 0x80;
	data[2] = 0x18;
	data[3] = 0x00;
	data[4] = 0x07;
	ret = tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
				      CXD2880_IO_TGT_SYS,
				      0xe7, data, 5);
	अगर (ret)
		वापस ret;

	usleep_range(1000, 2000);

	data[0] = 0x72;
	data[1] = 0x81;
	data[3] = 0x1d;
	data[4] = 0x6f;
	data[5] = 0x7e;
	data[7] = 0x1c;
	चयन (sys) अणु
	हाल CXD2880_DTV_SYS_DVBT:
		data[2] = 0x94;
		data[6] = 0x91;
		अवरोध;
	हाल CXD2880_DTV_SYS_DVBT2:
		data[2] = 0x96;
		data[6] = 0x93;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	ret = tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
				      CXD2880_IO_TGT_SYS,
				      0x44, data, 8);
	अगर (ret)
		वापस ret;

	ret = cxd2880_io_ग_लिखो_multi_regs(tnr_dmd->io,
					  CXD2880_IO_TGT_SYS,
					  x_tune1_seq2,
					  ARRAY_SIZE(x_tune1_seq2));
	अगर (ret)
		वापस ret;

	data[0] = 0x03;
	data[1] = 0xe2;
	ret = tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
				      CXD2880_IO_TGT_SYS,
				      0x1e, data, 2);
	अगर (ret)
		वापस ret;

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x00, 0x10);
	अगर (ret)
		वापस ret;

	data[0] = is_cable ? 0x01 : 0x00;
	data[1] = 0x00;
	data[2] = 0x6b;
	data[3] = 0x4d;

	चयन (bandwidth) अणु
	हाल CXD2880_DTV_BW_1_7_MHZ:
		data[4] = 0x03;
		अवरोध;
	हाल CXD2880_DTV_BW_5_MHZ:
	हाल CXD2880_DTV_BW_6_MHZ:
		data[4] = 0x00;
		अवरोध;
	हाल CXD2880_DTV_BW_7_MHZ:
		data[4] = 0x01;
		अवरोध;
	हाल CXD2880_DTV_BW_8_MHZ:
		data[4] = 0x02;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	data[5] = 0x00;

	freq_khz += shअगरt_frequency_khz;

	data[6] = (freq_khz >> 16) & 0x0f;
	data[7] = (freq_khz >> 8) & 0xff;
	data[8] = freq_khz & 0xff;
	data[9] = 0xff;
	data[10] = 0xfe;

	वापस tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
				       CXD2880_IO_TGT_SYS,
				       0x52, data, 11);
पूर्ण

अटल पूर्णांक x_tune2(काष्ठा cxd2880_tnrdmd *tnr_dmd,
		   क्रमागत cxd2880_dtv_bandwidth bandwidth,
		   क्रमागत cxd2880_tnrdmd_घड़ीmode clk_mode,
		   पूर्णांक shअगरt_frequency_khz)
अणु
	u8 data[3] = अणु 0 पूर्ण;
	पूर्णांक ret;

	अगर (!tnr_dmd)
		वापस -EINVAL;

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x00, 0x11);
	अगर (ret)
		वापस ret;

	data[0] = 0x01;
	data[1] = 0x0e;
	data[2] = 0x01;
	ret = tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
				      CXD2880_IO_TGT_SYS,
				      0x2d, data, 3);
	अगर (ret)
		वापस ret;

	ret = cxd2880_io_ग_लिखो_multi_regs(tnr_dmd->io,
					  CXD2880_IO_TGT_SYS,
					  x_tune2_seq1,
					  ARRAY_SIZE(x_tune2_seq1));
	अगर (ret)
		वापस ret;

	ret = tnr_dmd->io->पढ़ो_regs(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x2c, data, 1);
	अगर (ret)
		वापस ret;

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x00, 0x10);
	अगर (ret)
		वापस ret;

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x60, data[0]);
	अगर (ret)
		वापस ret;

	ret = cxd2880_io_ग_लिखो_multi_regs(tnr_dmd->io,
					  CXD2880_IO_TGT_SYS,
					  x_tune2_seq2,
					  ARRAY_SIZE(x_tune2_seq2));
	अगर (ret)
		वापस ret;

	ret = cxd2880_io_ग_लिखो_multi_regs(tnr_dmd->io,
					  CXD2880_IO_TGT_DMD,
					  x_tune2_seq3,
					  ARRAY_SIZE(x_tune2_seq3));
	अगर (ret)
		वापस ret;

	अगर (shअगरt_frequency_khz != 0) अणु
		पूर्णांक shअगरt_freq = 0;

		ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
					     CXD2880_IO_TGT_DMD,
					     0x00, 0xe1);
		अगर (ret)
			वापस ret;

		ret = tnr_dmd->io->पढ़ो_regs(tnr_dmd->io,
					     CXD2880_IO_TGT_DMD,
					     0x60, data, 2);
		अगर (ret)
			वापस ret;

		shअगरt_freq = shअगरt_frequency_khz * 1000;

		चयन (clk_mode) अणु
		हाल CXD2880_TNRDMD_CLOCKMODE_A:
		हाल CXD2880_TNRDMD_CLOCKMODE_C:
		शेष:
			अगर (shअगरt_freq >= 0)
				shअगरt_freq = (shअगरt_freq + 183 / 2) / 183;
			अन्यथा
				shअगरt_freq = (shअगरt_freq - 183 / 2) / 183;
			अवरोध;
		हाल CXD2880_TNRDMD_CLOCKMODE_B:
			अगर (shअगरt_freq >= 0)
				shअगरt_freq = (shअगरt_freq + 178 / 2) / 178;
			अन्यथा
				shअगरt_freq = (shअगरt_freq - 178 / 2) / 178;
			अवरोध;
		पूर्ण

		shअगरt_freq +=
		    cxd2880_convert2s_complement((data[0] << 8) | data[1], 16);

		अगर (shअगरt_freq > 32767)
			shअगरt_freq = 32767;
		अन्यथा अगर (shअगरt_freq < -32768)
			shअगरt_freq = -32768;

		data[0] = (shअगरt_freq >> 8) & 0xff;
		data[1] = shअगरt_freq & 0xff;

		ret = tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
					      CXD2880_IO_TGT_DMD,
					      0x60, data, 2);
		अगर (ret)
			वापस ret;

		ret = tnr_dmd->io->पढ़ो_regs(tnr_dmd->io,
					     CXD2880_IO_TGT_DMD,
					     0x69, data, 1);
		अगर (ret)
			वापस ret;

		shअगरt_freq = -shअगरt_frequency_khz;

		अगर (bandwidth == CXD2880_DTV_BW_1_7_MHZ) अणु
			चयन (clk_mode) अणु
			हाल CXD2880_TNRDMD_CLOCKMODE_A:
			हाल CXD2880_TNRDMD_CLOCKMODE_C:
			शेष:
				अगर (shअगरt_freq >= 0)
					shअगरt_freq =
					    (shअगरt_freq * 1000 +
					     17578 / 2) / 17578;
				अन्यथा
					shअगरt_freq =
					    (shअगरt_freq * 1000 -
					     17578 / 2) / 17578;
				अवरोध;
			हाल CXD2880_TNRDMD_CLOCKMODE_B:
				अगर (shअगरt_freq >= 0)
					shअगरt_freq =
					    (shअगरt_freq * 1000 +
					     17090 / 2) / 17090;
				अन्यथा
					shअगरt_freq =
					    (shअगरt_freq * 1000 -
					     17090 / 2) / 17090;
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			चयन (clk_mode) अणु
			हाल CXD2880_TNRDMD_CLOCKMODE_A:
			हाल CXD2880_TNRDMD_CLOCKMODE_C:
			शेष:
				अगर (shअगरt_freq >= 0)
					shअगरt_freq =
					    (shअगरt_freq * 1000 +
					     35156 / 2) / 35156;
				अन्यथा
					shअगरt_freq =
					    (shअगरt_freq * 1000 -
					     35156 / 2) / 35156;
				अवरोध;
			हाल CXD2880_TNRDMD_CLOCKMODE_B:
				अगर (shअगरt_freq >= 0)
					shअगरt_freq =
					    (shअगरt_freq * 1000 +
					     34180 / 2) / 34180;
				अन्यथा
					shअगरt_freq =
					    (shअगरt_freq * 1000 -
					     34180 / 2) / 34180;
				अवरोध;
			पूर्ण
		पूर्ण

		shअगरt_freq += cxd2880_convert2s_complement(data[0], 8);

		अगर (shअगरt_freq > 127)
			shअगरt_freq = 127;
		अन्यथा अगर (shअगरt_freq < -128)
			shअगरt_freq = -128;

		data[0] = shअगरt_freq & 0xff;

		ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
					     CXD2880_IO_TGT_DMD,
					     0x69, data[0]);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (tnr_dmd->create_param.stationary_use) अणु
		ret = cxd2880_io_ग_लिखो_multi_regs(tnr_dmd->io,
						  CXD2880_IO_TGT_DMD,
						  x_tune2_seq4,
						  ARRAY_SIZE(x_tune2_seq4));
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस cxd2880_io_ग_लिखो_multi_regs(tnr_dmd->io,
					   CXD2880_IO_TGT_DMD,
					   x_tune2_seq5,
					   ARRAY_SIZE(x_tune2_seq5));
पूर्ण

अटल पूर्णांक x_tune3(काष्ठा cxd2880_tnrdmd *tnr_dmd,
		   क्रमागत cxd2880_dtv_sys sys,
		   u8 en_fef_पूर्णांकmtnt_ctrl)
अणु
	u8 data[6] = अणु 0 पूर्ण;
	पूर्णांक ret;

	अगर (!tnr_dmd)
		वापस -EINVAL;

	ret = cxd2880_io_ग_लिखो_multi_regs(tnr_dmd->io,
					  CXD2880_IO_TGT_DMD,
					  x_tune3_seq,
					  ARRAY_SIZE(x_tune3_seq));
	अगर (ret)
		वापस ret;

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x00, 0x10);
	अगर (ret)
		वापस ret;

	अगर (sys == CXD2880_DTV_SYS_DVBT2 && en_fef_पूर्णांकmtnt_ctrl)
		स_रखो(data, 0x01, माप(data));
	अन्यथा
		स_रखो(data, 0x00, माप(data));

	ret = tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
				      CXD2880_IO_TGT_SYS,
				      0xef, data, 6);
	अगर (ret)
		वापस ret;

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x2d);
	अगर (ret)
		वापस ret;
	अगर (sys == CXD2880_DTV_SYS_DVBT2 && en_fef_पूर्णांकmtnt_ctrl)
		data[0] = 0x00;
	अन्यथा
		data[0] = 0x01;

	वापस tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				      CXD2880_IO_TGT_DMD,
				      0xb1, data[0]);
पूर्ण

अटल पूर्णांक x_tune4(काष्ठा cxd2880_tnrdmd *tnr_dmd)
अणु
	u8 data[2] = अणु 0 पूर्ण;
	पूर्णांक ret;

	अगर (!tnr_dmd)
		वापस -EINVAL;

	अगर (tnr_dmd->भागer_mode != CXD2880_TNRDMD_DIVERMODE_MAIN)
		वापस -EINVAL;

	ret = tnr_dmd->भागer_sub->io->ग_लिखो_reg(tnr_dmd->भागer_sub->io,
						CXD2880_IO_TGT_SYS,
						0x00, 0x00);
	अगर (ret)
		वापस ret;
	data[0] = 0x14;
	data[1] = 0x00;
	ret = tnr_dmd->भागer_sub->io->ग_लिखो_regs(tnr_dmd->भागer_sub->io,
						CXD2880_IO_TGT_SYS,
						0x55, data, 2);
	अगर (ret)
		वापस ret;

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x00, 0x00);
	अगर (ret)
		वापस ret;
	data[0] = 0x0b;
	data[1] = 0xff;
	ret = tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
				      CXD2880_IO_TGT_SYS,
				      0x53, data, 2);
	अगर (ret)
		वापस ret;
	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x57, 0x01);
	अगर (ret)
		वापस ret;
	data[0] = 0x0b;
	data[1] = 0xff;
	ret = tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
				      CXD2880_IO_TGT_SYS,
				      0x55, data, 2);
	अगर (ret)
		वापस ret;

	ret = tnr_dmd->भागer_sub->io->ग_लिखो_reg(tnr_dmd->भागer_sub->io,
						CXD2880_IO_TGT_SYS,
						0x00, 0x00);
	अगर (ret)
		वापस ret;
	data[0] = 0x14;
	data[1] = 0x00;
	ret = tnr_dmd->भागer_sub->io->ग_लिखो_regs(tnr_dmd->भागer_sub->io,
						 CXD2880_IO_TGT_SYS,
						 0x53, data, 2);
	अगर (ret)
		वापस ret;
	ret = tnr_dmd->भागer_sub->io->ग_लिखो_reg(tnr_dmd->भागer_sub->io,
						CXD2880_IO_TGT_SYS,
						0x57, 0x02);
	अगर (ret)
		वापस ret;

	ret = cxd2880_io_ग_लिखो_multi_regs(tnr_dmd->io,
					  CXD2880_IO_TGT_DMD,
					  x_tune4_seq,
					  ARRAY_SIZE(x_tune4_seq));
	अगर (ret)
		वापस ret;

	वापस cxd2880_io_ग_लिखो_multi_regs(tnr_dmd->भागer_sub->io,
					   CXD2880_IO_TGT_DMD,
					   x_tune4_seq,
					   ARRAY_SIZE(x_tune4_seq));
पूर्ण

अटल पूर्णांक x_sleep1(काष्ठा cxd2880_tnrdmd *tnr_dmd)
अणु
	u8 data[3] = अणु 0 पूर्ण;
	पूर्णांक ret;

	अगर (!tnr_dmd)
		वापस -EINVAL;

	अगर (tnr_dmd->भागer_mode != CXD2880_TNRDMD_DIVERMODE_MAIN)
		वापस -EINVAL;

	ret = cxd2880_io_ग_लिखो_multi_regs(tnr_dmd->io,
					  CXD2880_IO_TGT_SYS,
					  x_sleep1_seq,
					  ARRAY_SIZE(x_sleep1_seq));
	अगर (ret)
		वापस ret;

	data[0] = 0x00;
	data[1] = 0x00;
	ret = tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
				      CXD2880_IO_TGT_SYS,
				      0x53, data, 2);
	अगर (ret)
		वापस ret;

	ret = tnr_dmd->भागer_sub->io->ग_लिखो_reg(tnr_dmd->भागer_sub->io,
						CXD2880_IO_TGT_SYS,
						0x00, 0x00);
	अगर (ret)
		वापस ret;
	data[0] = 0x1f;
	data[1] = 0xff;
	data[2] = 0x03;
	ret = tnr_dmd->भागer_sub->io->ग_लिखो_regs(tnr_dmd->भागer_sub->io,
						 CXD2880_IO_TGT_SYS,
						 0x55, data, 3);
	अगर (ret)
		वापस ret;
	data[0] = 0x00;
	data[1] = 0x00;
	ret = tnr_dmd->भागer_sub->io->ग_लिखो_regs(tnr_dmd->भागer_sub->io,
						 CXD2880_IO_TGT_SYS,
						 0x53, data, 2);
	अगर (ret)
		वापस ret;

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x00, 0x00);
	अगर (ret)
		वापस ret;
	data[0] = 0x1f;
	data[1] = 0xff;

	वापस tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
				       CXD2880_IO_TGT_SYS,
				       0x55, data, 2);
पूर्ण

अटल पूर्णांक x_sleep2(काष्ठा cxd2880_tnrdmd *tnr_dmd)
अणु
	u8 data = 0;
	पूर्णांक ret;

	अगर (!tnr_dmd)
		वापस -EINVAL;

	ret = cxd2880_io_ग_लिखो_multi_regs(tnr_dmd->io,
					  CXD2880_IO_TGT_DMD,
					  x_sleep2_seq1,
					  ARRAY_SIZE(x_sleep2_seq1));
	अगर (ret)
		वापस ret;

	usleep_range(1000, 2000);

	ret = tnr_dmd->io->पढ़ो_regs(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0xb2, &data, 1);
	अगर (ret)
		वापस ret;

	अगर ((data & 0x01) == 0x00)
		वापस -EINVAL;

	वापस cxd2880_io_ग_लिखो_multi_regs(tnr_dmd->io,
					   CXD2880_IO_TGT_SYS,
					   x_sleep2_seq2,
					   ARRAY_SIZE(x_sleep2_seq2));
पूर्ण

अटल पूर्णांक x_sleep3(काष्ठा cxd2880_tnrdmd *tnr_dmd)
अणु
	अगर (!tnr_dmd)
		वापस -EINVAL;

	वापस cxd2880_io_ग_लिखो_multi_regs(tnr_dmd->io,
					   CXD2880_IO_TGT_DMD,
					   x_sleep3_seq,
					   ARRAY_SIZE(x_sleep3_seq));
पूर्ण

अटल पूर्णांक x_sleep4(काष्ठा cxd2880_tnrdmd *tnr_dmd)
अणु
	अगर (!tnr_dmd)
		वापस -EINVAL;

	वापस cxd2880_io_ग_लिखो_multi_regs(tnr_dmd->io,
					   CXD2880_IO_TGT_DMD,
					   x_sleep4_seq,
					   ARRAY_SIZE(x_sleep4_seq));
पूर्ण

अटल पूर्णांक spll_reset(काष्ठा cxd2880_tnrdmd *tnr_dmd,
		      क्रमागत cxd2880_tnrdmd_घड़ीmode घड़ीmode)
अणु
	u8 data[4] = अणु 0 पूर्ण;
	पूर्णांक ret;

	अगर (!tnr_dmd)
		वापस -EINVAL;

	ret = cxd2880_io_ग_लिखो_multi_regs(tnr_dmd->io,
					  CXD2880_IO_TGT_SYS,
					  spll_reset_seq1,
					  ARRAY_SIZE(spll_reset_seq1));
	अगर (ret)
		वापस ret;

	ret = cxd2880_io_ग_लिखो_multi_regs(tnr_dmd->io,
					  CXD2880_IO_TGT_DMD,
					  spll_reset_seq2,
					  ARRAY_SIZE(spll_reset_seq2));
	अगर (ret)
		वापस ret;

	ret = cxd2880_io_ग_लिखो_multi_regs(tnr_dmd->io,
					  CXD2880_IO_TGT_SYS,
					  spll_reset_seq3,
					  ARRAY_SIZE(spll_reset_seq3));
	अगर (ret)
		वापस ret;

	चयन (घड़ीmode) अणु
	हाल CXD2880_TNRDMD_CLOCKMODE_A:
		data[0] = 0x00;
		अवरोध;

	हाल CXD2880_TNRDMD_CLOCKMODE_B:
		data[0] = 0x01;
		अवरोध;

	हाल CXD2880_TNRDMD_CLOCKMODE_C:
		data[0] = 0x02;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण
	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x30, data[0]);
	अगर (ret)
		वापस ret;
	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x22, 0x00);
	अगर (ret)
		वापस ret;

	usleep_range(2000, 3000);

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x00, 0x0a);
	अगर (ret)
		वापस ret;
	ret = tnr_dmd->io->पढ़ो_regs(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x10, data, 1);
	अगर (ret)
		वापस ret;
	अगर ((data[0] & 0x01) == 0x00)
		वापस -EINVAL;

	ret = cxd2880_io_ग_लिखो_multi_regs(tnr_dmd->io,
					  CXD2880_IO_TGT_SYS,
					  spll_reset_seq4,
					  ARRAY_SIZE(spll_reset_seq4));
	अगर (ret)
		वापस ret;

	usleep_range(1000, 2000);

	ret = cxd2880_io_ग_लिखो_multi_regs(tnr_dmd->io,
					  CXD2880_IO_TGT_DMD,
					  spll_reset_seq5,
					  ARRAY_SIZE(spll_reset_seq5));
	अगर (ret)
		वापस ret;

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x00, 0x10);
	अगर (ret)
		वापस ret;

	स_रखो(data, 0x00, माप(data));

	वापस tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
				       CXD2880_IO_TGT_SYS,
				       0x26, data, 4);
पूर्ण

अटल पूर्णांक t_घातer_x(काष्ठा cxd2880_tnrdmd *tnr_dmd, u8 on)
अणु
	u8 data[3] = अणु 0 पूर्ण;
	पूर्णांक ret;

	अगर (!tnr_dmd)
		वापस -EINVAL;

	ret = cxd2880_io_ग_लिखो_multi_regs(tnr_dmd->io,
					  CXD2880_IO_TGT_SYS,
					  t_घातer_x_seq1,
					  ARRAY_SIZE(t_घातer_x_seq1));
	अगर (ret)
		वापस ret;

	ret = cxd2880_io_ग_लिखो_multi_regs(tnr_dmd->io,
					  CXD2880_IO_TGT_DMD,
					  t_घातer_x_seq2,
					  ARRAY_SIZE(t_घातer_x_seq2));
	अगर (ret)
		वापस ret;

	ret = cxd2880_io_ग_लिखो_multi_regs(tnr_dmd->io,
					  CXD2880_IO_TGT_SYS,
					  t_घातer_x_seq3,
					  ARRAY_SIZE(t_घातer_x_seq3));
	अगर (ret)
		वापस ret;

	अगर (on) अणु
		ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
					     CXD2880_IO_TGT_SYS,
					     0x2b, 0x01);
		अगर (ret)
			वापस ret;

		usleep_range(1000, 2000);

		ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
					     CXD2880_IO_TGT_SYS,
					     0x00, 0x0a);
		अगर (ret)
			वापस ret;
		ret = tnr_dmd->io->पढ़ो_regs(tnr_dmd->io,
					     CXD2880_IO_TGT_SYS,
					     0x12, data, 1);
		अगर (ret)
			वापस ret;
		अगर ((data[0] & 0x01) == 0)
			वापस -EINVAL;

		ret = cxd2880_io_ग_लिखो_multi_regs(tnr_dmd->io,
						  CXD2880_IO_TGT_SYS,
						  t_घातer_x_seq4,
						  ARRAY_SIZE(t_घातer_x_seq4));
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		data[0] = 0x03;
		data[1] = 0x00;
		ret = tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
					      CXD2880_IO_TGT_SYS,
					      0x2a, data, 2);
		अगर (ret)
			वापस ret;

		usleep_range(1000, 2000);

		ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
					     CXD2880_IO_TGT_SYS,
					     0x00, 0x0a);
		अगर (ret)
			वापस ret;
		ret = tnr_dmd->io->पढ़ो_regs(tnr_dmd->io,
					     CXD2880_IO_TGT_SYS,
					     0x13, data, 1);
		अगर (ret)
			वापस ret;
		अगर ((data[0] & 0x01) == 0)
			वापस -EINVAL;
	पूर्ण

	ret = cxd2880_io_ग_लिखो_multi_regs(tnr_dmd->io,
					  CXD2880_IO_TGT_SYS,
					  t_घातer_x_seq5,
					  ARRAY_SIZE(t_घातer_x_seq5));
	अगर (ret)
		वापस ret;

	usleep_range(1000, 2000);

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x00, 0x0a);
	अगर (ret)
		वापस ret;
	ret = tnr_dmd->io->पढ़ो_regs(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x11, data, 1);
	अगर (ret)
		वापस ret;
	अगर ((data[0] & 0x01) == 0)
		वापस -EINVAL;

	ret = cxd2880_io_ग_लिखो_multi_regs(tnr_dmd->io,
					  CXD2880_IO_TGT_SYS,
					  t_घातer_x_seq6,
					  ARRAY_SIZE(t_घातer_x_seq6));
	अगर (ret)
		वापस ret;

	usleep_range(1000, 2000);

	ret = cxd2880_io_ग_लिखो_multi_regs(tnr_dmd->io,
					  CXD2880_IO_TGT_DMD,
					  t_घातer_x_seq7,
					  ARRAY_SIZE(t_घातer_x_seq7));
	अगर (ret)
		वापस ret;

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x00, 0x10);
	अगर (ret)
		वापस ret;

	स_रखो(data, 0x00, माप(data));

	वापस tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
				       CXD2880_IO_TGT_SYS,
				       0x27, data, 3);
पूर्ण

काष्ठा cxd2880_tnrdmd_ts_clk_cfg अणु
	u8 srl_clk_mode;
	u8 srl_duty_mode;
	u8 ts_clk_period;
पूर्ण;

अटल पूर्णांक set_ts_clk_mode_and_freq(काष्ठा cxd2880_tnrdmd *tnr_dmd,
				    क्रमागत cxd2880_dtv_sys sys)
अणु
	पूर्णांक ret;
	u8 backwards_compatible = 0;
	काष्ठा cxd2880_tnrdmd_ts_clk_cfg ts_clk_cfg;
	u8 ts_rate_ctrl_off = 0;
	u8 ts_in_off = 0;
	u8 ts_clk_manaul_on = 0;
	u8 data = 0;

	अटल स्थिर काष्ठा cxd2880_tnrdmd_ts_clk_cfg srl_ts_clk_stgs[2][2] = अणु
		अणु
			अणु3, 1, 8,पूर्ण,
			अणु0, 2, 16,पूर्ण
		पूर्ण, अणु
			अणु1, 1, 8,पूर्ण,
			अणु2, 2, 16,पूर्ण
		पूर्ण
	पूर्ण;

	अगर (!tnr_dmd)
		वापस -EINVAL;

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x00);
	अगर (ret)
		वापस ret;

	अगर (tnr_dmd->is_ts_backwards_compatible_mode) अणु
		backwards_compatible = 1;
		ts_rate_ctrl_off = 1;
		ts_in_off = 1;
	पूर्ण अन्यथा अणु
		backwards_compatible = 0;
		ts_rate_ctrl_off = 0;
		ts_in_off = 0;
	पूर्ण

	अगर (tnr_dmd->ts_byte_clk_manual_setting) अणु
		ts_clk_manaul_on = 1;
		ts_rate_ctrl_off = 0;
	पूर्ण

	ret = cxd2880_io_set_reg_bits(tnr_dmd->io,
				      CXD2880_IO_TGT_DMD,
				      0xd3, ts_rate_ctrl_off, 0x01);
	अगर (ret)
		वापस ret;

	ret = cxd2880_io_set_reg_bits(tnr_dmd->io,
				      CXD2880_IO_TGT_DMD,
				      0xde, ts_in_off, 0x01);
	अगर (ret)
		वापस ret;

	ret = cxd2880_io_set_reg_bits(tnr_dmd->io,
				      CXD2880_IO_TGT_DMD,
				      0xda, ts_clk_manaul_on, 0x01);
	अगर (ret)
		वापस ret;

	ts_clk_cfg = srl_ts_clk_stgs[tnr_dmd->srl_ts_clk_mod_cnts]
				    [tnr_dmd->srl_ts_clk_frq];

	अगर (tnr_dmd->ts_byte_clk_manual_setting)
		ts_clk_cfg.ts_clk_period = tnr_dmd->ts_byte_clk_manual_setting;

	ret = cxd2880_io_set_reg_bits(tnr_dmd->io,
				      CXD2880_IO_TGT_DMD,
				      0xc4, ts_clk_cfg.srl_clk_mode, 0x03);
	अगर (ret)
		वापस ret;

	ret = cxd2880_io_set_reg_bits(tnr_dmd->io,
				      CXD2880_IO_TGT_DMD,
				      0xd1, ts_clk_cfg.srl_duty_mode, 0x03);
	अगर (ret)
		वापस ret;

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD, 0xd9,
				     ts_clk_cfg.ts_clk_period);
	अगर (ret)
		वापस ret;

	data = backwards_compatible ? 0x00 : 0x01;

	अगर (sys == CXD2880_DTV_SYS_DVBT) अणु
		ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
					     CXD2880_IO_TGT_DMD,
					     0x00, 0x10);
		अगर (ret)
			वापस ret;

		ret =
		    cxd2880_io_set_reg_bits(tnr_dmd->io,
					    CXD2880_IO_TGT_DMD,
					    0x66, data, 0x01);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक pid_ftr_setting(काष्ठा cxd2880_tnrdmd *tnr_dmd,
			   काष्ठा cxd2880_tnrdmd_pid_ftr_cfg
			   *pid_ftr_cfg)
अणु
	पूर्णांक i;
	पूर्णांक ret;
	u8 data[65];

	अगर (!tnr_dmd)
		वापस -EINVAL;

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x00);
	अगर (ret)
		वापस ret;

	अगर (!pid_ftr_cfg)
		वापस tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
					      CXD2880_IO_TGT_DMD,
					      0x50, 0x02);

	data[0] = pid_ftr_cfg->is_negative ? 0x01 : 0x00;

	क्रम (i = 0; i < 32; i++) अणु
		अगर (pid_ftr_cfg->pid_cfg[i].is_en) अणु
			data[1 + (i * 2)] = (pid_ftr_cfg->pid_cfg[i].pid >> 8) | 0x20;
			data[2 + (i * 2)] =  pid_ftr_cfg->pid_cfg[i].pid & 0xff;
		पूर्ण अन्यथा अणु
			data[1 + (i * 2)] = 0x00;
			data[2 + (i * 2)] = 0x00;
		पूर्ण
	पूर्ण

	वापस tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
				       CXD2880_IO_TGT_DMD,
				       0x50, data, 65);
पूर्ण

अटल पूर्णांक load_cfg_mem(काष्ठा cxd2880_tnrdmd *tnr_dmd)
अणु
	पूर्णांक ret;
	u8 i;

	अगर (!tnr_dmd)
		वापस -EINVAL;

	क्रम (i = 0; i < tnr_dmd->cfg_mem_last_entry; i++) अणु
		ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
					     tnr_dmd->cfg_mem[i].tgt,
					     0x00, tnr_dmd->cfg_mem[i].bank);
		अगर (ret)
			वापस ret;

		ret = cxd2880_io_set_reg_bits(tnr_dmd->io,
					      tnr_dmd->cfg_mem[i].tgt,
					      tnr_dmd->cfg_mem[i].address,
					      tnr_dmd->cfg_mem[i].value,
					      tnr_dmd->cfg_mem[i].bit_mask);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक set_cfg_mem(काष्ठा cxd2880_tnrdmd *tnr_dmd,
		       क्रमागत cxd2880_io_tgt tgt,
		       u8 bank, u8 address, u8 value, u8 bit_mask)
अणु
	u8 i;
	u8 value_stored = 0;

	अगर (!tnr_dmd)
		वापस -EINVAL;

	क्रम (i = 0; i < tnr_dmd->cfg_mem_last_entry; i++) अणु
		अगर (value_stored == 0 &&
		    tnr_dmd->cfg_mem[i].tgt == tgt &&
		    tnr_dmd->cfg_mem[i].bank == bank &&
		    tnr_dmd->cfg_mem[i].address == address) अणु
			tnr_dmd->cfg_mem[i].value &= ~bit_mask;
			tnr_dmd->cfg_mem[i].value |= (value & bit_mask);

			tnr_dmd->cfg_mem[i].bit_mask |= bit_mask;

			value_stored = 1;
		पूर्ण
	पूर्ण

	अगर (value_stored)
		वापस 0;

	अगर (tnr_dmd->cfg_mem_last_entry < CXD2880_TNRDMD_MAX_CFG_MEM_COUNT) अणु
		tnr_dmd->cfg_mem[tnr_dmd->cfg_mem_last_entry].tgt = tgt;
		tnr_dmd->cfg_mem[tnr_dmd->cfg_mem_last_entry].bank = bank;
		tnr_dmd->cfg_mem[tnr_dmd->cfg_mem_last_entry].address = address;
		tnr_dmd->cfg_mem[tnr_dmd->cfg_mem_last_entry].value = (value & bit_mask);
		tnr_dmd->cfg_mem[tnr_dmd->cfg_mem_last_entry].bit_mask = bit_mask;
		tnr_dmd->cfg_mem_last_entry++;
	पूर्ण अन्यथा अणु
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक cxd2880_tnrdmd_create(काष्ठा cxd2880_tnrdmd *tnr_dmd,
			  काष्ठा cxd2880_io *io,
			  काष्ठा cxd2880_tnrdmd_create_param
			  *create_param)
अणु
	अगर (!tnr_dmd || !io || !create_param)
		वापस -EINVAL;

	स_रखो(tnr_dmd, 0, माप(काष्ठा cxd2880_tnrdmd));

	tnr_dmd->io = io;
	tnr_dmd->create_param = *create_param;

	tnr_dmd->भागer_mode = CXD2880_TNRDMD_DIVERMODE_SINGLE;
	tnr_dmd->भागer_sub = शून्य;

	tnr_dmd->srl_ts_clk_mod_cnts = 1;
	tnr_dmd->en_fef_पूर्णांकmtnt_base = 1;
	tnr_dmd->en_fef_पूर्णांकmtnt_lite = 1;
	tnr_dmd->rf_lvl_cmpstn = शून्य;
	tnr_dmd->lna_thrs_tbl_air = शून्य;
	tnr_dmd->lna_thrs_tbl_cable = शून्य;
	atomic_set(&tnr_dmd->cancel, 0);

	वापस 0;
पूर्ण

पूर्णांक cxd2880_tnrdmd_भागer_create(काष्ठा cxd2880_tnrdmd
				*tnr_dmd_मुख्य,
				काष्ठा cxd2880_io *io_मुख्य,
				काष्ठा cxd2880_tnrdmd *tnr_dmd_sub,
				काष्ठा cxd2880_io *io_sub,
				काष्ठा
				cxd2880_tnrdmd_भागer_create_param
				*create_param)
अणु
	काष्ठा cxd2880_tnrdmd_create_param *मुख्य_param, *sub_param;

	अगर (!tnr_dmd_मुख्य || !io_मुख्य || !tnr_dmd_sub || !io_sub ||
	    !create_param)
		वापस -EINVAL;

	स_रखो(tnr_dmd_मुख्य, 0, माप(काष्ठा cxd2880_tnrdmd));
	स_रखो(tnr_dmd_sub, 0, माप(काष्ठा cxd2880_tnrdmd));

	मुख्य_param = &tnr_dmd_मुख्य->create_param;
	sub_param = &tnr_dmd_sub->create_param;

	tnr_dmd_मुख्य->io = io_मुख्य;
	tnr_dmd_मुख्य->भागer_mode = CXD2880_TNRDMD_DIVERMODE_MAIN;
	tnr_dmd_मुख्य->भागer_sub = tnr_dmd_sub;
	tnr_dmd_मुख्य->create_param.en_पूर्णांकernal_lकरो =
	    create_param->en_पूर्णांकernal_lकरो;

	मुख्य_param->ts_output_अगर = create_param->ts_output_अगर;
	मुख्य_param->xtal_share_type = CXD2880_TNRDMD_XTAL_SHARE_MASTER;
	मुख्य_param->xosc_cap = create_param->xosc_cap_मुख्य;
	मुख्य_param->xosc_i = create_param->xosc_i_मुख्य;
	मुख्य_param->is_cxd2881gg = create_param->is_cxd2881gg;
	मुख्य_param->stationary_use = create_param->stationary_use;

	tnr_dmd_sub->io = io_sub;
	tnr_dmd_sub->भागer_mode = CXD2880_TNRDMD_DIVERMODE_SUB;
	tnr_dmd_sub->भागer_sub = शून्य;

	sub_param->en_पूर्णांकernal_lकरो = create_param->en_पूर्णांकernal_lकरो;
	sub_param->ts_output_अगर = create_param->ts_output_अगर;
	sub_param->xtal_share_type = CXD2880_TNRDMD_XTAL_SHARE_SLAVE;
	sub_param->xosc_cap = 0;
	sub_param->xosc_i = create_param->xosc_i_sub;
	sub_param->is_cxd2881gg = create_param->is_cxd2881gg;
	sub_param->stationary_use = create_param->stationary_use;

	tnr_dmd_मुख्य->srl_ts_clk_mod_cnts = 1;
	tnr_dmd_मुख्य->en_fef_पूर्णांकmtnt_base = 1;
	tnr_dmd_मुख्य->en_fef_पूर्णांकmtnt_lite = 1;
	tnr_dmd_मुख्य->rf_lvl_cmpstn = शून्य;
	tnr_dmd_मुख्य->lna_thrs_tbl_air = शून्य;
	tnr_dmd_मुख्य->lna_thrs_tbl_cable = शून्य;

	tnr_dmd_sub->srl_ts_clk_mod_cnts = 1;
	tnr_dmd_sub->en_fef_पूर्णांकmtnt_base = 1;
	tnr_dmd_sub->en_fef_पूर्णांकmtnt_lite = 1;
	tnr_dmd_sub->rf_lvl_cmpstn = शून्य;
	tnr_dmd_sub->lna_thrs_tbl_air = शून्य;
	tnr_dmd_sub->lna_thrs_tbl_cable = शून्य;

	वापस 0;
पूर्ण

पूर्णांक cxd2880_tnrdmd_init1(काष्ठा cxd2880_tnrdmd *tnr_dmd)
अणु
	पूर्णांक ret;

	अगर (!tnr_dmd || tnr_dmd->भागer_mode == CXD2880_TNRDMD_DIVERMODE_SUB)
		वापस -EINVAL;

	tnr_dmd->chip_id = CXD2880_TNRDMD_CHIP_ID_UNKNOWN;
	tnr_dmd->state = CXD2880_TNRDMD_STATE_UNKNOWN;
	tnr_dmd->clk_mode = CXD2880_TNRDMD_CLOCKMODE_UNKNOWN;
	tnr_dmd->frequency_khz = 0;
	tnr_dmd->sys = CXD2880_DTV_SYS_UNKNOWN;
	tnr_dmd->bandwidth = CXD2880_DTV_BW_UNKNOWN;
	tnr_dmd->scan_mode = 0;
	atomic_set(&tnr_dmd->cancel, 0);

	अगर (tnr_dmd->भागer_mode == CXD2880_TNRDMD_DIVERMODE_MAIN) अणु
		tnr_dmd->भागer_sub->chip_id = CXD2880_TNRDMD_CHIP_ID_UNKNOWN;
		tnr_dmd->भागer_sub->state = CXD2880_TNRDMD_STATE_UNKNOWN;
		tnr_dmd->भागer_sub->clk_mode = CXD2880_TNRDMD_CLOCKMODE_UNKNOWN;
		tnr_dmd->भागer_sub->frequency_khz = 0;
		tnr_dmd->भागer_sub->sys = CXD2880_DTV_SYS_UNKNOWN;
		tnr_dmd->भागer_sub->bandwidth = CXD2880_DTV_BW_UNKNOWN;
		tnr_dmd->भागer_sub->scan_mode = 0;
		atomic_set(&tnr_dmd->भागer_sub->cancel, 0);
	पूर्ण

	ret = cxd2880_tnrdmd_chip_id(tnr_dmd, &tnr_dmd->chip_id);
	अगर (ret)
		वापस ret;

	अगर (!CXD2880_TNRDMD_CHIP_ID_VALID(tnr_dmd->chip_id))
		वापस -ENOTTY;

	अगर (tnr_dmd->भागer_mode == CXD2880_TNRDMD_DIVERMODE_MAIN) अणु
		ret =
		    cxd2880_tnrdmd_chip_id(tnr_dmd->भागer_sub,
					   &tnr_dmd->भागer_sub->chip_id);
		अगर (ret)
			वापस ret;

		अगर (!CXD2880_TNRDMD_CHIP_ID_VALID(tnr_dmd->भागer_sub->chip_id))
			वापस -ENOTTY;
	पूर्ण

	ret = p_init1(tnr_dmd);
	अगर (ret)
		वापस ret;

	अगर (tnr_dmd->भागer_mode == CXD2880_TNRDMD_DIVERMODE_MAIN) अणु
		ret = p_init1(tnr_dmd->भागer_sub);
		अगर (ret)
			वापस ret;
	पूर्ण

	usleep_range(1000, 2000);

	अगर (tnr_dmd->भागer_mode == CXD2880_TNRDMD_DIVERMODE_MAIN) अणु
		ret = p_init2(tnr_dmd->भागer_sub);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = p_init2(tnr_dmd);
	अगर (ret)
		वापस ret;

	usleep_range(5000, 6000);

	ret = p_init3(tnr_dmd);
	अगर (ret)
		वापस ret;

	अगर (tnr_dmd->भागer_mode == CXD2880_TNRDMD_DIVERMODE_MAIN) अणु
		ret = p_init3(tnr_dmd->भागer_sub);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = rf_init1(tnr_dmd);
	अगर (ret)
		वापस ret;

	अगर (tnr_dmd->भागer_mode == CXD2880_TNRDMD_DIVERMODE_MAIN)
		ret = rf_init1(tnr_dmd->भागer_sub);

	वापस ret;
पूर्ण

पूर्णांक cxd2880_tnrdmd_init2(काष्ठा cxd2880_tnrdmd *tnr_dmd)
अणु
	u8 cpu_task_completed;
	पूर्णांक ret;

	अगर (!tnr_dmd)
		वापस -EINVAL;

	अगर (tnr_dmd->भागer_mode == CXD2880_TNRDMD_DIVERMODE_SUB)
		वापस -EINVAL;

	ret = cxd2880_tnrdmd_check_पूर्णांकernal_cpu_status(tnr_dmd,
						     &cpu_task_completed);
	अगर (ret)
		वापस ret;

	अगर (!cpu_task_completed)
		वापस -EINVAL;

	ret = rf_init2(tnr_dmd);
	अगर (ret)
		वापस ret;

	अगर (tnr_dmd->भागer_mode == CXD2880_TNRDMD_DIVERMODE_MAIN) अणु
		ret = rf_init2(tnr_dmd->भागer_sub);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = load_cfg_mem(tnr_dmd);
	अगर (ret)
		वापस ret;

	अगर (tnr_dmd->भागer_mode == CXD2880_TNRDMD_DIVERMODE_MAIN) अणु
		ret = load_cfg_mem(tnr_dmd->भागer_sub);
		अगर (ret)
			वापस ret;
	पूर्ण

	tnr_dmd->state = CXD2880_TNRDMD_STATE_SLEEP;

	अगर (tnr_dmd->भागer_mode == CXD2880_TNRDMD_DIVERMODE_MAIN)
		tnr_dmd->भागer_sub->state = CXD2880_TNRDMD_STATE_SLEEP;

	वापस ret;
पूर्ण

पूर्णांक cxd2880_tnrdmd_check_पूर्णांकernal_cpu_status(काष्ठा cxd2880_tnrdmd
					     *tnr_dmd,
					     u8 *task_completed)
अणु
	u16 cpu_status = 0;
	पूर्णांक ret;

	अगर (!tnr_dmd || !task_completed)
		वापस -EINVAL;

	अगर (tnr_dmd->भागer_mode == CXD2880_TNRDMD_DIVERMODE_SUB)
		वापस -EINVAL;

	ret = cxd2880_tnrdmd_mon_पूर्णांकernal_cpu_status(tnr_dmd, &cpu_status);
	अगर (ret)
		वापस ret;

	अगर (tnr_dmd->भागer_mode == CXD2880_TNRDMD_DIVERMODE_SINGLE) अणु
		अगर (cpu_status == 0)
			*task_completed = 1;
		अन्यथा
			*task_completed = 0;

		वापस ret;
	पूर्ण
	अगर (cpu_status != 0) अणु
		*task_completed = 0;
		वापस ret;
	पूर्ण

	ret = cxd2880_tnrdmd_mon_पूर्णांकernal_cpu_status_sub(tnr_dmd, &cpu_status);
	अगर (ret)
		वापस ret;

	अगर (cpu_status == 0)
		*task_completed = 1;
	अन्यथा
		*task_completed = 0;

	वापस ret;
पूर्ण

पूर्णांक cxd2880_tnrdmd_common_tune_setting1(काष्ठा cxd2880_tnrdmd *tnr_dmd,
					क्रमागत cxd2880_dtv_sys sys,
					u32 frequency_khz,
					क्रमागत cxd2880_dtv_bandwidth
					bandwidth, u8 one_seg_opt,
					u8 one_seg_opt_shft_dir)
अणु
	u8 data;
	क्रमागत cxd2880_tnrdmd_घड़ीmode new_clk_mode =
				CXD2880_TNRDMD_CLOCKMODE_A;
	पूर्णांक shअगरt_frequency_khz;
	u8 cpu_task_completed;
	पूर्णांक ret;

	अगर (!tnr_dmd)
		वापस -EINVAL;

	अगर (tnr_dmd->भागer_mode == CXD2880_TNRDMD_DIVERMODE_SUB)
		वापस -EINVAL;

	अगर (tnr_dmd->state != CXD2880_TNRDMD_STATE_SLEEP &&
	    tnr_dmd->state != CXD2880_TNRDMD_STATE_ACTIVE)
		वापस -EINVAL;

	अगर (frequency_khz < 4000)
		वापस -EINVAL;

	ret = cxd2880_tnrdmd_sleep(tnr_dmd);
	अगर (ret)
		वापस ret;

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x00,
				     0x00);
	अगर (ret)
		वापस ret;

	ret = tnr_dmd->io->पढ़ो_regs(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x2b,
				     &data,
				     1);
	अगर (ret)
		वापस ret;

	चयन (sys) अणु
	हाल CXD2880_DTV_SYS_DVBT:
		अगर (data == 0x00) अणु
			ret = t_घातer_x(tnr_dmd, 1);
			अगर (ret)
				वापस ret;

			अगर (tnr_dmd->भागer_mode ==
			    CXD2880_TNRDMD_DIVERMODE_MAIN) अणु
				ret = t_घातer_x(tnr_dmd->भागer_sub, 1);
				अगर (ret)
					वापस ret;
			पूर्ण
		पूर्ण
		अवरोध;

	हाल CXD2880_DTV_SYS_DVBT2:
		अगर (data == 0x01) अणु
			ret = t_घातer_x(tnr_dmd, 0);
			अगर (ret)
				वापस ret;

			अगर (tnr_dmd->भागer_mode ==
			    CXD2880_TNRDMD_DIVERMODE_MAIN) अणु
				ret = t_घातer_x(tnr_dmd->भागer_sub, 0);
				अगर (ret)
					वापस ret;
			पूर्ण
		पूर्ण
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	ret = spll_reset(tnr_dmd, new_clk_mode);
	अगर (ret)
		वापस ret;

	tnr_dmd->clk_mode = new_clk_mode;

	अगर (tnr_dmd->भागer_mode == CXD2880_TNRDMD_DIVERMODE_MAIN) अणु
		ret = spll_reset(tnr_dmd->भागer_sub, new_clk_mode);
		अगर (ret)
			वापस ret;

		tnr_dmd->भागer_sub->clk_mode = new_clk_mode;
	पूर्ण

	ret = load_cfg_mem(tnr_dmd);
	अगर (ret)
		वापस ret;

	अगर (tnr_dmd->भागer_mode == CXD2880_TNRDMD_DIVERMODE_MAIN) अणु
		ret = load_cfg_mem(tnr_dmd->भागer_sub);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (one_seg_opt) अणु
		अगर (tnr_dmd->भागer_mode ==
		    CXD2880_TNRDMD_DIVERMODE_MAIN) अणु
			shअगरt_frequency_khz = 350;
		पूर्ण अन्यथा अणु
			अगर (one_seg_opt_shft_dir)
				shअगरt_frequency_khz = 350;
			अन्यथा
				shअगरt_frequency_khz = -350;

			अगर (tnr_dmd->create_param.xtal_share_type ==
			    CXD2880_TNRDMD_XTAL_SHARE_SLAVE)
				shअगरt_frequency_khz *= -1;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (tnr_dmd->भागer_mode ==
		    CXD2880_TNRDMD_DIVERMODE_MAIN) अणु
			shअगरt_frequency_khz = 150;
		पूर्ण अन्यथा अणु
			चयन (tnr_dmd->create_param.xtal_share_type) अणु
			हाल CXD2880_TNRDMD_XTAL_SHARE_NONE:
			हाल CXD2880_TNRDMD_XTAL_SHARE_EXTREF:
			शेष:
				shअगरt_frequency_khz = 0;
				अवरोध;
			हाल CXD2880_TNRDMD_XTAL_SHARE_MASTER:
				shअगरt_frequency_khz = 150;
				अवरोध;
			हाल CXD2880_TNRDMD_XTAL_SHARE_SLAVE:
				shअगरt_frequency_khz = -150;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	ret =
	    x_tune1(tnr_dmd, sys, frequency_khz, bandwidth,
		    tnr_dmd->is_cable_input, shअगरt_frequency_khz);
	अगर (ret)
		वापस ret;

	अगर (tnr_dmd->भागer_mode == CXD2880_TNRDMD_DIVERMODE_MAIN) अणु
		ret =
		    x_tune1(tnr_dmd->भागer_sub, sys, frequency_khz,
			    bandwidth, tnr_dmd->is_cable_input,
			    -shअगरt_frequency_khz);
		अगर (ret)
			वापस ret;
	पूर्ण

	usleep_range(10000, 11000);

	ret =
	    cxd2880_tnrdmd_check_पूर्णांकernal_cpu_status(tnr_dmd,
					     &cpu_task_completed);
	अगर (ret)
		वापस ret;

	अगर (!cpu_task_completed)
		वापस -EINVAL;

	ret =
	    x_tune2(tnr_dmd, bandwidth, tnr_dmd->clk_mode,
		    shअगरt_frequency_khz);
	अगर (ret)
		वापस ret;

	अगर (tnr_dmd->भागer_mode == CXD2880_TNRDMD_DIVERMODE_MAIN) अणु
		ret =
		    x_tune2(tnr_dmd->भागer_sub, bandwidth,
			    tnr_dmd->भागer_sub->clk_mode,
			    -shअगरt_frequency_khz);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (tnr_dmd->create_param.ts_output_अगर == CXD2880_TNRDMD_TSOUT_IF_TS) अणु
		ret = set_ts_clk_mode_and_freq(tnr_dmd, sys);
	पूर्ण अन्यथा अणु
		काष्ठा cxd2880_tnrdmd_pid_ftr_cfg *pid_ftr_cfg;

		अगर (tnr_dmd->pid_ftr_cfg_en)
			pid_ftr_cfg = &tnr_dmd->pid_ftr_cfg;
		अन्यथा
			pid_ftr_cfg = शून्य;

		ret = pid_ftr_setting(tnr_dmd, pid_ftr_cfg);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक cxd2880_tnrdmd_common_tune_setting2(काष्ठा cxd2880_tnrdmd
					*tnr_dmd,
					क्रमागत cxd2880_dtv_sys sys,
					u8 en_fef_पूर्णांकmtnt_ctrl)
अणु
	पूर्णांक ret;

	अगर (!tnr_dmd)
		वापस -EINVAL;

	अगर (tnr_dmd->भागer_mode == CXD2880_TNRDMD_DIVERMODE_SUB)
		वापस -EINVAL;

	अगर (tnr_dmd->state != CXD2880_TNRDMD_STATE_SLEEP &&
	    tnr_dmd->state != CXD2880_TNRDMD_STATE_ACTIVE)
		वापस -EINVAL;

	ret = x_tune3(tnr_dmd, sys, en_fef_पूर्णांकmtnt_ctrl);
	अगर (ret)
		वापस ret;

	अगर (tnr_dmd->भागer_mode == CXD2880_TNRDMD_DIVERMODE_MAIN) अणु
		ret = x_tune3(tnr_dmd->भागer_sub, sys, en_fef_पूर्णांकmtnt_ctrl);
		अगर (ret)
			वापस ret;
		ret = x_tune4(tnr_dmd);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस cxd2880_tnrdmd_set_ts_output(tnr_dmd, 1);
पूर्ण

पूर्णांक cxd2880_tnrdmd_sleep(काष्ठा cxd2880_tnrdmd *tnr_dmd)
अणु
	पूर्णांक ret;

	अगर (!tnr_dmd)
		वापस -EINVAL;

	अगर (tnr_dmd->भागer_mode == CXD2880_TNRDMD_DIVERMODE_SUB)
		वापस -EINVAL;

	अगर (tnr_dmd->state == CXD2880_TNRDMD_STATE_SLEEP)
		वापस 0;

	अगर (tnr_dmd->state != CXD2880_TNRDMD_STATE_ACTIVE)
		वापस -EINVAL;

	ret = cxd2880_tnrdmd_set_ts_output(tnr_dmd, 0);
	अगर (ret)
		वापस ret;

	अगर (tnr_dmd->भागer_mode == CXD2880_TNRDMD_DIVERMODE_MAIN) अणु
		ret = x_sleep1(tnr_dmd);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = x_sleep2(tnr_dmd);
	अगर (ret)
		वापस ret;

	अगर (tnr_dmd->भागer_mode == CXD2880_TNRDMD_DIVERMODE_MAIN) अणु
		ret = x_sleep2(tnr_dmd->भागer_sub);
		अगर (ret)
			वापस ret;
	पूर्ण

	चयन (tnr_dmd->sys) अणु
	हाल CXD2880_DTV_SYS_DVBT:
		ret = cxd2880_tnrdmd_dvbt_sleep_setting(tnr_dmd);
		अगर (ret)
			वापस ret;
		अवरोध;

	हाल CXD2880_DTV_SYS_DVBT2:
		ret = cxd2880_tnrdmd_dvbt2_sleep_setting(tnr_dmd);
		अगर (ret)
			वापस ret;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	ret = x_sleep3(tnr_dmd);
	अगर (ret)
		वापस ret;

	अगर (tnr_dmd->भागer_mode == CXD2880_TNRDMD_DIVERMODE_MAIN) अणु
		ret = x_sleep3(tnr_dmd->भागer_sub);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = x_sleep4(tnr_dmd);
	अगर (ret)
		वापस ret;

	अगर (tnr_dmd->भागer_mode == CXD2880_TNRDMD_DIVERMODE_MAIN) अणु
		ret = x_sleep4(tnr_dmd->भागer_sub);
		अगर (ret)
			वापस ret;
	पूर्ण

	tnr_dmd->state = CXD2880_TNRDMD_STATE_SLEEP;
	tnr_dmd->frequency_khz = 0;
	tnr_dmd->sys = CXD2880_DTV_SYS_UNKNOWN;
	tnr_dmd->bandwidth = CXD2880_DTV_BW_UNKNOWN;

	अगर (tnr_dmd->भागer_mode == CXD2880_TNRDMD_DIVERMODE_MAIN) अणु
		tnr_dmd->भागer_sub->state = CXD2880_TNRDMD_STATE_SLEEP;
		tnr_dmd->भागer_sub->frequency_khz = 0;
		tnr_dmd->भागer_sub->sys = CXD2880_DTV_SYS_UNKNOWN;
		tnr_dmd->भागer_sub->bandwidth = CXD2880_DTV_BW_UNKNOWN;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक cxd2880_tnrdmd_set_cfg(काष्ठा cxd2880_tnrdmd *tnr_dmd,
			   क्रमागत cxd2880_tnrdmd_cfg_id id,
			   पूर्णांक value)
अणु
	पूर्णांक ret = 0;
	u8 data[2] = अणु 0 पूर्ण;
	u8 need_sub_setting = 0;

	अगर (!tnr_dmd)
		वापस -EINVAL;

	अगर (tnr_dmd->state != CXD2880_TNRDMD_STATE_SLEEP &&
	    tnr_dmd->state != CXD2880_TNRDMD_STATE_ACTIVE)
		वापस -EINVAL;

	चयन (id) अणु
	हाल CXD2880_TNRDMD_CFG_OUTPUT_SEL_MSB:
		अगर (tnr_dmd->state != CXD2880_TNRDMD_STATE_SLEEP)
			वापस -EINVAL;

		ret =
		    cxd2880_tnrdmd_set_and_save_reg_bits(tnr_dmd,
							 CXD2880_IO_TGT_DMD,
							 0x00, 0xc4,
							 value ? 0x00 : 0x10,
							 0x10);
		अगर (ret)
			वापस ret;
		अवरोध;

	हाल CXD2880_TNRDMD_CFG_TSVALID_ACTIVE_HI:
		अगर (tnr_dmd->state != CXD2880_TNRDMD_STATE_SLEEP)
			वापस -EINVAL;

		ret =
		    cxd2880_tnrdmd_set_and_save_reg_bits(tnr_dmd,
							 CXD2880_IO_TGT_DMD,
							 0x00, 0xc5,
							 value ? 0x00 : 0x02,
							 0x02);
		अगर (ret)
			वापस ret;
		अवरोध;

	हाल CXD2880_TNRDMD_CFG_TSSYNC_ACTIVE_HI:
		अगर (tnr_dmd->state != CXD2880_TNRDMD_STATE_SLEEP)
			वापस -EINVAL;

		ret =
		    cxd2880_tnrdmd_set_and_save_reg_bits(tnr_dmd,
							 CXD2880_IO_TGT_DMD,
							 0x00, 0xc5,
							 value ? 0x00 : 0x04,
							 0x04);
		अगर (ret)
			वापस ret;
		अवरोध;

	हाल CXD2880_TNRDMD_CFG_TSERR_ACTIVE_HI:
		अगर (tnr_dmd->state != CXD2880_TNRDMD_STATE_SLEEP)
			वापस -EINVAL;

		ret =
		    cxd2880_tnrdmd_set_and_save_reg_bits(tnr_dmd,
							 CXD2880_IO_TGT_DMD,
							 0x00, 0xcb,
							 value ? 0x00 : 0x01,
							 0x01);
		अगर (ret)
			वापस ret;
		अवरोध;

	हाल CXD2880_TNRDMD_CFG_LATCH_ON_POSEDGE:
		अगर (tnr_dmd->state != CXD2880_TNRDMD_STATE_SLEEP)
			वापस -EINVAL;

		ret =
		    cxd2880_tnrdmd_set_and_save_reg_bits(tnr_dmd,
							 CXD2880_IO_TGT_DMD,
							 0x00, 0xc5,
							 value ? 0x01 : 0x00,
							 0x01);
		अगर (ret)
			वापस ret;
		अवरोध;

	हाल CXD2880_TNRDMD_CFG_TSCLK_CONT:
		अगर (tnr_dmd->state != CXD2880_TNRDMD_STATE_SLEEP)
			वापस -EINVAL;

		tnr_dmd->srl_ts_clk_mod_cnts = value ? 0x01 : 0x00;
		अवरोध;

	हाल CXD2880_TNRDMD_CFG_TSCLK_MASK:
		अगर (tnr_dmd->state != CXD2880_TNRDMD_STATE_SLEEP)
			वापस -EINVAL;

		अगर (value < 0 || value > 0x1f)
			वापस -EINVAL;

		ret =
		    cxd2880_tnrdmd_set_and_save_reg_bits(tnr_dmd,
							 CXD2880_IO_TGT_DMD,
							 0x00, 0xc6, value,
							 0x1f);
		अगर (ret)
			वापस ret;
		अवरोध;

	हाल CXD2880_TNRDMD_CFG_TSVALID_MASK:
		अगर (tnr_dmd->state != CXD2880_TNRDMD_STATE_SLEEP)
			वापस -EINVAL;

		अगर (value < 0 || value > 0x1f)
			वापस -EINVAL;

		ret =
		    cxd2880_tnrdmd_set_and_save_reg_bits(tnr_dmd,
							 CXD2880_IO_TGT_DMD,
							 0x00, 0xc8, value,
							 0x1f);
		अगर (ret)
			वापस ret;
		अवरोध;

	हाल CXD2880_TNRDMD_CFG_TSERR_MASK:
		अगर (tnr_dmd->state != CXD2880_TNRDMD_STATE_SLEEP)
			वापस -EINVAL;

		अगर (value < 0 || value > 0x1f)
			वापस -EINVAL;

		ret =
		    cxd2880_tnrdmd_set_and_save_reg_bits(tnr_dmd,
							 CXD2880_IO_TGT_DMD,
							 0x00, 0xc9, value,
							 0x1f);
		अगर (ret)
			वापस ret;
		अवरोध;

	हाल CXD2880_TNRDMD_CFG_TSERR_VALID_DIS:
		अगर (tnr_dmd->state != CXD2880_TNRDMD_STATE_SLEEP)
			वापस -EINVAL;

		ret =
		    cxd2880_tnrdmd_set_and_save_reg_bits(tnr_dmd,
							 CXD2880_IO_TGT_DMD,
							 0x00, 0x91,
							 value ? 0x01 : 0x00,
							 0x01);
		अगर (ret)
			वापस ret;
		अवरोध;

	हाल CXD2880_TNRDMD_CFG_TSPIN_CURRENT:
		अगर (tnr_dmd->state != CXD2880_TNRDMD_STATE_SLEEP)
			वापस -EINVAL;

		ret =
		    cxd2880_tnrdmd_set_and_save_reg_bits(tnr_dmd,
							 CXD2880_IO_TGT_SYS,
							 0x00, 0x51, value,
							 0x3f);
		अगर (ret)
			वापस ret;
		अवरोध;

	हाल CXD2880_TNRDMD_CFG_TSPIN_PULLUP_MANUAL:
		अगर (tnr_dmd->state != CXD2880_TNRDMD_STATE_SLEEP)
			वापस -EINVAL;

		ret =
		    cxd2880_tnrdmd_set_and_save_reg_bits(tnr_dmd,
							 CXD2880_IO_TGT_SYS,
							 0x00, 0x50,
							 value ? 0x80 : 0x00,
							 0x80);
		अगर (ret)
			वापस ret;
		अवरोध;

	हाल CXD2880_TNRDMD_CFG_TSPIN_PULLUP:
		अगर (tnr_dmd->state != CXD2880_TNRDMD_STATE_SLEEP)
			वापस -EINVAL;

		ret =
		    cxd2880_tnrdmd_set_and_save_reg_bits(tnr_dmd,
							 CXD2880_IO_TGT_SYS,
							 0x00, 0x50, value,
							 0x3f);
		अगर (ret)
			वापस ret;
		अवरोध;

	हाल CXD2880_TNRDMD_CFG_TSCLK_FREQ:
		अगर (tnr_dmd->state != CXD2880_TNRDMD_STATE_SLEEP)
			वापस -EINVAL;

		अगर (value < 0 || value > 1)
			वापस -EINVAL;

		tnr_dmd->srl_ts_clk_frq =
		    (क्रमागत cxd2880_tnrdmd_serial_ts_clk)value;
		अवरोध;

	हाल CXD2880_TNRDMD_CFG_TSBYTECLK_MANUAL:
		अगर (tnr_dmd->state != CXD2880_TNRDMD_STATE_SLEEP)
			वापस -EINVAL;

		अगर (value < 0 || value > 0xff)
			वापस -EINVAL;

		tnr_dmd->ts_byte_clk_manual_setting = value;

		अवरोध;

	हाल CXD2880_TNRDMD_CFG_TS_PACKET_GAP:
		अगर (tnr_dmd->state != CXD2880_TNRDMD_STATE_SLEEP)
			वापस -EINVAL;

		अगर (value < 0 || value > 7)
			वापस -EINVAL;

		ret =
		    cxd2880_tnrdmd_set_and_save_reg_bits(tnr_dmd,
							 CXD2880_IO_TGT_DMD,
							 0x00, 0xd6, value,
							 0x07);
		अगर (ret)
			वापस ret;

		अवरोध;

	हाल CXD2880_TNRDMD_CFG_TS_BACKWARDS_COMPATIBLE:
		अगर (tnr_dmd->state != CXD2880_TNRDMD_STATE_SLEEP)
			वापस -EINVAL;

		tnr_dmd->is_ts_backwards_compatible_mode = value ? 1 : 0;

		अवरोध;

	हाल CXD2880_TNRDMD_CFG_PWM_VALUE:
		अगर (value < 0 || value > 0x1000)
			वापस -EINVAL;

		ret =
		    cxd2880_tnrdmd_set_and_save_reg_bits(tnr_dmd,
							 CXD2880_IO_TGT_DMD,
							 0x00, 0x22,
							 value ? 0x01 : 0x00,
							 0x01);
		अगर (ret)
			वापस ret;

		data[0] = (value >> 8) & 0x1f;
		data[1] = value & 0xff;

		ret =
		    cxd2880_tnrdmd_set_and_save_reg_bits(tnr_dmd,
							 CXD2880_IO_TGT_DMD,
							 0x00, 0x23,
							 data[0], 0x1f);
		अगर (ret)
			वापस ret;

		ret =
		    cxd2880_tnrdmd_set_and_save_reg_bits(tnr_dmd,
							 CXD2880_IO_TGT_DMD,
							 0x00, 0x24,
							 data[1], 0xff);
		अगर (ret)
			वापस ret;

		अवरोध;

	हाल CXD2880_TNRDMD_CFG_INTERRUPT:
		data[0] = (value >> 8) & 0xff;
		data[1] = value & 0xff;
		ret =
		    cxd2880_tnrdmd_set_and_save_reg_bits(tnr_dmd,
							 CXD2880_IO_TGT_SYS,
							 0x00, 0x48, data[0],
							 0xff);
		अगर (ret)
			वापस ret;
		ret =
		    cxd2880_tnrdmd_set_and_save_reg_bits(tnr_dmd,
							 CXD2880_IO_TGT_SYS,
							 0x00, 0x49, data[1],
							 0xff);
		अगर (ret)
			वापस ret;
		अवरोध;

	हाल CXD2880_TNRDMD_CFG_INTERRUPT_LOCK_SEL:
		data[0] = value & 0x07;
		ret =
		    cxd2880_tnrdmd_set_and_save_reg_bits(tnr_dmd,
							 CXD2880_IO_TGT_SYS,
							 0x00, 0x4a, data[0],
							 0x07);
		अगर (ret)
			वापस ret;
		अवरोध;

	हाल CXD2880_TNRDMD_CFG_INTERRUPT_INV_LOCK_SEL:
		data[0] = (value & 0x07) << 3;
		ret =
		    cxd2880_tnrdmd_set_and_save_reg_bits(tnr_dmd,
							 CXD2880_IO_TGT_SYS,
							 0x00, 0x4a, data[0],
							 0x38);
		अगर (ret)
			वापस ret;
		अवरोध;

	हाल CXD2880_TNRDMD_CFG_FIXED_CLOCKMODE:
		अगर (value < CXD2880_TNRDMD_CLOCKMODE_UNKNOWN ||
		    value > CXD2880_TNRDMD_CLOCKMODE_C)
			वापस -EINVAL;
		tnr_dmd->fixed_clk_mode = (क्रमागत cxd2880_tnrdmd_घड़ीmode)value;
		अवरोध;

	हाल CXD2880_TNRDMD_CFG_CABLE_INPUT:
		tnr_dmd->is_cable_input = value ? 1 : 0;
		अवरोध;

	हाल CXD2880_TNRDMD_CFG_DVBT2_FEF_INTERMITTENT_BASE:
		tnr_dmd->en_fef_पूर्णांकmtnt_base = value ? 1 : 0;
		अवरोध;

	हाल CXD2880_TNRDMD_CFG_DVBT2_FEF_INTERMITTENT_LITE:
		tnr_dmd->en_fef_पूर्णांकmtnt_lite = value ? 1 : 0;
		अवरोध;

	हाल CXD2880_TNRDMD_CFG_TS_BUF_ALMOST_EMPTY_THRS:
		data[0] = (value >> 8) & 0x07;
		data[1] = value & 0xff;
		ret =
		    cxd2880_tnrdmd_set_and_save_reg_bits(tnr_dmd,
							 CXD2880_IO_TGT_DMD,
							 0x00, 0x99, data[0],
							 0x07);
		अगर (ret)
			वापस ret;
		ret =
		    cxd2880_tnrdmd_set_and_save_reg_bits(tnr_dmd,
							 CXD2880_IO_TGT_DMD,
							 0x00, 0x9a, data[1],
							 0xff);
		अगर (ret)
			वापस ret;
		अवरोध;

	हाल CXD2880_TNRDMD_CFG_TS_BUF_ALMOST_FULL_THRS:
		data[0] = (value >> 8) & 0x07;
		data[1] = value & 0xff;
		ret =
		    cxd2880_tnrdmd_set_and_save_reg_bits(tnr_dmd,
							 CXD2880_IO_TGT_DMD,
							 0x00, 0x9b, data[0],
							 0x07);
		अगर (ret)
			वापस ret;
		ret =
		    cxd2880_tnrdmd_set_and_save_reg_bits(tnr_dmd,
							 CXD2880_IO_TGT_DMD,
							 0x00, 0x9c, data[1],
							 0xff);
		अगर (ret)
			वापस ret;
		अवरोध;

	हाल CXD2880_TNRDMD_CFG_TS_BUF_RRDY_THRS:
		data[0] = (value >> 8) & 0x07;
		data[1] = value & 0xff;
		ret =
		    cxd2880_tnrdmd_set_and_save_reg_bits(tnr_dmd,
							 CXD2880_IO_TGT_DMD,
							 0x00, 0x9d, data[0],
							 0x07);
		अगर (ret)
			वापस ret;
		ret =
		    cxd2880_tnrdmd_set_and_save_reg_bits(tnr_dmd,
							 CXD2880_IO_TGT_DMD,
							 0x00, 0x9e, data[1],
							 0xff);
		अगर (ret)
			वापस ret;
		अवरोध;

	हाल CXD2880_TNRDMD_CFG_BLINDTUNE_DVBT2_FIRST:
		tnr_dmd->blind_tune_dvbt2_first = value ? 1 : 0;
		अवरोध;

	हाल CXD2880_TNRDMD_CFG_DVBT_BERN_PERIOD:
		अगर (value < 0 || value > 31)
			वापस -EINVAL;

		ret =
		    cxd2880_tnrdmd_set_and_save_reg_bits(tnr_dmd,
							 CXD2880_IO_TGT_DMD,
							 0x10, 0x60,
							 value & 0x1f, 0x1f);
		अगर (ret)
			वापस ret;
		अवरोध;

	हाल CXD2880_TNRDMD_CFG_DVBT_VBER_PERIOD:
		अगर (value < 0 || value > 7)
			वापस -EINVAL;

		ret =
		    cxd2880_tnrdmd_set_and_save_reg_bits(tnr_dmd,
							 CXD2880_IO_TGT_DMD,
							 0x10, 0x6f,
							 value & 0x07, 0x07);
		अगर (ret)
			वापस ret;
		अवरोध;

	हाल CXD2880_TNRDMD_CFG_DVBT2_BBER_MES:
		अगर (value < 0 || value > 15)
			वापस -EINVAL;

		ret =
		    cxd2880_tnrdmd_set_and_save_reg_bits(tnr_dmd,
							 CXD2880_IO_TGT_DMD,
							 0x20, 0x72,
							 value & 0x0f, 0x0f);
		अगर (ret)
			वापस ret;
		अवरोध;

	हाल CXD2880_TNRDMD_CFG_DVBT2_LBER_MES:
		अगर (value < 0 || value > 15)
			वापस -EINVAL;

		ret =
		    cxd2880_tnrdmd_set_and_save_reg_bits(tnr_dmd,
							 CXD2880_IO_TGT_DMD,
							 0x20, 0x6f,
							 value & 0x0f, 0x0f);
		अगर (ret)
			वापस ret;
		अवरोध;

	हाल CXD2880_TNRDMD_CFG_DVBT_PER_MES:
		अगर (value < 0 || value > 15)
			वापस -EINVAL;

		ret =
		    cxd2880_tnrdmd_set_and_save_reg_bits(tnr_dmd,
							 CXD2880_IO_TGT_DMD,
							 0x10, 0x5c,
							 value & 0x0f, 0x0f);
		अगर (ret)
			वापस ret;
		अवरोध;

	हाल CXD2880_TNRDMD_CFG_DVBT2_PER_MES:
		अगर (value < 0 || value > 15)
			वापस -EINVAL;

		ret =
		    cxd2880_tnrdmd_set_and_save_reg_bits(tnr_dmd,
							 CXD2880_IO_TGT_DMD,
							 0x24, 0xdc,
							 value & 0x0f, 0x0f);
		अगर (ret)
			वापस ret;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (need_sub_setting &&
	    tnr_dmd->भागer_mode == CXD2880_TNRDMD_DIVERMODE_MAIN)
		ret = cxd2880_tnrdmd_set_cfg(tnr_dmd->भागer_sub, id, value);

	वापस ret;
पूर्ण

पूर्णांक cxd2880_tnrdmd_gpio_set_cfg(काष्ठा cxd2880_tnrdmd *tnr_dmd,
				u8 id,
				u8 en,
				क्रमागत cxd2880_tnrdmd_gpio_mode mode,
				u8 खोलो_drain, u8 invert)
अणु
	पूर्णांक ret;

	अगर (!tnr_dmd)
		वापस -EINVAL;

	अगर (id > 2)
		वापस -EINVAL;

	अगर (mode > CXD2880_TNRDMD_GPIO_MODE_EEW)
		वापस -EINVAL;

	अगर (tnr_dmd->state != CXD2880_TNRDMD_STATE_SLEEP &&
	    tnr_dmd->state != CXD2880_TNRDMD_STATE_ACTIVE)
		वापस -EINVAL;

	ret =
	    cxd2880_tnrdmd_set_and_save_reg_bits(tnr_dmd, CXD2880_IO_TGT_SYS,
						 0x00, 0x40 + id, mode,
						 0x0f);
	अगर (ret)
		वापस ret;

	ret =
	    cxd2880_tnrdmd_set_and_save_reg_bits(tnr_dmd, CXD2880_IO_TGT_SYS,
						 0x00, 0x43,
						 खोलो_drain ? (1 << id) : 0,
						 1 << id);
	अगर (ret)
		वापस ret;

	ret =
	    cxd2880_tnrdmd_set_and_save_reg_bits(tnr_dmd, CXD2880_IO_TGT_SYS,
						 0x00, 0x44,
						 invert ? (1 << id) : 0,
						 1 << id);
	अगर (ret)
		वापस ret;

	वापस cxd2880_tnrdmd_set_and_save_reg_bits(tnr_dmd,
						    CXD2880_IO_TGT_SYS,
						    0x00, 0x45,
						    en ? 0 : (1 << id),
						    1 << id);
पूर्ण

पूर्णांक cxd2880_tnrdmd_gpio_set_cfg_sub(काष्ठा cxd2880_tnrdmd *tnr_dmd,
				    u8 id,
				    u8 en,
				    क्रमागत cxd2880_tnrdmd_gpio_mode
				    mode, u8 खोलो_drain, u8 invert)
अणु
	अगर (!tnr_dmd)
		वापस -EINVAL;

	अगर (tnr_dmd->भागer_mode != CXD2880_TNRDMD_DIVERMODE_MAIN)
		वापस -EINVAL;

	वापस cxd2880_tnrdmd_gpio_set_cfg(tnr_dmd->भागer_sub, id, en, mode,
					   खोलो_drain, invert);
पूर्ण

पूर्णांक cxd2880_tnrdmd_gpio_पढ़ो(काष्ठा cxd2880_tnrdmd *tnr_dmd,
			     u8 id, u8 *value)
अणु
	u8 data = 0;
	पूर्णांक ret;

	अगर (!tnr_dmd || !value)
		वापस -EINVAL;

	अगर (id > 2)
		वापस -EINVAL;

	अगर (tnr_dmd->state != CXD2880_TNRDMD_STATE_SLEEP &&
	    tnr_dmd->state != CXD2880_TNRDMD_STATE_ACTIVE)
		वापस -EINVAL;

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x00, 0x0a);
	अगर (ret)
		वापस ret;
	ret = tnr_dmd->io->पढ़ो_regs(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x20, &data, 1);
	अगर (ret)
		वापस ret;

	*value = (data >> id) & 0x01;

	वापस 0;
पूर्ण

पूर्णांक cxd2880_tnrdmd_gpio_पढ़ो_sub(काष्ठा cxd2880_tnrdmd *tnr_dmd,
				 u8 id, u8 *value)
अणु
	अगर (!tnr_dmd)
		वापस -EINVAL;

	अगर (tnr_dmd->भागer_mode != CXD2880_TNRDMD_DIVERMODE_MAIN)
		वापस -EINVAL;

	वापस cxd2880_tnrdmd_gpio_पढ़ो(tnr_dmd->भागer_sub, id, value);
पूर्ण

पूर्णांक cxd2880_tnrdmd_gpio_ग_लिखो(काष्ठा cxd2880_tnrdmd *tnr_dmd,
			      u8 id, u8 value)
अणु
	अगर (!tnr_dmd)
		वापस -EINVAL;

	अगर (id > 2)
		वापस -EINVAL;

	अगर (tnr_dmd->state != CXD2880_TNRDMD_STATE_SLEEP &&
	    tnr_dmd->state != CXD2880_TNRDMD_STATE_ACTIVE)
		वापस -EINVAL;

	वापस cxd2880_tnrdmd_set_and_save_reg_bits(tnr_dmd,
						    CXD2880_IO_TGT_SYS,
						    0x00, 0x46,
						    value ? (1 << id) : 0,
						    1 << id);
पूर्ण

पूर्णांक cxd2880_tnrdmd_gpio_ग_लिखो_sub(काष्ठा cxd2880_tnrdmd *tnr_dmd,
				  u8 id, u8 value)
अणु
	अगर (!tnr_dmd)
		वापस -EINVAL;

	अगर (tnr_dmd->भागer_mode != CXD2880_TNRDMD_DIVERMODE_MAIN)
		वापस -EINVAL;

	वापस cxd2880_tnrdmd_gpio_ग_लिखो(tnr_dmd->भागer_sub, id, value);
पूर्ण

पूर्णांक cxd2880_tnrdmd_पूर्णांकerrupt_पढ़ो(काष्ठा cxd2880_tnrdmd *tnr_dmd,
				  u16 *value)
अणु
	पूर्णांक ret;
	u8 data[2] = अणु 0 पूर्ण;

	अगर (!tnr_dmd || !value)
		वापस -EINVAL;

	अगर (tnr_dmd->state != CXD2880_TNRDMD_STATE_SLEEP &&
	    tnr_dmd->state != CXD2880_TNRDMD_STATE_ACTIVE)
		वापस -EINVAL;

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x00, 0x0a);
	अगर (ret)
		वापस ret;
	ret = tnr_dmd->io->पढ़ो_regs(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x15, data, 2);
	अगर (ret)
		वापस ret;

	*value = (data[0] << 8) | data[1];

	वापस 0;
पूर्ण

पूर्णांक cxd2880_tnrdmd_पूर्णांकerrupt_clear(काष्ठा cxd2880_tnrdmd *tnr_dmd,
				   u16 value)
अणु
	पूर्णांक ret;
	u8 data[2] = अणु 0 पूर्ण;

	अगर (!tnr_dmd)
		वापस -EINVAL;

	अगर (tnr_dmd->state != CXD2880_TNRDMD_STATE_SLEEP &&
	    tnr_dmd->state != CXD2880_TNRDMD_STATE_ACTIVE)
		वापस -EINVAL;

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x00, 0x00);
	अगर (ret)
		वापस ret;

	data[0] = (value >> 8) & 0xff;
	data[1] = value & 0xff;

	वापस tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
				       CXD2880_IO_TGT_SYS,
				       0x3c, data, 2);
पूर्ण

पूर्णांक cxd2880_tnrdmd_ts_buf_clear(काष्ठा cxd2880_tnrdmd *tnr_dmd,
				u8 clear_overflow_flag,
				u8 clear_underflow_flag,
				u8 clear_buf)
अणु
	पूर्णांक ret;
	u8 data[2] = अणु 0 पूर्ण;

	अगर (!tnr_dmd)
		वापस -EINVAL;

	अगर (tnr_dmd->भागer_mode == CXD2880_TNRDMD_DIVERMODE_SUB)
		वापस -EINVAL;

	अगर (tnr_dmd->state != CXD2880_TNRDMD_STATE_SLEEP &&
	    tnr_dmd->state != CXD2880_TNRDMD_STATE_ACTIVE)
		वापस -EINVAL;

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x00);
	अगर (ret)
		वापस ret;

	data[0] = clear_overflow_flag ? 0x02 : 0x00;
	data[0] |= clear_underflow_flag ? 0x01 : 0x00;
	data[1] = clear_buf ? 0x01 : 0x00;

	वापस tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
				       CXD2880_IO_TGT_DMD,
				       0x9f, data, 2);
पूर्ण

पूर्णांक cxd2880_tnrdmd_chip_id(काष्ठा cxd2880_tnrdmd *tnr_dmd,
			   क्रमागत cxd2880_tnrdmd_chip_id *chip_id)
अणु
	पूर्णांक ret;
	u8 data = 0;

	अगर (!tnr_dmd || !chip_id)
		वापस -EINVAL;

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x00, 0x00);
	अगर (ret)
		वापस ret;
	ret = tnr_dmd->io->पढ़ो_regs(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0xfd, &data, 1);
	अगर (ret)
		वापस ret;

	*chip_id = (क्रमागत cxd2880_tnrdmd_chip_id)data;

	वापस 0;
पूर्ण

पूर्णांक cxd2880_tnrdmd_set_and_save_reg_bits(काष्ठा cxd2880_tnrdmd
					 *tnr_dmd,
					 क्रमागत cxd2880_io_tgt tgt,
					 u8 bank, u8 address,
					 u8 value, u8 bit_mask)
अणु
	पूर्णांक ret;

	अगर (!tnr_dmd)
		वापस -EINVAL;

	अगर (tnr_dmd->state != CXD2880_TNRDMD_STATE_SLEEP &&
	    tnr_dmd->state != CXD2880_TNRDMD_STATE_ACTIVE)
		वापस -EINVAL;

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io, tgt, 0x00, bank);
	अगर (ret)
		वापस ret;

	ret = cxd2880_io_set_reg_bits(tnr_dmd->io,
				      tgt, address, value, bit_mask);
	अगर (ret)
		वापस ret;

	वापस set_cfg_mem(tnr_dmd, tgt, bank, address, value, bit_mask);
पूर्ण

पूर्णांक cxd2880_tnrdmd_set_scan_mode(काष्ठा cxd2880_tnrdmd *tnr_dmd,
				 क्रमागत cxd2880_dtv_sys sys,
				 u8 scan_mode_end)
अणु
	अगर (!tnr_dmd)
		वापस -EINVAL;

	अगर (tnr_dmd->state != CXD2880_TNRDMD_STATE_SLEEP &&
	    tnr_dmd->state != CXD2880_TNRDMD_STATE_ACTIVE)
		वापस -EINVAL;

	tnr_dmd->scan_mode = scan_mode_end;

	अगर (tnr_dmd->भागer_mode == CXD2880_TNRDMD_DIVERMODE_MAIN)
		वापस cxd2880_tnrdmd_set_scan_mode(tnr_dmd->भागer_sub, sys,
						    scan_mode_end);
	अन्यथा
		वापस 0;
पूर्ण

पूर्णांक cxd2880_tnrdmd_set_pid_ftr(काष्ठा cxd2880_tnrdmd *tnr_dmd,
			       काष्ठा cxd2880_tnrdmd_pid_ftr_cfg
			       *pid_ftr_cfg)
अणु
	अगर (!tnr_dmd)
		वापस -EINVAL;

	अगर (tnr_dmd->भागer_mode == CXD2880_TNRDMD_DIVERMODE_SUB)
		वापस -EINVAL;

	अगर (tnr_dmd->state != CXD2880_TNRDMD_STATE_SLEEP &&
	    tnr_dmd->state != CXD2880_TNRDMD_STATE_ACTIVE)
		वापस -EINVAL;

	अगर (tnr_dmd->create_param.ts_output_अगर == CXD2880_TNRDMD_TSOUT_IF_TS)
		वापस -ENOTTY;

	अगर (pid_ftr_cfg) अणु
		tnr_dmd->pid_ftr_cfg = *pid_ftr_cfg;
		tnr_dmd->pid_ftr_cfg_en = 1;
	पूर्ण अन्यथा अणु
		tnr_dmd->pid_ftr_cfg_en = 0;
	पूर्ण

	अगर (tnr_dmd->state == CXD2880_TNRDMD_STATE_ACTIVE)
		वापस pid_ftr_setting(tnr_dmd, pid_ftr_cfg);
	अन्यथा
		वापस 0;
पूर्ण

पूर्णांक cxd2880_tnrdmd_set_rf_lvl_cmpstn(काष्ठा cxd2880_tnrdmd
				     *tnr_dmd,
				     पूर्णांक (*rf_lvl_cmpstn)
				     (काष्ठा cxd2880_tnrdmd *,
				     पूर्णांक *))
अणु
	अगर (!tnr_dmd)
		वापस -EINVAL;

	tnr_dmd->rf_lvl_cmpstn = rf_lvl_cmpstn;

	वापस 0;
पूर्ण

पूर्णांक cxd2880_tnrdmd_set_rf_lvl_cmpstn_sub(काष्ठा cxd2880_tnrdmd
					 *tnr_dmd,
					 पूर्णांक (*rf_lvl_cmpstn)
					 (काष्ठा cxd2880_tnrdmd *,
					 पूर्णांक *))
अणु
	अगर (!tnr_dmd)
		वापस -EINVAL;

	अगर (tnr_dmd->भागer_mode != CXD2880_TNRDMD_DIVERMODE_MAIN)
		वापस -EINVAL;

	वापस cxd2880_tnrdmd_set_rf_lvl_cmpstn(tnr_dmd->भागer_sub,
						rf_lvl_cmpstn);
पूर्ण

पूर्णांक cxd2880_tnrdmd_set_lna_thrs(काष्ठा cxd2880_tnrdmd *tnr_dmd,
				काष्ठा cxd2880_tnrdmd_lna_thrs_tbl_air
				*tbl_air,
				काष्ठा cxd2880_tnrdmd_lna_thrs_tbl_cable
				*tbl_cable)
अणु
	अगर (!tnr_dmd)
		वापस -EINVAL;

	tnr_dmd->lna_thrs_tbl_air = tbl_air;
	tnr_dmd->lna_thrs_tbl_cable = tbl_cable;

	वापस 0;
पूर्ण

पूर्णांक cxd2880_tnrdmd_set_lna_thrs_sub(काष्ठा cxd2880_tnrdmd *tnr_dmd,
				    काष्ठा
				    cxd2880_tnrdmd_lna_thrs_tbl_air
				    *tbl_air,
				    काष्ठा cxd2880_tnrdmd_lna_thrs_tbl_cable
				    *tbl_cable)
अणु
	अगर (!tnr_dmd)
		वापस -EINVAL;

	अगर (tnr_dmd->भागer_mode != CXD2880_TNRDMD_DIVERMODE_MAIN)
		वापस -EINVAL;

	वापस cxd2880_tnrdmd_set_lna_thrs(tnr_dmd->भागer_sub,
					   tbl_air, tbl_cable);
पूर्ण

पूर्णांक cxd2880_tnrdmd_set_ts_pin_high_low(काष्ठा cxd2880_tnrdmd
				       *tnr_dmd, u8 en, u8 value)
अणु
	पूर्णांक ret;

	अगर (!tnr_dmd)
		वापस -EINVAL;

	अगर (tnr_dmd->भागer_mode == CXD2880_TNRDMD_DIVERMODE_SUB)
		वापस -EINVAL;

	अगर (tnr_dmd->state != CXD2880_TNRDMD_STATE_SLEEP)
		वापस -EINVAL;

	अगर (tnr_dmd->create_param.ts_output_अगर != CXD2880_TNRDMD_TSOUT_IF_TS)
		वापस -ENOTTY;

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x00, 0x00);
	अगर (ret)
		वापस ret;

	अगर (en) अणु
		ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
					     CXD2880_IO_TGT_SYS,
					     0x50, ((value & 0x1f) | 0x80));
		अगर (ret)
			वापस ret;

		ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
					     CXD2880_IO_TGT_SYS,
					     0x52, (value & 0x1f));
	पूर्ण अन्यथा अणु
		ret = cxd2880_io_ग_लिखो_multi_regs(tnr_dmd->io,
						  CXD2880_IO_TGT_SYS,
						  set_ts_pin_seq,
						  ARRAY_SIZE(set_ts_pin_seq));
		अगर (ret)
			वापस ret;

		ret = load_cfg_mem(tnr_dmd);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक cxd2880_tnrdmd_set_ts_output(काष्ठा cxd2880_tnrdmd *tnr_dmd,
				 u8 en)
अणु
	पूर्णांक ret;

	अगर (!tnr_dmd)
		वापस -EINVAL;

	अगर (tnr_dmd->भागer_mode == CXD2880_TNRDMD_DIVERMODE_SUB)
		वापस -EINVAL;

	अगर (tnr_dmd->state != CXD2880_TNRDMD_STATE_SLEEP &&
	    tnr_dmd->state != CXD2880_TNRDMD_STATE_ACTIVE)
		वापस -EINVAL;

	चयन (tnr_dmd->create_param.ts_output_अगर) अणु
	हाल CXD2880_TNRDMD_TSOUT_IF_TS:
		अगर (en) अणु
			ret = cxd2880_io_ग_लिखो_multi_regs(tnr_dmd->io,
							  CXD2880_IO_TGT_SYS,
							  set_ts_output_seq1,
							  ARRAY_SIZE(set_ts_output_seq1));
			अगर (ret)
				वापस ret;

			ret = cxd2880_io_ग_लिखो_multi_regs(tnr_dmd->io,
							  CXD2880_IO_TGT_DMD,
							  set_ts_output_seq2,
							  ARRAY_SIZE(set_ts_output_seq2));
			अगर (ret)
				वापस ret;
		पूर्ण अन्यथा अणु
			ret = cxd2880_io_ग_लिखो_multi_regs(tnr_dmd->io,
							  CXD2880_IO_TGT_DMD,
							  set_ts_output_seq3,
							  ARRAY_SIZE(set_ts_output_seq3));
			अगर (ret)
				वापस ret;

			ret = cxd2880_io_ग_लिखो_multi_regs(tnr_dmd->io,
							  CXD2880_IO_TGT_SYS,
							  set_ts_output_seq4,
							  ARRAY_SIZE(set_ts_output_seq4));
			अगर (ret)
				वापस ret;
		पूर्ण
		अवरोध;

	हाल CXD2880_TNRDMD_TSOUT_IF_SPI:
		अवरोध;

	हाल CXD2880_TNRDMD_TSOUT_IF_SDIO:
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक slvt_मुक्तze_reg(काष्ठा cxd2880_tnrdmd *tnr_dmd)
अणु
	u8 data;
	पूर्णांक ret;

	अगर (!tnr_dmd)
		वापस -EINVAL;

	चयन (tnr_dmd->create_param.ts_output_अगर) अणु
	हाल CXD2880_TNRDMD_TSOUT_IF_SPI:
	हाल CXD2880_TNRDMD_TSOUT_IF_SDIO:

		ret = tnr_dmd->io->पढ़ो_regs(tnr_dmd->io,
					     CXD2880_IO_TGT_DMD,
					     0x00, &data, 1);
		अगर (ret)
			वापस ret;

		अवरोध;
	हाल CXD2880_TNRDMD_TSOUT_IF_TS:
	शेष:
		अवरोध;
	पूर्ण

	वापस tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				      CXD2880_IO_TGT_DMD,
				      0x01, 0x01);
पूर्ण
