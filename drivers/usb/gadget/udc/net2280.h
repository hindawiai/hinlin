<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * NetChip 2280 high/full speed USB device controller.
 * Unlike many such controllers, this one talks PCI.
 */

/*
 * Copyright (C) 2002 NetChip Technology, Inc. (http://www.netchip.com)
 * Copyright (C) 2003 David Brownell
 * Copyright (C) 2014 Ricarकरो Ribalda - Qtechnology/AS
 */

#समावेश <linux/usb/net2280.h>
#समावेश <linux/usb/usb338x.h>

/*-------------------------------------------------------------------------*/

#अगर_घोषित	__KERNEL__

/* indexed रेजिस्टरs [11.10] are accessed indirectly
 * caller must own the device lock.
 */

अटल अंतरभूत u32 get_idx_reg(काष्ठा net2280_regs __iomem *regs, u32 index)
अणु
	ग_लिखोl(index, &regs->idxaddr);
	/* NOTE:  synchs device/cpu memory views */
	वापस पढ़ोl(&regs->idxdata);
पूर्ण

अटल अंतरभूत व्योम
set_idx_reg(काष्ठा net2280_regs __iomem *regs, u32 index, u32 value)
अणु
	ग_लिखोl(index, &regs->idxaddr);
	ग_लिखोl(value, &regs->idxdata);
	/* posted, may not be visible yet */
पूर्ण

#पूर्ण_अगर	/* __KERNEL__ */

#घोषणा PCI_VENDOR_ID_PLX_LEGACY 0x17cc

#घोषणा PLX_LEGACY		BIT(0)
#घोषणा PLX_2280		BIT(1)
#घोषणा PLX_SUPERSPEED		BIT(2)
#घोषणा PLX_PCIE		BIT(3)

#घोषणा REG_DIAG		0x0
#घोषणा     RETRY_COUNTER                                       16
#घोषणा     FORCE_PCI_SERR                                      11
#घोषणा     FORCE_PCI_INTERRUPT                                 10
#घोषणा     FORCE_USB_INTERRUPT                                 9
#घोषणा     FORCE_CPU_INTERRUPT                                 8
#घोषणा     ILLEGAL_BYTE_ENABLES                                5
#घोषणा     FAST_TIMES                                          4
#घोषणा     FORCE_RECEIVE_ERROR                                 2
#घोषणा     FORCE_TRANSMIT_CRC_ERROR                            0
#घोषणा REG_FRAME		0x02	/* from last sof */
#घोषणा REG_CHIPREV		0x03	/* in bcd */
#घोषणा	REG_HS_NAK_RATE		0x0a	/* NAK per N uframes */

#घोषणा	CHIPREV_1	0x0100
#घोषणा	CHIPREV_1A	0x0110

/* DEFECT 7374 */
#घोषणा DEFECT_7374_NUMBEROF_MAX_WAIT_LOOPS         200
#घोषणा DEFECT_7374_PROCESSOR_WAIT_TIME             10

/* ep0 max packet size */
#घोषणा EP0_SS_MAX_PACKET_SIZE  0x200
#घोषणा EP0_HS_MAX_PACKET_SIZE  0x40
#अगर_घोषित	__KERNEL__

/*-------------------------------------------------------------------------*/

/* [8.3] क्रम scatter/gather i/o
 * use काष्ठा net2280_dma_regs bitfields
 */
काष्ठा net2280_dma अणु
	__le32		dmacount;
	__le32		dmaaddr;		/* the buffer */
	__le32		dmadesc;		/* next dma descriptor */
	__le32		_reserved;
पूर्ण __aligned(16);

/*-------------------------------------------------------------------------*/

/* DRIVER DATA STRUCTURES and UTILITIES */

काष्ठा net2280_ep अणु
	काष्ठा usb_ep				ep;
	काष्ठा net2280_ep_regs __iomem *cfg;
	काष्ठा net2280_ep_regs			__iomem *regs;
	काष्ठा net2280_dma_regs			__iomem *dma;
	काष्ठा net2280_dma			*dummy;
	dma_addr_t				td_dma;	/* of dummy */
	काष्ठा net2280				*dev;
	अचिन्हित दीर्घ				irqs;

	/* analogous to a host-side qh */
	काष्ठा list_head			queue;
	स्थिर काष्ठा usb_endpoपूर्णांक_descriptor	*desc;
	अचिन्हित				num : 8,
						fअगरo_size : 12,
						in_fअगरo_validate : 1,
						out_overflow : 1,
						stopped : 1,
						wedged : 1,
						is_in : 1,
						is_iso : 1,
						responded : 1;
