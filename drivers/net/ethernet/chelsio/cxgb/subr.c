<शैली गुरु>
/*****************************************************************************
 *                                                                           *
 * File: subr.c                                                              *
 * $Revision: 1.27 $                                                         *
 * $Date: 2005/06/22 01:08:36 $                                              *
 * Description:                                                              *
 *  Various subroutines (पूर्णांकr,pio,etc.) used by Chelsio 10G Ethernet driver. *
 *  part of the Chelsio 10Gb Ethernet Driver.                                *
 *                                                                           *
 * This program is मुक्त software; you can redistribute it and/or modअगरy      *
 * it under the terms of the GNU General Public License, version 2, as       *
 * published by the Free Software Foundation.                                *
 *                                                                           *
 * You should have received a copy of the GNU General Public License aदीर्घ   *
 * with this program; अगर not, see <http://www.gnu.org/licenses/>.            *
 *                                                                           *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR IMPLIED    *
 * WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF      *
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.                     *
 *                                                                           *
 * http://www.chelsio.com                                                    *
 *                                                                           *
 * Copyright (c) 2003 - 2005 Chelsio Communications, Inc.                    *
 * All rights reserved.                                                      *
 *                                                                           *
 * Maपूर्णांकainers: मुख्यtainers@chelsio.com                                      *
 *                                                                           *
 * Authors: Dimitrios Michailidis   <dm@chelsio.com>                         *
 *          Tina Yang               <tainay@chelsio.com>                     *
 *          Felix Marti             <felix@chelsio.com>                      *
 *          Scott Barकरोne           <sbarकरोne@chelsio.com>                   *
 *          Kurt Ottaway            <kottaway@chelsio.com>                   *
 *          Frank DiMambro          <frank@chelsio.com>                      *
 *                                                                           *
 * History:                                                                  *
 *                                                                           *
 ****************************************************************************/

#समावेश "common.h"
#समावेश "elmer0.h"
#समावेश "regs.h"
#समावेश "gmac.h"
#समावेश "cphy.h"
#समावेश "sge.h"
#समावेश "tp.h"
#समावेश "espi.h"

/**
 *	t1_रुको_op_करोne - रुको until an operation is completed
 *	@adapter: the adapter perक्रमming the operation
 *	@reg: the रेजिस्टर to check क्रम completion
 *	@mask: a single-bit field within @reg that indicates completion
 *	@polarity: the value of the field when the operation is completed
 *	@attempts: number of check iterations
 *      @delay: delay in usecs between iterations
 *
 *	Wait until an operation is completed by checking a bit in a रेजिस्टर
 *	up to @attempts बार.  Returns %0 अगर the operation completes and %1
 *	otherwise.
 */
अटल पूर्णांक t1_रुको_op_करोne(adapter_t *adapter, पूर्णांक reg, u32 mask, पूर्णांक polarity,
			   पूर्णांक attempts, पूर्णांक delay)
अणु
	जबतक (1) अणु
		u32 val = पढ़ोl(adapter->regs + reg) & mask;

		अगर (!!val == polarity)
			वापस 0;
		अगर (--attempts == 0)
			वापस 1;
		अगर (delay)
			udelay(delay);
	पूर्ण
पूर्ण

#घोषणा TPI_ATTEMPTS 50

/*
 * Write a रेजिस्टर over the TPI पूर्णांकerface (unlocked and locked versions).
 */
पूर्णांक __t1_tpi_ग_लिखो(adapter_t *adapter, u32 addr, u32 value)
अणु
	पूर्णांक tpi_busy;

	ग_लिखोl(addr, adapter->regs + A_TPI_ADDR);
	ग_लिखोl(value, adapter->regs + A_TPI_WR_DATA);
	ग_लिखोl(F_TPIWR, adapter->regs + A_TPI_CSR);

	tpi_busy = t1_रुको_op_करोne(adapter, A_TPI_CSR, F_TPIRDY, 1,
				   TPI_ATTEMPTS, 3);
	अगर (tpi_busy)
		pr_alert("%s: TPI write to 0x%x failed\n",
			 adapter->name, addr);
	वापस tpi_busy;
पूर्ण

पूर्णांक t1_tpi_ग_लिखो(adapter_t *adapter, u32 addr, u32 value)
अणु
	पूर्णांक ret;

	spin_lock(&adapter->tpi_lock);
	ret = __t1_tpi_ग_लिखो(adapter, addr, value);
	spin_unlock(&adapter->tpi_lock);
	वापस ret;
पूर्ण

/*
 * Read a रेजिस्टर over the TPI पूर्णांकerface (unlocked and locked versions).
 */
पूर्णांक __t1_tpi_पढ़ो(adapter_t *adapter, u32 addr, u32 *valp)
अणु
	पूर्णांक tpi_busy;

	ग_लिखोl(addr, adapter->regs + A_TPI_ADDR);
	ग_लिखोl(0, adapter->regs + A_TPI_CSR);

	tpi_busy = t1_रुको_op_करोne(adapter, A_TPI_CSR, F_TPIRDY, 1,
				   TPI_ATTEMPTS, 3);
	अगर (tpi_busy)
		pr_alert("%s: TPI read from 0x%x failed\n",
			 adapter->name, addr);
	अन्यथा
		*valp = पढ़ोl(adapter->regs + A_TPI_RD_DATA);
	वापस tpi_busy;
पूर्ण

पूर्णांक t1_tpi_पढ़ो(adapter_t *adapter, u32 addr, u32 *valp)
अणु
	पूर्णांक ret;

	spin_lock(&adapter->tpi_lock);
	ret = __t1_tpi_पढ़ो(adapter, addr, valp);
	spin_unlock(&adapter->tpi_lock);
	वापस ret;
पूर्ण

/*
 * Set a TPI parameter.
 */
अटल व्योम t1_tpi_par(adapter_t *adapter, u32 value)
अणु
	ग_लिखोl(V_TPIPAR(value), adapter->regs + A_TPI_PAR);
पूर्ण

/*
 * Called when a port's link settings change to propagate the new values to the
 * associated PHY and MAC.  After perक्रमming the common tasks it invokes an
 * OS-specअगरic handler.
 */
