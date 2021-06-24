<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * bcm63xx_udc.c -- BCM63xx UDC high/full speed USB device controller
 *
 * Copyright (C) 2012 Kevin Cernekee <cernekee@gmail.com>
 * Copyright (C) 2012 Broadcom Corporation
 */

#समावेश <linux/bitops.h>
#समावेश <linux/bug.h>
#समावेश <linux/clk.h>
#समावेश <linux/compiler.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/sched.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/slab.h>
#समावेश <linux/समयr.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/ch9.h>
#समावेश <linux/usb/gadget.h>
#समावेश <linux/workqueue.h>

#समावेश <bcm63xx_cpu.h>
#समावेश <bcm63xx_iudma.h>
#समावेश <bcm63xx_dev_usb_usbd.h>
#समावेश <bcm63xx_पन.स>
#समावेश <bcm63xx_regs.h>

#घोषणा DRV_MODULE_NAME		"bcm63xx_udc"

अटल स्थिर अक्षर bcm63xx_ep0name[] = "ep0";

अटल स्थिर काष्ठा अणु
	स्थिर अक्षर *name;
	स्थिर काष्ठा usb_ep_caps caps;
पूर्ण bcm63xx_ep_info[] = अणु
#घोषणा EP_INFO(_name, _caps) \
	अणु \
		.name = _name, \
		.caps = _caps, \
	पूर्ण

	EP_INFO(bcm63xx_ep0name,
		USB_EP_CAPS(USB_EP_CAPS_TYPE_CONTROL, USB_EP_CAPS_सूची_ALL)),
	EP_INFO("ep1in-bulk",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_BULK, USB_EP_CAPS_सूची_IN)),
	EP_INFO("ep2out-bulk",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_BULK, USB_EP_CAPS_सूची_OUT)),
	EP_INFO("ep3in-int",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_INT, USB_EP_CAPS_सूची_IN)),
	EP_INFO("ep4out-int",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_INT, USB_EP_CAPS_सूची_OUT)),

#अघोषित EP_INFO
पूर्ण;

अटल bool use_fullspeed;
module_param(use_fullspeed, bool, S_IRUGO);
MODULE_PARM_DESC(use_fullspeed, "true for fullspeed only");

/*
 * RX IRQ coalescing options:
 *
 * false (शेष) - one IRQ per DATAx packet.  Slow but reliable.  The
 * driver is able to pass the "testusb" suite and recover from conditions like:
 *
 *   1) Device queues up a 2048-byte RX IUDMA transaction on an OUT bulk ep
 *   2) Host sends 512 bytes of data
 *   3) Host decides to reconfigure the device and sends SET_INTERFACE
 *   4) Device shuts करोwn the endpoपूर्णांक and cancels the RX transaction
 *
 * true - one IRQ per transfer, क्रम transfers <= 2048B.  Generates
 * considerably fewer IRQs, but error recovery is less robust.  Does not
 * reliably pass "testusb".
 *
 * TX always uses coalescing, because we can cancel partially complete TX
 * transfers by repeatedly flushing the FIFO.  The hardware करोesn't allow
 * this on RX.
 */
अटल bool irq_coalesce;
module_param(irq_coalesce, bool, S_IRUGO);
MODULE_PARM_DESC(irq_coalesce, "take one IRQ per RX transfer");

#घोषणा BCM63XX_NUM_EP			5
#घोषणा BCM63XX_NUM_IUDMA		6
#घोषणा BCM63XX_NUM_FIFO_PAIRS		3

#घोषणा IUDMA_RESET_TIMEOUT_US		10000

#घोषणा IUDMA_EP0_RXCHAN		0
#घोषणा IUDMA_EP0_TXCHAN		1

#घोषणा IUDMA_MAX_FRAGMENT		2048
#घोषणा BCM63XX_MAX_CTRL_PKT		64

#घोषणा BCMEP_CTRL			0x00
#घोषणा BCMEP_ISOC			0x01
#घोषणा BCMEP_BULK			0x02
#घोषणा BCMEP_INTR			0x03

#घोषणा BCMEP_OUT			0x00
#घोषणा BCMEP_IN			0x01

#घोषणा BCM63XX_SPD_FULL		1
#घोषणा BCM63XX_SPD_HIGH		0

#घोषणा IUDMA_DMAC_OFFSET		0x200
#घोषणा IUDMA_DMAS_OFFSET		0x400

क्रमागत bcm63xx_ep0_state अणु
	EP0_REQUEUE,
	EP0_IDLE,
	EP0_IN_DATA_PHASE_SETUP,
	EP0_IN_DATA_PHASE_COMPLETE,
	EP0_OUT_DATA_PHASE_SETUP,
	EP0_OUT_DATA_PHASE_COMPLETE,
	EP0_OUT_STATUS_PHASE,
	EP0_IN_FAKE_STATUS_PHASE,
	EP0_SHUTDOWN,
पूर्ण;

अटल स्थिर अक्षर __maybe_unused bcm63xx_ep0_state_names[][32] = अणु
	"REQUEUE",
	"IDLE",
	"IN_DATA_PHASE_SETUP",
	"IN_DATA_PHASE_COMPLETE",
	"OUT_DATA_PHASE_SETUP",
	"OUT_DATA_PHASE_COMPLETE",
	"OUT_STATUS_PHASE",
	"IN_FAKE_STATUS_PHASE",
	"SHUTDOWN",
पूर्ण;

/**
 * काष्ठा iudma_ch_cfg - Static configuration क्रम an IUDMA channel.
 * @ep_num: USB endpoपूर्णांक number.
 * @n_bds: Number of buffer descriptors in the ring.
 * @ep_type: Endpoपूर्णांक type (control, bulk, पूर्णांकerrupt).
 * @dir: Direction (in, out).
 * @n_fअगरo_slots: Number of FIFO entries to allocate क्रम this channel.
 * @max_pkt_hs: Maximum packet size in high speed mode.
 * @max_pkt_fs: Maximum packet size in full speed mode.
 */
काष्ठा iudma_ch_cfg अणु
	पूर्णांक				ep_num;
	पूर्णांक				n_bds;
	पूर्णांक				ep_type;
	पूर्णांक				dir;
	पूर्णांक				n_fअगरo_slots;
	पूर्णांक				max_pkt_hs;
	पूर्णांक				max_pkt_fs;
पूर्ण;

अटल स्थिर काष्ठा iudma_ch_cfg iudma_शेषs[] = अणु

	/* This controller was deचिन्हित to support a CDC/RNDIS application.
	   It may be possible to reconfigure some of the endpoपूर्णांकs, but
	   the hardware limitations (FIFO sizing and number of DMA channels)
	   may signअगरicantly impact flexibility and/or stability.  Change
	   these values at your own risk.

	      ep_num       ep_type           n_fअगरo_slots    max_pkt_fs
	idx      |  n_bds     |         dir       |  max_pkt_hs  |
	 |       |    |       |          |        |      |       |       */
	[0] = अणु -1,   4, BCMEP_CTRL, BCMEP_OUT,  32,    64,     64 पूर्ण,
	[1] = अणु  0,   4, BCMEP_CTRL, BCMEP_OUT,  32,    64,     64 पूर्ण,
	[2] = अणु  2,  16, BCMEP_BULK, BCMEP_OUT, 128,   512,     64 पूर्ण,
	[3] = अणु  1,  16, BCMEP_BULK, BCMEP_IN,  128,   512,     64 पूर्ण,
	[4] = अणु  4,   4, BCMEP_INTR, BCMEP_OUT,  32,    64,     64 पूर्ण,
	[5] = अणु  3,   4, BCMEP_INTR, BCMEP_IN,   32,    64,     64 पूर्ण,
पूर्ण;

काष्ठा bcm63xx_udc;

/**
 * काष्ठा iudma_ch - Represents the current state of a single IUDMA channel.
 * @ch_idx: IUDMA channel index (0 to BCM63XX_NUM_IUDMA-1).
 * @ep_num: USB endpoपूर्णांक number.  -1 क्रम ep0 RX.
 * @enabled: Whether bcm63xx_ep_enable() has been called.
 * @max_pkt: "Chunk size" on the USB पूर्णांकerface.  Based on पूर्णांकerface speed.
 * @is_tx: true क्रम TX, false क्रम RX.
 * @bep: Poपूर्णांकer to the associated endpoपूर्णांक.  शून्य क्रम ep0 RX.
 * @udc: Reference to the device controller.
 * @पढ़ो_bd: Next buffer descriptor to reap from the hardware.
 * @ग_लिखो_bd: Next BD available क्रम a new packet.
 * @end_bd: Poपूर्णांकs to the final BD in the ring.
 * @n_bds_used: Number of BD entries currently occupied.
 * @bd_ring: Base poपूर्णांकer to the BD ring.
 * @bd_ring_dma: Physical (DMA) address of bd_ring.
 * @n_bds: Total number of BDs in the ring.
 *
 * ep0 has two IUDMA channels (IUDMA_EP0_RXCHAN and IUDMA_EP0_TXCHAN), as it is
 * bidirectional.  The "struct usb_ep" associated with ep0 is क्रम TX (IN)
 * only.
 *
 * Each bulk/पूर्णांकr endpoपूर्णांक has a single IUDMA channel and a single
 * काष्ठा usb_ep.
 */
काष्ठा iudma_ch अणु
	अचिन्हित पूर्णांक			ch_idx;
	पूर्णांक				ep_num;
	bool				enabled;
	पूर्णांक				max_pkt;
	bool				is_tx;
	काष्ठा bcm63xx_ep		*bep;
	काष्ठा bcm63xx_udc		*udc;

	काष्ठा bcm_enet_desc		*पढ़ो_bd;
	काष्ठा bcm_enet_desc		*ग_लिखो_bd;
	काष्ठा bcm_enet_desc		*end_bd;
	पूर्णांक				n_bds_used;

	काष्ठा bcm_enet_desc		*bd_ring;
	dma_addr_t			bd_ring_dma;
	अचिन्हित पूर्णांक			n_bds;
पूर्ण;

/**
 * काष्ठा bcm63xx_ep - Internal (driver) state of a single endpoपूर्णांक.
 * @ep_num: USB endpoपूर्णांक number.
 * @iudma: Poपूर्णांकer to IUDMA channel state.
 * @ep: USB gadget layer representation of the EP.
 * @udc: Reference to the device controller.
 * @queue: Linked list of outstanding requests क्रम this EP.
 * @halted: 1 अगर the EP is stalled; 0 otherwise.
 */
काष्ठा bcm63xx_ep अणु
	अचिन्हित पूर्णांक			ep_num;
	काष्ठा iudma_ch			*iudma;
	काष्ठा usb_ep			ep;
	काष्ठा bcm63xx_udc		*udc;
	काष्ठा list_head		queue;
	अचिन्हित			halted:1;
पूर्ण;

/**
 * काष्ठा bcm63xx_req - Internal (driver) state of a single request.
 * @queue: Links back to the EP's request list.
 * @req: USB gadget layer representation of the request.
 * @offset: Current byte offset पूर्णांकo the data buffer (next byte to queue).
 * @bd_bytes: Number of data bytes in outstanding BD entries.
 * @iudma: IUDMA channel used क्रम the request.
 */
काष्ठा bcm63xx_req अणु
	काष्ठा list_head		queue;		/* ep's requests */
	काष्ठा usb_request		req;
	अचिन्हित पूर्णांक			offset;
	अचिन्हित पूर्णांक			bd_bytes;
	काष्ठा iudma_ch			*iudma;
पूर्ण;

/**
 * काष्ठा bcm63xx_udc - Driver/hardware निजी context.
 * @lock: Spinlock to mediate access to this काष्ठा, and (most) HW regs.
 * @dev: Generic Linux device काष्ठाure.
 * @pd: Platक्रमm data (board/port info).
 * @usbd_clk: Clock descriptor क्रम the USB device block.
 * @usbh_clk: Clock descriptor क्रम the USB host block.
 * @gadget: USB device.
 * @driver: Driver क्रम USB device.
 * @usbd_regs: Base address of the USBD/USB20D block.
 * @iudma_regs: Base address of the USBD's associated IUDMA block.
 * @bep: Array of endpoपूर्णांकs, including ep0.
 * @iudma: Array of all IUDMA channels used by this controller.
 * @cfg: USB configuration number, from SET_CONFIGURATION wValue.
 * @अगरace: USB पूर्णांकerface number, from SET_INTERFACE wIndex.
 * @alt_अगरace: USB alt पूर्णांकerface number, from SET_INTERFACE wValue.
 * @ep0_ctrl_req: Request object क्रम bcm63xx_udc-initiated ep0 transactions.
 * @ep0_ctrl_buf: Data buffer क्रम ep0_ctrl_req.
 * @ep0state: Current state of the ep0 state machine.
 * @ep0_wq: Workqueue काष्ठा used to wake up the ep0 state machine.
 * @wedgemap: Biपंचांगap of wedged endpoपूर्णांकs.
 * @ep0_req_reset: USB reset is pending.
 * @ep0_req_set_cfg: Need to spoof a SET_CONFIGURATION packet.
 * @ep0_req_set_अगरace: Need to spoof a SET_INTERFACE packet.
 * @ep0_req_shutकरोwn: Driver is shutting करोwn; requesting ep0 to halt activity.
 * @ep0_req_completed: ep0 request has completed; worker has not seen it yet.
 * @ep0_reply: Pending reply from gadget driver.
 * @ep0_request: Outstanding ep0 request.
 * @debugfs_root: debugfs directory: /sys/kernel/debug/<DRV_MODULE_NAME>.
 */
