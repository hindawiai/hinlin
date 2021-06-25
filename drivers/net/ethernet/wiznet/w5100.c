<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Ethernet driver क्रम the WIZnet W5100 chip.
 *
 * Copyright (C) 2006-2008 WIZnet Co.,Ltd.
 * Copyright (C) 2012 Mike Sinkovsky <msink@permonline.ru>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/platक्रमm_data/wiznet.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पन.स>
#समावेश <linux/ioport.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/gpपन.स>

#समावेश "w5100.h"

#घोषणा DRV_NAME	"w5100"
#घोषणा DRV_VERSION	"2012-04-04"

MODULE_DESCRIPTION("WIZnet W5100 Ethernet driver v"DRV_VERSION);
MODULE_AUTHOR("Mike Sinkovsky <msink@permonline.ru>");
MODULE_ALIAS("platform:"DRV_NAME);
MODULE_LICENSE("GPL");

/*
 * W5100/W5200/W5500 common रेजिस्टरs
 */
#घोषणा W5100_COMMON_REGS	0x0000
#घोषणा W5100_MR		0x0000 /* Mode Register */
#घोषणा   MR_RST		  0x80 /* S/W reset */
#घोषणा   MR_PB			  0x10 /* Ping block */
#घोषणा   MR_AI			  0x02 /* Address Auto-Increment */
#घोषणा   MR_IND		  0x01 /* Indirect mode */
#घोषणा W5100_SHAR		0x0009 /* Source MAC address */
#घोषणा W5100_IR		0x0015 /* Interrupt Register */
#घोषणा W5100_COMMON_REGS_LEN	0x0040

#घोषणा W5100_Sn_MR		0x0000 /* Sn Mode Register */
#घोषणा W5100_Sn_CR		0x0001 /* Sn Command Register */
#घोषणा W5100_Sn_IR		0x0002 /* Sn Interrupt Register */
#घोषणा W5100_Sn_SR		0x0003 /* Sn Status Register */
#घोषणा W5100_Sn_TX_FSR		0x0020 /* Sn Transmit मुक्त memory size */
#घोषणा W5100_Sn_TX_RD		0x0022 /* Sn Transmit memory पढ़ो poपूर्णांकer */
#घोषणा W5100_Sn_TX_WR		0x0024 /* Sn Transmit memory ग_लिखो poपूर्णांकer */
#घोषणा W5100_Sn_RX_RSR		0x0026 /* Sn Receive मुक्त memory size */
#घोषणा W5100_Sn_RX_RD		0x0028 /* Sn Receive memory पढ़ो poपूर्णांकer */

#घोषणा S0_REGS(priv)		((priv)->s0_regs)

#घोषणा W5100_S0_MR(priv)	(S0_REGS(priv) + W5100_Sn_MR)
#घोषणा   S0_MR_MACRAW		  0x04 /* MAC RAW mode */
#घोषणा   S0_MR_MF		  0x40 /* MAC Filter क्रम W5100 and W5200 */
#घोषणा   W5500_S0_MR_MF	  0x80 /* MAC Filter क्रम W5500 */
#घोषणा W5100_S0_CR(priv)	(S0_REGS(priv) + W5100_Sn_CR)
#घोषणा   S0_CR_OPEN		  0x01 /* OPEN command */
#घोषणा   S0_CR_CLOSE		  0x10 /* CLOSE command */
#घोषणा   S0_CR_SEND		  0x20 /* SEND command */
#घोषणा   S0_CR_RECV		  0x40 /* RECV command */
#घोषणा W5100_S0_IR(priv)	(S0_REGS(priv) + W5100_Sn_IR)
#घोषणा   S0_IR_SENDOK		  0x10 /* complete sending */
#घोषणा   S0_IR_RECV		  0x04 /* receiving data */
#घोषणा W5100_S0_SR(priv)	(S0_REGS(priv) + W5100_Sn_SR)
#घोषणा   S0_SR_MACRAW		  0x42 /* mac raw mode */
#घोषणा W5100_S0_TX_FSR(priv)	(S0_REGS(priv) + W5100_Sn_TX_FSR)
#घोषणा W5100_S0_TX_RD(priv)	(S0_REGS(priv) + W5100_Sn_TX_RD)
#घोषणा W5100_S0_TX_WR(priv)	(S0_REGS(priv) + W5100_Sn_TX_WR)
#घोषणा W5100_S0_RX_RSR(priv)	(S0_REGS(priv) + W5100_Sn_RX_RSR)
#घोषणा W5100_S0_RX_RD(priv)	(S0_REGS(priv) + W5100_Sn_RX_RD)

#घोषणा W5100_S0_REGS_LEN	0x0040

/*
 * W5100 and W5200 common रेजिस्टरs
 */
#घोषणा W5100_IMR		0x0016 /* Interrupt Mask Register */
#घोषणा   IR_S0			  0x01 /* S0 पूर्णांकerrupt */
#घोषणा W5100_RTR		0x0017 /* Retry Time-value Register */
#घोषणा   RTR_DEFAULT		  2000 /* =0x07d0 (2000) */

/*
 * W5100 specअगरic रेजिस्टर and memory
 */
#घोषणा W5100_RMSR		0x001a /* Receive Memory Size */
#घोषणा W5100_TMSR		0x001b /* Transmit Memory Size */

#घोषणा W5100_S0_REGS		0x0400

#घोषणा W5100_TX_MEM_START	0x4000
#घोषणा W5100_TX_MEM_SIZE	0x2000
#घोषणा W5100_RX_MEM_START	0x6000
#घोषणा W5100_RX_MEM_SIZE	0x2000

/*
 * W5200 specअगरic रेजिस्टर and memory
 */
#घोषणा W5200_S0_REGS		0x4000

#घोषणा W5200_Sn_RXMEM_SIZE(n)	(0x401e + (n) * 0x0100) /* Sn RX Memory Size */
#घोषणा W5200_Sn_TXMEM_SIZE(n)	(0x401f + (n) * 0x0100) /* Sn TX Memory Size */

#घोषणा W5200_TX_MEM_START	0x8000
#घोषणा W5200_TX_MEM_SIZE	0x4000
#घोषणा W5200_RX_MEM_START	0xc000
#घोषणा W5200_RX_MEM_SIZE	0x4000

