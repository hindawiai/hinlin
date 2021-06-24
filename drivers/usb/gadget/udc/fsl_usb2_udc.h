<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2004,2012 Freescale Semiconductor, Inc
 * All rights reserved.
 *
 * Freescale USB device/endpoपूर्णांक management रेजिस्टरs
 */
#अगर_अघोषित __FSL_USB2_UDC_H
#घोषणा __FSL_USB2_UDC_H

#समावेश <linux/usb/ch9.h>
#समावेश <linux/usb/gadget.h>

/* ### define USB रेजिस्टरs here
 */
#घोषणा USB_MAX_CTRL_PAYLOAD		64
#घोषणा USB_DR_SYS_OFFSET		0x400

 /* USB DR device mode रेजिस्टरs (Little Endian) */
काष्ठा usb_dr_device अणु
	/* Capability रेजिस्टर */
	u8 res1[256];
	u16 caplength;		/* Capability Register Length */
	u16 hciversion;		/* Host Controller Interface Version */
	u32 hcsparams;		/* Host Controller Structural Parameters */
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
	u8 res6[24];
	u32 configflag;		/* Configure Flag Register */
	u32 portsc1;		/* Port 1 Status and Control Register */
	u8 res7[28];
	u32 otgsc;		/* On-The-Go Status and Control */
	u32 usbmode;		/* USB Mode Register */
	u32 endptsetupstat;	/* Endpoपूर्णांक Setup Status Register */
	u32 endpoपूर्णांकprime;	/* Endpoपूर्णांक Initialization Register */
	u32 endptflush;		/* Endpoपूर्णांक Flush Register */
	u32 endptstatus;	/* Endpoपूर्णांक Status Register */
	u32 endptcomplete;	/* Endpoपूर्णांक Complete Register */
	u32 endptctrl[6];	/* Endpoपूर्णांक Control Registers */
पूर्ण;

 /* USB DR host mode रेजिस्टरs (Little Endian) */
काष्ठा usb_dr_host अणु
	/* Capability रेजिस्टर */
	u8 res1[256];
	u16 caplength;		/* Capability Register Length */
	u16 hciversion;		/* Host Controller Interface Version */
	u32 hcsparams;		/* Host Controller Structural Parameters */
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
	u32 periodiclistbase;	/* Periodic Frame List Base Address Register */
	u32 asynclistaddr;	/* Current Asynchronous List Address Register */
	u8 res5[4];
	u32 burstsize;		/* Master Interface Data Burst Size Register */
	u32 txttfilltuning;	/* Transmit FIFO Tuning Controls Register */
	u8 res6[24];
	u32 configflag;		/* Configure Flag Register */
	u32 portsc1;		/* Port 1 Status and Control Register */
	u8 res7[28];
	u32 otgsc;		/* On-The-Go Status and Control */
	u32 usbmode;		/* USB Mode Register */
	u32 endptsetupstat;	/* Endpoपूर्णांक Setup Status Register */
	u32 endpoपूर्णांकprime;	/* Endpoपूर्णांक Initialization Register */
	u32 endptflush;		/* Endpoपूर्णांक Flush Register */
	u32 endptstatus;	/* Endpoपूर्णांक Status Register */
	u32 endptcomplete;	/* Endpoपूर्णांक Complete Register */
	u32 endptctrl[6];	/* Endpoपूर्णांक Control Registers */
पूर्ण;

 /* non-EHCI USB प्रणाली पूर्णांकerface रेजिस्टरs (Big Endian) */
काष्ठा usb_sys_पूर्णांकerface अणु
	u32 snoop1;
	u32 snoop2;
	u32 age_cnt_thresh;	/* Age Count Threshold Register */
	u32 pri_ctrl;		/* Priority Control Register */
	u32 si_ctrl;		/* System Interface Control Register */
	u8 res[236];
	u32 control;		/* General Purpose Control Register */
पूर्ण;

/* ep0 transfer state */
#घोषणा WAIT_FOR_SETUP          0
#घोषणा DATA_STATE_XMIT         1
#घोषणा DATA_STATE_NEED_ZLP     2
#घोषणा WAIT_FOR_OUT_STATUS     3
#घोषणा DATA_STATE_RECV         4

