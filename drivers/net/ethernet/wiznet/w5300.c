<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Ethernet driver क्रम the WIZnet W5300 chip.
 *
 * Copyright (C) 2008-2009 WIZnet Co.,Ltd.
 * Copyright (C) 2011 Taehun Kim <kth3321 <at> gmail.com>
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

#घोषणा DRV_NAME	"w5300"
#घोषणा DRV_VERSION	"2012-04-04"

MODULE_DESCRIPTION("WIZnet W5300 Ethernet driver v"DRV_VERSION);
MODULE_AUTHOR("Mike Sinkovsky <msink@permonline.ru>");
MODULE_ALIAS("platform:"DRV_NAME);
MODULE_LICENSE("GPL");

/*
 * Registers
 */
#घोषणा W5300_MR		0x0000	/* Mode Register */
#घोषणा   MR_DBW		  (1 << 15) /* Data bus width */
#घोषणा   MR_MPF		  (1 << 14) /* Mac layer छोड़ो frame */
#घोषणा   MR_WDF(n)		  (((n)&7)<<11) /* Write data fetch समय */
#घोषणा   MR_RDH		  (1 << 10) /* Read data hold समय */
#घोषणा   MR_FS			  (1 << 8)  /* FIFO swap */
#घोषणा   MR_RST		  (1 << 7)  /* S/W reset */
#घोषणा   MR_PB			  (1 << 4)  /* Ping block */
#घोषणा   MR_DBS		  (1 << 2)  /* Data bus swap */
#घोषणा   MR_IND		  (1 << 0)  /* Indirect mode */
#घोषणा W5300_IR		0x0002	/* Interrupt Register */
#घोषणा W5300_IMR		0x0004	/* Interrupt Mask Register */
#घोषणा   IR_S0			  0x0001  /* S0 पूर्णांकerrupt */
#घोषणा W5300_SHARL		0x0008	/* Source MAC address (0123) */
#घोषणा W5300_SHARH		0x000c	/* Source MAC address (45) */
#घोषणा W5300_TMSRL		0x0020	/* Transmit Memory Size (0123) */
#घोषणा W5300_TMSRH		0x0024	/* Transmit Memory Size (4567) */
#घोषणा W5300_RMSRL		0x0028	/* Receive Memory Size (0123) */
#घोषणा W5300_RMSRH		0x002c	/* Receive Memory Size (4567) */
#घोषणा W5300_MTYPE		0x0030	/* Memory Type */
#घोषणा W5300_IDR		0x00fe	/* Chip ID रेजिस्टर */
#घोषणा   IDR_W5300		  0x5300  /* =0x5300 क्रम WIZnet W5300 */
#घोषणा W5300_S0_MR		0x0200	/* S0 Mode Register */
#घोषणा   S0_MR_CLOSED		  0x0000  /* Close mode */
#घोषणा   S0_MR_MACRAW		  0x0004  /* MAC RAW mode (promiscuous) */
#घोषणा   S0_MR_MACRAW_MF	  0x0044  /* MAC RAW mode (filtered) */
#घोषणा W5300_S0_CR		0x0202	/* S0 Command Register */
#घोषणा   S0_CR_OPEN		  0x0001  /* OPEN command */
#घोषणा   S0_CR_CLOSE		  0x0010  /* CLOSE command */
#घोषणा   S0_CR_SEND		  0x0020  /* SEND command */
#घोषणा   S0_CR_RECV		  0x0040  /* RECV command */
#घोषणा W5300_S0_IMR		0x0204	/* S0 Interrupt Mask Register */
#घोषणा W5300_S0_IR		0x0206	/* S0 Interrupt Register */
#घोषणा   S0_IR_RECV		  0x0004  /* Receive पूर्णांकerrupt */
#घोषणा   S0_IR_SENDOK		  0x0010  /* Send OK पूर्णांकerrupt */
#घोषणा W5300_S0_SSR		0x0208	/* S0 Socket Status Register */
#घोषणा W5300_S0_TX_WRSR	0x0220	/* S0 TX Write Size Register */
#घोषणा W5300_S0_TX_FSR		0x0224	/* S0 TX Free Size Register */
#घोषणा W5300_S0_RX_RSR		0x0228	/* S0 Received data Size */
#घोषणा W5300_S0_TX_FIFO	0x022e	/* S0 Transmit FIFO */
#घोषणा W5300_S0_RX_FIFO	0x0230	/* S0 Receive FIFO */
#घोषणा W5300_REGS_LEN		0x0400

