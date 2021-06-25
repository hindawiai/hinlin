<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Broadcom GENET (Gigabit Ethernet) controller driver
 *
 * Copyright (c) 2014-2020 Broadcom
 */

#घोषणा pr_fmt(fmt)				"bcmgenet: " fmt

#समावेश <linux/acpi.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <linux/types.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/माला.स>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/delay.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/pm.h>
#समावेश <linux/clk.h>
#समावेश <net/arp.h>

#समावेश <linux/mii.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/in.h>
#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/phy.h>
#समावेश <linux/platक्रमm_data/bcmgenet.h>

#समावेश <यंत्र/unaligned.h>

#समावेश "bcmgenet.h"

/* Maximum number of hardware queues, करोwnsized अगर needed */
#घोषणा GENET_MAX_MQ_CNT	4

/* Default highest priority queue क्रम multi queue support */
#घोषणा GENET_Q0_PRIORITY	0

#घोषणा GENET_Q16_RX_BD_CNT	\
	(TOTAL_DESC - priv->hw_params->rx_queues * priv->hw_params->rx_bds_per_q)
#घोषणा GENET_Q16_TX_BD_CNT	\
	(TOTAL_DESC - priv->hw_params->tx_queues * priv->hw_params->tx_bds_per_q)

#घोषणा RX_BUF_LENGTH		2048
#घोषणा SKB_ALIGNMENT		32

/* Tx/Rx DMA रेजिस्टर offset, skip 256 descriptors */
#घोषणा WORDS_PER_BD(p)		(p->hw_params->words_per_bd)
#घोषणा DMA_DESC_SIZE		(WORDS_PER_BD(priv) * माप(u32))

#घोषणा GENET_TDMA_REG_OFF	(priv->hw_params->tdma_offset + \
				TOTAL_DESC * DMA_DESC_SIZE)

#घोषणा GENET_RDMA_REG_OFF	(priv->hw_params->rdma_offset + \
				TOTAL_DESC * DMA_DESC_SIZE)

/* Forward declarations */
अटल व्योम bcmgenet_set_rx_mode(काष्ठा net_device *dev);

अटल अंतरभूत व्योम bcmgenet_ग_लिखोl(u32 value, व्योम __iomem *offset)
अणु
	/* MIPS chips strapped क्रम BE will स्वतःmagically configure the
	 * peripheral रेजिस्टरs क्रम CPU-native byte order.
	 */
	अगर (IS_ENABLED(CONFIG_MIPS) && IS_ENABLED(CONFIG_CPU_BIG_ENDIAN))
		__raw_ग_लिखोl(value, offset);
	अन्यथा
		ग_लिखोl_relaxed(value, offset);
पूर्ण

अटल अंतरभूत u32 bcmgenet_पढ़ोl(व्योम __iomem *offset)
अणु
	अगर (IS_ENABLED(CONFIG_MIPS) && IS_ENABLED(CONFIG_CPU_BIG_ENDIAN))
		वापस __raw_पढ़ोl(offset);
	अन्यथा
		वापस पढ़ोl_relaxed(offset);
पूर्ण

अटल अंतरभूत व्योम dmadesc_set_length_status(काष्ठा bcmgenet_priv *priv,
					     व्योम __iomem *d, u32 value)
अणु
	bcmgenet_ग_लिखोl(value, d + DMA_DESC_LENGTH_STATUS);
पूर्ण

अटल अंतरभूत व्योम dmadesc_set_addr(काष्ठा bcmgenet_priv *priv,
				    व्योम __iomem *d,
				    dma_addr_t addr)
अणु
	bcmgenet_ग_लिखोl(lower_32_bits(addr), d + DMA_DESC_ADDRESS_LO);

	/* Register ग_लिखोs to GISB bus can take couple hundred nanoseconds
	 * and are करोne क्रम each packet, save these expensive ग_लिखोs unless
	 * the platक्रमm is explicitly configured क्रम 64-bits/LPAE.
	 */
#अगर_घोषित CONFIG_PHYS_ADDR_T_64BIT
	अगर (priv->hw_params->flags & GENET_HAS_40BITS)
		bcmgenet_ग_लिखोl(upper_32_bits(addr), d + DMA_DESC_ADDRESS_HI);
#पूर्ण_अगर
पूर्ण

/* Combined address + length/status setter */
अटल अंतरभूत व्योम dmadesc_set(काष्ठा bcmgenet_priv *priv,
			       व्योम __iomem *d, dma_addr_t addr, u32 val)
अणु
	dmadesc_set_addr(priv, d, addr);
	dmadesc_set_length_status(priv, d, val);
पूर्ण

अटल अंतरभूत dma_addr_t dmadesc_get_addr(काष्ठा bcmgenet_priv *priv,
					  व्योम __iomem *d)
अणु
	dma_addr_t addr;

	addr = bcmgenet_पढ़ोl(d + DMA_DESC_ADDRESS_LO);

	/* Register ग_लिखोs to GISB bus can take couple hundred nanoseconds
	 * and are करोne क्रम each packet, save these expensive ग_लिखोs unless
	 * the platक्रमm is explicitly configured क्रम 64-bits/LPAE.
	 */
#अगर_घोषित CONFIG_PHYS_ADDR_T_64BIT
	अगर (priv->hw_params->flags & GENET_HAS_40BITS)
		addr |= (u64)bcmgenet_पढ़ोl(d + DMA_DESC_ADDRESS_HI) << 32;
#पूर्ण_अगर
	वापस addr;
पूर्ण

#घोषणा GENET_VER_FMT	"%1d.%1d EPHY: 0x%04x"

#घोषणा GENET_MSG_DEFAULT	(NETIF_MSG_DRV | NETIF_MSG_PROBE | \
				NETIF_MSG_LINK)

अटल अंतरभूत u32 bcmgenet_rbuf_ctrl_get(काष्ठा bcmgenet_priv *priv)
अणु
	अगर (GENET_IS_V1(priv))
		वापस bcmgenet_rbuf_पढ़ोl(priv, RBUF_FLUSH_CTRL_V1);
	अन्यथा
		वापस bcmgenet_sys_पढ़ोl(priv, SYS_RBUF_FLUSH_CTRL);
पूर्ण

अटल अंतरभूत व्योम bcmgenet_rbuf_ctrl_set(काष्ठा bcmgenet_priv *priv, u32 val)
अणु
	अगर (GENET_IS_V1(priv))
		bcmgenet_rbuf_ग_लिखोl(priv, val, RBUF_FLUSH_CTRL_V1);
	अन्यथा
		bcmgenet_sys_ग_लिखोl(priv, val, SYS_RBUF_FLUSH_CTRL);
पूर्ण

/* These macros are defined to deal with रेजिस्टर map change
 * between GENET1.1 and GENET2. Only those currently being used
 * by driver are defined.
 */
अटल अंतरभूत u32 bcmgenet_tbuf_ctrl_get(काष्ठा bcmgenet_priv *priv)
अणु
	अगर (GENET_IS_V1(priv))
		वापस bcmgenet_rbuf_पढ़ोl(priv, TBUF_CTRL_V1);
	अन्यथा
		वापस bcmgenet_पढ़ोl(priv->base +
				      priv->hw_params->tbuf_offset + TBUF_CTRL);
पूर्ण

अटल अंतरभूत व्योम bcmgenet_tbuf_ctrl_set(काष्ठा bcmgenet_priv *priv, u32 val)
अणु
	अगर (GENET_IS_V1(priv))
		bcmgenet_rbuf_ग_लिखोl(priv, val, TBUF_CTRL_V1);
	अन्यथा
		bcmgenet_ग_लिखोl(val, priv->base +
				priv->hw_params->tbuf_offset + TBUF_CTRL);
पूर्ण

अटल अंतरभूत u32 bcmgenet_bp_mc_get(काष्ठा bcmgenet_priv *priv)
अणु
	अगर (GENET_IS_V1(priv))
		वापस bcmgenet_rbuf_पढ़ोl(priv, TBUF_BP_MC_V1);
	अन्यथा
		वापस bcmgenet_पढ़ोl(priv->base +
				      priv->hw_params->tbuf_offset + TBUF_BP_MC);
पूर्ण

अटल अंतरभूत व्योम bcmgenet_bp_mc_set(काष्ठा bcmgenet_priv *priv, u32 val)
अणु
	अगर (GENET_IS_V1(priv))
		bcmgenet_rbuf_ग_लिखोl(priv, val, TBUF_BP_MC_V1);
	अन्यथा
		bcmgenet_ग_लिखोl(val, priv->base +
				priv->hw_params->tbuf_offset + TBUF_BP_MC);
पूर्ण

/* RX/TX DMA रेजिस्टर accessors */
क्रमागत dma_reg अणु
	DMA_RING_CFG = 0,
	DMA_CTRL,
	DMA_STATUS,
	DMA_SCB_BURST_SIZE,
	DMA_ARB_CTRL,
	DMA_PRIORITY_0,
	DMA_PRIORITY_1,
	DMA_PRIORITY_2,
	DMA_INDEX2RING_0,
	DMA_INDEX2RING_1,
	DMA_INDEX2RING_2,
	DMA_INDEX2RING_3,
	DMA_INDEX2RING_4,
	DMA_INDEX2RING_5,
	DMA_INDEX2RING_6,
	DMA_INDEX2RING_7,
	DMA_RING0_TIMEOUT,
	DMA_RING1_TIMEOUT,
	DMA_RING2_TIMEOUT,
	DMA_RING3_TIMEOUT,
	DMA_RING4_TIMEOUT,
	DMA_RING5_TIMEOUT,
	DMA_RING6_TIMEOUT,
	DMA_RING7_TIMEOUT,
	DMA_RING8_TIMEOUT,
	DMA_RING9_TIMEOUT,
	DMA_RING10_TIMEOUT,
	DMA_RING11_TIMEOUT,
	DMA_RING12_TIMEOUT,
	DMA_RING13_TIMEOUT,
	DMA_RING14_TIMEOUT,
	DMA_RING15_TIMEOUT,
	DMA_RING16_TIMEOUT,
पूर्ण;

अटल स्थिर u8 bcmgenet_dma_regs_v3plus[] = अणु
	[DMA_RING_CFG]		= 0x00,
	[DMA_CTRL]		= 0x04,
	[DMA_STATUS]		= 0x08,
	[DMA_SCB_BURST_SIZE]	= 0x0C,
	[DMA_ARB_CTRL]		= 0x2C,
	[DMA_PRIORITY_0]	= 0x30,
	[DMA_PRIORITY_1]	= 0x34,
	[DMA_PRIORITY_2]	= 0x38,
	[DMA_RING0_TIMEOUT]	= 0x2C,
	[DMA_RING1_TIMEOUT]	= 0x30,
	[DMA_RING2_TIMEOUT]	= 0x34,
	[DMA_RING3_TIMEOUT]	= 0x38,
	[DMA_RING4_TIMEOUT]	= 0x3c,
	[DMA_RING5_TIMEOUT]	= 0x40,
	[DMA_RING6_TIMEOUT]	= 0x44,
	[DMA_RING7_TIMEOUT]	= 0x48,
	[DMA_RING8_TIMEOUT]	= 0x4c,
	[DMA_RING9_TIMEOUT]	= 0x50,
	[DMA_RING10_TIMEOUT]	= 0x54,
	[DMA_RING11_TIMEOUT]	= 0x58,
	[DMA_RING12_TIMEOUT]	= 0x5c,
	[DMA_RING13_TIMEOUT]	= 0x60,
	[DMA_RING14_TIMEOUT]	= 0x64,
	[DMA_RING15_TIMEOUT]	= 0x68,
	[DMA_RING16_TIMEOUT]	= 0x6C,
	[DMA_INDEX2RING_0]	= 0x70,
	[DMA_INDEX2RING_1]	= 0x74,
	[DMA_INDEX2RING_2]	= 0x78,
	[DMA_INDEX2RING_3]	= 0x7C,
	[DMA_INDEX2RING_4]	= 0x80,
	[DMA_INDEX2RING_5]	= 0x84,
	[DMA_INDEX2RING_6]	= 0x88,
	[DMA_INDEX2RING_7]	= 0x8C,
पूर्ण;

अटल स्थिर u8 bcmgenet_dma_regs_v2[] = अणु
	[DMA_RING_CFG]		= 0x00,
	[DMA_CTRL]		= 0x04,
	[DMA_STATUS]		= 0x08,
	[DMA_SCB_BURST_SIZE]	= 0x0C,
	[DMA_ARB_CTRL]		= 0x30,
	[DMA_PRIORITY_0]	= 0x34,
	[DMA_PRIORITY_1]	= 0x38,
	[DMA_PRIORITY_2]	= 0x3C,
	[DMA_RING0_TIMEOUT]	= 0x2C,
	[DMA_RING1_TIMEOUT]	= 0x30,
	[DMA_RING2_TIMEOUT]	= 0x34,
	[DMA_RING3_TIMEOUT]	= 0x38,
	[DMA_RING4_TIMEOUT]	= 0x3c,
	[DMA_RING5_TIMEOUT]	= 0x40,
	[DMA_RING6_TIMEOUT]	= 0x44,
	[DMA_RING7_TIMEOUT]	= 0x48,
	[DMA_RING8_TIMEOUT]	= 0x4c,
	[DMA_RING9_TIMEOUT]	= 0x50,
	[DMA_RING10_TIMEOUT]	= 0x54,
	[DMA_RING11_TIMEOUT]	= 0x58,
	[DMA_RING12_TIMEOUT]	= 0x5c,
	[DMA_RING13_TIMEOUT]	= 0x60,
	[DMA_RING14_TIMEOUT]	= 0x64,
	[DMA_RING15_TIMEOUT]	= 0x68,
	[DMA_RING16_TIMEOUT]	= 0x6C,
पूर्ण;

अटल स्थिर u8 bcmgenet_dma_regs_v1[] = अणु
	[DMA_CTRL]		= 0x00,
	[DMA_STATUS]		= 0x04,
	[DMA_SCB_BURST_SIZE]	= 0x0C,
	[DMA_ARB_CTRL]		= 0x30,
	[DMA_PRIORITY_0]	= 0x34,
	[DMA_PRIORITY_1]	= 0x38,
	[DMA_PRIORITY_2]	= 0x3C,
	[DMA_RING0_TIMEOUT]	= 0x2C,
	[DMA_RING1_TIMEOUT]	= 0x30,
	[DMA_RING2_TIMEOUT]	= 0x34,
	[DMA_RING3_TIMEOUT]	= 0x38,
	[DMA_RING4_TIMEOUT]	= 0x3c,
	[DMA_RING5_TIMEOUT]	= 0x40,
	[DMA_RING6_TIMEOUT]	= 0x44,
	[DMA_RING7_TIMEOUT]	= 0x48,
	[DMA_RING8_TIMEOUT]	= 0x4c,
	[DMA_RING9_TIMEOUT]	= 0x50,
	[DMA_RING10_TIMEOUT]	= 0x54,
	[DMA_RING11_TIMEOUT]	= 0x58,
	[DMA_RING12_TIMEOUT]	= 0x5c,
	[DMA_RING13_TIMEOUT]	= 0x60,
	[DMA_RING14_TIMEOUT]	= 0x64,
	[DMA_RING15_TIMEOUT]	= 0x68,
	[DMA_RING16_TIMEOUT]	= 0x6C,
पूर्ण;

/* Set at runसमय once bcmgenet version is known */
अटल स्थिर u8 *bcmgenet_dma_regs;

अटल अंतरभूत काष्ठा bcmgenet_priv *dev_to_priv(काष्ठा device *dev)
अणु
	वापस netdev_priv(dev_get_drvdata(dev));
पूर्ण

अटल अंतरभूत u32 bcmgenet_tdma_पढ़ोl(काष्ठा bcmgenet_priv *priv,
				      क्रमागत dma_reg r)
अणु
	वापस bcmgenet_पढ़ोl(priv->base + GENET_TDMA_REG_OFF +
			      DMA_RINGS_SIZE + bcmgenet_dma_regs[r]);
पूर्ण

अटल अंतरभूत व्योम bcmgenet_tdma_ग_लिखोl(काष्ठा bcmgenet_priv *priv,
					u32 val, क्रमागत dma_reg r)
अणु
	bcmgenet_ग_लिखोl(val, priv->base + GENET_TDMA_REG_OFF +
			DMA_RINGS_SIZE + bcmgenet_dma_regs[r]);
पूर्ण

अटल अंतरभूत u32 bcmgenet_rdma_पढ़ोl(काष्ठा bcmgenet_priv *priv,
				      क्रमागत dma_reg r)
अणु
	वापस bcmgenet_पढ़ोl(priv->base + GENET_RDMA_REG_OFF +
			      DMA_RINGS_SIZE + bcmgenet_dma_regs[r]);
पूर्ण

अटल अंतरभूत व्योम bcmgenet_rdma_ग_लिखोl(काष्ठा bcmgenet_priv *priv,
					u32 val, क्रमागत dma_reg r)
अणु
	bcmgenet_ग_लिखोl(val, priv->base + GENET_RDMA_REG_OFF +
			DMA_RINGS_SIZE + bcmgenet_dma_regs[r]);
पूर्ण

/* RDMA/TDMA ring रेजिस्टरs and accessors
 * we merge the common fields and just prefix with T/D the रेजिस्टरs
 * having dअगरferent meaning depending on the direction
 */
क्रमागत dma_ring_reg अणु
	TDMA_READ_PTR = 0,
	RDMA_WRITE_PTR = TDMA_READ_PTR,
	TDMA_READ_PTR_HI,
	RDMA_WRITE_PTR_HI = TDMA_READ_PTR_HI,
	TDMA_CONS_INDEX,
	RDMA_PROD_INDEX = TDMA_CONS_INDEX,
	TDMA_PROD_INDEX,
	RDMA_CONS_INDEX = TDMA_PROD_INDEX,
	DMA_RING_BUF_SIZE,
	DMA_START_ADDR,
	DMA_START_ADDR_HI,
	DMA_END_ADDR,
	DMA_END_ADDR_HI,
	DMA_MBUF_DONE_THRESH,
	TDMA_FLOW_PERIOD,
	RDMA_XON_XOFF_THRESH = TDMA_FLOW_PERIOD,
	TDMA_WRITE_PTR,
	RDMA_READ_PTR = TDMA_WRITE_PTR,
	TDMA_WRITE_PTR_HI,
	RDMA_READ_PTR_HI = TDMA_WRITE_PTR_HI
पूर्ण;

/* GENET v4 supports 40-bits poपूर्णांकer addressing
 * क्रम obvious reasons the LO and HI word parts
 * are contiguous, but this offsets the other
 * रेजिस्टरs.
 */
अटल स्थिर u8 genet_dma_ring_regs_v4[] = अणु
	[TDMA_READ_PTR]			= 0x00,
	[TDMA_READ_PTR_HI]		= 0x04,
	[TDMA_CONS_INDEX]		= 0x08,
	[TDMA_PROD_INDEX]		= 0x0C,
	[DMA_RING_BUF_SIZE]		= 0x10,
	[DMA_START_ADDR]		= 0x14,
	[DMA_START_ADDR_HI]		= 0x18,
	[DMA_END_ADDR]			= 0x1C,
	[DMA_END_ADDR_HI]		= 0x20,
	[DMA_MBUF_DONE_THRESH]		= 0x24,
	[TDMA_FLOW_PERIOD]		= 0x28,
	[TDMA_WRITE_PTR]		= 0x2C,
	[TDMA_WRITE_PTR_HI]		= 0x30,
पूर्ण;

अटल स्थिर u8 genet_dma_ring_regs_v123[] = अणु
	[TDMA_READ_PTR]			= 0x00,
	[TDMA_CONS_INDEX]		= 0x04,
	[TDMA_PROD_INDEX]		= 0x08,
	[DMA_RING_BUF_SIZE]		= 0x0C,
	[DMA_START_ADDR]		= 0x10,
	[DMA_END_ADDR]			= 0x14,
	[DMA_MBUF_DONE_THRESH]		= 0x18,
	[TDMA_FLOW_PERIOD]		= 0x1C,
	[TDMA_WRITE_PTR]		= 0x20,
पूर्ण;

/* Set at runसमय once GENET version is known */
अटल स्थिर u8 *genet_dma_ring_regs;

अटल अंतरभूत u32 bcmgenet_tdma_ring_पढ़ोl(काष्ठा bcmgenet_priv *priv,
					   अचिन्हित पूर्णांक ring,
					   क्रमागत dma_ring_reg r)
अणु
	वापस bcmgenet_पढ़ोl(priv->base + GENET_TDMA_REG_OFF +
			      (DMA_RING_SIZE * ring) +
			      genet_dma_ring_regs[r]);
पूर्ण

अटल अंतरभूत व्योम bcmgenet_tdma_ring_ग_लिखोl(काष्ठा bcmgenet_priv *priv,
					     अचिन्हित पूर्णांक ring, u32 val,
					     क्रमागत dma_ring_reg r)
अणु
	bcmgenet_ग_लिखोl(val, priv->base + GENET_TDMA_REG_OFF +
			(DMA_RING_SIZE * ring) +
			genet_dma_ring_regs[r]);
पूर्ण

अटल अंतरभूत u32 bcmgenet_rdma_ring_पढ़ोl(काष्ठा bcmgenet_priv *priv,
					   अचिन्हित पूर्णांक ring,
					   क्रमागत dma_ring_reg r)
अणु
	वापस bcmgenet_पढ़ोl(priv->base + GENET_RDMA_REG_OFF +
			      (DMA_RING_SIZE * ring) +
			      genet_dma_ring_regs[r]);
पूर्ण

अटल अंतरभूत व्योम bcmgenet_rdma_ring_ग_लिखोl(काष्ठा bcmgenet_priv *priv,
					     अचिन्हित पूर्णांक ring, u32 val,
					     क्रमागत dma_ring_reg r)
अणु
	bcmgenet_ग_लिखोl(val, priv->base + GENET_RDMA_REG_OFF +
			(DMA_RING_SIZE * ring) +
			genet_dma_ring_regs[r]);
पूर्ण

अटल व्योम bcmgenet_hfb_enable_filter(काष्ठा bcmgenet_priv *priv, u32 f_index)
अणु
	u32 offset;
	u32 reg;

	offset = HFB_FLT_ENABLE_V3PLUS + (f_index < 32) * माप(u32);
	reg = bcmgenet_hfb_reg_पढ़ोl(priv, offset);
	reg |= (1 << (f_index % 32));
	bcmgenet_hfb_reg_ग_लिखोl(priv, reg, offset);
	reg = bcmgenet_hfb_reg_पढ़ोl(priv, HFB_CTRL);
	reg |= RBUF_HFB_EN;
	bcmgenet_hfb_reg_ग_लिखोl(priv, reg, HFB_CTRL);
पूर्ण

अटल व्योम bcmgenet_hfb_disable_filter(काष्ठा bcmgenet_priv *priv, u32 f_index)
अणु
	u32 offset, reg, reg1;

	offset = HFB_FLT_ENABLE_V3PLUS;
	reg = bcmgenet_hfb_reg_पढ़ोl(priv, offset);
	reg1 = bcmgenet_hfb_reg_पढ़ोl(priv, offset + माप(u32));
	अगर  (f_index < 32) अणु
		reg1 &= ~(1 << (f_index % 32));
		bcmgenet_hfb_reg_ग_लिखोl(priv, reg1, offset + माप(u32));
	पूर्ण अन्यथा अणु
		reg &= ~(1 << (f_index % 32));
		bcmgenet_hfb_reg_ग_लिखोl(priv, reg, offset);
	पूर्ण
	अगर (!reg && !reg1) अणु
		reg = bcmgenet_hfb_reg_पढ़ोl(priv, HFB_CTRL);
		reg &= ~RBUF_HFB_EN;
		bcmgenet_hfb_reg_ग_लिखोl(priv, reg, HFB_CTRL);
	पूर्ण
