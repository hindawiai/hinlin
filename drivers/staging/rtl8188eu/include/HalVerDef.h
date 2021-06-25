<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#अगर_अघोषित __HAL_VERSION_DEF_H__
#घोषणा __HAL_VERSION_DEF_H__

क्रमागत HAL_CHIP_TYPE अणु
	TEST_CHIP	=	0,
	NORMAL_CHIP	=	1,
	FPGA		=	2,
पूर्ण;

क्रमागत HAL_CUT_VERSION अणु
	A_CUT_VERSION	=	0,
	B_CUT_VERSION	=	1,
	C_CUT_VERSION	=	2,
	D_CUT_VERSION	=	3,
	E_CUT_VERSION	=	4,
	F_CUT_VERSION	=	5,
	G_CUT_VERSION	=	6,
पूर्ण;

क्रमागत HAL_VENDOR अणु
	CHIP_VENDOR_TSMC	=	0,
	CHIP_VENDOR_UMC		=	1,
पूर्ण;

काष्ठा HAL_VERSION अणु
	क्रमागत HAL_CHIP_TYPE	ChipType;
	क्रमागत HAL_CUT_VERSION	CUTVersion;
	क्रमागत HAL_VENDOR		VenकरोrType;
पूर्ण;

#पूर्ण_अगर