/*
 * W5500 specअगरic रेजिस्टर and memory
 *
 * W5500 रेजिस्टर and memory are organized by multiple blocks.  Each one is
 * selected by 16bits offset address and 5bits block select bits.  So we
 * encode it पूर्णांकo 32bits address. (lower 16bits is offset address and
 * upper 16bits is block select bits)
 */
#घोषणा W5500_SIMR		0x0018 /* Socket Interrupt Mask Register */
#घोषणा W5500_RTR		0x0019 /* Retry Time-value Register */

#घोषणा W5500_S0_REGS		0x10000

#घोषणा W5500_Sn_RXMEM_SIZE(n)	\
		(0x1001e + (n) * 0x40000) /* Sn RX Memory Size */
#घोषणा W5500_Sn_TXMEM_SIZE(n)	\
		(0x1001f + (n) * 0x40000) /* Sn TX Memory Size */

#घोषणा W5500_TX_MEM_START	0x20000
#घोषणा W5500_TX_MEM_SIZE	0x04000
#घोषणा W5500_RX_MEM_START	0x30000
#घोषणा W5500_RX_MEM_SIZE	0x04000

/*
 * Device driver निजी data काष्ठाure
 */

काष्ठा w5100_priv अणु
	स्थिर काष्ठा w5100_ops *ops;

	/* Socket 0 रेजिस्टर offset address */
	u32 s0_regs;
	/* Socket 0 TX buffer offset address and size */
	u32 s0_tx_buf;
	u16 s0_tx_buf_size;
	/* Socket 0 RX buffer offset address and size */
	u32 s0_rx_buf;
	u16 s0_rx_buf_size;

	पूर्णांक irq;
	पूर्णांक link_irq;
	पूर्णांक link_gpio;

	काष्ठा napi_काष्ठा napi;
	काष्ठा net_device *ndev;
	bool promisc;
	u32 msg_enable;

	काष्ठा workqueue_काष्ठा *xfer_wq;
	काष्ठा work_काष्ठा rx_work;
	काष्ठा sk_buff *tx_skb;
	काष्ठा work_काष्ठा tx_work;
	काष्ठा work_काष्ठा setrx_work;
	काष्ठा work_काष्ठा restart_work;
पूर्ण;

/************************************************************************
 *
 *  Lowlevel I/O functions
 *
 ***********************************************************************/

काष्ठा w5100_mmio_priv अणु
	व्योम __iomem *base;
	/* Serialize access in indirect address mode */
	spinlock_t reg_lock;
पूर्ण;

अटल अंतरभूत काष्ठा w5100_mmio_priv *w5100_mmio_priv(काष्ठा net_device *dev)
अणु
	वापस w5100_ops_priv(dev);
पूर्ण

अटल अंतरभूत व्योम __iomem *w5100_mmio(काष्ठा net_device *ndev)
अणु
	काष्ठा w5100_mmio_priv *mmio_priv = w5100_mmio_priv(ndev);

	वापस mmio_priv->base;
पूर्ण

/*
 * In direct address mode host प्रणाली can directly access W5100 रेजिस्टरs
 * after mapping to Memory-Mapped I/O space.
 *
 * 0x8000 bytes are required क्रम memory space.
 */
अटल अंतरभूत पूर्णांक w5100_पढ़ो_direct(काष्ठा net_device *ndev, u32 addr)
अणु
	वापस ioपढ़ो8(w5100_mmio(ndev) + (addr << CONFIG_WIZNET_BUS_SHIFT));
पूर्ण

अटल अंतरभूत पूर्णांक __w5100_ग_लिखो_direct(काष्ठा net_device *ndev, u32 addr,
				       u8 data)
अणु
	ioग_लिखो8(data, w5100_mmio(ndev) + (addr << CONFIG_WIZNET_BUS_SHIFT));

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक w5100_ग_लिखो_direct(काष्ठा net_device *ndev, u32 addr, u8 data)
अणु
	__w5100_ग_लिखो_direct(ndev, addr, data);

	वापस 0;
पूर्ण

अटल पूर्णांक w5100_पढ़ो16_direct(काष्ठा net_device *ndev, u32 addr)
अणु
	u16 data;
	data  = w5100_पढ़ो_direct(ndev, addr) << 8;
	data |= w5100_पढ़ो_direct(ndev, addr + 1);
	वापस data;
पूर्ण

अटल पूर्णांक w5100_ग_लिखो16_direct(काष्ठा net_device *ndev, u32 addr, u16 data)
अणु
	__w5100_ग_लिखो_direct(ndev, addr, data >> 8);
	__w5100_ग_लिखो_direct(ndev, addr + 1, data);

	वापस 0;
पूर्ण

अटल पूर्णांक w5100_पढ़ोbulk_direct(काष्ठा net_device *ndev, u32 addr, u8 *buf,
				 पूर्णांक len)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < len; i++, addr++)
		*buf++ = w5100_पढ़ो_direct(ndev, addr);

	वापस 0;
पूर्ण

अटल पूर्णांक w5100_ग_लिखोbulk_direct(काष्ठा net_device *ndev, u32 addr,
				  स्थिर u8 *buf, पूर्णांक len)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < len; i++, addr++)
		__w5100_ग_लिखो_direct(ndev, addr, *buf++);

	वापस 0;
पूर्ण