काष्ठा bcm63xx_udc अणु
	spinlock_t			lock;

	काष्ठा device			*dev;
	काष्ठा bcm63xx_usbd_platक्रमm_data *pd;
	काष्ठा clk			*usbd_clk;
	काष्ठा clk			*usbh_clk;

	काष्ठा usb_gadget		gadget;
	काष्ठा usb_gadget_driver	*driver;

	व्योम __iomem			*usbd_regs;
	व्योम __iomem			*iudma_regs;

	काष्ठा bcm63xx_ep		bep[BCM63XX_NUM_EP];
	काष्ठा iudma_ch			iudma[BCM63XX_NUM_IUDMA];

	पूर्णांक				cfg;
	पूर्णांक				अगरace;
	पूर्णांक				alt_अगरace;

	काष्ठा bcm63xx_req		ep0_ctrl_req;
	u8				*ep0_ctrl_buf;

	पूर्णांक				ep0state;
	काष्ठा work_काष्ठा		ep0_wq;

	अचिन्हित दीर्घ			wedgemap;

	अचिन्हित			ep0_req_reset:1;
	अचिन्हित			ep0_req_set_cfg:1;
	अचिन्हित			ep0_req_set_अगरace:1;
	अचिन्हित			ep0_req_shutकरोwn:1;

	अचिन्हित			ep0_req_completed:1;
	काष्ठा usb_request		*ep0_reply;
	काष्ठा usb_request		*ep0_request;

	काष्ठा dentry			*debugfs_root;
पूर्ण;

अटल स्थिर काष्ठा usb_ep_ops bcm63xx_udc_ep_ops;

/***********************************************************************
 * Convenience functions
 ***********************************************************************/

अटल अंतरभूत काष्ठा bcm63xx_udc *gadget_to_udc(काष्ठा usb_gadget *g)
अणु
	वापस container_of(g, काष्ठा bcm63xx_udc, gadget);
पूर्ण

अटल अंतरभूत काष्ठा bcm63xx_ep *our_ep(काष्ठा usb_ep *ep)
अणु
	वापस container_of(ep, काष्ठा bcm63xx_ep, ep);
पूर्ण

अटल अंतरभूत काष्ठा bcm63xx_req *our_req(काष्ठा usb_request *req)
अणु
	वापस container_of(req, काष्ठा bcm63xx_req, req);
पूर्ण

अटल अंतरभूत u32 usbd_पढ़ोl(काष्ठा bcm63xx_udc *udc, u32 off)
अणु
	वापस bcm_पढ़ोl(udc->usbd_regs + off);
पूर्ण

अटल अंतरभूत व्योम usbd_ग_लिखोl(काष्ठा bcm63xx_udc *udc, u32 val, u32 off)
अणु
	bcm_ग_लिखोl(val, udc->usbd_regs + off);
पूर्ण

अटल अंतरभूत u32 usb_dma_पढ़ोl(काष्ठा bcm63xx_udc *udc, u32 off)
अणु
	वापस bcm_पढ़ोl(udc->iudma_regs + off);
पूर्ण

अटल अंतरभूत व्योम usb_dma_ग_लिखोl(काष्ठा bcm63xx_udc *udc, u32 val, u32 off)
अणु
	bcm_ग_लिखोl(val, udc->iudma_regs + off);
पूर्ण

अटल अंतरभूत u32 usb_dmac_पढ़ोl(काष्ठा bcm63xx_udc *udc, u32 off, पूर्णांक chan)
अणु
	वापस bcm_पढ़ोl(udc->iudma_regs + IUDMA_DMAC_OFFSET + off +
			(ENETDMA_CHAN_WIDTH * chan));
पूर्ण

अटल अंतरभूत व्योम usb_dmac_ग_लिखोl(काष्ठा bcm63xx_udc *udc, u32 val, u32 off,
					पूर्णांक chan)
अणु
	bcm_ग_लिखोl(val, udc->iudma_regs + IUDMA_DMAC_OFFSET + off +
			(ENETDMA_CHAN_WIDTH * chan));
पूर्ण

अटल अंतरभूत u32 usb_dmas_पढ़ोl(काष्ठा bcm63xx_udc *udc, u32 off, पूर्णांक chan)
अणु
	वापस bcm_पढ़ोl(udc->iudma_regs + IUDMA_DMAS_OFFSET + off +
			(ENETDMA_CHAN_WIDTH * chan));
पूर्ण

अटल अंतरभूत व्योम usb_dmas_ग_लिखोl(काष्ठा bcm63xx_udc *udc, u32 val, u32 off,
					पूर्णांक chan)
अणु
	bcm_ग_लिखोl(val, udc->iudma_regs + IUDMA_DMAS_OFFSET + off +
			(ENETDMA_CHAN_WIDTH * chan));
पूर्ण

अटल अंतरभूत व्योम set_घड़ीs(काष्ठा bcm63xx_udc *udc, bool is_enabled)
अणु
	अगर (is_enabled) अणु
		clk_enable(udc->usbh_clk);
		clk_enable(udc->usbd_clk);
		udelay(10);
	पूर्ण अन्यथा अणु
		clk_disable(udc->usbd_clk);
		clk_disable(udc->usbh_clk);
	पूर्ण
पूर्ण

/***********************************************************************
 * Low-level IUDMA / FIFO operations
 ***********************************************************************/

/**
 * bcm63xx_ep_dma_select - Helper function to set up the init_sel संकेत.
 * @udc: Reference to the device controller.
 * @idx: Desired init_sel value.
 *
 * The "init_sel" संकेत is used as a selection index क्रम both endpoपूर्णांकs
 * and IUDMA channels.  Since these करो not map 1:1, the use of this संकेत
 * depends on the context.
 */
अटल व्योम bcm63xx_ep_dma_select(काष्ठा bcm63xx_udc *udc, पूर्णांक idx)
अणु
	u32 val = usbd_पढ़ोl(udc, USBD_CONTROL_REG);

	val &= ~USBD_CONTROL_INIT_SEL_MASK;
	val |= idx << USBD_CONTROL_INIT_SEL_SHIFT;
	usbd_ग_लिखोl(udc, val, USBD_CONTROL_REG);
पूर्ण

/**
 * bcm63xx_set_stall - Enable/disable stall on one endpoपूर्णांक.
 * @udc: Reference to the device controller.
 * @bep: Endpoपूर्णांक on which to operate.
 * @is_stalled: true to enable stall, false to disable.
 *
 * See notes in bcm63xx_update_wedge() regarding स्वतःmatic clearing of
 * halt/stall conditions.
 */
अटल व्योम bcm63xx_set_stall(काष्ठा bcm63xx_udc *udc, काष्ठा bcm63xx_ep *bep,
	bool is_stalled)
अणु
	u32 val;

	val = USBD_STALL_UPDATE_MASK |
		(is_stalled ? USBD_STALL_ENABLE_MASK : 0) |
		(bep->ep_num << USBD_STALL_EPNUM_SHIFT);
	usbd_ग_लिखोl(udc, val, USBD_STALL_REG);
पूर्ण

/**
 * bcm63xx_fअगरo_setup - (Re)initialize FIFO boundaries and settings.
 * @udc: Reference to the device controller.
 *
 * These parameters depend on the USB link speed.  Settings are
 * per-IUDMA-channel-pair.
 */
अटल व्योम bcm63xx_fअगरo_setup(काष्ठा bcm63xx_udc *udc)
अणु
	पूर्णांक is_hs = udc->gadget.speed == USB_SPEED_HIGH;
	u32 i, val, rx_fअगरo_slot, tx_fअगरo_slot;

	/* set up FIFO boundaries and packet sizes; this is करोne in pairs */
	rx_fअगरo_slot = tx_fअगरo_slot = 0;
	क्रम (i = 0; i < BCM63XX_NUM_IUDMA; i += 2) अणु
		स्थिर काष्ठा iudma_ch_cfg *rx_cfg = &iudma_शेषs[i];
		स्थिर काष्ठा iudma_ch_cfg *tx_cfg = &iudma_शेषs[i + 1];

		bcm63xx_ep_dma_select(udc, i >> 1);

		val = (rx_fअगरo_slot << USBD_RXFIFO_CONFIG_START_SHIFT) |
			((rx_fअगरo_slot + rx_cfg->n_fअगरo_slots - 1) <<
			 USBD_RXFIFO_CONFIG_END_SHIFT);
		rx_fअगरo_slot += rx_cfg->n_fअगरo_slots;
		usbd_ग_लिखोl(udc, val, USBD_RXFIFO_CONFIG_REG);
		usbd_ग_लिखोl(udc,
			    is_hs ? rx_cfg->max_pkt_hs : rx_cfg->max_pkt_fs,
			    USBD_RXFIFO_EPSIZE_REG);

		val = (tx_fअगरo_slot << USBD_TXFIFO_CONFIG_START_SHIFT) |
			((tx_fअगरo_slot + tx_cfg->n_fअगरo_slots - 1) <<
			 USBD_TXFIFO_CONFIG_END_SHIFT);
		tx_fअगरo_slot += tx_cfg->n_fअगरo_slots;
		usbd_ग_लिखोl(udc, val, USBD_TXFIFO_CONFIG_REG);
		usbd_ग_लिखोl(udc,
			    is_hs ? tx_cfg->max_pkt_hs : tx_cfg->max_pkt_fs,
			    USBD_TXFIFO_EPSIZE_REG);

		usbd_पढ़ोl(udc, USBD_TXFIFO_EPSIZE_REG);
	पूर्ण
पूर्ण

/**
 * bcm63xx_fअगरo_reset_ep - Flush a single endpoपूर्णांक's FIFO.
 * @udc: Reference to the device controller.
 * @ep_num: Endpoपूर्णांक number.
 */
अटल व्योम bcm63xx_fअगरo_reset_ep(काष्ठा bcm63xx_udc *udc, पूर्णांक ep_num)
अणु
	u32 val;

	bcm63xx_ep_dma_select(udc, ep_num);

	val = usbd_पढ़ोl(udc, USBD_CONTROL_REG);
	val |= USBD_CONTROL_FIFO_RESET_MASK;
	usbd_ग_लिखोl(udc, val, USBD_CONTROL_REG);
	usbd_पढ़ोl(udc, USBD_CONTROL_REG);
पूर्ण

/**
 * bcm63xx_fअगरo_reset - Flush all hardware FIFOs.
 * @udc: Reference to the device controller.
 */
अटल व्योम bcm63xx_fअगरo_reset(काष्ठा bcm63xx_udc *udc)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < BCM63XX_NUM_FIFO_PAIRS; i++)
		bcm63xx_fअगरo_reset_ep(udc, i);
पूर्ण

/**
 * bcm63xx_ep_init - Initial (one-समय) endpoपूर्णांक initialization.
 * @udc: Reference to the device controller.
 */
अटल व्योम bcm63xx_ep_init(काष्ठा bcm63xx_udc *udc)
अणु
	u32 i, val;

	क्रम (i = 0; i < BCM63XX_NUM_IUDMA; i++) अणु
		स्थिर काष्ठा iudma_ch_cfg *cfg = &iudma_शेषs[i];

		अगर (cfg->ep_num < 0)
			जारी;

		bcm63xx_ep_dma_select(udc, cfg->ep_num);
		val = (cfg->ep_type << USBD_EPNUM_TYPEMAP_TYPE_SHIFT) |
			((i >> 1) << USBD_EPNUM_TYPEMAP_DMA_CH_SHIFT);
		usbd_ग_लिखोl(udc, val, USBD_EPNUM_TYPEMAP_REG);
	पूर्ण
पूर्ण

/**
 * bcm63xx_ep_setup - Configure per-endpoपूर्णांक settings.
 * @udc: Reference to the device controller.
 *
 * This needs to be rerun अगर the speed/cfg/पूर्णांकf/altपूर्णांकf changes.
 */
