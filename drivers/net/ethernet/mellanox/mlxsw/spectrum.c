<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/* Copyright (c) 2015-2018 Mellanox Technologies. All rights reserved */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/slab.h>
#समावेश <linux/device.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/अगर_bridge.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/bitops.h>
#समावेश <linux/list.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/dcbnl.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/netlink.h>
#समावेश <linux/jhash.h>
#समावेश <linux/log2.h>
#समावेश <linux/refcount.h>
#समावेश <linux/rhashtable.h>
#समावेश <net/चयनdev.h>
#समावेश <net/pkt_cls.h>
#समावेश <net/netevent.h>
#समावेश <net/addrconf.h>

#समावेश "spectrum.h"
#समावेश "pci.h"
#समावेश "core.h"
#समावेश "core_env.h"
#समावेश "reg.h"
#समावेश "port.h"
#समावेश "trap.h"
#समावेश "txheader.h"
#समावेश "spectrum_cnt.h"
#समावेश "spectrum_dpipe.h"
#समावेश "spectrum_acl_flex_actions.h"
#समावेश "spectrum_span.h"
#समावेश "spectrum_ptp.h"
#समावेश "spectrum_trap.h"

#घोषणा MLXSW_SP1_FWREV_MAJOR 13
#घोषणा MLXSW_SP1_FWREV_MINOR 2008
#घोषणा MLXSW_SP1_FWREV_SUBMINOR 2406
#घोषणा MLXSW_SP1_FWREV_CAN_RESET_MINOR 1702

अटल स्थिर काष्ठा mlxsw_fw_rev mlxsw_sp1_fw_rev = अणु
	.major = MLXSW_SP1_FWREV_MAJOR,
	.minor = MLXSW_SP1_FWREV_MINOR,
	.subminor = MLXSW_SP1_FWREV_SUBMINOR,
	.can_reset_minor = MLXSW_SP1_FWREV_CAN_RESET_MINOR,
पूर्ण;

#घोषणा MLXSW_SP1_FW_खाताNAME \
	"mellanox/mlxsw_spectrum-" __stringअगरy(MLXSW_SP1_FWREV_MAJOR) \
	"." __stringअगरy(MLXSW_SP1_FWREV_MINOR) \
	"." __stringअगरy(MLXSW_SP1_FWREV_SUBMINOR) ".mfa2"

#घोषणा MLXSW_SP2_FWREV_MAJOR 29
#घोषणा MLXSW_SP2_FWREV_MINOR 2008
#घोषणा MLXSW_SP2_FWREV_SUBMINOR 2406

अटल स्थिर काष्ठा mlxsw_fw_rev mlxsw_sp2_fw_rev = अणु
	.major = MLXSW_SP2_FWREV_MAJOR,
	.minor = MLXSW_SP2_FWREV_MINOR,
	.subminor = MLXSW_SP2_FWREV_SUBMINOR,
पूर्ण;

#घोषणा MLXSW_SP2_FW_खाताNAME \
	"mellanox/mlxsw_spectrum2-" __stringअगरy(MLXSW_SP2_FWREV_MAJOR) \
	"." __stringअगरy(MLXSW_SP2_FWREV_MINOR) \
	"." __stringअगरy(MLXSW_SP2_FWREV_SUBMINOR) ".mfa2"

#घोषणा MLXSW_SP3_FWREV_MAJOR 30
#घोषणा MLXSW_SP3_FWREV_MINOR 2008
#घोषणा MLXSW_SP3_FWREV_SUBMINOR 2406

अटल स्थिर काष्ठा mlxsw_fw_rev mlxsw_sp3_fw_rev = अणु
	.major = MLXSW_SP3_FWREV_MAJOR,
	.minor = MLXSW_SP3_FWREV_MINOR,
	.subminor = MLXSW_SP3_FWREV_SUBMINOR,
पूर्ण;

#घोषणा MLXSW_SP3_FW_खाताNAME \
	"mellanox/mlxsw_spectrum3-" __stringअगरy(MLXSW_SP3_FWREV_MAJOR) \
	"." __stringअगरy(MLXSW_SP3_FWREV_MINOR) \
	"." __stringअगरy(MLXSW_SP3_FWREV_SUBMINOR) ".mfa2"

अटल स्थिर अक्षर mlxsw_sp1_driver_name[] = "mlxsw_spectrum";
अटल स्थिर अक्षर mlxsw_sp2_driver_name[] = "mlxsw_spectrum2";
अटल स्थिर अक्षर mlxsw_sp3_driver_name[] = "mlxsw_spectrum3";

अटल स्थिर अचिन्हित अक्षर mlxsw_sp1_mac_mask[ETH_ALEN] = अणु
	0xff, 0xff, 0xff, 0xff, 0xfc, 0x00
पूर्ण;
अटल स्थिर अचिन्हित अक्षर mlxsw_sp2_mac_mask[ETH_ALEN] = अणु
	0xff, 0xff, 0xff, 0xff, 0xf0, 0x00
पूर्ण;

/* tx_hdr_version
 * Tx header version.
 * Must be set to 1.
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

/* tx_hdr_rx_is_router
 * Packet is sent from the router. Valid क्रम data packets only.
 */
MLXSW_ITEM32(tx, hdr, rx_is_router, 0x00, 19, 1);

/* tx_hdr_fid_valid
 * Indicates अगर the 'fid' field is valid and should be used क्रम
 * क्रमwarding lookup. Valid क्रम data packets only.
 */
MLXSW_ITEM32(tx, hdr, fid_valid, 0x00, 16, 1);

/* tx_hdr_swid
 * Switch partition ID. Must be set to 0.
 */
MLXSW_ITEM32(tx, hdr, swid, 0x00, 12, 3);

/* tx_hdr_control_tclass
 * Indicates अगर the packet should use the control TClass and not one
 * of the data TClasses.
 */
MLXSW_ITEM32(tx, hdr, control_tclass, 0x00, 6, 1);

/* tx_hdr_etclass
 * Egress TClass to be used on the egress device on the egress port.
 */
MLXSW_ITEM32(tx, hdr, etclass, 0x00, 0, 4);

/* tx_hdr_port_mid
 * Destination local port क्रम unicast packets.
 * Destination multicast ID क्रम multicast packets.
 *
 * Control packets are directed to a specअगरic egress port, जबतक data
 * packets are transmitted through the CPU port (0) पूर्णांकo the चयन partition,
 * where क्रमwarding rules are applied.
 */
MLXSW_ITEM32(tx, hdr, port_mid, 0x04, 16, 16);

/* tx_hdr_fid
 * Forwarding ID used क्रम L2 क्रमwarding lookup. Valid only अगर 'fid_valid' is
 * set, otherwise calculated based on the packet's VID using VID to FID mapping.
 * Valid क्रम data packets only.
 */
MLXSW_ITEM32(tx, hdr, fid, 0x08, 0, 16);

/* tx_hdr_type
 * 0 - Data packets
 * 6 - Control packets
 */
MLXSW_ITEM32(tx, hdr, type, 0x0C, 0, 4);

पूर्णांक mlxsw_sp_flow_counter_get(काष्ठा mlxsw_sp *mlxsw_sp,
			      अचिन्हित पूर्णांक counter_index, u64 *packets,
			      u64 *bytes)
अणु
	अक्षर mgpc_pl[MLXSW_REG_MGPC_LEN];
	पूर्णांक err;

	mlxsw_reg_mgpc_pack(mgpc_pl, counter_index, MLXSW_REG_MGPC_OPCODE_NOP,
			    MLXSW_REG_FLOW_COUNTER_SET_TYPE_PACKETS_BYTES);
	err = mlxsw_reg_query(mlxsw_sp->core, MLXSW_REG(mgpc), mgpc_pl);
	अगर (err)
		वापस err;
	अगर (packets)
		*packets = mlxsw_reg_mgpc_packet_counter_get(mgpc_pl);
	अगर (bytes)
		*bytes = mlxsw_reg_mgpc_byte_counter_get(mgpc_pl);
	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_sp_flow_counter_clear(काष्ठा mlxsw_sp *mlxsw_sp,
				       अचिन्हित पूर्णांक counter_index)
अणु
	अक्षर mgpc_pl[MLXSW_REG_MGPC_LEN];

	mlxsw_reg_mgpc_pack(mgpc_pl, counter_index, MLXSW_REG_MGPC_OPCODE_CLEAR,
			    MLXSW_REG_FLOW_COUNTER_SET_TYPE_PACKETS_BYTES);
	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(mgpc), mgpc_pl);
पूर्ण

पूर्णांक mlxsw_sp_flow_counter_alloc(काष्ठा mlxsw_sp *mlxsw_sp,
				अचिन्हित पूर्णांक *p_counter_index)
अणु
	पूर्णांक err;

	err = mlxsw_sp_counter_alloc(mlxsw_sp, MLXSW_SP_COUNTER_SUB_POOL_FLOW,
				     p_counter_index);
	अगर (err)
		वापस err;
	err = mlxsw_sp_flow_counter_clear(mlxsw_sp, *p_counter_index);
	अगर (err)
		जाओ err_counter_clear;
	वापस 0;

err_counter_clear:
	mlxsw_sp_counter_मुक्त(mlxsw_sp, MLXSW_SP_COUNTER_SUB_POOL_FLOW,
			      *p_counter_index);
	वापस err;
पूर्ण

व्योम mlxsw_sp_flow_counter_मुक्त(काष्ठा mlxsw_sp *mlxsw_sp,
				अचिन्हित पूर्णांक counter_index)
अणु
	 mlxsw_sp_counter_मुक्त(mlxsw_sp, MLXSW_SP_COUNTER_SUB_POOL_FLOW,
			       counter_index);
पूर्ण

अटल व्योम mlxsw_sp_txhdr_स्थिरruct(काष्ठा sk_buff *skb,
				     स्थिर काष्ठा mlxsw_tx_info *tx_info)
अणु
	अक्षर *txhdr = skb_push(skb, MLXSW_TXHDR_LEN);

	स_रखो(txhdr, 0, MLXSW_TXHDR_LEN);

	mlxsw_tx_hdr_version_set(txhdr, MLXSW_TXHDR_VERSION_1);
	mlxsw_tx_hdr_ctl_set(txhdr, MLXSW_TXHDR_ETH_CTL);
	mlxsw_tx_hdr_proto_set(txhdr, MLXSW_TXHDR_PROTO_ETH);
	mlxsw_tx_hdr_swid_set(txhdr, 0);
	mlxsw_tx_hdr_control_tclass_set(txhdr, 1);
	mlxsw_tx_hdr_port_mid_set(txhdr, tx_info->local_port);
	mlxsw_tx_hdr_type_set(txhdr, MLXSW_TXHDR_TYPE_CONTROL);
पूर्ण

क्रमागत mlxsw_reg_spms_state mlxsw_sp_stp_spms_state(u8 state)
अणु
	चयन (state) अणु
	हाल BR_STATE_FORWARDING:
		वापस MLXSW_REG_SPMS_STATE_FORWARDING;
	हाल BR_STATE_LEARNING:
		वापस MLXSW_REG_SPMS_STATE_LEARNING;
	हाल BR_STATE_LISTENING:
	हाल BR_STATE_DISABLED:
	हाल BR_STATE_BLOCKING:
		वापस MLXSW_REG_SPMS_STATE_DISCARDING;
	शेष:
		BUG();
	पूर्ण
पूर्ण

पूर्णांक mlxsw_sp_port_vid_stp_set(काष्ठा mlxsw_sp_port *mlxsw_sp_port, u16 vid,
			      u8 state)
अणु
	क्रमागत mlxsw_reg_spms_state spms_state = mlxsw_sp_stp_spms_state(state);
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	अक्षर *spms_pl;
	पूर्णांक err;

	spms_pl = kदो_स्मृति(MLXSW_REG_SPMS_LEN, GFP_KERNEL);
	अगर (!spms_pl)
		वापस -ENOMEM;
	mlxsw_reg_spms_pack(spms_pl, mlxsw_sp_port->local_port);
	mlxsw_reg_spms_vid_pack(spms_pl, vid, spms_state);

	err = mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(spms), spms_pl);
	kमुक्त(spms_pl);
	वापस err;
पूर्ण

अटल पूर्णांक mlxsw_sp_base_mac_get(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	अक्षर spad_pl[MLXSW_REG_SPAD_LEN] = अणु0पूर्ण;
	पूर्णांक err;

	err = mlxsw_reg_query(mlxsw_sp->core, MLXSW_REG(spad), spad_pl);
	अगर (err)
		वापस err;
	mlxsw_reg_spad_base_mac_स_नकल_from(spad_pl, mlxsw_sp->base_mac);
	वापस 0;
पूर्ण

पूर्णांक mlxsw_sp_port_admin_status_set(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				   bool is_up)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	अक्षर paos_pl[MLXSW_REG_PAOS_LEN];

	mlxsw_reg_paos_pack(paos_pl, mlxsw_sp_port->local_port,
			    is_up ? MLXSW_PORT_ADMIN_STATUS_UP :
			    MLXSW_PORT_ADMIN_STATUS_DOWN);
	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(paos), paos_pl);
पूर्ण

अटल पूर्णांक mlxsw_sp_port_dev_addr_set(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				      अचिन्हित अक्षर *addr)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	अक्षर ppad_pl[MLXSW_REG_PPAD_LEN];

	mlxsw_reg_ppad_pack(ppad_pl, true, mlxsw_sp_port->local_port);
	mlxsw_reg_ppad_mac_स_नकल_to(ppad_pl, addr);
	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(ppad), ppad_pl);
पूर्ण

अटल पूर्णांक mlxsw_sp_port_dev_addr_init(काष्ठा mlxsw_sp_port *mlxsw_sp_port)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	अचिन्हित अक्षर *addr = mlxsw_sp_port->dev->dev_addr;

	ether_addr_copy(addr, mlxsw_sp->base_mac);
	addr[ETH_ALEN - 1] += mlxsw_sp_port->local_port;
	वापस mlxsw_sp_port_dev_addr_set(mlxsw_sp_port, addr);
पूर्ण

अटल पूर्णांक mlxsw_sp_port_max_mtu_get(काष्ठा mlxsw_sp_port *mlxsw_sp_port, पूर्णांक *p_max_mtu)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	अक्षर pmtu_pl[MLXSW_REG_PMTU_LEN];
	पूर्णांक err;

	mlxsw_reg_pmtu_pack(pmtu_pl, mlxsw_sp_port->local_port, 0);
	err = mlxsw_reg_query(mlxsw_sp->core, MLXSW_REG(pmtu), pmtu_pl);
	अगर (err)
		वापस err;

	*p_max_mtu = mlxsw_reg_pmtu_max_mtu_get(pmtu_pl);
	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_sp_port_mtu_set(काष्ठा mlxsw_sp_port *mlxsw_sp_port, u16 mtu)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	अक्षर pmtu_pl[MLXSW_REG_PMTU_LEN];

	mtu += MLXSW_TXHDR_LEN + ETH_HLEN;
	अगर (mtu > mlxsw_sp_port->max_mtu)
		वापस -EINVAL;

	mlxsw_reg_pmtu_pack(pmtu_pl, mlxsw_sp_port->local_port, mtu);
	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(pmtu), pmtu_pl);
पूर्ण

अटल पूर्णांक mlxsw_sp_port_swid_set(काष्ठा mlxsw_sp_port *mlxsw_sp_port, u8 swid)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	अक्षर pspa_pl[MLXSW_REG_PSPA_LEN];

	mlxsw_reg_pspa_pack(pspa_pl, swid, mlxsw_sp_port->local_port);
	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(pspa), pspa_pl);
पूर्ण

पूर्णांक mlxsw_sp_port_vp_mode_set(काष्ठा mlxsw_sp_port *mlxsw_sp_port, bool enable)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	अक्षर svpe_pl[MLXSW_REG_SVPE_LEN];

	mlxsw_reg_svpe_pack(svpe_pl, mlxsw_sp_port->local_port, enable);
	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(svpe), svpe_pl);
पूर्ण

पूर्णांक mlxsw_sp_port_vid_learning_set(काष्ठा mlxsw_sp_port *mlxsw_sp_port, u16 vid,
				   bool learn_enable)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	अक्षर *spvmlr_pl;
	पूर्णांक err;

	spvmlr_pl = kदो_स्मृति(MLXSW_REG_SPVMLR_LEN, GFP_KERNEL);
	अगर (!spvmlr_pl)
		वापस -ENOMEM;
	mlxsw_reg_spvmlr_pack(spvmlr_pl, mlxsw_sp_port->local_port, vid, vid,
			      learn_enable);
	err = mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(spvmlr), spvmlr_pl);
	kमुक्त(spvmlr_pl);
	वापस err;
पूर्ण

पूर्णांक mlxsw_sp_ethtype_to_sver_type(u16 ethtype, u8 *p_sver_type)
अणु
	चयन (ethtype) अणु
	हाल ETH_P_8021Q:
		*p_sver_type = 0;
		अवरोध;
	हाल ETH_P_8021AD:
		*p_sver_type = 1;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक mlxsw_sp_port_egress_ethtype_set(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				     u16 ethtype)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	अक्षर spevet_pl[MLXSW_REG_SPEVET_LEN];
	u8 sver_type;
	पूर्णांक err;

	err = mlxsw_sp_ethtype_to_sver_type(ethtype, &sver_type);
	अगर (err)
		वापस err;

	mlxsw_reg_spevet_pack(spevet_pl, mlxsw_sp_port->local_port, sver_type);
	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(spevet), spevet_pl);
पूर्ण

अटल पूर्णांक __mlxsw_sp_port_pvid_set(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				    u16 vid, u16 ethtype)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	अक्षर spvid_pl[MLXSW_REG_SPVID_LEN];
	u8 sver_type;
	पूर्णांक err;

	err = mlxsw_sp_ethtype_to_sver_type(ethtype, &sver_type);
	अगर (err)
		वापस err;

	mlxsw_reg_spvid_pack(spvid_pl, mlxsw_sp_port->local_port, vid,
			     sver_type);

	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(spvid), spvid_pl);
पूर्ण

अटल पूर्णांक mlxsw_sp_port_allow_untagged_set(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
					    bool allow)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	अक्षर spaft_pl[MLXSW_REG_SPAFT_LEN];

	mlxsw_reg_spaft_pack(spaft_pl, mlxsw_sp_port->local_port, allow);
	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(spaft), spaft_pl);
पूर्ण

पूर्णांक mlxsw_sp_port_pvid_set(काष्ठा mlxsw_sp_port *mlxsw_sp_port, u16 vid,
			   u16 ethtype)
अणु
	पूर्णांक err;

	अगर (!vid) अणु
		err = mlxsw_sp_port_allow_untagged_set(mlxsw_sp_port, false);
		अगर (err)
			वापस err;
	पूर्ण अन्यथा अणु
		err = __mlxsw_sp_port_pvid_set(mlxsw_sp_port, vid, ethtype);
		अगर (err)
			वापस err;
		err = mlxsw_sp_port_allow_untagged_set(mlxsw_sp_port, true);
		अगर (err)
			जाओ err_port_allow_untagged_set;
	पूर्ण

	mlxsw_sp_port->pvid = vid;
	वापस 0;

err_port_allow_untagged_set:
	__mlxsw_sp_port_pvid_set(mlxsw_sp_port, mlxsw_sp_port->pvid, ethtype);
	वापस err;
पूर्ण

अटल पूर्णांक
mlxsw_sp_port_प्रणाली_port_mapping_set(काष्ठा mlxsw_sp_port *mlxsw_sp_port)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	अक्षर sspr_pl[MLXSW_REG_SSPR_LEN];

	mlxsw_reg_sspr_pack(sspr_pl, mlxsw_sp_port->local_port);
	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(sspr), sspr_pl);
पूर्ण

अटल पूर्णांक
mlxsw_sp_port_module_info_get(काष्ठा mlxsw_sp *mlxsw_sp, u8 local_port,
			      काष्ठा mlxsw_sp_port_mapping *port_mapping)
अणु
	अक्षर pmlp_pl[MLXSW_REG_PMLP_LEN];
	bool separate_rxtx;
	u8 module;
	u8 width;
	पूर्णांक err;
	पूर्णांक i;

	mlxsw_reg_pmlp_pack(pmlp_pl, local_port);
	err = mlxsw_reg_query(mlxsw_sp->core, MLXSW_REG(pmlp), pmlp_pl);
	अगर (err)
		वापस err;
	module = mlxsw_reg_pmlp_module_get(pmlp_pl, 0);
	width = mlxsw_reg_pmlp_width_get(pmlp_pl);
	separate_rxtx = mlxsw_reg_pmlp_rxtx_get(pmlp_pl);

	अगर (width && !is_घातer_of_2(width)) अणु
		dev_err(mlxsw_sp->bus_info->dev, "Port %d: Unsupported module config: width value is not power of 2\n",
			local_port);
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < width; i++) अणु
		अगर (mlxsw_reg_pmlp_module_get(pmlp_pl, i) != module) अणु
			dev_err(mlxsw_sp->bus_info->dev, "Port %d: Unsupported module config: contains multiple modules\n",
				local_port);
			वापस -EINVAL;
		पूर्ण
		अगर (separate_rxtx &&
		    mlxsw_reg_pmlp_tx_lane_get(pmlp_pl, i) !=
		    mlxsw_reg_pmlp_rx_lane_get(pmlp_pl, i)) अणु
			dev_err(mlxsw_sp->bus_info->dev, "Port %d: Unsupported module config: TX and RX lane numbers are different\n",
				local_port);
			वापस -EINVAL;
		पूर्ण
		अगर (mlxsw_reg_pmlp_tx_lane_get(pmlp_pl, i) != i) अणु
			dev_err(mlxsw_sp->bus_info->dev, "Port %d: Unsupported module config: TX and RX lane numbers are not sequential\n",
				local_port);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	port_mapping->module = module;
	port_mapping->width = width;
	port_mapping->lane = mlxsw_reg_pmlp_tx_lane_get(pmlp_pl, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_sp_port_module_map(काष्ठा mlxsw_sp_port *mlxsw_sp_port)
अणु
	काष्ठा mlxsw_sp_port_mapping *port_mapping = &mlxsw_sp_port->mapping;
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	अक्षर pmlp_pl[MLXSW_REG_PMLP_LEN];
	पूर्णांक i;

	mlxsw_reg_pmlp_pack(pmlp_pl, mlxsw_sp_port->local_port);
	mlxsw_reg_pmlp_width_set(pmlp_pl, port_mapping->width);
	क्रम (i = 0; i < port_mapping->width; i++) अणु
		mlxsw_reg_pmlp_module_set(pmlp_pl, i, port_mapping->module);
		mlxsw_reg_pmlp_tx_lane_set(pmlp_pl, i, port_mapping->lane + i); /* Rx & Tx */
	पूर्ण

	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(pmlp), pmlp_pl);
पूर्ण

अटल पूर्णांक mlxsw_sp_port_module_unmap(काष्ठा mlxsw_sp_port *mlxsw_sp_port)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	अक्षर pmlp_pl[MLXSW_REG_PMLP_LEN];

	mlxsw_reg_pmlp_pack(pmlp_pl, mlxsw_sp_port->local_port);
	mlxsw_reg_pmlp_width_set(pmlp_pl, 0);
	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(pmlp), pmlp_pl);
पूर्ण

अटल पूर्णांक mlxsw_sp_port_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा mlxsw_sp_port *mlxsw_sp_port = netdev_priv(dev);
	पूर्णांक err;

	err = mlxsw_sp_port_admin_status_set(mlxsw_sp_port, true);
	अगर (err)
		वापस err;
	netअगर_start_queue(dev);
	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_sp_port_stop(काष्ठा net_device *dev)
अणु
	काष्ठा mlxsw_sp_port *mlxsw_sp_port = netdev_priv(dev);

	netअगर_stop_queue(dev);
	वापस mlxsw_sp_port_admin_status_set(mlxsw_sp_port, false);
पूर्ण

अटल netdev_tx_t mlxsw_sp_port_xmit(काष्ठा sk_buff *skb,
				      काष्ठा net_device *dev)
अणु
	काष्ठा mlxsw_sp_port *mlxsw_sp_port = netdev_priv(dev);
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	काष्ठा mlxsw_sp_port_pcpu_stats *pcpu_stats;
	स्थिर काष्ठा mlxsw_tx_info tx_info = अणु
		.local_port = mlxsw_sp_port->local_port,
		.is_emad = false,
	पूर्ण;
	u64 len;
	पूर्णांक err;

	अगर (skb_cow_head(skb, MLXSW_TXHDR_LEN)) अणु
		this_cpu_inc(mlxsw_sp_port->pcpu_stats->tx_dropped);
		dev_kमुक्त_skb_any(skb);
		वापस NETDEV_TX_OK;
	पूर्ण

	स_रखो(skb->cb, 0, माप(काष्ठा mlxsw_skb_cb));

	अगर (mlxsw_core_skb_transmit_busy(mlxsw_sp->core, &tx_info))
		वापस NETDEV_TX_BUSY;

	अगर (eth_skb_pad(skb)) अणु
		this_cpu_inc(mlxsw_sp_port->pcpu_stats->tx_dropped);
		वापस NETDEV_TX_OK;
	पूर्ण

	mlxsw_sp_txhdr_स्थिरruct(skb, &tx_info);
	/* TX header is consumed by HW on the way so we shouldn't count its
	 * bytes as being sent.
	 */
	len = skb->len - MLXSW_TXHDR_LEN;

	/* Due to a race we might fail here because of a full queue. In that
	 * unlikely हाल we simply drop the packet.
	 */
	err = mlxsw_core_skb_transmit(mlxsw_sp->core, skb, &tx_info);

	अगर (!err) अणु
		pcpu_stats = this_cpu_ptr(mlxsw_sp_port->pcpu_stats);
		u64_stats_update_begin(&pcpu_stats->syncp);
		pcpu_stats->tx_packets++;
		pcpu_stats->tx_bytes += len;
		u64_stats_update_end(&pcpu_stats->syncp);
	पूर्ण अन्यथा अणु
		this_cpu_inc(mlxsw_sp_port->pcpu_stats->tx_dropped);
		dev_kमुक्त_skb_any(skb);
	पूर्ण
	वापस NETDEV_TX_OK;
पूर्ण