/* Device Controller Capability Parameter रेजिस्टर */
#घोषणा DCCPARAMS_DC				0x00000080
#घोषणा DCCPARAMS_DEN_MASK			0x0000001f

/* Frame Index Register Bit Masks */
#घोषणा	USB_FRINDEX_MASKS			0x3fff
/* USB CMD  Register Bit Masks */
#घोषणा  USB_CMD_RUN_STOP                     0x00000001
#घोषणा  USB_CMD_CTRL_RESET                   0x00000002
#घोषणा  USB_CMD_PERIODIC_SCHEDULE_EN         0x00000010
#घोषणा  USB_CMD_ASYNC_SCHEDULE_EN            0x00000020
#घोषणा  USB_CMD_INT_AA_DOORBELL              0x00000040
#घोषणा  USB_CMD_ASP                          0x00000300
#घोषणा  USB_CMD_ASYNC_SCH_PARK_EN            0x00000800
#घोषणा  USB_CMD_SUTW                         0x00002000
#घोषणा  USB_CMD_ATDTW                        0x00004000
#घोषणा  USB_CMD_ITC                          0x00FF0000

/* bit 15,3,2 are frame list size */
#घोषणा  USB_CMD_FRAME_SIZE_1024              0x00000000
#घोषणा  USB_CMD_FRAME_SIZE_512               0x00000004
#घोषणा  USB_CMD_FRAME_SIZE_256               0x00000008
#घोषणा  USB_CMD_FRAME_SIZE_128               0x0000000C
#घोषणा  USB_CMD_FRAME_SIZE_64                0x00008000
#घोषणा  USB_CMD_FRAME_SIZE_32                0x00008004
#घोषणा  USB_CMD_FRAME_SIZE_16                0x00008008
#घोषणा  USB_CMD_FRAME_SIZE_8                 0x0000800C

/* bit 9-8 are async schedule park mode count */
#घोषणा  USB_CMD_ASP_00                       0x00000000
#घोषणा  USB_CMD_ASP_01                       0x00000100
#घोषणा  USB_CMD_ASP_10                       0x00000200
#घोषणा  USB_CMD_ASP_11                       0x00000300
#घोषणा  USB_CMD_ASP_BIT_POS                  8

/* bit 23-16 are पूर्णांकerrupt threshold control */
#घोषणा  USB_CMD_ITC_NO_THRESHOLD             0x00000000
#घोषणा  USB_CMD_ITC_1_MICRO_FRM              0x00010000
#घोषणा  USB_CMD_ITC_2_MICRO_FRM              0x00020000
#घोषणा  USB_CMD_ITC_4_MICRO_FRM              0x00040000
#घोषणा  USB_CMD_ITC_8_MICRO_FRM              0x00080000
#घोषणा  USB_CMD_ITC_16_MICRO_FRM             0x00100000
#घोषणा  USB_CMD_ITC_32_MICRO_FRM             0x00200000
#घोषणा  USB_CMD_ITC_64_MICRO_FRM             0x00400000
#घोषणा  USB_CMD_ITC_BIT_POS                  16

/* USB STS Register Bit Masks */
#घोषणा  USB_STS_INT                          0x00000001
#घोषणा  USB_STS_ERR                          0x00000002
#घोषणा  USB_STS_PORT_CHANGE                  0x00000004
#घोषणा  USB_STS_FRM_LST_ROLL                 0x00000008
#घोषणा  USB_STS_SYS_ERR                      0x00000010
#घोषणा  USB_STS_IAA                          0x00000020
#घोषणा  USB_STS_RESET                        0x00000040
#घोषणा  USB_STS_SOF                          0x00000080
#घोषणा  USB_STS_SUSPEND                      0x00000100
#घोषणा  USB_STS_HC_HALTED                    0x00001000
#घोषणा  USB_STS_RCL                          0x00002000
#घोषणा  USB_STS_PERIODIC_SCHEDULE            0x00004000
#घोषणा  USB_STS_ASYNC_SCHEDULE               0x00008000

