<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*******************************************************************************
  This is the driver क्रम the MAC 10/100 on-chip Ethernet controller
  currently tested on all the ST boards based on STb7109 and stx7200 SoCs.

  DWC Ether MAC 10/100 Universal version 4.0 has been used क्रम developing
  this code.

  This only implements the mac core functions क्रम this chip.

  Copyright (C) 2007-2009  STMicroelectronics Ltd


  Author: Giuseppe Cavallaro <peppe.cavallaro@st.com>
*******************************************************************************/

#समावेश <linux/crc32.h>
#समावेश <net/dsa.h>
#समावेश <यंत्र/पन.स>
#समावेश "stmmac.h"
#समावेश "dwmac100.h"

अटल व्योम dwmac100_core_init(काष्ठा mac_device_info *hw,
			       काष्ठा net_device *dev)
अणु
	व्योम __iomem *ioaddr = hw->pcsr;
	u32 value = पढ़ोl(ioaddr + MAC_CONTROL);

	value |= MAC_CORE_INIT;

	/* Clear ASTP bit because Ethernet चयन tagging क्रमmats such as
	 * Broadcom tags can look like invalid LLC/SNAP packets and cause the
	 * hardware to truncate packets on reception.
	 */
	अगर (netdev_uses_dsa(dev))
		value &= ~MAC_CONTROL_ASTP;

	ग_लिखोl(value, ioaddr + MAC_CONTROL);

#अगर_घोषित STMMAC_VLAN_TAG_USED
	ग_लिखोl(ETH_P_8021Q, ioaddr + MAC_VLAN1);
#पूर्ण_अगर
पूर्ण

अटल व्योम dwmac100_dump_mac_regs(काष्ठा mac_device_info *hw, u32 *reg_space)
अणु
	व्योम __iomem *ioaddr = hw->pcsr;

	reg_space[MAC_CONTROL / 4] = पढ़ोl(ioaddr + MAC_CONTROL);
	reg_space[MAC_ADDR_HIGH / 4] = पढ़ोl(ioaddr + MAC_ADDR_HIGH);
	reg_space[MAC_ADDR_LOW / 4] = पढ़ोl(ioaddr + MAC_ADDR_LOW);
	reg_space[MAC_HASH_HIGH / 4] = पढ़ोl(ioaddr + MAC_HASH_HIGH);
	reg_space[MAC_HASH_LOW / 4] = पढ़ोl(ioaddr + MAC_HASH_LOW);
	reg_space[MAC_FLOW_CTRL / 4] = पढ़ोl(ioaddr + MAC_FLOW_CTRL);
	reg_space[MAC_VLAN1 / 4] = पढ़ोl(ioaddr + MAC_VLAN1);
	reg_space[MAC_VLAN2 / 4] = पढ़ोl(ioaddr + MAC_VLAN2);
पूर्ण

अटल पूर्णांक dwmac100_rx_ipc_enable(काष्ठा mac_device_info *hw)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक dwmac100_irq_status(काष्ठा mac_device_info *hw,
			       काष्ठा sपंचांगmac_extra_stats *x)
अणु
	वापस 0;
पूर्ण

अटल व्योम dwmac100_set_umac_addr(काष्ठा mac_device_info *hw,
				   अचिन्हित अक्षर *addr,
				   अचिन्हित पूर्णांक reg_n)
अणु
	व्योम __iomem *ioaddr = hw->pcsr;
	sपंचांगmac_set_mac_addr(ioaddr, addr, MAC_ADDR_HIGH, MAC_ADDR_LOW);
पूर्ण

अटल व्योम dwmac100_get_umac_addr(काष्ठा mac_device_info *hw,
				   अचिन्हित अक्षर *addr,
				   अचिन्हित पूर्णांक reg_n)
अणु
	व्योम __iomem *ioaddr = hw->pcsr;
	sपंचांगmac_get_mac_addr(ioaddr, addr, MAC_ADDR_HIGH, MAC_ADDR_LOW);
पूर्ण

अटल व्योम dwmac100_set_filter(काष्ठा mac_device_info *hw,
				काष्ठा net_device *dev)