अटल व्योम bcm63xx_ep_setup(काष्ठा bcm63xx_udc *udc)
अणु
	u32 val, i;

	usbd_ग_लिखोl(udc, USBD_CSR_SETUPADDR_DEF, USBD_CSR_SETUPADDR_REG);

	क्रम (i = 0; i < BCM63XX_NUM_IUDMA; i++) अणु
		स्थिर काष्ठा iudma_ch_cfg *cfg = &iudma_शेषs[i];
		पूर्णांक max_pkt = udc->gadget.speed == USB_SPEED_HIGH ?
			      cfg->max_pkt_hs : cfg->max_pkt_fs;
		पूर्णांक idx = cfg->ep_num;

		udc->iudma[i].max_pkt = max_pkt;

		अगर (idx < 0)
			जारी;
		usb_ep_set_maxpacket_limit(&udc->bep[idx].ep, max_pkt);

		val = (idx << USBD_CSR_EP_LOG_SHIFT) |
		      (cfg->dir << USBD_CSR_EP_सूची_SHIFT) |
		      (cfg->ep_type << USBD_CSR_EP_TYPE_SHIFT) |
		      (udc->cfg << USBD_CSR_EP_CFG_SHIFT) |
		      (udc->अगरace << USBD_CSR_EP_IFACE_SHIFT) |
		      (udc->alt_अगरace << USBD_CSR_EP_ALTIFACE_SHIFT) |
		      (max_pkt << USBD_CSR_EP_MAXPKT_SHIFT);
		usbd_ग_लिखोl(udc, val, USBD_CSR_EP_REG(idx));
	पूर्ण
पूर्ण

/**
 * iudma_ग_लिखो - Queue a single IUDMA transaction.
 * @udc: Reference to the device controller.
 * @iudma: IUDMA channel to use.
 * @breq: Request containing the transaction data.
 *
 * For RX IUDMA, this will queue a single buffer descriptor, as RX IUDMA
 * करोes not honor SOP/EOP so the handling of multiple buffers is ambiguous.
 * So iudma_ग_लिखो() may be called several बार to fulfill a single
 * usb_request.
 *
 * For TX IUDMA, this can queue multiple buffer descriptors अगर needed.
 */
अटल व्योम iudma_ग_लिखो(काष्ठा bcm63xx_udc *udc, काष्ठा iudma_ch *iudma,
	काष्ठा bcm63xx_req *breq)
अणु
	पूर्णांक first_bd = 1, last_bd = 0, extra_zero_pkt = 0;
	अचिन्हित पूर्णांक bytes_left = breq->req.length - breq->offset;
	स्थिर पूर्णांक max_bd_bytes = !irq_coalesce && !iudma->is_tx ?
		iudma->max_pkt : IUDMA_MAX_FRAGMENT;

	iudma->n_bds_used = 0;
	breq->bd_bytes = 0;
	breq->iudma = iudma;

	अगर ((bytes_left % iudma->max_pkt == 0) && bytes_left && breq->req.zero)
		extra_zero_pkt = 1;

	करो अणु
		काष्ठा bcm_enet_desc *d = iudma->ग_लिखो_bd;
		u32 dmaflags = 0;
		अचिन्हित पूर्णांक n_bytes;

		अगर (d == iudma->end_bd) अणु
			dmaflags |= DMADESC_WRAP_MASK;
			iudma->ग_लिखो_bd = iudma->bd_ring;
		पूर्ण अन्यथा अणु
			iudma->ग_लिखो_bd++;
		पूर्ण
		iudma->n_bds_used++;

		n_bytes = min_t(पूर्णांक, bytes_left, max_bd_bytes);
		अगर (n_bytes)
			dmaflags |= n_bytes << DMADESC_LENGTH_SHIFT;
		अन्यथा
			dmaflags |= (1 << DMADESC_LENGTH_SHIFT) |
				    DMADESC_USB_ZERO_MASK;

		dmaflags |= DMADESC_OWNER_MASK;
		अगर (first_bd) अणु
			dmaflags |= DMADESC_SOP_MASK;
			first_bd = 0;
		पूर्ण

		/*
		 * extra_zero_pkt क्रमces one more iteration through the loop
		 * after all data is queued up, to send the zero packet
		 */
		अगर (extra_zero_pkt && !bytes_left)
			extra_zero_pkt = 0;

		अगर (!iudma->is_tx || iudma->n_bds_used == iudma->n_bds ||
		    (n_bytes == bytes_left && !extra_zero_pkt)) अणु
			last_bd = 1;
			dmaflags |= DMADESC_EOP_MASK;
		पूर्ण

		d->address = breq->req.dma + breq->offset;
		mb();
		d->len_stat = dmaflags;

		breq->offset += n_bytes;
		breq->bd_bytes += n_bytes;
		bytes_left -= n_bytes;
	पूर्ण जबतक (!last_bd);

	usb_dmac_ग_लिखोl(udc, ENETDMAC_CHANCFG_EN_MASK,
			ENETDMAC_CHANCFG_REG, iudma->ch_idx);
पूर्ण

/**
 * iudma_पढ़ो - Check क्रम IUDMA buffer completion.
 * @udc: Reference to the device controller.
 * @iudma: IUDMA channel to use.
 *
 * This checks to see अगर ALL of the outstanding BDs on the DMA channel
 * have been filled.  If so, it वापसs the actual transfer length;
 * otherwise it वापसs -EBUSY.
 */
अटल पूर्णांक iudma_पढ़ो(काष्ठा bcm63xx_udc *udc, काष्ठा iudma_ch *iudma)
अणु
	पूर्णांक i, actual_len = 0;
	काष्ठा bcm_enet_desc *d = iudma->पढ़ो_bd;

	अगर (!iudma->n_bds_used)
		वापस -EINVAL;

	क्रम (i = 0; i < iudma->n_bds_used; i++) अणु
		u32 dmaflags;

		dmaflags = d->len_stat;

		अगर (dmaflags & DMADESC_OWNER_MASK)
			वापस -EBUSY;

		actual_len += (dmaflags & DMADESC_LENGTH_MASK) >>
			      DMADESC_LENGTH_SHIFT;
		अगर (d == iudma->end_bd)
			d = iudma->bd_ring;
		अन्यथा
			d++;
	पूर्ण

	iudma->पढ़ो_bd = d;
	iudma->n_bds_used = 0;
	वापस actual_len;
पूर्ण

/**
 * iudma_reset_channel - Stop DMA on a single channel.
 * @udc: Reference to the device controller.
 * @iudma: IUDMA channel to reset.
 */
अटल व्योम iudma_reset_channel(काष्ठा bcm63xx_udc *udc, काष्ठा iudma_ch *iudma)
अणु
	पूर्णांक समयout = IUDMA_RESET_TIMEOUT_US;
	काष्ठा bcm_enet_desc *d;
	पूर्णांक ch_idx = iudma->ch_idx;

	अगर (!iudma->is_tx)
		bcm63xx_fअगरo_reset_ep(udc, max(0, iudma->ep_num));

	/* stop DMA, then रुको क्रम the hardware to wrap up */
	usb_dmac_ग_लिखोl(udc, 0, ENETDMAC_CHANCFG_REG, ch_idx);

	जबतक (usb_dmac_पढ़ोl(udc, ENETDMAC_CHANCFG_REG, ch_idx) &
				   ENETDMAC_CHANCFG_EN_MASK) अणु
		udelay(1);

		/* repeatedly flush the FIFO data until the BD completes */
		अगर (iudma->is_tx && iudma->ep_num >= 0)
			bcm63xx_fअगरo_reset_ep(udc, iudma->ep_num);

		अगर (!समयout--) अणु
			dev_err(udc->dev, "can't reset IUDMA channel %d\n",
				ch_idx);
			अवरोध;
		पूर्ण
		अगर (समयout == IUDMA_RESET_TIMEOUT_US / 2) अणु
			dev_warn(udc->dev, "forcibly halting IUDMA channel %d\n",
				 ch_idx);
			usb_dmac_ग_लिखोl(udc, ENETDMAC_CHANCFG_BUFHALT_MASK,
					ENETDMAC_CHANCFG_REG, ch_idx);
		पूर्ण
	पूर्ण
	usb_dmac_ग_लिखोl(udc, ~0, ENETDMAC_IR_REG, ch_idx);

	/* करोn't leave "live" HW-owned entries क्रम the next guy to step on */
	क्रम (d = iudma->bd_ring; d <= iudma->end_bd; d++)
		d->len_stat = 0;
	mb();

	iudma->पढ़ो_bd = iudma->ग_लिखो_bd = iudma->bd_ring;
	iudma->n_bds_used = 0;

	/* set up IRQs, UBUS burst size, and BD base क्रम this channel */
	usb_dmac_ग_लिखोl(udc, ENETDMAC_IR_BUFDONE_MASK,
			ENETDMAC_IRMASK_REG, ch_idx);
	usb_dmac_ग_लिखोl(udc, 8, ENETDMAC_MAXBURST_REG, ch_idx);

	usb_dmas_ग_लिखोl(udc, iudma->bd_ring_dma, ENETDMAS_RSTART_REG, ch_idx);
	usb_dmas_ग_लिखोl(udc, 0, ENETDMAS_SRAM2_REG, ch_idx);
पूर्ण

/**
 * iudma_init_channel - One-समय IUDMA channel initialization.
 * @udc: Reference to the device controller.
 * @ch_idx: Channel to initialize.
 */
अटल पूर्णांक iudma_init_channel(काष्ठा bcm63xx_udc *udc, अचिन्हित पूर्णांक ch_idx)
अणु
	काष्ठा iudma_ch *iudma = &udc->iudma[ch_idx];
	स्थिर काष्ठा iudma_ch_cfg *cfg = &iudma_शेषs[ch_idx];
	अचिन्हित पूर्णांक n_bds = cfg->n_bds;
	काष्ठा bcm63xx_ep *bep = शून्य;

	iudma->ep_num = cfg->ep_num;
	iudma->ch_idx = ch_idx;
	iudma->is_tx = !!(ch_idx & 0x01);
	अगर (iudma->ep_num >= 0) अणु
		bep = &udc->bep[iudma->ep_num];
		bep->iudma = iudma;
		INIT_LIST_HEAD(&bep->queue);
	पूर्ण

	iudma->bep = bep;
	iudma->udc = udc;

	/* ep0 is always active; others are controlled by the gadget driver */
	अगर (iudma->ep_num <= 0)
		iudma->enabled = true;

	iudma->n_bds = n_bds;
	iudma->bd_ring = dmam_alloc_coherent(udc->dev,
		n_bds * माप(काष्ठा bcm_enet_desc),
		&iudma->bd_ring_dma, GFP_KERNEL);
	अगर (!iudma->bd_ring)
		वापस -ENOMEM;
	iudma->end_bd = &iudma->bd_ring[n_bds - 1];

	वापस 0;
पूर्ण

/**
 * iudma_init - One-समय initialization of all IUDMA channels.
 * @udc: Reference to the device controller.
 *
 * Enable DMA, flush channels, and enable global IUDMA IRQs.
 */
अटल पूर्णांक iudma_init(काष्ठा bcm63xx_udc *udc)
अणु
	पूर्णांक i, rc;

	usb_dma_ग_लिखोl(udc, ENETDMA_CFG_EN_MASK, ENETDMA_CFG_REG);

	क्रम (i = 0; i < BCM63XX_NUM_IUDMA; i++) अणु
		rc = iudma_init_channel(udc, i);
		अगर (rc)
			वापस rc;
		iudma_reset_channel(udc, &udc->iudma[i]);
	पूर्ण

	usb_dma_ग_लिखोl(udc, BIT(BCM63XX_NUM_IUDMA)-1, ENETDMA_GLB_IRQMASK_REG);
	वापस 0;
पूर्ण

/**
 * iudma_uninit - Uninitialize IUDMA channels.
 * @udc: Reference to the device controller.
 *
 * Kill global IUDMA IRQs, flush channels, and समाप्त DMA.
 */
अटल व्योम iudma_uninit(काष्ठा bcm63xx_udc *udc)
अणु
	पूर्णांक i;

	usb_dma_ग_लिखोl(udc, 0, ENETDMA_GLB_IRQMASK_REG);

	क्रम (i = 0; i < BCM63XX_NUM_IUDMA; i++)
		iudma_reset_channel(udc, &udc->iudma[i]);

	usb_dma_ग_लिखोl(udc, 0, ENETDMA_CFG_REG);
पूर्ण

/***********************************************************************
 * Other low-level USBD operations
 ***********************************************************************/

/**
 * bcm63xx_set_ctrl_irqs - Mask/unmask control path पूर्णांकerrupts.
 * @udc: Reference to the device controller.
 * @enable_irqs: true to enable, false to disable.
 */
