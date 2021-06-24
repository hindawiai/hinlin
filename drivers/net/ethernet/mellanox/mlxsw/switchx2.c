<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/* Copyright (c) 2015-2018 Mellanox Technologies. All rights reserved */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/slab.h>
#समावेश <linux/device.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/अगर_vlan.h>

#समावेश "pci.h"
#समावेश "core.h"
#समावेश "reg.h"
#समावेश "port.h"
#समावेश "trap.h"
#समावेश "txheader.h"
#समावेश "ib.h"

अटल स्थिर अक्षर mlxsw_sx_driver_name[] = "mlxsw_switchx2";
अटल स्थिर अक्षर mlxsw_sx_driver_version[] = "1.0";

काष्ठा mlxsw_sx_port;

काष्ठा mlxsw_sx अणु
	काष्ठा mlxsw_sx_port **ports;
	काष्ठा mlxsw_core *core;
	स्थिर काष्ठा mlxsw_bus_info *bus_info;
	u8 hw_id[ETH_ALEN];
पूर्ण;

काष्ठा mlxsw_sx_port_pcpu_stats अणु
	u64			rx_packets;
	u64			rx_bytes;
	u64			tx_packets;
	u64			tx_bytes;
	काष्ठा u64_stats_sync	syncp;
	u32			tx_dropped;
पूर्ण;

काष्ठा mlxsw_sx_port अणु
	काष्ठा net_device *dev;
	काष्ठा mlxsw_sx_port_pcpu_stats __percpu *pcpu_stats;
	काष्ठा mlxsw_sx *mlxsw_sx;
	u8 local_port;
	काष्ठा अणु
		u8 module;
	पूर्ण mapping;
पूर्ण;

/* tx_hdr_version
 * Tx header version.
 * Must be set to 0.
 */
MLXSW_ITEM32(tx, hdr, version, 0x00, 28, 4);

/* tx_hdr_ctl
 * Packet control type.
 * 0 - Ethernet control (e.g. EMADs, LACP)
 * 1 - Ethernet data
 */
MLXSW_ITEM32(tx, hdr, ctl, 0x00, 26, 2);

/* tx_hdr_proto
 * Packet protocol type. Must be set to 1 (Ethernet).
 */
MLXSW_ITEM32(tx, hdr, proto, 0x00, 21, 3);

/* tx_hdr_etclass
 * Egress TClass to be used on the egress device on the egress port.
 * The MSB is specअगरied in the 'ctclass3' field.
 * Range is 0-15, where 15 is the highest priority.
 */
MLXSW_ITEM32(tx, hdr, etclass, 0x00, 18, 3);

/* tx_hdr_swid
 * Switch partition ID.
 */
MLXSW_ITEM32(tx, hdr, swid, 0x00, 12, 3);

/* tx_hdr_port_mid
 * Destination local port क्रम unicast packets.
 * Destination multicast ID क्रम multicast packets.
 *
 * Control packets are directed to a specअगरic egress port, जबतक data
 * packets are transmitted through the CPU port (0) पूर्णांकo the चयन partition,
 * where क्रमwarding rules are applied.
 */
MLXSW_ITEM32(tx, hdr, port_mid, 0x04, 16, 16);

/* tx_hdr_ctclass3
 * See field 'etclass'.
 */
MLXSW_ITEM32(tx, hdr, ctclass3, 0x04, 14, 1);

/* tx_hdr_rdq
 * RDQ क्रम control packets sent to remote CPU.
 * Must be set to 0x1F क्रम EMADs, otherwise 0.
 */
MLXSW_ITEM32(tx, hdr, rdq, 0x04, 9, 5);

/* tx_hdr_cpu_sig
 * Signature control क्रम packets going to CPU. Must be set to 0.
 */
MLXSW_ITEM32(tx, hdr, cpu_sig, 0x04, 0, 9);

/* tx_hdr_sig
 * Stacking protocl signature. Must be set to 0xE0E0.
 */
MLXSW_ITEM32(tx, hdr, sig, 0x0C, 16, 16);

/* tx_hdr_stclass
 * Stacking TClass.
 */
MLXSW_ITEM32(tx, hdr, stclass, 0x0C, 13, 3);

/* tx_hdr_emad
 * EMAD bit. Must be set क्रम EMADs.
 */
MLXSW_ITEM32(tx, hdr, emad, 0x0C, 5, 1);

/* tx_hdr_type
 * 0 - Data packets
 * 6 - Control packets
 */
MLXSW_ITEM32(tx, hdr, type, 0x0C, 0, 4);

अटल व्योम mlxsw_sx_txhdr_स्थिरruct(काष्ठा sk_buff *skb,
				     स्थिर काष्ठा mlxsw_tx_info *tx_info)
अणु
	अक्षर *txhdr = skb_push(skb, MLXSW_TXHDR_LEN);
	bool is_emad = tx_info->is_emad;

	स_रखो(txhdr, 0, MLXSW_TXHDR_LEN);

	/* We currently set शेष values क्रम the egress tclass (QoS). */
	mlxsw_tx_hdr_version_set(txhdr, MLXSW_TXHDR_VERSION_0);
	mlxsw_tx_hdr_ctl_set(txhdr, MLXSW_TXHDR_ETH_CTL);
	mlxsw_tx_hdr_proto_set(txhdr, MLXSW_TXHDR_PROTO_ETH);
	mlxsw_tx_hdr_etclass_set(txhdr, is_emad ? MLXSW_TXHDR_ETCLASS_6 :
						  MLXSW_TXHDR_ETCLASS_5);
	mlxsw_tx_hdr_swid_set(txhdr, 0);
	mlxsw_tx_hdr_port_mid_set(txhdr, tx_info->local_port);
	mlxsw_tx_hdr_ctclass3_set(txhdr, MLXSW_TXHDR_CTCLASS3);
	mlxsw_tx_hdr_rdq_set(txhdr, is_emad ? MLXSW_TXHDR_RDQ_EMAD :
					      MLXSW_TXHDR_RDQ_OTHER);
	mlxsw_tx_hdr_cpu_sig_set(txhdr, MLXSW_TXHDR_CPU_SIG);
	mlxsw_tx_hdr_sig_set(txhdr, MLXSW_TXHDR_SIG);
	mlxsw_tx_hdr_stclass_set(txhdr, MLXSW_TXHDR_STCLASS_NONE);
	mlxsw_tx_hdr_emad_set(txhdr, is_emad ? MLXSW_TXHDR_EMAD :
					       MLXSW_TXHDR_NOT_EMAD);
	mlxsw_tx_hdr_type_set(txhdr, MLXSW_TXHDR_TYPE_CONTROL);
पूर्ण

अटल पूर्णांक mlxsw_sx_port_admin_status_set(काष्ठा mlxsw_sx_port *mlxsw_sx_port,
					  bool is_up)
अणु
	काष्ठा mlxsw_sx *mlxsw_sx = mlxsw_sx_port->mlxsw_sx;
	अक्षर paos_pl[MLXSW_REG_PAOS_LEN];

	mlxsw_reg_paos_pack(paos_pl, mlxsw_sx_port->local_port,
			    is_up ? MLXSW_PORT_ADMIN_STATUS_UP :
			    MLXSW_PORT_ADMIN_STATUS_DOWN);
	वापस mlxsw_reg_ग_लिखो(mlxsw_sx->core, MLXSW_REG(paos), paos_pl);
पूर्ण

अटल पूर्णांक mlxsw_sx_port_oper_status_get(काष्ठा mlxsw_sx_port *mlxsw_sx_port,
					 bool *p_is_up)
अणु
	काष्ठा mlxsw_sx *mlxsw_sx = mlxsw_sx_port->mlxsw_sx;
	अक्षर paos_pl[MLXSW_REG_PAOS_LEN];
	u8 oper_status;
	पूर्णांक err;

	mlxsw_reg_paos_pack(paos_pl, mlxsw_sx_port->local_port, 0);
	err = mlxsw_reg_query(mlxsw_sx->core, MLXSW_REG(paos), paos_pl);
	अगर (err)
		वापस err;
	oper_status = mlxsw_reg_paos_oper_status_get(paos_pl);
	*p_is_up = oper_status == MLXSW_PORT_ADMIN_STATUS_UP;
	वापस 0;
पूर्ण

अटल पूर्णांक __mlxsw_sx_port_mtu_set(काष्ठा mlxsw_sx_port *mlxsw_sx_port,
				   u16 mtu)
अणु
	काष्ठा mlxsw_sx *mlxsw_sx = mlxsw_sx_port->mlxsw_sx;
	अक्षर pmtu_pl[MLXSW_REG_PMTU_LEN];
	पूर्णांक max_mtu;
	पूर्णांक err;

	mlxsw_reg_pmtu_pack(pmtu_pl, mlxsw_sx_port->local_port, 0);
	err = mlxsw_reg_query(mlxsw_sx->core, MLXSW_REG(pmtu), pmtu_pl);
	अगर (err)
		वापस err;
	max_mtu = mlxsw_reg_pmtu_max_mtu_get(pmtu_pl);

	अगर (mtu > max_mtu)
		वापस -EINVAL;

	mlxsw_reg_pmtu_pack(pmtu_pl, mlxsw_sx_port->local_port, mtu);
	वापस mlxsw_reg_ग_लिखो(mlxsw_sx->core, MLXSW_REG(pmtu), pmtu_pl);
पूर्ण

अटल पूर्णांक mlxsw_sx_port_mtu_eth_set(काष्ठा mlxsw_sx_port *mlxsw_sx_port,
				     u16 mtu)
अणु
	mtu += MLXSW_TXHDR_LEN + ETH_HLEN;
	वापस __mlxsw_sx_port_mtu_set(mlxsw_sx_port, mtu);
पूर्ण

अटल पूर्णांक mlxsw_sx_port_mtu_ib_set(काष्ठा mlxsw_sx_port *mlxsw_sx_port,
				    u16 mtu)
अणु
	वापस __mlxsw_sx_port_mtu_set(mlxsw_sx_port, mtu);
