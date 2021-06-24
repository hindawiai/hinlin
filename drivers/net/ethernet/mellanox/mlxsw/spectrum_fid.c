<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/* Copyright (c) 2017-2018 Mellanox Technologies. All rights reserved */

#समावेश <linux/kernel.h>
#समावेश <linux/bitops.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/अगर_bridge.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/rhashtable.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/refcount.h>

#समावेश "spectrum.h"
#समावेश "reg.h"

काष्ठा mlxsw_sp_fid_family;

काष्ठा mlxsw_sp_fid_core अणु
	काष्ठा rhashtable fid_ht;
	काष्ठा rhashtable vni_ht;
	काष्ठा mlxsw_sp_fid_family *fid_family_arr[MLXSW_SP_FID_TYPE_MAX];
	अचिन्हित पूर्णांक *port_fid_mappings;
पूर्ण;

काष्ठा mlxsw_sp_fid अणु
	काष्ठा list_head list;
	काष्ठा mlxsw_sp_rअगर *rअगर;
	refcount_t ref_count;
	u16 fid_index;
	काष्ठा mlxsw_sp_fid_family *fid_family;
	काष्ठा rhash_head ht_node;

	काष्ठा rhash_head vni_ht_node;
	क्रमागत mlxsw_sp_nve_type nve_type;
	__be32 vni;
	u32 nve_flood_index;
	पूर्णांक nve_अगरindex;
	u8 vni_valid:1,
	   nve_flood_index_valid:1;
पूर्ण;

काष्ठा mlxsw_sp_fid_8021q अणु
	काष्ठा mlxsw_sp_fid common;
	u16 vid;
पूर्ण;

काष्ठा mlxsw_sp_fid_8021d अणु
	काष्ठा mlxsw_sp_fid common;
	पूर्णांक br_अगरindex;
पूर्ण;

अटल स्थिर काष्ठा rhashtable_params mlxsw_sp_fid_ht_params = अणु
	.key_len = माप_field(काष्ठा mlxsw_sp_fid, fid_index),
	.key_offset = दुरत्व(काष्ठा mlxsw_sp_fid, fid_index),
	.head_offset = दुरत्व(काष्ठा mlxsw_sp_fid, ht_node),
पूर्ण;

अटल स्थिर काष्ठा rhashtable_params mlxsw_sp_fid_vni_ht_params = अणु
	.key_len = माप_field(काष्ठा mlxsw_sp_fid, vni),
	.key_offset = दुरत्व(काष्ठा mlxsw_sp_fid, vni),
	.head_offset = दुरत्व(काष्ठा mlxsw_sp_fid, vni_ht_node),
पूर्ण;

काष्ठा mlxsw_sp_flood_table अणु
	क्रमागत mlxsw_sp_flood_type packet_type;
	क्रमागत mlxsw_reg_sfgc_bridge_type bridge_type;
	क्रमागत mlxsw_flood_table_type table_type;
	पूर्णांक table_index;
पूर्ण;

काष्ठा mlxsw_sp_fid_ops अणु
	व्योम (*setup)(काष्ठा mlxsw_sp_fid *fid, स्थिर व्योम *arg);
	पूर्णांक (*configure)(काष्ठा mlxsw_sp_fid *fid);
	व्योम (*deconfigure)(काष्ठा mlxsw_sp_fid *fid);
	पूर्णांक (*index_alloc)(काष्ठा mlxsw_sp_fid *fid, स्थिर व्योम *arg,
			   u16 *p_fid_index);
	bool (*compare)(स्थिर काष्ठा mlxsw_sp_fid *fid,
			स्थिर व्योम *arg);
	u16 (*flood_index)(स्थिर काष्ठा mlxsw_sp_fid *fid);
	पूर्णांक (*port_vid_map)(काष्ठा mlxsw_sp_fid *fid,
			    काष्ठा mlxsw_sp_port *port, u16 vid);
	व्योम (*port_vid_unmap)(काष्ठा mlxsw_sp_fid *fid,
			       काष्ठा mlxsw_sp_port *port, u16 vid);
	पूर्णांक (*vni_set)(काष्ठा mlxsw_sp_fid *fid, __be32 vni);
	व्योम (*vni_clear)(काष्ठा mlxsw_sp_fid *fid);
	पूर्णांक (*nve_flood_index_set)(काष्ठा mlxsw_sp_fid *fid,
				   u32 nve_flood_index);
	व्योम (*nve_flood_index_clear)(काष्ठा mlxsw_sp_fid *fid);
	व्योम (*fdb_clear_offload)(स्थिर काष्ठा mlxsw_sp_fid *fid,
				  स्थिर काष्ठा net_device *nve_dev);
पूर्ण;

काष्ठा mlxsw_sp_fid_family अणु
	क्रमागत mlxsw_sp_fid_type type;
	माप_प्रकार fid_size;
	u16 start_index;
	u16 end_index;
	काष्ठा list_head fids_list;
	अचिन्हित दीर्घ *fids_biपंचांगap;
	स्थिर काष्ठा mlxsw_sp_flood_table *flood_tables;
	पूर्णांक nr_flood_tables;
	क्रमागत mlxsw_sp_rअगर_type rअगर_type;
	स्थिर काष्ठा mlxsw_sp_fid_ops *ops;
	काष्ठा mlxsw_sp *mlxsw_sp;
	u8 lag_vid_valid:1;
पूर्ण;

अटल स्थिर पूर्णांक mlxsw_sp_sfgc_uc_packet_types[MLXSW_REG_SFGC_TYPE_MAX] = अणु
	[MLXSW_REG_SFGC_TYPE_UNKNOWN_UNICAST]			= 1,
पूर्ण;

अटल स्थिर पूर्णांक mlxsw_sp_sfgc_bc_packet_types[MLXSW_REG_SFGC_TYPE_MAX] = अणु
	[MLXSW_REG_SFGC_TYPE_BROADCAST]				= 1,
	[MLXSW_REG_SFGC_TYPE_UNREGISTERED_MULTICAST_NON_IP]	= 1,
	[MLXSW_REG_SFGC_TYPE_IPV4_LINK_LOCAL]			= 1,
	[MLXSW_REG_SFGC_TYPE_IPV6_ALL_HOST]			= 1,
	[MLXSW_REG_SFGC_TYPE_UNREGISTERED_MULTICAST_IPV6]	= 1,
पूर्ण;

अटल स्थिर पूर्णांक mlxsw_sp_sfgc_mc_packet_types[MLXSW_REG_SFGC_TYPE_MAX] = अणु
	[MLXSW_REG_SFGC_TYPE_UNREGISTERED_MULTICAST_IPV4]	= 1,
पूर्ण;

अटल स्थिर पूर्णांक *mlxsw_sp_packet_type_sfgc_types[] = अणु
	[MLXSW_SP_FLOOD_TYPE_UC]	= mlxsw_sp_sfgc_uc_packet_types,
	[MLXSW_SP_FLOOD_TYPE_BC]	= mlxsw_sp_sfgc_bc_packet_types,
	[MLXSW_SP_FLOOD_TYPE_MC]	= mlxsw_sp_sfgc_mc_packet_types,
