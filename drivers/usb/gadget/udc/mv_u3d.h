<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2011 Marvell International Ltd. All rights reserved.
 */

#अगर_अघोषित __MV_U3D_H
#घोषणा __MV_U3D_H

#घोषणा MV_U3D_EP_CONTEXT_ALIGNMENT	32
#घोषणा MV_U3D_TRB_ALIGNMENT	16
#घोषणा MV_U3D_DMA_BOUNDARY	4096
#घोषणा MV_U3D_EP0_MAX_PKT_SIZE	512

/* ep0 transfer state */
#घोषणा MV_U3D_WAIT_FOR_SETUP		0
#घोषणा MV_U3D_DATA_STATE_XMIT		1
#घोषणा MV_U3D_DATA_STATE_NEED_ZLP	2
#घोषणा MV_U3D_WAIT_FOR_OUT_STATUS	3
#घोषणा MV_U3D_DATA_STATE_RECV		4
#घोषणा MV_U3D_STATUS_STAGE		5

#घोषणा MV_U3D_EP_MAX_LENGTH_TRANSFER	0x10000

/* USB3 Interrupt Status */
#घोषणा MV_U3D_USBINT_SETUP		0x00000001
#घोषणा MV_U3D_USBINT_RX_COMPLETE	0x00000002
#घोषणा MV_U3D_USBINT_TX_COMPLETE	0x00000004
#घोषणा MV_U3D_USBINT_UNDER_RUN	0x00000008
#घोषणा MV_U3D_USBINT_RXDESC_ERR	0x00000010
#घोषणा MV_U3D_USBINT_TXDESC_ERR	0x00000020
#घोषणा MV_U3D_USBINT_RX_TRB_COMPLETE	0x00000040
#घोषणा MV_U3D_USBINT_TX_TRB_COMPLETE	0x00000080
#घोषणा MV_U3D_USBINT_VBUS_VALID	0x00010000
#घोषणा MV_U3D_USBINT_STORAGE_CMD_FULL	0x00020000
#घोषणा MV_U3D_USBINT_LINK_CHG		0x01000000

/* USB3 Interrupt Enable */
#घोषणा MV_U3D_INTR_ENABLE_SETUP		0x00000001
#घोषणा MV_U3D_INTR_ENABLE_RX_COMPLETE		0x00000002
#घोषणा MV_U3D_INTR_ENABLE_TX_COMPLETE		0x00000004
#घोषणा MV_U3D_INTR_ENABLE_UNDER_RUN		0x00000008
#घोषणा MV_U3D_INTR_ENABLE_RXDESC_ERR		0x00000010
#घोषणा MV_U3D_INTR_ENABLE_TXDESC_ERR		0x00000020
#घोषणा MV_U3D_INTR_ENABLE_RX_TRB_COMPLETE	0x00000040
#घोषणा MV_U3D_INTR_ENABLE_TX_TRB_COMPLETE	0x00000080
#घोषणा MV_U3D_INTR_ENABLE_RX_BUFFER_ERR	0x00000100
#घोषणा MV_U3D_INTR_ENABLE_VBUS_VALID		0x00010000
#घोषणा MV_U3D_INTR_ENABLE_STORAGE_CMD_FULL	0x00020000
#घोषणा MV_U3D_INTR_ENABLE_LINK_CHG		0x01000000
#घोषणा MV_U3D_INTR_ENABLE_PRIME_STATUS	0x02000000

/* USB3 Link Change */
#घोषणा MV_U3D_LINK_CHANGE_LINK_UP		0x00000001
#घोषणा MV_U3D_LINK_CHANGE_SUSPEND		0x00000002
#घोषणा MV_U3D_LINK_CHANGE_RESUME		0x00000004
#घोषणा MV_U3D_LINK_CHANGE_WRESET		0x00000008
#घोषणा MV_U3D_LINK_CHANGE_HRESET		0x00000010
#घोषणा MV_U3D_LINK_CHANGE_VBUS_INVALID	0x00000020
#घोषणा MV_U3D_LINK_CHANGE_INACT		0x00000040
#घोषणा MV_U3D_LINK_CHANGE_DISABLE_AFTER_U0	0x00000080
#घोषणा MV_U3D_LINK_CHANGE_U1			0x00000100
#घोषणा MV_U3D_LINK_CHANGE_U2			0x00000200
#घोषणा MV_U3D_LINK_CHANGE_U3			0x00000400

