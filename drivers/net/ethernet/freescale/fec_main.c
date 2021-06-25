<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Fast Ethernet Controller (FEC) driver क्रम Motorola MPC8xx.
 * Copyright (c) 1997 Dan Malek (dmalek@jlc.net)
 *
 * Right now, I am very wasteful with the buffers.  I allocate memory
 * pages and then भागide them पूर्णांकo 2K frame buffers.  This way I know I
 * have buffers large enough to hold one frame within one buffer descriptor.
 * Once I get this working, I will use 64 or 128 byte CPM buffers, which
 * will be much more memory efficient and will easily handle lots of
 * small packets.
 *
 * Much better multiple PHY support by Magnus Damm.
 * Copyright (c) 2000 Ericsson Radio Systems AB.
 *
 * Support क्रम FEC controller of ColdFire processors.
 * Copyright (c) 2001-2005 Greg Ungerer (gerg@snapgear.com)
 *
 * Bug fixes and cleanup by Philippe De Muyter (phdm@macqel.be)
 * Copyright (c) 2004-2006 Macq Electronique SA.
 *
 * Copyright (C) 2010-2011 Freescale Semiconductor, Inc.
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/ptrace.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ioport.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/in.h>
#समावेश <linux/ip.h>
#समावेश <net/ip.h>
#समावेश <net/selftests.h>
#समावेश <net/tso.h>
#समावेश <linux/tcp.h>
#समावेश <linux/udp.h>
#समावेश <linux/icmp.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/bitops.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/clk.h>
#समावेश <linux/crc32.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mdपन.स>
#समावेश <linux/phy.h>
#समावेश <linux/fec.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/of_net.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/prefetch.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/regmap.h>
#समावेश <soc/imx/cpuidle.h>

#समावेश <यंत्र/cacheflush.h>

#समावेश "fec.h"

अटल व्योम set_multicast_list(काष्ठा net_device *ndev);
अटल व्योम fec_enet_itr_coal_init(काष्ठा net_device *ndev);

#घोषणा DRIVER_NAME	"fec"

/* Pause frame feild and FIFO threshold */
#घोषणा FEC_ENET_FCE	(1 << 5)
#घोषणा FEC_ENET_RSEM_V	0x84
#घोषणा FEC_ENET_RSFL_V	16
#घोषणा FEC_ENET_RAEM_V	0x8
#घोषणा FEC_ENET_RAFL_V	0x8
#घोषणा FEC_ENET_OPD_V	0xFFF0
#घोषणा FEC_MDIO_PM_TIMEOUT  100 /* ms */

काष्ठा fec_devinfo अणु
	u32 quirks;
पूर्ण;

अटल स्थिर काष्ठा fec_devinfo fec_imx25_info = अणु
	.quirks = FEC_QUIRK_USE_GASKET | FEC_QUIRK_MIB_CLEAR |
		  FEC_QUIRK_HAS_FRREG,
पूर्ण;

अटल स्थिर काष्ठा fec_devinfo fec_imx27_info = अणु
	.quirks = FEC_QUIRK_MIB_CLEAR | FEC_QUIRK_HAS_FRREG,
पूर्ण;

अटल स्थिर काष्ठा fec_devinfo fec_imx28_info = अणु
	.quirks = FEC_QUIRK_ENET_MAC | FEC_QUIRK_SWAP_FRAME |
		  FEC_QUIRK_SINGLE_MDIO | FEC_QUIRK_HAS_RACC |
		  FEC_QUIRK_HAS_FRREG | FEC_QUIRK_CLEAR_SETUP_MII |
		  FEC_QUIRK_NO_HARD_RESET,
पूर्ण;

अटल स्थिर काष्ठा fec_devinfo fec_imx6q_info = अणु
	.quirks = FEC_QUIRK_ENET_MAC | FEC_QUIRK_HAS_GBIT |
		  FEC_QUIRK_HAS_BUFDESC_EX | FEC_QUIRK_HAS_CSUM |
		  FEC_QUIRK_HAS_VLAN | FEC_QUIRK_ERR006358 |
		  FEC_QUIRK_HAS_RACC | FEC_QUIRK_CLEAR_SETUP_MII,
पूर्ण;

अटल स्थिर काष्ठा fec_devinfo fec_mvf600_info = अणु
	.quirks = FEC_QUIRK_ENET_MAC | FEC_QUIRK_HAS_RACC,
पूर्ण;

अटल स्थिर काष्ठा fec_devinfo fec_imx6x_info = अणु
	.quirks = FEC_QUIRK_ENET_MAC | FEC_QUIRK_HAS_GBIT |
		  FEC_QUIRK_HAS_BUFDESC_EX | FEC_QUIRK_HAS_CSUM |
		  FEC_QUIRK_HAS_VLAN | FEC_QUIRK_HAS_AVB |
		  FEC_QUIRK_ERR007885 | FEC_QUIRK_BUG_CAPTURE |
		  FEC_QUIRK_HAS_RACC | FEC_QUIRK_HAS_COALESCE |
		  FEC_QUIRK_CLEAR_SETUP_MII,
पूर्ण;

अटल स्थिर काष्ठा fec_devinfo fec_imx6ul_info = अणु
	.quirks = FEC_QUIRK_ENET_MAC | FEC_QUIRK_HAS_GBIT |
		  FEC_QUIRK_HAS_BUFDESC_EX | FEC_QUIRK_HAS_CSUM |
		  FEC_QUIRK_HAS_VLAN | FEC_QUIRK_ERR007885 |
		  FEC_QUIRK_BUG_CAPTURE | FEC_QUIRK_HAS_RACC |
		  FEC_QUIRK_HAS_COALESCE | FEC_QUIRK_CLEAR_SETUP_MII,
पूर्ण;

अटल काष्ठा platक्रमm_device_id fec_devtype[] = अणु
	अणु
		/* keep it क्रम coldfire */
		.name = DRIVER_NAME,
		.driver_data = 0,
	पूर्ण, अणु
		.name = "imx25-fec",
		.driver_data = (kernel_uदीर्घ_t)&fec_imx25_info,
	पूर्ण, अणु
		.name = "imx27-fec",
		.driver_data = (kernel_uदीर्घ_t)&fec_imx27_info,
	पूर्ण, अणु
		.name = "imx28-fec",
		.driver_data = (kernel_uदीर्घ_t)&fec_imx28_info,
	पूर्ण, अणु
		.name = "imx6q-fec",
		.driver_data = (kernel_uदीर्घ_t)&fec_imx6q_info,
	पूर्ण, अणु
		.name = "mvf600-fec",
		.driver_data = (kernel_uदीर्घ_t)&fec_mvf600_info,
	पूर्ण, अणु
		.name = "imx6sx-fec",
		.driver_data = (kernel_uदीर्घ_t)&fec_imx6x_info,
	पूर्ण, अणु
		.name = "imx6ul-fec",
		.driver_data = (kernel_uदीर्घ_t)&fec_imx6ul_info,
	पूर्ण, अणु
		/* sentinel */
	पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, fec_devtype);

क्रमागत imx_fec_type अणु
	IMX25_FEC = 1,	/* runs on i.mx25/50/53 */
	IMX27_FEC,	/* runs on i.mx27/35/51 */
	IMX28_FEC,
	IMX6Q_FEC,
	MVF600_FEC,
	IMX6SX_FEC,
	IMX6UL_FEC,
पूर्ण;

अटल स्थिर काष्ठा of_device_id fec_dt_ids[] = अणु
	अणु .compatible = "fsl,imx25-fec", .data = &fec_devtype[IMX25_FEC], पूर्ण,
	अणु .compatible = "fsl,imx27-fec", .data = &fec_devtype[IMX27_FEC], पूर्ण,
	अणु .compatible = "fsl,imx28-fec", .data = &fec_devtype[IMX28_FEC], पूर्ण,
	अणु .compatible = "fsl,imx6q-fec", .data = &fec_devtype[IMX6Q_FEC], पूर्ण,
	अणु .compatible = "fsl,mvf600-fec", .data = &fec_devtype[MVF600_FEC], पूर्ण,
	अणु .compatible = "fsl,imx6sx-fec", .data = &fec_devtype[IMX6SX_FEC], पूर्ण,
	अणु .compatible = "fsl,imx6ul-fec", .data = &fec_devtype[IMX6UL_FEC], पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, fec_dt_ids);

अटल अचिन्हित अक्षर macaddr[ETH_ALEN];
module_param_array(macaddr, byte, शून्य, 0);
MODULE_PARM_DESC(macaddr, "FEC Ethernet MAC address");

#अगर defined(CONFIG_M5272)
/*
 * Some hardware माला_लो it MAC address out of local flash memory.
 * अगर this is non-zero then assume it is the address to get MAC from.
 */
#अगर defined(CONFIG_NETtel)
#घोषणा	FEC_FLASHMAC	0xf0006006
#या_अगर defined(CONFIG_GILBARCONAP) || defined(CONFIG_SCALES)
#घोषणा	FEC_FLASHMAC	0xf0006000
#या_अगर defined(CONFIG_CANCam)
#घोषणा	FEC_FLASHMAC	0xf0020000
#या_अगर defined (CONFIG_M5272C3)
#घोषणा	FEC_FLASHMAC	(0xffe04000 + 4)
#या_अगर defined(CONFIG_MOD5272)
#घोषणा FEC_FLASHMAC	0xffc0406b
#अन्यथा
#घोषणा	FEC_FLASHMAC	0
#पूर्ण_अगर
#पूर्ण_अगर /* CONFIG_M5272 */

/* The FEC stores dest/src/type/vlan, data, and checksum क्रम receive packets.
 *
 * 2048 byte skbufs are allocated. However, alignment requirements
 * varies between FEC variants. Worst हाल is 64, so round करोwn by 64.
 */
#घोषणा PKT_MAXBUF_SIZE		(round_करोwn(2048 - 64, 64))
#घोषणा PKT_MINBUF_SIZE		64

/* FEC receive acceleration */
#घोषणा FEC_RACC_IPDIS		(1 << 1)
#घोषणा FEC_RACC_PRODIS		(1 << 2)
#घोषणा FEC_RACC_SHIFT16	BIT(7)
#घोषणा FEC_RACC_OPTIONS	(FEC_RACC_IPDIS | FEC_RACC_PRODIS)

/* MIB Control Register */
#घोषणा FEC_MIB_CTRLSTAT_DISABLE	BIT(31)

/*
 * The 5270/5271/5280/5282/532x RX control रेजिस्टर also contains maximum frame
 * size bits. Other FEC hardware करोes not, so we need to take that पूर्णांकo
 * account when setting it.
 */
#अगर defined(CONFIG_M523x) || defined(CONFIG_M527x) || defined(CONFIG_M528x) || \
    defined(CONFIG_M520x) || defined(CONFIG_M532x) || defined(CONFIG_ARM) || \
    defined(CONFIG_ARM64)
#घोषणा	OPT_FRAME_SIZE	(PKT_MAXBUF_SIZE << 16)
#अन्यथा
#घोषणा	OPT_FRAME_SIZE	0
#पूर्ण_अगर

/* FEC MII MMFR bits definition */
#घोषणा FEC_MMFR_ST		(1 << 30)
#घोषणा FEC_MMFR_ST_C45		(0)
#घोषणा FEC_MMFR_OP_READ	(2 << 28)
#घोषणा FEC_MMFR_OP_READ_C45	(3 << 28)
#घोषणा FEC_MMFR_OP_WRITE	(1 << 28)
#घोषणा FEC_MMFR_OP_ADDR_WRITE	(0)
#घोषणा FEC_MMFR_PA(v)		((v & 0x1f) << 23)
#घोषणा FEC_MMFR_RA(v)		((v & 0x1f) << 18)
#घोषणा FEC_MMFR_TA		(2 << 16)
#घोषणा FEC_MMFR_DATA(v)	(v & 0xffff)
/* FEC ECR bits definition */
#घोषणा FEC_ECR_MAGICEN		(1 << 2)
#घोषणा FEC_ECR_SLEEP		(1 << 3)

#घोषणा FEC_MII_TIMEOUT		30000 /* us */

/* Transmitter समयout */
#घोषणा TX_TIMEOUT (2 * HZ)

#घोषणा FEC_PAUSE_FLAG_AUTONEG	0x1
#घोषणा FEC_PAUSE_FLAG_ENABLE	0x2
#घोषणा FEC_WOL_HAS_MAGIC_PACKET	(0x1 << 0)
#घोषणा FEC_WOL_FLAG_ENABLE		(0x1 << 1)
#घोषणा FEC_WOL_FLAG_SLEEP_ON		(0x1 << 2)

#घोषणा COPYBREAK_DEFAULT	256

/* Max number of allowed TCP segments क्रम software TSO */
#घोषणा FEC_MAX_TSO_SEGS	100
#घोषणा FEC_MAX_SKB_DESCS	(FEC_MAX_TSO_SEGS * 2 + MAX_SKB_FRAGS)

#घोषणा IS_TSO_HEADER(txq, addr) \
	((addr >= txq->tso_hdrs_dma) && \
	(addr < txq->tso_hdrs_dma + txq->bd.ring_size * TSO_HEADER_SIZE))

अटल पूर्णांक mii_cnt;

अटल काष्ठा bufdesc *fec_enet_get_nextdesc(काष्ठा bufdesc *bdp,
					     काष्ठा bufdesc_prop *bd)
अणु
	वापस (bdp >= bd->last) ? bd->base
			: (काष्ठा bufdesc *)(((व्योम *)bdp) + bd->dsize);
पूर्ण

अटल काष्ठा bufdesc *fec_enet_get_prevdesc(काष्ठा bufdesc *bdp,
					     काष्ठा bufdesc_prop *bd)
अणु
	वापस (bdp <= bd->base) ? bd->last
			: (काष्ठा bufdesc *)(((व्योम *)bdp) - bd->dsize);
पूर्ण

अटल पूर्णांक fec_enet_get_bd_index(काष्ठा bufdesc *bdp,
				 काष्ठा bufdesc_prop *bd)
अणु
	वापस ((स्थिर अक्षर *)bdp - (स्थिर अक्षर *)bd->base) >> bd->dsize_log2;
पूर्ण

अटल पूर्णांक fec_enet_get_मुक्त_txdesc_num(काष्ठा fec_enet_priv_tx_q *txq)
अणु
	पूर्णांक entries;

	entries = (((स्थिर अक्षर *)txq->dirty_tx -
			(स्थिर अक्षर *)txq->bd.cur) >> txq->bd.dsize_log2) - 1;

	वापस entries >= 0 ? entries : entries + txq->bd.ring_size;
पूर्ण

अटल व्योम swap_buffer(व्योम *bufaddr, पूर्णांक len)
अणु
	पूर्णांक i;
	अचिन्हित पूर्णांक *buf = bufaddr;

	क्रम (i = 0; i < len; i += 4, buf++)
		swab32s(buf);
पूर्ण

अटल व्योम swap_buffer2(व्योम *dst_buf, व्योम *src_buf, पूर्णांक len)
अणु
	पूर्णांक i;
	अचिन्हित पूर्णांक *src = src_buf;
	अचिन्हित पूर्णांक *dst = dst_buf;

	क्रम (i = 0; i < len; i += 4, src++, dst++)
		*dst = swab32p(src);
पूर्ण

अटल व्योम fec_dump(काष्ठा net_device *ndev)
अणु
	काष्ठा fec_enet_निजी *fep = netdev_priv(ndev);
	काष्ठा bufdesc *bdp;
	काष्ठा fec_enet_priv_tx_q *txq;
	पूर्णांक index = 0;

	netdev_info(ndev, "TX ring dump\n");
	pr_info("Nr     SC     addr       len  SKB\n");

	txq = fep->tx_queue[0];
	bdp = txq->bd.base;

	करो अणु
		pr_info("%3u %c%c 0x%04x 0x%08x %4u %p\n",
			index,
			bdp == txq->bd.cur ? 'S' : ' ',
			bdp == txq->dirty_tx ? 'H' : ' ',
			fec16_to_cpu(bdp->cbd_sc),
			fec32_to_cpu(bdp->cbd_bufaddr),
			fec16_to_cpu(bdp->cbd_datlen),
			txq->tx_skbuff[index]);
		bdp = fec_enet_get_nextdesc(bdp, &txq->bd);
		index++;
	पूर्ण जबतक (bdp != txq->bd.base);
पूर्ण

अटल अंतरभूत bool is_ipv4_pkt(काष्ठा sk_buff *skb)
अणु
	वापस skb->protocol == htons(ETH_P_IP) && ip_hdr(skb)->version == 4;
पूर्ण

अटल पूर्णांक
fec_enet_clear_csum(काष्ठा sk_buff *skb, काष्ठा net_device *ndev)
अणु
	/* Only run क्रम packets requiring a checksum. */
	अगर (skb->ip_summed != CHECKSUM_PARTIAL)
		वापस 0;

	अगर (unlikely(skb_cow_head(skb, 0)))
		वापस -1;

	अगर (is_ipv4_pkt(skb))
		ip_hdr(skb)->check = 0;
	*(__sum16 *)(skb->head + skb->csum_start + skb->csum_offset) = 0;

	वापस 0;
पूर्ण

अटल काष्ठा bufdesc *
fec_enet_txq_submit_frag_skb(काष्ठा fec_enet_priv_tx_q *txq,
			     काष्ठा sk_buff *skb,
			     काष्ठा net_device *ndev)
अणु
	काष्ठा fec_enet_निजी *fep = netdev_priv(ndev);
	काष्ठा bufdesc *bdp = txq->bd.cur;
	काष्ठा bufdesc_ex *ebdp;
	पूर्णांक nr_frags = skb_shinfo(skb)->nr_frags;
	पूर्णांक frag, frag_len;
	अचिन्हित लघु status;
	अचिन्हित पूर्णांक estatus = 0;
	skb_frag_t *this_frag;
	अचिन्हित पूर्णांक index;
	व्योम *bufaddr;
	dma_addr_t addr;
	पूर्णांक i;

	क्रम (frag = 0; frag < nr_frags; frag++) अणु
		this_frag = &skb_shinfo(skb)->frags[frag];
		bdp = fec_enet_get_nextdesc(bdp, &txq->bd);
		ebdp = (काष्ठा bufdesc_ex *)bdp;

		status = fec16_to_cpu(bdp->cbd_sc);
		status &= ~BD_ENET_TX_STATS;
		status |= (BD_ENET_TX_TC | BD_ENET_TX_READY);
		frag_len = skb_frag_size(&skb_shinfo(skb)->frags[frag]);

		/* Handle the last BD specially */
		अगर (frag == nr_frags - 1) अणु
			status |= (BD_ENET_TX_INTR | BD_ENET_TX_LAST);
			अगर (fep->bufdesc_ex) अणु
				estatus |= BD_ENET_TX_INT;
				अगर (unlikely(skb_shinfo(skb)->tx_flags &
					SKBTX_HW_TSTAMP && fep->hwts_tx_en))
					estatus |= BD_ENET_TX_TS;
			पूर्ण
		पूर्ण

		अगर (fep->bufdesc_ex) अणु
			अगर (fep->quirks & FEC_QUIRK_HAS_AVB)
				estatus |= FEC_TX_BD_FTYPE(txq->bd.qid);
			अगर (skb->ip_summed == CHECKSUM_PARTIAL)
				estatus |= BD_ENET_TX_PINS | BD_ENET_TX_IINS;
			ebdp->cbd_bdu = 0;
			ebdp->cbd_esc = cpu_to_fec32(estatus);
		पूर्ण

		bufaddr = skb_frag_address(this_frag);

		index = fec_enet_get_bd_index(bdp, &txq->bd);
		अगर (((अचिन्हित दीर्घ) bufaddr) & fep->tx_align ||
			fep->quirks & FEC_QUIRK_SWAP_FRAME) अणु
			स_नकल(txq->tx_bounce[index], bufaddr, frag_len);
			bufaddr = txq->tx_bounce[index];

			अगर (fep->quirks & FEC_QUIRK_SWAP_FRAME)
				swap_buffer(bufaddr, frag_len);
		पूर्ण

		addr = dma_map_single(&fep->pdev->dev, bufaddr, frag_len,
				      DMA_TO_DEVICE);
		अगर (dma_mapping_error(&fep->pdev->dev, addr)) अणु
			अगर (net_ratelimit())
				netdev_err(ndev, "Tx DMA memory map failed\n");
			जाओ dma_mapping_error;
		पूर्ण

		bdp->cbd_bufaddr = cpu_to_fec32(addr);
		bdp->cbd_datlen = cpu_to_fec16(frag_len);
		/* Make sure the updates to rest of the descriptor are
		 * perक्रमmed beक्रमe transferring ownership.
		 */
		wmb();
		bdp->cbd_sc = cpu_to_fec16(status);
	पूर्ण

	वापस bdp;
dma_mapping_error:
	bdp = txq->bd.cur;
	क्रम (i = 0; i < frag; i++) अणु
		bdp = fec_enet_get_nextdesc(bdp, &txq->bd);
		dma_unmap_single(&fep->pdev->dev, fec32_to_cpu(bdp->cbd_bufaddr),
				 fec16_to_cpu(bdp->cbd_datlen), DMA_TO_DEVICE);
	पूर्ण
	वापस ERR_PTR(-ENOMEM);
