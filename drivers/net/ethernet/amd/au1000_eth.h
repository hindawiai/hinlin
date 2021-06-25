<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *
 * Alchemy Au1x00 ethernet driver include file
 *
 * Author: Pete Popov <ppopov@mvista.com>
 *
 * Copyright 2001 MontaVista Software Inc.
 */


#घोषणा MAC_IOSIZE 0x10000
#घोषणा NUM_RX_DMA 4       /* Au1x00 has 4 rx hardware descriptors */
#घोषणा NUM_TX_DMA 4       /* Au1x00 has 4 tx hardware descriptors */

#घोषणा NUM_RX_BUFFS 4
#घोषणा NUM_TX_BUFFS 4
#घोषणा MAX_BUF_SIZE 2048

#घोषणा ETH_TX_TIMEOUT (HZ/4)
#घोषणा MAC_MIN_PKT_SIZE 64

#घोषणा MULTICAST_FILTER_LIMIT 64

/*
 * Data Buffer Descriptor. Data buffers must be aligned on 32 byte
 * boundary क्रम both, receive and transmit.
 */
काष्ठा db_dest अणु
	काष्ठा db_dest *pnext;
	u32 *vaddr;
	dma_addr_t dma_addr;
पूर्ण;

/*
 * The transmit and receive descriptors are memory
 * mapped रेजिस्टरs.
 */
काष्ठा tx_dma अणु
	u32 status;
	u32 buff_stat;
	u32 len;
	u32 pad;
पूर्ण;

काष्ठा rx_dma अणु
	u32 status;
	u32 buff_stat;
	u32 pad[2];
पूर्ण;


/*
 * MAC control रेजिस्टरs, memory mapped.
 */
काष्ठा mac_reg अणु
	u32 control;
	u32 mac_addr_high;
	u32 mac_addr_low;
	u32 multi_hash_high;
	u32 multi_hash_low;
	u32 mii_control;
	u32 mii_data;
	u32 flow_control;
	u32 vlan1_tag;
	u32 vlan2_tag;
पूर्ण;


काष्ठा au1000_निजी अणु
	काष्ठा db_dest *pDBमुक्त;
	काष्ठा db_dest db[NUM_RX_BUFFS+NUM_TX_BUFFS];
	काष्ठा rx_dma *rx_dma_ring[NUM_RX_DMA];
	काष्ठा tx_dma *tx_dma_ring[NUM_TX_DMA];
	काष्ठा db_dest *rx_db_inuse[NUM_RX_DMA];
	काष्ठा db_dest *tx_db_inuse[NUM_TX_DMA];
	u32 rx_head;
	u32 tx_head;
	u32 tx_tail;
	u32 tx_full;

	पूर्णांक mac_id;

	पूर्णांक mac_enabled;       /* whether MAC is currently enabled and running
				* (req. क्रम mdio)
				*/

	पूर्णांक old_link;          /* used by au1000_adjust_link */
	पूर्णांक old_speed;
	पूर्णांक old_duplex;

	काष्ठा mii_bus *mii_bus;

	/* PHY configuration */
	पूर्णांक phy_अटल_config;
	पूर्णांक phy_search_highest_addr;
	पूर्णांक phy1_search_mac0;

	पूर्णांक phy_addr;
	पूर्णांक phy_busid;
	पूर्णांक phy_irq;

	/* These variables are just क्रम quick access
	 * to certain regs addresses.
	 */
	काष्ठा mac_reg *mac;  /* mac रेजिस्टरs                      */
	u32 *enable;     /* address of MAC Enable Register     */
	व्योम __iomem *macdma;	/* base of MAC DMA port */
	u32 vaddr;                /* भव address of rx/tx buffers   */
	dma_addr_t dma_addr;      /* dma address of rx/tx buffers       */

	spinlock_t lock;       /* Serialise access to device */

	u32 msg_enable;
पूर्ण;
