<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * drivers/usb/gadget/qe_udc.h
 *
 * Copyright (C) 2006-2008 Freescale Semiconductor, Inc. All rights reserved.
 *
 * 	Xiaobo Xie <X.Xie@मुक्तscale.com>
 * 	Li Yang <leoli@मुक्तscale.com>
 *
 * Description:
 * Freescale USB device/endpoपूर्णांक management रेजिस्टरs
 */

#अगर_अघोषित __FSL_QE_UDC_H
#घोषणा __FSL_QE_UDC_H

/* SoC type */
#घोषणा PORT_CPM	0
#घोषणा PORT_QE		1

#घोषणा USB_MAX_ENDPOINTS               4
#घोषणा USB_MAX_PIPES                   USB_MAX_ENDPOINTS
#घोषणा USB_EP0_MAX_SIZE		64
#घोषणा USB_MAX_CTRL_PAYLOAD            0x4000
#घोषणा USB_BDRING_LEN			16
#घोषणा USB_BDRING_LEN_RX		256
#घोषणा USB_BDRING_LEN_TX		16
#घोषणा MIN_EMPTY_BDS			128
#घोषणा MAX_DATA_BDS			8
#घोषणा USB_CRC_SIZE			2
#घोषणा USB_सूची_BOTH			0x88
#घोषणा R_BUF_MAXSIZE			0x800
#घोषणा USB_EP_PARA_ALIGNMENT		32

/* USB Mode Register bit define */
#घोषणा USB_MODE_EN		0x01
#घोषणा USB_MODE_HOST		0x02
#घोषणा USB_MODE_TEST		0x04
#घोषणा USB_MODE_SFTE		0x08
#घोषणा USB_MODE_RESUME		0x40
#घोषणा USB_MODE_LSS		0x80

/* USB Slave Address Register Mask */
#घोषणा USB_SLVADDR_MASK	0x7F

/* USB Endpoपूर्णांक रेजिस्टर define */
#घोषणा USB_EPNUM_MASK		0xF000
#घोषणा USB_EPNUM_SHIFT		12

#घोषणा USB_TRANS_MODE_SHIFT	8
#घोषणा USB_TRANS_CTR		0x0000
#घोषणा USB_TRANS_INT		0x0100
#घोषणा USB_TRANS_BULK		0x0200
#घोषणा USB_TRANS_ISO		0x0300

#घोषणा USB_EP_MF		0x0020
#घोषणा USB_EP_RTE		0x0010

#घोषणा USB_THS_SHIFT		2
#घोषणा USB_THS_MASK		0x000c
#घोषणा USB_THS_NORMAL		0x0
#घोषणा USB_THS_IGNORE_IN	0x0004
#घोषणा USB_THS_NACK		0x0008
#घोषणा USB_THS_STALL		0x000c

#घोषणा USB_RHS_SHIFT   	0
#घोषणा USB_RHS_MASK		0x0003
#घोषणा USB_RHS_NORMAL  	0x0
#घोषणा USB_RHS_IGNORE_OUT	0x0001
#घोषणा USB_RHS_NACK		0x0002
#घोषणा USB_RHS_STALL		0x0003

#घोषणा USB_RTHS_MASK		0x000f

/* USB Command Register define */
#घोषणा USB_CMD_STR_FIFO	0x80
#घोषणा USB_CMD_FLUSH_FIFO	0x40
#घोषणा USB_CMD_ISFT		0x20
#घोषणा USB_CMD_DSFT		0x10
#घोषणा USB_CMD_EP_MASK		0x03

/* USB Event and Mask Register define */
#घोषणा USB_E_MSF_MASK		0x0800
#घोषणा USB_E_SFT_MASK		0x0400
#घोषणा USB_E_RESET_MASK	0x0200
#घोषणा USB_E_IDLE_MASK		0x0100
#घोषणा USB_E_TXE4_MASK		0x0080
#घोषणा USB_E_TXE3_MASK		0x0040
#घोषणा USB_E_TXE2_MASK		0x0020
#घोषणा USB_E_TXE1_MASK		0x0010
#घोषणा USB_E_SOF_MASK		0x0008
#घोषणा USB_E_BSY_MASK		0x0004
#घोषणा USB_E_TXB_MASK		0x0002
#घोषणा USB_E_RXB_MASK		0x0001
#घोषणा USBER_ALL_CLEAR 	0x0fff

#घोषणा USB_E_DEFAULT_DEVICE   (USB_E_RESET_MASK | USB_E_TXE4_MASK | \
				USB_E_TXE3_MASK | USB_E_TXE2_MASK | \
				USB_E_TXE1_MASK | USB_E_BSY_MASK | \
				USB_E_TXB_MASK | USB_E_RXB_MASK)

