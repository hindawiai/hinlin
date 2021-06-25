<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2009-2012  Realtek Corporation.*/

#अगर_अघोषित __RTL8723E_PWRSEQ_H__
#घोषणा __RTL8723E_PWRSEQ_H__

#समावेश "../pwrseqcmd.h"
/*
 *	Check करोcument WM-20110607-Paul-RTL8723A_Power_Architecture-R02.vsd
 *	There are 6 HW Power States:
 *	0: POFF--Power Off
 *	1: PDN--Power Down
 *	2: CARDEMU--Card Emulation
 *	3: ACT--Active Mode
 *	4: LPS--Low Power State
 *	5: SUS--Suspend
 *
 *	The transision from dअगरferent states are defined below
 *	TRANS_CARDEMU_TO_ACT
 *	TRANS_ACT_TO_CARDEMU
 *	TRANS_CARDEMU_TO_SUS
 *	TRANS_SUS_TO_CARDEMU
 *	TRANS_CARDEMU_TO_PDN
 *	TRANS_ACT_TO_LPS
 *	TRANS_LPS_TO_ACT
 *
 *	TRANS_END
 */

#घोषणा	RTL8723A_TRANS_CARDEMU_TO_ACT_STEPS	10
#घोषणा	RTL8723A_TRANS_ACT_TO_CARDEMU_STEPS	10
#घोषणा	RTL8723A_TRANS_CARDEMU_TO_SUS_STEPS	10
#घोषणा	RTL8723A_TRANS_SUS_TO_CARDEMU_STEPS	10
#घोषणा	RTL8723A_TRANS_CARDEMU_TO_PDN_STEPS	10
#घोषणा	RTL8723A_TRANS_PDN_TO_CARDEMU_STEPS	10
#घोषणा	RTL8723A_TRANS_ACT_TO_LPS_STEPS		15
#घोषणा	RTL8723A_TRANS_LPS_TO_ACT_STEPS		15
#घोषणा	RTL8723A_TRANS_END_STEPS		1

/* क्रमmat */
/* अणु offset, cut_msk, fab_msk|पूर्णांकerface_msk, base|cmd, msk, value पूर्ण*/

#घोषणा RTL8723A_TRANS_CARDEMU_TO_ACT	\
	/* disable SW LPS 0x04[10]=0*/	\
	अणु0x0005, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,\
		PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT(2), 0पूर्ण,\
	/* रुको till 0x04[17] = 1    घातer पढ़ोy*/	\
	अणु0x0006, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,\
		PWR_BASEADDR_MAC, PWR_CMD_POLLING, BIT(1), BIT(1)पूर्ण,\
	/* release WLON reset  0x04[16]=1*/	\
	अणु0x0006, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,\
		PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT(0), BIT(0)पूर्ण,\
	/* disable HWPDN 0x04[15]=0*/ \
	अणु0x0005, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,\
		PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT(7), 0पूर्ण,\
	/* disable WL suspend*/ \
	अणु0x0005, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,\
		PWR_BASEADDR_MAC, PWR_CMD_WRITE, (BIT(4)|BIT(3)), 0पूर्ण,\
	/* polling until वापस 0*/ \
	अणु0x0005, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,\
		PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT(0), BIT(0)पूर्ण,\
	अणु0x0005, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,\
		PWR_BASEADDR_MAC, PWR_CMD_POLLING, BIT(0), 0पूर्ण,

/* क्रमmat */
/* अणु offset, cut_msk, fab_msk|पूर्णांकerface_msk, base|cmd, msk, value पूर्ण, */

#घोषणा RTL8723A_TRANS_ACT_TO_CARDEMU	\
	/*0x1F[7:0] = 0 turn off RF*/ \
	अणु0x001F, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,\
		PWR_BASEADDR_MAC, PWR_CMD_WRITE, 0xFF, 0पूर्ण,	\
	अणु0x004E, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,\
		PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT(7), 0पूर्ण,\
	अणु0x0005, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,\
		PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT(1), BIT(1)पूर्ण, \
	अणु0x0005, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,\
		PWR_BASEADDR_MAC, PWR_CMD_POLLING, BIT(1), 0पूर्ण,

