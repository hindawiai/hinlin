<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2011 Marvell International Ltd. All rights reserved.
 */

#अगर_अघोषित __MV_UDC_H
#घोषणा __MV_UDC_H

#घोषणा VUSBHS_MAX_PORTS	8

#घोषणा DQH_ALIGNMENT		2048
#घोषणा DTD_ALIGNMENT		64
#घोषणा DMA_BOUNDARY		4096

#घोषणा EP_सूची_IN	1
#घोषणा EP_सूची_OUT	0

#घोषणा DMA_ADDR_INVALID	(~(dma_addr_t)0)

#घोषणा EP0_MAX_PKT_SIZE	64
/* ep0 transfer state */
#घोषणा WAIT_FOR_SETUP		0
#घोषणा DATA_STATE_XMIT		1
#घोषणा DATA_STATE_NEED_ZLP	2
#घोषणा WAIT_FOR_OUT_STATUS	3
#घोषणा DATA_STATE_RECV		4

#घोषणा CAPLENGTH_MASK		(0xff)
#घोषणा DCCPARAMS_DEN_MASK	(0x1f)

#घोषणा HCSPARAMS_PPC		(0x10)

/* Frame Index Register Bit Masks */
#घोषणा USB_FRINDEX_MASKS	0x3fff

/* Command Register Bit Masks */
#घोषणा USBCMD_RUN_STOP				(0x00000001)
#घोषणा USBCMD_CTRL_RESET			(0x00000002)
#घोषणा USBCMD_SETUP_TRIPWIRE_SET		(0x00002000)
#घोषणा USBCMD_SETUP_TRIPWIRE_CLEAR		(~USBCMD_SETUP_TRIPWIRE_SET)

#घोषणा USBCMD_ATDTW_TRIPWIRE_SET		(0x00004000)
#घोषणा USBCMD_ATDTW_TRIPWIRE_CLEAR		(~USBCMD_ATDTW_TRIPWIRE_SET)

/* bit 15,3,2 are क्रम frame list size */
#घोषणा USBCMD_FRAME_SIZE_1024			(0x00000000) /* 000 */
#घोषणा USBCMD_FRAME_SIZE_512			(0x00000004) /* 001 */
#घोषणा USBCMD_FRAME_SIZE_256			(0x00000008) /* 010 */
#घोषणा USBCMD_FRAME_SIZE_128			(0x0000000C) /* 011 */
#घोषणा USBCMD_FRAME_SIZE_64			(0x00008000) /* 100 */
#घोषणा USBCMD_FRAME_SIZE_32			(0x00008004) /* 101 */
#घोषणा USBCMD_FRAME_SIZE_16			(0x00008008) /* 110 */
#घोषणा USBCMD_FRAME_SIZE_8			(0x0000800C) /* 111 */

#घोषणा EPCTRL_TX_ALL_MASK			(0xFFFF0000)
#घोषणा EPCTRL_RX_ALL_MASK			(0x0000FFFF)

#घोषणा EPCTRL_TX_DATA_TOGGLE_RST		(0x00400000)
#घोषणा EPCTRL_TX_EP_STALL			(0x00010000)
#घोषणा EPCTRL_RX_EP_STALL			(0x00000001)
#घोषणा EPCTRL_RX_DATA_TOGGLE_RST		(0x00000040)
#घोषणा EPCTRL_RX_ENABLE			(0x00000080)
#घोषणा EPCTRL_TX_ENABLE			(0x00800000)
#घोषणा EPCTRL_CONTROL				(0x00000000)
#घोषणा EPCTRL_ISOCHRONOUS			(0x00040000)
#घोषणा EPCTRL_BULK				(0x00080000)
#घोषणा EPCTRL_INT				(0x000C0000)
#घोषणा EPCTRL_TX_TYPE				(0x000C0000)
#घोषणा EPCTRL_RX_TYPE				(0x0000000C)
#घोषणा EPCTRL_DATA_TOGGLE_INHIBIT		(0x00000020)
#घोषणा EPCTRL_TX_EP_TYPE_SHIFT			(18)
#घोषणा EPCTRL_RX_EP_TYPE_SHIFT			(2)

#घोषणा EPCOMPLETE_MAX_ENDPOINTS		(16)

