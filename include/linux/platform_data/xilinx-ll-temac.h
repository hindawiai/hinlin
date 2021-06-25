<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_XILINX_LL_TEMAC_H
#घोषणा __LINUX_XILINX_LL_TEMAC_H

#समावेश <linux/अगर_ether.h>
#समावेश <linux/phy.h>
#समावेश <linux/spinlock.h>

काष्ठा ll_temac_platक्रमm_data अणु
	bool txcsum;		/* Enable/disable TX checksum */
	bool rxcsum;		/* Enable/disable RX checksum */
	u8 mac_addr[ETH_ALEN];	/* MAC address (6 bytes) */
	/* Clock frequency क्रम input to MDIO घड़ी generator */
	u32 mdio_clk_freq;
	अचिन्हित दीर्घ दीर्घ mdio_bus_id; /* Unique id क्रम MDIO bus */
	पूर्णांक phy_addr;		/* Address of the PHY to connect to */
	phy_पूर्णांकerface_t phy_पूर्णांकerface; /* PHY पूर्णांकerface mode */
	bool reg_little_endian;	/* Little endian TEMAC रेजिस्टर access  */
	bool dma_little_endian;	/* Little endian DMA रेजिस्टर access  */
	/* Pre-initialized mutex to use क्रम synchronizing indirect
	 * रेजिस्टर access.  When using both पूर्णांकerfaces of a single
	 * TEMAC IP block, the same mutex should be passed here, as
	 * they share the same DCR bus bridge.
	 */
	spinlock_t *indirect_lock;
	/* DMA channel control setup */
	u8 tx_irq_समयout;	/* TX Interrupt Delay Time-out */
	u8 tx_irq_count;	/* TX Interrupt Coalescing Threshold Count */
	u8 rx_irq_समयout;	/* RX Interrupt Delay Time-out */
	u8 rx_irq_count;	/* RX Interrupt Coalescing Threshold Count */
पूर्ण;

#पूर्ण_अगर /* __LINUX_XILINX_LL_TEMAC_H */
