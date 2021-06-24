<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* 10G controller driver क्रम Samsung SoCs
 *
 * Copyright (C) 2013 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * Author: Siva Reddy Kallam <siva.kallam@samsung.com>
 */
#समावेश <linux/delay.h>
#समावेश <linux/export.h>
#समावेश <linux/पन.स>
#समावेश <linux/netdevice.h>
#समावेश <linux/phy.h>

#समावेश "sxgbe_common.h"
#समावेश "sxgbe_dma.h"
#समावेश "sxgbe_reg.h"
#समावेश "sxgbe_desc.h"

/* DMA core initialization */
अटल पूर्णांक sxgbe_dma_init(व्योम __iomem *ioaddr, पूर्णांक fix_burst, पूर्णांक burst_map)
अणु
	u32 reg_val;

	reg_val = पढ़ोl(ioaddr + SXGBE_DMA_SYSBUS_MODE_REG);

	/* अगर fix_burst = 0, Set UNDEF = 1 of DMA_Sys_Mode Register.
	 * अगर fix_burst = 1, Set UNDEF = 0 of DMA_Sys_Mode Register.
	 * burst_map is biपंचांगap क्रम  BLEN[4, 8, 16, 32, 64, 128 and 256].
	 * Set burst_map irrespective of fix_burst value.
	 */
	अगर (!fix_burst)
		reg_val |= SXGBE_DMA_AXI_UNDEF_BURST;

	/* ग_लिखो burst len map */
	reg_val |= (burst_map << SXGBE_DMA_BLENMAP_LSHIFT);

	ग_लिखोl(reg_val,	ioaddr + SXGBE_DMA_SYSBUS_MODE_REG);

	वापस 0;
पूर्ण

अटल व्योम sxgbe_dma_channel_init(व्योम __iomem *ioaddr, पूर्णांक cha_num,
				   पूर्णांक fix_burst, पूर्णांक pbl, dma_addr_t dma_tx,
				   dma_addr_t dma_rx, पूर्णांक t_rsize, पूर्णांक r_rsize)
अणु
	u32 reg_val;
	dma_addr_t dma_addr;

	reg_val = पढ़ोl(ioaddr + SXGBE_DMA_CHA_CTL_REG(cha_num));
	/* set the pbl */
	अगर (fix_burst) अणु
		reg_val |= SXGBE_DMA_PBL_X8MODE;
		ग_लिखोl(reg_val, ioaddr + SXGBE_DMA_CHA_CTL_REG(cha_num));
		/* program the TX pbl */
		reg_val = पढ़ोl(ioaddr + SXGBE_DMA_CHA_TXCTL_REG(cha_num));
		reg_val |= (pbl << SXGBE_DMA_TXPBL_LSHIFT);
		ग_लिखोl(reg_val, ioaddr + SXGBE_DMA_CHA_TXCTL_REG(cha_num));
		/* program the RX pbl */
		reg_val = पढ़ोl(ioaddr + SXGBE_DMA_CHA_RXCTL_REG(cha_num));
		reg_val |= (pbl << SXGBE_DMA_RXPBL_LSHIFT);
		ग_लिखोl(reg_val, ioaddr + SXGBE_DMA_CHA_RXCTL_REG(cha_num));
	पूर्ण

	/* program desc रेजिस्टरs */
	ग_लिखोl(upper_32_bits(dma_tx),
	       ioaddr + SXGBE_DMA_CHA_TXDESC_HADD_REG(cha_num));
	ग_लिखोl(lower_32_bits(dma_tx),
	       ioaddr + SXGBE_DMA_CHA_TXDESC_LADD_REG(cha_num));

	ग_लिखोl(upper_32_bits(dma_rx),
	       ioaddr + SXGBE_DMA_CHA_RXDESC_HADD_REG(cha_num));
	ग_लिखोl(lower_32_bits(dma_rx),
	       ioaddr + SXGBE_DMA_CHA_RXDESC_LADD_REG(cha_num));

	/* program tail poपूर्णांकers */
	/* assumption: upper 32 bits are स्थिरant and
	 * same as TX/RX desc list
	 */
	dma_addr = dma_tx + ((t_rsize - 1) * SXGBE_DESC_SIZE_BYTES);
	ग_लिखोl(lower_32_bits(dma_addr),
	       ioaddr + SXGBE_DMA_CHA_TXDESC_TAILPTR_REG(cha_num));

	dma_addr = dma_rx + ((r_rsize - 1) * SXGBE_DESC_SIZE_BYTES);
	ग_लिखोl(lower_32_bits(dma_addr),
	       ioaddr + SXGBE_DMA_CHA_RXDESC_LADD_REG(cha_num));
	/* program the ring sizes */
	ग_लिखोl(t_rsize - 1, ioaddr + SXGBE_DMA_CHA_TXDESC_RINGLEN_REG(cha_num));
	ग_लिखोl(r_rsize - 1, ioaddr + SXGBE_DMA_CHA_RXDESC_RINGLEN_REG(cha_num));

	/* Enable TX/RX पूर्णांकerrupts */
	ग_लिखोl(SXGBE_DMA_ENA_INT,
	       ioaddr + SXGBE_DMA_CHA_INT_ENABLE_REG(cha_num));