/* endpoपूर्णांक list address bit masks */
#घोषणा USB_EP_LIST_ADDRESS_MASK              0xfffff800

#घोषणा PORTSCX_W1C_BITS			0x2a
#घोषणा PORTSCX_PORT_RESET			0x00000100
#घोषणा PORTSCX_PORT_POWER			0x00001000
#घोषणा PORTSCX_FORCE_FULL_SPEED_CONNECT	0x01000000
#घोषणा PORTSCX_PAR_XCVR_SELECT			0xC0000000
#घोषणा PORTSCX_PORT_FORCE_RESUME		0x00000040
#घोषणा PORTSCX_PORT_SUSPEND			0x00000080
#घोषणा PORTSCX_PORT_SPEED_FULL			0x00000000
#घोषणा PORTSCX_PORT_SPEED_LOW			0x04000000
#घोषणा PORTSCX_PORT_SPEED_HIGH			0x08000000
#घोषणा PORTSCX_PORT_SPEED_MASK			0x0C000000

/* USB MODE Register Bit Masks */
#घोषणा USBMODE_CTRL_MODE_IDLE			0x00000000
#घोषणा USBMODE_CTRL_MODE_DEVICE		0x00000002
#घोषणा USBMODE_CTRL_MODE_HOST			0x00000003
#घोषणा USBMODE_CTRL_MODE_RSV			0x00000001
#घोषणा USBMODE_SETUP_LOCK_OFF			0x00000008
#घोषणा USBMODE_STREAM_DISABLE			0x00000010

/* USB STS Register Bit Masks */
#घोषणा USBSTS_INT			0x00000001
#घोषणा USBSTS_ERR			0x00000002
#घोषणा USBSTS_PORT_CHANGE		0x00000004
#घोषणा USBSTS_FRM_LST_ROLL		0x00000008
#घोषणा USBSTS_SYS_ERR			0x00000010
#घोषणा USBSTS_IAA			0x00000020
#घोषणा USBSTS_RESET			0x00000040
#घोषणा USBSTS_SOF			0x00000080
#घोषणा USBSTS_SUSPEND			0x00000100
#घोषणा USBSTS_HC_HALTED		0x00001000
#घोषणा USBSTS_RCL			0x00002000
#घोषणा USBSTS_PERIODIC_SCHEDULE	0x00004000
#घोषणा USBSTS_ASYNC_SCHEDULE		0x00008000


/* Interrupt Enable Register Bit Masks */
#घोषणा USBINTR_INT_EN                          (0x00000001)
#घोषणा USBINTR_ERR_INT_EN                      (0x00000002)
#घोषणा USBINTR_PORT_CHANGE_DETECT_EN           (0x00000004)

#घोषणा USBINTR_ASYNC_ADV_AAE                   (0x00000020)
#घोषणा USBINTR_ASYNC_ADV_AAE_ENABLE            (0x00000020)
#घोषणा USBINTR_ASYNC_ADV_AAE_DISABLE           (0xFFFFFFDF)

#घोषणा USBINTR_RESET_EN                        (0x00000040)
#घोषणा USBINTR_SOF_UFRAME_EN                   (0x00000080)
#घोषणा USBINTR_DEVICE_SUSPEND                  (0x00000100)

#घोषणा USB_DEVICE_ADDRESS_MASK			(0xfe000000)
#घोषणा USB_DEVICE_ADDRESS_BIT_SHIFT		(25)

काष्ठा mv_cap_regs अणु
	u32	caplength_hciversion;
	u32	hcsparams;	/* HC काष्ठाural parameters */
	u32	hccparams;	/* HC Capability Parameters*/
	u32	reserved[5];
	u32	dciversion;	/* DC version number and reserved 16 bits */
	u32	dccparams;	/* DC Capability Parameters */
पूर्ण;