#घोषणा USB_E_TXE_MASK         (USB_E_TXE4_MASK | USB_E_TXE3_MASK|\
				 USB_E_TXE2_MASK | USB_E_TXE1_MASK)
/* USB Status Register define */
#घोषणा USB_IDLE_STATUS_MASK	0x01

/* USB Start of Frame Timer */
#घोषणा USB_USSFT_MASK		0x3FFF

/* USB Frame Number Register */
#घोषणा USB_USFRN_MASK		0xFFFF

काष्ठा usb_device_paraअणु
	u16	epptr[4];
	u32	rstate;
	u32	rptr;
	u16	frame_n;
	u16	rbcnt;
	u32	rtemp;
	u32	rxusb_data;
	u16	rxuptr;
	u8	reso[2];
	u32	softbl;
	u8	sofucrctemp;
पूर्ण;

काष्ठा usb_ep_paraअणु
	u16	rbase;
	u16	tbase;
	u8	rbmr;
	u8	tbmr;
	u16	mrblr;
	u16	rbptr;
	u16	tbptr;
	u32	tstate;
	u32	tptr;
	u16	tcrc;
	u16	tbcnt;
	u32	ttemp;
	u16	txusbu_ptr;
	u8	reserve[2];
पूर्ण;

#घोषणा USB_BUSMODE_GBL		0x20
#घोषणा USB_BUSMODE_BO_MASK	0x18
#घोषणा USB_BUSMODE_BO_SHIFT	0x3
#घोषणा USB_BUSMODE_BE		0x2
#घोषणा USB_BUSMODE_CETM	0x04
#घोषणा USB_BUSMODE_DTB		0x02

/* Endpoपूर्णांक basic handle */
#घोषणा ep_index(EP)		((EP)->ep.desc->bEndpoपूर्णांकAddress & 0xF)
#घोषणा ep_maxpacket(EP)	((EP)->ep.maxpacket)
#घोषणा ep_is_in(EP)	((ep_index(EP) == 0) ? (EP->udc->ep0_dir == \
			USB_सूची_IN) : ((EP)->ep.desc->bEndpoपूर्णांकAddress \
			& USB_सूची_IN) == USB_सूची_IN)

/* ep0 transfer state */
#घोषणा WAIT_FOR_SETUP          0
#घोषणा DATA_STATE_XMIT         1
#घोषणा DATA_STATE_NEED_ZLP     2
#घोषणा WAIT_FOR_OUT_STATUS     3
#घोषणा DATA_STATE_RECV         4

/* ep tramsfer mode */
#घोषणा USBP_TM_CTL	0
#घोषणा USBP_TM_ISO	1
#घोषणा USBP_TM_BULK	2
#घोषणा USBP_TM_INT	3

/*-----------------------------------------------------------------------------
	USB RX And TX DATA Frame
 -----------------------------------------------------------------------------*/
काष्ठा qe_frameअणु
	u8 *data;
	u32 len;
	u32 status;
	u32 info;

	व्योम *privdata;
	काष्ठा list_head node;
पूर्ण;

/* Frame काष्ठाure, info field. */
#घोषणा PID_DATA0              0x80000000 /* Data toggle zero */
#घोषणा PID_DATA1              0x40000000 /* Data toggle one  */
#घोषणा PID_SETUP              0x20000000 /* setup bit */
#घोषणा SETUP_STATUS           0x10000000 /* setup status bit */
#घोषणा SETADDR_STATUS         0x08000000 /* setupup address status bit */
#घोषणा NO_REQ                 0x04000000 /* Frame without request */
#घोषणा HOST_DATA              0x02000000 /* Host data frame */
#घोषणा FIRST_PACKET_IN_FRAME  0x01000000 /* first packet in the frame */
#घोषणा TOKEN_FRAME            0x00800000 /* Host token frame */
#घोषणा ZLP                    0x00400000 /* Zero length packet */
#घोषणा IN_TOKEN_FRAME         0x00200000 /* In token package */
#घोषणा OUT_TOKEN_FRAME        0x00100000 /* Out token package */
#घोषणा SETUP_TOKEN_FRAME      0x00080000 /* Setup token package */
#घोषणा STALL_FRAME            0x00040000 /* Stall handshake */
#घोषणा NACK_FRAME             0x00020000 /* Nack handshake */
#घोषणा NO_PID                 0x00010000 /* No send PID */
#घोषणा NO_CRC                 0x00008000 /* No send CRC */
#घोषणा HOST_COMMAND           0x00004000 /* Host command frame   */