पूर्ण

अटल व्योम sxgbe_enable_dma_transmission(व्योम __iomem *ioaddr, पूर्णांक cha_num)
अणु
	u32 tx_config;

	tx_config = पढ़ोl(ioaddr + SXGBE_DMA_CHA_TXCTL_REG(cha_num));
	tx_config |= SXGBE_TX_START_DMA;
	ग_लिखोl(tx_config, ioaddr + SXGBE_DMA_CHA_TXCTL_REG(cha_num));
पूर्ण

अटल व्योम sxgbe_enable_dma_irq(व्योम __iomem *ioaddr, पूर्णांक dma_cnum)
अणु
	/* Enable TX/RX पूर्णांकerrupts */
	ग_लिखोl(SXGBE_DMA_ENA_INT,
	       ioaddr + SXGBE_DMA_CHA_INT_ENABLE_REG(dma_cnum));
पूर्ण

अटल व्योम sxgbe_disable_dma_irq(व्योम __iomem *ioaddr, पूर्णांक dma_cnum)
अणु
	/* Disable TX/RX पूर्णांकerrupts */
	ग_लिखोl(0, ioaddr + SXGBE_DMA_CHA_INT_ENABLE_REG(dma_cnum));
पूर्ण

अटल व्योम sxgbe_dma_start_tx(व्योम __iomem *ioaddr, पूर्णांक tchannels)
अणु
	पूर्णांक cnum;
	u32 tx_ctl_reg;

	क्रम (cnum = 0; cnum < tchannels; cnum++) अणु
		tx_ctl_reg = पढ़ोl(ioaddr + SXGBE_DMA_CHA_TXCTL_REG(cnum));
		tx_ctl_reg |= SXGBE_TX_ENABLE;
		ग_लिखोl(tx_ctl_reg,
		       ioaddr + SXGBE_DMA_CHA_TXCTL_REG(cnum));
	पूर्ण
पूर्ण

अटल व्योम sxgbe_dma_start_tx_queue(व्योम __iomem *ioaddr, पूर्णांक dma_cnum)
अणु
	u32 tx_ctl_reg;

	tx_ctl_reg = पढ़ोl(ioaddr + SXGBE_DMA_CHA_TXCTL_REG(dma_cnum));
	tx_ctl_reg |= SXGBE_TX_ENABLE;
	ग_लिखोl(tx_ctl_reg, ioaddr + SXGBE_DMA_CHA_TXCTL_REG(dma_cnum));
पूर्ण

अटल व्योम sxgbe_dma_stop_tx_queue(व्योम __iomem *ioaddr, पूर्णांक dma_cnum)
अणु
	u32 tx_ctl_reg;

	tx_ctl_reg = पढ़ोl(ioaddr + SXGBE_DMA_CHA_TXCTL_REG(dma_cnum));
	tx_ctl_reg &= ~(SXGBE_TX_ENABLE);
	ग_लिखोl(tx_ctl_reg, ioaddr + SXGBE_DMA_CHA_TXCTL_REG(dma_cnum));
पूर्ण

अटल व्योम sxgbe_dma_stop_tx(व्योम __iomem *ioaddr, पूर्णांक tchannels)
अणु
	पूर्णांक cnum;
	u32 tx_ctl_reg;

	क्रम (cnum = 0; cnum < tchannels; cnum++) अणु
		tx_ctl_reg = पढ़ोl(ioaddr + SXGBE_DMA_CHA_TXCTL_REG(cnum));
		tx_ctl_reg &= ~(SXGBE_TX_ENABLE);
		ग_लिखोl(tx_ctl_reg, ioaddr + SXGBE_DMA_CHA_TXCTL_REG(cnum));
	पूर्ण
पूर्ण

अटल व्योम sxgbe_dma_start_rx(व्योम __iomem *ioaddr, पूर्णांक rchannels)
अणु
	पूर्णांक cnum;
	u32 rx_ctl_reg;

	क्रम (cnum = 0; cnum < rchannels; cnum++) अणु
		rx_ctl_reg = पढ़ोl(ioaddr + SXGBE_DMA_CHA_RXCTL_REG(cnum));
		rx_ctl_reg |= SXGBE_RX_ENABLE;
		ग_लिखोl(rx_ctl_reg,
		       ioaddr + SXGBE_DMA_CHA_RXCTL_REG(cnum));
	पूर्ण
पूर्ण

