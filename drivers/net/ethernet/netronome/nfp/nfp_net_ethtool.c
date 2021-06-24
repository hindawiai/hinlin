<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause)
/* Copyright (C) 2015-2018 Netronome Systems, Inc. */

/*
 * nfp_net_ethtool.c
 * Netronome network device driver: ethtool support
 * Authors: Jakub Kicinski <jakub.kicinski@netronome.com>
 *          Jason McMullan <jason.mcmullan@netronome.com>
 *          Rolf Neugebauer <rolf.neugebauer@netronome.com>
 *          Brad Petrus <brad.petrus@netronome.com>
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/kernel.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/firmware.h>
#समावेश <linux/sfp.h>

#समावेश "nfpcore/nfp.h"
#समावेश "nfpcore/nfp_nsp.h"
#समावेश "nfp_app.h"
#समावेश "nfp_main.h"
#समावेश "nfp_net_ctrl.h"
#समावेश "nfp_net.h"
#समावेश "nfp_port.h"

काष्ठा nfp_et_stat अणु
	अक्षर name[ETH_GSTRING_LEN];
	पूर्णांक off;
पूर्ण;

अटल स्थिर काष्ठा nfp_et_stat nfp_net_et_stats[] = अणु
	/* Stats from the device */
	अणु "dev_rx_discards",	NFP_NET_CFG_STATS_RX_DISCARDS पूर्ण,
	अणु "dev_rx_errors",	NFP_NET_CFG_STATS_RX_ERRORS पूर्ण,
	अणु "dev_rx_bytes",	NFP_NET_CFG_STATS_RX_OCTETS पूर्ण,
	अणु "dev_rx_uc_bytes",	NFP_NET_CFG_STATS_RX_UC_OCTETS पूर्ण,
	अणु "dev_rx_mc_bytes",	NFP_NET_CFG_STATS_RX_MC_OCTETS पूर्ण,
	अणु "dev_rx_bc_bytes",	NFP_NET_CFG_STATS_RX_BC_OCTETS पूर्ण,
	अणु "dev_rx_pkts",	NFP_NET_CFG_STATS_RX_FRAMES पूर्ण,
	अणु "dev_rx_mc_pkts",	NFP_NET_CFG_STATS_RX_MC_FRAMES पूर्ण,
	अणु "dev_rx_bc_pkts",	NFP_NET_CFG_STATS_RX_BC_FRAMES पूर्ण,

	अणु "dev_tx_discards",	NFP_NET_CFG_STATS_TX_DISCARDS पूर्ण,
	अणु "dev_tx_errors",	NFP_NET_CFG_STATS_TX_ERRORS पूर्ण,
	अणु "dev_tx_bytes",	NFP_NET_CFG_STATS_TX_OCTETS पूर्ण,
	अणु "dev_tx_uc_bytes",	NFP_NET_CFG_STATS_TX_UC_OCTETS पूर्ण,
	अणु "dev_tx_mc_bytes",	NFP_NET_CFG_STATS_TX_MC_OCTETS पूर्ण,
	अणु "dev_tx_bc_bytes",	NFP_NET_CFG_STATS_TX_BC_OCTETS पूर्ण,
	अणु "dev_tx_pkts",	NFP_NET_CFG_STATS_TX_FRAMES पूर्ण,
	अणु "dev_tx_mc_pkts",	NFP_NET_CFG_STATS_TX_MC_FRAMES पूर्ण,
	अणु "dev_tx_bc_pkts",	NFP_NET_CFG_STATS_TX_BC_FRAMES पूर्ण,

	अणु "bpf_pass_pkts",	NFP_NET_CFG_STATS_APP0_FRAMES पूर्ण,
	अणु "bpf_pass_bytes",	NFP_NET_CFG_STATS_APP0_BYTES पूर्ण,
	/* see comments in outro functions in nfp_bpf_jit.c to find out
	 * how dअगरferent BPF modes use app-specअगरic counters
	 */
	अणु "bpf_app1_pkts",	NFP_NET_CFG_STATS_APP1_FRAMES पूर्ण,
	अणु "bpf_app1_bytes",	NFP_NET_CFG_STATS_APP1_BYTES पूर्ण,
	अणु "bpf_app2_pkts",	NFP_NET_CFG_STATS_APP2_FRAMES पूर्ण,
	अणु "bpf_app2_bytes",	NFP_NET_CFG_STATS_APP2_BYTES पूर्ण,
	अणु "bpf_app3_pkts",	NFP_NET_CFG_STATS_APP3_FRAMES पूर्ण,
	अणु "bpf_app3_bytes",	NFP_NET_CFG_STATS_APP3_BYTES पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nfp_et_stat nfp_mac_et_stats[] = अणु
	अणु "rx_octets",			NFP_MAC_STATS_RX_IN_OCTETS, पूर्ण,
	अणु "rx_frame_too_long_errors",
			NFP_MAC_STATS_RX_FRAME_TOO_LONG_ERRORS, पूर्ण,
	अणु "rx_range_length_errors",	NFP_MAC_STATS_RX_RANGE_LENGTH_ERRORS, पूर्ण,
	अणु "rx_vlan_received_ok",	NFP_MAC_STATS_RX_VLAN_RECEIVED_OK, पूर्ण,
	अणु "rx_errors",			NFP_MAC_STATS_RX_IN_ERRORS, पूर्ण,
	अणु "rx_broadcast_pkts",		NFP_MAC_STATS_RX_IN_BROADCAST_PKTS, पूर्ण,
	अणु "rx_drop_events",		NFP_MAC_STATS_RX_DROP_EVENTS, पूर्ण,
	अणु "rx_alignment_errors",	NFP_MAC_STATS_RX_ALIGNMENT_ERRORS, पूर्ण,
	अणु "rx_pause_mac_ctrl_frames",
			NFP_MAC_STATS_RX_PAUSE_MAC_CTRL_FRAMES, पूर्ण,
	अणु "rx_frames_received_ok",	NFP_MAC_STATS_RX_FRAMES_RECEIVED_OK, पूर्ण,
	अणु "rx_frame_check_sequence_errors",
			NFP_MAC_STATS_RX_FRAME_CHECK_SEQUENCE_ERRORS, पूर्ण,
	अणु "rx_unicast_pkts",		NFP_MAC_STATS_RX_UNICAST_PKTS, पूर्ण,
	अणु "rx_multicast_pkts",		NFP_MAC_STATS_RX_MULTICAST_PKTS, पूर्ण,
	अणु "rx_pkts",			NFP_MAC_STATS_RX_PKTS, पूर्ण,
	अणु "rx_undersize_pkts",		NFP_MAC_STATS_RX_UNDERSIZE_PKTS, पूर्ण,
	अणु "rx_pkts_64_octets",		NFP_MAC_STATS_RX_PKTS_64_OCTETS, पूर्ण,
	अणु "rx_pkts_65_to_127_octets",
			NFP_MAC_STATS_RX_PKTS_65_TO_127_OCTETS, पूर्ण,
	अणु "rx_pkts_128_to_255_octets",
			NFP_MAC_STATS_RX_PKTS_128_TO_255_OCTETS, पूर्ण,
	अणु "rx_pkts_256_to_511_octets",
			NFP_MAC_STATS_RX_PKTS_256_TO_511_OCTETS, पूर्ण,
	अणु "rx_pkts_512_to_1023_octets",
			NFP_MAC_STATS_RX_PKTS_512_TO_1023_OCTETS, पूर्ण,
	अणु "rx_pkts_1024_to_1518_octets",
			NFP_MAC_STATS_RX_PKTS_1024_TO_1518_OCTETS, पूर्ण,
	अणु "rx_pkts_1519_to_max_octets",
			NFP_MAC_STATS_RX_PKTS_1519_TO_MAX_OCTETS, पूर्ण,
	अणु "rx_jabbers",			NFP_MAC_STATS_RX_JABBERS, पूर्ण,
	अणु "rx_fragments",		NFP_MAC_STATS_RX_FRAGMENTS, पूर्ण,
	अणु "rx_oversize_pkts",		NFP_MAC_STATS_RX_OVERSIZE_PKTS, पूर्ण,
	अणु "rx_pause_frames_class0",	NFP_MAC_STATS_RX_PAUSE_FRAMES_CLASS0, पूर्ण,
	अणु "rx_pause_frames_class1",	NFP_MAC_STATS_RX_PAUSE_FRAMES_CLASS1, पूर्ण,
	अणु "rx_pause_frames_class2",	NFP_MAC_STATS_RX_PAUSE_FRAMES_CLASS2, पूर्ण,
	अणु "rx_pause_frames_class3",	NFP_MAC_STATS_RX_PAUSE_FRAMES_CLASS3, पूर्ण,
	अणु "rx_pause_frames_class4",	NFP_MAC_STATS_RX_PAUSE_FRAMES_CLASS4, पूर्ण,
	अणु "rx_pause_frames_class5",	NFP_MAC_STATS_RX_PAUSE_FRAMES_CLASS5, पूर्ण,
	अणु "rx_pause_frames_class6",	NFP_MAC_STATS_RX_PAUSE_FRAMES_CLASS6, पूर्ण,
	अणु "rx_pause_frames_class7",	NFP_MAC_STATS_RX_PAUSE_FRAMES_CLASS7, पूर्ण,
	अणु "rx_mac_ctrl_frames_received",
			NFP_MAC_STATS_RX_MAC_CTRL_FRAMES_RECEIVED, पूर्ण,
	अणु "rx_mac_head_drop",		NFP_MAC_STATS_RX_MAC_HEAD_DROP, पूर्ण,
	अणु "tx_queue_drop",		NFP_MAC_STATS_TX_QUEUE_DROP, पूर्ण,
	अणु "tx_octets",			NFP_MAC_STATS_TX_OUT_OCTETS, पूर्ण,
	अणु "tx_vlan_transmitted_ok",	NFP_MAC_STATS_TX_VLAN_TRANSMITTED_OK, पूर्ण,
	अणु "tx_errors",			NFP_MAC_STATS_TX_OUT_ERRORS, पूर्ण,
	अणु "tx_broadcast_pkts",		NFP_MAC_STATS_TX_BROADCAST_PKTS, पूर्ण,
	अणु "tx_pause_mac_ctrl_frames",
			NFP_MAC_STATS_TX_PAUSE_MAC_CTRL_FRAMES, पूर्ण,
	अणु "tx_frames_transmitted_ok",
			NFP_MAC_STATS_TX_FRAMES_TRANSMITTED_OK, पूर्ण,
	अणु "tx_unicast_pkts",		NFP_MAC_STATS_TX_UNICAST_PKTS, पूर्ण,
	अणु "tx_multicast_pkts",		NFP_MAC_STATS_TX_MULTICAST_PKTS, पूर्ण,
	अणु "tx_pkts_64_octets",		NFP_MAC_STATS_TX_PKTS_64_OCTETS, पूर्ण,
	अणु "tx_pkts_65_to_127_octets",
			NFP_MAC_STATS_TX_PKTS_65_TO_127_OCTETS, पूर्ण,
	अणु "tx_pkts_128_to_255_octets",
			NFP_MAC_STATS_TX_PKTS_128_TO_255_OCTETS, पूर्ण,
	अणु "tx_pkts_256_to_511_octets",
			NFP_MAC_STATS_TX_PKTS_256_TO_511_OCTETS, पूर्ण,
	अणु "tx_pkts_512_to_1023_octets",
			NFP_MAC_STATS_TX_PKTS_512_TO_1023_OCTETS, पूर्ण,
	अणु "tx_pkts_1024_to_1518_octets",
			NFP_MAC_STATS_TX_PKTS_1024_TO_1518_OCTETS, पूर्ण,
	अणु "tx_pkts_1519_to_max_octets",
			NFP_MAC_STATS_TX_PKTS_1519_TO_MAX_OCTETS, पूर्ण,
	अणु "tx_pause_frames_class0",	NFP_MAC_STATS_TX_PAUSE_FRAMES_CLASS0, पूर्ण,
	अणु "tx_pause_frames_class1",	NFP_MAC_STATS_TX_PAUSE_FRAMES_CLASS1, पूर्ण,
	अणु "tx_pause_frames_class2",	NFP_MAC_STATS_TX_PAUSE_FRAMES_CLASS2, पूर्ण,
	अणु "tx_pause_frames_class3",	NFP_MAC_STATS_TX_PAUSE_FRAMES_CLASS3, पूर्ण,
	अणु "tx_pause_frames_class4",	NFP_MAC_STATS_TX_PAUSE_FRAMES_CLASS4, पूर्ण,
	अणु "tx_pause_frames_class5",	NFP_MAC_STATS_TX_PAUSE_FRAMES_CLASS5, पूर्ण,
	अणु "tx_pause_frames_class6",	NFP_MAC_STATS_TX_PAUSE_FRAMES_CLASS6, पूर्ण,
	अणु "tx_pause_frames_class7",	NFP_MAC_STATS_TX_PAUSE_FRAMES_CLASS7, पूर्ण,