व्योम t1_link_changed(adapter_t *adapter, पूर्णांक port_id)
अणु
	पूर्णांक link_ok, speed, duplex, fc;
	काष्ठा cphy *phy = adapter->port[port_id].phy;
	काष्ठा link_config *lc = &adapter->port[port_id].link_config;

	phy->ops->get_link_status(phy, &link_ok, &speed, &duplex, &fc);

	lc->speed = speed < 0 ? SPEED_INVALID : speed;
	lc->duplex = duplex < 0 ? DUPLEX_INVALID : duplex;
	अगर (!(lc->requested_fc & PAUSE_AUTONEG))
		fc = lc->requested_fc & (PAUSE_RX | PAUSE_TX);

	अगर (link_ok && speed >= 0 && lc->स्वतःneg == AUTONEG_ENABLE) अणु
		/* Set MAC speed, duplex, and flow control to match PHY. */
		काष्ठा cmac *mac = adapter->port[port_id].mac;

		mac->ops->set_speed_duplex_fc(mac, speed, duplex, fc);
		lc->fc = (अचिन्हित अक्षर)fc;
	पूर्ण
	t1_link_negotiated(adapter, port_id, link_ok, speed, duplex, fc);
पूर्ण

अटल bool t1_pci_पूर्णांकr_handler(adapter_t *adapter)
अणु
	u32 pcix_cause;

	pci_पढ़ो_config_dword(adapter->pdev, A_PCICFG_INTR_CAUSE, &pcix_cause);

	अगर (pcix_cause) अणु
		pci_ग_लिखो_config_dword(adapter->pdev, A_PCICFG_INTR_CAUSE,
				       pcix_cause);
		/* PCI errors are fatal */
		t1_पूर्णांकerrupts_disable(adapter);
		adapter->pending_thपढ़ो_पूर्णांकr |= F_PL_INTR_SGE_ERR;
		pr_alert("%s: PCI error encountered.\n", adapter->name);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

#अगर_घोषित CONFIG_CHELSIO_T1_1G
#समावेश "fpga_defs.h"

/*
 * PHY पूर्णांकerrupt handler क्रम FPGA boards.
 */
अटल पूर्णांक fpga_phy_पूर्णांकr_handler(adapter_t *adapter)
अणु
	पूर्णांक p;
	u32 cause = पढ़ोl(adapter->regs + FPGA_GMAC_ADDR_INTERRUPT_CAUSE);

	क्रम_each_port(adapter, p)
		अगर (cause & (1 << p)) अणु
			काष्ठा cphy *phy = adapter->port[p].phy;
			पूर्णांक phy_cause = phy->ops->पूर्णांकerrupt_handler(phy);

			अगर (phy_cause & cphy_cause_link_change)
				t1_link_changed(adapter, p);
		पूर्ण
	ग_लिखोl(cause, adapter->regs + FPGA_GMAC_ADDR_INTERRUPT_CAUSE);
	वापस 0;
पूर्ण

/*
 * Slow path पूर्णांकerrupt handler क्रम FPGAs.
 */
अटल irqवापस_t fpga_slow_पूर्णांकr(adapter_t *adapter)
अणु
	u32 cause = पढ़ोl(adapter->regs + A_PL_CAUSE);
	irqवापस_t ret = IRQ_NONE;

	cause &= ~F_PL_INTR_SGE_DATA;
	अगर (cause & F_PL_INTR_SGE_ERR) अणु
		अगर (t1_sge_पूर्णांकr_error_handler(adapter->sge))
			ret = IRQ_WAKE_THREAD;
	पूर्ण

	अगर (cause & FPGA_PCIX_INTERRUPT_GMAC)
		fpga_phy_पूर्णांकr_handler(adapter);

	अगर (cause & FPGA_PCIX_INTERRUPT_TP) अणु
		/*
		 * FPGA करोesn't support MC4 पूर्णांकerrupts and it requires
		 * this odd layer of indirection क्रम MC5.
		 */
		u32 tp_cause = पढ़ोl(adapter->regs + FPGA_TP_ADDR_INTERRUPT_CAUSE);

		/* Clear TP पूर्णांकerrupt */
		ग_लिखोl(tp_cause, adapter->regs + FPGA_TP_ADDR_INTERRUPT_CAUSE);
	पूर्ण
	अगर (cause & FPGA_PCIX_INTERRUPT_PCIX) अणु
		अगर (t1_pci_पूर्णांकr_handler(adapter))
			ret = IRQ_WAKE_THREAD;
	पूर्ण

	/* Clear the पूर्णांकerrupts just processed. */
	अगर (cause)
		ग_लिखोl(cause, adapter->regs + A_PL_CAUSE);

	अगर (ret != IRQ_NONE)
		वापस ret;

	वापस cause == 0 ? IRQ_NONE : IRQ_HANDLED;
पूर्ण
#पूर्ण_अगर

/*
 * Wait until Elmer's MI1 पूर्णांकerface is पढ़ोy क्रम new operations.
 */
अटल पूर्णांक mi1_रुको_until_पढ़ोy(adapter_t *adapter, पूर्णांक mi1_reg)
अणु
	पूर्णांक attempts = 100, busy;

	करो अणु
		u32 val;

		__t1_tpi_पढ़ो(adapter, mi1_reg, &val);
		busy = val & F_MI1_OP_BUSY;
		अगर (busy)
			udelay(10);
	पूर्ण जबतक (busy && --attempts);
	अगर (busy)
		pr_alert("%s: MDIO operation timed out\n", adapter->name);
	वापस busy;
पूर्ण

/*
 * MI1 MDIO initialization.
 */
अटल व्योम mi1_mdio_init(adapter_t *adapter, स्थिर काष्ठा board_info *bi)
अणु
	u32 clkभाग = bi->घड़ी_elmer0 / (2 * bi->mdio_mdc) - 1;
	u32 val = F_MI1_PREAMBLE_ENABLE | V_MI1_MDI_INVERT(bi->mdio_mdiinv) |
		V_MI1_MDI_ENABLE(bi->mdio_mdien) | V_MI1_CLK_DIV(clkभाग);

	अगर (!(bi->caps & SUPPORTED_10000baseT_Full))
		val |= V_MI1_SOF(1);
	t1_tpi_ग_लिखो(adapter, A_ELMER0_PORT0_MI1_CFG, val);
पूर्ण

#अगर defined(CONFIG_CHELSIO_T1_1G)
/*
 * Elmer MI1 MDIO पढ़ो/ग_लिखो operations.
 */
अटल पूर्णांक mi1_mdio_पढ़ो(काष्ठा net_device *dev, पूर्णांक phy_addr, पूर्णांक mmd_addr,
			 u16 reg_addr)
