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

#समावेश <linux/पन.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/export.h>
#समावेश <linux/jअगरfies.h>

#समावेश "sxgbe_mtl.h"
#समावेश "sxgbe_reg.h"

अटल व्योम sxgbe_mtl_init(व्योम __iomem *ioaddr, अचिन्हित पूर्णांक etsalg,
			   अचिन्हित पूर्णांक raa)
अणु
	u32 reg_val;

	reg_val = पढ़ोl(ioaddr + SXGBE_MTL_OP_MODE_REG);
	reg_val &= ETS_RST;

	/* ETS Algorith */
	चयन (etsalg & SXGBE_MTL_OPMODE_ESTMASK) अणु
	हाल ETS_WRR:
		reg_val &= ETS_WRR;
		अवरोध;
	हाल ETS_WFQ:
		reg_val |= ETS_WFQ;
		अवरोध;
	हाल ETS_DWRR:
		reg_val |= ETS_DWRR;
		अवरोध;
	पूर्ण
	ग_लिखोl(reg_val, ioaddr + SXGBE_MTL_OP_MODE_REG);

	चयन (raa & SXGBE_MTL_OPMODE_RAAMASK) अणु
	हाल RAA_SP:
		reg_val &= RAA_SP;
		अवरोध;
	हाल RAA_WSP:
		reg_val |= RAA_WSP;
		अवरोध;
	पूर्ण
	ग_लिखोl(reg_val, ioaddr + SXGBE_MTL_OP_MODE_REG);
पूर्ण

/* For Dynamic DMA channel mapping क्रम Rx queue */
अटल व्योम sxgbe_mtl_dma_dm_rxqueue(व्योम __iomem *ioaddr)
अणु
	ग_लिखोl(RX_QUEUE_DYNAMIC, ioaddr + SXGBE_MTL_RXQ_DMAMAP0_REG);
	ग_लिखोl(RX_QUEUE_DYNAMIC, ioaddr + SXGBE_MTL_RXQ_DMAMAP1_REG);
	ग_लिखोl(RX_QUEUE_DYNAMIC, ioaddr + SXGBE_MTL_RXQ_DMAMAP2_REG);
पूर्ण

अटल व्योम sxgbe_mtl_set_txfअगरosize(व्योम __iomem *ioaddr, पूर्णांक queue_num,
				     पूर्णांक queue_fअगरo)
अणु
	u32 fअगरo_bits, reg_val;

	/* 0 means 256 bytes */
	fअगरo_bits = (queue_fअगरo / SXGBE_MTL_TX_FIFO_DIV) - 1;
	reg_val = पढ़ोl(ioaddr + SXGBE_MTL_TXQ_OPMODE_REG(queue_num));
	reg_val |= (fअगरo_bits << SXGBE_MTL_FIFO_LSHIFT);
	ग_लिखोl(reg_val, ioaddr + SXGBE_MTL_TXQ_OPMODE_REG(queue_num));
पूर्ण

अटल व्योम sxgbe_mtl_set_rxfअगरosize(व्योम __iomem *ioaddr, पूर्णांक queue_num,
				     पूर्णांक queue_fअगरo)
अणु
	u32 fअगरo_bits, reg_val;

	/* 0 means 256 bytes */
	fअगरo_bits = (queue_fअगरo / SXGBE_MTL_RX_FIFO_DIV)-1;
	reg_val = पढ़ोl(ioaddr + SXGBE_MTL_RXQ_OPMODE_REG(queue_num));
	reg_val |= (fअगरo_bits << SXGBE_MTL_FIFO_LSHIFT);
	ग_लिखोl(reg_val, ioaddr + SXGBE_MTL_RXQ_OPMODE_REG(queue_num));
पूर्ण

अटल व्योम sxgbe_mtl_enable_txqueue(व्योम __iomem *ioaddr, पूर्णांक queue_num)
अणु
	u32 reg_val;

	reg_val = पढ़ोl(ioaddr + SXGBE_MTL_TXQ_OPMODE_REG(queue_num));
	reg_val |= SXGBE_MTL_ENABLE_QUEUE;
	ग_लिखोl(reg_val, ioaddr + SXGBE_MTL_TXQ_OPMODE_REG(queue_num));
पूर्ण

