<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Applied Micro X-Gene SoC Ethernet Driver
 *
 * Copyright (c) 2014, Applied Micro Circuits Corporation
 * Authors: Iyappan Subramanian <isubramanian@apm.com>
 */

#समावेश <linux/ethtool.h>
#समावेश "xgene_enet_main.h"

काष्ठा xgene_gstrings_stats अणु
	अक्षर name[ETH_GSTRING_LEN];
	पूर्णांक offset;
	u32 addr;
	u32 mask;
पूर्ण;

#घोषणा XGENE_STAT(m) अणु #m, दुरत्व(काष्ठा rtnl_link_stats64, m) पूर्ण
#घोषणा XGENE_EXTD_STAT(s, a, m)		\
		अणु			\
		.name = #s,		\
		.addr = a ## _ADDR,	\
		.mask = m		\
		पूर्ण

अटल स्थिर काष्ठा xgene_gstrings_stats gstrings_stats[] = अणु
	XGENE_STAT(rx_packets),
	XGENE_STAT(tx_packets),
	XGENE_STAT(rx_bytes),
	XGENE_STAT(tx_bytes),
	XGENE_STAT(rx_errors),
	XGENE_STAT(tx_errors),
	XGENE_STAT(rx_length_errors),
	XGENE_STAT(rx_crc_errors),
	XGENE_STAT(rx_frame_errors),
	XGENE_STAT(rx_fअगरo_errors)
पूर्ण;

अटल स्थिर काष्ठा xgene_gstrings_stats gstrings_extd_stats[] = अणु
	XGENE_EXTD_STAT(tx_rx_64b_frame_cntr, TR64, 31),
	XGENE_EXTD_STAT(tx_rx_127b_frame_cntr, TR127, 31),
	XGENE_EXTD_STAT(tx_rx_255b_frame_cntr, TR255, 31),
	XGENE_EXTD_STAT(tx_rx_511b_frame_cntr, TR511, 31),
	XGENE_EXTD_STAT(tx_rx_1023b_frame_cntr, TR1K, 31),
	XGENE_EXTD_STAT(tx_rx_1518b_frame_cntr, TRMAX, 31),
	XGENE_EXTD_STAT(tx_rx_1522b_frame_cntr, TRMGV, 31),
	XGENE_EXTD_STAT(rx_fcs_error_cntr, RFCS, 16),
	XGENE_EXTD_STAT(rx_multicast_pkt_cntr, RMCA, 31),
	XGENE_EXTD_STAT(rx_broadcast_pkt_cntr, RBCA, 31),
	XGENE_EXTD_STAT(rx_ctrl_frame_pkt_cntr, RXCF, 16),
	XGENE_EXTD_STAT(rx_छोड़ो_frame_pkt_cntr, RXPF, 16),
	XGENE_EXTD_STAT(rx_unk_opcode_cntr, RXUO, 16),
	XGENE_EXTD_STAT(rx_align_err_cntr, RALN, 16),
	XGENE_EXTD_STAT(rx_frame_len_err_cntr, RFLR, 16),
	XGENE_EXTD_STAT(rx_frame_len_err_recov_cntr, DUMP, 0),
	XGENE_EXTD_STAT(rx_code_err_cntr, RCDE, 16),
	XGENE_EXTD_STAT(rx_carrier_sense_err_cntr, RCSE, 16),
	XGENE_EXTD_STAT(rx_undersize_pkt_cntr, RUND, 16),
	XGENE_EXTD_STAT(rx_oversize_pkt_cntr, ROVR, 16),
	XGENE_EXTD_STAT(rx_fragments_cntr, RFRG, 16),
	XGENE_EXTD_STAT(rx_jabber_cntr, RJBR, 16),
	XGENE_EXTD_STAT(rx_jabber_recov_cntr, DUMP, 0),
	XGENE_EXTD_STAT(rx_dropped_pkt_cntr, RDRP, 16),
	XGENE_EXTD_STAT(rx_overrun_cntr, DUMP, 0),
	XGENE_EXTD_STAT(tx_multicast_pkt_cntr, TMCA, 31),
	XGENE_EXTD_STAT(tx_broadcast_pkt_cntr, TBCA, 31),
	XGENE_EXTD_STAT(tx_छोड़ो_ctrl_frame_cntr, TXPF, 16),
	XGENE_EXTD_STAT(tx_defer_pkt_cntr, TDFR, 31),
	XGENE_EXTD_STAT(tx_excv_defer_pkt_cntr, TEDF, 31),
	XGENE_EXTD_STAT(tx_single_col_pkt_cntr, TSCL, 31),
	XGENE_EXTD_STAT(tx_multi_col_pkt_cntr, TMCL, 31),
	XGENE_EXTD_STAT(tx_late_col_pkt_cntr, TLCL, 31),
	XGENE_EXTD_STAT(tx_excv_col_pkt_cntr, TXCL, 31),
	XGENE_EXTD_STAT(tx_total_col_cntr, TNCL, 31),
	XGENE_EXTD_STAT(tx_छोड़ो_frames_hnrd_cntr, TPFH, 16),
	XGENE_EXTD_STAT(tx_drop_frame_cntr, TDRP, 16),
	XGENE_EXTD_STAT(tx_jabber_frame_cntr, TJBR, 12),
	XGENE_EXTD_STAT(tx_fcs_error_cntr, TFCS, 12),
	XGENE_EXTD_STAT(tx_ctrl_frame_cntr, TXCF, 12),
	XGENE_EXTD_STAT(tx_oversize_frame_cntr, TOVR, 12),
	XGENE_EXTD_STAT(tx_undersize_frame_cntr, TUND, 12),
	XGENE_EXTD_STAT(tx_fragments_cntr, TFRG, 12),
	XGENE_EXTD_STAT(tx_underrun_cntr, DUMP, 0)
