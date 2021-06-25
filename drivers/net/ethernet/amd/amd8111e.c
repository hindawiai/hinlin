<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later

/* Advanced  Micro Devices Inc. AMD8111E Linux Network Driver
 * Copyright (C) 2004 Advanced Micro Devices
 *
 * Copyright 2001,2002 Jeff Garzik <jgarzik@mandrakesoft.com> [ 8139cp.c,tg3.c ]
 * Copyright (C) 2001, 2002 David S. Miller (davem@redhat.com)[ tg3.c]
 * Copyright 1996-1999 Thomas Bogenकरोerfer [ pcnet32.c ]
 * Derived from the lance driver written 1993,1994,1995 by Donald Becker.
 * Copyright 1993 United States Government as represented by the
 *	Director, National Security Agency.[ pcnet32.c ]
 * Carsten Langgaard, carstenl@mips.com [ pcnet32.c ]
 * Copyright (C) 2000 MIPS Technologies, Inc.  All rights reserved.
 *

Module Name:

	amd8111e.c

Abstract:

 	 AMD8111 based 10/100 Ethernet Controller Driver.

Environment:

	Kernel Mode

Revision History:
 	3.0.0
	   Initial Revision.
	3.0.1
	 1. Dynamic पूर्णांकerrupt coalescing.
	 2. Removed prev_stats.
	 3. MII support.
	 4. Dynamic IPG support
	3.0.2  05/29/2003
	 1. Bug fix: Fixed failure to send jumbo packets larger than 4k.
	 2. Bug fix: Fixed VLAN support failure.
	 3. Bug fix: Fixed receive पूर्णांकerrupt coalescing bug.
	 4. Dynamic IPG support is disabled by शेष.
	3.0.3 06/05/2003
	 1. Bug fix: Fixed failure to बंद the पूर्णांकerface अगर SMP is enabled.
	3.0.4 12/09/2003
	 1. Added set_mac_address routine क्रम bonding driver support.
	 2. Tested the driver क्रम bonding support
	 3. Bug fix: Fixed mismach in actual receive buffer lenth and lenth
	    indicated to the h/w.
	 4. Modअगरied amd8111e_rx() routine to receive all the received packets
	    in the first पूर्णांकerrupt.
	 5. Bug fix: Corrected  rx_errors  reported in get_stats() function.
	3.0.5 03/22/2004
	 1. Added NAPI support

*/


#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/compiler.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>
#समावेश <linux/pci.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/mii.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/crc32.h>
#समावेश <linux/dma-mapping.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/byteorder.h>
#समावेश <linux/uaccess.h>

#अगर IS_ENABLED(CONFIG_VLAN_8021Q)
#घोषणा AMD8111E_VLAN_TAG_USED 1
#अन्यथा
#घोषणा AMD8111E_VLAN_TAG_USED 0
#पूर्ण_अगर

#समावेश "amd8111e.h"
#घोषणा MODULE_NAME	"amd8111e"
MODULE_AUTHOR("Advanced Micro Devices, Inc.");
MODULE_DESCRIPTION("AMD8111 based 10/100 Ethernet Controller.");
MODULE_LICENSE("GPL");
module_param_array(speed_duplex, पूर्णांक, शून्य, 0);
MODULE_PARM_DESC(speed_duplex, "Set device speed and duplex modes, 0: Auto Negotiate, 1: 10Mbps Half Duplex, 2: 10Mbps Full Duplex, 3: 100Mbps Half Duplex, 4: 100Mbps Full Duplex");
module_param_array(coalesce, bool, शून्य, 0);
MODULE_PARM_DESC(coalesce, "Enable or Disable interrupt coalescing, 1: Enable, 0: Disable");
module_param_array(dynamic_ipg, bool, शून्य, 0);
MODULE_PARM_DESC(dynamic_ipg, "Enable or Disable dynamic IPG, 1: Enable, 0: Disable");

/* This function will पढ़ो the PHY रेजिस्टरs. */
अटल पूर्णांक amd8111e_पढ़ो_phy(काष्ठा amd8111e_priv *lp,
			     पूर्णांक phy_id, पूर्णांक reg, u32 *val)
अणु
	व्योम __iomem *mmio = lp->mmio;
	अचिन्हित पूर्णांक reg_val;
	अचिन्हित पूर्णांक repeat = REPEAT_CNT;

	reg_val = पढ़ोl(mmio + PHY_ACCESS);
	जबतक (reg_val & PHY_CMD_ACTIVE)
		reg_val = पढ़ोl(mmio + PHY_ACCESS);

	ग_लिखोl(PHY_RD_CMD | ((phy_id & 0x1f) << 21) |
			   ((reg & 0x1f) << 16), mmio + PHY_ACCESS);
	करो अणु
		reg_val = पढ़ोl(mmio + PHY_ACCESS);
		udelay(30);  /* It takes 30 us to पढ़ो/ग_लिखो data */
	पूर्ण जबतक (--repeat && (reg_val & PHY_CMD_ACTIVE));
	अगर (reg_val & PHY_RD_ERR)
		जाओ err_phy_पढ़ो;

	*val = reg_val & 0xffff;
	वापस 0;
err_phy_पढ़ो:
	*val = 0;
	वापस -EINVAL;

पूर्ण

/* This function will ग_लिखो पूर्णांकo PHY रेजिस्टरs. */
अटल पूर्णांक amd8111e_ग_लिखो_phy(काष्ठा amd8111e_priv *lp,
			      पूर्णांक phy_id, पूर्णांक reg, u32 val)
अणु
	अचिन्हित पूर्णांक repeat = REPEAT_CNT;
	व्योम __iomem *mmio = lp->mmio;
	अचिन्हित पूर्णांक reg_val;

	reg_val = पढ़ोl(mmio + PHY_ACCESS);
	जबतक (reg_val & PHY_CMD_ACTIVE)
		reg_val = पढ़ोl(mmio + PHY_ACCESS);

	ग_लिखोl(PHY_WR_CMD | ((phy_id & 0x1f) << 21) |
			   ((reg & 0x1f) << 16)|val, mmio + PHY_ACCESS);

	करो अणु
		reg_val = पढ़ोl(mmio + PHY_ACCESS);
		udelay(30);  /* It takes 30 us to पढ़ो/ग_लिखो the data */
	पूर्ण जबतक (--repeat && (reg_val & PHY_CMD_ACTIVE));

	अगर (reg_val & PHY_RD_ERR)
		जाओ err_phy_ग_लिखो;

	वापस 0;

err_phy_ग_लिखो:
	वापस -EINVAL;

पूर्ण

/* This is the mii रेजिस्टर पढ़ो function provided to the mii पूर्णांकerface. */
अटल पूर्णांक amd8111e_mdio_पढ़ो(काष्ठा net_device *dev, पूर्णांक phy_id, पूर्णांक reg_num)
अणु
	काष्ठा amd8111e_priv *lp = netdev_priv(dev);
	अचिन्हित पूर्णांक reg_val;

	amd8111e_पढ़ो_phy(lp, phy_id, reg_num, &reg_val);
	वापस reg_val;

पूर्ण

/* This is the mii रेजिस्टर ग_लिखो function provided to the mii पूर्णांकerface. */
अटल व्योम amd8111e_mdio_ग_लिखो(काष्ठा net_device *dev,
				पूर्णांक phy_id, पूर्णांक reg_num, पूर्णांक val)
अणु
	काष्ठा amd8111e_priv *lp = netdev_priv(dev);

	amd8111e_ग_लिखो_phy(lp, phy_id, reg_num, val);
पूर्ण

/* This function will set PHY speed. During initialization sets
 * the original speed to 100 full
 */
अटल व्योम amd8111e_set_ext_phy(काष्ठा net_device *dev)
अणु
	काष्ठा amd8111e_priv *lp = netdev_priv(dev);
	u32 bmcr, advert, पंचांगp;

	/* Determine mii रेजिस्टर values to set the speed */
	advert = amd8111e_mdio_पढ़ो(dev, lp->ext_phy_addr, MII_ADVERTISE);
	पंचांगp = advert & ~(ADVERTISE_ALL | ADVERTISE_100BASE4);
	चयन (lp->ext_phy_option) अणु

		शेष:
		हाल SPEED_AUTONEG: /* advertise all values */
			पंचांगp |= (ADVERTISE_10HALF | ADVERTISE_10FULL |
				ADVERTISE_100HALF | ADVERTISE_100FULL);
			अवरोध;
		हाल SPEED10_HALF:
			पंचांगp |= ADVERTISE_10HALF;
			अवरोध;
		हाल SPEED10_FULL:
			पंचांगp |= ADVERTISE_10FULL;
			अवरोध;
		हाल SPEED100_HALF:
			पंचांगp |= ADVERTISE_100HALF;
			अवरोध;
		हाल SPEED100_FULL:
			पंचांगp |= ADVERTISE_100FULL;
			अवरोध;
	पूर्ण

	अगर(advert != पंचांगp)
		amd8111e_mdio_ग_लिखो(dev, lp->ext_phy_addr, MII_ADVERTISE, पंचांगp);
	/* Restart स्वतः negotiation */
	bmcr = amd8111e_mdio_पढ़ो(dev, lp->ext_phy_addr, MII_BMCR);
	bmcr |= (BMCR_ANENABLE | BMCR_ANRESTART);
	amd8111e_mdio_ग_लिखो(dev, lp->ext_phy_addr, MII_BMCR, bmcr);

पूर्ण

/* This function will unmap skb->data space and will मुक्त
 * all transmit and receive skbuffs.
 */