अणु
	काष्ठा adapter *adapter = dev->ml_priv;
	u32 addr = V_MI1_REG_ADDR(reg_addr) | V_MI1_PHY_ADDR(phy_addr);
	अचिन्हित पूर्णांक val;

	spin_lock(&adapter->tpi_lock);
	__t1_tpi_ग_लिखो(adapter, A_ELMER0_PORT0_MI1_ADDR, addr);
	__t1_tpi_ग_लिखो(adapter,
			A_ELMER0_PORT0_MI1_OP, MI1_OP_सूचीECT_READ);
	mi1_रुको_until_पढ़ोy(adapter, A_ELMER0_PORT0_MI1_OP);
	__t1_tpi_पढ़ो(adapter, A_ELMER0_PORT0_MI1_DATA, &val);
	spin_unlock(&adapter->tpi_lock);
	वापस val;
पूर्ण

अटल पूर्णांक mi1_mdio_ग_लिखो(काष्ठा net_device *dev, पूर्णांक phy_addr, पूर्णांक mmd_addr,
			  u16 reg_addr, u16 val)
अणु
	काष्ठा adapter *adapter = dev->ml_priv;
	u32 addr = V_MI1_REG_ADDR(reg_addr) | V_MI1_PHY_ADDR(phy_addr);

	spin_lock(&adapter->tpi_lock);
	__t1_tpi_ग_लिखो(adapter, A_ELMER0_PORT0_MI1_ADDR, addr);
	__t1_tpi_ग_लिखो(adapter, A_ELMER0_PORT0_MI1_DATA, val);
	__t1_tpi_ग_लिखो(adapter,
			A_ELMER0_PORT0_MI1_OP, MI1_OP_सूचीECT_WRITE);
	mi1_रुको_until_पढ़ोy(adapter, A_ELMER0_PORT0_MI1_OP);
	spin_unlock(&adapter->tpi_lock);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mdio_ops mi1_mdio_ops = अणु
	.init = mi1_mdio_init,
	.पढ़ो = mi1_mdio_पढ़ो,
	.ग_लिखो = mi1_mdio_ग_लिखो,
	.mode_support = MDIO_SUPPORTS_C22
पूर्ण;

#पूर्ण_अगर

अटल पूर्णांक mi1_mdio_ext_पढ़ो(काष्ठा net_device *dev, पूर्णांक phy_addr, पूर्णांक mmd_addr,
			     u16 reg_addr)
अणु
	काष्ठा adapter *adapter = dev->ml_priv;
	u32 addr = V_MI1_REG_ADDR(mmd_addr) | V_MI1_PHY_ADDR(phy_addr);
	अचिन्हित पूर्णांक val;

	spin_lock(&adapter->tpi_lock);

	/* Write the address we want. */
	__t1_tpi_ग_लिखो(adapter, A_ELMER0_PORT0_MI1_ADDR, addr);
	__t1_tpi_ग_लिखो(adapter, A_ELMER0_PORT0_MI1_DATA, reg_addr);
	__t1_tpi_ग_लिखो(adapter, A_ELMER0_PORT0_MI1_OP,
		       MI1_OP_INसूचीECT_ADDRESS);
	mi1_रुको_until_पढ़ोy(adapter, A_ELMER0_PORT0_MI1_OP);

	/* Write the operation we want. */
	__t1_tpi_ग_लिखो(adapter,
			A_ELMER0_PORT0_MI1_OP, MI1_OP_INसूचीECT_READ);
	mi1_रुको_until_पढ़ोy(adapter, A_ELMER0_PORT0_MI1_OP);

	/* Read the data. */
	__t1_tpi_पढ़ो(adapter, A_ELMER0_PORT0_MI1_DATA, &val);
	spin_unlock(&adapter->tpi_lock);
	वापस val;
पूर्ण

अटल पूर्णांक mi1_mdio_ext_ग_लिखो(काष्ठा net_device *dev, पूर्णांक phy_addr,
			      पूर्णांक mmd_addr, u16 reg_addr, u16 val)
अणु
	काष्ठा adapter *adapter = dev->ml_priv;
	u32 addr = V_MI1_REG_ADDR(mmd_addr) | V_MI1_PHY_ADDR(phy_addr);

	spin_lock(&adapter->tpi_lock);

	/* Write the address we want. */
	__t1_tpi_ग_लिखो(adapter, A_ELMER0_PORT0_MI1_ADDR, addr);
	__t1_tpi_ग_लिखो(adapter, A_ELMER0_PORT0_MI1_DATA, reg_addr);
	__t1_tpi_ग_लिखो(adapter, A_ELMER0_PORT0_MI1_OP,
		       MI1_OP_INसूचीECT_ADDRESS);
	mi1_रुको_until_पढ़ोy(adapter, A_ELMER0_PORT0_MI1_OP);

	/* Write the data. */
	__t1_tpi_ग_लिखो(adapter, A_ELMER0_PORT0_MI1_DATA, val);
	__t1_tpi_ग_लिखो(adapter, A_ELMER0_PORT0_MI1_OP, MI1_OP_INसूचीECT_WRITE);
	mi1_रुको_until_पढ़ोy(adapter, A_ELMER0_PORT0_MI1_OP);
	spin_unlock(&adapter->tpi_lock);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mdio_ops mi1_mdio_ext_ops = अणु
	.init = mi1_mdio_init,
	.पढ़ो = mi1_mdio_ext_पढ़ो,
	.ग_लिखो = mi1_mdio_ext_ग_लिखो,
	.mode_support = MDIO_SUPPORTS_C45 | MDIO_EMULATE_C22
पूर्ण;

क्रमागत अणु
	CH_BRD_T110_1CU,
	CH_BRD_N110_1F,
	CH_BRD_N210_1F,
	CH_BRD_T210_1F,
	CH_BRD_T210_1CU,
	CH_BRD_N204_4CU,
पूर्ण;

