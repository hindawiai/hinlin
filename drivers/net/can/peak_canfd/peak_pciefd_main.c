<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (C) 2007, 2011 Wolfgang Gअक्रमegger <wg@gअक्रमegger.com>
 * Copyright (C) 2012 Stephane Grosjean <s.grosjean@peak-प्रणाली.com>
 *
 * Derived from the PCAN project file driver/src/pcan_pci.c:
 *
 * Copyright (C) 2001-2006  PEAK System-Technik GmbH
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/delay.h>
#समावेश <linux/pci.h>
#समावेश <linux/पन.स>
#समावेश <linux/can.h>
#समावेश <linux/can/dev.h>

#समावेश "peak_canfd_user.h"

MODULE_AUTHOR("Stephane Grosjean <s.grosjean@peak-system.com>");
MODULE_DESCRIPTION("Socket-CAN driver for PEAK PCAN PCIe/M.2 FD family cards");
MODULE_LICENSE("GPL v2");

#घोषणा PCIEFD_DRV_NAME		"peak_pciefd"

#घोषणा PEAK_PCI_VENDOR_ID	0x001c	/* The PCI device and venकरोr IDs */
#घोषणा PEAK_PCIEFD_ID		0x0013	/* क्रम PCIe slot cards */
#घोषणा PCAN_CPCIEFD_ID		0x0014	/* क्रम Compact-PCI Serial slot cards */
#घोषणा PCAN_PCIE104FD_ID	0x0017	/* क्रम PCIe-104 Express slot cards */
#घोषणा PCAN_MINIPCIEFD_ID      0x0018	/* क्रम mini-PCIe slot cards */
#घोषणा PCAN_PCIEFD_OEM_ID      0x0019	/* क्रम PCIe slot OEM cards */
#घोषणा PCAN_M2_ID		0x001a	/* क्रम M2 slot cards */

/* PEAK PCIe board access description */
#घोषणा PCIEFD_BAR0_SIZE		(64 * 1024)
#घोषणा PCIEFD_RX_DMA_SIZE		(4 * 1024)
#घोषणा PCIEFD_TX_DMA_SIZE		(4 * 1024)

#घोषणा PCIEFD_TX_PAGE_SIZE		(2 * 1024)

/* System Control Registers */
#घोषणा PCIEFD_REG_SYS_CTL_SET		0x0000	/* set bits */
#घोषणा PCIEFD_REG_SYS_CTL_CLR		0x0004	/* clear bits */

/* Version info रेजिस्टरs */
#घोषणा PCIEFD_REG_SYS_VER1		0x0040	/* version reg #1 */
#घोषणा PCIEFD_REG_SYS_VER2		0x0044	/* version reg #2 */

#घोषणा PCIEFD_FW_VERSION(x, y, z)	(((u32)(x) << 24) | \
					 ((u32)(y) << 16) | \
					 ((u32)(z) << 8))

/* System Control Registers Bits */
#घोषणा PCIEFD_SYS_CTL_TS_RST		0x00000001	/* बारtamp घड़ी */
#घोषणा PCIEFD_SYS_CTL_CLK_EN		0x00000002	/* प्रणाली घड़ी */

/* CAN-FD channel addresses */
#घोषणा PCIEFD_CANX_OFF(c)		(((c) + 1) * 0x1000)

#घोषणा PCIEFD_ECHO_SKB_MAX		PCANFD_ECHO_SKB_DEF

/* CAN-FD channel रेजिस्टरs */
#घोषणा PCIEFD_REG_CAN_MISC		0x0000	/* Misc. control */
#घोषणा PCIEFD_REG_CAN_CLK_SEL		0x0008	/* Clock selector */
#घोषणा PCIEFD_REG_CAN_CMD_PORT_L	0x0010	/* 64-bits command port */
#घोषणा PCIEFD_REG_CAN_CMD_PORT_H	0x0014
#घोषणा PCIEFD_REG_CAN_TX_REQ_ACC	0x0020	/* Tx request accumulator */
#घोषणा PCIEFD_REG_CAN_TX_CTL_SET	0x0030	/* Tx control set रेजिस्टर */
#घोषणा PCIEFD_REG_CAN_TX_CTL_CLR	0x0038	/* Tx control clear रेजिस्टर */
#घोषणा PCIEFD_REG_CAN_TX_DMA_ADDR_L	0x0040	/* 64-bits addr क्रम Tx DMA */
#घोषणा PCIEFD_REG_CAN_TX_DMA_ADDR_H	0x0044
#घोषणा PCIEFD_REG_CAN_RX_CTL_SET	0x0050	/* Rx control set रेजिस्टर */
#घोषणा PCIEFD_REG_CAN_RX_CTL_CLR	0x0058	/* Rx control clear रेजिस्टर */
#घोषणा PCIEFD_REG_CAN_RX_CTL_WRT	0x0060	/* Rx control ग_लिखो रेजिस्टर */
#घोषणा PCIEFD_REG_CAN_RX_CTL_ACK	0x0068	/* Rx control ACK रेजिस्टर */
#घोषणा PCIEFD_REG_CAN_RX_DMA_ADDR_L	0x0070	/* 64-bits addr क्रम Rx DMA */
#घोषणा PCIEFD_REG_CAN_RX_DMA_ADDR_H	0x0074