/* क्रमmat */
/* अणु offset, cut_msk, fab_msk|पूर्णांकerface_msk, base|cmd, msk, value पूर्ण,*/
#घोषणा RTL8723A_TRANS_CARDEMU_TO_SUS			\
		/*0x04[12:11] = 2b'11 enable WL suspend क्रम PCIe*/	\
	अणु0x0005, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_PCI_MSK,\
		PWR_BASEADDR_MAC, PWR_CMD_WRITE, \
		BIT(4)|BIT(3), (BIT(4)|BIT(3))पूर्ण,\
/*0x04[12:11] = 2b'01 enable WL suspend*/	\
	अणु0x0005, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_USB_MSK| \
		PWR_INTF_SDIO_MSK,\
		PWR_BASEADDR_MAC, \
		PWR_CMD_WRITE, \
		BIT(3)|BIT(4), BIT(3)पूर्ण, \
/*0x04[12:11] = 2b'11 enable WL suspend क्रम PCIe*/ \
	अणु0x0005, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, \
		PWR_INTF_PCI_MSK, PWR_BASEADDR_MAC, \
		PWR_CMD_WRITE, BIT(3)|BIT(4), \
		BIT(3)|BIT(4)पूर्ण, \
/*Set SDIO suspend local रेजिस्टर*/	\
	अणु0x0086, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, \
		PWR_INTF_SDIO_MSK, PWR_BASEADDR_SDIO,\
		PWR_CMD_WRITE, BIT(0), BIT(0)पूर्ण, \
/*रुको घातer state to suspend*/ \
	अणु0x0086, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, \
		PWR_INTF_SDIO_MSK, PWR_BASEADDR_SDIO,\
		PWR_CMD_POLLING, BIT(1), 0पूर्ण,

/* क्रमmat */
/* अणु offset, cut_msk, fab_msk|पूर्णांकerface_msk, base|cmd, msk, value पूर्ण, */

#घोषणा RTL8723A_TRANS_SUS_TO_CARDEMU	\
 /*Set SDIO suspend local रेजिस्टर*/	\
	अणु0x0086, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK,\
		PWR_BASEADDR_SDIO, PWR_CMD_WRITE, BIT(0), 0पूर्ण,\
 /*रुको घातer state to suspend*/ \
	अणु0x0086, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK,\
		PWR_BASEADDR_SDIO, PWR_CMD_POLLING, BIT(1), BIT(1)पूर्ण,\
 /*0x04[12:11] = 2b'00 disable WL suspend*/ \
	अणु0x0005, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,\
		PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT(3)|BIT(4), 0पूर्ण,

/* क्रमmat */
/* अणु offset, cut_msk, fab_msk|पूर्णांकerface_msk, base|cmd, msk, value पूर्ण, */

#घोषणा RTL8723A_TRANS_CARDEMU_TO_CARDDIS \
 /*0x04[12:11] = 2b'01 enable WL suspend*/	 \
	अणु0x0005, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, \
		PWR_INTF_USB_MSK|PWR_INTF_SDIO_MSK, \
		PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT(3)|BIT(4), BIT(3)पूर्ण, \
/*0x04[10] = 1, enable SW LPS*/	\
	अणु0x0005, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, \
		PWR_INTF_PCI_MSK, PWR_BASEADDR_MAC,\
		PWR_CMD_WRITE, BIT(2), BIT(2)पूर्ण, \
/*Set SDIO suspend local रेजिस्टर*/ \
	अणु0x0086, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, \
		PWR_INTF_SDIO_MSK, PWR_BASEADDR_SDIO,\
		PWR_CMD_WRITE, BIT(0), BIT(0)पूर्ण, \
 /*रुको घातer state to suspend*/ \
	अणु0x0086, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, \
		PWR_INTF_SDIO_MSK, PWR_BASEADDR_SDIO,\
		PWR_CMD_POLLING, BIT(1), 0पूर्ण,

/* क्रमmat */
/* अणु offset, cut_msk, fab_msk|पूर्णांकerface_msk, base|cmd, msk, value पूर्ण, */