/*
 * Device driver निजी data काष्ठाure
 */
काष्ठा w5300_priv अणु
	व्योम __iomem *base;
	spinlock_t reg_lock;
	bool indirect;
	u16  (*पढ़ो) (काष्ठा w5300_priv *priv, u16 addr);
	व्योम (*ग_लिखो)(काष्ठा w5300_priv *priv, u16 addr, u16 data);
	पूर्णांक irq;
	पूर्णांक link_irq;
	पूर्णांक link_gpio;

	काष्ठा napi_काष्ठा napi;
	काष्ठा net_device *ndev;
	bool promisc;
	u32 msg_enable;
पूर्ण;

/************************************************************************
 *
 *  Lowlevel I/O functions
 *
 ***********************************************************************/

/*
 * In direct address mode host प्रणाली can directly access W5300 रेजिस्टरs
 * after mapping to Memory-Mapped I/O space.
 *
 * 0x400 bytes are required क्रम memory space.
 */
अटल अंतरभूत u16 w5300_पढ़ो_direct(काष्ठा w5300_priv *priv, u16 addr)
अणु
	वापस ioपढ़ो16(priv->base + (addr << CONFIG_WIZNET_BUS_SHIFT));
पूर्ण

अटल अंतरभूत व्योम w5300_ग_लिखो_direct(काष्ठा w5300_priv *priv,
				      u16 addr, u16 data)
अणु
	ioग_लिखो16(data, priv->base + (addr << CONFIG_WIZNET_BUS_SHIFT));
पूर्ण

/*
 * In indirect address mode host प्रणाली indirectly accesses रेजिस्टरs by
 * using Indirect Mode Address Register (IDM_AR) and Indirect Mode Data
 * Register (IDM_DR), which are directly mapped to Memory-Mapped I/O space.
 * Mode Register (MR) is directly accessible.
 *
 * Only 0x06 bytes are required क्रम memory space.
 */
#घोषणा W5300_IDM_AR		0x0002	 /* Indirect Mode Address */
#घोषणा W5300_IDM_DR		0x0004	 /* Indirect Mode Data */

अटल u16 w5300_पढ़ो_indirect(काष्ठा w5300_priv *priv, u16 addr)
अणु
	अचिन्हित दीर्घ flags;
	u16 data;

	spin_lock_irqsave(&priv->reg_lock, flags);
	w5300_ग_लिखो_direct(priv, W5300_IDM_AR, addr);
	data = w5300_पढ़ो_direct(priv, W5300_IDM_DR);
	spin_unlock_irqrestore(&priv->reg_lock, flags);

	वापस data;
पूर्ण

अटल व्योम w5300_ग_लिखो_indirect(काष्ठा w5300_priv *priv, u16 addr, u16 data)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv->reg_lock, flags);
	w5300_ग_लिखो_direct(priv, W5300_IDM_AR, addr);
	w5300_ग_लिखो_direct(priv, W5300_IDM_DR, data);
	spin_unlock_irqrestore(&priv->reg_lock, flags);
पूर्ण

#अगर defined(CONFIG_WIZNET_BUS_सूचीECT)
#घोषणा w5300_पढ़ो	w5300_पढ़ो_direct
#घोषणा w5300_ग_लिखो	w5300_ग_लिखो_direct

#या_अगर defined(CONFIG_WIZNET_BUS_INसूचीECT)
#घोषणा w5300_पढ़ो	w5300_पढ़ो_indirect
#घोषणा w5300_ग_लिखो	w5300_ग_लिखो_indirect