पूर्ण;

bool mlxsw_sp_fid_is_dummy(काष्ठा mlxsw_sp *mlxsw_sp, u16 fid_index)
अणु
	क्रमागत mlxsw_sp_fid_type fid_type = MLXSW_SP_FID_TYPE_DUMMY;
	काष्ठा mlxsw_sp_fid_family *fid_family;

	fid_family = mlxsw_sp->fid_core->fid_family_arr[fid_type];

	वापस fid_family->start_index == fid_index;
पूर्ण

bool mlxsw_sp_fid_lag_vid_valid(स्थिर काष्ठा mlxsw_sp_fid *fid)
अणु
	वापस fid->fid_family->lag_vid_valid;
पूर्ण

काष्ठा mlxsw_sp_fid *mlxsw_sp_fid_lookup_by_index(काष्ठा mlxsw_sp *mlxsw_sp,
						  u16 fid_index)
अणु
	काष्ठा mlxsw_sp_fid *fid;

	fid = rhashtable_lookup_fast(&mlxsw_sp->fid_core->fid_ht, &fid_index,
				     mlxsw_sp_fid_ht_params);
	अगर (fid)
		refcount_inc(&fid->ref_count);

	वापस fid;
पूर्ण

पूर्णांक mlxsw_sp_fid_nve_अगरindex(स्थिर काष्ठा mlxsw_sp_fid *fid, पूर्णांक *nve_अगरindex)
अणु
	अगर (!fid->vni_valid)
		वापस -EINVAL;

	*nve_अगरindex = fid->nve_अगरindex;

	वापस 0;
पूर्ण

पूर्णांक mlxsw_sp_fid_nve_type(स्थिर काष्ठा mlxsw_sp_fid *fid,
			  क्रमागत mlxsw_sp_nve_type *p_type)
अणु
	अगर (!fid->vni_valid)
		वापस -EINVAL;

	*p_type = fid->nve_type;

	वापस 0;
पूर्ण

काष्ठा mlxsw_sp_fid *mlxsw_sp_fid_lookup_by_vni(काष्ठा mlxsw_sp *mlxsw_sp,
						__be32 vni)
अणु
	काष्ठा mlxsw_sp_fid *fid;

	fid = rhashtable_lookup_fast(&mlxsw_sp->fid_core->vni_ht, &vni,
				     mlxsw_sp_fid_vni_ht_params);
	अगर (fid)
		refcount_inc(&fid->ref_count);

	वापस fid;
पूर्ण

पूर्णांक mlxsw_sp_fid_vni(स्थिर काष्ठा mlxsw_sp_fid *fid, __be32 *vni)
अणु
	अगर (!fid->vni_valid)
		वापस -EINVAL;

	*vni = fid->vni;

	वापस 0;
पूर्ण

पूर्णांक mlxsw_sp_fid_nve_flood_index_set(काष्ठा mlxsw_sp_fid *fid,
				     u32 nve_flood_index)
अणु
	काष्ठा mlxsw_sp_fid_family *fid_family = fid->fid_family;
	स्थिर काष्ठा mlxsw_sp_fid_ops *ops = fid_family->ops;
	पूर्णांक err;

	अगर (WARN_ON(!ops->nve_flood_index_set || fid->nve_flood_index_valid))
		वापस -EINVAL;

	err = ops->nve_flood_index_set(fid, nve_flood_index);
	अगर (err)
		वापस err;

	fid->nve_flood_index = nve_flood_index;
	fid->nve_flood_index_valid = true;

	वापस 0;
पूर्ण

व्योम mlxsw_sp_fid_nve_flood_index_clear(काष्ठा mlxsw_sp_fid *fid)
अणु
	काष्ठा mlxsw_sp_fid_family *fid_family = fid->fid_family;
	स्थिर काष्ठा mlxsw_sp_fid_ops *ops = fid_family->ops;

	अगर (WARN_ON(!ops->nve_flood_index_clear || !fid->nve_flood_index_valid))
		वापस;

	fid->nve_flood_index_valid = false;
	ops->nve_flood_index_clear(fid);
पूर्ण

bool mlxsw_sp_fid_nve_flood_index_is_set(स्थिर काष्ठा mlxsw_sp_fid *fid)
अणु
	वापस fid->nve_flood_index_valid;
पूर्ण

पूर्णांक mlxsw_sp_fid_vni_set(काष्ठा mlxsw_sp_fid *fid, क्रमागत mlxsw_sp_nve_type type,
			 __be32 vni, पूर्णांक nve_अगरindex)
अणु
	काष्ठा mlxsw_sp_fid_family *fid_family = fid->fid_family;
	स्थिर काष्ठा mlxsw_sp_fid_ops *ops = fid_family->ops;
	काष्ठा mlxsw_sp *mlxsw_sp = fid_family->mlxsw_sp;
	पूर्णांक err;

	अगर (WARN_ON(!ops->vni_set || fid->vni_valid))
		वापस -EINVAL;

	fid->nve_type = type;
	fid->nve_अगरindex = nve_अगरindex;
	fid->vni = vni;
	err = rhashtable_lookup_insert_fast(&mlxsw_sp->fid_core->vni_ht,
					    &fid->vni_ht_node,
					    mlxsw_sp_fid_vni_ht_params);
	अगर (err)
		वापस err;

	err = ops->vni_set(fid, vni);
	अगर (err)
		जाओ err_vni_set;

	fid->vni_valid = true;

	वापस 0;

err_vni_set:
	rhashtable_हटाओ_fast(&mlxsw_sp->fid_core->vni_ht, &fid->vni_ht_node,
			       mlxsw_sp_fid_vni_ht_params);
	वापस err;
पूर्ण

व्योम mlxsw_sp_fid_vni_clear(काष्ठा mlxsw_sp_fid *fid)
अणु
	काष्ठा mlxsw_sp_fid_family *fid_family = fid->fid_family;
	स्थिर काष्ठा mlxsw_sp_fid_ops *ops = fid_family->ops;
	काष्ठा mlxsw_sp *mlxsw_sp = fid_family->mlxsw_sp;

	अगर (WARN_ON(!ops->vni_clear || !fid->vni_valid))
		वापस;

	fid->vni_valid = false;
	ops->vni_clear(fid);
	rhashtable_हटाओ_fast(&mlxsw_sp->fid_core->vni_ht, &fid->vni_ht_node,
			       mlxsw_sp_fid_vni_ht_params);
पूर्ण

bool mlxsw_sp_fid_vni_is_set(स्थिर काष्ठा mlxsw_sp_fid *fid)
अणु
	वापस fid->vni_valid;
पूर्ण

व्योम mlxsw_sp_fid_fdb_clear_offload(स्थिर काष्ठा mlxsw_sp_fid *fid,
				    स्थिर काष्ठा net_device *nve_dev)
अणु
	काष्ठा mlxsw_sp_fid_family *fid_family = fid->fid_family;
	स्थिर काष्ठा mlxsw_sp_fid_ops *ops = fid_family->ops;

	अगर (ops->fdb_clear_offload)
		ops->fdb_clear_offload(fid, nve_dev);
