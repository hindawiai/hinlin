<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * PXA168 ethernet driver.
 * Most of the code is derived from mv643xx ethernet driver.
 *
 * Copyright (C) 2010 Marvell International Ltd.
 *		Sachin Sanap <ssanap@marvell.com>
 *		Zhangfei Gao <zgao6@marvell.com>
 *		Philip Rakity <prakity@marvell.com>
 *		Mark Brown <markb@marvell.com>
 */

#समावेश <linux/bitops.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/in.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/ip.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_net.h>
#समावेश <linux/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pxa168_eth.h>
#समावेश <linux/tcp.h>
#समावेश <linux/types.h>
#समावेश <linux/udp.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/pgtable.h>

#समावेश <यंत्र/cacheflush.h>

#घोषणा DRIVER_NAME	"pxa168-eth"
#घोषणा DRIVER_VERSION	"0.3"

/*
 * Registers
 */

#घोषणा PHY_ADDRESS		0x0000
#घोषणा SMI			0x0010
#घोषणा PORT_CONFIG		0x0400
#घोषणा PORT_CONFIG_EXT		0x0408
#घोषणा PORT_COMMAND		0x0410
#घोषणा PORT_STATUS		0x0418
#घोषणा HTPR			0x0428
#घोषणा MAC_ADDR_LOW		0x0430
#घोषणा MAC_ADDR_HIGH		0x0438
#घोषणा SDMA_CONFIG		0x0440
#घोषणा SDMA_CMD		0x0448
#घोषणा INT_CAUSE		0x0450
#घोषणा INT_W_CLEAR		0x0454
#घोषणा INT_MASK		0x0458
#घोषणा ETH_F_RX_DESC_0		0x0480
#घोषणा ETH_C_RX_DESC_0		0x04A0
#घोषणा ETH_C_TX_DESC_1		0x04E4

/* smi रेजिस्टर */
#घोषणा SMI_BUSY		(1 << 28)	/* 0 - Write, 1 - Read  */
#घोषणा SMI_R_VALID		(1 << 27)	/* 0 - Write, 1 - Read  */
#घोषणा SMI_OP_W		(0 << 26)	/* Write operation      */
#घोषणा SMI_OP_R		(1 << 26)	/* Read operation */

#घोषणा PHY_WAIT_ITERATIONS	10

#घोषणा PXA168_ETH_PHY_ADDR_DEFAULT	0
/* RX & TX descriptor command */
#घोषणा BUF_OWNED_BY_DMA	(1 << 31)

/* RX descriptor status */
#घोषणा RX_EN_INT		(1 << 23)
#घोषणा RX_FIRST_DESC		(1 << 17)
#घोषणा RX_LAST_DESC		(1 << 16)
#घोषणा RX_ERROR		(1 << 15)

/* TX descriptor command */
#घोषणा TX_EN_INT		(1 << 23)
#घोषणा TX_GEN_CRC		(1 << 22)
#घोषणा TX_ZERO_PADDING		(1 << 18)
#घोषणा TX_FIRST_DESC		(1 << 17)
#घोषणा TX_LAST_DESC		(1 << 16)
#घोषणा TX_ERROR		(1 << 15)

/* SDMA_CMD */
#घोषणा SDMA_CMD_AT		(1 << 31)
#घोषणा SDMA_CMD_TXDL		(1 << 24)
#घोषणा SDMA_CMD_TXDH		(1 << 23)
#घोषणा SDMA_CMD_AR		(1 << 15)
#घोषणा SDMA_CMD_ERD		(1 << 7)

/* Bit definitions of the Port Config Reg */
#घोषणा PCR_DUPLEX_FULL		(1 << 15)
#घोषणा PCR_HS			(1 << 12)
#घोषणा PCR_EN			(1 << 7)
#घोषणा PCR_PM			(1 << 0)

/* Bit definitions of the Port Config Extend Reg */
#घोषणा PCXR_2BSM		(1 << 28)
#घोषणा PCXR_DSCP_EN		(1 << 21)
#घोषणा PCXR_RMII_EN		(1 << 20)
#घोषणा PCXR_AN_SPEED_DIS	(1 << 19)
#घोषणा PCXR_SPEED_100		(1 << 18)
#घोषणा PCXR_MFL_1518		(0 << 14)
#घोषणा PCXR_MFL_1536		(1 << 14)
#घोषणा PCXR_MFL_2048		(2 << 14)
#घोषणा PCXR_MFL_64K		(3 << 14)
#घोषणा PCXR_FLOWCTL_DIS	(1 << 12)
#घोषणा PCXR_FLP		(1 << 11)
#घोषणा PCXR_AN_FLOWCTL_DIS	(1 << 10)
#घोषणा PCXR_AN_DUPLEX_DIS	(1 << 9)
#घोषणा PCXR_PRIO_TX_OFF	3
#घोषणा PCXR_TX_HIGH_PRI	(7 << PCXR_PRIO_TX_OFF)

/* Bit definitions of the SDMA Config Reg */
#घोषणा SDCR_BSZ_OFF		12
#घोषणा SDCR_BSZ8		(3 << SDCR_BSZ_OFF)
#घोषणा SDCR_BSZ4		(2 << SDCR_BSZ_OFF)
#घोषणा SDCR_BSZ2		(1 << SDCR_BSZ_OFF)
#घोषणा SDCR_BSZ1		(0 << SDCR_BSZ_OFF)
#घोषणा SDCR_BLMR		(1 << 6)
#घोषणा SDCR_BLMT		(1 << 7)
#घोषणा SDCR_RIFB		(1 << 9)
#घोषणा SDCR_RC_OFF		2
#घोषणा SDCR_RC_MAX_RETRANS	(0xf << SDCR_RC_OFF)

/*
 * Bit definitions of the Interrupt Cause Reg
 * and Interrupt MASK Reg is the same
 */
#घोषणा ICR_RXBUF		(1 << 0)
#घोषणा ICR_TXBUF_H		(1 << 2)
#घोषणा ICR_TXBUF_L		(1 << 3)
#घोषणा ICR_TXEND_H		(1 << 6)
#घोषणा ICR_TXEND_L		(1 << 7)
#घोषणा ICR_RXERR		(1 << 8)
#घोषणा ICR_TXERR_H		(1 << 10)
#घोषणा ICR_TXERR_L		(1 << 11)
#घोषणा ICR_TX_UDR		(1 << 13)
#घोषणा ICR_MII_CH		(1 << 28)

#घोषणा ALL_INTS (ICR_TXBUF_H  | ICR_TXBUF_L  | ICR_TX_UDR |\
				ICR_TXERR_H  | ICR_TXERR_L |\
				ICR_TXEND_H  | ICR_TXEND_L |\
				ICR_RXBUF | ICR_RXERR  | ICR_MII_CH)

#घोषणा ETH_HW_IP_ALIGN		2	/* hw aligns IP header */

#घोषणा NUM_RX_DESCS		64
#घोषणा NUM_TX_DESCS		64

#घोषणा HASH_ADD		0
#घोषणा HASH_DELETE		1
#घोषणा HASH_ADDR_TABLE_SIZE	0x4000	/* 16K (1/2K address - PCR_HS == 1) */
#घोषणा HOP_NUMBER		12

/* Bit definitions क्रम Port status */
#घोषणा PORT_SPEED_100		(1 << 0)
#घोषणा FULL_DUPLEX		(1 << 1)
#घोषणा FLOW_CONTROL_DISABLED	(1 << 2)
#घोषणा LINK_UP			(1 << 3)

/* Bit definitions क्रम work to be करोne */
#घोषणा WORK_TX_DONE		(1 << 1)

/*
 * Misc definitions.
 */
#घोषणा SKB_DMA_REALIGN		((PAGE_SIZE - NET_SKB_PAD) % SMP_CACHE_BYTES)

काष्ठा rx_desc अणु
	u32 cmd_sts;		/* Descriptor command status            */
	u16 byte_cnt;		/* Descriptor buffer byte count         */
	u16 buf_size;		/* Buffer size                          */
	u32 buf_ptr;		/* Descriptor buffer poपूर्णांकer            */
	u32 next_desc_ptr;	/* Next descriptor poपूर्णांकer              */
