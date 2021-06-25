<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित REALTEK_POWER_SEQUENCE_8723B
#घोषणा REALTEK_POWER_SEQUENCE_8723B

#समावेश "HalPwrSeqCmd.h"

/*
	Check करोcument WM-20130815-JackieLau-RTL8723B_Power_Architecture v08.vsd
	There are 6 HW Power States:
	0: POFF--Power Off
	1: PDN--Power Down
	2: CARDEMU--Card Emulation
	3: ACT--Active Mode
	4: LPS--Low Power State
	5: SUS--Suspend

	The transition from dअगरferent states are defined below
	TRANS_CARDEMU_TO_ACT
	TRANS_ACT_TO_CARDEMU
	TRANS_CARDEMU_TO_SUS
	TRANS_SUS_TO_CARDEMU
	TRANS_CARDEMU_TO_PDN
	TRANS_ACT_TO_LPS
	TRANS_LPS_TO_ACT

	TRANS_END
*/
#घोषणा	RTL8723B_TRANS_CARDEMU_TO_ACT_STEPS	26
#घोषणा	RTL8723B_TRANS_ACT_TO_CARDEMU_STEPS	15
#घोषणा	RTL8723B_TRANS_CARDEMU_TO_SUS_STEPS	15
#घोषणा	RTL8723B_TRANS_SUS_TO_CARDEMU_STEPS	15
#घोषणा	RTL8723B_TRANS_CARDEMU_TO_PDN_STEPS	15
#घोषणा	RTL8723B_TRANS_PDN_TO_CARDEMU_STEPS	15
#घोषणा	RTL8723B_TRANS_ACT_TO_LPS_STEPS		15
#घोषणा	RTL8723B_TRANS_LPS_TO_ACT_STEPS		15
#घोषणा	RTL8723B_TRANS_ACT_TO_SWLPS_STEPS		22
#घोषणा	RTL8723B_TRANS_SWLPS_TO_ACT_STEPS		15
#घोषणा	RTL8723B_TRANS_END_STEPS		1


#घोषणा RTL8723B_TRANS_CARDEMU_TO_ACT														\
	/* क्रमmat */																\
	/* अणु offset, cut_msk, fab_msk|पूर्णांकerface_msk, base|cmd, msk, value पूर्ण,  comments here*/								\
	अणु0x0020, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_USB_MSK|PWR_INTF_SDIO_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT0, BIT0पूर्ण, /*0x20[0] = 1b'1 enable LDOA12 MACRO block क्रम all पूर्णांकerface*/   \
	अणु0x0067, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_USB_MSK|PWR_INTF_SDIO_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT4, 0पूर्ण, /*0x67[0] = 0 to disable BT_GPS_SEL pins*/	\
	अणु0x0001, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_USB_MSK|PWR_INTF_SDIO_MSK, PWR_BASEADDR_MAC, PWR_CMD_DELAY, 1, PWRSEQ_DELAY_MSपूर्ण,/*Delay 1ms*/   \
	अणु0x0000, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_USB_MSK|PWR_INTF_SDIO_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT5, 0पूर्ण, /*0x00[5] = 1b'0 release analog Ips to digital , 1:isolation*/   \
	अणु0x0005, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, (BIT4|BIT3|BIT2), 0पूर्ण,/* disable SW LPS 0x04[10]= 0 and WLSUS_EN 0x04[11]= 0*/	\
	अणु0x0075, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_PCI_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT0, BIT0पूर्ण,/* Disable USB suspend */	\
	अणु0x0006, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK, PWR_BASEADDR_MAC, PWR_CMD_POLLING, BIT1, BIT1पूर्ण,/* रुको till 0x04[17] = 1    घातer पढ़ोy*/	\
	अणु0x0075, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_PCI_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT0, 0पूर्ण,/* Enable USB suspend */	\
	अणु0x0006, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT0, BIT0पूर्ण,/* release WLON reset  0x04[16]= 1*/	\
	अणु0x0005, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT7, 0पूर्ण,/* disable HWPDN 0x04[15]= 0*/	\
	अणु0x0005, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, (BIT4|BIT3), 0पूर्ण,/* disable WL suspend*/	\
	अणु0x0005, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT0, BIT0पूर्ण,/* polling until वापस 0*/	\
	अणु0x0005, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK, PWR_BASEADDR_MAC, PWR_CMD_POLLING, BIT0, 0पूर्ण,/**/	\
	अणु0x0010, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT6, BIT6पूर्ण,/* Enable WL control XTAL setting*/	\
	अणु0x0049, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT1, BIT1पूर्ण,/*Enable falling edge triggering पूर्णांकerrupt*/\
	अणु0x0063, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT1, BIT1पूर्ण,/*Enable GPIO9 पूर्णांकerrupt mode*/\
	अणु0x0062, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT1, 0पूर्ण,/*Enable GPIO9 input mode*/\
	अणु0x0058, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT0, BIT0पूर्ण,/*Enable HSISR GPIO[C:0] पूर्णांकerrupt*/\
	अणु0x005A, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT1, BIT1पूर्ण,/*Enable HSISR GPIO9 पूर्णांकerrupt*/\
	अणु0x0068, PWR_CUT_TESTCHIP_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT3, BIT3पूर्ण,/*For GPIO9 पूर्णांकernal pull high setting by test chip*/\
	अणु0x0069, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT6, BIT6पूर्ण,/*For GPIO9 पूर्णांकernal pull high setting*/\


