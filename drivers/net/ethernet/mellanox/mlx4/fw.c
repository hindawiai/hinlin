<शैली गुरु>
/*
 * Copyright (c) 2004, 2005 Topspin Communications.  All rights reserved.
 * Copyright (c) 2005, 2006, 2007, 2008 Mellanox Technologies. All rights reserved.
 * Copyright (c) 2005, 2006, 2007 Cisco Systems, Inc.  All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#समावेश <linux/etherdevice.h>
#समावेश <linux/mlx4/cmd.h>
#समावेश <linux/module.h>
#समावेश <linux/cache.h>
#समावेश <linux/kernel.h>
#समावेश <uapi/rdma/mlx4-abi.h>

#समावेश "fw.h"
#समावेश "icm.h"

क्रमागत अणु
	MLX4_COMMAND_INTERFACE_MIN_REV		= 2,
	MLX4_COMMAND_INTERFACE_MAX_REV		= 3,
	MLX4_COMMAND_INTERFACE_NEW_PORT_CMDS	= 3,
पूर्ण;

बाह्य व्योम __buggy_use_of_MLX4_GET(व्योम);
बाह्य व्योम __buggy_use_of_MLX4_PUT(व्योम);

अटल bool enable_qos;
module_param(enable_qos, bool, 0444);
MODULE_PARM_DESC(enable_qos, "Enable Enhanced QoS support (default: off)");

#घोषणा MLX4_GET(dest, source, offset)				      \
	करो अणु							      \
		व्योम *__p = (अक्षर *) (source) + (offset);	      \
		__be64 val;                                           \
		चयन (माप(dest)) अणु				      \
		हाल 1: (dest) = *(u8 *) __p;	    अवरोध;	      \
		हाल 2: (dest) = be16_to_cpup(__p); अवरोध;	      \
		हाल 4: (dest) = be32_to_cpup(__p); अवरोध;	      \
		हाल 8: val = get_unaligned((__be64 *)__p);           \
			(dest) = be64_to_cpu(val);  अवरोध;            \
		शेष: __buggy_use_of_MLX4_GET();		      \
		पूर्ण						      \
	पूर्ण जबतक (0)

#घोषणा MLX4_PUT(dest, source, offset)				      \
	करो अणु							      \
		व्योम *__d = ((अक्षर *) (dest) + (offset));	      \
		चयन (माप(source)) अणु			      \
		हाल 1: *(u8 *) __d = (source);		       अवरोध; \
		हाल 2:	*(__be16 *) __d = cpu_to_be16(source); अवरोध; \
		हाल 4:	*(__be32 *) __d = cpu_to_be32(source); अवरोध; \
		हाल 8:	*(__be64 *) __d = cpu_to_be64(source); अवरोध; \
		शेष: __buggy_use_of_MLX4_PUT();		      \
		पूर्ण						      \
	पूर्ण जबतक (0)

अटल व्योम dump_dev_cap_flags(काष्ठा mlx4_dev *dev, u64 flags)
अणु
	अटल स्थिर अक्षर *fname[] = अणु
		[ 0] = "RC transport",
		[ 1] = "UC transport",
		[ 2] = "UD transport",
		[ 3] = "XRC transport",
		[ 6] = "SRQ support",
		[ 7] = "IPoIB checksum offload",
		[ 8] = "P_Key violation counter",
		[ 9] = "Q_Key violation counter",
		[12] = "Dual Port Different Protocol (DPDP) support",
		[15] = "Big LSO headers",
		[16] = "MW support",
		[17] = "APM support",
		[18] = "Atomic ops support",
		[19] = "Raw multicast support",
		[20] = "Address vector port checking support",
		[21] = "UD multicast support",
		[30] = "IBoE support",
		[32] = "Unicast loopback support",
		[34] = "FCS header control",
		[37] = "Wake On LAN (port1) support",
		[38] = "Wake On LAN (port2) support",
		[40] = "UDP RSS support",
		[41] = "Unicast VEP steering support",
		[42] = "Multicast VEP steering support",
		[48] = "Counters support",
		[52] = "RSS IP fragments support",
		[53] = "Port ETS Scheduler support",
		[55] = "Port link type sensing support",
		[59] = "Port management change event support",
		[61] = "64 byte EQE support",
		[62] = "64 byte CQE support",
	पूर्ण;
	पूर्णांक i;

	mlx4_dbg(dev, "DEV_CAP flags:\n");
	क्रम (i = 0; i < ARRAY_SIZE(fname); ++i)
		अगर (fname[i] && (flags & (1LL << i)))
			mlx4_dbg(dev, "    %s\n", fname[i]);
पूर्ण

अटल व्योम dump_dev_cap_flags2(काष्ठा mlx4_dev *dev, u64 flags)
अणु
	अटल स्थिर अक्षर * स्थिर fname[] = अणु
		[0] = "RSS support",
		[1] = "RSS Toeplitz Hash Function support",
		[2] = "RSS XOR Hash Function support",
		[3] = "Device managed flow steering support",
		[4] = "Automatic MAC reassignment support",
		[5] = "Time stamping support",
		[6] = "VST (control vlan insertion/stripping) support",
		[7] = "FSM (MAC anti-spoofing) support",
		[8] = "Dynamic QP updates support",
		[9] = "Device managed flow steering IPoIB support",
		[10] = "TCP/IP offloads/flow-steering for VXLAN support",
		[11] = "MAD DEMUX (Secure-Host) support",
		[12] = "Large cache line (>64B) CQE stride support",
		[13] = "Large cache line (>64B) EQE stride support",
		[14] = "Ethernet protocol control support",
		[15] = "Ethernet Backplane autoneg support",
		[16] = "CONFIG DEV support",
		[17] = "Asymmetric EQs support",
		[18] = "More than 80 VFs support",
		[19] = "Performance optimized for limited rule configuration flow steering support",
		[20] = "Recoverable error events support",
		[21] = "Port Remap support",
		[22] = "QCN support",
		[23] = "QP rate limiting support",
		[24] = "Ethernet Flow control statistics support",
		[25] = "Granular QoS per VF support",
		[26] = "Port ETS Scheduler support",
		[27] = "Port beacon support",
		[28] = "RX-ALL support",
		[29] = "802.1ad offload support",
		[31] = "Modifying loopback source checks using UPDATE_QP support",
		[32] = "Loopback source checks support",
		[33] = "RoCEv2 support",
		[34] = "DMFS Sniffer support (UC & MC)",
		[35] = "Diag counters per port",
		[36] = "QinQ VST mode support",
		[37] = "sl to vl mapping table change event support",
		[38] = "user MAC support",
		[39] = "Report driver version to FW support",
		[40] = "SW CQ initialization support",
	पूर्ण;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(fname); ++i)
		अगर (fname[i] && (flags & (1LL << i)))
			mlx4_dbg(dev, "    %s\n", fname[i]);
पूर्ण

पूर्णांक mlx4_MOD_STAT_CFG(काष्ठा mlx4_dev *dev, काष्ठा mlx4_mod_stat_cfg *cfg)
अणु
	काष्ठा mlx4_cmd_mailbox *mailbox;
	u32 *inbox;
	पूर्णांक err = 0;

#घोषणा MOD_STAT_CFG_IN_SIZE		0x100

#घोषणा MOD_STAT_CFG_PG_SZ_M_OFFSET	0x002
#घोषणा MOD_STAT_CFG_PG_SZ_OFFSET	0x003

	mailbox = mlx4_alloc_cmd_mailbox(dev);
	अगर (IS_ERR(mailbox))
		वापस PTR_ERR(mailbox);
	inbox = mailbox->buf;

	MLX4_PUT(inbox, cfg->log_pg_sz, MOD_STAT_CFG_PG_SZ_OFFSET);
	MLX4_PUT(inbox, cfg->log_pg_sz_m, MOD_STAT_CFG_PG_SZ_M_OFFSET);

	err = mlx4_cmd(dev, mailbox->dma, 0, 0, MLX4_CMD_MOD_STAT_CFG,
			MLX4_CMD_TIME_CLASS_A, MLX4_CMD_NATIVE);

	mlx4_मुक्त_cmd_mailbox(dev, mailbox);
	वापस err;
पूर्ण

पूर्णांक mlx4_QUERY_FUNC(काष्ठा mlx4_dev *dev, काष्ठा mlx4_func *func, पूर्णांक slave)
अणु
	काष्ठा mlx4_cmd_mailbox *mailbox;
	u32 *outbox;
	u8 in_modअगरier;
	u8 field;
	u16 field16;
	पूर्णांक err;

#घोषणा QUERY_FUNC_BUS_OFFSET			0x00
#घोषणा QUERY_FUNC_DEVICE_OFFSET		0x01
#घोषणा QUERY_FUNC_FUNCTION_OFFSET		0x01
#घोषणा QUERY_FUNC_PHYSICAL_FUNCTION_OFFSET	0x03
#घोषणा QUERY_FUNC_RSVD_EQS_OFFSET		0x04
#घोषणा QUERY_FUNC_MAX_EQ_OFFSET		0x06
#घोषणा QUERY_FUNC_RSVD_UARS_OFFSET		0x0b

	mailbox = mlx4_alloc_cmd_mailbox(dev);
	अगर (IS_ERR(mailbox))
		वापस PTR_ERR(mailbox);
	outbox = mailbox->buf;

	in_modअगरier = slave;

	err = mlx4_cmd_box(dev, 0, mailbox->dma, in_modअगरier, 0,
			   MLX4_CMD_QUERY_FUNC,
			   MLX4_CMD_TIME_CLASS_A,
			   MLX4_CMD_NATIVE);
	अगर (err)
		जाओ out;

	MLX4_GET(field, outbox, QUERY_FUNC_BUS_OFFSET);
	func->bus = field & 0xf;
	MLX4_GET(field, outbox, QUERY_FUNC_DEVICE_OFFSET);
	func->device = field & 0xf1;
	MLX4_GET(field, outbox, QUERY_FUNC_FUNCTION_OFFSET);
	func->function = field & 0x7;
	MLX4_GET(field, outbox, QUERY_FUNC_PHYSICAL_FUNCTION_OFFSET);
	func->physical_function = field & 0xf;
	MLX4_GET(field16, outbox, QUERY_FUNC_RSVD_EQS_OFFSET);
	func->rsvd_eqs = field16 & 0xffff;
	MLX4_GET(field16, outbox, QUERY_FUNC_MAX_EQ_OFFSET);
	func->max_eq = field16 & 0xffff;
	MLX4_GET(field, outbox, QUERY_FUNC_RSVD_UARS_OFFSET);
	func->rsvd_uars = field & 0x0f;

	mlx4_dbg(dev, "Bus: %d, Device: %d, Function: %d, Physical function: %d, Max EQs: %d, Reserved EQs: %d, Reserved UARs: %d\n",
		 func->bus, func->device, func->function, func->physical_function,
		 func->max_eq, func->rsvd_eqs, func->rsvd_uars);

out:
	mlx4_मुक्त_cmd_mailbox(dev, mailbox);
	वापस err;
पूर्ण

अटल पूर्णांक mlx4_activate_vst_qinq(काष्ठा mlx4_priv *priv, पूर्णांक slave, पूर्णांक port)
अणु
	काष्ठा mlx4_vport_oper_state *vp_oper;
	काष्ठा mlx4_vport_state *vp_admin;
	पूर्णांक err;

	vp_oper = &priv->mfunc.master.vf_oper[slave].vport[port];
	vp_admin = &priv->mfunc.master.vf_admin[slave].vport[port];

	अगर (vp_admin->शेष_vlan != vp_oper->state.शेष_vlan) अणु
		err = __mlx4_रेजिस्टर_vlan(&priv->dev, port,
					   vp_admin->शेष_vlan,
					   &vp_oper->vlan_idx);
		अगर (err) अणु
			vp_oper->vlan_idx = NO_INDX;
			mlx4_warn(&priv->dev,
				  "No vlan resources slave %d, port %d\n",
				  slave, port);
			वापस err;
		पूर्ण
		mlx4_dbg(&priv->dev, "alloc vlan %d idx  %d slave %d port %d\n",
			 (पूर्णांक)(vp_oper->state.शेष_vlan),
			 vp_oper->vlan_idx, slave, port);
	पूर्ण
	vp_oper->state.vlan_proto   = vp_admin->vlan_proto;
	vp_oper->state.शेष_vlan = vp_admin->शेष_vlan;
	vp_oper->state.शेष_qos  = vp_admin->शेष_qos;

	वापस 0;
पूर्ण

अटल पूर्णांक mlx4_handle_vst_qinq(काष्ठा mlx4_priv *priv, पूर्णांक slave, पूर्णांक port)
अणु
	काष्ठा mlx4_vport_oper_state *vp_oper;
	काष्ठा mlx4_slave_state *slave_state;
	काष्ठा mlx4_vport_state *vp_admin;
	पूर्णांक err;

	vp_oper = &priv->mfunc.master.vf_oper[slave].vport[port];
	vp_admin = &priv->mfunc.master.vf_admin[slave].vport[port];
	slave_state = &priv->mfunc.master.slave_state[slave];

	अगर ((vp_admin->vlan_proto != htons(ETH_P_8021AD)) ||
	    (!slave_state->active))
		वापस 0;

	अगर (vp_oper->state.vlan_proto == vp_admin->vlan_proto &&
	    vp_oper->state.शेष_vlan == vp_admin->शेष_vlan &&
	    vp_oper->state.शेष_qos == vp_admin->शेष_qos)
		वापस 0;

	अगर (!slave_state->vst_qinq_supported) अणु
		/* Warn and revert the request to set vst QinQ mode */
		vp_admin->vlan_proto   = vp_oper->state.vlan_proto;
		vp_admin->शेष_vlan = vp_oper->state.शेष_vlan;
		vp_admin->शेष_qos  = vp_oper->state.शेष_qos;

		mlx4_warn(&priv->dev,
			  "Slave %d does not support VST QinQ mode\n", slave);
		वापस 0;
	पूर्ण

	err = mlx4_activate_vst_qinq(priv, slave, port);
	वापस err;
पूर्ण

पूर्णांक mlx4_QUERY_FUNC_CAP_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
				काष्ठा mlx4_vhcr *vhcr,
				काष्ठा mlx4_cmd_mailbox *inbox,
				काष्ठा mlx4_cmd_mailbox *outbox,
				काष्ठा mlx4_cmd_info *cmd)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	u8	field, port;
	u32	size, proxy_qp, qkey;
	पूर्णांक	err = 0;
	काष्ठा mlx4_func func;

#घोषणा QUERY_FUNC_CAP_FLAGS_OFFSET		0x0
#घोषणा QUERY_FUNC_CAP_NUM_PORTS_OFFSET		0x1
#घोषणा QUERY_FUNC_CAP_PF_BHVR_OFFSET		0x4
#घोषणा QUERY_FUNC_CAP_FMR_OFFSET		0x8
#घोषणा QUERY_FUNC_CAP_QP_QUOTA_OFFSET_DEP	0x10
#घोषणा QUERY_FUNC_CAP_CQ_QUOTA_OFFSET_DEP	0x14
#घोषणा QUERY_FUNC_CAP_SRQ_QUOTA_OFFSET_DEP	0x18
#घोषणा QUERY_FUNC_CAP_MPT_QUOTA_OFFSET_DEP	0x20
#घोषणा QUERY_FUNC_CAP_MTT_QUOTA_OFFSET_DEP	0x24
#घोषणा QUERY_FUNC_CAP_MCG_QUOTA_OFFSET_DEP	0x28
#घोषणा QUERY_FUNC_CAP_MAX_EQ_OFFSET		0x2c
#घोषणा QUERY_FUNC_CAP_RESERVED_EQ_OFFSET	0x30
#घोषणा QUERY_FUNC_CAP_QP_RESD_LKEY_OFFSET	0x48

#घोषणा QUERY_FUNC_CAP_QP_QUOTA_OFFSET		0x50
#घोषणा QUERY_FUNC_CAP_CQ_QUOTA_OFFSET		0x54
#घोषणा QUERY_FUNC_CAP_SRQ_QUOTA_OFFSET		0x58
#घोषणा QUERY_FUNC_CAP_MPT_QUOTA_OFFSET		0x60
#घोषणा QUERY_FUNC_CAP_MTT_QUOTA_OFFSET		0x64
#घोषणा QUERY_FUNC_CAP_MCG_QUOTA_OFFSET		0x68

#घोषणा QUERY_FUNC_CAP_EXTRA_FLAGS_OFFSET	0x6c

#घोषणा QUERY_FUNC_CAP_FMR_FLAG			0x80
#घोषणा QUERY_FUNC_CAP_FLAG_RDMA		0x40
#घोषणा QUERY_FUNC_CAP_FLAG_ETH			0x80
#घोषणा QUERY_FUNC_CAP_FLAG_QUOTAS		0x10
#घोषणा QUERY_FUNC_CAP_FLAG_RESD_LKEY		0x08
#घोषणा QUERY_FUNC_CAP_FLAG_VALID_MAILBOX	0x04

#घोषणा QUERY_FUNC_CAP_EXTRA_FLAGS_BF_QP_ALLOC_FLAG	(1UL << 31)
#घोषणा QUERY_FUNC_CAP_EXTRA_FLAGS_A0_QP_ALLOC_FLAG	(1UL << 30)

/* when opcode modअगरier = 1 */
#घोषणा QUERY_FUNC_CAP_PHYS_PORT_OFFSET		0x3
#घोषणा QUERY_FUNC_CAP_PRIV_VF_QKEY_OFFSET	0x4
#घोषणा QUERY_FUNC_CAP_FLAGS0_OFFSET		0x8
#घोषणा QUERY_FUNC_CAP_FLAGS1_OFFSET		0xc

#घोषणा QUERY_FUNC_CAP_QP0_TUNNEL		0x10
#घोषणा QUERY_FUNC_CAP_QP0_PROXY		0x14
#घोषणा QUERY_FUNC_CAP_QP1_TUNNEL		0x18
#घोषणा QUERY_FUNC_CAP_QP1_PROXY		0x1c
#घोषणा QUERY_FUNC_CAP_PHYS_PORT_ID		0x28

#घोषणा QUERY_FUNC_CAP_FLAGS1_FORCE_MAC		0x40
#घोषणा QUERY_FUNC_CAP_FLAGS1_FORCE_VLAN	0x80
#घोषणा QUERY_FUNC_CAP_FLAGS1_NIC_INFO			0x10
#घोषणा QUERY_FUNC_CAP_VF_ENABLE_QP0		0x08

#घोषणा QUERY_FUNC_CAP_FLAGS0_FORCE_PHY_WQE_GID 0x80
#घोषणा QUERY_FUNC_CAP_PHV_BIT			0x40
#घोषणा QUERY_FUNC_CAP_VLAN_OFFLOAD_DISABLE	0x20

