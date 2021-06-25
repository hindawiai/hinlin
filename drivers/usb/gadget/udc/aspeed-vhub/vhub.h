<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
#अगर_अघोषित __ASPEED_VHUB_H
#घोषणा __ASPEED_VHUB_H

#समावेश <linux/usb.h>
#समावेश <linux/usb/ch11.h>

/*****************************
 *                           *
 * VHUB रेजिस्टर definitions *
 *                           *
 *****************************/

#घोषणा	AST_VHUB_CTRL		0x00	/* Root Function Control & Status Register */
#घोषणा	AST_VHUB_CONF		0x04	/* Root Configuration Setting Register */
#घोषणा	AST_VHUB_IER		0x08	/* Interrupt Ctrl Register */
#घोषणा	AST_VHUB_ISR		0x0C	/* Interrupt Status Register */
#घोषणा	AST_VHUB_EP_ACK_IER	0x10	/* Programmable Endpoपूर्णांक Pool ACK Interrupt Enable Register */
#घोषणा	AST_VHUB_EP_NACK_IER	0x14	/* Programmable Endpoपूर्णांक Pool NACK Interrupt Enable Register  */
#घोषणा AST_VHUB_EP_ACK_ISR	0x18	/* Programmable Endpoपूर्णांक Pool ACK Interrupt Status Register  */
#घोषणा AST_VHUB_EP_NACK_ISR	0x1C	/* Programmable Endpoपूर्णांक Pool NACK Interrupt Status Register  */
#घोषणा AST_VHUB_SW_RESET	0x20	/* Device Controller Soft Reset Enable Register */
#घोषणा AST_VHUB_USBSTS		0x24	/* USB Status Register */
#घोषणा AST_VHUB_EP_TOGGLE	0x28	/* Programmable Endpoपूर्णांक Pool Data Toggle Value Set */
#घोषणा AST_VHUB_ISO_FAIL_ACC	0x2C	/* Isochronous Transaction Fail Accumulator */
#घोषणा AST_VHUB_EP0_CTRL	0x30	/* Endpoपूर्णांक 0 Contrl/Status Register */
#घोषणा AST_VHUB_EP0_DATA	0x34	/* Base Address of Endpoपूर्णांक 0 In/OUT Data Buffer Register */
#घोषणा AST_VHUB_EP1_CTRL	0x38	/* Endpoपूर्णांक 1 Contrl/Status Register */
#घोषणा AST_VHUB_EP1_STS_CHG	0x3C	/* Endpoपूर्णांक 1 Status Change Biपंचांगap Data */
#घोषणा AST_VHUB_SETUP0		0x80	/* Root Device Setup Data Buffer0 */
#घोषणा AST_VHUB_SETUP1		0x84	/* Root Device Setup Data Buffer1 */

/* Main control reg */
#घोषणा VHUB_CTRL_PHY_CLK			(1 << 31)
#घोषणा VHUB_CTRL_PHY_LOOP_TEST			(1 << 25)
#घोषणा VHUB_CTRL_DN_PWN			(1 << 24)
#घोषणा VHUB_CTRL_DP_PWN			(1 << 23)
#घोषणा VHUB_CTRL_LONG_DESC			(1 << 18)
#घोषणा VHUB_CTRL_ISO_RSP_CTRL			(1 << 17)
#घोषणा VHUB_CTRL_SPLIT_IN			(1 << 16)
#घोषणा VHUB_CTRL_LOOP_T_RESULT			(1 << 15)
#घोषणा VHUB_CTRL_LOOP_T_STS			(1 << 14)
#घोषणा VHUB_CTRL_PHY_BIST_RESULT		(1 << 13)
#घोषणा VHUB_CTRL_PHY_BIST_CTRL			(1 << 12)
#घोषणा VHUB_CTRL_PHY_RESET_DIS			(1 << 11)
#घोषणा VHUB_CTRL_SET_TEST_MODE(x)		((x) << 8)
#घोषणा VHUB_CTRL_MANUAL_REMOTE_WAKEUP		(1 << 4)
#घोषणा VHUB_CTRL_AUTO_REMOTE_WAKEUP		(1 << 3)
#घोषणा VHUB_CTRL_CLK_STOP_SUSPEND		(1 << 2)
#घोषणा VHUB_CTRL_FULL_SPEED_ONLY		(1 << 1)
#घोषणा VHUB_CTRL_UPSTREAM_CONNECT		(1 << 0)