पूर्ण;

अटल स्थिर अक्षर nfp_tlv_stat_names[][ETH_GSTRING_LEN] = अणु
	[1]	= "dev_rx_discards",
	[2]	= "dev_rx_errors",
	[3]	= "dev_rx_bytes",
	[4]	= "dev_rx_uc_bytes",
	[5]	= "dev_rx_mc_bytes",
	[6]	= "dev_rx_bc_bytes",
	[7]	= "dev_rx_pkts",
	[8]	= "dev_rx_mc_pkts",
	[9]	= "dev_rx_bc_pkts",

	[10]	= "dev_tx_discards",
	[11]	= "dev_tx_errors",
	[12]	= "dev_tx_bytes",
	[13]	= "dev_tx_uc_bytes",
	[14]	= "dev_tx_mc_bytes",
	[15]	= "dev_tx_bc_bytes",
	[16]	= "dev_tx_pkts",
	[17]	= "dev_tx_mc_pkts",
	[18]	= "dev_tx_bc_pkts",
पूर्ण;

#घोषणा NN_ET_GLOBAL_STATS_LEN ARRAY_SIZE(nfp_net_et_stats)
#घोषणा NN_ET_SWITCH_STATS_LEN 9
#घोषणा NN_RVEC_GATHER_STATS	13
#घोषणा NN_RVEC_PER_Q_STATS	3
#घोषणा NN_CTRL_PATH_STATS	4

#घोषणा SFP_SFF_REV_COMPLIANCE	1

अटल व्योम nfp_net_get_nspinfo(काष्ठा nfp_app *app, अक्षर *version)
अणु
	काष्ठा nfp_nsp *nsp;

	अगर (!app)
		वापस;

	nsp = nfp_nsp_खोलो(app->cpp);
	अगर (IS_ERR(nsp))
		वापस;

	snम_लिखो(version, ETHTOOL_FWVERS_LEN, "%hu.%hu",
		 nfp_nsp_get_abi_ver_major(nsp),
		 nfp_nsp_get_abi_ver_minor(nsp));

	nfp_nsp_बंद(nsp);
पूर्ण

अटल व्योम
nfp_get_drvinfo(काष्ठा nfp_app *app, काष्ठा pci_dev *pdev,
		स्थिर अक्षर *vnic_version, काष्ठा ethtool_drvinfo *drvinfo)
अणु
	अक्षर nsp_version[ETHTOOL_FWVERS_LEN] = अणुपूर्ण;

	strlcpy(drvinfo->driver, pdev->driver->name, माप(drvinfo->driver));
	nfp_net_get_nspinfo(app, nsp_version);
	snम_लिखो(drvinfo->fw_version, माप(drvinfo->fw_version),
		 "%s %s %s %s", vnic_version, nsp_version,
		 nfp_app_mip_name(app), nfp_app_name(app));
पूर्ण

अटल व्योम
nfp_net_get_drvinfo(काष्ठा net_device *netdev, काष्ठा ethtool_drvinfo *drvinfo)
अणु
	अक्षर vnic_version[ETHTOOL_FWVERS_LEN] = अणुपूर्ण;
	काष्ठा nfp_net *nn = netdev_priv(netdev);

	snम_लिखो(vnic_version, माप(vnic_version), "%d.%d.%d.%d",
		 nn->fw_ver.resv, nn->fw_ver.class,
		 nn->fw_ver.major, nn->fw_ver.minor);
	strlcpy(drvinfo->bus_info, pci_name(nn->pdev),
		माप(drvinfo->bus_info));

	nfp_get_drvinfo(nn->app, nn->pdev, vnic_version, drvinfo);
पूर्ण

अटल व्योम
nfp_app_get_drvinfo(काष्ठा net_device *netdev, काष्ठा ethtool_drvinfo *drvinfo)
अणु
	काष्ठा nfp_app *app = nfp_app_from_netdev(netdev);

	strlcpy(drvinfo->bus_info, pci_name(app->pdev),
		माप(drvinfo->bus_info));
	nfp_get_drvinfo(app, app->pdev, "*", drvinfo);
पूर्ण

अटल व्योम
nfp_net_set_fec_link_mode(काष्ठा nfp_eth_table_port *eth_port,
			  काष्ठा ethtool_link_ksettings *c)
अणु
	अचिन्हित पूर्णांक modes;

	ethtool_link_ksettings_add_link_mode(c, supported, FEC_NONE);
	अगर (!nfp_eth_can_support_fec(eth_port)) अणु
		ethtool_link_ksettings_add_link_mode(c, advertising, FEC_NONE);
		वापस;
	पूर्ण

	modes = nfp_eth_supported_fec_modes(eth_port);
	अगर (modes & NFP_FEC_BASER) अणु
		ethtool_link_ksettings_add_link_mode(c, supported, FEC_BASER);
		ethtool_link_ksettings_add_link_mode(c, advertising, FEC_BASER);
	पूर्ण

	अगर (modes & NFP_FEC_REED_SOLOMON) अणु
		ethtool_link_ksettings_add_link_mode(c, supported, FEC_RS);
		ethtool_link_ksettings_add_link_mode(c, advertising, FEC_RS);
	पूर्ण
