<शैली गुरु>
/*
 *  Driver क्रम the IDT RC32434 (Korina) on-chip ethernet controller.
 *
 *  Copyright 2004 IDT Inc. (rischelp@idt.com)
 *  Copyright 2006 Felix Fietkau <nbd@खोलोwrt.org>
 *  Copyright 2008 Florian Fainelli <florian@खोलोwrt.org>
 *  Copyright 2017 Roman Yeryomin <roman@advem.lv>
 *
 *  This program is मुक्त software; you can redistribute  it and/or modअगरy it
 *  under  the terms of  the GNU General  Public License as published by the
 *  Free Software Foundation;  either version 2 of the  License, or (at your
 *  option) any later version.
 *
 *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS'' AND   ANY  EXPRESS OR IMPLIED
 *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF
 *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN
 *  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   सूचीECT, INसूचीECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF
 *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *  You should have received a copy of the  GNU General Public License aदीर्घ
 *  with this program; अगर not, ग_लिखो  to the Free Software Foundation, Inc.,
 *  675 Mass Ave, Cambridge, MA 02139, USA.
 *
 *  Writing to a DMA status रेजिस्टर:
 *
 *  When writing to the status रेजिस्टर, you should mask the bit you have
 *  been testing the status रेजिस्टर with. Both Tx and Rx DMA रेजिस्टरs
 *  should stick to this procedure.
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/sched.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/types.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/in.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_net.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/delay.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mii.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/crc32.h>
#समावेश <linux/pgtable.h>
#समावेश <linux/clk.h>

#घोषणा DRV_NAME	"korina"
#घोषणा DRV_VERSION	"0.20"
#घोषणा DRV_RELDATE	"15Sep2017"

काष्ठा eth_regs अणु
	u32 ethपूर्णांकfc;
	u32 ethfअगरott;
	u32 etharc;
	u32 ethhash0;
	u32 ethhash1;
	u32 ethu0[4];		/* Reserved. */
	u32 ethpfs;
	u32 ethmcp;
	u32 eth_u1[10];		/* Reserved. */
	u32 ethspare;
	u32 eth_u2[42];		/* Reserved. */
	u32 ethsal0;
	u32 ethsah0;
	u32 ethsal1;
	u32 ethsah1;
	u32 ethsal2;
	u32 ethsah2;
	u32 ethsal3;
	u32 ethsah3;
	u32 ethrbc;
	u32 ethrpc;
	u32 ethrupc;
	u32 ethrfc;
	u32 ethtbc;
	u32 ethgpf;
	u32 eth_u9[50];		/* Reserved. */
	u32 ethmac1;
	u32 ethmac2;
	u32 ethipgt;
	u32 ethipgr;
	u32 ethclrt;
	u32 ethmaxf;
	u32 eth_u10;		/* Reserved. */
	u32 ethmtest;
	u32 miimcfg;
	u32 miimcmd;
	u32 miimaddr;
	u32 miimwtd;
	u32 miimrdd;
	u32 miimind;
	u32 eth_u11;		/* Reserved. */
	u32 eth_u12;		/* Reserved. */
	u32 ethcfsa0;
	u32 ethcfsa1;
	u32 ethcfsa2;
पूर्ण;

/* Ethernet पूर्णांकerrupt रेजिस्टरs */
#घोषणा ETH_INT_FC_EN		BIT(0)
#घोषणा ETH_INT_FC_ITS		BIT(1)
#घोषणा ETH_INT_FC_RIP		BIT(2)
#घोषणा ETH_INT_FC_JAM		BIT(3)
#घोषणा ETH_INT_FC_OVR		BIT(4)
#घोषणा ETH_INT_FC_UND		BIT(5)
#घोषणा ETH_INT_FC_IOC		0x000000c0

/* Ethernet FIFO रेजिस्टरs */
#घोषणा ETH_FIFI_TT_TTH_BIT	0
#घोषणा ETH_FIFO_TT_TTH		0x0000007f

/* Ethernet ARC/multicast रेजिस्टरs */
#घोषणा ETH_ARC_PRO		BIT(0)
#घोषणा ETH_ARC_AM		BIT(1)
#घोषणा ETH_ARC_AFM		BIT(2)
#घोषणा ETH_ARC_AB		BIT(3)

/* Ethernet SAL रेजिस्टरs */
#घोषणा ETH_SAL_BYTE_5		0x000000ff
#घोषणा ETH_SAL_BYTE_4		0x0000ff00
#घोषणा ETH_SAL_BYTE_3		0x00ff0000
#घोषणा ETH_SAL_BYTE_2		0xff000000

/* Ethernet SAH रेजिस्टरs */
#घोषणा ETH_SAH_BYTE1		0x000000ff
#घोषणा ETH_SAH_BYTE0		0x0000ff00

/* Ethernet GPF रेजिस्टर */
#घोषणा ETH_GPF_PTV		0x0000ffff

/* Ethernet PFG रेजिस्टर */
#घोषणा ETH_PFS_PFD		BIT(0)

/* Ethernet CFSA[0-3] रेजिस्टरs */
#घोषणा ETH_CFSA0_CFSA4		0x000000ff
#घोषणा ETH_CFSA0_CFSA5		0x0000ff00
#घोषणा ETH_CFSA1_CFSA2		0x000000ff
#घोषणा ETH_CFSA1_CFSA3		0x0000ff00
#घोषणा ETH_CFSA1_CFSA0		0x000000ff
#घोषणा ETH_CFSA1_CFSA1		0x0000ff00

/* Ethernet MAC1 रेजिस्टरs */
#घोषणा ETH_MAC1_RE		BIT(0)
#घोषणा ETH_MAC1_PAF		BIT(1)
#घोषणा ETH_MAC1_RFC		BIT(2)
#घोषणा ETH_MAC1_TFC		BIT(3)
#घोषणा ETH_MAC1_LB		BIT(4)
#घोषणा ETH_MAC1_MR		BIT(31)

/* Ethernet MAC2 रेजिस्टरs */
#घोषणा ETH_MAC2_FD		BIT(0)
#घोषणा ETH_MAC2_FLC		BIT(1)
#घोषणा ETH_MAC2_HFE		BIT(2)
#घोषणा ETH_MAC2_DC		BIT(3)
#घोषणा ETH_MAC2_CEN		BIT(4)
#घोषणा ETH_MAC2_PE		BIT(5)
#घोषणा ETH_MAC2_VPE		BIT(6)
#घोषणा ETH_MAC2_APE		BIT(7)
#घोषणा ETH_MAC2_PPE		BIT(8)
#घोषणा ETH_MAC2_LPE		BIT(9)
#घोषणा ETH_MAC2_NB		BIT(12)
#घोषणा ETH_MAC2_BP		BIT(13)
#घोषणा ETH_MAC2_ED		BIT(14)

/* Ethernet IPGT रेजिस्टर */
#घोषणा ETH_IPGT		0x0000007f

/* Ethernet IPGR रेजिस्टरs */
#घोषणा ETH_IPGR_IPGR2		0x0000007f
#घोषणा ETH_IPGR_IPGR1		0x00007f00

/* Ethernet CLRT रेजिस्टरs */
#घोषणा ETH_CLRT_MAX_RET	0x0000000f
#घोषणा ETH_CLRT_COL_WIN	0x00003f00

/* Ethernet MAXF रेजिस्टर */
#घोषणा ETH_MAXF		0x0000ffff