/* CAN-FD channel misc रेजिस्टर bits */
#घोषणा CANFD_MISC_TS_RST		0x00000001	/* बारtamp cnt rst */

/* CAN-FD channel Clock SELector Source & DIVider */
#घोषणा CANFD_CLK_SEL_DIV_MASK		0x00000007
#घोषणा CANFD_CLK_SEL_DIV_60MHZ		0x00000000	/* SRC=240MHz only */
#घोषणा CANFD_CLK_SEL_DIV_40MHZ		0x00000001	/* SRC=240MHz only */
#घोषणा CANFD_CLK_SEL_DIV_30MHZ		0x00000002	/* SRC=240MHz only */
#घोषणा CANFD_CLK_SEL_DIV_24MHZ		0x00000003	/* SRC=240MHz only */
#घोषणा CANFD_CLK_SEL_DIV_20MHZ		0x00000004	/* SRC=240MHz only */

#घोषणा CANFD_CLK_SEL_SRC_MASK		0x00000008	/* 0=80MHz, 1=240MHz */
#घोषणा CANFD_CLK_SEL_SRC_240MHZ	0x00000008
#घोषणा CANFD_CLK_SEL_SRC_80MHZ		(~CANFD_CLK_SEL_SRC_240MHZ & \
							CANFD_CLK_SEL_SRC_MASK)

#घोषणा CANFD_CLK_SEL_20MHZ		(CANFD_CLK_SEL_SRC_240MHZ |\
						CANFD_CLK_SEL_DIV_20MHZ)
#घोषणा CANFD_CLK_SEL_24MHZ		(CANFD_CLK_SEL_SRC_240MHZ |\
						CANFD_CLK_SEL_DIV_24MHZ)
#घोषणा CANFD_CLK_SEL_30MHZ		(CANFD_CLK_SEL_SRC_240MHZ |\
						CANFD_CLK_SEL_DIV_30MHZ)
#घोषणा CANFD_CLK_SEL_40MHZ		(CANFD_CLK_SEL_SRC_240MHZ |\
						CANFD_CLK_SEL_DIV_40MHZ)
#घोषणा CANFD_CLK_SEL_60MHZ		(CANFD_CLK_SEL_SRC_240MHZ |\
						CANFD_CLK_SEL_DIV_60MHZ)
#घोषणा CANFD_CLK_SEL_80MHZ		(CANFD_CLK_SEL_SRC_80MHZ)

/* CAN-FD channel Rx/Tx control रेजिस्टर bits */
#घोषणा CANFD_CTL_UNC_BIT		0x00010000	/* Uncached DMA mem */
#घोषणा CANFD_CTL_RST_BIT		0x00020000	/* reset DMA action */
#घोषणा CANFD_CTL_IEN_BIT		0x00040000	/* IRQ enable */

/* Rx IRQ Count and Time Limits */
#घोषणा CANFD_CTL_IRQ_CL_DEF	16	/* Rx msg max nb per IRQ in Rx DMA */
#घोषणा CANFD_CTL_IRQ_TL_DEF	10	/* Time beक्रमe IRQ अगर < CL (x100 तगs) */

/* Tx anticipation winकरोw (link logical address should be aligned on 2K
 * boundary)
 */
#घोषणा PCIEFD_TX_PAGE_COUNT	(PCIEFD_TX_DMA_SIZE / PCIEFD_TX_PAGE_SIZE)

#घोषणा CANFD_MSG_LNK_TX	0x1001	/* Tx msgs link */

/* 32-bits IRQ status fields, heading Rx DMA area */
अटल अंतरभूत पूर्णांक pciefd_irq_tag(u32 irq_status)
अणु
	वापस irq_status & 0x0000000f;
पूर्ण

अटल अंतरभूत पूर्णांक pciefd_irq_rx_cnt(u32 irq_status)
अणु
	वापस (irq_status & 0x000007f0) >> 4;
पूर्ण

अटल अंतरभूत पूर्णांक pciefd_irq_is_lnk(u32 irq_status)
अणु
	वापस irq_status & 0x00010000;
पूर्ण

/* Rx record */
काष्ठा pciefd_rx_dma अणु
	__le32 irq_status;
	__le32 sys_समय_low;
	__le32 sys_समय_high;
	काष्ठा pucan_rx_msg msg[];
पूर्ण __packed __aligned(4);

/* Tx Link record */
काष्ठा pciefd_tx_link अणु
	__le16 size;
	__le16 type;
	__le32 laddr_lo;
	__le32 laddr_hi;
पूर्ण __packed __aligned(4);

/* Tx page descriptor */
काष्ठा pciefd_page अणु
	व्योम *vbase;			/* page भव address */
	dma_addr_t lbase;		/* page logical address */
	u32 offset;
	u32 size;
पूर्ण;

