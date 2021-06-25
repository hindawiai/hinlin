<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* niu.c: Neptune ethernet driver.
 *
 * Copyright (C) 2007, 2008 David S. Miller (davem@davemloft.net)
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/delay.h>
#समावेश <linux/bitops.h>
#समावेश <linux/mii.h>
#समावेश <linux/अगर.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/ip.h>
#समावेश <linux/in.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/log2.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/crc32.h>
#समावेश <linux/list.h>
#समावेश <linux/slab.h>

#समावेश <linux/पन.स>
#समावेश <linux/of_device.h>

#समावेश "niu.h"

#घोषणा DRV_MODULE_NAME		"niu"
#घोषणा DRV_MODULE_VERSION	"1.1"
#घोषणा DRV_MODULE_RELDATE	"Apr 22, 2010"

अटल अक्षर version[] =
	DRV_MODULE_NAME ".c:v" DRV_MODULE_VERSION " (" DRV_MODULE_RELDATE ")\n";

MODULE_AUTHOR("David S. Miller (davem@davemloft.net)");
MODULE_DESCRIPTION("NIU ethernet driver");
MODULE_LICENSE("GPL");
MODULE_VERSION(DRV_MODULE_VERSION);

#अगर_अघोषित पढ़ोq
अटल u64 पढ़ोq(व्योम __iomem *reg)
अणु
	वापस ((u64) पढ़ोl(reg)) | (((u64) पढ़ोl(reg + 4UL)) << 32);
पूर्ण

अटल व्योम ग_लिखोq(u64 val, व्योम __iomem *reg)
अणु
	ग_लिखोl(val & 0xffffffff, reg);
	ग_लिखोl(val >> 32, reg + 0x4UL);
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा pci_device_id niu_pci_tbl[] = अणु
	अणुPCI_DEVICE(PCI_VENDOR_ID_SUN, 0xabcd)पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, niu_pci_tbl);

#घोषणा NIU_TX_TIMEOUT			(5 * HZ)

#घोषणा nr64(reg)		पढ़ोq(np->regs + (reg))
#घोषणा nw64(reg, val)		ग_लिखोq((val), np->regs + (reg))

#घोषणा nr64_mac(reg)		पढ़ोq(np->mac_regs + (reg))
#घोषणा nw64_mac(reg, val)	ग_लिखोq((val), np->mac_regs + (reg))

#घोषणा nr64_ipp(reg)		पढ़ोq(np->regs + np->ipp_off + (reg))
#घोषणा nw64_ipp(reg, val)	ग_लिखोq((val), np->regs + np->ipp_off + (reg))

#घोषणा nr64_pcs(reg)		पढ़ोq(np->regs + np->pcs_off + (reg))
#घोषणा nw64_pcs(reg, val)	ग_लिखोq((val), np->regs + np->pcs_off + (reg))

#घोषणा nr64_xpcs(reg)		पढ़ोq(np->regs + np->xpcs_off + (reg))
#घोषणा nw64_xpcs(reg, val)	ग_लिखोq((val), np->regs + np->xpcs_off + (reg))

#घोषणा NIU_MSG_DEFAULT (NETIF_MSG_DRV | NETIF_MSG_PROBE | NETIF_MSG_LINK)

अटल पूर्णांक niu_debug;
अटल पूर्णांक debug = -1;
module_param(debug, पूर्णांक, 0);
MODULE_PARM_DESC(debug, "NIU debug level");

#घोषणा niu_lock_parent(np, flags) \
	spin_lock_irqsave(&np->parent->lock, flags)
#घोषणा niu_unlock_parent(np, flags) \
	spin_unlock_irqrestore(&np->parent->lock, flags)

अटल पूर्णांक serdes_init_10g_serdes(काष्ठा niu *np);

अटल पूर्णांक __niu_रुको_bits_clear_mac(काष्ठा niu *np, अचिन्हित दीर्घ reg,
				     u64 bits, पूर्णांक limit, पूर्णांक delay)
अणु
	जबतक (--limit >= 0) अणु
		u64 val = nr64_mac(reg);

		अगर (!(val & bits))
			अवरोध;
		udelay(delay);
	पूर्ण
	अगर (limit < 0)
		वापस -ENODEV;
	वापस 0;
पूर्ण

अटल पूर्णांक __niu_set_and_रुको_clear_mac(काष्ठा niu *np, अचिन्हित दीर्घ reg,
					u64 bits, पूर्णांक limit, पूर्णांक delay,
					स्थिर अक्षर *reg_name)
अणु
	पूर्णांक err;

	nw64_mac(reg, bits);
	err = __niu_रुको_bits_clear_mac(np, reg, bits, limit, delay);
	अगर (err)
		netdev_err(np->dev, "bits (%llx) of register %s would not clear, val[%llx]\n",
			   (अचिन्हित दीर्घ दीर्घ)bits, reg_name,
			   (अचिन्हित दीर्घ दीर्घ)nr64_mac(reg));
	वापस err;
पूर्ण

#घोषणा niu_set_and_रुको_clear_mac(NP, REG, BITS, LIMIT, DELAY, REG_NAME) \
(अणु	BUILD_BUG_ON(LIMIT <= 0 || DELAY < 0); \
	__niu_set_and_रुको_clear_mac(NP, REG, BITS, LIMIT, DELAY, REG_NAME); \
पूर्ण)

अटल पूर्णांक __niu_रुको_bits_clear_ipp(काष्ठा niu *np, अचिन्हित दीर्घ reg,
				     u64 bits, पूर्णांक limit, पूर्णांक delay)
अणु
	जबतक (--limit >= 0) अणु
		u64 val = nr64_ipp(reg);

		अगर (!(val & bits))
			अवरोध;
		udelay(delay);
	पूर्ण
	अगर (limit < 0)
		वापस -ENODEV;
	वापस 0;
पूर्ण

अटल पूर्णांक __niu_set_and_रुको_clear_ipp(काष्ठा niu *np, अचिन्हित दीर्घ reg,
					u64 bits, पूर्णांक limit, पूर्णांक delay,
					स्थिर अक्षर *reg_name)
अणु
	पूर्णांक err;
	u64 val;

	val = nr64_ipp(reg);
	val |= bits;
	nw64_ipp(reg, val);

	err = __niu_रुको_bits_clear_ipp(np, reg, bits, limit, delay);
	अगर (err)
		netdev_err(np->dev, "bits (%llx) of register %s would not clear, val[%llx]\n",
			   (अचिन्हित दीर्घ दीर्घ)bits, reg_name,
			   (अचिन्हित दीर्घ दीर्घ)nr64_ipp(reg));
	वापस err;
पूर्ण

#घोषणा niu_set_and_रुको_clear_ipp(NP, REG, BITS, LIMIT, DELAY, REG_NAME) \
(अणु	BUILD_BUG_ON(LIMIT <= 0 || DELAY < 0); \
	__niu_set_and_रुको_clear_ipp(NP, REG, BITS, LIMIT, DELAY, REG_NAME); \
पूर्ण)

अटल पूर्णांक __niu_रुको_bits_clear(काष्ठा niu *np, अचिन्हित दीर्घ reg,
				 u64 bits, पूर्णांक limit, पूर्णांक delay)
अणु
	जबतक (--limit >= 0) अणु
		u64 val = nr64(reg);

		अगर (!(val & bits))
			अवरोध;
		udelay(delay);
	पूर्ण
	अगर (limit < 0)
		वापस -ENODEV;
	वापस 0;
पूर्ण

#घोषणा niu_रुको_bits_clear(NP, REG, BITS, LIMIT, DELAY) \
(अणु	BUILD_BUG_ON(LIMIT <= 0 || DELAY < 0); \
	__niu_रुको_bits_clear(NP, REG, BITS, LIMIT, DELAY); \
पूर्ण)

अटल पूर्णांक __niu_set_and_रुको_clear(काष्ठा niu *np, अचिन्हित दीर्घ reg,
				    u64 bits, पूर्णांक limit, पूर्णांक delay,
				    स्थिर अक्षर *reg_name)
अणु
	पूर्णांक err;

	nw64(reg, bits);
	err = __niu_रुको_bits_clear(np, reg, bits, limit, delay);
	अगर (err)
		netdev_err(np->dev, "bits (%llx) of register %s would not clear, val[%llx]\n",
			   (अचिन्हित दीर्घ दीर्घ)bits, reg_name,
			   (अचिन्हित दीर्घ दीर्घ)nr64(reg));
	वापस err;
पूर्ण

#घोषणा niu_set_and_रुको_clear(NP, REG, BITS, LIMIT, DELAY, REG_NAME) \
(अणु	BUILD_BUG_ON(LIMIT <= 0 || DELAY < 0); \
	__niu_set_and_रुको_clear(NP, REG, BITS, LIMIT, DELAY, REG_NAME); \
पूर्ण)

अटल व्योम niu_ldg_rearm(काष्ठा niu *np, काष्ठा niu_ldg *lp, पूर्णांक on)
अणु
	u64 val = (u64) lp->समयr;

	अगर (on)
		val |= LDG_IMGMT_ARM;

	nw64(LDG_IMGMT(lp->ldg_num), val);
पूर्ण

अटल पूर्णांक niu_ldn_irq_enable(काष्ठा niu *np, पूर्णांक ldn, पूर्णांक on)
अणु
	अचिन्हित दीर्घ mask_reg, bits;
	u64 val;

	अगर (ldn < 0 || ldn > LDN_MAX)
		वापस -EINVAL;

	अगर (ldn < 64) अणु
		mask_reg = LD_IM0(ldn);
		bits = LD_IM0_MASK;
	पूर्ण अन्यथा अणु
		mask_reg = LD_IM1(ldn - 64);
		bits = LD_IM1_MASK;
	पूर्ण

	val = nr64(mask_reg);
	अगर (on)
		val &= ~bits;
	अन्यथा
		val |= bits;
	nw64(mask_reg, val);

	वापस 0;
पूर्ण

अटल पूर्णांक niu_enable_ldn_in_ldg(काष्ठा niu *np, काष्ठा niu_ldg *lp, पूर्णांक on)
अणु
	काष्ठा niu_parent *parent = np->parent;
	पूर्णांक i;

	क्रम (i = 0; i <= LDN_MAX; i++) अणु
		पूर्णांक err;

		अगर (parent->ldg_map[i] != lp->ldg_num)
			जारी;

		err = niu_ldn_irq_enable(np, i, on);
		अगर (err)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक niu_enable_पूर्णांकerrupts(काष्ठा niu *np, पूर्णांक on)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < np->num_ldg; i++) अणु
		काष्ठा niu_ldg *lp = &np->ldg[i];
		पूर्णांक err;

		err = niu_enable_ldn_in_ldg(np, lp, on);
		अगर (err)
			वापस err;
	पूर्ण
	क्रम (i = 0; i < np->num_ldg; i++)
		niu_ldg_rearm(np, &np->ldg[i], on);

	वापस 0;
पूर्ण

अटल u32 phy_encode(u32 type, पूर्णांक port)
अणु
	वापस type << (port * 2);
पूर्ण

अटल u32 phy_decode(u32 val, पूर्णांक port)
अणु
	वापस (val >> (port * 2)) & PORT_TYPE_MASK;
पूर्ण

अटल पूर्णांक mdio_रुको(काष्ठा niu *np)
अणु
	पूर्णांक limit = 1000;
	u64 val;

	जबतक (--limit > 0) अणु
		val = nr64(MIF_FRAME_OUTPUT);
		अगर ((val >> MIF_FRAME_OUTPUT_TA_SHIFT) & 0x1)
			वापस val & MIF_FRAME_OUTPUT_DATA;

		udelay(10);
	पूर्ण

	वापस -ENODEV;
पूर्ण

अटल पूर्णांक mdio_पढ़ो(काष्ठा niu *np, पूर्णांक port, पूर्णांक dev, पूर्णांक reg)
अणु
	पूर्णांक err;

	nw64(MIF_FRAME_OUTPUT, MDIO_ADDR_OP(port, dev, reg));
	err = mdio_रुको(np);
	अगर (err < 0)
		वापस err;

	nw64(MIF_FRAME_OUTPUT, MDIO_READ_OP(port, dev));
	वापस mdio_रुको(np);
पूर्ण

अटल पूर्णांक mdio_ग_लिखो(काष्ठा niu *np, पूर्णांक port, पूर्णांक dev, पूर्णांक reg, पूर्णांक data)
अणु
	पूर्णांक err;

	nw64(MIF_FRAME_OUTPUT, MDIO_ADDR_OP(port, dev, reg));
	err = mdio_रुको(np);
	अगर (err < 0)
		वापस err;

	nw64(MIF_FRAME_OUTPUT, MDIO_WRITE_OP(port, dev, data));
	err = mdio_रुको(np);
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक mii_पढ़ो(काष्ठा niu *np, पूर्णांक port, पूर्णांक reg)
अणु
	nw64(MIF_FRAME_OUTPUT, MII_READ_OP(port, reg));
	वापस mdio_रुको(np);
पूर्ण

अटल पूर्णांक mii_ग_लिखो(काष्ठा niu *np, पूर्णांक port, पूर्णांक reg, पूर्णांक data)
अणु
	पूर्णांक err;

	nw64(MIF_FRAME_OUTPUT, MII_WRITE_OP(port, reg, data));
	err = mdio_रुको(np);
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक esr2_set_tx_cfg(काष्ठा niu *np, अचिन्हित दीर्घ channel, u32 val)
अणु
	पूर्णांक err;

	err = mdio_ग_लिखो(np, np->port, NIU_ESR2_DEV_ADDR,
			 ESR2_TI_PLL_TX_CFG_L(channel),
			 val & 0xffff);
	अगर (!err)
		err = mdio_ग_लिखो(np, np->port, NIU_ESR2_DEV_ADDR,
				 ESR2_TI_PLL_TX_CFG_H(channel),
				 val >> 16);
	वापस err;
पूर्ण

अटल पूर्णांक esr2_set_rx_cfg(काष्ठा niu *np, अचिन्हित दीर्घ channel, u32 val)
अणु
	पूर्णांक err;

	err = mdio_ग_लिखो(np, np->port, NIU_ESR2_DEV_ADDR,
			 ESR2_TI_PLL_RX_CFG_L(channel),
			 val & 0xffff);
	अगर (!err)
		err = mdio_ग_लिखो(np, np->port, NIU_ESR2_DEV_ADDR,
				 ESR2_TI_PLL_RX_CFG_H(channel),
				 val >> 16);
	वापस err;
पूर्ण

/* Mode is always 10G fiber.  */
अटल पूर्णांक serdes_init_niu_10g_fiber(काष्ठा niu *np)
अणु
	काष्ठा niu_link_config *lp = &np->link_config;
	u32 tx_cfg, rx_cfg;
	अचिन्हित दीर्घ i;

	tx_cfg = (PLL_TX_CFG_ENTX | PLL_TX_CFG_SWING_1375MV);
	rx_cfg = (PLL_RX_CFG_ENRX | PLL_RX_CFG_TERM_0P8VDDT |
		  PLL_RX_CFG_ALIGN_ENA | PLL_RX_CFG_LOS_LTHRESH |
		  PLL_RX_CFG_EQ_LP_ADAPTIVE);

	अगर (lp->loopback_mode == LOOPBACK_PHY) अणु
		u16 test_cfg = PLL_TEST_CFG_LOOPBACK_CML_DIS;

		mdio_ग_लिखो(np, np->port, NIU_ESR2_DEV_ADDR,
			   ESR2_TI_PLL_TEST_CFG_L, test_cfg);

		tx_cfg |= PLL_TX_CFG_ENTEST;
		rx_cfg |= PLL_RX_CFG_ENTEST;
	पूर्ण

	/* Initialize all 4 lanes of the SERDES.  */
	क्रम (i = 0; i < 4; i++) अणु
		पूर्णांक err = esr2_set_tx_cfg(np, i, tx_cfg);
		अगर (err)
			वापस err;
	पूर्ण

	क्रम (i = 0; i < 4; i++) अणु
		पूर्णांक err = esr2_set_rx_cfg(np, i, rx_cfg);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक serdes_init_niu_1g_serdes(काष्ठा niu *np)
अणु
	काष्ठा niu_link_config *lp = &np->link_config;
	u16 pll_cfg, pll_sts;
	पूर्णांक max_retry = 100;
	u64 sig, mask, val;
	u32 tx_cfg, rx_cfg;
	अचिन्हित दीर्घ i;
	पूर्णांक err;

	tx_cfg = (PLL_TX_CFG_ENTX | PLL_TX_CFG_SWING_1375MV |
		  PLL_TX_CFG_RATE_HALF);
	rx_cfg = (PLL_RX_CFG_ENRX | PLL_RX_CFG_TERM_0P8VDDT |
		  PLL_RX_CFG_ALIGN_ENA | PLL_RX_CFG_LOS_LTHRESH |
		  PLL_RX_CFG_RATE_HALF);

	अगर (np->port == 0)
		rx_cfg |= PLL_RX_CFG_EQ_LP_ADAPTIVE;

	अगर (lp->loopback_mode == LOOPBACK_PHY) अणु
		u16 test_cfg = PLL_TEST_CFG_LOOPBACK_CML_DIS;

		mdio_ग_लिखो(np, np->port, NIU_ESR2_DEV_ADDR,
			   ESR2_TI_PLL_TEST_CFG_L, test_cfg);

		tx_cfg |= PLL_TX_CFG_ENTEST;
		rx_cfg |= PLL_RX_CFG_ENTEST;
	पूर्ण

	/* Initialize PLL क्रम 1G */
	pll_cfg = (PLL_CFG_ENPLL | PLL_CFG_MPY_8X);

	err = mdio_ग_लिखो(np, np->port, NIU_ESR2_DEV_ADDR,
			 ESR2_TI_PLL_CFG_L, pll_cfg);
	अगर (err) अणु
		netdev_err(np->dev, "NIU Port %d %s() mdio write to ESR2_TI_PLL_CFG_L failed\n",
			   np->port, __func__);
		वापस err;
	पूर्ण

	pll_sts = PLL_CFG_ENPLL;

	err = mdio_ग_लिखो(np, np->port, NIU_ESR2_DEV_ADDR,
			 ESR2_TI_PLL_STS_L, pll_sts);
	अगर (err) अणु
		netdev_err(np->dev, "NIU Port %d %s() mdio write to ESR2_TI_PLL_STS_L failed\n",
			   np->port, __func__);
		वापस err;
	पूर्ण

	udelay(200);

	/* Initialize all 4 lanes of the SERDES.  */
	क्रम (i = 0; i < 4; i++) अणु
		err = esr2_set_tx_cfg(np, i, tx_cfg);
		अगर (err)
			वापस err;
	पूर्ण

	क्रम (i = 0; i < 4; i++) अणु
		err = esr2_set_rx_cfg(np, i, rx_cfg);
		अगर (err)
			वापस err;
	पूर्ण

	चयन (np->port) अणु
	हाल 0:
		val = (ESR_INT_SRDY0_P0 | ESR_INT_DET0_P0);
		mask = val;
		अवरोध;

	हाल 1:
		val = (ESR_INT_SRDY0_P1 | ESR_INT_DET0_P1);
		mask = val;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	जबतक (max_retry--) अणु
		sig = nr64(ESR_INT_SIGNALS);
		अगर ((sig & mask) == val)
			अवरोध;

		mdelay(500);
	पूर्ण

	अगर ((sig & mask) != val) अणु
		netdev_err(np->dev, "Port %u signal bits [%08x] are not [%08x]\n",
			   np->port, (पूर्णांक)(sig & mask), (पूर्णांक)val);
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक serdes_init_niu_10g_serdes(काष्ठा niu *np)
अणु
	काष्ठा niu_link_config *lp = &np->link_config;
	u32 tx_cfg, rx_cfg, pll_cfg, pll_sts;
	पूर्णांक max_retry = 100;
	u64 sig, mask, val;
	अचिन्हित दीर्घ i;
	पूर्णांक err;

	tx_cfg = (PLL_TX_CFG_ENTX | PLL_TX_CFG_SWING_1375MV);
	rx_cfg = (PLL_RX_CFG_ENRX | PLL_RX_CFG_TERM_0P8VDDT |
		  PLL_RX_CFG_ALIGN_ENA | PLL_RX_CFG_LOS_LTHRESH |
		  PLL_RX_CFG_EQ_LP_ADAPTIVE);

	अगर (lp->loopback_mode == LOOPBACK_PHY) अणु
		u16 test_cfg = PLL_TEST_CFG_LOOPBACK_CML_DIS;

		mdio_ग_लिखो(np, np->port, NIU_ESR2_DEV_ADDR,
			   ESR2_TI_PLL_TEST_CFG_L, test_cfg);

		tx_cfg |= PLL_TX_CFG_ENTEST;
		rx_cfg |= PLL_RX_CFG_ENTEST;
	पूर्ण

	/* Initialize PLL क्रम 10G */
	pll_cfg = (PLL_CFG_ENPLL | PLL_CFG_MPY_10X);

	err = mdio_ग_लिखो(np, np->port, NIU_ESR2_DEV_ADDR,
			 ESR2_TI_PLL_CFG_L, pll_cfg & 0xffff);
	अगर (err) अणु
		netdev_err(np->dev, "NIU Port %d %s() mdio write to ESR2_TI_PLL_CFG_L failed\n",
			   np->port, __func__);
		वापस err;
	पूर्ण

	pll_sts = PLL_CFG_ENPLL;

	err = mdio_ग_लिखो(np, np->port, NIU_ESR2_DEV_ADDR,
			 ESR2_TI_PLL_STS_L, pll_sts & 0xffff);
	अगर (err) अणु
		netdev_err(np->dev, "NIU Port %d %s() mdio write to ESR2_TI_PLL_STS_L failed\n",
			   np->port, __func__);
		वापस err;
	पूर्ण

	udelay(200);

	/* Initialize all 4 lanes of the SERDES.  */
	क्रम (i = 0; i < 4; i++) अणु
		err = esr2_set_tx_cfg(np, i, tx_cfg);
		अगर (err)
			वापस err;
	पूर्ण

	क्रम (i = 0; i < 4; i++) अणु
		err = esr2_set_rx_cfg(np, i, rx_cfg);
		अगर (err)
			वापस err;
	पूर्ण

	/* check अगर serdes is पढ़ोy */

	चयन (np->port) अणु
	हाल 0:
		mask = ESR_INT_SIGNALS_P0_BITS;
		val = (ESR_INT_SRDY0_P0 |
		       ESR_INT_DET0_P0 |
		       ESR_INT_XSRDY_P0 |
		       ESR_INT_XDP_P0_CH3 |
		       ESR_INT_XDP_P0_CH2 |
		       ESR_INT_XDP_P0_CH1 |
		       ESR_INT_XDP_P0_CH0);
		अवरोध;

	हाल 1:
		mask = ESR_INT_SIGNALS_P1_BITS;
		val = (ESR_INT_SRDY0_P1 |
		       ESR_INT_DET0_P1 |
		       ESR_INT_XSRDY_P1 |
		       ESR_INT_XDP_P1_CH3 |
		       ESR_INT_XDP_P1_CH2 |
		       ESR_INT_XDP_P1_CH1 |
		       ESR_INT_XDP_P1_CH0);
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	जबतक (max_retry--) अणु
		sig = nr64(ESR_INT_SIGNALS);
		अगर ((sig & mask) == val)
			अवरोध;

		mdelay(500);
	पूर्ण

	अगर ((sig & mask) != val) अणु
		pr_info("NIU Port %u signal bits [%08x] are not [%08x] for 10G...trying 1G\n",
			np->port, (पूर्णांक)(sig & mask), (पूर्णांक)val);

		/* 10G failed, try initializing at 1G */
		err = serdes_init_niu_1g_serdes(np);
		अगर (!err) अणु
			np->flags &= ~NIU_FLAGS_10G;
			np->mac_xcvr = MAC_XCVR_PCS;
		पूर्ण  अन्यथा अणु
			netdev_err(np->dev, "Port %u 10G/1G SERDES Link Failed\n",
				   np->port);
			वापस -ENODEV;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक esr_पढ़ो_rxtx_ctrl(काष्ठा niu *np, अचिन्हित दीर्घ chan, u32 *val)
अणु
	पूर्णांक err;

	err = mdio_पढ़ो(np, np->port, NIU_ESR_DEV_ADDR, ESR_RXTX_CTRL_L(chan));
	अगर (err >= 0) अणु
		*val = (err & 0xffff);
		err = mdio_पढ़ो(np, np->port, NIU_ESR_DEV_ADDR,
				ESR_RXTX_CTRL_H(chan));
		अगर (err >= 0)
			*val |= ((err & 0xffff) << 16);
		err = 0;
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक esr_पढ़ो_glue0(काष्ठा niu *np, अचिन्हित दीर्घ chan, u32 *val)
अणु
	पूर्णांक err;

	err = mdio_पढ़ो(np, np->port, NIU_ESR_DEV_ADDR,
			ESR_GLUE_CTRL0_L(chan));
	अगर (err >= 0) अणु
		*val = (err & 0xffff);
		err = mdio_पढ़ो(np, np->port, NIU_ESR_DEV_ADDR,
				ESR_GLUE_CTRL0_H(chan));
		अगर (err >= 0) अणु
			*val |= ((err & 0xffff) << 16);
			err = 0;
		पूर्ण
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक esr_पढ़ो_reset(काष्ठा niu *np, u32 *val)
अणु
	पूर्णांक err;

	err = mdio_पढ़ो(np, np->port, NIU_ESR_DEV_ADDR,
			ESR_RXTX_RESET_CTRL_L);
	अगर (err >= 0) अणु
		*val = (err & 0xffff);
		err = mdio_पढ़ो(np, np->port, NIU_ESR_DEV_ADDR,
				ESR_RXTX_RESET_CTRL_H);
		अगर (err >= 0) अणु
			*val |= ((err & 0xffff) << 16);
			err = 0;
		पूर्ण
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक esr_ग_लिखो_rxtx_ctrl(काष्ठा niu *np, अचिन्हित दीर्घ chan, u32 val)
अणु
	पूर्णांक err;

	err = mdio_ग_लिखो(np, np->port, NIU_ESR_DEV_ADDR,
			 ESR_RXTX_CTRL_L(chan), val & 0xffff);
	अगर (!err)
		err = mdio_ग_लिखो(np, np->port, NIU_ESR_DEV_ADDR,
				 ESR_RXTX_CTRL_H(chan), (val >> 16));
	वापस err;
पूर्ण

अटल पूर्णांक esr_ग_लिखो_glue0(काष्ठा niu *np, अचिन्हित दीर्घ chan, u32 val)
अणु
	पूर्णांक err;

	err = mdio_ग_लिखो(np, np->port, NIU_ESR_DEV_ADDR,
			ESR_GLUE_CTRL0_L(chan), val & 0xffff);
	अगर (!err)
		err = mdio_ग_लिखो(np, np->port, NIU_ESR_DEV_ADDR,
				 ESR_GLUE_CTRL0_H(chan), (val >> 16));
	वापस err;
पूर्ण

अटल पूर्णांक esr_reset(काष्ठा niu *np)
अणु
	u32 reset;
	पूर्णांक err;

	err = mdio_ग_लिखो(np, np->port, NIU_ESR_DEV_ADDR,
			 ESR_RXTX_RESET_CTRL_L, 0x0000);
	अगर (err)
		वापस err;
	err = mdio_ग_लिखो(np, np->port, NIU_ESR_DEV_ADDR,
			 ESR_RXTX_RESET_CTRL_H, 0xffff);
	अगर (err)
		वापस err;
	udelay(200);

	err = mdio_ग_लिखो(np, np->port, NIU_ESR_DEV_ADDR,
			 ESR_RXTX_RESET_CTRL_L, 0xffff);
	अगर (err)
		वापस err;
	udelay(200);

	err = mdio_ग_लिखो(np, np->port, NIU_ESR_DEV_ADDR,
			 ESR_RXTX_RESET_CTRL_H, 0x0000);
	अगर (err)
		वापस err;
	udelay(200);

	err = esr_पढ़ो_reset(np, &reset);
	अगर (err)
		वापस err;
	अगर (reset != 0) अणु
		netdev_err(np->dev, "Port %u ESR_RESET did not clear [%08x]\n",
			   np->port, reset);
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक serdes_init_10g(काष्ठा niu *np)
अणु
	काष्ठा niu_link_config *lp = &np->link_config;
	अचिन्हित दीर्घ ctrl_reg, test_cfg_reg, i;
	u64 ctrl_val, test_cfg_val, sig, mask, val;
	पूर्णांक err;

	चयन (np->port) अणु
	हाल 0:
		ctrl_reg = ENET_SERDES_0_CTRL_CFG;
		test_cfg_reg = ENET_SERDES_0_TEST_CFG;
		अवरोध;
	हाल 1:
		ctrl_reg = ENET_SERDES_1_CTRL_CFG;
		test_cfg_reg = ENET_SERDES_1_TEST_CFG;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण
	ctrl_val = (ENET_SERDES_CTRL_SDET_0 |
		    ENET_SERDES_CTRL_SDET_1 |
		    ENET_SERDES_CTRL_SDET_2 |
		    ENET_SERDES_CTRL_SDET_3 |
		    (0x5 << ENET_SERDES_CTRL_EMPH_0_SHIFT) |
		    (0x5 << ENET_SERDES_CTRL_EMPH_1_SHIFT) |
		    (0x5 << ENET_SERDES_CTRL_EMPH_2_SHIFT) |
		    (0x5 << ENET_SERDES_CTRL_EMPH_3_SHIFT) |
		    (0x1 << ENET_SERDES_CTRL_LADJ_0_SHIFT) |
		    (0x1 << ENET_SERDES_CTRL_LADJ_1_SHIFT) |
		    (0x1 << ENET_SERDES_CTRL_LADJ_2_SHIFT) |
		    (0x1 << ENET_SERDES_CTRL_LADJ_3_SHIFT));
	test_cfg_val = 0;

	अगर (lp->loopback_mode == LOOPBACK_PHY) अणु
		test_cfg_val |= ((ENET_TEST_MD_PAD_LOOPBACK <<
				  ENET_SERDES_TEST_MD_0_SHIFT) |
				 (ENET_TEST_MD_PAD_LOOPBACK <<
				  ENET_SERDES_TEST_MD_1_SHIFT) |
				 (ENET_TEST_MD_PAD_LOOPBACK <<
				  ENET_SERDES_TEST_MD_2_SHIFT) |
				 (ENET_TEST_MD_PAD_LOOPBACK <<
				  ENET_SERDES_TEST_MD_3_SHIFT));
	पूर्ण

	nw64(ctrl_reg, ctrl_val);
	nw64(test_cfg_reg, test_cfg_val);

	/* Initialize all 4 lanes of the SERDES.  */
	क्रम (i = 0; i < 4; i++) अणु
		u32 rxtx_ctrl, glue0;

		err = esr_पढ़ो_rxtx_ctrl(np, i, &rxtx_ctrl);
		अगर (err)
			वापस err;
		err = esr_पढ़ो_glue0(np, i, &glue0);
		अगर (err)
			वापस err;

		rxtx_ctrl &= ~(ESR_RXTX_CTRL_VMUXLO);
		rxtx_ctrl |= (ESR_RXTX_CTRL_ENSTRETCH |
			      (2 << ESR_RXTX_CTRL_VMUXLO_SHIFT));

		glue0 &= ~(ESR_GLUE_CTRL0_SRATE |
			   ESR_GLUE_CTRL0_THCNT |
			   ESR_GLUE_CTRL0_BLTIME);
		glue0 |= (ESR_GLUE_CTRL0_RXLOSENAB |
			  (0xf << ESR_GLUE_CTRL0_SRATE_SHIFT) |
			  (0xff << ESR_GLUE_CTRL0_THCNT_SHIFT) |
			  (BLTIME_300_CYCLES <<
			   ESR_GLUE_CTRL0_BLTIME_SHIFT));

		err = esr_ग_लिखो_rxtx_ctrl(np, i, rxtx_ctrl);
		अगर (err)
			वापस err;
		err = esr_ग_लिखो_glue0(np, i, glue0);
		अगर (err)
			वापस err;
	पूर्ण

	err = esr_reset(np);
	अगर (err)
		वापस err;

	sig = nr64(ESR_INT_SIGNALS);
	चयन (np->port) अणु
	हाल 0:
		mask = ESR_INT_SIGNALS_P0_BITS;
		val = (ESR_INT_SRDY0_P0 |
		       ESR_INT_DET0_P0 |
		       ESR_INT_XSRDY_P0 |
		       ESR_INT_XDP_P0_CH3 |
		       ESR_INT_XDP_P0_CH2 |
		       ESR_INT_XDP_P0_CH1 |
		       ESR_INT_XDP_P0_CH0);
		अवरोध;

	हाल 1:
		mask = ESR_INT_SIGNALS_P1_BITS;
		val = (ESR_INT_SRDY0_P1 |
		       ESR_INT_DET0_P1 |
		       ESR_INT_XSRDY_P1 |
		       ESR_INT_XDP_P1_CH3 |
		       ESR_INT_XDP_P1_CH2 |
		       ESR_INT_XDP_P1_CH1 |
		       ESR_INT_XDP_P1_CH0);
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर ((sig & mask) != val) अणु
		अगर (np->flags & NIU_FLAGS_HOTPLUG_PHY) अणु
			np->flags &= ~NIU_FLAGS_HOTPLUG_PHY_PRESENT;
			वापस 0;
		पूर्ण
		netdev_err(np->dev, "Port %u signal bits [%08x] are not [%08x]\n",
			   np->port, (पूर्णांक)(sig & mask), (पूर्णांक)val);
		वापस -ENODEV;
	पूर्ण
	अगर (np->flags & NIU_FLAGS_HOTPLUG_PHY)
		np->flags |= NIU_FLAGS_HOTPLUG_PHY_PRESENT;
	वापस 0;
पूर्ण

अटल पूर्णांक serdes_init_1g(काष्ठा niu *np)
अणु
	u64 val;

	val = nr64(ENET_SERDES_1_PLL_CFG);
	val &= ~ENET_SERDES_PLL_FBDIV2;
	चयन (np->port) अणु
	हाल 0:
		val |= ENET_SERDES_PLL_HRATE0;
		अवरोध;
	हाल 1:
		val |= ENET_SERDES_PLL_HRATE1;
		अवरोध;
	हाल 2:
		val |= ENET_SERDES_PLL_HRATE2;
		अवरोध;
	हाल 3:
		val |= ENET_SERDES_PLL_HRATE3;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	nw64(ENET_SERDES_1_PLL_CFG, val);

	वापस 0;
पूर्ण

अटल पूर्णांक serdes_init_1g_serdes(काष्ठा niu *np)
अणु
	काष्ठा niu_link_config *lp = &np->link_config;
	अचिन्हित दीर्घ ctrl_reg, test_cfg_reg, pll_cfg, i;
	u64 ctrl_val, test_cfg_val, sig, mask, val;
	पूर्णांक err;
	u64 reset_val, val_rd;

	val = ENET_SERDES_PLL_HRATE0 | ENET_SERDES_PLL_HRATE1 |
		ENET_SERDES_PLL_HRATE2 | ENET_SERDES_PLL_HRATE3 |
		ENET_SERDES_PLL_FBDIV0;
	चयन (np->port) अणु
	हाल 0:
		reset_val =  ENET_SERDES_RESET_0;
		ctrl_reg = ENET_SERDES_0_CTRL_CFG;
		test_cfg_reg = ENET_SERDES_0_TEST_CFG;
		pll_cfg = ENET_SERDES_0_PLL_CFG;
		अवरोध;
	हाल 1:
		reset_val =  ENET_SERDES_RESET_1;
		ctrl_reg = ENET_SERDES_1_CTRL_CFG;
		test_cfg_reg = ENET_SERDES_1_TEST_CFG;
		pll_cfg = ENET_SERDES_1_PLL_CFG;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण
	ctrl_val = (ENET_SERDES_CTRL_SDET_0 |
		    ENET_SERDES_CTRL_SDET_1 |
		    ENET_SERDES_CTRL_SDET_2 |
		    ENET_SERDES_CTRL_SDET_3 |
		    (0x5 << ENET_SERDES_CTRL_EMPH_0_SHIFT) |
		    (0x5 << ENET_SERDES_CTRL_EMPH_1_SHIFT) |
		    (0x5 << ENET_SERDES_CTRL_EMPH_2_SHIFT) |
		    (0x5 << ENET_SERDES_CTRL_EMPH_3_SHIFT) |
		    (0x1 << ENET_SERDES_CTRL_LADJ_0_SHIFT) |
		    (0x1 << ENET_SERDES_CTRL_LADJ_1_SHIFT) |
		    (0x1 << ENET_SERDES_CTRL_LADJ_2_SHIFT) |
		    (0x1 << ENET_SERDES_CTRL_LADJ_3_SHIFT));
	test_cfg_val = 0;

	अगर (lp->loopback_mode == LOOPBACK_PHY) अणु
		test_cfg_val |= ((ENET_TEST_MD_PAD_LOOPBACK <<
				  ENET_SERDES_TEST_MD_0_SHIFT) |
				 (ENET_TEST_MD_PAD_LOOPBACK <<
				  ENET_SERDES_TEST_MD_1_SHIFT) |
				 (ENET_TEST_MD_PAD_LOOPBACK <<
				  ENET_SERDES_TEST_MD_2_SHIFT) |
				 (ENET_TEST_MD_PAD_LOOPBACK <<
				  ENET_SERDES_TEST_MD_3_SHIFT));
	पूर्ण

	nw64(ENET_SERDES_RESET, reset_val);
	mdelay(20);
	val_rd = nr64(ENET_SERDES_RESET);
	val_rd &= ~reset_val;
	nw64(pll_cfg, val);
	nw64(ctrl_reg, ctrl_val);
	nw64(test_cfg_reg, test_cfg_val);
	nw64(ENET_SERDES_RESET, val_rd);
	mdelay(2000);

	/* Initialize all 4 lanes of the SERDES.  */
	क्रम (i = 0; i < 4; i++) अणु
		u32 rxtx_ctrl, glue0;

		err = esr_पढ़ो_rxtx_ctrl(np, i, &rxtx_ctrl);
		अगर (err)
			वापस err;
		err = esr_पढ़ो_glue0(np, i, &glue0);
		अगर (err)
			वापस err;

		rxtx_ctrl &= ~(ESR_RXTX_CTRL_VMUXLO);
		rxtx_ctrl |= (ESR_RXTX_CTRL_ENSTRETCH |
			      (2 << ESR_RXTX_CTRL_VMUXLO_SHIFT));

		glue0 &= ~(ESR_GLUE_CTRL0_SRATE |
			   ESR_GLUE_CTRL0_THCNT |
			   ESR_GLUE_CTRL0_BLTIME);
		glue0 |= (ESR_GLUE_CTRL0_RXLOSENAB |
			  (0xf << ESR_GLUE_CTRL0_SRATE_SHIFT) |
			  (0xff << ESR_GLUE_CTRL0_THCNT_SHIFT) |
			  (BLTIME_300_CYCLES <<
			   ESR_GLUE_CTRL0_BLTIME_SHIFT));

		err = esr_ग_लिखो_rxtx_ctrl(np, i, rxtx_ctrl);
		अगर (err)
			वापस err;
		err = esr_ग_लिखो_glue0(np, i, glue0);
		अगर (err)
			वापस err;
	पूर्ण


	sig = nr64(ESR_INT_SIGNALS);
	चयन (np->port) अणु
	हाल 0:
		val = (ESR_INT_SRDY0_P0 | ESR_INT_DET0_P0);
		mask = val;
		अवरोध;

	हाल 1:
		val = (ESR_INT_SRDY0_P1 | ESR_INT_DET0_P1);
		mask = val;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर ((sig & mask) != val) अणु
		netdev_err(np->dev, "Port %u signal bits [%08x] are not [%08x]\n",
			   np->port, (पूर्णांक)(sig & mask), (पूर्णांक)val);
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक link_status_1g_serdes(काष्ठा niu *np, पूर्णांक *link_up_p)
अणु
	काष्ठा niu_link_config *lp = &np->link_config;
	पूर्णांक link_up;
	u64 val;
	u16 current_speed;
	अचिन्हित दीर्घ flags;
	u8 current_duplex;

	link_up = 0;
	current_speed = SPEED_INVALID;
	current_duplex = DUPLEX_INVALID;

	spin_lock_irqsave(&np->lock, flags);

	val = nr64_pcs(PCS_MII_STAT);

	अगर (val & PCS_MII_STAT_LINK_STATUS) अणु
		link_up = 1;
		current_speed = SPEED_1000;
		current_duplex = DUPLEX_FULL;
	पूर्ण

	lp->active_speed = current_speed;
	lp->active_duplex = current_duplex;
	spin_unlock_irqrestore(&np->lock, flags);

	*link_up_p = link_up;
	वापस 0;
पूर्ण

अटल पूर्णांक link_status_10g_serdes(काष्ठा niu *np, पूर्णांक *link_up_p)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा niu_link_config *lp = &np->link_config;
	पूर्णांक link_up = 0;
	पूर्णांक link_ok = 1;
	u64 val, val2;
	u16 current_speed;
	u8 current_duplex;

	अगर (!(np->flags & NIU_FLAGS_10G))
		वापस link_status_1g_serdes(np, link_up_p);

	current_speed = SPEED_INVALID;
	current_duplex = DUPLEX_INVALID;
	spin_lock_irqsave(&np->lock, flags);

	val = nr64_xpcs(XPCS_STATUS(0));
	val2 = nr64_mac(XMAC_INTER2);
	अगर (val2 & 0x01000000)
		link_ok = 0;

	अगर ((val & 0x1000ULL) && link_ok) अणु
		link_up = 1;
		current_speed = SPEED_10000;
		current_duplex = DUPLEX_FULL;
	पूर्ण
	lp->active_speed = current_speed;
	lp->active_duplex = current_duplex;
	spin_unlock_irqrestore(&np->lock, flags);
	*link_up_p = link_up;
	वापस 0;
पूर्ण

अटल पूर्णांक link_status_mii(काष्ठा niu *np, पूर्णांक *link_up_p)
अणु
	काष्ठा niu_link_config *lp = &np->link_config;
	पूर्णांक err;
	पूर्णांक bmsr, advert, ctrl1000, stat1000, lpa, bmcr, estatus;
	पूर्णांक supported, advertising, active_speed, active_duplex;

	err = mii_पढ़ो(np, np->phy_addr, MII_BMCR);
	अगर (unlikely(err < 0))
		वापस err;
	bmcr = err;

	err = mii_पढ़ो(np, np->phy_addr, MII_BMSR);
	अगर (unlikely(err < 0))
		वापस err;
	bmsr = err;

	err = mii_पढ़ो(np, np->phy_addr, MII_ADVERTISE);
	अगर (unlikely(err < 0))
		वापस err;
	advert = err;

	err = mii_पढ़ो(np, np->phy_addr, MII_LPA);
	अगर (unlikely(err < 0))
		वापस err;
	lpa = err;

	अगर (likely(bmsr & BMSR_ESTATEN)) अणु
		err = mii_पढ़ो(np, np->phy_addr, MII_ESTATUS);
		अगर (unlikely(err < 0))
			वापस err;
		estatus = err;

		err = mii_पढ़ो(np, np->phy_addr, MII_CTRL1000);
		अगर (unlikely(err < 0))
			वापस err;
		ctrl1000 = err;

		err = mii_पढ़ो(np, np->phy_addr, MII_STAT1000);
		अगर (unlikely(err < 0))
			वापस err;
		stat1000 = err;
	पूर्ण अन्यथा
		estatus = ctrl1000 = stat1000 = 0;

	supported = 0;
	अगर (bmsr & BMSR_ANEGCAPABLE)
		supported |= SUPPORTED_Autoneg;
	अगर (bmsr & BMSR_10HALF)
		supported |= SUPPORTED_10baseT_Half;
	अगर (bmsr & BMSR_10FULL)
		supported |= SUPPORTED_10baseT_Full;
	अगर (bmsr & BMSR_100HALF)
		supported |= SUPPORTED_100baseT_Half;
	अगर (bmsr & BMSR_100FULL)
		supported |= SUPPORTED_100baseT_Full;
	अगर (estatus & ESTATUS_1000_THALF)
		supported |= SUPPORTED_1000baseT_Half;
	अगर (estatus & ESTATUS_1000_TFULL)
		supported |= SUPPORTED_1000baseT_Full;
	lp->supported = supported;

	advertising = mii_adv_to_ethtool_adv_t(advert);
	advertising |= mii_ctrl1000_to_ethtool_adv_t(ctrl1000);

	अगर (bmcr & BMCR_ANENABLE) अणु
		पूर्णांक neg, neg1000;

		lp->active_स्वतःneg = 1;
		advertising |= ADVERTISED_Autoneg;

		neg = advert & lpa;
		neg1000 = (ctrl1000 << 2) & stat1000;

		अगर (neg1000 & (LPA_1000FULL | LPA_1000HALF))
			active_speed = SPEED_1000;
		अन्यथा अगर (neg & LPA_100)
			active_speed = SPEED_100;
		अन्यथा अगर (neg & (LPA_10HALF | LPA_10FULL))
			active_speed = SPEED_10;
		अन्यथा
			active_speed = SPEED_INVALID;

		अगर ((neg1000 & LPA_1000FULL) || (neg & LPA_DUPLEX))
			active_duplex = DUPLEX_FULL;
		अन्यथा अगर (active_speed != SPEED_INVALID)
			active_duplex = DUPLEX_HALF;
		अन्यथा
			active_duplex = DUPLEX_INVALID;
	पूर्ण अन्यथा अणु
		lp->active_स्वतःneg = 0;

		अगर ((bmcr & BMCR_SPEED1000) && !(bmcr & BMCR_SPEED100))
			active_speed = SPEED_1000;
		अन्यथा अगर (bmcr & BMCR_SPEED100)
			active_speed = SPEED_100;
		अन्यथा
			active_speed = SPEED_10;

		अगर (bmcr & BMCR_FULLDPLX)
			active_duplex = DUPLEX_FULL;
		अन्यथा
			active_duplex = DUPLEX_HALF;
	पूर्ण

	lp->active_advertising = advertising;
	lp->active_speed = active_speed;
	lp->active_duplex = active_duplex;
	*link_up_p = !!(bmsr & BMSR_LSTATUS);

	वापस 0;
पूर्ण

अटल पूर्णांक link_status_1g_rgmii(काष्ठा niu *np, पूर्णांक *link_up_p)
अणु
	काष्ठा niu_link_config *lp = &np->link_config;
	u16 current_speed, bmsr;
	अचिन्हित दीर्घ flags;
	u8 current_duplex;
	पूर्णांक err, link_up;

	link_up = 0;
	current_speed = SPEED_INVALID;
	current_duplex = DUPLEX_INVALID;

	spin_lock_irqsave(&np->lock, flags);

	err = mii_पढ़ो(np, np->phy_addr, MII_BMSR);
	अगर (err < 0)
		जाओ out;

	bmsr = err;
	अगर (bmsr & BMSR_LSTATUS) अणु
		link_up = 1;
		current_speed = SPEED_1000;
		current_duplex = DUPLEX_FULL;
	पूर्ण
	lp->active_speed = current_speed;
	lp->active_duplex = current_duplex;
	err = 0;

out:
	spin_unlock_irqrestore(&np->lock, flags);

	*link_up_p = link_up;
	वापस err;
पूर्ण

अटल पूर्णांक link_status_1g(काष्ठा niu *np, पूर्णांक *link_up_p)
अणु
	काष्ठा niu_link_config *lp = &np->link_config;
	अचिन्हित दीर्घ flags;
	पूर्णांक err;

	spin_lock_irqsave(&np->lock, flags);

	err = link_status_mii(np, link_up_p);
	lp->supported |= SUPPORTED_TP;
	lp->active_advertising |= ADVERTISED_TP;

	spin_unlock_irqrestore(&np->lock, flags);
	वापस err;
पूर्ण

अटल पूर्णांक bcm8704_reset(काष्ठा niu *np)
अणु
	पूर्णांक err, limit;

	err = mdio_पढ़ो(np, np->phy_addr,
			BCM8704_PHYXS_DEV_ADDR, MII_BMCR);
	अगर (err < 0 || err == 0xffff)
		वापस err;
	err |= BMCR_RESET;
	err = mdio_ग_लिखो(np, np->phy_addr, BCM8704_PHYXS_DEV_ADDR,
			 MII_BMCR, err);
	अगर (err)
		वापस err;

	limit = 1000;
	जबतक (--limit >= 0) अणु
		err = mdio_पढ़ो(np, np->phy_addr,
				BCM8704_PHYXS_DEV_ADDR, MII_BMCR);
		अगर (err < 0)
			वापस err;
		अगर (!(err & BMCR_RESET))
			अवरोध;
	पूर्ण
	अगर (limit < 0) अणु
		netdev_err(np->dev, "Port %u PHY will not reset (bmcr=%04x)\n",
			   np->port, (err & 0xffff));
		वापस -ENODEV;
	पूर्ण
	वापस 0;
पूर्ण

/* When written, certain PHY रेजिस्टरs need to be पढ़ो back twice
 * in order क्रम the bits to settle properly.
 */
अटल पूर्णांक bcm8704_user_dev3_पढ़ोback(काष्ठा niu *np, पूर्णांक reg)
अणु
	पूर्णांक err = mdio_पढ़ो(np, np->phy_addr, BCM8704_USER_DEV3_ADDR, reg);
	अगर (err < 0)
		वापस err;
	err = mdio_पढ़ो(np, np->phy_addr, BCM8704_USER_DEV3_ADDR, reg);
	अगर (err < 0)
		वापस err;
	वापस 0;
पूर्ण

अटल पूर्णांक bcm8706_init_user_dev3(काष्ठा niu *np)
अणु
	पूर्णांक err;


	err = mdio_पढ़ो(np, np->phy_addr, BCM8704_USER_DEV3_ADDR,
			BCM8704_USER_OPT_DIGITAL_CTRL);
	अगर (err < 0)
		वापस err;
	err &= ~USER_ODIG_CTRL_GPIOS;
	err |= (0x3 << USER_ODIG_CTRL_GPIOS_SHIFT);
	err |=  USER_ODIG_CTRL_RESV2;
	err = mdio_ग_लिखो(np, np->phy_addr, BCM8704_USER_DEV3_ADDR,
			 BCM8704_USER_OPT_DIGITAL_CTRL, err);
	अगर (err)
		वापस err;

	mdelay(1000);

	वापस 0;
पूर्ण

अटल पूर्णांक bcm8704_init_user_dev3(काष्ठा niu *np)
अणु
	पूर्णांक err;

	err = mdio_ग_लिखो(np, np->phy_addr,
			 BCM8704_USER_DEV3_ADDR, BCM8704_USER_CONTROL,
			 (USER_CONTROL_OPTXRST_LVL |
			  USER_CONTROL_OPBIASFLT_LVL |
			  USER_CONTROL_OBTMPFLT_LVL |
			  USER_CONTROL_OPPRFLT_LVL |
			  USER_CONTROL_OPTXFLT_LVL |
			  USER_CONTROL_OPRXLOS_LVL |
			  USER_CONTROL_OPRXFLT_LVL |
			  USER_CONTROL_OPTXON_LVL |
			  (0x3f << USER_CONTROL_RES1_SHIFT)));
	अगर (err)
		वापस err;

	err = mdio_ग_लिखो(np, np->phy_addr,
			 BCM8704_USER_DEV3_ADDR, BCM8704_USER_PMD_TX_CONTROL,
			 (USER_PMD_TX_CTL_XFP_CLKEN |
			  (1 << USER_PMD_TX_CTL_TX_DAC_TXD_SH) |
			  (2 << USER_PMD_TX_CTL_TX_DAC_TXCK_SH) |
			  USER_PMD_TX_CTL_TSCK_LPWREN));
	अगर (err)
		वापस err;

	err = bcm8704_user_dev3_पढ़ोback(np, BCM8704_USER_CONTROL);
	अगर (err)
		वापस err;
	err = bcm8704_user_dev3_पढ़ोback(np, BCM8704_USER_PMD_TX_CONTROL);
	अगर (err)
		वापस err;

	err = mdio_पढ़ो(np, np->phy_addr, BCM8704_USER_DEV3_ADDR,
			BCM8704_USER_OPT_DIGITAL_CTRL);
	अगर (err < 0)
		वापस err;
	err &= ~USER_ODIG_CTRL_GPIOS;
	err |= (0x3 << USER_ODIG_CTRL_GPIOS_SHIFT);
	err = mdio_ग_लिखो(np, np->phy_addr, BCM8704_USER_DEV3_ADDR,
			 BCM8704_USER_OPT_DIGITAL_CTRL, err);
	अगर (err)
		वापस err;

	mdelay(1000);

	वापस 0;
पूर्ण

अटल पूर्णांक mrvl88x2011_act_led(काष्ठा niu *np, पूर्णांक val)
अणु
	पूर्णांक	err;

	err  = mdio_पढ़ो(np, np->phy_addr, MRVL88X2011_USER_DEV2_ADDR,
		MRVL88X2011_LED_8_TO_11_CTL);
	अगर (err < 0)
		वापस err;

	err &= ~MRVL88X2011_LED(MRVL88X2011_LED_ACT,MRVL88X2011_LED_CTL_MASK);
	err |=  MRVL88X2011_LED(MRVL88X2011_LED_ACT,val);

	वापस mdio_ग_लिखो(np, np->phy_addr, MRVL88X2011_USER_DEV2_ADDR,
			  MRVL88X2011_LED_8_TO_11_CTL, err);
पूर्ण

अटल पूर्णांक mrvl88x2011_led_blink_rate(काष्ठा niu *np, पूर्णांक rate)
अणु
	पूर्णांक	err;

	err = mdio_पढ़ो(np, np->phy_addr, MRVL88X2011_USER_DEV2_ADDR,
			MRVL88X2011_LED_BLINK_CTL);
	अगर (err >= 0) अणु
		err &= ~MRVL88X2011_LED_BLKRATE_MASK;
		err |= (rate << 4);

		err = mdio_ग_लिखो(np, np->phy_addr, MRVL88X2011_USER_DEV2_ADDR,
				 MRVL88X2011_LED_BLINK_CTL, err);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक xcvr_init_10g_mrvl88x2011(काष्ठा niu *np)
अणु
	पूर्णांक	err;

	/* Set LED functions */
	err = mrvl88x2011_led_blink_rate(np, MRVL88X2011_LED_BLKRATE_134MS);
	अगर (err)
		वापस err;

	/* led activity */
	err = mrvl88x2011_act_led(np, MRVL88X2011_LED_CTL_OFF);
	अगर (err)
		वापस err;

	err = mdio_पढ़ो(np, np->phy_addr, MRVL88X2011_USER_DEV3_ADDR,
			MRVL88X2011_GENERAL_CTL);
	अगर (err < 0)
		वापस err;

	err |= MRVL88X2011_ENA_XFPREFCLK;

	err = mdio_ग_लिखो(np, np->phy_addr, MRVL88X2011_USER_DEV3_ADDR,
			 MRVL88X2011_GENERAL_CTL, err);
	अगर (err < 0)
		वापस err;

	err = mdio_पढ़ो(np, np->phy_addr, MRVL88X2011_USER_DEV1_ADDR,
			MRVL88X2011_PMA_PMD_CTL_1);
	अगर (err < 0)
		वापस err;

	अगर (np->link_config.loopback_mode == LOOPBACK_MAC)
		err |= MRVL88X2011_LOOPBACK;
	अन्यथा
		err &= ~MRVL88X2011_LOOPBACK;

	err = mdio_ग_लिखो(np, np->phy_addr, MRVL88X2011_USER_DEV1_ADDR,
			 MRVL88X2011_PMA_PMD_CTL_1, err);
	अगर (err < 0)
		वापस err;

	/* Enable PMD  */
	वापस mdio_ग_लिखो(np, np->phy_addr, MRVL88X2011_USER_DEV1_ADDR,
			  MRVL88X2011_10G_PMD_TX_DIS, MRVL88X2011_ENA_PMDTX);
पूर्ण


अटल पूर्णांक xcvr_diag_bcm870x(काष्ठा niu *np)
अणु
	u16 analog_stat0, tx_alarm_status;
	पूर्णांक err = 0;

#अगर 1
	err = mdio_पढ़ो(np, np->phy_addr, BCM8704_PMA_PMD_DEV_ADDR,
			MII_STAT1000);
	अगर (err < 0)
		वापस err;
	pr_info("Port %u PMA_PMD(MII_STAT1000) [%04x]\n", np->port, err);

	err = mdio_पढ़ो(np, np->phy_addr, BCM8704_USER_DEV3_ADDR, 0x20);
	अगर (err < 0)
		वापस err;
	pr_info("Port %u USER_DEV3(0x20) [%04x]\n", np->port, err);

	err = mdio_पढ़ो(np, np->phy_addr, BCM8704_PHYXS_DEV_ADDR,
			MII_NWAYTEST);
	अगर (err < 0)
		वापस err;
	pr_info("Port %u PHYXS(MII_NWAYTEST) [%04x]\n", np->port, err);
#पूर्ण_अगर

	/* XXX dig this out it might not be so useful XXX */
	err = mdio_पढ़ो(np, np->phy_addr, BCM8704_USER_DEV3_ADDR,
			BCM8704_USER_ANALOG_STATUS0);
	अगर (err < 0)
		वापस err;
	err = mdio_पढ़ो(np, np->phy_addr, BCM8704_USER_DEV3_ADDR,
			BCM8704_USER_ANALOG_STATUS0);
	अगर (err < 0)
		वापस err;
	analog_stat0 = err;

	err = mdio_पढ़ो(np, np->phy_addr, BCM8704_USER_DEV3_ADDR,
			BCM8704_USER_TX_ALARM_STATUS);
	अगर (err < 0)
		वापस err;
	err = mdio_पढ़ो(np, np->phy_addr, BCM8704_USER_DEV3_ADDR,
			BCM8704_USER_TX_ALARM_STATUS);
	अगर (err < 0)
		वापस err;
	tx_alarm_status = err;

	अगर (analog_stat0 != 0x03fc) अणु
		अगर ((analog_stat0 == 0x43bc) && (tx_alarm_status != 0)) अणु
			pr_info("Port %u cable not connected or bad cable\n",
				np->port);
		पूर्ण अन्यथा अगर (analog_stat0 == 0x639c) अणु
			pr_info("Port %u optical module is bad or missing\n",
				np->port);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक xcvr_10g_set_lb_bcm870x(काष्ठा niu *np)
अणु
	काष्ठा niu_link_config *lp = &np->link_config;
	पूर्णांक err;

	err = mdio_पढ़ो(np, np->phy_addr, BCM8704_PCS_DEV_ADDR,
			MII_BMCR);
	अगर (err < 0)
		वापस err;

	err &= ~BMCR_LOOPBACK;

	अगर (lp->loopback_mode == LOOPBACK_MAC)
		err |= BMCR_LOOPBACK;

	err = mdio_ग_लिखो(np, np->phy_addr, BCM8704_PCS_DEV_ADDR,
			 MII_BMCR, err);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक xcvr_init_10g_bcm8706(काष्ठा niu *np)
अणु
	पूर्णांक err = 0;
	u64 val;

	अगर ((np->flags & NIU_FLAGS_HOTPLUG_PHY) &&
	    (np->flags & NIU_FLAGS_HOTPLUG_PHY_PRESENT) == 0)
			वापस err;

	val = nr64_mac(XMAC_CONFIG);
	val &= ~XMAC_CONFIG_LED_POLARITY;
	val |= XMAC_CONFIG_FORCE_LED_ON;
	nw64_mac(XMAC_CONFIG, val);

	val = nr64(MIF_CONFIG);
	val |= MIF_CONFIG_INसूचीECT_MODE;
	nw64(MIF_CONFIG, val);

	err = bcm8704_reset(np);
	अगर (err)
		वापस err;

	err = xcvr_10g_set_lb_bcm870x(np);
	अगर (err)
		वापस err;

	err = bcm8706_init_user_dev3(np);
	अगर (err)
		वापस err;

	err = xcvr_diag_bcm870x(np);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक xcvr_init_10g_bcm8704(काष्ठा niu *np)
अणु
	पूर्णांक err;

	err = bcm8704_reset(np);
	अगर (err)
		वापस err;

	err = bcm8704_init_user_dev3(np);
	अगर (err)
		वापस err;

	err = xcvr_10g_set_lb_bcm870x(np);
	अगर (err)
		वापस err;

	err =  xcvr_diag_bcm870x(np);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक xcvr_init_10g(काष्ठा niu *np)
अणु
	पूर्णांक phy_id, err;
	u64 val;

	val = nr64_mac(XMAC_CONFIG);
	val &= ~XMAC_CONFIG_LED_POLARITY;
	val |= XMAC_CONFIG_FORCE_LED_ON;
	nw64_mac(XMAC_CONFIG, val);

	/* XXX shared resource, lock parent XXX */
	val = nr64(MIF_CONFIG);
	val |= MIF_CONFIG_INसूचीECT_MODE;
	nw64(MIF_CONFIG, val);

	phy_id = phy_decode(np->parent->port_phy, np->port);
	phy_id = np->parent->phy_probe_info.phy_id[phy_id][np->port];

	/* handle dअगरferent phy types */
	चयन (phy_id & NIU_PHY_ID_MASK) अणु
	हाल NIU_PHY_ID_MRVL88X2011:
		err = xcvr_init_10g_mrvl88x2011(np);
		अवरोध;

	शेष: /* bcom 8704 */
		err = xcvr_init_10g_bcm8704(np);
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक mii_reset(काष्ठा niu *np)
अणु
	पूर्णांक limit, err;

	err = mii_ग_लिखो(np, np->phy_addr, MII_BMCR, BMCR_RESET);
	अगर (err)
		वापस err;

	limit = 1000;
	जबतक (--limit >= 0) अणु
		udelay(500);
		err = mii_पढ़ो(np, np->phy_addr, MII_BMCR);
		अगर (err < 0)
			वापस err;
		अगर (!(err & BMCR_RESET))
			अवरोध;
	पूर्ण
	अगर (limit < 0) अणु
		netdev_err(np->dev, "Port %u MII would not reset, bmcr[%04x]\n",
			   np->port, err);
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक xcvr_init_1g_rgmii(काष्ठा niu *np)
अणु
	पूर्णांक err;
	u64 val;
	u16 bmcr, bmsr, estat;

	val = nr64(MIF_CONFIG);
	val &= ~MIF_CONFIG_INसूचीECT_MODE;
	nw64(MIF_CONFIG, val);

	err = mii_reset(np);
	अगर (err)
		वापस err;

	err = mii_पढ़ो(np, np->phy_addr, MII_BMSR);
	अगर (err < 0)
		वापस err;
	bmsr = err;

	estat = 0;
	अगर (bmsr & BMSR_ESTATEN) अणु
		err = mii_पढ़ो(np, np->phy_addr, MII_ESTATUS);
		अगर (err < 0)
			वापस err;
		estat = err;
	पूर्ण

	bmcr = 0;
	err = mii_ग_लिखो(np, np->phy_addr, MII_BMCR, bmcr);
	अगर (err)
		वापस err;

	अगर (bmsr & BMSR_ESTATEN) अणु
		u16 ctrl1000 = 0;

		अगर (estat & ESTATUS_1000_TFULL)
			ctrl1000 |= ADVERTISE_1000FULL;
		err = mii_ग_लिखो(np, np->phy_addr, MII_CTRL1000, ctrl1000);
		अगर (err)
			वापस err;
	पूर्ण

	bmcr = (BMCR_SPEED1000 | BMCR_FULLDPLX);

	err = mii_ग_लिखो(np, np->phy_addr, MII_BMCR, bmcr);
	अगर (err)
		वापस err;

	err = mii_पढ़ो(np, np->phy_addr, MII_BMCR);
	अगर (err < 0)
		वापस err;
	bmcr = mii_पढ़ो(np, np->phy_addr, MII_BMCR);

	err = mii_पढ़ो(np, np->phy_addr, MII_BMSR);
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक mii_init_common(काष्ठा niu *np)
अणु
	काष्ठा niu_link_config *lp = &np->link_config;
	u16 bmcr, bmsr, adv, estat;
	पूर्णांक err;

	err = mii_reset(np);
	अगर (err)
		वापस err;

	err = mii_पढ़ो(np, np->phy_addr, MII_BMSR);
	अगर (err < 0)
		वापस err;
	bmsr = err;

	estat = 0;
	अगर (bmsr & BMSR_ESTATEN) अणु
		err = mii_पढ़ो(np, np->phy_addr, MII_ESTATUS);
		अगर (err < 0)
			वापस err;
		estat = err;
	पूर्ण

	bmcr = 0;
	err = mii_ग_लिखो(np, np->phy_addr, MII_BMCR, bmcr);
	अगर (err)
		वापस err;

	अगर (lp->loopback_mode == LOOPBACK_MAC) अणु
		bmcr |= BMCR_LOOPBACK;
		अगर (lp->active_speed == SPEED_1000)
			bmcr |= BMCR_SPEED1000;
		अगर (lp->active_duplex == DUPLEX_FULL)
			bmcr |= BMCR_FULLDPLX;
	पूर्ण

	अगर (lp->loopback_mode == LOOPBACK_PHY) अणु
		u16 aux;

		aux = (BCM5464R_AUX_CTL_EXT_LB |
		       BCM5464R_AUX_CTL_WRITE_1);
		err = mii_ग_लिखो(np, np->phy_addr, BCM5464R_AUX_CTL, aux);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (lp->स्वतःneg) अणु
		u16 ctrl1000;

		adv = ADVERTISE_CSMA | ADVERTISE_PAUSE_CAP;
		अगर ((bmsr & BMSR_10HALF) &&
			(lp->advertising & ADVERTISED_10baseT_Half))
			adv |= ADVERTISE_10HALF;
		अगर ((bmsr & BMSR_10FULL) &&
			(lp->advertising & ADVERTISED_10baseT_Full))
			adv |= ADVERTISE_10FULL;
		अगर ((bmsr & BMSR_100HALF) &&
			(lp->advertising & ADVERTISED_100baseT_Half))
			adv |= ADVERTISE_100HALF;
		अगर ((bmsr & BMSR_100FULL) &&
			(lp->advertising & ADVERTISED_100baseT_Full))
			adv |= ADVERTISE_100FULL;
		err = mii_ग_लिखो(np, np->phy_addr, MII_ADVERTISE, adv);
		अगर (err)
			वापस err;

		अगर (likely(bmsr & BMSR_ESTATEN)) अणु
			ctrl1000 = 0;
			अगर ((estat & ESTATUS_1000_THALF) &&
				(lp->advertising & ADVERTISED_1000baseT_Half))
				ctrl1000 |= ADVERTISE_1000HALF;
			अगर ((estat & ESTATUS_1000_TFULL) &&
				(lp->advertising & ADVERTISED_1000baseT_Full))
				ctrl1000 |= ADVERTISE_1000FULL;
			err = mii_ग_लिखो(np, np->phy_addr,
					MII_CTRL1000, ctrl1000);
			अगर (err)
				वापस err;
		पूर्ण

		bmcr |= (BMCR_ANENABLE | BMCR_ANRESTART);
	पूर्ण अन्यथा अणु
		/* !lp->स्वतःneg */
		पूर्णांक fulldpx;

		अगर (lp->duplex == DUPLEX_FULL) अणु
			bmcr |= BMCR_FULLDPLX;
			fulldpx = 1;
		पूर्ण अन्यथा अगर (lp->duplex == DUPLEX_HALF)
			fulldpx = 0;
		अन्यथा
			वापस -EINVAL;

		अगर (lp->speed == SPEED_1000) अणु
			/* अगर X-full requested जबतक not supported, or
			   X-half requested जबतक not supported... */
			अगर ((fulldpx && !(estat & ESTATUS_1000_TFULL)) ||
				(!fulldpx && !(estat & ESTATUS_1000_THALF)))
				वापस -EINVAL;
			bmcr |= BMCR_SPEED1000;
		पूर्ण अन्यथा अगर (lp->speed == SPEED_100) अणु
			अगर ((fulldpx && !(bmsr & BMSR_100FULL)) ||
				(!fulldpx && !(bmsr & BMSR_100HALF)))
				वापस -EINVAL;
			bmcr |= BMCR_SPEED100;
		पूर्ण अन्यथा अगर (lp->speed == SPEED_10) अणु
			अगर ((fulldpx && !(bmsr & BMSR_10FULL)) ||
				(!fulldpx && !(bmsr & BMSR_10HALF)))
				वापस -EINVAL;
		पूर्ण अन्यथा
			वापस -EINVAL;
	पूर्ण

	err = mii_ग_लिखो(np, np->phy_addr, MII_BMCR, bmcr);
	अगर (err)
		वापस err;

#अगर 0
	err = mii_पढ़ो(np, np->phy_addr, MII_BMCR);
	अगर (err < 0)
		वापस err;
	bmcr = err;

	err = mii_पढ़ो(np, np->phy_addr, MII_BMSR);
	अगर (err < 0)
		वापस err;
	bmsr = err;

	pr_info("Port %u after MII init bmcr[%04x] bmsr[%04x]\n",
		np->port, bmcr, bmsr);
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल पूर्णांक xcvr_init_1g(काष्ठा niu *np)
अणु
	u64 val;

	/* XXX shared resource, lock parent XXX */
	val = nr64(MIF_CONFIG);
	val &= ~MIF_CONFIG_INसूचीECT_MODE;
	nw64(MIF_CONFIG, val);

	वापस mii_init_common(np);
पूर्ण

अटल पूर्णांक niu_xcvr_init(काष्ठा niu *np)
अणु
	स्थिर काष्ठा niu_phy_ops *ops = np->phy_ops;
	पूर्णांक err;

	err = 0;
	अगर (ops->xcvr_init)
		err = ops->xcvr_init(np);

	वापस err;
पूर्ण

अटल पूर्णांक niu_serdes_init(काष्ठा niu *np)
अणु
	स्थिर काष्ठा niu_phy_ops *ops = np->phy_ops;
	पूर्णांक err;

	err = 0;
	अगर (ops->serdes_init)
		err = ops->serdes_init(np);

	वापस err;
पूर्ण

अटल व्योम niu_init_xअगर(काष्ठा niu *);
अटल व्योम niu_handle_led(काष्ठा niu *, पूर्णांक status);

अटल पूर्णांक niu_link_status_common(काष्ठा niu *np, पूर्णांक link_up)
अणु
	काष्ठा niu_link_config *lp = &np->link_config;
	काष्ठा net_device *dev = np->dev;
	अचिन्हित दीर्घ flags;

	अगर (!netअगर_carrier_ok(dev) && link_up) अणु
		netअगर_info(np, link, dev, "Link is up at %s, %s duplex\n",
			   lp->active_speed == SPEED_10000 ? "10Gb/sec" :
			   lp->active_speed == SPEED_1000 ? "1Gb/sec" :
			   lp->active_speed == SPEED_100 ? "100Mbit/sec" :
			   "10Mbit/sec",
			   lp->active_duplex == DUPLEX_FULL ? "full" : "half");

		spin_lock_irqsave(&np->lock, flags);
		niu_init_xअगर(np);
		niu_handle_led(np, 1);
		spin_unlock_irqrestore(&np->lock, flags);

		netअगर_carrier_on(dev);
	पूर्ण अन्यथा अगर (netअगर_carrier_ok(dev) && !link_up) अणु
		netअगर_warn(np, link, dev, "Link is down\n");
		spin_lock_irqsave(&np->lock, flags);
		niu_handle_led(np, 0);
		spin_unlock_irqrestore(&np->lock, flags);
		netअगर_carrier_off(dev);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक link_status_10g_mrvl(काष्ठा niu *np, पूर्णांक *link_up_p)
अणु
	पूर्णांक err, link_up, pma_status, pcs_status;

	link_up = 0;

	err = mdio_पढ़ो(np, np->phy_addr, MRVL88X2011_USER_DEV1_ADDR,
			MRVL88X2011_10G_PMD_STATUS_2);
	अगर (err < 0)
		जाओ out;

	/* Check PMA/PMD Register: 1.0001.2 == 1 */
	err = mdio_पढ़ो(np, np->phy_addr, MRVL88X2011_USER_DEV1_ADDR,
			MRVL88X2011_PMA_PMD_STATUS_1);
	अगर (err < 0)
		जाओ out;

	pma_status = ((err & MRVL88X2011_LNK_STATUS_OK) ? 1 : 0);

        /* Check PMC Register : 3.0001.2 == 1: पढ़ो twice */
	err = mdio_पढ़ो(np, np->phy_addr, MRVL88X2011_USER_DEV3_ADDR,
			MRVL88X2011_PMA_PMD_STATUS_1);
	अगर (err < 0)
		जाओ out;

	err = mdio_पढ़ो(np, np->phy_addr, MRVL88X2011_USER_DEV3_ADDR,
			MRVL88X2011_PMA_PMD_STATUS_1);
	अगर (err < 0)
		जाओ out;

	pcs_status = ((err & MRVL88X2011_LNK_STATUS_OK) ? 1 : 0);

        /* Check XGXS Register : 4.0018.[0-3,12] */
	err = mdio_पढ़ो(np, np->phy_addr, MRVL88X2011_USER_DEV4_ADDR,
			MRVL88X2011_10G_XGXS_LANE_STAT);
	अगर (err < 0)
		जाओ out;

	अगर (err == (PHYXS_XGXS_LANE_STAT_ALINGED | PHYXS_XGXS_LANE_STAT_LANE3 |
		    PHYXS_XGXS_LANE_STAT_LANE2 | PHYXS_XGXS_LANE_STAT_LANE1 |
		    PHYXS_XGXS_LANE_STAT_LANE0 | PHYXS_XGXS_LANE_STAT_MAGIC |
		    0x800))
		link_up = (pma_status && pcs_status) ? 1 : 0;

	np->link_config.active_speed = SPEED_10000;
	np->link_config.active_duplex = DUPLEX_FULL;
	err = 0;
out:
	mrvl88x2011_act_led(np, (link_up ?
				 MRVL88X2011_LED_CTL_PCS_ACT :
				 MRVL88X2011_LED_CTL_OFF));

	*link_up_p = link_up;
	वापस err;
पूर्ण

अटल पूर्णांक link_status_10g_bcm8706(काष्ठा niu *np, पूर्णांक *link_up_p)
अणु
	पूर्णांक err, link_up;
	link_up = 0;

	err = mdio_पढ़ो(np, np->phy_addr, BCM8704_PMA_PMD_DEV_ADDR,
			BCM8704_PMD_RCV_SIGDET);
	अगर (err < 0 || err == 0xffff)
		जाओ out;
	अगर (!(err & PMD_RCV_SIGDET_GLOBAL)) अणु
		err = 0;
		जाओ out;
	पूर्ण

	err = mdio_पढ़ो(np, np->phy_addr, BCM8704_PCS_DEV_ADDR,
			BCM8704_PCS_10G_R_STATUS);
	अगर (err < 0)
		जाओ out;

	अगर (!(err & PCS_10G_R_STATUS_BLK_LOCK)) अणु
		err = 0;
		जाओ out;
	पूर्ण

	err = mdio_पढ़ो(np, np->phy_addr, BCM8704_PHYXS_DEV_ADDR,
			BCM8704_PHYXS_XGXS_LANE_STAT);
	अगर (err < 0)
		जाओ out;
	अगर (err != (PHYXS_XGXS_LANE_STAT_ALINGED |
		    PHYXS_XGXS_LANE_STAT_MAGIC |
		    PHYXS_XGXS_LANE_STAT_PATTEST |
		    PHYXS_XGXS_LANE_STAT_LANE3 |
		    PHYXS_XGXS_LANE_STAT_LANE2 |
		    PHYXS_XGXS_LANE_STAT_LANE1 |
		    PHYXS_XGXS_LANE_STAT_LANE0)) अणु
		err = 0;
		np->link_config.active_speed = SPEED_INVALID;
		np->link_config.active_duplex = DUPLEX_INVALID;
		जाओ out;
	पूर्ण

	link_up = 1;
	np->link_config.active_speed = SPEED_10000;
	np->link_config.active_duplex = DUPLEX_FULL;
	err = 0;

out:
	*link_up_p = link_up;
	वापस err;
पूर्ण

अटल पूर्णांक link_status_10g_bcom(काष्ठा niu *np, पूर्णांक *link_up_p)
अणु
	पूर्णांक err, link_up;

	link_up = 0;

	err = mdio_पढ़ो(np, np->phy_addr, BCM8704_PMA_PMD_DEV_ADDR,
			BCM8704_PMD_RCV_SIGDET);
	अगर (err < 0)
		जाओ out;
	अगर (!(err & PMD_RCV_SIGDET_GLOBAL)) अणु
		err = 0;
		जाओ out;
	पूर्ण

	err = mdio_पढ़ो(np, np->phy_addr, BCM8704_PCS_DEV_ADDR,
			BCM8704_PCS_10G_R_STATUS);
	अगर (err < 0)
		जाओ out;
	अगर (!(err & PCS_10G_R_STATUS_BLK_LOCK)) अणु
		err = 0;
		जाओ out;
	पूर्ण

	err = mdio_पढ़ो(np, np->phy_addr, BCM8704_PHYXS_DEV_ADDR,
			BCM8704_PHYXS_XGXS_LANE_STAT);
	अगर (err < 0)
		जाओ out;

	अगर (err != (PHYXS_XGXS_LANE_STAT_ALINGED |
		    PHYXS_XGXS_LANE_STAT_MAGIC |
		    PHYXS_XGXS_LANE_STAT_LANE3 |
		    PHYXS_XGXS_LANE_STAT_LANE2 |
		    PHYXS_XGXS_LANE_STAT_LANE1 |
		    PHYXS_XGXS_LANE_STAT_LANE0)) अणु
		err = 0;
		जाओ out;
	पूर्ण

	link_up = 1;
	np->link_config.active_speed = SPEED_10000;
	np->link_config.active_duplex = DUPLEX_FULL;
	err = 0;

out:
	*link_up_p = link_up;
	वापस err;
पूर्ण

अटल पूर्णांक link_status_10g(काष्ठा niu *np, पूर्णांक *link_up_p)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक err = -EINVAL;

	spin_lock_irqsave(&np->lock, flags);

	अगर (np->link_config.loopback_mode == LOOPBACK_DISABLED) अणु
		पूर्णांक phy_id;

		phy_id = phy_decode(np->parent->port_phy, np->port);
		phy_id = np->parent->phy_probe_info.phy_id[phy_id][np->port];

		/* handle dअगरferent phy types */
		चयन (phy_id & NIU_PHY_ID_MASK) अणु
		हाल NIU_PHY_ID_MRVL88X2011:
			err = link_status_10g_mrvl(np, link_up_p);
			अवरोध;

		शेष: /* bcom 8704 */
			err = link_status_10g_bcom(np, link_up_p);
			अवरोध;
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&np->lock, flags);

	वापस err;
पूर्ण

अटल पूर्णांक niu_10g_phy_present(काष्ठा niu *np)
अणु
	u64 sig, mask, val;

	sig = nr64(ESR_INT_SIGNALS);
	चयन (np->port) अणु
	हाल 0:
		mask = ESR_INT_SIGNALS_P0_BITS;
		val = (ESR_INT_SRDY0_P0 |
		       ESR_INT_DET0_P0 |
		       ESR_INT_XSRDY_P0 |
		       ESR_INT_XDP_P0_CH3 |
		       ESR_INT_XDP_P0_CH2 |
		       ESR_INT_XDP_P0_CH1 |
		       ESR_INT_XDP_P0_CH0);
		अवरोध;

	हाल 1:
		mask = ESR_INT_SIGNALS_P1_BITS;
		val = (ESR_INT_SRDY0_P1 |
		       ESR_INT_DET0_P1 |
		       ESR_INT_XSRDY_P1 |
		       ESR_INT_XDP_P1_CH3 |
		       ESR_INT_XDP_P1_CH2 |
		       ESR_INT_XDP_P1_CH1 |
		       ESR_INT_XDP_P1_CH0);
		अवरोध;

	शेष:
		वापस 0;
	पूर्ण

	अगर ((sig & mask) != val)
		वापस 0;
	वापस 1;
पूर्ण

अटल पूर्णांक link_status_10g_hotplug(काष्ठा niu *np, पूर्णांक *link_up_p)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक err = 0;
	पूर्णांक phy_present;
	पूर्णांक phy_present_prev;

	spin_lock_irqsave(&np->lock, flags);

	अगर (np->link_config.loopback_mode == LOOPBACK_DISABLED) अणु
		phy_present_prev = (np->flags & NIU_FLAGS_HOTPLUG_PHY_PRESENT) ?
			1 : 0;
		phy_present = niu_10g_phy_present(np);
		अगर (phy_present != phy_present_prev) अणु
			/* state change */
			अगर (phy_present) अणु
				/* A NEM was just plugged in */
				np->flags |= NIU_FLAGS_HOTPLUG_PHY_PRESENT;
				अगर (np->phy_ops->xcvr_init)
					err = np->phy_ops->xcvr_init(np);
				अगर (err) अणु
					err = mdio_पढ़ो(np, np->phy_addr,
						BCM8704_PHYXS_DEV_ADDR, MII_BMCR);
					अगर (err == 0xffff) अणु
						/* No mdio, back-to-back XAUI */
						जाओ out;
					पूर्ण
					/* debounce */
					np->flags &= ~NIU_FLAGS_HOTPLUG_PHY_PRESENT;
				पूर्ण
			पूर्ण अन्यथा अणु
				np->flags &= ~NIU_FLAGS_HOTPLUG_PHY_PRESENT;
				*link_up_p = 0;
				netअगर_warn(np, link, np->dev,
					   "Hotplug PHY Removed\n");
			पूर्ण
		पूर्ण
out:
		अगर (np->flags & NIU_FLAGS_HOTPLUG_PHY_PRESENT) अणु
			err = link_status_10g_bcm8706(np, link_up_p);
			अगर (err == 0xffff) अणु
				/* No mdio, back-to-back XAUI: it is C10NEM */
				*link_up_p = 1;
				np->link_config.active_speed = SPEED_10000;
				np->link_config.active_duplex = DUPLEX_FULL;
			पूर्ण
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&np->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक niu_link_status(काष्ठा niu *np, पूर्णांक *link_up_p)
अणु
	स्थिर काष्ठा niu_phy_ops *ops = np->phy_ops;
	पूर्णांक err;

	err = 0;
	अगर (ops->link_status)
		err = ops->link_status(np, link_up_p);

	वापस err;
पूर्ण

अटल व्योम niu_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा niu *np = from_समयr(np, t, समयr);
	अचिन्हित दीर्घ off;
	पूर्णांक err, link_up;

	err = niu_link_status(np, &link_up);
	अगर (!err)
		niu_link_status_common(np, link_up);

	अगर (netअगर_carrier_ok(np->dev))
		off = 5 * HZ;
	अन्यथा
		off = 1 * HZ;
	np->समयr.expires = jअगरfies + off;

	add_समयr(&np->समयr);
पूर्ण

अटल स्थिर काष्ठा niu_phy_ops phy_ops_10g_serdes = अणु
	.serdes_init		= serdes_init_10g_serdes,
	.link_status		= link_status_10g_serdes,
पूर्ण;

अटल स्थिर काष्ठा niu_phy_ops phy_ops_10g_serdes_niu = अणु
	.serdes_init		= serdes_init_niu_10g_serdes,
	.link_status		= link_status_10g_serdes,
पूर्ण;

अटल स्थिर काष्ठा niu_phy_ops phy_ops_1g_serdes_niu = अणु
	.serdes_init		= serdes_init_niu_1g_serdes,
	.link_status		= link_status_1g_serdes,
पूर्ण;

अटल स्थिर काष्ठा niu_phy_ops phy_ops_1g_rgmii = अणु
	.xcvr_init		= xcvr_init_1g_rgmii,
	.link_status		= link_status_1g_rgmii,
पूर्ण;

अटल स्थिर काष्ठा niu_phy_ops phy_ops_10g_fiber_niu = अणु
	.serdes_init		= serdes_init_niu_10g_fiber,
	.xcvr_init		= xcvr_init_10g,
	.link_status		= link_status_10g,
पूर्ण;

अटल स्थिर काष्ठा niu_phy_ops phy_ops_10g_fiber = अणु
	.serdes_init		= serdes_init_10g,
	.xcvr_init		= xcvr_init_10g,
	.link_status		= link_status_10g,
पूर्ण;

अटल स्थिर काष्ठा niu_phy_ops phy_ops_10g_fiber_hotplug = अणु
	.serdes_init		= serdes_init_10g,
	.xcvr_init		= xcvr_init_10g_bcm8706,
	.link_status		= link_status_10g_hotplug,
पूर्ण;

अटल स्थिर काष्ठा niu_phy_ops phy_ops_niu_10g_hotplug = अणु
	.serdes_init		= serdes_init_niu_10g_fiber,
	.xcvr_init		= xcvr_init_10g_bcm8706,
	.link_status		= link_status_10g_hotplug,
पूर्ण;

अटल स्थिर काष्ठा niu_phy_ops phy_ops_10g_copper = अणु
	.serdes_init		= serdes_init_10g,
	.link_status		= link_status_10g, /* XXX */
पूर्ण;

अटल स्थिर काष्ठा niu_phy_ops phy_ops_1g_fiber = अणु
	.serdes_init		= serdes_init_1g,
	.xcvr_init		= xcvr_init_1g,
	.link_status		= link_status_1g,
पूर्ण;

अटल स्थिर काष्ठा niu_phy_ops phy_ops_1g_copper = अणु
	.xcvr_init		= xcvr_init_1g,
	.link_status		= link_status_1g,
पूर्ण;

काष्ठा niu_phy_ढाँचा अणु
	स्थिर काष्ठा niu_phy_ops	*ops;
	u32				phy_addr_base;
पूर्ण;

अटल स्थिर काष्ठा niu_phy_ढाँचा phy_ढाँचा_niu_10g_fiber = अणु
	.ops		= &phy_ops_10g_fiber_niu,
	.phy_addr_base	= 16,
पूर्ण;

अटल स्थिर काष्ठा niu_phy_ढाँचा phy_ढाँचा_niu_10g_serdes = अणु
	.ops		= &phy_ops_10g_serdes_niu,
	.phy_addr_base	= 0,
पूर्ण;

अटल स्थिर काष्ठा niu_phy_ढाँचा phy_ढाँचा_niu_1g_serdes = अणु
	.ops		= &phy_ops_1g_serdes_niu,
	.phy_addr_base	= 0,
पूर्ण;

अटल स्थिर काष्ठा niu_phy_ढाँचा phy_ढाँचा_10g_fiber = अणु
	.ops		= &phy_ops_10g_fiber,
	.phy_addr_base	= 8,
पूर्ण;

अटल स्थिर काष्ठा niu_phy_ढाँचा phy_ढाँचा_10g_fiber_hotplug = अणु
	.ops		= &phy_ops_10g_fiber_hotplug,
	.phy_addr_base	= 8,
पूर्ण;

अटल स्थिर काष्ठा niu_phy_ढाँचा phy_ढाँचा_niu_10g_hotplug = अणु
	.ops		= &phy_ops_niu_10g_hotplug,
	.phy_addr_base	= 8,
पूर्ण;

अटल स्थिर काष्ठा niu_phy_ढाँचा phy_ढाँचा_10g_copper = अणु
	.ops		= &phy_ops_10g_copper,
	.phy_addr_base	= 10,
पूर्ण;

अटल स्थिर काष्ठा niu_phy_ढाँचा phy_ढाँचा_1g_fiber = अणु
	.ops		= &phy_ops_1g_fiber,
	.phy_addr_base	= 0,
पूर्ण;

अटल स्थिर काष्ठा niu_phy_ढाँचा phy_ढाँचा_1g_copper = अणु
	.ops		= &phy_ops_1g_copper,
	.phy_addr_base	= 0,
पूर्ण;

अटल स्थिर काष्ठा niu_phy_ढाँचा phy_ढाँचा_1g_rgmii = अणु
	.ops		= &phy_ops_1g_rgmii,
	.phy_addr_base	= 0,
पूर्ण;

अटल स्थिर काष्ठा niu_phy_ढाँचा phy_ढाँचा_10g_serdes = अणु
	.ops		= &phy_ops_10g_serdes,
	.phy_addr_base	= 0,
पूर्ण;

अटल पूर्णांक niu_atca_port_num[4] = अणु
	0, 0,  11, 10
पूर्ण;

अटल पूर्णांक serdes_init_10g_serdes(काष्ठा niu *np)
अणु
	काष्ठा niu_link_config *lp = &np->link_config;
	अचिन्हित दीर्घ ctrl_reg, test_cfg_reg, pll_cfg, i;
	u64 ctrl_val, test_cfg_val, sig, mask, val;

	चयन (np->port) अणु
	हाल 0:
		ctrl_reg = ENET_SERDES_0_CTRL_CFG;
		test_cfg_reg = ENET_SERDES_0_TEST_CFG;
		pll_cfg = ENET_SERDES_0_PLL_CFG;
		अवरोध;
	हाल 1:
		ctrl_reg = ENET_SERDES_1_CTRL_CFG;
		test_cfg_reg = ENET_SERDES_1_TEST_CFG;
		pll_cfg = ENET_SERDES_1_PLL_CFG;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण
	ctrl_val = (ENET_SERDES_CTRL_SDET_0 |
		    ENET_SERDES_CTRL_SDET_1 |
		    ENET_SERDES_CTRL_SDET_2 |
		    ENET_SERDES_CTRL_SDET_3 |
		    (0x5 << ENET_SERDES_CTRL_EMPH_0_SHIFT) |
		    (0x5 << ENET_SERDES_CTRL_EMPH_1_SHIFT) |
		    (0x5 << ENET_SERDES_CTRL_EMPH_2_SHIFT) |
		    (0x5 << ENET_SERDES_CTRL_EMPH_3_SHIFT) |
		    (0x1 << ENET_SERDES_CTRL_LADJ_0_SHIFT) |
		    (0x1 << ENET_SERDES_CTRL_LADJ_1_SHIFT) |
		    (0x1 << ENET_SERDES_CTRL_LADJ_2_SHIFT) |
		    (0x1 << ENET_SERDES_CTRL_LADJ_3_SHIFT));
	test_cfg_val = 0;

	अगर (lp->loopback_mode == LOOPBACK_PHY) अणु
		test_cfg_val |= ((ENET_TEST_MD_PAD_LOOPBACK <<
				  ENET_SERDES_TEST_MD_0_SHIFT) |
				 (ENET_TEST_MD_PAD_LOOPBACK <<
				  ENET_SERDES_TEST_MD_1_SHIFT) |
				 (ENET_TEST_MD_PAD_LOOPBACK <<
				  ENET_SERDES_TEST_MD_2_SHIFT) |
				 (ENET_TEST_MD_PAD_LOOPBACK <<
				  ENET_SERDES_TEST_MD_3_SHIFT));
	पूर्ण

	esr_reset(np);
	nw64(pll_cfg, ENET_SERDES_PLL_FBDIV2);
	nw64(ctrl_reg, ctrl_val);
	nw64(test_cfg_reg, test_cfg_val);

	/* Initialize all 4 lanes of the SERDES.  */
	क्रम (i = 0; i < 4; i++) अणु
		u32 rxtx_ctrl, glue0;
		पूर्णांक err;

		err = esr_पढ़ो_rxtx_ctrl(np, i, &rxtx_ctrl);
		अगर (err)
			वापस err;
		err = esr_पढ़ो_glue0(np, i, &glue0);
		अगर (err)
			वापस err;

		rxtx_ctrl &= ~(ESR_RXTX_CTRL_VMUXLO);
		rxtx_ctrl |= (ESR_RXTX_CTRL_ENSTRETCH |
			      (2 << ESR_RXTX_CTRL_VMUXLO_SHIFT));

		glue0 &= ~(ESR_GLUE_CTRL0_SRATE |
			   ESR_GLUE_CTRL0_THCNT |
			   ESR_GLUE_CTRL0_BLTIME);
		glue0 |= (ESR_GLUE_CTRL0_RXLOSENAB |
			  (0xf << ESR_GLUE_CTRL0_SRATE_SHIFT) |
			  (0xff << ESR_GLUE_CTRL0_THCNT_SHIFT) |
			  (BLTIME_300_CYCLES <<
			   ESR_GLUE_CTRL0_BLTIME_SHIFT));

		err = esr_ग_लिखो_rxtx_ctrl(np, i, rxtx_ctrl);
		अगर (err)
			वापस err;
		err = esr_ग_लिखो_glue0(np, i, glue0);
		अगर (err)
			वापस err;
	पूर्ण


	sig = nr64(ESR_INT_SIGNALS);
	चयन (np->port) अणु
	हाल 0:
		mask = ESR_INT_SIGNALS_P0_BITS;
		val = (ESR_INT_SRDY0_P0 |
		       ESR_INT_DET0_P0 |
		       ESR_INT_XSRDY_P0 |
		       ESR_INT_XDP_P0_CH3 |
		       ESR_INT_XDP_P0_CH2 |
		       ESR_INT_XDP_P0_CH1 |
		       ESR_INT_XDP_P0_CH0);
		अवरोध;

	हाल 1:
		mask = ESR_INT_SIGNALS_P1_BITS;
		val = (ESR_INT_SRDY0_P1 |
		       ESR_INT_DET0_P1 |
		       ESR_INT_XSRDY_P1 |
		       ESR_INT_XDP_P1_CH3 |
		       ESR_INT_XDP_P1_CH2 |
		       ESR_INT_XDP_P1_CH1 |
		       ESR_INT_XDP_P1_CH0);
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर ((sig & mask) != val) अणु
		पूर्णांक err;
		err = serdes_init_1g_serdes(np);
		अगर (!err) अणु
			np->flags &= ~NIU_FLAGS_10G;
			np->mac_xcvr = MAC_XCVR_PCS;
		पूर्ण  अन्यथा अणु
			netdev_err(np->dev, "Port %u 10G/1G SERDES Link Failed\n",
				   np->port);
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक niu_determine_phy_disposition(काष्ठा niu *np)
अणु
	काष्ठा niu_parent *parent = np->parent;
	u8 plat_type = parent->plat_type;
	स्थिर काष्ठा niu_phy_ढाँचा *tp;
	u32 phy_addr_off = 0;

	अगर (plat_type == PLAT_TYPE_NIU) अणु
		चयन (np->flags &
			(NIU_FLAGS_10G |
			 NIU_FLAGS_FIBER |
			 NIU_FLAGS_XCVR_SERDES)) अणु
		हाल NIU_FLAGS_10G | NIU_FLAGS_XCVR_SERDES:
			/* 10G Serdes */
			tp = &phy_ढाँचा_niu_10g_serdes;
			अवरोध;
		हाल NIU_FLAGS_XCVR_SERDES:
			/* 1G Serdes */
			tp = &phy_ढाँचा_niu_1g_serdes;
			अवरोध;
		हाल NIU_FLAGS_10G | NIU_FLAGS_FIBER:
			/* 10G Fiber */
		शेष:
			अगर (np->flags & NIU_FLAGS_HOTPLUG_PHY) अणु
				tp = &phy_ढाँचा_niu_10g_hotplug;
				अगर (np->port == 0)
					phy_addr_off = 8;
				अगर (np->port == 1)
					phy_addr_off = 12;
			पूर्ण अन्यथा अणु
				tp = &phy_ढाँचा_niu_10g_fiber;
				phy_addr_off += np->port;
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (np->flags &
			(NIU_FLAGS_10G |
			 NIU_FLAGS_FIBER |
			 NIU_FLAGS_XCVR_SERDES)) अणु
		हाल 0:
			/* 1G copper */
			tp = &phy_ढाँचा_1g_copper;
			अगर (plat_type == PLAT_TYPE_VF_P0)
				phy_addr_off = 10;
			अन्यथा अगर (plat_type == PLAT_TYPE_VF_P1)
				phy_addr_off = 26;

			phy_addr_off += (np->port ^ 0x3);
			अवरोध;

		हाल NIU_FLAGS_10G:
			/* 10G copper */
			tp = &phy_ढाँचा_10g_copper;
			अवरोध;

		हाल NIU_FLAGS_FIBER:
			/* 1G fiber */
			tp = &phy_ढाँचा_1g_fiber;
			अवरोध;

		हाल NIU_FLAGS_10G | NIU_FLAGS_FIBER:
			/* 10G fiber */
			tp = &phy_ढाँचा_10g_fiber;
			अगर (plat_type == PLAT_TYPE_VF_P0 ||
			    plat_type == PLAT_TYPE_VF_P1)
				phy_addr_off = 8;
			phy_addr_off += np->port;
			अगर (np->flags & NIU_FLAGS_HOTPLUG_PHY) अणु
				tp = &phy_ढाँचा_10g_fiber_hotplug;
				अगर (np->port == 0)
					phy_addr_off = 8;
				अगर (np->port == 1)
					phy_addr_off = 12;
			पूर्ण
			अवरोध;

		हाल NIU_FLAGS_10G | NIU_FLAGS_XCVR_SERDES:
		हाल NIU_FLAGS_XCVR_SERDES | NIU_FLAGS_FIBER:
		हाल NIU_FLAGS_XCVR_SERDES:
			चयन(np->port) अणु
			हाल 0:
			हाल 1:
				tp = &phy_ढाँचा_10g_serdes;
				अवरोध;
			हाल 2:
			हाल 3:
				tp = &phy_ढाँचा_1g_rgmii;
				अवरोध;
			शेष:
				वापस -EINVAL;
			पूर्ण
			phy_addr_off = niu_atca_port_num[np->port];
			अवरोध;

		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	np->phy_ops = tp->ops;
	np->phy_addr = tp->phy_addr_base + phy_addr_off;

	वापस 0;
पूर्ण

अटल पूर्णांक niu_init_link(काष्ठा niu *np)
अणु
	काष्ठा niu_parent *parent = np->parent;
	पूर्णांक err, ignore;

	अगर (parent->plat_type == PLAT_TYPE_NIU) अणु
		err = niu_xcvr_init(np);
		अगर (err)
			वापस err;
		msleep(200);
	पूर्ण
	err = niu_serdes_init(np);
	अगर (err && !(np->flags & NIU_FLAGS_HOTPLUG_PHY))
		वापस err;
	msleep(200);
	err = niu_xcvr_init(np);
	अगर (!err || (np->flags & NIU_FLAGS_HOTPLUG_PHY))
		niu_link_status(np, &ignore);
	वापस 0;
पूर्ण

अटल व्योम niu_set_primary_mac(काष्ठा niu *np, अचिन्हित अक्षर *addr)
अणु
	u16 reg0 = addr[4] << 8 | addr[5];
	u16 reg1 = addr[2] << 8 | addr[3];
	u16 reg2 = addr[0] << 8 | addr[1];

	अगर (np->flags & NIU_FLAGS_XMAC) अणु
		nw64_mac(XMAC_ADDR0, reg0);
		nw64_mac(XMAC_ADDR1, reg1);
		nw64_mac(XMAC_ADDR2, reg2);
	पूर्ण अन्यथा अणु
		nw64_mac(BMAC_ADDR0, reg0);
		nw64_mac(BMAC_ADDR1, reg1);
		nw64_mac(BMAC_ADDR2, reg2);
	पूर्ण
पूर्ण

अटल पूर्णांक niu_num_alt_addr(काष्ठा niu *np)
अणु
	अगर (np->flags & NIU_FLAGS_XMAC)
		वापस XMAC_NUM_ALT_ADDR;
	अन्यथा
		वापस BMAC_NUM_ALT_ADDR;
पूर्ण

अटल पूर्णांक niu_set_alt_mac(काष्ठा niu *np, पूर्णांक index, अचिन्हित अक्षर *addr)
अणु
	u16 reg0 = addr[4] << 8 | addr[5];
	u16 reg1 = addr[2] << 8 | addr[3];
	u16 reg2 = addr[0] << 8 | addr[1];

	अगर (index >= niu_num_alt_addr(np))
		वापस -EINVAL;

	अगर (np->flags & NIU_FLAGS_XMAC) अणु
		nw64_mac(XMAC_ALT_ADDR0(index), reg0);
		nw64_mac(XMAC_ALT_ADDR1(index), reg1);
		nw64_mac(XMAC_ALT_ADDR2(index), reg2);
	पूर्ण अन्यथा अणु
		nw64_mac(BMAC_ALT_ADDR0(index), reg0);
		nw64_mac(BMAC_ALT_ADDR1(index), reg1);
		nw64_mac(BMAC_ALT_ADDR2(index), reg2);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक niu_enable_alt_mac(काष्ठा niu *np, पूर्णांक index, पूर्णांक on)
अणु
	अचिन्हित दीर्घ reg;
	u64 val, mask;

	अगर (index >= niu_num_alt_addr(np))
		वापस -EINVAL;

	अगर (np->flags & NIU_FLAGS_XMAC) अणु
		reg = XMAC_ADDR_CMPEN;
		mask = 1 << index;
	पूर्ण अन्यथा अणु
		reg = BMAC_ADDR_CMPEN;
		mask = 1 << (index + 1);
	पूर्ण

	val = nr64_mac(reg);
	अगर (on)
		val |= mask;
	अन्यथा
		val &= ~mask;
	nw64_mac(reg, val);

	वापस 0;
पूर्ण

अटल व्योम __set_rdc_table_num_hw(काष्ठा niu *np, अचिन्हित दीर्घ reg,
				   पूर्णांक num, पूर्णांक mac_pref)
अणु
	u64 val = nr64_mac(reg);
	val &= ~(HOST_INFO_MACRDCTBLN | HOST_INFO_MPR);
	val |= num;
	अगर (mac_pref)
		val |= HOST_INFO_MPR;
	nw64_mac(reg, val);
पूर्ण

अटल पूर्णांक __set_rdc_table_num(काष्ठा niu *np,
			       पूर्णांक xmac_index, पूर्णांक bmac_index,
			       पूर्णांक rdc_table_num, पूर्णांक mac_pref)
अणु
	अचिन्हित दीर्घ reg;

	अगर (rdc_table_num & ~HOST_INFO_MACRDCTBLN)
		वापस -EINVAL;
	अगर (np->flags & NIU_FLAGS_XMAC)
		reg = XMAC_HOST_INFO(xmac_index);
	अन्यथा
		reg = BMAC_HOST_INFO(bmac_index);
	__set_rdc_table_num_hw(np, reg, rdc_table_num, mac_pref);
	वापस 0;
पूर्ण

अटल पूर्णांक niu_set_primary_mac_rdc_table(काष्ठा niu *np, पूर्णांक table_num,
					 पूर्णांक mac_pref)
अणु
	वापस __set_rdc_table_num(np, 17, 0, table_num, mac_pref);
पूर्ण

अटल पूर्णांक niu_set_multicast_mac_rdc_table(काष्ठा niu *np, पूर्णांक table_num,
					   पूर्णांक mac_pref)
अणु
	वापस __set_rdc_table_num(np, 16, 8, table_num, mac_pref);
पूर्ण

अटल पूर्णांक niu_set_alt_mac_rdc_table(काष्ठा niu *np, पूर्णांक idx,
				     पूर्णांक table_num, पूर्णांक mac_pref)
अणु
	अगर (idx >= niu_num_alt_addr(np))
		वापस -EINVAL;
	वापस __set_rdc_table_num(np, idx, idx + 1, table_num, mac_pref);
पूर्ण

अटल u64 vlan_entry_set_parity(u64 reg_val)
अणु
	u64 port01_mask;
	u64 port23_mask;

	port01_mask = 0x00ff;
	port23_mask = 0xff00;

	अगर (hweight64(reg_val & port01_mask) & 1)
		reg_val |= ENET_VLAN_TBL_PARITY0;
	अन्यथा
		reg_val &= ~ENET_VLAN_TBL_PARITY0;

	अगर (hweight64(reg_val & port23_mask) & 1)
		reg_val |= ENET_VLAN_TBL_PARITY1;
	अन्यथा
		reg_val &= ~ENET_VLAN_TBL_PARITY1;

	वापस reg_val;
पूर्ण

अटल व्योम vlan_tbl_ग_लिखो(काष्ठा niu *np, अचिन्हित दीर्घ index,
			   पूर्णांक port, पूर्णांक vpr, पूर्णांक rdc_table)
अणु
	u64 reg_val = nr64(ENET_VLAN_TBL(index));

	reg_val &= ~((ENET_VLAN_TBL_VPR |
		      ENET_VLAN_TBL_VLANRDCTBLN) <<
		     ENET_VLAN_TBL_SHIFT(port));
	अगर (vpr)
		reg_val |= (ENET_VLAN_TBL_VPR <<
			    ENET_VLAN_TBL_SHIFT(port));
	reg_val |= (rdc_table << ENET_VLAN_TBL_SHIFT(port));

	reg_val = vlan_entry_set_parity(reg_val);

	nw64(ENET_VLAN_TBL(index), reg_val);
पूर्ण

अटल व्योम vlan_tbl_clear(काष्ठा niu *np)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ENET_VLAN_TBL_NUM_ENTRIES; i++)
		nw64(ENET_VLAN_TBL(i), 0);
पूर्ण

अटल पूर्णांक tcam_रुको_bit(काष्ठा niu *np, u64 bit)
अणु
	पूर्णांक limit = 1000;

	जबतक (--limit > 0) अणु
		अगर (nr64(TCAM_CTL) & bit)
			अवरोध;
		udelay(1);
	पूर्ण
	अगर (limit <= 0)
		वापस -ENODEV;

	वापस 0;
पूर्ण

अटल पूर्णांक tcam_flush(काष्ठा niu *np, पूर्णांक index)
अणु
	nw64(TCAM_KEY_0, 0x00);
	nw64(TCAM_KEY_MASK_0, 0xff);
	nw64(TCAM_CTL, (TCAM_CTL_RWC_TCAM_WRITE | index));

	वापस tcam_रुको_bit(np, TCAM_CTL_STAT);
पूर्ण

#अगर 0
अटल पूर्णांक tcam_पढ़ो(काष्ठा niu *np, पूर्णांक index,
		     u64 *key, u64 *mask)
अणु
	पूर्णांक err;

	nw64(TCAM_CTL, (TCAM_CTL_RWC_TCAM_READ | index));
	err = tcam_रुको_bit(np, TCAM_CTL_STAT);
	अगर (!err) अणु
		key[0] = nr64(TCAM_KEY_0);
		key[1] = nr64(TCAM_KEY_1);
		key[2] = nr64(TCAM_KEY_2);
		key[3] = nr64(TCAM_KEY_3);
		mask[0] = nr64(TCAM_KEY_MASK_0);
		mask[1] = nr64(TCAM_KEY_MASK_1);
		mask[2] = nr64(TCAM_KEY_MASK_2);
		mask[3] = nr64(TCAM_KEY_MASK_3);
	पूर्ण
	वापस err;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक tcam_ग_लिखो(काष्ठा niu *np, पूर्णांक index,
		      u64 *key, u64 *mask)
अणु
	nw64(TCAM_KEY_0, key[0]);
	nw64(TCAM_KEY_1, key[1]);
	nw64(TCAM_KEY_2, key[2]);
	nw64(TCAM_KEY_3, key[3]);
	nw64(TCAM_KEY_MASK_0, mask[0]);
	nw64(TCAM_KEY_MASK_1, mask[1]);
	nw64(TCAM_KEY_MASK_2, mask[2]);
	nw64(TCAM_KEY_MASK_3, mask[3]);
	nw64(TCAM_CTL, (TCAM_CTL_RWC_TCAM_WRITE | index));

	वापस tcam_रुको_bit(np, TCAM_CTL_STAT);
पूर्ण

#अगर 0
अटल पूर्णांक tcam_assoc_पढ़ो(काष्ठा niu *np, पूर्णांक index, u64 *data)
अणु
	पूर्णांक err;

	nw64(TCAM_CTL, (TCAM_CTL_RWC_RAM_READ | index));
	err = tcam_रुको_bit(np, TCAM_CTL_STAT);
	अगर (!err)
		*data = nr64(TCAM_KEY_1);

	वापस err;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक tcam_assoc_ग_लिखो(काष्ठा niu *np, पूर्णांक index, u64 assoc_data)
अणु
	nw64(TCAM_KEY_1, assoc_data);
	nw64(TCAM_CTL, (TCAM_CTL_RWC_RAM_WRITE | index));

	वापस tcam_रुको_bit(np, TCAM_CTL_STAT);
पूर्ण

अटल व्योम tcam_enable(काष्ठा niu *np, पूर्णांक on)
अणु
	u64 val = nr64(FFLP_CFG_1);

	अगर (on)
		val &= ~FFLP_CFG_1_TCAM_DIS;
	अन्यथा
		val |= FFLP_CFG_1_TCAM_DIS;
	nw64(FFLP_CFG_1, val);
पूर्ण

अटल व्योम tcam_set_lat_and_ratio(काष्ठा niu *np, u64 latency, u64 ratio)
अणु
	u64 val = nr64(FFLP_CFG_1);

	val &= ~(FFLP_CFG_1_FFLPINITDONE |
		 FFLP_CFG_1_CAMLAT |
		 FFLP_CFG_1_CAMRATIO);
	val |= (latency << FFLP_CFG_1_CAMLAT_SHIFT);
	val |= (ratio << FFLP_CFG_1_CAMRATIO_SHIFT);
	nw64(FFLP_CFG_1, val);

	val = nr64(FFLP_CFG_1);
	val |= FFLP_CFG_1_FFLPINITDONE;
	nw64(FFLP_CFG_1, val);
पूर्ण

अटल पूर्णांक tcam_user_eth_class_enable(काष्ठा niu *np, अचिन्हित दीर्घ class,
				      पूर्णांक on)
अणु
	अचिन्हित दीर्घ reg;
	u64 val;

	अगर (class < CLASS_CODE_ETHERTYPE1 ||
	    class > CLASS_CODE_ETHERTYPE2)
		वापस -EINVAL;

	reg = L2_CLS(class - CLASS_CODE_ETHERTYPE1);
	val = nr64(reg);
	अगर (on)
		val |= L2_CLS_VLD;
	अन्यथा
		val &= ~L2_CLS_VLD;
	nw64(reg, val);

	वापस 0;
पूर्ण

#अगर 0
अटल पूर्णांक tcam_user_eth_class_set(काष्ठा niu *np, अचिन्हित दीर्घ class,
				   u64 ether_type)
अणु
	अचिन्हित दीर्घ reg;
	u64 val;

	अगर (class < CLASS_CODE_ETHERTYPE1 ||
	    class > CLASS_CODE_ETHERTYPE2 ||
	    (ether_type & ~(u64)0xffff) != 0)
		वापस -EINVAL;

	reg = L2_CLS(class - CLASS_CODE_ETHERTYPE1);
	val = nr64(reg);
	val &= ~L2_CLS_ETYPE;
	val |= (ether_type << L2_CLS_ETYPE_SHIFT);
	nw64(reg, val);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक tcam_user_ip_class_enable(काष्ठा niu *np, अचिन्हित दीर्घ class,
				     पूर्णांक on)
अणु
	अचिन्हित दीर्घ reg;
	u64 val;

	अगर (class < CLASS_CODE_USER_PROG1 ||
	    class > CLASS_CODE_USER_PROG4)
		वापस -EINVAL;

	reg = L3_CLS(class - CLASS_CODE_USER_PROG1);
	val = nr64(reg);
	अगर (on)
		val |= L3_CLS_VALID;
	अन्यथा
		val &= ~L3_CLS_VALID;
	nw64(reg, val);

	वापस 0;
पूर्ण

अटल पूर्णांक tcam_user_ip_class_set(काष्ठा niu *np, अचिन्हित दीर्घ class,
				  पूर्णांक ipv6, u64 protocol_id,
				  u64 tos_mask, u64 tos_val)
अणु
	अचिन्हित दीर्घ reg;
	u64 val;

	अगर (class < CLASS_CODE_USER_PROG1 ||
	    class > CLASS_CODE_USER_PROG4 ||
	    (protocol_id & ~(u64)0xff) != 0 ||
	    (tos_mask & ~(u64)0xff) != 0 ||
	    (tos_val & ~(u64)0xff) != 0)
		वापस -EINVAL;

	reg = L3_CLS(class - CLASS_CODE_USER_PROG1);
	val = nr64(reg);
	val &= ~(L3_CLS_IPVER | L3_CLS_PID |
		 L3_CLS_TOSMASK | L3_CLS_TOS);
	अगर (ipv6)
		val |= L3_CLS_IPVER;
	val |= (protocol_id << L3_CLS_PID_SHIFT);
	val |= (tos_mask << L3_CLS_TOSMASK_SHIFT);
	val |= (tos_val << L3_CLS_TOS_SHIFT);
	nw64(reg, val);

	वापस 0;
पूर्ण

अटल पूर्णांक tcam_early_init(काष्ठा niu *np)
अणु
	अचिन्हित दीर्घ i;
	पूर्णांक err;

	tcam_enable(np, 0);
	tcam_set_lat_and_ratio(np,
			       DEFAULT_TCAM_LATENCY,
			       DEFAULT_TCAM_ACCESS_RATIO);
	क्रम (i = CLASS_CODE_ETHERTYPE1; i <= CLASS_CODE_ETHERTYPE2; i++) अणु
		err = tcam_user_eth_class_enable(np, i, 0);
		अगर (err)
			वापस err;
	पूर्ण
	क्रम (i = CLASS_CODE_USER_PROG1; i <= CLASS_CODE_USER_PROG4; i++) अणु
		err = tcam_user_ip_class_enable(np, i, 0);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tcam_flush_all(काष्ठा niu *np)
अणु
	अचिन्हित दीर्घ i;

	क्रम (i = 0; i < np->parent->tcam_num_entries; i++) अणु
		पूर्णांक err = tcam_flush(np, i);
		अगर (err)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल u64 hash_addr_regval(अचिन्हित दीर्घ index, अचिन्हित दीर्घ num_entries)
अणु
	वापस (u64)index | (num_entries == 1 ? HASH_TBL_ADDR_AUTOINC : 0);
पूर्ण

#अगर 0
अटल पूर्णांक hash_पढ़ो(काष्ठा niu *np, अचिन्हित दीर्घ partition,
		     अचिन्हित दीर्घ index, अचिन्हित दीर्घ num_entries,
		     u64 *data)
अणु
	u64 val = hash_addr_regval(index, num_entries);
	अचिन्हित दीर्घ i;

	अगर (partition >= FCRAM_NUM_PARTITIONS ||
	    index + num_entries > FCRAM_SIZE)
		वापस -EINVAL;

	nw64(HASH_TBL_ADDR(partition), val);
	क्रम (i = 0; i < num_entries; i++)
		data[i] = nr64(HASH_TBL_DATA(partition));

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक hash_ग_लिखो(काष्ठा niu *np, अचिन्हित दीर्घ partition,
		      अचिन्हित दीर्घ index, अचिन्हित दीर्घ num_entries,
		      u64 *data)
अणु
	u64 val = hash_addr_regval(index, num_entries);
	अचिन्हित दीर्घ i;

	अगर (partition >= FCRAM_NUM_PARTITIONS ||
	    index + (num_entries * 8) > FCRAM_SIZE)
		वापस -EINVAL;

	nw64(HASH_TBL_ADDR(partition), val);
	क्रम (i = 0; i < num_entries; i++)
		nw64(HASH_TBL_DATA(partition), data[i]);

	वापस 0;
पूर्ण

अटल व्योम fflp_reset(काष्ठा niu *np)
अणु
	u64 val;

	nw64(FFLP_CFG_1, FFLP_CFG_1_PIO_FIO_RST);
	udelay(10);
	nw64(FFLP_CFG_1, 0);

	val = FFLP_CFG_1_FCRAMOUTDR_NORMAL | FFLP_CFG_1_FFLPINITDONE;
	nw64(FFLP_CFG_1, val);
पूर्ण

अटल व्योम fflp_set_timings(काष्ठा niu *np)
अणु
	u64 val = nr64(FFLP_CFG_1);

	val &= ~FFLP_CFG_1_FFLPINITDONE;
	val |= (DEFAULT_FCRAMRATIO << FFLP_CFG_1_FCRAMRATIO_SHIFT);
	nw64(FFLP_CFG_1, val);

	val = nr64(FFLP_CFG_1);
	val |= FFLP_CFG_1_FFLPINITDONE;
	nw64(FFLP_CFG_1, val);

	val = nr64(FCRAM_REF_TMR);
	val &= ~(FCRAM_REF_TMR_MAX | FCRAM_REF_TMR_MIN);
	val |= (DEFAULT_FCRAM_REFRESH_MAX << FCRAM_REF_TMR_MAX_SHIFT);
	val |= (DEFAULT_FCRAM_REFRESH_MIN << FCRAM_REF_TMR_MIN_SHIFT);
	nw64(FCRAM_REF_TMR, val);
पूर्ण

अटल पूर्णांक fflp_set_partition(काष्ठा niu *np, u64 partition,
			      u64 mask, u64 base, पूर्णांक enable)
अणु
	अचिन्हित दीर्घ reg;
	u64 val;

	अगर (partition >= FCRAM_NUM_PARTITIONS ||
	    (mask & ~(u64)0x1f) != 0 ||
	    (base & ~(u64)0x1f) != 0)
		वापस -EINVAL;

	reg = FLW_PRT_SEL(partition);

	val = nr64(reg);
	val &= ~(FLW_PRT_SEL_EXT | FLW_PRT_SEL_MASK | FLW_PRT_SEL_BASE);
	val |= (mask << FLW_PRT_SEL_MASK_SHIFT);
	val |= (base << FLW_PRT_SEL_BASE_SHIFT);
	अगर (enable)
		val |= FLW_PRT_SEL_EXT;
	nw64(reg, val);

	वापस 0;
पूर्ण

अटल पूर्णांक fflp_disable_all_partitions(काष्ठा niu *np)
अणु
	अचिन्हित दीर्घ i;

	क्रम (i = 0; i < FCRAM_NUM_PARTITIONS; i++) अणु
		पूर्णांक err = fflp_set_partition(np, 0, 0, 0, 0);
		अगर (err)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम fflp_llcsnap_enable(काष्ठा niu *np, पूर्णांक on)
अणु
	u64 val = nr64(FFLP_CFG_1);

	अगर (on)
		val |= FFLP_CFG_1_LLCSNAP;
	अन्यथा
		val &= ~FFLP_CFG_1_LLCSNAP;
	nw64(FFLP_CFG_1, val);
पूर्ण

अटल व्योम fflp_errors_enable(काष्ठा niu *np, पूर्णांक on)
अणु
	u64 val = nr64(FFLP_CFG_1);

	अगर (on)
		val &= ~FFLP_CFG_1_ERRORDIS;
	अन्यथा
		val |= FFLP_CFG_1_ERRORDIS;
	nw64(FFLP_CFG_1, val);
पूर्ण

अटल पूर्णांक fflp_hash_clear(काष्ठा niu *np)
अणु
	काष्ठा fcram_hash_ipv4 ent;
	अचिन्हित दीर्घ i;

	/* IPV4 hash entry with valid bit clear, rest is करोn't care.  */
	स_रखो(&ent, 0, माप(ent));
	ent.header = HASH_HEADER_EXT;

	क्रम (i = 0; i < FCRAM_SIZE; i += माप(ent)) अणु
		पूर्णांक err = hash_ग_लिखो(np, 0, i, 1, (u64 *) &ent);
		अगर (err)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक fflp_early_init(काष्ठा niu *np)
अणु
	काष्ठा niu_parent *parent;
	अचिन्हित दीर्घ flags;
	पूर्णांक err;

	niu_lock_parent(np, flags);

	parent = np->parent;
	err = 0;
	अगर (!(parent->flags & PARENT_FLGS_CLS_HWINIT)) अणु
		अगर (np->parent->plat_type != PLAT_TYPE_NIU) अणु
			fflp_reset(np);
			fflp_set_timings(np);
			err = fflp_disable_all_partitions(np);
			अगर (err) अणु
				netअगर_prपूर्णांकk(np, probe, KERN_DEBUG, np->dev,
					     "fflp_disable_all_partitions failed, err=%d\n",
					     err);
				जाओ out;
			पूर्ण
		पूर्ण

		err = tcam_early_init(np);
		अगर (err) अणु
			netअगर_prपूर्णांकk(np, probe, KERN_DEBUG, np->dev,
				     "tcam_early_init failed, err=%d\n", err);
			जाओ out;
		पूर्ण
		fflp_llcsnap_enable(np, 1);
		fflp_errors_enable(np, 0);
		nw64(H1POLY, 0);
		nw64(H2POLY, 0);

		err = tcam_flush_all(np);
		अगर (err) अणु
			netअगर_prपूर्णांकk(np, probe, KERN_DEBUG, np->dev,
				     "tcam_flush_all failed, err=%d\n", err);
			जाओ out;
		पूर्ण
		अगर (np->parent->plat_type != PLAT_TYPE_NIU) अणु
			err = fflp_hash_clear(np);
			अगर (err) अणु
				netअगर_prपूर्णांकk(np, probe, KERN_DEBUG, np->dev,
					     "fflp_hash_clear failed, err=%d\n",
					     err);
				जाओ out;
			पूर्ण
		पूर्ण

		vlan_tbl_clear(np);

		parent->flags |= PARENT_FLGS_CLS_HWINIT;
	पूर्ण
out:
	niu_unlock_parent(np, flags);
	वापस err;
पूर्ण

अटल पूर्णांक niu_set_flow_key(काष्ठा niu *np, अचिन्हित दीर्घ class_code, u64 key)
अणु
	अगर (class_code < CLASS_CODE_USER_PROG1 ||
	    class_code > CLASS_CODE_SCTP_IPV6)
		वापस -EINVAL;

	nw64(FLOW_KEY(class_code - CLASS_CODE_USER_PROG1), key);
	वापस 0;
पूर्ण

अटल पूर्णांक niu_set_tcam_key(काष्ठा niu *np, अचिन्हित दीर्घ class_code, u64 key)
अणु
	अगर (class_code < CLASS_CODE_USER_PROG1 ||
	    class_code > CLASS_CODE_SCTP_IPV6)
		वापस -EINVAL;

	nw64(TCAM_KEY(class_code - CLASS_CODE_USER_PROG1), key);
	वापस 0;
पूर्ण

/* Entries क्रम the ports are पूर्णांकerleaved in the TCAM */
अटल u16 tcam_get_index(काष्ठा niu *np, u16 idx)
अणु
	/* One entry reserved क्रम IP fragment rule */
	अगर (idx >= (np->clas.tcam_sz - 1))
		idx = 0;
	वापस np->clas.tcam_top + ((idx+1) * np->parent->num_ports);
पूर्ण

अटल u16 tcam_get_size(काष्ठा niu *np)
अणु
	/* One entry reserved क्रम IP fragment rule */
	वापस np->clas.tcam_sz - 1;
पूर्ण

अटल u16 tcam_get_valid_entry_cnt(काष्ठा niu *np)
अणु
	/* One entry reserved क्रम IP fragment rule */
	वापस np->clas.tcam_valid_entries - 1;
पूर्ण

अटल व्योम niu_rx_skb_append(काष्ठा sk_buff *skb, काष्ठा page *page,
			      u32 offset, u32 size, u32 truesize)
अणु
	skb_fill_page_desc(skb, skb_shinfo(skb)->nr_frags, page, offset, size);

	skb->len += size;
	skb->data_len += size;
	skb->truesize += truesize;
पूर्ण

अटल अचिन्हित पूर्णांक niu_hash_rxaddr(काष्ठा rx_ring_info *rp, u64 a)
अणु
	a >>= PAGE_SHIFT;
	a ^= (a >> ilog2(MAX_RBR_RING_SIZE));

	वापस a & (MAX_RBR_RING_SIZE - 1);
पूर्ण

अटल काष्ठा page *niu_find_rxpage(काष्ठा rx_ring_info *rp, u64 addr,
				    काष्ठा page ***link)
अणु
	अचिन्हित पूर्णांक h = niu_hash_rxaddr(rp, addr);
	काष्ठा page *p, **pp;

	addr &= PAGE_MASK;
	pp = &rp->rxhash[h];
	क्रम (; (p = *pp) != शून्य; pp = (काष्ठा page **) &p->mapping) अणु
		अगर (p->index == addr) अणु
			*link = pp;
			जाओ found;
		पूर्ण
	पूर्ण
	BUG();

found:
	वापस p;
पूर्ण

अटल व्योम niu_hash_page(काष्ठा rx_ring_info *rp, काष्ठा page *page, u64 base)
अणु
	अचिन्हित पूर्णांक h = niu_hash_rxaddr(rp, base);

	page->index = base;
	page->mapping = (काष्ठा address_space *) rp->rxhash[h];
	rp->rxhash[h] = page;
पूर्ण

अटल पूर्णांक niu_rbr_add_page(काष्ठा niu *np, काष्ठा rx_ring_info *rp,
			    gfp_t mask, पूर्णांक start_index)
अणु
	काष्ठा page *page;
	u64 addr;
	पूर्णांक i;

	page = alloc_page(mask);
	अगर (!page)
		वापस -ENOMEM;

	addr = np->ops->map_page(np->device, page, 0,
				 PAGE_SIZE, DMA_FROM_DEVICE);
	अगर (!addr) अणु
		__मुक्त_page(page);
		वापस -ENOMEM;
	पूर्ण

	niu_hash_page(rp, page, addr);
	अगर (rp->rbr_blocks_per_page > 1)
		page_ref_add(page, rp->rbr_blocks_per_page - 1);

	क्रम (i = 0; i < rp->rbr_blocks_per_page; i++) अणु
		__le32 *rbr = &rp->rbr[start_index + i];

		*rbr = cpu_to_le32(addr >> RBR_DESCR_ADDR_SHIFT);
		addr += rp->rbr_block_size;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम niu_rbr_refill(काष्ठा niu *np, काष्ठा rx_ring_info *rp, gfp_t mask)
अणु
	पूर्णांक index = rp->rbr_index;

	rp->rbr_pending++;
	अगर ((rp->rbr_pending % rp->rbr_blocks_per_page) == 0) अणु
		पूर्णांक err = niu_rbr_add_page(np, rp, mask, index);

		अगर (unlikely(err)) अणु
			rp->rbr_pending--;
			वापस;
		पूर्ण

		rp->rbr_index += rp->rbr_blocks_per_page;
		BUG_ON(rp->rbr_index > rp->rbr_table_size);
		अगर (rp->rbr_index == rp->rbr_table_size)
			rp->rbr_index = 0;

		अगर (rp->rbr_pending >= rp->rbr_kick_thresh) अणु
			nw64(RBR_KICK(rp->rx_channel), rp->rbr_pending);
			rp->rbr_pending = 0;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक niu_rx_pkt_ignore(काष्ठा niu *np, काष्ठा rx_ring_info *rp)
अणु
	अचिन्हित पूर्णांक index = rp->rcr_index;
	पूर्णांक num_rcr = 0;

	rp->rx_dropped++;
	जबतक (1) अणु
		काष्ठा page *page, **link;
		u64 addr, val;
		u32 rcr_size;

		num_rcr++;

		val = le64_to_cpup(&rp->rcr[index]);
		addr = (val & RCR_ENTRY_PKT_BUF_ADDR) <<
			RCR_ENTRY_PKT_BUF_ADDR_SHIFT;
		page = niu_find_rxpage(rp, addr, &link);

		rcr_size = rp->rbr_sizes[(val & RCR_ENTRY_PKTBUFSZ) >>
					 RCR_ENTRY_PKTBUFSZ_SHIFT];
		अगर ((page->index + PAGE_SIZE) - rcr_size == addr) अणु
			*link = (काष्ठा page *) page->mapping;
			np->ops->unmap_page(np->device, page->index,
					    PAGE_SIZE, DMA_FROM_DEVICE);
			page->index = 0;
			page->mapping = शून्य;
			__मुक्त_page(page);
			rp->rbr_refill_pending++;
		पूर्ण

		index = NEXT_RCR(rp, index);
		अगर (!(val & RCR_ENTRY_MULTI))
			अवरोध;

	पूर्ण
	rp->rcr_index = index;

	वापस num_rcr;
पूर्ण

अटल पूर्णांक niu_process_rx_pkt(काष्ठा napi_काष्ठा *napi, काष्ठा niu *np,
			      काष्ठा rx_ring_info *rp)
अणु
	अचिन्हित पूर्णांक index = rp->rcr_index;
	काष्ठा rx_pkt_hdr1 *rh;
	काष्ठा sk_buff *skb;
	पूर्णांक len, num_rcr;

	skb = netdev_alloc_skb(np->dev, RX_SKB_ALLOC_SIZE);
	अगर (unlikely(!skb))
		वापस niu_rx_pkt_ignore(np, rp);

	num_rcr = 0;
	जबतक (1) अणु
		काष्ठा page *page, **link;
		u32 rcr_size, append_size;
		u64 addr, val, off;

		num_rcr++;

		val = le64_to_cpup(&rp->rcr[index]);

		len = (val & RCR_ENTRY_L2_LEN) >>
			RCR_ENTRY_L2_LEN_SHIFT;
		append_size = len + ETH_HLEN + ETH_FCS_LEN;

		addr = (val & RCR_ENTRY_PKT_BUF_ADDR) <<
			RCR_ENTRY_PKT_BUF_ADDR_SHIFT;
		page = niu_find_rxpage(rp, addr, &link);

		rcr_size = rp->rbr_sizes[(val & RCR_ENTRY_PKTBUFSZ) >>
					 RCR_ENTRY_PKTBUFSZ_SHIFT];

		off = addr & ~PAGE_MASK;
		अगर (num_rcr == 1) अणु
			पूर्णांक ptype;

			ptype = (val >> RCR_ENTRY_PKT_TYPE_SHIFT);
			अगर ((ptype == RCR_PKT_TYPE_TCP ||
			     ptype == RCR_PKT_TYPE_UDP) &&
			    !(val & (RCR_ENTRY_NOPORT |
				     RCR_ENTRY_ERROR)))
				skb->ip_summed = CHECKSUM_UNNECESSARY;
			अन्यथा
				skb_checksum_none_निश्चित(skb);
		पूर्ण अन्यथा अगर (!(val & RCR_ENTRY_MULTI))
			append_size = append_size - skb->len;

		niu_rx_skb_append(skb, page, off, append_size, rcr_size);
		अगर ((page->index + rp->rbr_block_size) - rcr_size == addr) अणु
			*link = (काष्ठा page *) page->mapping;
			np->ops->unmap_page(np->device, page->index,
					    PAGE_SIZE, DMA_FROM_DEVICE);
			page->index = 0;
			page->mapping = शून्य;
			rp->rbr_refill_pending++;
		पूर्ण अन्यथा
			get_page(page);

		index = NEXT_RCR(rp, index);
		अगर (!(val & RCR_ENTRY_MULTI))
			अवरोध;

	पूर्ण
	rp->rcr_index = index;

	len += माप(*rh);
	len = min_t(पूर्णांक, len, माप(*rh) + VLAN_ETH_HLEN);
	__pskb_pull_tail(skb, len);

	rh = (काष्ठा rx_pkt_hdr1 *) skb->data;
	अगर (np->dev->features & NETIF_F_RXHASH)
		skb_set_hash(skb,
			     ((u32)rh->hashval2_0 << 24 |
			      (u32)rh->hashval2_1 << 16 |
			      (u32)rh->hashval1_1 << 8 |
			      (u32)rh->hashval1_2 << 0),
			     PKT_HASH_TYPE_L3);
	skb_pull(skb, माप(*rh));

	rp->rx_packets++;
	rp->rx_bytes += skb->len;

	skb->protocol = eth_type_trans(skb, np->dev);
	skb_record_rx_queue(skb, rp->rx_channel);
	napi_gro_receive(napi, skb);

	वापस num_rcr;
पूर्ण

अटल पूर्णांक niu_rbr_fill(काष्ठा niu *np, काष्ठा rx_ring_info *rp, gfp_t mask)
अणु
	पूर्णांक blocks_per_page = rp->rbr_blocks_per_page;
	पूर्णांक err, index = rp->rbr_index;

	err = 0;
	जबतक (index < (rp->rbr_table_size - blocks_per_page)) अणु
		err = niu_rbr_add_page(np, rp, mask, index);
		अगर (unlikely(err))
			अवरोध;

		index += blocks_per_page;
	पूर्ण

	rp->rbr_index = index;
	वापस err;
पूर्ण

अटल व्योम niu_rbr_मुक्त(काष्ठा niu *np, काष्ठा rx_ring_info *rp)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MAX_RBR_RING_SIZE; i++) अणु
		काष्ठा page *page;

		page = rp->rxhash[i];
		जबतक (page) अणु
			काष्ठा page *next = (काष्ठा page *) page->mapping;
			u64 base = page->index;

			np->ops->unmap_page(np->device, base, PAGE_SIZE,
					    DMA_FROM_DEVICE);
			page->index = 0;
			page->mapping = शून्य;

			__मुक्त_page(page);

			page = next;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < rp->rbr_table_size; i++)
		rp->rbr[i] = cpu_to_le32(0);
	rp->rbr_index = 0;
पूर्ण

अटल पूर्णांक release_tx_packet(काष्ठा niu *np, काष्ठा tx_ring_info *rp, पूर्णांक idx)
अणु
	काष्ठा tx_buff_info *tb = &rp->tx_buffs[idx];
	काष्ठा sk_buff *skb = tb->skb;
	काष्ठा tx_pkt_hdr *tp;
	u64 tx_flags;
	पूर्णांक i, len;

	tp = (काष्ठा tx_pkt_hdr *) skb->data;
	tx_flags = le64_to_cpup(&tp->flags);

	rp->tx_packets++;
	rp->tx_bytes += (((tx_flags & TXHDR_LEN) >> TXHDR_LEN_SHIFT) -
			 ((tx_flags & TXHDR_PAD) / 2));

	len = skb_headlen(skb);
	np->ops->unmap_single(np->device, tb->mapping,
			      len, DMA_TO_DEVICE);

	अगर (le64_to_cpu(rp->descr[idx]) & TX_DESC_MARK)
		rp->mark_pending--;

	tb->skb = शून्य;
	करो अणु
		idx = NEXT_TX(rp, idx);
		len -= MAX_TX_DESC_LEN;
	पूर्ण जबतक (len > 0);

	क्रम (i = 0; i < skb_shinfo(skb)->nr_frags; i++) अणु
		tb = &rp->tx_buffs[idx];
		BUG_ON(tb->skb != शून्य);
		np->ops->unmap_page(np->device, tb->mapping,
				    skb_frag_size(&skb_shinfo(skb)->frags[i]),
				    DMA_TO_DEVICE);
		idx = NEXT_TX(rp, idx);
	पूर्ण

	dev_kमुक्त_skb(skb);

	वापस idx;
पूर्ण

#घोषणा NIU_TX_WAKEUP_THRESH(rp)		((rp)->pending / 4)

अटल व्योम niu_tx_work(काष्ठा niu *np, काष्ठा tx_ring_info *rp)
अणु
	काष्ठा netdev_queue *txq;
	u16 pkt_cnt, पंचांगp;
	पूर्णांक cons, index;
	u64 cs;

	index = (rp - np->tx_rings);
	txq = netdev_get_tx_queue(np->dev, index);

	cs = rp->tx_cs;
	अगर (unlikely(!(cs & (TX_CS_MK | TX_CS_MMK))))
		जाओ out;

	पंचांगp = pkt_cnt = (cs & TX_CS_PKT_CNT) >> TX_CS_PKT_CNT_SHIFT;
	pkt_cnt = (pkt_cnt - rp->last_pkt_cnt) &
		(TX_CS_PKT_CNT >> TX_CS_PKT_CNT_SHIFT);

	rp->last_pkt_cnt = पंचांगp;

	cons = rp->cons;

	netअगर_prपूर्णांकk(np, tx_करोne, KERN_DEBUG, np->dev,
		     "%s() pkt_cnt[%u] cons[%d]\n", __func__, pkt_cnt, cons);

	जबतक (pkt_cnt--)
		cons = release_tx_packet(np, rp, cons);

	rp->cons = cons;
	smp_mb();

out:
	अगर (unlikely(netअगर_tx_queue_stopped(txq) &&
		     (niu_tx_avail(rp) > NIU_TX_WAKEUP_THRESH(rp)))) अणु
		__netअगर_tx_lock(txq, smp_processor_id());
		अगर (netअगर_tx_queue_stopped(txq) &&
		    (niu_tx_avail(rp) > NIU_TX_WAKEUP_THRESH(rp)))
			netअगर_tx_wake_queue(txq);
		__netअगर_tx_unlock(txq);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम niu_sync_rx_discard_stats(काष्ठा niu *np,
					     काष्ठा rx_ring_info *rp,
					     स्थिर पूर्णांक limit)
अणु
	/* This elaborate scheme is needed क्रम पढ़ोing the RX discard
	 * counters, as they are only 16-bit and can overflow quickly,
	 * and because the overflow indication bit is not usable as
	 * the counter value करोes not wrap, but reमुख्यs at max value
	 * 0xFFFF.
	 *
	 * In theory and in practice counters can be lost in between
	 * पढ़ोing nr64() and clearing the counter nw64().  For this
	 * reason, the number of counter clearings nw64() is
	 * limited/reduced though the limit parameter.
	 */
	पूर्णांक rx_channel = rp->rx_channel;
	u32 misc, wred;

	/* RXMISC (Receive Miscellaneous Discard Count), covers the
	 * following discard events: IPP (Input Port Process),
	 * FFLP/TCAM, Full RCR (Receive Completion Ring) RBR (Receive
	 * Block Ring) prefetch buffer is empty.
	 */
	misc = nr64(RXMISC(rx_channel));
	अगर (unlikely((misc & RXMISC_COUNT) > limit)) अणु
		nw64(RXMISC(rx_channel), 0);
		rp->rx_errors += misc & RXMISC_COUNT;

		अगर (unlikely(misc & RXMISC_OFLOW))
			dev_err(np->device, "rx-%d: Counter overflow RXMISC discard\n",
				rx_channel);

		netअगर_prपूर्णांकk(np, rx_err, KERN_DEBUG, np->dev,
			     "rx-%d: MISC drop=%u over=%u\n",
			     rx_channel, misc, misc-limit);
	पूर्ण

	/* WRED (Weighted Ranकरोm Early Discard) by hardware */
	wred = nr64(RED_DIS_CNT(rx_channel));
	अगर (unlikely((wred & RED_DIS_CNT_COUNT) > limit)) अणु
		nw64(RED_DIS_CNT(rx_channel), 0);
		rp->rx_dropped += wred & RED_DIS_CNT_COUNT;

		अगर (unlikely(wred & RED_DIS_CNT_OFLOW))
			dev_err(np->device, "rx-%d: Counter overflow WRED discard\n", rx_channel);

		netअगर_prपूर्णांकk(np, rx_err, KERN_DEBUG, np->dev,
			     "rx-%d: WRED drop=%u over=%u\n",
			     rx_channel, wred, wred-limit);
	पूर्ण
पूर्ण

अटल पूर्णांक niu_rx_work(काष्ठा napi_काष्ठा *napi, काष्ठा niu *np,
		       काष्ठा rx_ring_info *rp, पूर्णांक budget)
अणु
	पूर्णांक qlen, rcr_करोne = 0, work_करोne = 0;
	काष्ठा rxdma_mailbox *mbox = rp->mbox;
	u64 stat;

#अगर 1
	stat = nr64(RX_DMA_CTL_STAT(rp->rx_channel));
	qlen = nr64(RCRSTAT_A(rp->rx_channel)) & RCRSTAT_A_QLEN;
#अन्यथा
	stat = le64_to_cpup(&mbox->rx_dma_ctl_stat);
	qlen = (le64_to_cpup(&mbox->rcrstat_a) & RCRSTAT_A_QLEN);
#पूर्ण_अगर
	mbox->rx_dma_ctl_stat = 0;
	mbox->rcrstat_a = 0;

	netअगर_prपूर्णांकk(np, rx_status, KERN_DEBUG, np->dev,
		     "%s(chan[%d]), stat[%llx] qlen=%d\n",
		     __func__, rp->rx_channel, (अचिन्हित दीर्घ दीर्घ)stat, qlen);

	rcr_करोne = work_करोne = 0;
	qlen = min(qlen, budget);
	जबतक (work_करोne < qlen) अणु
		rcr_करोne += niu_process_rx_pkt(napi, np, rp);
		work_करोne++;
	पूर्ण

	अगर (rp->rbr_refill_pending >= rp->rbr_kick_thresh) अणु
		अचिन्हित पूर्णांक i;

		क्रम (i = 0; i < rp->rbr_refill_pending; i++)
			niu_rbr_refill(np, rp, GFP_ATOMIC);
		rp->rbr_refill_pending = 0;
	पूर्ण

	stat = (RX_DMA_CTL_STAT_MEX |
		((u64)work_करोne << RX_DMA_CTL_STAT_PKTREAD_SHIFT) |
		((u64)rcr_करोne << RX_DMA_CTL_STAT_PTRREAD_SHIFT));

	nw64(RX_DMA_CTL_STAT(rp->rx_channel), stat);

	/* Only sync discards stats when qlen indicate potential क्रम drops */
	अगर (qlen > 10)
		niu_sync_rx_discard_stats(np, rp, 0x7FFF);

	वापस work_करोne;
पूर्ण

अटल पूर्णांक niu_poll_core(काष्ठा niu *np, काष्ठा niu_ldg *lp, पूर्णांक budget)
अणु
	u64 v0 = lp->v0;
	u32 tx_vec = (v0 >> 32);
	u32 rx_vec = (v0 & 0xffffffff);
	पूर्णांक i, work_करोne = 0;

	netअगर_prपूर्णांकk(np, पूर्णांकr, KERN_DEBUG, np->dev,
		     "%s() v0[%016llx]\n", __func__, (अचिन्हित दीर्घ दीर्घ)v0);

	क्रम (i = 0; i < np->num_tx_rings; i++) अणु
		काष्ठा tx_ring_info *rp = &np->tx_rings[i];
		अगर (tx_vec & (1 << rp->tx_channel))
			niu_tx_work(np, rp);
		nw64(LD_IM0(LDN_TXDMA(rp->tx_channel)), 0);
	पूर्ण

	क्रम (i = 0; i < np->num_rx_rings; i++) अणु
		काष्ठा rx_ring_info *rp = &np->rx_rings[i];

		अगर (rx_vec & (1 << rp->rx_channel)) अणु
			पूर्णांक this_work_करोne;

			this_work_करोne = niu_rx_work(&lp->napi, np, rp,
						     budget);

			budget -= this_work_करोne;
			work_करोne += this_work_करोne;
		पूर्ण
		nw64(LD_IM0(LDN_RXDMA(rp->rx_channel)), 0);
	पूर्ण

	वापस work_करोne;
पूर्ण

अटल पूर्णांक niu_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा niu_ldg *lp = container_of(napi, काष्ठा niu_ldg, napi);
	काष्ठा niu *np = lp->np;
	पूर्णांक work_करोne;

	work_करोne = niu_poll_core(np, lp, budget);

	अगर (work_करोne < budget) अणु
		napi_complete_करोne(napi, work_करोne);
		niu_ldg_rearm(np, lp, 1);
	पूर्ण
	वापस work_करोne;
पूर्ण

अटल व्योम niu_log_rxchan_errors(काष्ठा niu *np, काष्ठा rx_ring_info *rp,
				  u64 stat)
अणु
	netdev_err(np->dev, "RX channel %u errors ( ", rp->rx_channel);

	अगर (stat & RX_DMA_CTL_STAT_RBR_TMOUT)
		pr_cont("RBR_TMOUT ");
	अगर (stat & RX_DMA_CTL_STAT_RSP_CNT_ERR)
		pr_cont("RSP_CNT ");
	अगर (stat & RX_DMA_CTL_STAT_BYTE_EN_BUS)
		pr_cont("BYTE_EN_BUS ");
	अगर (stat & RX_DMA_CTL_STAT_RSP_DAT_ERR)
		pr_cont("RSP_DAT ");
	अगर (stat & RX_DMA_CTL_STAT_RCR_ACK_ERR)
		pr_cont("RCR_ACK ");
	अगर (stat & RX_DMA_CTL_STAT_RCR_SHA_PAR)
		pr_cont("RCR_SHA_PAR ");
	अगर (stat & RX_DMA_CTL_STAT_RBR_PRE_PAR)
		pr_cont("RBR_PRE_PAR ");
	अगर (stat & RX_DMA_CTL_STAT_CONFIG_ERR)
		pr_cont("CONFIG ");
	अगर (stat & RX_DMA_CTL_STAT_RCRINCON)
		pr_cont("RCRINCON ");
	अगर (stat & RX_DMA_CTL_STAT_RCRFULL)
		pr_cont("RCRFULL ");
	अगर (stat & RX_DMA_CTL_STAT_RBRFULL)
		pr_cont("RBRFULL ");
	अगर (stat & RX_DMA_CTL_STAT_RBRLOGPAGE)
		pr_cont("RBRLOGPAGE ");
	अगर (stat & RX_DMA_CTL_STAT_CFIGLOGPAGE)
		pr_cont("CFIGLOGPAGE ");
	अगर (stat & RX_DMA_CTL_STAT_DC_FIFO_ERR)
		pr_cont("DC_FIDO ");

	pr_cont(")\n");
पूर्ण

अटल पूर्णांक niu_rx_error(काष्ठा niu *np, काष्ठा rx_ring_info *rp)
अणु
	u64 stat = nr64(RX_DMA_CTL_STAT(rp->rx_channel));
	पूर्णांक err = 0;


	अगर (stat & (RX_DMA_CTL_STAT_CHAN_FATAL |
		    RX_DMA_CTL_STAT_PORT_FATAL))
		err = -EINVAL;

	अगर (err) अणु
		netdev_err(np->dev, "RX channel %u error, stat[%llx]\n",
			   rp->rx_channel,
			   (अचिन्हित दीर्घ दीर्घ) stat);

		niu_log_rxchan_errors(np, rp, stat);
	पूर्ण

	nw64(RX_DMA_CTL_STAT(rp->rx_channel),
	     stat & RX_DMA_CTL_WRITE_CLEAR_ERRS);

	वापस err;
पूर्ण

अटल व्योम niu_log_txchan_errors(काष्ठा niu *np, काष्ठा tx_ring_info *rp,
				  u64 cs)
अणु
	netdev_err(np->dev, "TX channel %u errors ( ", rp->tx_channel);

	अगर (cs & TX_CS_MBOX_ERR)
		pr_cont("MBOX ");
	अगर (cs & TX_CS_PKT_SIZE_ERR)
		pr_cont("PKT_SIZE ");
	अगर (cs & TX_CS_TX_RING_OFLOW)
		pr_cont("TX_RING_OFLOW ");
	अगर (cs & TX_CS_PREF_BUF_PAR_ERR)
		pr_cont("PREF_BUF_PAR ");
	अगर (cs & TX_CS_NACK_PREF)
		pr_cont("NACK_PREF ");
	अगर (cs & TX_CS_NACK_PKT_RD)
		pr_cont("NACK_PKT_RD ");
	अगर (cs & TX_CS_CONF_PART_ERR)
		pr_cont("CONF_PART ");
	अगर (cs & TX_CS_PKT_PRT_ERR)
		pr_cont("PKT_PTR ");

	pr_cont(")\n");
पूर्ण

अटल पूर्णांक niu_tx_error(काष्ठा niu *np, काष्ठा tx_ring_info *rp)
अणु
	u64 cs, logh, logl;

	cs = nr64(TX_CS(rp->tx_channel));
	logh = nr64(TX_RNG_ERR_LOGH(rp->tx_channel));
	logl = nr64(TX_RNG_ERR_LOGL(rp->tx_channel));

	netdev_err(np->dev, "TX channel %u error, cs[%llx] logh[%llx] logl[%llx]\n",
		   rp->tx_channel,
		   (अचिन्हित दीर्घ दीर्घ)cs,
		   (अचिन्हित दीर्घ दीर्घ)logh,
		   (अचिन्हित दीर्घ दीर्घ)logl);

	niu_log_txchan_errors(np, rp, cs);

	वापस -ENODEV;
पूर्ण

अटल पूर्णांक niu_mअगर_पूर्णांकerrupt(काष्ठा niu *np)
अणु
	u64 mअगर_status = nr64(MIF_STATUS);
	पूर्णांक phy_mdपूर्णांक = 0;

	अगर (np->flags & NIU_FLAGS_XMAC) अणु
		u64 xrxmac_stat = nr64_mac(XRXMAC_STATUS);

		अगर (xrxmac_stat & XRXMAC_STATUS_PHY_MDINT)
			phy_mdपूर्णांक = 1;
	पूर्ण

	netdev_err(np->dev, "MIF interrupt, stat[%llx] phy_mdint(%d)\n",
		   (अचिन्हित दीर्घ दीर्घ)mअगर_status, phy_mdपूर्णांक);

	वापस -ENODEV;
पूर्ण

अटल व्योम niu_xmac_पूर्णांकerrupt(काष्ठा niu *np)
अणु
	काष्ठा niu_xmac_stats *mp = &np->mac_stats.xmac;
	u64 val;

	val = nr64_mac(XTXMAC_STATUS);
	अगर (val & XTXMAC_STATUS_FRAME_CNT_EXP)
		mp->tx_frames += TXMAC_FRM_CNT_COUNT;
	अगर (val & XTXMAC_STATUS_BYTE_CNT_EXP)
		mp->tx_bytes += TXMAC_BYTE_CNT_COUNT;
	अगर (val & XTXMAC_STATUS_TXFIFO_XFR_ERR)
		mp->tx_fअगरo_errors++;
	अगर (val & XTXMAC_STATUS_TXMAC_OFLOW)
		mp->tx_overflow_errors++;
	अगर (val & XTXMAC_STATUS_MAX_PSIZE_ERR)
		mp->tx_max_pkt_size_errors++;
	अगर (val & XTXMAC_STATUS_TXMAC_UFLOW)
		mp->tx_underflow_errors++;

	val = nr64_mac(XRXMAC_STATUS);
	अगर (val & XRXMAC_STATUS_LCL_FLT_STATUS)
		mp->rx_local_faults++;
	अगर (val & XRXMAC_STATUS_RFLT_DET)
		mp->rx_remote_faults++;
	अगर (val & XRXMAC_STATUS_LFLT_CNT_EXP)
		mp->rx_link_faults += LINK_FAULT_CNT_COUNT;
	अगर (val & XRXMAC_STATUS_ALIGNERR_CNT_EXP)
		mp->rx_align_errors += RXMAC_ALIGN_ERR_CNT_COUNT;
	अगर (val & XRXMAC_STATUS_RXFRAG_CNT_EXP)
		mp->rx_frags += RXMAC_FRAG_CNT_COUNT;
	अगर (val & XRXMAC_STATUS_RXMULTF_CNT_EXP)
		mp->rx_mcasts += RXMAC_MC_FRM_CNT_COUNT;
	अगर (val & XRXMAC_STATUS_RXBCAST_CNT_EXP)
		mp->rx_bcasts += RXMAC_BC_FRM_CNT_COUNT;
	अगर (val & XRXMAC_STATUS_RXHIST1_CNT_EXP)
		mp->rx_hist_cnt1 += RXMAC_HIST_CNT1_COUNT;
	अगर (val & XRXMAC_STATUS_RXHIST2_CNT_EXP)
		mp->rx_hist_cnt2 += RXMAC_HIST_CNT2_COUNT;
	अगर (val & XRXMAC_STATUS_RXHIST3_CNT_EXP)
		mp->rx_hist_cnt3 += RXMAC_HIST_CNT3_COUNT;
	अगर (val & XRXMAC_STATUS_RXHIST4_CNT_EXP)
		mp->rx_hist_cnt4 += RXMAC_HIST_CNT4_COUNT;
	अगर (val & XRXMAC_STATUS_RXHIST5_CNT_EXP)
		mp->rx_hist_cnt5 += RXMAC_HIST_CNT5_COUNT;
	अगर (val & XRXMAC_STATUS_RXHIST6_CNT_EXP)
		mp->rx_hist_cnt6 += RXMAC_HIST_CNT6_COUNT;
	अगर (val & XRXMAC_STATUS_RXHIST7_CNT_EXP)
		mp->rx_hist_cnt7 += RXMAC_HIST_CNT7_COUNT;
	अगर (val & XRXMAC_STATUS_RXOCTET_CNT_EXP)
		mp->rx_octets += RXMAC_BT_CNT_COUNT;
	अगर (val & XRXMAC_STATUS_CVIOLERR_CNT_EXP)
		mp->rx_code_violations += RXMAC_CD_VIO_CNT_COUNT;
	अगर (val & XRXMAC_STATUS_LENERR_CNT_EXP)
		mp->rx_len_errors += RXMAC_MPSZER_CNT_COUNT;
	अगर (val & XRXMAC_STATUS_CRCERR_CNT_EXP)
		mp->rx_crc_errors += RXMAC_CRC_ER_CNT_COUNT;
	अगर (val & XRXMAC_STATUS_RXUFLOW)
		mp->rx_underflows++;
	अगर (val & XRXMAC_STATUS_RXOFLOW)
		mp->rx_overflows++;

	val = nr64_mac(XMAC_FC_STAT);
	अगर (val & XMAC_FC_STAT_TX_MAC_NPAUSE)
		mp->छोड़ो_off_state++;
	अगर (val & XMAC_FC_STAT_TX_MAC_PAUSE)
		mp->छोड़ो_on_state++;
	अगर (val & XMAC_FC_STAT_RX_MAC_RPAUSE)
		mp->छोड़ो_received++;
पूर्ण

अटल व्योम niu_bmac_पूर्णांकerrupt(काष्ठा niu *np)
अणु
	काष्ठा niu_bmac_stats *mp = &np->mac_stats.bmac;
	u64 val;

	val = nr64_mac(BTXMAC_STATUS);
	अगर (val & BTXMAC_STATUS_UNDERRUN)
		mp->tx_underflow_errors++;
	अगर (val & BTXMAC_STATUS_MAX_PKT_ERR)
		mp->tx_max_pkt_size_errors++;
	अगर (val & BTXMAC_STATUS_BYTE_CNT_EXP)
		mp->tx_bytes += BTXMAC_BYTE_CNT_COUNT;
	अगर (val & BTXMAC_STATUS_FRAME_CNT_EXP)
		mp->tx_frames += BTXMAC_FRM_CNT_COUNT;

	val = nr64_mac(BRXMAC_STATUS);
	अगर (val & BRXMAC_STATUS_OVERFLOW)
		mp->rx_overflows++;
	अगर (val & BRXMAC_STATUS_FRAME_CNT_EXP)
		mp->rx_frames += BRXMAC_FRAME_CNT_COUNT;
	अगर (val & BRXMAC_STATUS_ALIGN_ERR_EXP)
		mp->rx_align_errors += BRXMAC_ALIGN_ERR_CNT_COUNT;
	अगर (val & BRXMAC_STATUS_CRC_ERR_EXP)
		mp->rx_crc_errors += BRXMAC_ALIGN_ERR_CNT_COUNT;
	अगर (val & BRXMAC_STATUS_LEN_ERR_EXP)
		mp->rx_len_errors += BRXMAC_CODE_VIOL_ERR_CNT_COUNT;

	val = nr64_mac(BMAC_CTRL_STATUS);
	अगर (val & BMAC_CTRL_STATUS_NOPAUSE)
		mp->छोड़ो_off_state++;
	अगर (val & BMAC_CTRL_STATUS_PAUSE)
		mp->छोड़ो_on_state++;
	अगर (val & BMAC_CTRL_STATUS_PAUSE_RECV)
		mp->छोड़ो_received++;
पूर्ण

अटल पूर्णांक niu_mac_पूर्णांकerrupt(काष्ठा niu *np)
अणु
	अगर (np->flags & NIU_FLAGS_XMAC)
		niu_xmac_पूर्णांकerrupt(np);
	अन्यथा
		niu_bmac_पूर्णांकerrupt(np);

	वापस 0;
पूर्ण

अटल व्योम niu_log_device_error(काष्ठा niu *np, u64 stat)
अणु
	netdev_err(np->dev, "Core device errors ( ");

	अगर (stat & SYS_ERR_MASK_META2)
		pr_cont("META2 ");
	अगर (stat & SYS_ERR_MASK_META1)
		pr_cont("META1 ");
	अगर (stat & SYS_ERR_MASK_PEU)
		pr_cont("PEU ");
	अगर (stat & SYS_ERR_MASK_TXC)
		pr_cont("TXC ");
	अगर (stat & SYS_ERR_MASK_RDMC)
		pr_cont("RDMC ");
	अगर (stat & SYS_ERR_MASK_TDMC)
		pr_cont("TDMC ");
	अगर (stat & SYS_ERR_MASK_ZCP)
		pr_cont("ZCP ");
	अगर (stat & SYS_ERR_MASK_FFLP)
		pr_cont("FFLP ");
	अगर (stat & SYS_ERR_MASK_IPP)
		pr_cont("IPP ");
	अगर (stat & SYS_ERR_MASK_MAC)
		pr_cont("MAC ");
	अगर (stat & SYS_ERR_MASK_SMX)
		pr_cont("SMX ");

	pr_cont(")\n");
पूर्ण

अटल पूर्णांक niu_device_error(काष्ठा niu *np)
अणु
	u64 stat = nr64(SYS_ERR_STAT);

	netdev_err(np->dev, "Core device error, stat[%llx]\n",
		   (अचिन्हित दीर्घ दीर्घ)stat);

	niu_log_device_error(np, stat);

	वापस -ENODEV;
पूर्ण

अटल पूर्णांक niu_slowpath_पूर्णांकerrupt(काष्ठा niu *np, काष्ठा niu_ldg *lp,
			      u64 v0, u64 v1, u64 v2)
अणु

	पूर्णांक i, err = 0;

	lp->v0 = v0;
	lp->v1 = v1;
	lp->v2 = v2;

	अगर (v1 & 0x00000000ffffffffULL) अणु
		u32 rx_vec = (v1 & 0xffffffff);

		क्रम (i = 0; i < np->num_rx_rings; i++) अणु
			काष्ठा rx_ring_info *rp = &np->rx_rings[i];

			अगर (rx_vec & (1 << rp->rx_channel)) अणु
				पूर्णांक r = niu_rx_error(np, rp);
				अगर (r) अणु
					err = r;
				पूर्ण अन्यथा अणु
					अगर (!v0)
						nw64(RX_DMA_CTL_STAT(rp->rx_channel),
						     RX_DMA_CTL_STAT_MEX);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (v1 & 0x7fffffff00000000ULL) अणु
		u32 tx_vec = (v1 >> 32) & 0x7fffffff;

		क्रम (i = 0; i < np->num_tx_rings; i++) अणु
			काष्ठा tx_ring_info *rp = &np->tx_rings[i];

			अगर (tx_vec & (1 << rp->tx_channel)) अणु
				पूर्णांक r = niu_tx_error(np, rp);
				अगर (r)
					err = r;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर ((v0 | v1) & 0x8000000000000000ULL) अणु
		पूर्णांक r = niu_mअगर_पूर्णांकerrupt(np);
		अगर (r)
			err = r;
	पूर्ण
	अगर (v2) अणु
		अगर (v2 & 0x01ef) अणु
			पूर्णांक r = niu_mac_पूर्णांकerrupt(np);
			अगर (r)
				err = r;
		पूर्ण
		अगर (v2 & 0x0210) अणु
			पूर्णांक r = niu_device_error(np);
			अगर (r)
				err = r;
		पूर्ण
	पूर्ण

	अगर (err)
		niu_enable_पूर्णांकerrupts(np, 0);

	वापस err;
पूर्ण

अटल व्योम niu_rxchan_पूर्णांकr(काष्ठा niu *np, काष्ठा rx_ring_info *rp,
			    पूर्णांक ldn)
अणु
	काष्ठा rxdma_mailbox *mbox = rp->mbox;
	u64 stat_ग_लिखो, stat = le64_to_cpup(&mbox->rx_dma_ctl_stat);

	stat_ग_लिखो = (RX_DMA_CTL_STAT_RCRTHRES |
		      RX_DMA_CTL_STAT_RCRTO);
	nw64(RX_DMA_CTL_STAT(rp->rx_channel), stat_ग_लिखो);

	netअगर_prपूर्णांकk(np, पूर्णांकr, KERN_DEBUG, np->dev,
		     "%s() stat[%llx]\n", __func__, (अचिन्हित दीर्घ दीर्घ)stat);
पूर्ण

अटल व्योम niu_txchan_पूर्णांकr(काष्ठा niu *np, काष्ठा tx_ring_info *rp,
			    पूर्णांक ldn)
अणु
	rp->tx_cs = nr64(TX_CS(rp->tx_channel));

	netअगर_prपूर्णांकk(np, पूर्णांकr, KERN_DEBUG, np->dev,
		     "%s() cs[%llx]\n", __func__, (अचिन्हित दीर्घ दीर्घ)rp->tx_cs);
पूर्ण

अटल व्योम __niu_fastpath_पूर्णांकerrupt(काष्ठा niu *np, पूर्णांक ldg, u64 v0)
अणु
	काष्ठा niu_parent *parent = np->parent;
	u32 rx_vec, tx_vec;
	पूर्णांक i;

	tx_vec = (v0 >> 32);
	rx_vec = (v0 & 0xffffffff);

	क्रम (i = 0; i < np->num_rx_rings; i++) अणु
		काष्ठा rx_ring_info *rp = &np->rx_rings[i];
		पूर्णांक ldn = LDN_RXDMA(rp->rx_channel);

		अगर (parent->ldg_map[ldn] != ldg)
			जारी;

		nw64(LD_IM0(ldn), LD_IM0_MASK);
		अगर (rx_vec & (1 << rp->rx_channel))
			niu_rxchan_पूर्णांकr(np, rp, ldn);
	पूर्ण

	क्रम (i = 0; i < np->num_tx_rings; i++) अणु
		काष्ठा tx_ring_info *rp = &np->tx_rings[i];
		पूर्णांक ldn = LDN_TXDMA(rp->tx_channel);

		अगर (parent->ldg_map[ldn] != ldg)
			जारी;

		nw64(LD_IM0(ldn), LD_IM0_MASK);
		अगर (tx_vec & (1 << rp->tx_channel))
			niu_txchan_पूर्णांकr(np, rp, ldn);
	पूर्ण
पूर्ण

अटल व्योम niu_schedule_napi(काष्ठा niu *np, काष्ठा niu_ldg *lp,
			      u64 v0, u64 v1, u64 v2)
अणु
	अगर (likely(napi_schedule_prep(&lp->napi))) अणु
		lp->v0 = v0;
		lp->v1 = v1;
		lp->v2 = v2;
		__niu_fastpath_पूर्णांकerrupt(np, lp->ldg_num, v0);
		__napi_schedule(&lp->napi);
	पूर्ण
पूर्ण

अटल irqवापस_t niu_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा niu_ldg *lp = dev_id;
	काष्ठा niu *np = lp->np;
	पूर्णांक ldg = lp->ldg_num;
	अचिन्हित दीर्घ flags;
	u64 v0, v1, v2;

	अगर (netअगर_msg_पूर्णांकr(np))
		prपूर्णांकk(KERN_DEBUG KBUILD_MODNAME ": " "%s() ldg[%p](%d)",
		       __func__, lp, ldg);

	spin_lock_irqsave(&np->lock, flags);

	v0 = nr64(LDSV0(ldg));
	v1 = nr64(LDSV1(ldg));
	v2 = nr64(LDSV2(ldg));

	अगर (netअगर_msg_पूर्णांकr(np))
		pr_cont(" v0[%llx] v1[%llx] v2[%llx]\n",
		       (अचिन्हित दीर्घ दीर्घ) v0,
		       (अचिन्हित दीर्घ दीर्घ) v1,
		       (अचिन्हित दीर्घ दीर्घ) v2);

	अगर (unlikely(!v0 && !v1 && !v2)) अणु
		spin_unlock_irqrestore(&np->lock, flags);
		वापस IRQ_NONE;
	पूर्ण

	अगर (unlikely((v0 & ((u64)1 << LDN_MIF)) || v1 || v2)) अणु
		पूर्णांक err = niu_slowpath_पूर्णांकerrupt(np, lp, v0, v1, v2);
		अगर (err)
			जाओ out;
	पूर्ण
	अगर (likely(v0 & ~((u64)1 << LDN_MIF)))
		niu_schedule_napi(np, lp, v0, v1, v2);
	अन्यथा
		niu_ldg_rearm(np, lp, 1);
out:
	spin_unlock_irqrestore(&np->lock, flags);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम niu_मुक्त_rx_ring_info(काष्ठा niu *np, काष्ठा rx_ring_info *rp)
अणु
	अगर (rp->mbox) अणु
		np->ops->मुक्त_coherent(np->device,
				       माप(काष्ठा rxdma_mailbox),
				       rp->mbox, rp->mbox_dma);
		rp->mbox = शून्य;
	पूर्ण
	अगर (rp->rcr) अणु
		np->ops->मुक्त_coherent(np->device,
				       MAX_RCR_RING_SIZE * माप(__le64),
				       rp->rcr, rp->rcr_dma);
		rp->rcr = शून्य;
		rp->rcr_table_size = 0;
		rp->rcr_index = 0;
	पूर्ण
	अगर (rp->rbr) अणु
		niu_rbr_मुक्त(np, rp);

		np->ops->मुक्त_coherent(np->device,
				       MAX_RBR_RING_SIZE * माप(__le32),
				       rp->rbr, rp->rbr_dma);
		rp->rbr = शून्य;
		rp->rbr_table_size = 0;
		rp->rbr_index = 0;
	पूर्ण
	kमुक्त(rp->rxhash);
	rp->rxhash = शून्य;
पूर्ण

अटल व्योम niu_मुक्त_tx_ring_info(काष्ठा niu *np, काष्ठा tx_ring_info *rp)
अणु
	अगर (rp->mbox) अणु
		np->ops->मुक्त_coherent(np->device,
				       माप(काष्ठा txdma_mailbox),
				       rp->mbox, rp->mbox_dma);
		rp->mbox = शून्य;
	पूर्ण
	अगर (rp->descr) अणु
		पूर्णांक i;

		क्रम (i = 0; i < MAX_TX_RING_SIZE; i++) अणु
			अगर (rp->tx_buffs[i].skb)
				(व्योम) release_tx_packet(np, rp, i);
		पूर्ण

		np->ops->मुक्त_coherent(np->device,
				       MAX_TX_RING_SIZE * माप(__le64),
				       rp->descr, rp->descr_dma);
		rp->descr = शून्य;
		rp->pending = 0;
		rp->prod = 0;
		rp->cons = 0;
		rp->wrap_bit = 0;
	पूर्ण
पूर्ण

अटल व्योम niu_मुक्त_channels(काष्ठा niu *np)
अणु
	पूर्णांक i;

	अगर (np->rx_rings) अणु
		क्रम (i = 0; i < np->num_rx_rings; i++) अणु
			काष्ठा rx_ring_info *rp = &np->rx_rings[i];

			niu_मुक्त_rx_ring_info(np, rp);
		पूर्ण
		kमुक्त(np->rx_rings);
		np->rx_rings = शून्य;
		np->num_rx_rings = 0;
	पूर्ण

	अगर (np->tx_rings) अणु
		क्रम (i = 0; i < np->num_tx_rings; i++) अणु
			काष्ठा tx_ring_info *rp = &np->tx_rings[i];

			niu_मुक्त_tx_ring_info(np, rp);
		पूर्ण
		kमुक्त(np->tx_rings);
		np->tx_rings = शून्य;
		np->num_tx_rings = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक niu_alloc_rx_ring_info(काष्ठा niu *np,
				  काष्ठा rx_ring_info *rp)
अणु
	BUILD_BUG_ON(माप(काष्ठा rxdma_mailbox) != 64);

	rp->rxhash = kसुस्मृति(MAX_RBR_RING_SIZE, माप(काष्ठा page *),
			     GFP_KERNEL);
	अगर (!rp->rxhash)
		वापस -ENOMEM;

	rp->mbox = np->ops->alloc_coherent(np->device,
					   माप(काष्ठा rxdma_mailbox),
					   &rp->mbox_dma, GFP_KERNEL);
	अगर (!rp->mbox)
		वापस -ENOMEM;
	अगर ((अचिन्हित दीर्घ)rp->mbox & (64UL - 1)) अणु
		netdev_err(np->dev, "Coherent alloc gives misaligned RXDMA mailbox %p\n",
			   rp->mbox);
		वापस -EINVAL;
	पूर्ण

	rp->rcr = np->ops->alloc_coherent(np->device,
					  MAX_RCR_RING_SIZE * माप(__le64),
					  &rp->rcr_dma, GFP_KERNEL);
	अगर (!rp->rcr)
		वापस -ENOMEM;
	अगर ((अचिन्हित दीर्घ)rp->rcr & (64UL - 1)) अणु
		netdev_err(np->dev, "Coherent alloc gives misaligned RXDMA RCR table %p\n",
			   rp->rcr);
		वापस -EINVAL;
	पूर्ण
	rp->rcr_table_size = MAX_RCR_RING_SIZE;
	rp->rcr_index = 0;

	rp->rbr = np->ops->alloc_coherent(np->device,
					  MAX_RBR_RING_SIZE * माप(__le32),
					  &rp->rbr_dma, GFP_KERNEL);
	अगर (!rp->rbr)
		वापस -ENOMEM;
	अगर ((अचिन्हित दीर्घ)rp->rbr & (64UL - 1)) अणु
		netdev_err(np->dev, "Coherent alloc gives misaligned RXDMA RBR table %p\n",
			   rp->rbr);
		वापस -EINVAL;
	पूर्ण
	rp->rbr_table_size = MAX_RBR_RING_SIZE;
	rp->rbr_index = 0;
	rp->rbr_pending = 0;

	वापस 0;
पूर्ण

अटल व्योम niu_set_max_burst(काष्ठा niu *np, काष्ठा tx_ring_info *rp)
अणु
	पूर्णांक mtu = np->dev->mtu;

	/* These values are recommended by the HW designers क्रम fair
	 * utilization of DRR amongst the rings.
	 */
	rp->max_burst = mtu + 32;
	अगर (rp->max_burst > 4096)
		rp->max_burst = 4096;
पूर्ण

अटल पूर्णांक niu_alloc_tx_ring_info(काष्ठा niu *np,
				  काष्ठा tx_ring_info *rp)
अणु
	BUILD_BUG_ON(माप(काष्ठा txdma_mailbox) != 64);

	rp->mbox = np->ops->alloc_coherent(np->device,
					   माप(काष्ठा txdma_mailbox),
					   &rp->mbox_dma, GFP_KERNEL);
	अगर (!rp->mbox)
		वापस -ENOMEM;
	अगर ((अचिन्हित दीर्घ)rp->mbox & (64UL - 1)) अणु
		netdev_err(np->dev, "Coherent alloc gives misaligned TXDMA mailbox %p\n",
			   rp->mbox);
		वापस -EINVAL;
	पूर्ण

	rp->descr = np->ops->alloc_coherent(np->device,
					    MAX_TX_RING_SIZE * माप(__le64),
					    &rp->descr_dma, GFP_KERNEL);
	अगर (!rp->descr)
		वापस -ENOMEM;
	अगर ((अचिन्हित दीर्घ)rp->descr & (64UL - 1)) अणु
		netdev_err(np->dev, "Coherent alloc gives misaligned TXDMA descr table %p\n",
			   rp->descr);
		वापस -EINVAL;
	पूर्ण

	rp->pending = MAX_TX_RING_SIZE;
	rp->prod = 0;
	rp->cons = 0;
	rp->wrap_bit = 0;

	/* XXX make these configurable... XXX */
	rp->mark_freq = rp->pending / 4;

	niu_set_max_burst(np, rp);

	वापस 0;
पूर्ण

अटल व्योम niu_size_rbr(काष्ठा niu *np, काष्ठा rx_ring_info *rp)
अणु
	u16 bss;

	bss = min(PAGE_SHIFT, 15);

	rp->rbr_block_size = 1 << bss;
	rp->rbr_blocks_per_page = 1 << (PAGE_SHIFT-bss);

	rp->rbr_sizes[0] = 256;
	rp->rbr_sizes[1] = 1024;
	अगर (np->dev->mtu > ETH_DATA_LEN) अणु
		चयन (PAGE_SIZE) अणु
		हाल 4 * 1024:
			rp->rbr_sizes[2] = 4096;
			अवरोध;

		शेष:
			rp->rbr_sizes[2] = 8192;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		rp->rbr_sizes[2] = 2048;
	पूर्ण
	rp->rbr_sizes[3] = rp->rbr_block_size;
पूर्ण

अटल पूर्णांक niu_alloc_channels(काष्ठा niu *np)
अणु
	काष्ठा niu_parent *parent = np->parent;
	पूर्णांक first_rx_channel, first_tx_channel;
	पूर्णांक num_rx_rings, num_tx_rings;
	काष्ठा rx_ring_info *rx_rings;
	काष्ठा tx_ring_info *tx_rings;
	पूर्णांक i, port, err;

	port = np->port;
	first_rx_channel = first_tx_channel = 0;
	क्रम (i = 0; i < port; i++) अणु
		first_rx_channel += parent->rxchan_per_port[i];
		first_tx_channel += parent->txchan_per_port[i];
	पूर्ण

	num_rx_rings = parent->rxchan_per_port[port];
	num_tx_rings = parent->txchan_per_port[port];

	rx_rings = kसुस्मृति(num_rx_rings, माप(काष्ठा rx_ring_info),
			   GFP_KERNEL);
	err = -ENOMEM;
	अगर (!rx_rings)
		जाओ out_err;

	np->num_rx_rings = num_rx_rings;
	smp_wmb();
	np->rx_rings = rx_rings;

	netअगर_set_real_num_rx_queues(np->dev, num_rx_rings);

	क्रम (i = 0; i < np->num_rx_rings; i++) अणु
		काष्ठा rx_ring_info *rp = &np->rx_rings[i];

		rp->np = np;
		rp->rx_channel = first_rx_channel + i;

		err = niu_alloc_rx_ring_info(np, rp);
		अगर (err)
			जाओ out_err;

		niu_size_rbr(np, rp);

		/* XXX better शेषs, configurable, etc... XXX */
		rp->nonsyn_winकरोw = 64;
		rp->nonsyn_threshold = rp->rcr_table_size - 64;
		rp->syn_winकरोw = 64;
		rp->syn_threshold = rp->rcr_table_size - 64;
		rp->rcr_pkt_threshold = 16;
		rp->rcr_समयout = 8;
		rp->rbr_kick_thresh = RBR_REFILL_MIN;
		अगर (rp->rbr_kick_thresh < rp->rbr_blocks_per_page)
			rp->rbr_kick_thresh = rp->rbr_blocks_per_page;

		err = niu_rbr_fill(np, rp, GFP_KERNEL);
		अगर (err)
			वापस err;
	पूर्ण

	tx_rings = kसुस्मृति(num_tx_rings, माप(काष्ठा tx_ring_info),
			   GFP_KERNEL);
	err = -ENOMEM;
	अगर (!tx_rings)
		जाओ out_err;

	np->num_tx_rings = num_tx_rings;
	smp_wmb();
	np->tx_rings = tx_rings;

	netअगर_set_real_num_tx_queues(np->dev, num_tx_rings);

	क्रम (i = 0; i < np->num_tx_rings; i++) अणु
		काष्ठा tx_ring_info *rp = &np->tx_rings[i];

		rp->np = np;
		rp->tx_channel = first_tx_channel + i;

		err = niu_alloc_tx_ring_info(np, rp);
		अगर (err)
			जाओ out_err;
	पूर्ण

	वापस 0;

out_err:
	niu_मुक्त_channels(np);
	वापस err;
पूर्ण

अटल पूर्णांक niu_tx_cs_sng_poll(काष्ठा niu *np, पूर्णांक channel)
अणु
	पूर्णांक limit = 1000;

	जबतक (--limit > 0) अणु
		u64 val = nr64(TX_CS(channel));
		अगर (val & TX_CS_SNG_STATE)
			वापस 0;
	पूर्ण
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक niu_tx_channel_stop(काष्ठा niu *np, पूर्णांक channel)
अणु
	u64 val = nr64(TX_CS(channel));

	val |= TX_CS_STOP_N_GO;
	nw64(TX_CS(channel), val);

	वापस niu_tx_cs_sng_poll(np, channel);
पूर्ण

अटल पूर्णांक niu_tx_cs_reset_poll(काष्ठा niu *np, पूर्णांक channel)
अणु
	पूर्णांक limit = 1000;

	जबतक (--limit > 0) अणु
		u64 val = nr64(TX_CS(channel));
		अगर (!(val & TX_CS_RST))
			वापस 0;
	पूर्ण
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक niu_tx_channel_reset(काष्ठा niu *np, पूर्णांक channel)
अणु
	u64 val = nr64(TX_CS(channel));
	पूर्णांक err;

	val |= TX_CS_RST;
	nw64(TX_CS(channel), val);

	err = niu_tx_cs_reset_poll(np, channel);
	अगर (!err)
		nw64(TX_RING_KICK(channel), 0);

	वापस err;
पूर्ण

अटल पूर्णांक niu_tx_channel_lpage_init(काष्ठा niu *np, पूर्णांक channel)
अणु
	u64 val;

	nw64(TX_LOG_MASK1(channel), 0);
	nw64(TX_LOG_VAL1(channel), 0);
	nw64(TX_LOG_MASK2(channel), 0);
	nw64(TX_LOG_VAL2(channel), 0);
	nw64(TX_LOG_PAGE_RELO1(channel), 0);
	nw64(TX_LOG_PAGE_RELO2(channel), 0);
	nw64(TX_LOG_PAGE_HDL(channel), 0);

	val  = (u64)np->port << TX_LOG_PAGE_VLD_FUNC_SHIFT;
	val |= (TX_LOG_PAGE_VLD_PAGE0 | TX_LOG_PAGE_VLD_PAGE1);
	nw64(TX_LOG_PAGE_VLD(channel), val);

	/* XXX TXDMA 32bit mode? XXX */

	वापस 0;
पूर्ण

अटल व्योम niu_txc_enable_port(काष्ठा niu *np, पूर्णांक on)
अणु
	अचिन्हित दीर्घ flags;
	u64 val, mask;

	niu_lock_parent(np, flags);
	val = nr64(TXC_CONTROL);
	mask = (u64)1 << np->port;
	अगर (on) अणु
		val |= TXC_CONTROL_ENABLE | mask;
	पूर्ण अन्यथा अणु
		val &= ~mask;
		अगर ((val & ~TXC_CONTROL_ENABLE) == 0)
			val &= ~TXC_CONTROL_ENABLE;
	पूर्ण
	nw64(TXC_CONTROL, val);
	niu_unlock_parent(np, flags);
पूर्ण

अटल व्योम niu_txc_set_imask(काष्ठा niu *np, u64 imask)
अणु
	अचिन्हित दीर्घ flags;
	u64 val;

	niu_lock_parent(np, flags);
	val = nr64(TXC_INT_MASK);
	val &= ~TXC_INT_MASK_VAL(np->port);
	val |= (imask << TXC_INT_MASK_VAL_SHIFT(np->port));
	niu_unlock_parent(np, flags);
पूर्ण

अटल व्योम niu_txc_port_dma_enable(काष्ठा niu *np, पूर्णांक on)
अणु
	u64 val = 0;

	अगर (on) अणु
		पूर्णांक i;

		क्रम (i = 0; i < np->num_tx_rings; i++)
			val |= (1 << np->tx_rings[i].tx_channel);
	पूर्ण
	nw64(TXC_PORT_DMA(np->port), val);
पूर्ण

अटल पूर्णांक niu_init_one_tx_channel(काष्ठा niu *np, काष्ठा tx_ring_info *rp)
अणु
	पूर्णांक err, channel = rp->tx_channel;
	u64 val, ring_len;

	err = niu_tx_channel_stop(np, channel);
	अगर (err)
		वापस err;

	err = niu_tx_channel_reset(np, channel);
	अगर (err)
		वापस err;

	err = niu_tx_channel_lpage_init(np, channel);
	अगर (err)
		वापस err;

	nw64(TXC_DMA_MAX(channel), rp->max_burst);
	nw64(TX_ENT_MSK(channel), 0);

	अगर (rp->descr_dma & ~(TX_RNG_CFIG_STADDR_BASE |
			      TX_RNG_CFIG_STADDR)) अणु
		netdev_err(np->dev, "TX ring channel %d DMA addr (%llx) is not aligned\n",
			   channel, (अचिन्हित दीर्घ दीर्घ)rp->descr_dma);
		वापस -EINVAL;
	पूर्ण

	/* The length field in TX_RNG_CFIG is measured in 64-byte
	 * blocks.  rp->pending is the number of TX descriptors in
	 * our ring, 8 bytes each, thus we भागide by 8 bytes more
	 * to get the proper value the chip wants.
	 */
	ring_len = (rp->pending / 8);

	val = ((ring_len << TX_RNG_CFIG_LEN_SHIFT) |
	       rp->descr_dma);
	nw64(TX_RNG_CFIG(channel), val);

	अगर (((rp->mbox_dma >> 32) & ~TXDMA_MBH_MBADDR) ||
	    ((u32)rp->mbox_dma & ~TXDMA_MBL_MBADDR)) अणु
		netdev_err(np->dev, "TX ring channel %d MBOX addr (%llx) has invalid bits\n",
			    channel, (अचिन्हित दीर्घ दीर्घ)rp->mbox_dma);
		वापस -EINVAL;
	पूर्ण
	nw64(TXDMA_MBH(channel), rp->mbox_dma >> 32);
	nw64(TXDMA_MBL(channel), rp->mbox_dma & TXDMA_MBL_MBADDR);

	nw64(TX_CS(channel), 0);

	rp->last_pkt_cnt = 0;

	वापस 0;
पूर्ण

अटल व्योम niu_init_rdc_groups(काष्ठा niu *np)
अणु
	काष्ठा niu_rdc_tables *tp = &np->parent->rdc_group_cfg[np->port];
	पूर्णांक i, first_table_num = tp->first_table_num;

	क्रम (i = 0; i < tp->num_tables; i++) अणु
		काष्ठा rdc_table *tbl = &tp->tables[i];
		पूर्णांक this_table = first_table_num + i;
		पूर्णांक slot;

		क्रम (slot = 0; slot < NIU_RDC_TABLE_SLOTS; slot++)
			nw64(RDC_TBL(this_table, slot),
			     tbl->rxdma_channel[slot]);
	पूर्ण

	nw64(DEF_RDC(np->port), np->parent->rdc_शेष[np->port]);
पूर्ण

अटल व्योम niu_init_drr_weight(काष्ठा niu *np)
अणु
	पूर्णांक type = phy_decode(np->parent->port_phy, np->port);
	u64 val;

	चयन (type) अणु
	हाल PORT_TYPE_10G:
		val = PT_DRR_WEIGHT_DEFAULT_10G;
		अवरोध;

	हाल PORT_TYPE_1G:
	शेष:
		val = PT_DRR_WEIGHT_DEFAULT_1G;
		अवरोध;
	पूर्ण
	nw64(PT_DRR_WT(np->port), val);
पूर्ण

अटल पूर्णांक niu_init_hostinfo(काष्ठा niu *np)
अणु
	काष्ठा niu_parent *parent = np->parent;
	काष्ठा niu_rdc_tables *tp = &parent->rdc_group_cfg[np->port];
	पूर्णांक i, err, num_alt = niu_num_alt_addr(np);
	पूर्णांक first_rdc_table = tp->first_table_num;

	err = niu_set_primary_mac_rdc_table(np, first_rdc_table, 1);
	अगर (err)
		वापस err;

	err = niu_set_multicast_mac_rdc_table(np, first_rdc_table, 1);
	अगर (err)
		वापस err;

	क्रम (i = 0; i < num_alt; i++) अणु
		err = niu_set_alt_mac_rdc_table(np, i, first_rdc_table, 1);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक niu_rx_channel_reset(काष्ठा niu *np, पूर्णांक channel)
अणु
	वापस niu_set_and_रुको_clear(np, RXDMA_CFIG1(channel),
				      RXDMA_CFIG1_RST, 1000, 10,
				      "RXDMA_CFIG1");
पूर्ण

अटल पूर्णांक niu_rx_channel_lpage_init(काष्ठा niu *np, पूर्णांक channel)
अणु
	u64 val;

	nw64(RX_LOG_MASK1(channel), 0);
	nw64(RX_LOG_VAL1(channel), 0);
	nw64(RX_LOG_MASK2(channel), 0);
	nw64(RX_LOG_VAL2(channel), 0);
	nw64(RX_LOG_PAGE_RELO1(channel), 0);
	nw64(RX_LOG_PAGE_RELO2(channel), 0);
	nw64(RX_LOG_PAGE_HDL(channel), 0);

	val  = (u64)np->port << RX_LOG_PAGE_VLD_FUNC_SHIFT;
	val |= (RX_LOG_PAGE_VLD_PAGE0 | RX_LOG_PAGE_VLD_PAGE1);
	nw64(RX_LOG_PAGE_VLD(channel), val);

	वापस 0;
पूर्ण

अटल व्योम niu_rx_channel_wred_init(काष्ठा niu *np, काष्ठा rx_ring_info *rp)
अणु
	u64 val;

	val = (((u64)rp->nonsyn_winकरोw << RDC_RED_PARA_WIN_SHIFT) |
	       ((u64)rp->nonsyn_threshold << RDC_RED_PARA_THRE_SHIFT) |
	       ((u64)rp->syn_winकरोw << RDC_RED_PARA_WIN_SYN_SHIFT) |
	       ((u64)rp->syn_threshold << RDC_RED_PARA_THRE_SYN_SHIFT));
	nw64(RDC_RED_PARA(rp->rx_channel), val);
पूर्ण

अटल पूर्णांक niu_compute_rbr_cfig_b(काष्ठा rx_ring_info *rp, u64 *ret)
अणु
	u64 val = 0;

	*ret = 0;
	चयन (rp->rbr_block_size) अणु
	हाल 4 * 1024:
		val |= (RBR_BLKSIZE_4K << RBR_CFIG_B_BLKSIZE_SHIFT);
		अवरोध;
	हाल 8 * 1024:
		val |= (RBR_BLKSIZE_8K << RBR_CFIG_B_BLKSIZE_SHIFT);
		अवरोध;
	हाल 16 * 1024:
		val |= (RBR_BLKSIZE_16K << RBR_CFIG_B_BLKSIZE_SHIFT);
		अवरोध;
	हाल 32 * 1024:
		val |= (RBR_BLKSIZE_32K << RBR_CFIG_B_BLKSIZE_SHIFT);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	val |= RBR_CFIG_B_VLD2;
	चयन (rp->rbr_sizes[2]) अणु
	हाल 2 * 1024:
		val |= (RBR_BUFSZ2_2K << RBR_CFIG_B_BUFSZ2_SHIFT);
		अवरोध;
	हाल 4 * 1024:
		val |= (RBR_BUFSZ2_4K << RBR_CFIG_B_BUFSZ2_SHIFT);
		अवरोध;
	हाल 8 * 1024:
		val |= (RBR_BUFSZ2_8K << RBR_CFIG_B_BUFSZ2_SHIFT);
		अवरोध;
	हाल 16 * 1024:
		val |= (RBR_BUFSZ2_16K << RBR_CFIG_B_BUFSZ2_SHIFT);
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण
	val |= RBR_CFIG_B_VLD1;
	चयन (rp->rbr_sizes[1]) अणु
	हाल 1 * 1024:
		val |= (RBR_BUFSZ1_1K << RBR_CFIG_B_BUFSZ1_SHIFT);
		अवरोध;
	हाल 2 * 1024:
		val |= (RBR_BUFSZ1_2K << RBR_CFIG_B_BUFSZ1_SHIFT);
		अवरोध;
	हाल 4 * 1024:
		val |= (RBR_BUFSZ1_4K << RBR_CFIG_B_BUFSZ1_SHIFT);
		अवरोध;
	हाल 8 * 1024:
		val |= (RBR_BUFSZ1_8K << RBR_CFIG_B_BUFSZ1_SHIFT);
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण
	val |= RBR_CFIG_B_VLD0;
	चयन (rp->rbr_sizes[0]) अणु
	हाल 256:
		val |= (RBR_BUFSZ0_256 << RBR_CFIG_B_BUFSZ0_SHIFT);
		अवरोध;
	हाल 512:
		val |= (RBR_BUFSZ0_512 << RBR_CFIG_B_BUFSZ0_SHIFT);
		अवरोध;
	हाल 1 * 1024:
		val |= (RBR_BUFSZ0_1K << RBR_CFIG_B_BUFSZ0_SHIFT);
		अवरोध;
	हाल 2 * 1024:
		val |= (RBR_BUFSZ0_2K << RBR_CFIG_B_BUFSZ0_SHIFT);
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	*ret = val;
	वापस 0;
पूर्ण

अटल पूर्णांक niu_enable_rx_channel(काष्ठा niu *np, पूर्णांक channel, पूर्णांक on)
अणु
	u64 val = nr64(RXDMA_CFIG1(channel));
	पूर्णांक limit;

	अगर (on)
		val |= RXDMA_CFIG1_EN;
	अन्यथा
		val &= ~RXDMA_CFIG1_EN;
	nw64(RXDMA_CFIG1(channel), val);

	limit = 1000;
	जबतक (--limit > 0) अणु
		अगर (nr64(RXDMA_CFIG1(channel)) & RXDMA_CFIG1_QST)
			अवरोध;
		udelay(10);
	पूर्ण
	अगर (limit <= 0)
		वापस -ENODEV;
	वापस 0;
पूर्ण

अटल पूर्णांक niu_init_one_rx_channel(काष्ठा niu *np, काष्ठा rx_ring_info *rp)
अणु
	पूर्णांक err, channel = rp->rx_channel;
	u64 val;

	err = niu_rx_channel_reset(np, channel);
	अगर (err)
		वापस err;

	err = niu_rx_channel_lpage_init(np, channel);
	अगर (err)
		वापस err;

	niu_rx_channel_wred_init(np, rp);

	nw64(RX_DMA_ENT_MSK(channel), RX_DMA_ENT_MSK_RBR_EMPTY);
	nw64(RX_DMA_CTL_STAT(channel),
	     (RX_DMA_CTL_STAT_MEX |
	      RX_DMA_CTL_STAT_RCRTHRES |
	      RX_DMA_CTL_STAT_RCRTO |
	      RX_DMA_CTL_STAT_RBR_EMPTY));
	nw64(RXDMA_CFIG1(channel), rp->mbox_dma >> 32);
	nw64(RXDMA_CFIG2(channel),
	     ((rp->mbox_dma & RXDMA_CFIG2_MBADDR_L) |
	      RXDMA_CFIG2_FULL_HDR));
	nw64(RBR_CFIG_A(channel),
	     ((u64)rp->rbr_table_size << RBR_CFIG_A_LEN_SHIFT) |
	     (rp->rbr_dma & (RBR_CFIG_A_STADDR_BASE | RBR_CFIG_A_STADDR)));
	err = niu_compute_rbr_cfig_b(rp, &val);
	अगर (err)
		वापस err;
	nw64(RBR_CFIG_B(channel), val);
	nw64(RCRCFIG_A(channel),
	     ((u64)rp->rcr_table_size << RCRCFIG_A_LEN_SHIFT) |
	     (rp->rcr_dma & (RCRCFIG_A_STADDR_BASE | RCRCFIG_A_STADDR)));
	nw64(RCRCFIG_B(channel),
	     ((u64)rp->rcr_pkt_threshold << RCRCFIG_B_PTHRES_SHIFT) |
	     RCRCFIG_B_ENTOUT |
	     ((u64)rp->rcr_समयout << RCRCFIG_B_TIMEOUT_SHIFT));

	err = niu_enable_rx_channel(np, channel, 1);
	अगर (err)
		वापस err;

	nw64(RBR_KICK(channel), rp->rbr_index);

	val = nr64(RX_DMA_CTL_STAT(channel));
	val |= RX_DMA_CTL_STAT_RBR_EMPTY;
	nw64(RX_DMA_CTL_STAT(channel), val);

	वापस 0;
पूर्ण

अटल पूर्णांक niu_init_rx_channels(काष्ठा niu *np)
अणु
	अचिन्हित दीर्घ flags;
	u64 seed = jअगरfies_64;
	पूर्णांक err, i;

	niu_lock_parent(np, flags);
	nw64(RX_DMA_CK_DIV, np->parent->rxdma_घड़ी_भागider);
	nw64(RED_RAN_INIT, RED_RAN_INIT_OPMODE | (seed & RED_RAN_INIT_VAL));
	niu_unlock_parent(np, flags);

	/* XXX RXDMA 32bit mode? XXX */

	niu_init_rdc_groups(np);
	niu_init_drr_weight(np);

	err = niu_init_hostinfo(np);
	अगर (err)
		वापस err;

	क्रम (i = 0; i < np->num_rx_rings; i++) अणु
		काष्ठा rx_ring_info *rp = &np->rx_rings[i];

		err = niu_init_one_rx_channel(np, rp);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक niu_set_ip_frag_rule(काष्ठा niu *np)
अणु
	काष्ठा niu_parent *parent = np->parent;
	काष्ठा niu_classअगरier *cp = &np->clas;
	काष्ठा niu_tcam_entry *tp;
	पूर्णांक index, err;

	index = cp->tcam_top;
	tp = &parent->tcam[index];

	/* Note that the noport bit is the same in both ipv4 and
	 * ipv6 क्रमmat TCAM entries.
	 */
	स_रखो(tp, 0, माप(*tp));
	tp->key[1] = TCAM_V4KEY1_NOPORT;
	tp->key_mask[1] = TCAM_V4KEY1_NOPORT;
	tp->assoc_data = (TCAM_ASSOCDATA_TRES_USE_OFFSET |
			  ((u64)0 << TCAM_ASSOCDATA_OFFSET_SHIFT));
	err = tcam_ग_लिखो(np, index, tp->key, tp->key_mask);
	अगर (err)
		वापस err;
	err = tcam_assoc_ग_लिखो(np, index, tp->assoc_data);
	अगर (err)
		वापस err;
	tp->valid = 1;
	cp->tcam_valid_entries++;

	वापस 0;
पूर्ण

अटल पूर्णांक niu_init_classअगरier_hw(काष्ठा niu *np)
अणु
	काष्ठा niu_parent *parent = np->parent;
	काष्ठा niu_classअगरier *cp = &np->clas;
	पूर्णांक i, err;

	nw64(H1POLY, cp->h1_init);
	nw64(H2POLY, cp->h2_init);

	err = niu_init_hostinfo(np);
	अगर (err)
		वापस err;

	क्रम (i = 0; i < ENET_VLAN_TBL_NUM_ENTRIES; i++) अणु
		काष्ठा niu_vlan_rdc *vp = &cp->vlan_mappings[i];

		vlan_tbl_ग_लिखो(np, i, np->port,
			       vp->vlan_pref, vp->rdc_num);
	पूर्ण

	क्रम (i = 0; i < cp->num_alt_mac_mappings; i++) अणु
		काष्ठा niu_alपंचांगac_rdc *ap = &cp->alt_mac_mappings[i];

		err = niu_set_alt_mac_rdc_table(np, ap->alt_mac_num,
						ap->rdc_num, ap->mac_pref);
		अगर (err)
			वापस err;
	पूर्ण

	क्रम (i = CLASS_CODE_USER_PROG1; i <= CLASS_CODE_SCTP_IPV6; i++) अणु
		पूर्णांक index = i - CLASS_CODE_USER_PROG1;

		err = niu_set_tcam_key(np, i, parent->tcam_key[index]);
		अगर (err)
			वापस err;
		err = niu_set_flow_key(np, i, parent->flow_key[index]);
		अगर (err)
			वापस err;
	पूर्ण

	err = niu_set_ip_frag_rule(np);
	अगर (err)
		वापस err;

	tcam_enable(np, 1);

	वापस 0;
पूर्ण

अटल पूर्णांक niu_zcp_ग_लिखो(काष्ठा niu *np, पूर्णांक index, u64 *data)
अणु
	nw64(ZCP_RAM_DATA0, data[0]);
	nw64(ZCP_RAM_DATA1, data[1]);
	nw64(ZCP_RAM_DATA2, data[2]);
	nw64(ZCP_RAM_DATA3, data[3]);
	nw64(ZCP_RAM_DATA4, data[4]);
	nw64(ZCP_RAM_BE, ZCP_RAM_BE_VAL);
	nw64(ZCP_RAM_ACC,
	     (ZCP_RAM_ACC_WRITE |
	      (0 << ZCP_RAM_ACC_ZFCID_SHIFT) |
	      (ZCP_RAM_SEL_CFIFO(np->port) << ZCP_RAM_ACC_RAM_SEL_SHIFT)));

	वापस niu_रुको_bits_clear(np, ZCP_RAM_ACC, ZCP_RAM_ACC_BUSY,
				   1000, 100);
पूर्ण

अटल पूर्णांक niu_zcp_पढ़ो(काष्ठा niu *np, पूर्णांक index, u64 *data)
अणु
	पूर्णांक err;

	err = niu_रुको_bits_clear(np, ZCP_RAM_ACC, ZCP_RAM_ACC_BUSY,
				  1000, 100);
	अगर (err) अणु
		netdev_err(np->dev, "ZCP read busy won't clear, ZCP_RAM_ACC[%llx]\n",
			   (अचिन्हित दीर्घ दीर्घ)nr64(ZCP_RAM_ACC));
		वापस err;
	पूर्ण

	nw64(ZCP_RAM_ACC,
	     (ZCP_RAM_ACC_READ |
	      (0 << ZCP_RAM_ACC_ZFCID_SHIFT) |
	      (ZCP_RAM_SEL_CFIFO(np->port) << ZCP_RAM_ACC_RAM_SEL_SHIFT)));

	err = niu_रुको_bits_clear(np, ZCP_RAM_ACC, ZCP_RAM_ACC_BUSY,
				  1000, 100);
	अगर (err) अणु
		netdev_err(np->dev, "ZCP read busy2 won't clear, ZCP_RAM_ACC[%llx]\n",
			   (अचिन्हित दीर्घ दीर्घ)nr64(ZCP_RAM_ACC));
		वापस err;
	पूर्ण

	data[0] = nr64(ZCP_RAM_DATA0);
	data[1] = nr64(ZCP_RAM_DATA1);
	data[2] = nr64(ZCP_RAM_DATA2);
	data[3] = nr64(ZCP_RAM_DATA3);
	data[4] = nr64(ZCP_RAM_DATA4);

	वापस 0;
पूर्ण

अटल व्योम niu_zcp_cfअगरo_reset(काष्ठा niu *np)
अणु
	u64 val = nr64(RESET_CFIFO);

	val |= RESET_CFIFO_RST(np->port);
	nw64(RESET_CFIFO, val);
	udelay(10);

	val &= ~RESET_CFIFO_RST(np->port);
	nw64(RESET_CFIFO, val);
पूर्ण

अटल पूर्णांक niu_init_zcp(काष्ठा niu *np)
अणु
	u64 data[5], rbuf[5];
	पूर्णांक i, max, err;

	अगर (np->parent->plat_type != PLAT_TYPE_NIU) अणु
		अगर (np->port == 0 || np->port == 1)
			max = ATLAS_P0_P1_CFIFO_ENTRIES;
		अन्यथा
			max = ATLAS_P2_P3_CFIFO_ENTRIES;
	पूर्ण अन्यथा
		max = NIU_CFIFO_ENTRIES;

	data[0] = 0;
	data[1] = 0;
	data[2] = 0;
	data[3] = 0;
	data[4] = 0;

	क्रम (i = 0; i < max; i++) अणु
		err = niu_zcp_ग_लिखो(np, i, data);
		अगर (err)
			वापस err;
		err = niu_zcp_पढ़ो(np, i, rbuf);
		अगर (err)
			वापस err;
	पूर्ण

	niu_zcp_cfअगरo_reset(np);
	nw64(CFIFO_ECC(np->port), 0);
	nw64(ZCP_INT_STAT, ZCP_INT_STAT_ALL);
	(व्योम) nr64(ZCP_INT_STAT);
	nw64(ZCP_INT_MASK, ZCP_INT_MASK_ALL);

	वापस 0;
पूर्ण

अटल व्योम niu_ipp_ग_लिखो(काष्ठा niu *np, पूर्णांक index, u64 *data)
अणु
	u64 val = nr64_ipp(IPP_CFIG);

	nw64_ipp(IPP_CFIG, val | IPP_CFIG_DFIFO_PIO_W);
	nw64_ipp(IPP_DFIFO_WR_PTR, index);
	nw64_ipp(IPP_DFIFO_WR0, data[0]);
	nw64_ipp(IPP_DFIFO_WR1, data[1]);
	nw64_ipp(IPP_DFIFO_WR2, data[2]);
	nw64_ipp(IPP_DFIFO_WR3, data[3]);
	nw64_ipp(IPP_DFIFO_WR4, data[4]);
	nw64_ipp(IPP_CFIG, val & ~IPP_CFIG_DFIFO_PIO_W);
पूर्ण

अटल व्योम niu_ipp_पढ़ो(काष्ठा niu *np, पूर्णांक index, u64 *data)
अणु
	nw64_ipp(IPP_DFIFO_RD_PTR, index);
	data[0] = nr64_ipp(IPP_DFIFO_RD0);
	data[1] = nr64_ipp(IPP_DFIFO_RD1);
	data[2] = nr64_ipp(IPP_DFIFO_RD2);
	data[3] = nr64_ipp(IPP_DFIFO_RD3);
	data[4] = nr64_ipp(IPP_DFIFO_RD4);
पूर्ण

अटल पूर्णांक niu_ipp_reset(काष्ठा niu *np)
अणु
	वापस niu_set_and_रुको_clear_ipp(np, IPP_CFIG, IPP_CFIG_SOFT_RST,
					  1000, 100, "IPP_CFIG");
पूर्ण

अटल पूर्णांक niu_init_ipp(काष्ठा niu *np)
अणु
	u64 data[5], rbuf[5], val;
	पूर्णांक i, max, err;

	अगर (np->parent->plat_type != PLAT_TYPE_NIU) अणु
		अगर (np->port == 0 || np->port == 1)
			max = ATLAS_P0_P1_DFIFO_ENTRIES;
		अन्यथा
			max = ATLAS_P2_P3_DFIFO_ENTRIES;
	पूर्ण अन्यथा
		max = NIU_DFIFO_ENTRIES;

	data[0] = 0;
	data[1] = 0;
	data[2] = 0;
	data[3] = 0;
	data[4] = 0;

	क्रम (i = 0; i < max; i++) अणु
		niu_ipp_ग_लिखो(np, i, data);
		niu_ipp_पढ़ो(np, i, rbuf);
	पूर्ण

	(व्योम) nr64_ipp(IPP_INT_STAT);
	(व्योम) nr64_ipp(IPP_INT_STAT);

	err = niu_ipp_reset(np);
	अगर (err)
		वापस err;

	(व्योम) nr64_ipp(IPP_PKT_DIS);
	(व्योम) nr64_ipp(IPP_BAD_CS_CNT);
	(व्योम) nr64_ipp(IPP_ECC);

	(व्योम) nr64_ipp(IPP_INT_STAT);

	nw64_ipp(IPP_MSK, ~IPP_MSK_ALL);

	val = nr64_ipp(IPP_CFIG);
	val &= ~IPP_CFIG_IP_MAX_PKT;
	val |= (IPP_CFIG_IPP_ENABLE |
		IPP_CFIG_DFIFO_ECC_EN |
		IPP_CFIG_DROP_BAD_CRC |
		IPP_CFIG_CKSUM_EN |
		(0x1ffff << IPP_CFIG_IP_MAX_PKT_SHIFT));
	nw64_ipp(IPP_CFIG, val);

	वापस 0;
पूर्ण

अटल व्योम niu_handle_led(काष्ठा niu *np, पूर्णांक status)
अणु
	u64 val;
	val = nr64_mac(XMAC_CONFIG);

	अगर ((np->flags & NIU_FLAGS_10G) != 0 &&
	    (np->flags & NIU_FLAGS_FIBER) != 0) अणु
		अगर (status) अणु
			val |= XMAC_CONFIG_LED_POLARITY;
			val &= ~XMAC_CONFIG_FORCE_LED_ON;
		पूर्ण अन्यथा अणु
			val |= XMAC_CONFIG_FORCE_LED_ON;
			val &= ~XMAC_CONFIG_LED_POLARITY;
		पूर्ण
	पूर्ण

	nw64_mac(XMAC_CONFIG, val);
पूर्ण

अटल व्योम niu_init_xअगर_xmac(काष्ठा niu *np)
अणु
	काष्ठा niu_link_config *lp = &np->link_config;
	u64 val;

	अगर (np->flags & NIU_FLAGS_XCVR_SERDES) अणु
		val = nr64(MIF_CONFIG);
		val |= MIF_CONFIG_ATCA_GE;
		nw64(MIF_CONFIG, val);
	पूर्ण

	val = nr64_mac(XMAC_CONFIG);
	val &= ~XMAC_CONFIG_SEL_POR_CLK_SRC;

	val |= XMAC_CONFIG_TX_OUTPUT_EN;

	अगर (lp->loopback_mode == LOOPBACK_MAC) अणु
		val &= ~XMAC_CONFIG_SEL_POR_CLK_SRC;
		val |= XMAC_CONFIG_LOOPBACK;
	पूर्ण अन्यथा अणु
		val &= ~XMAC_CONFIG_LOOPBACK;
	पूर्ण

	अगर (np->flags & NIU_FLAGS_10G) अणु
		val &= ~XMAC_CONFIG_LFS_DISABLE;
	पूर्ण अन्यथा अणु
		val |= XMAC_CONFIG_LFS_DISABLE;
		अगर (!(np->flags & NIU_FLAGS_FIBER) &&
		    !(np->flags & NIU_FLAGS_XCVR_SERDES))
			val |= XMAC_CONFIG_1G_PCS_BYPASS;
		अन्यथा
			val &= ~XMAC_CONFIG_1G_PCS_BYPASS;
	पूर्ण

	val &= ~XMAC_CONFIG_10G_XPCS_BYPASS;

	अगर (lp->active_speed == SPEED_100)
		val |= XMAC_CONFIG_SEL_CLK_25MHZ;
	अन्यथा
		val &= ~XMAC_CONFIG_SEL_CLK_25MHZ;

	nw64_mac(XMAC_CONFIG, val);

	val = nr64_mac(XMAC_CONFIG);
	val &= ~XMAC_CONFIG_MODE_MASK;
	अगर (np->flags & NIU_FLAGS_10G) अणु
		val |= XMAC_CONFIG_MODE_XGMII;
	पूर्ण अन्यथा अणु
		अगर (lp->active_speed == SPEED_1000)
			val |= XMAC_CONFIG_MODE_GMII;
		अन्यथा
			val |= XMAC_CONFIG_MODE_MII;
	पूर्ण

	nw64_mac(XMAC_CONFIG, val);
पूर्ण

अटल व्योम niu_init_xअगर_bmac(काष्ठा niu *np)
अणु
	काष्ठा niu_link_config *lp = &np->link_config;
	u64 val;

	val = BMAC_XIF_CONFIG_TX_OUTPUT_EN;

	अगर (lp->loopback_mode == LOOPBACK_MAC)
		val |= BMAC_XIF_CONFIG_MII_LOOPBACK;
	अन्यथा
		val &= ~BMAC_XIF_CONFIG_MII_LOOPBACK;

	अगर (lp->active_speed == SPEED_1000)
		val |= BMAC_XIF_CONFIG_GMII_MODE;
	अन्यथा
		val &= ~BMAC_XIF_CONFIG_GMII_MODE;

	val &= ~(BMAC_XIF_CONFIG_LINK_LED |
		 BMAC_XIF_CONFIG_LED_POLARITY);

	अगर (!(np->flags & NIU_FLAGS_10G) &&
	    !(np->flags & NIU_FLAGS_FIBER) &&
	    lp->active_speed == SPEED_100)
		val |= BMAC_XIF_CONFIG_25MHZ_CLOCK;
	अन्यथा
		val &= ~BMAC_XIF_CONFIG_25MHZ_CLOCK;

	nw64_mac(BMAC_XIF_CONFIG, val);
पूर्ण

अटल व्योम niu_init_xअगर(काष्ठा niu *np)
अणु
	अगर (np->flags & NIU_FLAGS_XMAC)
		niu_init_xअगर_xmac(np);
	अन्यथा
		niu_init_xअगर_bmac(np);
पूर्ण

अटल व्योम niu_pcs_mii_reset(काष्ठा niu *np)
अणु
	पूर्णांक limit = 1000;
	u64 val = nr64_pcs(PCS_MII_CTL);
	val |= PCS_MII_CTL_RST;
	nw64_pcs(PCS_MII_CTL, val);
	जबतक ((--limit >= 0) && (val & PCS_MII_CTL_RST)) अणु
		udelay(100);
		val = nr64_pcs(PCS_MII_CTL);
	पूर्ण
पूर्ण

अटल व्योम niu_xpcs_reset(काष्ठा niu *np)
अणु
	पूर्णांक limit = 1000;
	u64 val = nr64_xpcs(XPCS_CONTROL1);
	val |= XPCS_CONTROL1_RESET;
	nw64_xpcs(XPCS_CONTROL1, val);
	जबतक ((--limit >= 0) && (val & XPCS_CONTROL1_RESET)) अणु
		udelay(100);
		val = nr64_xpcs(XPCS_CONTROL1);
	पूर्ण
पूर्ण

अटल पूर्णांक niu_init_pcs(काष्ठा niu *np)
अणु
	काष्ठा niu_link_config *lp = &np->link_config;
	u64 val;

	चयन (np->flags & (NIU_FLAGS_10G |
			     NIU_FLAGS_FIBER |
			     NIU_FLAGS_XCVR_SERDES)) अणु
	हाल NIU_FLAGS_FIBER:
		/* 1G fiber */
		nw64_pcs(PCS_CONF, PCS_CONF_MASK | PCS_CONF_ENABLE);
		nw64_pcs(PCS_DPATH_MODE, 0);
		niu_pcs_mii_reset(np);
		अवरोध;

	हाल NIU_FLAGS_10G:
	हाल NIU_FLAGS_10G | NIU_FLAGS_FIBER:
	हाल NIU_FLAGS_10G | NIU_FLAGS_XCVR_SERDES:
		/* 10G SERDES */
		अगर (!(np->flags & NIU_FLAGS_XMAC))
			वापस -EINVAL;

		/* 10G copper or fiber */
		val = nr64_mac(XMAC_CONFIG);
		val &= ~XMAC_CONFIG_10G_XPCS_BYPASS;
		nw64_mac(XMAC_CONFIG, val);

		niu_xpcs_reset(np);

		val = nr64_xpcs(XPCS_CONTROL1);
		अगर (lp->loopback_mode == LOOPBACK_PHY)
			val |= XPCS_CONTROL1_LOOPBACK;
		अन्यथा
			val &= ~XPCS_CONTROL1_LOOPBACK;
		nw64_xpcs(XPCS_CONTROL1, val);

		nw64_xpcs(XPCS_DESKEW_ERR_CNT, 0);
		(व्योम) nr64_xpcs(XPCS_SYMERR_CNT01);
		(व्योम) nr64_xpcs(XPCS_SYMERR_CNT23);
		अवरोध;


	हाल NIU_FLAGS_XCVR_SERDES:
		/* 1G SERDES */
		niu_pcs_mii_reset(np);
		nw64_pcs(PCS_CONF, PCS_CONF_MASK | PCS_CONF_ENABLE);
		nw64_pcs(PCS_DPATH_MODE, 0);
		अवरोध;

	हाल 0:
		/* 1G copper */
	हाल NIU_FLAGS_XCVR_SERDES | NIU_FLAGS_FIBER:
		/* 1G RGMII FIBER */
		nw64_pcs(PCS_DPATH_MODE, PCS_DPATH_MODE_MII);
		niu_pcs_mii_reset(np);
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक niu_reset_tx_xmac(काष्ठा niu *np)
अणु
	वापस niu_set_and_रुको_clear_mac(np, XTXMAC_SW_RST,
					  (XTXMAC_SW_RST_REG_RS |
					   XTXMAC_SW_RST_SOFT_RST),
					  1000, 100, "XTXMAC_SW_RST");
पूर्ण

अटल पूर्णांक niu_reset_tx_bmac(काष्ठा niu *np)
अणु
	पूर्णांक limit;

	nw64_mac(BTXMAC_SW_RST, BTXMAC_SW_RST_RESET);
	limit = 1000;
	जबतक (--limit >= 0) अणु
		अगर (!(nr64_mac(BTXMAC_SW_RST) & BTXMAC_SW_RST_RESET))
			अवरोध;
		udelay(100);
	पूर्ण
	अगर (limit < 0) अणु
		dev_err(np->device, "Port %u TX BMAC would not reset, BTXMAC_SW_RST[%llx]\n",
			np->port,
			(अचिन्हित दीर्घ दीर्घ) nr64_mac(BTXMAC_SW_RST));
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक niu_reset_tx_mac(काष्ठा niu *np)
अणु
	अगर (np->flags & NIU_FLAGS_XMAC)
		वापस niu_reset_tx_xmac(np);
	अन्यथा
		वापस niu_reset_tx_bmac(np);
पूर्ण

अटल व्योम niu_init_tx_xmac(काष्ठा niu *np, u64 min, u64 max)
अणु
	u64 val;

	val = nr64_mac(XMAC_MIN);
	val &= ~(XMAC_MIN_TX_MIN_PKT_SIZE |
		 XMAC_MIN_RX_MIN_PKT_SIZE);
	val |= (min << XMAC_MIN_RX_MIN_PKT_SIZE_SHFT);
	val |= (min << XMAC_MIN_TX_MIN_PKT_SIZE_SHFT);
	nw64_mac(XMAC_MIN, val);

	nw64_mac(XMAC_MAX, max);

	nw64_mac(XTXMAC_STAT_MSK, ~(u64)0);

	val = nr64_mac(XMAC_IPG);
	अगर (np->flags & NIU_FLAGS_10G) अणु
		val &= ~XMAC_IPG_IPG_XGMII;
		val |= (IPG_12_15_XGMII << XMAC_IPG_IPG_XGMII_SHIFT);
	पूर्ण अन्यथा अणु
		val &= ~XMAC_IPG_IPG_MII_GMII;
		val |= (IPG_12_MII_GMII << XMAC_IPG_IPG_MII_GMII_SHIFT);
	पूर्ण
	nw64_mac(XMAC_IPG, val);

	val = nr64_mac(XMAC_CONFIG);
	val &= ~(XMAC_CONFIG_ALWAYS_NO_CRC |
		 XMAC_CONFIG_STRETCH_MODE |
		 XMAC_CONFIG_VAR_MIN_IPG_EN |
		 XMAC_CONFIG_TX_ENABLE);
	nw64_mac(XMAC_CONFIG, val);

	nw64_mac(TXMAC_FRM_CNT, 0);
	nw64_mac(TXMAC_BYTE_CNT, 0);
पूर्ण

अटल व्योम niu_init_tx_bmac(काष्ठा niu *np, u64 min, u64 max)
अणु
	u64 val;

	nw64_mac(BMAC_MIN_FRAME, min);
	nw64_mac(BMAC_MAX_FRAME, max);

	nw64_mac(BTXMAC_STATUS_MASK, ~(u64)0);
	nw64_mac(BMAC_CTRL_TYPE, 0x8808);
	nw64_mac(BMAC_PREAMBLE_SIZE, 7);

	val = nr64_mac(BTXMAC_CONFIG);
	val &= ~(BTXMAC_CONFIG_FCS_DISABLE |
		 BTXMAC_CONFIG_ENABLE);
	nw64_mac(BTXMAC_CONFIG, val);
पूर्ण

अटल व्योम niu_init_tx_mac(काष्ठा niu *np)
अणु
	u64 min, max;

	min = 64;
	अगर (np->dev->mtu > ETH_DATA_LEN)
		max = 9216;
	अन्यथा
		max = 1522;

	/* The XMAC_MIN रेजिस्टर only accepts values क्रम TX min which
	 * have the low 3 bits cleared.
	 */
	BUG_ON(min & 0x7);

	अगर (np->flags & NIU_FLAGS_XMAC)
		niu_init_tx_xmac(np, min, max);
	अन्यथा
		niu_init_tx_bmac(np, min, max);
पूर्ण

अटल पूर्णांक niu_reset_rx_xmac(काष्ठा niu *np)
अणु
	पूर्णांक limit;

	nw64_mac(XRXMAC_SW_RST,
		 XRXMAC_SW_RST_REG_RS | XRXMAC_SW_RST_SOFT_RST);
	limit = 1000;
	जबतक (--limit >= 0) अणु
		अगर (!(nr64_mac(XRXMAC_SW_RST) & (XRXMAC_SW_RST_REG_RS |
						 XRXMAC_SW_RST_SOFT_RST)))
			अवरोध;
		udelay(100);
	पूर्ण
	अगर (limit < 0) अणु
		dev_err(np->device, "Port %u RX XMAC would not reset, XRXMAC_SW_RST[%llx]\n",
			np->port,
			(अचिन्हित दीर्घ दीर्घ) nr64_mac(XRXMAC_SW_RST));
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक niu_reset_rx_bmac(काष्ठा niu *np)
अणु
	पूर्णांक limit;

	nw64_mac(BRXMAC_SW_RST, BRXMAC_SW_RST_RESET);
	limit = 1000;
	जबतक (--limit >= 0) अणु
		अगर (!(nr64_mac(BRXMAC_SW_RST) & BRXMAC_SW_RST_RESET))
			अवरोध;
		udelay(100);
	पूर्ण
	अगर (limit < 0) अणु
		dev_err(np->device, "Port %u RX BMAC would not reset, BRXMAC_SW_RST[%llx]\n",
			np->port,
			(अचिन्हित दीर्घ दीर्घ) nr64_mac(BRXMAC_SW_RST));
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक niu_reset_rx_mac(काष्ठा niu *np)
अणु
	अगर (np->flags & NIU_FLAGS_XMAC)
		वापस niu_reset_rx_xmac(np);
	अन्यथा
		वापस niu_reset_rx_bmac(np);
पूर्ण

अटल व्योम niu_init_rx_xmac(काष्ठा niu *np)
अणु
	काष्ठा niu_parent *parent = np->parent;
	काष्ठा niu_rdc_tables *tp = &parent->rdc_group_cfg[np->port];
	पूर्णांक first_rdc_table = tp->first_table_num;
	अचिन्हित दीर्घ i;
	u64 val;

	nw64_mac(XMAC_ADD_FILT0, 0);
	nw64_mac(XMAC_ADD_FILT1, 0);
	nw64_mac(XMAC_ADD_FILT2, 0);
	nw64_mac(XMAC_ADD_FILT12_MASK, 0);
	nw64_mac(XMAC_ADD_FILT00_MASK, 0);
	क्रम (i = 0; i < MAC_NUM_HASH; i++)
		nw64_mac(XMAC_HASH_TBL(i), 0);
	nw64_mac(XRXMAC_STAT_MSK, ~(u64)0);
	niu_set_primary_mac_rdc_table(np, first_rdc_table, 1);
	niu_set_multicast_mac_rdc_table(np, first_rdc_table, 1);

	val = nr64_mac(XMAC_CONFIG);
	val &= ~(XMAC_CONFIG_RX_MAC_ENABLE |
		 XMAC_CONFIG_PROMISCUOUS |
		 XMAC_CONFIG_PROMISC_GROUP |
		 XMAC_CONFIG_ERR_CHK_DIS |
		 XMAC_CONFIG_RX_CRC_CHK_DIS |
		 XMAC_CONFIG_RESERVED_MULTICAST |
		 XMAC_CONFIG_RX_CODEV_CHK_DIS |
		 XMAC_CONFIG_ADDR_FILTER_EN |
		 XMAC_CONFIG_RCV_PAUSE_ENABLE |
		 XMAC_CONFIG_STRIP_CRC |
		 XMAC_CONFIG_PASS_FLOW_CTRL |
		 XMAC_CONFIG_MAC2IPP_PKT_CNT_EN);
	val |= (XMAC_CONFIG_HASH_FILTER_EN);
	nw64_mac(XMAC_CONFIG, val);

	nw64_mac(RXMAC_BT_CNT, 0);
	nw64_mac(RXMAC_BC_FRM_CNT, 0);
	nw64_mac(RXMAC_MC_FRM_CNT, 0);
	nw64_mac(RXMAC_FRAG_CNT, 0);
	nw64_mac(RXMAC_HIST_CNT1, 0);
	nw64_mac(RXMAC_HIST_CNT2, 0);
	nw64_mac(RXMAC_HIST_CNT3, 0);
	nw64_mac(RXMAC_HIST_CNT4, 0);
	nw64_mac(RXMAC_HIST_CNT5, 0);
	nw64_mac(RXMAC_HIST_CNT6, 0);
	nw64_mac(RXMAC_HIST_CNT7, 0);
	nw64_mac(RXMAC_MPSZER_CNT, 0);
	nw64_mac(RXMAC_CRC_ER_CNT, 0);
	nw64_mac(RXMAC_CD_VIO_CNT, 0);
	nw64_mac(LINK_FAULT_CNT, 0);
पूर्ण

अटल व्योम niu_init_rx_bmac(काष्ठा niu *np)
अणु
	काष्ठा niu_parent *parent = np->parent;
	काष्ठा niu_rdc_tables *tp = &parent->rdc_group_cfg[np->port];
	पूर्णांक first_rdc_table = tp->first_table_num;
	अचिन्हित दीर्घ i;
	u64 val;

	nw64_mac(BMAC_ADD_FILT0, 0);
	nw64_mac(BMAC_ADD_FILT1, 0);
	nw64_mac(BMAC_ADD_FILT2, 0);
	nw64_mac(BMAC_ADD_FILT12_MASK, 0);
	nw64_mac(BMAC_ADD_FILT00_MASK, 0);
	क्रम (i = 0; i < MAC_NUM_HASH; i++)
		nw64_mac(BMAC_HASH_TBL(i), 0);
	niu_set_primary_mac_rdc_table(np, first_rdc_table, 1);
	niu_set_multicast_mac_rdc_table(np, first_rdc_table, 1);
	nw64_mac(BRXMAC_STATUS_MASK, ~(u64)0);

	val = nr64_mac(BRXMAC_CONFIG);
	val &= ~(BRXMAC_CONFIG_ENABLE |
		 BRXMAC_CONFIG_STRIP_PAD |
		 BRXMAC_CONFIG_STRIP_FCS |
		 BRXMAC_CONFIG_PROMISC |
		 BRXMAC_CONFIG_PROMISC_GRP |
		 BRXMAC_CONFIG_ADDR_FILT_EN |
		 BRXMAC_CONFIG_DISCARD_DIS);
	val |= (BRXMAC_CONFIG_HASH_FILT_EN);
	nw64_mac(BRXMAC_CONFIG, val);

	val = nr64_mac(BMAC_ADDR_CMPEN);
	val |= BMAC_ADDR_CMPEN_EN0;
	nw64_mac(BMAC_ADDR_CMPEN, val);
पूर्ण

अटल व्योम niu_init_rx_mac(काष्ठा niu *np)
अणु
	niu_set_primary_mac(np, np->dev->dev_addr);

	अगर (np->flags & NIU_FLAGS_XMAC)
		niu_init_rx_xmac(np);
	अन्यथा
		niu_init_rx_bmac(np);
पूर्ण

अटल व्योम niu_enable_tx_xmac(काष्ठा niu *np, पूर्णांक on)
अणु
	u64 val = nr64_mac(XMAC_CONFIG);

	अगर (on)
		val |= XMAC_CONFIG_TX_ENABLE;
	अन्यथा
		val &= ~XMAC_CONFIG_TX_ENABLE;
	nw64_mac(XMAC_CONFIG, val);
पूर्ण

अटल व्योम niu_enable_tx_bmac(काष्ठा niu *np, पूर्णांक on)
अणु
	u64 val = nr64_mac(BTXMAC_CONFIG);

	अगर (on)
		val |= BTXMAC_CONFIG_ENABLE;
	अन्यथा
		val &= ~BTXMAC_CONFIG_ENABLE;
	nw64_mac(BTXMAC_CONFIG, val);
पूर्ण

अटल व्योम niu_enable_tx_mac(काष्ठा niu *np, पूर्णांक on)
अणु
	अगर (np->flags & NIU_FLAGS_XMAC)
		niu_enable_tx_xmac(np, on);
	अन्यथा
		niu_enable_tx_bmac(np, on);
पूर्ण

अटल व्योम niu_enable_rx_xmac(काष्ठा niu *np, पूर्णांक on)
अणु
	u64 val = nr64_mac(XMAC_CONFIG);

	val &= ~(XMAC_CONFIG_HASH_FILTER_EN |
		 XMAC_CONFIG_PROMISCUOUS);

	अगर (np->flags & NIU_FLAGS_MCAST)
		val |= XMAC_CONFIG_HASH_FILTER_EN;
	अगर (np->flags & NIU_FLAGS_PROMISC)
		val |= XMAC_CONFIG_PROMISCUOUS;

	अगर (on)
		val |= XMAC_CONFIG_RX_MAC_ENABLE;
	अन्यथा
		val &= ~XMAC_CONFIG_RX_MAC_ENABLE;
	nw64_mac(XMAC_CONFIG, val);
पूर्ण

अटल व्योम niu_enable_rx_bmac(काष्ठा niu *np, पूर्णांक on)
अणु
	u64 val = nr64_mac(BRXMAC_CONFIG);

	val &= ~(BRXMAC_CONFIG_HASH_FILT_EN |
		 BRXMAC_CONFIG_PROMISC);

	अगर (np->flags & NIU_FLAGS_MCAST)
		val |= BRXMAC_CONFIG_HASH_FILT_EN;
	अगर (np->flags & NIU_FLAGS_PROMISC)
		val |= BRXMAC_CONFIG_PROMISC;

	अगर (on)
		val |= BRXMAC_CONFIG_ENABLE;
	अन्यथा
		val &= ~BRXMAC_CONFIG_ENABLE;
	nw64_mac(BRXMAC_CONFIG, val);
पूर्ण

अटल व्योम niu_enable_rx_mac(काष्ठा niu *np, पूर्णांक on)
अणु
	अगर (np->flags & NIU_FLAGS_XMAC)
		niu_enable_rx_xmac(np, on);
	अन्यथा
		niu_enable_rx_bmac(np, on);
पूर्ण

अटल पूर्णांक niu_init_mac(काष्ठा niu *np)
अणु
	पूर्णांक err;

	niu_init_xअगर(np);
	err = niu_init_pcs(np);
	अगर (err)
		वापस err;

	err = niu_reset_tx_mac(np);
	अगर (err)
		वापस err;
	niu_init_tx_mac(np);
	err = niu_reset_rx_mac(np);
	अगर (err)
		वापस err;
	niu_init_rx_mac(np);

	/* This looks hookey but the RX MAC reset we just did will
	 * unकरो some of the state we setup in niu_init_tx_mac() so we
	 * have to call it again.  In particular, the RX MAC reset will
	 * set the XMAC_MAX रेजिस्टर back to it's शेष value.
	 */
	niu_init_tx_mac(np);
	niu_enable_tx_mac(np, 1);

	niu_enable_rx_mac(np, 1);

	वापस 0;
पूर्ण

अटल व्योम niu_stop_one_tx_channel(काष्ठा niu *np, काष्ठा tx_ring_info *rp)
अणु
	(व्योम) niu_tx_channel_stop(np, rp->tx_channel);
पूर्ण

अटल व्योम niu_stop_tx_channels(काष्ठा niu *np)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < np->num_tx_rings; i++) अणु
		काष्ठा tx_ring_info *rp = &np->tx_rings[i];

		niu_stop_one_tx_channel(np, rp);
	पूर्ण
पूर्ण

अटल व्योम niu_reset_one_tx_channel(काष्ठा niu *np, काष्ठा tx_ring_info *rp)
अणु
	(व्योम) niu_tx_channel_reset(np, rp->tx_channel);
पूर्ण

अटल व्योम niu_reset_tx_channels(काष्ठा niu *np)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < np->num_tx_rings; i++) अणु
		काष्ठा tx_ring_info *rp = &np->tx_rings[i];

		niu_reset_one_tx_channel(np, rp);
	पूर्ण
पूर्ण

अटल व्योम niu_stop_one_rx_channel(काष्ठा niu *np, काष्ठा rx_ring_info *rp)
अणु
	(व्योम) niu_enable_rx_channel(np, rp->rx_channel, 0);
पूर्ण

अटल व्योम niu_stop_rx_channels(काष्ठा niu *np)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < np->num_rx_rings; i++) अणु
		काष्ठा rx_ring_info *rp = &np->rx_rings[i];

		niu_stop_one_rx_channel(np, rp);
	पूर्ण
पूर्ण

अटल व्योम niu_reset_one_rx_channel(काष्ठा niu *np, काष्ठा rx_ring_info *rp)
अणु
	पूर्णांक channel = rp->rx_channel;

	(व्योम) niu_rx_channel_reset(np, channel);
	nw64(RX_DMA_ENT_MSK(channel), RX_DMA_ENT_MSK_ALL);
	nw64(RX_DMA_CTL_STAT(channel), 0);
	(व्योम) niu_enable_rx_channel(np, channel, 0);
पूर्ण

अटल व्योम niu_reset_rx_channels(काष्ठा niu *np)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < np->num_rx_rings; i++) अणु
		काष्ठा rx_ring_info *rp = &np->rx_rings[i];

		niu_reset_one_rx_channel(np, rp);
	पूर्ण
पूर्ण

अटल व्योम niu_disable_ipp(काष्ठा niu *np)
अणु
	u64 rd, wr, val;
	पूर्णांक limit;

	rd = nr64_ipp(IPP_DFIFO_RD_PTR);
	wr = nr64_ipp(IPP_DFIFO_WR_PTR);
	limit = 100;
	जबतक (--limit >= 0 && (rd != wr)) अणु
		rd = nr64_ipp(IPP_DFIFO_RD_PTR);
		wr = nr64_ipp(IPP_DFIFO_WR_PTR);
	पूर्ण
	अगर (limit < 0 &&
	    (rd != 0 && wr != 1)) अणु
		netdev_err(np->dev, "IPP would not quiesce, rd_ptr[%llx] wr_ptr[%llx]\n",
			   (अचिन्हित दीर्घ दीर्घ)nr64_ipp(IPP_DFIFO_RD_PTR),
			   (अचिन्हित दीर्घ दीर्घ)nr64_ipp(IPP_DFIFO_WR_PTR));
	पूर्ण

	val = nr64_ipp(IPP_CFIG);
	val &= ~(IPP_CFIG_IPP_ENABLE |
		 IPP_CFIG_DFIFO_ECC_EN |
		 IPP_CFIG_DROP_BAD_CRC |
		 IPP_CFIG_CKSUM_EN);
	nw64_ipp(IPP_CFIG, val);

	(व्योम) niu_ipp_reset(np);
पूर्ण

अटल पूर्णांक niu_init_hw(काष्ठा niu *np)
अणु
	पूर्णांक i, err;

	netअगर_prपूर्णांकk(np, अगरup, KERN_DEBUG, np->dev, "Initialize TXC\n");
	niu_txc_enable_port(np, 1);
	niu_txc_port_dma_enable(np, 1);
	niu_txc_set_imask(np, 0);

	netअगर_prपूर्णांकk(np, अगरup, KERN_DEBUG, np->dev, "Initialize TX channels\n");
	क्रम (i = 0; i < np->num_tx_rings; i++) अणु
		काष्ठा tx_ring_info *rp = &np->tx_rings[i];

		err = niu_init_one_tx_channel(np, rp);
		अगर (err)
			वापस err;
	पूर्ण

	netअगर_prपूर्णांकk(np, अगरup, KERN_DEBUG, np->dev, "Initialize RX channels\n");
	err = niu_init_rx_channels(np);
	अगर (err)
		जाओ out_uninit_tx_channels;

	netअगर_prपूर्णांकk(np, अगरup, KERN_DEBUG, np->dev, "Initialize classifier\n");
	err = niu_init_classअगरier_hw(np);
	अगर (err)
		जाओ out_uninit_rx_channels;

	netअगर_prपूर्णांकk(np, अगरup, KERN_DEBUG, np->dev, "Initialize ZCP\n");
	err = niu_init_zcp(np);
	अगर (err)
		जाओ out_uninit_rx_channels;

	netअगर_prपूर्णांकk(np, अगरup, KERN_DEBUG, np->dev, "Initialize IPP\n");
	err = niu_init_ipp(np);
	अगर (err)
		जाओ out_uninit_rx_channels;

	netअगर_prपूर्णांकk(np, अगरup, KERN_DEBUG, np->dev, "Initialize MAC\n");
	err = niu_init_mac(np);
	अगर (err)
		जाओ out_uninit_ipp;

	वापस 0;

out_uninit_ipp:
	netअगर_prपूर्णांकk(np, अगरup, KERN_DEBUG, np->dev, "Uninit IPP\n");
	niu_disable_ipp(np);

out_uninit_rx_channels:
	netअगर_prपूर्णांकk(np, अगरup, KERN_DEBUG, np->dev, "Uninit RX channels\n");
	niu_stop_rx_channels(np);
	niu_reset_rx_channels(np);

out_uninit_tx_channels:
	netअगर_prपूर्णांकk(np, अगरup, KERN_DEBUG, np->dev, "Uninit TX channels\n");
	niu_stop_tx_channels(np);
	niu_reset_tx_channels(np);

	वापस err;
पूर्ण

अटल व्योम niu_stop_hw(काष्ठा niu *np)
अणु
	netअगर_prपूर्णांकk(np, अगरकरोwn, KERN_DEBUG, np->dev, "Disable interrupts\n");
	niu_enable_पूर्णांकerrupts(np, 0);

	netअगर_prपूर्णांकk(np, अगरकरोwn, KERN_DEBUG, np->dev, "Disable RX MAC\n");
	niu_enable_rx_mac(np, 0);

	netअगर_prपूर्णांकk(np, अगरकरोwn, KERN_DEBUG, np->dev, "Disable IPP\n");
	niu_disable_ipp(np);

	netअगर_prपूर्णांकk(np, अगरकरोwn, KERN_DEBUG, np->dev, "Stop TX channels\n");
	niu_stop_tx_channels(np);

	netअगर_prपूर्णांकk(np, अगरकरोwn, KERN_DEBUG, np->dev, "Stop RX channels\n");
	niu_stop_rx_channels(np);

	netअगर_prपूर्णांकk(np, अगरकरोwn, KERN_DEBUG, np->dev, "Reset TX channels\n");
	niu_reset_tx_channels(np);

	netअगर_prपूर्णांकk(np, अगरकरोwn, KERN_DEBUG, np->dev, "Reset RX channels\n");
	niu_reset_rx_channels(np);
पूर्ण

अटल व्योम niu_set_irq_name(काष्ठा niu *np)
अणु
	पूर्णांक port = np->port;
	पूर्णांक i, j = 1;

	प्र_लिखो(np->irq_name[0], "%s:MAC", np->dev->name);

	अगर (port == 0) अणु
		प्र_लिखो(np->irq_name[1], "%s:MIF", np->dev->name);
		प्र_लिखो(np->irq_name[2], "%s:SYSERR", np->dev->name);
		j = 3;
	पूर्ण

	क्रम (i = 0; i < np->num_ldg - j; i++) अणु
		अगर (i < np->num_rx_rings)
			प्र_लिखो(np->irq_name[i+j], "%s-rx-%d",
				np->dev->name, i);
		अन्यथा अगर (i < np->num_tx_rings + np->num_rx_rings)
			प्र_लिखो(np->irq_name[i+j], "%s-tx-%d", np->dev->name,
				i - np->num_rx_rings);
	पूर्ण
पूर्ण

अटल पूर्णांक niu_request_irq(काष्ठा niu *np)
अणु
	पूर्णांक i, j, err;

	niu_set_irq_name(np);

	err = 0;
	क्रम (i = 0; i < np->num_ldg; i++) अणु
		काष्ठा niu_ldg *lp = &np->ldg[i];

		err = request_irq(lp->irq, niu_पूर्णांकerrupt, IRQF_SHARED,
				  np->irq_name[i], lp);
		अगर (err)
			जाओ out_मुक्त_irqs;

	पूर्ण

	वापस 0;

out_मुक्त_irqs:
	क्रम (j = 0; j < i; j++) अणु
		काष्ठा niu_ldg *lp = &np->ldg[j];

		मुक्त_irq(lp->irq, lp);
	पूर्ण
	वापस err;
पूर्ण

अटल व्योम niu_मुक्त_irq(काष्ठा niu *np)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < np->num_ldg; i++) अणु
		काष्ठा niu_ldg *lp = &np->ldg[i];

		मुक्त_irq(lp->irq, lp);
	पूर्ण
पूर्ण

अटल व्योम niu_enable_napi(काष्ठा niu *np)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < np->num_ldg; i++)
		napi_enable(&np->ldg[i].napi);
पूर्ण

अटल व्योम niu_disable_napi(काष्ठा niu *np)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < np->num_ldg; i++)
		napi_disable(&np->ldg[i].napi);
पूर्ण

अटल पूर्णांक niu_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा niu *np = netdev_priv(dev);
	पूर्णांक err;

	netअगर_carrier_off(dev);

	err = niu_alloc_channels(np);
	अगर (err)
		जाओ out_err;

	err = niu_enable_पूर्णांकerrupts(np, 0);
	अगर (err)
		जाओ out_मुक्त_channels;

	err = niu_request_irq(np);
	अगर (err)
		जाओ out_मुक्त_channels;

	niu_enable_napi(np);

	spin_lock_irq(&np->lock);

	err = niu_init_hw(np);
	अगर (!err) अणु
		समयr_setup(&np->समयr, niu_समयr, 0);
		np->समयr.expires = jअगरfies + HZ;

		err = niu_enable_पूर्णांकerrupts(np, 1);
		अगर (err)
			niu_stop_hw(np);
	पूर्ण

	spin_unlock_irq(&np->lock);

	अगर (err) अणु
		niu_disable_napi(np);
		जाओ out_मुक्त_irq;
	पूर्ण

	netअगर_tx_start_all_queues(dev);

	अगर (np->link_config.loopback_mode != LOOPBACK_DISABLED)
		netअगर_carrier_on(dev);

	add_समयr(&np->समयr);

	वापस 0;

out_मुक्त_irq:
	niu_मुक्त_irq(np);

out_मुक्त_channels:
	niu_मुक्त_channels(np);

out_err:
	वापस err;
पूर्ण

अटल व्योम niu_full_shutकरोwn(काष्ठा niu *np, काष्ठा net_device *dev)
अणु
	cancel_work_sync(&np->reset_task);

	niu_disable_napi(np);
	netअगर_tx_stop_all_queues(dev);

	del_समयr_sync(&np->समयr);

	spin_lock_irq(&np->lock);

	niu_stop_hw(np);

	spin_unlock_irq(&np->lock);
पूर्ण

अटल पूर्णांक niu_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा niu *np = netdev_priv(dev);

	niu_full_shutकरोwn(np, dev);

	niu_मुक्त_irq(np);

	niu_मुक्त_channels(np);

	niu_handle_led(np, 0);

	वापस 0;
पूर्ण

अटल व्योम niu_sync_xmac_stats(काष्ठा niu *np)
अणु
	काष्ठा niu_xmac_stats *mp = &np->mac_stats.xmac;

	mp->tx_frames += nr64_mac(TXMAC_FRM_CNT);
	mp->tx_bytes += nr64_mac(TXMAC_BYTE_CNT);

	mp->rx_link_faults += nr64_mac(LINK_FAULT_CNT);
	mp->rx_align_errors += nr64_mac(RXMAC_ALIGN_ERR_CNT);
	mp->rx_frags += nr64_mac(RXMAC_FRAG_CNT);
	mp->rx_mcasts += nr64_mac(RXMAC_MC_FRM_CNT);
	mp->rx_bcasts += nr64_mac(RXMAC_BC_FRM_CNT);
	mp->rx_hist_cnt1 += nr64_mac(RXMAC_HIST_CNT1);
	mp->rx_hist_cnt2 += nr64_mac(RXMAC_HIST_CNT2);
	mp->rx_hist_cnt3 += nr64_mac(RXMAC_HIST_CNT3);
	mp->rx_hist_cnt4 += nr64_mac(RXMAC_HIST_CNT4);
	mp->rx_hist_cnt5 += nr64_mac(RXMAC_HIST_CNT5);
	mp->rx_hist_cnt6 += nr64_mac(RXMAC_HIST_CNT6);
	mp->rx_hist_cnt7 += nr64_mac(RXMAC_HIST_CNT7);
	mp->rx_octets += nr64_mac(RXMAC_BT_CNT);
	mp->rx_code_violations += nr64_mac(RXMAC_CD_VIO_CNT);
	mp->rx_len_errors += nr64_mac(RXMAC_MPSZER_CNT);
	mp->rx_crc_errors += nr64_mac(RXMAC_CRC_ER_CNT);
पूर्ण

अटल व्योम niu_sync_bmac_stats(काष्ठा niu *np)
अणु
	काष्ठा niu_bmac_stats *mp = &np->mac_stats.bmac;

	mp->tx_bytes += nr64_mac(BTXMAC_BYTE_CNT);
	mp->tx_frames += nr64_mac(BTXMAC_FRM_CNT);

	mp->rx_frames += nr64_mac(BRXMAC_FRAME_CNT);
	mp->rx_align_errors += nr64_mac(BRXMAC_ALIGN_ERR_CNT);
	mp->rx_crc_errors += nr64_mac(BRXMAC_ALIGN_ERR_CNT);
	mp->rx_len_errors += nr64_mac(BRXMAC_CODE_VIOL_ERR_CNT);
पूर्ण

अटल व्योम niu_sync_mac_stats(काष्ठा niu *np)
अणु
	अगर (np->flags & NIU_FLAGS_XMAC)
		niu_sync_xmac_stats(np);
	अन्यथा
		niu_sync_bmac_stats(np);
पूर्ण

अटल व्योम niu_get_rx_stats(काष्ठा niu *np,
			     काष्ठा rtnl_link_stats64 *stats)
अणु
	u64 pkts, dropped, errors, bytes;
	काष्ठा rx_ring_info *rx_rings;
	पूर्णांक i;

	pkts = dropped = errors = bytes = 0;

	rx_rings = READ_ONCE(np->rx_rings);
	अगर (!rx_rings)
		जाओ no_rings;

	क्रम (i = 0; i < np->num_rx_rings; i++) अणु
		काष्ठा rx_ring_info *rp = &rx_rings[i];

		niu_sync_rx_discard_stats(np, rp, 0);

		pkts += rp->rx_packets;
		bytes += rp->rx_bytes;
		dropped += rp->rx_dropped;
		errors += rp->rx_errors;
	पूर्ण

no_rings:
	stats->rx_packets = pkts;
	stats->rx_bytes = bytes;
	stats->rx_dropped = dropped;
	stats->rx_errors = errors;
पूर्ण

अटल व्योम niu_get_tx_stats(काष्ठा niu *np,
			     काष्ठा rtnl_link_stats64 *stats)
अणु
	u64 pkts, errors, bytes;
	काष्ठा tx_ring_info *tx_rings;
	पूर्णांक i;

	pkts = errors = bytes = 0;

	tx_rings = READ_ONCE(np->tx_rings);
	अगर (!tx_rings)
		जाओ no_rings;

	क्रम (i = 0; i < np->num_tx_rings; i++) अणु
		काष्ठा tx_ring_info *rp = &tx_rings[i];

		pkts += rp->tx_packets;
		bytes += rp->tx_bytes;
		errors += rp->tx_errors;
	पूर्ण

no_rings:
	stats->tx_packets = pkts;
	stats->tx_bytes = bytes;
	stats->tx_errors = errors;
पूर्ण

अटल व्योम niu_get_stats(काष्ठा net_device *dev,
			  काष्ठा rtnl_link_stats64 *stats)
अणु
	काष्ठा niu *np = netdev_priv(dev);

	अगर (netअगर_running(dev)) अणु
		niu_get_rx_stats(np, stats);
		niu_get_tx_stats(np, stats);
	पूर्ण
पूर्ण

अटल व्योम niu_load_hash_xmac(काष्ठा niu *np, u16 *hash)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 16; i++)
		nw64_mac(XMAC_HASH_TBL(i), hash[i]);
पूर्ण

अटल व्योम niu_load_hash_bmac(काष्ठा niu *np, u16 *hash)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 16; i++)
		nw64_mac(BMAC_HASH_TBL(i), hash[i]);
पूर्ण

अटल व्योम niu_load_hash(काष्ठा niu *np, u16 *hash)
अणु
	अगर (np->flags & NIU_FLAGS_XMAC)
		niu_load_hash_xmac(np, hash);
	अन्यथा
		niu_load_hash_bmac(np, hash);
पूर्ण

अटल व्योम niu_set_rx_mode(काष्ठा net_device *dev)
अणु
	काष्ठा niu *np = netdev_priv(dev);
	पूर्णांक i, alt_cnt, err;
	काष्ठा netdev_hw_addr *ha;
	अचिन्हित दीर्घ flags;
	u16 hash[16] = अणु 0, पूर्ण;

	spin_lock_irqsave(&np->lock, flags);
	niu_enable_rx_mac(np, 0);

	np->flags &= ~(NIU_FLAGS_MCAST | NIU_FLAGS_PROMISC);
	अगर (dev->flags & IFF_PROMISC)
		np->flags |= NIU_FLAGS_PROMISC;
	अगर ((dev->flags & IFF_ALLMULTI) || (!netdev_mc_empty(dev)))
		np->flags |= NIU_FLAGS_MCAST;

	alt_cnt = netdev_uc_count(dev);
	अगर (alt_cnt > niu_num_alt_addr(np)) अणु
		alt_cnt = 0;
		np->flags |= NIU_FLAGS_PROMISC;
	पूर्ण

	अगर (alt_cnt) अणु
		पूर्णांक index = 0;

		netdev_क्रम_each_uc_addr(ha, dev) अणु
			err = niu_set_alt_mac(np, index, ha->addr);
			अगर (err)
				netdev_warn(dev, "Error %d adding alt mac %d\n",
					    err, index);
			err = niu_enable_alt_mac(np, index, 1);
			अगर (err)
				netdev_warn(dev, "Error %d enabling alt mac %d\n",
					    err, index);

			index++;
		पूर्ण
	पूर्ण अन्यथा अणु
		पूर्णांक alt_start;
		अगर (np->flags & NIU_FLAGS_XMAC)
			alt_start = 0;
		अन्यथा
			alt_start = 1;
		क्रम (i = alt_start; i < niu_num_alt_addr(np); i++) अणु
			err = niu_enable_alt_mac(np, i, 0);
			अगर (err)
				netdev_warn(dev, "Error %d disabling alt mac %d\n",
					    err, i);
		पूर्ण
	पूर्ण
	अगर (dev->flags & IFF_ALLMULTI) अणु
		क्रम (i = 0; i < 16; i++)
			hash[i] = 0xffff;
	पूर्ण अन्यथा अगर (!netdev_mc_empty(dev)) अणु
		netdev_क्रम_each_mc_addr(ha, dev) अणु
			u32 crc = ether_crc_le(ETH_ALEN, ha->addr);

			crc >>= 24;
			hash[crc >> 4] |= (1 << (15 - (crc & 0xf)));
		पूर्ण
	पूर्ण

	अगर (np->flags & NIU_FLAGS_MCAST)
		niu_load_hash(np, hash);

	niu_enable_rx_mac(np, 1);
	spin_unlock_irqrestore(&np->lock, flags);
पूर्ण

अटल पूर्णांक niu_set_mac_addr(काष्ठा net_device *dev, व्योम *p)
अणु
	काष्ठा niu *np = netdev_priv(dev);
	काष्ठा sockaddr *addr = p;
	अचिन्हित दीर्घ flags;

	अगर (!is_valid_ether_addr(addr->sa_data))
		वापस -EADDRNOTAVAIL;

	स_नकल(dev->dev_addr, addr->sa_data, ETH_ALEN);

	अगर (!netअगर_running(dev))
		वापस 0;

	spin_lock_irqsave(&np->lock, flags);
	niu_enable_rx_mac(np, 0);
	niu_set_primary_mac(np, dev->dev_addr);
	niu_enable_rx_mac(np, 1);
	spin_unlock_irqrestore(&np->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक niu_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल व्योम niu_netअगर_stop(काष्ठा niu *np)
अणु
	netअगर_trans_update(np->dev);	/* prevent tx समयout */

	niu_disable_napi(np);

	netअगर_tx_disable(np->dev);
पूर्ण

अटल व्योम niu_netअगर_start(काष्ठा niu *np)
अणु
	/* NOTE: unconditional netअगर_wake_queue is only appropriate
	 * so दीर्घ as all callers are assured to have मुक्त tx slots
	 * (such as after niu_init_hw).
	 */
	netअगर_tx_wake_all_queues(np->dev);

	niu_enable_napi(np);

	niu_enable_पूर्णांकerrupts(np, 1);
पूर्ण

अटल व्योम niu_reset_buffers(काष्ठा niu *np)
अणु
	पूर्णांक i, j, k, err;

	अगर (np->rx_rings) अणु
		क्रम (i = 0; i < np->num_rx_rings; i++) अणु
			काष्ठा rx_ring_info *rp = &np->rx_rings[i];

			क्रम (j = 0, k = 0; j < MAX_RBR_RING_SIZE; j++) अणु
				काष्ठा page *page;

				page = rp->rxhash[j];
				जबतक (page) अणु
					काष्ठा page *next =
						(काष्ठा page *) page->mapping;
					u64 base = page->index;
					base = base >> RBR_DESCR_ADDR_SHIFT;
					rp->rbr[k++] = cpu_to_le32(base);
					page = next;
				पूर्ण
			पूर्ण
			क्रम (; k < MAX_RBR_RING_SIZE; k++) अणु
				err = niu_rbr_add_page(np, rp, GFP_ATOMIC, k);
				अगर (unlikely(err))
					अवरोध;
			पूर्ण

			rp->rbr_index = rp->rbr_table_size - 1;
			rp->rcr_index = 0;
			rp->rbr_pending = 0;
			rp->rbr_refill_pending = 0;
		पूर्ण
	पूर्ण
	अगर (np->tx_rings) अणु
		क्रम (i = 0; i < np->num_tx_rings; i++) अणु
			काष्ठा tx_ring_info *rp = &np->tx_rings[i];

			क्रम (j = 0; j < MAX_TX_RING_SIZE; j++) अणु
				अगर (rp->tx_buffs[j].skb)
					(व्योम) release_tx_packet(np, rp, j);
			पूर्ण

			rp->pending = MAX_TX_RING_SIZE;
			rp->prod = 0;
			rp->cons = 0;
			rp->wrap_bit = 0;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम niu_reset_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा niu *np = container_of(work, काष्ठा niu, reset_task);
	अचिन्हित दीर्घ flags;
	पूर्णांक err;

	spin_lock_irqsave(&np->lock, flags);
	अगर (!netअगर_running(np->dev)) अणु
		spin_unlock_irqrestore(&np->lock, flags);
		वापस;
	पूर्ण

	spin_unlock_irqrestore(&np->lock, flags);

	del_समयr_sync(&np->समयr);

	niu_netअगर_stop(np);

	spin_lock_irqsave(&np->lock, flags);

	niu_stop_hw(np);

	spin_unlock_irqrestore(&np->lock, flags);

	niu_reset_buffers(np);

	spin_lock_irqsave(&np->lock, flags);

	err = niu_init_hw(np);
	अगर (!err) अणु
		np->समयr.expires = jअगरfies + HZ;
		add_समयr(&np->समयr);
		niu_netअगर_start(np);
	पूर्ण

	spin_unlock_irqrestore(&np->lock, flags);
पूर्ण

अटल व्योम niu_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा niu *np = netdev_priv(dev);

	dev_err(np->device, "%s: Transmit timed out, resetting\n",
		dev->name);

	schedule_work(&np->reset_task);
पूर्ण

अटल व्योम niu_set_txd(काष्ठा tx_ring_info *rp, पूर्णांक index,
			u64 mapping, u64 len, u64 mark,
			u64 n_frags)
अणु
	__le64 *desc = &rp->descr[index];

	*desc = cpu_to_le64(mark |
			    (n_frags << TX_DESC_NUM_PTR_SHIFT) |
			    (len << TX_DESC_TR_LEN_SHIFT) |
			    (mapping & TX_DESC_SAD));
पूर्ण

अटल u64 niu_compute_tx_flags(काष्ठा sk_buff *skb, काष्ठा ethhdr *ehdr,
				u64 pad_bytes, u64 len)
अणु
	u16 eth_proto, eth_proto_inner;
	u64 csum_bits, l3off, ihl, ret;
	u8 ip_proto;
	पूर्णांक ipv6;

	eth_proto = be16_to_cpu(ehdr->h_proto);
	eth_proto_inner = eth_proto;
	अगर (eth_proto == ETH_P_8021Q) अणु
		काष्ठा vlan_ethhdr *vp = (काष्ठा vlan_ethhdr *) ehdr;
		__be16 val = vp->h_vlan_encapsulated_proto;

		eth_proto_inner = be16_to_cpu(val);
	पूर्ण

	ipv6 = ihl = 0;
	चयन (skb->protocol) अणु
	हाल cpu_to_be16(ETH_P_IP):
		ip_proto = ip_hdr(skb)->protocol;
		ihl = ip_hdr(skb)->ihl;
		अवरोध;
	हाल cpu_to_be16(ETH_P_IPV6):
		ip_proto = ipv6_hdr(skb)->nexthdr;
		ihl = (40 >> 2);
		ipv6 = 1;
		अवरोध;
	शेष:
		ip_proto = ihl = 0;
		अवरोध;
	पूर्ण

	csum_bits = TXHDR_CSUM_NONE;
	अगर (skb->ip_summed == CHECKSUM_PARTIAL) अणु
		u64 start, stuff;

		csum_bits = (ip_proto == IPPROTO_TCP ?
			     TXHDR_CSUM_TCP :
			     (ip_proto == IPPROTO_UDP ?
			      TXHDR_CSUM_UDP : TXHDR_CSUM_SCTP));

		start = skb_checksum_start_offset(skb) -
			(pad_bytes + माप(काष्ठा tx_pkt_hdr));
		stuff = start + skb->csum_offset;

		csum_bits |= (start / 2) << TXHDR_L4START_SHIFT;
		csum_bits |= (stuff / 2) << TXHDR_L4STUFF_SHIFT;
	पूर्ण

	l3off = skb_network_offset(skb) -
		(pad_bytes + माप(काष्ठा tx_pkt_hdr));

	ret = (((pad_bytes / 2) << TXHDR_PAD_SHIFT) |
	       (len << TXHDR_LEN_SHIFT) |
	       ((l3off / 2) << TXHDR_L3START_SHIFT) |
	       (ihl << TXHDR_IHL_SHIFT) |
	       ((eth_proto_inner < ETH_P_802_3_MIN) ? TXHDR_LLC : 0) |
	       ((eth_proto == ETH_P_8021Q) ? TXHDR_VLAN : 0) |
	       (ipv6 ? TXHDR_IP_VER : 0) |
	       csum_bits);

	वापस ret;
पूर्ण

अटल netdev_tx_t niu_start_xmit(काष्ठा sk_buff *skb,
				  काष्ठा net_device *dev)
अणु
	काष्ठा niu *np = netdev_priv(dev);
	अचिन्हित दीर्घ align, headroom;
	काष्ठा netdev_queue *txq;
	काष्ठा tx_ring_info *rp;
	काष्ठा tx_pkt_hdr *tp;
	अचिन्हित पूर्णांक len, nfg;
	काष्ठा ethhdr *ehdr;
	पूर्णांक prod, i, tlen;
	u64 mapping, mrk;

	i = skb_get_queue_mapping(skb);
	rp = &np->tx_rings[i];
	txq = netdev_get_tx_queue(dev, i);

	अगर (niu_tx_avail(rp) <= (skb_shinfo(skb)->nr_frags + 1)) अणु
		netअगर_tx_stop_queue(txq);
		dev_err(np->device, "%s: BUG! Tx ring full when queue awake!\n", dev->name);
		rp->tx_errors++;
		वापस NETDEV_TX_BUSY;
	पूर्ण

	अगर (eth_skb_pad(skb))
		जाओ out;

	len = माप(काष्ठा tx_pkt_hdr) + 15;
	अगर (skb_headroom(skb) < len) अणु
		काष्ठा sk_buff *skb_new;

		skb_new = skb_पुनः_स्मृति_headroom(skb, len);
		अगर (!skb_new)
			जाओ out_drop;
		kमुक्त_skb(skb);
		skb = skb_new;
	पूर्ण अन्यथा
		skb_orphan(skb);

	align = ((अचिन्हित दीर्घ) skb->data & (16 - 1));
	headroom = align + माप(काष्ठा tx_pkt_hdr);

	ehdr = (काष्ठा ethhdr *) skb->data;
	tp = skb_push(skb, headroom);

	len = skb->len - माप(काष्ठा tx_pkt_hdr);
	tp->flags = cpu_to_le64(niu_compute_tx_flags(skb, ehdr, align, len));
	tp->resv = 0;

	len = skb_headlen(skb);
	mapping = np->ops->map_single(np->device, skb->data,
				      len, DMA_TO_DEVICE);

	prod = rp->prod;

	rp->tx_buffs[prod].skb = skb;
	rp->tx_buffs[prod].mapping = mapping;

	mrk = TX_DESC_SOP;
	अगर (++rp->mark_counter == rp->mark_freq) अणु
		rp->mark_counter = 0;
		mrk |= TX_DESC_MARK;
		rp->mark_pending++;
	पूर्ण

	tlen = len;
	nfg = skb_shinfo(skb)->nr_frags;
	जबतक (tlen > 0) अणु
		tlen -= MAX_TX_DESC_LEN;
		nfg++;
	पूर्ण

	जबतक (len > 0) अणु
		अचिन्हित पूर्णांक this_len = len;

		अगर (this_len > MAX_TX_DESC_LEN)
			this_len = MAX_TX_DESC_LEN;

		niu_set_txd(rp, prod, mapping, this_len, mrk, nfg);
		mrk = nfg = 0;

		prod = NEXT_TX(rp, prod);
		mapping += this_len;
		len -= this_len;
	पूर्ण

	क्रम (i = 0; i <  skb_shinfo(skb)->nr_frags; i++) अणु
		स्थिर skb_frag_t *frag = &skb_shinfo(skb)->frags[i];

		len = skb_frag_size(frag);
		mapping = np->ops->map_page(np->device, skb_frag_page(frag),
					    skb_frag_off(frag), len,
					    DMA_TO_DEVICE);

		rp->tx_buffs[prod].skb = शून्य;
		rp->tx_buffs[prod].mapping = mapping;

		niu_set_txd(rp, prod, mapping, len, 0, 0);

		prod = NEXT_TX(rp, prod);
	पूर्ण

	अगर (prod < rp->prod)
		rp->wrap_bit ^= TX_RING_KICK_WRAP;
	rp->prod = prod;

	nw64(TX_RING_KICK(rp->tx_channel), rp->wrap_bit | (prod << 3));

	अगर (unlikely(niu_tx_avail(rp) <= (MAX_SKB_FRAGS + 1))) अणु
		netअगर_tx_stop_queue(txq);
		अगर (niu_tx_avail(rp) > NIU_TX_WAKEUP_THRESH(rp))
			netअगर_tx_wake_queue(txq);
	पूर्ण

out:
	वापस NETDEV_TX_OK;

out_drop:
	rp->tx_errors++;
	kमुक्त_skb(skb);
	जाओ out;
पूर्ण

अटल पूर्णांक niu_change_mtu(काष्ठा net_device *dev, पूर्णांक new_mtu)
अणु
	काष्ठा niu *np = netdev_priv(dev);
	पूर्णांक err, orig_jumbo, new_jumbo;

	orig_jumbo = (dev->mtu > ETH_DATA_LEN);
	new_jumbo = (new_mtu > ETH_DATA_LEN);

	dev->mtu = new_mtu;

	अगर (!netअगर_running(dev) ||
	    (orig_jumbo == new_jumbo))
		वापस 0;

	niu_full_shutकरोwn(np, dev);

	niu_मुक्त_channels(np);

	niu_enable_napi(np);

	err = niu_alloc_channels(np);
	अगर (err)
		वापस err;

	spin_lock_irq(&np->lock);

	err = niu_init_hw(np);
	अगर (!err) अणु
		समयr_setup(&np->समयr, niu_समयr, 0);
		np->समयr.expires = jअगरfies + HZ;

		err = niu_enable_पूर्णांकerrupts(np, 1);
		अगर (err)
			niu_stop_hw(np);
	पूर्ण

	spin_unlock_irq(&np->lock);

	अगर (!err) अणु
		netअगर_tx_start_all_queues(dev);
		अगर (np->link_config.loopback_mode != LOOPBACK_DISABLED)
			netअगर_carrier_on(dev);

		add_समयr(&np->समयr);
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम niu_get_drvinfo(काष्ठा net_device *dev,
			    काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा niu *np = netdev_priv(dev);
	काष्ठा niu_vpd *vpd = &np->vpd;

	strlcpy(info->driver, DRV_MODULE_NAME, माप(info->driver));
	strlcpy(info->version, DRV_MODULE_VERSION, माप(info->version));
	snम_लिखो(info->fw_version, माप(info->fw_version), "%d.%d",
		vpd->fcode_major, vpd->fcode_minor);
	अगर (np->parent->plat_type != PLAT_TYPE_NIU)
		strlcpy(info->bus_info, pci_name(np->pdev),
			माप(info->bus_info));
पूर्ण

अटल पूर्णांक niu_get_link_ksettings(काष्ठा net_device *dev,
				  काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा niu *np = netdev_priv(dev);
	काष्ठा niu_link_config *lp;

	lp = &np->link_config;

	स_रखो(cmd, 0, माप(*cmd));
	cmd->base.phy_address = np->phy_addr;
	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.supported,
						lp->supported);
	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.advertising,
						lp->active_advertising);
	cmd->base.स्वतःneg = lp->active_स्वतःneg;
	cmd->base.speed = lp->active_speed;
	cmd->base.duplex = lp->active_duplex;
	cmd->base.port = (np->flags & NIU_FLAGS_FIBER) ? PORT_FIBRE : PORT_TP;

	वापस 0;
पूर्ण

अटल पूर्णांक niu_set_link_ksettings(काष्ठा net_device *dev,
				  स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा niu *np = netdev_priv(dev);
	काष्ठा niu_link_config *lp = &np->link_config;

	ethtool_convert_link_mode_to_legacy_u32(&lp->advertising,
						cmd->link_modes.advertising);
	lp->speed = cmd->base.speed;
	lp->duplex = cmd->base.duplex;
	lp->स्वतःneg = cmd->base.स्वतःneg;
	वापस niu_init_link(np);
पूर्ण

अटल u32 niu_get_msglevel(काष्ठा net_device *dev)
अणु
	काष्ठा niu *np = netdev_priv(dev);
	वापस np->msg_enable;
पूर्ण

अटल व्योम niu_set_msglevel(काष्ठा net_device *dev, u32 value)
अणु
	काष्ठा niu *np = netdev_priv(dev);
	np->msg_enable = value;
पूर्ण

अटल पूर्णांक niu_nway_reset(काष्ठा net_device *dev)
अणु
	काष्ठा niu *np = netdev_priv(dev);

	अगर (np->link_config.स्वतःneg)
		वापस niu_init_link(np);

	वापस 0;
पूर्ण

अटल पूर्णांक niu_get_eeprom_len(काष्ठा net_device *dev)
अणु
	काष्ठा niu *np = netdev_priv(dev);

	वापस np->eeprom_len;
पूर्ण

अटल पूर्णांक niu_get_eeprom(काष्ठा net_device *dev,
			  काष्ठा ethtool_eeprom *eeprom, u8 *data)
अणु
	काष्ठा niu *np = netdev_priv(dev);
	u32 offset, len, val;

	offset = eeprom->offset;
	len = eeprom->len;

	अगर (offset + len < offset)
		वापस -EINVAL;
	अगर (offset >= np->eeprom_len)
		वापस -EINVAL;
	अगर (offset + len > np->eeprom_len)
		len = eeprom->len = np->eeprom_len - offset;

	अगर (offset & 3) अणु
		u32 b_offset, b_count;

		b_offset = offset & 3;
		b_count = 4 - b_offset;
		अगर (b_count > len)
			b_count = len;

		val = nr64(ESPC_NCR((offset - b_offset) / 4));
		स_नकल(data, ((अक्षर *)&val) + b_offset, b_count);
		data += b_count;
		len -= b_count;
		offset += b_count;
	पूर्ण
	जबतक (len >= 4) अणु
		val = nr64(ESPC_NCR(offset / 4));
		स_नकल(data, &val, 4);
		data += 4;
		len -= 4;
		offset += 4;
	पूर्ण
	अगर (len) अणु
		val = nr64(ESPC_NCR(offset / 4));
		स_नकल(data, &val, len);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम niu_ethflow_to_l3proto(पूर्णांक flow_type, u8 *pid)
अणु
	चयन (flow_type) अणु
	हाल TCP_V4_FLOW:
	हाल TCP_V6_FLOW:
		*pid = IPPROTO_TCP;
		अवरोध;
	हाल UDP_V4_FLOW:
	हाल UDP_V6_FLOW:
		*pid = IPPROTO_UDP;
		अवरोध;
	हाल SCTP_V4_FLOW:
	हाल SCTP_V6_FLOW:
		*pid = IPPROTO_SCTP;
		अवरोध;
	हाल AH_V4_FLOW:
	हाल AH_V6_FLOW:
		*pid = IPPROTO_AH;
		अवरोध;
	हाल ESP_V4_FLOW:
	हाल ESP_V6_FLOW:
		*pid = IPPROTO_ESP;
		अवरोध;
	शेष:
		*pid = 0;
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक niu_class_to_ethflow(u64 class, पूर्णांक *flow_type)
अणु
	चयन (class) अणु
	हाल CLASS_CODE_TCP_IPV4:
		*flow_type = TCP_V4_FLOW;
		अवरोध;
	हाल CLASS_CODE_UDP_IPV4:
		*flow_type = UDP_V4_FLOW;
		अवरोध;
	हाल CLASS_CODE_AH_ESP_IPV4:
		*flow_type = AH_V4_FLOW;
		अवरोध;
	हाल CLASS_CODE_SCTP_IPV4:
		*flow_type = SCTP_V4_FLOW;
		अवरोध;
	हाल CLASS_CODE_TCP_IPV6:
		*flow_type = TCP_V6_FLOW;
		अवरोध;
	हाल CLASS_CODE_UDP_IPV6:
		*flow_type = UDP_V6_FLOW;
		अवरोध;
	हाल CLASS_CODE_AH_ESP_IPV6:
		*flow_type = AH_V6_FLOW;
		अवरोध;
	हाल CLASS_CODE_SCTP_IPV6:
		*flow_type = SCTP_V6_FLOW;
		अवरोध;
	हाल CLASS_CODE_USER_PROG1:
	हाल CLASS_CODE_USER_PROG2:
	हाल CLASS_CODE_USER_PROG3:
	हाल CLASS_CODE_USER_PROG4:
		*flow_type = IP_USER_FLOW;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक niu_ethflow_to_class(पूर्णांक flow_type, u64 *class)
अणु
	चयन (flow_type) अणु
	हाल TCP_V4_FLOW:
		*class = CLASS_CODE_TCP_IPV4;
		अवरोध;
	हाल UDP_V4_FLOW:
		*class = CLASS_CODE_UDP_IPV4;
		अवरोध;
	हाल AH_ESP_V4_FLOW:
	हाल AH_V4_FLOW:
	हाल ESP_V4_FLOW:
		*class = CLASS_CODE_AH_ESP_IPV4;
		अवरोध;
	हाल SCTP_V4_FLOW:
		*class = CLASS_CODE_SCTP_IPV4;
		अवरोध;
	हाल TCP_V6_FLOW:
		*class = CLASS_CODE_TCP_IPV6;
		अवरोध;
	हाल UDP_V6_FLOW:
		*class = CLASS_CODE_UDP_IPV6;
		अवरोध;
	हाल AH_ESP_V6_FLOW:
	हाल AH_V6_FLOW:
	हाल ESP_V6_FLOW:
		*class = CLASS_CODE_AH_ESP_IPV6;
		अवरोध;
	हाल SCTP_V6_FLOW:
		*class = CLASS_CODE_SCTP_IPV6;
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

अटल u64 niu_flowkey_to_ethflow(u64 flow_key)
अणु
	u64 ethflow = 0;

	अगर (flow_key & FLOW_KEY_L2DA)
		ethflow |= RXH_L2DA;
	अगर (flow_key & FLOW_KEY_VLAN)
		ethflow |= RXH_VLAN;
	अगर (flow_key & FLOW_KEY_IPSA)
		ethflow |= RXH_IP_SRC;
	अगर (flow_key & FLOW_KEY_IPDA)
		ethflow |= RXH_IP_DST;
	अगर (flow_key & FLOW_KEY_PROTO)
		ethflow |= RXH_L3_PROTO;
	अगर (flow_key & (FLOW_KEY_L4_BYTE12 << FLOW_KEY_L4_0_SHIFT))
		ethflow |= RXH_L4_B_0_1;
	अगर (flow_key & (FLOW_KEY_L4_BYTE12 << FLOW_KEY_L4_1_SHIFT))
		ethflow |= RXH_L4_B_2_3;

	वापस ethflow;

पूर्ण

अटल पूर्णांक niu_ethflow_to_flowkey(u64 ethflow, u64 *flow_key)
अणु
	u64 key = 0;

	अगर (ethflow & RXH_L2DA)
		key |= FLOW_KEY_L2DA;
	अगर (ethflow & RXH_VLAN)
		key |= FLOW_KEY_VLAN;
	अगर (ethflow & RXH_IP_SRC)
		key |= FLOW_KEY_IPSA;
	अगर (ethflow & RXH_IP_DST)
		key |= FLOW_KEY_IPDA;
	अगर (ethflow & RXH_L3_PROTO)
		key |= FLOW_KEY_PROTO;
	अगर (ethflow & RXH_L4_B_0_1)
		key |= (FLOW_KEY_L4_BYTE12 << FLOW_KEY_L4_0_SHIFT);
	अगर (ethflow & RXH_L4_B_2_3)
		key |= (FLOW_KEY_L4_BYTE12 << FLOW_KEY_L4_1_SHIFT);

	*flow_key = key;

	वापस 1;

पूर्ण

अटल पूर्णांक niu_get_hash_opts(काष्ठा niu *np, काष्ठा ethtool_rxnfc *nfc)
अणु
	u64 class;

	nfc->data = 0;

	अगर (!niu_ethflow_to_class(nfc->flow_type, &class))
		वापस -EINVAL;

	अगर (np->parent->tcam_key[class - CLASS_CODE_USER_PROG1] &
	    TCAM_KEY_DISC)
		nfc->data = RXH_DISCARD;
	अन्यथा
		nfc->data = niu_flowkey_to_ethflow(np->parent->flow_key[class -
						      CLASS_CODE_USER_PROG1]);
	वापस 0;
पूर्ण

अटल व्योम niu_get_ip4fs_from_tcam_key(काष्ठा niu_tcam_entry *tp,
					काष्ठा ethtool_rx_flow_spec *fsp)
अणु
	u32 पंचांगp;
	u16 prt;

	पंचांगp = (tp->key[3] & TCAM_V4KEY3_SADDR) >> TCAM_V4KEY3_SADDR_SHIFT;
	fsp->h_u.tcp_ip4_spec.ip4src = cpu_to_be32(पंचांगp);

	पंचांगp = (tp->key[3] & TCAM_V4KEY3_DADDR) >> TCAM_V4KEY3_DADDR_SHIFT;
	fsp->h_u.tcp_ip4_spec.ip4dst = cpu_to_be32(पंचांगp);

	पंचांगp = (tp->key_mask[3] & TCAM_V4KEY3_SADDR) >> TCAM_V4KEY3_SADDR_SHIFT;
	fsp->m_u.tcp_ip4_spec.ip4src = cpu_to_be32(पंचांगp);

	पंचांगp = (tp->key_mask[3] & TCAM_V4KEY3_DADDR) >> TCAM_V4KEY3_DADDR_SHIFT;
	fsp->m_u.tcp_ip4_spec.ip4dst = cpu_to_be32(पंचांगp);

	fsp->h_u.tcp_ip4_spec.tos = (tp->key[2] & TCAM_V4KEY2_TOS) >>
		TCAM_V4KEY2_TOS_SHIFT;
	fsp->m_u.tcp_ip4_spec.tos = (tp->key_mask[2] & TCAM_V4KEY2_TOS) >>
		TCAM_V4KEY2_TOS_SHIFT;

	चयन (fsp->flow_type) अणु
	हाल TCP_V4_FLOW:
	हाल UDP_V4_FLOW:
	हाल SCTP_V4_FLOW:
		prt = ((tp->key[2] & TCAM_V4KEY2_PORT_SPI) >>
			TCAM_V4KEY2_PORT_SPI_SHIFT) >> 16;
		fsp->h_u.tcp_ip4_spec.psrc = cpu_to_be16(prt);

		prt = ((tp->key[2] & TCAM_V4KEY2_PORT_SPI) >>
			TCAM_V4KEY2_PORT_SPI_SHIFT) & 0xffff;
		fsp->h_u.tcp_ip4_spec.pdst = cpu_to_be16(prt);

		prt = ((tp->key_mask[2] & TCAM_V4KEY2_PORT_SPI) >>
			TCAM_V4KEY2_PORT_SPI_SHIFT) >> 16;
		fsp->m_u.tcp_ip4_spec.psrc = cpu_to_be16(prt);

		prt = ((tp->key_mask[2] & TCAM_V4KEY2_PORT_SPI) >>
			 TCAM_V4KEY2_PORT_SPI_SHIFT) & 0xffff;
		fsp->m_u.tcp_ip4_spec.pdst = cpu_to_be16(prt);
		अवरोध;
	हाल AH_V4_FLOW:
	हाल ESP_V4_FLOW:
		पंचांगp = (tp->key[2] & TCAM_V4KEY2_PORT_SPI) >>
			TCAM_V4KEY2_PORT_SPI_SHIFT;
		fsp->h_u.ah_ip4_spec.spi = cpu_to_be32(पंचांगp);

		पंचांगp = (tp->key_mask[2] & TCAM_V4KEY2_PORT_SPI) >>
			TCAM_V4KEY2_PORT_SPI_SHIFT;
		fsp->m_u.ah_ip4_spec.spi = cpu_to_be32(पंचांगp);
		अवरोध;
	हाल IP_USER_FLOW:
		पंचांगp = (tp->key[2] & TCAM_V4KEY2_PORT_SPI) >>
			TCAM_V4KEY2_PORT_SPI_SHIFT;
		fsp->h_u.usr_ip4_spec.l4_4_bytes = cpu_to_be32(पंचांगp);

		पंचांगp = (tp->key_mask[2] & TCAM_V4KEY2_PORT_SPI) >>
			TCAM_V4KEY2_PORT_SPI_SHIFT;
		fsp->m_u.usr_ip4_spec.l4_4_bytes = cpu_to_be32(पंचांगp);

		fsp->h_u.usr_ip4_spec.proto =
			(tp->key[2] & TCAM_V4KEY2_PROTO) >>
			TCAM_V4KEY2_PROTO_SHIFT;
		fsp->m_u.usr_ip4_spec.proto =
			(tp->key_mask[2] & TCAM_V4KEY2_PROTO) >>
			TCAM_V4KEY2_PROTO_SHIFT;

		fsp->h_u.usr_ip4_spec.ip_ver = ETH_RX_NFC_IP4;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक niu_get_ethtool_tcam_entry(काष्ठा niu *np,
				      काष्ठा ethtool_rxnfc *nfc)
अणु
	काष्ठा niu_parent *parent = np->parent;
	काष्ठा niu_tcam_entry *tp;
	काष्ठा ethtool_rx_flow_spec *fsp = &nfc->fs;
	u16 idx;
	u64 class;
	पूर्णांक ret = 0;

	idx = tcam_get_index(np, (u16)nfc->fs.location);

	tp = &parent->tcam[idx];
	अगर (!tp->valid) अणु
		netdev_info(np->dev, "niu%d: entry [%d] invalid for idx[%d]\n",
			    parent->index, (u16)nfc->fs.location, idx);
		वापस -EINVAL;
	पूर्ण

	/* fill the flow spec entry */
	class = (tp->key[0] & TCAM_V4KEY0_CLASS_CODE) >>
		TCAM_V4KEY0_CLASS_CODE_SHIFT;
	ret = niu_class_to_ethflow(class, &fsp->flow_type);
	अगर (ret < 0) अणु
		netdev_info(np->dev, "niu%d: niu_class_to_ethflow failed\n",
			    parent->index);
		जाओ out;
	पूर्ण

	अगर (fsp->flow_type == AH_V4_FLOW || fsp->flow_type == AH_V6_FLOW) अणु
		u32 proto = (tp->key[2] & TCAM_V4KEY2_PROTO) >>
			TCAM_V4KEY2_PROTO_SHIFT;
		अगर (proto == IPPROTO_ESP) अणु
			अगर (fsp->flow_type == AH_V4_FLOW)
				fsp->flow_type = ESP_V4_FLOW;
			अन्यथा
				fsp->flow_type = ESP_V6_FLOW;
		पूर्ण
	पूर्ण

	चयन (fsp->flow_type) अणु
	हाल TCP_V4_FLOW:
	हाल UDP_V4_FLOW:
	हाल SCTP_V4_FLOW:
	हाल AH_V4_FLOW:
	हाल ESP_V4_FLOW:
		niu_get_ip4fs_from_tcam_key(tp, fsp);
		अवरोध;
	हाल TCP_V6_FLOW:
	हाल UDP_V6_FLOW:
	हाल SCTP_V6_FLOW:
	हाल AH_V6_FLOW:
	हाल ESP_V6_FLOW:
		/* Not yet implemented */
		ret = -EINVAL;
		अवरोध;
	हाल IP_USER_FLOW:
		niu_get_ip4fs_from_tcam_key(tp, fsp);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	अगर (ret < 0)
		जाओ out;

	अगर (tp->assoc_data & TCAM_ASSOCDATA_DISC)
		fsp->ring_cookie = RX_CLS_FLOW_DISC;
	अन्यथा
		fsp->ring_cookie = (tp->assoc_data & TCAM_ASSOCDATA_OFFSET) >>
			TCAM_ASSOCDATA_OFFSET_SHIFT;

	/* put the tcam size here */
	nfc->data = tcam_get_size(np);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक niu_get_ethtool_tcam_all(काष्ठा niu *np,
				    काष्ठा ethtool_rxnfc *nfc,
				    u32 *rule_locs)
अणु
	काष्ठा niu_parent *parent = np->parent;
	काष्ठा niu_tcam_entry *tp;
	पूर्णांक i, idx, cnt;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	/* put the tcam size here */
	nfc->data = tcam_get_size(np);

	niu_lock_parent(np, flags);
	क्रम (cnt = 0, i = 0; i < nfc->data; i++) अणु
		idx = tcam_get_index(np, i);
		tp = &parent->tcam[idx];
		अगर (!tp->valid)
			जारी;
		अगर (cnt == nfc->rule_cnt) अणु
			ret = -EMSGSIZE;
			अवरोध;
		पूर्ण
		rule_locs[cnt] = i;
		cnt++;
	पूर्ण
	niu_unlock_parent(np, flags);

	nfc->rule_cnt = cnt;

	वापस ret;
पूर्ण

अटल पूर्णांक niu_get_nfc(काष्ठा net_device *dev, काष्ठा ethtool_rxnfc *cmd,
		       u32 *rule_locs)
अणु
	काष्ठा niu *np = netdev_priv(dev);
	पूर्णांक ret = 0;

	चयन (cmd->cmd) अणु
	हाल ETHTOOL_GRXFH:
		ret = niu_get_hash_opts(np, cmd);
		अवरोध;
	हाल ETHTOOL_GRXRINGS:
		cmd->data = np->num_rx_rings;
		अवरोध;
	हाल ETHTOOL_GRXCLSRLCNT:
		cmd->rule_cnt = tcam_get_valid_entry_cnt(np);
		अवरोध;
	हाल ETHTOOL_GRXCLSRULE:
		ret = niu_get_ethtool_tcam_entry(np, cmd);
		अवरोध;
	हाल ETHTOOL_GRXCLSRLALL:
		ret = niu_get_ethtool_tcam_all(np, cmd, rule_locs);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक niu_set_hash_opts(काष्ठा niu *np, काष्ठा ethtool_rxnfc *nfc)
अणु
	u64 class;
	u64 flow_key = 0;
	अचिन्हित दीर्घ flags;

	अगर (!niu_ethflow_to_class(nfc->flow_type, &class))
		वापस -EINVAL;

	अगर (class < CLASS_CODE_USER_PROG1 ||
	    class > CLASS_CODE_SCTP_IPV6)
		वापस -EINVAL;

	अगर (nfc->data & RXH_DISCARD) अणु
		niu_lock_parent(np, flags);
		flow_key = np->parent->tcam_key[class -
					       CLASS_CODE_USER_PROG1];
		flow_key |= TCAM_KEY_DISC;
		nw64(TCAM_KEY(class - CLASS_CODE_USER_PROG1), flow_key);
		np->parent->tcam_key[class - CLASS_CODE_USER_PROG1] = flow_key;
		niu_unlock_parent(np, flags);
		वापस 0;
	पूर्ण अन्यथा अणु
		/* Discard was set beक्रमe, but is not set now */
		अगर (np->parent->tcam_key[class - CLASS_CODE_USER_PROG1] &
		    TCAM_KEY_DISC) अणु
			niu_lock_parent(np, flags);
			flow_key = np->parent->tcam_key[class -
					       CLASS_CODE_USER_PROG1];
			flow_key &= ~TCAM_KEY_DISC;
			nw64(TCAM_KEY(class - CLASS_CODE_USER_PROG1),
			     flow_key);
			np->parent->tcam_key[class - CLASS_CODE_USER_PROG1] =
				flow_key;
			niu_unlock_parent(np, flags);
		पूर्ण
	पूर्ण

	अगर (!niu_ethflow_to_flowkey(nfc->data, &flow_key))
		वापस -EINVAL;

	niu_lock_parent(np, flags);
	nw64(FLOW_KEY(class - CLASS_CODE_USER_PROG1), flow_key);
	np->parent->flow_key[class - CLASS_CODE_USER_PROG1] = flow_key;
	niu_unlock_parent(np, flags);

	वापस 0;
पूर्ण

अटल व्योम niu_get_tcamkey_from_ip4fs(काष्ठा ethtool_rx_flow_spec *fsp,
				       काष्ठा niu_tcam_entry *tp,
				       पूर्णांक l2_rdc_tab, u64 class)
अणु
	u8 pid = 0;
	u32 sip, dip, sipm, dipm, spi, spim;
	u16 sport, dport, spm, dpm;

	sip = be32_to_cpu(fsp->h_u.tcp_ip4_spec.ip4src);
	sipm = be32_to_cpu(fsp->m_u.tcp_ip4_spec.ip4src);
	dip = be32_to_cpu(fsp->h_u.tcp_ip4_spec.ip4dst);
	dipm = be32_to_cpu(fsp->m_u.tcp_ip4_spec.ip4dst);

	tp->key[0] = class << TCAM_V4KEY0_CLASS_CODE_SHIFT;
	tp->key_mask[0] = TCAM_V4KEY0_CLASS_CODE;
	tp->key[1] = (u64)l2_rdc_tab << TCAM_V4KEY1_L2RDCNUM_SHIFT;
	tp->key_mask[1] = TCAM_V4KEY1_L2RDCNUM;

	tp->key[3] = (u64)sip << TCAM_V4KEY3_SADDR_SHIFT;
	tp->key[3] |= dip;

	tp->key_mask[3] = (u64)sipm << TCAM_V4KEY3_SADDR_SHIFT;
	tp->key_mask[3] |= dipm;

	tp->key[2] |= ((u64)fsp->h_u.tcp_ip4_spec.tos <<
		       TCAM_V4KEY2_TOS_SHIFT);
	tp->key_mask[2] |= ((u64)fsp->m_u.tcp_ip4_spec.tos <<
			    TCAM_V4KEY2_TOS_SHIFT);
	चयन (fsp->flow_type) अणु
	हाल TCP_V4_FLOW:
	हाल UDP_V4_FLOW:
	हाल SCTP_V4_FLOW:
		sport = be16_to_cpu(fsp->h_u.tcp_ip4_spec.psrc);
		spm = be16_to_cpu(fsp->m_u.tcp_ip4_spec.psrc);
		dport = be16_to_cpu(fsp->h_u.tcp_ip4_spec.pdst);
		dpm = be16_to_cpu(fsp->m_u.tcp_ip4_spec.pdst);

		tp->key[2] |= (((u64)sport << 16) | dport);
		tp->key_mask[2] |= (((u64)spm << 16) | dpm);
		niu_ethflow_to_l3proto(fsp->flow_type, &pid);
		अवरोध;
	हाल AH_V4_FLOW:
	हाल ESP_V4_FLOW:
		spi = be32_to_cpu(fsp->h_u.ah_ip4_spec.spi);
		spim = be32_to_cpu(fsp->m_u.ah_ip4_spec.spi);

		tp->key[2] |= spi;
		tp->key_mask[2] |= spim;
		niu_ethflow_to_l3proto(fsp->flow_type, &pid);
		अवरोध;
	हाल IP_USER_FLOW:
		spi = be32_to_cpu(fsp->h_u.usr_ip4_spec.l4_4_bytes);
		spim = be32_to_cpu(fsp->m_u.usr_ip4_spec.l4_4_bytes);

		tp->key[2] |= spi;
		tp->key_mask[2] |= spim;
		pid = fsp->h_u.usr_ip4_spec.proto;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	tp->key[2] |= ((u64)pid << TCAM_V4KEY2_PROTO_SHIFT);
	अगर (pid) अणु
		tp->key_mask[2] |= TCAM_V4KEY2_PROTO;
	पूर्ण
पूर्ण

अटल पूर्णांक niu_add_ethtool_tcam_entry(काष्ठा niu *np,
				      काष्ठा ethtool_rxnfc *nfc)
अणु
	काष्ठा niu_parent *parent = np->parent;
	काष्ठा niu_tcam_entry *tp;
	काष्ठा ethtool_rx_flow_spec *fsp = &nfc->fs;
	काष्ठा niu_rdc_tables *rdc_table = &parent->rdc_group_cfg[np->port];
	पूर्णांक l2_rdc_table = rdc_table->first_table_num;
	u16 idx;
	u64 class;
	अचिन्हित दीर्घ flags;
	पूर्णांक err, ret;

	ret = 0;

	idx = nfc->fs.location;
	अगर (idx >= tcam_get_size(np))
		वापस -EINVAL;

	अगर (fsp->flow_type == IP_USER_FLOW) अणु
		पूर्णांक i;
		पूर्णांक add_usr_cls = 0;
		काष्ठा ethtool_usrip4_spec *uspec = &fsp->h_u.usr_ip4_spec;
		काष्ठा ethtool_usrip4_spec *umask = &fsp->m_u.usr_ip4_spec;

		अगर (uspec->ip_ver != ETH_RX_NFC_IP4)
			वापस -EINVAL;

		niu_lock_parent(np, flags);

		क्रम (i = 0; i < NIU_L3_PROG_CLS; i++) अणु
			अगर (parent->l3_cls[i]) अणु
				अगर (uspec->proto == parent->l3_cls_pid[i]) अणु
					class = parent->l3_cls[i];
					parent->l3_cls_refcnt[i]++;
					add_usr_cls = 1;
					अवरोध;
				पूर्ण
			पूर्ण अन्यथा अणु
				/* Program new user IP class */
				चयन (i) अणु
				हाल 0:
					class = CLASS_CODE_USER_PROG1;
					अवरोध;
				हाल 1:
					class = CLASS_CODE_USER_PROG2;
					अवरोध;
				हाल 2:
					class = CLASS_CODE_USER_PROG3;
					अवरोध;
				हाल 3:
					class = CLASS_CODE_USER_PROG4;
					अवरोध;
				शेष:
					class = CLASS_CODE_UNRECOG;
					अवरोध;
				पूर्ण
				ret = tcam_user_ip_class_set(np, class, 0,
							     uspec->proto,
							     uspec->tos,
							     umask->tos);
				अगर (ret)
					जाओ out;

				ret = tcam_user_ip_class_enable(np, class, 1);
				अगर (ret)
					जाओ out;
				parent->l3_cls[i] = class;
				parent->l3_cls_pid[i] = uspec->proto;
				parent->l3_cls_refcnt[i]++;
				add_usr_cls = 1;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (!add_usr_cls) अणु
			netdev_info(np->dev, "niu%d: %s(): Could not find/insert class for pid %d\n",
				    parent->index, __func__, uspec->proto);
			ret = -EINVAL;
			जाओ out;
		पूर्ण
		niu_unlock_parent(np, flags);
	पूर्ण अन्यथा अणु
		अगर (!niu_ethflow_to_class(fsp->flow_type, &class)) अणु
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	niu_lock_parent(np, flags);

	idx = tcam_get_index(np, idx);
	tp = &parent->tcam[idx];

	स_रखो(tp, 0, माप(*tp));

	/* fill in the tcam key and mask */
	चयन (fsp->flow_type) अणु
	हाल TCP_V4_FLOW:
	हाल UDP_V4_FLOW:
	हाल SCTP_V4_FLOW:
	हाल AH_V4_FLOW:
	हाल ESP_V4_FLOW:
		niu_get_tcamkey_from_ip4fs(fsp, tp, l2_rdc_table, class);
		अवरोध;
	हाल TCP_V6_FLOW:
	हाल UDP_V6_FLOW:
	हाल SCTP_V6_FLOW:
	हाल AH_V6_FLOW:
	हाल ESP_V6_FLOW:
		/* Not yet implemented */
		netdev_info(np->dev, "niu%d: In %s(): flow %d for IPv6 not implemented\n",
			    parent->index, __func__, fsp->flow_type);
		ret = -EINVAL;
		जाओ out;
	हाल IP_USER_FLOW:
		niu_get_tcamkey_from_ip4fs(fsp, tp, l2_rdc_table, class);
		अवरोध;
	शेष:
		netdev_info(np->dev, "niu%d: In %s(): Unknown flow type %d\n",
			    parent->index, __func__, fsp->flow_type);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	/* fill in the assoc data */
	अगर (fsp->ring_cookie == RX_CLS_FLOW_DISC) अणु
		tp->assoc_data = TCAM_ASSOCDATA_DISC;
	पूर्ण अन्यथा अणु
		अगर (fsp->ring_cookie >= np->num_rx_rings) अणु
			netdev_info(np->dev, "niu%d: In %s(): Invalid RX ring %lld\n",
				    parent->index, __func__,
				    (दीर्घ दीर्घ)fsp->ring_cookie);
			ret = -EINVAL;
			जाओ out;
		पूर्ण
		tp->assoc_data = (TCAM_ASSOCDATA_TRES_USE_OFFSET |
				  (fsp->ring_cookie <<
				   TCAM_ASSOCDATA_OFFSET_SHIFT));
	पूर्ण

	err = tcam_ग_लिखो(np, idx, tp->key, tp->key_mask);
	अगर (err) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण
	err = tcam_assoc_ग_लिखो(np, idx, tp->assoc_data);
	अगर (err) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	/* validate the entry */
	tp->valid = 1;
	np->clas.tcam_valid_entries++;
out:
	niu_unlock_parent(np, flags);

	वापस ret;
पूर्ण

अटल पूर्णांक niu_del_ethtool_tcam_entry(काष्ठा niu *np, u32 loc)
अणु
	काष्ठा niu_parent *parent = np->parent;
	काष्ठा niu_tcam_entry *tp;
	u16 idx;
	अचिन्हित दीर्घ flags;
	u64 class;
	पूर्णांक ret = 0;

	अगर (loc >= tcam_get_size(np))
		वापस -EINVAL;

	niu_lock_parent(np, flags);

	idx = tcam_get_index(np, loc);
	tp = &parent->tcam[idx];

	/* अगर the entry is of a user defined class, then update*/
	class = (tp->key[0] & TCAM_V4KEY0_CLASS_CODE) >>
		TCAM_V4KEY0_CLASS_CODE_SHIFT;

	अगर (class >= CLASS_CODE_USER_PROG1 && class <= CLASS_CODE_USER_PROG4) अणु
		पूर्णांक i;
		क्रम (i = 0; i < NIU_L3_PROG_CLS; i++) अणु
			अगर (parent->l3_cls[i] == class) अणु
				parent->l3_cls_refcnt[i]--;
				अगर (!parent->l3_cls_refcnt[i]) अणु
					/* disable class */
					ret = tcam_user_ip_class_enable(np,
									class,
									0);
					अगर (ret)
						जाओ out;
					parent->l3_cls[i] = 0;
					parent->l3_cls_pid[i] = 0;
				पूर्ण
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (i == NIU_L3_PROG_CLS) अणु
			netdev_info(np->dev, "niu%d: In %s(): Usr class 0x%llx not found\n",
				    parent->index, __func__,
				    (अचिन्हित दीर्घ दीर्घ)class);
			ret = -EINVAL;
			जाओ out;
		पूर्ण
	पूर्ण

	ret = tcam_flush(np, idx);
	अगर (ret)
		जाओ out;

	/* invalidate the entry */
	tp->valid = 0;
	np->clas.tcam_valid_entries--;
out:
	niu_unlock_parent(np, flags);

	वापस ret;
पूर्ण

अटल पूर्णांक niu_set_nfc(काष्ठा net_device *dev, काष्ठा ethtool_rxnfc *cmd)
अणु
	काष्ठा niu *np = netdev_priv(dev);
	पूर्णांक ret = 0;

	चयन (cmd->cmd) अणु
	हाल ETHTOOL_SRXFH:
		ret = niu_set_hash_opts(np, cmd);
		अवरोध;
	हाल ETHTOOL_SRXCLSRLINS:
		ret = niu_add_ethtool_tcam_entry(np, cmd);
		अवरोध;
	हाल ETHTOOL_SRXCLSRLDEL:
		ret = niu_del_ethtool_tcam_entry(np, cmd->fs.location);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा अणु
	स्थिर अक्षर string[ETH_GSTRING_LEN];
पूर्ण niu_xmac_stat_keys[] = अणु
	अणु "tx_frames" पूर्ण,
	अणु "tx_bytes" पूर्ण,
	अणु "tx_fifo_errors" पूर्ण,
	अणु "tx_overflow_errors" पूर्ण,
	अणु "tx_max_pkt_size_errors" पूर्ण,
	अणु "tx_underflow_errors" पूर्ण,
	अणु "rx_local_faults" पूर्ण,
	अणु "rx_remote_faults" पूर्ण,
	अणु "rx_link_faults" पूर्ण,
	अणु "rx_align_errors" पूर्ण,
	अणु "rx_frags" पूर्ण,
	अणु "rx_mcasts" पूर्ण,
	अणु "rx_bcasts" पूर्ण,
	अणु "rx_hist_cnt1" पूर्ण,
	अणु "rx_hist_cnt2" पूर्ण,
	अणु "rx_hist_cnt3" पूर्ण,
	अणु "rx_hist_cnt4" पूर्ण,
	अणु "rx_hist_cnt5" पूर्ण,
	अणु "rx_hist_cnt6" पूर्ण,
	अणु "rx_hist_cnt7" पूर्ण,
	अणु "rx_octets" पूर्ण,
	अणु "rx_code_violations" पूर्ण,
	अणु "rx_len_errors" पूर्ण,
	अणु "rx_crc_errors" पूर्ण,
	अणु "rx_underflows" पूर्ण,
	अणु "rx_overflows" पूर्ण,
	अणु "pause_off_state" पूर्ण,
	अणु "pause_on_state" पूर्ण,
	अणु "pause_received" पूर्ण,
पूर्ण;

#घोषणा NUM_XMAC_STAT_KEYS	ARRAY_SIZE(niu_xmac_stat_keys)

अटल स्थिर काष्ठा अणु
	स्थिर अक्षर string[ETH_GSTRING_LEN];
पूर्ण niu_bmac_stat_keys[] = अणु
	अणु "tx_underflow_errors" पूर्ण,
	अणु "tx_max_pkt_size_errors" पूर्ण,
	अणु "tx_bytes" पूर्ण,
	अणु "tx_frames" पूर्ण,
	अणु "rx_overflows" पूर्ण,
	अणु "rx_frames" पूर्ण,
	अणु "rx_align_errors" पूर्ण,
	अणु "rx_crc_errors" पूर्ण,
	अणु "rx_len_errors" पूर्ण,
	अणु "pause_off_state" पूर्ण,
	अणु "pause_on_state" पूर्ण,
	अणु "pause_received" पूर्ण,
पूर्ण;

#घोषणा NUM_BMAC_STAT_KEYS	ARRAY_SIZE(niu_bmac_stat_keys)

अटल स्थिर काष्ठा अणु
	स्थिर अक्षर string[ETH_GSTRING_LEN];
पूर्ण niu_rxchan_stat_keys[] = अणु
	अणु "rx_channel" पूर्ण,
	अणु "rx_packets" पूर्ण,
	अणु "rx_bytes" पूर्ण,
	अणु "rx_dropped" पूर्ण,
	अणु "rx_errors" पूर्ण,
पूर्ण;

#घोषणा NUM_RXCHAN_STAT_KEYS	ARRAY_SIZE(niu_rxchan_stat_keys)

अटल स्थिर काष्ठा अणु
	स्थिर अक्षर string[ETH_GSTRING_LEN];
पूर्ण niu_txchan_stat_keys[] = अणु
	अणु "tx_channel" पूर्ण,
	अणु "tx_packets" पूर्ण,
	अणु "tx_bytes" पूर्ण,
	अणु "tx_errors" पूर्ण,
पूर्ण;

#घोषणा NUM_TXCHAN_STAT_KEYS	ARRAY_SIZE(niu_txchan_stat_keys)

अटल व्योम niu_get_strings(काष्ठा net_device *dev, u32 stringset, u8 *data)
अणु
	काष्ठा niu *np = netdev_priv(dev);
	पूर्णांक i;

	अगर (stringset != ETH_SS_STATS)
		वापस;

	अगर (np->flags & NIU_FLAGS_XMAC) अणु
		स_नकल(data, niu_xmac_stat_keys,
		       माप(niu_xmac_stat_keys));
		data += माप(niu_xmac_stat_keys);
	पूर्ण अन्यथा अणु
		स_नकल(data, niu_bmac_stat_keys,
		       माप(niu_bmac_stat_keys));
		data += माप(niu_bmac_stat_keys);
	पूर्ण
	क्रम (i = 0; i < np->num_rx_rings; i++) अणु
		स_नकल(data, niu_rxchan_stat_keys,
		       माप(niu_rxchan_stat_keys));
		data += माप(niu_rxchan_stat_keys);
	पूर्ण
	क्रम (i = 0; i < np->num_tx_rings; i++) अणु
		स_नकल(data, niu_txchan_stat_keys,
		       माप(niu_txchan_stat_keys));
		data += माप(niu_txchan_stat_keys);
	पूर्ण
पूर्ण

अटल पूर्णांक niu_get_sset_count(काष्ठा net_device *dev, पूर्णांक stringset)
अणु
	काष्ठा niu *np = netdev_priv(dev);

	अगर (stringset != ETH_SS_STATS)
		वापस -EINVAL;

	वापस (np->flags & NIU_FLAGS_XMAC ?
		 NUM_XMAC_STAT_KEYS :
		 NUM_BMAC_STAT_KEYS) +
		(np->num_rx_rings * NUM_RXCHAN_STAT_KEYS) +
		(np->num_tx_rings * NUM_TXCHAN_STAT_KEYS);
पूर्ण

अटल व्योम niu_get_ethtool_stats(काष्ठा net_device *dev,
				  काष्ठा ethtool_stats *stats, u64 *data)
अणु
	काष्ठा niu *np = netdev_priv(dev);
	पूर्णांक i;

	niu_sync_mac_stats(np);
	अगर (np->flags & NIU_FLAGS_XMAC) अणु
		स_नकल(data, &np->mac_stats.xmac,
		       माप(काष्ठा niu_xmac_stats));
		data += (माप(काष्ठा niu_xmac_stats) / माप(u64));
	पूर्ण अन्यथा अणु
		स_नकल(data, &np->mac_stats.bmac,
		       माप(काष्ठा niu_bmac_stats));
		data += (माप(काष्ठा niu_bmac_stats) / माप(u64));
	पूर्ण
	क्रम (i = 0; i < np->num_rx_rings; i++) अणु
		काष्ठा rx_ring_info *rp = &np->rx_rings[i];

		niu_sync_rx_discard_stats(np, rp, 0);

		data[0] = rp->rx_channel;
		data[1] = rp->rx_packets;
		data[2] = rp->rx_bytes;
		data[3] = rp->rx_dropped;
		data[4] = rp->rx_errors;
		data += 5;
	पूर्ण
	क्रम (i = 0; i < np->num_tx_rings; i++) अणु
		काष्ठा tx_ring_info *rp = &np->tx_rings[i];

		data[0] = rp->tx_channel;
		data[1] = rp->tx_packets;
		data[2] = rp->tx_bytes;
		data[3] = rp->tx_errors;
		data += 4;
	पूर्ण
पूर्ण

अटल u64 niu_led_state_save(काष्ठा niu *np)
अणु
	अगर (np->flags & NIU_FLAGS_XMAC)
		वापस nr64_mac(XMAC_CONFIG);
	अन्यथा
		वापस nr64_mac(BMAC_XIF_CONFIG);
पूर्ण

अटल व्योम niu_led_state_restore(काष्ठा niu *np, u64 val)
अणु
	अगर (np->flags & NIU_FLAGS_XMAC)
		nw64_mac(XMAC_CONFIG, val);
	अन्यथा
		nw64_mac(BMAC_XIF_CONFIG, val);
पूर्ण

अटल व्योम niu_क्रमce_led(काष्ठा niu *np, पूर्णांक on)
अणु
	u64 val, reg, bit;

	अगर (np->flags & NIU_FLAGS_XMAC) अणु
		reg = XMAC_CONFIG;
		bit = XMAC_CONFIG_FORCE_LED_ON;
	पूर्ण अन्यथा अणु
		reg = BMAC_XIF_CONFIG;
		bit = BMAC_XIF_CONFIG_LINK_LED;
	पूर्ण

	val = nr64_mac(reg);
	अगर (on)
		val |= bit;
	अन्यथा
		val &= ~bit;
	nw64_mac(reg, val);
पूर्ण

अटल पूर्णांक niu_set_phys_id(काष्ठा net_device *dev,
			   क्रमागत ethtool_phys_id_state state)

अणु
	काष्ठा niu *np = netdev_priv(dev);

	अगर (!netअगर_running(dev))
		वापस -EAGAIN;

	चयन (state) अणु
	हाल ETHTOOL_ID_ACTIVE:
		np->orig_led_state = niu_led_state_save(np);
		वापस 1;	/* cycle on/off once per second */

	हाल ETHTOOL_ID_ON:
		niu_क्रमce_led(np, 1);
		अवरोध;

	हाल ETHTOOL_ID_OFF:
		niu_क्रमce_led(np, 0);
		अवरोध;

	हाल ETHTOOL_ID_INACTIVE:
		niu_led_state_restore(np, np->orig_led_state);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops niu_ethtool_ops = अणु
	.get_drvinfo		= niu_get_drvinfo,
	.get_link		= ethtool_op_get_link,
	.get_msglevel		= niu_get_msglevel,
	.set_msglevel		= niu_set_msglevel,
	.nway_reset		= niu_nway_reset,
	.get_eeprom_len		= niu_get_eeprom_len,
	.get_eeprom		= niu_get_eeprom,
	.get_strings		= niu_get_strings,
	.get_sset_count		= niu_get_sset_count,
	.get_ethtool_stats	= niu_get_ethtool_stats,
	.set_phys_id		= niu_set_phys_id,
	.get_rxnfc		= niu_get_nfc,
	.set_rxnfc		= niu_set_nfc,
	.get_link_ksettings	= niu_get_link_ksettings,
	.set_link_ksettings	= niu_set_link_ksettings,
पूर्ण;

अटल पूर्णांक niu_ldg_assign_ldn(काष्ठा niu *np, काष्ठा niu_parent *parent,
			      पूर्णांक ldg, पूर्णांक ldn)
अणु
	अगर (ldg < NIU_LDG_MIN || ldg > NIU_LDG_MAX)
		वापस -EINVAL;
	अगर (ldn < 0 || ldn > LDN_MAX)
		वापस -EINVAL;

	parent->ldg_map[ldn] = ldg;

	अगर (np->parent->plat_type == PLAT_TYPE_NIU) अणु
		/* On N2 NIU, the ldn-->ldg assignments are setup and fixed by
		 * the firmware, and we're not supposed to change them.
		 * Validate the mapping, because अगर it's wrong we probably
		 * won't get any interrupts and that's painful to debug.
		 */
		अगर (nr64(LDG_NUM(ldn)) != ldg) अणु
			dev_err(np->device, "Port %u, mis-matched LDG assignment for ldn %d, should be %d is %llu\n",
				np->port, ldn, ldg,
				(अचिन्हित दीर्घ दीर्घ) nr64(LDG_NUM(ldn)));
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा
		nw64(LDG_NUM(ldn), ldg);

	वापस 0;
पूर्ण

अटल पूर्णांक niu_set_ldg_समयr_res(काष्ठा niu *np, पूर्णांक res)
अणु
	अगर (res < 0 || res > LDG_TIMER_RES_VAL)
		वापस -EINVAL;


	nw64(LDG_TIMER_RES, res);

	वापस 0;
पूर्ण

अटल पूर्णांक niu_set_ldg_sid(काष्ठा niu *np, पूर्णांक ldg, पूर्णांक func, पूर्णांक vector)
अणु
	अगर ((ldg < NIU_LDG_MIN || ldg > NIU_LDG_MAX) ||
	    (func < 0 || func > 3) ||
	    (vector < 0 || vector > 0x1f))
		वापस -EINVAL;

	nw64(SID(ldg), (func << SID_FUNC_SHIFT) | vector);

	वापस 0;
पूर्ण

अटल पूर्णांक niu_pci_eeprom_पढ़ो(काष्ठा niu *np, u32 addr)
अणु
	u64 frame, frame_base = (ESPC_PIO_STAT_READ_START |
				 (addr << ESPC_PIO_STAT_ADDR_SHIFT));
	पूर्णांक limit;

	अगर (addr > (ESPC_PIO_STAT_ADDR >> ESPC_PIO_STAT_ADDR_SHIFT))
		वापस -EINVAL;

	frame = frame_base;
	nw64(ESPC_PIO_STAT, frame);
	limit = 64;
	करो अणु
		udelay(5);
		frame = nr64(ESPC_PIO_STAT);
		अगर (frame & ESPC_PIO_STAT_READ_END)
			अवरोध;
	पूर्ण जबतक (limit--);
	अगर (!(frame & ESPC_PIO_STAT_READ_END)) अणु
		dev_err(np->device, "EEPROM read timeout frame[%llx]\n",
			(अचिन्हित दीर्घ दीर्घ) frame);
		वापस -ENODEV;
	पूर्ण

	frame = frame_base;
	nw64(ESPC_PIO_STAT, frame);
	limit = 64;
	करो अणु
		udelay(5);
		frame = nr64(ESPC_PIO_STAT);
		अगर (frame & ESPC_PIO_STAT_READ_END)
			अवरोध;
	पूर्ण जबतक (limit--);
	अगर (!(frame & ESPC_PIO_STAT_READ_END)) अणु
		dev_err(np->device, "EEPROM read timeout frame[%llx]\n",
			(अचिन्हित दीर्घ दीर्घ) frame);
		वापस -ENODEV;
	पूर्ण

	frame = nr64(ESPC_PIO_STAT);
	वापस (frame & ESPC_PIO_STAT_DATA) >> ESPC_PIO_STAT_DATA_SHIFT;
पूर्ण

अटल पूर्णांक niu_pci_eeprom_पढ़ो16(काष्ठा niu *np, u32 off)
अणु
	पूर्णांक err = niu_pci_eeprom_पढ़ो(np, off);
	u16 val;

	अगर (err < 0)
		वापस err;
	val = (err << 8);
	err = niu_pci_eeprom_पढ़ो(np, off + 1);
	अगर (err < 0)
		वापस err;
	val |= (err & 0xff);

	वापस val;
पूर्ण

अटल पूर्णांक niu_pci_eeprom_पढ़ो16_swp(काष्ठा niu *np, u32 off)
अणु
	पूर्णांक err = niu_pci_eeprom_पढ़ो(np, off);
	u16 val;

	अगर (err < 0)
		वापस err;

	val = (err & 0xff);
	err = niu_pci_eeprom_पढ़ो(np, off + 1);
	अगर (err < 0)
		वापस err;

	val |= (err & 0xff) << 8;

	वापस val;
पूर्ण

अटल पूर्णांक niu_pci_vpd_get_propname(काष्ठा niu *np, u32 off, अक्षर *namebuf,
				    पूर्णांक namebuf_len)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < namebuf_len; i++) अणु
		पूर्णांक err = niu_pci_eeprom_पढ़ो(np, off + i);
		अगर (err < 0)
			वापस err;
		*namebuf++ = err;
		अगर (!err)
			अवरोध;
	पूर्ण
	अगर (i >= namebuf_len)
		वापस -EINVAL;

	वापस i + 1;
पूर्ण

अटल व्योम niu_vpd_parse_version(काष्ठा niu *np)
अणु
	काष्ठा niu_vpd *vpd = &np->vpd;
	पूर्णांक len = म_माप(vpd->version) + 1;
	स्थिर अक्षर *s = vpd->version;
	पूर्णांक i;

	क्रम (i = 0; i < len - 5; i++) अणु
		अगर (!म_भेदन(s + i, "FCode ", 6))
			अवरोध;
	पूर्ण
	अगर (i >= len - 5)
		वापस;

	s += i + 5;
	माला_पूछो(s, "%d.%d", &vpd->fcode_major, &vpd->fcode_minor);

	netअगर_prपूर्णांकk(np, probe, KERN_DEBUG, np->dev,
		     "VPD_SCAN: FCODE major(%d) minor(%d)\n",
		     vpd->fcode_major, vpd->fcode_minor);
	अगर (vpd->fcode_major > NIU_VPD_MIN_MAJOR ||
	    (vpd->fcode_major == NIU_VPD_MIN_MAJOR &&
	     vpd->fcode_minor >= NIU_VPD_MIN_MINOR))
		np->flags |= NIU_FLAGS_VPD_VALID;
पूर्ण

/* ESPC_PIO_EN_ENABLE must be set */
अटल पूर्णांक niu_pci_vpd_scan_props(काष्ठा niu *np, u32 start, u32 end)
अणु
	अचिन्हित पूर्णांक found_mask = 0;
#घोषणा FOUND_MASK_MODEL	0x00000001
#घोषणा FOUND_MASK_BMODEL	0x00000002
#घोषणा FOUND_MASK_VERS		0x00000004
#घोषणा FOUND_MASK_MAC		0x00000008
#घोषणा FOUND_MASK_NMAC		0x00000010
#घोषणा FOUND_MASK_PHY		0x00000020
#घोषणा FOUND_MASK_ALL		0x0000003f

	netअगर_prपूर्णांकk(np, probe, KERN_DEBUG, np->dev,
		     "VPD_SCAN: start[%x] end[%x]\n", start, end);
	जबतक (start < end) अणु
		पूर्णांक len, err, prop_len;
		अक्षर namebuf[64];
		u8 *prop_buf;
		पूर्णांक max_len;

		अगर (found_mask == FOUND_MASK_ALL) अणु
			niu_vpd_parse_version(np);
			वापस 1;
		पूर्ण

		err = niu_pci_eeprom_पढ़ो(np, start + 2);
		अगर (err < 0)
			वापस err;
		len = err;
		start += 3;

		prop_len = niu_pci_eeprom_पढ़ो(np, start + 4);
		अगर (prop_len < 0)
			वापस prop_len;
		err = niu_pci_vpd_get_propname(np, start + 5, namebuf, 64);
		अगर (err < 0)
			वापस err;

		prop_buf = शून्य;
		max_len = 0;
		अगर (!म_भेद(namebuf, "model")) अणु
			prop_buf = np->vpd.model;
			max_len = NIU_VPD_MODEL_MAX;
			found_mask |= FOUND_MASK_MODEL;
		पूर्ण अन्यथा अगर (!म_भेद(namebuf, "board-model")) अणु
			prop_buf = np->vpd.board_model;
			max_len = NIU_VPD_BD_MODEL_MAX;
			found_mask |= FOUND_MASK_BMODEL;
		पूर्ण अन्यथा अगर (!म_भेद(namebuf, "version")) अणु
			prop_buf = np->vpd.version;
			max_len = NIU_VPD_VERSION_MAX;
			found_mask |= FOUND_MASK_VERS;
		पूर्ण अन्यथा अगर (!म_भेद(namebuf, "local-mac-address")) अणु
			prop_buf = np->vpd.local_mac;
			max_len = ETH_ALEN;
			found_mask |= FOUND_MASK_MAC;
		पूर्ण अन्यथा अगर (!म_भेद(namebuf, "num-mac-addresses")) अणु
			prop_buf = &np->vpd.mac_num;
			max_len = 1;
			found_mask |= FOUND_MASK_NMAC;
		पूर्ण अन्यथा अगर (!म_भेद(namebuf, "phy-type")) अणु
			prop_buf = np->vpd.phy_type;
			max_len = NIU_VPD_PHY_TYPE_MAX;
			found_mask |= FOUND_MASK_PHY;
		पूर्ण

		अगर (max_len && prop_len > max_len) अणु
			dev_err(np->device, "Property '%s' length (%d) is too long\n", namebuf, prop_len);
			वापस -EINVAL;
		पूर्ण

		अगर (prop_buf) अणु
			u32 off = start + 5 + err;
			पूर्णांक i;

			netअगर_prपूर्णांकk(np, probe, KERN_DEBUG, np->dev,
				     "VPD_SCAN: Reading in property [%s] len[%d]\n",
				     namebuf, prop_len);
			क्रम (i = 0; i < prop_len; i++) अणु
				err =  niu_pci_eeprom_पढ़ो(np, off + i);
				अगर (err < 0)
					वापस err;
				*prop_buf++ = err;
			पूर्ण
		पूर्ण

		start += len;
	पूर्ण

	वापस 0;
पूर्ण

/* ESPC_PIO_EN_ENABLE must be set */
अटल पूर्णांक niu_pci_vpd_fetch(काष्ठा niu *np, u32 start)
अणु
	u32 offset;
	पूर्णांक err;

	err = niu_pci_eeprom_पढ़ो16_swp(np, start + 1);
	अगर (err < 0)
		वापस err;

	offset = err + 3;

	जबतक (start + offset < ESPC_EEPROM_SIZE) अणु
		u32 here = start + offset;
		u32 end;

		err = niu_pci_eeprom_पढ़ो(np, here);
		अगर (err < 0)
			वापस err;
		अगर (err != 0x90)
			वापस -EINVAL;

		err = niu_pci_eeprom_पढ़ो16_swp(np, here + 1);
		अगर (err < 0)
			वापस err;

		here = start + offset + 3;
		end = start + offset + err;

		offset += err;

		err = niu_pci_vpd_scan_props(np, here, end);
		अगर (err < 0)
			वापस err;
		अगर (err == 1)
			वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/* ESPC_PIO_EN_ENABLE must be set */
अटल u32 niu_pci_vpd_offset(काष्ठा niu *np)
अणु
	u32 start = 0, end = ESPC_EEPROM_SIZE, ret;
	पूर्णांक err;

	जबतक (start < end) अणु
		ret = start;

		/* ROM header signature?  */
		err = niu_pci_eeprom_पढ़ो16(np, start +  0);
		अगर (err != 0x55aa)
			वापस 0;

		/* Apply offset to PCI data काष्ठाure.  */
		err = niu_pci_eeprom_पढ़ो16(np, start + 23);
		अगर (err < 0)
			वापस 0;
		start += err;

		/* Check क्रम "PCIR" signature.  */
		err = niu_pci_eeprom_पढ़ो16(np, start +  0);
		अगर (err != 0x5043)
			वापस 0;
		err = niu_pci_eeprom_पढ़ो16(np, start +  2);
		अगर (err != 0x4952)
			वापस 0;

		/* Check क्रम OBP image type.  */
		err = niu_pci_eeprom_पढ़ो(np, start + 20);
		अगर (err < 0)
			वापस 0;
		अगर (err != 0x01) अणु
			err = niu_pci_eeprom_पढ़ो(np, ret + 2);
			अगर (err < 0)
				वापस 0;

			start = ret + (err * 512);
			जारी;
		पूर्ण

		err = niu_pci_eeprom_पढ़ो16_swp(np, start + 8);
		अगर (err < 0)
			वापस err;
		ret += err;

		err = niu_pci_eeprom_पढ़ो(np, ret + 0);
		अगर (err != 0x82)
			वापस 0;

		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक niu_phy_type_prop_decode(काष्ठा niu *np, स्थिर अक्षर *phy_prop)
अणु
	अगर (!म_भेद(phy_prop, "mif")) अणु
		/* 1G copper, MII */
		np->flags &= ~(NIU_FLAGS_FIBER |
			       NIU_FLAGS_10G);
		np->mac_xcvr = MAC_XCVR_MII;
	पूर्ण अन्यथा अगर (!म_भेद(phy_prop, "xgf")) अणु
		/* 10G fiber, XPCS */
		np->flags |= (NIU_FLAGS_10G |
			      NIU_FLAGS_FIBER);
		np->mac_xcvr = MAC_XCVR_XPCS;
	पूर्ण अन्यथा अगर (!म_भेद(phy_prop, "pcs")) अणु
		/* 1G fiber, PCS */
		np->flags &= ~NIU_FLAGS_10G;
		np->flags |= NIU_FLAGS_FIBER;
		np->mac_xcvr = MAC_XCVR_PCS;
	पूर्ण अन्यथा अगर (!म_भेद(phy_prop, "xgc")) अणु
		/* 10G copper, XPCS */
		np->flags |= NIU_FLAGS_10G;
		np->flags &= ~NIU_FLAGS_FIBER;
		np->mac_xcvr = MAC_XCVR_XPCS;
	पूर्ण अन्यथा अगर (!म_भेद(phy_prop, "xgsd") || !म_भेद(phy_prop, "gsd")) अणु
		/* 10G Serdes or 1G Serdes, शेष to 10G */
		np->flags |= NIU_FLAGS_10G;
		np->flags &= ~NIU_FLAGS_FIBER;
		np->flags |= NIU_FLAGS_XCVR_SERDES;
		np->mac_xcvr = MAC_XCVR_XPCS;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक niu_pci_vpd_get_nports(काष्ठा niu *np)
अणु
	पूर्णांक ports = 0;

	अगर ((!म_भेद(np->vpd.model, NIU_QGC_LP_MDL_STR)) ||
	    (!म_भेद(np->vpd.model, NIU_QGC_PEM_MDL_STR)) ||
	    (!म_भेद(np->vpd.model, NIU_MARAMBA_MDL_STR)) ||
	    (!म_भेद(np->vpd.model, NIU_KIMI_MDL_STR)) ||
	    (!म_भेद(np->vpd.model, NIU_ALONSO_MDL_STR))) अणु
		ports = 4;
	पूर्ण अन्यथा अगर ((!म_भेद(np->vpd.model, NIU_2XGF_LP_MDL_STR)) ||
		   (!म_भेद(np->vpd.model, NIU_2XGF_PEM_MDL_STR)) ||
		   (!म_भेद(np->vpd.model, NIU_FOXXY_MDL_STR)) ||
		   (!म_भेद(np->vpd.model, NIU_2XGF_MRVL_MDL_STR))) अणु
		ports = 2;
	पूर्ण

	वापस ports;
पूर्ण

अटल व्योम niu_pci_vpd_validate(काष्ठा niu *np)
अणु
	काष्ठा net_device *dev = np->dev;
	काष्ठा niu_vpd *vpd = &np->vpd;
	u8 val8;

	अगर (!is_valid_ether_addr(&vpd->local_mac[0])) अणु
		dev_err(np->device, "VPD MAC invalid, falling back to SPROM\n");

		np->flags &= ~NIU_FLAGS_VPD_VALID;
		वापस;
	पूर्ण

	अगर (!म_भेद(np->vpd.model, NIU_ALONSO_MDL_STR) ||
	    !म_भेद(np->vpd.model, NIU_KIMI_MDL_STR)) अणु
		np->flags |= NIU_FLAGS_10G;
		np->flags &= ~NIU_FLAGS_FIBER;
		np->flags |= NIU_FLAGS_XCVR_SERDES;
		np->mac_xcvr = MAC_XCVR_PCS;
		अगर (np->port > 1) अणु
			np->flags |= NIU_FLAGS_FIBER;
			np->flags &= ~NIU_FLAGS_10G;
		पूर्ण
		अगर (np->flags & NIU_FLAGS_10G)
			np->mac_xcvr = MAC_XCVR_XPCS;
	पूर्ण अन्यथा अगर (!म_भेद(np->vpd.model, NIU_FOXXY_MDL_STR)) अणु
		np->flags |= (NIU_FLAGS_10G | NIU_FLAGS_FIBER |
			      NIU_FLAGS_HOTPLUG_PHY);
	पूर्ण अन्यथा अगर (niu_phy_type_prop_decode(np, np->vpd.phy_type)) अणु
		dev_err(np->device, "Illegal phy string [%s]\n",
			np->vpd.phy_type);
		dev_err(np->device, "Falling back to SPROM\n");
		np->flags &= ~NIU_FLAGS_VPD_VALID;
		वापस;
	पूर्ण

	स_नकल(dev->dev_addr, vpd->local_mac, ETH_ALEN);

	val8 = dev->dev_addr[5];
	dev->dev_addr[5] += np->port;
	अगर (dev->dev_addr[5] < val8)
		dev->dev_addr[4]++;
पूर्ण

अटल पूर्णांक niu_pci_probe_sprom(काष्ठा niu *np)
अणु
	काष्ठा net_device *dev = np->dev;
	पूर्णांक len, i;
	u64 val, sum;
	u8 val8;

	val = (nr64(ESPC_VER_IMGSZ) & ESPC_VER_IMGSZ_IMGSZ);
	val >>= ESPC_VER_IMGSZ_IMGSZ_SHIFT;
	len = val / 4;

	np->eeprom_len = len;

	netअगर_prपूर्णांकk(np, probe, KERN_DEBUG, np->dev,
		     "SPROM: Image size %llu\n", (अचिन्हित दीर्घ दीर्घ)val);

	sum = 0;
	क्रम (i = 0; i < len; i++) अणु
		val = nr64(ESPC_NCR(i));
		sum += (val >>  0) & 0xff;
		sum += (val >>  8) & 0xff;
		sum += (val >> 16) & 0xff;
		sum += (val >> 24) & 0xff;
	पूर्ण
	netअगर_prपूर्णांकk(np, probe, KERN_DEBUG, np->dev,
		     "SPROM: Checksum %x\n", (पूर्णांक)(sum & 0xff));
	अगर ((sum & 0xff) != 0xab) अणु
		dev_err(np->device, "Bad SPROM checksum (%x, should be 0xab)\n", (पूर्णांक)(sum & 0xff));
		वापस -EINVAL;
	पूर्ण

	val = nr64(ESPC_PHY_TYPE);
	चयन (np->port) अणु
	हाल 0:
		val8 = (val & ESPC_PHY_TYPE_PORT0) >>
			ESPC_PHY_TYPE_PORT0_SHIFT;
		अवरोध;
	हाल 1:
		val8 = (val & ESPC_PHY_TYPE_PORT1) >>
			ESPC_PHY_TYPE_PORT1_SHIFT;
		अवरोध;
	हाल 2:
		val8 = (val & ESPC_PHY_TYPE_PORT2) >>
			ESPC_PHY_TYPE_PORT2_SHIFT;
		अवरोध;
	हाल 3:
		val8 = (val & ESPC_PHY_TYPE_PORT3) >>
			ESPC_PHY_TYPE_PORT3_SHIFT;
		अवरोध;
	शेष:
		dev_err(np->device, "Bogus port number %u\n",
			np->port);
		वापस -EINVAL;
	पूर्ण
	netअगर_prपूर्णांकk(np, probe, KERN_DEBUG, np->dev,
		     "SPROM: PHY type %x\n", val8);

	चयन (val8) अणु
	हाल ESPC_PHY_TYPE_1G_COPPER:
		/* 1G copper, MII */
		np->flags &= ~(NIU_FLAGS_FIBER |
			       NIU_FLAGS_10G);
		np->mac_xcvr = MAC_XCVR_MII;
		अवरोध;

	हाल ESPC_PHY_TYPE_1G_FIBER:
		/* 1G fiber, PCS */
		np->flags &= ~NIU_FLAGS_10G;
		np->flags |= NIU_FLAGS_FIBER;
		np->mac_xcvr = MAC_XCVR_PCS;
		अवरोध;

	हाल ESPC_PHY_TYPE_10G_COPPER:
		/* 10G copper, XPCS */
		np->flags |= NIU_FLAGS_10G;
		np->flags &= ~NIU_FLAGS_FIBER;
		np->mac_xcvr = MAC_XCVR_XPCS;
		अवरोध;

	हाल ESPC_PHY_TYPE_10G_FIBER:
		/* 10G fiber, XPCS */
		np->flags |= (NIU_FLAGS_10G |
			      NIU_FLAGS_FIBER);
		np->mac_xcvr = MAC_XCVR_XPCS;
		अवरोध;

	शेष:
		dev_err(np->device, "Bogus SPROM phy type %u\n", val8);
		वापस -EINVAL;
	पूर्ण

	val = nr64(ESPC_MAC_ADDR0);
	netअगर_prपूर्णांकk(np, probe, KERN_DEBUG, np->dev,
		     "SPROM: MAC_ADDR0[%08llx]\n", (अचिन्हित दीर्घ दीर्घ)val);
	dev->dev_addr[0] = (val >>  0) & 0xff;
	dev->dev_addr[1] = (val >>  8) & 0xff;
	dev->dev_addr[2] = (val >> 16) & 0xff;
	dev->dev_addr[3] = (val >> 24) & 0xff;

	val = nr64(ESPC_MAC_ADDR1);
	netअगर_prपूर्णांकk(np, probe, KERN_DEBUG, np->dev,
		     "SPROM: MAC_ADDR1[%08llx]\n", (अचिन्हित दीर्घ दीर्घ)val);
	dev->dev_addr[4] = (val >>  0) & 0xff;
	dev->dev_addr[5] = (val >>  8) & 0xff;

	अगर (!is_valid_ether_addr(&dev->dev_addr[0])) अणु
		dev_err(np->device, "SPROM MAC address invalid [ %pM ]\n",
			dev->dev_addr);
		वापस -EINVAL;
	पूर्ण

	val8 = dev->dev_addr[5];
	dev->dev_addr[5] += np->port;
	अगर (dev->dev_addr[5] < val8)
		dev->dev_addr[4]++;

	val = nr64(ESPC_MOD_STR_LEN);
	netअगर_prपूर्णांकk(np, probe, KERN_DEBUG, np->dev,
		     "SPROM: MOD_STR_LEN[%llu]\n", (अचिन्हित दीर्घ दीर्घ)val);
	अगर (val >= 8 * 4)
		वापस -EINVAL;

	क्रम (i = 0; i < val; i += 4) अणु
		u64 पंचांगp = nr64(ESPC_NCR(5 + (i / 4)));

		np->vpd.model[i + 3] = (पंचांगp >>  0) & 0xff;
		np->vpd.model[i + 2] = (पंचांगp >>  8) & 0xff;
		np->vpd.model[i + 1] = (पंचांगp >> 16) & 0xff;
		np->vpd.model[i + 0] = (पंचांगp >> 24) & 0xff;
	पूर्ण
	np->vpd.model[val] = '\0';

	val = nr64(ESPC_BD_MOD_STR_LEN);
	netअगर_prपूर्णांकk(np, probe, KERN_DEBUG, np->dev,
		     "SPROM: BD_MOD_STR_LEN[%llu]\n", (अचिन्हित दीर्घ दीर्घ)val);
	अगर (val >= 4 * 4)
		वापस -EINVAL;

	क्रम (i = 0; i < val; i += 4) अणु
		u64 पंचांगp = nr64(ESPC_NCR(14 + (i / 4)));

		np->vpd.board_model[i + 3] = (पंचांगp >>  0) & 0xff;
		np->vpd.board_model[i + 2] = (पंचांगp >>  8) & 0xff;
		np->vpd.board_model[i + 1] = (पंचांगp >> 16) & 0xff;
		np->vpd.board_model[i + 0] = (पंचांगp >> 24) & 0xff;
	पूर्ण
	np->vpd.board_model[val] = '\0';

	np->vpd.mac_num =
		nr64(ESPC_NUM_PORTS_MACS) & ESPC_NUM_PORTS_MACS_VAL;
	netअगर_prपूर्णांकk(np, probe, KERN_DEBUG, np->dev,
		     "SPROM: NUM_PORTS_MACS[%d]\n", np->vpd.mac_num);

	वापस 0;
पूर्ण

अटल पूर्णांक niu_get_and_validate_port(काष्ठा niu *np)
अणु
	काष्ठा niu_parent *parent = np->parent;

	अगर (np->port <= 1)
		np->flags |= NIU_FLAGS_XMAC;

	अगर (!parent->num_ports) अणु
		अगर (parent->plat_type == PLAT_TYPE_NIU) अणु
			parent->num_ports = 2;
		पूर्ण अन्यथा अणु
			parent->num_ports = niu_pci_vpd_get_nports(np);
			अगर (!parent->num_ports) अणु
				/* Fall back to SPROM as last resort.
				 * This will fail on most cards.
				 */
				parent->num_ports = nr64(ESPC_NUM_PORTS_MACS) &
					ESPC_NUM_PORTS_MACS_VAL;

				/* All of the current probing methods fail on
				 * Maramba on-board parts.
				 */
				अगर (!parent->num_ports)
					parent->num_ports = 4;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (np->port >= parent->num_ports)
		वापस -ENODEV;

	वापस 0;
पूर्ण

अटल पूर्णांक phy_record(काष्ठा niu_parent *parent, काष्ठा phy_probe_info *p,
		      पूर्णांक dev_id_1, पूर्णांक dev_id_2, u8 phy_port, पूर्णांक type)
अणु
	u32 id = (dev_id_1 << 16) | dev_id_2;
	u8 idx;

	अगर (dev_id_1 < 0 || dev_id_2 < 0)
		वापस 0;
	अगर (type == PHY_TYPE_PMA_PMD || type == PHY_TYPE_PCS) अणु
		/* Because of the NIU_PHY_ID_MASK being applied, the 8704
		 * test covers the 8706 as well.
		 */
		अगर (((id & NIU_PHY_ID_MASK) != NIU_PHY_ID_BCM8704) &&
		    ((id & NIU_PHY_ID_MASK) != NIU_PHY_ID_MRVL88X2011))
			वापस 0;
	पूर्ण अन्यथा अणु
		अगर ((id & NIU_PHY_ID_MASK) != NIU_PHY_ID_BCM5464R)
			वापस 0;
	पूर्ण

	pr_info("niu%d: Found PHY %08x type %s at phy_port %u\n",
		parent->index, id,
		type == PHY_TYPE_PMA_PMD ? "PMA/PMD" :
		type == PHY_TYPE_PCS ? "PCS" : "MII",
		phy_port);

	अगर (p->cur[type] >= NIU_MAX_PORTS) अणु
		pr_err("Too many PHY ports\n");
		वापस -EINVAL;
	पूर्ण
	idx = p->cur[type];
	p->phy_id[type][idx] = id;
	p->phy_port[type][idx] = phy_port;
	p->cur[type] = idx + 1;
	वापस 0;
पूर्ण

अटल पूर्णांक port_has_10g(काष्ठा phy_probe_info *p, पूर्णांक port)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < p->cur[PHY_TYPE_PMA_PMD]; i++) अणु
		अगर (p->phy_port[PHY_TYPE_PMA_PMD][i] == port)
			वापस 1;
	पूर्ण
	क्रम (i = 0; i < p->cur[PHY_TYPE_PCS]; i++) अणु
		अगर (p->phy_port[PHY_TYPE_PCS][i] == port)
			वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक count_10g_ports(काष्ठा phy_probe_info *p, पूर्णांक *lowest)
अणु
	पूर्णांक port, cnt;

	cnt = 0;
	*lowest = 32;
	क्रम (port = 8; port < 32; port++) अणु
		अगर (port_has_10g(p, port)) अणु
			अगर (!cnt)
				*lowest = port;
			cnt++;
		पूर्ण
	पूर्ण

	वापस cnt;
पूर्ण

अटल पूर्णांक count_1g_ports(काष्ठा phy_probe_info *p, पूर्णांक *lowest)
अणु
	*lowest = 32;
	अगर (p->cur[PHY_TYPE_MII])
		*lowest = p->phy_port[PHY_TYPE_MII][0];

	वापस p->cur[PHY_TYPE_MII];
पूर्ण

अटल व्योम niu_n2_भागide_channels(काष्ठा niu_parent *parent)
अणु
	पूर्णांक num_ports = parent->num_ports;
	पूर्णांक i;

	क्रम (i = 0; i < num_ports; i++) अणु
		parent->rxchan_per_port[i] = (16 / num_ports);
		parent->txchan_per_port[i] = (16 / num_ports);

		pr_info("niu%d: Port %u [%u RX chans] [%u TX chans]\n",
			parent->index, i,
			parent->rxchan_per_port[i],
			parent->txchan_per_port[i]);
	पूर्ण
पूर्ण

अटल व्योम niu_भागide_channels(काष्ठा niu_parent *parent,
				पूर्णांक num_10g, पूर्णांक num_1g)
अणु
	पूर्णांक num_ports = parent->num_ports;
	पूर्णांक rx_chans_per_10g, rx_chans_per_1g;
	पूर्णांक tx_chans_per_10g, tx_chans_per_1g;
	पूर्णांक i, tot_rx, tot_tx;

	अगर (!num_10g || !num_1g) अणु
		rx_chans_per_10g = rx_chans_per_1g =
			(NIU_NUM_RXCHAN / num_ports);
		tx_chans_per_10g = tx_chans_per_1g =
			(NIU_NUM_TXCHAN / num_ports);
	पूर्ण अन्यथा अणु
		rx_chans_per_1g = NIU_NUM_RXCHAN / 8;
		rx_chans_per_10g = (NIU_NUM_RXCHAN -
				    (rx_chans_per_1g * num_1g)) /
			num_10g;

		tx_chans_per_1g = NIU_NUM_TXCHAN / 6;
		tx_chans_per_10g = (NIU_NUM_TXCHAN -
				    (tx_chans_per_1g * num_1g)) /
			num_10g;
	पूर्ण

	tot_rx = tot_tx = 0;
	क्रम (i = 0; i < num_ports; i++) अणु
		पूर्णांक type = phy_decode(parent->port_phy, i);

		अगर (type == PORT_TYPE_10G) अणु
			parent->rxchan_per_port[i] = rx_chans_per_10g;
			parent->txchan_per_port[i] = tx_chans_per_10g;
		पूर्ण अन्यथा अणु
			parent->rxchan_per_port[i] = rx_chans_per_1g;
			parent->txchan_per_port[i] = tx_chans_per_1g;
		पूर्ण
		pr_info("niu%d: Port %u [%u RX chans] [%u TX chans]\n",
			parent->index, i,
			parent->rxchan_per_port[i],
			parent->txchan_per_port[i]);
		tot_rx += parent->rxchan_per_port[i];
		tot_tx += parent->txchan_per_port[i];
	पूर्ण

	अगर (tot_rx > NIU_NUM_RXCHAN) अणु
		pr_err("niu%d: Too many RX channels (%d), resetting to one per port\n",
		       parent->index, tot_rx);
		क्रम (i = 0; i < num_ports; i++)
			parent->rxchan_per_port[i] = 1;
	पूर्ण
	अगर (tot_tx > NIU_NUM_TXCHAN) अणु
		pr_err("niu%d: Too many TX channels (%d), resetting to one per port\n",
		       parent->index, tot_tx);
		क्रम (i = 0; i < num_ports; i++)
			parent->txchan_per_port[i] = 1;
	पूर्ण
	अगर (tot_rx < NIU_NUM_RXCHAN || tot_tx < NIU_NUM_TXCHAN) अणु
		pr_warn("niu%d: Driver bug, wasted channels, RX[%d] TX[%d]\n",
			parent->index, tot_rx, tot_tx);
	पूर्ण
पूर्ण

अटल व्योम niu_भागide_rdc_groups(काष्ठा niu_parent *parent,
				  पूर्णांक num_10g, पूर्णांक num_1g)
अणु
	पूर्णांक i, num_ports = parent->num_ports;
	पूर्णांक rdc_group, rdc_groups_per_port;
	पूर्णांक rdc_channel_base;

	rdc_group = 0;
	rdc_groups_per_port = NIU_NUM_RDC_TABLES / num_ports;

	rdc_channel_base = 0;

	क्रम (i = 0; i < num_ports; i++) अणु
		काष्ठा niu_rdc_tables *tp = &parent->rdc_group_cfg[i];
		पूर्णांक grp, num_channels = parent->rxchan_per_port[i];
		पूर्णांक this_channel_offset;

		tp->first_table_num = rdc_group;
		tp->num_tables = rdc_groups_per_port;
		this_channel_offset = 0;
		क्रम (grp = 0; grp < tp->num_tables; grp++) अणु
			काष्ठा rdc_table *rt = &tp->tables[grp];
			पूर्णांक slot;

			pr_info("niu%d: Port %d RDC tbl(%d) [ ",
				parent->index, i, tp->first_table_num + grp);
			क्रम (slot = 0; slot < NIU_RDC_TABLE_SLOTS; slot++) अणु
				rt->rxdma_channel[slot] =
					rdc_channel_base + this_channel_offset;

				pr_cont("%d ", rt->rxdma_channel[slot]);

				अगर (++this_channel_offset == num_channels)
					this_channel_offset = 0;
			पूर्ण
			pr_cont("]\n");
		पूर्ण

		parent->rdc_शेष[i] = rdc_channel_base;

		rdc_channel_base += num_channels;
		rdc_group += rdc_groups_per_port;
	पूर्ण
पूर्ण

अटल पूर्णांक fill_phy_probe_info(काष्ठा niu *np, काष्ठा niu_parent *parent,
			       काष्ठा phy_probe_info *info)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक port, err;

	स_रखो(info, 0, माप(*info));

	/* Port 0 to 7 are reserved क्रम onboard Serdes, probe the rest.  */
	niu_lock_parent(np, flags);
	err = 0;
	क्रम (port = 8; port < 32; port++) अणु
		पूर्णांक dev_id_1, dev_id_2;

		dev_id_1 = mdio_पढ़ो(np, port,
				     NIU_PMA_PMD_DEV_ADDR, MII_PHYSID1);
		dev_id_2 = mdio_पढ़ो(np, port,
				     NIU_PMA_PMD_DEV_ADDR, MII_PHYSID2);
		err = phy_record(parent, info, dev_id_1, dev_id_2, port,
				 PHY_TYPE_PMA_PMD);
		अगर (err)
			अवरोध;
		dev_id_1 = mdio_पढ़ो(np, port,
				     NIU_PCS_DEV_ADDR, MII_PHYSID1);
		dev_id_2 = mdio_पढ़ो(np, port,
				     NIU_PCS_DEV_ADDR, MII_PHYSID2);
		err = phy_record(parent, info, dev_id_1, dev_id_2, port,
				 PHY_TYPE_PCS);
		अगर (err)
			अवरोध;
		dev_id_1 = mii_पढ़ो(np, port, MII_PHYSID1);
		dev_id_2 = mii_पढ़ो(np, port, MII_PHYSID2);
		err = phy_record(parent, info, dev_id_1, dev_id_2, port,
				 PHY_TYPE_MII);
		अगर (err)
			अवरोध;
	पूर्ण
	niu_unlock_parent(np, flags);

	वापस err;
पूर्ण

अटल पूर्णांक walk_phys(काष्ठा niu *np, काष्ठा niu_parent *parent)
अणु
	काष्ठा phy_probe_info *info = &parent->phy_probe_info;
	पूर्णांक lowest_10g, lowest_1g;
	पूर्णांक num_10g, num_1g;
	u32 val;
	पूर्णांक err;

	num_10g = num_1g = 0;

	अगर (!म_भेद(np->vpd.model, NIU_ALONSO_MDL_STR) ||
	    !म_भेद(np->vpd.model, NIU_KIMI_MDL_STR)) अणु
		num_10g = 0;
		num_1g = 2;
		parent->plat_type = PLAT_TYPE_ATCA_CP3220;
		parent->num_ports = 4;
		val = (phy_encode(PORT_TYPE_1G, 0) |
		       phy_encode(PORT_TYPE_1G, 1) |
		       phy_encode(PORT_TYPE_1G, 2) |
		       phy_encode(PORT_TYPE_1G, 3));
	पूर्ण अन्यथा अगर (!म_भेद(np->vpd.model, NIU_FOXXY_MDL_STR)) अणु
		num_10g = 2;
		num_1g = 0;
		parent->num_ports = 2;
		val = (phy_encode(PORT_TYPE_10G, 0) |
		       phy_encode(PORT_TYPE_10G, 1));
	पूर्ण अन्यथा अगर ((np->flags & NIU_FLAGS_XCVR_SERDES) &&
		   (parent->plat_type == PLAT_TYPE_NIU)) अणु
		/* this is the Monza हाल */
		अगर (np->flags & NIU_FLAGS_10G) अणु
			val = (phy_encode(PORT_TYPE_10G, 0) |
			       phy_encode(PORT_TYPE_10G, 1));
		पूर्ण अन्यथा अणु
			val = (phy_encode(PORT_TYPE_1G, 0) |
			       phy_encode(PORT_TYPE_1G, 1));
		पूर्ण
	पूर्ण अन्यथा अणु
		err = fill_phy_probe_info(np, parent, info);
		अगर (err)
			वापस err;

		num_10g = count_10g_ports(info, &lowest_10g);
		num_1g = count_1g_ports(info, &lowest_1g);

		चयन ((num_10g << 4) | num_1g) अणु
		हाल 0x24:
			अगर (lowest_1g == 10)
				parent->plat_type = PLAT_TYPE_VF_P0;
			अन्यथा अगर (lowest_1g == 26)
				parent->plat_type = PLAT_TYPE_VF_P1;
			अन्यथा
				जाओ unknown_vg_1g_port;

			fallthrough;
		हाल 0x22:
			val = (phy_encode(PORT_TYPE_10G, 0) |
			       phy_encode(PORT_TYPE_10G, 1) |
			       phy_encode(PORT_TYPE_1G, 2) |
			       phy_encode(PORT_TYPE_1G, 3));
			अवरोध;

		हाल 0x20:
			val = (phy_encode(PORT_TYPE_10G, 0) |
			       phy_encode(PORT_TYPE_10G, 1));
			अवरोध;

		हाल 0x10:
			val = phy_encode(PORT_TYPE_10G, np->port);
			अवरोध;

		हाल 0x14:
			अगर (lowest_1g == 10)
				parent->plat_type = PLAT_TYPE_VF_P0;
			अन्यथा अगर (lowest_1g == 26)
				parent->plat_type = PLAT_TYPE_VF_P1;
			अन्यथा
				जाओ unknown_vg_1g_port;

			fallthrough;
		हाल 0x13:
			अगर ((lowest_10g & 0x7) == 0)
				val = (phy_encode(PORT_TYPE_10G, 0) |
				       phy_encode(PORT_TYPE_1G, 1) |
				       phy_encode(PORT_TYPE_1G, 2) |
				       phy_encode(PORT_TYPE_1G, 3));
			अन्यथा
				val = (phy_encode(PORT_TYPE_1G, 0) |
				       phy_encode(PORT_TYPE_10G, 1) |
				       phy_encode(PORT_TYPE_1G, 2) |
				       phy_encode(PORT_TYPE_1G, 3));
			अवरोध;

		हाल 0x04:
			अगर (lowest_1g == 10)
				parent->plat_type = PLAT_TYPE_VF_P0;
			अन्यथा अगर (lowest_1g == 26)
				parent->plat_type = PLAT_TYPE_VF_P1;
			अन्यथा
				जाओ unknown_vg_1g_port;

			val = (phy_encode(PORT_TYPE_1G, 0) |
			       phy_encode(PORT_TYPE_1G, 1) |
			       phy_encode(PORT_TYPE_1G, 2) |
			       phy_encode(PORT_TYPE_1G, 3));
			अवरोध;

		शेष:
			pr_err("Unsupported port config 10G[%d] 1G[%d]\n",
			       num_10g, num_1g);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	parent->port_phy = val;

	अगर (parent->plat_type == PLAT_TYPE_NIU)
		niu_n2_भागide_channels(parent);
	अन्यथा
		niu_भागide_channels(parent, num_10g, num_1g);

	niu_भागide_rdc_groups(parent, num_10g, num_1g);

	वापस 0;

unknown_vg_1g_port:
	pr_err("Cannot identify platform type, 1gport=%d\n", lowest_1g);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक niu_probe_ports(काष्ठा niu *np)
अणु
	काष्ठा niu_parent *parent = np->parent;
	पूर्णांक err, i;

	अगर (parent->port_phy == PORT_PHY_UNKNOWN) अणु
		err = walk_phys(np, parent);
		अगर (err)
			वापस err;

		niu_set_ldg_समयr_res(np, 2);
		क्रम (i = 0; i <= LDN_MAX; i++)
			niu_ldn_irq_enable(np, i, 0);
	पूर्ण

	अगर (parent->port_phy == PORT_PHY_INVALID)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक niu_classअगरier_swstate_init(काष्ठा niu *np)
अणु
	काष्ठा niu_classअगरier *cp = &np->clas;

	cp->tcam_top = (u16) np->port;
	cp->tcam_sz = np->parent->tcam_num_entries / np->parent->num_ports;
	cp->h1_init = 0xffffffff;
	cp->h2_init = 0xffff;

	वापस fflp_early_init(np);
पूर्ण

अटल व्योम niu_link_config_init(काष्ठा niu *np)
अणु
	काष्ठा niu_link_config *lp = &np->link_config;

	lp->advertising = (ADVERTISED_10baseT_Half |
			   ADVERTISED_10baseT_Full |
			   ADVERTISED_100baseT_Half |
			   ADVERTISED_100baseT_Full |
			   ADVERTISED_1000baseT_Half |
			   ADVERTISED_1000baseT_Full |
			   ADVERTISED_10000baseT_Full |
			   ADVERTISED_Autoneg);
	lp->speed = lp->active_speed = SPEED_INVALID;
	lp->duplex = DUPLEX_FULL;
	lp->active_duplex = DUPLEX_INVALID;
	lp->स्वतःneg = 1;
#अगर 0
	lp->loopback_mode = LOOPBACK_MAC;
	lp->active_speed = SPEED_10000;
	lp->active_duplex = DUPLEX_FULL;
#अन्यथा
	lp->loopback_mode = LOOPBACK_DISABLED;
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक niu_init_mac_ipp_pcs_base(काष्ठा niu *np)
अणु
	चयन (np->port) अणु
	हाल 0:
		np->mac_regs = np->regs + XMAC_PORT0_OFF;
		np->ipp_off  = 0x00000;
		np->pcs_off  = 0x04000;
		np->xpcs_off = 0x02000;
		अवरोध;

	हाल 1:
		np->mac_regs = np->regs + XMAC_PORT1_OFF;
		np->ipp_off  = 0x08000;
		np->pcs_off  = 0x0a000;
		np->xpcs_off = 0x08000;
		अवरोध;

	हाल 2:
		np->mac_regs = np->regs + BMAC_PORT2_OFF;
		np->ipp_off  = 0x04000;
		np->pcs_off  = 0x0e000;
		np->xpcs_off = ~0UL;
		अवरोध;

	हाल 3:
		np->mac_regs = np->regs + BMAC_PORT3_OFF;
		np->ipp_off  = 0x0c000;
		np->pcs_off  = 0x12000;
		np->xpcs_off = ~0UL;
		अवरोध;

	शेष:
		dev_err(np->device, "Port %u is invalid, cannot compute MAC block offset\n", np->port);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम niu_try_msix(काष्ठा niu *np, u8 *ldg_num_map)
अणु
	काष्ठा msix_entry msi_vec[NIU_NUM_LDG];
	काष्ठा niu_parent *parent = np->parent;
	काष्ठा pci_dev *pdev = np->pdev;
	पूर्णांक i, num_irqs;
	u8 first_ldg;

	first_ldg = (NIU_NUM_LDG / parent->num_ports) * np->port;
	क्रम (i = 0; i < (NIU_NUM_LDG / parent->num_ports); i++)
		ldg_num_map[i] = first_ldg + i;

	num_irqs = (parent->rxchan_per_port[np->port] +
		    parent->txchan_per_port[np->port] +
		    (np->port == 0 ? 3 : 1));
	BUG_ON(num_irqs > (NIU_NUM_LDG / parent->num_ports));

	क्रम (i = 0; i < num_irqs; i++) अणु
		msi_vec[i].vector = 0;
		msi_vec[i].entry = i;
	पूर्ण

	num_irqs = pci_enable_msix_range(pdev, msi_vec, 1, num_irqs);
	अगर (num_irqs < 0) अणु
		np->flags &= ~NIU_FLAGS_MSIX;
		वापस;
	पूर्ण

	np->flags |= NIU_FLAGS_MSIX;
	क्रम (i = 0; i < num_irqs; i++)
		np->ldg[i].irq = msi_vec[i].vector;
	np->num_ldg = num_irqs;
पूर्ण

अटल पूर्णांक niu_n2_irq_init(काष्ठा niu *np, u8 *ldg_num_map)
अणु
#अगर_घोषित CONFIG_SPARC64
	काष्ठा platक्रमm_device *op = np->op;
	स्थिर u32 *पूर्णांक_prop;
	पूर्णांक i;

	पूर्णांक_prop = of_get_property(op->dev.of_node, "interrupts", शून्य);
	अगर (!पूर्णांक_prop)
		वापस -ENODEV;

	क्रम (i = 0; i < op->archdata.num_irqs; i++) अणु
		ldg_num_map[i] = पूर्णांक_prop[i];
		np->ldg[i].irq = op->archdata.irqs[i];
	पूर्ण

	np->num_ldg = op->archdata.num_irqs;

	वापस 0;
#अन्यथा
	वापस -EINVAL;
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक niu_ldg_init(काष्ठा niu *np)
अणु
	काष्ठा niu_parent *parent = np->parent;
	u8 ldg_num_map[NIU_NUM_LDG];
	पूर्णांक first_chan, num_chan;
	पूर्णांक i, err, ldg_rotor;
	u8 port;

	np->num_ldg = 1;
	np->ldg[0].irq = np->dev->irq;
	अगर (parent->plat_type == PLAT_TYPE_NIU) अणु
		err = niu_n2_irq_init(np, ldg_num_map);
		अगर (err)
			वापस err;
	पूर्ण अन्यथा
		niu_try_msix(np, ldg_num_map);

	port = np->port;
	क्रम (i = 0; i < np->num_ldg; i++) अणु
		काष्ठा niu_ldg *lp = &np->ldg[i];

		netअगर_napi_add(np->dev, &lp->napi, niu_poll, 64);

		lp->np = np;
		lp->ldg_num = ldg_num_map[i];
		lp->समयr = 2; /* XXX */

		/* On N2 NIU the firmware has setup the SID mappings so they go
		 * to the correct values that will route the LDG to the proper
		 * पूर्णांकerrupt in the NCU पूर्णांकerrupt table.
		 */
		अगर (np->parent->plat_type != PLAT_TYPE_NIU) अणु
			err = niu_set_ldg_sid(np, lp->ldg_num, port, i);
			अगर (err)
				वापस err;
		पूर्ण
	पूर्ण

	/* We aकरोpt the LDG assignment ordering used by the N2 NIU
	 * 'interrupt' properties because that simplअगरies a lot of
	 * things.  This ordering is:
	 *
	 *	MAC
	 *	MIF	(अगर port zero)
	 *	SYSERR	(अगर port zero)
	 *	RX channels
	 *	TX channels
	 */

	ldg_rotor = 0;

	err = niu_ldg_assign_ldn(np, parent, ldg_num_map[ldg_rotor],
				  LDN_MAC(port));
	अगर (err)
		वापस err;

	ldg_rotor++;
	अगर (ldg_rotor == np->num_ldg)
		ldg_rotor = 0;

	अगर (port == 0) अणु
		err = niu_ldg_assign_ldn(np, parent,
					 ldg_num_map[ldg_rotor],
					 LDN_MIF);
		अगर (err)
			वापस err;

		ldg_rotor++;
		अगर (ldg_rotor == np->num_ldg)
			ldg_rotor = 0;

		err = niu_ldg_assign_ldn(np, parent,
					 ldg_num_map[ldg_rotor],
					 LDN_DEVICE_ERROR);
		अगर (err)
			वापस err;

		ldg_rotor++;
		अगर (ldg_rotor == np->num_ldg)
			ldg_rotor = 0;

	पूर्ण

	first_chan = 0;
	क्रम (i = 0; i < port; i++)
		first_chan += parent->rxchan_per_port[i];
	num_chan = parent->rxchan_per_port[port];

	क्रम (i = first_chan; i < (first_chan + num_chan); i++) अणु
		err = niu_ldg_assign_ldn(np, parent,
					 ldg_num_map[ldg_rotor],
					 LDN_RXDMA(i));
		अगर (err)
			वापस err;
		ldg_rotor++;
		अगर (ldg_rotor == np->num_ldg)
			ldg_rotor = 0;
	पूर्ण

	first_chan = 0;
	क्रम (i = 0; i < port; i++)
		first_chan += parent->txchan_per_port[i];
	num_chan = parent->txchan_per_port[port];
	क्रम (i = first_chan; i < (first_chan + num_chan); i++) अणु
		err = niu_ldg_assign_ldn(np, parent,
					 ldg_num_map[ldg_rotor],
					 LDN_TXDMA(i));
		अगर (err)
			वापस err;
		ldg_rotor++;
		अगर (ldg_rotor == np->num_ldg)
			ldg_rotor = 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम niu_ldg_मुक्त(काष्ठा niu *np)
अणु
	अगर (np->flags & NIU_FLAGS_MSIX)
		pci_disable_msix(np->pdev);
पूर्ण

अटल पूर्णांक niu_get_of_props(काष्ठा niu *np)
अणु
#अगर_घोषित CONFIG_SPARC64
	काष्ठा net_device *dev = np->dev;
	काष्ठा device_node *dp;
	स्थिर अक्षर *phy_type;
	स्थिर u8 *mac_addr;
	स्थिर अक्षर *model;
	पूर्णांक prop_len;

	अगर (np->parent->plat_type == PLAT_TYPE_NIU)
		dp = np->op->dev.of_node;
	अन्यथा
		dp = pci_device_to_OF_node(np->pdev);

	phy_type = of_get_property(dp, "phy-type", &prop_len);
	अगर (!phy_type) अणु
		netdev_err(dev, "%pOF: OF node lacks phy-type property\n", dp);
		वापस -EINVAL;
	पूर्ण

	अगर (!म_भेद(phy_type, "none"))
		वापस -ENODEV;

	म_नकल(np->vpd.phy_type, phy_type);

	अगर (niu_phy_type_prop_decode(np, np->vpd.phy_type)) अणु
		netdev_err(dev, "%pOF: Illegal phy string [%s]\n",
			   dp, np->vpd.phy_type);
		वापस -EINVAL;
	पूर्ण

	mac_addr = of_get_property(dp, "local-mac-address", &prop_len);
	अगर (!mac_addr) अणु
		netdev_err(dev, "%pOF: OF node lacks local-mac-address property\n",
			   dp);
		वापस -EINVAL;
	पूर्ण
	अगर (prop_len != dev->addr_len) अणु
		netdev_err(dev, "%pOF: OF MAC address prop len (%d) is wrong\n",
			   dp, prop_len);
	पूर्ण
	स_नकल(dev->dev_addr, mac_addr, dev->addr_len);
	अगर (!is_valid_ether_addr(&dev->dev_addr[0])) अणु
		netdev_err(dev, "%pOF: OF MAC address is invalid\n", dp);
		netdev_err(dev, "%pOF: [ %pM ]\n", dp, dev->dev_addr);
		वापस -EINVAL;
	पूर्ण

	model = of_get_property(dp, "model", &prop_len);

	अगर (model)
		म_नकल(np->vpd.model, model);

	अगर (of_find_property(dp, "hot-swappable-phy", &prop_len)) अणु
		np->flags |= (NIU_FLAGS_10G | NIU_FLAGS_FIBER |
			NIU_FLAGS_HOTPLUG_PHY);
	पूर्ण

	वापस 0;
#अन्यथा
	वापस -EINVAL;
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक niu_get_invariants(काष्ठा niu *np)
अणु
	पूर्णांक err, have_props;
	u32 offset;

	err = niu_get_of_props(np);
	अगर (err == -ENODEV)
		वापस err;

	have_props = !err;

	err = niu_init_mac_ipp_pcs_base(np);
	अगर (err)
		वापस err;

	अगर (have_props) अणु
		err = niu_get_and_validate_port(np);
		अगर (err)
			वापस err;

	पूर्ण अन्यथा  अणु
		अगर (np->parent->plat_type == PLAT_TYPE_NIU)
			वापस -EINVAL;

		nw64(ESPC_PIO_EN, ESPC_PIO_EN_ENABLE);
		offset = niu_pci_vpd_offset(np);
		netअगर_prपूर्णांकk(np, probe, KERN_DEBUG, np->dev,
			     "%s() VPD offset [%08x]\n", __func__, offset);
		अगर (offset) अणु
			err = niu_pci_vpd_fetch(np, offset);
			अगर (err < 0)
				वापस err;
		पूर्ण
		nw64(ESPC_PIO_EN, 0);

		अगर (np->flags & NIU_FLAGS_VPD_VALID) अणु
			niu_pci_vpd_validate(np);
			err = niu_get_and_validate_port(np);
			अगर (err)
				वापस err;
		पूर्ण

		अगर (!(np->flags & NIU_FLAGS_VPD_VALID)) अणु
			err = niu_get_and_validate_port(np);
			अगर (err)
				वापस err;
			err = niu_pci_probe_sprom(np);
			अगर (err)
				वापस err;
		पूर्ण
	पूर्ण

	err = niu_probe_ports(np);
	अगर (err)
		वापस err;

	niu_ldg_init(np);

	niu_classअगरier_swstate_init(np);
	niu_link_config_init(np);

	err = niu_determine_phy_disposition(np);
	अगर (!err)
		err = niu_init_link(np);

	वापस err;
पूर्ण

अटल LIST_HEAD(niu_parent_list);
अटल DEFINE_MUTEX(niu_parent_lock);
अटल पूर्णांक niu_parent_index;

अटल sमाप_प्रकार show_port_phy(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा platक्रमm_device *plat_dev = to_platक्रमm_device(dev);
	काष्ठा niu_parent *p = dev_get_platdata(&plat_dev->dev);
	u32 port_phy = p->port_phy;
	अक्षर *orig_buf = buf;
	पूर्णांक i;

	अगर (port_phy == PORT_PHY_UNKNOWN ||
	    port_phy == PORT_PHY_INVALID)
		वापस 0;

	क्रम (i = 0; i < p->num_ports; i++) अणु
		स्थिर अक्षर *type_str;
		पूर्णांक type;

		type = phy_decode(port_phy, i);
		अगर (type == PORT_TYPE_10G)
			type_str = "10G";
		अन्यथा
			type_str = "1G";
		buf += प्र_लिखो(buf,
			       (i == 0) ? "%s" : " %s",
			       type_str);
	पूर्ण
	buf += प्र_लिखो(buf, "\n");
	वापस buf - orig_buf;
पूर्ण

अटल sमाप_प्रकार show_plat_type(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा platक्रमm_device *plat_dev = to_platक्रमm_device(dev);
	काष्ठा niu_parent *p = dev_get_platdata(&plat_dev->dev);
	स्थिर अक्षर *type_str;

	चयन (p->plat_type) अणु
	हाल PLAT_TYPE_ATLAS:
		type_str = "atlas";
		अवरोध;
	हाल PLAT_TYPE_NIU:
		type_str = "niu";
		अवरोध;
	हाल PLAT_TYPE_VF_P0:
		type_str = "vf_p0";
		अवरोध;
	हाल PLAT_TYPE_VF_P1:
		type_str = "vf_p1";
		अवरोध;
	शेष:
		type_str = "unknown";
		अवरोध;
	पूर्ण

	वापस प्र_लिखो(buf, "%s\n", type_str);
पूर्ण

अटल sमाप_प्रकार __show_chan_per_port(काष्ठा device *dev,
				    काष्ठा device_attribute *attr, अक्षर *buf,
				    पूर्णांक rx)
अणु
	काष्ठा platक्रमm_device *plat_dev = to_platक्रमm_device(dev);
	काष्ठा niu_parent *p = dev_get_platdata(&plat_dev->dev);
	अक्षर *orig_buf = buf;
	u8 *arr;
	पूर्णांक i;

	arr = (rx ? p->rxchan_per_port : p->txchan_per_port);

	क्रम (i = 0; i < p->num_ports; i++) अणु
		buf += प्र_लिखो(buf,
			       (i == 0) ? "%d" : " %d",
			       arr[i]);
	पूर्ण
	buf += प्र_लिखो(buf, "\n");

	वापस buf - orig_buf;
पूर्ण

अटल sमाप_प्रकार show_rxchan_per_port(काष्ठा device *dev,
				    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस __show_chan_per_port(dev, attr, buf, 1);
पूर्ण

अटल sमाप_प्रकार show_txchan_per_port(काष्ठा device *dev,
				    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस __show_chan_per_port(dev, attr, buf, 1);
पूर्ण

अटल sमाप_प्रकार show_num_ports(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा platक्रमm_device *plat_dev = to_platक्रमm_device(dev);
	काष्ठा niu_parent *p = dev_get_platdata(&plat_dev->dev);

	वापस प्र_लिखो(buf, "%d\n", p->num_ports);
पूर्ण

अटल काष्ठा device_attribute niu_parent_attributes[] = अणु
	__ATTR(port_phy, 0444, show_port_phy, शून्य),
	__ATTR(plat_type, 0444, show_plat_type, शून्य),
	__ATTR(rxchan_per_port, 0444, show_rxchan_per_port, शून्य),
	__ATTR(txchan_per_port, 0444, show_txchan_per_port, शून्य),
	__ATTR(num_ports, 0444, show_num_ports, शून्य),
	अणुपूर्ण
पूर्ण;

अटल काष्ठा niu_parent *niu_new_parent(काष्ठा niu *np,
					 जोड़ niu_parent_id *id, u8 ptype)
अणु
	काष्ठा platक्रमm_device *plat_dev;
	काष्ठा niu_parent *p;
	पूर्णांक i;

	plat_dev = platक्रमm_device_रेजिस्टर_simple("niu-board", niu_parent_index,
						   शून्य, 0);
	अगर (IS_ERR(plat_dev))
		वापस शून्य;

	क्रम (i = 0; niu_parent_attributes[i].attr.name; i++) अणु
		पूर्णांक err = device_create_file(&plat_dev->dev,
					     &niu_parent_attributes[i]);
		अगर (err)
			जाओ fail_unरेजिस्टर;
	पूर्ण

	p = kzalloc(माप(*p), GFP_KERNEL);
	अगर (!p)
		जाओ fail_unरेजिस्टर;

	p->index = niu_parent_index++;

	plat_dev->dev.platक्रमm_data = p;
	p->plat_dev = plat_dev;

	स_नकल(&p->id, id, माप(*id));
	p->plat_type = ptype;
	INIT_LIST_HEAD(&p->list);
	atomic_set(&p->refcnt, 0);
	list_add(&p->list, &niu_parent_list);
	spin_lock_init(&p->lock);

	p->rxdma_घड़ी_भागider = 7500;

	p->tcam_num_entries = NIU_PCI_TCAM_ENTRIES;
	अगर (p->plat_type == PLAT_TYPE_NIU)
		p->tcam_num_entries = NIU_NONPCI_TCAM_ENTRIES;

	क्रम (i = CLASS_CODE_USER_PROG1; i <= CLASS_CODE_SCTP_IPV6; i++) अणु
		पूर्णांक index = i - CLASS_CODE_USER_PROG1;

		p->tcam_key[index] = TCAM_KEY_TSEL;
		p->flow_key[index] = (FLOW_KEY_IPSA |
				      FLOW_KEY_IPDA |
				      FLOW_KEY_PROTO |
				      (FLOW_KEY_L4_BYTE12 <<
				       FLOW_KEY_L4_0_SHIFT) |
				      (FLOW_KEY_L4_BYTE12 <<
				       FLOW_KEY_L4_1_SHIFT));
	पूर्ण

	क्रम (i = 0; i < LDN_MAX + 1; i++)
		p->ldg_map[i] = LDG_INVALID;

	वापस p;

fail_unरेजिस्टर:
	platक्रमm_device_unरेजिस्टर(plat_dev);
	वापस शून्य;
पूर्ण

अटल काष्ठा niu_parent *niu_get_parent(काष्ठा niu *np,
					 जोड़ niu_parent_id *id, u8 ptype)
अणु
	काष्ठा niu_parent *p, *पंचांगp;
	पूर्णांक port = np->port;

	mutex_lock(&niu_parent_lock);
	p = शून्य;
	list_क्रम_each_entry(पंचांगp, &niu_parent_list, list) अणु
		अगर (!स_भेद(id, &पंचांगp->id, माप(*id))) अणु
			p = पंचांगp;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!p)
		p = niu_new_parent(np, id, ptype);

	अगर (p) अणु
		अक्षर port_name[8];
		पूर्णांक err;

		प्र_लिखो(port_name, "port%d", port);
		err = sysfs_create_link(&p->plat_dev->dev.kobj,
					&np->device->kobj,
					port_name);
		अगर (!err) अणु
			p->ports[port] = np;
			atomic_inc(&p->refcnt);
		पूर्ण
	पूर्ण
	mutex_unlock(&niu_parent_lock);

	वापस p;
पूर्ण

अटल व्योम niu_put_parent(काष्ठा niu *np)
अणु
	काष्ठा niu_parent *p = np->parent;
	u8 port = np->port;
	अक्षर port_name[8];

	BUG_ON(!p || p->ports[port] != np);

	netअगर_prपूर्णांकk(np, probe, KERN_DEBUG, np->dev,
		     "%s() port[%u]\n", __func__, port);

	प्र_लिखो(port_name, "port%d", port);

	mutex_lock(&niu_parent_lock);

	sysfs_हटाओ_link(&p->plat_dev->dev.kobj, port_name);

	p->ports[port] = शून्य;
	np->parent = शून्य;

	अगर (atomic_dec_and_test(&p->refcnt)) अणु
		list_del(&p->list);
		platक्रमm_device_unरेजिस्टर(p->plat_dev);
	पूर्ण

	mutex_unlock(&niu_parent_lock);
पूर्ण

अटल व्योम *niu_pci_alloc_coherent(काष्ठा device *dev, माप_प्रकार size,
				    u64 *handle, gfp_t flag)
अणु
	dma_addr_t dh;
	व्योम *ret;

	ret = dma_alloc_coherent(dev, size, &dh, flag);
	अगर (ret)
		*handle = dh;
	वापस ret;
पूर्ण

अटल व्योम niu_pci_मुक्त_coherent(काष्ठा device *dev, माप_प्रकार size,
				  व्योम *cpu_addr, u64 handle)
अणु
	dma_मुक्त_coherent(dev, size, cpu_addr, handle);
पूर्ण

अटल u64 niu_pci_map_page(काष्ठा device *dev, काष्ठा page *page,
			    अचिन्हित दीर्घ offset, माप_प्रकार size,
			    क्रमागत dma_data_direction direction)
अणु
	वापस dma_map_page(dev, page, offset, size, direction);
पूर्ण

अटल व्योम niu_pci_unmap_page(काष्ठा device *dev, u64 dma_address,
			       माप_प्रकार size, क्रमागत dma_data_direction direction)
अणु
	dma_unmap_page(dev, dma_address, size, direction);
पूर्ण

अटल u64 niu_pci_map_single(काष्ठा device *dev, व्योम *cpu_addr,
			      माप_प्रकार size,
			      क्रमागत dma_data_direction direction)
अणु
	वापस dma_map_single(dev, cpu_addr, size, direction);
पूर्ण

अटल व्योम niu_pci_unmap_single(काष्ठा device *dev, u64 dma_address,
				 माप_प्रकार size,
				 क्रमागत dma_data_direction direction)
अणु
	dma_unmap_single(dev, dma_address, size, direction);
पूर्ण

अटल स्थिर काष्ठा niu_ops niu_pci_ops = अणु
	.alloc_coherent	= niu_pci_alloc_coherent,
	.मुक्त_coherent	= niu_pci_मुक्त_coherent,
	.map_page	= niu_pci_map_page,
	.unmap_page	= niu_pci_unmap_page,
	.map_single	= niu_pci_map_single,
	.unmap_single	= niu_pci_unmap_single,
पूर्ण;

अटल व्योम niu_driver_version(व्योम)
अणु
	अटल पूर्णांक niu_version_prपूर्णांकed;

	अगर (niu_version_prपूर्णांकed++ == 0)
		pr_info("%s", version);
पूर्ण

अटल काष्ठा net_device *niu_alloc_and_init(काष्ठा device *gen_dev,
					     काष्ठा pci_dev *pdev,
					     काष्ठा platक्रमm_device *op,
					     स्थिर काष्ठा niu_ops *ops, u8 port)
अणु
	काष्ठा net_device *dev;
	काष्ठा niu *np;

	dev = alloc_etherdev_mq(माप(काष्ठा niu), NIU_NUM_TXCHAN);
	अगर (!dev)
		वापस शून्य;

	SET_NETDEV_DEV(dev, gen_dev);

	np = netdev_priv(dev);
	np->dev = dev;
	np->pdev = pdev;
	np->op = op;
	np->device = gen_dev;
	np->ops = ops;

	np->msg_enable = niu_debug;

	spin_lock_init(&np->lock);
	INIT_WORK(&np->reset_task, niu_reset_task);

	np->port = port;

	वापस dev;
पूर्ण

अटल स्थिर काष्ठा net_device_ops niu_netdev_ops = अणु
	.nकरो_खोलो		= niu_खोलो,
	.nकरो_stop		= niu_बंद,
	.nकरो_start_xmit		= niu_start_xmit,
	.nकरो_get_stats64	= niu_get_stats,
	.nकरो_set_rx_mode	= niu_set_rx_mode,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_set_mac_address	= niu_set_mac_addr,
	.nकरो_करो_ioctl		= niu_ioctl,
	.nकरो_tx_समयout		= niu_tx_समयout,
	.nकरो_change_mtu		= niu_change_mtu,
पूर्ण;

अटल व्योम niu_assign_netdev_ops(काष्ठा net_device *dev)
अणु
	dev->netdev_ops = &niu_netdev_ops;
	dev->ethtool_ops = &niu_ethtool_ops;
	dev->watchकरोg_समयo = NIU_TX_TIMEOUT;
पूर्ण

अटल व्योम niu_device_announce(काष्ठा niu *np)
अणु
	काष्ठा net_device *dev = np->dev;

	pr_info("%s: NIU Ethernet %pM\n", dev->name, dev->dev_addr);

	अगर (np->parent->plat_type == PLAT_TYPE_ATCA_CP3220) अणु
		pr_info("%s: Port type[%s] mode[%s:%s] XCVR[%s] phy[%s]\n",
				dev->name,
				(np->flags & NIU_FLAGS_XMAC ? "XMAC" : "BMAC"),
				(np->flags & NIU_FLAGS_10G ? "10G" : "1G"),
				(np->flags & NIU_FLAGS_FIBER ? "RGMII FIBER" : "SERDES"),
				(np->mac_xcvr == MAC_XCVR_MII ? "MII" :
				 (np->mac_xcvr == MAC_XCVR_PCS ? "PCS" : "XPCS")),
				np->vpd.phy_type);
	पूर्ण अन्यथा अणु
		pr_info("%s: Port type[%s] mode[%s:%s] XCVR[%s] phy[%s]\n",
				dev->name,
				(np->flags & NIU_FLAGS_XMAC ? "XMAC" : "BMAC"),
				(np->flags & NIU_FLAGS_10G ? "10G" : "1G"),
				(np->flags & NIU_FLAGS_FIBER ? "FIBER" :
				 (np->flags & NIU_FLAGS_XCVR_SERDES ? "SERDES" :
				  "COPPER")),
				(np->mac_xcvr == MAC_XCVR_MII ? "MII" :
				 (np->mac_xcvr == MAC_XCVR_PCS ? "PCS" : "XPCS")),
				np->vpd.phy_type);
	पूर्ण
पूर्ण

अटल व्योम niu_set_basic_features(काष्ठा net_device *dev)
अणु
	dev->hw_features = NETIF_F_SG | NETIF_F_HW_CSUM | NETIF_F_RXHASH;
	dev->features |= dev->hw_features | NETIF_F_RXCSUM;
पूर्ण

अटल पूर्णांक niu_pci_init_one(काष्ठा pci_dev *pdev,
			    स्थिर काष्ठा pci_device_id *ent)
अणु
	जोड़ niu_parent_id parent_id;
	काष्ठा net_device *dev;
	काष्ठा niu *np;
	पूर्णांक err;
	u64 dma_mask;

	niu_driver_version();

	err = pci_enable_device(pdev);
	अगर (err) अणु
		dev_err(&pdev->dev, "Cannot enable PCI device, aborting\n");
		वापस err;
	पूर्ण

	अगर (!(pci_resource_flags(pdev, 0) & IORESOURCE_MEM) ||
	    !(pci_resource_flags(pdev, 2) & IORESOURCE_MEM)) अणु
		dev_err(&pdev->dev, "Cannot find proper PCI device base addresses, aborting\n");
		err = -ENODEV;
		जाओ err_out_disable_pdev;
	पूर्ण

	err = pci_request_regions(pdev, DRV_MODULE_NAME);
	अगर (err) अणु
		dev_err(&pdev->dev, "Cannot obtain PCI resources, aborting\n");
		जाओ err_out_disable_pdev;
	पूर्ण

	अगर (!pci_is_pcie(pdev)) अणु
		dev_err(&pdev->dev, "Cannot find PCI Express capability, aborting\n");
		err = -ENODEV;
		जाओ err_out_मुक्त_res;
	पूर्ण

	dev = niu_alloc_and_init(&pdev->dev, pdev, शून्य,
				 &niu_pci_ops, PCI_FUNC(pdev->devfn));
	अगर (!dev) अणु
		err = -ENOMEM;
		जाओ err_out_मुक्त_res;
	पूर्ण
	np = netdev_priv(dev);

	स_रखो(&parent_id, 0, माप(parent_id));
	parent_id.pci.करोमुख्य = pci_करोमुख्य_nr(pdev->bus);
	parent_id.pci.bus = pdev->bus->number;
	parent_id.pci.device = PCI_SLOT(pdev->devfn);

	np->parent = niu_get_parent(np, &parent_id,
				    PLAT_TYPE_ATLAS);
	अगर (!np->parent) अणु
		err = -ENOMEM;
		जाओ err_out_मुक्त_dev;
	पूर्ण

	pcie_capability_clear_and_set_word(pdev, PCI_EXP_DEVCTL,
		PCI_EXP_DEVCTL_NOSNOOP_EN,
		PCI_EXP_DEVCTL_CERE | PCI_EXP_DEVCTL_NFERE |
		PCI_EXP_DEVCTL_FERE | PCI_EXP_DEVCTL_URRE |
		PCI_EXP_DEVCTL_RELAX_EN);

	dma_mask = DMA_BIT_MASK(44);
	err = pci_set_dma_mask(pdev, dma_mask);
	अगर (!err) अणु
		dev->features |= NETIF_F_HIGHDMA;
		err = pci_set_consistent_dma_mask(pdev, dma_mask);
		अगर (err) अणु
			dev_err(&pdev->dev, "Unable to obtain 44 bit DMA for consistent allocations, aborting\n");
			जाओ err_out_release_parent;
		पूर्ण
	पूर्ण
	अगर (err) अणु
		err = pci_set_dma_mask(pdev, DMA_BIT_MASK(32));
		अगर (err) अणु
			dev_err(&pdev->dev, "No usable DMA configuration, aborting\n");
			जाओ err_out_release_parent;
		पूर्ण
	पूर्ण

	niu_set_basic_features(dev);

	dev->priv_flags |= IFF_UNICAST_FLT;

	np->regs = pci_ioremap_bar(pdev, 0);
	अगर (!np->regs) अणु
		dev_err(&pdev->dev, "Cannot map device registers, aborting\n");
		err = -ENOMEM;
		जाओ err_out_release_parent;
	पूर्ण

	pci_set_master(pdev);
	pci_save_state(pdev);

	dev->irq = pdev->irq;

	/* MTU range: 68 - 9216 */
	dev->min_mtu = ETH_MIN_MTU;
	dev->max_mtu = NIU_MAX_MTU;

	niu_assign_netdev_ops(dev);

	err = niu_get_invariants(np);
	अगर (err) अणु
		अगर (err != -ENODEV)
			dev_err(&pdev->dev, "Problem fetching invariants of chip, aborting\n");
		जाओ err_out_iounmap;
	पूर्ण

	err = रेजिस्टर_netdev(dev);
	अगर (err) अणु
		dev_err(&pdev->dev, "Cannot register net device, aborting\n");
		जाओ err_out_iounmap;
	पूर्ण

	pci_set_drvdata(pdev, dev);

	niu_device_announce(np);

	वापस 0;

err_out_iounmap:
	अगर (np->regs) अणु
		iounmap(np->regs);
		np->regs = शून्य;
	पूर्ण

err_out_release_parent:
	niu_put_parent(np);

err_out_मुक्त_dev:
	मुक्त_netdev(dev);

err_out_मुक्त_res:
	pci_release_regions(pdev);

err_out_disable_pdev:
	pci_disable_device(pdev);

	वापस err;
पूर्ण

अटल व्योम niu_pci_हटाओ_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *dev = pci_get_drvdata(pdev);

	अगर (dev) अणु
		काष्ठा niu *np = netdev_priv(dev);

		unरेजिस्टर_netdev(dev);
		अगर (np->regs) अणु
			iounmap(np->regs);
			np->regs = शून्य;
		पूर्ण

		niu_ldg_मुक्त(np);

		niu_put_parent(np);

		मुक्त_netdev(dev);
		pci_release_regions(pdev);
		pci_disable_device(pdev);
	पूर्ण
पूर्ण

अटल पूर्णांक __maybe_unused niu_suspend(काष्ठा device *dev_d)
अणु
	काष्ठा net_device *dev = dev_get_drvdata(dev_d);
	काष्ठा niu *np = netdev_priv(dev);
	अचिन्हित दीर्घ flags;

	अगर (!netअगर_running(dev))
		वापस 0;

	flush_work(&np->reset_task);
	niu_netअगर_stop(np);

	del_समयr_sync(&np->समयr);

	spin_lock_irqsave(&np->lock, flags);
	niu_enable_पूर्णांकerrupts(np, 0);
	spin_unlock_irqrestore(&np->lock, flags);

	netअगर_device_detach(dev);

	spin_lock_irqsave(&np->lock, flags);
	niu_stop_hw(np);
	spin_unlock_irqrestore(&np->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused niu_resume(काष्ठा device *dev_d)
अणु
	काष्ठा net_device *dev = dev_get_drvdata(dev_d);
	काष्ठा niu *np = netdev_priv(dev);
	अचिन्हित दीर्घ flags;
	पूर्णांक err;

	अगर (!netअगर_running(dev))
		वापस 0;

	netअगर_device_attach(dev);

	spin_lock_irqsave(&np->lock, flags);

	err = niu_init_hw(np);
	अगर (!err) अणु
		np->समयr.expires = jअगरfies + HZ;
		add_समयr(&np->समयr);
		niu_netअगर_start(np);
	पूर्ण

	spin_unlock_irqrestore(&np->lock, flags);

	वापस err;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(niu_pm_ops, niu_suspend, niu_resume);

अटल काष्ठा pci_driver niu_pci_driver = अणु
	.name		= DRV_MODULE_NAME,
	.id_table	= niu_pci_tbl,
	.probe		= niu_pci_init_one,
	.हटाओ		= niu_pci_हटाओ_one,
	.driver.pm	= &niu_pm_ops,
पूर्ण;

#अगर_घोषित CONFIG_SPARC64
अटल व्योम *niu_phys_alloc_coherent(काष्ठा device *dev, माप_प्रकार size,
				     u64 *dma_addr, gfp_t flag)
अणु
	अचिन्हित दीर्घ order = get_order(size);
	अचिन्हित दीर्घ page = __get_मुक्त_pages(flag, order);

	अगर (page == 0UL)
		वापस शून्य;
	स_रखो((अक्षर *)page, 0, PAGE_SIZE << order);
	*dma_addr = __pa(page);

	वापस (व्योम *) page;
पूर्ण

अटल व्योम niu_phys_मुक्त_coherent(काष्ठा device *dev, माप_प्रकार size,
				   व्योम *cpu_addr, u64 handle)
अणु
	अचिन्हित दीर्घ order = get_order(size);

	मुक्त_pages((अचिन्हित दीर्घ) cpu_addr, order);
पूर्ण

अटल u64 niu_phys_map_page(काष्ठा device *dev, काष्ठा page *page,
			     अचिन्हित दीर्घ offset, माप_प्रकार size,
			     क्रमागत dma_data_direction direction)
अणु
	वापस page_to_phys(page) + offset;
पूर्ण

अटल व्योम niu_phys_unmap_page(काष्ठा device *dev, u64 dma_address,
				माप_प्रकार size, क्रमागत dma_data_direction direction)
अणु
	/* Nothing to करो.  */
पूर्ण

अटल u64 niu_phys_map_single(काष्ठा device *dev, व्योम *cpu_addr,
			       माप_प्रकार size,
			       क्रमागत dma_data_direction direction)
अणु
	वापस __pa(cpu_addr);
पूर्ण

अटल व्योम niu_phys_unmap_single(काष्ठा device *dev, u64 dma_address,
				  माप_प्रकार size,
				  क्रमागत dma_data_direction direction)
अणु
	/* Nothing to करो.  */
पूर्ण

अटल स्थिर काष्ठा niu_ops niu_phys_ops = अणु
	.alloc_coherent	= niu_phys_alloc_coherent,
	.मुक्त_coherent	= niu_phys_मुक्त_coherent,
	.map_page	= niu_phys_map_page,
	.unmap_page	= niu_phys_unmap_page,
	.map_single	= niu_phys_map_single,
	.unmap_single	= niu_phys_unmap_single,
पूर्ण;

अटल पूर्णांक niu_of_probe(काष्ठा platक्रमm_device *op)
अणु
	जोड़ niu_parent_id parent_id;
	काष्ठा net_device *dev;
	काष्ठा niu *np;
	स्थिर u32 *reg;
	पूर्णांक err;

	niu_driver_version();

	reg = of_get_property(op->dev.of_node, "reg", शून्य);
	अगर (!reg) अणु
		dev_err(&op->dev, "%pOF: No 'reg' property, aborting\n",
			op->dev.of_node);
		वापस -ENODEV;
	पूर्ण

	dev = niu_alloc_and_init(&op->dev, शून्य, op,
				 &niu_phys_ops, reg[0] & 0x1);
	अगर (!dev) अणु
		err = -ENOMEM;
		जाओ err_out;
	पूर्ण
	np = netdev_priv(dev);

	स_रखो(&parent_id, 0, माप(parent_id));
	parent_id.of = of_get_parent(op->dev.of_node);

	np->parent = niu_get_parent(np, &parent_id,
				    PLAT_TYPE_NIU);
	अगर (!np->parent) अणु
		err = -ENOMEM;
		जाओ err_out_मुक्त_dev;
	पूर्ण

	niu_set_basic_features(dev);

	np->regs = of_ioremap(&op->resource[1], 0,
			      resource_size(&op->resource[1]),
			      "niu regs");
	अगर (!np->regs) अणु
		dev_err(&op->dev, "Cannot map device registers, aborting\n");
		err = -ENOMEM;
		जाओ err_out_release_parent;
	पूर्ण

	np->vir_regs_1 = of_ioremap(&op->resource[2], 0,
				    resource_size(&op->resource[2]),
				    "niu vregs-1");
	अगर (!np->vir_regs_1) अणु
		dev_err(&op->dev, "Cannot map device vir registers 1, aborting\n");
		err = -ENOMEM;
		जाओ err_out_iounmap;
	पूर्ण

	np->vir_regs_2 = of_ioremap(&op->resource[3], 0,
				    resource_size(&op->resource[3]),
				    "niu vregs-2");
	अगर (!np->vir_regs_2) अणु
		dev_err(&op->dev, "Cannot map device vir registers 2, aborting\n");
		err = -ENOMEM;
		जाओ err_out_iounmap;
	पूर्ण

	niu_assign_netdev_ops(dev);

	err = niu_get_invariants(np);
	अगर (err) अणु
		अगर (err != -ENODEV)
			dev_err(&op->dev, "Problem fetching invariants of chip, aborting\n");
		जाओ err_out_iounmap;
	पूर्ण

	err = रेजिस्टर_netdev(dev);
	अगर (err) अणु
		dev_err(&op->dev, "Cannot register net device, aborting\n");
		जाओ err_out_iounmap;
	पूर्ण

	platक्रमm_set_drvdata(op, dev);

	niu_device_announce(np);

	वापस 0;

err_out_iounmap:
	अगर (np->vir_regs_1) अणु
		of_iounmap(&op->resource[2], np->vir_regs_1,
			   resource_size(&op->resource[2]));
		np->vir_regs_1 = शून्य;
	पूर्ण

	अगर (np->vir_regs_2) अणु
		of_iounmap(&op->resource[3], np->vir_regs_2,
			   resource_size(&op->resource[3]));
		np->vir_regs_2 = शून्य;
	पूर्ण

	अगर (np->regs) अणु
		of_iounmap(&op->resource[1], np->regs,
			   resource_size(&op->resource[1]));
		np->regs = शून्य;
	पूर्ण

err_out_release_parent:
	niu_put_parent(np);

err_out_मुक्त_dev:
	मुक्त_netdev(dev);

err_out:
	वापस err;
पूर्ण

अटल पूर्णांक niu_of_हटाओ(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा net_device *dev = platक्रमm_get_drvdata(op);

	अगर (dev) अणु
		काष्ठा niu *np = netdev_priv(dev);

		unरेजिस्टर_netdev(dev);

		अगर (np->vir_regs_1) अणु
			of_iounmap(&op->resource[2], np->vir_regs_1,
				   resource_size(&op->resource[2]));
			np->vir_regs_1 = शून्य;
		पूर्ण

		अगर (np->vir_regs_2) अणु
			of_iounmap(&op->resource[3], np->vir_regs_2,
				   resource_size(&op->resource[3]));
			np->vir_regs_2 = शून्य;
		पूर्ण

		अगर (np->regs) अणु
			of_iounmap(&op->resource[1], np->regs,
				   resource_size(&op->resource[1]));
			np->regs = शून्य;
		पूर्ण

		niu_ldg_मुक्त(np);

		niu_put_parent(np);

		मुक्त_netdev(dev);
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id niu_match[] = अणु
	अणु
		.name = "network",
		.compatible = "SUNW,niusl",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, niu_match);

अटल काष्ठा platक्रमm_driver niu_of_driver = अणु
	.driver = अणु
		.name = "niu",
		.of_match_table = niu_match,
	पूर्ण,
	.probe		= niu_of_probe,
	.हटाओ		= niu_of_हटाओ,
पूर्ण;

#पूर्ण_अगर /* CONFIG_SPARC64 */

अटल पूर्णांक __init niu_init(व्योम)
अणु
	पूर्णांक err = 0;

	BUILD_BUG_ON(PAGE_SIZE < 4 * 1024);

	niu_debug = netअगर_msg_init(debug, NIU_MSG_DEFAULT);

#अगर_घोषित CONFIG_SPARC64
	err = platक्रमm_driver_रेजिस्टर(&niu_of_driver);
#पूर्ण_अगर

	अगर (!err) अणु
		err = pci_रेजिस्टर_driver(&niu_pci_driver);
#अगर_घोषित CONFIG_SPARC64
		अगर (err)
			platक्रमm_driver_unरेजिस्टर(&niu_of_driver);
#पूर्ण_अगर
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम __निकास niu_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&niu_pci_driver);
#अगर_घोषित CONFIG_SPARC64
	platक्रमm_driver_unरेजिस्टर(&niu_of_driver);
#पूर्ण_अगर
पूर्ण

module_init(niu_init);
module_निकास(niu_निकास);
