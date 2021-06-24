<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2009-2012  Realtek Corporation.*/

#अगर_अघोषित __RTL8723E_PWRSEQCMD_H__
#घोषणा __RTL8723E_PWRSEQCMD_H__

#समावेश "wifi.h"
/*---------------------------------------------
 * 3 The value of cmd: 4 bits
 *---------------------------------------------
 */
#घोषणा    PWR_CMD_READ		0x00
#घोषणा    PWR_CMD_WRITE	0x01
#घोषणा    PWR_CMD_POLLING	0x02
#घोषणा    PWR_CMD_DELAY	0x03
#घोषणा    PWR_CMD_END		0x04

/* define the base address of each block */
#घोषणा   PWR_BASEADDR_MAC	0x00
#घोषणा   PWR_BASEADDR_USB	0x01
#घोषणा   PWR_BASEADDR_PCIE	0x02
#घोषणा   PWR_BASEADDR_SDIO	0x03

#घोषणा	PWR_INTF_SDIO_MSK	BIT(0)
#घोषणा	PWR_INTF_USB_MSK	BIT(1)
#घोषणा	PWR_INTF_PCI_MSK	BIT(2)
#घोषणा	PWR_INTF_ALL_MSK	(BIT(0)|BIT(1)|BIT(2)|BIT(3))

#घोषणा	PWR_FAB_TSMC_MSK	BIT(0)
#घोषणा	PWR_FAB_UMC_MSK		BIT(1)
#घोषणा	PWR_FAB_ALL_MSK		(BIT(0)|BIT(1)|BIT(2)|BIT(3))

#घोषणा	PWR_CUT_TESTCHIP_MSK	BIT(0)
#घोषणा	PWR_CUT_A_MSK		BIT(1)
#घोषणा	PWR_CUT_B_MSK		BIT(2)
#घोषणा	PWR_CUT_C_MSK		BIT(3)
#घोषणा	PWR_CUT_D_MSK		BIT(4)
#घोषणा	PWR_CUT_E_MSK		BIT(5)
#घोषणा	PWR_CUT_F_MSK		BIT(6)
#घोषणा	PWR_CUT_G_MSK		BIT(7)
#घोषणा	PWR_CUT_ALL_MSK		0xFF

क्रमागत pwrseq_delay_unit अणु
	PWRSEQ_DELAY_US,
	PWRSEQ_DELAY_MS,
पूर्ण;

काष्ठा wlan_pwr_cfg अणु
	u16 offset;
	u8 cut_msk;
	u8 fab_msk:4;
	u8 पूर्णांकerface_msk:4;
	u8 base:4;
	u8 cmd:4;
	u8 msk;
	u8 value;
पूर्ण;

#घोषणा	GET_PWR_CFG_OFFSET(__PWR_CMD)	(__PWR_CMD.offset)
#घोषणा	GET_PWR_CFG_CUT_MASK(__PWR_CMD)	(__PWR_CMD.cut_msk)
#घोषणा	GET_PWR_CFG_FAB_MASK(__PWR_CMD)	(__PWR_CMD.fab_msk)
#घोषणा	GET_PWR_CFG_INTF_MASK(__PWR_CMD)	(__PWR_CMD.पूर्णांकerface_msk)
#घोषणा	GET_PWR_CFG_BASE(__PWR_CMD)	(__PWR_CMD.base)
#घोषणा	GET_PWR_CFG_CMD(__PWR_CMD)	(__PWR_CMD.cmd)
#घोषणा	GET_PWR_CFG_MASK(__PWR_CMD)	(__PWR_CMD.msk)
#घोषणा	GET_PWR_CFG_VALUE(__PWR_CMD)	(__PWR_CMD.value)

bool rtl_hal_pwrseqcmdparsing(काष्ठा rtl_priv *rtlpriv, u8 cut_version,
			      u8 fab_version, u8 पूर्णांकerface_type,
			      काष्ठा wlan_pwr_cfg pwrcfgcmd[]);

#पूर्ण_अगर