/* bridge setting */
#घोषणा MV_U3D_BRIDGE_SETTING_VBUS_VALID	(1 << 16)

/* Command Register Bit Masks */
#घोषणा MV_U3D_CMD_RUN_STOP		0x00000001
#घोषणा MV_U3D_CMD_CTRL_RESET		0x00000002

/* ep control रेजिस्टर */
#घोषणा MV_U3D_EPXCR_EP_TYPE_CONTROL		0
#घोषणा MV_U3D_EPXCR_EP_TYPE_ISOC		1
#घोषणा MV_U3D_EPXCR_EP_TYPE_BULK		2
#घोषणा MV_U3D_EPXCR_EP_TYPE_INT		3
#घोषणा MV_U3D_EPXCR_EP_ENABLE_SHIFT		4
#घोषणा MV_U3D_EPXCR_MAX_BURST_SIZE_SHIFT	12
#घोषणा MV_U3D_EPXCR_MAX_PACKET_SIZE_SHIFT	16
#घोषणा MV_U3D_USB_BULK_BURST_OUT		6
#घोषणा MV_U3D_USB_BULK_BURST_IN		14

#घोषणा MV_U3D_EPXCR_EP_FLUSH		(1 << 7)
#घोषणा MV_U3D_EPXCR_EP_HALT		(1 << 1)
#घोषणा MV_U3D_EPXCR_EP_INIT		(1)

/* TX/RX Status Register */
#घोषणा MV_U3D_XFERSTATUS_COMPLETE_SHIFT	24
#घोषणा MV_U3D_COMPLETE_INVALID	0
#घोषणा MV_U3D_COMPLETE_SUCCESS	1
#घोषणा MV_U3D_COMPLETE_BUFF_ERR	2
#घोषणा MV_U3D_COMPLETE_SHORT_PACKET	3
#घोषणा MV_U3D_COMPLETE_TRB_ERR	5
#घोषणा MV_U3D_XFERSTATUS_TRB_LENGTH_MASK	(0xFFFFFF)

#घोषणा MV_U3D_USB_LINK_BYPASS_VBUS	0x8

#घोषणा MV_U3D_LTSSM_PHY_INIT_DONE		0x80000000
#घोषणा MV_U3D_LTSSM_NEVER_GO_COMPLIANCE	0x40000000

#घोषणा MV_U3D_USB3_OP_REGS_OFFSET	0x100
#घोषणा MV_U3D_USB3_PHY_OFFSET		0xB800

#घोषणा DCS_ENABLE	0x1

/* समयout */
#घोषणा MV_U3D_RESET_TIMEOUT		10000
#घोषणा MV_U3D_FLUSH_TIMEOUT		100000
#घोषणा MV_U3D_OWN_TIMEOUT		10000
#घोषणा LOOPS_USEC_SHIFT	4
#घोषणा LOOPS_USEC		(1 << LOOPS_USEC_SHIFT)
#घोषणा LOOPS(समयout)		((समयout) >> LOOPS_USEC_SHIFT)

/* ep direction */
#घोषणा MV_U3D_EP_सूची_IN		1
#घोषणा MV_U3D_EP_सूची_OUT		0
#घोषणा mv_u3d_ep_dir(ep)	(((ep)->ep_num == 0) ? \
				((ep)->u3d->ep0_dir) : ((ep)->direction))

/* usb capability रेजिस्टरs */
काष्ठा mv_u3d_cap_regs अणु
	u32	rsvd[5];
	u32	dboff;	/* करोorbell रेजिस्टर offset */
	u32	rtsoff;	/* runसमय रेजिस्टर offset */
	u32	vuoff;	/* venकरोr unique रेजिस्टर offset */
पूर्ण;

/* operation रेजिस्टरs */
काष्ठा mv_u3d_op_regs अणु
	u32	usbcmd;		/* Command रेजिस्टर */
	u32	rsvd1[11];
	u32	dcbaapl;	/* Device Context Base Address low रेजिस्टर */
	u32	dcbaaph;	/* Device Context Base Address high रेजिस्टर */
	u32	rsvd2[243];
	u32	portsc;		/* port status and control रेजिस्टर*/
	u32	portlinkinfo;	/* port link info रेजिस्टर*/
	u32	rsvd3[9917];
	u32	करोorbell;	/* करोorbell रेजिस्टर */
पूर्ण;