पूर्ण

/**
 * nfp_net_get_link_ksettings - Get Link Speed settings
 * @netdev:	network पूर्णांकerface device काष्ठाure
 * @cmd:	ethtool command
 *
 * Reports speed settings based on info in the BAR provided by the fw.
 */
अटल पूर्णांक
nfp_net_get_link_ksettings(काष्ठा net_device *netdev,
			   काष्ठा ethtool_link_ksettings *cmd)
अणु
	अटल स्थिर u32 ls_to_ethtool[] = अणु
		[NFP_NET_CFG_STS_LINK_RATE_UNSUPPORTED]	= 0,
		[NFP_NET_CFG_STS_LINK_RATE_UNKNOWN]	= SPEED_UNKNOWN,
		[NFP_NET_CFG_STS_LINK_RATE_1G]		= SPEED_1000,
		[NFP_NET_CFG_STS_LINK_RATE_10G]		= SPEED_10000,
		[NFP_NET_CFG_STS_LINK_RATE_25G]		= SPEED_25000,
		[NFP_NET_CFG_STS_LINK_RATE_40G]		= SPEED_40000,
		[NFP_NET_CFG_STS_LINK_RATE_50G]		= SPEED_50000,
		[NFP_NET_CFG_STS_LINK_RATE_100G]	= SPEED_100000,
	पूर्ण;
	काष्ठा nfp_eth_table_port *eth_port;
	काष्ठा nfp_port *port;
	काष्ठा nfp_net *nn;
	u32 sts, ls;

	/* Init to unknowns */
	ethtool_link_ksettings_add_link_mode(cmd, supported, FIBRE);
	cmd->base.port = PORT_OTHER;
	cmd->base.speed = SPEED_UNKNOWN;
	cmd->base.duplex = DUPLEX_UNKNOWN;

	port = nfp_port_from_netdev(netdev);
	eth_port = nfp_port_get_eth_port(port);
	अगर (eth_port) अणु
		cmd->base.स्वतःneg = eth_port->aneg != NFP_ANEG_DISABLED ?
			AUTONEG_ENABLE : AUTONEG_DISABLE;
		nfp_net_set_fec_link_mode(eth_port, cmd);
	पूर्ण

	अगर (!netअगर_carrier_ok(netdev))
		वापस 0;

	/* Use link speed from ETH table अगर available, otherwise try the BAR */
	अगर (eth_port) अणु
		cmd->base.port = eth_port->port_type;
		cmd->base.speed = eth_port->speed;
		cmd->base.duplex = DUPLEX_FULL;
		वापस 0;
	पूर्ण

	अगर (!nfp_netdev_is_nfp_net(netdev))
		वापस -EOPNOTSUPP;
	nn = netdev_priv(netdev);

	sts = nn_पढ़ोl(nn, NFP_NET_CFG_STS);

	ls = FIELD_GET(NFP_NET_CFG_STS_LINK_RATE, sts);
	अगर (ls == NFP_NET_CFG_STS_LINK_RATE_UNSUPPORTED)
		वापस -EOPNOTSUPP;

	अगर (ls == NFP_NET_CFG_STS_LINK_RATE_UNKNOWN ||
	    ls >= ARRAY_SIZE(ls_to_ethtool))
		वापस 0;

	cmd->base.speed = ls_to_ethtool[ls];
	cmd->base.duplex = DUPLEX_FULL;

	वापस 0;
पूर्ण