अटल पूर्णांक amd8111e_मुक्त_skbs(काष्ठा net_device *dev)
अणु
	काष्ठा amd8111e_priv *lp = netdev_priv(dev);
	काष्ठा sk_buff *rx_skbuff;
	पूर्णांक i;

	/* Freeing transmit skbs */
	क्रम (i = 0; i < NUM_TX_BUFFERS; i++) अणु
		अगर (lp->tx_skbuff[i]) अणु
			dma_unmap_single(&lp->pci_dev->dev,
					 lp->tx_dma_addr[i],
					 lp->tx_skbuff[i]->len, DMA_TO_DEVICE);
			dev_kमुक्त_skb(lp->tx_skbuff[i]);
			lp->tx_skbuff[i] = शून्य;
			lp->tx_dma_addr[i] = 0;
		पूर्ण
	पूर्ण
	/* Freeing previously allocated receive buffers */
	क्रम (i = 0; i < NUM_RX_BUFFERS; i++) अणु
		rx_skbuff = lp->rx_skbuff[i];
		अगर (rx_skbuff != शून्य) अणु
			dma_unmap_single(&lp->pci_dev->dev,
					 lp->rx_dma_addr[i],
					 lp->rx_buff_len - 2, DMA_FROM_DEVICE);
			dev_kमुक्त_skb(lp->rx_skbuff[i]);
			lp->rx_skbuff[i] = शून्य;
			lp->rx_dma_addr[i] = 0;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* This will set the receive buffer length corresponding
 * to the mtu size of networkपूर्णांकerface.
 */
अटल अंतरभूत व्योम amd8111e_set_rx_buff_len(काष्ठा net_device *dev)
अणु
	काष्ठा amd8111e_priv *lp = netdev_priv(dev);
	अचिन्हित पूर्णांक mtu = dev->mtu;

	अगर (mtu > ETH_DATA_LEN) अणु
		/* MTU + ethernet header + FCS
		 * + optional VLAN tag + skb reserve space 2
		 */
		lp->rx_buff_len = mtu + ETH_HLEN + 10;
		lp->options |= OPTION_JUMBO_ENABLE;
	पूर्ण अन्यथा अणु
		lp->rx_buff_len = PKT_BUFF_SZ;
		lp->options &= ~OPTION_JUMBO_ENABLE;
	पूर्ण
पूर्ण

/* This function will मुक्त all the previously allocated buffers,
 * determine new receive buffer length  and will allocate new receive buffers.
 * This function also allocates and initializes both the transmitter
 * and receive hardware descriptors.
 */
अटल पूर्णांक amd8111e_init_ring(काष्ठा net_device *dev)
अणु
	काष्ठा amd8111e_priv *lp = netdev_priv(dev);
	पूर्णांक i;

	lp->rx_idx = lp->tx_idx = 0;
	lp->tx_complete_idx = 0;
	lp->tx_ring_idx = 0;


	अगर (lp->खोलोed)
		/* Free previously allocated transmit and receive skbs */
		amd8111e_मुक्त_skbs(dev);

	अन्यथा अणु
		/* allocate the tx and rx descriptors */
		lp->tx_ring = dma_alloc_coherent(&lp->pci_dev->dev,
			माप(काष्ठा amd8111e_tx_dr) * NUM_TX_RING_DR,
			&lp->tx_ring_dma_addr, GFP_ATOMIC);
		अगर (!lp->tx_ring)
			जाओ err_no_mem;

		lp->rx_ring = dma_alloc_coherent(&lp->pci_dev->dev,
			माप(काष्ठा amd8111e_rx_dr) * NUM_RX_RING_DR,
			&lp->rx_ring_dma_addr, GFP_ATOMIC);
		अगर (!lp->rx_ring)
			जाओ err_मुक्त_tx_ring;
	पूर्ण

	/* Set new receive buff size */
	amd8111e_set_rx_buff_len(dev);

	/* Allocating receive  skbs */
	क्रम (i = 0; i < NUM_RX_BUFFERS; i++) अणु

		lp->rx_skbuff[i] = netdev_alloc_skb(dev, lp->rx_buff_len);
		अगर (!lp->rx_skbuff[i]) अणु
			/* Release previos allocated skbs */
			क्रम (--i; i >= 0; i--)
				dev_kमुक्त_skb(lp->rx_skbuff[i]);
			जाओ err_मुक्त_rx_ring;
		पूर्ण
		skb_reserve(lp->rx_skbuff[i], 2);
	पूर्ण
        /* Initilaizing receive descriptors */
	क्रम (i = 0; i < NUM_RX_BUFFERS; i++) अणु
		lp->rx_dma_addr[i] = dma_map_single(&lp->pci_dev->dev,
						    lp->rx_skbuff[i]->data,
						    lp->rx_buff_len - 2,
						    DMA_FROM_DEVICE);

		lp->rx_ring[i].buff_phy_addr = cpu_to_le32(lp->rx_dma_addr[i]);
		lp->rx_ring[i].buff_count = cpu_to_le16(lp->rx_buff_len-2);
		wmb();
		lp->rx_ring[i].rx_flags = cpu_to_le16(OWN_BIT);
	पूर्ण

	/* Initializing transmit descriptors */
	क्रम (i = 0; i < NUM_TX_RING_DR; i++) अणु
		lp->tx_ring[i].buff_phy_addr = 0;
		lp->tx_ring[i].tx_flags = 0;
		lp->tx_ring[i].buff_count = 0;
	पूर्ण

	वापस 0;

err_मुक्त_rx_ring:

	dma_मुक्त_coherent(&lp->pci_dev->dev,
			  माप(काष्ठा amd8111e_rx_dr) * NUM_RX_RING_DR,
			  lp->rx_ring, lp->rx_ring_dma_addr);

err_मुक्त_tx_ring:

	dma_मुक्त_coherent(&lp->pci_dev->dev,
			  माप(काष्ठा amd8111e_tx_dr) * NUM_TX_RING_DR,
			  lp->tx_ring, lp->tx_ring_dma_addr);

err_no_mem:
	वापस -ENOMEM;
पूर्ण

/* This function will set the पूर्णांकerrupt coalescing according
 * to the input arguments
 */
अटल पूर्णांक amd8111e_set_coalesce(काष्ठा net_device *dev, क्रमागत coal_mode cmod)
अणु
	अचिन्हित पूर्णांक समयout;
	अचिन्हित पूर्णांक event_count;

	काष्ठा amd8111e_priv *lp = netdev_priv(dev);
	व्योम __iomem *mmio = lp->mmio;
	काष्ठा amd8111e_coalesce_conf *coal_conf = &lp->coal_conf;


	चयन(cmod)
	अणु
		हाल RX_INTR_COAL :
			समयout = coal_conf->rx_समयout;
			event_count = coal_conf->rx_event_count;
			अगर (समयout > MAX_TIMEOUT ||
			    event_count > MAX_EVENT_COUNT)
				वापस -EINVAL;

			समयout = समयout * DELAY_TIMER_CONV;
			ग_लिखोl(VAL0|STINTEN, mmio+INTEN0);
			ग_लिखोl((u32)DLY_INT_A_R0 | (event_count << 16) |
				समयout, mmio + DLY_INT_A);
			अवरोध;

		हाल TX_INTR_COAL:
			समयout = coal_conf->tx_समयout;
			event_count = coal_conf->tx_event_count;
			अगर (समयout > MAX_TIMEOUT ||
			    event_count > MAX_EVENT_COUNT)
				वापस -EINVAL;


			समयout = समयout * DELAY_TIMER_CONV;
			ग_लिखोl(VAL0 | STINTEN, mmio + INTEN0);
			ग_लिखोl((u32)DLY_INT_B_T0 | (event_count << 16) |
				समयout, mmio + DLY_INT_B);
			अवरोध;

		हाल DISABLE_COAL:
			ग_लिखोl(0, mmio + STVAL);
			ग_लिखोl(STINTEN, mmio + INTEN0);
			ग_लिखोl(0, mmio + DLY_INT_B);
			ग_लिखोl(0, mmio + DLY_INT_A);
			अवरोध;
		 हाल ENABLE_COAL:
		       /* Start the समयr */
			ग_लिखोl((u32)SOFT_TIMER_FREQ, mmio + STVAL); /* 0.5 sec */
			ग_लिखोl(VAL0 | STINTEN, mmio + INTEN0);
			अवरोध;
		शेष:
			अवरोध;

   पूर्ण
	वापस 0;

पूर्ण

/* This function initializes the device रेजिस्टरs  and starts the device. */
अटल पूर्णांक amd8111e_restart(काष्ठा net_device *dev)
अणु
	काष्ठा amd8111e_priv *lp = netdev_priv(dev);
	व्योम __iomem *mmio = lp->mmio;
	पूर्णांक i, reg_val;

	/* stop the chip */
	ग_लिखोl(RUN, mmio + CMD0);

	अगर (amd8111e_init_ring(dev))
		वापस -ENOMEM;

	/* enable the port manager and set स्वतः negotiation always */
	ग_लिखोl((u32)VAL1 | EN_PMGR, mmio + CMD3);
	ग_लिखोl((u32)XPHYANE | XPHYRST, mmio + CTRL2);

	amd8111e_set_ext_phy(dev);

	/* set control रेजिस्टरs */
	reg_val = पढ़ोl(mmio + CTRL1);
	reg_val &= ~XMTSP_MASK;
	ग_लिखोl(reg_val | XMTSP_128 | CACHE_ALIGN, mmio + CTRL1);

	/* enable पूर्णांकerrupt */
	ग_लिखोl(APINT5EN | APINT4EN | APINT3EN | APINT2EN | APINT1EN |
		APINT0EN | MIIPDTINTEN | MCCIINTEN | MCCINTEN | MREINTEN |
		SPNDINTEN | MPINTEN | SINTEN | STINTEN, mmio + INTEN0);

	ग_लिखोl(VAL3 | LCINTEN | VAL1 | TINTEN0 | VAL0 | RINTEN0, mmio + INTEN0);

	/* initialize tx and rx ring base addresses */
	ग_लिखोl((u32)lp->tx_ring_dma_addr, mmio + XMT_RING_BASE_ADDR0);
	ग_लिखोl((u32)lp->rx_ring_dma_addr, mmio + RCV_RING_BASE_ADDR0);

	ग_लिखोw((u32)NUM_TX_RING_DR, mmio + XMT_RING_LEN0);
	ग_लिखोw((u16)NUM_RX_RING_DR, mmio + RCV_RING_LEN0);

	/* set शेष IPG to 96 */
	ग_लिखोw((u32)DEFAULT_IPG, mmio + IPG);
	ग_लिखोw((u32)(DEFAULT_IPG-IFS1_DELTA), mmio + IFS1);

	अगर (lp->options & OPTION_JUMBO_ENABLE) अणु
		ग_लिखोl((u32)VAL2|JUMBO, mmio + CMD3);
		/* Reset REX_UFLO */
		ग_लिखोl(REX_UFLO, mmio + CMD2);
		/* Should not set REX_UFLO क्रम jumbo frames */
		ग_लिखोl(VAL0 | APAD_XMT | REX_RTRY, mmio + CMD2);
	पूर्ण अन्यथा अणु
		ग_लिखोl(VAL0 | APAD_XMT | REX_RTRY | REX_UFLO, mmio + CMD2);
		ग_लिखोl((u32)JUMBO, mmio + CMD3);
	पूर्ण

