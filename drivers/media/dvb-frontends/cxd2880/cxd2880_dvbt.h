<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * cxd2880_dvbt.h
 * Sony CXD2880 DVB-T2/T tuner + demodulator driver
 * DVB-T related definitions
 *
 * Copyright (C) 2016, 2017, 2018 Sony Semiconductor Solutions Corporation
 */

#अगर_अघोषित CXD2880_DVBT_H
#घोषणा CXD2880_DVBT_H

#समावेश "cxd2880_common.h"

क्रमागत cxd2880_dvbt_स्थिरellation अणु
	CXD2880_DVBT_CONSTELLATION_QPSK,
	CXD2880_DVBT_CONSTELLATION_16QAM,
	CXD2880_DVBT_CONSTELLATION_64QAM,
	CXD2880_DVBT_CONSTELLATION_RESERVED_3
पूर्ण;

क्रमागत cxd2880_dvbt_hierarchy अणु
	CXD2880_DVBT_HIERARCHY_NON,
	CXD2880_DVBT_HIERARCHY_1,
	CXD2880_DVBT_HIERARCHY_2,
	CXD2880_DVBT_HIERARCHY_4
पूर्ण;

क्रमागत cxd2880_dvbt_coderate अणु
	CXD2880_DVBT_CODERATE_1_2,
	CXD2880_DVBT_CODERATE_2_3,
	CXD2880_DVBT_CODERATE_3_4,
	CXD2880_DVBT_CODERATE_5_6,
	CXD2880_DVBT_CODERATE_7_8,
	CXD2880_DVBT_CODERATE_RESERVED_5,
	CXD2880_DVBT_CODERATE_RESERVED_6,
	CXD2880_DVBT_CODERATE_RESERVED_7
पूर्ण;

क्रमागत cxd2880_dvbt_guard अणु
	CXD2880_DVBT_GUARD_1_32,
	CXD2880_DVBT_GUARD_1_16,
	CXD2880_DVBT_GUARD_1_8,
	CXD2880_DVBT_GUARD_1_4
पूर्ण;

क्रमागत cxd2880_dvbt_mode अणु
	CXD2880_DVBT_MODE_2K,
	CXD2880_DVBT_MODE_8K,
	CXD2880_DVBT_MODE_RESERVED_2,
	CXD2880_DVBT_MODE_RESERVED_3
पूर्ण;

क्रमागत cxd2880_dvbt_profile अणु
	CXD2880_DVBT_PROखाता_HP = 0,
	CXD2880_DVBT_PROखाता_LP
पूर्ण;

काष्ठा cxd2880_dvbt_tpsinfo अणु
	क्रमागत cxd2880_dvbt_स्थिरellation स्थिरellation;
	क्रमागत cxd2880_dvbt_hierarchy hierarchy;
	क्रमागत cxd2880_dvbt_coderate rate_hp;
	क्रमागत cxd2880_dvbt_coderate rate_lp;
	क्रमागत cxd2880_dvbt_guard guard;
	क्रमागत cxd2880_dvbt_mode mode;
	u8 fnum;
	u8 length_indicator;
	u16 cell_id;
	u8 cell_id_ok;
	u8 reserved_even;
	u8 reserved_odd;
पूर्ण;

#पूर्ण_अगर
