<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/* Copyright (C) 2007,2008 Freescale Semiconductor, Inc. */

#समावेश <linux/usb/otg-fsm.h>
#समावेश <linux/usb/otg.h>
#समावेश <linux/ioctl.h>

/* USB Command Register Bit Masks */
#घोषणा USB_CMD_RUN_STOP		(0x1<<0)
#घोषणा USB_CMD_CTRL_RESET		(0x1<<1)
#घोषणा USB_CMD_PERIODIC_SCHEDULE_EN	(0x1<<4)
#घोषणा USB_CMD_ASYNC_SCHEDULE_EN	(0x1<<5)
#घोषणा USB_CMD_INT_AA_DOORBELL		(0x1<<6)
#घोषणा USB_CMD_ASP			(0x3<<8)
#घोषणा USB_CMD_ASYNC_SCH_PARK_EN	(0x1<<11)
#घोषणा USB_CMD_SUTW			(0x1<<13)
#घोषणा USB_CMD_ATDTW			(0x1<<14)
#घोषणा USB_CMD_ITC			(0xFF<<16)

/* bit 15,3,2 are frame list size */
#घोषणा USB_CMD_FRAME_SIZE_1024		(0x0<<15 | 0x0<<2)
#घोषणा USB_CMD_FRAME_SIZE_512		(0x0<<15 | 0x1<<2)
#घोषणा USB_CMD_FRAME_SIZE_256		(0x0<<15 | 0x2<<2)
#घोषणा USB_CMD_FRAME_SIZE_128		(0x0<<15 | 0x3<<2)
#घोषणा USB_CMD_FRAME_SIZE_64		(0x1<<15 | 0x0<<2)
#घोषणा USB_CMD_FRAME_SIZE_32		(0x1<<15 | 0x1<<2)
#घोषणा USB_CMD_FRAME_SIZE_16		(0x1<<15 | 0x2<<2)
#घोषणा USB_CMD_FRAME_SIZE_8		(0x1<<15 | 0x3<<2)

/* bit 9-8 are async schedule park mode count */
#घोषणा USB_CMD_ASP_00			(0x0<<8)
#घोषणा USB_CMD_ASP_01			(0x1<<8)
#घोषणा USB_CMD_ASP_10			(0x2<<8)
#घोषणा USB_CMD_ASP_11			(0x3<<8)
#घोषणा USB_CMD_ASP_BIT_POS		(8)

/* bit 23-16 are पूर्णांकerrupt threshold control */
#घोषणा USB_CMD_ITC_NO_THRESHOLD	(0x00<<16)
#घोषणा USB_CMD_ITC_1_MICRO_FRM		(0x01<<16)
#घोषणा USB_CMD_ITC_2_MICRO_FRM		(0x02<<16)
#घोषणा USB_CMD_ITC_4_MICRO_FRM		(0x04<<16)
#घोषणा USB_CMD_ITC_8_MICRO_FRM		(0x08<<16)
#घोषणा USB_CMD_ITC_16_MICRO_FRM	(0x10<<16)
#घोषणा USB_CMD_ITC_32_MICRO_FRM	(0x20<<16)
#घोषणा USB_CMD_ITC_64_MICRO_FRM	(0x40<<16)
#घोषणा USB_CMD_ITC_BIT_POS		(16)

/* USB Status Register Bit Masks */
#घोषणा USB_STS_INT			(0x1<<0)
#घोषणा USB_STS_ERR			(0x1<<1)
#घोषणा USB_STS_PORT_CHANGE		(0x1<<2)
#घोषणा USB_STS_FRM_LST_ROLL		(0x1<<3)
#घोषणा USB_STS_SYS_ERR			(0x1<<4)
#घोषणा USB_STS_IAA			(0x1<<5)
#घोषणा USB_STS_RESET_RECEIVED		(0x1<<6)
#घोषणा USB_STS_SOF			(0x1<<7)
#घोषणा USB_STS_DCSUSPEND		(0x1<<8)
#घोषणा USB_STS_HC_HALTED		(0x1<<12)
#घोषणा USB_STS_RCL			(0x1<<13)
#घोषणा USB_STS_PERIODIC_SCHEDULE	(0x1<<14)
#घोषणा USB_STS_ASYNC_SCHEDULE		(0x1<<15)