पूर्ण

अटल व्योम bcmgenet_hfb_set_filter_rx_queue_mapping(काष्ठा bcmgenet_priv *priv,
						     u32 f_index, u32 rx_queue)
अणु
	u32 offset;
	u32 reg;

	offset = f_index / 8;
	reg = bcmgenet_rdma_पढ़ोl(priv, DMA_INDEX2RING_0 + offset);
	reg &= ~(0xF << (4 * (f_index % 8)));
	reg |= ((rx_queue & 0xF) << (4 * (f_index % 8)));
	bcmgenet_rdma_ग_लिखोl(priv, reg, DMA_INDEX2RING_0 + offset);
पूर्ण

अटल व्योम bcmgenet_hfb_set_filter_length(काष्ठा bcmgenet_priv *priv,
					   u32 f_index, u32 f_length)
अणु
	u32 offset;
	u32 reg;

	offset = HFB_FLT_LEN_V3PLUS +
		 ((priv->hw_params->hfb_filter_cnt - 1 - f_index) / 4) *
		 माप(u32);
	reg = bcmgenet_hfb_reg_पढ़ोl(priv, offset);
	reg &= ~(0xFF << (8 * (f_index % 4)));
	reg |= ((f_length & 0xFF) << (8 * (f_index % 4)));
	bcmgenet_hfb_reg_ग_लिखोl(priv, reg, offset);
पूर्ण

अटल पूर्णांक bcmgenet_hfb_validate_mask(व्योम *mask, माप_प्रकार size)
अणु
	जबतक (size) अणु
		चयन (*(अचिन्हित अक्षर *)mask++) अणु
		हाल 0x00:
		हाल 0x0f:
		हाल 0xf0:
		हाल 0xff:
			size--;
			जारी;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा VALIDATE_MASK(x) \
	bcmgenet_hfb_validate_mask(&(x), माप(x))

अटल पूर्णांक bcmgenet_hfb_insert_data(काष्ठा bcmgenet_priv *priv, u32 f_index,
				    u32 offset, व्योम *val, व्योम *mask,
				    माप_प्रकार size)
अणु
	u32 index, पंचांगp;

	index = f_index * priv->hw_params->hfb_filter_size + offset / 2;
	पंचांगp = bcmgenet_hfb_पढ़ोl(priv, index * माप(u32));

	जबतक (size--) अणु
		अगर (offset++ & 1) अणु
			पंचांगp &= ~0x300FF;
			पंचांगp |= (*(अचिन्हित अक्षर *)val++);
			चयन ((*(अचिन्हित अक्षर *)mask++)) अणु
			हाल 0xFF:
				पंचांगp |= 0x30000;
				अवरोध;
			हाल 0xF0:
				पंचांगp |= 0x20000;
				अवरोध;
			हाल 0x0F:
				पंचांगp |= 0x10000;
				अवरोध;
			पूर्ण
			bcmgenet_hfb_ग_लिखोl(priv, पंचांगp, index++ * माप(u32));
			अगर (size)
				पंचांगp = bcmgenet_hfb_पढ़ोl(priv,
							 index * माप(u32));
		पूर्ण अन्यथा अणु
			पंचांगp &= ~0xCFF00;
			पंचांगp |= (*(अचिन्हित अक्षर *)val++) << 8;
			चयन ((*(अचिन्हित अक्षर *)mask++)) अणु
			हाल 0xFF:
				पंचांगp |= 0xC0000;
				अवरोध;
			हाल 0xF0:
				पंचांगp |= 0x80000;
				अवरोध;
			हाल 0x0F:
				पंचांगp |= 0x40000;
				अवरोध;
			पूर्ण
			अगर (!size)
				bcmgenet_hfb_ग_लिखोl(priv, पंचांगp, index * माप(u32));
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम bcmgenet_hfb_create_rxnfc_filter(काष्ठा bcmgenet_priv *priv,
					     काष्ठा bcmgenet_rxnfc_rule *rule)
अणु
	काष्ठा ethtool_rx_flow_spec *fs = &rule->fs;
	u32 offset = 0, f_length = 0, f;
	u8 val_8, mask_8;
	__be16 val_16;
	u16 mask_16;
	माप_प्रकार size;

	f = fs->location;
	अगर (fs->flow_type & FLOW_MAC_EXT) अणु
		bcmgenet_hfb_insert_data(priv, f, 0,
					 &fs->h_ext.h_dest, &fs->m_ext.h_dest,
					 माप(fs->h_ext.h_dest));
	पूर्ण

	अगर (fs->flow_type & FLOW_EXT) अणु
		अगर (fs->m_ext.vlan_etype ||
		    fs->m_ext.vlan_tci) अणु
			bcmgenet_hfb_insert_data(priv, f, 12,
						 &fs->h_ext.vlan_etype,
						 &fs->m_ext.vlan_etype,
						 माप(fs->h_ext.vlan_etype));
			bcmgenet_hfb_insert_data(priv, f, 14,
						 &fs->h_ext.vlan_tci,
						 &fs->m_ext.vlan_tci,
						 माप(fs->h_ext.vlan_tci));
			offset += VLAN_HLEN;
			f_length += DIV_ROUND_UP(VLAN_HLEN, 2);
		पूर्ण
	पूर्ण

	चयन (fs->flow_type & ~(FLOW_EXT | FLOW_MAC_EXT)) अणु
	हाल ETHER_FLOW:
		f_length += DIV_ROUND_UP(ETH_HLEN, 2);
		bcmgenet_hfb_insert_data(priv, f, 0,
					 &fs->h_u.ether_spec.h_dest,
					 &fs->m_u.ether_spec.h_dest,
					 माप(fs->h_u.ether_spec.h_dest));
		bcmgenet_hfb_insert_data(priv, f, ETH_ALEN,
					 &fs->h_u.ether_spec.h_source,
					 &fs->m_u.ether_spec.h_source,
					 माप(fs->h_u.ether_spec.h_source));
		bcmgenet_hfb_insert_data(priv, f, (2 * ETH_ALEN) + offset,
					 &fs->h_u.ether_spec.h_proto,
					 &fs->m_u.ether_spec.h_proto,
					 माप(fs->h_u.ether_spec.h_proto));
		अवरोध;
	हाल IP_USER_FLOW:
		f_length += DIV_ROUND_UP(ETH_HLEN + 20, 2);
		/* Specअगरy IP Ether Type */
		val_16 = htons(ETH_P_IP);
		mask_16 = 0xFFFF;
		bcmgenet_hfb_insert_data(priv, f, (2 * ETH_ALEN) + offset,
					 &val_16, &mask_16, माप(val_16));
		bcmgenet_hfb_insert_data(priv, f, 15 + offset,
					 &fs->h_u.usr_ip4_spec.tos,
					 &fs->m_u.usr_ip4_spec.tos,
					 माप(fs->h_u.usr_ip4_spec.tos));
		bcmgenet_hfb_insert_data(priv, f, 23 + offset,
					 &fs->h_u.usr_ip4_spec.proto,
					 &fs->m_u.usr_ip4_spec.proto,
					 माप(fs->h_u.usr_ip4_spec.proto));
		bcmgenet_hfb_insert_data(priv, f, 26 + offset,
					 &fs->h_u.usr_ip4_spec.ip4src,
					 &fs->m_u.usr_ip4_spec.ip4src,
					 माप(fs->h_u.usr_ip4_spec.ip4src));
		bcmgenet_hfb_insert_data(priv, f, 30 + offset,
					 &fs->h_u.usr_ip4_spec.ip4dst,
					 &fs->m_u.usr_ip4_spec.ip4dst,
					 माप(fs->h_u.usr_ip4_spec.ip4dst));
		अगर (!fs->m_u.usr_ip4_spec.l4_4_bytes)
			अवरोध;

		/* Only supports 20 byte IPv4 header */
		val_8 = 0x45;
		mask_8 = 0xFF;
		bcmgenet_hfb_insert_data(priv, f, ETH_HLEN + offset,
					 &val_8, &mask_8,
					 माप(val_8));
		size = माप(fs->h_u.usr_ip4_spec.l4_4_bytes);
		bcmgenet_hfb_insert_data(priv, f,
					 ETH_HLEN + 20 + offset,
					 &fs->h_u.usr_ip4_spec.l4_4_bytes,
					 &fs->m_u.usr_ip4_spec.l4_4_bytes,
					 size);
		f_length += DIV_ROUND_UP(size, 2);
		अवरोध;
	पूर्ण

	bcmgenet_hfb_set_filter_length(priv, f, 2 * f_length);
	अगर (!fs->ring_cookie || fs->ring_cookie == RX_CLS_FLOW_WAKE) अणु
		/* Ring 0 flows can be handled by the शेष Descriptor Ring
		 * We'll map them to ring 0, but don't enable the filter
		 */
		bcmgenet_hfb_set_filter_rx_queue_mapping(priv, f, 0);
		rule->state = BCMGENET_RXNFC_STATE_DISABLED;
	पूर्ण अन्यथा अणु
		/* Other Rx rings are direct mapped here */
		bcmgenet_hfb_set_filter_rx_queue_mapping(priv, f,
							 fs->ring_cookie);
		bcmgenet_hfb_enable_filter(priv, f);
		rule->state = BCMGENET_RXNFC_STATE_ENABLED;
	पूर्ण
पूर्ण

/* bcmgenet_hfb_clear
 *
 * Clear Hardware Filter Block and disable all filtering.
 */
अटल व्योम bcmgenet_hfb_clear_filter(काष्ठा bcmgenet_priv *priv, u32 f_index)
अणु
	u32 base, i;

	base = f_index * priv->hw_params->hfb_filter_size;
	क्रम (i = 0; i < priv->hw_params->hfb_filter_size; i++)
		bcmgenet_hfb_ग_लिखोl(priv, 0x0, (base + i) * माप(u32));
पूर्ण

अटल व्योम bcmgenet_hfb_clear(काष्ठा bcmgenet_priv *priv)
अणु
	u32 i;

	अगर (GENET_IS_V1(priv) || GENET_IS_V2(priv))
		वापस;

	bcmgenet_hfb_reg_ग_लिखोl(priv, 0x0, HFB_CTRL);
	bcmgenet_hfb_reg_ग_लिखोl(priv, 0x0, HFB_FLT_ENABLE_V3PLUS);
	bcmgenet_hfb_reg_ग_लिखोl(priv, 0x0, HFB_FLT_ENABLE_V3PLUS + 4);

	क्रम (i = DMA_INDEX2RING_0; i <= DMA_INDEX2RING_7; i++)
		bcmgenet_rdma_ग_लिखोl(priv, 0x0, i);

	क्रम (i = 0; i < (priv->hw_params->hfb_filter_cnt / 4); i++)
		bcmgenet_hfb_reg_ग_लिखोl(priv, 0x0,
					HFB_FLT_LEN_V3PLUS + i * माप(u32));

	क्रम (i = 0; i < priv->hw_params->hfb_filter_cnt; i++)
		bcmgenet_hfb_clear_filter(priv, i);
पूर्ण

अटल व्योम bcmgenet_hfb_init(काष्ठा bcmgenet_priv *priv)
अणु
	पूर्णांक i;

	INIT_LIST_HEAD(&priv->rxnfc_list);
	अगर (GENET_IS_V1(priv) || GENET_IS_V2(priv))
		वापस;

	क्रम (i = 0; i < MAX_NUM_OF_FS_RULES; i++) अणु
		INIT_LIST_HEAD(&priv->rxnfc_rules[i].list);
		priv->rxnfc_rules[i].state = BCMGENET_RXNFC_STATE_UNUSED;
	पूर्ण

	bcmgenet_hfb_clear(priv);
पूर्ण

अटल पूर्णांक bcmgenet_begin(काष्ठा net_device *dev)
अणु
	काष्ठा bcmgenet_priv *priv = netdev_priv(dev);

	/* Turn on the घड़ी */
	वापस clk_prepare_enable(priv->clk);
पूर्ण

अटल व्योम bcmgenet_complete(काष्ठा net_device *dev)
अणु
	काष्ठा bcmgenet_priv *priv = netdev_priv(dev);

	/* Turn off the घड़ी */
	clk_disable_unprepare(priv->clk);
पूर्ण

अटल पूर्णांक bcmgenet_get_link_ksettings(काष्ठा net_device *dev,
				       काष्ठा ethtool_link_ksettings *cmd)
अणु
	अगर (!netअगर_running(dev))
		वापस -EINVAL;

	अगर (!dev->phydev)
		वापस -ENODEV;

	phy_ethtool_ksettings_get(dev->phydev, cmd);

	वापस 0;
पूर्ण