पूर्ण;

अटल अंतरभूत व्योम allow_status(काष्ठा net2280_ep *ep)
अणु
	/* ep0 only */
	ग_लिखोl(BIT(CLEAR_CONTROL_STATUS_PHASE_HANDSHAKE) |
		BIT(CLEAR_NAK_OUT_PACKETS) |
		BIT(CLEAR_NAK_OUT_PACKETS_MODE),
		&ep->regs->ep_rsp);
	ep->stopped = 1;
पूर्ण

अटल अंतरभूत व्योम allow_status_338x(काष्ठा net2280_ep *ep)
अणु
	/*
	 * Control Status Phase Handshake was set by the chip when the setup
	 * packet arrived. While set, the chip स्वतःmatically NAKs the host's
	 * Status Phase tokens.
	 */
	ग_लिखोl(BIT(CLEAR_CONTROL_STATUS_PHASE_HANDSHAKE), &ep->regs->ep_rsp);

	ep->stopped = 1;

	/* TD 9.9 Halt Endpoपूर्णांक test.  TD 9.22 set feature test. */
	ep->responded = 0;
पूर्ण

काष्ठा net2280_request अणु
	काष्ठा usb_request		req;
	काष्ठा net2280_dma		*td;
	dma_addr_t			td_dma;
	काष्ठा list_head		queue;
	अचिन्हित			mapped : 1,
					valid : 1;
पूर्ण;

काष्ठा net2280 अणु
	/* each pci device provides one gadget, several endpoपूर्णांकs */
	काष्ठा usb_gadget		gadget;
	spinlock_t			lock;
	काष्ठा net2280_ep		ep[9];
	काष्ठा usb_gadget_driver	*driver;
	अचिन्हित			enabled : 1,
					protocol_stall : 1,
					softconnect : 1,
					got_irq : 1,
					region:1,
					added:1,
					u1_enable:1,
					u2_enable:1,
					lपंचांग_enable:1,
					wakeup_enable:1,
					addressed_state:1,
					bug7734_patched:1;
	u16				chiprev;
	पूर्णांक enhanced_mode;
	पूर्णांक n_ep;
	kernel_uदीर्घ_t			quirks;


	/* pci state used to access those endpoपूर्णांकs */
	काष्ठा pci_dev			*pdev;
	काष्ठा net2280_regs		__iomem *regs;
	काष्ठा net2280_usb_regs		__iomem *usb;
	काष्ठा usb338x_usb_ext_regs	__iomem *usb_ext;
	काष्ठा net2280_pci_regs		__iomem *pci;
	काष्ठा net2280_dma_regs		__iomem *dma;
	काष्ठा net2280_dep_regs		__iomem *dep;
	काष्ठा net2280_ep_regs		__iomem *epregs;
	काष्ठा usb338x_ll_regs		__iomem *llregs;
	काष्ठा usb338x_pl_regs		__iomem *plregs;

	काष्ठा dma_pool			*requests;
	/* statistics...*/
पूर्ण;

अटल अंतरभूत व्योम set_halt(काष्ठा net2280_ep *ep)
अणु
	/* ep0 and bulk/पूर्णांकr endpoपूर्णांकs */
	ग_लिखोl(BIT(CLEAR_CONTROL_STATUS_PHASE_HANDSHAKE) |
		/* set NAK_OUT क्रम erratum 0114 */
		((ep->dev->chiprev == CHIPREV_1) << SET_NAK_OUT_PACKETS) |
		BIT(SET_ENDPOINT_HALT),
		&ep->regs->ep_rsp);
पूर्ण

