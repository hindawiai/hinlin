<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2009-2013  Realtek Corporation.*/

#अगर_अघोषित __RTL8723E_PWRSEQ_H__
#घोषणा __RTL8723E_PWRSEQ_H__

#समावेश "../pwrseqcmd.h"
/* Check करोcument WM-20110607-Paul-RTL8188EE_Power_Architecture-R02.vsd
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
 *	PWR SEQ Version: rtl8188ee_PwrSeq_V09.h
 */

#घोषणा	RTL8188EE_TRANS_CARDEMU_TO_ACT_STEPS	10
#घोषणा	RTL8188EE_TRANS_ACT_TO_CARDEMU_STEPS	10
#घोषणा	RTL8188EE_TRANS_CARDEMU_TO_SUS_STEPS	10
#घोषणा	RTL8188EE_TRANS_SUS_TO_CARDEMU_STEPS	10
#घोषणा	RTL8188EE_TRANS_CARDEMU_TO_PDN_STEPS	10
#घोषणा	RTL8188EE_TRANS_PDN_TO_CARDEMU_STEPS	10
#घोषणा	RTL8188EE_TRANS_ACT_TO_LPS_STEPS		15
#घोषणा	RTL8188EE_TRANS_LPS_TO_ACT_STEPS		15
#घोषणा	RTL8188EE_TRANS_END_STEPS		1

/* The following macros have the following क्रमmat:
 * अणु offset, cut_msk, fab_msk|पूर्णांकerface_msk, base|cmd, msk, value
 *   comments पूर्ण,
 */
#घोषणा RTL8188EE_TRANS_CARDEMU_TO_ACT					\
	अणु0x0006, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,	\
	PWR_BASEADDR_MAC, PWR_CMD_POLLING, BIT(1), BIT(1)		\
	/* रुको till 0x04[17] = 1    घातer पढ़ोy*/पूर्ण,			\
	अणु0x0002, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,	\
	PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT(0)|BIT(1), 0		\
	/* 0x02[1:0] = 0	reset BB*/पूर्ण,				\
	अणु0x0026, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,	\
	PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT(7), BIT(7)			\
	/*0x24[23] = 2b'01 schmit trigger */पूर्ण,				\
	अणु0x0005, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,	\
	PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT(7), 0			\
	/* 0x04[15] = 0 disable HWPDN (control by DRV)*/पूर्ण,		\
	अणु0x0005, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,	\
	PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT(4)|BIT(3), 0		\
	/*0x04[12:11] = 2b'00 disable WL suspend*/पूर्ण,			\
	अणु0x0005, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,	\
	PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT(0), BIT(0)			\
	/*0x04[8] = 1 polling until वापस 0*/पूर्ण,			\
	अणु0x0005, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,	\
	PWR_BASEADDR_MAC, PWR_CMD_POLLING, BIT(0), 0			\
	/*रुको till 0x04[8] = 0*/पूर्ण,					\
	अणु0x0023, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,	\
	PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT(4), 0			\
	/*LDO normal mode*/पूर्ण,						\
	अणु0x0074, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK,	\
	PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT(4), BIT(4)			\
	/*SDIO Driving*/पूर्ण,

#घोषणा RTL8188EE_TRANS_ACT_TO_CARDEMU					\
	अणु0x001F, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,	\
	PWR_BASEADDR_MAC, PWR_CMD_WRITE, 0xFF, 0			\
	/*0x1F[7:0] = 0 turn off RF*/पूर्ण,					\
	अणु0x0023, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,	\
	PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT(4), BIT(4)			\
	/*LDO Sleep mode*/पूर्ण,						\
	अणु0x0005, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,	\
	PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT(1), BIT(1)			\
	/*0x04[9] = 1 turn off MAC by HW state machine*/पूर्ण,		\
	अणु0x0005, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,	\
	PWR_BASEADDR_MAC, PWR_CMD_POLLING, BIT(1), 0			\
	/*रुको till 0x04[9] = 0 polling until वापस 0 to disable*/पूर्ण,

