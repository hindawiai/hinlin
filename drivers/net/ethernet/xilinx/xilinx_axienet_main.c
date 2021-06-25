<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Xilinx Axi Ethernet device driver
 *
 * Copyright (c) 2008 Nissin Systems Co., Ltd.,  Yoshio Kashiwagi
 * Copyright (c) 2005-2008 DLA Systems,  David H. Lynch Jr. <dhlii@dlasys.net>
 * Copyright (c) 2008-2009 Secret Lab Technologies Ltd.
 * Copyright (c) 2010 - 2011 Michal Simek <monstr@monstr.eu>
 * Copyright (c) 2010 - 2011 PetaLogix
 * Copyright (c) 2019 SED Systems, a भागision of Calian Ltd.
 * Copyright (c) 2010 - 2012 Xilinx, Inc. All rights reserved.
 *
 * This is a driver क्रम the Xilinx Axi Ethernet which is used in the Virtex6
 * and Spartan6.
 *
 * TODO:
 *  - Add Axi Fअगरo support.
 *  - Factor out Axi DMA code पूर्णांकo separate driver.
 *  - Test and fix basic multicast filtering.
 *  - Add support क्रम extended multicast filtering.
 *  - Test basic VLAN support.
 *  - Add support क्रम extended VLAN support.
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/of_net.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_address.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/phy.h>
#समावेश <linux/mii.h>
#समावेश <linux/ethtool.h>

#समावेश "xilinx_axienet.h"

/* Descriptors defines क्रम Tx and Rx DMA */
#घोषणा TX_BD_NUM_DEFAULT		64
#घोषणा RX_BD_NUM_DEFAULT		1024
#घोषणा TX_BD_NUM_MAX			4096
#घोषणा RX_BD_NUM_MAX			4096

/* Must be लघुer than length of ethtool_drvinfo.driver field to fit */
#घोषणा DRIVER_NAME		"xaxienet"
#घोषणा DRIVER_DESCRIPTION	"Xilinx Axi Ethernet driver"
#घोषणा DRIVER_VERSION		"1.00a"

#घोषणा AXIENET_REGS_N		40

/* Match table क्रम of_platक्रमm binding */
अटल स्थिर काष्ठा of_device_id axienet_of_match[] = अणु
	अणु .compatible = "xlnx,axi-ethernet-1.00.a", पूर्ण,
	अणु .compatible = "xlnx,axi-ethernet-1.01.a", पूर्ण,
	अणु .compatible = "xlnx,axi-ethernet-2.01.a", पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, axienet_of_match);

/* Option table क्रम setting up Axi Ethernet hardware options */
अटल काष्ठा axienet_option axienet_options[] = अणु
	/* Turn on jumbo packet support क्रम both Rx and Tx */
	अणु
		.opt = XAE_OPTION_JUMBO,
		.reg = XAE_TC_OFFSET,
		.m_or = XAE_TC_JUM_MASK,
	पूर्ण, अणु
		.opt = XAE_OPTION_JUMBO,
		.reg = XAE_RCW1_OFFSET,
		.m_or = XAE_RCW1_JUM_MASK,
	पूर्ण, अणु /* Turn on VLAN packet support क्रम both Rx and Tx */
		.opt = XAE_OPTION_VLAN,
		.reg = XAE_TC_OFFSET,
		.m_or = XAE_TC_VLAN_MASK,
	पूर्ण, अणु
		.opt = XAE_OPTION_VLAN,
		.reg = XAE_RCW1_OFFSET,
		.m_or = XAE_RCW1_VLAN_MASK,
	पूर्ण, अणु /* Turn on FCS stripping on receive packets */
		.opt = XAE_OPTION_FCS_STRIP,
		.reg = XAE_RCW1_OFFSET,
		.m_or = XAE_RCW1_FCS_MASK,
	पूर्ण, अणु /* Turn on FCS insertion on transmit packets */
		.opt = XAE_OPTION_FCS_INSERT,
		.reg = XAE_TC_OFFSET,
		.m_or = XAE_TC_FCS_MASK,
	पूर्ण, अणु /* Turn off length/type field checking on receive packets */
		.opt = XAE_OPTION_LENTYPE_ERR,
		.reg = XAE_RCW1_OFFSET,
		.m_or = XAE_RCW1_LT_DIS_MASK,
	पूर्ण, अणु /* Turn on Rx flow control */
		.opt = XAE_OPTION_FLOW_CONTROL,
		.reg = XAE_FCC_OFFSET,
		.m_or = XAE_FCC_FCRX_MASK,
	पूर्ण, अणु /* Turn on Tx flow control */
		.opt = XAE_OPTION_FLOW_CONTROL,
		.reg = XAE_FCC_OFFSET,
		.m_or = XAE_FCC_FCTX_MASK,
	पूर्ण, अणु /* Turn on promiscuous frame filtering */
		.opt = XAE_OPTION_PROMISC,
		.reg = XAE_FMI_OFFSET,
		.m_or = XAE_FMI_PM_MASK,
	पूर्ण, अणु /* Enable transmitter */
		.opt = XAE_OPTION_TXEN,
		.reg = XAE_TC_OFFSET,
		.m_or = XAE_TC_TX_MASK,
	पूर्ण, अणु /* Enable receiver */
		.opt = XAE_OPTION_RXEN,
		.reg = XAE_RCW1_OFFSET,
		.m_or = XAE_RCW1_RX_MASK,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

/**
 * axienet_dma_in32 - Memory mapped Axi DMA रेजिस्टर पढ़ो
 * @lp:		Poपूर्णांकer to axienet local काष्ठाure
 * @reg:	Address offset from the base address of the Axi DMA core
 *
 * Return: The contents of the Axi DMA रेजिस्टर
 *
 * This function वापसs the contents of the corresponding Axi DMA रेजिस्टर.
 */
अटल अंतरभूत u32 axienet_dma_in32(काष्ठा axienet_local *lp, off_t reg)
अणु
	वापस ioपढ़ो32(lp->dma_regs + reg);
पूर्ण

/**
 * axienet_dma_out32 - Memory mapped Axi DMA रेजिस्टर ग_लिखो.
 * @lp:		Poपूर्णांकer to axienet local काष्ठाure
 * @reg:	Address offset from the base address of the Axi DMA core
 * @value:	Value to be written पूर्णांकo the Axi DMA रेजिस्टर
 *
 * This function ग_लिखोs the desired value पूर्णांकo the corresponding Axi DMA
 * रेजिस्टर.
 */
अटल अंतरभूत व्योम axienet_dma_out32(काष्ठा axienet_local *lp,
				     off_t reg, u32 value)
अणु
	ioग_लिखो32(value, lp->dma_regs + reg);
पूर्ण

अटल व्योम axienet_dma_out_addr(काष्ठा axienet_local *lp, off_t reg,
				 dma_addr_t addr)
अणु
	axienet_dma_out32(lp, reg, lower_32_bits(addr));

	अगर (lp->features & XAE_FEATURE_DMA_64BIT)
		axienet_dma_out32(lp, reg + 4, upper_32_bits(addr));
पूर्ण

अटल व्योम desc_set_phys_addr(काष्ठा axienet_local *lp, dma_addr_t addr,
			       काष्ठा axidma_bd *desc)
अणु
	desc->phys = lower_32_bits(addr);
	अगर (lp->features & XAE_FEATURE_DMA_64BIT)
		desc->phys_msb = upper_32_bits(addr);
पूर्ण

अटल dma_addr_t desc_get_phys_addr(काष्ठा axienet_local *lp,
				     काष्ठा axidma_bd *desc)
अणु
	dma_addr_t ret = desc->phys;

	अगर (lp->features & XAE_FEATURE_DMA_64BIT)
		ret |= ((dma_addr_t)desc->phys_msb << 16) << 16;

	वापस ret;
पूर्ण

/**
 * axienet_dma_bd_release - Release buffer descriptor rings
 * @ndev:	Poपूर्णांकer to the net_device काष्ठाure
 *
 * This function is used to release the descriptors allocated in
 * axienet_dma_bd_init. axienet_dma_bd_release is called when Axi Ethernet
 * driver stop api is called.
 */
अटल व्योम axienet_dma_bd_release(काष्ठा net_device *ndev)
अणु
	पूर्णांक i;
	काष्ठा axienet_local *lp = netdev_priv(ndev);

	/* If we end up here, tx_bd_v must have been DMA allocated. */
	dma_मुक्त_coherent(ndev->dev.parent,
			  माप(*lp->tx_bd_v) * lp->tx_bd_num,
			  lp->tx_bd_v,
			  lp->tx_bd_p);

	अगर (!lp->rx_bd_v)
		वापस;

	क्रम (i = 0; i < lp->rx_bd_num; i++) अणु
		dma_addr_t phys;

		/* A शून्य skb means this descriptor has not been initialised
		 * at all.
		 */
		अगर (!lp->rx_bd_v[i].skb)
			अवरोध;

		dev_kमुक्त_skb(lp->rx_bd_v[i].skb);

		/* For each descriptor, we programmed cntrl with the (non-zero)
		 * descriptor size, after it had been successfully allocated.
		 * So a non-zero value in there means we need to unmap it.
		 */
		अगर (lp->rx_bd_v[i].cntrl) अणु
			phys = desc_get_phys_addr(lp, &lp->rx_bd_v[i]);
			dma_unmap_single(ndev->dev.parent, phys,
					 lp->max_frm_size, DMA_FROM_DEVICE);
		पूर्ण
	पूर्ण

	dma_मुक्त_coherent(ndev->dev.parent,
			  माप(*lp->rx_bd_v) * lp->rx_bd_num,
			  lp->rx_bd_v,
			  lp->rx_bd_p);
पूर्ण

/**
 * axienet_dma_bd_init - Setup buffer descriptor rings क्रम Axi DMA
 * @ndev:	Poपूर्णांकer to the net_device काष्ठाure
 *
 * Return: 0, on success -ENOMEM, on failure
 *
 * This function is called to initialize the Rx and Tx DMA descriptor
 * rings. This initializes the descriptors with required शेष values
 * and is called when Axi Ethernet driver reset is called.
 */
