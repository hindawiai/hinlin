<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (c) 2007 Freescale Semiconductor, Inc. All rights reserved.
 *
 * Description: QE UCC Gigabit Ethernet Ethtool API Set
 *
 * Author: Li Yang <leoli@मुक्तscale.com>
 *
 * Limitation:
 * Can only get/set settings of the first queue.
 * Need to re-खोलो the पूर्णांकerface manually after changing some parameters.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/mm.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/mii.h>
#समावेश <linux/phy.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/types.h>

#समावेश "ucc_geth.h"

अटल स्थिर अक्षर hw_stat_gstrings[][ETH_GSTRING_LEN] = अणु
	"tx-64-frames",
	"tx-65-127-frames",
	"tx-128-255-frames",
	"rx-64-frames",
	"rx-65-127-frames",
	"rx-128-255-frames",
	"tx-bytes-ok",
	"tx-pause-frames",
	"tx-multicast-frames",
	"tx-broadcast-frames",
	"rx-frames",
	"rx-bytes-ok",
	"rx-bytes-all",
	"rx-multicast-frames",
	"rx-broadcast-frames",
	"stats-counter-carry",
	"stats-counter-mask",
	"rx-dropped-frames",
पूर्ण;

अटल स्थिर अक्षर tx_fw_stat_gstrings[][ETH_GSTRING_LEN] = अणु
	"tx-single-collision",
	"tx-multiple-collision",
	"tx-late-collision",
	"tx-aborted-frames",
	"tx-lost-frames",
	"tx-carrier-sense-errors",
	"tx-frames-ok",
	"tx-excessive-differ-frames",
	"tx-256-511-frames",
	"tx-512-1023-frames",
	"tx-1024-1518-frames",
	"tx-jumbo-frames",
पूर्ण;

अटल स्थिर अक्षर rx_fw_stat_gstrings[][ETH_GSTRING_LEN] = अणु
	"rx-crc-errors",
	"rx-alignment-errors",
	"rx-in-range-length-errors",
	"rx-out-of-range-length-errors",
	"rx-too-long-frames",
	"rx-runt",
	"rx-very-long-event",
	"rx-symbol-errors",
	"rx-busy-drop-frames",
	"reserved",
	"reserved",
	"rx-mismatch-drop-frames",
	"rx-small-than-64",
	"rx-256-511-frames",
	"rx-512-1023-frames",
	"rx-1024-1518-frames",
	"rx-jumbo-frames",
	"rx-mac-error-loss",
	"rx-pause-frames",
	"reserved",
	"rx-vlan-removed",
	"rx-vlan-replaced",
	"rx-vlan-inserted",
	"rx-ip-checksum-errors",
पूर्ण;

#घोषणा UEC_HW_STATS_LEN ARRAY_SIZE(hw_stat_gstrings)
#घोषणा UEC_TX_FW_STATS_LEN ARRAY_SIZE(tx_fw_stat_gstrings)
#घोषणा UEC_RX_FW_STATS_LEN ARRAY_SIZE(rx_fw_stat_gstrings)

