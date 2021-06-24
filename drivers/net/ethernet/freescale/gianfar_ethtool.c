<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  drivers/net/ethernet/मुक्तscale/gianfar_ethtool.c
 *
 *  Gianfar Ethernet Driver
 *  Ethtool support क्रम Gianfar Enet
 *  Based on e1000 ethtool support
 *
 *  Author: Andy Fleming
 *  Maपूर्णांकainer: Kumar Gala
 *  Modअगरier: Sandeep Gopalpet <sandeep.kumar@मुक्तscale.com>
 *
 *  Copyright 2003-2006, 2008-2009, 2011 Freescale Semiconductor, Inc.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/net_tstamp.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/mm.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/module.h>
#समावेश <linux/crc32.h>
#समावेश <यंत्र/types.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/mii.h>
#समावेश <linux/phy.h>
#समावेश <linux/sort.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/fsl/ptp_qoriq.h>

#समावेश "gianfar.h"

#घोषणा GFAR_MAX_COAL_USECS 0xffff
#घोषणा GFAR_MAX_COAL_FRAMES 0xff

अटल स्थिर अक्षर stat_gstrings[][ETH_GSTRING_LEN] = अणु
	/* extra stats */
	"rx-allocation-errors",
	"rx-large-frame-errors",
	"rx-short-frame-errors",
	"rx-non-octet-errors",
	"rx-crc-errors",
	"rx-overrun-errors",
	"rx-busy-errors",
	"rx-babbling-errors",
	"rx-truncated-frames",
	"ethernet-bus-error",
	"tx-babbling-errors",
	"tx-underrun-errors",
	"tx-timeout-errors",
	/* rmon stats */
	"tx-rx-64-frames",
	"tx-rx-65-127-frames",
	"tx-rx-128-255-frames",
	"tx-rx-256-511-frames",
	"tx-rx-512-1023-frames",
	"tx-rx-1024-1518-frames",
	"tx-rx-1519-1522-good-vlan",
	"rx-bytes",
	"rx-packets",
	"rx-fcs-errors",
	"receive-multicast-packet",
	"receive-broadcast-packet",
	"rx-control-frame-packets",
	"rx-pause-frame-packets",
	"rx-unknown-op-code",
	"rx-alignment-error",
	"rx-frame-length-error",
	"rx-code-error",
	"rx-carrier-sense-error",
	"rx-undersize-packets",
	"rx-oversize-packets",
	"rx-fragmented-frames",
	"rx-jabber-frames",
	"rx-dropped-frames",
	"tx-byte-counter",
	"tx-packets",
	"tx-multicast-packets",
	"tx-broadcast-packets",
	"tx-pause-control-frames",
	"tx-deferral-packets",
	"tx-excessive-deferral-packets",
	"tx-single-collision-packets",
	"tx-multiple-collision-packets",
	"tx-late-collision-packets",
	"tx-excessive-collision-packets",
	"tx-total-collision",
	"reserved",
	"tx-dropped-frames",
	"tx-jabber-frames",
	"tx-fcs-errors",
	"tx-control-frames",
	"tx-oversize-frames",
	"tx-undersize-frames",
	"tx-fragmented-frames",
पूर्ण;

/* Fill in a buffer with the strings which correspond to the
 * stats */
अटल व्योम gfar_gstrings(काष्ठा net_device *dev, u32 stringset, u8 * buf)
अणु
	काष्ठा gfar_निजी *priv = netdev_priv(dev);

	अगर (priv->device_flags & FSL_GIANFAR_DEV_HAS_RMON)
		स_नकल(buf, stat_gstrings, GFAR_STATS_LEN * ETH_GSTRING_LEN);
	अन्यथा
		स_नकल(buf, stat_gstrings,
		       GFAR_EXTRA_STATS_LEN * ETH_GSTRING_LEN);
पूर्ण

/* Fill in an array of 64-bit statistics from various sources.
 * This array will be appended to the end of the ethtool_stats
 * काष्ठाure, and वापसed to user space
 */
अटल व्योम gfar_fill_stats(काष्ठा net_device *dev, काष्ठा ethtool_stats *dummy,
			    u64 *buf)
अणु
	पूर्णांक i;
	काष्ठा gfar_निजी *priv = netdev_priv(dev);
	काष्ठा gfar __iomem *regs = priv->gfargrp[0].regs;
	atomic64_t *extra = (atomic64_t *)&priv->extra_stats;

	क्रम (i = 0; i < GFAR_EXTRA_STATS_LEN; i++)
		buf[i] = atomic64_पढ़ो(&extra[i]);

	अगर (priv->device_flags & FSL_GIANFAR_DEV_HAS_RMON) अणु
		u32 __iomem *rmon = (u32 __iomem *) &regs->rmon;

		क्रम (; i < GFAR_STATS_LEN; i++, rmon++)
			buf[i] = (u64) gfar_पढ़ो(rmon);
	पूर्ण
पूर्ण

अटल पूर्णांक gfar_sset_count(काष्ठा net_device *dev, पूर्णांक sset)
अणु
	काष्ठा gfar_निजी *priv = netdev_priv(dev);

	चयन (sset) अणु
	हाल ETH_SS_STATS:
		अगर (priv->device_flags & FSL_GIANFAR_DEV_HAS_RMON)
			वापस GFAR_STATS_LEN;
		अन्यथा
			वापस GFAR_EXTRA_STATS_LEN;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

/* Fills in the drvinfo काष्ठाure with some basic info */
अटल व्योम gfar_gdrvinfo(काष्ठा net_device *dev,
			  काष्ठा ethtool_drvinfo *drvinfo)
अणु
	strlcpy(drvinfo->driver, DRV_NAME, माप(drvinfo->driver));
पूर्ण

/* Return the length of the रेजिस्टर काष्ठाure */
अटल पूर्णांक gfar_reglen(काष्ठा net_device *dev)
अणु
	वापस माप (काष्ठा gfar);
पूर्ण

/* Return a dump of the GFAR रेजिस्टर space */
अटल व्योम gfar_get_regs(काष्ठा net_device *dev, काष्ठा ethtool_regs *regs,
			  व्योम *regbuf)
अणु
	पूर्णांक i;
	काष्ठा gfar_निजी *priv = netdev_priv(dev);
	u32 __iomem *theregs = (u32 __iomem *) priv->gfargrp[0].regs;
	u32 *buf = (u32 *) regbuf;

	क्रम (i = 0; i < माप (काष्ठा gfar) / माप (u32); i++)
		buf[i] = gfar_पढ़ो(&theregs[i]);
पूर्ण

/* Convert microseconds to ethernet घड़ी ticks, which changes
 * depending on what speed the controller is running at */
अटल अचिन्हित पूर्णांक gfar_usecs2ticks(काष्ठा gfar_निजी *priv,
				     अचिन्हित पूर्णांक usecs)
अणु
	काष्ठा net_device *ndev = priv->ndev;
	काष्ठा phy_device *phydev = ndev->phydev;
	अचिन्हित पूर्णांक count;

	/* The समयr is dअगरferent, depending on the पूर्णांकerface speed */
	चयन (phydev->speed) अणु
	हाल SPEED_1000:
		count = GFAR_GBIT_TIME;
		अवरोध;
	हाल SPEED_100:
		count = GFAR_100_TIME;
		अवरोध;
	हाल SPEED_10:
	शेष:
		count = GFAR_10_TIME;
		अवरोध;
	पूर्ण

	/* Make sure we वापस a number greater than 0
	 * अगर usecs > 0 */
	वापस DIV_ROUND_UP(usecs * 1000, count);
पूर्ण

/* Convert ethernet घड़ी ticks to microseconds */
अटल अचिन्हित पूर्णांक gfar_ticks2usecs(काष्ठा gfar_निजी *priv,
				     अचिन्हित पूर्णांक ticks)