अटल पूर्णांक axienet_dma_bd_init(काष्ठा net_device *ndev)
अणु
	u32 cr;
	पूर्णांक i;
	काष्ठा sk_buff *skb;
	काष्ठा axienet_local *lp = netdev_priv(ndev);

	/* Reset the indexes which are used क्रम accessing the BDs */
	lp->tx_bd_ci = 0;
	lp->tx_bd_tail = 0;
	lp->rx_bd_ci = 0;

	/* Allocate the Tx and Rx buffer descriptors. */
	lp->tx_bd_v = dma_alloc_coherent(ndev->dev.parent,
					 माप(*lp->tx_bd_v) * lp->tx_bd_num,
					 &lp->tx_bd_p, GFP_KERNEL);
	अगर (!lp->tx_bd_v)
		वापस -ENOMEM;

	lp->rx_bd_v = dma_alloc_coherent(ndev->dev.parent,
					 माप(*lp->rx_bd_v) * lp->rx_bd_num,
					 &lp->rx_bd_p, GFP_KERNEL);
	अगर (!lp->rx_bd_v)
		जाओ out;

	क्रम (i = 0; i < lp->tx_bd_num; i++) अणु
		dma_addr_t addr = lp->tx_bd_p +
				  माप(*lp->tx_bd_v) *
				  ((i + 1) % lp->tx_bd_num);

		lp->tx_bd_v[i].next = lower_32_bits(addr);
		अगर (lp->features & XAE_FEATURE_DMA_64BIT)
			lp->tx_bd_v[i].next_msb = upper_32_bits(addr);
	पूर्ण

	क्रम (i = 0; i < lp->rx_bd_num; i++) अणु
		dma_addr_t addr;

		addr = lp->rx_bd_p + माप(*lp->rx_bd_v) *
			((i + 1) % lp->rx_bd_num);
		lp->rx_bd_v[i].next = lower_32_bits(addr);
		अगर (lp->features & XAE_FEATURE_DMA_64BIT)
			lp->rx_bd_v[i].next_msb = upper_32_bits(addr);

		skb = netdev_alloc_skb_ip_align(ndev, lp->max_frm_size);
		अगर (!skb)
			जाओ out;

		lp->rx_bd_v[i].skb = skb;
		addr = dma_map_single(ndev->dev.parent, skb->data,
				      lp->max_frm_size, DMA_FROM_DEVICE);
		अगर (dma_mapping_error(ndev->dev.parent, addr)) अणु
			netdev_err(ndev, "DMA mapping error\n");
			जाओ out;
		पूर्ण
		desc_set_phys_addr(lp, addr, &lp->rx_bd_v[i]);

		lp->rx_bd_v[i].cntrl = lp->max_frm_size;
	पूर्ण

	/* Start updating the Rx channel control रेजिस्टर */
	cr = axienet_dma_in32(lp, XAXIDMA_RX_CR_OFFSET);
	/* Update the पूर्णांकerrupt coalesce count */
	cr = ((cr & ~XAXIDMA_COALESCE_MASK) |
	      ((lp->coalesce_count_rx) << XAXIDMA_COALESCE_SHIFT));
	/* Update the delay समयr count */
	cr = ((cr & ~XAXIDMA_DELAY_MASK) |
	      (XAXIDMA_DFT_RX_WAITBOUND << XAXIDMA_DELAY_SHIFT));
	/* Enable coalesce, delay समयr and error पूर्णांकerrupts */
	cr |= XAXIDMA_IRQ_ALL_MASK;
	/* Write to the Rx channel control रेजिस्टर */
	axienet_dma_out32(lp, XAXIDMA_RX_CR_OFFSET, cr);

	/* Start updating the Tx channel control रेजिस्टर */
	cr = axienet_dma_in32(lp, XAXIDMA_TX_CR_OFFSET);
	/* Update the पूर्णांकerrupt coalesce count */
	cr = (((cr & ~XAXIDMA_COALESCE_MASK)) |
	      ((lp->coalesce_count_tx) << XAXIDMA_COALESCE_SHIFT));
	/* Update the delay समयr count */
	cr = (((cr & ~XAXIDMA_DELAY_MASK)) |
	      (XAXIDMA_DFT_TX_WAITBOUND << XAXIDMA_DELAY_SHIFT));
	/* Enable coalesce, delay समयr and error पूर्णांकerrupts */
	cr |= XAXIDMA_IRQ_ALL_MASK;
	/* Write to the Tx channel control रेजिस्टर */
	axienet_dma_out32(lp, XAXIDMA_TX_CR_OFFSET, cr);

	/* Populate the tail poपूर्णांकer and bring the Rx Axi DMA engine out of
	 * halted state. This will make the Rx side पढ़ोy क्रम reception.
	 */
	axienet_dma_out_addr(lp, XAXIDMA_RX_CDESC_OFFSET, lp->rx_bd_p);
	cr = axienet_dma_in32(lp, XAXIDMA_RX_CR_OFFSET);
	axienet_dma_out32(lp, XAXIDMA_RX_CR_OFFSET,
			  cr | XAXIDMA_CR_RUNSTOP_MASK);
	axienet_dma_out_addr(lp, XAXIDMA_RX_TDESC_OFFSET, lp->rx_bd_p +
			     (माप(*lp->rx_bd_v) * (lp->rx_bd_num - 1)));

	/* Write to the RS (Run-stop) bit in the Tx channel control रेजिस्टर.
	 * Tx channel is now पढ़ोy to run. But only after we ग_लिखो to the
	 * tail poपूर्णांकer रेजिस्टर that the Tx channel will start transmitting.
	 */
	axienet_dma_out_addr(lp, XAXIDMA_TX_CDESC_OFFSET, lp->tx_bd_p);
	cr = axienet_dma_in32(lp, XAXIDMA_TX_CR_OFFSET);
	axienet_dma_out32(lp, XAXIDMA_TX_CR_OFFSET,
			  cr | XAXIDMA_CR_RUNSTOP_MASK);

	वापस 0;
out:
	axienet_dma_bd_release(ndev);
	वापस -ENOMEM;
पूर्ण

/**
 * axienet_set_mac_address - Write the MAC address
 * @ndev:	Poपूर्णांकer to the net_device काष्ठाure
 * @address:	6 byte Address to be written as MAC address
 *
 * This function is called to initialize the MAC address of the Axi Ethernet
 * core. It ग_लिखोs to the UAW0 and UAW1 रेजिस्टरs of the core.
 */
अटल व्योम axienet_set_mac_address(काष्ठा net_device *ndev,
				    स्थिर व्योम *address)
अणु
	काष्ठा axienet_local *lp = netdev_priv(ndev);

	अगर (address)
		स_नकल(ndev->dev_addr, address, ETH_ALEN);
	अगर (!is_valid_ether_addr(ndev->dev_addr))
		eth_hw_addr_अक्रमom(ndev);

	/* Set up unicast MAC address filter set its mac address */
	axienet_iow(lp, XAE_UAW0_OFFSET,
		    (ndev->dev_addr[0]) |
		    (ndev->dev_addr[1] << 8) |
		    (ndev->dev_addr[2] << 16) |
		    (ndev->dev_addr[3] << 24));
	axienet_iow(lp, XAE_UAW1_OFFSET,
		    (((axienet_ior(lp, XAE_UAW1_OFFSET)) &
		      ~XAE_UAW1_UNICASTADDR_MASK) |
		     (ndev->dev_addr[4] |
		     (ndev->dev_addr[5] << 8))));
पूर्ण

/**
 * netdev_set_mac_address - Write the MAC address (from outside the driver)
 * @ndev:	Poपूर्णांकer to the net_device काष्ठाure
 * @p:		6 byte Address to be written as MAC address
 *
 * Return: 0 क्रम all conditions. Presently, there is no failure हाल.
 *
 * This function is called to initialize the MAC address of the Axi Ethernet
 * core. It calls the core specअगरic axienet_set_mac_address. This is the
 * function that goes पूर्णांकo net_device_ops काष्ठाure entry nकरो_set_mac_address.
 */
अटल पूर्णांक netdev_set_mac_address(काष्ठा net_device *ndev, व्योम *p)
अणु
	काष्ठा sockaddr *addr = p;
	axienet_set_mac_address(ndev, addr->sa_data);
	वापस 0;
पूर्ण

/**
 * axienet_set_multicast_list - Prepare the multicast table
 * @ndev:	Poपूर्णांकer to the net_device काष्ठाure
 *
 * This function is called to initialize the multicast table during
 * initialization. The Axi Ethernet basic multicast support has a four-entry
 * multicast table which is initialized here. Additionally this function
 * goes पूर्णांकo the net_device_ops काष्ठाure entry nकरो_set_multicast_list. This
 * means whenever the multicast table entries need to be updated this
 * function माला_लो called.
 */
अटल व्योम axienet_set_multicast_list(काष्ठा net_device *ndev)
अणु
	पूर्णांक i;
	u32 reg, af0reg, af1reg;
	काष्ठा axienet_local *lp = netdev_priv(ndev);

	अगर (ndev->flags & (IFF_ALLMULTI | IFF_PROMISC) ||
	    netdev_mc_count(ndev) > XAE_MULTICAST_CAM_TABLE_NUM) अणु
		/* We must make the kernel realize we had to move पूर्णांकo
		 * promiscuous mode. If it was a promiscuous mode request
		 * the flag is alपढ़ोy set. If not we set it.
		 */
		ndev->flags |= IFF_PROMISC;
		reg = axienet_ior(lp, XAE_FMI_OFFSET);
		reg |= XAE_FMI_PM_MASK;
		axienet_iow(lp, XAE_FMI_OFFSET, reg);
		dev_info(&ndev->dev, "Promiscuous mode enabled.\n");
	पूर्ण अन्यथा अगर (!netdev_mc_empty(ndev)) अणु
		काष्ठा netdev_hw_addr *ha;

		i = 0;
		netdev_क्रम_each_mc_addr(ha, ndev) अणु
			अगर (i >= XAE_MULTICAST_CAM_TABLE_NUM)
				अवरोध;

			af0reg = (ha->addr[0]);
			af0reg |= (ha->addr[1] << 8);
			af0reg |= (ha->addr[2] << 16);
			af0reg |= (ha->addr[3] << 24);

			af1reg = (ha->addr[4]);
			af1reg |= (ha->addr[5] << 8);

			reg = axienet_ior(lp, XAE_FMI_OFFSET) & 0xFFFFFF00;
			reg |= i;

			axienet_iow(lp, XAE_FMI_OFFSET, reg);
			axienet_iow(lp, XAE_AF0_OFFSET, af0reg);
			axienet_iow(lp, XAE_AF1_OFFSET, af1reg);
			i++;
		पूर्ण
	पूर्ण अन्यथा अणु
		reg = axienet_ior(lp, XAE_FMI_OFFSET);
		reg &= ~XAE_FMI_PM_MASK;

		axienet_iow(lp, XAE_FMI_OFFSET, reg);

		क्रम (i = 0; i < XAE_MULTICAST_CAM_TABLE_NUM; i++) अणु
			reg = axienet_ior(lp, XAE_FMI_OFFSET) & 0xFFFFFF00;
			reg |= i;

			axienet_iow(lp, XAE_FMI_OFFSET, reg);
			axienet_iow(lp, XAE_AF0_OFFSET, 0);
			axienet_iow(lp, XAE_AF1_OFFSET, 0);
		पूर्ण

		dev_info(&ndev->dev, "Promiscuous mode disabled.\n");
	पूर्ण
पूर्ण

/**
 * axienet_setoptions - Set an Axi Ethernet option
 * @ndev:	Poपूर्णांकer to the net_device काष्ठाure
 * @options:	Option to be enabled/disabled
 *
 * The Axi Ethernet core has multiple features which can be selectively turned
 * on or off. The typical options could be jumbo frame option, basic VLAN
 * option, promiscuous mode option etc. This function is used to set or clear
 * these options in the Axi Ethernet hardware. This is करोne through
 * axienet_option काष्ठाure .
 */
अटल व्योम axienet_setoptions(काष्ठा net_device *ndev, u32 options)
अणु
	पूर्णांक reg;
	काष्ठा axienet_local *lp = netdev_priv(ndev);
	काष्ठा axienet_option *tp = &axienet_options[0];

	जबतक (tp->opt) अणु
		reg = ((axienet_ior(lp, tp->reg)) & ~(tp->m_or));
		अगर (options & tp->opt)
			reg |= tp->m_or;
		axienet_iow(lp, tp->reg, reg);
		tp++;
	पूर्ण

	lp->options |= options;
पूर्ण

अटल पूर्णांक __axienet_device_reset(काष्ठा axienet_local *lp)
अणु
	u32 समयout;

	/* Reset Axi DMA. This would reset Axi Ethernet core as well. The reset
	 * process of Axi DMA takes a जबतक to complete as all pending
	 * commands/transfers will be flushed or completed during this
	 * reset process.
	 * Note that even though both TX and RX have their own reset रेजिस्टर,
	 * they both reset the entire DMA core, so only one needs to be used.
	 */
	axienet_dma_out32(lp, XAXIDMA_TX_CR_OFFSET, XAXIDMA_CR_RESET_MASK);
	समयout = DELAY_OF_ONE_MILLISEC;
	जबतक (axienet_dma_in32(lp, XAXIDMA_TX_CR_OFFSET) &
				XAXIDMA_CR_RESET_MASK) अणु
		udelay(1);
		अगर (--समयout == 0) अणु
			netdev_err(lp->ndev, "%s: DMA reset timeout!\n",
				   __func__);
			वापस -ETIMEDOUT;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * axienet_device_reset - Reset and initialize the Axi Ethernet hardware.
 * @ndev:	Poपूर्णांकer to the net_device काष्ठाure
 *
 * This function is called to reset and initialize the Axi Ethernet core. This
 * is typically called during initialization. It करोes a reset of the Axi DMA
 * Rx/Tx channels and initializes the Axi DMA BDs. Since Axi DMA reset lines
 * areconnected to Axi Ethernet reset lines, this in turn resets the Axi
 * Ethernet core. No separate hardware reset is करोne क्रम the Axi Ethernet
 * core.
 * Returns 0 on success or a negative error number otherwise.
 */