पूर्ण

अटल स्थिर काष्ठा mlxsw_sp_flood_table *
mlxsw_sp_fid_flood_table_lookup(स्थिर काष्ठा mlxsw_sp_fid *fid,
				क्रमागत mlxsw_sp_flood_type packet_type)
अणु
	काष्ठा mlxsw_sp_fid_family *fid_family = fid->fid_family;
	पूर्णांक i;

	क्रम (i = 0; i < fid_family->nr_flood_tables; i++) अणु
		अगर (fid_family->flood_tables[i].packet_type != packet_type)
			जारी;
		वापस &fid_family->flood_tables[i];
	पूर्ण

	वापस शून्य;
पूर्ण

पूर्णांक mlxsw_sp_fid_flood_set(काष्ठा mlxsw_sp_fid *fid,
			   क्रमागत mlxsw_sp_flood_type packet_type, u8 local_port,
			   bool member)
अणु
	काष्ठा mlxsw_sp_fid_family *fid_family = fid->fid_family;
	स्थिर काष्ठा mlxsw_sp_fid_ops *ops = fid_family->ops;
	स्थिर काष्ठा mlxsw_sp_flood_table *flood_table;
	अक्षर *sftr_pl;
	पूर्णांक err;

	अगर (WARN_ON(!fid_family->flood_tables || !ops->flood_index))
		वापस -EINVAL;

	flood_table = mlxsw_sp_fid_flood_table_lookup(fid, packet_type);
	अगर (!flood_table)
		वापस -ESRCH;

	sftr_pl = kदो_स्मृति(MLXSW_REG_SFTR_LEN, GFP_KERNEL);
	अगर (!sftr_pl)
		वापस -ENOMEM;

	mlxsw_reg_sftr_pack(sftr_pl, flood_table->table_index,
			    ops->flood_index(fid), flood_table->table_type, 1,
			    local_port, member);
	err = mlxsw_reg_ग_लिखो(fid_family->mlxsw_sp->core, MLXSW_REG(sftr),
			      sftr_pl);
	kमुक्त(sftr_pl);
	वापस err;
पूर्ण

पूर्णांक mlxsw_sp_fid_port_vid_map(काष्ठा mlxsw_sp_fid *fid,
			      काष्ठा mlxsw_sp_port *mlxsw_sp_port, u16 vid)
अणु
	अगर (WARN_ON(!fid->fid_family->ops->port_vid_map))
		वापस -EINVAL;
	वापस fid->fid_family->ops->port_vid_map(fid, mlxsw_sp_port, vid);
पूर्ण

व्योम mlxsw_sp_fid_port_vid_unmap(काष्ठा mlxsw_sp_fid *fid,
				 काष्ठा mlxsw_sp_port *mlxsw_sp_port, u16 vid)
अणु
	fid->fid_family->ops->port_vid_unmap(fid, mlxsw_sp_port, vid);
पूर्ण

u16 mlxsw_sp_fid_index(स्थिर काष्ठा mlxsw_sp_fid *fid)
अणु
	वापस fid->fid_index;
पूर्ण

क्रमागत mlxsw_sp_fid_type mlxsw_sp_fid_type(स्थिर काष्ठा mlxsw_sp_fid *fid)
अणु
	वापस fid->fid_family->type;
पूर्ण

व्योम mlxsw_sp_fid_rअगर_set(काष्ठा mlxsw_sp_fid *fid, काष्ठा mlxsw_sp_rअगर *rअगर)
अणु
	fid->rअगर = rअगर;
पूर्ण

काष्ठा mlxsw_sp_rअगर *mlxsw_sp_fid_rअगर(स्थिर काष्ठा mlxsw_sp_fid *fid)
अणु
	वापस fid->rअगर;
पूर्ण

क्रमागत mlxsw_sp_rअगर_type
mlxsw_sp_fid_type_rअगर_type(स्थिर काष्ठा mlxsw_sp *mlxsw_sp,
			   क्रमागत mlxsw_sp_fid_type type)
अणु
	काष्ठा mlxsw_sp_fid_core *fid_core = mlxsw_sp->fid_core;

	वापस fid_core->fid_family_arr[type]->rअगर_type;
पूर्ण

अटल काष्ठा mlxsw_sp_fid_8021q *
mlxsw_sp_fid_8021q_fid(स्थिर काष्ठा mlxsw_sp_fid *fid)
अणु
	वापस container_of(fid, काष्ठा mlxsw_sp_fid_8021q, common);
पूर्ण

u16 mlxsw_sp_fid_8021q_vid(स्थिर काष्ठा mlxsw_sp_fid *fid)
अणु
	वापस mlxsw_sp_fid_8021q_fid(fid)->vid;
पूर्ण

अटल व्योम mlxsw_sp_fid_8021q_setup(काष्ठा mlxsw_sp_fid *fid, स्थिर व्योम *arg)
अणु
	u16 vid = *(u16 *) arg;

	mlxsw_sp_fid_8021q_fid(fid)->vid = vid;
पूर्ण

अटल क्रमागत mlxsw_reg_sfmr_op mlxsw_sp_sfmr_op(bool valid)
अणु
	वापस valid ? MLXSW_REG_SFMR_OP_CREATE_FID :
		       MLXSW_REG_SFMR_OP_DESTROY_FID;
पूर्ण

अटल पूर्णांक mlxsw_sp_fid_op(काष्ठा mlxsw_sp *mlxsw_sp, u16 fid_index,
			   u16 fid_offset, bool valid)
अणु
	अक्षर sfmr_pl[MLXSW_REG_SFMR_LEN];

	mlxsw_reg_sfmr_pack(sfmr_pl, mlxsw_sp_sfmr_op(valid), fid_index,
			    fid_offset);
	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(sfmr), sfmr_pl);
पूर्ण

अटल पूर्णांक mlxsw_sp_fid_vni_op(काष्ठा mlxsw_sp *mlxsw_sp, u16 fid_index,
			       __be32 vni, bool vni_valid, u32 nve_flood_index,
			       bool nve_flood_index_valid)
अणु
	अक्षर sfmr_pl[MLXSW_REG_SFMR_LEN];

	mlxsw_reg_sfmr_pack(sfmr_pl, MLXSW_REG_SFMR_OP_CREATE_FID, fid_index,
			    0);
	mlxsw_reg_sfmr_vv_set(sfmr_pl, vni_valid);
	mlxsw_reg_sfmr_vni_set(sfmr_pl, be32_to_cpu(vni));
	mlxsw_reg_sfmr_vtfp_set(sfmr_pl, nve_flood_index_valid);
	mlxsw_reg_sfmr_nve_tunnel_flood_ptr_set(sfmr_pl, nve_flood_index);
	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(sfmr), sfmr_pl);
पूर्ण

अटल पूर्णांक __mlxsw_sp_fid_port_vid_map(काष्ठा mlxsw_sp *mlxsw_sp, u16 fid_index,
				       u8 local_port, u16 vid, bool valid)