#घोषणा RTL8723B_TRANS_ACT_TO_CARDEMU													\
	/* क्रमmat */																\
	/* अणु offset, cut_msk, fab_msk|पूर्णांकerface_msk, base|cmd, msk, value पूर्ण,  comments here*/								\
	अणु0x001F, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, 0xFF, 0पूर्ण,/*0x1F[7:0] = 0 turn off RF*/	\
	अणु0x0049, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT1, 0पूर्ण,/*Enable rising edge triggering पूर्णांकerrupt*/ \
	अणु0x0006, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT0, BIT0पूर्ण,/* release WLON reset  0x04[16]= 1*/	\
	अणु0x0005, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT1, BIT1पूर्ण, /*0x04[9] = 1 turn off MAC by HW state machine*/	\
	अणु0x0005, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK, PWR_BASEADDR_MAC, PWR_CMD_POLLING, BIT1, 0पूर्ण, /*रुको till 0x04[9] = 0 polling until वापस 0 to disable*/	\
	अणु0x0010, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT6, 0पूर्ण,/* Enable BT control XTAL setting*/\
	अणु0x0000, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_USB_MSK|PWR_INTF_SDIO_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT5, BIT5पूर्ण, /*0x00[5] = 1b'1 analog Ips to digital , 1:isolation*/   \
	अणु0x0020, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_USB_MSK|PWR_INTF_SDIO_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT0, 0पूर्ण, /*0x20[0] = 1b'0 disable LDOA12 MACRO block*/\


#घोषणा RTL8723B_TRANS_CARDEMU_TO_SUS													\
	/* क्रमmat */																\
	/* अणु offset, cut_msk, fab_msk|पूर्णांकerface_msk, base|cmd, msk, value पूर्ण,  comments here*/								\
	अणु0x0005, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_PCI_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT4|BIT3, (BIT4|BIT3)पूर्ण, /*0x04[12:11] = 2b'11 enable WL suspend क्रम PCIe*/	\
	अणु0x0005, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_USB_MSK|PWR_INTF_SDIO_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT3|BIT4, BIT3पूर्ण, /*0x04[12:11] = 2b'01 enable WL suspend*/	\
	अणु0x0023, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT4, BIT4पूर्ण, /*0x23[4] = 1b'1 12H LDO enter sleep mode*/   \
	अणु0x0007, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, 0xFF, 0x20पूर्ण, /*0x07[7:0] = 0x20 SDIO SOP option to disable BG/MB/ACK/SWR*/   \
	अणु0x0005, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_PCI_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT3|BIT4, BIT3|BIT4पूर्ण, /*0x04[12:11] = 2b'11 enable WL suspend क्रम PCIe*/	\
	अणु0x0086, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK, PWR_BASEADDR_SDIO, PWR_CMD_WRITE, BIT0, BIT0पूर्ण, /*Set SDIO suspend local रेजिस्टर*/	\
	अणु0x0086, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK, PWR_BASEADDR_SDIO, PWR_CMD_POLLING, BIT1, 0पूर्ण, /*रुको घातer state to suspend*/