अटल व्योम sxgbe_dma_stop_rx(व्योम __iomem *ioaddr, पूर्णांक rchannels)
अणु
	पूर्णांक cnum;
	u32 rx_ctl_reg;

	क्रम (cnum = 0; cnum < rchannels; cnum++) अणु
		rx_ctl_reg = पढ़ोl(ioaddr + SXGBE_DMA_CHA_RXCTL_REG(cnum));
		rx_ctl_reg &= ~(SXGBE_RX_ENABLE);
		ग_लिखोl(rx_ctl_reg, ioaddr + SXGBE_DMA_CHA_RXCTL_REG(cnum));
	पूर्ण
पूर्ण

अटल पूर्णांक sxgbe_tx_dma_पूर्णांक_status(व्योम __iomem *ioaddr, पूर्णांक channel_no,
				   काष्ठा sxgbe_extra_stats *x)
अणु
	u32 पूर्णांक_status = पढ़ोl(ioaddr + SXGBE_DMA_CHA_STATUS_REG(channel_no));
	u32 clear_val = 0;
	u32 ret_val = 0;

	/* TX Normal Interrupt Summary */
	अगर (likely(पूर्णांक_status & SXGBE_DMA_INT_STATUS_NIS)) अणु
		x->normal_irq_n++;
		अगर (पूर्णांक_status & SXGBE_DMA_INT_STATUS_TI) अणु
			ret_val |= handle_tx;
			x->tx_normal_irq_n++;
			clear_val |= SXGBE_DMA_INT_STATUS_TI;
		पूर्ण

		अगर (पूर्णांक_status & SXGBE_DMA_INT_STATUS_TBU) अणु
			x->tx_underflow_irq++;
			ret_val |= tx_bump_tc;
			clear_val |= SXGBE_DMA_INT_STATUS_TBU;
		पूर्ण
	पूर्ण अन्यथा अगर (unlikely(पूर्णांक_status & SXGBE_DMA_INT_STATUS_AIS)) अणु
		/* TX Abnormal Interrupt Summary */
		अगर (पूर्णांक_status & SXGBE_DMA_INT_STATUS_TPS) अणु
			ret_val |= tx_hard_error;
			clear_val |= SXGBE_DMA_INT_STATUS_TPS;
			x->tx_process_stopped_irq++;
		पूर्ण

		अगर (पूर्णांक_status & SXGBE_DMA_INT_STATUS_FBE) अणु
			ret_val |= tx_hard_error;
			x->fatal_bus_error_irq++;

			/* Assumption: FBE bit is the combination of
			 * all the bus access erros and cleared when
			 * the respective error bits cleared
			 */

			/* check क्रम actual cause */
			अगर (पूर्णांक_status & SXGBE_DMA_INT_STATUS_TEB0) अणु
				x->tx_पढ़ो_transfer_err++;
				clear_val |= SXGBE_DMA_INT_STATUS_TEB0;
			पूर्ण अन्यथा अणु
				x->tx_ग_लिखो_transfer_err++;
			पूर्ण

			अगर (पूर्णांक_status & SXGBE_DMA_INT_STATUS_TEB1) अणु
				x->tx_desc_access_err++;
				clear_val |= SXGBE_DMA_INT_STATUS_TEB1;
			पूर्ण अन्यथा अणु
				x->tx_buffer_access_err++;
			पूर्ण

			अगर (पूर्णांक_status & SXGBE_DMA_INT_STATUS_TEB2) अणु
				x->tx_data_transfer_err++;
				clear_val |= SXGBE_DMA_INT_STATUS_TEB2;
			पूर्ण
		पूर्ण

		/* context descriptor error */
		अगर (पूर्णांक_status & SXGBE_DMA_INT_STATUS_CTXTERR) अणु
			x->tx_ctxt_desc_err++;
			clear_val |= SXGBE_DMA_INT_STATUS_CTXTERR;
		पूर्ण
	पूर्ण

	/* clear the served bits */
	ग_लिखोl(clear_val, ioaddr + SXGBE_DMA_CHA_STATUS_REG(channel_no));

	वापस ret_val;
पूर्ण

अटल पूर्णांक sxgbe_rx_dma_पूर्णांक_status(व्योम __iomem *ioaddr, पूर्णांक channel_no,
				   काष्ठा sxgbe_extra_stats *x)