पूर्ण

अटल पूर्णांक fec_enet_txq_submit_skb(काष्ठा fec_enet_priv_tx_q *txq,
				   काष्ठा sk_buff *skb, काष्ठा net_device *ndev)
अणु
	काष्ठा fec_enet_निजी *fep = netdev_priv(ndev);
	पूर्णांक nr_frags = skb_shinfo(skb)->nr_frags;
	काष्ठा bufdesc *bdp, *last_bdp;
	व्योम *bufaddr;
	dma_addr_t addr;
	अचिन्हित लघु status;
	अचिन्हित लघु buflen;
	अचिन्हित पूर्णांक estatus = 0;
	अचिन्हित पूर्णांक index;
	पूर्णांक entries_मुक्त;

	entries_मुक्त = fec_enet_get_मुक्त_txdesc_num(txq);
	अगर (entries_मुक्त < MAX_SKB_FRAGS + 1) अणु
		dev_kमुक्त_skb_any(skb);
		अगर (net_ratelimit())
			netdev_err(ndev, "NOT enough BD for SG!\n");
		वापस NETDEV_TX_OK;
	पूर्ण

	/* Protocol checksum off-load क्रम TCP and UDP. */
	अगर (fec_enet_clear_csum(skb, ndev)) अणु
		dev_kमुक्त_skb_any(skb);
		वापस NETDEV_TX_OK;
	पूर्ण

	/* Fill in a Tx ring entry */
	bdp = txq->bd.cur;
	last_bdp = bdp;
	status = fec16_to_cpu(bdp->cbd_sc);
	status &= ~BD_ENET_TX_STATS;

	/* Set buffer length and buffer poपूर्णांकer */
	bufaddr = skb->data;
	buflen = skb_headlen(skb);

	index = fec_enet_get_bd_index(bdp, &txq->bd);
	अगर (((अचिन्हित दीर्घ) bufaddr) & fep->tx_align ||
		fep->quirks & FEC_QUIRK_SWAP_FRAME) अणु
		स_नकल(txq->tx_bounce[index], skb->data, buflen);
		bufaddr = txq->tx_bounce[index];

		अगर (fep->quirks & FEC_QUIRK_SWAP_FRAME)
			swap_buffer(bufaddr, buflen);
	पूर्ण

	/* Push the data cache so the CPM करोes not get stale memory data. */
	addr = dma_map_single(&fep->pdev->dev, bufaddr, buflen, DMA_TO_DEVICE);
	अगर (dma_mapping_error(&fep->pdev->dev, addr)) अणु
		dev_kमुक्त_skb_any(skb);
		अगर (net_ratelimit())
			netdev_err(ndev, "Tx DMA memory map failed\n");
		वापस NETDEV_TX_OK;
	पूर्ण

	अगर (nr_frags) अणु
		last_bdp = fec_enet_txq_submit_frag_skb(txq, skb, ndev);
		अगर (IS_ERR(last_bdp)) अणु
			dma_unmap_single(&fep->pdev->dev, addr,
					 buflen, DMA_TO_DEVICE);
			dev_kमुक्त_skb_any(skb);
			वापस NETDEV_TX_OK;
		पूर्ण
	पूर्ण अन्यथा अणु
		status |= (BD_ENET_TX_INTR | BD_ENET_TX_LAST);
		अगर (fep->bufdesc_ex) अणु
			estatus = BD_ENET_TX_INT;
			अगर (unlikely(skb_shinfo(skb)->tx_flags &
				SKBTX_HW_TSTAMP && fep->hwts_tx_en))
				estatus |= BD_ENET_TX_TS;
		पूर्ण
	पूर्ण
	bdp->cbd_bufaddr = cpu_to_fec32(addr);
	bdp->cbd_datlen = cpu_to_fec16(buflen);

	अगर (fep->bufdesc_ex) अणु

		काष्ठा bufdesc_ex *ebdp = (काष्ठा bufdesc_ex *)bdp;

		अगर (unlikely(skb_shinfo(skb)->tx_flags & SKBTX_HW_TSTAMP &&
			fep->hwts_tx_en))
			skb_shinfo(skb)->tx_flags |= SKBTX_IN_PROGRESS;

		अगर (fep->quirks & FEC_QUIRK_HAS_AVB)
			estatus |= FEC_TX_BD_FTYPE(txq->bd.qid);

		अगर (skb->ip_summed == CHECKSUM_PARTIAL)
			estatus |= BD_ENET_TX_PINS | BD_ENET_TX_IINS;

		ebdp->cbd_bdu = 0;
		ebdp->cbd_esc = cpu_to_fec32(estatus);
	पूर्ण

	index = fec_enet_get_bd_index(last_bdp, &txq->bd);
	/* Save skb poपूर्णांकer */
	txq->tx_skbuff[index] = skb;

	/* Make sure the updates to rest of the descriptor are perक्रमmed beक्रमe
	 * transferring ownership.
	 */
	wmb();

	/* Send it on its way.  Tell FEC it's पढ़ोy, पूर्णांकerrupt when करोne,
	 * it's the last BD of the frame, and to put the CRC on the end.
	 */
	status |= (BD_ENET_TX_READY | BD_ENET_TX_TC);
	bdp->cbd_sc = cpu_to_fec16(status);

	/* If this was the last BD in the ring, start at the beginning again. */
	bdp = fec_enet_get_nextdesc(last_bdp, &txq->bd);

	skb_tx_बारtamp(skb);

	/* Make sure the update to bdp and tx_skbuff are perक्रमmed beक्रमe
	 * txq->bd.cur.
	 */
	wmb();
	txq->bd.cur = bdp;

	/* Trigger transmission start */
	ग_लिखोl(0, txq->bd.reg_desc_active);

	वापस 0;
पूर्ण

अटल पूर्णांक
fec_enet_txq_put_data_tso(काष्ठा fec_enet_priv_tx_q *txq, काष्ठा sk_buff *skb,
			  काष्ठा net_device *ndev,
			  काष्ठा bufdesc *bdp, पूर्णांक index, अक्षर *data,
			  पूर्णांक size, bool last_tcp, bool is_last)
अणु
	काष्ठा fec_enet_निजी *fep = netdev_priv(ndev);
	काष्ठा bufdesc_ex *ebdp = container_of(bdp, काष्ठा bufdesc_ex, desc);
	अचिन्हित लघु status;
	अचिन्हित पूर्णांक estatus = 0;
	dma_addr_t addr;

	status = fec16_to_cpu(bdp->cbd_sc);
	status &= ~BD_ENET_TX_STATS;

	status |= (BD_ENET_TX_TC | BD_ENET_TX_READY);

	अगर (((अचिन्हित दीर्घ) data) & fep->tx_align ||
		fep->quirks & FEC_QUIRK_SWAP_FRAME) अणु
		स_नकल(txq->tx_bounce[index], data, size);
		data = txq->tx_bounce[index];

		अगर (fep->quirks & FEC_QUIRK_SWAP_FRAME)
			swap_buffer(data, size);
	पूर्ण

	addr = dma_map_single(&fep->pdev->dev, data, size, DMA_TO_DEVICE);
	अगर (dma_mapping_error(&fep->pdev->dev, addr)) अणु
		dev_kमुक्त_skb_any(skb);
		अगर (net_ratelimit())
			netdev_err(ndev, "Tx DMA memory map failed\n");
		वापस NETDEV_TX_BUSY;
	पूर्ण

	bdp->cbd_datlen = cpu_to_fec16(size);
	bdp->cbd_bufaddr = cpu_to_fec32(addr);

	अगर (fep->bufdesc_ex) अणु
		अगर (fep->quirks & FEC_QUIRK_HAS_AVB)
			estatus |= FEC_TX_BD_FTYPE(txq->bd.qid);
		अगर (skb->ip_summed == CHECKSUM_PARTIAL)
			estatus |= BD_ENET_TX_PINS | BD_ENET_TX_IINS;
		ebdp->cbd_bdu = 0;
		ebdp->cbd_esc = cpu_to_fec32(estatus);
	पूर्ण

	/* Handle the last BD specially */
	अगर (last_tcp)
		status |= (BD_ENET_TX_LAST | BD_ENET_TX_TC);
	अगर (is_last) अणु
		status |= BD_ENET_TX_INTR;
		अगर (fep->bufdesc_ex)
			ebdp->cbd_esc |= cpu_to_fec32(BD_ENET_TX_INT);
	पूर्ण

	bdp->cbd_sc = cpu_to_fec16(status);

	वापस 0;
पूर्ण

अटल पूर्णांक
fec_enet_txq_put_hdr_tso(काष्ठा fec_enet_priv_tx_q *txq,
			 काष्ठा sk_buff *skb, काष्ठा net_device *ndev,
			 काष्ठा bufdesc *bdp, पूर्णांक index)
अणु
	काष्ठा fec_enet_निजी *fep = netdev_priv(ndev);
	पूर्णांक hdr_len = skb_transport_offset(skb) + tcp_hdrlen(skb);
	काष्ठा bufdesc_ex *ebdp = container_of(bdp, काष्ठा bufdesc_ex, desc);
	व्योम *bufaddr;
	अचिन्हित दीर्घ dmabuf;
	अचिन्हित लघु status;
	अचिन्हित पूर्णांक estatus = 0;

	status = fec16_to_cpu(bdp->cbd_sc);
	status &= ~BD_ENET_TX_STATS;
	status |= (BD_ENET_TX_TC | BD_ENET_TX_READY);

	bufaddr = txq->tso_hdrs + index * TSO_HEADER_SIZE;
	dmabuf = txq->tso_hdrs_dma + index * TSO_HEADER_SIZE;
	अगर (((अचिन्हित दीर्घ)bufaddr) & fep->tx_align ||
		fep->quirks & FEC_QUIRK_SWAP_FRAME) अणु
		स_नकल(txq->tx_bounce[index], skb->data, hdr_len);
		bufaddr = txq->tx_bounce[index];

		अगर (fep->quirks & FEC_QUIRK_SWAP_FRAME)
			swap_buffer(bufaddr, hdr_len);

		dmabuf = dma_map_single(&fep->pdev->dev, bufaddr,
					hdr_len, DMA_TO_DEVICE);
		अगर (dma_mapping_error(&fep->pdev->dev, dmabuf)) अणु
			dev_kमुक्त_skb_any(skb);
			अगर (net_ratelimit())
				netdev_err(ndev, "Tx DMA memory map failed\n");
			वापस NETDEV_TX_BUSY;
		पूर्ण
	पूर्ण

	bdp->cbd_bufaddr = cpu_to_fec32(dmabuf);
	bdp->cbd_datlen = cpu_to_fec16(hdr_len);

	अगर (fep->bufdesc_ex) अणु
		अगर (fep->quirks & FEC_QUIRK_HAS_AVB)
			estatus |= FEC_TX_BD_FTYPE(txq->bd.qid);
		अगर (skb->ip_summed == CHECKSUM_PARTIAL)
			estatus |= BD_ENET_TX_PINS | BD_ENET_TX_IINS;
		ebdp->cbd_bdu = 0;
		ebdp->cbd_esc = cpu_to_fec32(estatus);
	पूर्ण

	bdp->cbd_sc = cpu_to_fec16(status);

	वापस 0;
पूर्ण

अटल पूर्णांक fec_enet_txq_submit_tso(काष्ठा fec_enet_priv_tx_q *txq,
				   काष्ठा sk_buff *skb,
				   काष्ठा net_device *ndev)
अणु
	काष्ठा fec_enet_निजी *fep = netdev_priv(ndev);
	पूर्णांक hdr_len, total_len, data_left;
	काष्ठा bufdesc *bdp = txq->bd.cur;
	काष्ठा tso_t tso;
	अचिन्हित पूर्णांक index = 0;
	पूर्णांक ret;

	अगर (tso_count_descs(skb) >= fec_enet_get_मुक्त_txdesc_num(txq)) अणु
		dev_kमुक्त_skb_any(skb);
		अगर (net_ratelimit())
			netdev_err(ndev, "NOT enough BD for TSO!\n");
		वापस NETDEV_TX_OK;
	पूर्ण

	/* Protocol checksum off-load क्रम TCP and UDP. */
	अगर (fec_enet_clear_csum(skb, ndev)) अणु
		dev_kमुक्त_skb_any(skb);
		वापस NETDEV_TX_OK;
	पूर्ण

	/* Initialize the TSO handler, and prepare the first payload */
	hdr_len = tso_start(skb, &tso);

	total_len = skb->len - hdr_len;
	जबतक (total_len > 0) अणु
		अक्षर *hdr;

		index = fec_enet_get_bd_index(bdp, &txq->bd);
		data_left = min_t(पूर्णांक, skb_shinfo(skb)->gso_size, total_len);
		total_len -= data_left;

		/* prepare packet headers: MAC + IP + TCP */
		hdr = txq->tso_hdrs + index * TSO_HEADER_SIZE;
		tso_build_hdr(skb, hdr, &tso, data_left, total_len == 0);
		ret = fec_enet_txq_put_hdr_tso(txq, skb, ndev, bdp, index);
		अगर (ret)
			जाओ err_release;

		जबतक (data_left > 0) अणु
			पूर्णांक size;

			size = min_t(पूर्णांक, tso.size, data_left);
			bdp = fec_enet_get_nextdesc(bdp, &txq->bd);
			index = fec_enet_get_bd_index(bdp, &txq->bd);
			ret = fec_enet_txq_put_data_tso(txq, skb, ndev,
							bdp, index,
							tso.data, size,
							size == data_left,
							total_len == 0);
			अगर (ret)
				जाओ err_release;

			data_left -= size;
			tso_build_data(skb, &tso, size);
		पूर्ण

		bdp = fec_enet_get_nextdesc(bdp, &txq->bd);
	पूर्ण

	/* Save skb poपूर्णांकer */
	txq->tx_skbuff[index] = skb;

	skb_tx_बारtamp(skb);
	txq->bd.cur = bdp;

	/* Trigger transmission start */
	अगर (!(fep->quirks & FEC_QUIRK_ERR007885) ||
	    !पढ़ोl(txq->bd.reg_desc_active) ||
	    !पढ़ोl(txq->bd.reg_desc_active) ||
	    !पढ़ोl(txq->bd.reg_desc_active) ||
	    !पढ़ोl(txq->bd.reg_desc_active))
		ग_लिखोl(0, txq->bd.reg_desc_active);

	वापस 0;

err_release:
	/* TODO: Release all used data descriptors क्रम TSO */
	वापस ret;
पूर्ण

अटल netdev_tx_t
fec_enet_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *ndev)
अणु
	काष्ठा fec_enet_निजी *fep = netdev_priv(ndev);
	पूर्णांक entries_मुक्त;
	अचिन्हित लघु queue;
	काष्ठा fec_enet_priv_tx_q *txq;
	काष्ठा netdev_queue *nq;
	पूर्णांक ret;

	queue = skb_get_queue_mapping(skb);
	txq = fep->tx_queue[queue];
	nq = netdev_get_tx_queue(ndev, queue);

	अगर (skb_is_gso(skb))
		ret = fec_enet_txq_submit_tso(txq, skb, ndev);
	अन्यथा
		ret = fec_enet_txq_submit_skb(txq, skb, ndev);
	अगर (ret)
		वापस ret;

	entries_मुक्त = fec_enet_get_मुक्त_txdesc_num(txq);
	अगर (entries_मुक्त <= txq->tx_stop_threshold)
		netअगर_tx_stop_queue(nq);

	वापस NETDEV_TX_OK;
पूर्ण

/* Init RX & TX buffer descriptors
 */
अटल व्योम fec_enet_bd_init(काष्ठा net_device *dev)
अणु
	काष्ठा fec_enet_निजी *fep = netdev_priv(dev);
	काष्ठा fec_enet_priv_tx_q *txq;
	काष्ठा fec_enet_priv_rx_q *rxq;
	काष्ठा bufdesc *bdp;
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक q;

	क्रम (q = 0; q < fep->num_rx_queues; q++) अणु
		/* Initialize the receive buffer descriptors. */
		rxq = fep->rx_queue[q];
		bdp = rxq->bd.base;

		क्रम (i = 0; i < rxq->bd.ring_size; i++) अणु

			/* Initialize the BD क्रम every fragment in the page. */
			अगर (bdp->cbd_bufaddr)
				bdp->cbd_sc = cpu_to_fec16(BD_ENET_RX_EMPTY);
			अन्यथा
				bdp->cbd_sc = cpu_to_fec16(0);
			bdp = fec_enet_get_nextdesc(bdp, &rxq->bd);
		पूर्ण

		/* Set the last buffer to wrap */
		bdp = fec_enet_get_prevdesc(bdp, &rxq->bd);
		bdp->cbd_sc |= cpu_to_fec16(BD_SC_WRAP);

		rxq->bd.cur = rxq->bd.base;
	पूर्ण

	क्रम (q = 0; q < fep->num_tx_queues; q++) अणु
		/* ...and the same क्रम transmit */
		txq = fep->tx_queue[q];
		bdp = txq->bd.base;
		txq->bd.cur = bdp;

		क्रम (i = 0; i < txq->bd.ring_size; i++) अणु
			/* Initialize the BD क्रम every fragment in the page. */
			bdp->cbd_sc = cpu_to_fec16(0);
			अगर (bdp->cbd_bufaddr &&
			    !IS_TSO_HEADER(txq, fec32_to_cpu(bdp->cbd_bufaddr)))
				dma_unmap_single(&fep->pdev->dev,
						 fec32_to_cpu(bdp->cbd_bufaddr),
						 fec16_to_cpu(bdp->cbd_datlen),
						 DMA_TO_DEVICE);
			अगर (txq->tx_skbuff[i]) अणु
				dev_kमुक्त_skb_any(txq->tx_skbuff[i]);
				txq->tx_skbuff[i] = शून्य;
			पूर्ण
			bdp->cbd_bufaddr = cpu_to_fec32(0);
			bdp = fec_enet_get_nextdesc(bdp, &txq->bd);
		पूर्ण

		/* Set the last buffer to wrap */
		bdp = fec_enet_get_prevdesc(bdp, &txq->bd);
		bdp->cbd_sc |= cpu_to_fec16(BD_SC_WRAP);
		txq->dirty_tx = bdp;
	पूर्ण
पूर्ण

अटल व्योम fec_enet_active_rxring(काष्ठा net_device *ndev)
अणु
	काष्ठा fec_enet_निजी *fep = netdev_priv(ndev);
	पूर्णांक i;

	क्रम (i = 0; i < fep->num_rx_queues; i++)
		ग_लिखोl(0, fep->rx_queue[i]->bd.reg_desc_active);
पूर्ण

अटल व्योम fec_enet_enable_ring(काष्ठा net_device *ndev)
अणु
	काष्ठा fec_enet_निजी *fep = netdev_priv(ndev);
	काष्ठा fec_enet_priv_tx_q *txq;
	काष्ठा fec_enet_priv_rx_q *rxq;
	पूर्णांक i;

	क्रम (i = 0; i < fep->num_rx_queues; i++) अणु
		rxq = fep->rx_queue[i];
		ग_लिखोl(rxq->bd.dma, fep->hwp + FEC_R_DES_START(i));
		ग_लिखोl(PKT_MAXBUF_SIZE, fep->hwp + FEC_R_BUFF_SIZE(i));

		/* enable DMA1/2 */
		अगर (i)
			ग_लिखोl(RCMR_MATCHEN | RCMR_CMP(i),
			       fep->hwp + FEC_RCMR(i));
	पूर्ण

	क्रम (i = 0; i < fep->num_tx_queues; i++) अणु
		txq = fep->tx_queue[i];
		ग_लिखोl(txq->bd.dma, fep->hwp + FEC_X_DES_START(i));

		/* enable DMA1/2 */
		अगर (i)
			ग_लिखोl(DMA_CLASS_EN | IDLE_SLOPE(i),
			       fep->hwp + FEC_DMA_CFG(i));
	पूर्ण
पूर्ण

अटल व्योम fec_enet_reset_skb(काष्ठा net_device *ndev)
अणु
	काष्ठा fec_enet_निजी *fep = netdev_priv(ndev);
	काष्ठा fec_enet_priv_tx_q *txq;
	पूर्णांक i, j;

	क्रम (i = 0; i < fep->num_tx_queues; i++) अणु
		txq = fep->tx_queue[i];

		क्रम (j = 0; j < txq->bd.ring_size; j++) अणु
			अगर (txq->tx_skbuff[j]) अणु
				dev_kमुक्त_skb_any(txq->tx_skbuff[j]);
				txq->tx_skbuff[j] = शून्य;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/*
 * This function is called to start or restart the FEC during a link
 * change, transmit समयout, or to reconfigure the FEC.  The network
 * packet processing क्रम this device must be stopped beक्रमe this call.
 */
