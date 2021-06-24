<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * MUSB OTG driver DMA controller असलtraction
 *
 * Copyright 2005 Mentor Graphics Corporation
 * Copyright (C) 2005-2006 by Texas Instruments
 * Copyright (C) 2006-2007 Nokia Corporation
 */

#अगर_अघोषित __MUSB_DMA_H__
#घोषणा __MUSB_DMA_H__

काष्ठा musb_hw_ep;

/*
 * DMA Controller Abstraction
 *
 * DMA Controllers are असलtracted to allow use of a variety of dअगरferent
 * implementations of DMA, as allowed by the Inventra USB cores.  On the
 * host side, usbcore sets up the DMA mappings and flushes caches; on the
 * peripheral side, the gadget controller driver करोes.  Responsibilities
 * of a DMA controller driver include:
 *
 *  - Handling the details of moving multiple USB packets
 *    in cooperation with the Inventra USB core, including especially
 *    the correct RX side treaपंचांगent of लघु packets and buffer-full
 *    states (both of which terminate transfers).
 *
 *  - Knowing the correlation between dma channels and the
 *    Inventra core's local endpoपूर्णांक resources and data direction.
 *
 *  - Maपूर्णांकaining a list of allocated/available channels.
 *
 *  - Updating channel status on पूर्णांकerrupts,
 *    whether shared with the Inventra core or separate.
 */

#घोषणा MUSB_HSDMA_BASE		0x200
#घोषणा MUSB_HSDMA_INTR		(MUSB_HSDMA_BASE + 0)
#घोषणा MUSB_HSDMA_CONTROL	0x4
#घोषणा MUSB_HSDMA_ADDRESS	0x8
#घोषणा MUSB_HSDMA_COUNT	0xc

#घोषणा	DMA_ADDR_INVALID	(~(dma_addr_t)0)

#अगर_घोषित CONFIG_MUSB_PIO_ONLY
#घोषणा	is_dma_capable()	(0)
#अन्यथा
#घोषणा	is_dma_capable()	(1)
#पूर्ण_अगर

#अगर_घोषित CONFIG_USB_UX500_DMA
#घोषणा musb_dma_ux500(musb)		(musb->ops->quirks & MUSB_DMA_UX500)
#अन्यथा
#घोषणा musb_dma_ux500(musb)		0
#पूर्ण_अगर

#अगर_घोषित CONFIG_USB_TI_CPPI41_DMA
#घोषणा musb_dma_cppi41(musb)		(musb->ops->quirks & MUSB_DMA_CPPI41)
#अन्यथा
#घोषणा musb_dma_cppi41(musb)		0
#पूर्ण_अगर

#अगर_घोषित CONFIG_USB_TI_CPPI_DMA
#घोषणा musb_dma_cppi(musb)		(musb->ops->quirks & MUSB_DMA_CPPI)
#अन्यथा
#घोषणा musb_dma_cppi(musb)		0
#पूर्ण_अगर

#अगर_घोषित CONFIG_USB_TUSB_OMAP_DMA
#घोषणा tusb_dma_omap(musb)		(musb->ops->quirks & MUSB_DMA_TUSB_OMAP)
#अन्यथा
#घोषणा tusb_dma_omap(musb)		0
#पूर्ण_अगर

#अगर_घोषित CONFIG_USB_INVENTRA_DMA
#घोषणा musb_dma_inventra(musb)		(musb->ops->quirks & MUSB_DMA_INVENTRA)
#अन्यथा
#घोषणा musb_dma_inventra(musb)		0
#पूर्ण_अगर

#अगर defined(CONFIG_USB_TI_CPPI_DMA) || defined(CONFIG_USB_TI_CPPI41_DMA)
#घोषणा	is_cppi_enabled(musb)		\
	(musb_dma_cppi(musb) || musb_dma_cppi41(musb))
#अन्यथा
#घोषणा	is_cppi_enabled(musb)	0
#पूर्ण_अगर

/*
 * DMA channel status ... updated by the dma controller driver whenever that
 * status changes, and रक्षित by the overall controller spinlock.
 */
क्रमागत dma_channel_status अणु
	/* unallocated */
	MUSB_DMA_STATUS_UNKNOWN,
	/* allocated ... but not busy, no errors */
	MUSB_DMA_STATUS_FREE,
	/* busy ... transactions are active */
	MUSB_DMA_STATUS_BUSY,
	/* transaction(s) पातed due to ... dma or memory bus error */
	MUSB_DMA_STATUS_BUS_ABORT,
	/* transaction(s) पातed due to ... core error or USB fault */
	MUSB_DMA_STATUS_CORE_ABORT
पूर्ण;

काष्ठा dma_controller;

/**
 * काष्ठा dma_channel - A DMA channel.
 * @निजी_data: channel-निजी data
 * @max_len: the maximum number of bytes the channel can move in one
 *	transaction (typically representing many USB maximum-sized packets)
 * @actual_len: how many bytes have been transferred
 * @status: current channel status (updated e.g. on पूर्णांकerrupt)
 * @desired_mode: true अगर mode 1 is desired; false अगर mode 0 is desired
 *
 * channels are associated with an endpoपूर्णांक क्रम the duration of at least
 * one usb transfer.
 */
