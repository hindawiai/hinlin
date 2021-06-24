<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Freescale QUICC Engine USB Host Controller Driver
 *
 * Copyright (c) Freescale Semicondutor, Inc. 2006.
 *               Shlomi Gridish <gridish@मुक्तscale.com>
 *               Jerry Huang <Chang-Ming.Huang@मुक्तscale.com>
 * Copyright (c) Logic Product Development, Inc. 2007
 *               Peter Barada <peterb@logicpd.com>
 * Copyright (c) MontaVista Software, Inc. 2008.
 *               Anton Vorontsov <avorontsov@ru.mvista.com>
 */

#अगर_अघोषित __FHCI_H
#घोषणा __FHCI_H

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/bug.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kfअगरo.h>
#समावेश <linux/पन.स>
#समावेश <linux/usb.h>
#समावेश <linux/usb/hcd.h>
#समावेश <soc/fsl/qe/qe.h>
#समावेश <soc/fsl/qe/immap_qe.h>

#घोषणा USB_CLOCK	48000000

#घोषणा FHCI_PRAM_SIZE 0x100

#घोषणा MAX_EDS		32
#घोषणा MAX_TDS		32


/* CRC16 field size */
#घोषणा CRC_SIZE 2

/* USB protocol overhead क्रम each frame transmitted from the host */
#घोषणा PROTOCOL_OVERHEAD 7

/* Packet काष्ठाure, info field */
#घोषणा PKT_PID_DATA0		0x80000000 /* PID - Data toggle zero */
#घोषणा PKT_PID_DATA1		0x40000000 /* PID - Data toggle one  */
#घोषणा PKT_PID_SETUP		0x20000000 /* PID - Setup bit */
#घोषणा PKT_SETUP_STATUS	0x10000000 /* Setup status bit */
#घोषणा PKT_SETADDR_STATUS	0x08000000 /* Set address status bit */
#घोषणा PKT_SET_HOST_LAST	0x04000000 /* Last data packet */
#घोषणा PKT_HOST_DATA		0x02000000 /* Data packet */
#घोषणा PKT_FIRST_IN_FRAME	0x01000000 /* First packet in the frame */
#घोषणा PKT_TOKEN_FRAME		0x00800000 /* Token packet */
#घोषणा PKT_ZLP			0x00400000 /* Zero length packet */
#घोषणा PKT_IN_TOKEN_FRAME	0x00200000 /* IN token packet */
#घोषणा PKT_OUT_TOKEN_FRAME	0x00100000 /* OUT token packet */
#घोषणा PKT_SETUP_TOKEN_FRAME	0x00080000 /* SETUP token packet */
#घोषणा PKT_STALL_FRAME		0x00040000 /* STALL packet */
#घोषणा PKT_NACK_FRAME		0x00020000 /* NACK packet */
#घोषणा PKT_NO_PID		0x00010000 /* No PID */
#घोषणा PKT_NO_CRC		0x00008000 /* करोn't append CRC */
#घोषणा PKT_HOST_COMMAND	0x00004000 /* Host command packet */
#घोषणा PKT_DUMMY_PACKET	0x00002000 /* Dummy packet, used क्रम mmm */
#घोषणा PKT_LOW_SPEED_PACKET	0x00001000 /* Low-Speed packet */

#घोषणा TRANS_OK		(0)
#घोषणा TRANS_INPROGRESS	(-1)
#घोषणा TRANS_DISCARD		(-2)
#घोषणा TRANS_FAIL		(-3)

#घोषणा PS_INT		0
#घोषणा PS_DISCONNECTED	1
#घोषणा PS_CONNECTED	2
#घोषणा PS_READY	3
#घोषणा PS_MISSING	4