अटल पूर्णांक
nfp_net_set_link_ksettings(काष्ठा net_device *netdev,
			   स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा nfp_eth_table_port *eth_port;
	काष्ठा nfp_port *port;
	काष्ठा nfp_nsp *nsp;
	पूर्णांक err;

	port = nfp_port_from_netdev(netdev);
	eth_port = __nfp_port_get_eth_port(port);
	अगर (!eth_port)
		वापस -EOPNOTSUPP;

	अगर (netअगर_running(netdev)) अणु
		netdev_warn(netdev, "Changing settings not allowed on an active interface. It may cause the port to be disabled until driver reload.\n");
		वापस -EBUSY;
	पूर्ण

	nsp = nfp_eth_config_start(port->app->cpp, eth_port->index);
	अगर (IS_ERR(nsp))
		वापस PTR_ERR(nsp);

	err = __nfp_eth_set_aneg(nsp, cmd->base.स्वतःneg == AUTONEG_ENABLE ?
				 NFP_ANEG_AUTO : NFP_ANEG_DISABLED);
	अगर (err)
		जाओ err_bad_set;
	अगर (cmd->base.speed != SPEED_UNKNOWN) अणु
		u32 speed = cmd->base.speed / eth_port->lanes;

		err = __nfp_eth_set_speed(nsp, speed);
		अगर (err)
			जाओ err_bad_set;
	पूर्ण

	err = nfp_eth_config_commit_end(nsp);
	अगर (err > 0)
		वापस 0; /* no change */

	nfp_net_refresh_port_table(port);

	वापस err;

err_bad_set:
	nfp_eth_config_cleanup_end(nsp);
	वापस err;
पूर्ण

अटल व्योम nfp_net_get_ringparam(काष्ठा net_device *netdev,
				  काष्ठा ethtool_ringparam *ring)
अणु
	काष्ठा nfp_net *nn = netdev_priv(netdev);

	ring->rx_max_pending = NFP_NET_MAX_RX_DESCS;
	ring->tx_max_pending = NFP_NET_MAX_TX_DESCS;
	ring->rx_pending = nn->dp.rxd_cnt;
	ring->tx_pending = nn->dp.txd_cnt;
पूर्ण

अटल पूर्णांक nfp_net_set_ring_size(काष्ठा nfp_net *nn, u32 rxd_cnt, u32 txd_cnt)
अणु
	काष्ठा nfp_net_dp *dp;

	dp = nfp_net_clone_dp(nn);
	अगर (!dp)
		वापस -ENOMEM;

	dp->rxd_cnt = rxd_cnt;
	dp->txd_cnt = txd_cnt;

	वापस nfp_net_ring_reconfig(nn, dp, शून्य);
पूर्ण

अटल पूर्णांक nfp_net_set_ringparam(काष्ठा net_device *netdev,
				 काष्ठा ethtool_ringparam *ring)
अणु
	काष्ठा nfp_net *nn = netdev_priv(netdev);
	u32 rxd_cnt, txd_cnt;

	/* We करोn't have separate queues/rings क्रम small/large frames. */
	अगर (ring->rx_mini_pending || ring->rx_jumbo_pending)
		वापस -EINVAL;

	/* Round up to supported values */
	rxd_cnt = roundup_घात_of_two(ring->rx_pending);
	txd_cnt = roundup_घात_of_two(ring->tx_pending);

	अगर (rxd_cnt < NFP_NET_MIN_RX_DESCS || rxd_cnt > NFP_NET_MAX_RX_DESCS ||
	    txd_cnt < NFP_NET_MIN_TX_DESCS || txd_cnt > NFP_NET_MAX_TX_DESCS)
		वापस -EINVAL;

	अगर (nn->dp.rxd_cnt == rxd_cnt && nn->dp.txd_cnt == txd_cnt)
		वापस 0;

	nn_dbg(nn, "Change ring size: RxQ %u->%u, TxQ %u->%u\n",
	       nn->dp.rxd_cnt, rxd_cnt, nn->dp.txd_cnt, txd_cnt);

	वापस nfp_net_set_ring_size(nn, rxd_cnt, txd_cnt);
पूर्ण

अटल अचिन्हित पूर्णांक nfp_vnic_get_sw_stats_count(काष्ठा net_device *netdev)
अणु
	काष्ठा nfp_net *nn = netdev_priv(netdev);

	वापस NN_RVEC_GATHER_STATS + nn->max_r_vecs * NN_RVEC_PER_Q_STATS +
		NN_CTRL_PATH_STATS;
पूर्ण

अटल u8 *nfp_vnic_get_sw_stats_strings(काष्ठा net_device *netdev, u8 *data)
अणु
	काष्ठा nfp_net *nn = netdev_priv(netdev);
	पूर्णांक i;

	क्रम (i = 0; i < nn->max_r_vecs; i++) अणु
		ethtool_प्र_लिखो(&data, "rvec_%u_rx_pkts", i);
		ethtool_प्र_लिखो(&data, "rvec_%u_tx_pkts", i);
		ethtool_प्र_लिखो(&data, "rvec_%u_tx_busy", i);
	पूर्ण

	ethtool_प्र_लिखो(&data, "hw_rx_csum_ok");
	ethtool_प्र_लिखो(&data, "hw_rx_csum_inner_ok");
	ethtool_प्र_लिखो(&data, "hw_rx_csum_complete");
	ethtool_प्र_लिखो(&data, "hw_rx_csum_err");
	ethtool_प्र_लिखो(&data, "rx_replace_buf_alloc_fail");
	ethtool_प्र_लिखो(&data, "rx_tls_decrypted_packets");
	ethtool_प्र_लिखो(&data, "hw_tx_csum");
	ethtool_प्र_लिखो(&data, "hw_tx_inner_csum");
	ethtool_प्र_लिखो(&data, "tx_gather");
	ethtool_प्र_लिखो(&data, "tx_lso");
	ethtool_प्र_लिखो(&data, "tx_tls_encrypted_packets");
	ethtool_प्र_लिखो(&data, "tx_tls_ooo");
	ethtool_प्र_लिखो(&data, "tx_tls_drop_no_sync_data");

	ethtool_प्र_लिखो(&data, "hw_tls_no_space");
	ethtool_प्र_लिखो(&data, "rx_tls_resync_req_ok");
	ethtool_प्र_लिखो(&data, "rx_tls_resync_req_ign");
	ethtool_प्र_लिखो(&data, "rx_tls_resync_sent");

	वापस data;
पूर्ण

अटल u64 *nfp_vnic_get_sw_stats(काष्ठा net_device *netdev, u64 *data)
अणु
	u64 gathered_stats[NN_RVEC_GATHER_STATS] = अणुपूर्ण;
	काष्ठा nfp_net *nn = netdev_priv(netdev);
	u64 पंचांगp[NN_RVEC_GATHER_STATS];
	अचिन्हित पूर्णांक i, j;

	क्रम (i = 0; i < nn->max_r_vecs; i++) अणु
		अचिन्हित पूर्णांक start;

		करो अणु
			start = u64_stats_fetch_begin(&nn->r_vecs[i].rx_sync);
			data[0] = nn->r_vecs[i].rx_pkts;
			पंचांगp[0] = nn->r_vecs[i].hw_csum_rx_ok;
			पंचांगp[1] = nn->r_vecs[i].hw_csum_rx_inner_ok;
			पंचांगp[2] = nn->r_vecs[i].hw_csum_rx_complete;
			पंचांगp[3] = nn->r_vecs[i].hw_csum_rx_error;
			पंचांगp[4] = nn->r_vecs[i].rx_replace_buf_alloc_fail;
			पंचांगp[5] = nn->r_vecs[i].hw_tls_rx;
		पूर्ण जबतक (u64_stats_fetch_retry(&nn->r_vecs[i].rx_sync, start));

		करो अणु
			start = u64_stats_fetch_begin(&nn->r_vecs[i].tx_sync);
			data[1] = nn->r_vecs[i].tx_pkts;
			data[2] = nn->r_vecs[i].tx_busy;
			पंचांगp[6] = nn->r_vecs[i].hw_csum_tx;
			पंचांगp[7] = nn->r_vecs[i].hw_csum_tx_inner;
			पंचांगp[8] = nn->r_vecs[i].tx_gather;
			पंचांगp[9] = nn->r_vecs[i].tx_lso;
			पंचांगp[10] = nn->r_vecs[i].hw_tls_tx;
			पंचांगp[11] = nn->r_vecs[i].tls_tx_fallback;
			पंचांगp[12] = nn->r_vecs[i].tls_tx_no_fallback;
		पूर्ण जबतक (u64_stats_fetch_retry(&nn->r_vecs[i].tx_sync, start));

		data += NN_RVEC_PER_Q_STATS;

		क्रम (j = 0; j < NN_RVEC_GATHER_STATS; j++)
			gathered_stats[j] += पंचांगp[j];
	पूर्ण

	क्रम (j = 0; j < NN_RVEC_GATHER_STATS; j++)
		*data++ = gathered_stats[j];

	*data++ = atomic_पढ़ो(&nn->ktls_no_space);
	*data++ = atomic_पढ़ो(&nn->ktls_rx_resync_req);
	*data++ = atomic_पढ़ो(&nn->ktls_rx_resync_ign);
	*data++ = atomic_पढ़ो(&nn->ktls_rx_resync_sent);

	वापस data;
पूर्ण

अटल अचिन्हित पूर्णांक nfp_vnic_get_hw_stats_count(अचिन्हित पूर्णांक num_vecs)
अणु
	वापस NN_ET_GLOBAL_STATS_LEN + num_vecs * 4;
पूर्ण

अटल u8 *
nfp_vnic_get_hw_stats_strings(u8 *data, अचिन्हित पूर्णांक num_vecs, bool repr)
अणु
	पूर्णांक swap_off, i;

	BUILD_BUG_ON(NN_ET_GLOBAL_STATS_LEN < NN_ET_SWITCH_STATS_LEN * 2);
	/* If repr is true first add SWITCH_STATS_LEN and then subtract it
	 * effectively swapping the RX and TX statistics (giving us the RX
	 * and TX from perspective of the चयन).
	 */
	swap_off = repr * NN_ET_SWITCH_STATS_LEN;

	क्रम (i = 0; i < NN_ET_SWITCH_STATS_LEN; i++)
		ethtool_प्र_लिखो(&data, nfp_net_et_stats[i + swap_off].name);

	क्रम (i = NN_ET_SWITCH_STATS_LEN; i < NN_ET_SWITCH_STATS_LEN * 2; i++)
		ethtool_प्र_लिखो(&data, nfp_net_et_stats[i - swap_off].name);

	क्रम (i = NN_ET_SWITCH_STATS_LEN * 2; i < NN_ET_GLOBAL_STATS_LEN; i++)
		ethtool_प्र_लिखो(&data, nfp_net_et_stats[i].name);

	क्रम (i = 0; i < num_vecs; i++) अणु
		ethtool_प्र_लिखो(&data, "rxq_%u_pkts", i);
		ethtool_प्र_लिखो(&data, "rxq_%u_bytes", i);
		ethtool_प्र_लिखो(&data, "txq_%u_pkts", i);
		ethtool_प्र_लिखो(&data, "txq_%u_bytes", i);
	पूर्ण

	वापस data;
पूर्ण

अटल u64 *
nfp_vnic_get_hw_stats(u64 *data, u8 __iomem *mem, अचिन्हित पूर्णांक num_vecs)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < NN_ET_GLOBAL_STATS_LEN; i++)
		*data++ = पढ़ोq(mem + nfp_net_et_stats[i].off);

	क्रम (i = 0; i < num_vecs; i++) अणु
		*data++ = पढ़ोq(mem + NFP_NET_CFG_RXR_STATS(i));
		*data++ = पढ़ोq(mem + NFP_NET_CFG_RXR_STATS(i) + 8);
		*data++ = पढ़ोq(mem + NFP_NET_CFG_TXR_STATS(i));
		*data++ = पढ़ोq(mem + NFP_NET_CFG_TXR_STATS(i) + 8);
	पूर्ण

	वापस data;
पूर्ण

अटल अचिन्हित पूर्णांक nfp_vnic_get_tlv_stats_count(काष्ठा nfp_net *nn)
अणु
	वापस nn->tlv_caps.vnic_stats_cnt + nn->max_r_vecs * 4;
पूर्ण

अटल u8 *nfp_vnic_get_tlv_stats_strings(काष्ठा nfp_net *nn, u8 *data)
अणु
	अचिन्हित पूर्णांक i, id;
	u8 __iomem *mem;
	u64 id_word = 0;

	mem = nn->dp.ctrl_bar + nn->tlv_caps.vnic_stats_off;
	क्रम (i = 0; i < nn->tlv_caps.vnic_stats_cnt; i++) अणु
		अगर (!(i % 4))
			id_word = पढ़ोq(mem + i * 2);

		id = (u16)id_word;
		id_word >>= 16;

		अगर (id < ARRAY_SIZE(nfp_tlv_stat_names) &&
		    nfp_tlv_stat_names[id][0]) अणु
			स_नकल(data, nfp_tlv_stat_names[id], ETH_GSTRING_LEN);
			data += ETH_GSTRING_LEN;
		पूर्ण अन्यथा अणु
			ethtool_प्र_लिखो(&data, "dev_unknown_stat%u", id);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < nn->max_r_vecs; i++) अणु
		ethtool_प्र_लिखो(&data, "rxq_%u_pkts", i);
		ethtool_प्र_लिखो(&data, "rxq_%u_bytes", i);
		ethtool_प्र_लिखो(&data, "txq_%u_pkts", i);
		ethtool_प्र_लिखो(&data, "txq_%u_bytes", i);
	पूर्ण

	वापस data;
पूर्ण