#घोषणा QUERY_FUNC_CAP_SUPPORTS_VST_QINQ	BIT(30)
#घोषणा QUERY_FUNC_CAP_SUPPORTS_NON_POWER_OF_2_NUM_EQS BIT(31)

	अगर (vhcr->op_modअगरier == 1) अणु
		काष्ठा mlx4_active_ports actv_ports =
			mlx4_get_active_ports(dev, slave);
		पूर्णांक converted_port = mlx4_slave_convert_port(
				dev, slave, vhcr->in_modअगरier);
		काष्ठा mlx4_vport_oper_state *vp_oper;

		अगर (converted_port < 0)
			वापस -EINVAL;

		vhcr->in_modअगरier = converted_port;
		/* phys-port = logical-port */
		field = vhcr->in_modअगरier -
			find_first_bit(actv_ports.ports, dev->caps.num_ports);
		MLX4_PUT(outbox->buf, field, QUERY_FUNC_CAP_PHYS_PORT_OFFSET);

		port = vhcr->in_modअगरier;
		proxy_qp = dev->phys_caps.base_proxy_sqpn + 8 * slave + port - 1;

		/* Set nic_info bit to mark new fields support */
		field  = QUERY_FUNC_CAP_FLAGS1_NIC_INFO;

		अगर (mlx4_vf_smi_enabled(dev, slave, port) &&
		    !mlx4_get_parav_qkey(dev, proxy_qp, &qkey)) अणु
			field |= QUERY_FUNC_CAP_VF_ENABLE_QP0;
			MLX4_PUT(outbox->buf, qkey,
				 QUERY_FUNC_CAP_PRIV_VF_QKEY_OFFSET);
		पूर्ण
		MLX4_PUT(outbox->buf, field, QUERY_FUNC_CAP_FLAGS1_OFFSET);

		/* size is now the QP number */
		size = dev->phys_caps.base_tunnel_sqpn + 8 * slave + port - 1;
		MLX4_PUT(outbox->buf, size, QUERY_FUNC_CAP_QP0_TUNNEL);

		size += 2;
		MLX4_PUT(outbox->buf, size, QUERY_FUNC_CAP_QP1_TUNNEL);

		MLX4_PUT(outbox->buf, proxy_qp, QUERY_FUNC_CAP_QP0_PROXY);
		proxy_qp += 2;
		MLX4_PUT(outbox->buf, proxy_qp, QUERY_FUNC_CAP_QP1_PROXY);

		MLX4_PUT(outbox->buf, dev->caps.phys_port_id[vhcr->in_modअगरier],
			 QUERY_FUNC_CAP_PHYS_PORT_ID);

		vp_oper = &priv->mfunc.master.vf_oper[slave].vport[port];
		err = mlx4_handle_vst_qinq(priv, slave, port);
		अगर (err)
			वापस err;

		field = 0;
		अगर (dev->caps.phv_bit[port])
			field |= QUERY_FUNC_CAP_PHV_BIT;
		अगर (vp_oper->state.vlan_proto == htons(ETH_P_8021AD))
			field |= QUERY_FUNC_CAP_VLAN_OFFLOAD_DISABLE;
		MLX4_PUT(outbox->buf, field, QUERY_FUNC_CAP_FLAGS0_OFFSET);

	पूर्ण अन्यथा अगर (vhcr->op_modअगरier == 0) अणु
		काष्ठा mlx4_active_ports actv_ports =
			mlx4_get_active_ports(dev, slave);
		काष्ठा mlx4_slave_state *slave_state =
			&priv->mfunc.master.slave_state[slave];

		/* enable rdma and ethernet पूर्णांकerfaces, new quota locations,
		 * and reserved lkey
		 */
		field = (QUERY_FUNC_CAP_FLAG_ETH | QUERY_FUNC_CAP_FLAG_RDMA |
			 QUERY_FUNC_CAP_FLAG_QUOTAS | QUERY_FUNC_CAP_FLAG_VALID_MAILBOX |
			 QUERY_FUNC_CAP_FLAG_RESD_LKEY);
		MLX4_PUT(outbox->buf, field, QUERY_FUNC_CAP_FLAGS_OFFSET);

		field = min(
			biपंचांगap_weight(actv_ports.ports, dev->caps.num_ports),
			dev->caps.num_ports);
		MLX4_PUT(outbox->buf, field, QUERY_FUNC_CAP_NUM_PORTS_OFFSET);

		size = dev->caps.function_caps; /* set PF behaviours */
		MLX4_PUT(outbox->buf, size, QUERY_FUNC_CAP_PF_BHVR_OFFSET);

		field = 0; /* रक्षित FMR support not available as yet */
		MLX4_PUT(outbox->buf, field, QUERY_FUNC_CAP_FMR_OFFSET);

		size = priv->mfunc.master.res_tracker.res_alloc[RES_QP].quota[slave];
		MLX4_PUT(outbox->buf, size, QUERY_FUNC_CAP_QP_QUOTA_OFFSET);
		size = dev->caps.num_qps;
		MLX4_PUT(outbox->buf, size, QUERY_FUNC_CAP_QP_QUOTA_OFFSET_DEP);

		size = priv->mfunc.master.res_tracker.res_alloc[RES_SRQ].quota[slave];
		MLX4_PUT(outbox->buf, size, QUERY_FUNC_CAP_SRQ_QUOTA_OFFSET);
		size = dev->caps.num_srqs;
		MLX4_PUT(outbox->buf, size, QUERY_FUNC_CAP_SRQ_QUOTA_OFFSET_DEP);

		size = priv->mfunc.master.res_tracker.res_alloc[RES_CQ].quota[slave];
		MLX4_PUT(outbox->buf, size, QUERY_FUNC_CAP_CQ_QUOTA_OFFSET);
		size = dev->caps.num_cqs;
		MLX4_PUT(outbox->buf, size, QUERY_FUNC_CAP_CQ_QUOTA_OFFSET_DEP);

		अगर (!(dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_SYS_EQS) ||
		    mlx4_QUERY_FUNC(dev, &func, slave)) अणु
			size = vhcr->in_modअगरier &
				QUERY_FUNC_CAP_SUPPORTS_NON_POWER_OF_2_NUM_EQS ?
				dev->caps.num_eqs :
				roundकरोwn_घात_of_two(dev->caps.num_eqs);
			MLX4_PUT(outbox->buf, size, QUERY_FUNC_CAP_MAX_EQ_OFFSET);
			size = dev->caps.reserved_eqs;
			MLX4_PUT(outbox->buf, size, QUERY_FUNC_CAP_RESERVED_EQ_OFFSET);
		पूर्ण अन्यथा अणु
			size = vhcr->in_modअगरier &
				QUERY_FUNC_CAP_SUPPORTS_NON_POWER_OF_2_NUM_EQS ?
				func.max_eq :
				roundकरोwn_घात_of_two(func.max_eq);
			MLX4_PUT(outbox->buf, size, QUERY_FUNC_CAP_MAX_EQ_OFFSET);
			size = func.rsvd_eqs;
			MLX4_PUT(outbox->buf, size, QUERY_FUNC_CAP_RESERVED_EQ_OFFSET);
		पूर्ण

		size = priv->mfunc.master.res_tracker.res_alloc[RES_MPT].quota[slave];
		MLX4_PUT(outbox->buf, size, QUERY_FUNC_CAP_MPT_QUOTA_OFFSET);
		size = dev->caps.num_mpts;
		MLX4_PUT(outbox->buf, size, QUERY_FUNC_CAP_MPT_QUOTA_OFFSET_DEP);

		size = priv->mfunc.master.res_tracker.res_alloc[RES_MTT].quota[slave];
		MLX4_PUT(outbox->buf, size, QUERY_FUNC_CAP_MTT_QUOTA_OFFSET);
		size = dev->caps.num_mtts;
		MLX4_PUT(outbox->buf, size, QUERY_FUNC_CAP_MTT_QUOTA_OFFSET_DEP);

		size = dev->caps.num_mgms + dev->caps.num_amgms;
		MLX4_PUT(outbox->buf, size, QUERY_FUNC_CAP_MCG_QUOTA_OFFSET);
		MLX4_PUT(outbox->buf, size, QUERY_FUNC_CAP_MCG_QUOTA_OFFSET_DEP);

		size = QUERY_FUNC_CAP_EXTRA_FLAGS_BF_QP_ALLOC_FLAG |
			QUERY_FUNC_CAP_EXTRA_FLAGS_A0_QP_ALLOC_FLAG;
		MLX4_PUT(outbox->buf, size, QUERY_FUNC_CAP_EXTRA_FLAGS_OFFSET);

		size = dev->caps.reserved_lkey + ((slave << 8) & 0xFF00);
		MLX4_PUT(outbox->buf, size, QUERY_FUNC_CAP_QP_RESD_LKEY_OFFSET);

		अगर (vhcr->in_modअगरier & QUERY_FUNC_CAP_SUPPORTS_VST_QINQ)
			slave_state->vst_qinq_supported = true;

	पूर्ण अन्यथा
		err = -EINVAL;

	वापस err;
पूर्ण

पूर्णांक mlx4_QUERY_FUNC_CAP(काष्ठा mlx4_dev *dev, u8 gen_or_port,
			काष्ठा mlx4_func_cap *func_cap)
अणु
	काष्ठा mlx4_cmd_mailbox *mailbox;
	u32			*outbox;
	u8			field, op_modअगरier;
	u32			size, qkey;
	पूर्णांक			err = 0, quotas = 0;
	u32                     in_modअगरier;
	u32			slave_caps;

	op_modअगरier = !!gen_or_port; /* 0 = general, 1 = logical port */
	slave_caps = QUERY_FUNC_CAP_SUPPORTS_VST_QINQ |
		QUERY_FUNC_CAP_SUPPORTS_NON_POWER_OF_2_NUM_EQS;
	in_modअगरier = op_modअगरier ? gen_or_port : slave_caps;

	mailbox = mlx4_alloc_cmd_mailbox(dev);
	अगर (IS_ERR(mailbox))
		वापस PTR_ERR(mailbox);

	err = mlx4_cmd_box(dev, 0, mailbox->dma, in_modअगरier, op_modअगरier,
			   MLX4_CMD_QUERY_FUNC_CAP,
			   MLX4_CMD_TIME_CLASS_A, MLX4_CMD_WRAPPED);
	अगर (err)
		जाओ out;

	outbox = mailbox->buf;

	अगर (!op_modअगरier) अणु
		MLX4_GET(field, outbox, QUERY_FUNC_CAP_FLAGS_OFFSET);
		अगर (!(field & (QUERY_FUNC_CAP_FLAG_ETH | QUERY_FUNC_CAP_FLAG_RDMA))) अणु
			mlx4_err(dev, "The host supports neither eth nor rdma interfaces\n");
			err = -EPROTONOSUPPORT;
			जाओ out;
		पूर्ण
		func_cap->flags = field;
		quotas = !!(func_cap->flags & QUERY_FUNC_CAP_FLAG_QUOTAS);

		MLX4_GET(field, outbox, QUERY_FUNC_CAP_NUM_PORTS_OFFSET);
		func_cap->num_ports = field;

		MLX4_GET(size, outbox, QUERY_FUNC_CAP_PF_BHVR_OFFSET);
		func_cap->pf_context_behaviour = size;

		अगर (quotas) अणु
			MLX4_GET(size, outbox, QUERY_FUNC_CAP_QP_QUOTA_OFFSET);
			func_cap->qp_quota = size & 0xFFFFFF;

			MLX4_GET(size, outbox, QUERY_FUNC_CAP_SRQ_QUOTA_OFFSET);
			func_cap->srq_quota = size & 0xFFFFFF;

			MLX4_GET(size, outbox, QUERY_FUNC_CAP_CQ_QUOTA_OFFSET);
			func_cap->cq_quota = size & 0xFFFFFF;

			MLX4_GET(size, outbox, QUERY_FUNC_CAP_MPT_QUOTA_OFFSET);
			func_cap->mpt_quota = size & 0xFFFFFF;

			MLX4_GET(size, outbox, QUERY_FUNC_CAP_MTT_QUOTA_OFFSET);
			func_cap->mtt_quota = size & 0xFFFFFF;

			MLX4_GET(size, outbox, QUERY_FUNC_CAP_MCG_QUOTA_OFFSET);
			func_cap->mcg_quota = size & 0xFFFFFF;

		पूर्ण अन्यथा अणु
			MLX4_GET(size, outbox, QUERY_FUNC_CAP_QP_QUOTA_OFFSET_DEP);
			func_cap->qp_quota = size & 0xFFFFFF;

			MLX4_GET(size, outbox, QUERY_FUNC_CAP_SRQ_QUOTA_OFFSET_DEP);
			func_cap->srq_quota = size & 0xFFFFFF;

			MLX4_GET(size, outbox, QUERY_FUNC_CAP_CQ_QUOTA_OFFSET_DEP);
			func_cap->cq_quota = size & 0xFFFFFF;

			MLX4_GET(size, outbox, QUERY_FUNC_CAP_MPT_QUOTA_OFFSET_DEP);
			func_cap->mpt_quota = size & 0xFFFFFF;

			MLX4_GET(size, outbox, QUERY_FUNC_CAP_MTT_QUOTA_OFFSET_DEP);
			func_cap->mtt_quota = size & 0xFFFFFF;

			MLX4_GET(size, outbox, QUERY_FUNC_CAP_MCG_QUOTA_OFFSET_DEP);
			func_cap->mcg_quota = size & 0xFFFFFF;
		पूर्ण
		MLX4_GET(size, outbox, QUERY_FUNC_CAP_MAX_EQ_OFFSET);
		func_cap->max_eq = size & 0xFFFFFF;

		MLX4_GET(size, outbox, QUERY_FUNC_CAP_RESERVED_EQ_OFFSET);
		func_cap->reserved_eq = size & 0xFFFFFF;

		अगर (func_cap->flags & QUERY_FUNC_CAP_FLAG_RESD_LKEY) अणु
			MLX4_GET(size, outbox, QUERY_FUNC_CAP_QP_RESD_LKEY_OFFSET);
			func_cap->reserved_lkey = size;
		पूर्ण अन्यथा अणु
			func_cap->reserved_lkey = 0;
		पूर्ण

		func_cap->extra_flags = 0;

		/* Mailbox data from 0x6c and onward should only be treated अगर
		 * QUERY_FUNC_CAP_FLAG_VALID_MAILBOX is set in func_cap->flags
		 */
		अगर (func_cap->flags & QUERY_FUNC_CAP_FLAG_VALID_MAILBOX) अणु
			MLX4_GET(size, outbox, QUERY_FUNC_CAP_EXTRA_FLAGS_OFFSET);
			अगर (size & QUERY_FUNC_CAP_EXTRA_FLAGS_BF_QP_ALLOC_FLAG)
				func_cap->extra_flags |= MLX4_QUERY_FUNC_FLAGS_BF_RES_QP;
			अगर (size & QUERY_FUNC_CAP_EXTRA_FLAGS_A0_QP_ALLOC_FLAG)
				func_cap->extra_flags |= MLX4_QUERY_FUNC_FLAGS_A0_RES_QP;
		पूर्ण

		जाओ out;
	पूर्ण

	/* logical port query */
	अगर (gen_or_port > dev->caps.num_ports) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण

	MLX4_GET(func_cap->flags1, outbox, QUERY_FUNC_CAP_FLAGS1_OFFSET);
	अगर (dev->caps.port_type[gen_or_port] == MLX4_PORT_TYPE_ETH) अणु
		अगर (func_cap->flags1 & QUERY_FUNC_CAP_FLAGS1_FORCE_VLAN) अणु
			mlx4_err(dev, "VLAN is enforced on this port\n");
			err = -EPROTONOSUPPORT;
			जाओ out;
		पूर्ण

		अगर (func_cap->flags1 & QUERY_FUNC_CAP_FLAGS1_FORCE_MAC) अणु
			mlx4_err(dev, "Force mac is enabled on this port\n");
			err = -EPROTONOSUPPORT;
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अगर (dev->caps.port_type[gen_or_port] == MLX4_PORT_TYPE_IB) अणु
		MLX4_GET(field, outbox, QUERY_FUNC_CAP_FLAGS0_OFFSET);
		अगर (field & QUERY_FUNC_CAP_FLAGS0_FORCE_PHY_WQE_GID) अणु
			mlx4_err(dev, "phy_wqe_gid is enforced on this ib port\n");
			err = -EPROTONOSUPPORT;
			जाओ out;
		पूर्ण
	पूर्ण

	MLX4_GET(field, outbox, QUERY_FUNC_CAP_PHYS_PORT_OFFSET);
	func_cap->physical_port = field;
	अगर (func_cap->physical_port != gen_or_port) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (func_cap->flags1 & QUERY_FUNC_CAP_VF_ENABLE_QP0) अणु
		MLX4_GET(qkey, outbox, QUERY_FUNC_CAP_PRIV_VF_QKEY_OFFSET);
		func_cap->spec_qps.qp0_qkey = qkey;
	पूर्ण अन्यथा अणु
		func_cap->spec_qps.qp0_qkey = 0;
	पूर्ण

	MLX4_GET(size, outbox, QUERY_FUNC_CAP_QP0_TUNNEL);
	func_cap->spec_qps.qp0_tunnel = size & 0xFFFFFF;

	MLX4_GET(size, outbox, QUERY_FUNC_CAP_QP0_PROXY);
	func_cap->spec_qps.qp0_proxy = size & 0xFFFFFF;

	MLX4_GET(size, outbox, QUERY_FUNC_CAP_QP1_TUNNEL);
	func_cap->spec_qps.qp1_tunnel = size & 0xFFFFFF;

	MLX4_GET(size, outbox, QUERY_FUNC_CAP_QP1_PROXY);
	func_cap->spec_qps.qp1_proxy = size & 0xFFFFFF;

	अगर (func_cap->flags1 & QUERY_FUNC_CAP_FLAGS1_NIC_INFO)
		MLX4_GET(func_cap->phys_port_id, outbox,
			 QUERY_FUNC_CAP_PHYS_PORT_ID);

	MLX4_GET(func_cap->flags0, outbox, QUERY_FUNC_CAP_FLAGS0_OFFSET);

	/* All other resources are allocated by the master, but we still report
	 * 'num' and 'reserved' capabilities as follows:
	 * - num reमुख्यs the maximum resource index
	 * - 'num - reserved' is the total available objects of a resource, but
	 *   resource indices may be less than 'reserved'
	 * TODO: set per-resource quotas */

out:
	mlx4_मुक्त_cmd_mailbox(dev, mailbox);

	वापस err;
पूर्ण

अटल व्योम disable_unsupported_roce_caps(व्योम *buf);

पूर्णांक mlx4_QUERY_DEV_CAP(काष्ठा mlx4_dev *dev, काष्ठा mlx4_dev_cap *dev_cap)
अणु
	काष्ठा mlx4_cmd_mailbox *mailbox;
	u32 *outbox;
	u8 field;
	u32 field32, flags, ext_flags;
	u16 size;
	u16 stat_rate;
	पूर्णांक err;
	पूर्णांक i;