#घोषणा RTL8723B_TRANS_SUS_TO_CARDEMU													\
	/* क्रमmat */																\
	/* अणु offset, cut_msk, fab_msk|पूर्णांकerface_msk, base|cmd, msk, value पूर्ण,  comments here*/								\
	अणु0x0005, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT3 | BIT7, 0पूर्ण, /*clear suspend enable and घातer करोwn enable*/	\
	अणु0x0086, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK, PWR_BASEADDR_SDIO, PWR_CMD_WRITE, BIT0, 0पूर्ण, /*Set SDIO suspend local रेजिस्टर*/	\
	अणु0x0086, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK, PWR_BASEADDR_SDIO, PWR_CMD_POLLING, BIT1, BIT1पूर्ण, /*रुको घातer state to suspend*/\
	अणु0x0023, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT4, 0पूर्ण, /*0x23[4] = 1b'0 12H LDO enter normal mode*/   \
	अणु0x0005, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT3|BIT4, 0पूर्ण, /*0x04[12:11] = 2b'01enable WL suspend*/

#घोषणा RTL8723B_TRANS_CARDEMU_TO_CARDDIS													\
	/* क्रमmat */																\
	/* अणु offset, cut_msk, fab_msk|पूर्णांकerface_msk, base|cmd, msk, value पूर्ण, omments here*/								\
	अणु0x0007, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, 0xFF, 0x20पूर्ण, /*0x07 = 0x20 , SOP option to disable BG/MB*/	\
	अणु0x0005, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_USB_MSK|PWR_INTF_SDIO_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT3|BIT4, BIT3पूर्ण, /*0x04[12:11] = 2b'01 enable WL suspend*/	\
	अणु0x0005, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_PCI_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT2, BIT2पूर्ण, /*0x04[10] = 1, enable SW LPS*/	\
        अणु0x004A, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_USB_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT0, 1पूर्ण, /*0x48[16] = 1 to enable GPIO9 as EXT WAKEUP*/   \
	अणु0x0023, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT4, BIT4पूर्ण, /*0x23[4] = 1b'1 12H LDO enter sleep mode*/   \
	अणु0x0086, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK, PWR_BASEADDR_SDIO, PWR_CMD_WRITE, BIT0, BIT0पूर्ण, /*Set SDIO suspend local रेजिस्टर*/	\
	अणु0x0086, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK, PWR_BASEADDR_SDIO, PWR_CMD_POLLING, BIT1, 0पूर्ण, /*रुको घातer state to suspend*/

#घोषणा RTL8723B_TRANS_CARDDIS_TO_CARDEMU													\
	/* क्रमmat */																\
	/* अणु offset, cut_msk, fab_msk|पूर्णांकerface_msk, base|cmd, msk, value पूर्ण, comments here*/								\
	अणु0x0005, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT3 | BIT7, 0पूर्ण, /*clear suspend enable and घातer करोwn enable*/	\
	अणु0x0086, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK, PWR_BASEADDR_SDIO, PWR_CMD_WRITE, BIT0, 0पूर्ण, /*Set SDIO suspend local रेजिस्टर*/	\
	अणु0x0086, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK, PWR_BASEADDR_SDIO, PWR_CMD_POLLING, BIT1, BIT1पूर्ण, /*रुको घातer state to suspend*/\
        अणु0x004A, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_USB_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT0, 0पूर्ण, /*0x48[16] = 0 to disable GPIO9 as EXT WAKEUP*/   \
	अणु0x0005, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT3|BIT4, 0पूर्ण, /*0x04[12:11] = 2b'01enable WL suspend*/\
	अणु0x0023, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT4, 0पूर्ण, /*0x23[4] = 1b'0 12H LDO enter normal mode*/   \
	अणु0x0301, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_PCI_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, 0xFF, 0पूर्ण,/*PCIe DMA start*/


#घोषणा RTL8723B_TRANS_CARDEMU_TO_PDN												\
	/* क्रमmat */																\
	/* अणु offset, cut_msk, fab_msk|पूर्णांकerface_msk, base|cmd, msk, value पूर्ण, comments here*/								\
	अणु0x0023, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT4, BIT4पूर्ण, /*0x23[4] = 1b'1 12H LDO enter sleep mode*/   \
	अणु0x0007, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK|PWR_INTF_USB_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, 0xFF, 0x20पूर्ण, /*0x07[7:0] = 0x20 SOP option to disable BG/MB/ACK/SWR*/   \
	अणु0x0006, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT0, 0पूर्ण,/* 0x04[16] = 0*/\
	अणु0x0005, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT7, BIT7पूर्ण,/* 0x04[15] = 1*/