अणु
	क्रमागत mlxsw_reg_svfa_mt mt = MLXSW_REG_SVFA_MT_PORT_VID_TO_FID;
	अक्षर svfa_pl[MLXSW_REG_SVFA_LEN];

	mlxsw_reg_svfa_pack(svfa_pl, local_port, mt, valid, fid_index, vid);
	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(svfa), svfa_pl);
पूर्ण

अटल काष्ठा mlxsw_sp_fid_8021d *
mlxsw_sp_fid_8021d_fid(स्थिर काष्ठा mlxsw_sp_fid *fid)
अणु
	वापस container_of(fid, काष्ठा mlxsw_sp_fid_8021d, common);
पूर्ण

अटल व्योम mlxsw_sp_fid_8021d_setup(काष्ठा mlxsw_sp_fid *fid, स्थिर व्योम *arg)
अणु
	पूर्णांक br_अगरindex = *(पूर्णांक *) arg;

	mlxsw_sp_fid_8021d_fid(fid)->br_अगरindex = br_अगरindex;
पूर्ण

अटल पूर्णांक mlxsw_sp_fid_8021d_configure(काष्ठा mlxsw_sp_fid *fid)
अणु
	काष्ठा mlxsw_sp_fid_family *fid_family = fid->fid_family;

	वापस mlxsw_sp_fid_op(fid_family->mlxsw_sp, fid->fid_index, 0, true);
पूर्ण

अटल व्योम mlxsw_sp_fid_8021d_deconfigure(काष्ठा mlxsw_sp_fid *fid)
अणु
	अगर (fid->vni_valid)
		mlxsw_sp_nve_fid_disable(fid->fid_family->mlxsw_sp, fid);
	mlxsw_sp_fid_op(fid->fid_family->mlxsw_sp, fid->fid_index, 0, false);
पूर्ण

अटल पूर्णांक mlxsw_sp_fid_8021d_index_alloc(काष्ठा mlxsw_sp_fid *fid,
					  स्थिर व्योम *arg, u16 *p_fid_index)
अणु
	काष्ठा mlxsw_sp_fid_family *fid_family = fid->fid_family;
	u16 nr_fids, fid_index;

	nr_fids = fid_family->end_index - fid_family->start_index + 1;
	fid_index = find_first_zero_bit(fid_family->fids_biपंचांगap, nr_fids);
	अगर (fid_index == nr_fids)
		वापस -ENOBUFS;
	*p_fid_index = fid_family->start_index + fid_index;

	वापस 0;
पूर्ण

अटल bool
mlxsw_sp_fid_8021d_compare(स्थिर काष्ठा mlxsw_sp_fid *fid, स्थिर व्योम *arg)
अणु
	पूर्णांक br_अगरindex = *(पूर्णांक *) arg;

	वापस mlxsw_sp_fid_8021d_fid(fid)->br_अगरindex == br_अगरindex;
पूर्ण

अटल u16 mlxsw_sp_fid_8021d_flood_index(स्थिर काष्ठा mlxsw_sp_fid *fid)
अणु
	वापस fid->fid_index - VLAN_N_VID;
पूर्ण

अटल पूर्णांक mlxsw_sp_port_vp_mode_trans(काष्ठा mlxsw_sp_port *mlxsw_sp_port)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	काष्ठा mlxsw_sp_port_vlan *mlxsw_sp_port_vlan;
	पूर्णांक err;

	list_क्रम_each_entry(mlxsw_sp_port_vlan, &mlxsw_sp_port->vlans_list,
			    list) अणु
		काष्ठा mlxsw_sp_fid *fid = mlxsw_sp_port_vlan->fid;
		u16 vid = mlxsw_sp_port_vlan->vid;

		अगर (!fid)
			जारी;

		err = __mlxsw_sp_fid_port_vid_map(mlxsw_sp, fid->fid_index,
						  mlxsw_sp_port->local_port,
						  vid, true);
		अगर (err)
			जाओ err_fid_port_vid_map;
	पूर्ण

	err = mlxsw_sp_port_vp_mode_set(mlxsw_sp_port, true);
	अगर (err)
		जाओ err_port_vp_mode_set;

	वापस 0;

err_port_vp_mode_set:
err_fid_port_vid_map:
	list_क्रम_each_entry_जारी_reverse(mlxsw_sp_port_vlan,
					     &mlxsw_sp_port->vlans_list, list) अणु
		काष्ठा mlxsw_sp_fid *fid = mlxsw_sp_port_vlan->fid;
		u16 vid = mlxsw_sp_port_vlan->vid;

		अगर (!fid)
			जारी;

		__mlxsw_sp_fid_port_vid_map(mlxsw_sp, fid->fid_index,
					    mlxsw_sp_port->local_port, vid,
					    false);
	पूर्ण
	वापस err;
पूर्ण

अटल व्योम mlxsw_sp_port_vlan_mode_trans(काष्ठा mlxsw_sp_port *mlxsw_sp_port)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	काष्ठा mlxsw_sp_port_vlan *mlxsw_sp_port_vlan;

	mlxsw_sp_port_vp_mode_set(mlxsw_sp_port, false);

	list_क्रम_each_entry_reverse(mlxsw_sp_port_vlan,
				    &mlxsw_sp_port->vlans_list, list) अणु
		काष्ठा mlxsw_sp_fid *fid = mlxsw_sp_port_vlan->fid;
		u16 vid = mlxsw_sp_port_vlan->vid;

		अगर (!fid)
			जारी;

		__mlxsw_sp_fid_port_vid_map(mlxsw_sp, fid->fid_index,
					    mlxsw_sp_port->local_port, vid,
					    false);
	पूर्ण
पूर्ण

अटल पूर्णांक mlxsw_sp_fid_8021d_port_vid_map(काष्ठा mlxsw_sp_fid *fid,
					   काष्ठा mlxsw_sp_port *mlxsw_sp_port,
					   u16 vid)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	u8 local_port = mlxsw_sp_port->local_port;
	पूर्णांक err;

	err = __mlxsw_sp_fid_port_vid_map(mlxsw_sp, fid->fid_index,
					  mlxsw_sp_port->local_port, vid, true);
	अगर (err)
		वापस err;

	अगर (mlxsw_sp->fid_core->port_fid_mappings[local_port]++ == 0) अणु
		err = mlxsw_sp_port_vp_mode_trans(mlxsw_sp_port);
		अगर (err)
			जाओ err_port_vp_mode_trans;
	पूर्ण

	वापस 0;

err_port_vp_mode_trans:
	mlxsw_sp->fid_core->port_fid_mappings[local_port]--;
	__mlxsw_sp_fid_port_vid_map(mlxsw_sp, fid->fid_index,
				    mlxsw_sp_port->local_port, vid, false);
	वापस err;
पूर्ण

