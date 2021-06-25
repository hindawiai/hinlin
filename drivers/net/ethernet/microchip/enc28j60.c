<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Microchip ENC28J60 ethernet driver (MAC + PHY)
 *
 * Copyright (C) 2007 Eurek srl
 * Author: Claudio Lanconelli <lanconelli.claudio@eptar.com>
 * based on enc28j60.c written by David Anders क्रम 2.4 kernel version
 *
 * $Id: enc28j60.c,v 1.22 2007/12/20 10:47:01 claudio Exp $
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/property.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/tcp.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/delay.h>
#समावेश <linux/spi/spi.h>

#समावेश "enc28j60_hw.h"

#घोषणा DRV_NAME	"enc28j60"
#घोषणा DRV_VERSION	"1.02"

#घोषणा SPI_OPLEN	1

#घोषणा ENC28J60_MSG_DEFAULT	\
	(NETIF_MSG_PROBE | NETIF_MSG_IFUP | NETIF_MSG_IFDOWN | NETIF_MSG_LINK)

/* Buffer size required क्रम the largest SPI transfer (i.e., पढ़ोing a
 * frame).
 */
#घोषणा SPI_TRANSFER_BUF_LEN	(4 + MAX_FRAMELEN)

#घोषणा TX_TIMEOUT		(4 * HZ)

/* Max TX retries in हाल of collision as suggested by errata datasheet */
#घोषणा MAX_TX_RETRYCOUNT	16

क्रमागत अणु
	RXFILTER_NORMAL,
	RXFILTER_MULTI,
	RXFILTER_PROMISC
पूर्ण;

/* Driver local data */
काष्ठा enc28j60_net अणु
	काष्ठा net_device *netdev;
	काष्ठा spi_device *spi;
	काष्ठा mutex lock;
	काष्ठा sk_buff *tx_skb;
	काष्ठा work_काष्ठा tx_work;
	काष्ठा work_काष्ठा irq_work;
	काष्ठा work_काष्ठा setrx_work;
	काष्ठा work_काष्ठा restart_work;
	u8 bank;		/* current रेजिस्टर bank selected */
	u16 next_pk_ptr;	/* next packet poपूर्णांकer within FIFO */
	u16 max_pk_counter;	/* statistics: max packet counter */
	u16 tx_retry_count;
	bool hw_enable;
	bool full_duplex;
	पूर्णांक rxfilter;
	u32 msg_enable;
	u8 spi_transfer_buf[SPI_TRANSFER_BUF_LEN];
पूर्ण;

/* use ethtool to change the level क्रम any given device */
अटल काष्ठा अणु
	u32 msg_enable;
पूर्ण debug = अणु -1 पूर्ण;

/*
 * SPI पढ़ो buffer
 * Wait क्रम the SPI transfer and copy received data to destination.
 */
अटल पूर्णांक
spi_पढ़ो_buf(काष्ठा enc28j60_net *priv, पूर्णांक len, u8 *data)
अणु
	काष्ठा device *dev = &priv->spi->dev;
	u8 *rx_buf = priv->spi_transfer_buf + 4;
	u8 *tx_buf = priv->spi_transfer_buf;
	काष्ठा spi_transfer tx = अणु
		.tx_buf = tx_buf,
		.len = SPI_OPLEN,
	पूर्ण;
	काष्ठा spi_transfer rx = अणु
		.rx_buf = rx_buf,
		.len = len,
	पूर्ण;
	काष्ठा spi_message msg;
	पूर्णांक ret;

	tx_buf[0] = ENC28J60_READ_BUF_MEM;

	spi_message_init(&msg);
	spi_message_add_tail(&tx, &msg);
	spi_message_add_tail(&rx, &msg);

	ret = spi_sync(priv->spi, &msg);
	अगर (ret == 0) अणु
		स_नकल(data, rx_buf, len);
		ret = msg.status;
	पूर्ण
	अगर (ret && netअगर_msg_drv(priv))
		dev_prपूर्णांकk(KERN_DEBUG, dev, "%s() failed: ret = %d\n",
			   __func__, ret);

	वापस ret;
पूर्ण

/*
 * SPI ग_लिखो buffer
 */
अटल पूर्णांक spi_ग_लिखो_buf(काष्ठा enc28j60_net *priv, पूर्णांक len, स्थिर u8 *data)
अणु
	काष्ठा device *dev = &priv->spi->dev;
	पूर्णांक ret;

	अगर (len > SPI_TRANSFER_BUF_LEN - 1 || len <= 0)
		ret = -EINVAL;
	अन्यथा अणु
		priv->spi_transfer_buf[0] = ENC28J60_WRITE_BUF_MEM;
		स_नकल(&priv->spi_transfer_buf[1], data, len);
		ret = spi_ग_लिखो(priv->spi, priv->spi_transfer_buf, len + 1);
		अगर (ret && netअगर_msg_drv(priv))
			dev_prपूर्णांकk(KERN_DEBUG, dev, "%s() failed: ret = %d\n",
				   __func__, ret);
	पूर्ण
	वापस ret;
पूर्ण

/*
 * basic SPI पढ़ो operation
 */
अटल u8 spi_पढ़ो_op(काष्ठा enc28j60_net *priv, u8 op, u8 addr)
अणु
	काष्ठा device *dev = &priv->spi->dev;
	u8 tx_buf[2];
	u8 rx_buf[4];
	u8 val = 0;
	पूर्णांक ret;
	पूर्णांक slen = SPI_OPLEN;

	/* करो dummy पढ़ो अगर needed */
	अगर (addr & SPRD_MASK)
		slen++;

	tx_buf[0] = op | (addr & ADDR_MASK);
	ret = spi_ग_लिखो_then_पढ़ो(priv->spi, tx_buf, 1, rx_buf, slen);
	अगर (ret)
		dev_prपूर्णांकk(KERN_DEBUG, dev, "%s() failed: ret = %d\n",
			   __func__, ret);
	अन्यथा
		val = rx_buf[slen - 1];

	वापस val;
पूर्ण

/*
 * basic SPI ग_लिखो operation
 */
अटल पूर्णांक spi_ग_लिखो_op(काष्ठा enc28j60_net *priv, u8 op, u8 addr, u8 val)
अणु
	काष्ठा device *dev = &priv->spi->dev;
	पूर्णांक ret;

	priv->spi_transfer_buf[0] = op | (addr & ADDR_MASK);
	priv->spi_transfer_buf[1] = val;
	ret = spi_ग_लिखो(priv->spi, priv->spi_transfer_buf, 2);
	अगर (ret && netअगर_msg_drv(priv))
		dev_prपूर्णांकk(KERN_DEBUG, dev, "%s() failed: ret = %d\n",
			   __func__, ret);
	वापस ret;
पूर्ण

अटल व्योम enc28j60_soft_reset(काष्ठा enc28j60_net *priv)
अणु
	spi_ग_लिखो_op(priv, ENC28J60_SOFT_RESET, 0, ENC28J60_SOFT_RESET);
	/* Errata workaround #1, CLKRDY check is unreliable,
	 * delay at least 1 ms instead */
	udelay(2000);
पूर्ण

/*
 * select the current रेजिस्टर bank अगर necessary
 */
अटल व्योम enc28j60_set_bank(काष्ठा enc28j60_net *priv, u8 addr)
अणु
	u8 b = (addr & BANK_MASK) >> 5;

	/* These रेजिस्टरs (EIE, EIR, ESTAT, ECON2, ECON1)
	 * are present in all banks, no need to चयन bank.
	 */
	अगर (addr >= EIE && addr <= ECON1)
		वापस;

	/* Clear or set each bank selection bit as needed */
	अगर ((b & ECON1_BSEL0) != (priv->bank & ECON1_BSEL0)) अणु
		अगर (b & ECON1_BSEL0)
			spi_ग_लिखो_op(priv, ENC28J60_BIT_FIELD_SET, ECON1,
					ECON1_BSEL0);
		अन्यथा
			spi_ग_लिखो_op(priv, ENC28J60_BIT_FIELD_CLR, ECON1,
					ECON1_BSEL0);
	पूर्ण
	अगर ((b & ECON1_BSEL1) != (priv->bank & ECON1_BSEL1)) अणु
		अगर (b & ECON1_BSEL1)
			spi_ग_लिखो_op(priv, ENC28J60_BIT_FIELD_SET, ECON1,
					ECON1_BSEL1);
		अन्यथा
			spi_ग_लिखो_op(priv, ENC28J60_BIT_FIELD_CLR, ECON1,
					ECON1_BSEL1);
	पूर्ण
	priv->bank = b;
पूर्ण

/*
 * Register access routines through the SPI bus.
 * Every रेजिस्टर access comes in two flavours:
 * - nolock_xxx: caller needs to invoke mutex_lock, usually to access
 *   atomically more than one रेजिस्टर
 * - locked_xxx: caller करोesn't need to invoke mutex_lock, single access
 *
 * Some रेजिस्टरs can be accessed through the bit field clear and
 * bit field set to aव्योम a पढ़ो modअगरy ग_लिखो cycle.
 */

/*
 * Register bit field Set
 */