#घोषणा RTL8723B_TRANS_PDN_TO_CARDEMU												\
	/* क्रमmat */																\
	/* अणु offset, cut_msk, fab_msk|पूर्णांकerface_msk, base|cmd, msk, value पूर्ण, comments here*/								\
	अणु0x0005, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT7, 0पूर्ण,/* 0x04[15] = 0*/

#घोषणा RTL8723B_TRANS_ACT_TO_LPS														\
	/* क्रमmat */																\
	/* अणु offset, cut_msk, fab_msk|पूर्णांकerface_msk, base|cmd, msk, value पूर्ण, comments here*/								\
	अणु0x0301, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_PCI_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, 0xFF, 0xFFपूर्ण,/*PCIe DMA stop*/	\
	अणु0x0522, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, 0xFF, 0xFFपूर्ण,/*Tx Pause*/	\
	अणु0x05F8, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK, PWR_BASEADDR_MAC, PWR_CMD_POLLING, 0xFF, 0पूर्ण,/*Should be zero अगर no packet is transmitting*/	\
	अणु0x05F9, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK, PWR_BASEADDR_MAC, PWR_CMD_POLLING, 0xFF, 0पूर्ण,/*Should be zero अगर no packet is transmitting*/	\
	अणु0x05FA, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK, PWR_BASEADDR_MAC, PWR_CMD_POLLING, 0xFF, 0पूर्ण,/*Should be zero अगर no packet is transmitting*/	\
	अणु0x05FB, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK, PWR_BASEADDR_MAC, PWR_CMD_POLLING, 0xFF, 0पूर्ण,/*Should be zero अगर no packet is transmitting*/	\
	अणु0x0002, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT0, 0पूर्ण,/*CCK and OFDM are disabled, and घड़ी are gated*/	\
	अणु0x0002, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK, PWR_BASEADDR_MAC, PWR_CMD_DELAY, 0, PWRSEQ_DELAY_USपूर्ण,/*Delay 1us*/	\
	अणु0x0002, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT1, 0पूर्ण,/*Whole BB is reset*/	\
	अणु0x0100, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, 0xFF, 0x03पूर्ण,/*Reset MAC TRX*/	\
	अणु0x0101, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT1, 0पूर्ण,/*check अगर हटाओd later*/	\
	अणु0x0093, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, 0xFF, 0x00पूर्ण,/*When driver enter Sus/ Disable, enable LOP क्रम BT*/	\
	अणु0x0553, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT5, BIT5पूर्ण,/*Respond TxOK to scheduler*/	\