काष्ठा mv_op_regs अणु
	u32	usbcmd;		/* Command रेजिस्टर */
	u32	usbsts;		/* Status रेजिस्टर */
	u32	usbपूर्णांकr;	/* Interrupt enable */
	u32	frindex;	/* Frame index */
	u32	reserved1[1];
	u32	deviceaddr;	/* Device Address */
	u32	eplistaddr;	/* Endpoपूर्णांक List Address */
	u32	ttctrl;		/* HOST TT status and control */
	u32	burstsize;	/* Programmable Burst Size */
	u32	txfilltuning;	/* Host Transmit Pre-Buffer Packet Tuning */
	u32	reserved[4];
	u32	epnak;		/* Endpoपूर्णांक NAK */
	u32	epnaken;	/* Endpoपूर्णांक NAK Enable */
	u32	configflag;	/* Configured Flag रेजिस्टर */
	u32	portsc[VUSBHS_MAX_PORTS]; /* Port Status/Control x, x = 1..8 */
	u32	otgsc;
	u32	usbmode;	/* USB Host/Device mode */
	u32	epsetupstat;	/* Endpoपूर्णांक Setup Status */
	u32	epprime;	/* Endpoपूर्णांक Initialize */
	u32	epflush;	/* Endpoपूर्णांक De-initialize */
	u32	epstatus;	/* Endpoपूर्णांक Status */
	u32	epcomplete;	/* Endpoपूर्णांक Interrupt On Complete */
	u32	epctrlx[16];	/* Endpoपूर्णांक Control, where x = 0.. 15 */
	u32	mcr;		/* Mux Control */
	u32	isr;		/* Interrupt Status */
	u32	ier;		/* Interrupt Enable */
पूर्ण;

काष्ठा mv_udc अणु
	काष्ठा usb_gadget		gadget;
	काष्ठा usb_gadget_driver	*driver;
	spinlock_t			lock;
	काष्ठा completion		*करोne;
	काष्ठा platक्रमm_device		*dev;
	पूर्णांक				irq;

	काष्ठा mv_cap_regs __iomem	*cap_regs;
	काष्ठा mv_op_regs __iomem	*op_regs;
	व्योम __iomem                    *phy_regs;
	अचिन्हित पूर्णांक			max_eps;
	काष्ठा mv_dqh			*ep_dqh;
	माप_प्रकार				ep_dqh_size;
	dma_addr_t			ep_dqh_dma;

	काष्ठा dma_pool			*dtd_pool;
	काष्ठा mv_ep			*eps;

	काष्ठा mv_dtd			*dtd_head;
	काष्ठा mv_dtd			*dtd_tail;
	अचिन्हित पूर्णांक			dtd_entries;

	काष्ठा mv_req			*status_req;
	काष्ठा usb_ctrlrequest		local_setup_buff;

	अचिन्हित पूर्णांक		resume_state;	/* USB state to resume */
	अचिन्हित पूर्णांक		usb_state;	/* USB current state */
	अचिन्हित पूर्णांक		ep0_state;	/* Endpoपूर्णांक zero state */
	अचिन्हित पूर्णांक		ep0_dir;

	अचिन्हित पूर्णांक		dev_addr;
	अचिन्हित पूर्णांक		test_mode;

	पूर्णांक			errors;
	अचिन्हित		softconnect:1,
				vbus_active:1,
				remote_wakeup:1,
				softconnected:1,
				क्रमce_fs:1,
				घड़ी_gating:1,
				active:1,
				stopped:1;      /* stop bit is setted */

	काष्ठा work_काष्ठा	vbus_work;
	काष्ठा workqueue_काष्ठा *qwork;

	काष्ठा usb_phy		*transceiver;

	काष्ठा mv_usb_platक्रमm_data     *pdata;

	/* some SOC has mutiple घड़ी sources क्रम USB*/
	काष्ठा clk      *clk;
पूर्ण;

/* endpoपूर्णांक data काष्ठाure */
काष्ठा mv_ep अणु
	काष्ठा usb_ep		ep;
	काष्ठा mv_udc		*udc;
	काष्ठा list_head	queue;
	काष्ठा mv_dqh		*dqh;
	u32			direction;
	अक्षर			name[14];
	अचिन्हित		stopped:1,
				wedge:1,
				ep_type:2,
				ep_num:8;
पूर्ण;

/* request data काष्ठाure */
काष्ठा mv_req अणु
	काष्ठा usb_request	req;
	काष्ठा mv_dtd		*dtd, *head, *tail;
	काष्ठा mv_ep		*ep;
	काष्ठा list_head	queue;
	अचिन्हित पूर्णांक            test_mode;
	अचिन्हित		dtd_count;
	अचिन्हित		mapped:1;