/* USB Interrupt Enable Register Bit Masks */
#घोषणा USB_INTR_INT_EN			(0x1<<0)
#घोषणा USB_INTR_ERR_INT_EN		(0x1<<1)
#घोषणा USB_INTR_PC_DETECT_EN		(0x1<<2)
#घोषणा USB_INTR_FRM_LST_ROLL_EN	(0x1<<3)
#घोषणा USB_INTR_SYS_ERR_EN		(0x1<<4)
#घोषणा USB_INTR_ASYN_ADV_EN		(0x1<<5)
#घोषणा USB_INTR_RESET_EN		(0x1<<6)
#घोषणा USB_INTR_SOF_EN			(0x1<<7)
#घोषणा USB_INTR_DEVICE_SUSPEND		(0x1<<8)

/* Device Address bit masks */
#घोषणा USB_DEVICE_ADDRESS_MASK		(0x7F<<25)
#घोषणा USB_DEVICE_ADDRESS_BIT_POS	(25)
/* PORTSC  Register Bit Masks,Only one PORT in OTG mode*/
#घोषणा PORTSC_CURRENT_CONNECT_STATUS	(0x1<<0)
#घोषणा PORTSC_CONNECT_STATUS_CHANGE	(0x1<<1)
#घोषणा PORTSC_PORT_ENABLE		(0x1<<2)
#घोषणा PORTSC_PORT_EN_DIS_CHANGE	(0x1<<3)
#घोषणा PORTSC_OVER_CURRENT_ACT		(0x1<<4)
#घोषणा PORTSC_OVER_CUURENT_CHG		(0x1<<5)
#घोषणा PORTSC_PORT_FORCE_RESUME	(0x1<<6)
#घोषणा PORTSC_PORT_SUSPEND		(0x1<<7)
#घोषणा PORTSC_PORT_RESET		(0x1<<8)
#घोषणा PORTSC_LINE_STATUS_BITS		(0x3<<10)
#घोषणा PORTSC_PORT_POWER		(0x1<<12)
#घोषणा PORTSC_PORT_INDICTOR_CTRL	(0x3<<14)
#घोषणा PORTSC_PORT_TEST_CTRL		(0xF<<16)
#घोषणा PORTSC_WAKE_ON_CONNECT_EN	(0x1<<20)
#घोषणा PORTSC_WAKE_ON_CONNECT_DIS	(0x1<<21)
#घोषणा PORTSC_WAKE_ON_OVER_CURRENT	(0x1<<22)
#घोषणा PORTSC_PHY_LOW_POWER_SPD	(0x1<<23)
#घोषणा PORTSC_PORT_FORCE_FULL_SPEED	(0x1<<24)
#घोषणा PORTSC_PORT_SPEED_MASK		(0x3<<26)
#घोषणा PORTSC_TRANSCEIVER_WIDTH	(0x1<<28)
#घोषणा PORTSC_PHY_TYPE_SEL		(0x3<<30)
/* bit 11-10 are line status */
#घोषणा PORTSC_LINE_STATUS_SE0		(0x0<<10)
#घोषणा PORTSC_LINE_STATUS_JSTATE	(0x1<<10)
#घोषणा PORTSC_LINE_STATUS_KSTATE	(0x2<<10)
#घोषणा PORTSC_LINE_STATUS_UNDEF	(0x3<<10)
#घोषणा PORTSC_LINE_STATUS_BIT_POS	(10)

/* bit 15-14 are port indicator control */
#घोषणा PORTSC_PIC_OFF			(0x0<<14)
#घोषणा PORTSC_PIC_AMBER		(0x1<<14)
#घोषणा PORTSC_PIC_GREEN		(0x2<<14)
#घोषणा PORTSC_PIC_UNDEF		(0x3<<14)
#घोषणा PORTSC_PIC_BIT_POS		(14)

/* bit 19-16 are port test control */
#घोषणा PORTSC_PTC_DISABLE		(0x0<<16)
#घोषणा PORTSC_PTC_JSTATE		(0x1<<16)
#घोषणा PORTSC_PTC_KSTATE		(0x2<<16)
#घोषणा PORTSC_PTC_SEQNAK		(0x3<<16)
#घोषणा PORTSC_PTC_PACKET		(0x4<<16)
#घोषणा PORTSC_PTC_FORCE_EN		(0x5<<16)
#घोषणा PORTSC_PTC_BIT_POS		(16)

/* bit 27-26 are port speed */
#घोषणा PORTSC_PORT_SPEED_FULL		(0x0<<26)
#घोषणा PORTSC_PORT_SPEED_LOW		(0x1<<26)
#घोषणा PORTSC_PORT_SPEED_HIGH		(0x2<<26)
#घोषणा PORTSC_PORT_SPEED_UNDEF		(0x3<<26)
#घोषणा PORTSC_SPEED_BIT_POS		(26)

