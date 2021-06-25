<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2003 - 2009 NetXen, Inc.
 * Copyright (C) 2009 - QLogic Corporation.
 * All rights reserved.
 */

#समावेश <linux/types.h>
#समावेश <linux/delay.h>
#समावेश <linux/pci.h>
#समावेश <यंत्र/पन.स>
#समावेश <linux/netdevice.h>
#समावेश <linux/ethtool.h>

#समावेश "netxen_nic.h"
#समावेश "netxen_nic_hw.h"

काष्ठा netxen_nic_stats अणु
	अक्षर stat_string[ETH_GSTRING_LEN];
	पूर्णांक माप_stat;
	पूर्णांक stat_offset;
पूर्ण;

#घोषणा NETXEN_NIC_STAT(m) माप(((काष्ठा netxen_adapter *)0)->m), \
			दुरत्व(काष्ठा netxen_adapter, m)

#घोषणा NETXEN_NIC_PORT_WINDOW 0x10000
#घोषणा NETXEN_NIC_INVALID_DATA 0xDEADBEEF

अटल स्थिर काष्ठा netxen_nic_stats netxen_nic_gstrings_stats[] = अणु
	अणु"xmit_called", NETXEN_NIC_STAT(stats.xmitcalled)पूर्ण,
	अणु"xmit_finished", NETXEN_NIC_STAT(stats.xmitfinished)पूर्ण,
	अणु"rx_dropped", NETXEN_NIC_STAT(stats.rxdropped)पूर्ण,
	अणु"tx_dropped", NETXEN_NIC_STAT(stats.txdropped)पूर्ण,
	अणु"csummed", NETXEN_NIC_STAT(stats.csummed)पूर्ण,
	अणु"rx_pkts", NETXEN_NIC_STAT(stats.rx_pkts)पूर्ण,
	अणु"lro_pkts", NETXEN_NIC_STAT(stats.lro_pkts)पूर्ण,
	अणु"rx_bytes", NETXEN_NIC_STAT(stats.rxbytes)पूर्ण,
	अणु"tx_bytes", NETXEN_NIC_STAT(stats.txbytes)पूर्ण,
पूर्ण;

#घोषणा NETXEN_NIC_STATS_LEN	ARRAY_SIZE(netxen_nic_gstrings_stats)

अटल स्थिर अक्षर netxen_nic_gstrings_test[][ETH_GSTRING_LEN] = अणु
	"Register_Test_on_offline",
	"Link_Test_on_offline"
पूर्ण;

#घोषणा NETXEN_NIC_TEST_LEN	ARRAY_SIZE(netxen_nic_gstrings_test)

#घोषणा NETXEN_NIC_REGS_COUNT 30
#घोषणा NETXEN_NIC_REGS_LEN (NETXEN_NIC_REGS_COUNT * माप(__le32))
#घोषणा NETXEN_MAX_EEPROM_LEN   1024

अटल पूर्णांक netxen_nic_get_eeprom_len(काष्ठा net_device *dev)
अणु
	वापस NETXEN_FLASH_TOTAL_SIZE;
पूर्ण

अटल व्योम
netxen_nic_get_drvinfo(काष्ठा net_device *dev, काष्ठा ethtool_drvinfo *drvinfo)
अणु
	काष्ठा netxen_adapter *adapter = netdev_priv(dev);
	u32 fw_major = 0;
	u32 fw_minor = 0;
	u32 fw_build = 0;

	strlcpy(drvinfo->driver, netxen_nic_driver_name,
		माप(drvinfo->driver));
	strlcpy(drvinfo->version, NETXEN_NIC_LINUX_VERSIONID,
		माप(drvinfo->version));
	fw_major = NXRD32(adapter, NETXEN_FW_VERSION_MAJOR);
	fw_minor = NXRD32(adapter, NETXEN_FW_VERSION_MINOR);
	fw_build = NXRD32(adapter, NETXEN_FW_VERSION_SUB);
	snम_लिखो(drvinfo->fw_version, माप(drvinfo->fw_version),
		"%d.%d.%d", fw_major, fw_minor, fw_build);

	strlcpy(drvinfo->bus_info, pci_name(adapter->pdev),
		माप(drvinfo->bus_info));
पूर्ण

