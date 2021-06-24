<शैली गुरु>
/*
 * Copyright (c) 2010 Broadcom Corporation
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
 * OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#अगर_अघोषित	_BRCM_DMA_H_
#घोषणा	_BRCM_DMA_H_

#समावेश <linux/delay.h>
#समावेश <linux/skbuff.h>
#समावेश "types.h"		/* क्रमward काष्ठाure declarations */

/* map/unmap direction */
#घोषणा	DMA_TX	1		/* TX direction क्रम DMA */
#घोषणा	DMA_RX	2		/* RX direction क्रम DMA */

/* DMA काष्ठाure:
 *  support two DMA engines: 32 bits address or 64 bit addressing
 *  basic DMA रेजिस्टर set is per channel(transmit or receive)
 *  a pair of channels is defined क्रम convenience
 */

/* 32 bits addressing */

काष्ठा dma32diag अणु	/* diag access */
	u32 fअगरoaddr;	/* diag address */
	u32 fअगरodatalow;	/* low 32bits of data */
	u32 fअगरodatahigh;	/* high 32bits of data */
	u32 pad;		/* reserved */
पूर्ण;

/* 64 bits addressing */

/* dma रेजिस्टरs per channel(xmt or rcv) */
काष्ठा dma64regs अणु
	u32 control;	/* enable, et al */
	u32 ptr;	/* last descriptor posted to chip */
	u32 addrlow;	/* desc ring base address low 32-bits (8K aligned) */
	u32 addrhigh;	/* desc ring base address bits 63:32 (8K aligned) */
	u32 status0;	/* current descriptor, xmt state */
	u32 status1;	/* active descriptor, xmt error */
पूर्ण;

/* range param क्रम dma_getnexttxp() and dma_txreclaim */
क्रमागत txd_range अणु
	DMA_RANGE_ALL = 1,
	DMA_RANGE_TRANSMITTED,
	DMA_RANGE_TRANSFERED
पूर्ण;

/*
 * Exported data काष्ठाure (पढ़ो-only)
 */
/* export काष्ठाure */
काष्ठा dma_pub अणु
	uपूर्णांक txavail;		/* # मुक्त tx descriptors */
	uपूर्णांक dmactrlflags;	/* dma control flags */

	/* rx error counters */
	uपूर्णांक rxgiants;		/* rx giant frames */
	uपूर्णांक rxnobuf;		/* rx out of dma descriptors */
	/* tx error counters */
	uपूर्णांक txnobuf;		/* tx out of dma descriptors */
पूर्ण;

बाह्य काष्ठा dma_pub *dma_attach(अक्षर *name, काष्ठा brcms_c_info *wlc,
				  uपूर्णांक txregbase, uपूर्णांक rxregbase,
				  uपूर्णांक ntxd, uपूर्णांक nrxd,
				  uपूर्णांक rxbufsize, पूर्णांक rxextheadroom,
				  uपूर्णांक nrxpost, uपूर्णांक rxoffset);

व्योम dma_rxinit(काष्ठा dma_pub *pub);
पूर्णांक dma_rx(काष्ठा dma_pub *pub, काष्ठा sk_buff_head *skb_list);
bool dma_rxfill(काष्ठा dma_pub *pub);
bool dma_rxreset(काष्ठा dma_pub *pub);
bool dma_txreset(काष्ठा dma_pub *pub);
व्योम dma_txinit(काष्ठा dma_pub *pub);
पूर्णांक dma_txfast(काष्ठा brcms_c_info *wlc, काष्ठा dma_pub *pub,
	       काष्ठा sk_buff *p0);
व्योम dma_txflush(काष्ठा dma_pub *pub);
पूर्णांक dma_txpending(काष्ठा dma_pub *pub);
व्योम dma_kick_tx(काष्ठा dma_pub *pub);
व्योम dma_txsuspend(काष्ठा dma_pub *pub);
bool dma_txsuspended(काष्ठा dma_pub *pub);
व्योम dma_txresume(काष्ठा dma_pub *pub);
व्योम dma_txreclaim(काष्ठा dma_pub *pub, क्रमागत txd_range range);
व्योम dma_rxreclaim(काष्ठा dma_pub *pub);
व्योम dma_detach(काष्ठा dma_pub *pub);
अचिन्हित दीर्घ dma_getvar(काष्ठा dma_pub *pub, स्थिर अक्षर *name);
काष्ठा sk_buff *dma_getnexttxp(काष्ठा dma_pub *pub, क्रमागत txd_range range);
व्योम dma_counterreset(काष्ठा dma_pub *pub);

व्योम dma_walk_packets(काष्ठा dma_pub *dmah, व्योम (*callback_fnc)
		      (व्योम *pkt, व्योम *arg_a), व्योम *arg_a);

/*
 * DMA(Bug) on bcm47xx chips seems to declare that the packet is पढ़ोy, but
 * the packet length is not updated yet (by DMA) on the expected समय.
 * Workaround is to hold processor till DMA updates the length, and stay off
 * the bus to allow DMA update the length in buffer
 */
अटल अंतरभूत व्योम dma_spin_क्रम_len(uपूर्णांक len, काष्ठा sk_buff *head)
अणु
#अगर defined(CONFIG_BCM47XX)
	अगर (!len) अणु
		जबतक (!(len = *(u16 *) KSEG1ADDR(head->data)))
			udelay(1);

		*(u16 *) (head->data) = cpu_to_le16((u16) len);
	पूर्ण
#पूर्ण_अगर				/* defined(CONFIG_BCM47XX) */
पूर्ण

#पूर्ण_अगर				/* _BRCM_DMA_H_ */