अटल पूर्णांक axienet_device_reset(काष्ठा net_device *ndev)
अणु
	u32 axienet_status;
	काष्ठा axienet_local *lp = netdev_priv(ndev);
	पूर्णांक ret;

	ret = __axienet_device_reset(lp);
	अगर (ret)
		वापस ret;

	lp->max_frm_size = XAE_MAX_VLAN_FRAME_SIZE;
	lp->options |= XAE_OPTION_VLAN;
	lp->options &= (~XAE_OPTION_JUMBO);

	अगर ((ndev->mtu > XAE_MTU) &&
		(ndev->mtu <= XAE_JUMBO_MTU)) अणु
		lp->max_frm_size = ndev->mtu + VLAN_ETH_HLEN +
					XAE_TRL_SIZE;

		अगर (lp->max_frm_size <= lp->rxmem)
			lp->options |= XAE_OPTION_JUMBO;
	पूर्ण

	ret = axienet_dma_bd_init(ndev);
	अगर (ret) अणु
		netdev_err(ndev, "%s: descriptor allocation failed\n",
			   __func__);
		वापस ret;
	पूर्ण

	axienet_status = axienet_ior(lp, XAE_RCW1_OFFSET);
	axienet_status &= ~XAE_RCW1_RX_MASK;
	axienet_iow(lp, XAE_RCW1_OFFSET, axienet_status);

	axienet_status = axienet_ior(lp, XAE_IP_OFFSET);
	अगर (axienet_status & XAE_INT_RXRJECT_MASK)
		axienet_iow(lp, XAE_IS_OFFSET, XAE_INT_RXRJECT_MASK);
	axienet_iow(lp, XAE_IE_OFFSET, lp->eth_irq > 0 ?
		    XAE_INT_RECV_ERROR_MASK : 0);

	axienet_iow(lp, XAE_FCC_OFFSET, XAE_FCC_FCRX_MASK);

	/* Sync शेष options with HW but leave receiver and
	 * transmitter disabled.
	 */
	axienet_setoptions(ndev, lp->options &
			   ~(XAE_OPTION_TXEN | XAE_OPTION_RXEN));
	axienet_set_mac_address(ndev, शून्य);
	axienet_set_multicast_list(ndev);
	axienet_setoptions(ndev, lp->options);

	netअगर_trans_update(ndev);

	वापस 0;
पूर्ण

/**
 * axienet_मुक्त_tx_chain - Clean up a series of linked TX descriptors.
 * @ndev:	Poपूर्णांकer to the net_device काष्ठाure
 * @first_bd:	Index of first descriptor to clean up
 * @nr_bds:	Number of descriptors to clean up, can be -1 अगर unknown.
 * @sizep:	Poपूर्णांकer to a u32 filled with the total sum of all bytes
 * 		in all cleaned-up descriptors. Ignored अगर शून्य.
 *
 * Would either be called after a successful transmit operation, or after
 * there was an error when setting up the chain.
 * Returns the number of descriptors handled.
 */
अटल पूर्णांक axienet_मुक्त_tx_chain(काष्ठा net_device *ndev, u32 first_bd,
				 पूर्णांक nr_bds, u32 *sizep)
अणु
	काष्ठा axienet_local *lp = netdev_priv(ndev);
	काष्ठा axidma_bd *cur_p;
	पूर्णांक max_bds = nr_bds;
	अचिन्हित पूर्णांक status;
	dma_addr_t phys;
	पूर्णांक i;

	अगर (max_bds == -1)
		max_bds = lp->tx_bd_num;

	क्रम (i = 0; i < max_bds; i++) अणु
		cur_p = &lp->tx_bd_v[(first_bd + i) % lp->tx_bd_num];
		status = cur_p->status;

		/* If no number is given, clean up *all* descriptors that have
		 * been completed by the MAC.
		 */
		अगर (nr_bds == -1 && !(status & XAXIDMA_BD_STS_COMPLETE_MASK))
			अवरोध;

		phys = desc_get_phys_addr(lp, cur_p);
		dma_unmap_single(ndev->dev.parent, phys,
				 (cur_p->cntrl & XAXIDMA_BD_CTRL_LENGTH_MASK),
				 DMA_TO_DEVICE);

		अगर (cur_p->skb && (status & XAXIDMA_BD_STS_COMPLETE_MASK))
			dev_consume_skb_irq(cur_p->skb);

		cur_p->cntrl = 0;
		cur_p->app0 = 0;
		cur_p->app1 = 0;
		cur_p->app2 = 0;
		cur_p->app4 = 0;
		cur_p->status = 0;
		cur_p->skb = शून्य;

		अगर (sizep)
			*sizep += status & XAXIDMA_BD_STS_ACTUAL_LEN_MASK;
	पूर्ण

	वापस i;
पूर्ण

/**
 * axienet_start_xmit_करोne - Invoked once a transmit is completed by the
 * Axi DMA Tx channel.
 * @ndev:	Poपूर्णांकer to the net_device काष्ठाure
 *
 * This function is invoked from the Axi DMA Tx isr to notअगरy the completion
 * of transmit operation. It clears fields in the corresponding Tx BDs and
 * unmaps the corresponding buffer so that CPU can regain ownership of the
 * buffer. It finally invokes "netif_wake_queue" to restart transmission अगर
 * required.
 */
अटल व्योम axienet_start_xmit_करोne(काष्ठा net_device *ndev)
अणु
	काष्ठा axienet_local *lp = netdev_priv(ndev);
	u32 packets = 0;
	u32 size = 0;

	packets = axienet_मुक्त_tx_chain(ndev, lp->tx_bd_ci, -1, &size);

	lp->tx_bd_ci += packets;
	अगर (lp->tx_bd_ci >= lp->tx_bd_num)
		lp->tx_bd_ci -= lp->tx_bd_num;

	ndev->stats.tx_packets += packets;
	ndev->stats.tx_bytes += size;

	/* Matches barrier in axienet_start_xmit */
	smp_mb();

	netअगर_wake_queue(ndev);
पूर्ण

/**
 * axienet_check_tx_bd_space - Checks अगर a BD/group of BDs are currently busy
 * @lp:		Poपूर्णांकer to the axienet_local काष्ठाure
 * @num_frag:	The number of BDs to check क्रम
 *
 * Return: 0, on success
 *	    NETDEV_TX_BUSY, अगर any of the descriptors are not मुक्त
 *
 * This function is invoked beक्रमe BDs are allocated and transmission starts.
 * This function वापसs 0 अगर a BD or group of BDs can be allocated क्रम
 * transmission. If the BD or any of the BDs are not मुक्त the function
 * वापसs a busy status. This is invoked from axienet_start_xmit.
 */
अटल अंतरभूत पूर्णांक axienet_check_tx_bd_space(काष्ठा axienet_local *lp,
					    पूर्णांक num_frag)
अणु
	काष्ठा axidma_bd *cur_p;
	cur_p = &lp->tx_bd_v[(lp->tx_bd_tail + num_frag) % lp->tx_bd_num];
	अगर (cur_p->status & XAXIDMA_BD_STS_ALL_MASK)
		वापस NETDEV_TX_BUSY;
	वापस 0;
पूर्ण

/**
 * axienet_start_xmit - Starts the transmission.
 * @skb:	sk_buff poपूर्णांकer that contains data to be Txed.
 * @ndev:	Poपूर्णांकer to net_device काष्ठाure.
 *
 * Return: NETDEV_TX_OK, on success
 *	    NETDEV_TX_BUSY, अगर any of the descriptors are not मुक्त
 *
 * This function is invoked from upper layers to initiate transmission. The
 * function uses the next available मुक्त BDs and populates their fields to
 * start the transmission. Additionally अगर checksum offloading is supported,
 * it populates AXI Stream Control fields with appropriate values.
 */
अटल netdev_tx_t
axienet_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *ndev)
अणु
	u32 ii;
	u32 num_frag;
	u32 csum_start_off;
	u32 csum_index_off;
	skb_frag_t *frag;
	dma_addr_t tail_p, phys;
	काष्ठा axienet_local *lp = netdev_priv(ndev);
	काष्ठा axidma_bd *cur_p;
	u32 orig_tail_ptr = lp->tx_bd_tail;

	num_frag = skb_shinfo(skb)->nr_frags;
	cur_p = &lp->tx_bd_v[lp->tx_bd_tail];

	अगर (axienet_check_tx_bd_space(lp, num_frag)) अणु
		अगर (netअगर_queue_stopped(ndev))
			वापस NETDEV_TX_BUSY;

		netअगर_stop_queue(ndev);

		/* Matches barrier in axienet_start_xmit_करोne */
		smp_mb();

		/* Space might have just been मुक्तd - check again */
		अगर (axienet_check_tx_bd_space(lp, num_frag))
			वापस NETDEV_TX_BUSY;

		netअगर_wake_queue(ndev);
	पूर्ण

	अगर (skb->ip_summed == CHECKSUM_PARTIAL) अणु
		अगर (lp->features & XAE_FEATURE_FULL_TX_CSUM) अणु
			/* Tx Full Checksum Offload Enabled */
			cur_p->app0 |= 2;
		पूर्ण अन्यथा अगर (lp->features & XAE_FEATURE_PARTIAL_RX_CSUM) अणु
			csum_start_off = skb_transport_offset(skb);
			csum_index_off = csum_start_off + skb->csum_offset;
			/* Tx Partial Checksum Offload Enabled */
			cur_p->app0 |= 1;
			cur_p->app1 = (csum_start_off << 16) | csum_index_off;
		पूर्ण
	पूर्ण अन्यथा अगर (skb->ip_summed == CHECKSUM_UNNECESSARY) अणु
		cur_p->app0 |= 2; /* Tx Full Checksum Offload Enabled */
	पूर्ण

	phys = dma_map_single(ndev->dev.parent, skb->data,
			      skb_headlen(skb), DMA_TO_DEVICE);
	अगर (unlikely(dma_mapping_error(ndev->dev.parent, phys))) अणु
		अगर (net_ratelimit())
			netdev_err(ndev, "TX DMA mapping error\n");
		ndev->stats.tx_dropped++;
		वापस NETDEV_TX_OK;
	पूर्ण
	desc_set_phys_addr(lp, phys, cur_p);
	cur_p->cntrl = skb_headlen(skb) | XAXIDMA_BD_CTRL_TXSOF_MASK;

	क्रम (ii = 0; ii < num_frag; ii++) अणु
		अगर (++lp->tx_bd_tail >= lp->tx_bd_num)
			lp->tx_bd_tail = 0;
		cur_p = &lp->tx_bd_v[lp->tx_bd_tail];
		frag = &skb_shinfo(skb)->frags[ii];
		phys = dma_map_single(ndev->dev.parent,
				      skb_frag_address(frag),
				      skb_frag_size(frag),
				      DMA_TO_DEVICE);
		अगर (unlikely(dma_mapping_error(ndev->dev.parent, phys))) अणु
			अगर (net_ratelimit())
				netdev_err(ndev, "TX DMA mapping error\n");
			ndev->stats.tx_dropped++;
			axienet_मुक्त_tx_chain(ndev, orig_tail_ptr, ii + 1,
					      शून्य);
			lp->tx_bd_tail = orig_tail_ptr;

			वापस NETDEV_TX_OK;
		पूर्ण
		desc_set_phys_addr(lp, phys, cur_p);
		cur_p->cntrl = skb_frag_size(frag);
	पूर्ण

	cur_p->cntrl |= XAXIDMA_BD_CTRL_TXखातापूर्ण_MASK;
	cur_p->skb = skb;

	tail_p = lp->tx_bd_p + माप(*lp->tx_bd_v) * lp->tx_bd_tail;
	/* Start the transfer */
	axienet_dma_out_addr(lp, XAXIDMA_TX_TDESC_OFFSET, tail_p);
	अगर (++lp->tx_bd_tail >= lp->tx_bd_num)
		lp->tx_bd_tail = 0;

	वापस NETDEV_TX_OK;
पूर्ण

/**
 * axienet_recv - Is called from Axi DMA Rx Isr to complete the received
 *		  BD processing.
 * @ndev:	Poपूर्णांकer to net_device काष्ठाure.
 *
 * This function is invoked from the Axi DMA Rx isr to process the Rx BDs. It
 * करोes minimal processing and invokes "netif_rx" to complete further
 * processing.
 */