अटल व्योम
mlxsw_sp_fid_8021d_port_vid_unmap(काष्ठा mlxsw_sp_fid *fid,
				  काष्ठा mlxsw_sp_port *mlxsw_sp_port, u16 vid)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	u8 local_port = mlxsw_sp_port->local_port;

	अगर (mlxsw_sp->fid_core->port_fid_mappings[local_port] == 1)
		mlxsw_sp_port_vlan_mode_trans(mlxsw_sp_port);
	mlxsw_sp->fid_core->port_fid_mappings[local_port]--;
	__mlxsw_sp_fid_port_vid_map(mlxsw_sp, fid->fid_index,
				    mlxsw_sp_port->local_port, vid, false);
पूर्ण

अटल पूर्णांक mlxsw_sp_fid_8021d_vni_set(काष्ठा mlxsw_sp_fid *fid, __be32 vni)
अणु
	काष्ठा mlxsw_sp_fid_family *fid_family = fid->fid_family;

	वापस mlxsw_sp_fid_vni_op(fid_family->mlxsw_sp, fid->fid_index, vni,
				   true, fid->nve_flood_index,
				   fid->nve_flood_index_valid);
पूर्ण

अटल व्योम mlxsw_sp_fid_8021d_vni_clear(काष्ठा mlxsw_sp_fid *fid)
अणु
	काष्ठा mlxsw_sp_fid_family *fid_family = fid->fid_family;

	mlxsw_sp_fid_vni_op(fid_family->mlxsw_sp, fid->fid_index, 0, false,
			    fid->nve_flood_index, fid->nve_flood_index_valid);
पूर्ण

अटल पूर्णांक mlxsw_sp_fid_8021d_nve_flood_index_set(काष्ठा mlxsw_sp_fid *fid,
						  u32 nve_flood_index)
अणु
	काष्ठा mlxsw_sp_fid_family *fid_family = fid->fid_family;

	वापस mlxsw_sp_fid_vni_op(fid_family->mlxsw_sp, fid->fid_index,
				   fid->vni, fid->vni_valid, nve_flood_index,
				   true);
पूर्ण

अटल व्योम mlxsw_sp_fid_8021d_nve_flood_index_clear(काष्ठा mlxsw_sp_fid *fid)
अणु
	काष्ठा mlxsw_sp_fid_family *fid_family = fid->fid_family;

	mlxsw_sp_fid_vni_op(fid_family->mlxsw_sp, fid->fid_index, fid->vni,
			    fid->vni_valid, 0, false);
पूर्ण

अटल व्योम
mlxsw_sp_fid_8021d_fdb_clear_offload(स्थिर काष्ठा mlxsw_sp_fid *fid,
				     स्थिर काष्ठा net_device *nve_dev)
अणु
	br_fdb_clear_offload(nve_dev, 0);
पूर्ण

अटल स्थिर काष्ठा mlxsw_sp_fid_ops mlxsw_sp_fid_8021d_ops = अणु
	.setup			= mlxsw_sp_fid_8021d_setup,
	.configure		= mlxsw_sp_fid_8021d_configure,
	.deconfigure		= mlxsw_sp_fid_8021d_deconfigure,
	.index_alloc		= mlxsw_sp_fid_8021d_index_alloc,
	.compare		= mlxsw_sp_fid_8021d_compare,
	.flood_index		= mlxsw_sp_fid_8021d_flood_index,
	.port_vid_map		= mlxsw_sp_fid_8021d_port_vid_map,
	.port_vid_unmap		= mlxsw_sp_fid_8021d_port_vid_unmap,
	.vni_set		= mlxsw_sp_fid_8021d_vni_set,
	.vni_clear		= mlxsw_sp_fid_8021d_vni_clear,
	.nve_flood_index_set	= mlxsw_sp_fid_8021d_nve_flood_index_set,
	.nve_flood_index_clear	= mlxsw_sp_fid_8021d_nve_flood_index_clear,
	.fdb_clear_offload	= mlxsw_sp_fid_8021d_fdb_clear_offload,
पूर्ण;

अटल स्थिर काष्ठा mlxsw_sp_flood_table mlxsw_sp_fid_8021d_flood_tables[] = अणु
	अणु
		.packet_type	= MLXSW_SP_FLOOD_TYPE_UC,
		.bridge_type	= MLXSW_REG_SFGC_BRIDGE_TYPE_VFID,
		.table_type	= MLXSW_REG_SFGC_TABLE_TYPE_FID,
		.table_index	= 0,
	पूर्ण,
	अणु
		.packet_type	= MLXSW_SP_FLOOD_TYPE_MC,
		.bridge_type	= MLXSW_REG_SFGC_BRIDGE_TYPE_VFID,
		.table_type	= MLXSW_REG_SFGC_TABLE_TYPE_FID,
		.table_index	= 1,
	पूर्ण,
	अणु
		.packet_type	= MLXSW_SP_FLOOD_TYPE_BC,
		.bridge_type	= MLXSW_REG_SFGC_BRIDGE_TYPE_VFID,
		.table_type	= MLXSW_REG_SFGC_TABLE_TYPE_FID,
		.table_index	= 2,
	पूर्ण,
पूर्ण;

/* Range and flood configuration must match mlxsw_config_profile */
अटल स्थिर काष्ठा mlxsw_sp_fid_family mlxsw_sp_fid_8021d_family = अणु
	.type			= MLXSW_SP_FID_TYPE_8021D,
	.fid_size		= माप(काष्ठा mlxsw_sp_fid_8021d),
	.start_index		= VLAN_N_VID,
	.end_index		= VLAN_N_VID + MLXSW_SP_FID_8021D_MAX - 1,
	.flood_tables		= mlxsw_sp_fid_8021d_flood_tables,
	.nr_flood_tables	= ARRAY_SIZE(mlxsw_sp_fid_8021d_flood_tables),
	.rअगर_type		= MLXSW_SP_RIF_TYPE_FID,
	.ops			= &mlxsw_sp_fid_8021d_ops,
	.lag_vid_valid		= 1,
पूर्ण;

अटल bool
mlxsw_sp_fid_8021q_compare(स्थिर काष्ठा mlxsw_sp_fid *fid, स्थिर व्योम *arg)
अणु
	u16 vid = *(u16 *) arg;

	वापस mlxsw_sp_fid_8021q_fid(fid)->vid == vid;
पूर्ण

अटल व्योम
mlxsw_sp_fid_8021q_fdb_clear_offload(स्थिर काष्ठा mlxsw_sp_fid *fid,
				     स्थिर काष्ठा net_device *nve_dev)
अणु
	br_fdb_clear_offload(nve_dev, mlxsw_sp_fid_8021q_vid(fid));
पूर्ण

अटल स्थिर काष्ठा mlxsw_sp_fid_ops mlxsw_sp_fid_8021q_emu_ops = अणु
	.setup			= mlxsw_sp_fid_8021q_setup,
	.configure		= mlxsw_sp_fid_8021d_configure,
	.deconfigure		= mlxsw_sp_fid_8021d_deconfigure,
	.index_alloc		= mlxsw_sp_fid_8021d_index_alloc,
	.compare		= mlxsw_sp_fid_8021q_compare,
	.flood_index		= mlxsw_sp_fid_8021d_flood_index,
	.port_vid_map		= mlxsw_sp_fid_8021d_port_vid_map,
	.port_vid_unmap		= mlxsw_sp_fid_8021d_port_vid_unmap,
	.vni_set		= mlxsw_sp_fid_8021d_vni_set,
	.vni_clear		= mlxsw_sp_fid_8021d_vni_clear,
	.nve_flood_index_set	= mlxsw_sp_fid_8021d_nve_flood_index_set,
	.nve_flood_index_clear	= mlxsw_sp_fid_8021d_nve_flood_index_clear,
	.fdb_clear_offload	= mlxsw_sp_fid_8021q_fdb_clear_offload,