अटल व्योम bcm63xx_set_ctrl_irqs(काष्ठा bcm63xx_udc *udc, bool enable_irqs)
अणु
	u32 val;

	usbd_ग_लिखोl(udc, 0, USBD_STATUS_REG);

	val = BIT(USBD_EVENT_IRQ_USB_RESET) |
	      BIT(USBD_EVENT_IRQ_SETUP) |
	      BIT(USBD_EVENT_IRQ_SETCFG) |
	      BIT(USBD_EVENT_IRQ_SETINTF) |
	      BIT(USBD_EVENT_IRQ_USB_LINK);
	usbd_ग_लिखोl(udc, enable_irqs ? val : 0, USBD_EVENT_IRQ_MASK_REG);
	usbd_ग_लिखोl(udc, val, USBD_EVENT_IRQ_STATUS_REG);
पूर्ण

/**
 * bcm63xx_select_phy_mode - Select between USB device and host mode.
 * @udc: Reference to the device controller.
 * @is_device: true क्रम device, false क्रम host.
 *
 * This should probably be reworked to use the drivers/usb/otg
 * infraकाष्ठाure.
 *
 * By शेष, the AFE/pullups are disabled in device mode, until
 * bcm63xx_select_pullup() is called.
 */
अटल व्योम bcm63xx_select_phy_mode(काष्ठा bcm63xx_udc *udc, bool is_device)
अणु
	u32 val, porपंचांगask = BIT(udc->pd->port_no);

	अगर (BCMCPU_IS_6328()) अणु
		/* configure pinmux to sense VBUS संकेत */
		val = bcm_gpio_पढ़ोl(GPIO_PINMUX_OTHR_REG);
		val &= ~GPIO_PINMUX_OTHR_6328_USB_MASK;
		val |= is_device ? GPIO_PINMUX_OTHR_6328_USB_DEV :
			       GPIO_PINMUX_OTHR_6328_USB_HOST;
		bcm_gpio_ग_लिखोl(val, GPIO_PINMUX_OTHR_REG);
	पूर्ण

	val = bcm_rset_पढ़ोl(RSET_USBH_PRIV, USBH_PRIV_UTMI_CTL_6368_REG);
	अगर (is_device) अणु
		val |= (porपंचांगask << USBH_PRIV_UTMI_CTL_HOSTB_SHIFT);
		val |= (porपंचांगask << USBH_PRIV_UTMI_CTL_NODRIV_SHIFT);
	पूर्ण अन्यथा अणु
		val &= ~(porपंचांगask << USBH_PRIV_UTMI_CTL_HOSTB_SHIFT);
		val &= ~(porपंचांगask << USBH_PRIV_UTMI_CTL_NODRIV_SHIFT);
	पूर्ण
	bcm_rset_ग_लिखोl(RSET_USBH_PRIV, val, USBH_PRIV_UTMI_CTL_6368_REG);

	val = bcm_rset_पढ़ोl(RSET_USBH_PRIV, USBH_PRIV_SWAP_6368_REG);
	अगर (is_device)
		val |= USBH_PRIV_SWAP_USBD_MASK;
	अन्यथा
		val &= ~USBH_PRIV_SWAP_USBD_MASK;
	bcm_rset_ग_लिखोl(RSET_USBH_PRIV, val, USBH_PRIV_SWAP_6368_REG);
पूर्ण

/**
 * bcm63xx_select_pullup - Enable/disable the pullup on D+
 * @udc: Reference to the device controller.
 * @is_on: true to enable the pullup, false to disable.
 *
 * If the pullup is active, the host will sense a FS/HS device connected to
 * the port.  If the pullup is inactive, the host will think the USB
 * device has been disconnected.
 */
अटल व्योम bcm63xx_select_pullup(काष्ठा bcm63xx_udc *udc, bool is_on)
अणु
	u32 val, porपंचांगask = BIT(udc->pd->port_no);

	val = bcm_rset_पढ़ोl(RSET_USBH_PRIV, USBH_PRIV_UTMI_CTL_6368_REG);
	अगर (is_on)
		val &= ~(porपंचांगask << USBH_PRIV_UTMI_CTL_NODRIV_SHIFT);
	अन्यथा
		val |= (porपंचांगask << USBH_PRIV_UTMI_CTL_NODRIV_SHIFT);
	bcm_rset_ग_लिखोl(RSET_USBH_PRIV, val, USBH_PRIV_UTMI_CTL_6368_REG);
पूर्ण

/**
 * bcm63xx_uninit_udc_hw - Shut करोwn the hardware prior to driver removal.
 * @udc: Reference to the device controller.
 *
 * This just masks the IUDMA IRQs and releases the घड़ीs.  It is assumed
 * that bcm63xx_udc_stop() has alपढ़ोy run, and the घड़ीs are stopped.
 */
अटल व्योम bcm63xx_uninit_udc_hw(काष्ठा bcm63xx_udc *udc)
अणु
	set_घड़ीs(udc, true);
	iudma_uninit(udc);
	set_घड़ीs(udc, false);

	clk_put(udc->usbd_clk);
	clk_put(udc->usbh_clk);
पूर्ण

/**
 * bcm63xx_init_udc_hw - Initialize the controller hardware and data काष्ठाures.
 * @udc: Reference to the device controller.
 */
अटल पूर्णांक bcm63xx_init_udc_hw(काष्ठा bcm63xx_udc *udc)
अणु
	पूर्णांक i, rc = 0;
	u32 val;

	udc->ep0_ctrl_buf = devm_kzalloc(udc->dev, BCM63XX_MAX_CTRL_PKT,
					 GFP_KERNEL);
	अगर (!udc->ep0_ctrl_buf)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&udc->gadget.ep_list);
	क्रम (i = 0; i < BCM63XX_NUM_EP; i++) अणु
		काष्ठा bcm63xx_ep *bep = &udc->bep[i];

		bep->ep.name = bcm63xx_ep_info[i].name;
		bep->ep.caps = bcm63xx_ep_info[i].caps;
		bep->ep_num = i;
		bep->ep.ops = &bcm63xx_udc_ep_ops;
		list_add_tail(&bep->ep.ep_list, &udc->gadget.ep_list);
		bep->halted = 0;
		usb_ep_set_maxpacket_limit(&bep->ep, BCM63XX_MAX_CTRL_PKT);
		bep->udc = udc;
		bep->ep.desc = शून्य;
		INIT_LIST_HEAD(&bep->queue);
	पूर्ण

	udc->gadget.ep0 = &udc->bep[0].ep;
	list_del(&udc->bep[0].ep.ep_list);

	udc->gadget.speed = USB_SPEED_UNKNOWN;
	udc->ep0state = EP0_SHUTDOWN;

	udc->usbh_clk = clk_get(udc->dev, "usbh");
	अगर (IS_ERR(udc->usbh_clk))
		वापस -EIO;

	udc->usbd_clk = clk_get(udc->dev, "usbd");
	अगर (IS_ERR(udc->usbd_clk)) अणु
		clk_put(udc->usbh_clk);
		वापस -EIO;
	पूर्ण

	set_घड़ीs(udc, true);

	val = USBD_CONTROL_AUTO_CSRS_MASK |
	      USBD_CONTROL_DONE_CSRS_MASK |
	      (irq_coalesce ? USBD_CONTROL_RXZSCFG_MASK : 0);
	usbd_ग_लिखोl(udc, val, USBD_CONTROL_REG);

	val = USBD_STRAPS_APP_SELF_PWR_MASK |
	      USBD_STRAPS_APP_RAM_IF_MASK |
	      USBD_STRAPS_APP_CSRPRGSUP_MASK |
	      USBD_STRAPS_APP_8BITPHY_MASK |
	      USBD_STRAPS_APP_RMTWKUP_MASK;

	अगर (udc->gadget.max_speed == USB_SPEED_HIGH)
		val |= (BCM63XX_SPD_HIGH << USBD_STRAPS_SPEED_SHIFT);
	अन्यथा
		val |= (BCM63XX_SPD_FULL << USBD_STRAPS_SPEED_SHIFT);
	usbd_ग_लिखोl(udc, val, USBD_STRAPS_REG);

	bcm63xx_set_ctrl_irqs(udc, false);

	usbd_ग_लिखोl(udc, 0, USBD_EVENT_IRQ_CFG_LO_REG);

	val = USBD_EVENT_IRQ_CFG_FALLING(USBD_EVENT_IRQ_ENUM_ON) |
	      USBD_EVENT_IRQ_CFG_FALLING(USBD_EVENT_IRQ_SET_CSRS);
	usbd_ग_लिखोl(udc, val, USBD_EVENT_IRQ_CFG_HI_REG);

	rc = iudma_init(udc);
	set_घड़ीs(udc, false);
	अगर (rc)
		bcm63xx_uninit_udc_hw(udc);

	वापस 0;
पूर्ण

/***********************************************************************
 * Standard EP gadget operations
 ***********************************************************************/

/**
 * bcm63xx_ep_enable - Enable one endpoपूर्णांक.
 * @ep: Endpoपूर्णांक to enable.
 * @desc: Contains max packet, direction, etc.
 *
 * Most of the endpoपूर्णांक parameters are fixed in this controller, so there
 * isn't much क्रम this function to करो.
 */
अटल पूर्णांक bcm63xx_ep_enable(काष्ठा usb_ep *ep,
	स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *desc)
अणु
	काष्ठा bcm63xx_ep *bep = our_ep(ep);
	काष्ठा bcm63xx_udc *udc = bep->udc;
	काष्ठा iudma_ch *iudma = bep->iudma;
	अचिन्हित दीर्घ flags;

	अगर (!ep || !desc || ep->name == bcm63xx_ep0name)
		वापस -EINVAL;

	अगर (!udc->driver)
		वापस -ESHUTDOWN;

	spin_lock_irqsave(&udc->lock, flags);
	अगर (iudma->enabled) अणु
		spin_unlock_irqrestore(&udc->lock, flags);
		वापस -EINVAL;
	पूर्ण

	iudma->enabled = true;
	BUG_ON(!list_empty(&bep->queue));

	iudma_reset_channel(udc, iudma);

	bep->halted = 0;
	bcm63xx_set_stall(udc, bep, false);
	clear_bit(bep->ep_num, &udc->wedgemap);

	ep->desc = desc;
	ep->maxpacket = usb_endpoपूर्णांक_maxp(desc);

	spin_unlock_irqrestore(&udc->lock, flags);
	वापस 0;
पूर्ण

/**
 * bcm63xx_ep_disable - Disable one endpoपूर्णांक.
 * @ep: Endpoपूर्णांक to disable.
 */
अटल पूर्णांक bcm63xx_ep_disable(काष्ठा usb_ep *ep)
अणु
	काष्ठा bcm63xx_ep *bep = our_ep(ep);
	काष्ठा bcm63xx_udc *udc = bep->udc;
	काष्ठा iudma_ch *iudma = bep->iudma;
	काष्ठा bcm63xx_req *breq, *n;
	अचिन्हित दीर्घ flags;

	अगर (!ep || !ep->desc)
		वापस -EINVAL;

	spin_lock_irqsave(&udc->lock, flags);
	अगर (!iudma->enabled) अणु
		spin_unlock_irqrestore(&udc->lock, flags);
		वापस -EINVAL;
	पूर्ण
	iudma->enabled = false;

	iudma_reset_channel(udc, iudma);

	अगर (!list_empty(&bep->queue)) अणु
		list_क्रम_each_entry_safe(breq, n, &bep->queue, queue) अणु
			usb_gadget_unmap_request(&udc->gadget, &breq->req,
						 iudma->is_tx);
			list_del(&breq->queue);
			breq->req.status = -ESHUTDOWN;

			spin_unlock_irqrestore(&udc->lock, flags);
			usb_gadget_giveback_request(&iudma->bep->ep, &breq->req);
			spin_lock_irqsave(&udc->lock, flags);
		पूर्ण
	पूर्ण
	ep->desc = शून्य;

	spin_unlock_irqrestore(&udc->lock, flags);
	वापस 0;
पूर्ण

/**
 * bcm63xx_udc_alloc_request - Allocate a new request.
 * @ep: Endpoपूर्णांक associated with the request.
 * @mem_flags: Flags to pass to kzalloc().
 */
अटल काष्ठा usb_request *bcm63xx_udc_alloc_request(काष्ठा usb_ep *ep,
	gfp_t mem_flags)
अणु
	काष्ठा bcm63xx_req *breq;

	breq = kzalloc(माप(*breq), mem_flags);
	अगर (!breq)
		वापस शून्य;
	वापस &breq->req;
पूर्ण

/**
 * bcm63xx_udc_मुक्त_request - Free a request.
 * @ep: Endpoपूर्णांक associated with the request.
 * @req: Request to मुक्त.
 */
अटल व्योम bcm63xx_udc_मुक्त_request(काष्ठा usb_ep *ep,
	काष्ठा usb_request *req)
अणु
	काष्ठा bcm63xx_req *breq = our_req(req);
	kमुक्त(breq);
पूर्ण