अटल पूर्णांक
netxen_nic_get_link_ksettings(काष्ठा net_device *dev,
			      काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा netxen_adapter *adapter = netdev_priv(dev);
	पूर्णांक check_sfp_module = 0;
	u32 supported, advertising;

	/* पढ़ो which mode */
	अगर (adapter->ahw.port_type == NETXEN_NIC_GBE) अणु
		supported = (SUPPORTED_10baseT_Half |
				   SUPPORTED_10baseT_Full |
				   SUPPORTED_100baseT_Half |
				   SUPPORTED_100baseT_Full |
				   SUPPORTED_1000baseT_Half |
				   SUPPORTED_1000baseT_Full);

		advertising = (ADVERTISED_100baseT_Half |
				     ADVERTISED_100baseT_Full |
				     ADVERTISED_1000baseT_Half |
				     ADVERTISED_1000baseT_Full);

		cmd->base.port = PORT_TP;

		cmd->base.speed = adapter->link_speed;
		cmd->base.duplex = adapter->link_duplex;
		cmd->base.स्वतःneg = adapter->link_स्वतःneg;

	पूर्ण अन्यथा अगर (adapter->ahw.port_type == NETXEN_NIC_XGBE) अणु
		u32 val;

		val = NXRD32(adapter, NETXEN_PORT_MODE_ADDR);
		अगर (val == NETXEN_PORT_MODE_802_3_AP) अणु
			supported = SUPPORTED_1000baseT_Full;
			advertising = ADVERTISED_1000baseT_Full;
		पूर्ण अन्यथा अणु
			supported = SUPPORTED_10000baseT_Full;
			advertising = ADVERTISED_10000baseT_Full;
		पूर्ण

		अगर (netअगर_running(dev) && adapter->has_link_events) अणु
			cmd->base.speed = adapter->link_speed;
			cmd->base.स्वतःneg = adapter->link_स्वतःneg;
			cmd->base.duplex = adapter->link_duplex;
			जाओ skip;
		पूर्ण

		cmd->base.port = PORT_TP;

		अगर (NX_IS_REVISION_P3(adapter->ahw.revision_id)) अणु
			u16 pcअगरn = adapter->ahw.pci_func;

			val = NXRD32(adapter, P3_LINK_SPEED_REG(pcअगरn));
			cmd->base.speed = P3_LINK_SPEED_MHZ *
				P3_LINK_SPEED_VAL(pcअगरn, val);
		पूर्ण अन्यथा
			cmd->base.speed = SPEED_10000;

		cmd->base.duplex = DUPLEX_FULL;
		cmd->base.स्वतःneg = AUTONEG_DISABLE;
	पूर्ण अन्यथा
		वापस -EIO;

skip:
	cmd->base.phy_address = adapter->physical_port;

	चयन (adapter->ahw.board_type) अणु
	हाल NETXEN_BRDTYPE_P2_SB35_4G:
	हाल NETXEN_BRDTYPE_P2_SB31_2G:
	हाल NETXEN_BRDTYPE_P3_REF_QG:
	हाल NETXEN_BRDTYPE_P3_4_GB:
	हाल NETXEN_BRDTYPE_P3_4_GB_MM:
		supported |= SUPPORTED_Autoneg;
		advertising |= ADVERTISED_Autoneg;
		fallthrough;
	हाल NETXEN_BRDTYPE_P2_SB31_10G_CX4:
	हाल NETXEN_BRDTYPE_P3_10G_CX4:
	हाल NETXEN_BRDTYPE_P3_10G_CX4_LP:
	हाल NETXEN_BRDTYPE_P3_10000_BASE_T:
		supported |= SUPPORTED_TP;
		advertising |= ADVERTISED_TP;
		cmd->base.port = PORT_TP;
		cmd->base.स्वतःneg = (adapter->ahw.board_type ==
				 NETXEN_BRDTYPE_P2_SB31_10G_CX4) ?
		    (AUTONEG_DISABLE) : (adapter->link_स्वतःneg);
		अवरोध;
	हाल NETXEN_BRDTYPE_P2_SB31_10G_HMEZ:
	हाल NETXEN_BRDTYPE_P2_SB31_10G_IMEZ:
	हाल NETXEN_BRDTYPE_P3_IMEZ:
	हाल NETXEN_BRDTYPE_P3_XG_LOM:
	हाल NETXEN_BRDTYPE_P3_HMEZ:
		supported |= SUPPORTED_MII;
		advertising |= ADVERTISED_MII;
		cmd->base.port = PORT_MII;
		cmd->base.स्वतःneg = AUTONEG_DISABLE;
		अवरोध;
	हाल NETXEN_BRDTYPE_P3_10G_SFP_PLUS:
	हाल NETXEN_BRDTYPE_P3_10G_SFP_CT:
	हाल NETXEN_BRDTYPE_P3_10G_SFP_QT:
		advertising |= ADVERTISED_TP;
		supported |= SUPPORTED_TP;
		check_sfp_module = netअगर_running(dev) &&
			adapter->has_link_events;
		fallthrough;
	हाल NETXEN_BRDTYPE_P2_SB31_10G:
	हाल NETXEN_BRDTYPE_P3_10G_XFP:
		supported |= SUPPORTED_FIBRE;
		advertising |= ADVERTISED_FIBRE;
		cmd->base.port = PORT_FIBRE;
		cmd->base.स्वतःneg = AUTONEG_DISABLE;
		अवरोध;
	हाल NETXEN_BRDTYPE_P3_10G_TP:
		अगर (adapter->ahw.port_type == NETXEN_NIC_XGBE) अणु
			cmd->base.स्वतःneg = AUTONEG_DISABLE;
			supported |= (SUPPORTED_FIBRE | SUPPORTED_TP);
			advertising |=
				(ADVERTISED_FIBRE | ADVERTISED_TP);
			cmd->base.port = PORT_FIBRE;
			check_sfp_module = netअगर_running(dev) &&
				adapter->has_link_events;
		पूर्ण अन्यथा अणु
			supported |= (SUPPORTED_TP | SUPPORTED_Autoneg);
			advertising |=
				(ADVERTISED_TP | ADVERTISED_Autoneg);
			cmd->base.port = PORT_TP;
		पूर्ण
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_ERR "netxen-nic: Unsupported board model %d\n",
				adapter->ahw.board_type);
		वापस -EIO;
	पूर्ण

	अगर (check_sfp_module) अणु
		चयन (adapter->module_type) अणु
		हाल LINKEVENT_MODULE_OPTICAL_UNKNOWN:
		हाल LINKEVENT_MODULE_OPTICAL_SRLR:
		हाल LINKEVENT_MODULE_OPTICAL_LRM:
		हाल LINKEVENT_MODULE_OPTICAL_SFP_1G:
			cmd->base.port = PORT_FIBRE;
			अवरोध;
		हाल LINKEVENT_MODULE_TWINAX_UNSUPPORTED_CABLE:
		हाल LINKEVENT_MODULE_TWINAX_UNSUPPORTED_CABLELEN:
		हाल LINKEVENT_MODULE_TWINAX:
			cmd->base.port = PORT_TP;
			अवरोध;
		शेष:
			cmd->base.port = -1;
		पूर्ण
	पूर्ण

	अगर (!netअगर_running(dev) || !adapter->ahw.linkup) अणु
		cmd->base.duplex = DUPLEX_UNKNOWN;
		cmd->base.speed = SPEED_UNKNOWN;
	पूर्ण

	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.supported,
						supported);
	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.advertising,
						advertising);

	वापस 0;