/* USB INTR Register Bit Masks */
#घोषणा  USB_INTR_INT_EN                      0x00000001
#घोषणा  USB_INTR_ERR_INT_EN                  0x00000002
#घोषणा  USB_INTR_PTC_DETECT_EN               0x00000004
#घोषणा  USB_INTR_FRM_LST_ROLL_EN             0x00000008
#घोषणा  USB_INTR_SYS_ERR_EN                  0x00000010
#घोषणा  USB_INTR_ASYN_ADV_EN                 0x00000020
#घोषणा  USB_INTR_RESET_EN                    0x00000040
#घोषणा  USB_INTR_SOF_EN                      0x00000080
#घोषणा  USB_INTR_DEVICE_SUSPEND              0x00000100

/* Device Address bit masks */
#घोषणा  USB_DEVICE_ADDRESS_MASK              0xFE000000
#घोषणा  USB_DEVICE_ADDRESS_BIT_POS           25

/* endpoपूर्णांक list address bit masks */
#घोषणा USB_EP_LIST_ADDRESS_MASK              0xfffff800

/* PORTSCX  Register Bit Masks */
#घोषणा  PORTSCX_CURRENT_CONNECT_STATUS       0x00000001
#घोषणा  PORTSCX_CONNECT_STATUS_CHANGE        0x00000002
#घोषणा  PORTSCX_PORT_ENABLE                  0x00000004
#घोषणा  PORTSCX_PORT_EN_DIS_CHANGE           0x00000008
#घोषणा  PORTSCX_OVER_CURRENT_ACT             0x00000010
#घोषणा  PORTSCX_OVER_CURRENT_CHG             0x00000020
#घोषणा  PORTSCX_PORT_FORCE_RESUME            0x00000040
#घोषणा  PORTSCX_PORT_SUSPEND                 0x00000080
#घोषणा  PORTSCX_PORT_RESET                   0x00000100
#घोषणा  PORTSCX_LINE_STATUS_BITS             0x00000C00
#घोषणा  PORTSCX_PORT_POWER                   0x00001000
#घोषणा  PORTSCX_PORT_INDICTOR_CTRL           0x0000C000
#घोषणा  PORTSCX_PORT_TEST_CTRL               0x000F0000
#घोषणा  PORTSCX_WAKE_ON_CONNECT_EN           0x00100000
#घोषणा  PORTSCX_WAKE_ON_CONNECT_DIS          0x00200000
#घोषणा  PORTSCX_WAKE_ON_OVER_CURRENT         0x00400000
#घोषणा  PORTSCX_PHY_LOW_POWER_SPD            0x00800000
#घोषणा  PORTSCX_PORT_FORCE_FULL_SPEED        0x01000000
#घोषणा  PORTSCX_PORT_SPEED_MASK              0x0C000000
#घोषणा  PORTSCX_PORT_WIDTH                   0x10000000
#घोषणा  PORTSCX_PHY_TYPE_SEL                 0xC0000000

/* bit 11-10 are line status */
#घोषणा  PORTSCX_LINE_STATUS_SE0              0x00000000
#घोषणा  PORTSCX_LINE_STATUS_JSTATE           0x00000400
#घोषणा  PORTSCX_LINE_STATUS_KSTATE           0x00000800
#घोषणा  PORTSCX_LINE_STATUS_UNDEF            0x00000C00
#घोषणा  PORTSCX_LINE_STATUS_BIT_POS          10

/* bit 15-14 are port indicator control */
#घोषणा  PORTSCX_PIC_OFF                      0x00000000
#घोषणा  PORTSCX_PIC_AMBER                    0x00004000
#घोषणा  PORTSCX_PIC_GREEN                    0x00008000
#घोषणा  PORTSCX_PIC_UNDEF                    0x0000C000
#घोषणा  PORTSCX_PIC_BIT_POS                  14

/* bit 19-16 are port test control */
#घोषणा  PORTSCX_PTC_DISABLE                  0x00000000
#घोषणा  PORTSCX_PTC_JSTATE                   0x00010000
#घोषणा  PORTSCX_PTC_KSTATE                   0x00020000
#घोषणा  PORTSCX_PTC_SEQNAK                   0x00030000
#घोषणा  PORTSCX_PTC_PACKET                   0x00040000
#घोषणा  PORTSCX_PTC_FORCE_EN                 0x00050000
#घोषणा  PORTSCX_PTC_BIT_POS                  16

