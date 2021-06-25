<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*******************************************************************************

  Copyright(c) 2006 Tundra Semiconductor Corporation.


*******************************************************************************/

/* This driver is based on the driver code originally developed
 * क्रम the Intel IOC80314 (ForestLake) Gigabit Ethernet by
 * scott.wood@बारys.com  * Copyright (C) 2003 TimeSys Corporation
 *
 * Currently changes from original version are:
 * - porting to Tsi108-based platक्रमm and kernel 2.6 (kong.lai@tundra.com)
 * - modअगरications to handle two ports independently and support क्रम
 *   additional PHY devices (alexandre.bounine@tundra.com)
 * - Get hardware inक्रमmation from platक्रमm device. (tie-fei.zang@मुक्तscale.com)
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/net.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/delay.h>
#समावेश <linux/crc32.h>
#समावेश <linux/mii.h>
#समावेश <linux/device.h>
#समावेश <linux/pci.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/समयr.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/gfp.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/tsi108.h>

#समावेश "tsi108_eth.h"

#घोषणा MII_READ_DELAY 10000	/* max link रुको समय in msec */

#घोषणा TSI108_RXRING_LEN     256

/* NOTE: The driver currently करोes not support receiving packets
 * larger than the buffer size, so करोn't decrease this (unless you
 * want to add such support).
 */
#घोषणा TSI108_RXBUF_SIZE     1536

#घोषणा TSI108_TXRING_LEN     256

#घोषणा TSI108_TX_INT_FREQ    64

/* Check the phy status every half a second. */
#घोषणा CHECK_PHY_INTERVAL (HZ/2)

अटल पूर्णांक tsi108_init_one(काष्ठा platक्रमm_device *pdev);
अटल पूर्णांक tsi108_ether_हटाओ(काष्ठा platक्रमm_device *pdev);

काष्ठा tsi108_prv_data अणु
	व्योम  __iomem *regs;	/* Base of normal regs */
	व्योम  __iomem *phyregs;	/* Base of रेजिस्टर bank used क्रम PHY access */

	काष्ठा net_device *dev;
	काष्ठा napi_काष्ठा napi;

	अचिन्हित पूर्णांक phy;		/* Index of PHY क्रम this पूर्णांकerface */
	अचिन्हित पूर्णांक irq_num;
	अचिन्हित पूर्णांक id;
	अचिन्हित पूर्णांक phy_type;

	काष्ठा समयr_list समयr;/* Timer that triggers the check phy function */
	अचिन्हित पूर्णांक rxtail;	/* Next entry in rxring to पढ़ो */
	अचिन्हित पूर्णांक rxhead;	/* Next entry in rxring to give a new buffer */
	अचिन्हित पूर्णांक rxमुक्त;	/* Number of मुक्त, allocated RX buffers */

	अचिन्हित पूर्णांक rxpending;	/* Non-zero अगर there are still descriptors
				 * to be processed from a previous descriptor
				 * पूर्णांकerrupt condition that has been cleared */

	अचिन्हित पूर्णांक txtail;	/* Next TX descriptor to check status on */
	अचिन्हित पूर्णांक txhead;	/* Next TX descriptor to use */

	/* Number of मुक्त TX descriptors.  This could be calculated from
	 * rxhead and rxtail अगर one descriptor were left unused to disambiguate
	 * full and empty conditions, but it's simpler to just keep track
	 * explicitly. */

	अचिन्हित पूर्णांक txमुक्त;

	अचिन्हित पूर्णांक phy_ok;		/* The PHY is currently घातered on. */

	/* PHY status (duplex is 1 क्रम half, 2 क्रम full,
	 * so that the शेष 0 indicates that neither has
	 * yet been configured). */

	अचिन्हित पूर्णांक link_up;
	अचिन्हित पूर्णांक speed;
	अचिन्हित पूर्णांक duplex;

	tx_desc *txring;
	rx_desc *rxring;
	काष्ठा sk_buff *txskbs[TSI108_TXRING_LEN];
	काष्ठा sk_buff *rxskbs[TSI108_RXRING_LEN];

	dma_addr_t txdma, rxdma;

	/* txlock nests in misघड़ी and phy_lock */

	spinlock_t txlock, misघड़ी;

	/* stats is used to hold the upper bits of each hardware counter,
	 * and पंचांगpstats is used to hold the full values क्रम वापसing
	 * to the caller of get_stats().  They must be separate in हाल
	 * an overflow पूर्णांकerrupt occurs beक्रमe the stats are consumed.
	 */

	काष्ठा net_device_stats stats;
	काष्ठा net_device_stats पंचांगpstats;

	/* These stats are kept separate in hardware, thus require inभागidual
	 * fields क्रम handling carry.  They are combined in get_stats.
	 */

	अचिन्हित दीर्घ rx_fcs;	/* Add to rx_frame_errors */
	अचिन्हित दीर्घ rx_लघु_fcs;	/* Add to rx_frame_errors */
	अचिन्हित दीर्घ rx_दीर्घ_fcs;	/* Add to rx_frame_errors */
	अचिन्हित दीर्घ rx_underruns;	/* Add to rx_length_errors */
	अचिन्हित दीर्घ rx_overruns;	/* Add to rx_length_errors */

	अचिन्हित दीर्घ tx_coll_पात;	/* Add to tx_पातed_errors/collisions */
	अचिन्हित दीर्घ tx_छोड़ो_drop;	/* Add to tx_पातed_errors */

	अचिन्हित दीर्घ mc_hash[16];
	u32 msg_enable;			/* debug message level */
	काष्ठा mii_अगर_info mii_अगर;
	अचिन्हित पूर्णांक init_media;

	काष्ठा platक्रमm_device *pdev;
पूर्ण;

/* Structure क्रम a device driver */

अटल काष्ठा platक्रमm_driver tsi_eth_driver = अणु
	.probe = tsi108_init_one,
	.हटाओ = tsi108_ether_हटाओ,
	.driver	= अणु
		.name = "tsi-ethernet",
	पूर्ण,
पूर्ण;

अटल व्योम tsi108_समयd_checker(काष्ठा समयr_list *t);

#अगर_घोषित DEBUG
अटल व्योम dump_eth_one(काष्ठा net_device *dev)
अणु
	काष्ठा tsi108_prv_data *data = netdev_priv(dev);

	prपूर्णांकk("Dumping %s...\n", dev->name);
	prपूर्णांकk("intstat %x intmask %x phy_ok %d"
	       " link %d speed %d duplex %d\n",
	       TSI_READ(TSI108_EC_INTSTAT),
	       TSI_READ(TSI108_EC_INTMASK), data->phy_ok,
	       data->link_up, data->speed, data->duplex);

	prपूर्णांकk("TX: head %d, tail %d, free %d, stat %x, estat %x, err %x\n",
	       data->txhead, data->txtail, data->txमुक्त,
	       TSI_READ(TSI108_EC_TXSTAT),
	       TSI_READ(TSI108_EC_TXESTAT),
	       TSI_READ(TSI108_EC_TXERR));

	prपूर्णांकk("RX: head %d, tail %d, free %d, stat %x,"
	       " estat %x, err %x, pending %d\n\n",
	       data->rxhead, data->rxtail, data->rxमुक्त,
	       TSI_READ(TSI108_EC_RXSTAT),
	       TSI_READ(TSI108_EC_RXESTAT),
	       TSI_READ(TSI108_EC_RXERR), data->rxpending);
पूर्ण
#पूर्ण_अगर

/* Synchronization is needed between the thपढ़ो and up/करोwn events.
 * Note that the PHY is accessed through the same रेजिस्टरs क्रम both
 * पूर्णांकerfaces, so this can't be made पूर्णांकerface-specअगरic.
 */

अटल DEFINE_SPINLOCK(phy_lock);

अटल पूर्णांक tsi108_पढ़ो_mii(काष्ठा tsi108_prv_data *data, पूर्णांक reg)
अणु
	अचिन्हित i;

	TSI_WRITE_PHY(TSI108_MAC_MII_ADDR,
				(data->phy << TSI108_MAC_MII_ADDR_PHY) |
				(reg << TSI108_MAC_MII_ADDR_REG));
	TSI_WRITE_PHY(TSI108_MAC_MII_CMD, 0);
	TSI_WRITE_PHY(TSI108_MAC_MII_CMD, TSI108_MAC_MII_CMD_READ);
	क्रम (i = 0; i < 100; i++) अणु
		अगर (!(TSI_READ_PHY(TSI108_MAC_MII_IND) &
		      (TSI108_MAC_MII_IND_NOTVALID | TSI108_MAC_MII_IND_BUSY)))
			अवरोध;
		udelay(10);
	पूर्ण

	अगर (i == 100)
		वापस 0xffff;
	अन्यथा
		वापस TSI_READ_PHY(TSI108_MAC_MII_DATAIN);
पूर्ण

अटल व्योम tsi108_ग_लिखो_mii(काष्ठा tsi108_prv_data *data,
				पूर्णांक reg, u16 val)