पूर्ण

अटल पूर्णांक mlxsw_sx_port_ib_port_set(काष्ठा mlxsw_sx_port *mlxsw_sx_port,
				     u8 ib_port)
अणु
	काष्ठा mlxsw_sx *mlxsw_sx = mlxsw_sx_port->mlxsw_sx;
	अक्षर plib_pl[MLXSW_REG_PLIB_LEN] = अणु0पूर्ण;
	पूर्णांक err;

	mlxsw_reg_plib_local_port_set(plib_pl, mlxsw_sx_port->local_port);
	mlxsw_reg_plib_ib_port_set(plib_pl, ib_port);
	err = mlxsw_reg_ग_लिखो(mlxsw_sx->core, MLXSW_REG(plib), plib_pl);
	वापस err;
पूर्ण

अटल पूर्णांक mlxsw_sx_port_swid_set(काष्ठा mlxsw_sx_port *mlxsw_sx_port, u8 swid)
अणु
	काष्ठा mlxsw_sx *mlxsw_sx = mlxsw_sx_port->mlxsw_sx;
	अक्षर pspa_pl[MLXSW_REG_PSPA_LEN];

	mlxsw_reg_pspa_pack(pspa_pl, swid, mlxsw_sx_port->local_port);
	वापस mlxsw_reg_ग_लिखो(mlxsw_sx->core, MLXSW_REG(pspa), pspa_pl);
पूर्ण

अटल पूर्णांक
mlxsw_sx_port_प्रणाली_port_mapping_set(काष्ठा mlxsw_sx_port *mlxsw_sx_port)
अणु
	काष्ठा mlxsw_sx *mlxsw_sx = mlxsw_sx_port->mlxsw_sx;
	अक्षर sspr_pl[MLXSW_REG_SSPR_LEN];

	mlxsw_reg_sspr_pack(sspr_pl, mlxsw_sx_port->local_port);
	वापस mlxsw_reg_ग_लिखो(mlxsw_sx->core, MLXSW_REG(sspr), sspr_pl);
पूर्ण

अटल पूर्णांक mlxsw_sx_port_module_info_get(काष्ठा mlxsw_sx *mlxsw_sx,
					 u8 local_port, u8 *p_module,
					 u8 *p_width)
अणु
	अक्षर pmlp_pl[MLXSW_REG_PMLP_LEN];
	पूर्णांक err;

	mlxsw_reg_pmlp_pack(pmlp_pl, local_port);
	err = mlxsw_reg_query(mlxsw_sx->core, MLXSW_REG(pmlp), pmlp_pl);
	अगर (err)
		वापस err;
	*p_module = mlxsw_reg_pmlp_module_get(pmlp_pl, 0);
	*p_width = mlxsw_reg_pmlp_width_get(pmlp_pl);
	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_sx_port_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा mlxsw_sx_port *mlxsw_sx_port = netdev_priv(dev);
	पूर्णांक err;

	err = mlxsw_sx_port_admin_status_set(mlxsw_sx_port, true);
	अगर (err)
		वापस err;
	netअगर_start_queue(dev);
	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_sx_port_stop(काष्ठा net_device *dev)
अणु
	काष्ठा mlxsw_sx_port *mlxsw_sx_port = netdev_priv(dev);

	netअगर_stop_queue(dev);
	वापस mlxsw_sx_port_admin_status_set(mlxsw_sx_port, false);
पूर्ण

अटल netdev_tx_t mlxsw_sx_port_xmit(काष्ठा sk_buff *skb,
				      काष्ठा net_device *dev)
अणु
	काष्ठा mlxsw_sx_port *mlxsw_sx_port = netdev_priv(dev);
	काष्ठा mlxsw_sx *mlxsw_sx = mlxsw_sx_port->mlxsw_sx;
	काष्ठा mlxsw_sx_port_pcpu_stats *pcpu_stats;
	स्थिर काष्ठा mlxsw_tx_info tx_info = अणु
		.local_port = mlxsw_sx_port->local_port,
		.is_emad = false,
	पूर्ण;
	u64 len;
	पूर्णांक err;

	अगर (skb_cow_head(skb, MLXSW_TXHDR_LEN)) अणु
		this_cpu_inc(mlxsw_sx_port->pcpu_stats->tx_dropped);
		dev_kमुक्त_skb_any(skb);
		वापस NETDEV_TX_OK;
	पूर्ण

	स_रखो(skb->cb, 0, माप(काष्ठा mlxsw_skb_cb));

	अगर (mlxsw_core_skb_transmit_busy(mlxsw_sx->core, &tx_info))
		वापस NETDEV_TX_BUSY;

	mlxsw_sx_txhdr_स्थिरruct(skb, &tx_info);
	/* TX header is consumed by HW on the way so we shouldn't count its
	 * bytes as being sent.
	 */
	len = skb->len - MLXSW_TXHDR_LEN;
	/* Due to a race we might fail here because of a full queue. In that
	 * unlikely हाल we simply drop the packet.
	 */
	err = mlxsw_core_skb_transmit(mlxsw_sx->core, skb, &tx_info);

	अगर (!err) अणु
		pcpu_stats = this_cpu_ptr(mlxsw_sx_port->pcpu_stats);
		u64_stats_update_begin(&pcpu_stats->syncp);
		pcpu_stats->tx_packets++;
		pcpu_stats->tx_bytes += len;
		u64_stats_update_end(&pcpu_stats->syncp);
	पूर्ण अन्यथा अणु
		this_cpu_inc(mlxsw_sx_port->pcpu_stats->tx_dropped);
		dev_kमुक्त_skb_any(skb);
	पूर्ण
	वापस NETDEV_TX_OK;
पूर्ण

अटल पूर्णांक mlxsw_sx_port_change_mtu(काष्ठा net_device *dev, पूर्णांक mtu)
अणु
	काष्ठा mlxsw_sx_port *mlxsw_sx_port = netdev_priv(dev);
	पूर्णांक err;

	err = mlxsw_sx_port_mtu_eth_set(mlxsw_sx_port, mtu);
	अगर (err)
		वापस err;
	dev->mtu = mtu;
	वापस 0;
पूर्ण

अटल व्योम
mlxsw_sx_port_get_stats64(काष्ठा net_device *dev,
			  काष्ठा rtnl_link_stats64 *stats)
अणु
	काष्ठा mlxsw_sx_port *mlxsw_sx_port = netdev_priv(dev);
	काष्ठा mlxsw_sx_port_pcpu_stats *p;
	u64 rx_packets, rx_bytes, tx_packets, tx_bytes;
	u32 tx_dropped = 0;
	अचिन्हित पूर्णांक start;
	पूर्णांक i;

	क्रम_each_possible_cpu(i) अणु
		p = per_cpu_ptr(mlxsw_sx_port->pcpu_stats, i);
		करो अणु
			start = u64_stats_fetch_begin_irq(&p->syncp);
			rx_packets	= p->rx_packets;
			rx_bytes	= p->rx_bytes;
			tx_packets	= p->tx_packets;
			tx_bytes	= p->tx_bytes;
		पूर्ण जबतक (u64_stats_fetch_retry_irq(&p->syncp, start));

		stats->rx_packets	+= rx_packets;
		stats->rx_bytes		+= rx_bytes;
		stats->tx_packets	+= tx_packets;
		stats->tx_bytes		+= tx_bytes;
		/* tx_dropped is u32, updated without syncp protection. */
		tx_dropped	+= p->tx_dropped;
	पूर्ण
	stats->tx_dropped	= tx_dropped;
पूर्ण

अटल काष्ठा devlink_port *
mlxsw_sx_port_get_devlink_port(काष्ठा net_device *dev)
अणु
	काष्ठा mlxsw_sx_port *mlxsw_sx_port = netdev_priv(dev);
	काष्ठा mlxsw_sx *mlxsw_sx = mlxsw_sx_port->mlxsw_sx;

	वापस mlxsw_core_port_devlink_port_get(mlxsw_sx->core,
						mlxsw_sx_port->local_port);
पूर्ण

अटल स्थिर काष्ठा net_device_ops mlxsw_sx_port_netdev_ops = अणु
	.nकरो_खोलो		= mlxsw_sx_port_खोलो,
	.nकरो_stop		= mlxsw_sx_port_stop,
	.nकरो_start_xmit		= mlxsw_sx_port_xmit,
	.nकरो_change_mtu		= mlxsw_sx_port_change_mtu,
	.nकरो_get_stats64	= mlxsw_sx_port_get_stats64,
	.nकरो_get_devlink_port	= mlxsw_sx_port_get_devlink_port,
पूर्ण;

अटल व्योम mlxsw_sx_port_get_drvinfo(काष्ठा net_device *dev,
				      काष्ठा ethtool_drvinfo *drvinfo)
अणु
	काष्ठा mlxsw_sx_port *mlxsw_sx_port = netdev_priv(dev);
	काष्ठा mlxsw_sx *mlxsw_sx = mlxsw_sx_port->mlxsw_sx;

	strlcpy(drvinfo->driver, mlxsw_sx_driver_name, माप(drvinfo->driver));
	strlcpy(drvinfo->version, mlxsw_sx_driver_version,
		माप(drvinfo->version));
	snम_लिखो(drvinfo->fw_version, माप(drvinfo->fw_version),
		 "%d.%d.%d",
		 mlxsw_sx->bus_info->fw_rev.major,
		 mlxsw_sx->bus_info->fw_rev.minor,
		 mlxsw_sx->bus_info->fw_rev.subminor);
	strlcpy(drvinfo->bus_info, mlxsw_sx->bus_info->device_name,
		माप(drvinfo->bus_info));
पूर्ण

काष्ठा mlxsw_sx_port_hw_stats अणु
	अक्षर str[ETH_GSTRING_LEN];
	u64 (*getter)(स्थिर अक्षर *payload);
पूर्ण;