/* bit 27-26 are port speed */
#घोषणा  PORTSCX_PORT_SPEED_FULL              0x00000000
#घोषणा  PORTSCX_PORT_SPEED_LOW               0x04000000
#घोषणा  PORTSCX_PORT_SPEED_HIGH              0x08000000
#घोषणा  PORTSCX_PORT_SPEED_UNDEF             0x0C000000
#घोषणा  PORTSCX_SPEED_BIT_POS                26

/* bit 28 is parallel transceiver width क्रम UTMI पूर्णांकerface */
#घोषणा  PORTSCX_PTW                          0x10000000
#घोषणा  PORTSCX_PTW_8BIT                     0x00000000
#घोषणा  PORTSCX_PTW_16BIT                    0x10000000

/* bit 31-30 are port transceiver select */
#घोषणा  PORTSCX_PTS_UTMI                     0x00000000
#घोषणा  PORTSCX_PTS_ULPI                     0x80000000
#घोषणा  PORTSCX_PTS_FSLS                     0xC0000000
#घोषणा  PORTSCX_PTS_BIT_POS                  30

/* otgsc Register Bit Masks */
#घोषणा  OTGSC_CTRL_VUSB_DISCHARGE            0x00000001
#घोषणा  OTGSC_CTRL_VUSB_CHARGE               0x00000002
#घोषणा  OTGSC_CTRL_OTG_TERM                  0x00000008
#घोषणा  OTGSC_CTRL_DATA_PULSING              0x00000010
#घोषणा  OTGSC_STS_USB_ID                     0x00000100
#घोषणा  OTGSC_STS_A_VBUS_VALID               0x00000200
#घोषणा  OTGSC_STS_A_SESSION_VALID            0x00000400
#घोषणा  OTGSC_STS_B_SESSION_VALID            0x00000800
#घोषणा  OTGSC_STS_B_SESSION_END              0x00001000
#घोषणा  OTGSC_STS_1MS_TOGGLE                 0x00002000
#घोषणा  OTGSC_STS_DATA_PULSING               0x00004000
#घोषणा  OTGSC_INTSTS_USB_ID                  0x00010000
#घोषणा  OTGSC_INTSTS_A_VBUS_VALID            0x00020000
#घोषणा  OTGSC_INTSTS_A_SESSION_VALID         0x00040000
#घोषणा  OTGSC_INTSTS_B_SESSION_VALID         0x00080000
#घोषणा  OTGSC_INTSTS_B_SESSION_END           0x00100000
#घोषणा  OTGSC_INTSTS_1MS                     0x00200000
#घोषणा  OTGSC_INTSTS_DATA_PULSING            0x00400000
#घोषणा  OTGSC_INTR_USB_ID                    0x01000000
#घोषणा  OTGSC_INTR_A_VBUS_VALID              0x02000000
#घोषणा  OTGSC_INTR_A_SESSION_VALID           0x04000000
#घोषणा  OTGSC_INTR_B_SESSION_VALID           0x08000000
#घोषणा  OTGSC_INTR_B_SESSION_END             0x10000000
#घोषणा  OTGSC_INTR_1MS_TIMER                 0x20000000
#घोषणा  OTGSC_INTR_DATA_PULSING              0x40000000

/* USB MODE Register Bit Masks */
#घोषणा  USB_MODE_CTRL_MODE_IDLE              0x00000000
#घोषणा  USB_MODE_CTRL_MODE_DEVICE            0x00000002
#घोषणा  USB_MODE_CTRL_MODE_HOST              0x00000003
#घोषणा  USB_MODE_CTRL_MODE_MASK              0x00000003
#घोषणा  USB_MODE_CTRL_MODE_RSV               0x00000001
#घोषणा  USB_MODE_ES                          0x00000004 /* Endian Select */
#घोषणा  USB_MODE_SETUP_LOCK_OFF              0x00000008
#घोषणा  USB_MODE_STREAM_DISABLE              0x00000010
/* Endpoपूर्णांक Flush Register */
#घोषणा EPFLUSH_TX_OFFSET		      0x00010000
#घोषणा EPFLUSH_RX_OFFSET		      0x00000000