अटल व्योम mlxsw_sp_set_rx_mode(काष्ठा net_device *dev)
अणु
पूर्ण

अटल पूर्णांक mlxsw_sp_port_set_mac_address(काष्ठा net_device *dev, व्योम *p)
अणु
	काष्ठा mlxsw_sp_port *mlxsw_sp_port = netdev_priv(dev);
	काष्ठा sockaddr *addr = p;
	पूर्णांक err;

	अगर (!is_valid_ether_addr(addr->sa_data))
		वापस -EADDRNOTAVAIL;

	err = mlxsw_sp_port_dev_addr_set(mlxsw_sp_port, addr->sa_data);
	अगर (err)
		वापस err;
	स_नकल(dev->dev_addr, addr->sa_data, dev->addr_len);
	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_sp_port_change_mtu(काष्ठा net_device *dev, पूर्णांक mtu)
अणु
	काष्ठा mlxsw_sp_port *mlxsw_sp_port = netdev_priv(dev);
	काष्ठा mlxsw_sp_hdroom orig_hdroom;
	काष्ठा mlxsw_sp_hdroom hdroom;
	पूर्णांक err;

	orig_hdroom = *mlxsw_sp_port->hdroom;

	hdroom = orig_hdroom;
	hdroom.mtu = mtu;
	mlxsw_sp_hdroom_bufs_reset_sizes(mlxsw_sp_port, &hdroom);

	err = mlxsw_sp_hdroom_configure(mlxsw_sp_port, &hdroom);
	अगर (err) अणु
		netdev_err(dev, "Failed to configure port's headroom\n");
		वापस err;
	पूर्ण

	err = mlxsw_sp_port_mtu_set(mlxsw_sp_port, mtu);
	अगर (err)
		जाओ err_port_mtu_set;
	dev->mtu = mtu;
	वापस 0;

err_port_mtu_set:
	mlxsw_sp_hdroom_configure(mlxsw_sp_port, &orig_hdroom);
	वापस err;
पूर्ण

अटल पूर्णांक
mlxsw_sp_port_get_sw_stats64(स्थिर काष्ठा net_device *dev,
			     काष्ठा rtnl_link_stats64 *stats)
अणु
	काष्ठा mlxsw_sp_port *mlxsw_sp_port = netdev_priv(dev);
	काष्ठा mlxsw_sp_port_pcpu_stats *p;
	u64 rx_packets, rx_bytes, tx_packets, tx_bytes;
	u32 tx_dropped = 0;
	अचिन्हित पूर्णांक start;
	पूर्णांक i;

	क्रम_each_possible_cpu(i) अणु
		p = per_cpu_ptr(mlxsw_sp_port->pcpu_stats, i);
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
	वापस 0;
पूर्ण

अटल bool mlxsw_sp_port_has_offload_stats(स्थिर काष्ठा net_device *dev, पूर्णांक attr_id)
अणु
	चयन (attr_id) अणु
	हाल IFLA_OFFLOAD_XSTATS_CPU_HIT:
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक mlxsw_sp_port_get_offload_stats(पूर्णांक attr_id, स्थिर काष्ठा net_device *dev,
					   व्योम *sp)
अणु
	चयन (attr_id) अणु
	हाल IFLA_OFFLOAD_XSTATS_CPU_HIT:
		वापस mlxsw_sp_port_get_sw_stats64(dev, sp);
	पूर्ण

	वापस -EINVAL;
पूर्ण

पूर्णांक mlxsw_sp_port_get_stats_raw(काष्ठा net_device *dev, पूर्णांक grp,
				पूर्णांक prio, अक्षर *ppcnt_pl)
अणु
	काष्ठा mlxsw_sp_port *mlxsw_sp_port = netdev_priv(dev);
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;

	mlxsw_reg_ppcnt_pack(ppcnt_pl, mlxsw_sp_port->local_port, grp, prio);
	वापस mlxsw_reg_query(mlxsw_sp->core, MLXSW_REG(ppcnt), ppcnt_pl);
पूर्ण

अटल पूर्णांक mlxsw_sp_port_get_hw_stats(काष्ठा net_device *dev,
				      काष्ठा rtnl_link_stats64 *stats)
अणु
	अक्षर ppcnt_pl[MLXSW_REG_PPCNT_LEN];
	पूर्णांक err;

	err = mlxsw_sp_port_get_stats_raw(dev, MLXSW_REG_PPCNT_IEEE_8023_CNT,
					  0, ppcnt_pl);
	अगर (err)
		जाओ out;

	stats->tx_packets =
		mlxsw_reg_ppcnt_a_frames_transmitted_ok_get(ppcnt_pl);
	stats->rx_packets =
		mlxsw_reg_ppcnt_a_frames_received_ok_get(ppcnt_pl);
	stats->tx_bytes =
		mlxsw_reg_ppcnt_a_octets_transmitted_ok_get(ppcnt_pl);
	stats->rx_bytes =
		mlxsw_reg_ppcnt_a_octets_received_ok_get(ppcnt_pl);
	stats->multicast =
		mlxsw_reg_ppcnt_a_multicast_frames_received_ok_get(ppcnt_pl);

	stats->rx_crc_errors =
		mlxsw_reg_ppcnt_a_frame_check_sequence_errors_get(ppcnt_pl);
	stats->rx_frame_errors =
		mlxsw_reg_ppcnt_a_alignment_errors_get(ppcnt_pl);

	stats->rx_length_errors = (
		mlxsw_reg_ppcnt_a_in_range_length_errors_get(ppcnt_pl) +
		mlxsw_reg_ppcnt_a_out_of_range_length_field_get(ppcnt_pl) +
		mlxsw_reg_ppcnt_a_frame_too_दीर्घ_errors_get(ppcnt_pl));

	stats->rx_errors = (stats->rx_crc_errors +
		stats->rx_frame_errors + stats->rx_length_errors);

out:
	वापस err;
पूर्ण

अटल व्योम
mlxsw_sp_port_get_hw_xstats(काष्ठा net_device *dev,
			    काष्ठा mlxsw_sp_port_xstats *xstats)
अणु
	अक्षर ppcnt_pl[MLXSW_REG_PPCNT_LEN];
	पूर्णांक err, i;

	err = mlxsw_sp_port_get_stats_raw(dev, MLXSW_REG_PPCNT_EXT_CNT, 0,
					  ppcnt_pl);
	अगर (!err)
		xstats->ecn = mlxsw_reg_ppcnt_ecn_marked_get(ppcnt_pl);

	क्रम (i = 0; i < TC_MAX_QUEUE; i++) अणु
		err = mlxsw_sp_port_get_stats_raw(dev,
						  MLXSW_REG_PPCNT_TC_CONG_TC,
						  i, ppcnt_pl);
		अगर (!err)
			xstats->wred_drop[i] =
				mlxsw_reg_ppcnt_wred_discard_get(ppcnt_pl);

		err = mlxsw_sp_port_get_stats_raw(dev, MLXSW_REG_PPCNT_TC_CNT,
						  i, ppcnt_pl);
		अगर (err)
			जारी;

		xstats->backlog[i] =
			mlxsw_reg_ppcnt_tc_transmit_queue_get(ppcnt_pl);
		xstats->tail_drop[i] =
			mlxsw_reg_ppcnt_tc_no_buffer_discard_uc_get(ppcnt_pl);
	पूर्ण

	क्रम (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++) अणु
		err = mlxsw_sp_port_get_stats_raw(dev, MLXSW_REG_PPCNT_PRIO_CNT,
						  i, ppcnt_pl);
		अगर (err)
			जारी;

		xstats->tx_packets[i] = mlxsw_reg_ppcnt_tx_frames_get(ppcnt_pl);
		xstats->tx_bytes[i] = mlxsw_reg_ppcnt_tx_octets_get(ppcnt_pl);
	पूर्ण
पूर्ण

अटल व्योम update_stats_cache(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mlxsw_sp_port *mlxsw_sp_port =
		container_of(work, काष्ठा mlxsw_sp_port,
			     periodic_hw_stats.update_dw.work);

	अगर (!netअगर_carrier_ok(mlxsw_sp_port->dev))
		/* Note: mlxsw_sp_port_करोwn_wipe_counters() clears the cache as
		 * necessary when port goes करोwn.
		 */
		जाओ out;

	mlxsw_sp_port_get_hw_stats(mlxsw_sp_port->dev,
				   &mlxsw_sp_port->periodic_hw_stats.stats);
	mlxsw_sp_port_get_hw_xstats(mlxsw_sp_port->dev,
				    &mlxsw_sp_port->periodic_hw_stats.xstats);

out:
	mlxsw_core_schedule_dw(&mlxsw_sp_port->periodic_hw_stats.update_dw,
			       MLXSW_HW_STATS_UPDATE_TIME);
पूर्ण

/* Return the stats from a cache that is updated periodically,
 * as this function might get called in an atomic context.
 */
अटल व्योम
mlxsw_sp_port_get_stats64(काष्ठा net_device *dev,
			  काष्ठा rtnl_link_stats64 *stats)
अणु
	काष्ठा mlxsw_sp_port *mlxsw_sp_port = netdev_priv(dev);

	स_नकल(stats, &mlxsw_sp_port->periodic_hw_stats.stats, माप(*stats));
पूर्ण

अटल पूर्णांक __mlxsw_sp_port_vlan_set(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				    u16 vid_begin, u16 vid_end,
				    bool is_member, bool untagged)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	अक्षर *spvm_pl;
	पूर्णांक err;

	spvm_pl = kदो_स्मृति(MLXSW_REG_SPVM_LEN, GFP_KERNEL);
	अगर (!spvm_pl)
		वापस -ENOMEM;

	mlxsw_reg_spvm_pack(spvm_pl, mlxsw_sp_port->local_port,	vid_begin,
			    vid_end, is_member, untagged);
	err = mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(spvm), spvm_pl);
	kमुक्त(spvm_pl);
	वापस err;
पूर्ण

पूर्णांक mlxsw_sp_port_vlan_set(काष्ठा mlxsw_sp_port *mlxsw_sp_port, u16 vid_begin,
			   u16 vid_end, bool is_member, bool untagged)
अणु
	u16 vid, vid_e;
	पूर्णांक err;

	क्रम (vid = vid_begin; vid <= vid_end;
	     vid += MLXSW_REG_SPVM_REC_MAX_COUNT) अणु
		vid_e = min((u16) (vid + MLXSW_REG_SPVM_REC_MAX_COUNT - 1),
			    vid_end);

		err = __mlxsw_sp_port_vlan_set(mlxsw_sp_port, vid, vid_e,
					       is_member, untagged);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mlxsw_sp_port_vlan_flush(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				     bool flush_शेष)
अणु
	काष्ठा mlxsw_sp_port_vlan *mlxsw_sp_port_vlan, *पंचांगp;

	list_क्रम_each_entry_safe(mlxsw_sp_port_vlan, पंचांगp,
				 &mlxsw_sp_port->vlans_list, list) अणु
		अगर (!flush_शेष &&
		    mlxsw_sp_port_vlan->vid == MLXSW_SP_DEFAULT_VID)
			जारी;
		mlxsw_sp_port_vlan_destroy(mlxsw_sp_port_vlan);
	पूर्ण
पूर्ण

अटल व्योम
mlxsw_sp_port_vlan_cleanup(काष्ठा mlxsw_sp_port_vlan *mlxsw_sp_port_vlan)
अणु
	अगर (mlxsw_sp_port_vlan->bridge_port)
		mlxsw_sp_port_vlan_bridge_leave(mlxsw_sp_port_vlan);
	अन्यथा अगर (mlxsw_sp_port_vlan->fid)
		mlxsw_sp_port_vlan_router_leave(mlxsw_sp_port_vlan);
पूर्ण

काष्ठा mlxsw_sp_port_vlan *
mlxsw_sp_port_vlan_create(काष्ठा mlxsw_sp_port *mlxsw_sp_port, u16 vid)
अणु
	काष्ठा mlxsw_sp_port_vlan *mlxsw_sp_port_vlan;
	bool untagged = vid == MLXSW_SP_DEFAULT_VID;
	पूर्णांक err;

	mlxsw_sp_port_vlan = mlxsw_sp_port_vlan_find_by_vid(mlxsw_sp_port, vid);
	अगर (mlxsw_sp_port_vlan)
		वापस ERR_PTR(-EEXIST);

	err = mlxsw_sp_port_vlan_set(mlxsw_sp_port, vid, vid, true, untagged);
	अगर (err)
		वापस ERR_PTR(err);

	mlxsw_sp_port_vlan = kzalloc(माप(*mlxsw_sp_port_vlan), GFP_KERNEL);
	अगर (!mlxsw_sp_port_vlan) अणु
		err = -ENOMEM;
		जाओ err_port_vlan_alloc;
	पूर्ण

	mlxsw_sp_port_vlan->mlxsw_sp_port = mlxsw_sp_port;
	mlxsw_sp_port_vlan->vid = vid;
	list_add(&mlxsw_sp_port_vlan->list, &mlxsw_sp_port->vlans_list);

	वापस mlxsw_sp_port_vlan;

err_port_vlan_alloc:
	mlxsw_sp_port_vlan_set(mlxsw_sp_port, vid, vid, false, false);
	वापस ERR_PTR(err);
पूर्ण

व्योम mlxsw_sp_port_vlan_destroy(काष्ठा mlxsw_sp_port_vlan *mlxsw_sp_port_vlan)
अणु
	काष्ठा mlxsw_sp_port *mlxsw_sp_port = mlxsw_sp_port_vlan->mlxsw_sp_port;
	u16 vid = mlxsw_sp_port_vlan->vid;

	mlxsw_sp_port_vlan_cleanup(mlxsw_sp_port_vlan);
	list_del(&mlxsw_sp_port_vlan->list);
	kमुक्त(mlxsw_sp_port_vlan);
	mlxsw_sp_port_vlan_set(mlxsw_sp_port, vid, vid, false, false);
पूर्ण

अटल पूर्णांक mlxsw_sp_port_add_vid(काष्ठा net_device *dev,
				 __be16 __always_unused proto, u16 vid)
अणु
	काष्ठा mlxsw_sp_port *mlxsw_sp_port = netdev_priv(dev);

	/* VLAN 0 is added to HW filter when device goes up, but it is
	 * reserved in our हाल, so simply वापस.
	 */
	अगर (!vid)
		वापस 0;

	वापस PTR_ERR_OR_ZERO(mlxsw_sp_port_vlan_create(mlxsw_sp_port, vid));
पूर्ण

अटल पूर्णांक mlxsw_sp_port_समाप्त_vid(काष्ठा net_device *dev,
				  __be16 __always_unused proto, u16 vid)
अणु
	काष्ठा mlxsw_sp_port *mlxsw_sp_port = netdev_priv(dev);
	काष्ठा mlxsw_sp_port_vlan *mlxsw_sp_port_vlan;

	/* VLAN 0 is हटाओd from HW filter when device goes करोwn, but
	 * it is reserved in our हाल, so simply वापस.
	 */
	अगर (!vid)
		वापस 0;

	mlxsw_sp_port_vlan = mlxsw_sp_port_vlan_find_by_vid(mlxsw_sp_port, vid);
	अगर (!mlxsw_sp_port_vlan)
		वापस 0;
	mlxsw_sp_port_vlan_destroy(mlxsw_sp_port_vlan);

	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_sp_setup_tc_block(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				   काष्ठा flow_block_offload *f)
अणु
	चयन (f->binder_type) अणु
	हाल FLOW_BLOCK_BINDER_TYPE_CLSACT_INGRESS:
		वापस mlxsw_sp_setup_tc_block_clsact(mlxsw_sp_port, f, true);
	हाल FLOW_BLOCK_BINDER_TYPE_CLSACT_EGRESS:
		वापस mlxsw_sp_setup_tc_block_clsact(mlxsw_sp_port, f, false);
	हाल FLOW_BLOCK_BINDER_TYPE_RED_EARLY_DROP:
		वापस mlxsw_sp_setup_tc_block_qevent_early_drop(mlxsw_sp_port, f);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक mlxsw_sp_setup_tc(काष्ठा net_device *dev, क्रमागत tc_setup_type type,
			     व्योम *type_data)
अणु
	काष्ठा mlxsw_sp_port *mlxsw_sp_port = netdev_priv(dev);

	चयन (type) अणु
	हाल TC_SETUP_BLOCK:
		वापस mlxsw_sp_setup_tc_block(mlxsw_sp_port, type_data);
	हाल TC_SETUP_QDISC_RED:
		वापस mlxsw_sp_setup_tc_red(mlxsw_sp_port, type_data);
	हाल TC_SETUP_QDISC_PRIO:
		वापस mlxsw_sp_setup_tc_prio(mlxsw_sp_port, type_data);
	हाल TC_SETUP_QDISC_ETS:
		वापस mlxsw_sp_setup_tc_ets(mlxsw_sp_port, type_data);
	हाल TC_SETUP_QDISC_TBF:
		वापस mlxsw_sp_setup_tc_tbf(mlxsw_sp_port, type_data);
	हाल TC_SETUP_QDISC_FIFO:
		वापस mlxsw_sp_setup_tc_fअगरo(mlxsw_sp_port, type_data);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक mlxsw_sp_feature_hw_tc(काष्ठा net_device *dev, bool enable)
अणु
	काष्ठा mlxsw_sp_port *mlxsw_sp_port = netdev_priv(dev);

	अगर (!enable) अणु
		अगर (mlxsw_sp_flow_block_rule_count(mlxsw_sp_port->ing_flow_block) ||
		    mlxsw_sp_flow_block_rule_count(mlxsw_sp_port->eg_flow_block)) अणु
			netdev_err(dev, "Active offloaded tc filters, can't turn hw_tc_offload off\n");
			वापस -EINVAL;
		पूर्ण
		mlxsw_sp_flow_block_disable_inc(mlxsw_sp_port->ing_flow_block);
		mlxsw_sp_flow_block_disable_inc(mlxsw_sp_port->eg_flow_block);
	पूर्ण अन्यथा अणु
		mlxsw_sp_flow_block_disable_dec(mlxsw_sp_port->ing_flow_block);
		mlxsw_sp_flow_block_disable_dec(mlxsw_sp_port->eg_flow_block);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_sp_feature_loopback(काष्ठा net_device *dev, bool enable)
अणु
	काष्ठा mlxsw_sp_port *mlxsw_sp_port = netdev_priv(dev);
	अक्षर pplr_pl[MLXSW_REG_PPLR_LEN];
	पूर्णांक err;

	अगर (netअगर_running(dev))
		mlxsw_sp_port_admin_status_set(mlxsw_sp_port, false);

	mlxsw_reg_pplr_pack(pplr_pl, mlxsw_sp_port->local_port, enable);
	err = mlxsw_reg_ग_लिखो(mlxsw_sp_port->mlxsw_sp->core, MLXSW_REG(pplr),
			      pplr_pl);

	अगर (netअगर_running(dev))
		mlxsw_sp_port_admin_status_set(mlxsw_sp_port, true);

	वापस err;
पूर्ण

प्रकार पूर्णांक (*mlxsw_sp_feature_handler)(काष्ठा net_device *dev, bool enable);

अटल पूर्णांक mlxsw_sp_handle_feature(काष्ठा net_device *dev,
				   netdev_features_t wanted_features,
				   netdev_features_t feature,
				   mlxsw_sp_feature_handler feature_handler)
अणु
	netdev_features_t changes = wanted_features ^ dev->features;
	bool enable = !!(wanted_features & feature);
	पूर्णांक err;

	अगर (!(changes & feature))
		वापस 0;

	err = feature_handler(dev, enable);
	अगर (err) अणु
		netdev_err(dev, "%s feature %pNF failed, err %d\n",
			   enable ? "Enable" : "Disable", &feature, err);
		वापस err;
	पूर्ण

	अगर (enable)
		dev->features |= feature;
	अन्यथा
		dev->features &= ~feature;

	वापस 0;
पूर्ण
अटल पूर्णांक mlxsw_sp_set_features(काष्ठा net_device *dev,
				 netdev_features_t features)
अणु
	netdev_features_t oper_features = dev->features;
	पूर्णांक err = 0;

	err |= mlxsw_sp_handle_feature(dev, features, NETIF_F_HW_TC,
				       mlxsw_sp_feature_hw_tc);
	err |= mlxsw_sp_handle_feature(dev, features, NETIF_F_LOOPBACK,
				       mlxsw_sp_feature_loopback);

	अगर (err) अणु
		dev->features = oper_features;
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा devlink_port *
mlxsw_sp_port_get_devlink_port(काष्ठा net_device *dev)
अणु
	काष्ठा mlxsw_sp_port *mlxsw_sp_port = netdev_priv(dev);
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;

	वापस mlxsw_core_port_devlink_port_get(mlxsw_sp->core,
						mlxsw_sp_port->local_port);
पूर्ण

अटल पूर्णांक mlxsw_sp_port_hwtstamp_set(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				      काष्ठा अगरreq *अगरr)
अणु
	काष्ठा hwtstamp_config config;
	पूर्णांक err;

	अगर (copy_from_user(&config, अगरr->अगरr_data, माप(config)))
		वापस -EFAULT;

	err = mlxsw_sp_port->mlxsw_sp->ptp_ops->hwtstamp_set(mlxsw_sp_port,
							     &config);
	अगर (err)
		वापस err;

	अगर (copy_to_user(अगरr->अगरr_data, &config, माप(config)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_sp_port_hwtstamp_get(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				      काष्ठा अगरreq *अगरr)
अणु
	काष्ठा hwtstamp_config config;
	पूर्णांक err;

	err = mlxsw_sp_port->mlxsw_sp->ptp_ops->hwtstamp_get(mlxsw_sp_port,
							     &config);
	अगर (err)
		वापस err;

	अगर (copy_to_user(अगरr->अगरr_data, &config, माप(config)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम mlxsw_sp_port_ptp_clear(काष्ठा mlxsw_sp_port *mlxsw_sp_port)
अणु
	काष्ठा hwtstamp_config config = अणु0पूर्ण;

	mlxsw_sp_port->mlxsw_sp->ptp_ops->hwtstamp_set(mlxsw_sp_port, &config);
पूर्ण

अटल पूर्णांक
mlxsw_sp_port_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	काष्ठा mlxsw_sp_port *mlxsw_sp_port = netdev_priv(dev);

	चयन (cmd) अणु
	हाल SIOCSHWTSTAMP:
		वापस mlxsw_sp_port_hwtstamp_set(mlxsw_sp_port, अगरr);
	हाल SIOCGHWTSTAMP:
		वापस mlxsw_sp_port_hwtstamp_get(mlxsw_sp_port, अगरr);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा net_device_ops mlxsw_sp_port_netdev_ops = अणु
	.nकरो_खोलो		= mlxsw_sp_port_खोलो,
	.nकरो_stop		= mlxsw_sp_port_stop,
	.nकरो_start_xmit		= mlxsw_sp_port_xmit,
	.nकरो_setup_tc           = mlxsw_sp_setup_tc,
	.nकरो_set_rx_mode	= mlxsw_sp_set_rx_mode,
	.nकरो_set_mac_address	= mlxsw_sp_port_set_mac_address,
	.nकरो_change_mtu		= mlxsw_sp_port_change_mtu,
	.nकरो_get_stats64	= mlxsw_sp_port_get_stats64,
	.nकरो_has_offload_stats	= mlxsw_sp_port_has_offload_stats,
	.nकरो_get_offload_stats	= mlxsw_sp_port_get_offload_stats,
	.nकरो_vlan_rx_add_vid	= mlxsw_sp_port_add_vid,
	.nकरो_vlan_rx_समाप्त_vid	= mlxsw_sp_port_समाप्त_vid,
	.nकरो_set_features	= mlxsw_sp_set_features,
	.nकरो_get_devlink_port	= mlxsw_sp_port_get_devlink_port,
	.nकरो_करो_ioctl		= mlxsw_sp_port_ioctl,
पूर्ण;

अटल पूर्णांक
mlxsw_sp_port_speed_by_width_set(काष्ठा mlxsw_sp_port *mlxsw_sp_port)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	u32 eth_proto_cap, eth_proto_admin, eth_proto_oper;
	स्थिर काष्ठा mlxsw_sp_port_type_speed_ops *ops;
	अक्षर ptys_pl[MLXSW_REG_PTYS_LEN];
	u32 eth_proto_cap_masked;
	पूर्णांक err;

	ops = mlxsw_sp->port_type_speed_ops;

	/* Set advertised speeds to speeds supported by both the driver
	 * and the device.
	 */
	ops->reg_ptys_eth_pack(mlxsw_sp, ptys_pl, mlxsw_sp_port->local_port,
			       0, false);
	err = mlxsw_reg_query(mlxsw_sp->core, MLXSW_REG(ptys), ptys_pl);
	अगर (err)
		वापस err;

	ops->reg_ptys_eth_unpack(mlxsw_sp, ptys_pl, &eth_proto_cap,
				 &eth_proto_admin, &eth_proto_oper);
	eth_proto_cap_masked = ops->ptys_proto_cap_masked_get(eth_proto_cap);
	ops->reg_ptys_eth_pack(mlxsw_sp, ptys_pl, mlxsw_sp_port->local_port,
			       eth_proto_cap_masked,
			       mlxsw_sp_port->link.स्वतःneg);
	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(ptys), ptys_pl);
पूर्ण

पूर्णांक mlxsw_sp_port_speed_get(काष्ठा mlxsw_sp_port *mlxsw_sp_port, u32 *speed)
अणु
	स्थिर काष्ठा mlxsw_sp_port_type_speed_ops *port_type_speed_ops;
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	अक्षर ptys_pl[MLXSW_REG_PTYS_LEN];
	u32 eth_proto_oper;
	पूर्णांक err;

	port_type_speed_ops = mlxsw_sp->port_type_speed_ops;
	port_type_speed_ops->reg_ptys_eth_pack(mlxsw_sp, ptys_pl,
					       mlxsw_sp_port->local_port, 0,
					       false);
	err = mlxsw_reg_query(mlxsw_sp->core, MLXSW_REG(ptys), ptys_pl);
	अगर (err)
		वापस err;
	port_type_speed_ops->reg_ptys_eth_unpack(mlxsw_sp, ptys_pl, शून्य, शून्य,
						 &eth_proto_oper);
	*speed = port_type_speed_ops->from_ptys_speed(mlxsw_sp, eth_proto_oper);
	वापस 0;
पूर्ण

पूर्णांक mlxsw_sp_port_ets_set(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
			  क्रमागत mlxsw_reg_qeec_hr hr, u8 index, u8 next_index,
			  bool dwrr, u8 dwrr_weight)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	अक्षर qeec_pl[MLXSW_REG_QEEC_LEN];

	mlxsw_reg_qeec_pack(qeec_pl, mlxsw_sp_port->local_port, hr, index,
			    next_index);
	mlxsw_reg_qeec_de_set(qeec_pl, true);
	mlxsw_reg_qeec_dwrr_set(qeec_pl, dwrr);
	mlxsw_reg_qeec_dwrr_weight_set(qeec_pl, dwrr_weight);
	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(qeec), qeec_pl);
पूर्ण

पूर्णांक mlxsw_sp_port_ets_maxrate_set(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				  क्रमागत mlxsw_reg_qeec_hr hr, u8 index,
				  u8 next_index, u32 maxrate, u8 burst_size)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	अक्षर qeec_pl[MLXSW_REG_QEEC_LEN];

	mlxsw_reg_qeec_pack(qeec_pl, mlxsw_sp_port->local_port, hr, index,
			    next_index);
	mlxsw_reg_qeec_mase_set(qeec_pl, true);
	mlxsw_reg_qeec_max_shaper_rate_set(qeec_pl, maxrate);
	mlxsw_reg_qeec_max_shaper_bs_set(qeec_pl, burst_size);
	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(qeec), qeec_pl);
पूर्ण

अटल पूर्णांक mlxsw_sp_port_min_bw_set(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				    क्रमागत mlxsw_reg_qeec_hr hr, u8 index,
				    u8 next_index, u32 minrate)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	अक्षर qeec_pl[MLXSW_REG_QEEC_LEN];

	mlxsw_reg_qeec_pack(qeec_pl, mlxsw_sp_port->local_port, hr, index,
			    next_index);
	mlxsw_reg_qeec_mise_set(qeec_pl, true);
	mlxsw_reg_qeec_min_shaper_rate_set(qeec_pl, minrate);

	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(qeec), qeec_pl);
