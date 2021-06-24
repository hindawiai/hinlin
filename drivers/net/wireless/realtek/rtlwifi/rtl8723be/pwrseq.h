<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2009-2014  Realtek Corporation.*/

#अगर_अघोषित __RTL8723BE_PWRSEQ_H__
#घोषणा __RTL8723BE_PWRSEQ_H__

#समावेश "../pwrseqcmd.h"
/**
 *	Check करोcument WM-20130425-JackieLau-RTL8723B_Power_Architecture v05.vsd
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
#घोषणा	RTL8723B_TRANS_CARDEMU_TO_ACT_STEPS	23
#घोषणा	RTL8723B_TRANS_ACT_TO_CARDEMU_STEPS	15
#घोषणा	RTL8723B_TRANS_CARDEMU_TO_SUS_STEPS	15
#घोषणा	RTL8723B_TRANS_SUS_TO_CARDEMU_STEPS	15
#घोषणा	RTL8723B_TRANS_CARDEMU_TO_PDN_STEPS	15
#घोषणा	RTL8723B_TRANS_PDN_TO_CARDEMU_STEPS	15
#घोषणा	RTL8723B_TRANS_ACT_TO_LPS_STEPS		15
#घोषणा	RTL8723B_TRANS_LPS_TO_ACT_STEPS		15
#घोषणा	RTL8723B_TRANS_END_STEPS		1

#घोषणा RTL8723B_TRANS_CARDEMU_TO_ACT					\
	/* क्रमmat */							\
	/* comments here */						\
	/* अणुoffset, cut_msk, fab_msk|पूर्णांकerface_msk, base|cmd, msk, valueपूर्ण, */\
	/*0x20[0] = 1b'1 enable LDOA12 MACRO block क्रम all पूर्णांकerface*/  \
	अणु0x0020, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK,			\
	 PWR_INTF_USB_MSK | PWR_INTF_SDIO_MSK,				\
	 PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT(0), BIT(0)पूर्ण,		\
	/*0x67[0] = 0 to disable BT_GPS_SEL pins*/			\
	अणु0x0067, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK,			\
	 PWR_INTF_USB_MSK | PWR_INTF_SDIO_MSK,				\
	 PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT(4), 0पूर्ण,			\
	/*Delay 1ms*/							\
	अणु0x0001, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK,			\
	 PWR_INTF_USB_MSK | PWR_INTF_SDIO_MSK,				\
	 PWR_BASEADDR_MAC, PWR_CMD_DELAY, 1, PWRSEQ_DELAY_MSपूर्ण,		\
	/*0x00[5] = 1b'0 release analog Ips to digital ,1:isolation*/   \
	अणु0x0000, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK,			\
	 PWR_INTF_USB_MSK | PWR_INTF_SDIO_MSK,				\
	 PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT(5), 0पूर्ण,			\
	/* disable SW LPS 0x04[10]=0 and WLSUS_EN 0x04[11]=0*/		\
	अणु0x0005, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,	\
	 PWR_BASEADDR_MAC, PWR_CMD_WRITE, (BIT(4)|BIT(3)|BIT(2)), 0पूर्ण,	\
	/* Disable USB suspend */					\
	अणु0x0075, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_PCI_MSK,	\
	 PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT(0) , BIT(0)पूर्ण,		\
	/* रुको till 0x04[17] = 1    घातer पढ़ोy*/			\
	अणु0x0006, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,	\
	 PWR_BASEADDR_MAC, PWR_CMD_POLLING, BIT(1), BIT(1)पूर्ण,		\
	/* Enable USB suspend */					\
	अणु0x0075, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_PCI_MSK,	\
	 PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT(0) , 0पूर्ण,			\
	/* release WLON reset  0x04[16]=1*/				\
	अणु0x0006, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,	\
	 PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT(0), BIT(0)पूर्ण,		\
	/* disable HWPDN 0x04[15]=0*/					\
	अणु0x0005, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,	\
	 PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT(7), 0पूर्ण,			\
	/* disable WL suspend*/						\
	अणु0x0005, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,	\
	 PWR_BASEADDR_MAC, PWR_CMD_WRITE, (BIT(4)|BIT(3)), 0पूर्ण,		\
	/* polling until वापस 0*/					\
	अणु0x0005, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,	\
	 PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT(0), BIT(0)पूर्ण,		\
	अणु0x0005, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,	\
	 PWR_BASEADDR_MAC, PWR_CMD_POLLING, BIT(0), 0पूर्ण,			\
	/* Enable WL control XTAL setting*/				\
	अणु0x0010, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,	\
	 PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT(6), BIT(6)पूर्ण,		\
	/*Enable falling edge triggering पूर्णांकerrupt*/			\
	अणु0x0049, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,	\
	 PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT(1), BIT(1)पूर्ण,		\
	/*Enable GPIO9 पूर्णांकerrupt mode*/					\
	अणु0x0063, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,	\
	 PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT(1), BIT(1)पूर्ण,		\
	/*Enable GPIO9 input mode*/					\
	अणु0x0062, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,	\
	 PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT(1), 0पूर्ण,			\
	/*Enable HSISR GPIO[C:0] पूर्णांकerrupt*/				\
	अणु0x0058, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,	\
	 PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT(0), BIT(0)पूर्ण,		\
	/*Enable HSISR GPIO9 पूर्णांकerrupt*/				\
	अणु0x005A, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,	\
	 PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT(1), BIT(1)पूर्ण,		\
	/*For GPIO9 पूर्णांकernal pull high setting by test chip*/		\
	अणु0x0068, PWR_CUT_TESTCHIP_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,\
	 PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT(3), BIT(3)पूर्ण,		\
	/*For GPIO9 पूर्णांकernal pull high setting*/			\
	अणु0x0069, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,	\
	 PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT(6), BIT(6)पूर्ण,