अणु
	अचिन्हित i = 100;
	TSI_WRITE_PHY(TSI108_MAC_MII_ADDR,
				(data->phy << TSI108_MAC_MII_ADDR_PHY) |
				(reg << TSI108_MAC_MII_ADDR_REG));
	TSI_WRITE_PHY(TSI108_MAC_MII_DATAOUT, val);
	जबतक (i--) अणु
		अगर(!(TSI_READ_PHY(TSI108_MAC_MII_IND) &
			TSI108_MAC_MII_IND_BUSY))
			अवरोध;
		udelay(10);
	पूर्ण
पूर्ण

अटल पूर्णांक tsi108_mdio_पढ़ो(काष्ठा net_device *dev, पूर्णांक addr, पूर्णांक reg)
अणु
	काष्ठा tsi108_prv_data *data = netdev_priv(dev);
	वापस tsi108_पढ़ो_mii(data, reg);
पूर्ण

अटल व्योम tsi108_mdio_ग_लिखो(काष्ठा net_device *dev, पूर्णांक addr, पूर्णांक reg, पूर्णांक val)
अणु
	काष्ठा tsi108_prv_data *data = netdev_priv(dev);
	tsi108_ग_लिखो_mii(data, reg, val);
पूर्ण

अटल अंतरभूत व्योम tsi108_ग_लिखो_tbi(काष्ठा tsi108_prv_data *data,
					पूर्णांक reg, u16 val)
अणु
	अचिन्हित i = 1000;
	TSI_WRITE(TSI108_MAC_MII_ADDR,
			     (0x1e << TSI108_MAC_MII_ADDR_PHY)
			     | (reg << TSI108_MAC_MII_ADDR_REG));
	TSI_WRITE(TSI108_MAC_MII_DATAOUT, val);
	जबतक(i--) अणु
		अगर(!(TSI_READ(TSI108_MAC_MII_IND) & TSI108_MAC_MII_IND_BUSY))
			वापस;
		udelay(10);
	पूर्ण
	prपूर्णांकk(KERN_ERR "%s function time out\n", __func__);
पूर्ण

अटल पूर्णांक mii_speed(काष्ठा mii_अगर_info *mii)
अणु
	पूर्णांक advert, lpa, val, media;
	पूर्णांक lpa2 = 0;
	पूर्णांक speed;

	अगर (!mii_link_ok(mii))
		वापस 0;

	val = (*mii->mdio_पढ़ो) (mii->dev, mii->phy_id, MII_BMSR);
	अगर ((val & BMSR_ANEGCOMPLETE) == 0)
		वापस 0;

	advert = (*mii->mdio_पढ़ो) (mii->dev, mii->phy_id, MII_ADVERTISE);
	lpa = (*mii->mdio_पढ़ो) (mii->dev, mii->phy_id, MII_LPA);
	media = mii_nway_result(advert & lpa);

	अगर (mii->supports_gmii)
		lpa2 = mii->mdio_पढ़ो(mii->dev, mii->phy_id, MII_STAT1000);

	speed = lpa2 & (LPA_1000FULL | LPA_1000HALF) ? 1000 :
			(media & (ADVERTISE_100FULL | ADVERTISE_100HALF) ? 100 : 10);
	वापस speed;
पूर्ण

अटल व्योम tsi108_check_phy(काष्ठा net_device *dev)
अणु
	काष्ठा tsi108_prv_data *data = netdev_priv(dev);
	u32 mac_cfg2_reg, portctrl_reg;
	u32 duplex;
	u32 speed;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&phy_lock, flags);

	अगर (!data->phy_ok)
		जाओ out;

	duplex = mii_check_media(&data->mii_अगर, netअगर_msg_link(data), data->init_media);
	data->init_media = 0;

	अगर (netअगर_carrier_ok(dev)) अणु

		speed = mii_speed(&data->mii_अगर);

		अगर ((speed != data->speed) || duplex) अणु

			mac_cfg2_reg = TSI_READ(TSI108_MAC_CFG2);
			portctrl_reg = TSI_READ(TSI108_EC_PORTCTRL);

			mac_cfg2_reg &= ~TSI108_MAC_CFG2_IFACE_MASK;

			अगर (speed == 1000) अणु
				mac_cfg2_reg |= TSI108_MAC_CFG2_GIG;
				portctrl_reg &= ~TSI108_EC_PORTCTRL_NOGIG;
			पूर्ण अन्यथा अणु
				mac_cfg2_reg |= TSI108_MAC_CFG2_NOGIG;
				portctrl_reg |= TSI108_EC_PORTCTRL_NOGIG;
			पूर्ण

			data->speed = speed;

			अगर (data->mii_अगर.full_duplex) अणु
				mac_cfg2_reg |= TSI108_MAC_CFG2_FULLDUPLEX;
				portctrl_reg &= ~TSI108_EC_PORTCTRL_HALFDUPLEX;
				data->duplex = 2;
			पूर्ण अन्यथा अणु
				mac_cfg2_reg &= ~TSI108_MAC_CFG2_FULLDUPLEX;
				portctrl_reg |= TSI108_EC_PORTCTRL_HALFDUPLEX;
				data->duplex = 1;
			पूर्ण

			TSI_WRITE(TSI108_MAC_CFG2, mac_cfg2_reg);
			TSI_WRITE(TSI108_EC_PORTCTRL, portctrl_reg);
		पूर्ण

		अगर (data->link_up == 0) अणु
			/* The manual says it can take 3-4 usecs क्रम the speed change
			 * to take effect.
			 */
			udelay(5);

			spin_lock(&data->txlock);
			अगर (is_valid_ether_addr(dev->dev_addr) && data->txमुक्त)
				netअगर_wake_queue(dev);

			data->link_up = 1;
			spin_unlock(&data->txlock);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (data->link_up == 1) अणु
			netअगर_stop_queue(dev);
			data->link_up = 0;
			prपूर्णांकk(KERN_NOTICE "%s : link is down\n", dev->name);
		पूर्ण

		जाओ out;
	पूर्ण


out:
	spin_unlock_irqrestore(&phy_lock, flags);
पूर्ण

अटल अंतरभूत व्योम
tsi108_stat_carry_one(पूर्णांक carry, पूर्णांक carry_bit, पूर्णांक carry_shअगरt,
		      अचिन्हित दीर्घ *upper)
अणु
	अगर (carry & carry_bit)
		*upper += carry_shअगरt;
पूर्ण

अटल व्योम tsi108_stat_carry(काष्ठा net_device *dev)
अणु
	काष्ठा tsi108_prv_data *data = netdev_priv(dev);
	अचिन्हित दीर्घ flags;
	u32 carry1, carry2;

	spin_lock_irqsave(&data->misघड़ी, flags);

	carry1 = TSI_READ(TSI108_STAT_CARRY1);
	carry2 = TSI_READ(TSI108_STAT_CARRY2);

	TSI_WRITE(TSI108_STAT_CARRY1, carry1);
	TSI_WRITE(TSI108_STAT_CARRY2, carry2);

	tsi108_stat_carry_one(carry1, TSI108_STAT_CARRY1_RXBYTES,
			      TSI108_STAT_RXBYTES_CARRY, &data->stats.rx_bytes);

	tsi108_stat_carry_one(carry1, TSI108_STAT_CARRY1_RXPKTS,
			      TSI108_STAT_RXPKTS_CARRY,
			      &data->stats.rx_packets);

	tsi108_stat_carry_one(carry1, TSI108_STAT_CARRY1_RXFCS,
			      TSI108_STAT_RXFCS_CARRY, &data->rx_fcs);

	tsi108_stat_carry_one(carry1, TSI108_STAT_CARRY1_RXMCAST,
			      TSI108_STAT_RXMCAST_CARRY,
			      &data->stats.multicast);

	tsi108_stat_carry_one(carry1, TSI108_STAT_CARRY1_RXALIGN,
			      TSI108_STAT_RXALIGN_CARRY,
			      &data->stats.rx_frame_errors);

	tsi108_stat_carry_one(carry1, TSI108_STAT_CARRY1_RXLENGTH,
			      TSI108_STAT_RXLENGTH_CARRY,
			      &data->stats.rx_length_errors);

	tsi108_stat_carry_one(carry1, TSI108_STAT_CARRY1_RXRUNT,
			      TSI108_STAT_RXRUNT_CARRY, &data->rx_underruns);

	tsi108_stat_carry_one(carry1, TSI108_STAT_CARRY1_RXJUMBO,
			      TSI108_STAT_RXJUMBO_CARRY, &data->rx_overruns);

	tsi108_stat_carry_one(carry1, TSI108_STAT_CARRY1_RXFRAG,
			      TSI108_STAT_RXFRAG_CARRY, &data->rx_लघु_fcs);

	tsi108_stat_carry_one(carry1, TSI108_STAT_CARRY1_RXJABBER,
			      TSI108_STAT_RXJABBER_CARRY, &data->rx_दीर्घ_fcs);

	tsi108_stat_carry_one(carry1, TSI108_STAT_CARRY1_RXDROP,
			      TSI108_STAT_RXDROP_CARRY,
			      &data->stats.rx_missed_errors);

	tsi108_stat_carry_one(carry2, TSI108_STAT_CARRY2_TXBYTES,
			      TSI108_STAT_TXBYTES_CARRY, &data->stats.tx_bytes);

	tsi108_stat_carry_one(carry2, TSI108_STAT_CARRY2_TXPKTS,
			      TSI108_STAT_TXPKTS_CARRY,
			      &data->stats.tx_packets);

	tsi108_stat_carry_one(carry2, TSI108_STAT_CARRY2_TXEXDEF,
			      TSI108_STAT_TXEXDEF_CARRY,
			      &data->stats.tx_पातed_errors);

	tsi108_stat_carry_one(carry2, TSI108_STAT_CARRY2_TXEXCOL,
			      TSI108_STAT_TXEXCOL_CARRY, &data->tx_coll_पात);

	tsi108_stat_carry_one(carry2, TSI108_STAT_CARRY2_TXTCOL,
			      TSI108_STAT_TXTCOL_CARRY,
			      &data->stats.collisions);

	tsi108_stat_carry_one(carry2, TSI108_STAT_CARRY2_TXPAUSE,
			      TSI108_STAT_TXPAUSEDROP_CARRY,
			      &data->tx_छोड़ो_drop);

	spin_unlock_irqrestore(&data->misघड़ी, flags);