अटल स्थिर काष्ठा board_info t1_board[] = अणु
	अणु
		.board		= CHBT_BOARD_CHT110,
		.port_number	= 1,
		.caps		= SUPPORTED_10000baseT_Full,
		.chip_term	= CHBT_TERM_T1,
		.chip_mac	= CHBT_MAC_PM3393,
		.chip_phy	= CHBT_PHY_MY3126,
		.घड़ी_core	= 125000000,
		.घड़ी_mc3	= 150000000,
		.घड़ी_mc4	= 125000000,
		.espi_nports	= 1,
		.घड़ी_elmer0	= 44,
		.mdio_mdien	= 1,
		.mdio_mdiinv	= 1,
		.mdio_mdc	= 1,
		.mdio_phybaseaddr = 1,
		.gmac		= &t1_pm3393_ops,
		.gphy		= &t1_my3126_ops,
		.mdio_ops	= &mi1_mdio_ext_ops,
		.desc		= "Chelsio T110 1x10GBase-CX4 TOE",
	पूर्ण,

	अणु
		.board		= CHBT_BOARD_N110,
		.port_number	= 1,
		.caps		= SUPPORTED_10000baseT_Full | SUPPORTED_FIBRE,
		.chip_term	= CHBT_TERM_T1,
		.chip_mac	= CHBT_MAC_PM3393,
		.chip_phy	= CHBT_PHY_88X2010,
		.घड़ी_core	= 125000000,
		.espi_nports	= 1,
		.घड़ी_elmer0	= 44,
		.mdio_mdien	= 0,
		.mdio_mdiinv	= 0,
		.mdio_mdc	= 1,
		.mdio_phybaseaddr = 0,
		.gmac		= &t1_pm3393_ops,
		.gphy		= &t1_mv88x201x_ops,
		.mdio_ops	= &mi1_mdio_ext_ops,
		.desc		= "Chelsio N110 1x10GBaseX NIC",
	पूर्ण,

	अणु
		.board		= CHBT_BOARD_N210,
		.port_number	= 1,
		.caps		= SUPPORTED_10000baseT_Full | SUPPORTED_FIBRE,
		.chip_term	= CHBT_TERM_T2,
		.chip_mac	= CHBT_MAC_PM3393,
		.chip_phy	= CHBT_PHY_88X2010,
		.घड़ी_core	= 125000000,
		.espi_nports	= 1,
		.घड़ी_elmer0	= 44,
		.mdio_mdien	= 0,
		.mdio_mdiinv	= 0,
		.mdio_mdc	= 1,
		.mdio_phybaseaddr = 0,
		.gmac		= &t1_pm3393_ops,
		.gphy		= &t1_mv88x201x_ops,
		.mdio_ops	= &mi1_mdio_ext_ops,
		.desc		= "Chelsio N210 1x10GBaseX NIC",
	पूर्ण,

	अणु
		.board		= CHBT_BOARD_CHT210,
		.port_number	= 1,
		.caps		= SUPPORTED_10000baseT_Full,
		.chip_term	= CHBT_TERM_T2,
		.chip_mac	= CHBT_MAC_PM3393,
		.chip_phy	= CHBT_PHY_88X2010,
		.घड़ी_core	= 125000000,
		.घड़ी_mc3	= 133000000,
		.घड़ी_mc4	= 125000000,
		.espi_nports	= 1,
		.घड़ी_elmer0	= 44,
		.mdio_mdien	= 0,
		.mdio_mdiinv	= 0,
		.mdio_mdc	= 1,
		.mdio_phybaseaddr = 0,
		.gmac		= &t1_pm3393_ops,
		.gphy		= &t1_mv88x201x_ops,
		.mdio_ops	= &mi1_mdio_ext_ops,
		.desc		= "Chelsio T210 1x10GBaseX TOE",
	पूर्ण,

	अणु
		.board		= CHBT_BOARD_CHT210,
		.port_number	= 1,
		.caps		= SUPPORTED_10000baseT_Full,
		.chip_term	= CHBT_TERM_T2,
		.chip_mac	= CHBT_MAC_PM3393,
		.chip_phy	= CHBT_PHY_MY3126,
		.घड़ी_core	= 125000000,
		.घड़ी_mc3	= 133000000,
		.घड़ी_mc4	= 125000000,
		.espi_nports	= 1,
		.घड़ी_elmer0	= 44,
		.mdio_mdien	= 1,
		.mdio_mdiinv	= 1,
		.mdio_mdc	= 1,
		.mdio_phybaseaddr = 1,
		.gmac		= &t1_pm3393_ops,
		.gphy		= &t1_my3126_ops,
		.mdio_ops	= &mi1_mdio_ext_ops,
		.desc		= "Chelsio T210 1x10GBase-CX4 TOE",
	पूर्ण,

#अगर_घोषित CONFIG_CHELSIO_T1_1G
	अणु
		.board		= CHBT_BOARD_CHN204,
		.port_number	= 4,
		.caps		= SUPPORTED_10baseT_Half | SUPPORTED_10baseT_Full
				| SUPPORTED_100baseT_Half | SUPPORTED_100baseT_Full
				| SUPPORTED_1000baseT_Full | SUPPORTED_Autoneg |
				  SUPPORTED_PAUSE | SUPPORTED_TP,
		.chip_term	= CHBT_TERM_T2,
		.chip_mac	= CHBT_MAC_VSC7321,
		.chip_phy	= CHBT_PHY_88E1111,
		.घड़ी_core	= 100000000,
		.espi_nports	= 4,
		.घड़ी_elmer0	= 44,
		.mdio_mdien	= 0,
		.mdio_mdiinv	= 0,
		.mdio_mdc	= 0,
		.mdio_phybaseaddr = 4,
		.gmac		= &t1_vsc7326_ops,
		.gphy		= &t1_mv88e1xxx_ops,
		.mdio_ops	= &mi1_mdio_ops,
		.desc		= "Chelsio N204 4x100/1000BaseT NIC",
	पूर्ण,
#पूर्ण_अगर

पूर्ण;

स्थिर काष्ठा pci_device_id t1_pci_tbl[] = अणु
	CH_DEVICE(8, 0, CH_BRD_T110_1CU),
	CH_DEVICE(8, 1, CH_BRD_T110_1CU),
	CH_DEVICE(7, 0, CH_BRD_N110_1F),
	CH_DEVICE(10, 1, CH_BRD_N210_1F),
	CH_DEVICE(11, 1, CH_BRD_T210_1F),
	CH_DEVICE(14, 1, CH_BRD_T210_1CU),
	CH_DEVICE(16, 1, CH_BRD_N204_4CU),
	अणु 0 पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, t1_pci_tbl);

/*
 * Return the board_info काष्ठाure with a given index.  Out-of-range indices
 * वापस शून्य.
 */
स्थिर काष्ठा board_info *t1_get_board_info(अचिन्हित पूर्णांक board_id)
अणु
	वापस board_id < ARRAY_SIZE(t1_board) ? &t1_board[board_id] : शून्य;
पूर्ण

काष्ठा chelsio_vpd_t अणु
	u32 क्रमmat_version;
	u8 serial_number[16];
	u8 mac_base_address[6];
	u8 pad[2];           /* make multiple-of-4 size requirement explicit */
पूर्ण;