#घोषणा RTL8723B_TRANS_ACT_TO_CARDEMU					\
	/* क्रमmat */							\
	/* comments here */						\
	/* अणु offset, cut_msk, fab_msk|पूर्णांकerface_msk, base|cmd, msk, value पूर्ण, */\
	/*0x1F[7:0] = 0 turn off RF*/					\
	अणु0x001F, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,	\
	 PWR_BASEADDR_MAC, PWR_CMD_WRITE, 0xFF, 0पूर्ण,			\
	/*0x4C[24] = 0x4F[0] = 0, */					\
	/*चयन DPDT_SEL_P output from रेजिस्टर 0x65[2] */		\
	अणु0x004F, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,	\
	 PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT(0), 0पूर्ण,			\
	/*Enable rising edge triggering पूर्णांकerrupt*/			\
	अणु0x0049, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,	\
	 PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT(1), 0पूर्ण,			\
	 /*0x04[9] = 1 turn off MAC by HW state machine*/		\
	अणु0x0005, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,	\
	 PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT(1), BIT(1)पूर्ण,		\
	 /*रुको till 0x04[9] = 0 polling until वापस 0 to disable*/	\
	अणु0x0005, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,	\
	 PWR_BASEADDR_MAC, PWR_CMD_POLLING, BIT(1), 0पूर्ण,			\
	/* Enable BT control XTAL setting*/				\
	अणु0x0010, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,	\
	 PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT(6), 0पूर्ण,			\
	/*0x00[5] = 1b'1 analog Ips to digital ,1:isolation*/		\
	अणु0x0000, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK,			\
	 PWR_INTF_USB_MSK | PWR_INTF_SDIO_MSK, PWR_BASEADDR_MAC,	\
	 PWR_CMD_WRITE, BIT(5), BIT(5)पूर्ण,				\
	/*0x20[0] = 1b'0 disable LDOA12 MACRO block*/			\
	अणु0x0020, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK,			\
	 PWR_INTF_USB_MSK | PWR_INTF_SDIO_MSK, PWR_BASEADDR_MAC,	\
	 PWR_CMD_WRITE, BIT(0), 0पूर्ण,