#अगर AMD8111E_VLAN_TAG_USED
	ग_लिखोl((u32)VAL2 | VSIZE | VL_TAG_DEL, mmio + CMD3);
#पूर्ण_अगर
	ग_लिखोl(VAL0 | APAD_XMT | REX_RTRY, mmio + CMD2);

	/* Setting the MAC address to the device */
	क्रम (i = 0; i < ETH_ALEN; i++)
		ग_लिखोb(dev->dev_addr[i], mmio + PADR + i);

	/* Enable पूर्णांकerrupt coalesce */
	अगर (lp->options & OPTION_INTR_COAL_ENABLE) अणु
		netdev_info(dev, "Interrupt Coalescing Enabled.\n");
		amd8111e_set_coalesce(dev, ENABLE_COAL);
	पूर्ण

	/* set RUN bit to start the chip */
	ग_लिखोl(VAL2 | RDMD0, mmio + CMD0);
	ग_लिखोl(VAL0 | INTREN | RUN, mmio + CMD0);

	/* To aव्योम PCI posting bug */
	पढ़ोl(mmio+CMD0);
	वापस 0;
पूर्ण

/* This function clears necessary the device रेजिस्टरs. */
अटल व्योम amd8111e_init_hw_शेष(काष्ठा amd8111e_priv *lp)
अणु
	अचिन्हित पूर्णांक reg_val;
	अचिन्हित पूर्णांक logic_filter[2] = अणु0,पूर्ण;
	व्योम __iomem *mmio = lp->mmio;


	/* stop the chip */
	ग_लिखोl(RUN, mmio + CMD0);

	/* AUTOPOLL0 Register *//*TBD शेष value is 8100 in FPS */
	ग_लिखोw( 0x8100 | lp->ext_phy_addr, mmio + AUTOPOLL0);

	/* Clear RCV_RING_BASE_ADDR */
	ग_लिखोl(0, mmio + RCV_RING_BASE_ADDR0);

	/* Clear XMT_RING_BASE_ADDR */
	ग_लिखोl(0, mmio + XMT_RING_BASE_ADDR0);
	ग_लिखोl(0, mmio + XMT_RING_BASE_ADDR1);
	ग_लिखोl(0, mmio + XMT_RING_BASE_ADDR2);
	ग_लिखोl(0, mmio + XMT_RING_BASE_ADDR3);

	/* Clear CMD0  */
	ग_लिखोl(CMD0_CLEAR, mmio + CMD0);

	/* Clear CMD2 */
	ग_लिखोl(CMD2_CLEAR, mmio + CMD2);

	/* Clear CMD7 */
	ग_लिखोl(CMD7_CLEAR, mmio + CMD7);

	/* Clear DLY_INT_A and DLY_INT_B */
	ग_लिखोl(0x0, mmio + DLY_INT_A);
	ग_लिखोl(0x0, mmio + DLY_INT_B);

	/* Clear FLOW_CONTROL */
	ग_लिखोl(0x0, mmio + FLOW_CONTROL);

	/* Clear INT0  ग_लिखो 1 to clear रेजिस्टर */
	reg_val = पढ़ोl(mmio + INT0);
	ग_लिखोl(reg_val, mmio + INT0);

	/* Clear STVAL */
	ग_लिखोl(0x0, mmio + STVAL);

	/* Clear INTEN0 */
	ग_लिखोl(INTEN0_CLEAR, mmio + INTEN0);

	/* Clear LADRF */
	ग_लिखोl(0x0, mmio + LADRF);

	/* Set SRAM_SIZE & SRAM_BOUNDARY रेजिस्टरs  */
	ग_लिखोl(0x80010, mmio + SRAM_SIZE);

	/* Clear RCV_RING0_LEN */
	ग_लिखोl(0x0, mmio + RCV_RING_LEN0);

	/* Clear XMT_RING0/1/2/3_LEN */
	ग_लिखोl(0x0, mmio +  XMT_RING_LEN0);
	ग_लिखोl(0x0, mmio +  XMT_RING_LEN1);
	ग_लिखोl(0x0, mmio +  XMT_RING_LEN2);
	ग_लिखोl(0x0, mmio +  XMT_RING_LEN3);

	/* Clear XMT_RING_LIMIT */
	ग_लिखोl(0x0, mmio + XMT_RING_LIMIT);

	/* Clear MIB */
	ग_लिखोw(MIB_CLEAR, mmio + MIB_ADDR);

	/* Clear LARF */
	amd8111e_ग_लिखोq(*(u64 *)logic_filter, mmio + LADRF);

	/* SRAM_SIZE रेजिस्टर */
	reg_val = पढ़ोl(mmio + SRAM_SIZE);

	अगर (lp->options & OPTION_JUMBO_ENABLE)
		ग_लिखोl(VAL2 | JUMBO, mmio + CMD3);
#अगर AMD8111E_VLAN_TAG_USED
	ग_लिखोl(VAL2 | VSIZE | VL_TAG_DEL, mmio + CMD3);
#पूर्ण_अगर
	/* Set शेष value to CTRL1 Register */
	ग_लिखोl(CTRL1_DEFAULT, mmio + CTRL1);

	/* To aव्योम PCI posting bug */
	पढ़ोl(mmio + CMD2);

पूर्ण

/* This function disables the पूर्णांकerrupt and clears all the pending
 * पूर्णांकerrupts in INT0
 */
अटल व्योम amd8111e_disable_पूर्णांकerrupt(काष्ठा amd8111e_priv *lp)
अणु
	u32 पूर्णांकr0;

	/* Disable पूर्णांकerrupt */
	ग_लिखोl(INTREN, lp->mmio + CMD0);

	/* Clear INT0 */
	पूर्णांकr0 = पढ़ोl(lp->mmio + INT0);
	ग_लिखोl(पूर्णांकr0, lp->mmio + INT0);

	/* To aव्योम PCI posting bug */
	पढ़ोl(lp->mmio + INT0);

पूर्ण

/* This function stops the chip. */
अटल व्योम amd8111e_stop_chip(काष्ठा amd8111e_priv *lp)
अणु
	ग_लिखोl(RUN, lp->mmio + CMD0);

	/* To aव्योम PCI posting bug */
	पढ़ोl(lp->mmio + CMD0);
पूर्ण

/* This function मुक्तs the  transmiter and receiver descriptor rings. */
अटल व्योम amd8111e_मुक्त_ring(काष्ठा amd8111e_priv *lp)
अणु
	/* Free transmit and receive descriptor rings */
	अगर (lp->rx_ring) अणु
		dma_मुक्त_coherent(&lp->pci_dev->dev,
				  माप(काष्ठा amd8111e_rx_dr) * NUM_RX_RING_DR,
				  lp->rx_ring, lp->rx_ring_dma_addr);
		lp->rx_ring = शून्य;
	पूर्ण

	अगर (lp->tx_ring) अणु
		dma_मुक्त_coherent(&lp->pci_dev->dev,
				  माप(काष्ठा amd8111e_tx_dr) * NUM_TX_RING_DR,
				  lp->tx_ring, lp->tx_ring_dma_addr);

		lp->tx_ring = शून्य;
	पूर्ण

पूर्ण

/* This function will मुक्त all the transmit skbs that are actually
 * transmitted by the device. It will check the ownership of the
 * skb beक्रमe मुक्तing the skb.
 */
अटल पूर्णांक amd8111e_tx(काष्ठा net_device *dev)
अणु
	काष्ठा amd8111e_priv *lp = netdev_priv(dev);
	पूर्णांक tx_index;
	पूर्णांक status;
	/* Complete all the transmit packet */
	जबतक (lp->tx_complete_idx != lp->tx_idx) अणु
		tx_index =  lp->tx_complete_idx & TX_RING_DR_MOD_MASK;
		status = le16_to_cpu(lp->tx_ring[tx_index].tx_flags);

		अगर (status & OWN_BIT)
			अवरोध;	/* It still hasn't been Txed */

		lp->tx_ring[tx_index].buff_phy_addr = 0;

		/* We must मुक्त the original skb */
		अगर (lp->tx_skbuff[tx_index]) अणु
			dma_unmap_single(&lp->pci_dev->dev,
					 lp->tx_dma_addr[tx_index],
					 lp->tx_skbuff[tx_index]->len,
					 DMA_TO_DEVICE);
			dev_consume_skb_irq(lp->tx_skbuff[tx_index]);
			lp->tx_skbuff[tx_index] = शून्य;
			lp->tx_dma_addr[tx_index] = 0;
		पूर्ण
		lp->tx_complete_idx++;
		/*COAL update tx coalescing parameters */
		lp->coal_conf.tx_packets++;
		lp->coal_conf.tx_bytes +=
			le16_to_cpu(lp->tx_ring[tx_index].buff_count);

		अगर (netअगर_queue_stopped(dev) &&
			lp->tx_complete_idx > lp->tx_idx - NUM_TX_BUFFERS + 2) अणु
			/* The ring is no दीर्घer full, clear tbusy. */
			/* lp->tx_full = 0; */
			netअगर_wake_queue(dev);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/* This function handles the driver receive operation in polling mode */
अटल पूर्णांक amd8111e_rx_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा amd8111e_priv *lp = container_of(napi, काष्ठा amd8111e_priv, napi);
	काष्ठा net_device *dev = lp->amd8111e_net_dev;
	पूर्णांक rx_index = lp->rx_idx & RX_RING_DR_MOD_MASK;
	व्योम __iomem *mmio = lp->mmio;
	काष्ठा sk_buff *skb, *new_skb;
	पूर्णांक min_pkt_len, status;
	पूर्णांक num_rx_pkt = 0;
	लघु pkt_len;