पूर्ण

पूर्णांक mlxsw_sp_port_prio_tc_set(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
			      u8 चयन_prio, u8 tclass)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	अक्षर qtct_pl[MLXSW_REG_QTCT_LEN];

	mlxsw_reg_qtct_pack(qtct_pl, mlxsw_sp_port->local_port, चयन_prio,
			    tclass);
	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(qtct), qtct_pl);
पूर्ण

अटल पूर्णांक mlxsw_sp_port_ets_init(काष्ठा mlxsw_sp_port *mlxsw_sp_port)
अणु
	पूर्णांक err, i;

	/* Setup the elements hierarcy, so that each TC is linked to
	 * one subgroup, which are all member in the same group.
	 */
	err = mlxsw_sp_port_ets_set(mlxsw_sp_port,
				    MLXSW_REG_QEEC_HR_GROUP, 0, 0, false, 0);
	अगर (err)
		वापस err;
	क्रम (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++) अणु
		err = mlxsw_sp_port_ets_set(mlxsw_sp_port,
					    MLXSW_REG_QEEC_HR_SUBGROUP, i,
					    0, false, 0);
		अगर (err)
			वापस err;
	पूर्ण
	क्रम (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++) अणु
		err = mlxsw_sp_port_ets_set(mlxsw_sp_port,
					    MLXSW_REG_QEEC_HR_TC, i, i,
					    false, 0);
		अगर (err)
			वापस err;

		err = mlxsw_sp_port_ets_set(mlxsw_sp_port,
					    MLXSW_REG_QEEC_HR_TC,
					    i + 8, i,
					    true, 100);
		अगर (err)
			वापस err;
	पूर्ण

	/* Make sure the max shaper is disabled in all hierarchies that support
	 * it. Note that this disables ptps (PTP shaper), but that is पूर्णांकended
	 * क्रम the initial configuration.
	 */
	err = mlxsw_sp_port_ets_maxrate_set(mlxsw_sp_port,
					    MLXSW_REG_QEEC_HR_PORT, 0, 0,
					    MLXSW_REG_QEEC_MAS_DIS, 0);
	अगर (err)
		वापस err;
	क्रम (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++) अणु
		err = mlxsw_sp_port_ets_maxrate_set(mlxsw_sp_port,
						    MLXSW_REG_QEEC_HR_SUBGROUP,
						    i, 0,
						    MLXSW_REG_QEEC_MAS_DIS, 0);
		अगर (err)
			वापस err;
	पूर्ण
	क्रम (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++) अणु
		err = mlxsw_sp_port_ets_maxrate_set(mlxsw_sp_port,
						    MLXSW_REG_QEEC_HR_TC,
						    i, i,
						    MLXSW_REG_QEEC_MAS_DIS, 0);
		अगर (err)
			वापस err;

		err = mlxsw_sp_port_ets_maxrate_set(mlxsw_sp_port,
						    MLXSW_REG_QEEC_HR_TC,
						    i + 8, i,
						    MLXSW_REG_QEEC_MAS_DIS, 0);
		अगर (err)
			वापस err;
	पूर्ण

	/* Configure the min shaper क्रम multicast TCs. */
	क्रम (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++) अणु
		err = mlxsw_sp_port_min_bw_set(mlxsw_sp_port,
					       MLXSW_REG_QEEC_HR_TC,
					       i + 8, i,
					       MLXSW_REG_QEEC_MIS_MIN);
		अगर (err)
			वापस err;
	पूर्ण

	/* Map all priorities to traffic class 0. */
	क्रम (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++) अणु
		err = mlxsw_sp_port_prio_tc_set(mlxsw_sp_port, i, 0);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_sp_port_tc_mc_mode_set(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
					bool enable)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	अक्षर qtcपंचांग_pl[MLXSW_REG_QTCTM_LEN];

	mlxsw_reg_qtcपंचांग_pack(qtcपंचांग_pl, mlxsw_sp_port->local_port, enable);
	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(qtcपंचांग), qtcपंचांग_pl);
पूर्ण

अटल पूर्णांक mlxsw_sp_port_overheat_init_val_set(काष्ठा mlxsw_sp_port *mlxsw_sp_port)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	u8 module = mlxsw_sp_port->mapping.module;
	u64 overheat_counter;
	पूर्णांक err;

	err = mlxsw_env_module_overheat_counter_get(mlxsw_sp->core, module,
						    &overheat_counter);
	अगर (err)
		वापस err;

	mlxsw_sp_port->module_overheat_initial_val = overheat_counter;
	वापस 0;
पूर्ण

पूर्णांक
mlxsw_sp_port_vlan_classअगरication_set(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				      bool is_8021ad_tagged,
				      bool is_8021q_tagged)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	अक्षर spvc_pl[MLXSW_REG_SPVC_LEN];

	mlxsw_reg_spvc_pack(spvc_pl, mlxsw_sp_port->local_port,
			    is_8021ad_tagged, is_8021q_tagged);
	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(spvc), spvc_pl);
पूर्ण

अटल पूर्णांक mlxsw_sp_port_create(काष्ठा mlxsw_sp *mlxsw_sp, u8 local_port,
				u8 split_base_local_port,
				काष्ठा mlxsw_sp_port_mapping *port_mapping)
अणु
	काष्ठा mlxsw_sp_port_vlan *mlxsw_sp_port_vlan;
	bool split = !!split_base_local_port;
	काष्ठा mlxsw_sp_port *mlxsw_sp_port;
	u32 lanes = port_mapping->width;
	काष्ठा net_device *dev;
	bool splittable;
	पूर्णांक err;

	splittable = lanes > 1 && !split;
	err = mlxsw_core_port_init(mlxsw_sp->core, local_port,
				   port_mapping->module + 1, split,
				   port_mapping->lane / lanes,
				   splittable, lanes,
				   mlxsw_sp->base_mac,
				   माप(mlxsw_sp->base_mac));
	अगर (err) अणु
		dev_err(mlxsw_sp->bus_info->dev, "Port %d: Failed to init core port\n",
			local_port);
		वापस err;
	पूर्ण

	dev = alloc_etherdev(माप(काष्ठा mlxsw_sp_port));
	अगर (!dev) अणु
		err = -ENOMEM;
		जाओ err_alloc_etherdev;
	पूर्ण
	SET_NETDEV_DEV(dev, mlxsw_sp->bus_info->dev);
	dev_net_set(dev, mlxsw_sp_net(mlxsw_sp));
	mlxsw_sp_port = netdev_priv(dev);
	mlxsw_sp_port->dev = dev;
	mlxsw_sp_port->mlxsw_sp = mlxsw_sp;
	mlxsw_sp_port->local_port = local_port;
	mlxsw_sp_port->pvid = MLXSW_SP_DEFAULT_VID;
	mlxsw_sp_port->split = split;
	mlxsw_sp_port->split_base_local_port = split_base_local_port;
	mlxsw_sp_port->mapping = *port_mapping;
	mlxsw_sp_port->link.स्वतःneg = 1;
	INIT_LIST_HEAD(&mlxsw_sp_port->vlans_list);

	mlxsw_sp_port->pcpu_stats =
		netdev_alloc_pcpu_stats(काष्ठा mlxsw_sp_port_pcpu_stats);
	अगर (!mlxsw_sp_port->pcpu_stats) अणु
		err = -ENOMEM;
		जाओ err_alloc_stats;
	पूर्ण

	INIT_DELAYED_WORK(&mlxsw_sp_port->periodic_hw_stats.update_dw,
			  &update_stats_cache);

	dev->netdev_ops = &mlxsw_sp_port_netdev_ops;
	dev->ethtool_ops = &mlxsw_sp_port_ethtool_ops;

	err = mlxsw_sp_port_module_map(mlxsw_sp_port);
	अगर (err) अणु
		dev_err(mlxsw_sp->bus_info->dev, "Port %d: Failed to map module\n",
			mlxsw_sp_port->local_port);
		जाओ err_port_module_map;
	पूर्ण

	err = mlxsw_sp_port_swid_set(mlxsw_sp_port, 0);
	अगर (err) अणु
		dev_err(mlxsw_sp->bus_info->dev, "Port %d: Failed to set SWID\n",
			mlxsw_sp_port->local_port);
		जाओ err_port_swid_set;
	पूर्ण

	err = mlxsw_sp_port_dev_addr_init(mlxsw_sp_port);
	अगर (err) अणु
		dev_err(mlxsw_sp->bus_info->dev, "Port %d: Unable to init port mac address\n",
			mlxsw_sp_port->local_port);
		जाओ err_dev_addr_init;
	पूर्ण

	netअगर_carrier_off(dev);

	dev->features |= NETIF_F_NETNS_LOCAL | NETIF_F_LLTX | NETIF_F_SG |
			 NETIF_F_HW_VLAN_CTAG_FILTER | NETIF_F_HW_TC;
	dev->hw_features |= NETIF_F_HW_TC | NETIF_F_LOOPBACK;

	dev->min_mtu = 0;
	dev->max_mtu = ETH_MAX_MTU;

	/* Each packet needs to have a Tx header (metadata) on top all other
	 * headers.
	 */
	dev->needed_headroom = MLXSW_TXHDR_LEN;

	err = mlxsw_sp_port_प्रणाली_port_mapping_set(mlxsw_sp_port);
	अगर (err) अणु
		dev_err(mlxsw_sp->bus_info->dev, "Port %d: Failed to set system port mapping\n",
			mlxsw_sp_port->local_port);
		जाओ err_port_प्रणाली_port_mapping_set;
	पूर्ण

	err = mlxsw_sp_port_speed_by_width_set(mlxsw_sp_port);
	अगर (err) अणु
		dev_err(mlxsw_sp->bus_info->dev, "Port %d: Failed to enable speeds\n",
			mlxsw_sp_port->local_port);
		जाओ err_port_speed_by_width_set;
	पूर्ण

	err = mlxsw_sp->port_type_speed_ops->ptys_max_speed(mlxsw_sp_port,
							    &mlxsw_sp_port->max_speed);
	अगर (err) अणु
		dev_err(mlxsw_sp->bus_info->dev, "Port %d: Failed to get maximum speed\n",
			mlxsw_sp_port->local_port);
		जाओ err_max_speed_get;
	पूर्ण

	err = mlxsw_sp_port_max_mtu_get(mlxsw_sp_port, &mlxsw_sp_port->max_mtu);
	अगर (err) अणु
		dev_err(mlxsw_sp->bus_info->dev, "Port %d: Failed to get maximum MTU\n",
			mlxsw_sp_port->local_port);
		जाओ err_port_max_mtu_get;
	पूर्ण

	err = mlxsw_sp_port_mtu_set(mlxsw_sp_port, ETH_DATA_LEN);
	अगर (err) अणु
		dev_err(mlxsw_sp->bus_info->dev, "Port %d: Failed to set MTU\n",
			mlxsw_sp_port->local_port);
		जाओ err_port_mtu_set;
	पूर्ण

	err = mlxsw_sp_port_admin_status_set(mlxsw_sp_port, false);
	अगर (err)
		जाओ err_port_admin_status_set;

	err = mlxsw_sp_port_buffers_init(mlxsw_sp_port);
	अगर (err) अणु
		dev_err(mlxsw_sp->bus_info->dev, "Port %d: Failed to initialize buffers\n",
			mlxsw_sp_port->local_port);
		जाओ err_port_buffers_init;
	पूर्ण

	err = mlxsw_sp_port_ets_init(mlxsw_sp_port);
	अगर (err) अणु
		dev_err(mlxsw_sp->bus_info->dev, "Port %d: Failed to initialize ETS\n",
			mlxsw_sp_port->local_port);
		जाओ err_port_ets_init;
	पूर्ण

	err = mlxsw_sp_port_tc_mc_mode_set(mlxsw_sp_port, true);
	अगर (err) अणु
		dev_err(mlxsw_sp->bus_info->dev, "Port %d: Failed to initialize TC MC mode\n",
			mlxsw_sp_port->local_port);
		जाओ err_port_tc_mc_mode;
	पूर्ण

	/* ETS and buffers must be initialized beक्रमe DCB. */
	err = mlxsw_sp_port_dcb_init(mlxsw_sp_port);
	अगर (err) अणु
		dev_err(mlxsw_sp->bus_info->dev, "Port %d: Failed to initialize DCB\n",
			mlxsw_sp_port->local_port);
		जाओ err_port_dcb_init;
	पूर्ण

	err = mlxsw_sp_port_fids_init(mlxsw_sp_port);
	अगर (err) अणु
		dev_err(mlxsw_sp->bus_info->dev, "Port %d: Failed to initialize FIDs\n",
			mlxsw_sp_port->local_port);
		जाओ err_port_fids_init;
	पूर्ण

	err = mlxsw_sp_tc_qdisc_init(mlxsw_sp_port);
	अगर (err) अणु
		dev_err(mlxsw_sp->bus_info->dev, "Port %d: Failed to initialize TC qdiscs\n",
			mlxsw_sp_port->local_port);
		जाओ err_port_qdiscs_init;
	पूर्ण

	err = mlxsw_sp_port_vlan_set(mlxsw_sp_port, 0, VLAN_N_VID - 1, false,
				     false);
	अगर (err) अणु
		dev_err(mlxsw_sp->bus_info->dev, "Port %d: Failed to clear VLAN filter\n",
			mlxsw_sp_port->local_port);
		जाओ err_port_vlan_clear;
	पूर्ण

	err = mlxsw_sp_port_nve_init(mlxsw_sp_port);
	अगर (err) अणु
		dev_err(mlxsw_sp->bus_info->dev, "Port %d: Failed to initialize NVE\n",
			mlxsw_sp_port->local_port);
		जाओ err_port_nve_init;
	पूर्ण

	err = mlxsw_sp_port_pvid_set(mlxsw_sp_port, MLXSW_SP_DEFAULT_VID,
				     ETH_P_8021Q);
	अगर (err) अणु
		dev_err(mlxsw_sp->bus_info->dev, "Port %d: Failed to set PVID\n",
			mlxsw_sp_port->local_port);
		जाओ err_port_pvid_set;
	पूर्ण

	mlxsw_sp_port_vlan = mlxsw_sp_port_vlan_create(mlxsw_sp_port,
						       MLXSW_SP_DEFAULT_VID);
	अगर (IS_ERR(mlxsw_sp_port_vlan)) अणु
		dev_err(mlxsw_sp->bus_info->dev, "Port %d: Failed to create VID 1\n",
			mlxsw_sp_port->local_port);
		err = PTR_ERR(mlxsw_sp_port_vlan);
		जाओ err_port_vlan_create;
	पूर्ण
	mlxsw_sp_port->शेष_vlan = mlxsw_sp_port_vlan;

	/* Set SPVC.et0=true and SPVC.et1=false to make the local port to treat
	 * only packets with 802.1q header as tagged packets.
	 */
	err = mlxsw_sp_port_vlan_classअगरication_set(mlxsw_sp_port, false, true);
	अगर (err) अणु
		dev_err(mlxsw_sp->bus_info->dev, "Port %d: Failed to set default VLAN classification\n",
			local_port);
		जाओ err_port_vlan_classअगरication_set;
	पूर्ण

	INIT_DELAYED_WORK(&mlxsw_sp_port->ptp.shaper_dw,
			  mlxsw_sp->ptp_ops->shaper_work);

	mlxsw_sp->ports[local_port] = mlxsw_sp_port;

	err = mlxsw_sp_port_overheat_init_val_set(mlxsw_sp_port);
	अगर (err) अणु
		dev_err(mlxsw_sp->bus_info->dev, "Port %d: Failed to set overheat initial value\n",
			mlxsw_sp_port->local_port);
		जाओ err_port_overheat_init_val_set;
	पूर्ण

	err = रेजिस्टर_netdev(dev);
	अगर (err) अणु
		dev_err(mlxsw_sp->bus_info->dev, "Port %d: Failed to register netdev\n",
			mlxsw_sp_port->local_port);
		जाओ err_रेजिस्टर_netdev;
	पूर्ण

	mlxsw_core_port_eth_set(mlxsw_sp->core, mlxsw_sp_port->local_port,
				mlxsw_sp_port, dev);
	mlxsw_core_schedule_dw(&mlxsw_sp_port->periodic_hw_stats.update_dw, 0);
	वापस 0;

err_रेजिस्टर_netdev:
err_port_overheat_init_val_set:
	mlxsw_sp_port_vlan_classअगरication_set(mlxsw_sp_port, true, true);
err_port_vlan_classअगरication_set:
	mlxsw_sp->ports[local_port] = शून्य;
	mlxsw_sp_port_vlan_destroy(mlxsw_sp_port_vlan);
err_port_vlan_create:
err_port_pvid_set:
	mlxsw_sp_port_nve_fini(mlxsw_sp_port);
err_port_nve_init:
err_port_vlan_clear:
	mlxsw_sp_tc_qdisc_fini(mlxsw_sp_port);
err_port_qdiscs_init:
	mlxsw_sp_port_fids_fini(mlxsw_sp_port);
err_port_fids_init:
	mlxsw_sp_port_dcb_fini(mlxsw_sp_port);
err_port_dcb_init:
	mlxsw_sp_port_tc_mc_mode_set(mlxsw_sp_port, false);
err_port_tc_mc_mode:
err_port_ets_init:
	mlxsw_sp_port_buffers_fini(mlxsw_sp_port);
err_port_buffers_init:
err_port_admin_status_set:
err_port_mtu_set:
err_port_max_mtu_get:
err_max_speed_get:
err_port_speed_by_width_set:
err_port_प्रणाली_port_mapping_set:
err_dev_addr_init:
	mlxsw_sp_port_swid_set(mlxsw_sp_port, MLXSW_PORT_SWID_DISABLED_PORT);
err_port_swid_set:
	mlxsw_sp_port_module_unmap(mlxsw_sp_port);
err_port_module_map:
	मुक्त_percpu(mlxsw_sp_port->pcpu_stats);
err_alloc_stats:
	मुक्त_netdev(dev);
err_alloc_etherdev:
	mlxsw_core_port_fini(mlxsw_sp->core, local_port);
	वापस err;
पूर्ण

अटल व्योम mlxsw_sp_port_हटाओ(काष्ठा mlxsw_sp *mlxsw_sp, u8 local_port)
अणु
	काष्ठा mlxsw_sp_port *mlxsw_sp_port = mlxsw_sp->ports[local_port];

	cancel_delayed_work_sync(&mlxsw_sp_port->periodic_hw_stats.update_dw);
	cancel_delayed_work_sync(&mlxsw_sp_port->ptp.shaper_dw);
	mlxsw_sp_port_ptp_clear(mlxsw_sp_port);
	mlxsw_core_port_clear(mlxsw_sp->core, local_port, mlxsw_sp);
	unरेजिस्टर_netdev(mlxsw_sp_port->dev); /* This calls nकरो_stop */
	mlxsw_sp_port_vlan_classअगरication_set(mlxsw_sp_port, true, true);
	mlxsw_sp->ports[local_port] = शून्य;
	mlxsw_sp_port_vlan_flush(mlxsw_sp_port, true);
	mlxsw_sp_port_nve_fini(mlxsw_sp_port);
	mlxsw_sp_tc_qdisc_fini(mlxsw_sp_port);
	mlxsw_sp_port_fids_fini(mlxsw_sp_port);
	mlxsw_sp_port_dcb_fini(mlxsw_sp_port);
	mlxsw_sp_port_tc_mc_mode_set(mlxsw_sp_port, false);
	mlxsw_sp_port_buffers_fini(mlxsw_sp_port);
	mlxsw_sp_port_swid_set(mlxsw_sp_port, MLXSW_PORT_SWID_DISABLED_PORT);
	mlxsw_sp_port_module_unmap(mlxsw_sp_port);
	मुक्त_percpu(mlxsw_sp_port->pcpu_stats);
	WARN_ON_ONCE(!list_empty(&mlxsw_sp_port->vlans_list));
	मुक्त_netdev(mlxsw_sp_port->dev);
	mlxsw_core_port_fini(mlxsw_sp->core, local_port);
पूर्ण