#घोषणा QUERY_DEV_CAP_OUT_SIZE		       0x100
#घोषणा QUERY_DEV_CAP_MAX_SRQ_SZ_OFFSET		0x10
#घोषणा QUERY_DEV_CAP_MAX_QP_SZ_OFFSET		0x11
#घोषणा QUERY_DEV_CAP_RSVD_QP_OFFSET		0x12
#घोषणा QUERY_DEV_CAP_MAX_QP_OFFSET		0x13
#घोषणा QUERY_DEV_CAP_RSVD_SRQ_OFFSET		0x14
#घोषणा QUERY_DEV_CAP_MAX_SRQ_OFFSET		0x15
#घोषणा QUERY_DEV_CAP_RSVD_EEC_OFFSET		0x16
#घोषणा QUERY_DEV_CAP_MAX_EEC_OFFSET		0x17
#घोषणा QUERY_DEV_CAP_MAX_CQ_SZ_OFFSET		0x19
#घोषणा QUERY_DEV_CAP_RSVD_CQ_OFFSET		0x1a
#घोषणा QUERY_DEV_CAP_MAX_CQ_OFFSET		0x1b
#घोषणा QUERY_DEV_CAP_MAX_MPT_OFFSET		0x1d
#घोषणा QUERY_DEV_CAP_RSVD_EQ_OFFSET		0x1e
#घोषणा QUERY_DEV_CAP_MAX_EQ_OFFSET		0x1f
#घोषणा QUERY_DEV_CAP_RSVD_MTT_OFFSET		0x20
#घोषणा QUERY_DEV_CAP_MAX_MRW_SZ_OFFSET		0x21
#घोषणा QUERY_DEV_CAP_RSVD_MRW_OFFSET		0x22
#घोषणा QUERY_DEV_CAP_MAX_MTT_SEG_OFFSET	0x23
#घोषणा QUERY_DEV_CAP_NUM_SYS_EQ_OFFSET		0x26
#घोषणा QUERY_DEV_CAP_MAX_AV_OFFSET		0x27
#घोषणा QUERY_DEV_CAP_MAX_REQ_QP_OFFSET		0x29
#घोषणा QUERY_DEV_CAP_MAX_RES_QP_OFFSET		0x2b
#घोषणा QUERY_DEV_CAP_MAX_GSO_OFFSET		0x2d
#घोषणा QUERY_DEV_CAP_RSS_OFFSET		0x2e
#घोषणा QUERY_DEV_CAP_MAX_RDMA_OFFSET		0x2f
#घोषणा QUERY_DEV_CAP_RSZ_SRQ_OFFSET		0x33
#घोषणा QUERY_DEV_CAP_PORT_BEACON_OFFSET	0x34
#घोषणा QUERY_DEV_CAP_ACK_DELAY_OFFSET		0x35
#घोषणा QUERY_DEV_CAP_MTU_WIDTH_OFFSET		0x36
#घोषणा QUERY_DEV_CAP_VL_PORT_OFFSET		0x37
#घोषणा QUERY_DEV_CAP_MAX_MSG_SZ_OFFSET		0x38
#घोषणा QUERY_DEV_CAP_MAX_GID_OFFSET		0x3b
#घोषणा QUERY_DEV_CAP_RATE_SUPPORT_OFFSET	0x3c
#घोषणा QUERY_DEV_CAP_CQ_TS_SUPPORT_OFFSET	0x3e
#घोषणा QUERY_DEV_CAP_MAX_PKEY_OFFSET		0x3f
#घोषणा QUERY_DEV_CAP_EXT_FLAGS_OFFSET		0x40
#घोषणा QUERY_DEV_CAP_WOL_OFFSET		0x43
#घोषणा QUERY_DEV_CAP_FLAGS_OFFSET		0x44
#घोषणा QUERY_DEV_CAP_RSVD_UAR_OFFSET		0x48
#घोषणा QUERY_DEV_CAP_UAR_SZ_OFFSET		0x49
#घोषणा QUERY_DEV_CAP_PAGE_SZ_OFFSET		0x4b
#घोषणा QUERY_DEV_CAP_BF_OFFSET			0x4c
#घोषणा QUERY_DEV_CAP_LOG_BF_REG_SZ_OFFSET	0x4d
#घोषणा QUERY_DEV_CAP_LOG_MAX_BF_REGS_PER_PAGE_OFFSET	0x4e
#घोषणा QUERY_DEV_CAP_LOG_MAX_BF_PAGES_OFFSET	0x4f
#घोषणा QUERY_DEV_CAP_MAX_SG_SQ_OFFSET		0x51
#घोषणा QUERY_DEV_CAP_MAX_DESC_SZ_SQ_OFFSET	0x52
#घोषणा QUERY_DEV_CAP_MAX_SG_RQ_OFFSET		0x55
#घोषणा QUERY_DEV_CAP_MAX_DESC_SZ_RQ_OFFSET	0x56
#घोषणा QUERY_DEV_CAP_USER_MAC_EN_OFFSET	0x5C
#घोषणा QUERY_DEV_CAP_SVLAN_BY_QP_OFFSET	0x5D
#घोषणा QUERY_DEV_CAP_MAX_QP_MCG_OFFSET		0x61
#घोषणा QUERY_DEV_CAP_RSVD_MCG_OFFSET		0x62
#घोषणा QUERY_DEV_CAP_MAX_MCG_OFFSET		0x63
#घोषणा QUERY_DEV_CAP_RSVD_PD_OFFSET		0x64
#घोषणा QUERY_DEV_CAP_MAX_PD_OFFSET		0x65
#घोषणा QUERY_DEV_CAP_RSVD_XRC_OFFSET		0x66
#घोषणा QUERY_DEV_CAP_MAX_XRC_OFFSET		0x67
#घोषणा QUERY_DEV_CAP_MAX_COUNTERS_OFFSET	0x68
#घोषणा QUERY_DEV_CAP_PORT_FLOWSTATS_COUNTERS_OFFSET	0x70
#घोषणा QUERY_DEV_CAP_EXT_2_FLAGS_OFFSET	0x70
#घोषणा QUERY_DEV_CAP_FLOW_STEERING_IPOIB_OFFSET	0x74
#घोषणा QUERY_DEV_CAP_FLOW_STEERING_RANGE_EN_OFFSET	0x76
#घोषणा QUERY_DEV_CAP_FLOW_STEERING_MAX_QP_OFFSET	0x77
#घोषणा QUERY_DEV_CAP_SL2VL_EVENT_OFFSET	0x78
#घोषणा QUERY_DEV_CAP_CQ_EQ_CACHE_LINE_STRIDE	0x7a
#घोषणा QUERY_DEV_CAP_ECN_QCN_VER_OFFSET	0x7b
#घोषणा QUERY_DEV_CAP_RDMARC_ENTRY_SZ_OFFSET	0x80
#घोषणा QUERY_DEV_CAP_QPC_ENTRY_SZ_OFFSET	0x82
#घोषणा QUERY_DEV_CAP_AUX_ENTRY_SZ_OFFSET	0x84
#घोषणा QUERY_DEV_CAP_ALTC_ENTRY_SZ_OFFSET	0x86
#घोषणा QUERY_DEV_CAP_EQC_ENTRY_SZ_OFFSET	0x88
#घोषणा QUERY_DEV_CAP_CQC_ENTRY_SZ_OFFSET	0x8a
#घोषणा QUERY_DEV_CAP_SRQ_ENTRY_SZ_OFFSET	0x8c
#घोषणा QUERY_DEV_CAP_C_MPT_ENTRY_SZ_OFFSET	0x8e
#घोषणा QUERY_DEV_CAP_MTT_ENTRY_SZ_OFFSET	0x90
#घोषणा QUERY_DEV_CAP_D_MPT_ENTRY_SZ_OFFSET	0x92
#घोषणा QUERY_DEV_CAP_BMME_FLAGS_OFFSET		0x94
#घोषणा QUERY_DEV_CAP_CONFIG_DEV_OFFSET		0x94
#घोषणा QUERY_DEV_CAP_PHV_EN_OFFSET		0x96
#घोषणा QUERY_DEV_CAP_RSVD_LKEY_OFFSET		0x98
#घोषणा QUERY_DEV_CAP_MAX_ICM_SZ_OFFSET		0xa0
#घोषणा QUERY_DEV_CAP_ETH_BACKPL_OFFSET		0x9c
#घोषणा QUERY_DEV_CAP_DIAG_RPRT_PER_PORT	0x9c
#घोषणा QUERY_DEV_CAP_FW_REASSIGN_MAC		0x9d
#घोषणा QUERY_DEV_CAP_VXLAN			0x9e
#घोषणा QUERY_DEV_CAP_MAD_DEMUX_OFFSET		0xb0
#घोषणा QUERY_DEV_CAP_DMFS_HIGH_RATE_QPN_BASE_OFFSET	0xa8
#घोषणा QUERY_DEV_CAP_DMFS_HIGH_RATE_QPN_RANGE_OFFSET	0xac
#घोषणा QUERY_DEV_CAP_MAP_CLOCK_TO_USER 0xc1
#घोषणा QUERY_DEV_CAP_QP_RATE_LIMIT_NUM_OFFSET	0xcc
#घोषणा QUERY_DEV_CAP_QP_RATE_LIMIT_MAX_OFFSET	0xd0
#घोषणा QUERY_DEV_CAP_QP_RATE_LIMIT_MIN_OFFSET	0xd2
#घोषणा QUERY_DEV_CAP_HEALTH_BUFFER_ADDRESS_OFFSET	0xe4

	dev_cap->flags2 = 0;
	mailbox = mlx4_alloc_cmd_mailbox(dev);
	अगर (IS_ERR(mailbox))
		वापस PTR_ERR(mailbox);
	outbox = mailbox->buf;

	err = mlx4_cmd_box(dev, 0, mailbox->dma, 0, 0, MLX4_CMD_QUERY_DEV_CAP,
			   MLX4_CMD_TIME_CLASS_A, MLX4_CMD_NATIVE);
	अगर (err)
		जाओ out;

	अगर (mlx4_is_mfunc(dev))
		disable_unsupported_roce_caps(outbox);
	MLX4_GET(field, outbox, QUERY_DEV_CAP_MAP_CLOCK_TO_USER);
	dev_cap->map_घड़ी_प्रकारo_user = field & 0x80;
	MLX4_GET(field, outbox, QUERY_DEV_CAP_RSVD_QP_OFFSET);
	dev_cap->reserved_qps = 1 << (field & 0xf);
	MLX4_GET(field, outbox, QUERY_DEV_CAP_MAX_QP_OFFSET);
	dev_cap->max_qps = 1 << (field & 0x1f);
	MLX4_GET(field, outbox, QUERY_DEV_CAP_RSVD_SRQ_OFFSET);
	dev_cap->reserved_srqs = 1 << (field >> 4);
	MLX4_GET(field, outbox, QUERY_DEV_CAP_MAX_SRQ_OFFSET);
	dev_cap->max_srqs = 1 << (field & 0x1f);
	MLX4_GET(field, outbox, QUERY_DEV_CAP_MAX_CQ_SZ_OFFSET);
	dev_cap->max_cq_sz = 1 << field;
	MLX4_GET(field, outbox, QUERY_DEV_CAP_RSVD_CQ_OFFSET);
	dev_cap->reserved_cqs = 1 << (field & 0xf);
	MLX4_GET(field, outbox, QUERY_DEV_CAP_MAX_CQ_OFFSET);
	dev_cap->max_cqs = 1 << (field & 0x1f);
	MLX4_GET(field, outbox, QUERY_DEV_CAP_MAX_MPT_OFFSET);
	dev_cap->max_mpts = 1 << (field & 0x3f);
	MLX4_GET(field, outbox, QUERY_DEV_CAP_RSVD_EQ_OFFSET);
	dev_cap->reserved_eqs = 1 << (field & 0xf);
	MLX4_GET(field, outbox, QUERY_DEV_CAP_MAX_EQ_OFFSET);
	dev_cap->max_eqs = 1 << (field & 0xf);
	MLX4_GET(field, outbox, QUERY_DEV_CAP_RSVD_MTT_OFFSET);
	dev_cap->reserved_mtts = 1 << (field >> 4);
	MLX4_GET(field, outbox, QUERY_DEV_CAP_RSVD_MRW_OFFSET);
	dev_cap->reserved_mrws = 1 << (field & 0xf);
	MLX4_GET(size, outbox, QUERY_DEV_CAP_NUM_SYS_EQ_OFFSET);
	dev_cap->num_sys_eqs = size & 0xfff;
	MLX4_GET(field, outbox, QUERY_DEV_CAP_MAX_REQ_QP_OFFSET);
	dev_cap->max_requester_per_qp = 1 << (field & 0x3f);
	MLX4_GET(field, outbox, QUERY_DEV_CAP_MAX_RES_QP_OFFSET);
	dev_cap->max_responder_per_qp = 1 << (field & 0x3f);
	MLX4_GET(field, outbox, QUERY_DEV_CAP_MAX_GSO_OFFSET);
	field &= 0x1f;
	अगर (!field)
		dev_cap->max_gso_sz = 0;
	अन्यथा
		dev_cap->max_gso_sz = 1 << field;

	MLX4_GET(field, outbox, QUERY_DEV_CAP_RSS_OFFSET);
	अगर (field & 0x20)
		dev_cap->flags2 |= MLX4_DEV_CAP_FLAG2_RSS_XOR;
	अगर (field & 0x10)
		dev_cap->flags2 |= MLX4_DEV_CAP_FLAG2_RSS_TOP;
	field &= 0xf;
	अगर (field) अणु
		dev_cap->flags2 |= MLX4_DEV_CAP_FLAG2_RSS;
		dev_cap->max_rss_tbl_sz = 1 << field;
	पूर्ण अन्यथा
		dev_cap->max_rss_tbl_sz = 0;
	MLX4_GET(field, outbox, QUERY_DEV_CAP_MAX_RDMA_OFFSET);
	dev_cap->max_rdma_global = 1 << (field & 0x3f);
	MLX4_GET(field, outbox, QUERY_DEV_CAP_ACK_DELAY_OFFSET);
	dev_cap->local_ca_ack_delay = field & 0x1f;
	MLX4_GET(field, outbox, QUERY_DEV_CAP_VL_PORT_OFFSET);
	dev_cap->num_ports = field & 0xf;
	MLX4_GET(field, outbox, QUERY_DEV_CAP_MAX_MSG_SZ_OFFSET);
	dev_cap->max_msg_sz = 1 << (field & 0x1f);
	MLX4_GET(field, outbox, QUERY_DEV_CAP_PORT_FLOWSTATS_COUNTERS_OFFSET);
	अगर (field & 0x10)
		dev_cap->flags2 |= MLX4_DEV_CAP_FLAG2_FLOWSTATS_EN;
	MLX4_GET(field, outbox, QUERY_DEV_CAP_FLOW_STEERING_RANGE_EN_OFFSET);
	अगर (field & 0x80)
		dev_cap->flags2 |= MLX4_DEV_CAP_FLAG2_FS_EN;
	dev_cap->fs_log_max_ucast_qp_range_size = field & 0x1f;
	अगर (field & 0x20)
		dev_cap->flags2 |= MLX4_DEV_CAP_FLAG2_DMFS_UC_MC_SNIFFER;
	MLX4_GET(field, outbox, QUERY_DEV_CAP_PORT_BEACON_OFFSET);
	अगर (field & 0x80)
		dev_cap->flags2 |= MLX4_DEV_CAP_FLAG2_PORT_BEACON;
	MLX4_GET(field, outbox, QUERY_DEV_CAP_FLOW_STEERING_IPOIB_OFFSET);
	अगर (field & 0x80)
		dev_cap->flags2 |= MLX4_DEV_CAP_FLAG2_DMFS_IPOIB;
	MLX4_GET(field, outbox, QUERY_DEV_CAP_FLOW_STEERING_MAX_QP_OFFSET);
	dev_cap->fs_max_num_qp_per_entry = field;
	MLX4_GET(field, outbox, QUERY_DEV_CAP_SL2VL_EVENT_OFFSET);
	अगर (field & (1 << 5))
		dev_cap->flags2 |= MLX4_DEV_CAP_FLAG2_SL_TO_VL_CHANGE_EVENT;
	MLX4_GET(field, outbox, QUERY_DEV_CAP_ECN_QCN_VER_OFFSET);
	अगर (field & 0x1)
		dev_cap->flags2 |= MLX4_DEV_CAP_FLAG2_QCN;
	MLX4_GET(stat_rate, outbox, QUERY_DEV_CAP_RATE_SUPPORT_OFFSET);
	dev_cap->stat_rate_support = stat_rate;
	MLX4_GET(field, outbox, QUERY_DEV_CAP_CQ_TS_SUPPORT_OFFSET);
	अगर (field & 0x80)
		dev_cap->flags2 |= MLX4_DEV_CAP_FLAG2_TS;
	MLX4_GET(ext_flags, outbox, QUERY_DEV_CAP_EXT_FLAGS_OFFSET);
	MLX4_GET(flags, outbox, QUERY_DEV_CAP_FLAGS_OFFSET);
	dev_cap->flags = flags | (u64)ext_flags << 32;
	MLX4_GET(field, outbox, QUERY_DEV_CAP_WOL_OFFSET);
	dev_cap->wol_port[1] = !!(field & 0x20);
	dev_cap->wol_port[2] = !!(field & 0x40);
	MLX4_GET(field, outbox, QUERY_DEV_CAP_RSVD_UAR_OFFSET);
	dev_cap->reserved_uars = field >> 4;
	MLX4_GET(field, outbox, QUERY_DEV_CAP_UAR_SZ_OFFSET);
	dev_cap->uar_size = 1 << ((field & 0x3f) + 20);
	MLX4_GET(field, outbox, QUERY_DEV_CAP_PAGE_SZ_OFFSET);
	dev_cap->min_page_sz = 1 << field;

	MLX4_GET(field, outbox, QUERY_DEV_CAP_BF_OFFSET);
	अगर (field & 0x80) अणु
		MLX4_GET(field, outbox, QUERY_DEV_CAP_LOG_BF_REG_SZ_OFFSET);
		dev_cap->bf_reg_size = 1 << (field & 0x1f);
		MLX4_GET(field, outbox, QUERY_DEV_CAP_LOG_MAX_BF_REGS_PER_PAGE_OFFSET);
		अगर ((1 << (field & 0x3f)) > (PAGE_SIZE / dev_cap->bf_reg_size))
			field = 3;
		dev_cap->bf_regs_per_page = 1 << (field & 0x3f);
	पूर्ण अन्यथा अणु
		dev_cap->bf_reg_size = 0;
	पूर्ण

	MLX4_GET(field, outbox, QUERY_DEV_CAP_MAX_SG_SQ_OFFSET);
	dev_cap->max_sq_sg = field;
	MLX4_GET(size, outbox, QUERY_DEV_CAP_MAX_DESC_SZ_SQ_OFFSET);
	dev_cap->max_sq_desc_sz = size;

	MLX4_GET(field, outbox, QUERY_DEV_CAP_USER_MAC_EN_OFFSET);
	अगर (field & (1 << 2))
		dev_cap->flags2 |= MLX4_DEV_CAP_FLAG2_USER_MAC_EN;
	MLX4_GET(field, outbox, QUERY_DEV_CAP_SVLAN_BY_QP_OFFSET);
	अगर (field & 0x1)
		dev_cap->flags2 |= MLX4_DEV_CAP_FLAG2_SVLAN_BY_QP;
	MLX4_GET(field, outbox, QUERY_DEV_CAP_MAX_QP_MCG_OFFSET);
	dev_cap->max_qp_per_mcg = 1 << field;
	MLX4_GET(field, outbox, QUERY_DEV_CAP_RSVD_MCG_OFFSET);
	dev_cap->reserved_mgms = field & 0xf;
	MLX4_GET(field, outbox, QUERY_DEV_CAP_MAX_MCG_OFFSET);
	dev_cap->max_mcgs = 1 << field;
	MLX4_GET(field, outbox, QUERY_DEV_CAP_RSVD_PD_OFFSET);
	dev_cap->reserved_pds = field >> 4;
	MLX4_GET(field, outbox, QUERY_DEV_CAP_MAX_PD_OFFSET);
	dev_cap->max_pds = 1 << (field & 0x3f);
	MLX4_GET(field, outbox, QUERY_DEV_CAP_RSVD_XRC_OFFSET);
	dev_cap->reserved_xrcds = field >> 4;
	MLX4_GET(field, outbox, QUERY_DEV_CAP_MAX_XRC_OFFSET);
	dev_cap->max_xrcds = 1 << (field & 0x1f);

	MLX4_GET(size, outbox, QUERY_DEV_CAP_RDMARC_ENTRY_SZ_OFFSET);
	dev_cap->rdmarc_entry_sz = size;
	MLX4_GET(size, outbox, QUERY_DEV_CAP_QPC_ENTRY_SZ_OFFSET);
	dev_cap->qpc_entry_sz = size;
	MLX4_GET(size, outbox, QUERY_DEV_CAP_AUX_ENTRY_SZ_OFFSET);
	dev_cap->aux_entry_sz = size;
	MLX4_GET(size, outbox, QUERY_DEV_CAP_ALTC_ENTRY_SZ_OFFSET);
	dev_cap->altc_entry_sz = size;
	MLX4_GET(size, outbox, QUERY_DEV_CAP_EQC_ENTRY_SZ_OFFSET);
	dev_cap->eqc_entry_sz = size;
	MLX4_GET(size, outbox, QUERY_DEV_CAP_CQC_ENTRY_SZ_OFFSET);
	dev_cap->cqc_entry_sz = size;
	MLX4_GET(size, outbox, QUERY_DEV_CAP_SRQ_ENTRY_SZ_OFFSET);
	dev_cap->srq_entry_sz = size;
	MLX4_GET(size, outbox, QUERY_DEV_CAP_C_MPT_ENTRY_SZ_OFFSET);
	dev_cap->cmpt_entry_sz = size;
	MLX4_GET(size, outbox, QUERY_DEV_CAP_MTT_ENTRY_SZ_OFFSET);
	dev_cap->mtt_entry_sz = size;
	MLX4_GET(size, outbox, QUERY_DEV_CAP_D_MPT_ENTRY_SZ_OFFSET);
	dev_cap->dmpt_entry_sz = size;

	MLX4_GET(field, outbox, QUERY_DEV_CAP_MAX_SRQ_SZ_OFFSET);
	dev_cap->max_srq_sz = 1 << field;
	MLX4_GET(field, outbox, QUERY_DEV_CAP_MAX_QP_SZ_OFFSET);
	dev_cap->max_qp_sz = 1 << field;
	MLX4_GET(field, outbox, QUERY_DEV_CAP_RSZ_SRQ_OFFSET);
	dev_cap->resize_srq = field & 1;
	MLX4_GET(field, outbox, QUERY_DEV_CAP_MAX_SG_RQ_OFFSET);
	dev_cap->max_rq_sg = field;
	MLX4_GET(size, outbox, QUERY_DEV_CAP_MAX_DESC_SZ_RQ_OFFSET);
	dev_cap->max_rq_desc_sz = size;
	MLX4_GET(field, outbox, QUERY_DEV_CAP_CQ_EQ_CACHE_LINE_STRIDE);
	अगर (field & (1 << 4))
		dev_cap->flags2 |= MLX4_DEV_CAP_FLAG2_QOS_VPP;
	अगर (field & (1 << 5))
		dev_cap->flags2 |= MLX4_DEV_CAP_FLAG2_ETH_PROT_CTRL;
	अगर (field & (1 << 6))
		dev_cap->flags2 |= MLX4_DEV_CAP_FLAG2_CQE_STRIDE;
	अगर (field & (1 << 7))
		dev_cap->flags2 |= MLX4_DEV_CAP_FLAG2_EQE_STRIDE;
	MLX4_GET(dev_cap->bmme_flags, outbox,
		 QUERY_DEV_CAP_BMME_FLAGS_OFFSET);
	अगर (dev_cap->bmme_flags & MLX4_FLAG_ROCE_V1_V2)
		dev_cap->flags2 |= MLX4_DEV_CAP_FLAG2_ROCE_V1_V2;
	अगर (dev_cap->bmme_flags & MLX4_FLAG_PORT_REMAP)
		dev_cap->flags2 |= MLX4_DEV_CAP_FLAG2_PORT_REMAP;
	MLX4_GET(field, outbox, QUERY_DEV_CAP_CONFIG_DEV_OFFSET);
	अगर (field & 0x20)
		dev_cap->flags2 |= MLX4_DEV_CAP_FLAG2_CONFIG_DEV;
	अगर (field & (1 << 2))
		dev_cap->flags2 |= MLX4_DEV_CAP_FLAG2_IGNORE_FCS;
	MLX4_GET(field, outbox, QUERY_DEV_CAP_PHV_EN_OFFSET);
	अगर (field & 0x80)
		dev_cap->flags2 |= MLX4_DEV_CAP_FLAG2_PHV_EN;
	अगर (field & 0x40)
		dev_cap->flags2 |= MLX4_DEV_CAP_FLAG2_SKIP_OUTER_VLAN;

	MLX4_GET(dev_cap->reserved_lkey, outbox,
		 QUERY_DEV_CAP_RSVD_LKEY_OFFSET);
	MLX4_GET(field32, outbox, QUERY_DEV_CAP_ETH_BACKPL_OFFSET);
	अगर (field32 & (1 << 0))
		dev_cap->flags2 |= MLX4_DEV_CAP_FLAG2_ETH_BACKPL_AN_REP;
	अगर (field32 & (1 << 7))
		dev_cap->flags2 |= MLX4_DEV_CAP_FLAG2_RECOVERABLE_ERROR_EVENT;
	अगर (field32 & (1 << 8))
		dev_cap->flags2 |= MLX4_DEV_CAP_FLAG2_DRIVER_VERSION_TO_FW;
	MLX4_GET(field32, outbox, QUERY_DEV_CAP_DIAG_RPRT_PER_PORT);
	अगर (field32 & (1 << 17))
		dev_cap->flags2 |= MLX4_DEV_CAP_FLAG2_DIAG_PER_PORT;
	MLX4_GET(field, outbox, QUERY_DEV_CAP_FW_REASSIGN_MAC);
	अगर (field & 1<<6)
		dev_cap->flags2 |= MLX4_DEV_CAP_FLAG2_REASSIGN_MAC_EN;
	MLX4_GET(field, outbox, QUERY_DEV_CAP_VXLAN);
	अगर (field & 1<<3)
		dev_cap->flags2 |= MLX4_DEV_CAP_FLAG2_VXLAN_OFFLOADS;
	अगर (field & (1 << 5))
		dev_cap->flags2 |= MLX4_DEV_CAP_FLAG2_ETS_CFG;
	MLX4_GET(dev_cap->max_icm_sz, outbox,
		 QUERY_DEV_CAP_MAX_ICM_SZ_OFFSET);
	अगर (dev_cap->flags & MLX4_DEV_CAP_FLAG_COUNTERS)
		MLX4_GET(dev_cap->max_counters, outbox,
			 QUERY_DEV_CAP_MAX_COUNTERS_OFFSET);

	MLX4_GET(field32, outbox,
		 QUERY_DEV_CAP_MAD_DEMUX_OFFSET);
	अगर (field32 & (1 << 0))
		dev_cap->flags2 |= MLX4_DEV_CAP_FLAG2_MAD_DEMUX;

	MLX4_GET(dev_cap->dmfs_high_rate_qpn_base, outbox,
		 QUERY_DEV_CAP_DMFS_HIGH_RATE_QPN_BASE_OFFSET);
	dev_cap->dmfs_high_rate_qpn_base &= MGM_QPN_MASK;
	MLX4_GET(dev_cap->dmfs_high_rate_qpn_range, outbox,
		 QUERY_DEV_CAP_DMFS_HIGH_RATE_QPN_RANGE_OFFSET);
	dev_cap->dmfs_high_rate_qpn_range &= MGM_QPN_MASK;

	MLX4_GET(size, outbox, QUERY_DEV_CAP_QP_RATE_LIMIT_NUM_OFFSET);
	dev_cap->rl_caps.num_rates = size;
	अगर (dev_cap->rl_caps.num_rates) अणु
		dev_cap->flags2 |= MLX4_DEV_CAP_FLAG2_QP_RATE_LIMIT;
		MLX4_GET(size, outbox, QUERY_DEV_CAP_QP_RATE_LIMIT_MAX_OFFSET);
		dev_cap->rl_caps.max_val  = size & 0xfff;
		dev_cap->rl_caps.max_unit = size >> 14;
		MLX4_GET(size, outbox, QUERY_DEV_CAP_QP_RATE_LIMIT_MIN_OFFSET);
		dev_cap->rl_caps.min_val  = size & 0xfff;
		dev_cap->rl_caps.min_unit = size >> 14;
	पूर्ण

	MLX4_GET(dev_cap->health_buffer_addrs, outbox,
		 QUERY_DEV_CAP_HEALTH_BUFFER_ADDRESS_OFFSET);

	MLX4_GET(field32, outbox, QUERY_DEV_CAP_EXT_2_FLAGS_OFFSET);
	अगर (field32 & (1 << 16))
		dev_cap->flags2 |= MLX4_DEV_CAP_FLAG2_UPDATE_QP;
	अगर (field32 & (1 << 18))
		dev_cap->flags2 |= MLX4_DEV_CAP_FLAG2_UPDATE_QP_SRC_CHECK_LB;
	अगर (field32 & (1 << 19))
		dev_cap->flags2 |= MLX4_DEV_CAP_FLAG2_LB_SRC_CHK;
	अगर (field32 & (1 << 26))
		dev_cap->flags2 |= MLX4_DEV_CAP_FLAG2_VLAN_CONTROL;
	अगर (field32 & (1 << 20))
		dev_cap->flags2 |= MLX4_DEV_CAP_FLAG2_FSM;
	अगर (field32 & (1 << 21))
		dev_cap->flags2 |= MLX4_DEV_CAP_FLAG2_80_VFS;
	अगर (field32 & (1 << 23))
		dev_cap->flags2 |= MLX4_DEV_CAP_FLAG2_SW_CQ_INIT;

	क्रम (i = 1; i <= dev_cap->num_ports; i++) अणु
		err = mlx4_QUERY_PORT(dev, i, dev_cap->port_cap + i);
		अगर (err)
			जाओ out;
	पूर्ण

	/*
	 * Each UAR has 4 EQ करोorbells; so अगर a UAR is reserved, then
	 * we can't use any EQs whose करोorbell falls on that page,
	 * even अगर the EQ itself isn't reserved.
	 */
	अगर (dev_cap->num_sys_eqs == 0)
		dev_cap->reserved_eqs = max(dev_cap->reserved_uars * 4,
					    dev_cap->reserved_eqs);
	अन्यथा
		dev_cap->flags2 |= MLX4_DEV_CAP_FLAG2_SYS_EQS;

