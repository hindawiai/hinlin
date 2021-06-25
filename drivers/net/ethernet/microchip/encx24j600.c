<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Microchip ENCX24J600 ethernet driver
 *
 * Copyright (C) 2015 Gridpoपूर्णांक
 * Author: Jon Ringle <jringle@gridpoपूर्णांक.com>
 */

#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/regmap.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/spi/spi.h>

#समावेश "encx24j600_hw.h"

#घोषणा DRV_NAME	"encx24j600"
#घोषणा DRV_VERSION	"1.0"

#घोषणा DEFAULT_MSG_ENABLE (NETIF_MSG_DRV | NETIF_MSG_PROBE | NETIF_MSG_LINK)
अटल पूर्णांक debug = -1;
module_param(debug, पूर्णांक, 0000);
MODULE_PARM_DESC(debug, "Debug level (0=none,...,16=all)");

/* SRAM memory layout:
 *
 * 0x0000-0x05ff TX buffers  1.5KB  (1*1536) reside in the GP area in SRAM
 * 0x0600-0x5fff RX buffers 22.5KB (15*1536) reside in the RX area in SRAM
 */
#घोषणा ENC_TX_BUF_START 0x0000U
#घोषणा ENC_RX_BUF_START 0x0600U
#घोषणा ENC_RX_BUF_END   0x5fffU
#घोषणा ENC_SRAM_SIZE    0x6000U

क्रमागत अणु
	RXFILTER_NORMAL,
	RXFILTER_MULTI,
	RXFILTER_PROMISC
पूर्ण;

काष्ठा encx24j600_priv अणु
	काष्ठा net_device        *ndev;
	काष्ठा mutex              lock; /* device access lock */
	काष्ठा encx24j600_context ctx;
	काष्ठा sk_buff           *tx_skb;
	काष्ठा task_काष्ठा       *kworker_task;
	काष्ठा kthपढ़ो_worker     kworker;
	काष्ठा kthपढ़ो_work       tx_work;
	काष्ठा kthपढ़ो_work       setrx_work;
	u16                       next_packet;
	bool                      hw_enabled;
	bool                      full_duplex;
	bool                      स्वतःneg;
	u16                       speed;
	पूर्णांक                       rxfilter;
	u32                       msg_enable;
पूर्ण;

अटल व्योम dump_packet(स्थिर अक्षर *msg, पूर्णांक len, स्थिर अक्षर *data)
अणु
	pr_debug(DRV_NAME ": %s - packet len:%d\n", msg, len);
	prपूर्णांक_hex_dump_bytes("pk data: ", DUMP_PREFIX_OFFSET, data, len);
पूर्ण

अटल व्योम encx24j600_dump_rsv(काष्ठा encx24j600_priv *priv, स्थिर अक्षर *msg,
				काष्ठा rsv *rsv)
अणु
	काष्ठा net_device *dev = priv->ndev;

	netdev_info(dev, "RX packet Len:%d\n", rsv->len);
	netdev_dbg(dev, "%s - NextPk: 0x%04x\n", msg,
		   rsv->next_packet);
	netdev_dbg(dev, "RxOK: %d, DribbleNibble: %d\n",
		   RSV_GETBIT(rsv->rxstat, RSV_RXOK),
		   RSV_GETBIT(rsv->rxstat, RSV_DRIBBLENIBBLE));
	netdev_dbg(dev, "CRCErr:%d, LenChkErr: %d, LenOutOfRange: %d\n",
		   RSV_GETBIT(rsv->rxstat, RSV_CRCERROR),
		   RSV_GETBIT(rsv->rxstat, RSV_LENCHECKERR),
		   RSV_GETBIT(rsv->rxstat, RSV_LENOUTOFRANGE));
	netdev_dbg(dev, "Multicast: %d, Broadcast: %d, LongDropEvent: %d, CarrierEvent: %d\n",
		   RSV_GETBIT(rsv->rxstat, RSV_RXMULTICAST),
		   RSV_GETBIT(rsv->rxstat, RSV_RXBROADCAST),
		   RSV_GETBIT(rsv->rxstat, RSV_RXLONGEVDROPEV),
		   RSV_GETBIT(rsv->rxstat, RSV_CARRIEREV));
	netdev_dbg(dev, "ControlFrame: %d, PauseFrame: %d, UnknownOp: %d, VLanTagFrame: %d\n",
		   RSV_GETBIT(rsv->rxstat, RSV_RXCONTROLFRAME),
		   RSV_GETBIT(rsv->rxstat, RSV_RXPAUSEFRAME),
		   RSV_GETBIT(rsv->rxstat, RSV_RXUNKNOWNOPCODE),
		   RSV_GETBIT(rsv->rxstat, RSV_RXTYPEVLAN));
पूर्ण

अटल u16 encx24j600_पढ़ो_reg(काष्ठा encx24j600_priv *priv, u8 reg)
अणु
	काष्ठा net_device *dev = priv->ndev;
	अचिन्हित पूर्णांक val = 0;
	पूर्णांक ret = regmap_पढ़ो(priv->ctx.regmap, reg, &val);

	अगर (unlikely(ret))
		netअगर_err(priv, drv, dev, "%s: error %d reading reg %02x\n",
			  __func__, ret, reg);
	वापस val;
पूर्ण

अटल व्योम encx24j600_ग_लिखो_reg(काष्ठा encx24j600_priv *priv, u8 reg, u16 val)
अणु
	काष्ठा net_device *dev = priv->ndev;
	पूर्णांक ret = regmap_ग_लिखो(priv->ctx.regmap, reg, val);

	अगर (unlikely(ret))
		netअगर_err(priv, drv, dev, "%s: error %d writing reg %02x=%04x\n",
			  __func__, ret, reg, val);
पूर्ण

अटल व्योम encx24j600_update_reg(काष्ठा encx24j600_priv *priv, u8 reg,
				  u16 mask, u16 val)