/* CAN-FD channel object */
काष्ठा pciefd_board;
काष्ठा pciefd_can अणु
	काष्ठा peak_canfd_priv ucan;	/* must be the first member */
	व्योम __iomem *reg_base;		/* channel config base addr */
	काष्ठा pciefd_board *board;	/* reverse link */

	काष्ठा pucan_command pucan_cmd;	/* command buffer */

	dma_addr_t rx_dma_laddr;	/* DMA भव and logical addr */
	व्योम *rx_dma_vaddr;		/* क्रम Rx and Tx areas */
	dma_addr_t tx_dma_laddr;
	व्योम *tx_dma_vaddr;

	काष्ठा pciefd_page tx_pages[PCIEFD_TX_PAGE_COUNT];
	u16 tx_pages_मुक्त;		/* मुक्त Tx pages counter */
	u16 tx_page_index;		/* current page used क्रम Tx */
	spinlock_t tx_lock;

	u32 irq_status;
	u32 irq_tag;				/* next irq tag */
पूर्ण;

/* PEAK-PCIe FD board object */
काष्ठा pciefd_board अणु
	व्योम __iomem *reg_base;
	काष्ठा pci_dev *pci_dev;
	पूर्णांक can_count;
	spinlock_t cmd_lock;		/* 64-bits cmds must be atomic */
	काष्ठा pciefd_can *can[];	/* array of network devices */
पूर्ण;

/* supported device ids. */
अटल स्थिर काष्ठा pci_device_id peak_pciefd_tbl[] = अणु
	अणुPEAK_PCI_VENDOR_ID, PEAK_PCIEFD_ID, PCI_ANY_ID, PCI_ANY_ID,पूर्ण,
	अणुPEAK_PCI_VENDOR_ID, PCAN_CPCIEFD_ID, PCI_ANY_ID, PCI_ANY_ID,पूर्ण,
	अणुPEAK_PCI_VENDOR_ID, PCAN_PCIE104FD_ID, PCI_ANY_ID, PCI_ANY_ID,पूर्ण,
	अणुPEAK_PCI_VENDOR_ID, PCAN_MINIPCIEFD_ID, PCI_ANY_ID, PCI_ANY_ID,पूर्ण,
	अणुPEAK_PCI_VENDOR_ID, PCAN_PCIEFD_OEM_ID, PCI_ANY_ID, PCI_ANY_ID,पूर्ण,
	अणुPEAK_PCI_VENDOR_ID, PCAN_M2_ID, PCI_ANY_ID, PCI_ANY_ID,पूर्ण,
	अणु0,पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, peak_pciefd_tbl);

/* पढ़ो a 32 bits value from a SYS block रेजिस्टर */
अटल अंतरभूत u32 pciefd_sys_पढ़ोreg(स्थिर काष्ठा pciefd_board *priv, u16 reg)
अणु
	वापस पढ़ोl(priv->reg_base + reg);
पूर्ण

/* ग_लिखो a 32 bits value पूर्णांकo a SYS block रेजिस्टर */
अटल अंतरभूत व्योम pciefd_sys_ग_लिखोreg(स्थिर काष्ठा pciefd_board *priv,
				       u32 val, u16 reg)
अणु
	ग_लिखोl(val, priv->reg_base + reg);
पूर्ण

/* पढ़ो a 32 bits value from CAN-FD block रेजिस्टर */
अटल अंतरभूत u32 pciefd_can_पढ़ोreg(स्थिर काष्ठा pciefd_can *priv, u16 reg)
अणु
	वापस पढ़ोl(priv->reg_base + reg);
पूर्ण

/* ग_लिखो a 32 bits value पूर्णांकo a CAN-FD block रेजिस्टर */
अटल अंतरभूत व्योम pciefd_can_ग_लिखोreg(स्थिर काष्ठा pciefd_can *priv,
				       u32 val, u16 reg)
अणु
	ग_लिखोl(val, priv->reg_base + reg);
पूर्ण

/* give a channel logical Rx DMA address to the board */
अटल व्योम pciefd_can_setup_rx_dma(काष्ठा pciefd_can *priv)
अणु
#अगर_घोषित CONFIG_ARCH_DMA_ADDR_T_64BIT
	स्थिर u32 dma_addr_h = (u32)(priv->rx_dma_laddr >> 32);
#अन्यथा
	स्थिर u32 dma_addr_h = 0;
#पूर्ण_अगर

	/* (DMA must be reset क्रम Rx) */
	pciefd_can_ग_लिखोreg(priv, CANFD_CTL_RST_BIT, PCIEFD_REG_CAN_RX_CTL_SET);

	/* ग_लिखो the logical address of the Rx DMA area क्रम this channel */
	pciefd_can_ग_लिखोreg(priv, (u32)priv->rx_dma_laddr,
			    PCIEFD_REG_CAN_RX_DMA_ADDR_L);
	pciefd_can_ग_लिखोreg(priv, dma_addr_h, PCIEFD_REG_CAN_RX_DMA_ADDR_H);

	/* also indicates that Rx DMA is cacheable */
	pciefd_can_ग_लिखोreg(priv, CANFD_CTL_UNC_BIT, PCIEFD_REG_CAN_RX_CTL_CLR);
पूर्ण