#घोषणा EEPROMSIZE        (8 * 1024)
#घोषणा EEPROM_MAX_POLL   4

/*
 * Read SEEPROM. A zero is written to the flag रेजिस्टर when the address is
 * written to the Control रेजिस्टर. The hardware device will set the flag to a
 * one when 4B have been transferred to the Data रेजिस्टर.
 */
पूर्णांक t1_seeprom_पढ़ो(adapter_t *adapter, u32 addr, __le32 *data)
अणु
	पूर्णांक i = EEPROM_MAX_POLL;
	u16 val;
	u32 v;

	अगर (addr >= EEPROMSIZE || (addr & 3))
		वापस -EINVAL;

	pci_ग_लिखो_config_word(adapter->pdev, A_PCICFG_VPD_ADDR, (u16)addr);
	करो अणु
		udelay(50);
		pci_पढ़ो_config_word(adapter->pdev, A_PCICFG_VPD_ADDR, &val);
	पूर्ण जबतक (!(val & F_VPD_OP_FLAG) && --i);

	अगर (!(val & F_VPD_OP_FLAG)) अणु
		pr_err("%s: reading EEPROM address 0x%x failed\n",
		       adapter->name, addr);
		वापस -EIO;
	पूर्ण
	pci_पढ़ो_config_dword(adapter->pdev, A_PCICFG_VPD_DATA, &v);
	*data = cpu_to_le32(v);
	वापस 0;
पूर्ण

अटल पूर्णांक t1_eeprom_vpd_get(adapter_t *adapter, काष्ठा chelsio_vpd_t *vpd)
अणु
	पूर्णांक addr, ret = 0;

	क्रम (addr = 0; !ret && addr < माप(*vpd); addr += माप(u32))
		ret = t1_seeprom_पढ़ो(adapter, addr,
				      (__le32 *)((u8 *)vpd + addr));

	वापस ret;
पूर्ण

/*
 * Read a port's MAC address from the VPD ROM.
 */
अटल पूर्णांक vpd_macaddress_get(adapter_t *adapter, पूर्णांक index, u8 mac_addr[])
अणु
	काष्ठा chelsio_vpd_t vpd;

	अगर (t1_eeprom_vpd_get(adapter, &vpd))
		वापस 1;
	स_नकल(mac_addr, vpd.mac_base_address, 5);
	mac_addr[5] = vpd.mac_base_address[5] + index;
	वापस 0;
पूर्ण

/*
 * Set up the MAC/PHY according to the requested link settings.
 *
 * If the PHY can स्वतः-negotiate first decide what to advertise, then
 * enable/disable स्वतः-negotiation as desired and reset.
 *
 * If the PHY करोes not स्वतः-negotiate we just reset it.
 *
 * If स्वतः-negotiation is off set the MAC to the proper speed/duplex/FC,
 * otherwise करो it later based on the outcome of स्वतः-negotiation.
 */
पूर्णांक t1_link_start(काष्ठा cphy *phy, काष्ठा cmac *mac, काष्ठा link_config *lc)
अणु
	अचिन्हित पूर्णांक fc = lc->requested_fc & (PAUSE_RX | PAUSE_TX);

	अगर (lc->supported & SUPPORTED_Autoneg) अणु
		lc->advertising &= ~(ADVERTISED_ASYM_PAUSE | ADVERTISED_PAUSE);
		अगर (fc) अणु
			अगर (fc == ((PAUSE_RX | PAUSE_TX) &
				   (mac->adapter->params.nports < 2)))
				lc->advertising |= ADVERTISED_PAUSE;
			अन्यथा अणु
				lc->advertising |= ADVERTISED_ASYM_PAUSE;
				अगर (fc == PAUSE_RX)
					lc->advertising |= ADVERTISED_PAUSE;
			पूर्ण
		पूर्ण
		phy->ops->advertise(phy, lc->advertising);

		अगर (lc->स्वतःneg == AUTONEG_DISABLE) अणु
			lc->speed = lc->requested_speed;
			lc->duplex = lc->requested_duplex;
			lc->fc = (अचिन्हित अक्षर)fc;
			mac->ops->set_speed_duplex_fc(mac, lc->speed,
						      lc->duplex, fc);
			/* Also disables स्वतःneg */
			phy->state = PHY_AUTONEG_RDY;
			phy->ops->set_speed_duplex(phy, lc->speed, lc->duplex);
			phy->ops->reset(phy, 0);
		पूर्ण अन्यथा अणु
			phy->state = PHY_AUTONEG_EN;
			phy->ops->स्वतःneg_enable(phy); /* also resets PHY */
		पूर्ण
	पूर्ण अन्यथा अणु
		phy->state = PHY_AUTONEG_RDY;
		mac->ops->set_speed_duplex_fc(mac, -1, -1, fc);
		lc->fc = (अचिन्हित अक्षर)fc;
		phy->ops->reset(phy, 0);
	पूर्ण
	वापस 0;
पूर्ण

/*
 * External पूर्णांकerrupt handler क्रम boards using elmer0.
 */
पूर्णांक t1_elmer0_ext_पूर्णांकr_handler(adapter_t *adapter)
अणु
	काष्ठा cphy *phy;
	पूर्णांक phy_cause;
	u32 cause;

	t1_tpi_पढ़ो(adapter, A_ELMER0_INT_CAUSE, &cause);

	चयन (board_info(adapter)->board) अणु
#अगर_घोषित CONFIG_CHELSIO_T1_1G
	हाल CHBT_BOARD_CHT204:
	हाल CHBT_BOARD_CHT204E:
	हाल CHBT_BOARD_CHN204:
	हाल CHBT_BOARD_CHT204V: अणु
		पूर्णांक i, port_bit;
		क्रम_each_port(adapter, i) अणु
			port_bit = i + 1;
			अगर (!(cause & (1 << port_bit)))
				जारी;

			phy = adapter->port[i].phy;
			phy_cause = phy->ops->पूर्णांकerrupt_handler(phy);
			अगर (phy_cause & cphy_cause_link_change)
				t1_link_changed(adapter, i);
		पूर्ण
		अवरोध;
	पूर्ण
	हाल CHBT_BOARD_CHT101:
		अगर (cause & ELMER0_GP_BIT1) अणु /* Marvell 88E1111 पूर्णांकerrupt */
			phy = adapter->port[0].phy;
			phy_cause = phy->ops->पूर्णांकerrupt_handler(phy);
			अगर (phy_cause & cphy_cause_link_change)
				t1_link_changed(adapter, 0);
		पूर्ण
		अवरोध;
	हाल CHBT_BOARD_7500: अणु
		पूर्णांक p;
		/*
		 * Elmer0's interrupt cause isn't useful here because there is
		 * only one bit that can be set क्रम all 4 ports.  This means
		 * we are क्रमced to check every PHY's पूर्णांकerrupt status
		 * रेजिस्टर to see who initiated the पूर्णांकerrupt.
		 */
		क्रम_each_port(adapter, p) अणु
			phy = adapter->port[p].phy;
			phy_cause = phy->ops->पूर्णांकerrupt_handler(phy);
			अगर (phy_cause & cphy_cause_link_change)
			    t1_link_changed(adapter, p);
		पूर्ण
		अवरोध;
	पूर्ण