पूर्ण;

काष्ठा tx_desc अणु
	u32 cmd_sts;		/* Command/status field                 */
	u16 reserved;
	u16 byte_cnt;		/* buffer byte count                    */
	u32 buf_ptr;		/* poपूर्णांकer to buffer क्रम this descriptor */
	u32 next_desc_ptr;	/* Poपूर्णांकer to next descriptor           */
पूर्ण;

काष्ठा pxa168_eth_निजी अणु
	काष्ठा platक्रमm_device *pdev;
	पूर्णांक port_num;		/* User Ethernet port number    */
	पूर्णांक phy_addr;
	पूर्णांक phy_speed;
	पूर्णांक phy_duplex;
	phy_पूर्णांकerface_t phy_पूर्णांकf;

	पूर्णांक rx_resource_err;	/* Rx ring resource error flag */

	/* Next available and first वापसing Rx resource */
	पूर्णांक rx_curr_desc_q, rx_used_desc_q;

	/* Next available and first वापसing Tx resource */
	पूर्णांक tx_curr_desc_q, tx_used_desc_q;

	काष्ठा rx_desc *p_rx_desc_area;
	dma_addr_t rx_desc_dma;
	पूर्णांक rx_desc_area_size;
	काष्ठा sk_buff **rx_skb;

	काष्ठा tx_desc *p_tx_desc_area;
	dma_addr_t tx_desc_dma;
	पूर्णांक tx_desc_area_size;
	काष्ठा sk_buff **tx_skb;

	काष्ठा work_काष्ठा tx_समयout_task;

	काष्ठा net_device *dev;
	काष्ठा napi_काष्ठा napi;
	u8 work_toकरो;
	पूर्णांक skb_size;

	/* Size of Tx Ring per queue */
	पूर्णांक tx_ring_size;
	/* Number of tx descriptors in use */
	पूर्णांक tx_desc_count;
	/* Size of Rx Ring per queue */
	पूर्णांक rx_ring_size;
	/* Number of rx descriptors in use */
	पूर्णांक rx_desc_count;

	/*
	 * Used in हाल RX Ring is empty, which can occur when
	 * प्रणाली करोes not have resources (skb's)
	 */
	काष्ठा समयr_list समयout;
	काष्ठा mii_bus *smi_bus;

	/* घड़ी */
	काष्ठा clk *clk;
	काष्ठा pxa168_eth_platक्रमm_data *pd;
	/*
	 * Ethernet controller base address.
	 */
	व्योम __iomem *base;

	/* Poपूर्णांकer to the hardware address filter table */
	व्योम *htpr;
	dma_addr_t htpr_dma;
पूर्ण;

काष्ठा addr_table_entry अणु
	__le32 lo;
	__le32 hi;
पूर्ण;

/* Bit fields of a Hash Table Entry */
क्रमागत hash_table_entry अणु
	HASH_ENTRY_VALID = 1,
	SKIP = 2,
	HASH_ENTRY_RECEIVE_DISCARD = 4,
	HASH_ENTRY_RECEIVE_DISCARD_BIT = 2
पूर्ण;

अटल पूर्णांक pxa168_init_hw(काष्ठा pxa168_eth_निजी *pep);
अटल पूर्णांक pxa168_init_phy(काष्ठा net_device *dev);
अटल व्योम eth_port_reset(काष्ठा net_device *dev);
अटल व्योम eth_port_start(काष्ठा net_device *dev);
अटल पूर्णांक pxa168_eth_खोलो(काष्ठा net_device *dev);
अटल पूर्णांक pxa168_eth_stop(काष्ठा net_device *dev);

अटल अंतरभूत u32 rdl(काष्ठा pxa168_eth_निजी *pep, पूर्णांक offset)
अणु
	वापस पढ़ोl_relaxed(pep->base + offset);
पूर्ण

अटल अंतरभूत व्योम wrl(काष्ठा pxa168_eth_निजी *pep, पूर्णांक offset, u32 data)
अणु
	ग_लिखोl_relaxed(data, pep->base + offset);
पूर्ण

अटल व्योम पात_dma(काष्ठा pxa168_eth_निजी *pep)
अणु
	पूर्णांक delay;
	पूर्णांक max_retries = 40;

	करो अणु
		wrl(pep, SDMA_CMD, SDMA_CMD_AR | SDMA_CMD_AT);
		udelay(100);

		delay = 10;
		जबतक ((rdl(pep, SDMA_CMD) & (SDMA_CMD_AR | SDMA_CMD_AT))
		       && delay-- > 0) अणु
			udelay(10);
		पूर्ण
	पूर्ण जबतक (max_retries-- > 0 && delay <= 0);

	अगर (max_retries <= 0)
		netdev_err(pep->dev, "%s : DMA Stuck\n", __func__);
पूर्ण

अटल व्योम rxq_refill(काष्ठा net_device *dev)
अणु
	काष्ठा pxa168_eth_निजी *pep = netdev_priv(dev);
	काष्ठा sk_buff *skb;
	काष्ठा rx_desc *p_used_rx_desc;
	पूर्णांक used_rx_desc;

	जबतक (pep->rx_desc_count < pep->rx_ring_size) अणु
		पूर्णांक size;

		skb = netdev_alloc_skb(dev, pep->skb_size);
		अगर (!skb)
			अवरोध;
		अगर (SKB_DMA_REALIGN)
			skb_reserve(skb, SKB_DMA_REALIGN);
		pep->rx_desc_count++;
		/* Get 'used' Rx descriptor */
		used_rx_desc = pep->rx_used_desc_q;
		p_used_rx_desc = &pep->p_rx_desc_area[used_rx_desc];
		size = skb_end_poपूर्णांकer(skb) - skb->data;
		p_used_rx_desc->buf_ptr = dma_map_single(&pep->pdev->dev,
							 skb->data,
							 size,
							 DMA_FROM_DEVICE);
		p_used_rx_desc->buf_size = size;
		pep->rx_skb[used_rx_desc] = skb;

		/* Return the descriptor to DMA ownership */
		dma_wmb();
		p_used_rx_desc->cmd_sts = BUF_OWNED_BY_DMA | RX_EN_INT;
		dma_wmb();

		/* Move the used descriptor poपूर्णांकer to the next descriptor */
		pep->rx_used_desc_q = (used_rx_desc + 1) % pep->rx_ring_size;

		/* Any Rx वापस cancels the Rx resource error status */
		pep->rx_resource_err = 0;

		skb_reserve(skb, ETH_HW_IP_ALIGN);
	पूर्ण

	/*
	 * If RX ring is empty of SKB, set a समयr to try allocating
	 * again at a later समय.
	 */
	अगर (pep->rx_desc_count == 0) अणु
		pep->समयout.expires = jअगरfies + (HZ / 10);
		add_समयr(&pep->समयout);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम rxq_refill_समयr_wrapper(काष्ठा समयr_list *t)
अणु
	काष्ठा pxa168_eth_निजी *pep = from_समयr(pep, t, समयout);
	napi_schedule(&pep->napi);
पूर्ण

अटल अंतरभूत u8 flip_8_bits(u8 x)
अणु
	वापस (((x) & 0x01) << 3) | (((x) & 0x02) << 1)
	    | (((x) & 0x04) >> 1) | (((x) & 0x08) >> 3)
	    | (((x) & 0x10) << 3) | (((x) & 0x20) << 1)
	    | (((x) & 0x40) >> 1) | (((x) & 0x80) >> 3);
पूर्ण

अटल व्योम nibble_swap_every_byte(अचिन्हित अक्षर *mac_addr)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < ETH_ALEN; i++) अणु
		mac_addr[i] = ((mac_addr[i] & 0x0f) << 4) |
				((mac_addr[i] & 0xf0) >> 4);
	पूर्ण
पूर्ण

अटल व्योम inverse_every_nibble(अचिन्हित अक्षर *mac_addr)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < ETH_ALEN; i++)
		mac_addr[i] = flip_8_bits(mac_addr[i]);
पूर्ण