अटल पूर्णांक bcmgenet_set_link_ksettings(काष्ठा net_device *dev,
				       स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	अगर (!netअगर_running(dev))
		वापस -EINVAL;

	अगर (!dev->phydev)
		वापस -ENODEV;

	वापस phy_ethtool_ksettings_set(dev->phydev, cmd);
पूर्ण

अटल पूर्णांक bcmgenet_set_features(काष्ठा net_device *dev,
				 netdev_features_t features)
अणु
	काष्ठा bcmgenet_priv *priv = netdev_priv(dev);
	u32 reg;
	पूर्णांक ret;

	ret = clk_prepare_enable(priv->clk);
	अगर (ret)
		वापस ret;

	/* Make sure we reflect the value of CRC_CMD_FWD */
	reg = bcmgenet_umac_पढ़ोl(priv, UMAC_CMD);
	priv->crc_fwd_en = !!(reg & CMD_CRC_FWD);

	clk_disable_unprepare(priv->clk);

	वापस ret;
पूर्ण

अटल u32 bcmgenet_get_msglevel(काष्ठा net_device *dev)
अणु
	काष्ठा bcmgenet_priv *priv = netdev_priv(dev);

	वापस priv->msg_enable;
पूर्ण

अटल व्योम bcmgenet_set_msglevel(काष्ठा net_device *dev, u32 level)
अणु
	काष्ठा bcmgenet_priv *priv = netdev_priv(dev);

	priv->msg_enable = level;
पूर्ण

अटल पूर्णांक bcmgenet_get_coalesce(काष्ठा net_device *dev,
				 काष्ठा ethtool_coalesce *ec)
अणु
	काष्ठा bcmgenet_priv *priv = netdev_priv(dev);
	काष्ठा bcmgenet_rx_ring *ring;
	अचिन्हित पूर्णांक i;

	ec->tx_max_coalesced_frames =
		bcmgenet_tdma_ring_पढ़ोl(priv, DESC_INDEX,
					 DMA_MBUF_DONE_THRESH);
	ec->rx_max_coalesced_frames =
		bcmgenet_rdma_ring_पढ़ोl(priv, DESC_INDEX,
					 DMA_MBUF_DONE_THRESH);
	ec->rx_coalesce_usecs =
		bcmgenet_rdma_पढ़ोl(priv, DMA_RING16_TIMEOUT) * 8192 / 1000;

	क्रम (i = 0; i < priv->hw_params->rx_queues; i++) अणु
		ring = &priv->rx_rings[i];
		ec->use_adaptive_rx_coalesce |= ring->dim.use_dim;
	पूर्ण
	ring = &priv->rx_rings[DESC_INDEX];
	ec->use_adaptive_rx_coalesce |= ring->dim.use_dim;

	वापस 0;
पूर्ण

अटल व्योम bcmgenet_set_rx_coalesce(काष्ठा bcmgenet_rx_ring *ring,
				     u32 usecs, u32 pkts)
अणु
	काष्ठा bcmgenet_priv *priv = ring->priv;
	अचिन्हित पूर्णांक i = ring->index;
	u32 reg;

	bcmgenet_rdma_ring_ग_लिखोl(priv, i, pkts, DMA_MBUF_DONE_THRESH);

	reg = bcmgenet_rdma_पढ़ोl(priv, DMA_RING0_TIMEOUT + i);
	reg &= ~DMA_TIMEOUT_MASK;
	reg |= DIV_ROUND_UP(usecs * 1000, 8192);
	bcmgenet_rdma_ग_लिखोl(priv, reg, DMA_RING0_TIMEOUT + i);
पूर्ण

अटल व्योम bcmgenet_set_ring_rx_coalesce(काष्ठा bcmgenet_rx_ring *ring,
					  काष्ठा ethtool_coalesce *ec)
अणु
	काष्ठा dim_cq_moder moder;
	u32 usecs, pkts;

	ring->rx_coalesce_usecs = ec->rx_coalesce_usecs;
	ring->rx_max_coalesced_frames = ec->rx_max_coalesced_frames;
	usecs = ring->rx_coalesce_usecs;
	pkts = ring->rx_max_coalesced_frames;

	अगर (ec->use_adaptive_rx_coalesce && !ring->dim.use_dim) अणु
		moder = net_dim_get_def_rx_moderation(ring->dim.dim.mode);
		usecs = moder.usec;
		pkts = moder.pkts;
	पूर्ण

	ring->dim.use_dim = ec->use_adaptive_rx_coalesce;
	bcmgenet_set_rx_coalesce(ring, usecs, pkts);
पूर्ण

अटल पूर्णांक bcmgenet_set_coalesce(काष्ठा net_device *dev,
				 काष्ठा ethtool_coalesce *ec)
अणु
	काष्ठा bcmgenet_priv *priv = netdev_priv(dev);
	अचिन्हित पूर्णांक i;

	/* Base प्रणाली घड़ी is 125Mhz, DMA समयout is this reference घड़ी
	 * भागided by 1024, which yields roughly 8.192us, our maximum value
	 * has to fit in the DMA_TIMEOUT_MASK (16 bits)
	 */
	अगर (ec->tx_max_coalesced_frames > DMA_INTR_THRESHOLD_MASK ||
	    ec->tx_max_coalesced_frames == 0 ||
	    ec->rx_max_coalesced_frames > DMA_INTR_THRESHOLD_MASK ||
	    ec->rx_coalesce_usecs > (DMA_TIMEOUT_MASK * 8) + 1)
		वापस -EINVAL;

	अगर (ec->rx_coalesce_usecs == 0 && ec->rx_max_coalesced_frames == 0)
		वापस -EINVAL;

	/* GENET TDMA hardware करोes not support a configurable समयout, but will
	 * always generate an पूर्णांकerrupt either after MBDONE packets have been
	 * transmitted, or when the ring is empty.
	 */

	/* Program all TX queues with the same values, as there is no
	 * ethtool knob to करो coalescing on a per-queue basis
	 */
	क्रम (i = 0; i < priv->hw_params->tx_queues; i++)
		bcmgenet_tdma_ring_ग_लिखोl(priv, i,
					  ec->tx_max_coalesced_frames,
					  DMA_MBUF_DONE_THRESH);
	bcmgenet_tdma_ring_ग_लिखोl(priv, DESC_INDEX,
				  ec->tx_max_coalesced_frames,
				  DMA_MBUF_DONE_THRESH);

	क्रम (i = 0; i < priv->hw_params->rx_queues; i++)
		bcmgenet_set_ring_rx_coalesce(&priv->rx_rings[i], ec);
	bcmgenet_set_ring_rx_coalesce(&priv->rx_rings[DESC_INDEX], ec);

	वापस 0;
पूर्ण

/* standard ethtool support functions. */
क्रमागत bcmgenet_stat_type अणु
	BCMGENET_STAT_NETDEV = -1,
	BCMGENET_STAT_MIB_RX,
	BCMGENET_STAT_MIB_TX,
	BCMGENET_STAT_RUNT,
	BCMGENET_STAT_MISC,
	BCMGENET_STAT_SOFT,
पूर्ण;

काष्ठा bcmgenet_stats अणु
	अक्षर stat_string[ETH_GSTRING_LEN];
	पूर्णांक stat_माप;
	पूर्णांक stat_offset;
	क्रमागत bcmgenet_stat_type type;
	/* reg offset from UMAC base क्रम misc counters */
	u16 reg_offset;
पूर्ण;

#घोषणा STAT_NETDEV(m) अणु \
	.stat_string = __stringअगरy(m), \
	.stat_माप = माप(((काष्ठा net_device_stats *)0)->m), \
	.stat_offset = दुरत्व(काष्ठा net_device_stats, m), \
	.type = BCMGENET_STAT_NETDEV, \
पूर्ण

#घोषणा STAT_GENET_MIB(str, m, _type) अणु \
	.stat_string = str, \
	.stat_माप = माप(((काष्ठा bcmgenet_priv *)0)->m), \
	.stat_offset = दुरत्व(काष्ठा bcmgenet_priv, m), \
	.type = _type, \
पूर्ण

#घोषणा STAT_GENET_MIB_RX(str, m) STAT_GENET_MIB(str, m, BCMGENET_STAT_MIB_RX)
#घोषणा STAT_GENET_MIB_TX(str, m) STAT_GENET_MIB(str, m, BCMGENET_STAT_MIB_TX)
#घोषणा STAT_GENET_RUNT(str, m) STAT_GENET_MIB(str, m, BCMGENET_STAT_RUNT)
#घोषणा STAT_GENET_SOFT_MIB(str, m) STAT_GENET_MIB(str, m, BCMGENET_STAT_SOFT)

#घोषणा STAT_GENET_MISC(str, m, offset) अणु \
	.stat_string = str, \
	.stat_माप = माप(((काष्ठा bcmgenet_priv *)0)->m), \
	.stat_offset = दुरत्व(काष्ठा bcmgenet_priv, m), \
	.type = BCMGENET_STAT_MISC, \
	.reg_offset = offset, \
पूर्ण

#घोषणा STAT_GENET_Q(num) \
	STAT_GENET_SOFT_MIB("txq" __stringअगरy(num) "_packets", \
			tx_rings[num].packets), \
	STAT_GENET_SOFT_MIB("txq" __stringअगरy(num) "_bytes", \
			tx_rings[num].bytes), \
	STAT_GENET_SOFT_MIB("rxq" __stringअगरy(num) "_bytes", \
			rx_rings[num].bytes),	 \
	STAT_GENET_SOFT_MIB("rxq" __stringअगरy(num) "_packets", \
			rx_rings[num].packets), \
	STAT_GENET_SOFT_MIB("rxq" __stringअगरy(num) "_errors", \
			rx_rings[num].errors), \
	STAT_GENET_SOFT_MIB("rxq" __stringअगरy(num) "_dropped", \
			rx_rings[num].dropped)

/* There is a 0xC gap between the end of RX and beginning of TX stats and then
 * between the end of TX stats and the beginning of the RX RUNT
 */
#घोषणा BCMGENET_STAT_OFFSET	0xc

/* Hardware counters must be kept in sync because the order/offset
 * is important here (order in काष्ठाure declaration = order in hardware)
 */
अटल स्थिर काष्ठा bcmgenet_stats bcmgenet_gstrings_stats[] = अणु
	/* general stats */
	STAT_NETDEV(rx_packets),
	STAT_NETDEV(tx_packets),
	STAT_NETDEV(rx_bytes),
	STAT_NETDEV(tx_bytes),
	STAT_NETDEV(rx_errors),
	STAT_NETDEV(tx_errors),
	STAT_NETDEV(rx_dropped),
	STAT_NETDEV(tx_dropped),
	STAT_NETDEV(multicast),
	/* UniMAC RSV counters */
	STAT_GENET_MIB_RX("rx_64_octets", mib.rx.pkt_cnt.cnt_64),
	STAT_GENET_MIB_RX("rx_65_127_oct", mib.rx.pkt_cnt.cnt_127),
	STAT_GENET_MIB_RX("rx_128_255_oct", mib.rx.pkt_cnt.cnt_255),
	STAT_GENET_MIB_RX("rx_256_511_oct", mib.rx.pkt_cnt.cnt_511),
	STAT_GENET_MIB_RX("rx_512_1023_oct", mib.rx.pkt_cnt.cnt_1023),
	STAT_GENET_MIB_RX("rx_1024_1518_oct", mib.rx.pkt_cnt.cnt_1518),
	STAT_GENET_MIB_RX("rx_vlan_1519_1522_oct", mib.rx.pkt_cnt.cnt_mgv),
	STAT_GENET_MIB_RX("rx_1522_2047_oct", mib.rx.pkt_cnt.cnt_2047),
	STAT_GENET_MIB_RX("rx_2048_4095_oct", mib.rx.pkt_cnt.cnt_4095),
	STAT_GENET_MIB_RX("rx_4096_9216_oct", mib.rx.pkt_cnt.cnt_9216),
	STAT_GENET_MIB_RX("rx_pkts", mib.rx.pkt),
	STAT_GENET_MIB_RX("rx_bytes", mib.rx.bytes),
	STAT_GENET_MIB_RX("rx_multicast", mib.rx.mca),
	STAT_GENET_MIB_RX("rx_broadcast", mib.rx.bca),
	STAT_GENET_MIB_RX("rx_fcs", mib.rx.fcs),
	STAT_GENET_MIB_RX("rx_control", mib.rx.cf),
	STAT_GENET_MIB_RX("rx_pause", mib.rx.pf),
	STAT_GENET_MIB_RX("rx_unknown", mib.rx.uo),
	STAT_GENET_MIB_RX("rx_align", mib.rx.aln),
	STAT_GENET_MIB_RX("rx_outrange", mib.rx.flr),
	STAT_GENET_MIB_RX("rx_code", mib.rx.cde),
	STAT_GENET_MIB_RX("rx_carrier", mib.rx.fcr),
	STAT_GENET_MIB_RX("rx_oversize", mib.rx.ovr),
	STAT_GENET_MIB_RX("rx_jabber", mib.rx.jbr),
	STAT_GENET_MIB_RX("rx_mtu_err", mib.rx.mtue),
	STAT_GENET_MIB_RX("rx_good_pkts", mib.rx.pok),
	STAT_GENET_MIB_RX("rx_unicast", mib.rx.uc),
	STAT_GENET_MIB_RX("rx_ppp", mib.rx.ppp),
	STAT_GENET_MIB_RX("rx_crc", mib.rx.rcrc),
	/* UniMAC TSV counters */
	STAT_GENET_MIB_TX("tx_64_octets", mib.tx.pkt_cnt.cnt_64),
	STAT_GENET_MIB_TX("tx_65_127_oct", mib.tx.pkt_cnt.cnt_127),
	STAT_GENET_MIB_TX("tx_128_255_oct", mib.tx.pkt_cnt.cnt_255),
	STAT_GENET_MIB_TX("tx_256_511_oct", mib.tx.pkt_cnt.cnt_511),
	STAT_GENET_MIB_TX("tx_512_1023_oct", mib.tx.pkt_cnt.cnt_1023),
	STAT_GENET_MIB_TX("tx_1024_1518_oct", mib.tx.pkt_cnt.cnt_1518),
	STAT_GENET_MIB_TX("tx_vlan_1519_1522_oct", mib.tx.pkt_cnt.cnt_mgv),
	STAT_GENET_MIB_TX("tx_1522_2047_oct", mib.tx.pkt_cnt.cnt_2047),
	STAT_GENET_MIB_TX("tx_2048_4095_oct", mib.tx.pkt_cnt.cnt_4095),
	STAT_GENET_MIB_TX("tx_4096_9216_oct", mib.tx.pkt_cnt.cnt_9216),
	STAT_GENET_MIB_TX("tx_pkts", mib.tx.pkts),
	STAT_GENET_MIB_TX("tx_multicast", mib.tx.mca),
	STAT_GENET_MIB_TX("tx_broadcast", mib.tx.bca),
	STAT_GENET_MIB_TX("tx_pause", mib.tx.pf),
	STAT_GENET_MIB_TX("tx_control", mib.tx.cf),
	STAT_GENET_MIB_TX("tx_fcs_err", mib.tx.fcs),
	STAT_GENET_MIB_TX("tx_oversize", mib.tx.ovr),
	STAT_GENET_MIB_TX("tx_defer", mib.tx.drf),
	STAT_GENET_MIB_TX("tx_excess_defer", mib.tx.edf),
	STAT_GENET_MIB_TX("tx_single_col", mib.tx.scl),
	STAT_GENET_MIB_TX("tx_multi_col", mib.tx.mcl),
	STAT_GENET_MIB_TX("tx_late_col", mib.tx.lcl),
	STAT_GENET_MIB_TX("tx_excess_col", mib.tx.ecl),
	STAT_GENET_MIB_TX("tx_frags", mib.tx.frg),
	STAT_GENET_MIB_TX("tx_total_col", mib.tx.ncl),
	STAT_GENET_MIB_TX("tx_jabber", mib.tx.jbr),
	STAT_GENET_MIB_TX("tx_bytes", mib.tx.bytes),
	STAT_GENET_MIB_TX("tx_good_pkts", mib.tx.pok),
	STAT_GENET_MIB_TX("tx_unicast", mib.tx.uc),
	/* UniMAC RUNT counters */
	STAT_GENET_RUNT("rx_runt_pkts", mib.rx_runt_cnt),
	STAT_GENET_RUNT("rx_runt_valid_fcs", mib.rx_runt_fcs),
	STAT_GENET_RUNT("rx_runt_inval_fcs_align", mib.rx_runt_fcs_align),
	STAT_GENET_RUNT("rx_runt_bytes", mib.rx_runt_bytes),
	/* Misc UniMAC counters */
	STAT_GENET_MISC("rbuf_ovflow_cnt", mib.rbuf_ovflow_cnt,
			UMAC_RBUF_OVFL_CNT_V1),
	STAT_GENET_MISC("rbuf_err_cnt", mib.rbuf_err_cnt,
			UMAC_RBUF_ERR_CNT_V1),
	STAT_GENET_MISC("mdf_err_cnt", mib.mdf_err_cnt, UMAC_MDF_ERR_CNT),
	STAT_GENET_SOFT_MIB("alloc_rx_buff_failed", mib.alloc_rx_buff_failed),
	STAT_GENET_SOFT_MIB("rx_dma_failed", mib.rx_dma_failed),
	STAT_GENET_SOFT_MIB("tx_dma_failed", mib.tx_dma_failed),
	STAT_GENET_SOFT_MIB("tx_realloc_tsb", mib.tx_पुनः_स्मृति_tsb),
	STAT_GENET_SOFT_MIB("tx_realloc_tsb_failed",
			    mib.tx_पुनः_स्मृति_tsb_failed),
	/* Per TX queues */
	STAT_GENET_Q(0),
	STAT_GENET_Q(1),
	STAT_GENET_Q(2),
	STAT_GENET_Q(3),
	STAT_GENET_Q(16),
पूर्ण;

#घोषणा BCMGENET_STATS_LEN	ARRAY_SIZE(bcmgenet_gstrings_stats)

अटल व्योम bcmgenet_get_drvinfo(काष्ठा net_device *dev,
				 काष्ठा ethtool_drvinfo *info)
अणु
	strlcpy(info->driver, "bcmgenet", माप(info->driver));
पूर्ण

अटल पूर्णांक bcmgenet_get_sset_count(काष्ठा net_device *dev, पूर्णांक string_set)
अणु
	चयन (string_set) अणु
	हाल ETH_SS_STATS:
		वापस BCMGENET_STATS_LEN;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल व्योम bcmgenet_get_strings(काष्ठा net_device *dev, u32 stringset,
				 u8 *data)
अणु
	पूर्णांक i;

	चयन (stringset) अणु
	हाल ETH_SS_STATS:
		क्रम (i = 0; i < BCMGENET_STATS_LEN; i++) अणु
			स_नकल(data + i * ETH_GSTRING_LEN,
			       bcmgenet_gstrings_stats[i].stat_string,
			       ETH_GSTRING_LEN);
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

अटल u32 bcmgenet_update_stat_misc(काष्ठा bcmgenet_priv *priv, u16 offset)
अणु
	u16 new_offset;
	u32 val;

	चयन (offset) अणु
	हाल UMAC_RBUF_OVFL_CNT_V1:
		अगर (GENET_IS_V2(priv))
			new_offset = RBUF_OVFL_CNT_V2;
		अन्यथा
			new_offset = RBUF_OVFL_CNT_V3PLUS;

		val = bcmgenet_rbuf_पढ़ोl(priv,	new_offset);
		/* clear अगर overflowed */
		अगर (val == ~0)
			bcmgenet_rbuf_ग_लिखोl(priv, 0, new_offset);
		अवरोध;
	हाल UMAC_RBUF_ERR_CNT_V1:
		अगर (GENET_IS_V2(priv))
			new_offset = RBUF_ERR_CNT_V2;
		अन्यथा
			new_offset = RBUF_ERR_CNT_V3PLUS;

		val = bcmgenet_rbuf_पढ़ोl(priv,	new_offset);
		/* clear अगर overflowed */
		अगर (val == ~0)
			bcmgenet_rbuf_ग_लिखोl(priv, 0, new_offset);
		अवरोध;
	शेष:
		val = bcmgenet_umac_पढ़ोl(priv, offset);
		/* clear अगर overflowed */
		अगर (val == ~0)
			bcmgenet_umac_ग_लिखोl(priv, 0, offset);
		अवरोध;
	पूर्ण

	वापस val;
पूर्ण

अटल व्योम bcmgenet_update_mib_counters(काष्ठा bcmgenet_priv *priv)
अणु
	पूर्णांक i, j = 0;

	क्रम (i = 0; i < BCMGENET_STATS_LEN; i++) अणु
		स्थिर काष्ठा bcmgenet_stats *s;
		u8 offset = 0;
		u32 val = 0;
		अक्षर *p;

		s = &bcmgenet_gstrings_stats[i];
		चयन (s->type) अणु
		हाल BCMGENET_STAT_NETDEV:
		हाल BCMGENET_STAT_SOFT:
			जारी;
		हाल BCMGENET_STAT_RUNT:
			offset += BCMGENET_STAT_OFFSET;
			fallthrough;
		हाल BCMGENET_STAT_MIB_TX:
			offset += BCMGENET_STAT_OFFSET;
			fallthrough;
		हाल BCMGENET_STAT_MIB_RX:
			val = bcmgenet_umac_पढ़ोl(priv,
						  UMAC_MIB_START + j + offset);
			offset = 0;	/* Reset Offset */
			अवरोध;
		हाल BCMGENET_STAT_MISC:
			अगर (GENET_IS_V1(priv)) अणु
				val = bcmgenet_umac_पढ़ोl(priv, s->reg_offset);
				/* clear अगर overflowed */
				अगर (val == ~0)
					bcmgenet_umac_ग_लिखोl(priv, 0,
							     s->reg_offset);
			पूर्ण अन्यथा अणु
				val = bcmgenet_update_stat_misc(priv,
								s->reg_offset);
			पूर्ण
			अवरोध;
		पूर्ण

		j += s->stat_माप;
		p = (अक्षर *)priv + s->stat_offset;
		*(u32 *)p = val;
	पूर्ण
पूर्ण

अटल व्योम bcmgenet_get_ethtool_stats(काष्ठा net_device *dev,
				       काष्ठा ethtool_stats *stats,
				       u64 *data)
अणु
	काष्ठा bcmgenet_priv *priv = netdev_priv(dev);
	पूर्णांक i;

	अगर (netअगर_running(dev))
		bcmgenet_update_mib_counters(priv);

	dev->netdev_ops->nकरो_get_stats(dev);

	क्रम (i = 0; i < BCMGENET_STATS_LEN; i++) अणु
		स्थिर काष्ठा bcmgenet_stats *s;
		अक्षर *p;

		s = &bcmgenet_gstrings_stats[i];
		अगर (s->type == BCMGENET_STAT_NETDEV)
			p = (अक्षर *)&dev->stats;
		अन्यथा
			p = (अक्षर *)priv;
		p += s->stat_offset;
		अगर (माप(अचिन्हित दीर्घ) != माप(u32) &&
		    s->stat_माप == माप(अचिन्हित दीर्घ))
			data[i] = *(अचिन्हित दीर्घ *)p;
		अन्यथा
			data[i] = *(u32 *)p;
	पूर्ण
पूर्ण

अटल व्योम bcmgenet_eee_enable_set(काष्ठा net_device *dev, bool enable)
अणु
	काष्ठा bcmgenet_priv *priv = netdev_priv(dev);
	u32 off = priv->hw_params->tbuf_offset + TBUF_ENERGY_CTRL;
	u32 reg;

	अगर (enable && !priv->clk_eee_enabled) अणु
		clk_prepare_enable(priv->clk_eee);
		priv->clk_eee_enabled = true;
	पूर्ण

	reg = bcmgenet_umac_पढ़ोl(priv, UMAC_EEE_CTRL);
	अगर (enable)
		reg |= EEE_EN;
	अन्यथा
		reg &= ~EEE_EN;
	bcmgenet_umac_ग_लिखोl(priv, reg, UMAC_EEE_CTRL);

	/* Enable EEE and चयन to a 27Mhz घड़ी स्वतःmatically */
	reg = bcmgenet_पढ़ोl(priv->base + off);
	अगर (enable)
		reg |= TBUF_EEE_EN | TBUF_PM_EN;
	अन्यथा
		reg &= ~(TBUF_EEE_EN | TBUF_PM_EN);
	bcmgenet_ग_लिखोl(reg, priv->base + off);

	/* Do the same क्रम thing क्रम RBUF */
	reg = bcmgenet_rbuf_पढ़ोl(priv, RBUF_ENERGY_CTRL);
	अगर (enable)
		reg |= RBUF_EEE_EN | RBUF_PM_EN;
	अन्यथा
		reg &= ~(RBUF_EEE_EN | RBUF_PM_EN);
	bcmgenet_rbuf_ग_लिखोl(priv, reg, RBUF_ENERGY_CTRL);

	अगर (!enable && priv->clk_eee_enabled) अणु
		clk_disable_unprepare(priv->clk_eee);
		priv->clk_eee_enabled = false;
	पूर्ण

	priv->eee.eee_enabled = enable;
	priv->eee.eee_active = enable;
पूर्ण

अटल पूर्णांक bcmgenet_get_eee(काष्ठा net_device *dev, काष्ठा ethtool_eee *e)
अणु
	काष्ठा bcmgenet_priv *priv = netdev_priv(dev);
	काष्ठा ethtool_eee *p = &priv->eee;

	अगर (GENET_IS_V1(priv))
		वापस -EOPNOTSUPP;

	अगर (!dev->phydev)
		वापस -ENODEV;

	e->eee_enabled = p->eee_enabled;
	e->eee_active = p->eee_active;
	e->tx_lpi_समयr = bcmgenet_umac_पढ़ोl(priv, UMAC_EEE_LPI_TIMER);

	वापस phy_ethtool_get_eee(dev->phydev, e);
पूर्ण

अटल पूर्णांक bcmgenet_set_eee(काष्ठा net_device *dev, काष्ठा ethtool_eee *e)
अणु
	काष्ठा bcmgenet_priv *priv = netdev_priv(dev);
	काष्ठा ethtool_eee *p = &priv->eee;
	पूर्णांक ret = 0;

	अगर (GENET_IS_V1(priv))
		वापस -EOPNOTSUPP;

	अगर (!dev->phydev)
		वापस -ENODEV;

	p->eee_enabled = e->eee_enabled;

	अगर (!p->eee_enabled) अणु
		bcmgenet_eee_enable_set(dev, false);
	पूर्ण अन्यथा अणु
		ret = phy_init_eee(dev->phydev, 0);
		अगर (ret) अणु
			netअगर_err(priv, hw, dev, "EEE initialization failed\n");
			वापस ret;
		पूर्ण

		bcmgenet_umac_ग_लिखोl(priv, e->tx_lpi_समयr, UMAC_EEE_LPI_TIMER);
		bcmgenet_eee_enable_set(dev, true);
	पूर्ण

	वापस phy_ethtool_set_eee(dev->phydev, e);
पूर्ण

अटल पूर्णांक bcmgenet_validate_flow(काष्ठा net_device *dev,
				  काष्ठा ethtool_rxnfc *cmd)
अणु
	काष्ठा ethtool_usrip4_spec *l4_mask;
	काष्ठा ethhdr *eth_mask;

	अगर (cmd->fs.location >= MAX_NUM_OF_FS_RULES) अणु
		netdev_err(dev, "rxnfc: Invalid location (%d)\n",
			   cmd->fs.location);
		वापस -EINVAL;
	पूर्ण

	चयन (cmd->fs.flow_type & ~(FLOW_EXT | FLOW_MAC_EXT)) अणु
	हाल IP_USER_FLOW:
		l4_mask = &cmd->fs.m_u.usr_ip4_spec;
		/* करोn't allow mask which isn't valid */
		अगर (VALIDATE_MASK(l4_mask->ip4src) ||
		    VALIDATE_MASK(l4_mask->ip4dst) ||
		    VALIDATE_MASK(l4_mask->l4_4_bytes) ||
		    VALIDATE_MASK(l4_mask->proto) ||
		    VALIDATE_MASK(l4_mask->ip_ver) ||
		    VALIDATE_MASK(l4_mask->tos)) अणु
			netdev_err(dev, "rxnfc: Unsupported mask\n");
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल ETHER_FLOW:
		eth_mask = &cmd->fs.m_u.ether_spec;
		/* करोn't allow mask which isn't valid */
		अगर (VALIDATE_MASK(eth_mask->h_dest) ||
		    VALIDATE_MASK(eth_mask->h_source) ||
		    VALIDATE_MASK(eth_mask->h_proto)) अणु
			netdev_err(dev, "rxnfc: Unsupported mask\n");
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		netdev_err(dev, "rxnfc: Unsupported flow type (0x%x)\n",
			   cmd->fs.flow_type);
		वापस -EINVAL;
	पूर्ण

	अगर ((cmd->fs.flow_type & FLOW_EXT)) अणु
		/* करोn't allow mask which isn't valid */
		अगर (VALIDATE_MASK(cmd->fs.m_ext.vlan_etype) ||
		    VALIDATE_MASK(cmd->fs.m_ext.vlan_tci)) अणु
			netdev_err(dev, "rxnfc: Unsupported mask\n");
			वापस -EINVAL;
		पूर्ण
		अगर (cmd->fs.m_ext.data[0] || cmd->fs.m_ext.data[1]) अणु
			netdev_err(dev, "rxnfc: user-def not supported\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर ((cmd->fs.flow_type & FLOW_MAC_EXT)) अणु
		/* करोn't allow mask which isn't valid */
		अगर (VALIDATE_MASK(cmd->fs.m_ext.h_dest)) अणु
			netdev_err(dev, "rxnfc: Unsupported mask\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bcmgenet_insert_flow(काष्ठा net_device *dev,
				काष्ठा ethtool_rxnfc *cmd)
अणु
	काष्ठा bcmgenet_priv *priv = netdev_priv(dev);
	काष्ठा bcmgenet_rxnfc_rule *loc_rule;
	पूर्णांक err;

	अगर (priv->hw_params->hfb_filter_size < 128) अणु
		netdev_err(dev, "rxnfc: Not supported by this device\n");
		वापस -EINVAL;
	पूर्ण

	अगर (cmd->fs.ring_cookie > priv->hw_params->rx_queues &&
	    cmd->fs.ring_cookie != RX_CLS_FLOW_WAKE) अणु
		netdev_err(dev, "rxnfc: Unsupported action (%llu)\n",
			   cmd->fs.ring_cookie);
		वापस -EINVAL;
	पूर्ण

	err = bcmgenet_validate_flow(dev, cmd);
	अगर (err)
		वापस err;

	loc_rule = &priv->rxnfc_rules[cmd->fs.location];
	अगर (loc_rule->state == BCMGENET_RXNFC_STATE_ENABLED)
		bcmgenet_hfb_disable_filter(priv, cmd->fs.location);
	अगर (loc_rule->state != BCMGENET_RXNFC_STATE_UNUSED) अणु
		list_del(&loc_rule->list);
		bcmgenet_hfb_clear_filter(priv, cmd->fs.location);
	पूर्ण
	loc_rule->state = BCMGENET_RXNFC_STATE_UNUSED;
	स_नकल(&loc_rule->fs, &cmd->fs,
	       माप(काष्ठा ethtool_rx_flow_spec));

	bcmgenet_hfb_create_rxnfc_filter(priv, loc_rule);

	list_add_tail(&loc_rule->list, &priv->rxnfc_list);

	वापस 0;
पूर्ण

अटल पूर्णांक bcmgenet_delete_flow(काष्ठा net_device *dev,
				काष्ठा ethtool_rxnfc *cmd)
अणु
	काष्ठा bcmgenet_priv *priv = netdev_priv(dev);
	काष्ठा bcmgenet_rxnfc_rule *rule;
	पूर्णांक err = 0;

	अगर (cmd->fs.location >= MAX_NUM_OF_FS_RULES)
		वापस -EINVAL;

	rule = &priv->rxnfc_rules[cmd->fs.location];
	अगर (rule->state == BCMGENET_RXNFC_STATE_UNUSED) अणु
		err =  -ENOENT;
		जाओ out;
	पूर्ण

	अगर (rule->state == BCMGENET_RXNFC_STATE_ENABLED)
		bcmgenet_hfb_disable_filter(priv, cmd->fs.location);
	अगर (rule->state != BCMGENET_RXNFC_STATE_UNUSED) अणु
		list_del(&rule->list);
		bcmgenet_hfb_clear_filter(priv, cmd->fs.location);
	पूर्ण
	rule->state = BCMGENET_RXNFC_STATE_UNUSED;
	स_रखो(&rule->fs, 0, माप(काष्ठा ethtool_rx_flow_spec));

out:
	वापस err;
पूर्ण

अटल पूर्णांक bcmgenet_set_rxnfc(काष्ठा net_device *dev, काष्ठा ethtool_rxnfc *cmd)
अणु
	काष्ठा bcmgenet_priv *priv = netdev_priv(dev);
	पूर्णांक err = 0;

	चयन (cmd->cmd) अणु
	हाल ETHTOOL_SRXCLSRLINS:
		err = bcmgenet_insert_flow(dev, cmd);
		अवरोध;
	हाल ETHTOOL_SRXCLSRLDEL:
		err = bcmgenet_delete_flow(dev, cmd);
		अवरोध;
	शेष:
		netdev_warn(priv->dev, "Unsupported ethtool command. (%d)\n",
			    cmd->cmd);
		वापस -EINVAL;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक bcmgenet_get_flow(काष्ठा net_device *dev, काष्ठा ethtool_rxnfc *cmd,
			     पूर्णांक loc)
अणु
	काष्ठा bcmgenet_priv *priv = netdev_priv(dev);
	काष्ठा bcmgenet_rxnfc_rule *rule;
	पूर्णांक err = 0;

	अगर (loc < 0 || loc >= MAX_NUM_OF_FS_RULES)
		वापस -EINVAL;

	rule = &priv->rxnfc_rules[loc];
	अगर (rule->state == BCMGENET_RXNFC_STATE_UNUSED)
		err = -ENOENT;
	अन्यथा
		स_नकल(&cmd->fs, &rule->fs,
		       माप(काष्ठा ethtool_rx_flow_spec));

	वापस err;
पूर्ण

अटल पूर्णांक bcmgenet_get_num_flows(काष्ठा bcmgenet_priv *priv)
अणु
	काष्ठा list_head *pos;
	पूर्णांक res = 0;

	list_क्रम_each(pos, &priv->rxnfc_list)
		res++;

	वापस res;
पूर्ण

अटल पूर्णांक bcmgenet_get_rxnfc(काष्ठा net_device *dev, काष्ठा ethtool_rxnfc *cmd,
			      u32 *rule_locs)
अणु
	काष्ठा bcmgenet_priv *priv = netdev_priv(dev);
	काष्ठा bcmgenet_rxnfc_rule *rule;
	पूर्णांक err = 0;
	पूर्णांक i = 0;

	चयन (cmd->cmd) अणु
	हाल ETHTOOL_GRXRINGS:
		cmd->data = priv->hw_params->rx_queues ?: 1;
		अवरोध;
	हाल ETHTOOL_GRXCLSRLCNT:
		cmd->rule_cnt = bcmgenet_get_num_flows(priv);
		cmd->data = MAX_NUM_OF_FS_RULES;
		अवरोध;
	हाल ETHTOOL_GRXCLSRULE:
		err = bcmgenet_get_flow(dev, cmd, cmd->fs.location);
		अवरोध;
	हाल ETHTOOL_GRXCLSRLALL:
		list_क्रम_each_entry(rule, &priv->rxnfc_list, list)
			अगर (i < cmd->rule_cnt)
				rule_locs[i++] = rule->fs.location;
		cmd->rule_cnt = i;
		cmd->data = MAX_NUM_OF_FS_RULES;
		अवरोध;
	शेष:
		err = -EOPNOTSUPP;
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

/* standard ethtool support functions. */
अटल स्थिर काष्ठा ethtool_ops bcmgenet_ethtool_ops = अणु
	.supported_coalesce_params = ETHTOOL_COALESCE_RX_USECS |
				     ETHTOOL_COALESCE_MAX_FRAMES |
				     ETHTOOL_COALESCE_USE_ADAPTIVE_RX,
	.begin			= bcmgenet_begin,
	.complete		= bcmgenet_complete,
	.get_strings		= bcmgenet_get_strings,
	.get_sset_count		= bcmgenet_get_sset_count,
	.get_ethtool_stats	= bcmgenet_get_ethtool_stats,
	.get_drvinfo		= bcmgenet_get_drvinfo,
	.get_link		= ethtool_op_get_link,
	.get_msglevel		= bcmgenet_get_msglevel,
	.set_msglevel		= bcmgenet_set_msglevel,
	.get_wol		= bcmgenet_get_wol,
	.set_wol		= bcmgenet_set_wol,
	.get_eee		= bcmgenet_get_eee,
	.set_eee		= bcmgenet_set_eee,
	.nway_reset		= phy_ethtool_nway_reset,
	.get_coalesce		= bcmgenet_get_coalesce,
	.set_coalesce		= bcmgenet_set_coalesce,
	.get_link_ksettings	= bcmgenet_get_link_ksettings,
	.set_link_ksettings	= bcmgenet_set_link_ksettings,
	.get_ts_info		= ethtool_op_get_ts_info,
	.get_rxnfc		= bcmgenet_get_rxnfc,
	.set_rxnfc		= bcmgenet_set_rxnfc,
पूर्ण;

/* Power करोwn the unimac, based on mode. */
अटल पूर्णांक bcmgenet_घातer_करोwn(काष्ठा bcmgenet_priv *priv,
				क्रमागत bcmgenet_घातer_mode mode)
अणु
	पूर्णांक ret = 0;
	u32 reg;

	चयन (mode) अणु
	हाल GENET_POWER_CABLE_SENSE:
		phy_detach(priv->dev->phydev);
		अवरोध;

	हाल GENET_POWER_WOL_MAGIC:
		ret = bcmgenet_wol_घातer_करोwn_cfg(priv, mode);
		अवरोध;

	हाल GENET_POWER_PASSIVE:
		/* Power करोwn LED */
		अगर (priv->hw_params->flags & GENET_HAS_EXT) अणु
			reg = bcmgenet_ext_पढ़ोl(priv, EXT_EXT_PWR_MGMT);
			अगर (GENET_IS_V5(priv))
				reg |= EXT_PWR_DOWN_PHY_EN |
				       EXT_PWR_DOWN_PHY_RD |
				       EXT_PWR_DOWN_PHY_SD |
				       EXT_PWR_DOWN_PHY_RX |
				       EXT_PWR_DOWN_PHY_TX |
				       EXT_IDDQ_GLBL_PWR;
			अन्यथा
				reg |= EXT_PWR_DOWN_PHY;

			reg |= (EXT_PWR_DOWN_DLL | EXT_PWR_DOWN_BIAS);
			bcmgenet_ext_ग_लिखोl(priv, reg, EXT_EXT_PWR_MGMT);

			bcmgenet_phy_घातer_set(priv->dev, false);
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम bcmgenet_घातer_up(काष्ठा bcmgenet_priv *priv,
			      क्रमागत bcmgenet_घातer_mode mode)
अणु
	u32 reg;

	अगर (!(priv->hw_params->flags & GENET_HAS_EXT))
		वापस;

	reg = bcmgenet_ext_पढ़ोl(priv, EXT_EXT_PWR_MGMT);

	चयन (mode) अणु
	हाल GENET_POWER_PASSIVE:
		reg &= ~(EXT_PWR_DOWN_DLL | EXT_PWR_DOWN_BIAS);
		अगर (GENET_IS_V5(priv)) अणु
			reg &= ~(EXT_PWR_DOWN_PHY_EN |
				 EXT_PWR_DOWN_PHY_RD |
				 EXT_PWR_DOWN_PHY_SD |
				 EXT_PWR_DOWN_PHY_RX |
				 EXT_PWR_DOWN_PHY_TX |
				 EXT_IDDQ_GLBL_PWR);
			reg |=   EXT_PHY_RESET;
			bcmgenet_ext_ग_लिखोl(priv, reg, EXT_EXT_PWR_MGMT);
			mdelay(1);

			reg &=  ~EXT_PHY_RESET;
		पूर्ण अन्यथा अणु
			reg &= ~EXT_PWR_DOWN_PHY;
			reg |= EXT_PWR_DN_EN_LD;
		पूर्ण
		bcmgenet_ext_ग_लिखोl(priv, reg, EXT_EXT_PWR_MGMT);
		bcmgenet_phy_घातer_set(priv->dev, true);
		अवरोध;

	हाल GENET_POWER_CABLE_SENSE:
		/* enable APD */
		अगर (!GENET_IS_V5(priv)) अणु
			reg |= EXT_PWR_DN_EN_LD;
			bcmgenet_ext_ग_लिखोl(priv, reg, EXT_EXT_PWR_MGMT);
		पूर्ण
		अवरोध;
	हाल GENET_POWER_WOL_MAGIC:
		bcmgenet_wol_घातer_up_cfg(priv, mode);
		वापस;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल काष्ठा enet_cb *bcmgenet_get_txcb(काष्ठा bcmgenet_priv *priv,
					 काष्ठा bcmgenet_tx_ring *ring)
अणु
	काष्ठा enet_cb *tx_cb_ptr;

	tx_cb_ptr = ring->cbs;
	tx_cb_ptr += ring->ग_लिखो_ptr - ring->cb_ptr;

	/* Advancing local ग_लिखो poपूर्णांकer */
	अगर (ring->ग_लिखो_ptr == ring->end_ptr)
		ring->ग_लिखो_ptr = ring->cb_ptr;
	अन्यथा
		ring->ग_लिखो_ptr++;

	वापस tx_cb_ptr;
पूर्ण

अटल काष्ठा enet_cb *bcmgenet_put_txcb(काष्ठा bcmgenet_priv *priv,
					 काष्ठा bcmgenet_tx_ring *ring)
अणु
	काष्ठा enet_cb *tx_cb_ptr;

	tx_cb_ptr = ring->cbs;
	tx_cb_ptr += ring->ग_लिखो_ptr - ring->cb_ptr;

	/* Rewinding local ग_लिखो poपूर्णांकer */
	अगर (ring->ग_लिखो_ptr == ring->cb_ptr)
		ring->ग_लिखो_ptr = ring->end_ptr;
	अन्यथा
		ring->ग_लिखो_ptr--;

	वापस tx_cb_ptr;
पूर्ण

अटल अंतरभूत व्योम bcmgenet_rx_ring16_पूर्णांक_disable(काष्ठा bcmgenet_rx_ring *ring)
अणु
	bcmgenet_पूर्णांकrl2_0_ग_लिखोl(ring->priv, UMAC_IRQ_RXDMA_DONE,
				 INTRL2_CPU_MASK_SET);
पूर्ण

अटल अंतरभूत व्योम bcmgenet_rx_ring16_पूर्णांक_enable(काष्ठा bcmgenet_rx_ring *ring)
अणु
	bcmgenet_पूर्णांकrl2_0_ग_लिखोl(ring->priv, UMAC_IRQ_RXDMA_DONE,
				 INTRL2_CPU_MASK_CLEAR);
पूर्ण

अटल अंतरभूत व्योम bcmgenet_rx_ring_पूर्णांक_disable(काष्ठा bcmgenet_rx_ring *ring)
अणु
	bcmgenet_पूर्णांकrl2_1_ग_लिखोl(ring->priv,
				 1 << (UMAC_IRQ1_RX_INTR_SHIFT + ring->index),
				 INTRL2_CPU_MASK_SET);
पूर्ण

अटल अंतरभूत व्योम bcmgenet_rx_ring_पूर्णांक_enable(काष्ठा bcmgenet_rx_ring *ring)
अणु
	bcmgenet_पूर्णांकrl2_1_ग_लिखोl(ring->priv,
				 1 << (UMAC_IRQ1_RX_INTR_SHIFT + ring->index),
				 INTRL2_CPU_MASK_CLEAR);
पूर्ण

अटल अंतरभूत व्योम bcmgenet_tx_ring16_पूर्णांक_disable(काष्ठा bcmgenet_tx_ring *ring)
अणु
	bcmgenet_पूर्णांकrl2_0_ग_लिखोl(ring->priv, UMAC_IRQ_TXDMA_DONE,
				 INTRL2_CPU_MASK_SET);
पूर्ण

अटल अंतरभूत व्योम bcmgenet_tx_ring16_पूर्णांक_enable(काष्ठा bcmgenet_tx_ring *ring)
अणु
	bcmgenet_पूर्णांकrl2_0_ग_लिखोl(ring->priv, UMAC_IRQ_TXDMA_DONE,
				 INTRL2_CPU_MASK_CLEAR);
पूर्ण

अटल अंतरभूत व्योम bcmgenet_tx_ring_पूर्णांक_enable(काष्ठा bcmgenet_tx_ring *ring)
अणु
	bcmgenet_पूर्णांकrl2_1_ग_लिखोl(ring->priv, 1 << ring->index,
				 INTRL2_CPU_MASK_CLEAR);
पूर्ण

अटल अंतरभूत व्योम bcmgenet_tx_ring_पूर्णांक_disable(काष्ठा bcmgenet_tx_ring *ring)
अणु
	bcmgenet_पूर्णांकrl2_1_ग_लिखोl(ring->priv, 1 << ring->index,
				 INTRL2_CPU_MASK_SET);
पूर्ण

/* Simple helper to मुक्त a transmit control block's resources
 * Returns an skb when the last transmit control block associated with the
 * skb is मुक्तd.  The skb should be मुक्तd by the caller अगर necessary.
 */
अटल काष्ठा sk_buff *bcmgenet_मुक्त_tx_cb(काष्ठा device *dev,
					   काष्ठा enet_cb *cb)
अणु
	काष्ठा sk_buff *skb;

	skb = cb->skb;

	अगर (skb) अणु
		cb->skb = शून्य;
		अगर (cb == GENET_CB(skb)->first_cb)
			dma_unmap_single(dev, dma_unmap_addr(cb, dma_addr),
					 dma_unmap_len(cb, dma_len),
					 DMA_TO_DEVICE);
		अन्यथा
			dma_unmap_page(dev, dma_unmap_addr(cb, dma_addr),
				       dma_unmap_len(cb, dma_len),
				       DMA_TO_DEVICE);
		dma_unmap_addr_set(cb, dma_addr, 0);

		अगर (cb == GENET_CB(skb)->last_cb)
			वापस skb;

	पूर्ण अन्यथा अगर (dma_unmap_addr(cb, dma_addr)) अणु
		dma_unmap_page(dev,
			       dma_unmap_addr(cb, dma_addr),
			       dma_unmap_len(cb, dma_len),
			       DMA_TO_DEVICE);
		dma_unmap_addr_set(cb, dma_addr, 0);
	पूर्ण

	वापस शून्य;
पूर्ण

/* Simple helper to मुक्त a receive control block's resources */
अटल काष्ठा sk_buff *bcmgenet_मुक्त_rx_cb(काष्ठा device *dev,
					   काष्ठा enet_cb *cb)
अणु
	काष्ठा sk_buff *skb;

	skb = cb->skb;
	cb->skb = शून्य;

	अगर (dma_unmap_addr(cb, dma_addr)) अणु
		dma_unmap_single(dev, dma_unmap_addr(cb, dma_addr),
				 dma_unmap_len(cb, dma_len), DMA_FROM_DEVICE);
		dma_unmap_addr_set(cb, dma_addr, 0);
	पूर्ण

	वापस skb;
पूर्ण

/* Unlocked version of the reclaim routine */
अटल अचिन्हित पूर्णांक __bcmgenet_tx_reclaim(काष्ठा net_device *dev,
					  काष्ठा bcmgenet_tx_ring *ring)
अणु
	काष्ठा bcmgenet_priv *priv = netdev_priv(dev);
	अचिन्हित पूर्णांक txbds_processed = 0;
	अचिन्हित पूर्णांक bytes_compl = 0;
	अचिन्हित पूर्णांक pkts_compl = 0;
	अचिन्हित पूर्णांक txbds_पढ़ोy;
	अचिन्हित पूर्णांक c_index;
	काष्ठा sk_buff *skb;

	/* Clear status beक्रमe servicing to reduce spurious पूर्णांकerrupts */
	अगर (ring->index == DESC_INDEX)
		bcmgenet_पूर्णांकrl2_0_ग_लिखोl(priv, UMAC_IRQ_TXDMA_DONE,
					 INTRL2_CPU_CLEAR);
	अन्यथा
		bcmgenet_पूर्णांकrl2_1_ग_लिखोl(priv, (1 << ring->index),
					 INTRL2_CPU_CLEAR);

	/* Compute how many buffers are transmitted since last xmit call */
	c_index = bcmgenet_tdma_ring_पढ़ोl(priv, ring->index, TDMA_CONS_INDEX)
		& DMA_C_INDEX_MASK;
	txbds_पढ़ोy = (c_index - ring->c_index) & DMA_C_INDEX_MASK;

	netअगर_dbg(priv, tx_करोne, dev,
		  "%s ring=%d old_c_index=%u c_index=%u txbds_ready=%u\n",
		  __func__, ring->index, ring->c_index, c_index, txbds_पढ़ोy);

	/* Reclaim transmitted buffers */
	जबतक (txbds_processed < txbds_पढ़ोy) अणु
		skb = bcmgenet_मुक्त_tx_cb(&priv->pdev->dev,
					  &priv->tx_cbs[ring->clean_ptr]);
		अगर (skb) अणु
			pkts_compl++;
			bytes_compl += GENET_CB(skb)->bytes_sent;
			dev_consume_skb_any(skb);
		पूर्ण

		txbds_processed++;
		अगर (likely(ring->clean_ptr < ring->end_ptr))
			ring->clean_ptr++;
		अन्यथा
			ring->clean_ptr = ring->cb_ptr;
	पूर्ण

	ring->मुक्त_bds += txbds_processed;
	ring->c_index = c_index;

	ring->packets += pkts_compl;
	ring->bytes += bytes_compl;

	netdev_tx_completed_queue(netdev_get_tx_queue(dev, ring->queue),
				  pkts_compl, bytes_compl);

	वापस txbds_processed;
पूर्ण

अटल अचिन्हित पूर्णांक bcmgenet_tx_reclaim(काष्ठा net_device *dev,
				काष्ठा bcmgenet_tx_ring *ring)
अणु
	अचिन्हित पूर्णांक released;

	spin_lock_bh(&ring->lock);
	released = __bcmgenet_tx_reclaim(dev, ring);
	spin_unlock_bh(&ring->lock);

	वापस released;
पूर्ण

अटल पूर्णांक bcmgenet_tx_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा bcmgenet_tx_ring *ring =
		container_of(napi, काष्ठा bcmgenet_tx_ring, napi);
	अचिन्हित पूर्णांक work_करोne = 0;
	काष्ठा netdev_queue *txq;

	spin_lock(&ring->lock);
	work_करोne = __bcmgenet_tx_reclaim(ring->priv->dev, ring);
	अगर (ring->मुक्त_bds > (MAX_SKB_FRAGS + 1)) अणु
		txq = netdev_get_tx_queue(ring->priv->dev, ring->queue);
		netअगर_tx_wake_queue(txq);
	पूर्ण
	spin_unlock(&ring->lock);

	अगर (work_करोne == 0) अणु
		napi_complete(napi);
		ring->पूर्णांक_enable(ring);

		वापस 0;
	पूर्ण

	वापस budget;
पूर्ण

अटल व्योम bcmgenet_tx_reclaim_all(काष्ठा net_device *dev)
अणु
	काष्ठा bcmgenet_priv *priv = netdev_priv(dev);
	पूर्णांक i;

	अगर (netअगर_is_multiqueue(dev)) अणु
		क्रम (i = 0; i < priv->hw_params->tx_queues; i++)
			bcmgenet_tx_reclaim(dev, &priv->tx_rings[i]);
	पूर्ण

	bcmgenet_tx_reclaim(dev, &priv->tx_rings[DESC_INDEX]);
पूर्ण

/* Reallocate the SKB to put enough headroom in front of it and insert
 * the transmit checksum offsets in the descriptors
 */
अटल काष्ठा sk_buff *bcmgenet_add_tsb(काष्ठा net_device *dev,
					काष्ठा sk_buff *skb)
अणु
	काष्ठा bcmgenet_priv *priv = netdev_priv(dev);
	काष्ठा status_64 *status = शून्य;
	काष्ठा sk_buff *new_skb;
	u16 offset;
	u8 ip_proto;
	__be16 ip_ver;
	u32 tx_csum_info;

	अगर (unlikely(skb_headroom(skb) < माप(*status))) अणु
		/* If 64 byte status block enabled, must make sure skb has
		 * enough headroom क्रम us to insert 64B status block.
		 */
		new_skb = skb_पुनः_स्मृति_headroom(skb, माप(*status));
		अगर (!new_skb) अणु
			dev_kमुक्त_skb_any(skb);
			priv->mib.tx_पुनः_स्मृति_tsb_failed++;
			dev->stats.tx_dropped++;
			वापस शून्य;
		पूर्ण
		dev_consume_skb_any(skb);
		skb = new_skb;
		priv->mib.tx_पुनः_स्मृति_tsb++;
	पूर्ण

	skb_push(skb, माप(*status));
	status = (काष्ठा status_64 *)skb->data;

	अगर (skb->ip_summed  == CHECKSUM_PARTIAL) अणु
		ip_ver = skb->protocol;
		चयन (ip_ver) अणु
		हाल htons(ETH_P_IP):
			ip_proto = ip_hdr(skb)->protocol;
			अवरोध;
		हाल htons(ETH_P_IPV6):
			ip_proto = ipv6_hdr(skb)->nexthdr;
			अवरोध;
		शेष:
			/* करोn't use UDP flag */
			ip_proto = 0;
			अवरोध;
		पूर्ण

		offset = skb_checksum_start_offset(skb) - माप(*status);
		tx_csum_info = (offset << STATUS_TX_CSUM_START_SHIFT) |
				(offset + skb->csum_offset) |
				STATUS_TX_CSUM_LV;

		/* Set the special UDP flag क्रम UDP */
		अगर (ip_proto == IPPROTO_UDP)
			tx_csum_info |= STATUS_TX_CSUM_PROTO_UDP;

		status->tx_csum_info = tx_csum_info;
	पूर्ण

	वापस skb;
पूर्ण

अटल netdev_tx_t bcmgenet_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा bcmgenet_priv *priv = netdev_priv(dev);
	काष्ठा device *kdev = &priv->pdev->dev;
	काष्ठा bcmgenet_tx_ring *ring = शून्य;
	काष्ठा enet_cb *tx_cb_ptr;
	काष्ठा netdev_queue *txq;
	पूर्णांक nr_frags, index;
	dma_addr_t mapping;
	अचिन्हित पूर्णांक size;
	skb_frag_t *frag;
	u32 len_stat;
	पूर्णांक ret;
	पूर्णांक i;

	index = skb_get_queue_mapping(skb);
	/* Mapping strategy:
	 * queue_mapping = 0, unclassअगरied, packet xmited through ring16
	 * queue_mapping = 1, goes to ring 0. (highest priority queue
	 * queue_mapping = 2, goes to ring 1.
	 * queue_mapping = 3, goes to ring 2.
	 * queue_mapping = 4, goes to ring 3.
	 */
	अगर (index == 0)
		index = DESC_INDEX;
	अन्यथा
		index -= 1;

	ring = &priv->tx_rings[index];
	txq = netdev_get_tx_queue(dev, ring->queue);

	nr_frags = skb_shinfo(skb)->nr_frags;

	spin_lock(&ring->lock);
	अगर (ring->मुक्त_bds <= (nr_frags + 1)) अणु
		अगर (!netअगर_tx_queue_stopped(txq)) अणु
			netअगर_tx_stop_queue(txq);
			netdev_err(dev,
				   "%s: tx ring %d full when queue %d awake\n",
				   __func__, index, ring->queue);
		पूर्ण
		ret = NETDEV_TX_BUSY;
		जाओ out;
	पूर्ण

	/* Retain how many bytes will be sent on the wire, without TSB inserted
	 * by transmit checksum offload
	 */
	GENET_CB(skb)->bytes_sent = skb->len;

	/* add the Transmit Status Block */
	skb = bcmgenet_add_tsb(dev, skb);
	अगर (!skb) अणु
		ret = NETDEV_TX_OK;
		जाओ out;
	पूर्ण

	क्रम (i = 0; i <= nr_frags; i++) अणु
		tx_cb_ptr = bcmgenet_get_txcb(priv, ring);

		BUG_ON(!tx_cb_ptr);

		अगर (!i) अणु
			/* Transmit single SKB or head of fragment list */
			GENET_CB(skb)->first_cb = tx_cb_ptr;
			size = skb_headlen(skb);
			mapping = dma_map_single(kdev, skb->data, size,
						 DMA_TO_DEVICE);
		पूर्ण अन्यथा अणु
			/* xmit fragment */
			frag = &skb_shinfo(skb)->frags[i - 1];
			size = skb_frag_size(frag);
			mapping = skb_frag_dma_map(kdev, frag, 0, size,
						   DMA_TO_DEVICE);
		पूर्ण

		ret = dma_mapping_error(kdev, mapping);
		अगर (ret) अणु
			priv->mib.tx_dma_failed++;
			netअगर_err(priv, tx_err, dev, "Tx DMA map failed\n");
			ret = NETDEV_TX_OK;
			जाओ out_unmap_frags;
		पूर्ण
		dma_unmap_addr_set(tx_cb_ptr, dma_addr, mapping);
		dma_unmap_len_set(tx_cb_ptr, dma_len, size);

		tx_cb_ptr->skb = skb;

		len_stat = (size << DMA_BUFLENGTH_SHIFT) |
			   (priv->hw_params->qtag_mask << DMA_TX_QTAG_SHIFT);

		/* Note: अगर we ever change from DMA_TX_APPEND_CRC below we
		 * will need to restore software padding of "runt" packets
		 */
		अगर (!i) अणु
			len_stat |= DMA_TX_APPEND_CRC | DMA_SOP;
			अगर (skb->ip_summed == CHECKSUM_PARTIAL)
				len_stat |= DMA_TX_DO_CSUM;
		पूर्ण
		अगर (i == nr_frags)
			len_stat |= DMA_EOP;

		dmadesc_set(priv, tx_cb_ptr->bd_addr, mapping, len_stat);
	पूर्ण

	GENET_CB(skb)->last_cb = tx_cb_ptr;
	skb_tx_बारtamp(skb);

	/* Decrement total BD count and advance our ग_लिखो poपूर्णांकer */
	ring->मुक्त_bds -= nr_frags + 1;
	ring->prod_index += nr_frags + 1;
	ring->prod_index &= DMA_P_INDEX_MASK;

	netdev_tx_sent_queue(txq, GENET_CB(skb)->bytes_sent);

	अगर (ring->मुक्त_bds <= (MAX_SKB_FRAGS + 1))
		netअगर_tx_stop_queue(txq);

	अगर (!netdev_xmit_more() || netअगर_xmit_stopped(txq))
		/* Packets are पढ़ोy, update producer index */
		bcmgenet_tdma_ring_ग_लिखोl(priv, ring->index,
					  ring->prod_index, TDMA_PROD_INDEX);
out:
	spin_unlock(&ring->lock);

	वापस ret;

out_unmap_frags:
	/* Back up क्रम failed control block mapping */
	bcmgenet_put_txcb(priv, ring);

	/* Unmap successfully mapped control blocks */
	जबतक (i-- > 0) अणु
		tx_cb_ptr = bcmgenet_put_txcb(priv, ring);
		bcmgenet_मुक्त_tx_cb(kdev, tx_cb_ptr);
	पूर्ण

	dev_kमुक्त_skb(skb);
	जाओ out;
पूर्ण

अटल काष्ठा sk_buff *bcmgenet_rx_refill(काष्ठा bcmgenet_priv *priv,
					  काष्ठा enet_cb *cb)
अणु
	काष्ठा device *kdev = &priv->pdev->dev;
	काष्ठा sk_buff *skb;
	काष्ठा sk_buff *rx_skb;
	dma_addr_t mapping;

	/* Allocate a new Rx skb */
	skb = __netdev_alloc_skb(priv->dev, priv->rx_buf_len + SKB_ALIGNMENT,
				 GFP_ATOMIC | __GFP_NOWARN);
	अगर (!skb) अणु
		priv->mib.alloc_rx_buff_failed++;
		netअगर_err(priv, rx_err, priv->dev,
			  "%s: Rx skb allocation failed\n", __func__);
		वापस शून्य;
	पूर्ण

	/* DMA-map the new Rx skb */
	mapping = dma_map_single(kdev, skb->data, priv->rx_buf_len,
				 DMA_FROM_DEVICE);
	अगर (dma_mapping_error(kdev, mapping)) अणु
		priv->mib.rx_dma_failed++;
		dev_kमुक्त_skb_any(skb);
		netअगर_err(priv, rx_err, priv->dev,
			  "%s: Rx skb DMA mapping failed\n", __func__);
		वापस शून्य;
	पूर्ण

	/* Grab the current Rx skb from the ring and DMA-unmap it */
	rx_skb = bcmgenet_मुक्त_rx_cb(kdev, cb);

	/* Put the new Rx skb on the ring */
	cb->skb = skb;
	dma_unmap_addr_set(cb, dma_addr, mapping);
	dma_unmap_len_set(cb, dma_len, priv->rx_buf_len);
	dmadesc_set_addr(priv, cb->bd_addr, mapping);

	/* Return the current Rx skb to caller */
	वापस rx_skb;
पूर्ण

/* bcmgenet_desc_rx - descriptor based rx process.
 * this could be called from bottom half, or from NAPI polling method.
 */
अटल अचिन्हित पूर्णांक bcmgenet_desc_rx(काष्ठा bcmgenet_rx_ring *ring,
				     अचिन्हित पूर्णांक budget)
अणु
	काष्ठा bcmgenet_priv *priv = ring->priv;
	काष्ठा net_device *dev = priv->dev;
	काष्ठा enet_cb *cb;
	काष्ठा sk_buff *skb;
	u32 dma_length_status;
	अचिन्हित दीर्घ dma_flag;
	पूर्णांक len;
	अचिन्हित पूर्णांक rxpktprocessed = 0, rxpkttoprocess;
	अचिन्हित पूर्णांक bytes_processed = 0;
	अचिन्हित पूर्णांक p_index, mask;
	अचिन्हित पूर्णांक discards;

	/* Clear status beक्रमe servicing to reduce spurious पूर्णांकerrupts */
	अगर (ring->index == DESC_INDEX) अणु
		bcmgenet_पूर्णांकrl2_0_ग_लिखोl(priv, UMAC_IRQ_RXDMA_DONE,
					 INTRL2_CPU_CLEAR);
	पूर्ण अन्यथा अणु
		mask = 1 << (UMAC_IRQ1_RX_INTR_SHIFT + ring->index);
		bcmgenet_पूर्णांकrl2_1_ग_लिखोl(priv,
					 mask,
					 INTRL2_CPU_CLEAR);
	पूर्ण

	p_index = bcmgenet_rdma_ring_पढ़ोl(priv, ring->index, RDMA_PROD_INDEX);

	discards = (p_index >> DMA_P_INDEX_DISCARD_CNT_SHIFT) &
		   DMA_P_INDEX_DISCARD_CNT_MASK;
	अगर (discards > ring->old_discards) अणु
		discards = discards - ring->old_discards;
		ring->errors += discards;
		ring->old_discards += discards;

		/* Clear HW रेजिस्टर when we reach 75% of maximum 0xFFFF */
		अगर (ring->old_discards >= 0xC000) अणु
			ring->old_discards = 0;
			bcmgenet_rdma_ring_ग_लिखोl(priv, ring->index, 0,
						  RDMA_PROD_INDEX);
		पूर्ण
	पूर्ण

	p_index &= DMA_P_INDEX_MASK;
	rxpkttoprocess = (p_index - ring->c_index) & DMA_C_INDEX_MASK;

	netअगर_dbg(priv, rx_status, dev,
		  "RDMA: rxpkttoprocess=%d\n", rxpkttoprocess);

	जबतक ((rxpktprocessed < rxpkttoprocess) &&
	       (rxpktprocessed < budget)) अणु
		काष्ठा status_64 *status;
		__be16 rx_csum;

		cb = &priv->rx_cbs[ring->पढ़ो_ptr];
		skb = bcmgenet_rx_refill(priv, cb);

		अगर (unlikely(!skb)) अणु
			ring->dropped++;
			जाओ next;
		पूर्ण

		status = (काष्ठा status_64 *)skb->data;
		dma_length_status = status->length_status;
		अगर (dev->features & NETIF_F_RXCSUM) अणु
			rx_csum = (__क्रमce __be16)(status->rx_csum & 0xffff);
			skb->csum = (__क्रमce __wsum)ntohs(rx_csum);
			skb->ip_summed = CHECKSUM_COMPLETE;
		पूर्ण

		/* DMA flags and length are still valid no matter how
		 * we got the Receive Status Vector (64B RSB or रेजिस्टर)
		 */
		dma_flag = dma_length_status & 0xffff;
		len = dma_length_status >> DMA_BUFLENGTH_SHIFT;

		netअगर_dbg(priv, rx_status, dev,
			  "%s:p_ind=%d c_ind=%d read_ptr=%d len_stat=0x%08x\n",
			  __func__, p_index, ring->c_index,
			  ring->पढ़ो_ptr, dma_length_status);

		अगर (unlikely(!(dma_flag & DMA_EOP) || !(dma_flag & DMA_SOP))) अणु
			netअगर_err(priv, rx_status, dev,
				  "dropping fragmented packet!\n");
			ring->errors++;
			dev_kमुक्त_skb_any(skb);
			जाओ next;
		पूर्ण

		/* report errors */
		अगर (unlikely(dma_flag & (DMA_RX_CRC_ERROR |
						DMA_RX_OV |
						DMA_RX_NO |
						DMA_RX_LG |
						DMA_RX_RXER))) अणु
			netअगर_err(priv, rx_status, dev, "dma_flag=0x%x\n",
				  (अचिन्हित पूर्णांक)dma_flag);
			अगर (dma_flag & DMA_RX_CRC_ERROR)
				dev->stats.rx_crc_errors++;
			अगर (dma_flag & DMA_RX_OV)
				dev->stats.rx_over_errors++;
			अगर (dma_flag & DMA_RX_NO)
				dev->stats.rx_frame_errors++;
			अगर (dma_flag & DMA_RX_LG)
				dev->stats.rx_length_errors++;
			dev->stats.rx_errors++;
			dev_kमुक्त_skb_any(skb);
			जाओ next;
		पूर्ण /* error packet */

		skb_put(skb, len);

		/* हटाओ RSB and hardware 2bytes added क्रम IP alignment */
		skb_pull(skb, 66);
		len -= 66;

		अगर (priv->crc_fwd_en) अणु
			skb_trim(skb, len - ETH_FCS_LEN);
			len -= ETH_FCS_LEN;
		पूर्ण

		bytes_processed += len;

		/*Finish setting up the received SKB and send it to the kernel*/
		skb->protocol = eth_type_trans(skb, priv->dev);
		ring->packets++;
		ring->bytes += len;
		अगर (dma_flag & DMA_RX_MULT)
			dev->stats.multicast++;

		/* Notअगरy kernel */
		napi_gro_receive(&ring->napi, skb);
		netअगर_dbg(priv, rx_status, dev, "pushed up to kernel\n");

next:
		rxpktprocessed++;
		अगर (likely(ring->पढ़ो_ptr < ring->end_ptr))
			ring->पढ़ो_ptr++;
		अन्यथा
			ring->पढ़ो_ptr = ring->cb_ptr;

		ring->c_index = (ring->c_index + 1) & DMA_C_INDEX_MASK;
		bcmgenet_rdma_ring_ग_लिखोl(priv, ring->index, ring->c_index, RDMA_CONS_INDEX);
	पूर्ण

	ring->dim.bytes = bytes_processed;
	ring->dim.packets = rxpktprocessed;

	वापस rxpktprocessed;
पूर्ण

/* Rx NAPI polling method */
अटल पूर्णांक bcmgenet_rx_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा bcmgenet_rx_ring *ring = container_of(napi,
			काष्ठा bcmgenet_rx_ring, napi);
	काष्ठा dim_sample dim_sample = अणुपूर्ण;
	अचिन्हित पूर्णांक work_करोne;

	work_करोne = bcmgenet_desc_rx(ring, budget);

	अगर (work_करोne < budget) अणु
		napi_complete_करोne(napi, work_करोne);
		ring->पूर्णांक_enable(ring);
	पूर्ण

	अगर (ring->dim.use_dim) अणु
		dim_update_sample(ring->dim.event_ctr, ring->dim.packets,
				  ring->dim.bytes, &dim_sample);
		net_dim(&ring->dim.dim, dim_sample);
	पूर्ण

	वापस work_करोne;
पूर्ण

अटल व्योम bcmgenet_dim_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा dim *dim = container_of(work, काष्ठा dim, work);
	काष्ठा bcmgenet_net_dim *ndim =
			container_of(dim, काष्ठा bcmgenet_net_dim, dim);
	काष्ठा bcmgenet_rx_ring *ring =
			container_of(ndim, काष्ठा bcmgenet_rx_ring, dim);
	काष्ठा dim_cq_moder cur_profile =
			net_dim_get_rx_moderation(dim->mode, dim->profile_ix);

	bcmgenet_set_rx_coalesce(ring, cur_profile.usec, cur_profile.pkts);
	dim->state = DIM_START_MEASURE;
पूर्ण

/* Assign skb to RX DMA descriptor. */
अटल पूर्णांक bcmgenet_alloc_rx_buffers(काष्ठा bcmgenet_priv *priv,
				     काष्ठा bcmgenet_rx_ring *ring)
अणु
	काष्ठा enet_cb *cb;
	काष्ठा sk_buff *skb;
	पूर्णांक i;

	netअगर_dbg(priv, hw, priv->dev, "%s\n", __func__);

	/* loop here क्रम each buffer needing assign */
	क्रम (i = 0; i < ring->size; i++) अणु
		cb = ring->cbs + i;
		skb = bcmgenet_rx_refill(priv, cb);
		अगर (skb)
			dev_consume_skb_any(skb);
		अगर (!cb->skb)
			वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम bcmgenet_मुक्त_rx_buffers(काष्ठा bcmgenet_priv *priv)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा enet_cb *cb;
	पूर्णांक i;

	क्रम (i = 0; i < priv->num_rx_bds; i++) अणु
		cb = &priv->rx_cbs[i];

		skb = bcmgenet_मुक्त_rx_cb(&priv->pdev->dev, cb);
		अगर (skb)
			dev_consume_skb_any(skb);
	पूर्ण
पूर्ण

अटल व्योम umac_enable_set(काष्ठा bcmgenet_priv *priv, u32 mask, bool enable)
अणु
	u32 reg;

	reg = bcmgenet_umac_पढ़ोl(priv, UMAC_CMD);
	अगर (reg & CMD_SW_RESET)
		वापस;
	अगर (enable)
		reg |= mask;
	अन्यथा
		reg &= ~mask;
	bcmgenet_umac_ग_लिखोl(priv, reg, UMAC_CMD);

	/* UniMAC stops on a packet boundary, रुको क्रम a full-size packet
	 * to be processed
	 */
	अगर (enable == 0)
		usleep_range(1000, 2000);
पूर्ण

अटल व्योम reset_umac(काष्ठा bcmgenet_priv *priv)
अणु
	/* 7358a0/7552a0: bad शेष in RBUF_FLUSH_CTRL.umac_sw_rst */
	bcmgenet_rbuf_ctrl_set(priv, 0);
	udelay(10);

	/* issue soft reset and disable MAC जबतक updating its रेजिस्टरs */
	bcmgenet_umac_ग_लिखोl(priv, CMD_SW_RESET, UMAC_CMD);
	udelay(2);
पूर्ण

अटल व्योम bcmgenet_पूर्णांकr_disable(काष्ठा bcmgenet_priv *priv)
अणु
	/* Mask all पूर्णांकerrupts.*/
	bcmgenet_पूर्णांकrl2_0_ग_लिखोl(priv, 0xFFFFFFFF, INTRL2_CPU_MASK_SET);
	bcmgenet_पूर्णांकrl2_0_ग_लिखोl(priv, 0xFFFFFFFF, INTRL2_CPU_CLEAR);
	bcmgenet_पूर्णांकrl2_1_ग_लिखोl(priv, 0xFFFFFFFF, INTRL2_CPU_MASK_SET);
	bcmgenet_पूर्णांकrl2_1_ग_लिखोl(priv, 0xFFFFFFFF, INTRL2_CPU_CLEAR);
पूर्ण

अटल व्योम bcmgenet_link_पूर्णांकr_enable(काष्ठा bcmgenet_priv *priv)
अणु
	u32 पूर्णांक0_enable = 0;

	/* Monitor cable plug/unplugged event क्रम पूर्णांकernal PHY, बाह्यal PHY
	 * and MoCA PHY
	 */
	अगर (priv->पूर्णांकernal_phy) अणु
		पूर्णांक0_enable |= UMAC_IRQ_LINK_EVENT;
		अगर (GENET_IS_V1(priv) || GENET_IS_V2(priv) || GENET_IS_V3(priv))
			पूर्णांक0_enable |= UMAC_IRQ_PHY_DET_R;
	पूर्ण अन्यथा अगर (priv->ext_phy) अणु
		पूर्णांक0_enable |= UMAC_IRQ_LINK_EVENT;
	पूर्ण अन्यथा अगर (priv->phy_पूर्णांकerface == PHY_INTERFACE_MODE_MOCA) अणु
		अगर (priv->hw_params->flags & GENET_HAS_MOCA_LINK_DET)
			पूर्णांक0_enable |= UMAC_IRQ_LINK_EVENT;
	पूर्ण
	bcmgenet_पूर्णांकrl2_0_ग_लिखोl(priv, पूर्णांक0_enable, INTRL2_CPU_MASK_CLEAR);
पूर्ण

अटल व्योम init_umac(काष्ठा bcmgenet_priv *priv)
अणु
	काष्ठा device *kdev = &priv->pdev->dev;
	u32 reg;
	u32 पूर्णांक0_enable = 0;

	dev_dbg(&priv->pdev->dev, "bcmgenet: init_umac\n");

	reset_umac(priv);

	/* clear tx/rx counter */
	bcmgenet_umac_ग_लिखोl(priv,
			     MIB_RESET_RX | MIB_RESET_TX | MIB_RESET_RUNT,
			     UMAC_MIB_CTRL);
	bcmgenet_umac_ग_लिखोl(priv, 0, UMAC_MIB_CTRL);

	bcmgenet_umac_ग_लिखोl(priv, ENET_MAX_MTU_SIZE, UMAC_MAX_FRAME_LEN);

	/* init tx रेजिस्टरs, enable TSB */
	reg = bcmgenet_tbuf_ctrl_get(priv);
	reg |= TBUF_64B_EN;
	bcmgenet_tbuf_ctrl_set(priv, reg);

	/* init rx रेजिस्टरs, enable ip header optimization and RSB */
	reg = bcmgenet_rbuf_पढ़ोl(priv, RBUF_CTRL);
	reg |= RBUF_ALIGN_2B | RBUF_64B_EN;
	bcmgenet_rbuf_ग_लिखोl(priv, reg, RBUF_CTRL);

	/* enable rx checksumming */
	reg = bcmgenet_rbuf_पढ़ोl(priv, RBUF_CHK_CTRL);
	reg |= RBUF_RXCHK_EN | RBUF_L3_PARSE_DIS;
	/* If UniMAC क्रमwards CRC, we need to skip over it to get
	 * a valid CHK bit to be set in the per-packet status word
	 */
	अगर (priv->crc_fwd_en)
		reg |= RBUF_SKIP_FCS;
	अन्यथा
		reg &= ~RBUF_SKIP_FCS;
	bcmgenet_rbuf_ग_लिखोl(priv, reg, RBUF_CHK_CTRL);

	अगर (!GENET_IS_V1(priv) && !GENET_IS_V2(priv))
		bcmgenet_rbuf_ग_लिखोl(priv, 1, RBUF_TBUF_SIZE_CTRL);

	bcmgenet_पूर्णांकr_disable(priv);

	/* Configure backpressure vectors क्रम MoCA */
	अगर (priv->phy_पूर्णांकerface == PHY_INTERFACE_MODE_MOCA) अणु
		reg = bcmgenet_bp_mc_get(priv);
		reg |= BIT(priv->hw_params->bp_in_en_shअगरt);

		/* bp_mask: back pressure mask */
		अगर (netअगर_is_multiqueue(priv->dev))
			reg |= priv->hw_params->bp_in_mask;
		अन्यथा
			reg &= ~priv->hw_params->bp_in_mask;
		bcmgenet_bp_mc_set(priv, reg);
	पूर्ण

	/* Enable MDIO पूर्णांकerrupts on GENET v3+ */
	अगर (priv->hw_params->flags & GENET_HAS_MDIO_INTR)
		पूर्णांक0_enable |= (UMAC_IRQ_MDIO_DONE | UMAC_IRQ_MDIO_ERROR);

	bcmgenet_पूर्णांकrl2_0_ग_लिखोl(priv, पूर्णांक0_enable, INTRL2_CPU_MASK_CLEAR);

	dev_dbg(kdev, "done init umac\n");
पूर्ण

अटल व्योम bcmgenet_init_dim(काष्ठा bcmgenet_rx_ring *ring,
			      व्योम (*cb)(काष्ठा work_काष्ठा *work))
अणु
	काष्ठा bcmgenet_net_dim *dim = &ring->dim;

	INIT_WORK(&dim->dim.work, cb);
	dim->dim.mode = DIM_CQ_PERIOD_MODE_START_FROM_EQE;
	dim->event_ctr = 0;
	dim->packets = 0;
	dim->bytes = 0;
पूर्ण

अटल व्योम bcmgenet_init_rx_coalesce(काष्ठा bcmgenet_rx_ring *ring)
अणु
	काष्ठा bcmgenet_net_dim *dim = &ring->dim;
	काष्ठा dim_cq_moder moder;
	u32 usecs, pkts;

	usecs = ring->rx_coalesce_usecs;
	pkts = ring->rx_max_coalesced_frames;

	/* If DIM was enabled, re-apply शेष parameters */
	अगर (dim->use_dim) अणु
		moder = net_dim_get_def_rx_moderation(dim->dim.mode);
		usecs = moder.usec;
		pkts = moder.pkts;
	पूर्ण

	bcmgenet_set_rx_coalesce(ring, usecs, pkts);
पूर्ण

/* Initialize a Tx ring aदीर्घ with corresponding hardware रेजिस्टरs */
अटल व्योम bcmgenet_init_tx_ring(काष्ठा bcmgenet_priv *priv,
				  अचिन्हित पूर्णांक index, अचिन्हित पूर्णांक size,
				  अचिन्हित पूर्णांक start_ptr, अचिन्हित पूर्णांक end_ptr)
अणु
	काष्ठा bcmgenet_tx_ring *ring = &priv->tx_rings[index];
	u32 words_per_bd = WORDS_PER_BD(priv);
	u32 flow_period_val = 0;

	spin_lock_init(&ring->lock);
	ring->priv = priv;
	ring->index = index;
	अगर (index == DESC_INDEX) अणु
		ring->queue = 0;
		ring->पूर्णांक_enable = bcmgenet_tx_ring16_पूर्णांक_enable;
		ring->पूर्णांक_disable = bcmgenet_tx_ring16_पूर्णांक_disable;
	पूर्ण अन्यथा अणु
		ring->queue = index + 1;
		ring->पूर्णांक_enable = bcmgenet_tx_ring_पूर्णांक_enable;
		ring->पूर्णांक_disable = bcmgenet_tx_ring_पूर्णांक_disable;
	पूर्ण
	ring->cbs = priv->tx_cbs + start_ptr;
	ring->size = size;
	ring->clean_ptr = start_ptr;
	ring->c_index = 0;
	ring->मुक्त_bds = size;
	ring->ग_लिखो_ptr = start_ptr;
	ring->cb_ptr = start_ptr;
	ring->end_ptr = end_ptr - 1;
	ring->prod_index = 0;

	/* Set flow period क्रम ring != 16 */
	अगर (index != DESC_INDEX)
		flow_period_val = ENET_MAX_MTU_SIZE << 16;

	bcmgenet_tdma_ring_ग_लिखोl(priv, index, 0, TDMA_PROD_INDEX);
	bcmgenet_tdma_ring_ग_लिखोl(priv, index, 0, TDMA_CONS_INDEX);
	bcmgenet_tdma_ring_ग_लिखोl(priv, index, 1, DMA_MBUF_DONE_THRESH);
	/* Disable rate control क्रम now */
	bcmgenet_tdma_ring_ग_लिखोl(priv, index, flow_period_val,
				  TDMA_FLOW_PERIOD);
	bcmgenet_tdma_ring_ग_लिखोl(priv, index,
				  ((size << DMA_RING_SIZE_SHIFT) |
				   RX_BUF_LENGTH), DMA_RING_BUF_SIZE);

	/* Set start and end address, पढ़ो and ग_लिखो poपूर्णांकers */
	bcmgenet_tdma_ring_ग_लिखोl(priv, index, start_ptr * words_per_bd,
				  DMA_START_ADDR);
	bcmgenet_tdma_ring_ग_लिखोl(priv, index, start_ptr * words_per_bd,
				  TDMA_READ_PTR);
	bcmgenet_tdma_ring_ग_लिखोl(priv, index, start_ptr * words_per_bd,
				  TDMA_WRITE_PTR);
	bcmgenet_tdma_ring_ग_लिखोl(priv, index, end_ptr * words_per_bd - 1,
				  DMA_END_ADDR);

	/* Initialize Tx NAPI */
	netअगर_tx_napi_add(priv->dev, &ring->napi, bcmgenet_tx_poll,
			  NAPI_POLL_WEIGHT);
पूर्ण

/* Initialize a RDMA ring */
अटल पूर्णांक bcmgenet_init_rx_ring(काष्ठा bcmgenet_priv *priv,
				 अचिन्हित पूर्णांक index, अचिन्हित पूर्णांक size,
				 अचिन्हित पूर्णांक start_ptr, अचिन्हित पूर्णांक end_ptr)
अणु
	काष्ठा bcmgenet_rx_ring *ring = &priv->rx_rings[index];
	u32 words_per_bd = WORDS_PER_BD(priv);
	पूर्णांक ret;

	ring->priv = priv;
	ring->index = index;
	अगर (index == DESC_INDEX) अणु
		ring->पूर्णांक_enable = bcmgenet_rx_ring16_पूर्णांक_enable;
		ring->पूर्णांक_disable = bcmgenet_rx_ring16_पूर्णांक_disable;
	पूर्ण अन्यथा अणु
		ring->पूर्णांक_enable = bcmgenet_rx_ring_पूर्णांक_enable;
		ring->पूर्णांक_disable = bcmgenet_rx_ring_पूर्णांक_disable;
	पूर्ण
	ring->cbs = priv->rx_cbs + start_ptr;
	ring->size = size;
	ring->c_index = 0;
	ring->पढ़ो_ptr = start_ptr;
	ring->cb_ptr = start_ptr;
	ring->end_ptr = end_ptr - 1;

	ret = bcmgenet_alloc_rx_buffers(priv, ring);
	अगर (ret)
		वापस ret;

	bcmgenet_init_dim(ring, bcmgenet_dim_work);
	bcmgenet_init_rx_coalesce(ring);

	/* Initialize Rx NAPI */
	netअगर_napi_add(priv->dev, &ring->napi, bcmgenet_rx_poll,
		       NAPI_POLL_WEIGHT);

	bcmgenet_rdma_ring_ग_लिखोl(priv, index, 0, RDMA_PROD_INDEX);
	bcmgenet_rdma_ring_ग_लिखोl(priv, index, 0, RDMA_CONS_INDEX);
	bcmgenet_rdma_ring_ग_लिखोl(priv, index,
				  ((size << DMA_RING_SIZE_SHIFT) |
				   RX_BUF_LENGTH), DMA_RING_BUF_SIZE);
	bcmgenet_rdma_ring_ग_लिखोl(priv, index,
				  (DMA_FC_THRESH_LO <<
				   DMA_XOFF_THRESHOLD_SHIFT) |
				   DMA_FC_THRESH_HI, RDMA_XON_XOFF_THRESH);

	/* Set start and end address, पढ़ो and ग_लिखो poपूर्णांकers */
	bcmgenet_rdma_ring_ग_लिखोl(priv, index, start_ptr * words_per_bd,
				  DMA_START_ADDR);
	bcmgenet_rdma_ring_ग_लिखोl(priv, index, start_ptr * words_per_bd,
				  RDMA_READ_PTR);
	bcmgenet_rdma_ring_ग_लिखोl(priv, index, start_ptr * words_per_bd,
				  RDMA_WRITE_PTR);
	bcmgenet_rdma_ring_ग_लिखोl(priv, index, end_ptr * words_per_bd - 1,
				  DMA_END_ADDR);

	वापस ret;
पूर्ण

अटल व्योम bcmgenet_enable_tx_napi(काष्ठा bcmgenet_priv *priv)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा bcmgenet_tx_ring *ring;

	क्रम (i = 0; i < priv->hw_params->tx_queues; ++i) अणु
		ring = &priv->tx_rings[i];
		napi_enable(&ring->napi);
		ring->पूर्णांक_enable(ring);
	पूर्ण

	ring = &priv->tx_rings[DESC_INDEX];
	napi_enable(&ring->napi);
	ring->पूर्णांक_enable(ring);
पूर्ण

अटल व्योम bcmgenet_disable_tx_napi(काष्ठा bcmgenet_priv *priv)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा bcmgenet_tx_ring *ring;

	क्रम (i = 0; i < priv->hw_params->tx_queues; ++i) अणु
		ring = &priv->tx_rings[i];
		napi_disable(&ring->napi);
	पूर्ण

	ring = &priv->tx_rings[DESC_INDEX];
	napi_disable(&ring->napi);
पूर्ण

अटल व्योम bcmgenet_fini_tx_napi(काष्ठा bcmgenet_priv *priv)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा bcmgenet_tx_ring *ring;

	क्रम (i = 0; i < priv->hw_params->tx_queues; ++i) अणु
		ring = &priv->tx_rings[i];
		netअगर_napi_del(&ring->napi);
	पूर्ण

	ring = &priv->tx_rings[DESC_INDEX];
	netअगर_napi_del(&ring->napi);
पूर्ण

/* Initialize Tx queues
 *
 * Queues 0-3 are priority-based, each one has 32 descriptors,
 * with queue 0 being the highest priority queue.
 *
 * Queue 16 is the शेष Tx queue with
 * GENET_Q16_TX_BD_CNT = 256 - 4 * 32 = 128 descriptors.
 *
 * The transmit control block pool is then partitioned as follows:
 * - Tx queue 0 uses tx_cbs[0..31]
 * - Tx queue 1 uses tx_cbs[32..63]
 * - Tx queue 2 uses tx_cbs[64..95]
 * - Tx queue 3 uses tx_cbs[96..127]
 * - Tx queue 16 uses tx_cbs[128..255]
 */
अटल व्योम bcmgenet_init_tx_queues(काष्ठा net_device *dev)
अणु
	काष्ठा bcmgenet_priv *priv = netdev_priv(dev);
	u32 i, dma_enable;
	u32 dma_ctrl, ring_cfg;
	u32 dma_priority[3] = अणु0, 0, 0पूर्ण;

	dma_ctrl = bcmgenet_tdma_पढ़ोl(priv, DMA_CTRL);
	dma_enable = dma_ctrl & DMA_EN;
	dma_ctrl &= ~DMA_EN;
	bcmgenet_tdma_ग_लिखोl(priv, dma_ctrl, DMA_CTRL);

	dma_ctrl = 0;
	ring_cfg = 0;

	/* Enable strict priority arbiter mode */
	bcmgenet_tdma_ग_लिखोl(priv, DMA_ARBITER_SP, DMA_ARB_CTRL);

	/* Initialize Tx priority queues */
	क्रम (i = 0; i < priv->hw_params->tx_queues; i++) अणु
		bcmgenet_init_tx_ring(priv, i, priv->hw_params->tx_bds_per_q,
				      i * priv->hw_params->tx_bds_per_q,
				      (i + 1) * priv->hw_params->tx_bds_per_q);
		ring_cfg |= (1 << i);
		dma_ctrl |= (1 << (i + DMA_RING_BUF_EN_SHIFT));
		dma_priority[DMA_PRIO_REG_INDEX(i)] |=
			((GENET_Q0_PRIORITY + i) << DMA_PRIO_REG_SHIFT(i));
	पूर्ण

	/* Initialize Tx शेष queue 16 */
	bcmgenet_init_tx_ring(priv, DESC_INDEX, GENET_Q16_TX_BD_CNT,
			      priv->hw_params->tx_queues *
			      priv->hw_params->tx_bds_per_q,
			      TOTAL_DESC);
	ring_cfg |= (1 << DESC_INDEX);
	dma_ctrl |= (1 << (DESC_INDEX + DMA_RING_BUF_EN_SHIFT));
	dma_priority[DMA_PRIO_REG_INDEX(DESC_INDEX)] |=
		((GENET_Q0_PRIORITY + priv->hw_params->tx_queues) <<
		 DMA_PRIO_REG_SHIFT(DESC_INDEX));

	/* Set Tx queue priorities */
	bcmgenet_tdma_ग_लिखोl(priv, dma_priority[0], DMA_PRIORITY_0);
	bcmgenet_tdma_ग_लिखोl(priv, dma_priority[1], DMA_PRIORITY_1);
	bcmgenet_tdma_ग_लिखोl(priv, dma_priority[2], DMA_PRIORITY_2);

	/* Enable Tx queues */
	bcmgenet_tdma_ग_लिखोl(priv, ring_cfg, DMA_RING_CFG);

	/* Enable Tx DMA */
	अगर (dma_enable)
		dma_ctrl |= DMA_EN;
	bcmgenet_tdma_ग_लिखोl(priv, dma_ctrl, DMA_CTRL);
पूर्ण

अटल व्योम bcmgenet_enable_rx_napi(काष्ठा bcmgenet_priv *priv)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा bcmgenet_rx_ring *ring;

	क्रम (i = 0; i < priv->hw_params->rx_queues; ++i) अणु
		ring = &priv->rx_rings[i];
		napi_enable(&ring->napi);
		ring->पूर्णांक_enable(ring);
	पूर्ण

	ring = &priv->rx_rings[DESC_INDEX];
	napi_enable(&ring->napi);
	ring->पूर्णांक_enable(ring);
पूर्ण

अटल व्योम bcmgenet_disable_rx_napi(काष्ठा bcmgenet_priv *priv)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा bcmgenet_rx_ring *ring;

	क्रम (i = 0; i < priv->hw_params->rx_queues; ++i) अणु
		ring = &priv->rx_rings[i];
		napi_disable(&ring->napi);
		cancel_work_sync(&ring->dim.dim.work);
	पूर्ण

	ring = &priv->rx_rings[DESC_INDEX];
	napi_disable(&ring->napi);
	cancel_work_sync(&ring->dim.dim.work);
पूर्ण

अटल व्योम bcmgenet_fini_rx_napi(काष्ठा bcmgenet_priv *priv)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा bcmgenet_rx_ring *ring;

	क्रम (i = 0; i < priv->hw_params->rx_queues; ++i) अणु
		ring = &priv->rx_rings[i];
		netअगर_napi_del(&ring->napi);
	पूर्ण

	ring = &priv->rx_rings[DESC_INDEX];
	netअगर_napi_del(&ring->napi);
पूर्ण

/* Initialize Rx queues
 *
 * Queues 0-15 are priority queues. Hardware Filtering Block (HFB) can be
 * used to direct traffic to these queues.
 *
 * Queue 16 is the शेष Rx queue with GENET_Q16_RX_BD_CNT descriptors.
 */
अटल पूर्णांक bcmgenet_init_rx_queues(काष्ठा net_device *dev)
अणु
	काष्ठा bcmgenet_priv *priv = netdev_priv(dev);
	u32 i;
	u32 dma_enable;
	u32 dma_ctrl;
	u32 ring_cfg;
	पूर्णांक ret;

	dma_ctrl = bcmgenet_rdma_पढ़ोl(priv, DMA_CTRL);
	dma_enable = dma_ctrl & DMA_EN;
	dma_ctrl &= ~DMA_EN;
	bcmgenet_rdma_ग_लिखोl(priv, dma_ctrl, DMA_CTRL);

	dma_ctrl = 0;
	ring_cfg = 0;

	/* Initialize Rx priority queues */
	क्रम (i = 0; i < priv->hw_params->rx_queues; i++) अणु
		ret = bcmgenet_init_rx_ring(priv, i,
					    priv->hw_params->rx_bds_per_q,
					    i * priv->hw_params->rx_bds_per_q,
					    (i + 1) *
					    priv->hw_params->rx_bds_per_q);
		अगर (ret)
			वापस ret;

		ring_cfg |= (1 << i);
		dma_ctrl |= (1 << (i + DMA_RING_BUF_EN_SHIFT));
	पूर्ण

	/* Initialize Rx शेष queue 16 */
	ret = bcmgenet_init_rx_ring(priv, DESC_INDEX, GENET_Q16_RX_BD_CNT,
				    priv->hw_params->rx_queues *
				    priv->hw_params->rx_bds_per_q,
				    TOTAL_DESC);
	अगर (ret)
		वापस ret;

	ring_cfg |= (1 << DESC_INDEX);
	dma_ctrl |= (1 << (DESC_INDEX + DMA_RING_BUF_EN_SHIFT));

	/* Enable rings */
	bcmgenet_rdma_ग_लिखोl(priv, ring_cfg, DMA_RING_CFG);

	/* Configure ring as descriptor ring and re-enable DMA अगर enabled */
	अगर (dma_enable)
		dma_ctrl |= DMA_EN;
	bcmgenet_rdma_ग_लिखोl(priv, dma_ctrl, DMA_CTRL);

	वापस 0;
पूर्ण

अटल पूर्णांक bcmgenet_dma_tearकरोwn(काष्ठा bcmgenet_priv *priv)
अणु
	पूर्णांक ret = 0;
	पूर्णांक समयout = 0;
	u32 reg;
	u32 dma_ctrl;
	पूर्णांक i;

	/* Disable TDMA to stop add more frames in TX DMA */
	reg = bcmgenet_tdma_पढ़ोl(priv, DMA_CTRL);
	reg &= ~DMA_EN;
	bcmgenet_tdma_ग_लिखोl(priv, reg, DMA_CTRL);

	/* Check TDMA status रेजिस्टर to confirm TDMA is disabled */
	जबतक (समयout++ < DMA_TIMEOUT_VAL) अणु
		reg = bcmgenet_tdma_पढ़ोl(priv, DMA_STATUS);
		अगर (reg & DMA_DISABLED)
			अवरोध;

		udelay(1);
	पूर्ण

	अगर (समयout == DMA_TIMEOUT_VAL) अणु
		netdev_warn(priv->dev, "Timed out while disabling TX DMA\n");
		ret = -ETIMEDOUT;
	पूर्ण

	/* Wait 10ms क्रम packet drain in both tx and rx dma */
	usleep_range(10000, 20000);

	/* Disable RDMA */
	reg = bcmgenet_rdma_पढ़ोl(priv, DMA_CTRL);
	reg &= ~DMA_EN;
	bcmgenet_rdma_ग_लिखोl(priv, reg, DMA_CTRL);

	समयout = 0;
	/* Check RDMA status रेजिस्टर to confirm RDMA is disabled */
	जबतक (समयout++ < DMA_TIMEOUT_VAL) अणु
		reg = bcmgenet_rdma_पढ़ोl(priv, DMA_STATUS);
		अगर (reg & DMA_DISABLED)
			अवरोध;

		udelay(1);
	पूर्ण

	अगर (समयout == DMA_TIMEOUT_VAL) अणु
		netdev_warn(priv->dev, "Timed out while disabling RX DMA\n");
		ret = -ETIMEDOUT;
	पूर्ण

	dma_ctrl = 0;
	क्रम (i = 0; i < priv->hw_params->rx_queues; i++)
		dma_ctrl |= (1 << (i + DMA_RING_BUF_EN_SHIFT));
	reg = bcmgenet_rdma_पढ़ोl(priv, DMA_CTRL);
	reg &= ~dma_ctrl;
	bcmgenet_rdma_ग_लिखोl(priv, reg, DMA_CTRL);

	dma_ctrl = 0;
	क्रम (i = 0; i < priv->hw_params->tx_queues; i++)
		dma_ctrl |= (1 << (i + DMA_RING_BUF_EN_SHIFT));
	reg = bcmgenet_tdma_पढ़ोl(priv, DMA_CTRL);
	reg &= ~dma_ctrl;
	bcmgenet_tdma_ग_लिखोl(priv, reg, DMA_CTRL);

	वापस ret;
पूर्ण

अटल व्योम bcmgenet_fini_dma(काष्ठा bcmgenet_priv *priv)
अणु
	काष्ठा netdev_queue *txq;
	पूर्णांक i;

	bcmgenet_fini_rx_napi(priv);
	bcmgenet_fini_tx_napi(priv);

	क्रम (i = 0; i < priv->num_tx_bds; i++)
		dev_kमुक्त_skb(bcmgenet_मुक्त_tx_cb(&priv->pdev->dev,
						  priv->tx_cbs + i));

	क्रम (i = 0; i < priv->hw_params->tx_queues; i++) अणु
		txq = netdev_get_tx_queue(priv->dev, priv->tx_rings[i].queue);
		netdev_tx_reset_queue(txq);
	पूर्ण

	txq = netdev_get_tx_queue(priv->dev, priv->tx_rings[DESC_INDEX].queue);
	netdev_tx_reset_queue(txq);

	bcmgenet_मुक्त_rx_buffers(priv);
	kमुक्त(priv->rx_cbs);
	kमुक्त(priv->tx_cbs);
पूर्ण

/* init_edma: Initialize DMA control रेजिस्टर */
अटल पूर्णांक bcmgenet_init_dma(काष्ठा bcmgenet_priv *priv)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक i;
	काष्ठा enet_cb *cb;

	netअगर_dbg(priv, hw, priv->dev, "%s\n", __func__);

	/* Initialize common Rx ring काष्ठाures */
	priv->rx_bds = priv->base + priv->hw_params->rdma_offset;
	priv->num_rx_bds = TOTAL_DESC;
	priv->rx_cbs = kसुस्मृति(priv->num_rx_bds, माप(काष्ठा enet_cb),
			       GFP_KERNEL);
	अगर (!priv->rx_cbs)
		वापस -ENOMEM;

	क्रम (i = 0; i < priv->num_rx_bds; i++) अणु
		cb = priv->rx_cbs + i;
		cb->bd_addr = priv->rx_bds + i * DMA_DESC_SIZE;
	पूर्ण

	/* Initialize common TX ring काष्ठाures */
	priv->tx_bds = priv->base + priv->hw_params->tdma_offset;
	priv->num_tx_bds = TOTAL_DESC;
	priv->tx_cbs = kसुस्मृति(priv->num_tx_bds, माप(काष्ठा enet_cb),
			       GFP_KERNEL);
	अगर (!priv->tx_cbs) अणु
		kमुक्त(priv->rx_cbs);
		वापस -ENOMEM;
	पूर्ण

	क्रम (i = 0; i < priv->num_tx_bds; i++) अणु
		cb = priv->tx_cbs + i;
		cb->bd_addr = priv->tx_bds + i * DMA_DESC_SIZE;
	पूर्ण

	/* Init rDma */
	bcmgenet_rdma_ग_लिखोl(priv, priv->dma_max_burst_length,
			     DMA_SCB_BURST_SIZE);

	/* Initialize Rx queues */
	ret = bcmgenet_init_rx_queues(priv->dev);
	अगर (ret) अणु
		netdev_err(priv->dev, "failed to initialize Rx queues\n");
		bcmgenet_मुक्त_rx_buffers(priv);
		kमुक्त(priv->rx_cbs);
		kमुक्त(priv->tx_cbs);
		वापस ret;
	पूर्ण

	/* Init tDma */
	bcmgenet_tdma_ग_लिखोl(priv, priv->dma_max_burst_length,
			     DMA_SCB_BURST_SIZE);

	/* Initialize Tx queues */
	bcmgenet_init_tx_queues(priv->dev);

	वापस 0;
पूर्ण

/* Interrupt bottom half */
अटल व्योम bcmgenet_irq_task(काष्ठा work_काष्ठा *work)
अणु
	अचिन्हित पूर्णांक status;
	काष्ठा bcmgenet_priv *priv = container_of(
			work, काष्ठा bcmgenet_priv, bcmgenet_irq_work);

	netअगर_dbg(priv, पूर्णांकr, priv->dev, "%s\n", __func__);

	spin_lock_irq(&priv->lock);
	status = priv->irq0_stat;
	priv->irq0_stat = 0;
	spin_unlock_irq(&priv->lock);

	अगर (status & UMAC_IRQ_PHY_DET_R &&
	    priv->dev->phydev->स्वतःneg != AUTONEG_ENABLE) अणु
		phy_init_hw(priv->dev->phydev);
		genphy_config_aneg(priv->dev->phydev);
	पूर्ण

	/* Link UP/DOWN event */
	अगर (status & UMAC_IRQ_LINK_EVENT)
		phy_mac_पूर्णांकerrupt(priv->dev->phydev);

पूर्ण

/* bcmgenet_isr1: handle Rx and Tx priority queues */
अटल irqवापस_t bcmgenet_isr1(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा bcmgenet_priv *priv = dev_id;
	काष्ठा bcmgenet_rx_ring *rx_ring;
	काष्ठा bcmgenet_tx_ring *tx_ring;
	अचिन्हित पूर्णांक index, status;

	/* Read irq status */
	status = bcmgenet_पूर्णांकrl2_1_पढ़ोl(priv, INTRL2_CPU_STAT) &
		~bcmgenet_पूर्णांकrl2_1_पढ़ोl(priv, INTRL2_CPU_MASK_STATUS);

	/* clear पूर्णांकerrupts */
	bcmgenet_पूर्णांकrl2_1_ग_लिखोl(priv, status, INTRL2_CPU_CLEAR);

	netअगर_dbg(priv, पूर्णांकr, priv->dev,
		  "%s: IRQ=0x%x\n", __func__, status);

	/* Check Rx priority queue पूर्णांकerrupts */
	क्रम (index = 0; index < priv->hw_params->rx_queues; index++) अणु
		अगर (!(status & BIT(UMAC_IRQ1_RX_INTR_SHIFT + index)))
			जारी;

		rx_ring = &priv->rx_rings[index];
		rx_ring->dim.event_ctr++;

		अगर (likely(napi_schedule_prep(&rx_ring->napi))) अणु
			rx_ring->पूर्णांक_disable(rx_ring);
			__napi_schedule_irqoff(&rx_ring->napi);
		पूर्ण
	पूर्ण

	/* Check Tx priority queue पूर्णांकerrupts */
	क्रम (index = 0; index < priv->hw_params->tx_queues; index++) अणु
		अगर (!(status & BIT(index)))
			जारी;

		tx_ring = &priv->tx_rings[index];

		अगर (likely(napi_schedule_prep(&tx_ring->napi))) अणु
			tx_ring->पूर्णांक_disable(tx_ring);
			__napi_schedule_irqoff(&tx_ring->napi);
		पूर्ण
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/* bcmgenet_isr0: handle Rx and Tx शेष queues + other stuff */
अटल irqवापस_t bcmgenet_isr0(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा bcmgenet_priv *priv = dev_id;
	काष्ठा bcmgenet_rx_ring *rx_ring;
	काष्ठा bcmgenet_tx_ring *tx_ring;
	अचिन्हित पूर्णांक status;
	अचिन्हित दीर्घ flags;

	/* Read irq status */
	status = bcmgenet_पूर्णांकrl2_0_पढ़ोl(priv, INTRL2_CPU_STAT) &
		~bcmgenet_पूर्णांकrl2_0_पढ़ोl(priv, INTRL2_CPU_MASK_STATUS);

	/* clear पूर्णांकerrupts */
	bcmgenet_पूर्णांकrl2_0_ग_लिखोl(priv, status, INTRL2_CPU_CLEAR);

	netअगर_dbg(priv, पूर्णांकr, priv->dev,
		  "IRQ=0x%x\n", status);

	अगर (status & UMAC_IRQ_RXDMA_DONE) अणु
		rx_ring = &priv->rx_rings[DESC_INDEX];
		rx_ring->dim.event_ctr++;

		अगर (likely(napi_schedule_prep(&rx_ring->napi))) अणु
			rx_ring->पूर्णांक_disable(rx_ring);
			__napi_schedule_irqoff(&rx_ring->napi);
		पूर्ण
	पूर्ण

	अगर (status & UMAC_IRQ_TXDMA_DONE) अणु
		tx_ring = &priv->tx_rings[DESC_INDEX];

		अगर (likely(napi_schedule_prep(&tx_ring->napi))) अणु
			tx_ring->पूर्णांक_disable(tx_ring);
			__napi_schedule_irqoff(&tx_ring->napi);
		पूर्ण
	पूर्ण

	अगर ((priv->hw_params->flags & GENET_HAS_MDIO_INTR) &&
		status & (UMAC_IRQ_MDIO_DONE | UMAC_IRQ_MDIO_ERROR)) अणु
		wake_up(&priv->wq);
	पूर्ण

	/* all other पूर्णांकerested पूर्णांकerrupts handled in bottom half */
	status &= (UMAC_IRQ_LINK_EVENT | UMAC_IRQ_PHY_DET_R);
	अगर (status) अणु
		/* Save irq status क्रम bottom-half processing. */
		spin_lock_irqsave(&priv->lock, flags);
		priv->irq0_stat |= status;
		spin_unlock_irqrestore(&priv->lock, flags);

		schedule_work(&priv->bcmgenet_irq_work);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t bcmgenet_wol_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	/* Acknowledge the पूर्णांकerrupt */
	वापस IRQ_HANDLED;
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
अटल व्योम bcmgenet_poll_controller(काष्ठा net_device *dev)
अणु
	काष्ठा bcmgenet_priv *priv = netdev_priv(dev);

	/* Invoke the मुख्य RX/TX पूर्णांकerrupt handler */
	disable_irq(priv->irq0);
	bcmgenet_isr0(priv->irq0, priv);
	enable_irq(priv->irq0);

	/* And the पूर्णांकerrupt handler क्रम RX/TX priority queues */
	disable_irq(priv->irq1);
	bcmgenet_isr1(priv->irq1, priv);
	enable_irq(priv->irq1);
पूर्ण
#पूर्ण_अगर

अटल व्योम bcmgenet_umac_reset(काष्ठा bcmgenet_priv *priv)
अणु
	u32 reg;

	reg = bcmgenet_rbuf_ctrl_get(priv);
	reg |= BIT(1);
	bcmgenet_rbuf_ctrl_set(priv, reg);
	udelay(10);

	reg &= ~BIT(1);
	bcmgenet_rbuf_ctrl_set(priv, reg);
	udelay(10);
पूर्ण

अटल व्योम bcmgenet_set_hw_addr(काष्ठा bcmgenet_priv *priv,
				 अचिन्हित अक्षर *addr)
अणु
	bcmgenet_umac_ग_लिखोl(priv, get_unaligned_be32(&addr[0]), UMAC_MAC0);
	bcmgenet_umac_ग_लिखोl(priv, get_unaligned_be16(&addr[4]), UMAC_MAC1);
पूर्ण

अटल व्योम bcmgenet_get_hw_addr(काष्ठा bcmgenet_priv *priv,
				 अचिन्हित अक्षर *addr)
अणु
	u32 addr_पंचांगp;

	addr_पंचांगp = bcmgenet_umac_पढ़ोl(priv, UMAC_MAC0);
	put_unaligned_be32(addr_पंचांगp, &addr[0]);
	addr_पंचांगp = bcmgenet_umac_पढ़ोl(priv, UMAC_MAC1);
	put_unaligned_be16(addr_पंचांगp, &addr[4]);
पूर्ण

/* Returns a reusable dma control रेजिस्टर value */
अटल u32 bcmgenet_dma_disable(काष्ठा bcmgenet_priv *priv)
अणु
	u32 reg;
	u32 dma_ctrl;

	/* disable DMA */
	dma_ctrl = 1 << (DESC_INDEX + DMA_RING_BUF_EN_SHIFT) | DMA_EN;
	reg = bcmgenet_tdma_पढ़ोl(priv, DMA_CTRL);
	reg &= ~dma_ctrl;
	bcmgenet_tdma_ग_लिखोl(priv, reg, DMA_CTRL);

	reg = bcmgenet_rdma_पढ़ोl(priv, DMA_CTRL);
	reg &= ~dma_ctrl;
	bcmgenet_rdma_ग_लिखोl(priv, reg, DMA_CTRL);

	bcmgenet_umac_ग_लिखोl(priv, 1, UMAC_TX_FLUSH);
	udelay(10);
	bcmgenet_umac_ग_लिखोl(priv, 0, UMAC_TX_FLUSH);

	वापस dma_ctrl;
पूर्ण

अटल व्योम bcmgenet_enable_dma(काष्ठा bcmgenet_priv *priv, u32 dma_ctrl)
अणु
	u32 reg;

	reg = bcmgenet_rdma_पढ़ोl(priv, DMA_CTRL);
	reg |= dma_ctrl;
	bcmgenet_rdma_ग_लिखोl(priv, reg, DMA_CTRL);

	reg = bcmgenet_tdma_पढ़ोl(priv, DMA_CTRL);
	reg |= dma_ctrl;
	bcmgenet_tdma_ग_लिखोl(priv, reg, DMA_CTRL);
पूर्ण

अटल व्योम bcmgenet_netअगर_start(काष्ठा net_device *dev)
अणु
	काष्ठा bcmgenet_priv *priv = netdev_priv(dev);

	/* Start the network engine */
	bcmgenet_set_rx_mode(dev);
	bcmgenet_enable_rx_napi(priv);

	umac_enable_set(priv, CMD_TX_EN | CMD_RX_EN, true);

	bcmgenet_enable_tx_napi(priv);

	/* Monitor link पूर्णांकerrupts now */
	bcmgenet_link_पूर्णांकr_enable(priv);

	phy_start(dev->phydev);
पूर्ण

अटल पूर्णांक bcmgenet_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा bcmgenet_priv *priv = netdev_priv(dev);
	अचिन्हित दीर्घ dma_ctrl;
	u32 reg;
	पूर्णांक ret;

	netअगर_dbg(priv, अगरup, dev, "bcmgenet_open\n");

	/* Turn on the घड़ी */
	clk_prepare_enable(priv->clk);

	/* If this is an पूर्णांकernal GPHY, घातer it back on now, beक्रमe UniMAC is
	 * brought out of reset as असलolutely no UniMAC activity is allowed
	 */
	अगर (priv->पूर्णांकernal_phy)
		bcmgenet_घातer_up(priv, GENET_POWER_PASSIVE);

	/* take MAC out of reset */
	bcmgenet_umac_reset(priv);

	init_umac(priv);

	/* Apply features again in हाल we changed them जबतक पूर्णांकerface was
	 * करोwn
	 */
	bcmgenet_set_features(dev, dev->features);

	bcmgenet_set_hw_addr(priv, dev->dev_addr);

	अगर (priv->पूर्णांकernal_phy) अणु
		reg = bcmgenet_ext_पढ़ोl(priv, EXT_EXT_PWR_MGMT);
		reg |= EXT_ENERGY_DET_MASK;
		bcmgenet_ext_ग_लिखोl(priv, reg, EXT_EXT_PWR_MGMT);
	पूर्ण

	/* Disable RX/TX DMA and flush TX queues */
	dma_ctrl = bcmgenet_dma_disable(priv);

	/* Reinitialize TDMA and RDMA and SW housekeeping */
	ret = bcmgenet_init_dma(priv);
	अगर (ret) अणु
		netdev_err(dev, "failed to initialize DMA\n");
		जाओ err_clk_disable;
	पूर्ण

	/* Always enable ring 16 - descriptor ring */
	bcmgenet_enable_dma(priv, dma_ctrl);

	/* HFB init */
	bcmgenet_hfb_init(priv);

	ret = request_irq(priv->irq0, bcmgenet_isr0, IRQF_SHARED,
			  dev->name, priv);
	अगर (ret < 0) अणु
		netdev_err(dev, "can't request IRQ %d\n", priv->irq0);
		जाओ err_fini_dma;
	पूर्ण

	ret = request_irq(priv->irq1, bcmgenet_isr1, IRQF_SHARED,
			  dev->name, priv);
	अगर (ret < 0) अणु
		netdev_err(dev, "can't request IRQ %d\n", priv->irq1);
		जाओ err_irq0;
	पूर्ण

	ret = bcmgenet_mii_probe(dev);
	अगर (ret) अणु
		netdev_err(dev, "failed to connect to PHY\n");
		जाओ err_irq1;
	पूर्ण

	bcmgenet_netअगर_start(dev);

	netअगर_tx_start_all_queues(dev);

	वापस 0;

err_irq1:
	मुक्त_irq(priv->irq1, priv);
err_irq0:
	मुक्त_irq(priv->irq0, priv);
err_fini_dma:
	bcmgenet_dma_tearकरोwn(priv);
	bcmgenet_fini_dma(priv);
err_clk_disable:
	अगर (priv->पूर्णांकernal_phy)
		bcmgenet_घातer_करोwn(priv, GENET_POWER_PASSIVE);
	clk_disable_unprepare(priv->clk);
	वापस ret;
पूर्ण

अटल व्योम bcmgenet_netअगर_stop(काष्ठा net_device *dev)
अणु
	काष्ठा bcmgenet_priv *priv = netdev_priv(dev);

	bcmgenet_disable_tx_napi(priv);
	netअगर_tx_disable(dev);

	/* Disable MAC receive */
	umac_enable_set(priv, CMD_RX_EN, false);

	bcmgenet_dma_tearकरोwn(priv);

	/* Disable MAC transmit. TX DMA disabled must be करोne beक्रमe this */
	umac_enable_set(priv, CMD_TX_EN, false);

	phy_stop(dev->phydev);
	bcmgenet_disable_rx_napi(priv);
	bcmgenet_पूर्णांकr_disable(priv);

	/* Wait क्रम pending work items to complete. Since पूर्णांकerrupts are
	 * disabled no new work will be scheduled.
	 */
	cancel_work_sync(&priv->bcmgenet_irq_work);

	priv->old_link = -1;
	priv->old_speed = -1;
	priv->old_duplex = -1;
	priv->old_छोड़ो = -1;

	/* tx reclaim */
	bcmgenet_tx_reclaim_all(dev);
	bcmgenet_fini_dma(priv);
पूर्ण

अटल पूर्णांक bcmgenet_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा bcmgenet_priv *priv = netdev_priv(dev);
	पूर्णांक ret = 0;

	netअगर_dbg(priv, अगरकरोwn, dev, "bcmgenet_close\n");

	bcmgenet_netअगर_stop(dev);

	/* Really समाप्त the PHY state machine and disconnect from it */
	phy_disconnect(dev->phydev);

	मुक्त_irq(priv->irq0, priv);
	मुक्त_irq(priv->irq1, priv);

	अगर (priv->पूर्णांकernal_phy)
		ret = bcmgenet_घातer_करोwn(priv, GENET_POWER_PASSIVE);

	clk_disable_unprepare(priv->clk);

	वापस ret;
पूर्ण

अटल व्योम bcmgenet_dump_tx_queue(काष्ठा bcmgenet_tx_ring *ring)
अणु
	काष्ठा bcmgenet_priv *priv = ring->priv;
	u32 p_index, c_index, पूर्णांकsts, पूर्णांकmsk;
	काष्ठा netdev_queue *txq;
	अचिन्हित पूर्णांक मुक्त_bds;
	bool txq_stopped;

	अगर (!netअगर_msg_tx_err(priv))
		वापस;

	txq = netdev_get_tx_queue(priv->dev, ring->queue);

	spin_lock(&ring->lock);
	अगर (ring->index == DESC_INDEX) अणु
		पूर्णांकsts = ~bcmgenet_पूर्णांकrl2_0_पढ़ोl(priv, INTRL2_CPU_MASK_STATUS);
		पूर्णांकmsk = UMAC_IRQ_TXDMA_DONE | UMAC_IRQ_TXDMA_MBDONE;
	पूर्ण अन्यथा अणु
		पूर्णांकsts = ~bcmgenet_पूर्णांकrl2_1_पढ़ोl(priv, INTRL2_CPU_MASK_STATUS);
		पूर्णांकmsk = 1 << ring->index;
	पूर्ण
	c_index = bcmgenet_tdma_ring_पढ़ोl(priv, ring->index, TDMA_CONS_INDEX);
	p_index = bcmgenet_tdma_ring_पढ़ोl(priv, ring->index, TDMA_PROD_INDEX);
	txq_stopped = netअगर_tx_queue_stopped(txq);
	मुक्त_bds = ring->मुक्त_bds;
	spin_unlock(&ring->lock);

	netअगर_err(priv, tx_err, priv->dev, "Ring %d queue %d status summary\n"
		  "TX queue status: %s, interrupts: %s\n"
		  "(sw)free_bds: %d (sw)size: %d\n"
		  "(sw)p_index: %d (hw)p_index: %d\n"
		  "(sw)c_index: %d (hw)c_index: %d\n"
		  "(sw)clean_p: %d (sw)write_p: %d\n"
		  "(sw)cb_ptr: %d (sw)end_ptr: %d\n",
		  ring->index, ring->queue,
		  txq_stopped ? "stopped" : "active",
		  पूर्णांकsts & पूर्णांकmsk ? "enabled" : "disabled",
		  मुक्त_bds, ring->size,
		  ring->prod_index, p_index & DMA_P_INDEX_MASK,
		  ring->c_index, c_index & DMA_C_INDEX_MASK,
		  ring->clean_ptr, ring->ग_लिखो_ptr,
		  ring->cb_ptr, ring->end_ptr);
पूर्ण

अटल व्योम bcmgenet_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा bcmgenet_priv *priv = netdev_priv(dev);
	u32 पूर्णांक0_enable = 0;
	u32 पूर्णांक1_enable = 0;
	अचिन्हित पूर्णांक q;

	netअगर_dbg(priv, tx_err, dev, "bcmgenet_timeout\n");

	क्रम (q = 0; q < priv->hw_params->tx_queues; q++)
		bcmgenet_dump_tx_queue(&priv->tx_rings[q]);
	bcmgenet_dump_tx_queue(&priv->tx_rings[DESC_INDEX]);

	bcmgenet_tx_reclaim_all(dev);

	क्रम (q = 0; q < priv->hw_params->tx_queues; q++)
		पूर्णांक1_enable |= (1 << q);

	पूर्णांक0_enable = UMAC_IRQ_TXDMA_DONE;

	/* Re-enable TX पूर्णांकerrupts अगर disabled */
	bcmgenet_पूर्णांकrl2_0_ग_लिखोl(priv, पूर्णांक0_enable, INTRL2_CPU_MASK_CLEAR);
	bcmgenet_पूर्णांकrl2_1_ग_लिखोl(priv, पूर्णांक1_enable, INTRL2_CPU_MASK_CLEAR);

	netअगर_trans_update(dev);

	dev->stats.tx_errors++;

	netअगर_tx_wake_all_queues(dev);
पूर्ण

#घोषणा MAX_MDF_FILTER	17

अटल अंतरभूत व्योम bcmgenet_set_mdf_addr(काष्ठा bcmgenet_priv *priv,
					 अचिन्हित अक्षर *addr,
					 पूर्णांक *i)
अणु
	bcmgenet_umac_ग_लिखोl(priv, addr[0] << 8 | addr[1],
			     UMAC_MDF_ADDR + (*i * 4));
	bcmgenet_umac_ग_लिखोl(priv, addr[2] << 24 | addr[3] << 16 |
			     addr[4] << 8 | addr[5],
			     UMAC_MDF_ADDR + ((*i + 1) * 4));
	*i += 2;
पूर्ण

अटल व्योम bcmgenet_set_rx_mode(काष्ठा net_device *dev)
अणु
	काष्ठा bcmgenet_priv *priv = netdev_priv(dev);
	काष्ठा netdev_hw_addr *ha;
	पूर्णांक i, nfilter;
	u32 reg;

	netअगर_dbg(priv, hw, dev, "%s: %08X\n", __func__, dev->flags);

	/* Number of filters needed */
	nfilter = netdev_uc_count(dev) + netdev_mc_count(dev) + 2;

	/*
	 * Turn on promicuous mode क्रम three scenarios
	 * 1. IFF_PROMISC flag is set
	 * 2. IFF_ALLMULTI flag is set
	 * 3. The number of filters needed exceeds the number filters
	 *    supported by the hardware.
	*/
	reg = bcmgenet_umac_पढ़ोl(priv, UMAC_CMD);
	अगर ((dev->flags & (IFF_PROMISC | IFF_ALLMULTI)) ||
	    (nfilter > MAX_MDF_FILTER)) अणु
		reg |= CMD_PROMISC;
		bcmgenet_umac_ग_लिखोl(priv, reg, UMAC_CMD);
		bcmgenet_umac_ग_लिखोl(priv, 0, UMAC_MDF_CTRL);
		वापस;
	पूर्ण अन्यथा अणु
		reg &= ~CMD_PROMISC;
		bcmgenet_umac_ग_लिखोl(priv, reg, UMAC_CMD);
	पूर्ण

	/* update MDF filter */
	i = 0;
	/* Broadcast */
	bcmgenet_set_mdf_addr(priv, dev->broadcast, &i);
	/* my own address.*/
	bcmgenet_set_mdf_addr(priv, dev->dev_addr, &i);

	/* Unicast */
	netdev_क्रम_each_uc_addr(ha, dev)
		bcmgenet_set_mdf_addr(priv, ha->addr, &i);

	/* Multicast */
	netdev_क्रम_each_mc_addr(ha, dev)
		bcmgenet_set_mdf_addr(priv, ha->addr, &i);

	/* Enable filters */
	reg = GENMASK(MAX_MDF_FILTER - 1, MAX_MDF_FILTER - nfilter);
	bcmgenet_umac_ग_लिखोl(priv, reg, UMAC_MDF_CTRL);
पूर्ण

/* Set the hardware MAC address. */
अटल पूर्णांक bcmgenet_set_mac_addr(काष्ठा net_device *dev, व्योम *p)
अणु
	काष्ठा sockaddr *addr = p;

	/* Setting the MAC address at the hardware level is not possible
	 * without disabling the UniMAC RX/TX enable bits.
	 */
	अगर (netअगर_running(dev))
		वापस -EBUSY;

	ether_addr_copy(dev->dev_addr, addr->sa_data);

	वापस 0;
पूर्ण

अटल काष्ठा net_device_stats *bcmgenet_get_stats(काष्ठा net_device *dev)
अणु
	काष्ठा bcmgenet_priv *priv = netdev_priv(dev);
	अचिन्हित दीर्घ tx_bytes = 0, tx_packets = 0;
	अचिन्हित दीर्घ rx_bytes = 0, rx_packets = 0;
	अचिन्हित दीर्घ rx_errors = 0, rx_dropped = 0;
	काष्ठा bcmgenet_tx_ring *tx_ring;
	काष्ठा bcmgenet_rx_ring *rx_ring;
	अचिन्हित पूर्णांक q;

	क्रम (q = 0; q < priv->hw_params->tx_queues; q++) अणु
		tx_ring = &priv->tx_rings[q];
		tx_bytes += tx_ring->bytes;
		tx_packets += tx_ring->packets;
	पूर्ण
	tx_ring = &priv->tx_rings[DESC_INDEX];
	tx_bytes += tx_ring->bytes;
	tx_packets += tx_ring->packets;

	क्रम (q = 0; q < priv->hw_params->rx_queues; q++) अणु
		rx_ring = &priv->rx_rings[q];

		rx_bytes += rx_ring->bytes;
		rx_packets += rx_ring->packets;
		rx_errors += rx_ring->errors;
		rx_dropped += rx_ring->dropped;
	पूर्ण
	rx_ring = &priv->rx_rings[DESC_INDEX];
	rx_bytes += rx_ring->bytes;
	rx_packets += rx_ring->packets;
	rx_errors += rx_ring->errors;
	rx_dropped += rx_ring->dropped;

	dev->stats.tx_bytes = tx_bytes;
	dev->stats.tx_packets = tx_packets;
	dev->stats.rx_bytes = rx_bytes;
	dev->stats.rx_packets = rx_packets;
	dev->stats.rx_errors = rx_errors;
	dev->stats.rx_missed_errors = rx_errors;
	dev->stats.rx_dropped = rx_dropped;
	वापस &dev->stats;
पूर्ण

अटल पूर्णांक bcmgenet_change_carrier(काष्ठा net_device *dev, bool new_carrier)
अणु
	काष्ठा bcmgenet_priv *priv = netdev_priv(dev);

	अगर (!dev->phydev || !phy_is_pseuकरो_fixed_link(dev->phydev) ||
	    priv->phy_पूर्णांकerface != PHY_INTERFACE_MODE_MOCA)
		वापस -EOPNOTSUPP;

	अगर (new_carrier)
		netअगर_carrier_on(dev);
	अन्यथा
		netअगर_carrier_off(dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा net_device_ops bcmgenet_netdev_ops = अणु
	.nकरो_खोलो		= bcmgenet_खोलो,
	.nकरो_stop		= bcmgenet_बंद,
	.nकरो_start_xmit		= bcmgenet_xmit,
	.nकरो_tx_समयout		= bcmgenet_समयout,
	.nकरो_set_rx_mode	= bcmgenet_set_rx_mode,
	.nकरो_set_mac_address	= bcmgenet_set_mac_addr,
	.nकरो_करो_ioctl		= phy_करो_ioctl_running,
	.nकरो_set_features	= bcmgenet_set_features,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller	= bcmgenet_poll_controller,
#पूर्ण_अगर
	.nकरो_get_stats		= bcmgenet_get_stats,
	.nकरो_change_carrier	= bcmgenet_change_carrier,
पूर्ण;

/* Array of GENET hardware parameters/अक्षरacteristics */
अटल काष्ठा bcmgenet_hw_params bcmgenet_hw_params[] = अणु
	[GENET_V1] = अणु
		.tx_queues = 0,
		.tx_bds_per_q = 0,
		.rx_queues = 0,
		.rx_bds_per_q = 0,
		.bp_in_en_shअगरt = 16,
		.bp_in_mask = 0xffff,
		.hfb_filter_cnt = 16,
		.qtag_mask = 0x1F,
		.hfb_offset = 0x1000,
		.rdma_offset = 0x2000,
		.tdma_offset = 0x3000,
		.words_per_bd = 2,
	पूर्ण,
	[GENET_V2] = अणु
		.tx_queues = 4,
		.tx_bds_per_q = 32,
		.rx_queues = 0,
		.rx_bds_per_q = 0,
		.bp_in_en_shअगरt = 16,
		.bp_in_mask = 0xffff,
		.hfb_filter_cnt = 16,
		.qtag_mask = 0x1F,
		.tbuf_offset = 0x0600,
		.hfb_offset = 0x1000,
		.hfb_reg_offset = 0x2000,
		.rdma_offset = 0x3000,
		.tdma_offset = 0x4000,
		.words_per_bd = 2,
		.flags = GENET_HAS_EXT,
	पूर्ण,
	[GENET_V3] = अणु
		.tx_queues = 4,
		.tx_bds_per_q = 32,
		.rx_queues = 0,
		.rx_bds_per_q = 0,
		.bp_in_en_shअगरt = 17,
		.bp_in_mask = 0x1ffff,
		.hfb_filter_cnt = 48,
		.hfb_filter_size = 128,
		.qtag_mask = 0x3F,
		.tbuf_offset = 0x0600,
		.hfb_offset = 0x8000,
		.hfb_reg_offset = 0xfc00,
		.rdma_offset = 0x10000,
		.tdma_offset = 0x11000,
		.words_per_bd = 2,
		.flags = GENET_HAS_EXT | GENET_HAS_MDIO_INTR |
			 GENET_HAS_MOCA_LINK_DET,
	पूर्ण,
	[GENET_V4] = अणु
		.tx_queues = 4,
		.tx_bds_per_q = 32,
		.rx_queues = 0,
		.rx_bds_per_q = 0,
		.bp_in_en_shअगरt = 17,
		.bp_in_mask = 0x1ffff,
		.hfb_filter_cnt = 48,
		.hfb_filter_size = 128,
		.qtag_mask = 0x3F,
		.tbuf_offset = 0x0600,
		.hfb_offset = 0x8000,
		.hfb_reg_offset = 0xfc00,
		.rdma_offset = 0x2000,
		.tdma_offset = 0x4000,
		.words_per_bd = 3,
		.flags = GENET_HAS_40BITS | GENET_HAS_EXT |
			 GENET_HAS_MDIO_INTR | GENET_HAS_MOCA_LINK_DET,
	पूर्ण,
	[GENET_V5] = अणु
		.tx_queues = 4,
		.tx_bds_per_q = 32,
		.rx_queues = 0,
		.rx_bds_per_q = 0,
		.bp_in_en_shअगरt = 17,
		.bp_in_mask = 0x1ffff,
		.hfb_filter_cnt = 48,
		.hfb_filter_size = 128,
		.qtag_mask = 0x3F,
		.tbuf_offset = 0x0600,
		.hfb_offset = 0x8000,
		.hfb_reg_offset = 0xfc00,
		.rdma_offset = 0x2000,
		.tdma_offset = 0x4000,
		.words_per_bd = 3,
		.flags = GENET_HAS_40BITS | GENET_HAS_EXT |
			 GENET_HAS_MDIO_INTR | GENET_HAS_MOCA_LINK_DET,
	पूर्ण,
पूर्ण;

/* Infer hardware parameters from the detected GENET version */
अटल व्योम bcmgenet_set_hw_params(काष्ठा bcmgenet_priv *priv)
अणु
	काष्ठा bcmgenet_hw_params *params;
	u32 reg;
	u8 major;
	u16 gphy_rev;

	अगर (GENET_IS_V5(priv) || GENET_IS_V4(priv)) अणु
		bcmgenet_dma_regs = bcmgenet_dma_regs_v3plus;
		genet_dma_ring_regs = genet_dma_ring_regs_v4;
	पूर्ण अन्यथा अगर (GENET_IS_V3(priv)) अणु
		bcmgenet_dma_regs = bcmgenet_dma_regs_v3plus;
		genet_dma_ring_regs = genet_dma_ring_regs_v123;
	पूर्ण अन्यथा अगर (GENET_IS_V2(priv)) अणु
		bcmgenet_dma_regs = bcmgenet_dma_regs_v2;
		genet_dma_ring_regs = genet_dma_ring_regs_v123;
	पूर्ण अन्यथा अगर (GENET_IS_V1(priv)) अणु
		bcmgenet_dma_regs = bcmgenet_dma_regs_v1;
		genet_dma_ring_regs = genet_dma_ring_regs_v123;
	पूर्ण

	/* क्रमागत genet_version starts at 1 */
	priv->hw_params = &bcmgenet_hw_params[priv->version];
	params = priv->hw_params;

	/* Read GENET HW version */
	reg = bcmgenet_sys_पढ़ोl(priv, SYS_REV_CTRL);
	major = (reg >> 24 & 0x0f);
	अगर (major == 6)
		major = 5;
	अन्यथा अगर (major == 5)
		major = 4;
	अन्यथा अगर (major == 0)
		major = 1;
	अगर (major != priv->version) अणु
		dev_err(&priv->pdev->dev,
			"GENET version mismatch, got: %d, configured for: %d\n",
			major, priv->version);
	पूर्ण

	/* Prपूर्णांक the GENET core version */
	dev_info(&priv->pdev->dev, "GENET " GENET_VER_FMT,
		 major, (reg >> 16) & 0x0f, reg & 0xffff);

	/* Store the पूर्णांकegrated PHY revision क्रम the MDIO probing function
	 * to pass this inक्रमmation to the PHY driver. The PHY driver expects
	 * to find the PHY major revision in bits 15:8 जबतक the GENET रेजिस्टर
	 * stores that inक्रमmation in bits 7:0, account क्रम that.
	 *
	 * On newer chips, starting with PHY revision G0, a new scheme is
	 * deployed similar to the Starfighter 2 चयन with GPHY major
	 * revision in bits 15:8 and patch level in bits 7:0. Major revision 0
	 * is reserved as well as special value 0x01ff, we have a small
	 * heuristic to check क्रम the new GPHY revision and re-arrange things
	 * so the GPHY driver is happy.
	 */
	gphy_rev = reg & 0xffff;

	अगर (GENET_IS_V5(priv)) अणु
		/* The EPHY revision should come from the MDIO रेजिस्टरs of
		 * the PHY not from GENET.
		 */
		अगर (gphy_rev != 0) अणु
			pr_warn("GENET is reporting EPHY revision: 0x%04x\n",
				gphy_rev);
		पूर्ण
	/* This is reserved so should require special treaपंचांगent */
	पूर्ण अन्यथा अगर (gphy_rev == 0 || gphy_rev == 0x01ff) अणु
		pr_warn("Invalid GPHY revision detected: 0x%04x\n", gphy_rev);
		वापस;
	/* This is the good old scheme, just GPHY major, no minor nor patch */
	पूर्ण अन्यथा अगर ((gphy_rev & 0xf0) != 0) अणु
		priv->gphy_rev = gphy_rev << 8;
	/* This is the new scheme, GPHY major rolls over with 0x10 = rev G0 */
	पूर्ण अन्यथा अगर ((gphy_rev & 0xff00) != 0) अणु
		priv->gphy_rev = gphy_rev;
	पूर्ण

#अगर_घोषित CONFIG_PHYS_ADDR_T_64BIT
	अगर (!(params->flags & GENET_HAS_40BITS))
		pr_warn("GENET does not support 40-bits PA\n");
#पूर्ण_अगर

	pr_debug("Configuration for version: %d\n"
		"TXq: %1d, TXqBDs: %1d, RXq: %1d, RXqBDs: %1d\n"
		"BP << en: %2d, BP msk: 0x%05x\n"
		"HFB count: %2d, QTAQ msk: 0x%05x\n"
		"TBUF: 0x%04x, HFB: 0x%04x, HFBreg: 0x%04x\n"
		"RDMA: 0x%05x, TDMA: 0x%05x\n"
		"Words/BD: %d\n",
		priv->version,
		params->tx_queues, params->tx_bds_per_q,
		params->rx_queues, params->rx_bds_per_q,
		params->bp_in_en_shअगरt, params->bp_in_mask,
		params->hfb_filter_cnt, params->qtag_mask,
		params->tbuf_offset, params->hfb_offset,
		params->hfb_reg_offset,
		params->rdma_offset, params->tdma_offset,
		params->words_per_bd);
पूर्ण

काष्ठा bcmgenet_plat_data अणु
	क्रमागत bcmgenet_version version;
	u32 dma_max_burst_length;
पूर्ण;

अटल स्थिर काष्ठा bcmgenet_plat_data v1_plat_data = अणु
	.version = GENET_V1,
	.dma_max_burst_length = DMA_MAX_BURST_LENGTH,
पूर्ण;

अटल स्थिर काष्ठा bcmgenet_plat_data v2_plat_data = अणु
	.version = GENET_V2,
	.dma_max_burst_length = DMA_MAX_BURST_LENGTH,
पूर्ण;

अटल स्थिर काष्ठा bcmgenet_plat_data v3_plat_data = अणु
	.version = GENET_V3,
	.dma_max_burst_length = DMA_MAX_BURST_LENGTH,
पूर्ण;

अटल स्थिर काष्ठा bcmgenet_plat_data v4_plat_data = अणु
	.version = GENET_V4,
	.dma_max_burst_length = DMA_MAX_BURST_LENGTH,
पूर्ण;

अटल स्थिर काष्ठा bcmgenet_plat_data v5_plat_data = अणु
	.version = GENET_V5,
	.dma_max_burst_length = DMA_MAX_BURST_LENGTH,
पूर्ण;

अटल स्थिर काष्ठा bcmgenet_plat_data bcm2711_plat_data = अणु
	.version = GENET_V5,
	.dma_max_burst_length = 0x08,
पूर्ण;

अटल स्थिर काष्ठा of_device_id bcmgenet_match[] = अणु
	अणु .compatible = "brcm,genet-v1", .data = &v1_plat_data पूर्ण,
	अणु .compatible = "brcm,genet-v2", .data = &v2_plat_data पूर्ण,
	अणु .compatible = "brcm,genet-v3", .data = &v3_plat_data पूर्ण,
	अणु .compatible = "brcm,genet-v4", .data = &v4_plat_data पूर्ण,
	अणु .compatible = "brcm,genet-v5", .data = &v5_plat_data पूर्ण,
	अणु .compatible = "brcm,bcm2711-genet-v5", .data = &bcm2711_plat_data पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, bcmgenet_match);

अटल पूर्णांक bcmgenet_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा bcmgenet_platक्रमm_data *pd = pdev->dev.platक्रमm_data;
	स्थिर काष्ठा bcmgenet_plat_data *pdata;
	काष्ठा bcmgenet_priv *priv;
	काष्ठा net_device *dev;
	अचिन्हित पूर्णांक i;
	पूर्णांक err = -EIO;

	/* Up to GENET_MAX_MQ_CNT + 1 TX queues and RX queues */
	dev = alloc_etherdev_mqs(माप(*priv), GENET_MAX_MQ_CNT + 1,
				 GENET_MAX_MQ_CNT + 1);
	अगर (!dev) अणु
		dev_err(&pdev->dev, "can't allocate net device\n");
		वापस -ENOMEM;
	पूर्ण

	priv = netdev_priv(dev);
	priv->irq0 = platक्रमm_get_irq(pdev, 0);
	अगर (priv->irq0 < 0) अणु
		err = priv->irq0;
		जाओ err;
	पूर्ण
	priv->irq1 = platक्रमm_get_irq(pdev, 1);
	अगर (priv->irq1 < 0) अणु
		err = priv->irq1;
		जाओ err;
	पूर्ण
	priv->wol_irq = platक्रमm_get_irq_optional(pdev, 2);

	priv->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(priv->base)) अणु
		err = PTR_ERR(priv->base);
		जाओ err;
	पूर्ण

	spin_lock_init(&priv->lock);

	SET_NETDEV_DEV(dev, &pdev->dev);
	dev_set_drvdata(&pdev->dev, dev);
	dev->watchकरोg_समयo = 2 * HZ;
	dev->ethtool_ops = &bcmgenet_ethtool_ops;
	dev->netdev_ops = &bcmgenet_netdev_ops;

	priv->msg_enable = netअगर_msg_init(-1, GENET_MSG_DEFAULT);

	/* Set शेष features */
	dev->features |= NETIF_F_SG | NETIF_F_HIGHDMA | NETIF_F_HW_CSUM |
			 NETIF_F_RXCSUM;
	dev->hw_features |= dev->features;
	dev->vlan_features |= dev->features;

	/* Request the WOL पूर्णांकerrupt and advertise suspend अगर available */
	priv->wol_irq_disabled = true;
	err = devm_request_irq(&pdev->dev, priv->wol_irq, bcmgenet_wol_isr, 0,
			       dev->name, priv);
	अगर (!err)
		device_set_wakeup_capable(&pdev->dev, 1);

	/* Set the needed headroom to account क्रम any possible
	 * features enabling/disabling at runसमय
	 */
	dev->needed_headroom += 64;

	netdev_boot_setup_check(dev);

	priv->dev = dev;
	priv->pdev = pdev;

	pdata = device_get_match_data(&pdev->dev);
	अगर (pdata) अणु
		priv->version = pdata->version;
		priv->dma_max_burst_length = pdata->dma_max_burst_length;
	पूर्ण अन्यथा अणु
		priv->version = pd->genet_version;
		priv->dma_max_burst_length = DMA_MAX_BURST_LENGTH;
	पूर्ण

	priv->clk = devm_clk_get_optional(&priv->pdev->dev, "enet");
	अगर (IS_ERR(priv->clk)) अणु
		dev_dbg(&priv->pdev->dev, "failed to get enet clock\n");
		err = PTR_ERR(priv->clk);
		जाओ err;
	पूर्ण

	err = clk_prepare_enable(priv->clk);
	अगर (err)
		जाओ err;

	bcmgenet_set_hw_params(priv);

	err = -EIO;
	अगर (priv->hw_params->flags & GENET_HAS_40BITS)
		err = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(40));
	अगर (err)
		err = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));
	अगर (err)
		जाओ err_clk_disable;

	/* Mii रुको queue */
	init_रुकोqueue_head(&priv->wq);
	/* Always use RX_BUF_LENGTH (2KB) buffer क्रम all chips */
	priv->rx_buf_len = RX_BUF_LENGTH;
	INIT_WORK(&priv->bcmgenet_irq_work, bcmgenet_irq_task);

	priv->clk_wol = devm_clk_get_optional(&priv->pdev->dev, "enet-wol");
	अगर (IS_ERR(priv->clk_wol)) अणु
		dev_dbg(&priv->pdev->dev, "failed to get enet-wol clock\n");
		err = PTR_ERR(priv->clk_wol);
		जाओ err_clk_disable;
	पूर्ण

	priv->clk_eee = devm_clk_get_optional(&priv->pdev->dev, "enet-eee");
	अगर (IS_ERR(priv->clk_eee)) अणु
		dev_dbg(&priv->pdev->dev, "failed to get enet-eee clock\n");
		err = PTR_ERR(priv->clk_eee);
		जाओ err_clk_disable;
	पूर्ण

	/* If this is an पूर्णांकernal GPHY, घातer it on now, beक्रमe UniMAC is
	 * brought out of reset as असलolutely no UniMAC activity is allowed
	 */
	अगर (device_get_phy_mode(&pdev->dev) == PHY_INTERFACE_MODE_INTERNAL)
		bcmgenet_घातer_up(priv, GENET_POWER_PASSIVE);

	अगर (pd && !IS_ERR_OR_शून्य(pd->mac_address))
		ether_addr_copy(dev->dev_addr, pd->mac_address);
	अन्यथा
		अगर (!device_get_mac_address(&pdev->dev, dev->dev_addr, ETH_ALEN))
			अगर (has_acpi_companion(&pdev->dev))
				bcmgenet_get_hw_addr(priv, dev->dev_addr);

	अगर (!is_valid_ether_addr(dev->dev_addr)) अणु
		dev_warn(&pdev->dev, "using random Ethernet MAC\n");
		eth_hw_addr_अक्रमom(dev);
	पूर्ण

	reset_umac(priv);

	err = bcmgenet_mii_init(dev);
	अगर (err)
		जाओ err_clk_disable;

	/* setup number of real queues  + 1 (GENET_V1 has 0 hardware queues
	 * just the ring 16 descriptor based TX
	 */
	netअगर_set_real_num_tx_queues(priv->dev, priv->hw_params->tx_queues + 1);
	netअगर_set_real_num_rx_queues(priv->dev, priv->hw_params->rx_queues + 1);

	/* Set शेष coalescing parameters */
	क्रम (i = 0; i < priv->hw_params->rx_queues; i++)
		priv->rx_rings[i].rx_max_coalesced_frames = 1;
	priv->rx_rings[DESC_INDEX].rx_max_coalesced_frames = 1;

	/* libphy will determine the link state */
	netअगर_carrier_off(dev);

	/* Turn off the मुख्य घड़ी, WOL घड़ी is handled separately */
	clk_disable_unprepare(priv->clk);

	err = रेजिस्टर_netdev(dev);
	अगर (err) अणु
		bcmgenet_mii_निकास(dev);
		जाओ err;
	पूर्ण

	वापस err;

