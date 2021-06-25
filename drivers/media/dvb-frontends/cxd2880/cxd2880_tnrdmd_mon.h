<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * cxd2880_tnrdmd_mon.h
 * Sony CXD2880 DVB-T2/T tuner + demodulator driver
 * common monitor पूर्णांकerface
 *
 * Copyright (C) 2016, 2017, 2018 Sony Semiconductor Solutions Corporation
 */

#अगर_अघोषित CXD2880_TNRDMD_MON_H
#घोषणा CXD2880_TNRDMD_MON_H

#समावेश "cxd2880_common.h"
#समावेश "cxd2880_tnrdmd.h"

पूर्णांक cxd2880_tnrdmd_mon_rf_lvl(काष्ठा cxd2880_tnrdmd *tnr_dmd,
			      पूर्णांक *rf_lvl_db);

पूर्णांक cxd2880_tnrdmd_mon_rf_lvl_sub(काष्ठा cxd2880_tnrdmd *tnr_dmd,
				  पूर्णांक *rf_lvl_db);

पूर्णांक cxd2880_tnrdmd_mon_पूर्णांकernal_cpu_status(काष्ठा cxd2880_tnrdmd
					   *tnr_dmd, u16 *status);

पूर्णांक cxd2880_tnrdmd_mon_पूर्णांकernal_cpu_status_sub(काष्ठा
					       cxd2880_tnrdmd
					       *tnr_dmd,
					       u16 *status);
#पूर्ण_अगर