/* clear channel logical Rx DMA address from the board */
अटल व्योम pciefd_can_clear_rx_dma(काष्ठा pciefd_can *priv)
अणु
	/* DMA must be reset क्रम Rx */
	pciefd_can_ग_लिखोreg(priv, CANFD_CTL_RST_BIT, PCIEFD_REG_CAN_RX_CTL_SET);

	/* clear the logical address of the Rx DMA area क्रम this channel */
	pciefd_can_ग_लिखोreg(priv, 0, PCIEFD_REG_CAN_RX_DMA_ADDR_L);
	pciefd_can_ग_लिखोreg(priv, 0, PCIEFD_REG_CAN_RX_DMA_ADDR_H);
पूर्ण

/* give a channel logical Tx DMA address to the board */
अटल व्योम pciefd_can_setup_tx_dma(काष्ठा pciefd_can *priv)
अणु
#अगर_घोषित CONFIG_ARCH_DMA_ADDR_T_64BIT
	स्थिर u32 dma_addr_h = (u32)(priv->tx_dma_laddr >> 32);
#अन्यथा
	स्थिर u32 dma_addr_h = 0;
#पूर्ण_अगर

	/* (DMA must be reset क्रम Tx) */
	pciefd_can_ग_लिखोreg(priv, CANFD_CTL_RST_BIT, PCIEFD_REG_CAN_TX_CTL_SET);

	/* ग_लिखो the logical address of the Tx DMA area क्रम this channel */
	pciefd_can_ग_लिखोreg(priv, (u32)priv->tx_dma_laddr,
			    PCIEFD_REG_CAN_TX_DMA_ADDR_L);
	pciefd_can_ग_लिखोreg(priv, dma_addr_h, PCIEFD_REG_CAN_TX_DMA_ADDR_H);

	/* also indicates that Tx DMA is cacheable */
	pciefd_can_ग_लिखोreg(priv, CANFD_CTL_UNC_BIT, PCIEFD_REG_CAN_TX_CTL_CLR);
पूर्ण

/* clear channel logical Tx DMA address from the board */
अटल व्योम pciefd_can_clear_tx_dma(काष्ठा pciefd_can *priv)
अणु
	/* DMA must be reset क्रम Tx */
	pciefd_can_ग_लिखोreg(priv, CANFD_CTL_RST_BIT, PCIEFD_REG_CAN_TX_CTL_SET);

	/* clear the logical address of the Tx DMA area क्रम this channel */
	pciefd_can_ग_लिखोreg(priv, 0, PCIEFD_REG_CAN_TX_DMA_ADDR_L);
	pciefd_can_ग_लिखोreg(priv, 0, PCIEFD_REG_CAN_TX_DMA_ADDR_H);
पूर्ण

अटल व्योम pciefd_can_ack_rx_dma(काष्ठा pciefd_can *priv)
अणु
	/* पढ़ो value of current IRQ tag and inc it क्रम next one */
	priv->irq_tag = le32_to_cpu(*(__le32 *)priv->rx_dma_vaddr);
	priv->irq_tag++;
	priv->irq_tag &= 0xf;

	/* ग_लिखो the next IRQ tag क्रम this CAN */
	pciefd_can_ग_लिखोreg(priv, priv->irq_tag, PCIEFD_REG_CAN_RX_CTL_ACK);
पूर्ण