err_clk_disable:
	clk_disable_unprepare(priv->clk);
err:
	मुक्त_netdev(dev);
	वापस err;
पूर्ण

अटल पूर्णांक bcmgenet_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा bcmgenet_priv *priv = dev_to_priv(&pdev->dev);

	dev_set_drvdata(&pdev->dev, शून्य);
	unरेजिस्टर_netdev(priv->dev);
	bcmgenet_mii_निकास(priv->dev);
	मुक्त_netdev(priv->dev);

	वापस 0;
पूर्ण

अटल व्योम bcmgenet_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	bcmgenet_हटाओ(pdev);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक bcmgenet_resume_noirq(काष्ठा device *d)
अणु
	काष्ठा net_device *dev = dev_get_drvdata(d);
	काष्ठा bcmgenet_priv *priv = netdev_priv(dev);
	पूर्णांक ret;
	u32 reg;

	अगर (!netअगर_running(dev))
		वापस 0;

	/* Turn on the घड़ी */
	ret = clk_prepare_enable(priv->clk);
	अगर (ret)
		वापस ret;

	अगर (device_may_wakeup(d) && priv->wolopts) अणु
		/* Account क्रम Wake-on-LAN events and clear those events
		 * (Some devices need more समय between enabling the घड़ीs
		 *  and the पूर्णांकerrupt रेजिस्टर reflecting the wake event so
		 *  पढ़ो the रेजिस्टर twice)
		 */
		reg = bcmgenet_पूर्णांकrl2_0_पढ़ोl(priv, INTRL2_CPU_STAT);
		reg = bcmgenet_पूर्णांकrl2_0_पढ़ोl(priv, INTRL2_CPU_STAT);
		अगर (reg & UMAC_IRQ_WAKE_EVENT)
			pm_wakeup_event(&priv->pdev->dev, 0);
	पूर्ण

	bcmgenet_पूर्णांकrl2_0_ग_लिखोl(priv, UMAC_IRQ_WAKE_EVENT, INTRL2_CPU_CLEAR);

	वापस 0;