/* Ethernet test रेजिस्टरs */
#घोषणा ETH_TEST_REG		BIT(2)
#घोषणा ETH_MCP_DIV		0x000000ff

/* MII रेजिस्टरs */
#घोषणा ETH_MII_CFG_RSVD	0x0000000c
#घोषणा ETH_MII_CMD_RD		BIT(0)
#घोषणा ETH_MII_CMD_SCN		BIT(1)
#घोषणा ETH_MII_REG_ADDR	0x0000001f
#घोषणा ETH_MII_PHY_ADDR	0x00001f00
#घोषणा ETH_MII_WTD_DATA	0x0000ffff
#घोषणा ETH_MII_RDD_DATA	0x0000ffff
#घोषणा ETH_MII_IND_BSY		BIT(0)
#घोषणा ETH_MII_IND_SCN		BIT(1)
#घोषणा ETH_MII_IND_NV		BIT(2)

/* Values क्रम the DEVCS field of the Ethernet DMA Rx and Tx descriptors. */
#घोषणा ETH_RX_FD		BIT(0)
#घोषणा ETH_RX_LD		BIT(1)
#घोषणा ETH_RX_ROK		BIT(2)
#घोषणा ETH_RX_FM		BIT(3)
#घोषणा ETH_RX_MP		BIT(4)
#घोषणा ETH_RX_BP		BIT(5)
#घोषणा ETH_RX_VLT		BIT(6)
#घोषणा ETH_RX_CF		BIT(7)
#घोषणा ETH_RX_OVR		BIT(8)
#घोषणा ETH_RX_CRC		BIT(9)
#घोषणा ETH_RX_CV		BIT(10)
#घोषणा ETH_RX_DB		BIT(11)
#घोषणा ETH_RX_LE		BIT(12)
#घोषणा ETH_RX_LOR		BIT(13)
#घोषणा ETH_RX_CES		BIT(14)
#घोषणा ETH_RX_LEN_BIT		16
#घोषणा ETH_RX_LEN		0xffff0000

#घोषणा ETH_TX_FD		BIT(0)
#घोषणा ETH_TX_LD		BIT(1)
#घोषणा ETH_TX_OEN		BIT(2)
#घोषणा ETH_TX_PEN		BIT(3)
#घोषणा ETH_TX_CEN		BIT(4)
#घोषणा ETH_TX_HEN		BIT(5)
#घोषणा ETH_TX_TOK		BIT(6)
#घोषणा ETH_TX_MP		BIT(7)
#घोषणा ETH_TX_BP		BIT(8)
#घोषणा ETH_TX_UND		BIT(9)
#घोषणा ETH_TX_OF		BIT(10)
#घोषणा ETH_TX_ED		BIT(11)
#घोषणा ETH_TX_EC		BIT(12)
#घोषणा ETH_TX_LC		BIT(13)
#घोषणा ETH_TX_TD		BIT(14)
#घोषणा ETH_TX_CRC		BIT(15)
#घोषणा ETH_TX_LE		BIT(16)
#घोषणा ETH_TX_CC		0x001E0000

/* DMA descriptor (in physical memory). */
काष्ठा dma_desc अणु
	u32 control;			/* Control. use DMAD_* */
	u32 ca;				/* Current Address. */
	u32 devcs;			/* Device control and status. */
	u32 link;			/* Next descriptor in chain. */
पूर्ण;

#घोषणा DMA_DESC_COUNT_BIT		0
#घोषणा DMA_DESC_COUNT_MSK		0x0003ffff
#घोषणा DMA_DESC_DS_BIT			20
#घोषणा DMA_DESC_DS_MSK			0x00300000

#घोषणा DMA_DESC_DEV_CMD_BIT		22
#घोषणा DMA_DESC_DEV_CMD_MSK		0x01c00000

/* DMA descriptors पूर्णांकerrupts */
#घोषणा DMA_DESC_COF			BIT(25) /* Chain on finished */
#घोषणा DMA_DESC_COD			BIT(26) /* Chain on करोne */
#घोषणा DMA_DESC_IOF			BIT(27) /* Interrupt on finished */
#घोषणा DMA_DESC_IOD			BIT(28) /* Interrupt on करोne */
#घोषणा DMA_DESC_TERM			BIT(29) /* Terminated */
#घोषणा DMA_DESC_DONE			BIT(30) /* Done */
#घोषणा DMA_DESC_FINI			BIT(31) /* Finished */

/* DMA रेजिस्टर (within Internal Register Map).  */
काष्ठा dma_reg अणु
	u32 dmac;		/* Control. */
	u32 dmas;		/* Status. */
	u32 dmयंत्र;		/* Mask. */
	u32 dmadptr;		/* Descriptor poपूर्णांकer. */
	u32 dmandptr;		/* Next descriptor poपूर्णांकer. */
पूर्ण;

/* DMA channels specअगरic रेजिस्टरs */
#घोषणा DMA_CHAN_RUN_BIT		BIT(0)
#घोषणा DMA_CHAN_DONE_BIT		BIT(1)
#घोषणा DMA_CHAN_MODE_BIT		BIT(2)
#घोषणा DMA_CHAN_MODE_MSK		0x0000000c
#घोषणा	 DMA_CHAN_MODE_AUTO		0
#घोषणा	 DMA_CHAN_MODE_BURST		1
#घोषणा	 DMA_CHAN_MODE_XFRT		2
#घोषणा	 DMA_CHAN_MODE_RSVD		3
#घोषणा DMA_CHAN_ACT_BIT		BIT(4)

/* DMA status रेजिस्टरs */
#घोषणा DMA_STAT_FINI			BIT(0)
#घोषणा DMA_STAT_DONE			BIT(1)
#घोषणा DMA_STAT_CHAIN			BIT(2)
#घोषणा DMA_STAT_ERR			BIT(3)
#घोषणा DMA_STAT_HALT			BIT(4)

#घोषणा STATION_ADDRESS_HIGH(dev) (((dev)->dev_addr[0] << 8) | \
				   ((dev)->dev_addr[1]))
#घोषणा STATION_ADDRESS_LOW(dev)  (((dev)->dev_addr[2] << 24) | \
				   ((dev)->dev_addr[3] << 16) | \
				   ((dev)->dev_addr[4] << 8)  | \
				   ((dev)->dev_addr[5]))

#घोषणा MII_CLOCK	1250000 /* no more than 2.5MHz */

/* the following must be घातers of two */
#घोषणा KORINA_NUM_RDS	64  /* number of receive descriptors */
#घोषणा KORINA_NUM_TDS	64  /* number of transmit descriptors */

/* KORINA_RBSIZE is the hardware's शेष maximum receive
 * frame size in bytes. Having this hardcoded means that there
 * is no support क्रम MTU sizes greater than 1500. */
#घोषणा KORINA_RBSIZE	1536 /* size of one resource buffer = Ether MTU */
#घोषणा KORINA_RDS_MASK	(KORINA_NUM_RDS - 1)
#घोषणा KORINA_TDS_MASK	(KORINA_NUM_TDS - 1)
#घोषणा RD_RING_SIZE	(KORINA_NUM_RDS * माप(काष्ठा dma_desc))
#घोषणा TD_RING_SIZE	(KORINA_NUM_TDS * माप(काष्ठा dma_desc))

#घोषणा TX_TIMEOUT	(6000 * HZ / 1000)