अणु
	काष्ठा net_device *dev = priv->ndev;
	पूर्णांक ret = regmap_update_bits(priv->ctx.regmap, reg, mask, val);

	अगर (unlikely(ret))
		netअगर_err(priv, drv, dev, "%s: error %d updating reg %02x=%04x~%04x\n",
			  __func__, ret, reg, val, mask);
पूर्ण

अटल u16 encx24j600_पढ़ो_phy(काष्ठा encx24j600_priv *priv, u8 reg)
अणु
	काष्ठा net_device *dev = priv->ndev;
	अचिन्हित पूर्णांक val = 0;
	पूर्णांक ret = regmap_पढ़ो(priv->ctx.phymap, reg, &val);

	अगर (unlikely(ret))
		netअगर_err(priv, drv, dev, "%s: error %d reading %02x\n",
			  __func__, ret, reg);
	वापस val;
पूर्ण

अटल व्योम encx24j600_ग_लिखो_phy(काष्ठा encx24j600_priv *priv, u8 reg, u16 val)
अणु
	काष्ठा net_device *dev = priv->ndev;
	पूर्णांक ret = regmap_ग_लिखो(priv->ctx.phymap, reg, val);

	अगर (unlikely(ret))
		netअगर_err(priv, drv, dev, "%s: error %d writing reg %02x=%04x\n",
			  __func__, ret, reg, val);
पूर्ण

अटल व्योम encx24j600_clr_bits(काष्ठा encx24j600_priv *priv, u8 reg, u16 mask)
अणु
	encx24j600_update_reg(priv, reg, mask, 0);
पूर्ण

अटल व्योम encx24j600_set_bits(काष्ठा encx24j600_priv *priv, u8 reg, u16 mask)
अणु
	encx24j600_update_reg(priv, reg, mask, mask);
पूर्ण

अटल व्योम encx24j600_cmd(काष्ठा encx24j600_priv *priv, u8 cmd)
अणु
	काष्ठा net_device *dev = priv->ndev;
	पूर्णांक ret = regmap_ग_लिखो(priv->ctx.regmap, cmd, 0);

	अगर (unlikely(ret))
		netअगर_err(priv, drv, dev, "%s: error %d with cmd %02x\n",
			  __func__, ret, cmd);
पूर्ण

अटल पूर्णांक encx24j600_raw_पढ़ो(काष्ठा encx24j600_priv *priv, u8 reg, u8 *data,
			       माप_प्रकार count)