अणु
	काष्ठा net_device *ndev = priv->ndev;
	काष्ठा phy_device *phydev = ndev->phydev;
	अचिन्हित पूर्णांक count;

	/* The समयr is dअगरferent, depending on the पूर्णांकerface speed */
	चयन (phydev->speed) अणु
	हाल SPEED_1000:
		count = GFAR_GBIT_TIME;
		अवरोध;
	हाल SPEED_100:
		count = GFAR_100_TIME;
		अवरोध;
	हाल SPEED_10:
	शेष:
		count = GFAR_10_TIME;
		अवरोध;
	पूर्ण

	/* Make sure we वापस a number greater than 0 */
	/* अगर ticks is > 0 */
	वापस (ticks * count) / 1000;
पूर्ण

/* Get the coalescing parameters, and put them in the cvals
 * काष्ठाure.  */
अटल पूर्णांक gfar_gcoalesce(काष्ठा net_device *dev,
			  काष्ठा ethtool_coalesce *cvals)
अणु
	काष्ठा gfar_निजी *priv = netdev_priv(dev);
	काष्ठा gfar_priv_rx_q *rx_queue = शून्य;
	काष्ठा gfar_priv_tx_q *tx_queue = शून्य;
	अचिन्हित दीर्घ rxसमय;
	अचिन्हित दीर्घ rxcount;
	अचिन्हित दीर्घ txसमय;
	अचिन्हित दीर्घ txcount;

	अगर (!(priv->device_flags & FSL_GIANFAR_DEV_HAS_COALESCE))
		वापस -EOPNOTSUPP;

	अगर (!dev->phydev)
		वापस -ENODEV;

	rx_queue = priv->rx_queue[0];
	tx_queue = priv->tx_queue[0];

	rxसमय  = get_ictt_value(rx_queue->rxic);
	rxcount = get_icft_value(rx_queue->rxic);
	txसमय  = get_ictt_value(tx_queue->txic);
	txcount = get_icft_value(tx_queue->txic);
	cvals->rx_coalesce_usecs = gfar_ticks2usecs(priv, rxसमय);
	cvals->rx_max_coalesced_frames = rxcount;

	cvals->tx_coalesce_usecs = gfar_ticks2usecs(priv, txसमय);
	cvals->tx_max_coalesced_frames = txcount;

	वापस 0;
पूर्ण

/* Change the coalescing values.
 * Both cvals->*_usecs and cvals->*_frames have to be > 0
 * in order क्रम coalescing to be active
 */
अटल पूर्णांक gfar_scoalesce(काष्ठा net_device *dev,
			  काष्ठा ethtool_coalesce *cvals)
अणु
	काष्ठा gfar_निजी *priv = netdev_priv(dev);
	पूर्णांक i, err = 0;

	अगर (!(priv->device_flags & FSL_GIANFAR_DEV_HAS_COALESCE))
		वापस -EOPNOTSUPP;

	अगर (!dev->phydev)
		वापस -ENODEV;

	/* Check the bounds of the values */
	अगर (cvals->rx_coalesce_usecs > GFAR_MAX_COAL_USECS) अणु
		netdev_info(dev, "Coalescing is limited to %d microseconds\n",
			    GFAR_MAX_COAL_USECS);
		वापस -EINVAL;
	पूर्ण

	अगर (cvals->rx_max_coalesced_frames > GFAR_MAX_COAL_FRAMES) अणु
		netdev_info(dev, "Coalescing is limited to %d frames\n",
			    GFAR_MAX_COAL_FRAMES);
		वापस -EINVAL;
	पूर्ण

	/* Check the bounds of the values */
	अगर (cvals->tx_coalesce_usecs > GFAR_MAX_COAL_USECS) अणु
		netdev_info(dev, "Coalescing is limited to %d microseconds\n",
			    GFAR_MAX_COAL_USECS);
		वापस -EINVAL;
	पूर्ण

	अगर (cvals->tx_max_coalesced_frames > GFAR_MAX_COAL_FRAMES) अणु
		netdev_info(dev, "Coalescing is limited to %d frames\n",
			    GFAR_MAX_COAL_FRAMES);
		वापस -EINVAL;
	पूर्ण

	जबतक (test_and_set_bit_lock(GFAR_RESETTING, &priv->state))
		cpu_relax();

	/* Set up rx coalescing */
	अगर ((cvals->rx_coalesce_usecs == 0) ||
	    (cvals->rx_max_coalesced_frames == 0)) अणु
		क्रम (i = 0; i < priv->num_rx_queues; i++)
			priv->rx_queue[i]->rxcoalescing = 0;
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < priv->num_rx_queues; i++)
			priv->rx_queue[i]->rxcoalescing = 1;
	पूर्ण

	क्रम (i = 0; i < priv->num_rx_queues; i++) अणु
		priv->rx_queue[i]->rxic = mk_ic_value(
			cvals->rx_max_coalesced_frames,
			gfar_usecs2ticks(priv, cvals->rx_coalesce_usecs));
	पूर्ण

	/* Set up tx coalescing */
	अगर ((cvals->tx_coalesce_usecs == 0) ||
	    (cvals->tx_max_coalesced_frames == 0)) अणु
		क्रम (i = 0; i < priv->num_tx_queues; i++)
			priv->tx_queue[i]->txcoalescing = 0;
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < priv->num_tx_queues; i++)
			priv->tx_queue[i]->txcoalescing = 1;
	पूर्ण

	क्रम (i = 0; i < priv->num_tx_queues; i++) अणु
		priv->tx_queue[i]->txic = mk_ic_value(
			cvals->tx_max_coalesced_frames,
			gfar_usecs2ticks(priv, cvals->tx_coalesce_usecs));
	पूर्ण

	अगर (dev->flags & IFF_UP) अणु
		stop_gfar(dev);
		err = startup_gfar(dev);
	पूर्ण अन्यथा अणु
		gfar_mac_reset(priv);
	पूर्ण

	clear_bit_unlock(GFAR_RESETTING, &priv->state);

	वापस err;
पूर्ण

/* Fills in rvals with the current ring parameters.  Currently,
 * rx, rx_mini, and rx_jumbo rings are the same size, as mini and
 * jumbo are ignored by the driver */
अटल व्योम gfar_gringparam(काष्ठा net_device *dev,
			    काष्ठा ethtool_ringparam *rvals)
अणु
	काष्ठा gfar_निजी *priv = netdev_priv(dev);
	काष्ठा gfar_priv_tx_q *tx_queue = शून्य;
	काष्ठा gfar_priv_rx_q *rx_queue = शून्य;

	tx_queue = priv->tx_queue[0];
	rx_queue = priv->rx_queue[0];

	rvals->rx_max_pending = GFAR_RX_MAX_RING_SIZE;
	rvals->rx_mini_max_pending = GFAR_RX_MAX_RING_SIZE;
	rvals->rx_jumbo_max_pending = GFAR_RX_MAX_RING_SIZE;
	rvals->tx_max_pending = GFAR_TX_MAX_RING_SIZE;

	/* Values changeable by the user.  The valid values are
	 * in the range 1 to the "*_max_pending" counterpart above.
	 */
	rvals->rx_pending = rx_queue->rx_ring_size;
	rvals->rx_mini_pending = rx_queue->rx_ring_size;
	rvals->rx_jumbo_pending = rx_queue->rx_ring_size;
	rvals->tx_pending = tx_queue->tx_ring_size;
पूर्ण

/* Change the current ring parameters, stopping the controller अगर
 * necessary so that we करोn't mess things up while we're in motion.
 */
अटल पूर्णांक gfar_sringparam(काष्ठा net_device *dev,
			   काष्ठा ethtool_ringparam *rvals)