#घोषणा RTL8188EE_TRANS_CARDEMU_TO_SUS					\
	अणु0x0005, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK,			\
	PWR_INTF_USB_MSK|PWR_INTF_SDIO_MSK,				\
	PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT(3)|BIT(4), BIT(3)		\
	/*0x04[12:11] = 2b'01enable WL suspend*/पूर्ण,			\
	अणु0x0005, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_PCI_MSK,	\
	PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT(3)|BIT(4), BIT(3)|BIT(4)	\
	/*0x04[12:11] = 2b'11enable WL suspend क्रम PCIe*/पूर्ण,		\
	अणु0x0007, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK,			\
	PWR_INTF_USB_MSK|PWR_INTF_SDIO_MSK,				\
	PWR_BASEADDR_MAC, PWR_CMD_WRITE, 0xFF, BIT(7)			\
	/*  0x04[31:30] = 2b'10 enable enable bandgap mbias in suspend */पूर्ण,\
	अणु0x0041, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK,			\
	PWR_INTF_USB_MSK|PWR_INTF_SDIO_MSK,				\
	PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT(4), 0			\
	/*Clear SIC_EN रेजिस्टर 0x40[12] = 1'b0 */पूर्ण,			\
	अणु0xfe10, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK,			\
	PWR_INTF_USB_MSK|PWR_INTF_SDIO_MSK,				\
	PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT(4), BIT(4)			\
	/*Set USB suspend enable local रेजिस्टर  0xfe10[4]=1 */पूर्ण,	\
	अणु0x0086, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK,	\
	PWR_BASEADDR_SDIO, PWR_CMD_WRITE, BIT(0), BIT(0)		\
	/*Set SDIO suspend local रेजिस्टर*/पूर्ण,				\
	अणु0x0086, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK,	\
	PWR_BASEADDR_SDIO, PWR_CMD_POLLING, BIT(1), 0			\
	/*रुको घातer state to suspend*/पूर्ण,

#घोषणा RTL8188EE_TRANS_SUS_TO_CARDEMU					\
	अणु0x0086, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK,	\
	PWR_BASEADDR_SDIO, PWR_CMD_WRITE, BIT(0), 0			\
	/*Set SDIO suspend local रेजिस्टर*/पूर्ण,				\
	अणु0x0086, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK,	\
	PWR_BASEADDR_SDIO, PWR_CMD_POLLING, BIT(1), BIT(1)		\
	/*रुको घातer state to suspend*/पूर्ण,				\
	अणु0x0005, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,	\
	PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT(3) | BIT(4), 0		\
	/*0x04[12:11] = 2b'00 disable WL suspend*/पूर्ण,

#घोषणा RTL8188EE_TRANS_CARDEMU_TO_CARDDIS				\
	अणु0x0026, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,	\
	PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT(7), BIT(7)			\
	/*0x24[23] = 2b'01 schmit trigger */पूर्ण,				\
	अणु0x0005, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK,			\
	PWR_INTF_USB_MSK|PWR_INTF_SDIO_MSK,				\
	PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT(3) | BIT(4), BIT(3)	\
	/*0x04[12:11] = 2b'01 enable WL suspend*/पूर्ण,			\
	अणु0x0007, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK,			\
	PWR_INTF_USB_MSK|PWR_INTF_SDIO_MSK,				\
	PWR_BASEADDR_MAC, PWR_CMD_WRITE, 0xFF, 0			\
	/*  0x04[31:30] = 2b'10 enable enable bandgap mbias in suspend */पूर्ण,\
	अणु0x0041, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK,			\
	PWR_INTF_USB_MSK|PWR_INTF_SDIO_MSK,				\
	PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT(4), 0			\
	/*Clear SIC_EN रेजिस्टर 0x40[12] = 1'b0 */पूर्ण,			\
	अणु0xfe10, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_USB_MSK,	\
	PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT(4), BIT(4)			\
	/*Set USB suspend enable local रेजिस्टर  0xfe10[4]=1 */पूर्ण,	\
	अणु0x0086, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK,	\
	PWR_BASEADDR_SDIO, PWR_CMD_WRITE, BIT(0), BIT(0)		\
	/*Set SDIO suspend local रेजिस्टर*/पूर्ण,				\
	अणु0x0086, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK,	\
	PWR_BASEADDR_SDIO, PWR_CMD_POLLING, BIT(1), 0			\
	/*रुको घातer state to suspend*/पूर्ण,

#घोषणा RTL8188EE_TRANS_CARDDIS_TO_CARDEMU				\
	अणु0x0086, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK,	\
	PWR_BASEADDR_SDIO, PWR_CMD_WRITE, BIT(0), 0			\
	/*Set SDIO suspend local रेजिस्टर*/पूर्ण,				\
	अणु0x0086, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK,	\
	PWR_BASEADDR_SDIO, PWR_CMD_POLLING, BIT(1), BIT(1)		\
	/*रुको घातer state to suspend*/पूर्ण,				\
	अणु0x0005, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,	\
	PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT(3)|BIT(4), 0		\
	/*0x04[12:11] = 2b'00 disable WL suspend*/पूर्ण,