क्रमागत chain_status अणु
	desc_filled,
	desc_is_empty
पूर्ण;

#घोषणा DMA_COUNT(count)	((count) & DMA_DESC_COUNT_MSK)
#घोषणा IS_DMA_FINISHED(X)	(((X) & (DMA_DESC_FINI)) != 0)
#घोषणा IS_DMA_DONE(X)		(((X) & (DMA_DESC_DONE)) != 0)
#घोषणा RCVPKT_LENGTH(X)	(((X) & ETH_RX_LEN) >> ETH_RX_LEN_BIT)

/* Inक्रमmation that need to be kept क्रम each board. */
काष्ठा korina_निजी अणु
	काष्ठा eth_regs __iomem *eth_regs;
	काष्ठा dma_reg __iomem *rx_dma_regs;
	काष्ठा dma_reg __iomem *tx_dma_regs;
	काष्ठा dma_desc *td_ring; /* transmit descriptor ring */
	काष्ठा dma_desc *rd_ring; /* receive descriptor ring  */
	dma_addr_t td_dma;
	dma_addr_t rd_dma;

	काष्ठा sk_buff *tx_skb[KORINA_NUM_TDS];
	काष्ठा sk_buff *rx_skb[KORINA_NUM_RDS];

	dma_addr_t rx_skb_dma[KORINA_NUM_RDS];
	dma_addr_t tx_skb_dma[KORINA_NUM_TDS];

	पूर्णांक rx_next_करोne;
	पूर्णांक rx_chain_head;
	पूर्णांक rx_chain_tail;
	क्रमागत chain_status rx_chain_status;

	पूर्णांक tx_next_करोne;
	पूर्णांक tx_chain_head;
	पूर्णांक tx_chain_tail;
	क्रमागत chain_status tx_chain_status;
	पूर्णांक tx_count;
	पूर्णांक tx_full;

	पूर्णांक rx_irq;
	पूर्णांक tx_irq;

	spinlock_t lock;	/* NIC xmit lock */

	पूर्णांक dma_halt_cnt;
	पूर्णांक dma_run_cnt;
	काष्ठा napi_काष्ठा napi;
	काष्ठा समयr_list media_check_समयr;
	काष्ठा mii_अगर_info mii_अगर;
	काष्ठा work_काष्ठा restart_task;
	काष्ठा net_device *dev;
	काष्ठा device *dmadev;
	पूर्णांक mii_घड़ी_freq;
पूर्ण;

अटल dma_addr_t korina_tx_dma(काष्ठा korina_निजी *lp, पूर्णांक idx)
अणु
	वापस lp->td_dma + (idx * माप(काष्ठा dma_desc));
पूर्ण

अटल dma_addr_t korina_rx_dma(काष्ठा korina_निजी *lp, पूर्णांक idx)
अणु
	वापस lp->rd_dma + (idx * माप(काष्ठा dma_desc));
पूर्ण

अटल अंतरभूत व्योम korina_पात_dma(काष्ठा net_device *dev,
					काष्ठा dma_reg *ch)
अणु
	अगर (पढ़ोl(&ch->dmac) & DMA_CHAN_RUN_BIT) अणु
		ग_लिखोl(0x10, &ch->dmac);

		जबतक (!(पढ़ोl(&ch->dmas) & DMA_STAT_HALT))
			netअगर_trans_update(dev);

		ग_लिखोl(0, &ch->dmas);
	पूर्ण

	ग_लिखोl(0, &ch->dmadptr);
	ग_लिखोl(0, &ch->dmandptr);
पूर्ण

अटल व्योम korina_पात_tx(काष्ठा net_device *dev)
अणु
	काष्ठा korina_निजी *lp = netdev_priv(dev);

	korina_पात_dma(dev, lp->tx_dma_regs);
पूर्ण

अटल व्योम korina_पात_rx(काष्ठा net_device *dev)
अणु
	काष्ठा korina_निजी *lp = netdev_priv(dev);

	korina_पात_dma(dev, lp->rx_dma_regs);
पूर्ण