अटल व्योम sxgbe_mtl_disable_txqueue(व्योम __iomem *ioaddr, पूर्णांक queue_num)
अणु
	u32 reg_val;

	reg_val = पढ़ोl(ioaddr + SXGBE_MTL_TXQ_OPMODE_REG(queue_num));
	reg_val &= ~SXGBE_MTL_ENABLE_QUEUE;
	ग_लिखोl(reg_val, ioaddr + SXGBE_MTL_TXQ_OPMODE_REG(queue_num));
पूर्ण

अटल व्योम sxgbe_mtl_fc_active(व्योम __iomem *ioaddr, पूर्णांक queue_num,
				पूर्णांक threshold)
अणु
	u32 reg_val;

	reg_val = पढ़ोl(ioaddr + SXGBE_MTL_RXQ_OPMODE_REG(queue_num));
	reg_val &= ~(SXGBE_MTL_FCMASK << RX_FC_ACTIVE);
	reg_val |= (threshold << RX_FC_ACTIVE);

	ग_लिखोl(reg_val, ioaddr + SXGBE_MTL_RXQ_OPMODE_REG(queue_num));
पूर्ण

अटल व्योम sxgbe_mtl_fc_enable(व्योम __iomem *ioaddr, पूर्णांक queue_num)
अणु
	u32 reg_val;

	reg_val = पढ़ोl(ioaddr + SXGBE_MTL_RXQ_OPMODE_REG(queue_num));
	reg_val |= SXGBE_MTL_ENABLE_FC;
	ग_लिखोl(reg_val, ioaddr + SXGBE_MTL_RXQ_OPMODE_REG(queue_num));
पूर्ण

अटल व्योम sxgbe_mtl_fc_deactive(व्योम __iomem *ioaddr, पूर्णांक queue_num,
				  पूर्णांक threshold)
अणु
	u32 reg_val;

	reg_val = पढ़ोl(ioaddr + SXGBE_MTL_RXQ_OPMODE_REG(queue_num));
	reg_val &= ~(SXGBE_MTL_FCMASK << RX_FC_DEACTIVE);
	reg_val |= (threshold << RX_FC_DEACTIVE);

	ग_लिखोl(reg_val, ioaddr + SXGBE_MTL_RXQ_OPMODE_REG(queue_num));
पूर्ण

अटल व्योम sxgbe_mtl_fep_enable(व्योम __iomem *ioaddr, पूर्णांक queue_num)
अणु
	u32 reg_val;

	reg_val = पढ़ोl(ioaddr + SXGBE_MTL_RXQ_OPMODE_REG(queue_num));
	reg_val |= SXGBE_MTL_RXQ_OP_FEP;

	ग_लिखोl(reg_val, ioaddr + SXGBE_MTL_RXQ_OPMODE_REG(queue_num));
पूर्ण

अटल व्योम sxgbe_mtl_fep_disable(व्योम __iomem *ioaddr, पूर्णांक queue_num)
अणु
	u32 reg_val;

	reg_val = पढ़ोl(ioaddr + SXGBE_MTL_RXQ_OPMODE_REG(queue_num));
	reg_val &= ~(SXGBE_MTL_RXQ_OP_FEP);

	ग_लिखोl(reg_val, ioaddr + SXGBE_MTL_RXQ_OPMODE_REG(queue_num));
पूर्ण

अटल व्योम sxgbe_mtl_fup_enable(व्योम __iomem *ioaddr, पूर्णांक queue_num)
अणु
	u32 reg_val;

	reg_val = पढ़ोl(ioaddr + SXGBE_MTL_RXQ_OPMODE_REG(queue_num));
	reg_val |= SXGBE_MTL_RXQ_OP_FUP;

	ग_लिखोl(reg_val, ioaddr + SXGBE_MTL_RXQ_OPMODE_REG(queue_num));
पूर्ण

अटल व्योम sxgbe_mtl_fup_disable(व्योम __iomem *ioaddr, पूर्णांक queue_num)
अणु
	u32 reg_val;

	reg_val = पढ़ोl(ioaddr + SXGBE_MTL_RXQ_OPMODE_REG(queue_num));
	reg_val &= ~(SXGBE_MTL_RXQ_OP_FUP);

	ग_लिखोl(reg_val, ioaddr + SXGBE_MTL_RXQ_OPMODE_REG(queue_num));
पूर्ण