#घोषणा RTL8723B_TRANS_CARDEMU_TO_SUS					\
	/* क्रमmat */							\
	/* comments here */						\
	/* अणु offset, cut_msk, fab_msk|पूर्णांकerface_msk, base|cmd, msk, value पूर्ण,*/\
	/*0x04[12:11] = 2b'11 enable WL suspend क्रम PCIe*/		\
	अणु0x0005, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_PCI_MSK,	\
	 PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT(4) | BIT(3), (BIT(4) | BIT(3))पूर्ण, \
	/*0x04[12:11] = 2b'01 enable WL suspend*/			\
	अणु0x0005, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK,			\
	 PWR_INTF_USB_MSK | PWR_INTF_SDIO_MSK, PWR_BASEADDR_MAC,	\
	 PWR_CMD_WRITE, BIT(3) | BIT(4), BIT(3)पूर्ण,			\
	/*0x23[4] = 1b'1 12H LDO enter sleep mode*/			\
	अणु0x0023, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK,	\
	 PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT(4), BIT(4)पूर्ण,		\
	/*0x07[7:0] = 0x20 SDIO SOP option to disable BG/MB/ACK/SWR*/   \
	अणु0x0007, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK,	\
	 PWR_BASEADDR_MAC, PWR_CMD_WRITE, 0xFF, 0x20पूर्ण,			\
	/*0x04[12:11] = 2b'11 enable WL suspend क्रम PCIe*/		\
	अणु0x0005, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_PCI_MSK,	\
	 PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT(3) | BIT(4), BIT(3) | BIT(4)पूर्ण,\
	/*Set SDIO suspend local रेजिस्टर*/				\
	अणु0x0086, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK,	\
	 PWR_BASEADDR_SDIO, PWR_CMD_WRITE, BIT(0), BIT(0)पूर्ण,		\
	/*रुको घातer state to suspend*/					\
	अणु0x0086, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK,	\
	 PWR_BASEADDR_SDIO, PWR_CMD_POLLING, BIT(1), 0पूर्ण,

#घोषणा RTL8723B_TRANS_SUS_TO_CARDEMU					\
	/* क्रमmat */							\
	/* comments here */						\
	/* अणु offset, cut_msk, fab_msk|पूर्णांकerface_msk, base|cmd, msk, value पूर्ण, */\
	/*clear suspend enable and घातer करोwn enable*/			\
	अणु0x0005, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,	\
	 PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT(3) | BIT(7), 0पूर्ण,		\
	/*Set SDIO suspend local रेजिस्टर*/				\
	अणु0x0086, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK,	\
	 PWR_BASEADDR_SDIO, PWR_CMD_WRITE, BIT(0), 0पूर्ण,			\
	/*रुको घातer state to suspend*/					\
	अणु0x0086, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK,	\
	 PWR_BASEADDR_SDIO, PWR_CMD_POLLING, BIT(1), BIT(1)पूर्ण,		\
	/*0x23[4] = 1b'0 12H LDO enter normal mode*/			\
	अणु0x0023, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK,	\
	 PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT(4), 0पूर्ण,			\
	/*0x04[12:11] = 2b'00 disable WL suspend*/			\
	अणु0x0005, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,	\
	 PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT(3)|BIT(4), 0पूर्ण,

#घोषणा RTL8723B_TRANS_CARDEMU_TO_CARDDIS				\
	/* क्रमmat */							\
	/* comments here */						\
	/* अणु offset, cut_msk, fab_msk|पूर्णांकerface_msk, base|cmd, msk, value पूर्ण, */\
	/*0x07=0x20 , SOP option to disable BG/MB*/			\
	अणु0x0007, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK,	\
	 PWR_BASEADDR_MAC, PWR_CMD_WRITE, 0xFF, 0x20पूर्ण,			\
	/*0x04[12:11] = 2b'01 enable WL suspend*/			\
	अणु0x0005, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK,			\
	 PWR_INTF_USB_MSK | PWR_INTF_SDIO_MSK,				\
	 PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT(3)|BIT(4), BIT(3)पूर्ण,	\
	/*0x04[10] = 1, enable SW LPS*/					\
	अणु0x0005, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_PCI_MSK,	\
	 PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT(2), BIT(2)पूर्ण,		\
	/*0x48[16] = 1 to enable GPIO9 as EXT WAKEUP*/			\
	अणु0x004A, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_USB_MSK,	\
	 PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT(0), 1पूर्ण,			\
	/*0x23[4] = 1b'1 12H LDO enter sleep mode*/			\
	अणु0x0023, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK,	\
	 PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT(4), BIT(4)पूर्ण,		\
	/*Set SDIO suspend local रेजिस्टर*/				\
	अणु0x0086, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK,	\
	 PWR_BASEADDR_SDIO, PWR_CMD_WRITE, BIT(0), BIT(0)पूर्ण,		\
	/*रुको घातer state to suspend*/					\
	अणु0x0086, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK,	\
	 PWR_BASEADDR_SDIO, PWR_CMD_POLLING, BIT(1), 0पूर्ण,