अटल u64 *nfp_vnic_get_tlv_stats(काष्ठा nfp_net *nn, u64 *data)
अणु
	u8 __iomem *mem;
	अचिन्हित पूर्णांक i;

	mem = nn->dp.ctrl_bar + nn->tlv_caps.vnic_stats_off;
	mem += roundup(2 * nn->tlv_caps.vnic_stats_cnt, 8);
	क्रम (i = 0; i < nn->tlv_caps.vnic_stats_cnt; i++)
		*data++ = पढ़ोq(mem + i * 8);

	mem = nn->dp.ctrl_bar;
	क्रम (i = 0; i < nn->max_r_vecs; i++) अणु
		*data++ = पढ़ोq(mem + NFP_NET_CFG_RXR_STATS(i));
		*data++ = पढ़ोq(mem + NFP_NET_CFG_RXR_STATS(i) + 8);
		*data++ = पढ़ोq(mem + NFP_NET_CFG_TXR_STATS(i));
		*data++ = पढ़ोq(mem + NFP_NET_CFG_TXR_STATS(i) + 8);
	पूर्ण

	वापस data;
पूर्ण

अटल अचिन्हित पूर्णांक nfp_mac_get_stats_count(काष्ठा net_device *netdev)
अणु
	काष्ठा nfp_port *port;

	port = nfp_port_from_netdev(netdev);
	अगर (!__nfp_port_get_eth_port(port) || !port->eth_stats)
		वापस 0;

	वापस ARRAY_SIZE(nfp_mac_et_stats);
पूर्ण

अटल u8 *nfp_mac_get_stats_strings(काष्ठा net_device *netdev, u8 *data)
अणु
	काष्ठा nfp_port *port;
	अचिन्हित पूर्णांक i;

	port = nfp_port_from_netdev(netdev);
	अगर (!__nfp_port_get_eth_port(port) || !port->eth_stats)
		वापस data;

	क्रम (i = 0; i < ARRAY_SIZE(nfp_mac_et_stats); i++)
		ethtool_प्र_लिखो(&data, "mac.%s", nfp_mac_et_stats[i].name);

	वापस data;
पूर्ण

अटल u64 *nfp_mac_get_stats(काष्ठा net_device *netdev, u64 *data)
अणु
	काष्ठा nfp_port *port;
	अचिन्हित पूर्णांक i;

	port = nfp_port_from_netdev(netdev);
	अगर (!__nfp_port_get_eth_port(port) || !port->eth_stats)
		वापस data;

	क्रम (i = 0; i < ARRAY_SIZE(nfp_mac_et_stats); i++)
		*data++ = पढ़ोq(port->eth_stats + nfp_mac_et_stats[i].off);

	वापस data;
पूर्ण

अटल व्योम nfp_net_get_strings(काष्ठा net_device *netdev,
				u32 stringset, u8 *data)
अणु
	काष्ठा nfp_net *nn = netdev_priv(netdev);

	चयन (stringset) अणु
	हाल ETH_SS_STATS:
		data = nfp_vnic_get_sw_stats_strings(netdev, data);
		अगर (!nn->tlv_caps.vnic_stats_off)
			data = nfp_vnic_get_hw_stats_strings(data,
							     nn->max_r_vecs,
							     false);
		अन्यथा
			data = nfp_vnic_get_tlv_stats_strings(nn, data);
		data = nfp_mac_get_stats_strings(netdev, data);
		data = nfp_app_port_get_stats_strings(nn->port, data);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम
nfp_net_get_stats(काष्ठा net_device *netdev, काष्ठा ethtool_stats *stats,
		  u64 *data)
अणु
	काष्ठा nfp_net *nn = netdev_priv(netdev);

	data = nfp_vnic_get_sw_stats(netdev, data);
	अगर (!nn->tlv_caps.vnic_stats_off)
		data = nfp_vnic_get_hw_stats(data, nn->dp.ctrl_bar,
					     nn->max_r_vecs);
	अन्यथा
		data = nfp_vnic_get_tlv_stats(nn, data);
	data = nfp_mac_get_stats(netdev, data);
	data = nfp_app_port_get_stats(nn->port, data);
पूर्ण

अटल पूर्णांक nfp_net_get_sset_count(काष्ठा net_device *netdev, पूर्णांक sset)
अणु
	काष्ठा nfp_net *nn = netdev_priv(netdev);
	अचिन्हित पूर्णांक cnt;

	चयन (sset) अणु
	हाल ETH_SS_STATS:
		cnt = nfp_vnic_get_sw_stats_count(netdev);
		अगर (!nn->tlv_caps.vnic_stats_off)
			cnt += nfp_vnic_get_hw_stats_count(nn->max_r_vecs);
		अन्यथा
			cnt += nfp_vnic_get_tlv_stats_count(nn);
		cnt += nfp_mac_get_stats_count(netdev);
		cnt += nfp_app_port_get_stats_count(nn->port);
		वापस cnt;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल व्योम nfp_port_get_strings(काष्ठा net_device *netdev,
				 u32 stringset, u8 *data)
अणु
	काष्ठा nfp_port *port = nfp_port_from_netdev(netdev);

	चयन (stringset) अणु
	हाल ETH_SS_STATS:
		अगर (nfp_port_is_vnic(port))
			data = nfp_vnic_get_hw_stats_strings(data, 0, true);
		अन्यथा
			data = nfp_mac_get_stats_strings(netdev, data);
		data = nfp_app_port_get_stats_strings(port, data);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम
nfp_port_get_stats(काष्ठा net_device *netdev, काष्ठा ethtool_stats *stats,
		   u64 *data)
अणु
	काष्ठा nfp_port *port = nfp_port_from_netdev(netdev);

	अगर (nfp_port_is_vnic(port))
		data = nfp_vnic_get_hw_stats(data, port->vnic, 0);
	अन्यथा
		data = nfp_mac_get_stats(netdev, data);
	data = nfp_app_port_get_stats(port, data);
पूर्ण

अटल पूर्णांक nfp_port_get_sset_count(काष्ठा net_device *netdev, पूर्णांक sset)
अणु
	काष्ठा nfp_port *port = nfp_port_from_netdev(netdev);
	अचिन्हित पूर्णांक count;

	चयन (sset) अणु
	हाल ETH_SS_STATS:
		अगर (nfp_port_is_vnic(port))
			count = nfp_vnic_get_hw_stats_count(0);
		अन्यथा
			count = nfp_mac_get_stats_count(netdev);
		count += nfp_app_port_get_stats_count(port);
		वापस count;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक nfp_port_fec_ethtool_to_nsp(u32 fec)
अणु
	चयन (fec) अणु
	हाल ETHTOOL_FEC_AUTO:
		वापस NFP_FEC_AUTO_BIT;
	हाल ETHTOOL_FEC_OFF:
		वापस NFP_FEC_DISABLED_BIT;
	हाल ETHTOOL_FEC_RS:
		वापस NFP_FEC_REED_SOLOMON_BIT;
	हाल ETHTOOL_FEC_BASER:
		वापस NFP_FEC_BASER_BIT;
	शेष:
		/* NSP only supports a single mode at a समय */
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल u32 nfp_port_fec_nsp_to_ethtool(u32 fec)
अणु
	u32 result = 0;

	अगर (fec & NFP_FEC_AUTO)
		result |= ETHTOOL_FEC_AUTO;
	अगर (fec & NFP_FEC_BASER)
		result |= ETHTOOL_FEC_BASER;
	अगर (fec & NFP_FEC_REED_SOLOMON)
		result |= ETHTOOL_FEC_RS;
	अगर (fec & NFP_FEC_DISABLED)
		result |= ETHTOOL_FEC_OFF;

	वापस result ?: ETHTOOL_FEC_NONE;
पूर्ण

अटल पूर्णांक
nfp_port_get_fecparam(काष्ठा net_device *netdev,
		      काष्ठा ethtool_fecparam *param)
अणु
	काष्ठा nfp_eth_table_port *eth_port;
	काष्ठा nfp_port *port;

	param->active_fec = ETHTOOL_FEC_NONE;
	param->fec = ETHTOOL_FEC_NONE;

	port = nfp_port_from_netdev(netdev);
	eth_port = nfp_port_get_eth_port(port);
	अगर (!eth_port)
		वापस -EOPNOTSUPP;

	अगर (!nfp_eth_can_support_fec(eth_port))
		वापस 0;

	param->fec = nfp_port_fec_nsp_to_ethtool(eth_port->fec_modes_supported);
	param->active_fec = nfp_port_fec_nsp_to_ethtool(eth_port->fec);

	वापस 0;
पूर्ण

अटल पूर्णांक
nfp_port_set_fecparam(काष्ठा net_device *netdev,
		      काष्ठा ethtool_fecparam *param)
अणु
	काष्ठा nfp_eth_table_port *eth_port;
	काष्ठा nfp_port *port;
	पूर्णांक err, fec;

	port = nfp_port_from_netdev(netdev);
	eth_port = nfp_port_get_eth_port(port);
	अगर (!eth_port)
		वापस -EOPNOTSUPP;

	अगर (!nfp_eth_can_support_fec(eth_port))
		वापस -EOPNOTSUPP;

	fec = nfp_port_fec_ethtool_to_nsp(param->fec);
	अगर (fec < 0)
		वापस fec;

	err = nfp_eth_set_fec(port->app->cpp, eth_port->index, fec);
	अगर (!err)
		/* Only refresh अगर we did something */
		nfp_net_refresh_port_table(port);

	वापस err < 0 ? err : 0;