अटल व्योम nolock_reg_bfset(काष्ठा enc28j60_net *priv, u8 addr, u8 mask)
अणु
	enc28j60_set_bank(priv, addr);
	spi_ग_लिखो_op(priv, ENC28J60_BIT_FIELD_SET, addr, mask);
पूर्ण

अटल व्योम locked_reg_bfset(काष्ठा enc28j60_net *priv, u8 addr, u8 mask)
अणु
	mutex_lock(&priv->lock);
	nolock_reg_bfset(priv, addr, mask);
	mutex_unlock(&priv->lock);
पूर्ण

/*
 * Register bit field Clear
 */
अटल व्योम nolock_reg_bfclr(काष्ठा enc28j60_net *priv, u8 addr, u8 mask)
अणु
	enc28j60_set_bank(priv, addr);
	spi_ग_लिखो_op(priv, ENC28J60_BIT_FIELD_CLR, addr, mask);
पूर्ण

अटल व्योम locked_reg_bfclr(काष्ठा enc28j60_net *priv, u8 addr, u8 mask)
अणु
	mutex_lock(&priv->lock);
	nolock_reg_bfclr(priv, addr, mask);
	mutex_unlock(&priv->lock);
पूर्ण

/*
 * Register byte पढ़ो
 */
अटल पूर्णांक nolock_regb_पढ़ो(काष्ठा enc28j60_net *priv, u8 address)
अणु
	enc28j60_set_bank(priv, address);
	वापस spi_पढ़ो_op(priv, ENC28J60_READ_CTRL_REG, address);
पूर्ण

अटल पूर्णांक locked_regb_पढ़ो(काष्ठा enc28j60_net *priv, u8 address)
अणु
	पूर्णांक ret;

	mutex_lock(&priv->lock);
	ret = nolock_regb_पढ़ो(priv, address);
	mutex_unlock(&priv->lock);

	वापस ret;
पूर्ण

/*
 * Register word पढ़ो
 */
अटल पूर्णांक nolock_regw_पढ़ो(काष्ठा enc28j60_net *priv, u8 address)
अणु
	पूर्णांक rl, rh;

	enc28j60_set_bank(priv, address);
	rl = spi_पढ़ो_op(priv, ENC28J60_READ_CTRL_REG, address);
	rh = spi_पढ़ो_op(priv, ENC28J60_READ_CTRL_REG, address + 1);

	वापस (rh << 8) | rl;
पूर्ण

अटल पूर्णांक locked_regw_पढ़ो(काष्ठा enc28j60_net *priv, u8 address)
अणु
	पूर्णांक ret;

	mutex_lock(&priv->lock);
	ret = nolock_regw_पढ़ो(priv, address);
	mutex_unlock(&priv->lock);

	वापस ret;
पूर्ण

/*
 * Register byte ग_लिखो
 */
अटल व्योम nolock_regb_ग_लिखो(काष्ठा enc28j60_net *priv, u8 address, u8 data)
अणु
	enc28j60_set_bank(priv, address);
	spi_ग_लिखो_op(priv, ENC28J60_WRITE_CTRL_REG, address, data);
पूर्ण

अटल व्योम locked_regb_ग_लिखो(काष्ठा enc28j60_net *priv, u8 address, u8 data)
अणु
	mutex_lock(&priv->lock);
	nolock_regb_ग_लिखो(priv, address, data);
	mutex_unlock(&priv->lock);
पूर्ण

/*
 * Register word ग_लिखो
 */
अटल व्योम nolock_regw_ग_लिखो(काष्ठा enc28j60_net *priv, u8 address, u16 data)
अणु
	enc28j60_set_bank(priv, address);
	spi_ग_लिखो_op(priv, ENC28J60_WRITE_CTRL_REG, address, (u8) data);
	spi_ग_लिखो_op(priv, ENC28J60_WRITE_CTRL_REG, address + 1,
		     (u8) (data >> 8));
पूर्ण

अटल व्योम locked_regw_ग_लिखो(काष्ठा enc28j60_net *priv, u8 address, u16 data)
अणु
	mutex_lock(&priv->lock);
	nolock_regw_ग_लिखो(priv, address, data);
	mutex_unlock(&priv->lock);
पूर्ण

/*
 * Buffer memory पढ़ो
 * Select the starting address and execute a SPI buffer पढ़ो.
 */
अटल व्योम enc28j60_mem_पढ़ो(काष्ठा enc28j60_net *priv, u16 addr, पूर्णांक len,
			      u8 *data)
अणु
	mutex_lock(&priv->lock);
	nolock_regw_ग_लिखो(priv, ERDPTL, addr);
#अगर_घोषित CONFIG_ENC28J60_WRITEVERIFY
	अगर (netअगर_msg_drv(priv)) अणु
		काष्ठा device *dev = &priv->spi->dev;
		u16 reg;

		reg = nolock_regw_पढ़ो(priv, ERDPTL);
		अगर (reg != addr)
			dev_prपूर्णांकk(KERN_DEBUG, dev,
				   "%s() error writing ERDPT (0x%04x - 0x%04x)\n",
				   __func__, reg, addr);
	पूर्ण
#पूर्ण_अगर
	spi_पढ़ो_buf(priv, len, data);
	mutex_unlock(&priv->lock);
पूर्ण

/*
 * Write packet to enc28j60 TX buffer memory
 */
अटल व्योम
enc28j60_packet_ग_लिखो(काष्ठा enc28j60_net *priv, पूर्णांक len, स्थिर u8 *data)
अणु
	काष्ठा device *dev = &priv->spi->dev;

	mutex_lock(&priv->lock);
	/* Set the ग_लिखो poपूर्णांकer to start of transmit buffer area */
	nolock_regw_ग_लिखो(priv, EWRPTL, TXSTART_INIT);
#अगर_घोषित CONFIG_ENC28J60_WRITEVERIFY
	अगर (netअगर_msg_drv(priv)) अणु
		u16 reg;
		reg = nolock_regw_पढ़ो(priv, EWRPTL);
		अगर (reg != TXSTART_INIT)
			dev_prपूर्णांकk(KERN_DEBUG, dev,
				   "%s() ERWPT:0x%04x != 0x%04x\n",
				   __func__, reg, TXSTART_INIT);
	पूर्ण
#पूर्ण_अगर
	/* Set the TXND poपूर्णांकer to correspond to the packet size given */
	nolock_regw_ग_लिखो(priv, ETXNDL, TXSTART_INIT + len);
	/* ग_लिखो per-packet control byte */
	spi_ग_लिखो_op(priv, ENC28J60_WRITE_BUF_MEM, 0, 0x00);
	अगर (netअगर_msg_hw(priv))
		dev_prपूर्णांकk(KERN_DEBUG, dev,
			   "%s() after control byte ERWPT:0x%04x\n",
			   __func__, nolock_regw_पढ़ो(priv, EWRPTL));
	/* copy the packet पूर्णांकo the transmit buffer */
	spi_ग_लिखो_buf(priv, len, data);
	अगर (netअगर_msg_hw(priv))
		dev_prपूर्णांकk(KERN_DEBUG, dev,
			   "%s() after write packet ERWPT:0x%04x, len=%d\n",
			   __func__, nolock_regw_पढ़ो(priv, EWRPTL), len);
	mutex_unlock(&priv->lock);
पूर्ण

अटल पूर्णांक poll_पढ़ोy(काष्ठा enc28j60_net *priv, u8 reg, u8 mask, u8 val)
अणु
	काष्ठा device *dev = &priv->spi->dev;
	अचिन्हित दीर्घ समयout = jअगरfies + msecs_to_jअगरfies(20);

	/* 20 msec समयout पढ़ो */
	जबतक ((nolock_regb_पढ़ो(priv, reg) & mask) != val) अणु
		अगर (समय_after(jअगरfies, समयout)) अणु
			अगर (netअगर_msg_drv(priv))
				dev_dbg(dev, "reg %02x ready timeout!\n", reg);
			वापस -ETIMEDOUT;
		पूर्ण
		cpu_relax();
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Wait until the PHY operation is complete.
 */
अटल पूर्णांक रुको_phy_पढ़ोy(काष्ठा enc28j60_net *priv)
अणु
	वापस poll_पढ़ोy(priv, MISTAT, MISTAT_BUSY, 0) ? 0 : 1;
पूर्ण

/*
 * PHY रेजिस्टर पढ़ो
 * PHY रेजिस्टरs are not accessed directly, but through the MII.
 */
