<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* drivers/aपंचांग/eni.h - Efficient Networks ENI155P device driver declarations */
 
/* Written 1995-2000 by Werner Almesberger, EPFL LRC/ICA */
 
 
#अगर_अघोषित DRIVER_ATM_ENI_H
#घोषणा DRIVER_ATM_ENI_H

#समावेश <linux/aपंचांग.h>
#समावेश <linux/aपंचांगdev.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/sonet.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/समय.स>
#समावेश <linux/pci.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/atomic.h>

#समावेश "midway.h"


#घोषणा DEV_LABEL	"eni"

#घोषणा UBR_BUFFER	(128*1024)	/* UBR buffer size */

#घोषणा RX_DMA_BUF	  8		/* burst and skip a few things */
#घोषणा TX_DMA_BUF	100		/* should be enough क्रम 64 kB */

#घोषणा DEFAULT_RX_MULT	300		/* max_sdu*3 */
#घोषणा DEFAULT_TX_MULT	300		/* max_sdu*3 */

#घोषणा ENI_ZEROES_SIZE	  4		/* need that many DMA-able zero bytes */


काष्ठा eni_मुक्त अणु
	व्योम __iomem *start;		/* counting in bytes */
	पूर्णांक order;
पूर्ण;

काष्ठा eni_tx अणु
	व्योम __iomem *send;		/* base, 0 अगर unused */
	पूर्णांक prescaler;			/* shaping prescaler */
	पूर्णांक resolution;			/* shaping भागider */
	अचिन्हित दीर्घ tx_pos;		/* current TX ग_लिखो position */
	अचिन्हित दीर्घ words;		/* size of TX queue */
	पूर्णांक index;			/* TX channel number */
	पूर्णांक reserved;			/* reserved peak cell rate */
	पूर्णांक shaping;			/* shaped peak cell rate */
	काष्ठा sk_buff_head backlog;	/* queue of रुकोing TX buffers */
पूर्ण;

काष्ठा eni_vcc अणु
	पूर्णांक (*rx)(काष्ठा aपंचांग_vcc *vcc);	/* RX function, शून्य अगर none */
	व्योम __iomem *recv;		/* receive buffer */
	अचिन्हित दीर्घ words;		/* its size in words */
	अचिन्हित दीर्घ descr;		/* next descriptor (RX) */
	अचिन्हित दीर्घ rx_pos;		/* current RX descriptor pos */
	काष्ठा eni_tx *tx;		/* TXer, शून्य अगर none */
	पूर्णांक rxing;			/* number of pending PDUs */
	पूर्णांक servicing;			/* number of रुकोing VCs (0 or 1) */
	पूर्णांक txing;			/* number of pending TX bytes */
	kसमय_प्रकार बारtamp;		/* क्रम RX timing */
	काष्ठा aपंचांग_vcc *next;		/* next pending RX */
	काष्ठा sk_buff *last;		/* last PDU being DMAed (used to carry
					   discard inक्रमmation) */
पूर्ण;

काष्ठा eni_dev अणु
	/*-------------------------------- spinlock */
	spinlock_t lock;		/* sync with पूर्णांकerrupt */
	काष्ठा tasklet_काष्ठा task;	/* tasklet क्रम पूर्णांकerrupt work */
	u32 events;			/* pending events */
	/*-------------------------------- base poपूर्णांकers पूर्णांकo Midway address
					   space */
	व्योम __iomem *ioaddr;
	व्योम __iomem *phy;		/* PHY पूर्णांकerface chip रेजिस्टरs */
	व्योम __iomem *reg;		/* रेजिस्टर base */
	व्योम __iomem *ram;		/* RAM base */
	व्योम __iomem *vci;		/* VCI table */
	व्योम __iomem *rx_dma;		/* RX DMA queue */
	व्योम __iomem *tx_dma;		/* TX DMA queue */
	व्योम __iomem *service;		/* service list */
	/*-------------------------------- TX part */
	काष्ठा eni_tx tx[NR_CHAN];	/* TX channels */
	काष्ठा eni_tx *ubr;		/* UBR channel */
	काष्ठा sk_buff_head tx_queue;	/* PDUs currently being TX DMAed*/
	रुको_queue_head_t tx_रुको;	/* क्रम बंद */
	पूर्णांक tx_bw;			/* reमुख्यing bandwidth */
	u32 dma[TX_DMA_BUF*2];		/* DMA request scratch area */
	काष्ठा eni_zero अणु		/* aligned "magic" zeroes */
		u32 *addr;
		dma_addr_t dma;
	पूर्ण zero;
	पूर्णांक tx_mult;			/* buffer size multiplier (percent) */
	/*-------------------------------- RX part */
	u32 serv_पढ़ो;			/* host service पढ़ो index */
	काष्ठा aपंचांग_vcc *fast,*last_fast;/* queues of VCCs with pending PDUs */
	काष्ठा aपंचांग_vcc *slow,*last_slow;
	काष्ठा aपंचांग_vcc **rx_map;	/* क्रम fast lookups */
	काष्ठा sk_buff_head rx_queue;	/* PDUs currently being RX-DMAed */
	रुको_queue_head_t rx_रुको;	/* क्रम बंद */
	पूर्णांक rx_mult;			/* buffer size multiplier (percent) */
	/*-------------------------------- statistics */
	अचिन्हित दीर्घ lost;		/* number of lost cells (RX) */
	/*-------------------------------- memory management */
	अचिन्हित दीर्घ base_dअगरf;	/* भव-real base address */
	पूर्णांक मुक्त_len;			/* मुक्त list length */
	काष्ठा eni_मुक्त *मुक्त_list;	/* मुक्त list */
	पूर्णांक मुक्त_list_size;		/* maximum size of मुक्त list */
	/*-------------------------------- ENI links */
	काष्ठा aपंचांग_dev *more;		/* other ENI devices */
	/*-------------------------------- general inक्रमmation */
	पूर्णांक mem;			/* RAM on board (in bytes) */
	पूर्णांक asic;			/* PCI पूर्णांकerface type, 0 क्रम FPGA */
	अचिन्हित पूर्णांक irq;		/* IRQ */
	काष्ठा pci_dev *pci_dev;	/* PCI stuff */
पूर्ण;


#घोषणा ENI_DEV(d) ((काष्ठा eni_dev *) (d)->dev_data)
#घोषणा ENI_VCC(d) ((काष्ठा eni_vcc *) (d)->dev_data)


काष्ठा eni_skb_prv अणु
	काष्ठा aपंचांग_skb_data _;		/* reserved */
	अचिन्हित दीर्घ pos;		/* position of next descriptor */
	पूर्णांक size;			/* PDU size in reassembly buffer */
	dma_addr_t paddr;		/* DMA handle */
पूर्ण;

#घोषणा ENI_PRV_SIZE(skb) (((काष्ठा eni_skb_prv *) (skb)->cb)->size)
#घोषणा ENI_PRV_POS(skb) (((काष्ठा eni_skb_prv *) (skb)->cb)->pos)
#घोषणा ENI_PRV_PADDR(skb) (((काष्ठा eni_skb_prv *) (skb)->cb)->paddr)

#पूर्ण_अगर