#पूर्ण_अगर
	हाल CHBT_BOARD_CHT210:
	हाल CHBT_BOARD_N210:
	हाल CHBT_BOARD_N110:
		अगर (cause & ELMER0_GP_BIT6) अणु /* Marvell 88x2010 पूर्णांकerrupt */
			phy = adapter->port[0].phy;
			phy_cause = phy->ops->पूर्णांकerrupt_handler(phy);
			अगर (phy_cause & cphy_cause_link_change)
				t1_link_changed(adapter, 0);
		पूर्ण
		अवरोध;
	हाल CHBT_BOARD_8000:
	हाल CHBT_BOARD_CHT110:
		अगर (netअगर_msg_पूर्णांकr(adapter))
			dev_dbg(&adapter->pdev->dev,
				"External interrupt cause 0x%x\n", cause);
		अगर (cause & ELMER0_GP_BIT1) अणु        /* PMC3393 INTB */
			काष्ठा cmac *mac = adapter->port[0].mac;

			mac->ops->पूर्णांकerrupt_handler(mac);
		पूर्ण
		अगर (cause & ELMER0_GP_BIT5) अणु        /* XPAK MOD_DETECT */
			u32 mod_detect;

			t1_tpi_पढ़ो(adapter,
					A_ELMER0_GPI_STAT, &mod_detect);
			अगर (netअगर_msg_link(adapter))
				dev_info(&adapter->pdev->dev, "XPAK %s\n",
					 mod_detect ? "removed" : "inserted");
		पूर्ण
		अवरोध;
	पूर्ण
	t1_tpi_ग_लिखो(adapter, A_ELMER0_INT_CAUSE, cause);
	वापस 0;
पूर्ण

/* Enables all पूर्णांकerrupts. */
व्योम t1_पूर्णांकerrupts_enable(adapter_t *adapter)
अणु
	अचिन्हित पूर्णांक i;

	adapter->slow_पूर्णांकr_mask = F_PL_INTR_SGE_ERR | F_PL_INTR_TP;

	t1_sge_पूर्णांकr_enable(adapter->sge);
	t1_tp_पूर्णांकr_enable(adapter->tp);
	अगर (adapter->espi) अणु
		adapter->slow_पूर्णांकr_mask |= F_PL_INTR_ESPI;
		t1_espi_पूर्णांकr_enable(adapter->espi);
	पूर्ण

	/* Enable MAC/PHY पूर्णांकerrupts क्रम each port. */
	क्रम_each_port(adapter, i) अणु
		adapter->port[i].mac->ops->पूर्णांकerrupt_enable(adapter->port[i].mac);
		adapter->port[i].phy->ops->पूर्णांकerrupt_enable(adapter->port[i].phy);
	पूर्ण

	/* Enable PCIX & बाह्यal chip पूर्णांकerrupts on ASIC boards. */
	अगर (t1_is_asic(adapter)) अणु
		u32 pl_पूर्णांकr = पढ़ोl(adapter->regs + A_PL_ENABLE);

		/* PCI-X पूर्णांकerrupts */
		pci_ग_लिखो_config_dword(adapter->pdev, A_PCICFG_INTR_ENABLE,
				       0xffffffff);

		adapter->slow_पूर्णांकr_mask |= F_PL_INTR_EXT | F_PL_INTR_PCIX;
		pl_पूर्णांकr |= F_PL_INTR_EXT | F_PL_INTR_PCIX;
		ग_लिखोl(pl_पूर्णांकr, adapter->regs + A_PL_ENABLE);
	पूर्ण
पूर्ण

/* Disables all पूर्णांकerrupts. */
व्योम t1_पूर्णांकerrupts_disable(adapter_t* adapter)
अणु
	अचिन्हित पूर्णांक i;

	t1_sge_पूर्णांकr_disable(adapter->sge);
	t1_tp_पूर्णांकr_disable(adapter->tp);
	अगर (adapter->espi)
		t1_espi_पूर्णांकr_disable(adapter->espi);

	/* Disable MAC/PHY पूर्णांकerrupts क्रम each port. */
	क्रम_each_port(adapter, i) अणु
		adapter->port[i].mac->ops->पूर्णांकerrupt_disable(adapter->port[i].mac);
		adapter->port[i].phy->ops->पूर्णांकerrupt_disable(adapter->port[i].phy);
	पूर्ण

	/* Disable PCIX & बाह्यal chip पूर्णांकerrupts. */
	अगर (t1_is_asic(adapter))
		ग_लिखोl(0, adapter->regs + A_PL_ENABLE);

	/* PCI-X पूर्णांकerrupts */
	pci_ग_लिखो_config_dword(adapter->pdev, A_PCICFG_INTR_ENABLE, 0);

	adapter->slow_पूर्णांकr_mask = 0;
पूर्ण

/* Clears all पूर्णांकerrupts */
व्योम t1_पूर्णांकerrupts_clear(adapter_t* adapter)
अणु
	अचिन्हित पूर्णांक i;

	t1_sge_पूर्णांकr_clear(adapter->sge);
	t1_tp_पूर्णांकr_clear(adapter->tp);
	अगर (adapter->espi)
		t1_espi_पूर्णांकr_clear(adapter->espi);

	/* Clear MAC/PHY पूर्णांकerrupts क्रम each port. */
	क्रम_each_port(adapter, i) अणु
		adapter->port[i].mac->ops->पूर्णांकerrupt_clear(adapter->port[i].mac);
		adapter->port[i].phy->ops->पूर्णांकerrupt_clear(adapter->port[i].phy);
	पूर्ण

	/* Enable पूर्णांकerrupts क्रम बाह्यal devices. */
	अगर (t1_is_asic(adapter)) अणु
		u32 pl_पूर्णांकr = पढ़ोl(adapter->regs + A_PL_CAUSE);

		ग_लिखोl(pl_पूर्णांकr | F_PL_INTR_EXT | F_PL_INTR_PCIX,
		       adapter->regs + A_PL_CAUSE);
	पूर्ण

	/* PCI-X पूर्णांकerrupts */
	pci_ग_लिखो_config_dword(adapter->pdev, A_PCICFG_INTR_CAUSE, 0xffffffff);