अटल u16 enc28j60_phy_पढ़ो(काष्ठा enc28j60_net *priv, u8 address)
अणु
	u16 ret;

	mutex_lock(&priv->lock);
	/* set the PHY रेजिस्टर address */
	nolock_regb_ग_लिखो(priv, MIREGADR, address);
	/* start the रेजिस्टर पढ़ो operation */
	nolock_regb_ग_लिखो(priv, MICMD, MICMD_MIIRD);
	/* रुको until the PHY पढ़ो completes */
	रुको_phy_पढ़ोy(priv);
	/* quit पढ़ोing */
	nolock_regb_ग_लिखो(priv, MICMD, 0x00);
	/* वापस the data */
	ret = nolock_regw_पढ़ो(priv, MIRDL);
	mutex_unlock(&priv->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक enc28j60_phy_ग_लिखो(काष्ठा enc28j60_net *priv, u8 address, u16 data)
अणु
	पूर्णांक ret;

	mutex_lock(&priv->lock);
	/* set the PHY रेजिस्टर address */
	nolock_regb_ग_लिखो(priv, MIREGADR, address);
	/* ग_लिखो the PHY data */
	nolock_regw_ग_लिखो(priv, MIWRL, data);
	/* रुको until the PHY ग_लिखो completes and वापस */
	ret = रुको_phy_पढ़ोy(priv);
	mutex_unlock(&priv->lock);

	वापस ret;
पूर्ण

/*
 * Program the hardware MAC address from dev->dev_addr.
 */
अटल पूर्णांक enc28j60_set_hw_macaddr(काष्ठा net_device *ndev)
अणु
	पूर्णांक ret;
	काष्ठा enc28j60_net *priv = netdev_priv(ndev);
	काष्ठा device *dev = &priv->spi->dev;

	mutex_lock(&priv->lock);
	अगर (!priv->hw_enable) अणु
		अगर (netअगर_msg_drv(priv))
			dev_info(dev, "%s: Setting MAC address to %pM\n",
				 ndev->name, ndev->dev_addr);
		/* NOTE: MAC address in ENC28J60 is byte-backward */
		nolock_regb_ग_लिखो(priv, MAADR5, ndev->dev_addr[0]);
		nolock_regb_ग_लिखो(priv, MAADR4, ndev->dev_addr[1]);
		nolock_regb_ग_लिखो(priv, MAADR3, ndev->dev_addr[2]);
		nolock_regb_ग_लिखो(priv, MAADR2, ndev->dev_addr[3]);
		nolock_regb_ग_लिखो(priv, MAADR1, ndev->dev_addr[4]);
		nolock_regb_ग_लिखो(priv, MAADR0, ndev->dev_addr[5]);
		ret = 0;
	पूर्ण अन्यथा अणु
		अगर (netअगर_msg_drv(priv))
			dev_prपूर्णांकk(KERN_DEBUG, dev,
				   "%s() Hardware must be disabled to set Mac address\n",
				   __func__);
		ret = -EBUSY;
	पूर्ण
	mutex_unlock(&priv->lock);
	वापस ret;
पूर्ण

/*
 * Store the new hardware address in dev->dev_addr, and update the MAC.
 */
अटल पूर्णांक enc28j60_set_mac_address(काष्ठा net_device *dev, व्योम *addr)
अणु
	काष्ठा sockaddr *address = addr;

	अगर (netअगर_running(dev))
		वापस -EBUSY;
	अगर (!is_valid_ether_addr(address->sa_data))
		वापस -EADDRNOTAVAIL;

	ether_addr_copy(dev->dev_addr, address->sa_data);
	वापस enc28j60_set_hw_macaddr(dev);
पूर्ण

/*
 * Debug routine to dump useful रेजिस्टर contents
 */
अटल व्योम enc28j60_dump_regs(काष्ठा enc28j60_net *priv, स्थिर अक्षर *msg)
अणु
	काष्ठा device *dev = &priv->spi->dev;

	mutex_lock(&priv->lock);
	dev_prपूर्णांकk(KERN_DEBUG, dev,
		   " %s\n"
		   "HwRevID: 0x%02x\n"
		   "Cntrl: ECON1 ECON2 ESTAT  EIR  EIE\n"
		   "       0x%02x  0x%02x  0x%02x  0x%02x  0x%02x\n"
		   "MAC  : MACON1 MACON3 MACON4\n"
		   "       0x%02x   0x%02x   0x%02x\n"
		   "Rx   : ERXST  ERXND  ERXWRPT ERXRDPT ERXFCON EPKTCNT MAMXFL\n"
		   "       0x%04x 0x%04x 0x%04x  0x%04x  "
		   "0x%02x    0x%02x    0x%04x\n"
		   "Tx   : ETXST  ETXND  MACLCON1 MACLCON2 MAPHSUP\n"
		   "       0x%04x 0x%04x 0x%02x     0x%02x     0x%02x\n",
		   msg, nolock_regb_पढ़ो(priv, EREVID),
		   nolock_regb_पढ़ो(priv, ECON1), nolock_regb_पढ़ो(priv, ECON2),
		   nolock_regb_पढ़ो(priv, ESTAT), nolock_regb_पढ़ो(priv, EIR),
		   nolock_regb_पढ़ो(priv, EIE), nolock_regb_पढ़ो(priv, MACON1),
		   nolock_regb_पढ़ो(priv, MACON3), nolock_regb_पढ़ो(priv, MACON4),
		   nolock_regw_पढ़ो(priv, ERXSTL), nolock_regw_पढ़ो(priv, ERXNDL),
		   nolock_regw_पढ़ो(priv, ERXWRPTL),
		   nolock_regw_पढ़ो(priv, ERXRDPTL),
		   nolock_regb_पढ़ो(priv, ERXFCON),
		   nolock_regb_पढ़ो(priv, EPKTCNT),
		   nolock_regw_पढ़ो(priv, MAMXFLL), nolock_regw_पढ़ो(priv, ETXSTL),
		   nolock_regw_पढ़ो(priv, ETXNDL),
		   nolock_regb_पढ़ो(priv, MACLCON1),
		   nolock_regb_पढ़ो(priv, MACLCON2),
		   nolock_regb_पढ़ो(priv, MAPHSUP));
	mutex_unlock(&priv->lock);
पूर्ण

/*
 * ERXRDPT need to be set always at odd addresses, refer to errata datasheet
 */
अटल u16 erxrdpt_workaround(u16 next_packet_ptr, u16 start, u16 end)
अणु
	u16 erxrdpt;

	अगर ((next_packet_ptr - 1 < start) || (next_packet_ptr - 1 > end))
		erxrdpt = end;
	अन्यथा
		erxrdpt = next_packet_ptr - 1;

	वापस erxrdpt;
पूर्ण

/*
 * Calculate wrap around when पढ़ोing beyond the end of the RX buffer
 */
अटल u16 rx_packet_start(u16 ptr)
अणु
	अगर (ptr + RSV_SIZE > RXEND_INIT)
		वापस (ptr + RSV_SIZE) - (RXEND_INIT - RXSTART_INIT + 1);
	अन्यथा
		वापस ptr + RSV_SIZE;
पूर्ण

अटल व्योम nolock_rxfअगरo_init(काष्ठा enc28j60_net *priv, u16 start, u16 end)
अणु
	काष्ठा device *dev = &priv->spi->dev;
	u16 erxrdpt;

	अगर (start > 0x1FFF || end > 0x1FFF || start > end) अणु
		अगर (netअगर_msg_drv(priv))
			dev_err(dev, "%s(%d, %d) RXFIFO bad parameters!\n",
				__func__, start, end);
		वापस;
	पूर्ण
	/* set receive buffer start + end */
	priv->next_pk_ptr = start;
	nolock_regw_ग_लिखो(priv, ERXSTL, start);
	erxrdpt = erxrdpt_workaround(priv->next_pk_ptr, start, end);
	nolock_regw_ग_लिखो(priv, ERXRDPTL, erxrdpt);
	nolock_regw_ग_लिखो(priv, ERXNDL, end);
पूर्ण

अटल व्योम nolock_txfअगरo_init(काष्ठा enc28j60_net *priv, u16 start, u16 end)
अणु
	काष्ठा device *dev = &priv->spi->dev;

	अगर (start > 0x1FFF || end > 0x1FFF || start > end) अणु
		अगर (netअगर_msg_drv(priv))
			dev_err(dev, "%s(%d, %d) TXFIFO bad parameters!\n",
				__func__, start, end);
		वापस;
	पूर्ण
	/* set transmit buffer start + end */
	nolock_regw_ग_लिखो(priv, ETXSTL, start);
	nolock_regw_ग_लिखो(priv, ETXNDL, end);
पूर्ण

/*
 * Low घातer mode shrinks घातer consumption about 100x, so we'd like
 * the chip to be in that mode whenever it's inactive. (However, we
 * can't stay in low घातer mode during suspend with WOL active.)
 */
अटल व्योम enc28j60_lowघातer(काष्ठा enc28j60_net *priv, bool is_low)
अणु
	काष्ठा device *dev = &priv->spi->dev;

	अगर (netअगर_msg_drv(priv))
		dev_dbg(dev, "%s power...\n", is_low ? "low" : "high");

	mutex_lock(&priv->lock);
	अगर (is_low) अणु
		nolock_reg_bfclr(priv, ECON1, ECON1_RXEN);
		poll_पढ़ोy(priv, ESTAT, ESTAT_RXBUSY, 0);
		poll_पढ़ोy(priv, ECON1, ECON1_TXRTS, 0);
		/* ECON2_VRPS was set during initialization */
		nolock_reg_bfset(priv, ECON2, ECON2_PWRSV);
	पूर्ण अन्यथा अणु
		nolock_reg_bfclr(priv, ECON2, ECON2_PWRSV);
		poll_पढ़ोy(priv, ESTAT, ESTAT_CLKRDY, ESTAT_CLKRDY);
		/* caller sets ECON1_RXEN */
	पूर्ण
	mutex_unlock(&priv->lock);
पूर्ण

अटल पूर्णांक enc28j60_hw_init(काष्ठा enc28j60_net *priv)
अणु
	काष्ठा device *dev = &priv->spi->dev;
	u8 reg;

	अगर (netअगर_msg_drv(priv))
		dev_prपूर्णांकk(KERN_DEBUG, dev, "%s() - %s\n", __func__,
			   priv->full_duplex ? "FullDuplex" : "HalfDuplex");

	mutex_lock(&priv->lock);
	/* first reset the chip */
	enc28j60_soft_reset(priv);
	/* Clear ECON1 */
	spi_ग_लिखो_op(priv, ENC28J60_WRITE_CTRL_REG, ECON1, 0x00);
	priv->bank = 0;
	priv->hw_enable = false;
	priv->tx_retry_count = 0;
	priv->max_pk_counter = 0;
	priv->rxfilter = RXFILTER_NORMAL;
	/* enable address स्वतः increment and voltage regulator घातersave */
	nolock_regb_ग_लिखो(priv, ECON2, ECON2_AUTOINC | ECON2_VRPS);

	nolock_rxfअगरo_init(priv, RXSTART_INIT, RXEND_INIT);
	nolock_txfअगरo_init(priv, TXSTART_INIT, TXEND_INIT);
	mutex_unlock(&priv->lock);

	/*
	 * Check the RevID.
	 * If it's 0x00 or 0xFF probably the enc28j60 is not mounted or
	 * damaged.
	 */
	reg = locked_regb_पढ़ो(priv, EREVID);
	अगर (netअगर_msg_drv(priv))
		dev_info(dev, "chip RevID: 0x%02x\n", reg);
	अगर (reg == 0x00 || reg == 0xff) अणु
		अगर (netअगर_msg_drv(priv))
			dev_prपूर्णांकk(KERN_DEBUG, dev, "%s() Invalid RevId %d\n",
				   __func__, reg);
		वापस 0;
	पूर्ण

	/* शेष filter mode: (unicast OR broadcast) AND crc valid */
	locked_regb_ग_लिखो(priv, ERXFCON,
			    ERXFCON_UCEN | ERXFCON_CRCEN | ERXFCON_BCEN);

	/* enable MAC receive */
	locked_regb_ग_लिखो(priv, MACON1,
			    MACON1_MARXEN | MACON1_TXPAUS | MACON1_RXPAUS);
	/* enable स्वतःmatic padding and CRC operations */
	अगर (priv->full_duplex) अणु
		locked_regb_ग_लिखो(priv, MACON3,
				    MACON3_PADCFG0 | MACON3_TXCRCEN |
				    MACON3_FRMLNEN | MACON3_FULDPX);
		/* set पूर्णांकer-frame gap (non-back-to-back) */
		locked_regb_ग_लिखो(priv, MAIPGL, 0x12);
		/* set पूर्णांकer-frame gap (back-to-back) */
		locked_regb_ग_लिखो(priv, MABBIPG, 0x15);
	पूर्ण अन्यथा अणु
		locked_regb_ग_लिखो(priv, MACON3,
				    MACON3_PADCFG0 | MACON3_TXCRCEN |
				    MACON3_FRMLNEN);
		locked_regb_ग_लिखो(priv, MACON4, 1 << 6);	/* DEFER bit */
		/* set पूर्णांकer-frame gap (non-back-to-back) */
		locked_regw_ग_लिखो(priv, MAIPGL, 0x0C12);
		/* set पूर्णांकer-frame gap (back-to-back) */
		locked_regb_ग_लिखो(priv, MABBIPG, 0x12);
	पूर्ण
	/*
	 * MACLCON1 (शेष)
	 * MACLCON2 (शेष)
	 * Set the maximum packet size which the controller will accept.
	 */
	locked_regw_ग_लिखो(priv, MAMXFLL, MAX_FRAMELEN);

	/* Configure LEDs */
	अगर (!enc28j60_phy_ग_लिखो(priv, PHLCON, ENC28J60_LAMPS_MODE))
		वापस 0;

	अगर (priv->full_duplex) अणु
		अगर (!enc28j60_phy_ग_लिखो(priv, PHCON1, PHCON1_PDPXMD))
			वापस 0;
		अगर (!enc28j60_phy_ग_लिखो(priv, PHCON2, 0x00))
			वापस 0;
	पूर्ण अन्यथा अणु
		अगर (!enc28j60_phy_ग_लिखो(priv, PHCON1, 0x00))
			वापस 0;
		अगर (!enc28j60_phy_ग_लिखो(priv, PHCON2, PHCON2_HDLDIS))
			वापस 0;
	पूर्ण
	अगर (netअगर_msg_hw(priv))
		enc28j60_dump_regs(priv, "Hw initialized.");

	वापस 1;
पूर्ण

अटल व्योम enc28j60_hw_enable(काष्ठा enc28j60_net *priv)
अणु
	काष्ठा device *dev = &priv->spi->dev;

	/* enable पूर्णांकerrupts */
	अगर (netअगर_msg_hw(priv))
		dev_prपूर्णांकk(KERN_DEBUG, dev, "%s() enabling interrupts.\n",
			   __func__);

	enc28j60_phy_ग_लिखो(priv, PHIE, PHIE_PGEIE | PHIE_PLNKIE);

	mutex_lock(&priv->lock);
	nolock_reg_bfclr(priv, EIR, EIR_DMAIF | EIR_LINKIF |
			 EIR_TXIF | EIR_TXERIF | EIR_RXERIF | EIR_PKTIF);
	nolock_regb_ग_लिखो(priv, EIE, EIE_INTIE | EIE_PKTIE | EIE_LINKIE |
			  EIE_TXIE | EIE_TXERIE | EIE_RXERIE);

	/* enable receive logic */
	nolock_reg_bfset(priv, ECON1, ECON1_RXEN);
	priv->hw_enable = true;
	mutex_unlock(&priv->lock);
पूर्ण

अटल व्योम enc28j60_hw_disable(काष्ठा enc28j60_net *priv)
अणु
	mutex_lock(&priv->lock);
	/* disable पूर्णांकerrupts and packet reception */
	nolock_regb_ग_लिखो(priv, EIE, 0x00);
	nolock_reg_bfclr(priv, ECON1, ECON1_RXEN);
	priv->hw_enable = false;
	mutex_unlock(&priv->lock);
पूर्ण

अटल पूर्णांक
enc28j60_setlink(काष्ठा net_device *ndev, u8 स्वतःneg, u16 speed, u8 duplex)
अणु
	काष्ठा enc28j60_net *priv = netdev_priv(ndev);
	पूर्णांक ret = 0;

	अगर (!priv->hw_enable) अणु
		/* link is in low घातer mode now; duplex setting
		 * will take effect on next enc28j60_hw_init().
		 */
		अगर (स्वतःneg == AUTONEG_DISABLE && speed == SPEED_10)
			priv->full_duplex = (duplex == DUPLEX_FULL);
		अन्यथा अणु
			अगर (netअगर_msg_link(priv))
				netdev_warn(ndev, "unsupported link setting\n");
			ret = -EOPNOTSUPP;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (netअगर_msg_link(priv))
			netdev_warn(ndev, "Warning: hw must be disabled to set link mode\n");
		ret = -EBUSY;
	पूर्ण
	वापस ret;
पूर्ण

/*
 * Read the Transmit Status Vector
 */
अटल व्योम enc28j60_पढ़ो_tsv(काष्ठा enc28j60_net *priv, u8 tsv[TSV_SIZE])
अणु
	काष्ठा device *dev = &priv->spi->dev;
	पूर्णांक endptr;

	endptr = locked_regw_पढ़ो(priv, ETXNDL);
	अगर (netअगर_msg_hw(priv))
		dev_prपूर्णांकk(KERN_DEBUG, dev, "reading TSV at addr:0x%04x\n",
			   endptr + 1);
	enc28j60_mem_पढ़ो(priv, endptr + 1, TSV_SIZE, tsv);
पूर्ण

अटल व्योम enc28j60_dump_tsv(काष्ठा enc28j60_net *priv, स्थिर अक्षर *msg,
			      u8 tsv[TSV_SIZE])
अणु
	काष्ठा device *dev = &priv->spi->dev;
	u16 पंचांगp1, पंचांगp2;

	dev_prपूर्णांकk(KERN_DEBUG, dev, "%s - TSV:\n", msg);
	पंचांगp1 = tsv[1];
	पंचांगp1 <<= 8;
	पंचांगp1 |= tsv[0];

	पंचांगp2 = tsv[5];
	पंचांगp2 <<= 8;
	पंचांगp2 |= tsv[4];

	dev_prपूर्णांकk(KERN_DEBUG, dev,
		   "ByteCount: %d, CollisionCount: %d, TotByteOnWire: %d\n",
		   पंचांगp1, tsv[2] & 0x0f, पंचांगp2);
	dev_prपूर्णांकk(KERN_DEBUG, dev,
		   "TxDone: %d, CRCErr:%d, LenChkErr: %d, LenOutOfRange: %d\n",
		   TSV_GETBIT(tsv, TSV_TXDONE),
		   TSV_GETBIT(tsv, TSV_TXCRCERROR),
		   TSV_GETBIT(tsv, TSV_TXLENCHKERROR),
		   TSV_GETBIT(tsv, TSV_TXLENOUTOFRANGE));
	dev_prपूर्णांकk(KERN_DEBUG, dev,
		   "Multicast: %d, Broadcast: %d, PacketDefer: %d, ExDefer: %d\n",
		   TSV_GETBIT(tsv, TSV_TXMULTICAST),
		   TSV_GETBIT(tsv, TSV_TXBROADCAST),
		   TSV_GETBIT(tsv, TSV_TXPACKETDEFER),
		   TSV_GETBIT(tsv, TSV_TXEXDEFER));
	dev_prपूर्णांकk(KERN_DEBUG, dev,
		   "ExCollision: %d, LateCollision: %d, Giant: %d, Underrun: %d\n",
		   TSV_GETBIT(tsv, TSV_TXEXCOLLISION),
		   TSV_GETBIT(tsv, TSV_TXLATECOLLISION),
		   TSV_GETBIT(tsv, TSV_TXGIANT), TSV_GETBIT(tsv, TSV_TXUNDERRUN));
	dev_prपूर्णांकk(KERN_DEBUG, dev,
		   "ControlFrame: %d, PauseFrame: %d, BackPressApp: %d, VLanTagFrame: %d\n",
		   TSV_GETBIT(tsv, TSV_TXCONTROLFRAME),
		   TSV_GETBIT(tsv, TSV_TXPAUSEFRAME),
		   TSV_GETBIT(tsv, TSV_BACKPRESSUREAPP),
		   TSV_GETBIT(tsv, TSV_TXVLANTAGFRAME));
पूर्ण

/*
 * Receive Status vector
 */
अटल व्योम enc28j60_dump_rsv(काष्ठा enc28j60_net *priv, स्थिर अक्षर *msg,
			      u16 pk_ptr, पूर्णांक len, u16 sts)
अणु
	काष्ठा device *dev = &priv->spi->dev;

	dev_prपूर्णांकk(KERN_DEBUG, dev, "%s - NextPk: 0x%04x - RSV:\n", msg, pk_ptr);
	dev_prपूर्णांकk(KERN_DEBUG, dev, "ByteCount: %d, DribbleNibble: %d\n",
		   len, RSV_GETBIT(sts, RSV_DRIBBLENIBBLE));
	dev_prपूर्णांकk(KERN_DEBUG, dev,
		   "RxOK: %d, CRCErr:%d, LenChkErr: %d, LenOutOfRange: %d\n",
		   RSV_GETBIT(sts, RSV_RXOK),
		   RSV_GETBIT(sts, RSV_CRCERROR),
		   RSV_GETBIT(sts, RSV_LENCHECKERR),
		   RSV_GETBIT(sts, RSV_LENOUTOFRANGE));
	dev_prपूर्णांकk(KERN_DEBUG, dev,
		   "Multicast: %d, Broadcast: %d, LongDropEvent: %d, CarrierEvent: %d\n",
		   RSV_GETBIT(sts, RSV_RXMULTICAST),
		   RSV_GETBIT(sts, RSV_RXBROADCAST),
		   RSV_GETBIT(sts, RSV_RXLONGEVDROPEV),
		   RSV_GETBIT(sts, RSV_CARRIEREV));
	dev_prपूर्णांकk(KERN_DEBUG, dev,
		   "ControlFrame: %d, PauseFrame: %d, UnknownOp: %d, VLanTagFrame: %d\n",
		   RSV_GETBIT(sts, RSV_RXCONTROLFRAME),
		   RSV_GETBIT(sts, RSV_RXPAUSEFRAME),
		   RSV_GETBIT(sts, RSV_RXUNKNOWNOPCODE),
		   RSV_GETBIT(sts, RSV_RXTYPEVLAN));
पूर्ण

अटल व्योम dump_packet(स्थिर अक्षर *msg, पूर्णांक len, स्थिर अक्षर *data)
अणु
	prपूर्णांकk(KERN_DEBUG DRV_NAME ": %s - packet len:%d\n", msg, len);
	prपूर्णांक_hex_dump(KERN_DEBUG, "pk data: ", DUMP_PREFIX_OFFSET, 16, 1,
			data, len, true);
पूर्ण

/*
 * Hardware receive function.
 * Read the buffer memory, update the FIFO poपूर्णांकer to मुक्त the buffer,
 * check the status vector and decrement the packet counter.
 */
अटल व्योम enc28j60_hw_rx(काष्ठा net_device *ndev)
अणु
	काष्ठा enc28j60_net *priv = netdev_priv(ndev);
	काष्ठा device *dev = &priv->spi->dev;
	काष्ठा sk_buff *skb = शून्य;
	u16 erxrdpt, next_packet, rxstat;
	u8 rsv[RSV_SIZE];
	पूर्णांक len;

	अगर (netअगर_msg_rx_status(priv))
		netdev_prपूर्णांकk(KERN_DEBUG, ndev, "RX pk_addr:0x%04x\n",
			      priv->next_pk_ptr);

	अगर (unlikely(priv->next_pk_ptr > RXEND_INIT)) अणु
		अगर (netअगर_msg_rx_err(priv))
			netdev_err(ndev, "%s() Invalid packet address!! 0x%04x\n",
				   __func__, priv->next_pk_ptr);
		/* packet address corrupted: reset RX logic */
		mutex_lock(&priv->lock);
		nolock_reg_bfclr(priv, ECON1, ECON1_RXEN);
		nolock_reg_bfset(priv, ECON1, ECON1_RXRST);
		nolock_reg_bfclr(priv, ECON1, ECON1_RXRST);
		nolock_rxfअगरo_init(priv, RXSTART_INIT, RXEND_INIT);
		nolock_reg_bfclr(priv, EIR, EIR_RXERIF);
		nolock_reg_bfset(priv, ECON1, ECON1_RXEN);
		mutex_unlock(&priv->lock);
		ndev->stats.rx_errors++;
		वापस;
	पूर्ण
	/* Read next packet poपूर्णांकer and rx status vector */
	enc28j60_mem_पढ़ो(priv, priv->next_pk_ptr, माप(rsv), rsv);

	next_packet = rsv[1];
	next_packet <<= 8;
	next_packet |= rsv[0];

	len = rsv[3];
	len <<= 8;
	len |= rsv[2];

	rxstat = rsv[5];
	rxstat <<= 8;
	rxstat |= rsv[4];

	अगर (netअगर_msg_rx_status(priv))
		enc28j60_dump_rsv(priv, __func__, next_packet, len, rxstat);

	अगर (!RSV_GETBIT(rxstat, RSV_RXOK) || len > MAX_FRAMELEN) अणु
		अगर (netअगर_msg_rx_err(priv))
			netdev_err(ndev, "Rx Error (%04x)\n", rxstat);
		ndev->stats.rx_errors++;
		अगर (RSV_GETBIT(rxstat, RSV_CRCERROR))
			ndev->stats.rx_crc_errors++;
		अगर (RSV_GETBIT(rxstat, RSV_LENCHECKERR))
			ndev->stats.rx_frame_errors++;
		अगर (len > MAX_FRAMELEN)
			ndev->stats.rx_over_errors++;
	पूर्ण अन्यथा अणु
		skb = netdev_alloc_skb(ndev, len + NET_IP_ALIGN);
		अगर (!skb) अणु
			अगर (netअगर_msg_rx_err(priv))
				netdev_err(ndev, "out of memory for Rx'd frame\n");
			ndev->stats.rx_dropped++;
		पूर्ण अन्यथा अणु
			skb_reserve(skb, NET_IP_ALIGN);
			/* copy the packet from the receive buffer */
			enc28j60_mem_पढ़ो(priv,
				rx_packet_start(priv->next_pk_ptr),
				len, skb_put(skb, len));
			अगर (netअगर_msg_pktdata(priv))
				dump_packet(__func__, skb->len, skb->data);
			skb->protocol = eth_type_trans(skb, ndev);
			/* update statistics */
			ndev->stats.rx_packets++;
			ndev->stats.rx_bytes += len;
			netअगर_rx_ni(skb);
		पूर्ण
	पूर्ण
	/*
	 * Move the RX पढ़ो poपूर्णांकer to the start of the next
	 * received packet.
	 * This मुक्तs the memory we just पढ़ो out.
	 */
	erxrdpt = erxrdpt_workaround(next_packet, RXSTART_INIT, RXEND_INIT);
	अगर (netअगर_msg_hw(priv))
		dev_prपूर्णांकk(KERN_DEBUG, dev, "%s() ERXRDPT:0x%04x\n",
			   __func__, erxrdpt);

	mutex_lock(&priv->lock);
	nolock_regw_ग_लिखो(priv, ERXRDPTL, erxrdpt);
#अगर_घोषित CONFIG_ENC28J60_WRITEVERIFY
	अगर (netअगर_msg_drv(priv)) अणु
		u16 reg;
		reg = nolock_regw_पढ़ो(priv, ERXRDPTL);
		अगर (reg != erxrdpt)
			dev_prपूर्णांकk(KERN_DEBUG, dev,
				   "%s() ERXRDPT verify error (0x%04x - 0x%04x)\n",
				   __func__, reg, erxrdpt);
	पूर्ण
#पूर्ण_अगर
	priv->next_pk_ptr = next_packet;
	/* we are करोne with this packet, decrement the packet counter */
	nolock_reg_bfset(priv, ECON2, ECON2_PKTDEC);
	mutex_unlock(&priv->lock);
पूर्ण

/*
 * Calculate मुक्त space in RxFIFO
 */
अटल पूर्णांक enc28j60_get_मुक्त_rxfअगरo(काष्ठा enc28j60_net *priv)
अणु
	काष्ठा net_device *ndev = priv->netdev;
	पूर्णांक epkcnt, erxst, erxnd, erxwr, erxrd;
	पूर्णांक मुक्त_space;

	mutex_lock(&priv->lock);
	epkcnt = nolock_regb_पढ़ो(priv, EPKTCNT);
	अगर (epkcnt >= 255)
		मुक्त_space = -1;
	अन्यथा अणु
		erxst = nolock_regw_पढ़ो(priv, ERXSTL);
		erxnd = nolock_regw_पढ़ो(priv, ERXNDL);
		erxwr = nolock_regw_पढ़ो(priv, ERXWRPTL);
		erxrd = nolock_regw_पढ़ो(priv, ERXRDPTL);

		अगर (erxwr > erxrd)
			मुक्त_space = (erxnd - erxst) - (erxwr - erxrd);
		अन्यथा अगर (erxwr == erxrd)
			मुक्त_space = (erxnd - erxst);
		अन्यथा
			मुक्त_space = erxrd - erxwr - 1;
	पूर्ण
	mutex_unlock(&priv->lock);
	अगर (netअगर_msg_rx_status(priv))
		netdev_prपूर्णांकk(KERN_DEBUG, ndev, "%s() free_space = %d\n",
			      __func__, मुक्त_space);
	वापस मुक्त_space;
पूर्ण

/*
 * Access the PHY to determine link status
 */
अटल व्योम enc28j60_check_link_status(काष्ठा net_device *ndev)
अणु
	काष्ठा enc28j60_net *priv = netdev_priv(ndev);
	काष्ठा device *dev = &priv->spi->dev;
	u16 reg;
	पूर्णांक duplex;

	reg = enc28j60_phy_पढ़ो(priv, PHSTAT2);
	अगर (netअगर_msg_hw(priv))
		dev_prपूर्णांकk(KERN_DEBUG, dev,
			   "%s() PHSTAT1: %04x, PHSTAT2: %04x\n", __func__,
			   enc28j60_phy_पढ़ो(priv, PHSTAT1), reg);
	duplex = reg & PHSTAT2_DPXSTAT;

	अगर (reg & PHSTAT2_LSTAT) अणु
		netअगर_carrier_on(ndev);
		अगर (netअगर_msg_अगरup(priv))
			netdev_info(ndev, "link up - %s\n",
				    duplex ? "Full duplex" : "Half duplex");
	पूर्ण अन्यथा अणु
		अगर (netअगर_msg_अगरकरोwn(priv))
			netdev_info(ndev, "link down\n");
		netअगर_carrier_off(ndev);
	पूर्ण
पूर्ण

अटल व्योम enc28j60_tx_clear(काष्ठा net_device *ndev, bool err)
अणु
	काष्ठा enc28j60_net *priv = netdev_priv(ndev);

	अगर (err)
		ndev->stats.tx_errors++;
	अन्यथा
		ndev->stats.tx_packets++;

	अगर (priv->tx_skb) अणु
		अगर (!err)
			ndev->stats.tx_bytes += priv->tx_skb->len;
		dev_kमुक्त_skb(priv->tx_skb);
		priv->tx_skb = शून्य;
	पूर्ण
	locked_reg_bfclr(priv, ECON1, ECON1_TXRTS);
	netअगर_wake_queue(ndev);
पूर्ण

/*
 * RX handler
 * Ignore PKTIF because is unreliable! (Look at the errata datasheet)
 * Check EPKTCNT is the suggested workaround.
 * We करोn't need to clear पूर्णांकerrupt flag, स्वतःmatically करोne when
 * enc28j60_hw_rx() decrements the packet counter.
 * Returns how many packet processed.
 */
अटल पूर्णांक enc28j60_rx_पूर्णांकerrupt(काष्ठा net_device *ndev)
अणु
	काष्ठा enc28j60_net *priv = netdev_priv(ndev);
	पूर्णांक pk_counter, ret;

	pk_counter = locked_regb_पढ़ो(priv, EPKTCNT);
	अगर (pk_counter && netअगर_msg_पूर्णांकr(priv))
		netdev_prपूर्णांकk(KERN_DEBUG, ndev, "intRX, pk_cnt: %d\n",
			      pk_counter);
	अगर (pk_counter > priv->max_pk_counter) अणु
		/* update statistics */
		priv->max_pk_counter = pk_counter;
		अगर (netअगर_msg_rx_status(priv) && priv->max_pk_counter > 1)
			netdev_prपूर्णांकk(KERN_DEBUG, ndev, "RX max_pk_cnt: %d\n",
				      priv->max_pk_counter);
	पूर्ण
	ret = pk_counter;
	जबतक (pk_counter-- > 0)
		enc28j60_hw_rx(ndev);

	वापस ret;
पूर्ण

अटल व्योम enc28j60_irq_work_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा enc28j60_net *priv =
		container_of(work, काष्ठा enc28j60_net, irq_work);
	काष्ठा net_device *ndev = priv->netdev;
	पूर्णांक पूर्णांकflags, loop;

	/* disable further पूर्णांकerrupts */
	locked_reg_bfclr(priv, EIE, EIE_INTIE);

	करो अणु
		loop = 0;
		पूर्णांकflags = locked_regb_पढ़ो(priv, EIR);
		/* DMA पूर्णांकerrupt handler (not currently used) */
		अगर ((पूर्णांकflags & EIR_DMAIF) != 0) अणु
			loop++;
			अगर (netअगर_msg_पूर्णांकr(priv))
				netdev_prपूर्णांकk(KERN_DEBUG, ndev, "intDMA(%d)\n",
					      loop);
			locked_reg_bfclr(priv, EIR, EIR_DMAIF);
		पूर्ण
		/* LINK changed handler */
		अगर ((पूर्णांकflags & EIR_LINKIF) != 0) अणु
			loop++;
			अगर (netअगर_msg_पूर्णांकr(priv))
				netdev_prपूर्णांकk(KERN_DEBUG, ndev, "intLINK(%d)\n",
					      loop);
			enc28j60_check_link_status(ndev);
			/* पढ़ो PHIR to clear the flag */
			enc28j60_phy_पढ़ो(priv, PHIR);
		पूर्ण
		/* TX complete handler */
		अगर (((पूर्णांकflags & EIR_TXIF) != 0) &&
		    ((पूर्णांकflags & EIR_TXERIF) == 0)) अणु
			bool err = false;
			loop++;
			अगर (netअगर_msg_पूर्णांकr(priv))
				netdev_prपूर्णांकk(KERN_DEBUG, ndev, "intTX(%d)\n",
					      loop);
			priv->tx_retry_count = 0;
			अगर (locked_regb_पढ़ो(priv, ESTAT) & ESTAT_TXABRT) अणु
				अगर (netअगर_msg_tx_err(priv))
					netdev_err(ndev, "Tx Error (aborted)\n");
				err = true;
			पूर्ण
			अगर (netअगर_msg_tx_करोne(priv)) अणु
				u8 tsv[TSV_SIZE];
				enc28j60_पढ़ो_tsv(priv, tsv);
				enc28j60_dump_tsv(priv, "Tx Done", tsv);
			पूर्ण
			enc28j60_tx_clear(ndev, err);
			locked_reg_bfclr(priv, EIR, EIR_TXIF);
		पूर्ण
		/* TX Error handler */
		अगर ((पूर्णांकflags & EIR_TXERIF) != 0) अणु
			u8 tsv[TSV_SIZE];

			loop++;
			अगर (netअगर_msg_पूर्णांकr(priv))
				netdev_prपूर्णांकk(KERN_DEBUG, ndev, "intTXErr(%d)\n",
					      loop);
			locked_reg_bfclr(priv, ECON1, ECON1_TXRTS);
			enc28j60_पढ़ो_tsv(priv, tsv);
			अगर (netअगर_msg_tx_err(priv))
				enc28j60_dump_tsv(priv, "Tx Error", tsv);
			/* Reset TX logic */
			mutex_lock(&priv->lock);
			nolock_reg_bfset(priv, ECON1, ECON1_TXRST);
			nolock_reg_bfclr(priv, ECON1, ECON1_TXRST);
			nolock_txfअगरo_init(priv, TXSTART_INIT, TXEND_INIT);
			mutex_unlock(&priv->lock);
			/* Transmit Late collision check क्रम retransmit */
			अगर (TSV_GETBIT(tsv, TSV_TXLATECOLLISION)) अणु
				अगर (netअगर_msg_tx_err(priv))
					netdev_prपूर्णांकk(KERN_DEBUG, ndev,
						      "LateCollision TXErr (%d)\n",
						      priv->tx_retry_count);
				अगर (priv->tx_retry_count++ < MAX_TX_RETRYCOUNT)
					locked_reg_bfset(priv, ECON1,
							   ECON1_TXRTS);
				अन्यथा
					enc28j60_tx_clear(ndev, true);
			पूर्ण अन्यथा
				enc28j60_tx_clear(ndev, true);
			locked_reg_bfclr(priv, EIR, EIR_TXERIF | EIR_TXIF);
		पूर्ण
		/* RX Error handler */
		अगर ((पूर्णांकflags & EIR_RXERIF) != 0) अणु
			loop++;
			अगर (netअगर_msg_पूर्णांकr(priv))
				netdev_prपूर्णांकk(KERN_DEBUG, ndev, "intRXErr(%d)\n",
					      loop);
			/* Check मुक्त FIFO space to flag RX overrun */
			अगर (enc28j60_get_मुक्त_rxfअगरo(priv) <= 0) अणु
				अगर (netअगर_msg_rx_err(priv))
					netdev_prपूर्णांकk(KERN_DEBUG, ndev, "RX Overrun\n");
				ndev->stats.rx_dropped++;
			पूर्ण
			locked_reg_bfclr(priv, EIR, EIR_RXERIF);
		पूर्ण
		/* RX handler */
		अगर (enc28j60_rx_पूर्णांकerrupt(ndev))
			loop++;
	पूर्ण जबतक (loop);

	/* re-enable पूर्णांकerrupts */
	locked_reg_bfset(priv, EIE, EIE_INTIE);
पूर्ण

/*
 * Hardware transmit function.
 * Fill the buffer memory and send the contents of the transmit buffer
 * onto the network
 */
अटल व्योम enc28j60_hw_tx(काष्ठा enc28j60_net *priv)
अणु
	काष्ठा net_device *ndev = priv->netdev;

	BUG_ON(!priv->tx_skb);

	अगर (netअगर_msg_tx_queued(priv))
		netdev_prपूर्णांकk(KERN_DEBUG, ndev, "Tx Packet Len:%d\n",
			      priv->tx_skb->len);

	अगर (netअगर_msg_pktdata(priv))
		dump_packet(__func__,
			    priv->tx_skb->len, priv->tx_skb->data);
	enc28j60_packet_ग_लिखो(priv, priv->tx_skb->len, priv->tx_skb->data);

#अगर_घोषित CONFIG_ENC28J60_WRITEVERIFY
	/* पढ़ोback and verअगरy written data */
	अगर (netअगर_msg_drv(priv)) अणु
		काष्ठा device *dev = &priv->spi->dev;
		पूर्णांक test_len, k;
		u8 test_buf[64]; /* limit the test to the first 64 bytes */
		पूर्णांक okflag;

		test_len = priv->tx_skb->len;
		अगर (test_len > माप(test_buf))
			test_len = माप(test_buf);

		/* + 1 to skip control byte */
		enc28j60_mem_पढ़ो(priv, TXSTART_INIT + 1, test_len, test_buf);
		okflag = 1;
		क्रम (k = 0; k < test_len; k++) अणु
			अगर (priv->tx_skb->data[k] != test_buf[k]) अणु
				dev_prपूर्णांकk(KERN_DEBUG, dev,
					   "Error, %d location differ: 0x%02x-0x%02x\n",
					   k, priv->tx_skb->data[k], test_buf[k]);
				okflag = 0;
			पूर्ण
		पूर्ण
		अगर (!okflag)
			dev_prपूर्णांकk(KERN_DEBUG, dev, "Tx write buffer, verify ERROR!\n");
	पूर्ण
#पूर्ण_अगर
	/* set TX request flag */
	locked_reg_bfset(priv, ECON1, ECON1_TXRTS);
पूर्ण

अटल netdev_tx_t enc28j60_send_packet(काष्ठा sk_buff *skb,
					काष्ठा net_device *dev)
अणु
	काष्ठा enc28j60_net *priv = netdev_priv(dev);

	/* If some error occurs जबतक trying to transmit this
	 * packet, you should वापस '1' from this function.
	 * In such a हाल you _may not_ करो anything to the
	 * SKB, it is still owned by the network queueing
	 * layer when an error is वापसed. This means you
	 * may not modअगरy any SKB fields, you may not मुक्त
	 * the SKB, etc.
	 */
	netअगर_stop_queue(dev);

	/* Remember the skb क्रम deferred processing */
	priv->tx_skb = skb;
	schedule_work(&priv->tx_work);

	वापस NETDEV_TX_OK;
पूर्ण

अटल व्योम enc28j60_tx_work_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा enc28j60_net *priv =
		container_of(work, काष्ठा enc28j60_net, tx_work);

	/* actual delivery of data */
	enc28j60_hw_tx(priv);
पूर्ण

अटल irqवापस_t enc28j60_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा enc28j60_net *priv = dev_id;

	/*
	 * Can't करो anything in पूर्णांकerrupt context because we need to
	 * block (spi_sync() is blocking) so fire of the पूर्णांकerrupt
	 * handling workqueue.
	 * Remember that we access enc28j60 रेजिस्टरs through SPI bus
	 * via spi_sync() call.
	 */
	schedule_work(&priv->irq_work);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम enc28j60_tx_समयout(काष्ठा net_device *ndev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा enc28j60_net *priv = netdev_priv(ndev);

	अगर (netअगर_msg_समयr(priv))
		netdev_err(ndev, "tx timeout\n");

	ndev->stats.tx_errors++;
	/* can't restart safely under softirq */
	schedule_work(&priv->restart_work);
पूर्ण

/*
 * Open/initialize the board. This is called (in the current kernel)
 * someसमय after booting when the 'ifconfig' program is run.
 *
 * This routine should set everything up anew at each खोलो, even
 * रेजिस्टरs that "should" only need to be set once at boot, so that
 * there is non-reboot way to recover अगर something goes wrong.
 */
अटल पूर्णांक enc28j60_net_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा enc28j60_net *priv = netdev_priv(dev);

	अगर (!is_valid_ether_addr(dev->dev_addr)) अणु
		अगर (netअगर_msg_अगरup(priv))
			netdev_err(dev, "invalid MAC address %pM\n", dev->dev_addr);
		वापस -EADDRNOTAVAIL;
	पूर्ण
	/* Reset the hardware here (and take it out of low घातer mode) */
	enc28j60_lowघातer(priv, false);
	enc28j60_hw_disable(priv);
	अगर (!enc28j60_hw_init(priv)) अणु
		अगर (netअगर_msg_अगरup(priv))
			netdev_err(dev, "hw_reset() failed\n");
		वापस -EINVAL;
	पूर्ण
	/* Update the MAC address (in हाल user has changed it) */
	enc28j60_set_hw_macaddr(dev);
	/* Enable पूर्णांकerrupts */
	enc28j60_hw_enable(priv);
	/* check link status */
	enc28j60_check_link_status(dev);
	/* We are now पढ़ोy to accept transmit requests from
	 * the queueing layer of the networking.
	 */
	netअगर_start_queue(dev);

	वापस 0;
पूर्ण

/* The inverse routine to net_खोलो(). */
अटल पूर्णांक enc28j60_net_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा enc28j60_net *priv = netdev_priv(dev);

	enc28j60_hw_disable(priv);
	enc28j60_lowघातer(priv, true);
	netअगर_stop_queue(dev);

	वापस 0;
पूर्ण

/*
 * Set or clear the multicast filter क्रम this adapter
 * num_addrs == -1	Promiscuous mode, receive all packets
 * num_addrs == 0	Normal mode, filter out multicast packets
 * num_addrs > 0	Multicast mode, receive normal and MC packets
 */
अटल व्योम enc28j60_set_multicast_list(काष्ठा net_device *dev)
अणु
	काष्ठा enc28j60_net *priv = netdev_priv(dev);
	पूर्णांक oldfilter = priv->rxfilter;

	अगर (dev->flags & IFF_PROMISC) अणु
		अगर (netअगर_msg_link(priv))
			netdev_info(dev, "promiscuous mode\n");
		priv->rxfilter = RXFILTER_PROMISC;
	पूर्ण अन्यथा अगर ((dev->flags & IFF_ALLMULTI) || !netdev_mc_empty(dev)) अणु
		अगर (netअगर_msg_link(priv))
			netdev_info(dev, "%smulticast mode\n",
				    (dev->flags & IFF_ALLMULTI) ? "all-" : "");
		priv->rxfilter = RXFILTER_MULTI;
	पूर्ण अन्यथा अणु
		अगर (netअगर_msg_link(priv))
			netdev_info(dev, "normal mode\n");
		priv->rxfilter = RXFILTER_NORMAL;
	पूर्ण

	अगर (oldfilter != priv->rxfilter)
		schedule_work(&priv->setrx_work);
पूर्ण

अटल व्योम enc28j60_setrx_work_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा enc28j60_net *priv =
		container_of(work, काष्ठा enc28j60_net, setrx_work);
	काष्ठा device *dev = &priv->spi->dev;

	अगर (priv->rxfilter == RXFILTER_PROMISC) अणु
		अगर (netअगर_msg_drv(priv))
			dev_prपूर्णांकk(KERN_DEBUG, dev, "promiscuous mode\n");
		locked_regb_ग_लिखो(priv, ERXFCON, 0x00);
	पूर्ण अन्यथा अगर (priv->rxfilter == RXFILTER_MULTI) अणु
		अगर (netअगर_msg_drv(priv))
			dev_prपूर्णांकk(KERN_DEBUG, dev, "multicast mode\n");
		locked_regb_ग_लिखो(priv, ERXFCON,
					ERXFCON_UCEN | ERXFCON_CRCEN |
					ERXFCON_BCEN | ERXFCON_MCEN);
	पूर्ण अन्यथा अणु
		अगर (netअगर_msg_drv(priv))
			dev_prपूर्णांकk(KERN_DEBUG, dev, "normal mode\n");
		locked_regb_ग_लिखो(priv, ERXFCON,
					ERXFCON_UCEN | ERXFCON_CRCEN |
					ERXFCON_BCEN);
	पूर्ण
पूर्ण

अटल व्योम enc28j60_restart_work_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा enc28j60_net *priv =
			container_of(work, काष्ठा enc28j60_net, restart_work);
	काष्ठा net_device *ndev = priv->netdev;
	पूर्णांक ret;

	rtnl_lock();
	अगर (netअगर_running(ndev)) अणु
		enc28j60_net_बंद(ndev);
		ret = enc28j60_net_खोलो(ndev);
		अगर (unlikely(ret)) अणु
			netdev_info(ndev, "could not restart %d\n", ret);
			dev_बंद(ndev);
		पूर्ण
	पूर्ण
	rtnl_unlock();
पूर्ण

/* ......................... ETHTOOL SUPPORT ........................... */

अटल व्योम
enc28j60_get_drvinfo(काष्ठा net_device *dev, काष्ठा ethtool_drvinfo *info)
अणु
	strlcpy(info->driver, DRV_NAME, माप(info->driver));
	strlcpy(info->version, DRV_VERSION, माप(info->version));
	strlcpy(info->bus_info,
		dev_name(dev->dev.parent), माप(info->bus_info));
पूर्ण

अटल पूर्णांक
enc28j60_get_link_ksettings(काष्ठा net_device *dev,
			    काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा enc28j60_net *priv = netdev_priv(dev);

	ethtool_link_ksettings_zero_link_mode(cmd, supported);
	ethtool_link_ksettings_add_link_mode(cmd, supported, 10baseT_Half);
	ethtool_link_ksettings_add_link_mode(cmd, supported, 10baseT_Full);
	ethtool_link_ksettings_add_link_mode(cmd, supported, TP);

	cmd->base.speed = SPEED_10;
	cmd->base.duplex = priv->full_duplex ? DUPLEX_FULL : DUPLEX_HALF;
	cmd->base.port	= PORT_TP;
	cmd->base.स्वतःneg = AUTONEG_DISABLE;

	वापस 0;
पूर्ण

अटल पूर्णांक
enc28j60_set_link_ksettings(काष्ठा net_device *dev,
			    स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	वापस enc28j60_setlink(dev, cmd->base.स्वतःneg,
				cmd->base.speed, cmd->base.duplex);
पूर्ण

अटल u32 enc28j60_get_msglevel(काष्ठा net_device *dev)
अणु
	काष्ठा enc28j60_net *priv = netdev_priv(dev);
	वापस priv->msg_enable;
पूर्ण

अटल व्योम enc28j60_set_msglevel(काष्ठा net_device *dev, u32 val)
अणु
	काष्ठा enc28j60_net *priv = netdev_priv(dev);
	priv->msg_enable = val;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops enc28j60_ethtool_ops = अणु
	.get_drvinfo	= enc28j60_get_drvinfo,
	.get_msglevel	= enc28j60_get_msglevel,
	.set_msglevel	= enc28j60_set_msglevel,
	.get_link_ksettings = enc28j60_get_link_ksettings,
	.set_link_ksettings = enc28j60_set_link_ksettings,
पूर्ण;

अटल पूर्णांक enc28j60_chipset_init(काष्ठा net_device *dev)
अणु
	काष्ठा enc28j60_net *priv = netdev_priv(dev);

	वापस enc28j60_hw_init(priv);
पूर्ण

अटल स्थिर काष्ठा net_device_ops enc28j60_netdev_ops = अणु
	.nकरो_खोलो		= enc28j60_net_खोलो,
	.nकरो_stop		= enc28j60_net_बंद,
	.nकरो_start_xmit		= enc28j60_send_packet,
	.nकरो_set_rx_mode	= enc28j60_set_multicast_list,
	.nकरो_set_mac_address	= enc28j60_set_mac_address,
	.nकरो_tx_समयout		= enc28j60_tx_समयout,
	.nकरो_validate_addr	= eth_validate_addr,
पूर्ण;

अटल पूर्णांक enc28j60_probe(काष्ठा spi_device *spi)
अणु
	अचिन्हित अक्षर macaddr[ETH_ALEN];
	काष्ठा net_device *dev;
	काष्ठा enc28j60_net *priv;
	पूर्णांक ret = 0;

	अगर (netअगर_msg_drv(&debug))
		dev_info(&spi->dev, "Ethernet driver %s loaded\n", DRV_VERSION);

	dev = alloc_etherdev(माप(काष्ठा enc28j60_net));
	अगर (!dev) अणु
		ret = -ENOMEM;
		जाओ error_alloc;
	पूर्ण
	priv = netdev_priv(dev);

	priv->netdev = dev;	/* priv to netdev reference */
	priv->spi = spi;	/* priv to spi reference */
	priv->msg_enable = netअगर_msg_init(debug.msg_enable, ENC28J60_MSG_DEFAULT);
	mutex_init(&priv->lock);
	INIT_WORK(&priv->tx_work, enc28j60_tx_work_handler);
	INIT_WORK(&priv->setrx_work, enc28j60_setrx_work_handler);
	INIT_WORK(&priv->irq_work, enc28j60_irq_work_handler);
	INIT_WORK(&priv->restart_work, enc28j60_restart_work_handler);
	spi_set_drvdata(spi, priv);	/* spi to priv reference */
	SET_NETDEV_DEV(dev, &spi->dev);

	अगर (!enc28j60_chipset_init(dev)) अणु
		अगर (netअगर_msg_probe(priv))
			dev_info(&spi->dev, "chip not found\n");
		ret = -EIO;
		जाओ error_irq;
	पूर्ण

	अगर (device_get_mac_address(&spi->dev, macaddr, माप(macaddr)))
		ether_addr_copy(dev->dev_addr, macaddr);
	अन्यथा
		eth_hw_addr_अक्रमom(dev);
	enc28j60_set_hw_macaddr(dev);

	/* Board setup must set the relevant edge trigger type;
	 * level triggers won't currently work.
	 */
	ret = request_irq(spi->irq, enc28j60_irq, 0, DRV_NAME, priv);
	अगर (ret < 0) अणु
		अगर (netअगर_msg_probe(priv))
			dev_err(&spi->dev, "request irq %d failed (ret = %d)\n",
				spi->irq, ret);
		जाओ error_irq;
	पूर्ण

	dev->अगर_port = IF_PORT_10BASET;
	dev->irq = spi->irq;
	dev->netdev_ops = &enc28j60_netdev_ops;
	dev->watchकरोg_समयo = TX_TIMEOUT;
	dev->ethtool_ops = &enc28j60_ethtool_ops;

	enc28j60_lowघातer(priv, true);

	ret = रेजिस्टर_netdev(dev);
	अगर (ret) अणु
		अगर (netअगर_msg_probe(priv))
			dev_err(&spi->dev, "register netdev failed (ret = %d)\n",
				ret);
		जाओ error_रेजिस्टर;
	पूर्ण

	वापस 0;

error_रेजिस्टर:
	मुक्त_irq(spi->irq, priv);
error_irq:
	मुक्त_netdev(dev);
error_alloc:
	वापस ret;
पूर्ण

अटल पूर्णांक enc28j60_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा enc28j60_net *priv = spi_get_drvdata(spi);

	unरेजिस्टर_netdev(priv->netdev);
	मुक्त_irq(spi->irq, priv);
	मुक्त_netdev(priv->netdev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id enc28j60_dt_ids[] = अणु
	अणु .compatible = "microchip,enc28j60" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, enc28j60_dt_ids);

अटल काष्ठा spi_driver enc28j60_driver = अणु
	.driver = अणु
		.name = DRV_NAME,
		.of_match_table = enc28j60_dt_ids,
	 पूर्ण,
	.probe = enc28j60_probe,
	.हटाओ = enc28j60_हटाओ,
पूर्ण;
module_spi_driver(enc28j60_driver);

MODULE_DESCRIPTION(DRV_NAME " ethernet driver");
MODULE_AUTHOR("Claudio Lanconelli <lanconelli.claudio@eptar.com>");
MODULE_LICENSE("GPL");
module_param_named(debug, debug.msg_enable, पूर्णांक, 0);
MODULE_PARM_DESC(debug, "Debug verbosity level in amount of bits set (0=none, ..., 31=all)");
MODULE_ALIAS("spi:" DRV_NAME);