/* bit 28 is parallel transceiver width क्रम UTMI पूर्णांकerface */
#घोषणा PORTSC_PTW			(0x1<<28)
#घोषणा PORTSC_PTW_8BIT			(0x0<<28)
#घोषणा PORTSC_PTW_16BIT		(0x1<<28)

/* bit 31-30 are port transceiver select */
#घोषणा PORTSC_PTS_UTMI			(0x0<<30)
#घोषणा PORTSC_PTS_ULPI			(0x2<<30)
#घोषणा PORTSC_PTS_FSLS_SERIAL		(0x3<<30)
#घोषणा PORTSC_PTS_BIT_POS		(30)

#घोषणा PORTSC_W1C_BITS			\
	(PORTSC_CONNECT_STATUS_CHANGE |	\
	 PORTSC_PORT_EN_DIS_CHANGE    |	\
	 PORTSC_OVER_CUURENT_CHG)

/* OTG Status Control Register Bit Masks */
#घोषणा OTGSC_CTRL_VBUS_DISCHARGE	(0x1<<0)
#घोषणा OTGSC_CTRL_VBUS_CHARGE		(0x1<<1)
#घोषणा OTGSC_CTRL_OTG_TERMINATION	(0x1<<3)
#घोषणा OTGSC_CTRL_DATA_PULSING		(0x1<<4)
#घोषणा OTGSC_CTRL_ID_PULL_EN		(0x1<<5)
#घोषणा OTGSC_HA_DATA_PULSE		(0x1<<6)
#घोषणा OTGSC_HA_BA			(0x1<<7)
#घोषणा OTGSC_STS_USB_ID		(0x1<<8)
#घोषणा OTGSC_STS_A_VBUS_VALID		(0x1<<9)
#घोषणा OTGSC_STS_A_SESSION_VALID	(0x1<<10)
#घोषणा OTGSC_STS_B_SESSION_VALID	(0x1<<11)
#घोषणा OTGSC_STS_B_SESSION_END		(0x1<<12)
#घोषणा OTGSC_STS_1MS_TOGGLE		(0x1<<13)
#घोषणा OTGSC_STS_DATA_PULSING		(0x1<<14)
#घोषणा OTGSC_INTSTS_USB_ID		(0x1<<16)
#घोषणा OTGSC_INTSTS_A_VBUS_VALID	(0x1<<17)
#घोषणा OTGSC_INTSTS_A_SESSION_VALID	(0x1<<18)
#घोषणा OTGSC_INTSTS_B_SESSION_VALID	(0x1<<19)
#घोषणा OTGSC_INTSTS_B_SESSION_END	(0x1<<20)
#घोषणा OTGSC_INTSTS_1MS		(0x1<<21)
#घोषणा OTGSC_INTSTS_DATA_PULSING	(0x1<<22)
#घोषणा OTGSC_INTR_USB_ID_EN		(0x1<<24)
#घोषणा OTGSC_INTR_A_VBUS_VALID_EN	(0x1<<25)
#घोषणा OTGSC_INTR_A_SESSION_VALID_EN	(0x1<<26)
#घोषणा OTGSC_INTR_B_SESSION_VALID_EN	(0x1<<27)
#घोषणा OTGSC_INTR_B_SESSION_END_EN	(0x1<<28)
#घोषणा OTGSC_INTR_1MS_TIMER_EN		(0x1<<29)
#घोषणा OTGSC_INTR_DATA_PULSING_EN	(0x1<<30)
#घोषणा OTGSC_INTSTS_MASK		(0x00ff0000)

/* USB MODE Register Bit Masks */
#घोषणा  USB_MODE_CTRL_MODE_IDLE	(0x0<<0)
#घोषणा  USB_MODE_CTRL_MODE_DEVICE	(0x2<<0)
#घोषणा  USB_MODE_CTRL_MODE_HOST	(0x3<<0)
#घोषणा  USB_MODE_CTRL_MODE_RSV		(0x1<<0)
#घोषणा  USB_MODE_SETUP_LOCK_OFF	(0x1<<3)
#घोषणा  USB_MODE_STREAM_DISABLE	(0x1<<4)
#घोषणा  USB_MODE_ES			(0x1<<2) /* Endian Select */

/* control Register Bit Masks */
#घोषणा  USB_CTRL_IOENB			(0x1<<2)
#घोषणा  USB_CTRL_ULPI_INT0EN		(0x1<<0)

/* BCSR5 */
#घोषणा BCSR5_INT_USB			(0x02)