अटल स्थिर काष्ठा mlxsw_sx_port_hw_stats mlxsw_sx_port_hw_stats[] = अणु
	अणु
		.str = "a_frames_transmitted_ok",
		.getter = mlxsw_reg_ppcnt_a_frames_transmitted_ok_get,
	पूर्ण,
	अणु
		.str = "a_frames_received_ok",
		.getter = mlxsw_reg_ppcnt_a_frames_received_ok_get,
	पूर्ण,
	अणु
		.str = "a_frame_check_sequence_errors",
		.getter = mlxsw_reg_ppcnt_a_frame_check_sequence_errors_get,
	पूर्ण,
	अणु
		.str = "a_alignment_errors",
		.getter = mlxsw_reg_ppcnt_a_alignment_errors_get,
	पूर्ण,
	अणु
		.str = "a_octets_transmitted_ok",
		.getter = mlxsw_reg_ppcnt_a_octets_transmitted_ok_get,
	पूर्ण,
	अणु
		.str = "a_octets_received_ok",
		.getter = mlxsw_reg_ppcnt_a_octets_received_ok_get,
	पूर्ण,
	अणु
		.str = "a_multicast_frames_xmitted_ok",
		.getter = mlxsw_reg_ppcnt_a_multicast_frames_xmitted_ok_get,
	पूर्ण,
	अणु
		.str = "a_broadcast_frames_xmitted_ok",
		.getter = mlxsw_reg_ppcnt_a_broadcast_frames_xmitted_ok_get,
	पूर्ण,
	अणु
		.str = "a_multicast_frames_received_ok",
		.getter = mlxsw_reg_ppcnt_a_multicast_frames_received_ok_get,
	पूर्ण,
	अणु
		.str = "a_broadcast_frames_received_ok",
		.getter = mlxsw_reg_ppcnt_a_broadcast_frames_received_ok_get,
	पूर्ण,
	अणु
		.str = "a_in_range_length_errors",
		.getter = mlxsw_reg_ppcnt_a_in_range_length_errors_get,
	पूर्ण,
	अणु
		.str = "a_out_of_range_length_field",
		.getter = mlxsw_reg_ppcnt_a_out_of_range_length_field_get,
	पूर्ण,
	अणु
		.str = "a_frame_too_long_errors",
		.getter = mlxsw_reg_ppcnt_a_frame_too_दीर्घ_errors_get,
	पूर्ण,
	अणु
		.str = "a_symbol_error_during_carrier",
		.getter = mlxsw_reg_ppcnt_a_symbol_error_during_carrier_get,
	पूर्ण,
	अणु
		.str = "a_mac_control_frames_transmitted",
		.getter = mlxsw_reg_ppcnt_a_mac_control_frames_transmitted_get,
	पूर्ण,
	अणु
		.str = "a_mac_control_frames_received",
		.getter = mlxsw_reg_ppcnt_a_mac_control_frames_received_get,
	पूर्ण,
	अणु
		.str = "a_unsupported_opcodes_received",
		.getter = mlxsw_reg_ppcnt_a_unsupported_opcodes_received_get,
	पूर्ण,
	अणु
		.str = "a_pause_mac_ctrl_frames_received",
		.getter = mlxsw_reg_ppcnt_a_छोड़ो_mac_ctrl_frames_received_get,
	पूर्ण,
	अणु
		.str = "a_pause_mac_ctrl_frames_xmitted",
		.getter = mlxsw_reg_ppcnt_a_छोड़ो_mac_ctrl_frames_transmitted_get,
	पूर्ण,
पूर्ण;

#घोषणा MLXSW_SX_PORT_HW_STATS_LEN ARRAY_SIZE(mlxsw_sx_port_hw_stats)

अटल व्योम mlxsw_sx_port_get_strings(काष्ठा net_device *dev,
				      u32 stringset, u8 *data)
अणु
	u8 *p = data;
	पूर्णांक i;

	चयन (stringset) अणु
	हाल ETH_SS_STATS:
		क्रम (i = 0; i < MLXSW_SX_PORT_HW_STATS_LEN; i++) अणु
			स_नकल(p, mlxsw_sx_port_hw_stats[i].str,
			       ETH_GSTRING_LEN);
			p += ETH_GSTRING_LEN;
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम mlxsw_sx_port_get_stats(काष्ठा net_device *dev,
				    काष्ठा ethtool_stats *stats, u64 *data)
अणु
	काष्ठा mlxsw_sx_port *mlxsw_sx_port = netdev_priv(dev);
	काष्ठा mlxsw_sx *mlxsw_sx = mlxsw_sx_port->mlxsw_sx;
	अक्षर ppcnt_pl[MLXSW_REG_PPCNT_LEN];
	पूर्णांक i;
	पूर्णांक err;

	mlxsw_reg_ppcnt_pack(ppcnt_pl, mlxsw_sx_port->local_port,
			     MLXSW_REG_PPCNT_IEEE_8023_CNT, 0);
	err = mlxsw_reg_query(mlxsw_sx->core, MLXSW_REG(ppcnt), ppcnt_pl);
	क्रम (i = 0; i < MLXSW_SX_PORT_HW_STATS_LEN; i++)
		data[i] = !err ? mlxsw_sx_port_hw_stats[i].getter(ppcnt_pl) : 0;
पूर्ण

अटल पूर्णांक mlxsw_sx_port_get_sset_count(काष्ठा net_device *dev, पूर्णांक sset)
अणु
	चयन (sset) अणु
	हाल ETH_SS_STATS:
		वापस MLXSW_SX_PORT_HW_STATS_LEN;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

काष्ठा mlxsw_sx_port_link_mode अणु
	u32 mask;
	u32 supported;
	u32 advertised;
	u32 speed;
पूर्ण;

अटल स्थिर काष्ठा mlxsw_sx_port_link_mode mlxsw_sx_port_link_mode[] = अणु
	अणु
		.mask		= MLXSW_REG_PTYS_ETH_SPEED_SGMII |
				  MLXSW_REG_PTYS_ETH_SPEED_1000BASE_KX,
		.supported	= SUPPORTED_1000baseKX_Full,
		.advertised	= ADVERTISED_1000baseKX_Full,
		.speed		= 1000,
	पूर्ण,
	अणु
		.mask		= MLXSW_REG_PTYS_ETH_SPEED_10GBASE_CX4 |
				  MLXSW_REG_PTYS_ETH_SPEED_10GBASE_KX4,
		.supported	= SUPPORTED_10000baseKX4_Full,
		.advertised	= ADVERTISED_10000baseKX4_Full,
		.speed		= 10000,
	पूर्ण,
	अणु
		.mask		= MLXSW_REG_PTYS_ETH_SPEED_10GBASE_KR |
				  MLXSW_REG_PTYS_ETH_SPEED_10GBASE_CR |
				  MLXSW_REG_PTYS_ETH_SPEED_10GBASE_SR |
				  MLXSW_REG_PTYS_ETH_SPEED_10GBASE_ER_LR,
		.supported	= SUPPORTED_10000baseKR_Full,
		.advertised	= ADVERTISED_10000baseKR_Full,
		.speed		= 10000,
	पूर्ण,
	अणु
		.mask		= MLXSW_REG_PTYS_ETH_SPEED_40GBASE_CR4,
		.supported	= SUPPORTED_40000baseCR4_Full,
		.advertised	= ADVERTISED_40000baseCR4_Full,
		.speed		= 40000,
	पूर्ण,
	अणु
		.mask		= MLXSW_REG_PTYS_ETH_SPEED_40GBASE_KR4,
		.supported	= SUPPORTED_40000baseKR4_Full,
		.advertised	= ADVERTISED_40000baseKR4_Full,
		.speed		= 40000,
	पूर्ण,
	अणु
		.mask		= MLXSW_REG_PTYS_ETH_SPEED_40GBASE_SR4,
		.supported	= SUPPORTED_40000baseSR4_Full,
		.advertised	= ADVERTISED_40000baseSR4_Full,
		.speed		= 40000,
	पूर्ण,
	अणु
		.mask		= MLXSW_REG_PTYS_ETH_SPEED_40GBASE_LR4_ER4,
		.supported	= SUPPORTED_40000baseLR4_Full,
		.advertised	= ADVERTISED_40000baseLR4_Full,
		.speed		= 40000,
	पूर्ण,
	अणु
		.mask		= MLXSW_REG_PTYS_ETH_SPEED_25GBASE_CR |
				  MLXSW_REG_PTYS_ETH_SPEED_25GBASE_KR |
				  MLXSW_REG_PTYS_ETH_SPEED_25GBASE_SR,
		.speed		= 25000,
	पूर्ण,
	अणु
		.mask		= MLXSW_REG_PTYS_ETH_SPEED_50GBASE_KR4 |
				  MLXSW_REG_PTYS_ETH_SPEED_50GBASE_CR2 |
				  MLXSW_REG_PTYS_ETH_SPEED_50GBASE_KR2,
		.speed		= 50000,
	पूर्ण,
	अणु
		.mask		= MLXSW_REG_PTYS_ETH_SPEED_100GBASE_CR4 |
				  MLXSW_REG_PTYS_ETH_SPEED_100GBASE_SR4 |
				  MLXSW_REG_PTYS_ETH_SPEED_100GBASE_KR4 |
				  MLXSW_REG_PTYS_ETH_SPEED_100GBASE_LR4_ER4,
		.speed		= 100000,
	पूर्ण,
पूर्ण;

#घोषणा MLXSW_SX_PORT_LINK_MODE_LEN ARRAY_SIZE(mlxsw_sx_port_link_mode)
#घोषणा MLXSW_SX_PORT_BASE_SPEED 10000 /* Mb/s */