पूर्ण

अटल पूर्णांक bcmgenet_resume(काष्ठा device *d)
अणु
	काष्ठा net_device *dev = dev_get_drvdata(d);
	काष्ठा bcmgenet_priv *priv = netdev_priv(dev);
	काष्ठा bcmgenet_rxnfc_rule *rule;
	अचिन्हित दीर्घ dma_ctrl;
	u32 reg;
	पूर्णांक ret;

	अगर (!netअगर_running(dev))
		वापस 0;

	/* From WOL-enabled suspend, चयन to regular घड़ी */
	अगर (device_may_wakeup(d) && priv->wolopts)
		bcmgenet_घातer_up(priv, GENET_POWER_WOL_MAGIC);

	/* If this is an पूर्णांकernal GPHY, घातer it back on now, beक्रमe UniMAC is
	 * brought out of reset as असलolutely no UniMAC activity is allowed
	 */
	अगर (priv->पूर्णांकernal_phy)
		bcmgenet_घातer_up(priv, GENET_POWER_PASSIVE);

	bcmgenet_umac_reset(priv);

	init_umac(priv);

	phy_init_hw(dev->phydev);

	/* Speed settings must be restored */
	genphy_config_aneg(dev->phydev);
	bcmgenet_mii_config(priv->dev, false);

	/* Restore enabled features */
	bcmgenet_set_features(dev, dev->features);

	bcmgenet_set_hw_addr(priv, dev->dev_addr);

	/* Restore hardware filters */
	bcmgenet_hfb_clear(priv);
	list_क्रम_each_entry(rule, &priv->rxnfc_list, list)
		अगर (rule->state != BCMGENET_RXNFC_STATE_UNUSED)
			bcmgenet_hfb_create_rxnfc_filter(priv, rule);

	अगर (priv->पूर्णांकernal_phy) अणु
		reg = bcmgenet_ext_पढ़ोl(priv, EXT_EXT_PWR_MGMT);
		reg |= EXT_ENERGY_DET_MASK;
		bcmgenet_ext_ग_लिखोl(priv, reg, EXT_EXT_PWR_MGMT);
	पूर्ण

	/* Disable RX/TX DMA and flush TX queues */
	dma_ctrl = bcmgenet_dma_disable(priv);

	/* Reinitialize TDMA and RDMA and SW housekeeping */
	ret = bcmgenet_init_dma(priv);
	अगर (ret) अणु
		netdev_err(dev, "failed to initialize DMA\n");
		जाओ out_clk_disable;
	पूर्ण

	/* Always enable ring 16 - descriptor ring */
	bcmgenet_enable_dma(priv, dma_ctrl);

	अगर (!device_may_wakeup(d))
		phy_resume(dev->phydev);

	अगर (priv->eee.eee_enabled)
		bcmgenet_eee_enable_set(dev, true);

	bcmgenet_netअगर_start(dev);

	netअगर_device_attach(dev);

	वापस 0;