#अन्यथा /* CONFIG_WIZNET_BUS_ANY */
#घोषणा w5300_पढ़ो	priv->पढ़ो
#घोषणा w5300_ग_लिखो	priv->ग_लिखो
#पूर्ण_अगर

अटल u32 w5300_पढ़ो32(काष्ठा w5300_priv *priv, u16 addr)
अणु
	u32 data;
	data  = w5300_पढ़ो(priv, addr) << 16;
	data |= w5300_पढ़ो(priv, addr + 2);
	वापस data;
पूर्ण

अटल व्योम w5300_ग_लिखो32(काष्ठा w5300_priv *priv, u16 addr, u32 data)
अणु
	w5300_ग_लिखो(priv, addr, data >> 16);
	w5300_ग_लिखो(priv, addr + 2, data);
पूर्ण

अटल पूर्णांक w5300_command(काष्ठा w5300_priv *priv, u16 cmd)
अणु
	अचिन्हित दीर्घ समयout = jअगरfies + msecs_to_jअगरfies(100);

	w5300_ग_लिखो(priv, W5300_S0_CR, cmd);

	जबतक (w5300_पढ़ो(priv, W5300_S0_CR) != 0) अणु
		अगर (समय_after(jअगरfies, समयout))
			वापस -EIO;
		cpu_relax();
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम w5300_पढ़ो_frame(काष्ठा w5300_priv *priv, u8 *buf, पूर्णांक len)
अणु
	u16 fअगरo;
	पूर्णांक i;

	क्रम (i = 0; i < len; i += 2) अणु
		fअगरo = w5300_पढ़ो(priv, W5300_S0_RX_FIFO);
		*buf++ = fअगरo >> 8;
		*buf++ = fअगरo;
	पूर्ण
	fअगरo = w5300_पढ़ो(priv, W5300_S0_RX_FIFO);
	fअगरo = w5300_पढ़ो(priv, W5300_S0_RX_FIFO);
पूर्ण

अटल व्योम w5300_ग_लिखो_frame(काष्ठा w5300_priv *priv, u8 *buf, पूर्णांक len)
अणु
	u16 fअगरo;
	पूर्णांक i;

	क्रम (i = 0; i < len; i += 2) अणु
		fअगरo  = *buf++ << 8;
		fअगरo |= *buf++;
		w5300_ग_लिखो(priv, W5300_S0_TX_FIFO, fअगरo);
	पूर्ण
	w5300_ग_लिखो32(priv, W5300_S0_TX_WRSR, len);
पूर्ण

अटल व्योम w5300_ग_लिखो_macaddr(काष्ठा w5300_priv *priv)
अणु
	काष्ठा net_device *ndev = priv->ndev;
	w5300_ग_लिखो32(priv, W5300_SHARL,
		      ndev->dev_addr[0] << 24 |
		      ndev->dev_addr[1] << 16 |
		      ndev->dev_addr[2] << 8 |
		      ndev->dev_addr[3]);
	w5300_ग_लिखो(priv, W5300_SHARH,
		      ndev->dev_addr[4] << 8 |
		      ndev->dev_addr[5]);
पूर्ण

अटल व्योम w5300_hw_reset(काष्ठा w5300_priv *priv)
अणु
	w5300_ग_लिखो_direct(priv, W5300_MR, MR_RST);
	mdelay(5);
	w5300_ग_लिखो_direct(priv, W5300_MR, priv->indirect ?
				 MR_WDF(7) | MR_PB | MR_IND :
				 MR_WDF(7) | MR_PB);
	w5300_ग_लिखो(priv, W5300_IMR, 0);
	w5300_ग_लिखो_macaddr(priv);

	/* Configure 128K of पूर्णांकernal memory
	 * as 64K RX fअगरo and 64K TX fअगरo
	 */
	w5300_ग_लिखो32(priv, W5300_RMSRL, 64 << 24);
	w5300_ग_लिखो32(priv, W5300_RMSRH, 0);
	w5300_ग_लिखो32(priv, W5300_TMSRL, 64 << 24);
	w5300_ग_लिखो32(priv, W5300_TMSRH, 0);
	w5300_ग_लिखो(priv, W5300_MTYPE, 0x00ff);
