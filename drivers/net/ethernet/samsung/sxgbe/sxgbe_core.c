<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* 10G controller driver क्रम Samsung SoCs
 *
 * Copyright (C) 2013 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * Author: Siva Reddy Kallam <siva.kallam@samsung.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/export.h>
#समावेश <linux/पन.स>
#समावेश <linux/netdevice.h>
#समावेश <linux/phy.h>

#समावेश "sxgbe_common.h"
#समावेश "sxgbe_reg.h"

/* MAC core initialization */
अटल व्योम sxgbe_core_init(व्योम __iomem *ioaddr)
अणु
	u32 regval;

	/* TX configuration */
	regval = पढ़ोl(ioaddr + SXGBE_CORE_TX_CONFIG_REG);
	/* Other configurable parameters IFP, IPG, ISR, ISM
	 * needs to be set अगर needed
	 */
	regval |= SXGBE_TX_JABBER_DISABLE;
	ग_लिखोl(regval, ioaddr + SXGBE_CORE_TX_CONFIG_REG);

	/* RX configuration */
	regval = पढ़ोl(ioaddr + SXGBE_CORE_RX_CONFIG_REG);
	/* Other configurable parameters CST, SPEN, USP, GPSLCE
	 * WD, LM, S2KP, HDSMS, GPSL, ELEN, ARPEN needs to be
	 * set अगर needed
	 */
	regval |= SXGBE_RX_JUMBPKT_ENABLE | SXGBE_RX_ACS_ENABLE;
	ग_लिखोl(regval, ioaddr + SXGBE_CORE_RX_CONFIG_REG);
पूर्ण

/* Dump MAC रेजिस्टरs */
अटल व्योम sxgbe_core_dump_regs(व्योम __iomem *ioaddr)
अणु
पूर्ण

अटल पूर्णांक sxgbe_get_lpi_status(व्योम __iomem *ioaddr, स्थिर u32 irq_status)
अणु
	पूर्णांक status = 0;
	पूर्णांक lpi_status;

	/* Reading this रेजिस्टर shall clear all the LPI status bits */
	lpi_status = पढ़ोl(ioaddr + SXGBE_CORE_LPI_CTRL_STATUS);

	अगर (lpi_status & LPI_CTRL_STATUS_TLPIEN)
		status |= TX_ENTRY_LPI_MODE;
	अगर (lpi_status & LPI_CTRL_STATUS_TLPIEX)
		status |= TX_EXIT_LPI_MODE;
	अगर (lpi_status & LPI_CTRL_STATUS_RLPIEN)
		status |= RX_ENTRY_LPI_MODE;
	अगर (lpi_status & LPI_CTRL_STATUS_RLPIEX)
		status |= RX_EXIT_LPI_MODE;

	वापस status;
पूर्ण

/* Handle extra events on specअगरic पूर्णांकerrupts hw dependent */
अटल पूर्णांक sxgbe_core_host_irq_status(व्योम __iomem *ioaddr,
				      काष्ठा sxgbe_extra_stats *x)
अणु
	पूर्णांक irq_status, status = 0;

	irq_status = पढ़ोl(ioaddr + SXGBE_CORE_INT_STATUS_REG);

	अगर (unlikely(irq_status & LPI_INT_STATUS))
		status |= sxgbe_get_lpi_status(ioaddr, irq_status);

	वापस status;
पूर्ण

/* Set घातer management mode (e.g. magic frame) */
अटल व्योम sxgbe_core_pmt(व्योम __iomem *ioaddr, अचिन्हित दीर्घ mode)
अणु
पूर्ण

/* Set/Get Unicast MAC addresses */
अटल व्योम sxgbe_core_set_umac_addr(व्योम __iomem *ioaddr, अचिन्हित अक्षर *addr,
				     अचिन्हित पूर्णांक reg_n)
अणु
	u32 high_word, low_word;

	high_word = (addr[5] << 8) | (addr[4]);
	low_word = (addr[3] << 24) | (addr[2] << 16) |
		   (addr[1] << 8) | (addr[0]);
	ग_लिखोl(high_word, ioaddr + SXGBE_CORE_ADD_HIGHOFFSET(reg_n));
	ग_लिखोl(low_word, ioaddr + SXGBE_CORE_ADD_LOWOFFSET(reg_n));
पूर्ण

अटल व्योम sxgbe_core_get_umac_addr(व्योम __iomem *ioaddr, अचिन्हित अक्षर *addr,
				     अचिन्हित पूर्णांक reg_n)
