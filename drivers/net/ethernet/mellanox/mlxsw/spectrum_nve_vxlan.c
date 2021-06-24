<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/* Copyright (c) 2018 Mellanox Technologies. All rights reserved */

#समावेश <linux/netdevice.h>
#समावेश <linux/netlink.h>
#समावेश <linux/अक्रमom.h>
#समावेश <net/vxlan.h>

#समावेश "reg.h"
#समावेश "spectrum.h"
#समावेश "spectrum_nve.h"

/* Eth (18B) | IPv6 (40B) | UDP (8B) | VxLAN (8B) | Eth (14B) | IPv6 (40B)
 *
 * In the worst हाल - where we have a VLAN tag on the outer Ethernet
 * header and IPv6 in overlay and underlay - we need to parse 128 bytes
 */
#घोषणा MLXSW_SP_NVE_VXLAN_PARSING_DEPTH 128
#घोषणा MLXSW_SP_NVE_DEFAULT_PARSING_DEPTH 96

#घोषणा MLXSW_SP_NVE_VXLAN_SUPPORTED_FLAGS	(VXLAN_F_UDP_ZERO_CSUM_TX | \
						 VXLAN_F_LEARN)

अटल bool mlxsw_sp_nve_vxlan_can_offload(स्थिर काष्ठा mlxsw_sp_nve *nve,
					   स्थिर काष्ठा mlxsw_sp_nve_params *params,
					   काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा vxlan_dev *vxlan = netdev_priv(params->dev);
	काष्ठा vxlan_config *cfg = &vxlan->cfg;

	अगर (cfg->saddr.sa.sa_family != AF_INET) अणु
		NL_SET_ERR_MSG_MOD(extack, "VxLAN: Only IPv4 underlay is supported");
		वापस false;
	पूर्ण

	अगर (vxlan_addr_multicast(&cfg->remote_ip)) अणु
		NL_SET_ERR_MSG_MOD(extack, "VxLAN: Multicast destination IP is not supported");
		वापस false;
	पूर्ण

	अगर (vxlan_addr_any(&cfg->saddr)) अणु
		NL_SET_ERR_MSG_MOD(extack, "VxLAN: Source address must be specified");
		वापस false;
	पूर्ण

	अगर (cfg->remote_अगरindex) अणु
		NL_SET_ERR_MSG_MOD(extack, "VxLAN: Local interface is not supported");
		वापस false;
	पूर्ण

	अगर (cfg->port_min || cfg->port_max) अणु
		NL_SET_ERR_MSG_MOD(extack, "VxLAN: Only default UDP source port range is supported");
		वापस false;
	पूर्ण

	अगर (cfg->tos != 1) अणु
		NL_SET_ERR_MSG_MOD(extack, "VxLAN: TOS must be configured to inherit");
		वापस false;
	पूर्ण

	अगर (cfg->flags & VXLAN_F_TTL_INHERIT) अणु
		NL_SET_ERR_MSG_MOD(extack, "VxLAN: TTL must not be configured to inherit");
		वापस false;
	पूर्ण

	अगर (!(cfg->flags & VXLAN_F_UDP_ZERO_CSUM_TX)) अणु
		NL_SET_ERR_MSG_MOD(extack, "VxLAN: UDP checksum is not supported");
		वापस false;
	पूर्ण

	अगर (cfg->flags & ~MLXSW_SP_NVE_VXLAN_SUPPORTED_FLAGS) अणु
		NL_SET_ERR_MSG_MOD(extack, "VxLAN: Unsupported flag");
		वापस false;
	पूर्ण

	अगर (cfg->ttl == 0) अणु
		NL_SET_ERR_MSG_MOD(extack, "VxLAN: TTL must not be configured to 0");
		वापस false;
	पूर्ण

	अगर (cfg->label != 0) अणु
		NL_SET_ERR_MSG_MOD(extack, "VxLAN: Flow label must be configured to 0");
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल bool mlxsw_sp1_nve_vxlan_can_offload(स्थिर काष्ठा mlxsw_sp_nve *nve,
					    स्थिर काष्ठा mlxsw_sp_nve_params *params,
					    काष्ठा netlink_ext_ack *extack)
अणु
	अगर (params->ethertype == ETH_P_8021AD) अणु
		NL_SET_ERR_MSG_MOD(extack, "VxLAN: 802.1ad bridge is not supported with VxLAN");
		वापस false;
	पूर्ण

	वापस mlxsw_sp_nve_vxlan_can_offload(nve, params, extack);
पूर्ण

अटल व्योम mlxsw_sp_nve_vxlan_config(स्थिर काष्ठा mlxsw_sp_nve *nve,
				      स्थिर काष्ठा mlxsw_sp_nve_params *params,
				      काष्ठा mlxsw_sp_nve_config *config)
अणु
	काष्ठा vxlan_dev *vxlan = netdev_priv(params->dev);
	काष्ठा vxlan_config *cfg = &vxlan->cfg;

	config->type = MLXSW_SP_NVE_TYPE_VXLAN;
	config->ttl = cfg->ttl;
	config->flowlabel = cfg->label;
	config->learning_en = cfg->flags & VXLAN_F_LEARN ? 1 : 0;
	config->ul_tb_id = RT_TABLE_MAIN;
	config->ul_proto = MLXSW_SP_L3_PROTO_IPV4;
	config->ul_sip.addr4 = cfg->saddr.sin.sin_addr.s_addr;
	config->udp_dport = cfg->dst_port;
पूर्ण

अटल पूर्णांक __mlxsw_sp_nve_parsing_set(काष्ठा mlxsw_sp *mlxsw_sp,
				      अचिन्हित पूर्णांक parsing_depth,
				      __be16 udp_dport)
अणु
	अक्षर mprs_pl[MLXSW_REG_MPRS_LEN];

	mlxsw_reg_mprs_pack(mprs_pl, parsing_depth, be16_to_cpu(udp_dport));
	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(mprs), mprs_pl);