अणु
	काष्ठा gfar_निजी *priv = netdev_priv(dev);
	पूर्णांक err = 0, i;

	अगर (rvals->rx_pending > GFAR_RX_MAX_RING_SIZE)
		वापस -EINVAL;

	अगर (!is_घातer_of_2(rvals->rx_pending)) अणु
		netdev_err(dev, "Ring sizes must be a power of 2\n");
		वापस -EINVAL;
	पूर्ण

	अगर (rvals->tx_pending > GFAR_TX_MAX_RING_SIZE)
		वापस -EINVAL;

	अगर (!is_घातer_of_2(rvals->tx_pending)) अणु
		netdev_err(dev, "Ring sizes must be a power of 2\n");
		वापस -EINVAL;
	पूर्ण

	जबतक (test_and_set_bit_lock(GFAR_RESETTING, &priv->state))
		cpu_relax();

	अगर (dev->flags & IFF_UP)
		stop_gfar(dev);

	/* Change the sizes */
	क्रम (i = 0; i < priv->num_rx_queues; i++)
		priv->rx_queue[i]->rx_ring_size = rvals->rx_pending;

	क्रम (i = 0; i < priv->num_tx_queues; i++)
		priv->tx_queue[i]->tx_ring_size = rvals->tx_pending;

	/* Rebuild the rings with the new size */
	अगर (dev->flags & IFF_UP)
		err = startup_gfar(dev);

	clear_bit_unlock(GFAR_RESETTING, &priv->state);

	वापस err;
पूर्ण

अटल व्योम gfar_gछोड़ोparam(काष्ठा net_device *dev,
			     काष्ठा ethtool_छोड़ोparam *eछोड़ो)
अणु
	काष्ठा gfar_निजी *priv = netdev_priv(dev);

	eछोड़ो->स्वतःneg = !!priv->छोड़ो_aneg_en;
	eछोड़ो->rx_छोड़ो = !!priv->rx_छोड़ो_en;
	eछोड़ो->tx_छोड़ो = !!priv->tx_छोड़ो_en;
पूर्ण

अटल पूर्णांक gfar_sछोड़ोparam(काष्ठा net_device *dev,
			    काष्ठा ethtool_छोड़ोparam *eछोड़ो)
अणु
	काष्ठा gfar_निजी *priv = netdev_priv(dev);
	काष्ठा phy_device *phydev = dev->phydev;
	काष्ठा gfar __iomem *regs = priv->gfargrp[0].regs;

	अगर (!phydev)
		वापस -ENODEV;

	अगर (!phy_validate_छोड़ो(phydev, eछोड़ो))
		वापस -EINVAL;

	priv->rx_छोड़ो_en = priv->tx_छोड़ो_en = 0;
	phy_set_asym_छोड़ो(phydev, eछोड़ो->rx_छोड़ो, eछोड़ो->tx_छोड़ो);
	अगर (eछोड़ो->rx_छोड़ो) अणु
		priv->rx_छोड़ो_en = 1;

		अगर (eछोड़ो->tx_छोड़ो) अणु
			priv->tx_छोड़ो_en = 1;
		पूर्ण
	पूर्ण अन्यथा अगर (eछोड़ो->tx_छोड़ो) अणु
		priv->tx_छोड़ो_en = 1;
	पूर्ण

	अगर (eछोड़ो->स्वतःneg)
		priv->छोड़ो_aneg_en = 1;
	अन्यथा
		priv->छोड़ो_aneg_en = 0;

	अगर (!eछोड़ो->स्वतःneg) अणु
		u32 tempval = gfar_पढ़ो(&regs->maccfg1);

		tempval &= ~(MACCFG1_TX_FLOW | MACCFG1_RX_FLOW);

		priv->tx_actual_en = 0;
		अगर (priv->tx_छोड़ो_en) अणु
			priv->tx_actual_en = 1;
			tempval |= MACCFG1_TX_FLOW;
		पूर्ण

		अगर (priv->rx_छोड़ो_en)
			tempval |= MACCFG1_RX_FLOW;
		gfar_ग_लिखो(&regs->maccfg1, tempval);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक gfar_set_features(काष्ठा net_device *dev, netdev_features_t features)
अणु
	netdev_features_t changed = dev->features ^ features;
	काष्ठा gfar_निजी *priv = netdev_priv(dev);
	पूर्णांक err = 0;

	अगर (!(changed & (NETIF_F_HW_VLAN_CTAG_TX | NETIF_F_HW_VLAN_CTAG_RX |
			 NETIF_F_RXCSUM)))
		वापस 0;

	जबतक (test_and_set_bit_lock(GFAR_RESETTING, &priv->state))
		cpu_relax();

	dev->features = features;

	अगर (dev->flags & IFF_UP) अणु
		/* Now we take करोwn the rings to rebuild them */
		stop_gfar(dev);
		err = startup_gfar(dev);
	पूर्ण अन्यथा अणु
		gfar_mac_reset(priv);
	पूर्ण

	clear_bit_unlock(GFAR_RESETTING, &priv->state);

	वापस err;
पूर्ण

अटल uपूर्णांक32_t gfar_get_msglevel(काष्ठा net_device *dev)
अणु
	काष्ठा gfar_निजी *priv = netdev_priv(dev);

	वापस priv->msg_enable;
पूर्ण