#घोषणा RTL8723A_TRANS_CARDDIS_TO_CARDEMU\
/*Set SDIO suspend local रेजिस्टर*/	\
	अणु0x0086, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, \
		PWR_INTF_SDIO_MSK, PWR_BASEADDR_SDIO,\
		PWR_CMD_WRITE, BIT(0), 0पूर्ण, \
 /*रुको घातer state to suspend*/ \
	अणु0x0086, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, \
		PWR_INTF_SDIO_MSK, PWR_BASEADDR_SDIO,\
		PWR_CMD_POLLING, BIT(1), BIT(1)पूर्ण,\
 /*0x04[12:11] = 2b'00 disable WL suspend*/ \
	अणु0x0005, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, \
		PWR_INTF_ALL_MSK, PWR_BASEADDR_MAC,\
		PWR_CMD_WRITE, BIT(3)|BIT(4), 0पूर्ण,\
/*PCIe DMA start*/ \
	अणु0x0301, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, \
		PWR_INTF_ALL_MSK, PWR_BASEADDR_MAC,\
		PWR_CMD_WRITE, 0xFF, 0पूर्ण,

/* क्रमmat */
/* अणु offset, cut_msk, fab_msk|पूर्णांकerface_msk, base|cmd, msk, value पूर्ण, */
#घोषणा RTL8723A_TRANS_CARDEMU_TO_PDN	\
	अणु0x0006, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, \
		PWR_INTF_ALL_MSK, PWR_BASEADDR_MAC,\
		PWR_CMD_WRITE, BIT(0), 0पूर्ण,/* 0x04[16] = 0*/\
	अणु0x0005, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, \
		PWR_INTF_ALL_MSK, PWR_BASEADDR_MAC,\
		PWR_CMD_WRITE, BIT(7), BIT(7)पूर्ण,/* 0x04[15] = 1*/

/* क्रमmat */
/* अणु offset, cut_msk, fab_msk|पूर्णांकerface_msk, base|cmd, msk, value पूर्ण, */
#घोषणा RTL8723A_TRANS_PDN_TO_CARDEMU	\
	अणु0x0005, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, \
		PWR_INTF_ALL_MSK, PWR_BASEADDR_MAC,\
		PWR_CMD_WRITE, BIT(7), 0पूर्ण,/* 0x04[15] = 0*/

/* क्रमmat */
/* अणु offset, cut_msk, fab_msk|पूर्णांकerface_msk, base|cmd, msk, value पूर्ण, */

#घोषणा RTL8723A_TRANS_ACT_TO_LPS	\
	अणु0x0301, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, \
		PWR_INTF_ALL_MSK, PWR_BASEADDR_MAC,\
		PWR_CMD_WRITE, 0xFF, 0xFFपूर्ण,/*PCIe DMA stop*/	\
	अणु0x0522, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, \
		PWR_INTF_ALL_MSK, PWR_BASEADDR_MAC,\
		PWR_CMD_WRITE, 0xFF, 0x7Fपूर्ण,/*Tx Pause*/	\
	/*Should be zero अगर no packet is transmitting*/	\
	अणु0x05F8, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, \
		PWR_INTF_ALL_MSK, PWR_BASEADDR_MAC,\
		PWR_CMD_POLLING, 0xFF, 0पूर्ण,\
	/*Should be zero अगर no packet is transmitting*/	\
	अणु0x05F9, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, \
		PWR_INTF_ALL_MSK, PWR_BASEADDR_MAC,\
		PWR_CMD_POLLING, 0xFF, 0पूर्ण,\
	/*Should be zero अगर no packet is transmitting*/	\
	अणु0x05FA, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, \
		PWR_INTF_ALL_MSK, PWR_BASEADDR_MAC,\
		PWR_CMD_POLLING, 0xFF, 0पूर्ण,\
	/*Should be zero अगर no packet is transmitting*/	\
	अणु0x05FB, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, \
		PWR_INTF_ALL_MSK, PWR_BASEADDR_MAC,\
		PWR_CMD_POLLING, 0xFF, 0पूर्ण,\
	/*CCK and OFDM are disabled,and घड़ी are gated*/ \
	अणु0x0002, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, \
		PWR_INTF_ALL_MSK, PWR_BASEADDR_MAC,\
		PWR_CMD_WRITE, BIT(0), 0पूर्ण,\
	अणु0x0002, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, \
		PWR_INTF_ALL_MSK, PWR_BASEADDR_MAC,\
		PWR_CMD_DELAY, 0, PWRSEQ_DELAY_USपूर्ण,/*Delay 1us*/\
	अणु0x0002, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, \
		PWR_INTF_ALL_MSK, PWR_BASEADDR_MAC,\
		PWR_CMD_WRITE, BIT(1), 0पूर्ण,/*Whole BB is reset*/	\
	अणु0x0100, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, \
		PWR_INTF_ALL_MSK, PWR_BASEADDR_MAC,\
		PWR_CMD_WRITE, 0xFF, 0x3Fपूर्ण,/*Reset MAC TRX*/	\
	अणु0x0101, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, \
		PWR_INTF_ALL_MSK, PWR_BASEADDR_MAC,\
		PWR_CMD_WRITE, BIT(1), 0पूर्ण,/*check अगर हटाओd later*/	\
	/*Respond TxOK to scheduler*/	\
	अणु0x0553, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, \
		PWR_INTF_ALL_MSK, PWR_BASEADDR_MAC,\
		PWR_CMD_WRITE, BIT(5), BIT(5)पूर्ण,\