अटल व्योम
fec_restart(काष्ठा net_device *ndev)
अणु
	काष्ठा fec_enet_निजी *fep = netdev_priv(ndev);
	u32 temp_mac[2];
	u32 rcntl = OPT_FRAME_SIZE | 0x04;
	u32 ecntl = 0x2; /* ETHEREN */

	/* Whack a reset.  We should रुको क्रम this.
	 * For i.MX6SX SOC, enet use AXI bus, we use disable MAC
	 * instead of reset MAC itself.
	 */
	अगर (fep->quirks & FEC_QUIRK_HAS_AVB ||
	    ((fep->quirks & FEC_QUIRK_NO_HARD_RESET) && fep->link)) अणु
		ग_लिखोl(0, fep->hwp + FEC_ECNTRL);
	पूर्ण अन्यथा अणु
		ग_लिखोl(1, fep->hwp + FEC_ECNTRL);
		udelay(10);
	पूर्ण

	/*
	 * enet-mac reset will reset mac address रेजिस्टरs too,
	 * so need to reconfigure it.
	 */
	स_नकल(&temp_mac, ndev->dev_addr, ETH_ALEN);
	ग_लिखोl((__क्रमce u32)cpu_to_be32(temp_mac[0]),
	       fep->hwp + FEC_ADDR_LOW);
	ग_लिखोl((__क्रमce u32)cpu_to_be32(temp_mac[1]),
	       fep->hwp + FEC_ADDR_HIGH);

	/* Clear any outstanding पूर्णांकerrupt, except MDIO. */
	ग_लिखोl((0xffffffff & ~FEC_ENET_MII), fep->hwp + FEC_IEVENT);

	fec_enet_bd_init(ndev);

	fec_enet_enable_ring(ndev);

	/* Reset tx SKB buffers. */
	fec_enet_reset_skb(ndev);

	/* Enable MII mode */
	अगर (fep->full_duplex == DUPLEX_FULL) अणु
		/* FD enable */
		ग_लिखोl(0x04, fep->hwp + FEC_X_CNTRL);
	पूर्ण अन्यथा अणु
		/* No Rcv on Xmit */
		rcntl |= 0x02;
		ग_लिखोl(0x0, fep->hwp + FEC_X_CNTRL);
	पूर्ण

	/* Set MII speed */
	ग_लिखोl(fep->phy_speed, fep->hwp + FEC_MII_SPEED);

#अगर !defined(CONFIG_M5272)
	अगर (fep->quirks & FEC_QUIRK_HAS_RACC) अणु
		u32 val = पढ़ोl(fep->hwp + FEC_RACC);

		/* align IP header */
		val |= FEC_RACC_SHIFT16;
		अगर (fep->csum_flags & FLAG_RX_CSUM_ENABLED)
			/* set RX checksum */
			val |= FEC_RACC_OPTIONS;
		अन्यथा
			val &= ~FEC_RACC_OPTIONS;
		ग_लिखोl(val, fep->hwp + FEC_RACC);
		ग_लिखोl(PKT_MAXBUF_SIZE, fep->hwp + FEC_FTRL);
	पूर्ण
#पूर्ण_अगर

	/*
	 * The phy पूर्णांकerface and speed need to get configured
	 * dअगरferently on enet-mac.
	 */
	अगर (fep->quirks & FEC_QUIRK_ENET_MAC) अणु
		/* Enable flow control and length check */
		rcntl |= 0x40000000 | 0x00000020;

		/* RGMII, RMII or MII */
		अगर (fep->phy_पूर्णांकerface == PHY_INTERFACE_MODE_RGMII ||
		    fep->phy_पूर्णांकerface == PHY_INTERFACE_MODE_RGMII_ID ||
		    fep->phy_पूर्णांकerface == PHY_INTERFACE_MODE_RGMII_RXID ||
		    fep->phy_पूर्णांकerface == PHY_INTERFACE_MODE_RGMII_TXID)
			rcntl |= (1 << 6);
		अन्यथा अगर (fep->phy_पूर्णांकerface == PHY_INTERFACE_MODE_RMII)
			rcntl |= (1 << 8);
		अन्यथा
			rcntl &= ~(1 << 8);

		/* 1G, 100M or 10M */
		अगर (ndev->phydev) अणु
			अगर (ndev->phydev->speed == SPEED_1000)
				ecntl |= (1 << 5);
			अन्यथा अगर (ndev->phydev->speed == SPEED_100)
				rcntl &= ~(1 << 9);
			अन्यथा
				rcntl |= (1 << 9);
		पूर्ण
	पूर्ण अन्यथा अणु
#अगर_घोषित FEC_MIIGSK_ENR
		अगर (fep->quirks & FEC_QUIRK_USE_GASKET) अणु
			u32 cfgr;
			/* disable the gasket and रुको */
			ग_लिखोl(0, fep->hwp + FEC_MIIGSK_ENR);
			जबतक (पढ़ोl(fep->hwp + FEC_MIIGSK_ENR) & 4)
				udelay(1);

			/*
			 * configure the gasket:
			 *   RMII, 50 MHz, no loopback, no echo
			 *   MII, 25 MHz, no loopback, no echo
			 */
			cfgr = (fep->phy_पूर्णांकerface == PHY_INTERFACE_MODE_RMII)
				? BM_MIIGSK_CFGR_RMII : BM_MIIGSK_CFGR_MII;
			अगर (ndev->phydev && ndev->phydev->speed == SPEED_10)
				cfgr |= BM_MIIGSK_CFGR_FRCONT_10M;
			ग_लिखोl(cfgr, fep->hwp + FEC_MIIGSK_CFGR);

			/* re-enable the gasket */
			ग_लिखोl(2, fep->hwp + FEC_MIIGSK_ENR);
		पूर्ण
#पूर्ण_अगर
	पूर्ण

#अगर !defined(CONFIG_M5272)
	/* enable छोड़ो frame*/
	अगर ((fep->छोड़ो_flag & FEC_PAUSE_FLAG_ENABLE) ||
	    ((fep->छोड़ो_flag & FEC_PAUSE_FLAG_AUTONEG) &&
	     ndev->phydev && ndev->phydev->छोड़ो)) अणु
		rcntl |= FEC_ENET_FCE;

		/* set FIFO threshold parameter to reduce overrun */
		ग_लिखोl(FEC_ENET_RSEM_V, fep->hwp + FEC_R_FIFO_RSEM);
		ग_लिखोl(FEC_ENET_RSFL_V, fep->hwp + FEC_R_FIFO_RSFL);
		ग_लिखोl(FEC_ENET_RAEM_V, fep->hwp + FEC_R_FIFO_RAEM);
		ग_लिखोl(FEC_ENET_RAFL_V, fep->hwp + FEC_R_FIFO_RAFL);

		/* OPD */
		ग_लिखोl(FEC_ENET_OPD_V, fep->hwp + FEC_OPD);
	पूर्ण अन्यथा अणु
		rcntl &= ~FEC_ENET_FCE;
	पूर्ण
#पूर्ण_अगर /* !defined(CONFIG_M5272) */

	ग_लिखोl(rcntl, fep->hwp + FEC_R_CNTRL);

	/* Setup multicast filter. */
	set_multicast_list(ndev);
#अगर_अघोषित CONFIG_M5272
	ग_लिखोl(0, fep->hwp + FEC_HASH_TABLE_HIGH);
	ग_लिखोl(0, fep->hwp + FEC_HASH_TABLE_LOW);
#पूर्ण_अगर

	अगर (fep->quirks & FEC_QUIRK_ENET_MAC) अणु
		/* enable ENET endian swap */
		ecntl |= (1 << 8);
		/* enable ENET store and क्रमward mode */
		ग_लिखोl(1 << 8, fep->hwp + FEC_X_WMRK);
	पूर्ण

	अगर (fep->bufdesc_ex)
		ecntl |= (1 << 4);

#अगर_अघोषित CONFIG_M5272
	/* Enable the MIB statistic event counters */
	ग_लिखोl(0 << 31, fep->hwp + FEC_MIB_CTRLSTAT);
#पूर्ण_अगर

	/* And last, enable the transmit and receive processing */
	ग_लिखोl(ecntl, fep->hwp + FEC_ECNTRL);
	fec_enet_active_rxring(ndev);

	अगर (fep->bufdesc_ex)
		fec_ptp_start_cyclecounter(ndev);

	/* Enable पूर्णांकerrupts we wish to service */
	अगर (fep->link)
		ग_लिखोl(FEC_DEFAULT_IMASK, fep->hwp + FEC_IMASK);
	अन्यथा
		ग_लिखोl(0, fep->hwp + FEC_IMASK);

	/* Init the पूर्णांकerrupt coalescing */
	fec_enet_itr_coal_init(ndev);

पूर्ण

अटल व्योम fec_enet_stop_mode(काष्ठा fec_enet_निजी *fep, bool enabled)
अणु
	काष्ठा fec_platक्रमm_data *pdata = fep->pdev->dev.platक्रमm_data;
	काष्ठा fec_stop_mode_gpr *stop_gpr = &fep->stop_gpr;

	अगर (stop_gpr->gpr) अणु
		अगर (enabled)
			regmap_update_bits(stop_gpr->gpr, stop_gpr->reg,
					   BIT(stop_gpr->bit),
					   BIT(stop_gpr->bit));
		अन्यथा
			regmap_update_bits(stop_gpr->gpr, stop_gpr->reg,
					   BIT(stop_gpr->bit), 0);
	पूर्ण अन्यथा अगर (pdata && pdata->sleep_mode_enable) अणु
		pdata->sleep_mode_enable(enabled);
	पूर्ण
पूर्ण

अटल व्योम
fec_stop(काष्ठा net_device *ndev)
अणु
	काष्ठा fec_enet_निजी *fep = netdev_priv(ndev);
	u32 rmii_mode = पढ़ोl(fep->hwp + FEC_R_CNTRL) & (1 << 8);
	u32 val;

	/* We cannot expect a graceful transmit stop without link !!! */
	अगर (fep->link) अणु
		ग_लिखोl(1, fep->hwp + FEC_X_CNTRL); /* Graceful transmit stop */
		udelay(10);
		अगर (!(पढ़ोl(fep->hwp + FEC_IEVENT) & FEC_ENET_GRA))
			netdev_err(ndev, "Graceful transmit stop did not complete!\n");
	पूर्ण

	/* Whack a reset.  We should रुको क्रम this.
	 * For i.MX6SX SOC, enet use AXI bus, we use disable MAC
	 * instead of reset MAC itself.
	 */
	अगर (!(fep->wol_flag & FEC_WOL_FLAG_SLEEP_ON)) अणु
		अगर (fep->quirks & FEC_QUIRK_HAS_AVB) अणु
			ग_लिखोl(0, fep->hwp + FEC_ECNTRL);
		पूर्ण अन्यथा अणु
			ग_लिखोl(1, fep->hwp + FEC_ECNTRL);
			udelay(10);
		पूर्ण
		ग_लिखोl(FEC_DEFAULT_IMASK, fep->hwp + FEC_IMASK);
	पूर्ण अन्यथा अणु
		ग_लिखोl(FEC_DEFAULT_IMASK | FEC_ENET_WAKEUP, fep->hwp + FEC_IMASK);
		val = पढ़ोl(fep->hwp + FEC_ECNTRL);
		val |= (FEC_ECR_MAGICEN | FEC_ECR_SLEEP);
		ग_लिखोl(val, fep->hwp + FEC_ECNTRL);
		fec_enet_stop_mode(fep, true);
	पूर्ण
	ग_लिखोl(fep->phy_speed, fep->hwp + FEC_MII_SPEED);

	/* We have to keep ENET enabled to have MII पूर्णांकerrupt stay working */
	अगर (fep->quirks & FEC_QUIRK_ENET_MAC &&
		!(fep->wol_flag & FEC_WOL_FLAG_SLEEP_ON)) अणु
		ग_लिखोl(2, fep->hwp + FEC_ECNTRL);
		ग_लिखोl(rmii_mode, fep->hwp + FEC_R_CNTRL);
	पूर्ण
पूर्ण