/**
 * bcm63xx_udc_queue - Queue up a new request.
 * @ep: Endpoपूर्णांक associated with the request.
 * @req: Request to add.
 * @mem_flags: Unused.
 *
 * If the queue is empty, start this request immediately.  Otherwise, add
 * it to the list.
 *
 * ep0 replies are sent through this function from the gadget driver, but
 * they are treated dअगरferently because they need to be handled by the ep0
 * state machine.  (Someबार they are replies to control requests that
 * were spoofed by this driver, and so they shouldn't be transmitted at all.)
 */
अटल पूर्णांक bcm63xx_udc_queue(काष्ठा usb_ep *ep, काष्ठा usb_request *req,
	gfp_t mem_flags)
अणु
	काष्ठा bcm63xx_ep *bep = our_ep(ep);
	काष्ठा bcm63xx_udc *udc = bep->udc;
	काष्ठा bcm63xx_req *breq = our_req(req);
	अचिन्हित दीर्घ flags;
	पूर्णांक rc = 0;

	अगर (unlikely(!req || !req->complete || !req->buf || !ep))
		वापस -EINVAL;

	req->actual = 0;
	req->status = 0;
	breq->offset = 0;

	अगर (bep == &udc->bep[0]) अणु
		/* only one reply per request, please */
		अगर (udc->ep0_reply)
			वापस -EINVAL;

		udc->ep0_reply = req;
		schedule_work(&udc->ep0_wq);
		वापस 0;
	पूर्ण

	spin_lock_irqsave(&udc->lock, flags);
	अगर (!bep->iudma->enabled) अणु
		rc = -ESHUTDOWN;
		जाओ out;
	पूर्ण

	rc = usb_gadget_map_request(&udc->gadget, req, bep->iudma->is_tx);
	अगर (rc == 0) अणु
		list_add_tail(&breq->queue, &bep->queue);
		अगर (list_is_singular(&bep->queue))
			iudma_ग_लिखो(udc, bep->iudma, breq);
	पूर्ण

out:
	spin_unlock_irqrestore(&udc->lock, flags);
	वापस rc;
पूर्ण

/**
 * bcm63xx_udc_dequeue - Remove a pending request from the queue.
 * @ep: Endpoपूर्णांक associated with the request.
 * @req: Request to हटाओ.
 *
 * If the request is not at the head of the queue, this is easy - just nuke
 * it.  If the request is at the head of the queue, we'll need to stop the
 * DMA transaction and then queue up the successor.
 */
अटल पूर्णांक bcm63xx_udc_dequeue(काष्ठा usb_ep *ep, काष्ठा usb_request *req)
अणु
	काष्ठा bcm63xx_ep *bep = our_ep(ep);
	काष्ठा bcm63xx_udc *udc = bep->udc;
	काष्ठा bcm63xx_req *breq = our_req(req), *cur;
	अचिन्हित दीर्घ flags;
	पूर्णांक rc = 0;

	spin_lock_irqsave(&udc->lock, flags);
	अगर (list_empty(&bep->queue)) अणु
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	cur = list_first_entry(&bep->queue, काष्ठा bcm63xx_req, queue);
	usb_gadget_unmap_request(&udc->gadget, &breq->req, bep->iudma->is_tx);

	अगर (breq == cur) अणु
		iudma_reset_channel(udc, bep->iudma);
		list_del(&breq->queue);

		अगर (!list_empty(&bep->queue)) अणु
			काष्ठा bcm63xx_req *next;

			next = list_first_entry(&bep->queue,
				काष्ठा bcm63xx_req, queue);
			iudma_ग_लिखो(udc, bep->iudma, next);
		पूर्ण
	पूर्ण अन्यथा अणु
		list_del(&breq->queue);
	पूर्ण

out:
	spin_unlock_irqrestore(&udc->lock, flags);

	req->status = -ESHUTDOWN;
	req->complete(ep, req);

	वापस rc;
पूर्ण

/**
 * bcm63xx_udc_set_halt - Enable/disable STALL flag in the hardware.
 * @ep: Endpoपूर्णांक to halt.
 * @value: Zero to clear halt; nonzero to set halt.
 *
 * See comments in bcm63xx_update_wedge().
 */
अटल पूर्णांक bcm63xx_udc_set_halt(काष्ठा usb_ep *ep, पूर्णांक value)
अणु
	काष्ठा bcm63xx_ep *bep = our_ep(ep);
	काष्ठा bcm63xx_udc *udc = bep->udc;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&udc->lock, flags);
	bcm63xx_set_stall(udc, bep, !!value);
	bep->halted = value;
	spin_unlock_irqrestore(&udc->lock, flags);

	वापस 0;
पूर्ण

/**
 * bcm63xx_udc_set_wedge - Stall the endpoपूर्णांक until the next reset.
 * @ep: Endpoपूर्णांक to wedge.
 *
 * See comments in bcm63xx_update_wedge().
 */
अटल पूर्णांक bcm63xx_udc_set_wedge(काष्ठा usb_ep *ep)
अणु
	काष्ठा bcm63xx_ep *bep = our_ep(ep);
	काष्ठा bcm63xx_udc *udc = bep->udc;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&udc->lock, flags);
	set_bit(bep->ep_num, &udc->wedgemap);
	bcm63xx_set_stall(udc, bep, true);
	spin_unlock_irqrestore(&udc->lock, flags);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा usb_ep_ops bcm63xx_udc_ep_ops = अणु
	.enable		= bcm63xx_ep_enable,
	.disable	= bcm63xx_ep_disable,

	.alloc_request	= bcm63xx_udc_alloc_request,
	.मुक्त_request	= bcm63xx_udc_मुक्त_request,

	.queue		= bcm63xx_udc_queue,
	.dequeue	= bcm63xx_udc_dequeue,

	.set_halt	= bcm63xx_udc_set_halt,
	.set_wedge	= bcm63xx_udc_set_wedge,
पूर्ण;

/***********************************************************************
 * EP0 handling
 ***********************************************************************/

/**
 * bcm63xx_ep0_setup_callback - Drop spinlock to invoke ->setup callback.
 * @udc: Reference to the device controller.
 * @ctrl: 8-byte SETUP request.
 */
अटल पूर्णांक bcm63xx_ep0_setup_callback(काष्ठा bcm63xx_udc *udc,
	काष्ठा usb_ctrlrequest *ctrl)
अणु
	पूर्णांक rc;

	spin_unlock_irq(&udc->lock);
	rc = udc->driver->setup(&udc->gadget, ctrl);
	spin_lock_irq(&udc->lock);
	वापस rc;
पूर्ण

/**
 * bcm63xx_ep0_spoof_set_cfg - Synthesize a SET_CONFIGURATION request.
 * @udc: Reference to the device controller.
 *
 * Many standard requests are handled स्वतःmatically in the hardware, but
 * we still need to pass them to the gadget driver so that it can
 * reconfigure the पूर्णांकerfaces/endpoपूर्णांकs अगर necessary.
 *
 * Unक्रमtunately we are not able to send a STALL response अगर the host
 * requests an invalid configuration.  If this happens, we'll have to be
 * content with prपूर्णांकing a warning.
 */
अटल पूर्णांक bcm63xx_ep0_spoof_set_cfg(काष्ठा bcm63xx_udc *udc)
अणु
	काष्ठा usb_ctrlrequest ctrl;
	पूर्णांक rc;

	ctrl.bRequestType = USB_सूची_OUT | USB_RECIP_DEVICE;
	ctrl.bRequest = USB_REQ_SET_CONFIGURATION;
	ctrl.wValue = cpu_to_le16(udc->cfg);
	ctrl.wIndex = 0;
	ctrl.wLength = 0;

	rc = bcm63xx_ep0_setup_callback(udc, &ctrl);
	अगर (rc < 0) अणु
		dev_warn_ratelimited(udc->dev,
			"hardware auto-acked bad SET_CONFIGURATION(%d) request\n",
			udc->cfg);
	पूर्ण
	वापस rc;
पूर्ण

/**
 * bcm63xx_ep0_spoof_set_अगरace - Synthesize a SET_INTERFACE request.
 * @udc: Reference to the device controller.
 */
अटल पूर्णांक bcm63xx_ep0_spoof_set_अगरace(काष्ठा bcm63xx_udc *udc)
अणु
	काष्ठा usb_ctrlrequest ctrl;
	पूर्णांक rc;

	ctrl.bRequestType = USB_सूची_OUT | USB_RECIP_INTERFACE;
	ctrl.bRequest = USB_REQ_SET_INTERFACE;
	ctrl.wValue = cpu_to_le16(udc->alt_अगरace);
	ctrl.wIndex = cpu_to_le16(udc->अगरace);
	ctrl.wLength = 0;

	rc = bcm63xx_ep0_setup_callback(udc, &ctrl);
	अगर (rc < 0) अणु
		dev_warn_ratelimited(udc->dev,
			"hardware auto-acked bad SET_INTERFACE(%d,%d) request\n",
			udc->अगरace, udc->alt_अगरace);
	पूर्ण
	वापस rc;
पूर्ण

/**
 * bcm63xx_ep0_map_ग_लिखो - dma_map and iudma_ग_लिखो a single request.
 * @udc: Reference to the device controller.
 * @ch_idx: IUDMA channel number.
 * @req: USB gadget layer representation of the request.
 */
अटल व्योम bcm63xx_ep0_map_ग_लिखो(काष्ठा bcm63xx_udc *udc, पूर्णांक ch_idx,
	काष्ठा usb_request *req)
अणु
	काष्ठा bcm63xx_req *breq = our_req(req);
	काष्ठा iudma_ch *iudma = &udc->iudma[ch_idx];

	BUG_ON(udc->ep0_request);
	udc->ep0_request = req;

	req->actual = 0;
	breq->offset = 0;
	usb_gadget_map_request(&udc->gadget, req, iudma->is_tx);
	iudma_ग_लिखो(udc, iudma, breq);
पूर्ण

/**
 * bcm63xx_ep0_complete - Set completion status and "stage" the callback.
 * @udc: Reference to the device controller.
 * @req: USB gadget layer representation of the request.
 * @status: Status to वापस to the gadget driver.
 */
अटल व्योम bcm63xx_ep0_complete(काष्ठा bcm63xx_udc *udc,
	काष्ठा usb_request *req, पूर्णांक status)
अणु
	req->status = status;
	अगर (status)
		req->actual = 0;
	अगर (req->complete) अणु
		spin_unlock_irq(&udc->lock);
		req->complete(&udc->bep[0].ep, req);
		spin_lock_irq(&udc->lock);
	पूर्ण
पूर्ण

/**
 * bcm63xx_ep0_nuke_reply - Abort request from the gadget driver due to
 *   reset/shutकरोwn.
 * @udc: Reference to the device controller.
 * @is_tx: Nonzero क्रम TX (IN), zero क्रम RX (OUT).
 */
अटल व्योम bcm63xx_ep0_nuke_reply(काष्ठा bcm63xx_udc *udc, पूर्णांक is_tx)
अणु
	काष्ठा usb_request *req = udc->ep0_reply;

	udc->ep0_reply = शून्य;
	usb_gadget_unmap_request(&udc->gadget, req, is_tx);
	अगर (udc->ep0_request == req) अणु
		udc->ep0_req_completed = 0;
		udc->ep0_request = शून्य;
	पूर्ण
	bcm63xx_ep0_complete(udc, req, -ESHUTDOWN);
पूर्ण

/**
 * bcm63xx_ep0_पढ़ो_complete - Close out the pending ep0 request; वापस
 *   transfer len.
 * @udc: Reference to the device controller.
 */
अटल पूर्णांक bcm63xx_ep0_पढ़ो_complete(काष्ठा bcm63xx_udc *udc)
अणु
	काष्ठा usb_request *req = udc->ep0_request;

	udc->ep0_req_completed = 0;
	udc->ep0_request = शून्य;

	वापस req->actual;
पूर्ण

/**
 * bcm63xx_ep0_पूर्णांकernal_request - Helper function to submit an ep0 request.
 * @udc: Reference to the device controller.
 * @ch_idx: IUDMA channel number.
 * @length: Number of bytes to TX/RX.
 *
 * Used क्रम simple transfers perक्रमmed by the ep0 worker.  This will always
 * use ep0_ctrl_req / ep0_ctrl_buf.
 */
अटल व्योम bcm63xx_ep0_पूर्णांकernal_request(काष्ठा bcm63xx_udc *udc, पूर्णांक ch_idx,
	पूर्णांक length)
अणु
	काष्ठा usb_request *req = &udc->ep0_ctrl_req.req;

	req->buf = udc->ep0_ctrl_buf;
	req->length = length;
	req->complete = शून्य;

	bcm63xx_ep0_map_ग_लिखो(udc, ch_idx, req);
पूर्ण

/**
 * bcm63xx_ep0_करो_setup - Parse new SETUP packet and decide how to handle it.
 * @udc: Reference to the device controller.
 *
 * EP0_IDLE probably shouldn't ever happen.  EP0_REQUEUE means we're पढ़ोy
 * क्रम the next packet.  Anything अन्यथा means the transaction requires multiple
 * stages of handling.
 */