अटल व्योम axienet_recv(काष्ठा net_device *ndev)
अणु
	u32 length;
	u32 csumstatus;
	u32 size = 0;
	u32 packets = 0;
	dma_addr_t tail_p = 0;
	काष्ठा axienet_local *lp = netdev_priv(ndev);
	काष्ठा sk_buff *skb, *new_skb;
	काष्ठा axidma_bd *cur_p;

	cur_p = &lp->rx_bd_v[lp->rx_bd_ci];

	जबतक ((cur_p->status & XAXIDMA_BD_STS_COMPLETE_MASK)) अणु
		dma_addr_t phys;

		tail_p = lp->rx_bd_p + माप(*lp->rx_bd_v) * lp->rx_bd_ci;

		phys = desc_get_phys_addr(lp, cur_p);
		dma_unmap_single(ndev->dev.parent, phys, lp->max_frm_size,
				 DMA_FROM_DEVICE);

		skb = cur_p->skb;
		cur_p->skb = शून्य;
		length = cur_p->app4 & 0x0000FFFF;

		skb_put(skb, length);
		skb->protocol = eth_type_trans(skb, ndev);
		/*skb_checksum_none_निश्चित(skb);*/
		skb->ip_summed = CHECKSUM_NONE;

		/* अगर we're करोing Rx csum offload, set it up */
		अगर (lp->features & XAE_FEATURE_FULL_RX_CSUM) अणु
			csumstatus = (cur_p->app2 &
				      XAE_FULL_CSUM_STATUS_MASK) >> 3;
			अगर ((csumstatus == XAE_IP_TCP_CSUM_VALIDATED) ||
			    (csumstatus == XAE_IP_UDP_CSUM_VALIDATED)) अणु
				skb->ip_summed = CHECKSUM_UNNECESSARY;
			पूर्ण
		पूर्ण अन्यथा अगर ((lp->features & XAE_FEATURE_PARTIAL_RX_CSUM) != 0 &&
			   skb->protocol == htons(ETH_P_IP) &&
			   skb->len > 64) अणु
			skb->csum = be32_to_cpu(cur_p->app3 & 0xFFFF);
			skb->ip_summed = CHECKSUM_COMPLETE;
		पूर्ण

		netअगर_rx(skb);

		size += length;
		packets++;

		new_skb = netdev_alloc_skb_ip_align(ndev, lp->max_frm_size);
		अगर (!new_skb)
			वापस;

		phys = dma_map_single(ndev->dev.parent, new_skb->data,
				      lp->max_frm_size,
				      DMA_FROM_DEVICE);
		अगर (unlikely(dma_mapping_error(ndev->dev.parent, phys))) अणु
			अगर (net_ratelimit())
				netdev_err(ndev, "RX DMA mapping error\n");
			dev_kमुक्त_skb(new_skb);
			वापस;
		पूर्ण
		desc_set_phys_addr(lp, phys, cur_p);

		cur_p->cntrl = lp->max_frm_size;
		cur_p->status = 0;
		cur_p->skb = new_skb;

		अगर (++lp->rx_bd_ci >= lp->rx_bd_num)
			lp->rx_bd_ci = 0;
		cur_p = &lp->rx_bd_v[lp->rx_bd_ci];
	पूर्ण

	ndev->stats.rx_packets += packets;
	ndev->stats.rx_bytes += size;

	अगर (tail_p)
		axienet_dma_out_addr(lp, XAXIDMA_RX_TDESC_OFFSET, tail_p);
पूर्ण

/**
 * axienet_tx_irq - Tx Done Isr.
 * @irq:	irq number
 * @_ndev:	net_device poपूर्णांकer
 *
 * Return: IRQ_HANDLED अगर device generated a TX पूर्णांकerrupt, IRQ_NONE otherwise.
 *
 * This is the Axi DMA Tx करोne Isr. It invokes "axienet_start_xmit_done"
 * to complete the BD processing.
 */
अटल irqवापस_t axienet_tx_irq(पूर्णांक irq, व्योम *_ndev)
अणु
	u32 cr;
	अचिन्हित पूर्णांक status;
	काष्ठा net_device *ndev = _ndev;
	काष्ठा axienet_local *lp = netdev_priv(ndev);

	status = axienet_dma_in32(lp, XAXIDMA_TX_SR_OFFSET);
	अगर (status & (XAXIDMA_IRQ_IOC_MASK | XAXIDMA_IRQ_DELAY_MASK)) अणु
		axienet_dma_out32(lp, XAXIDMA_TX_SR_OFFSET, status);
		axienet_start_xmit_करोne(lp->ndev);
		जाओ out;
	पूर्ण
	अगर (!(status & XAXIDMA_IRQ_ALL_MASK))
		वापस IRQ_NONE;
	अगर (status & XAXIDMA_IRQ_ERROR_MASK) अणु
		dev_err(&ndev->dev, "DMA Tx error 0x%x\n", status);
		dev_err(&ndev->dev, "Current BD is at: 0x%x%08x\n",
			(lp->tx_bd_v[lp->tx_bd_ci]).phys_msb,
			(lp->tx_bd_v[lp->tx_bd_ci]).phys);

		cr = axienet_dma_in32(lp, XAXIDMA_TX_CR_OFFSET);
		/* Disable coalesce, delay समयr and error पूर्णांकerrupts */
		cr &= (~XAXIDMA_IRQ_ALL_MASK);
		/* Write to the Tx channel control रेजिस्टर */
		axienet_dma_out32(lp, XAXIDMA_TX_CR_OFFSET, cr);

		cr = axienet_dma_in32(lp, XAXIDMA_RX_CR_OFFSET);
		/* Disable coalesce, delay समयr and error पूर्णांकerrupts */
		cr &= (~XAXIDMA_IRQ_ALL_MASK);
		/* Write to the Rx channel control रेजिस्टर */
		axienet_dma_out32(lp, XAXIDMA_RX_CR_OFFSET, cr);

		schedule_work(&lp->dma_err_task);
		axienet_dma_out32(lp, XAXIDMA_TX_SR_OFFSET, status);
	पूर्ण
out:
	वापस IRQ_HANDLED;
पूर्ण

/**
 * axienet_rx_irq - Rx Isr.
 * @irq:	irq number
 * @_ndev:	net_device poपूर्णांकer
 *
 * Return: IRQ_HANDLED अगर device generated a RX पूर्णांकerrupt, IRQ_NONE otherwise.
 *
 * This is the Axi DMA Rx Isr. It invokes "axienet_recv" to complete the BD
 * processing.
 */
अटल irqवापस_t axienet_rx_irq(पूर्णांक irq, व्योम *_ndev)
अणु
	u32 cr;
	अचिन्हित पूर्णांक status;
	काष्ठा net_device *ndev = _ndev;
	काष्ठा axienet_local *lp = netdev_priv(ndev);

	status = axienet_dma_in32(lp, XAXIDMA_RX_SR_OFFSET);
	अगर (status & (XAXIDMA_IRQ_IOC_MASK | XAXIDMA_IRQ_DELAY_MASK)) अणु
		axienet_dma_out32(lp, XAXIDMA_RX_SR_OFFSET, status);
		axienet_recv(lp->ndev);
		जाओ out;
	पूर्ण
	अगर (!(status & XAXIDMA_IRQ_ALL_MASK))
		वापस IRQ_NONE;
	अगर (status & XAXIDMA_IRQ_ERROR_MASK) अणु
		dev_err(&ndev->dev, "DMA Rx error 0x%x\n", status);
		dev_err(&ndev->dev, "Current BD is at: 0x%x%08x\n",
			(lp->rx_bd_v[lp->rx_bd_ci]).phys_msb,
			(lp->rx_bd_v[lp->rx_bd_ci]).phys);

		cr = axienet_dma_in32(lp, XAXIDMA_TX_CR_OFFSET);
		/* Disable coalesce, delay समयr and error पूर्णांकerrupts */
		cr &= (~XAXIDMA_IRQ_ALL_MASK);
		/* Finally ग_लिखो to the Tx channel control रेजिस्टर */
		axienet_dma_out32(lp, XAXIDMA_TX_CR_OFFSET, cr);

		cr = axienet_dma_in32(lp, XAXIDMA_RX_CR_OFFSET);
		/* Disable coalesce, delay समयr and error पूर्णांकerrupts */
		cr &= (~XAXIDMA_IRQ_ALL_MASK);
		/* ग_लिखो to the Rx channel control रेजिस्टर */
		axienet_dma_out32(lp, XAXIDMA_RX_CR_OFFSET, cr);

		schedule_work(&lp->dma_err_task);
		axienet_dma_out32(lp, XAXIDMA_RX_SR_OFFSET, status);
	पूर्ण
out:
	वापस IRQ_HANDLED;
पूर्ण

/**
 * axienet_eth_irq - Ethernet core Isr.
 * @irq:	irq number
 * @_ndev:	net_device poपूर्णांकer
 *
 * Return: IRQ_HANDLED अगर device generated a core पूर्णांकerrupt, IRQ_NONE otherwise.
 *
 * Handle miscellaneous conditions indicated by Ethernet core IRQ.
 */
अटल irqवापस_t axienet_eth_irq(पूर्णांक irq, व्योम *_ndev)
अणु
	काष्ठा net_device *ndev = _ndev;
	काष्ठा axienet_local *lp = netdev_priv(ndev);
	अचिन्हित पूर्णांक pending;

	pending = axienet_ior(lp, XAE_IP_OFFSET);
	अगर (!pending)
		वापस IRQ_NONE;

	अगर (pending & XAE_INT_RXFIFOOVR_MASK)
		ndev->stats.rx_missed_errors++;

	अगर (pending & XAE_INT_RXRJECT_MASK)
		ndev->stats.rx_frame_errors++;

	axienet_iow(lp, XAE_IS_OFFSET, pending);
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम axienet_dma_err_handler(काष्ठा work_काष्ठा *work);

/**
 * axienet_खोलो - Driver खोलो routine.
 * @ndev:	Poपूर्णांकer to net_device काष्ठाure
 *
 * Return: 0, on success.
 *	    non-zero error value on failure
 *
 * This is the driver खोलो routine. It calls phylink_start to start the
 * PHY device.
 * It also allocates पूर्णांकerrupt service routines, enables the पूर्णांकerrupt lines
 * and ISR handling. Axi Ethernet core is reset through Axi DMA core. Buffer
 * descriptors are initialized.
 */
अटल पूर्णांक axienet_खोलो(काष्ठा net_device *ndev)
अणु
	पूर्णांक ret;
	काष्ठा axienet_local *lp = netdev_priv(ndev);

	dev_dbg(&ndev->dev, "axienet_open()\n");

	/* When we करो an Axi Ethernet reset, it resets the complete core
	 * including the MDIO. MDIO must be disabled beक्रमe resetting.
	 * Hold MDIO bus lock to aव्योम MDIO accesses during the reset.
	 */
	axienet_lock_mii(lp);
	ret = axienet_device_reset(ndev);
	axienet_unlock_mii(lp);

	ret = phylink_of_phy_connect(lp->phylink, lp->dev->of_node, 0);
	अगर (ret) अणु
		dev_err(lp->dev, "phylink_of_phy_connect() failed: %d\n", ret);
		वापस ret;
	पूर्ण

	phylink_start(lp->phylink);

	/* Enable worker thपढ़ो क्रम Axi DMA error handling */
	INIT_WORK(&lp->dma_err_task, axienet_dma_err_handler);

	/* Enable पूर्णांकerrupts क्रम Axi DMA Tx */
	ret = request_irq(lp->tx_irq, axienet_tx_irq, IRQF_SHARED,
			  ndev->name, ndev);
	अगर (ret)
		जाओ err_tx_irq;
	/* Enable पूर्णांकerrupts क्रम Axi DMA Rx */
	ret = request_irq(lp->rx_irq, axienet_rx_irq, IRQF_SHARED,
			  ndev->name, ndev);
	अगर (ret)
		जाओ err_rx_irq;
	/* Enable पूर्णांकerrupts क्रम Axi Ethernet core (अगर defined) */
	अगर (lp->eth_irq > 0) अणु
		ret = request_irq(lp->eth_irq, axienet_eth_irq, IRQF_SHARED,
				  ndev->name, ndev);
		अगर (ret)
			जाओ err_eth_irq;
	पूर्ण

	वापस 0;

err_eth_irq:
	मुक्त_irq(lp->rx_irq, ndev);
err_rx_irq:
	मुक्त_irq(lp->tx_irq, ndev);
err_tx_irq:
	phylink_stop(lp->phylink);
	phylink_disconnect_phy(lp->phylink);
	cancel_work_sync(&lp->dma_err_task);
	dev_err(lp->dev, "request_irq() failed\n");
	वापस ret;