पूर्ण

अटल पूर्णांक
netxen_nic_set_link_ksettings(काष्ठा net_device *dev,
			      स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा netxen_adapter *adapter = netdev_priv(dev);
	u32 speed = cmd->base.speed;
	पूर्णांक ret;

	अगर (adapter->ahw.port_type != NETXEN_NIC_GBE)
		वापस -EOPNOTSUPP;

	अगर (!(adapter->capabilities & NX_FW_CAPABILITY_GBE_LINK_CFG))
		वापस -EOPNOTSUPP;

	ret = nx_fw_cmd_set_gbe_port(adapter, speed, cmd->base.duplex,
				     cmd->base.स्वतःneg);
	अगर (ret == NX_RCODE_NOT_SUPPORTED)
		वापस -EOPNOTSUPP;
	अन्यथा अगर (ret)
		वापस -EIO;

	adapter->link_speed = speed;
	adapter->link_duplex = cmd->base.duplex;
	adapter->link_स्वतःneg = cmd->base.स्वतःneg;

	अगर (!netअगर_running(dev))
		वापस 0;

	dev->netdev_ops->nकरो_stop(dev);
	वापस dev->netdev_ops->nकरो_खोलो(dev);
पूर्ण

अटल पूर्णांक netxen_nic_get_regs_len(काष्ठा net_device *dev)
अणु
	वापस NETXEN_NIC_REGS_LEN;
पूर्ण

अटल व्योम
netxen_nic_get_regs(काष्ठा net_device *dev, काष्ठा ethtool_regs *regs, व्योम *p)
अणु
	काष्ठा netxen_adapter *adapter = netdev_priv(dev);
	काष्ठा netxen_recv_context *recv_ctx = &adapter->recv_ctx;
	काष्ठा nx_host_sds_ring *sds_ring;
	u32 *regs_buff = p;
	पूर्णांक ring, i = 0;
	पूर्णांक port = adapter->physical_port;

	स_रखो(p, 0, NETXEN_NIC_REGS_LEN);

	regs->version = (1 << 24) | (adapter->ahw.revision_id << 16) |
	    (adapter->pdev)->device;

	अगर (adapter->is_up != NETXEN_ADAPTER_UP_MAGIC)
		वापस;

	regs_buff[i++] = NXRD32(adapter, CRB_CMDPEG_STATE);
	regs_buff[i++] = NXRD32(adapter, CRB_RCVPEG_STATE);
	regs_buff[i++] = NXRD32(adapter, CRB_FW_CAPABILITIES_1);
	regs_buff[i++] = NXRDIO(adapter, adapter->crb_पूर्णांक_state_reg);
	regs_buff[i++] = NXRD32(adapter, NX_CRB_DEV_REF_COUNT);
	regs_buff[i++] = NXRD32(adapter, NX_CRB_DEV_STATE);
	regs_buff[i++] = NXRD32(adapter, NETXEN_PEG_ALIVE_COUNTER);
	regs_buff[i++] = NXRD32(adapter, NETXEN_PEG_HALT_STATUS1);
	regs_buff[i++] = NXRD32(adapter, NETXEN_PEG_HALT_STATUS2);

	regs_buff[i++] = NXRD32(adapter, NETXEN_CRB_PEG_NET_0+0x3c);
	regs_buff[i++] = NXRD32(adapter, NETXEN_CRB_PEG_NET_1+0x3c);
	regs_buff[i++] = NXRD32(adapter, NETXEN_CRB_PEG_NET_2+0x3c);
	regs_buff[i++] = NXRD32(adapter, NETXEN_CRB_PEG_NET_3+0x3c);

	अगर (NX_IS_REVISION_P3(adapter->ahw.revision_id)) अणु

		regs_buff[i++] = NXRD32(adapter, NETXEN_CRB_PEG_NET_4+0x3c);
		i += 2;

		regs_buff[i++] = NXRD32(adapter, CRB_XG_STATE_P3);
		regs_buff[i++] = le32_to_cpu(*(adapter->tx_ring->hw_consumer));

	पूर्ण अन्यथा अणु
		i++;

		regs_buff[i++] = NXRD32(adapter,
					NETXEN_NIU_XGE_CONFIG_0+(0x10000*port));
		regs_buff[i++] = NXRD32(adapter,
					NETXEN_NIU_XGE_CONFIG_1+(0x10000*port));

		regs_buff[i++] = NXRD32(adapter, CRB_XG_STATE);
		regs_buff[i++] = NXRDIO(adapter,
				 adapter->tx_ring->crb_cmd_consumer);
	पूर्ण

	regs_buff[i++] = NXRDIO(adapter, adapter->tx_ring->crb_cmd_producer);

	regs_buff[i++] = NXRDIO(adapter,
			 recv_ctx->rds_rings[0].crb_rcv_producer);
	regs_buff[i++] = NXRDIO(adapter,
			 recv_ctx->rds_rings[1].crb_rcv_producer);

	regs_buff[i++] = adapter->max_sds_rings;

	क्रम (ring = 0; ring < adapter->max_sds_rings; ring++) अणु
		sds_ring = &(recv_ctx->sds_rings[ring]);
		regs_buff[i++] = NXRDIO(adapter,
					sds_ring->crb_sts_consumer);
	पूर्ण
पूर्ण

अटल u32 netxen_nic_test_link(काष्ठा net_device *dev)
अणु
	काष्ठा netxen_adapter *adapter = netdev_priv(dev);
	u32 val, port;

	port = adapter->physical_port;
	अगर (NX_IS_REVISION_P3(adapter->ahw.revision_id)) अणु
		val = NXRD32(adapter, CRB_XG_STATE_P3);
		val = XG_LINK_STATE_P3(adapter->ahw.pci_func, val);
		वापस (val == XG_LINK_UP_P3) ? 0 : 1;
	पूर्ण अन्यथा अणु
		val = NXRD32(adapter, CRB_XG_STATE);
		val = (val >> port*8) & 0xff;
		वापस (val == XG_LINK_UP) ? 0 : 1;
	पूर्ण
पूर्ण

अटल पूर्णांक
netxen_nic_get_eeprom(काष्ठा net_device *dev, काष्ठा ethtool_eeprom *eeprom,
		      u8 *bytes)
अणु
	काष्ठा netxen_adapter *adapter = netdev_priv(dev);
	पूर्णांक offset;
	पूर्णांक ret;

	अगर (eeprom->len == 0)
		वापस -EINVAL;

	eeprom->magic = (adapter->pdev)->venकरोr |
			((adapter->pdev)->device << 16);
	offset = eeprom->offset;

	ret = netxen_rom_fast_पढ़ो_words(adapter, offset, bytes,
						eeprom->len);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल व्योम
netxen_nic_get_ringparam(काष्ठा net_device *dev,
		काष्ठा ethtool_ringparam *ring)
अणु
	काष्ठा netxen_adapter *adapter = netdev_priv(dev);

	ring->rx_pending = adapter->num_rxd;
	ring->rx_jumbo_pending = adapter->num_jumbo_rxd;
	ring->rx_jumbo_pending += adapter->num_lro_rxd;
	ring->tx_pending = adapter->num_txd;

	अगर (adapter->ahw.port_type == NETXEN_NIC_GBE) अणु
		ring->rx_max_pending = MAX_RCV_DESCRIPTORS_1G;
		ring->rx_jumbo_max_pending = MAX_JUMBO_RCV_DESCRIPTORS_1G;
	पूर्ण अन्यथा अणु
		ring->rx_max_pending = MAX_RCV_DESCRIPTORS_10G;
		ring->rx_jumbo_max_pending = MAX_JUMBO_RCV_DESCRIPTORS_10G;
	पूर्ण

	ring->tx_max_pending = MAX_CMD_DESCRIPTORS;
पूर्ण

अटल u32
netxen_validate_ringparam(u32 val, u32 min, u32 max, अक्षर *r_name)
अणु
	u32 num_desc;
	num_desc = max(val, min);
	num_desc = min(num_desc, max);
	num_desc = roundup_घात_of_two(num_desc);

	अगर (val != num_desc) अणु
		prपूर्णांकk(KERN_INFO "%s: setting %s ring size %d instead of %d\n",
		       netxen_nic_driver_name, r_name, num_desc, val);
	पूर्ण

	वापस num_desc;
पूर्ण

अटल पूर्णांक
netxen_nic_set_ringparam(काष्ठा net_device *dev,
		काष्ठा ethtool_ringparam *ring)
अणु
	काष्ठा netxen_adapter *adapter = netdev_priv(dev);
	u16 max_rcv_desc = MAX_RCV_DESCRIPTORS_10G;
	u16 max_jumbo_desc = MAX_JUMBO_RCV_DESCRIPTORS_10G;
	u16 num_rxd, num_jumbo_rxd, num_txd;

	अगर (NX_IS_REVISION_P2(adapter->ahw.revision_id))
		वापस -EOPNOTSUPP;

	अगर (ring->rx_mini_pending)
		वापस -EOPNOTSUPP;

	अगर (adapter->ahw.port_type == NETXEN_NIC_GBE) अणु
		max_rcv_desc = MAX_RCV_DESCRIPTORS_1G;
		max_jumbo_desc = MAX_JUMBO_RCV_DESCRIPTORS_10G;
	पूर्ण

	num_rxd = netxen_validate_ringparam(ring->rx_pending,
			MIN_RCV_DESCRIPTORS, max_rcv_desc, "rx");

	num_jumbo_rxd = netxen_validate_ringparam(ring->rx_jumbo_pending,
			MIN_JUMBO_DESCRIPTORS, max_jumbo_desc, "rx jumbo");

	num_txd = netxen_validate_ringparam(ring->tx_pending,
			MIN_CMD_DESCRIPTORS, MAX_CMD_DESCRIPTORS, "tx");

	अगर (num_rxd == adapter->num_rxd && num_txd == adapter->num_txd &&
			num_jumbo_rxd == adapter->num_jumbo_rxd)
		वापस 0;

	adapter->num_rxd = num_rxd;
	adapter->num_jumbo_rxd = num_jumbo_rxd;
	adapter->num_txd = num_txd;

	वापस netxen_nic_reset_context(adapter);
पूर्ण

अटल व्योम
netxen_nic_get_छोड़ोparam(काष्ठा net_device *dev,
			  काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
	काष्ठा netxen_adapter *adapter = netdev_priv(dev);
	__u32 val;
	पूर्णांक port = adapter->physical_port;

	छोड़ो->स्वतःneg = 0;

	अगर (adapter->ahw.port_type == NETXEN_NIC_GBE) अणु
		अगर ((port < 0) || (port >= NETXEN_NIU_MAX_GBE_PORTS))
			वापस;
		/* get flow control settings */
		val = NXRD32(adapter, NETXEN_NIU_GB_MAC_CONFIG_0(port));
		छोड़ो->rx_छोड़ो = netxen_gb_get_rx_flowctl(val);
		val = NXRD32(adapter, NETXEN_NIU_GB_PAUSE_CTL);
		चयन (port) अणु
		हाल 0:
			छोड़ो->tx_छोड़ो = !(netxen_gb_get_gb0_mask(val));
			अवरोध;
		हाल 1:
			छोड़ो->tx_छोड़ो = !(netxen_gb_get_gb1_mask(val));
			अवरोध;
		हाल 2:
			छोड़ो->tx_छोड़ो = !(netxen_gb_get_gb2_mask(val));
			अवरोध;
		हाल 3:
		शेष:
			छोड़ो->tx_छोड़ो = !(netxen_gb_get_gb3_mask(val));
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (adapter->ahw.port_type == NETXEN_NIC_XGBE) अणु
		अगर ((port < 0) || (port >= NETXEN_NIU_MAX_XG_PORTS))
			वापस;
		छोड़ो->rx_छोड़ो = 1;
		val = NXRD32(adapter, NETXEN_NIU_XG_PAUSE_CTL);
		अगर (port == 0)
			छोड़ो->tx_छोड़ो = !(netxen_xg_get_xg0_mask(val));
		अन्यथा
			छोड़ो->tx_छोड़ो = !(netxen_xg_get_xg1_mask(val));
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_ERR"%s: Unknown board type: %x\n",
				netxen_nic_driver_name, adapter->ahw.port_type);
	पूर्ण
पूर्ण

अटल पूर्णांक
netxen_nic_set_छोड़ोparam(काष्ठा net_device *dev,
			  काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
	काष्ठा netxen_adapter *adapter = netdev_priv(dev);
	__u32 val;
	पूर्णांक port = adapter->physical_port;

	/* not supported */
	अगर (छोड़ो->स्वतःneg)
		वापस -EINVAL;

	/* पढ़ो mode */
	अगर (adapter->ahw.port_type == NETXEN_NIC_GBE) अणु
		अगर ((port < 0) || (port >= NETXEN_NIU_MAX_GBE_PORTS))
			वापस -EIO;
		/* set flow control */
		val = NXRD32(adapter, NETXEN_NIU_GB_MAC_CONFIG_0(port));

		अगर (छोड़ो->rx_छोड़ो)
			netxen_gb_rx_flowctl(val);
		अन्यथा
			netxen_gb_unset_rx_flowctl(val);

		NXWR32(adapter, NETXEN_NIU_GB_MAC_CONFIG_0(port),
				val);
		/* set स्वतःneg */
		val = NXRD32(adapter, NETXEN_NIU_GB_PAUSE_CTL);
		चयन (port) अणु
		हाल 0:
			अगर (छोड़ो->tx_छोड़ो)
				netxen_gb_unset_gb0_mask(val);
			अन्यथा
				netxen_gb_set_gb0_mask(val);
			अवरोध;
		हाल 1:
			अगर (छोड़ो->tx_छोड़ो)
				netxen_gb_unset_gb1_mask(val);
			अन्यथा
				netxen_gb_set_gb1_mask(val);
			अवरोध;
		हाल 2:
			अगर (छोड़ो->tx_छोड़ो)
				netxen_gb_unset_gb2_mask(val);
			अन्यथा
				netxen_gb_set_gb2_mask(val);
			अवरोध;
		हाल 3:
		शेष:
			अगर (छोड़ो->tx_छोड़ो)
				netxen_gb_unset_gb3_mask(val);
			अन्यथा
				netxen_gb_set_gb3_mask(val);
			अवरोध;
		पूर्ण
		NXWR32(adapter, NETXEN_NIU_GB_PAUSE_CTL, val);
	पूर्ण अन्यथा अगर (adapter->ahw.port_type == NETXEN_NIC_XGBE) अणु
		अगर ((port < 0) || (port >= NETXEN_NIU_MAX_XG_PORTS))
			वापस -EIO;
		val = NXRD32(adapter, NETXEN_NIU_XG_PAUSE_CTL);
		अगर (port == 0) अणु
			अगर (छोड़ो->tx_छोड़ो)
				netxen_xg_unset_xg0_mask(val);
			अन्यथा
				netxen_xg_set_xg0_mask(val);
		पूर्ण अन्यथा अणु
			अगर (छोड़ो->tx_छोड़ो)
				netxen_xg_unset_xg1_mask(val);
			अन्यथा
				netxen_xg_set_xg1_mask(val);
		पूर्ण
		NXWR32(adapter, NETXEN_NIU_XG_PAUSE_CTL, val);
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_ERR "%s: Unknown board type: %x\n",
				netxen_nic_driver_name,
				adapter->ahw.port_type);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक netxen_nic_reg_test(काष्ठा net_device *dev)
अणु
	काष्ठा netxen_adapter *adapter = netdev_priv(dev);
	u32 data_पढ़ो, data_written;

	data_पढ़ो = NXRD32(adapter, NETXEN_PCIX_PH_REG(0));
	अगर ((data_पढ़ो & 0xffff) != adapter->pdev->venकरोr)
		वापस 1;

	अगर (NX_IS_REVISION_P3(adapter->ahw.revision_id))
		वापस 0;

	data_written = (u32)0xa5a5a5a5;

	NXWR32(adapter, CRB_SCRATCHPAD_TEST, data_written);
	data_पढ़ो = NXRD32(adapter, CRB_SCRATCHPAD_TEST);
	अगर (data_written != data_पढ़ो)
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक netxen_get_sset_count(काष्ठा net_device *dev, पूर्णांक sset)
अणु
	चयन (sset) अणु
	हाल ETH_SS_TEST:
		वापस NETXEN_NIC_TEST_LEN;
	हाल ETH_SS_STATS:
		वापस NETXEN_NIC_STATS_LEN;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल व्योम
netxen_nic_diag_test(काष्ठा net_device *dev, काष्ठा ethtool_test *eth_test,
		     u64 *data)
अणु
	स_रखो(data, 0, माप(uपूर्णांक64_t) * NETXEN_NIC_TEST_LEN);
	अगर ((data[0] = netxen_nic_reg_test(dev)))
		eth_test->flags |= ETH_TEST_FL_FAILED;
	/* link test */
	अगर ((data[1] = (u64) netxen_nic_test_link(dev)))
		eth_test->flags |= ETH_TEST_FL_FAILED;
पूर्ण

अटल व्योम
netxen_nic_get_strings(काष्ठा net_device *dev, u32 stringset, u8 *data)
अणु
	पूर्णांक index;

	चयन (stringset) अणु
	हाल ETH_SS_TEST:
		स_नकल(data, *netxen_nic_gstrings_test,
		       NETXEN_NIC_TEST_LEN * ETH_GSTRING_LEN);
		अवरोध;
	हाल ETH_SS_STATS:
		क्रम (index = 0; index < NETXEN_NIC_STATS_LEN; index++) अणु
			स_नकल(data + index * ETH_GSTRING_LEN,
			       netxen_nic_gstrings_stats[index].stat_string,
			       ETH_GSTRING_LEN);
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम
netxen_nic_get_ethtool_stats(काष्ठा net_device *dev,
			     काष्ठा ethtool_stats *stats, u64 *data)
अणु
	काष्ठा netxen_adapter *adapter = netdev_priv(dev);
	पूर्णांक index;

	क्रम (index = 0; index < NETXEN_NIC_STATS_LEN; index++) अणु
		अक्षर *p =
		    (अक्षर *)adapter +
		    netxen_nic_gstrings_stats[index].stat_offset;
		data[index] =
		    (netxen_nic_gstrings_stats[index].माप_stat ==
		     माप(u64)) ? *(u64 *) p : *(u32 *) p;
	पूर्ण
पूर्ण

अटल व्योम
netxen_nic_get_wol(काष्ठा net_device *dev, काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा netxen_adapter *adapter = netdev_priv(dev);
	u32 wol_cfg = 0;

	wol->supported = 0;
	wol->wolopts = 0;

	अगर (NX_IS_REVISION_P2(adapter->ahw.revision_id))
		वापस;

	wol_cfg = NXRD32(adapter, NETXEN_WOL_CONFIG_NV);
	अगर (wol_cfg & (1UL << adapter->portnum))
		wol->supported |= WAKE_MAGIC;

	wol_cfg = NXRD32(adapter, NETXEN_WOL_CONFIG);
	अगर (wol_cfg & (1UL << adapter->portnum))
		wol->wolopts |= WAKE_MAGIC;
पूर्ण

अटल पूर्णांक
netxen_nic_set_wol(काष्ठा net_device *dev, काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा netxen_adapter *adapter = netdev_priv(dev);
	u32 wol_cfg = 0;

	अगर (NX_IS_REVISION_P2(adapter->ahw.revision_id))
		वापस -EOPNOTSUPP;

	अगर (wol->wolopts & ~WAKE_MAGIC)
		वापस -EOPNOTSUPP;

	wol_cfg = NXRD32(adapter, NETXEN_WOL_CONFIG_NV);
	अगर (!(wol_cfg & (1 << adapter->portnum)))
		वापस -EOPNOTSUPP;

	wol_cfg = NXRD32(adapter, NETXEN_WOL_CONFIG);
	अगर (wol->wolopts & WAKE_MAGIC)
		wol_cfg |= 1UL << adapter->portnum;
	अन्यथा
		wol_cfg &= ~(1UL << adapter->portnum);
	NXWR32(adapter, NETXEN_WOL_CONFIG, wol_cfg);

	वापस 0;
पूर्ण

/*
 * Set the coalescing parameters. Currently only normal is supported.
 * If rx_coalesce_usecs == 0 or rx_max_coalesced_frames == 0 then set the
 * firmware coalescing to शेष.
 */
अटल पूर्णांक netxen_set_पूर्णांकr_coalesce(काष्ठा net_device *netdev,
			काष्ठा ethtool_coalesce *ethcoal)
अणु
	काष्ठा netxen_adapter *adapter = netdev_priv(netdev);

	अगर (!NX_IS_REVISION_P3(adapter->ahw.revision_id))
		वापस -EINVAL;

	अगर (adapter->is_up != NETXEN_ADAPTER_UP_MAGIC)
		वापस -EINVAL;

	/*
	* Return Error अगर unsupported values or
	* unsupported parameters are set.
	*/
	अगर (ethcoal->rx_coalesce_usecs > 0xffff ||
		ethcoal->rx_max_coalesced_frames > 0xffff ||
		ethcoal->tx_coalesce_usecs > 0xffff ||
		ethcoal->tx_max_coalesced_frames > 0xffff)
		वापस -EINVAL;

	अगर (!ethcoal->rx_coalesce_usecs ||
		!ethcoal->rx_max_coalesced_frames) अणु
		adapter->coal.flags = NETXEN_NIC_INTR_DEFAULT;
		adapter->coal.normal.data.rx_समय_us =
			NETXEN_DEFAULT_INTR_COALESCE_RX_TIME_US;
		adapter->coal.normal.data.rx_packets =
			NETXEN_DEFAULT_INTR_COALESCE_RX_PACKETS;
	पूर्ण अन्यथा अणु
		adapter->coal.flags = 0;
		adapter->coal.normal.data.rx_समय_us =
		ethcoal->rx_coalesce_usecs;
		adapter->coal.normal.data.rx_packets =
		ethcoal->rx_max_coalesced_frames;
	पूर्ण
	adapter->coal.normal.data.tx_समय_us = ethcoal->tx_coalesce_usecs;
	adapter->coal.normal.data.tx_packets =
	ethcoal->tx_max_coalesced_frames;

	netxen_config_पूर्णांकr_coalesce(adapter);

	वापस 0;
पूर्ण

अटल पूर्णांक netxen_get_पूर्णांकr_coalesce(काष्ठा net_device *netdev,
			काष्ठा ethtool_coalesce *ethcoal)
अणु
	काष्ठा netxen_adapter *adapter = netdev_priv(netdev);

	अगर (!NX_IS_REVISION_P3(adapter->ahw.revision_id))
		वापस -EINVAL;

	अगर (adapter->is_up != NETXEN_ADAPTER_UP_MAGIC)
		वापस -EINVAL;

	ethcoal->rx_coalesce_usecs = adapter->coal.normal.data.rx_समय_us;
	ethcoal->tx_coalesce_usecs = adapter->coal.normal.data.tx_समय_us;
	ethcoal->rx_max_coalesced_frames =
		adapter->coal.normal.data.rx_packets;
	ethcoal->tx_max_coalesced_frames =
		adapter->coal.normal.data.tx_packets;

	वापस 0;
पूर्ण

अटल पूर्णांक
netxen_get_dump_flag(काष्ठा net_device *netdev, काष्ठा ethtool_dump *dump)
अणु
	काष्ठा netxen_adapter *adapter = netdev_priv(netdev);
	काष्ठा netxen_minidump *mdump = &adapter->mdump;
	अगर (adapter->fw_mdump_rdy)
		dump->len = mdump->md_dump_size;
	अन्यथा
		dump->len = 0;

	अगर (!mdump->md_enabled)
		dump->flag = ETH_FW_DUMP_DISABLE;
	अन्यथा
		dump->flag = mdump->md_capture_mask;

	dump->version = adapter->fw_version;
	वापस 0;
पूर्ण

/* Fw dump levels */
अटल स्थिर u32 FW_DUMP_LEVELS[] = अणु 0x3, 0x7, 0xf, 0x1f, 0x3f, 0x7f, 0xff पूर्ण;

अटल पूर्णांक
netxen_set_dump(काष्ठा net_device *netdev, काष्ठा ethtool_dump *val)
अणु
	पूर्णांक i;
	काष्ठा netxen_adapter *adapter = netdev_priv(netdev);
	काष्ठा netxen_minidump *mdump = &adapter->mdump;

	चयन (val->flag) अणु
	हाल NX_FORCE_FW_DUMP_KEY:
		अगर (!mdump->md_enabled) अणु
			netdev_info(netdev, "FW dump not enabled\n");
			वापस 0;
		पूर्ण
		अगर (adapter->fw_mdump_rdy) अणु
			netdev_info(netdev, "Previous dump not cleared, not forcing dump\n");
			वापस 0;
		पूर्ण
		netdev_info(netdev, "Forcing a fw dump\n");
		nx_dev_request_reset(adapter);
		अवरोध;
	हाल NX_DISABLE_FW_DUMP:
		अगर (mdump->md_enabled) अणु
			netdev_info(netdev, "Disabling FW Dump\n");
			mdump->md_enabled = 0;
		पूर्ण
		अवरोध;
	हाल NX_ENABLE_FW_DUMP:
		अगर (!mdump->md_enabled) अणु
			netdev_info(netdev, "Enabling FW dump\n");
			mdump->md_enabled = 1;
		पूर्ण
		अवरोध;
	हाल NX_FORCE_FW_RESET:
		netdev_info(netdev, "Forcing FW reset\n");
		nx_dev_request_reset(adapter);
		adapter->flags &= ~NETXEN_FW_RESET_OWNER;
		अवरोध;
	शेष:
		क्रम (i = 0; i < ARRAY_SIZE(FW_DUMP_LEVELS); i++) अणु
			अगर (val->flag == FW_DUMP_LEVELS[i]) अणु
				mdump->md_capture_mask = val->flag;
				netdev_info(netdev,
					"Driver mask changed to: 0x%x\n",
					mdump->md_capture_mask);
				वापस 0;
			पूर्ण
		पूर्ण
		netdev_info(netdev,
			"Invalid dump level: 0x%x\n", val->flag);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
netxen_get_dump_data(काष्ठा net_device *netdev, काष्ठा ethtool_dump *dump,
			व्योम *buffer)
अणु
	पूर्णांक i, copy_sz;
	u32 *hdr_ptr, *data;
	काष्ठा netxen_adapter *adapter = netdev_priv(netdev);
	काष्ठा netxen_minidump *mdump = &adapter->mdump;


	अगर (!adapter->fw_mdump_rdy) अणु
		netdev_info(netdev, "Dump not available\n");
		वापस -EINVAL;
	पूर्ण
	/* Copy ढाँचा header first */
	copy_sz = mdump->md_ढाँचा_size;
	hdr_ptr = (u32 *) mdump->md_ढाँचा;
	data = buffer;
	क्रम (i = 0; i < copy_sz/माप(u32); i++)
		*data++ = cpu_to_le32(*hdr_ptr++);

	/* Copy captured dump data */
	स_नकल(buffer + copy_sz,
		mdump->md_capture_buff + mdump->md_ढाँचा_size,
			mdump->md_capture_size);
	dump->len = copy_sz + mdump->md_capture_size;
	dump->flag = mdump->md_capture_mask;

	/* Free dump area once data has been captured */
	vमुक्त(mdump->md_capture_buff);
	mdump->md_capture_buff = शून्य;
	adapter->fw_mdump_rdy = 0;
	netdev_info(netdev, "extracted the fw dump Successfully\n");
	वापस 0;
पूर्ण

स्थिर काष्ठा ethtool_ops netxen_nic_ethtool_ops = अणु
	.supported_coalesce_params = ETHTOOL_COALESCE_USECS |
				     ETHTOOL_COALESCE_MAX_FRAMES,
	.get_drvinfo = netxen_nic_get_drvinfo,
	.get_regs_len = netxen_nic_get_regs_len,
	.get_regs = netxen_nic_get_regs,
	.get_link = ethtool_op_get_link,
	.get_eeprom_len = netxen_nic_get_eeprom_len,
	.get_eeprom = netxen_nic_get_eeprom,
	.get_ringparam = netxen_nic_get_ringparam,
	.set_ringparam = netxen_nic_set_ringparam,
	.get_छोड़ोparam = netxen_nic_get_छोड़ोparam,
	.set_छोड़ोparam = netxen_nic_set_छोड़ोparam,
	.get_wol = netxen_nic_get_wol,
	.set_wol = netxen_nic_set_wol,
	.self_test = netxen_nic_diag_test,
	.get_strings = netxen_nic_get_strings,
	.get_ethtool_stats = netxen_nic_get_ethtool_stats,
	.get_sset_count = netxen_get_sset_count,
	.get_coalesce = netxen_get_पूर्णांकr_coalesce,
	.set_coalesce = netxen_set_पूर्णांकr_coalesce,
	.get_dump_flag = netxen_get_dump_flag,
	.get_dump_data = netxen_get_dump_data,
	.set_dump = netxen_set_dump,
	.get_link_ksettings = netxen_nic_get_link_ksettings,
	.set_link_ksettings = netxen_nic_set_link_ksettings,
पूर्ण;
