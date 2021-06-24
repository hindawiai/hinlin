<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0 */
/* Copyright (c) 2018 Mellanox Technologies. All rights reserved */

#अगर_अघोषित _MLXSW_SPECTRUM_NVE_H
#घोषणा _MLXSW_SPECTRUM_NVE_H

#समावेश <linux/netlink.h>
#समावेश <linux/rhashtable.h>

#समावेश "spectrum.h"

काष्ठा mlxsw_sp_nve_config अणु
	क्रमागत mlxsw_sp_nve_type type;
	u8 ttl;
	u8 learning_en:1;
	__be16 udp_dport;
	__be32 flowlabel;
	u32 ul_tb_id;
	क्रमागत mlxsw_sp_l3proto ul_proto;
	जोड़ mlxsw_sp_l3addr ul_sip;
पूर्ण;

काष्ठा mlxsw_sp_nve अणु
	काष्ठा mlxsw_sp_nve_config config;
	काष्ठा rhashtable mc_list_ht;
	काष्ठा mlxsw_sp *mlxsw_sp;
	स्थिर काष्ठा mlxsw_sp_nve_ops **nve_ops_arr;
	अचिन्हित पूर्णांक num_nve_tunnels;	/* Protected by RTNL */
	अचिन्हित पूर्णांक num_max_mc_entries[MLXSW_SP_L3_PROTO_MAX];
	u32 tunnel_index;
	u16 ul_rअगर_index;	/* Reserved क्रम Spectrum */
	अचिन्हित पूर्णांक inc_parsing_depth_refs;
पूर्ण;

काष्ठा mlxsw_sp_nve_ops अणु
	क्रमागत mlxsw_sp_nve_type type;
	bool (*can_offload)(स्थिर काष्ठा mlxsw_sp_nve *nve,
			    स्थिर काष्ठा mlxsw_sp_nve_params *params,
			    काष्ठा netlink_ext_ack *extack);
	व्योम (*nve_config)(स्थिर काष्ठा mlxsw_sp_nve *nve,
			   स्थिर काष्ठा mlxsw_sp_nve_params *params,
			   काष्ठा mlxsw_sp_nve_config *config);
	पूर्णांक (*init)(काष्ठा mlxsw_sp_nve *nve,
		    स्थिर काष्ठा mlxsw_sp_nve_config *config);
	व्योम (*fini)(काष्ठा mlxsw_sp_nve *nve);
	पूर्णांक (*fdb_replay)(स्थिर काष्ठा net_device *nve_dev, __be32 vni,
			  काष्ठा netlink_ext_ack *extack);
	व्योम (*fdb_clear_offload)(स्थिर काष्ठा net_device *nve_dev, __be32 vni);
पूर्ण;

बाह्य स्थिर काष्ठा mlxsw_sp_nve_ops mlxsw_sp1_nve_vxlan_ops;
बाह्य स्थिर काष्ठा mlxsw_sp_nve_ops mlxsw_sp2_nve_vxlan_ops;

#पूर्ण_अगर