पूर्ण

/**
 * axienet_stop - Driver stop routine.
 * @ndev:	Poपूर्णांकer to net_device काष्ठाure
 *
 * Return: 0, on success.
 *
 * This is the driver stop routine. It calls phylink_disconnect to stop the PHY
 * device. It also हटाओs the पूर्णांकerrupt handlers and disables the पूर्णांकerrupts.
 * The Axi DMA Tx/Rx BDs are released.
 */
अटल पूर्णांक axienet_stop(काष्ठा net_device *ndev)
अणु
	u32 cr, sr;
	पूर्णांक count;
	काष्ठा axienet_local *lp = netdev_priv(ndev);

	dev_dbg(&ndev->dev, "axienet_close()\n");

	phylink_stop(lp->phylink);
	phylink_disconnect_phy(lp->phylink);

	axienet_setoptions(ndev, lp->options &
			   ~(XAE_OPTION_TXEN | XAE_OPTION_RXEN));

	cr = axienet_dma_in32(lp, XAXIDMA_RX_CR_OFFSET);
	cr &= ~(XAXIDMA_CR_RUNSTOP_MASK | XAXIDMA_IRQ_ALL_MASK);
	axienet_dma_out32(lp, XAXIDMA_RX_CR_OFFSET, cr);

	cr = axienet_dma_in32(lp, XAXIDMA_TX_CR_OFFSET);
	cr &= ~(XAXIDMA_CR_RUNSTOP_MASK | XAXIDMA_IRQ_ALL_MASK);
	axienet_dma_out32(lp, XAXIDMA_TX_CR_OFFSET, cr);

	axienet_iow(lp, XAE_IE_OFFSET, 0);

	/* Give DMAs a chance to halt gracefully */
	sr = axienet_dma_in32(lp, XAXIDMA_RX_SR_OFFSET);
	क्रम (count = 0; !(sr & XAXIDMA_SR_HALT_MASK) && count < 5; ++count) अणु
		msleep(20);
		sr = axienet_dma_in32(lp, XAXIDMA_RX_SR_OFFSET);
	पूर्ण

	sr = axienet_dma_in32(lp, XAXIDMA_TX_SR_OFFSET);
	क्रम (count = 0; !(sr & XAXIDMA_SR_HALT_MASK) && count < 5; ++count) अणु
		msleep(20);
		sr = axienet_dma_in32(lp, XAXIDMA_TX_SR_OFFSET);
	पूर्ण

	/* Do a reset to ensure DMA is really stopped */
	axienet_lock_mii(lp);
	__axienet_device_reset(lp);
	axienet_unlock_mii(lp);

	cancel_work_sync(&lp->dma_err_task);

	अगर (lp->eth_irq > 0)
		मुक्त_irq(lp->eth_irq, ndev);
	मुक्त_irq(lp->tx_irq, ndev);
	मुक्त_irq(lp->rx_irq, ndev);

	axienet_dma_bd_release(ndev);
	वापस 0;
पूर्ण

/**
 * axienet_change_mtu - Driver change mtu routine.
 * @ndev:	Poपूर्णांकer to net_device काष्ठाure
 * @new_mtu:	New mtu value to be applied
 *
 * Return: Always वापसs 0 (success).
 *
 * This is the change mtu driver routine. It checks अगर the Axi Ethernet
 * hardware supports jumbo frames beक्रमe changing the mtu. This can be
 * called only when the device is not up.
 */
अटल पूर्णांक axienet_change_mtu(काष्ठा net_device *ndev, पूर्णांक new_mtu)
अणु
	काष्ठा axienet_local *lp = netdev_priv(ndev);

	अगर (netअगर_running(ndev))
		वापस -EBUSY;

	अगर ((new_mtu + VLAN_ETH_HLEN +
		XAE_TRL_SIZE) > lp->rxmem)
		वापस -EINVAL;

	ndev->mtu = new_mtu;

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
/**
 * axienet_poll_controller - Axi Ethernet poll mechanism.
 * @ndev:	Poपूर्णांकer to net_device काष्ठाure
 *
 * This implements Rx/Tx ISR poll mechanisms. The पूर्णांकerrupts are disabled prior
 * to polling the ISRs and are enabled back after the polling is करोne.
 */
अटल व्योम axienet_poll_controller(काष्ठा net_device *ndev)
अणु
	काष्ठा axienet_local *lp = netdev_priv(ndev);
	disable_irq(lp->tx_irq);
	disable_irq(lp->rx_irq);
	axienet_rx_irq(lp->tx_irq, ndev);
	axienet_tx_irq(lp->rx_irq, ndev);
	enable_irq(lp->tx_irq);
	enable_irq(lp->rx_irq);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक axienet_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *rq, पूर्णांक cmd)
अणु
	काष्ठा axienet_local *lp = netdev_priv(dev);

	अगर (!netअगर_running(dev))
		वापस -EINVAL;

	वापस phylink_mii_ioctl(lp->phylink, rq, cmd);
पूर्ण

अटल स्थिर काष्ठा net_device_ops axienet_netdev_ops = अणु
	.nकरो_खोलो = axienet_खोलो,
	.nकरो_stop = axienet_stop,
	.nकरो_start_xmit = axienet_start_xmit,
	.nकरो_change_mtu	= axienet_change_mtu,
	.nकरो_set_mac_address = netdev_set_mac_address,
	.nकरो_validate_addr = eth_validate_addr,
	.nकरो_करो_ioctl = axienet_ioctl,
	.nकरो_set_rx_mode = axienet_set_multicast_list,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller = axienet_poll_controller,
#पूर्ण_अगर
पूर्ण;

/**
 * axienet_ethtools_get_drvinfo - Get various Axi Ethernet driver inक्रमmation.
 * @ndev:	Poपूर्णांकer to net_device काष्ठाure
 * @ed:		Poपूर्णांकer to ethtool_drvinfo काष्ठाure
 *
 * This implements ethtool command क्रम getting the driver inक्रमmation.
 * Issue "ethtool -i ethX" under linux prompt to execute this function.
 */
अटल व्योम axienet_ethtools_get_drvinfo(काष्ठा net_device *ndev,
					 काष्ठा ethtool_drvinfo *ed)
अणु
	strlcpy(ed->driver, DRIVER_NAME, माप(ed->driver));
	strlcpy(ed->version, DRIVER_VERSION, माप(ed->version));
पूर्ण

/**
 * axienet_ethtools_get_regs_len - Get the total regs length present in the
 *				   AxiEthernet core.
 * @ndev:	Poपूर्णांकer to net_device काष्ठाure
 *
 * This implements ethtool command क्रम getting the total रेजिस्टर length
 * inक्रमmation.
 *
 * Return: the total regs length
 */
अटल पूर्णांक axienet_ethtools_get_regs_len(काष्ठा net_device *ndev)
अणु
	वापस माप(u32) * AXIENET_REGS_N;
पूर्ण

/**
 * axienet_ethtools_get_regs - Dump the contents of all रेजिस्टरs present
 *			       in AxiEthernet core.
 * @ndev:	Poपूर्णांकer to net_device काष्ठाure
 * @regs:	Poपूर्णांकer to ethtool_regs काष्ठाure
 * @ret:	Void poपूर्णांकer used to वापस the contents of the रेजिस्टरs.
 *
 * This implements ethtool command क्रम getting the Axi Ethernet रेजिस्टर dump.
 * Issue "ethtool -d ethX" to execute this function.
 */
अटल व्योम axienet_ethtools_get_regs(काष्ठा net_device *ndev,
				      काष्ठा ethtool_regs *regs, व्योम *ret)
अणु
	u32 *data = (u32 *) ret;
	माप_प्रकार len = माप(u32) * AXIENET_REGS_N;
	काष्ठा axienet_local *lp = netdev_priv(ndev);

	regs->version = 0;
	regs->len = len;

	स_रखो(data, 0, len);
	data[0] = axienet_ior(lp, XAE_RAF_OFFSET);
	data[1] = axienet_ior(lp, XAE_TPF_OFFSET);
	data[2] = axienet_ior(lp, XAE_IFGP_OFFSET);
	data[3] = axienet_ior(lp, XAE_IS_OFFSET);
	data[4] = axienet_ior(lp, XAE_IP_OFFSET);
	data[5] = axienet_ior(lp, XAE_IE_OFFSET);
	data[6] = axienet_ior(lp, XAE_TTAG_OFFSET);
	data[7] = axienet_ior(lp, XAE_RTAG_OFFSET);
	data[8] = axienet_ior(lp, XAE_UAWL_OFFSET);
	data[9] = axienet_ior(lp, XAE_UAWU_OFFSET);
	data[10] = axienet_ior(lp, XAE_TPID0_OFFSET);
	data[11] = axienet_ior(lp, XAE_TPID1_OFFSET);
	data[12] = axienet_ior(lp, XAE_PPST_OFFSET);
	data[13] = axienet_ior(lp, XAE_RCW0_OFFSET);
	data[14] = axienet_ior(lp, XAE_RCW1_OFFSET);
	data[15] = axienet_ior(lp, XAE_TC_OFFSET);
	data[16] = axienet_ior(lp, XAE_FCC_OFFSET);
	data[17] = axienet_ior(lp, XAE_EMMC_OFFSET);
	data[18] = axienet_ior(lp, XAE_PHYC_OFFSET);
	data[19] = axienet_ior(lp, XAE_MDIO_MC_OFFSET);
	data[20] = axienet_ior(lp, XAE_MDIO_MCR_OFFSET);
	data[21] = axienet_ior(lp, XAE_MDIO_MWD_OFFSET);
	data[22] = axienet_ior(lp, XAE_MDIO_MRD_OFFSET);
	data[27] = axienet_ior(lp, XAE_UAW0_OFFSET);
	data[28] = axienet_ior(lp, XAE_UAW1_OFFSET);
	data[29] = axienet_ior(lp, XAE_FMI_OFFSET);
	data[30] = axienet_ior(lp, XAE_AF0_OFFSET);
	data[31] = axienet_ior(lp, XAE_AF1_OFFSET);
	data[32] = axienet_dma_in32(lp, XAXIDMA_TX_CR_OFFSET);
	data[33] = axienet_dma_in32(lp, XAXIDMA_TX_SR_OFFSET);
	data[34] = axienet_dma_in32(lp, XAXIDMA_TX_CDESC_OFFSET);
	data[35] = axienet_dma_in32(lp, XAXIDMA_TX_TDESC_OFFSET);
	data[36] = axienet_dma_in32(lp, XAXIDMA_RX_CR_OFFSET);
	data[37] = axienet_dma_in32(lp, XAXIDMA_RX_SR_OFFSET);
	data[38] = axienet_dma_in32(lp, XAXIDMA_RX_CDESC_OFFSET);
	data[39] = axienet_dma_in32(lp, XAXIDMA_RX_TDESC_OFFSET);
पूर्ण

अटल व्योम axienet_ethtools_get_ringparam(काष्ठा net_device *ndev,
					   काष्ठा ethtool_ringparam *ering)
अणु
	काष्ठा axienet_local *lp = netdev_priv(ndev);

	ering->rx_max_pending = RX_BD_NUM_MAX;
	ering->rx_mini_max_pending = 0;
	ering->rx_jumbo_max_pending = 0;
	ering->tx_max_pending = TX_BD_NUM_MAX;
	ering->rx_pending = lp->rx_bd_num;
	ering->rx_mini_pending = 0;
	ering->rx_jumbo_pending = 0;
	ering->tx_pending = lp->tx_bd_num;
पूर्ण

अटल पूर्णांक axienet_ethtools_set_ringparam(काष्ठा net_device *ndev,
					  काष्ठा ethtool_ringparam *ering)
अणु
	काष्ठा axienet_local *lp = netdev_priv(ndev);

	अगर (ering->rx_pending > RX_BD_NUM_MAX ||
	    ering->rx_mini_pending ||
	    ering->rx_jumbo_pending ||
	    ering->rx_pending > TX_BD_NUM_MAX)
		वापस -EINVAL;

	अगर (netअगर_running(ndev))
		वापस -EBUSY;

	lp->rx_bd_num = ering->rx_pending;
	lp->tx_bd_num = ering->tx_pending;
	वापस 0;
पूर्ण