out:
	mlx4_मुक्त_cmd_mailbox(dev, mailbox);
	वापस err;
पूर्ण

व्योम mlx4_dev_cap_dump(काष्ठा mlx4_dev *dev, काष्ठा mlx4_dev_cap *dev_cap)
अणु
	अगर (dev_cap->bf_reg_size > 0)
		mlx4_dbg(dev, "BlueFlame available (reg size %d, regs/page %d)\n",
			 dev_cap->bf_reg_size, dev_cap->bf_regs_per_page);
	अन्यथा
		mlx4_dbg(dev, "BlueFlame not available\n");

	mlx4_dbg(dev, "Base MM extensions: flags %08x, rsvd L_Key %08x\n",
		 dev_cap->bmme_flags, dev_cap->reserved_lkey);
	mlx4_dbg(dev, "Max ICM size %lld MB\n",
		 (अचिन्हित दीर्घ दीर्घ) dev_cap->max_icm_sz >> 20);
	mlx4_dbg(dev, "Max QPs: %d, reserved QPs: %d, entry size: %d\n",
		 dev_cap->max_qps, dev_cap->reserved_qps, dev_cap->qpc_entry_sz);
	mlx4_dbg(dev, "Max SRQs: %d, reserved SRQs: %d, entry size: %d\n",
		 dev_cap->max_srqs, dev_cap->reserved_srqs, dev_cap->srq_entry_sz);
	mlx4_dbg(dev, "Max CQs: %d, reserved CQs: %d, entry size: %d\n",
		 dev_cap->max_cqs, dev_cap->reserved_cqs, dev_cap->cqc_entry_sz);
	mlx4_dbg(dev, "Num sys EQs: %d, max EQs: %d, reserved EQs: %d, entry size: %d\n",
		 dev_cap->num_sys_eqs, dev_cap->max_eqs, dev_cap->reserved_eqs,
		 dev_cap->eqc_entry_sz);
	mlx4_dbg(dev, "reserved MPTs: %d, reserved MTTs: %d\n",
		 dev_cap->reserved_mrws, dev_cap->reserved_mtts);
	mlx4_dbg(dev, "Max PDs: %d, reserved PDs: %d, reserved UARs: %d\n",
		 dev_cap->max_pds, dev_cap->reserved_pds, dev_cap->reserved_uars);
	mlx4_dbg(dev, "Max QP/MCG: %d, reserved MGMs: %d\n",
		 dev_cap->max_pds, dev_cap->reserved_mgms);
	mlx4_dbg(dev, "Max CQEs: %d, max WQEs: %d, max SRQ WQEs: %d\n",
		 dev_cap->max_cq_sz, dev_cap->max_qp_sz, dev_cap->max_srq_sz);
	mlx4_dbg(dev, "Local CA ACK delay: %d, max MTU: %d, port width cap: %d\n",
		 dev_cap->local_ca_ack_delay, 128 << dev_cap->port_cap[1].ib_mtu,
		 dev_cap->port_cap[1].max_port_width);
	mlx4_dbg(dev, "Max SQ desc size: %d, max SQ S/G: %d\n",
		 dev_cap->max_sq_desc_sz, dev_cap->max_sq_sg);
	mlx4_dbg(dev, "Max RQ desc size: %d, max RQ S/G: %d\n",
		 dev_cap->max_rq_desc_sz, dev_cap->max_rq_sg);
	mlx4_dbg(dev, "Max GSO size: %d\n", dev_cap->max_gso_sz);
	mlx4_dbg(dev, "Max counters: %d\n", dev_cap->max_counters);
	mlx4_dbg(dev, "Max RSS Table size: %d\n", dev_cap->max_rss_tbl_sz);
	mlx4_dbg(dev, "DMFS high rate steer QPn base: %d\n",
		 dev_cap->dmfs_high_rate_qpn_base);
	mlx4_dbg(dev, "DMFS high rate steer QPn range: %d\n",
		 dev_cap->dmfs_high_rate_qpn_range);

	अगर (dev_cap->flags2 & MLX4_DEV_CAP_FLAG2_QP_RATE_LIMIT) अणु
		काष्ठा mlx4_rate_limit_caps *rl_caps = &dev_cap->rl_caps;

		mlx4_dbg(dev, "QP Rate-Limit: #rates %d, unit/val max %d/%d, min %d/%d\n",
			 rl_caps->num_rates, rl_caps->max_unit, rl_caps->max_val,
			 rl_caps->min_unit, rl_caps->min_val);
	पूर्ण

	dump_dev_cap_flags(dev, dev_cap->flags);
	dump_dev_cap_flags2(dev, dev_cap->flags2);
पूर्ण

पूर्णांक mlx4_QUERY_PORT(काष्ठा mlx4_dev *dev, पूर्णांक port, काष्ठा mlx4_port_cap *port_cap)
अणु
	काष्ठा mlx4_cmd_mailbox *mailbox;
	u32 *outbox;
	u8 field;
	u32 field32;
	पूर्णांक err;

	mailbox = mlx4_alloc_cmd_mailbox(dev);
	अगर (IS_ERR(mailbox))
		वापस PTR_ERR(mailbox);
	outbox = mailbox->buf;

	अगर (dev->flags & MLX4_FLAG_OLD_PORT_CMDS) अणु
		err = mlx4_cmd_box(dev, 0, mailbox->dma, 0, 0, MLX4_CMD_QUERY_DEV_CAP,
				   MLX4_CMD_TIME_CLASS_A,
				   MLX4_CMD_NATIVE);

		अगर (err)
			जाओ out;

		MLX4_GET(field, outbox, QUERY_DEV_CAP_VL_PORT_OFFSET);
		port_cap->max_vl	   = field >> 4;
		MLX4_GET(field, outbox, QUERY_DEV_CAP_MTU_WIDTH_OFFSET);
		port_cap->ib_mtu	   = field >> 4;
		port_cap->max_port_width = field & 0xf;
		MLX4_GET(field, outbox, QUERY_DEV_CAP_MAX_GID_OFFSET);
		port_cap->max_gids	   = 1 << (field & 0xf);
		MLX4_GET(field, outbox, QUERY_DEV_CAP_MAX_PKEY_OFFSET);
		port_cap->max_pkeys	   = 1 << (field & 0xf);
	पूर्ण अन्यथा अणु
#घोषणा QUERY_PORT_SUPPORTED_TYPE_OFFSET	0x00
#घोषणा QUERY_PORT_MTU_OFFSET			0x01
#घोषणा QUERY_PORT_ETH_MTU_OFFSET		0x02
#घोषणा QUERY_PORT_WIDTH_OFFSET			0x06
#घोषणा QUERY_PORT_MAX_GID_PKEY_OFFSET		0x07
#घोषणा QUERY_PORT_MAX_MACVLAN_OFFSET		0x0a
#घोषणा QUERY_PORT_MAX_VL_OFFSET		0x0b
#घोषणा QUERY_PORT_MAC_OFFSET			0x10
#घोषणा QUERY_PORT_TRANS_VENDOR_OFFSET		0x18
#घोषणा QUERY_PORT_WAVELENGTH_OFFSET		0x1c
#घोषणा QUERY_PORT_TRANS_CODE_OFFSET		0x20

		err = mlx4_cmd_box(dev, 0, mailbox->dma, port, 0, MLX4_CMD_QUERY_PORT,
				   MLX4_CMD_TIME_CLASS_B, MLX4_CMD_NATIVE);
		अगर (err)
			जाओ out;

		MLX4_GET(field, outbox, QUERY_PORT_SUPPORTED_TYPE_OFFSET);
		port_cap->link_state = (field & 0x80) >> 7;
		port_cap->supported_port_types = field & 3;
		port_cap->suggested_type = (field >> 3) & 1;
		port_cap->शेष_sense = (field >> 4) & 1;
		port_cap->dmfs_optimized_state = (field >> 5) & 1;
		MLX4_GET(field, outbox, QUERY_PORT_MTU_OFFSET);
		port_cap->ib_mtu	   = field & 0xf;
		MLX4_GET(field, outbox, QUERY_PORT_WIDTH_OFFSET);
		port_cap->max_port_width = field & 0xf;
		MLX4_GET(field, outbox, QUERY_PORT_MAX_GID_PKEY_OFFSET);
		port_cap->max_gids	   = 1 << (field >> 4);
		port_cap->max_pkeys	   = 1 << (field & 0xf);
		MLX4_GET(field, outbox, QUERY_PORT_MAX_VL_OFFSET);
		port_cap->max_vl	   = field & 0xf;
		port_cap->max_tc_eth	   = field >> 4;
		MLX4_GET(field, outbox, QUERY_PORT_MAX_MACVLAN_OFFSET);
		port_cap->log_max_macs  = field & 0xf;
		port_cap->log_max_vlans = field >> 4;
		MLX4_GET(port_cap->eth_mtu, outbox, QUERY_PORT_ETH_MTU_OFFSET);
		MLX4_GET(port_cap->def_mac, outbox, QUERY_PORT_MAC_OFFSET);
		MLX4_GET(field32, outbox, QUERY_PORT_TRANS_VENDOR_OFFSET);
		port_cap->trans_type = field32 >> 24;
		port_cap->venकरोr_oui = field32 & 0xffffff;
		MLX4_GET(port_cap->wavelength, outbox, QUERY_PORT_WAVELENGTH_OFFSET);
		MLX4_GET(port_cap->trans_code, outbox, QUERY_PORT_TRANS_CODE_OFFSET);
	पूर्ण

out:
	mlx4_मुक्त_cmd_mailbox(dev, mailbox);
	वापस err;
पूर्ण

#घोषणा DEV_CAP_EXT_2_FLAG_PFC_COUNTERS	(1 << 28)
#घोषणा DEV_CAP_EXT_2_FLAG_VLAN_CONTROL (1 << 26)
#घोषणा DEV_CAP_EXT_2_FLAG_80_VFS	(1 << 21)
#घोषणा DEV_CAP_EXT_2_FLAG_FSM		(1 << 20)

पूर्णांक mlx4_QUERY_DEV_CAP_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			       काष्ठा mlx4_vhcr *vhcr,
			       काष्ठा mlx4_cmd_mailbox *inbox,
			       काष्ठा mlx4_cmd_mailbox *outbox,
			       काष्ठा mlx4_cmd_info *cmd)
अणु
	u64	flags;
	पूर्णांक	err = 0;
	u8	field;
	u16	field16;
	u32	bmme_flags, field32;
	पूर्णांक	real_port;
	पूर्णांक	slave_port;
	पूर्णांक	first_port;
	काष्ठा mlx4_active_ports actv_ports;

	err = mlx4_cmd_box(dev, 0, outbox->dma, 0, 0, MLX4_CMD_QUERY_DEV_CAP,
			   MLX4_CMD_TIME_CLASS_A, MLX4_CMD_NATIVE);
	अगर (err)
		वापस err;

	disable_unsupported_roce_caps(outbox->buf);
	/* add port mng change event capability and disable mw type 1
	 * unconditionally to slaves
	 */
	MLX4_GET(flags, outbox->buf, QUERY_DEV_CAP_EXT_FLAGS_OFFSET);
	flags |= MLX4_DEV_CAP_FLAG_PORT_MNG_CHG_EV;
	flags &= ~MLX4_DEV_CAP_FLAG_MEM_WINDOW;
	actv_ports = mlx4_get_active_ports(dev, slave);
	first_port = find_first_bit(actv_ports.ports, dev->caps.num_ports);
	क्रम (slave_port = 0, real_port = first_port;
	     real_port < first_port +
	     biपंचांगap_weight(actv_ports.ports, dev->caps.num_ports);
	     ++real_port, ++slave_port) अणु
		अगर (flags & (MLX4_DEV_CAP_FLAG_WOL_PORT1 << real_port))
			flags |= MLX4_DEV_CAP_FLAG_WOL_PORT1 << slave_port;
		अन्यथा
			flags &= ~(MLX4_DEV_CAP_FLAG_WOL_PORT1 << slave_port);
	पूर्ण
	क्रम (; slave_port < dev->caps.num_ports; ++slave_port)
		flags &= ~(MLX4_DEV_CAP_FLAG_WOL_PORT1 << slave_port);

	/* Not exposing RSS IP fragments to guests */
	flags &= ~MLX4_DEV_CAP_FLAG_RSS_IP_FRAG;
	MLX4_PUT(outbox->buf, flags, QUERY_DEV_CAP_EXT_FLAGS_OFFSET);

	MLX4_GET(field, outbox->buf, QUERY_DEV_CAP_VL_PORT_OFFSET);
	field &= ~0x0F;
	field |= biपंचांगap_weight(actv_ports.ports, dev->caps.num_ports) & 0x0F;
	MLX4_PUT(outbox->buf, field, QUERY_DEV_CAP_VL_PORT_OFFSET);

	/* For guests, disable बारtamp */
	MLX4_GET(field, outbox->buf, QUERY_DEV_CAP_CQ_TS_SUPPORT_OFFSET);
	field &= 0x7f;
	MLX4_PUT(outbox->buf, field, QUERY_DEV_CAP_CQ_TS_SUPPORT_OFFSET);

	/* For guests, disable vxlan tunneling and QoS support */
	MLX4_GET(field, outbox->buf, QUERY_DEV_CAP_VXLAN);
	field &= 0xd7;
	MLX4_PUT(outbox->buf, field, QUERY_DEV_CAP_VXLAN);

	/* For guests, disable port BEACON */
	MLX4_GET(field, outbox->buf, QUERY_DEV_CAP_PORT_BEACON_OFFSET);
	field &= 0x7f;
	MLX4_PUT(outbox->buf, field, QUERY_DEV_CAP_PORT_BEACON_OFFSET);

	/* For guests, report Blueflame disabled */
	MLX4_GET(field, outbox->buf, QUERY_DEV_CAP_BF_OFFSET);
	field &= 0x7f;
	MLX4_PUT(outbox->buf, field, QUERY_DEV_CAP_BF_OFFSET);

	/* For guests, disable mw type 2 and port remap*/
	MLX4_GET(bmme_flags, outbox->buf, QUERY_DEV_CAP_BMME_FLAGS_OFFSET);
	bmme_flags &= ~MLX4_BMME_FLAG_TYPE_2_WIN;
	bmme_flags &= ~MLX4_FLAG_PORT_REMAP;
	MLX4_PUT(outbox->buf, bmme_flags, QUERY_DEV_CAP_BMME_FLAGS_OFFSET);

	/* turn off device-managed steering capability अगर not enabled */
	अगर (dev->caps.steering_mode != MLX4_STEERING_MODE_DEVICE_MANAGED) अणु
		MLX4_GET(field, outbox->buf,
			 QUERY_DEV_CAP_FLOW_STEERING_RANGE_EN_OFFSET);
		field &= 0x7f;
		MLX4_PUT(outbox->buf, field,
			 QUERY_DEV_CAP_FLOW_STEERING_RANGE_EN_OFFSET);
	पूर्ण

	/* turn off ipoib managed steering क्रम guests */
	MLX4_GET(field, outbox->buf, QUERY_DEV_CAP_FLOW_STEERING_IPOIB_OFFSET);
	field &= ~0x80;
	MLX4_PUT(outbox->buf, field, QUERY_DEV_CAP_FLOW_STEERING_IPOIB_OFFSET);

	/* turn off host side virt features (VST, FSM, etc) क्रम guests */
	MLX4_GET(field32, outbox->buf, QUERY_DEV_CAP_EXT_2_FLAGS_OFFSET);
	field32 &= ~(DEV_CAP_EXT_2_FLAG_VLAN_CONTROL | DEV_CAP_EXT_2_FLAG_80_VFS |
		     DEV_CAP_EXT_2_FLAG_FSM | DEV_CAP_EXT_2_FLAG_PFC_COUNTERS);
	MLX4_PUT(outbox->buf, field32, QUERY_DEV_CAP_EXT_2_FLAGS_OFFSET);

	/* turn off QCN क्रम guests */
	MLX4_GET(field, outbox->buf, QUERY_DEV_CAP_ECN_QCN_VER_OFFSET);
	field &= 0xfe;
	MLX4_PUT(outbox->buf, field, QUERY_DEV_CAP_ECN_QCN_VER_OFFSET);

	/* turn off QP max-rate limiting क्रम guests */
	field16 = 0;
	MLX4_PUT(outbox->buf, field16, QUERY_DEV_CAP_QP_RATE_LIMIT_NUM_OFFSET);

	/* turn off QoS per VF support क्रम guests */
	MLX4_GET(field, outbox->buf, QUERY_DEV_CAP_CQ_EQ_CACHE_LINE_STRIDE);
	field &= 0xef;
	MLX4_PUT(outbox->buf, field, QUERY_DEV_CAP_CQ_EQ_CACHE_LINE_STRIDE);

	/* turn off ignore FCS feature क्रम guests */
	MLX4_GET(field, outbox->buf, QUERY_DEV_CAP_CONFIG_DEV_OFFSET);
	field &= 0xfb;
	MLX4_PUT(outbox->buf, field, QUERY_DEV_CAP_CONFIG_DEV_OFFSET);

	वापस 0;
पूर्ण

अटल व्योम disable_unsupported_roce_caps(व्योम *buf)
अणु
	u32 flags;

	MLX4_GET(flags, buf, QUERY_DEV_CAP_EXT_FLAGS_OFFSET);
	flags &= ~(1UL << 31);
	MLX4_PUT(buf, flags, QUERY_DEV_CAP_EXT_FLAGS_OFFSET);
	MLX4_GET(flags, buf, QUERY_DEV_CAP_EXT_2_FLAGS_OFFSET);
	flags &= ~(1UL << 24);
	MLX4_PUT(buf, flags, QUERY_DEV_CAP_EXT_2_FLAGS_OFFSET);
	MLX4_GET(flags, buf, QUERY_DEV_CAP_BMME_FLAGS_OFFSET);
	flags &= ~(MLX4_FLAG_ROCE_V1_V2);
	MLX4_PUT(buf, flags, QUERY_DEV_CAP_BMME_FLAGS_OFFSET);
पूर्ण

पूर्णांक mlx4_QUERY_PORT_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			    काष्ठा mlx4_vhcr *vhcr,
			    काष्ठा mlx4_cmd_mailbox *inbox,
			    काष्ठा mlx4_cmd_mailbox *outbox,
			    काष्ठा mlx4_cmd_info *cmd)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	u64 def_mac;
	u8 port_type;
	u16 लघु_field;
	पूर्णांक err;
	पूर्णांक admin_link_state;
	पूर्णांक port = mlx4_slave_convert_port(dev, slave,
					   vhcr->in_modअगरier & 0xFF);

