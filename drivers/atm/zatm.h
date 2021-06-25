<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* drivers/aपंचांग/zaपंचांग.h - ZeitNet ZN122x device driver declarations */

/* Written 1995-1998 by Werner Almesberger, EPFL LRC/ICA */


#अगर_अघोषित DRIVER_ATM_ZATM_H
#घोषणा DRIVER_ATM_ZATM_H

#समावेश <linux/skbuff.h>
#समावेश <linux/aपंचांग.h>
#समावेश <linux/aपंचांगdev.h>
#समावेश <linux/sonet.h>
#समावेश <linux/pci.h>


#घोषणा DEV_LABEL	"zatm"

#घोषणा MAX_AAL5_PDU	10240	/* allocate क्रम AAL5 PDUs of this size */
#घोषणा MAX_RX_SIZE_LD	14	/* उच्चमान(log2((MAX_AAL5_PDU+47)/48)) */

#घोषणा LOW_MARK	12	/* start adding new buffers अगर less than 12 */
#घोषणा HIGH_MARK	30	/* stop adding buffers after reaching 30 */
#घोषणा OFF_CNG_THRES	5	/* threshold क्रम offset changes */

#घोषणा RX_SIZE		2	/* RX lookup entry size (in bytes) */
#घोषणा NR_POOLS	32	/* number of मुक्त buffer poपूर्णांकers */
#घोषणा POOL_SIZE	8	/* buffer entry size (in bytes) */
#घोषणा NR_SHAPERS	16	/* number of shapers */
#घोषणा SHAPER_SIZE	4	/* shaper entry size (in bytes) */
#घोषणा VC_SIZE		32	/* VC dsc (TX or RX) size (in bytes) */

#घोषणा RING_ENTRIES	32	/* ring entries (without back poपूर्णांकer) */
#घोषणा RING_WORDS	4	/* ring element size */
#घोषणा RING_SIZE	(माप(अचिन्हित दीर्घ)*(RING_ENTRIES+1)*RING_WORDS)

#घोषणा NR_MBX		4	/* four mailboxes */
#घोषणा MBX_RX_0	0	/* mailbox indices */
#घोषणा MBX_RX_1	1
#घोषणा MBX_TX_0	2
#घोषणा MBX_TX_1	3

काष्ठा zaपंचांग_vcc अणु
	/*-------------------------------- RX part */
	पूर्णांक rx_chan;			/* RX channel, 0 अगर none */
	पूर्णांक pool;			/* मुक्त buffer pool */
	/*-------------------------------- TX part */
	पूर्णांक tx_chan;			/* TX channel, 0 अगर none */
	पूर्णांक shaper;			/* shaper, <0 अगर none */
	काष्ठा sk_buff_head tx_queue;	/* list of buffers in transit */
	रुको_queue_head_t tx_रुको;	/* क्रम बंद */
	u32 *ring;			/* transmit ring */
	पूर्णांक ring_curr;			/* current ग_लिखो position */
	पूर्णांक txing;			/* number of transmits in progress */
	काष्ठा sk_buff_head backlog;	/* list of buffers रुकोing क्रम ring */
पूर्ण;

काष्ठा zaपंचांग_dev अणु
	/*-------------------------------- TX part */
	पूर्णांक tx_bw;			/* reमुख्यing bandwidth */
	u32 मुक्त_shapers;		/* bit set */
	पूर्णांक ubr;			/* UBR shaper; -1 अगर none */
	पूर्णांक ubr_ref_cnt;		/* number of VCs using UBR shaper */
	/*-------------------------------- RX part */
	पूर्णांक pool_ref[NR_POOLS];		/* मुक्त buffer pool usage counters */
	अस्थिर काष्ठा sk_buff *last_मुक्त[NR_POOLS];
					/* last entry in respective pool */
	काष्ठा sk_buff_head pool[NR_POOLS];/* मुक्त buffer pools */
	काष्ठा zaपंचांग_pool_info pool_info[NR_POOLS]; /* pool inक्रमmation */
	/*-------------------------------- maps */
	काष्ठा aपंचांग_vcc **tx_map;	/* TX VCCs */
	काष्ठा aपंचांग_vcc **rx_map;	/* RX VCCs */
	पूर्णांक chans;			/* map size, must be 2^n */
	/*-------------------------------- mailboxes */
	अचिन्हित दीर्घ mbx_start[NR_MBX];/* start addresses */
	dma_addr_t mbx_dma[NR_MBX];
	u16 mbx_end[NR_MBX];		/* end offset (in bytes) */
	/*-------------------------------- other poपूर्णांकers */
	u32 pool_base;			/* Free buffer pool dsc (word addr) */
	/*-------------------------------- ZATM links */
	काष्ठा aपंचांग_dev *more;		/* other ZATM devices */
	/*-------------------------------- general inक्रमmation */
	पूर्णांक mem;			/* RAM on board (in bytes) */
	पूर्णांक khz;			/* समयr घड़ी */
	पूर्णांक copper;			/* PHY type */
	अचिन्हित अक्षर irq;		/* IRQ */
	अचिन्हित पूर्णांक base;		/* IO base address */
	काष्ठा pci_dev *pci_dev;	/* PCI stuff */
	spinlock_t lock;
पूर्ण;


#घोषणा ZATM_DEV(d) ((काष्ठा zaपंचांग_dev *) (d)->dev_data)
#घोषणा ZATM_VCC(d) ((काष्ठा zaपंचांग_vcc *) (d)->dev_data)


काष्ठा zaपंचांग_skb_prv अणु
	काष्ठा aपंचांग_skb_data _;		/* reserved */
	u32 *dsc;			/* poपूर्णांकer to skb's descriptor */
पूर्ण;

#घोषणा ZATM_PRV_DSC(skb) (((काष्ठा zaपंचांग_skb_prv *) (skb)->cb)->dsc)

#पूर्ण_अगर
