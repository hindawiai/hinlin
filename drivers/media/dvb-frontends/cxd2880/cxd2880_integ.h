<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * cxd2880_पूर्णांकeg.h
 * Sony CXD2880 DVB-T2/T tuner + demodulator driver
 * पूर्णांकegration layer common पूर्णांकerface
 *
 * Copyright (C) 2016, 2017, 2018 Sony Semiconductor Solutions Corporation
 */

#अगर_अघोषित CXD2880_INTEG_H
#घोषणा CXD2880_INTEG_H

#समावेश "cxd2880_tnrdmd.h"

#घोषणा CXD2880_TNRDMD_WAIT_INIT_TIMEOUT	500
#घोषणा CXD2880_TNRDMD_WAIT_INIT_INTVL	10

#घोषणा CXD2880_TNRDMD_WAIT_AGC_STABLE		100

पूर्णांक cxd2880_पूर्णांकeg_init(काष्ठा cxd2880_tnrdmd *tnr_dmd);

पूर्णांक cxd2880_पूर्णांकeg_cancel(काष्ठा cxd2880_tnrdmd *tnr_dmd);

पूर्णांक cxd2880_पूर्णांकeg_check_cancellation(काष्ठा cxd2880_tnrdmd
				     *tnr_dmd);

#पूर्ण_अगर