out_clk_disable:
	अगर (priv->पूर्णांकernal_phy)
		bcmgenet_घातer_करोwn(priv, GENET_POWER_PASSIVE);
	clk_disable_unprepare(priv->clk);
	वापस ret;
पूर्ण

अटल पूर्णांक bcmgenet_suspend(काष्ठा device *d)
अणु
	काष्ठा net_device *dev = dev_get_drvdata(d);
	काष्ठा bcmgenet_priv *priv = netdev_priv(dev);

	अगर (!netअगर_running(dev))
		वापस 0;

	netअगर_device_detach(dev);

	bcmgenet_netअगर_stop(dev);

	अगर (!device_may_wakeup(d))
		phy_suspend(dev->phydev);

	/* Disable filtering */
	bcmgenet_hfb_reg_ग_लिखोl(priv, 0, HFB_CTRL);

	वापस 0;
पूर्ण

अटल पूर्णांक bcmgenet_suspend_noirq(काष्ठा device *d)
अणु
	काष्ठा net_device *dev = dev_get_drvdata(d);
	काष्ठा bcmgenet_priv *priv = netdev_priv(dev);
	पूर्णांक ret = 0;

	अगर (!netअगर_running(dev))
		वापस 0;

	/* Prepare the device क्रम Wake-on-LAN and चयन to the slow घड़ी */
	अगर (device_may_wakeup(d) && priv->wolopts)
		ret = bcmgenet_घातer_करोwn(priv, GENET_POWER_WOL_MAGIC);
	अन्यथा अगर (priv->पूर्णांकernal_phy)
		ret = bcmgenet_घातer_करोwn(priv, GENET_POWER_PASSIVE);

	/* Let the framework handle resumption and leave the घड़ीs on */
	अगर (ret)
		वापस ret;

	/* Turn off the घड़ीs */
	clk_disable_unprepare(priv->clk);

	वापस 0;