पूर्ण

अटल पूर्णांक mlxsw_sp_nve_parsing_set(काष्ठा mlxsw_sp *mlxsw_sp,
				    __be16 udp_dport)
अणु
	पूर्णांक parsing_depth = mlxsw_sp->nve->inc_parsing_depth_refs ?
				MLXSW_SP_NVE_VXLAN_PARSING_DEPTH :
				MLXSW_SP_NVE_DEFAULT_PARSING_DEPTH;

	वापस __mlxsw_sp_nve_parsing_set(mlxsw_sp, parsing_depth, udp_dport);
पूर्ण

अटल पूर्णांक
__mlxsw_sp_nve_inc_parsing_depth_get(काष्ठा mlxsw_sp *mlxsw_sp,
				     __be16 udp_dport)
अणु
	पूर्णांक err;

	mlxsw_sp->nve->inc_parsing_depth_refs++;

	err = mlxsw_sp_nve_parsing_set(mlxsw_sp, udp_dport);
	अगर (err)
		जाओ err_nve_parsing_set;
	वापस 0;

err_nve_parsing_set:
	mlxsw_sp->nve->inc_parsing_depth_refs--;
	वापस err;
पूर्ण

अटल व्योम
__mlxsw_sp_nve_inc_parsing_depth_put(काष्ठा mlxsw_sp *mlxsw_sp,
				     __be16 udp_dport)
अणु
	mlxsw_sp->nve->inc_parsing_depth_refs--;
	mlxsw_sp_nve_parsing_set(mlxsw_sp, udp_dport);
पूर्ण