पूर्ण

/*
 * Slow path पूर्णांकerrupt handler क्रम ASICs.
 */
अटल irqवापस_t asic_slow_पूर्णांकr(adapter_t *adapter)
अणु
	u32 cause = पढ़ोl(adapter->regs + A_PL_CAUSE);
	irqवापस_t ret = IRQ_HANDLED;

	cause &= adapter->slow_पूर्णांकr_mask;
	अगर (!cause)
		वापस IRQ_NONE;
	अगर (cause & F_PL_INTR_SGE_ERR) अणु
		अगर (t1_sge_पूर्णांकr_error_handler(adapter->sge))
			ret = IRQ_WAKE_THREAD;
	पूर्ण
	अगर (cause & F_PL_INTR_TP)
		t1_tp_पूर्णांकr_handler(adapter->tp);
	अगर (cause & F_PL_INTR_ESPI)
		t1_espi_पूर्णांकr_handler(adapter->espi);
	अगर (cause & F_PL_INTR_PCIX) अणु
		अगर (t1_pci_पूर्णांकr_handler(adapter))
			ret = IRQ_WAKE_THREAD;
	पूर्ण
	अगर (cause & F_PL_INTR_EXT) अणु
		/* Wake the thपढ़ोed पूर्णांकerrupt to handle बाह्यal पूर्णांकerrupts as
		 * we require a process context. We disable EXT पूर्णांकerrupts in
		 * the पूर्णांकerim and let the thपढ़ो reenable them when it's करोne.
		 */
		adapter->pending_thपढ़ो_पूर्णांकr |= F_PL_INTR_EXT;
		adapter->slow_पूर्णांकr_mask &= ~F_PL_INTR_EXT;
		ग_लिखोl(adapter->slow_पूर्णांकr_mask | F_PL_INTR_SGE_DATA,
		       adapter->regs + A_PL_ENABLE);
		ret = IRQ_WAKE_THREAD;
	पूर्ण

	/* Clear the पूर्णांकerrupts just processed. */
	ग_लिखोl(cause, adapter->regs + A_PL_CAUSE);
	पढ़ोl(adapter->regs + A_PL_CAUSE); /* flush ग_लिखोs */
	वापस ret;
पूर्ण

irqवापस_t t1_slow_पूर्णांकr_handler(adapter_t *adapter)
अणु
#अगर_घोषित CONFIG_CHELSIO_T1_1G
	अगर (!t1_is_asic(adapter))
		वापस fpga_slow_पूर्णांकr(adapter);
#पूर्ण_अगर
	वापस asic_slow_पूर्णांकr(adapter);
पूर्ण

/* Power sequencing is a work-around क्रम Intel's XPAKs. */
अटल व्योम घातer_sequence_xpak(adapter_t* adapter)
अणु
	u32 mod_detect;
	u32 gpo;

	/* Check क्रम XPAK */
	t1_tpi_पढ़ो(adapter, A_ELMER0_GPI_STAT, &mod_detect);
	अगर (!(ELMER0_GP_BIT5 & mod_detect)) अणु
		/* XPAK is present */
		t1_tpi_पढ़ो(adapter, A_ELMER0_GPO, &gpo);
		gpo |= ELMER0_GP_BIT18;
		t1_tpi_ग_लिखो(adapter, A_ELMER0_GPO, gpo);
	पूर्ण
पूर्ण

पूर्णांक t1_get_board_rev(adapter_t *adapter, स्थिर काष्ठा board_info *bi,
		     काष्ठा adapter_params *p)
अणु
	p->chip_version = bi->chip_term;
	p->is_asic = (p->chip_version != CHBT_TERM_FPGA);
	अगर (p->chip_version == CHBT_TERM_T1 ||
	    p->chip_version == CHBT_TERM_T2 ||
	    p->chip_version == CHBT_TERM_FPGA) अणु
		u32 val = पढ़ोl(adapter->regs + A_TP_PC_CONFIG);

		val = G_TP_PC_REV(val);
		अगर (val == 2)
			p->chip_revision = TERM_T1B;
		अन्यथा अगर (val == 3)
			p->chip_revision = TERM_T2;
		अन्यथा
			वापस -1;
	पूर्ण अन्यथा
		वापस -1;
	वापस 0;
पूर्ण

/*
 * Enable board components other than the Chelsio chip, such as बाह्यal MAC
 * and PHY.
 */
अटल पूर्णांक board_init(adapter_t *adapter, स्थिर काष्ठा board_info *bi)
अणु
	चयन (bi->board) अणु
	हाल CHBT_BOARD_8000:
	हाल CHBT_BOARD_N110:
	हाल CHBT_BOARD_N210:
	हाल CHBT_BOARD_CHT210:
		t1_tpi_par(adapter, 0xf);
		t1_tpi_ग_लिखो(adapter, A_ELMER0_GPO, 0x800);
		अवरोध;
	हाल CHBT_BOARD_CHT110:
		t1_tpi_par(adapter, 0xf);
		t1_tpi_ग_लिखो(adapter, A_ELMER0_GPO, 0x1800);

		/* TBD XXX Might not need.  This fixes a problem
		 *         described in the Intel SR XPAK errata.
		 */
		घातer_sequence_xpak(adapter);
		अवरोध;
#अगर_घोषित CONFIG_CHELSIO_T1_1G
	हाल CHBT_BOARD_CHT204E:
		/* add config space ग_लिखो here */
	हाल CHBT_BOARD_CHT204:
	हाल CHBT_BOARD_CHT204V:
	हाल CHBT_BOARD_CHN204:
		t1_tpi_par(adapter, 0xf);
		t1_tpi_ग_लिखो(adapter, A_ELMER0_GPO, 0x804);
		अवरोध;
	हाल CHBT_BOARD_CHT101:
	हाल CHBT_BOARD_7500:
		t1_tpi_par(adapter, 0xf);
		t1_tpi_ग_लिखो(adapter, A_ELMER0_GPO, 0x1804);
		अवरोध;
#पूर्ण_अगर
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Initialize and configure the Terminator HW modules.  Note that बाह्यal
 * MAC and PHYs are initialized separately.
 */