पूर्ण

/* Read a stat counter atomically with respect to carries.
 * data->misघड़ी must be held.
 */
अटल अंतरभूत अचिन्हित दीर्घ
tsi108_पढ़ो_stat(काष्ठा tsi108_prv_data * data, पूर्णांक reg, पूर्णांक carry_bit,
		 पूर्णांक carry_shअगरt, अचिन्हित दीर्घ *upper)
अणु
	पूर्णांक carryreg;
	अचिन्हित दीर्घ val;

	अगर (reg < 0xb0)
		carryreg = TSI108_STAT_CARRY1;
	अन्यथा
		carryreg = TSI108_STAT_CARRY2;

      again:
	val = TSI_READ(reg) | *upper;

	/* Check to see अगर it overflowed, but the पूर्णांकerrupt hasn't
	 * been serviced yet.  If so, handle the carry here, and
	 * try again.
	 */

	अगर (unlikely(TSI_READ(carryreg) & carry_bit)) अणु
		*upper += carry_shअगरt;
		TSI_WRITE(carryreg, carry_bit);
		जाओ again;
	पूर्ण

	वापस val;
पूर्ण

अटल काष्ठा net_device_stats *tsi108_get_stats(काष्ठा net_device *dev)
अणु
	अचिन्हित दीर्घ excol;

	काष्ठा tsi108_prv_data *data = netdev_priv(dev);
	spin_lock_irq(&data->misघड़ी);

	data->पंचांगpstats.rx_packets =
	    tsi108_पढ़ो_stat(data, TSI108_STAT_RXPKTS,
			     TSI108_STAT_CARRY1_RXPKTS,
			     TSI108_STAT_RXPKTS_CARRY, &data->stats.rx_packets);

	data->पंचांगpstats.tx_packets =
	    tsi108_पढ़ो_stat(data, TSI108_STAT_TXPKTS,
			     TSI108_STAT_CARRY2_TXPKTS,
			     TSI108_STAT_TXPKTS_CARRY, &data->stats.tx_packets);

	data->पंचांगpstats.rx_bytes =
	    tsi108_पढ़ो_stat(data, TSI108_STAT_RXBYTES,
			     TSI108_STAT_CARRY1_RXBYTES,
			     TSI108_STAT_RXBYTES_CARRY, &data->stats.rx_bytes);

	data->पंचांगpstats.tx_bytes =
	    tsi108_पढ़ो_stat(data, TSI108_STAT_TXBYTES,
			     TSI108_STAT_CARRY2_TXBYTES,
			     TSI108_STAT_TXBYTES_CARRY, &data->stats.tx_bytes);

	data->पंचांगpstats.multicast =
	    tsi108_पढ़ो_stat(data, TSI108_STAT_RXMCAST,
			     TSI108_STAT_CARRY1_RXMCAST,
			     TSI108_STAT_RXMCAST_CARRY, &data->stats.multicast);

	excol = tsi108_पढ़ो_stat(data, TSI108_STAT_TXEXCOL,
				 TSI108_STAT_CARRY2_TXEXCOL,
				 TSI108_STAT_TXEXCOL_CARRY,
				 &data->tx_coll_पात);

	data->पंचांगpstats.collisions =
	    tsi108_पढ़ो_stat(data, TSI108_STAT_TXTCOL,
			     TSI108_STAT_CARRY2_TXTCOL,
			     TSI108_STAT_TXTCOL_CARRY, &data->stats.collisions);

	data->पंचांगpstats.collisions += excol;

	data->पंचांगpstats.rx_length_errors =
	    tsi108_पढ़ो_stat(data, TSI108_STAT_RXLENGTH,
			     TSI108_STAT_CARRY1_RXLENGTH,
			     TSI108_STAT_RXLENGTH_CARRY,
			     &data->stats.rx_length_errors);

	data->पंचांगpstats.rx_length_errors +=
	    tsi108_पढ़ो_stat(data, TSI108_STAT_RXRUNT,
			     TSI108_STAT_CARRY1_RXRUNT,
			     TSI108_STAT_RXRUNT_CARRY, &data->rx_underruns);

	data->पंचांगpstats.rx_length_errors +=
	    tsi108_पढ़ो_stat(data, TSI108_STAT_RXJUMBO,
			     TSI108_STAT_CARRY1_RXJUMBO,
			     TSI108_STAT_RXJUMBO_CARRY, &data->rx_overruns);

	data->पंचांगpstats.rx_frame_errors =
	    tsi108_पढ़ो_stat(data, TSI108_STAT_RXALIGN,
			     TSI108_STAT_CARRY1_RXALIGN,
			     TSI108_STAT_RXALIGN_CARRY,
			     &data->stats.rx_frame_errors);

	data->पंचांगpstats.rx_frame_errors +=
	    tsi108_पढ़ो_stat(data, TSI108_STAT_RXFCS,
			     TSI108_STAT_CARRY1_RXFCS, TSI108_STAT_RXFCS_CARRY,
			     &data->rx_fcs);

	data->पंचांगpstats.rx_frame_errors +=
	    tsi108_पढ़ो_stat(data, TSI108_STAT_RXFRAG,
			     TSI108_STAT_CARRY1_RXFRAG,
			     TSI108_STAT_RXFRAG_CARRY, &data->rx_लघु_fcs);

	data->पंचांगpstats.rx_missed_errors =
	    tsi108_पढ़ो_stat(data, TSI108_STAT_RXDROP,
			     TSI108_STAT_CARRY1_RXDROP,
			     TSI108_STAT_RXDROP_CARRY,
			     &data->stats.rx_missed_errors);

	/* These three are मुख्यtained by software. */
	data->पंचांगpstats.rx_fअगरo_errors = data->stats.rx_fअगरo_errors;
	data->पंचांगpstats.rx_crc_errors = data->stats.rx_crc_errors;

	data->पंचांगpstats.tx_पातed_errors =
	    tsi108_पढ़ो_stat(data, TSI108_STAT_TXEXDEF,
			     TSI108_STAT_CARRY2_TXEXDEF,
			     TSI108_STAT_TXEXDEF_CARRY,
			     &data->stats.tx_पातed_errors);

	data->पंचांगpstats.tx_पातed_errors +=
	    tsi108_पढ़ो_stat(data, TSI108_STAT_TXPAUSEDROP,
			     TSI108_STAT_CARRY2_TXPAUSE,
			     TSI108_STAT_TXPAUSEDROP_CARRY,
			     &data->tx_छोड़ो_drop);

	data->पंचांगpstats.tx_पातed_errors += excol;

	data->पंचांगpstats.tx_errors = data->पंचांगpstats.tx_पातed_errors;
	data->पंचांगpstats.rx_errors = data->पंचांगpstats.rx_length_errors +
	    data->पंचांगpstats.rx_crc_errors +
	    data->पंचांगpstats.rx_frame_errors +
	    data->पंचांगpstats.rx_fअगरo_errors + data->पंचांगpstats.rx_missed_errors;

	spin_unlock_irq(&data->misघड़ी);
	वापस &data->पंचांगpstats;
पूर्ण

अटल व्योम tsi108_restart_rx(काष्ठा tsi108_prv_data * data, काष्ठा net_device *dev)
अणु
	TSI_WRITE(TSI108_EC_RXQ_PTRHIGH,
			     TSI108_EC_RXQ_PTRHIGH_VALID);

	TSI_WRITE(TSI108_EC_RXCTRL, TSI108_EC_RXCTRL_GO
			     | TSI108_EC_RXCTRL_QUEUE0);
पूर्ण

अटल व्योम tsi108_restart_tx(काष्ठा tsi108_prv_data * data)
अणु
	TSI_WRITE(TSI108_EC_TXQ_PTRHIGH,
			     TSI108_EC_TXQ_PTRHIGH_VALID);

	TSI_WRITE(TSI108_EC_TXCTRL, TSI108_EC_TXCTRL_IDLEINT |
			     TSI108_EC_TXCTRL_GO | TSI108_EC_TXCTRL_QUEUE0);
पूर्ण