/*
 * ----------------------------------------------------------------------------
 * This function will calculate the hash function of the address.
 * Inमाला_दो
 * mac_addr_orig    - MAC address.
 * Outमाला_दो
 * वापस the calculated entry.
 */
अटल u32 hash_function(अचिन्हित अक्षर *mac_addr_orig)
अणु
	u32 hash_result;
	u32 addr0;
	u32 addr1;
	u32 addr2;
	u32 addr3;
	अचिन्हित अक्षर mac_addr[ETH_ALEN];

	/* Make a copy of MAC address since we are going to perक्रमme bit
	 * operations on it
	 */
	स_नकल(mac_addr, mac_addr_orig, ETH_ALEN);

	nibble_swap_every_byte(mac_addr);
	inverse_every_nibble(mac_addr);

	addr0 = (mac_addr[5] >> 2) & 0x3f;
	addr1 = (mac_addr[5] & 0x03) | (((mac_addr[4] & 0x7f)) << 2);
	addr2 = ((mac_addr[4] & 0x80) >> 7) | mac_addr[3] << 1;
	addr3 = (mac_addr[2] & 0xff) | ((mac_addr[1] & 1) << 8);

	hash_result = (addr0 << 9) | (addr1 ^ addr2 ^ addr3);
	hash_result = hash_result & 0x07ff;
	वापस hash_result;
पूर्ण

/*
 * ----------------------------------------------------------------------------
 * This function will add/del an entry to the address table.
 * Inमाला_दो
 * pep - ETHERNET .
 * mac_addr - MAC address.
 * skip - अगर 1, skip this address.Used in हाल of deleting an entry which is a
 *	  part of chain in the hash table.We can't just delete the entry since
 *	  that will अवरोध the chain.We need to defragment the tables समय to
 *	  समय.
 * rd   - 0 Discard packet upon match.
 *	- 1 Receive packet upon match.
 * Outमाला_दो
 * address table entry is added/deleted.
 * 0 अगर success.
 * -ENOSPC अगर table full
 */
अटल पूर्णांक add_del_hash_entry(काष्ठा pxa168_eth_निजी *pep,
			      अचिन्हित अक्षर *mac_addr,
			      u32 rd, u32 skip, पूर्णांक del)
अणु
	काष्ठा addr_table_entry *entry, *start;
	u32 new_high;
	u32 new_low;
	u32 i;

	new_low = (((mac_addr[1] >> 4) & 0xf) << 15)
	    | (((mac_addr[1] >> 0) & 0xf) << 11)
	    | (((mac_addr[0] >> 4) & 0xf) << 7)
	    | (((mac_addr[0] >> 0) & 0xf) << 3)
	    | (((mac_addr[3] >> 4) & 0x1) << 31)
	    | (((mac_addr[3] >> 0) & 0xf) << 27)
	    | (((mac_addr[2] >> 4) & 0xf) << 23)
	    | (((mac_addr[2] >> 0) & 0xf) << 19)
	    | (skip << SKIP) | (rd << HASH_ENTRY_RECEIVE_DISCARD_BIT)
	    | HASH_ENTRY_VALID;

	new_high = (((mac_addr[5] >> 4) & 0xf) << 15)
	    | (((mac_addr[5] >> 0) & 0xf) << 11)
	    | (((mac_addr[4] >> 4) & 0xf) << 7)
	    | (((mac_addr[4] >> 0) & 0xf) << 3)
	    | (((mac_addr[3] >> 5) & 0x7) << 0);

	/*
	 * Pick the appropriate table, start scanning क्रम मुक्त/reusable
	 * entries at the index obtained by hashing the specअगरied MAC address
	 */
	start = pep->htpr;
	entry = start + hash_function(mac_addr);
	क्रम (i = 0; i < HOP_NUMBER; i++) अणु
		अगर (!(le32_to_cpu(entry->lo) & HASH_ENTRY_VALID)) अणु
			अवरोध;
		पूर्ण अन्यथा अणु
			/* अगर same address put in same position */
			अगर (((le32_to_cpu(entry->lo) & 0xfffffff8) ==
				(new_low & 0xfffffff8)) &&
				(le32_to_cpu(entry->hi) == new_high)) अणु
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (entry == start + 0x7ff)
			entry = start;
		अन्यथा
			entry++;
	पूर्ण

	अगर (((le32_to_cpu(entry->lo) & 0xfffffff8) != (new_low & 0xfffffff8)) &&
	    (le32_to_cpu(entry->hi) != new_high) && del)
		वापस 0;

	अगर (i == HOP_NUMBER) अणु
		अगर (!del) अणु
			netdev_info(pep->dev,
				    "%s: table section is full, need to "
				    "move to 16kB implementation?\n",
				    __खाता__);
			वापस -ENOSPC;
		पूर्ण अन्यथा
			वापस 0;
	पूर्ण

	/*
	 * Update the selected entry
	 */
	अगर (del) अणु
		entry->hi = 0;
		entry->lo = 0;
	पूर्ण अन्यथा अणु
		entry->hi = cpu_to_le32(new_high);
		entry->lo = cpu_to_le32(new_low);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * ----------------------------------------------------------------------------
 *  Create an addressTable entry from MAC address info
 *  found in the specअगरed net_device काष्ठा
 *
 *  Input : poपूर्णांकer to ethernet पूर्णांकerface network device काष्ठाure
 *  Output : N/A
 */
अटल व्योम update_hash_table_mac_address(काष्ठा pxa168_eth_निजी *pep,
					  अचिन्हित अक्षर *oaddr,
					  अचिन्हित अक्षर *addr)
अणु
	/* Delete old entry */
	अगर (oaddr)
		add_del_hash_entry(pep, oaddr, 1, 0, HASH_DELETE);
	/* Add new entry */
	add_del_hash_entry(pep, addr, 1, 0, HASH_ADD);
पूर्ण

अटल पूर्णांक init_hash_table(काष्ठा pxa168_eth_निजी *pep)
अणु
	/*
	 * Hardware expects CPU to build a hash table based on a predefined
	 * hash function and populate it based on hardware address. The
	 * location of the hash table is identअगरied by 32-bit poपूर्णांकer stored
	 * in HTPR पूर्णांकernal रेजिस्टर. Two possible sizes exists क्रम the hash
	 * table 8kB (256kB of DRAM required (4 x 64 kB banks)) and 1/2kB
	 * (16kB of DRAM required (4 x 4 kB banks)).We currently only support
	 * 1/2kB.
	 */
	/* TODO: Add support क्रम 8kB hash table and alternative hash
	 * function.Driver can dynamically चयन to them अगर the 1/2kB hash
	 * table is full.
	 */
	अगर (!pep->htpr) अणु
		pep->htpr = dma_alloc_coherent(pep->dev->dev.parent,
					       HASH_ADDR_TABLE_SIZE,
					       &pep->htpr_dma, GFP_KERNEL);
		अगर (!pep->htpr)
			वापस -ENOMEM;
	पूर्ण अन्यथा अणु
		स_रखो(pep->htpr, 0, HASH_ADDR_TABLE_SIZE);
	पूर्ण
	wrl(pep, HTPR, pep->htpr_dma);
	वापस 0;
पूर्ण

अटल व्योम pxa168_eth_set_rx_mode(काष्ठा net_device *dev)
अणु
	काष्ठा pxa168_eth_निजी *pep = netdev_priv(dev);
	काष्ठा netdev_hw_addr *ha;
	u32 val;

	val = rdl(pep, PORT_CONFIG);
	अगर (dev->flags & IFF_PROMISC)
		val |= PCR_PM;
	अन्यथा
		val &= ~PCR_PM;
	wrl(pep, PORT_CONFIG, val);

	/*
	 * Remove the old list of MAC address and add dev->addr
	 * and multicast address.
	 */
	स_रखो(pep->htpr, 0, HASH_ADDR_TABLE_SIZE);
	update_hash_table_mac_address(pep, शून्य, dev->dev_addr);

	netdev_क्रम_each_mc_addr(ha, dev)
		update_hash_table_mac_address(pep, शून्य, ha->addr);
पूर्ण

अटल व्योम pxa168_eth_get_mac_address(काष्ठा net_device *dev,
				       अचिन्हित अक्षर *addr)