अणु
	u32 high_word, low_word;

	high_word = पढ़ोl(ioaddr + SXGBE_CORE_ADD_HIGHOFFSET(reg_n));
	low_word = पढ़ोl(ioaddr + SXGBE_CORE_ADD_LOWOFFSET(reg_n));

	/* extract and assign address */
	addr[5] = (high_word & 0x0000FF00) >> 8;
	addr[4] = (high_word & 0x000000FF);
	addr[3] = (low_word & 0xFF000000) >> 24;
	addr[2] = (low_word & 0x00FF0000) >> 16;
	addr[1] = (low_word & 0x0000FF00) >> 8;
	addr[0] = (low_word & 0x000000FF);
पूर्ण

अटल व्योम sxgbe_enable_tx(व्योम __iomem *ioaddr, bool enable)
अणु
	u32 tx_config;

	tx_config = पढ़ोl(ioaddr + SXGBE_CORE_TX_CONFIG_REG);
	tx_config &= ~SXGBE_TX_ENABLE;

	अगर (enable)
		tx_config |= SXGBE_TX_ENABLE;
	ग_लिखोl(tx_config, ioaddr + SXGBE_CORE_TX_CONFIG_REG);
पूर्ण

अटल व्योम sxgbe_enable_rx(व्योम __iomem *ioaddr, bool enable)
अणु
	u32 rx_config;

	rx_config = पढ़ोl(ioaddr + SXGBE_CORE_RX_CONFIG_REG);
	rx_config &= ~SXGBE_RX_ENABLE;

	अगर (enable)
		rx_config |= SXGBE_RX_ENABLE;
	ग_लिखोl(rx_config, ioaddr + SXGBE_CORE_RX_CONFIG_REG);
पूर्ण

अटल पूर्णांक sxgbe_get_controller_version(व्योम __iomem *ioaddr)
अणु
	वापस पढ़ोl(ioaddr + SXGBE_CORE_VERSION_REG);
पूर्ण

/* If supported then get the optional core features */
अटल अचिन्हित पूर्णांक sxgbe_get_hw_feature(व्योम __iomem *ioaddr,
					 अचिन्हित अक्षर feature_index)
अणु
	वापस पढ़ोl(ioaddr + (SXGBE_CORE_HW_FEA_REG(feature_index)));
पूर्ण

अटल व्योम sxgbe_core_set_speed(व्योम __iomem *ioaddr, अचिन्हित अक्षर speed)
अणु
	u32 tx_cfg = पढ़ोl(ioaddr + SXGBE_CORE_TX_CONFIG_REG);

	/* clear the speed bits */
	tx_cfg &= ~0x60000000;
	tx_cfg |= (speed << SXGBE_SPEED_LSHIFT);

	/* set the speed */
	ग_लिखोl(tx_cfg, ioaddr + SXGBE_CORE_TX_CONFIG_REG);
पूर्ण

अटल व्योम sxgbe_core_enable_rxqueue(व्योम __iomem *ioaddr, पूर्णांक queue_num)
अणु
	u32 reg_val;

	reg_val = पढ़ोl(ioaddr + SXGBE_CORE_RX_CTL0_REG);
	reg_val &= ~(SXGBE_CORE_RXQ_ENABLE_MASK << queue_num);
	reg_val |= SXGBE_CORE_RXQ_ENABLE;
	ग_लिखोl(reg_val, ioaddr + SXGBE_CORE_RX_CTL0_REG);
पूर्ण

अटल व्योम sxgbe_core_disable_rxqueue(व्योम __iomem *ioaddr, पूर्णांक queue_num)
अणु
	u32 reg_val;

	reg_val = पढ़ोl(ioaddr + SXGBE_CORE_RX_CTL0_REG);
	reg_val &= ~(SXGBE_CORE_RXQ_ENABLE_MASK << queue_num);
	reg_val |= SXGBE_CORE_RXQ_DISABLE;
	ग_लिखोl(reg_val, ioaddr + SXGBE_CORE_RX_CTL0_REG);
पूर्ण

अटल व्योम  sxgbe_set_eee_mode(व्योम __iomem *ioaddr)
अणु
	u32 ctrl;

	/* Enable the LPI mode क्रम transmit path with Tx स्वतःmate bit set.
	 * When Tx Automate bit is set, MAC पूर्णांकernally handles the entry
	 * to LPI mode after all outstanding and pending packets are
	 * transmitted.
	 */
	ctrl = पढ़ोl(ioaddr + SXGBE_CORE_LPI_CTRL_STATUS);
	ctrl |= LPI_CTRL_STATUS_LPIEN | LPI_CTRL_STATUS_TXA;
	ग_लिखोl(ctrl, ioaddr + SXGBE_CORE_LPI_CTRL_STATUS);