पूर्ण

अटल व्योम w5300_hw_start(काष्ठा w5300_priv *priv)
अणु
	w5300_ग_लिखो(priv, W5300_S0_MR, priv->promisc ?
			  S0_MR_MACRAW : S0_MR_MACRAW_MF);
	w5300_command(priv, S0_CR_OPEN);
	w5300_ग_लिखो(priv, W5300_S0_IMR, S0_IR_RECV | S0_IR_SENDOK);
	w5300_ग_लिखो(priv, W5300_IMR, IR_S0);
पूर्ण

अटल व्योम w5300_hw_बंद(काष्ठा w5300_priv *priv)
अणु
	w5300_ग_लिखो(priv, W5300_IMR, 0);
	w5300_command(priv, S0_CR_CLOSE);
पूर्ण

/***********************************************************************
 *
 *   Device driver functions / callbacks
 *
 ***********************************************************************/

अटल व्योम w5300_get_drvinfo(काष्ठा net_device *ndev,
			      काष्ठा ethtool_drvinfo *info)
अणु
	strlcpy(info->driver, DRV_NAME, माप(info->driver));
	strlcpy(info->version, DRV_VERSION, माप(info->version));
	strlcpy(info->bus_info, dev_name(ndev->dev.parent),
		माप(info->bus_info));
पूर्ण

अटल u32 w5300_get_link(काष्ठा net_device *ndev)
अणु
	काष्ठा w5300_priv *priv = netdev_priv(ndev);

	अगर (gpio_is_valid(priv->link_gpio))
		वापस !!gpio_get_value(priv->link_gpio);

	वापस 1;
पूर्ण

अटल u32 w5300_get_msglevel(काष्ठा net_device *ndev)
अणु
	काष्ठा w5300_priv *priv = netdev_priv(ndev);

	वापस priv->msg_enable;
पूर्ण

अटल व्योम w5300_set_msglevel(काष्ठा net_device *ndev, u32 value)
अणु
	काष्ठा w5300_priv *priv = netdev_priv(ndev);

	priv->msg_enable = value;
पूर्ण

अटल पूर्णांक w5300_get_regs_len(काष्ठा net_device *ndev)
अणु
	वापस W5300_REGS_LEN;
पूर्ण

अटल व्योम w5300_get_regs(काष्ठा net_device *ndev,
			   काष्ठा ethtool_regs *regs, व्योम *_buf)
अणु
	काष्ठा w5300_priv *priv = netdev_priv(ndev);
	u8 *buf = _buf;
	u16 addr;
	u16 data;

	regs->version = 1;
	क्रम (addr = 0; addr < W5300_REGS_LEN; addr += 2) अणु
		चयन (addr & 0x23f) अणु
		हाल W5300_S0_TX_FIFO: /* cannot पढ़ो TX_FIFO */
		हाल W5300_S0_RX_FIFO: /* cannot पढ़ो RX_FIFO */
			data = 0xffff;
			अवरोध;
		शेष:
			data = w5300_पढ़ो(priv, addr);
			अवरोध;
		पूर्ण
		*buf++ = data >> 8;
		*buf++ = data;
	पूर्ण
पूर्ण