अणु
	काष्ठा pxa168_eth_निजी *pep = netdev_priv(dev);
	अचिन्हित पूर्णांक mac_h = rdl(pep, MAC_ADDR_HIGH);
	अचिन्हित पूर्णांक mac_l = rdl(pep, MAC_ADDR_LOW);

	addr[0] = (mac_h >> 24) & 0xff;
	addr[1] = (mac_h >> 16) & 0xff;
	addr[2] = (mac_h >> 8) & 0xff;
	addr[3] = mac_h & 0xff;
	addr[4] = (mac_l >> 8) & 0xff;
	addr[5] = mac_l & 0xff;
पूर्ण

अटल पूर्णांक pxa168_eth_set_mac_address(काष्ठा net_device *dev, व्योम *addr)
अणु
	काष्ठा sockaddr *sa = addr;
	काष्ठा pxa168_eth_निजी *pep = netdev_priv(dev);
	अचिन्हित अक्षर oldMac[ETH_ALEN];
	u32 mac_h, mac_l;

	अगर (!is_valid_ether_addr(sa->sa_data))
		वापस -EADDRNOTAVAIL;
	स_नकल(oldMac, dev->dev_addr, ETH_ALEN);
	स_नकल(dev->dev_addr, sa->sa_data, ETH_ALEN);

	mac_h = dev->dev_addr[0] << 24;
	mac_h |= dev->dev_addr[1] << 16;
	mac_h |= dev->dev_addr[2] << 8;
	mac_h |= dev->dev_addr[3];
	mac_l = dev->dev_addr[4] << 8;
	mac_l |= dev->dev_addr[5];
	wrl(pep, MAC_ADDR_HIGH, mac_h);
	wrl(pep, MAC_ADDR_LOW, mac_l);

	netअगर_addr_lock_bh(dev);
	update_hash_table_mac_address(pep, oldMac, dev->dev_addr);
	netअगर_addr_unlock_bh(dev);
	वापस 0;
पूर्ण

अटल व्योम eth_port_start(काष्ठा net_device *dev)
अणु
	अचिन्हित पूर्णांक val = 0;
	काष्ठा pxa168_eth_निजी *pep = netdev_priv(dev);
	पूर्णांक tx_curr_desc, rx_curr_desc;

	phy_start(dev->phydev);

	/* Assignment of Tx CTRP of given queue */
	tx_curr_desc = pep->tx_curr_desc_q;
	wrl(pep, ETH_C_TX_DESC_1,
	    (u32) (pep->tx_desc_dma + tx_curr_desc * माप(काष्ठा tx_desc)));

	/* Assignment of Rx CRDP of given queue */
	rx_curr_desc = pep->rx_curr_desc_q;
	wrl(pep, ETH_C_RX_DESC_0,
	    (u32) (pep->rx_desc_dma + rx_curr_desc * माप(काष्ठा rx_desc)));

	wrl(pep, ETH_F_RX_DESC_0,
	    (u32) (pep->rx_desc_dma + rx_curr_desc * माप(काष्ठा rx_desc)));

	/* Clear all पूर्णांकerrupts */
	wrl(pep, INT_CAUSE, 0);

	/* Enable all पूर्णांकerrupts क्रम receive, transmit and error. */
	wrl(pep, INT_MASK, ALL_INTS);

	val = rdl(pep, PORT_CONFIG);
	val |= PCR_EN;
	wrl(pep, PORT_CONFIG, val);

	/* Start RX DMA engine */
	val = rdl(pep, SDMA_CMD);
	val |= SDMA_CMD_ERD;
	wrl(pep, SDMA_CMD, val);
पूर्ण

अटल व्योम eth_port_reset(काष्ठा net_device *dev)
अणु
	काष्ठा pxa168_eth_निजी *pep = netdev_priv(dev);
	अचिन्हित पूर्णांक val = 0;

	/* Stop all पूर्णांकerrupts क्रम receive, transmit and error. */
	wrl(pep, INT_MASK, 0);

	/* Clear all पूर्णांकerrupts */
	wrl(pep, INT_CAUSE, 0);

	/* Stop RX DMA */
	val = rdl(pep, SDMA_CMD);
	val &= ~SDMA_CMD_ERD;	/* पात dma command */

	/* Abort any transmit and receive operations and put DMA
	 * in idle state.
	 */
	पात_dma(pep);

	/* Disable port */
	val = rdl(pep, PORT_CONFIG);
	val &= ~PCR_EN;
	wrl(pep, PORT_CONFIG, val);

	phy_stop(dev->phydev);
पूर्ण

/*
 * txq_reclaim - Free the tx desc data क्रम completed descriptors
 * If क्रमce is non-zero, मुक्तs uncompleted descriptors as well
 */
अटल पूर्णांक txq_reclaim(काष्ठा net_device *dev, पूर्णांक क्रमce)
अणु
	काष्ठा pxa168_eth_निजी *pep = netdev_priv(dev);
	काष्ठा tx_desc *desc;
	u32 cmd_sts;
	काष्ठा sk_buff *skb;
	पूर्णांक tx_index;
	dma_addr_t addr;
	पूर्णांक count;
	पूर्णांक released = 0;

	netअगर_tx_lock(dev);

	pep->work_toकरो &= ~WORK_TX_DONE;
	जबतक (pep->tx_desc_count > 0) अणु
		tx_index = pep->tx_used_desc_q;
		desc = &pep->p_tx_desc_area[tx_index];
		cmd_sts = desc->cmd_sts;
		अगर (!क्रमce && (cmd_sts & BUF_OWNED_BY_DMA)) अणु
			अगर (released > 0) अणु
				जाओ txq_reclaim_end;
			पूर्ण अन्यथा अणु
				released = -1;
				जाओ txq_reclaim_end;
			पूर्ण
		पूर्ण
		pep->tx_used_desc_q = (tx_index + 1) % pep->tx_ring_size;
		pep->tx_desc_count--;
		addr = desc->buf_ptr;
		count = desc->byte_cnt;
		skb = pep->tx_skb[tx_index];
		अगर (skb)
			pep->tx_skb[tx_index] = शून्य;

		अगर (cmd_sts & TX_ERROR) अणु
			अगर (net_ratelimit())
				netdev_err(dev, "Error in TX\n");
			dev->stats.tx_errors++;
		पूर्ण
		dma_unmap_single(&pep->pdev->dev, addr, count, DMA_TO_DEVICE);
		अगर (skb)
			dev_kमुक्त_skb_irq(skb);
		released++;
	पूर्ण
txq_reclaim_end:
	netअगर_tx_unlock(dev);
	वापस released;
पूर्ण

अटल व्योम pxa168_eth_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा pxa168_eth_निजी *pep = netdev_priv(dev);

	netdev_info(dev, "TX timeout  desc_count %d\n", pep->tx_desc_count);

	schedule_work(&pep->tx_समयout_task);
पूर्ण

अटल व्योम pxa168_eth_tx_समयout_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा pxa168_eth_निजी *pep = container_of(work,
						 काष्ठा pxa168_eth_निजी,
						 tx_समयout_task);
	काष्ठा net_device *dev = pep->dev;
	pxa168_eth_stop(dev);
	pxa168_eth_खोलो(dev);
पूर्ण