/* Endpoपूर्णांक Setup Status bit masks */
#घोषणा  EP_SETUP_STATUS_MASK                 0x0000003F
#घोषणा  EP_SETUP_STATUS_EP0		      0x00000001

/* ENDPOINTCTRLx  Register Bit Masks */
#घोषणा  EPCTRL_TX_ENABLE                     0x00800000
#घोषणा  EPCTRL_TX_DATA_TOGGLE_RST            0x00400000	/* Not EP0 */
#घोषणा  EPCTRL_TX_DATA_TOGGLE_INH            0x00200000	/* Not EP0 */
#घोषणा  EPCTRL_TX_TYPE                       0x000C0000
#घोषणा  EPCTRL_TX_DATA_SOURCE                0x00020000	/* Not EP0 */
#घोषणा  EPCTRL_TX_EP_STALL                   0x00010000
#घोषणा  EPCTRL_RX_ENABLE                     0x00000080
#घोषणा  EPCTRL_RX_DATA_TOGGLE_RST            0x00000040	/* Not EP0 */
#घोषणा  EPCTRL_RX_DATA_TOGGLE_INH            0x00000020	/* Not EP0 */
#घोषणा  EPCTRL_RX_TYPE                       0x0000000C
#घोषणा  EPCTRL_RX_DATA_SINK                  0x00000002	/* Not EP0 */
#घोषणा  EPCTRL_RX_EP_STALL                   0x00000001

/* bit 19-18 and 3-2 are endpoपूर्णांक type */
#घोषणा  EPCTRL_EP_TYPE_CONTROL               0
#घोषणा  EPCTRL_EP_TYPE_ISO                   1
#घोषणा  EPCTRL_EP_TYPE_BULK                  2
#घोषणा  EPCTRL_EP_TYPE_INTERRUPT             3
#घोषणा  EPCTRL_TX_EP_TYPE_SHIFT              18
#घोषणा  EPCTRL_RX_EP_TYPE_SHIFT              2

/* SNOOPn Register Bit Masks */
#घोषणा  SNOOP_ADDRESS_MASK                   0xFFFFF000
#घोषणा  SNOOP_SIZE_ZERO                      0x00	/* snooping disable */
#घोषणा  SNOOP_SIZE_4KB                       0x0B	/* 4KB snoop size */
#घोषणा  SNOOP_SIZE_8KB                       0x0C
#घोषणा  SNOOP_SIZE_16KB                      0x0D
#घोषणा  SNOOP_SIZE_32KB                      0x0E
#घोषणा  SNOOP_SIZE_64KB                      0x0F
#घोषणा  SNOOP_SIZE_128KB                     0x10
#घोषणा  SNOOP_SIZE_256KB                     0x11
#घोषणा  SNOOP_SIZE_512KB                     0x12
#घोषणा  SNOOP_SIZE_1MB                       0x13
#घोषणा  SNOOP_SIZE_2MB                       0x14
#घोषणा  SNOOP_SIZE_4MB                       0x15
#घोषणा  SNOOP_SIZE_8MB                       0x16
#घोषणा  SNOOP_SIZE_16MB                      0x17
#घोषणा  SNOOP_SIZE_32MB                      0x18
#घोषणा  SNOOP_SIZE_64MB                      0x19
#घोषणा  SNOOP_SIZE_128MB                     0x1A
#घोषणा  SNOOP_SIZE_256MB                     0x1B
#घोषणा  SNOOP_SIZE_512MB                     0x1C
#घोषणा  SNOOP_SIZE_1GB                       0x1D
#घोषणा  SNOOP_SIZE_2GB                       0x1E	/* 2GB snoop size */

/* pri_ctrl Register Bit Masks */
#घोषणा  PRI_CTRL_PRI_LVL1                    0x0000000C
#घोषणा  PRI_CTRL_PRI_LVL0                    0x00000003

/* si_ctrl Register Bit Masks */
#घोषणा  SI_CTRL_ERR_DISABLE                  0x00000010
#घोषणा  SI_CTRL_IDRC_DISABLE                 0x00000008
#घोषणा  SI_CTRL_RD_SAFE_EN                   0x00000004
#घोषणा  SI_CTRL_RD_PREFETCH_DISABLE          0x00000002
#घोषणा  SI_CTRL_RD_PREFEFETCH_VAL            0x00000001

