<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * cxd2841er_priv.h
 *
 * Sony CXD2441ER digital demodulator driver पूर्णांकernal definitions
 *
 * Copyright 2012 Sony Corporation
 * Copyright (C) 2014 NetUP Inc.
 * Copyright (C) 2014 Sergey Kozlov <serjk@netup.ru>
 * Copyright (C) 2014 Abylay Ospan <aospan@netup.ru>
 */

#अगर_अघोषित CXD2841ER_PRIV_H
#घोषणा CXD2841ER_PRIV_H

#घोषणा I2C_SLVX			0
#घोषणा I2C_SLVT			1

#घोषणा CXD2837ER_CHIP_ID		0xb1
#घोषणा CXD2838ER_CHIP_ID		0xb0
#घोषणा CXD2841ER_CHIP_ID		0xa7
#घोषणा CXD2843ER_CHIP_ID		0xa4
#घोषणा CXD2854ER_CHIP_ID		0xc1

#घोषणा CXD2841ER_DVBS_POLLING_INVL	10

काष्ठा cxd2841er_cnr_data अणु
	u32 value;
	पूर्णांक cnr_x1000;
पूर्ण;

क्रमागत cxd2841er_dvbt2_profile_t अणु
	DVBT2_PROखाता_ANY = 0,
	DVBT2_PROखाता_BASE = 1,
	DVBT2_PROखाता_LITE = 2
पूर्ण;

#पूर्ण_अगर