अटल u32 mlxsw_sx_from_ptys_supported_port(u32 ptys_eth_proto)
अणु
	अगर (ptys_eth_proto & (MLXSW_REG_PTYS_ETH_SPEED_10GBASE_CR |
			      MLXSW_REG_PTYS_ETH_SPEED_10GBASE_SR |
			      MLXSW_REG_PTYS_ETH_SPEED_40GBASE_CR4 |
			      MLXSW_REG_PTYS_ETH_SPEED_40GBASE_SR4 |
			      MLXSW_REG_PTYS_ETH_SPEED_100GBASE_SR4 |
			      MLXSW_REG_PTYS_ETH_SPEED_SGMII))
		वापस SUPPORTED_FIBRE;

	अगर (ptys_eth_proto & (MLXSW_REG_PTYS_ETH_SPEED_10GBASE_KR |
			      MLXSW_REG_PTYS_ETH_SPEED_10GBASE_KX4 |
			      MLXSW_REG_PTYS_ETH_SPEED_40GBASE_KR4 |
			      MLXSW_REG_PTYS_ETH_SPEED_100GBASE_KR4 |
			      MLXSW_REG_PTYS_ETH_SPEED_1000BASE_KX))
		वापस SUPPORTED_Backplane;
	वापस 0;
पूर्ण

अटल u32 mlxsw_sx_from_ptys_supported_link(u32 ptys_eth_proto)
अणु
	u32 modes = 0;
	पूर्णांक i;

	क्रम (i = 0; i < MLXSW_SX_PORT_LINK_MODE_LEN; i++) अणु
		अगर (ptys_eth_proto & mlxsw_sx_port_link_mode[i].mask)
			modes |= mlxsw_sx_port_link_mode[i].supported;
	पूर्ण
	वापस modes;
पूर्ण

अटल u32 mlxsw_sx_from_ptys_advert_link(u32 ptys_eth_proto)
अणु
	u32 modes = 0;
	पूर्णांक i;

	क्रम (i = 0; i < MLXSW_SX_PORT_LINK_MODE_LEN; i++) अणु
		अगर (ptys_eth_proto & mlxsw_sx_port_link_mode[i].mask)
			modes |= mlxsw_sx_port_link_mode[i].advertised;
	पूर्ण
	वापस modes;
पूर्ण

अटल व्योम mlxsw_sx_from_ptys_speed_duplex(bool carrier_ok, u32 ptys_eth_proto,
					    काष्ठा ethtool_link_ksettings *cmd)
अणु
	u32 speed = SPEED_UNKNOWN;
	u8 duplex = DUPLEX_UNKNOWN;
	पूर्णांक i;

	अगर (!carrier_ok)
		जाओ out;

	क्रम (i = 0; i < MLXSW_SX_PORT_LINK_MODE_LEN; i++) अणु
		अगर (ptys_eth_proto & mlxsw_sx_port_link_mode[i].mask) अणु
			speed = mlxsw_sx_port_link_mode[i].speed;
			duplex = DUPLEX_FULL;
			अवरोध;
		पूर्ण
	पूर्ण
out:
	cmd->base.speed = speed;
	cmd->base.duplex = duplex;
पूर्ण

अटल u8 mlxsw_sx_port_connector_port(u32 ptys_eth_proto)
अणु
	अगर (ptys_eth_proto & (MLXSW_REG_PTYS_ETH_SPEED_10GBASE_SR |
			      MLXSW_REG_PTYS_ETH_SPEED_40GBASE_SR4 |
			      MLXSW_REG_PTYS_ETH_SPEED_100GBASE_SR4 |
			      MLXSW_REG_PTYS_ETH_SPEED_SGMII))
		वापस PORT_FIBRE;

	अगर (ptys_eth_proto & (MLXSW_REG_PTYS_ETH_SPEED_10GBASE_CR |
			      MLXSW_REG_PTYS_ETH_SPEED_40GBASE_CR4 |
			      MLXSW_REG_PTYS_ETH_SPEED_100GBASE_CR4))
		वापस PORT_DA;

	अगर (ptys_eth_proto & (MLXSW_REG_PTYS_ETH_SPEED_10GBASE_KR |
			      MLXSW_REG_PTYS_ETH_SPEED_10GBASE_KX4 |
			      MLXSW_REG_PTYS_ETH_SPEED_40GBASE_KR4 |
			      MLXSW_REG_PTYS_ETH_SPEED_100GBASE_KR4))
		वापस PORT_NONE;

	वापस PORT_OTHER;
पूर्ण

अटल पूर्णांक
mlxsw_sx_port_get_link_ksettings(काष्ठा net_device *dev,
				 काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा mlxsw_sx_port *mlxsw_sx_port = netdev_priv(dev);
	काष्ठा mlxsw_sx *mlxsw_sx = mlxsw_sx_port->mlxsw_sx;
	अक्षर ptys_pl[MLXSW_REG_PTYS_LEN];
	u32 eth_proto_cap;
	u32 eth_proto_admin;
	u32 eth_proto_oper;
	u32 supported, advertising, lp_advertising;
	पूर्णांक err;

	mlxsw_reg_ptys_eth_pack(ptys_pl, mlxsw_sx_port->local_port, 0, false);
	err = mlxsw_reg_query(mlxsw_sx->core, MLXSW_REG(ptys), ptys_pl);
	अगर (err) अणु
		netdev_err(dev, "Failed to get proto");
		वापस err;
	पूर्ण
	mlxsw_reg_ptys_eth_unpack(ptys_pl, &eth_proto_cap,
				  &eth_proto_admin, &eth_proto_oper);

	supported = mlxsw_sx_from_ptys_supported_port(eth_proto_cap) |
			 mlxsw_sx_from_ptys_supported_link(eth_proto_cap) |
			 SUPPORTED_Pause | SUPPORTED_Asym_Pause;
	advertising = mlxsw_sx_from_ptys_advert_link(eth_proto_admin);
	mlxsw_sx_from_ptys_speed_duplex(netअगर_carrier_ok(dev),
					eth_proto_oper, cmd);

	eth_proto_oper = eth_proto_oper ? eth_proto_oper : eth_proto_cap;
	cmd->base.port = mlxsw_sx_port_connector_port(eth_proto_oper);
	lp_advertising = mlxsw_sx_from_ptys_advert_link(eth_proto_oper);

	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.supported,
						supported);
	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.advertising,
						advertising);
	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.lp_advertising,
						lp_advertising);

	वापस 0;
पूर्ण

अटल u32 mlxsw_sx_to_ptys_advert_link(u32 advertising)
अणु
	u32 ptys_proto = 0;
	पूर्णांक i;

	क्रम (i = 0; i < MLXSW_SX_PORT_LINK_MODE_LEN; i++) अणु
		अगर (advertising & mlxsw_sx_port_link_mode[i].advertised)
			ptys_proto |= mlxsw_sx_port_link_mode[i].mask;
	पूर्ण
	वापस ptys_proto;
पूर्ण

अटल u32 mlxsw_sx_to_ptys_speed(u32 speed)
अणु
	u32 ptys_proto = 0;
	पूर्णांक i;

	क्रम (i = 0; i < MLXSW_SX_PORT_LINK_MODE_LEN; i++) अणु
		अगर (speed == mlxsw_sx_port_link_mode[i].speed)
			ptys_proto |= mlxsw_sx_port_link_mode[i].mask;
	पूर्ण
	वापस ptys_proto;
पूर्ण

अटल u32 mlxsw_sx_to_ptys_upper_speed(u32 upper_speed)
अणु
	u32 ptys_proto = 0;
	पूर्णांक i;

	क्रम (i = 0; i < MLXSW_SX_PORT_LINK_MODE_LEN; i++) अणु
		अगर (mlxsw_sx_port_link_mode[i].speed <= upper_speed)
			ptys_proto |= mlxsw_sx_port_link_mode[i].mask;
	पूर्ण
	वापस ptys_proto;
पूर्ण