#अगर AMD8111E_VLAN_TAG_USED
	लघु vtag;
#पूर्ण_अगर

	जबतक (num_rx_pkt < budget) अणु
		status = le16_to_cpu(lp->rx_ring[rx_index].rx_flags);
		अगर (status & OWN_BIT)
			अवरोध;

		/* There is a tricky error noted by John Murphy,
		 * <murf@perftech.com> to Russ Nelson: Even with
		 * full-sized * buffers it's possible क्रम a
		 * jabber packet to use two buffers, with only
		 * the last correctly noting the error.
		 */
		अगर (status & ERR_BIT) अणु
			/* resetting flags */
			lp->rx_ring[rx_index].rx_flags &= RESET_RX_FLAGS;
			जाओ err_next_pkt;
		पूर्ण
		/* check क्रम STP and ENP */
		अगर (!((status & STP_BIT) && (status & ENP_BIT))) अणु
			/* resetting flags */
			lp->rx_ring[rx_index].rx_flags &= RESET_RX_FLAGS;
			जाओ err_next_pkt;
		पूर्ण
		pkt_len = le16_to_cpu(lp->rx_ring[rx_index].msg_count) - 4;

#अगर AMD8111E_VLAN_TAG_USED
		vtag = status & TT_MASK;
		/* MAC will strip vlan tag */
		अगर (vtag != 0)
			min_pkt_len = MIN_PKT_LEN - 4;
			अन्यथा
#पूर्ण_अगर
			min_pkt_len = MIN_PKT_LEN;

		अगर (pkt_len < min_pkt_len) अणु
			lp->rx_ring[rx_index].rx_flags &= RESET_RX_FLAGS;
			lp->drv_rx_errors++;
			जाओ err_next_pkt;
		पूर्ण
		new_skb = netdev_alloc_skb(dev, lp->rx_buff_len);
		अगर (!new_skb) अणु
			/* अगर allocation fail,
			 * ignore that pkt and go to next one
			 */
			lp->rx_ring[rx_index].rx_flags &= RESET_RX_FLAGS;
			lp->drv_rx_errors++;
			जाओ err_next_pkt;
		पूर्ण

		skb_reserve(new_skb, 2);
		skb = lp->rx_skbuff[rx_index];
		dma_unmap_single(&lp->pci_dev->dev, lp->rx_dma_addr[rx_index],
				 lp->rx_buff_len - 2, DMA_FROM_DEVICE);
		skb_put(skb, pkt_len);
		lp->rx_skbuff[rx_index] = new_skb;
		lp->rx_dma_addr[rx_index] = dma_map_single(&lp->pci_dev->dev,
							   new_skb->data,
							   lp->rx_buff_len - 2,
							   DMA_FROM_DEVICE);

		skb->protocol = eth_type_trans(skb, dev);

#अगर AMD8111E_VLAN_TAG_USED
		अगर (vtag == TT_VLAN_TAGGED) अणु
			u16 vlan_tag = le16_to_cpu(lp->rx_ring[rx_index].tag_ctrl_info);
			__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q), vlan_tag);
		पूर्ण
#पूर्ण_अगर
		napi_gro_receive(napi, skb);
		/* COAL update rx coalescing parameters */
		lp->coal_conf.rx_packets++;
		lp->coal_conf.rx_bytes += pkt_len;
		num_rx_pkt++;

err_next_pkt:
		lp->rx_ring[rx_index].buff_phy_addr
			= cpu_to_le32(lp->rx_dma_addr[rx_index]);
		lp->rx_ring[rx_index].buff_count =
			cpu_to_le16(lp->rx_buff_len-2);
		wmb();
		lp->rx_ring[rx_index].rx_flags |= cpu_to_le16(OWN_BIT);
		rx_index = (++lp->rx_idx) & RX_RING_DR_MOD_MASK;
	पूर्ण

	अगर (num_rx_pkt < budget && napi_complete_करोne(napi, num_rx_pkt)) अणु
		अचिन्हित दीर्घ flags;

		/* Receive descriptor is empty now */
		spin_lock_irqsave(&lp->lock, flags);
		ग_लिखोl(VAL0|RINTEN0, mmio + INTEN0);
		ग_लिखोl(VAL2 | RDMD0, mmio + CMD0);
		spin_unlock_irqrestore(&lp->lock, flags);
	पूर्ण

	वापस num_rx_pkt;
पूर्ण

/* This function will indicate the link status to the kernel. */
अटल पूर्णांक amd8111e_link_change(काष्ठा net_device *dev)
अणु
	काष्ठा amd8111e_priv *lp = netdev_priv(dev);
	पूर्णांक status0, speed;

	/* पढ़ो the link change */
	status0 = पढ़ोl(lp->mmio + STAT0);

	अगर (status0 & LINK_STATS) अणु
		अगर (status0 & AUTONEG_COMPLETE)
			lp->link_config.स्वतःneg = AUTONEG_ENABLE;
		अन्यथा
			lp->link_config.स्वतःneg = AUTONEG_DISABLE;

		अगर (status0 & FULL_DPLX)
			lp->link_config.duplex = DUPLEX_FULL;
		अन्यथा
			lp->link_config.duplex = DUPLEX_HALF;
		speed = (status0 & SPEED_MASK) >> 7;
		अगर (speed == PHY_SPEED_10)
			lp->link_config.speed = SPEED_10;
		अन्यथा अगर (speed == PHY_SPEED_100)
			lp->link_config.speed = SPEED_100;

		netdev_info(dev, "Link is Up. Speed is %s Mbps %s Duplex\n",
			    (lp->link_config.speed == SPEED_100) ?
							"100" : "10",
			    (lp->link_config.duplex == DUPLEX_FULL) ?
							"Full" : "Half");

		netअगर_carrier_on(dev);
	पूर्ण अन्यथा अणु
		lp->link_config.speed = SPEED_INVALID;
		lp->link_config.duplex = DUPLEX_INVALID;
		lp->link_config.स्वतःneg = AUTONEG_INVALID;
		netdev_info(dev, "Link is Down.\n");
		netअगर_carrier_off(dev);
	पूर्ण

	वापस 0;
पूर्ण

/* This function पढ़ोs the mib counters. */
अटल पूर्णांक amd8111e_पढ़ो_mib(व्योम __iomem *mmio, u8 MIB_COUNTER)
अणु
	अचिन्हित पूर्णांक  status;
	अचिन्हित  पूर्णांक data;
	अचिन्हित पूर्णांक repeat = REPEAT_CNT;

	ग_लिखोw(MIB_RD_CMD | MIB_COUNTER, mmio + MIB_ADDR);
	करो अणु
		status = पढ़ोw(mmio + MIB_ADDR);
		udelay(2);	/* controller takes MAX 2 us to get mib data */
	पूर्ण
	जबतक (--repeat && (status & MIB_CMD_ACTIVE));

	data = पढ़ोl(mmio + MIB_DATA);
	वापस data;
पूर्ण

/* This function पढ़ोs the mib रेजिस्टरs and वापसs the hardware statistics.
 * It updates previous पूर्णांकernal driver statistics with new values.
 */
अटल काष्ठा net_device_stats *amd8111e_get_stats(काष्ठा net_device *dev)
अणु
	काष्ठा amd8111e_priv *lp = netdev_priv(dev);
	व्योम __iomem *mmio = lp->mmio;
	अचिन्हित दीर्घ flags;
	काष्ठा net_device_stats *new_stats = &dev->stats;

	अगर (!lp->खोलोed)
		वापस new_stats;
	spin_lock_irqsave(&lp->lock, flags);

	/* stats.rx_packets */
	new_stats->rx_packets = amd8111e_पढ़ो_mib(mmio, rcv_broadcast_pkts)+
				amd8111e_पढ़ो_mib(mmio, rcv_multicast_pkts)+
				amd8111e_पढ़ो_mib(mmio, rcv_unicast_pkts);

	/* stats.tx_packets */
	new_stats->tx_packets = amd8111e_पढ़ो_mib(mmio, xmt_packets);

	/*stats.rx_bytes */
	new_stats->rx_bytes = amd8111e_पढ़ो_mib(mmio, rcv_octets);

	/* stats.tx_bytes */
	new_stats->tx_bytes = amd8111e_पढ़ो_mib(mmio, xmt_octets);

	/* stats.rx_errors */
	/* hw errors + errors driver reported */
	new_stats->rx_errors = amd8111e_पढ़ो_mib(mmio, rcv_undersize_pkts)+
				amd8111e_पढ़ो_mib(mmio, rcv_fragments)+
				amd8111e_पढ़ो_mib(mmio, rcv_jabbers)+
				amd8111e_पढ़ो_mib(mmio, rcv_alignment_errors)+
				amd8111e_पढ़ो_mib(mmio, rcv_fcs_errors)+
				amd8111e_पढ़ो_mib(mmio, rcv_miss_pkts)+
				lp->drv_rx_errors;

	/* stats.tx_errors */
	new_stats->tx_errors = amd8111e_पढ़ो_mib(mmio, xmt_underrun_pkts);

	/* stats.rx_dropped*/
	new_stats->rx_dropped = amd8111e_पढ़ो_mib(mmio, rcv_miss_pkts);

	/* stats.tx_dropped*/
	new_stats->tx_dropped = amd8111e_पढ़ो_mib(mmio,  xmt_underrun_pkts);

	/* stats.multicast*/
	new_stats->multicast = amd8111e_पढ़ो_mib(mmio, rcv_multicast_pkts);

	/* stats.collisions*/
	new_stats->collisions = amd8111e_पढ़ो_mib(mmio, xmt_collisions);

	/* stats.rx_length_errors*/
	new_stats->rx_length_errors =
		amd8111e_पढ़ो_mib(mmio, rcv_undersize_pkts)+
		amd8111e_पढ़ो_mib(mmio, rcv_oversize_pkts);

	/* stats.rx_over_errors*/
	new_stats->rx_over_errors = amd8111e_पढ़ो_mib(mmio, rcv_miss_pkts);

	/* stats.rx_crc_errors*/
	new_stats->rx_crc_errors = amd8111e_पढ़ो_mib(mmio, rcv_fcs_errors);

	/* stats.rx_frame_errors*/
	new_stats->rx_frame_errors =
		amd8111e_पढ़ो_mib(mmio, rcv_alignment_errors);

	/* stats.rx_fअगरo_errors */
	new_stats->rx_fअगरo_errors = amd8111e_पढ़ो_mib(mmio, rcv_miss_pkts);

	/* stats.rx_missed_errors */
	new_stats->rx_missed_errors = amd8111e_पढ़ो_mib(mmio, rcv_miss_pkts);

	/* stats.tx_पातed_errors*/
	new_stats->tx_पातed_errors =
		amd8111e_पढ़ो_mib(mmio, xmt_excessive_collision);

	/* stats.tx_carrier_errors*/
	new_stats->tx_carrier_errors =
		amd8111e_पढ़ो_mib(mmio, xmt_loss_carrier);

	/* stats.tx_fअगरo_errors*/
	new_stats->tx_fअगरo_errors = amd8111e_पढ़ो_mib(mmio, xmt_underrun_pkts);

	/* stats.tx_winकरोw_errors*/
	new_stats->tx_winकरोw_errors =
		amd8111e_पढ़ो_mib(mmio, xmt_late_collision);

	/* Reset the mibs क्रम collecting new statistics */
	/* ग_लिखोw(MIB_CLEAR, mmio + MIB_ADDR);*/

	spin_unlock_irqrestore(&lp->lock, flags);

	वापस new_stats;
