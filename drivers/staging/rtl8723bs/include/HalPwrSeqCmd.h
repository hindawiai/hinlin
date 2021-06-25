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

/*---------------------------------------------*/
/* 3 The value of cmd: 4 bits */
/*---------------------------------------------*/
#घोषणा PWR_CMD_READ			0x00
     /*  offset: the पढ़ो रेजिस्टर offset */
     /*  msk: the mask of the पढ़ो value */
     /*  value: N/A, left by 0 */
     /*  note: dirver shall implement this function by पढ़ो & msk */

#घोषणा PWR_CMD_WRITE			0x01
     /*  offset: the पढ़ो रेजिस्टर offset */
     /*  msk: the mask of the ग_लिखो bits */
     /*  value: ग_लिखो value */
     /*  note: driver shall implement this cmd by पढ़ो & msk after ग_लिखो */

#घोषणा PWR_CMD_POLLING			0x02
     /*  offset: the पढ़ो रेजिस्टर offset */
     /*  msk: the mask of the polled value */
     /*  value: the value to be polled, masked by the msd field. */
     /*  note: driver shall implement this cmd by */
     /*  करोअणु */
     /*  अगर ((Read(offset) & msk) == (value & msk)) */
     /*  अवरोध; */
     /*  पूर्ण जबतक (not समयout); */

#घोषणा PWR_CMD_DELAY			0x03
     /*  offset: the value to delay */
     /*  msk: N/A */
     /*  value: the unit of delay, 0: us, 1: ms */

#घोषणा PWR_CMD_END				0x04
     /*  offset: N/A */
     /*  msk: N/A */
     /*  value: N/A */

/*---------------------------------------------*/
/* 3 The value of base: 4 bits */
/*---------------------------------------------*/
   /*  define the base address of each block */
#घोषणा PWR_BASEADDR_MAC		0x00
#घोषणा PWR_BASEADDR_USB		0x01
#घोषणा PWR_BASEADDR_PCIE		0x02
#घोषणा PWR_BASEADDR_SDIO		0x03

/*---------------------------------------------*/
/* 3 The value of पूर्णांकerface_msk: 4 bits */
/*---------------------------------------------*/
#घोषणा	PWR_INTF_SDIO_MSK		BIT(0)
#घोषणा	PWR_INTF_USB_MSK		BIT(1)
#घोषणा	PWR_INTF_PCI_MSK		BIT(2)
#घोषणा	PWR_INTF_ALL_MSK		(BIT(0)|BIT(1)|BIT(2)|BIT(3))

/*---------------------------------------------*/
/* 3 The value of fab_msk: 4 bits */
/*---------------------------------------------*/
#घोषणा	PWR_FAB_TSMC_MSK		BIT(0)
#घोषणा	PWR_FAB_UMC_MSK			BIT(1)
#घोषणा	PWR_FAB_ALL_MSK			(BIT(0)|BIT(1)|BIT(2)|BIT(3))

/*---------------------------------------------*/
/* 3 The value of cut_msk: 8 bits */
/*---------------------------------------------*/
#घोषणा	PWR_CUT_TESTCHIP_MSK	BIT(0)
#घोषणा	PWR_CUT_A_MSK			BIT(1)
#घोषणा	PWR_CUT_B_MSK			BIT(2)
#घोषणा	PWR_CUT_C_MSK			BIT(3)
#घोषणा	PWR_CUT_D_MSK			BIT(4)
#घोषणा	PWR_CUT_E_MSK			BIT(5)
#घोषणा	PWR_CUT_F_MSK			BIT(6)
#घोषणा	PWR_CUT_G_MSK			BIT(7)
#घोषणा	PWR_CUT_ALL_MSK			0xFF


क्रमागत अणु
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


#घोषणा GET_PWR_CFG_OFFSET(__PWR_CMD)		__PWR_CMD.offset
#घोषणा GET_PWR_CFG_CUT_MASK(__PWR_CMD)		__PWR_CMD.cut_msk
#घोषणा GET_PWR_CFG_FAB_MASK(__PWR_CMD)		__PWR_CMD.fab_msk
#घोषणा GET_PWR_CFG_INTF_MASK(__PWR_CMD)	__PWR_CMD.पूर्णांकerface_msk
#घोषणा GET_PWR_CFG_BASE(__PWR_CMD)			__PWR_CMD.base
#घोषणा GET_PWR_CFG_CMD(__PWR_CMD)			__PWR_CMD.cmd
#घोषणा GET_PWR_CFG_MASK(__PWR_CMD)			__PWR_CMD.msk
#घोषणा GET_PWR_CFG_VALUE(__PWR_CMD)		__PWR_CMD.value


/*  */
/* 	Prototype of रक्षित function. */
/*  */
u8 HalPwrSeqCmdParsing(
	काष्ठा adapter *padapter,
	u8 		CutVersion,
	u8 		FabVersion,
	u8 		InterfaceType,
	काष्ठा wlan_pwr_cfg	PwrCfgCmd[]);

#पूर्ण_अगर