#घोषणा MLX4_VF_PORT_NO_LINK_SENSE_MASK	0xE0
#घोषणा MLX4_PORT_LINK_UP_MASK		0x80
#घोषणा QUERY_PORT_CUR_MAX_PKEY_OFFSET	0x0c
#घोषणा QUERY_PORT_CUR_MAX_GID_OFFSET	0x0e

	अगर (port < 0)
		वापस -EINVAL;

	/* Protect against untrusted guests: enक्रमce that this is the
	 * QUERY_PORT general query.
	 */
	अगर (vhcr->op_modअगरier || vhcr->in_modअगरier & ~0xFF)
		वापस -EINVAL;

	vhcr->in_modअगरier = port;

	err = mlx4_cmd_box(dev, 0, outbox->dma, vhcr->in_modअगरier, 0,
			   MLX4_CMD_QUERY_PORT, MLX4_CMD_TIME_CLASS_B,
			   MLX4_CMD_NATIVE);

	अगर (!err && dev->caps.function != slave) अणु
		def_mac = priv->mfunc.master.vf_oper[slave].vport[vhcr->in_modअगरier].state.mac;
		MLX4_PUT(outbox->buf, def_mac, QUERY_PORT_MAC_OFFSET);

		/* get port type - currently only eth is enabled */
		MLX4_GET(port_type, outbox->buf,
			 QUERY_PORT_SUPPORTED_TYPE_OFFSET);

		/* No link sensing allowed */
		port_type &= MLX4_VF_PORT_NO_LINK_SENSE_MASK;
		/* set port type to currently operating port type */
		port_type |= (dev->caps.port_type[vhcr->in_modअगरier] & 0x3);

		admin_link_state = priv->mfunc.master.vf_oper[slave].vport[vhcr->in_modअगरier].state.link_state;
		अगर (IFLA_VF_LINK_STATE_ENABLE == admin_link_state)
			port_type |= MLX4_PORT_LINK_UP_MASK;
		अन्यथा अगर (IFLA_VF_LINK_STATE_DISABLE == admin_link_state)
			port_type &= ~MLX4_PORT_LINK_UP_MASK;
		अन्यथा अगर (IFLA_VF_LINK_STATE_AUTO == admin_link_state && mlx4_is_bonded(dev)) अणु
			पूर्णांक other_port = (port == 1) ? 2 : 1;
			काष्ठा mlx4_port_cap port_cap;

			err = mlx4_QUERY_PORT(dev, other_port, &port_cap);
			अगर (err)
				जाओ out;
			port_type |= (port_cap.link_state << 7);
		पूर्ण

		MLX4_PUT(outbox->buf, port_type,
			 QUERY_PORT_SUPPORTED_TYPE_OFFSET);

		अगर (dev->caps.port_type[vhcr->in_modअगरier] == MLX4_PORT_TYPE_ETH)
			लघु_field = mlx4_get_slave_num_gids(dev, slave, port);
		अन्यथा
			लघु_field = 1; /* slave max gids */
		MLX4_PUT(outbox->buf, लघु_field,
			 QUERY_PORT_CUR_MAX_GID_OFFSET);

		लघु_field = dev->caps.pkey_table_len[vhcr->in_modअगरier];
		MLX4_PUT(outbox->buf, लघु_field,
			 QUERY_PORT_CUR_MAX_PKEY_OFFSET);
	पूर्ण
out:
	वापस err;
पूर्ण

पूर्णांक mlx4_get_slave_pkey_gid_tbl_len(काष्ठा mlx4_dev *dev, u8 port,
				    पूर्णांक *gid_tbl_len, पूर्णांक *pkey_tbl_len)
अणु
	काष्ठा mlx4_cmd_mailbox *mailbox;
	u32			*outbox;
	u16			field;
	पूर्णांक			err;

	mailbox = mlx4_alloc_cmd_mailbox(dev);
	अगर (IS_ERR(mailbox))
		वापस PTR_ERR(mailbox);

	err =  mlx4_cmd_box(dev, 0, mailbox->dma, port, 0,
			    MLX4_CMD_QUERY_PORT, MLX4_CMD_TIME_CLASS_B,
			    MLX4_CMD_WRAPPED);
	अगर (err)
		जाओ out;

	outbox = mailbox->buf;

	MLX4_GET(field, outbox, QUERY_PORT_CUR_MAX_GID_OFFSET);
	*gid_tbl_len = field;

	MLX4_GET(field, outbox, QUERY_PORT_CUR_MAX_PKEY_OFFSET);
	*pkey_tbl_len = field;

out:
	mlx4_मुक्त_cmd_mailbox(dev, mailbox);
	वापस err;
पूर्ण
EXPORT_SYMBOL(mlx4_get_slave_pkey_gid_tbl_len);

पूर्णांक mlx4_map_cmd(काष्ठा mlx4_dev *dev, u16 op, काष्ठा mlx4_icm *icm, u64 virt)
अणु
	काष्ठा mlx4_cmd_mailbox *mailbox;
	काष्ठा mlx4_icm_iter iter;
	__be64 *pages;
	पूर्णांक lg;
	पूर्णांक nent = 0;
	पूर्णांक i;
	पूर्णांक err = 0;
	पूर्णांक ts = 0, tc = 0;

	mailbox = mlx4_alloc_cmd_mailbox(dev);
	अगर (IS_ERR(mailbox))
		वापस PTR_ERR(mailbox);
	pages = mailbox->buf;

	क्रम (mlx4_icm_first(icm, &iter);
	     !mlx4_icm_last(&iter);
	     mlx4_icm_next(&iter)) अणु
		/*
		 * We have to pass pages that are aligned to their
		 * size, so find the least signअगरicant 1 in the
		 * address or size and use that as our log2 size.
		 */
		lg = ffs(mlx4_icm_addr(&iter) | mlx4_icm_size(&iter)) - 1;
		अगर (lg < MLX4_ICM_PAGE_SHIFT) अणु
			mlx4_warn(dev, "Got FW area not aligned to %d (%llx/%lx)\n",
				  MLX4_ICM_PAGE_SIZE,
				  (अचिन्हित दीर्घ दीर्घ) mlx4_icm_addr(&iter),
				  mlx4_icm_size(&iter));
			err = -EINVAL;
			जाओ out;
		पूर्ण

		क्रम (i = 0; i < mlx4_icm_size(&iter) >> lg; ++i) अणु
			अगर (virt != -1) अणु
				pages[nent * 2] = cpu_to_be64(virt);
				virt += 1ULL << lg;
			पूर्ण

			pages[nent * 2 + 1] =
				cpu_to_be64((mlx4_icm_addr(&iter) + (i << lg)) |
					    (lg - MLX4_ICM_PAGE_SHIFT));
			ts += 1 << (lg - 10);
			++tc;

			अगर (++nent == MLX4_MAILBOX_SIZE / 16) अणु
				err = mlx4_cmd(dev, mailbox->dma, nent, 0, op,
						MLX4_CMD_TIME_CLASS_B,
						MLX4_CMD_NATIVE);
				अगर (err)
					जाओ out;
				nent = 0;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (nent)
		err = mlx4_cmd(dev, mailbox->dma, nent, 0, op,
			       MLX4_CMD_TIME_CLASS_B, MLX4_CMD_NATIVE);
	अगर (err)
		जाओ out;

	चयन (op) अणु
	हाल MLX4_CMD_MAP_FA:
		mlx4_dbg(dev, "Mapped %d chunks/%d KB for FW\n", tc, ts);
		अवरोध;
	हाल MLX4_CMD_MAP_ICM_AUX:
		mlx4_dbg(dev, "Mapped %d chunks/%d KB for ICM aux\n", tc, ts);
		अवरोध;
	हाल MLX4_CMD_MAP_ICM:
		mlx4_dbg(dev, "Mapped %d chunks/%d KB at %llx for ICM\n",
			 tc, ts, (अचिन्हित दीर्घ दीर्घ) virt - (ts << 10));
		अवरोध;
	पूर्ण

out:
	mlx4_मुक्त_cmd_mailbox(dev, mailbox);
	वापस err;
पूर्ण

पूर्णांक mlx4_MAP_FA(काष्ठा mlx4_dev *dev, काष्ठा mlx4_icm *icm)
अणु
	वापस mlx4_map_cmd(dev, MLX4_CMD_MAP_FA, icm, -1);
पूर्ण

पूर्णांक mlx4_UNMAP_FA(काष्ठा mlx4_dev *dev)
अणु
	वापस mlx4_cmd(dev, 0, 0, 0, MLX4_CMD_UNMAP_FA,
			MLX4_CMD_TIME_CLASS_B, MLX4_CMD_NATIVE);
पूर्ण


पूर्णांक mlx4_RUN_FW(काष्ठा mlx4_dev *dev)
अणु
	वापस mlx4_cmd(dev, 0, 0, 0, MLX4_CMD_RUN_FW,
			MLX4_CMD_TIME_CLASS_A, MLX4_CMD_NATIVE);
पूर्ण

पूर्णांक mlx4_QUERY_FW(काष्ठा mlx4_dev *dev)
अणु
	काष्ठा mlx4_fw  *fw  = &mlx4_priv(dev)->fw;
	काष्ठा mlx4_cmd *cmd = &mlx4_priv(dev)->cmd;
	काष्ठा mlx4_cmd_mailbox *mailbox;
	u32 *outbox;
	पूर्णांक err = 0;
	u64 fw_ver;
	u16 cmd_अगर_rev;
	u8 lg;

#घोषणा QUERY_FW_OUT_SIZE             0x100
#घोषणा QUERY_FW_VER_OFFSET            0x00
#घोषणा QUERY_FW_PPF_ID		       0x09
#घोषणा QUERY_FW_CMD_IF_REV_OFFSET     0x0a
#घोषणा QUERY_FW_MAX_CMD_OFFSET        0x0f
#घोषणा QUERY_FW_ERR_START_OFFSET      0x30
#घोषणा QUERY_FW_ERR_SIZE_OFFSET       0x38
#घोषणा QUERY_FW_ERR_BAR_OFFSET        0x3c

#घोषणा QUERY_FW_SIZE_OFFSET           0x00
#घोषणा QUERY_FW_CLR_INT_BASE_OFFSET   0x20
#घोषणा QUERY_FW_CLR_INT_BAR_OFFSET    0x28

#घोषणा QUERY_FW_COMM_BASE_OFFSET      0x40
#घोषणा QUERY_FW_COMM_BAR_OFFSET       0x48

#घोषणा QUERY_FW_CLOCK_OFFSET	       0x50
#घोषणा QUERY_FW_CLOCK_BAR	       0x58

	mailbox = mlx4_alloc_cmd_mailbox(dev);
	अगर (IS_ERR(mailbox))
		वापस PTR_ERR(mailbox);
	outbox = mailbox->buf;

	err = mlx4_cmd_box(dev, 0, mailbox->dma, 0, 0, MLX4_CMD_QUERY_FW,
			    MLX4_CMD_TIME_CLASS_A, MLX4_CMD_NATIVE);
	अगर (err)
		जाओ out;

	MLX4_GET(fw_ver, outbox, QUERY_FW_VER_OFFSET);
	/*
	 * FW subminor version is at more signअगरicant bits than minor
	 * version, so swap here.
	 */
	dev->caps.fw_ver = (fw_ver & 0xffff00000000ull) |
		((fw_ver & 0xffff0000ull) >> 16) |
		((fw_ver & 0x0000ffffull) << 16);

	MLX4_GET(lg, outbox, QUERY_FW_PPF_ID);
	dev->caps.function = lg;

	अगर (mlx4_is_slave(dev))
		जाओ out;


	MLX4_GET(cmd_अगर_rev, outbox, QUERY_FW_CMD_IF_REV_OFFSET);
	अगर (cmd_अगर_rev < MLX4_COMMAND_INTERFACE_MIN_REV ||
	    cmd_अगर_rev > MLX4_COMMAND_INTERFACE_MAX_REV) अणु
		mlx4_err(dev, "Installed FW has unsupported command interface revision %d\n",
			 cmd_अगर_rev);
		mlx4_err(dev, "(Installed FW version is %d.%d.%03d)\n",
			 (पूर्णांक) (dev->caps.fw_ver >> 32),
			 (पूर्णांक) (dev->caps.fw_ver >> 16) & 0xffff,
			 (पूर्णांक) dev->caps.fw_ver & 0xffff);
		mlx4_err(dev, "This driver version supports only revisions %d to %d\n",
			 MLX4_COMMAND_INTERFACE_MIN_REV, MLX4_COMMAND_INTERFACE_MAX_REV);
		err = -ENODEV;
		जाओ out;
	पूर्ण

	अगर (cmd_अगर_rev < MLX4_COMMAND_INTERFACE_NEW_PORT_CMDS)
		dev->flags |= MLX4_FLAG_OLD_PORT_CMDS;

	MLX4_GET(lg, outbox, QUERY_FW_MAX_CMD_OFFSET);
	cmd->max_cmds = 1 << lg;

	mlx4_dbg(dev, "FW version %d.%d.%03d (cmd intf rev %d), max commands %d\n",
		 (पूर्णांक) (dev->caps.fw_ver >> 32),
		 (पूर्णांक) (dev->caps.fw_ver >> 16) & 0xffff,
		 (पूर्णांक) dev->caps.fw_ver & 0xffff,
		 cmd_अगर_rev, cmd->max_cmds);

	MLX4_GET(fw->catas_offset, outbox, QUERY_FW_ERR_START_OFFSET);
	MLX4_GET(fw->catas_size,   outbox, QUERY_FW_ERR_SIZE_OFFSET);
	MLX4_GET(fw->catas_bar,    outbox, QUERY_FW_ERR_BAR_OFFSET);
	fw->catas_bar = (fw->catas_bar >> 6) * 2;

	mlx4_dbg(dev, "Catastrophic error buffer at 0x%llx, size 0x%x, BAR %d\n",
		 (अचिन्हित दीर्घ दीर्घ) fw->catas_offset, fw->catas_size, fw->catas_bar);

	MLX4_GET(fw->fw_pages,     outbox, QUERY_FW_SIZE_OFFSET);
	MLX4_GET(fw->clr_पूर्णांक_base, outbox, QUERY_FW_CLR_INT_BASE_OFFSET);
	MLX4_GET(fw->clr_पूर्णांक_bar,  outbox, QUERY_FW_CLR_INT_BAR_OFFSET);
	fw->clr_पूर्णांक_bar = (fw->clr_पूर्णांक_bar >> 6) * 2;

	MLX4_GET(fw->comm_base, outbox, QUERY_FW_COMM_BASE_OFFSET);
	MLX4_GET(fw->comm_bar,  outbox, QUERY_FW_COMM_BAR_OFFSET);
	fw->comm_bar = (fw->comm_bar >> 6) * 2;
	mlx4_dbg(dev, "Communication vector bar:%d offset:0x%llx\n",
		 fw->comm_bar, fw->comm_base);
	mlx4_dbg(dev, "FW size %d KB\n", fw->fw_pages >> 2);

	MLX4_GET(fw->घड़ी_offset, outbox, QUERY_FW_CLOCK_OFFSET);
	MLX4_GET(fw->घड़ी_bar,    outbox, QUERY_FW_CLOCK_BAR);
	fw->घड़ी_bar = (fw->घड़ी_bar >> 6) * 2;
	mlx4_dbg(dev, "Internal clock bar:%d offset:0x%llx\n",
		 fw->घड़ी_bar, fw->घड़ी_offset);

	/*
	 * Round up number of प्रणाली pages needed in हाल
	 * MLX4_ICM_PAGE_SIZE < PAGE_SIZE.
	 */
	fw->fw_pages =
		ALIGN(fw->fw_pages, PAGE_SIZE / MLX4_ICM_PAGE_SIZE) >>
		(PAGE_SHIFT - MLX4_ICM_PAGE_SHIFT);

	mlx4_dbg(dev, "Clear int @ %llx, BAR %d\n",
		 (अचिन्हित दीर्घ दीर्घ) fw->clr_पूर्णांक_base, fw->clr_पूर्णांक_bar);

out:
	mlx4_मुक्त_cmd_mailbox(dev, mailbox);
	वापस err;
पूर्ण

पूर्णांक mlx4_QUERY_FW_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			  काष्ठा mlx4_vhcr *vhcr,
			  काष्ठा mlx4_cmd_mailbox *inbox,
			  काष्ठा mlx4_cmd_mailbox *outbox,
			  काष्ठा mlx4_cmd_info *cmd)
अणु
	u8 *outbuf;
	पूर्णांक err;

	outbuf = outbox->buf;
	err = mlx4_cmd_box(dev, 0, outbox->dma, 0, 0, MLX4_CMD_QUERY_FW,
			    MLX4_CMD_TIME_CLASS_A, MLX4_CMD_NATIVE);
	अगर (err)
		वापस err;

	/* क्रम slaves, set pci PPF ID to invalid and zero out everything
	 * अन्यथा except FW version */
	outbuf[0] = outbuf[1] = 0;
	स_रखो(&outbuf[8], 0, QUERY_FW_OUT_SIZE - 8);
	outbuf[QUERY_FW_PPF_ID] = MLX4_INVALID_SLAVE_ID;

	वापस 0;
पूर्ण

अटल व्योम get_board_id(व्योम *vsd, अक्षर *board_id)
अणु
	पूर्णांक i;

#घोषणा VSD_OFFSET_SIG1		0x00
#घोषणा VSD_OFFSET_SIG2		0xde
#घोषणा VSD_OFFSET_MLX_BOARD_ID	0xd0
#घोषणा VSD_OFFSET_TS_BOARD_ID	0x20

#घोषणा VSD_SIGNATURE_TOPSPIN	0x5ad

	स_रखो(board_id, 0, MLX4_BOARD_ID_LEN);

	अगर (be16_to_cpup(vsd + VSD_OFFSET_SIG1) == VSD_SIGNATURE_TOPSPIN &&
	    be16_to_cpup(vsd + VSD_OFFSET_SIG2) == VSD_SIGNATURE_TOPSPIN) अणु
		strlcpy(board_id, vsd + VSD_OFFSET_TS_BOARD_ID, MLX4_BOARD_ID_LEN);
	पूर्ण अन्यथा अणु
		/*
		 * The board ID is a string but the firmware byte
		 * swaps each 4-byte word beक्रमe passing it back to
		 * us.  Thereक्रमe we need to swab it beक्रमe prपूर्णांकing.
		 */
		u32 *bid_u32 = (u32 *)board_id;

		क्रम (i = 0; i < 4; ++i) अणु
			u32 *addr;
			u32 val;

			addr = (u32 *) (vsd + VSD_OFFSET_MLX_BOARD_ID + i * 4);
			val = get_unaligned(addr);
			val = swab32(val);
			put_unaligned(val, &bid_u32[i]);
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक mlx4_QUERY_ADAPTER(काष्ठा mlx4_dev *dev, काष्ठा mlx4_adapter *adapter)
अणु
	काष्ठा mlx4_cmd_mailbox *mailbox;
	u32 *outbox;
	पूर्णांक err;

#घोषणा QUERY_ADAPTER_OUT_SIZE             0x100
#घोषणा QUERY_ADAPTER_INTA_PIN_OFFSET      0x10
#घोषणा QUERY_ADAPTER_VSD_OFFSET           0x20

	mailbox = mlx4_alloc_cmd_mailbox(dev);
	अगर (IS_ERR(mailbox))
		वापस PTR_ERR(mailbox);
	outbox = mailbox->buf;

	err = mlx4_cmd_box(dev, 0, mailbox->dma, 0, 0, MLX4_CMD_QUERY_ADAPTER,
			   MLX4_CMD_TIME_CLASS_A, MLX4_CMD_NATIVE);
	अगर (err)
		जाओ out;

	MLX4_GET(adapter->पूर्णांकa_pin, outbox,    QUERY_ADAPTER_INTA_PIN_OFFSET);

	get_board_id(outbox + QUERY_ADAPTER_VSD_OFFSET / 4,
		     adapter->board_id);

out:
	mlx4_मुक्त_cmd_mailbox(dev, mailbox);
	वापस err;
पूर्ण

पूर्णांक mlx4_INIT_HCA(काष्ठा mlx4_dev *dev, काष्ठा mlx4_init_hca_param *param)
अणु
	काष्ठा mlx4_cmd_mailbox *mailbox;
	__be32 *inbox;
	पूर्णांक err;
	अटल स्थिर u8 a0_dmfs_hw_steering[] =  अणु
		[MLX4_STEERING_DMFS_A0_DEFAULT]		= 0,
		[MLX4_STEERING_DMFS_A0_DYNAMIC]		= 1,
		[MLX4_STEERING_DMFS_A0_STATIC]		= 2,
		[MLX4_STEERING_DMFS_A0_DISABLE]		= 3
	पूर्ण;