#घोषणा RTL8723B_TRANS_LPS_TO_ACT															\
	/* क्रमmat */																\
	/* अणु offset, cut_msk, fab_msk|पूर्णांकerface_msk, base|cmd, msk, value पूर्ण, comments here*/								\
	अणु0x0080, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK, PWR_BASEADDR_SDIO, PWR_CMD_WRITE, 0xFF, 0x84पूर्ण, /*SDIO RPWM*/\
	अणु0xFE58, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_USB_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, 0xFF, 0x84पूर्ण, /*USB RPWM*/\
	अणु0x0361, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_PCI_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, 0xFF, 0x84पूर्ण, /*PCIe RPWM*/\
	अणु0x0002, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK, PWR_BASEADDR_MAC, PWR_CMD_DELAY, 0, PWRSEQ_DELAY_MSपूर्ण, /*Delay*/\
	अणु0x0008, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT4, 0पूर्ण, /*.	0x08[4] = 0		 चयन TSF to 40M*/\
	अणु0x0109, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK, PWR_BASEADDR_MAC, PWR_CMD_POLLING, BIT7, 0पूर्ण, /*Polling 0x109[7]= 0  TSF in 40M*/\
	अणु0x0029, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT6|BIT7, 0पूर्ण, /*.	0x29[7:6] = 2b'00	 enable BB घड़ी*/\
	अणु0x0101, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT1, BIT1पूर्ण, /*.	0x101[1] = 1*/\
	अणु0x0100, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, 0xFF, 0xFFपूर्ण, /*.	0x100[7:0] = 0xFF	 enable WMAC TRX*/\
	अणु0x0002, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT1|BIT0, BIT1|BIT0पूर्ण, /*.	0x02[1:0] = 2b'11	 enable BB macro*/\
	अणु0x0522, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, 0xFF, 0पूर्ण, /*.	0x522 = 0*/


 #घोषणा RTL8723B_TRANS_ACT_TO_SWLPS														\
	/* क्रमmat */																\
	/* अणु offset, cut_msk, fab_msk|पूर्णांकerface_msk, base|cmd, msk, value पूर्ण, comments here*/								\
	अणु0x0194, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT0, BIT0पूर्ण,/*enable 32 K source*/	\
	अणु0x0002, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT0, 0पूर्ण,/*CCK and OFDM are disabled, and घड़ी are gated*/	\
	अणु0x0002, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT0, 1पूर्ण,/*CCK and OFDM are enable*/	\
	अणु0x0002, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT0, 0पूर्ण,/*CCK and OFDM are disabled, and घड़ी are gated*/	\
	अणु0x0002, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT0, 1पूर्ण,/*CCK and OFDM are enable*/	\
	अणु0x0002, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT0, 0पूर्ण,/*CCK and OFDM are disabled, and घड़ी are gated*/	\
	अणु0x0100, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, 0xFF, 0x3Fपूर्ण,/*Reset MAC TRX*/	\
	अणु0x0101, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT1, 0पूर्ण,/*disable security engine*/	\
	अणु0x0093, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, 0xFF, 0x40पूर्ण,/*When driver enter Sus/ Disable, enable LOP क्रम BT*/	\
	अणु0x0553, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT5, BIT5पूर्ण,/*reset dual TSF*/	\
	अणु0x0003, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT2, 0पूर्ण,/*Reset CPU*/	\
	अणु0x0080, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, 0xFF, 0पूर्ण,/*Reset MCUFWDL रेजिस्टर*/	\
	अणु0x001D, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT0, 0पूर्ण,/*Reset CPU IO Wrapper*/	\
	अणु0x001D, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT0, 1पूर्ण,/*Reset CPU IO Wrapper*/	\
	अणु0x0287, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK, PWR_BASEADDR_MAC, PWR_CMD_POLLING, 0xFF, 0पूर्ण,/*polling RXFF packet number = 0 */	\
	अणु0x0286, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK, PWR_BASEADDR_MAC, PWR_CMD_POLLING, BIT1, BIT1पूर्ण,/*polling RXDMA idle */	\
	अणु0x013D, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT0, BIT0पूर्ण,/*Clear FW RPWM पूर्णांकerrupt */\
	अणु0x0139, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT0, BIT0पूर्ण,/*Set FW RPWM पूर्णांकerrupt source*/\
	अणु0x0008, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT4, BIT4पूर्ण,/*चयन TSF to 32K*/\
	अणु0x0109, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT7, BIT7पूर्ण,/*polling TSF stable*/\
	अणु0x0090, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT0, BIT0पूर्ण,/*Set FW LPS*/	\
	अणु0x0090, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK, PWR_BASEADDR_MAC, PWR_CMD_POLLING, BIT0, 0पूर्ण,/*polling FW LPS पढ़ोy */


