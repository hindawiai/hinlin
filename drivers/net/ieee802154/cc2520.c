<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Driver क्रम TI CC2520 802.15.4 Wireless-PAN Networking controller
 *
 * Copyright (C) 2014 Varka Bhadram <varkab@cdac.in>
 *		      Md.Jamal Mohiuddin <mjmohiuddin@cdac.in>
 *		      P Sowjanya <sowjanyap@cdac.in>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/delay.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/cc2520.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/ieee802154.h>
#समावेश <linux/crc-ccitt.h>
#समावेश <यंत्र/unaligned.h>

#समावेश <net/mac802154.h>
#समावेश <net/cfg802154.h>

#घोषणा	SPI_COMMAND_BUFFER	3
#घोषणा	HIGH			1
#घोषणा	LOW			0
#घोषणा	STATE_IDLE		0
#घोषणा	RSSI_VALID		0
#घोषणा	RSSI_OFFSET		78

#घोषणा	CC2520_RAM_SIZE		640
#घोषणा	CC2520_FIFO_SIZE	128

#घोषणा	CC2520RAM_TXFIFO	0x100
#घोषणा	CC2520RAM_RXFIFO	0x180
#घोषणा	CC2520RAM_IEEEADDR	0x3EA
#घोषणा	CC2520RAM_PANID		0x3F2
#घोषणा	CC2520RAM_SHORTADDR	0x3F4

#घोषणा	CC2520_FREG_MASK	0x3F

/* status byte values */
#घोषणा	CC2520_STATUS_XOSC32M_STABLE	BIT(7)
#घोषणा	CC2520_STATUS_RSSI_VALID	BIT(6)
#घोषणा	CC2520_STATUS_TX_UNDERFLOW	BIT(3)

/* IEEE-802.15.4 defined स्थिरants (2.4 GHz logical channels) */
#घोषणा	CC2520_MINCHANNEL		11
#घोषणा	CC2520_MAXCHANNEL		26
#घोषणा	CC2520_CHANNEL_SPACING		5

/* command strobes */
#घोषणा	CC2520_CMD_SNOP			0x00
#घोषणा	CC2520_CMD_IBUFLD		0x02
#घोषणा	CC2520_CMD_SIBUFEX		0x03
#घोषणा	CC2520_CMD_SSAMPLECCA		0x04
#घोषणा	CC2520_CMD_SRES			0x0f
#घोषणा	CC2520_CMD_MEMORY_MASK		0x0f
#घोषणा	CC2520_CMD_MEMORY_READ		0x10
#घोषणा	CC2520_CMD_MEMORY_WRITE		0x20
#घोषणा	CC2520_CMD_RXBUF		0x30
#घोषणा	CC2520_CMD_RXBUFCP		0x38
#घोषणा	CC2520_CMD_RXBUFMOV		0x32
#घोषणा	CC2520_CMD_TXBUF		0x3A
#घोषणा	CC2520_CMD_TXBUFCP		0x3E
#घोषणा	CC2520_CMD_RANDOM		0x3C
#घोषणा	CC2520_CMD_SXOSCON		0x40
#घोषणा	CC2520_CMD_STXCAL		0x41
#घोषणा	CC2520_CMD_SRXON		0x42
#घोषणा	CC2520_CMD_STXON		0x43
#घोषणा	CC2520_CMD_STXONCCA		0x44
#घोषणा	CC2520_CMD_SRFOFF		0x45
#घोषणा	CC2520_CMD_SXOSCOFF		0x46
#घोषणा	CC2520_CMD_SFLUSHRX		0x47
#घोषणा	CC2520_CMD_SFLUSHTX		0x48
#घोषणा	CC2520_CMD_SACK			0x49
#घोषणा	CC2520_CMD_SACKPEND		0x4A
#घोषणा	CC2520_CMD_SNACK		0x4B
#घोषणा	CC2520_CMD_SRXMASKBITSET	0x4C
#घोषणा	CC2520_CMD_SRXMASKBITCLR	0x4D
#घोषणा	CC2520_CMD_RXMASKAND		0x4E
#घोषणा	CC2520_CMD_RXMASKOR		0x4F
#घोषणा	CC2520_CMD_MEMCP		0x50
#घोषणा	CC2520_CMD_MEMCPR		0x52
#घोषणा	CC2520_CMD_MEMXCP		0x54
#घोषणा	CC2520_CMD_MEMXWR		0x56
#घोषणा	CC2520_CMD_BCLR			0x58
#घोषणा	CC2520_CMD_BSET			0x59
#घोषणा	CC2520_CMD_CTR_UCTR		0x60
#घोषणा	CC2520_CMD_CBCMAC		0x64
#घोषणा	CC2520_CMD_UCBCMAC		0x66
#घोषणा	CC2520_CMD_CCM			0x68
#घोषणा	CC2520_CMD_UCCM			0x6A
#घोषणा	CC2520_CMD_ECB			0x70
#घोषणा	CC2520_CMD_ECBO			0x72
#घोषणा	CC2520_CMD_ECBX			0x74
#घोषणा	CC2520_CMD_INC			0x78
#घोषणा	CC2520_CMD_ABORT		0x7F
#घोषणा	CC2520_CMD_REGISTER_READ	0x80
#घोषणा	CC2520_CMD_REGISTER_WRITE	0xC0

/* status रेजिस्टरs */
#घोषणा	CC2520_CHIPID			0x40
#घोषणा	CC2520_VERSION			0x42
#घोषणा	CC2520_EXTCLOCK			0x44
#घोषणा	CC2520_MDMCTRL0			0x46
#घोषणा	CC2520_MDMCTRL1			0x47
#घोषणा	CC2520_FREQEST			0x48
#घोषणा	CC2520_RXCTRL			0x4A
#घोषणा	CC2520_FSCTRL			0x4C
#घोषणा	CC2520_FSCAL0			0x4E
#घोषणा	CC2520_FSCAL1			0x4F
#घोषणा	CC2520_FSCAL2			0x50
#घोषणा	CC2520_FSCAL3			0x51
#घोषणा	CC2520_AGCCTRL0			0x52
#घोषणा	CC2520_AGCCTRL1			0x53
#घोषणा	CC2520_AGCCTRL2			0x54
#घोषणा	CC2520_AGCCTRL3			0x55
#घोषणा	CC2520_ADCTEST0			0x56
#घोषणा	CC2520_ADCTEST1			0x57
#घोषणा	CC2520_ADCTEST2			0x58
#घोषणा	CC2520_MDMTEST0			0x5A
#घोषणा	CC2520_MDMTEST1			0x5B
#घोषणा	CC2520_DACTEST0			0x5C
#घोषणा	CC2520_DACTEST1			0x5D
#घोषणा	CC2520_ATEST			0x5E
#घोषणा	CC2520_DACTEST2			0x5F
#घोषणा	CC2520_PTEST0			0x60
#घोषणा	CC2520_PTEST1			0x61
#घोषणा	CC2520_RESERVED			0x62
#घोषणा	CC2520_DPUBIST			0x7A
#घोषणा	CC2520_ACTBIST			0x7C
#घोषणा	CC2520_RAMBIST			0x7E