अटल व्योम
fec_समयout(काष्ठा net_device *ndev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा fec_enet_निजी *fep = netdev_priv(ndev);

	fec_dump(ndev);

	ndev->stats.tx_errors++;

	schedule_work(&fep->tx_समयout_work);
पूर्ण

अटल व्योम fec_enet_समयout_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा fec_enet_निजी *fep =
		container_of(work, काष्ठा fec_enet_निजी, tx_समयout_work);
	काष्ठा net_device *ndev = fep->netdev;

	rtnl_lock();
	अगर (netअगर_device_present(ndev) || netअगर_running(ndev)) अणु
		napi_disable(&fep->napi);
		netअगर_tx_lock_bh(ndev);
		fec_restart(ndev);
		netअगर_tx_wake_all_queues(ndev);
		netअगर_tx_unlock_bh(ndev);
		napi_enable(&fep->napi);
	पूर्ण
	rtnl_unlock();
पूर्ण

अटल व्योम
fec_enet_hwtstamp(काष्ठा fec_enet_निजी *fep, अचिन्हित ts,
	काष्ठा skb_shared_hwtstamps *hwtstamps)
अणु
	अचिन्हित दीर्घ flags;
	u64 ns;

	spin_lock_irqsave(&fep->पंचांगreg_lock, flags);
	ns = समयcounter_cyc2समय(&fep->tc, ts);
	spin_unlock_irqrestore(&fep->पंचांगreg_lock, flags);

	स_रखो(hwtstamps, 0, माप(*hwtstamps));
	hwtstamps->hwtstamp = ns_to_kसमय(ns);
पूर्ण

अटल व्योम
fec_enet_tx_queue(काष्ठा net_device *ndev, u16 queue_id)
अणु
	काष्ठा	fec_enet_निजी *fep;
	काष्ठा bufdesc *bdp;
	अचिन्हित लघु status;
	काष्ठा	sk_buff	*skb;
	काष्ठा fec_enet_priv_tx_q *txq;
	काष्ठा netdev_queue *nq;
	पूर्णांक	index = 0;
	पूर्णांक	entries_मुक्त;

	fep = netdev_priv(ndev);

	txq = fep->tx_queue[queue_id];
	/* get next bdp of dirty_tx */
	nq = netdev_get_tx_queue(ndev, queue_id);
	bdp = txq->dirty_tx;

	/* get next bdp of dirty_tx */
	bdp = fec_enet_get_nextdesc(bdp, &txq->bd);

	जबतक (bdp != READ_ONCE(txq->bd.cur)) अणु
		/* Order the load of bd.cur and cbd_sc */
		rmb();
		status = fec16_to_cpu(READ_ONCE(bdp->cbd_sc));
		अगर (status & BD_ENET_TX_READY)
			अवरोध;

		index = fec_enet_get_bd_index(bdp, &txq->bd);

		skb = txq->tx_skbuff[index];
		txq->tx_skbuff[index] = शून्य;
		अगर (!IS_TSO_HEADER(txq, fec32_to_cpu(bdp->cbd_bufaddr)))
			dma_unmap_single(&fep->pdev->dev,
					 fec32_to_cpu(bdp->cbd_bufaddr),
					 fec16_to_cpu(bdp->cbd_datlen),
					 DMA_TO_DEVICE);
		bdp->cbd_bufaddr = cpu_to_fec32(0);
		अगर (!skb)
			जाओ skb_करोne;

		/* Check क्रम errors. */
		अगर (status & (BD_ENET_TX_HB | BD_ENET_TX_LC |
				   BD_ENET_TX_RL | BD_ENET_TX_UN |
				   BD_ENET_TX_CSL)) अणु
			ndev->stats.tx_errors++;
			अगर (status & BD_ENET_TX_HB)  /* No heartbeat */
				ndev->stats.tx_heartbeat_errors++;
			अगर (status & BD_ENET_TX_LC)  /* Late collision */
				ndev->stats.tx_winकरोw_errors++;
			अगर (status & BD_ENET_TX_RL)  /* Retrans limit */
				ndev->stats.tx_पातed_errors++;
			अगर (status & BD_ENET_TX_UN)  /* Underrun */
				ndev->stats.tx_fअगरo_errors++;
			अगर (status & BD_ENET_TX_CSL) /* Carrier lost */
				ndev->stats.tx_carrier_errors++;
		पूर्ण अन्यथा अणु
			ndev->stats.tx_packets++;
			ndev->stats.tx_bytes += skb->len;
		पूर्ण

		/* NOTE: SKBTX_IN_PROGRESS being set करोes not imply it's we who
		 * are to समय stamp the packet, so we still need to check समय
		 * stamping enabled flag.
		 */
		अगर (unlikely(skb_shinfo(skb)->tx_flags & SKBTX_IN_PROGRESS &&
			     fep->hwts_tx_en) &&
		    fep->bufdesc_ex) अणु
			काष्ठा skb_shared_hwtstamps shhwtstamps;
			काष्ठा bufdesc_ex *ebdp = (काष्ठा bufdesc_ex *)bdp;

			fec_enet_hwtstamp(fep, fec32_to_cpu(ebdp->ts), &shhwtstamps);
			skb_tstamp_tx(skb, &shhwtstamps);
		पूर्ण

		/* Deferred means some collisions occurred during transmit,
		 * but we eventually sent the packet OK.
		 */
		अगर (status & BD_ENET_TX_DEF)
			ndev->stats.collisions++;

		/* Free the sk buffer associated with this last transmit */
		dev_kमुक्त_skb_any(skb);
skb_करोne:
		/* Make sure the update to bdp and tx_skbuff are perक्रमmed
		 * beक्रमe dirty_tx
		 */
		wmb();
		txq->dirty_tx = bdp;

		/* Update poपूर्णांकer to next buffer descriptor to be transmitted */
		bdp = fec_enet_get_nextdesc(bdp, &txq->bd);

		/* Since we have मुक्तd up a buffer, the ring is no दीर्घer full
		 */
		अगर (netअगर_tx_queue_stopped(nq)) अणु
			entries_मुक्त = fec_enet_get_मुक्त_txdesc_num(txq);
			अगर (entries_मुक्त >= txq->tx_wake_threshold)
				netअगर_tx_wake_queue(nq);
		पूर्ण
	पूर्ण

	/* ERR006358: Keep the transmitter going */
	अगर (bdp != txq->bd.cur &&
	    पढ़ोl(txq->bd.reg_desc_active) == 0)
		ग_लिखोl(0, txq->bd.reg_desc_active);
पूर्ण

अटल व्योम fec_enet_tx(काष्ठा net_device *ndev)
अणु
	काष्ठा fec_enet_निजी *fep = netdev_priv(ndev);
	पूर्णांक i;

	/* Make sure that AVB queues are processed first. */
	क्रम (i = fep->num_tx_queues - 1; i >= 0; i--)
		fec_enet_tx_queue(ndev, i);
पूर्ण

अटल पूर्णांक
fec_enet_new_rxbdp(काष्ठा net_device *ndev, काष्ठा bufdesc *bdp, काष्ठा sk_buff *skb)
अणु
	काष्ठा  fec_enet_निजी *fep = netdev_priv(ndev);
	पूर्णांक off;

	off = ((अचिन्हित दीर्घ)skb->data) & fep->rx_align;
	अगर (off)
		skb_reserve(skb, fep->rx_align + 1 - off);

	bdp->cbd_bufaddr = cpu_to_fec32(dma_map_single(&fep->pdev->dev, skb->data, FEC_ENET_RX_FRSIZE - fep->rx_align, DMA_FROM_DEVICE));
	अगर (dma_mapping_error(&fep->pdev->dev, fec32_to_cpu(bdp->cbd_bufaddr))) अणु
		अगर (net_ratelimit())
			netdev_err(ndev, "Rx DMA memory map failed\n");
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल bool fec_enet_copyअवरोध(काष्ठा net_device *ndev, काष्ठा sk_buff **skb,
			       काष्ठा bufdesc *bdp, u32 length, bool swap)
अणु
	काष्ठा  fec_enet_निजी *fep = netdev_priv(ndev);
	काष्ठा sk_buff *new_skb;

	अगर (length > fep->rx_copyअवरोध)
		वापस false;

	new_skb = netdev_alloc_skb(ndev, length);
	अगर (!new_skb)
		वापस false;

	dma_sync_single_क्रम_cpu(&fep->pdev->dev,
				fec32_to_cpu(bdp->cbd_bufaddr),
				FEC_ENET_RX_FRSIZE - fep->rx_align,
				DMA_FROM_DEVICE);
	अगर (!swap)
		स_नकल(new_skb->data, (*skb)->data, length);
	अन्यथा
		swap_buffer2(new_skb->data, (*skb)->data, length);
	*skb = new_skb;

	वापस true;
पूर्ण

/* During a receive, the bd_rx.cur poपूर्णांकs to the current incoming buffer.
 * When we update through the ring, अगर the next incoming buffer has
 * not been given to the प्रणाली, we just set the empty indicator,
 * effectively tossing the packet.
 */
अटल पूर्णांक
fec_enet_rx_queue(काष्ठा net_device *ndev, पूर्णांक budget, u16 queue_id)
अणु
	काष्ठा fec_enet_निजी *fep = netdev_priv(ndev);
	काष्ठा fec_enet_priv_rx_q *rxq;
	काष्ठा bufdesc *bdp;
	अचिन्हित लघु status;
	काष्ठा  sk_buff *skb_new = शून्य;
	काष्ठा  sk_buff *skb;
	uलघु	pkt_len;
	__u8 *data;
	पूर्णांक	pkt_received = 0;
	काष्ठा	bufdesc_ex *ebdp = शून्य;
	bool	vlan_packet_rcvd = false;
	u16	vlan_tag;
	पूर्णांक	index = 0;
	bool	is_copyअवरोध;
	bool	need_swap = fep->quirks & FEC_QUIRK_SWAP_FRAME;

#अगर_घोषित CONFIG_M532x
	flush_cache_all();
#पूर्ण_अगर
	rxq = fep->rx_queue[queue_id];

	/* First, grab all of the stats क्रम the incoming packet.
	 * These get messed up अगर we get called due to a busy condition.
	 */
	bdp = rxq->bd.cur;

	जबतक (!((status = fec16_to_cpu(bdp->cbd_sc)) & BD_ENET_RX_EMPTY)) अणु

		अगर (pkt_received >= budget)
			अवरोध;
		pkt_received++;

		ग_लिखोl(FEC_ENET_RXF, fep->hwp + FEC_IEVENT);

		/* Check क्रम errors. */
		status ^= BD_ENET_RX_LAST;
		अगर (status & (BD_ENET_RX_LG | BD_ENET_RX_SH | BD_ENET_RX_NO |
			   BD_ENET_RX_CR | BD_ENET_RX_OV | BD_ENET_RX_LAST |
			   BD_ENET_RX_CL)) अणु
			ndev->stats.rx_errors++;
			अगर (status & BD_ENET_RX_OV) अणु
				/* FIFO overrun */
				ndev->stats.rx_fअगरo_errors++;
				जाओ rx_processing_करोne;
			पूर्ण
			अगर (status & (BD_ENET_RX_LG | BD_ENET_RX_SH
						| BD_ENET_RX_LAST)) अणु
				/* Frame too दीर्घ or too लघु. */
				ndev->stats.rx_length_errors++;
				अगर (status & BD_ENET_RX_LAST)
					netdev_err(ndev, "rcv is not +last\n");
			पूर्ण
			अगर (status & BD_ENET_RX_CR)	/* CRC Error */
				ndev->stats.rx_crc_errors++;
			/* Report late collisions as a frame error. */
			अगर (status & (BD_ENET_RX_NO | BD_ENET_RX_CL))
				ndev->stats.rx_frame_errors++;
			जाओ rx_processing_करोne;
		पूर्ण

		/* Process the incoming frame. */
		ndev->stats.rx_packets++;
		pkt_len = fec16_to_cpu(bdp->cbd_datlen);
		ndev->stats.rx_bytes += pkt_len;

		index = fec_enet_get_bd_index(bdp, &rxq->bd);
		skb = rxq->rx_skbuff[index];

		/* The packet length includes FCS, but we करोn't want to
		 * include that when passing upstream as it messes up
		 * bridging applications.
		 */
		is_copyअवरोध = fec_enet_copyअवरोध(ndev, &skb, bdp, pkt_len - 4,
						  need_swap);
		अगर (!is_copyअवरोध) अणु
			skb_new = netdev_alloc_skb(ndev, FEC_ENET_RX_FRSIZE);
			अगर (unlikely(!skb_new)) अणु
				ndev->stats.rx_dropped++;
				जाओ rx_processing_करोne;
			पूर्ण
			dma_unmap_single(&fep->pdev->dev,
					 fec32_to_cpu(bdp->cbd_bufaddr),
					 FEC_ENET_RX_FRSIZE - fep->rx_align,
					 DMA_FROM_DEVICE);
		पूर्ण

		prefetch(skb->data - NET_IP_ALIGN);
		skb_put(skb, pkt_len - 4);
		data = skb->data;

		अगर (!is_copyअवरोध && need_swap)
			swap_buffer(data, pkt_len);

#अगर !defined(CONFIG_M5272)
		अगर (fep->quirks & FEC_QUIRK_HAS_RACC)
			data = skb_pull_अंतरभूत(skb, 2);
#पूर्ण_अगर

		/* Extract the enhanced buffer descriptor */
		ebdp = शून्य;
		अगर (fep->bufdesc_ex)
			ebdp = (काष्ठा bufdesc_ex *)bdp;

		/* If this is a VLAN packet हटाओ the VLAN Tag */
		vlan_packet_rcvd = false;
		अगर ((ndev->features & NETIF_F_HW_VLAN_CTAG_RX) &&
		    fep->bufdesc_ex &&
		    (ebdp->cbd_esc & cpu_to_fec32(BD_ENET_RX_VLAN))) अणु
			/* Push and हटाओ the vlan tag */
			काष्ठा vlan_hdr *vlan_header =
					(काष्ठा vlan_hdr *) (data + ETH_HLEN);
			vlan_tag = ntohs(vlan_header->h_vlan_TCI);

			vlan_packet_rcvd = true;

			स_हटाओ(skb->data + VLAN_HLEN, data, ETH_ALEN * 2);
			skb_pull(skb, VLAN_HLEN);
		पूर्ण

		skb->protocol = eth_type_trans(skb, ndev);

		/* Get receive बारtamp from the skb */
		अगर (fep->hwts_rx_en && fep->bufdesc_ex)
			fec_enet_hwtstamp(fep, fec32_to_cpu(ebdp->ts),
					  skb_hwtstamps(skb));

		अगर (fep->bufdesc_ex &&
		    (fep->csum_flags & FLAG_RX_CSUM_ENABLED)) अणु
			अगर (!(ebdp->cbd_esc & cpu_to_fec32(FLAG_RX_CSUM_ERROR))) अणु
				/* करोn't check it */
				skb->ip_summed = CHECKSUM_UNNECESSARY;
			पूर्ण अन्यथा अणु
				skb_checksum_none_निश्चित(skb);
			पूर्ण
		पूर्ण

		/* Handle received VLAN packets */
		अगर (vlan_packet_rcvd)
			__vlan_hwaccel_put_tag(skb,
					       htons(ETH_P_8021Q),
					       vlan_tag);

		skb_record_rx_queue(skb, queue_id);
		napi_gro_receive(&fep->napi, skb);

		अगर (is_copyअवरोध) अणु
			dma_sync_single_क्रम_device(&fep->pdev->dev,
						   fec32_to_cpu(bdp->cbd_bufaddr),
						   FEC_ENET_RX_FRSIZE - fep->rx_align,
						   DMA_FROM_DEVICE);
		पूर्ण अन्यथा अणु
			rxq->rx_skbuff[index] = skb_new;
			fec_enet_new_rxbdp(ndev, bdp, skb_new);
		पूर्ण

rx_processing_करोne:
		/* Clear the status flags क्रम this buffer */
		status &= ~BD_ENET_RX_STATS;

		/* Mark the buffer empty */
		status |= BD_ENET_RX_EMPTY;

		अगर (fep->bufdesc_ex) अणु
			काष्ठा bufdesc_ex *ebdp = (काष्ठा bufdesc_ex *)bdp;

			ebdp->cbd_esc = cpu_to_fec32(BD_ENET_RX_INT);
			ebdp->cbd_prot = 0;
			ebdp->cbd_bdu = 0;
		पूर्ण
		/* Make sure the updates to rest of the descriptor are
		 * perक्रमmed beक्रमe transferring ownership.
		 */
		wmb();
		bdp->cbd_sc = cpu_to_fec16(status);

		/* Update BD poपूर्णांकer to next entry */
		bdp = fec_enet_get_nextdesc(bdp, &rxq->bd);

		/* Doing this here will keep the FEC running जबतक we process
		 * incoming frames.  On a heavily loaded network, we should be
		 * able to keep up at the expense of प्रणाली resources.
		 */
		ग_लिखोl(0, rxq->bd.reg_desc_active);
	पूर्ण
	rxq->bd.cur = bdp;
	वापस pkt_received;
पूर्ण

अटल पूर्णांक fec_enet_rx(काष्ठा net_device *ndev, पूर्णांक budget)
अणु
	काष्ठा fec_enet_निजी *fep = netdev_priv(ndev);
	पूर्णांक i, करोne = 0;

	/* Make sure that AVB queues are processed first. */
	क्रम (i = fep->num_rx_queues - 1; i >= 0; i--)
		करोne += fec_enet_rx_queue(ndev, budget - करोne, i);

	वापस करोne;
पूर्ण

अटल bool fec_enet_collect_events(काष्ठा fec_enet_निजी *fep)
अणु
	uपूर्णांक पूर्णांक_events;

	पूर्णांक_events = पढ़ोl(fep->hwp + FEC_IEVENT);

	/* Don't clear MDIO events, we poll क्रम those */
	पूर्णांक_events &= ~FEC_ENET_MII;

	ग_लिखोl(पूर्णांक_events, fep->hwp + FEC_IEVENT);

	वापस पूर्णांक_events != 0;
पूर्ण

अटल irqवापस_t
fec_enet_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *ndev = dev_id;
	काष्ठा fec_enet_निजी *fep = netdev_priv(ndev);
	irqवापस_t ret = IRQ_NONE;

	अगर (fec_enet_collect_events(fep) && fep->link) अणु
		ret = IRQ_HANDLED;

		अगर (napi_schedule_prep(&fep->napi)) अणु
			/* Disable पूर्णांकerrupts */
			ग_लिखोl(0, fep->hwp + FEC_IMASK);
			__napi_schedule(&fep->napi);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक fec_enet_rx_napi(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा net_device *ndev = napi->dev;
	काष्ठा fec_enet_निजी *fep = netdev_priv(ndev);
	पूर्णांक करोne = 0;

	करो अणु
		करोne += fec_enet_rx(ndev, budget - करोne);
		fec_enet_tx(ndev);
	पूर्ण जबतक ((करोne < budget) && fec_enet_collect_events(fep));

	अगर (करोne < budget) अणु
		napi_complete_करोne(napi, करोne);
		ग_लिखोl(FEC_DEFAULT_IMASK, fep->hwp + FEC_IMASK);
	पूर्ण

	वापस करोne;
पूर्ण

/* ------------------------------------------------------------------------- */
अटल पूर्णांक fec_get_mac(काष्ठा net_device *ndev)
अणु
	काष्ठा fec_enet_निजी *fep = netdev_priv(ndev);
	अचिन्हित अक्षर *iap, पंचांगpaddr[ETH_ALEN];
	पूर्णांक ret;

	/*
	 * try to get mac address in following order:
	 *
	 * 1) module parameter via kernel command line in क्रमm
	 *    fec.macaddr=0x00,0x04,0x9f,0x01,0x30,0xe0
	 */
	iap = macaddr;

	/*
	 * 2) from device tree data
	 */
	अगर (!is_valid_ether_addr(iap)) अणु
		काष्ठा device_node *np = fep->pdev->dev.of_node;
		अगर (np) अणु
			ret = of_get_mac_address(np, पंचांगpaddr);
			अगर (!ret)
				iap = पंचांगpaddr;
			अन्यथा अगर (ret == -EPROBE_DEFER)
				वापस ret;
		पूर्ण
	पूर्ण

	/*
	 * 3) from flash or fuse (via platक्रमm data)
	 */
	अगर (!is_valid_ether_addr(iap)) अणु
#अगर_घोषित CONFIG_M5272
		अगर (FEC_FLASHMAC)
			iap = (अचिन्हित अक्षर *)FEC_FLASHMAC;
#अन्यथा
		काष्ठा fec_platक्रमm_data *pdata = dev_get_platdata(&fep->pdev->dev);

		अगर (pdata)
			iap = (अचिन्हित अक्षर *)&pdata->mac;
#पूर्ण_अगर
	पूर्ण

	/*
	 * 4) FEC mac रेजिस्टरs set by bootloader
	 */
	अगर (!is_valid_ether_addr(iap)) अणु
		*((__be32 *) &पंचांगpaddr[0]) =
			cpu_to_be32(पढ़ोl(fep->hwp + FEC_ADDR_LOW));
		*((__be16 *) &पंचांगpaddr[4]) =
			cpu_to_be16(पढ़ोl(fep->hwp + FEC_ADDR_HIGH) >> 16);
		iap = &पंचांगpaddr[0];
	पूर्ण

	/*
	 * 5) अक्रमom mac address
	 */
	अगर (!is_valid_ether_addr(iap)) अणु
		/* Report it and use a अक्रमom ethernet address instead */
		dev_err(&fep->pdev->dev, "Invalid MAC address: %pM\n", iap);
		eth_hw_addr_अक्रमom(ndev);
		dev_info(&fep->pdev->dev, "Using random MAC address: %pM\n",
			 ndev->dev_addr);
		वापस 0;
	पूर्ण

	स_नकल(ndev->dev_addr, iap, ETH_ALEN);

	/* Adjust MAC अगर using macaddr */
	अगर (iap == macaddr)
		 ndev->dev_addr[ETH_ALEN-1] = macaddr[ETH_ALEN-1] + fep->dev_id;

	वापस 0;
पूर्ण

/* ------------------------------------------------------------------------- */

/*
 * Phy section
 */
अटल व्योम fec_enet_adjust_link(काष्ठा net_device *ndev)
अणु
	काष्ठा fec_enet_निजी *fep = netdev_priv(ndev);
	काष्ठा phy_device *phy_dev = ndev->phydev;
	पूर्णांक status_change = 0;

	/*
	 * If the netdev is करोwn, or is going करोwn, we're not पूर्णांकerested
	 * in link state events, so just mark our idea of the link as करोwn
	 * and ignore the event.
	 */
	अगर (!netअगर_running(ndev) || !netअगर_device_present(ndev)) अणु
		fep->link = 0;
	पूर्ण अन्यथा अगर (phy_dev->link) अणु
		अगर (!fep->link) अणु
			fep->link = phy_dev->link;
			status_change = 1;
		पूर्ण

		अगर (fep->full_duplex != phy_dev->duplex) अणु
			fep->full_duplex = phy_dev->duplex;
			status_change = 1;
		पूर्ण

		अगर (phy_dev->speed != fep->speed) अणु
			fep->speed = phy_dev->speed;
			status_change = 1;
		पूर्ण

		/* अगर any of the above changed restart the FEC */
		अगर (status_change) अणु
			napi_disable(&fep->napi);
			netअगर_tx_lock_bh(ndev);
			fec_restart(ndev);
			netअगर_tx_wake_all_queues(ndev);
			netअगर_tx_unlock_bh(ndev);
			napi_enable(&fep->napi);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (fep->link) अणु
			napi_disable(&fep->napi);
			netअगर_tx_lock_bh(ndev);
			fec_stop(ndev);
			netअगर_tx_unlock_bh(ndev);
			napi_enable(&fep->napi);
			fep->link = phy_dev->link;
			status_change = 1;
		पूर्ण
	पूर्ण

	अगर (status_change)
		phy_prपूर्णांक_status(phy_dev);
पूर्ण

अटल पूर्णांक fec_enet_mdio_रुको(काष्ठा fec_enet_निजी *fep)
अणु
	uपूर्णांक ievent;
	पूर्णांक ret;

	ret = पढ़ोl_poll_समयout_atomic(fep->hwp + FEC_IEVENT, ievent,
					ievent & FEC_ENET_MII, 2, 30000);

	अगर (!ret)
		ग_लिखोl(FEC_ENET_MII, fep->hwp + FEC_IEVENT);

	वापस ret;
पूर्ण

अटल पूर्णांक fec_enet_mdio_पढ़ो(काष्ठा mii_bus *bus, पूर्णांक mii_id, पूर्णांक regnum)
अणु
	काष्ठा fec_enet_निजी *fep = bus->priv;
	काष्ठा device *dev = &fep->pdev->dev;
	पूर्णांक ret = 0, frame_start, frame_addr, frame_op;
	bool is_c45 = !!(regnum & MII_ADDR_C45);

	ret = pm_runसमय_resume_and_get(dev);
	अगर (ret < 0)
		वापस ret;

	अगर (is_c45) अणु
		frame_start = FEC_MMFR_ST_C45;

		/* ग_लिखो address */
		frame_addr = (regnum >> 16);
		ग_लिखोl(frame_start | FEC_MMFR_OP_ADDR_WRITE |
		       FEC_MMFR_PA(mii_id) | FEC_MMFR_RA(frame_addr) |
		       FEC_MMFR_TA | (regnum & 0xFFFF),
		       fep->hwp + FEC_MII_DATA);

		/* रुको क्रम end of transfer */
		ret = fec_enet_mdio_रुको(fep);
		अगर (ret) अणु
			netdev_err(fep->netdev, "MDIO address write timeout\n");
			जाओ out;
		पूर्ण

		frame_op = FEC_MMFR_OP_READ_C45;

	पूर्ण अन्यथा अणु
		/* C22 पढ़ो */
		frame_op = FEC_MMFR_OP_READ;
		frame_start = FEC_MMFR_ST;
		frame_addr = regnum;
	पूर्ण

	/* start a पढ़ो op */
	ग_लिखोl(frame_start | frame_op |
		FEC_MMFR_PA(mii_id) | FEC_MMFR_RA(frame_addr) |
		FEC_MMFR_TA, fep->hwp + FEC_MII_DATA);

	/* रुको क्रम end of transfer */
	ret = fec_enet_mdio_रुको(fep);
	अगर (ret) अणु
		netdev_err(fep->netdev, "MDIO read timeout\n");
		जाओ out;
	पूर्ण

	ret = FEC_MMFR_DATA(पढ़ोl(fep->hwp + FEC_MII_DATA));

out:
	pm_runसमय_mark_last_busy(dev);
	pm_runसमय_put_स्वतःsuspend(dev);

	वापस ret;
पूर्ण

अटल पूर्णांक fec_enet_mdio_ग_लिखो(काष्ठा mii_bus *bus, पूर्णांक mii_id, पूर्णांक regnum,
			   u16 value)
अणु
	काष्ठा fec_enet_निजी *fep = bus->priv;
	काष्ठा device *dev = &fep->pdev->dev;
	पूर्णांक ret, frame_start, frame_addr;
	bool is_c45 = !!(regnum & MII_ADDR_C45);

	ret = pm_runसमय_resume_and_get(dev);
	अगर (ret < 0)
		वापस ret;

	अगर (is_c45) अणु
		frame_start = FEC_MMFR_ST_C45;

		/* ग_लिखो address */
		frame_addr = (regnum >> 16);
		ग_लिखोl(frame_start | FEC_MMFR_OP_ADDR_WRITE |
		       FEC_MMFR_PA(mii_id) | FEC_MMFR_RA(frame_addr) |
		       FEC_MMFR_TA | (regnum & 0xFFFF),
		       fep->hwp + FEC_MII_DATA);

		/* रुको क्रम end of transfer */
		ret = fec_enet_mdio_रुको(fep);
		अगर (ret) अणु
			netdev_err(fep->netdev, "MDIO address write timeout\n");
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* C22 ग_लिखो */
		frame_start = FEC_MMFR_ST;
		frame_addr = regnum;
	पूर्ण

	/* start a ग_लिखो op */
	ग_लिखोl(frame_start | FEC_MMFR_OP_WRITE |
		FEC_MMFR_PA(mii_id) | FEC_MMFR_RA(frame_addr) |
		FEC_MMFR_TA | FEC_MMFR_DATA(value),
		fep->hwp + FEC_MII_DATA);

	/* रुको क्रम end of transfer */
	ret = fec_enet_mdio_रुको(fep);
	अगर (ret)
		netdev_err(fep->netdev, "MDIO write timeout\n");

out:
	pm_runसमय_mark_last_busy(dev);
	pm_runसमय_put_स्वतःsuspend(dev);

	वापस ret;
पूर्ण

अटल व्योम fec_enet_phy_reset_after_clk_enable(काष्ठा net_device *ndev)
अणु
	काष्ठा fec_enet_निजी *fep = netdev_priv(ndev);
	काष्ठा phy_device *phy_dev = ndev->phydev;

	अगर (phy_dev) अणु
		phy_reset_after_clk_enable(phy_dev);
	पूर्ण अन्यथा अगर (fep->phy_node) अणु
		/*
		 * If the PHY still is not bound to the MAC, but there is
		 * OF PHY node and a matching PHY device instance alपढ़ोy,
		 * use the OF PHY node to obtain the PHY device instance,
		 * and then use that PHY device instance when triggering
		 * the PHY reset.
		 */
		phy_dev = of_phy_find_device(fep->phy_node);
		phy_reset_after_clk_enable(phy_dev);
		put_device(&phy_dev->mdio.dev);
	पूर्ण
पूर्ण

अटल पूर्णांक fec_enet_clk_enable(काष्ठा net_device *ndev, bool enable)
अणु
	काष्ठा fec_enet_निजी *fep = netdev_priv(ndev);
	पूर्णांक ret;

	अगर (enable) अणु
		ret = clk_prepare_enable(fep->clk_enet_out);
		अगर (ret)
			वापस ret;

		अगर (fep->clk_ptp) अणु
			mutex_lock(&fep->ptp_clk_mutex);
			ret = clk_prepare_enable(fep->clk_ptp);
			अगर (ret) अणु
				mutex_unlock(&fep->ptp_clk_mutex);
				जाओ failed_clk_ptp;
			पूर्ण अन्यथा अणु
				fep->ptp_clk_on = true;
			पूर्ण
			mutex_unlock(&fep->ptp_clk_mutex);
		पूर्ण

		ret = clk_prepare_enable(fep->clk_ref);
		अगर (ret)
			जाओ failed_clk_ref;

		fec_enet_phy_reset_after_clk_enable(ndev);
	पूर्ण अन्यथा अणु
		clk_disable_unprepare(fep->clk_enet_out);
		अगर (fep->clk_ptp) अणु
			mutex_lock(&fep->ptp_clk_mutex);
			clk_disable_unprepare(fep->clk_ptp);
			fep->ptp_clk_on = false;
			mutex_unlock(&fep->ptp_clk_mutex);
		पूर्ण
		clk_disable_unprepare(fep->clk_ref);
	पूर्ण

	वापस 0;

failed_clk_ref:
	अगर (fep->clk_ptp) अणु
		mutex_lock(&fep->ptp_clk_mutex);
		clk_disable_unprepare(fep->clk_ptp);
		fep->ptp_clk_on = false;
		mutex_unlock(&fep->ptp_clk_mutex);
	पूर्ण
failed_clk_ptp:
	clk_disable_unprepare(fep->clk_enet_out);

	वापस ret;
पूर्ण

अटल पूर्णांक fec_enet_mii_probe(काष्ठा net_device *ndev)
अणु
	काष्ठा fec_enet_निजी *fep = netdev_priv(ndev);
	काष्ठा phy_device *phy_dev = शून्य;
	अक्षर mdio_bus_id[MII_BUS_ID_SIZE];
	अक्षर phy_name[MII_BUS_ID_SIZE + 3];
	पूर्णांक phy_id;
	पूर्णांक dev_id = fep->dev_id;

	अगर (fep->phy_node) अणु
		phy_dev = of_phy_connect(ndev, fep->phy_node,
					 &fec_enet_adjust_link, 0,
					 fep->phy_पूर्णांकerface);
		अगर (!phy_dev) अणु
			netdev_err(ndev, "Unable to connect to phy\n");
			वापस -ENODEV;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* check क्रम attached phy */
		क्रम (phy_id = 0; (phy_id < PHY_MAX_ADDR); phy_id++) अणु
			अगर (!mdiobus_is_रेजिस्टरed_device(fep->mii_bus, phy_id))
				जारी;
			अगर (dev_id--)
				जारी;
			strlcpy(mdio_bus_id, fep->mii_bus->id, MII_BUS_ID_SIZE);
			अवरोध;
		पूर्ण

		अगर (phy_id >= PHY_MAX_ADDR) अणु
			netdev_info(ndev, "no PHY, assuming direct connection to switch\n");
			strlcpy(mdio_bus_id, "fixed-0", MII_BUS_ID_SIZE);
			phy_id = 0;
		पूर्ण

		snम_लिखो(phy_name, माप(phy_name),
			 PHY_ID_FMT, mdio_bus_id, phy_id);
		phy_dev = phy_connect(ndev, phy_name, &fec_enet_adjust_link,
				      fep->phy_पूर्णांकerface);
	पूर्ण

	अगर (IS_ERR(phy_dev)) अणु
		netdev_err(ndev, "could not attach to PHY\n");
		वापस PTR_ERR(phy_dev);
	पूर्ण

	/* mask with MAC supported features */
	अगर (fep->quirks & FEC_QUIRK_HAS_GBIT) अणु
		phy_set_max_speed(phy_dev, 1000);
		phy_हटाओ_link_mode(phy_dev,
				     ETHTOOL_LINK_MODE_1000baseT_Half_BIT);
#अगर !defined(CONFIG_M5272)
		phy_support_sym_छोड़ो(phy_dev);
#पूर्ण_अगर
	पूर्ण
	अन्यथा
		phy_set_max_speed(phy_dev, 100);

	fep->link = 0;
	fep->full_duplex = 0;

	phy_dev->mac_managed_pm = 1;

	phy_attached_info(phy_dev);

	वापस 0;
पूर्ण

अटल पूर्णांक fec_enet_mii_init(काष्ठा platक्रमm_device *pdev)
अणु
	अटल काष्ठा mii_bus *fec0_mii_bus;
	काष्ठा net_device *ndev = platक्रमm_get_drvdata(pdev);
	काष्ठा fec_enet_निजी *fep = netdev_priv(ndev);
	bool suppress_preamble = false;
	काष्ठा device_node *node;
	पूर्णांक err = -ENXIO;
	u32 mii_speed, holdसमय;
	u32 bus_freq;

	/*
	 * The i.MX28 dual fec पूर्णांकerfaces are not equal.
	 * Here are the dअगरferences:
	 *
	 *  - fec0 supports MII & RMII modes जबतक fec1 only supports RMII
	 *  - fec0 acts as the 1588 समय master जबतक fec1 is slave
	 *  - बाह्यal phys can only be configured by fec0
	 *
	 * That is to say fec1 can not work independently. It only works
	 * when fec0 is working. The reason behind this design is that the
	 * second पूर्णांकerface is added primarily क्रम Switch mode.
	 *
	 * Because of the last poपूर्णांक above, both phys are attached on fec0
	 * mdio पूर्णांकerface in board design, and need to be configured by
	 * fec0 mii_bus.
	 */
	अगर ((fep->quirks & FEC_QUIRK_SINGLE_MDIO) && fep->dev_id > 0) अणु
		/* fec1 uses fec0 mii_bus */
		अगर (mii_cnt && fec0_mii_bus) अणु
			fep->mii_bus = fec0_mii_bus;
			mii_cnt++;
			वापस 0;
		पूर्ण
		वापस -ENOENT;
	पूर्ण

	bus_freq = 2500000; /* 2.5MHz by शेष */
	node = of_get_child_by_name(pdev->dev.of_node, "mdio");
	अगर (node) अणु
		of_property_पढ़ो_u32(node, "clock-frequency", &bus_freq);
		suppress_preamble = of_property_पढ़ो_bool(node,
							  "suppress-preamble");
	पूर्ण

	/*
	 * Set MII speed (= clk_get_rate() / 2 * phy_speed)
	 *
	 * The क्रमmula क्रम FEC MDC is 'ref_freq / (MII_SPEED x 2)' जबतक
	 * क्रम ENET-MAC is 'ref_freq / ((MII_SPEED + 1) x 2)'.  The i.MX28
	 * Reference Manual has an error on this, and माला_लो fixed on i.MX6Q
	 * करोcument.
	 */
	mii_speed = DIV_ROUND_UP(clk_get_rate(fep->clk_ipg), bus_freq * 2);
	अगर (fep->quirks & FEC_QUIRK_ENET_MAC)
		mii_speed--;
	अगर (mii_speed > 63) अणु
		dev_err(&pdev->dev,
			"fec clock (%lu) too fast to get right mii speed\n",
			clk_get_rate(fep->clk_ipg));
		err = -EINVAL;
		जाओ err_out;
	पूर्ण

	/*
	 * The i.MX28 and i.MX6 types have another filed in the MSCR (aka
	 * MII_SPEED) रेजिस्टर that defines the MDIO output hold समय. Earlier
	 * versions are RAZ there, so just ignore the dअगरference and ग_लिखो the
	 * रेजिस्टर always.
	 * The minimal hold समय according to IEE802.3 (clause 22) is 10 ns.
	 * HOLDTIME + 1 is the number of clk cycles the fec is holding the
	 * output.
	 * The HOLDTIME bitfield takes values between 0 and 7 (inclusive).
	 * Given that उच्चमान(clkrate / 5000000) <= 64, the calculation क्रम
	 * holdसमय cannot result in a value greater than 3.
	 */
	holdसमय = DIV_ROUND_UP(clk_get_rate(fep->clk_ipg), 100000000) - 1;

	fep->phy_speed = mii_speed << 1 | holdसमय << 8;

	अगर (suppress_preamble)
		fep->phy_speed |= BIT(7);

	अगर (fep->quirks & FEC_QUIRK_CLEAR_SETUP_MII) अणु
		/* Clear MMFR to aव्योम to generate MII event by writing MSCR.
		 * MII event generation condition:
		 * - writing MSCR:
		 *	- mmfr[31:0]_not_zero & mscr[7:0]_is_zero &
		 *	  mscr_reg_data_in[7:0] != 0
		 * - writing MMFR:
		 *	- mscr[7:0]_not_zero
		 */
		ग_लिखोl(0, fep->hwp + FEC_MII_DATA);
	पूर्ण

	ग_लिखोl(fep->phy_speed, fep->hwp + FEC_MII_SPEED);

	/* Clear any pending transaction complete indication */
	ग_लिखोl(FEC_ENET_MII, fep->hwp + FEC_IEVENT);

	fep->mii_bus = mdiobus_alloc();
	अगर (fep->mii_bus == शून्य) अणु
		err = -ENOMEM;
		जाओ err_out;
	पूर्ण

	fep->mii_bus->name = "fec_enet_mii_bus";
	fep->mii_bus->पढ़ो = fec_enet_mdio_पढ़ो;
	fep->mii_bus->ग_लिखो = fec_enet_mdio_ग_लिखो;
	snम_लिखो(fep->mii_bus->id, MII_BUS_ID_SIZE, "%s-%x",
		pdev->name, fep->dev_id + 1);
	fep->mii_bus->priv = fep;
	fep->mii_bus->parent = &pdev->dev;

	err = of_mdiobus_रेजिस्टर(fep->mii_bus, node);
	अगर (err)
		जाओ err_out_मुक्त_mdiobus;
	of_node_put(node);

	mii_cnt++;

	/* save fec0 mii_bus */
	अगर (fep->quirks & FEC_QUIRK_SINGLE_MDIO)
		fec0_mii_bus = fep->mii_bus;

	वापस 0;

err_out_मुक्त_mdiobus:
	mdiobus_मुक्त(fep->mii_bus);
err_out:
	of_node_put(node);
	वापस err;
पूर्ण

अटल व्योम fec_enet_mii_हटाओ(काष्ठा fec_enet_निजी *fep)
अणु
	अगर (--mii_cnt == 0) अणु
		mdiobus_unरेजिस्टर(fep->mii_bus);
		mdiobus_मुक्त(fep->mii_bus);
	पूर्ण
पूर्ण

अटल व्योम fec_enet_get_drvinfo(काष्ठा net_device *ndev,
				 काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा fec_enet_निजी *fep = netdev_priv(ndev);

	strlcpy(info->driver, fep->pdev->dev.driver->name,
		माप(info->driver));
	strlcpy(info->bus_info, dev_name(&ndev->dev), माप(info->bus_info));
पूर्ण

अटल पूर्णांक fec_enet_get_regs_len(काष्ठा net_device *ndev)
अणु
	काष्ठा fec_enet_निजी *fep = netdev_priv(ndev);
	काष्ठा resource *r;
	पूर्णांक s = 0;

	r = platक्रमm_get_resource(fep->pdev, IORESOURCE_MEM, 0);
	अगर (r)
		s = resource_size(r);

	वापस s;
पूर्ण

/* List of रेजिस्टरs that can be safety be पढ़ो to dump them with ethtool */
#अगर defined(CONFIG_M523x) || defined(CONFIG_M527x) || defined(CONFIG_M528x) || \
	defined(CONFIG_M520x) || defined(CONFIG_M532x) || defined(CONFIG_ARM) || \
	defined(CONFIG_ARM64) || defined(CONFIG_COMPILE_TEST)
अटल __u32 fec_enet_रेजिस्टर_version = 2;
अटल u32 fec_enet_रेजिस्टर_offset[] = अणु
	FEC_IEVENT, FEC_IMASK, FEC_R_DES_ACTIVE_0, FEC_X_DES_ACTIVE_0,
	FEC_ECNTRL, FEC_MII_DATA, FEC_MII_SPEED, FEC_MIB_CTRLSTAT, FEC_R_CNTRL,
	FEC_X_CNTRL, FEC_ADDR_LOW, FEC_ADDR_HIGH, FEC_OPD, FEC_TXIC0, FEC_TXIC1,
	FEC_TXIC2, FEC_RXIC0, FEC_RXIC1, FEC_RXIC2, FEC_HASH_TABLE_HIGH,
	FEC_HASH_TABLE_LOW, FEC_GRP_HASH_TABLE_HIGH, FEC_GRP_HASH_TABLE_LOW,
	FEC_X_WMRK, FEC_R_BOUND, FEC_R_FSTART, FEC_R_DES_START_1,
	FEC_X_DES_START_1, FEC_R_BUFF_SIZE_1, FEC_R_DES_START_2,
	FEC_X_DES_START_2, FEC_R_BUFF_SIZE_2, FEC_R_DES_START_0,
	FEC_X_DES_START_0, FEC_R_BUFF_SIZE_0, FEC_R_FIFO_RSFL, FEC_R_FIFO_RSEM,
	FEC_R_FIFO_RAEM, FEC_R_FIFO_RAFL, FEC_RACC, FEC_RCMR_1, FEC_RCMR_2,
	FEC_DMA_CFG_1, FEC_DMA_CFG_2, FEC_R_DES_ACTIVE_1, FEC_X_DES_ACTIVE_1,
	FEC_R_DES_ACTIVE_2, FEC_X_DES_ACTIVE_2, FEC_QOS_SCHEME,
	RMON_T_DROP, RMON_T_PACKETS, RMON_T_BC_PKT, RMON_T_MC_PKT,
	RMON_T_CRC_ALIGN, RMON_T_UNDERSIZE, RMON_T_OVERSIZE, RMON_T_FRAG,
	RMON_T_JAB, RMON_T_COL, RMON_T_P64, RMON_T_P65TO127, RMON_T_P128TO255,
	RMON_T_P256TO511, RMON_T_P512TO1023, RMON_T_P1024TO2047,
	RMON_T_P_GTE2048, RMON_T_OCTETS,
	IEEE_T_DROP, IEEE_T_FRAME_OK, IEEE_T_1COL, IEEE_T_MCOL, IEEE_T_DEF,
	IEEE_T_LCOL, IEEE_T_EXCOL, IEEE_T_MACERR, IEEE_T_CSERR, IEEE_T_SQE,
	IEEE_T_FDXFC, IEEE_T_OCTETS_OK,
	RMON_R_PACKETS, RMON_R_BC_PKT, RMON_R_MC_PKT, RMON_R_CRC_ALIGN,
	RMON_R_UNDERSIZE, RMON_R_OVERSIZE, RMON_R_FRAG, RMON_R_JAB,
	RMON_R_RESVD_O, RMON_R_P64, RMON_R_P65TO127, RMON_R_P128TO255,
	RMON_R_P256TO511, RMON_R_P512TO1023, RMON_R_P1024TO2047,
	RMON_R_P_GTE2048, RMON_R_OCTETS,
	IEEE_R_DROP, IEEE_R_FRAME_OK, IEEE_R_CRC, IEEE_R_ALIGN, IEEE_R_MACERR,
	IEEE_R_FDXFC, IEEE_R_OCTETS_OK
पूर्ण;
#अन्यथा
अटल __u32 fec_enet_रेजिस्टर_version = 1;
अटल u32 fec_enet_रेजिस्टर_offset[] = अणु
	FEC_ECNTRL, FEC_IEVENT, FEC_IMASK, FEC_IVEC, FEC_R_DES_ACTIVE_0,
	FEC_R_DES_ACTIVE_1, FEC_R_DES_ACTIVE_2, FEC_X_DES_ACTIVE_0,
	FEC_X_DES_ACTIVE_1, FEC_X_DES_ACTIVE_2, FEC_MII_DATA, FEC_MII_SPEED,
	FEC_R_BOUND, FEC_R_FSTART, FEC_X_WMRK, FEC_X_FSTART, FEC_R_CNTRL,
	FEC_MAX_FRM_LEN, FEC_X_CNTRL, FEC_ADDR_LOW, FEC_ADDR_HIGH,
	FEC_GRP_HASH_TABLE_HIGH, FEC_GRP_HASH_TABLE_LOW, FEC_R_DES_START_0,
	FEC_R_DES_START_1, FEC_R_DES_START_2, FEC_X_DES_START_0,
	FEC_X_DES_START_1, FEC_X_DES_START_2, FEC_R_BUFF_SIZE_0,
	FEC_R_BUFF_SIZE_1, FEC_R_BUFF_SIZE_2
पूर्ण;
#पूर्ण_अगर

अटल व्योम fec_enet_get_regs(काष्ठा net_device *ndev,
			      काष्ठा ethtool_regs *regs, व्योम *regbuf)
अणु
	काष्ठा fec_enet_निजी *fep = netdev_priv(ndev);
	u32 __iomem *theregs = (u32 __iomem *)fep->hwp;
	काष्ठा device *dev = &fep->pdev->dev;
	u32 *buf = (u32 *)regbuf;
	u32 i, off;
	पूर्णांक ret;

	ret = pm_runसमय_resume_and_get(dev);
	अगर (ret < 0)
		वापस;

	regs->version = fec_enet_रेजिस्टर_version;

	स_रखो(buf, 0, regs->len);

	क्रम (i = 0; i < ARRAY_SIZE(fec_enet_रेजिस्टर_offset); i++) अणु
		off = fec_enet_रेजिस्टर_offset[i];

		अगर ((off == FEC_R_BOUND || off == FEC_R_FSTART) &&
		    !(fep->quirks & FEC_QUIRK_HAS_FRREG))
			जारी;

		off >>= 2;
		buf[off] = पढ़ोl(&theregs[off]);
	पूर्ण

	pm_runसमय_mark_last_busy(dev);
	pm_runसमय_put_स्वतःsuspend(dev);
पूर्ण

अटल पूर्णांक fec_enet_get_ts_info(काष्ठा net_device *ndev,
				काष्ठा ethtool_ts_info *info)
अणु
	काष्ठा fec_enet_निजी *fep = netdev_priv(ndev);

	अगर (fep->bufdesc_ex) अणु

		info->so_बारtamping = SOF_TIMESTAMPING_TX_SOFTWARE |
					SOF_TIMESTAMPING_RX_SOFTWARE |
					SOF_TIMESTAMPING_SOFTWARE |
					SOF_TIMESTAMPING_TX_HARDWARE |
					SOF_TIMESTAMPING_RX_HARDWARE |
					SOF_TIMESTAMPING_RAW_HARDWARE;
		अगर (fep->ptp_घड़ी)
			info->phc_index = ptp_घड़ी_index(fep->ptp_घड़ी);
		अन्यथा
			info->phc_index = -1;

		info->tx_types = (1 << HWTSTAMP_TX_OFF) |
				 (1 << HWTSTAMP_TX_ON);

		info->rx_filters = (1 << HWTSTAMP_FILTER_NONE) |
				   (1 << HWTSTAMP_FILTER_ALL);
		वापस 0;
	पूर्ण अन्यथा अणु
		वापस ethtool_op_get_ts_info(ndev, info);
	पूर्ण
पूर्ण

#अगर !defined(CONFIG_M5272)

अटल व्योम fec_enet_get_छोड़ोparam(काष्ठा net_device *ndev,
				    काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
	काष्ठा fec_enet_निजी *fep = netdev_priv(ndev);

	छोड़ो->स्वतःneg = (fep->छोड़ो_flag & FEC_PAUSE_FLAG_AUTONEG) != 0;
	छोड़ो->tx_छोड़ो = (fep->छोड़ो_flag & FEC_PAUSE_FLAG_ENABLE) != 0;
	छोड़ो->rx_छोड़ो = छोड़ो->tx_छोड़ो;
पूर्ण

अटल पूर्णांक fec_enet_set_छोड़ोparam(काष्ठा net_device *ndev,
				   काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
	काष्ठा fec_enet_निजी *fep = netdev_priv(ndev);

	अगर (!ndev->phydev)
		वापस -ENODEV;

	अगर (छोड़ो->tx_छोड़ो != छोड़ो->rx_छोड़ो) अणु
		netdev_info(ndev,
			"hardware only support enable/disable both tx and rx");
		वापस -EINVAL;
	पूर्ण

	fep->छोड़ो_flag = 0;

	/* tx छोड़ो must be same as rx छोड़ो */
	fep->छोड़ो_flag |= छोड़ो->rx_छोड़ो ? FEC_PAUSE_FLAG_ENABLE : 0;
	fep->छोड़ो_flag |= छोड़ो->स्वतःneg ? FEC_PAUSE_FLAG_AUTONEG : 0;

	phy_set_sym_छोड़ो(ndev->phydev, छोड़ो->rx_छोड़ो, छोड़ो->tx_छोड़ो,
			  छोड़ो->स्वतःneg);

	अगर (छोड़ो->स्वतःneg) अणु
		अगर (netअगर_running(ndev))
			fec_stop(ndev);
		phy_start_aneg(ndev->phydev);
	पूर्ण
	अगर (netअगर_running(ndev)) अणु
		napi_disable(&fep->napi);
		netअगर_tx_lock_bh(ndev);
		fec_restart(ndev);
		netअगर_tx_wake_all_queues(ndev);
		netअगर_tx_unlock_bh(ndev);
		napi_enable(&fep->napi);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा fec_stat अणु
	अक्षर name[ETH_GSTRING_LEN];
	u16 offset;
पूर्ण fec_stats[] = अणु
	/* RMON TX */
	अणु "tx_dropped", RMON_T_DROP पूर्ण,
	अणु "tx_packets", RMON_T_PACKETS पूर्ण,
	अणु "tx_broadcast", RMON_T_BC_PKT पूर्ण,
	अणु "tx_multicast", RMON_T_MC_PKT पूर्ण,
	अणु "tx_crc_errors", RMON_T_CRC_ALIGN पूर्ण,
	अणु "tx_undersize", RMON_T_UNDERSIZE पूर्ण,
	अणु "tx_oversize", RMON_T_OVERSIZE पूर्ण,
	अणु "tx_fragment", RMON_T_FRAG पूर्ण,
	अणु "tx_jabber", RMON_T_JAB पूर्ण,
	अणु "tx_collision", RMON_T_COL पूर्ण,
	अणु "tx_64byte", RMON_T_P64 पूर्ण,
	अणु "tx_65to127byte", RMON_T_P65TO127 पूर्ण,
	अणु "tx_128to255byte", RMON_T_P128TO255 पूर्ण,
	अणु "tx_256to511byte", RMON_T_P256TO511 पूर्ण,
	अणु "tx_512to1023byte", RMON_T_P512TO1023 पूर्ण,
	अणु "tx_1024to2047byte", RMON_T_P1024TO2047 पूर्ण,
	अणु "tx_GTE2048byte", RMON_T_P_GTE2048 पूर्ण,
	अणु "tx_octets", RMON_T_OCTETS पूर्ण,

	/* IEEE TX */
	अणु "IEEE_tx_drop", IEEE_T_DROP पूर्ण,
	अणु "IEEE_tx_frame_ok", IEEE_T_FRAME_OK पूर्ण,
	अणु "IEEE_tx_1col", IEEE_T_1COL पूर्ण,
	अणु "IEEE_tx_mcol", IEEE_T_MCOL पूर्ण,
	अणु "IEEE_tx_def", IEEE_T_DEF पूर्ण,
	अणु "IEEE_tx_lcol", IEEE_T_LCOL पूर्ण,
	अणु "IEEE_tx_excol", IEEE_T_EXCOL पूर्ण,
	अणु "IEEE_tx_macerr", IEEE_T_MACERR पूर्ण,
	अणु "IEEE_tx_cserr", IEEE_T_CSERR पूर्ण,
	अणु "IEEE_tx_sqe", IEEE_T_SQE पूर्ण,
	अणु "IEEE_tx_fdxfc", IEEE_T_FDXFC पूर्ण,
	अणु "IEEE_tx_octets_ok", IEEE_T_OCTETS_OK पूर्ण,

	/* RMON RX */
	अणु "rx_packets", RMON_R_PACKETS पूर्ण,
	अणु "rx_broadcast", RMON_R_BC_PKT पूर्ण,
	अणु "rx_multicast", RMON_R_MC_PKT पूर्ण,
	अणु "rx_crc_errors", RMON_R_CRC_ALIGN पूर्ण,
	अणु "rx_undersize", RMON_R_UNDERSIZE पूर्ण,
	अणु "rx_oversize", RMON_R_OVERSIZE पूर्ण,
	अणु "rx_fragment", RMON_R_FRAG पूर्ण,
	अणु "rx_jabber", RMON_R_JAB पूर्ण,
	अणु "rx_64byte", RMON_R_P64 पूर्ण,
	अणु "rx_65to127byte", RMON_R_P65TO127 पूर्ण,
	अणु "rx_128to255byte", RMON_R_P128TO255 पूर्ण,
	अणु "rx_256to511byte", RMON_R_P256TO511 पूर्ण,
	अणु "rx_512to1023byte", RMON_R_P512TO1023 पूर्ण,
	अणु "rx_1024to2047byte", RMON_R_P1024TO2047 पूर्ण,
	अणु "rx_GTE2048byte", RMON_R_P_GTE2048 पूर्ण,
	अणु "rx_octets", RMON_R_OCTETS पूर्ण,

	/* IEEE RX */
	अणु "IEEE_rx_drop", IEEE_R_DROP पूर्ण,
	अणु "IEEE_rx_frame_ok", IEEE_R_FRAME_OK पूर्ण,
	अणु "IEEE_rx_crc", IEEE_R_CRC पूर्ण,
	अणु "IEEE_rx_align", IEEE_R_ALIGN पूर्ण,
	अणु "IEEE_rx_macerr", IEEE_R_MACERR पूर्ण,
	अणु "IEEE_rx_fdxfc", IEEE_R_FDXFC पूर्ण,
	अणु "IEEE_rx_octets_ok", IEEE_R_OCTETS_OK पूर्ण,
पूर्ण;

#घोषणा FEC_STATS_SIZE		(ARRAY_SIZE(fec_stats) * माप(u64))

अटल व्योम fec_enet_update_ethtool_stats(काष्ठा net_device *dev)
अणु
	काष्ठा fec_enet_निजी *fep = netdev_priv(dev);
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(fec_stats); i++)
		fep->ethtool_stats[i] = पढ़ोl(fep->hwp + fec_stats[i].offset);
पूर्ण

अटल व्योम fec_enet_get_ethtool_stats(काष्ठा net_device *dev,
				       काष्ठा ethtool_stats *stats, u64 *data)
अणु
	काष्ठा fec_enet_निजी *fep = netdev_priv(dev);

	अगर (netअगर_running(dev))
		fec_enet_update_ethtool_stats(dev);

	स_नकल(data, fep->ethtool_stats, FEC_STATS_SIZE);
पूर्ण

अटल व्योम fec_enet_get_strings(काष्ठा net_device *netdev,
	u32 stringset, u8 *data)
अणु
	पूर्णांक i;
	चयन (stringset) अणु
	हाल ETH_SS_STATS:
		क्रम (i = 0; i < ARRAY_SIZE(fec_stats); i++)
			स_नकल(data + i * ETH_GSTRING_LEN,
				fec_stats[i].name, ETH_GSTRING_LEN);
		अवरोध;
	हाल ETH_SS_TEST:
		net_selftest_get_strings(data);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक fec_enet_get_sset_count(काष्ठा net_device *dev, पूर्णांक sset)
अणु
	चयन (sset) अणु
	हाल ETH_SS_STATS:
		वापस ARRAY_SIZE(fec_stats);
	हाल ETH_SS_TEST:
		वापस net_selftest_get_count();
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल व्योम fec_enet_clear_ethtool_stats(काष्ठा net_device *dev)
अणु
	काष्ठा fec_enet_निजी *fep = netdev_priv(dev);
	पूर्णांक i;

	/* Disable MIB statistics counters */
	ग_लिखोl(FEC_MIB_CTRLSTAT_DISABLE, fep->hwp + FEC_MIB_CTRLSTAT);

	क्रम (i = 0; i < ARRAY_SIZE(fec_stats); i++)
		ग_लिखोl(0, fep->hwp + fec_stats[i].offset);

	/* Don't disable MIB statistics counters */
	ग_लिखोl(0, fep->hwp + FEC_MIB_CTRLSTAT);
पूर्ण

#अन्यथा	/* !defined(CONFIG_M5272) */
#घोषणा FEC_STATS_SIZE	0
अटल अंतरभूत व्योम fec_enet_update_ethtool_stats(काष्ठा net_device *dev)
अणु
पूर्ण

अटल अंतरभूत व्योम fec_enet_clear_ethtool_stats(काष्ठा net_device *dev)
अणु
पूर्ण
#पूर्ण_अगर /* !defined(CONFIG_M5272) */

/* ITR घड़ी source is enet प्रणाली घड़ी (clk_ahb).
 * TCTT unit is cycle_ns * 64 cycle
 * So, the ICTT value = X us / (cycle_ns * 64)
 */
अटल पूर्णांक fec_enet_us_to_itr_घड़ी(काष्ठा net_device *ndev, पूर्णांक us)
अणु
	काष्ठा fec_enet_निजी *fep = netdev_priv(ndev);

	वापस us * (fep->itr_clk_rate / 64000) / 1000;
पूर्ण

/* Set threshold क्रम पूर्णांकerrupt coalescing */
अटल व्योम fec_enet_itr_coal_set(काष्ठा net_device *ndev)
अणु
	काष्ठा fec_enet_निजी *fep = netdev_priv(ndev);
	पूर्णांक rx_itr, tx_itr;

	/* Must be greater than zero to aव्योम unpredictable behavior */
	अगर (!fep->rx_समय_itr || !fep->rx_pkts_itr ||
	    !fep->tx_समय_itr || !fep->tx_pkts_itr)
		वापस;

	/* Select enet प्रणाली घड़ी as Interrupt Coalescing
	 * समयr Clock Source
	 */
	rx_itr = FEC_ITR_CLK_SEL;
	tx_itr = FEC_ITR_CLK_SEL;

	/* set ICFT and ICTT */
	rx_itr |= FEC_ITR_ICFT(fep->rx_pkts_itr);
	rx_itr |= FEC_ITR_ICTT(fec_enet_us_to_itr_घड़ी(ndev, fep->rx_समय_itr));
	tx_itr |= FEC_ITR_ICFT(fep->tx_pkts_itr);
	tx_itr |= FEC_ITR_ICTT(fec_enet_us_to_itr_घड़ी(ndev, fep->tx_समय_itr));

	rx_itr |= FEC_ITR_EN;
	tx_itr |= FEC_ITR_EN;

	ग_लिखोl(tx_itr, fep->hwp + FEC_TXIC0);
	ग_लिखोl(rx_itr, fep->hwp + FEC_RXIC0);
	अगर (fep->quirks & FEC_QUIRK_HAS_AVB) अणु
		ग_लिखोl(tx_itr, fep->hwp + FEC_TXIC1);
		ग_लिखोl(rx_itr, fep->hwp + FEC_RXIC1);
		ग_लिखोl(tx_itr, fep->hwp + FEC_TXIC2);
		ग_लिखोl(rx_itr, fep->hwp + FEC_RXIC2);
	पूर्ण
पूर्ण

अटल पूर्णांक
fec_enet_get_coalesce(काष्ठा net_device *ndev, काष्ठा ethtool_coalesce *ec)
अणु
	काष्ठा fec_enet_निजी *fep = netdev_priv(ndev);

	अगर (!(fep->quirks & FEC_QUIRK_HAS_COALESCE))
		वापस -EOPNOTSUPP;

	ec->rx_coalesce_usecs = fep->rx_समय_itr;
	ec->rx_max_coalesced_frames = fep->rx_pkts_itr;

	ec->tx_coalesce_usecs = fep->tx_समय_itr;
	ec->tx_max_coalesced_frames = fep->tx_pkts_itr;

	वापस 0;
पूर्ण

अटल पूर्णांक
fec_enet_set_coalesce(काष्ठा net_device *ndev, काष्ठा ethtool_coalesce *ec)
अणु
	काष्ठा fec_enet_निजी *fep = netdev_priv(ndev);
	काष्ठा device *dev = &fep->pdev->dev;
	अचिन्हित पूर्णांक cycle;

	अगर (!(fep->quirks & FEC_QUIRK_HAS_COALESCE))
		वापस -EOPNOTSUPP;

	अगर (ec->rx_max_coalesced_frames > 255) अणु
		dev_err(dev, "Rx coalesced frames exceed hardware limitation\n");
		वापस -EINVAL;
	पूर्ण

	अगर (ec->tx_max_coalesced_frames > 255) अणु
		dev_err(dev, "Tx coalesced frame exceed hardware limitation\n");
		वापस -EINVAL;
	पूर्ण

	cycle = fec_enet_us_to_itr_घड़ी(ndev, ec->rx_coalesce_usecs);
	अगर (cycle > 0xFFFF) अणु
		dev_err(dev, "Rx coalesced usec exceed hardware limitation\n");
		वापस -EINVAL;
	पूर्ण

	cycle = fec_enet_us_to_itr_घड़ी(ndev, ec->tx_coalesce_usecs);
	अगर (cycle > 0xFFFF) अणु
		dev_err(dev, "Tx coalesced usec exceed hardware limitation\n");
		वापस -EINVAL;
	पूर्ण

	fep->rx_समय_itr = ec->rx_coalesce_usecs;
	fep->rx_pkts_itr = ec->rx_max_coalesced_frames;

	fep->tx_समय_itr = ec->tx_coalesce_usecs;
	fep->tx_pkts_itr = ec->tx_max_coalesced_frames;

	fec_enet_itr_coal_set(ndev);

	वापस 0;
पूर्ण

अटल व्योम fec_enet_itr_coal_init(काष्ठा net_device *ndev)
अणु
	काष्ठा ethtool_coalesce ec;

	ec.rx_coalesce_usecs = FEC_ITR_ICTT_DEFAULT;
	ec.rx_max_coalesced_frames = FEC_ITR_ICFT_DEFAULT;

	ec.tx_coalesce_usecs = FEC_ITR_ICTT_DEFAULT;
	ec.tx_max_coalesced_frames = FEC_ITR_ICFT_DEFAULT;

	fec_enet_set_coalesce(ndev, &ec);
पूर्ण

अटल पूर्णांक fec_enet_get_tunable(काष्ठा net_device *netdev,
				स्थिर काष्ठा ethtool_tunable *tuna,
				व्योम *data)
अणु
	काष्ठा fec_enet_निजी *fep = netdev_priv(netdev);
	पूर्णांक ret = 0;

	चयन (tuna->id) अणु
	हाल ETHTOOL_RX_COPYBREAK:
		*(u32 *)data = fep->rx_copyअवरोध;
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक fec_enet_set_tunable(काष्ठा net_device *netdev,
				स्थिर काष्ठा ethtool_tunable *tuna,
				स्थिर व्योम *data)
अणु
	काष्ठा fec_enet_निजी *fep = netdev_priv(netdev);
	पूर्णांक ret = 0;

	चयन (tuna->id) अणु
	हाल ETHTOOL_RX_COPYBREAK:
		fep->rx_copyअवरोध = *(u32 *)data;
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम
fec_enet_get_wol(काष्ठा net_device *ndev, काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा fec_enet_निजी *fep = netdev_priv(ndev);

	अगर (fep->wol_flag & FEC_WOL_HAS_MAGIC_PACKET) अणु
		wol->supported = WAKE_MAGIC;
		wol->wolopts = fep->wol_flag & FEC_WOL_FLAG_ENABLE ? WAKE_MAGIC : 0;
	पूर्ण अन्यथा अणु
		wol->supported = wol->wolopts = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक
fec_enet_set_wol(काष्ठा net_device *ndev, काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा fec_enet_निजी *fep = netdev_priv(ndev);

	अगर (!(fep->wol_flag & FEC_WOL_HAS_MAGIC_PACKET))
		वापस -EINVAL;

	अगर (wol->wolopts & ~WAKE_MAGIC)
		वापस -EINVAL;

	device_set_wakeup_enable(&ndev->dev, wol->wolopts & WAKE_MAGIC);
	अगर (device_may_wakeup(&ndev->dev)) अणु
		fep->wol_flag |= FEC_WOL_FLAG_ENABLE;
		अगर (fep->irq[0] > 0)
			enable_irq_wake(fep->irq[0]);
	पूर्ण अन्यथा अणु
		fep->wol_flag &= (~FEC_WOL_FLAG_ENABLE);
		अगर (fep->irq[0] > 0)
			disable_irq_wake(fep->irq[0]);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops fec_enet_ethtool_ops = अणु
	.supported_coalesce_params = ETHTOOL_COALESCE_USECS |
				     ETHTOOL_COALESCE_MAX_FRAMES,
	.get_drvinfo		= fec_enet_get_drvinfo,
	.get_regs_len		= fec_enet_get_regs_len,
	.get_regs		= fec_enet_get_regs,
	.nway_reset		= phy_ethtool_nway_reset,
	.get_link		= ethtool_op_get_link,
	.get_coalesce		= fec_enet_get_coalesce,
	.set_coalesce		= fec_enet_set_coalesce,
#अगर_अघोषित CONFIG_M5272
	.get_छोड़ोparam		= fec_enet_get_छोड़ोparam,
	.set_छोड़ोparam		= fec_enet_set_छोड़ोparam,
	.get_strings		= fec_enet_get_strings,
	.get_ethtool_stats	= fec_enet_get_ethtool_stats,
	.get_sset_count		= fec_enet_get_sset_count,
#पूर्ण_अगर
	.get_ts_info		= fec_enet_get_ts_info,
	.get_tunable		= fec_enet_get_tunable,
	.set_tunable		= fec_enet_set_tunable,
	.get_wol		= fec_enet_get_wol,
	.set_wol		= fec_enet_set_wol,
	.get_link_ksettings	= phy_ethtool_get_link_ksettings,
	.set_link_ksettings	= phy_ethtool_set_link_ksettings,
	.self_test		= net_selftest,
पूर्ण;

अटल पूर्णांक fec_enet_ioctl(काष्ठा net_device *ndev, काष्ठा अगरreq *rq, पूर्णांक cmd)
अणु
	काष्ठा fec_enet_निजी *fep = netdev_priv(ndev);
	काष्ठा phy_device *phydev = ndev->phydev;

	अगर (!netअगर_running(ndev))
		वापस -EINVAL;

	अगर (!phydev)
		वापस -ENODEV;

	अगर (fep->bufdesc_ex) अणु
		bool use_fec_hwts = !phy_has_hwtstamp(phydev);

		अगर (cmd == SIOCSHWTSTAMP) अणु
			अगर (use_fec_hwts)
				वापस fec_ptp_set(ndev, rq);
			fec_ptp_disable_hwts(ndev);
		पूर्ण अन्यथा अगर (cmd == SIOCGHWTSTAMP) अणु
			अगर (use_fec_hwts)
				वापस fec_ptp_get(ndev, rq);
		पूर्ण
	पूर्ण

	वापस phy_mii_ioctl(phydev, rq, cmd);
पूर्ण

अटल व्योम fec_enet_मुक्त_buffers(काष्ठा net_device *ndev)
अणु
	काष्ठा fec_enet_निजी *fep = netdev_priv(ndev);
	अचिन्हित पूर्णांक i;
	काष्ठा sk_buff *skb;
	काष्ठा bufdesc	*bdp;
	काष्ठा fec_enet_priv_tx_q *txq;
	काष्ठा fec_enet_priv_rx_q *rxq;
	अचिन्हित पूर्णांक q;

	क्रम (q = 0; q < fep->num_rx_queues; q++) अणु
		rxq = fep->rx_queue[q];
		bdp = rxq->bd.base;
		क्रम (i = 0; i < rxq->bd.ring_size; i++) अणु
			skb = rxq->rx_skbuff[i];
			rxq->rx_skbuff[i] = शून्य;
			अगर (skb) अणु
				dma_unmap_single(&fep->pdev->dev,
						 fec32_to_cpu(bdp->cbd_bufaddr),
						 FEC_ENET_RX_FRSIZE - fep->rx_align,
						 DMA_FROM_DEVICE);
				dev_kमुक्त_skb(skb);
			पूर्ण
			bdp = fec_enet_get_nextdesc(bdp, &rxq->bd);
		पूर्ण
	पूर्ण

	क्रम (q = 0; q < fep->num_tx_queues; q++) अणु
		txq = fep->tx_queue[q];
		क्रम (i = 0; i < txq->bd.ring_size; i++) अणु
			kमुक्त(txq->tx_bounce[i]);
			txq->tx_bounce[i] = शून्य;
			skb = txq->tx_skbuff[i];
			txq->tx_skbuff[i] = शून्य;
			dev_kमुक्त_skb(skb);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम fec_enet_मुक्त_queue(काष्ठा net_device *ndev)
अणु
	काष्ठा fec_enet_निजी *fep = netdev_priv(ndev);
	पूर्णांक i;
	काष्ठा fec_enet_priv_tx_q *txq;

	क्रम (i = 0; i < fep->num_tx_queues; i++)
		अगर (fep->tx_queue[i] && fep->tx_queue[i]->tso_hdrs) अणु
			txq = fep->tx_queue[i];
			dma_मुक्त_coherent(&fep->pdev->dev,
					  txq->bd.ring_size * TSO_HEADER_SIZE,
					  txq->tso_hdrs,
					  txq->tso_hdrs_dma);
		पूर्ण

	क्रम (i = 0; i < fep->num_rx_queues; i++)
		kमुक्त(fep->rx_queue[i]);
	क्रम (i = 0; i < fep->num_tx_queues; i++)
		kमुक्त(fep->tx_queue[i]);
पूर्ण

अटल पूर्णांक fec_enet_alloc_queue(काष्ठा net_device *ndev)
अणु
	काष्ठा fec_enet_निजी *fep = netdev_priv(ndev);
	पूर्णांक i;
	पूर्णांक ret = 0;
	काष्ठा fec_enet_priv_tx_q *txq;

	क्रम (i = 0; i < fep->num_tx_queues; i++) अणु
		txq = kzalloc(माप(*txq), GFP_KERNEL);
		अगर (!txq) अणु
			ret = -ENOMEM;
			जाओ alloc_failed;
		पूर्ण

		fep->tx_queue[i] = txq;
		txq->bd.ring_size = TX_RING_SIZE;
		fep->total_tx_ring_size += fep->tx_queue[i]->bd.ring_size;

		txq->tx_stop_threshold = FEC_MAX_SKB_DESCS;
		txq->tx_wake_threshold =
			(txq->bd.ring_size - txq->tx_stop_threshold) / 2;

		txq->tso_hdrs = dma_alloc_coherent(&fep->pdev->dev,
					txq->bd.ring_size * TSO_HEADER_SIZE,
					&txq->tso_hdrs_dma,
					GFP_KERNEL);
		अगर (!txq->tso_hdrs) अणु
			ret = -ENOMEM;
			जाओ alloc_failed;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < fep->num_rx_queues; i++) अणु
		fep->rx_queue[i] = kzalloc(माप(*fep->rx_queue[i]),
					   GFP_KERNEL);
		अगर (!fep->rx_queue[i]) अणु
			ret = -ENOMEM;
			जाओ alloc_failed;
		पूर्ण

		fep->rx_queue[i]->bd.ring_size = RX_RING_SIZE;
		fep->total_rx_ring_size += fep->rx_queue[i]->bd.ring_size;
	पूर्ण
	वापस ret;

alloc_failed:
	fec_enet_मुक्त_queue(ndev);
	वापस ret;
पूर्ण

अटल पूर्णांक
fec_enet_alloc_rxq_buffers(काष्ठा net_device *ndev, अचिन्हित पूर्णांक queue)
अणु
	काष्ठा fec_enet_निजी *fep = netdev_priv(ndev);
	अचिन्हित पूर्णांक i;
	काष्ठा sk_buff *skb;
	काष्ठा bufdesc	*bdp;
	काष्ठा fec_enet_priv_rx_q *rxq;

	rxq = fep->rx_queue[queue];
	bdp = rxq->bd.base;
	क्रम (i = 0; i < rxq->bd.ring_size; i++) अणु
		skb = netdev_alloc_skb(ndev, FEC_ENET_RX_FRSIZE);
		अगर (!skb)
			जाओ err_alloc;

		अगर (fec_enet_new_rxbdp(ndev, bdp, skb)) अणु
			dev_kमुक्त_skb(skb);
			जाओ err_alloc;
		पूर्ण

		rxq->rx_skbuff[i] = skb;
		bdp->cbd_sc = cpu_to_fec16(BD_ENET_RX_EMPTY);

		अगर (fep->bufdesc_ex) अणु
			काष्ठा bufdesc_ex *ebdp = (काष्ठा bufdesc_ex *)bdp;
			ebdp->cbd_esc = cpu_to_fec32(BD_ENET_RX_INT);
		पूर्ण

		bdp = fec_enet_get_nextdesc(bdp, &rxq->bd);
	पूर्ण

	/* Set the last buffer to wrap. */
	bdp = fec_enet_get_prevdesc(bdp, &rxq->bd);
	bdp->cbd_sc |= cpu_to_fec16(BD_SC_WRAP);
	वापस 0;

 err_alloc:
	fec_enet_मुक्त_buffers(ndev);
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक
fec_enet_alloc_txq_buffers(काष्ठा net_device *ndev, अचिन्हित पूर्णांक queue)
अणु
	काष्ठा fec_enet_निजी *fep = netdev_priv(ndev);
	अचिन्हित पूर्णांक i;
	काष्ठा bufdesc  *bdp;
	काष्ठा fec_enet_priv_tx_q *txq;

	txq = fep->tx_queue[queue];
	bdp = txq->bd.base;
	क्रम (i = 0; i < txq->bd.ring_size; i++) अणु
		txq->tx_bounce[i] = kदो_स्मृति(FEC_ENET_TX_FRSIZE, GFP_KERNEL);
		अगर (!txq->tx_bounce[i])
			जाओ err_alloc;

		bdp->cbd_sc = cpu_to_fec16(0);
		bdp->cbd_bufaddr = cpu_to_fec32(0);

		अगर (fep->bufdesc_ex) अणु
			काष्ठा bufdesc_ex *ebdp = (काष्ठा bufdesc_ex *)bdp;
			ebdp->cbd_esc = cpu_to_fec32(BD_ENET_TX_INT);
		पूर्ण

		bdp = fec_enet_get_nextdesc(bdp, &txq->bd);
	पूर्ण

	/* Set the last buffer to wrap. */
	bdp = fec_enet_get_prevdesc(bdp, &txq->bd);
	bdp->cbd_sc |= cpu_to_fec16(BD_SC_WRAP);

	वापस 0;

 err_alloc:
	fec_enet_मुक्त_buffers(ndev);
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक fec_enet_alloc_buffers(काष्ठा net_device *ndev)
अणु
	काष्ठा fec_enet_निजी *fep = netdev_priv(ndev);
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < fep->num_rx_queues; i++)
		अगर (fec_enet_alloc_rxq_buffers(ndev, i))
			वापस -ENOMEM;

	क्रम (i = 0; i < fep->num_tx_queues; i++)
		अगर (fec_enet_alloc_txq_buffers(ndev, i))
			वापस -ENOMEM;
	वापस 0;
पूर्ण

अटल पूर्णांक
fec_enet_खोलो(काष्ठा net_device *ndev)
अणु
	काष्ठा fec_enet_निजी *fep = netdev_priv(ndev);
	पूर्णांक ret;
	bool reset_again;

	ret = pm_runसमय_resume_and_get(&fep->pdev->dev);
	अगर (ret < 0)
		वापस ret;

	pinctrl_pm_select_शेष_state(&fep->pdev->dev);
	ret = fec_enet_clk_enable(ndev, true);
	अगर (ret)
		जाओ clk_enable;

	/* During the first fec_enet_खोलो call the PHY isn't probed at this
	 * poपूर्णांक. Thereक्रमe the phy_reset_after_clk_enable() call within
	 * fec_enet_clk_enable() fails. As we need this reset in order to be
	 * sure the PHY is working correctly we check अगर we need to reset again
	 * later when the PHY is probed
	 */
	अगर (ndev->phydev && ndev->phydev->drv)
		reset_again = false;
	अन्यथा
		reset_again = true;

	/* I should reset the ring buffers here, but I करोn't yet know
	 * a simple way to करो that.
	 */

	ret = fec_enet_alloc_buffers(ndev);
	अगर (ret)
		जाओ err_enet_alloc;

	/* Init MAC prior to mii bus probe */
	fec_restart(ndev);

	/* Call phy_reset_after_clk_enable() again अगर it failed during
	 * phy_reset_after_clk_enable() beक्रमe because the PHY wasn't probed.
	 */
	अगर (reset_again)
		fec_enet_phy_reset_after_clk_enable(ndev);

	/* Probe and connect to PHY when खोलो the पूर्णांकerface */
	ret = fec_enet_mii_probe(ndev);
	अगर (ret)
		जाओ err_enet_mii_probe;

	अगर (fep->quirks & FEC_QUIRK_ERR006687)
		imx6q_cpuidle_fec_irqs_used();

	napi_enable(&fep->napi);
	phy_start(ndev->phydev);
	netअगर_tx_start_all_queues(ndev);

	device_set_wakeup_enable(&ndev->dev, fep->wol_flag &
				 FEC_WOL_FLAG_ENABLE);

	वापस 0;

err_enet_mii_probe:
	fec_enet_मुक्त_buffers(ndev);
err_enet_alloc:
	fec_enet_clk_enable(ndev, false);
clk_enable:
	pm_runसमय_mark_last_busy(&fep->pdev->dev);
	pm_runसमय_put_स्वतःsuspend(&fep->pdev->dev);
	pinctrl_pm_select_sleep_state(&fep->pdev->dev);
	वापस ret;
पूर्ण

अटल पूर्णांक
fec_enet_बंद(काष्ठा net_device *ndev)
अणु
	काष्ठा fec_enet_निजी *fep = netdev_priv(ndev);

	phy_stop(ndev->phydev);

	अगर (netअगर_device_present(ndev)) अणु
		napi_disable(&fep->napi);
		netअगर_tx_disable(ndev);
		fec_stop(ndev);
	पूर्ण

	phy_disconnect(ndev->phydev);

	अगर (fep->quirks & FEC_QUIRK_ERR006687)
		imx6q_cpuidle_fec_irqs_unused();

	fec_enet_update_ethtool_stats(ndev);

	fec_enet_clk_enable(ndev, false);
	pinctrl_pm_select_sleep_state(&fep->pdev->dev);
	pm_runसमय_mark_last_busy(&fep->pdev->dev);
	pm_runसमय_put_स्वतःsuspend(&fep->pdev->dev);

	fec_enet_मुक्त_buffers(ndev);

	वापस 0;
पूर्ण

/* Set or clear the multicast filter क्रम this adaptor.
 * Skeleton taken from sunlance driver.
 * The CPM Ethernet implementation allows Multicast as well as inभागidual
 * MAC address filtering.  Some of the drivers check to make sure it is
 * a group multicast address, and discard those that are not.  I guess I
 * will करो the same क्रम now, but just हटाओ the test अगर you want
 * inभागidual filtering as well (करो the upper net layers want or support
 * this kind of feature?).
 */

#घोषणा FEC_HASH_BITS	6		/* #bits in hash */

अटल व्योम set_multicast_list(काष्ठा net_device *ndev)
अणु
	काष्ठा fec_enet_निजी *fep = netdev_priv(ndev);
	काष्ठा netdev_hw_addr *ha;
	अचिन्हित पूर्णांक crc, पंचांगp;
	अचिन्हित अक्षर hash;
	अचिन्हित पूर्णांक hash_high = 0, hash_low = 0;

	अगर (ndev->flags & IFF_PROMISC) अणु
		पंचांगp = पढ़ोl(fep->hwp + FEC_R_CNTRL);
		पंचांगp |= 0x8;
		ग_लिखोl(पंचांगp, fep->hwp + FEC_R_CNTRL);
		वापस;
	पूर्ण

	पंचांगp = पढ़ोl(fep->hwp + FEC_R_CNTRL);
	पंचांगp &= ~0x8;
	ग_लिखोl(पंचांगp, fep->hwp + FEC_R_CNTRL);

	अगर (ndev->flags & IFF_ALLMULTI) अणु
		/* Catch all multicast addresses, so set the
		 * filter to all 1's
		 */
		ग_लिखोl(0xffffffff, fep->hwp + FEC_GRP_HASH_TABLE_HIGH);
		ग_लिखोl(0xffffffff, fep->hwp + FEC_GRP_HASH_TABLE_LOW);

		वापस;
	पूर्ण

	/* Add the addresses in hash रेजिस्टर */
	netdev_क्रम_each_mc_addr(ha, ndev) अणु
		/* calculate crc32 value of mac address */
		crc = ether_crc_le(ndev->addr_len, ha->addr);

		/* only upper 6 bits (FEC_HASH_BITS) are used
		 * which poपूर्णांक to specअगरic bit in the hash रेजिस्टरs
		 */
		hash = (crc >> (32 - FEC_HASH_BITS)) & 0x3f;

		अगर (hash > 31)
			hash_high |= 1 << (hash - 32);
		अन्यथा
			hash_low |= 1 << hash;
	पूर्ण

	ग_लिखोl(hash_high, fep->hwp + FEC_GRP_HASH_TABLE_HIGH);
	ग_लिखोl(hash_low, fep->hwp + FEC_GRP_HASH_TABLE_LOW);
पूर्ण

/* Set a MAC change in hardware. */
अटल पूर्णांक
fec_set_mac_address(काष्ठा net_device *ndev, व्योम *p)
अणु
	काष्ठा fec_enet_निजी *fep = netdev_priv(ndev);
	काष्ठा sockaddr *addr = p;

	अगर (addr) अणु
		अगर (!is_valid_ether_addr(addr->sa_data))
			वापस -EADDRNOTAVAIL;
		स_नकल(ndev->dev_addr, addr->sa_data, ndev->addr_len);
	पूर्ण

	/* Add netअगर status check here to aव्योम प्रणाली hang in below हाल:
	 * अगरconfig ethx करोwn; अगरconfig ethx hw ether xx:xx:xx:xx:xx:xx;
	 * After ethx करोwn, fec all घड़ीs are gated off and then रेजिस्टर
	 * access causes प्रणाली hang.
	 */
	अगर (!netअगर_running(ndev))
		वापस 0;

	ग_लिखोl(ndev->dev_addr[3] | (ndev->dev_addr[2] << 8) |
		(ndev->dev_addr[1] << 16) | (ndev->dev_addr[0] << 24),
		fep->hwp + FEC_ADDR_LOW);
	ग_लिखोl((ndev->dev_addr[5] << 16) | (ndev->dev_addr[4] << 24),
		fep->hwp + FEC_ADDR_HIGH);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
/**
 * fec_poll_controller - FEC Poll controller function
 * @dev: The FEC network adapter
 *
 * Polled functionality used by netconsole and others in non पूर्णांकerrupt mode
 *
 */
अटल व्योम fec_poll_controller(काष्ठा net_device *dev)
अणु
	पूर्णांक i;
	काष्ठा fec_enet_निजी *fep = netdev_priv(dev);

	क्रम (i = 0; i < FEC_IRQ_NUM; i++) अणु
		अगर (fep->irq[i] > 0) अणु
			disable_irq(fep->irq[i]);
			fec_enet_पूर्णांकerrupt(fep->irq[i], dev);
			enable_irq(fep->irq[i]);
		पूर्ण
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत व्योम fec_enet_set_netdev_features(काष्ठा net_device *netdev,
	netdev_features_t features)
अणु
	काष्ठा fec_enet_निजी *fep = netdev_priv(netdev);
	netdev_features_t changed = features ^ netdev->features;

	netdev->features = features;

	/* Receive checksum has been changed */
	अगर (changed & NETIF_F_RXCSUM) अणु
		अगर (features & NETIF_F_RXCSUM)
			fep->csum_flags |= FLAG_RX_CSUM_ENABLED;
		अन्यथा
			fep->csum_flags &= ~FLAG_RX_CSUM_ENABLED;
	पूर्ण
पूर्ण

अटल पूर्णांक fec_set_features(काष्ठा net_device *netdev,
	netdev_features_t features)
अणु
	काष्ठा fec_enet_निजी *fep = netdev_priv(netdev);
	netdev_features_t changed = features ^ netdev->features;

	अगर (netअगर_running(netdev) && changed & NETIF_F_RXCSUM) अणु
		napi_disable(&fep->napi);
		netअगर_tx_lock_bh(netdev);
		fec_stop(netdev);
		fec_enet_set_netdev_features(netdev, features);
		fec_restart(netdev);
		netअगर_tx_wake_all_queues(netdev);
		netअगर_tx_unlock_bh(netdev);
		napi_enable(&fep->napi);
	पूर्ण अन्यथा अणु
		fec_enet_set_netdev_features(netdev, features);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा net_device_ops fec_netdev_ops = अणु
	.nकरो_खोलो		= fec_enet_खोलो,
	.nकरो_stop		= fec_enet_बंद,
	.nकरो_start_xmit		= fec_enet_start_xmit,
	.nकरो_set_rx_mode	= set_multicast_list,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_tx_समयout		= fec_समयout,
	.nकरो_set_mac_address	= fec_set_mac_address,
	.nकरो_करो_ioctl		= fec_enet_ioctl,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller	= fec_poll_controller,
#पूर्ण_अगर
	.nकरो_set_features	= fec_set_features,
पूर्ण;

अटल स्थिर अचिन्हित लघु offset_des_active_rxq[] = अणु
	FEC_R_DES_ACTIVE_0, FEC_R_DES_ACTIVE_1, FEC_R_DES_ACTIVE_2
पूर्ण;

अटल स्थिर अचिन्हित लघु offset_des_active_txq[] = अणु
	FEC_X_DES_ACTIVE_0, FEC_X_DES_ACTIVE_1, FEC_X_DES_ACTIVE_2
पूर्ण;

 /*
  * XXX:  We need to clean up on failure निकासs here.
  *
  */
अटल पूर्णांक fec_enet_init(काष्ठा net_device *ndev)
अणु
	काष्ठा fec_enet_निजी *fep = netdev_priv(ndev);
	काष्ठा bufdesc *cbd_base;
	dma_addr_t bd_dma;
	पूर्णांक bd_size;
	अचिन्हित पूर्णांक i;
	अचिन्हित dsize = fep->bufdesc_ex ? माप(काष्ठा bufdesc_ex) :
			माप(काष्ठा bufdesc);
	अचिन्हित dsize_log2 = __fls(dsize);
	पूर्णांक ret;

	WARN_ON(dsize != (1 << dsize_log2));
#अगर defined(CONFIG_ARM) || defined(CONFIG_ARM64)
	fep->rx_align = 0xf;
	fep->tx_align = 0xf;
#अन्यथा
	fep->rx_align = 0x3;
	fep->tx_align = 0x3;
#पूर्ण_अगर

	/* Check mask of the streaming and coherent API */
	ret = dma_set_mask_and_coherent(&fep->pdev->dev, DMA_BIT_MASK(32));
	अगर (ret < 0) अणु
		dev_warn(&fep->pdev->dev, "No suitable DMA available\n");
		वापस ret;
	पूर्ण

	ret = fec_enet_alloc_queue(ndev);
	अगर (ret)
		वापस ret;

	bd_size = (fep->total_tx_ring_size + fep->total_rx_ring_size) * dsize;

	/* Allocate memory क्रम buffer descriptors. */
	cbd_base = dmam_alloc_coherent(&fep->pdev->dev, bd_size, &bd_dma,
				       GFP_KERNEL);
	अगर (!cbd_base) अणु
		ret = -ENOMEM;
		जाओ मुक्त_queue_mem;
	पूर्ण

	/* Get the Ethernet address */
	ret = fec_get_mac(ndev);
	अगर (ret)
		जाओ मुक्त_queue_mem;

	/* make sure MAC we just acquired is programmed पूर्णांकo the hw */
	fec_set_mac_address(ndev, शून्य);

	/* Set receive and transmit descriptor base. */
	क्रम (i = 0; i < fep->num_rx_queues; i++) अणु
		काष्ठा fec_enet_priv_rx_q *rxq = fep->rx_queue[i];
		अचिन्हित size = dsize * rxq->bd.ring_size;

		rxq->bd.qid = i;
		rxq->bd.base = cbd_base;
		rxq->bd.cur = cbd_base;
		rxq->bd.dma = bd_dma;
		rxq->bd.dsize = dsize;
		rxq->bd.dsize_log2 = dsize_log2;
		rxq->bd.reg_desc_active = fep->hwp + offset_des_active_rxq[i];
		bd_dma += size;
		cbd_base = (काष्ठा bufdesc *)(((व्योम *)cbd_base) + size);
		rxq->bd.last = (काष्ठा bufdesc *)(((व्योम *)cbd_base) - dsize);
	पूर्ण

	क्रम (i = 0; i < fep->num_tx_queues; i++) अणु
		काष्ठा fec_enet_priv_tx_q *txq = fep->tx_queue[i];
		अचिन्हित size = dsize * txq->bd.ring_size;

		txq->bd.qid = i;
		txq->bd.base = cbd_base;
		txq->bd.cur = cbd_base;
		txq->bd.dma = bd_dma;
		txq->bd.dsize = dsize;
		txq->bd.dsize_log2 = dsize_log2;
		txq->bd.reg_desc_active = fep->hwp + offset_des_active_txq[i];
		bd_dma += size;
		cbd_base = (काष्ठा bufdesc *)(((व्योम *)cbd_base) + size);
		txq->bd.last = (काष्ठा bufdesc *)(((व्योम *)cbd_base) - dsize);
	पूर्ण


	/* The FEC Ethernet specअगरic entries in the device काष्ठाure */
	ndev->watchकरोg_समयo = TX_TIMEOUT;
	ndev->netdev_ops = &fec_netdev_ops;
	ndev->ethtool_ops = &fec_enet_ethtool_ops;

	ग_लिखोl(FEC_RX_DISABLED_IMASK, fep->hwp + FEC_IMASK);
	netअगर_napi_add(ndev, &fep->napi, fec_enet_rx_napi, NAPI_POLL_WEIGHT);

	अगर (fep->quirks & FEC_QUIRK_HAS_VLAN)
		/* enable hw VLAN support */
		ndev->features |= NETIF_F_HW_VLAN_CTAG_RX;

	अगर (fep->quirks & FEC_QUIRK_HAS_CSUM) अणु
		ndev->gso_max_segs = FEC_MAX_TSO_SEGS;

		/* enable hw accelerator */
		ndev->features |= (NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM
				| NETIF_F_RXCSUM | NETIF_F_SG | NETIF_F_TSO);
		fep->csum_flags |= FLAG_RX_CSUM_ENABLED;
	पूर्ण

	अगर (fep->quirks & FEC_QUIRK_HAS_AVB) अणु
		fep->tx_align = 0;
		fep->rx_align = 0x3f;
	पूर्ण

	ndev->hw_features = ndev->features;

	fec_restart(ndev);

	अगर (fep->quirks & FEC_QUIRK_MIB_CLEAR)
		fec_enet_clear_ethtool_stats(ndev);
	अन्यथा
		fec_enet_update_ethtool_stats(ndev);

	वापस 0;

मुक्त_queue_mem:
	fec_enet_मुक्त_queue(ndev);
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल पूर्णांक fec_reset_phy(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक err, phy_reset;
	bool active_high = false;
	पूर्णांक msec = 1, phy_post_delay = 0;
	काष्ठा device_node *np = pdev->dev.of_node;

	अगर (!np)
		वापस 0;

	err = of_property_पढ़ो_u32(np, "phy-reset-duration", &msec);
	/* A sane reset duration should not be दीर्घer than 1s */
	अगर (!err && msec > 1000)
		msec = 1;

	phy_reset = of_get_named_gpio(np, "phy-reset-gpios", 0);
	अगर (phy_reset == -EPROBE_DEFER)
		वापस phy_reset;
	अन्यथा अगर (!gpio_is_valid(phy_reset))
		वापस 0;

	err = of_property_पढ़ो_u32(np, "phy-reset-post-delay", &phy_post_delay);
	/* valid reset duration should be less than 1s */
	अगर (!err && phy_post_delay > 1000)
		वापस -EINVAL;

	active_high = of_property_पढ़ो_bool(np, "phy-reset-active-high");

	err = devm_gpio_request_one(&pdev->dev, phy_reset,
			active_high ? GPIOF_OUT_INIT_HIGH : GPIOF_OUT_INIT_LOW,
			"phy-reset");
	अगर (err) अणु
		dev_err(&pdev->dev, "failed to get phy-reset-gpios: %d\n", err);
		वापस err;
	पूर्ण

	अगर (msec > 20)
		msleep(msec);
	अन्यथा
		usleep_range(msec * 1000, msec * 1000 + 1000);

	gpio_set_value_cansleep(phy_reset, !active_high);

	अगर (!phy_post_delay)
		वापस 0;

	अगर (phy_post_delay > 20)
		msleep(phy_post_delay);
	अन्यथा
		usleep_range(phy_post_delay * 1000,
			     phy_post_delay * 1000 + 1000);

	वापस 0;
पूर्ण
#अन्यथा /* CONFIG_OF */
अटल पूर्णांक fec_reset_phy(काष्ठा platक्रमm_device *pdev)
अणु
	/*
	 * In हाल of platक्रमm probe, the reset has been करोne
	 * by machine code.
	 */
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_OF */

अटल व्योम
fec_enet_get_queue_num(काष्ठा platक्रमm_device *pdev, पूर्णांक *num_tx, पूर्णांक *num_rx)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;

	*num_tx = *num_rx = 1;

	अगर (!np || !of_device_is_available(np))
		वापस;

	/* parse the num of tx and rx queues */
	of_property_पढ़ो_u32(np, "fsl,num-tx-queues", num_tx);

	of_property_पढ़ो_u32(np, "fsl,num-rx-queues", num_rx);

	अगर (*num_tx < 1 || *num_tx > FEC_ENET_MAX_TX_QS) अणु
		dev_warn(&pdev->dev, "Invalid num_tx(=%d), fall back to 1\n",
			 *num_tx);
		*num_tx = 1;
		वापस;
	पूर्ण

	अगर (*num_rx < 1 || *num_rx > FEC_ENET_MAX_RX_QS) अणु
		dev_warn(&pdev->dev, "Invalid num_rx(=%d), fall back to 1\n",
			 *num_rx);
		*num_rx = 1;
		वापस;
	पूर्ण

पूर्ण

अटल पूर्णांक fec_enet_get_irq_cnt(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक irq_cnt = platक्रमm_irq_count(pdev);

	अगर (irq_cnt > FEC_IRQ_NUM)
		irq_cnt = FEC_IRQ_NUM;	/* last क्रम pps */
	अन्यथा अगर (irq_cnt == 2)
		irq_cnt = 1;	/* last क्रम pps */
	अन्यथा अगर (irq_cnt <= 0)
		irq_cnt = 1;	/* At least 1 irq is needed */
	वापस irq_cnt;
पूर्ण

अटल पूर्णांक fec_enet_init_stop_mode(काष्ठा fec_enet_निजी *fep,
				   काष्ठा device_node *np)
अणु
	काष्ठा device_node *gpr_np;
	u32 out_val[3];
	पूर्णांक ret = 0;

	gpr_np = of_parse_phandle(np, "fsl,stop-mode", 0);
	अगर (!gpr_np)
		वापस 0;

	ret = of_property_पढ़ो_u32_array(np, "fsl,stop-mode", out_val,
					 ARRAY_SIZE(out_val));
	अगर (ret) अणु
		dev_dbg(&fep->pdev->dev, "no stop mode property\n");
		वापस ret;
	पूर्ण

	fep->stop_gpr.gpr = syscon_node_to_regmap(gpr_np);
	अगर (IS_ERR(fep->stop_gpr.gpr)) अणु
		dev_err(&fep->pdev->dev, "could not find gpr regmap\n");
		ret = PTR_ERR(fep->stop_gpr.gpr);
		fep->stop_gpr.gpr = शून्य;
		जाओ out;
	पूर्ण

	fep->stop_gpr.reg = out_val[1];
	fep->stop_gpr.bit = out_val[2];

out:
	of_node_put(gpr_np);

	वापस ret;
पूर्ण

अटल पूर्णांक
fec_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा fec_enet_निजी *fep;
	काष्ठा fec_platक्रमm_data *pdata;
	phy_पूर्णांकerface_t पूर्णांकerface;
	काष्ठा net_device *ndev;
	पूर्णांक i, irq, ret = 0;
	स्थिर काष्ठा of_device_id *of_id;
	अटल पूर्णांक dev_id;
	काष्ठा device_node *np = pdev->dev.of_node, *phy_node;
	पूर्णांक num_tx_qs;
	पूर्णांक num_rx_qs;
	अक्षर irq_name[8];
	पूर्णांक irq_cnt;
	काष्ठा fec_devinfo *dev_info;

	fec_enet_get_queue_num(pdev, &num_tx_qs, &num_rx_qs);

	/* Init network device */
	ndev = alloc_etherdev_mqs(माप(काष्ठा fec_enet_निजी) +
				  FEC_STATS_SIZE, num_tx_qs, num_rx_qs);
	अगर (!ndev)
		वापस -ENOMEM;

	SET_NETDEV_DEV(ndev, &pdev->dev);

	/* setup board info काष्ठाure */
	fep = netdev_priv(ndev);

	of_id = of_match_device(fec_dt_ids, &pdev->dev);
	अगर (of_id)
		pdev->id_entry = of_id->data;
	dev_info = (काष्ठा fec_devinfo *)pdev->id_entry->driver_data;
	अगर (dev_info)
		fep->quirks = dev_info->quirks;

	fep->netdev = ndev;
	fep->num_rx_queues = num_rx_qs;
	fep->num_tx_queues = num_tx_qs;

#अगर !defined(CONFIG_M5272)
	/* शेष enable छोड़ो frame स्वतः negotiation */
	अगर (fep->quirks & FEC_QUIRK_HAS_GBIT)
		fep->छोड़ो_flag |= FEC_PAUSE_FLAG_AUTONEG;
#पूर्ण_अगर

	/* Select शेष pin state */
	pinctrl_pm_select_शेष_state(&pdev->dev);

	fep->hwp = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(fep->hwp)) अणु
		ret = PTR_ERR(fep->hwp);
		जाओ failed_ioremap;
	पूर्ण

	fep->pdev = pdev;
	fep->dev_id = dev_id++;

	platक्रमm_set_drvdata(pdev, ndev);

	अगर ((of_machine_is_compatible("fsl,imx6q") ||
	     of_machine_is_compatible("fsl,imx6dl")) &&
	    !of_property_पढ़ो_bool(np, "fsl,err006687-workaround-present"))
		fep->quirks |= FEC_QUIRK_ERR006687;

	अगर (of_get_property(np, "fsl,magic-packet", शून्य))
		fep->wol_flag |= FEC_WOL_HAS_MAGIC_PACKET;

	ret = fec_enet_init_stop_mode(fep, np);
	अगर (ret)
		जाओ failed_stop_mode;

	phy_node = of_parse_phandle(np, "phy-handle", 0);
	अगर (!phy_node && of_phy_is_fixed_link(np)) अणु
		ret = of_phy_रेजिस्टर_fixed_link(np);
		अगर (ret < 0) अणु
			dev_err(&pdev->dev,
				"broken fixed-link specification\n");
			जाओ failed_phy;
		पूर्ण
		phy_node = of_node_get(np);
	पूर्ण
	fep->phy_node = phy_node;

	ret = of_get_phy_mode(pdev->dev.of_node, &पूर्णांकerface);
	अगर (ret) अणु
		pdata = dev_get_platdata(&pdev->dev);
		अगर (pdata)
			fep->phy_पूर्णांकerface = pdata->phy;
		अन्यथा
			fep->phy_पूर्णांकerface = PHY_INTERFACE_MODE_MII;
	पूर्ण अन्यथा अणु
		fep->phy_पूर्णांकerface = पूर्णांकerface;
	पूर्ण

	fep->clk_ipg = devm_clk_get(&pdev->dev, "ipg");
	अगर (IS_ERR(fep->clk_ipg)) अणु
		ret = PTR_ERR(fep->clk_ipg);
		जाओ failed_clk;
	पूर्ण

	fep->clk_ahb = devm_clk_get(&pdev->dev, "ahb");
	अगर (IS_ERR(fep->clk_ahb)) अणु
		ret = PTR_ERR(fep->clk_ahb);
		जाओ failed_clk;
	पूर्ण

	fep->itr_clk_rate = clk_get_rate(fep->clk_ahb);

	/* enet_out is optional, depends on board */
	fep->clk_enet_out = devm_clk_get(&pdev->dev, "enet_out");
	अगर (IS_ERR(fep->clk_enet_out))
		fep->clk_enet_out = शून्य;

	fep->ptp_clk_on = false;
	mutex_init(&fep->ptp_clk_mutex);

	/* clk_ref is optional, depends on board */
	fep->clk_ref = devm_clk_get(&pdev->dev, "enet_clk_ref");
	अगर (IS_ERR(fep->clk_ref))
		fep->clk_ref = शून्य;

	fep->bufdesc_ex = fep->quirks & FEC_QUIRK_HAS_BUFDESC_EX;
	fep->clk_ptp = devm_clk_get(&pdev->dev, "ptp");
	अगर (IS_ERR(fep->clk_ptp)) अणु
		fep->clk_ptp = शून्य;
		fep->bufdesc_ex = false;
	पूर्ण

	ret = fec_enet_clk_enable(ndev, true);
	अगर (ret)
		जाओ failed_clk;

	ret = clk_prepare_enable(fep->clk_ipg);
	अगर (ret)
		जाओ failed_clk_ipg;
	ret = clk_prepare_enable(fep->clk_ahb);
	अगर (ret)
		जाओ failed_clk_ahb;

	fep->reg_phy = devm_regulator_get_optional(&pdev->dev, "phy");
	अगर (!IS_ERR(fep->reg_phy)) अणु
		ret = regulator_enable(fep->reg_phy);
		अगर (ret) अणु
			dev_err(&pdev->dev,
				"Failed to enable phy regulator: %d\n", ret);
			जाओ failed_regulator;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (PTR_ERR(fep->reg_phy) == -EPROBE_DEFER) अणु
			ret = -EPROBE_DEFER;
			जाओ failed_regulator;
		पूर्ण
		fep->reg_phy = शून्य;
	पूर्ण

	pm_runसमय_set_स्वतःsuspend_delay(&pdev->dev, FEC_MDIO_PM_TIMEOUT);
	pm_runसमय_use_स्वतःsuspend(&pdev->dev);
	pm_runसमय_get_noresume(&pdev->dev);
	pm_runसमय_set_active(&pdev->dev);
	pm_runसमय_enable(&pdev->dev);

	ret = fec_reset_phy(pdev);
	अगर (ret)
		जाओ failed_reset;

	irq_cnt = fec_enet_get_irq_cnt(pdev);
	अगर (fep->bufdesc_ex)
		fec_ptp_init(pdev, irq_cnt);

	ret = fec_enet_init(ndev);
	अगर (ret)
		जाओ failed_init;

	क्रम (i = 0; i < irq_cnt; i++) अणु
		snम_लिखो(irq_name, माप(irq_name), "int%d", i);
		irq = platक्रमm_get_irq_byname_optional(pdev, irq_name);
		अगर (irq < 0)
			irq = platक्रमm_get_irq(pdev, i);
		अगर (irq < 0) अणु
			ret = irq;
			जाओ failed_irq;
		पूर्ण
		ret = devm_request_irq(&pdev->dev, irq, fec_enet_पूर्णांकerrupt,
				       0, pdev->name, ndev);
		अगर (ret)
			जाओ failed_irq;

		fep->irq[i] = irq;
	पूर्ण

	ret = fec_enet_mii_init(pdev);
	अगर (ret)
		जाओ failed_mii_init;

	/* Carrier starts करोwn, phylib will bring it up */
	netअगर_carrier_off(ndev);
	fec_enet_clk_enable(ndev, false);
	pinctrl_pm_select_sleep_state(&pdev->dev);

	ndev->max_mtu = PKT_MAXBUF_SIZE - ETH_HLEN - ETH_FCS_LEN;

	ret = रेजिस्टर_netdev(ndev);
	अगर (ret)
		जाओ failed_रेजिस्टर;

	device_init_wakeup(&ndev->dev, fep->wol_flag &
			   FEC_WOL_HAS_MAGIC_PACKET);

	अगर (fep->bufdesc_ex && fep->ptp_घड़ी)
		netdev_info(ndev, "registered PHC device %d\n", fep->dev_id);

	fep->rx_copyअवरोध = COPYBREAK_DEFAULT;
	INIT_WORK(&fep->tx_समयout_work, fec_enet_समयout_work);

	pm_runसमय_mark_last_busy(&pdev->dev);
	pm_runसमय_put_स्वतःsuspend(&pdev->dev);

	वापस 0;

failed_रेजिस्टर:
	fec_enet_mii_हटाओ(fep);
failed_mii_init:
failed_irq:
failed_init:
	fec_ptp_stop(pdev);
failed_reset:
	pm_runसमय_put_noidle(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);
	अगर (fep->reg_phy)
		regulator_disable(fep->reg_phy);
failed_regulator:
	clk_disable_unprepare(fep->clk_ahb);
failed_clk_ahb:
	clk_disable_unprepare(fep->clk_ipg);
failed_clk_ipg:
	fec_enet_clk_enable(ndev, false);
failed_clk:
	अगर (of_phy_is_fixed_link(np))
		of_phy_deरेजिस्टर_fixed_link(np);
	of_node_put(phy_node);
failed_stop_mode:
failed_phy:
	dev_id--;
failed_ioremap:
	मुक्त_netdev(ndev);

	वापस ret;
पूर्ण

अटल पूर्णांक
fec_drv_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *ndev = platक्रमm_get_drvdata(pdev);
	काष्ठा fec_enet_निजी *fep = netdev_priv(ndev);
	काष्ठा device_node *np = pdev->dev.of_node;
	पूर्णांक ret;

	ret = pm_runसमय_resume_and_get(&pdev->dev);
	अगर (ret < 0)
		वापस ret;

	cancel_work_sync(&fep->tx_समयout_work);
	fec_ptp_stop(pdev);
	unरेजिस्टर_netdev(ndev);
	fec_enet_mii_हटाओ(fep);
	अगर (fep->reg_phy)
		regulator_disable(fep->reg_phy);

	अगर (of_phy_is_fixed_link(np))
		of_phy_deरेजिस्टर_fixed_link(np);
	of_node_put(fep->phy_node);
	मुक्त_netdev(ndev);

	clk_disable_unprepare(fep->clk_ahb);
	clk_disable_unprepare(fep->clk_ipg);
	pm_runसमय_put_noidle(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused fec_suspend(काष्ठा device *dev)
अणु
	काष्ठा net_device *ndev = dev_get_drvdata(dev);
	काष्ठा fec_enet_निजी *fep = netdev_priv(ndev);

	rtnl_lock();
	अगर (netअगर_running(ndev)) अणु
		अगर (fep->wol_flag & FEC_WOL_FLAG_ENABLE)
			fep->wol_flag |= FEC_WOL_FLAG_SLEEP_ON;
		phy_stop(ndev->phydev);
		napi_disable(&fep->napi);
		netअगर_tx_lock_bh(ndev);
		netअगर_device_detach(ndev);
		netअगर_tx_unlock_bh(ndev);
		fec_stop(ndev);
		fec_enet_clk_enable(ndev, false);
		अगर (!(fep->wol_flag & FEC_WOL_FLAG_ENABLE))
			pinctrl_pm_select_sleep_state(&fep->pdev->dev);
	पूर्ण
	rtnl_unlock();

	अगर (fep->reg_phy && !(fep->wol_flag & FEC_WOL_FLAG_ENABLE))
		regulator_disable(fep->reg_phy);

	/* SOC supply घड़ी to phy, when घड़ी is disabled, phy link करोwn
	 * SOC control phy regulator, when regulator is disabled, phy link करोwn
	 */
	अगर (fep->clk_enet_out || fep->reg_phy)
		fep->link = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused fec_resume(काष्ठा device *dev)
अणु
	काष्ठा net_device *ndev = dev_get_drvdata(dev);
	काष्ठा fec_enet_निजी *fep = netdev_priv(ndev);
	पूर्णांक ret;
	पूर्णांक val;

	अगर (fep->reg_phy && !(fep->wol_flag & FEC_WOL_FLAG_ENABLE)) अणु
		ret = regulator_enable(fep->reg_phy);
		अगर (ret)
			वापस ret;
	पूर्ण

	rtnl_lock();
	अगर (netअगर_running(ndev)) अणु
		ret = fec_enet_clk_enable(ndev, true);
		अगर (ret) अणु
			rtnl_unlock();
			जाओ failed_clk;
		पूर्ण
		अगर (fep->wol_flag & FEC_WOL_FLAG_ENABLE) अणु
			fec_enet_stop_mode(fep, false);

			val = पढ़ोl(fep->hwp + FEC_ECNTRL);
			val &= ~(FEC_ECR_MAGICEN | FEC_ECR_SLEEP);
			ग_लिखोl(val, fep->hwp + FEC_ECNTRL);
			fep->wol_flag &= ~FEC_WOL_FLAG_SLEEP_ON;
		पूर्ण अन्यथा अणु
			pinctrl_pm_select_शेष_state(&fep->pdev->dev);
		पूर्ण
		fec_restart(ndev);
		netअगर_tx_lock_bh(ndev);
		netअगर_device_attach(ndev);
		netअगर_tx_unlock_bh(ndev);
		napi_enable(&fep->napi);
		phy_init_hw(ndev->phydev);
		phy_start(ndev->phydev);
	पूर्ण
	rtnl_unlock();

	वापस 0;

failed_clk:
	अगर (fep->reg_phy)
		regulator_disable(fep->reg_phy);
	वापस ret;
पूर्ण

अटल पूर्णांक __maybe_unused fec_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा net_device *ndev = dev_get_drvdata(dev);
	काष्ठा fec_enet_निजी *fep = netdev_priv(ndev);

	clk_disable_unprepare(fep->clk_ahb);
	clk_disable_unprepare(fep->clk_ipg);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused fec_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा net_device *ndev = dev_get_drvdata(dev);
	काष्ठा fec_enet_निजी *fep = netdev_priv(ndev);
	पूर्णांक ret;

	ret = clk_prepare_enable(fep->clk_ahb);
	अगर (ret)
		वापस ret;
	ret = clk_prepare_enable(fep->clk_ipg);
	अगर (ret)
		जाओ failed_clk_ipg;

	वापस 0;

failed_clk_ipg:
	clk_disable_unprepare(fep->clk_ahb);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops fec_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(fec_suspend, fec_resume)
	SET_RUNTIME_PM_OPS(fec_runसमय_suspend, fec_runसमय_resume, शून्य)
पूर्ण;

अटल काष्ठा platक्रमm_driver fec_driver = अणु
	.driver	= अणु
		.name	= DRIVER_NAME,
		.pm	= &fec_pm_ops,
		.of_match_table = fec_dt_ids,
		.suppress_bind_attrs = true,
	पूर्ण,
	.id_table = fec_devtype,
	.probe	= fec_probe,
	.हटाओ	= fec_drv_हटाओ,
पूर्ण;

module_platक्रमm_driver(fec_driver);

MODULE_ALIAS("platform:"DRIVER_NAME);
MODULE_LICENSE("GPL");