अटल अंतरभूत व्योम clear_halt(काष्ठा net2280_ep *ep)
अणु
	/* ep0 and bulk/पूर्णांकr endpoपूर्णांकs */
	ग_लिखोl(BIT(CLEAR_ENDPOINT_HALT) |
		BIT(CLEAR_ENDPOINT_TOGGLE) |
		    /*
		     * unless the gadget driver left a लघु packet in the
		     * fअगरo, this reverses the erratum 0114 workaround.
		     */
		((ep->dev->chiprev == CHIPREV_1) << CLEAR_NAK_OUT_PACKETS),
		&ep->regs->ep_rsp);
पूर्ण

/*
 * FSM value क्रम Defect 7374 (U1U2 Test) is managed in
 * chip's SCRATCH रेजिस्टर:
 */
#घोषणा DEFECT7374_FSM_FIELD    28

/* Waiting क्रम Control Read:
 *  - A transition to this state indicates a fresh USB connection,
 *    beक्रमe the first Setup Packet. The connection speed is not
 *    known. Firmware is रुकोing क्रम the first Control Read.
 *  - Starting state: This state can be thought of as the FSM's typical
 *    starting state.
 *  - Tip: Upon the first SS Control Read the FSM never
 *    वापसs to this state.
 */
#घोषणा DEFECT7374_FSM_WAITING_FOR_CONTROL_READ BIT(DEFECT7374_FSM_FIELD)

/* Non-SS Control Read:
 *  - A transition to this state indicates detection of the first HS
 *    or FS Control Read.
 *  - Tip: Upon the first SS Control Read the FSM never
 *    वापसs to this state.
 */
#घोषणा	DEFECT7374_FSM_NON_SS_CONTROL_READ (2 << DEFECT7374_FSM_FIELD)

/* SS Control Read:
 *  - A transition to this state indicates detection of the
 *    first SS Control Read.
 *  - This state indicates workaround completion. Workarounds no दीर्घer
 *    need to be applied (as दीर्घ as the chip reमुख्यs घातered up).
 *  - Tip: Once in this state the FSM state करोes not change (until
 *    the chip's घातer is lost and restored).
 *  - This can be thought of as the final state of the FSM;
 *    the FSM 'locks-up' in this state until the chip loses घातer.
 */
#घोषणा DEFECT7374_FSM_SS_CONTROL_READ (3 << DEFECT7374_FSM_FIELD)

#अगर_घोषित USE_RDK_LEDS

अटल अंतरभूत व्योम net2280_led_init(काष्ठा net2280 *dev)
अणु
	/* LED3 (green) is on during USB activity. note erratum 0113. */
	ग_लिखोl(BIT(GPIO3_LED_SELECT) |
		BIT(GPIO3_OUTPUT_ENABLE) |
		BIT(GPIO2_OUTPUT_ENABLE) |
		BIT(GPIO1_OUTPUT_ENABLE) |
		BIT(GPIO0_OUTPUT_ENABLE),
		&dev->regs->gpioctl);
पूर्ण

/* indicate speed with bi-color LED 0/1 */
अटल अंतरभूत
व्योम net2280_led_speed(काष्ठा net2280 *dev, क्रमागत usb_device_speed speed)
अणु
	u32	val = पढ़ोl(&dev->regs->gpioctl);
	चयन (speed) अणु
	हाल USB_SPEED_SUPER:		/* green + red */
		val |= BIT(GPIO0_DATA) | BIT(GPIO1_DATA);
		अवरोध;
	हाल USB_SPEED_HIGH:		/* green */
		val &= ~BIT(GPIO0_DATA);
		val |= BIT(GPIO1_DATA);
		अवरोध;
	हाल USB_SPEED_FULL:		/* red */
		val &= ~BIT(GPIO1_DATA);
		val |= BIT(GPIO0_DATA);
		अवरोध;
	शेष:			/* (off/black) */
		val &= ~(BIT(GPIO1_DATA) | BIT(GPIO0_DATA));
		अवरोध;
	पूर्ण
	ग_लिखोl(val, &dev->regs->gpioctl);
पूर्ण

/* indicate घातer with LED 2 */
अटल अंतरभूत व्योम net2280_led_active(काष्ठा net2280 *dev, पूर्णांक is_active)
अणु
	u32	val = पढ़ोl(&dev->regs->gpioctl);

	/* FIXME this LED never seems to turn on.*/
	अगर (is_active)
		val |= GPIO2_DATA;
	अन्यथा
		val &= ~GPIO2_DATA;
	ग_लिखोl(val, &dev->regs->gpioctl);