अटल क्रमागत bcm63xx_ep0_state bcm63xx_ep0_करो_setup(काष्ठा bcm63xx_udc *udc)
अणु
	पूर्णांक rc;
	काष्ठा usb_ctrlrequest *ctrl = (व्योम *)udc->ep0_ctrl_buf;

	rc = bcm63xx_ep0_पढ़ो_complete(udc);

	अगर (rc < 0) अणु
		dev_err(udc->dev, "missing SETUP packet\n");
		वापस EP0_IDLE;
	पूर्ण

	/*
	 * Handle 0-byte IN STATUS acknowledgement.  The hardware करोesn't
	 * ALWAYS deliver these 100% of the समय, so अगर we happen to see one,
	 * just throw it away.
	 */
	अगर (rc == 0)
		वापस EP0_REQUEUE;

	/* Drop malक्रमmed SETUP packets */
	अगर (rc != माप(*ctrl)) अणु
		dev_warn_ratelimited(udc->dev,
			"malformed SETUP packet (%d bytes)\n", rc);
		वापस EP0_REQUEUE;
	पूर्ण

	/* Process new SETUP packet arriving on ep0 */
	rc = bcm63xx_ep0_setup_callback(udc, ctrl);
	अगर (rc < 0) अणु
		bcm63xx_set_stall(udc, &udc->bep[0], true);
		वापस EP0_REQUEUE;
	पूर्ण

	अगर (!ctrl->wLength)
		वापस EP0_REQUEUE;
	अन्यथा अगर (ctrl->bRequestType & USB_सूची_IN)
		वापस EP0_IN_DATA_PHASE_SETUP;
	अन्यथा
		वापस EP0_OUT_DATA_PHASE_SETUP;
पूर्ण

/**
 * bcm63xx_ep0_करो_idle - Check क्रम outstanding requests अगर ep0 is idle.
 * @udc: Reference to the device controller.
 *
 * In state EP0_IDLE, the RX descriptor is either pending, or has been
 * filled with a SETUP packet from the host.  This function handles new
 * SETUP packets, control IRQ events (which can generate fake SETUP packets),
 * and reset/shutकरोwn events.
 *
 * Returns 0 अगर work was करोne; -EAGAIN अगर nothing to करो.
 */
अटल पूर्णांक bcm63xx_ep0_करो_idle(काष्ठा bcm63xx_udc *udc)
अणु
	अगर (udc->ep0_req_reset) अणु
		udc->ep0_req_reset = 0;
	पूर्ण अन्यथा अगर (udc->ep0_req_set_cfg) अणु
		udc->ep0_req_set_cfg = 0;
		अगर (bcm63xx_ep0_spoof_set_cfg(udc) >= 0)
			udc->ep0state = EP0_IN_FAKE_STATUS_PHASE;
	पूर्ण अन्यथा अगर (udc->ep0_req_set_अगरace) अणु
		udc->ep0_req_set_अगरace = 0;
		अगर (bcm63xx_ep0_spoof_set_अगरace(udc) >= 0)
			udc->ep0state = EP0_IN_FAKE_STATUS_PHASE;
	पूर्ण अन्यथा अगर (udc->ep0_req_completed) अणु
		udc->ep0state = bcm63xx_ep0_करो_setup(udc);
		वापस udc->ep0state == EP0_IDLE ? -EAGAIN : 0;
	पूर्ण अन्यथा अगर (udc->ep0_req_shutकरोwn) अणु
		udc->ep0_req_shutकरोwn = 0;
		udc->ep0_req_completed = 0;
		udc->ep0_request = शून्य;
		iudma_reset_channel(udc, &udc->iudma[IUDMA_EP0_RXCHAN]);
		usb_gadget_unmap_request(&udc->gadget,
			&udc->ep0_ctrl_req.req, 0);

		/* bcm63xx_udc_pullup() is रुकोing क्रम this */
		mb();
		udc->ep0state = EP0_SHUTDOWN;
	पूर्ण अन्यथा अगर (udc->ep0_reply) अणु
		/*
		 * This could happen अगर a USB RESET shows up during an ep0
		 * transaction (especially अगर a laggy driver like gadgetfs
		 * is in use).
		 */
		dev_warn(udc->dev, "nuking unexpected reply\n");
		bcm63xx_ep0_nuke_reply(udc, 0);
	पूर्ण अन्यथा अणु
		वापस -EAGAIN;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * bcm63xx_ep0_one_round - Handle the current ep0 state.
 * @udc: Reference to the device controller.
 *
 * Returns 0 अगर work was करोne; -EAGAIN अगर nothing to करो.
 */
अटल पूर्णांक bcm63xx_ep0_one_round(काष्ठा bcm63xx_udc *udc)
अणु
	क्रमागत bcm63xx_ep0_state ep0state = udc->ep0state;
	bool shutकरोwn = udc->ep0_req_reset || udc->ep0_req_shutकरोwn;

	चयन (udc->ep0state) अणु
	हाल EP0_REQUEUE:
		/* set up descriptor to receive SETUP packet */
		bcm63xx_ep0_पूर्णांकernal_request(udc, IUDMA_EP0_RXCHAN,
					     BCM63XX_MAX_CTRL_PKT);
		ep0state = EP0_IDLE;
		अवरोध;
	हाल EP0_IDLE:
		वापस bcm63xx_ep0_करो_idle(udc);
	हाल EP0_IN_DATA_PHASE_SETUP:
		/*
		 * Normal हाल: TX request is in ep0_reply (queued by the
		 * callback), or will be queued लघुly.  When it's here,
		 * send it to the HW and go to EP0_IN_DATA_PHASE_COMPLETE.
		 *
		 * Shutकरोwn हाल: Stop रुकोing क्रम the reply.  Just
		 * REQUEUE->IDLE.  The gadget driver is NOT expected to
		 * queue anything अन्यथा now.
		 */
		अगर (udc->ep0_reply) अणु
			bcm63xx_ep0_map_ग_लिखो(udc, IUDMA_EP0_TXCHAN,
					      udc->ep0_reply);
			ep0state = EP0_IN_DATA_PHASE_COMPLETE;
		पूर्ण अन्यथा अगर (shutकरोwn) अणु
			ep0state = EP0_REQUEUE;
		पूर्ण
		अवरोध;
	हाल EP0_IN_DATA_PHASE_COMPLETE: अणु
		/*
		 * Normal हाल: TX packet (ep0_reply) is in flight; रुको क्रम
		 * it to finish, then go back to REQUEUE->IDLE.
		 *
		 * Shutकरोwn हाल: Reset the TX channel, send -ESHUTDOWN
		 * completion to the gadget driver, then REQUEUE->IDLE.
		 */
		अगर (udc->ep0_req_completed) अणु
			udc->ep0_reply = शून्य;
			bcm63xx_ep0_पढ़ो_complete(udc);
			/*
			 * the "ack" someबार माला_लो eaten (see
			 * bcm63xx_ep0_करो_idle)
			 */
			ep0state = EP0_REQUEUE;
		पूर्ण अन्यथा अगर (shutकरोwn) अणु
			iudma_reset_channel(udc, &udc->iudma[IUDMA_EP0_TXCHAN]);
			bcm63xx_ep0_nuke_reply(udc, 1);
			ep0state = EP0_REQUEUE;
		पूर्ण
		अवरोध;
	पूर्ण
	हाल EP0_OUT_DATA_PHASE_SETUP:
		/* Similar behavior to EP0_IN_DATA_PHASE_SETUP */
		अगर (udc->ep0_reply) अणु
			bcm63xx_ep0_map_ग_लिखो(udc, IUDMA_EP0_RXCHAN,
					      udc->ep0_reply);
			ep0state = EP0_OUT_DATA_PHASE_COMPLETE;
		पूर्ण अन्यथा अगर (shutकरोwn) अणु
			ep0state = EP0_REQUEUE;
		पूर्ण
		अवरोध;
	हाल EP0_OUT_DATA_PHASE_COMPLETE: अणु
		/* Similar behavior to EP0_IN_DATA_PHASE_COMPLETE */
		अगर (udc->ep0_req_completed) अणु
			udc->ep0_reply = शून्य;
			bcm63xx_ep0_पढ़ो_complete(udc);

			/* send 0-byte ack to host */
			bcm63xx_ep0_पूर्णांकernal_request(udc, IUDMA_EP0_TXCHAN, 0);
			ep0state = EP0_OUT_STATUS_PHASE;
		पूर्ण अन्यथा अगर (shutकरोwn) अणु
			iudma_reset_channel(udc, &udc->iudma[IUDMA_EP0_RXCHAN]);
			bcm63xx_ep0_nuke_reply(udc, 0);
			ep0state = EP0_REQUEUE;
		पूर्ण
		अवरोध;
	पूर्ण
	हाल EP0_OUT_STATUS_PHASE:
		/*
		 * Normal हाल: 0-byte OUT ack packet is in flight; रुको
		 * क्रम it to finish, then go back to REQUEUE->IDLE.
		 *
		 * Shutकरोwn हाल: just cancel the transmission.  Don't bother
		 * calling the completion, because it originated from this
		 * function anyway.  Then go back to REQUEUE->IDLE.
		 */
		अगर (udc->ep0_req_completed) अणु
			bcm63xx_ep0_पढ़ो_complete(udc);
			ep0state = EP0_REQUEUE;
		पूर्ण अन्यथा अगर (shutकरोwn) अणु
			iudma_reset_channel(udc, &udc->iudma[IUDMA_EP0_TXCHAN]);
			udc->ep0_request = शून्य;
			ep0state = EP0_REQUEUE;
		पूर्ण
		अवरोध;
	हाल EP0_IN_FAKE_STATUS_PHASE: अणु
		/*
		 * Normal हाल: we spoofed a SETUP packet and are now
		 * रुकोing क्रम the gadget driver to send a 0-byte reply.
		 * This करोesn't actually get sent to the HW because the
		 * HW has alपढ़ोy sent its own reply.  Once we get the
		 * response, वापस to IDLE.
		 *
		 * Shutकरोwn हाल: वापस to IDLE immediately.
		 *
		 * Note that the ep0 RX descriptor has reमुख्यed queued
		 * (and possibly unfilled) during this entire transaction.
		 * The HW datapath (IUDMA) never even sees SET_CONFIGURATION
		 * or SET_INTERFACE transactions.
		 */
		काष्ठा usb_request *r = udc->ep0_reply;

		अगर (!r) अणु
			अगर (shutकरोwn)
				ep0state = EP0_IDLE;
			अवरोध;
		पूर्ण

		bcm63xx_ep0_complete(udc, r, 0);
		udc->ep0_reply = शून्य;
		ep0state = EP0_IDLE;
		अवरोध;
	पूर्ण
	हाल EP0_SHUTDOWN:
		अवरोध;
	पूर्ण

	अगर (udc->ep0state == ep0state)
		वापस -EAGAIN;

	udc->ep0state = ep0state;
	वापस 0;
पूर्ण

/**
 * bcm63xx_ep0_process - ep0 worker thपढ़ो / state machine.
 * @w: Workqueue काष्ठा.
 *
 * bcm63xx_ep0_process is triggered any समय an event occurs on ep0.  It
 * is used to synchronize ep0 events and ensure that both HW and SW events
 * occur in a well-defined order.  When the ep0 IUDMA queues are idle, it may
 * synthesize SET_CONFIGURATION / SET_INTERFACE requests that were consumed
 * by the USBD hardware.
 *
 * The worker function will जारी iterating around the state machine
 * until there is nothing left to करो.  Usually "nothing left to do" means
 * that we're रुकोing क्रम a new event from the hardware.
 */
अटल व्योम bcm63xx_ep0_process(काष्ठा work_काष्ठा *w)
अणु
	काष्ठा bcm63xx_udc *udc = container_of(w, काष्ठा bcm63xx_udc, ep0_wq);
	spin_lock_irq(&udc->lock);
	जबतक (bcm63xx_ep0_one_round(udc) == 0)
		;
	spin_unlock_irq(&udc->lock);
पूर्ण

/***********************************************************************
 * Standard UDC gadget operations
 ***********************************************************************/

/**
 * bcm63xx_udc_get_frame - Read current SOF frame number from the HW.
 * @gadget: USB device.
 */
अटल पूर्णांक bcm63xx_udc_get_frame(काष्ठा usb_gadget *gadget)
अणु
	काष्ठा bcm63xx_udc *udc = gadget_to_udc(gadget);

	वापस (usbd_पढ़ोl(udc, USBD_STATUS_REG) &
		USBD_STATUS_SOF_MASK) >> USBD_STATUS_SOF_SHIFT;
पूर्ण