/* IER & ISR */
#घोषणा VHUB_IRQ_DEV1_BIT			9
#घोषणा VHUB_IRQ_USB_CMD_DEADLOCK		(1 << 18)
#घोषणा VHUB_IRQ_EP_POOL_NAK			(1 << 17)
#घोषणा VHUB_IRQ_EP_POOL_ACK_STALL		(1 << 16)
#घोषणा VHUB_IRQ_DEVICE1			(1 << (VHUB_IRQ_DEV1_BIT))
#घोषणा VHUB_IRQ_BUS_RESUME			(1 << 8)
#घोषणा VHUB_IRQ_BUS_SUSPEND 			(1 << 7)
#घोषणा VHUB_IRQ_BUS_RESET 			(1 << 6)
#घोषणा VHUB_IRQ_HUB_EP1_IN_DATA_ACK		(1 << 5)
#घोषणा VHUB_IRQ_HUB_EP0_IN_DATA_NAK		(1 << 4)
#घोषणा VHUB_IRQ_HUB_EP0_IN_ACK_STALL		(1 << 3)
#घोषणा VHUB_IRQ_HUB_EP0_OUT_NAK		(1 << 2)
#घोषणा VHUB_IRQ_HUB_EP0_OUT_ACK_STALL		(1 << 1)
#घोषणा VHUB_IRQ_HUB_EP0_SETUP			(1 << 0)
#घोषणा VHUB_IRQ_ACK_ALL			0x1ff

/* Downstream device IRQ mask. */
#घोषणा VHUB_DEV_IRQ(n)				(VHUB_IRQ_DEVICE1 << (n))

/* SW reset reg */
#घोषणा VHUB_SW_RESET_EP_POOL			(1 << 9)
#घोषणा VHUB_SW_RESET_DMA_CONTROLLER		(1 << 8)
#घोषणा VHUB_SW_RESET_DEVICE5			(1 << 5)
#घोषणा VHUB_SW_RESET_DEVICE4			(1 << 4)
#घोषणा VHUB_SW_RESET_DEVICE3			(1 << 3)
#घोषणा VHUB_SW_RESET_DEVICE2			(1 << 2)
#घोषणा VHUB_SW_RESET_DEVICE1			(1 << 1)
#घोषणा VHUB_SW_RESET_ROOT_HUB			(1 << 0)

/* EP ACK/NACK IRQ masks */
#घोषणा VHUB_EP_IRQ(n)				(1 << (n))

/* USB status reg */
#घोषणा VHUB_USBSTS_HISPEED			(1 << 27)

/* EP toggle */
#घोषणा VHUB_EP_TOGGLE_VALUE			(1 << 8)
#घोषणा VHUB_EP_TOGGLE_SET_EPNUM(x)		((x) & 0x1f)

/* HUB EP0 control */
#घोषणा VHUB_EP0_CTRL_STALL			(1 << 0)
#घोषणा VHUB_EP0_TX_BUFF_RDY			(1 << 1)
#घोषणा VHUB_EP0_RX_BUFF_RDY			(1 << 2)
#घोषणा VHUB_EP0_RX_LEN(x)			(((x) >> 16) & 0x7f)
#घोषणा VHUB_EP0_SET_TX_LEN(x)			(((x) & 0x7f) << 8)

/* HUB EP1 control */
#घोषणा VHUB_EP1_CTRL_RESET_TOGGLE		(1 << 2)
#घोषणा VHUB_EP1_CTRL_STALL			(1 << 1)
#घोषणा VHUB_EP1_CTRL_ENABLE			(1 << 0)

/***********************************
 *                                 *
 * per-device रेजिस्टर definitions *
 *                                 *
 ***********************************/
#घोषणा AST_VHUB_DEV_EN_CTRL		0x00
#घोषणा AST_VHUB_DEV_ISR		0x04
#घोषणा AST_VHUB_DEV_EP0_CTRL		0x08
#घोषणा AST_VHUB_DEV_EP0_DATA		0x0c