पूर्णांक t1_init_hw_modules(adapter_t *adapter)
अणु
	पूर्णांक err = -EIO;
	स्थिर काष्ठा board_info *bi = board_info(adapter);

	अगर (!bi->घड़ी_mc4) अणु
		u32 val = पढ़ोl(adapter->regs + A_MC4_CFG);

		ग_लिखोl(val | F_READY | F_MC4_SLOW, adapter->regs + A_MC4_CFG);
		ग_लिखोl(F_M_BUS_ENABLE | F_TCAM_RESET,
		       adapter->regs + A_MC5_CONFIG);
	पूर्ण

	अगर (adapter->espi && t1_espi_init(adapter->espi, bi->chip_mac,
					  bi->espi_nports))
		जाओ out_err;

	अगर (t1_tp_reset(adapter->tp, &adapter->params.tp, bi->घड़ी_core))
		जाओ out_err;

	err = t1_sge_configure(adapter->sge, &adapter->params.sge);
	अगर (err)
		जाओ out_err;

	err = 0;
out_err:
	वापस err;
पूर्ण

/*
 * Determine a card's PCI mode.
 */
अटल व्योम get_pci_mode(adapter_t *adapter, काष्ठा chelsio_pci_params *p)
अणु
	अटल स्थिर अचिन्हित लघु speed_map[] = अणु 33, 66, 100, 133 पूर्ण;
	u32 pci_mode;

	pci_पढ़ो_config_dword(adapter->pdev, A_PCICFG_MODE, &pci_mode);
	p->speed = speed_map[G_PCI_MODE_CLK(pci_mode)];
	p->width = (pci_mode & F_PCI_MODE_64BIT) ? 64 : 32;
	p->is_pcix = (pci_mode & F_PCI_MODE_PCIX) != 0;
पूर्ण

/*
 * Release the काष्ठाures holding the SW per-Terminator-HW-module state.
 */
व्योम t1_मुक्त_sw_modules(adapter_t *adapter)
अणु
	अचिन्हित पूर्णांक i;

	क्रम_each_port(adapter, i) अणु
		काष्ठा cmac *mac = adapter->port[i].mac;
		काष्ठा cphy *phy = adapter->port[i].phy;

		अगर (mac)
			mac->ops->destroy(mac);
		अगर (phy)
			phy->ops->destroy(phy);
	पूर्ण

	अगर (adapter->sge)
		t1_sge_destroy(adapter->sge);
	अगर (adapter->tp)
		t1_tp_destroy(adapter->tp);
	अगर (adapter->espi)
		t1_espi_destroy(adapter->espi);
पूर्ण

अटल व्योम init_link_config(काष्ठा link_config *lc,
			     स्थिर काष्ठा board_info *bi)
अणु
	lc->supported = bi->caps;
	lc->requested_speed = lc->speed = SPEED_INVALID;
	lc->requested_duplex = lc->duplex = DUPLEX_INVALID;
	lc->requested_fc = lc->fc = PAUSE_RX | PAUSE_TX;
	अगर (lc->supported & SUPPORTED_Autoneg) अणु
		lc->advertising = lc->supported;
		lc->स्वतःneg = AUTONEG_ENABLE;
		lc->requested_fc |= PAUSE_AUTONEG;
	पूर्ण अन्यथा अणु
		lc->advertising = 0;
		lc->स्वतःneg = AUTONEG_DISABLE;
	पूर्ण
पूर्ण

/*
 * Allocate and initialize the data काष्ठाures that hold the SW state of
 * the Terminator HW modules.
 */
पूर्णांक t1_init_sw_modules(adapter_t *adapter, स्थिर काष्ठा board_info *bi)
अणु
	अचिन्हित पूर्णांक i;

	adapter->params.brd_info = bi;
	adapter->params.nports = bi->port_number;
	adapter->params.stats_update_period = bi->gmac->stats_update_period;

	adapter->sge = t1_sge_create(adapter, &adapter->params.sge);
	अगर (!adapter->sge) अणु
		pr_err("%s: SGE initialization failed\n",
		       adapter->name);
		जाओ error;
	पूर्ण

	अगर (bi->espi_nports && !(adapter->espi = t1_espi_create(adapter))) अणु
		pr_err("%s: ESPI initialization failed\n",
		       adapter->name);
		जाओ error;
	पूर्ण

	adapter->tp = t1_tp_create(adapter, &adapter->params.tp);
	अगर (!adapter->tp) अणु
		pr_err("%s: TP initialization failed\n",
		       adapter->name);
		जाओ error;
	पूर्ण

	board_init(adapter, bi);
	bi->mdio_ops->init(adapter, bi);
	अगर (bi->gphy->reset)
		bi->gphy->reset(adapter);
	अगर (bi->gmac->reset)
		bi->gmac->reset(adapter);

	क्रम_each_port(adapter, i) अणु
		u8 hw_addr[6];
		काष्ठा cmac *mac;
		पूर्णांक phy_addr = bi->mdio_phybaseaddr + i;

		adapter->port[i].phy = bi->gphy->create(adapter->port[i].dev,
							phy_addr, bi->mdio_ops);
		अगर (!adapter->port[i].phy) अणु
			pr_err("%s: PHY %d initialization failed\n",
			       adapter->name, i);
			जाओ error;
		पूर्ण

		adapter->port[i].mac = mac = bi->gmac->create(adapter, i);
		अगर (!mac) अणु
			pr_err("%s: MAC %d initialization failed\n",
			       adapter->name, i);
			जाओ error;
		पूर्ण

		/*
		 * Get the port's MAC addresses either from the EEPROM अगर one
		 * exists or the one hardcoded in the MAC.
		 */
		अगर (!t1_is_asic(adapter) || bi->chip_mac == CHBT_MAC_DUMMY)
			mac->ops->macaddress_get(mac, hw_addr);
		अन्यथा अगर (vpd_macaddress_get(adapter, i, hw_addr)) अणु
			pr_err("%s: could not read MAC address from VPD ROM\n",
			       adapter->port[i].dev->name);
			जाओ error;
		पूर्ण
		स_नकल(adapter->port[i].dev->dev_addr, hw_addr, ETH_ALEN);
		init_link_config(&adapter->port[i].link_config, bi);
	पूर्ण

	get_pci_mode(adapter, &adapter->params.pci);
	t1_पूर्णांकerrupts_clear(adapter);
	वापस 0;

error:
	t1_मुक्त_sw_modules(adapter);
	वापस -1;
पूर्ण