/* Transfer Descriptor status field */
#घोषणा USB_TD_OK		0x00000000 /* TD transmited or received ok */
#घोषणा USB_TD_INPROGRESS	0x80000000 /* TD is being transmitted */
#घोषणा USB_TD_RX_ER_NONOCT	0x40000000 /* Tx Non Octet Aligned Packet */
#घोषणा USB_TD_RX_ER_BITSTUFF	0x20000000 /* Frame Aborted-Received pkt */
#घोषणा USB_TD_RX_ER_CRC	0x10000000 /* CRC error */
#घोषणा USB_TD_RX_ER_OVERUN	0x08000000 /* Over - run occurred */
#घोषणा USB_TD_RX_ER_PID	0x04000000 /* wrong PID received */
#घोषणा USB_TD_RX_DATA_UNDERUN	0x02000000 /* लघुer than expected */
#घोषणा USB_TD_RX_DATA_OVERUN	0x01000000 /* दीर्घer than expected */
#घोषणा USB_TD_TX_ER_NAK	0x00800000 /* NAK handshake */
#घोषणा USB_TD_TX_ER_STALL	0x00400000 /* STALL handshake */
#घोषणा USB_TD_TX_ER_TIMEOUT	0x00200000 /* transmit समय out */
#घोषणा USB_TD_TX_ER_UNDERUN	0x00100000 /* transmit underrun */

#घोषणा USB_TD_ERROR (USB_TD_RX_ER_NONOCT | USB_TD_RX_ER_BITSTUFF | \
		USB_TD_RX_ER_CRC | USB_TD_RX_ER_OVERUN | USB_TD_RX_ER_PID | \
		USB_TD_RX_DATA_UNDERUN | USB_TD_RX_DATA_OVERUN | \
		USB_TD_TX_ER_NAK | USB_TD_TX_ER_STALL | \
		USB_TD_TX_ER_TIMEOUT | USB_TD_TX_ER_UNDERUN)

/* Transfer Descriptor toggle field */
#घोषणा USB_TD_TOGGLE_DATA0	0
#घोषणा USB_TD_TOGGLE_DATA1	1
#घोषणा USB_TD_TOGGLE_CARRY	2

/* #घोषणा MULTI_DATA_BUS */

/* Bus mode रेजिस्टर RBMR/TBMR */
#घोषणा BUS_MODE_GBL	0x20	/* Global snooping */
#घोषणा BUS_MODE_BO	0x18	/* Byte ordering */
#घोषणा BUS_MODE_BO_BE	0x10	/* Byte ordering - Big-endian */
#घोषणा BUS_MODE_DTB	0x02	/* Data bus */

/* FHCI QE USB Register Description */

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

/* Freescale USB HOST */
काष्ठा fhci_pram अणु
	__be16 ep_ptr[4];	/* Endpoपूर्णांक porter reg */
	__be32 rx_state;	/* Rx पूर्णांकernal state */
	__be32 rx_ptr;		/* Rx पूर्णांकernal data poपूर्णांकer */
	__be16 frame_num;	/* Frame number */
	__be16 rx_cnt;		/* Rx byte count */
	__be32 rx_temp;		/* Rx temp */
	__be32 rx_data_temp;	/* Rx data temp */
	__be16 rx_u_ptr;	/* Rx microcode वापस address temp */
	u8 reserved1[2];	/* reserved area */
	__be32 sof_tbl;		/* SOF lookup table poपूर्णांकer */
	u8 sof_u_crc_temp;	/* SOF micorcode CRC5 temp reg */
	u8 reserved2[0xdb];
पूर्ण;

/* Freescale USB Endpoपूर्णांक*/
काष्ठा fhci_ep_pram अणु
	__be16 rx_base;		/* Rx BD base address */
	__be16 tx_base;		/* Tx BD base address */
	u8 rx_func_code;	/* Rx function code */
	u8 tx_func_code;	/* Tx function code */
	__be16 rx_buff_len;	/* Rx buffer length */
	__be16 rx_bd_ptr;	/* Rx BD poपूर्णांकer */
	__be16 tx_bd_ptr;	/* Tx BD poपूर्णांकer */
	__be32 tx_state;	/* Tx पूर्णांकernal state */
	__be32 tx_ptr;		/* Tx पूर्णांकernal data poपूर्णांकer */
	__be16 tx_crc;		/* temp transmit CRC */
	__be16 tx_cnt;		/* Tx byte count */
	__be32 tx_temp;		/* Tx temp */
	__be16 tx_u_ptr;	/* Tx microcode वापस address temp */
	__be16 reserved;