/* transmit packet */
अटल पूर्णांक korina_send_packet(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा korina_निजी *lp = netdev_priv(dev);
	u32 chain_prev, chain_next;
	अचिन्हित दीर्घ flags;
	काष्ठा dma_desc *td;
	dma_addr_t ca;
	u32 length;
	पूर्णांक idx;

	spin_lock_irqsave(&lp->lock, flags);

	idx = lp->tx_chain_tail;
	td = &lp->td_ring[idx];

	/* stop queue when full, drop pkts अगर queue alपढ़ोy full */
	अगर (lp->tx_count >= (KORINA_NUM_TDS - 2)) अणु
		lp->tx_full = 1;

		अगर (lp->tx_count == (KORINA_NUM_TDS - 2))
			netअगर_stop_queue(dev);
		अन्यथा
			जाओ drop_packet;
	पूर्ण

	lp->tx_count++;

	lp->tx_skb[idx] = skb;

	length = skb->len;

	/* Setup the transmit descriptor. */
	ca = dma_map_single(lp->dmadev, skb->data, length, DMA_TO_DEVICE);
	अगर (dma_mapping_error(lp->dmadev, ca))
		जाओ drop_packet;

	lp->tx_skb_dma[idx] = ca;
	td->ca = ca;

	chain_prev = (idx - 1) & KORINA_TDS_MASK;
	chain_next = (idx + 1) & KORINA_TDS_MASK;

	अगर (पढ़ोl(&(lp->tx_dma_regs->dmandptr)) == 0) अणु
		अगर (lp->tx_chain_status == desc_is_empty) अणु
			/* Update tail */
			td->control = DMA_COUNT(length) |
					DMA_DESC_COF | DMA_DESC_IOF;
			/* Move tail */
			lp->tx_chain_tail = chain_next;
			/* Write to NDPTR */
			ग_लिखोl(korina_tx_dma(lp, lp->tx_chain_head),
			       &lp->tx_dma_regs->dmandptr);
			/* Move head to tail */
			lp->tx_chain_head = lp->tx_chain_tail;
		पूर्ण अन्यथा अणु
			/* Update tail */
			td->control = DMA_COUNT(length) |
					DMA_DESC_COF | DMA_DESC_IOF;
			/* Link to prev */
			lp->td_ring[chain_prev].control &=
					~DMA_DESC_COF;
			/* Link to prev */
			lp->td_ring[chain_prev].link = korina_tx_dma(lp, idx);
			/* Move tail */
			lp->tx_chain_tail = chain_next;
			/* Write to NDPTR */
			ग_लिखोl(korina_tx_dma(lp, lp->tx_chain_head),
			       &lp->tx_dma_regs->dmandptr);
			/* Move head to tail */
			lp->tx_chain_head = lp->tx_chain_tail;
			lp->tx_chain_status = desc_is_empty;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (lp->tx_chain_status == desc_is_empty) अणु
			/* Update tail */
			td->control = DMA_COUNT(length) |
					DMA_DESC_COF | DMA_DESC_IOF;
			/* Move tail */
			lp->tx_chain_tail = chain_next;
			lp->tx_chain_status = desc_filled;
		पूर्ण अन्यथा अणु
			/* Update tail */
			td->control = DMA_COUNT(length) |
					DMA_DESC_COF | DMA_DESC_IOF;
			lp->td_ring[chain_prev].control &=
					~DMA_DESC_COF;
			lp->td_ring[chain_prev].link = korina_tx_dma(lp, idx);
			lp->tx_chain_tail = chain_next;
		पूर्ण
	पूर्ण

	netअगर_trans_update(dev);
	spin_unlock_irqrestore(&lp->lock, flags);

	वापस NETDEV_TX_OK;

drop_packet:
	dev->stats.tx_dropped++;
	dev_kमुक्त_skb_any(skb);
	spin_unlock_irqrestore(&lp->lock, flags);

	वापस NETDEV_TX_OK;
पूर्ण

अटल पूर्णांक korina_mdio_रुको(काष्ठा korina_निजी *lp)
अणु
	u32 value;

	वापस पढ़ोl_poll_समयout_atomic(&lp->eth_regs->miimind,
					 value, value & ETH_MII_IND_BSY,
					 1, 1000);
पूर्ण

अटल पूर्णांक korina_mdio_पढ़ो(काष्ठा net_device *dev, पूर्णांक phy, पूर्णांक reg)
अणु
	काष्ठा korina_निजी *lp = netdev_priv(dev);
	पूर्णांक ret;

	ret = korina_mdio_रुको(lp);
	अगर (ret < 0)
		वापस ret;

	ग_लिखोl(phy << 8 | reg, &lp->eth_regs->miimaddr);
	ग_लिखोl(1, &lp->eth_regs->miimcmd);

	ret = korina_mdio_रुको(lp);
	अगर (ret < 0)
		वापस ret;

	अगर (पढ़ोl(&lp->eth_regs->miimind) & ETH_MII_IND_NV)
		वापस -EINVAL;

	ret = पढ़ोl(&lp->eth_regs->miimrdd);
	ग_लिखोl(0, &lp->eth_regs->miimcmd);
	वापस ret;
पूर्ण

अटल व्योम korina_mdio_ग_लिखो(काष्ठा net_device *dev, पूर्णांक phy, पूर्णांक reg, पूर्णांक val)
अणु
	काष्ठा korina_निजी *lp = netdev_priv(dev);

	अगर (korina_mdio_रुको(lp))
		वापस;

	ग_लिखोl(0, &lp->eth_regs->miimcmd);
	ग_लिखोl(phy << 8 | reg, &lp->eth_regs->miimaddr);
	ग_लिखोl(val, &lp->eth_regs->miimwtd);
पूर्ण

/* Ethernet Rx DMA पूर्णांकerrupt */
अटल irqवापस_t korina_rx_dma_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = dev_id;
	काष्ठा korina_निजी *lp = netdev_priv(dev);
	u32 dmas, dmयंत्र;
	irqवापस_t retval;

	dmas = पढ़ोl(&lp->rx_dma_regs->dmas);
	अगर (dmas & (DMA_STAT_DONE | DMA_STAT_HALT | DMA_STAT_ERR)) अणु
		dmयंत्र = पढ़ोl(&lp->rx_dma_regs->dmयंत्र);
		ग_लिखोl(dmयंत्र | (DMA_STAT_DONE |
				DMA_STAT_HALT | DMA_STAT_ERR),
				&lp->rx_dma_regs->dmयंत्र);

		napi_schedule(&lp->napi);

		अगर (dmas & DMA_STAT_ERR)
			prपूर्णांकk(KERN_ERR "%s: DMA error\n", dev->name);

		retval = IRQ_HANDLED;
	पूर्ण अन्यथा
		retval = IRQ_NONE;

	वापस retval;
पूर्ण

अटल पूर्णांक korina_rx(काष्ठा net_device *dev, पूर्णांक limit)
अणु
	काष्ठा korina_निजी *lp = netdev_priv(dev);
	काष्ठा dma_desc *rd = &lp->rd_ring[lp->rx_next_करोne];
	काष्ठा sk_buff *skb, *skb_new;
	u32 devcs, pkt_len, dmas;
	dma_addr_t ca;
	पूर्णांक count;

	क्रम (count = 0; count < limit; count++) अणु
		skb = lp->rx_skb[lp->rx_next_करोne];
		skb_new = शून्य;

		devcs = rd->devcs;

		अगर ((KORINA_RBSIZE - (u32)DMA_COUNT(rd->control)) == 0)
			अवरोध;

		/* check that this is a whole packet
		 * WARNING: DMA_FD bit incorrectly set
		 * in Rc32434 (errata ref #077) */
		अगर (!(devcs & ETH_RX_LD))
			जाओ next;

		अगर (!(devcs & ETH_RX_ROK)) अणु
			/* Update statistics counters */
			dev->stats.rx_errors++;
			dev->stats.rx_dropped++;
			अगर (devcs & ETH_RX_CRC)
				dev->stats.rx_crc_errors++;
			अगर (devcs & ETH_RX_LE)
				dev->stats.rx_length_errors++;
			अगर (devcs & ETH_RX_OVR)
				dev->stats.rx_fअगरo_errors++;
			अगर (devcs & ETH_RX_CV)
				dev->stats.rx_frame_errors++;
			अगर (devcs & ETH_RX_CES)
				dev->stats.rx_frame_errors++;

			जाओ next;
		पूर्ण

		/* Malloc up new buffer. */
		skb_new = netdev_alloc_skb_ip_align(dev, KORINA_RBSIZE);
		अगर (!skb_new)
			अवरोध;

		ca = dma_map_single(lp->dmadev, skb_new->data, KORINA_RBSIZE,
				    DMA_FROM_DEVICE);
		अगर (dma_mapping_error(lp->dmadev, ca)) अणु
			dev_kमुक्त_skb_any(skb_new);
			अवरोध;
		पूर्ण

		pkt_len = RCVPKT_LENGTH(devcs);
		dma_unmap_single(lp->dmadev, lp->rx_skb_dma[lp->rx_next_करोne],
				 pkt_len, DMA_FROM_DEVICE);

		/* Do not count the CRC */
		skb_put(skb, pkt_len - 4);
		skb->protocol = eth_type_trans(skb, dev);

		/* Pass the packet to upper layers */
		napi_gro_receive(&lp->napi, skb);
		dev->stats.rx_packets++;
		dev->stats.rx_bytes += pkt_len;

		/* Update the mcast stats */
		अगर (devcs & ETH_RX_MP)
			dev->stats.multicast++;

		lp->rx_skb[lp->rx_next_करोne] = skb_new;
		lp->rx_skb_dma[lp->rx_next_करोne] = ca;

next:
		rd->devcs = 0;

		/* Restore descriptor's curr_addr */
		rd->ca = lp->rx_skb_dma[lp->rx_next_करोne];

		rd->control = DMA_COUNT(KORINA_RBSIZE) |
			DMA_DESC_COD | DMA_DESC_IOD;
		lp->rd_ring[(lp->rx_next_करोne - 1) &
			KORINA_RDS_MASK].control &=
			~DMA_DESC_COD;

		lp->rx_next_करोne = (lp->rx_next_करोne + 1) & KORINA_RDS_MASK;
		rd = &lp->rd_ring[lp->rx_next_करोne];
		ग_लिखोl((u32)~DMA_STAT_DONE, &lp->rx_dma_regs->dmas);
	पूर्ण

	dmas = पढ़ोl(&lp->rx_dma_regs->dmas);

	अगर (dmas & DMA_STAT_HALT) अणु
		ग_लिखोl((u32)~(DMA_STAT_HALT | DMA_STAT_ERR),
		       &lp->rx_dma_regs->dmas);

		lp->dma_halt_cnt++;
		rd->devcs = 0;
		rd->ca = lp->rx_skb_dma[lp->rx_next_करोne];
		ग_लिखोl(korina_rx_dma(lp, rd - lp->rd_ring),
		       &lp->rx_dma_regs->dmandptr);
	पूर्ण

	वापस count;
पूर्ण

अटल पूर्णांक korina_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा korina_निजी *lp =
		container_of(napi, काष्ठा korina_निजी, napi);
	काष्ठा net_device *dev = lp->dev;
	पूर्णांक work_करोne;

	work_करोne = korina_rx(dev, budget);
	अगर (work_करोne < budget) अणु
		napi_complete_करोne(napi, work_करोne);

		ग_लिखोl(पढ़ोl(&lp->rx_dma_regs->dmयंत्र) &
			~(DMA_STAT_DONE | DMA_STAT_HALT | DMA_STAT_ERR),
			&lp->rx_dma_regs->dmयंत्र);
	पूर्ण
	वापस work_करोne;
पूर्ण

/*
 * Set or clear the multicast filter क्रम this adaptor.
 */
अटल व्योम korina_multicast_list(काष्ठा net_device *dev)
अणु
	काष्ठा korina_निजी *lp = netdev_priv(dev);
	अचिन्हित दीर्घ flags;
	काष्ठा netdev_hw_addr *ha;
	u32 recognise = ETH_ARC_AB;	/* always accept broadcasts */

	/* Set promiscuous mode */
	अगर (dev->flags & IFF_PROMISC)
		recognise |= ETH_ARC_PRO;

	अन्यथा अगर ((dev->flags & IFF_ALLMULTI) || (netdev_mc_count(dev) > 4))
		/* All multicast and broadcast */
		recognise |= ETH_ARC_AM;

	/* Build the hash table */
	अगर (netdev_mc_count(dev) > 4) अणु
		u16 hash_table[4] = अणु 0 पूर्ण;
		u32 crc;

		netdev_क्रम_each_mc_addr(ha, dev) अणु
			crc = ether_crc_le(6, ha->addr);
			crc >>= 26;
			hash_table[crc >> 4] |= 1 << (15 - (crc & 0xf));
		पूर्ण
		/* Accept filtered multicast */
		recognise |= ETH_ARC_AFM;

		/* Fill the MAC hash tables with their values */
		ग_लिखोl((u32)(hash_table[1] << 16 | hash_table[0]),
					&lp->eth_regs->ethhash0);
		ग_लिखोl((u32)(hash_table[3] << 16 | hash_table[2]),
					&lp->eth_regs->ethhash1);
	पूर्ण

	spin_lock_irqsave(&lp->lock, flags);
	ग_लिखोl(recognise, &lp->eth_regs->etharc);
	spin_unlock_irqrestore(&lp->lock, flags);
पूर्ण

अटल व्योम korina_tx(काष्ठा net_device *dev)
अणु
	काष्ठा korina_निजी *lp = netdev_priv(dev);
	काष्ठा dma_desc *td = &lp->td_ring[lp->tx_next_करोne];
	u32 devcs;
	u32 dmas;

	spin_lock(&lp->lock);

	/* Process all desc that are करोne */
	जबतक (IS_DMA_FINISHED(td->control)) अणु
		अगर (lp->tx_full == 1) अणु
			netअगर_wake_queue(dev);
			lp->tx_full = 0;
		पूर्ण

		devcs = lp->td_ring[lp->tx_next_करोne].devcs;
		अगर ((devcs & (ETH_TX_FD | ETH_TX_LD)) !=
				(ETH_TX_FD | ETH_TX_LD)) अणु
			dev->stats.tx_errors++;
			dev->stats.tx_dropped++;

			/* Should never happen */
			prपूर्णांकk(KERN_ERR "%s: split tx ignored\n",
							dev->name);
		पूर्ण अन्यथा अगर (devcs & ETH_TX_TOK) अणु
			dev->stats.tx_packets++;
			dev->stats.tx_bytes +=
					lp->tx_skb[lp->tx_next_करोne]->len;
		पूर्ण अन्यथा अणु
			dev->stats.tx_errors++;
			dev->stats.tx_dropped++;

			/* Underflow */
			अगर (devcs & ETH_TX_UND)
				dev->stats.tx_fअगरo_errors++;

			/* Oversized frame */
			अगर (devcs & ETH_TX_OF)
				dev->stats.tx_पातed_errors++;

			/* Excessive deferrals */
			अगर (devcs & ETH_TX_ED)
				dev->stats.tx_carrier_errors++;

			/* Collisions: medium busy */
			अगर (devcs & ETH_TX_EC)
				dev->stats.collisions++;

			/* Late collision */
			अगर (devcs & ETH_TX_LC)
				dev->stats.tx_winकरोw_errors++;
		पूर्ण

		/* We must always मुक्त the original skb */
		अगर (lp->tx_skb[lp->tx_next_करोne]) अणु
			dma_unmap_single(lp->dmadev,
					 lp->tx_skb_dma[lp->tx_next_करोne],
					 lp->tx_skb[lp->tx_next_करोne]->len,
					 DMA_TO_DEVICE);
			dev_kमुक्त_skb_any(lp->tx_skb[lp->tx_next_करोne]);
			lp->tx_skb[lp->tx_next_करोne] = शून्य;
		पूर्ण

		lp->td_ring[lp->tx_next_करोne].control = DMA_DESC_IOF;
		lp->td_ring[lp->tx_next_करोne].devcs = ETH_TX_FD | ETH_TX_LD;
		lp->td_ring[lp->tx_next_करोne].link = 0;
		lp->td_ring[lp->tx_next_करोne].ca = 0;
		lp->tx_count--;

		/* Go on to next transmission */
		lp->tx_next_करोne = (lp->tx_next_करोne + 1) & KORINA_TDS_MASK;
		td = &lp->td_ring[lp->tx_next_करोne];

	पूर्ण

	/* Clear the DMA status रेजिस्टर */
	dmas = पढ़ोl(&lp->tx_dma_regs->dmas);
	ग_लिखोl(~dmas, &lp->tx_dma_regs->dmas);

	ग_लिखोl(पढ़ोl(&lp->tx_dma_regs->dmयंत्र) &
			~(DMA_STAT_FINI | DMA_STAT_ERR),
			&lp->tx_dma_regs->dmयंत्र);

	spin_unlock(&lp->lock);
पूर्ण

अटल irqवापस_t
korina_tx_dma_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = dev_id;
	काष्ठा korina_निजी *lp = netdev_priv(dev);
	u32 dmas, dmयंत्र;
	irqवापस_t retval;

	dmas = पढ़ोl(&lp->tx_dma_regs->dmas);

	अगर (dmas & (DMA_STAT_FINI | DMA_STAT_ERR)) अणु
		dmयंत्र = पढ़ोl(&lp->tx_dma_regs->dmयंत्र);
		ग_लिखोl(dmयंत्र | (DMA_STAT_FINI | DMA_STAT_ERR),
				&lp->tx_dma_regs->dmयंत्र);

		korina_tx(dev);

		अगर (lp->tx_chain_status == desc_filled &&
			(पढ़ोl(&(lp->tx_dma_regs->dmandptr)) == 0)) अणु
			ग_लिखोl(korina_tx_dma(lp, lp->tx_chain_head),
			       &lp->tx_dma_regs->dmandptr);
			lp->tx_chain_status = desc_is_empty;
			lp->tx_chain_head = lp->tx_chain_tail;
			netअगर_trans_update(dev);
		पूर्ण
		अगर (dmas & DMA_STAT_ERR)
			prपूर्णांकk(KERN_ERR "%s: DMA error\n", dev->name);

		retval = IRQ_HANDLED;
	पूर्ण अन्यथा
		retval = IRQ_NONE;

	वापस retval;
पूर्ण


अटल व्योम korina_check_media(काष्ठा net_device *dev, अचिन्हित पूर्णांक init_media)
अणु
	काष्ठा korina_निजी *lp = netdev_priv(dev);

	mii_check_media(&lp->mii_अगर, 1, init_media);

	अगर (lp->mii_अगर.full_duplex)
		ग_लिखोl(पढ़ोl(&lp->eth_regs->ethmac2) | ETH_MAC2_FD,
						&lp->eth_regs->ethmac2);
	अन्यथा
		ग_लिखोl(पढ़ोl(&lp->eth_regs->ethmac2) & ~ETH_MAC2_FD,
						&lp->eth_regs->ethmac2);
पूर्ण

अटल व्योम korina_poll_media(काष्ठा समयr_list *t)
अणु
	काष्ठा korina_निजी *lp = from_समयr(lp, t, media_check_समयr);
	काष्ठा net_device *dev = lp->dev;

	korina_check_media(dev, 0);
	mod_समयr(&lp->media_check_समयr, jअगरfies + HZ);
पूर्ण

अटल व्योम korina_set_carrier(काष्ठा mii_अगर_info *mii)
अणु
	अगर (mii->क्रमce_media) अणु
		/* स्वतःneg is off: Link is always assumed to be up */
		अगर (!netअगर_carrier_ok(mii->dev))
			netअगर_carrier_on(mii->dev);
	पूर्ण अन्यथा  /* Let MMI library update carrier status */
		korina_check_media(mii->dev, 0);
पूर्ण

अटल पूर्णांक korina_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *rq, पूर्णांक cmd)
अणु
	काष्ठा korina_निजी *lp = netdev_priv(dev);
	काष्ठा mii_ioctl_data *data = अगर_mii(rq);
	पूर्णांक rc;

	अगर (!netअगर_running(dev))
		वापस -EINVAL;
	spin_lock_irq(&lp->lock);
	rc = generic_mii_ioctl(&lp->mii_अगर, data, cmd, शून्य);
	spin_unlock_irq(&lp->lock);
	korina_set_carrier(&lp->mii_अगर);

	वापस rc;
