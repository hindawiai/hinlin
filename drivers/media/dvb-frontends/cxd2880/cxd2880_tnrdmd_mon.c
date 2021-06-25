<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * cxd2880_tnrdmd_mon.c
 * Sony CXD2880 DVB-T2/T tuner + demodulator driver
 * common monitor functions
 *
 * Copyright (C) 2016, 2017, 2018 Sony Semiconductor Solutions Corporation
 */

#समावेश "cxd2880_common.h"
#समावेश "cxd2880_tnrdmd_mon.h"

अटल स्थिर u8 rf_lvl_seq[2] = अणु
	0x80, 0x00,
पूर्ण;

पूर्णांक cxd2880_tnrdmd_mon_rf_lvl(काष्ठा cxd2880_tnrdmd *tnr_dmd,
			      पूर्णांक *rf_lvl_db)
अणु
	u8 rdata[2];
	पूर्णांक ret;

	अगर (!tnr_dmd || !rf_lvl_db)
		वापस -EINVAL;

	अगर (tnr_dmd->state != CXD2880_TNRDMD_STATE_ACTIVE)
		वापस -EINVAL;

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x00);
	अगर (ret)
		वापस ret;

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x10, 0x01);
	अगर (ret)
		वापस ret;

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x00, 0x10);
	अगर (ret)
		वापस ret;

	ret = tnr_dmd->io->ग_लिखो_regs(tnr_dmd->io,
				      CXD2880_IO_TGT_SYS,
				      0x5b, rf_lvl_seq, 2);
	अगर (ret)
		वापस ret;

	usleep_range(2000, 3000);

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x00, 0x1a);
	अगर (ret)
		वापस ret;

	ret = tnr_dmd->io->पढ़ो_regs(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x15, rdata, 2);
	अगर (ret)
		वापस ret;

	अगर (rdata[0] || rdata[1])
		वापस -EINVAL;

	ret = tnr_dmd->io->पढ़ो_regs(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x11, rdata, 2);
	अगर (ret)
		वापस ret;

	*rf_lvl_db =
	    cxd2880_convert2s_complement((rdata[0] << 3) |
					 ((rdata[1] & 0xe0) >> 5), 11);

	*rf_lvl_db *= 125;

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x00);
	अगर (ret)
		वापस ret;

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x10, 0x00);
	अगर (ret)
		वापस ret;

	अगर (tnr_dmd->rf_lvl_cmpstn)
		ret = tnr_dmd->rf_lvl_cmpstn(tnr_dmd, rf_lvl_db);

	वापस ret;
पूर्ण

पूर्णांक cxd2880_tnrdmd_mon_rf_lvl_sub(काष्ठा cxd2880_tnrdmd *tnr_dmd,
				  पूर्णांक *rf_lvl_db)
अणु
	अगर (!tnr_dmd || !rf_lvl_db)
		वापस -EINVAL;

	अगर (tnr_dmd->भागer_mode != CXD2880_TNRDMD_DIVERMODE_MAIN)
		वापस -EINVAL;

	वापस cxd2880_tnrdmd_mon_rf_lvl(tnr_dmd->भागer_sub, rf_lvl_db);
पूर्ण

पूर्णांक cxd2880_tnrdmd_mon_पूर्णांकernal_cpu_status(काष्ठा cxd2880_tnrdmd
					   *tnr_dmd, u16 *status)
अणु
	u8 data[2] = अणु 0 पूर्ण;
	पूर्णांक ret;

	अगर (!tnr_dmd || !status)
		वापस -EINVAL;

	ret = tnr_dmd->io->ग_लिखो_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x00, 0x1a);
	अगर (ret)
		वापस ret;
	ret = tnr_dmd->io->पढ़ो_regs(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x15, data, 2);
	अगर (ret)
		वापस ret;

	*status = (data[0] << 8) | data[1];

	वापस 0;
पूर्ण

पूर्णांक cxd2880_tnrdmd_mon_पूर्णांकernal_cpu_status_sub(काष्ठा
					       cxd2880_tnrdmd
					       *tnr_dmd,
					       u16 *status)
अणु
	अगर (!tnr_dmd || !status)
		वापस -EINVAL;

	अगर (tnr_dmd->भागer_mode != CXD2880_TNRDMD_DIVERMODE_MAIN)
		वापस -EINVAL;

	वापस cxd2880_tnrdmd_mon_पूर्णांकernal_cpu_status(tnr_dmd->भागer_sub,
						      status);
पूर्ण