अटल पूर्णांक mlxsw_sp_cpu_port_create(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	काष्ठा mlxsw_sp_port *mlxsw_sp_port;
	पूर्णांक err;

	mlxsw_sp_port = kzalloc(माप(*mlxsw_sp_port), GFP_KERNEL);
	अगर (!mlxsw_sp_port)
		वापस -ENOMEM;

	mlxsw_sp_port->mlxsw_sp = mlxsw_sp;
	mlxsw_sp_port->local_port = MLXSW_PORT_CPU_PORT;

	err = mlxsw_core_cpu_port_init(mlxsw_sp->core,
				       mlxsw_sp_port,
				       mlxsw_sp->base_mac,
				       माप(mlxsw_sp->base_mac));
	अगर (err) अणु
		dev_err(mlxsw_sp->bus_info->dev, "Failed to initialize core CPU port\n");
		जाओ err_core_cpu_port_init;
	पूर्ण

	mlxsw_sp->ports[MLXSW_PORT_CPU_PORT] = mlxsw_sp_port;
	वापस 0;

err_core_cpu_port_init:
	kमुक्त(mlxsw_sp_port);
	वापस err;
पूर्ण

अटल व्योम mlxsw_sp_cpu_port_हटाओ(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	काष्ठा mlxsw_sp_port *mlxsw_sp_port =
				mlxsw_sp->ports[MLXSW_PORT_CPU_PORT];

	mlxsw_core_cpu_port_fini(mlxsw_sp->core);
	mlxsw_sp->ports[MLXSW_PORT_CPU_PORT] = शून्य;
	kमुक्त(mlxsw_sp_port);
पूर्ण

अटल bool mlxsw_sp_port_created(काष्ठा mlxsw_sp *mlxsw_sp, u8 local_port)
अणु
	वापस mlxsw_sp->ports[local_port] != शून्य;
पूर्ण

अटल व्योम mlxsw_sp_ports_हटाओ(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	पूर्णांक i;

	क्रम (i = 1; i < mlxsw_core_max_ports(mlxsw_sp->core); i++)
		अगर (mlxsw_sp_port_created(mlxsw_sp, i))
			mlxsw_sp_port_हटाओ(mlxsw_sp, i);
	mlxsw_sp_cpu_port_हटाओ(mlxsw_sp);
	kमुक्त(mlxsw_sp->ports);
	mlxsw_sp->ports = शून्य;
पूर्ण

अटल पूर्णांक mlxsw_sp_ports_create(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	अचिन्हित पूर्णांक max_ports = mlxsw_core_max_ports(mlxsw_sp->core);
	काष्ठा mlxsw_sp_port_mapping *port_mapping;
	माप_प्रकार alloc_size;
	पूर्णांक i;
	पूर्णांक err;

	alloc_size = माप(काष्ठा mlxsw_sp_port *) * max_ports;
	mlxsw_sp->ports = kzalloc(alloc_size, GFP_KERNEL);
	अगर (!mlxsw_sp->ports)
		वापस -ENOMEM;

	err = mlxsw_sp_cpu_port_create(mlxsw_sp);
	अगर (err)
		जाओ err_cpu_port_create;

	क्रम (i = 1; i < max_ports; i++) अणु
		port_mapping = mlxsw_sp->port_mapping[i];
		अगर (!port_mapping)
			जारी;
		err = mlxsw_sp_port_create(mlxsw_sp, i, 0, port_mapping);
		अगर (err)
			जाओ err_port_create;
	पूर्ण
	वापस 0;

err_port_create:
	क्रम (i--; i >= 1; i--)
		अगर (mlxsw_sp_port_created(mlxsw_sp, i))
			mlxsw_sp_port_हटाओ(mlxsw_sp, i);
	mlxsw_sp_cpu_port_हटाओ(mlxsw_sp);
err_cpu_port_create:
	kमुक्त(mlxsw_sp->ports);
	mlxsw_sp->ports = शून्य;
	वापस err;
पूर्ण

अटल पूर्णांक mlxsw_sp_port_module_info_init(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	अचिन्हित पूर्णांक max_ports = mlxsw_core_max_ports(mlxsw_sp->core);
	काष्ठा mlxsw_sp_port_mapping port_mapping;
	पूर्णांक i;
	पूर्णांक err;

	mlxsw_sp->port_mapping = kसुस्मृति(max_ports,
					 माप(काष्ठा mlxsw_sp_port_mapping *),
					 GFP_KERNEL);
	अगर (!mlxsw_sp->port_mapping)
		वापस -ENOMEM;

	क्रम (i = 1; i < max_ports; i++) अणु
		अगर (mlxsw_core_port_is_xm(mlxsw_sp->core, i))
			जारी;

		err = mlxsw_sp_port_module_info_get(mlxsw_sp, i, &port_mapping);
		अगर (err)
			जाओ err_port_module_info_get;
		अगर (!port_mapping.width)
			जारी;

		mlxsw_sp->port_mapping[i] = kmemdup(&port_mapping,
						    माप(port_mapping),
						    GFP_KERNEL);
		अगर (!mlxsw_sp->port_mapping[i]) अणु
			err = -ENOMEM;
			जाओ err_port_module_info_dup;
		पूर्ण
	पूर्ण
	वापस 0;

err_port_module_info_get:
err_port_module_info_dup:
	क्रम (i--; i >= 1; i--)
		kमुक्त(mlxsw_sp->port_mapping[i]);
	kमुक्त(mlxsw_sp->port_mapping);
	वापस err;
पूर्ण

अटल व्योम mlxsw_sp_port_module_info_fini(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	पूर्णांक i;

	क्रम (i = 1; i < mlxsw_core_max_ports(mlxsw_sp->core); i++)
		kमुक्त(mlxsw_sp->port_mapping[i]);
	kमुक्त(mlxsw_sp->port_mapping);
पूर्ण

अटल u8 mlxsw_sp_cluster_base_port_get(u8 local_port, अचिन्हित पूर्णांक max_width)
अणु
	u8 offset = (local_port - 1) % max_width;

	वापस local_port - offset;
पूर्ण

अटल पूर्णांक
mlxsw_sp_port_split_create(काष्ठा mlxsw_sp *mlxsw_sp, u8 base_port,
			   काष्ठा mlxsw_sp_port_mapping *port_mapping,
			   अचिन्हित पूर्णांक count, u8 offset)
अणु
	काष्ठा mlxsw_sp_port_mapping split_port_mapping;
	पूर्णांक err, i;

	split_port_mapping = *port_mapping;
	split_port_mapping.width /= count;
	क्रम (i = 0; i < count; i++) अणु
		err = mlxsw_sp_port_create(mlxsw_sp, base_port + i * offset,
					   base_port, &split_port_mapping);
		अगर (err)
			जाओ err_port_create;
		split_port_mapping.lane += split_port_mapping.width;
	पूर्ण

	वापस 0;

err_port_create:
	क्रम (i--; i >= 0; i--)
		अगर (mlxsw_sp_port_created(mlxsw_sp, base_port + i * offset))
			mlxsw_sp_port_हटाओ(mlxsw_sp, base_port + i * offset);
	वापस err;
पूर्ण

अटल व्योम mlxsw_sp_port_unsplit_create(काष्ठा mlxsw_sp *mlxsw_sp,
					 u8 base_port,
					 अचिन्हित पूर्णांक count, u8 offset)
अणु
	काष्ठा mlxsw_sp_port_mapping *port_mapping;
	पूर्णांक i;

	/* Go over original unsplit ports in the gap and recreate them. */
	क्रम (i = 0; i < count * offset; i++) अणु
		port_mapping = mlxsw_sp->port_mapping[base_port + i];
		अगर (!port_mapping)
			जारी;
		mlxsw_sp_port_create(mlxsw_sp, base_port + i, 0, port_mapping);
	पूर्ण
पूर्ण

अटल पूर्णांक mlxsw_sp_local_ports_offset(काष्ठा mlxsw_core *mlxsw_core,
				       अचिन्हित पूर्णांक count,
				       अचिन्हित पूर्णांक max_width)
अणु
	क्रमागत mlxsw_res_id local_ports_in_x_res_id;
	पूर्णांक split_width = max_width / count;

	अगर (split_width == 1)
		local_ports_in_x_res_id = MLXSW_RES_ID_LOCAL_PORTS_IN_1X;
	अन्यथा अगर (split_width == 2)
		local_ports_in_x_res_id = MLXSW_RES_ID_LOCAL_PORTS_IN_2X;
	अन्यथा अगर (split_width == 4)
		local_ports_in_x_res_id = MLXSW_RES_ID_LOCAL_PORTS_IN_4X;
	अन्यथा
		वापस -EINVAL;

	अगर (!mlxsw_core_res_valid(mlxsw_core, local_ports_in_x_res_id))
		वापस -EINVAL;
	वापस mlxsw_core_res_get(mlxsw_core, local_ports_in_x_res_id);
पूर्ण

अटल काष्ठा mlxsw_sp_port *
mlxsw_sp_port_get_by_local_port(काष्ठा mlxsw_sp *mlxsw_sp, u8 local_port)
अणु
	अगर (mlxsw_sp->ports && mlxsw_sp->ports[local_port])
		वापस mlxsw_sp->ports[local_port];
	वापस शून्य;
पूर्ण

अटल पूर्णांक mlxsw_sp_port_split(काष्ठा mlxsw_core *mlxsw_core, u8 local_port,
			       अचिन्हित पूर्णांक count,
			       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_core_driver_priv(mlxsw_core);
	काष्ठा mlxsw_sp_port_mapping port_mapping;
	काष्ठा mlxsw_sp_port *mlxsw_sp_port;
	पूर्णांक max_width;
	u8 base_port;
	पूर्णांक offset;
	पूर्णांक i;
	पूर्णांक err;

	mlxsw_sp_port = mlxsw_sp_port_get_by_local_port(mlxsw_sp, local_port);
	अगर (!mlxsw_sp_port) अणु
		dev_err(mlxsw_sp->bus_info->dev, "Port number \"%d\" does not exist\n",
			local_port);
		NL_SET_ERR_MSG_MOD(extack, "Port number does not exist");
		वापस -EINVAL;
	पूर्ण

	max_width = mlxsw_core_module_max_width(mlxsw_core,
						mlxsw_sp_port->mapping.module);
	अगर (max_width < 0) अणु
		netdev_err(mlxsw_sp_port->dev, "Cannot get max width of port module\n");
		NL_SET_ERR_MSG_MOD(extack, "Cannot get max width of port module");
		वापस max_width;
	पूर्ण

	/* Split port with non-max cannot be split. */
	अगर (mlxsw_sp_port->mapping.width != max_width) अणु
		netdev_err(mlxsw_sp_port->dev, "Port cannot be split\n");
		NL_SET_ERR_MSG_MOD(extack, "Port cannot be split");
		वापस -EINVAL;
	पूर्ण

	offset = mlxsw_sp_local_ports_offset(mlxsw_core, count, max_width);
	अगर (offset < 0) अणु
		netdev_err(mlxsw_sp_port->dev, "Cannot obtain local port offset\n");
		NL_SET_ERR_MSG_MOD(extack, "Cannot obtain local port offset");
		वापस -EINVAL;
	पूर्ण

	/* Only in हाल max split is being करोne, the local port and
	 * base port may dअगरfer.
	 */
	base_port = count == max_width ?
		    mlxsw_sp_cluster_base_port_get(local_port, max_width) :
		    local_port;

	क्रम (i = 0; i < count * offset; i++) अणु
		/* Expect base port to exist and also the one in the middle in
		 * हाल of maximal split count.
		 */
		अगर (i == 0 || (count == max_width && i == count / 2))
			जारी;

		अगर (mlxsw_sp_port_created(mlxsw_sp, base_port + i)) अणु
			netdev_err(mlxsw_sp_port->dev, "Invalid split configuration\n");
			NL_SET_ERR_MSG_MOD(extack, "Invalid split configuration");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	port_mapping = mlxsw_sp_port->mapping;

	क्रम (i = 0; i < count; i++)
		अगर (mlxsw_sp_port_created(mlxsw_sp, base_port + i * offset))
			mlxsw_sp_port_हटाओ(mlxsw_sp, base_port + i * offset);

	err = mlxsw_sp_port_split_create(mlxsw_sp, base_port, &port_mapping,
					 count, offset);
	अगर (err) अणु
		dev_err(mlxsw_sp->bus_info->dev, "Failed to create split ports\n");
		जाओ err_port_split_create;
	पूर्ण

	वापस 0;

err_port_split_create:
	mlxsw_sp_port_unsplit_create(mlxsw_sp, base_port, count, offset);
	वापस err;
पूर्ण

अटल पूर्णांक mlxsw_sp_port_unsplit(काष्ठा mlxsw_core *mlxsw_core, u8 local_port,
				 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_core_driver_priv(mlxsw_core);
	काष्ठा mlxsw_sp_port *mlxsw_sp_port;
	अचिन्हित पूर्णांक count;
	पूर्णांक max_width;
	u8 base_port;
	पूर्णांक offset;
	पूर्णांक i;

	mlxsw_sp_port = mlxsw_sp_port_get_by_local_port(mlxsw_sp, local_port);
	अगर (!mlxsw_sp_port) अणु
		dev_err(mlxsw_sp->bus_info->dev, "Port number \"%d\" does not exist\n",
			local_port);
		NL_SET_ERR_MSG_MOD(extack, "Port number does not exist");
		वापस -EINVAL;
	पूर्ण

	अगर (!mlxsw_sp_port->split) अणु
		netdev_err(mlxsw_sp_port->dev, "Port was not split\n");
		NL_SET_ERR_MSG_MOD(extack, "Port was not split");
		वापस -EINVAL;
	पूर्ण

	max_width = mlxsw_core_module_max_width(mlxsw_core,
						mlxsw_sp_port->mapping.module);
	अगर (max_width < 0) अणु
		netdev_err(mlxsw_sp_port->dev, "Cannot get max width of port module\n");
		NL_SET_ERR_MSG_MOD(extack, "Cannot get max width of port module");
		वापस max_width;
	पूर्ण

	count = max_width / mlxsw_sp_port->mapping.width;

	offset = mlxsw_sp_local_ports_offset(mlxsw_core, count, max_width);
	अगर (WARN_ON(offset < 0)) अणु
		netdev_err(mlxsw_sp_port->dev, "Cannot obtain local port offset\n");
		NL_SET_ERR_MSG_MOD(extack, "Cannot obtain local port offset");
		वापस -EINVAL;
	पूर्ण

	base_port = mlxsw_sp_port->split_base_local_port;

	क्रम (i = 0; i < count; i++)
		अगर (mlxsw_sp_port_created(mlxsw_sp, base_port + i * offset))
			mlxsw_sp_port_हटाओ(mlxsw_sp, base_port + i * offset);

	mlxsw_sp_port_unsplit_create(mlxsw_sp, base_port, count, offset);

	वापस 0;
पूर्ण

अटल व्योम
mlxsw_sp_port_करोwn_wipe_counters(काष्ठा mlxsw_sp_port *mlxsw_sp_port)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < TC_MAX_QUEUE; i++)
		mlxsw_sp_port->periodic_hw_stats.xstats.backlog[i] = 0;
पूर्ण

अटल व्योम mlxsw_sp_pude_event_func(स्थिर काष्ठा mlxsw_reg_info *reg,
				     अक्षर *pude_pl, व्योम *priv)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = priv;
	काष्ठा mlxsw_sp_port *mlxsw_sp_port;
	क्रमागत mlxsw_reg_pude_oper_status status;
	u8 local_port;

	local_port = mlxsw_reg_pude_local_port_get(pude_pl);
	mlxsw_sp_port = mlxsw_sp->ports[local_port];
	अगर (!mlxsw_sp_port)
		वापस;

	status = mlxsw_reg_pude_oper_status_get(pude_pl);
	अगर (status == MLXSW_PORT_OPER_STATUS_UP) अणु
		netdev_info(mlxsw_sp_port->dev, "link up\n");
		netअगर_carrier_on(mlxsw_sp_port->dev);
		mlxsw_core_schedule_dw(&mlxsw_sp_port->ptp.shaper_dw, 0);
	पूर्ण अन्यथा अणु
		netdev_info(mlxsw_sp_port->dev, "link down\n");
		netअगर_carrier_off(mlxsw_sp_port->dev);
		mlxsw_sp_port_करोwn_wipe_counters(mlxsw_sp_port);
	पूर्ण
पूर्ण

अटल व्योम mlxsw_sp1_ptp_fअगरo_event_func(काष्ठा mlxsw_sp *mlxsw_sp,
					  अक्षर *mtpptr_pl, bool ingress)
अणु
	u8 local_port;
	u8 num_rec;
	पूर्णांक i;

	local_port = mlxsw_reg_mtpptr_local_port_get(mtpptr_pl);
	num_rec = mlxsw_reg_mtpptr_num_rec_get(mtpptr_pl);
	क्रम (i = 0; i < num_rec; i++) अणु
		u8 करोमुख्य_number;
		u8 message_type;
		u16 sequence_id;
		u64 बारtamp;

		mlxsw_reg_mtpptr_unpack(mtpptr_pl, i, &message_type,
					&करोमुख्य_number, &sequence_id,
					&बारtamp);
		mlxsw_sp1_ptp_got_बारtamp(mlxsw_sp, ingress, local_port,
					    message_type, करोमुख्य_number,
					    sequence_id, बारtamp);
	पूर्ण
पूर्ण

अटल व्योम mlxsw_sp1_ptp_ing_fअगरo_event_func(स्थिर काष्ठा mlxsw_reg_info *reg,
					      अक्षर *mtpptr_pl, व्योम *priv)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = priv;

	mlxsw_sp1_ptp_fअगरo_event_func(mlxsw_sp, mtpptr_pl, true);
पूर्ण

अटल व्योम mlxsw_sp1_ptp_egr_fअगरo_event_func(स्थिर काष्ठा mlxsw_reg_info *reg,
					      अक्षर *mtpptr_pl, व्योम *priv)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = priv;

	mlxsw_sp1_ptp_fअगरo_event_func(mlxsw_sp, mtpptr_pl, false);
पूर्ण

व्योम mlxsw_sp_rx_listener_no_mark_func(काष्ठा sk_buff *skb,
				       u8 local_port, व्योम *priv)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = priv;
	काष्ठा mlxsw_sp_port *mlxsw_sp_port = mlxsw_sp->ports[local_port];
	काष्ठा mlxsw_sp_port_pcpu_stats *pcpu_stats;

	अगर (unlikely(!mlxsw_sp_port)) अणु
		dev_warn_ratelimited(mlxsw_sp->bus_info->dev, "Port %d: skb received for non-existent port\n",
				     local_port);
		वापस;
	पूर्ण

	skb->dev = mlxsw_sp_port->dev;

	pcpu_stats = this_cpu_ptr(mlxsw_sp_port->pcpu_stats);
	u64_stats_update_begin(&pcpu_stats->syncp);
	pcpu_stats->rx_packets++;
	pcpu_stats->rx_bytes += skb->len;
	u64_stats_update_end(&pcpu_stats->syncp);

	skb->protocol = eth_type_trans(skb, skb->dev);
	netअगर_receive_skb(skb);
पूर्ण

अटल व्योम mlxsw_sp_rx_listener_mark_func(काष्ठा sk_buff *skb, u8 local_port,
					   व्योम *priv)
अणु
	skb->offload_fwd_mark = 1;
	वापस mlxsw_sp_rx_listener_no_mark_func(skb, local_port, priv);
पूर्ण

अटल व्योम mlxsw_sp_rx_listener_l3_mark_func(काष्ठा sk_buff *skb,
					      u8 local_port, व्योम *priv)
अणु
	skb->offload_l3_fwd_mark = 1;
	skb->offload_fwd_mark = 1;
	वापस mlxsw_sp_rx_listener_no_mark_func(skb, local_port, priv);
पूर्ण

व्योम mlxsw_sp_ptp_receive(काष्ठा mlxsw_sp *mlxsw_sp, काष्ठा sk_buff *skb,
			  u8 local_port)
अणु
	mlxsw_sp->ptp_ops->receive(mlxsw_sp, skb, local_port);
पूर्ण

#घोषणा MLXSW_SP_RXL_NO_MARK(_trap_id, _action, _trap_group, _is_ctrl)	\
	MLXSW_RXL(mlxsw_sp_rx_listener_no_mark_func, _trap_id, _action,	\
		  _is_ctrl, SP_##_trap_group, DISCARD)

#घोषणा MLXSW_SP_RXL_MARK(_trap_id, _action, _trap_group, _is_ctrl)	\
	MLXSW_RXL(mlxsw_sp_rx_listener_mark_func, _trap_id, _action,	\
		_is_ctrl, SP_##_trap_group, DISCARD)

#घोषणा MLXSW_SP_RXL_L3_MARK(_trap_id, _action, _trap_group, _is_ctrl)	\
	MLXSW_RXL(mlxsw_sp_rx_listener_l3_mark_func, _trap_id, _action,	\
		_is_ctrl, SP_##_trap_group, DISCARD)

#घोषणा MLXSW_SP_EVENTL(_func, _trap_id)		\
	MLXSW_EVENTL(_func, _trap_id, SP_EVENT)

अटल स्थिर काष्ठा mlxsw_listener mlxsw_sp_listener[] = अणु
	/* Events */
	MLXSW_SP_EVENTL(mlxsw_sp_pude_event_func, PUDE),
	/* L2 traps */
	MLXSW_SP_RXL_NO_MARK(FID_MISS, TRAP_TO_CPU, FID_MISS, false),
	/* L3 traps */
	MLXSW_SP_RXL_MARK(IPV6_UNSPECIFIED_ADDRESS, TRAP_TO_CPU, ROUTER_EXP,
			  false),
	MLXSW_SP_RXL_MARK(IPV6_LINK_LOCAL_SRC, TRAP_TO_CPU, ROUTER_EXP, false),
	MLXSW_SP_RXL_MARK(IPV6_MC_LINK_LOCAL_DEST, TRAP_TO_CPU, ROUTER_EXP,
			  false),
	MLXSW_SP_RXL_NO_MARK(DISCARD_ING_ROUTER_SIP_CLASS_E, FORWARD,
			     ROUTER_EXP, false),
	MLXSW_SP_RXL_NO_MARK(DISCARD_ING_ROUTER_MC_DMAC, FORWARD,
			     ROUTER_EXP, false),
	MLXSW_SP_RXL_NO_MARK(DISCARD_ING_ROUTER_SIP_DIP, FORWARD,
			     ROUTER_EXP, false),
	MLXSW_SP_RXL_NO_MARK(DISCARD_ING_ROUTER_DIP_LINK_LOCAL, FORWARD,
			     ROUTER_EXP, false),
	/* Multicast Router Traps */
	MLXSW_SP_RXL_MARK(ACL1, TRAP_TO_CPU, MULTICAST, false),
	MLXSW_SP_RXL_L3_MARK(ACL2, TRAP_TO_CPU, MULTICAST, false),
	/* NVE traps */
	MLXSW_SP_RXL_MARK(NVE_ENCAP_ARP, TRAP_TO_CPU, NEIGH_DISCOVERY, false),
पूर्ण;

अटल स्थिर काष्ठा mlxsw_listener mlxsw_sp1_listener[] = अणु
	/* Events */
	MLXSW_EVENTL(mlxsw_sp1_ptp_egr_fअगरo_event_func, PTP_EGR_FIFO, SP_PTP0),
	MLXSW_EVENTL(mlxsw_sp1_ptp_ing_fअगरo_event_func, PTP_ING_FIFO, SP_PTP0),
पूर्ण;

अटल पूर्णांक mlxsw_sp_cpu_policers_set(काष्ठा mlxsw_core *mlxsw_core)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_core_driver_priv(mlxsw_core);
	अक्षर qpcr_pl[MLXSW_REG_QPCR_LEN];
	क्रमागत mlxsw_reg_qpcr_ir_units ir_units;
	पूर्णांक max_cpu_policers;
	bool is_bytes;
	u8 burst_size;
	u32 rate;
	पूर्णांक i, err;

	अगर (!MLXSW_CORE_RES_VALID(mlxsw_core, MAX_CPU_POLICERS))
		वापस -EIO;

	max_cpu_policers = MLXSW_CORE_RES_GET(mlxsw_core, MAX_CPU_POLICERS);

	ir_units = MLXSW_REG_QPCR_IR_UNITS_M;
	क्रम (i = 0; i < max_cpu_policers; i++) अणु
		is_bytes = false;
		चयन (i) अणु
		हाल MLXSW_REG_HTGT_TRAP_GROUP_SP_ROUTER_EXP:
		हाल MLXSW_REG_HTGT_TRAP_GROUP_SP_MULTICAST:
		हाल MLXSW_REG_HTGT_TRAP_GROUP_SP_FID_MISS:
			rate = 1024;
			burst_size = 7;
			अवरोध;
		शेष:
			जारी;
		पूर्ण

		__set_bit(i, mlxsw_sp->trap->policers_usage);
		mlxsw_reg_qpcr_pack(qpcr_pl, i, ir_units, is_bytes, rate,
				    burst_size);
		err = mlxsw_reg_ग_लिखो(mlxsw_core, MLXSW_REG(qpcr), qpcr_pl);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_sp_trap_groups_set(काष्ठा mlxsw_core *mlxsw_core)
अणु
	अक्षर htgt_pl[MLXSW_REG_HTGT_LEN];
	क्रमागत mlxsw_reg_htgt_trap_group i;
	पूर्णांक max_cpu_policers;
	पूर्णांक max_trap_groups;
	u8 priority, tc;
	u16 policer_id;
	पूर्णांक err;

	अगर (!MLXSW_CORE_RES_VALID(mlxsw_core, MAX_TRAP_GROUPS))
		वापस -EIO;

	max_trap_groups = MLXSW_CORE_RES_GET(mlxsw_core, MAX_TRAP_GROUPS);
	max_cpu_policers = MLXSW_CORE_RES_GET(mlxsw_core, MAX_CPU_POLICERS);

	क्रम (i = 0; i < max_trap_groups; i++) अणु
		policer_id = i;
		चयन (i) अणु
		हाल MLXSW_REG_HTGT_TRAP_GROUP_SP_ROUTER_EXP:
		हाल MLXSW_REG_HTGT_TRAP_GROUP_SP_MULTICAST:
		हाल MLXSW_REG_HTGT_TRAP_GROUP_SP_FID_MISS:
			priority = 1;
			tc = 1;
			अवरोध;
		हाल MLXSW_REG_HTGT_TRAP_GROUP_SP_EVENT:
			priority = MLXSW_REG_HTGT_DEFAULT_PRIORITY;
			tc = MLXSW_REG_HTGT_DEFAULT_TC;
			policer_id = MLXSW_REG_HTGT_INVALID_POLICER;
			अवरोध;
		शेष:
			जारी;
		पूर्ण

		अगर (max_cpu_policers <= policer_id &&
		    policer_id != MLXSW_REG_HTGT_INVALID_POLICER)
			वापस -EIO;

		mlxsw_reg_htgt_pack(htgt_pl, i, policer_id, priority, tc);
		err = mlxsw_reg_ग_लिखो(mlxsw_core, MLXSW_REG(htgt), htgt_pl);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_sp_traps_रेजिस्टर(काष्ठा mlxsw_sp *mlxsw_sp,
				   स्थिर काष्ठा mlxsw_listener listeners[],
				   माप_प्रकार listeners_count)
अणु
	पूर्णांक i;
	पूर्णांक err;

	क्रम (i = 0; i < listeners_count; i++) अणु
		err = mlxsw_core_trap_रेजिस्टर(mlxsw_sp->core,
					       &listeners[i],
					       mlxsw_sp);
		अगर (err)
			जाओ err_listener_रेजिस्टर;

	पूर्ण
	वापस 0;

err_listener_रेजिस्टर:
	क्रम (i--; i >= 0; i--) अणु
		mlxsw_core_trap_unरेजिस्टर(mlxsw_sp->core,
					   &listeners[i],
					   mlxsw_sp);
	पूर्ण
	वापस err;
पूर्ण

अटल व्योम mlxsw_sp_traps_unरेजिस्टर(काष्ठा mlxsw_sp *mlxsw_sp,
				      स्थिर काष्ठा mlxsw_listener listeners[],
				      माप_प्रकार listeners_count)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < listeners_count; i++) अणु
		mlxsw_core_trap_unरेजिस्टर(mlxsw_sp->core,
					   &listeners[i],
					   mlxsw_sp);
	पूर्ण
पूर्ण

अटल पूर्णांक mlxsw_sp_traps_init(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	काष्ठा mlxsw_sp_trap *trap;
	u64 max_policers;
	पूर्णांक err;

	अगर (!MLXSW_CORE_RES_VALID(mlxsw_sp->core, MAX_CPU_POLICERS))
		वापस -EIO;
	max_policers = MLXSW_CORE_RES_GET(mlxsw_sp->core, MAX_CPU_POLICERS);
	trap = kzalloc(काष्ठा_size(trap, policers_usage,
				   BITS_TO_LONGS(max_policers)), GFP_KERNEL);
	अगर (!trap)
		वापस -ENOMEM;
	trap->max_policers = max_policers;
	mlxsw_sp->trap = trap;

	err = mlxsw_sp_cpu_policers_set(mlxsw_sp->core);
	अगर (err)
		जाओ err_cpu_policers_set;

	err = mlxsw_sp_trap_groups_set(mlxsw_sp->core);
	अगर (err)
		जाओ err_trap_groups_set;

	err = mlxsw_sp_traps_रेजिस्टर(mlxsw_sp, mlxsw_sp_listener,
				      ARRAY_SIZE(mlxsw_sp_listener));
	अगर (err)
		जाओ err_traps_रेजिस्टर;

	err = mlxsw_sp_traps_रेजिस्टर(mlxsw_sp, mlxsw_sp->listeners,
				      mlxsw_sp->listeners_count);
	अगर (err)
		जाओ err_extra_traps_init;

	वापस 0;

err_extra_traps_init:
	mlxsw_sp_traps_unरेजिस्टर(mlxsw_sp, mlxsw_sp_listener,
				  ARRAY_SIZE(mlxsw_sp_listener));
err_traps_रेजिस्टर:
err_trap_groups_set:
err_cpu_policers_set:
	kमुक्त(trap);
	वापस err;
पूर्ण

अटल व्योम mlxsw_sp_traps_fini(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	mlxsw_sp_traps_unरेजिस्टर(mlxsw_sp, mlxsw_sp->listeners,
				  mlxsw_sp->listeners_count);
	mlxsw_sp_traps_unरेजिस्टर(mlxsw_sp, mlxsw_sp_listener,
				  ARRAY_SIZE(mlxsw_sp_listener));
	kमुक्त(mlxsw_sp->trap);
पूर्ण

#घोषणा MLXSW_SP_LAG_SEED_INIT 0xcafecafe

अटल पूर्णांक mlxsw_sp_lag_init(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	अक्षर slcr_pl[MLXSW_REG_SLCR_LEN];
	u32 seed;
	पूर्णांक err;

	seed = jhash(mlxsw_sp->base_mac, माप(mlxsw_sp->base_mac),
		     MLXSW_SP_LAG_SEED_INIT);
	mlxsw_reg_slcr_pack(slcr_pl, MLXSW_REG_SLCR_LAG_HASH_SMAC |
				     MLXSW_REG_SLCR_LAG_HASH_DMAC |
				     MLXSW_REG_SLCR_LAG_HASH_ETHERTYPE |
				     MLXSW_REG_SLCR_LAG_HASH_VLANID |
				     MLXSW_REG_SLCR_LAG_HASH_SIP |
				     MLXSW_REG_SLCR_LAG_HASH_DIP |
				     MLXSW_REG_SLCR_LAG_HASH_SPORT |
				     MLXSW_REG_SLCR_LAG_HASH_DPORT |
				     MLXSW_REG_SLCR_LAG_HASH_IPPROTO, seed);
	err = mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(slcr), slcr_pl);
	अगर (err)
		वापस err;

	अगर (!MLXSW_CORE_RES_VALID(mlxsw_sp->core, MAX_LAG) ||
	    !MLXSW_CORE_RES_VALID(mlxsw_sp->core, MAX_LAG_MEMBERS))
		वापस -EIO;

	mlxsw_sp->lags = kसुस्मृति(MLXSW_CORE_RES_GET(mlxsw_sp->core, MAX_LAG),
				 माप(काष्ठा mlxsw_sp_upper),
				 GFP_KERNEL);
	अगर (!mlxsw_sp->lags)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल व्योम mlxsw_sp_lag_fini(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	kमुक्त(mlxsw_sp->lags);
पूर्ण

अटल पूर्णांक mlxsw_sp_basic_trap_groups_set(काष्ठा mlxsw_core *mlxsw_core)
अणु
	अक्षर htgt_pl[MLXSW_REG_HTGT_LEN];
	पूर्णांक err;

	mlxsw_reg_htgt_pack(htgt_pl, MLXSW_REG_HTGT_TRAP_GROUP_EMAD,
			    MLXSW_REG_HTGT_INVALID_POLICER,
			    MLXSW_REG_HTGT_DEFAULT_PRIORITY,
			    MLXSW_REG_HTGT_DEFAULT_TC);
	err =  mlxsw_reg_ग_लिखो(mlxsw_core, MLXSW_REG(htgt), htgt_pl);
	अगर (err)
		वापस err;

	mlxsw_reg_htgt_pack(htgt_pl, MLXSW_REG_HTGT_TRAP_GROUP_MFDE,
			    MLXSW_REG_HTGT_INVALID_POLICER,
			    MLXSW_REG_HTGT_DEFAULT_PRIORITY,
			    MLXSW_REG_HTGT_DEFAULT_TC);
	err = mlxsw_reg_ग_लिखो(mlxsw_core, MLXSW_REG(htgt), htgt_pl);
	अगर (err)
		वापस err;

	mlxsw_reg_htgt_pack(htgt_pl, MLXSW_REG_HTGT_TRAP_GROUP_MTWE,
			    MLXSW_REG_HTGT_INVALID_POLICER,
			    MLXSW_REG_HTGT_DEFAULT_PRIORITY,
			    MLXSW_REG_HTGT_DEFAULT_TC);
	err = mlxsw_reg_ग_लिखो(mlxsw_core, MLXSW_REG(htgt), htgt_pl);
	अगर (err)
		वापस err;

	mlxsw_reg_htgt_pack(htgt_pl, MLXSW_REG_HTGT_TRAP_GROUP_PMPE,
			    MLXSW_REG_HTGT_INVALID_POLICER,
			    MLXSW_REG_HTGT_DEFAULT_PRIORITY,
			    MLXSW_REG_HTGT_DEFAULT_TC);
	वापस mlxsw_reg_ग_लिखो(mlxsw_core, MLXSW_REG(htgt), htgt_pl);
पूर्ण

अटल स्थिर काष्ठा mlxsw_sp_ptp_ops mlxsw_sp1_ptp_ops = अणु
	.घड़ी_init	= mlxsw_sp1_ptp_घड़ी_init,
	.घड़ी_fini	= mlxsw_sp1_ptp_घड़ी_fini,
	.init		= mlxsw_sp1_ptp_init,
	.fini		= mlxsw_sp1_ptp_fini,
	.receive	= mlxsw_sp1_ptp_receive,
	.transmitted	= mlxsw_sp1_ptp_transmitted,
	.hwtstamp_get	= mlxsw_sp1_ptp_hwtstamp_get,
	.hwtstamp_set	= mlxsw_sp1_ptp_hwtstamp_set,
	.shaper_work	= mlxsw_sp1_ptp_shaper_work,
	.get_ts_info	= mlxsw_sp1_ptp_get_ts_info,
	.get_stats_count = mlxsw_sp1_get_stats_count,
	.get_stats_strings = mlxsw_sp1_get_stats_strings,
	.get_stats	= mlxsw_sp1_get_stats,
पूर्ण;

अटल स्थिर काष्ठा mlxsw_sp_ptp_ops mlxsw_sp2_ptp_ops = अणु
	.घड़ी_init	= mlxsw_sp2_ptp_घड़ी_init,
	.घड़ी_fini	= mlxsw_sp2_ptp_घड़ी_fini,
	.init		= mlxsw_sp2_ptp_init,
	.fini		= mlxsw_sp2_ptp_fini,
	.receive	= mlxsw_sp2_ptp_receive,
	.transmitted	= mlxsw_sp2_ptp_transmitted,
	.hwtstamp_get	= mlxsw_sp2_ptp_hwtstamp_get,
	.hwtstamp_set	= mlxsw_sp2_ptp_hwtstamp_set,
	.shaper_work	= mlxsw_sp2_ptp_shaper_work,
	.get_ts_info	= mlxsw_sp2_ptp_get_ts_info,
	.get_stats_count = mlxsw_sp2_get_stats_count,
	.get_stats_strings = mlxsw_sp2_get_stats_strings,
	.get_stats	= mlxsw_sp2_get_stats,
पूर्ण;

काष्ठा mlxsw_sp_sample_trigger_node अणु
	काष्ठा mlxsw_sp_sample_trigger trigger;
	काष्ठा mlxsw_sp_sample_params params;
	काष्ठा rhash_head ht_node;
	काष्ठा rcu_head rcu;
	refcount_t refcount;
पूर्ण;

अटल स्थिर काष्ठा rhashtable_params mlxsw_sp_sample_trigger_ht_params = अणु
	.key_offset = दुरत्व(काष्ठा mlxsw_sp_sample_trigger_node, trigger),
	.head_offset = दुरत्व(काष्ठा mlxsw_sp_sample_trigger_node, ht_node),
	.key_len = माप(काष्ठा mlxsw_sp_sample_trigger),
	.स्वतःmatic_shrinking = true,
पूर्ण;

अटल व्योम
mlxsw_sp_sample_trigger_key_init(काष्ठा mlxsw_sp_sample_trigger *key,
				 स्थिर काष्ठा mlxsw_sp_sample_trigger *trigger)
अणु
	स_रखो(key, 0, माप(*key));
	key->type = trigger->type;
	key->local_port = trigger->local_port;
पूर्ण

/* RCU पढ़ो lock must be held */
काष्ठा mlxsw_sp_sample_params *
mlxsw_sp_sample_trigger_params_lookup(काष्ठा mlxsw_sp *mlxsw_sp,
				      स्थिर काष्ठा mlxsw_sp_sample_trigger *trigger)
अणु
	काष्ठा mlxsw_sp_sample_trigger_node *trigger_node;
	काष्ठा mlxsw_sp_sample_trigger key;

	mlxsw_sp_sample_trigger_key_init(&key, trigger);
	trigger_node = rhashtable_lookup(&mlxsw_sp->sample_trigger_ht, &key,
					 mlxsw_sp_sample_trigger_ht_params);
	अगर (!trigger_node)
		वापस शून्य;

	वापस &trigger_node->params;
पूर्ण

अटल पूर्णांक
mlxsw_sp_sample_trigger_node_init(काष्ठा mlxsw_sp *mlxsw_sp,
				  स्थिर काष्ठा mlxsw_sp_sample_trigger *trigger,
				  स्थिर काष्ठा mlxsw_sp_sample_params *params)
अणु
	काष्ठा mlxsw_sp_sample_trigger_node *trigger_node;
	पूर्णांक err;

	trigger_node = kzalloc(माप(*trigger_node), GFP_KERNEL);
	अगर (!trigger_node)
		वापस -ENOMEM;

	trigger_node->trigger = *trigger;
	trigger_node->params = *params;
	refcount_set(&trigger_node->refcount, 1);

	err = rhashtable_insert_fast(&mlxsw_sp->sample_trigger_ht,
				     &trigger_node->ht_node,
				     mlxsw_sp_sample_trigger_ht_params);
	अगर (err)
		जाओ err_rhashtable_insert;

	वापस 0;

err_rhashtable_insert:
	kमुक्त(trigger_node);
	वापस err;
पूर्ण

अटल व्योम
mlxsw_sp_sample_trigger_node_fini(काष्ठा mlxsw_sp *mlxsw_sp,
				  काष्ठा mlxsw_sp_sample_trigger_node *trigger_node)
अणु
	rhashtable_हटाओ_fast(&mlxsw_sp->sample_trigger_ht,
			       &trigger_node->ht_node,
			       mlxsw_sp_sample_trigger_ht_params);
	kमुक्त_rcu(trigger_node, rcu);
पूर्ण

पूर्णांक
mlxsw_sp_sample_trigger_params_set(काष्ठा mlxsw_sp *mlxsw_sp,
				   स्थिर काष्ठा mlxsw_sp_sample_trigger *trigger,
				   स्थिर काष्ठा mlxsw_sp_sample_params *params,
				   काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlxsw_sp_sample_trigger_node *trigger_node;
	काष्ठा mlxsw_sp_sample_trigger key;

	ASSERT_RTNL();

	mlxsw_sp_sample_trigger_key_init(&key, trigger);

	trigger_node = rhashtable_lookup_fast(&mlxsw_sp->sample_trigger_ht,
					      &key,
					      mlxsw_sp_sample_trigger_ht_params);
	अगर (!trigger_node)
		वापस mlxsw_sp_sample_trigger_node_init(mlxsw_sp, &key,
							 params);

	अगर (trigger_node->trigger.local_port) अणु
		NL_SET_ERR_MSG_MOD(extack, "Sampling already enabled on port");
		वापस -EINVAL;
	पूर्ण

	अगर (trigger_node->params.psample_group != params->psample_group ||
	    trigger_node->params.truncate != params->truncate ||
	    trigger_node->params.rate != params->rate ||
	    trigger_node->params.trunc_size != params->trunc_size) अणु
		NL_SET_ERR_MSG_MOD(extack, "Sampling parameters do not match for an existing sampling trigger");
		वापस -EINVAL;
	पूर्ण

	refcount_inc(&trigger_node->refcount);

	वापस 0;
पूर्ण

व्योम
mlxsw_sp_sample_trigger_params_unset(काष्ठा mlxsw_sp *mlxsw_sp,
				     स्थिर काष्ठा mlxsw_sp_sample_trigger *trigger)
अणु
	काष्ठा mlxsw_sp_sample_trigger_node *trigger_node;
	काष्ठा mlxsw_sp_sample_trigger key;

	ASSERT_RTNL();

	mlxsw_sp_sample_trigger_key_init(&key, trigger);

	trigger_node = rhashtable_lookup_fast(&mlxsw_sp->sample_trigger_ht,
					      &key,
					      mlxsw_sp_sample_trigger_ht_params);
	अगर (!trigger_node)
		वापस;

	अगर (!refcount_dec_and_test(&trigger_node->refcount))
		वापस;

	mlxsw_sp_sample_trigger_node_fini(mlxsw_sp, trigger_node);
पूर्ण

अटल पूर्णांक mlxsw_sp_netdevice_event(काष्ठा notअगरier_block *unused,
				    अचिन्हित दीर्घ event, व्योम *ptr);

अटल पूर्णांक mlxsw_sp_init(काष्ठा mlxsw_core *mlxsw_core,
			 स्थिर काष्ठा mlxsw_bus_info *mlxsw_bus_info,
			 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_core_driver_priv(mlxsw_core);
	पूर्णांक err;

	mlxsw_sp->core = mlxsw_core;
	mlxsw_sp->bus_info = mlxsw_bus_info;

	mlxsw_core_emad_string_tlv_enable(mlxsw_core);

	err = mlxsw_sp_base_mac_get(mlxsw_sp);
	अगर (err) अणु
		dev_err(mlxsw_sp->bus_info->dev, "Failed to get base mac\n");
		वापस err;
	पूर्ण

	err = mlxsw_sp_kvdl_init(mlxsw_sp);
	अगर (err) अणु
		dev_err(mlxsw_sp->bus_info->dev, "Failed to initialize KVDL\n");
		वापस err;
	पूर्ण

	err = mlxsw_sp_fids_init(mlxsw_sp);
	अगर (err) अणु
		dev_err(mlxsw_sp->bus_info->dev, "Failed to initialize FIDs\n");
		जाओ err_fids_init;
	पूर्ण

	err = mlxsw_sp_policers_init(mlxsw_sp);
	अगर (err) अणु
		dev_err(mlxsw_sp->bus_info->dev, "Failed to initialize policers\n");
		जाओ err_policers_init;
	पूर्ण

	err = mlxsw_sp_traps_init(mlxsw_sp);
	अगर (err) अणु
		dev_err(mlxsw_sp->bus_info->dev, "Failed to set traps\n");
		जाओ err_traps_init;
	पूर्ण

	err = mlxsw_sp_devlink_traps_init(mlxsw_sp);
	अगर (err) अणु
		dev_err(mlxsw_sp->bus_info->dev, "Failed to initialize devlink traps\n");
		जाओ err_devlink_traps_init;
	पूर्ण

	err = mlxsw_sp_buffers_init(mlxsw_sp);
	अगर (err) अणु
		dev_err(mlxsw_sp->bus_info->dev, "Failed to initialize buffers\n");
		जाओ err_buffers_init;
	पूर्ण

	err = mlxsw_sp_lag_init(mlxsw_sp);
	अगर (err) अणु
		dev_err(mlxsw_sp->bus_info->dev, "Failed to initialize LAG\n");
		जाओ err_lag_init;
	पूर्ण

	/* Initialize SPAN beक्रमe router and चयनdev, so that those components
	 * can call mlxsw_sp_span_respin().
	 */
	err = mlxsw_sp_span_init(mlxsw_sp);
	अगर (err) अणु
		dev_err(mlxsw_sp->bus_info->dev, "Failed to init span system\n");
		जाओ err_span_init;
	पूर्ण

	err = mlxsw_sp_चयनdev_init(mlxsw_sp);
	अगर (err) अणु
		dev_err(mlxsw_sp->bus_info->dev, "Failed to initialize switchdev\n");
		जाओ err_चयनdev_init;
	पूर्ण

	err = mlxsw_sp_counter_pool_init(mlxsw_sp);
	अगर (err) अणु
		dev_err(mlxsw_sp->bus_info->dev, "Failed to init counter pool\n");
		जाओ err_counter_pool_init;
	पूर्ण

	err = mlxsw_sp_afa_init(mlxsw_sp);
	अगर (err) अणु
		dev_err(mlxsw_sp->bus_info->dev, "Failed to initialize ACL actions\n");
		जाओ err_afa_init;
	पूर्ण

	err = mlxsw_sp_nve_init(mlxsw_sp);
	अगर (err) अणु
		dev_err(mlxsw_sp->bus_info->dev, "Failed to initialize NVE\n");
		जाओ err_nve_init;
	पूर्ण

	err = mlxsw_sp_acl_init(mlxsw_sp);
	अगर (err) अणु
		dev_err(mlxsw_sp->bus_info->dev, "Failed to initialize ACL\n");
		जाओ err_acl_init;
	पूर्ण

	err = mlxsw_sp_router_init(mlxsw_sp, extack);
	अगर (err) अणु
		dev_err(mlxsw_sp->bus_info->dev, "Failed to initialize router\n");
		जाओ err_router_init;
	पूर्ण

	अगर (mlxsw_sp->bus_info->पढ़ो_frc_capable) अणु
		/* शून्य is a valid वापस value from घड़ी_init */
		mlxsw_sp->घड़ी =
			mlxsw_sp->ptp_ops->घड़ी_init(mlxsw_sp,
						      mlxsw_sp->bus_info->dev);
		अगर (IS_ERR(mlxsw_sp->घड़ी)) अणु
			err = PTR_ERR(mlxsw_sp->घड़ी);
			dev_err(mlxsw_sp->bus_info->dev, "Failed to init ptp clock\n");
			जाओ err_ptp_घड़ी_init;
		पूर्ण
	पूर्ण

	अगर (mlxsw_sp->घड़ी) अणु
		/* शून्य is a valid वापस value from ptp_ops->init */
		mlxsw_sp->ptp_state = mlxsw_sp->ptp_ops->init(mlxsw_sp);
		अगर (IS_ERR(mlxsw_sp->ptp_state)) अणु
			err = PTR_ERR(mlxsw_sp->ptp_state);
			dev_err(mlxsw_sp->bus_info->dev, "Failed to initialize PTP\n");
			जाओ err_ptp_init;
		पूर्ण
	पूर्ण

	/* Initialize netdevice notअगरier after router and SPAN is initialized,
	 * so that the event handler can use router काष्ठाures and call SPAN
	 * respin.
	 */
	mlxsw_sp->netdevice_nb.notअगरier_call = mlxsw_sp_netdevice_event;
	err = रेजिस्टर_netdevice_notअगरier_net(mlxsw_sp_net(mlxsw_sp),
					      &mlxsw_sp->netdevice_nb);
	अगर (err) अणु
		dev_err(mlxsw_sp->bus_info->dev, "Failed to register netdev notifier\n");
		जाओ err_netdev_notअगरier;
	पूर्ण

	err = mlxsw_sp_dpipe_init(mlxsw_sp);
	अगर (err) अणु
		dev_err(mlxsw_sp->bus_info->dev, "Failed to init pipeline debug\n");
		जाओ err_dpipe_init;
	पूर्ण

	err = mlxsw_sp_port_module_info_init(mlxsw_sp);
	अगर (err) अणु
		dev_err(mlxsw_sp->bus_info->dev, "Failed to init port module info\n");
		जाओ err_port_module_info_init;
	पूर्ण

	err = rhashtable_init(&mlxsw_sp->sample_trigger_ht,
			      &mlxsw_sp_sample_trigger_ht_params);
	अगर (err) अणु
		dev_err(mlxsw_sp->bus_info->dev, "Failed to init sampling trigger hashtable\n");
		जाओ err_sample_trigger_init;
	पूर्ण

	err = mlxsw_sp_ports_create(mlxsw_sp);
	अगर (err) अणु
		dev_err(mlxsw_sp->bus_info->dev, "Failed to create ports\n");
		जाओ err_ports_create;
	पूर्ण

	वापस 0;

err_ports_create:
	rhashtable_destroy(&mlxsw_sp->sample_trigger_ht);
err_sample_trigger_init:
	mlxsw_sp_port_module_info_fini(mlxsw_sp);
err_port_module_info_init:
	mlxsw_sp_dpipe_fini(mlxsw_sp);
err_dpipe_init:
	unरेजिस्टर_netdevice_notअगरier_net(mlxsw_sp_net(mlxsw_sp),
					  &mlxsw_sp->netdevice_nb);
err_netdev_notअगरier:
	अगर (mlxsw_sp->घड़ी)
		mlxsw_sp->ptp_ops->fini(mlxsw_sp->ptp_state);
err_ptp_init:
	अगर (mlxsw_sp->घड़ी)
		mlxsw_sp->ptp_ops->घड़ी_fini(mlxsw_sp->घड़ी);
err_ptp_घड़ी_init:
	mlxsw_sp_router_fini(mlxsw_sp);
err_router_init:
	mlxsw_sp_acl_fini(mlxsw_sp);
err_acl_init:
	mlxsw_sp_nve_fini(mlxsw_sp);
err_nve_init:
	mlxsw_sp_afa_fini(mlxsw_sp);
err_afa_init:
	mlxsw_sp_counter_pool_fini(mlxsw_sp);
err_counter_pool_init:
	mlxsw_sp_चयनdev_fini(mlxsw_sp);
err_चयनdev_init:
	mlxsw_sp_span_fini(mlxsw_sp);
err_span_init:
	mlxsw_sp_lag_fini(mlxsw_sp);
err_lag_init:
	mlxsw_sp_buffers_fini(mlxsw_sp);
err_buffers_init:
	mlxsw_sp_devlink_traps_fini(mlxsw_sp);
err_devlink_traps_init:
	mlxsw_sp_traps_fini(mlxsw_sp);
err_traps_init:
	mlxsw_sp_policers_fini(mlxsw_sp);
err_policers_init:
	mlxsw_sp_fids_fini(mlxsw_sp);
err_fids_init:
	mlxsw_sp_kvdl_fini(mlxsw_sp);
	वापस err;
पूर्ण

अटल पूर्णांक mlxsw_sp1_init(काष्ठा mlxsw_core *mlxsw_core,
			  स्थिर काष्ठा mlxsw_bus_info *mlxsw_bus_info,
			  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_core_driver_priv(mlxsw_core);

	mlxsw_sp->चयनdev_ops = &mlxsw_sp1_चयनdev_ops;
	mlxsw_sp->kvdl_ops = &mlxsw_sp1_kvdl_ops;
	mlxsw_sp->afa_ops = &mlxsw_sp1_act_afa_ops;
	mlxsw_sp->afk_ops = &mlxsw_sp1_afk_ops;
	mlxsw_sp->mr_tcam_ops = &mlxsw_sp1_mr_tcam_ops;
	mlxsw_sp->acl_rulei_ops = &mlxsw_sp1_acl_rulei_ops;
	mlxsw_sp->acl_tcam_ops = &mlxsw_sp1_acl_tcam_ops;
	mlxsw_sp->nve_ops_arr = mlxsw_sp1_nve_ops_arr;
	mlxsw_sp->mac_mask = mlxsw_sp1_mac_mask;
	mlxsw_sp->sb_vals = &mlxsw_sp1_sb_vals;
	mlxsw_sp->sb_ops = &mlxsw_sp1_sb_ops;
	mlxsw_sp->port_type_speed_ops = &mlxsw_sp1_port_type_speed_ops;
	mlxsw_sp->ptp_ops = &mlxsw_sp1_ptp_ops;
	mlxsw_sp->span_ops = &mlxsw_sp1_span_ops;
	mlxsw_sp->policer_core_ops = &mlxsw_sp1_policer_core_ops;
	mlxsw_sp->trap_ops = &mlxsw_sp1_trap_ops;
	mlxsw_sp->mall_ops = &mlxsw_sp1_mall_ops;
	mlxsw_sp->router_ops = &mlxsw_sp1_router_ops;
	mlxsw_sp->listeners = mlxsw_sp1_listener;
	mlxsw_sp->listeners_count = ARRAY_SIZE(mlxsw_sp1_listener);
	mlxsw_sp->lowest_shaper_bs = MLXSW_REG_QEEC_LOWEST_SHAPER_BS_SP1;

	वापस mlxsw_sp_init(mlxsw_core, mlxsw_bus_info, extack);
पूर्ण

अटल पूर्णांक mlxsw_sp2_init(काष्ठा mlxsw_core *mlxsw_core,
			  स्थिर काष्ठा mlxsw_bus_info *mlxsw_bus_info,
			  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_core_driver_priv(mlxsw_core);

	mlxsw_sp->चयनdev_ops = &mlxsw_sp2_चयनdev_ops;
	mlxsw_sp->kvdl_ops = &mlxsw_sp2_kvdl_ops;
	mlxsw_sp->afa_ops = &mlxsw_sp2_act_afa_ops;
	mlxsw_sp->afk_ops = &mlxsw_sp2_afk_ops;
	mlxsw_sp->mr_tcam_ops = &mlxsw_sp2_mr_tcam_ops;
	mlxsw_sp->acl_rulei_ops = &mlxsw_sp2_acl_rulei_ops;
	mlxsw_sp->acl_tcam_ops = &mlxsw_sp2_acl_tcam_ops;
	mlxsw_sp->nve_ops_arr = mlxsw_sp2_nve_ops_arr;
	mlxsw_sp->mac_mask = mlxsw_sp2_mac_mask;
	mlxsw_sp->sb_vals = &mlxsw_sp2_sb_vals;
	mlxsw_sp->sb_ops = &mlxsw_sp2_sb_ops;
	mlxsw_sp->port_type_speed_ops = &mlxsw_sp2_port_type_speed_ops;
	mlxsw_sp->ptp_ops = &mlxsw_sp2_ptp_ops;
	mlxsw_sp->span_ops = &mlxsw_sp2_span_ops;
	mlxsw_sp->policer_core_ops = &mlxsw_sp2_policer_core_ops;
	mlxsw_sp->trap_ops = &mlxsw_sp2_trap_ops;
	mlxsw_sp->mall_ops = &mlxsw_sp2_mall_ops;
	mlxsw_sp->router_ops = &mlxsw_sp2_router_ops;
	mlxsw_sp->lowest_shaper_bs = MLXSW_REG_QEEC_LOWEST_SHAPER_BS_SP2;

	वापस mlxsw_sp_init(mlxsw_core, mlxsw_bus_info, extack);
पूर्ण

अटल पूर्णांक mlxsw_sp3_init(काष्ठा mlxsw_core *mlxsw_core,
			  स्थिर काष्ठा mlxsw_bus_info *mlxsw_bus_info,
			  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_core_driver_priv(mlxsw_core);

	mlxsw_sp->चयनdev_ops = &mlxsw_sp2_चयनdev_ops;
	mlxsw_sp->kvdl_ops = &mlxsw_sp2_kvdl_ops;
	mlxsw_sp->afa_ops = &mlxsw_sp2_act_afa_ops;
	mlxsw_sp->afk_ops = &mlxsw_sp2_afk_ops;
	mlxsw_sp->mr_tcam_ops = &mlxsw_sp2_mr_tcam_ops;
	mlxsw_sp->acl_rulei_ops = &mlxsw_sp2_acl_rulei_ops;
	mlxsw_sp->acl_tcam_ops = &mlxsw_sp2_acl_tcam_ops;
	mlxsw_sp->nve_ops_arr = mlxsw_sp2_nve_ops_arr;
	mlxsw_sp->mac_mask = mlxsw_sp2_mac_mask;
	mlxsw_sp->sb_vals = &mlxsw_sp2_sb_vals;
	mlxsw_sp->sb_ops = &mlxsw_sp3_sb_ops;
	mlxsw_sp->port_type_speed_ops = &mlxsw_sp2_port_type_speed_ops;
	mlxsw_sp->ptp_ops = &mlxsw_sp2_ptp_ops;
	mlxsw_sp->span_ops = &mlxsw_sp3_span_ops;
	mlxsw_sp->policer_core_ops = &mlxsw_sp2_policer_core_ops;
	mlxsw_sp->trap_ops = &mlxsw_sp2_trap_ops;
	mlxsw_sp->mall_ops = &mlxsw_sp2_mall_ops;
	mlxsw_sp->router_ops = &mlxsw_sp2_router_ops;
	mlxsw_sp->lowest_shaper_bs = MLXSW_REG_QEEC_LOWEST_SHAPER_BS_SP3;

	वापस mlxsw_sp_init(mlxsw_core, mlxsw_bus_info, extack);
पूर्ण

अटल व्योम mlxsw_sp_fini(काष्ठा mlxsw_core *mlxsw_core)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_core_driver_priv(mlxsw_core);

	mlxsw_sp_ports_हटाओ(mlxsw_sp);
	rhashtable_destroy(&mlxsw_sp->sample_trigger_ht);
	mlxsw_sp_port_module_info_fini(mlxsw_sp);
	mlxsw_sp_dpipe_fini(mlxsw_sp);
	unरेजिस्टर_netdevice_notअगरier_net(mlxsw_sp_net(mlxsw_sp),
					  &mlxsw_sp->netdevice_nb);
	अगर (mlxsw_sp->घड़ी) अणु
		mlxsw_sp->ptp_ops->fini(mlxsw_sp->ptp_state);
		mlxsw_sp->ptp_ops->घड़ी_fini(mlxsw_sp->घड़ी);
	पूर्ण
	mlxsw_sp_router_fini(mlxsw_sp);
	mlxsw_sp_acl_fini(mlxsw_sp);
	mlxsw_sp_nve_fini(mlxsw_sp);
	mlxsw_sp_afa_fini(mlxsw_sp);
	mlxsw_sp_counter_pool_fini(mlxsw_sp);
	mlxsw_sp_चयनdev_fini(mlxsw_sp);
	mlxsw_sp_span_fini(mlxsw_sp);
	mlxsw_sp_lag_fini(mlxsw_sp);
	mlxsw_sp_buffers_fini(mlxsw_sp);
	mlxsw_sp_devlink_traps_fini(mlxsw_sp);
	mlxsw_sp_traps_fini(mlxsw_sp);
	mlxsw_sp_policers_fini(mlxsw_sp);
	mlxsw_sp_fids_fini(mlxsw_sp);
	mlxsw_sp_kvdl_fini(mlxsw_sp);
पूर्ण

/* Per-FID flood tables are used क्रम both "true" 802.1D FIDs and emulated
 * 802.1Q FIDs
 */
#घोषणा MLXSW_SP_FID_FLOOD_TABLE_SIZE	(MLXSW_SP_FID_8021D_MAX + \
					 VLAN_VID_MASK - 1)

अटल स्थिर काष्ठा mlxsw_config_profile mlxsw_sp1_config_profile = अणु
	.used_max_mid			= 1,
	.max_mid			= MLXSW_SP_MID_MAX,
	.used_flood_tables		= 1,
	.used_flood_mode		= 1,
	.flood_mode			= 3,
	.max_fid_flood_tables		= 3,
	.fid_flood_table_size		= MLXSW_SP_FID_FLOOD_TABLE_SIZE,
	.used_max_ib_mc			= 1,
	.max_ib_mc			= 0,
	.used_max_pkey			= 1,
	.max_pkey			= 0,
	.used_kvd_sizes			= 1,
	.kvd_hash_single_parts		= 59,
	.kvd_hash_द्विगुन_parts		= 41,
	.kvd_linear_size		= MLXSW_SP_KVD_LINEAR_SIZE,
	.swid_config			= अणु
		अणु
			.used_type	= 1,
			.type		= MLXSW_PORT_SWID_TYPE_ETH,
		पूर्ण
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mlxsw_config_profile mlxsw_sp2_config_profile = अणु
	.used_max_mid			= 1,
	.max_mid			= MLXSW_SP_MID_MAX,
	.used_flood_tables		= 1,
	.used_flood_mode		= 1,
	.flood_mode			= 3,
	.max_fid_flood_tables		= 3,
	.fid_flood_table_size		= MLXSW_SP_FID_FLOOD_TABLE_SIZE,
	.used_max_ib_mc			= 1,
	.max_ib_mc			= 0,
	.used_max_pkey			= 1,
	.max_pkey			= 0,
	.used_kvh_xlt_cache_mode	= 1,
	.kvh_xlt_cache_mode		= 1,
	.swid_config			= अणु
		अणु
			.used_type	= 1,
			.type		= MLXSW_PORT_SWID_TYPE_ETH,
		पूर्ण
	पूर्ण,
पूर्ण;

अटल व्योम
mlxsw_sp_resource_size_params_prepare(काष्ठा mlxsw_core *mlxsw_core,
				      काष्ठा devlink_resource_size_params *kvd_size_params,
				      काष्ठा devlink_resource_size_params *linear_size_params,
				      काष्ठा devlink_resource_size_params *hash_द्विगुन_size_params,
				      काष्ठा devlink_resource_size_params *hash_single_size_params)
अणु
	u32 single_size_min = MLXSW_CORE_RES_GET(mlxsw_core,
						 KVD_SINGLE_MIN_SIZE);
	u32 द्विगुन_size_min = MLXSW_CORE_RES_GET(mlxsw_core,
						 KVD_DOUBLE_MIN_SIZE);
	u32 kvd_size = MLXSW_CORE_RES_GET(mlxsw_core, KVD_SIZE);
	u32 linear_size_min = 0;

	devlink_resource_size_params_init(kvd_size_params, kvd_size, kvd_size,
					  MLXSW_SP_KVD_GRANULARITY,
					  DEVLINK_RESOURCE_UNIT_ENTRY);
	devlink_resource_size_params_init(linear_size_params, linear_size_min,
					  kvd_size - single_size_min -
					  द्विगुन_size_min,
					  MLXSW_SP_KVD_GRANULARITY,
					  DEVLINK_RESOURCE_UNIT_ENTRY);
	devlink_resource_size_params_init(hash_द्विगुन_size_params,
					  द्विगुन_size_min,
					  kvd_size - single_size_min -
					  linear_size_min,
					  MLXSW_SP_KVD_GRANULARITY,
					  DEVLINK_RESOURCE_UNIT_ENTRY);
	devlink_resource_size_params_init(hash_single_size_params,
					  single_size_min,
					  kvd_size - द्विगुन_size_min -
					  linear_size_min,
					  MLXSW_SP_KVD_GRANULARITY,
					  DEVLINK_RESOURCE_UNIT_ENTRY);
पूर्ण

अटल पूर्णांक mlxsw_sp1_resources_kvd_रेजिस्टर(काष्ठा mlxsw_core *mlxsw_core)
अणु
	काष्ठा devlink *devlink = priv_to_devlink(mlxsw_core);
	काष्ठा devlink_resource_size_params hash_single_size_params;
	काष्ठा devlink_resource_size_params hash_द्विगुन_size_params;
	काष्ठा devlink_resource_size_params linear_size_params;
	काष्ठा devlink_resource_size_params kvd_size_params;
	u32 kvd_size, single_size, द्विगुन_size, linear_size;
	स्थिर काष्ठा mlxsw_config_profile *profile;
	पूर्णांक err;

	profile = &mlxsw_sp1_config_profile;
	अगर (!MLXSW_CORE_RES_VALID(mlxsw_core, KVD_SIZE))
		वापस -EIO;

	mlxsw_sp_resource_size_params_prepare(mlxsw_core, &kvd_size_params,
					      &linear_size_params,
					      &hash_द्विगुन_size_params,
					      &hash_single_size_params);

	kvd_size = MLXSW_CORE_RES_GET(mlxsw_core, KVD_SIZE);
	err = devlink_resource_रेजिस्टर(devlink, MLXSW_SP_RESOURCE_NAME_KVD,
					kvd_size, MLXSW_SP_RESOURCE_KVD,
					DEVLINK_RESOURCE_ID_PARENT_TOP,
					&kvd_size_params);
	अगर (err)
		वापस err;

	linear_size = profile->kvd_linear_size;
	err = devlink_resource_रेजिस्टर(devlink, MLXSW_SP_RESOURCE_NAME_KVD_LINEAR,
					linear_size,
					MLXSW_SP_RESOURCE_KVD_LINEAR,
					MLXSW_SP_RESOURCE_KVD,
					&linear_size_params);
	अगर (err)
		वापस err;

	err = mlxsw_sp1_kvdl_resources_रेजिस्टर(mlxsw_core);
	अगर  (err)
		वापस err;

	द्विगुन_size = kvd_size - linear_size;
	द्विगुन_size *= profile->kvd_hash_द्विगुन_parts;
	द्विगुन_size /= profile->kvd_hash_द्विगुन_parts +
		       profile->kvd_hash_single_parts;
	द्विगुन_size = roundकरोwn(द्विगुन_size, MLXSW_SP_KVD_GRANULARITY);
	err = devlink_resource_रेजिस्टर(devlink, MLXSW_SP_RESOURCE_NAME_KVD_HASH_DOUBLE,
					द्विगुन_size,
					MLXSW_SP_RESOURCE_KVD_HASH_DOUBLE,
					MLXSW_SP_RESOURCE_KVD,
					&hash_द्विगुन_size_params);
	अगर (err)
		वापस err;

	single_size = kvd_size - द्विगुन_size - linear_size;
	err = devlink_resource_रेजिस्टर(devlink, MLXSW_SP_RESOURCE_NAME_KVD_HASH_SINGLE,
					single_size,
					MLXSW_SP_RESOURCE_KVD_HASH_SINGLE,
					MLXSW_SP_RESOURCE_KVD,
					&hash_single_size_params);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_sp2_resources_kvd_रेजिस्टर(काष्ठा mlxsw_core *mlxsw_core)
अणु
	काष्ठा devlink *devlink = priv_to_devlink(mlxsw_core);
	काष्ठा devlink_resource_size_params kvd_size_params;
	u32 kvd_size;

	अगर (!MLXSW_CORE_RES_VALID(mlxsw_core, KVD_SIZE))
		वापस -EIO;

	kvd_size = MLXSW_CORE_RES_GET(mlxsw_core, KVD_SIZE);
	devlink_resource_size_params_init(&kvd_size_params, kvd_size, kvd_size,
					  MLXSW_SP_KVD_GRANULARITY,
					  DEVLINK_RESOURCE_UNIT_ENTRY);

	वापस devlink_resource_रेजिस्टर(devlink, MLXSW_SP_RESOURCE_NAME_KVD,
					 kvd_size, MLXSW_SP_RESOURCE_KVD,
					 DEVLINK_RESOURCE_ID_PARENT_TOP,
					 &kvd_size_params);
पूर्ण

अटल पूर्णांक mlxsw_sp_resources_span_रेजिस्टर(काष्ठा mlxsw_core *mlxsw_core)
अणु
	काष्ठा devlink *devlink = priv_to_devlink(mlxsw_core);
	काष्ठा devlink_resource_size_params span_size_params;
	u32 max_span;

	अगर (!MLXSW_CORE_RES_VALID(mlxsw_core, MAX_SPAN))
		वापस -EIO;

	max_span = MLXSW_CORE_RES_GET(mlxsw_core, MAX_SPAN);
	devlink_resource_size_params_init(&span_size_params, max_span, max_span,
					  1, DEVLINK_RESOURCE_UNIT_ENTRY);

	वापस devlink_resource_रेजिस्टर(devlink, MLXSW_SP_RESOURCE_NAME_SPAN,
					 max_span, MLXSW_SP_RESOURCE_SPAN,
					 DEVLINK_RESOURCE_ID_PARENT_TOP,
					 &span_size_params);
पूर्ण

अटल पूर्णांक mlxsw_sp1_resources_रेजिस्टर(काष्ठा mlxsw_core *mlxsw_core)
अणु
	पूर्णांक err;

	err = mlxsw_sp1_resources_kvd_रेजिस्टर(mlxsw_core);
	अगर (err)
		वापस err;

	err = mlxsw_sp_resources_span_रेजिस्टर(mlxsw_core);
	अगर (err)
		जाओ err_resources_span_रेजिस्टर;

	err = mlxsw_sp_counter_resources_रेजिस्टर(mlxsw_core);
	अगर (err)
		जाओ err_resources_counter_रेजिस्टर;

	err = mlxsw_sp_policer_resources_रेजिस्टर(mlxsw_core);
	अगर (err)
		जाओ err_resources_counter_रेजिस्टर;

	वापस 0;

err_resources_counter_रेजिस्टर:
err_resources_span_रेजिस्टर:
	devlink_resources_unरेजिस्टर(priv_to_devlink(mlxsw_core), शून्य);
	वापस err;
पूर्ण

अटल पूर्णांक mlxsw_sp2_resources_रेजिस्टर(काष्ठा mlxsw_core *mlxsw_core)
अणु
	पूर्णांक err;

	err = mlxsw_sp2_resources_kvd_रेजिस्टर(mlxsw_core);
	अगर (err)
		वापस err;

	err = mlxsw_sp_resources_span_रेजिस्टर(mlxsw_core);
	अगर (err)
		जाओ err_resources_span_रेजिस्टर;

	err = mlxsw_sp_counter_resources_रेजिस्टर(mlxsw_core);
	अगर (err)
		जाओ err_resources_counter_रेजिस्टर;

	err = mlxsw_sp_policer_resources_रेजिस्टर(mlxsw_core);
	अगर (err)
		जाओ err_resources_counter_रेजिस्टर;

	वापस 0;

err_resources_counter_रेजिस्टर:
err_resources_span_रेजिस्टर:
	devlink_resources_unरेजिस्टर(priv_to_devlink(mlxsw_core), शून्य);
	वापस err;
पूर्ण

अटल पूर्णांक mlxsw_sp_kvd_sizes_get(काष्ठा mlxsw_core *mlxsw_core,
				  स्थिर काष्ठा mlxsw_config_profile *profile,
				  u64 *p_single_size, u64 *p_द्विगुन_size,
				  u64 *p_linear_size)
अणु
	काष्ठा devlink *devlink = priv_to_devlink(mlxsw_core);
	u32 द्विगुन_size;
	पूर्णांक err;

	अगर (!MLXSW_CORE_RES_VALID(mlxsw_core, KVD_SINGLE_MIN_SIZE) ||
	    !MLXSW_CORE_RES_VALID(mlxsw_core, KVD_DOUBLE_MIN_SIZE))
		वापस -EIO;

	/* The hash part is what left of the kvd without the
	 * linear part. It is split to the single size and
	 * द्विगुन size by the parts ratio from the profile.
	 * Both sizes must be a multiplications of the
	 * granularity from the profile. In हाल the user
	 * provided the sizes they are obtained via devlink.
	 */
	err = devlink_resource_size_get(devlink,
					MLXSW_SP_RESOURCE_KVD_LINEAR,
					p_linear_size);
	अगर (err)
		*p_linear_size = profile->kvd_linear_size;

	err = devlink_resource_size_get(devlink,
					MLXSW_SP_RESOURCE_KVD_HASH_DOUBLE,
					p_द्विगुन_size);
	अगर (err) अणु
		द्विगुन_size = MLXSW_CORE_RES_GET(mlxsw_core, KVD_SIZE) -
			      *p_linear_size;
		द्विगुन_size *= profile->kvd_hash_द्विगुन_parts;
		द्विगुन_size /= profile->kvd_hash_द्विगुन_parts +
			       profile->kvd_hash_single_parts;
		*p_द्विगुन_size = roundकरोwn(द्विगुन_size,
					   MLXSW_SP_KVD_GRANULARITY);
	पूर्ण

	err = devlink_resource_size_get(devlink,
					MLXSW_SP_RESOURCE_KVD_HASH_SINGLE,
					p_single_size);
	अगर (err)
		*p_single_size = MLXSW_CORE_RES_GET(mlxsw_core, KVD_SIZE) -
				 *p_द्विगुन_size - *p_linear_size;

	/* Check results are legal. */
	अगर (*p_single_size < MLXSW_CORE_RES_GET(mlxsw_core, KVD_SINGLE_MIN_SIZE) ||
	    *p_द्विगुन_size < MLXSW_CORE_RES_GET(mlxsw_core, KVD_DOUBLE_MIN_SIZE) ||
	    MLXSW_CORE_RES_GET(mlxsw_core, KVD_SIZE) < *p_linear_size)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक
mlxsw_sp_params_acl_region_rehash_पूर्णांकrvl_get(काष्ठा devlink *devlink, u32 id,
					     काष्ठा devlink_param_gset_ctx *ctx)
अणु
	काष्ठा mlxsw_core *mlxsw_core = devlink_priv(devlink);
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_core_driver_priv(mlxsw_core);

	ctx->val.vu32 = mlxsw_sp_acl_region_rehash_पूर्णांकrvl_get(mlxsw_sp);
	वापस 0;
पूर्ण

अटल पूर्णांक
mlxsw_sp_params_acl_region_rehash_पूर्णांकrvl_set(काष्ठा devlink *devlink, u32 id,
					     काष्ठा devlink_param_gset_ctx *ctx)
अणु
	काष्ठा mlxsw_core *mlxsw_core = devlink_priv(devlink);
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_core_driver_priv(mlxsw_core);

	वापस mlxsw_sp_acl_region_rehash_पूर्णांकrvl_set(mlxsw_sp, ctx->val.vu32);
पूर्ण

अटल स्थिर काष्ठा devlink_param mlxsw_sp2_devlink_params[] = अणु
	DEVLINK_PARAM_DRIVER(MLXSW_DEVLINK_PARAM_ID_ACL_REGION_REHASH_INTERVAL,
			     "acl_region_rehash_interval",
			     DEVLINK_PARAM_TYPE_U32,
			     BIT(DEVLINK_PARAM_CMODE_RUNTIME),
			     mlxsw_sp_params_acl_region_rehash_पूर्णांकrvl_get,
			     mlxsw_sp_params_acl_region_rehash_पूर्णांकrvl_set,
			     शून्य),
पूर्ण;

अटल पूर्णांक mlxsw_sp2_params_रेजिस्टर(काष्ठा mlxsw_core *mlxsw_core)
अणु
	काष्ठा devlink *devlink = priv_to_devlink(mlxsw_core);
	जोड़ devlink_param_value value;
	पूर्णांक err;

	err = devlink_params_रेजिस्टर(devlink, mlxsw_sp2_devlink_params,
				      ARRAY_SIZE(mlxsw_sp2_devlink_params));
	अगर (err)
		वापस err;

	value.vu32 = 0;
	devlink_param_driverinit_value_set(devlink,
					   MLXSW_DEVLINK_PARAM_ID_ACL_REGION_REHASH_INTERVAL,
					   value);
	वापस 0;
पूर्ण

अटल व्योम mlxsw_sp2_params_unरेजिस्टर(काष्ठा mlxsw_core *mlxsw_core)
अणु
	devlink_params_unरेजिस्टर(priv_to_devlink(mlxsw_core),
				  mlxsw_sp2_devlink_params,
				  ARRAY_SIZE(mlxsw_sp2_devlink_params));
पूर्ण

अटल व्योम mlxsw_sp_ptp_transmitted(काष्ठा mlxsw_core *mlxsw_core,
				     काष्ठा sk_buff *skb, u8 local_port)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_core_driver_priv(mlxsw_core);

	skb_pull(skb, MLXSW_TXHDR_LEN);
	mlxsw_sp->ptp_ops->transmitted(mlxsw_sp, skb, local_port);
पूर्ण

अटल काष्ठा mlxsw_driver mlxsw_sp1_driver = अणु
	.kind				= mlxsw_sp1_driver_name,
	.priv_size			= माप(काष्ठा mlxsw_sp),
	.fw_req_rev			= &mlxsw_sp1_fw_rev,
	.fw_filename			= MLXSW_SP1_FW_खाताNAME,
	.init				= mlxsw_sp1_init,
	.fini				= mlxsw_sp_fini,
	.basic_trap_groups_set		= mlxsw_sp_basic_trap_groups_set,
	.port_split			= mlxsw_sp_port_split,
	.port_unsplit			= mlxsw_sp_port_unsplit,
	.sb_pool_get			= mlxsw_sp_sb_pool_get,
	.sb_pool_set			= mlxsw_sp_sb_pool_set,
	.sb_port_pool_get		= mlxsw_sp_sb_port_pool_get,
	.sb_port_pool_set		= mlxsw_sp_sb_port_pool_set,
	.sb_tc_pool_bind_get		= mlxsw_sp_sb_tc_pool_bind_get,
	.sb_tc_pool_bind_set		= mlxsw_sp_sb_tc_pool_bind_set,
	.sb_occ_snapshot		= mlxsw_sp_sb_occ_snapshot,
	.sb_occ_max_clear		= mlxsw_sp_sb_occ_max_clear,
	.sb_occ_port_pool_get		= mlxsw_sp_sb_occ_port_pool_get,
	.sb_occ_tc_port_bind_get	= mlxsw_sp_sb_occ_tc_port_bind_get,
	.trap_init			= mlxsw_sp_trap_init,
	.trap_fini			= mlxsw_sp_trap_fini,
	.trap_action_set		= mlxsw_sp_trap_action_set,
	.trap_group_init		= mlxsw_sp_trap_group_init,
	.trap_group_set			= mlxsw_sp_trap_group_set,
	.trap_policer_init		= mlxsw_sp_trap_policer_init,
	.trap_policer_fini		= mlxsw_sp_trap_policer_fini,
	.trap_policer_set		= mlxsw_sp_trap_policer_set,
	.trap_policer_counter_get	= mlxsw_sp_trap_policer_counter_get,
	.txhdr_स्थिरruct		= mlxsw_sp_txhdr_स्थिरruct,
	.resources_रेजिस्टर		= mlxsw_sp1_resources_रेजिस्टर,
	.kvd_sizes_get			= mlxsw_sp_kvd_sizes_get,
	.ptp_transmitted		= mlxsw_sp_ptp_transmitted,
	.txhdr_len			= MLXSW_TXHDR_LEN,
	.profile			= &mlxsw_sp1_config_profile,
	.res_query_enabled		= true,
	.fw_fatal_enabled		= true,
	.temp_warn_enabled		= true,
पूर्ण;

अटल काष्ठा mlxsw_driver mlxsw_sp2_driver = अणु
	.kind				= mlxsw_sp2_driver_name,
	.priv_size			= माप(काष्ठा mlxsw_sp),
	.fw_req_rev			= &mlxsw_sp2_fw_rev,
	.fw_filename			= MLXSW_SP2_FW_खाताNAME,
	.init				= mlxsw_sp2_init,
	.fini				= mlxsw_sp_fini,
	.basic_trap_groups_set		= mlxsw_sp_basic_trap_groups_set,
	.port_split			= mlxsw_sp_port_split,
	.port_unsplit			= mlxsw_sp_port_unsplit,
	.sb_pool_get			= mlxsw_sp_sb_pool_get,
	.sb_pool_set			= mlxsw_sp_sb_pool_set,
	.sb_port_pool_get		= mlxsw_sp_sb_port_pool_get,
	.sb_port_pool_set		= mlxsw_sp_sb_port_pool_set,
	.sb_tc_pool_bind_get		= mlxsw_sp_sb_tc_pool_bind_get,
	.sb_tc_pool_bind_set		= mlxsw_sp_sb_tc_pool_bind_set,
	.sb_occ_snapshot		= mlxsw_sp_sb_occ_snapshot,
	.sb_occ_max_clear		= mlxsw_sp_sb_occ_max_clear,
	.sb_occ_port_pool_get		= mlxsw_sp_sb_occ_port_pool_get,
	.sb_occ_tc_port_bind_get	= mlxsw_sp_sb_occ_tc_port_bind_get,
	.trap_init			= mlxsw_sp_trap_init,
	.trap_fini			= mlxsw_sp_trap_fini,
	.trap_action_set		= mlxsw_sp_trap_action_set,
	.trap_group_init		= mlxsw_sp_trap_group_init,
	.trap_group_set			= mlxsw_sp_trap_group_set,
	.trap_policer_init		= mlxsw_sp_trap_policer_init,
	.trap_policer_fini		= mlxsw_sp_trap_policer_fini,
	.trap_policer_set		= mlxsw_sp_trap_policer_set,
	.trap_policer_counter_get	= mlxsw_sp_trap_policer_counter_get,
	.txhdr_स्थिरruct		= mlxsw_sp_txhdr_स्थिरruct,
	.resources_रेजिस्टर		= mlxsw_sp2_resources_रेजिस्टर,
	.params_रेजिस्टर		= mlxsw_sp2_params_रेजिस्टर,
	.params_unरेजिस्टर		= mlxsw_sp2_params_unरेजिस्टर,
	.ptp_transmitted		= mlxsw_sp_ptp_transmitted,
	.txhdr_len			= MLXSW_TXHDR_LEN,
	.profile			= &mlxsw_sp2_config_profile,
	.res_query_enabled		= true,
	.fw_fatal_enabled		= true,
	.temp_warn_enabled		= true,
पूर्ण;

अटल काष्ठा mlxsw_driver mlxsw_sp3_driver = अणु
	.kind				= mlxsw_sp3_driver_name,
	.priv_size			= माप(काष्ठा mlxsw_sp),
	.fw_req_rev			= &mlxsw_sp3_fw_rev,
	.fw_filename			= MLXSW_SP3_FW_खाताNAME,
	.init				= mlxsw_sp3_init,
	.fini				= mlxsw_sp_fini,
	.basic_trap_groups_set		= mlxsw_sp_basic_trap_groups_set,
	.port_split			= mlxsw_sp_port_split,
	.port_unsplit			= mlxsw_sp_port_unsplit,
	.sb_pool_get			= mlxsw_sp_sb_pool_get,
	.sb_pool_set			= mlxsw_sp_sb_pool_set,
	.sb_port_pool_get		= mlxsw_sp_sb_port_pool_get,
	.sb_port_pool_set		= mlxsw_sp_sb_port_pool_set,
	.sb_tc_pool_bind_get		= mlxsw_sp_sb_tc_pool_bind_get,
	.sb_tc_pool_bind_set		= mlxsw_sp_sb_tc_pool_bind_set,
	.sb_occ_snapshot		= mlxsw_sp_sb_occ_snapshot,
	.sb_occ_max_clear		= mlxsw_sp_sb_occ_max_clear,
	.sb_occ_port_pool_get		= mlxsw_sp_sb_occ_port_pool_get,
	.sb_occ_tc_port_bind_get	= mlxsw_sp_sb_occ_tc_port_bind_get,
	.trap_init			= mlxsw_sp_trap_init,
	.trap_fini			= mlxsw_sp_trap_fini,
	.trap_action_set		= mlxsw_sp_trap_action_set,
	.trap_group_init		= mlxsw_sp_trap_group_init,
	.trap_group_set			= mlxsw_sp_trap_group_set,
	.trap_policer_init		= mlxsw_sp_trap_policer_init,
	.trap_policer_fini		= mlxsw_sp_trap_policer_fini,
	.trap_policer_set		= mlxsw_sp_trap_policer_set,
	.trap_policer_counter_get	= mlxsw_sp_trap_policer_counter_get,
	.txhdr_स्थिरruct		= mlxsw_sp_txhdr_स्थिरruct,
	.resources_रेजिस्टर		= mlxsw_sp2_resources_रेजिस्टर,
	.params_रेजिस्टर		= mlxsw_sp2_params_रेजिस्टर,
	.params_unरेजिस्टर		= mlxsw_sp2_params_unरेजिस्टर,
	.ptp_transmitted		= mlxsw_sp_ptp_transmitted,
	.txhdr_len			= MLXSW_TXHDR_LEN,
	.profile			= &mlxsw_sp2_config_profile,
	.res_query_enabled		= true,
	.fw_fatal_enabled		= true,
	.temp_warn_enabled		= true,
पूर्ण;

bool mlxsw_sp_port_dev_check(स्थिर काष्ठा net_device *dev)
अणु
	वापस dev->netdev_ops == &mlxsw_sp_port_netdev_ops;
पूर्ण

अटल पूर्णांक mlxsw_sp_lower_dev_walk(काष्ठा net_device *lower_dev,
				   काष्ठा netdev_nested_priv *priv)
अणु
	पूर्णांक ret = 0;

	अगर (mlxsw_sp_port_dev_check(lower_dev)) अणु
		priv->data = (व्योम *)netdev_priv(lower_dev);
		ret = 1;
	पूर्ण

	वापस ret;
पूर्ण

काष्ठा mlxsw_sp_port *mlxsw_sp_port_dev_lower_find(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_nested_priv priv = अणु
		.data = शून्य,
	पूर्ण;

	अगर (mlxsw_sp_port_dev_check(dev))
		वापस netdev_priv(dev);

	netdev_walk_all_lower_dev(dev, mlxsw_sp_lower_dev_walk, &priv);

	वापस (काष्ठा mlxsw_sp_port *)priv.data;
पूर्ण

काष्ठा mlxsw_sp *mlxsw_sp_lower_get(काष्ठा net_device *dev)
अणु
	काष्ठा mlxsw_sp_port *mlxsw_sp_port;

	mlxsw_sp_port = mlxsw_sp_port_dev_lower_find(dev);
	वापस mlxsw_sp_port ? mlxsw_sp_port->mlxsw_sp : शून्य;
पूर्ण

काष्ठा mlxsw_sp_port *mlxsw_sp_port_dev_lower_find_rcu(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_nested_priv priv = अणु
		.data = शून्य,
	पूर्ण;

	अगर (mlxsw_sp_port_dev_check(dev))
		वापस netdev_priv(dev);

	netdev_walk_all_lower_dev_rcu(dev, mlxsw_sp_lower_dev_walk,
				      &priv);

	वापस (काष्ठा mlxsw_sp_port *)priv.data;
पूर्ण

काष्ठा mlxsw_sp_port *mlxsw_sp_port_lower_dev_hold(काष्ठा net_device *dev)
अणु
	काष्ठा mlxsw_sp_port *mlxsw_sp_port;

	rcu_पढ़ो_lock();
	mlxsw_sp_port = mlxsw_sp_port_dev_lower_find_rcu(dev);
	अगर (mlxsw_sp_port)
		dev_hold(mlxsw_sp_port->dev);
	rcu_पढ़ो_unlock();
	वापस mlxsw_sp_port;
पूर्ण

व्योम mlxsw_sp_port_dev_put(काष्ठा mlxsw_sp_port *mlxsw_sp_port)
अणु
	dev_put(mlxsw_sp_port->dev);
पूर्ण

अटल व्योम
mlxsw_sp_port_lag_uppers_cleanup(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				 काष्ठा net_device *lag_dev)
अणु
	काष्ठा net_device *br_dev = netdev_master_upper_dev_get(lag_dev);
	काष्ठा net_device *upper_dev;
	काष्ठा list_head *iter;

	अगर (netअगर_is_bridge_port(lag_dev))
		mlxsw_sp_port_bridge_leave(mlxsw_sp_port, lag_dev, br_dev);

	netdev_क्रम_each_upper_dev_rcu(lag_dev, upper_dev, iter) अणु
		अगर (!netअगर_is_bridge_port(upper_dev))
			जारी;
		br_dev = netdev_master_upper_dev_get(upper_dev);
		mlxsw_sp_port_bridge_leave(mlxsw_sp_port, upper_dev, br_dev);
	पूर्ण
पूर्ण

अटल पूर्णांक mlxsw_sp_lag_create(काष्ठा mlxsw_sp *mlxsw_sp, u16 lag_id)
अणु
	अक्षर sldr_pl[MLXSW_REG_SLDR_LEN];

	mlxsw_reg_sldr_lag_create_pack(sldr_pl, lag_id);
	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(sldr), sldr_pl);
पूर्ण

अटल पूर्णांक mlxsw_sp_lag_destroy(काष्ठा mlxsw_sp *mlxsw_sp, u16 lag_id)
अणु
	अक्षर sldr_pl[MLXSW_REG_SLDR_LEN];

	mlxsw_reg_sldr_lag_destroy_pack(sldr_pl, lag_id);
	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(sldr), sldr_pl);
पूर्ण

अटल पूर्णांक mlxsw_sp_lag_col_port_add(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				     u16 lag_id, u8 port_index)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	अक्षर slcor_pl[MLXSW_REG_SLCOR_LEN];

	mlxsw_reg_slcor_port_add_pack(slcor_pl, mlxsw_sp_port->local_port,
				      lag_id, port_index);
	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(slcor), slcor_pl);
पूर्ण

अटल पूर्णांक mlxsw_sp_lag_col_port_हटाओ(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
					u16 lag_id)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	अक्षर slcor_pl[MLXSW_REG_SLCOR_LEN];

	mlxsw_reg_slcor_port_हटाओ_pack(slcor_pl, mlxsw_sp_port->local_port,
					 lag_id);
	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(slcor), slcor_pl);
पूर्ण

अटल पूर्णांक mlxsw_sp_lag_col_port_enable(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
					u16 lag_id)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	अक्षर slcor_pl[MLXSW_REG_SLCOR_LEN];

	mlxsw_reg_slcor_col_enable_pack(slcor_pl, mlxsw_sp_port->local_port,
					lag_id);
	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(slcor), slcor_pl);
पूर्ण

अटल पूर्णांक mlxsw_sp_lag_col_port_disable(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
					 u16 lag_id)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	अक्षर slcor_pl[MLXSW_REG_SLCOR_LEN];

	mlxsw_reg_slcor_col_disable_pack(slcor_pl, mlxsw_sp_port->local_port,
					 lag_id);
	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(slcor), slcor_pl);
पूर्ण

अटल पूर्णांक mlxsw_sp_lag_index_get(काष्ठा mlxsw_sp *mlxsw_sp,
				  काष्ठा net_device *lag_dev,
				  u16 *p_lag_id)
अणु
	काष्ठा mlxsw_sp_upper *lag;
	पूर्णांक मुक्त_lag_id = -1;
	u64 max_lag;
	पूर्णांक i;

	max_lag = MLXSW_CORE_RES_GET(mlxsw_sp->core, MAX_LAG);
	क्रम (i = 0; i < max_lag; i++) अणु
		lag = mlxsw_sp_lag_get(mlxsw_sp, i);
		अगर (lag->ref_count) अणु
			अगर (lag->dev == lag_dev) अणु
				*p_lag_id = i;
				वापस 0;
			पूर्ण
		पूर्ण अन्यथा अगर (मुक्त_lag_id < 0) अणु
			मुक्त_lag_id = i;
		पूर्ण
	पूर्ण
	अगर (मुक्त_lag_id < 0)
		वापस -EBUSY;
	*p_lag_id = मुक्त_lag_id;
	वापस 0;
पूर्ण

अटल bool
mlxsw_sp_master_lag_check(काष्ठा mlxsw_sp *mlxsw_sp,
			  काष्ठा net_device *lag_dev,
			  काष्ठा netdev_lag_upper_info *lag_upper_info,
			  काष्ठा netlink_ext_ack *extack)
अणु
	u16 lag_id;

	अगर (mlxsw_sp_lag_index_get(mlxsw_sp, lag_dev, &lag_id) != 0) अणु
		NL_SET_ERR_MSG_MOD(extack, "Exceeded number of supported LAG devices");
		वापस false;
	पूर्ण
	अगर (lag_upper_info->tx_type != NETDEV_LAG_TX_TYPE_HASH) अणु
		NL_SET_ERR_MSG_MOD(extack, "LAG device using unsupported Tx type");
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल पूर्णांक mlxsw_sp_port_lag_index_get(काष्ठा mlxsw_sp *mlxsw_sp,
				       u16 lag_id, u8 *p_port_index)
अणु
	u64 max_lag_members;
	पूर्णांक i;

	max_lag_members = MLXSW_CORE_RES_GET(mlxsw_sp->core,
					     MAX_LAG_MEMBERS);
	क्रम (i = 0; i < max_lag_members; i++) अणु
		अगर (!mlxsw_sp_port_lagged_get(mlxsw_sp, lag_id, i)) अणु
			*p_port_index = i;
			वापस 0;
		पूर्ण
	पूर्ण
	वापस -EBUSY;
पूर्ण

अटल पूर्णांक mlxsw_sp_port_lag_join(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				  काष्ठा net_device *lag_dev,
				  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	काष्ठा mlxsw_sp_upper *lag;
	u16 lag_id;
	u8 port_index;
	पूर्णांक err;

	err = mlxsw_sp_lag_index_get(mlxsw_sp, lag_dev, &lag_id);
	अगर (err)
		वापस err;
	lag = mlxsw_sp_lag_get(mlxsw_sp, lag_id);
	अगर (!lag->ref_count) अणु
		err = mlxsw_sp_lag_create(mlxsw_sp, lag_id);
		अगर (err)
			वापस err;
		lag->dev = lag_dev;
	पूर्ण

	err = mlxsw_sp_port_lag_index_get(mlxsw_sp, lag_id, &port_index);
	अगर (err)
		वापस err;
	err = mlxsw_sp_lag_col_port_add(mlxsw_sp_port, lag_id, port_index);
	अगर (err)
		जाओ err_col_port_add;

	mlxsw_core_lag_mapping_set(mlxsw_sp->core, lag_id, port_index,
				   mlxsw_sp_port->local_port);
	mlxsw_sp_port->lag_id = lag_id;
	mlxsw_sp_port->lagged = 1;
	lag->ref_count++;

	/* Port is no दीर्घer usable as a router पूर्णांकerface */
	अगर (mlxsw_sp_port->शेष_vlan->fid)
		mlxsw_sp_port_vlan_router_leave(mlxsw_sp_port->शेष_vlan);

	/* Join a router पूर्णांकerface configured on the LAG, अगर exists */
	err = mlxsw_sp_port_vlan_router_join(mlxsw_sp_port->शेष_vlan,
					     lag_dev, extack);
	अगर (err)
		जाओ err_router_join;

	वापस 0;

err_router_join:
	lag->ref_count--;
	mlxsw_sp_port->lagged = 0;
	mlxsw_core_lag_mapping_clear(mlxsw_sp->core, lag_id,
				     mlxsw_sp_port->local_port);
	mlxsw_sp_lag_col_port_हटाओ(mlxsw_sp_port, lag_id);
err_col_port_add:
	अगर (!lag->ref_count)
		mlxsw_sp_lag_destroy(mlxsw_sp, lag_id);
	वापस err;
पूर्ण

अटल व्योम mlxsw_sp_port_lag_leave(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				    काष्ठा net_device *lag_dev)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	u16 lag_id = mlxsw_sp_port->lag_id;
	काष्ठा mlxsw_sp_upper *lag;

	अगर (!mlxsw_sp_port->lagged)
		वापस;
	lag = mlxsw_sp_lag_get(mlxsw_sp, lag_id);
	WARN_ON(lag->ref_count == 0);

	mlxsw_sp_lag_col_port_हटाओ(mlxsw_sp_port, lag_id);

	/* Any VLANs configured on the port are no दीर्घer valid */
	mlxsw_sp_port_vlan_flush(mlxsw_sp_port, false);
	mlxsw_sp_port_vlan_cleanup(mlxsw_sp_port->शेष_vlan);
	/* Make the LAG and its directly linked uppers leave bridges they
	 * are memeber in
	 */
	mlxsw_sp_port_lag_uppers_cleanup(mlxsw_sp_port, lag_dev);

	अगर (lag->ref_count == 1)
		mlxsw_sp_lag_destroy(mlxsw_sp, lag_id);

	mlxsw_core_lag_mapping_clear(mlxsw_sp->core, lag_id,
				     mlxsw_sp_port->local_port);
	mlxsw_sp_port->lagged = 0;
	lag->ref_count--;

	/* Make sure untagged frames are allowed to ingress */
	mlxsw_sp_port_pvid_set(mlxsw_sp_port, MLXSW_SP_DEFAULT_VID,
			       ETH_P_8021Q);
पूर्ण

अटल पूर्णांक mlxsw_sp_lag_dist_port_add(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				      u16 lag_id)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	अक्षर sldr_pl[MLXSW_REG_SLDR_LEN];

	mlxsw_reg_sldr_lag_add_port_pack(sldr_pl, lag_id,
					 mlxsw_sp_port->local_port);
	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(sldr), sldr_pl);
पूर्ण

अटल पूर्णांक mlxsw_sp_lag_dist_port_हटाओ(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
					 u16 lag_id)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	अक्षर sldr_pl[MLXSW_REG_SLDR_LEN];

	mlxsw_reg_sldr_lag_हटाओ_port_pack(sldr_pl, lag_id,
					    mlxsw_sp_port->local_port);
	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(sldr), sldr_pl);
पूर्ण

अटल पूर्णांक
mlxsw_sp_port_lag_col_dist_enable(काष्ठा mlxsw_sp_port *mlxsw_sp_port)
अणु
	पूर्णांक err;

	err = mlxsw_sp_lag_col_port_enable(mlxsw_sp_port,
					   mlxsw_sp_port->lag_id);
	अगर (err)
		वापस err;

	err = mlxsw_sp_lag_dist_port_add(mlxsw_sp_port, mlxsw_sp_port->lag_id);
	अगर (err)
		जाओ err_dist_port_add;

	वापस 0;

err_dist_port_add:
	mlxsw_sp_lag_col_port_disable(mlxsw_sp_port, mlxsw_sp_port->lag_id);
	वापस err;
पूर्ण

अटल पूर्णांक
mlxsw_sp_port_lag_col_dist_disable(काष्ठा mlxsw_sp_port *mlxsw_sp_port)
अणु
	पूर्णांक err;

	err = mlxsw_sp_lag_dist_port_हटाओ(mlxsw_sp_port,
					    mlxsw_sp_port->lag_id);
	अगर (err)
		वापस err;

	err = mlxsw_sp_lag_col_port_disable(mlxsw_sp_port,
					    mlxsw_sp_port->lag_id);
	अगर (err)
		जाओ err_col_port_disable;

	वापस 0;

err_col_port_disable:
	mlxsw_sp_lag_dist_port_add(mlxsw_sp_port, mlxsw_sp_port->lag_id);
	वापस err;
पूर्ण

अटल पूर्णांक mlxsw_sp_port_lag_changed(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				     काष्ठा netdev_lag_lower_state_info *info)
अणु
	अगर (info->tx_enabled)
		वापस mlxsw_sp_port_lag_col_dist_enable(mlxsw_sp_port);
	अन्यथा
		वापस mlxsw_sp_port_lag_col_dist_disable(mlxsw_sp_port);
पूर्ण

अटल पूर्णांक mlxsw_sp_port_stp_set(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				 bool enable)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	क्रमागत mlxsw_reg_spms_state spms_state;
	अक्षर *spms_pl;
	u16 vid;
	पूर्णांक err;

	spms_state = enable ? MLXSW_REG_SPMS_STATE_FORWARDING :
			      MLXSW_REG_SPMS_STATE_DISCARDING;

	spms_pl = kदो_स्मृति(MLXSW_REG_SPMS_LEN, GFP_KERNEL);
	अगर (!spms_pl)
		वापस -ENOMEM;
	mlxsw_reg_spms_pack(spms_pl, mlxsw_sp_port->local_port);

	क्रम (vid = 0; vid < VLAN_N_VID; vid++)
		mlxsw_reg_spms_vid_pack(spms_pl, vid, spms_state);

	err = mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(spms), spms_pl);
	kमुक्त(spms_pl);
	वापस err;
पूर्ण

अटल पूर्णांक mlxsw_sp_port_ovs_join(काष्ठा mlxsw_sp_port *mlxsw_sp_port)
अणु
	u16 vid = 1;
	पूर्णांक err;

	err = mlxsw_sp_port_vp_mode_set(mlxsw_sp_port, true);
	अगर (err)
		वापस err;
	err = mlxsw_sp_port_stp_set(mlxsw_sp_port, true);
	अगर (err)
		जाओ err_port_stp_set;
	err = mlxsw_sp_port_vlan_set(mlxsw_sp_port, 1, VLAN_N_VID - 2,
				     true, false);
	अगर (err)
		जाओ err_port_vlan_set;

	क्रम (; vid <= VLAN_N_VID - 1; vid++) अणु
		err = mlxsw_sp_port_vid_learning_set(mlxsw_sp_port,
						     vid, false);
		अगर (err)
			जाओ err_vid_learning_set;
	पूर्ण

	वापस 0;

err_vid_learning_set:
	क्रम (vid--; vid >= 1; vid--)
		mlxsw_sp_port_vid_learning_set(mlxsw_sp_port, vid, true);
err_port_vlan_set:
	mlxsw_sp_port_stp_set(mlxsw_sp_port, false);
err_port_stp_set:
	mlxsw_sp_port_vp_mode_set(mlxsw_sp_port, false);
	वापस err;
पूर्ण

अटल व्योम mlxsw_sp_port_ovs_leave(काष्ठा mlxsw_sp_port *mlxsw_sp_port)
अणु
	u16 vid;

	क्रम (vid = VLAN_N_VID - 1; vid >= 1; vid--)
		mlxsw_sp_port_vid_learning_set(mlxsw_sp_port,
					       vid, true);

	mlxsw_sp_port_vlan_set(mlxsw_sp_port, 1, VLAN_N_VID - 2,
			       false, false);
	mlxsw_sp_port_stp_set(mlxsw_sp_port, false);
	mlxsw_sp_port_vp_mode_set(mlxsw_sp_port, false);
पूर्ण

अटल bool mlxsw_sp_bridge_has_multiple_vxlans(काष्ठा net_device *br_dev)
अणु
	अचिन्हित पूर्णांक num_vxlans = 0;
	काष्ठा net_device *dev;
	काष्ठा list_head *iter;

	netdev_क्रम_each_lower_dev(br_dev, dev, iter) अणु
		अगर (netअगर_is_vxlan(dev))
			num_vxlans++;
	पूर्ण

	वापस num_vxlans > 1;
पूर्ण

अटल bool mlxsw_sp_bridge_vxlan_vlan_is_valid(काष्ठा net_device *br_dev)
अणु
	DECLARE_BITMAP(vlans, VLAN_N_VID) = अणु0पूर्ण;
	काष्ठा net_device *dev;
	काष्ठा list_head *iter;

	netdev_क्रम_each_lower_dev(br_dev, dev, iter) अणु
		u16 pvid;
		पूर्णांक err;

		अगर (!netअगर_is_vxlan(dev))
			जारी;

		err = mlxsw_sp_vxlan_mapped_vid(dev, &pvid);
		अगर (err || !pvid)
			जारी;

		अगर (test_and_set_bit(pvid, vlans))
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल bool mlxsw_sp_bridge_vxlan_is_valid(काष्ठा net_device *br_dev,
					   काष्ठा netlink_ext_ack *extack)
अणु
	अगर (br_multicast_enabled(br_dev)) अणु
		NL_SET_ERR_MSG_MOD(extack, "Multicast can not be enabled on a bridge with a VxLAN device");
		वापस false;
	पूर्ण

	अगर (!br_vlan_enabled(br_dev) &&
	    mlxsw_sp_bridge_has_multiple_vxlans(br_dev)) अणु
		NL_SET_ERR_MSG_MOD(extack, "Multiple VxLAN devices are not supported in a VLAN-unaware bridge");
		वापस false;
	पूर्ण

	अगर (br_vlan_enabled(br_dev) &&
	    !mlxsw_sp_bridge_vxlan_vlan_is_valid(br_dev)) अणु
		NL_SET_ERR_MSG_MOD(extack, "Multiple VxLAN devices cannot have the same VLAN as PVID and egress untagged");
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक mlxsw_sp_netdevice_port_upper_event(काष्ठा net_device *lower_dev,
					       काष्ठा net_device *dev,
					       अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा netdev_notअगरier_changeupper_info *info;
	काष्ठा mlxsw_sp_port *mlxsw_sp_port;
	काष्ठा netlink_ext_ack *extack;
	काष्ठा net_device *upper_dev;
	काष्ठा mlxsw_sp *mlxsw_sp;
	पूर्णांक err = 0;
	u16 proto;

	mlxsw_sp_port = netdev_priv(dev);
	mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	info = ptr;
	extack = netdev_notअगरier_info_to_extack(&info->info);

	चयन (event) अणु
	हाल NETDEV_PRECHANGEUPPER:
		upper_dev = info->upper_dev;
		अगर (!is_vlan_dev(upper_dev) &&
		    !netअगर_is_lag_master(upper_dev) &&
		    !netअगर_is_bridge_master(upper_dev) &&
		    !netअगर_is_ovs_master(upper_dev) &&
		    !netअगर_is_macvlan(upper_dev)) अणु
			NL_SET_ERR_MSG_MOD(extack, "Unknown upper device type");
			वापस -EINVAL;
		पूर्ण
		अगर (!info->linking)
			अवरोध;
		अगर (netअगर_is_bridge_master(upper_dev) &&
		    !mlxsw_sp_bridge_device_is_offloaded(mlxsw_sp, upper_dev) &&
		    mlxsw_sp_bridge_has_vxlan(upper_dev) &&
		    !mlxsw_sp_bridge_vxlan_is_valid(upper_dev, extack))
			वापस -EOPNOTSUPP;
		अगर (netdev_has_any_upper_dev(upper_dev) &&
		    (!netअगर_is_bridge_master(upper_dev) ||
		     !mlxsw_sp_bridge_device_is_offloaded(mlxsw_sp,
							  upper_dev))) अणु
			NL_SET_ERR_MSG_MOD(extack, "Enslaving a port to a device that already has an upper device is not supported");
			वापस -EINVAL;
		पूर्ण
		अगर (netअगर_is_lag_master(upper_dev) &&
		    !mlxsw_sp_master_lag_check(mlxsw_sp, upper_dev,
					       info->upper_info, extack))
			वापस -EINVAL;
		अगर (netअगर_is_lag_master(upper_dev) && vlan_uses_dev(dev)) अणु
			NL_SET_ERR_MSG_MOD(extack, "Master device is a LAG master and this device has a VLAN");
			वापस -EINVAL;
		पूर्ण
		अगर (netअगर_is_lag_port(dev) && is_vlan_dev(upper_dev) &&
		    !netअगर_is_lag_master(vlan_dev_real_dev(upper_dev))) अणु
			NL_SET_ERR_MSG_MOD(extack, "Can not put a VLAN on a LAG port");
			वापस -EINVAL;
		पूर्ण
		अगर (netअगर_is_macvlan(upper_dev) &&
		    !mlxsw_sp_rअगर_exists(mlxsw_sp, lower_dev)) अणु
			NL_SET_ERR_MSG_MOD(extack, "macvlan is only supported on top of router interfaces");
			वापस -EOPNOTSUPP;
		पूर्ण
		अगर (netअगर_is_ovs_master(upper_dev) && vlan_uses_dev(dev)) अणु
			NL_SET_ERR_MSG_MOD(extack, "Master device is an OVS master and this device has a VLAN");
			वापस -EINVAL;
		पूर्ण
		अगर (netअगर_is_ovs_port(dev) && is_vlan_dev(upper_dev)) अणु
			NL_SET_ERR_MSG_MOD(extack, "Can not put a VLAN on an OVS port");
			वापस -EINVAL;
		पूर्ण
		अगर (netअगर_is_bridge_master(upper_dev)) अणु
			br_vlan_get_proto(upper_dev, &proto);
			अगर (br_vlan_enabled(upper_dev) &&
			    proto != ETH_P_8021Q && proto != ETH_P_8021AD) अणु
				NL_SET_ERR_MSG_MOD(extack, "Enslaving a port to a bridge with unknown VLAN protocol is not supported");
				वापस -EOPNOTSUPP;
			पूर्ण
			अगर (vlan_uses_dev(lower_dev) &&
			    br_vlan_enabled(upper_dev) &&
			    proto == ETH_P_8021AD) अणु
				NL_SET_ERR_MSG_MOD(extack, "Enslaving a port that already has a VLAN upper to an 802.1ad bridge is not supported");
				वापस -EOPNOTSUPP;
			पूर्ण
		पूर्ण
		अगर (netअगर_is_bridge_port(lower_dev) && is_vlan_dev(upper_dev)) अणु
			काष्ठा net_device *br_dev = netdev_master_upper_dev_get(lower_dev);

			अगर (br_vlan_enabled(br_dev)) अणु
				br_vlan_get_proto(br_dev, &proto);
				अगर (proto == ETH_P_8021AD) अणु
					NL_SET_ERR_MSG_MOD(extack, "VLAN uppers are not supported on a port enslaved to an 802.1ad bridge");
					वापस -EOPNOTSUPP;
				पूर्ण
			पूर्ण
		पूर्ण
		अगर (is_vlan_dev(upper_dev) &&
		    ntohs(vlan_dev_vlan_proto(upper_dev)) != ETH_P_8021Q) अणु
			NL_SET_ERR_MSG_MOD(extack, "VLAN uppers are only supported with 802.1q VLAN protocol");
			वापस -EOPNOTSUPP;
		पूर्ण
		अवरोध;
	हाल NETDEV_CHANGEUPPER:
		upper_dev = info->upper_dev;
		अगर (netअगर_is_bridge_master(upper_dev)) अणु
			अगर (info->linking)
				err = mlxsw_sp_port_bridge_join(mlxsw_sp_port,
								lower_dev,
								upper_dev,
								extack);
			अन्यथा
				mlxsw_sp_port_bridge_leave(mlxsw_sp_port,
							   lower_dev,
							   upper_dev);
		पूर्ण अन्यथा अगर (netअगर_is_lag_master(upper_dev)) अणु
			अगर (info->linking) अणु
				err = mlxsw_sp_port_lag_join(mlxsw_sp_port,
							     upper_dev, extack);
			पूर्ण अन्यथा अणु
				mlxsw_sp_port_lag_col_dist_disable(mlxsw_sp_port);
				mlxsw_sp_port_lag_leave(mlxsw_sp_port,
							upper_dev);
			पूर्ण
		पूर्ण अन्यथा अगर (netअगर_is_ovs_master(upper_dev)) अणु
			अगर (info->linking)
				err = mlxsw_sp_port_ovs_join(mlxsw_sp_port);
			अन्यथा
				mlxsw_sp_port_ovs_leave(mlxsw_sp_port);
		पूर्ण अन्यथा अगर (netअगर_is_macvlan(upper_dev)) अणु
			अगर (!info->linking)
				mlxsw_sp_rअगर_macvlan_del(mlxsw_sp, upper_dev);
		पूर्ण अन्यथा अगर (is_vlan_dev(upper_dev)) अणु
			काष्ठा net_device *br_dev;

			अगर (!netअगर_is_bridge_port(upper_dev))
				अवरोध;
			अगर (info->linking)
				अवरोध;
			br_dev = netdev_master_upper_dev_get(upper_dev);
			mlxsw_sp_port_bridge_leave(mlxsw_sp_port, upper_dev,
						   br_dev);
		पूर्ण
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक mlxsw_sp_netdevice_port_lower_event(काष्ठा net_device *dev,
					       अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा netdev_notअगरier_changelowerstate_info *info;
	काष्ठा mlxsw_sp_port *mlxsw_sp_port;
	पूर्णांक err;

	mlxsw_sp_port = netdev_priv(dev);
	info = ptr;

	चयन (event) अणु
	हाल NETDEV_CHANGELOWERSTATE:
		अगर (netअगर_is_lag_port(dev) && mlxsw_sp_port->lagged) अणु
			err = mlxsw_sp_port_lag_changed(mlxsw_sp_port,
							info->lower_state_info);
			अगर (err)
				netdev_err(dev, "Failed to reflect link aggregation lower state change\n");
		पूर्ण
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_sp_netdevice_port_event(काष्ठा net_device *lower_dev,
					 काष्ठा net_device *port_dev,
					 अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	चयन (event) अणु
	हाल NETDEV_PRECHANGEUPPER:
	हाल NETDEV_CHANGEUPPER:
		वापस mlxsw_sp_netdevice_port_upper_event(lower_dev, port_dev,
							   event, ptr);
	हाल NETDEV_CHANGELOWERSTATE:
		वापस mlxsw_sp_netdevice_port_lower_event(port_dev, event,
							   ptr);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_sp_netdevice_lag_event(काष्ठा net_device *lag_dev,
					अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा net_device *dev;
	काष्ठा list_head *iter;
	पूर्णांक ret;

	netdev_क्रम_each_lower_dev(lag_dev, dev, iter) अणु
		अगर (mlxsw_sp_port_dev_check(dev)) अणु
			ret = mlxsw_sp_netdevice_port_event(lag_dev, dev, event,
							    ptr);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_sp_netdevice_port_vlan_event(काष्ठा net_device *vlan_dev,
					      काष्ठा net_device *dev,
					      अचिन्हित दीर्घ event, व्योम *ptr,
					      u16 vid)
अणु
	काष्ठा mlxsw_sp_port *mlxsw_sp_port = netdev_priv(dev);
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	काष्ठा netdev_notअगरier_changeupper_info *info = ptr;
	काष्ठा netlink_ext_ack *extack;
	काष्ठा net_device *upper_dev;
	पूर्णांक err = 0;

	extack = netdev_notअगरier_info_to_extack(&info->info);

	चयन (event) अणु
	हाल NETDEV_PRECHANGEUPPER:
		upper_dev = info->upper_dev;
		अगर (!netअगर_is_bridge_master(upper_dev) &&
		    !netअगर_is_macvlan(upper_dev)) अणु
			NL_SET_ERR_MSG_MOD(extack, "Unknown upper device type");
			वापस -EINVAL;
		पूर्ण
		अगर (!info->linking)
			अवरोध;
		अगर (netअगर_is_bridge_master(upper_dev) &&
		    !mlxsw_sp_bridge_device_is_offloaded(mlxsw_sp, upper_dev) &&
		    mlxsw_sp_bridge_has_vxlan(upper_dev) &&
		    !mlxsw_sp_bridge_vxlan_is_valid(upper_dev, extack))
			वापस -EOPNOTSUPP;
		अगर (netdev_has_any_upper_dev(upper_dev) &&
		    (!netअगर_is_bridge_master(upper_dev) ||
		     !mlxsw_sp_bridge_device_is_offloaded(mlxsw_sp,
							  upper_dev))) अणु
			NL_SET_ERR_MSG_MOD(extack, "Enslaving a port to a device that already has an upper device is not supported");
			वापस -EINVAL;
		पूर्ण
		अगर (netअगर_is_macvlan(upper_dev) &&
		    !mlxsw_sp_rअगर_exists(mlxsw_sp, vlan_dev)) अणु
			NL_SET_ERR_MSG_MOD(extack, "macvlan is only supported on top of router interfaces");
			वापस -EOPNOTSUPP;
		पूर्ण
		अवरोध;
	हाल NETDEV_CHANGEUPPER:
		upper_dev = info->upper_dev;
		अगर (netअगर_is_bridge_master(upper_dev)) अणु
			अगर (info->linking)
				err = mlxsw_sp_port_bridge_join(mlxsw_sp_port,
								vlan_dev,
								upper_dev,
								extack);
			अन्यथा
				mlxsw_sp_port_bridge_leave(mlxsw_sp_port,
							   vlan_dev,
							   upper_dev);
		पूर्ण अन्यथा अगर (netअगर_is_macvlan(upper_dev)) अणु
			अगर (!info->linking)
				mlxsw_sp_rअगर_macvlan_del(mlxsw_sp, upper_dev);
		पूर्ण अन्यथा अणु
			err = -EINVAL;
			WARN_ON(1);
		पूर्ण
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक mlxsw_sp_netdevice_lag_port_vlan_event(काष्ठा net_device *vlan_dev,
						  काष्ठा net_device *lag_dev,
						  अचिन्हित दीर्घ event,
						  व्योम *ptr, u16 vid)
अणु
	काष्ठा net_device *dev;
	काष्ठा list_head *iter;
	पूर्णांक ret;

	netdev_क्रम_each_lower_dev(lag_dev, dev, iter) अणु
		अगर (mlxsw_sp_port_dev_check(dev)) अणु
			ret = mlxsw_sp_netdevice_port_vlan_event(vlan_dev, dev,
								 event, ptr,
								 vid);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_sp_netdevice_bridge_vlan_event(काष्ठा net_device *vlan_dev,
						काष्ठा net_device *br_dev,
						अचिन्हित दीर्घ event, व्योम *ptr,
						u16 vid)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_lower_get(vlan_dev);
	काष्ठा netdev_notअगरier_changeupper_info *info = ptr;
	काष्ठा netlink_ext_ack *extack;
	काष्ठा net_device *upper_dev;

	अगर (!mlxsw_sp)
		वापस 0;

	extack = netdev_notअगरier_info_to_extack(&info->info);

	चयन (event) अणु
	हाल NETDEV_PRECHANGEUPPER:
		upper_dev = info->upper_dev;
		अगर (!netअगर_is_macvlan(upper_dev)) अणु
			NL_SET_ERR_MSG_MOD(extack, "Unknown upper device type");
			वापस -EOPNOTSUPP;
		पूर्ण
		अगर (!info->linking)
			अवरोध;
		अगर (netअगर_is_macvlan(upper_dev) &&
		    !mlxsw_sp_rअगर_exists(mlxsw_sp, vlan_dev)) अणु
			NL_SET_ERR_MSG_MOD(extack, "macvlan is only supported on top of router interfaces");
			वापस -EOPNOTSUPP;
		पूर्ण
		अवरोध;
	हाल NETDEV_CHANGEUPPER:
		upper_dev = info->upper_dev;
		अगर (info->linking)
			अवरोध;
		अगर (netअगर_is_macvlan(upper_dev))
			mlxsw_sp_rअगर_macvlan_del(mlxsw_sp, upper_dev);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_sp_netdevice_vlan_event(काष्ठा net_device *vlan_dev,
					 अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा net_device *real_dev = vlan_dev_real_dev(vlan_dev);
	u16 vid = vlan_dev_vlan_id(vlan_dev);

	अगर (mlxsw_sp_port_dev_check(real_dev))
		वापस mlxsw_sp_netdevice_port_vlan_event(vlan_dev, real_dev,
							  event, ptr, vid);
	अन्यथा अगर (netअगर_is_lag_master(real_dev))
		वापस mlxsw_sp_netdevice_lag_port_vlan_event(vlan_dev,
							      real_dev, event,
							      ptr, vid);
	अन्यथा अगर (netअगर_is_bridge_master(real_dev))
		वापस mlxsw_sp_netdevice_bridge_vlan_event(vlan_dev, real_dev,
							    event, ptr, vid);

	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_sp_netdevice_bridge_event(काष्ठा net_device *br_dev,
					   अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_lower_get(br_dev);
	काष्ठा netdev_notअगरier_changeupper_info *info = ptr;
	काष्ठा netlink_ext_ack *extack;
	काष्ठा net_device *upper_dev;
	u16 proto;

	अगर (!mlxsw_sp)
		वापस 0;

	extack = netdev_notअगरier_info_to_extack(&info->info);

	चयन (event) अणु
	हाल NETDEV_PRECHANGEUPPER:
		upper_dev = info->upper_dev;
		अगर (!is_vlan_dev(upper_dev) && !netअगर_is_macvlan(upper_dev)) अणु
			NL_SET_ERR_MSG_MOD(extack, "Unknown upper device type");
			वापस -EOPNOTSUPP;
		पूर्ण
		अगर (!info->linking)
			अवरोध;
		अगर (br_vlan_enabled(br_dev)) अणु
			br_vlan_get_proto(br_dev, &proto);
			अगर (proto == ETH_P_8021AD) अणु
				NL_SET_ERR_MSG_MOD(extack, "Upper devices are not supported on top of an 802.1ad bridge");
				वापस -EOPNOTSUPP;
			पूर्ण
		पूर्ण
		अगर (is_vlan_dev(upper_dev) &&
		    ntohs(vlan_dev_vlan_proto(upper_dev)) != ETH_P_8021Q) अणु
			NL_SET_ERR_MSG_MOD(extack, "VLAN uppers are only supported with 802.1q VLAN protocol");
			वापस -EOPNOTSUPP;
		पूर्ण
		अगर (netअगर_is_macvlan(upper_dev) &&
		    !mlxsw_sp_rअगर_exists(mlxsw_sp, br_dev)) अणु
			NL_SET_ERR_MSG_MOD(extack, "macvlan is only supported on top of router interfaces");
			वापस -EOPNOTSUPP;
		पूर्ण
		अवरोध;
	हाल NETDEV_CHANGEUPPER:
		upper_dev = info->upper_dev;
		अगर (info->linking)
			अवरोध;
		अगर (is_vlan_dev(upper_dev))
			mlxsw_sp_rअगर_destroy_by_dev(mlxsw_sp, upper_dev);
		अगर (netअगर_is_macvlan(upper_dev))
			mlxsw_sp_rअगर_macvlan_del(mlxsw_sp, upper_dev);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_sp_netdevice_macvlan_event(काष्ठा net_device *macvlan_dev,
					    अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_lower_get(macvlan_dev);
	काष्ठा netdev_notअगरier_changeupper_info *info = ptr;
	काष्ठा netlink_ext_ack *extack;

	अगर (!mlxsw_sp || event != NETDEV_PRECHANGEUPPER)
		वापस 0;

	extack = netdev_notअगरier_info_to_extack(&info->info);

	/* VRF enslavement is handled in mlxsw_sp_netdevice_vrf_event() */
	NL_SET_ERR_MSG_MOD(extack, "Unknown upper device type");

	वापस -EOPNOTSUPP;
पूर्ण

अटल bool mlxsw_sp_is_vrf_event(अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा netdev_notअगरier_changeupper_info *info = ptr;

	अगर (event != NETDEV_PRECHANGEUPPER && event != NETDEV_CHANGEUPPER)
		वापस false;
	वापस netअगर_is_l3_master(info->upper_dev);
पूर्ण

अटल पूर्णांक mlxsw_sp_netdevice_vxlan_event(काष्ठा mlxsw_sp *mlxsw_sp,
					  काष्ठा net_device *dev,
					  अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा netdev_notअगरier_changeupper_info *cu_info;
	काष्ठा netdev_notअगरier_info *info = ptr;
	काष्ठा netlink_ext_ack *extack;
	काष्ठा net_device *upper_dev;

	extack = netdev_notअगरier_info_to_extack(info);

	चयन (event) अणु
	हाल NETDEV_CHANGEUPPER:
		cu_info = container_of(info,
				       काष्ठा netdev_notअगरier_changeupper_info,
				       info);
		upper_dev = cu_info->upper_dev;
		अगर (!netअगर_is_bridge_master(upper_dev))
			वापस 0;
		अगर (!mlxsw_sp_lower_get(upper_dev))
			वापस 0;
		अगर (!mlxsw_sp_bridge_vxlan_is_valid(upper_dev, extack))
			वापस -EOPNOTSUPP;
		अगर (cu_info->linking) अणु
			अगर (!netअगर_running(dev))
				वापस 0;
			/* When the bridge is VLAN-aware, the VNI of the VxLAN
			 * device needs to be mapped to a VLAN, but at this
			 * poपूर्णांक no VLANs are configured on the VxLAN device
			 */
			अगर (br_vlan_enabled(upper_dev))
				वापस 0;
			वापस mlxsw_sp_bridge_vxlan_join(mlxsw_sp, upper_dev,
							  dev, 0, extack);
		पूर्ण अन्यथा अणु
			/* VLANs were alपढ़ोy flushed, which triggered the
			 * necessary cleanup
			 */
			अगर (br_vlan_enabled(upper_dev))
				वापस 0;
			mlxsw_sp_bridge_vxlan_leave(mlxsw_sp, dev);
		पूर्ण
		अवरोध;
	हाल NETDEV_PRE_UP:
		upper_dev = netdev_master_upper_dev_get(dev);
		अगर (!upper_dev)
			वापस 0;
		अगर (!netअगर_is_bridge_master(upper_dev))
			वापस 0;
		अगर (!mlxsw_sp_lower_get(upper_dev))
			वापस 0;
		वापस mlxsw_sp_bridge_vxlan_join(mlxsw_sp, upper_dev, dev, 0,
						  extack);
	हाल NETDEV_DOWN:
		upper_dev = netdev_master_upper_dev_get(dev);
		अगर (!upper_dev)
			वापस 0;
		अगर (!netअगर_is_bridge_master(upper_dev))
			वापस 0;
		अगर (!mlxsw_sp_lower_get(upper_dev))
			वापस 0;
		mlxsw_sp_bridge_vxlan_leave(mlxsw_sp, dev);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_sp_netdevice_event(काष्ठा notअगरier_block *nb,
				    अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा net_device *dev = netdev_notअगरier_info_to_dev(ptr);
	काष्ठा mlxsw_sp_span_entry *span_entry;
	काष्ठा mlxsw_sp *mlxsw_sp;
	पूर्णांक err = 0;

	mlxsw_sp = container_of(nb, काष्ठा mlxsw_sp, netdevice_nb);
	अगर (event == NETDEV_UNREGISTER) अणु
		span_entry = mlxsw_sp_span_entry_find_by_port(mlxsw_sp, dev);
		अगर (span_entry)
			mlxsw_sp_span_entry_invalidate(mlxsw_sp, span_entry);
	पूर्ण
	mlxsw_sp_span_respin(mlxsw_sp);

	अगर (netअगर_is_vxlan(dev))
		err = mlxsw_sp_netdevice_vxlan_event(mlxsw_sp, dev, event, ptr);
	अगर (mlxsw_sp_netdev_is_ipip_ol(mlxsw_sp, dev))
		err = mlxsw_sp_netdevice_ipip_ol_event(mlxsw_sp, dev,
						       event, ptr);
	अन्यथा अगर (mlxsw_sp_netdev_is_ipip_ul(mlxsw_sp, dev))
		err = mlxsw_sp_netdevice_ipip_ul_event(mlxsw_sp, dev,
						       event, ptr);
	अन्यथा अगर (event == NETDEV_PRE_CHANGEADDR ||
		 event == NETDEV_CHANGEADDR ||
		 event == NETDEV_CHANGEMTU)
		err = mlxsw_sp_netdevice_router_port_event(dev, event, ptr);
	अन्यथा अगर (mlxsw_sp_is_vrf_event(event, ptr))
		err = mlxsw_sp_netdevice_vrf_event(dev, event, ptr);
	अन्यथा अगर (mlxsw_sp_port_dev_check(dev))
		err = mlxsw_sp_netdevice_port_event(dev, dev, event, ptr);
	अन्यथा अगर (netअगर_is_lag_master(dev))
		err = mlxsw_sp_netdevice_lag_event(dev, event, ptr);
	अन्यथा अगर (is_vlan_dev(dev))
		err = mlxsw_sp_netdevice_vlan_event(dev, event, ptr);
	अन्यथा अगर (netअगर_is_bridge_master(dev))
		err = mlxsw_sp_netdevice_bridge_event(dev, event, ptr);
	अन्यथा अगर (netअगर_is_macvlan(dev))
		err = mlxsw_sp_netdevice_macvlan_event(dev, event, ptr);

	वापस notअगरier_from_त्रुटि_सं(err);
पूर्ण

अटल काष्ठा notअगरier_block mlxsw_sp_inetaddr_valid_nb __पढ़ो_mostly = अणु
	.notअगरier_call = mlxsw_sp_inetaddr_valid_event,
पूर्ण;

अटल काष्ठा notअगरier_block mlxsw_sp_inet6addr_valid_nb __पढ़ो_mostly = अणु
	.notअगरier_call = mlxsw_sp_inet6addr_valid_event,
पूर्ण;

अटल स्थिर काष्ठा pci_device_id mlxsw_sp1_pci_id_table[] = अणु
	अणुPCI_VDEVICE(MELLANOX, PCI_DEVICE_ID_MELLANOX_SPECTRUM), 0पूर्ण,
	अणु0, पूर्ण,
पूर्ण;

अटल काष्ठा pci_driver mlxsw_sp1_pci_driver = अणु
	.name = mlxsw_sp1_driver_name,
	.id_table = mlxsw_sp1_pci_id_table,
पूर्ण;

अटल स्थिर काष्ठा pci_device_id mlxsw_sp2_pci_id_table[] = अणु
	अणुPCI_VDEVICE(MELLANOX, PCI_DEVICE_ID_MELLANOX_SPECTRUM2), 0पूर्ण,
	अणु0, पूर्ण,
पूर्ण;

अटल काष्ठा pci_driver mlxsw_sp2_pci_driver = अणु
	.name = mlxsw_sp2_driver_name,
	.id_table = mlxsw_sp2_pci_id_table,
पूर्ण;

अटल स्थिर काष्ठा pci_device_id mlxsw_sp3_pci_id_table[] = अणु
	अणुPCI_VDEVICE(MELLANOX, PCI_DEVICE_ID_MELLANOX_SPECTRUM3), 0पूर्ण,
	अणु0, पूर्ण,
पूर्ण;

अटल काष्ठा pci_driver mlxsw_sp3_pci_driver = अणु
	.name = mlxsw_sp3_driver_name,
	.id_table = mlxsw_sp3_pci_id_table,
पूर्ण;

अटल पूर्णांक __init mlxsw_sp_module_init(व्योम)
अणु
	पूर्णांक err;

	रेजिस्टर_inetaddr_validator_notअगरier(&mlxsw_sp_inetaddr_valid_nb);
	रेजिस्टर_inet6addr_validator_notअगरier(&mlxsw_sp_inet6addr_valid_nb);

	err = mlxsw_core_driver_रेजिस्टर(&mlxsw_sp1_driver);
	अगर (err)
		जाओ err_sp1_core_driver_रेजिस्टर;

	err = mlxsw_core_driver_रेजिस्टर(&mlxsw_sp2_driver);
	अगर (err)
		जाओ err_sp2_core_driver_रेजिस्टर;

	err = mlxsw_core_driver_रेजिस्टर(&mlxsw_sp3_driver);
	अगर (err)
		जाओ err_sp3_core_driver_रेजिस्टर;

	err = mlxsw_pci_driver_रेजिस्टर(&mlxsw_sp1_pci_driver);
	अगर (err)
		जाओ err_sp1_pci_driver_रेजिस्टर;

	err = mlxsw_pci_driver_रेजिस्टर(&mlxsw_sp2_pci_driver);
	अगर (err)
		जाओ err_sp2_pci_driver_रेजिस्टर;

	err = mlxsw_pci_driver_रेजिस्टर(&mlxsw_sp3_pci_driver);
	अगर (err)
		जाओ err_sp3_pci_driver_रेजिस्टर;

	वापस 0;

err_sp3_pci_driver_रेजिस्टर:
	mlxsw_pci_driver_unरेजिस्टर(&mlxsw_sp2_pci_driver);
err_sp2_pci_driver_रेजिस्टर:
	mlxsw_pci_driver_unरेजिस्टर(&mlxsw_sp1_pci_driver);
err_sp1_pci_driver_रेजिस्टर:
	mlxsw_core_driver_unरेजिस्टर(&mlxsw_sp3_driver);
err_sp3_core_driver_रेजिस्टर:
	mlxsw_core_driver_unरेजिस्टर(&mlxsw_sp2_driver);
err_sp2_core_driver_रेजिस्टर:
	mlxsw_core_driver_unरेजिस्टर(&mlxsw_sp1_driver);
err_sp1_core_driver_रेजिस्टर:
	unरेजिस्टर_inet6addr_validator_notअगरier(&mlxsw_sp_inet6addr_valid_nb);
	unरेजिस्टर_inetaddr_validator_notअगरier(&mlxsw_sp_inetaddr_valid_nb);
	वापस err;
पूर्ण

अटल व्योम __निकास mlxsw_sp_module_निकास(व्योम)
अणु
	mlxsw_pci_driver_unरेजिस्टर(&mlxsw_sp3_pci_driver);
	mlxsw_pci_driver_unरेजिस्टर(&mlxsw_sp2_pci_driver);
	mlxsw_pci_driver_unरेजिस्टर(&mlxsw_sp1_pci_driver);
	mlxsw_core_driver_unरेजिस्टर(&mlxsw_sp3_driver);
	mlxsw_core_driver_unरेजिस्टर(&mlxsw_sp2_driver);
	mlxsw_core_driver_unरेजिस्टर(&mlxsw_sp1_driver);
	unरेजिस्टर_inet6addr_validator_notअगरier(&mlxsw_sp_inet6addr_valid_nb);
	unरेजिस्टर_inetaddr_validator_notअगरier(&mlxsw_sp_inetaddr_valid_nb);
पूर्ण

module_init(mlxsw_sp_module_init);
module_निकास(mlxsw_sp_module_निकास);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Jiri Pirko <jiri@mellanox.com>");
MODULE_DESCRIPTION("Mellanox Spectrum driver");
MODULE_DEVICE_TABLE(pci, mlxsw_sp1_pci_id_table);
MODULE_DEVICE_TABLE(pci, mlxsw_sp2_pci_id_table);
MODULE_DEVICE_TABLE(pci, mlxsw_sp3_pci_id_table);
MODULE_FIRMWARE(MLXSW_SP1_FW_खाताNAME);
MODULE_FIRMWARE(MLXSW_SP2_FW_खाताNAME);
MODULE_FIRMWARE(MLXSW_SP3_FW_खाताNAME);