/* txlock must be held by caller, with IRQs disabled, and
 * with permission to re-enable them when the lock is dropped.
 */
अटल व्योम tsi108_complete_tx(काष्ठा net_device *dev)
अणु
	काष्ठा tsi108_prv_data *data = netdev_priv(dev);
	पूर्णांक tx;
	काष्ठा sk_buff *skb;
	पूर्णांक release = 0;

	जबतक (!data->txमुक्त || data->txhead != data->txtail) अणु
		tx = data->txtail;

		अगर (data->txring[tx].misc & TSI108_TX_OWN)
			अवरोध;

		skb = data->txskbs[tx];

		अगर (!(data->txring[tx].misc & TSI108_TX_OK))
			prपूर्णांकk("%s: bad tx packet, misc %x\n",
			       dev->name, data->txring[tx].misc);

		data->txtail = (data->txtail + 1) % TSI108_TXRING_LEN;
		data->txमुक्त++;

		अगर (data->txring[tx].misc & TSI108_TX_खातापूर्ण) अणु
			dev_kमुक्त_skb_any(skb);
			release++;
		पूर्ण
	पूर्ण

	अगर (release) अणु
		अगर (is_valid_ether_addr(dev->dev_addr) && data->link_up)
			netअगर_wake_queue(dev);
	पूर्ण
पूर्ण

अटल पूर्णांक tsi108_send_packet(काष्ठा sk_buff * skb, काष्ठा net_device *dev)
अणु
	काष्ठा tsi108_prv_data *data = netdev_priv(dev);
	पूर्णांक frags = skb_shinfo(skb)->nr_frags + 1;
	पूर्णांक i;

	अगर (!data->phy_ok && net_ratelimit())
		prपूर्णांकk(KERN_ERR "%s: Transmit while PHY is down!\n", dev->name);

	अगर (!data->link_up) अणु
		prपूर्णांकk(KERN_ERR "%s: Transmit while link is down!\n",
		       dev->name);
		netअगर_stop_queue(dev);
		वापस NETDEV_TX_BUSY;
	पूर्ण

	अगर (data->txमुक्त < MAX_SKB_FRAGS + 1) अणु
		netअगर_stop_queue(dev);

		अगर (net_ratelimit())
			prपूर्णांकk(KERN_ERR "%s: Transmit with full tx ring!\n",
			       dev->name);
		वापस NETDEV_TX_BUSY;
	पूर्ण

	अगर (data->txमुक्त - frags < MAX_SKB_FRAGS + 1) अणु
		netअगर_stop_queue(dev);
	पूर्ण

	spin_lock_irq(&data->txlock);

	क्रम (i = 0; i < frags; i++) अणु
		पूर्णांक misc = 0;
		पूर्णांक tx = data->txhead;

		/* This is करोne to mark every TSI108_TX_INT_FREQ tx buffers with
		 * the पूर्णांकerrupt bit.  TX descriptor-complete पूर्णांकerrupts are
		 * enabled when the queue fills up, and masked when there is
		 * still मुक्त space.  This way, when saturating the outbound
		 * link, the tx पूर्णांकerrupts are kept to a reasonable level.
		 * When the queue is not full, reclamation of skbs still occurs
		 * as new packets are transmitted, or on a queue-empty
		 * पूर्णांकerrupt.
		 */

		अगर ((tx % TSI108_TX_INT_FREQ == 0) &&
		    ((TSI108_TXRING_LEN - data->txमुक्त) >= TSI108_TX_INT_FREQ))
			misc = TSI108_TX_INT;

		data->txskbs[tx] = skb;

		अगर (i == 0) अणु
			data->txring[tx].buf0 = dma_map_single(&data->pdev->dev,
					skb->data, skb_headlen(skb),
					DMA_TO_DEVICE);
			data->txring[tx].len = skb_headlen(skb);
			misc |= TSI108_TX_SOF;
		पूर्ण अन्यथा अणु
			स्थिर skb_frag_t *frag = &skb_shinfo(skb)->frags[i - 1];

			data->txring[tx].buf0 =
				skb_frag_dma_map(&data->pdev->dev, frag,
						0, skb_frag_size(frag),
						DMA_TO_DEVICE);
			data->txring[tx].len = skb_frag_size(frag);
		पूर्ण

		अगर (i == frags - 1)
			misc |= TSI108_TX_खातापूर्ण;

		अगर (netअगर_msg_pktdata(data)) अणु
			पूर्णांक i;
			prपूर्णांकk("%s: Tx Frame contents (%d)\n", dev->name,
			       skb->len);
			क्रम (i = 0; i < skb->len; i++)
				prपूर्णांकk(" %2.2x", skb->data[i]);
			prपूर्णांकk(".\n");
		पूर्ण
		data->txring[tx].misc = misc | TSI108_TX_OWN;

		data->txhead = (data->txhead + 1) % TSI108_TXRING_LEN;
		data->txमुक्त--;
	पूर्ण

	tsi108_complete_tx(dev);

	/* This must be करोne after the check क्रम completed tx descriptors,
	 * so that the tail poपूर्णांकer is correct.
	 */

	अगर (!(TSI_READ(TSI108_EC_TXSTAT) & TSI108_EC_TXSTAT_QUEUE0))
		tsi108_restart_tx(data);

	spin_unlock_irq(&data->txlock);
	वापस NETDEV_TX_OK;
पूर्ण

अटल पूर्णांक tsi108_complete_rx(काष्ठा net_device *dev, पूर्णांक budget)
अणु
	काष्ठा tsi108_prv_data *data = netdev_priv(dev);
	पूर्णांक करोne = 0;

	जबतक (data->rxमुक्त && करोne != budget) अणु
		पूर्णांक rx = data->rxtail;
		काष्ठा sk_buff *skb;

		अगर (data->rxring[rx].misc & TSI108_RX_OWN)
			अवरोध;

		skb = data->rxskbs[rx];
		data->rxtail = (data->rxtail + 1) % TSI108_RXRING_LEN;
		data->rxमुक्त--;
		करोne++;

		अगर (data->rxring[rx].misc & TSI108_RX_BAD) अणु
			spin_lock_irq(&data->misघड़ी);

			अगर (data->rxring[rx].misc & TSI108_RX_CRC)
				data->stats.rx_crc_errors++;
			अगर (data->rxring[rx].misc & TSI108_RX_OVER)
				data->stats.rx_fअगरo_errors++;

			spin_unlock_irq(&data->misघड़ी);

			dev_kमुक्त_skb_any(skb);
			जारी;
		पूर्ण
		अगर (netअगर_msg_pktdata(data)) अणु
			पूर्णांक i;
			prपूर्णांकk("%s: Rx Frame contents (%d)\n",
			       dev->name, data->rxring[rx].len);
			क्रम (i = 0; i < data->rxring[rx].len; i++)
				prपूर्णांकk(" %2.2x", skb->data[i]);
			prपूर्णांकk(".\n");
		पूर्ण

		skb_put(skb, data->rxring[rx].len);
		skb->protocol = eth_type_trans(skb, dev);
		netअगर_receive_skb(skb);
	पूर्ण

	वापस करोne;
पूर्ण

अटल पूर्णांक tsi108_refill_rx(काष्ठा net_device *dev, पूर्णांक budget)
अणु
	काष्ठा tsi108_prv_data *data = netdev_priv(dev);
	पूर्णांक करोne = 0;

	जबतक (data->rxमुक्त != TSI108_RXRING_LEN && करोne != budget) अणु
		पूर्णांक rx = data->rxhead;
		काष्ठा sk_buff *skb;

		skb = netdev_alloc_skb_ip_align(dev, TSI108_RXBUF_SIZE);
		data->rxskbs[rx] = skb;
		अगर (!skb)
			अवरोध;

		data->rxring[rx].buf0 = dma_map_single(&data->pdev->dev,
				skb->data, TSI108_RX_SKB_SIZE,
				DMA_FROM_DEVICE);

		/* Someबार the hardware sets blen to zero after packet
		 * reception, even though the manual says that it's only ever
		 * modअगरied by the driver.
		 */

		data->rxring[rx].blen = TSI108_RX_SKB_SIZE;
		data->rxring[rx].misc = TSI108_RX_OWN | TSI108_RX_INT;

		data->rxhead = (data->rxhead + 1) % TSI108_RXRING_LEN;
		data->rxमुक्त++;
		करोne++;
	पूर्ण

	अगर (करोne != 0 && !(TSI_READ(TSI108_EC_RXSTAT) &
			   TSI108_EC_RXSTAT_QUEUE0))
		tsi108_restart_rx(data, dev);

	वापस करोne;
पूर्ण