अणु
	u32 पूर्णांक_status = पढ़ोl(ioaddr + SXGBE_DMA_CHA_STATUS_REG(channel_no));
	u32 clear_val = 0;
	u32 ret_val = 0;

	/* RX Normal Interrupt Summary */
	अगर (likely(पूर्णांक_status & SXGBE_DMA_INT_STATUS_NIS)) अणु
		x->normal_irq_n++;
		अगर (पूर्णांक_status & SXGBE_DMA_INT_STATUS_RI) अणु
			ret_val |= handle_rx;
			x->rx_normal_irq_n++;
			clear_val |= SXGBE_DMA_INT_STATUS_RI;
		पूर्ण
	पूर्ण अन्यथा अगर (unlikely(पूर्णांक_status & SXGBE_DMA_INT_STATUS_AIS)) अणु
		/* RX Abnormal Interrupt Summary */
		अगर (पूर्णांक_status & SXGBE_DMA_INT_STATUS_RBU) अणु
			ret_val |= rx_bump_tc;
			clear_val |= SXGBE_DMA_INT_STATUS_RBU;
			x->rx_underflow_irq++;
		पूर्ण

		अगर (पूर्णांक_status & SXGBE_DMA_INT_STATUS_RPS) अणु
			ret_val |= rx_hard_error;
			clear_val |= SXGBE_DMA_INT_STATUS_RPS;
			x->rx_process_stopped_irq++;
		पूर्ण

		अगर (पूर्णांक_status & SXGBE_DMA_INT_STATUS_FBE) अणु
			ret_val |= rx_hard_error;
			x->fatal_bus_error_irq++;

			/* Assumption: FBE bit is the combination of
			 * all the bus access erros and cleared when
			 * the respective error bits cleared
			 */

			/* check क्रम actual cause */
			अगर (पूर्णांक_status & SXGBE_DMA_INT_STATUS_REB0) अणु
				x->rx_पढ़ो_transfer_err++;
				clear_val |= SXGBE_DMA_INT_STATUS_REB0;
			पूर्ण अन्यथा अणु
				x->rx_ग_लिखो_transfer_err++;
			पूर्ण

			अगर (पूर्णांक_status & SXGBE_DMA_INT_STATUS_REB1) अणु
				x->rx_desc_access_err++;
				clear_val |= SXGBE_DMA_INT_STATUS_REB1;
			पूर्ण अन्यथा अणु
				x->rx_buffer_access_err++;
			पूर्ण

			अगर (पूर्णांक_status & SXGBE_DMA_INT_STATUS_REB2) अणु
				x->rx_data_transfer_err++;
				clear_val |= SXGBE_DMA_INT_STATUS_REB2;
			पूर्ण
		पूर्ण
	पूर्ण

	/* clear the served bits */
	ग_लिखोl(clear_val, ioaddr + SXGBE_DMA_CHA_STATUS_REG(channel_no));

	वापस ret_val;
पूर्ण

/* Program the HW RX Watchकरोg */
अटल व्योम sxgbe_dma_rx_watchकरोg(व्योम __iomem *ioaddr, u32 riwt)
अणु
	u32 que_num;

	SXGBE_FOR_EACH_QUEUE(SXGBE_RX_QUEUES, que_num) अणु
		ग_लिखोl(riwt,
		       ioaddr + SXGBE_DMA_CHA_INT_RXWATCHTMR_REG(que_num));
	पूर्ण
पूर्ण

अटल व्योम sxgbe_enable_tso(व्योम __iomem *ioaddr, u8 chan_num)
अणु
	u32 ctrl;

	ctrl = पढ़ोl(ioaddr + SXGBE_DMA_CHA_TXCTL_REG(chan_num));
	ctrl |= SXGBE_DMA_CHA_TXCTL_TSE_ENABLE;
	ग_लिखोl(ctrl, ioaddr + SXGBE_DMA_CHA_TXCTL_REG(chan_num));
पूर्ण

अटल स्थिर काष्ठा sxgbe_dma_ops sxgbe_dma_ops = अणु
	.init				= sxgbe_dma_init,
	.cha_init			= sxgbe_dma_channel_init,
	.enable_dma_transmission	= sxgbe_enable_dma_transmission,
	.enable_dma_irq			= sxgbe_enable_dma_irq,
	.disable_dma_irq		= sxgbe_disable_dma_irq,
	.start_tx			= sxgbe_dma_start_tx,
	.start_tx_queue			= sxgbe_dma_start_tx_queue,
	.stop_tx			= sxgbe_dma_stop_tx,
	.stop_tx_queue			= sxgbe_dma_stop_tx_queue,
	.start_rx			= sxgbe_dma_start_rx,
	.stop_rx			= sxgbe_dma_stop_rx,
	.tx_dma_पूर्णांक_status		= sxgbe_tx_dma_पूर्णांक_status,
	.rx_dma_पूर्णांक_status		= sxgbe_rx_dma_पूर्णांक_status,
	.rx_watchकरोg			= sxgbe_dma_rx_watchकरोg,
	.enable_tso			= sxgbe_enable_tso,
पूर्ण;

स्थिर काष्ठा sxgbe_dma_ops *sxgbe_get_dma_ops(व्योम)
अणु
	वापस &sxgbe_dma_ops;
पूर्ण