/* Frame status field */
/* Receive side */
#घोषणा FRAME_OK               0x00000000 /* Frame transmitted or received OK */
#घोषणा FRAME_ERROR            0x80000000 /* Error occurred on frame */
#घोषणा START_FRAME_LOST       0x40000000 /* START_FRAME_LOST */
#घोषणा END_FRAME_LOST         0x20000000 /* END_FRAME_LOST */
#घोषणा RX_ER_NONOCT           0x10000000 /* Rx Non Octet Aligned Packet */
#घोषणा RX_ER_BITSTUFF         0x08000000 /* Frame Aborted --Received packet
					     with bit stuff error */
#घोषणा RX_ER_CRC              0x04000000 /* Received packet with CRC error */
#घोषणा RX_ER_OVERUN           0x02000000 /* Over-run occurred on reception */
#घोषणा RX_ER_PID              0x01000000 /* Wrong PID received */
/* Tranmit side */
#घोषणा TX_ER_NAK              0x00800000 /* Received NAK handshake */
#घोषणा TX_ER_STALL            0x00400000 /* Received STALL handshake */
#घोषणा TX_ER_TIMEOUT          0x00200000 /* Transmit समय out */
#घोषणा TX_ER_UNDERUN          0x00100000 /* Transmit underrun */
#घोषणा FRAME_INPROGRESS       0x00080000 /* Frame is being transmitted */
#घोषणा ER_DATA_UNDERUN        0x00040000 /* Frame is लघुer then expected */
#घोषणा ER_DATA_OVERUN         0x00020000 /* Frame is दीर्घer then expected */

/* QE USB frame operation functions */
#घोषणा frame_get_length(frm) (frm->len)
#घोषणा frame_set_length(frm, leng) (frm->len = leng)
#घोषणा frame_get_data(frm) (frm->data)
#घोषणा frame_set_data(frm, dat) (frm->data = dat)
#घोषणा frame_get_info(frm) (frm->info)
#घोषणा frame_set_info(frm, inf) (frm->info = inf)
#घोषणा frame_get_status(frm) (frm->status)
#घोषणा frame_set_status(frm, stat) (frm->status = stat)
#घोषणा frame_get_privdata(frm) (frm->privdata)
#घोषणा frame_set_privdata(frm, dat) (frm->privdata = dat)

अटल अंतरभूत व्योम qe_frame_clean(काष्ठा qe_frame *frm)
अणु
	frame_set_data(frm, शून्य);
	frame_set_length(frm, 0);
	frame_set_status(frm, FRAME_OK);
	frame_set_info(frm, 0);
	frame_set_privdata(frm, शून्य);
पूर्ण

अटल अंतरभूत व्योम qe_frame_init(काष्ठा qe_frame *frm)
अणु
	qe_frame_clean(frm);
	INIT_LIST_HEAD(&(frm->node));
पूर्ण

काष्ठा qe_req अणु
	काष्ठा usb_request req;
	काष्ठा list_head queue;
	/* ep_queue() func will add
	 a request->queue पूर्णांकo a udc_ep->queue 'd tail */
	काष्ठा qe_ep *ep;
	अचिन्हित mapped:1;
पूर्ण;

काष्ठा qe_ep अणु
	काष्ठा usb_ep ep;
	काष्ठा list_head queue;
	काष्ठा qe_udc *udc;
	काष्ठा usb_gadget *gadget;

	u8 state;

	काष्ठा qe_bd __iomem *rxbase;
	काष्ठा qe_bd __iomem *n_rxbd;
	काष्ठा qe_bd __iomem *e_rxbd;

	काष्ठा qe_bd __iomem *txbase;
	काष्ठा qe_bd __iomem *n_txbd;
	काष्ठा qe_bd __iomem *c_txbd;

	काष्ठा qe_frame *rxframe;
	u8 *rxbuffer;
	dma_addr_t rxbuf_d;
	u8 rxbufmap;
	अचिन्हित अक्षर localnack;
	पूर्णांक has_data;

	काष्ठा qe_frame *txframe;
	काष्ठा qe_req *tx_req;
	पूर्णांक sent;  /*data alपढ़ोy sent */
	पूर्णांक last;  /*data sent in the last समय*/

	u8 dir;
	u8 epnum;
	u8 पंचांग; /* transfer mode */
	u8 data01;
	u8 init;

	u8 alपढ़ोy_seen;
	u8 enable_tasklet;
	u8 setup_stage;
	u32 last_io;            /* बारtamp */

	अक्षर name[14];

	अचिन्हित द्विगुन_buf:1;
	अचिन्हित stopped:1;
	अचिन्हित fnf:1;
	अचिन्हित has_dma:1;

	u8 ackरुको;
	u8 dma_channel;
	u16 dma_counter;
	पूर्णांक lch;

	काष्ठा समयr_list समयr;
पूर्ण;