पूर्ण;

#घोषणा XGENE_STATS_LEN		ARRAY_SIZE(gstrings_stats)
#घोषणा XGENE_EXTD_STATS_LEN	ARRAY_SIZE(gstrings_extd_stats)
#घोषणा RFCS_IDX		7
#घोषणा RALN_IDX		13
#घोषणा RFLR_IDX		14
#घोषणा FALSE_RFLR_IDX		15
#घोषणा RUND_IDX		18
#घोषणा FALSE_RJBR_IDX		22
#घोषणा RX_OVERRUN_IDX		24
#घोषणा TFCS_IDX		38
#घोषणा TFRG_IDX		42
#घोषणा TX_UNDERRUN_IDX		43

अटल व्योम xgene_get_drvinfo(काष्ठा net_device *ndev,
			      काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा xgene_enet_pdata *pdata = netdev_priv(ndev);
	काष्ठा platक्रमm_device *pdev = pdata->pdev;

	म_नकल(info->driver, "xgene_enet");
	प्र_लिखो(info->bus_info, "%s", pdev->name);
पूर्ण

अटल पूर्णांक xgene_get_link_ksettings(काष्ठा net_device *ndev,
				    काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा xgene_enet_pdata *pdata = netdev_priv(ndev);
	काष्ठा phy_device *phydev = ndev->phydev;
	u32 supported;

	अगर (phy_पूर्णांकerface_mode_is_rgmii(pdata->phy_mode)) अणु
		अगर (phydev == शून्य)
			वापस -ENODEV;

		phy_ethtool_ksettings_get(phydev, cmd);

		वापस 0;
	पूर्ण अन्यथा अगर (pdata->phy_mode == PHY_INTERFACE_MODE_SGMII) अणु
		अगर (pdata->mdio_driver) अणु
			अगर (!phydev)
				वापस -ENODEV;

			phy_ethtool_ksettings_get(phydev, cmd);

			वापस 0;
		पूर्ण

		supported = SUPPORTED_1000baseT_Full | SUPPORTED_Autoneg |
			SUPPORTED_MII;
		ethtool_convert_legacy_u32_to_link_mode(
			cmd->link_modes.supported,
			supported);
		ethtool_convert_legacy_u32_to_link_mode(
			cmd->link_modes.advertising,
			supported);

		cmd->base.speed = SPEED_1000;
		cmd->base.duplex = DUPLEX_FULL;
		cmd->base.port = PORT_MII;
		cmd->base.स्वतःneg = AUTONEG_ENABLE;
	पूर्ण अन्यथा अणु
		supported = SUPPORTED_10000baseT_Full | SUPPORTED_FIBRE;
		ethtool_convert_legacy_u32_to_link_mode(
			cmd->link_modes.supported,
			supported);
		ethtool_convert_legacy_u32_to_link_mode(
			cmd->link_modes.advertising,
			supported);

		cmd->base.speed = SPEED_10000;
		cmd->base.duplex = DUPLEX_FULL;
		cmd->base.port = PORT_FIBRE;
		cmd->base.स्वतःneg = AUTONEG_DISABLE;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक xgene_set_link_ksettings(काष्ठा net_device *ndev,
				    स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा xgene_enet_pdata *pdata = netdev_priv(ndev);
	काष्ठा phy_device *phydev = ndev->phydev;

	अगर (phy_पूर्णांकerface_mode_is_rgmii(pdata->phy_mode)) अणु
		अगर (!phydev)
			वापस -ENODEV;

		वापस phy_ethtool_ksettings_set(phydev, cmd);
	पूर्ण

	अगर (pdata->phy_mode == PHY_INTERFACE_MODE_SGMII) अणु
		अगर (pdata->mdio_driver) अणु
			अगर (!phydev)
				वापस -ENODEV;

			वापस phy_ethtool_ksettings_set(phydev, cmd);
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल व्योम xgene_get_strings(काष्ठा net_device *ndev, u32 stringset, u8 *data)
अणु
	पूर्णांक i;
	u8 *p = data;

	अगर (stringset != ETH_SS_STATS)
		वापस;

	क्रम (i = 0; i < XGENE_STATS_LEN; i++) अणु
		स_नकल(p, gstrings_stats[i].name, ETH_GSTRING_LEN);
		p += ETH_GSTRING_LEN;
	पूर्ण

	क्रम (i = 0; i < XGENE_EXTD_STATS_LEN; i++) अणु
		स_नकल(p, gstrings_extd_stats[i].name, ETH_GSTRING_LEN);
		p += ETH_GSTRING_LEN;
	पूर्ण
पूर्ण

अटल पूर्णांक xgene_get_sset_count(काष्ठा net_device *ndev, पूर्णांक sset)
अणु
	अगर (sset != ETH_SS_STATS)
		वापस -EINVAL;

	वापस XGENE_STATS_LEN + XGENE_EXTD_STATS_LEN;
पूर्ण

अटल व्योम xgene_get_extd_stats(काष्ठा xgene_enet_pdata *pdata)
अणु
	u32 rx_drop, tx_drop;
	u32 mask, पंचांगp;
	पूर्णांक i;

	क्रम (i = 0; i < XGENE_EXTD_STATS_LEN; i++) अणु
		पंचांगp = xgene_enet_rd_stat(pdata, gstrings_extd_stats[i].addr);
		अगर (gstrings_extd_stats[i].mask) अणु
			mask = GENMASK(gstrings_extd_stats[i].mask - 1, 0);
			pdata->extd_stats[i] += (पंचांगp & mask);
		पूर्ण
	पूर्ण

	अगर (pdata->phy_mode == PHY_INTERFACE_MODE_XGMII) अणु
		/* Errata 10GE_10 - SW should पूर्णांकepret RALN as 0 */
		pdata->extd_stats[RALN_IDX] = 0;
	पूर्ण अन्यथा अणु
		/* Errata ENET_15 - Fixes RFCS, RFLR, TFCS counter */
		pdata->extd_stats[RFCS_IDX] -= pdata->extd_stats[RALN_IDX];
		pdata->extd_stats[RFLR_IDX] -= pdata->extd_stats[RUND_IDX];
		pdata->extd_stats[TFCS_IDX] -= pdata->extd_stats[TFRG_IDX];
	पूर्ण

	pdata->mac_ops->get_drop_cnt(pdata, &rx_drop, &tx_drop);
	pdata->extd_stats[RX_OVERRUN_IDX] += rx_drop;
	pdata->extd_stats[TX_UNDERRUN_IDX] += tx_drop;

	/* Errata 10GE_8 -  Update Frame recovered from Errata 10GE_8/ENET_11 */
	pdata->extd_stats[FALSE_RFLR_IDX] = pdata->false_rflr;
	/* Errata ENET_15 - Jabber Frame recov'ed from Errata 10GE_10/ENET_15 */
	pdata->extd_stats[FALSE_RJBR_IDX] = pdata->vlan_rjbr;
पूर्ण

पूर्णांक xgene_extd_stats_init(काष्ठा xgene_enet_pdata *pdata)
अणु
	pdata->extd_stats = devm_kदो_स्मृति_array(&pdata->pdev->dev,
			XGENE_EXTD_STATS_LEN, माप(u64), GFP_KERNEL);
	अगर (!pdata->extd_stats)
		वापस -ENOMEM;

	xgene_get_extd_stats(pdata);
	स_रखो(pdata->extd_stats, 0, XGENE_EXTD_STATS_LEN * माप(u64));

	वापस 0;
पूर्ण

अटल व्योम xgene_get_ethtool_stats(काष्ठा net_device *ndev,
				    काष्ठा ethtool_stats *dummy,
				    u64 *data)
अणु
	काष्ठा xgene_enet_pdata *pdata = netdev_priv(ndev);
	काष्ठा rtnl_link_stats64 stats;
	पूर्णांक i;

	dev_get_stats(ndev, &stats);
	क्रम (i = 0; i < XGENE_STATS_LEN; i++)
		data[i] = *(u64 *)((अक्षर *)&stats + gstrings_stats[i].offset);

	xgene_get_extd_stats(pdata);
	क्रम (i = 0; i < XGENE_EXTD_STATS_LEN; i++)
		data[i + XGENE_STATS_LEN] = pdata->extd_stats[i];
पूर्ण

अटल व्योम xgene_get_छोड़ोparam(काष्ठा net_device *ndev,
				 काष्ठा ethtool_छोड़ोparam *pp)
अणु
	काष्ठा xgene_enet_pdata *pdata = netdev_priv(ndev);

	pp->स्वतःneg = pdata->छोड़ो_स्वतःneg;
	pp->tx_छोड़ो = pdata->tx_छोड़ो;
	pp->rx_छोड़ो = pdata->rx_छोड़ो;
पूर्ण

अटल पूर्णांक xgene_set_छोड़ोparam(काष्ठा net_device *ndev,
				काष्ठा ethtool_छोड़ोparam *pp)
अणु
	काष्ठा xgene_enet_pdata *pdata = netdev_priv(ndev);
	काष्ठा phy_device *phydev = ndev->phydev;

	अगर (phy_पूर्णांकerface_mode_is_rgmii(pdata->phy_mode) ||
	    pdata->phy_mode == PHY_INTERFACE_MODE_SGMII) अणु
		अगर (!phydev)
			वापस -EINVAL;

		अगर (!phy_validate_छोड़ो(phydev, pp))
			वापस -EINVAL;

		pdata->छोड़ो_स्वतःneg = pp->स्वतःneg;
		pdata->tx_छोड़ो = pp->tx_छोड़ो;
		pdata->rx_छोड़ो = pp->rx_छोड़ो;

		phy_set_asym_छोड़ो(phydev, pp->rx_छोड़ो,  pp->tx_छोड़ो);

		अगर (!pp->स्वतःneg) अणु
			pdata->mac_ops->flowctl_tx(pdata, pdata->tx_छोड़ो);
			pdata->mac_ops->flowctl_rx(pdata, pdata->rx_छोड़ो);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (pp->स्वतःneg)
			वापस -EINVAL;

		pdata->tx_छोड़ो = pp->tx_छोड़ो;
		pdata->rx_छोड़ो = pp->rx_छोड़ो;

		pdata->mac_ops->flowctl_tx(pdata, pdata->tx_छोड़ो);
		pdata->mac_ops->flowctl_rx(pdata, pdata->rx_छोड़ो);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops xgene_ethtool_ops = अणु
	.get_drvinfo = xgene_get_drvinfo,
	.get_link = ethtool_op_get_link,
	.get_strings = xgene_get_strings,
	.get_sset_count = xgene_get_sset_count,
	.get_ethtool_stats = xgene_get_ethtool_stats,
	.get_link_ksettings = xgene_get_link_ksettings,
	.set_link_ksettings = xgene_set_link_ksettings,
	.get_छोड़ोparam = xgene_get_छोड़ोparam,
	.set_छोड़ोparam = xgene_set_छोड़ोparam
पूर्ण;

व्योम xgene_enet_set_ethtool_ops(काष्ठा net_device *ndev)
अणु
	ndev->ethtool_ops = &xgene_ethtool_ops;
पूर्ण
