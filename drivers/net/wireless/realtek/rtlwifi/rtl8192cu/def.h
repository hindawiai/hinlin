<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2009-2012  Realtek Corporation.*/

#समावेश "../rtl8192ce/def.h"

/*-------------------------------------------------------------------------
 *	Chip specअगरic
 *-------------------------------------------------------------------------*/
#घोषणा NORMAL_CHIP			BIT(4)
#घोषणा CHIP_VENDOR_UMC			BIT(5)
#घोषणा CHIP_VENDOR_UMC_B_CUT		BIT(6)

#घोषणा IS_92C_1T2R(version)		\
	(((version) & CHIP_92C) && ((version) & CHIP_92C_1T2R))

#घोषणा IS_VENDOR_UMC(version)		\
	(((version) & CHIP_VENDOR_UMC) ? true : false)

#घोषणा CHIP_BONDING_92C_1T2R	0x1
#घोषणा CHIP_BONDING_IDENTIFIER(_value)	(((_value) >> 22) & 0x3)