पूर्ण;

काष्ठा fhci_controller_list अणु
	काष्ठा list_head ctrl_list;	/* control endpoपूर्णांकs */
	काष्ठा list_head bulk_list;	/* bulk endpoपूर्णांकs */
	काष्ठा list_head iso_list;	/* isochronous endpoपूर्णांकs */
	काष्ठा list_head पूर्णांकr_list;	/* पूर्णांकerruput endpoपूर्णांकs */
	काष्ठा list_head करोne_list;	/* करोne transfers */
पूर्ण;

काष्ठा भव_root_hub अणु
	पूर्णांक dev_num;	/* USB address of the root hub */
	u32 feature;	/* indicates what feature has been set */
	काष्ठा usb_hub_status hub;
	काष्ठा usb_port_status port;
पूर्ण;

क्रमागत fhci_gpios अणु
	GPIO_USBOE = 0,
	GPIO_USBTP,
	GPIO_USBTN,
	GPIO_USBRP,
	GPIO_USBRN,
	/* these are optional */
	GPIO_SPEED,
	GPIO_POWER,
	NUM_GPIOS,
पूर्ण;

क्रमागत fhci_pins अणु
	PIN_USBOE = 0,
	PIN_USBTP,
	PIN_USBTN,
	NUM_PINS,
पूर्ण;

काष्ठा fhci_hcd अणु
	क्रमागत qe_घड़ी fullspeed_clk;
	क्रमागत qe_घड़ी lowspeed_clk;
	काष्ठा qe_pin *pins[NUM_PINS];
	पूर्णांक gpios[NUM_GPIOS];
	bool alow_gpios[NUM_GPIOS];

	काष्ठा qe_usb_ctlr __iomem *regs; /* I/O memory used to communicate */
	काष्ठा fhci_pram __iomem *pram;	/* Parameter RAM */
	काष्ठा gपंचांग_समयr *समयr;

	spinlock_t lock;
	काष्ठा fhci_usb *usb_lld; /* Low-level driver */
	काष्ठा भव_root_hub *vroot_hub; /* the भव root hub */
	पूर्णांक active_urbs;
	काष्ठा fhci_controller_list *hc_list;
	काष्ठा tasklet_काष्ठा *process_करोne_task; /* tasklet क्रम करोne list */

	काष्ठा list_head empty_eds;
	काष्ठा list_head empty_tds;

#अगर_घोषित CONFIG_FHCI_DEBUG
	पूर्णांक usb_irq_stat[13];
	काष्ठा dentry *dfs_root;
#पूर्ण_अगर
पूर्ण;

#घोषणा USB_FRAME_USAGE 90
#घोषणा FRAME_TIME_USAGE (USB_FRAME_USAGE*10)	/* frame समय usage */
#घोषणा SW_FIX_TIME_BETWEEN_TRANSACTION 150	/* SW */
#घोषणा MAX_BYTES_PER_FRAME (USB_FRAME_USAGE*15)
#घोषणा MAX_PERIODIC_FRAME_USAGE 90

/* transaction type */
क्रमागत fhci_ta_type अणु
	FHCI_TA_IN = 0,	/* input transaction */
	FHCI_TA_OUT,	/* output transaction */
	FHCI_TA_SETUP,	/* setup transaction */
पूर्ण;

/* transfer mode */
क्रमागत fhci_tf_mode अणु
	FHCI_TF_CTRL = 0,
	FHCI_TF_ISO,
	FHCI_TF_BULK,
	FHCI_TF_INTR,
पूर्ण;

क्रमागत fhci_speed अणु
	FHCI_FULL_SPEED,
	FHCI_LOW_SPEED,
पूर्ण;

/* endpoपूर्णांक state */
क्रमागत fhci_ed_state अणु
	FHCI_ED_NEW = 0, /* pipe is new */
	FHCI_ED_OPER,    /* pipe is operating */
	FHCI_ED_URB_DEL, /* pipe is in hold because urb is being deleted */
	FHCI_ED_SKIP,    /* skip this pipe */
	FHCI_ED_HALTED,  /* pipe is halted */