#घोषणा RTL8723A_TRANS_LPS_TO_ACT\
/* क्रमmat */	\
/* अणु offset, cut_msk, fab_msk|पूर्णांकerface_msk, base|cmd, msk, value पूर्ण, */	\
	अणु0x0080, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, \
		PWR_INTF_SDIO_MSK, PWR_BASEADDR_SDIO,\
		PWR_CMD_WRITE, 0xFF, 0x84पूर्ण, /*SDIO RPWM*/\
	अणु0xFE58, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, \
		PWR_INTF_USB_MSK, PWR_BASEADDR_MAC,\
		PWR_CMD_WRITE, 0xFF, 0x84पूर्ण, /*USB RPWM*/\
	अणु0x0361, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, \
		PWR_INTF_PCI_MSK, PWR_BASEADDR_MAC,\
		PWR_CMD_WRITE, 0xFF, 0x84पूर्ण, /*PCIe RPWM*/\
	अणु0x0002, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, \
		PWR_INTF_ALL_MSK, PWR_BASEADDR_MAC,\
		PWR_CMD_DELAY, 0, PWRSEQ_DELAY_MSपूर्ण, /*Delay*/\
	/*.	0x08[4] = 0		 चयन TSF to 40M*/\
	अणु0x0008, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, \
		PWR_INTF_ALL_MSK, PWR_BASEADDR_MAC,\
		PWR_CMD_WRITE, BIT(4), 0पूर्ण,  \
	/*Polling 0x109[7]=0  TSF in 40M*/\
	अणु0x0109, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, \
		PWR_INTF_ALL_MSK, PWR_BASEADDR_MAC,\
		PWR_CMD_POLLING, BIT(7), 0पूर्ण, \
	/*.	0x29[7:6] = 2b'00	 enable BB घड़ी*/\
	अणु0x0029, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, \
		PWR_INTF_ALL_MSK, PWR_BASEADDR_MAC,\
		PWR_CMD_WRITE, BIT(6)|BIT(7), 0पूर्ण,\
	 /*.	0x101[1] = 1*/\
	अणु0x0101, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, \
		PWR_INTF_ALL_MSK, PWR_BASEADDR_MAC,\
		PWR_CMD_WRITE, BIT(1), BIT(1)पूर्ण,\
	 /*.	0x100[7:0] = 0xFF	 enable WMAC TRX*/\
	अणु0x0100, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, \
		PWR_INTF_ALL_MSK, PWR_BASEADDR_MAC,\
		PWR_CMD_WRITE, 0xFF, 0xFFपूर्ण,\
	 /*.	0x02[1:0] = 2b'11	 enable BB macro*/\
	अणु0x0002, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, \
		PWR_INTF_ALL_MSK, PWR_BASEADDR_MAC,\
		PWR_CMD_WRITE, BIT(1)|BIT(0), BIT(1)|BIT(0)पूर्ण,\
	अणु0x0522, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, \
		PWR_INTF_ALL_MSK, PWR_BASEADDR_MAC,\
		PWR_CMD_WRITE, 0xFF, 0पूर्ण, /*.	0x522 = 0*/