अटल पूर्णांक
uec_get_ksettings(काष्ठा net_device *netdev, काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा ucc_geth_निजी *ugeth = netdev_priv(netdev);
	काष्ठा phy_device *phydev = ugeth->phydev;

	अगर (!phydev)
		वापस -ENODEV;

	phy_ethtool_ksettings_get(phydev, cmd);

	वापस 0;
पूर्ण

अटल पूर्णांक
uec_set_ksettings(काष्ठा net_device *netdev,
		  स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा ucc_geth_निजी *ugeth = netdev_priv(netdev);
	काष्ठा phy_device *phydev = ugeth->phydev;

	अगर (!phydev)
		वापस -ENODEV;

	वापस phy_ethtool_ksettings_set(phydev, cmd);
पूर्ण

अटल व्योम
uec_get_छोड़ोparam(काष्ठा net_device *netdev,
                     काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
	काष्ठा ucc_geth_निजी *ugeth = netdev_priv(netdev);

	छोड़ो->स्वतःneg = ugeth->phydev->स्वतःneg;

	अगर (ugeth->ug_info->receiveFlowControl)
		छोड़ो->rx_छोड़ो = 1;
	अगर (ugeth->ug_info->transmitFlowControl)
		छोड़ो->tx_छोड़ो = 1;
पूर्ण

अटल पूर्णांक
uec_set_छोड़ोparam(काष्ठा net_device *netdev,
                     काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
	काष्ठा ucc_geth_निजी *ugeth = netdev_priv(netdev);
	पूर्णांक ret = 0;

	ugeth->ug_info->receiveFlowControl = छोड़ो->rx_छोड़ो;
	ugeth->ug_info->transmitFlowControl = छोड़ो->tx_छोड़ो;

	अगर (ugeth->phydev->स्वतःneg) अणु
		अगर (netअगर_running(netdev)) अणु
			/* FIXME: स्वतःmatically restart */
			netdev_info(netdev, "Please re-open the interface\n");
		पूर्ण
	पूर्ण अन्यथा अणु
		काष्ठा ucc_geth_info *ug_info = ugeth->ug_info;

		ret = init_flow_control_params(ug_info->aufc,
					ug_info->receiveFlowControl,
					ug_info->transmitFlowControl,
					ug_info->छोड़ोPeriod,
					ug_info->extensionField,
					&ugeth->uccf->uf_regs->upsmr,
					&ugeth->ug_regs->uempr,
					&ugeth->ug_regs->maccfg1);
	पूर्ण

	वापस ret;
पूर्ण

अटल uपूर्णांक32_t
uec_get_msglevel(काष्ठा net_device *netdev)
अणु
	काष्ठा ucc_geth_निजी *ugeth = netdev_priv(netdev);
	वापस ugeth->msg_enable;
पूर्ण

अटल व्योम
uec_set_msglevel(काष्ठा net_device *netdev, uपूर्णांक32_t data)
अणु
	काष्ठा ucc_geth_निजी *ugeth = netdev_priv(netdev);
	ugeth->msg_enable = data;
पूर्ण

अटल पूर्णांक
uec_get_regs_len(काष्ठा net_device *netdev)
अणु
	वापस माप(काष्ठा ucc_geth);
पूर्ण

अटल व्योम
uec_get_regs(काष्ठा net_device *netdev,
               काष्ठा ethtool_regs *regs, व्योम *p)
अणु
	पूर्णांक i;
	काष्ठा ucc_geth_निजी *ugeth = netdev_priv(netdev);
	u32 __iomem *ug_regs = (u32 __iomem *)ugeth->ug_regs;
	u32 *buff = p;

	क्रम (i = 0; i < माप(काष्ठा ucc_geth) / माप(u32); i++)
		buff[i] = in_be32(&ug_regs[i]);
पूर्ण

अटल व्योम
uec_get_ringparam(काष्ठा net_device *netdev,
                    काष्ठा ethtool_ringparam *ring)
अणु
	काष्ठा ucc_geth_निजी *ugeth = netdev_priv(netdev);
	काष्ठा ucc_geth_info *ug_info = ugeth->ug_info;
	पूर्णांक queue = 0;

	ring->rx_max_pending = UCC_GETH_BD_RING_SIZE_MAX;
	ring->rx_mini_max_pending = UCC_GETH_BD_RING_SIZE_MAX;
	ring->rx_jumbo_max_pending = UCC_GETH_BD_RING_SIZE_MAX;
	ring->tx_max_pending = UCC_GETH_BD_RING_SIZE_MAX;

	ring->rx_pending = ug_info->bdRingLenRx[queue];
	ring->rx_mini_pending = ug_info->bdRingLenRx[queue];
	ring->rx_jumbo_pending = ug_info->bdRingLenRx[queue];
	ring->tx_pending = ug_info->bdRingLenTx[queue];
पूर्ण

अटल पूर्णांक
uec_set_ringparam(काष्ठा net_device *netdev,
                    काष्ठा ethtool_ringparam *ring)
अणु
	काष्ठा ucc_geth_निजी *ugeth = netdev_priv(netdev);
	काष्ठा ucc_geth_info *ug_info = ugeth->ug_info;
	पूर्णांक queue = 0, ret = 0;

	अगर (ring->rx_pending < UCC_GETH_RX_BD_RING_SIZE_MIN) अणु
		netdev_info(netdev, "RxBD ring size must be no smaller than %d\n",
			    UCC_GETH_RX_BD_RING_SIZE_MIN);
		वापस -EINVAL;
	पूर्ण
	अगर (ring->rx_pending % UCC_GETH_RX_BD_RING_SIZE_ALIGNMENT) अणु
		netdev_info(netdev, "RxBD ring size must be multiple of %d\n",
			    UCC_GETH_RX_BD_RING_SIZE_ALIGNMENT);
		वापस -EINVAL;
	पूर्ण
	अगर (ring->tx_pending < UCC_GETH_TX_BD_RING_SIZE_MIN) अणु
		netdev_info(netdev, "TxBD ring size must be no smaller than %d\n",
			    UCC_GETH_TX_BD_RING_SIZE_MIN);
		वापस -EINVAL;
	पूर्ण

	अगर (netअगर_running(netdev))
		वापस -EBUSY;

	ug_info->bdRingLenRx[queue] = ring->rx_pending;
	ug_info->bdRingLenTx[queue] = ring->tx_pending;

	वापस ret;
पूर्ण

अटल पूर्णांक uec_get_sset_count(काष्ठा net_device *netdev, पूर्णांक sset)
अणु
	काष्ठा ucc_geth_निजी *ugeth = netdev_priv(netdev);
	u32 stats_mode = ugeth->ug_info->statisticsMode;
	पूर्णांक len = 0;

	चयन (sset) अणु
	हाल ETH_SS_STATS:
		अगर (stats_mode & UCC_GETH_STATISTICS_GATHERING_MODE_HARDWARE)
			len += UEC_HW_STATS_LEN;
		अगर (stats_mode & UCC_GETH_STATISTICS_GATHERING_MODE_FIRMWARE_TX)
			len += UEC_TX_FW_STATS_LEN;
		अगर (stats_mode & UCC_GETH_STATISTICS_GATHERING_MODE_FIRMWARE_RX)
			len += UEC_RX_FW_STATS_LEN;

		वापस len;

	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल व्योम uec_get_strings(काष्ठा net_device *netdev, u32 stringset, u8 *buf)
अणु
	काष्ठा ucc_geth_निजी *ugeth = netdev_priv(netdev);
	u32 stats_mode = ugeth->ug_info->statisticsMode;

	अगर (stats_mode & UCC_GETH_STATISTICS_GATHERING_MODE_HARDWARE) अणु
		स_नकल(buf, hw_stat_gstrings, UEC_HW_STATS_LEN *
			       	ETH_GSTRING_LEN);
		buf += UEC_HW_STATS_LEN * ETH_GSTRING_LEN;
	पूर्ण
	अगर (stats_mode & UCC_GETH_STATISTICS_GATHERING_MODE_FIRMWARE_TX) अणु
		स_नकल(buf, tx_fw_stat_gstrings, UEC_TX_FW_STATS_LEN *
			       	ETH_GSTRING_LEN);
		buf += UEC_TX_FW_STATS_LEN * ETH_GSTRING_LEN;
	पूर्ण
	अगर (stats_mode & UCC_GETH_STATISTICS_GATHERING_MODE_FIRMWARE_RX)
		स_नकल(buf, rx_fw_stat_gstrings, UEC_RX_FW_STATS_LEN *
			       	ETH_GSTRING_LEN);
पूर्ण

अटल व्योम uec_get_ethtool_stats(काष्ठा net_device *netdev,
		काष्ठा ethtool_stats *stats, uपूर्णांक64_t *data)
अणु
	काष्ठा ucc_geth_निजी *ugeth = netdev_priv(netdev);
	u32 stats_mode = ugeth->ug_info->statisticsMode;
	u32 __iomem *base;
	पूर्णांक i, j = 0;

	अगर (stats_mode & UCC_GETH_STATISTICS_GATHERING_MODE_HARDWARE) अणु
		अगर (ugeth->ug_regs)
			base = (u32 __iomem *)&ugeth->ug_regs->tx64;
		अन्यथा
			base = शून्य;

		क्रम (i = 0; i < UEC_HW_STATS_LEN; i++)
			data[j++] = base ? in_be32(&base[i]) : 0;
	पूर्ण
	अगर (stats_mode & UCC_GETH_STATISTICS_GATHERING_MODE_FIRMWARE_TX) अणु
		base = (u32 __iomem *)ugeth->p_tx_fw_statistics_pram;
		क्रम (i = 0; i < UEC_TX_FW_STATS_LEN; i++)
			data[j++] = base ? in_be32(&base[i]) : 0;
	पूर्ण
	अगर (stats_mode & UCC_GETH_STATISTICS_GATHERING_MODE_FIRMWARE_RX) अणु
		base = (u32 __iomem *)ugeth->p_rx_fw_statistics_pram;
		क्रम (i = 0; i < UEC_RX_FW_STATS_LEN; i++)
			data[j++] = base ? in_be32(&base[i]) : 0;
	पूर्ण
पूर्ण

/* Report driver inक्रमmation */
अटल व्योम
uec_get_drvinfo(काष्ठा net_device *netdev,
                       काष्ठा ethtool_drvinfo *drvinfo)
अणु
	strlcpy(drvinfo->driver, DRV_NAME, माप(drvinfo->driver));
	strlcpy(drvinfo->bus_info, "QUICC ENGINE", माप(drvinfo->bus_info));
पूर्ण

#अगर_घोषित CONFIG_PM

अटल व्योम uec_get_wol(काष्ठा net_device *netdev, काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा ucc_geth_निजी *ugeth = netdev_priv(netdev);
	काष्ठा phy_device *phydev = ugeth->phydev;

	अगर (phydev && phydev->irq)
		wol->supported |= WAKE_PHY;
	अगर (qe_alive_during_sleep())
		wol->supported |= WAKE_MAGIC;

	wol->wolopts = ugeth->wol_en;
पूर्ण

अटल पूर्णांक uec_set_wol(काष्ठा net_device *netdev, काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा ucc_geth_निजी *ugeth = netdev_priv(netdev);
	काष्ठा phy_device *phydev = ugeth->phydev;

	अगर (wol->wolopts & ~(WAKE_PHY | WAKE_MAGIC))
		वापस -EINVAL;
	अन्यथा अगर (wol->wolopts & WAKE_PHY && (!phydev || !phydev->irq))
		वापस -EINVAL;
	अन्यथा अगर (wol->wolopts & WAKE_MAGIC && !qe_alive_during_sleep())
		वापस -EINVAL;

	ugeth->wol_en = wol->wolopts;
	device_set_wakeup_enable(&netdev->dev, ugeth->wol_en);

	वापस 0;
पूर्ण

#अन्यथा
#घोषणा uec_get_wol शून्य
#घोषणा uec_set_wol शून्य
#पूर्ण_अगर /* CONFIG_PM */

अटल स्थिर काष्ठा ethtool_ops uec_ethtool_ops = अणु
	.get_drvinfo            = uec_get_drvinfo,
	.get_regs_len           = uec_get_regs_len,
	.get_regs               = uec_get_regs,
	.get_msglevel           = uec_get_msglevel,
	.set_msglevel           = uec_set_msglevel,
	.nway_reset             = phy_ethtool_nway_reset,
	.get_link               = ethtool_op_get_link,
	.get_ringparam          = uec_get_ringparam,
	.set_ringparam          = uec_set_ringparam,
	.get_छोड़ोparam         = uec_get_छोड़ोparam,
	.set_छोड़ोparam         = uec_set_छोड़ोparam,
	.get_sset_count		= uec_get_sset_count,
	.get_strings            = uec_get_strings,
	.get_ethtool_stats      = uec_get_ethtool_stats,
	.get_wol		= uec_get_wol,
	.set_wol		= uec_set_wol,
	.get_ts_info		= ethtool_op_get_ts_info,
	.get_link_ksettings	= uec_get_ksettings,
	.set_link_ksettings	= uec_set_ksettings,
पूर्ण;

व्योम uec_set_ethtool_ops(काष्ठा net_device *netdev)
अणु
	netdev->ethtool_ops = &uec_ethtool_ops;
पूर्ण