पूर्ण;

/* There are 4K-2 emulated 802.1Q FIDs, starting right after the 802.1D FIDs */
#घोषणा MLXSW_SP_FID_8021Q_EMU_START	(VLAN_N_VID + MLXSW_SP_FID_8021D_MAX)
#घोषणा MLXSW_SP_FID_8021Q_EMU_END	(MLXSW_SP_FID_8021Q_EMU_START + \
					 VLAN_VID_MASK - 2)

/* Range and flood configuration must match mlxsw_config_profile */
अटल स्थिर काष्ठा mlxsw_sp_fid_family mlxsw_sp_fid_8021q_emu_family = अणु
	.type			= MLXSW_SP_FID_TYPE_8021Q,
	.fid_size		= माप(काष्ठा mlxsw_sp_fid_8021q),
	.start_index		= MLXSW_SP_FID_8021Q_EMU_START,
	.end_index		= MLXSW_SP_FID_8021Q_EMU_END,
	.flood_tables		= mlxsw_sp_fid_8021d_flood_tables,
	.nr_flood_tables	= ARRAY_SIZE(mlxsw_sp_fid_8021d_flood_tables),
	.rअगर_type		= MLXSW_SP_RIF_TYPE_VLAN,
	.ops			= &mlxsw_sp_fid_8021q_emu_ops,
	.lag_vid_valid		= 1,
पूर्ण;

अटल पूर्णांक mlxsw_sp_fid_rfid_configure(काष्ठा mlxsw_sp_fid *fid)
अणु
	/* rFIDs are allocated by the device during init */
	वापस 0;
पूर्ण

अटल व्योम mlxsw_sp_fid_rfid_deconfigure(काष्ठा mlxsw_sp_fid *fid)
अणु
पूर्ण

अटल पूर्णांक mlxsw_sp_fid_rfid_index_alloc(काष्ठा mlxsw_sp_fid *fid,
					 स्थिर व्योम *arg, u16 *p_fid_index)
अणु
	u16 rअगर_index = *(u16 *) arg;

	*p_fid_index = fid->fid_family->start_index + rअगर_index;

	वापस 0;
पूर्ण

अटल bool mlxsw_sp_fid_rfid_compare(स्थिर काष्ठा mlxsw_sp_fid *fid,
				      स्थिर व्योम *arg)
अणु
	u16 rअगर_index = *(u16 *) arg;

	वापस fid->fid_index == rअगर_index + fid->fid_family->start_index;
पूर्ण

अटल पूर्णांक mlxsw_sp_fid_rfid_port_vid_map(काष्ठा mlxsw_sp_fid *fid,
					  काष्ठा mlxsw_sp_port *mlxsw_sp_port,
					  u16 vid)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	u8 local_port = mlxsw_sp_port->local_port;
	पूर्णांक err;

	/* We only need to transition the port to भव mode since
	 * अणुPort, VIDपूर्ण => FID is करोne by the firmware upon RIF creation.
	 */
	अगर (mlxsw_sp->fid_core->port_fid_mappings[local_port]++ == 0) अणु
		err = mlxsw_sp_port_vp_mode_trans(mlxsw_sp_port);
		अगर (err)
			जाओ err_port_vp_mode_trans;
	पूर्ण

	वापस 0;

err_port_vp_mode_trans:
	mlxsw_sp->fid_core->port_fid_mappings[local_port]--;
	वापस err;
पूर्ण

अटल व्योम
mlxsw_sp_fid_rfid_port_vid_unmap(काष्ठा mlxsw_sp_fid *fid,
				 काष्ठा mlxsw_sp_port *mlxsw_sp_port, u16 vid)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	u8 local_port = mlxsw_sp_port->local_port;

	अगर (mlxsw_sp->fid_core->port_fid_mappings[local_port] == 1)
		mlxsw_sp_port_vlan_mode_trans(mlxsw_sp_port);
	mlxsw_sp->fid_core->port_fid_mappings[local_port]--;
पूर्ण

अटल स्थिर काष्ठा mlxsw_sp_fid_ops mlxsw_sp_fid_rfid_ops = अणु
	.configure		= mlxsw_sp_fid_rfid_configure,
	.deconfigure		= mlxsw_sp_fid_rfid_deconfigure,
	.index_alloc		= mlxsw_sp_fid_rfid_index_alloc,
	.compare		= mlxsw_sp_fid_rfid_compare,
	.port_vid_map		= mlxsw_sp_fid_rfid_port_vid_map,
	.port_vid_unmap		= mlxsw_sp_fid_rfid_port_vid_unmap,
पूर्ण;

#घोषणा MLXSW_SP_RFID_BASE	(15 * 1024)
#घोषणा MLXSW_SP_RFID_MAX	1024

अटल स्थिर काष्ठा mlxsw_sp_fid_family mlxsw_sp_fid_rfid_family = अणु
	.type			= MLXSW_SP_FID_TYPE_RFID,
	.fid_size		= माप(काष्ठा mlxsw_sp_fid),
	.start_index		= MLXSW_SP_RFID_BASE,
	.end_index		= MLXSW_SP_RFID_BASE + MLXSW_SP_RFID_MAX - 1,
	.rअगर_type		= MLXSW_SP_RIF_TYPE_SUBPORT,
	.ops			= &mlxsw_sp_fid_rfid_ops,
पूर्ण;

अटल पूर्णांक mlxsw_sp_fid_dummy_configure(काष्ठा mlxsw_sp_fid *fid)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = fid->fid_family->mlxsw_sp;

	वापस mlxsw_sp_fid_op(mlxsw_sp, fid->fid_index, 0, true);
पूर्ण

अटल व्योम mlxsw_sp_fid_dummy_deconfigure(काष्ठा mlxsw_sp_fid *fid)
अणु
	mlxsw_sp_fid_op(fid->fid_family->mlxsw_sp, fid->fid_index, 0, false);
पूर्ण

अटल पूर्णांक mlxsw_sp_fid_dummy_index_alloc(काष्ठा mlxsw_sp_fid *fid,
					  स्थिर व्योम *arg, u16 *p_fid_index)
अणु
	*p_fid_index = fid->fid_family->start_index;

	वापस 0;
पूर्ण

अटल bool mlxsw_sp_fid_dummy_compare(स्थिर काष्ठा mlxsw_sp_fid *fid,
				       स्थिर व्योम *arg)
अणु
	वापस true;
पूर्ण