अटल पूर्णांक
mlxsw_sx_port_set_link_ksettings(काष्ठा net_device *dev,
				 स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा mlxsw_sx_port *mlxsw_sx_port = netdev_priv(dev);
	काष्ठा mlxsw_sx *mlxsw_sx = mlxsw_sx_port->mlxsw_sx;
	अक्षर ptys_pl[MLXSW_REG_PTYS_LEN];
	u32 speed;
	u32 eth_proto_new;
	u32 eth_proto_cap;
	u32 eth_proto_admin;
	u32 advertising;
	bool is_up;
	पूर्णांक err;

	speed = cmd->base.speed;

	ethtool_convert_link_mode_to_legacy_u32(&advertising,
						cmd->link_modes.advertising);

	eth_proto_new = cmd->base.स्वतःneg == AUTONEG_ENABLE ?
		mlxsw_sx_to_ptys_advert_link(advertising) :
		mlxsw_sx_to_ptys_speed(speed);

	mlxsw_reg_ptys_eth_pack(ptys_pl, mlxsw_sx_port->local_port, 0, false);
	err = mlxsw_reg_query(mlxsw_sx->core, MLXSW_REG(ptys), ptys_pl);
	अगर (err) अणु
		netdev_err(dev, "Failed to get proto");
		वापस err;
	पूर्ण
	mlxsw_reg_ptys_eth_unpack(ptys_pl, &eth_proto_cap, &eth_proto_admin,
				  शून्य);

	eth_proto_new = eth_proto_new & eth_proto_cap;
	अगर (!eth_proto_new) अणु
		netdev_err(dev, "Not supported proto admin requested");
		वापस -EINVAL;
	पूर्ण
	अगर (eth_proto_new == eth_proto_admin)
		वापस 0;

	mlxsw_reg_ptys_eth_pack(ptys_pl, mlxsw_sx_port->local_port,
				eth_proto_new, true);
	err = mlxsw_reg_ग_लिखो(mlxsw_sx->core, MLXSW_REG(ptys), ptys_pl);
	अगर (err) अणु
		netdev_err(dev, "Failed to set proto admin");
		वापस err;
	पूर्ण

	err = mlxsw_sx_port_oper_status_get(mlxsw_sx_port, &is_up);
	अगर (err) अणु
		netdev_err(dev, "Failed to get oper status");
		वापस err;
	पूर्ण
	अगर (!is_up)
		वापस 0;

	err = mlxsw_sx_port_admin_status_set(mlxsw_sx_port, false);
	अगर (err) अणु
		netdev_err(dev, "Failed to set admin status");
		वापस err;
	पूर्ण

	err = mlxsw_sx_port_admin_status_set(mlxsw_sx_port, true);
	अगर (err) अणु
		netdev_err(dev, "Failed to set admin status");
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops mlxsw_sx_port_ethtool_ops = अणु
	.get_drvinfo		= mlxsw_sx_port_get_drvinfo,
	.get_link		= ethtool_op_get_link,
	.get_strings		= mlxsw_sx_port_get_strings,
	.get_ethtool_stats	= mlxsw_sx_port_get_stats,
	.get_sset_count		= mlxsw_sx_port_get_sset_count,
	.get_link_ksettings	= mlxsw_sx_port_get_link_ksettings,
	.set_link_ksettings	= mlxsw_sx_port_set_link_ksettings,
पूर्ण;

अटल पूर्णांक mlxsw_sx_hw_id_get(काष्ठा mlxsw_sx *mlxsw_sx)
अणु
	अक्षर spad_pl[MLXSW_REG_SPAD_LEN] = अणु0पूर्ण;
	पूर्णांक err;

	err = mlxsw_reg_query(mlxsw_sx->core, MLXSW_REG(spad), spad_pl);
	अगर (err)
		वापस err;
	mlxsw_reg_spad_base_mac_स_नकल_from(spad_pl, mlxsw_sx->hw_id);
	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_sx_port_dev_addr_get(काष्ठा mlxsw_sx_port *mlxsw_sx_port)
अणु
	काष्ठा mlxsw_sx *mlxsw_sx = mlxsw_sx_port->mlxsw_sx;
	काष्ठा net_device *dev = mlxsw_sx_port->dev;
	अक्षर ppad_pl[MLXSW_REG_PPAD_LEN];
	पूर्णांक err;

	mlxsw_reg_ppad_pack(ppad_pl, false, 0);
	err = mlxsw_reg_query(mlxsw_sx->core, MLXSW_REG(ppad), ppad_pl);
	अगर (err)
		वापस err;
	mlxsw_reg_ppad_mac_स_नकल_from(ppad_pl, dev->dev_addr);
	/* The last byte value in base mac address is guaranteed
	 * to be such it करोes not overflow when adding local_port
	 * value.
	 */
	dev->dev_addr[ETH_ALEN - 1] += mlxsw_sx_port->local_port;
	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_sx_port_stp_state_set(काष्ठा mlxsw_sx_port *mlxsw_sx_port,
				       u16 vid, क्रमागत mlxsw_reg_spms_state state)
अणु
	काष्ठा mlxsw_sx *mlxsw_sx = mlxsw_sx_port->mlxsw_sx;
	अक्षर *spms_pl;
	पूर्णांक err;

	spms_pl = kदो_स्मृति(MLXSW_REG_SPMS_LEN, GFP_KERNEL);
	अगर (!spms_pl)
		वापस -ENOMEM;
	mlxsw_reg_spms_pack(spms_pl, mlxsw_sx_port->local_port);
	mlxsw_reg_spms_vid_pack(spms_pl, vid, state);
	err = mlxsw_reg_ग_लिखो(mlxsw_sx->core, MLXSW_REG(spms), spms_pl);
	kमुक्त(spms_pl);
	वापस err;
पूर्ण

अटल पूर्णांक mlxsw_sx_port_ib_speed_set(काष्ठा mlxsw_sx_port *mlxsw_sx_port,
				      u16 speed, u16 width)
अणु
	काष्ठा mlxsw_sx *mlxsw_sx = mlxsw_sx_port->mlxsw_sx;
	अक्षर ptys_pl[MLXSW_REG_PTYS_LEN];

	mlxsw_reg_ptys_ib_pack(ptys_pl, mlxsw_sx_port->local_port, speed,
			       width);
	वापस mlxsw_reg_ग_लिखो(mlxsw_sx->core, MLXSW_REG(ptys), ptys_pl);
पूर्ण

अटल पूर्णांक
mlxsw_sx_port_speed_by_width_set(काष्ठा mlxsw_sx_port *mlxsw_sx_port, u8 width)
अणु
	काष्ठा mlxsw_sx *mlxsw_sx = mlxsw_sx_port->mlxsw_sx;
	u32 upper_speed = MLXSW_SX_PORT_BASE_SPEED * width;
	अक्षर ptys_pl[MLXSW_REG_PTYS_LEN];
	u32 eth_proto_admin;

	eth_proto_admin = mlxsw_sx_to_ptys_upper_speed(upper_speed);
	mlxsw_reg_ptys_eth_pack(ptys_pl, mlxsw_sx_port->local_port,
				eth_proto_admin, true);
	वापस mlxsw_reg_ग_लिखो(mlxsw_sx->core, MLXSW_REG(ptys), ptys_pl);
पूर्ण

अटल पूर्णांक
mlxsw_sx_port_mac_learning_mode_set(काष्ठा mlxsw_sx_port *mlxsw_sx_port,
				    क्रमागत mlxsw_reg_spmlr_learn_mode mode)
अणु
	काष्ठा mlxsw_sx *mlxsw_sx = mlxsw_sx_port->mlxsw_sx;
	अक्षर spmlr_pl[MLXSW_REG_SPMLR_LEN];

	mlxsw_reg_spmlr_pack(spmlr_pl, mlxsw_sx_port->local_port, mode);
	वापस mlxsw_reg_ग_लिखो(mlxsw_sx->core, MLXSW_REG(spmlr), spmlr_pl);
पूर्ण

अटल पूर्णांक __mlxsw_sx_port_eth_create(काष्ठा mlxsw_sx *mlxsw_sx, u8 local_port,
				      u8 module, u8 width)
अणु
	काष्ठा mlxsw_sx_port *mlxsw_sx_port;
	काष्ठा net_device *dev;
	पूर्णांक err;

	dev = alloc_etherdev(माप(काष्ठा mlxsw_sx_port));
	अगर (!dev)
		वापस -ENOMEM;
	SET_NETDEV_DEV(dev, mlxsw_sx->bus_info->dev);
	dev_net_set(dev, mlxsw_core_net(mlxsw_sx->core));
	mlxsw_sx_port = netdev_priv(dev);
	mlxsw_sx_port->dev = dev;
	mlxsw_sx_port->mlxsw_sx = mlxsw_sx;
	mlxsw_sx_port->local_port = local_port;
	mlxsw_sx_port->mapping.module = module;

	mlxsw_sx_port->pcpu_stats =
		netdev_alloc_pcpu_stats(काष्ठा mlxsw_sx_port_pcpu_stats);
	अगर (!mlxsw_sx_port->pcpu_stats) अणु
		err = -ENOMEM;
		जाओ err_alloc_stats;
	पूर्ण

	dev->netdev_ops = &mlxsw_sx_port_netdev_ops;
	dev->ethtool_ops = &mlxsw_sx_port_ethtool_ops;

	err = mlxsw_sx_port_dev_addr_get(mlxsw_sx_port);
	अगर (err) अणु
		dev_err(mlxsw_sx->bus_info->dev, "Port %d: Unable to get port mac address\n",
			mlxsw_sx_port->local_port);
		जाओ err_dev_addr_get;
	पूर्ण

	netअगर_carrier_off(dev);

	dev->features |= NETIF_F_NETNS_LOCAL | NETIF_F_LLTX | NETIF_F_SG |
			 NETIF_F_VLAN_CHALLENGED;

	dev->min_mtu = 0;
	dev->max_mtu = ETH_MAX_MTU;

	/* Each packet needs to have a Tx header (metadata) on top all other
	 * headers.
	 */
	dev->needed_headroom = MLXSW_TXHDR_LEN;

	err = mlxsw_sx_port_प्रणाली_port_mapping_set(mlxsw_sx_port);
	अगर (err) अणु
		dev_err(mlxsw_sx->bus_info->dev, "Port %d: Failed to set system port mapping\n",
			mlxsw_sx_port->local_port);
		जाओ err_port_प्रणाली_port_mapping_set;
	पूर्ण

	err = mlxsw_sx_port_swid_set(mlxsw_sx_port, 0);
	अगर (err) अणु
		dev_err(mlxsw_sx->bus_info->dev, "Port %d: Failed to set SWID\n",
			mlxsw_sx_port->local_port);
		जाओ err_port_swid_set;
	पूर्ण

	err = mlxsw_sx_port_speed_by_width_set(mlxsw_sx_port, width);
	अगर (err) अणु
		dev_err(mlxsw_sx->bus_info->dev, "Port %d: Failed to set speed\n",
			mlxsw_sx_port->local_port);
		जाओ err_port_speed_set;
	पूर्ण

	err = mlxsw_sx_port_mtu_eth_set(mlxsw_sx_port, ETH_DATA_LEN);
	अगर (err) अणु
		dev_err(mlxsw_sx->bus_info->dev, "Port %d: Failed to set MTU\n",
			mlxsw_sx_port->local_port);
		जाओ err_port_mtu_set;
	पूर्ण

	err = mlxsw_sx_port_admin_status_set(mlxsw_sx_port, false);
	अगर (err)
		जाओ err_port_admin_status_set;

	err = mlxsw_sx_port_stp_state_set(mlxsw_sx_port,
					  MLXSW_PORT_DEFAULT_VID,
					  MLXSW_REG_SPMS_STATE_FORWARDING);
	अगर (err) अणु
		dev_err(mlxsw_sx->bus_info->dev, "Port %d: Failed to set STP state\n",
			mlxsw_sx_port->local_port);
		जाओ err_port_stp_state_set;
	पूर्ण

	err = mlxsw_sx_port_mac_learning_mode_set(mlxsw_sx_port,
						  MLXSW_REG_SPMLR_LEARN_MODE_DISABLE);
	अगर (err) अणु
		dev_err(mlxsw_sx->bus_info->dev, "Port %d: Failed to set MAC learning mode\n",
			mlxsw_sx_port->local_port);
		जाओ err_port_mac_learning_mode_set;
	पूर्ण

	err = रेजिस्टर_netdev(dev);
	अगर (err) अणु
		dev_err(mlxsw_sx->bus_info->dev, "Port %d: Failed to register netdev\n",
			mlxsw_sx_port->local_port);
		जाओ err_रेजिस्टर_netdev;
	पूर्ण

	mlxsw_core_port_eth_set(mlxsw_sx->core, mlxsw_sx_port->local_port,
				mlxsw_sx_port, dev);
	mlxsw_sx->ports[local_port] = mlxsw_sx_port;
	वापस 0;

err_रेजिस्टर_netdev:
err_port_mac_learning_mode_set:
err_port_stp_state_set:
err_port_admin_status_set:
err_port_mtu_set:
err_port_speed_set:
	mlxsw_sx_port_swid_set(mlxsw_sx_port, MLXSW_PORT_SWID_DISABLED_PORT);
err_port_swid_set:
err_port_प्रणाली_port_mapping_set:
err_dev_addr_get:
	मुक्त_percpu(mlxsw_sx_port->pcpu_stats);
err_alloc_stats:
	मुक्त_netdev(dev);
	वापस err;
पूर्ण

अटल पूर्णांक mlxsw_sx_port_eth_create(काष्ठा mlxsw_sx *mlxsw_sx, u8 local_port,
				    u8 module, u8 width)
अणु
	पूर्णांक err;

	err = mlxsw_core_port_init(mlxsw_sx->core, local_port,
				   module + 1, false, 0, false, 0,
				   mlxsw_sx->hw_id, माप(mlxsw_sx->hw_id));
	अगर (err) अणु
		dev_err(mlxsw_sx->bus_info->dev, "Port %d: Failed to init core port\n",
			local_port);
		वापस err;
	पूर्ण
	err = __mlxsw_sx_port_eth_create(mlxsw_sx, local_port, module, width);
	अगर (err)
		जाओ err_port_create;

	वापस 0;

err_port_create:
	mlxsw_core_port_fini(mlxsw_sx->core, local_port);
	वापस err;
पूर्ण

अटल व्योम __mlxsw_sx_port_eth_हटाओ(काष्ठा mlxsw_sx *mlxsw_sx, u8 local_port)
अणु
	काष्ठा mlxsw_sx_port *mlxsw_sx_port = mlxsw_sx->ports[local_port];

	mlxsw_core_port_clear(mlxsw_sx->core, local_port, mlxsw_sx);
	unरेजिस्टर_netdev(mlxsw_sx_port->dev); /* This calls nकरो_stop */
	mlxsw_sx->ports[local_port] = शून्य;
	mlxsw_sx_port_swid_set(mlxsw_sx_port, MLXSW_PORT_SWID_DISABLED_PORT);
	मुक्त_percpu(mlxsw_sx_port->pcpu_stats);
	मुक्त_netdev(mlxsw_sx_port->dev);
पूर्ण

अटल bool mlxsw_sx_port_created(काष्ठा mlxsw_sx *mlxsw_sx, u8 local_port)
अणु
	वापस mlxsw_sx->ports[local_port] != शून्य;
पूर्ण

अटल पूर्णांक __mlxsw_sx_port_ib_create(काष्ठा mlxsw_sx *mlxsw_sx, u8 local_port,
				     u8 module, u8 width)
अणु
	काष्ठा mlxsw_sx_port *mlxsw_sx_port;
	पूर्णांक err;

	mlxsw_sx_port = kzalloc(माप(*mlxsw_sx_port), GFP_KERNEL);
	अगर (!mlxsw_sx_port)
		वापस -ENOMEM;
	mlxsw_sx_port->mlxsw_sx = mlxsw_sx;
	mlxsw_sx_port->local_port = local_port;
	mlxsw_sx_port->mapping.module = module;

	err = mlxsw_sx_port_प्रणाली_port_mapping_set(mlxsw_sx_port);
	अगर (err) अणु
		dev_err(mlxsw_sx->bus_info->dev, "Port %d: Failed to set system port mapping\n",
			mlxsw_sx_port->local_port);
		जाओ err_port_प्रणाली_port_mapping_set;
	पूर्ण

	/* Adding port to Infiniband swid (1) */
	err = mlxsw_sx_port_swid_set(mlxsw_sx_port, 1);
	अगर (err) अणु
		dev_err(mlxsw_sx->bus_info->dev, "Port %d: Failed to set SWID\n",
			mlxsw_sx_port->local_port);
		जाओ err_port_swid_set;
	पूर्ण

	/* Expose the IB port number as it's front panel name */
	err = mlxsw_sx_port_ib_port_set(mlxsw_sx_port, module + 1);
	अगर (err) अणु
		dev_err(mlxsw_sx->bus_info->dev, "Port %d: Failed to set IB port\n",
			mlxsw_sx_port->local_port);
		जाओ err_port_ib_set;
	पूर्ण

	/* Supports all speeds from SDR to FDR (biपंचांगask) and support bus width
	 * of 1x, 2x and 4x (3 bits biपंचांगask)
	 */
	err = mlxsw_sx_port_ib_speed_set(mlxsw_sx_port,
					 MLXSW_REG_PTYS_IB_SPEED_EDR - 1,
					 BIT(3) - 1);
	अगर (err) अणु
		dev_err(mlxsw_sx->bus_info->dev, "Port %d: Failed to set speed\n",
			mlxsw_sx_port->local_port);
		जाओ err_port_speed_set;
	पूर्ण

	/* Change to the maximum MTU the device supports, the SMA will take
	 * care of the active MTU
	 */
	err = mlxsw_sx_port_mtu_ib_set(mlxsw_sx_port, MLXSW_IB_DEFAULT_MTU);
	अगर (err) अणु
		dev_err(mlxsw_sx->bus_info->dev, "Port %d: Failed to set MTU\n",
			mlxsw_sx_port->local_port);
		जाओ err_port_mtu_set;
	पूर्ण

	err = mlxsw_sx_port_admin_status_set(mlxsw_sx_port, true);
	अगर (err) अणु
		dev_err(mlxsw_sx->bus_info->dev, "Port %d: Failed to change admin state to UP\n",
			mlxsw_sx_port->local_port);
		जाओ err_port_admin_set;
	पूर्ण

	mlxsw_core_port_ib_set(mlxsw_sx->core, mlxsw_sx_port->local_port,
			       mlxsw_sx_port);
	mlxsw_sx->ports[local_port] = mlxsw_sx_port;
	वापस 0;

err_port_admin_set:
err_port_mtu_set:
err_port_speed_set:
err_port_ib_set:
	mlxsw_sx_port_swid_set(mlxsw_sx_port, MLXSW_PORT_SWID_DISABLED_PORT);
err_port_swid_set:
err_port_प्रणाली_port_mapping_set:
	kमुक्त(mlxsw_sx_port);
	वापस err;
पूर्ण

अटल व्योम __mlxsw_sx_port_ib_हटाओ(काष्ठा mlxsw_sx *mlxsw_sx, u8 local_port)
अणु
	काष्ठा mlxsw_sx_port *mlxsw_sx_port = mlxsw_sx->ports[local_port];

	mlxsw_core_port_clear(mlxsw_sx->core, local_port, mlxsw_sx);
	mlxsw_sx->ports[local_port] = शून्य;
	mlxsw_sx_port_admin_status_set(mlxsw_sx_port, false);
	mlxsw_sx_port_swid_set(mlxsw_sx_port, MLXSW_PORT_SWID_DISABLED_PORT);
	kमुक्त(mlxsw_sx_port);
पूर्ण

अटल व्योम __mlxsw_sx_port_हटाओ(काष्ठा mlxsw_sx *mlxsw_sx, u8 local_port)
अणु
	क्रमागत devlink_port_type port_type =
		mlxsw_core_port_type_get(mlxsw_sx->core, local_port);

	अगर (port_type == DEVLINK_PORT_TYPE_ETH)
		__mlxsw_sx_port_eth_हटाओ(mlxsw_sx, local_port);
	अन्यथा अगर (port_type == DEVLINK_PORT_TYPE_IB)
		__mlxsw_sx_port_ib_हटाओ(mlxsw_sx, local_port);
पूर्ण

अटल व्योम mlxsw_sx_port_हटाओ(काष्ठा mlxsw_sx *mlxsw_sx, u8 local_port)
अणु
	__mlxsw_sx_port_हटाओ(mlxsw_sx, local_port);
	mlxsw_core_port_fini(mlxsw_sx->core, local_port);
पूर्ण

अटल व्योम mlxsw_sx_ports_हटाओ(काष्ठा mlxsw_sx *mlxsw_sx)
अणु
	पूर्णांक i;

	क्रम (i = 1; i < mlxsw_core_max_ports(mlxsw_sx->core); i++)
		अगर (mlxsw_sx_port_created(mlxsw_sx, i))
			mlxsw_sx_port_हटाओ(mlxsw_sx, i);
	kमुक्त(mlxsw_sx->ports);
	mlxsw_sx->ports = शून्य;
पूर्ण

अटल पूर्णांक mlxsw_sx_ports_create(काष्ठा mlxsw_sx *mlxsw_sx)
अणु
	अचिन्हित पूर्णांक max_ports = mlxsw_core_max_ports(mlxsw_sx->core);
	माप_प्रकार alloc_size;
	u8 module, width;
	पूर्णांक i;
	पूर्णांक err;

	alloc_size = माप(काष्ठा mlxsw_sx_port *) * max_ports;
	mlxsw_sx->ports = kzalloc(alloc_size, GFP_KERNEL);
	अगर (!mlxsw_sx->ports)
		वापस -ENOMEM;

	क्रम (i = 1; i < max_ports; i++) अणु
		err = mlxsw_sx_port_module_info_get(mlxsw_sx, i, &module,
						    &width);
		अगर (err)
			जाओ err_port_module_info_get;
		अगर (!width)
			जारी;
		err = mlxsw_sx_port_eth_create(mlxsw_sx, i, module, width);
		अगर (err)
			जाओ err_port_create;
	पूर्ण
	वापस 0;

err_port_create:
err_port_module_info_get:
	क्रम (i--; i >= 1; i--)
		अगर (mlxsw_sx_port_created(mlxsw_sx, i))
			mlxsw_sx_port_हटाओ(mlxsw_sx, i);
	kमुक्त(mlxsw_sx->ports);
	mlxsw_sx->ports = शून्य;
	वापस err;
पूर्ण

अटल व्योम mlxsw_sx_pude_eth_event_func(काष्ठा mlxsw_sx_port *mlxsw_sx_port,
					 क्रमागत mlxsw_reg_pude_oper_status status)
अणु
	अगर (status == MLXSW_PORT_OPER_STATUS_UP) अणु
		netdev_info(mlxsw_sx_port->dev, "link up\n");
		netअगर_carrier_on(mlxsw_sx_port->dev);
	पूर्ण अन्यथा अणु
		netdev_info(mlxsw_sx_port->dev, "link down\n");
		netअगर_carrier_off(mlxsw_sx_port->dev);
	पूर्ण
पूर्ण

अटल व्योम mlxsw_sx_pude_ib_event_func(काष्ठा mlxsw_sx_port *mlxsw_sx_port,
					क्रमागत mlxsw_reg_pude_oper_status status)
अणु
	अगर (status == MLXSW_PORT_OPER_STATUS_UP)
		pr_info("ib link for port %d - up\n",
			mlxsw_sx_port->mapping.module + 1);
	अन्यथा
		pr_info("ib link for port %d - down\n",
			mlxsw_sx_port->mapping.module + 1);
पूर्ण

अटल व्योम mlxsw_sx_pude_event_func(स्थिर काष्ठा mlxsw_reg_info *reg,
				     अक्षर *pude_pl, व्योम *priv)
अणु
	काष्ठा mlxsw_sx *mlxsw_sx = priv;
	काष्ठा mlxsw_sx_port *mlxsw_sx_port;
	क्रमागत mlxsw_reg_pude_oper_status status;
	क्रमागत devlink_port_type port_type;
	u8 local_port;

	local_port = mlxsw_reg_pude_local_port_get(pude_pl);
	mlxsw_sx_port = mlxsw_sx->ports[local_port];
	अगर (!mlxsw_sx_port) अणु
		dev_warn(mlxsw_sx->bus_info->dev, "Port %d: Link event received for non-existent port\n",
			 local_port);
		वापस;
	पूर्ण

	status = mlxsw_reg_pude_oper_status_get(pude_pl);
	port_type = mlxsw_core_port_type_get(mlxsw_sx->core, local_port);
	अगर (port_type == DEVLINK_PORT_TYPE_ETH)
		mlxsw_sx_pude_eth_event_func(mlxsw_sx_port, status);
	अन्यथा अगर (port_type == DEVLINK_PORT_TYPE_IB)
		mlxsw_sx_pude_ib_event_func(mlxsw_sx_port, status);
पूर्ण

अटल व्योम mlxsw_sx_rx_listener_func(काष्ठा sk_buff *skb, u8 local_port,
				      व्योम *priv)
अणु
	काष्ठा mlxsw_sx *mlxsw_sx = priv;
	काष्ठा mlxsw_sx_port *mlxsw_sx_port = mlxsw_sx->ports[local_port];
	काष्ठा mlxsw_sx_port_pcpu_stats *pcpu_stats;

	अगर (unlikely(!mlxsw_sx_port)) अणु
		dev_warn_ratelimited(mlxsw_sx->bus_info->dev, "Port %d: skb received for non-existent port\n",
				     local_port);
		वापस;
	पूर्ण

	skb->dev = mlxsw_sx_port->dev;

	pcpu_stats = this_cpu_ptr(mlxsw_sx_port->pcpu_stats);
	u64_stats_update_begin(&pcpu_stats->syncp);
	pcpu_stats->rx_packets++;
	pcpu_stats->rx_bytes += skb->len;
	u64_stats_update_end(&pcpu_stats->syncp);

	skb->protocol = eth_type_trans(skb, skb->dev);
	netअगर_receive_skb(skb);
पूर्ण

अटल पूर्णांक mlxsw_sx_port_type_set(काष्ठा mlxsw_core *mlxsw_core, u8 local_port,
				  क्रमागत devlink_port_type new_type)
अणु
	काष्ठा mlxsw_sx *mlxsw_sx = mlxsw_core_driver_priv(mlxsw_core);
	u8 module, width;
	पूर्णांक err;

	अगर (!mlxsw_sx->ports || !mlxsw_sx->ports[local_port]) अणु
		dev_err(mlxsw_sx->bus_info->dev, "Port number \"%d\" does not exist\n",
			local_port);
		वापस -EINVAL;
	पूर्ण

	अगर (new_type == DEVLINK_PORT_TYPE_AUTO)
		वापस -EOPNOTSUPP;

	__mlxsw_sx_port_हटाओ(mlxsw_sx, local_port);
	err = mlxsw_sx_port_module_info_get(mlxsw_sx, local_port, &module,
					    &width);
	अगर (err)
		जाओ err_port_module_info_get;

	अगर (new_type == DEVLINK_PORT_TYPE_ETH)
		err = __mlxsw_sx_port_eth_create(mlxsw_sx, local_port, module,
						 width);
	अन्यथा अगर (new_type == DEVLINK_PORT_TYPE_IB)
		err = __mlxsw_sx_port_ib_create(mlxsw_sx, local_port, module,
						width);

err_port_module_info_get:
	वापस err;
पूर्ण

क्रमागत अणु
	MLXSW_REG_HTGT_TRAP_GROUP_SX2_RX = 1,
	MLXSW_REG_HTGT_TRAP_GROUP_SX2_CTRL = 2,
पूर्ण;

#घोषणा MLXSW_SX_RXL(_trap_id) \
	MLXSW_RXL(mlxsw_sx_rx_listener_func, _trap_id, TRAP_TO_CPU,	\
		  false, SX2_RX, FORWARD)

अटल स्थिर काष्ठा mlxsw_listener mlxsw_sx_listener[] = अणु
	MLXSW_EVENTL(mlxsw_sx_pude_event_func, PUDE, EMAD),
	MLXSW_SX_RXL(FDB_MC),
	MLXSW_SX_RXL(STP),
	MLXSW_SX_RXL(LACP),
	MLXSW_SX_RXL(EAPOL),
	MLXSW_SX_RXL(LLDP),
	MLXSW_SX_RXL(MMRP),
	MLXSW_SX_RXL(MVRP),
	MLXSW_SX_RXL(RPVST),
	MLXSW_SX_RXL(DHCP),
	MLXSW_SX_RXL(IGMP_QUERY),
	MLXSW_SX_RXL(IGMP_V1_REPORT),
	MLXSW_SX_RXL(IGMP_V2_REPORT),
	MLXSW_SX_RXL(IGMP_V2_LEAVE),
	MLXSW_SX_RXL(IGMP_V3_REPORT),
पूर्ण;

अटल पूर्णांक mlxsw_sx_traps_init(काष्ठा mlxsw_sx *mlxsw_sx)
अणु
	अक्षर htgt_pl[MLXSW_REG_HTGT_LEN];
	पूर्णांक i;
	पूर्णांक err;

	mlxsw_reg_htgt_pack(htgt_pl, MLXSW_REG_HTGT_TRAP_GROUP_SX2_RX,
			    MLXSW_REG_HTGT_INVALID_POLICER,
			    MLXSW_REG_HTGT_DEFAULT_PRIORITY,
			    MLXSW_REG_HTGT_DEFAULT_TC);
	mlxsw_reg_htgt_local_path_rdq_set(htgt_pl,
					  MLXSW_REG_HTGT_LOCAL_PATH_RDQ_SX2_RX);

	err = mlxsw_reg_ग_लिखो(mlxsw_sx->core, MLXSW_REG(htgt), htgt_pl);
	अगर (err)
		वापस err;

	mlxsw_reg_htgt_pack(htgt_pl, MLXSW_REG_HTGT_TRAP_GROUP_SX2_CTRL,
			    MLXSW_REG_HTGT_INVALID_POLICER,
			    MLXSW_REG_HTGT_DEFAULT_PRIORITY,
			    MLXSW_REG_HTGT_DEFAULT_TC);
	mlxsw_reg_htgt_local_path_rdq_set(htgt_pl,
					MLXSW_REG_HTGT_LOCAL_PATH_RDQ_SX2_CTRL);

	err = mlxsw_reg_ग_लिखो(mlxsw_sx->core, MLXSW_REG(htgt), htgt_pl);
	अगर (err)
		वापस err;

	क्रम (i = 0; i < ARRAY_SIZE(mlxsw_sx_listener); i++) अणु
		err = mlxsw_core_trap_रेजिस्टर(mlxsw_sx->core,
					       &mlxsw_sx_listener[i],
					       mlxsw_sx);
		अगर (err)
			जाओ err_listener_रेजिस्टर;

	पूर्ण
	वापस 0;

err_listener_रेजिस्टर:
	क्रम (i--; i >= 0; i--) अणु
		mlxsw_core_trap_unरेजिस्टर(mlxsw_sx->core,
					   &mlxsw_sx_listener[i],
					   mlxsw_sx);
	पूर्ण
	वापस err;
पूर्ण

अटल व्योम mlxsw_sx_traps_fini(काष्ठा mlxsw_sx *mlxsw_sx)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(mlxsw_sx_listener); i++) अणु
		mlxsw_core_trap_unरेजिस्टर(mlxsw_sx->core,
					   &mlxsw_sx_listener[i],
					   mlxsw_sx);
	पूर्ण