/* क्रमmat */
/* अणु offset, cut_msk, fab_msk|पूर्णांकerface_msk, base|cmd, msk, value पूर्ण, */

#घोषणा RTL8723A_TRANS_END \
	अणु0xFFFF, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,\
	0, PWR_CMD_END, 0, 0पूर्ण

बाह्य काष्ठा wlan_pwr_cfg rtl8723A_घातer_on_flow
		[RTL8723A_TRANS_CARDEMU_TO_ACT_STEPS +
		 RTL8723A_TRANS_END_STEPS];
बाह्य काष्ठा wlan_pwr_cfg rtl8723A_radio_off_flow
		[RTL8723A_TRANS_ACT_TO_CARDEMU_STEPS +
		 RTL8723A_TRANS_END_STEPS];
बाह्य काष्ठा wlan_pwr_cfg rtl8723A_card_disable_flow
		[RTL8723A_TRANS_ACT_TO_CARDEMU_STEPS +
		 RTL8723A_TRANS_CARDEMU_TO_PDN_STEPS +
		 RTL8723A_TRANS_END_STEPS];
बाह्य काष्ठा wlan_pwr_cfg rtl8723A_card_enable_flow
		[RTL8723A_TRANS_ACT_TO_CARDEMU_STEPS +
		 RTL8723A_TRANS_CARDEMU_TO_PDN_STEPS +
		 RTL8723A_TRANS_END_STEPS];
बाह्य काष्ठा wlan_pwr_cfg rtl8723A_suspend_flow
		[RTL8723A_TRANS_ACT_TO_CARDEMU_STEPS +
		 RTL8723A_TRANS_CARDEMU_TO_SUS_STEPS +
		 RTL8723A_TRANS_END_STEPS];
बाह्य काष्ठा wlan_pwr_cfg rtl8723A_resume_flow
		[RTL8723A_TRANS_ACT_TO_CARDEMU_STEPS +
		 RTL8723A_TRANS_CARDEMU_TO_SUS_STEPS +
		 RTL8723A_TRANS_END_STEPS];
बाह्य काष्ठा wlan_pwr_cfg rtl8723A_hwpdn_flow
		[RTL8723A_TRANS_ACT_TO_CARDEMU_STEPS +
		 RTL8723A_TRANS_CARDEMU_TO_PDN_STEPS +
		 RTL8723A_TRANS_END_STEPS];
बाह्य काष्ठा wlan_pwr_cfg rtl8723A_enter_lps_flow
		[RTL8723A_TRANS_ACT_TO_LPS_STEPS + RTL8723A_TRANS_END_STEPS];
बाह्य काष्ठा wlan_pwr_cfg rtl8723A_leave_lps_flow
		[RTL8723A_TRANS_LPS_TO_ACT_STEPS + RTL8723A_TRANS_END_STEPS];

/* RTL8723 Power Configuration CMDs क्रम PCIe पूर्णांकerface */
#घोषणा RTL8723_NIC_PWR_ON_FLOW		rtl8723A_घातer_on_flow
#घोषणा RTL8723_NIC_RF_OFF_FLOW		rtl8723A_radio_off_flow
#घोषणा RTL8723_NIC_DISABLE_FLOW	rtl8723A_card_disable_flow
#घोषणा RTL8723_NIC_ENABLE_FLOW		rtl8723A_card_enable_flow
#घोषणा RTL8723_NIC_SUSPEND_FLOW	rtl8723A_suspend_flow
#घोषणा RTL8723_NIC_RESUME_FLOW		rtl8723A_resume_flow
#घोषणा RTL8723_NIC_PDN_FLOW		rtl8723A_hwpdn_flow
#घोषणा RTL8723_NIC_LPS_ENTER_FLOW	rtl8723A_enter_lps_flow
#घोषणा RTL8723_NIC_LPS_LEAVE_FLOW	rtl8723A_leave_lps_flow

#पूर्ण_अगर
