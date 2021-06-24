<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Copyright (C) 2011 Marvell International Ltd. All rights reserved.
 */

#अगर_अघोषित	__MV_USB_OTG_CONTROLLER__
#घोषणा	__MV_USB_OTG_CONTROLLER__

#समावेश <linux/types.h>

/* Command Register Bit Masks */
#घोषणा USBCMD_RUN_STOP			(0x00000001)
#घोषणा USBCMD_CTRL_RESET		(0x00000002)

/* otgsc Register Bit Masks */
#घोषणा OTGSC_CTRL_VUSB_DISCHARGE		0x00000001
#घोषणा OTGSC_CTRL_VUSB_CHARGE			0x00000002
#घोषणा OTGSC_CTRL_OTG_TERM			0x00000008
#घोषणा OTGSC_CTRL_DATA_PULSING			0x00000010
#घोषणा OTGSC_STS_USB_ID			0x00000100
#घोषणा OTGSC_STS_A_VBUS_VALID			0x00000200
#घोषणा OTGSC_STS_A_SESSION_VALID		0x00000400
#घोषणा OTGSC_STS_B_SESSION_VALID		0x00000800
#घोषणा OTGSC_STS_B_SESSION_END			0x00001000
#घोषणा OTGSC_STS_1MS_TOGGLE			0x00002000
#घोषणा OTGSC_STS_DATA_PULSING			0x00004000
#घोषणा OTGSC_INTSTS_USB_ID			0x00010000
#घोषणा OTGSC_INTSTS_A_VBUS_VALID		0x00020000
#घोषणा OTGSC_INTSTS_A_SESSION_VALID		0x00040000
#घोषणा OTGSC_INTSTS_B_SESSION_VALID		0x00080000
#घोषणा OTGSC_INTSTS_B_SESSION_END		0x00100000
#घोषणा OTGSC_INTSTS_1MS			0x00200000
#घोषणा OTGSC_INTSTS_DATA_PULSING		0x00400000
#घोषणा OTGSC_INTR_USB_ID			0x01000000
#घोषणा OTGSC_INTR_A_VBUS_VALID			0x02000000
#घोषणा OTGSC_INTR_A_SESSION_VALID		0x04000000
#घोषणा OTGSC_INTR_B_SESSION_VALID		0x08000000
#घोषणा OTGSC_INTR_B_SESSION_END		0x10000000
#घोषणा OTGSC_INTR_1MS_TIMER			0x20000000
#घोषणा OTGSC_INTR_DATA_PULSING			0x40000000

#घोषणा CAPLENGTH_MASK		(0xff)

/* Timer's पूर्णांकerval, unit 10ms */
#घोषणा T_A_WAIT_VRISE		100
#घोषणा T_A_WAIT_BCON		2000
#घोषणा T_A_AIDL_BDIS		100
#घोषणा T_A_BIDL_ADIS		20
#घोषणा T_B_ASE0_BRST		400
#घोषणा T_B_SE0_SRP		300
#घोषणा T_B_SRP_FAIL		2000
#घोषणा T_B_DATA_PLS		10
#घोषणा T_B_SRP_INIT		100
#घोषणा T_A_SRP_RSPNS		10
#घोषणा T_A_DRV_RSM		5

क्रमागत otg_function अणु
	OTG_B_DEVICE = 0,
	OTG_A_DEVICE
पूर्ण;

क्रमागत mv_otg_समयr अणु
	A_WAIT_BCON_TIMER = 0,
	OTG_TIMER_NUM
पूर्ण;

/* PXA OTG state machine */
काष्ठा mv_otg_ctrl अणु
	/* पूर्णांकernal variables */
	u8 a_set_b_hnp_en;	/* A-Device set b_hnp_en */
	u8 b_srp_करोne;
	u8 b_hnp_en;

	/* OTG inमाला_दो */
	u8 a_bus_drop;
	u8 a_bus_req;
	u8 a_clr_err;
	u8 a_bus_resume;
	u8 a_bus_suspend;
	u8 a_conn;
	u8 a_sess_vld;
	u8 a_srp_det;
	u8 a_vbus_vld;
	u8 b_bus_req;		/* B-Device Require Bus */
	u8 b_bus_resume;
	u8 b_bus_suspend;
	u8 b_conn;
	u8 b_se0_srp;
	u8 b_sess_end;
	u8 b_sess_vld;
	u8 id;
	u8 a_suspend_req;

	/*Timer event */
	u8 a_aidl_bdis_समयout;
	u8 b_ase0_brst_समयout;
	u8 a_bidl_adis_समयout;
	u8 a_रुको_bcon_समयout;

	काष्ठा समयr_list समयr[OTG_TIMER_NUM];
पूर्ण;

#घोषणा VUSBHS_MAX_PORTS	8

काष्ठा mv_otg_regs अणु
	u32 usbcmd;		/* Command रेजिस्टर */
	u32 usbsts;		/* Status रेजिस्टर */
	u32 usbपूर्णांकr;		/* Interrupt enable */
	u32 frindex;		/* Frame index */
	u32 reserved1[1];
	u32 deviceaddr;		/* Device Address */
	u32 eplistaddr;		/* Endpoपूर्णांक List Address */
	u32 ttctrl;		/* HOST TT status and control */
	u32 burstsize;		/* Programmable Burst Size */
	u32 txfilltuning;	/* Host Transmit Pre-Buffer Packet Tuning */
	u32 reserved[4];
	u32 epnak;		/* Endpoपूर्णांक NAK */
	u32 epnaken;		/* Endpoपूर्णांक NAK Enable */
	u32 configflag;		/* Configured Flag रेजिस्टर */
	u32 portsc[VUSBHS_MAX_PORTS];	/* Port Status/Control x, x = 1..8 */
	u32 otgsc;
	u32 usbmode;		/* USB Host/Device mode */
	u32 epsetupstat;	/* Endpoपूर्णांक Setup Status */
	u32 epprime;		/* Endpoपूर्णांक Initialize */
	u32 epflush;		/* Endpoपूर्णांक De-initialize */
	u32 epstatus;		/* Endpoपूर्णांक Status */
	u32 epcomplete;		/* Endpoपूर्णांक Interrupt On Complete */
	u32 epctrlx[16];	/* Endpoपूर्णांक Control, where x = 0.. 15 */
	u32 mcr;		/* Mux Control */
	u32 isr;		/* Interrupt Status */
	u32 ier;		/* Interrupt Enable */
पूर्ण;

काष्ठा mv_otg अणु
	काष्ठा usb_phy phy;
	काष्ठा mv_otg_ctrl otg_ctrl;

	/* base address */
	व्योम __iomem *phy_regs;
	व्योम __iomem *cap_regs;
	काष्ठा mv_otg_regs __iomem *op_regs;

	काष्ठा platक्रमm_device *pdev;
	पूर्णांक irq;
	u32 irq_status;
	u32 irq_en;

	काष्ठा delayed_work work;
	काष्ठा workqueue_काष्ठा *qwork;

	spinlock_t wq_lock;

	काष्ठा mv_usb_platक्रमm_data *pdata;

	अचिन्हित पूर्णांक active;
	अचिन्हित पूर्णांक घड़ी_gating;
	काष्ठा clk *clk;
पूर्ण;

#पूर्ण_अगर