अटल पूर्णांक tsi108_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा tsi108_prv_data *data = container_of(napi, काष्ठा tsi108_prv_data, napi);
	काष्ठा net_device *dev = data->dev;
	u32 estat = TSI_READ(TSI108_EC_RXESTAT);
	u32 पूर्णांकstat = TSI_READ(TSI108_EC_INTSTAT);
	पूर्णांक num_received = 0, num_filled = 0;

	पूर्णांकstat &= TSI108_INT_RXQUEUE0 | TSI108_INT_RXTHRESH |
	    TSI108_INT_RXOVERRUN | TSI108_INT_RXERROR | TSI108_INT_RXWAIT;

	TSI_WRITE(TSI108_EC_RXESTAT, estat);
	TSI_WRITE(TSI108_EC_INTSTAT, पूर्णांकstat);

	अगर (data->rxpending || (estat & TSI108_EC_RXESTAT_Q0_DESCINT))
		num_received = tsi108_complete_rx(dev, budget);

	/* This should normally fill no more slots than the number of
	 * packets received in tsi108_complete_rx().  The exception
	 * is when we previously ran out of memory क्रम RX SKBs.  In that
	 * हाल, it's helpful to obey the budget, not only so that the
	 * CPU isn't hogged, but so that memory (which may still be low)
	 * is not hogged by one device.
	 *
	 * A work unit is considered to be two SKBs to allow us to catch
	 * up when the ring has shrunk due to out-of-memory but we're
	 * still removing the full budget's worth of packets each समय.
	 */

	अगर (data->rxमुक्त < TSI108_RXRING_LEN)
		num_filled = tsi108_refill_rx(dev, budget * 2);

	अगर (पूर्णांकstat & TSI108_INT_RXERROR) अणु
		u32 err = TSI_READ(TSI108_EC_RXERR);
		TSI_WRITE(TSI108_EC_RXERR, err);

		अगर (err) अणु
			अगर (net_ratelimit())
				prपूर्णांकk(KERN_DEBUG "%s: RX error %x\n",
				       dev->name, err);

			अगर (!(TSI_READ(TSI108_EC_RXSTAT) &
			      TSI108_EC_RXSTAT_QUEUE0))
				tsi108_restart_rx(data, dev);
		पूर्ण
	पूर्ण

	अगर (पूर्णांकstat & TSI108_INT_RXOVERRUN) अणु
		spin_lock_irq(&data->misघड़ी);
		data->stats.rx_fअगरo_errors++;
		spin_unlock_irq(&data->misघड़ी);
	पूर्ण

	अगर (num_received < budget) अणु
		data->rxpending = 0;
		napi_complete_करोne(napi, num_received);

		TSI_WRITE(TSI108_EC_INTMASK,
				     TSI_READ(TSI108_EC_INTMASK)
				     & ~(TSI108_INT_RXQUEUE0
					 | TSI108_INT_RXTHRESH |
					 TSI108_INT_RXOVERRUN |
					 TSI108_INT_RXERROR |
					 TSI108_INT_RXWAIT));
	पूर्ण अन्यथा अणु
		data->rxpending = 1;
	पूर्ण

	वापस num_received;
पूर्ण

अटल व्योम tsi108_rx_पूर्णांक(काष्ठा net_device *dev)
अणु
	काष्ठा tsi108_prv_data *data = netdev_priv(dev);

	/* A race could cause dev to alपढ़ोy be scheduled, so it's not an
	 * error अगर that happens (and पूर्णांकerrupts shouldn't be re-masked,
	 * because that can cause harmful races, अगर poll has alपढ़ोy
	 * unmasked them but not cleared LINK_STATE_SCHED).
	 *
	 * This can happen अगर this code races with tsi108_poll(), which masks
	 * the पूर्णांकerrupts after tsi108_irq_one() पढ़ो the mask, but beक्रमe
	 * napi_schedule is called.  It could also happen due to calls
	 * from tsi108_check_rxring().
	 */

	अगर (napi_schedule_prep(&data->napi)) अणु
		/* Mask, rather than ack, the receive पूर्णांकerrupts.  The ack
		 * will happen in tsi108_poll().
		 */

		TSI_WRITE(TSI108_EC_INTMASK,
				     TSI_READ(TSI108_EC_INTMASK) |
				     TSI108_INT_RXQUEUE0
				     | TSI108_INT_RXTHRESH |
				     TSI108_INT_RXOVERRUN | TSI108_INT_RXERROR |
				     TSI108_INT_RXWAIT);
		__napi_schedule(&data->napi);
	पूर्ण अन्यथा अणु
		अगर (!netअगर_running(dev)) अणु
			/* This can happen अगर an पूर्णांकerrupt occurs जबतक the
			 * पूर्णांकerface is being brought करोwn, as the START
			 * bit is cleared beक्रमe the stop function is called.
			 *
			 * In this हाल, the पूर्णांकerrupts must be masked, or
			 * they will जारी indefinitely.
			 *
			 * There's a race here अगर the पूर्णांकerface is brought करोwn
			 * and then up in rapid succession, as the device could
			 * be made running after the above check and beक्रमe
			 * the masking below.  This will only happen अगर the IRQ
			 * thपढ़ो has a lower priority than the task brining
			 * up the पूर्णांकerface.  Fixing this race would likely
			 * require changes in generic code.
			 */

			TSI_WRITE(TSI108_EC_INTMASK,
					     TSI_READ
					     (TSI108_EC_INTMASK) |
					     TSI108_INT_RXQUEUE0 |
					     TSI108_INT_RXTHRESH |
					     TSI108_INT_RXOVERRUN |
					     TSI108_INT_RXERROR |
					     TSI108_INT_RXWAIT);
		पूर्ण
	पूर्ण
पूर्ण

/* If the RX ring has run out of memory, try periodically
 * to allocate some more, as otherwise poll would never
 * get called (apart from the initial end-of-queue condition).
 *
 * This is called once per second (by शेष) from the thपढ़ो.
 */

अटल व्योम tsi108_check_rxring(काष्ठा net_device *dev)
अणु
	काष्ठा tsi108_prv_data *data = netdev_priv(dev);

	/* A poll is scheduled, as opposed to caling tsi108_refill_rx
	 * directly, so as to keep the receive path single-thपढ़ोed
	 * (and thus not needing a lock).
	 */

	अगर (netअगर_running(dev) && data->rxमुक्त < TSI108_RXRING_LEN / 4)
		tsi108_rx_पूर्णांक(dev);
पूर्ण

अटल व्योम tsi108_tx_पूर्णांक(काष्ठा net_device *dev)
अणु
	काष्ठा tsi108_prv_data *data = netdev_priv(dev);
	u32 estat = TSI_READ(TSI108_EC_TXESTAT);

	TSI_WRITE(TSI108_EC_TXESTAT, estat);
	TSI_WRITE(TSI108_EC_INTSTAT, TSI108_INT_TXQUEUE0 |
			     TSI108_INT_TXIDLE | TSI108_INT_TXERROR);
	अगर (estat & TSI108_EC_TXESTAT_Q0_ERR) अणु
		u32 err = TSI_READ(TSI108_EC_TXERR);
		TSI_WRITE(TSI108_EC_TXERR, err);

		अगर (err && net_ratelimit())
			prपूर्णांकk(KERN_ERR "%s: TX error %x\n", dev->name, err);
	पूर्ण

	अगर (estat & (TSI108_EC_TXESTAT_Q0_DESCINT | TSI108_EC_TXESTAT_Q0_EOQ)) अणु
		spin_lock(&data->txlock);
		tsi108_complete_tx(dev);
		spin_unlock(&data->txlock);
	पूर्ण
पूर्ण


अटल irqवापस_t tsi108_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = dev_id;
	काष्ठा tsi108_prv_data *data = netdev_priv(dev);
	u32 stat = TSI_READ(TSI108_EC_INTSTAT);

	अगर (!(stat & TSI108_INT_ANY))
		वापस IRQ_NONE;	/* Not our पूर्णांकerrupt */

	stat &= ~TSI_READ(TSI108_EC_INTMASK);

	अगर (stat & (TSI108_INT_TXQUEUE0 | TSI108_INT_TXIDLE |
		    TSI108_INT_TXERROR))
		tsi108_tx_पूर्णांक(dev);
	अगर (stat & (TSI108_INT_RXQUEUE0 | TSI108_INT_RXTHRESH |
		    TSI108_INT_RXWAIT | TSI108_INT_RXOVERRUN |
		    TSI108_INT_RXERROR))
		tsi108_rx_पूर्णांक(dev);

	अगर (stat & TSI108_INT_SFN) अणु
		अगर (net_ratelimit())
			prपूर्णांकk(KERN_DEBUG "%s: SFN error\n", dev->name);
		TSI_WRITE(TSI108_EC_INTSTAT, TSI108_INT_SFN);
	पूर्ण

	अगर (stat & TSI108_INT_STATCARRY) अणु
		tsi108_stat_carry(dev);
		TSI_WRITE(TSI108_EC_INTSTAT, TSI108_INT_STATCARRY);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम tsi108_stop_ethernet(काष्ठा net_device *dev)
अणु
	काष्ठा tsi108_prv_data *data = netdev_priv(dev);
	पूर्णांक i = 1000;
	/* Disable all TX and RX queues ... */
	TSI_WRITE(TSI108_EC_TXCTRL, 0);
	TSI_WRITE(TSI108_EC_RXCTRL, 0);

	/* ...and रुको क्रम them to become idle */
	जबतक(i--) अणु
		अगर(!(TSI_READ(TSI108_EC_TXSTAT) & TSI108_EC_TXSTAT_ACTIVE))
			अवरोध;
		udelay(10);
	पूर्ण
	i = 1000;
	जबतक(i--)अणु
		अगर(!(TSI_READ(TSI108_EC_RXSTAT) & TSI108_EC_RXSTAT_ACTIVE))
			वापस;
		udelay(10);
	पूर्ण
	prपूर्णांकk(KERN_ERR "%s function time out\n", __func__);