अटल व्योम w5300_tx_समयout(काष्ठा net_device *ndev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा w5300_priv *priv = netdev_priv(ndev);

	netअगर_stop_queue(ndev);
	w5300_hw_reset(priv);
	w5300_hw_start(priv);
	ndev->stats.tx_errors++;
	netअगर_trans_update(ndev);
	netअगर_wake_queue(ndev);
पूर्ण

अटल netdev_tx_t w5300_start_tx(काष्ठा sk_buff *skb, काष्ठा net_device *ndev)
अणु
	काष्ठा w5300_priv *priv = netdev_priv(ndev);

	netअगर_stop_queue(ndev);

	w5300_ग_लिखो_frame(priv, skb->data, skb->len);
	ndev->stats.tx_packets++;
	ndev->stats.tx_bytes += skb->len;
	dev_kमुक्त_skb(skb);
	netअगर_dbg(priv, tx_queued, ndev, "tx queued\n");

	w5300_command(priv, S0_CR_SEND);

	वापस NETDEV_TX_OK;
पूर्ण

अटल पूर्णांक w5300_napi_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा w5300_priv *priv = container_of(napi, काष्ठा w5300_priv, napi);
	काष्ठा net_device *ndev = priv->ndev;
	काष्ठा sk_buff *skb;
	पूर्णांक rx_count;
	u16 rx_len;

	क्रम (rx_count = 0; rx_count < budget; rx_count++) अणु
		u32 rx_fअगरo_len = w5300_पढ़ो32(priv, W5300_S0_RX_RSR);
		अगर (rx_fअगरo_len == 0)
			अवरोध;

		rx_len = w5300_पढ़ो(priv, W5300_S0_RX_FIFO);

		skb = netdev_alloc_skb_ip_align(ndev, roundup(rx_len, 2));
		अगर (unlikely(!skb)) अणु
			u32 i;
			क्रम (i = 0; i < rx_fअगरo_len; i += 2)
				w5300_पढ़ो(priv, W5300_S0_RX_FIFO);
			ndev->stats.rx_dropped++;
			वापस -ENOMEM;
		पूर्ण

		skb_put(skb, rx_len);
		w5300_पढ़ो_frame(priv, skb->data, rx_len);
		skb->protocol = eth_type_trans(skb, ndev);

		netअगर_receive_skb(skb);
		ndev->stats.rx_packets++;
		ndev->stats.rx_bytes += rx_len;
	पूर्ण

	अगर (rx_count < budget) अणु
		napi_complete_करोne(napi, rx_count);
		w5300_ग_लिखो(priv, W5300_IMR, IR_S0);
	पूर्ण

	वापस rx_count;
पूर्ण

अटल irqवापस_t w5300_पूर्णांकerrupt(पूर्णांक irq, व्योम *ndev_instance)
अणु
	काष्ठा net_device *ndev = ndev_instance;
	काष्ठा w5300_priv *priv = netdev_priv(ndev);

	पूर्णांक ir = w5300_पढ़ो(priv, W5300_S0_IR);
	अगर (!ir)
		वापस IRQ_NONE;
	w5300_ग_लिखो(priv, W5300_S0_IR, ir);

	अगर (ir & S0_IR_SENDOK) अणु
		netअगर_dbg(priv, tx_करोne, ndev, "tx done\n");
		netअगर_wake_queue(ndev);
	पूर्ण

	अगर (ir & S0_IR_RECV) अणु
		अगर (napi_schedule_prep(&priv->napi)) अणु
			w5300_ग_लिखो(priv, W5300_IMR, 0);
			__napi_schedule(&priv->napi);
		पूर्ण
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t w5300_detect_link(पूर्णांक irq, व्योम *ndev_instance)
अणु
	काष्ठा net_device *ndev = ndev_instance;
	काष्ठा w5300_priv *priv = netdev_priv(ndev);

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

अटल व्योम w5300_set_rx_mode(काष्ठा net_device *ndev)
अणु
	काष्ठा w5300_priv *priv = netdev_priv(ndev);
	bool set_promisc = (ndev->flags & IFF_PROMISC) != 0;

	अगर (priv->promisc != set_promisc) अणु
		priv->promisc = set_promisc;
		w5300_hw_start(priv);
	पूर्ण
पूर्ण

अटल पूर्णांक w5300_set_macaddr(काष्ठा net_device *ndev, व्योम *addr)
अणु
	काष्ठा w5300_priv *priv = netdev_priv(ndev);
	काष्ठा sockaddr *sock_addr = addr;

	अगर (!is_valid_ether_addr(sock_addr->sa_data))
		वापस -EADDRNOTAVAIL;
	स_नकल(ndev->dev_addr, sock_addr->sa_data, ETH_ALEN);
	w5300_ग_लिखो_macaddr(priv);
	वापस 0;
पूर्ण

अटल पूर्णांक w5300_खोलो(काष्ठा net_device *ndev)
अणु
	काष्ठा w5300_priv *priv = netdev_priv(ndev);

	netअगर_info(priv, अगरup, ndev, "enabling\n");
	w5300_hw_start(priv);
	napi_enable(&priv->napi);
	netअगर_start_queue(ndev);
	अगर (!gpio_is_valid(priv->link_gpio) ||
	    gpio_get_value(priv->link_gpio) != 0)
		netअगर_carrier_on(ndev);
	वापस 0;
पूर्ण

अटल पूर्णांक w5300_stop(काष्ठा net_device *ndev)
अणु
	काष्ठा w5300_priv *priv = netdev_priv(ndev);

	netअगर_info(priv, अगरकरोwn, ndev, "shutting down\n");
	w5300_hw_बंद(priv);
	netअगर_carrier_off(ndev);
	netअगर_stop_queue(ndev);
	napi_disable(&priv->napi);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops w5300_ethtool_ops = अणु
	.get_drvinfo		= w5300_get_drvinfo,
	.get_msglevel		= w5300_get_msglevel,
	.set_msglevel		= w5300_set_msglevel,
	.get_link		= w5300_get_link,
	.get_regs_len		= w5300_get_regs_len,
	.get_regs		= w5300_get_regs,
पूर्ण;

अटल स्थिर काष्ठा net_device_ops w5300_netdev_ops = अणु
	.nकरो_खोलो		= w5300_खोलो,
	.nकरो_stop		= w5300_stop,
	.nकरो_start_xmit		= w5300_start_tx,
	.nकरो_tx_समयout		= w5300_tx_समयout,
	.nकरो_set_rx_mode	= w5300_set_rx_mode,
	.nकरो_set_mac_address	= w5300_set_macaddr,
	.nकरो_validate_addr	= eth_validate_addr,
पूर्ण;

अटल पूर्णांक w5300_hw_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा wiznet_platक्रमm_data *data = dev_get_platdata(&pdev->dev);
	काष्ठा net_device *ndev = platक्रमm_get_drvdata(pdev);
	काष्ठा w5300_priv *priv = netdev_priv(ndev);
	स्थिर अक्षर *name = netdev_name(ndev);
	काष्ठा resource *mem;
	पूर्णांक mem_size;
	पूर्णांक irq;
	पूर्णांक ret;

	अगर (data && is_valid_ether_addr(data->mac_addr)) अणु
		स_नकल(ndev->dev_addr, data->mac_addr, ETH_ALEN);
	पूर्ण अन्यथा अणु
		eth_hw_addr_अक्रमom(ndev);
	पूर्ण

	mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	priv->base = devm_ioremap_resource(&pdev->dev, mem);
	अगर (IS_ERR(priv->base))
		वापस PTR_ERR(priv->base);

	mem_size = resource_size(mem);

	spin_lock_init(&priv->reg_lock);
	priv->indirect = mem_size < W5300_BUS_सूचीECT_SIZE;
	अगर (priv->indirect) अणु
		priv->पढ़ो  = w5300_पढ़ो_indirect;
		priv->ग_लिखो = w5300_ग_लिखो_indirect;
	पूर्ण अन्यथा अणु
		priv->पढ़ो  = w5300_पढ़ो_direct;
		priv->ग_लिखो = w5300_ग_लिखो_direct;
	पूर्ण

	w5300_hw_reset(priv);
	अगर (w5300_पढ़ो(priv, W5300_IDR) != IDR_W5300)
		वापस -ENODEV;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;
	ret = request_irq(irq, w5300_पूर्णांकerrupt,
			  IRQ_TYPE_LEVEL_LOW, name, ndev);
	अगर (ret < 0)
		वापस ret;
	priv->irq = irq;

	priv->link_gpio = data ? data->link_gpio : -EINVAL;
	अगर (gpio_is_valid(priv->link_gpio)) अणु
		अक्षर *link_name = devm_kzalloc(&pdev->dev, 16, GFP_KERNEL);
		अगर (!link_name)
			वापस -ENOMEM;
		snम_लिखो(link_name, 16, "%s-link", name);
		priv->link_irq = gpio_to_irq(priv->link_gpio);
		अगर (request_any_context_irq(priv->link_irq, w5300_detect_link,
				IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING,
				link_name, priv->ndev) < 0)
			priv->link_gpio = -EINVAL;
	पूर्ण

	netdev_info(ndev, "at 0x%llx irq %d\n", (u64)mem->start, irq);
	वापस 0;
पूर्ण

अटल पूर्णांक w5300_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा w5300_priv *priv;
	काष्ठा net_device *ndev;
	पूर्णांक err;

	ndev = alloc_etherdev(माप(*priv));
	अगर (!ndev)
		वापस -ENOMEM;
	SET_NETDEV_DEV(ndev, &pdev->dev);
	platक्रमm_set_drvdata(pdev, ndev);
	priv = netdev_priv(ndev);
	priv->ndev = ndev;

	ndev->netdev_ops = &w5300_netdev_ops;
	ndev->ethtool_ops = &w5300_ethtool_ops;
	ndev->watchकरोg_समयo = HZ;
	netअगर_napi_add(ndev, &priv->napi, w5300_napi_poll, 16);

	/* This chip करोesn't support VLAN packets with normal MTU,
	 * so disable VLAN क्रम this device.
	 */
	ndev->features |= NETIF_F_VLAN_CHALLENGED;

	err = रेजिस्टर_netdev(ndev);
	अगर (err < 0)
		जाओ err_रेजिस्टर;

	err = w5300_hw_probe(pdev);
	अगर (err < 0)
		जाओ err_hw_probe;

	वापस 0;

err_hw_probe:
	unरेजिस्टर_netdev(ndev);
err_रेजिस्टर:
	मुक्त_netdev(ndev);
	वापस err;
पूर्ण

अटल पूर्णांक w5300_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *ndev = platक्रमm_get_drvdata(pdev);
	काष्ठा w5300_priv *priv = netdev_priv(ndev);

	w5300_hw_reset(priv);
	मुक्त_irq(priv->irq, ndev);
	अगर (gpio_is_valid(priv->link_gpio))
		मुक्त_irq(priv->link_irq, ndev);

	unरेजिस्टर_netdev(ndev);
	मुक्त_netdev(ndev);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक w5300_suspend(काष्ठा device *dev)
अणु
	काष्ठा net_device *ndev = dev_get_drvdata(dev);
	काष्ठा w5300_priv *priv = netdev_priv(ndev);

	अगर (netअगर_running(ndev)) अणु
		netअगर_carrier_off(ndev);
		netअगर_device_detach(ndev);

		w5300_hw_बंद(priv);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक w5300_resume(काष्ठा device *dev)
अणु
	काष्ठा net_device *ndev = dev_get_drvdata(dev);
	काष्ठा w5300_priv *priv = netdev_priv(ndev);

	अगर (!netअगर_running(ndev)) अणु
		w5300_hw_reset(priv);
		w5300_hw_start(priv);

		netअगर_device_attach(ndev);
		अगर (!gpio_is_valid(priv->link_gpio) ||
		    gpio_get_value(priv->link_gpio) != 0)
			netअगर_carrier_on(ndev);
	पूर्ण
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल SIMPLE_DEV_PM_OPS(w5300_pm_ops, w5300_suspend, w5300_resume);

अटल काष्ठा platक्रमm_driver w5300_driver = अणु
	.driver		= अणु
		.name	= DRV_NAME,
		.pm	= &w5300_pm_ops,
	पूर्ण,
	.probe		= w5300_probe,
	.हटाओ		= w5300_हटाओ,
पूर्ण;

module_platक्रमm_driver(w5300_driver);