पूर्ण;

क्रमागत fhci_port_status अणु
	FHCI_PORT_POWER_OFF = 0,
	FHCI_PORT_DISABLED,
	FHCI_PORT_DISCONNECTING,
	FHCI_PORT_WAITING,	/* रुकोing क्रम connection */
	FHCI_PORT_FULL,		/* full speed connected */
	FHCI_PORT_LOW,		/* low speed connected */
पूर्ण;

क्रमागत fhci_mem_alloc अणु
	MEM_CACHABLE_SYS = 0x00000001,	/* primary DDR,cachable */
	MEM_NOCACHE_SYS = 0x00000004,	/* primary DDR,non-cachable */
	MEM_SECONDARY = 0x00000002,	/* either secondary DDR or SDRAM */
	MEM_PRAM = 0x00000008,		/* multi-user RAM identअगरier */
पूर्ण;

/* USB शेष parameters*/
#घोषणा DEFAULT_RING_LEN	8
#घोषणा DEFAULT_DATA_MEM	MEM_CACHABLE_SYS

काष्ठा ed अणु
	u8 dev_addr;		/* device address */
	u8 ep_addr;		/* endpoपूर्णांक address */
	क्रमागत fhci_tf_mode mode;	/* USB transfer mode */
	क्रमागत fhci_speed speed;
	अचिन्हित पूर्णांक max_pkt_size;
	क्रमागत fhci_ed_state state;
	काष्ठा list_head td_list; /* a list of all queued TD to this pipe */
	काष्ठा list_head node;

	/* पढ़ो only parameters, should be cleared upon initialization */
	u8 toggle_carry;	/* toggle carry from the last TD submitted */
	u16 next_iso;		/* समय stamp of next queued ISO transfer */
	काष्ठा td *td_head;	/* a poपूर्णांकer to the current TD handled */
पूर्ण;

काष्ठा td अणु
	व्योम *data;		 /* a poपूर्णांकer to the data buffer */
	अचिन्हित पूर्णांक len;	 /* length of the data to be submitted */
	अचिन्हित पूर्णांक actual_len; /* actual bytes transferred on this td */
	क्रमागत fhci_ta_type type;	 /* transaction type */
	u8 toggle;		 /* toggle क्रम next trans. within this TD */
	u16 iso_index;		 /* ISO transaction index */
	u16 start_frame;	 /* start frame समय stamp */
	u16 पूर्णांकerval;		 /* पूर्णांकerval between trans. (क्रम ISO/Intr) */
	u32 status;		 /* status of the TD */
	काष्ठा ed *ed;		 /* a handle to the corresponding ED */
	काष्ठा urb *urb;	 /* a handle to the corresponding URB */
	bool ioc;		 /* Inक्रमm On Completion */
	काष्ठा list_head node;

	/* पढ़ो only parameters should be cleared upon initialization */
	काष्ठा packet *pkt;
	पूर्णांक nak_cnt;
	पूर्णांक error_cnt;
	काष्ठा list_head frame_lh;
पूर्ण;

काष्ठा packet अणु
	u8 *data;	/* packet data */
	u32 len;	/* packet length */
	u32 status;	/* status of the packet - equivalent to the status
			 * field क्रम the corresponding काष्ठाure td */
	u32 info;	/* packet inक्रमmation */
	व्योम __iomem *priv_data; /* निजी data of the driver (TDs or BDs) */
पूर्ण;

/* काष्ठा क्रम each URB */
#घोषणा URB_INPROGRESS	0
#घोषणा URB_DEL		1

/* URB states (state field) */
#घोषणा US_BULK		0
#घोषणा US_BULK0	1

/* three setup states */
#घोषणा US_CTRL_SETUP	2
#घोषणा US_CTRL_DATA	1
#घोषणा US_CTRL_ACK	0

#घोषणा EP_ZERO	0

काष्ठा urb_priv अणु
	पूर्णांक num_of_tds;
	पूर्णांक tds_cnt;
	पूर्णांक state;

	काष्ठा td **tds;
	काष्ठा ed *ed;
	काष्ठा समयr_list समय_out;