पूर्ण

/* This function recalculate the पूर्णांकerrupt coalescing  mode on every पूर्णांकerrupt
 * according to the datarate and the packet rate.
 */
अटल पूर्णांक amd8111e_calc_coalesce(काष्ठा net_device *dev)
अणु
	काष्ठा amd8111e_priv *lp = netdev_priv(dev);
	काष्ठा amd8111e_coalesce_conf *coal_conf = &lp->coal_conf;
	पूर्णांक tx_pkt_rate;
	पूर्णांक rx_pkt_rate;
	पूर्णांक tx_data_rate;
	पूर्णांक rx_data_rate;
	पूर्णांक rx_pkt_size;
	पूर्णांक tx_pkt_size;

	tx_pkt_rate = coal_conf->tx_packets - coal_conf->tx_prev_packets;
	coal_conf->tx_prev_packets =  coal_conf->tx_packets;

	tx_data_rate = coal_conf->tx_bytes - coal_conf->tx_prev_bytes;
	coal_conf->tx_prev_bytes =  coal_conf->tx_bytes;

	rx_pkt_rate = coal_conf->rx_packets - coal_conf->rx_prev_packets;
	coal_conf->rx_prev_packets =  coal_conf->rx_packets;

	rx_data_rate = coal_conf->rx_bytes - coal_conf->rx_prev_bytes;
	coal_conf->rx_prev_bytes =  coal_conf->rx_bytes;

	अगर (rx_pkt_rate < 800) अणु
		अगर (coal_conf->rx_coal_type != NO_COALESCE) अणु

			coal_conf->rx_समयout = 0x0;
			coal_conf->rx_event_count = 0;
			amd8111e_set_coalesce(dev, RX_INTR_COAL);
			coal_conf->rx_coal_type = NO_COALESCE;
		पूर्ण
	पूर्ण अन्यथा अणु

		rx_pkt_size = rx_data_rate/rx_pkt_rate;
		अगर (rx_pkt_size < 128) अणु
			अगर (coal_conf->rx_coal_type != NO_COALESCE) अणु

				coal_conf->rx_समयout = 0;
				coal_conf->rx_event_count = 0;
				amd8111e_set_coalesce(dev, RX_INTR_COAL);
				coal_conf->rx_coal_type = NO_COALESCE;
			पूर्ण

		पूर्ण अन्यथा अगर ((rx_pkt_size >= 128) && (rx_pkt_size < 512)) अणु

			अगर (coal_conf->rx_coal_type !=  LOW_COALESCE) अणु
				coal_conf->rx_समयout = 1;
				coal_conf->rx_event_count = 4;
				amd8111e_set_coalesce(dev, RX_INTR_COAL);
				coal_conf->rx_coal_type = LOW_COALESCE;
			पूर्ण
		पूर्ण अन्यथा अगर ((rx_pkt_size >= 512) && (rx_pkt_size < 1024)) अणु

			अगर (coal_conf->rx_coal_type != MEDIUM_COALESCE) अणु
				coal_conf->rx_समयout = 1;
				coal_conf->rx_event_count = 4;
				amd8111e_set_coalesce(dev, RX_INTR_COAL);
				coal_conf->rx_coal_type = MEDIUM_COALESCE;
			पूर्ण

		पूर्ण अन्यथा अगर (rx_pkt_size >= 1024) अणु

			अगर (coal_conf->rx_coal_type !=  HIGH_COALESCE) अणु
				coal_conf->rx_समयout = 2;
				coal_conf->rx_event_count = 3;
				amd8111e_set_coalesce(dev, RX_INTR_COAL);
				coal_conf->rx_coal_type = HIGH_COALESCE;
			पूर्ण
		पूर्ण
	पूर्ण
	/* NOW FOR TX INTR COALESC */
	अगर (tx_pkt_rate < 800) अणु
		अगर (coal_conf->tx_coal_type != NO_COALESCE) अणु

			coal_conf->tx_समयout = 0x0;
			coal_conf->tx_event_count = 0;
			amd8111e_set_coalesce(dev, TX_INTR_COAL);
			coal_conf->tx_coal_type = NO_COALESCE;
		पूर्ण
	पूर्ण अन्यथा अणु

		tx_pkt_size = tx_data_rate/tx_pkt_rate;
		अगर (tx_pkt_size < 128) अणु

			अगर (coal_conf->tx_coal_type != NO_COALESCE) अणु

				coal_conf->tx_समयout = 0;
				coal_conf->tx_event_count = 0;
				amd8111e_set_coalesce(dev, TX_INTR_COAL);
				coal_conf->tx_coal_type = NO_COALESCE;
			पूर्ण

		पूर्ण अन्यथा अगर ((tx_pkt_size >= 128) && (tx_pkt_size < 512)) अणु

			अगर (coal_conf->tx_coal_type != LOW_COALESCE) अणु
				coal_conf->tx_समयout = 1;
				coal_conf->tx_event_count = 2;
				amd8111e_set_coalesce(dev, TX_INTR_COAL);
				coal_conf->tx_coal_type = LOW_COALESCE;

			पूर्ण
		पूर्ण अन्यथा अगर ((tx_pkt_size >= 512) && (tx_pkt_size < 1024)) अणु

			अगर (coal_conf->tx_coal_type != MEDIUM_COALESCE) अणु
				coal_conf->tx_समयout = 2;
				coal_conf->tx_event_count = 5;
				amd8111e_set_coalesce(dev, TX_INTR_COAL);
				coal_conf->tx_coal_type = MEDIUM_COALESCE;
			पूर्ण
		पूर्ण अन्यथा अगर (tx_pkt_size >= 1024) अणु
			अगर (coal_conf->tx_coal_type != HIGH_COALESCE) अणु
				coal_conf->tx_समयout = 4;
				coal_conf->tx_event_count = 8;
				amd8111e_set_coalesce(dev, TX_INTR_COAL);
				coal_conf->tx_coal_type = HIGH_COALESCE;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;

पूर्ण

/* This is device पूर्णांकerrupt function. It handles transmit,
 * receive,link change and hardware समयr पूर्णांकerrupts.
 */
अटल irqवापस_t amd8111e_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु

	काष्ठा net_device *dev = (काष्ठा net_device *)dev_id;
	काष्ठा amd8111e_priv *lp = netdev_priv(dev);
	व्योम __iomem *mmio = lp->mmio;
	अचिन्हित पूर्णांक पूर्णांकr0, पूर्णांकren0;
	अचिन्हित पूर्णांक handled = 1;

	अगर (unlikely(dev == शून्य))
		वापस IRQ_NONE;

	spin_lock(&lp->lock);

	/* disabling पूर्णांकerrupt */
	ग_लिखोl(INTREN, mmio + CMD0);

	/* Read पूर्णांकerrupt status */
	पूर्णांकr0 = पढ़ोl(mmio + INT0);
	पूर्णांकren0 = पढ़ोl(mmio + INTEN0);

	/* Process all the INT event until INTR bit is clear. */

	अगर (!(पूर्णांकr0 & INTR)) अणु
		handled = 0;
		जाओ err_no_पूर्णांकerrupt;
	पूर्ण

	/* Current driver processes 4 पूर्णांकerrupts : RINT,TINT,LCINT,STINT */
	ग_लिखोl(पूर्णांकr0, mmio + INT0);

	/* Check अगर Receive Interrupt has occurred. */
	अगर (पूर्णांकr0 & RINT0) अणु
		अगर (napi_schedule_prep(&lp->napi)) अणु
			/* Disable receive पूर्णांकerupts */
			ग_लिखोl(RINTEN0, mmio + INTEN0);
			/* Schedule a polling routine */
			__napi_schedule(&lp->napi);
		पूर्ण अन्यथा अगर (पूर्णांकren0 & RINTEN0) अणु
			netdev_dbg(dev, "************Driver bug! interrupt while in poll\n");
			/* Fix by disable receive पूर्णांकerrupts */
			ग_लिखोl(RINTEN0, mmio + INTEN0);
		पूर्ण
	पूर्ण

	/* Check अगर  Transmit Interrupt has occurred. */
	अगर (पूर्णांकr0 & TINT0)
		amd8111e_tx(dev);

	/* Check अगर  Link Change Interrupt has occurred. */
	अगर (पूर्णांकr0 & LCINT)
		amd8111e_link_change(dev);

	/* Check अगर Hardware Timer Interrupt has occurred. */
	अगर (पूर्णांकr0 & STINT)
		amd8111e_calc_coalesce(dev);

err_no_पूर्णांकerrupt:
	ग_लिखोl(VAL0 | INTREN, mmio + CMD0);

	spin_unlock(&lp->lock);

	वापस IRQ_RETVAL(handled);
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
अटल व्योम amd8111e_poll(काष्ठा net_device *dev)
अणु
	अचिन्हित दीर्घ flags;
	local_irq_save(flags);
	amd8111e_पूर्णांकerrupt(0, dev);
	local_irq_restore(flags);