/**
 * axienet_ethtools_get_छोड़ोparam - Get the छोड़ो parameter setting क्रम
 *				     Tx and Rx paths.
 * @ndev:	Poपूर्णांकer to net_device काष्ठाure
 * @eछोड़ोparm:	Poपूर्णांकer to ethtool_छोड़ोparam काष्ठाure.
 *
 * This implements ethtool command क्रम getting axi ethernet छोड़ो frame
 * setting. Issue "ethtool -a ethX" to execute this function.
 */
अटल व्योम
axienet_ethtools_get_छोड़ोparam(काष्ठा net_device *ndev,
				काष्ठा ethtool_छोड़ोparam *eछोड़ोparm)
अणु
	काष्ठा axienet_local *lp = netdev_priv(ndev);

	phylink_ethtool_get_छोड़ोparam(lp->phylink, eछोड़ोparm);
पूर्ण

/**
 * axienet_ethtools_set_छोड़ोparam - Set device छोड़ो parameter(flow control)
 *				     settings.
 * @ndev:	Poपूर्णांकer to net_device काष्ठाure
 * @eछोड़ोparm:Poपूर्णांकer to ethtool_छोड़ोparam काष्ठाure
 *
 * This implements ethtool command क्रम enabling flow control on Rx and Tx
 * paths. Issue "ethtool -A ethX tx on|off" under linux prompt to execute this
 * function.
 *
 * Return: 0 on success, -EFAULT अगर device is running
 */
अटल पूर्णांक
axienet_ethtools_set_छोड़ोparam(काष्ठा net_device *ndev,
				काष्ठा ethtool_छोड़ोparam *eछोड़ोparm)
अणु
	काष्ठा axienet_local *lp = netdev_priv(ndev);

	वापस phylink_ethtool_set_छोड़ोparam(lp->phylink, eछोड़ोparm);
पूर्ण

/**
 * axienet_ethtools_get_coalesce - Get DMA पूर्णांकerrupt coalescing count.
 * @ndev:	Poपूर्णांकer to net_device काष्ठाure
 * @ecoalesce:	Poपूर्णांकer to ethtool_coalesce काष्ठाure
 *
 * This implements ethtool command क्रम getting the DMA पूर्णांकerrupt coalescing
 * count on Tx and Rx paths. Issue "ethtool -c ethX" under linux prompt to
 * execute this function.
 *
 * Return: 0 always
 */
अटल पूर्णांक axienet_ethtools_get_coalesce(काष्ठा net_device *ndev,
					 काष्ठा ethtool_coalesce *ecoalesce)
अणु
	u32 regval = 0;
	काष्ठा axienet_local *lp = netdev_priv(ndev);
	regval = axienet_dma_in32(lp, XAXIDMA_RX_CR_OFFSET);
	ecoalesce->rx_max_coalesced_frames = (regval & XAXIDMA_COALESCE_MASK)
					     >> XAXIDMA_COALESCE_SHIFT;
	regval = axienet_dma_in32(lp, XAXIDMA_TX_CR_OFFSET);
	ecoalesce->tx_max_coalesced_frames = (regval & XAXIDMA_COALESCE_MASK)
					     >> XAXIDMA_COALESCE_SHIFT;
	वापस 0;
पूर्ण

/**
 * axienet_ethtools_set_coalesce - Set DMA पूर्णांकerrupt coalescing count.
 * @ndev:	Poपूर्णांकer to net_device काष्ठाure
 * @ecoalesce:	Poपूर्णांकer to ethtool_coalesce काष्ठाure
 *
 * This implements ethtool command क्रम setting the DMA पूर्णांकerrupt coalescing
 * count on Tx and Rx paths. Issue "ethtool -C ethX rx-frames 5" under linux
 * prompt to execute this function.
 *
 * Return: 0, on success, Non-zero error value on failure.
 */
अटल पूर्णांक axienet_ethtools_set_coalesce(काष्ठा net_device *ndev,
					 काष्ठा ethtool_coalesce *ecoalesce)
अणु
	काष्ठा axienet_local *lp = netdev_priv(ndev);

	अगर (netअगर_running(ndev)) अणु
		netdev_err(ndev,
			   "Please stop netif before applying configuration\n");
		वापस -EFAULT;
	पूर्ण

	अगर (ecoalesce->rx_max_coalesced_frames)
		lp->coalesce_count_rx = ecoalesce->rx_max_coalesced_frames;
	अगर (ecoalesce->tx_max_coalesced_frames)
		lp->coalesce_count_tx = ecoalesce->tx_max_coalesced_frames;

	वापस 0;
पूर्ण