#घोषणा INIT_HCA_IN_SIZE		 0x200
#घोषणा INIT_HCA_VERSION_OFFSET		 0x000
#घोषणा	 INIT_HCA_VERSION		 2
#घोषणा INIT_HCA_VXLAN_OFFSET		 0x0c
#घोषणा INIT_HCA_CACHELINE_SZ_OFFSET	 0x0e
#घोषणा INIT_HCA_FLAGS_OFFSET		 0x014
#घोषणा INIT_HCA_RECOVERABLE_ERROR_EVENT_OFFSET 0x018
#घोषणा INIT_HCA_QPC_OFFSET		 0x020
#घोषणा	 INIT_HCA_QPC_BASE_OFFSET	 (INIT_HCA_QPC_OFFSET + 0x10)
#घोषणा	 INIT_HCA_LOG_QP_OFFSET		 (INIT_HCA_QPC_OFFSET + 0x17)
#घोषणा	 INIT_HCA_SRQC_BASE_OFFSET	 (INIT_HCA_QPC_OFFSET + 0x28)
#घोषणा	 INIT_HCA_LOG_SRQ_OFFSET	 (INIT_HCA_QPC_OFFSET + 0x2f)
#घोषणा	 INIT_HCA_CQC_BASE_OFFSET	 (INIT_HCA_QPC_OFFSET + 0x30)
#घोषणा	 INIT_HCA_LOG_CQ_OFFSET		 (INIT_HCA_QPC_OFFSET + 0x37)
#घोषणा	 INIT_HCA_EQE_CQE_OFFSETS	 (INIT_HCA_QPC_OFFSET + 0x38)
#घोषणा	 INIT_HCA_EQE_CQE_STRIDE_OFFSET  (INIT_HCA_QPC_OFFSET + 0x3b)
#घोषणा	 INIT_HCA_ALTC_BASE_OFFSET	 (INIT_HCA_QPC_OFFSET + 0x40)
#घोषणा	 INIT_HCA_AUXC_BASE_OFFSET	 (INIT_HCA_QPC_OFFSET + 0x50)
#घोषणा	 INIT_HCA_EQC_BASE_OFFSET	 (INIT_HCA_QPC_OFFSET + 0x60)
#घोषणा	 INIT_HCA_LOG_EQ_OFFSET		 (INIT_HCA_QPC_OFFSET + 0x67)
#घोषणा	INIT_HCA_NUM_SYS_EQS_OFFSET	(INIT_HCA_QPC_OFFSET + 0x6a)
#घोषणा	 INIT_HCA_RDMARC_BASE_OFFSET	 (INIT_HCA_QPC_OFFSET + 0x70)
#घोषणा	 INIT_HCA_LOG_RD_OFFSET		 (INIT_HCA_QPC_OFFSET + 0x77)
#घोषणा INIT_HCA_MCAST_OFFSET		 0x0c0
#घोषणा	 INIT_HCA_MC_BASE_OFFSET	 (INIT_HCA_MCAST_OFFSET + 0x00)
#घोषणा	 INIT_HCA_LOG_MC_ENTRY_SZ_OFFSET (INIT_HCA_MCAST_OFFSET + 0x13)
#घोषणा	 INIT_HCA_LOG_MC_HASH_SZ_OFFSET	 (INIT_HCA_MCAST_OFFSET + 0x17)
#घोषणा  INIT_HCA_UC_STEERING_OFFSET	 (INIT_HCA_MCAST_OFFSET + 0x18)
#घोषणा	 INIT_HCA_LOG_MC_TABLE_SZ_OFFSET (INIT_HCA_MCAST_OFFSET + 0x1b)
#घोषणा  INIT_HCA_DEVICE_MANAGED_FLOW_STEERING_EN	0x6
#घोषणा  INIT_HCA_DRIVER_VERSION_OFFSET   0x140
#घोषणा  INIT_HCA_DRIVER_VERSION_SZ       0x40
#घोषणा  INIT_HCA_FS_PARAM_OFFSET         0x1d0
#घोषणा  INIT_HCA_FS_BASE_OFFSET          (INIT_HCA_FS_PARAM_OFFSET + 0x00)
#घोषणा  INIT_HCA_FS_LOG_ENTRY_SZ_OFFSET  (INIT_HCA_FS_PARAM_OFFSET + 0x13)
#घोषणा  INIT_HCA_FS_A0_OFFSET		  (INIT_HCA_FS_PARAM_OFFSET + 0x18)
#घोषणा  INIT_HCA_FS_LOG_TABLE_SZ_OFFSET  (INIT_HCA_FS_PARAM_OFFSET + 0x1b)
#घोषणा  INIT_HCA_FS_ETH_BITS_OFFSET      (INIT_HCA_FS_PARAM_OFFSET + 0x21)
#घोषणा  INIT_HCA_FS_ETH_NUM_ADDRS_OFFSET (INIT_HCA_FS_PARAM_OFFSET + 0x22)
#घोषणा  INIT_HCA_FS_IB_BITS_OFFSET       (INIT_HCA_FS_PARAM_OFFSET + 0x25)
#घोषणा  INIT_HCA_FS_IB_NUM_ADDRS_OFFSET  (INIT_HCA_FS_PARAM_OFFSET + 0x26)
#घोषणा INIT_HCA_TPT_OFFSET		 0x0f0
#घोषणा	 INIT_HCA_DMPT_BASE_OFFSET	 (INIT_HCA_TPT_OFFSET + 0x00)
#घोषणा  INIT_HCA_TPT_MW_OFFSET		 (INIT_HCA_TPT_OFFSET + 0x08)
#घोषणा	 INIT_HCA_LOG_MPT_SZ_OFFSET	 (INIT_HCA_TPT_OFFSET + 0x0b)
#घोषणा	 INIT_HCA_MTT_BASE_OFFSET	 (INIT_HCA_TPT_OFFSET + 0x10)
#घोषणा	 INIT_HCA_CMPT_BASE_OFFSET	 (INIT_HCA_TPT_OFFSET + 0x18)
#घोषणा INIT_HCA_UAR_OFFSET		 0x120
#घोषणा	 INIT_HCA_LOG_UAR_SZ_OFFSET	 (INIT_HCA_UAR_OFFSET + 0x0a)
#घोषणा  INIT_HCA_UAR_PAGE_SZ_OFFSET     (INIT_HCA_UAR_OFFSET + 0x0b)

	mailbox = mlx4_alloc_cmd_mailbox(dev);
	अगर (IS_ERR(mailbox))
		वापस PTR_ERR(mailbox);
	inbox = mailbox->buf;

	*((u8 *) mailbox->buf + INIT_HCA_VERSION_OFFSET) = INIT_HCA_VERSION;

	*((u8 *) mailbox->buf + INIT_HCA_CACHELINE_SZ_OFFSET) =
		((ilog2(cache_line_size()) - 4) << 5) | (1 << 4);

#अगर defined(__LITTLE_ENDIAN)
	*(inbox + INIT_HCA_FLAGS_OFFSET / 4) &= ~cpu_to_be32(1 << 1);
#या_अगर defined(__BIG_ENDIAN)
	*(inbox + INIT_HCA_FLAGS_OFFSET / 4) |= cpu_to_be32(1 << 1);
#अन्यथा
#त्रुटि Host endianness not defined
#पूर्ण_अगर
	/* Check port क्रम UD address vector: */
	*(inbox + INIT_HCA_FLAGS_OFFSET / 4) |= cpu_to_be32(1);

	/* Enable IPoIB checksumming अगर we can: */
	अगर (dev->caps.flags & MLX4_DEV_CAP_FLAG_IPOIB_CSUM)
		*(inbox + INIT_HCA_FLAGS_OFFSET / 4) |= cpu_to_be32(1 << 3);

	/* Enable QoS support अगर module parameter set */
	अगर (dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_ETS_CFG && enable_qos)
		*(inbox + INIT_HCA_FLAGS_OFFSET / 4) |= cpu_to_be32(1 << 2);

	/* enable counters */
	अगर (dev->caps.flags & MLX4_DEV_CAP_FLAG_COUNTERS)
		*(inbox + INIT_HCA_FLAGS_OFFSET / 4) |= cpu_to_be32(1 << 4);

	/* Enable RSS spपढ़ो to fragmented IP packets when supported */
	अगर (dev->caps.flags & MLX4_DEV_CAP_FLAG_RSS_IP_FRAG)
		*(inbox + INIT_HCA_FLAGS_OFFSET / 4) |= cpu_to_be32(1 << 13);

	/* CX3 is capable of extending CQEs/EQEs from 32 to 64 bytes */
	अगर (dev->caps.flags & MLX4_DEV_CAP_FLAG_64B_EQE) अणु
		*(inbox + INIT_HCA_EQE_CQE_OFFSETS / 4) |= cpu_to_be32(1 << 29);
		dev->caps.eqe_size   = 64;
		dev->caps.eqe_factor = 1;
	पूर्ण अन्यथा अणु
		dev->caps.eqe_size   = 32;
		dev->caps.eqe_factor = 0;
	पूर्ण

	अगर (dev->caps.flags & MLX4_DEV_CAP_FLAG_64B_CQE) अणु
		*(inbox + INIT_HCA_EQE_CQE_OFFSETS / 4) |= cpu_to_be32(1 << 30);
		dev->caps.cqe_size   = 64;
		dev->caps.userspace_caps |= MLX4_USER_DEV_CAP_LARGE_CQE;
	पूर्ण अन्यथा अणु
		dev->caps.cqe_size   = 32;
	पूर्ण

	/* CX3 is capable of extending CQEs\EQEs to strides larger than 64B */
	अगर ((dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_EQE_STRIDE) &&
	    (dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_CQE_STRIDE)) अणु
		dev->caps.eqe_size = cache_line_size();
		dev->caps.cqe_size = cache_line_size();
		dev->caps.eqe_factor = 0;
		MLX4_PUT(inbox, (u8)((ilog2(dev->caps.eqe_size) - 5) << 4 |
				      (ilog2(dev->caps.eqe_size) - 5)),
			 INIT_HCA_EQE_CQE_STRIDE_OFFSET);

		/* User still need to know to support CQE > 32B */
		dev->caps.userspace_caps |= MLX4_USER_DEV_CAP_LARGE_CQE;
	पूर्ण

	अगर (dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_RECOVERABLE_ERROR_EVENT)
		*(inbox + INIT_HCA_RECOVERABLE_ERROR_EVENT_OFFSET / 4) |= cpu_to_be32(1 << 31);

	अगर (dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_DRIVER_VERSION_TO_FW) अणु
		u8 *dst = (u8 *)(inbox + INIT_HCA_DRIVER_VERSION_OFFSET / 4);

		म_नकलन(dst, DRV_NAME_FOR_FW, INIT_HCA_DRIVER_VERSION_SZ - 1);
		mlx4_dbg(dev, "Reporting Driver Version to FW: %s\n", dst);
	पूर्ण

	/* QPC/EEC/CQC/EQC/RDMARC attributes */

	MLX4_PUT(inbox, param->qpc_base,      INIT_HCA_QPC_BASE_OFFSET);
	MLX4_PUT(inbox, param->log_num_qps,   INIT_HCA_LOG_QP_OFFSET);
	MLX4_PUT(inbox, param->srqc_base,     INIT_HCA_SRQC_BASE_OFFSET);
	MLX4_PUT(inbox, param->log_num_srqs,  INIT_HCA_LOG_SRQ_OFFSET);
	MLX4_PUT(inbox, param->cqc_base,      INIT_HCA_CQC_BASE_OFFSET);
	MLX4_PUT(inbox, param->log_num_cqs,   INIT_HCA_LOG_CQ_OFFSET);
	MLX4_PUT(inbox, param->altc_base,     INIT_HCA_ALTC_BASE_OFFSET);
	MLX4_PUT(inbox, param->auxc_base,     INIT_HCA_AUXC_BASE_OFFSET);
	MLX4_PUT(inbox, param->eqc_base,      INIT_HCA_EQC_BASE_OFFSET);
	MLX4_PUT(inbox, param->log_num_eqs,   INIT_HCA_LOG_EQ_OFFSET);
	MLX4_PUT(inbox, param->num_sys_eqs,   INIT_HCA_NUM_SYS_EQS_OFFSET);
	MLX4_PUT(inbox, param->rdmarc_base,   INIT_HCA_RDMARC_BASE_OFFSET);
	MLX4_PUT(inbox, param->log_rd_per_qp, INIT_HCA_LOG_RD_OFFSET);

	/* steering attributes */
	अगर (dev->caps.steering_mode ==
	    MLX4_STEERING_MODE_DEVICE_MANAGED) अणु
		*(inbox + INIT_HCA_FLAGS_OFFSET / 4) |=
			cpu_to_be32(1 <<
				    INIT_HCA_DEVICE_MANAGED_FLOW_STEERING_EN);

		MLX4_PUT(inbox, param->mc_base, INIT_HCA_FS_BASE_OFFSET);
		MLX4_PUT(inbox, param->log_mc_entry_sz,
			 INIT_HCA_FS_LOG_ENTRY_SZ_OFFSET);
		MLX4_PUT(inbox, param->log_mc_table_sz,
			 INIT_HCA_FS_LOG_TABLE_SZ_OFFSET);
		/* Enable Ethernet flow steering
		 * with udp unicast and tcp unicast
		 */
		अगर (dev->caps.dmfs_high_steer_mode !=
		    MLX4_STEERING_DMFS_A0_STATIC)
			MLX4_PUT(inbox,
				 (u8)(MLX4_FS_UDP_UC_EN | MLX4_FS_TCP_UC_EN),
				 INIT_HCA_FS_ETH_BITS_OFFSET);
		MLX4_PUT(inbox, (u16) MLX4_FS_NUM_OF_L2_ADDR,
			 INIT_HCA_FS_ETH_NUM_ADDRS_OFFSET);
		/* Enable IPoIB flow steering
		 * with udp unicast and tcp unicast
		 */
		MLX4_PUT(inbox, (u8) (MLX4_FS_UDP_UC_EN | MLX4_FS_TCP_UC_EN),
			 INIT_HCA_FS_IB_BITS_OFFSET);
		MLX4_PUT(inbox, (u16) MLX4_FS_NUM_OF_L2_ADDR,
			 INIT_HCA_FS_IB_NUM_ADDRS_OFFSET);

		अगर (dev->caps.dmfs_high_steer_mode !=
		    MLX4_STEERING_DMFS_A0_NOT_SUPPORTED)
			MLX4_PUT(inbox,
				 ((u8)(a0_dmfs_hw_steering[dev->caps.dmfs_high_steer_mode]
				       << 6)),
				 INIT_HCA_FS_A0_OFFSET);
	पूर्ण अन्यथा अणु
		MLX4_PUT(inbox, param->mc_base,	INIT_HCA_MC_BASE_OFFSET);
		MLX4_PUT(inbox, param->log_mc_entry_sz,
			 INIT_HCA_LOG_MC_ENTRY_SZ_OFFSET);
		MLX4_PUT(inbox, param->log_mc_hash_sz,
			 INIT_HCA_LOG_MC_HASH_SZ_OFFSET);
		MLX4_PUT(inbox, param->log_mc_table_sz,
			 INIT_HCA_LOG_MC_TABLE_SZ_OFFSET);
		अगर (dev->caps.steering_mode == MLX4_STEERING_MODE_B0)
			MLX4_PUT(inbox, (u8) (1 << 3),
				 INIT_HCA_UC_STEERING_OFFSET);
	पूर्ण

	/* TPT attributes */

	MLX4_PUT(inbox, param->dmpt_base,  INIT_HCA_DMPT_BASE_OFFSET);
	MLX4_PUT(inbox, param->mw_enabled, INIT_HCA_TPT_MW_OFFSET);
	MLX4_PUT(inbox, param->log_mpt_sz, INIT_HCA_LOG_MPT_SZ_OFFSET);
	MLX4_PUT(inbox, param->mtt_base,   INIT_HCA_MTT_BASE_OFFSET);
	MLX4_PUT(inbox, param->cmpt_base,  INIT_HCA_CMPT_BASE_OFFSET);

	/* UAR attributes */

	MLX4_PUT(inbox, param->uar_page_sz,	INIT_HCA_UAR_PAGE_SZ_OFFSET);
	MLX4_PUT(inbox, param->log_uar_sz,      INIT_HCA_LOG_UAR_SZ_OFFSET);

	/* set parser VXLAN attributes */
	अगर (dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_VXLAN_OFFLOADS) अणु
		u8 parser_params = 0;
		MLX4_PUT(inbox, parser_params,	INIT_HCA_VXLAN_OFFSET);
	पूर्ण

	err = mlx4_cmd(dev, mailbox->dma, 0, 0, MLX4_CMD_INIT_HCA,
		       MLX4_CMD_TIME_CLASS_C, MLX4_CMD_NATIVE);

	अगर (err)
		mlx4_err(dev, "INIT_HCA returns %d\n", err);

	mlx4_मुक्त_cmd_mailbox(dev, mailbox);
	वापस err;
पूर्ण

पूर्णांक mlx4_QUERY_HCA(काष्ठा mlx4_dev *dev,
		   काष्ठा mlx4_init_hca_param *param)
अणु
	काष्ठा mlx4_cmd_mailbox *mailbox;
	__be32 *outbox;
	u64 qword_field;
	u32 dword_field;
	u16 word_field;
	u8 byte_field;
	पूर्णांक err;
	अटल स्थिर u8 a0_dmfs_query_hw_steering[] =  अणु
		[0] = MLX4_STEERING_DMFS_A0_DEFAULT,
		[1] = MLX4_STEERING_DMFS_A0_DYNAMIC,
		[2] = MLX4_STEERING_DMFS_A0_STATIC,
		[3] = MLX4_STEERING_DMFS_A0_DISABLE
	पूर्ण;

#घोषणा QUERY_HCA_GLOBAL_CAPS_OFFSET	0x04
#घोषणा QUERY_HCA_CORE_CLOCK_OFFSET	0x0c

	mailbox = mlx4_alloc_cmd_mailbox(dev);
	अगर (IS_ERR(mailbox))
		वापस PTR_ERR(mailbox);
	outbox = mailbox->buf;

	err = mlx4_cmd_box(dev, 0, mailbox->dma, 0, 0,
			   MLX4_CMD_QUERY_HCA,
			   MLX4_CMD_TIME_CLASS_B,
			   !mlx4_is_slave(dev));
	अगर (err)
		जाओ out;

	MLX4_GET(param->global_caps, outbox, QUERY_HCA_GLOBAL_CAPS_OFFSET);
	MLX4_GET(param->hca_core_घड़ी, outbox, QUERY_HCA_CORE_CLOCK_OFFSET);

	/* QPC/EEC/CQC/EQC/RDMARC attributes */

	MLX4_GET(qword_field, outbox, INIT_HCA_QPC_BASE_OFFSET);
	param->qpc_base = qword_field & ~((u64)0x1f);
	MLX4_GET(byte_field, outbox, INIT_HCA_LOG_QP_OFFSET);
	param->log_num_qps = byte_field & 0x1f;
	MLX4_GET(qword_field, outbox, INIT_HCA_SRQC_BASE_OFFSET);
	param->srqc_base = qword_field & ~((u64)0x1f);
	MLX4_GET(byte_field, outbox, INIT_HCA_LOG_SRQ_OFFSET);
	param->log_num_srqs = byte_field & 0x1f;
	MLX4_GET(qword_field, outbox, INIT_HCA_CQC_BASE_OFFSET);
	param->cqc_base = qword_field & ~((u64)0x1f);
	MLX4_GET(byte_field, outbox, INIT_HCA_LOG_CQ_OFFSET);
	param->log_num_cqs = byte_field & 0x1f;
	MLX4_GET(qword_field, outbox, INIT_HCA_ALTC_BASE_OFFSET);
	param->altc_base = qword_field;
	MLX4_GET(qword_field, outbox, INIT_HCA_AUXC_BASE_OFFSET);
	param->auxc_base = qword_field;
	MLX4_GET(qword_field, outbox, INIT_HCA_EQC_BASE_OFFSET);
	param->eqc_base = qword_field & ~((u64)0x1f);
	MLX4_GET(byte_field, outbox, INIT_HCA_LOG_EQ_OFFSET);
	param->log_num_eqs = byte_field & 0x1f;
	MLX4_GET(word_field, outbox, INIT_HCA_NUM_SYS_EQS_OFFSET);
	param->num_sys_eqs = word_field & 0xfff;
	MLX4_GET(qword_field, outbox, INIT_HCA_RDMARC_BASE_OFFSET);
	param->rdmarc_base = qword_field & ~((u64)0x1f);
	MLX4_GET(byte_field, outbox, INIT_HCA_LOG_RD_OFFSET);
	param->log_rd_per_qp = byte_field & 0x7;

	MLX4_GET(dword_field, outbox, INIT_HCA_FLAGS_OFFSET);
	अगर (dword_field & (1 << INIT_HCA_DEVICE_MANAGED_FLOW_STEERING_EN)) अणु
		param->steering_mode = MLX4_STEERING_MODE_DEVICE_MANAGED;
	पूर्ण अन्यथा अणु
		MLX4_GET(byte_field, outbox, INIT_HCA_UC_STEERING_OFFSET);
		अगर (byte_field & 0x8)
			param->steering_mode = MLX4_STEERING_MODE_B0;
		अन्यथा
			param->steering_mode = MLX4_STEERING_MODE_A0;
	पूर्ण

	अगर (dword_field & (1 << 13))
		param->rss_ip_frags = 1;

	/* steering attributes */
	अगर (param->steering_mode == MLX4_STEERING_MODE_DEVICE_MANAGED) अणु
		MLX4_GET(param->mc_base, outbox, INIT_HCA_FS_BASE_OFFSET);
		MLX4_GET(byte_field, outbox, INIT_HCA_FS_LOG_ENTRY_SZ_OFFSET);
		param->log_mc_entry_sz = byte_field & 0x1f;
		MLX4_GET(byte_field, outbox, INIT_HCA_FS_LOG_TABLE_SZ_OFFSET);
		param->log_mc_table_sz = byte_field & 0x1f;
		MLX4_GET(byte_field, outbox, INIT_HCA_FS_A0_OFFSET);
		param->dmfs_high_steer_mode =
			a0_dmfs_query_hw_steering[(byte_field >> 6) & 3];
	पूर्ण अन्यथा अणु
		MLX4_GET(param->mc_base, outbox, INIT_HCA_MC_BASE_OFFSET);
		MLX4_GET(byte_field, outbox, INIT_HCA_LOG_MC_ENTRY_SZ_OFFSET);
		param->log_mc_entry_sz = byte_field & 0x1f;
		MLX4_GET(byte_field,  outbox, INIT_HCA_LOG_MC_HASH_SZ_OFFSET);
		param->log_mc_hash_sz = byte_field & 0x1f;
		MLX4_GET(byte_field, outbox, INIT_HCA_LOG_MC_TABLE_SZ_OFFSET);
		param->log_mc_table_sz = byte_field & 0x1f;
	पूर्ण

	/* CX3 is capable of extending CQEs/EQEs from 32 to 64 bytes */
	MLX4_GET(byte_field, outbox, INIT_HCA_EQE_CQE_OFFSETS);
	अगर (byte_field & 0x20) /* 64-bytes eqe enabled */
		param->dev_cap_enabled |= MLX4_DEV_CAP_64B_EQE_ENABLED;
	अगर (byte_field & 0x40) /* 64-bytes cqe enabled */
		param->dev_cap_enabled |= MLX4_DEV_CAP_64B_CQE_ENABLED;

	/* CX3 is capable of extending CQEs\EQEs to strides larger than 64B */
	MLX4_GET(byte_field, outbox, INIT_HCA_EQE_CQE_STRIDE_OFFSET);
	अगर (byte_field) अणु
		param->dev_cap_enabled |= MLX4_DEV_CAP_EQE_STRIDE_ENABLED;
		param->dev_cap_enabled |= MLX4_DEV_CAP_CQE_STRIDE_ENABLED;
		param->cqe_size = 1 << ((byte_field &
					 MLX4_CQE_SIZE_MASK_STRIDE) + 5);
		param->eqe_size = 1 << (((byte_field &
					  MLX4_EQE_SIZE_MASK_STRIDE) >> 4) + 5);
	पूर्ण

	/* TPT attributes */

	MLX4_GET(param->dmpt_base,  outbox, INIT_HCA_DMPT_BASE_OFFSET);
	MLX4_GET(byte_field, outbox, INIT_HCA_TPT_MW_OFFSET);
	param->mw_enabled = byte_field >> 7;
	MLX4_GET(byte_field, outbox, INIT_HCA_LOG_MPT_SZ_OFFSET);
	param->log_mpt_sz = byte_field & 0x3f;
	MLX4_GET(param->mtt_base,   outbox, INIT_HCA_MTT_BASE_OFFSET);
	MLX4_GET(param->cmpt_base,  outbox, INIT_HCA_CMPT_BASE_OFFSET);

	/* UAR attributes */

	MLX4_GET(param->uar_page_sz, outbox, INIT_HCA_UAR_PAGE_SZ_OFFSET);
	MLX4_GET(byte_field, outbox, INIT_HCA_LOG_UAR_SZ_OFFSET);
	param->log_uar_sz = byte_field & 0xf;

	/* phv_check enable */
	MLX4_GET(byte_field, outbox, INIT_HCA_CACHELINE_SZ_OFFSET);
	अगर (byte_field & 0x2)
		param->phv_check_en = 1;