पूर्ण;

#घोषणा EP_QUEUE_HEAD_MULT_POS			30
#घोषणा EP_QUEUE_HEAD_ZLT_SEL			0x20000000
#घोषणा EP_QUEUE_HEAD_MAX_PKT_LEN_POS		16
#घोषणा EP_QUEUE_HEAD_MAX_PKT_LEN(ep_info)	(((ep_info)>>16)&0x07ff)
#घोषणा EP_QUEUE_HEAD_IOS			0x00008000
#घोषणा EP_QUEUE_HEAD_NEXT_TERMINATE		0x00000001
#घोषणा EP_QUEUE_HEAD_IOC			0x00008000
#घोषणा EP_QUEUE_HEAD_MULTO			0x00000C00
#घोषणा EP_QUEUE_HEAD_STATUS_HALT		0x00000040
#घोषणा EP_QUEUE_HEAD_STATUS_ACTIVE		0x00000080
#घोषणा EP_QUEUE_CURRENT_OFFSET_MASK		0x00000FFF
#घोषणा EP_QUEUE_HEAD_NEXT_POINTER_MASK		0xFFFFFFE0
#घोषणा EP_QUEUE_FRINDEX_MASK			0x000007FF
#घोषणा EP_MAX_LENGTH_TRANSFER			0x4000

काष्ठा mv_dqh अणु
	/* Bits 16..26 Bit 15 is Interrupt On Setup */
	u32	max_packet_length;
	u32	curr_dtd_ptr;		/* Current dTD Poपूर्णांकer */
	u32	next_dtd_ptr;		/* Next dTD Poपूर्णांकer */
	/* Total bytes (16..30), IOC (15), INT (8), STS (0-7) */
	u32	size_ioc_पूर्णांक_sts;
	u32	buff_ptr0;		/* Buffer poपूर्णांकer Page 0 (12-31) */
	u32	buff_ptr1;		/* Buffer poपूर्णांकer Page 1 (12-31) */
	u32	buff_ptr2;		/* Buffer poपूर्णांकer Page 2 (12-31) */
	u32	buff_ptr3;		/* Buffer poपूर्णांकer Page 3 (12-31) */
	u32	buff_ptr4;		/* Buffer poपूर्णांकer Page 4 (12-31) */
	u32	reserved1;
	/* 8 bytes of setup data that follows the Setup PID */
	u8	setup_buffer[8];
	u32	reserved2[4];
पूर्ण;


#घोषणा DTD_NEXT_TERMINATE		(0x00000001)
#घोषणा DTD_IOC				(0x00008000)
#घोषणा DTD_STATUS_ACTIVE		(0x00000080)
#घोषणा DTD_STATUS_HALTED		(0x00000040)
#घोषणा DTD_STATUS_DATA_BUFF_ERR	(0x00000020)
#घोषणा DTD_STATUS_TRANSACTION_ERR	(0x00000008)
#घोषणा DTD_RESERVED_FIELDS		(0x00007F00)
#घोषणा DTD_ERROR_MASK			(0x68)
#घोषणा DTD_ADDR_MASK			(0xFFFFFFE0)
#घोषणा DTD_PACKET_SIZE			0x7FFF0000
#घोषणा DTD_LENGTH_BIT_POS		(16)

काष्ठा mv_dtd अणु
	u32	dtd_next;
	u32	size_ioc_sts;
	u32	buff_ptr0;		/* Buffer poपूर्णांकer Page 0 */
	u32	buff_ptr1;		/* Buffer poपूर्णांकer Page 1 */
	u32	buff_ptr2;		/* Buffer poपूर्णांकer Page 2 */
	u32	buff_ptr3;		/* Buffer poपूर्णांकer Page 3 */
	u32	buff_ptr4;		/* Buffer poपूर्णांकer Page 4 */
	u32	scratch_ptr;
	/* 32 bytes */
	dma_addr_t td_dma;		/* dma address क्रम this td */
	काष्ठा mv_dtd *next_dtd_virt;
पूर्ण;

#पूर्ण_अगर