अणु
	पूर्णांक ret;

	mutex_lock(&priv->ctx.mutex);
	ret = regmap_encx24j600_spi_पढ़ो(&priv->ctx, reg, data, count);
	mutex_unlock(&priv->ctx.mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक encx24j600_raw_ग_लिखो(काष्ठा encx24j600_priv *priv, u8 reg,
				स्थिर u8 *data, माप_प्रकार count)
अणु
	पूर्णांक ret;

	mutex_lock(&priv->ctx.mutex);
	ret = regmap_encx24j600_spi_ग_लिखो(&priv->ctx, reg, data, count);
	mutex_unlock(&priv->ctx.mutex);

	वापस ret;
पूर्ण

अटल व्योम encx24j600_update_phcon1(काष्ठा encx24j600_priv *priv)
अणु
	u16 phcon1 = encx24j600_पढ़ो_phy(priv, PHCON1);

	अगर (priv->स्वतःneg == AUTONEG_ENABLE) अणु
		phcon1 |= ANEN | RENEG;
	पूर्ण अन्यथा अणु
		phcon1 &= ~ANEN;
		अगर (priv->speed == SPEED_100)
			phcon1 |= SPD100;
		अन्यथा
			phcon1 &= ~SPD100;

		अगर (priv->full_duplex)
			phcon1 |= PFULDPX;
		अन्यथा
			phcon1 &= ~PFULDPX;
	पूर्ण
	encx24j600_ग_लिखो_phy(priv, PHCON1, phcon1);
पूर्ण

/* Waits क्रम स्वतःnegotiation to complete. */
अटल पूर्णांक encx24j600_रुको_क्रम_स्वतःneg(काष्ठा encx24j600_priv *priv)
अणु
	काष्ठा net_device *dev = priv->ndev;
	अचिन्हित दीर्घ समयout = jअगरfies + msecs_to_jअगरfies(2000);
	u16 phstat1;
	u16 estat;

	phstat1 = encx24j600_पढ़ो_phy(priv, PHSTAT1);
	जबतक ((phstat1 & ANDONE) == 0) अणु
		अगर (समय_after(jअगरfies, समयout)) अणु
			u16 phstat3;

			netअगर_notice(priv, drv, dev, "timeout waiting for autoneg done\n");

			priv->स्वतःneg = AUTONEG_DISABLE;
			phstat3 = encx24j600_पढ़ो_phy(priv, PHSTAT3);
			priv->speed = (phstat3 & PHY3SPD100)
				      ? SPEED_100 : SPEED_10;
			priv->full_duplex = (phstat3 & PHY3DPX) ? 1 : 0;
			encx24j600_update_phcon1(priv);
			netअगर_notice(priv, drv, dev, "Using parallel detection: %s/%s",
				     priv->speed == SPEED_100 ? "100" : "10",
				     priv->full_duplex ? "Full" : "Half");

			वापस -ETIMEDOUT;
		पूर्ण
		cpu_relax();
		phstat1 = encx24j600_पढ़ो_phy(priv, PHSTAT1);
	पूर्ण

	estat = encx24j600_पढ़ो_reg(priv, ESTAT);
	अगर (estat & PHYDPX) अणु
		encx24j600_set_bits(priv, MACON2, FULDPX);
		encx24j600_ग_लिखो_reg(priv, MABBIPG, 0x15);
	पूर्ण अन्यथा अणु
		encx24j600_clr_bits(priv, MACON2, FULDPX);
		encx24j600_ग_लिखो_reg(priv, MABBIPG, 0x12);
		/* Max retransmittions attempt  */
		encx24j600_ग_लिखो_reg(priv, MACLCON, 0x370f);
	पूर्ण

	वापस 0;
पूर्ण

/* Access the PHY to determine link status */
अटल व्योम encx24j600_check_link_status(काष्ठा encx24j600_priv *priv)
अणु
	काष्ठा net_device *dev = priv->ndev;
	u16 estat;

	estat = encx24j600_पढ़ो_reg(priv, ESTAT);

	अगर (estat & PHYLNK) अणु
		अगर (priv->स्वतःneg == AUTONEG_ENABLE)
			encx24j600_रुको_क्रम_स्वतःneg(priv);

		netअगर_carrier_on(dev);
		netअगर_info(priv, अगरup, dev, "link up\n");
	पूर्ण अन्यथा अणु
		netअगर_info(priv, अगरकरोwn, dev, "link down\n");

		/* Re-enable स्वतःneg since we won't know what we might be
		 * connected to when the link is brought back up again.
		 */
		priv->स्वतःneg  = AUTONEG_ENABLE;
		priv->full_duplex = true;
		priv->speed = SPEED_100;
		netअगर_carrier_off(dev);
	पूर्ण
पूर्ण

अटल व्योम encx24j600_पूर्णांक_link_handler(काष्ठा encx24j600_priv *priv)
अणु
	काष्ठा net_device *dev = priv->ndev;

	netअगर_dbg(priv, पूर्णांकr, dev, "%s", __func__);
	encx24j600_check_link_status(priv);
	encx24j600_clr_bits(priv, EIR, LINKIF);
पूर्ण

अटल व्योम encx24j600_tx_complete(काष्ठा encx24j600_priv *priv, bool err)
अणु
	काष्ठा net_device *dev = priv->ndev;

	अगर (!priv->tx_skb) अणु
		BUG();
		वापस;
	पूर्ण

	mutex_lock(&priv->lock);

	अगर (err)
		dev->stats.tx_errors++;
	अन्यथा
		dev->stats.tx_packets++;

	dev->stats.tx_bytes += priv->tx_skb->len;

	encx24j600_clr_bits(priv, EIR, TXIF | TXABTIF);

	netअगर_dbg(priv, tx_करोne, dev, "TX Done%s\n", err ? ": Err" : "");

	dev_kमुक्त_skb(priv->tx_skb);
	priv->tx_skb = शून्य;

	netअगर_wake_queue(dev);

	mutex_unlock(&priv->lock);
पूर्ण

अटल पूर्णांक encx24j600_receive_packet(काष्ठा encx24j600_priv *priv,
				     काष्ठा rsv *rsv)
अणु
	काष्ठा net_device *dev = priv->ndev;
	काष्ठा sk_buff *skb = netdev_alloc_skb(dev, rsv->len + NET_IP_ALIGN);

	अगर (!skb) अणु
		pr_err_ratelimited("RX: OOM: packet dropped\n");
		dev->stats.rx_dropped++;
		वापस -ENOMEM;
	पूर्ण
	skb_reserve(skb, NET_IP_ALIGN);
	encx24j600_raw_पढ़ो(priv, RRXDATA, skb_put(skb, rsv->len), rsv->len);

	अगर (netअगर_msg_pktdata(priv))
		dump_packet("RX", skb->len, skb->data);

	skb->dev = dev;
	skb->protocol = eth_type_trans(skb, dev);
	skb->ip_summed = CHECKSUM_COMPLETE;

	/* Maपूर्णांकain stats */
	dev->stats.rx_packets++;
	dev->stats.rx_bytes += rsv->len;

	netअगर_rx(skb);

	वापस 0;
पूर्ण

अटल व्योम encx24j600_rx_packets(काष्ठा encx24j600_priv *priv, u8 packet_count)
अणु
	काष्ठा net_device *dev = priv->ndev;

	जबतक (packet_count--) अणु
		काष्ठा rsv rsv;
		u16 newrxtail;

		encx24j600_ग_लिखो_reg(priv, ERXRDPT, priv->next_packet);
		encx24j600_raw_पढ़ो(priv, RRXDATA, (u8 *)&rsv, माप(rsv));

		अगर (netअगर_msg_rx_status(priv))
			encx24j600_dump_rsv(priv, __func__, &rsv);

		अगर (!RSV_GETBIT(rsv.rxstat, RSV_RXOK) ||
		    (rsv.len > MAX_FRAMELEN)) अणु
			netअगर_err(priv, rx_err, dev, "RX Error %04x\n",
				  rsv.rxstat);
			dev->stats.rx_errors++;

			अगर (RSV_GETBIT(rsv.rxstat, RSV_CRCERROR))
				dev->stats.rx_crc_errors++;
			अगर (RSV_GETBIT(rsv.rxstat, RSV_LENCHECKERR))
				dev->stats.rx_frame_errors++;
			अगर (rsv.len > MAX_FRAMELEN)
				dev->stats.rx_over_errors++;
		पूर्ण अन्यथा अणु
			encx24j600_receive_packet(priv, &rsv);
		पूर्ण

		priv->next_packet = rsv.next_packet;

		newrxtail = priv->next_packet - 2;
		अगर (newrxtail == ENC_RX_BUF_START)
			newrxtail = SRAM_SIZE - 2;

		encx24j600_cmd(priv, SETPKTDEC);
		encx24j600_ग_लिखो_reg(priv, ERXTAIL, newrxtail);
	पूर्ण
पूर्ण

अटल irqवापस_t encx24j600_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा encx24j600_priv *priv = dev_id;
	काष्ठा net_device *dev = priv->ndev;
	पूर्णांक eir;

	/* Clear पूर्णांकerrupts */
	encx24j600_cmd(priv, CLREIE);

	eir = encx24j600_पढ़ो_reg(priv, EIR);

	अगर (eir & LINKIF)
		encx24j600_पूर्णांक_link_handler(priv);

	अगर (eir & TXIF)
		encx24j600_tx_complete(priv, false);

	अगर (eir & TXABTIF)
		encx24j600_tx_complete(priv, true);

	अगर (eir & RXABTIF) अणु
		अगर (eir & PCFULIF) अणु
			/* Packet counter is full */
			netअगर_err(priv, rx_err, dev, "Packet counter full\n");
		पूर्ण
		dev->stats.rx_dropped++;
		encx24j600_clr_bits(priv, EIR, RXABTIF);
	पूर्ण

	अगर (eir & PKTIF) अणु
		u8 packet_count;

		mutex_lock(&priv->lock);

		packet_count = encx24j600_पढ़ो_reg(priv, ESTAT) & 0xff;
		जबतक (packet_count) अणु
			encx24j600_rx_packets(priv, packet_count);
			packet_count = encx24j600_पढ़ो_reg(priv, ESTAT) & 0xff;
		पूर्ण

		mutex_unlock(&priv->lock);
	पूर्ण

	/* Enable पूर्णांकerrupts */
	encx24j600_cmd(priv, SETEIE);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक encx24j600_soft_reset(काष्ठा encx24j600_priv *priv)
अणु
	पूर्णांक ret = 0;
	पूर्णांक समयout;
	u16 eudast;

	/* Write and verअगरy a test value to EUDAST */
	regcache_cache_bypass(priv->ctx.regmap, true);
	समयout = 10;
	करो अणु
		encx24j600_ग_लिखो_reg(priv, EUDAST, EUDAST_TEST_VAL);
		eudast = encx24j600_पढ़ो_reg(priv, EUDAST);
		usleep_range(25, 100);
	पूर्ण जबतक ((eudast != EUDAST_TEST_VAL) && --समयout);
	regcache_cache_bypass(priv->ctx.regmap, false);

	अगर (समयout == 0) अणु
		ret = -ETIMEDOUT;
		जाओ err_out;
	पूर्ण

	/* Wait क्रम CLKRDY to become set */
	समयout = 10;
	जबतक (!(encx24j600_पढ़ो_reg(priv, ESTAT) & CLKRDY) && --समयout)
		usleep_range(25, 100);

	अगर (समयout == 0) अणु
		ret = -ETIMEDOUT;
		जाओ err_out;
	पूर्ण

	/* Issue a System Reset command */
	encx24j600_cmd(priv, SETETHRST);
	usleep_range(25, 100);

	/* Confirm that EUDAST has 0000h after प्रणाली reset */
	अगर (encx24j600_पढ़ो_reg(priv, EUDAST) != 0) अणु
		ret = -EINVAL;
		जाओ err_out;
	पूर्ण

	/* Wait क्रम PHY रेजिस्टर and status bits to become available */
	usleep_range(256, 1000);

err_out:
	वापस ret;
पूर्ण

अटल पूर्णांक encx24j600_hw_reset(काष्ठा encx24j600_priv *priv)
अणु
	पूर्णांक ret;

	mutex_lock(&priv->lock);
	ret = encx24j600_soft_reset(priv);
	mutex_unlock(&priv->lock);

	वापस ret;
पूर्ण

अटल व्योम encx24j600_reset_hw_tx(काष्ठा encx24j600_priv *priv)
अणु
	encx24j600_set_bits(priv, ECON2, TXRST);
	encx24j600_clr_bits(priv, ECON2, TXRST);
पूर्ण

अटल व्योम encx24j600_hw_init_tx(काष्ठा encx24j600_priv *priv)
अणु
	/* Reset TX */
	encx24j600_reset_hw_tx(priv);

	/* Clear the TXIF flag अगर were previously set */
	encx24j600_clr_bits(priv, EIR, TXIF | TXABTIF);

	/* Write the Tx Buffer poपूर्णांकer */
	encx24j600_ग_लिखो_reg(priv, EGPWRPT, ENC_TX_BUF_START);
पूर्ण

अटल व्योम encx24j600_hw_init_rx(काष्ठा encx24j600_priv *priv)
अणु
	encx24j600_cmd(priv, DISABLERX);

	/* Set up RX packet start address in the SRAM */
	encx24j600_ग_लिखो_reg(priv, ERXST, ENC_RX_BUF_START);

	/* Preload the RX Data poपूर्णांकer to the beginning of the RX area */
	encx24j600_ग_लिखो_reg(priv, ERXRDPT, ENC_RX_BUF_START);

	priv->next_packet = ENC_RX_BUF_START;

	/* Set up RX end address in the SRAM */
	encx24j600_ग_लिखो_reg(priv, ERXTAIL, ENC_SRAM_SIZE - 2);

	/* Reset the  user data poपूर्णांकers    */
	encx24j600_ग_लिखो_reg(priv, EUDAST, ENC_SRAM_SIZE);
	encx24j600_ग_लिखो_reg(priv, EUDAND, ENC_SRAM_SIZE + 1);

	/* Set Max Frame length */
	encx24j600_ग_लिखो_reg(priv, MAMXFL, MAX_FRAMELEN);
पूर्ण

अटल व्योम encx24j600_dump_config(काष्ठा encx24j600_priv *priv,
				   स्थिर अक्षर *msg)
अणु
	pr_info(DRV_NAME ": %s\n", msg);

	/* CHIP configuration */
	pr_info(DRV_NAME " ECON1:   %04X\n", encx24j600_पढ़ो_reg(priv, ECON1));
	pr_info(DRV_NAME " ECON2:   %04X\n", encx24j600_पढ़ो_reg(priv, ECON2));
	pr_info(DRV_NAME " ERXFCON: %04X\n", encx24j600_पढ़ो_reg(priv,
								 ERXFCON));
	pr_info(DRV_NAME " ESTAT:   %04X\n", encx24j600_पढ़ो_reg(priv, ESTAT));
	pr_info(DRV_NAME " EIR:     %04X\n", encx24j600_पढ़ो_reg(priv, EIR));
	pr_info(DRV_NAME " EIDLED:  %04X\n", encx24j600_पढ़ो_reg(priv, EIDLED));

	/* MAC layer configuration */
	pr_info(DRV_NAME " MACON1:  %04X\n", encx24j600_पढ़ो_reg(priv, MACON1));
	pr_info(DRV_NAME " MACON2:  %04X\n", encx24j600_पढ़ो_reg(priv, MACON2));
	pr_info(DRV_NAME " MAIPG:   %04X\n", encx24j600_पढ़ो_reg(priv, MAIPG));
	pr_info(DRV_NAME " MACLCON: %04X\n", encx24j600_पढ़ो_reg(priv,
								 MACLCON));
	pr_info(DRV_NAME " MABBIPG: %04X\n", encx24j600_पढ़ो_reg(priv,
								 MABBIPG));

	/* PHY configuation */
	pr_info(DRV_NAME " PHCON1:  %04X\n", encx24j600_पढ़ो_phy(priv, PHCON1));
	pr_info(DRV_NAME " PHCON2:  %04X\n", encx24j600_पढ़ो_phy(priv, PHCON2));
	pr_info(DRV_NAME " PHANA:   %04X\n", encx24j600_पढ़ो_phy(priv, PHANA));
	pr_info(DRV_NAME " PHANLPA: %04X\n", encx24j600_पढ़ो_phy(priv,
								 PHANLPA));
	pr_info(DRV_NAME " PHANE:   %04X\n", encx24j600_पढ़ो_phy(priv, PHANE));
	pr_info(DRV_NAME " PHSTAT1: %04X\n", encx24j600_पढ़ो_phy(priv,
								 PHSTAT1));
	pr_info(DRV_NAME " PHSTAT2: %04X\n", encx24j600_पढ़ो_phy(priv,
								 PHSTAT2));
	pr_info(DRV_NAME " PHSTAT3: %04X\n", encx24j600_पढ़ो_phy(priv,
								 PHSTAT3));
पूर्ण

अटल व्योम encx24j600_set_rxfilter_mode(काष्ठा encx24j600_priv *priv)
अणु
	चयन (priv->rxfilter) अणु
	हाल RXFILTER_PROMISC:
		encx24j600_set_bits(priv, MACON1, PASSALL);
		encx24j600_ग_लिखो_reg(priv, ERXFCON, UCEN | MCEN | NOTMEEN);
		अवरोध;
	हाल RXFILTER_MULTI:
		encx24j600_clr_bits(priv, MACON1, PASSALL);
		encx24j600_ग_लिखो_reg(priv, ERXFCON, UCEN | CRCEN | BCEN | MCEN);
		अवरोध;
	हाल RXFILTER_NORMAL:
	शेष:
		encx24j600_clr_bits(priv, MACON1, PASSALL);
		encx24j600_ग_लिखो_reg(priv, ERXFCON, UCEN | CRCEN | BCEN);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम encx24j600_hw_init(काष्ठा encx24j600_priv *priv)
अणु
	u16 macon2;

	priv->hw_enabled = false;

	/* PHY Leds: link status,
	 * LEDA: Link State + collision events
	 * LEDB: Link State + transmit/receive events
	 */
	encx24j600_update_reg(priv, EIDLED, 0xff00, 0xcb00);

	/* Loopback disabled */
	encx24j600_ग_लिखो_reg(priv, MACON1, 0x9);

	/* पूर्णांकerpacket gap value */
	encx24j600_ग_लिखो_reg(priv, MAIPG, 0x0c12);

	/* Write the स्वतः negotiation pattern */
	encx24j600_ग_लिखो_phy(priv, PHANA, PHANA_DEFAULT);

	encx24j600_update_phcon1(priv);
	encx24j600_check_link_status(priv);

	macon2 = MACON2_RSV1 | TXCRCEN | PADCFG0 | PADCFG2 | MACON2_DEFER;
	अगर ((priv->स्वतःneg == AUTONEG_DISABLE) && priv->full_duplex)
		macon2 |= FULDPX;

	encx24j600_set_bits(priv, MACON2, macon2);

	priv->rxfilter = RXFILTER_NORMAL;
	encx24j600_set_rxfilter_mode(priv);

	/* Program the Maximum frame length */
	encx24j600_ग_लिखो_reg(priv, MAMXFL, MAX_FRAMELEN);

	/* Init Tx poपूर्णांकers */
	encx24j600_hw_init_tx(priv);

	/* Init Rx poपूर्णांकers */
	encx24j600_hw_init_rx(priv);

	अगर (netअगर_msg_hw(priv))
		encx24j600_dump_config(priv, "Hw is initialized");
पूर्ण

अटल व्योम encx24j600_hw_enable(काष्ठा encx24j600_priv *priv)
अणु
	/* Clear the पूर्णांकerrupt flags in हाल was set */
	encx24j600_clr_bits(priv, EIR, (PCFULIF | RXABTIF | TXABTIF | TXIF |
					PKTIF | LINKIF));

	/* Enable the पूर्णांकerrupts */
	encx24j600_ग_लिखो_reg(priv, EIE, (PCFULIE | RXABTIE | TXABTIE | TXIE |
					 PKTIE | LINKIE | INTIE));

	/* Enable RX */
	encx24j600_cmd(priv, ENABLERX);

	priv->hw_enabled = true;
पूर्ण

अटल व्योम encx24j600_hw_disable(काष्ठा encx24j600_priv *priv)
अणु
	/* Disable all पूर्णांकerrupts */
	encx24j600_ग_लिखो_reg(priv, EIE, 0);

	/* Disable RX */
	encx24j600_cmd(priv, DISABLERX);

	priv->hw_enabled = false;
पूर्ण

अटल पूर्णांक encx24j600_setlink(काष्ठा net_device *dev, u8 स्वतःneg, u16 speed,
			      u8 duplex)
अणु
	काष्ठा encx24j600_priv *priv = netdev_priv(dev);
	पूर्णांक ret = 0;

	अगर (!priv->hw_enabled) अणु
		/* link is in low घातer mode now; duplex setting
		 * will take effect on next encx24j600_hw_init()
		 */
		अगर (speed == SPEED_10 || speed == SPEED_100) अणु
			priv->स्वतःneg = (स्वतःneg == AUTONEG_ENABLE);
			priv->full_duplex = (duplex == DUPLEX_FULL);
			priv->speed = (speed == SPEED_100);
		पूर्ण अन्यथा अणु
			netअगर_warn(priv, link, dev, "unsupported link speed setting\n");
			/*speeds other than SPEED_10 and SPEED_100 */
			/*are not supported by chip */
			ret = -EOPNOTSUPP;
		पूर्ण
	पूर्ण अन्यथा अणु
		netअगर_warn(priv, link, dev, "Warning: hw must be disabled to set link mode\n");
		ret = -EBUSY;
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम encx24j600_hw_get_macaddr(काष्ठा encx24j600_priv *priv,
				      अचिन्हित अक्षर *ethaddr)
अणु
	अचिन्हित लघु val;

	val = encx24j600_पढ़ो_reg(priv, MAADR1);

	ethaddr[0] = val & 0x00ff;
	ethaddr[1] = (val & 0xff00) >> 8;

	val = encx24j600_पढ़ो_reg(priv, MAADR2);

	ethaddr[2] = val & 0x00ffU;
	ethaddr[3] = (val & 0xff00U) >> 8;

	val = encx24j600_पढ़ो_reg(priv, MAADR3);

	ethaddr[4] = val & 0x00ffU;
	ethaddr[5] = (val & 0xff00U) >> 8;
पूर्ण

/* Program the hardware MAC address from dev->dev_addr.*/
अटल पूर्णांक encx24j600_set_hw_macaddr(काष्ठा net_device *dev)
अणु
	काष्ठा encx24j600_priv *priv = netdev_priv(dev);

	अगर (priv->hw_enabled) अणु
		netअगर_info(priv, drv, dev, "Hardware must be disabled to set Mac address\n");
		वापस -EBUSY;
	पूर्ण

	mutex_lock(&priv->lock);

	netअगर_info(priv, drv, dev, "%s: Setting MAC address to %pM\n",
		   dev->name, dev->dev_addr);

	encx24j600_ग_लिखो_reg(priv, MAADR3, (dev->dev_addr[4] |
			     dev->dev_addr[5] << 8));
	encx24j600_ग_लिखो_reg(priv, MAADR2, (dev->dev_addr[2] |
			     dev->dev_addr[3] << 8));
	encx24j600_ग_लिखो_reg(priv, MAADR1, (dev->dev_addr[0] |
			     dev->dev_addr[1] << 8));

	mutex_unlock(&priv->lock);

	वापस 0;
पूर्ण

/* Store the new hardware address in dev->dev_addr, and update the MAC.*/
अटल पूर्णांक encx24j600_set_mac_address(काष्ठा net_device *dev, व्योम *addr)
अणु
	काष्ठा sockaddr *address = addr;

	अगर (netअगर_running(dev))
		वापस -EBUSY;
	अगर (!is_valid_ether_addr(address->sa_data))
		वापस -EADDRNOTAVAIL;

	स_नकल(dev->dev_addr, address->sa_data, dev->addr_len);
	वापस encx24j600_set_hw_macaddr(dev);
पूर्ण

अटल पूर्णांक encx24j600_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा encx24j600_priv *priv = netdev_priv(dev);

	पूर्णांक ret = request_thपढ़ोed_irq(priv->ctx.spi->irq, शून्य, encx24j600_isr,
				       IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
				       DRV_NAME, priv);
	अगर (unlikely(ret < 0)) अणु
		netdev_err(dev, "request irq %d failed (ret = %d)\n",
			   priv->ctx.spi->irq, ret);
		वापस ret;
	पूर्ण

	encx24j600_hw_disable(priv);
	encx24j600_hw_init(priv);
	encx24j600_hw_enable(priv);
	netअगर_start_queue(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक encx24j600_stop(काष्ठा net_device *dev)
अणु
	काष्ठा encx24j600_priv *priv = netdev_priv(dev);

	netअगर_stop_queue(dev);
	मुक्त_irq(priv->ctx.spi->irq, priv);
	वापस 0;
पूर्ण

अटल व्योम encx24j600_setrx_proc(काष्ठा kthपढ़ो_work *ws)
अणु
	काष्ठा encx24j600_priv *priv =
			container_of(ws, काष्ठा encx24j600_priv, setrx_work);

	mutex_lock(&priv->lock);
	encx24j600_set_rxfilter_mode(priv);
	mutex_unlock(&priv->lock);
पूर्ण

अटल व्योम encx24j600_set_multicast_list(काष्ठा net_device *dev)
अणु
	काष्ठा encx24j600_priv *priv = netdev_priv(dev);
	पूर्णांक oldfilter = priv->rxfilter;

	अगर (dev->flags & IFF_PROMISC) अणु
		netअगर_dbg(priv, link, dev, "promiscuous mode\n");
		priv->rxfilter = RXFILTER_PROMISC;
	पूर्ण अन्यथा अगर ((dev->flags & IFF_ALLMULTI) || !netdev_mc_empty(dev)) अणु
		netअगर_dbg(priv, link, dev, "%smulticast mode\n",
			  (dev->flags & IFF_ALLMULTI) ? "all-" : "");
		priv->rxfilter = RXFILTER_MULTI;
	पूर्ण अन्यथा अणु
		netअगर_dbg(priv, link, dev, "normal mode\n");
		priv->rxfilter = RXFILTER_NORMAL;
	पूर्ण

	अगर (oldfilter != priv->rxfilter)
		kthपढ़ो_queue_work(&priv->kworker, &priv->setrx_work);
पूर्ण

अटल व्योम encx24j600_hw_tx(काष्ठा encx24j600_priv *priv)
अणु
	काष्ठा net_device *dev = priv->ndev;

	netअगर_info(priv, tx_queued, dev, "TX Packet Len:%d\n",
		   priv->tx_skb->len);

	अगर (netअगर_msg_pktdata(priv))
		dump_packet("TX", priv->tx_skb->len, priv->tx_skb->data);

	अगर (encx24j600_पढ़ो_reg(priv, EIR) & TXABTIF)
		/* Last transmition पातed due to error. Reset TX पूर्णांकerface */
		encx24j600_reset_hw_tx(priv);

	/* Clear the TXIF flag अगर were previously set */
	encx24j600_clr_bits(priv, EIR, TXIF);

	/* Set the data poपूर्णांकer to the TX buffer address in the SRAM */
	encx24j600_ग_लिखो_reg(priv, EGPWRPT, ENC_TX_BUF_START);

	/* Copy the packet पूर्णांकo the SRAM */
	encx24j600_raw_ग_लिखो(priv, WGPDATA, (u8 *)priv->tx_skb->data,
			     priv->tx_skb->len);

	/* Program the Tx buffer start poपूर्णांकer */
	encx24j600_ग_लिखो_reg(priv, ETXST, ENC_TX_BUF_START);

	/* Program the packet length */
	encx24j600_ग_लिखो_reg(priv, ETXLEN, priv->tx_skb->len);

	/* Start the transmission */
	encx24j600_cmd(priv, SETTXRTS);
पूर्ण

अटल व्योम encx24j600_tx_proc(काष्ठा kthपढ़ो_work *ws)
अणु
	काष्ठा encx24j600_priv *priv =
			container_of(ws, काष्ठा encx24j600_priv, tx_work);

	mutex_lock(&priv->lock);
	encx24j600_hw_tx(priv);
	mutex_unlock(&priv->lock);
पूर्ण

अटल netdev_tx_t encx24j600_tx(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा encx24j600_priv *priv = netdev_priv(dev);

	netअगर_stop_queue(dev);

	/* save the बारtamp */
	netअगर_trans_update(dev);

	/* Remember the skb क्रम deferred processing */
	priv->tx_skb = skb;

	kthपढ़ो_queue_work(&priv->kworker, &priv->tx_work);

	वापस NETDEV_TX_OK;
पूर्ण

/* Deal with a transmit समयout */
अटल व्योम encx24j600_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा encx24j600_priv *priv = netdev_priv(dev);

	netअगर_err(priv, tx_err, dev, "TX timeout at %ld, latency %ld\n",
		  jअगरfies, jअगरfies - dev_trans_start(dev));

	dev->stats.tx_errors++;
	netअगर_wake_queue(dev);
पूर्ण

अटल पूर्णांक encx24j600_get_regs_len(काष्ठा net_device *dev)
अणु
	वापस SFR_REG_COUNT;
पूर्ण

अटल व्योम encx24j600_get_regs(काष्ठा net_device *dev,
				काष्ठा ethtool_regs *regs, व्योम *p)
अणु
	काष्ठा encx24j600_priv *priv = netdev_priv(dev);
	u16 *buff = p;
	u8 reg;

	regs->version = 1;
	mutex_lock(&priv->lock);
	क्रम (reg = 0; reg < SFR_REG_COUNT; reg += 2) अणु
		अचिन्हित पूर्णांक val = 0;
		/* ignore errors क्रम unपढ़ोable रेजिस्टरs */
		regmap_पढ़ो(priv->ctx.regmap, reg, &val);
		buff[reg] = val & 0xffff;
	पूर्ण
	mutex_unlock(&priv->lock);
पूर्ण

अटल व्योम encx24j600_get_drvinfo(काष्ठा net_device *dev,
				   काष्ठा ethtool_drvinfo *info)
अणु
	strlcpy(info->driver, DRV_NAME, माप(info->driver));
	strlcpy(info->version, DRV_VERSION, माप(info->version));
	strlcpy(info->bus_info, dev_name(dev->dev.parent),
		माप(info->bus_info));
पूर्ण

अटल पूर्णांक encx24j600_get_link_ksettings(काष्ठा net_device *dev,
					 काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा encx24j600_priv *priv = netdev_priv(dev);
	u32 supported;

	supported = SUPPORTED_10baseT_Half | SUPPORTED_10baseT_Full |
			 SUPPORTED_100baseT_Half | SUPPORTED_100baseT_Full |
			 SUPPORTED_Autoneg | SUPPORTED_TP;

	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.supported,
						supported);

	cmd->base.speed = priv->speed;
	cmd->base.duplex = priv->full_duplex ? DUPLEX_FULL : DUPLEX_HALF;
	cmd->base.port = PORT_TP;
	cmd->base.स्वतःneg = priv->स्वतःneg ? AUTONEG_ENABLE : AUTONEG_DISABLE;

	वापस 0;
पूर्ण

अटल पूर्णांक
encx24j600_set_link_ksettings(काष्ठा net_device *dev,
			      स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	वापस encx24j600_setlink(dev, cmd->base.स्वतःneg,
				  cmd->base.speed, cmd->base.duplex);
पूर्ण

अटल u32 encx24j600_get_msglevel(काष्ठा net_device *dev)
अणु
	काष्ठा encx24j600_priv *priv = netdev_priv(dev);

	वापस priv->msg_enable;
पूर्ण

अटल व्योम encx24j600_set_msglevel(काष्ठा net_device *dev, u32 val)
अणु
	काष्ठा encx24j600_priv *priv = netdev_priv(dev);

	priv->msg_enable = val;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops encx24j600_ethtool_ops = अणु
	.get_drvinfo = encx24j600_get_drvinfo,
	.get_msglevel = encx24j600_get_msglevel,
	.set_msglevel = encx24j600_set_msglevel,
	.get_regs_len = encx24j600_get_regs_len,
	.get_regs = encx24j600_get_regs,
	.get_link_ksettings = encx24j600_get_link_ksettings,
	.set_link_ksettings = encx24j600_set_link_ksettings,
पूर्ण;

अटल स्थिर काष्ठा net_device_ops encx24j600_netdev_ops = अणु
	.nकरो_खोलो = encx24j600_खोलो,
	.nकरो_stop = encx24j600_stop,
	.nकरो_start_xmit = encx24j600_tx,
	.nकरो_set_rx_mode = encx24j600_set_multicast_list,
	.nकरो_set_mac_address = encx24j600_set_mac_address,
	.nकरो_tx_समयout = encx24j600_tx_समयout,
	.nकरो_validate_addr = eth_validate_addr,
पूर्ण;

अटल पूर्णांक encx24j600_spi_probe(काष्ठा spi_device *spi)
अणु
	पूर्णांक ret;

	काष्ठा net_device *ndev;
	काष्ठा encx24j600_priv *priv;
	u16 eidled;

	ndev = alloc_etherdev(माप(काष्ठा encx24j600_priv));

	अगर (!ndev) अणु
		ret = -ENOMEM;
		जाओ error_out;
	पूर्ण

	priv = netdev_priv(ndev);
	spi_set_drvdata(spi, priv);
	dev_set_drvdata(&spi->dev, priv);
	SET_NETDEV_DEV(ndev, &spi->dev);

	priv->msg_enable = netअगर_msg_init(debug, DEFAULT_MSG_ENABLE);
	priv->ndev = ndev;

	/* Default configuration PHY configuration */
	priv->full_duplex = true;
	priv->स्वतःneg = AUTONEG_ENABLE;
	priv->speed = SPEED_100;

	priv->ctx.spi = spi;
	devm_regmap_init_encx24j600(&spi->dev, &priv->ctx);
	ndev->irq = spi->irq;
	ndev->netdev_ops = &encx24j600_netdev_ops;

	mutex_init(&priv->lock);

	/* Reset device and check अगर it is connected */
	अगर (encx24j600_hw_reset(priv)) अणु
		netअगर_err(priv, probe, ndev,
			  DRV_NAME ": Chip is not detected\n");
		ret = -EIO;
		जाओ out_मुक्त;
	पूर्ण

	/* Initialize the device HW to the consistent state */
	encx24j600_hw_init(priv);

	kthपढ़ो_init_worker(&priv->kworker);
	kthपढ़ो_init_work(&priv->tx_work, encx24j600_tx_proc);
	kthपढ़ो_init_work(&priv->setrx_work, encx24j600_setrx_proc);

	priv->kworker_task = kthपढ़ो_run(kthपढ़ो_worker_fn, &priv->kworker,
					 "encx24j600");

	अगर (IS_ERR(priv->kworker_task)) अणु
		ret = PTR_ERR(priv->kworker_task);
		जाओ out_मुक्त;
	पूर्ण

	/* Get the MAC address from the chip */
	encx24j600_hw_get_macaddr(priv, ndev->dev_addr);

	ndev->ethtool_ops = &encx24j600_ethtool_ops;

	ret = रेजिस्टर_netdev(ndev);
	अगर (unlikely(ret)) अणु
		netअगर_err(priv, probe, ndev, "Error %d initializing card encx24j600 card\n",
			  ret);
		जाओ out_stop;
	पूर्ण

	eidled = encx24j600_पढ़ो_reg(priv, EIDLED);
	अगर (((eidled & DEVID_MASK) >> DEVID_SHIFT) != ENCX24J600_DEV_ID) अणु
		ret = -EINVAL;
		जाओ out_unरेजिस्टर;
	पूर्ण

	netअगर_info(priv, probe, ndev, "Silicon rev ID: 0x%02x\n",
		   (eidled & REVID_MASK) >> REVID_SHIFT);

	netअगर_info(priv, drv, priv->ndev, "MAC address %pM\n", ndev->dev_addr);

	वापस ret;

out_unरेजिस्टर:
	unरेजिस्टर_netdev(priv->ndev);
out_stop:
	kthपढ़ो_stop(priv->kworker_task);
out_मुक्त:
	मुक्त_netdev(ndev);

error_out:
	वापस ret;
पूर्ण

अटल पूर्णांक encx24j600_spi_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा encx24j600_priv *priv = dev_get_drvdata(&spi->dev);

	unरेजिस्टर_netdev(priv->ndev);
	kthपढ़ो_stop(priv->kworker_task);

	मुक्त_netdev(priv->ndev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा spi_device_id encx24j600_spi_id_table[] = अणु
	अणु .name = "encx24j600" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, encx24j600_spi_id_table);

अटल काष्ठा spi_driver encx24j600_spi_net_driver = अणु
	.driver = अणु
		.name	= DRV_NAME,
		.owner	= THIS_MODULE,
		.bus	= &spi_bus_type,
	पूर्ण,
	.probe		= encx24j600_spi_probe,
	.हटाओ		= encx24j600_spi_हटाओ,
	.id_table	= encx24j600_spi_id_table,
पूर्ण;

module_spi_driver(encx24j600_spi_net_driver);

MODULE_DESCRIPTION(DRV_NAME " ethernet driver");
MODULE_AUTHOR("Jon Ringle <jringle@gridpoint.com>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("spi:" DRV_NAME);