पूर्णांक mlxsw_sp_nve_inc_parsing_depth_get(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	__be16 udp_dport = mlxsw_sp->nve->config.udp_dport;

	वापस __mlxsw_sp_nve_inc_parsing_depth_get(mlxsw_sp, udp_dport);
पूर्ण

व्योम mlxsw_sp_nve_inc_parsing_depth_put(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	__be16 udp_dport = mlxsw_sp->nve->config.udp_dport;

	__mlxsw_sp_nve_inc_parsing_depth_put(mlxsw_sp, udp_dport);
पूर्ण

अटल व्योम
mlxsw_sp_nve_vxlan_config_prepare(अक्षर *tngcr_pl,
				  स्थिर काष्ठा mlxsw_sp_nve_config *config)
अणु
	u8 udp_sport;

	mlxsw_reg_tngcr_pack(tngcr_pl, MLXSW_REG_TNGCR_TYPE_VXLAN, true,
			     config->ttl);
	/* VxLAN driver's शेष UDP source port range is 32768 (0x8000)
	 * to 60999 (0xee47). Set the upper 8 bits of the UDP source port
	 * to a अक्रमom number between 0x80 and 0xee
	 */
	get_अक्रमom_bytes(&udp_sport, माप(udp_sport));
	udp_sport = (udp_sport % (0xee - 0x80 + 1)) + 0x80;
	mlxsw_reg_tngcr_nve_udp_sport_prefix_set(tngcr_pl, udp_sport);
	mlxsw_reg_tngcr_usipv4_set(tngcr_pl, be32_to_cpu(config->ul_sip.addr4));
पूर्ण

अटल पूर्णांक
mlxsw_sp1_nve_vxlan_config_set(काष्ठा mlxsw_sp *mlxsw_sp,
			       स्थिर काष्ठा mlxsw_sp_nve_config *config)
अणु
	अक्षर tngcr_pl[MLXSW_REG_TNGCR_LEN];
	u16 ul_vr_id;
	पूर्णांक err;

	err = mlxsw_sp_router_tb_id_vr_id(mlxsw_sp, config->ul_tb_id,
					  &ul_vr_id);
	अगर (err)
		वापस err;

	mlxsw_sp_nve_vxlan_config_prepare(tngcr_pl, config);
	mlxsw_reg_tngcr_learn_enable_set(tngcr_pl, config->learning_en);
	mlxsw_reg_tngcr_underlay_भव_router_set(tngcr_pl, ul_vr_id);

	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(tngcr), tngcr_pl);
पूर्ण

अटल व्योम mlxsw_sp1_nve_vxlan_config_clear(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	अक्षर tngcr_pl[MLXSW_REG_TNGCR_LEN];

	mlxsw_reg_tngcr_pack(tngcr_pl, MLXSW_REG_TNGCR_TYPE_VXLAN, false, 0);

	mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(tngcr), tngcr_pl);
पूर्ण

अटल पूर्णांक mlxsw_sp1_nve_vxlan_rtdp_set(काष्ठा mlxsw_sp *mlxsw_sp,
					अचिन्हित पूर्णांक tunnel_index)
अणु
	अक्षर rtdp_pl[MLXSW_REG_RTDP_LEN];

	mlxsw_reg_rtdp_pack(rtdp_pl, MLXSW_REG_RTDP_TYPE_NVE, tunnel_index);

	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(rtdp), rtdp_pl);
पूर्ण

अटल पूर्णांक mlxsw_sp1_nve_vxlan_init(काष्ठा mlxsw_sp_nve *nve,
				    स्थिर काष्ठा mlxsw_sp_nve_config *config)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = nve->mlxsw_sp;
	पूर्णांक err;

	err = __mlxsw_sp_nve_inc_parsing_depth_get(mlxsw_sp, config->udp_dport);
	अगर (err)
		वापस err;

	err = mlxsw_sp1_nve_vxlan_config_set(mlxsw_sp, config);
	अगर (err)
		जाओ err_config_set;

	err = mlxsw_sp1_nve_vxlan_rtdp_set(mlxsw_sp, nve->tunnel_index);
	अगर (err)
		जाओ err_rtdp_set;

	err = mlxsw_sp_router_nve_promote_decap(mlxsw_sp, config->ul_tb_id,
						config->ul_proto,
						&config->ul_sip,
						nve->tunnel_index);
	अगर (err)
		जाओ err_promote_decap;

	वापस 0;

err_promote_decap:
err_rtdp_set:
	mlxsw_sp1_nve_vxlan_config_clear(mlxsw_sp);
err_config_set:
	__mlxsw_sp_nve_inc_parsing_depth_put(mlxsw_sp, 0);
	वापस err;
पूर्ण

अटल व्योम mlxsw_sp1_nve_vxlan_fini(काष्ठा mlxsw_sp_nve *nve)
अणु
	काष्ठा mlxsw_sp_nve_config *config = &nve->config;
	काष्ठा mlxsw_sp *mlxsw_sp = nve->mlxsw_sp;

	mlxsw_sp_router_nve_demote_decap(mlxsw_sp, config->ul_tb_id,
					 config->ul_proto, &config->ul_sip);
	mlxsw_sp1_nve_vxlan_config_clear(mlxsw_sp);
	__mlxsw_sp_nve_inc_parsing_depth_put(mlxsw_sp, 0);
पूर्ण

अटल पूर्णांक
mlxsw_sp_nve_vxlan_fdb_replay(स्थिर काष्ठा net_device *nve_dev, __be32 vni,
			      काष्ठा netlink_ext_ack *extack)
अणु
	अगर (WARN_ON(!netअगर_is_vxlan(nve_dev)))
		वापस -EINVAL;
	वापस vxlan_fdb_replay(nve_dev, vni, &mlxsw_sp_चयनdev_notअगरier,
				extack);
पूर्ण

