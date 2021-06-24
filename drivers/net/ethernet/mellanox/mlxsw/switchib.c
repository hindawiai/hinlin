<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/* Copyright (c) 2016-2018 Mellanox Technologies. All rights reserved */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/slab.h>
#समावेश <linux/device.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <net/चयनdev.h>

#समावेश "pci.h"
#समावेश "core.h"
#समावेश "reg.h"
#समावेश "port.h"
#समावेश "trap.h"
#समावेश "txheader.h"
#समावेश "ib.h"

अटल स्थिर अक्षर mlxsw_sib_driver_name[] = "mlxsw_switchib";
अटल स्थिर अक्षर mlxsw_sib2_driver_name[] = "mlxsw_switchib2";

काष्ठा mlxsw_sib_port;

काष्ठा mlxsw_sib अणु
	काष्ठा mlxsw_sib_port **ports;
	काष्ठा mlxsw_core *core;
	स्थिर काष्ठा mlxsw_bus_info *bus_info;
	u8 hw_id[ETH_ALEN];
पूर्ण;

काष्ठा mlxsw_sib_port अणु
	काष्ठा mlxsw_sib *mlxsw_sib;
	u8 local_port;
	काष्ठा अणु
		u8 module;
	पूर्ण mapping;
पूर्ण;

/* tx_v1_hdr_version
 * Tx header version.
 * Must be set to 1.
 */
MLXSW_ITEM32(tx_v1, hdr, version, 0x00, 28, 4);

/* tx_v1_hdr_ctl
 * Packet control type.
 * 0 - Ethernet control (e.g. EMADs, LACP)
 * 1 - Ethernet data
 */
MLXSW_ITEM32(tx_v1, hdr, ctl, 0x00, 26, 2);

/* tx_v1_hdr_proto
 * Packet protocol type. Must be set to 1 (Ethernet).
 */
MLXSW_ITEM32(tx_v1, hdr, proto, 0x00, 21, 3);

/* tx_v1_hdr_swid
 * Switch partition ID. Must be set to 0.
 */
MLXSW_ITEM32(tx_v1, hdr, swid, 0x00, 12, 3);

/* tx_v1_hdr_control_tclass
 * Indicates अगर the packet should use the control TClass and not one
 * of the data TClasses.
 */
MLXSW_ITEM32(tx_v1, hdr, control_tclass, 0x00, 6, 1);

/* tx_v1_hdr_port_mid
 * Destination local port क्रम unicast packets.
 * Destination multicast ID क्रम multicast packets.
 *
 * Control packets are directed to a specअगरic egress port, जबतक data
 * packets are transmitted through the CPU port (0) पूर्णांकo the चयन partition,
 * where क्रमwarding rules are applied.
 */
MLXSW_ITEM32(tx_v1, hdr, port_mid, 0x04, 16, 16);

/* tx_v1_hdr_type
 * 0 - Data packets
 * 6 - Control packets
 */
MLXSW_ITEM32(tx_v1, hdr, type, 0x0C, 0, 4);

अटल व्योम
mlxsw_sib_tx_v1_hdr_स्थिरruct(काष्ठा sk_buff *skb,
			      स्थिर काष्ठा mlxsw_tx_info *tx_info)
अणु
	अक्षर *txhdr = skb_push(skb, MLXSW_TXHDR_LEN);

	स_रखो(txhdr, 0, MLXSW_TXHDR_LEN);

	mlxsw_tx_v1_hdr_version_set(txhdr, MLXSW_TXHDR_VERSION_1);
	mlxsw_tx_v1_hdr_ctl_set(txhdr, MLXSW_TXHDR_ETH_CTL);
	mlxsw_tx_v1_hdr_proto_set(txhdr, MLXSW_TXHDR_PROTO_ETH);
	mlxsw_tx_v1_hdr_swid_set(txhdr, 0);
	mlxsw_tx_v1_hdr_control_tclass_set(txhdr, 1);
	mlxsw_tx_v1_hdr_port_mid_set(txhdr, tx_info->local_port);
	mlxsw_tx_v1_hdr_type_set(txhdr, MLXSW_TXHDR_TYPE_CONTROL);