अटल व्योम gfar_set_msglevel(काष्ठा net_device *dev, uपूर्णांक32_t data)
अणु
	काष्ठा gfar_निजी *priv = netdev_priv(dev);

	priv->msg_enable = data;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल व्योम gfar_get_wol(काष्ठा net_device *dev, काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा gfar_निजी *priv = netdev_priv(dev);

	wol->supported = 0;
	wol->wolopts = 0;

	अगर (priv->wol_supported & GFAR_WOL_MAGIC)
		wol->supported |= WAKE_MAGIC;

	अगर (priv->wol_supported & GFAR_WOL_खाताR_UCAST)
		wol->supported |= WAKE_UCAST;

	अगर (priv->wol_opts & GFAR_WOL_MAGIC)
		wol->wolopts |= WAKE_MAGIC;

	अगर (priv->wol_opts & GFAR_WOL_खाताR_UCAST)
		wol->wolopts |= WAKE_UCAST;
पूर्ण

अटल पूर्णांक gfar_set_wol(काष्ठा net_device *dev, काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा gfar_निजी *priv = netdev_priv(dev);
	u16 wol_opts = 0;
	पूर्णांक err;

	अगर (!priv->wol_supported && wol->wolopts)
		वापस -EINVAL;

	अगर (wol->wolopts & ~(WAKE_MAGIC | WAKE_UCAST))
		वापस -EINVAL;

	अगर (wol->wolopts & WAKE_MAGIC) अणु
		wol_opts |= GFAR_WOL_MAGIC;
	पूर्ण अन्यथा अणु
		अगर (wol->wolopts & WAKE_UCAST)
			wol_opts |= GFAR_WOL_खाताR_UCAST;
	पूर्ण

	wol_opts &= priv->wol_supported;
	priv->wol_opts = 0;

	err = device_set_wakeup_enable(priv->dev, wol_opts);
	अगर (err)
		वापस err;

	priv->wol_opts = wol_opts;

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल व्योम ethflow_to_filer_rules (काष्ठा gfar_निजी *priv, u64 ethflow)
अणु
	u32 fcr = 0x0, fpr = FPR_खाताR_MASK;

	अगर (ethflow & RXH_L2DA) अणु
		fcr = RQFCR_PID_DAH | RQFCR_CMP_NOMATCH |
		      RQFCR_HASH | RQFCR_AND | RQFCR_HASHTBL_0;
		priv->ftp_rqfpr[priv->cur_filer_idx] = fpr;
		priv->ftp_rqfcr[priv->cur_filer_idx] = fcr;
		gfar_ग_लिखो_filer(priv, priv->cur_filer_idx, fcr, fpr);
		priv->cur_filer_idx = priv->cur_filer_idx - 1;

		fcr = RQFCR_PID_DAL | RQFCR_CMP_NOMATCH |
		      RQFCR_HASH | RQFCR_AND | RQFCR_HASHTBL_0;
		priv->ftp_rqfpr[priv->cur_filer_idx] = fpr;
		priv->ftp_rqfcr[priv->cur_filer_idx] = fcr;
		gfar_ग_लिखो_filer(priv, priv->cur_filer_idx, fcr, fpr);
		priv->cur_filer_idx = priv->cur_filer_idx - 1;
	पूर्ण

	अगर (ethflow & RXH_VLAN) अणु
		fcr = RQFCR_PID_VID | RQFCR_CMP_NOMATCH | RQFCR_HASH |
		      RQFCR_AND | RQFCR_HASHTBL_0;
		gfar_ग_लिखो_filer(priv, priv->cur_filer_idx, fcr, fpr);
		priv->ftp_rqfpr[priv->cur_filer_idx] = fpr;
		priv->ftp_rqfcr[priv->cur_filer_idx] = fcr;
		priv->cur_filer_idx = priv->cur_filer_idx - 1;
	पूर्ण

	अगर (ethflow & RXH_IP_SRC) अणु
		fcr = RQFCR_PID_SIA | RQFCR_CMP_NOMATCH | RQFCR_HASH |
		      RQFCR_AND | RQFCR_HASHTBL_0;
		priv->ftp_rqfpr[priv->cur_filer_idx] = fpr;
		priv->ftp_rqfcr[priv->cur_filer_idx] = fcr;
		gfar_ग_लिखो_filer(priv, priv->cur_filer_idx, fcr, fpr);
		priv->cur_filer_idx = priv->cur_filer_idx - 1;
	पूर्ण

	अगर (ethflow & (RXH_IP_DST)) अणु
		fcr = RQFCR_PID_DIA | RQFCR_CMP_NOMATCH | RQFCR_HASH |
		      RQFCR_AND | RQFCR_HASHTBL_0;
		priv->ftp_rqfpr[priv->cur_filer_idx] = fpr;
		priv->ftp_rqfcr[priv->cur_filer_idx] = fcr;
		gfar_ग_लिखो_filer(priv, priv->cur_filer_idx, fcr, fpr);
		priv->cur_filer_idx = priv->cur_filer_idx - 1;
	पूर्ण

	अगर (ethflow & RXH_L3_PROTO) अणु
		fcr = RQFCR_PID_L4P | RQFCR_CMP_NOMATCH | RQFCR_HASH |
		      RQFCR_AND | RQFCR_HASHTBL_0;
		priv->ftp_rqfpr[priv->cur_filer_idx] = fpr;
		priv->ftp_rqfcr[priv->cur_filer_idx] = fcr;
		gfar_ग_लिखो_filer(priv, priv->cur_filer_idx, fcr, fpr);
		priv->cur_filer_idx = priv->cur_filer_idx - 1;
	पूर्ण

	अगर (ethflow & RXH_L4_B_0_1) अणु
		fcr = RQFCR_PID_SPT | RQFCR_CMP_NOMATCH | RQFCR_HASH |
		      RQFCR_AND | RQFCR_HASHTBL_0;
		priv->ftp_rqfpr[priv->cur_filer_idx] = fpr;
		priv->ftp_rqfcr[priv->cur_filer_idx] = fcr;
		gfar_ग_लिखो_filer(priv, priv->cur_filer_idx, fcr, fpr);
		priv->cur_filer_idx = priv->cur_filer_idx - 1;
	पूर्ण

	अगर (ethflow & RXH_L4_B_2_3) अणु
		fcr = RQFCR_PID_DPT | RQFCR_CMP_NOMATCH | RQFCR_HASH |
		      RQFCR_AND | RQFCR_HASHTBL_0;
		priv->ftp_rqfpr[priv->cur_filer_idx] = fpr;
		priv->ftp_rqfcr[priv->cur_filer_idx] = fcr;
		gfar_ग_लिखो_filer(priv, priv->cur_filer_idx, fcr, fpr);
		priv->cur_filer_idx = priv->cur_filer_idx - 1;
	पूर्ण
पूर्ण

अटल पूर्णांक gfar_ethflow_to_filer_table(काष्ठा gfar_निजी *priv, u64 ethflow,
				       u64 class)
अणु
	अचिन्हित पूर्णांक cmp_rqfpr;
	अचिन्हित पूर्णांक *local_rqfpr;
	अचिन्हित पूर्णांक *local_rqfcr;
	पूर्णांक i = 0x0, k = 0x0;
	पूर्णांक j = MAX_खाताR_IDX, l = 0x0;
	पूर्णांक ret = 1;

	local_rqfpr = kदो_स्मृति_array(MAX_खाताR_IDX + 1, माप(अचिन्हित पूर्णांक),
				    GFP_KERNEL);
	local_rqfcr = kदो_स्मृति_array(MAX_खाताR_IDX + 1, माप(अचिन्हित पूर्णांक),
				    GFP_KERNEL);
	अगर (!local_rqfpr || !local_rqfcr) अणु
		ret = 0;
		जाओ err;
	पूर्ण

	चयन (class) अणु
	हाल TCP_V4_FLOW:
		cmp_rqfpr = RQFPR_IPV4 |RQFPR_TCP;
		अवरोध;
	हाल UDP_V4_FLOW:
		cmp_rqfpr = RQFPR_IPV4 |RQFPR_UDP;
		अवरोध;
	हाल TCP_V6_FLOW:
		cmp_rqfpr = RQFPR_IPV6 |RQFPR_TCP;
		अवरोध;
	हाल UDP_V6_FLOW:
		cmp_rqfpr = RQFPR_IPV6 |RQFPR_UDP;
		अवरोध;
	शेष:
		netdev_err(priv->ndev,
			   "Right now this class is not supported\n");
		ret = 0;
		जाओ err;
	पूर्ण

	क्रम (i = 0; i < MAX_खाताR_IDX + 1; i++) अणु
		local_rqfpr[j] = priv->ftp_rqfpr[i];
		local_rqfcr[j] = priv->ftp_rqfcr[i];
		j--;
		अगर ((priv->ftp_rqfcr[i] ==
		     (RQFCR_PID_PARSE | RQFCR_CLE | RQFCR_AND)) &&
		    (priv->ftp_rqfpr[i] == cmp_rqfpr))
			अवरोध;
	पूर्ण

	अगर (i == MAX_खाताR_IDX + 1) अणु
		netdev_err(priv->ndev,
			   "No parse rule found, can't create hash rules\n");
		ret = 0;
		जाओ err;
	पूर्ण

	/* If a match was found, then it begins the starting of a cluster rule
	 * अगर it was alपढ़ोy programmed, we need to overग_लिखो these rules
	 */
	क्रम (l = i+1; l < MAX_खाताR_IDX; l++) अणु
		अगर ((priv->ftp_rqfcr[l] & RQFCR_CLE) &&
		    !(priv->ftp_rqfcr[l] & RQFCR_AND)) अणु
			priv->ftp_rqfcr[l] = RQFCR_CLE | RQFCR_CMP_EXACT |
					     RQFCR_HASHTBL_0 | RQFCR_PID_MASK;
			priv->ftp_rqfpr[l] = FPR_खाताR_MASK;
			gfar_ग_लिखो_filer(priv, l, priv->ftp_rqfcr[l],
					 priv->ftp_rqfpr[l]);
			अवरोध;
		पूर्ण

		अगर (!(priv->ftp_rqfcr[l] & RQFCR_CLE) &&
			(priv->ftp_rqfcr[l] & RQFCR_AND))
			जारी;
		अन्यथा अणु
			local_rqfpr[j] = priv->ftp_rqfpr[l];
			local_rqfcr[j] = priv->ftp_rqfcr[l];
			j--;
		पूर्ण
	पूर्ण

	priv->cur_filer_idx = l - 1;

	/* hash rules */
	ethflow_to_filer_rules(priv, ethflow);

	/* Write back the popped out rules again */
	क्रम (k = j+1; k < MAX_खाताR_IDX; k++) अणु
		priv->ftp_rqfpr[priv->cur_filer_idx] = local_rqfpr[k];
		priv->ftp_rqfcr[priv->cur_filer_idx] = local_rqfcr[k];
		gfar_ग_लिखो_filer(priv, priv->cur_filer_idx,
				 local_rqfcr[k], local_rqfpr[k]);
		अगर (!priv->cur_filer_idx)
			अवरोध;
		priv->cur_filer_idx = priv->cur_filer_idx - 1;
	पूर्ण

err:
	kमुक्त(local_rqfcr);
	kमुक्त(local_rqfpr);
	वापस ret;
पूर्ण

अटल पूर्णांक gfar_set_hash_opts(काष्ठा gfar_निजी *priv,
			      काष्ठा ethtool_rxnfc *cmd)
अणु
	/* ग_लिखो the filer rules here */
	अगर (!gfar_ethflow_to_filer_table(priv, cmd->data, cmd->flow_type))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक gfar_check_filer_hardware(काष्ठा gfar_निजी *priv)
अणु
	काष्ठा gfar __iomem *regs = priv->gfargrp[0].regs;
	u32 i;

	/* Check अगर we are in FIFO mode */
	i = gfar_पढ़ो(&regs->ecntrl);
	i &= ECNTRL_FIFM;
	अगर (i == ECNTRL_FIFM) अणु
		netdev_notice(priv->ndev, "Interface in FIFO mode\n");
		i = gfar_पढ़ो(&regs->rctrl);
		i &= RCTRL_PRSDEP_MASK | RCTRL_PRSFM;
		अगर (i == (RCTRL_PRSDEP_MASK | RCTRL_PRSFM)) अणु
			netdev_info(priv->ndev,
				    "Receive Queue Filtering enabled\n");
		पूर्ण अन्यथा अणु
			netdev_warn(priv->ndev,
				    "Receive Queue Filtering disabled\n");
			वापस -EOPNOTSUPP;
		पूर्ण
	पूर्ण
	/* Or in standard mode */
	अन्यथा अणु
		i = gfar_पढ़ो(&regs->rctrl);
		i &= RCTRL_PRSDEP_MASK;
		अगर (i == RCTRL_PRSDEP_MASK) अणु
			netdev_info(priv->ndev,
				    "Receive Queue Filtering enabled\n");
		पूर्ण अन्यथा अणु
			netdev_warn(priv->ndev,
				    "Receive Queue Filtering disabled\n");
			वापस -EOPNOTSUPP;
		पूर्ण
	पूर्ण

	/* Sets the properties क्रम arbitrary filer rule
	 * to the first 4 Layer 4 Bytes
	 */
	gfar_ग_लिखो(&regs->rbअगरx, 0xC0C1C2C3);
	वापस 0;
पूर्ण

/* Write a mask to filer cache */
अटल व्योम gfar_set_mask(u32 mask, काष्ठा filer_table *tab)
अणु
	tab->fe[tab->index].ctrl = RQFCR_AND | RQFCR_PID_MASK | RQFCR_CMP_EXACT;
	tab->fe[tab->index].prop = mask;
	tab->index++;
पूर्ण

/* Sets parse bits (e.g. IP or TCP) */
अटल व्योम gfar_set_parse_bits(u32 value, u32 mask, काष्ठा filer_table *tab)
अणु
	gfar_set_mask(mask, tab);
	tab->fe[tab->index].ctrl = RQFCR_CMP_EXACT | RQFCR_PID_PARSE |
				   RQFCR_AND;
	tab->fe[tab->index].prop = value;
	tab->index++;
पूर्ण

अटल व्योम gfar_set_general_attribute(u32 value, u32 mask, u32 flag,
				       काष्ठा filer_table *tab)
अणु
	gfar_set_mask(mask, tab);
	tab->fe[tab->index].ctrl = RQFCR_CMP_EXACT | RQFCR_AND | flag;
	tab->fe[tab->index].prop = value;
	tab->index++;
पूर्ण

/* For setting a tuple of value and mask of type flag
 * Example:
 * IP-Src = 10.0.0.0/255.0.0.0
 * value: 0x0A000000 mask: FF000000 flag: RQFPR_IPV4
 *
 * Ethtool gives us a value=0 and mask=~0 क्रम करोn't care a tuple
 * For a करोn't care mask it gives us a 0
 *
 * The check अगर करोn't care and the mask adjusपंचांगent अगर mask=0 is करोne क्रम VLAN
 * and MAC stuff on an upper level (due to missing inक्रमmation on this level).
 * For these guys we can discard them अगर they are value=0 and mask=0.
 *
 * Further the all masks are one-padded क्रम better hardware efficiency.
 */
अटल व्योम gfar_set_attribute(u32 value, u32 mask, u32 flag,
			       काष्ठा filer_table *tab)
अणु
	चयन (flag) अणु
		/* 3bit */
	हाल RQFCR_PID_PRI:
		अगर (!(value | mask))
			वापस;
		mask |= RQFCR_PID_PRI_MASK;
		अवरोध;
		/* 8bit */
	हाल RQFCR_PID_L4P:
	हाल RQFCR_PID_TOS:
		अगर (!~(mask | RQFCR_PID_L4P_MASK))
			वापस;
		अगर (!mask)
			mask = ~0;
		अन्यथा
			mask |= RQFCR_PID_L4P_MASK;
		अवरोध;
		/* 12bit */
	हाल RQFCR_PID_VID:
		अगर (!(value | mask))
			वापस;
		mask |= RQFCR_PID_VID_MASK;
		अवरोध;
		/* 16bit */
	हाल RQFCR_PID_DPT:
	हाल RQFCR_PID_SPT:
	हाल RQFCR_PID_ETY:
		अगर (!~(mask | RQFCR_PID_PORT_MASK))
			वापस;
		अगर (!mask)
			mask = ~0;
		अन्यथा
			mask |= RQFCR_PID_PORT_MASK;
		अवरोध;
		/* 24bit */
	हाल RQFCR_PID_DAH:
	हाल RQFCR_PID_DAL:
	हाल RQFCR_PID_SAH:
	हाल RQFCR_PID_SAL:
		अगर (!(value | mask))
			वापस;
		mask |= RQFCR_PID_MAC_MASK;
		अवरोध;
		/* क्रम all real 32bit masks */
	शेष:
		अगर (!~mask)
			वापस;
		अगर (!mask)
			mask = ~0;
		अवरोध;
	पूर्ण
	gfar_set_general_attribute(value, mask, flag, tab);
पूर्ण

/* Translates value and mask क्रम UDP, TCP or SCTP */
अटल व्योम gfar_set_basic_ip(काष्ठा ethtool_tcpip4_spec *value,
			      काष्ठा ethtool_tcpip4_spec *mask,
			      काष्ठा filer_table *tab)
अणु
	gfar_set_attribute(be32_to_cpu(value->ip4src),
			   be32_to_cpu(mask->ip4src),
			   RQFCR_PID_SIA, tab);
	gfar_set_attribute(be32_to_cpu(value->ip4dst),
			   be32_to_cpu(mask->ip4dst),
			   RQFCR_PID_DIA, tab);
	gfar_set_attribute(be16_to_cpu(value->pdst),
			   be16_to_cpu(mask->pdst),
			   RQFCR_PID_DPT, tab);
	gfar_set_attribute(be16_to_cpu(value->psrc),
			   be16_to_cpu(mask->psrc),
			   RQFCR_PID_SPT, tab);
	gfar_set_attribute(value->tos, mask->tos, RQFCR_PID_TOS, tab);
पूर्ण

/* Translates value and mask क्रम RAW-IP4 */
अटल व्योम gfar_set_user_ip(काष्ठा ethtool_usrip4_spec *value,
			     काष्ठा ethtool_usrip4_spec *mask,
			     काष्ठा filer_table *tab)
अणु
	gfar_set_attribute(be32_to_cpu(value->ip4src),
			   be32_to_cpu(mask->ip4src),
			   RQFCR_PID_SIA, tab);
	gfar_set_attribute(be32_to_cpu(value->ip4dst),
			   be32_to_cpu(mask->ip4dst),
			   RQFCR_PID_DIA, tab);
	gfar_set_attribute(value->tos, mask->tos, RQFCR_PID_TOS, tab);
	gfar_set_attribute(value->proto, mask->proto, RQFCR_PID_L4P, tab);
	gfar_set_attribute(be32_to_cpu(value->l4_4_bytes),
			   be32_to_cpu(mask->l4_4_bytes),
			   RQFCR_PID_ARB, tab);

पूर्ण

/* Translates value and mask क्रम ETHER spec */
अटल व्योम gfar_set_ether(काष्ठा ethhdr *value, काष्ठा ethhdr *mask,
			   काष्ठा filer_table *tab)
अणु
	u32 upper_temp_mask = 0;
	u32 lower_temp_mask = 0;

	/* Source address */
	अगर (!is_broadcast_ether_addr(mask->h_source)) अणु
		अगर (is_zero_ether_addr(mask->h_source)) अणु
			upper_temp_mask = 0xFFFFFFFF;
			lower_temp_mask = 0xFFFFFFFF;
		पूर्ण अन्यथा अणु
			upper_temp_mask = mask->h_source[0] << 16 |
					  mask->h_source[1] << 8  |
					  mask->h_source[2];
			lower_temp_mask = mask->h_source[3] << 16 |
					  mask->h_source[4] << 8  |
					  mask->h_source[5];
		पूर्ण
		/* Upper 24bit */
		gfar_set_attribute(value->h_source[0] << 16 |
				   value->h_source[1] << 8  |
				   value->h_source[2],
				   upper_temp_mask, RQFCR_PID_SAH, tab);
		/* And the same क्रम the lower part */
		gfar_set_attribute(value->h_source[3] << 16 |
				   value->h_source[4] << 8  |
				   value->h_source[5],
				   lower_temp_mask, RQFCR_PID_SAL, tab);
	पूर्ण
	/* Destination address */
	अगर (!is_broadcast_ether_addr(mask->h_dest)) अणु
		/* Special क्रम destination is limited broadcast */
		अगर ((is_broadcast_ether_addr(value->h_dest) &&
		    is_zero_ether_addr(mask->h_dest))) अणु
			gfar_set_parse_bits(RQFPR_EBC, RQFPR_EBC, tab);
		पूर्ण अन्यथा अणु
			अगर (is_zero_ether_addr(mask->h_dest)) अणु
				upper_temp_mask = 0xFFFFFFFF;
				lower_temp_mask = 0xFFFFFFFF;
			पूर्ण अन्यथा अणु
				upper_temp_mask = mask->h_dest[0] << 16 |
						  mask->h_dest[1] << 8  |
						  mask->h_dest[2];
				lower_temp_mask = mask->h_dest[3] << 16 |
						  mask->h_dest[4] << 8  |
						  mask->h_dest[5];
			पूर्ण

			/* Upper 24bit */
			gfar_set_attribute(value->h_dest[0] << 16 |
					   value->h_dest[1] << 8  |
					   value->h_dest[2],
					   upper_temp_mask, RQFCR_PID_DAH, tab);
			/* And the same क्रम the lower part */
			gfar_set_attribute(value->h_dest[3] << 16 |
					   value->h_dest[4] << 8  |
					   value->h_dest[5],
					   lower_temp_mask, RQFCR_PID_DAL, tab);
		पूर्ण
	पूर्ण

	gfar_set_attribute(be16_to_cpu(value->h_proto),
			   be16_to_cpu(mask->h_proto),
			   RQFCR_PID_ETY, tab);
पूर्ण

अटल अंतरभूत u32 vlan_tci_vid(काष्ठा ethtool_rx_flow_spec *rule)
अणु
	वापस be16_to_cpu(rule->h_ext.vlan_tci) & VLAN_VID_MASK;
पूर्ण

अटल अंतरभूत u32 vlan_tci_vidm(काष्ठा ethtool_rx_flow_spec *rule)
अणु
	वापस be16_to_cpu(rule->m_ext.vlan_tci) & VLAN_VID_MASK;
पूर्ण

अटल अंतरभूत u32 vlan_tci_cfi(काष्ठा ethtool_rx_flow_spec *rule)
अणु
	वापस be16_to_cpu(rule->h_ext.vlan_tci) & VLAN_CFI_MASK;
पूर्ण

अटल अंतरभूत u32 vlan_tci_cfim(काष्ठा ethtool_rx_flow_spec *rule)
अणु
	वापस be16_to_cpu(rule->m_ext.vlan_tci) & VLAN_CFI_MASK;
पूर्ण

अटल अंतरभूत u32 vlan_tci_prio(काष्ठा ethtool_rx_flow_spec *rule)
अणु
	वापस (be16_to_cpu(rule->h_ext.vlan_tci) & VLAN_PRIO_MASK) >>
		VLAN_PRIO_SHIFT;
पूर्ण

अटल अंतरभूत u32 vlan_tci_priom(काष्ठा ethtool_rx_flow_spec *rule)
अणु
	वापस (be16_to_cpu(rule->m_ext.vlan_tci) & VLAN_PRIO_MASK) >>
		VLAN_PRIO_SHIFT;
पूर्ण

/* Convert a rule to binary filter क्रमmat of gianfar */
अटल पूर्णांक gfar_convert_to_filer(काष्ठा ethtool_rx_flow_spec *rule,
				 काष्ठा filer_table *tab)
अणु
	u32 vlan = 0, vlan_mask = 0;
	u32 id = 0, id_mask = 0;
	u32 cfi = 0, cfi_mask = 0;
	u32 prio = 0, prio_mask = 0;
	u32 old_index = tab->index;

	/* Check अगर vlan is wanted */
	अगर ((rule->flow_type & FLOW_EXT) &&
	    (rule->m_ext.vlan_tci != cpu_to_be16(0xFFFF))) अणु
		अगर (!rule->m_ext.vlan_tci)
			rule->m_ext.vlan_tci = cpu_to_be16(0xFFFF);

		vlan = RQFPR_VLN;
		vlan_mask = RQFPR_VLN;

		/* Separate the fields */
		id = vlan_tci_vid(rule);
		id_mask = vlan_tci_vidm(rule);
		cfi = vlan_tci_cfi(rule);
		cfi_mask = vlan_tci_cfim(rule);
		prio = vlan_tci_prio(rule);
		prio_mask = vlan_tci_priom(rule);

		अगर (cfi_mask) अणु
			अगर (cfi)
				vlan |= RQFPR_CFI;
			vlan_mask |= RQFPR_CFI;
		पूर्ण
	पूर्ण

	चयन (rule->flow_type & ~FLOW_EXT) अणु
	हाल TCP_V4_FLOW:
		gfar_set_parse_bits(RQFPR_IPV4 | RQFPR_TCP | vlan,
				    RQFPR_IPV4 | RQFPR_TCP | vlan_mask, tab);
		gfar_set_basic_ip(&rule->h_u.tcp_ip4_spec,
				  &rule->m_u.tcp_ip4_spec, tab);
		अवरोध;
	हाल UDP_V4_FLOW:
		gfar_set_parse_bits(RQFPR_IPV4 | RQFPR_UDP | vlan,
				    RQFPR_IPV4 | RQFPR_UDP | vlan_mask, tab);
		gfar_set_basic_ip(&rule->h_u.udp_ip4_spec,
				  &rule->m_u.udp_ip4_spec, tab);
		अवरोध;
	हाल SCTP_V4_FLOW:
		gfar_set_parse_bits(RQFPR_IPV4 | vlan, RQFPR_IPV4 | vlan_mask,
				    tab);
		gfar_set_attribute(132, 0, RQFCR_PID_L4P, tab);
		gfar_set_basic_ip((काष्ठा ethtool_tcpip4_spec *)&rule->h_u,
				  (काष्ठा ethtool_tcpip4_spec *)&rule->m_u,
				  tab);
		अवरोध;
	हाल IP_USER_FLOW:
		gfar_set_parse_bits(RQFPR_IPV4 | vlan, RQFPR_IPV4 | vlan_mask,
				    tab);
		gfar_set_user_ip((काष्ठा ethtool_usrip4_spec *) &rule->h_u,
				 (काष्ठा ethtool_usrip4_spec *) &rule->m_u,
				 tab);
		अवरोध;
	हाल ETHER_FLOW:
		अगर (vlan)
			gfar_set_parse_bits(vlan, vlan_mask, tab);
		gfar_set_ether((काष्ठा ethhdr *) &rule->h_u,
			       (काष्ठा ethhdr *) &rule->m_u, tab);
		अवरोध;
	शेष:
		वापस -1;
	पूर्ण

	/* Set the vlan attributes in the end */
	अगर (vlan) अणु
		gfar_set_attribute(id, id_mask, RQFCR_PID_VID, tab);
		gfar_set_attribute(prio, prio_mask, RQFCR_PID_PRI, tab);
	पूर्ण

	/* If there has been nothing written till now, it must be a शेष */
	अगर (tab->index == old_index) अणु
		gfar_set_mask(0xFFFFFFFF, tab);
		tab->fe[tab->index].ctrl = 0x20;
		tab->fe[tab->index].prop = 0x0;
		tab->index++;
	पूर्ण

	/* Remove last AND */
	tab->fe[tab->index - 1].ctrl &= (~RQFCR_AND);

	/* Specअगरy which queue to use or to drop */
	अगर (rule->ring_cookie == RX_CLS_FLOW_DISC)
		tab->fe[tab->index - 1].ctrl |= RQFCR_RJE;
	अन्यथा
		tab->fe[tab->index - 1].ctrl |= (rule->ring_cookie << 10);

	/* Only big enough entries can be clustered */
	अगर (tab->index > (old_index + 2)) अणु
		tab->fe[old_index + 1].ctrl |= RQFCR_CLE;
		tab->fe[tab->index - 1].ctrl |= RQFCR_CLE;
	पूर्ण

	/* In rare हालs the cache can be full जबतक there is
	 * मुक्त space in hw
	 */
	अगर (tab->index > MAX_खाताR_CACHE_IDX - 1)
		वापस -EBUSY;

	वापस 0;
पूर्ण

/* Write the bit-pattern from software's buffer to hardware रेजिस्टरs */
अटल पूर्णांक gfar_ग_लिखो_filer_table(काष्ठा gfar_निजी *priv,
				  काष्ठा filer_table *tab)
अणु
	u32 i = 0;
	अगर (tab->index > MAX_खाताR_IDX - 1)
		वापस -EBUSY;

	/* Fill regular entries */
	क्रम (; i < MAX_खाताR_IDX && (tab->fe[i].ctrl | tab->fe[i].prop); i++)
		gfar_ग_लिखो_filer(priv, i, tab->fe[i].ctrl, tab->fe[i].prop);
	/* Fill the rest with fall-troughs */
	क्रम (; i < MAX_खाताR_IDX; i++)
		gfar_ग_लिखो_filer(priv, i, 0x60, 0xFFFFFFFF);
	/* Last entry must be शेष accept
	 * because that's what people expect
	 */
	gfar_ग_लिखो_filer(priv, i, 0x20, 0x0);

	वापस 0;
पूर्ण

अटल पूर्णांक gfar_check_capability(काष्ठा ethtool_rx_flow_spec *flow,
				 काष्ठा gfar_निजी *priv)
अणु

	अगर (flow->flow_type & FLOW_EXT)	अणु
		अगर (~flow->m_ext.data[0] || ~flow->m_ext.data[1])
			netdev_warn(priv->ndev,
				    "User-specific data not supported!\n");
		अगर (~flow->m_ext.vlan_etype)
			netdev_warn(priv->ndev,
				    "VLAN-etype not supported!\n");
	पूर्ण
	अगर (flow->flow_type == IP_USER_FLOW)
		अगर (flow->h_u.usr_ip4_spec.ip_ver != ETH_RX_NFC_IP4)
			netdev_warn(priv->ndev,
				    "IP-Version differing from IPv4 not supported!\n");

	वापस 0;
पूर्ण

अटल पूर्णांक gfar_process_filer_changes(काष्ठा gfar_निजी *priv)
अणु
	काष्ठा ethtool_flow_spec_container *j;
	काष्ठा filer_table *tab;
	s32 ret = 0;

	/* So index is set to zero, too! */
	tab = kzalloc(माप(*tab), GFP_KERNEL);
	अगर (tab == शून्य)
		वापस -ENOMEM;

	/* Now convert the existing filer data from flow_spec पूर्णांकo
	 * filer tables binary क्रमmat
	 */
	list_क्रम_each_entry(j, &priv->rx_list.list, list) अणु
		ret = gfar_convert_to_filer(&j->fs, tab);
		अगर (ret == -EBUSY) अणु
			netdev_err(priv->ndev,
				   "Rule not added: No free space!\n");
			जाओ end;
		पूर्ण
		अगर (ret == -1) अणु
			netdev_err(priv->ndev,
				   "Rule not added: Unsupported Flow-type!\n");
			जाओ end;
		पूर्ण
	पूर्ण

	/* Write everything to hardware */
	ret = gfar_ग_लिखो_filer_table(priv, tab);
	अगर (ret == -EBUSY) अणु
		netdev_err(priv->ndev, "Rule not added: No free space!\n");
		जाओ end;
	पूर्ण

end:
	kमुक्त(tab);
	वापस ret;
पूर्ण

अटल व्योम gfar_invert_masks(काष्ठा ethtool_rx_flow_spec *flow)
अणु
	u32 i = 0;

	क्रम (i = 0; i < माप(flow->m_u); i++)
		flow->m_u.hdata[i] ^= 0xFF;

	flow->m_ext.vlan_etype ^= cpu_to_be16(0xFFFF);
	flow->m_ext.vlan_tci ^= cpu_to_be16(0xFFFF);
	flow->m_ext.data[0] ^= cpu_to_be32(~0);
	flow->m_ext.data[1] ^= cpu_to_be32(~0);
पूर्ण

अटल पूर्णांक gfar_add_cls(काष्ठा gfar_निजी *priv,
			काष्ठा ethtool_rx_flow_spec *flow)
अणु
	काष्ठा ethtool_flow_spec_container *temp, *comp;
	पूर्णांक ret = 0;

	temp = kदो_स्मृति(माप(*temp), GFP_KERNEL);
	अगर (temp == शून्य)
		वापस -ENOMEM;
	स_नकल(&temp->fs, flow, माप(temp->fs));

	gfar_invert_masks(&temp->fs);
	ret = gfar_check_capability(&temp->fs, priv);
	अगर (ret)
		जाओ clean_mem;
	/* Link in the new element at the right @location */
	अगर (list_empty(&priv->rx_list.list)) अणु
		ret = gfar_check_filer_hardware(priv);
		अगर (ret != 0)
			जाओ clean_mem;
		list_add(&temp->list, &priv->rx_list.list);
		जाओ process;
	पूर्ण अन्यथा अणु
		list_क्रम_each_entry(comp, &priv->rx_list.list, list) अणु
			अगर (comp->fs.location > flow->location) अणु
				list_add_tail(&temp->list, &comp->list);
				जाओ process;
			पूर्ण
			अगर (comp->fs.location == flow->location) अणु
				netdev_err(priv->ndev,
					   "Rule not added: ID %d not free!\n",
					   flow->location);
				ret = -EBUSY;
				जाओ clean_mem;
			पूर्ण
		पूर्ण
		list_add_tail(&temp->list, &priv->rx_list.list);
	पूर्ण

process:
	priv->rx_list.count++;
	ret = gfar_process_filer_changes(priv);
	अगर (ret)
		जाओ clean_list;
	वापस ret;

clean_list:
	priv->rx_list.count--;
	list_del(&temp->list);
clean_mem:
	kमुक्त(temp);
	वापस ret;
पूर्ण

अटल पूर्णांक gfar_del_cls(काष्ठा gfar_निजी *priv, u32 loc)
अणु
	काष्ठा ethtool_flow_spec_container *comp;
	u32 ret = -EINVAL;

	अगर (list_empty(&priv->rx_list.list))
		वापस ret;

	list_क्रम_each_entry(comp, &priv->rx_list.list, list) अणु
		अगर (comp->fs.location == loc) अणु
			list_del(&comp->list);
			kमुक्त(comp);
			priv->rx_list.count--;
			gfar_process_filer_changes(priv);
			ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक gfar_get_cls(काष्ठा gfar_निजी *priv, काष्ठा ethtool_rxnfc *cmd)
अणु
	काष्ठा ethtool_flow_spec_container *comp;
	u32 ret = -EINVAL;

	list_क्रम_each_entry(comp, &priv->rx_list.list, list) अणु
		अगर (comp->fs.location == cmd->fs.location) अणु
			स_नकल(&cmd->fs, &comp->fs, माप(cmd->fs));
			gfar_invert_masks(&cmd->fs);
			ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक gfar_get_cls_all(काष्ठा gfar_निजी *priv,
			    काष्ठा ethtool_rxnfc *cmd, u32 *rule_locs)
अणु
	काष्ठा ethtool_flow_spec_container *comp;
	u32 i = 0;

	list_क्रम_each_entry(comp, &priv->rx_list.list, list) अणु
		अगर (i == cmd->rule_cnt)
			वापस -EMSGSIZE;
		rule_locs[i] = comp->fs.location;
		i++;
	पूर्ण

	cmd->data = MAX_खाताR_IDX;
	cmd->rule_cnt = i;

	वापस 0;
पूर्ण

अटल पूर्णांक gfar_set_nfc(काष्ठा net_device *dev, काष्ठा ethtool_rxnfc *cmd)
अणु
	काष्ठा gfar_निजी *priv = netdev_priv(dev);
	पूर्णांक ret = 0;

	अगर (test_bit(GFAR_RESETTING, &priv->state))
		वापस -EBUSY;

	mutex_lock(&priv->rx_queue_access);

	चयन (cmd->cmd) अणु
	हाल ETHTOOL_SRXFH:
		ret = gfar_set_hash_opts(priv, cmd);
		अवरोध;
	हाल ETHTOOL_SRXCLSRLINS:
		अगर ((cmd->fs.ring_cookie != RX_CLS_FLOW_DISC &&
		     cmd->fs.ring_cookie >= priv->num_rx_queues) ||
		    cmd->fs.location >= MAX_खाताR_IDX) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		ret = gfar_add_cls(priv, &cmd->fs);
		अवरोध;
	हाल ETHTOOL_SRXCLSRLDEL:
		ret = gfar_del_cls(priv, cmd->fs.location);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	mutex_unlock(&priv->rx_queue_access);

	वापस ret;
पूर्ण

अटल पूर्णांक gfar_get_nfc(काष्ठा net_device *dev, काष्ठा ethtool_rxnfc *cmd,
			u32 *rule_locs)
अणु
	काष्ठा gfar_निजी *priv = netdev_priv(dev);
	पूर्णांक ret = 0;

	चयन (cmd->cmd) अणु
	हाल ETHTOOL_GRXRINGS:
		cmd->data = priv->num_rx_queues;
		अवरोध;
	हाल ETHTOOL_GRXCLSRLCNT:
		cmd->rule_cnt = priv->rx_list.count;
		अवरोध;
	हाल ETHTOOL_GRXCLSRULE:
		ret = gfar_get_cls(priv, cmd);
		अवरोध;
	हाल ETHTOOL_GRXCLSRLALL:
		ret = gfar_get_cls_all(priv, cmd, rule_locs);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक gfar_get_ts_info(काष्ठा net_device *dev,
			    काष्ठा ethtool_ts_info *info)
अणु
	काष्ठा gfar_निजी *priv = netdev_priv(dev);
	काष्ठा platक्रमm_device *ptp_dev;
	काष्ठा device_node *ptp_node;
	काष्ठा ptp_qoriq *ptp = शून्य;

	info->phc_index = -1;

	अगर (!(priv->device_flags & FSL_GIANFAR_DEV_HAS_TIMER)) अणु
		info->so_बारtamping = SOF_TIMESTAMPING_RX_SOFTWARE |
					SOF_TIMESTAMPING_SOFTWARE;
		वापस 0;
	पूर्ण

	ptp_node = of_find_compatible_node(शून्य, शून्य, "fsl,etsec-ptp");
	अगर (ptp_node) अणु
		ptp_dev = of_find_device_by_node(ptp_node);
		अगर (ptp_dev)
			ptp = platक्रमm_get_drvdata(ptp_dev);
	पूर्ण

	अगर (ptp)
		info->phc_index = ptp->phc_index;

	info->so_बारtamping = SOF_TIMESTAMPING_TX_HARDWARE |
				SOF_TIMESTAMPING_RX_HARDWARE |
				SOF_TIMESTAMPING_RAW_HARDWARE;
	info->tx_types = (1 << HWTSTAMP_TX_OFF) |
			 (1 << HWTSTAMP_TX_ON);
	info->rx_filters = (1 << HWTSTAMP_FILTER_NONE) |
			   (1 << HWTSTAMP_FILTER_ALL);
	वापस 0;
पूर्ण

स्थिर काष्ठा ethtool_ops gfar_ethtool_ops = अणु
	.supported_coalesce_params = ETHTOOL_COALESCE_USECS |
				     ETHTOOL_COALESCE_MAX_FRAMES,
	.get_drvinfo = gfar_gdrvinfo,
	.get_regs_len = gfar_reglen,
	.get_regs = gfar_get_regs,
	.get_link = ethtool_op_get_link,
	.get_coalesce = gfar_gcoalesce,
	.set_coalesce = gfar_scoalesce,
	.get_ringparam = gfar_gringparam,
	.set_ringparam = gfar_sringparam,
	.get_छोड़ोparam = gfar_gछोड़ोparam,
	.set_छोड़ोparam = gfar_sछोड़ोparam,
	.get_strings = gfar_gstrings,
	.get_sset_count = gfar_sset_count,
	.get_ethtool_stats = gfar_fill_stats,
	.get_msglevel = gfar_get_msglevel,
	.set_msglevel = gfar_set_msglevel,
#अगर_घोषित CONFIG_PM
	.get_wol = gfar_get_wol,
	.set_wol = gfar_set_wol,
#पूर्ण_अगर
	.set_rxnfc = gfar_set_nfc,
	.get_rxnfc = gfar_get_nfc,
	.get_ts_info = gfar_get_ts_info,
	.get_link_ksettings = phy_ethtool_get_link_ksettings,
	.set_link_ksettings = phy_ethtool_set_link_ksettings,
पूर्ण;