अटल पूर्णांक
axienet_ethtools_get_link_ksettings(काष्ठा net_device *ndev,
				    काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा axienet_local *lp = netdev_priv(ndev);

	वापस phylink_ethtool_ksettings_get(lp->phylink, cmd);
पूर्ण

अटल पूर्णांक
axienet_ethtools_set_link_ksettings(काष्ठा net_device *ndev,
				    स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा axienet_local *lp = netdev_priv(ndev);

	वापस phylink_ethtool_ksettings_set(lp->phylink, cmd);
पूर्ण

अटल पूर्णांक axienet_ethtools_nway_reset(काष्ठा net_device *dev)
अणु
	काष्ठा axienet_local *lp = netdev_priv(dev);

	वापस phylink_ethtool_nway_reset(lp->phylink);
पूर्ण

अटल स्थिर काष्ठा ethtool_ops axienet_ethtool_ops = अणु
	.supported_coalesce_params = ETHTOOL_COALESCE_MAX_FRAMES,
	.get_drvinfo    = axienet_ethtools_get_drvinfo,
	.get_regs_len   = axienet_ethtools_get_regs_len,
	.get_regs       = axienet_ethtools_get_regs,
	.get_link       = ethtool_op_get_link,
	.get_ringparam	= axienet_ethtools_get_ringparam,
	.set_ringparam	= axienet_ethtools_set_ringparam,
	.get_छोड़ोparam = axienet_ethtools_get_छोड़ोparam,
	.set_छोड़ोparam = axienet_ethtools_set_छोड़ोparam,
	.get_coalesce   = axienet_ethtools_get_coalesce,
	.set_coalesce   = axienet_ethtools_set_coalesce,
	.get_link_ksettings = axienet_ethtools_get_link_ksettings,
	.set_link_ksettings = axienet_ethtools_set_link_ksettings,
	.nway_reset	= axienet_ethtools_nway_reset,
पूर्ण;

अटल व्योम axienet_validate(काष्ठा phylink_config *config,
			     अचिन्हित दीर्घ *supported,
			     काष्ठा phylink_link_state *state)
अणु
	काष्ठा net_device *ndev = to_net_dev(config->dev);
	काष्ठा axienet_local *lp = netdev_priv(ndev);
	__ETHTOOL_DECLARE_LINK_MODE_MASK(mask) = अणु 0, पूर्ण;

	/* Only support the mode we are configured क्रम */
	चयन (state->पूर्णांकerface) अणु
	हाल PHY_INTERFACE_MODE_NA:
		अवरोध;
	हाल PHY_INTERFACE_MODE_1000BASEX:
	हाल PHY_INTERFACE_MODE_SGMII:
		अगर (lp->चयन_x_sgmii)
			अवरोध;
		fallthrough;
	शेष:
		अगर (state->पूर्णांकerface != lp->phy_mode) अणु
			netdev_warn(ndev, "Cannot use PHY mode %s, supported: %s\n",
				    phy_modes(state->पूर्णांकerface),
				    phy_modes(lp->phy_mode));
			biपंचांगap_zero(supported, __ETHTOOL_LINK_MODE_MASK_NBITS);
			वापस;
		पूर्ण
	पूर्ण

	phylink_set(mask, Autoneg);
	phylink_set_port_modes(mask);

	phylink_set(mask, Asym_Pause);
	phylink_set(mask, Pause);

	चयन (state->पूर्णांकerface) अणु
	हाल PHY_INTERFACE_MODE_NA:
	हाल PHY_INTERFACE_MODE_1000BASEX:
	हाल PHY_INTERFACE_MODE_SGMII:
	हाल PHY_INTERFACE_MODE_GMII:
	हाल PHY_INTERFACE_MODE_RGMII:
	हाल PHY_INTERFACE_MODE_RGMII_ID:
	हाल PHY_INTERFACE_MODE_RGMII_RXID:
	हाल PHY_INTERFACE_MODE_RGMII_TXID:
		phylink_set(mask, 1000baseX_Full);
		phylink_set(mask, 1000baseT_Full);
		अगर (state->पूर्णांकerface == PHY_INTERFACE_MODE_1000BASEX)
			अवरोध;
		fallthrough;
	हाल PHY_INTERFACE_MODE_MII:
		phylink_set(mask, 100baseT_Full);
		phylink_set(mask, 10baseT_Full);
	शेष:
		अवरोध;
	पूर्ण

	biपंचांगap_and(supported, supported, mask,
		   __ETHTOOL_LINK_MODE_MASK_NBITS);
	biपंचांगap_and(state->advertising, state->advertising, mask,
		   __ETHTOOL_LINK_MODE_MASK_NBITS);
पूर्ण

अटल व्योम axienet_mac_pcs_get_state(काष्ठा phylink_config *config,
				      काष्ठा phylink_link_state *state)
अणु
	काष्ठा net_device *ndev = to_net_dev(config->dev);
	काष्ठा axienet_local *lp = netdev_priv(ndev);

	चयन (state->पूर्णांकerface) अणु
	हाल PHY_INTERFACE_MODE_SGMII:
	हाल PHY_INTERFACE_MODE_1000BASEX:
		phylink_mii_c22_pcs_get_state(lp->pcs_phy, state);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम axienet_mac_an_restart(काष्ठा phylink_config *config)
अणु
	काष्ठा net_device *ndev = to_net_dev(config->dev);
	काष्ठा axienet_local *lp = netdev_priv(ndev);

	phylink_mii_c22_pcs_an_restart(lp->pcs_phy);
पूर्ण

अटल पूर्णांक axienet_mac_prepare(काष्ठा phylink_config *config, अचिन्हित पूर्णांक mode,
			       phy_पूर्णांकerface_t अगरace)
अणु
	काष्ठा net_device *ndev = to_net_dev(config->dev);
	काष्ठा axienet_local *lp = netdev_priv(ndev);
	पूर्णांक ret;

	चयन (अगरace) अणु
	हाल PHY_INTERFACE_MODE_SGMII:
	हाल PHY_INTERFACE_MODE_1000BASEX:
		अगर (!lp->चयन_x_sgmii)
			वापस 0;

		ret = mdiobus_ग_लिखो(lp->pcs_phy->bus,
				    lp->pcs_phy->addr,
				    XLNX_MII_STD_SELECT_REG,
				    अगरace == PHY_INTERFACE_MODE_SGMII ?
					XLNX_MII_STD_SELECT_SGMII : 0);
		अगर (ret < 0)
			netdev_warn(ndev, "Failed to switch PHY interface: %d\n",
				    ret);
		वापस ret;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल व्योम axienet_mac_config(काष्ठा phylink_config *config, अचिन्हित पूर्णांक mode,
			       स्थिर काष्ठा phylink_link_state *state)
अणु
	काष्ठा net_device *ndev = to_net_dev(config->dev);
	काष्ठा axienet_local *lp = netdev_priv(ndev);
	पूर्णांक ret;

	चयन (state->पूर्णांकerface) अणु
	हाल PHY_INTERFACE_MODE_SGMII:
	हाल PHY_INTERFACE_MODE_1000BASEX:
		ret = phylink_mii_c22_pcs_config(lp->pcs_phy, mode,
						 state->पूर्णांकerface,
						 state->advertising);
		अगर (ret < 0)
			netdev_warn(ndev, "Failed to configure PCS: %d\n",
				    ret);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम axienet_mac_link_करोwn(काष्ठा phylink_config *config,
				  अचिन्हित पूर्णांक mode,
				  phy_पूर्णांकerface_t पूर्णांकerface)
अणु
	/* nothing meaningful to करो */
पूर्ण

अटल व्योम axienet_mac_link_up(काष्ठा phylink_config *config,
				काष्ठा phy_device *phy,
				अचिन्हित पूर्णांक mode, phy_पूर्णांकerface_t पूर्णांकerface,
				पूर्णांक speed, पूर्णांक duplex,
				bool tx_छोड़ो, bool rx_छोड़ो)
अणु
	काष्ठा net_device *ndev = to_net_dev(config->dev);
	काष्ठा axienet_local *lp = netdev_priv(ndev);
	u32 emmc_reg, fcc_reg;

	emmc_reg = axienet_ior(lp, XAE_EMMC_OFFSET);
	emmc_reg &= ~XAE_EMMC_LINKSPEED_MASK;

	चयन (speed) अणु
	हाल SPEED_1000:
		emmc_reg |= XAE_EMMC_LINKSPD_1000;
		अवरोध;
	हाल SPEED_100:
		emmc_reg |= XAE_EMMC_LINKSPD_100;
		अवरोध;
	हाल SPEED_10:
		emmc_reg |= XAE_EMMC_LINKSPD_10;
		अवरोध;
	शेष:
		dev_err(&ndev->dev,
			"Speed other than 10, 100 or 1Gbps is not supported\n");
		अवरोध;
	पूर्ण

	axienet_iow(lp, XAE_EMMC_OFFSET, emmc_reg);

	fcc_reg = axienet_ior(lp, XAE_FCC_OFFSET);
	अगर (tx_छोड़ो)
		fcc_reg |= XAE_FCC_FCTX_MASK;
	अन्यथा
		fcc_reg &= ~XAE_FCC_FCTX_MASK;
	अगर (rx_छोड़ो)
		fcc_reg |= XAE_FCC_FCRX_MASK;
	अन्यथा
		fcc_reg &= ~XAE_FCC_FCRX_MASK;
	axienet_iow(lp, XAE_FCC_OFFSET, fcc_reg);
पूर्ण

अटल स्थिर काष्ठा phylink_mac_ops axienet_phylink_ops = अणु
	.validate = axienet_validate,
	.mac_pcs_get_state = axienet_mac_pcs_get_state,
	.mac_an_restart = axienet_mac_an_restart,
	.mac_prepare = axienet_mac_prepare,
	.mac_config = axienet_mac_config,
	.mac_link_करोwn = axienet_mac_link_करोwn,
	.mac_link_up = axienet_mac_link_up,
पूर्ण;

/**
 * axienet_dma_err_handler - Work queue task क्रम Axi DMA Error
 * @work:	poपूर्णांकer to work_काष्ठा
 *
 * Resets the Axi DMA and Axi Ethernet devices, and reconfigures the
 * Tx/Rx BDs.
 */
अटल व्योम axienet_dma_err_handler(काष्ठा work_काष्ठा *work)
अणु
	u32 axienet_status;
	u32 cr, i;
	काष्ठा axienet_local *lp = container_of(work, काष्ठा axienet_local,
						dma_err_task);
	काष्ठा net_device *ndev = lp->ndev;
	काष्ठा axidma_bd *cur_p;

	axienet_setoptions(ndev, lp->options &
			   ~(XAE_OPTION_TXEN | XAE_OPTION_RXEN));
	/* When we करो an Axi Ethernet reset, it resets the complete core
	 * including the MDIO. MDIO must be disabled beक्रमe resetting.
	 * Hold MDIO bus lock to aव्योम MDIO accesses during the reset.
	 */
	axienet_lock_mii(lp);
	__axienet_device_reset(lp);
	axienet_unlock_mii(lp);

	क्रम (i = 0; i < lp->tx_bd_num; i++) अणु
		cur_p = &lp->tx_bd_v[i];
		अगर (cur_p->cntrl) अणु
			dma_addr_t addr = desc_get_phys_addr(lp, cur_p);

			dma_unmap_single(ndev->dev.parent, addr,
					 (cur_p->cntrl &
					  XAXIDMA_BD_CTRL_LENGTH_MASK),
					 DMA_TO_DEVICE);
		पूर्ण
		अगर (cur_p->skb)
			dev_kमुक्त_skb_irq(cur_p->skb);
		cur_p->phys = 0;
		cur_p->phys_msb = 0;
		cur_p->cntrl = 0;
		cur_p->status = 0;
		cur_p->app0 = 0;
		cur_p->app1 = 0;
		cur_p->app2 = 0;
		cur_p->app3 = 0;
		cur_p->app4 = 0;
		cur_p->skb = शून्य;
	पूर्ण

	क्रम (i = 0; i < lp->rx_bd_num; i++) अणु
		cur_p = &lp->rx_bd_v[i];
		cur_p->status = 0;
		cur_p->app0 = 0;
		cur_p->app1 = 0;
		cur_p->app2 = 0;
		cur_p->app3 = 0;
		cur_p->app4 = 0;
	पूर्ण

	lp->tx_bd_ci = 0;
	lp->tx_bd_tail = 0;
	lp->rx_bd_ci = 0;

	/* Start updating the Rx channel control रेजिस्टर */
	cr = axienet_dma_in32(lp, XAXIDMA_RX_CR_OFFSET);
	/* Update the पूर्णांकerrupt coalesce count */
	cr = ((cr & ~XAXIDMA_COALESCE_MASK) |
	      (XAXIDMA_DFT_RX_THRESHOLD << XAXIDMA_COALESCE_SHIFT));
	/* Update the delay समयr count */
	cr = ((cr & ~XAXIDMA_DELAY_MASK) |
	      (XAXIDMA_DFT_RX_WAITBOUND << XAXIDMA_DELAY_SHIFT));
	/* Enable coalesce, delay समयr and error पूर्णांकerrupts */
	cr |= XAXIDMA_IRQ_ALL_MASK;
	/* Finally ग_लिखो to the Rx channel control रेजिस्टर */
	axienet_dma_out32(lp, XAXIDMA_RX_CR_OFFSET, cr);

	/* Start updating the Tx channel control रेजिस्टर */
	cr = axienet_dma_in32(lp, XAXIDMA_TX_CR_OFFSET);
	/* Update the पूर्णांकerrupt coalesce count */
	cr = (((cr & ~XAXIDMA_COALESCE_MASK)) |
	      (XAXIDMA_DFT_TX_THRESHOLD << XAXIDMA_COALESCE_SHIFT));
	/* Update the delay समयr count */
	cr = (((cr & ~XAXIDMA_DELAY_MASK)) |
	      (XAXIDMA_DFT_TX_WAITBOUND << XAXIDMA_DELAY_SHIFT));
	/* Enable coalesce, delay समयr and error पूर्णांकerrupts */
	cr |= XAXIDMA_IRQ_ALL_MASK;
	/* Finally ग_लिखो to the Tx channel control रेजिस्टर */
	axienet_dma_out32(lp, XAXIDMA_TX_CR_OFFSET, cr);

	/* Populate the tail poपूर्णांकer and bring the Rx Axi DMA engine out of
	 * halted state. This will make the Rx side पढ़ोy क्रम reception.
	 */
	axienet_dma_out_addr(lp, XAXIDMA_RX_CDESC_OFFSET, lp->rx_bd_p);
	cr = axienet_dma_in32(lp, XAXIDMA_RX_CR_OFFSET);
	axienet_dma_out32(lp, XAXIDMA_RX_CR_OFFSET,
			  cr | XAXIDMA_CR_RUNSTOP_MASK);
	axienet_dma_out_addr(lp, XAXIDMA_RX_TDESC_OFFSET, lp->rx_bd_p +
			     (माप(*lp->rx_bd_v) * (lp->rx_bd_num - 1)));

	/* Write to the RS (Run-stop) bit in the Tx channel control रेजिस्टर.
	 * Tx channel is now पढ़ोy to run. But only after we ग_लिखो to the
	 * tail poपूर्णांकer रेजिस्टर that the Tx channel will start transmitting
	 */
	axienet_dma_out_addr(lp, XAXIDMA_TX_CDESC_OFFSET, lp->tx_bd_p);
	cr = axienet_dma_in32(lp, XAXIDMA_TX_CR_OFFSET);
	axienet_dma_out32(lp, XAXIDMA_TX_CR_OFFSET,
			  cr | XAXIDMA_CR_RUNSTOP_MASK);

	axienet_status = axienet_ior(lp, XAE_RCW1_OFFSET);
	axienet_status &= ~XAE_RCW1_RX_MASK;
	axienet_iow(lp, XAE_RCW1_OFFSET, axienet_status);

	axienet_status = axienet_ior(lp, XAE_IP_OFFSET);
	अगर (axienet_status & XAE_INT_RXRJECT_MASK)
		axienet_iow(lp, XAE_IS_OFFSET, XAE_INT_RXRJECT_MASK);
	axienet_iow(lp, XAE_IE_OFFSET, lp->eth_irq > 0 ?
		    XAE_INT_RECV_ERROR_MASK : 0);
	axienet_iow(lp, XAE_FCC_OFFSET, XAE_FCC_FCRX_MASK);

	/* Sync शेष options with HW but leave receiver and
	 * transmitter disabled.
	 */
	axienet_setoptions(ndev, lp->options &
			   ~(XAE_OPTION_TXEN | XAE_OPTION_RXEN));
	axienet_set_mac_address(ndev, शून्य);
	axienet_set_multicast_list(ndev);
	axienet_setoptions(ndev, lp->options);
पूर्ण

/**
 * axienet_probe - Axi Ethernet probe function.
 * @pdev:	Poपूर्णांकer to platक्रमm device काष्ठाure.
 *
 * Return: 0, on success
 *	    Non-zero error value on failure.
 *
 * This is the probe routine क्रम Axi Ethernet driver. This is called beक्रमe
 * any other driver routines are invoked. It allocates and sets up the Ethernet
 * device. Parses through device tree and populates fields of
 * axienet_local. It रेजिस्टरs the Ethernet device.
 */
अटल पूर्णांक axienet_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;
	काष्ठा device_node *np;
	काष्ठा axienet_local *lp;
	काष्ठा net_device *ndev;
	काष्ठा resource *ethres;
	u8 mac_addr[ETH_ALEN];
	पूर्णांक addr_width = 32;
	u32 value;

	ndev = alloc_etherdev(माप(*lp));
	अगर (!ndev)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, ndev);

	SET_NETDEV_DEV(ndev, &pdev->dev);
	ndev->flags &= ~IFF_MULTICAST;  /* clear multicast */
	ndev->features = NETIF_F_SG;
	ndev->netdev_ops = &axienet_netdev_ops;
	ndev->ethtool_ops = &axienet_ethtool_ops;

	/* MTU range: 64 - 9000 */
	ndev->min_mtu = 64;
	ndev->max_mtu = XAE_JUMBO_MTU;

	lp = netdev_priv(ndev);
	lp->ndev = ndev;
	lp->dev = &pdev->dev;
	lp->options = XAE_OPTION_DEFAULTS;
	lp->rx_bd_num = RX_BD_NUM_DEFAULT;
	lp->tx_bd_num = TX_BD_NUM_DEFAULT;

	lp->axi_clk = devm_clk_get_optional(&pdev->dev, "s_axi_lite_clk");
	अगर (!lp->axi_clk) अणु
		/* For backward compatibility, अगर named AXI घड़ी is not present,
		 * treat the first घड़ी specअगरied as the AXI घड़ी.
		 */
		lp->axi_clk = devm_clk_get_optional(&pdev->dev, शून्य);
	पूर्ण
	अगर (IS_ERR(lp->axi_clk)) अणु
		ret = PTR_ERR(lp->axi_clk);
		जाओ मुक्त_netdev;
	पूर्ण
	ret = clk_prepare_enable(lp->axi_clk);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Unable to enable AXI clock: %d\n", ret);
		जाओ मुक्त_netdev;
	पूर्ण

	lp->misc_clks[0].id = "axis_clk";
	lp->misc_clks[1].id = "ref_clk";
	lp->misc_clks[2].id = "mgt_clk";

	ret = devm_clk_bulk_get_optional(&pdev->dev, XAE_NUM_MISC_CLOCKS, lp->misc_clks);
	अगर (ret)
		जाओ cleanup_clk;

	ret = clk_bulk_prepare_enable(XAE_NUM_MISC_CLOCKS, lp->misc_clks);
	अगर (ret)
		जाओ cleanup_clk;

	/* Map device रेजिस्टरs */
	ethres = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	lp->regs = devm_ioremap_resource(&pdev->dev, ethres);
	अगर (IS_ERR(lp->regs)) अणु
		ret = PTR_ERR(lp->regs);
		जाओ cleanup_clk;
	पूर्ण
	lp->regs_start = ethres->start;

	/* Setup checksum offload, but शेष to off अगर not specअगरied */
	lp->features = 0;

	ret = of_property_पढ़ो_u32(pdev->dev.of_node, "xlnx,txcsum", &value);
	अगर (!ret) अणु
		चयन (value) अणु
		हाल 1:
			lp->csum_offload_on_tx_path =
				XAE_FEATURE_PARTIAL_TX_CSUM;
			lp->features |= XAE_FEATURE_PARTIAL_TX_CSUM;
			/* Can checksum TCP/UDP over IPv4. */
			ndev->features |= NETIF_F_IP_CSUM;
			अवरोध;
		हाल 2:
			lp->csum_offload_on_tx_path =
				XAE_FEATURE_FULL_TX_CSUM;
			lp->features |= XAE_FEATURE_FULL_TX_CSUM;
			/* Can checksum TCP/UDP over IPv4. */
			ndev->features |= NETIF_F_IP_CSUM;
			अवरोध;
		शेष:
			lp->csum_offload_on_tx_path = XAE_NO_CSUM_OFFLOAD;
		पूर्ण
	पूर्ण
	ret = of_property_पढ़ो_u32(pdev->dev.of_node, "xlnx,rxcsum", &value);
	अगर (!ret) अणु
		चयन (value) अणु
		हाल 1:
			lp->csum_offload_on_rx_path =
				XAE_FEATURE_PARTIAL_RX_CSUM;
			lp->features |= XAE_FEATURE_PARTIAL_RX_CSUM;
			अवरोध;
		हाल 2:
			lp->csum_offload_on_rx_path =
				XAE_FEATURE_FULL_RX_CSUM;
			lp->features |= XAE_FEATURE_FULL_RX_CSUM;
			अवरोध;
		शेष:
			lp->csum_offload_on_rx_path = XAE_NO_CSUM_OFFLOAD;
		पूर्ण
	पूर्ण
	/* For supporting jumbo frames, the Axi Ethernet hardware must have
	 * a larger Rx/Tx Memory. Typically, the size must be large so that
	 * we can enable jumbo option and start supporting jumbo frames.
	 * Here we check क्रम memory allocated क्रम Rx/Tx in the hardware from
	 * the device-tree and accordingly set flags.
	 */
	of_property_पढ़ो_u32(pdev->dev.of_node, "xlnx,rxmem", &lp->rxmem);

	lp->चयन_x_sgmii = of_property_पढ़ो_bool(pdev->dev.of_node,
						   "xlnx,switch-x-sgmii");

	/* Start with the proprietary, and broken phy_type */
	ret = of_property_पढ़ो_u32(pdev->dev.of_node, "xlnx,phy-type", &value);
	अगर (!ret) अणु
		netdev_warn(ndev, "Please upgrade your device tree binary blob to use phy-mode");
		चयन (value) अणु
		हाल XAE_PHY_TYPE_MII:
			lp->phy_mode = PHY_INTERFACE_MODE_MII;
			अवरोध;
		हाल XAE_PHY_TYPE_GMII:
			lp->phy_mode = PHY_INTERFACE_MODE_GMII;
			अवरोध;
		हाल XAE_PHY_TYPE_RGMII_2_0:
			lp->phy_mode = PHY_INTERFACE_MODE_RGMII_ID;
			अवरोध;
		हाल XAE_PHY_TYPE_SGMII:
			lp->phy_mode = PHY_INTERFACE_MODE_SGMII;
			अवरोध;
		हाल XAE_PHY_TYPE_1000BASE_X:
			lp->phy_mode = PHY_INTERFACE_MODE_1000BASEX;
			अवरोध;
		शेष:
			ret = -EINVAL;
			जाओ cleanup_clk;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = of_get_phy_mode(pdev->dev.of_node, &lp->phy_mode);
		अगर (ret)
			जाओ cleanup_clk;
	पूर्ण
	अगर (lp->चयन_x_sgmii && lp->phy_mode != PHY_INTERFACE_MODE_SGMII &&
	    lp->phy_mode != PHY_INTERFACE_MODE_1000BASEX) अणु
		dev_err(&pdev->dev, "xlnx,switch-x-sgmii only supported with SGMII or 1000BaseX\n");
		ret = -EINVAL;
		जाओ cleanup_clk;
	पूर्ण

	/* Find the DMA node, map the DMA रेजिस्टरs, and decode the DMA IRQs */
	np = of_parse_phandle(pdev->dev.of_node, "axistream-connected", 0);
	अगर (np) अणु
		काष्ठा resource dmares;

		ret = of_address_to_resource(np, 0, &dmares);
		अगर (ret) अणु
			dev_err(&pdev->dev,
				"unable to get DMA resource\n");
			of_node_put(np);
			जाओ cleanup_clk;
		पूर्ण
		lp->dma_regs = devm_ioremap_resource(&pdev->dev,
						     &dmares);
		lp->rx_irq = irq_of_parse_and_map(np, 1);
		lp->tx_irq = irq_of_parse_and_map(np, 0);
		of_node_put(np);
		lp->eth_irq = platक्रमm_get_irq_optional(pdev, 0);
	पूर्ण अन्यथा अणु
		/* Check क्रम these resources directly on the Ethernet node. */
		काष्ठा resource *res = platक्रमm_get_resource(pdev,
							     IORESOURCE_MEM, 1);
		lp->dma_regs = devm_ioremap_resource(&pdev->dev, res);
		lp->rx_irq = platक्रमm_get_irq(pdev, 1);
		lp->tx_irq = platक्रमm_get_irq(pdev, 0);
		lp->eth_irq = platक्रमm_get_irq_optional(pdev, 2);
	पूर्ण
	अगर (IS_ERR(lp->dma_regs)) अणु
		dev_err(&pdev->dev, "could not map DMA regs\n");
		ret = PTR_ERR(lp->dma_regs);
		जाओ cleanup_clk;
	पूर्ण
	अगर ((lp->rx_irq <= 0) || (lp->tx_irq <= 0)) अणु
		dev_err(&pdev->dev, "could not determine irqs\n");
		ret = -ENOMEM;
		जाओ cleanup_clk;
	पूर्ण

	/* Autodetect the need क्रम 64-bit DMA poपूर्णांकers.
	 * When the IP is configured क्रम a bus width bigger than 32 bits,
	 * writing the MSB रेजिस्टरs is mandatory, even अगर they are all 0.
	 * We can detect this हाल by writing all 1's to one such रेजिस्टर
	 * and see अगर that sticks: when the IP is configured क्रम 32 bits
	 * only, those रेजिस्टरs are RES0.
	 * Those MSB रेजिस्टरs were पूर्णांकroduced in IP v7.1, which we check first.
	 */
	अगर ((axienet_ior(lp, XAE_ID_OFFSET) >> 24) >= 0x9) अणु
		व्योम __iomem *desc = lp->dma_regs + XAXIDMA_TX_CDESC_OFFSET + 4;

		ioग_लिखो32(0x0, desc);
		अगर (ioपढ़ो32(desc) == 0) अणु	/* sanity check */
			ioग_लिखो32(0xffffffff, desc);
			अगर (ioपढ़ो32(desc) > 0) अणु
				lp->features |= XAE_FEATURE_DMA_64BIT;
				addr_width = 64;
				dev_info(&pdev->dev,
					 "autodetected 64-bit DMA range\n");
			पूर्ण
			ioग_लिखो32(0x0, desc);
		पूर्ण
	पूर्ण

	ret = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(addr_width));
	अगर (ret) अणु
		dev_err(&pdev->dev, "No suitable DMA available\n");
		जाओ cleanup_clk;
	पूर्ण

	/* Check क्रम Ethernet core IRQ (optional) */
	अगर (lp->eth_irq <= 0)
		dev_info(&pdev->dev, "Ethernet core IRQ not defined\n");

	/* Retrieve the MAC address */
	ret = of_get_mac_address(pdev->dev.of_node, mac_addr);
	अगर (!ret) अणु
		axienet_set_mac_address(ndev, mac_addr);
	पूर्ण अन्यथा अणु
		dev_warn(&pdev->dev, "could not find MAC address property: %d\n",
			 ret);
		axienet_set_mac_address(ndev, शून्य);
	पूर्ण

	lp->coalesce_count_rx = XAXIDMA_DFT_RX_THRESHOLD;
	lp->coalesce_count_tx = XAXIDMA_DFT_TX_THRESHOLD;

	lp->phy_node = of_parse_phandle(pdev->dev.of_node, "phy-handle", 0);
	अगर (lp->phy_node) अणु
		ret = axienet_mdio_setup(lp);
		अगर (ret)
			dev_warn(&pdev->dev,
				 "error registering MDIO bus: %d\n", ret);
	पूर्ण
	अगर (lp->phy_mode == PHY_INTERFACE_MODE_SGMII ||
	    lp->phy_mode == PHY_INTERFACE_MODE_1000BASEX) अणु
		अगर (!lp->phy_node) अणु
			dev_err(&pdev->dev, "phy-handle required for 1000BaseX/SGMII\n");
			ret = -EINVAL;
			जाओ cleanup_mdio;
		पूर्ण
		lp->pcs_phy = of_mdio_find_device(lp->phy_node);
		अगर (!lp->pcs_phy) अणु
			ret = -EPROBE_DEFER;
			जाओ cleanup_mdio;
		पूर्ण
		lp->phylink_config.pcs_poll = true;
	पूर्ण

	lp->phylink_config.dev = &ndev->dev;
	lp->phylink_config.type = PHYLINK_NETDEV;

	lp->phylink = phylink_create(&lp->phylink_config, pdev->dev.fwnode,
				     lp->phy_mode,
				     &axienet_phylink_ops);
	अगर (IS_ERR(lp->phylink)) अणु
		ret = PTR_ERR(lp->phylink);
		dev_err(&pdev->dev, "phylink_create error (%i)\n", ret);
		जाओ cleanup_mdio;
	पूर्ण

	ret = रेजिस्टर_netdev(lp->ndev);
	अगर (ret) अणु
		dev_err(lp->dev, "register_netdev() error (%i)\n", ret);
		जाओ cleanup_phylink;
	पूर्ण

	वापस 0;