अटल पूर्णांक rxq_process(काष्ठा net_device *dev, पूर्णांक budget)
अणु
	काष्ठा pxa168_eth_निजी *pep = netdev_priv(dev);
	काष्ठा net_device_stats *stats = &dev->stats;
	अचिन्हित पूर्णांक received_packets = 0;
	काष्ठा sk_buff *skb;

	जबतक (budget-- > 0) अणु
		पूर्णांक rx_next_curr_desc, rx_curr_desc, rx_used_desc;
		काष्ठा rx_desc *rx_desc;
		अचिन्हित पूर्णांक cmd_sts;

		/* Do not process Rx ring in हाल of Rx ring resource error */
		अगर (pep->rx_resource_err)
			अवरोध;
		rx_curr_desc = pep->rx_curr_desc_q;
		rx_used_desc = pep->rx_used_desc_q;
		rx_desc = &pep->p_rx_desc_area[rx_curr_desc];
		cmd_sts = rx_desc->cmd_sts;
		dma_rmb();
		अगर (cmd_sts & (BUF_OWNED_BY_DMA))
			अवरोध;
		skb = pep->rx_skb[rx_curr_desc];
		pep->rx_skb[rx_curr_desc] = शून्य;

		rx_next_curr_desc = (rx_curr_desc + 1) % pep->rx_ring_size;
		pep->rx_curr_desc_q = rx_next_curr_desc;

		/* Rx descriptors exhausted. */
		/* Set the Rx ring resource error flag */
		अगर (rx_next_curr_desc == rx_used_desc)
			pep->rx_resource_err = 1;
		pep->rx_desc_count--;
		dma_unmap_single(&pep->pdev->dev, rx_desc->buf_ptr,
				 rx_desc->buf_size,
				 DMA_FROM_DEVICE);
		received_packets++;
		/*
		 * Update statistics.
		 * Note byte count includes 4 byte CRC count
		 */
		stats->rx_packets++;
		stats->rx_bytes += rx_desc->byte_cnt;
		/*
		 * In हाल received a packet without first / last bits on OR
		 * the error summary bit is on, the packets needs to be droped.
		 */
		अगर (((cmd_sts & (RX_FIRST_DESC | RX_LAST_DESC)) !=
		     (RX_FIRST_DESC | RX_LAST_DESC))
		    || (cmd_sts & RX_ERROR)) अणु

			stats->rx_dropped++;
			अगर ((cmd_sts & (RX_FIRST_DESC | RX_LAST_DESC)) !=
			    (RX_FIRST_DESC | RX_LAST_DESC)) अणु
				अगर (net_ratelimit())
					netdev_err(dev,
						   "Rx pkt on multiple desc\n");
			पूर्ण
			अगर (cmd_sts & RX_ERROR)
				stats->rx_errors++;
			dev_kमुक्त_skb_irq(skb);
		पूर्ण अन्यथा अणु
			/*
			 * The -4 is क्रम the CRC in the trailer of the
			 * received packet
			 */
			skb_put(skb, rx_desc->byte_cnt - 4);
			skb->protocol = eth_type_trans(skb, dev);
			netअगर_receive_skb(skb);
		पूर्ण
	पूर्ण
	/* Fill RX ring with skb's */
	rxq_refill(dev);
	वापस received_packets;
पूर्ण

अटल पूर्णांक pxa168_eth_collect_events(काष्ठा pxa168_eth_निजी *pep,
				     काष्ठा net_device *dev)
अणु
	u32 icr;
	पूर्णांक ret = 0;

	icr = rdl(pep, INT_CAUSE);
	अगर (icr == 0)
		वापस IRQ_NONE;

	wrl(pep, INT_CAUSE, ~icr);
	अगर (icr & (ICR_TXBUF_H | ICR_TXBUF_L)) अणु
		pep->work_toकरो |= WORK_TX_DONE;
		ret = 1;
	पूर्ण
	अगर (icr & ICR_RXBUF)
		ret = 1;
	वापस ret;
पूर्ण

अटल irqवापस_t pxa168_eth_पूर्णांक_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = (काष्ठा net_device *)dev_id;
	काष्ठा pxa168_eth_निजी *pep = netdev_priv(dev);

	अगर (unlikely(!pxa168_eth_collect_events(pep, dev)))
		वापस IRQ_NONE;
	/* Disable पूर्णांकerrupts */
	wrl(pep, INT_MASK, 0);
	napi_schedule(&pep->napi);
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम pxa168_eth_recalc_skb_size(काष्ठा pxa168_eth_निजी *pep)
अणु
	पूर्णांक skb_size;

	/*
	 * Reserve 2+14 bytes क्रम an ethernet header (the hardware
	 * स्वतःmatically prepends 2 bytes of dummy data to each
	 * received packet), 16 bytes क्रम up to four VLAN tags, and
	 * 4 bytes क्रम the trailing FCS -- 36 bytes total.
	 */
	skb_size = pep->dev->mtu + 36;

	/*
	 * Make sure that the skb size is a multiple of 8 bytes, as
	 * the lower three bits of the receive descriptor's buffer
	 * size field are ignored by the hardware.
	 */
	pep->skb_size = (skb_size + 7) & ~7;

	/*
	 * If NET_SKB_PAD is smaller than a cache line,
	 * netdev_alloc_skb() will cause skb->data to be misaligned
	 * to a cache line boundary.  If this is the हाल, include
	 * some extra space to allow re-aligning the data area.
	 */
	pep->skb_size += SKB_DMA_REALIGN;

पूर्ण

अटल पूर्णांक set_port_config_ext(काष्ठा pxa168_eth_निजी *pep)
अणु
	पूर्णांक skb_size;

	pxa168_eth_recalc_skb_size(pep);
	अगर  (pep->skb_size <= 1518)
		skb_size = PCXR_MFL_1518;
	अन्यथा अगर (pep->skb_size <= 1536)
		skb_size = PCXR_MFL_1536;
	अन्यथा अगर (pep->skb_size <= 2048)
		skb_size = PCXR_MFL_2048;
	अन्यथा
		skb_size = PCXR_MFL_64K;

	/* Extended Port Configuration */
	wrl(pep, PORT_CONFIG_EXT,
	    PCXR_AN_SPEED_DIS |		 /* Disable HW AN */
	    PCXR_AN_DUPLEX_DIS |
	    PCXR_AN_FLOWCTL_DIS |
	    PCXR_2BSM |			 /* Two byte prefix aligns IP hdr */
	    PCXR_DSCP_EN |		 /* Enable DSCP in IP */
	    skb_size | PCXR_FLP |	 /* करो not क्रमce link pass */
	    PCXR_TX_HIGH_PRI);		 /* Transmit - high priority queue */

	वापस 0;
पूर्ण

अटल व्योम pxa168_eth_adjust_link(काष्ठा net_device *dev)
अणु
	काष्ठा pxa168_eth_निजी *pep = netdev_priv(dev);
	काष्ठा phy_device *phy = dev->phydev;
	u32 cfg, cfg_o = rdl(pep, PORT_CONFIG);
	u32 cfgext, cfgext_o = rdl(pep, PORT_CONFIG_EXT);

	cfg = cfg_o & ~PCR_DUPLEX_FULL;
	cfgext = cfgext_o & ~(PCXR_SPEED_100 | PCXR_FLOWCTL_DIS | PCXR_RMII_EN);

	अगर (phy->पूर्णांकerface == PHY_INTERFACE_MODE_RMII)
		cfgext |= PCXR_RMII_EN;
	अगर (phy->speed == SPEED_100)
		cfgext |= PCXR_SPEED_100;
	अगर (phy->duplex)
		cfg |= PCR_DUPLEX_FULL;
	अगर (!phy->छोड़ो)
		cfgext |= PCXR_FLOWCTL_DIS;

	/* Bail out अगर there has nothing changed */
	अगर (cfg == cfg_o && cfgext == cfgext_o)
		वापस;

	wrl(pep, PORT_CONFIG, cfg);
	wrl(pep, PORT_CONFIG_EXT, cfgext);

	phy_prपूर्णांक_status(phy);
पूर्ण

अटल पूर्णांक pxa168_init_phy(काष्ठा net_device *dev)
अणु
	काष्ठा pxa168_eth_निजी *pep = netdev_priv(dev);
	काष्ठा ethtool_link_ksettings cmd;
	काष्ठा phy_device *phy = शून्य;
	पूर्णांक err;

	अगर (dev->phydev)
		वापस 0;

	phy = mdiobus_scan(pep->smi_bus, pep->phy_addr);
	अगर (IS_ERR(phy))
		वापस PTR_ERR(phy);

	err = phy_connect_direct(dev, phy, pxa168_eth_adjust_link,
				 pep->phy_पूर्णांकf);
	अगर (err)
		वापस err;

	cmd.base.phy_address = pep->phy_addr;
	cmd.base.speed = pep->phy_speed;
	cmd.base.duplex = pep->phy_duplex;
	biपंचांगap_copy(cmd.link_modes.advertising, PHY_BASIC_FEATURES,
		    __ETHTOOL_LINK_MODE_MASK_NBITS);
	cmd.base.स्वतःneg = AUTONEG_ENABLE;

	अगर (cmd.base.speed != 0)
		cmd.base.स्वतःneg = AUTONEG_DISABLE;

	वापस phy_ethtool_set_link_ksettings(dev, &cmd);