/* control Register Bit Masks */
#घोषणा  USB_CTRL_IOENB                       0x00000004
#घोषणा  USB_CTRL_ULPI_INT0EN                 0x00000001
#घोषणा USB_CTRL_UTMI_PHY_EN		      0x00000200
#घोषणा USB_CTRL_USB_EN			      0x00000004
#घोषणा USB_CTRL_ULPI_PHY_CLK_SEL	      0x00000400

/* Endpoपूर्णांक Queue Head data काष्ठा
 * Rem: all the variables of qh are LittleEndian Mode
 * and NEXT_POINTER_MASK should operate on a LittleEndian, Phy Addr
 */
काष्ठा ep_queue_head अणु
	u32 max_pkt_length;	/* Mult(31-30) , Zlt(29) , Max Pkt len
				   and IOS(15) */
	u32 curr_dtd_ptr;	/* Current dTD Poपूर्णांकer(31-5) */
	u32 next_dtd_ptr;	/* Next dTD Poपूर्णांकer(31-5), T(0) */
	u32 size_ioc_पूर्णांक_sts;	/* Total bytes (30-16), IOC (15),
				   MultO(11-10), STS (7-0)  */
	u32 buff_ptr0;		/* Buffer poपूर्णांकer Page 0 (31-12) */
	u32 buff_ptr1;		/* Buffer poपूर्णांकer Page 1 (31-12) */
	u32 buff_ptr2;		/* Buffer poपूर्णांकer Page 2 (31-12) */
	u32 buff_ptr3;		/* Buffer poपूर्णांकer Page 3 (31-12) */
	u32 buff_ptr4;		/* Buffer poपूर्णांकer Page 4 (31-12) */
	u32 res1;
	u8 setup_buffer[8];	/* Setup data 8 bytes */
	u32 res2[4];
पूर्ण;

/* Endpoपूर्णांक Queue Head Bit Masks */
#घोषणा  EP_QUEUE_HEAD_MULT_POS               30
#घोषणा  EP_QUEUE_HEAD_ZLT_SEL                0x20000000
#घोषणा  EP_QUEUE_HEAD_MAX_PKT_LEN_POS        16
#घोषणा  EP_QUEUE_HEAD_MAX_PKT_LEN(ep_info)   (((ep_info)>>16)&0x07ff)
#घोषणा  EP_QUEUE_HEAD_IOS                    0x00008000
#घोषणा  EP_QUEUE_HEAD_NEXT_TERMINATE         0x00000001
#घोषणा  EP_QUEUE_HEAD_IOC                    0x00008000
#घोषणा  EP_QUEUE_HEAD_MULTO                  0x00000C00
#घोषणा  EP_QUEUE_HEAD_STATUS_HALT	      0x00000040
#घोषणा  EP_QUEUE_HEAD_STATUS_ACTIVE          0x00000080
#घोषणा  EP_QUEUE_CURRENT_OFFSET_MASK         0x00000FFF
#घोषणा  EP_QUEUE_HEAD_NEXT_POINTER_MASK      0xFFFFFFE0
#घोषणा  EP_QUEUE_FRINDEX_MASK                0x000007FF
#घोषणा  EP_MAX_LENGTH_TRANSFER               0x4000

/* Endpoपूर्णांक Transfer Descriptor data काष्ठा */
/* Rem: all the variables of td are LittleEndian Mode */
काष्ठा ep_td_काष्ठा अणु
	u32 next_td_ptr;	/* Next TD poपूर्णांकer(31-5), T(0) set
				   indicate invalid */
	u32 size_ioc_sts;	/* Total bytes (30-16), IOC (15),
				   MultO(11-10), STS (7-0)  */
	u32 buff_ptr0;		/* Buffer poपूर्णांकer Page 0 */
	u32 buff_ptr1;		/* Buffer poपूर्णांकer Page 1 */
	u32 buff_ptr2;		/* Buffer poपूर्णांकer Page 2 */
	u32 buff_ptr3;		/* Buffer poपूर्णांकer Page 3 */
	u32 buff_ptr4;		/* Buffer poपूर्णांकer Page 4 */
	u32 res;
	/* 32 bytes */
	dma_addr_t td_dma;	/* dma address क्रम this td */
	/* भव address of next td specअगरied in next_td_ptr */
	काष्ठा ep_td_काष्ठा *next_td_virt;