/* control endpoपूर्णांक enable रेजिस्टरs */
काष्ठा epxcr अणु
	u32	epxoutcr0;	/* ep out control 0 रेजिस्टर */
	u32	epxoutcr1;	/* ep out control 1 रेजिस्टर */
	u32	epxincr0;	/* ep in control 0 रेजिस्टर */
	u32	epxincr1;	/* ep in control 1 रेजिस्टर */
पूर्ण;

/* transfer status रेजिस्टरs */
काष्ठा xferstatus अणु
	u32	curdeqlo;	/* current TRB poपूर्णांकer low */
	u32	curdeqhi;	/* current TRB poपूर्णांकer high */
	u32	statuslo;	/* transfer status low */
	u32	statushi;	/* transfer status high */
पूर्ण;

/* venकरोr unique control रेजिस्टरs */
काष्ठा mv_u3d_vuc_regs अणु
	u32	ctrlepenable;	/* control endpoपूर्णांक enable रेजिस्टर */
	u32	setuplock;	/* setup lock रेजिस्टर */
	u32	endcomplete;	/* endpoपूर्णांक transfer complete रेजिस्टर */
	u32	पूर्णांकrcause;	/* पूर्णांकerrupt cause रेजिस्टर */
	u32	पूर्णांकrenable;	/* पूर्णांकerrupt enable रेजिस्टर */
	u32	trbcomplete;	/* TRB complete रेजिस्टर */
	u32	linkchange;	/* link change रेजिस्टर */
	u32	rsvd1[5];
	u32	trbunderrun;	/* TRB underrun रेजिस्टर */
	u32	rsvd2[43];
	u32	bridgesetting;	/* bridge setting रेजिस्टर */
	u32	rsvd3[7];
	काष्ठा xferstatus	txst[16];	/* TX status रेजिस्टर */
	काष्ठा xferstatus	rxst[16];	/* RX status रेजिस्टर */
	u32	ltssm;		/* LTSSM control रेजिस्टर */
	u32	pipe;		/* PIPE control रेजिस्टर */
	u32	linkcr0;	/* link control 0 रेजिस्टर */
	u32	linkcr1;	/* link control 1 रेजिस्टर */
	u32	rsvd6[60];
	u32	mib0;		/* MIB0 counter रेजिस्टर */
	u32	usblink;	/* usb link control रेजिस्टर */
	u32	ltssmstate;	/* LTSSM state रेजिस्टर */
	u32	linkerrorcause;	/* link error cause रेजिस्टर */
	u32	rsvd7[60];
	u32	devaddrtiebrkr;	/* device address and tie अवरोधer */
	u32	itpinfo0;	/* ITP info 0 रेजिस्टर */
	u32	itpinfo1;	/* ITP info 1 रेजिस्टर */
	u32	rsvd8[61];
	काष्ठा epxcr	epcr[16];	/* ep control रेजिस्टर */
	u32	rsvd9[64];
	u32	phyaddr;	/* PHY address रेजिस्टर */
	u32	phydata;	/* PHY data रेजिस्टर */
पूर्ण;

/* Endpoपूर्णांक context काष्ठाure */
काष्ठा mv_u3d_ep_context अणु
	u32	rsvd0;
	u32	rsvd1;
	u32	trb_addr_lo;		/* TRB address low 32 bit */
	u32	trb_addr_hi;		/* TRB address high 32 bit */
	u32	rsvd2;
	u32	rsvd3;
	काष्ठा usb_ctrlrequest setup_buffer;	/* setup data buffer */
पूर्ण;

/* TRB control data काष्ठाure */
काष्ठा mv_u3d_trb_ctrl अणु
	u32	own:1;		/* owner of TRB */
	u32	rsvd1:3;
	u32	chain:1;	/* associate this TRB with the
				next TRB on the Ring */
	u32	ioc:1;		/* पूर्णांकerrupt on complete */
	u32	rsvd2:4;
	u32	type:6;		/* TRB type */
#घोषणा TYPE_NORMAL	1
#घोषणा TYPE_DATA	3
#घोषणा TYPE_LINK	6
	u32	dir:1;		/* Working at data stage of control endpoपूर्णांक
				operation. 0 is OUT and 1 is IN. */
	u32	rsvd3:15;
पूर्ण;

/* TRB data काष्ठाure
 * For multiple TRB, all the TRBs' physical address should be continuous.
 */