पूर्ण

/* RX network flow classअगरication (RSS, filters, etc)
 */
अटल u32 ethtool_flow_to_nfp_flag(u32 flow_type)
अणु
	अटल स्थिर u32 xlate_ethtool_to_nfp[IPV6_FLOW + 1] = अणु
		[TCP_V4_FLOW]	= NFP_NET_CFG_RSS_IPV4_TCP,
		[TCP_V6_FLOW]	= NFP_NET_CFG_RSS_IPV6_TCP,
		[UDP_V4_FLOW]	= NFP_NET_CFG_RSS_IPV4_UDP,
		[UDP_V6_FLOW]	= NFP_NET_CFG_RSS_IPV6_UDP,
		[IPV4_FLOW]	= NFP_NET_CFG_RSS_IPV4,
		[IPV6_FLOW]	= NFP_NET_CFG_RSS_IPV6,
	पूर्ण;

	अगर (flow_type >= ARRAY_SIZE(xlate_ethtool_to_nfp))
		वापस 0;

	वापस xlate_ethtool_to_nfp[flow_type];
पूर्ण

अटल पूर्णांक nfp_net_get_rss_hash_opts(काष्ठा nfp_net *nn,
				     काष्ठा ethtool_rxnfc *cmd)
अणु
	u32 nfp_rss_flag;

	cmd->data = 0;

	अगर (!(nn->cap & NFP_NET_CFG_CTRL_RSS_ANY))
		वापस -EOPNOTSUPP;

	nfp_rss_flag = ethtool_flow_to_nfp_flag(cmd->flow_type);
	अगर (!nfp_rss_flag)
		वापस -EINVAL;

	cmd->data |= RXH_IP_SRC | RXH_IP_DST;
	अगर (nn->rss_cfg & nfp_rss_flag)
		cmd->data |= RXH_L4_B_0_1 | RXH_L4_B_2_3;

	वापस 0;
पूर्ण

अटल पूर्णांक nfp_net_get_rxnfc(काष्ठा net_device *netdev,
			     काष्ठा ethtool_rxnfc *cmd, u32 *rule_locs)
अणु
	काष्ठा nfp_net *nn = netdev_priv(netdev);

	चयन (cmd->cmd) अणु
	हाल ETHTOOL_GRXRINGS:
		cmd->data = nn->dp.num_rx_rings;
		वापस 0;
	हाल ETHTOOL_GRXFH:
		वापस nfp_net_get_rss_hash_opts(nn, cmd);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक nfp_net_set_rss_hash_opt(काष्ठा nfp_net *nn,
				    काष्ठा ethtool_rxnfc *nfc)
अणु
	u32 new_rss_cfg = nn->rss_cfg;
	u32 nfp_rss_flag;
	पूर्णांक err;

	अगर (!(nn->cap & NFP_NET_CFG_CTRL_RSS_ANY))
		वापस -EOPNOTSUPP;

	/* RSS only supports IP SA/DA and L4 src/dst ports  */
	अगर (nfc->data & ~(RXH_IP_SRC | RXH_IP_DST |
			  RXH_L4_B_0_1 | RXH_L4_B_2_3))
		वापस -EINVAL;

	/* We need at least the IP SA/DA fields क्रम hashing */
	अगर (!(nfc->data & RXH_IP_SRC) ||
	    !(nfc->data & RXH_IP_DST))
		वापस -EINVAL;

	nfp_rss_flag = ethtool_flow_to_nfp_flag(nfc->flow_type);
	अगर (!nfp_rss_flag)
		वापस -EINVAL;

	चयन (nfc->data & (RXH_L4_B_0_1 | RXH_L4_B_2_3)) अणु
	हाल 0:
		new_rss_cfg &= ~nfp_rss_flag;
		अवरोध;
	हाल (RXH_L4_B_0_1 | RXH_L4_B_2_3):
		new_rss_cfg |= nfp_rss_flag;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	new_rss_cfg |= FIELD_PREP(NFP_NET_CFG_RSS_HFUNC, nn->rss_hfunc);
	new_rss_cfg |= NFP_NET_CFG_RSS_MASK;

	अगर (new_rss_cfg == nn->rss_cfg)
		वापस 0;

	ग_लिखोl(new_rss_cfg, nn->dp.ctrl_bar + NFP_NET_CFG_RSS_CTRL);
	err = nfp_net_reconfig(nn, NFP_NET_CFG_UPDATE_RSS);
	अगर (err)
		वापस err;

	nn->rss_cfg = new_rss_cfg;

	nn_dbg(nn, "Changed RSS config to 0x%x\n", nn->rss_cfg);
	वापस 0;
पूर्ण

अटल पूर्णांक nfp_net_set_rxnfc(काष्ठा net_device *netdev,
			     काष्ठा ethtool_rxnfc *cmd)
अणु
	काष्ठा nfp_net *nn = netdev_priv(netdev);

	चयन (cmd->cmd) अणु
	हाल ETHTOOL_SRXFH:
		वापस nfp_net_set_rss_hash_opt(nn, cmd);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल u32 nfp_net_get_rxfh_indir_size(काष्ठा net_device *netdev)
अणु
	काष्ठा nfp_net *nn = netdev_priv(netdev);

	अगर (!(nn->cap & NFP_NET_CFG_CTRL_RSS_ANY))
		वापस 0;

	वापस ARRAY_SIZE(nn->rss_itbl);
पूर्ण

अटल u32 nfp_net_get_rxfh_key_size(काष्ठा net_device *netdev)
अणु
	काष्ठा nfp_net *nn = netdev_priv(netdev);

	अगर (!(nn->cap & NFP_NET_CFG_CTRL_RSS_ANY))
		वापस -EOPNOTSUPP;

	वापस nfp_net_rss_key_sz(nn);
पूर्ण

अटल पूर्णांक nfp_net_get_rxfh(काष्ठा net_device *netdev, u32 *indir, u8 *key,
			    u8 *hfunc)
अणु
	काष्ठा nfp_net *nn = netdev_priv(netdev);
	पूर्णांक i;

	अगर (!(nn->cap & NFP_NET_CFG_CTRL_RSS_ANY))
		वापस -EOPNOTSUPP;

	अगर (indir)
		क्रम (i = 0; i < ARRAY_SIZE(nn->rss_itbl); i++)
			indir[i] = nn->rss_itbl[i];
	अगर (key)
		स_नकल(key, nn->rss_key, nfp_net_rss_key_sz(nn));
	अगर (hfunc) अणु
		*hfunc = nn->rss_hfunc;
		अगर (*hfunc >= 1 << ETH_RSS_HASH_FUNCS_COUNT)
			*hfunc = ETH_RSS_HASH_UNKNOWN;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nfp_net_set_rxfh(काष्ठा net_device *netdev,
			    स्थिर u32 *indir, स्थिर u8 *key,
			    स्थिर u8 hfunc)
अणु
	काष्ठा nfp_net *nn = netdev_priv(netdev);
	पूर्णांक i;

	अगर (!(nn->cap & NFP_NET_CFG_CTRL_RSS_ANY) ||
	    !(hfunc == ETH_RSS_HASH_NO_CHANGE || hfunc == nn->rss_hfunc))
		वापस -EOPNOTSUPP;

	अगर (!key && !indir)
		वापस 0;

	अगर (key) अणु
		स_नकल(nn->rss_key, key, nfp_net_rss_key_sz(nn));
		nfp_net_rss_ग_लिखो_key(nn);
	पूर्ण
	अगर (indir) अणु
		क्रम (i = 0; i < ARRAY_SIZE(nn->rss_itbl); i++)
			nn->rss_itbl[i] = indir[i];

		nfp_net_rss_ग_लिखो_itbl(nn);
	पूर्ण

	वापस nfp_net_reconfig(nn, NFP_NET_CFG_UPDATE_RSS);
पूर्ण

/* Dump BAR रेजिस्टरs
 */
अटल पूर्णांक nfp_net_get_regs_len(काष्ठा net_device *netdev)
अणु
	वापस NFP_NET_CFG_BAR_SZ;
पूर्ण

अटल व्योम nfp_net_get_regs(काष्ठा net_device *netdev,
			     काष्ठा ethtool_regs *regs, व्योम *p)
अणु
	काष्ठा nfp_net *nn = netdev_priv(netdev);
	u32 *regs_buf = p;
	पूर्णांक i;

	regs->version = nn_पढ़ोl(nn, NFP_NET_CFG_VERSION);

	क्रम (i = 0; i < NFP_NET_CFG_BAR_SZ / माप(u32); i++)
		regs_buf[i] = पढ़ोl(nn->dp.ctrl_bar + (i * माप(u32)));