अटल पूर्णांक w5100_mmio_init(काष्ठा net_device *ndev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(ndev->dev.parent);
	काष्ठा w5100_priv *priv = netdev_priv(ndev);
	काष्ठा w5100_mmio_priv *mmio_priv = w5100_mmio_priv(ndev);
	काष्ठा resource *mem;

	spin_lock_init(&mmio_priv->reg_lock);

	mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	mmio_priv->base = devm_ioremap_resource(&pdev->dev, mem);
	अगर (IS_ERR(mmio_priv->base))
		वापस PTR_ERR(mmio_priv->base);

	netdev_info(ndev, "at 0x%llx irq %d\n", (u64)mem->start, priv->irq);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा w5100_ops w5100_mmio_direct_ops = अणु
	.chip_id = W5100,
	.पढ़ो = w5100_पढ़ो_direct,
	.ग_लिखो = w5100_ग_लिखो_direct,
	.पढ़ो16 = w5100_पढ़ो16_direct,
	.ग_लिखो16 = w5100_ग_लिखो16_direct,
	.पढ़ोbulk = w5100_पढ़ोbulk_direct,
	.ग_लिखोbulk = w5100_ग_लिखोbulk_direct,
	.init = w5100_mmio_init,
पूर्ण;

/*
 * In indirect address mode host प्रणाली indirectly accesses रेजिस्टरs by
 * using Indirect Mode Address Register (IDM_AR) and Indirect Mode Data
 * Register (IDM_DR), which are directly mapped to Memory-Mapped I/O space.
 * Mode Register (MR) is directly accessible.
 *
 * Only 0x04 bytes are required क्रम memory space.
 */
#घोषणा W5100_IDM_AR		0x01   /* Indirect Mode Address Register */
#घोषणा W5100_IDM_DR		0x03   /* Indirect Mode Data Register */

अटल पूर्णांक w5100_पढ़ो_indirect(काष्ठा net_device *ndev, u32 addr)
अणु
	काष्ठा w5100_mmio_priv *mmio_priv = w5100_mmio_priv(ndev);
	अचिन्हित दीर्घ flags;
	u8 data;

	spin_lock_irqsave(&mmio_priv->reg_lock, flags);
	w5100_ग_लिखो16_direct(ndev, W5100_IDM_AR, addr);
	data = w5100_पढ़ो_direct(ndev, W5100_IDM_DR);
	spin_unlock_irqrestore(&mmio_priv->reg_lock, flags);

	वापस data;
पूर्ण

अटल पूर्णांक w5100_ग_लिखो_indirect(काष्ठा net_device *ndev, u32 addr, u8 data)
अणु
	काष्ठा w5100_mmio_priv *mmio_priv = w5100_mmio_priv(ndev);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&mmio_priv->reg_lock, flags);
	w5100_ग_लिखो16_direct(ndev, W5100_IDM_AR, addr);
	w5100_ग_लिखो_direct(ndev, W5100_IDM_DR, data);
	spin_unlock_irqrestore(&mmio_priv->reg_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक w5100_पढ़ो16_indirect(काष्ठा net_device *ndev, u32 addr)
अणु
	काष्ठा w5100_mmio_priv *mmio_priv = w5100_mmio_priv(ndev);
	अचिन्हित दीर्घ flags;
	u16 data;

	spin_lock_irqsave(&mmio_priv->reg_lock, flags);
	w5100_ग_लिखो16_direct(ndev, W5100_IDM_AR, addr);
	data  = w5100_पढ़ो_direct(ndev, W5100_IDM_DR) << 8;
	data |= w5100_पढ़ो_direct(ndev, W5100_IDM_DR);
	spin_unlock_irqrestore(&mmio_priv->reg_lock, flags);

	वापस data;
पूर्ण

अटल पूर्णांक w5100_ग_लिखो16_indirect(काष्ठा net_device *ndev, u32 addr, u16 data)
अणु
	काष्ठा w5100_mmio_priv *mmio_priv = w5100_mmio_priv(ndev);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&mmio_priv->reg_lock, flags);
	w5100_ग_लिखो16_direct(ndev, W5100_IDM_AR, addr);
	__w5100_ग_लिखो_direct(ndev, W5100_IDM_DR, data >> 8);
	w5100_ग_लिखो_direct(ndev, W5100_IDM_DR, data);
	spin_unlock_irqrestore(&mmio_priv->reg_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक w5100_पढ़ोbulk_indirect(काष्ठा net_device *ndev, u32 addr, u8 *buf,
				   पूर्णांक len)
अणु
	काष्ठा w5100_mmio_priv *mmio_priv = w5100_mmio_priv(ndev);
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	spin_lock_irqsave(&mmio_priv->reg_lock, flags);
	w5100_ग_लिखो16_direct(ndev, W5100_IDM_AR, addr);

	क्रम (i = 0; i < len; i++)
		*buf++ = w5100_पढ़ो_direct(ndev, W5100_IDM_DR);

	spin_unlock_irqrestore(&mmio_priv->reg_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक w5100_ग_लिखोbulk_indirect(काष्ठा net_device *ndev, u32 addr,
				    स्थिर u8 *buf, पूर्णांक len)
अणु
	काष्ठा w5100_mmio_priv *mmio_priv = w5100_mmio_priv(ndev);
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	spin_lock_irqsave(&mmio_priv->reg_lock, flags);
	w5100_ग_लिखो16_direct(ndev, W5100_IDM_AR, addr);

	क्रम (i = 0; i < len; i++)
		__w5100_ग_लिखो_direct(ndev, W5100_IDM_DR, *buf++);

	spin_unlock_irqrestore(&mmio_priv->reg_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक w5100_reset_indirect(काष्ठा net_device *ndev)
अणु
	w5100_ग_लिखो_direct(ndev, W5100_MR, MR_RST);
	mdelay(5);
	w5100_ग_लिखो_direct(ndev, W5100_MR, MR_PB | MR_AI | MR_IND);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा w5100_ops w5100_mmio_indirect_ops = अणु
	.chip_id = W5100,
	.पढ़ो = w5100_पढ़ो_indirect,
	.ग_लिखो = w5100_ग_लिखो_indirect,
	.पढ़ो16 = w5100_पढ़ो16_indirect,
	.ग_लिखो16 = w5100_ग_लिखो16_indirect,
	.पढ़ोbulk = w5100_पढ़ोbulk_indirect,
	.ग_लिखोbulk = w5100_ग_लिखोbulk_indirect,
	.init = w5100_mmio_init,
	.reset = w5100_reset_indirect,
पूर्ण;

#अगर defined(CONFIG_WIZNET_BUS_सूचीECT)

अटल पूर्णांक w5100_पढ़ो(काष्ठा w5100_priv *priv, u32 addr)
अणु
	वापस w5100_पढ़ो_direct(priv->ndev, addr);
पूर्ण

अटल पूर्णांक w5100_ग_लिखो(काष्ठा w5100_priv *priv, u32 addr, u8 data)
अणु
	वापस w5100_ग_लिखो_direct(priv->ndev, addr, data);
पूर्ण

अटल पूर्णांक w5100_पढ़ो16(काष्ठा w5100_priv *priv, u32 addr)
अणु
	वापस w5100_पढ़ो16_direct(priv->ndev, addr);
पूर्ण

अटल पूर्णांक w5100_ग_लिखो16(काष्ठा w5100_priv *priv, u32 addr, u16 data)
अणु
	वापस w5100_ग_लिखो16_direct(priv->ndev, addr, data);
पूर्ण

अटल पूर्णांक w5100_पढ़ोbulk(काष्ठा w5100_priv *priv, u32 addr, u8 *buf, पूर्णांक len)
अणु
	वापस w5100_पढ़ोbulk_direct(priv->ndev, addr, buf, len);
पूर्ण

अटल पूर्णांक w5100_ग_लिखोbulk(काष्ठा w5100_priv *priv, u32 addr, स्थिर u8 *buf,
			   पूर्णांक len)
अणु
	वापस w5100_ग_लिखोbulk_direct(priv->ndev, addr, buf, len);
पूर्ण

#या_अगर defined(CONFIG_WIZNET_BUS_INसूचीECT)

अटल पूर्णांक w5100_पढ़ो(काष्ठा w5100_priv *priv, u32 addr)
अणु
	वापस w5100_पढ़ो_indirect(priv->ndev, addr);
पूर्ण

अटल पूर्णांक w5100_ग_लिखो(काष्ठा w5100_priv *priv, u32 addr, u8 data)
अणु
	वापस w5100_ग_लिखो_indirect(priv->ndev, addr, data);
पूर्ण

अटल पूर्णांक w5100_पढ़ो16(काष्ठा w5100_priv *priv, u32 addr)
अणु
	वापस w5100_पढ़ो16_indirect(priv->ndev, addr);
पूर्ण

अटल पूर्णांक w5100_ग_लिखो16(काष्ठा w5100_priv *priv, u32 addr, u16 data)
अणु
	वापस w5100_ग_लिखो16_indirect(priv->ndev, addr, data);
पूर्ण

अटल पूर्णांक w5100_पढ़ोbulk(काष्ठा w5100_priv *priv, u32 addr, u8 *buf, पूर्णांक len)
अणु
	वापस w5100_पढ़ोbulk_indirect(priv->ndev, addr, buf, len);
पूर्ण

अटल पूर्णांक w5100_ग_लिखोbulk(काष्ठा w5100_priv *priv, u32 addr, स्थिर u8 *buf,
			   पूर्णांक len)
अणु
	वापस w5100_ग_लिखोbulk_indirect(priv->ndev, addr, buf, len);
पूर्ण

#अन्यथा /* CONFIG_WIZNET_BUS_ANY */

अटल पूर्णांक w5100_पढ़ो(काष्ठा w5100_priv *priv, u32 addr)
अणु
	वापस priv->ops->पढ़ो(priv->ndev, addr);
पूर्ण

अटल पूर्णांक w5100_ग_लिखो(काष्ठा w5100_priv *priv, u32 addr, u8 data)
अणु
	वापस priv->ops->ग_लिखो(priv->ndev, addr, data);
पूर्ण

अटल पूर्णांक w5100_पढ़ो16(काष्ठा w5100_priv *priv, u32 addr)
अणु
	वापस priv->ops->पढ़ो16(priv->ndev, addr);
पूर्ण

अटल पूर्णांक w5100_ग_लिखो16(काष्ठा w5100_priv *priv, u32 addr, u16 data)
अणु
	वापस priv->ops->ग_लिखो16(priv->ndev, addr, data);
पूर्ण

अटल पूर्णांक w5100_पढ़ोbulk(काष्ठा w5100_priv *priv, u32 addr, u8 *buf, पूर्णांक len)
अणु
	वापस priv->ops->पढ़ोbulk(priv->ndev, addr, buf, len);
पूर्ण

अटल पूर्णांक w5100_ग_लिखोbulk(काष्ठा w5100_priv *priv, u32 addr, स्थिर u8 *buf,
			   पूर्णांक len)
अणु
	वापस priv->ops->ग_लिखोbulk(priv->ndev, addr, buf, len);
पूर्ण

#पूर्ण_अगर

अटल पूर्णांक w5100_पढ़ोbuf(काष्ठा w5100_priv *priv, u16 offset, u8 *buf, पूर्णांक len)
अणु
	u32 addr;
	पूर्णांक reमुख्य = 0;
	पूर्णांक ret;
	स्थिर u32 mem_start = priv->s0_rx_buf;
	स्थिर u16 mem_size = priv->s0_rx_buf_size;

	offset %= mem_size;
	addr = mem_start + offset;

	अगर (offset + len > mem_size) अणु
		reमुख्य = (offset + len) % mem_size;
		len = mem_size - offset;
	पूर्ण

	ret = w5100_पढ़ोbulk(priv, addr, buf, len);
	अगर (ret || !reमुख्य)
		वापस ret;

	वापस w5100_पढ़ोbulk(priv, mem_start, buf + len, reमुख्य);
पूर्ण

अटल पूर्णांक w5100_ग_लिखोbuf(काष्ठा w5100_priv *priv, u16 offset, स्थिर u8 *buf,
			  पूर्णांक len)
अणु
	u32 addr;
	पूर्णांक ret;
	पूर्णांक reमुख्य = 0;
	स्थिर u32 mem_start = priv->s0_tx_buf;
	स्थिर u16 mem_size = priv->s0_tx_buf_size;

	offset %= mem_size;
	addr = mem_start + offset;

	अगर (offset + len > mem_size) अणु
		reमुख्य = (offset + len) % mem_size;
		len = mem_size - offset;
	पूर्ण

	ret = w5100_ग_लिखोbulk(priv, addr, buf, len);
	अगर (ret || !reमुख्य)
		वापस ret;

	वापस w5100_ग_लिखोbulk(priv, mem_start, buf + len, reमुख्य);
पूर्ण

अटल पूर्णांक w5100_reset(काष्ठा w5100_priv *priv)
अणु
	अगर (priv->ops->reset)
		वापस priv->ops->reset(priv->ndev);

	w5100_ग_लिखो(priv, W5100_MR, MR_RST);
	mdelay(5);
	w5100_ग_लिखो(priv, W5100_MR, MR_PB);

	वापस 0;
पूर्ण

अटल पूर्णांक w5100_command(काष्ठा w5100_priv *priv, u16 cmd)
अणु
	अचिन्हित दीर्घ समयout;

	w5100_ग_लिखो(priv, W5100_S0_CR(priv), cmd);

	समयout = jअगरfies + msecs_to_jअगरfies(100);

	जबतक (w5100_पढ़ो(priv, W5100_S0_CR(priv)) != 0) अणु
		अगर (समय_after(jअगरfies, समयout))
			वापस -EIO;
		cpu_relax();
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम w5100_ग_लिखो_macaddr(काष्ठा w5100_priv *priv)
अणु
	काष्ठा net_device *ndev = priv->ndev;

	w5100_ग_लिखोbulk(priv, W5100_SHAR, ndev->dev_addr, ETH_ALEN);
पूर्ण

अटल व्योम w5100_socket_पूर्णांकr_mask(काष्ठा w5100_priv *priv, u8 mask)
अणु
	u32 imr;

	अगर (priv->ops->chip_id == W5500)
		imr = W5500_SIMR;
	अन्यथा
		imr = W5100_IMR;

	w5100_ग_लिखो(priv, imr, mask);
पूर्ण

अटल व्योम w5100_enable_पूर्णांकr(काष्ठा w5100_priv *priv)
अणु
	w5100_socket_पूर्णांकr_mask(priv, IR_S0);
पूर्ण

अटल व्योम w5100_disable_पूर्णांकr(काष्ठा w5100_priv *priv)
अणु
	w5100_socket_पूर्णांकr_mask(priv, 0);
पूर्ण

अटल व्योम w5100_memory_configure(काष्ठा w5100_priv *priv)
अणु
	/* Configure 16K of पूर्णांकernal memory
	 * as 8K RX buffer and 8K TX buffer
	 */
	w5100_ग_लिखो(priv, W5100_RMSR, 0x03);
	w5100_ग_लिखो(priv, W5100_TMSR, 0x03);
पूर्ण

अटल व्योम w5200_memory_configure(काष्ठा w5100_priv *priv)
अणु
	पूर्णांक i;

	/* Configure पूर्णांकernal RX memory as 16K RX buffer and
	 * पूर्णांकernal TX memory as 16K TX buffer
	 */
	w5100_ग_लिखो(priv, W5200_Sn_RXMEM_SIZE(0), 0x10);
	w5100_ग_लिखो(priv, W5200_Sn_TXMEM_SIZE(0), 0x10);

	क्रम (i = 1; i < 8; i++) अणु
		w5100_ग_लिखो(priv, W5200_Sn_RXMEM_SIZE(i), 0);
		w5100_ग_लिखो(priv, W5200_Sn_TXMEM_SIZE(i), 0);
	पूर्ण
पूर्ण

अटल व्योम w5500_memory_configure(काष्ठा w5100_priv *priv)
अणु
	पूर्णांक i;

	/* Configure पूर्णांकernal RX memory as 16K RX buffer and
	 * पूर्णांकernal TX memory as 16K TX buffer
	 */
	w5100_ग_लिखो(priv, W5500_Sn_RXMEM_SIZE(0), 0x10);
	w5100_ग_लिखो(priv, W5500_Sn_TXMEM_SIZE(0), 0x10);

	क्रम (i = 1; i < 8; i++) अणु
		w5100_ग_लिखो(priv, W5500_Sn_RXMEM_SIZE(i), 0);
		w5100_ग_लिखो(priv, W5500_Sn_TXMEM_SIZE(i), 0);
	पूर्ण
पूर्ण

अटल पूर्णांक w5100_hw_reset(काष्ठा w5100_priv *priv)
अणु
	u32 rtr;

	w5100_reset(priv);

	w5100_disable_पूर्णांकr(priv);
	w5100_ग_लिखो_macaddr(priv);

	चयन (priv->ops->chip_id) अणु
	हाल W5100:
		w5100_memory_configure(priv);
		rtr = W5100_RTR;
		अवरोध;
	हाल W5200:
		w5200_memory_configure(priv);
		rtr = W5100_RTR;
		अवरोध;
	हाल W5500:
		w5500_memory_configure(priv);
		rtr = W5500_RTR;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (w5100_पढ़ो16(priv, rtr) != RTR_DEFAULT)
		वापस -ENODEV;

	वापस 0;
पूर्ण

अटल व्योम w5100_hw_start(काष्ठा w5100_priv *priv)
अणु
	u8 mode = S0_MR_MACRAW;

	अगर (!priv->promisc) अणु
		अगर (priv->ops->chip_id == W5500)
			mode |= W5500_S0_MR_MF;
		अन्यथा
			mode |= S0_MR_MF;
	पूर्ण

	w5100_ग_लिखो(priv, W5100_S0_MR(priv), mode);
	w5100_command(priv, S0_CR_OPEN);
	w5100_enable_पूर्णांकr(priv);
पूर्ण

अटल व्योम w5100_hw_बंद(काष्ठा w5100_priv *priv)
अणु
	w5100_disable_पूर्णांकr(priv);
	w5100_command(priv, S0_CR_CLOSE);
पूर्ण

/***********************************************************************
 *
 *   Device driver functions / callbacks
 *
 ***********************************************************************/

अटल व्योम w5100_get_drvinfo(काष्ठा net_device *ndev,
			      काष्ठा ethtool_drvinfo *info)
अणु
	strlcpy(info->driver, DRV_NAME, माप(info->driver));
	strlcpy(info->version, DRV_VERSION, माप(info->version));
	strlcpy(info->bus_info, dev_name(ndev->dev.parent),
		माप(info->bus_info));
पूर्ण

अटल u32 w5100_get_link(काष्ठा net_device *ndev)
अणु
	काष्ठा w5100_priv *priv = netdev_priv(ndev);

	अगर (gpio_is_valid(priv->link_gpio))
		वापस !!gpio_get_value(priv->link_gpio);

	वापस 1;
पूर्ण

अटल u32 w5100_get_msglevel(काष्ठा net_device *ndev)
अणु
	काष्ठा w5100_priv *priv = netdev_priv(ndev);

	वापस priv->msg_enable;
पूर्ण

अटल व्योम w5100_set_msglevel(काष्ठा net_device *ndev, u32 value)
अणु
	काष्ठा w5100_priv *priv = netdev_priv(ndev);

	priv->msg_enable = value;
पूर्ण

अटल पूर्णांक w5100_get_regs_len(काष्ठा net_device *ndev)
अणु
	वापस W5100_COMMON_REGS_LEN + W5100_S0_REGS_LEN;
पूर्ण

अटल व्योम w5100_get_regs(काष्ठा net_device *ndev,
			   काष्ठा ethtool_regs *regs, व्योम *buf)
अणु
	काष्ठा w5100_priv *priv = netdev_priv(ndev);

	regs->version = 1;
	w5100_पढ़ोbulk(priv, W5100_COMMON_REGS, buf, W5100_COMMON_REGS_LEN);
	buf += W5100_COMMON_REGS_LEN;
	w5100_पढ़ोbulk(priv, S0_REGS(priv), buf, W5100_S0_REGS_LEN);
पूर्ण

अटल व्योम w5100_restart(काष्ठा net_device *ndev)
अणु
	काष्ठा w5100_priv *priv = netdev_priv(ndev);

	netअगर_stop_queue(ndev);
	w5100_hw_reset(priv);
	w5100_hw_start(priv);
	ndev->stats.tx_errors++;
	netअगर_trans_update(ndev);
	netअगर_wake_queue(ndev);
पूर्ण

अटल व्योम w5100_restart_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा w5100_priv *priv = container_of(work, काष्ठा w5100_priv,
					       restart_work);

	w5100_restart(priv->ndev);
पूर्ण

अटल व्योम w5100_tx_समयout(काष्ठा net_device *ndev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा w5100_priv *priv = netdev_priv(ndev);

	अगर (priv->ops->may_sleep)
		schedule_work(&priv->restart_work);
	अन्यथा
		w5100_restart(ndev);
पूर्ण

अटल व्योम w5100_tx_skb(काष्ठा net_device *ndev, काष्ठा sk_buff *skb)
अणु
	काष्ठा w5100_priv *priv = netdev_priv(ndev);
	u16 offset;

	offset = w5100_पढ़ो16(priv, W5100_S0_TX_WR(priv));
	w5100_ग_लिखोbuf(priv, offset, skb->data, skb->len);
	w5100_ग_लिखो16(priv, W5100_S0_TX_WR(priv), offset + skb->len);
	ndev->stats.tx_bytes += skb->len;
	ndev->stats.tx_packets++;
	dev_kमुक्त_skb(skb);

	w5100_command(priv, S0_CR_SEND);
पूर्ण

अटल व्योम w5100_tx_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा w5100_priv *priv = container_of(work, काष्ठा w5100_priv,
					       tx_work);
	काष्ठा sk_buff *skb = priv->tx_skb;

	priv->tx_skb = शून्य;

	अगर (WARN_ON(!skb))
		वापस;
	w5100_tx_skb(priv->ndev, skb);
पूर्ण

अटल netdev_tx_t w5100_start_tx(काष्ठा sk_buff *skb, काष्ठा net_device *ndev)
अणु
	काष्ठा w5100_priv *priv = netdev_priv(ndev);

	netअगर_stop_queue(ndev);

	अगर (priv->ops->may_sleep) अणु
		WARN_ON(priv->tx_skb);
		priv->tx_skb = skb;
		queue_work(priv->xfer_wq, &priv->tx_work);
	पूर्ण अन्यथा अणु
		w5100_tx_skb(ndev, skb);
	पूर्ण

	वापस NETDEV_TX_OK;
पूर्ण

अटल काष्ठा sk_buff *w5100_rx_skb(काष्ठा net_device *ndev)
अणु
	काष्ठा w5100_priv *priv = netdev_priv(ndev);
	काष्ठा sk_buff *skb;
	u16 rx_len;
	u16 offset;
	u8 header[2];
	u16 rx_buf_len = w5100_पढ़ो16(priv, W5100_S0_RX_RSR(priv));

	अगर (rx_buf_len == 0)
		वापस शून्य;

	offset = w5100_पढ़ो16(priv, W5100_S0_RX_RD(priv));
	w5100_पढ़ोbuf(priv, offset, header, 2);
	rx_len = get_unaligned_be16(header) - 2;

	skb = netdev_alloc_skb_ip_align(ndev, rx_len);
	अगर (unlikely(!skb)) अणु
		w5100_ग_लिखो16(priv, W5100_S0_RX_RD(priv), offset + rx_buf_len);
		w5100_command(priv, S0_CR_RECV);
		ndev->stats.rx_dropped++;
		वापस शून्य;
	पूर्ण

	skb_put(skb, rx_len);
	w5100_पढ़ोbuf(priv, offset + 2, skb->data, rx_len);
	w5100_ग_लिखो16(priv, W5100_S0_RX_RD(priv), offset + 2 + rx_len);
	w5100_command(priv, S0_CR_RECV);
	skb->protocol = eth_type_trans(skb, ndev);

	ndev->stats.rx_packets++;
	ndev->stats.rx_bytes += rx_len;

	वापस skb;
पूर्ण

अटल व्योम w5100_rx_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा w5100_priv *priv = container_of(work, काष्ठा w5100_priv,
					       rx_work);
	काष्ठा sk_buff *skb;

	जबतक ((skb = w5100_rx_skb(priv->ndev)))
		netअगर_rx_ni(skb);

	w5100_enable_पूर्णांकr(priv);
पूर्ण

अटल पूर्णांक w5100_napi_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा w5100_priv *priv = container_of(napi, काष्ठा w5100_priv, napi);
	पूर्णांक rx_count;

	क्रम (rx_count = 0; rx_count < budget; rx_count++) अणु
		काष्ठा sk_buff *skb = w5100_rx_skb(priv->ndev);

		अगर (skb)
			netअगर_receive_skb(skb);
		अन्यथा
			अवरोध;
	पूर्ण

	अगर (rx_count < budget) अणु
		napi_complete_करोne(napi, rx_count);
		w5100_enable_पूर्णांकr(priv);
	पूर्ण

	वापस rx_count;
पूर्ण

अटल irqवापस_t w5100_पूर्णांकerrupt(पूर्णांक irq, व्योम *ndev_instance)
अणु
	काष्ठा net_device *ndev = ndev_instance;
	काष्ठा w5100_priv *priv = netdev_priv(ndev);

	पूर्णांक ir = w5100_पढ़ो(priv, W5100_S0_IR(priv));
	अगर (!ir)
		वापस IRQ_NONE;
	w5100_ग_लिखो(priv, W5100_S0_IR(priv), ir);

	अगर (ir & S0_IR_SENDOK) अणु
		netअगर_dbg(priv, tx_करोne, ndev, "tx done\n");
		netअगर_wake_queue(ndev);
	पूर्ण

	अगर (ir & S0_IR_RECV) अणु
		w5100_disable_पूर्णांकr(priv);

		अगर (priv->ops->may_sleep)
			queue_work(priv->xfer_wq, &priv->rx_work);
		अन्यथा अगर (napi_schedule_prep(&priv->napi))
			__napi_schedule(&priv->napi);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t w5100_detect_link(पूर्णांक irq, व्योम *ndev_instance)
अणु
	काष्ठा net_device *ndev = ndev_instance;
	काष्ठा w5100_priv *priv = netdev_priv(ndev);

	अगर (netअगर_running(ndev)) अणु
		अगर (gpio_get_value(priv->link_gpio) != 0) अणु
			netअगर_info(priv, link, ndev, "link is up\n");
			netअगर_carrier_on(ndev);
		पूर्ण अन्यथा अणु
			netअगर_info(priv, link, ndev, "link is down\n");
			netअगर_carrier_off(ndev);
		पूर्ण
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम w5100_setrx_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा w5100_priv *priv = container_of(work, काष्ठा w5100_priv,
					       setrx_work);

	w5100_hw_start(priv);
पूर्ण

अटल व्योम w5100_set_rx_mode(काष्ठा net_device *ndev)
अणु
	काष्ठा w5100_priv *priv = netdev_priv(ndev);
	bool set_promisc = (ndev->flags & IFF_PROMISC) != 0;

	अगर (priv->promisc != set_promisc) अणु
		priv->promisc = set_promisc;

		अगर (priv->ops->may_sleep)
			schedule_work(&priv->setrx_work);
		अन्यथा
			w5100_hw_start(priv);
	पूर्ण
पूर्ण

अटल पूर्णांक w5100_set_macaddr(काष्ठा net_device *ndev, व्योम *addr)
अणु
	काष्ठा w5100_priv *priv = netdev_priv(ndev);
	काष्ठा sockaddr *sock_addr = addr;

	अगर (!is_valid_ether_addr(sock_addr->sa_data))
		वापस -EADDRNOTAVAIL;
	स_नकल(ndev->dev_addr, sock_addr->sa_data, ETH_ALEN);
	w5100_ग_लिखो_macaddr(priv);
	वापस 0;
पूर्ण

अटल पूर्णांक w5100_खोलो(काष्ठा net_device *ndev)
अणु
	काष्ठा w5100_priv *priv = netdev_priv(ndev);

	netअगर_info(priv, अगरup, ndev, "enabling\n");
	w5100_hw_start(priv);
	napi_enable(&priv->napi);
	netअगर_start_queue(ndev);
	अगर (!gpio_is_valid(priv->link_gpio) ||
	    gpio_get_value(priv->link_gpio) != 0)
		netअगर_carrier_on(ndev);
	वापस 0;
पूर्ण

अटल पूर्णांक w5100_stop(काष्ठा net_device *ndev)
अणु
	काष्ठा w5100_priv *priv = netdev_priv(ndev);

	netअगर_info(priv, अगरकरोwn, ndev, "shutting down\n");
	w5100_hw_बंद(priv);
	netअगर_carrier_off(ndev);
	netअगर_stop_queue(ndev);
	napi_disable(&priv->napi);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops w5100_ethtool_ops = अणु
	.get_drvinfo		= w5100_get_drvinfo,
	.get_msglevel		= w5100_get_msglevel,
	.set_msglevel		= w5100_set_msglevel,
	.get_link		= w5100_get_link,
	.get_regs_len		= w5100_get_regs_len,
	.get_regs		= w5100_get_regs,
पूर्ण;

अटल स्थिर काष्ठा net_device_ops w5100_netdev_ops = अणु
	.nकरो_खोलो		= w5100_खोलो,
	.nकरो_stop		= w5100_stop,
	.nकरो_start_xmit		= w5100_start_tx,
	.nकरो_tx_समयout		= w5100_tx_समयout,
	.nकरो_set_rx_mode	= w5100_set_rx_mode,
	.nकरो_set_mac_address	= w5100_set_macaddr,
	.nकरो_validate_addr	= eth_validate_addr,
पूर्ण;

अटल पूर्णांक w5100_mmio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा wiznet_platक्रमm_data *data = dev_get_platdata(&pdev->dev);
	स्थिर व्योम *mac_addr = शून्य;
	काष्ठा resource *mem;
	स्थिर काष्ठा w5100_ops *ops;
	पूर्णांक irq;

	अगर (data && is_valid_ether_addr(data->mac_addr))
		mac_addr = data->mac_addr;

	mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (resource_size(mem) < W5100_BUS_सूचीECT_SIZE)
		ops = &w5100_mmio_indirect_ops;
	अन्यथा
		ops = &w5100_mmio_direct_ops;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	वापस w5100_probe(&pdev->dev, ops, माप(काष्ठा w5100_mmio_priv),
			   mac_addr, irq, data ? data->link_gpio : -EINVAL);
पूर्ण

अटल पूर्णांक w5100_mmio_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	वापस w5100_हटाओ(&pdev->dev);
पूर्ण

व्योम *w5100_ops_priv(स्थिर काष्ठा net_device *ndev)
अणु
	वापस netdev_priv(ndev) +
	       ALIGN(माप(काष्ठा w5100_priv), NETDEV_ALIGN);
पूर्ण
EXPORT_SYMBOL_GPL(w5100_ops_priv);

पूर्णांक w5100_probe(काष्ठा device *dev, स्थिर काष्ठा w5100_ops *ops,
		पूर्णांक माप_ops_priv, स्थिर व्योम *mac_addr, पूर्णांक irq,
		पूर्णांक link_gpio)
अणु
	काष्ठा w5100_priv *priv;
	काष्ठा net_device *ndev;
	पूर्णांक err;
	माप_प्रकार alloc_size;

	alloc_size = माप(*priv);
	अगर (माप_ops_priv) अणु
		alloc_size = ALIGN(alloc_size, NETDEV_ALIGN);
		alloc_size += माप_ops_priv;
	पूर्ण
	alloc_size += NETDEV_ALIGN - 1;

	ndev = alloc_etherdev(alloc_size);
	अगर (!ndev)
		वापस -ENOMEM;
	SET_NETDEV_DEV(ndev, dev);
	dev_set_drvdata(dev, ndev);
	priv = netdev_priv(ndev);

	चयन (ops->chip_id) अणु
	हाल W5100:
		priv->s0_regs = W5100_S0_REGS;
		priv->s0_tx_buf = W5100_TX_MEM_START;
		priv->s0_tx_buf_size = W5100_TX_MEM_SIZE;
		priv->s0_rx_buf = W5100_RX_MEM_START;
		priv->s0_rx_buf_size = W5100_RX_MEM_SIZE;
		अवरोध;
	हाल W5200:
		priv->s0_regs = W5200_S0_REGS;
		priv->s0_tx_buf = W5200_TX_MEM_START;
		priv->s0_tx_buf_size = W5200_TX_MEM_SIZE;
		priv->s0_rx_buf = W5200_RX_MEM_START;
		priv->s0_rx_buf_size = W5200_RX_MEM_SIZE;
		अवरोध;
	हाल W5500:
		priv->s0_regs = W5500_S0_REGS;
		priv->s0_tx_buf = W5500_TX_MEM_START;
		priv->s0_tx_buf_size = W5500_TX_MEM_SIZE;
		priv->s0_rx_buf = W5500_RX_MEM_START;
		priv->s0_rx_buf_size = W5500_RX_MEM_SIZE;
		अवरोध;
	शेष:
		err = -EINVAL;
		जाओ err_रेजिस्टर;
	पूर्ण

	priv->ndev = ndev;
	priv->ops = ops;
	priv->irq = irq;
	priv->link_gpio = link_gpio;

	ndev->netdev_ops = &w5100_netdev_ops;
	ndev->ethtool_ops = &w5100_ethtool_ops;
	netअगर_napi_add(ndev, &priv->napi, w5100_napi_poll, 16);

	/* This chip करोesn't support VLAN packets with normal MTU,
	 * so disable VLAN क्रम this device.
	 */
	ndev->features |= NETIF_F_VLAN_CHALLENGED;

	err = रेजिस्टर_netdev(ndev);
	अगर (err < 0)
		जाओ err_रेजिस्टर;

	priv->xfer_wq = alloc_workqueue("%s", WQ_MEM_RECLAIM, 0,
					netdev_name(ndev));
	अगर (!priv->xfer_wq) अणु
		err = -ENOMEM;
		जाओ err_wq;
	पूर्ण

	INIT_WORK(&priv->rx_work, w5100_rx_work);
	INIT_WORK(&priv->tx_work, w5100_tx_work);
	INIT_WORK(&priv->setrx_work, w5100_setrx_work);
	INIT_WORK(&priv->restart_work, w5100_restart_work);

	अगर (mac_addr)
		स_नकल(ndev->dev_addr, mac_addr, ETH_ALEN);
	अन्यथा
		eth_hw_addr_अक्रमom(ndev);

	अगर (priv->ops->init) अणु
		err = priv->ops->init(priv->ndev);
		अगर (err)
			जाओ err_hw;
	पूर्ण

	err = w5100_hw_reset(priv);
	अगर (err)
		जाओ err_hw;

	अगर (ops->may_sleep) अणु
		err = request_thपढ़ोed_irq(priv->irq, शून्य, w5100_पूर्णांकerrupt,
					   IRQF_TRIGGER_LOW | IRQF_ONESHOT,
					   netdev_name(ndev), ndev);
	पूर्ण अन्यथा अणु
		err = request_irq(priv->irq, w5100_पूर्णांकerrupt,
				  IRQF_TRIGGER_LOW, netdev_name(ndev), ndev);
	पूर्ण
	अगर (err)
		जाओ err_hw;

	अगर (gpio_is_valid(priv->link_gpio)) अणु
		अक्षर *link_name = devm_kzalloc(dev, 16, GFP_KERNEL);

		अगर (!link_name) अणु
			err = -ENOMEM;
			जाओ err_gpio;
		पूर्ण
		snम_लिखो(link_name, 16, "%s-link", netdev_name(ndev));
		priv->link_irq = gpio_to_irq(priv->link_gpio);
		अगर (request_any_context_irq(priv->link_irq, w5100_detect_link,
					    IRQF_TRIGGER_RISING |
					    IRQF_TRIGGER_FALLING,
					    link_name, priv->ndev) < 0)
			priv->link_gpio = -EINVAL;
	पूर्ण

	वापस 0;

err_gpio:
	मुक्त_irq(priv->irq, ndev);
err_hw:
	destroy_workqueue(priv->xfer_wq);
err_wq:
	unरेजिस्टर_netdev(ndev);
err_रेजिस्टर:
	मुक्त_netdev(ndev);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(w5100_probe);

पूर्णांक w5100_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा net_device *ndev = dev_get_drvdata(dev);
	काष्ठा w5100_priv *priv = netdev_priv(ndev);

	w5100_hw_reset(priv);
	मुक्त_irq(priv->irq, ndev);
	अगर (gpio_is_valid(priv->link_gpio))
		मुक्त_irq(priv->link_irq, ndev);

	flush_work(&priv->setrx_work);
	flush_work(&priv->restart_work);
	destroy_workqueue(priv->xfer_wq);

	unरेजिस्टर_netdev(ndev);
	मुक्त_netdev(ndev);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(w5100_हटाओ);

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक w5100_suspend(काष्ठा device *dev)
अणु
	काष्ठा net_device *ndev = dev_get_drvdata(dev);
	काष्ठा w5100_priv *priv = netdev_priv(ndev);

	अगर (netअगर_running(ndev)) अणु
		netअगर_carrier_off(ndev);
		netअगर_device_detach(ndev);

		w5100_hw_बंद(priv);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक w5100_resume(काष्ठा device *dev)
अणु
	काष्ठा net_device *ndev = dev_get_drvdata(dev);
	काष्ठा w5100_priv *priv = netdev_priv(ndev);

	अगर (netअगर_running(ndev)) अणु
		w5100_hw_reset(priv);
		w5100_hw_start(priv);

		netअगर_device_attach(ndev);
		अगर (!gpio_is_valid(priv->link_gpio) ||
		    gpio_get_value(priv->link_gpio) != 0)
			netअगर_carrier_on(ndev);
	पूर्ण
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

SIMPLE_DEV_PM_OPS(w5100_pm_ops, w5100_suspend, w5100_resume);
EXPORT_SYMBOL_GPL(w5100_pm_ops);

अटल काष्ठा platक्रमm_driver w5100_mmio_driver = अणु
	.driver		= अणु
		.name	= DRV_NAME,
		.pm	= &w5100_pm_ops,
	पूर्ण,
	.probe		= w5100_mmio_probe,
	.हटाओ		= w5100_mmio_हटाओ,
पूर्ण;
module_platक्रमm_driver(w5100_mmio_driver);