पूर्ण

अटल पूर्णांक mlxsw_sib_hw_id_get(काष्ठा mlxsw_sib *mlxsw_sib)
अणु
	अक्षर spad_pl[MLXSW_REG_SPAD_LEN] = अणु0पूर्ण;
	पूर्णांक err;

	err = mlxsw_reg_query(mlxsw_sib->core, MLXSW_REG(spad), spad_pl);
	अगर (err)
		वापस err;
	mlxsw_reg_spad_base_mac_स_नकल_from(spad_pl, mlxsw_sib->hw_id);
	वापस 0;
पूर्ण

अटल पूर्णांक
mlxsw_sib_port_admin_status_set(काष्ठा mlxsw_sib_port *mlxsw_sib_port,
				bool is_up)
अणु
	काष्ठा mlxsw_sib *mlxsw_sib = mlxsw_sib_port->mlxsw_sib;
	अक्षर paos_pl[MLXSW_REG_PAOS_LEN];

	mlxsw_reg_paos_pack(paos_pl, mlxsw_sib_port->local_port,
			    is_up ? MLXSW_PORT_ADMIN_STATUS_UP :
			    MLXSW_PORT_ADMIN_STATUS_DOWN);
	वापस mlxsw_reg_ग_लिखो(mlxsw_sib->core, MLXSW_REG(paos), paos_pl);
पूर्ण

अटल पूर्णांक mlxsw_sib_port_mtu_set(काष्ठा mlxsw_sib_port *mlxsw_sib_port,
				  u16 mtu)
अणु
	काष्ठा mlxsw_sib *mlxsw_sib = mlxsw_sib_port->mlxsw_sib;
	अक्षर pmtu_pl[MLXSW_REG_PMTU_LEN];
	पूर्णांक max_mtu;
	पूर्णांक err;

	mlxsw_reg_pmtu_pack(pmtu_pl, mlxsw_sib_port->local_port, 0);
	err = mlxsw_reg_query(mlxsw_sib->core, MLXSW_REG(pmtu), pmtu_pl);
	अगर (err)
		वापस err;
	max_mtu = mlxsw_reg_pmtu_max_mtu_get(pmtu_pl);

	अगर (mtu > max_mtu)
		वापस -EINVAL;

	mlxsw_reg_pmtu_pack(pmtu_pl, mlxsw_sib_port->local_port, mtu);
	वापस mlxsw_reg_ग_लिखो(mlxsw_sib->core, MLXSW_REG(pmtu), pmtu_pl);
पूर्ण

अटल पूर्णांक mlxsw_sib_port_set(काष्ठा mlxsw_sib_port *mlxsw_sib_port, u8 port)
अणु
	काष्ठा mlxsw_sib *mlxsw_sib = mlxsw_sib_port->mlxsw_sib;
	अक्षर plib_pl[MLXSW_REG_PLIB_LEN] = अणु0पूर्ण;
	पूर्णांक err;

	mlxsw_reg_plib_local_port_set(plib_pl, mlxsw_sib_port->local_port);
	mlxsw_reg_plib_ib_port_set(plib_pl, port);
	err = mlxsw_reg_ग_लिखो(mlxsw_sib->core, MLXSW_REG(plib), plib_pl);
	वापस err;
पूर्ण

अटल पूर्णांक mlxsw_sib_port_swid_set(काष्ठा mlxsw_sib_port *mlxsw_sib_port,
				   u8 swid)
अणु
	काष्ठा mlxsw_sib *mlxsw_sib = mlxsw_sib_port->mlxsw_sib;
	अक्षर pspa_pl[MLXSW_REG_PSPA_LEN];

	mlxsw_reg_pspa_pack(pspa_pl, swid, mlxsw_sib_port->local_port);
	वापस mlxsw_reg_ग_लिखो(mlxsw_sib->core, MLXSW_REG(pspa), pspa_pl);