पूर्ण
#अन्यथा
#घोषणा bcmgenet_suspend	शून्य
#घोषणा bcmgenet_suspend_noirq	शून्य
#घोषणा bcmgenet_resume		शून्य
#घोषणा bcmgenet_resume_noirq	शून्य
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल स्थिर काष्ठा dev_pm_ops bcmgenet_pm_ops = अणु
	.suspend	= bcmgenet_suspend,
	.suspend_noirq	= bcmgenet_suspend_noirq,
	.resume		= bcmgenet_resume,
	.resume_noirq	= bcmgenet_resume_noirq,
पूर्ण;

अटल स्थिर काष्ठा acpi_device_id genet_acpi_match[] = अणु
	अणु "BCM6E4E", (kernel_uदीर्घ_t)&bcm2711_plat_data पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, genet_acpi_match);

अटल काष्ठा platक्रमm_driver bcmgenet_driver = अणु
	.probe	= bcmgenet_probe,
	.हटाओ	= bcmgenet_हटाओ,
	.shutकरोwn = bcmgenet_shutकरोwn,
	.driver	= अणु
		.name	= "bcmgenet",
		.of_match_table = bcmgenet_match,
		.pm	= &bcmgenet_pm_ops,
		.acpi_match_table = genet_acpi_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(bcmgenet_driver);

MODULE_AUTHOR("Broadcom Corporation");
MODULE_DESCRIPTION("Broadcom GENET Ethernet controller driver");
MODULE_ALIAS("platform:bcmgenet");
MODULE_LICENSE("GPL");