पूर्ण;

काष्ठा endpoपूर्णांक अणु
	/* Poपूर्णांकer to ep parameter RAM */
	काष्ठा fhci_ep_pram __iomem *ep_pram_ptr;

	/* Host transactions */
	काष्ठा usb_td __iomem *td_base; /* first TD in the ring */
	काष्ठा usb_td __iomem *conf_td; /* next TD क्रम confirm after transac */
	काष्ठा usb_td __iomem *empty_td;/* next TD क्रम new transaction req. */
	काष्ठा kfअगरo empty_frame_Q;  /* Empty frames list to use */
	काष्ठा kfअगरo conf_frame_Q;   /* frames passed to TDs,रुकोing क्रम tx */
	काष्ठा kfअगरo dummy_packets_Q;/* dummy packets क्रम the CRC overun */

	bool alपढ़ोy_pushed_dummy_bd;
पूर्ण;

/* काष्ठा क्रम each 1mSec frame समय */
#घोषणा FRAME_IS_TRANSMITTED		0x00
#घोषणा FRAME_TIMER_END_TRANSMISSION	0x01
#घोषणा FRAME_DATA_END_TRANSMISSION	0x02
#घोषणा FRAME_END_TRANSMISSION		0x03
#घोषणा FRAME_IS_PREPARED		0x04

काष्ठा fhci_समय_frame अणु
	u16 frame_num;	 /* frame number */
	u16 total_bytes; /* total bytes submitted within this frame */
	u8 frame_status; /* flag that indicates to stop fill this frame */
	काष्ठा list_head tds_list; /* all tds of this frame */
पूर्ण;

/* पूर्णांकernal driver काष्ठाure*/
काष्ठा fhci_usb अणु
	u16 saved_msk;		 /* saving of the USB mask रेजिस्टर */
	काष्ठा endpoपूर्णांक *ep0;	 /* poपूर्णांकer क्रम endpoपूर्णांक0 काष्ठाure */
	पूर्णांक पूर्णांकr_nesting_cnt;	 /* पूर्णांकerrupt nesting counter */
	u16 max_frame_usage;	 /* max frame समय usage,in micro-sec */
	u16 max_bytes_per_frame; /* max byte can be tx in one समय frame */
	u32 sw_transaction_समय; /* sw complete trans समय,in micro-sec */
	काष्ठा fhci_समय_frame *actual_frame;
	काष्ठा fhci_controller_list *hc_list;	/* मुख्य काष्ठाure क्रम hc */
	काष्ठा भव_root_hub *vroot_hub;
	क्रमागत fhci_port_status port_status;	/* v_rh port status */

	u32 (*transfer_confirm)(काष्ठा fhci_hcd *fhci);

	काष्ठा fhci_hcd *fhci;
पूर्ण;

/*
 * Various helpers and prototypes below.
 */

अटल अंतरभूत u16 get_frame_num(काष्ठा fhci_hcd *fhci)
अणु
	वापस in_be16(&fhci->pram->frame_num) & 0x07ff;
पूर्ण