पूर्ण

अटल व्योम tsi108_reset_ether(काष्ठा tsi108_prv_data * data)
अणु
	TSI_WRITE(TSI108_MAC_CFG1, TSI108_MAC_CFG1_SOFTRST);
	udelay(100);
	TSI_WRITE(TSI108_MAC_CFG1, 0);

	TSI_WRITE(TSI108_EC_PORTCTRL, TSI108_EC_PORTCTRL_STATRST);
	udelay(100);
	TSI_WRITE(TSI108_EC_PORTCTRL,
			     TSI_READ(TSI108_EC_PORTCTRL) &
			     ~TSI108_EC_PORTCTRL_STATRST);

	TSI_WRITE(TSI108_EC_TXCFG, TSI108_EC_TXCFG_RST);
	udelay(100);
	TSI_WRITE(TSI108_EC_TXCFG,
			     TSI_READ(TSI108_EC_TXCFG) &
			     ~TSI108_EC_TXCFG_RST);

	TSI_WRITE(TSI108_EC_RXCFG, TSI108_EC_RXCFG_RST);
	udelay(100);
	TSI_WRITE(TSI108_EC_RXCFG,
			     TSI_READ(TSI108_EC_RXCFG) &
			     ~TSI108_EC_RXCFG_RST);

	TSI_WRITE(TSI108_MAC_MII_MGMT_CFG,
			     TSI_READ(TSI108_MAC_MII_MGMT_CFG) |
			     TSI108_MAC_MII_MGMT_RST);
	udelay(100);
	TSI_WRITE(TSI108_MAC_MII_MGMT_CFG,
			     (TSI_READ(TSI108_MAC_MII_MGMT_CFG) &
			     ~(TSI108_MAC_MII_MGMT_RST |
			       TSI108_MAC_MII_MGMT_CLK)) | 0x07);
पूर्ण

अटल पूर्णांक tsi108_get_mac(काष्ठा net_device *dev)
अणु
	काष्ठा tsi108_prv_data *data = netdev_priv(dev);
	u32 word1 = TSI_READ(TSI108_MAC_ADDR1);
	u32 word2 = TSI_READ(TSI108_MAC_ADDR2);

	/* Note that the octets are reversed from what the manual says,
	 * producing an even weirder ordering...
	 */
	अगर (word2 == 0 && word1 == 0) अणु
		dev->dev_addr[0] = 0x00;
		dev->dev_addr[1] = 0x06;
		dev->dev_addr[2] = 0xd2;
		dev->dev_addr[3] = 0x00;
		dev->dev_addr[4] = 0x00;
		अगर (0x8 == data->phy)
			dev->dev_addr[5] = 0x01;
		अन्यथा
			dev->dev_addr[5] = 0x02;

		word2 = (dev->dev_addr[0] << 16) | (dev->dev_addr[1] << 24);

		word1 = (dev->dev_addr[2] << 0) | (dev->dev_addr[3] << 8) |
		    (dev->dev_addr[4] << 16) | (dev->dev_addr[5] << 24);

		TSI_WRITE(TSI108_MAC_ADDR1, word1);
		TSI_WRITE(TSI108_MAC_ADDR2, word2);
	पूर्ण अन्यथा अणु
		dev->dev_addr[0] = (word2 >> 16) & 0xff;
		dev->dev_addr[1] = (word2 >> 24) & 0xff;
		dev->dev_addr[2] = (word1 >> 0) & 0xff;
		dev->dev_addr[3] = (word1 >> 8) & 0xff;
		dev->dev_addr[4] = (word1 >> 16) & 0xff;
		dev->dev_addr[5] = (word1 >> 24) & 0xff;
	पूर्ण

	अगर (!is_valid_ether_addr(dev->dev_addr)) अणु
		prपूर्णांकk(KERN_ERR
		       "%s: Invalid MAC address. word1: %08x, word2: %08x\n",
		       dev->name, word1, word2);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tsi108_set_mac(काष्ठा net_device *dev, व्योम *addr)
अणु
	काष्ठा tsi108_prv_data *data = netdev_priv(dev);
	u32 word1, word2;
	पूर्णांक i;

	अगर (!is_valid_ether_addr(addr))
		वापस -EADDRNOTAVAIL;

	क्रम (i = 0; i < 6; i++)
		/* +2 is क्रम the offset of the HW addr type */
		dev->dev_addr[i] = ((अचिन्हित अक्षर *)addr)[i + 2];

	word2 = (dev->dev_addr[0] << 16) | (dev->dev_addr[1] << 24);

	word1 = (dev->dev_addr[2] << 0) | (dev->dev_addr[3] << 8) |
	    (dev->dev_addr[4] << 16) | (dev->dev_addr[5] << 24);

	spin_lock_irq(&data->misघड़ी);
	TSI_WRITE(TSI108_MAC_ADDR1, word1);
	TSI_WRITE(TSI108_MAC_ADDR2, word2);
	spin_lock(&data->txlock);

	अगर (data->txमुक्त && data->link_up)
		netअगर_wake_queue(dev);

	spin_unlock(&data->txlock);
	spin_unlock_irq(&data->misघड़ी);
	वापस 0;
पूर्ण

/* Protected by dev->xmit_lock. */
अटल व्योम tsi108_set_rx_mode(काष्ठा net_device *dev)
अणु
	काष्ठा tsi108_prv_data *data = netdev_priv(dev);
	u32 rxcfg = TSI_READ(TSI108_EC_RXCFG);

	अगर (dev->flags & IFF_PROMISC) अणु
		rxcfg &= ~(TSI108_EC_RXCFG_UC_HASH | TSI108_EC_RXCFG_MC_HASH);
		rxcfg |= TSI108_EC_RXCFG_UFE | TSI108_EC_RXCFG_MFE;
		जाओ out;
	पूर्ण

	rxcfg &= ~(TSI108_EC_RXCFG_UFE | TSI108_EC_RXCFG_MFE);

	अगर (dev->flags & IFF_ALLMULTI || !netdev_mc_empty(dev)) अणु
		पूर्णांक i;
		काष्ठा netdev_hw_addr *ha;
		rxcfg |= TSI108_EC_RXCFG_MFE | TSI108_EC_RXCFG_MC_HASH;

		स_रखो(data->mc_hash, 0, माप(data->mc_hash));

		netdev_क्रम_each_mc_addr(ha, dev) अणु
			u32 hash, crc;

			crc = ether_crc(6, ha->addr);
			hash = crc >> 23;
			__set_bit(hash, &data->mc_hash[0]);
		पूर्ण

		TSI_WRITE(TSI108_EC_HASHADDR,
				     TSI108_EC_HASHADDR_AUTOINC |
				     TSI108_EC_HASHADDR_MCAST);

		क्रम (i = 0; i < 16; i++) अणु
			/* The manual says that the hardware may drop
			 * back-to-back ग_लिखोs to the data रेजिस्टर.
			 */
			udelay(1);
			TSI_WRITE(TSI108_EC_HASHDATA,
					     data->mc_hash[i]);
		पूर्ण
	पूर्ण

      out:
	TSI_WRITE(TSI108_EC_RXCFG, rxcfg);
पूर्ण

अटल व्योम tsi108_init_phy(काष्ठा net_device *dev)
अणु
	काष्ठा tsi108_prv_data *data = netdev_priv(dev);
	u32 i = 0;
	u16 phyval = 0;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&phy_lock, flags);

	tsi108_ग_लिखो_mii(data, MII_BMCR, BMCR_RESET);
	जबतक (--i) अणु
		अगर(!(tsi108_पढ़ो_mii(data, MII_BMCR) & BMCR_RESET))
			अवरोध;
		udelay(10);
	पूर्ण
	अगर (i == 0)
		prपूर्णांकk(KERN_ERR "%s function time out\n", __func__);

	अगर (data->phy_type == TSI108_PHY_BCM54XX) अणु
		tsi108_ग_लिखो_mii(data, 0x09, 0x0300);
		tsi108_ग_लिखो_mii(data, 0x10, 0x1020);
		tsi108_ग_लिखो_mii(data, 0x1c, 0x8c00);
	पूर्ण

	tsi108_ग_लिखो_mii(data,
			 MII_BMCR,
			 BMCR_ANENABLE | BMCR_ANRESTART);
	जबतक (tsi108_पढ़ो_mii(data, MII_BMCR) & BMCR_ANRESTART)
		cpu_relax();

	/* Set G/MII mode and receive घड़ी select in TBI control #2.  The
	 * second port won't work if this isn't done, even though we don't
	 * use TBI mode.
	 */

	tsi108_ग_लिखो_tbi(data, 0x11, 0x30);

	/* FIXME: It seems to take more than 2 back-to-back पढ़ोs to the
	 * PHY_STAT रेजिस्टर beक्रमe the link up status bit is set.
	 */

	data->link_up = 0;

	जबतक (!((phyval = tsi108_पढ़ो_mii(data, MII_BMSR)) &
		 BMSR_LSTATUS)) अणु
		अगर (i++ > (MII_READ_DELAY / 10)) अणु
			अवरोध;
		पूर्ण
		spin_unlock_irqrestore(&phy_lock, flags);
		msleep(10);
		spin_lock_irqsave(&phy_lock, flags);
	पूर्ण

	data->mii_अगर.supports_gmii = mii_check_gmii_support(&data->mii_अगर);
	prपूर्णांकk(KERN_DEBUG "PHY_STAT reg contains %08x\n", phyval);
	data->phy_ok = 1;
	data->init_media = 1;
	spin_unlock_irqrestore(&phy_lock, flags);