पूर्ण

अटल पूर्णांक pxa168_init_hw(काष्ठा pxa168_eth_निजी *pep)
अणु
	पूर्णांक err = 0;

	/* Disable पूर्णांकerrupts */
	wrl(pep, INT_MASK, 0);
	wrl(pep, INT_CAUSE, 0);
	/* Write to ICR to clear पूर्णांकerrupts. */
	wrl(pep, INT_W_CLEAR, 0);
	/* Abort any transmit and receive operations and put DMA
	 * in idle state.
	 */
	पात_dma(pep);
	/* Initialize address hash table */
	err = init_hash_table(pep);
	अगर (err)
		वापस err;
	/* SDMA configuration */
	wrl(pep, SDMA_CONFIG, SDCR_BSZ8 |	/* Burst size = 32 bytes */
	    SDCR_RIFB |				/* Rx पूर्णांकerrupt on frame */
	    SDCR_BLMT |				/* Little endian transmit */
	    SDCR_BLMR |				/* Little endian receive */
	    SDCR_RC_MAX_RETRANS);		/* Max retransmit count */
	/* Port Configuration */
	wrl(pep, PORT_CONFIG, PCR_HS);		/* Hash size is 1/2kb */
	set_port_config_ext(pep);

	वापस err;
पूर्ण

अटल पूर्णांक rxq_init(काष्ठा net_device *dev)
अणु
	काष्ठा pxa168_eth_निजी *pep = netdev_priv(dev);
	काष्ठा rx_desc *p_rx_desc;
	पूर्णांक size = 0, i = 0;
	पूर्णांक rx_desc_num = pep->rx_ring_size;

	/* Allocate RX skb rings */
	pep->rx_skb = kसुस्मृति(rx_desc_num, माप(*pep->rx_skb), GFP_KERNEL);
	अगर (!pep->rx_skb)
		वापस -ENOMEM;

	/* Allocate RX ring */
	pep->rx_desc_count = 0;
	size = pep->rx_ring_size * माप(काष्ठा rx_desc);
	pep->rx_desc_area_size = size;
	pep->p_rx_desc_area = dma_alloc_coherent(pep->dev->dev.parent, size,
						 &pep->rx_desc_dma,
						 GFP_KERNEL);
	अगर (!pep->p_rx_desc_area)
		जाओ out;

	/* initialize the next_desc_ptr links in the Rx descriptors ring */
	p_rx_desc = pep->p_rx_desc_area;
	क्रम (i = 0; i < rx_desc_num; i++) अणु
		p_rx_desc[i].next_desc_ptr = pep->rx_desc_dma +
		    ((i + 1) % rx_desc_num) * माप(काष्ठा rx_desc);
	पूर्ण
	/* Save Rx desc poपूर्णांकer to driver काष्ठा. */
	pep->rx_curr_desc_q = 0;
	pep->rx_used_desc_q = 0;
	pep->rx_desc_area_size = rx_desc_num * माप(काष्ठा rx_desc);
	वापस 0;
out:
	kमुक्त(pep->rx_skb);
	वापस -ENOMEM;
पूर्ण

अटल व्योम rxq_deinit(काष्ठा net_device *dev)
अणु
	काष्ठा pxa168_eth_निजी *pep = netdev_priv(dev);
	पूर्णांक curr;

	/* Free pपुनः_स्मृतिated skb's on RX rings */
	क्रम (curr = 0; pep->rx_desc_count && curr < pep->rx_ring_size; curr++) अणु
		अगर (pep->rx_skb[curr]) अणु
			dev_kमुक्त_skb(pep->rx_skb[curr]);
			pep->rx_desc_count--;
		पूर्ण
	पूर्ण
	अगर (pep->rx_desc_count)
		netdev_err(dev, "Error in freeing Rx Ring. %d skb's still\n",
			   pep->rx_desc_count);
	/* Free RX ring */
	अगर (pep->p_rx_desc_area)
		dma_मुक्त_coherent(pep->dev->dev.parent, pep->rx_desc_area_size,
				  pep->p_rx_desc_area, pep->rx_desc_dma);
	kमुक्त(pep->rx_skb);
पूर्ण

अटल पूर्णांक txq_init(काष्ठा net_device *dev)
अणु
	काष्ठा pxa168_eth_निजी *pep = netdev_priv(dev);
	काष्ठा tx_desc *p_tx_desc;
	पूर्णांक size = 0, i = 0;
	पूर्णांक tx_desc_num = pep->tx_ring_size;

	pep->tx_skb = kसुस्मृति(tx_desc_num, माप(*pep->tx_skb), GFP_KERNEL);
	अगर (!pep->tx_skb)
		वापस -ENOMEM;

	/* Allocate TX ring */
	pep->tx_desc_count = 0;
	size = pep->tx_ring_size * माप(काष्ठा tx_desc);
	pep->tx_desc_area_size = size;
	pep->p_tx_desc_area = dma_alloc_coherent(pep->dev->dev.parent, size,
						 &pep->tx_desc_dma,
						 GFP_KERNEL);
	अगर (!pep->p_tx_desc_area)
		जाओ out;
	/* Initialize the next_desc_ptr links in the Tx descriptors ring */
	p_tx_desc = pep->p_tx_desc_area;
	क्रम (i = 0; i < tx_desc_num; i++) अणु
		p_tx_desc[i].next_desc_ptr = pep->tx_desc_dma +
		    ((i + 1) % tx_desc_num) * माप(काष्ठा tx_desc);
	पूर्ण
	pep->tx_curr_desc_q = 0;
	pep->tx_used_desc_q = 0;
	pep->tx_desc_area_size = tx_desc_num * माप(काष्ठा tx_desc);
	वापस 0;
out:
	kमुक्त(pep->tx_skb);
	वापस -ENOMEM;
पूर्ण

अटल व्योम txq_deinit(काष्ठा net_device *dev)
अणु
	काष्ठा pxa168_eth_निजी *pep = netdev_priv(dev);

	/* Free outstanding skb's on TX ring */
	txq_reclaim(dev, 1);
	BUG_ON(pep->tx_used_desc_q != pep->tx_curr_desc_q);
	/* Free TX ring */
	अगर (pep->p_tx_desc_area)
		dma_मुक्त_coherent(pep->dev->dev.parent, pep->tx_desc_area_size,
				  pep->p_tx_desc_area, pep->tx_desc_dma);
	kमुक्त(pep->tx_skb);
पूर्ण

अटल पूर्णांक pxa168_eth_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा pxa168_eth_निजी *pep = netdev_priv(dev);
	पूर्णांक err;

	err = pxa168_init_phy(dev);
	अगर (err)
		वापस err;

	err = request_irq(dev->irq, pxa168_eth_पूर्णांक_handler, 0, dev->name, dev);
	अगर (err) अणु
		dev_err(&dev->dev, "can't assign irq\n");
		वापस -EAGAIN;
	पूर्ण
	pep->rx_resource_err = 0;
	err = rxq_init(dev);
	अगर (err != 0)
		जाओ out_मुक्त_irq;
	err = txq_init(dev);
	अगर (err != 0)
		जाओ out_मुक्त_rx_skb;
	pep->rx_used_desc_q = 0;
	pep->rx_curr_desc_q = 0;

	/* Fill RX ring with skb's */
	rxq_refill(dev);
	pep->rx_used_desc_q = 0;
	pep->rx_curr_desc_q = 0;
	netअगर_carrier_off(dev);
	napi_enable(&pep->napi);
	eth_port_start(dev);
	वापस 0;
out_मुक्त_rx_skb:
	rxq_deinit(dev);
out_मुक्त_irq:
	मुक्त_irq(dev->irq, dev);
	वापस err;
पूर्ण