काष्ठा mv_u3d_trb_hw अणु
	u32	buf_addr_lo;	/* data buffer address low 32 bit */
	u32	buf_addr_hi;	/* data buffer address high 32 bit */
	u32	trb_len;	/* transfer length */
	काष्ठा mv_u3d_trb_ctrl	ctrl;	/* TRB control data */
पूर्ण;

/* TRB काष्ठाure */
काष्ठा mv_u3d_trb अणु
	काष्ठा mv_u3d_trb_hw *trb_hw;	/* poपूर्णांक to the trb_hw काष्ठाure */
	dma_addr_t trb_dma;		/* dma address क्रम this trb_hw */
	काष्ठा list_head trb_list;	/* trb list */
पूर्ण;

/* device data काष्ठाure */
काष्ठा mv_u3d अणु
	काष्ठा usb_gadget		gadget;
	काष्ठा usb_gadget_driver	*driver;
	spinlock_t			lock;	/* device lock */
	काष्ठा completion		*करोne;
	काष्ठा device			*dev;
	पूर्णांक				irq;

	/* usb controller रेजिस्टरs */
	काष्ठा mv_u3d_cap_regs __iomem	*cap_regs;
	काष्ठा mv_u3d_op_regs __iomem	*op_regs;
	काष्ठा mv_u3d_vuc_regs __iomem	*vuc_regs;
	व्योम __iomem			*phy_regs;

	अचिन्हित पूर्णांक			max_eps;
	काष्ठा mv_u3d_ep_context	*ep_context;
	माप_प्रकार				ep_context_size;
	dma_addr_t			ep_context_dma;

	काष्ठा dma_pool			*trb_pool; /* क्रम TRB data काष्ठाure */
	काष्ठा mv_u3d_ep		*eps;

	काष्ठा mv_u3d_req		*status_req; /* ep0 status request */
	काष्ठा usb_ctrlrequest		local_setup_buff; /* store setup data*/

	अचिन्हित पूर्णांक		resume_state;	/* USB state to resume */
	अचिन्हित पूर्णांक		usb_state;	/* USB current state */
	अचिन्हित पूर्णांक		ep0_state;	/* Endpoपूर्णांक zero state */
	अचिन्हित पूर्णांक		ep0_dir;

	अचिन्हित पूर्णांक		dev_addr;	/* device address */

	अचिन्हित पूर्णांक		errors;

	अचिन्हित		softconnect:1;
	अचिन्हित		vbus_active:1;	/* vbus is active or not */
	अचिन्हित		remote_wakeup:1; /* support remote wakeup */
	अचिन्हित		घड़ी_gating:1;	/* घड़ी gating or not */
	अचिन्हित		active:1;	/* udc is active or not */
	अचिन्हित		vbus_valid_detect:1; /* udc vbus detection */

	काष्ठा mv_usb_adकरोn_irq *vbus;
	अचिन्हित पूर्णांक		घातer;

	काष्ठा clk		*clk;
पूर्ण;

/* endpoपूर्णांक data काष्ठाure */
काष्ठा mv_u3d_ep अणु
	काष्ठा usb_ep		ep;
	काष्ठा mv_u3d		*u3d;
	काष्ठा list_head	queue;	/* ep request queued hardware */
	काष्ठा list_head	req_list; /* list of ep request */
	काष्ठा mv_u3d_ep_context	*ep_context; /* ep context */
	u32			direction;
	अक्षर			name[14];
	u32			processing; /* there is ep request
						queued on haredware */
	spinlock_t		req_lock; /* ep lock */
	अचिन्हित		wedge:1;
	अचिन्हित		enabled:1;
	अचिन्हित		ep_type:2;
	अचिन्हित		ep_num:8;
पूर्ण;

/* request data काष्ठाure */
काष्ठा mv_u3d_req अणु
	काष्ठा usb_request	req;
	काष्ठा mv_u3d_ep	*ep;
	काष्ठा list_head	queue;	/* ep requst queued on hardware */
	काष्ठा list_head	list;	/* ep request list */
	काष्ठा list_head	trb_list; /* trb list of a request */

	काष्ठा mv_u3d_trb	*trb_head; /* poपूर्णांक to first trb of a request */
	अचिन्हित		trb_count; /* TRB number in the chain */
	अचिन्हित		chain;	   /* TRB chain or not */
पूर्ण;

#पूर्ण_अगर