अटल स्थिर काष्ठा mlxsw_sp_fid_ops mlxsw_sp_fid_dummy_ops = अणु
	.configure		= mlxsw_sp_fid_dummy_configure,
	.deconfigure		= mlxsw_sp_fid_dummy_deconfigure,
	.index_alloc		= mlxsw_sp_fid_dummy_index_alloc,
	.compare		= mlxsw_sp_fid_dummy_compare,
पूर्ण;

अटल स्थिर काष्ठा mlxsw_sp_fid_family mlxsw_sp_fid_dummy_family = अणु
	.type			= MLXSW_SP_FID_TYPE_DUMMY,
	.fid_size		= माप(काष्ठा mlxsw_sp_fid),
	.start_index		= VLAN_N_VID - 1,
	.end_index		= VLAN_N_VID - 1,
	.ops			= &mlxsw_sp_fid_dummy_ops,
पूर्ण;

अटल स्थिर काष्ठा mlxsw_sp_fid_family *mlxsw_sp_fid_family_arr[] = अणु
	[MLXSW_SP_FID_TYPE_8021Q]	= &mlxsw_sp_fid_8021q_emu_family,
	[MLXSW_SP_FID_TYPE_8021D]	= &mlxsw_sp_fid_8021d_family,
	[MLXSW_SP_FID_TYPE_RFID]	= &mlxsw_sp_fid_rfid_family,
	[MLXSW_SP_FID_TYPE_DUMMY]	= &mlxsw_sp_fid_dummy_family,
पूर्ण;

अटल काष्ठा mlxsw_sp_fid *mlxsw_sp_fid_lookup(काष्ठा mlxsw_sp *mlxsw_sp,
						क्रमागत mlxsw_sp_fid_type type,
						स्थिर व्योम *arg)
अणु
	काष्ठा mlxsw_sp_fid_family *fid_family;
	काष्ठा mlxsw_sp_fid *fid;

	fid_family = mlxsw_sp->fid_core->fid_family_arr[type];
	list_क्रम_each_entry(fid, &fid_family->fids_list, list) अणु
		अगर (!fid->fid_family->ops->compare(fid, arg))
			जारी;
		refcount_inc(&fid->ref_count);
		वापस fid;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा mlxsw_sp_fid *mlxsw_sp_fid_get(काष्ठा mlxsw_sp *mlxsw_sp,
					     क्रमागत mlxsw_sp_fid_type type,
					     स्थिर व्योम *arg)
अणु
	काष्ठा mlxsw_sp_fid_family *fid_family;
	काष्ठा mlxsw_sp_fid *fid;
	u16 fid_index;
	पूर्णांक err;

	fid = mlxsw_sp_fid_lookup(mlxsw_sp, type, arg);
	अगर (fid)
		वापस fid;

	fid_family = mlxsw_sp->fid_core->fid_family_arr[type];
	fid = kzalloc(fid_family->fid_size, GFP_KERNEL);
	अगर (!fid)
		वापस ERR_PTR(-ENOMEM);
	fid->fid_family = fid_family;

	err = fid->fid_family->ops->index_alloc(fid, arg, &fid_index);
	अगर (err)
		जाओ err_index_alloc;
	fid->fid_index = fid_index;
	__set_bit(fid_index - fid_family->start_index, fid_family->fids_biपंचांगap);

	अगर (fid->fid_family->ops->setup)
		fid->fid_family->ops->setup(fid, arg);

	err = fid->fid_family->ops->configure(fid);
	अगर (err)
		जाओ err_configure;

	err = rhashtable_insert_fast(&mlxsw_sp->fid_core->fid_ht, &fid->ht_node,
				     mlxsw_sp_fid_ht_params);
	अगर (err)
		जाओ err_rhashtable_insert;

	list_add(&fid->list, &fid_family->fids_list);
	refcount_set(&fid->ref_count, 1);
	वापस fid;

err_rhashtable_insert:
	fid->fid_family->ops->deconfigure(fid);
err_configure:
	__clear_bit(fid_index - fid_family->start_index,
		    fid_family->fids_biपंचांगap);
err_index_alloc:
	kमुक्त(fid);
	वापस ERR_PTR(err);
पूर्ण

व्योम mlxsw_sp_fid_put(काष्ठा mlxsw_sp_fid *fid)
अणु
	काष्ठा mlxsw_sp_fid_family *fid_family = fid->fid_family;
	काष्ठा mlxsw_sp *mlxsw_sp = fid_family->mlxsw_sp;

	अगर (!refcount_dec_and_test(&fid->ref_count))
		वापस;

	list_del(&fid->list);
	rhashtable_हटाओ_fast(&mlxsw_sp->fid_core->fid_ht,
			       &fid->ht_node, mlxsw_sp_fid_ht_params);
	fid->fid_family->ops->deconfigure(fid);
	__clear_bit(fid->fid_index - fid_family->start_index,
		    fid_family->fids_biपंचांगap);
	kमुक्त(fid);
पूर्ण

काष्ठा mlxsw_sp_fid *mlxsw_sp_fid_8021q_get(काष्ठा mlxsw_sp *mlxsw_sp, u16 vid)
अणु
	वापस mlxsw_sp_fid_get(mlxsw_sp, MLXSW_SP_FID_TYPE_8021Q, &vid);
पूर्ण

काष्ठा mlxsw_sp_fid *mlxsw_sp_fid_8021d_get(काष्ठा mlxsw_sp *mlxsw_sp,
					    पूर्णांक br_अगरindex)
अणु
	वापस mlxsw_sp_fid_get(mlxsw_sp, MLXSW_SP_FID_TYPE_8021D, &br_अगरindex);
पूर्ण

काष्ठा mlxsw_sp_fid *mlxsw_sp_fid_8021q_lookup(काष्ठा mlxsw_sp *mlxsw_sp,
					       u16 vid)
अणु
	वापस mlxsw_sp_fid_lookup(mlxsw_sp, MLXSW_SP_FID_TYPE_8021Q, &vid);
पूर्ण

काष्ठा mlxsw_sp_fid *mlxsw_sp_fid_8021d_lookup(काष्ठा mlxsw_sp *mlxsw_sp,
					       पूर्णांक br_अगरindex)
अणु
	वापस mlxsw_sp_fid_lookup(mlxsw_sp, MLXSW_SP_FID_TYPE_8021D,
				   &br_अगरindex);
पूर्ण

काष्ठा mlxsw_sp_fid *mlxsw_sp_fid_rfid_get(काष्ठा mlxsw_sp *mlxsw_sp,
					   u16 rअगर_index)
अणु
	वापस mlxsw_sp_fid_get(mlxsw_sp, MLXSW_SP_FID_TYPE_RFID, &rअगर_index);
पूर्ण