/* Device enable control */
#घोषणा VHUB_DEV_EN_SET_ADDR(x)			((x) << 8)
#घोषणा VHUB_DEV_EN_ADDR_MASK			((0xff) << 8)
#घोषणा VHUB_DEV_EN_EP0_NAK_IRQEN		(1 << 6)
#घोषणा VHUB_DEV_EN_EP0_IN_ACK_IRQEN		(1 << 5)
#घोषणा VHUB_DEV_EN_EP0_OUT_NAK_IRQEN		(1 << 4)
#घोषणा VHUB_DEV_EN_EP0_OUT_ACK_IRQEN		(1 << 3)
#घोषणा VHUB_DEV_EN_EP0_SETUP_IRQEN		(1 << 2)
#घोषणा VHUB_DEV_EN_SPEED_SEL_HIGH		(1 << 1)
#घोषणा VHUB_DEV_EN_ENABLE_PORT			(1 << 0)

/* Interrupt status */
#घोषणा VHUV_DEV_IRQ_EP0_IN_DATA_NACK		(1 << 4)
#घोषणा VHUV_DEV_IRQ_EP0_IN_ACK_STALL		(1 << 3)
#घोषणा VHUV_DEV_IRQ_EP0_OUT_DATA_NACK		(1 << 2)
#घोषणा VHUV_DEV_IRQ_EP0_OUT_ACK_STALL		(1 << 1)
#घोषणा VHUV_DEV_IRQ_EP0_SETUP			(1 << 0)

/* Control bits.
 *
 * Note: The driver relies on the bulk of those bits
 *       matching corresponding vHub EP0 control bits
 */
#घोषणा VHUB_DEV_EP0_CTRL_STALL			VHUB_EP0_CTRL_STALL
#घोषणा VHUB_DEV_EP0_TX_BUFF_RDY		VHUB_EP0_TX_BUFF_RDY
#घोषणा VHUB_DEV_EP0_RX_BUFF_RDY		VHUB_EP0_RX_BUFF_RDY
#घोषणा VHUB_DEV_EP0_RX_LEN(x)			VHUB_EP0_RX_LEN(x)
#घोषणा VHUB_DEV_EP0_SET_TX_LEN(x)		VHUB_EP0_SET_TX_LEN(x)

/*************************************
 *                                   *
 * per-endpoपूर्णांक रेजिस्टर definitions *
 *                                   *
 *************************************/

#घोषणा AST_VHUB_EP_CONFIG		0x00
#घोषणा AST_VHUB_EP_DMA_CTLSTAT		0x04
#घोषणा AST_VHUB_EP_DESC_BASE		0x08
#घोषणा AST_VHUB_EP_DESC_STATUS		0x0C

/* EP config reg */
#घोषणा VHUB_EP_CFG_SET_MAX_PKT(x)	(((x) & 0x3ff) << 16)
#घोषणा VHUB_EP_CFG_AUTO_DATA_DISABLE	(1 << 13)
#घोषणा VHUB_EP_CFG_STALL_CTRL		(1 << 12)
#घोषणा VHUB_EP_CFG_SET_EP_NUM(x)	(((x) & 0xf) << 8)
#घोषणा VHUB_EP_CFG_SET_TYPE(x)		((x) << 5)
#घोषणा   EP_TYPE_OFF			0
#घोषणा   EP_TYPE_BULK			1
#घोषणा   EP_TYPE_INT			2
#घोषणा   EP_TYPE_ISO			3
#घोषणा VHUB_EP_CFG_सूची_OUT		(1 << 4)
#घोषणा VHUB_EP_CFG_SET_DEV(x)		((x) << 1)
#घोषणा VHUB_EP_CFG_ENABLE		(1 << 0)

/* EP DMA control */
#घोषणा VHUB_EP_DMA_PROC_STATUS(x)	(((x) >> 4) & 0xf)
#घोषणा   EP_DMA_PROC_RX_IDLE		0
#घोषणा   EP_DMA_PROC_TX_IDLE		8
#घोषणा VHUB_EP_DMA_IN_LONG_MODE	(1 << 3)
#घोषणा VHUB_EP_DMA_OUT_CONTIG_MODE	(1 << 3)
#घोषणा VHUB_EP_DMA_CTRL_RESET		(1 << 2)
#घोषणा VHUB_EP_DMA_SINGLE_STAGE	(1 << 1)
#घोषणा VHUB_EP_DMA_DESC_MODE		(1 << 0)

