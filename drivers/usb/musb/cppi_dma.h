<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (C) 2005-2006 by Texas Instruments */

#अगर_अघोषित _CPPI_DMA_H_
#घोषणा _CPPI_DMA_H_

#समावेश <linux/slab.h>
#समावेश <linux/list.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/dmapool.h>
#समावेश <linux/dmaengine.h>

#समावेश "musb_core.h"
#समावेश "musb_dma.h"

/* CPPI RX/TX state RAM */

काष्ठा cppi_tx_stateram अणु
	u32 tx_head;			/* "DMA packet" head descriptor */
	u32 tx_buf;
	u32 tx_current;			/* current descriptor */
	u32 tx_buf_current;
	u32 tx_info;			/* flags, reमुख्यing buflen */
	u32 tx_rem_len;
	u32 tx_dummy;			/* unused */
	u32 tx_complete;
पूर्ण;

काष्ठा cppi_rx_stateram अणु
	u32 rx_skipbytes;
	u32 rx_head;
	u32 rx_sop;			/* "DMA packet" head descriptor */
	u32 rx_current;			/* current descriptor */
	u32 rx_buf_current;
	u32 rx_len_len;
	u32 rx_cnt_cnt;
	u32 rx_complete;
पूर्ण;

/* hw_options bits in CPPI buffer descriptors */
#घोषणा CPPI_SOP_SET	((u32)(1 << 31))
#घोषणा CPPI_EOP_SET	((u32)(1 << 30))
#घोषणा CPPI_OWN_SET	((u32)(1 << 29))	/* owned by cppi */
#घोषणा CPPI_EOQ_MASK	((u32)(1 << 28))
#घोषणा CPPI_ZERO_SET	((u32)(1 << 23))	/* rx saw zlp; tx issues one */
#घोषणा CPPI_RXABT_MASK	((u32)(1 << 19))	/* need more rx buffers */

#घोषणा CPPI_RECV_PKTLEN_MASK 0xFFFF
#घोषणा CPPI_BUFFER_LEN_MASK 0xFFFF

#घोषणा CPPI_TEAR_READY ((u32)(1 << 31))

/* CPPI data काष्ठाure definitions */

#घोषणा	CPPI_DESCRIPTOR_ALIGN	16	/* bytes; 5-dec करोcs say 4-byte align */

काष्ठा cppi_descriptor अणु
	/* hardware overlay */
	u32		hw_next;	/* next buffer descriptor Poपूर्णांकer */
	u32		hw_bufp;	/* i/o buffer poपूर्णांकer */
	u32		hw_off_len;	/* buffer_offset16, buffer_length16 */
	u32		hw_options;	/* flags:  SOP, EOP etc*/

	काष्ठा cppi_descriptor *next;
	dma_addr_t	dma;		/* address of this descriptor */
	u32		buflen;		/* क्रम RX: original buffer length */
पूर्ण __attribute__ ((aligned(CPPI_DESCRIPTOR_ALIGN)));


काष्ठा cppi;

/* CPPI  Channel Control काष्ठाure */
काष्ठा cppi_channel अणु
	काष्ठा dma_channel	channel;

	/* back poपूर्णांकer to the DMA controller काष्ठाure */
	काष्ठा cppi		*controller;

	/* which direction of which endpoपूर्णांक? */
	काष्ठा musb_hw_ep	*hw_ep;
	bool			transmit;
	u8			index;

	/* DMA modes:  RNDIS or "transparent" */
	u8			is_rndis;

	/* book keeping क्रम current transfer request */
	dma_addr_t		buf_dma;
	u32			buf_len;
	u32			maxpacket;
	u32			offset;		/* dma requested */

	व्योम __iomem		*state_ram;	/* CPPI state */

	काष्ठा cppi_descriptor	*मुक्तlist;

	/* BD management fields */
	काष्ठा cppi_descriptor	*head;
	काष्ठा cppi_descriptor	*tail;
	काष्ठा cppi_descriptor	*last_processed;

	/* use tx_complete in host role to track endpoपूर्णांकs रुकोing क्रम
	 * FIFONOTEMPTY to clear.
	 */
	काष्ठा list_head	tx_complete;
पूर्ण;

/* CPPI DMA controller object */
काष्ठा cppi अणु
	काष्ठा dma_controller		controller;
	व्योम __iomem			*mregs;		/* Mentor regs */
	व्योम __iomem			*tibase;	/* TI/CPPI regs */

	पूर्णांक				irq;

	काष्ठा cppi_channel		tx[4];
	काष्ठा cppi_channel		rx[4];

	काष्ठा dma_pool			*pool;

	काष्ठा list_head		tx_complete;
पूर्ण;

/* CPPI IRQ handler */
बाह्य irqवापस_t cppi_पूर्णांकerrupt(पूर्णांक, व्योम *);

काष्ठा cppi41_dma_channel अणु
	काष्ठा dma_channel channel;
	काष्ठा cppi41_dma_controller *controller;
	काष्ठा musb_hw_ep *hw_ep;
	काष्ठा dma_chan *dc;
	dma_cookie_t cookie;
	u8 port_num;
	u8 is_tx;
	u8 is_allocated;
	u8 usb_toggle;

	dma_addr_t buf_addr;
	u32 total_len;
	u32 prog_len;
	u32 transferred;
	u32 packet_sz;
	काष्ठा list_head tx_check;
	पूर्णांक tx_zlp;
पूर्ण;

#पूर्ण_अगर				/* end of अगरndef _CPPI_DMA_H_ */