/**
 * bcm63xx_udc_pullup - Enable/disable pullup on D+ line.
 * @gadget: USB device.
 * @is_on: 0 to disable pullup, 1 to enable.
 *
 * See notes in bcm63xx_select_pullup().
 */
अटल पूर्णांक bcm63xx_udc_pullup(काष्ठा usb_gadget *gadget, पूर्णांक is_on)
अणु
	काष्ठा bcm63xx_udc *udc = gadget_to_udc(gadget);
	अचिन्हित दीर्घ flags;
	पूर्णांक i, rc = -EINVAL;

	spin_lock_irqsave(&udc->lock, flags);
	अगर (is_on && udc->ep0state == EP0_SHUTDOWN) अणु
		udc->gadget.speed = USB_SPEED_UNKNOWN;
		udc->ep0state = EP0_REQUEUE;
		bcm63xx_fअगरo_setup(udc);
		bcm63xx_fअगरo_reset(udc);
		bcm63xx_ep_setup(udc);

		biपंचांगap_zero(&udc->wedgemap, BCM63XX_NUM_EP);
		क्रम (i = 0; i < BCM63XX_NUM_EP; i++)
			bcm63xx_set_stall(udc, &udc->bep[i], false);

		bcm63xx_set_ctrl_irqs(udc, true);
		bcm63xx_select_pullup(gadget_to_udc(gadget), true);
		rc = 0;
	पूर्ण अन्यथा अगर (!is_on && udc->ep0state != EP0_SHUTDOWN) अणु
		bcm63xx_select_pullup(gadget_to_udc(gadget), false);

		udc->ep0_req_shutकरोwn = 1;
		spin_unlock_irqrestore(&udc->lock, flags);

		जबतक (1) अणु
			schedule_work(&udc->ep0_wq);
			अगर (udc->ep0state == EP0_SHUTDOWN)
				अवरोध;
			msleep(50);
		पूर्ण
		bcm63xx_set_ctrl_irqs(udc, false);
		cancel_work_sync(&udc->ep0_wq);
		वापस 0;
	पूर्ण

	spin_unlock_irqrestore(&udc->lock, flags);
	वापस rc;
पूर्ण

/**
 * bcm63xx_udc_start - Start the controller.
 * @gadget: USB device.
 * @driver: Driver क्रम USB device.
 */
अटल पूर्णांक bcm63xx_udc_start(काष्ठा usb_gadget *gadget,
		काष्ठा usb_gadget_driver *driver)
अणु
	काष्ठा bcm63xx_udc *udc = gadget_to_udc(gadget);
	अचिन्हित दीर्घ flags;

	अगर (!driver || driver->max_speed < USB_SPEED_HIGH ||
	    !driver->setup)
		वापस -EINVAL;
	अगर (!udc)
		वापस -ENODEV;
	अगर (udc->driver)
		वापस -EBUSY;

	spin_lock_irqsave(&udc->lock, flags);

	set_घड़ीs(udc, true);
	bcm63xx_fअगरo_setup(udc);
	bcm63xx_ep_init(udc);
	bcm63xx_ep_setup(udc);
	bcm63xx_fअगरo_reset(udc);
	bcm63xx_select_phy_mode(udc, true);

	udc->driver = driver;
	driver->driver.bus = शून्य;
	udc->gadget.dev.of_node = udc->dev->of_node;

	spin_unlock_irqrestore(&udc->lock, flags);

	वापस 0;
पूर्ण

/**
 * bcm63xx_udc_stop - Shut करोwn the controller.
 * @gadget: USB device.
 * @driver: Driver क्रम USB device.
 */
अटल पूर्णांक bcm63xx_udc_stop(काष्ठा usb_gadget *gadget)
अणु
	काष्ठा bcm63xx_udc *udc = gadget_to_udc(gadget);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&udc->lock, flags);

	udc->driver = शून्य;

	/*
	 * If we चयन the PHY too abruptly after dropping D+, the host
	 * will often complain:
	 *
	 *     hub 1-0:1.0: port 1 disabled by hub (EMI?), re-enabling...
	 */
	msleep(100);

	bcm63xx_select_phy_mode(udc, false);
	set_घड़ीs(udc, false);

	spin_unlock_irqrestore(&udc->lock, flags);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा usb_gadget_ops bcm63xx_udc_ops = अणु
	.get_frame	= bcm63xx_udc_get_frame,
	.pullup		= bcm63xx_udc_pullup,
	.udc_start	= bcm63xx_udc_start,
	.udc_stop	= bcm63xx_udc_stop,
पूर्ण;

/***********************************************************************
 * IRQ handling
 ***********************************************************************/

/**
 * bcm63xx_update_cfg_अगरace - Read current configuration/पूर्णांकerface settings.
 * @udc: Reference to the device controller.
 *
 * This controller पूर्णांकercepts SET_CONFIGURATION and SET_INTERFACE messages.
 * The driver never sees the raw control packets coming in on the ep0
 * IUDMA channel, but at least we get an पूर्णांकerrupt event to tell us that
 * new values are रुकोing in the USBD_STATUS रेजिस्टर.
 */
अटल व्योम bcm63xx_update_cfg_अगरace(काष्ठा bcm63xx_udc *udc)
अणु
	u32 reg = usbd_पढ़ोl(udc, USBD_STATUS_REG);

	udc->cfg = (reg & USBD_STATUS_CFG_MASK) >> USBD_STATUS_CFG_SHIFT;
	udc->अगरace = (reg & USBD_STATUS_INTF_MASK) >> USBD_STATUS_INTF_SHIFT;
	udc->alt_अगरace = (reg & USBD_STATUS_ALTINTF_MASK) >>
			 USBD_STATUS_ALTINTF_SHIFT;
	bcm63xx_ep_setup(udc);
पूर्ण

/**
 * bcm63xx_update_link_speed - Check to see अगर the link speed has changed.
 * @udc: Reference to the device controller.
 *
 * The link speed update coincides with a SETUP IRQ.  Returns 1 अगर the
 * speed has changed, so that the caller can update the endpoपूर्णांक settings.
 */
अटल पूर्णांक bcm63xx_update_link_speed(काष्ठा bcm63xx_udc *udc)
अणु
	u32 reg = usbd_पढ़ोl(udc, USBD_STATUS_REG);
	क्रमागत usb_device_speed oldspeed = udc->gadget.speed;

	चयन ((reg & USBD_STATUS_SPD_MASK) >> USBD_STATUS_SPD_SHIFT) अणु
	हाल BCM63XX_SPD_HIGH:
		udc->gadget.speed = USB_SPEED_HIGH;
		अवरोध;
	हाल BCM63XX_SPD_FULL:
		udc->gadget.speed = USB_SPEED_FULL;
		अवरोध;
	शेष:
		/* this should never happen */
		udc->gadget.speed = USB_SPEED_UNKNOWN;
		dev_err(udc->dev,
			"received SETUP packet with invalid link speed\n");
		वापस 0;
	पूर्ण

	अगर (udc->gadget.speed != oldspeed) अणु
		dev_info(udc->dev, "link up, %s-speed mode\n",
			 udc->gadget.speed == USB_SPEED_HIGH ? "high" : "full");
		वापस 1;
	पूर्ण अन्यथा अणु
		वापस 0;
	पूर्ण
पूर्ण

/**
 * bcm63xx_update_wedge - Iterate through wedged endpoपूर्णांकs.
 * @udc: Reference to the device controller.
 * @new_status: true to "refresh" wedge status; false to clear it.
 *
 * On a SETUP पूर्णांकerrupt, we need to manually "refresh" the wedge status
 * because the controller hardware is deचिन्हित to स्वतःmatically clear
 * stalls in response to a CLEAR_FEATURE request from the host.
 *
 * On a RESET पूर्णांकerrupt, we करो want to restore all wedged endpoपूर्णांकs.
 */
अटल व्योम bcm63xx_update_wedge(काष्ठा bcm63xx_udc *udc, bool new_status)
अणु
	पूर्णांक i;

	क्रम_each_set_bit(i, &udc->wedgemap, BCM63XX_NUM_EP) अणु
		bcm63xx_set_stall(udc, &udc->bep[i], new_status);
		अगर (!new_status)
			clear_bit(i, &udc->wedgemap);
	पूर्ण
पूर्ण

/**
 * bcm63xx_udc_ctrl_isr - ISR क्रम control path events (USBD).
 * @irq: IRQ number (unused).
 * @dev_id: Reference to the device controller.
 *
 * This is where we handle link (VBUS) करोwn, USB reset, speed changes,
 * SET_CONFIGURATION, and SET_INTERFACE events.
 */
अटल irqवापस_t bcm63xx_udc_ctrl_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा bcm63xx_udc *udc = dev_id;
	u32 stat;
	bool disconnected = false, bus_reset = false;

	stat = usbd_पढ़ोl(udc, USBD_EVENT_IRQ_STATUS_REG) &
	       usbd_पढ़ोl(udc, USBD_EVENT_IRQ_MASK_REG);

	usbd_ग_लिखोl(udc, stat, USBD_EVENT_IRQ_STATUS_REG);

	spin_lock(&udc->lock);
	अगर (stat & BIT(USBD_EVENT_IRQ_USB_LINK)) अणु
		/* VBUS toggled */

		अगर (!(usbd_पढ़ोl(udc, USBD_EVENTS_REG) &
		      USBD_EVENTS_USB_LINK_MASK) &&
		      udc->gadget.speed != USB_SPEED_UNKNOWN)
			dev_info(udc->dev, "link down\n");

		udc->gadget.speed = USB_SPEED_UNKNOWN;
		disconnected = true;
	पूर्ण
	अगर (stat & BIT(USBD_EVENT_IRQ_USB_RESET)) अणु
		bcm63xx_fअगरo_setup(udc);
		bcm63xx_fअगरo_reset(udc);
		bcm63xx_ep_setup(udc);

		bcm63xx_update_wedge(udc, false);

		udc->ep0_req_reset = 1;
		schedule_work(&udc->ep0_wq);
		bus_reset = true;
	पूर्ण
	अगर (stat & BIT(USBD_EVENT_IRQ_SETUP)) अणु
		अगर (bcm63xx_update_link_speed(udc)) अणु
			bcm63xx_fअगरo_setup(udc);
			bcm63xx_ep_setup(udc);
		पूर्ण
		bcm63xx_update_wedge(udc, true);
	पूर्ण
	अगर (stat & BIT(USBD_EVENT_IRQ_SETCFG)) अणु
		bcm63xx_update_cfg_अगरace(udc);
		udc->ep0_req_set_cfg = 1;
		schedule_work(&udc->ep0_wq);
	पूर्ण
	अगर (stat & BIT(USBD_EVENT_IRQ_SETINTF)) अणु
		bcm63xx_update_cfg_अगरace(udc);
		udc->ep0_req_set_अगरace = 1;
		schedule_work(&udc->ep0_wq);
	पूर्ण
	spin_unlock(&udc->lock);

	अगर (disconnected && udc->driver)
		udc->driver->disconnect(&udc->gadget);
	अन्यथा अगर (bus_reset && udc->driver)
		usb_gadget_udc_reset(&udc->gadget, udc->driver);

	वापस IRQ_HANDLED;
पूर्ण

/**
 * bcm63xx_udc_data_isr - ISR क्रम data path events (IUDMA).
 * @irq: IRQ number (unused).
 * @dev_id: Reference to the IUDMA channel that generated the पूर्णांकerrupt.
 *
 * For the two ep0 channels, we have special handling that triggers the
 * ep0 worker thपढ़ो.  For normal bulk/पूर्णांकr channels, either queue up
 * the next buffer descriptor क्रम the transaction (incomplete transaction),
 * or invoke the completion callback (complete transactions).
 */