पूर्ण

अटल व्योम tsi108_समाप्त_phy(काष्ठा net_device *dev)
अणु
	काष्ठा tsi108_prv_data *data = netdev_priv(dev);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&phy_lock, flags);
	tsi108_ग_लिखो_mii(data, MII_BMCR, BMCR_PDOWN);
	data->phy_ok = 0;
	spin_unlock_irqrestore(&phy_lock, flags);
पूर्ण

अटल पूर्णांक tsi108_खोलो(काष्ठा net_device *dev)
अणु
	पूर्णांक i;
	काष्ठा tsi108_prv_data *data = netdev_priv(dev);
	अचिन्हित पूर्णांक rxring_size = TSI108_RXRING_LEN * माप(rx_desc);
	अचिन्हित पूर्णांक txring_size = TSI108_TXRING_LEN * माप(tx_desc);

	i = request_irq(data->irq_num, tsi108_irq, 0, dev->name, dev);
	अगर (i != 0) अणु
		prपूर्णांकk(KERN_ERR "tsi108_eth%d: Could not allocate IRQ%d.\n",
		       data->id, data->irq_num);
		वापस i;
	पूर्ण अन्यथा अणु
		dev->irq = data->irq_num;
		prपूर्णांकk(KERN_NOTICE
		       "tsi108_open : Port %d Assigned IRQ %d to %s\n",
		       data->id, dev->irq, dev->name);
	पूर्ण

	data->rxring = dma_alloc_coherent(&data->pdev->dev, rxring_size,
					  &data->rxdma, GFP_KERNEL);
	अगर (!data->rxring)
		वापस -ENOMEM;

	data->txring = dma_alloc_coherent(&data->pdev->dev, txring_size,
					  &data->txdma, GFP_KERNEL);
	अगर (!data->txring) अणु
		dma_मुक्त_coherent(&data->pdev->dev, rxring_size, data->rxring,
				    data->rxdma);
		वापस -ENOMEM;
	पूर्ण

	क्रम (i = 0; i < TSI108_RXRING_LEN; i++) अणु
		data->rxring[i].next0 = data->rxdma + (i + 1) * माप(rx_desc);
		data->rxring[i].blen = TSI108_RXBUF_SIZE;
		data->rxring[i].vlan = 0;
	पूर्ण

	data->rxring[TSI108_RXRING_LEN - 1].next0 = data->rxdma;

	data->rxtail = 0;
	data->rxhead = 0;

	क्रम (i = 0; i < TSI108_RXRING_LEN; i++) अणु
		काष्ठा sk_buff *skb;

		skb = netdev_alloc_skb_ip_align(dev, TSI108_RXBUF_SIZE);
		अगर (!skb) अणु
			/* Bah.  No memory क्रम now, but maybe we'll get
			 * some more later.
			 * For now, we'll live with the smaller ring.
			 */
			prपूर्णांकk(KERN_WARNING
			       "%s: Could only allocate %d receive skb(s).\n",
			       dev->name, i);
			data->rxhead = i;
			अवरोध;
		पूर्ण

		data->rxskbs[i] = skb;
		data->rxring[i].buf0 = virt_to_phys(data->rxskbs[i]->data);
		data->rxring[i].misc = TSI108_RX_OWN | TSI108_RX_INT;
	पूर्ण

	data->rxमुक्त = i;
	TSI_WRITE(TSI108_EC_RXQ_PTRLOW, data->rxdma);

	क्रम (i = 0; i < TSI108_TXRING_LEN; i++) अणु
		data->txring[i].next0 = data->txdma + (i + 1) * माप(tx_desc);
		data->txring[i].misc = 0;
	पूर्ण

	data->txring[TSI108_TXRING_LEN - 1].next0 = data->txdma;
	data->txtail = 0;
	data->txhead = 0;
	data->txमुक्त = TSI108_TXRING_LEN;
	TSI_WRITE(TSI108_EC_TXQ_PTRLOW, data->txdma);
	tsi108_init_phy(dev);

	napi_enable(&data->napi);

	समयr_setup(&data->समयr, tsi108_समयd_checker, 0);
	mod_समयr(&data->समयr, jअगरfies + 1);

	tsi108_restart_rx(data, dev);

	TSI_WRITE(TSI108_EC_INTSTAT, ~0);

	TSI_WRITE(TSI108_EC_INTMASK,
			     ~(TSI108_INT_TXQUEUE0 | TSI108_INT_RXERROR |
			       TSI108_INT_RXTHRESH | TSI108_INT_RXQUEUE0 |
			       TSI108_INT_RXOVERRUN | TSI108_INT_RXWAIT |
			       TSI108_INT_SFN | TSI108_INT_STATCARRY));

	TSI_WRITE(TSI108_MAC_CFG1,
			     TSI108_MAC_CFG1_RXEN | TSI108_MAC_CFG1_TXEN);
	netअगर_start_queue(dev);
	वापस 0;
पूर्ण

अटल पूर्णांक tsi108_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा tsi108_prv_data *data = netdev_priv(dev);

	netअगर_stop_queue(dev);
	napi_disable(&data->napi);

	del_समयr_sync(&data->समयr);

	tsi108_stop_ethernet(dev);
	tsi108_समाप्त_phy(dev);
	TSI_WRITE(TSI108_EC_INTMASK, ~0);
	TSI_WRITE(TSI108_MAC_CFG1, 0);

	/* Check क्रम any pending TX packets, and drop them. */

	जबतक (!data->txमुक्त || data->txhead != data->txtail) अणु
		पूर्णांक tx = data->txtail;
		काष्ठा sk_buff *skb;
		skb = data->txskbs[tx];
		data->txtail = (data->txtail + 1) % TSI108_TXRING_LEN;
		data->txमुक्त++;
		dev_kमुक्त_skb(skb);
	पूर्ण

	मुक्त_irq(data->irq_num, dev);

	/* Discard the RX ring. */

	जबतक (data->rxमुक्त) अणु
		पूर्णांक rx = data->rxtail;
		काष्ठा sk_buff *skb;

		skb = data->rxskbs[rx];
		data->rxtail = (data->rxtail + 1) % TSI108_RXRING_LEN;
		data->rxमुक्त--;
		dev_kमुक्त_skb(skb);
	पूर्ण

	dma_मुक्त_coherent(&data->pdev->dev,
			    TSI108_RXRING_LEN * माप(rx_desc),
			    data->rxring, data->rxdma);
	dma_मुक्त_coherent(&data->pdev->dev,
			    TSI108_TXRING_LEN * माप(tx_desc),
			    data->txring, data->txdma);

	वापस 0;
पूर्ण

अटल व्योम tsi108_init_mac(काष्ठा net_device *dev)
अणु
	काष्ठा tsi108_prv_data *data = netdev_priv(dev);

	TSI_WRITE(TSI108_MAC_CFG2, TSI108_MAC_CFG2_DFLT_PREAMBLE |
			     TSI108_MAC_CFG2_PADCRC);

	TSI_WRITE(TSI108_EC_TXTHRESH,
			     (192 << TSI108_EC_TXTHRESH_STARTFILL) |
			     (192 << TSI108_EC_TXTHRESH_STOPFILL));

	TSI_WRITE(TSI108_STAT_CARRYMASK1,
			     ~(TSI108_STAT_CARRY1_RXBYTES |
			       TSI108_STAT_CARRY1_RXPKTS |
			       TSI108_STAT_CARRY1_RXFCS |
			       TSI108_STAT_CARRY1_RXMCAST |
			       TSI108_STAT_CARRY1_RXALIGN |
			       TSI108_STAT_CARRY1_RXLENGTH |
			       TSI108_STAT_CARRY1_RXRUNT |
			       TSI108_STAT_CARRY1_RXJUMBO |
			       TSI108_STAT_CARRY1_RXFRAG |
			       TSI108_STAT_CARRY1_RXJABBER |
			       TSI108_STAT_CARRY1_RXDROP));

	TSI_WRITE(TSI108_STAT_CARRYMASK2,
			     ~(TSI108_STAT_CARRY2_TXBYTES |
			       TSI108_STAT_CARRY2_TXPKTS |
			       TSI108_STAT_CARRY2_TXEXDEF |
			       TSI108_STAT_CARRY2_TXEXCOL |
			       TSI108_STAT_CARRY2_TXTCOL |
			       TSI108_STAT_CARRY2_TXPAUSE));

	TSI_WRITE(TSI108_EC_PORTCTRL, TSI108_EC_PORTCTRL_STATEN);
	TSI_WRITE(TSI108_MAC_CFG1, 0);

	TSI_WRITE(TSI108_EC_RXCFG,
			     TSI108_EC_RXCFG_SE | TSI108_EC_RXCFG_BFE);

	TSI_WRITE(TSI108_EC_TXQ_CFG, TSI108_EC_TXQ_CFG_DESC_INT |
			     TSI108_EC_TXQ_CFG_EOQ_OWN_INT |
			     TSI108_EC_TXQ_CFG_WSWP | (TSI108_PBM_PORT <<
						TSI108_EC_TXQ_CFG_SFNPORT));

	TSI_WRITE(TSI108_EC_RXQ_CFG, TSI108_EC_RXQ_CFG_DESC_INT |
			     TSI108_EC_RXQ_CFG_EOQ_OWN_INT |
			     TSI108_EC_RXQ_CFG_WSWP | (TSI108_PBM_PORT <<
						TSI108_EC_RXQ_CFG_SFNPORT));

	TSI_WRITE(TSI108_EC_TXQ_BUFCFG,
			     TSI108_EC_TXQ_BUFCFG_BURST256 |
			     TSI108_EC_TXQ_BUFCFG_BSWP | (TSI108_PBM_PORT <<
						TSI108_EC_TXQ_BUFCFG_SFNPORT));

	TSI_WRITE(TSI108_EC_RXQ_BUFCFG,
			     TSI108_EC_RXQ_BUFCFG_BURST256 |
			     TSI108_EC_RXQ_BUFCFG_BSWP | (TSI108_PBM_PORT <<
						TSI108_EC_RXQ_BUFCFG_SFNPORT));

	TSI_WRITE(TSI108_EC_INTMASK, ~0);