#घोषणा RTL8723B_TRANS_CARDDIS_TO_CARDEMU				\
	/* क्रमmat */							\
	/* comments here */						\
	/* अणु offset, cut_msk, fab_msk|पूर्णांकerface_msk, base|cmd, msk, value पूर्ण, */\
	/*clear suspend enable and घातer करोwn enable*/			\
	अणु0x0005, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,	\
	 PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT(3) | BIT(7), 0पूर्ण,		\
	/*Set SDIO suspend local रेजिस्टर*/				\
	अणु0x0086, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK,	\
	 PWR_BASEADDR_SDIO, PWR_CMD_WRITE, BIT(0), 0पूर्ण,			\
	/*रुको घातer state to suspend*/					\
	अणु0x0086, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK,	\
	 PWR_BASEADDR_SDIO, PWR_CMD_POLLING, BIT(1), BIT(1)पूर्ण,		\
	/*0x48[16] = 0 to disable GPIO9 as EXT WAKEUP*/			\
	अणु0x004A, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_USB_MSK,	\
	 PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT(0), 0पूर्ण,			\
	/*0x04[12:11] = 2b'00 disable WL suspend*/			\
	अणु0x0005, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,	\
	 PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT(3)|BIT(4), 0पूर्ण,		\
	/*0x23[4] = 1b'0 12H LDO enter normal mode*/			\
	अणु0x0023, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK,	\
	 PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT(4), 0पूर्ण,			\
	/*PCIe DMA start*/						\
	अणु0x0301, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_PCI_MSK,	\
	 PWR_BASEADDR_MAC, PWR_CMD_WRITE, 0xFF, 0पूर्ण,

#घोषणा RTL8723B_TRANS_CARDEMU_TO_PDN					\
	/* क्रमmat */							\
	/* comments here */						\
	/* अणु offset, cut_msk, fab_msk|पूर्णांकerface_msk, base|cmd, msk, value पूर्ण, */\
	/*0x23[4] = 1b'1 12H LDO enter sleep mode*/			\
	अणु0x0023, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK,	\
	 PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT(4), BIT(4)पूर्ण,		\
	/*0x07[7:0] = 0x20 SOP option to disable BG/MB/ACK/SWR*/	\
	अणु0x0007, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK,			\
	 PWR_INTF_SDIO_MSK | PWR_INTF_USB_MSK, PWR_BASEADDR_MAC,	\
	 PWR_CMD_WRITE, 0xFF, 0x20पूर्ण,					\
	/* 0x04[16] = 0*/						\
	अणु0x0006, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,	\
	 PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT(0), 0पूर्ण,			\
	/* 0x04[15] = 1*/						\
	अणु0x0005, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,	\
	 PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT(7), BIT(7)पूर्ण,

#घोषणा RTL8723B_TRANS_PDN_TO_CARDEMU					\
	/* क्रमmat */							\
	/* comments here */						\
	/* अणु offset, cut_msk, fab_msk|पूर्णांकerface_msk, base|cmd, msk, value पूर्ण, */\
	/* 0x04[15] = 0*/						\
	अणु0x0005, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,	\
	 PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT(7), 0पूर्ण,