/* frame रेजिस्टरs */
#घोषणा	CC2520_FRMFILT0			0x00
#घोषणा	CC2520_FRMFILT1			0x01
#घोषणा	CC2520_SRCMATCH			0x02
#घोषणा	CC2520_SRCSHORTEN0		0x04
#घोषणा	CC2520_SRCSHORTEN1		0x05
#घोषणा	CC2520_SRCSHORTEN2		0x06
#घोषणा	CC2520_SRCEXTEN0		0x08
#घोषणा	CC2520_SRCEXTEN1		0x09
#घोषणा	CC2520_SRCEXTEN2		0x0A
#घोषणा	CC2520_FRMCTRL0			0x0C
#घोषणा	CC2520_FRMCTRL1			0x0D
#घोषणा	CC2520_RXENABLE0		0x0E
#घोषणा	CC2520_RXENABLE1		0x0F
#घोषणा	CC2520_EXCFLAG0			0x10
#घोषणा	CC2520_EXCFLAG1			0x11
#घोषणा	CC2520_EXCFLAG2			0x12
#घोषणा	CC2520_EXCMASKA0		0x14
#घोषणा	CC2520_EXCMASKA1		0x15
#घोषणा	CC2520_EXCMASKA2		0x16
#घोषणा	CC2520_EXCMASKB0		0x18
#घोषणा	CC2520_EXCMASKB1		0x19
#घोषणा	CC2520_EXCMASKB2		0x1A
#घोषणा	CC2520_EXCBINDX0		0x1C
#घोषणा	CC2520_EXCBINDX1		0x1D
#घोषणा	CC2520_EXCBINDY0		0x1E
#घोषणा	CC2520_EXCBINDY1		0x1F
#घोषणा	CC2520_GPIOCTRL0		0x20
#घोषणा	CC2520_GPIOCTRL1		0x21
#घोषणा	CC2520_GPIOCTRL2		0x22
#घोषणा	CC2520_GPIOCTRL3		0x23
#घोषणा	CC2520_GPIOCTRL4		0x24
#घोषणा	CC2520_GPIOCTRL5		0x25
#घोषणा	CC2520_GPIOPOLARITY		0x26
#घोषणा	CC2520_GPIOCTRL			0x28
#घोषणा	CC2520_DPUCON			0x2A
#घोषणा	CC2520_DPUSTAT			0x2C
#घोषणा	CC2520_FREQCTRL			0x2E
#घोषणा	CC2520_FREQTUNE			0x2F
#घोषणा	CC2520_TXPOWER			0x30
#घोषणा	CC2520_TXCTRL			0x31
#घोषणा	CC2520_FSMSTAT0			0x32
#घोषणा	CC2520_FSMSTAT1			0x33
#घोषणा	CC2520_FIFOPCTRL		0x34
#घोषणा	CC2520_FSMCTRL			0x35
#घोषणा	CC2520_CCACTRL0			0x36
#घोषणा	CC2520_CCACTRL1			0x37
#घोषणा	CC2520_RSSI			0x38
#घोषणा	CC2520_RSSISTAT			0x39
#घोषणा	CC2520_RXFIRST			0x3C
#घोषणा	CC2520_RXFIFOCNT		0x3E
#घोषणा	CC2520_TXFIFOCNT		0x3F

/* CC2520_FRMFILT0 */
#घोषणा FRMFILT0_FRAME_FILTER_EN	BIT(0)
#घोषणा FRMFILT0_PAN_COORDINATOR	BIT(1)

/* CC2520_FRMCTRL0 */
#घोषणा FRMCTRL0_AUTOACK		BIT(5)
#घोषणा FRMCTRL0_AUTOCRC		BIT(6)

/* CC2520_FRMCTRL1 */
#घोषणा FRMCTRL1_SET_RXENMASK_ON_TX	BIT(0)
#घोषणा FRMCTRL1_IGNORE_TX_UNDERF	BIT(1)

/* Driver निजी inक्रमmation */
काष्ठा cc2520_निजी अणु
	काष्ठा spi_device *spi;		/* SPI device काष्ठाure */
	काष्ठा ieee802154_hw *hw;	/* IEEE-802.15.4 device */
	u8 *buf;			/* SPI TX/Rx data buffer */
	काष्ठा mutex buffer_mutex;	/* SPI buffer mutex */
	bool is_tx;			/* Flag क्रम sync b/w Tx and Rx */
	bool amplअगरied;			/* Flag क्रम CC2591 */
	पूर्णांक fअगरo_pin;			/* FIFO GPIO pin number */
	काष्ठा work_काष्ठा fअगरop_irqwork;/* Workqueue क्रम FIFOP */
	spinlock_t lock;		/* Lock क्रम is_tx*/
	काष्ठा completion tx_complete;	/* Work completion क्रम Tx */
	bool promiscuous;               /* Flag क्रम promiscuous mode */
पूर्ण;