/* EP DMA status */
#घोषणा VHUB_EP_DMA_SET_TX_SIZE(x)	((x) << 16)
#घोषणा VHUB_EP_DMA_TX_SIZE(x)		(((x) >> 16) & 0x7ff)
#घोषणा VHUB_EP_DMA_RPTR(x)		(((x) >> 8) & 0xff)
#घोषणा VHUB_EP_DMA_SET_RPTR(x)		(((x) & 0xff) << 8)
#घोषणा VHUB_EP_DMA_SET_CPU_WPTR(x)	(x)
#घोषणा VHUB_EP_DMA_SINGLE_KICK		(1 << 0) /* WPTR = 1 क्रम single mode */

/*******************************
 *                             *
 * DMA descriptors definitions *
 *                             *
 *******************************/

/* Desc W1 IN */
#घोषणा VHUB_DSC1_IN_INTERRUPT		(1 << 31)
#घोषणा VHUB_DSC1_IN_SPID_DATA0		(0 << 14)
#घोषणा VHUB_DSC1_IN_SPID_DATA2		(1 << 14)
#घोषणा VHUB_DSC1_IN_SPID_DATA1		(2 << 14)
#घोषणा VHUB_DSC1_IN_SPID_MDATA		(3 << 14)
#घोषणा VHUB_DSC1_IN_SET_LEN(x)		((x) & 0xfff)
#घोषणा VHUB_DSC1_IN_LEN(x)		((x) & 0xfff)

/****************************************
 *                                      *
 * Data काष्ठाures and misc definitions *
 *                                      *
 ****************************************/

/*
 * AST_VHUB_NUM_GEN_EPs and AST_VHUB_NUM_PORTS are kept to aव्योम अवरोधing
 * existing AST2400/AST2500 platक्रमms. AST2600 and future vhub revisions
 * should define number of करोwnstream ports and endpoपूर्णांकs in device tree.
 */
#घोषणा AST_VHUB_NUM_GEN_EPs	15	/* Generic non-0 EPs */
#घोषणा AST_VHUB_NUM_PORTS	5	/* vHub ports */
#घोषणा AST_VHUB_EP0_MAX_PACKET	64	/* EP0's max packet size */
#घोषणा AST_VHUB_EPn_MAX_PACKET	1024	/* Generic EPs max packet size */
#घोषणा AST_VHUB_DESCS_COUNT	256	/* Use 256 descriptor mode (valid
					 * values are 256 and 32)
					 */

काष्ठा ast_vhub;
काष्ठा ast_vhub_dev;

/*
 * DMA descriptor (generic EPs only, currently only used
 * क्रम IN endpoपूर्णांकs
 */
काष्ठा ast_vhub_desc अणु
	__le32	w0;
	__le32	w1;
पूर्ण;

/* A transfer request, either core-originated or पूर्णांकernal */
काष्ठा ast_vhub_req अणु
	काष्ठा usb_request	req;
	काष्ठा list_head	queue;

	/* Actual count written to descriptors (desc mode only) */
	अचिन्हित पूर्णांक		act_count;

	/*
	 * Desc number of the final packet or -1. For non-desc
	 * mode (or ep0), any >= 0 value means "last packet"
	 */
	पूर्णांक			last_desc;

	/* Request active (pending DMAs) */
	bool			active  : 1;

	/* Internal request (करोn't call back core) */
	bool			पूर्णांकernal : 1;
पूर्ण;
#घोषणा to_ast_req(__ureq) container_of(__ureq, काष्ठा ast_vhub_req, req)

/* Current state of an EP0 */
क्रमागत ep0_state अणु
	ep0_state_token,
	ep0_state_data,
	ep0_state_status,
	ep0_state_stall,
पूर्ण;

/*
 * An endpoपूर्णांक, either generic, ep0, actual gadget EP
 * or पूर्णांकernal use vhub EP0. vhub EP1 करोesn't have an
 * associated काष्ठाure as it's mostly HW managed.
 */