पूर्ण

अटल पूर्णांक mlxsw_sib_port_module_info_get(काष्ठा mlxsw_sib *mlxsw_sib,
					  u8 local_port, u8 *p_module,
					  u8 *p_width)
अणु
	अक्षर pmlp_pl[MLXSW_REG_PMLP_LEN];
	पूर्णांक err;

	mlxsw_reg_pmlp_pack(pmlp_pl, local_port);
	err = mlxsw_reg_query(mlxsw_sib->core, MLXSW_REG(pmlp), pmlp_pl);
	अगर (err)
		वापस err;
	*p_module = mlxsw_reg_pmlp_module_get(pmlp_pl, 0);
	*p_width = mlxsw_reg_pmlp_width_get(pmlp_pl);
	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_sib_port_speed_set(काष्ठा mlxsw_sib_port *mlxsw_sib_port,
				    u16 speed, u16 width)
अणु
	काष्ठा mlxsw_sib *mlxsw_sib = mlxsw_sib_port->mlxsw_sib;
	अक्षर ptys_pl[MLXSW_REG_PTYS_LEN];

	mlxsw_reg_ptys_ib_pack(ptys_pl, mlxsw_sib_port->local_port, speed,
			       width);
	वापस mlxsw_reg_ग_लिखो(mlxsw_sib->core, MLXSW_REG(ptys), ptys_pl);
पूर्ण

अटल bool mlxsw_sib_port_created(काष्ठा mlxsw_sib *mlxsw_sib, u8 local_port)
अणु
	वापस mlxsw_sib->ports[local_port] != शून्य;
पूर्ण

अटल पूर्णांक __mlxsw_sib_port_create(काष्ठा mlxsw_sib *mlxsw_sib, u8 local_port,
				   u8 module, u8 width)
अणु
	काष्ठा mlxsw_sib_port *mlxsw_sib_port;
	पूर्णांक err;

	mlxsw_sib_port = kzalloc(माप(*mlxsw_sib_port), GFP_KERNEL);
	अगर (!mlxsw_sib_port)
		वापस -ENOMEM;
	mlxsw_sib_port->mlxsw_sib = mlxsw_sib;
	mlxsw_sib_port->local_port = local_port;
	mlxsw_sib_port->mapping.module = module;

	err = mlxsw_sib_port_swid_set(mlxsw_sib_port, 0);
	अगर (err) अणु
		dev_err(mlxsw_sib->bus_info->dev, "Port %d: Failed to set SWID\n",
			mlxsw_sib_port->local_port);
		जाओ err_port_swid_set;
	पूर्ण

	/* Expose the IB port number as it's front panel name */
	err = mlxsw_sib_port_set(mlxsw_sib_port, module + 1);
	अगर (err) अणु
		dev_err(mlxsw_sib->bus_info->dev, "Port %d: Failed to set IB port\n",
			mlxsw_sib_port->local_port);
		जाओ err_port_ib_set;
	पूर्ण

	/* Supports all speeds from SDR to FDR (biपंचांगask) and support bus width
	 * of 1x, 2x and 4x (3 bits biपंचांगask)
	 */
	err = mlxsw_sib_port_speed_set(mlxsw_sib_port,
				       MLXSW_REG_PTYS_IB_SPEED_EDR - 1,
				       BIT(3) - 1);
	अगर (err) अणु
		dev_err(mlxsw_sib->bus_info->dev, "Port %d: Failed to set speed\n",
			mlxsw_sib_port->local_port);
		जाओ err_port_speed_set;
	पूर्ण

	/* Change to the maximum MTU the device supports, the SMA will take
	 * care of the active MTU
	 */
	err = mlxsw_sib_port_mtu_set(mlxsw_sib_port, MLXSW_IB_DEFAULT_MTU);
	अगर (err) अणु
		dev_err(mlxsw_sib->bus_info->dev, "Port %d: Failed to set MTU\n",
			mlxsw_sib_port->local_port);
		जाओ err_port_mtu_set;
	पूर्ण

	err = mlxsw_sib_port_admin_status_set(mlxsw_sib_port, true);
	अगर (err) अणु
		dev_err(mlxsw_sib->bus_info->dev, "Port %d: Failed to change admin state to UP\n",
			mlxsw_sib_port->local_port);
		जाओ err_port_admin_set;
	पूर्ण

	mlxsw_core_port_ib_set(mlxsw_sib->core, mlxsw_sib_port->local_port,
			       mlxsw_sib_port);
	mlxsw_sib->ports[local_port] = mlxsw_sib_port;
	वापस 0;