अटल पूर्णांक pxa168_eth_stop(काष्ठा net_device *dev)
अणु
	काष्ठा pxa168_eth_निजी *pep = netdev_priv(dev);
	eth_port_reset(dev);

	/* Disable पूर्णांकerrupts */
	wrl(pep, INT_MASK, 0);
	wrl(pep, INT_CAUSE, 0);
	/* Write to ICR to clear पूर्णांकerrupts. */
	wrl(pep, INT_W_CLEAR, 0);
	napi_disable(&pep->napi);
	del_समयr_sync(&pep->समयout);
	netअगर_carrier_off(dev);
	मुक्त_irq(dev->irq, dev);
	rxq_deinit(dev);
	txq_deinit(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक pxa168_eth_change_mtu(काष्ठा net_device *dev, पूर्णांक mtu)
अणु
	काष्ठा pxa168_eth_निजी *pep = netdev_priv(dev);

	dev->mtu = mtu;
	set_port_config_ext(pep);

	अगर (!netअगर_running(dev))
		वापस 0;

	/*
	 * Stop and then re-खोलो the पूर्णांकerface. This will allocate RX
	 * skbs of the new MTU.
	 * There is a possible danger that the खोलो will not succeed,
	 * due to memory being full.
	 */
	pxa168_eth_stop(dev);
	अगर (pxa168_eth_खोलो(dev)) अणु
		dev_err(&dev->dev,
			"fatal error on re-opening device after MTU change\n");
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक eth_alloc_tx_desc_index(काष्ठा pxa168_eth_निजी *pep)
अणु
	पूर्णांक tx_desc_curr;

	tx_desc_curr = pep->tx_curr_desc_q;
	pep->tx_curr_desc_q = (tx_desc_curr + 1) % pep->tx_ring_size;
	BUG_ON(pep->tx_curr_desc_q == pep->tx_used_desc_q);
	pep->tx_desc_count++;

	वापस tx_desc_curr;
पूर्ण

अटल पूर्णांक pxa168_rx_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा pxa168_eth_निजी *pep =
	    container_of(napi, काष्ठा pxa168_eth_निजी, napi);
	काष्ठा net_device *dev = pep->dev;
	पूर्णांक work_करोne = 0;

	/*
	 * We call txq_reclaim every समय since in NAPI पूर्णांकerupts are disabled
	 * and due to this we miss the TX_DONE पूर्णांकerrupt,which is not updated in
	 * पूर्णांकerrupt status रेजिस्टर.
	 */
	txq_reclaim(dev, 0);
	अगर (netअगर_queue_stopped(dev)
	    && pep->tx_ring_size - pep->tx_desc_count > 1) अणु
		netअगर_wake_queue(dev);
	पूर्ण
	work_करोne = rxq_process(dev, budget);
	अगर (work_करोne < budget) अणु
		napi_complete_करोne(napi, work_करोne);
		wrl(pep, INT_MASK, ALL_INTS);
	पूर्ण

	वापस work_करोne;
पूर्ण

अटल netdev_tx_t
pxa168_eth_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा pxa168_eth_निजी *pep = netdev_priv(dev);
	काष्ठा net_device_stats *stats = &dev->stats;
	काष्ठा tx_desc *desc;
	पूर्णांक tx_index;
	पूर्णांक length;

	tx_index = eth_alloc_tx_desc_index(pep);
	desc = &pep->p_tx_desc_area[tx_index];
	length = skb->len;
	pep->tx_skb[tx_index] = skb;
	desc->byte_cnt = length;
	desc->buf_ptr = dma_map_single(&pep->pdev->dev, skb->data, length,
					DMA_TO_DEVICE);

	skb_tx_बारtamp(skb);

	dma_wmb();
	desc->cmd_sts = BUF_OWNED_BY_DMA | TX_GEN_CRC | TX_FIRST_DESC |
			TX_ZERO_PADDING | TX_LAST_DESC | TX_EN_INT;
	wmb();
	wrl(pep, SDMA_CMD, SDMA_CMD_TXDH | SDMA_CMD_ERD);

	stats->tx_bytes += length;
	stats->tx_packets++;
	netअगर_trans_update(dev);
	अगर (pep->tx_ring_size - pep->tx_desc_count <= 1) अणु
		/* We handled the current skb, but now we are out of space.*/
		netअगर_stop_queue(dev);
	पूर्ण

	वापस NETDEV_TX_OK;
पूर्ण

अटल पूर्णांक smi_रुको_पढ़ोy(काष्ठा pxa168_eth_निजी *pep)
अणु
	पूर्णांक i = 0;

	/* रुको क्रम the SMI रेजिस्टर to become available */
	क्रम (i = 0; rdl(pep, SMI) & SMI_BUSY; i++) अणु
		अगर (i == PHY_WAIT_ITERATIONS)
			वापस -ETIMEDOUT;
		msleep(10);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pxa168_smi_पढ़ो(काष्ठा mii_bus *bus, पूर्णांक phy_addr, पूर्णांक regnum)
अणु
	काष्ठा pxa168_eth_निजी *pep = bus->priv;
	पूर्णांक i = 0;
	पूर्णांक val;

	अगर (smi_रुको_पढ़ोy(pep)) अणु
		netdev_warn(pep->dev, "pxa168_eth: SMI bus busy timeout\n");
		वापस -ETIMEDOUT;
	पूर्ण
	wrl(pep, SMI, (phy_addr << 16) | (regnum << 21) | SMI_OP_R);
	/* now रुको क्रम the data to be valid */
	क्रम (i = 0; !((val = rdl(pep, SMI)) & SMI_R_VALID); i++) अणु
		अगर (i == PHY_WAIT_ITERATIONS) अणु
			netdev_warn(pep->dev,
				    "pxa168_eth: SMI bus read not valid\n");
			वापस -ENODEV;
		पूर्ण
		msleep(10);
	पूर्ण

	वापस val & 0xffff;
पूर्ण

अटल पूर्णांक pxa168_smi_ग_लिखो(काष्ठा mii_bus *bus, पूर्णांक phy_addr, पूर्णांक regnum,
			    u16 value)
अणु
	काष्ठा pxa168_eth_निजी *pep = bus->priv;

	अगर (smi_रुको_पढ़ोy(pep)) अणु
		netdev_warn(pep->dev, "pxa168_eth: SMI bus busy timeout\n");
		वापस -ETIMEDOUT;
	पूर्ण

	wrl(pep, SMI, (phy_addr << 16) | (regnum << 21) |
	    SMI_OP_W | (value & 0xffff));

	अगर (smi_रुको_पढ़ोy(pep)) अणु
		netdev_err(pep->dev, "pxa168_eth: SMI bus busy timeout\n");
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
अटल व्योम pxa168_eth_netpoll(काष्ठा net_device *dev)
अणु
	disable_irq(dev->irq);
	pxa168_eth_पूर्णांक_handler(dev->irq, dev);
	enable_irq(dev->irq);
पूर्ण
#पूर्ण_अगर

अटल व्योम pxa168_get_drvinfo(काष्ठा net_device *dev,
			       काष्ठा ethtool_drvinfo *info)
अणु
	strlcpy(info->driver, DRIVER_NAME, माप(info->driver));
	strlcpy(info->version, DRIVER_VERSION, माप(info->version));
	strlcpy(info->fw_version, "N/A", माप(info->fw_version));
	strlcpy(info->bus_info, "N/A", माप(info->bus_info));
पूर्ण

अटल स्थिर काष्ठा ethtool_ops pxa168_ethtool_ops = अणु
	.get_drvinfo	= pxa168_get_drvinfo,
	.nway_reset	= phy_ethtool_nway_reset,
	.get_link	= ethtool_op_get_link,
	.get_ts_info	= ethtool_op_get_ts_info,
	.get_link_ksettings = phy_ethtool_get_link_ksettings,
	.set_link_ksettings = phy_ethtool_set_link_ksettings,
पूर्ण;

अटल स्थिर काष्ठा net_device_ops pxa168_eth_netdev_ops = अणु
	.nकरो_खोलो		= pxa168_eth_खोलो,
	.nकरो_stop		= pxa168_eth_stop,
	.nकरो_start_xmit		= pxa168_eth_start_xmit,
	.nकरो_set_rx_mode	= pxa168_eth_set_rx_mode,
	.nकरो_set_mac_address	= pxa168_eth_set_mac_address,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_करो_ioctl		= phy_करो_ioctl,
	.nकरो_change_mtu		= pxa168_eth_change_mtu,
	.nकरो_tx_समयout		= pxa168_eth_tx_समयout,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller    = pxa168_eth_netpoll,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक pxa168_eth_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pxa168_eth_निजी *pep = शून्य;
	काष्ठा net_device *dev = शून्य;
	काष्ठा resource *res;
	काष्ठा clk *clk;
	काष्ठा device_node *np;
	पूर्णांक err;

	prपूर्णांकk(KERN_NOTICE "PXA168 10/100 Ethernet Driver\n");

	clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(clk)) अणु
		dev_err(&pdev->dev, "Fast Ethernet failed to get clock\n");
		वापस -ENODEV;
	पूर्ण
	clk_prepare_enable(clk);

	dev = alloc_etherdev(माप(काष्ठा pxa168_eth_निजी));
	अगर (!dev) अणु
		err = -ENOMEM;
		जाओ err_clk;
	पूर्ण

	platक्रमm_set_drvdata(pdev, dev);
	pep = netdev_priv(dev);
	pep->dev = dev;
	pep->clk = clk;

	pep->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(pep->base)) अणु
		err = PTR_ERR(pep->base);
		जाओ err_netdev;
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);
	BUG_ON(!res);
	dev->irq = res->start;
	dev->netdev_ops = &pxa168_eth_netdev_ops;
	dev->watchकरोg_समयo = 2 * HZ;
	dev->base_addr = 0;
	dev->ethtool_ops = &pxa168_ethtool_ops;

	/* MTU range: 68 - 9500 */
	dev->min_mtu = ETH_MIN_MTU;
	dev->max_mtu = 9500;

	INIT_WORK(&pep->tx_समयout_task, pxa168_eth_tx_समयout_task);

	err = of_get_mac_address(pdev->dev.of_node, dev->dev_addr);
	अगर (err) अणु
		/* try पढ़ोing the mac address, अगर set by the bootloader */
		pxa168_eth_get_mac_address(dev, dev->dev_addr);
		अगर (!is_valid_ether_addr(dev->dev_addr)) अणु
			dev_info(&pdev->dev, "Using random mac address\n");
			eth_hw_addr_अक्रमom(dev);
		पूर्ण
	पूर्ण

	pep->rx_ring_size = NUM_RX_DESCS;
	pep->tx_ring_size = NUM_TX_DESCS;

	pep->pd = dev_get_platdata(&pdev->dev);
	अगर (pep->pd) अणु
		अगर (pep->pd->rx_queue_size)
			pep->rx_ring_size = pep->pd->rx_queue_size;

		अगर (pep->pd->tx_queue_size)
			pep->tx_ring_size = pep->pd->tx_queue_size;

		pep->port_num = pep->pd->port_number;
		pep->phy_addr = pep->pd->phy_addr;
		pep->phy_speed = pep->pd->speed;
		pep->phy_duplex = pep->pd->duplex;
		pep->phy_पूर्णांकf = pep->pd->पूर्णांकf;

		अगर (pep->pd->init)
			pep->pd->init();
	पूर्ण अन्यथा अगर (pdev->dev.of_node) अणु
		of_property_पढ़ो_u32(pdev->dev.of_node, "port-id",
				     &pep->port_num);

		np = of_parse_phandle(pdev->dev.of_node, "phy-handle", 0);
		अगर (!np) अणु
			dev_err(&pdev->dev, "missing phy-handle\n");
			err = -EINVAL;
			जाओ err_netdev;
		पूर्ण
		of_property_पढ़ो_u32(np, "reg", &pep->phy_addr);
		of_node_put(np);
		err = of_get_phy_mode(pdev->dev.of_node, &pep->phy_पूर्णांकf);
		अगर (err && err != -ENODEV)
			जाओ err_netdev;
	पूर्ण

	/* Hardware supports only 3 ports */
	BUG_ON(pep->port_num > 2);
	netअगर_napi_add(dev, &pep->napi, pxa168_rx_poll, pep->rx_ring_size);

	स_रखो(&pep->समयout, 0, माप(काष्ठा समयr_list));
	समयr_setup(&pep->समयout, rxq_refill_समयr_wrapper, 0);

	pep->smi_bus = mdiobus_alloc();
	अगर (!pep->smi_bus) अणु
		err = -ENOMEM;
		जाओ err_netdev;
	पूर्ण
	pep->smi_bus->priv = pep;
	pep->smi_bus->name = "pxa168_eth smi";
	pep->smi_bus->पढ़ो = pxa168_smi_पढ़ो;
	pep->smi_bus->ग_लिखो = pxa168_smi_ग_लिखो;
	snम_लिखो(pep->smi_bus->id, MII_BUS_ID_SIZE, "%s-%d",
		pdev->name, pdev->id);
	pep->smi_bus->parent = &pdev->dev;
	pep->smi_bus->phy_mask = 0xffffffff;
	err = mdiobus_रेजिस्टर(pep->smi_bus);
	अगर (err)
		जाओ err_मुक्त_mdio;

	pep->pdev = pdev;
	SET_NETDEV_DEV(dev, &pdev->dev);
	pxa168_init_hw(pep);
	err = रेजिस्टर_netdev(dev);
	अगर (err)
		जाओ err_mdiobus;
	वापस 0;