पूर्ण
#पूर्ण_अगर


/* This function बंदs the network पूर्णांकerface and updates
 * the statistics so that most recent statistics will be
 * available after the पूर्णांकerface is करोwn.
 */
अटल पूर्णांक amd8111e_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा amd8111e_priv *lp = netdev_priv(dev);
	netअगर_stop_queue(dev);

	napi_disable(&lp->napi);

	spin_lock_irq(&lp->lock);

	amd8111e_disable_पूर्णांकerrupt(lp);
	amd8111e_stop_chip(lp);

	/* Free transmit and receive skbs */
	amd8111e_मुक्त_skbs(lp->amd8111e_net_dev);

	netअगर_carrier_off(lp->amd8111e_net_dev);

	/* Delete ipg समयr */
	अगर (lp->options & OPTION_DYN_IPG_ENABLE)
		del_समयr_sync(&lp->ipg_data.ipg_समयr);

	spin_unlock_irq(&lp->lock);
	मुक्त_irq(dev->irq, dev);
	amd8111e_मुक्त_ring(lp);

	/* Update the statistics beक्रमe closing */
	amd8111e_get_stats(dev);
	lp->खोलोed = 0;
	वापस 0;
पूर्ण

/* This function खोलोs new पूर्णांकerface.It requests irq क्रम the device,
 * initializes the device,buffers and descriptors, and starts the device.
 */
अटल पूर्णांक amd8111e_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा amd8111e_priv *lp = netdev_priv(dev);

	अगर (dev->irq == 0 || request_irq(dev->irq, amd8111e_पूर्णांकerrupt,
					 IRQF_SHARED, dev->name, dev))
		वापस -EAGAIN;

	napi_enable(&lp->napi);

	spin_lock_irq(&lp->lock);

	amd8111e_init_hw_शेष(lp);

	अगर (amd8111e_restart(dev)) अणु
		spin_unlock_irq(&lp->lock);
		napi_disable(&lp->napi);
		अगर (dev->irq)
			मुक्त_irq(dev->irq, dev);
		वापस -ENOMEM;
	पूर्ण
	/* Start ipg समयr */
	अगर (lp->options & OPTION_DYN_IPG_ENABLE) अणु
		add_समयr(&lp->ipg_data.ipg_समयr);
		netdev_info(dev, "Dynamic IPG Enabled\n");
	पूर्ण

	lp->खोलोed = 1;

	spin_unlock_irq(&lp->lock);

	netअगर_start_queue(dev);

	वापस 0;
पूर्ण

/* This function checks अगर there is any transmit  descriptors
 * available to queue more packet.
 */
अटल पूर्णांक amd8111e_tx_queue_avail(काष्ठा amd8111e_priv *lp)
अणु
	पूर्णांक tx_index = lp->tx_idx & TX_BUFF_MOD_MASK;
	अगर (lp->tx_skbuff[tx_index])
		वापस -1;
	अन्यथा
		वापस 0;

पूर्ण

/* This function will queue the transmit packets to the
 * descriptors and will trigger the send operation. It also
 * initializes the transmit descriptors with buffer physical address,
 * byte count, ownership to hardware etc.
 */
अटल netdev_tx_t amd8111e_start_xmit(काष्ठा sk_buff *skb,
				       काष्ठा net_device *dev)
अणु
	काष्ठा amd8111e_priv *lp = netdev_priv(dev);
	पूर्णांक tx_index;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&lp->lock, flags);

	tx_index = lp->tx_idx & TX_RING_DR_MOD_MASK;

	lp->tx_ring[tx_index].buff_count = cpu_to_le16(skb->len);

	lp->tx_skbuff[tx_index] = skb;
	lp->tx_ring[tx_index].tx_flags = 0;

#अगर AMD8111E_VLAN_TAG_USED
	अगर (skb_vlan_tag_present(skb)) अणु
		lp->tx_ring[tx_index].tag_ctrl_cmd |=
				cpu_to_le16(TCC_VLAN_INSERT);
		lp->tx_ring[tx_index].tag_ctrl_info =
				cpu_to_le16(skb_vlan_tag_get(skb));

	पूर्ण
#पूर्ण_अगर
	lp->tx_dma_addr[tx_index] =
	    dma_map_single(&lp->pci_dev->dev, skb->data, skb->len,
			   DMA_TO_DEVICE);
	lp->tx_ring[tx_index].buff_phy_addr =
	    cpu_to_le32(lp->tx_dma_addr[tx_index]);

	/*  Set FCS and LTINT bits */
	wmb();
	lp->tx_ring[tx_index].tx_flags |=
	    cpu_to_le16(OWN_BIT | STP_BIT | ENP_BIT|ADD_FCS_BIT|LTINT_BIT);

	lp->tx_idx++;

	/* Trigger an immediate send poll. */
	ग_लिखोl(VAL1 | TDMD0, lp->mmio + CMD0);
	ग_लिखोl(VAL2 | RDMD0, lp->mmio + CMD0);

	अगर (amd8111e_tx_queue_avail(lp) < 0) अणु
		netअगर_stop_queue(dev);
	पूर्ण
	spin_unlock_irqrestore(&lp->lock, flags);
	वापस NETDEV_TX_OK;
पूर्ण
/* This function वापसs all the memory mapped रेजिस्टरs of the device. */
अटल व्योम amd8111e_पढ़ो_regs(काष्ठा amd8111e_priv *lp, u32 *buf)
अणु
	व्योम __iomem *mmio = lp->mmio;
	/* Read only necessary रेजिस्टरs */
	buf[0] = पढ़ोl(mmio + XMT_RING_BASE_ADDR0);
	buf[1] = पढ़ोl(mmio + XMT_RING_LEN0);
	buf[2] = पढ़ोl(mmio + RCV_RING_BASE_ADDR0);
	buf[3] = पढ़ोl(mmio + RCV_RING_LEN0);
	buf[4] = पढ़ोl(mmio + CMD0);
	buf[5] = पढ़ोl(mmio + CMD2);
	buf[6] = पढ़ोl(mmio + CMD3);
	buf[7] = पढ़ोl(mmio + CMD7);
	buf[8] = पढ़ोl(mmio + INT0);
	buf[9] = पढ़ोl(mmio + INTEN0);
	buf[10] = पढ़ोl(mmio + LADRF);
	buf[11] = पढ़ोl(mmio + LADRF+4);
	buf[12] = पढ़ोl(mmio + STAT0);
पूर्ण


/* This function sets promiscuos mode, all-multi mode or the multicast address
 * list to the device.
 */