पूर्ण

अटल पूर्णांक nfp_net_get_coalesce(काष्ठा net_device *netdev,
				काष्ठा ethtool_coalesce *ec)
अणु
	काष्ठा nfp_net *nn = netdev_priv(netdev);

	अगर (!(nn->cap & NFP_NET_CFG_CTRL_IRQMOD))
		वापस -EINVAL;

	ec->rx_coalesce_usecs       = nn->rx_coalesce_usecs;
	ec->rx_max_coalesced_frames = nn->rx_coalesce_max_frames;
	ec->tx_coalesce_usecs       = nn->tx_coalesce_usecs;
	ec->tx_max_coalesced_frames = nn->tx_coalesce_max_frames;

	वापस 0;
पूर्ण

/* Other debug dumps
 */
अटल पूर्णांक
nfp_dump_nsp_diag(काष्ठा nfp_app *app, काष्ठा ethtool_dump *dump, व्योम *buffer)
अणु
	काष्ठा nfp_resource *res;
	पूर्णांक ret;

	अगर (!app)
		वापस -EOPNOTSUPP;

	dump->version = 1;
	dump->flag = NFP_DUMP_NSP_DIAG;

	res = nfp_resource_acquire(app->cpp, NFP_RESOURCE_NSP_DIAG);
	अगर (IS_ERR(res))
		वापस PTR_ERR(res);

	अगर (buffer) अणु
		अगर (dump->len != nfp_resource_size(res)) अणु
			ret = -EINVAL;
			जाओ निकास_release;
		पूर्ण

		ret = nfp_cpp_पढ़ो(app->cpp, nfp_resource_cpp_id(res),
				   nfp_resource_address(res),
				   buffer, dump->len);
		अगर (ret != dump->len)
			ret = ret < 0 ? ret : -EIO;
		अन्यथा
			ret = 0;
	पूर्ण अन्यथा अणु
		dump->len = nfp_resource_size(res);
		ret = 0;
	पूर्ण
निकास_release:
	nfp_resource_release(res);

	वापस ret;
पूर्ण

/* Set the dump flag/level. Calculate the dump length क्रम flag > 0 only (new TLV
 * based dumps), since flag 0 (शेष) calculates the length in
 * nfp_app_get_dump_flag(), and we need to support triggering a level 0 dump
 * without setting the flag first, क्रम backward compatibility.
 */
अटल पूर्णांक nfp_app_set_dump(काष्ठा net_device *netdev, काष्ठा ethtool_dump *val)
अणु
	काष्ठा nfp_app *app = nfp_app_from_netdev(netdev);
	s64 len;

	अगर (!app)
		वापस -EOPNOTSUPP;

	अगर (val->flag == NFP_DUMP_NSP_DIAG) अणु
		app->pf->dump_flag = val->flag;
		वापस 0;
	पूर्ण

	अगर (!app->pf->dumpspec)
		वापस -EOPNOTSUPP;

	len = nfp_net_dump_calculate_size(app->pf, app->pf->dumpspec,
					  val->flag);
	अगर (len < 0)
		वापस len;

	app->pf->dump_flag = val->flag;
	app->pf->dump_len = len;

	वापस 0;
पूर्ण

अटल पूर्णांक
nfp_app_get_dump_flag(काष्ठा net_device *netdev, काष्ठा ethtool_dump *dump)
अणु
	काष्ठा nfp_app *app = nfp_app_from_netdev(netdev);

	अगर (!app)
		वापस -EOPNOTSUPP;

	अगर (app->pf->dump_flag == NFP_DUMP_NSP_DIAG)
		वापस nfp_dump_nsp_diag(app, dump, शून्य);

	dump->flag = app->pf->dump_flag;
	dump->len = app->pf->dump_len;

	वापस 0;
पूर्ण

अटल पूर्णांक
nfp_app_get_dump_data(काष्ठा net_device *netdev, काष्ठा ethtool_dump *dump,
		      व्योम *buffer)
अणु
	काष्ठा nfp_app *app = nfp_app_from_netdev(netdev);

	अगर (!app)
		वापस -EOPNOTSUPP;

	अगर (app->pf->dump_flag == NFP_DUMP_NSP_DIAG)
		वापस nfp_dump_nsp_diag(app, dump, buffer);

	dump->flag = app->pf->dump_flag;
	dump->len = app->pf->dump_len;

	वापस nfp_net_dump_populate_buffer(app->pf, app->pf->dumpspec, dump,
					    buffer);
पूर्ण

अटल पूर्णांक
nfp_port_get_module_info(काष्ठा net_device *netdev,
			 काष्ठा ethtool_modinfo *modinfo)
अणु
	काष्ठा nfp_eth_table_port *eth_port;
	काष्ठा nfp_port *port;
	अचिन्हित पूर्णांक पढ़ो_len;
	काष्ठा nfp_nsp *nsp;
	पूर्णांक err = 0;
	u8 data;

	port = nfp_port_from_netdev(netdev);
	eth_port = nfp_port_get_eth_port(port);
	अगर (!eth_port)
		वापस -EOPNOTSUPP;

	nsp = nfp_nsp_खोलो(port->app->cpp);
	अगर (IS_ERR(nsp)) अणु
		err = PTR_ERR(nsp);
		netdev_err(netdev, "Failed to access the NSP: %d\n", err);
		वापस err;
	पूर्ण

	अगर (!nfp_nsp_has_पढ़ो_module_eeprom(nsp)) अणु
		netdev_info(netdev, "reading module EEPROM not supported. Please update flash\n");
		err = -EOPNOTSUPP;
		जाओ निकास_बंद_nsp;
	पूर्ण

	चयन (eth_port->पूर्णांकerface) अणु
	हाल NFP_INTERFACE_SFP:
	हाल NFP_INTERFACE_SFP28:
		err = nfp_nsp_पढ़ो_module_eeprom(nsp, eth_port->eth_index,
						 SFP_SFF8472_COMPLIANCE, &data,
						 1, &पढ़ो_len);
		अगर (err < 0)
			जाओ निकास_बंद_nsp;

		अगर (!data) अणु
			modinfo->type = ETH_MODULE_SFF_8079;
			modinfo->eeprom_len = ETH_MODULE_SFF_8079_LEN;
		पूर्ण अन्यथा अणु
			modinfo->type = ETH_MODULE_SFF_8472;
			modinfo->eeprom_len = ETH_MODULE_SFF_8472_LEN;
		पूर्ण
		अवरोध;
	हाल NFP_INTERFACE_QSFP:
		err = nfp_nsp_पढ़ो_module_eeprom(nsp, eth_port->eth_index,
						 SFP_SFF_REV_COMPLIANCE, &data,
						 1, &पढ़ो_len);
		अगर (err < 0)
			जाओ निकास_बंद_nsp;

		अगर (data < 0x3) अणु
			modinfo->type = ETH_MODULE_SFF_8436;
			modinfo->eeprom_len = ETH_MODULE_SFF_8436_LEN;
		पूर्ण अन्यथा अणु
			modinfo->type = ETH_MODULE_SFF_8636;
			modinfo->eeprom_len = ETH_MODULE_SFF_8636_LEN;
		पूर्ण
		अवरोध;
	हाल NFP_INTERFACE_QSFP28:
		modinfo->type = ETH_MODULE_SFF_8636;
		modinfo->eeprom_len = ETH_MODULE_SFF_8636_LEN;
		अवरोध;
	शेष:
		netdev_err(netdev, "Unsupported module 0x%x detected\n",
			   eth_port->पूर्णांकerface);
		err = -EINVAL;
	पूर्ण

निकास_बंद_nsp:
	nfp_nsp_बंद(nsp);
	वापस err;
पूर्ण

अटल पूर्णांक
nfp_port_get_module_eeprom(काष्ठा net_device *netdev,
			   काष्ठा ethtool_eeprom *eeprom, u8 *data)
अणु
	काष्ठा nfp_eth_table_port *eth_port;
	काष्ठा nfp_port *port;
	काष्ठा nfp_nsp *nsp;
	पूर्णांक err;

	port = nfp_port_from_netdev(netdev);
	eth_port = __nfp_port_get_eth_port(port);
	अगर (!eth_port)
		वापस -EOPNOTSUPP;

	nsp = nfp_nsp_खोलो(port->app->cpp);
	अगर (IS_ERR(nsp)) अणु
		err = PTR_ERR(nsp);
		netdev_err(netdev, "Failed to access the NSP: %d\n", err);
		वापस err;
	पूर्ण

	अगर (!nfp_nsp_has_पढ़ो_module_eeprom(nsp)) अणु
		netdev_info(netdev, "reading module EEPROM not supported. Please update flash\n");
		err = -EOPNOTSUPP;
		जाओ निकास_बंद_nsp;
	पूर्ण

	err = nfp_nsp_पढ़ो_module_eeprom(nsp, eth_port->eth_index,
					 eeprom->offset, data, eeprom->len,
					 &eeprom->len);
	अगर (err < 0) अणु
		अगर (eeprom->len) अणु
			netdev_warn(netdev,
				    "Incomplete read from module EEPROM: %d\n",
				     err);
			err = 0;
		पूर्ण अन्यथा अणु
			netdev_err(netdev,
				   "Reading from module EEPROM failed: %d\n",
				   err);
		पूर्ण
	पूर्ण