अटल irqवापस_t bcm63xx_udc_data_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा iudma_ch *iudma = dev_id;
	काष्ठा bcm63xx_udc *udc = iudma->udc;
	काष्ठा bcm63xx_ep *bep;
	काष्ठा usb_request *req = शून्य;
	काष्ठा bcm63xx_req *breq = शून्य;
	पूर्णांक rc;
	bool is_करोne = false;

	spin_lock(&udc->lock);

	usb_dmac_ग_लिखोl(udc, ENETDMAC_IR_BUFDONE_MASK,
			ENETDMAC_IR_REG, iudma->ch_idx);
	bep = iudma->bep;
	rc = iudma_पढ़ो(udc, iudma);

	/* special handling क्रम EP0 RX (0) and TX (1) */
	अगर (iudma->ch_idx == IUDMA_EP0_RXCHAN ||
	    iudma->ch_idx == IUDMA_EP0_TXCHAN) अणु
		req = udc->ep0_request;
		breq = our_req(req);

		/* a single request could require multiple submissions */
		अगर (rc >= 0) अणु
			req->actual += rc;

			अगर (req->actual >= req->length || breq->bd_bytes > rc) अणु
				udc->ep0_req_completed = 1;
				is_करोne = true;
				schedule_work(&udc->ep0_wq);

				/* "actual" on a ZLP is 1 byte */
				req->actual = min(req->actual, req->length);
			पूर्ण अन्यथा अणु
				/* queue up the next BD (same request) */
				iudma_ग_लिखो(udc, iudma, breq);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (!list_empty(&bep->queue)) अणु
		breq = list_first_entry(&bep->queue, काष्ठा bcm63xx_req, queue);
		req = &breq->req;

		अगर (rc >= 0) अणु
			req->actual += rc;

			अगर (req->actual >= req->length || breq->bd_bytes > rc) अणु
				is_करोne = true;
				list_del(&breq->queue);

				req->actual = min(req->actual, req->length);

				अगर (!list_empty(&bep->queue)) अणु
					काष्ठा bcm63xx_req *next;

					next = list_first_entry(&bep->queue,
						काष्ठा bcm63xx_req, queue);
					iudma_ग_लिखो(udc, iudma, next);
				पूर्ण
			पूर्ण अन्यथा अणु
				iudma_ग_लिखो(udc, iudma, breq);
			पूर्ण
		पूर्ण
	पूर्ण
	spin_unlock(&udc->lock);

	अगर (is_करोne) अणु
		usb_gadget_unmap_request(&udc->gadget, req, iudma->is_tx);
		अगर (req->complete)
			req->complete(&bep->ep, req);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/***********************************************************************
 * Debug fileप्रणाली
 ***********************************************************************/

/*
 * bcm63xx_usbd_dbg_show - Show USBD controller state.
 * @s: seq_file to which the inक्रमmation will be written.
 * @p: Unused.
 *
 * This file nominally shows up as /sys/kernel/debug/bcm63xx_udc/usbd
 */
अटल पूर्णांक bcm63xx_usbd_dbg_show(काष्ठा seq_file *s, व्योम *p)
अणु
	काष्ठा bcm63xx_udc *udc = s->निजी;

	अगर (!udc->driver)
		वापस -ENODEV;

	seq_म_लिखो(s, "ep0 state: %s\n",
		   bcm63xx_ep0_state_names[udc->ep0state]);
	seq_म_लिखो(s, "  pending requests: %s%s%s%s%s%s%s\n",
		   udc->ep0_req_reset ? "reset " : "",
		   udc->ep0_req_set_cfg ? "set_cfg " : "",
		   udc->ep0_req_set_अगरace ? "set_iface " : "",
		   udc->ep0_req_shutकरोwn ? "shutdown " : "",
		   udc->ep0_request ? "pending " : "",
		   udc->ep0_req_completed ? "completed " : "",
		   udc->ep0_reply ? "reply " : "");
	seq_म_लिखो(s, "cfg: %d; iface: %d; alt_iface: %d\n",
		   udc->cfg, udc->अगरace, udc->alt_अगरace);
	seq_म_लिखो(s, "regs:\n");
	seq_म_लिखो(s, "  control: %08x; straps: %08x; status: %08x\n",
		   usbd_पढ़ोl(udc, USBD_CONTROL_REG),
		   usbd_पढ़ोl(udc, USBD_STRAPS_REG),
		   usbd_पढ़ोl(udc, USBD_STATUS_REG));
	seq_म_लिखो(s, "  events:  %08x; stall:  %08x\n",
		   usbd_पढ़ोl(udc, USBD_EVENTS_REG),
		   usbd_पढ़ोl(udc, USBD_STALL_REG));

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(bcm63xx_usbd_dbg);

/*
 * bcm63xx_iudma_dbg_show - Show IUDMA status and descriptors.
 * @s: seq_file to which the inक्रमmation will be written.
 * @p: Unused.
 *
 * This file nominally shows up as /sys/kernel/debug/bcm63xx_udc/iudma
 */
अटल पूर्णांक bcm63xx_iudma_dbg_show(काष्ठा seq_file *s, व्योम *p)
अणु
	काष्ठा bcm63xx_udc *udc = s->निजी;
	पूर्णांक ch_idx, i;
	u32 sram2, sram3;

	अगर (!udc->driver)
		वापस -ENODEV;

	क्रम (ch_idx = 0; ch_idx < BCM63XX_NUM_IUDMA; ch_idx++) अणु
		काष्ठा iudma_ch *iudma = &udc->iudma[ch_idx];
		काष्ठा list_head *pos;

		seq_म_लिखो(s, "IUDMA channel %d -- ", ch_idx);
		चयन (iudma_शेषs[ch_idx].ep_type) अणु
		हाल BCMEP_CTRL:
			seq_म_लिखो(s, "control");
			अवरोध;
		हाल BCMEP_BULK:
			seq_म_लिखो(s, "bulk");
			अवरोध;
		हाल BCMEP_INTR:
			seq_म_लिखो(s, "interrupt");
			अवरोध;
		पूर्ण
		seq_म_लिखो(s, ch_idx & 0x01 ? " tx" : " rx");
		seq_म_लिखो(s, " [ep%d]:\n",
			   max_t(पूर्णांक, iudma_शेषs[ch_idx].ep_num, 0));
		seq_म_लिखो(s, "  cfg: %08x; irqstat: %08x; irqmask: %08x; maxburst: %08x\n",
			   usb_dmac_पढ़ोl(udc, ENETDMAC_CHANCFG_REG, ch_idx),
			   usb_dmac_पढ़ोl(udc, ENETDMAC_IR_REG, ch_idx),
			   usb_dmac_पढ़ोl(udc, ENETDMAC_IRMASK_REG, ch_idx),
			   usb_dmac_पढ़ोl(udc, ENETDMAC_MAXBURST_REG, ch_idx));

		sram2 = usb_dmas_पढ़ोl(udc, ENETDMAS_SRAM2_REG, ch_idx);
		sram3 = usb_dmas_पढ़ोl(udc, ENETDMAS_SRAM3_REG, ch_idx);
		seq_म_लिखो(s, "  base: %08x; index: %04x_%04x; desc: %04x_%04x %08x\n",
			   usb_dmas_पढ़ोl(udc, ENETDMAS_RSTART_REG, ch_idx),
			   sram2 >> 16, sram2 & 0xffff,
			   sram3 >> 16, sram3 & 0xffff,
			   usb_dmas_पढ़ोl(udc, ENETDMAS_SRAM4_REG, ch_idx));
		seq_म_लिखो(s, "  desc: %d/%d used", iudma->n_bds_used,
			   iudma->n_bds);

		अगर (iudma->bep) अणु
			i = 0;
			list_क्रम_each(pos, &iudma->bep->queue)
				i++;
			seq_म_लिखो(s, "; %d queued\n", i);
		पूर्ण अन्यथा अणु
			seq_म_लिखो(s, "\n");
		पूर्ण

		क्रम (i = 0; i < iudma->n_bds; i++) अणु
			काष्ठा bcm_enet_desc *d = &iudma->bd_ring[i];

			seq_म_लिखो(s, "  %03x (%02x): len_stat: %04x_%04x; pa %08x",
				   i * माप(*d), i,
				   d->len_stat >> 16, d->len_stat & 0xffff,
				   d->address);
			अगर (d == iudma->पढ़ो_bd)
				seq_म_लिखो(s, "   <<RD");
			अगर (d == iudma->ग_लिखो_bd)
				seq_म_लिखो(s, "   <<WR");
			seq_म_लिखो(s, "\n");
		पूर्ण

		seq_म_लिखो(s, "\n");
	पूर्ण

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(bcm63xx_iudma_dbg);

/**
 * bcm63xx_udc_init_debugfs - Create debugfs entries.
 * @udc: Reference to the device controller.
 */
अटल व्योम bcm63xx_udc_init_debugfs(काष्ठा bcm63xx_udc *udc)
अणु
	काष्ठा dentry *root;

	अगर (!IS_ENABLED(CONFIG_USB_GADGET_DEBUG_FS))
		वापस;

	root = debugfs_create_dir(udc->gadget.name, usb_debug_root);
	udc->debugfs_root = root;

	debugfs_create_file("usbd", 0400, root, udc, &bcm63xx_usbd_dbg_fops);
	debugfs_create_file("iudma", 0400, root, udc, &bcm63xx_iudma_dbg_fops);
पूर्ण

/**
 * bcm63xx_udc_cleanup_debugfs - Remove debugfs entries.
 * @udc: Reference to the device controller.
 *
 * debugfs_हटाओ() is safe to call with a शून्य argument.
 */
अटल व्योम bcm63xx_udc_cleanup_debugfs(काष्ठा bcm63xx_udc *udc)
अणु
	debugfs_हटाओ_recursive(udc->debugfs_root);
पूर्ण

/***********************************************************************
 * Driver init/निकास
 ***********************************************************************/

/**
 * bcm63xx_udc_probe - Initialize a new instance of the UDC.
 * @pdev: Platक्रमm device काष्ठा from the bcm63xx BSP code.
 *
 * Note that platक्रमm data is required, because pd.port_no varies from chip
 * to chip and is used to चयन the correct USB port to device mode.
 */
अटल पूर्णांक bcm63xx_udc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा bcm63xx_usbd_platक्रमm_data *pd = dev_get_platdata(dev);
	काष्ठा bcm63xx_udc *udc;
	पूर्णांक rc = -ENOMEM, i, irq;

	udc = devm_kzalloc(dev, माप(*udc), GFP_KERNEL);
	अगर (!udc)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, udc);
	udc->dev = dev;
	udc->pd = pd;

	अगर (!pd) अणु
		dev_err(dev, "missing platform data\n");
		वापस -EINVAL;
	पूर्ण

	udc->usbd_regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(udc->usbd_regs))
		वापस PTR_ERR(udc->usbd_regs);

	udc->iudma_regs = devm_platक्रमm_ioremap_resource(pdev, 1);
	अगर (IS_ERR(udc->iudma_regs))
		वापस PTR_ERR(udc->iudma_regs);

	spin_lock_init(&udc->lock);
	INIT_WORK(&udc->ep0_wq, bcm63xx_ep0_process);

	udc->gadget.ops = &bcm63xx_udc_ops;
	udc->gadget.name = dev_name(dev);

	अगर (!pd->use_fullspeed && !use_fullspeed)
		udc->gadget.max_speed = USB_SPEED_HIGH;
	अन्यथा
		udc->gadget.max_speed = USB_SPEED_FULL;

	/* request घड़ीs, allocate buffers, and clear any pending IRQs */
	rc = bcm63xx_init_udc_hw(udc);
	अगर (rc)
		वापस rc;

	rc = -ENXIO;

	/* IRQ resource #0: control पूर्णांकerrupt (VBUS, speed, etc.) */
	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		जाओ out_uninit;
	अगर (devm_request_irq(dev, irq, &bcm63xx_udc_ctrl_isr, 0,
			     dev_name(dev), udc) < 0)
		जाओ report_request_failure;

	/* IRQ resources #1-6: data पूर्णांकerrupts क्रम IUDMA channels 0-5 */
	क्रम (i = 0; i < BCM63XX_NUM_IUDMA; i++) अणु
		irq = platक्रमm_get_irq(pdev, i + 1);
		अगर (irq < 0)
			जाओ out_uninit;
		अगर (devm_request_irq(dev, irq, &bcm63xx_udc_data_isr, 0,
				     dev_name(dev), &udc->iudma[i]) < 0)
			जाओ report_request_failure;
	पूर्ण

	bcm63xx_udc_init_debugfs(udc);
	rc = usb_add_gadget_udc(dev, &udc->gadget);
	अगर (!rc)
		वापस 0;

	bcm63xx_udc_cleanup_debugfs(udc);
out_uninit:
	bcm63xx_uninit_udc_hw(udc);
	वापस rc;

report_request_failure:
	dev_err(dev, "error requesting IRQ #%d\n", irq);
	जाओ out_uninit;
पूर्ण

/**
 * bcm63xx_udc_हटाओ - Remove the device from the प्रणाली.
 * @pdev: Platक्रमm device काष्ठा from the bcm63xx BSP code.
 */
अटल पूर्णांक bcm63xx_udc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा bcm63xx_udc *udc = platक्रमm_get_drvdata(pdev);

	bcm63xx_udc_cleanup_debugfs(udc);
	usb_del_gadget_udc(&udc->gadget);
	BUG_ON(udc->driver);

	bcm63xx_uninit_udc_hw(udc);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver bcm63xx_udc_driver = अणु
	.probe		= bcm63xx_udc_probe,
	.हटाओ		= bcm63xx_udc_हटाओ,
	.driver		= अणु
		.name	= DRV_MODULE_NAME,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(bcm63xx_udc_driver);

MODULE_DESCRIPTION("BCM63xx USB Peripheral Controller");
MODULE_AUTHOR("Kevin Cernekee <cernekee@gmail.com>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:" DRV_MODULE_NAME);