अटल व्योम amd8111e_set_multicast_list(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_hw_addr *ha;
	काष्ठा amd8111e_priv *lp = netdev_priv(dev);
	u32 mc_filter[2];
	पूर्णांक bit_num;

	अगर (dev->flags & IFF_PROMISC) अणु
		ग_लिखोl(VAL2 | PROM, lp->mmio + CMD2);
		वापस;
	पूर्ण
	अन्यथा
		ग_लिखोl(PROM, lp->mmio + CMD2);
	अगर (dev->flags & IFF_ALLMULTI ||
	    netdev_mc_count(dev) > MAX_FILTER_SIZE) अणु
		/* get all multicast packet */
		mc_filter[1] = mc_filter[0] = 0xffffffff;
		lp->options |= OPTION_MULTICAST_ENABLE;
		amd8111e_ग_लिखोq(*(u64 *)mc_filter, lp->mmio + LADRF);
		वापस;
	पूर्ण
	अगर (netdev_mc_empty(dev)) अणु
		/* get only own packets */
		mc_filter[1] = mc_filter[0] = 0;
		lp->options &= ~OPTION_MULTICAST_ENABLE;
		amd8111e_ग_लिखोq(*(u64 *)mc_filter, lp->mmio + LADRF);
		/* disable promiscuous mode */
		ग_लिखोl(PROM, lp->mmio + CMD2);
		वापस;
	पूर्ण
	/* load all the multicast addresses in the logic filter */
	lp->options |= OPTION_MULTICAST_ENABLE;
	mc_filter[1] = mc_filter[0] = 0;
	netdev_क्रम_each_mc_addr(ha, dev) अणु
		bit_num = (ether_crc_le(ETH_ALEN, ha->addr) >> 26) & 0x3f;
		mc_filter[bit_num >> 5] |= 1 << (bit_num & 31);
	पूर्ण
	amd8111e_ग_लिखोq(*(u64 *)mc_filter, lp->mmio + LADRF);

	/* To eliminate PCI posting bug */
	पढ़ोl(lp->mmio + CMD2);

पूर्ण

अटल व्योम amd8111e_get_drvinfo(काष्ठा net_device *dev,
				 काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा amd8111e_priv *lp = netdev_priv(dev);
	काष्ठा pci_dev *pci_dev = lp->pci_dev;
	strlcpy(info->driver, MODULE_NAME, माप(info->driver));
	snम_लिखो(info->fw_version, माप(info->fw_version),
		"%u", chip_version);
	strlcpy(info->bus_info, pci_name(pci_dev), माप(info->bus_info));
पूर्ण

अटल पूर्णांक amd8111e_get_regs_len(काष्ठा net_device *dev)
अणु
	वापस AMD8111E_REG_DUMP_LEN;
पूर्ण

अटल व्योम amd8111e_get_regs(काष्ठा net_device *dev, काष्ठा ethtool_regs *regs, व्योम *buf)
अणु
	काष्ठा amd8111e_priv *lp = netdev_priv(dev);
	regs->version = 0;
	amd8111e_पढ़ो_regs(lp, buf);
पूर्ण

अटल पूर्णांक amd8111e_get_link_ksettings(काष्ठा net_device *dev,
				       काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा amd8111e_priv *lp = netdev_priv(dev);
	spin_lock_irq(&lp->lock);
	mii_ethtool_get_link_ksettings(&lp->mii_अगर, cmd);
	spin_unlock_irq(&lp->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक amd8111e_set_link_ksettings(काष्ठा net_device *dev,
				       स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा amd8111e_priv *lp = netdev_priv(dev);
	पूर्णांक res;
	spin_lock_irq(&lp->lock);
	res = mii_ethtool_set_link_ksettings(&lp->mii_अगर, cmd);
	spin_unlock_irq(&lp->lock);
	वापस res;
पूर्ण

अटल पूर्णांक amd8111e_nway_reset(काष्ठा net_device *dev)
अणु
	काष्ठा amd8111e_priv *lp = netdev_priv(dev);
	वापस mii_nway_restart(&lp->mii_अगर);
पूर्ण

अटल u32 amd8111e_get_link(काष्ठा net_device *dev)
अणु
	काष्ठा amd8111e_priv *lp = netdev_priv(dev);
	वापस mii_link_ok(&lp->mii_अगर);
पूर्ण

अटल व्योम amd8111e_get_wol(काष्ठा net_device *dev, काष्ठा ethtool_wolinfo *wol_info)
अणु
	काष्ठा amd8111e_priv *lp = netdev_priv(dev);
	wol_info->supported = WAKE_MAGIC|WAKE_PHY;
	अगर (lp->options & OPTION_WOL_ENABLE)
		wol_info->wolopts = WAKE_MAGIC;
पूर्ण

अटल पूर्णांक amd8111e_set_wol(काष्ठा net_device *dev, काष्ठा ethtool_wolinfo *wol_info)
अणु
	काष्ठा amd8111e_priv *lp = netdev_priv(dev);
	अगर (wol_info->wolopts & ~(WAKE_MAGIC|WAKE_PHY))
		वापस -EINVAL;
	spin_lock_irq(&lp->lock);
	अगर (wol_info->wolopts & WAKE_MAGIC)
		lp->options |=
			(OPTION_WOL_ENABLE | OPTION_WAKE_MAGIC_ENABLE);
	अन्यथा अगर (wol_info->wolopts & WAKE_PHY)
		lp->options |=
			(OPTION_WOL_ENABLE | OPTION_WAKE_PHY_ENABLE);
	अन्यथा
		lp->options &= ~OPTION_WOL_ENABLE;
	spin_unlock_irq(&lp->lock);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops ops = अणु
	.get_drvinfo = amd8111e_get_drvinfo,
	.get_regs_len = amd8111e_get_regs_len,
	.get_regs = amd8111e_get_regs,
	.nway_reset = amd8111e_nway_reset,
	.get_link = amd8111e_get_link,
	.get_wol = amd8111e_get_wol,
	.set_wol = amd8111e_set_wol,
	.get_link_ksettings = amd8111e_get_link_ksettings,
	.set_link_ksettings = amd8111e_set_link_ksettings,
पूर्ण;

/* This function handles all the  ethtool ioctls. It gives driver info,
 * माला_लो/sets driver speed, माला_लो memory mapped रेजिस्टर values, क्रमces
 * स्वतः negotiation, sets/माला_लो WOL options क्रम ethtool application.
 */
अटल पूर्णांक amd8111e_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	काष्ठा mii_ioctl_data *data = अगर_mii(अगरr);
	काष्ठा amd8111e_priv *lp = netdev_priv(dev);
	पूर्णांक err;
	u32 mii_regval;

	चयन (cmd) अणु
	हाल SIOCGMIIPHY:
		data->phy_id = lp->ext_phy_addr;

		fallthrough;
	हाल SIOCGMIIREG:

		spin_lock_irq(&lp->lock);
		err = amd8111e_पढ़ो_phy(lp, data->phy_id,
			data->reg_num & PHY_REG_ADDR_MASK, &mii_regval);
		spin_unlock_irq(&lp->lock);

		data->val_out = mii_regval;
		वापस err;

	हाल SIOCSMIIREG:

		spin_lock_irq(&lp->lock);
		err = amd8111e_ग_लिखो_phy(lp, data->phy_id,
			data->reg_num & PHY_REG_ADDR_MASK, data->val_in);
		spin_unlock_irq(&lp->lock);

		वापस err;

	शेष:
		/* करो nothing */
		अवरोध;
	पूर्ण
	वापस -EOPNOTSUPP;
पूर्ण
अटल पूर्णांक amd8111e_set_mac_address(काष्ठा net_device *dev, व्योम *p)
अणु
	काष्ठा amd8111e_priv *lp = netdev_priv(dev);
	पूर्णांक i;
	काष्ठा sockaddr *addr = p;

	स_नकल(dev->dev_addr, addr->sa_data, dev->addr_len);
	spin_lock_irq(&lp->lock);
	/* Setting the MAC address to the device */
	क्रम (i = 0; i < ETH_ALEN; i++)
		ग_लिखोb(dev->dev_addr[i], lp->mmio + PADR + i);

	spin_unlock_irq(&lp->lock);

	वापस 0;
पूर्ण

/* This function changes the mtu of the device. It restarts the device  to
 * initialize the descriptor with new receive buffers.
 */
अटल पूर्णांक amd8111e_change_mtu(काष्ठा net_device *dev, पूर्णांक new_mtu)
अणु
	काष्ठा amd8111e_priv *lp = netdev_priv(dev);
	पूर्णांक err;

	अगर (!netअगर_running(dev)) अणु
		/* new_mtu will be used
		 * when device starts netxt समय
		 */
		dev->mtu = new_mtu;
		वापस 0;
	पूर्ण

	spin_lock_irq(&lp->lock);

	/* stop the chip */
	ग_लिखोl(RUN, lp->mmio + CMD0);

	dev->mtu = new_mtu;

	err = amd8111e_restart(dev);
	spin_unlock_irq(&lp->lock);
	अगर (!err)
		netअगर_start_queue(dev);
	वापस err;
पूर्ण

अटल पूर्णांक amd8111e_enable_magicpkt(काष्ठा amd8111e_priv *lp)
अणु
	ग_लिखोl(VAL1 | MPPLBA, lp->mmio + CMD3);
	ग_लिखोl(VAL0 | MPEN_SW, lp->mmio + CMD7);

	/* To eliminate PCI posting bug */
	पढ़ोl(lp->mmio + CMD7);
	वापस 0;
पूर्ण

अटल पूर्णांक amd8111e_enable_link_change(काष्ठा amd8111e_priv *lp)
अणु

	/* Adapter is alपढ़ोy stoped/suspended/पूर्णांकerrupt-disabled */
	ग_लिखोl(VAL0 | LCMODE_SW, lp->mmio + CMD7);

	/* To eliminate PCI posting bug */
	पढ़ोl(lp->mmio + CMD7);
	वापस 0;
पूर्ण

/* This function is called when a packet transmission fails to complete
 * within a reasonable period, on the assumption that an पूर्णांकerrupt have
 * failed or the पूर्णांकerface is locked up. This function will reinitialize
 * the hardware.
 */
अटल व्योम amd8111e_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा amd8111e_priv *lp = netdev_priv(dev);
	पूर्णांक err;

	netdev_err(dev, "transmit timed out, resetting\n");

	spin_lock_irq(&lp->lock);
	err = amd8111e_restart(dev);
	spin_unlock_irq(&lp->lock);
	अगर (!err)
		netअगर_wake_queue(dev);
पूर्ण

अटल पूर्णांक __maybe_unused amd8111e_suspend(काष्ठा device *dev_d)
अणु
	काष्ठा net_device *dev = dev_get_drvdata(dev_d);
	काष्ठा amd8111e_priv *lp = netdev_priv(dev);

	अगर (!netअगर_running(dev))
		वापस 0;

	/* disable the पूर्णांकerrupt */
	spin_lock_irq(&lp->lock);
	amd8111e_disable_पूर्णांकerrupt(lp);
	spin_unlock_irq(&lp->lock);

	netअगर_device_detach(dev);

	/* stop chip */
	spin_lock_irq(&lp->lock);
	अगर (lp->options & OPTION_DYN_IPG_ENABLE)
		del_समयr_sync(&lp->ipg_data.ipg_समयr);
	amd8111e_stop_chip(lp);
	spin_unlock_irq(&lp->lock);

	अगर (lp->options & OPTION_WOL_ENABLE) अणु
		 /* enable wol */
		अगर (lp->options & OPTION_WAKE_MAGIC_ENABLE)
			amd8111e_enable_magicpkt(lp);
		अगर (lp->options & OPTION_WAKE_PHY_ENABLE)
			amd8111e_enable_link_change(lp);

		device_set_wakeup_enable(dev_d, 1);

	पूर्ण अन्यथा अणु
		device_set_wakeup_enable(dev_d, 0);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused amd8111e_resume(काष्ठा device *dev_d)
अणु
	काष्ठा net_device *dev = dev_get_drvdata(dev_d);
	काष्ठा amd8111e_priv *lp = netdev_priv(dev);

	अगर (!netअगर_running(dev))
		वापस 0;

	netअगर_device_attach(dev);

	spin_lock_irq(&lp->lock);
	amd8111e_restart(dev);
	/* Restart ipg समयr */
	अगर (lp->options & OPTION_DYN_IPG_ENABLE)
		mod_समयr(&lp->ipg_data.ipg_समयr,
				jअगरfies + IPG_CONVERGE_JIFFIES);
	spin_unlock_irq(&lp->lock);

	वापस 0;
पूर्ण

अटल व्योम amd8111e_config_ipg(काष्ठा समयr_list *t)
अणु
	काष्ठा amd8111e_priv *lp = from_समयr(lp, t, ipg_data.ipg_समयr);
	काष्ठा ipg_info *ipg_data = &lp->ipg_data;
	व्योम __iomem *mmio = lp->mmio;
	अचिन्हित पूर्णांक prev_col_cnt = ipg_data->col_cnt;
	अचिन्हित पूर्णांक total_col_cnt;
	अचिन्हित पूर्णांक पंचांगp_ipg;

	अगर (lp->link_config.duplex == DUPLEX_FULL) अणु
		ipg_data->ipg = DEFAULT_IPG;
		वापस;
	पूर्ण

	अगर (ipg_data->ipg_state == SSTATE) अणु

		अगर (ipg_data->समयr_tick == IPG_STABLE_TIME) अणु

			ipg_data->समयr_tick = 0;
			ipg_data->ipg = MIN_IPG - IPG_STEP;
			ipg_data->current_ipg = MIN_IPG;
			ipg_data->dअगरf_col_cnt = 0xFFFFFFFF;
			ipg_data->ipg_state = CSTATE;
		पूर्ण
		अन्यथा
			ipg_data->समयr_tick++;
	पूर्ण

	अगर (ipg_data->ipg_state == CSTATE) अणु

		/* Get the current collision count */

		total_col_cnt = ipg_data->col_cnt =
				amd8111e_पढ़ो_mib(mmio, xmt_collisions);

		अगर ((total_col_cnt - prev_col_cnt) <
				(ipg_data->dअगरf_col_cnt)) अणु

			ipg_data->dअगरf_col_cnt =
				total_col_cnt - prev_col_cnt;

			ipg_data->ipg = ipg_data->current_ipg;
		पूर्ण

		ipg_data->current_ipg += IPG_STEP;

		अगर (ipg_data->current_ipg <= MAX_IPG)
			पंचांगp_ipg = ipg_data->current_ipg;
		अन्यथा अणु
			पंचांगp_ipg = ipg_data->ipg;
			ipg_data->ipg_state = SSTATE;
		पूर्ण
		ग_लिखोw((u32)पंचांगp_ipg, mmio + IPG);
		ग_लिखोw((u32)(पंचांगp_ipg - IFS1_DELTA), mmio + IFS1);
	पूर्ण
	mod_समयr(&lp->ipg_data.ipg_समयr, jअगरfies + IPG_CONVERGE_JIFFIES);
	वापस;

पूर्ण

अटल व्योम amd8111e_probe_ext_phy(काष्ठा net_device *dev)
अणु
	काष्ठा amd8111e_priv *lp = netdev_priv(dev);
	पूर्णांक i;

	क्रम (i = 0x1e; i >= 0; i--) अणु
		u32 id1, id2;

		अगर (amd8111e_पढ़ो_phy(lp, i, MII_PHYSID1, &id1))
			जारी;
		अगर (amd8111e_पढ़ो_phy(lp, i, MII_PHYSID2, &id2))
			जारी;
		lp->ext_phy_id = (id1 << 16) | id2;
		lp->ext_phy_addr = i;
		वापस;
	पूर्ण
	lp->ext_phy_id = 0;
	lp->ext_phy_addr = 1;
पूर्ण

अटल स्थिर काष्ठा net_device_ops amd8111e_netdev_ops = अणु
	.nकरो_खोलो		= amd8111e_खोलो,
	.nकरो_stop		= amd8111e_बंद,
	.nकरो_start_xmit		= amd8111e_start_xmit,
	.nकरो_tx_समयout		= amd8111e_tx_समयout,
	.nकरो_get_stats		= amd8111e_get_stats,
	.nकरो_set_rx_mode	= amd8111e_set_multicast_list,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_set_mac_address	= amd8111e_set_mac_address,
	.nकरो_करो_ioctl		= amd8111e_ioctl,
	.nकरो_change_mtu		= amd8111e_change_mtu,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller	 = amd8111e_poll,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक amd8111e_probe_one(काष्ठा pci_dev *pdev,
				  स्थिर काष्ठा pci_device_id *ent)
अणु
	पूर्णांक err, i;
	अचिन्हित दीर्घ reg_addr, reg_len;
	काष्ठा amd8111e_priv *lp;
	काष्ठा net_device *dev;

	err = pci_enable_device(pdev);
	अगर (err) अणु
		dev_err(&pdev->dev, "Cannot enable new PCI device\n");
		वापस err;
	पूर्ण

	अगर (!(pci_resource_flags(pdev, 0) & IORESOURCE_MEM)) अणु
		dev_err(&pdev->dev, "Cannot find PCI base address\n");
		err = -ENODEV;
		जाओ err_disable_pdev;
	पूर्ण

	err = pci_request_regions(pdev, MODULE_NAME);
	अगर (err) अणु
		dev_err(&pdev->dev, "Cannot obtain PCI resources\n");
		जाओ err_disable_pdev;
	पूर्ण

	pci_set_master(pdev);

	/* Find घातer-management capability. */
	अगर (!pdev->pm_cap) अणु
		dev_err(&pdev->dev, "No Power Management capability\n");
		err = -ENODEV;
		जाओ err_मुक्त_reg;
	पूर्ण

	/* Initialize DMA */
	अगर (dma_set_mask(&pdev->dev, DMA_BIT_MASK(32)) < 0) अणु
		dev_err(&pdev->dev, "DMA not supported\n");
		err = -ENODEV;
		जाओ err_मुक्त_reg;
	पूर्ण

	reg_addr = pci_resource_start(pdev, 0);
	reg_len = pci_resource_len(pdev, 0);

	dev = alloc_etherdev(माप(काष्ठा amd8111e_priv));
	अगर (!dev) अणु
		err = -ENOMEM;
		जाओ err_मुक्त_reg;
	पूर्ण

	SET_NETDEV_DEV(dev, &pdev->dev);

#अगर AMD8111E_VLAN_TAG_USED
	dev->features |= NETIF_F_HW_VLAN_CTAG_TX | NETIF_F_HW_VLAN_CTAG_RX;
#पूर्ण_अगर

	lp = netdev_priv(dev);
	lp->pci_dev = pdev;
	lp->amd8111e_net_dev = dev;
	lp->pm_cap = pdev->pm_cap;

	spin_lock_init(&lp->lock);

	lp->mmio = devm_ioremap(&pdev->dev, reg_addr, reg_len);
	अगर (!lp->mmio) अणु
		dev_err(&pdev->dev, "Cannot map device registers\n");
		err = -ENOMEM;
		जाओ err_मुक्त_dev;
	पूर्ण

	/* Initializing MAC address */
	क्रम (i = 0; i < ETH_ALEN; i++)
		dev->dev_addr[i] = पढ़ोb(lp->mmio + PADR + i);

	/* Setting user defined parametrs */
	lp->ext_phy_option = speed_duplex[card_idx];
	अगर (coalesce[card_idx])
		lp->options |= OPTION_INTR_COAL_ENABLE;
	अगर (dynamic_ipg[card_idx++])
		lp->options |= OPTION_DYN_IPG_ENABLE;


	/* Initialize driver entry poपूर्णांकs */
	dev->netdev_ops = &amd8111e_netdev_ops;
	dev->ethtool_ops = &ops;
	dev->irq = pdev->irq;
	dev->watchकरोg_समयo = AMD8111E_TX_TIMEOUT;
	dev->min_mtu = AMD8111E_MIN_MTU;
	dev->max_mtu = AMD8111E_MAX_MTU;
	netअगर_napi_add(dev, &lp->napi, amd8111e_rx_poll, 32);

#अगर AMD8111E_VLAN_TAG_USED
	dev->features |= NETIF_F_HW_VLAN_CTAG_TX | NETIF_F_HW_VLAN_CTAG_RX;
#पूर्ण_अगर
	/* Probe the बाह्यal PHY */
	amd8111e_probe_ext_phy(dev);

	/* setting mii शेष values */
	lp->mii_अगर.dev = dev;
	lp->mii_अगर.mdio_पढ़ो = amd8111e_mdio_पढ़ो;
	lp->mii_अगर.mdio_ग_लिखो = amd8111e_mdio_ग_लिखो;
	lp->mii_अगर.phy_id = lp->ext_phy_addr;

	/* Set receive buffer length and set jumbo option*/
	amd8111e_set_rx_buff_len(dev);


	err = रेजिस्टर_netdev(dev);
	अगर (err) अणु
		dev_err(&pdev->dev, "Cannot register net device\n");
		जाओ err_मुक्त_dev;
	पूर्ण

	pci_set_drvdata(pdev, dev);

	/* Initialize software ipg समयr */
	अगर (lp->options & OPTION_DYN_IPG_ENABLE) अणु
		समयr_setup(&lp->ipg_data.ipg_समयr, amd8111e_config_ipg, 0);
		lp->ipg_data.ipg_समयr.expires = jअगरfies +
						 IPG_CONVERGE_JIFFIES;
		lp->ipg_data.ipg = DEFAULT_IPG;
		lp->ipg_data.ipg_state = CSTATE;
	पूर्ण

	/*  display driver and device inक्रमmation */
	chip_version = (पढ़ोl(lp->mmio + CHIPID) & 0xf0000000) >> 28;
	dev_info(&pdev->dev, "[ Rev %x ] PCI 10/100BaseT Ethernet %pM\n",
		 chip_version, dev->dev_addr);
	अगर (lp->ext_phy_id)
		dev_info(&pdev->dev, "Found MII PHY ID 0x%08x at address 0x%02x\n",
			 lp->ext_phy_id, lp->ext_phy_addr);
	अन्यथा
		dev_info(&pdev->dev, "Couldn't detect MII PHY, assuming address 0x01\n");

	वापस 0;

err_मुक्त_dev:
	मुक्त_netdev(dev);

err_मुक्त_reg:
	pci_release_regions(pdev);

err_disable_pdev:
	pci_disable_device(pdev);
	वापस err;

पूर्ण

अटल व्योम amd8111e_हटाओ_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *dev = pci_get_drvdata(pdev);

	अगर (dev) अणु
		unरेजिस्टर_netdev(dev);
		मुक्त_netdev(dev);
		pci_release_regions(pdev);
		pci_disable_device(pdev);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा pci_device_id amd8111e_pci_tbl[] = अणु
	अणु
	 .venकरोr = PCI_VENDOR_ID_AMD,
	 .device = PCI_DEVICE_ID_AMD8111E_7462,
	पूर्ण,
	अणु
	 .venकरोr = 0,
	पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, amd8111e_pci_tbl);

अटल SIMPLE_DEV_PM_OPS(amd8111e_pm_ops, amd8111e_suspend, amd8111e_resume);

अटल काष्ठा pci_driver amd8111e_driver = अणु
	.name		= MODULE_NAME,
	.id_table	= amd8111e_pci_tbl,
	.probe		= amd8111e_probe_one,
	.हटाओ		= amd8111e_हटाओ_one,
	.driver.pm	= &amd8111e_pm_ops
पूर्ण;

module_pci_driver(amd8111e_driver);