अणु
	व्योम __iomem *ioaddr = (व्योम __iomem *)dev->base_addr;
	u32 value = पढ़ोl(ioaddr + MAC_CONTROL);

	अगर (dev->flags & IFF_PROMISC) अणु
		value |= MAC_CONTROL_PR;
		value &= ~(MAC_CONTROL_PM | MAC_CONTROL_IF | MAC_CONTROL_HO |
			   MAC_CONTROL_HP);
	पूर्ण अन्यथा अगर ((netdev_mc_count(dev) > HASH_TABLE_SIZE)
		   || (dev->flags & IFF_ALLMULTI)) अणु
		value |= MAC_CONTROL_PM;
		value &= ~(MAC_CONTROL_PR | MAC_CONTROL_IF | MAC_CONTROL_HO);
		ग_लिखोl(0xffffffff, ioaddr + MAC_HASH_HIGH);
		ग_लिखोl(0xffffffff, ioaddr + MAC_HASH_LOW);
	पूर्ण अन्यथा अगर (netdev_mc_empty(dev)) अणु	/* no multicast */
		value &= ~(MAC_CONTROL_PM | MAC_CONTROL_PR | MAC_CONTROL_IF |
			   MAC_CONTROL_HO | MAC_CONTROL_HP);
	पूर्ण अन्यथा अणु
		u32 mc_filter[2];
		काष्ठा netdev_hw_addr *ha;

		/* Perfect filter mode क्रम physical address and Hash
		 * filter क्रम multicast
		 */
		value |= MAC_CONTROL_HP;
		value &= ~(MAC_CONTROL_PM | MAC_CONTROL_PR |
			   MAC_CONTROL_IF | MAC_CONTROL_HO);

		स_रखो(mc_filter, 0, माप(mc_filter));
		netdev_क्रम_each_mc_addr(ha, dev) अणु
			/* The upper 6 bits of the calculated CRC are used to
			 * index the contens of the hash table
			 */
			पूर्णांक bit_nr = ether_crc(ETH_ALEN, ha->addr) >> 26;
			/* The most signअगरicant bit determines the रेजिस्टर to
			 * use (H/L) जबतक the other 5 bits determine the bit
			 * within the रेजिस्टर.
			 */
			mc_filter[bit_nr >> 5] |= 1 << (bit_nr & 31);
		पूर्ण
		ग_लिखोl(mc_filter[0], ioaddr + MAC_HASH_LOW);
		ग_लिखोl(mc_filter[1], ioaddr + MAC_HASH_HIGH);
	पूर्ण

	ग_लिखोl(value, ioaddr + MAC_CONTROL);
पूर्ण

अटल व्योम dwmac100_flow_ctrl(काष्ठा mac_device_info *hw, अचिन्हित पूर्णांक duplex,
			       अचिन्हित पूर्णांक fc, अचिन्हित पूर्णांक छोड़ो_समय,
			       u32 tx_cnt)
अणु
	व्योम __iomem *ioaddr = hw->pcsr;
	अचिन्हित पूर्णांक flow = MAC_FLOW_CTRL_ENABLE;

	अगर (duplex)
		flow |= (छोड़ो_समय << MAC_FLOW_CTRL_PT_SHIFT);
	ग_लिखोl(flow, ioaddr + MAC_FLOW_CTRL);
पूर्ण

/* No PMT module supported on ST boards with this Eth chip. */
अटल व्योम dwmac100_pmt(काष्ठा mac_device_info *hw, अचिन्हित दीर्घ mode)
अणु
	वापस;
पूर्ण

अटल व्योम dwmac100_set_mac_loopback(व्योम __iomem *ioaddr, bool enable)
अणु
	u32 value = पढ़ोl(ioaddr + MAC_CONTROL);

	अगर (enable)
		value |= MAC_CONTROL_OM;
	अन्यथा
		value &= ~MAC_CONTROL_OM;

	ग_लिखोl(value, ioaddr + MAC_CONTROL);
पूर्ण

स्थिर काष्ठा sपंचांगmac_ops dwmac100_ops = अणु
	.core_init = dwmac100_core_init,
	.set_mac = sपंचांगmac_set_mac,
	.rx_ipc = dwmac100_rx_ipc_enable,
	.dump_regs = dwmac100_dump_mac_regs,
	.host_irq_status = dwmac100_irq_status,
	.set_filter = dwmac100_set_filter,
	.flow_ctrl = dwmac100_flow_ctrl,
	.pmt = dwmac100_pmt,
	.set_umac_addr = dwmac100_set_umac_addr,
	.get_umac_addr = dwmac100_get_umac_addr,
	.set_mac_loopback = dwmac100_set_mac_loopback,
पूर्ण;

पूर्णांक dwmac100_setup(काष्ठा sपंचांगmac_priv *priv)
अणु
	काष्ठा mac_device_info *mac = priv->hw;

	dev_info(priv->device, "\tDWMAC100\n");

	mac->pcsr = priv->ioaddr;
	mac->link.duplex = MAC_CONTROL_F;
	mac->link.speed10 = 0;
	mac->link.speed100 = 0;
	mac->link.speed1000 = 0;
	mac->link.speed_mask = MAC_CONTROL_PS;
	mac->mii.addr = MAC_MII_ADDR;
	mac->mii.data = MAC_MII_DATA;
	mac->mii.addr_shअगरt = 11;
	mac->mii.addr_mask = 0x0000F800;
	mac->mii.reg_shअगरt = 6;
	mac->mii.reg_mask = 0x000007C0;
	mac->mii.clk_csr_shअगरt = 2;
	mac->mii.clk_csr_mask = GENMASK(5, 2);

	वापस 0;
पूर्ण