/* USB module clk cfg */
#घोषणा SCCR_OFFS			(0xA08)
#घोषणा SCCR_USB_CLK_DISABLE		(0x00000000)	/* USB clk disable */
#घोषणा SCCR_USB_MPHCM_11		(0x00c00000)
#घोषणा SCCR_USB_MPHCM_01		(0x00400000)
#घोषणा SCCR_USB_MPHCM_10		(0x00800000)
#घोषणा SCCR_USB_DRCM_11		(0x00300000)
#घोषणा SCCR_USB_DRCM_01		(0x00100000)
#घोषणा SCCR_USB_DRCM_10		(0x00200000)

#घोषणा SICRL_OFFS			(0x114)
#घोषणा SICRL_USB0			(0x40000000)
#घोषणा SICRL_USB1			(0x20000000)

#घोषणा SICRH_OFFS			(0x118)
#घोषणा SICRH_USB_UTMI			(0x00020000)

/* OTG पूर्णांकerrupt enable bit masks */
#घोषणा  OTGSC_INTERRUPT_ENABLE_BITS_MASK  \
	(OTGSC_INTR_USB_ID_EN            | \
	OTGSC_INTR_1MS_TIMER_EN		 | \
	OTGSC_INTR_A_VBUS_VALID_EN       | \
	OTGSC_INTR_A_SESSION_VALID_EN    | \
	OTGSC_INTR_B_SESSION_VALID_EN    | \
	OTGSC_INTR_B_SESSION_END_EN      | \
	OTGSC_INTR_DATA_PULSING_EN)

/* OTG पूर्णांकerrupt status bit masks */
#घोषणा  OTGSC_INTERRUPT_STATUS_BITS_MASK  \
	(OTGSC_INTSTS_USB_ID          |    \
	OTGSC_INTR_1MS_TIMER_EN       |    \
	OTGSC_INTSTS_A_VBUS_VALID     |    \
	OTGSC_INTSTS_A_SESSION_VALID  |    \
	OTGSC_INTSTS_B_SESSION_VALID  |    \
	OTGSC_INTSTS_B_SESSION_END    |    \
	OTGSC_INTSTS_DATA_PULSING)

/*
 *  A-DEVICE timing  स्थिरants
 */

/* Wait क्रम VBUS Rise  */
#घोषणा TA_WAIT_VRISE	(100)	/* a_रुको_vrise 100 ms, section: 6.6.5.1 */

/* Wait क्रम B-Connect */
#घोषणा TA_WAIT_BCON	(10000)  /* a_रुको_bcon > 1 sec, section: 6.6.5.2
				  * This is only used to get out of
				  * OTG_STATE_A_WAIT_BCON state अगर there was
				  * no connection क्रम these many milliseconds
				  */

/* A-Idle to B-Disconnect */
/* It is necessary क्रम this समयr to be more than 750 ms because of a bug in OPT
 * test 5.4 in which B OPT disconnects after 750 ms instead of 75ms as stated
 * in the test description
 */
#घोषणा TA_AIDL_BDIS	(5000)	/* a_suspend minimum 200 ms, section: 6.6.5.3 */

/* B-Idle to A-Disconnect */
#घोषणा TA_BIDL_ADIS	(12)	/* 3 to 200 ms */

/* B-device timing स्थिरants */


/* Data-Line Pulse Time*/
#घोषणा TB_DATA_PLS	(10)	/* b_srp_init,जारी 5~10ms, section:5.3.3 */
#घोषणा TB_DATA_PLS_MIN	(5)	/* minimum 5 ms */
#घोषणा TB_DATA_PLS_MAX	(10)	/* maximum 10 ms */

/* SRP Initiate Time  */
#घोषणा TB_SRP_INIT	(100)	/* b_srp_init,maximum 100 ms, section:5.3.8 */

/* SRP Fail Time  */
#घोषणा TB_SRP_FAIL	(7000)	/* b_srp_init,Fail समय 5~30s, section:6.8.2.2*/

/* SRP result रुको समय */
#घोषणा TB_SRP_WAIT	(60)

/* VBus समय */
#घोषणा TB_VBUS_PLS	(30)	/* समय to keep vbus pulsing निश्चितed */

/* Disअक्षरge समय */
/* This समय should be less than 10ms. It varies from प्रणाली to प्रणाली. */
#घोषणा TB_VBUS_DSCHRG	(8)

/* A-SE0 to B-Reset  */
#घोषणा TB_ASE0_BRST	(20)	/* b_रुको_acon, mini 3.125 ms,section:6.8.2.4 */

/* A bus suspend समयr beक्रमe we can चयन to b_रुको_aconn */
#घोषणा TB_A_SUSPEND	(7)
#घोषणा TB_BUS_RESUME	(12)