/* IRQ handler */
अटल irqवापस_t pciefd_irq_handler(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा pciefd_can *priv = arg;
	काष्ठा pciefd_rx_dma *rx_dma = priv->rx_dma_vaddr;

	/* INTA mode only to sync with PCIe transaction */
	अगर (!pci_dev_msi_enabled(priv->board->pci_dev))
		(व्योम)pciefd_sys_पढ़ोreg(priv->board, PCIEFD_REG_SYS_VER1);

	/* पढ़ो IRQ status from the first 32-bits of the Rx DMA area */
	priv->irq_status = le32_to_cpu(rx_dma->irq_status);

	/* check अगर this (shared) IRQ is क्रम this CAN */
	अगर (pciefd_irq_tag(priv->irq_status) != priv->irq_tag)
		वापस IRQ_NONE;

	/* handle rx messages (अगर any) */
	peak_canfd_handle_msgs_list(&priv->ucan,
				    rx_dma->msg,
				    pciefd_irq_rx_cnt(priv->irq_status));

	/* handle tx link पूर्णांकerrupt (अगर any) */
	अगर (pciefd_irq_is_lnk(priv->irq_status)) अणु
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(&priv->tx_lock, flags);
		priv->tx_pages_मुक्त++;
		spin_unlock_irqrestore(&priv->tx_lock, flags);

		/* wake producer up (only अगर enough room in echo_skb array) */
		spin_lock_irqsave(&priv->ucan.echo_lock, flags);
		अगर (!priv->ucan.can.echo_skb[priv->ucan.echo_idx])
			netअगर_wake_queue(priv->ucan.ndev);

		spin_unlock_irqrestore(&priv->ucan.echo_lock, flags);
	पूर्ण

	/* re-enable Rx DMA transfer क्रम this CAN */
	pciefd_can_ack_rx_dma(priv);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक pciefd_enable_tx_path(काष्ठा peak_canfd_priv *ucan)
अणु
	काष्ठा pciefd_can *priv = (काष्ठा pciefd_can *)ucan;
	पूर्णांक i;

	/* initialize the Tx pages descriptors */
	priv->tx_pages_मुक्त = PCIEFD_TX_PAGE_COUNT - 1;
	priv->tx_page_index = 0;

	priv->tx_pages[0].vbase = priv->tx_dma_vaddr;
	priv->tx_pages[0].lbase = priv->tx_dma_laddr;

	क्रम (i = 0; i < PCIEFD_TX_PAGE_COUNT; i++) अणु
		priv->tx_pages[i].offset = 0;
		priv->tx_pages[i].size = PCIEFD_TX_PAGE_SIZE -
					 माप(काष्ठा pciefd_tx_link);
		अगर (i) अणु
			priv->tx_pages[i].vbase =
					  priv->tx_pages[i - 1].vbase +
					  PCIEFD_TX_PAGE_SIZE;
			priv->tx_pages[i].lbase =
					  priv->tx_pages[i - 1].lbase +
					  PCIEFD_TX_PAGE_SIZE;
		पूर्ण
	पूर्ण

	/* setup Tx DMA addresses पूर्णांकo IP core */
	pciefd_can_setup_tx_dma(priv);

	/* start (TX_RST=0) Tx Path */
	pciefd_can_ग_लिखोreg(priv, CANFD_CTL_RST_BIT, PCIEFD_REG_CAN_TX_CTL_CLR);

	वापस 0;
पूर्ण

/* board specअगरic CANFD command pre-processing */
अटल पूर्णांक pciefd_pre_cmd(काष्ठा peak_canfd_priv *ucan)
अणु
	काष्ठा pciefd_can *priv = (काष्ठा pciefd_can *)ucan;
	u16 cmd = pucan_cmd_get_opcode(&priv->pucan_cmd);
	पूर्णांक err;

	/* pre-process command */
	चयन (cmd) अणु
	हाल PUCAN_CMD_NORMAL_MODE:
	हाल PUCAN_CMD_LISTEN_ONLY_MODE:

		अगर (ucan->can.state == CAN_STATE_BUS_OFF)
			अवरोध;

		/* going पूर्णांकo operational mode: setup IRQ handler */
		err = request_irq(priv->ucan.ndev->irq,
				  pciefd_irq_handler,
				  IRQF_SHARED,
				  PCIEFD_DRV_NAME,
				  priv);
		अगर (err)
			वापस err;

		/* setup Rx DMA address */
		pciefd_can_setup_rx_dma(priv);

		/* setup max count of msgs per IRQ */
		pciefd_can_ग_लिखोreg(priv, (CANFD_CTL_IRQ_TL_DEF) << 8 |
				    CANFD_CTL_IRQ_CL_DEF,
				    PCIEFD_REG_CAN_RX_CTL_WRT);

		/* clear DMA RST क्रम Rx (Rx start) */
		pciefd_can_ग_लिखोreg(priv, CANFD_CTL_RST_BIT,
				    PCIEFD_REG_CAN_RX_CTL_CLR);

		/* reset बारtamps */
		pciefd_can_ग_लिखोreg(priv, !CANFD_MISC_TS_RST,
				    PCIEFD_REG_CAN_MISC);

		/* करो an initial ACK */
		pciefd_can_ack_rx_dma(priv);

		/* enable IRQ क्रम this CAN after having set next irq_tag */
		pciefd_can_ग_लिखोreg(priv, CANFD_CTL_IEN_BIT,
				    PCIEFD_REG_CAN_RX_CTL_SET);

		/* Tx path will be setup as soon as RX_BARRIER is received */
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/* ग_लिखो a command */
अटल पूर्णांक pciefd_ग_लिखो_cmd(काष्ठा peak_canfd_priv *ucan)
अणु
	काष्ठा pciefd_can *priv = (काष्ठा pciefd_can *)ucan;
	अचिन्हित दीर्घ flags;

	/* 64-bits command is atomic */
	spin_lock_irqsave(&priv->board->cmd_lock, flags);

	pciefd_can_ग_लिखोreg(priv, *(u32 *)ucan->cmd_buffer,
			    PCIEFD_REG_CAN_CMD_PORT_L);
	pciefd_can_ग_लिखोreg(priv, *(u32 *)(ucan->cmd_buffer + 4),
			    PCIEFD_REG_CAN_CMD_PORT_H);

	spin_unlock_irqrestore(&priv->board->cmd_lock, flags);

	वापस 0;
पूर्ण

/* board specअगरic CANFD command post-processing */
अटल पूर्णांक pciefd_post_cmd(काष्ठा peak_canfd_priv *ucan)
अणु
	काष्ठा pciefd_can *priv = (काष्ठा pciefd_can *)ucan;
	u16 cmd = pucan_cmd_get_opcode(&priv->pucan_cmd);

	चयन (cmd) अणु
	हाल PUCAN_CMD_RESET_MODE:

		अगर (ucan->can.state == CAN_STATE_STOPPED)
			अवरोध;

		/* controller now in reset mode: */

		/* disable IRQ क्रम this CAN */
		pciefd_can_ग_लिखोreg(priv, CANFD_CTL_IEN_BIT,
				    PCIEFD_REG_CAN_RX_CTL_CLR);

		/* stop and reset DMA addresses in Tx/Rx engines */
		pciefd_can_clear_tx_dma(priv);
		pciefd_can_clear_rx_dma(priv);

		/* रुको क्रम above commands to complete (पढ़ो cycle) */
		(व्योम)pciefd_sys_पढ़ोreg(priv->board, PCIEFD_REG_SYS_VER1);

		मुक्त_irq(priv->ucan.ndev->irq, priv);

		ucan->can.state = CAN_STATE_STOPPED;

		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम *pciefd_alloc_tx_msg(काष्ठा peak_canfd_priv *ucan, u16 msg_size,
				 पूर्णांक *room_left)
अणु
	काष्ठा pciefd_can *priv = (काष्ठा pciefd_can *)ucan;
	काष्ठा pciefd_page *page = priv->tx_pages + priv->tx_page_index;
	अचिन्हित दीर्घ flags;
	व्योम *msg;

	spin_lock_irqsave(&priv->tx_lock, flags);

	अगर (page->offset + msg_size > page->size) अणु
		काष्ठा pciefd_tx_link *lk;

		/* not enough space in this page: try another one */
		अगर (!priv->tx_pages_मुक्त) अणु
			spin_unlock_irqrestore(&priv->tx_lock, flags);

			/* Tx overflow */
			वापस शून्य;
		पूर्ण

		priv->tx_pages_मुक्त--;

		/* keep address of the very last मुक्त slot of current page */
		lk = page->vbase + page->offset;

		/* next, move on a new मुक्त page */
		priv->tx_page_index = (priv->tx_page_index + 1) %
				      PCIEFD_TX_PAGE_COUNT;
		page = priv->tx_pages + priv->tx_page_index;

		/* put link record to this new page at the end of prev one */
		lk->size = cpu_to_le16(माप(*lk));
		lk->type = cpu_to_le16(CANFD_MSG_LNK_TX);
		lk->laddr_lo = cpu_to_le32(page->lbase);

#अगर_घोषित CONFIG_ARCH_DMA_ADDR_T_64BIT
		lk->laddr_hi = cpu_to_le32(page->lbase >> 32);
#अन्यथा
		lk->laddr_hi = 0;
#पूर्ण_अगर
		/* next msgs will be put from the begininng of this new page */
		page->offset = 0;
	पूर्ण

	*room_left = priv->tx_pages_मुक्त * page->size;

	spin_unlock_irqrestore(&priv->tx_lock, flags);

	msg = page->vbase + page->offset;

	/* give back room left in the tx ring */
	*room_left += page->size - (page->offset + msg_size);

	वापस msg;
पूर्ण

अटल पूर्णांक pciefd_ग_लिखो_tx_msg(काष्ठा peak_canfd_priv *ucan,
			       काष्ठा pucan_tx_msg *msg)
अणु
	काष्ठा pciefd_can *priv = (काष्ठा pciefd_can *)ucan;
	काष्ठा pciefd_page *page = priv->tx_pages + priv->tx_page_index;

	/* this slot is now reserved क्रम writing the frame */
	page->offset += le16_to_cpu(msg->size);

	/* tell the board a frame has been written in Tx DMA area */
	pciefd_can_ग_लिखोreg(priv, 1, PCIEFD_REG_CAN_TX_REQ_ACC);

	वापस 0;
पूर्ण

/* probe क्रम CAN-FD channel #pciefd_board->can_count */
अटल पूर्णांक pciefd_can_probe(काष्ठा pciefd_board *pciefd)
अणु
	काष्ठा net_device *ndev;
	काष्ठा pciefd_can *priv;
	u32 clk;
	पूर्णांक err;

	/* allocate the candev object with शेष isize of echo skbs ring */
	ndev = alloc_peak_canfd_dev(माप(*priv), pciefd->can_count,
				    PCIEFD_ECHO_SKB_MAX);
	अगर (!ndev) अणु
		dev_err(&pciefd->pci_dev->dev,
			"failed to alloc candev object\n");
		जाओ failure;
	पूर्ण

	priv = netdev_priv(ndev);

	/* fill-in candev निजी object: */

	/* setup PCIe-FD own callbacks */
	priv->ucan.pre_cmd = pciefd_pre_cmd;
	priv->ucan.ग_लिखो_cmd = pciefd_ग_लिखो_cmd;
	priv->ucan.post_cmd = pciefd_post_cmd;
	priv->ucan.enable_tx_path = pciefd_enable_tx_path;
	priv->ucan.alloc_tx_msg = pciefd_alloc_tx_msg;
	priv->ucan.ग_लिखो_tx_msg = pciefd_ग_लिखो_tx_msg;

	/* setup PCIe-FD own command buffer */
	priv->ucan.cmd_buffer = &priv->pucan_cmd;
	priv->ucan.cmd_maxlen = माप(priv->pucan_cmd);

	priv->board = pciefd;

	/* CAN config regs block address */
	priv->reg_base = pciefd->reg_base + PCIEFD_CANX_OFF(priv->ucan.index);

	/* allocate non-cacheable DMA'able 4KB memory area क्रम Rx */
	priv->rx_dma_vaddr = dmam_alloc_coherent(&pciefd->pci_dev->dev,
						 PCIEFD_RX_DMA_SIZE,
						 &priv->rx_dma_laddr,
						 GFP_KERNEL);
	अगर (!priv->rx_dma_vaddr) अणु
		dev_err(&pciefd->pci_dev->dev,
			"Rx dmam_alloc_coherent(%u) failure\n",
			PCIEFD_RX_DMA_SIZE);
		जाओ err_मुक्त_candev;
	पूर्ण

	/* allocate non-cacheable DMA'able 4KB memory area क्रम Tx */
	priv->tx_dma_vaddr = dmam_alloc_coherent(&pciefd->pci_dev->dev,
						 PCIEFD_TX_DMA_SIZE,
						 &priv->tx_dma_laddr,
						 GFP_KERNEL);
	अगर (!priv->tx_dma_vaddr) अणु
		dev_err(&pciefd->pci_dev->dev,
			"Tx dmam_alloc_coherent(%u) failure\n",
			PCIEFD_TX_DMA_SIZE);
		जाओ err_मुक्त_candev;
	पूर्ण

	/* CAN घड़ी in RST mode */
	pciefd_can_ग_लिखोreg(priv, CANFD_MISC_TS_RST, PCIEFD_REG_CAN_MISC);

	/* पढ़ो current घड़ी value */
	clk = pciefd_can_पढ़ोreg(priv, PCIEFD_REG_CAN_CLK_SEL);
	चयन (clk) अणु
	हाल CANFD_CLK_SEL_20MHZ:
		priv->ucan.can.घड़ी.freq = 20 * 1000 * 1000;
		अवरोध;
	हाल CANFD_CLK_SEL_24MHZ:
		priv->ucan.can.घड़ी.freq = 24 * 1000 * 1000;
		अवरोध;
	हाल CANFD_CLK_SEL_30MHZ:
		priv->ucan.can.घड़ी.freq = 30 * 1000 * 1000;
		अवरोध;
	हाल CANFD_CLK_SEL_40MHZ:
		priv->ucan.can.घड़ी.freq = 40 * 1000 * 1000;
		अवरोध;
	हाल CANFD_CLK_SEL_60MHZ:
		priv->ucan.can.घड़ी.freq = 60 * 1000 * 1000;
		अवरोध;
	शेष:
		pciefd_can_ग_लिखोreg(priv, CANFD_CLK_SEL_80MHZ,
				    PCIEFD_REG_CAN_CLK_SEL);

		fallthrough;
	हाल CANFD_CLK_SEL_80MHZ:
		priv->ucan.can.घड़ी.freq = 80 * 1000 * 1000;
		अवरोध;
	पूर्ण

	ndev->irq = pciefd->pci_dev->irq;

	SET_NETDEV_DEV(ndev, &pciefd->pci_dev->dev);

	err = रेजिस्टर_candev(ndev);
	अगर (err) अणु
		dev_err(&pciefd->pci_dev->dev,
			"couldn't register CAN device: %d\n", err);
		जाओ err_मुक्त_candev;
	पूर्ण

	spin_lock_init(&priv->tx_lock);

	/* save the object address in the board काष्ठाure */
	pciefd->can[pciefd->can_count] = priv;

	dev_info(&pciefd->pci_dev->dev, "%s at reg_base=0x%p irq=%d\n",
		 ndev->name, priv->reg_base, ndev->irq);

	वापस 0;

err_मुक्त_candev:
	मुक्त_candev(ndev);

failure:
	वापस -ENOMEM;
पूर्ण

/* हटाओ a CAN-FD channel by releasing all of its resources */
अटल व्योम pciefd_can_हटाओ(काष्ठा pciefd_can *priv)
अणु
	/* unरेजिस्टर (बंद) the can device to go back to RST mode first */
	unरेजिस्टर_candev(priv->ucan.ndev);

	/* finally, मुक्त the candev object */
	मुक्त_candev(priv->ucan.ndev);
पूर्ण

/* हटाओ all CAN-FD channels by releasing their own resources */
अटल व्योम pciefd_can_हटाओ_all(काष्ठा pciefd_board *pciefd)
अणु
	जबतक (pciefd->can_count > 0)
		pciefd_can_हटाओ(pciefd->can[--pciefd->can_count]);
पूर्ण

/* probe क्रम the entire device */
अटल पूर्णांक peak_pciefd_probe(काष्ठा pci_dev *pdev,
			     स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा pciefd_board *pciefd;
	पूर्णांक err, can_count;
	u16 sub_sys_id;
	u8 hw_ver_major;
	u8 hw_ver_minor;
	u8 hw_ver_sub;
	u32 v2;

	err = pci_enable_device(pdev);
	अगर (err)
		वापस err;
	err = pci_request_regions(pdev, PCIEFD_DRV_NAME);
	अगर (err)
		जाओ err_disable_pci;

	/* the number of channels depends on sub-प्रणाली id */
	err = pci_पढ़ो_config_word(pdev, PCI_SUBSYSTEM_ID, &sub_sys_id);
	अगर (err)
		जाओ err_release_regions;

	dev_dbg(&pdev->dev, "probing device %04x:%04x:%04x\n",
		pdev->venकरोr, pdev->device, sub_sys_id);

	अगर (sub_sys_id >= 0x0012)
		can_count = 4;
	अन्यथा अगर (sub_sys_id >= 0x0010)
		can_count = 3;
	अन्यथा अगर (sub_sys_id >= 0x0004)
		can_count = 2;
	अन्यथा
		can_count = 1;

	/* allocate board काष्ठाure object */
	pciefd = devm_kzalloc(&pdev->dev, काष्ठा_size(pciefd, can, can_count),
			      GFP_KERNEL);
	अगर (!pciefd) अणु
		err = -ENOMEM;
		जाओ err_release_regions;
	पूर्ण

	/* initialize the board काष्ठाure */
	pciefd->pci_dev = pdev;
	spin_lock_init(&pciefd->cmd_lock);

	/* save the PCI BAR0 भव address क्रम further प्रणाली regs access */
	pciefd->reg_base = pci_iomap(pdev, 0, PCIEFD_BAR0_SIZE);
	अगर (!pciefd->reg_base) अणु
		dev_err(&pdev->dev, "failed to map PCI resource #0\n");
		err = -ENOMEM;
		जाओ err_release_regions;
	पूर्ण

	/* पढ़ो the firmware version number */
	v2 = pciefd_sys_पढ़ोreg(pciefd, PCIEFD_REG_SYS_VER2);

	hw_ver_major = (v2 & 0x0000f000) >> 12;
	hw_ver_minor = (v2 & 0x00000f00) >> 8;
	hw_ver_sub = (v2 & 0x000000f0) >> 4;

	dev_info(&pdev->dev,
		 "%ux CAN-FD PCAN-PCIe FPGA v%u.%u.%u:\n", can_count,
		 hw_ver_major, hw_ver_minor, hw_ver_sub);

#अगर_घोषित CONFIG_ARCH_DMA_ADDR_T_64BIT
	/* FW < v3.3.0 DMA logic करोesn't handle correctly the mix of 32-bit and
	 * 64-bit logical addresses: this workaround क्रमces usage of 32-bit
	 * DMA addresses only when such a fw is detected.
	 */
	अगर (PCIEFD_FW_VERSION(hw_ver_major, hw_ver_minor, hw_ver_sub) <
	    PCIEFD_FW_VERSION(3, 3, 0)) अणु
		err = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));
		अगर (err)
			dev_warn(&pdev->dev,
				 "warning: can't set DMA mask %llxh (err %d)\n",
				 DMA_BIT_MASK(32), err);
	पूर्ण