#घोषणा RTL8188EE_TRANS_CARDEMU_TO_PDN					\
	अणु0x0006, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,	\
	PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT(0), 0/* 0x04[16] = 0*/पूर्ण,	\
	अणु0x0005, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,	\
	PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT(7), BIT(7)			\
	/* 0x04[15] = 1*/पूर्ण,

#घोषणा RTL8188EE_TRANS_PDN_TO_CARDEMU					\
	अणु0x0005, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,	\
	PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT(7), 0/* 0x04[15] = 0*/पूर्ण,

#घोषणा RTL8188EE_TRANS_ACT_TO_LPS					\
	अणु0x0522, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,	\
	PWR_BASEADDR_MAC, PWR_CMD_WRITE, 0xFF, 0x7F			\
	/*Tx Pause*/पूर्ण,							\
	अणु0x05F8, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,	\
	PWR_BASEADDR_MAC, PWR_CMD_POLLING, 0xFF, 0			\
	/*Should be zero अगर no packet is transmitting*/पूर्ण,		\
	अणु0x05F9, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,	\
	PWR_BASEADDR_MAC, PWR_CMD_POLLING, 0xFF, 0			\
	/*Should be zero अगर no packet is transmitting*/पूर्ण,		\
	अणु0x05FA, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,	\
	PWR_BASEADDR_MAC, PWR_CMD_POLLING, 0xFF, 0			\
	/*Should be zero अगर no packet is transmitting*/पूर्ण,		\
	अणु0x05FB, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,	\
	PWR_BASEADDR_MAC, PWR_CMD_POLLING, 0xFF, 0			\
	/*Should be zero अगर no packet is transmitting*/पूर्ण,		\
	अणु0x0002, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,	\
	PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT(0), 0			\
	/*CCK and OFDM are disabled,and घड़ी are gated*/पूर्ण,		\
	अणु0x0002, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,	\
	PWR_BASEADDR_MAC, PWR_CMD_DELAY, 0, PWRSEQ_DELAY_US		\
	/*Delay 1us*/पूर्ण,							\
	अणु0x0100, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,	\
	PWR_BASEADDR_MAC, PWR_CMD_WRITE, 0xFF, 0x3F			\
	/*Reset MAC TRX*/पूर्ण,						\
	अणु0x0101, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,	\
	PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT(1), 0			\
	/*check अगर हटाओd later*/पूर्ण,					\
	अणु0x0553, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,	\
	PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT(5), BIT(5)			\
	/*Respond TxOK to scheduler*/पूर्ण,


#घोषणा RTL8188EE_TRANS_LPS_TO_ACT					\
	अणु0x0080, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK,	\
	PWR_BASEADDR_SDIO, PWR_CMD_WRITE, 0xFF, 0x84			\
	/*SDIO RPWM*/पूर्ण,							\
	अणु0xFE58, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_USB_MSK,	\
	PWR_BASEADDR_MAC, PWR_CMD_WRITE, 0xFF, 0x84			\
	/*USB RPWM*/पूर्ण,							\
	अणु0x0361, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_PCI_MSK,	\
	PWR_BASEADDR_MAC, PWR_CMD_WRITE, 0xFF, 0x84			\
	/*PCIe RPWM*/पूर्ण,							\
	अणु0x0002, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,	\
	PWR_BASEADDR_MAC, PWR_CMD_DELAY, 0, PWRSEQ_DELAY_MS		\
	/*Delay*/पूर्ण,							\
	अणु0x0008, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,	\
	PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT(4), 0			\
	/*.	0x08[4] = 0		 चयन TSF to 40M*/पूर्ण,		\
	अणु0x0109, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,	\
	PWR_BASEADDR_MAC, PWR_CMD_POLLING, BIT(7), 0			\
	/*Polling 0x109[7]=0  TSF in 40M*/पूर्ण,				\
	अणु0x0029, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,	\
	PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT(6)|BIT(7), 0		\
	/*.	0x29[7:6] = 2b'00	 enable BB घड़ी*/पूर्ण,		\
	अणु0x0101, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,	\
	PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT(1), BIT(1)			\
	/*.	0x101[1] = 1*/पूर्ण,					\
	अणु0x0100, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,	\
	PWR_BASEADDR_MAC, PWR_CMD_WRITE, 0xFF, 0xFF			\
	/*.	0x100[7:0] = 0xFF	 enable WMAC TRX*/पूर्ण,		\
	अणु0x0002, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,	\
	PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT(1)|BIT(0), BIT(1)|BIT(0)	\
	/*.	0x02[1:0] = 2b'11	 enable BB macro*/पूर्ण,		\
	अणु0x0522, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,	\
	PWR_BASEADDR_MAC, PWR_CMD_WRITE, 0xFF, 0			\
	/*.	0x522 = 0*/पूर्ण,