पूर्ण

अटल व्योम  sxgbe_reset_eee_mode(व्योम __iomem *ioaddr)
अणु
	u32 ctrl;

	ctrl = पढ़ोl(ioaddr + SXGBE_CORE_LPI_CTRL_STATUS);
	ctrl &= ~(LPI_CTRL_STATUS_LPIEN | LPI_CTRL_STATUS_TXA);
	ग_लिखोl(ctrl, ioaddr + SXGBE_CORE_LPI_CTRL_STATUS);
पूर्ण

अटल व्योम  sxgbe_set_eee_pls(व्योम __iomem *ioaddr, स्थिर पूर्णांक link)
अणु
	u32 ctrl;

	ctrl = पढ़ोl(ioaddr + SXGBE_CORE_LPI_CTRL_STATUS);

	/* If the PHY link status is UP then set PLS */
	अगर (link)
		ctrl |= LPI_CTRL_STATUS_PLS;
	अन्यथा
		ctrl &= ~LPI_CTRL_STATUS_PLS;

	ग_लिखोl(ctrl, ioaddr + SXGBE_CORE_LPI_CTRL_STATUS);
पूर्ण

अटल व्योम  sxgbe_set_eee_समयr(व्योम __iomem *ioaddr,
				 स्थिर पूर्णांक ls, स्थिर पूर्णांक tw)
अणु
	पूर्णांक value = ((tw & 0xffff)) | ((ls & 0x7ff) << 16);

	/* Program the समयrs in the LPI समयr control रेजिस्टर:
	 * LS: minimum समय (ms) क्रम which the link
	 *  status from PHY should be ok beक्रमe transmitting
	 *  the LPI pattern.
	 * TW: minimum समय (us) क्रम which the core रुकोs
	 *  after it has stopped transmitting the LPI pattern.
	 */
	ग_लिखोl(value, ioaddr + SXGBE_CORE_LPI_TIMER_CTRL);
पूर्ण

अटल व्योम sxgbe_enable_rx_csum(व्योम __iomem *ioaddr)
अणु
	u32 ctrl;

	ctrl = पढ़ोl(ioaddr + SXGBE_CORE_RX_CONFIG_REG);
	ctrl |= SXGBE_RX_CSUMOFFLOAD_ENABLE;
	ग_लिखोl(ctrl, ioaddr + SXGBE_CORE_RX_CONFIG_REG);
पूर्ण

अटल व्योम sxgbe_disable_rx_csum(व्योम __iomem *ioaddr)
अणु
	u32 ctrl;

	ctrl = पढ़ोl(ioaddr + SXGBE_CORE_RX_CONFIG_REG);
	ctrl &= ~SXGBE_RX_CSUMOFFLOAD_ENABLE;
	ग_लिखोl(ctrl, ioaddr + SXGBE_CORE_RX_CONFIG_REG);
पूर्ण

अटल स्थिर काष्ठा sxgbe_core_ops core_ops = अणु
	.core_init		= sxgbe_core_init,
	.dump_regs		= sxgbe_core_dump_regs,
	.host_irq_status	= sxgbe_core_host_irq_status,
	.pmt			= sxgbe_core_pmt,
	.set_umac_addr		= sxgbe_core_set_umac_addr,
	.get_umac_addr		= sxgbe_core_get_umac_addr,
	.enable_rx		= sxgbe_enable_rx,
	.enable_tx		= sxgbe_enable_tx,
	.get_controller_version	= sxgbe_get_controller_version,
	.get_hw_feature		= sxgbe_get_hw_feature,
	.set_speed		= sxgbe_core_set_speed,
	.set_eee_mode		= sxgbe_set_eee_mode,
	.reset_eee_mode		= sxgbe_reset_eee_mode,
	.set_eee_समयr		= sxgbe_set_eee_समयr,
	.set_eee_pls		= sxgbe_set_eee_pls,
	.enable_rx_csum		= sxgbe_enable_rx_csum,
	.disable_rx_csum	= sxgbe_disable_rx_csum,
	.enable_rxqueue		= sxgbe_core_enable_rxqueue,
	.disable_rxqueue	= sxgbe_core_disable_rxqueue,
पूर्ण;

स्थिर काष्ठा sxgbe_core_ops *sxgbe_get_core_ops(व्योम)
अणु
	वापस &core_ops;
पूर्ण