अटल व्योम
mlxsw_sp_nve_vxlan_clear_offload(स्थिर काष्ठा net_device *nve_dev, __be32 vni)
अणु
	अगर (WARN_ON(!netअगर_is_vxlan(nve_dev)))
		वापस;
	vxlan_fdb_clear_offload(nve_dev, vni);
पूर्ण

स्थिर काष्ठा mlxsw_sp_nve_ops mlxsw_sp1_nve_vxlan_ops = अणु
	.type		= MLXSW_SP_NVE_TYPE_VXLAN,
	.can_offload	= mlxsw_sp1_nve_vxlan_can_offload,
	.nve_config	= mlxsw_sp_nve_vxlan_config,
	.init		= mlxsw_sp1_nve_vxlan_init,
	.fini		= mlxsw_sp1_nve_vxlan_fini,
	.fdb_replay	= mlxsw_sp_nve_vxlan_fdb_replay,
	.fdb_clear_offload = mlxsw_sp_nve_vxlan_clear_offload,
पूर्ण;

अटल bool mlxsw_sp2_nve_vxlan_learning_set(काष्ठा mlxsw_sp *mlxsw_sp,
					     bool learning_en)
अणु
	अक्षर tnpc_pl[MLXSW_REG_TNPC_LEN];

	mlxsw_reg_tnpc_pack(tnpc_pl, MLXSW_REG_TUNNEL_PORT_NVE,
			    learning_en);
	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(tnpc), tnpc_pl);
पूर्ण

अटल पूर्णांक
mlxsw_sp2_nve_decap_ethertype_set(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	अक्षर spvid_pl[MLXSW_REG_SPVID_LEN] = अणुपूर्ण;

	mlxsw_reg_spvid_tport_set(spvid_pl, true);
	mlxsw_reg_spvid_local_port_set(spvid_pl,
				       MLXSW_REG_TUNNEL_PORT_NVE);
	mlxsw_reg_spvid_egr_et_set_set(spvid_pl, true);
	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(spvid), spvid_pl);
पूर्ण

अटल पूर्णांक
mlxsw_sp2_nve_vxlan_config_set(काष्ठा mlxsw_sp *mlxsw_sp,
			       स्थिर काष्ठा mlxsw_sp_nve_config *config)
अणु
	अक्षर tngcr_pl[MLXSW_REG_TNGCR_LEN];
	अक्षर spvtr_pl[MLXSW_REG_SPVTR_LEN];
	u16 ul_rअगर_index;
	पूर्णांक err;

	err = mlxsw_sp_router_ul_rअगर_get(mlxsw_sp, config->ul_tb_id,
					 &ul_rअगर_index);
	अगर (err)
		वापस err;
	mlxsw_sp->nve->ul_rअगर_index = ul_rअगर_index;

	err = mlxsw_sp2_nve_vxlan_learning_set(mlxsw_sp, config->learning_en);
	अगर (err)
		जाओ err_vxlan_learning_set;

	mlxsw_sp_nve_vxlan_config_prepare(tngcr_pl, config);
	mlxsw_reg_tngcr_underlay_rअगर_set(tngcr_pl, ul_rअगर_index);

	err = mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(tngcr), tngcr_pl);
	अगर (err)
		जाओ err_tngcr_ग_लिखो;

	mlxsw_reg_spvtr_pack(spvtr_pl, true, MLXSW_REG_TUNNEL_PORT_NVE,
			     MLXSW_REG_SPVTR_IPVID_MODE_ALWAYS_PUSH_VLAN);
	err = mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(spvtr), spvtr_pl);
	अगर (err)
		जाओ err_spvtr_ग_लिखो;

	err = mlxsw_sp2_nve_decap_ethertype_set(mlxsw_sp);
	अगर (err)
		जाओ err_decap_ethertype_set;

	वापस 0;

err_decap_ethertype_set:
	mlxsw_reg_spvtr_pack(spvtr_pl, true, MLXSW_REG_TUNNEL_PORT_NVE,
			     MLXSW_REG_SPVTR_IPVID_MODE_IEEE_COMPLIANT_PVID);
	mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(spvtr), spvtr_pl);
err_spvtr_ग_लिखो:
	mlxsw_reg_tngcr_pack(tngcr_pl, MLXSW_REG_TNGCR_TYPE_VXLAN, false, 0);
	mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(tngcr), tngcr_pl);
err_tngcr_ग_लिखो:
	mlxsw_sp2_nve_vxlan_learning_set(mlxsw_sp, false);