out:
	mlx4_मुक्त_cmd_mailbox(dev, mailbox);

	वापस err;
पूर्ण

अटल पूर्णांक mlx4_hca_core_घड़ी_update(काष्ठा mlx4_dev *dev)
अणु
	काष्ठा mlx4_cmd_mailbox *mailbox;
	__be32 *outbox;
	पूर्णांक err;

	mailbox = mlx4_alloc_cmd_mailbox(dev);
	अगर (IS_ERR(mailbox)) अणु
		mlx4_warn(dev, "hca_core_clock mailbox allocation failed\n");
		वापस PTR_ERR(mailbox);
	पूर्ण
	outbox = mailbox->buf;

	err = mlx4_cmd_box(dev, 0, mailbox->dma, 0, 0,
			   MLX4_CMD_QUERY_HCA,
			   MLX4_CMD_TIME_CLASS_B,
			   !mlx4_is_slave(dev));
	अगर (err) अणु
		mlx4_warn(dev, "hca_core_clock update failed\n");
		जाओ out;
	पूर्ण

	MLX4_GET(dev->caps.hca_core_घड़ी, outbox, QUERY_HCA_CORE_CLOCK_OFFSET);

out:
	mlx4_मुक्त_cmd_mailbox(dev, mailbox);

	वापस err;
पूर्ण

/* क्रम IB-type ports only in SRIOV mode. Checks that both proxy QP0
 * and real QP0 are active, so that the paraभवized QP0 is पढ़ोy
 * to operate */
अटल पूर्णांक check_qp0_state(काष्ठा mlx4_dev *dev, पूर्णांक function, पूर्णांक port)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	/* irrelevant अगर not infiniband */
	अगर (priv->mfunc.master.qp0_state[port].proxy_qp0_active &&
	    priv->mfunc.master.qp0_state[port].qp0_active)
		वापस 1;
	वापस 0;
पूर्ण

पूर्णांक mlx4_INIT_PORT_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			   काष्ठा mlx4_vhcr *vhcr,
			   काष्ठा mlx4_cmd_mailbox *inbox,
			   काष्ठा mlx4_cmd_mailbox *outbox,
			   काष्ठा mlx4_cmd_info *cmd)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	पूर्णांक port = mlx4_slave_convert_port(dev, slave, vhcr->in_modअगरier);
	पूर्णांक err;

	अगर (port < 0)
		वापस -EINVAL;

	अगर (priv->mfunc.master.slave_state[slave].init_port_mask & (1 << port))
		वापस 0;

	अगर (dev->caps.port_mask[port] != MLX4_PORT_TYPE_IB) अणु
		/* Enable port only अगर it was previously disabled */
		अगर (!priv->mfunc.master.init_port_ref[port]) अणु
			err = mlx4_cmd(dev, 0, port, 0, MLX4_CMD_INIT_PORT,
				       MLX4_CMD_TIME_CLASS_A, MLX4_CMD_NATIVE);
			अगर (err)
				वापस err;
		पूर्ण
		priv->mfunc.master.slave_state[slave].init_port_mask |= (1 << port);
	पूर्ण अन्यथा अणु
		अगर (slave == mlx4_master_func_num(dev)) अणु
			अगर (check_qp0_state(dev, slave, port) &&
			    !priv->mfunc.master.qp0_state[port].port_active) अणु
				err = mlx4_cmd(dev, 0, port, 0, MLX4_CMD_INIT_PORT,
					       MLX4_CMD_TIME_CLASS_A, MLX4_CMD_NATIVE);
				अगर (err)
					वापस err;
				priv->mfunc.master.qp0_state[port].port_active = 1;
				priv->mfunc.master.slave_state[slave].init_port_mask |= (1 << port);
			पूर्ण
		पूर्ण अन्यथा
			priv->mfunc.master.slave_state[slave].init_port_mask |= (1 << port);
	पूर्ण
	++priv->mfunc.master.init_port_ref[port];
	वापस 0;
पूर्ण

पूर्णांक mlx4_INIT_PORT(काष्ठा mlx4_dev *dev, पूर्णांक port)
अणु
	काष्ठा mlx4_cmd_mailbox *mailbox;
	u32 *inbox;
	पूर्णांक err;
	u32 flags;
	u16 field;

	अगर (dev->flags & MLX4_FLAG_OLD_PORT_CMDS) अणु
#घोषणा INIT_PORT_IN_SIZE          256
#घोषणा INIT_PORT_FLAGS_OFFSET     0x00
#घोषणा INIT_PORT_FLAG_SIG         (1 << 18)
#घोषणा INIT_PORT_FLAG_NG          (1 << 17)
#घोषणा INIT_PORT_FLAG_G0          (1 << 16)
#घोषणा INIT_PORT_VL_SHIFT         4
#घोषणा INIT_PORT_PORT_WIDTH_SHIFT 8
#घोषणा INIT_PORT_MTU_OFFSET       0x04
#घोषणा INIT_PORT_MAX_GID_OFFSET   0x06
#घोषणा INIT_PORT_MAX_PKEY_OFFSET  0x0a
#घोषणा INIT_PORT_GUID0_OFFSET     0x10
#घोषणा INIT_PORT_NODE_GUID_OFFSET 0x18
#घोषणा INIT_PORT_SI_GUID_OFFSET   0x20

		mailbox = mlx4_alloc_cmd_mailbox(dev);
		अगर (IS_ERR(mailbox))
			वापस PTR_ERR(mailbox);
		inbox = mailbox->buf;

		flags = 0;
		flags |= (dev->caps.vl_cap[port] & 0xf) << INIT_PORT_VL_SHIFT;
		flags |= (dev->caps.port_width_cap[port] & 0xf) << INIT_PORT_PORT_WIDTH_SHIFT;
		MLX4_PUT(inbox, flags,		  INIT_PORT_FLAGS_OFFSET);

		field = 128 << dev->caps.ib_mtu_cap[port];
		MLX4_PUT(inbox, field, INIT_PORT_MTU_OFFSET);
		field = dev->caps.gid_table_len[port];
		MLX4_PUT(inbox, field, INIT_PORT_MAX_GID_OFFSET);
		field = dev->caps.pkey_table_len[port];
		MLX4_PUT(inbox, field, INIT_PORT_MAX_PKEY_OFFSET);

		err = mlx4_cmd(dev, mailbox->dma, port, 0, MLX4_CMD_INIT_PORT,
			       MLX4_CMD_TIME_CLASS_A, MLX4_CMD_NATIVE);

		mlx4_मुक्त_cmd_mailbox(dev, mailbox);
	पूर्ण अन्यथा
		err = mlx4_cmd(dev, 0, port, 0, MLX4_CMD_INIT_PORT,
			       MLX4_CMD_TIME_CLASS_A, MLX4_CMD_WRAPPED);

	अगर (!err)
		mlx4_hca_core_घड़ी_update(dev);

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_INIT_PORT);

पूर्णांक mlx4_CLOSE_PORT_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			    काष्ठा mlx4_vhcr *vhcr,
			    काष्ठा mlx4_cmd_mailbox *inbox,
			    काष्ठा mlx4_cmd_mailbox *outbox,
			    काष्ठा mlx4_cmd_info *cmd)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	पूर्णांक port = mlx4_slave_convert_port(dev, slave, vhcr->in_modअगरier);
	पूर्णांक err;

	अगर (port < 0)
		वापस -EINVAL;

	अगर (!(priv->mfunc.master.slave_state[slave].init_port_mask &
	    (1 << port)))
		वापस 0;

	अगर (dev->caps.port_mask[port] != MLX4_PORT_TYPE_IB) अणु
		अगर (priv->mfunc.master.init_port_ref[port] == 1) अणु
			err = mlx4_cmd(dev, 0, port, 0, MLX4_CMD_CLOSE_PORT,
				       MLX4_CMD_TIME_CLASS_A, MLX4_CMD_NATIVE);
			अगर (err)
				वापस err;
		पूर्ण
		priv->mfunc.master.slave_state[slave].init_port_mask &= ~(1 << port);
	पूर्ण अन्यथा अणु
		/* infiniband port */
		अगर (slave == mlx4_master_func_num(dev)) अणु
			अगर (!priv->mfunc.master.qp0_state[port].qp0_active &&
			    priv->mfunc.master.qp0_state[port].port_active) अणु
				err = mlx4_cmd(dev, 0, port, 0, MLX4_CMD_CLOSE_PORT,
					       MLX4_CMD_TIME_CLASS_A, MLX4_CMD_NATIVE);
				अगर (err)
					वापस err;
				priv->mfunc.master.slave_state[slave].init_port_mask &= ~(1 << port);
				priv->mfunc.master.qp0_state[port].port_active = 0;
			पूर्ण
		पूर्ण अन्यथा
			priv->mfunc.master.slave_state[slave].init_port_mask &= ~(1 << port);
	पूर्ण
	--priv->mfunc.master.init_port_ref[port];
	वापस 0;
पूर्ण

पूर्णांक mlx4_CLOSE_PORT(काष्ठा mlx4_dev *dev, पूर्णांक port)
अणु
	वापस mlx4_cmd(dev, 0, port, 0, MLX4_CMD_CLOSE_PORT,
			MLX4_CMD_TIME_CLASS_A, MLX4_CMD_WRAPPED);
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_CLOSE_PORT);

पूर्णांक mlx4_CLOSE_HCA(काष्ठा mlx4_dev *dev, पूर्णांक panic)
अणु
	वापस mlx4_cmd(dev, 0, 0, panic, MLX4_CMD_CLOSE_HCA,
			MLX4_CMD_TIME_CLASS_C, MLX4_CMD_NATIVE);
पूर्ण

काष्ठा mlx4_config_dev अणु
	__be32	update_flags;
	__be32	rsvd1[3];
	__be16	vxlan_udp_dport;
	__be16	rsvd2;
	__be16  roce_v2_entropy;
	__be16  roce_v2_udp_dport;
	__be32	roce_flags;
	__be32	rsvd4[25];
	__be16	rsvd5;
	u8	rsvd6;
	u8	rx_checksum_val;
पूर्ण;

#घोषणा MLX4_VXLAN_UDP_DPORT (1 << 0)
#घोषणा MLX4_ROCE_V2_UDP_DPORT BIT(3)
#घोषणा MLX4_DISABLE_RX_PORT BIT(18)

अटल पूर्णांक mlx4_CONFIG_DEV_set(काष्ठा mlx4_dev *dev, काष्ठा mlx4_config_dev *config_dev)
अणु
	पूर्णांक err;
	काष्ठा mlx4_cmd_mailbox *mailbox;

	mailbox = mlx4_alloc_cmd_mailbox(dev);
	अगर (IS_ERR(mailbox))
		वापस PTR_ERR(mailbox);

	स_नकल(mailbox->buf, config_dev, माप(*config_dev));

	err = mlx4_cmd(dev, mailbox->dma, 0, 0, MLX4_CMD_CONFIG_DEV,
		       MLX4_CMD_TIME_CLASS_B, MLX4_CMD_NATIVE);

	mlx4_मुक्त_cmd_mailbox(dev, mailbox);
	वापस err;
पूर्ण

अटल पूर्णांक mlx4_CONFIG_DEV_get(काष्ठा mlx4_dev *dev, काष्ठा mlx4_config_dev *config_dev)
अणु
	पूर्णांक err;
	काष्ठा mlx4_cmd_mailbox *mailbox;

	mailbox = mlx4_alloc_cmd_mailbox(dev);
	अगर (IS_ERR(mailbox))
		वापस PTR_ERR(mailbox);

	err = mlx4_cmd_box(dev, 0, mailbox->dma, 0, 1, MLX4_CMD_CONFIG_DEV,
			   MLX4_CMD_TIME_CLASS_A, MLX4_CMD_NATIVE);

	अगर (!err)
		स_नकल(config_dev, mailbox->buf, माप(*config_dev));

	mlx4_मुक्त_cmd_mailbox(dev, mailbox);
	वापस err;
पूर्ण

/* Conversion between the HW values and the actual functionality.
 * The value represented by the array index,
 * and the functionality determined by the flags.
 */
अटल स्थिर u8 config_dev_csum_flags[] = अणु
	[0] =	0,
	[1] =	MLX4_RX_CSUM_MODE_VAL_NON_TCP_UDP,
	[2] =	MLX4_RX_CSUM_MODE_VAL_NON_TCP_UDP	|
		MLX4_RX_CSUM_MODE_L4,
	[3] =	MLX4_RX_CSUM_MODE_L4			|
		MLX4_RX_CSUM_MODE_IP_OK_IP_NON_TCP_UDP	|
		MLX4_RX_CSUM_MODE_MULTI_VLAN
पूर्ण;

पूर्णांक mlx4_config_dev_retrieval(काष्ठा mlx4_dev *dev,
			      काष्ठा mlx4_config_dev_params *params)
अणु
	काष्ठा mlx4_config_dev config_dev = अणु0पूर्ण;
	पूर्णांक err;
	u8 csum_mask;

#घोषणा CONFIG_DEV_RX_CSUM_MODE_MASK			0x7
#घोषणा CONFIG_DEV_RX_CSUM_MODE_PORT1_BIT_OFFSET	0
#घोषणा CONFIG_DEV_RX_CSUM_MODE_PORT2_BIT_OFFSET	4

	अगर (!(dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_CONFIG_DEV))
		वापस -EOPNOTSUPP;

	err = mlx4_CONFIG_DEV_get(dev, &config_dev);
	अगर (err)
		वापस err;

	csum_mask = (config_dev.rx_checksum_val >> CONFIG_DEV_RX_CSUM_MODE_PORT1_BIT_OFFSET) &
			CONFIG_DEV_RX_CSUM_MODE_MASK;

	अगर (csum_mask >= ARRAY_SIZE(config_dev_csum_flags))
		वापस -EINVAL;
	params->rx_csum_flags_port_1 = config_dev_csum_flags[csum_mask];

	csum_mask = (config_dev.rx_checksum_val >> CONFIG_DEV_RX_CSUM_MODE_PORT2_BIT_OFFSET) &
			CONFIG_DEV_RX_CSUM_MODE_MASK;

	अगर (csum_mask >= ARRAY_SIZE(config_dev_csum_flags))
		वापस -EINVAL;
	params->rx_csum_flags_port_2 = config_dev_csum_flags[csum_mask];

	params->vxlan_udp_dport = be16_to_cpu(config_dev.vxlan_udp_dport);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_config_dev_retrieval);

पूर्णांक mlx4_config_vxlan_port(काष्ठा mlx4_dev *dev, __be16 udp_port)
अणु
	काष्ठा mlx4_config_dev config_dev;

	स_रखो(&config_dev, 0, माप(config_dev));
	config_dev.update_flags    = cpu_to_be32(MLX4_VXLAN_UDP_DPORT);
	config_dev.vxlan_udp_dport = udp_port;

	वापस mlx4_CONFIG_DEV_set(dev, &config_dev);
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_config_vxlan_port);

#घोषणा CONFIG_DISABLE_RX_PORT BIT(15)
पूर्णांक mlx4_disable_rx_port_check(काष्ठा mlx4_dev *dev, bool dis)
अणु
	काष्ठा mlx4_config_dev config_dev;

	स_रखो(&config_dev, 0, माप(config_dev));
	config_dev.update_flags = cpu_to_be32(MLX4_DISABLE_RX_PORT);
	अगर (dis)
		config_dev.roce_flags =
			cpu_to_be32(CONFIG_DISABLE_RX_PORT);

	वापस mlx4_CONFIG_DEV_set(dev, &config_dev);
पूर्ण

पूर्णांक mlx4_config_roce_v2_port(काष्ठा mlx4_dev *dev, u16 udp_port)
अणु
	काष्ठा mlx4_config_dev config_dev;

	स_रखो(&config_dev, 0, माप(config_dev));
	config_dev.update_flags    = cpu_to_be32(MLX4_ROCE_V2_UDP_DPORT);
	config_dev.roce_v2_udp_dport = cpu_to_be16(udp_port);

	वापस mlx4_CONFIG_DEV_set(dev, &config_dev);
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_config_roce_v2_port);

पूर्णांक mlx4_virt2phy_port_map(काष्ठा mlx4_dev *dev, u32 port1, u32 port2)
अणु
	काष्ठा mlx4_cmd_mailbox *mailbox;
	काष्ठा अणु
		__be32 v_port1;
		__be32 v_port2;
	पूर्ण *v2p;
	पूर्णांक err;

	mailbox = mlx4_alloc_cmd_mailbox(dev);
	अगर (IS_ERR(mailbox))
		वापस -ENOMEM;

	v2p = mailbox->buf;
	v2p->v_port1 = cpu_to_be32(port1);
	v2p->v_port2 = cpu_to_be32(port2);

	err = mlx4_cmd(dev, mailbox->dma, 0,
		       MLX4_SET_PORT_VIRT2PHY, MLX4_CMD_VIRT_PORT_MAP,
		       MLX4_CMD_TIME_CLASS_B, MLX4_CMD_NATIVE);

	mlx4_मुक्त_cmd_mailbox(dev, mailbox);
	वापस err;
पूर्ण


पूर्णांक mlx4_SET_ICM_SIZE(काष्ठा mlx4_dev *dev, u64 icm_size, u64 *aux_pages)
अणु
	पूर्णांक ret = mlx4_cmd_imm(dev, icm_size, aux_pages, 0, 0,
			       MLX4_CMD_SET_ICM_SIZE,
			       MLX4_CMD_TIME_CLASS_A, MLX4_CMD_NATIVE);
	अगर (ret)
		वापस ret;

	/*
	 * Round up number of प्रणाली pages needed in हाल
	 * MLX4_ICM_PAGE_SIZE < PAGE_SIZE.
	 */
	*aux_pages = ALIGN(*aux_pages, PAGE_SIZE / MLX4_ICM_PAGE_SIZE) >>
		(PAGE_SHIFT - MLX4_ICM_PAGE_SHIFT);

	वापस 0;
पूर्ण

पूर्णांक mlx4_NOP(काष्ठा mlx4_dev *dev)
अणु
	/* Input modअगरier of 0x1f means "finish as soon as possible." */
	वापस mlx4_cmd(dev, 0, 0x1f, 0, MLX4_CMD_NOP, MLX4_CMD_TIME_CLASS_A,
			MLX4_CMD_NATIVE);
पूर्ण

पूर्णांक mlx4_query_diag_counters(काष्ठा mlx4_dev *dev, u8 op_modअगरier,
			     स्थिर u32 offset[],
			     u32 value[], माप_प्रकार array_len, u8 port)