पूर्ण

अटल अंतरभूत व्योम net2280_led_shutकरोwn(काष्ठा net2280 *dev)
अणु
	/* turn off all four GPIO*_DATA bits */
	ग_लिखोl(पढ़ोl(&dev->regs->gpioctl) & ~0x0f,
			&dev->regs->gpioctl);
पूर्ण

#अन्यथा

#घोषणा net2280_led_init(dev)		करो अणु पूर्ण जबतक (0)
#घोषणा net2280_led_speed(dev, speed)	करो अणु पूर्ण जबतक (0)
#घोषणा net2280_led_shutकरोwn(dev)	करो अणु पूर्ण जबतक (0)

#पूर्ण_अगर

/*-------------------------------------------------------------------------*/

#घोषणा ep_dbg(ndev, fmt, args...) \
	dev_dbg((&((ndev)->pdev->dev)), fmt, ##args)

#घोषणा ep_vdbg(ndev, fmt, args...) \
	dev_vdbg((&((ndev)->pdev->dev)), fmt, ##args)

#घोषणा ep_info(ndev, fmt, args...) \
	dev_info((&((ndev)->pdev->dev)), fmt, ##args)

#घोषणा ep_warn(ndev, fmt, args...) \
	dev_warn((&((ndev)->pdev->dev)), fmt, ##args)

#घोषणा ep_err(ndev, fmt, args...) \
	dev_err((&((ndev)->pdev->dev)), fmt, ##args)

/*-------------------------------------------------------------------------*/

अटल अंतरभूत व्योम set_fअगरo_bytecount(काष्ठा net2280_ep *ep, अचिन्हित count)
अणु
	अगर (ep->dev->pdev->venकरोr == 0x17cc)
		ग_लिखोb(count, 2 + (u8 __iomem *) &ep->regs->ep_cfg);
	अन्यथाअणु
		u32 पंचांगp = पढ़ोl(&ep->cfg->ep_cfg) &
					(~(0x07 << EP_FIFO_BYTE_COUNT));
		ग_लिखोl(पंचांगp | (count << EP_FIFO_BYTE_COUNT), &ep->cfg->ep_cfg);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम start_out_naking(काष्ठा net2280_ep *ep)
अणु
	/* NOTE:  hardware races lurk here, and PING protocol issues */
	ग_लिखोl(BIT(SET_NAK_OUT_PACKETS), &ep->regs->ep_rsp);
	/* synch with device */
	पढ़ोl(&ep->regs->ep_rsp);
पूर्ण

अटल अंतरभूत व्योम stop_out_naking(काष्ठा net2280_ep *ep)
अणु
	u32	पंचांगp;

	पंचांगp = पढ़ोl(&ep->regs->ep_stat);
	अगर ((पंचांगp & BIT(NAK_OUT_PACKETS)) != 0)
		ग_लिखोl(BIT(CLEAR_NAK_OUT_PACKETS), &ep->regs->ep_rsp);
पूर्ण


अटल अंतरभूत व्योम set_max_speed(काष्ठा net2280_ep *ep, u32 max)
अणु
	u32 reg;
	अटल स्थिर u32 ep_enhanced[9] = अणु 0x10, 0x60, 0x30, 0x80,
					  0x50, 0x20, 0x70, 0x40, 0x90 पूर्ण;

	अगर (ep->dev->enhanced_mode) अणु
		reg = ep_enhanced[ep->num];
		चयन (ep->dev->gadget.speed) अणु
		हाल USB_SPEED_SUPER:
			reg += 2;
			अवरोध;
		हाल USB_SPEED_FULL:
			reg += 1;
			अवरोध;
		हाल USB_SPEED_HIGH:
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		reg = (ep->num + 1) * 0x10;
		अगर (ep->dev->gadget.speed != USB_SPEED_HIGH)
			reg += 1;
	पूर्ण

	set_idx_reg(ep->dev->regs, reg, max);
पूर्ण

#पूर्ण_अगर	/* __KERNEL__ */