err_vxlan_learning_set:
	mlxsw_sp_router_ul_rअगर_put(mlxsw_sp, ul_rअगर_index);
	वापस err;
पूर्ण

अटल व्योम mlxsw_sp2_nve_vxlan_config_clear(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	अक्षर spvtr_pl[MLXSW_REG_SPVTR_LEN];
	अक्षर tngcr_pl[MLXSW_REG_TNGCR_LEN];

	mlxsw_reg_spvtr_pack(spvtr_pl, true, MLXSW_REG_TUNNEL_PORT_NVE,
			     MLXSW_REG_SPVTR_IPVID_MODE_IEEE_COMPLIANT_PVID);
	mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(spvtr), spvtr_pl);
	mlxsw_reg_tngcr_pack(tngcr_pl, MLXSW_REG_TNGCR_TYPE_VXLAN, false, 0);
	mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(tngcr), tngcr_pl);
	mlxsw_sp2_nve_vxlan_learning_set(mlxsw_sp, false);
	mlxsw_sp_router_ul_rअगर_put(mlxsw_sp, mlxsw_sp->nve->ul_rअगर_index);
पूर्ण

अटल पूर्णांक mlxsw_sp2_nve_vxlan_rtdp_set(काष्ठा mlxsw_sp *mlxsw_sp,
					अचिन्हित पूर्णांक tunnel_index,
					u16 ul_rअगर_index)
अणु
	अक्षर rtdp_pl[MLXSW_REG_RTDP_LEN];

	mlxsw_reg_rtdp_pack(rtdp_pl, MLXSW_REG_RTDP_TYPE_NVE, tunnel_index);
	mlxsw_reg_rtdp_egress_router_पूर्णांकerface_set(rtdp_pl, ul_rअगर_index);

	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(rtdp), rtdp_pl);
पूर्ण

अटल पूर्णांक mlxsw_sp2_nve_vxlan_init(काष्ठा mlxsw_sp_nve *nve,
				    स्थिर काष्ठा mlxsw_sp_nve_config *config)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = nve->mlxsw_sp;
	पूर्णांक err;

	err = __mlxsw_sp_nve_inc_parsing_depth_get(mlxsw_sp, config->udp_dport);
	अगर (err)
		वापस err;

	err = mlxsw_sp2_nve_vxlan_config_set(mlxsw_sp, config);
	अगर (err)
		जाओ err_config_set;

	err = mlxsw_sp2_nve_vxlan_rtdp_set(mlxsw_sp, nve->tunnel_index,
					   nve->ul_rअगर_index);
	अगर (err)
		जाओ err_rtdp_set;

	err = mlxsw_sp_router_nve_promote_decap(mlxsw_sp, config->ul_tb_id,
						config->ul_proto,
						&config->ul_sip,
						nve->tunnel_index);
	अगर (err)
		जाओ err_promote_decap;

	वापस 0;

err_promote_decap:
err_rtdp_set:
	mlxsw_sp2_nve_vxlan_config_clear(mlxsw_sp);
err_config_set:
	__mlxsw_sp_nve_inc_parsing_depth_put(mlxsw_sp, 0);
	वापस err;
पूर्ण

अटल व्योम mlxsw_sp2_nve_vxlan_fini(काष्ठा mlxsw_sp_nve *nve)
अणु
	काष्ठा mlxsw_sp_nve_config *config = &nve->config;
	काष्ठा mlxsw_sp *mlxsw_sp = nve->mlxsw_sp;

	mlxsw_sp_router_nve_demote_decap(mlxsw_sp, config->ul_tb_id,
					 config->ul_proto, &config->ul_sip);
	mlxsw_sp2_nve_vxlan_config_clear(mlxsw_sp);
	__mlxsw_sp_nve_inc_parsing_depth_put(mlxsw_sp, 0);
पूर्ण

स्थिर काष्ठा mlxsw_sp_nve_ops mlxsw_sp2_nve_vxlan_ops = अणु
	.type		= MLXSW_SP_NVE_TYPE_VXLAN,
	.can_offload	= mlxsw_sp_nve_vxlan_can_offload,
	.nve_config	= mlxsw_sp_nve_vxlan_config,
	.init		= mlxsw_sp2_nve_vxlan_init,
	.fini		= mlxsw_sp2_nve_vxlan_fini,
	.fdb_replay	= mlxsw_sp_nve_vxlan_fdb_replay,
	.fdb_clear_offload = mlxsw_sp_nve_vxlan_clear_offload,
पूर्ण;