अणु
	काष्ठा mlx4_cmd_mailbox *mailbox;
	u32 *outbox;
	माप_प्रकार i;
	पूर्णांक ret;

	mailbox = mlx4_alloc_cmd_mailbox(dev);
	अगर (IS_ERR(mailbox))
		वापस PTR_ERR(mailbox);

	outbox = mailbox->buf;

	ret = mlx4_cmd_box(dev, 0, mailbox->dma, port, op_modअगरier,
			   MLX4_CMD_DIAG_RPRT, MLX4_CMD_TIME_CLASS_A,
			   MLX4_CMD_NATIVE);
	अगर (ret)
		जाओ out;

	क्रम (i = 0; i < array_len; i++) अणु
		अगर (offset[i] > MLX4_MAILBOX_SIZE) अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		MLX4_GET(value[i], outbox, offset[i]);
	पूर्ण

out:
	mlx4_मुक्त_cmd_mailbox(dev, mailbox);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(mlx4_query_diag_counters);

पूर्णांक mlx4_get_phys_port_id(काष्ठा mlx4_dev *dev)
अणु
	u8 port;
	u32 *outbox;
	काष्ठा mlx4_cmd_mailbox *mailbox;
	u32 in_mod;
	u32 guid_hi, guid_lo;
	पूर्णांक err, ret = 0;
#घोषणा MOD_STAT_CFG_PORT_OFFSET 8
#घोषणा MOD_STAT_CFG_GUID_H	 0X14
#घोषणा MOD_STAT_CFG_GUID_L	 0X1c

	mailbox = mlx4_alloc_cmd_mailbox(dev);
	अगर (IS_ERR(mailbox))
		वापस PTR_ERR(mailbox);
	outbox = mailbox->buf;

	क्रम (port = 1; port <= dev->caps.num_ports; port++) अणु
		in_mod = port << MOD_STAT_CFG_PORT_OFFSET;
		err = mlx4_cmd_box(dev, 0, mailbox->dma, in_mod, 0x2,
				   MLX4_CMD_MOD_STAT_CFG, MLX4_CMD_TIME_CLASS_A,
				   MLX4_CMD_NATIVE);
		अगर (err) अणु
			mlx4_err(dev, "Fail to get port %d uplink guid\n",
				 port);
			ret = err;
		पूर्ण अन्यथा अणु
			MLX4_GET(guid_hi, outbox, MOD_STAT_CFG_GUID_H);
			MLX4_GET(guid_lo, outbox, MOD_STAT_CFG_GUID_L);
			dev->caps.phys_port_id[port] = (u64)guid_lo |
						       (u64)guid_hi << 32;
		पूर्ण
	पूर्ण
	mlx4_मुक्त_cmd_mailbox(dev, mailbox);
	वापस ret;
पूर्ण

#घोषणा MLX4_WOL_SETUP_MODE (5 << 28)
पूर्णांक mlx4_wol_पढ़ो(काष्ठा mlx4_dev *dev, u64 *config, पूर्णांक port)
अणु
	u32 in_mod = MLX4_WOL_SETUP_MODE | port << 8;

	वापस mlx4_cmd_imm(dev, 0, config, in_mod, 0x3,
			    MLX4_CMD_MOD_STAT_CFG, MLX4_CMD_TIME_CLASS_A,
			    MLX4_CMD_NATIVE);
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_wol_पढ़ो);

पूर्णांक mlx4_wol_ग_लिखो(काष्ठा mlx4_dev *dev, u64 config, पूर्णांक port)
अणु
	u32 in_mod = MLX4_WOL_SETUP_MODE | port << 8;

	वापस mlx4_cmd(dev, config, in_mod, 0x1, MLX4_CMD_MOD_STAT_CFG,
			MLX4_CMD_TIME_CLASS_A, MLX4_CMD_NATIVE);
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_wol_ग_लिखो);

क्रमागत अणु
	ADD_TO_MCG = 0x26,
पूर्ण;


व्योम mlx4_opreq_action(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mlx4_priv *priv = container_of(work, काष्ठा mlx4_priv,
					      opreq_task);
	काष्ठा mlx4_dev *dev = &priv->dev;
	पूर्णांक num_tasks = atomic_पढ़ो(&priv->opreq_count);
	काष्ठा mlx4_cmd_mailbox *mailbox;
	काष्ठा mlx4_mgm *mgm;
	u32 *outbox;
	u32 modअगरier;
	u16 token;
	u16 type;
	पूर्णांक err;
	u32 num_qps;
	काष्ठा mlx4_qp qp;
	पूर्णांक i;
	u8 rem_mcg;
	u8 prot;

#घोषणा GET_OP_REQ_MODIFIER_OFFSET	0x08
#घोषणा GET_OP_REQ_TOKEN_OFFSET		0x14
#घोषणा GET_OP_REQ_TYPE_OFFSET		0x1a
#घोषणा GET_OP_REQ_DATA_OFFSET		0x20

	mailbox = mlx4_alloc_cmd_mailbox(dev);
	अगर (IS_ERR(mailbox)) अणु
		mlx4_err(dev, "Failed to allocate mailbox for GET_OP_REQ\n");
		वापस;
	पूर्ण
	outbox = mailbox->buf;

	जबतक (num_tasks) अणु
		err = mlx4_cmd_box(dev, 0, mailbox->dma, 0, 0,
				   MLX4_CMD_GET_OP_REQ, MLX4_CMD_TIME_CLASS_A,
				   MLX4_CMD_NATIVE);
		अगर (err) अणु
			mlx4_err(dev, "Failed to retrieve required operation: %d\n",
				 err);
			जाओ out;
		पूर्ण
		MLX4_GET(modअगरier, outbox, GET_OP_REQ_MODIFIER_OFFSET);
		MLX4_GET(token, outbox, GET_OP_REQ_TOKEN_OFFSET);
		MLX4_GET(type, outbox, GET_OP_REQ_TYPE_OFFSET);
		type &= 0xfff;

		चयन (type) अणु
		हाल ADD_TO_MCG:
			अगर (dev->caps.steering_mode ==
			    MLX4_STEERING_MODE_DEVICE_MANAGED) अणु
				mlx4_warn(dev, "ADD MCG operation is not supported in DEVICE_MANAGED steering mode\n");
				err = EPERM;
				अवरोध;
			पूर्ण
			mgm = (काष्ठा mlx4_mgm *)((u8 *)(outbox) +
						  GET_OP_REQ_DATA_OFFSET);
			num_qps = be32_to_cpu(mgm->members_count) &
				  MGM_QPN_MASK;
			rem_mcg = ((u8 *)(&mgm->members_count))[0] & 1;
			prot = ((u8 *)(&mgm->members_count))[0] >> 6;

			क्रम (i = 0; i < num_qps; i++) अणु
				qp.qpn = be32_to_cpu(mgm->qp[i]);
				अगर (rem_mcg)
					err = mlx4_multicast_detach(dev, &qp,
								    mgm->gid,
								    prot, 0);
				अन्यथा
					err = mlx4_multicast_attach(dev, &qp,
								    mgm->gid,
								    mgm->gid[5]
								    , 0, prot,
								    शून्य);
				अगर (err)
					अवरोध;
			पूर्ण
			अवरोध;
		शेष:
			mlx4_warn(dev, "Bad type for required operation\n");
			err = EINVAL;
			अवरोध;
		पूर्ण
		err = mlx4_cmd(dev, 0, ((u32) err |
					(__क्रमce u32)cpu_to_be32(token) << 16),
			       1, MLX4_CMD_GET_OP_REQ, MLX4_CMD_TIME_CLASS_A,
			       MLX4_CMD_NATIVE);
		अगर (err) अणु
			mlx4_err(dev, "Failed to acknowledge required request: %d\n",
				 err);
			जाओ out;
		पूर्ण
		स_रखो(outbox, 0, 0xffc);
		num_tasks = atomic_dec_वापस(&priv->opreq_count);
	पूर्ण

out:
	mlx4_मुक्त_cmd_mailbox(dev, mailbox);
पूर्ण

अटल पूर्णांक mlx4_check_smp_firewall_active(काष्ठा mlx4_dev *dev,
					  काष्ठा mlx4_cmd_mailbox *mailbox)
अणु
#घोषणा MLX4_CMD_MAD_DEMUX_SET_ATTR_OFFSET		0x10
#घोषणा MLX4_CMD_MAD_DEMUX_GETRESP_ATTR_OFFSET		0x20
#घोषणा MLX4_CMD_MAD_DEMUX_TRAP_ATTR_OFFSET		0x40
#घोषणा MLX4_CMD_MAD_DEMUX_TRAP_REPRESS_ATTR_OFFSET	0x70

	u32 set_attr_mask, getresp_attr_mask;
	u32 trap_attr_mask, traprepress_attr_mask;

	MLX4_GET(set_attr_mask, mailbox->buf,
		 MLX4_CMD_MAD_DEMUX_SET_ATTR_OFFSET);
	mlx4_dbg(dev, "SMP firewall set_attribute_mask = 0x%x\n",
		 set_attr_mask);

	MLX4_GET(getresp_attr_mask, mailbox->buf,
		 MLX4_CMD_MAD_DEMUX_GETRESP_ATTR_OFFSET);
	mlx4_dbg(dev, "SMP firewall getresp_attribute_mask = 0x%x\n",
		 getresp_attr_mask);

	MLX4_GET(trap_attr_mask, mailbox->buf,
		 MLX4_CMD_MAD_DEMUX_TRAP_ATTR_OFFSET);
	mlx4_dbg(dev, "SMP firewall trap_attribute_mask = 0x%x\n",
		 trap_attr_mask);

	MLX4_GET(traprepress_attr_mask, mailbox->buf,
		 MLX4_CMD_MAD_DEMUX_TRAP_REPRESS_ATTR_OFFSET);
	mlx4_dbg(dev, "SMP firewall traprepress_attribute_mask = 0x%x\n",
		 traprepress_attr_mask);

	अगर (set_attr_mask && getresp_attr_mask && trap_attr_mask &&
	    traprepress_attr_mask)
		वापस 1;

	वापस 0;
पूर्ण

पूर्णांक mlx4_config_mad_demux(काष्ठा mlx4_dev *dev)
अणु
	काष्ठा mlx4_cmd_mailbox *mailbox;
	पूर्णांक err;

	/* Check अगर mad_demux is supported */
	अगर (!(dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_MAD_DEMUX))
		वापस 0;

	mailbox = mlx4_alloc_cmd_mailbox(dev);
	अगर (IS_ERR(mailbox)) अणु
		mlx4_warn(dev, "Failed to allocate mailbox for cmd MAD_DEMUX");
		वापस -ENOMEM;
	पूर्ण

	/* Query mad_demux to find out which MADs are handled by पूर्णांकernal sma */
	err = mlx4_cmd_box(dev, 0, mailbox->dma, 0x01 /* subn mgmt class */,
			   MLX4_CMD_MAD_DEMUX_QUERY_RESTR, MLX4_CMD_MAD_DEMUX,
			   MLX4_CMD_TIME_CLASS_B, MLX4_CMD_NATIVE);
	अगर (err) अणु
		mlx4_warn(dev, "MLX4_CMD_MAD_DEMUX: query restrictions failed (%d)\n",
			  err);
		जाओ out;
	पूर्ण

	अगर (mlx4_check_smp_firewall_active(dev, mailbox))
		dev->flags |= MLX4_FLAG_SECURE_HOST;

	/* Config mad_demux to handle all MADs वापसed by the query above */
	err = mlx4_cmd(dev, mailbox->dma, 0x01 /* subn mgmt class */,
		       MLX4_CMD_MAD_DEMUX_CONFIG, MLX4_CMD_MAD_DEMUX,
		       MLX4_CMD_TIME_CLASS_B, MLX4_CMD_NATIVE);
	अगर (err) अणु
		mlx4_warn(dev, "MLX4_CMD_MAD_DEMUX: configure failed (%d)\n", err);
		जाओ out;
	पूर्ण

	अगर (dev->flags & MLX4_FLAG_SECURE_HOST)
		mlx4_warn(dev, "HCA operating in secure-host mode. SMP firewall activated.\n");
out:
	mlx4_मुक्त_cmd_mailbox(dev, mailbox);
	वापस err;
पूर्ण

/* Access Reg commands */
क्रमागत mlx4_access_reg_masks अणु
	MLX4_ACCESS_REG_STATUS_MASK = 0x7f,
	MLX4_ACCESS_REG_METHOD_MASK = 0x7f,
	MLX4_ACCESS_REG_LEN_MASK = 0x7ff
पूर्ण;

काष्ठा mlx4_access_reg अणु
	__be16 स्थिरant1;
	u8 status;
	u8 resrvd1;
	__be16 reg_id;
	u8 method;
	u8 स्थिरant2;
	__be32 resrvd2[2];
	__be16 len_स्थिर;
	__be16 resrvd3;
#घोषणा MLX4_ACCESS_REG_HEADER_SIZE (20)
	u8 reg_data[MLX4_MAILBOX_SIZE-MLX4_ACCESS_REG_HEADER_SIZE];
पूर्ण __attribute__((__packed__));

/**
 * mlx4_ACCESS_REG - Generic access reg command.
 * @dev: mlx4_dev.
 * @reg_id: रेजिस्टर ID to access.
 * @method: Access method Read/Write.
 * @reg_len: रेजिस्टर length to Read/Write in bytes.
 * @reg_data: reg_data poपूर्णांकer to Read/Write From/To.
 *
 * Access ConnectX रेजिस्टरs FW command.
 * Returns 0 on success and copies outbox mlx4_access_reg data
 * field पूर्णांकo reg_data or a negative error code.
 */
अटल पूर्णांक mlx4_ACCESS_REG(काष्ठा mlx4_dev *dev, u16 reg_id,
			   क्रमागत mlx4_access_reg_method method,
			   u16 reg_len, व्योम *reg_data)
अणु
	काष्ठा mlx4_cmd_mailbox *inbox, *outbox;
	काष्ठा mlx4_access_reg *inbuf, *outbuf;
	पूर्णांक err;

	inbox = mlx4_alloc_cmd_mailbox(dev);
	अगर (IS_ERR(inbox))
		वापस PTR_ERR(inbox);

	outbox = mlx4_alloc_cmd_mailbox(dev);
	अगर (IS_ERR(outbox)) अणु
		mlx4_मुक्त_cmd_mailbox(dev, inbox);
		वापस PTR_ERR(outbox);
	पूर्ण

	inbuf = inbox->buf;
	outbuf = outbox->buf;

	inbuf->स्थिरant1 = cpu_to_be16(0x1<<11 | 0x4);
	inbuf->स्थिरant2 = 0x1;
	inbuf->reg_id = cpu_to_be16(reg_id);
	inbuf->method = method & MLX4_ACCESS_REG_METHOD_MASK;

	reg_len = min(reg_len, (u16)(माप(inbuf->reg_data)));
	inbuf->len_स्थिर =
		cpu_to_be16(((reg_len/4 + 1) & MLX4_ACCESS_REG_LEN_MASK) |
			    ((0x3) << 12));

	स_नकल(inbuf->reg_data, reg_data, reg_len);
	err = mlx4_cmd_box(dev, inbox->dma, outbox->dma, 0, 0,
			   MLX4_CMD_ACCESS_REG, MLX4_CMD_TIME_CLASS_C,
			   MLX4_CMD_WRAPPED);
	अगर (err)
		जाओ out;

	अगर (outbuf->status & MLX4_ACCESS_REG_STATUS_MASK) अणु
		err = outbuf->status & MLX4_ACCESS_REG_STATUS_MASK;
		mlx4_err(dev,
			 "MLX4_CMD_ACCESS_REG(%x) returned REG status (%x)\n",
			 reg_id, err);
		जाओ out;
	पूर्ण

	स_नकल(reg_data, outbuf->reg_data, reg_len);
out:
	mlx4_मुक्त_cmd_mailbox(dev, inbox);
	mlx4_मुक्त_cmd_mailbox(dev, outbox);
	वापस err;
पूर्ण

/* ConnectX रेजिस्टरs IDs */
क्रमागत mlx4_reg_id अणु
	MLX4_REG_ID_PTYS = 0x5004,
पूर्ण;

/**
 * mlx4_ACCESS_PTYS_REG - Access PTYs (Port Type and Speed)
 * रेजिस्टर
 * @dev: mlx4_dev.
 * @method: Access method Read/Write.
 * @ptys_reg: PTYS रेजिस्टर data poपूर्णांकer.
 *
 * Access ConnectX PTYS रेजिस्टर, to Read/Write Port Type/Speed
 * configuration
 * Returns 0 on success or a negative error code.
 */
पूर्णांक mlx4_ACCESS_PTYS_REG(काष्ठा mlx4_dev *dev,
			 क्रमागत mlx4_access_reg_method method,
			 काष्ठा mlx4_ptys_reg *ptys_reg)
अणु
	वापस mlx4_ACCESS_REG(dev, MLX4_REG_ID_PTYS,
			       method, माप(*ptys_reg), ptys_reg);
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_ACCESS_PTYS_REG);

पूर्णांक mlx4_ACCESS_REG_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			    काष्ठा mlx4_vhcr *vhcr,
			    काष्ठा mlx4_cmd_mailbox *inbox,
			    काष्ठा mlx4_cmd_mailbox *outbox,
			    काष्ठा mlx4_cmd_info *cmd)
अणु
	काष्ठा mlx4_access_reg *inbuf = inbox->buf;
	u8 method = inbuf->method & MLX4_ACCESS_REG_METHOD_MASK;
	u16 reg_id = be16_to_cpu(inbuf->reg_id);

	अगर (slave != mlx4_master_func_num(dev) &&
	    method == MLX4_ACCESS_REG_WRITE)
		वापस -EPERM;

	अगर (reg_id == MLX4_REG_ID_PTYS) अणु
		काष्ठा mlx4_ptys_reg *ptys_reg =
			(काष्ठा mlx4_ptys_reg *)inbuf->reg_data;

		ptys_reg->local_port =
			mlx4_slave_convert_port(dev, slave,
						ptys_reg->local_port);
	पूर्ण

	वापस mlx4_cmd_box(dev, inbox->dma, outbox->dma, vhcr->in_modअगरier,
			    0, MLX4_CMD_ACCESS_REG, MLX4_CMD_TIME_CLASS_C,
			    MLX4_CMD_NATIVE);
पूर्ण

अटल पूर्णांक mlx4_SET_PORT_phv_bit(काष्ठा mlx4_dev *dev, u8 port, u8 phv_bit)
अणु
#घोषणा SET_PORT_GEN_PHV_VALID	0x10
#घोषणा SET_PORT_GEN_PHV_EN	0x80

	काष्ठा mlx4_cmd_mailbox *mailbox;
	काष्ठा mlx4_set_port_general_context *context;
	u32 in_mod;
	पूर्णांक err;

	mailbox = mlx4_alloc_cmd_mailbox(dev);
	अगर (IS_ERR(mailbox))
		वापस PTR_ERR(mailbox);
	context = mailbox->buf;

	context->flags2 |=  SET_PORT_GEN_PHV_VALID;
	अगर (phv_bit)
		context->phv_en |=  SET_PORT_GEN_PHV_EN;

	in_mod = MLX4_SET_PORT_GENERAL << 8 | port;
	err = mlx4_cmd(dev, mailbox->dma, in_mod, MLX4_SET_PORT_ETH_OPCODE,
		       MLX4_CMD_SET_PORT, MLX4_CMD_TIME_CLASS_B,
		       MLX4_CMD_NATIVE);

	mlx4_मुक्त_cmd_mailbox(dev, mailbox);
	वापस err;
पूर्ण

पूर्णांक get_phv_bit(काष्ठा mlx4_dev *dev, u8 port, पूर्णांक *phv)
अणु
	पूर्णांक err;
	काष्ठा mlx4_func_cap func_cap;

	स_रखो(&func_cap, 0, माप(func_cap));
	err = mlx4_QUERY_FUNC_CAP(dev, port, &func_cap);
	अगर (!err)
		*phv = func_cap.flags0 & QUERY_FUNC_CAP_PHV_BIT;
	वापस err;
पूर्ण
EXPORT_SYMBOL(get_phv_bit);

पूर्णांक set_phv_bit(काष्ठा mlx4_dev *dev, u8 port, पूर्णांक new_val)
अणु
	पूर्णांक ret;

	अगर (mlx4_is_slave(dev))
		वापस -EPERM;

	अगर (dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_PHV_EN &&
	    !(dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_SKIP_OUTER_VLAN)) अणु
		ret = mlx4_SET_PORT_phv_bit(dev, port, new_val);
		अगर (!ret)
			dev->caps.phv_bit[port] = new_val;
		वापस ret;
	पूर्ण

	वापस -EOPNOTSUPP;
पूर्ण
EXPORT_SYMBOL(set_phv_bit);

पूर्णांक mlx4_get_is_vlan_offload_disabled(काष्ठा mlx4_dev *dev, u8 port,
				      bool *vlan_offload_disabled)
अणु
	काष्ठा mlx4_func_cap func_cap;
	पूर्णांक err;

	स_रखो(&func_cap, 0, माप(func_cap));
	err = mlx4_QUERY_FUNC_CAP(dev, port, &func_cap);
	अगर (!err)
		*vlan_offload_disabled =
			!!(func_cap.flags0 &
			   QUERY_FUNC_CAP_VLAN_OFFLOAD_DISABLE);
	वापस err;
पूर्ण
EXPORT_SYMBOL(mlx4_get_is_vlan_offload_disabled);

व्योम mlx4_replace_zero_macs(काष्ठा mlx4_dev *dev)
अणु
	पूर्णांक i;
	u8 mac_addr[ETH_ALEN];

	dev->port_अक्रमom_macs = 0;
	क्रम (i = 1; i <= dev->caps.num_ports; ++i)
		अगर (!dev->caps.def_mac[i] &&
		    dev->caps.port_type[i] == MLX4_PORT_TYPE_ETH) अणु
			eth_अक्रमom_addr(mac_addr);
			dev->port_अक्रमom_macs |= 1 << i;
			dev->caps.def_mac[i] = mlx4_mac_to_u64(mac_addr);
		पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_replace_zero_macs);