पूर्ण

अटल पूर्णांक mlxsw_sx_flood_init(काष्ठा mlxsw_sx *mlxsw_sx)
अणु
	अक्षर sfgc_pl[MLXSW_REG_SFGC_LEN];
	अक्षर sgcr_pl[MLXSW_REG_SGCR_LEN];
	अक्षर *sftr_pl;
	पूर्णांक err;

	/* Configure a flooding table, which includes only CPU port. */
	sftr_pl = kदो_स्मृति(MLXSW_REG_SFTR_LEN, GFP_KERNEL);
	अगर (!sftr_pl)
		वापस -ENOMEM;
	mlxsw_reg_sftr_pack(sftr_pl, 0, 0, MLXSW_REG_SFGC_TABLE_TYPE_SINGLE, 0,
			    MLXSW_PORT_CPU_PORT, true);
	err = mlxsw_reg_ग_लिखो(mlxsw_sx->core, MLXSW_REG(sftr), sftr_pl);
	kमुक्त(sftr_pl);
	अगर (err)
		वापस err;

	/* Flood dअगरferent packet types using the flooding table. */
	mlxsw_reg_sfgc_pack(sfgc_pl,
			    MLXSW_REG_SFGC_TYPE_UNKNOWN_UNICAST,
			    MLXSW_REG_SFGC_BRIDGE_TYPE_1Q_FID,
			    MLXSW_REG_SFGC_TABLE_TYPE_SINGLE,
			    0);
	err = mlxsw_reg_ग_लिखो(mlxsw_sx->core, MLXSW_REG(sfgc), sfgc_pl);
	अगर (err)
		वापस err;

	mlxsw_reg_sfgc_pack(sfgc_pl,
			    MLXSW_REG_SFGC_TYPE_BROADCAST,
			    MLXSW_REG_SFGC_BRIDGE_TYPE_1Q_FID,
			    MLXSW_REG_SFGC_TABLE_TYPE_SINGLE,
			    0);
	err = mlxsw_reg_ग_लिखो(mlxsw_sx->core, MLXSW_REG(sfgc), sfgc_pl);
	अगर (err)
		वापस err;

	mlxsw_reg_sfgc_pack(sfgc_pl,
			    MLXSW_REG_SFGC_TYPE_UNREGISTERED_MULTICAST_NON_IP,
			    MLXSW_REG_SFGC_BRIDGE_TYPE_1Q_FID,
			    MLXSW_REG_SFGC_TABLE_TYPE_SINGLE,
			    0);
	err = mlxsw_reg_ग_लिखो(mlxsw_sx->core, MLXSW_REG(sfgc), sfgc_pl);
	अगर (err)
		वापस err;

	mlxsw_reg_sfgc_pack(sfgc_pl,
			    MLXSW_REG_SFGC_TYPE_UNREGISTERED_MULTICAST_IPV6,
			    MLXSW_REG_SFGC_BRIDGE_TYPE_1Q_FID,
			    MLXSW_REG_SFGC_TABLE_TYPE_SINGLE,
			    0);
	err = mlxsw_reg_ग_लिखो(mlxsw_sx->core, MLXSW_REG(sfgc), sfgc_pl);
	अगर (err)
		वापस err;

	mlxsw_reg_sfgc_pack(sfgc_pl,
			    MLXSW_REG_SFGC_TYPE_UNREGISTERED_MULTICAST_IPV4,
			    MLXSW_REG_SFGC_BRIDGE_TYPE_1Q_FID,
			    MLXSW_REG_SFGC_TABLE_TYPE_SINGLE,
			    0);
	err = mlxsw_reg_ग_लिखो(mlxsw_sx->core, MLXSW_REG(sfgc), sfgc_pl);
	अगर (err)
		वापस err;

	mlxsw_reg_sgcr_pack(sgcr_pl, true);
	वापस mlxsw_reg_ग_लिखो(mlxsw_sx->core, MLXSW_REG(sgcr), sgcr_pl);