/* Generic Functions */
अटल पूर्णांक
cc2520_cmd_strobe(काष्ठा cc2520_निजी *priv, u8 cmd)
अणु
	पूर्णांक ret;
	काष्ठा spi_message msg;
	काष्ठा spi_transfer xfer = अणु
		.len = 0,
		.tx_buf = priv->buf,
		.rx_buf = priv->buf,
	पूर्ण;

	spi_message_init(&msg);
	spi_message_add_tail(&xfer, &msg);

	mutex_lock(&priv->buffer_mutex);
	priv->buf[xfer.len++] = cmd;
	dev_vdbg(&priv->spi->dev,
		 "command strobe buf[0] = %02x\n",
		 priv->buf[0]);

	ret = spi_sync(priv->spi, &msg);
	dev_vdbg(&priv->spi->dev,
		 "buf[0] = %02x\n", priv->buf[0]);
	mutex_unlock(&priv->buffer_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक
cc2520_get_status(काष्ठा cc2520_निजी *priv, u8 *status)
अणु
	पूर्णांक ret;
	काष्ठा spi_message msg;
	काष्ठा spi_transfer xfer = अणु
		.len = 0,
		.tx_buf = priv->buf,
		.rx_buf = priv->buf,
	पूर्ण;

	spi_message_init(&msg);
	spi_message_add_tail(&xfer, &msg);

	mutex_lock(&priv->buffer_mutex);
	priv->buf[xfer.len++] = CC2520_CMD_SNOP;
	dev_vdbg(&priv->spi->dev,
		 "get status command buf[0] = %02x\n", priv->buf[0]);

	ret = spi_sync(priv->spi, &msg);
	अगर (!ret)
		*status = priv->buf[0];
	dev_vdbg(&priv->spi->dev,
		 "buf[0] = %02x\n", priv->buf[0]);
	mutex_unlock(&priv->buffer_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक
cc2520_ग_लिखो_रेजिस्टर(काष्ठा cc2520_निजी *priv, u8 reg, u8 value)
अणु
	पूर्णांक status;
	काष्ठा spi_message msg;
	काष्ठा spi_transfer xfer = अणु
		.len = 0,
		.tx_buf = priv->buf,
		.rx_buf = priv->buf,
	पूर्ण;

	spi_message_init(&msg);
	spi_message_add_tail(&xfer, &msg);

	mutex_lock(&priv->buffer_mutex);

	अगर (reg <= CC2520_FREG_MASK) अणु
		priv->buf[xfer.len++] = CC2520_CMD_REGISTER_WRITE | reg;
		priv->buf[xfer.len++] = value;
	पूर्ण अन्यथा अणु
		priv->buf[xfer.len++] = CC2520_CMD_MEMORY_WRITE;
		priv->buf[xfer.len++] = reg;
		priv->buf[xfer.len++] = value;
	पूर्ण
	status = spi_sync(priv->spi, &msg);
	अगर (msg.status)
		status = msg.status;

	mutex_unlock(&priv->buffer_mutex);

	वापस status;
पूर्ण

अटल पूर्णांक
cc2520_ग_लिखो_ram(काष्ठा cc2520_निजी *priv, u16 reg, u8 len, u8 *data)
अणु
	पूर्णांक status;
	काष्ठा spi_message msg;
	काष्ठा spi_transfer xfer_head = अणु
		.len        = 0,
		.tx_buf        = priv->buf,
		.rx_buf        = priv->buf,
	पूर्ण;

	काष्ठा spi_transfer xfer_buf = अणु
		.len = len,
		.tx_buf = data,
	पूर्ण;

	mutex_lock(&priv->buffer_mutex);
	priv->buf[xfer_head.len++] = (CC2520_CMD_MEMORY_WRITE |
						((reg >> 8) & 0xff));
	priv->buf[xfer_head.len++] = reg & 0xff;

	spi_message_init(&msg);
	spi_message_add_tail(&xfer_head, &msg);
	spi_message_add_tail(&xfer_buf, &msg);

	status = spi_sync(priv->spi, &msg);
	dev_dbg(&priv->spi->dev, "spi status = %d\n", status);
	अगर (msg.status)
		status = msg.status;

	mutex_unlock(&priv->buffer_mutex);
	वापस status;
पूर्ण

अटल पूर्णांक
cc2520_पढ़ो_रेजिस्टर(काष्ठा cc2520_निजी *priv, u8 reg, u8 *data)
अणु
	पूर्णांक status;
	काष्ठा spi_message msg;
	काष्ठा spi_transfer xfer1 = अणु
		.len = 0,
		.tx_buf = priv->buf,
		.rx_buf = priv->buf,
	पूर्ण;

	काष्ठा spi_transfer xfer2 = अणु
		.len = 1,
		.rx_buf = data,
	पूर्ण;

	spi_message_init(&msg);
	spi_message_add_tail(&xfer1, &msg);
	spi_message_add_tail(&xfer2, &msg);

	mutex_lock(&priv->buffer_mutex);
	priv->buf[xfer1.len++] = CC2520_CMD_MEMORY_READ;
	priv->buf[xfer1.len++] = reg;

	status = spi_sync(priv->spi, &msg);
	dev_dbg(&priv->spi->dev,
		"spi status = %d\n", status);
	अगर (msg.status)
		status = msg.status;

	mutex_unlock(&priv->buffer_mutex);

	वापस status;
पूर्ण

अटल पूर्णांक
cc2520_ग_लिखो_txfअगरo(काष्ठा cc2520_निजी *priv, u8 pkt_len, u8 *data, u8 len)
अणु
	पूर्णांक status;

	/* length byte must include FCS even
	 * अगर it is calculated in the hardware
	 */
	पूर्णांक len_byte = pkt_len;

	काष्ठा spi_message msg;

	काष्ठा spi_transfer xfer_head = अणु
		.len = 0,
		.tx_buf = priv->buf,
		.rx_buf = priv->buf,
	पूर्ण;
	काष्ठा spi_transfer xfer_len = अणु
		.len = 1,
		.tx_buf = &len_byte,
	पूर्ण;
	काष्ठा spi_transfer xfer_buf = अणु
		.len = len,
		.tx_buf = data,
	पूर्ण;

	spi_message_init(&msg);
	spi_message_add_tail(&xfer_head, &msg);
	spi_message_add_tail(&xfer_len, &msg);
	spi_message_add_tail(&xfer_buf, &msg);

	mutex_lock(&priv->buffer_mutex);
	priv->buf[xfer_head.len++] = CC2520_CMD_TXBUF;
	dev_vdbg(&priv->spi->dev,
		 "TX_FIFO cmd buf[0] = %02x\n", priv->buf[0]);

	status = spi_sync(priv->spi, &msg);
	dev_vdbg(&priv->spi->dev, "status = %d\n", status);
	अगर (msg.status)
		status = msg.status;
	dev_vdbg(&priv->spi->dev, "status = %d\n", status);
	dev_vdbg(&priv->spi->dev, "buf[0] = %02x\n", priv->buf[0]);
	mutex_unlock(&priv->buffer_mutex);

	वापस status;
पूर्ण

अटल पूर्णांक
cc2520_पढ़ो_rxfअगरo(काष्ठा cc2520_निजी *priv, u8 *data, u8 len)
अणु
	पूर्णांक status;
	काष्ठा spi_message msg;

	काष्ठा spi_transfer xfer_head = अणु
		.len = 0,
		.tx_buf = priv->buf,
		.rx_buf = priv->buf,
	पूर्ण;
	काष्ठा spi_transfer xfer_buf = अणु
		.len = len,
		.rx_buf = data,
	पूर्ण;

	spi_message_init(&msg);
	spi_message_add_tail(&xfer_head, &msg);
	spi_message_add_tail(&xfer_buf, &msg);

	mutex_lock(&priv->buffer_mutex);
	priv->buf[xfer_head.len++] = CC2520_CMD_RXBUF;

	dev_vdbg(&priv->spi->dev, "read rxfifo buf[0] = %02x\n", priv->buf[0]);
	dev_vdbg(&priv->spi->dev, "buf[1] = %02x\n", priv->buf[1]);

	status = spi_sync(priv->spi, &msg);
	dev_vdbg(&priv->spi->dev, "status = %d\n", status);
	अगर (msg.status)
		status = msg.status;
	dev_vdbg(&priv->spi->dev, "status = %d\n", status);
	dev_vdbg(&priv->spi->dev,
		 "return status buf[0] = %02x\n", priv->buf[0]);
	dev_vdbg(&priv->spi->dev, "length buf[1] = %02x\n", priv->buf[1]);

	mutex_unlock(&priv->buffer_mutex);

	वापस status;
पूर्ण

अटल पूर्णांक cc2520_start(काष्ठा ieee802154_hw *hw)
अणु
	वापस cc2520_cmd_strobe(hw->priv, CC2520_CMD_SRXON);
पूर्ण

अटल व्योम cc2520_stop(काष्ठा ieee802154_hw *hw)
अणु
	cc2520_cmd_strobe(hw->priv, CC2520_CMD_SRFOFF);
पूर्ण

अटल पूर्णांक
cc2520_tx(काष्ठा ieee802154_hw *hw, काष्ठा sk_buff *skb)
अणु
	काष्ठा cc2520_निजी *priv = hw->priv;
	अचिन्हित दीर्घ flags;
	पूर्णांक rc;
	u8 status = 0;
	u8 pkt_len;

	/* In promiscuous mode we disable AUTOCRC so we can get the raw CRC
	 * values on RX. This means we need to manually add the CRC on TX.
	 */
	अगर (priv->promiscuous) अणु
		u16 crc = crc_ccitt(0, skb->data, skb->len);

		put_unaligned_le16(crc, skb_put(skb, 2));
		pkt_len = skb->len;
	पूर्ण अन्यथा अणु
		pkt_len = skb->len + 2;
	पूर्ण

	rc = cc2520_cmd_strobe(priv, CC2520_CMD_SFLUSHTX);
	अगर (rc)
		जाओ err_tx;

	rc = cc2520_ग_लिखो_txfअगरo(priv, pkt_len, skb->data, skb->len);
	अगर (rc)
		जाओ err_tx;

	rc = cc2520_get_status(priv, &status);
	अगर (rc)
		जाओ err_tx;

	अगर (status & CC2520_STATUS_TX_UNDERFLOW) अणु
		dev_err(&priv->spi->dev, "cc2520 tx underflow exception\n");
		जाओ err_tx;
	पूर्ण

	spin_lock_irqsave(&priv->lock, flags);
	WARN_ON(priv->is_tx);
	priv->is_tx = 1;
	spin_unlock_irqrestore(&priv->lock, flags);

	rc = cc2520_cmd_strobe(priv, CC2520_CMD_STXONCCA);
	अगर (rc)
		जाओ err;

	rc = रुको_क्रम_completion_पूर्णांकerruptible(&priv->tx_complete);
	अगर (rc < 0)
		जाओ err;

	cc2520_cmd_strobe(priv, CC2520_CMD_SFLUSHTX);
	cc2520_cmd_strobe(priv, CC2520_CMD_SRXON);

	वापस rc;
err:
	spin_lock_irqsave(&priv->lock, flags);
	priv->is_tx = 0;
	spin_unlock_irqrestore(&priv->lock, flags);
err_tx:
	वापस rc;
पूर्ण

अटल पूर्णांक cc2520_rx(काष्ठा cc2520_निजी *priv)
अणु
	u8 len = 0, lqi = 0, bytes = 1;
	काष्ठा sk_buff *skb;

	/* Read single length byte from the radio. */
	cc2520_पढ़ो_rxfअगरo(priv, &len, bytes);

	अगर (!ieee802154_is_valid_psdu_len(len)) अणु
		/* Corrupted frame received, clear frame buffer by
		 * पढ़ोing entire buffer.
		 */
		dev_dbg(&priv->spi->dev, "corrupted frame received\n");
		len = IEEE802154_MTU;
	पूर्ण

	skb = dev_alloc_skb(len);
	अगर (!skb)
		वापस -ENOMEM;

	अगर (cc2520_पढ़ो_rxfअगरo(priv, skb_put(skb, len), len)) अणु
		dev_dbg(&priv->spi->dev, "frame reception failed\n");
		kमुक्त_skb(skb);
		वापस -EINVAL;
	पूर्ण

	/* In promiscuous mode, we configure the radio to include the
	 * CRC (AUTOCRC==0) and we pass on the packet unconditionally. If not
	 * in promiscuous mode, we check the CRC here, but leave the
	 * RSSI/LQI/CRC_OK bytes as they will get हटाओd in the mac layer.
	 */
	अगर (!priv->promiscuous) अणु
		bool crc_ok;

		/* Check अगर the CRC is valid. With AUTOCRC set, the most
		 * signअगरicant bit of the last byte वापसed from the CC2520
		 * is CRC_OK flag. See section 20.3.4 of the datasheet.
		 */
		crc_ok = skb->data[len - 1] & BIT(7);

		/* If we failed CRC drop the packet in the driver layer. */
		अगर (!crc_ok) अणु
			dev_dbg(&priv->spi->dev, "CRC check failed\n");
			kमुक्त_skb(skb);
			वापस -EINVAL;
		पूर्ण

		/* To calculate LQI, the lower 7 bits of the last byte (the
		 * correlation value provided by the radio) must be scaled to
		 * the range 0-255. According to section 20.6, the correlation
		 * value ranges from 50-110. Ideally this would be calibrated
		 * per hardware design, but we use roughly the datasheet values
		 * to get बंद enough जबतक aव्योमing भग्नing poपूर्णांक.
		 */
		lqi = skb->data[len - 1] & 0x7f;
		अगर (lqi < 50)
			lqi = 50;
		अन्यथा अगर (lqi > 113)
			lqi = 113;
		lqi = (lqi - 50) * 4;
	पूर्ण

	ieee802154_rx_irqsafe(priv->hw, skb, lqi);

	dev_vdbg(&priv->spi->dev, "RXFIFO: %x %x\n", len, lqi);

	वापस 0;
पूर्ण

अटल पूर्णांक
cc2520_ed(काष्ठा ieee802154_hw *hw, u8 *level)
अणु
	काष्ठा cc2520_निजी *priv = hw->priv;
	u8 status = 0xff;
	u8 rssi;
	पूर्णांक ret;

	ret = cc2520_पढ़ो_रेजिस्टर(priv, CC2520_RSSISTAT, &status);
	अगर (ret)
		वापस ret;

	अगर (status != RSSI_VALID)
		वापस -EINVAL;

	ret = cc2520_पढ़ो_रेजिस्टर(priv, CC2520_RSSI, &rssi);
	अगर (ret)
		वापस ret;

	/* level = RSSI(rssi) - OFFSET [dBm] : offset is 76dBm */
	*level = rssi - RSSI_OFFSET;

	वापस 0;
पूर्ण

अटल पूर्णांक
cc2520_set_channel(काष्ठा ieee802154_hw *hw, u8 page, u8 channel)
अणु
	काष्ठा cc2520_निजी *priv = hw->priv;
	पूर्णांक ret;

	dev_dbg(&priv->spi->dev, "trying to set channel\n");

	WARN_ON(page != 0);
	WARN_ON(channel < CC2520_MINCHANNEL);
	WARN_ON(channel > CC2520_MAXCHANNEL);

	ret = cc2520_ग_लिखो_रेजिस्टर(priv, CC2520_FREQCTRL,
				    11 + 5 * (channel - 11));

	वापस ret;
पूर्ण

अटल पूर्णांक
cc2520_filter(काष्ठा ieee802154_hw *hw,
	      काष्ठा ieee802154_hw_addr_filt *filt, अचिन्हित दीर्घ changed)
अणु
	काष्ठा cc2520_निजी *priv = hw->priv;
	पूर्णांक ret = 0;

	अगर (changed & IEEE802154_AFILT_PANID_CHANGED) अणु
		u16 panid = le16_to_cpu(filt->pan_id);

		dev_vdbg(&priv->spi->dev, "%s called for pan id\n", __func__);
		ret = cc2520_ग_लिखो_ram(priv, CC2520RAM_PANID,
				       माप(panid), (u8 *)&panid);
	पूर्ण

	अगर (changed & IEEE802154_AFILT_IEEEADDR_CHANGED) अणु
		dev_vdbg(&priv->spi->dev,
			 "%s called for IEEE addr\n", __func__);
		ret = cc2520_ग_लिखो_ram(priv, CC2520RAM_IEEEADDR,
				       माप(filt->ieee_addr),
				       (u8 *)&filt->ieee_addr);
	पूर्ण

	अगर (changed & IEEE802154_AFILT_SADDR_CHANGED) अणु
		u16 addr = le16_to_cpu(filt->लघु_addr);

		dev_vdbg(&priv->spi->dev, "%s called for saddr\n", __func__);
		ret = cc2520_ग_लिखो_ram(priv, CC2520RAM_SHORTADDR,
				       माप(addr), (u8 *)&addr);
	पूर्ण

	अगर (changed & IEEE802154_AFILT_PANC_CHANGED) अणु
		u8 frmfilt0;

		dev_vdbg(&priv->spi->dev,
			 "%s called for panc change\n", __func__);

		cc2520_पढ़ो_रेजिस्टर(priv, CC2520_FRMFILT0, &frmfilt0);

		अगर (filt->pan_coord)
			frmfilt0 |= FRMFILT0_PAN_COORDINATOR;
		अन्यथा
			frmfilt0 &= ~FRMFILT0_PAN_COORDINATOR;

		ret = cc2520_ग_लिखो_रेजिस्टर(priv, CC2520_FRMFILT0, frmfilt0);
	पूर्ण

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक cc2520_set_tx_घातer(काष्ठा cc2520_निजी *priv, s32 mbm)
अणु
	u8 घातer;

	चयन (mbm) अणु
	हाल 500:
		घातer = 0xF7;
		अवरोध;
	हाल 300:
		घातer = 0xF2;
		अवरोध;
	हाल 200:
		घातer = 0xAB;
		अवरोध;
	हाल 100:
		घातer = 0x13;
		अवरोध;
	हाल 0:
		घातer = 0x32;
		अवरोध;
	हाल -200:
		घातer = 0x81;
		अवरोध;
	हाल -400:
		घातer = 0x88;
		अवरोध;
	हाल -700:
		घातer = 0x2C;
		अवरोध;
	हाल -1800:
		घातer = 0x03;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस cc2520_ग_लिखो_रेजिस्टर(priv, CC2520_TXPOWER, घातer);
पूर्ण

अटल अंतरभूत पूर्णांक cc2520_cc2591_set_tx_घातer(काष्ठा cc2520_निजी *priv,
					     s32 mbm)
अणु
	u8 घातer;

	चयन (mbm) अणु
	हाल 1700:
		घातer = 0xF9;
		अवरोध;
	हाल 1600:
		घातer = 0xF0;
		अवरोध;
	हाल 1400:
		घातer = 0xA0;
		अवरोध;
	हाल 1100:
		घातer = 0x2C;
		अवरोध;
	हाल -100:
		घातer = 0x03;
		अवरोध;
	हाल -800:
		घातer = 0x01;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस cc2520_ग_लिखो_रेजिस्टर(priv, CC2520_TXPOWER, घातer);
पूर्ण

#घोषणा CC2520_MAX_TX_POWERS 0x8
अटल स्थिर s32 cc2520_घातers[CC2520_MAX_TX_POWERS + 1] = अणु
	500, 300, 200, 100, 0, -200, -400, -700, -1800,
पूर्ण;

#घोषणा CC2520_CC2591_MAX_TX_POWERS 0x5
अटल स्थिर s32 cc2520_cc2591_घातers[CC2520_CC2591_MAX_TX_POWERS + 1] = अणु
	1700, 1600, 1400, 1100, -100, -800,
पूर्ण;

अटल पूर्णांक
cc2520_set_txघातer(काष्ठा ieee802154_hw *hw, s32 mbm)
अणु
	काष्ठा cc2520_निजी *priv = hw->priv;

	अगर (!priv->amplअगरied)
		वापस cc2520_set_tx_घातer(priv, mbm);

	वापस cc2520_cc2591_set_tx_घातer(priv, mbm);
पूर्ण

अटल पूर्णांक
cc2520_set_promiscuous_mode(काष्ठा ieee802154_hw *hw, bool on)
अणु
	काष्ठा cc2520_निजी *priv = hw->priv;
	u8 frmfilt0;

	dev_dbg(&priv->spi->dev, "%s : mode %d\n", __func__, on);

	priv->promiscuous = on;

	cc2520_पढ़ो_रेजिस्टर(priv, CC2520_FRMFILT0, &frmfilt0);

	अगर (on) अणु
		/* Disable स्वतःmatic ACK, स्वतःmatic CRC, and frame filtering. */
		cc2520_ग_लिखो_रेजिस्टर(priv, CC2520_FRMCTRL0, 0);
		frmfilt0 &= ~FRMFILT0_FRAME_FILTER_EN;
	पूर्ण अन्यथा अणु
		cc2520_ग_लिखो_रेजिस्टर(priv, CC2520_FRMCTRL0, FRMCTRL0_AUTOACK |
							     FRMCTRL0_AUTOCRC);
		frmfilt0 |= FRMFILT0_FRAME_FILTER_EN;
	पूर्ण
	वापस cc2520_ग_लिखो_रेजिस्टर(priv, CC2520_FRMFILT0, frmfilt0);
पूर्ण

अटल स्थिर काष्ठा ieee802154_ops cc2520_ops = अणु
	.owner = THIS_MODULE,
	.start = cc2520_start,
	.stop = cc2520_stop,
	.xmit_sync = cc2520_tx,
	.ed = cc2520_ed,
	.set_channel = cc2520_set_channel,
	.set_hw_addr_filt = cc2520_filter,
	.set_txघातer = cc2520_set_txघातer,
	.set_promiscuous_mode = cc2520_set_promiscuous_mode,
पूर्ण;

अटल पूर्णांक cc2520_रेजिस्टर(काष्ठा cc2520_निजी *priv)
अणु
	पूर्णांक ret = -ENOMEM;

	priv->hw = ieee802154_alloc_hw(माप(*priv), &cc2520_ops);
	अगर (!priv->hw)
		जाओ err_ret;

	priv->hw->priv = priv;
	priv->hw->parent = &priv->spi->dev;
	priv->hw->extra_tx_headroom = 0;
	ieee802154_अक्रमom_extended_addr(&priv->hw->phy->perm_extended_addr);

	/* We करो support only 2.4 Ghz */
	priv->hw->phy->supported.channels[0] = 0x7FFF800;
	priv->hw->flags = IEEE802154_HW_TX_OMIT_CKSUM | IEEE802154_HW_AFILT |
			  IEEE802154_HW_PROMISCUOUS;

	priv->hw->phy->flags = WPAN_PHY_FLAG_TXPOWER;

	अगर (!priv->amplअगरied) अणु
		priv->hw->phy->supported.tx_घातers = cc2520_घातers;
		priv->hw->phy->supported.tx_घातers_size = ARRAY_SIZE(cc2520_घातers);
		priv->hw->phy->transmit_घातer = priv->hw->phy->supported.tx_घातers[4];
	पूर्ण अन्यथा अणु
		priv->hw->phy->supported.tx_घातers = cc2520_cc2591_घातers;
		priv->hw->phy->supported.tx_घातers_size = ARRAY_SIZE(cc2520_cc2591_घातers);
		priv->hw->phy->transmit_घातer = priv->hw->phy->supported.tx_घातers[0];
	पूर्ण

	priv->hw->phy->current_channel = 11;

	dev_vdbg(&priv->spi->dev, "registered cc2520\n");
	ret = ieee802154_रेजिस्टर_hw(priv->hw);
	अगर (ret)
		जाओ err_मुक्त_device;

	वापस 0;

err_मुक्त_device:
	ieee802154_मुक्त_hw(priv->hw);
err_ret:
	वापस ret;
पूर्ण

अटल व्योम cc2520_fअगरop_irqwork(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cc2520_निजी *priv
		= container_of(work, काष्ठा cc2520_निजी, fअगरop_irqwork);

	dev_dbg(&priv->spi->dev, "fifop interrupt received\n");

	अगर (gpio_get_value(priv->fअगरo_pin))
		cc2520_rx(priv);
	अन्यथा
		dev_dbg(&priv->spi->dev, "rxfifo overflow\n");

	cc2520_cmd_strobe(priv, CC2520_CMD_SFLUSHRX);
	cc2520_cmd_strobe(priv, CC2520_CMD_SFLUSHRX);
पूर्ण

अटल irqवापस_t cc2520_fअगरop_isr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा cc2520_निजी *priv = data;

	schedule_work(&priv->fअगरop_irqwork);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t cc2520_sfd_isr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा cc2520_निजी *priv = data;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv->lock, flags);
	अगर (priv->is_tx) अणु
		priv->is_tx = 0;
		spin_unlock_irqrestore(&priv->lock, flags);
		dev_dbg(&priv->spi->dev, "SFD for TX\n");
		complete(&priv->tx_complete);
	पूर्ण अन्यथा अणु
		spin_unlock_irqrestore(&priv->lock, flags);
		dev_dbg(&priv->spi->dev, "SFD for RX\n");
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक cc2520_get_platक्रमm_data(काष्ठा spi_device *spi,
				    काष्ठा cc2520_platक्रमm_data *pdata)
अणु
	काष्ठा device_node *np = spi->dev.of_node;
	काष्ठा cc2520_निजी *priv = spi_get_drvdata(spi);

	अगर (!np) अणु
		काष्ठा cc2520_platक्रमm_data *spi_pdata = spi->dev.platक्रमm_data;

		अगर (!spi_pdata)
			वापस -ENOENT;
		*pdata = *spi_pdata;
		priv->fअगरo_pin = pdata->fअगरo;
		वापस 0;
	पूर्ण

	pdata->fअगरo = of_get_named_gpio(np, "fifo-gpio", 0);
	priv->fअगरo_pin = pdata->fअगरo;

	pdata->fअगरop = of_get_named_gpio(np, "fifop-gpio", 0);

	pdata->sfd = of_get_named_gpio(np, "sfd-gpio", 0);
	pdata->cca = of_get_named_gpio(np, "cca-gpio", 0);
	pdata->vreg = of_get_named_gpio(np, "vreg-gpio", 0);
	pdata->reset = of_get_named_gpio(np, "reset-gpio", 0);

	/* CC2591 front end क्रम CC2520 */
	अगर (of_property_पढ़ो_bool(np, "amplified"))
		priv->amplअगरied = true;

	वापस 0;
पूर्ण

अटल पूर्णांक cc2520_hw_init(काष्ठा cc2520_निजी *priv)
अणु
	u8 status = 0, state = 0xff;
	पूर्णांक ret;
	पूर्णांक समयout = 100;
	काष्ठा cc2520_platक्रमm_data pdata;

	ret = cc2520_get_platक्रमm_data(priv->spi, &pdata);
	अगर (ret)
		जाओ err_ret;

	ret = cc2520_पढ़ो_रेजिस्टर(priv, CC2520_FSMSTAT1, &state);
	अगर (ret)
		जाओ err_ret;

	अगर (state != STATE_IDLE)
		वापस -EINVAL;

	करो अणु
		ret = cc2520_get_status(priv, &status);
		अगर (ret)
			जाओ err_ret;

		अगर (समयout-- <= 0) अणु
			dev_err(&priv->spi->dev, "oscillator start failed!\n");
			वापस ret;
		पूर्ण
		udelay(1);
	पूर्ण जबतक (!(status & CC2520_STATUS_XOSC32M_STABLE));

	dev_vdbg(&priv->spi->dev, "oscillator brought up\n");

	/* If the CC2520 is connected to a CC2591 amplअगरier, we must both
	 * configure GPIOs on the CC2520 to correctly configure the CC2591
	 * and change a couple settings of the CC2520 to work with the
	 * amplअगरier. See section 8 page 17 of TI application note AN065.
	 * http://www.ti.com/lit/an/swra229a/swra229a.pdf
	 */
	अगर (priv->amplअगरied) अणु
		ret = cc2520_ग_लिखो_रेजिस्टर(priv, CC2520_AGCCTRL1, 0x16);
		अगर (ret)
			जाओ err_ret;

		ret = cc2520_ग_लिखो_रेजिस्टर(priv, CC2520_GPIOCTRL0, 0x46);
		अगर (ret)
			जाओ err_ret;

		ret = cc2520_ग_लिखो_रेजिस्टर(priv, CC2520_GPIOCTRL5, 0x47);
		अगर (ret)
			जाओ err_ret;

		ret = cc2520_ग_लिखो_रेजिस्टर(priv, CC2520_GPIOPOLARITY, 0x1e);
		अगर (ret)
			जाओ err_ret;

		ret = cc2520_ग_लिखो_रेजिस्टर(priv, CC2520_TXCTRL, 0xc1);
		अगर (ret)
			जाओ err_ret;
	पूर्ण अन्यथा अणु
		ret = cc2520_ग_लिखो_रेजिस्टर(priv, CC2520_AGCCTRL1, 0x11);
		अगर (ret)
			जाओ err_ret;
	पूर्ण

	/* Registers शेष value: section 28.1 in Datasheet */

	/* Set the CCA threshold to -50 dBm. This seems to have been copied
	 * from the TinyOS CC2520 driver and is much higher than the -84 dBm
	 * threshold suggested in the datasheet.
	 */
	ret = cc2520_ग_लिखो_रेजिस्टर(priv, CC2520_CCACTRL0, 0x1A);
	अगर (ret)
		जाओ err_ret;

	ret = cc2520_ग_लिखो_रेजिस्टर(priv, CC2520_MDMCTRL0, 0x85);
	अगर (ret)
		जाओ err_ret;

	ret = cc2520_ग_लिखो_रेजिस्टर(priv, CC2520_MDMCTRL1, 0x14);
	अगर (ret)
		जाओ err_ret;

	ret = cc2520_ग_लिखो_रेजिस्टर(priv, CC2520_RXCTRL, 0x3f);
	अगर (ret)
		जाओ err_ret;

	ret = cc2520_ग_लिखो_रेजिस्टर(priv, CC2520_FSCTRL, 0x5a);
	अगर (ret)
		जाओ err_ret;

	ret = cc2520_ग_लिखो_रेजिस्टर(priv, CC2520_FSCAL1, 0x2b);
	अगर (ret)
		जाओ err_ret;

	ret = cc2520_ग_लिखो_रेजिस्टर(priv, CC2520_ADCTEST0, 0x10);
	अगर (ret)
		जाओ err_ret;

	ret = cc2520_ग_लिखो_रेजिस्टर(priv, CC2520_ADCTEST1, 0x0e);
	अगर (ret)
		जाओ err_ret;

	ret = cc2520_ग_लिखो_रेजिस्टर(priv, CC2520_ADCTEST2, 0x03);
	अगर (ret)
		जाओ err_ret;

	/* Configure रेजिस्टरs correctly क्रम this driver. */
	ret = cc2520_ग_लिखो_रेजिस्टर(priv, CC2520_FRMCTRL1,
				    FRMCTRL1_SET_RXENMASK_ON_TX |
				    FRMCTRL1_IGNORE_TX_UNDERF);
	अगर (ret)
		जाओ err_ret;

	ret = cc2520_ग_लिखो_रेजिस्टर(priv, CC2520_FIFOPCTRL, 127);
	अगर (ret)
		जाओ err_ret;

	वापस 0;

err_ret:
	वापस ret;
पूर्ण

अटल पूर्णांक cc2520_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा cc2520_निजी *priv;
	काष्ठा cc2520_platक्रमm_data pdata;
	पूर्णांक ret;

	priv = devm_kzalloc(&spi->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	spi_set_drvdata(spi, priv);

	ret = cc2520_get_platक्रमm_data(spi, &pdata);
	अगर (ret < 0) अणु
		dev_err(&spi->dev, "no platform data\n");
		वापस -EINVAL;
	पूर्ण

	priv->spi = spi;

	priv->buf = devm_kzalloc(&spi->dev,
				 SPI_COMMAND_BUFFER, GFP_KERNEL);
	अगर (!priv->buf)
		वापस -ENOMEM;

	mutex_init(&priv->buffer_mutex);
	INIT_WORK(&priv->fअगरop_irqwork, cc2520_fअगरop_irqwork);
	spin_lock_init(&priv->lock);
	init_completion(&priv->tx_complete);

	/* Assumption that CC2591 is not connected */
	priv->amplअगरied = false;

	/* Request all the gpio's */
	अगर (!gpio_is_valid(pdata.fअगरo)) अणु
		dev_err(&spi->dev, "fifo gpio is not valid\n");
		ret = -EINVAL;
		जाओ err_hw_init;
	पूर्ण

	ret = devm_gpio_request_one(&spi->dev, pdata.fअगरo,
				    GPIOF_IN, "fifo");
	अगर (ret)
		जाओ err_hw_init;

	अगर (!gpio_is_valid(pdata.cca)) अणु
		dev_err(&spi->dev, "cca gpio is not valid\n");
		ret = -EINVAL;
		जाओ err_hw_init;
	पूर्ण

	ret = devm_gpio_request_one(&spi->dev, pdata.cca,
				    GPIOF_IN, "cca");
	अगर (ret)
		जाओ err_hw_init;

	अगर (!gpio_is_valid(pdata.fअगरop)) अणु
		dev_err(&spi->dev, "fifop gpio is not valid\n");
		ret = -EINVAL;
		जाओ err_hw_init;
	पूर्ण

	ret = devm_gpio_request_one(&spi->dev, pdata.fअगरop,
				    GPIOF_IN, "fifop");
	अगर (ret)
		जाओ err_hw_init;

	अगर (!gpio_is_valid(pdata.sfd)) अणु
		dev_err(&spi->dev, "sfd gpio is not valid\n");
		ret = -EINVAL;
		जाओ err_hw_init;
	पूर्ण

	ret = devm_gpio_request_one(&spi->dev, pdata.sfd,
				    GPIOF_IN, "sfd");
	अगर (ret)
		जाओ err_hw_init;

	अगर (!gpio_is_valid(pdata.reset)) अणु
		dev_err(&spi->dev, "reset gpio is not valid\n");
		ret = -EINVAL;
		जाओ err_hw_init;
	पूर्ण

	ret = devm_gpio_request_one(&spi->dev, pdata.reset,
				    GPIOF_OUT_INIT_LOW, "reset");
	अगर (ret)
		जाओ err_hw_init;

	अगर (!gpio_is_valid(pdata.vreg)) अणु
		dev_err(&spi->dev, "vreg gpio is not valid\n");
		ret = -EINVAL;
		जाओ err_hw_init;
	पूर्ण

	ret = devm_gpio_request_one(&spi->dev, pdata.vreg,
				    GPIOF_OUT_INIT_LOW, "vreg");
	अगर (ret)
		जाओ err_hw_init;

	gpio_set_value(pdata.vreg, HIGH);
	usleep_range(100, 150);

	gpio_set_value(pdata.reset, HIGH);
	usleep_range(200, 250);

	ret = cc2520_hw_init(priv);
	अगर (ret)
		जाओ err_hw_init;

	/* Set up fअगरop पूर्णांकerrupt */
	ret = devm_request_irq(&spi->dev,
			       gpio_to_irq(pdata.fअगरop),
			       cc2520_fअगरop_isr,
			       IRQF_TRIGGER_RISING,
			       dev_name(&spi->dev),
			       priv);
	अगर (ret) अणु
		dev_err(&spi->dev, "could not get fifop irq\n");
		जाओ err_hw_init;
	पूर्ण

	/* Set up sfd पूर्णांकerrupt */
	ret = devm_request_irq(&spi->dev,
			       gpio_to_irq(pdata.sfd),
			       cc2520_sfd_isr,
			       IRQF_TRIGGER_FALLING,
			       dev_name(&spi->dev),
			       priv);
	अगर (ret) अणु
		dev_err(&spi->dev, "could not get sfd irq\n");
		जाओ err_hw_init;
	पूर्ण

	ret = cc2520_रेजिस्टर(priv);
	अगर (ret)
		जाओ err_hw_init;

	वापस 0;

err_hw_init:
	mutex_destroy(&priv->buffer_mutex);
	flush_work(&priv->fअगरop_irqwork);
	वापस ret;
पूर्ण

अटल पूर्णांक cc2520_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा cc2520_निजी *priv = spi_get_drvdata(spi);

	mutex_destroy(&priv->buffer_mutex);
	flush_work(&priv->fअगरop_irqwork);

	ieee802154_unरेजिस्टर_hw(priv->hw);
	ieee802154_मुक्त_hw(priv->hw);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा spi_device_id cc2520_ids[] = अणु
	अणु"cc2520", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(spi, cc2520_ids);

अटल स्थिर काष्ठा of_device_id cc2520_of_ids[] = अणु
	अणु.compatible = "ti,cc2520", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, cc2520_of_ids);

/* SPI driver काष्ठाure */
अटल काष्ठा spi_driver cc2520_driver = अणु
	.driver = अणु
		.name = "cc2520",
		.of_match_table = of_match_ptr(cc2520_of_ids),
	पूर्ण,
	.id_table = cc2520_ids,
	.probe = cc2520_probe,
	.हटाओ = cc2520_हटाओ,
पूर्ण;
module_spi_driver(cc2520_driver);

MODULE_AUTHOR("Varka Bhadram <varkab@cdac.in>");
MODULE_DESCRIPTION("CC2520 Transceiver Driver");
MODULE_LICENSE("GPL v2");