#घोषणा RTL8188EE_TRANS_END		\
	अणु0xFFFF, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,\
	0, PWR_CMD_END, 0, 0पूर्ण

बाह्य काष्ठा wlan_pwr_cfg rtl8188ee_घातer_on_flow
		[RTL8188EE_TRANS_CARDEMU_TO_ACT_STEPS +
		 RTL8188EE_TRANS_END_STEPS];
बाह्य काष्ठा wlan_pwr_cfg rtl8188ee_radio_off_flow
		[RTL8188EE_TRANS_ACT_TO_CARDEMU_STEPS +
		 RTL8188EE_TRANS_END_STEPS];
बाह्य काष्ठा wlan_pwr_cfg rtl8188ee_card_disable_flow
		[RTL8188EE_TRANS_ACT_TO_CARDEMU_STEPS +
		 RTL8188EE_TRANS_CARDEMU_TO_PDN_STEPS +
		 RTL8188EE_TRANS_END_STEPS];
बाह्य काष्ठा wlan_pwr_cfg rtl8188ee_card_enable_flow
		[RTL8188EE_TRANS_ACT_TO_CARDEMU_STEPS +
		 RTL8188EE_TRANS_CARDEMU_TO_PDN_STEPS +
		 RTL8188EE_TRANS_END_STEPS];
बाह्य काष्ठा wlan_pwr_cfg rtl8188ee_suspend_flow
		[RTL8188EE_TRANS_ACT_TO_CARDEMU_STEPS +
		 RTL8188EE_TRANS_CARDEMU_TO_SUS_STEPS +
		 RTL8188EE_TRANS_END_STEPS];
बाह्य काष्ठा wlan_pwr_cfg rtl8188ee_resume_flow
		[RTL8188EE_TRANS_ACT_TO_CARDEMU_STEPS +
		 RTL8188EE_TRANS_CARDEMU_TO_SUS_STEPS +
		 RTL8188EE_TRANS_END_STEPS];
बाह्य काष्ठा wlan_pwr_cfg rtl8188ee_hwpdn_flow
		[RTL8188EE_TRANS_ACT_TO_CARDEMU_STEPS +
		 RTL8188EE_TRANS_CARDEMU_TO_PDN_STEPS +
		 RTL8188EE_TRANS_END_STEPS];
बाह्य काष्ठा wlan_pwr_cfg rtl8188ee_enter_lps_flow
		[RTL8188EE_TRANS_ACT_TO_LPS_STEPS +
		 RTL8188EE_TRANS_END_STEPS];
बाह्य काष्ठा wlan_pwr_cfg rtl8188ee_leave_lps_flow
		[RTL8188EE_TRANS_LPS_TO_ACT_STEPS +
		 RTL8188EE_TRANS_END_STEPS];

/* RTL8723 Power Configuration CMDs क्रम PCIe पूर्णांकerface */
#घोषणा RTL8188EE_NIC_PWR_ON_FLOW	rtl8188ee_घातer_on_flow
#घोषणा RTL8188EE_NIC_RF_OFF_FLOW	rtl8188ee_radio_off_flow
#घोषणा RTL8188EE_NIC_DISABLE_FLOW	rtl8188ee_card_disable_flow
#घोषणा RTL8188EE_NIC_ENABLE_FLOW	rtl8188ee_card_enable_flow
#घोषणा RTL8188EE_NIC_SUSPEND_FLOW	rtl8188ee_suspend_flow
#घोषणा RTL8188EE_NIC_RESUME_FLOW	rtl8188ee_resume_flow
#घोषणा RTL8188EE_NIC_PDN_FLOW		rtl8188ee_hwpdn_flow
#घोषणा RTL8188EE_NIC_LPS_ENTER_FLOW	rtl8188ee_enter_lps_flow
#घोषणा RTL8188EE_NIC_LPS_LEAVE_FLOW	rtl8188ee_leave_lps_flow

#पूर्ण_अगर