निकास_बंद_nsp:
	nfp_nsp_बंद(nsp);
	वापस err;
पूर्ण

अटल पूर्णांक nfp_net_set_coalesce(काष्ठा net_device *netdev,
				काष्ठा ethtool_coalesce *ec)
अणु
	काष्ठा nfp_net *nn = netdev_priv(netdev);
	अचिन्हित पूर्णांक factor;

	/* Compute factor used to convert coalesce '_usecs' parameters to
	 * ME बारtamp ticks.  There are 16 ME घड़ी cycles क्रम each बारtamp
	 * count.
	 */
	factor = nn->me_freq_mhz / 16;

	/* Each pair of (usecs, max_frames) fields specअगरies that पूर्णांकerrupts
	 * should be coalesced until
	 *      (usecs > 0 && समय_since_first_completion >= usecs) ||
	 *      (max_frames > 0 && completed_frames >= max_frames)
	 *
	 * It is illegal to set both usecs and max_frames to zero as this would
	 * cause पूर्णांकerrupts to never be generated.  To disable coalescing, set
	 * usecs = 0 and max_frames = 1.
	 *
	 * Some implementations ignore the value of max_frames and use the
	 * condition समय_since_first_completion >= usecs
	 */

	अगर (!(nn->cap & NFP_NET_CFG_CTRL_IRQMOD))
		वापस -EINVAL;

	/* ensure valid configuration */
	अगर (!ec->rx_coalesce_usecs && !ec->rx_max_coalesced_frames)
		वापस -EINVAL;

	अगर (!ec->tx_coalesce_usecs && !ec->tx_max_coalesced_frames)
		वापस -EINVAL;

	अगर (ec->rx_coalesce_usecs * factor >= ((1 << 16) - 1))
		वापस -EINVAL;

	अगर (ec->tx_coalesce_usecs * factor >= ((1 << 16) - 1))
		वापस -EINVAL;

	अगर (ec->rx_max_coalesced_frames >= ((1 << 16) - 1))
		वापस -EINVAL;

	अगर (ec->tx_max_coalesced_frames >= ((1 << 16) - 1))
		वापस -EINVAL;

	/* configuration is valid */
	nn->rx_coalesce_usecs      = ec->rx_coalesce_usecs;
	nn->rx_coalesce_max_frames = ec->rx_max_coalesced_frames;
	nn->tx_coalesce_usecs      = ec->tx_coalesce_usecs;
	nn->tx_coalesce_max_frames = ec->tx_max_coalesced_frames;

	/* ग_लिखो configuration to device */
	nfp_net_coalesce_ग_लिखो_cfg(nn);
	वापस nfp_net_reconfig(nn, NFP_NET_CFG_UPDATE_IRQMOD);
पूर्ण

अटल व्योम nfp_net_get_channels(काष्ठा net_device *netdev,
				 काष्ठा ethtool_channels *channel)
अणु
	काष्ठा nfp_net *nn = netdev_priv(netdev);
	अचिन्हित पूर्णांक num_tx_rings;

	num_tx_rings = nn->dp.num_tx_rings;
	अगर (nn->dp.xdp_prog)
		num_tx_rings -= nn->dp.num_rx_rings;

	channel->max_rx = min(nn->max_rx_rings, nn->max_r_vecs);
	channel->max_tx = min(nn->max_tx_rings, nn->max_r_vecs);
	channel->max_combined = min(channel->max_rx, channel->max_tx);
	channel->max_other = NFP_NET_NON_Q_VECTORS;
	channel->combined_count = min(nn->dp.num_rx_rings, num_tx_rings);
	channel->rx_count = nn->dp.num_rx_rings - channel->combined_count;
	channel->tx_count = num_tx_rings - channel->combined_count;
	channel->other_count = NFP_NET_NON_Q_VECTORS;
पूर्ण

अटल पूर्णांक nfp_net_set_num_rings(काष्ठा nfp_net *nn, अचिन्हित पूर्णांक total_rx,
				 अचिन्हित पूर्णांक total_tx)
अणु
	काष्ठा nfp_net_dp *dp;

	dp = nfp_net_clone_dp(nn);
	अगर (!dp)
		वापस -ENOMEM;

	dp->num_rx_rings = total_rx;
	dp->num_tx_rings = total_tx;
	/* nfp_net_check_config() will catch num_tx_rings > nn->max_tx_rings */
	अगर (dp->xdp_prog)
		dp->num_tx_rings += total_rx;

	वापस nfp_net_ring_reconfig(nn, dp, शून्य);
पूर्ण

अटल पूर्णांक nfp_net_set_channels(काष्ठा net_device *netdev,
				काष्ठा ethtool_channels *channel)
अणु
	काष्ठा nfp_net *nn = netdev_priv(netdev);
	अचिन्हित पूर्णांक total_rx, total_tx;

	/* Reject unsupported */
	अगर (channel->other_count != NFP_NET_NON_Q_VECTORS ||
	    (channel->rx_count && channel->tx_count))
		वापस -EINVAL;

	total_rx = channel->combined_count + channel->rx_count;
	total_tx = channel->combined_count + channel->tx_count;

	अगर (total_rx > min(nn->max_rx_rings, nn->max_r_vecs) ||
	    total_tx > min(nn->max_tx_rings, nn->max_r_vecs))
		वापस -EINVAL;

	वापस nfp_net_set_num_rings(nn, total_rx, total_tx);
पूर्ण

अटल स्थिर काष्ठा ethtool_ops nfp_net_ethtool_ops = अणु
	.supported_coalesce_params = ETHTOOL_COALESCE_USECS |
				     ETHTOOL_COALESCE_MAX_FRAMES,
	.get_drvinfo		= nfp_net_get_drvinfo,
	.get_link		= ethtool_op_get_link,
	.get_ringparam		= nfp_net_get_ringparam,
	.set_ringparam		= nfp_net_set_ringparam,
	.get_strings		= nfp_net_get_strings,
	.get_ethtool_stats	= nfp_net_get_stats,
	.get_sset_count		= nfp_net_get_sset_count,
	.get_rxnfc		= nfp_net_get_rxnfc,
	.set_rxnfc		= nfp_net_set_rxnfc,
	.get_rxfh_indir_size	= nfp_net_get_rxfh_indir_size,
	.get_rxfh_key_size	= nfp_net_get_rxfh_key_size,
	.get_rxfh		= nfp_net_get_rxfh,
	.set_rxfh		= nfp_net_set_rxfh,
	.get_regs_len		= nfp_net_get_regs_len,
	.get_regs		= nfp_net_get_regs,
	.set_dump		= nfp_app_set_dump,
	.get_dump_flag		= nfp_app_get_dump_flag,
	.get_dump_data		= nfp_app_get_dump_data,
	.get_module_info	= nfp_port_get_module_info,
	.get_module_eeprom	= nfp_port_get_module_eeprom,
	.get_coalesce           = nfp_net_get_coalesce,
	.set_coalesce           = nfp_net_set_coalesce,
	.get_channels		= nfp_net_get_channels,
	.set_channels		= nfp_net_set_channels,
	.get_link_ksettings	= nfp_net_get_link_ksettings,
	.set_link_ksettings	= nfp_net_set_link_ksettings,
	.get_fecparam		= nfp_port_get_fecparam,
	.set_fecparam		= nfp_port_set_fecparam,
पूर्ण;

स्थिर काष्ठा ethtool_ops nfp_port_ethtool_ops = अणु
	.get_drvinfo		= nfp_app_get_drvinfo,
	.get_link		= ethtool_op_get_link,
	.get_strings		= nfp_port_get_strings,
	.get_ethtool_stats	= nfp_port_get_stats,
	.get_sset_count		= nfp_port_get_sset_count,
	.set_dump		= nfp_app_set_dump,
	.get_dump_flag		= nfp_app_get_dump_flag,
	.get_dump_data		= nfp_app_get_dump_data,
	.get_module_info	= nfp_port_get_module_info,
	.get_module_eeprom	= nfp_port_get_module_eeprom,
	.get_link_ksettings	= nfp_net_get_link_ksettings,
	.set_link_ksettings	= nfp_net_set_link_ksettings,
	.get_fecparam		= nfp_port_get_fecparam,
	.set_fecparam		= nfp_port_set_fecparam,
पूर्ण;

व्योम nfp_net_set_ethtool_ops(काष्ठा net_device *netdev)
अणु
	netdev->ethtool_ops = &nfp_net_ethtool_ops;
पूर्ण