पूर्ण;

/* Endpoपूर्णांक Transfer Descriptor bit Masks */
#घोषणा  DTD_NEXT_TERMINATE                   0x00000001
#घोषणा  DTD_IOC                              0x00008000
#घोषणा  DTD_STATUS_ACTIVE                    0x00000080
#घोषणा  DTD_STATUS_HALTED                    0x00000040
#घोषणा  DTD_STATUS_DATA_BUFF_ERR             0x00000020
#घोषणा  DTD_STATUS_TRANSACTION_ERR           0x00000008
#घोषणा  DTD_RESERVED_FIELDS                  0x80007300
#घोषणा  DTD_ADDR_MASK                        0xFFFFFFE0
#घोषणा  DTD_PACKET_SIZE                      0x7FFF0000
#घोषणा  DTD_LENGTH_BIT_POS                   16
#घोषणा  DTD_ERROR_MASK                       (DTD_STATUS_HALTED | \
                                               DTD_STATUS_DATA_BUFF_ERR | \
                                               DTD_STATUS_TRANSACTION_ERR)
/* Alignment requirements; must be a घातer of two */
#घोषणा DTD_ALIGNMENT				0x20
#घोषणा QH_ALIGNMENT				2048

/* Controller dma boundary */
#घोषणा UDC_DMA_BOUNDARY			0x1000

/*-------------------------------------------------------------------------*/

/* ### driver निजी data
 */
काष्ठा fsl_req अणु
	काष्ठा usb_request req;
	काष्ठा list_head queue;
	/* ep_queue() func will add
	   a request->queue पूर्णांकo a udc_ep->queue 'd tail */
	काष्ठा fsl_ep *ep;
	अचिन्हित mapped:1;

	काष्ठा ep_td_काष्ठा *head, *tail;	/* For dTD List
						   cpu endian Virtual addr */
	अचिन्हित पूर्णांक dtd_count;
पूर्ण;

#घोषणा REQ_UNCOMPLETE			1

काष्ठा fsl_ep अणु
	काष्ठा usb_ep ep;
	काष्ठा list_head queue;
	काष्ठा fsl_udc *udc;
	काष्ठा ep_queue_head *qh;
	काष्ठा usb_gadget *gadget;

	अक्षर name[14];
	अचिन्हित stopped:1;
पूर्ण;

#घोषणा EP_सूची_IN	1
#घोषणा EP_सूची_OUT	0

काष्ठा fsl_udc अणु
	काष्ठा usb_gadget gadget;
	काष्ठा usb_gadget_driver *driver;
	काष्ठा fsl_usb2_platक्रमm_data *pdata;
	काष्ठा completion *करोne;	/* to make sure release() is करोne */
	काष्ठा fsl_ep *eps;
	अचिन्हित पूर्णांक max_ep;
	अचिन्हित पूर्णांक irq;

	काष्ठा usb_ctrlrequest local_setup_buff;
	spinlock_t lock;
	काष्ठा usb_phy *transceiver;
	अचिन्हित softconnect:1;
	अचिन्हित vbus_active:1;
	अचिन्हित stopped:1;
	अचिन्हित remote_wakeup:1;
	अचिन्हित alपढ़ोy_stopped:1;
	अचिन्हित big_endian_desc:1;

	काष्ठा ep_queue_head *ep_qh;	/* Endpoपूर्णांकs Queue-Head */
	काष्ठा fsl_req *status_req;	/* ep0 status request */
	काष्ठा dma_pool *td_pool;	/* dma pool क्रम DTD */
	क्रमागत fsl_usb2_phy_modes phy_mode;

	माप_प्रकार ep_qh_size;		/* size after alignment adjusपंचांगent*/
	dma_addr_t ep_qh_dma;		/* dma address of QH */

	u32 max_pipes;          /* Device max pipes */
	u32 bus_reset;		/* Device is bus resetting */
	u32 resume_state;	/* USB state to resume */
	u32 usb_state;		/* USB current state */
	u32 ep0_state;		/* Endpoपूर्णांक zero state */
	u32 ep0_dir;		/* Endpoपूर्णांक zero direction: can be
				   USB_सूची_IN or USB_सूची_OUT */
	u8 device_address;	/* Device USB address */