काष्ठा dma_channel अणु
	व्योम			*निजी_data;
	/* FIXME not व्योम* निजी_data, but a dma_controller * */
	माप_प्रकार			max_len;
	माप_प्रकार			actual_len;
	क्रमागत dma_channel_status	status;
	bool			desired_mode;
	bool			rx_packet_करोne;
पूर्ण;

/*
 * dma_channel_status - वापस status of dma channel
 * @c: the channel
 *
 * Returns the software's view of the channel status.  If that status is BUSY
 * then it's possible that the hardware has completed (or पातed) a transfer,
 * so the driver needs to update that status.
 */
अटल अंतरभूत क्रमागत dma_channel_status
dma_channel_status(काष्ठा dma_channel *c)
अणु
	वापस (is_dma_capable() && c) ? c->status : MUSB_DMA_STATUS_UNKNOWN;
पूर्ण

/**
 * काष्ठा dma_controller - A DMA Controller.
 * @musb: the usb controller
 * @start: call this to start a DMA controller;
 *	वापस 0 on success, अन्यथा negative त्रुटि_सं
 * @stop: call this to stop a DMA controller
 *	वापस 0 on success, अन्यथा negative त्रुटि_सं
 * @channel_alloc: call this to allocate a DMA channel
 * @channel_release: call this to release a DMA channel
 * @channel_पात: call this to पात a pending DMA transaction,
 *	वापसing it to FREE (but allocated) state
 * @dma_callback: invoked on DMA completion, useful to run platक्रमm
 *	code such IRQ acknowledgment.
 *
 * Controllers manage dma channels.
 */
काष्ठा dma_controller अणु
	काष्ठा musb *musb;
	काष्ठा dma_channel	*(*channel_alloc)(काष्ठा dma_controller *,
					काष्ठा musb_hw_ep *, u8 is_tx);
	व्योम			(*channel_release)(काष्ठा dma_channel *);
	पूर्णांक			(*channel_program)(काष्ठा dma_channel *channel,
							u16 maxpacket, u8 mode,
							dma_addr_t dma_addr,
							u32 length);
	पूर्णांक			(*channel_पात)(काष्ठा dma_channel *);
	पूर्णांक			(*is_compatible)(काष्ठा dma_channel *channel,
							u16 maxpacket,
							व्योम *buf, u32 length);
	व्योम			(*dma_callback)(काष्ठा dma_controller *);
पूर्ण;

/* called after channel_program(), may indicate a fault */
बाह्य व्योम musb_dma_completion(काष्ठा musb *musb, u8 epnum, u8 transmit);

#अगर_घोषित CONFIG_MUSB_PIO_ONLY
अटल अंतरभूत काष्ठा dma_controller *
musb_dma_controller_create(काष्ठा musb *m, व्योम __iomem *io)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम musb_dma_controller_destroy(काष्ठा dma_controller *d) अणु पूर्ण

#अन्यथा

बाह्य काष्ठा dma_controller *
(*musb_dma_controller_create)(काष्ठा musb *, व्योम __iomem *);

बाह्य व्योम (*musb_dma_controller_destroy)(काष्ठा dma_controller *);
#पूर्ण_अगर

/* Platक्रमm specअगरic DMA functions */
बाह्य काष्ठा dma_controller *
musbhs_dma_controller_create(काष्ठा musb *musb, व्योम __iomem *base);
बाह्य व्योम musbhs_dma_controller_destroy(काष्ठा dma_controller *c);
बाह्य काष्ठा dma_controller *
musbhs_dma_controller_create_noirq(काष्ठा musb *musb, व्योम __iomem *base);
बाह्य irqवापस_t dma_controller_irq(पूर्णांक irq, व्योम *निजी_data);

बाह्य काष्ठा dma_controller *
tusb_dma_controller_create(काष्ठा musb *musb, व्योम __iomem *base);
बाह्य व्योम tusb_dma_controller_destroy(काष्ठा dma_controller *c);

बाह्य काष्ठा dma_controller *
cppi_dma_controller_create(काष्ठा musb *musb, व्योम __iomem *base);
बाह्य व्योम cppi_dma_controller_destroy(काष्ठा dma_controller *c);

बाह्य काष्ठा dma_controller *
cppi41_dma_controller_create(काष्ठा musb *musb, व्योम __iomem *base);
बाह्य व्योम cppi41_dma_controller_destroy(काष्ठा dma_controller *c);

बाह्य काष्ठा dma_controller *
ux500_dma_controller_create(काष्ठा musb *musb, व्योम __iomem *base);
बाह्य व्योम ux500_dma_controller_destroy(काष्ठा dma_controller *c);

#पूर्ण_अगर	/* __MUSB_DMA_H__ */