पूर्ण

/* ethtool helpers */
अटल व्योम netdev_get_drvinfo(काष्ठा net_device *dev,
				काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा korina_निजी *lp = netdev_priv(dev);

	strlcpy(info->driver, DRV_NAME, माप(info->driver));
	strlcpy(info->version, DRV_VERSION, माप(info->version));
	strlcpy(info->bus_info, lp->dev->name, माप(info->bus_info));
पूर्ण

अटल पूर्णांक netdev_get_link_ksettings(काष्ठा net_device *dev,
				     काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा korina_निजी *lp = netdev_priv(dev);

	spin_lock_irq(&lp->lock);
	mii_ethtool_get_link_ksettings(&lp->mii_अगर, cmd);
	spin_unlock_irq(&lp->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक netdev_set_link_ksettings(काष्ठा net_device *dev,
				     स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा korina_निजी *lp = netdev_priv(dev);
	पूर्णांक rc;

	spin_lock_irq(&lp->lock);
	rc = mii_ethtool_set_link_ksettings(&lp->mii_अगर, cmd);
	spin_unlock_irq(&lp->lock);
	korina_set_carrier(&lp->mii_अगर);

	वापस rc;
पूर्ण

अटल u32 netdev_get_link(काष्ठा net_device *dev)
अणु
	काष्ठा korina_निजी *lp = netdev_priv(dev);

	वापस mii_link_ok(&lp->mii_अगर);
पूर्ण

अटल स्थिर काष्ठा ethtool_ops netdev_ethtool_ops = अणु
	.get_drvinfo		= netdev_get_drvinfo,
	.get_link		= netdev_get_link,
	.get_link_ksettings	= netdev_get_link_ksettings,
	.set_link_ksettings	= netdev_set_link_ksettings,
पूर्ण;

अटल पूर्णांक korina_alloc_ring(काष्ठा net_device *dev)
अणु
	काष्ठा korina_निजी *lp = netdev_priv(dev);
	काष्ठा sk_buff *skb;
	dma_addr_t ca;
	पूर्णांक i;

	/* Initialize the transmit descriptors */
	क्रम (i = 0; i < KORINA_NUM_TDS; i++) अणु
		lp->td_ring[i].control = DMA_DESC_IOF;
		lp->td_ring[i].devcs = ETH_TX_FD | ETH_TX_LD;
		lp->td_ring[i].ca = 0;
		lp->td_ring[i].link = 0;
	पूर्ण
	lp->tx_next_करोne = lp->tx_chain_head = lp->tx_chain_tail =
			lp->tx_full = lp->tx_count = 0;
	lp->tx_chain_status = desc_is_empty;

	/* Initialize the receive descriptors */
	क्रम (i = 0; i < KORINA_NUM_RDS; i++) अणु
		skb = netdev_alloc_skb_ip_align(dev, KORINA_RBSIZE);
		अगर (!skb)
			वापस -ENOMEM;
		lp->rx_skb[i] = skb;
		lp->rd_ring[i].control = DMA_DESC_IOD |
				DMA_COUNT(KORINA_RBSIZE);
		lp->rd_ring[i].devcs = 0;
		ca = dma_map_single(lp->dmadev, skb->data, KORINA_RBSIZE,
				    DMA_FROM_DEVICE);
		अगर (dma_mapping_error(lp->dmadev, ca))
			वापस -ENOMEM;
		lp->rd_ring[i].ca = ca;
		lp->rx_skb_dma[i] = ca;
		lp->rd_ring[i].link = korina_rx_dma(lp, i + 1);
	पूर्ण

	/* loop back receive descriptors, so the last
	 * descriptor poपूर्णांकs to the first one */
	lp->rd_ring[i - 1].link = lp->rd_dma;
	lp->rd_ring[i - 1].control |= DMA_DESC_COD;

	lp->rx_next_करोne  = 0;
	lp->rx_chain_head = 0;
	lp->rx_chain_tail = 0;
	lp->rx_chain_status = desc_is_empty;

	वापस 0;
पूर्ण

अटल व्योम korina_मुक्त_ring(काष्ठा net_device *dev)
अणु
	काष्ठा korina_निजी *lp = netdev_priv(dev);
	पूर्णांक i;

	क्रम (i = 0; i < KORINA_NUM_RDS; i++) अणु
		lp->rd_ring[i].control = 0;
		अगर (lp->rx_skb[i]) अणु
			dma_unmap_single(lp->dmadev, lp->rx_skb_dma[i],
					 KORINA_RBSIZE, DMA_FROM_DEVICE);
			dev_kमुक्त_skb_any(lp->rx_skb[i]);
			lp->rx_skb[i] = शून्य;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < KORINA_NUM_TDS; i++) अणु
		lp->td_ring[i].control = 0;
		अगर (lp->tx_skb[i]) अणु
			dma_unmap_single(lp->dmadev, lp->tx_skb_dma[i],
					 lp->tx_skb[i]->len, DMA_TO_DEVICE);
			dev_kमुक्त_skb_any(lp->tx_skb[i]);
			lp->tx_skb[i] = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Initialize the RC32434 ethernet controller.
 */
अटल पूर्णांक korina_init(काष्ठा net_device *dev)
अणु
	काष्ठा korina_निजी *lp = netdev_priv(dev);

	/* Disable DMA */
	korina_पात_tx(dev);
	korina_पात_rx(dev);

	/* reset ethernet logic */
	ग_लिखोl(0, &lp->eth_regs->ethपूर्णांकfc);
	जबतक ((पढ़ोl(&lp->eth_regs->ethपूर्णांकfc) & ETH_INT_FC_RIP))
		netअगर_trans_update(dev);

	/* Enable Ethernet Interface */
	ग_लिखोl(ETH_INT_FC_EN, &lp->eth_regs->ethपूर्णांकfc);

	/* Allocate rings */
	अगर (korina_alloc_ring(dev)) अणु
		prपूर्णांकk(KERN_ERR "%s: descriptor allocation failed\n", dev->name);
		korina_मुक्त_ring(dev);
		वापस -ENOMEM;
	पूर्ण

	ग_लिखोl(0, &lp->rx_dma_regs->dmas);
	/* Start Rx DMA */
	ग_लिखोl(0, &lp->rx_dma_regs->dmandptr);
	ग_लिखोl(korina_rx_dma(lp, 0), &lp->rx_dma_regs->dmadptr);

	ग_लिखोl(पढ़ोl(&lp->tx_dma_regs->dmयंत्र) &
			~(DMA_STAT_FINI | DMA_STAT_ERR),
			&lp->tx_dma_regs->dmयंत्र);
	ग_लिखोl(पढ़ोl(&lp->rx_dma_regs->dmयंत्र) &
			~(DMA_STAT_DONE | DMA_STAT_HALT | DMA_STAT_ERR),
			&lp->rx_dma_regs->dmयंत्र);

	/* Accept only packets destined क्रम this Ethernet device address */
	ग_लिखोl(ETH_ARC_AB, &lp->eth_regs->etharc);

	/* Set all Ether station address रेजिस्टरs to their initial values */
	ग_लिखोl(STATION_ADDRESS_LOW(dev), &lp->eth_regs->ethsal0);
	ग_लिखोl(STATION_ADDRESS_HIGH(dev), &lp->eth_regs->ethsah0);

	ग_लिखोl(STATION_ADDRESS_LOW(dev), &lp->eth_regs->ethsal1);
	ग_लिखोl(STATION_ADDRESS_HIGH(dev), &lp->eth_regs->ethsah1);

	ग_लिखोl(STATION_ADDRESS_LOW(dev), &lp->eth_regs->ethsal2);
	ग_लिखोl(STATION_ADDRESS_HIGH(dev), &lp->eth_regs->ethsah2);

	ग_लिखोl(STATION_ADDRESS_LOW(dev), &lp->eth_regs->ethsal3);
	ग_लिखोl(STATION_ADDRESS_HIGH(dev), &lp->eth_regs->ethsah3);


	/* Frame Length Checking, Pad Enable, CRC Enable, Full Duplex set */
	ग_लिखोl(ETH_MAC2_PE | ETH_MAC2_CEN | ETH_MAC2_FD,
			&lp->eth_regs->ethmac2);

	/* Back to back पूर्णांकer-packet-gap */
	ग_लिखोl(0x15, &lp->eth_regs->ethipgt);
	/* Non - Back to back पूर्णांकer-packet-gap */
	ग_लिखोl(0x12, &lp->eth_regs->ethipgr);

	/* Management Clock Prescaler Divisor
	 * Clock independent setting */
	ग_लिखोl(((lp->mii_घड़ी_freq) / MII_CLOCK + 1) & ~1,
	       &lp->eth_regs->ethmcp);
	ग_लिखोl(0, &lp->eth_regs->miimcfg);

	/* करोn't transmit until fअगरo contains 48b */
	ग_लिखोl(48, &lp->eth_regs->ethfअगरott);

	ग_लिखोl(ETH_MAC1_RE, &lp->eth_regs->ethmac1);

	korina_check_media(dev, 1);

	napi_enable(&lp->napi);
	netअगर_start_queue(dev);

	वापस 0;
पूर्ण

/*
 * Restart the RC32434 ethernet controller.
 */
अटल व्योम korina_restart_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा korina_निजी *lp = container_of(work,
			काष्ठा korina_निजी, restart_task);
	काष्ठा net_device *dev = lp->dev;

	/*
	 * Disable पूर्णांकerrupts
	 */
	disable_irq(lp->rx_irq);
	disable_irq(lp->tx_irq);

	ग_लिखोl(पढ़ोl(&lp->tx_dma_regs->dmयंत्र) |
				DMA_STAT_FINI | DMA_STAT_ERR,
				&lp->tx_dma_regs->dmयंत्र);
	ग_लिखोl(पढ़ोl(&lp->rx_dma_regs->dmयंत्र) |
				DMA_STAT_DONE | DMA_STAT_HALT | DMA_STAT_ERR,
				&lp->rx_dma_regs->dmयंत्र);

	napi_disable(&lp->napi);

	korina_मुक्त_ring(dev);

	अगर (korina_init(dev) < 0) अणु
		prपूर्णांकk(KERN_ERR "%s: cannot restart device\n", dev->name);
		वापस;
	पूर्ण
	korina_multicast_list(dev);

	enable_irq(lp->tx_irq);
	enable_irq(lp->rx_irq);
पूर्ण

अटल व्योम korina_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा korina_निजी *lp = netdev_priv(dev);

	schedule_work(&lp->restart_task);
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
अटल व्योम korina_poll_controller(काष्ठा net_device *dev)
अणु
	disable_irq(dev->irq);
	korina_tx_dma_पूर्णांकerrupt(dev->irq, dev);
	enable_irq(dev->irq);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक korina_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा korina_निजी *lp = netdev_priv(dev);
	पूर्णांक ret;

	/* Initialize */
	ret = korina_init(dev);
	अगर (ret < 0) अणु
		prपूर्णांकk(KERN_ERR "%s: cannot open device\n", dev->name);
		जाओ out;
	पूर्ण

	/* Install the पूर्णांकerrupt handler
	 * that handles the Done Finished */
	ret = request_irq(lp->rx_irq, korina_rx_dma_पूर्णांकerrupt,
			0, "Korina ethernet Rx", dev);
	अगर (ret < 0) अणु
		prपूर्णांकk(KERN_ERR "%s: unable to get Rx DMA IRQ %d\n",
			dev->name, lp->rx_irq);
		जाओ err_release;
	पूर्ण
	ret = request_irq(lp->tx_irq, korina_tx_dma_पूर्णांकerrupt,
			0, "Korina ethernet Tx", dev);
	अगर (ret < 0) अणु
		prपूर्णांकk(KERN_ERR "%s: unable to get Tx DMA IRQ %d\n",
			dev->name, lp->tx_irq);
		जाओ err_मुक्त_rx_irq;
	पूर्ण

	mod_समयr(&lp->media_check_समयr, jअगरfies + 1);
out:
	वापस ret;

err_मुक्त_rx_irq:
	मुक्त_irq(lp->rx_irq, dev);
err_release:
	korina_मुक्त_ring(dev);
	जाओ out;
पूर्ण

अटल पूर्णांक korina_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा korina_निजी *lp = netdev_priv(dev);
	u32 पंचांगp;

	del_समयr(&lp->media_check_समयr);

	/* Disable पूर्णांकerrupts */
	disable_irq(lp->rx_irq);
	disable_irq(lp->tx_irq);

	korina_पात_tx(dev);
	पंचांगp = पढ़ोl(&lp->tx_dma_regs->dmयंत्र);
	पंचांगp = पंचांगp | DMA_STAT_FINI | DMA_STAT_ERR;
	ग_लिखोl(पंचांगp, &lp->tx_dma_regs->dmयंत्र);

	korina_पात_rx(dev);
	पंचांगp = पढ़ोl(&lp->rx_dma_regs->dmयंत्र);
	पंचांगp = पंचांगp | DMA_STAT_DONE | DMA_STAT_HALT | DMA_STAT_ERR;
	ग_लिखोl(पंचांगp, &lp->rx_dma_regs->dmयंत्र);

	napi_disable(&lp->napi);

	cancel_work_sync(&lp->restart_task);

	korina_मुक्त_ring(dev);

	मुक्त_irq(lp->rx_irq, dev);
	मुक्त_irq(lp->tx_irq, dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा net_device_ops korina_netdev_ops = अणु
	.nकरो_खोलो		= korina_खोलो,
	.nकरो_stop		= korina_बंद,
	.nकरो_start_xmit		= korina_send_packet,
	.nकरो_set_rx_mode	= korina_multicast_list,
	.nकरो_tx_समयout		= korina_tx_समयout,
	.nकरो_करो_ioctl		= korina_ioctl,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_set_mac_address	= eth_mac_addr,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller	= korina_poll_controller,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक korina_probe(काष्ठा platक्रमm_device *pdev)
अणु
	u8 *mac_addr = dev_get_platdata(&pdev->dev);
	काष्ठा korina_निजी *lp;
	काष्ठा net_device *dev;
	काष्ठा clk *clk;
	व्योम __iomem *p;
	पूर्णांक rc;

	dev = devm_alloc_etherdev(&pdev->dev, माप(काष्ठा korina_निजी));
	अगर (!dev)
		वापस -ENOMEM;

	SET_NETDEV_DEV(dev, &pdev->dev);
	lp = netdev_priv(dev);

	अगर (mac_addr)
		ether_addr_copy(dev->dev_addr, mac_addr);
	अन्यथा अगर (of_get_mac_address(pdev->dev.of_node, dev->dev_addr) < 0)
		eth_hw_addr_अक्रमom(dev);

	clk = devm_clk_get_optional(&pdev->dev, "mdioclk");
	अगर (IS_ERR(clk))
		वापस PTR_ERR(clk);
	अगर (clk) अणु
		clk_prepare_enable(clk);
		lp->mii_घड़ी_freq = clk_get_rate(clk);
	पूर्ण अन्यथा अणु
		lp->mii_घड़ी_freq = 200000000; /* max possible input clk */
	पूर्ण

	lp->rx_irq = platक्रमm_get_irq_byname(pdev, "rx");
	lp->tx_irq = platक्रमm_get_irq_byname(pdev, "tx");

	p = devm_platक्रमm_ioremap_resource_byname(pdev, "emac");
	अगर (IS_ERR(p)) अणु
		prपूर्णांकk(KERN_ERR DRV_NAME ": cannot remap registers\n");
		वापस PTR_ERR(p);
	पूर्ण
	lp->eth_regs = p;

	p = devm_platक्रमm_ioremap_resource_byname(pdev, "dma_rx");
	अगर (IS_ERR(p)) अणु
		prपूर्णांकk(KERN_ERR DRV_NAME ": cannot remap Rx DMA registers\n");
		वापस PTR_ERR(p);
	पूर्ण
	lp->rx_dma_regs = p;

	p = devm_platक्रमm_ioremap_resource_byname(pdev, "dma_tx");
	अगर (IS_ERR(p)) अणु
		prपूर्णांकk(KERN_ERR DRV_NAME ": cannot remap Tx DMA registers\n");
		वापस PTR_ERR(p);
	पूर्ण
	lp->tx_dma_regs = p;

	lp->td_ring = dmam_alloc_coherent(&pdev->dev, TD_RING_SIZE,
					  &lp->td_dma, GFP_KERNEL);
	अगर (!lp->td_ring)
		वापस -ENOMEM;

	lp->rd_ring = dmam_alloc_coherent(&pdev->dev, RD_RING_SIZE,
					  &lp->rd_dma, GFP_KERNEL);
	अगर (!lp->rd_ring)
		वापस -ENOMEM;

	spin_lock_init(&lp->lock);
	/* just use the rx dma irq */
	dev->irq = lp->rx_irq;
	lp->dev = dev;
	lp->dmadev = &pdev->dev;

	dev->netdev_ops = &korina_netdev_ops;
	dev->ethtool_ops = &netdev_ethtool_ops;
	dev->watchकरोg_समयo = TX_TIMEOUT;
	netअगर_napi_add(dev, &lp->napi, korina_poll, NAPI_POLL_WEIGHT);

	lp->mii_अगर.dev = dev;
	lp->mii_अगर.mdio_पढ़ो = korina_mdio_पढ़ो;
	lp->mii_अगर.mdio_ग_लिखो = korina_mdio_ग_लिखो;
	lp->mii_अगर.phy_id = 1;
	lp->mii_अगर.phy_id_mask = 0x1f;
	lp->mii_अगर.reg_num_mask = 0x1f;

	platक्रमm_set_drvdata(pdev, dev);

	rc = रेजिस्टर_netdev(dev);
	अगर (rc < 0) अणु
		prपूर्णांकk(KERN_ERR DRV_NAME
			": cannot register net device: %d\n", rc);
		वापस rc;
	पूर्ण
	समयr_setup(&lp->media_check_समयr, korina_poll_media, 0);

	INIT_WORK(&lp->restart_task, korina_restart_task);

	prपूर्णांकk(KERN_INFO "%s: " DRV_NAME "-" DRV_VERSION " " DRV_RELDATE "\n",
			dev->name);
	वापस rc;
पूर्ण

अटल पूर्णांक korina_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *dev = platक्रमm_get_drvdata(pdev);

	unरेजिस्टर_netdev(dev);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id korina_match[] = अणु
	अणु
		.compatible = "idt,3243x-emac",
	पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, korina_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver korina_driver = अणु
	.driver = अणु
		.name = "korina",
		.of_match_table = of_match_ptr(korina_match),
	पूर्ण,
	.probe = korina_probe,
	.हटाओ = korina_हटाओ,
पूर्ण;

module_platक्रमm_driver(korina_driver);

MODULE_AUTHOR("Philip Rischel <rischelp@idt.com>");
MODULE_AUTHOR("Felix Fietkau <nbd@openwrt.org>");
MODULE_AUTHOR("Florian Fainelli <florian@openwrt.org>");
MODULE_AUTHOR("Roman Yeryomin <roman@advem.lv>");
MODULE_DESCRIPTION("IDT RC32434 (Korina) Ethernet driver");
MODULE_LICENSE("GPL");