#घोषणा RTL8723B_TRANS_ACT_TO_LPS					\
	/* क्रमmat */							\
	/* comments here */						\
	/* अणु offset, cut_msk, fab_msk|पूर्णांकerface_msk, base|cmd, msk, value पूर्ण, */\
	/*PCIe DMA stop*/						\
	अणु0x0301, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_PCI_MSK,	\
	 PWR_BASEADDR_MAC, PWR_CMD_WRITE, 0xFF, 0xFFपूर्ण,			\
	/*Tx Pause*/							\
	अणु0x0522, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,	\
	 PWR_BASEADDR_MAC, PWR_CMD_WRITE, 0xFF, 0xFFपूर्ण,			\
	/*Should be zero अगर no packet is transmitting*/			\
	अणु0x05F8, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,	\
	 PWR_BASEADDR_MAC, PWR_CMD_POLLING, 0xFF, 0पूर्ण,			\
	/*Should be zero अगर no packet is transmitting*/			\
	अणु0x05F9, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,	\
	 PWR_BASEADDR_MAC, PWR_CMD_POLLING, 0xFF, 0पूर्ण,			\
	/*Should be zero अगर no packet is transmitting*/			\
	अणु0x05FA, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,	\
	 PWR_BASEADDR_MAC, PWR_CMD_POLLING, 0xFF, 0पूर्ण,			\
	/*Should be zero अगर no packet is transmitting*/			\
	अणु0x05FB, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,	\
	 PWR_BASEADDR_MAC, PWR_CMD_POLLING, 0xFF, 0पूर्ण,			\
	/*CCK and OFDM are disabled,and घड़ी are gated*/		\
	अणु0x0002, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,	\
	 PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT(0), 0पूर्ण,			\
	/*Delay 1us*/							\
	अणु0x0002, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,	\
	 PWR_BASEADDR_MAC, PWR_CMD_DELAY, 0, PWRSEQ_DELAY_USपूर्ण,		\
	/*Whole BB is reset*/						\
	अणु0x0002, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,	\
	 PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT(1), 0पूर्ण,			\
	/*Reset MAC TRX*/						\
	अणु0x0100, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,	\
	 PWR_BASEADDR_MAC, PWR_CMD_WRITE, 0xFF, 0x03पूर्ण,			\
	/*check अगर हटाओd later*/					\
	अणु0x0101, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,	\
	 PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT(1), 0पूर्ण,			\
	/*When driver enter Sus/ Disable, enable LOP क्रम BT*/		\
	अणु0x0093, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK,	\
	 PWR_BASEADDR_MAC, PWR_CMD_WRITE, 0xFF, 0x00पूर्ण,			\
	/*Respond TxOK to scheduler*/					\
	अणु0x0553, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,	\
	 PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT(5), BIT(5)पूर्ण,

#घोषणा RTL8723B_TRANS_LPS_TO_ACT					\
	/* क्रमmat */							\
	/* comments here */						\
	/* अणु offset, cut_msk, fab_msk|पूर्णांकerface_msk, base|cmd, msk, value पूर्ण, */\
	/*SDIO RPWM*/							\
	अणु0x0080, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK,	\
	 PWR_BASEADDR_SDIO, PWR_CMD_WRITE, 0xFF, 0x84पूर्ण,			\
	/*USB RPWM*/							\
	अणु0xFE58, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_USB_MSK,	\
	 PWR_BASEADDR_MAC, PWR_CMD_WRITE, 0xFF, 0x84पूर्ण,			\
	/*PCIe RPWM*/							\
	अणु0x0361, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_PCI_MSK,	\
	 PWR_BASEADDR_MAC, PWR_CMD_WRITE, 0xFF, 0x84पूर्ण,			\
	/*Delay*/							\
	अणु0x0002, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,	\
	 PWR_BASEADDR_MAC, PWR_CMD_DELAY, 0, PWRSEQ_DELAY_MSपूर्ण,		\
	/*.	0x08[4] = 0		 चयन TSF to 40M*/		\
	अणु0x0008, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,	\
	 PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT(4), 0पूर्ण,			\
	/*Polling 0x109[7]=0  TSF in 40M*/				\
	अणु0x0109, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,	\
	 PWR_BASEADDR_MAC, PWR_CMD_POLLING, BIT(7), 0पूर्ण,			\
	/*.	0x29[7:6] = 2b'00	 enable BB घड़ी*/		\
	अणु0x0029, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,	\
	 PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT(6)|BIT(7), 0पूर्ण,		\
	/*.	0x101[1] = 1*/						\
	अणु0x0101, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,	\
	 PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT(1), BIT(1)पूर्ण,		\
	/*.	0x100[7:0] = 0xFF	 enable WMAC TRX*/		\
	अणु0x0100, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,	\
	 PWR_BASEADDR_MAC, PWR_CMD_WRITE, 0xFF, 0xFFपूर्ण,			\
	/*.	0x02[1:0] = 2b'11	 enable BB macro*/		\
	अणु0x0002, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,	\
	 PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT(1) | BIT(0), BIT(1) | BIT(0)पूर्ण, \
	/*.	0x522 = 0*/						\
	अणु0x0522, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,	\
	 PWR_BASEADDR_MAC, PWR_CMD_WRITE, 0xFF, 0पूर्ण,