/* SE0 Time Beक्रमe SRP */
#घोषणा TB_SE0_SRP	(2)	/* b_idle,minimum 2 ms, section:5.3.2 */

#घोषणा SET_OTG_STATE(phy, newstate)	((phy)->otg->state = newstate)

काष्ठा usb_dr_mmap अणु
	/* Capability रेजिस्टर */
	u8 res1[256];
	u16 caplength;		/* Capability Register Length */
	u16 hciversion;		/* Host Controller Interface Version */
	u32 hcsparams;		/* Host Controller Structual Parameters */
	u32 hccparams;		/* Host Controller Capability Parameters */
	u8 res2[20];
	u32 dciversion;		/* Device Controller Interface Version */
	u32 dccparams;		/* Device Controller Capability Parameters */
	u8 res3[24];
	/* Operation रेजिस्टर */
	u32 usbcmd;		/* USB Command Register */
	u32 usbsts;		/* USB Status Register */
	u32 usbपूर्णांकr;		/* USB Interrupt Enable Register */
	u32 frindex;		/* Frame Index Register */
	u8 res4[4];
	u32 deviceaddr;		/* Device Address */
	u32 endpoपूर्णांकlistaddr;	/* Endpoपूर्णांक List Address Register */
	u8 res5[4];
	u32 burstsize;		/* Master Interface Data Burst Size Register */
	u32 txttfilltuning;	/* Transmit FIFO Tuning Controls Register */
	u8 res6[8];
	u32 ulpiview;		/* ULPI रेजिस्टर access */
	u8 res7[12];
	u32 configflag;		/* Configure Flag Register */
	u32 portsc;		/* Port 1 Status and Control Register */
	u8 res8[28];
	u32 otgsc;		/* On-The-Go Status and Control */
	u32 usbmode;		/* USB Mode Register */
	u32 endptsetupstat;	/* Endpoपूर्णांक Setup Status Register */
	u32 endpoपूर्णांकprime;	/* Endpoपूर्णांक Initialization Register */
	u32 endptflush;		/* Endpoपूर्णांक Flush Register */
	u32 endptstatus;	/* Endpoपूर्णांक Status Register */
	u32 endptcomplete;	/* Endpoपूर्णांक Complete Register */
	u32 endptctrl[6];	/* Endpoपूर्णांक Control Registers */
	u8 res9[552];
	u32 snoop1;
	u32 snoop2;
	u32 age_cnt_thresh;	/* Age Count Threshold Register */
	u32 pri_ctrl;		/* Priority Control Register */
	u32 si_ctrl;		/* System Interface Control Register */
	u8 res10[236];
	u32 control;		/* General Purpose Control Register */
पूर्ण;

काष्ठा fsl_otg_समयr अणु
	अचिन्हित दीर्घ expires;	/* Number of count increase to समयout */
	अचिन्हित दीर्घ count;	/* Tick counter */
	व्योम (*function)(अचिन्हित दीर्घ);	/* Timeout function */
	अचिन्हित दीर्घ data;	/* Data passed to function */
	काष्ठा list_head list;
पूर्ण;

अंतरभूत काष्ठा fsl_otg_समयr *otg_समयr_initializer
(व्योम (*function)(अचिन्हित दीर्घ), अचिन्हित दीर्घ expires, अचिन्हित दीर्घ data)
अणु
	काष्ठा fsl_otg_समयr *समयr;

	समयr = kदो_स्मृति(माप(काष्ठा fsl_otg_समयr), GFP_KERNEL);
	अगर (!समयr)
		वापस शून्य;
	समयr->function = function;
	समयr->expires = expires;
	समयr->data = data;
	वापस समयr;
पूर्ण

काष्ठा fsl_otg अणु
	काष्ठा usb_phy phy;
	काष्ठा otg_fsm fsm;
	काष्ठा usb_dr_mmap *dr_mem_map;
	काष्ठा delayed_work otg_event;

	/* used क्रम usb host */
	काष्ठा work_काष्ठा work_wq;
	u8	host_working;

	पूर्णांक irq;
पूर्ण;

काष्ठा fsl_otg_config अणु
	u8 otg_port;
पूर्ण;

#घोषणा FSL_OTG_NAME		"fsl-usb2-otg"

व्योम fsl_otg_add_समयr(काष्ठा otg_fsm *fsm, व्योम *समयr);
व्योम fsl_otg_del_समयr(काष्ठा otg_fsm *fsm, व्योम *समयr);
व्योम fsl_otg_pulse_vbus(व्योम);