err_port_admin_set:
err_port_mtu_set:
err_port_speed_set:
err_port_ib_set:
	mlxsw_sib_port_swid_set(mlxsw_sib_port, MLXSW_PORT_SWID_DISABLED_PORT);
err_port_swid_set:
	kमुक्त(mlxsw_sib_port);
	वापस err;
पूर्ण

अटल पूर्णांक mlxsw_sib_port_create(काष्ठा mlxsw_sib *mlxsw_sib, u8 local_port,
				 u8 module, u8 width)
अणु
	पूर्णांक err;

	err = mlxsw_core_port_init(mlxsw_sib->core, local_port,
				   module + 1, false, 0, false, 0,
				   mlxsw_sib->hw_id, माप(mlxsw_sib->hw_id));
	अगर (err) अणु
		dev_err(mlxsw_sib->bus_info->dev, "Port %d: Failed to init core port\n",
			local_port);
		वापस err;
	पूर्ण
	err = __mlxsw_sib_port_create(mlxsw_sib, local_port, module, width);
	अगर (err)
		जाओ err_port_create;

	वापस 0;

err_port_create:
	mlxsw_core_port_fini(mlxsw_sib->core, local_port);
	वापस err;
पूर्ण

अटल व्योम __mlxsw_sib_port_हटाओ(काष्ठा mlxsw_sib *mlxsw_sib, u8 local_port)
अणु
	काष्ठा mlxsw_sib_port *mlxsw_sib_port = mlxsw_sib->ports[local_port];

	mlxsw_core_port_clear(mlxsw_sib->core, local_port, mlxsw_sib);
	mlxsw_sib->ports[local_port] = शून्य;
	mlxsw_sib_port_admin_status_set(mlxsw_sib_port, false);
	mlxsw_sib_port_swid_set(mlxsw_sib_port, MLXSW_PORT_SWID_DISABLED_PORT);
	kमुक्त(mlxsw_sib_port);
पूर्ण

अटल व्योम mlxsw_sib_port_हटाओ(काष्ठा mlxsw_sib *mlxsw_sib, u8 local_port)
अणु
	__mlxsw_sib_port_हटाओ(mlxsw_sib, local_port);
	mlxsw_core_port_fini(mlxsw_sib->core, local_port);
पूर्ण

अटल व्योम mlxsw_sib_ports_हटाओ(काष्ठा mlxsw_sib *mlxsw_sib)
अणु
	पूर्णांक i;

	क्रम (i = 1; i < MLXSW_PORT_MAX_IB_PORTS; i++)
		अगर (mlxsw_sib_port_created(mlxsw_sib, i))
			mlxsw_sib_port_हटाओ(mlxsw_sib, i);
	kमुक्त(mlxsw_sib->ports);
पूर्ण