काष्ठा mlxsw_sp_fid *mlxsw_sp_fid_dummy_get(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	वापस mlxsw_sp_fid_get(mlxsw_sp, MLXSW_SP_FID_TYPE_DUMMY, शून्य);
पूर्ण

अटल पूर्णांक
mlxsw_sp_fid_flood_table_init(काष्ठा mlxsw_sp_fid_family *fid_family,
			      स्थिर काष्ठा mlxsw_sp_flood_table *flood_table)
अणु
	क्रमागत mlxsw_sp_flood_type packet_type = flood_table->packet_type;
	स्थिर पूर्णांक *sfgc_packet_types;
	पूर्णांक i;

	sfgc_packet_types = mlxsw_sp_packet_type_sfgc_types[packet_type];
	क्रम (i = 0; i < MLXSW_REG_SFGC_TYPE_MAX; i++) अणु
		काष्ठा mlxsw_sp *mlxsw_sp = fid_family->mlxsw_sp;
		अक्षर sfgc_pl[MLXSW_REG_SFGC_LEN];
		पूर्णांक err;

		अगर (!sfgc_packet_types[i])
			जारी;
		mlxsw_reg_sfgc_pack(sfgc_pl, i, flood_table->bridge_type,
				    flood_table->table_type,
				    flood_table->table_index);
		err = mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(sfgc), sfgc_pl);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
mlxsw_sp_fid_flood_tables_init(काष्ठा mlxsw_sp_fid_family *fid_family)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < fid_family->nr_flood_tables; i++) अणु
		स्थिर काष्ठा mlxsw_sp_flood_table *flood_table;
		पूर्णांक err;

		flood_table = &fid_family->flood_tables[i];
		err = mlxsw_sp_fid_flood_table_init(fid_family, flood_table);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_sp_fid_family_रेजिस्टर(काष्ठा mlxsw_sp *mlxsw_sp,
					स्थिर काष्ठा mlxsw_sp_fid_family *पंचांगpl)
अणु
	u16 nr_fids = पंचांगpl->end_index - पंचांगpl->start_index + 1;
	काष्ठा mlxsw_sp_fid_family *fid_family;
	पूर्णांक err;

	fid_family = kmemdup(पंचांगpl, माप(*fid_family), GFP_KERNEL);
	अगर (!fid_family)
		वापस -ENOMEM;

	fid_family->mlxsw_sp = mlxsw_sp;
	INIT_LIST_HEAD(&fid_family->fids_list);
	fid_family->fids_biपंचांगap = biपंचांगap_zalloc(nr_fids, GFP_KERNEL);
	अगर (!fid_family->fids_biपंचांगap) अणु
		err = -ENOMEM;
		जाओ err_alloc_fids_biपंचांगap;
	पूर्ण

	अगर (fid_family->flood_tables) अणु
		err = mlxsw_sp_fid_flood_tables_init(fid_family);
		अगर (err)
			जाओ err_fid_flood_tables_init;
	पूर्ण

	mlxsw_sp->fid_core->fid_family_arr[पंचांगpl->type] = fid_family;

	वापस 0;

err_fid_flood_tables_init:
	biपंचांगap_मुक्त(fid_family->fids_biपंचांगap);
err_alloc_fids_biपंचांगap:
	kमुक्त(fid_family);
	वापस err;
पूर्ण

अटल व्योम
mlxsw_sp_fid_family_unरेजिस्टर(काष्ठा mlxsw_sp *mlxsw_sp,
			       काष्ठा mlxsw_sp_fid_family *fid_family)
अणु
	mlxsw_sp->fid_core->fid_family_arr[fid_family->type] = शून्य;
	biपंचांगap_मुक्त(fid_family->fids_biपंचांगap);
	WARN_ON_ONCE(!list_empty(&fid_family->fids_list));
	kमुक्त(fid_family);
पूर्ण

पूर्णांक mlxsw_sp_port_fids_init(काष्ठा mlxsw_sp_port *mlxsw_sp_port)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;

	/* Track number of FIDs configured on the port with mapping type
	 * PORT_VID_TO_FID, so that we know when to transition the port
	 * back to non-भव (VLAN) mode.
	 */
	mlxsw_sp->fid_core->port_fid_mappings[mlxsw_sp_port->local_port] = 0;

	वापस mlxsw_sp_port_vp_mode_set(mlxsw_sp_port, false);
पूर्ण

व्योम mlxsw_sp_port_fids_fini(काष्ठा mlxsw_sp_port *mlxsw_sp_port)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;

	mlxsw_sp->fid_core->port_fid_mappings[mlxsw_sp_port->local_port] = 0;
पूर्ण

पूर्णांक mlxsw_sp_fids_init(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	अचिन्हित पूर्णांक max_ports = mlxsw_core_max_ports(mlxsw_sp->core);
	काष्ठा mlxsw_sp_fid_core *fid_core;
	पूर्णांक err, i;

	fid_core = kzalloc(माप(*mlxsw_sp->fid_core), GFP_KERNEL);
	अगर (!fid_core)
		वापस -ENOMEM;
	mlxsw_sp->fid_core = fid_core;

	err = rhashtable_init(&fid_core->fid_ht, &mlxsw_sp_fid_ht_params);
	अगर (err)
		जाओ err_rhashtable_fid_init;

	err = rhashtable_init(&fid_core->vni_ht, &mlxsw_sp_fid_vni_ht_params);
	अगर (err)
		जाओ err_rhashtable_vni_init;

	fid_core->port_fid_mappings = kसुस्मृति(max_ports, माप(अचिन्हित पूर्णांक),
					      GFP_KERNEL);
	अगर (!fid_core->port_fid_mappings) अणु
		err = -ENOMEM;
		जाओ err_alloc_port_fid_mappings;
	पूर्ण

	क्रम (i = 0; i < MLXSW_SP_FID_TYPE_MAX; i++) अणु
		err = mlxsw_sp_fid_family_रेजिस्टर(mlxsw_sp,
						   mlxsw_sp_fid_family_arr[i]);

		अगर (err)
			जाओ err_fid_ops_रेजिस्टर;
	पूर्ण

	वापस 0;

err_fid_ops_रेजिस्टर:
	क्रम (i--; i >= 0; i--) अणु
		काष्ठा mlxsw_sp_fid_family *fid_family;

		fid_family = fid_core->fid_family_arr[i];
		mlxsw_sp_fid_family_unरेजिस्टर(mlxsw_sp, fid_family);
	पूर्ण
	kमुक्त(fid_core->port_fid_mappings);
err_alloc_port_fid_mappings:
	rhashtable_destroy(&fid_core->vni_ht);
err_rhashtable_vni_init:
	rhashtable_destroy(&fid_core->fid_ht);
err_rhashtable_fid_init:
	kमुक्त(fid_core);
	वापस err;
पूर्ण

व्योम mlxsw_sp_fids_fini(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	काष्ठा mlxsw_sp_fid_core *fid_core = mlxsw_sp->fid_core;
	पूर्णांक i;

	क्रम (i = 0; i < MLXSW_SP_FID_TYPE_MAX; i++)
		mlxsw_sp_fid_family_unरेजिस्टर(mlxsw_sp,
					       fid_core->fid_family_arr[i]);
	kमुक्त(fid_core->port_fid_mappings);
	rhashtable_destroy(&fid_core->vni_ht);
	rhashtable_destroy(&fid_core->fid_ht);
	kमुक्त(fid_core);
पूर्ण