पूर्ण;

/*-------------------------------------------------------------------------*/

#अगर_घोषित DEBUG
#घोषणा DBG(fmt, args...) 	prपूर्णांकk(KERN_DEBUG "[%s]  " fmt "\n", \
				__func__, ## args)
#अन्यथा
#घोषणा DBG(fmt, args...)	करोअणुपूर्णजबतक(0)
#पूर्ण_अगर

#अगर 0
अटल व्योम dump_msg(स्थिर अक्षर *label, स्थिर u8 * buf, अचिन्हित पूर्णांक length)
अणु
	अचिन्हित पूर्णांक start, num, i;
	अक्षर line[52], *p;

	अगर (length >= 512)
		वापस;
	DBG("%s, length %u:\n", label, length);
	start = 0;
	जबतक (length > 0) अणु
		num = min(length, 16u);
		p = line;
		क्रम (i = 0; i < num; ++i) अणु
			अगर (i == 8)
				*p++ = ' ';
			प्र_लिखो(p, " %02x", buf[i]);
			p += 3;
		पूर्ण
		*p = 0;
		prपूर्णांकk(KERN_DEBUG "%6x: %s\n", start, line);
		buf += num;
		start += num;
		length -= num;
	पूर्ण
पूर्ण
#पूर्ण_अगर

#अगर_घोषित VERBOSE
#घोषणा VDBG		DBG
#अन्यथा
#घोषणा VDBG(stuff...)	करोअणुपूर्णजबतक(0)
#पूर्ण_अगर

#घोषणा ERR(stuff...)		pr_err("udc: " stuff)
#घोषणा WARNING(stuff...)	pr_warn("udc: " stuff)
#घोषणा INFO(stuff...)		pr_info("udc: " stuff)

/*-------------------------------------------------------------------------*/

/* ### Add board specअगरic defines here
 */

/*
 * ### pipe direction macro from device view
 */
#घोषणा USB_RECV	0	/* OUT EP */
#घोषणा USB_SEND	1	/* IN EP */

/*
 * ### पूर्णांकernal used help routines.
 */
#घोषणा ep_index(EP)		((EP)->ep.desc->bEndpoपूर्णांकAddress&0xF)
#घोषणा ep_maxpacket(EP)	((EP)->ep.maxpacket)
#घोषणा ep_is_in(EP)	( (ep_index(EP) == 0) ? (EP->udc->ep0_dir == \
			USB_सूची_IN) : ((EP)->ep.desc->bEndpoपूर्णांकAddress \
			& USB_सूची_IN)==USB_सूची_IN)
#घोषणा get_ep_by_pipe(udc, pipe)	((pipe == 1)? &udc->eps[0]: \
					&udc->eps[pipe])
#घोषणा get_pipe_by_windex(windex)	((windex & USB_ENDPOINT_NUMBER_MASK) \
					* 2 + ((windex & USB_सूची_IN) ? 1 : 0))
#घोषणा get_pipe_by_ep(EP)	(ep_index(EP) * 2 + ep_is_in(EP))

अटल अंतरभूत काष्ठा ep_queue_head *get_qh_by_ep(काष्ठा fsl_ep *ep)
अणु
	/* we only have one ep0 काष्ठाure but two queue heads */
	अगर (ep_index(ep) != 0)
		वापस ep->qh;
	अन्यथा
		वापस &ep->udc->ep_qh[(ep->udc->ep0_dir ==
				USB_सूची_IN) ? 1 : 0];
पूर्ण

काष्ठा platक्रमm_device;
#अगर_घोषित CONFIG_ARCH_MXC
पूर्णांक fsl_udc_clk_init(काष्ठा platक्रमm_device *pdev);
पूर्णांक fsl_udc_clk_finalize(काष्ठा platक्रमm_device *pdev);
व्योम fsl_udc_clk_release(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक fsl_udc_clk_init(काष्ठा platक्रमm_device *pdev)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक fsl_udc_clk_finalize(काष्ठा platक्रमm_device *pdev)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम fsl_udc_clk_release(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