#पूर्ण_अगर

	/* stop प्रणाली घड़ी */
	pciefd_sys_ग_लिखोreg(pciefd, PCIEFD_SYS_CTL_CLK_EN,
			    PCIEFD_REG_SYS_CTL_CLR);

	pci_set_master(pdev);

	/* create now the corresponding channels objects */
	जबतक (pciefd->can_count < can_count) अणु
		err = pciefd_can_probe(pciefd);
		अगर (err)
			जाओ err_मुक्त_canfd;

		pciefd->can_count++;
	पूर्ण

	/* set प्रणाली बारtamps counter in RST mode */
	pciefd_sys_ग_लिखोreg(pciefd, PCIEFD_SYS_CTL_TS_RST,
			    PCIEFD_REG_SYS_CTL_SET);

	/* रुको a bit (पढ़ो cycle) */
	(व्योम)pciefd_sys_पढ़ोreg(pciefd, PCIEFD_REG_SYS_VER1);

	/* मुक्त all घड़ीs */
	pciefd_sys_ग_लिखोreg(pciefd, PCIEFD_SYS_CTL_TS_RST,
			    PCIEFD_REG_SYS_CTL_CLR);

	/* start प्रणाली घड़ी */
	pciefd_sys_ग_लिखोreg(pciefd, PCIEFD_SYS_CTL_CLK_EN,
			    PCIEFD_REG_SYS_CTL_SET);

	/* remember the board काष्ठाure address in the device user data */
	pci_set_drvdata(pdev, pciefd);

	वापस 0;