#घोषणा RTL8723B_TRANS_END						\
	/* क्रमmat */							\
	/* comments here */						\
	/* अणु offset, cut_msk, fab_msk|पूर्णांकerface_msk, base|cmd, msk, value पूर्ण, */\
	अणु0xFFFF, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK, 0,	\
	 PWR_CMD_END, 0, 0पूर्ण,

बाह्य काष्ठा wlan_pwr_cfg rtl8723B_घातer_on_flow
				[RTL8723B_TRANS_CARDEMU_TO_ACT_STEPS +
				 RTL8723B_TRANS_END_STEPS];
बाह्य काष्ठा wlan_pwr_cfg rtl8723B_radio_off_flow
				[RTL8723B_TRANS_ACT_TO_CARDEMU_STEPS +
				 RTL8723B_TRANS_END_STEPS];
बाह्य काष्ठा wlan_pwr_cfg rtl8723B_card_disable_flow
				[RTL8723B_TRANS_ACT_TO_CARDEMU_STEPS +
				 RTL8723B_TRANS_CARDEMU_TO_PDN_STEPS +
				 RTL8723B_TRANS_END_STEPS];
बाह्य काष्ठा wlan_pwr_cfg rtl8723B_card_enable_flow
				[RTL8723B_TRANS_ACT_TO_CARDEMU_STEPS +
				 RTL8723B_TRANS_CARDEMU_TO_PDN_STEPS +
				 RTL8723B_TRANS_END_STEPS];
बाह्य काष्ठा wlan_pwr_cfg rtl8723B_suspend_flow
				[RTL8723B_TRANS_ACT_TO_CARDEMU_STEPS +
				 RTL8723B_TRANS_CARDEMU_TO_SUS_STEPS +
				 RTL8723B_TRANS_END_STEPS];
बाह्य काष्ठा wlan_pwr_cfg rtl8723B_resume_flow
				[RTL8723B_TRANS_ACT_TO_CARDEMU_STEPS +
				 RTL8723B_TRANS_CARDEMU_TO_SUS_STEPS +
				 RTL8723B_TRANS_END_STEPS];
बाह्य काष्ठा wlan_pwr_cfg rtl8723B_hwpdn_flow
				[RTL8723B_TRANS_ACT_TO_CARDEMU_STEPS +
				 RTL8723B_TRANS_CARDEMU_TO_PDN_STEPS +
				 RTL8723B_TRANS_END_STEPS];
बाह्य काष्ठा wlan_pwr_cfg rtl8723B_enter_lps_flow
				[RTL8723B_TRANS_ACT_TO_LPS_STEPS +
				 RTL8723B_TRANS_END_STEPS];
बाह्य काष्ठा wlan_pwr_cfg rtl8723B_leave_lps_flow
				[RTL8723B_TRANS_LPS_TO_ACT_STEPS +
				 RTL8723B_TRANS_END_STEPS];

/* RTL8723 Power Configuration CMDs क्रम PCIe पूर्णांकerface */
#घोषणा RTL8723_NIC_PWR_ON_FLOW		rtl8723B_घातer_on_flow
#घोषणा RTL8723_NIC_RF_OFF_FLOW		rtl8723B_radio_off_flow
#घोषणा RTL8723_NIC_DISABLE_FLOW	rtl8723B_card_disable_flow
#घोषणा RTL8723_NIC_ENABLE_FLOW		rtl8723B_card_enable_flow
#घोषणा RTL8723_NIC_SUSPEND_FLOW	rtl8723B_suspend_flow
#घोषणा RTL8723_NIC_RESUME_FLOW		rtl8723B_resume_flow
#घोषणा RTL8723_NIC_PDN_FLOW		rtl8723B_hwpdn_flow
#घोषणा RTL8723_NIC_LPS_ENTER_FLOW	rtl8723B_enter_lps_flow
#घोषणा RTL8723_NIC_LPS_LEAVE_FLOW	rtl8723B_leave_lps_flow

#पूर्ण_अगर