#घोषणा RTL8723B_TRANS_SWLPS_TO_ACT															\
	/* क्रमmat */																\
	/* अणु offset, cut_msk, fab_msk|पूर्णांकerface_msk, base|cmd, msk, value पूर्ण, comments here*/								\
	अणु0x0008, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT4, 0पूर्ण,/*चयन TSF to 32K*/\
	अणु0x0109, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT7, 0पूर्ण,/*polling TSF stable*/\
	अणु0x0101, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT1, BIT1पूर्ण, /*.	0x101[1] = 1, enable security engine*/\
	अणु0x0100, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, 0xFF, 0xFFपूर्ण, /*.	0x100[7:0] = 0xFF	 enable WMAC TRX*/\
	अणु0x06B7, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, 0xFF, 0x09पूर्ण, /*.	reset MAC rx state machine*/\
	अणु0x06B4, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, 0xFF, 0x86पूर्ण, /*.	reset MAC rx state machine*/\
	अणु0x0080, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT1, BIT1पूर्ण,/* set CPU RAM code पढ़ोy*/	\
	अणु0x001D, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT0, 0पूर्ण,/*Reset CPU IO Wrapper*/	\
	अणु0x0003, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT2, 0पूर्ण,/* Enable CPU*/	\
	अणु0x001D, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT0, BIT0पूर्ण,/*enable CPU IO Wrapper*/	\
	अणु0x0003, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT2, BIT2पूर्ण,/* Enable CPU*/	\
	अणु0x0080, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK, PWR_BASEADDR_MAC, PWR_CMD_POLLING, BIT7, BIT7पूर्ण,/*polling FW init पढ़ोy */	\
	अणु0x0080, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK, PWR_BASEADDR_MAC, PWR_CMD_POLLING, BIT6, BIT6पूर्ण,/*polling FW init पढ़ोy */	\
	अणु0x0002, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT0, BIT0पूर्ण, /*.	0x02[1:0] = 2b'11	 enable BB macro*/\
	अणु0x0522, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, 0xFF, 0पूर्ण, /*.	0x522 = 0*/

#घोषणा RTL8723B_TRANS_END															\
	/* क्रमmat */																\
	/* अणु offset, cut_msk, fab_msk|पूर्णांकerface_msk, base|cmd, msk, value पूर्ण, comments here*/								\
	अणु0xFFFF, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK, 0, PWR_CMD_END, 0, 0पूर्ण, 


बाह्य काष्ठा wlan_pwr_cfg rtl8723B_घातer_on_flow[RTL8723B_TRANS_CARDEMU_TO_ACT_STEPS+RTL8723B_TRANS_END_STEPS];
बाह्य काष्ठा wlan_pwr_cfg rtl8723B_radio_off_flow[RTL8723B_TRANS_ACT_TO_CARDEMU_STEPS+RTL8723B_TRANS_END_STEPS];
बाह्य काष्ठा wlan_pwr_cfg rtl8723B_card_disable_flow[RTL8723B_TRANS_ACT_TO_CARDEMU_STEPS+RTL8723B_TRANS_CARDEMU_TO_PDN_STEPS+RTL8723B_TRANS_END_STEPS];
बाह्य काष्ठा wlan_pwr_cfg rtl8723B_card_enable_flow[RTL8723B_TRANS_ACT_TO_CARDEMU_STEPS+RTL8723B_TRANS_CARDEMU_TO_PDN_STEPS+RTL8723B_TRANS_END_STEPS];
बाह्य काष्ठा wlan_pwr_cfg rtl8723B_suspend_flow[RTL8723B_TRANS_ACT_TO_CARDEMU_STEPS+RTL8723B_TRANS_CARDEMU_TO_SUS_STEPS+RTL8723B_TRANS_END_STEPS];
बाह्य काष्ठा wlan_pwr_cfg rtl8723B_resume_flow[RTL8723B_TRANS_ACT_TO_CARDEMU_STEPS+RTL8723B_TRANS_CARDEMU_TO_SUS_STEPS+RTL8723B_TRANS_END_STEPS];
बाह्य काष्ठा wlan_pwr_cfg rtl8723B_hwpdn_flow[RTL8723B_TRANS_ACT_TO_CARDEMU_STEPS+RTL8723B_TRANS_CARDEMU_TO_PDN_STEPS+RTL8723B_TRANS_END_STEPS];
बाह्य काष्ठा wlan_pwr_cfg rtl8723B_enter_lps_flow[RTL8723B_TRANS_ACT_TO_LPS_STEPS+RTL8723B_TRANS_END_STEPS];
बाह्य काष्ठा wlan_pwr_cfg rtl8723B_leave_lps_flow[RTL8723B_TRANS_LPS_TO_ACT_STEPS+RTL8723B_TRANS_END_STEPS];
बाह्य काष्ठा wlan_pwr_cfg rtl8723B_enter_swlps_flow[RTL8723B_TRANS_ACT_TO_SWLPS_STEPS+RTL8723B_TRANS_END_STEPS];
बाह्य काष्ठा wlan_pwr_cfg rtl8723B_leave_swlps_flow[RTL8723B_TRANS_SWLPS_TO_ACT_STEPS+RTL8723B_TRANS_END_STEPS];
#पूर्ण_अगर