काष्ठा qe_udc अणु
	काष्ठा usb_gadget gadget;
	काष्ठा usb_gadget_driver *driver;
	काष्ठा device *dev;
	काष्ठा qe_ep eps[USB_MAX_ENDPOINTS];
	काष्ठा usb_ctrlrequest local_setup_buff;
	spinlock_t lock;	/* lock क्रम set/config qe_udc */
	अचिन्हित दीर्घ soc_type;		/* QE or CPM soc */

	काष्ठा qe_req *status_req;	/* ep0 status request */

	/* USB and EP Parameter Block poपूर्णांकer */
	काष्ठा usb_device_para __iomem *usb_param;
	काष्ठा usb_ep_para __iomem *ep_param[4];

	u32 max_pipes;          /* Device max pipes */
	u32 max_use_endpts;     /* Max endpoपूर्णांकes to be used */
	u32 bus_reset;          /* Device is bus reseting */
	u32 resume_state;       /* USB state to resume*/
	u32 usb_state;          /* USB current state */
	u32 usb_next_state;     /* USB next state */
	u32 ep0_state;          /* Endpoपूर्णांक zero state */
	u32 ep0_dir;            /* Endpoपूर्णांक zero direction: can be
				USB_सूची_IN or USB_सूची_OUT*/
	u32 usb_sof_count;      /* SOF count */
	u32 errors;             /* USB ERRORs count */

	u8 *पंचांगpbuf;
	u32 c_start;
	u32 c_end;

	u8 *nullbuf;
	u8 *statusbuf;
	dma_addr_t nullp;
	u8 nullmap;
	u8 device_address;	/* Device USB address */

	अचिन्हित पूर्णांक usb_घड़ी;
	अचिन्हित पूर्णांक usb_irq;
	काष्ठा usb_ctlr __iomem *usb_regs;

	काष्ठा tasklet_काष्ठा rx_tasklet;

	काष्ठा completion *करोne;	/* to make sure release() is करोne */
पूर्ण;

#घोषणा EP_STATE_IDLE	0
#घोषणा EP_STATE_NACK	1
#घोषणा EP_STATE_STALL	2

/*
 * transmit BD's status
 */
#घोषणा T_R           0x80000000         /* पढ़ोy bit */
#घोषणा T_W           0x20000000         /* wrap bit */
#घोषणा T_I           0x10000000         /* पूर्णांकerrupt on completion */
#घोषणा T_L           0x08000000         /* last */
#घोषणा T_TC          0x04000000         /* transmit CRC */
#घोषणा T_CNF         0x02000000         /* रुको क्रम  transmit confirm */
#घोषणा T_LSP         0x01000000         /* Low-speed transaction */
#घोषणा T_PID         0x00c00000         /* packet id */
#घोषणा T_NAK         0x00100000         /* No ack. */
#घोषणा T_STAL        0x00080000         /* Stall received */
#घोषणा T_TO          0x00040000         /* समय out */
#घोषणा T_UN          0x00020000         /* underrun */

#घोषणा DEVICE_T_ERROR    (T_UN | T_TO)
#घोषणा HOST_T_ERROR      (T_UN | T_TO | T_NAK | T_STAL)
#घोषणा DEVICE_T_BD_MASK  DEVICE_T_ERROR
#घोषणा HOST_T_BD_MASK    HOST_T_ERROR

#घोषणा T_PID_SHIFT   6
#घोषणा T_PID_DATA0   0x00800000         /* Data 0 toggle */
#घोषणा T_PID_DATA1   0x00c00000         /* Data 1 toggle */

/*
 * receive BD's status
 */
#घोषणा R_E           0x80000000         /* buffer empty */
#घोषणा R_W           0x20000000         /* wrap bit */
#घोषणा R_I           0x10000000         /* पूर्णांकerrupt on reception */
#घोषणा R_L           0x08000000         /* last */
#घोषणा R_F           0x04000000         /* first */
#घोषणा R_PID         0x00c00000         /* packet id */
#घोषणा R_NO          0x00100000         /* Rx Non Octet Aligned Packet */
#घोषणा R_AB          0x00080000         /* Frame Aborted */
#घोषणा R_CR          0x00040000         /* CRC Error */
#घोषणा R_OV          0x00020000         /* Overrun */

#घोषणा R_ERROR       (R_NO | R_AB | R_CR | R_OV)
#घोषणा R_BD_MASK     R_ERROR

#घोषणा R_PID_DATA0   0x00000000
#घोषणा R_PID_DATA1   0x00400000
#घोषणा R_PID_SETUP   0x00800000

#घोषणा CPM_USB_STOP_TX 0x2e600000
#घोषणा CPM_USB_RESTART_TX 0x2e600000
#घोषणा CPM_USB_STOP_TX_OPCODE 0x0a
#घोषणा CPM_USB_RESTART_TX_OPCODE 0x0b
#घोषणा CPM_USB_EP_SHIFT 5

#पूर्ण_अगर  /* __FSL_QE_UDC_H */