err_mdiobus:
	mdiobus_unरेजिस्टर(pep->smi_bus);
err_मुक्त_mdio:
	mdiobus_मुक्त(pep->smi_bus);
err_netdev:
	मुक्त_netdev(dev);
err_clk:
	clk_disable_unprepare(clk);
	वापस err;
पूर्ण

अटल पूर्णांक pxa168_eth_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *dev = platक्रमm_get_drvdata(pdev);
	काष्ठा pxa168_eth_निजी *pep = netdev_priv(dev);

	अगर (pep->htpr) अणु
		dma_मुक्त_coherent(pep->dev->dev.parent, HASH_ADDR_TABLE_SIZE,
				  pep->htpr, pep->htpr_dma);
		pep->htpr = शून्य;
	पूर्ण
	अगर (dev->phydev)
		phy_disconnect(dev->phydev);

	clk_disable_unprepare(pep->clk);
	mdiobus_unरेजिस्टर(pep->smi_bus);
	mdiobus_मुक्त(pep->smi_bus);
	cancel_work_sync(&pep->tx_समयout_task);
	unरेजिस्टर_netdev(dev);
	मुक्त_netdev(dev);
	वापस 0;
पूर्ण

अटल व्योम pxa168_eth_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *dev = platक्रमm_get_drvdata(pdev);
	eth_port_reset(dev);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक pxa168_eth_resume(काष्ठा platक्रमm_device *pdev)
अणु
	वापस -ENOSYS;
पूर्ण

अटल पूर्णांक pxa168_eth_suspend(काष्ठा platक्रमm_device *pdev, pm_message_t state)
अणु
	वापस -ENOSYS;
पूर्ण

#अन्यथा
#घोषणा pxa168_eth_resume शून्य
#घोषणा pxa168_eth_suspend शून्य
#पूर्ण_अगर

अटल स्थिर काष्ठा of_device_id pxa168_eth_of_match[] = अणु
	अणु .compatible = "marvell,pxa168-eth" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, pxa168_eth_of_match);

अटल काष्ठा platक्रमm_driver pxa168_eth_driver = अणु
	.probe = pxa168_eth_probe,
	.हटाओ = pxa168_eth_हटाओ,
	.shutकरोwn = pxa168_eth_shutकरोwn,
	.resume = pxa168_eth_resume,
	.suspend = pxa168_eth_suspend,
	.driver = अणु
		.name		= DRIVER_NAME,
		.of_match_table	= of_match_ptr(pxa168_eth_of_match),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(pxa168_eth_driver);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Ethernet driver for Marvell PXA168");
MODULE_ALIAS("platform:pxa168_eth");