अटल पूर्णांक mlxsw_sib_ports_create(काष्ठा mlxsw_sib *mlxsw_sib)
अणु
	माप_प्रकार alloc_size;
	u8 module, width;
	पूर्णांक i;
	पूर्णांक err;

	alloc_size = माप(काष्ठा mlxsw_sib_port *) * MLXSW_PORT_MAX_IB_PORTS;
	mlxsw_sib->ports = kzalloc(alloc_size, GFP_KERNEL);
	अगर (!mlxsw_sib->ports)
		वापस -ENOMEM;

	क्रम (i = 1; i < MLXSW_PORT_MAX_IB_PORTS; i++) अणु
		err = mlxsw_sib_port_module_info_get(mlxsw_sib, i, &module,
						     &width);
		अगर (err)
			जाओ err_port_module_info_get;
		अगर (!width)
			जारी;
		err = mlxsw_sib_port_create(mlxsw_sib, i, module, width);
		अगर (err)
			जाओ err_port_create;
	पूर्ण
	वापस 0;

err_port_create:
err_port_module_info_get:
	क्रम (i--; i >= 1; i--)
		अगर (mlxsw_sib_port_created(mlxsw_sib, i))
			mlxsw_sib_port_हटाओ(mlxsw_sib, i);
	kमुक्त(mlxsw_sib->ports);
	वापस err;
पूर्ण

अटल व्योम
mlxsw_sib_pude_ib_event_func(काष्ठा mlxsw_sib_port *mlxsw_sib_port,
			     क्रमागत mlxsw_reg_pude_oper_status status)
अणु
	अगर (status == MLXSW_PORT_OPER_STATUS_UP)
		pr_info("ib link for port %d - up\n",
			mlxsw_sib_port->mapping.module + 1);
	अन्यथा
		pr_info("ib link for port %d - down\n",
			mlxsw_sib_port->mapping.module + 1);
पूर्ण

अटल व्योम mlxsw_sib_pude_event_func(स्थिर काष्ठा mlxsw_reg_info *reg,
				      अक्षर *pude_pl, व्योम *priv)
अणु
	काष्ठा mlxsw_sib *mlxsw_sib = priv;
	काष्ठा mlxsw_sib_port *mlxsw_sib_port;
	क्रमागत mlxsw_reg_pude_oper_status status;
	u8 local_port;

	local_port = mlxsw_reg_pude_local_port_get(pude_pl);
	mlxsw_sib_port = mlxsw_sib->ports[local_port];
	अगर (!mlxsw_sib_port) अणु
		dev_warn(mlxsw_sib->bus_info->dev, "Port %d: Link event received for non-existent port\n",
			 local_port);
		वापस;
	पूर्ण

	status = mlxsw_reg_pude_oper_status_get(pude_pl);
	mlxsw_sib_pude_ib_event_func(mlxsw_sib_port, status);
पूर्ण

अटल स्थिर काष्ठा mlxsw_listener mlxsw_sib_listener[] = अणु
	MLXSW_EVENTL(mlxsw_sib_pude_event_func, PUDE, EMAD),
पूर्ण;

अटल पूर्णांक mlxsw_sib_taps_init(काष्ठा mlxsw_sib *mlxsw_sib)
अणु
	पूर्णांक i;
	पूर्णांक err;

	क्रम (i = 0; i < ARRAY_SIZE(mlxsw_sib_listener); i++) अणु
		err = mlxsw_core_trap_रेजिस्टर(mlxsw_sib->core,
					       &mlxsw_sib_listener[i],
					       mlxsw_sib);
		अगर (err)
			जाओ err_rx_listener_रेजिस्टर;
	पूर्ण

	वापस 0;

err_rx_listener_रेजिस्टर:
	क्रम (i--; i >= 0; i--) अणु
		mlxsw_core_trap_unरेजिस्टर(mlxsw_sib->core,
					   &mlxsw_sib_listener[i],
					   mlxsw_sib);
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम mlxsw_sib_traps_fini(काष्ठा mlxsw_sib *mlxsw_sib)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(mlxsw_sib_listener); i++) अणु
		mlxsw_core_trap_unरेजिस्टर(mlxsw_sib->core,
					   &mlxsw_sib_listener[i], mlxsw_sib);
	पूर्ण
पूर्ण