काष्ठा ast_vhub_ep अणु
	काष्ठा usb_ep		ep;

	/* Request queue */
	काष्ठा list_head	queue;

	/* EP index in the device, 0 means this is an EP0 */
	अचिन्हित पूर्णांक		d_idx;

	/* Dev poपूर्णांकer or शून्य क्रम vHub EP0 */
	काष्ठा ast_vhub_dev	*dev;

	/* vHub itself */
	काष्ठा ast_vhub		*vhub;

	/*
	 * DMA buffer क्रम EP0, fallback DMA buffer क्रम misaligned
	 * OUT transfers क्रम generic EPs
	 */
	व्योम			*buf;
	dma_addr_t		buf_dma;

	/* The rest depends on the EP type */
	जोड़ अणु
		/* EP0 (either device or vhub) */
		काष्ठा अणु
			/*
			 * EP0 रेजिस्टरs are "similar" क्रम
			 * vHub and devices but located in
			 * dअगरferent places.
			 */
			व्योम __iomem		*ctlstat;
			व्योम __iomem		*setup;

			/* Current state & direction */
			क्रमागत ep0_state		state;
			bool			dir_in;

			/* Internal use request */
			काष्ठा ast_vhub_req	req;
		पूर्ण ep0;

		/* Generic endpoपूर्णांक (aka EPn) */
		काष्ठा अणु
			/* Registers */
			व्योम __iomem   		*regs;

			/* Index in global pool (zero-based) */
			अचिन्हित पूर्णांक		g_idx;

			/* DMA Descriptors */
			काष्ठा ast_vhub_desc	*descs;
			dma_addr_t		descs_dma;
			अचिन्हित पूर्णांक		d_next;
			अचिन्हित पूर्णांक		d_last;
			अचिन्हित पूर्णांक		dma_conf;

			/* Max chunk size क्रम IN EPs */
			अचिन्हित पूर्णांक		chunk_max;

			/* State flags */
			bool			is_in :  1;
			bool			is_iso : 1;
			bool			stalled : 1;
			bool			wedged : 1;
			bool			enabled : 1;
			bool			desc_mode : 1;
		पूर्ण epn;
	पूर्ण;
पूर्ण;
#घोषणा to_ast_ep(__uep) container_of(__uep, काष्ठा ast_vhub_ep, ep)

/* A device attached to a vHub port */
काष्ठा ast_vhub_dev अणु
	काष्ठा ast_vhub			*vhub;
	व्योम __iomem			*regs;

	/* Device index (zero-based) and name string */
	अचिन्हित पूर्णांक			index;
	स्थिर अक्षर			*name;

	/* sysfs enclosure क्रम the gadget gunk */
	काष्ठा device			*port_dev;

	/* Link to gadget core */
	काष्ठा usb_gadget		gadget;
	काष्ठा usb_gadget_driver	*driver;
	bool				रेजिस्टरed : 1;
	bool				wakeup_en : 1;
	bool				enabled : 1;

	/* Endpoपूर्णांक काष्ठाures */
	काष्ठा ast_vhub_ep		ep0;
	काष्ठा ast_vhub_ep		**epns;
	u32				max_epns;

पूर्ण;
#घोषणा to_ast_dev(__g) container_of(__g, काष्ठा ast_vhub_dev, gadget)

/* Per vhub port stateinfo काष्ठाure */
काष्ठा ast_vhub_port अणु
	/* Port status & status change रेजिस्टरs */
	u16			status;
	u16			change;

	/* Associated device slot */
	काष्ठा ast_vhub_dev	dev;
पूर्ण;

काष्ठा ast_vhub_full_cdesc अणु
	काष्ठा usb_config_descriptor	cfg;
	काष्ठा usb_पूर्णांकerface_descriptor पूर्णांकf;
	काष्ठा usb_endpoपूर्णांक_descriptor	ep;
पूर्ण __packed;

/* Global vhub काष्ठाure */
काष्ठा ast_vhub अणु
	काष्ठा platक्रमm_device		*pdev;
	व्योम __iomem			*regs;
	पूर्णांक				irq;
	spinlock_t			lock;
	काष्ठा work_काष्ठा		wake_work;
	काष्ठा clk			*clk;

	/* EP0 DMA buffers allocated in one chunk */
	व्योम				*ep0_bufs;
	dma_addr_t			ep0_bufs_dma;

	/* EP0 of the vhub itself */
	काष्ठा ast_vhub_ep		ep0;

	/* State of vhub ep1 */
	bool				ep1_stalled : 1;

	/* Per-port info */
	काष्ठा ast_vhub_port		*ports;
	u32				max_ports;
	u32				port_irq_mask;

	/* Generic EP data काष्ठाures */
	काष्ठा ast_vhub_ep		*epns;
	u32				max_epns;

	/* Upstream bus is suspended ? */
	bool				suspended : 1;

	/* Hub itself can संकेत remote wakeup */
	bool				wakeup_en : 1;

	/* Force full speed only */
	bool				क्रमce_usb1 : 1;

	/* Upstream bus speed captured at bus reset */
	अचिन्हित पूर्णांक			speed;

	/* Standard USB Descriptors of the vhub. */
	काष्ठा usb_device_descriptor	vhub_dev_desc;
	काष्ठा ast_vhub_full_cdesc	vhub_conf_desc;
	काष्ठा usb_hub_descriptor	vhub_hub_desc;
	काष्ठा list_head		vhub_str_desc;