पूर्ण

अटल पूर्णांक mlxsw_sx_basic_trap_groups_set(काष्ठा mlxsw_core *mlxsw_core)
अणु
	अक्षर htgt_pl[MLXSW_REG_HTGT_LEN];

	mlxsw_reg_htgt_pack(htgt_pl, MLXSW_REG_HTGT_TRAP_GROUP_EMAD,
			    MLXSW_REG_HTGT_INVALID_POLICER,
			    MLXSW_REG_HTGT_DEFAULT_PRIORITY,
			    MLXSW_REG_HTGT_DEFAULT_TC);
	mlxsw_reg_htgt_swid_set(htgt_pl, MLXSW_PORT_SWID_ALL_SWIDS);
	mlxsw_reg_htgt_local_path_rdq_set(htgt_pl,
					MLXSW_REG_HTGT_LOCAL_PATH_RDQ_SX2_EMAD);
	वापस mlxsw_reg_ग_लिखो(mlxsw_core, MLXSW_REG(htgt), htgt_pl);
पूर्ण

अटल पूर्णांक mlxsw_sx_init(काष्ठा mlxsw_core *mlxsw_core,
			 स्थिर काष्ठा mlxsw_bus_info *mlxsw_bus_info,
			 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlxsw_sx *mlxsw_sx = mlxsw_core_driver_priv(mlxsw_core);
	पूर्णांक err;

	mlxsw_sx->core = mlxsw_core;
	mlxsw_sx->bus_info = mlxsw_bus_info;

	err = mlxsw_sx_hw_id_get(mlxsw_sx);
	अगर (err) अणु
		dev_err(mlxsw_sx->bus_info->dev, "Failed to get switch HW ID\n");
		वापस err;
	पूर्ण

	err = mlxsw_sx_ports_create(mlxsw_sx);
	अगर (err) अणु
		dev_err(mlxsw_sx->bus_info->dev, "Failed to create ports\n");
		वापस err;
	पूर्ण

	err = mlxsw_sx_traps_init(mlxsw_sx);
	अगर (err) अणु
		dev_err(mlxsw_sx->bus_info->dev, "Failed to set traps\n");
		जाओ err_listener_रेजिस्टर;
	पूर्ण

	err = mlxsw_sx_flood_init(mlxsw_sx);
	अगर (err) अणु
		dev_err(mlxsw_sx->bus_info->dev, "Failed to initialize flood tables\n");
		जाओ err_flood_init;
	पूर्ण

	वापस 0;

err_flood_init:
	mlxsw_sx_traps_fini(mlxsw_sx);
err_listener_रेजिस्टर:
	mlxsw_sx_ports_हटाओ(mlxsw_sx);
	वापस err;
पूर्ण

अटल व्योम mlxsw_sx_fini(काष्ठा mlxsw_core *mlxsw_core)
अणु
	काष्ठा mlxsw_sx *mlxsw_sx = mlxsw_core_driver_priv(mlxsw_core);

	mlxsw_sx_traps_fini(mlxsw_sx);
	mlxsw_sx_ports_हटाओ(mlxsw_sx);
पूर्ण

अटल स्थिर काष्ठा mlxsw_config_profile mlxsw_sx_config_profile = अणु
	.used_max_vepa_channels		= 1,
	.max_vepa_channels		= 0,
	.used_max_mid			= 1,
	.max_mid			= 7000,
	.used_max_pgt			= 1,
	.max_pgt			= 0,
	.used_max_प्रणाली_port		= 1,
	.max_प्रणाली_port		= 48000,
	.used_max_vlan_groups		= 1,
	.max_vlan_groups		= 127,
	.used_max_regions		= 1,
	.max_regions			= 400,
	.used_flood_tables		= 1,
	.max_flood_tables		= 2,
	.max_vid_flood_tables		= 1,
	.used_flood_mode		= 1,
	.flood_mode			= 3,
	.used_max_ib_mc			= 1,
	.max_ib_mc			= 6,
	.used_max_pkey			= 1,
	.max_pkey			= 0,
	.swid_config			= अणु
		अणु
			.used_type	= 1,
			.type		= MLXSW_PORT_SWID_TYPE_ETH,
		पूर्ण,
		अणु
			.used_type	= 1,
			.type		= MLXSW_PORT_SWID_TYPE_IB,
		पूर्ण
	पूर्ण,
पूर्ण;

अटल काष्ठा mlxsw_driver mlxsw_sx_driver = अणु
	.kind			= mlxsw_sx_driver_name,
	.priv_size		= माप(काष्ठा mlxsw_sx),
	.init			= mlxsw_sx_init,
	.fini			= mlxsw_sx_fini,
	.basic_trap_groups_set	= mlxsw_sx_basic_trap_groups_set,
	.txhdr_स्थिरruct	= mlxsw_sx_txhdr_स्थिरruct,
	.txhdr_len		= MLXSW_TXHDR_LEN,
	.profile		= &mlxsw_sx_config_profile,
	.port_type_set		= mlxsw_sx_port_type_set,
पूर्ण;

अटल स्थिर काष्ठा pci_device_id mlxsw_sx_pci_id_table[] = अणु
	अणुPCI_VDEVICE(MELLANOX, PCI_DEVICE_ID_MELLANOX_SWITCHX2), 0पूर्ण,
	अणु0, पूर्ण,
पूर्ण;

अटल काष्ठा pci_driver mlxsw_sx_pci_driver = अणु
	.name = mlxsw_sx_driver_name,
	.id_table = mlxsw_sx_pci_id_table,
पूर्ण;

अटल पूर्णांक __init mlxsw_sx_module_init(व्योम)
अणु
	पूर्णांक err;

	err = mlxsw_core_driver_रेजिस्टर(&mlxsw_sx_driver);
	अगर (err)
		वापस err;

	err = mlxsw_pci_driver_रेजिस्टर(&mlxsw_sx_pci_driver);
	अगर (err)
		जाओ err_pci_driver_रेजिस्टर;

	वापस 0;

err_pci_driver_रेजिस्टर:
	mlxsw_core_driver_unरेजिस्टर(&mlxsw_sx_driver);
	वापस err;
पूर्ण

अटल व्योम __निकास mlxsw_sx_module_निकास(व्योम)
अणु
	mlxsw_pci_driver_unरेजिस्टर(&mlxsw_sx_pci_driver);
	mlxsw_core_driver_unरेजिस्टर(&mlxsw_sx_driver);
पूर्ण

module_init(mlxsw_sx_module_init);
module_निकास(mlxsw_sx_module_निकास);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Jiri Pirko <jiri@mellanox.com>");
MODULE_DESCRIPTION("Mellanox SwitchX-2 driver");
MODULE_DEVICE_TABLE(pci, mlxsw_sx_pci_id_table);
