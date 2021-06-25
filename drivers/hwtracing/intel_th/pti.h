<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Intel(R) Trace Hub PTI output data काष्ठाures
 *
 * Copyright (C) 2014-2015 Intel Corporation.
 */

#अगर_अघोषित __INTEL_TH_STH_H__
#घोषणा __INTEL_TH_STH_H__

क्रमागत अणु
	REG_PTI_CTL	= 0x1c00,
पूर्ण;

#घोषणा PTI_EN		BIT(0)
#घोषणा PTI_FCEN	BIT(1)
#घोषणा PTI_MODE	0xf0
#घोषणा LPP_PTIPRESENT	BIT(8)
#घोषणा LPP_BSSBPRESENT	BIT(9)
#घोषणा PTI_CLKDIV	0x000f0000
#घोषणा PTI_PATGENMODE	0x00f00000
#घोषणा LPP_DEST	BIT(25)
#घोषणा LPP_BSSBACT	BIT(30)
#घोषणा LPP_LPPBUSY	BIT(31)

#घोषणा LPP_DEST_PTI	BIT(0)
#घोषणा LPP_DEST_EXI	BIT(1)

#पूर्ण_अगर /* __INTEL_TH_STH_H__ */