अटल पूर्णांक mlxsw_sib_basic_trap_groups_set(काष्ठा mlxsw_core *mlxsw_core)
अणु
	अक्षर htgt_pl[MLXSW_REG_HTGT_LEN];

	mlxsw_reg_htgt_pack(htgt_pl, MLXSW_REG_HTGT_TRAP_GROUP_EMAD,
			    MLXSW_REG_HTGT_INVALID_POLICER,
			    MLXSW_REG_HTGT_DEFAULT_PRIORITY,
			    MLXSW_REG_HTGT_DEFAULT_TC);
	mlxsw_reg_htgt_swid_set(htgt_pl, MLXSW_PORT_SWID_ALL_SWIDS);
	mlxsw_reg_htgt_local_path_rdq_set(htgt_pl,
					MLXSW_REG_HTGT_LOCAL_PATH_RDQ_SIB_EMAD);
	वापस mlxsw_reg_ग_लिखो(mlxsw_core, MLXSW_REG(htgt), htgt_pl);
पूर्ण

अटल पूर्णांक mlxsw_sib_init(काष्ठा mlxsw_core *mlxsw_core,
			  स्थिर काष्ठा mlxsw_bus_info *mlxsw_bus_info,
			  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlxsw_sib *mlxsw_sib = mlxsw_core_driver_priv(mlxsw_core);
	पूर्णांक err;

	mlxsw_sib->core = mlxsw_core;
	mlxsw_sib->bus_info = mlxsw_bus_info;

	err = mlxsw_sib_hw_id_get(mlxsw_sib);
	अगर (err) अणु
		dev_err(mlxsw_sib->bus_info->dev, "Failed to get switch HW ID\n");
		वापस err;
	पूर्ण

	err = mlxsw_sib_ports_create(mlxsw_sib);
	अगर (err) अणु
		dev_err(mlxsw_sib->bus_info->dev, "Failed to create ports\n");
		वापस err;
	पूर्ण

	err = mlxsw_sib_taps_init(mlxsw_sib);
	अगर (err) अणु
		dev_err(mlxsw_sib->bus_info->dev, "Failed to set traps\n");
		जाओ err_traps_init_err;
	पूर्ण

	वापस 0;

err_traps_init_err:
	mlxsw_sib_ports_हटाओ(mlxsw_sib);
	वापस err;
पूर्ण

अटल व्योम mlxsw_sib_fini(काष्ठा mlxsw_core *mlxsw_core)
अणु
	काष्ठा mlxsw_sib *mlxsw_sib = mlxsw_core_driver_priv(mlxsw_core);

	mlxsw_sib_traps_fini(mlxsw_sib);
	mlxsw_sib_ports_हटाओ(mlxsw_sib);
पूर्ण

अटल स्थिर काष्ठा mlxsw_config_profile mlxsw_sib_config_profile = अणु
	.used_max_प्रणाली_port		= 1,
	.max_प्रणाली_port		= 48000,
	.used_max_ib_mc			= 1,
	.max_ib_mc			= 27,
	.used_max_pkey			= 1,
	.max_pkey			= 32,
	.swid_config			= अणु
		अणु
			.used_type	= 1,
			.type		= MLXSW_PORT_SWID_TYPE_IB,
		पूर्ण
	पूर्ण,
पूर्ण;

अटल काष्ठा mlxsw_driver mlxsw_sib_driver = अणु
	.kind			= mlxsw_sib_driver_name,
	.priv_size		= माप(काष्ठा mlxsw_sib),
	.init			= mlxsw_sib_init,
	.fini			= mlxsw_sib_fini,
	.basic_trap_groups_set	= mlxsw_sib_basic_trap_groups_set,
	.txhdr_स्थिरruct	= mlxsw_sib_tx_v1_hdr_स्थिरruct,
	.txhdr_len		= MLXSW_TXHDR_LEN,
	.profile		= &mlxsw_sib_config_profile,
पूर्ण;

अटल काष्ठा mlxsw_driver mlxsw_sib2_driver = अणु
	.kind			= mlxsw_sib2_driver_name,
	.priv_size		= माप(काष्ठा mlxsw_sib),
	.init			= mlxsw_sib_init,
	.fini			= mlxsw_sib_fini,
	.basic_trap_groups_set	= mlxsw_sib_basic_trap_groups_set,
	.txhdr_स्थिरruct	= mlxsw_sib_tx_v1_hdr_स्थिरruct,
	.txhdr_len		= MLXSW_TXHDR_LEN,
	.profile		= &mlxsw_sib_config_profile,
पूर्ण;

अटल स्थिर काष्ठा pci_device_id mlxsw_sib_pci_id_table[] = अणु
	अणुPCI_VDEVICE(MELLANOX, PCI_DEVICE_ID_MELLANOX_SWITCHIB), 0पूर्ण,
	अणु0, पूर्ण,
पूर्ण;

अटल काष्ठा pci_driver mlxsw_sib_pci_driver = अणु
	.name = mlxsw_sib_driver_name,
	.id_table = mlxsw_sib_pci_id_table,
पूर्ण;

अटल स्थिर काष्ठा pci_device_id mlxsw_sib2_pci_id_table[] = अणु
	अणुPCI_VDEVICE(MELLANOX, PCI_DEVICE_ID_MELLANOX_SWITCHIB2), 0पूर्ण,
	अणु0, पूर्ण,
पूर्ण;

अटल काष्ठा pci_driver mlxsw_sib2_pci_driver = अणु
	.name = mlxsw_sib2_driver_name,
	.id_table = mlxsw_sib2_pci_id_table,
पूर्ण;

अटल पूर्णांक __init mlxsw_sib_module_init(व्योम)
अणु
	पूर्णांक err;

	err = mlxsw_core_driver_रेजिस्टर(&mlxsw_sib_driver);
	अगर (err)
		वापस err;

	err = mlxsw_core_driver_रेजिस्टर(&mlxsw_sib2_driver);
	अगर (err)
		जाओ err_sib2_driver_रेजिस्टर;

	err = mlxsw_pci_driver_रेजिस्टर(&mlxsw_sib_pci_driver);
	अगर (err)
		जाओ err_sib_pci_driver_रेजिस्टर;

	err = mlxsw_pci_driver_रेजिस्टर(&mlxsw_sib2_pci_driver);
	अगर (err)
		जाओ err_sib2_pci_driver_रेजिस्टर;

	वापस 0;

err_sib2_pci_driver_रेजिस्टर:
	mlxsw_pci_driver_unरेजिस्टर(&mlxsw_sib_pci_driver);
err_sib_pci_driver_रेजिस्टर:
	mlxsw_core_driver_unरेजिस्टर(&mlxsw_sib2_driver);
err_sib2_driver_रेजिस्टर:
	mlxsw_core_driver_unरेजिस्टर(&mlxsw_sib_driver);
	वापस err;
पूर्ण

अटल व्योम __निकास mlxsw_sib_module_निकास(व्योम)
अणु
	mlxsw_pci_driver_unरेजिस्टर(&mlxsw_sib2_pci_driver);
	mlxsw_pci_driver_unरेजिस्टर(&mlxsw_sib_pci_driver);
	mlxsw_core_driver_unरेजिस्टर(&mlxsw_sib2_driver);
	mlxsw_core_driver_unरेजिस्टर(&mlxsw_sib_driver);
पूर्ण

module_init(mlxsw_sib_module_init);
module_निकास(mlxsw_sib_module_निकास);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Elad Raz <eladr@@mellanox.com>");
MODULE_DESCRIPTION("Mellanox SwitchIB and SwitchIB-2 driver");
MODULE_ALIAS("mlxsw_switchib2");
MODULE_DEVICE_TABLE(pci, mlxsw_sib_pci_id_table);
MODULE_DEVICE_TABLE(pci, mlxsw_sib2_pci_id_table);