पूर्ण

अटल पूर्णांक tsi108_get_link_ksettings(काष्ठा net_device *dev,
				     काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा tsi108_prv_data *data = netdev_priv(dev);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&data->txlock, flags);
	mii_ethtool_get_link_ksettings(&data->mii_अगर, cmd);
	spin_unlock_irqrestore(&data->txlock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक tsi108_set_link_ksettings(काष्ठा net_device *dev,
				     स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा tsi108_prv_data *data = netdev_priv(dev);
	अचिन्हित दीर्घ flags;
	पूर्णांक rc;

	spin_lock_irqsave(&data->txlock, flags);
	rc = mii_ethtool_set_link_ksettings(&data->mii_अगर, cmd);
	spin_unlock_irqrestore(&data->txlock, flags);

	वापस rc;
पूर्ण

अटल पूर्णांक tsi108_करो_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *rq, पूर्णांक cmd)
अणु
	काष्ठा tsi108_prv_data *data = netdev_priv(dev);
	अगर (!netअगर_running(dev))
		वापस -EINVAL;
	वापस generic_mii_ioctl(&data->mii_अगर, अगर_mii(rq), cmd, शून्य);
पूर्ण

अटल स्थिर काष्ठा ethtool_ops tsi108_ethtool_ops = अणु
	.get_link 	= ethtool_op_get_link,
	.get_link_ksettings	= tsi108_get_link_ksettings,
	.set_link_ksettings	= tsi108_set_link_ksettings,
पूर्ण;

अटल स्थिर काष्ठा net_device_ops tsi108_netdev_ops = अणु
	.nकरो_खोलो		= tsi108_खोलो,
	.nकरो_stop		= tsi108_बंद,
	.nकरो_start_xmit		= tsi108_send_packet,
	.nकरो_set_rx_mode	= tsi108_set_rx_mode,
	.nकरो_get_stats		= tsi108_get_stats,
	.nकरो_करो_ioctl		= tsi108_करो_ioctl,
	.nकरो_set_mac_address	= tsi108_set_mac,
	.nकरो_validate_addr	= eth_validate_addr,
पूर्ण;

अटल पूर्णांक
tsi108_init_one(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *dev = शून्य;
	काष्ठा tsi108_prv_data *data = शून्य;
	hw_info *einfo;
	पूर्णांक err = 0;

	einfo = dev_get_platdata(&pdev->dev);

	अगर (शून्य == einfo) अणु
		prपूर्णांकk(KERN_ERR "tsi-eth %d: Missing additional data!\n",
		       pdev->id);
		वापस -ENODEV;
	पूर्ण

	/* Create an ethernet device instance */

	dev = alloc_etherdev(माप(काष्ठा tsi108_prv_data));
	अगर (!dev)
		वापस -ENOMEM;

	prपूर्णांकk("tsi108_eth%d: probe...\n", pdev->id);
	data = netdev_priv(dev);
	data->dev = dev;
	data->pdev = pdev;

	pr_debug("tsi108_eth%d:regs:phyresgs:phy:irq_num=0x%x:0x%x:0x%x:0x%x\n",
			pdev->id, einfo->regs, einfo->phyregs,
			einfo->phy, einfo->irq_num);

	data->regs = ioremap(einfo->regs, 0x400);
	अगर (शून्य == data->regs) अणु
		err = -ENOMEM;
		जाओ regs_fail;
	पूर्ण

	data->phyregs = ioremap(einfo->phyregs, 0x400);
	अगर (शून्य == data->phyregs) अणु
		err = -ENOMEM;
		जाओ phyregs_fail;
	पूर्ण
/* MII setup */
	data->mii_अगर.dev = dev;
	data->mii_अगर.mdio_पढ़ो = tsi108_mdio_पढ़ो;
	data->mii_अगर.mdio_ग_लिखो = tsi108_mdio_ग_लिखो;
	data->mii_अगर.phy_id = einfo->phy;
	data->mii_अगर.phy_id_mask = 0x1f;
	data->mii_अगर.reg_num_mask = 0x1f;

	data->phy = einfo->phy;
	data->phy_type = einfo->phy_type;
	data->irq_num = einfo->irq_num;
	data->id = pdev->id;
	netअगर_napi_add(dev, &data->napi, tsi108_poll, 64);
	dev->netdev_ops = &tsi108_netdev_ops;
	dev->ethtool_ops = &tsi108_ethtool_ops;

	/* Apparently, the Linux networking code won't use scatter-gather
	 * अगर the hardware करोesn't do checksums.  However, it's faster
	 * to checksum in place and use SG, as (among other reasons)
	 * the cache won't be dirtied (which then has to be flushed
	 * beक्रमe DMA).  The checksumming is करोne by the driver (via
	 * a new function skb_csum_dev() in net/core/skbuff.c).
	 */

	dev->features = NETIF_F_HIGHDMA;

	spin_lock_init(&data->txlock);
	spin_lock_init(&data->misघड़ी);

	tsi108_reset_ether(data);
	tsi108_समाप्त_phy(dev);

	अगर ((err = tsi108_get_mac(dev)) != 0) अणु
		prपूर्णांकk(KERN_ERR "%s: Invalid MAC address.  Please correct.\n",
		       dev->name);
		जाओ रेजिस्टर_fail;
	पूर्ण

	tsi108_init_mac(dev);
	err = रेजिस्टर_netdev(dev);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "%s: Cannot register net device, aborting.\n",
				dev->name);
		जाओ रेजिस्टर_fail;
	पूर्ण

	platक्रमm_set_drvdata(pdev, dev);
	prपूर्णांकk(KERN_INFO "%s: Tsi108 Gigabit Ethernet, MAC: %pM\n",
	       dev->name, dev->dev_addr);
#अगर_घोषित DEBUG
	data->msg_enable = DEBUG;
	dump_eth_one(dev);
#पूर्ण_अगर

	वापस 0;

रेजिस्टर_fail:
	iounmap(data->phyregs);

phyregs_fail:
	iounmap(data->regs);

regs_fail:
	मुक्त_netdev(dev);
	वापस err;
पूर्ण

/* There's no way to either get पूर्णांकerrupts from the PHY when
 * something changes, or to have the Tsi108 स्वतःmatically communicate
 * with the PHY to reconfigure itself.
 *
 * Thus, we have to करो it using a समयr.
 */

अटल व्योम tsi108_समयd_checker(काष्ठा समयr_list *t)
अणु
	काष्ठा tsi108_prv_data *data = from_समयr(data, t, समयr);
	काष्ठा net_device *dev = data->dev;

	tsi108_check_phy(dev);
	tsi108_check_rxring(dev);
	mod_समयr(&data->समयr, jअगरfies + CHECK_PHY_INTERVAL);
पूर्ण

अटल पूर्णांक tsi108_ether_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *dev = platक्रमm_get_drvdata(pdev);
	काष्ठा tsi108_prv_data *priv = netdev_priv(dev);

	unरेजिस्टर_netdev(dev);
	tsi108_stop_ethernet(dev);
	iounmap(priv->regs);
	iounmap(priv->phyregs);
	मुक्त_netdev(dev);

	वापस 0;
पूर्ण
module_platक्रमm_driver(tsi_eth_driver);

MODULE_AUTHOR("Tundra Semiconductor Corporation");
MODULE_DESCRIPTION("Tsi108 Gigabit Ethernet driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:tsi-ethernet");