#घोषणा fhci_dbg(fhci, fmt, args...) \
		dev_dbg(fhci_to_hcd(fhci)->self.controller, fmt, ##args)
#घोषणा fhci_vdbg(fhci, fmt, args...) \
		dev_vdbg(fhci_to_hcd(fhci)->self.controller, fmt, ##args)
#घोषणा fhci_err(fhci, fmt, args...) \
		dev_err(fhci_to_hcd(fhci)->self.controller, fmt, ##args)
#घोषणा fhci_info(fhci, fmt, args...) \
		dev_info(fhci_to_hcd(fhci)->self.controller, fmt, ##args)
#घोषणा fhci_warn(fhci, fmt, args...) \
		dev_warn(fhci_to_hcd(fhci)->self.controller, fmt, ##args)

अटल अंतरभूत काष्ठा fhci_hcd *hcd_to_fhci(काष्ठा usb_hcd *hcd)
अणु
	वापस (काष्ठा fhci_hcd *)hcd->hcd_priv;
पूर्ण

अटल अंतरभूत काष्ठा usb_hcd *fhci_to_hcd(काष्ठा fhci_hcd *fhci)
अणु
	वापस container_of((व्योम *)fhci, काष्ठा usb_hcd, hcd_priv);
पूर्ण

/* fअगरo of poपूर्णांकers */
अटल अंतरभूत पूर्णांक cq_new(काष्ठा kfअगरo *fअगरo, पूर्णांक size)
अणु
	वापस kfअगरo_alloc(fअगरo, size * माप(व्योम *), GFP_KERNEL);
पूर्ण

अटल अंतरभूत व्योम cq_delete(काष्ठा kfअगरo *kfअगरo)
अणु
	kfअगरo_मुक्त(kfअगरo);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक cq_howmany(काष्ठा kfअगरo *kfअगरo)
अणु
	वापस kfअगरo_len(kfअगरo) / माप(व्योम *);
पूर्ण

अटल अंतरभूत पूर्णांक cq_put(काष्ठा kfअगरo *kfअगरo, व्योम *p)
अणु
	वापस kfअगरo_in(kfअगरo, (व्योम *)&p, माप(p));
पूर्ण

अटल अंतरभूत व्योम *cq_get(काष्ठा kfअगरo *kfअगरo)
अणु
	अचिन्हित पूर्णांक sz;
	व्योम *p;

	sz = kfअगरo_out(kfअगरo, (व्योम *)&p, माप(p));
	अगर (sz != माप(p))
		वापस शून्य;

	वापस p;
पूर्ण

/* fhci-hcd.c */
व्योम fhci_start_sof_समयr(काष्ठा fhci_hcd *fhci);
व्योम fhci_stop_sof_समयr(काष्ठा fhci_hcd *fhci);
u16 fhci_get_sof_समयr_count(काष्ठा fhci_usb *usb);
व्योम fhci_usb_enable_पूर्णांकerrupt(काष्ठा fhci_usb *usb);
व्योम fhci_usb_disable_पूर्णांकerrupt(काष्ठा fhci_usb *usb);
पूर्णांक fhci_ioports_check_bus_state(काष्ठा fhci_hcd *fhci);

/* fhci-mem.c */
व्योम fhci_recycle_empty_td(काष्ठा fhci_hcd *fhci, काष्ठा td *td);
व्योम fhci_recycle_empty_ed(काष्ठा fhci_hcd *fhci, काष्ठा ed *ed);
काष्ठा ed *fhci_get_empty_ed(काष्ठा fhci_hcd *fhci);
काष्ठा td *fhci_td_fill(काष्ठा fhci_hcd *fhci, काष्ठा urb *urb,
			काष्ठा urb_priv *urb_priv, काष्ठा ed *ed, u16 index,
			क्रमागत fhci_ta_type type, पूर्णांक toggle, u8 *data, u32 len,
			u16 पूर्णांकerval, u16 start_frame, bool ioc);
व्योम fhci_add_tds_to_ed(काष्ठा ed *ed, काष्ठा td **td_list, पूर्णांक number);

/* fhci-hub.c */
व्योम fhci_config_transceiver(काष्ठा fhci_hcd *fhci,
			क्रमागत fhci_port_status status);
व्योम fhci_port_disable(काष्ठा fhci_hcd *fhci);
व्योम fhci_port_enable(व्योम *lld);
व्योम fhci_io_port_generate_reset(काष्ठा fhci_hcd *fhci);
व्योम fhci_port_reset(व्योम *lld);
पूर्णांक fhci_hub_status_data(काष्ठा usb_hcd *hcd, अक्षर *buf);
पूर्णांक fhci_hub_control(काष्ठा usb_hcd *hcd, u16 typeReq, u16 wValue,
		     u16 wIndex, अक्षर *buf, u16 wLength);

/* fhci-tds.c */
व्योम fhci_flush_bds(काष्ठा fhci_usb *usb);
व्योम fhci_flush_actual_frame(काष्ठा fhci_usb *usb);
u32 fhci_host_transaction(काष्ठा fhci_usb *usb, काष्ठा packet *pkt,
			  क्रमागत fhci_ta_type trans_type, u8 dest_addr,
			  u8 dest_ep, क्रमागत fhci_tf_mode trans_mode,
			  क्रमागत fhci_speed dest_speed, u8 data_toggle);
व्योम fhci_host_transmit_actual_frame(काष्ठा fhci_usb *usb);
व्योम fhci_tx_conf_पूर्णांकerrupt(काष्ठा fhci_usb *usb);
व्योम fhci_push_dummy_bd(काष्ठा endpoपूर्णांक *ep);
u32 fhci_create_ep(काष्ठा fhci_usb *usb, क्रमागत fhci_mem_alloc data_mem,
		   u32 ring_len);
व्योम fhci_init_ep_रेजिस्टरs(काष्ठा fhci_usb *usb,
			    काष्ठा endpoपूर्णांक *ep,
			    क्रमागत fhci_mem_alloc data_mem);
व्योम fhci_ep0_मुक्त(काष्ठा fhci_usb *usb);

/* fhci-sched.c */
बाह्य काष्ठा tasklet_काष्ठा fhci_tasklet;
व्योम fhci_transaction_confirm(काष्ठा fhci_usb *usb, काष्ठा packet *pkt);
व्योम fhci_flush_all_transmissions(काष्ठा fhci_usb *usb);
व्योम fhci_schedule_transactions(काष्ठा fhci_usb *usb);
व्योम fhci_device_connected_पूर्णांकerrupt(काष्ठा fhci_hcd *fhci);
व्योम fhci_device_disconnected_पूर्णांकerrupt(काष्ठा fhci_hcd *fhci);
व्योम fhci_queue_urb(काष्ठा fhci_hcd *fhci, काष्ठा urb *urb);
u32 fhci_transfer_confirm_callback(काष्ठा fhci_hcd *fhci);
irqवापस_t fhci_irq(काष्ठा usb_hcd *hcd);
irqवापस_t fhci_frame_limit_समयr_irq(पूर्णांक irq, व्योम *_hcd);

/* fhci-q.h */
व्योम fhci_urb_complete_मुक्त(काष्ठा fhci_hcd *fhci, काष्ठा urb *urb);
काष्ठा td *fhci_हटाओ_td_from_ed(काष्ठा ed *ed);
काष्ठा td *fhci_हटाओ_td_from_frame(काष्ठा fhci_समय_frame *frame);
व्योम fhci_move_td_from_ed_to_करोne_list(काष्ठा fhci_usb *usb, काष्ठा ed *ed);
काष्ठा td *fhci_peek_td_from_frame(काष्ठा fhci_समय_frame *frame);
व्योम fhci_add_td_to_frame(काष्ठा fhci_समय_frame *frame, काष्ठा td *td);
काष्ठा td *fhci_हटाओ_td_from_करोne_list(काष्ठा fhci_controller_list *p_list);
व्योम fhci_करोne_td(काष्ठा urb *urb, काष्ठा td *td);
व्योम fhci_del_ed_list(काष्ठा fhci_hcd *fhci, काष्ठा ed *ed);

#अगर_घोषित CONFIG_FHCI_DEBUG

व्योम fhci_dbg_isr(काष्ठा fhci_hcd *fhci, पूर्णांक usb_er);
व्योम fhci_dfs_destroy(काष्ठा fhci_hcd *fhci);
व्योम fhci_dfs_create(काष्ठा fhci_hcd *fhci);

#अन्यथा

अटल अंतरभूत व्योम fhci_dbg_isr(काष्ठा fhci_hcd *fhci, पूर्णांक usb_er) अणुपूर्ण
अटल अंतरभूत व्योम fhci_dfs_destroy(काष्ठा fhci_hcd *fhci) अणुपूर्ण
अटल अंतरभूत व्योम fhci_dfs_create(काष्ठा fhci_hcd *fhci) अणुपूर्ण

#पूर्ण_अगर /* CONFIG_FHCI_DEBUG */

#पूर्ण_अगर /* __FHCI_H */