cleanup_phylink:
	phylink_destroy(lp->phylink);

cleanup_mdio:
	अगर (lp->pcs_phy)
		put_device(&lp->pcs_phy->dev);
	अगर (lp->mii_bus)
		axienet_mdio_tearकरोwn(lp);
	of_node_put(lp->phy_node);

cleanup_clk:
	clk_bulk_disable_unprepare(XAE_NUM_MISC_CLOCKS, lp->misc_clks);
	clk_disable_unprepare(lp->axi_clk);

मुक्त_netdev:
	मुक्त_netdev(ndev);

	वापस ret;
पूर्ण

अटल पूर्णांक axienet_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *ndev = platक्रमm_get_drvdata(pdev);
	काष्ठा axienet_local *lp = netdev_priv(ndev);

	unरेजिस्टर_netdev(ndev);

	अगर (lp->phylink)
		phylink_destroy(lp->phylink);

	अगर (lp->pcs_phy)
		put_device(&lp->pcs_phy->dev);

	axienet_mdio_tearकरोwn(lp);

	clk_bulk_disable_unprepare(XAE_NUM_MISC_CLOCKS, lp->misc_clks);
	clk_disable_unprepare(lp->axi_clk);

	of_node_put(lp->phy_node);
	lp->phy_node = शून्य;

	मुक्त_netdev(ndev);

	वापस 0;
पूर्ण

अटल व्योम axienet_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *ndev = platक्रमm_get_drvdata(pdev);

	rtnl_lock();
	netअगर_device_detach(ndev);

	अगर (netअगर_running(ndev))
		dev_बंद(ndev);

	rtnl_unlock();
पूर्ण

अटल काष्ठा platक्रमm_driver axienet_driver = अणु
	.probe = axienet_probe,
	.हटाओ = axienet_हटाओ,
	.shutकरोwn = axienet_shutकरोwn,
	.driver = अणु
		 .name = "xilinx_axienet",
		 .of_match_table = axienet_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(axienet_driver);

MODULE_DESCRIPTION("Xilinx Axi Ethernet driver");
MODULE_AUTHOR("Xilinx");
MODULE_LICENSE("GPL");