अटल व्योम sxgbe_set_tx_mtl_mode(व्योम __iomem *ioaddr, पूर्णांक queue_num,
				  पूर्णांक tx_mode)
अणु
	u32 reg_val;

	reg_val = पढ़ोl(ioaddr + SXGBE_MTL_TXQ_OPMODE_REG(queue_num));
	/* TX specअगरic MTL mode settings */
	अगर (tx_mode == SXGBE_MTL_SFMODE) अणु
		reg_val |= SXGBE_MTL_SFMODE;
	पूर्ण अन्यथा अणु
		/* set the TTC values */
		अगर (tx_mode <= 64)
			reg_val |= MTL_CONTROL_TTC_64;
		अन्यथा अगर (tx_mode <= 96)
			reg_val |= MTL_CONTROL_TTC_96;
		अन्यथा अगर (tx_mode <= 128)
			reg_val |= MTL_CONTROL_TTC_128;
		अन्यथा अगर (tx_mode <= 192)
			reg_val |= MTL_CONTROL_TTC_192;
		अन्यथा अगर (tx_mode <= 256)
			reg_val |= MTL_CONTROL_TTC_256;
		अन्यथा अगर (tx_mode <= 384)
			reg_val |= MTL_CONTROL_TTC_384;
		अन्यथा
			reg_val |= MTL_CONTROL_TTC_512;
	पूर्ण

	/* ग_लिखो पूर्णांकo TXQ operation रेजिस्टर */
	ग_लिखोl(reg_val, ioaddr + SXGBE_MTL_TXQ_OPMODE_REG(queue_num));
पूर्ण

अटल व्योम sxgbe_set_rx_mtl_mode(व्योम __iomem *ioaddr, पूर्णांक queue_num,
				  पूर्णांक rx_mode)
अणु
	u32 reg_val;

	reg_val = पढ़ोl(ioaddr + SXGBE_MTL_RXQ_OPMODE_REG(queue_num));
	/* RX specअगरic MTL mode settings */
	अगर (rx_mode == SXGBE_RX_MTL_SFMODE) अणु
		reg_val |= SXGBE_RX_MTL_SFMODE;
	पूर्ण अन्यथा अणु
		अगर (rx_mode <= 64)
			reg_val |= MTL_CONTROL_RTC_64;
		अन्यथा अगर (rx_mode <= 96)
			reg_val |= MTL_CONTROL_RTC_96;
		अन्यथा अगर (rx_mode <= 128)
			reg_val |= MTL_CONTROL_RTC_128;
	पूर्ण

	/* ग_लिखो पूर्णांकo RXQ operation रेजिस्टर */
	ग_लिखोl(reg_val, ioaddr + SXGBE_MTL_RXQ_OPMODE_REG(queue_num));
पूर्ण

अटल स्थिर काष्ठा sxgbe_mtl_ops mtl_ops = अणु
	.mtl_set_txfअगरosize		= sxgbe_mtl_set_txfअगरosize,
	.mtl_set_rxfअगरosize		= sxgbe_mtl_set_rxfअगरosize,
	.mtl_enable_txqueue		= sxgbe_mtl_enable_txqueue,
	.mtl_disable_txqueue		= sxgbe_mtl_disable_txqueue,
	.mtl_dynamic_dma_rxqueue	= sxgbe_mtl_dma_dm_rxqueue,
	.set_tx_mtl_mode		= sxgbe_set_tx_mtl_mode,
	.set_rx_mtl_mode		= sxgbe_set_rx_mtl_mode,
	.mtl_init			= sxgbe_mtl_init,
	.mtl_fc_active			= sxgbe_mtl_fc_active,
	.mtl_fc_deactive		= sxgbe_mtl_fc_deactive,
	.mtl_fc_enable			= sxgbe_mtl_fc_enable,
	.mtl_fep_enable			= sxgbe_mtl_fep_enable,
	.mtl_fep_disable		= sxgbe_mtl_fep_disable,
	.mtl_fup_enable			= sxgbe_mtl_fup_enable,
	.mtl_fup_disable		= sxgbe_mtl_fup_disable
पूर्ण;

स्थिर काष्ठा sxgbe_mtl_ops *sxgbe_get_mtl_ops(व्योम)
अणु
	वापस &mtl_ops;
पूर्ण