पूर्ण;

/* Standard request handlers result codes */
क्रमागत std_req_rc अणु
	std_req_stall = -1,	/* Stall requested */
	std_req_complete = 0,	/* Request completed with no data */
	std_req_data = 1,	/* Request completed with data */
	std_req_driver = 2,	/* Pass to driver pls */
पूर्ण;

#अगर_घोषित CONFIG_USB_GADGET_VERBOSE
#घोषणा UDCVDBG(u, fmt...)	dev_dbg(&(u)->pdev->dev, fmt)

#घोषणा EPVDBG(ep, fmt, ...)	करो अणु			\
	dev_dbg(&(ep)->vhub->pdev->dev,			\
		"%s:EP%d " fmt,				\
		(ep)->dev ? (ep)->dev->name : "hub",	\
		(ep)->d_idx, ##__VA_ARGS__);		\
	पूर्ण जबतक(0)

#घोषणा DVDBG(d, fmt, ...)	करो अणु			\
	dev_dbg(&(d)->vhub->pdev->dev,			\
		"%s " fmt, (d)->name,			\
		##__VA_ARGS__);				\
	पूर्ण जबतक(0)

#अन्यथा
#घोषणा UDCVDBG(u, fmt...)	करो अणु पूर्ण जबतक(0)
#घोषणा EPVDBG(ep, fmt, ...)	करो अणु पूर्ण जबतक(0)
#घोषणा DVDBG(d, fmt, ...)	करो अणु पूर्ण जबतक(0)
#पूर्ण_अगर

#अगर_घोषित CONFIG_USB_GADGET_DEBUG
#घोषणा UDCDBG(u, fmt...)	dev_dbg(&(u)->pdev->dev, fmt)

#घोषणा EPDBG(ep, fmt, ...)	करो अणु			\
	dev_dbg(&(ep)->vhub->pdev->dev,			\
		"%s:EP%d " fmt,				\
		(ep)->dev ? (ep)->dev->name : "hub",	\
		(ep)->d_idx, ##__VA_ARGS__);		\
	पूर्ण जबतक(0)

#घोषणा DDBG(d, fmt, ...)	करो अणु			\
	dev_dbg(&(d)->vhub->pdev->dev,			\
		"%s " fmt, (d)->name,			\
		##__VA_ARGS__);				\
	पूर्ण जबतक(0)
#अन्यथा
#घोषणा UDCDBG(u, fmt...)	करो अणु पूर्ण जबतक(0)
#घोषणा EPDBG(ep, fmt, ...)	करो अणु पूर्ण जबतक(0)
#घोषणा DDBG(d, fmt, ...)	करो अणु पूर्ण जबतक(0)
#पूर्ण_अगर

अटल अंतरभूत व्योम vhub_dma_workaround(व्योम *addr)
अणु
	/*
	 * This works around a confirmed HW issue with the Aspeed chip.
	 *
	 * The core uses a dअगरferent bus to memory than the AHB going to
	 * the USB device controller. Due to the latter having a higher
	 * priority than the core क्रम arbitration on that bus, it's
	 * possible क्रम an MMIO to the device, followed by a DMA by the
	 * device from memory to all be perक्रमmed and services beक्रमe
	 * a previous store to memory माला_लो completed.
	 *
	 * This the following scenario can happen:
	 *
	 *    - Driver ग_लिखोs to a DMA descriptor (Mbus)
	 *    - Driver ग_लिखोs to the MMIO रेजिस्टर to start the DMA (AHB)
	 *    - The gadget sees the second ग_लिखो and sends a पढ़ो of the
	 *      descriptor to the memory controller (Mbus)
	 *    - The gadget hits memory beक्रमe the descriptor ग_लिखो
	 *      causing it to पढ़ो an obsolete value.
	 *
	 * Thankfully the problem is limited to the USB gadget device, other
	 * masters in the SoC all have a lower priority than the core, thus
	 * ensuring that the store by the core arrives first.
	 *
	 * The workaround consists of using a dummy पढ़ो of the memory beक्रमe
	 * करोing the MMIO ग_लिखोs. This will ensure that the previous ग_लिखोs
	 * have been "pushed out".
	 */
	mb();
	(व्योम)__raw_पढ़ोl((व्योम __iomem *)addr);
पूर्ण

/* core.c */
व्योम ast_vhub_करोne(काष्ठा ast_vhub_ep *ep, काष्ठा ast_vhub_req *req,
		   पूर्णांक status);
व्योम ast_vhub_nuke(काष्ठा ast_vhub_ep *ep, पूर्णांक status);
काष्ठा usb_request *ast_vhub_alloc_request(काष्ठा usb_ep *u_ep,
					   gfp_t gfp_flags);
व्योम ast_vhub_मुक्त_request(काष्ठा usb_ep *u_ep, काष्ठा usb_request *u_req);
व्योम ast_vhub_init_hw(काष्ठा ast_vhub *vhub);

/* ep0.c */
व्योम ast_vhub_ep0_handle_ack(काष्ठा ast_vhub_ep *ep, bool in_ack);
व्योम ast_vhub_ep0_handle_setup(काष्ठा ast_vhub_ep *ep);
व्योम ast_vhub_reset_ep0(काष्ठा ast_vhub_dev *dev);
व्योम ast_vhub_init_ep0(काष्ठा ast_vhub *vhub, काष्ठा ast_vhub_ep *ep,
		       काष्ठा ast_vhub_dev *dev);
पूर्णांक ast_vhub_reply(काष्ठा ast_vhub_ep *ep, अक्षर *ptr, पूर्णांक len);
पूर्णांक __ast_vhub_simple_reply(काष्ठा ast_vhub_ep *ep, पूर्णांक len, ...);
#घोषणा ast_vhub_simple_reply(udc, ...)					       \
	__ast_vhub_simple_reply((udc),					       \
			       माप((u8[]) अणु __VA_ARGS__ पूर्ण)/माप(u8),      \
			       __VA_ARGS__)

/* hub.c */
पूर्णांक ast_vhub_init_hub(काष्ठा ast_vhub *vhub);
क्रमागत std_req_rc ast_vhub_std_hub_request(काष्ठा ast_vhub_ep *ep,
					 काष्ठा usb_ctrlrequest *crq);
क्रमागत std_req_rc ast_vhub_class_hub_request(काष्ठा ast_vhub_ep *ep,
					   काष्ठा usb_ctrlrequest *crq);
व्योम ast_vhub_device_connect(काष्ठा ast_vhub *vhub, अचिन्हित पूर्णांक port,
			     bool on);
व्योम ast_vhub_hub_suspend(काष्ठा ast_vhub *vhub);
व्योम ast_vhub_hub_resume(काष्ठा ast_vhub *vhub);
व्योम ast_vhub_hub_reset(काष्ठा ast_vhub *vhub);
व्योम ast_vhub_hub_wake_all(काष्ठा ast_vhub *vhub);

/* dev.c */
पूर्णांक ast_vhub_init_dev(काष्ठा ast_vhub *vhub, अचिन्हित पूर्णांक idx);
व्योम ast_vhub_del_dev(काष्ठा ast_vhub_dev *d);
व्योम ast_vhub_dev_irq(काष्ठा ast_vhub_dev *d);
पूर्णांक ast_vhub_std_dev_request(काष्ठा ast_vhub_ep *ep,
			     काष्ठा usb_ctrlrequest *crq);

/* epn.c */
व्योम ast_vhub_epn_ack_irq(काष्ठा ast_vhub_ep *ep);
व्योम ast_vhub_update_epn_stall(काष्ठा ast_vhub_ep *ep);
काष्ठा ast_vhub_ep *ast_vhub_alloc_epn(काष्ठा ast_vhub_dev *d, u8 addr);
व्योम ast_vhub_dev_suspend(काष्ठा ast_vhub_dev *d);
व्योम ast_vhub_dev_resume(काष्ठा ast_vhub_dev *d);
व्योम ast_vhub_dev_reset(काष्ठा ast_vhub_dev *d);

#पूर्ण_अगर /* __ASPEED_VHUB_H */