err_मुक्त_canfd:
	pciefd_can_हटाओ_all(pciefd);

	pci_iounmap(pdev, pciefd->reg_base);

err_release_regions:
	pci_release_regions(pdev);

err_disable_pci:
	pci_disable_device(pdev);

	/* pci_xxx_config_word() वापस positive PCIBIOS_xxx error codes जबतक
	 * the probe() function must वापस a negative त्रुटि_सं in हाल of failure
	 * (err is unchanged अगर negative)
	 */
	वापस pcibios_err_to_त्रुटि_सं(err);
पूर्ण

/* मुक्त the board काष्ठाure object, as well as its resources: */
अटल व्योम peak_pciefd_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा pciefd_board *pciefd = pci_get_drvdata(pdev);

	/* release CAN-FD channels resources */
	pciefd_can_हटाओ_all(pciefd);

	pci_iounmap(pdev, pciefd->reg_base);

	pci_release_regions(pdev);
	pci_disable_device(pdev);
पूर्ण

अटल काष्ठा pci_driver peak_pciefd_driver = अणु
	.name = PCIEFD_DRV_NAME,
	.id_table = peak_pciefd_tbl,
	.probe = peak_pciefd_probe,
	.हटाओ = peak_pciefd_हटाओ,
पूर्ण;

module_pci_driver(peak_pciefd_driver);
