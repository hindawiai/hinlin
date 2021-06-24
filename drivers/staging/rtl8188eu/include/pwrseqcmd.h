<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#अगर_अघोषित __HALPWRSEQCMD_H__
#घोषणा __HALPWRSEQCMD_H__

#समावेश <drv_types.h>

/* The value of cmd: 4 bits */
#घोषणा PWR_CMD_READ		0x00
#घोषणा PWR_CMD_WRITE		0x01
#घोषणा PWR_CMD_POLLING		0x02
#घोषणा PWR_CMD_DELAY		0x03
#घोषणा PWR_CMD_END		0x04

/* The value of cut_msk: 8 bits */
#घोषणा PWR_CUT_TESTCHIP_MSK	BIT(0)
#घोषणा PWR_CUT_A_MSK		BIT(1)
#घोषणा PWR_CUT_B_MSK		BIT(2)
#घोषणा PWR_CUT_C_MSK		BIT(3)
#घोषणा PWR_CUT_D_MSK		BIT(4)
#घोषणा PWR_CUT_E_MSK		BIT(5)
#घोषणा PWR_CUT_F_MSK		BIT(6)
#घोषणा PWR_CUT_G_MSK		BIT(7)
#घोषणा PWR_CUT_ALL_MSK		0xFF

क्रमागत pwrseq_cmd_delat_unit अणु
	PWRSEQ_DELAY_US,
	PWRSEQ_DELAY_MS,
पूर्ण;

काष्ठा wl_pwr_cfg अणु
	u16 offset;
	u8 cut_msk;
	u8 cmd:4;
	u8 msk;
	u8 value;
पूर्ण;

#घोषणा GET_PWR_CFG_OFFSET(__PWR_CMD)		__PWR_CMD.offset
#घोषणा GET_PWR_CFG_CUT_MASK(__PWR_CMD)		__PWR_CMD.cut_msk
#घोषणा GET_PWR_CFG_CMD(__PWR_CMD)		__PWR_CMD.cmd
#घोषणा GET_PWR_CFG_MASK(__PWR_CMD)		__PWR_CMD.msk
#घोषणा GET_PWR_CFG_VALUE(__PWR_CMD)		__PWR_CMD.value

u8 rtl88eu_pwrseqcmdparsing(काष्ठा adapter *padapter, u8 cut_vers,
			    काष्ठा wl_pwr_cfg pwrcfgCmd[]);

#पूर्ण_अगर
