<शैली गुरु>
/*
 * Copyright (c) 2016, Mellanox Technologies. All rights reserved.
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
#समावेश <linux/idr.h>
#समावेश <linux/mlx5/driver.h>
#समावेश <linux/mlx5/mlx5_अगरc.h>
#समावेश <linux/mlx5/vport.h>
#समावेश <linux/mlx5/fs.h>
#समावेश "mlx5_core.h"
#समावेश "eswitch.h"
#समावेश "esw/indir_table.h"
#समावेश "esw/acl/ofld.h"
#समावेश "rdma.h"
#समावेश "en.h"
#समावेश "fs_core.h"
#समावेश "lib/devcom.h"
#समावेश "lib/eq.h"
#समावेश "lib/fs_chains.h"
#समावेश "en_tc.h"
#समावेश "en/mapping.h"

#घोषणा mlx5_esw_क्रम_each_rep(esw, i, rep) \
	xa_क्रम_each(&((esw)->offloads.vport_reps), i, rep)

#घोषणा mlx5_esw_क्रम_each_sf_rep(esw, i, rep) \
	xa_क्रम_each_marked(&((esw)->offloads.vport_reps), i, rep, MLX5_ESW_VPT_SF)

#घोषणा mlx5_esw_क्रम_each_vf_rep(esw, index, rep)	\
	mlx5_esw_क्रम_each_entry_marked(&((esw)->offloads.vport_reps), index, \
				       rep, (esw)->esw_funcs.num_vfs, MLX5_ESW_VPT_VF)

/* There are two match-all miss flows, one क्रम unicast dst mac and
 * one क्रम multicast.
 */
#घोषणा MLX5_ESW_MISS_FLOWS (2)
#घोषणा UPLINK_REP_INDEX 0

#घोषणा MLX5_ESW_VPORT_TBL_SIZE 128
#घोषणा MLX5_ESW_VPORT_TBL_NUM_GROUPS  4

अटल स्थिर काष्ठा esw_vport_tbl_namespace mlx5_esw_vport_tbl_mirror_ns = अणु
	.max_fte = MLX5_ESW_VPORT_TBL_SIZE,
	.max_num_groups = MLX5_ESW_VPORT_TBL_NUM_GROUPS,
	.flags = 0,
पूर्ण;

अटल काष्ठा mlx5_eचयन_rep *mlx5_eचयन_get_rep(काष्ठा mlx5_eचयन *esw,
						     u16 vport_num)
अणु
	वापस xa_load(&esw->offloads.vport_reps, vport_num);
पूर्ण

अटल व्योम
mlx5_eचयन_set_rule_flow_source(काष्ठा mlx5_eचयन *esw,
				  काष्ठा mlx5_flow_spec *spec,
				  काष्ठा mlx5_esw_flow_attr *attr)
अणु
	अगर (MLX5_CAP_ESW_FLOWTABLE(esw->dev, flow_source) &&
	    attr && attr->in_rep)
		spec->flow_context.flow_source =
			attr->in_rep->vport == MLX5_VPORT_UPLINK ?
				MLX5_FLOW_CONTEXT_FLOW_SOURCE_UPLINK :
				MLX5_FLOW_CONTEXT_FLOW_SOURCE_LOCAL_VPORT;
पूर्ण

/* Actually only the upper 16 bits of reg c0 need to be cleared, but the lower 16 bits
 * are not needed as well in the following process. So clear them all क्रम simplicity.
 */
व्योम
mlx5_eचयन_clear_rule_source_port(काष्ठा mlx5_eचयन *esw, काष्ठा mlx5_flow_spec *spec)
अणु
	अगर (mlx5_eचयन_vport_match_metadata_enabled(esw)) अणु
		व्योम *misc2;

		misc2 = MLX5_ADDR_OF(fte_match_param, spec->match_value, misc_parameters_2);
		MLX5_SET(fte_match_set_misc2, misc2, metadata_reg_c_0, 0);

		misc2 = MLX5_ADDR_OF(fte_match_param, spec->match_criteria, misc_parameters_2);
		MLX5_SET(fte_match_set_misc2, misc2, metadata_reg_c_0, 0);

		अगर (!स_प्रथम_inv(misc2, 0, MLX5_ST_SZ_BYTES(fte_match_set_misc2)))
			spec->match_criteria_enable &= ~MLX5_MATCH_MISC_PARAMETERS_2;
	पूर्ण
पूर्ण

अटल व्योम
mlx5_eचयन_set_rule_source_port(काष्ठा mlx5_eचयन *esw,
				  काष्ठा mlx5_flow_spec *spec,
				  काष्ठा mlx5_flow_attr *attr,
				  काष्ठा mlx5_eचयन *src_esw,
				  u16 vport)
अणु
	व्योम *misc2;
	व्योम *misc;

	/* Use metadata matching because vport is not represented by single
	 * VHCA in dual-port RoCE mode, and matching on source vport may fail.
	 */
	अगर (mlx5_eचयन_vport_match_metadata_enabled(esw)) अणु
		अगर (mlx5_esw_indir_table_decap_vport(attr))
			vport = mlx5_esw_indir_table_decap_vport(attr);
		misc2 = MLX5_ADDR_OF(fte_match_param, spec->match_value, misc_parameters_2);
		MLX5_SET(fte_match_set_misc2, misc2, metadata_reg_c_0,
			 mlx5_eचयन_get_vport_metadata_क्रम_match(src_esw,
								   vport));

		misc2 = MLX5_ADDR_OF(fte_match_param, spec->match_criteria, misc_parameters_2);
		MLX5_SET(fte_match_set_misc2, misc2, metadata_reg_c_0,
			 mlx5_eचयन_get_vport_metadata_mask());

		spec->match_criteria_enable |= MLX5_MATCH_MISC_PARAMETERS_2;
	पूर्ण अन्यथा अणु
		misc = MLX5_ADDR_OF(fte_match_param, spec->match_value, misc_parameters);
		MLX5_SET(fte_match_set_misc, misc, source_port, vport);

		अगर (MLX5_CAP_ESW(esw->dev, merged_eचयन))
			MLX5_SET(fte_match_set_misc, misc,
				 source_eचयन_owner_vhca_id,
				 MLX5_CAP_GEN(src_esw->dev, vhca_id));

		misc = MLX5_ADDR_OF(fte_match_param, spec->match_criteria, misc_parameters);
		MLX5_SET_TO_ONES(fte_match_set_misc, misc, source_port);
		अगर (MLX5_CAP_ESW(esw->dev, merged_eचयन))
			MLX5_SET_TO_ONES(fte_match_set_misc, misc,
					 source_eचयन_owner_vhca_id);

		spec->match_criteria_enable |= MLX5_MATCH_MISC_PARAMETERS;
	पूर्ण
पूर्ण

अटल पूर्णांक
esw_setup_decap_indir(काष्ठा mlx5_eचयन *esw,
		      काष्ठा mlx5_flow_attr *attr,
		      काष्ठा mlx5_flow_spec *spec)
अणु
	काष्ठा mlx5_flow_table *ft;

	अगर (!(attr->flags & MLX5_ESW_ATTR_FLAG_SRC_REWRITE))
		वापस -EOPNOTSUPP;

	ft = mlx5_esw_indir_table_get(esw, attr, spec,
				      mlx5_esw_indir_table_decap_vport(attr), true);
	वापस PTR_ERR_OR_ZERO(ft);
पूर्ण

अटल व्योम
esw_cleanup_decap_indir(काष्ठा mlx5_eचयन *esw,
			काष्ठा mlx5_flow_attr *attr)
अणु
	अगर (mlx5_esw_indir_table_decap_vport(attr))
		mlx5_esw_indir_table_put(esw, attr,
					 mlx5_esw_indir_table_decap_vport(attr),
					 true);
पूर्ण

अटल पूर्णांक
esw_setup_sampler_dest(काष्ठा mlx5_flow_destination *dest,
		       काष्ठा mlx5_flow_act *flow_act,
		       काष्ठा mlx5_esw_flow_attr *esw_attr,
		       पूर्णांक i)
अणु
	flow_act->flags |= FLOW_ACT_IGNORE_FLOW_LEVEL;
	dest[i].type = MLX5_FLOW_DESTINATION_TYPE_FLOW_SAMPLER;
	dest[i].sampler_id = esw_attr->sample->sampler_id;

	वापस 0;
पूर्ण

अटल पूर्णांक
esw_setup_ft_dest(काष्ठा mlx5_flow_destination *dest,
		  काष्ठा mlx5_flow_act *flow_act,
		  काष्ठा mlx5_eचयन *esw,
		  काष्ठा mlx5_flow_attr *attr,
		  काष्ठा mlx5_flow_spec *spec,
		  पूर्णांक i)
अणु
	flow_act->flags |= FLOW_ACT_IGNORE_FLOW_LEVEL;
	dest[i].type = MLX5_FLOW_DESTINATION_TYPE_FLOW_TABLE;
	dest[i].ft = attr->dest_ft;

	अगर (mlx5_esw_indir_table_decap_vport(attr))
		वापस esw_setup_decap_indir(esw, attr, spec);
	वापस 0;
पूर्ण

अटल व्योम
esw_setup_slow_path_dest(काष्ठा mlx5_flow_destination *dest,
			 काष्ठा mlx5_flow_act *flow_act,
			 काष्ठा mlx5_fs_chains *chains,
			 पूर्णांक i)
अणु
	अगर (mlx5_chains_ignore_flow_level_supported(chains))
		flow_act->flags |= FLOW_ACT_IGNORE_FLOW_LEVEL;
	dest[i].type = MLX5_FLOW_DESTINATION_TYPE_FLOW_TABLE;
	dest[i].ft = mlx5_chains_get_tc_end_ft(chains);
पूर्ण

अटल पूर्णांक
esw_setup_chain_dest(काष्ठा mlx5_flow_destination *dest,
		     काष्ठा mlx5_flow_act *flow_act,
		     काष्ठा mlx5_fs_chains *chains,
		     u32 chain, u32 prio, u32 level,
		     पूर्णांक i)
अणु
	काष्ठा mlx5_flow_table *ft;

	flow_act->flags |= FLOW_ACT_IGNORE_FLOW_LEVEL;
	ft = mlx5_chains_get_table(chains, chain, prio, level);
	अगर (IS_ERR(ft))
		वापस PTR_ERR(ft);

	dest[i].type = MLX5_FLOW_DESTINATION_TYPE_FLOW_TABLE;
	dest[i].ft = ft;
	वापस  0;
पूर्ण

अटल व्योम esw_put_dest_tables_loop(काष्ठा mlx5_eचयन *esw, काष्ठा mlx5_flow_attr *attr,
				     पूर्णांक from, पूर्णांक to)
अणु
	काष्ठा mlx5_esw_flow_attr *esw_attr = attr->esw_attr;
	काष्ठा mlx5_fs_chains *chains = esw_chains(esw);
	पूर्णांक i;

	क्रम (i = from; i < to; i++)
		अगर (esw_attr->dests[i].flags & MLX5_ESW_DEST_CHAIN_WITH_SRC_PORT_CHANGE)
			mlx5_chains_put_table(chains, 0, 1, 0);
		अन्यथा अगर (mlx5_esw_indir_table_needed(esw, attr, esw_attr->dests[i].rep->vport,
						     esw_attr->dests[i].mdev))
			mlx5_esw_indir_table_put(esw, attr, esw_attr->dests[i].rep->vport,
						 false);
पूर्ण

अटल bool
esw_is_chain_src_port_reग_लिखो(काष्ठा mlx5_eचयन *esw, काष्ठा mlx5_esw_flow_attr *esw_attr)
अणु
	पूर्णांक i;

	क्रम (i = esw_attr->split_count; i < esw_attr->out_count; i++)
		अगर (esw_attr->dests[i].flags & MLX5_ESW_DEST_CHAIN_WITH_SRC_PORT_CHANGE)
			वापस true;
	वापस false;
पूर्ण

अटल पूर्णांक
esw_setup_chain_src_port_reग_लिखो(काष्ठा mlx5_flow_destination *dest,
				 काष्ठा mlx5_flow_act *flow_act,
				 काष्ठा mlx5_eचयन *esw,
				 काष्ठा mlx5_fs_chains *chains,
				 काष्ठा mlx5_flow_attr *attr,
				 पूर्णांक *i)
अणु
	काष्ठा mlx5_esw_flow_attr *esw_attr = attr->esw_attr;
	पूर्णांक j, err;

	अगर (!(attr->flags & MLX5_ESW_ATTR_FLAG_SRC_REWRITE))
		वापस -EOPNOTSUPP;

	क्रम (j = esw_attr->split_count; j < esw_attr->out_count; j++, (*i)++) अणु
		err = esw_setup_chain_dest(dest, flow_act, chains, attr->dest_chain, 1, 0, *i);
		अगर (err)
			जाओ err_setup_chain;
		flow_act->action |= MLX5_FLOW_CONTEXT_ACTION_PACKET_REFORMAT;
		flow_act->pkt_reक्रमmat = esw_attr->dests[j].pkt_reक्रमmat;
	पूर्ण
	वापस 0;

err_setup_chain:
	esw_put_dest_tables_loop(esw, attr, esw_attr->split_count, j);
	वापस err;
पूर्ण

अटल व्योम esw_cleanup_chain_src_port_reग_लिखो(काष्ठा mlx5_eचयन *esw,
					       काष्ठा mlx5_flow_attr *attr)
अणु
	काष्ठा mlx5_esw_flow_attr *esw_attr = attr->esw_attr;

	esw_put_dest_tables_loop(esw, attr, esw_attr->split_count, esw_attr->out_count);
पूर्ण

अटल bool
esw_is_indir_table(काष्ठा mlx5_eचयन *esw, काष्ठा mlx5_flow_attr *attr)
अणु
	काष्ठा mlx5_esw_flow_attr *esw_attr = attr->esw_attr;
	पूर्णांक i;

	क्रम (i = esw_attr->split_count; i < esw_attr->out_count; i++)
		अगर (mlx5_esw_indir_table_needed(esw, attr, esw_attr->dests[i].rep->vport,
						esw_attr->dests[i].mdev))
			वापस true;
	वापस false;
पूर्ण

अटल पूर्णांक
esw_setup_indir_table(काष्ठा mlx5_flow_destination *dest,
		      काष्ठा mlx5_flow_act *flow_act,
		      काष्ठा mlx5_eचयन *esw,
		      काष्ठा mlx5_flow_attr *attr,
		      काष्ठा mlx5_flow_spec *spec,
		      bool ignore_flow_lvl,
		      पूर्णांक *i)
अणु
	काष्ठा mlx5_esw_flow_attr *esw_attr = attr->esw_attr;
	पूर्णांक j, err;

	अगर (!(attr->flags & MLX5_ESW_ATTR_FLAG_SRC_REWRITE))
		वापस -EOPNOTSUPP;

	क्रम (j = esw_attr->split_count; j < esw_attr->out_count; j++, (*i)++) अणु
		अगर (ignore_flow_lvl)
			flow_act->flags |= FLOW_ACT_IGNORE_FLOW_LEVEL;
		dest[*i].type = MLX5_FLOW_DESTINATION_TYPE_FLOW_TABLE;

		dest[*i].ft = mlx5_esw_indir_table_get(esw, attr, spec,
						       esw_attr->dests[j].rep->vport, false);
		अगर (IS_ERR(dest[*i].ft)) अणु
			err = PTR_ERR(dest[*i].ft);
			जाओ err_indir_tbl_get;
		पूर्ण
	पूर्ण

	अगर (mlx5_esw_indir_table_decap_vport(attr)) अणु
		err = esw_setup_decap_indir(esw, attr, spec);
		अगर (err)
			जाओ err_indir_tbl_get;
	पूर्ण

	वापस 0;

err_indir_tbl_get:
	esw_put_dest_tables_loop(esw, attr, esw_attr->split_count, j);
	वापस err;
पूर्ण

अटल व्योम esw_cleanup_indir_table(काष्ठा mlx5_eचयन *esw, काष्ठा mlx5_flow_attr *attr)
अणु
	काष्ठा mlx5_esw_flow_attr *esw_attr = attr->esw_attr;

	esw_put_dest_tables_loop(esw, attr, esw_attr->split_count, esw_attr->out_count);
	esw_cleanup_decap_indir(esw, attr);
पूर्ण

अटल व्योम
esw_cleanup_chain_dest(काष्ठा mlx5_fs_chains *chains, u32 chain, u32 prio, u32 level)
अणु
	mlx5_chains_put_table(chains, chain, prio, level);
पूर्ण

अटल व्योम
esw_setup_vport_dest(काष्ठा mlx5_flow_destination *dest, काष्ठा mlx5_flow_act *flow_act,
		     काष्ठा mlx5_eचयन *esw, काष्ठा mlx5_esw_flow_attr *esw_attr,
		     पूर्णांक attr_idx, पूर्णांक dest_idx, bool pkt_reक्रमmat)
अणु
	dest[dest_idx].type = MLX5_FLOW_DESTINATION_TYPE_VPORT;
	dest[dest_idx].vport.num = esw_attr->dests[attr_idx].rep->vport;
	dest[dest_idx].vport.vhca_id =
		MLX5_CAP_GEN(esw_attr->dests[attr_idx].mdev, vhca_id);
	अगर (MLX5_CAP_ESW(esw->dev, merged_eचयन))
		dest[dest_idx].vport.flags |= MLX5_FLOW_DEST_VPORT_VHCA_ID;
	अगर (esw_attr->dests[attr_idx].flags & MLX5_ESW_DEST_ENCAP) अणु
		अगर (pkt_reक्रमmat) अणु
			flow_act->action |= MLX5_FLOW_CONTEXT_ACTION_PACKET_REFORMAT;
			flow_act->pkt_reक्रमmat = esw_attr->dests[attr_idx].pkt_reक्रमmat;
		पूर्ण
		dest[dest_idx].vport.flags |= MLX5_FLOW_DEST_VPORT_REFORMAT_ID;
		dest[dest_idx].vport.pkt_reक्रमmat = esw_attr->dests[attr_idx].pkt_reक्रमmat;
	पूर्ण
पूर्ण

अटल पूर्णांक
esw_setup_vport_dests(काष्ठा mlx5_flow_destination *dest, काष्ठा mlx5_flow_act *flow_act,
		      काष्ठा mlx5_eचयन *esw, काष्ठा mlx5_esw_flow_attr *esw_attr,
		      पूर्णांक i)
अणु
	पूर्णांक j;

	क्रम (j = esw_attr->split_count; j < esw_attr->out_count; j++, i++)
		esw_setup_vport_dest(dest, flow_act, esw, esw_attr, j, i, true);
	वापस i;
पूर्ण

अटल bool
esw_src_port_reग_लिखो_supported(काष्ठा mlx5_eचयन *esw)
अणु
	वापस MLX5_CAP_GEN(esw->dev, reg_c_preserve) &&
	       mlx5_eचयन_vport_match_metadata_enabled(esw) &&
	       MLX5_CAP_ESW_FLOWTABLE_FDB(esw->dev, ignore_flow_level);
पूर्ण

अटल पूर्णांक
esw_setup_dests(काष्ठा mlx5_flow_destination *dest,
		काष्ठा mlx5_flow_act *flow_act,
		काष्ठा mlx5_eचयन *esw,
		काष्ठा mlx5_flow_attr *attr,
		काष्ठा mlx5_flow_spec *spec,
		पूर्णांक *i)
अणु
	काष्ठा mlx5_esw_flow_attr *esw_attr = attr->esw_attr;
	काष्ठा mlx5_fs_chains *chains = esw_chains(esw);
	पूर्णांक err = 0;

	अगर (!mlx5_eचयन_termtbl_required(esw, attr, flow_act, spec) &&
	    esw_src_port_reग_लिखो_supported(esw))
		attr->flags |= MLX5_ESW_ATTR_FLAG_SRC_REWRITE;

	अगर (attr->flags & MLX5_ESW_ATTR_FLAG_SAMPLE) अणु
		esw_setup_sampler_dest(dest, flow_act, esw_attr, *i);
		(*i)++;
	पूर्ण अन्यथा अगर (attr->dest_ft) अणु
		esw_setup_ft_dest(dest, flow_act, esw, attr, spec, *i);
		(*i)++;
	पूर्ण अन्यथा अगर (attr->flags & MLX5_ESW_ATTR_FLAG_SLOW_PATH) अणु
		esw_setup_slow_path_dest(dest, flow_act, chains, *i);
		(*i)++;
	पूर्ण अन्यथा अगर (attr->dest_chain) अणु
		err = esw_setup_chain_dest(dest, flow_act, chains, attr->dest_chain,
					   1, 0, *i);
		(*i)++;
	पूर्ण अन्यथा अगर (esw_is_indir_table(esw, attr)) अणु
		err = esw_setup_indir_table(dest, flow_act, esw, attr, spec, true, i);
	पूर्ण अन्यथा अगर (esw_is_chain_src_port_reग_लिखो(esw, esw_attr)) अणु
		err = esw_setup_chain_src_port_reग_लिखो(dest, flow_act, esw, chains, attr, i);
	पूर्ण अन्यथा अणु
		*i = esw_setup_vport_dests(dest, flow_act, esw, esw_attr, *i);
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम
esw_cleanup_dests(काष्ठा mlx5_eचयन *esw,
		  काष्ठा mlx5_flow_attr *attr)
अणु
	काष्ठा mlx5_esw_flow_attr *esw_attr = attr->esw_attr;
	काष्ठा mlx5_fs_chains *chains = esw_chains(esw);

	अगर (attr->dest_ft) अणु
		esw_cleanup_decap_indir(esw, attr);
	पूर्ण अन्यथा अगर (!(attr->flags & MLX5_ESW_ATTR_FLAG_SLOW_PATH)) अणु
		अगर (attr->dest_chain)
			esw_cleanup_chain_dest(chains, attr->dest_chain, 1, 0);
		अन्यथा अगर (esw_is_indir_table(esw, attr))
			esw_cleanup_indir_table(esw, attr);
		अन्यथा अगर (esw_is_chain_src_port_reग_लिखो(esw, esw_attr))
			esw_cleanup_chain_src_port_reग_लिखो(esw, attr);
	पूर्ण
पूर्ण

काष्ठा mlx5_flow_handle *
mlx5_eचयन_add_offloaded_rule(काष्ठा mlx5_eचयन *esw,
				काष्ठा mlx5_flow_spec *spec,
				काष्ठा mlx5_flow_attr *attr)
अणु
	काष्ठा mlx5_flow_destination dest[MLX5_MAX_FLOW_FWD_VPORTS + 1] = अणुपूर्ण;
	काष्ठा mlx5_flow_act flow_act = अणु .flags = FLOW_ACT_NO_APPEND, पूर्ण;
	काष्ठा mlx5_esw_flow_attr *esw_attr = attr->esw_attr;
	काष्ठा mlx5_fs_chains *chains = esw_chains(esw);
	bool split = !!(esw_attr->split_count);
	काष्ठा mlx5_vport_tbl_attr fwd_attr;
	काष्ठा mlx5_flow_handle *rule;
	काष्ठा mlx5_flow_table *fdb;
	पूर्णांक i = 0;

	अगर (esw->mode != MLX5_ESWITCH_OFFLOADS)
		वापस ERR_PTR(-EOPNOTSUPP);

	flow_act.action = attr->action;
	/* अगर per flow vlan pop/push is emulated, करोn't set that पूर्णांकo the firmware */
	अगर (!mlx5_eचयन_vlan_actions_supported(esw->dev, 1))
		flow_act.action &= ~(MLX5_FLOW_CONTEXT_ACTION_VLAN_PUSH |
				     MLX5_FLOW_CONTEXT_ACTION_VLAN_POP);
	अन्यथा अगर (flow_act.action & MLX5_FLOW_CONTEXT_ACTION_VLAN_PUSH) अणु
		flow_act.vlan[0].ethtype = ntohs(esw_attr->vlan_proto[0]);
		flow_act.vlan[0].vid = esw_attr->vlan_vid[0];
		flow_act.vlan[0].prio = esw_attr->vlan_prio[0];
		अगर (flow_act.action & MLX5_FLOW_CONTEXT_ACTION_VLAN_PUSH_2) अणु
			flow_act.vlan[1].ethtype = ntohs(esw_attr->vlan_proto[1]);
			flow_act.vlan[1].vid = esw_attr->vlan_vid[1];
			flow_act.vlan[1].prio = esw_attr->vlan_prio[1];
		पूर्ण
	पूर्ण

	mlx5_eचयन_set_rule_flow_source(esw, spec, esw_attr);

	अगर (flow_act.action & MLX5_FLOW_CONTEXT_ACTION_FWD_DEST) अणु
		पूर्णांक err;

		err = esw_setup_dests(dest, &flow_act, esw, attr, spec, &i);
		अगर (err) अणु
			rule = ERR_PTR(err);
			जाओ err_create_जाओ_table;
		पूर्ण
	पूर्ण

	अगर (esw_attr->decap_pkt_reक्रमmat)
		flow_act.pkt_reक्रमmat = esw_attr->decap_pkt_reक्रमmat;

	अगर (flow_act.action & MLX5_FLOW_CONTEXT_ACTION_COUNT) अणु
		dest[i].type = MLX5_FLOW_DESTINATION_TYPE_COUNTER;
		dest[i].counter_id = mlx5_fc_id(attr->counter);
		i++;
	पूर्ण

	अगर (attr->outer_match_level != MLX5_MATCH_NONE)
		spec->match_criteria_enable |= MLX5_MATCH_OUTER_HEADERS;
	अगर (attr->inner_match_level != MLX5_MATCH_NONE)
		spec->match_criteria_enable |= MLX5_MATCH_INNER_HEADERS;

	अगर (flow_act.action & MLX5_FLOW_CONTEXT_ACTION_MOD_HDR)
		flow_act.modअगरy_hdr = attr->modअगरy_hdr;

	/* esw_attr->sample is allocated only when there is a sample action */
	अगर (esw_attr->sample && esw_attr->sample->sample_शेष_tbl) अणु
		fdb = esw_attr->sample->sample_शेष_tbl;
	पूर्ण अन्यथा अगर (split) अणु
		fwd_attr.chain = attr->chain;
		fwd_attr.prio = attr->prio;
		fwd_attr.vport = esw_attr->in_rep->vport;
		fwd_attr.vport_ns = &mlx5_esw_vport_tbl_mirror_ns;

		fdb = mlx5_esw_vporttbl_get(esw, &fwd_attr);
	पूर्ण अन्यथा अणु
		अगर (attr->chain || attr->prio)
			fdb = mlx5_chains_get_table(chains, attr->chain,
						    attr->prio, 0);
		अन्यथा
			fdb = attr->ft;

		अगर (!(attr->flags & MLX5_ESW_ATTR_FLAG_NO_IN_PORT))
			mlx5_eचयन_set_rule_source_port(esw, spec, attr,
							  esw_attr->in_mdev->priv.eचयन,
							  esw_attr->in_rep->vport);
	पूर्ण
	अगर (IS_ERR(fdb)) अणु
		rule = ERR_CAST(fdb);
		जाओ err_esw_get;
	पूर्ण

	अगर (mlx5_eचयन_termtbl_required(esw, attr, &flow_act, spec))
		rule = mlx5_eचयन_add_termtbl_rule(esw, fdb, spec, esw_attr,
						     &flow_act, dest, i);
	अन्यथा
		rule = mlx5_add_flow_rules(fdb, spec, &flow_act, dest, i);
	अगर (IS_ERR(rule))
		जाओ err_add_rule;
	अन्यथा
		atomic64_inc(&esw->offloads.num_flows);

	वापस rule;

err_add_rule:
	अगर (split)
		mlx5_esw_vporttbl_put(esw, &fwd_attr);
	अन्यथा अगर (attr->chain || attr->prio)
		mlx5_chains_put_table(chains, attr->chain, attr->prio, 0);
err_esw_get:
	esw_cleanup_dests(esw, attr);
err_create_जाओ_table:
	वापस rule;
पूर्ण

काष्ठा mlx5_flow_handle *
mlx5_eचयन_add_fwd_rule(काष्ठा mlx5_eचयन *esw,
			  काष्ठा mlx5_flow_spec *spec,
			  काष्ठा mlx5_flow_attr *attr)
अणु
	काष्ठा mlx5_flow_destination dest[MLX5_MAX_FLOW_FWD_VPORTS + 1] = अणुपूर्ण;
	काष्ठा mlx5_flow_act flow_act = अणु .flags = FLOW_ACT_NO_APPEND, पूर्ण;
	काष्ठा mlx5_esw_flow_attr *esw_attr = attr->esw_attr;
	काष्ठा mlx5_fs_chains *chains = esw_chains(esw);
	काष्ठा mlx5_vport_tbl_attr fwd_attr;
	काष्ठा mlx5_flow_table *fast_fdb;
	काष्ठा mlx5_flow_table *fwd_fdb;
	काष्ठा mlx5_flow_handle *rule;
	पूर्णांक i, err = 0;

	fast_fdb = mlx5_chains_get_table(chains, attr->chain, attr->prio, 0);
	अगर (IS_ERR(fast_fdb)) अणु
		rule = ERR_CAST(fast_fdb);
		जाओ err_get_fast;
	पूर्ण

	fwd_attr.chain = attr->chain;
	fwd_attr.prio = attr->prio;
	fwd_attr.vport = esw_attr->in_rep->vport;
	fwd_attr.vport_ns = &mlx5_esw_vport_tbl_mirror_ns;
	fwd_fdb = mlx5_esw_vporttbl_get(esw, &fwd_attr);
	अगर (IS_ERR(fwd_fdb)) अणु
		rule = ERR_CAST(fwd_fdb);
		जाओ err_get_fwd;
	पूर्ण

	flow_act.action = MLX5_FLOW_CONTEXT_ACTION_FWD_DEST;
	क्रम (i = 0; i < esw_attr->split_count; i++) अणु
		अगर (esw_is_indir_table(esw, attr))
			err = esw_setup_indir_table(dest, &flow_act, esw, attr, spec, false, &i);
		अन्यथा अगर (esw_is_chain_src_port_reग_लिखो(esw, esw_attr))
			err = esw_setup_chain_src_port_reग_लिखो(dest, &flow_act, esw, chains, attr,
							       &i);
		अन्यथा
			esw_setup_vport_dest(dest, &flow_act, esw, esw_attr, i, i, false);

		अगर (err) अणु
			rule = ERR_PTR(err);
			जाओ err_chain_src_reग_लिखो;
		पूर्ण
	पूर्ण
	dest[i].type = MLX5_FLOW_DESTINATION_TYPE_FLOW_TABLE;
	dest[i].ft = fwd_fdb;
	i++;

	mlx5_eचयन_set_rule_source_port(esw, spec, attr,
					  esw_attr->in_mdev->priv.eचयन,
					  esw_attr->in_rep->vport);

	अगर (attr->outer_match_level != MLX5_MATCH_NONE)
		spec->match_criteria_enable |= MLX5_MATCH_OUTER_HEADERS;

	flow_act.flags |= FLOW_ACT_IGNORE_FLOW_LEVEL;
	rule = mlx5_add_flow_rules(fast_fdb, spec, &flow_act, dest, i);

	अगर (IS_ERR(rule)) अणु
		i = esw_attr->split_count;
		जाओ err_chain_src_reग_लिखो;
	पूर्ण

	atomic64_inc(&esw->offloads.num_flows);

	वापस rule;
err_chain_src_reग_लिखो:
	esw_put_dest_tables_loop(esw, attr, 0, i);
	mlx5_esw_vporttbl_put(esw, &fwd_attr);
err_get_fwd:
	mlx5_chains_put_table(chains, attr->chain, attr->prio, 0);
err_get_fast:
	वापस rule;
पूर्ण

अटल व्योम
__mlx5_eचयन_del_rule(काष्ठा mlx5_eचयन *esw,
			काष्ठा mlx5_flow_handle *rule,
			काष्ठा mlx5_flow_attr *attr,
			bool fwd_rule)
अणु
	काष्ठा mlx5_esw_flow_attr *esw_attr = attr->esw_attr;
	काष्ठा mlx5_fs_chains *chains = esw_chains(esw);
	bool split = (esw_attr->split_count > 0);
	काष्ठा mlx5_vport_tbl_attr fwd_attr;
	पूर्णांक i;

	mlx5_del_flow_rules(rule);

	अगर (!(attr->flags & MLX5_ESW_ATTR_FLAG_SLOW_PATH)) अणु
		/* unref the term table */
		क्रम (i = 0; i < MLX5_MAX_FLOW_FWD_VPORTS; i++) अणु
			अगर (esw_attr->dests[i].termtbl)
				mlx5_eचयन_termtbl_put(esw, esw_attr->dests[i].termtbl);
		पूर्ण
	पूर्ण

	atomic64_dec(&esw->offloads.num_flows);

	अगर (fwd_rule || split) अणु
		fwd_attr.chain = attr->chain;
		fwd_attr.prio = attr->prio;
		fwd_attr.vport = esw_attr->in_rep->vport;
		fwd_attr.vport_ns = &mlx5_esw_vport_tbl_mirror_ns;
	पूर्ण

	अगर (fwd_rule)  अणु
		mlx5_esw_vporttbl_put(esw, &fwd_attr);
		mlx5_chains_put_table(chains, attr->chain, attr->prio, 0);
		esw_put_dest_tables_loop(esw, attr, 0, esw_attr->split_count);
	पूर्ण अन्यथा अणु
		अगर (split)
			mlx5_esw_vporttbl_put(esw, &fwd_attr);
		अन्यथा अगर (attr->chain || attr->prio)
			mlx5_chains_put_table(chains, attr->chain, attr->prio, 0);
		esw_cleanup_dests(esw, attr);
	पूर्ण
पूर्ण

व्योम
mlx5_eचयन_del_offloaded_rule(काष्ठा mlx5_eचयन *esw,
				काष्ठा mlx5_flow_handle *rule,
				काष्ठा mlx5_flow_attr *attr)
अणु
	__mlx5_eचयन_del_rule(esw, rule, attr, false);
पूर्ण

व्योम
mlx5_eचयन_del_fwd_rule(काष्ठा mlx5_eचयन *esw,
			  काष्ठा mlx5_flow_handle *rule,
			  काष्ठा mlx5_flow_attr *attr)
अणु
	__mlx5_eचयन_del_rule(esw, rule, attr, true);
पूर्ण

अटल पूर्णांक esw_set_global_vlan_pop(काष्ठा mlx5_eचयन *esw, u8 val)
अणु
	काष्ठा mlx5_eचयन_rep *rep;
	अचिन्हित दीर्घ i;
	पूर्णांक err = 0;

	esw_debug(esw->dev, "%s applying global %s policy\n", __func__, val ? "pop" : "none");
	mlx5_esw_क्रम_each_host_func_vport(esw, i, rep, esw->esw_funcs.num_vfs) अणु
		अगर (atomic_पढ़ो(&rep->rep_data[REP_ETH].state) != REP_LOADED)
			जारी;

		err = __mlx5_eचयन_set_vport_vlan(esw, rep->vport, 0, 0, val);
		अगर (err)
			जाओ out;
	पूर्ण

out:
	वापस err;
पूर्ण

अटल काष्ठा mlx5_eचयन_rep *
esw_vlan_action_get_vport(काष्ठा mlx5_esw_flow_attr *attr, bool push, bool pop)
अणु
	काष्ठा mlx5_eचयन_rep *in_rep, *out_rep, *vport = शून्य;

	in_rep  = attr->in_rep;
	out_rep = attr->dests[0].rep;

	अगर (push)
		vport = in_rep;
	अन्यथा अगर (pop)
		vport = out_rep;
	अन्यथा
		vport = in_rep;

	वापस vport;
पूर्ण

अटल पूर्णांक esw_add_vlan_action_check(काष्ठा mlx5_esw_flow_attr *attr,
				     bool push, bool pop, bool fwd)
अणु
	काष्ठा mlx5_eचयन_rep *in_rep, *out_rep;

	अगर ((push || pop) && !fwd)
		जाओ out_notsupp;

	in_rep  = attr->in_rep;
	out_rep = attr->dests[0].rep;

	अगर (push && in_rep->vport == MLX5_VPORT_UPLINK)
		जाओ out_notsupp;

	अगर (pop && out_rep->vport == MLX5_VPORT_UPLINK)
		जाओ out_notsupp;

	/* vport has vlan push configured, can't offload VF --> wire rules w.o it */
	अगर (!push && !pop && fwd)
		अगर (in_rep->vlan && out_rep->vport == MLX5_VPORT_UPLINK)
			जाओ out_notsupp;

	/* protects against (1) setting rules with dअगरferent vlans to push and
	 * (2) setting rules w.o vlans (attr->vlan = 0) && w. vlans to push (!= 0)
	 */
	अगर (push && in_rep->vlan_refcount && (in_rep->vlan != attr->vlan_vid[0]))
		जाओ out_notsupp;

	वापस 0;

out_notsupp:
	वापस -EOPNOTSUPP;
पूर्ण

पूर्णांक mlx5_eचयन_add_vlan_action(काष्ठा mlx5_eचयन *esw,
				 काष्ठा mlx5_flow_attr *attr)
अणु
	काष्ठा offloads_fdb *offloads = &esw->fdb_table.offloads;
	काष्ठा mlx5_esw_flow_attr *esw_attr = attr->esw_attr;
	काष्ठा mlx5_eचयन_rep *vport = शून्य;
	bool push, pop, fwd;
	पूर्णांक err = 0;

	/* nop अगर we're on the vlan push/pop non emulation mode */
	अगर (mlx5_eचयन_vlan_actions_supported(esw->dev, 1))
		वापस 0;

	push = !!(attr->action & MLX5_FLOW_CONTEXT_ACTION_VLAN_PUSH);
	pop  = !!(attr->action & MLX5_FLOW_CONTEXT_ACTION_VLAN_POP);
	fwd  = !!((attr->action & MLX5_FLOW_CONTEXT_ACTION_FWD_DEST) &&
		   !attr->dest_chain);

	mutex_lock(&esw->state_lock);

	err = esw_add_vlan_action_check(esw_attr, push, pop, fwd);
	अगर (err)
		जाओ unlock;

	attr->flags &= ~MLX5_ESW_ATTR_FLAG_VLAN_HANDLED;

	vport = esw_vlan_action_get_vport(esw_attr, push, pop);

	अगर (!push && !pop && fwd) अणु
		/* tracks VF --> wire rules without vlan push action */
		अगर (esw_attr->dests[0].rep->vport == MLX5_VPORT_UPLINK) अणु
			vport->vlan_refcount++;
			attr->flags |= MLX5_ESW_ATTR_FLAG_VLAN_HANDLED;
		पूर्ण

		जाओ unlock;
	पूर्ण

	अगर (!push && !pop)
		जाओ unlock;

	अगर (!(offloads->vlan_push_pop_refcount)) अणु
		/* it's the 1st vlan rule, apply global vlan pop policy */
		err = esw_set_global_vlan_pop(esw, SET_VLAN_STRIP);
		अगर (err)
			जाओ out;
	पूर्ण
	offloads->vlan_push_pop_refcount++;

	अगर (push) अणु
		अगर (vport->vlan_refcount)
			जाओ skip_set_push;

		err = __mlx5_eचयन_set_vport_vlan(esw, vport->vport, esw_attr->vlan_vid[0],
						    0, SET_VLAN_INSERT | SET_VLAN_STRIP);
		अगर (err)
			जाओ out;
		vport->vlan = esw_attr->vlan_vid[0];
skip_set_push:
		vport->vlan_refcount++;
	पूर्ण
out:
	अगर (!err)
		attr->flags |= MLX5_ESW_ATTR_FLAG_VLAN_HANDLED;
unlock:
	mutex_unlock(&esw->state_lock);
	वापस err;
पूर्ण

पूर्णांक mlx5_eचयन_del_vlan_action(काष्ठा mlx5_eचयन *esw,
				 काष्ठा mlx5_flow_attr *attr)
अणु
	काष्ठा offloads_fdb *offloads = &esw->fdb_table.offloads;
	काष्ठा mlx5_esw_flow_attr *esw_attr = attr->esw_attr;
	काष्ठा mlx5_eचयन_rep *vport = शून्य;
	bool push, pop, fwd;
	पूर्णांक err = 0;

	/* nop अगर we're on the vlan push/pop non emulation mode */
	अगर (mlx5_eचयन_vlan_actions_supported(esw->dev, 1))
		वापस 0;

	अगर (!(attr->flags & MLX5_ESW_ATTR_FLAG_VLAN_HANDLED))
		वापस 0;

	push = !!(attr->action & MLX5_FLOW_CONTEXT_ACTION_VLAN_PUSH);
	pop  = !!(attr->action & MLX5_FLOW_CONTEXT_ACTION_VLAN_POP);
	fwd  = !!(attr->action & MLX5_FLOW_CONTEXT_ACTION_FWD_DEST);

	mutex_lock(&esw->state_lock);

	vport = esw_vlan_action_get_vport(esw_attr, push, pop);

	अगर (!push && !pop && fwd) अणु
		/* tracks VF --> wire rules without vlan push action */
		अगर (esw_attr->dests[0].rep->vport == MLX5_VPORT_UPLINK)
			vport->vlan_refcount--;

		जाओ out;
	पूर्ण

	अगर (push) अणु
		vport->vlan_refcount--;
		अगर (vport->vlan_refcount)
			जाओ skip_unset_push;

		vport->vlan = 0;
		err = __mlx5_eचयन_set_vport_vlan(esw, vport->vport,
						    0, 0, SET_VLAN_STRIP);
		अगर (err)
			जाओ out;
	पूर्ण

skip_unset_push:
	offloads->vlan_push_pop_refcount--;
	अगर (offloads->vlan_push_pop_refcount)
		जाओ out;

	/* no more vlan rules, stop global vlan pop policy */
	err = esw_set_global_vlan_pop(esw, 0);

out:
	mutex_unlock(&esw->state_lock);
	वापस err;
पूर्ण

काष्ठा mlx5_flow_handle *
mlx5_eचयन_add_send_to_vport_rule(काष्ठा mlx5_eचयन *on_esw,
				    काष्ठा mlx5_eचयन_rep *rep,
				    u32 sqn)
अणु
	काष्ठा mlx5_flow_act flow_act = अणु0पूर्ण;
	काष्ठा mlx5_flow_destination dest = अणुपूर्ण;
	काष्ठा mlx5_flow_handle *flow_rule;
	काष्ठा mlx5_flow_spec *spec;
	व्योम *misc;

	spec = kvzalloc(माप(*spec), GFP_KERNEL);
	अगर (!spec) अणु
		flow_rule = ERR_PTR(-ENOMEM);
		जाओ out;
	पूर्ण

	misc = MLX5_ADDR_OF(fte_match_param, spec->match_value, misc_parameters);
	MLX5_SET(fte_match_set_misc, misc, source_sqn, sqn);
	/* source vport is the esw manager */
	MLX5_SET(fte_match_set_misc, misc, source_port, rep->esw->manager_vport);
	अगर (MLX5_CAP_ESW(on_esw->dev, merged_eचयन))
		MLX5_SET(fte_match_set_misc, misc, source_eचयन_owner_vhca_id,
			 MLX5_CAP_GEN(rep->esw->dev, vhca_id));

	misc = MLX5_ADDR_OF(fte_match_param, spec->match_criteria, misc_parameters);
	MLX5_SET_TO_ONES(fte_match_set_misc, misc, source_sqn);
	MLX5_SET_TO_ONES(fte_match_set_misc, misc, source_port);
	अगर (MLX5_CAP_ESW(on_esw->dev, merged_eचयन))
		MLX5_SET_TO_ONES(fte_match_set_misc, misc,
				 source_eचयन_owner_vhca_id);

	spec->match_criteria_enable = MLX5_MATCH_MISC_PARAMETERS;
	dest.type = MLX5_FLOW_DESTINATION_TYPE_VPORT;
	dest.vport.num = rep->vport;
	dest.vport.vhca_id = MLX5_CAP_GEN(rep->esw->dev, vhca_id);
	dest.vport.flags |= MLX5_FLOW_DEST_VPORT_VHCA_ID;
	flow_act.action = MLX5_FLOW_CONTEXT_ACTION_FWD_DEST;

	flow_rule = mlx5_add_flow_rules(on_esw->fdb_table.offloads.slow_fdb,
					spec, &flow_act, &dest, 1);
	अगर (IS_ERR(flow_rule))
		esw_warn(on_esw->dev, "FDB: Failed to add send to vport rule err %ld\n",
			 PTR_ERR(flow_rule));
out:
	kvमुक्त(spec);
	वापस flow_rule;
पूर्ण
EXPORT_SYMBOL(mlx5_eचयन_add_send_to_vport_rule);

व्योम mlx5_eचयन_del_send_to_vport_rule(काष्ठा mlx5_flow_handle *rule)
अणु
	mlx5_del_flow_rules(rule);
पूर्ण

अटल व्योम mlx5_eचयन_del_send_to_vport_meta_rules(काष्ठा mlx5_eचयन *esw)
अणु
	काष्ठा mlx5_flow_handle **flows = esw->fdb_table.offloads.send_to_vport_meta_rules;
	पूर्णांक i = 0, num_vfs = esw->esw_funcs.num_vfs;

	अगर (!num_vfs || !flows)
		वापस;

	क्रम (i = 0; i < num_vfs; i++)
		mlx5_del_flow_rules(flows[i]);

	kvमुक्त(flows);
पूर्ण

अटल पूर्णांक
mlx5_eचयन_add_send_to_vport_meta_rules(काष्ठा mlx5_eचयन *esw)
अणु
	काष्ठा mlx5_flow_destination dest = अणुपूर्ण;
	काष्ठा mlx5_flow_act flow_act = अणु0पूर्ण;
	पूर्णांक num_vfs, rule_idx = 0, err = 0;
	काष्ठा mlx5_flow_handle *flow_rule;
	काष्ठा mlx5_flow_handle **flows;
	काष्ठा mlx5_flow_spec *spec;
	काष्ठा mlx5_vport *vport;
	अचिन्हित दीर्घ i;
	u16 vport_num;

	num_vfs = esw->esw_funcs.num_vfs;
	flows = kvzalloc(num_vfs * माप(*flows), GFP_KERNEL);
	अगर (!flows)
		वापस -ENOMEM;

	spec = kvzalloc(माप(*spec), GFP_KERNEL);
	अगर (!spec) अणु
		err = -ENOMEM;
		जाओ alloc_err;
	पूर्ण

	MLX5_SET(fte_match_param, spec->match_criteria,
		 misc_parameters_2.metadata_reg_c_0, mlx5_eचयन_get_vport_metadata_mask());
	MLX5_SET(fte_match_param, spec->match_criteria,
		 misc_parameters_2.metadata_reg_c_1, ESW_TUN_MASK);
	MLX5_SET(fte_match_param, spec->match_value, misc_parameters_2.metadata_reg_c_1,
		 ESW_TUN_SLOW_TABLE_GOTO_VPORT_MARK);

	spec->match_criteria_enable = MLX5_MATCH_MISC_PARAMETERS_2;
	dest.type = MLX5_FLOW_DESTINATION_TYPE_VPORT;
	flow_act.action = MLX5_FLOW_CONTEXT_ACTION_FWD_DEST;

	mlx5_esw_क्रम_each_vf_vport(esw, i, vport, num_vfs) अणु
		vport_num = vport->vport;
		MLX5_SET(fte_match_param, spec->match_value, misc_parameters_2.metadata_reg_c_0,
			 mlx5_eचयन_get_vport_metadata_क्रम_match(esw, vport_num));
		dest.vport.num = vport_num;

		flow_rule = mlx5_add_flow_rules(esw->fdb_table.offloads.slow_fdb,
						spec, &flow_act, &dest, 1);
		अगर (IS_ERR(flow_rule)) अणु
			err = PTR_ERR(flow_rule);
			esw_warn(esw->dev, "FDB: Failed to add send to vport meta rule idx %d, err %ld\n",
				 rule_idx, PTR_ERR(flow_rule));
			जाओ rule_err;
		पूर्ण
		flows[rule_idx++] = flow_rule;
	पूर्ण

	esw->fdb_table.offloads.send_to_vport_meta_rules = flows;
	kvमुक्त(spec);
	वापस 0;

rule_err:
	जबतक (--rule_idx >= 0)
		mlx5_del_flow_rules(flows[rule_idx]);
	kvमुक्त(spec);
alloc_err:
	kvमुक्त(flows);
	वापस err;
पूर्ण

अटल bool mlx5_eचयन_reg_c1_loopback_supported(काष्ठा mlx5_eचयन *esw)
अणु
	वापस MLX5_CAP_ESW_FLOWTABLE(esw->dev, fdb_to_vport_reg_c_id) &
	       MLX5_FDB_TO_VPORT_REG_C_1;
पूर्ण

अटल पूर्णांक esw_set_passing_vport_metadata(काष्ठा mlx5_eचयन *esw, bool enable)
अणु
	u32 out[MLX5_ST_SZ_DW(query_esw_vport_context_out)] = अणुपूर्ण;
	u32 min[MLX5_ST_SZ_DW(modअगरy_esw_vport_context_in)] = अणुपूर्ण;
	u32 in[MLX5_ST_SZ_DW(query_esw_vport_context_in)] = अणुपूर्ण;
	u8 curr, wanted;
	पूर्णांक err;

	अगर (!mlx5_eचयन_reg_c1_loopback_supported(esw) &&
	    !mlx5_eचयन_vport_match_metadata_enabled(esw))
		वापस 0;

	MLX5_SET(query_esw_vport_context_in, in, opcode,
		 MLX5_CMD_OP_QUERY_ESW_VPORT_CONTEXT);
	err = mlx5_cmd_exec_inout(esw->dev, query_esw_vport_context, in, out);
	अगर (err)
		वापस err;

	curr = MLX5_GET(query_esw_vport_context_out, out,
			esw_vport_context.fdb_to_vport_reg_c_id);
	wanted = MLX5_FDB_TO_VPORT_REG_C_0;
	अगर (mlx5_eचयन_reg_c1_loopback_supported(esw))
		wanted |= MLX5_FDB_TO_VPORT_REG_C_1;

	अगर (enable)
		curr |= wanted;
	अन्यथा
		curr &= ~wanted;

	MLX5_SET(modअगरy_esw_vport_context_in, min,
		 esw_vport_context.fdb_to_vport_reg_c_id, curr);
	MLX5_SET(modअगरy_esw_vport_context_in, min,
		 field_select.fdb_to_vport_reg_c_id, 1);

	err = mlx5_eचयन_modअगरy_esw_vport_context(esw->dev, 0, false, min);
	अगर (!err) अणु
		अगर (enable && (curr & MLX5_FDB_TO_VPORT_REG_C_1))
			esw->flags |= MLX5_ESWITCH_REG_C1_LOOPBACK_ENABLED;
		अन्यथा
			esw->flags &= ~MLX5_ESWITCH_REG_C1_LOOPBACK_ENABLED;
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम peer_miss_rules_setup(काष्ठा mlx5_eचयन *esw,
				  काष्ठा mlx5_core_dev *peer_dev,
				  काष्ठा mlx5_flow_spec *spec,
				  काष्ठा mlx5_flow_destination *dest)
अणु
	व्योम *misc;

	अगर (mlx5_eचयन_vport_match_metadata_enabled(esw)) अणु
		misc = MLX5_ADDR_OF(fte_match_param, spec->match_criteria,
				    misc_parameters_2);
		MLX5_SET(fte_match_set_misc2, misc, metadata_reg_c_0,
			 mlx5_eचयन_get_vport_metadata_mask());

		spec->match_criteria_enable = MLX5_MATCH_MISC_PARAMETERS_2;
	पूर्ण अन्यथा अणु
		misc = MLX5_ADDR_OF(fte_match_param, spec->match_value,
				    misc_parameters);

		MLX5_SET(fte_match_set_misc, misc, source_eचयन_owner_vhca_id,
			 MLX5_CAP_GEN(peer_dev, vhca_id));

		spec->match_criteria_enable = MLX5_MATCH_MISC_PARAMETERS;

		misc = MLX5_ADDR_OF(fte_match_param, spec->match_criteria,
				    misc_parameters);
		MLX5_SET_TO_ONES(fte_match_set_misc, misc, source_port);
		MLX5_SET_TO_ONES(fte_match_set_misc, misc,
				 source_eचयन_owner_vhca_id);
	पूर्ण

	dest->type = MLX5_FLOW_DESTINATION_TYPE_VPORT;
	dest->vport.num = peer_dev->priv.eचयन->manager_vport;
	dest->vport.vhca_id = MLX5_CAP_GEN(peer_dev, vhca_id);
	dest->vport.flags |= MLX5_FLOW_DEST_VPORT_VHCA_ID;
पूर्ण

अटल व्योम esw_set_peer_miss_rule_source_port(काष्ठा mlx5_eचयन *esw,
					       काष्ठा mlx5_eचयन *peer_esw,
					       काष्ठा mlx5_flow_spec *spec,
					       u16 vport)
अणु
	व्योम *misc;

	अगर (mlx5_eचयन_vport_match_metadata_enabled(esw)) अणु
		misc = MLX5_ADDR_OF(fte_match_param, spec->match_value,
				    misc_parameters_2);
		MLX5_SET(fte_match_set_misc2, misc, metadata_reg_c_0,
			 mlx5_eचयन_get_vport_metadata_क्रम_match(peer_esw,
								   vport));
	पूर्ण अन्यथा अणु
		misc = MLX5_ADDR_OF(fte_match_param, spec->match_value,
				    misc_parameters);
		MLX5_SET(fte_match_set_misc, misc, source_port, vport);
	पूर्ण
पूर्ण

अटल पूर्णांक esw_add_fdb_peer_miss_rules(काष्ठा mlx5_eचयन *esw,
				       काष्ठा mlx5_core_dev *peer_dev)
अणु
	काष्ठा mlx5_flow_destination dest = अणुपूर्ण;
	काष्ठा mlx5_flow_act flow_act = अणु0पूर्ण;
	काष्ठा mlx5_flow_handle **flows;
	/* total vports is the same क्रम both e-चयनes */
	पूर्णांक nvports = esw->total_vports;
	काष्ठा mlx5_flow_handle *flow;
	काष्ठा mlx5_flow_spec *spec;
	काष्ठा mlx5_vport *vport;
	अचिन्हित दीर्घ i;
	व्योम *misc;
	पूर्णांक err;

	spec = kvzalloc(माप(*spec), GFP_KERNEL);
	अगर (!spec)
		वापस -ENOMEM;

	peer_miss_rules_setup(esw, peer_dev, spec, &dest);

	flows = kvzalloc(nvports * माप(*flows), GFP_KERNEL);
	अगर (!flows) अणु
		err = -ENOMEM;
		जाओ alloc_flows_err;
	पूर्ण

	flow_act.action = MLX5_FLOW_CONTEXT_ACTION_FWD_DEST;
	misc = MLX5_ADDR_OF(fte_match_param, spec->match_value,
			    misc_parameters);

	अगर (mlx5_core_is_ecpf_esw_manager(esw->dev)) अणु
		vport = mlx5_eचयन_get_vport(esw, MLX5_VPORT_PF);
		esw_set_peer_miss_rule_source_port(esw, peer_dev->priv.eचयन,
						   spec, MLX5_VPORT_PF);

		flow = mlx5_add_flow_rules(esw->fdb_table.offloads.slow_fdb,
					   spec, &flow_act, &dest, 1);
		अगर (IS_ERR(flow)) अणु
			err = PTR_ERR(flow);
			जाओ add_pf_flow_err;
		पूर्ण
		flows[vport->index] = flow;
	पूर्ण

	अगर (mlx5_ecpf_vport_exists(esw->dev)) अणु
		vport = mlx5_eचयन_get_vport(esw, MLX5_VPORT_ECPF);
		MLX5_SET(fte_match_set_misc, misc, source_port, MLX5_VPORT_ECPF);
		flow = mlx5_add_flow_rules(esw->fdb_table.offloads.slow_fdb,
					   spec, &flow_act, &dest, 1);
		अगर (IS_ERR(flow)) अणु
			err = PTR_ERR(flow);
			जाओ add_ecpf_flow_err;
		पूर्ण
		flows[vport->index] = flow;
	पूर्ण

	mlx5_esw_क्रम_each_vf_vport(esw, i, vport, mlx5_core_max_vfs(esw->dev)) अणु
		esw_set_peer_miss_rule_source_port(esw,
						   peer_dev->priv.eचयन,
						   spec, vport->vport);

		flow = mlx5_add_flow_rules(esw->fdb_table.offloads.slow_fdb,
					   spec, &flow_act, &dest, 1);
		अगर (IS_ERR(flow)) अणु
			err = PTR_ERR(flow);
			जाओ add_vf_flow_err;
		पूर्ण
		flows[vport->index] = flow;
	पूर्ण

	esw->fdb_table.offloads.peer_miss_rules = flows;

	kvमुक्त(spec);
	वापस 0;

add_vf_flow_err:
	mlx5_esw_क्रम_each_vf_vport(esw, i, vport, mlx5_core_max_vfs(esw->dev)) अणु
		अगर (!flows[vport->index])
			जारी;
		mlx5_del_flow_rules(flows[vport->index]);
	पूर्ण
	अगर (mlx5_ecpf_vport_exists(esw->dev)) अणु
		vport = mlx5_eचयन_get_vport(esw, MLX5_VPORT_ECPF);
		mlx5_del_flow_rules(flows[vport->index]);
	पूर्ण
add_ecpf_flow_err:
	अगर (mlx5_core_is_ecpf_esw_manager(esw->dev)) अणु
		vport = mlx5_eचयन_get_vport(esw, MLX5_VPORT_PF);
		mlx5_del_flow_rules(flows[vport->index]);
	पूर्ण
add_pf_flow_err:
	esw_warn(esw->dev, "FDB: Failed to add peer miss flow rule err %d\n", err);
	kvमुक्त(flows);
alloc_flows_err:
	kvमुक्त(spec);
	वापस err;
पूर्ण

अटल व्योम esw_del_fdb_peer_miss_rules(काष्ठा mlx5_eचयन *esw)
अणु
	काष्ठा mlx5_flow_handle **flows;
	काष्ठा mlx5_vport *vport;
	अचिन्हित दीर्घ i;

	flows = esw->fdb_table.offloads.peer_miss_rules;

	mlx5_esw_क्रम_each_vf_vport(esw, i, vport, mlx5_core_max_vfs(esw->dev))
		mlx5_del_flow_rules(flows[vport->index]);

	अगर (mlx5_ecpf_vport_exists(esw->dev)) अणु
		vport = mlx5_eचयन_get_vport(esw, MLX5_VPORT_ECPF);
		mlx5_del_flow_rules(flows[vport->index]);
	पूर्ण

	अगर (mlx5_core_is_ecpf_esw_manager(esw->dev)) अणु
		vport = mlx5_eचयन_get_vport(esw, MLX5_VPORT_PF);
		mlx5_del_flow_rules(flows[vport->index]);
	पूर्ण
	kvमुक्त(flows);
पूर्ण

अटल पूर्णांक esw_add_fdb_miss_rule(काष्ठा mlx5_eचयन *esw)
अणु
	काष्ठा mlx5_flow_act flow_act = अणु0पूर्ण;
	काष्ठा mlx5_flow_destination dest = अणुपूर्ण;
	काष्ठा mlx5_flow_handle *flow_rule = शून्य;
	काष्ठा mlx5_flow_spec *spec;
	व्योम *headers_c;
	व्योम *headers_v;
	पूर्णांक err = 0;
	u8 *dmac_c;
	u8 *dmac_v;

	spec = kvzalloc(माप(*spec), GFP_KERNEL);
	अगर (!spec) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	spec->match_criteria_enable = MLX5_MATCH_OUTER_HEADERS;
	headers_c = MLX5_ADDR_OF(fte_match_param, spec->match_criteria,
				 outer_headers);
	dmac_c = MLX5_ADDR_OF(fte_match_param, headers_c,
			      outer_headers.dmac_47_16);
	dmac_c[0] = 0x01;

	dest.type = MLX5_FLOW_DESTINATION_TYPE_VPORT;
	dest.vport.num = esw->manager_vport;
	flow_act.action = MLX5_FLOW_CONTEXT_ACTION_FWD_DEST;

	flow_rule = mlx5_add_flow_rules(esw->fdb_table.offloads.slow_fdb,
					spec, &flow_act, &dest, 1);
	अगर (IS_ERR(flow_rule)) अणु
		err = PTR_ERR(flow_rule);
		esw_warn(esw->dev,  "FDB: Failed to add unicast miss flow rule err %d\n", err);
		जाओ out;
	पूर्ण

	esw->fdb_table.offloads.miss_rule_uni = flow_rule;

	headers_v = MLX5_ADDR_OF(fte_match_param, spec->match_value,
				 outer_headers);
	dmac_v = MLX5_ADDR_OF(fte_match_param, headers_v,
			      outer_headers.dmac_47_16);
	dmac_v[0] = 0x01;
	flow_rule = mlx5_add_flow_rules(esw->fdb_table.offloads.slow_fdb,
					spec, &flow_act, &dest, 1);
	अगर (IS_ERR(flow_rule)) अणु
		err = PTR_ERR(flow_rule);
		esw_warn(esw->dev, "FDB: Failed to add multicast miss flow rule err %d\n", err);
		mlx5_del_flow_rules(esw->fdb_table.offloads.miss_rule_uni);
		जाओ out;
	पूर्ण

	esw->fdb_table.offloads.miss_rule_multi = flow_rule;

out:
	kvमुक्त(spec);
	वापस err;
पूर्ण

काष्ठा mlx5_flow_handle *
esw_add_restore_rule(काष्ठा mlx5_eचयन *esw, u32 tag)
अणु
	काष्ठा mlx5_flow_act flow_act = अणु .flags = FLOW_ACT_NO_APPEND, पूर्ण;
	काष्ठा mlx5_flow_table *ft = esw->offloads.ft_offloads_restore;
	काष्ठा mlx5_flow_context *flow_context;
	काष्ठा mlx5_flow_handle *flow_rule;
	काष्ठा mlx5_flow_destination dest;
	काष्ठा mlx5_flow_spec *spec;
	व्योम *misc;

	अगर (!mlx5_eचयन_reg_c1_loopback_supported(esw))
		वापस ERR_PTR(-EOPNOTSUPP);

	spec = kvzalloc(माप(*spec), GFP_KERNEL);
	अगर (!spec)
		वापस ERR_PTR(-ENOMEM);

	misc = MLX5_ADDR_OF(fte_match_param, spec->match_criteria,
			    misc_parameters_2);
	MLX5_SET(fte_match_set_misc2, misc, metadata_reg_c_0,
		 ESW_REG_C0_USER_DATA_METADATA_MASK);
	misc = MLX5_ADDR_OF(fte_match_param, spec->match_value,
			    misc_parameters_2);
	MLX5_SET(fte_match_set_misc2, misc, metadata_reg_c_0, tag);
	spec->match_criteria_enable = MLX5_MATCH_MISC_PARAMETERS_2;
	flow_act.action = MLX5_FLOW_CONTEXT_ACTION_FWD_DEST |
			  MLX5_FLOW_CONTEXT_ACTION_MOD_HDR;
	flow_act.modअगरy_hdr = esw->offloads.restore_copy_hdr_id;

	flow_context = &spec->flow_context;
	flow_context->flags |= FLOW_CONTEXT_HAS_TAG;
	flow_context->flow_tag = tag;
	dest.type = MLX5_FLOW_DESTINATION_TYPE_FLOW_TABLE;
	dest.ft = esw->offloads.ft_offloads;

	flow_rule = mlx5_add_flow_rules(ft, spec, &flow_act, &dest, 1);
	kvमुक्त(spec);

	अगर (IS_ERR(flow_rule))
		esw_warn(esw->dev,
			 "Failed to create restore rule for tag: %d, err(%d)\n",
			 tag, (पूर्णांक)PTR_ERR(flow_rule));

	वापस flow_rule;
पूर्ण

#घोषणा MAX_PF_SQ 256
#घोषणा MAX_SQ_NVPORTS 32

अटल व्योम esw_set_flow_group_source_port(काष्ठा mlx5_eचयन *esw,
					   u32 *flow_group_in)
अणु
	व्योम *match_criteria = MLX5_ADDR_OF(create_flow_group_in,
					    flow_group_in,
					    match_criteria);

	अगर (mlx5_eचयन_vport_match_metadata_enabled(esw)) अणु
		MLX5_SET(create_flow_group_in, flow_group_in,
			 match_criteria_enable,
			 MLX5_MATCH_MISC_PARAMETERS_2);

		MLX5_SET(fte_match_param, match_criteria,
			 misc_parameters_2.metadata_reg_c_0,
			 mlx5_eचयन_get_vport_metadata_mask());
	पूर्ण अन्यथा अणु
		MLX5_SET(create_flow_group_in, flow_group_in,
			 match_criteria_enable,
			 MLX5_MATCH_MISC_PARAMETERS);

		MLX5_SET_TO_ONES(fte_match_param, match_criteria,
				 misc_parameters.source_port);
	पूर्ण
पूर्ण

#अगर IS_ENABLED(CONFIG_MLX5_CLS_ACT)
अटल व्योम esw_vport_tbl_put(काष्ठा mlx5_eचयन *esw)
अणु
	काष्ठा mlx5_vport_tbl_attr attr;
	काष्ठा mlx5_vport *vport;
	अचिन्हित दीर्घ i;

	attr.chain = 0;
	attr.prio = 1;
	mlx5_esw_क्रम_each_vport(esw, i, vport) अणु
		attr.vport = vport->vport;
		attr.vport_ns = &mlx5_esw_vport_tbl_mirror_ns;
		mlx5_esw_vporttbl_put(esw, &attr);
	पूर्ण
पूर्ण

अटल पूर्णांक esw_vport_tbl_get(काष्ठा mlx5_eचयन *esw)
अणु
	काष्ठा mlx5_vport_tbl_attr attr;
	काष्ठा mlx5_flow_table *fdb;
	काष्ठा mlx5_vport *vport;
	अचिन्हित दीर्घ i;

	attr.chain = 0;
	attr.prio = 1;
	mlx5_esw_क्रम_each_vport(esw, i, vport) अणु
		attr.vport = vport->vport;
		attr.vport_ns = &mlx5_esw_vport_tbl_mirror_ns;
		fdb = mlx5_esw_vporttbl_get(esw, &attr);
		अगर (IS_ERR(fdb))
			जाओ out;
	पूर्ण
	वापस 0;

out:
	esw_vport_tbl_put(esw);
	वापस PTR_ERR(fdb);
पूर्ण

#घोषणा fdb_modअगरy_header_fwd_to_table_supported(esw) \
	(MLX5_CAP_ESW_FLOWTABLE((esw)->dev, fdb_modअगरy_header_fwd_to_table))
अटल व्योम esw_init_chains_offload_flags(काष्ठा mlx5_eचयन *esw, u32 *flags)
अणु
	काष्ठा mlx5_core_dev *dev = esw->dev;

	अगर (MLX5_CAP_ESW_FLOWTABLE_FDB(dev, ignore_flow_level))
		*flags |= MLX5_CHAINS_IGNORE_FLOW_LEVEL_SUPPORTED;

	अगर (!MLX5_CAP_ESW_FLOWTABLE(dev, multi_fdb_encap) &&
	    esw->offloads.encap != DEVLINK_ESWITCH_ENCAP_MODE_NONE) अणु
		*flags &= ~MLX5_CHAINS_AND_PRIOS_SUPPORTED;
		esw_warn(dev, "Tc chains and priorities offload aren't supported, update firmware if needed\n");
	पूर्ण अन्यथा अगर (!mlx5_eचयन_reg_c1_loopback_enabled(esw)) अणु
		*flags &= ~MLX5_CHAINS_AND_PRIOS_SUPPORTED;
		esw_warn(dev, "Tc chains and priorities offload aren't supported\n");
	पूर्ण अन्यथा अगर (!fdb_modअगरy_header_fwd_to_table_supported(esw)) अणु
		/* Disabled when ttl workaround is needed, e.g
		 * when ESWITCH_IPV4_TTL_MODIFY_ENABLE = true in mlxconfig
		 */
		esw_warn(dev,
			 "Tc chains and priorities offload aren't supported, check firmware version, or mlxconfig settings\n");
		*flags &= ~MLX5_CHAINS_AND_PRIOS_SUPPORTED;
	पूर्ण अन्यथा अणु
		*flags |= MLX5_CHAINS_AND_PRIOS_SUPPORTED;
		esw_info(dev, "Supported tc chains and prios offload\n");
	पूर्ण

	अगर (esw->offloads.encap != DEVLINK_ESWITCH_ENCAP_MODE_NONE)
		*flags |= MLX5_CHAINS_FT_TUNNEL_SUPPORTED;
पूर्ण

अटल पूर्णांक
esw_chains_create(काष्ठा mlx5_eचयन *esw, काष्ठा mlx5_flow_table *miss_fdb)
अणु
	काष्ठा mlx5_core_dev *dev = esw->dev;
	काष्ठा mlx5_flow_table *nf_ft, *ft;
	काष्ठा mlx5_chains_attr attr = अणुपूर्ण;
	काष्ठा mlx5_fs_chains *chains;
	u32 fdb_max;
	पूर्णांक err;

	fdb_max = 1 << MLX5_CAP_ESW_FLOWTABLE_FDB(dev, log_max_ft_size);

	esw_init_chains_offload_flags(esw, &attr.flags);
	attr.ns = MLX5_FLOW_NAMESPACE_FDB;
	attr.max_ft_sz = fdb_max;
	attr.max_grp_num = esw->params.large_group_num;
	attr.शेष_ft = miss_fdb;
	attr.mapping = esw->offloads.reg_c0_obj_pool;

	chains = mlx5_chains_create(dev, &attr);
	अगर (IS_ERR(chains)) अणु
		err = PTR_ERR(chains);
		esw_warn(dev, "Failed to create fdb chains err(%d)\n", err);
		वापस err;
	पूर्ण

	esw->fdb_table.offloads.esw_chains_priv = chains;

	/* Create tc_end_ft which is the always created ft chain */
	nf_ft = mlx5_chains_get_table(chains, mlx5_chains_get_nf_ft_chain(chains),
				      1, 0);
	अगर (IS_ERR(nf_ft)) अणु
		err = PTR_ERR(nf_ft);
		जाओ nf_ft_err;
	पूर्ण

	/* Always खोलो the root क्रम fast path */
	ft = mlx5_chains_get_table(chains, 0, 1, 0);
	अगर (IS_ERR(ft)) अणु
		err = PTR_ERR(ft);
		जाओ level_0_err;
	पूर्ण

	/* Open level 1 क्रम split fdb rules now अगर prios isn't supported  */
	अगर (!mlx5_chains_prios_supported(chains)) अणु
		err = esw_vport_tbl_get(esw);
		अगर (err)
			जाओ level_1_err;
	पूर्ण

	mlx5_chains_set_end_ft(chains, nf_ft);

	वापस 0;

level_1_err:
	mlx5_chains_put_table(chains, 0, 1, 0);
level_0_err:
	mlx5_chains_put_table(chains, mlx5_chains_get_nf_ft_chain(chains), 1, 0);
nf_ft_err:
	mlx5_chains_destroy(chains);
	esw->fdb_table.offloads.esw_chains_priv = शून्य;

	वापस err;
पूर्ण

अटल व्योम
esw_chains_destroy(काष्ठा mlx5_eचयन *esw, काष्ठा mlx5_fs_chains *chains)
अणु
	अगर (!mlx5_chains_prios_supported(chains))
		esw_vport_tbl_put(esw);
	mlx5_chains_put_table(chains, 0, 1, 0);
	mlx5_chains_put_table(chains, mlx5_chains_get_nf_ft_chain(chains), 1, 0);
	mlx5_chains_destroy(chains);
पूर्ण

#अन्यथा /* CONFIG_MLX5_CLS_ACT */

अटल पूर्णांक
esw_chains_create(काष्ठा mlx5_eचयन *esw, काष्ठा mlx5_flow_table *miss_fdb)
अणु वापस 0; पूर्ण

अटल व्योम
esw_chains_destroy(काष्ठा mlx5_eचयन *esw, काष्ठा mlx5_fs_chains *chains)
अणुपूर्ण

#पूर्ण_अगर

अटल पूर्णांक esw_create_offloads_fdb_tables(काष्ठा mlx5_eचयन *esw)
अणु
	पूर्णांक inlen = MLX5_ST_SZ_BYTES(create_flow_group_in);
	काष्ठा mlx5_flow_table_attr ft_attr = अणुपूर्ण;
	पूर्णांक num_vfs, table_size, ix, err = 0;
	काष्ठा mlx5_core_dev *dev = esw->dev;
	काष्ठा mlx5_flow_namespace *root_ns;
	काष्ठा mlx5_flow_table *fdb = शून्य;
	u32 flags = 0, *flow_group_in;
	काष्ठा mlx5_flow_group *g;
	व्योम *match_criteria;
	u8 *dmac;

	esw_debug(esw->dev, "Create offloads FDB Tables\n");

	flow_group_in = kvzalloc(inlen, GFP_KERNEL);
	अगर (!flow_group_in)
		वापस -ENOMEM;

	root_ns = mlx5_get_flow_namespace(dev, MLX5_FLOW_NAMESPACE_FDB);
	अगर (!root_ns) अणु
		esw_warn(dev, "Failed to get FDB flow namespace\n");
		err = -EOPNOTSUPP;
		जाओ ns_err;
	पूर्ण
	esw->fdb_table.offloads.ns = root_ns;
	err = mlx5_flow_namespace_set_mode(root_ns,
					   esw->dev->priv.steering->mode);
	अगर (err) अणु
		esw_warn(dev, "Failed to set FDB namespace steering mode\n");
		जाओ ns_err;
	पूर्ण

	table_size = esw->total_vports * MAX_SQ_NVPORTS + MAX_PF_SQ +
		MLX5_ESW_MISS_FLOWS + esw->total_vports + esw->esw_funcs.num_vfs;

	/* create the slow path fdb with encap set, so further table instances
	 * can be created at run समय जबतक VFs are probed अगर the FW allows that.
	 */
	अगर (esw->offloads.encap != DEVLINK_ESWITCH_ENCAP_MODE_NONE)
		flags |= (MLX5_FLOW_TABLE_TUNNEL_EN_REFORMAT |
			  MLX5_FLOW_TABLE_TUNNEL_EN_DECAP);

	ft_attr.flags = flags;
	ft_attr.max_fte = table_size;
	ft_attr.prio = FDB_SLOW_PATH;

	fdb = mlx5_create_flow_table(root_ns, &ft_attr);
	अगर (IS_ERR(fdb)) अणु
		err = PTR_ERR(fdb);
		esw_warn(dev, "Failed to create slow path FDB Table err %d\n", err);
		जाओ slow_fdb_err;
	पूर्ण
	esw->fdb_table.offloads.slow_fdb = fdb;

	err = esw_chains_create(esw, fdb);
	अगर (err) अणु
		esw_warn(dev, "Failed to open fdb chains err(%d)\n", err);
		जाओ fdb_chains_err;
	पूर्ण

	/* create send-to-vport group */
	MLX5_SET(create_flow_group_in, flow_group_in, match_criteria_enable,
		 MLX5_MATCH_MISC_PARAMETERS);

	match_criteria = MLX5_ADDR_OF(create_flow_group_in, flow_group_in, match_criteria);

	MLX5_SET_TO_ONES(fte_match_param, match_criteria, misc_parameters.source_sqn);
	MLX5_SET_TO_ONES(fte_match_param, match_criteria, misc_parameters.source_port);
	अगर (MLX5_CAP_ESW(esw->dev, merged_eचयन)) अणु
		MLX5_SET_TO_ONES(fte_match_param, match_criteria,
				 misc_parameters.source_eचयन_owner_vhca_id);
		MLX5_SET(create_flow_group_in, flow_group_in,
			 source_eचयन_owner_vhca_id_valid, 1);
	पूर्ण

	ix = esw->total_vports * MAX_SQ_NVPORTS + MAX_PF_SQ;
	MLX5_SET(create_flow_group_in, flow_group_in, start_flow_index, 0);
	MLX5_SET(create_flow_group_in, flow_group_in, end_flow_index, ix - 1);

	g = mlx5_create_flow_group(fdb, flow_group_in);
	अगर (IS_ERR(g)) अणु
		err = PTR_ERR(g);
		esw_warn(dev, "Failed to create send-to-vport flow group err(%d)\n", err);
		जाओ send_vport_err;
	पूर्ण
	esw->fdb_table.offloads.send_to_vport_grp = g;

	अगर (esw_src_port_reग_लिखो_supported(esw)) अणु
		/* meta send to vport */
		स_रखो(flow_group_in, 0, inlen);
		MLX5_SET(create_flow_group_in, flow_group_in, match_criteria_enable,
			 MLX5_MATCH_MISC_PARAMETERS_2);

		match_criteria = MLX5_ADDR_OF(create_flow_group_in, flow_group_in, match_criteria);

		MLX5_SET(fte_match_param, match_criteria,
			 misc_parameters_2.metadata_reg_c_0,
			 mlx5_eचयन_get_vport_metadata_mask());
		MLX5_SET(fte_match_param, match_criteria,
			 misc_parameters_2.metadata_reg_c_1, ESW_TUN_MASK);

		num_vfs = esw->esw_funcs.num_vfs;
		अगर (num_vfs) अणु
			MLX5_SET(create_flow_group_in, flow_group_in, start_flow_index, ix);
			MLX5_SET(create_flow_group_in, flow_group_in,
				 end_flow_index, ix + num_vfs - 1);
			ix += num_vfs;

			g = mlx5_create_flow_group(fdb, flow_group_in);
			अगर (IS_ERR(g)) अणु
				err = PTR_ERR(g);
				esw_warn(dev, "Failed to create send-to-vport meta flow group err(%d)\n",
					 err);
				जाओ send_vport_meta_err;
			पूर्ण
			esw->fdb_table.offloads.send_to_vport_meta_grp = g;

			err = mlx5_eचयन_add_send_to_vport_meta_rules(esw);
			अगर (err)
				जाओ meta_rule_err;
		पूर्ण
	पूर्ण

	अगर (MLX5_CAP_ESW(esw->dev, merged_eचयन)) अणु
		/* create peer esw miss group */
		स_रखो(flow_group_in, 0, inlen);

		esw_set_flow_group_source_port(esw, flow_group_in);

		अगर (!mlx5_eचयन_vport_match_metadata_enabled(esw)) अणु
			match_criteria = MLX5_ADDR_OF(create_flow_group_in,
						      flow_group_in,
						      match_criteria);

			MLX5_SET_TO_ONES(fte_match_param, match_criteria,
					 misc_parameters.source_eचयन_owner_vhca_id);

			MLX5_SET(create_flow_group_in, flow_group_in,
				 source_eचयन_owner_vhca_id_valid, 1);
		पूर्ण

		MLX5_SET(create_flow_group_in, flow_group_in, start_flow_index, ix);
		MLX5_SET(create_flow_group_in, flow_group_in, end_flow_index,
			 ix + esw->total_vports - 1);
		ix += esw->total_vports;

		g = mlx5_create_flow_group(fdb, flow_group_in);
		अगर (IS_ERR(g)) अणु
			err = PTR_ERR(g);
			esw_warn(dev, "Failed to create peer miss flow group err(%d)\n", err);
			जाओ peer_miss_err;
		पूर्ण
		esw->fdb_table.offloads.peer_miss_grp = g;
	पूर्ण

	/* create miss group */
	स_रखो(flow_group_in, 0, inlen);
	MLX5_SET(create_flow_group_in, flow_group_in, match_criteria_enable,
		 MLX5_MATCH_OUTER_HEADERS);
	match_criteria = MLX5_ADDR_OF(create_flow_group_in, flow_group_in,
				      match_criteria);
	dmac = MLX5_ADDR_OF(fte_match_param, match_criteria,
			    outer_headers.dmac_47_16);
	dmac[0] = 0x01;

	MLX5_SET(create_flow_group_in, flow_group_in, start_flow_index, ix);
	MLX5_SET(create_flow_group_in, flow_group_in, end_flow_index,
		 ix + MLX5_ESW_MISS_FLOWS);

	g = mlx5_create_flow_group(fdb, flow_group_in);
	अगर (IS_ERR(g)) अणु
		err = PTR_ERR(g);
		esw_warn(dev, "Failed to create miss flow group err(%d)\n", err);
		जाओ miss_err;
	पूर्ण
	esw->fdb_table.offloads.miss_grp = g;

	err = esw_add_fdb_miss_rule(esw);
	अगर (err)
		जाओ miss_rule_err;

	kvमुक्त(flow_group_in);
	वापस 0;

miss_rule_err:
	mlx5_destroy_flow_group(esw->fdb_table.offloads.miss_grp);
miss_err:
	अगर (MLX5_CAP_ESW(esw->dev, merged_eचयन))
		mlx5_destroy_flow_group(esw->fdb_table.offloads.peer_miss_grp);
peer_miss_err:
	mlx5_eचयन_del_send_to_vport_meta_rules(esw);
meta_rule_err:
	अगर (esw->fdb_table.offloads.send_to_vport_meta_grp)
		mlx5_destroy_flow_group(esw->fdb_table.offloads.send_to_vport_meta_grp);
send_vport_meta_err:
	mlx5_destroy_flow_group(esw->fdb_table.offloads.send_to_vport_grp);
send_vport_err:
	esw_chains_destroy(esw, esw_chains(esw));
fdb_chains_err:
	mlx5_destroy_flow_table(esw->fdb_table.offloads.slow_fdb);
slow_fdb_err:
	/* Holds true only as दीर्घ as DMFS is the शेष */
	mlx5_flow_namespace_set_mode(root_ns, MLX5_FLOW_STEERING_MODE_DMFS);
ns_err:
	kvमुक्त(flow_group_in);
	वापस err;
पूर्ण

अटल व्योम esw_destroy_offloads_fdb_tables(काष्ठा mlx5_eचयन *esw)
अणु
	अगर (!esw->fdb_table.offloads.slow_fdb)
		वापस;

	esw_debug(esw->dev, "Destroy offloads FDB Tables\n");
	mlx5_del_flow_rules(esw->fdb_table.offloads.miss_rule_multi);
	mlx5_del_flow_rules(esw->fdb_table.offloads.miss_rule_uni);
	mlx5_eचयन_del_send_to_vport_meta_rules(esw);
	mlx5_destroy_flow_group(esw->fdb_table.offloads.send_to_vport_grp);
	अगर (esw->fdb_table.offloads.send_to_vport_meta_grp)
		mlx5_destroy_flow_group(esw->fdb_table.offloads.send_to_vport_meta_grp);
	अगर (MLX5_CAP_ESW(esw->dev, merged_eचयन))
		mlx5_destroy_flow_group(esw->fdb_table.offloads.peer_miss_grp);
	mlx5_destroy_flow_group(esw->fdb_table.offloads.miss_grp);

	esw_chains_destroy(esw, esw_chains(esw));

	mlx5_destroy_flow_table(esw->fdb_table.offloads.slow_fdb);
	/* Holds true only as दीर्घ as DMFS is the शेष */
	mlx5_flow_namespace_set_mode(esw->fdb_table.offloads.ns,
				     MLX5_FLOW_STEERING_MODE_DMFS);
	atomic64_set(&esw->user_count, 0);
पूर्ण

अटल पूर्णांक esw_create_offloads_table(काष्ठा mlx5_eचयन *esw)
अणु
	काष्ठा mlx5_flow_table_attr ft_attr = अणुपूर्ण;
	काष्ठा mlx5_core_dev *dev = esw->dev;
	काष्ठा mlx5_flow_table *ft_offloads;
	काष्ठा mlx5_flow_namespace *ns;
	पूर्णांक err = 0;

	ns = mlx5_get_flow_namespace(dev, MLX5_FLOW_NAMESPACE_OFFLOADS);
	अगर (!ns) अणु
		esw_warn(esw->dev, "Failed to get offloads flow namespace\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	ft_attr.max_fte = esw->total_vports + MLX5_ESW_MISS_FLOWS;
	ft_attr.prio = 1;

	ft_offloads = mlx5_create_flow_table(ns, &ft_attr);
	अगर (IS_ERR(ft_offloads)) अणु
		err = PTR_ERR(ft_offloads);
		esw_warn(esw->dev, "Failed to create offloads table, err %d\n", err);
		वापस err;
	पूर्ण

	esw->offloads.ft_offloads = ft_offloads;
	वापस 0;
पूर्ण

अटल व्योम esw_destroy_offloads_table(काष्ठा mlx5_eचयन *esw)
अणु
	काष्ठा mlx5_esw_offload *offloads = &esw->offloads;

	mlx5_destroy_flow_table(offloads->ft_offloads);
पूर्ण

अटल पूर्णांक esw_create_vport_rx_group(काष्ठा mlx5_eचयन *esw)
अणु
	पूर्णांक inlen = MLX5_ST_SZ_BYTES(create_flow_group_in);
	काष्ठा mlx5_flow_group *g;
	u32 *flow_group_in;
	पूर्णांक nvports;
	पूर्णांक err = 0;

	nvports = esw->total_vports + MLX5_ESW_MISS_FLOWS;
	flow_group_in = kvzalloc(inlen, GFP_KERNEL);
	अगर (!flow_group_in)
		वापस -ENOMEM;

	/* create vport rx group */
	esw_set_flow_group_source_port(esw, flow_group_in);

	MLX5_SET(create_flow_group_in, flow_group_in, start_flow_index, 0);
	MLX5_SET(create_flow_group_in, flow_group_in, end_flow_index, nvports - 1);

	g = mlx5_create_flow_group(esw->offloads.ft_offloads, flow_group_in);

	अगर (IS_ERR(g)) अणु
		err = PTR_ERR(g);
		mlx5_core_warn(esw->dev, "Failed to create vport rx group err %d\n", err);
		जाओ out;
	पूर्ण

	esw->offloads.vport_rx_group = g;
out:
	kvमुक्त(flow_group_in);
	वापस err;
पूर्ण

अटल व्योम esw_destroy_vport_rx_group(काष्ठा mlx5_eचयन *esw)
अणु
	mlx5_destroy_flow_group(esw->offloads.vport_rx_group);
पूर्ण

काष्ठा mlx5_flow_handle *
mlx5_eचयन_create_vport_rx_rule(काष्ठा mlx5_eचयन *esw, u16 vport,
				  काष्ठा mlx5_flow_destination *dest)
अणु
	काष्ठा mlx5_flow_act flow_act = अणु0पूर्ण;
	काष्ठा mlx5_flow_handle *flow_rule;
	काष्ठा mlx5_flow_spec *spec;
	व्योम *misc;

	spec = kvzalloc(माप(*spec), GFP_KERNEL);
	अगर (!spec) अणु
		flow_rule = ERR_PTR(-ENOMEM);
		जाओ out;
	पूर्ण

	अगर (mlx5_eचयन_vport_match_metadata_enabled(esw)) अणु
		misc = MLX5_ADDR_OF(fte_match_param, spec->match_value, misc_parameters_2);
		MLX5_SET(fte_match_set_misc2, misc, metadata_reg_c_0,
			 mlx5_eचयन_get_vport_metadata_क्रम_match(esw, vport));

		misc = MLX5_ADDR_OF(fte_match_param, spec->match_criteria, misc_parameters_2);
		MLX5_SET(fte_match_set_misc2, misc, metadata_reg_c_0,
			 mlx5_eचयन_get_vport_metadata_mask());

		spec->match_criteria_enable = MLX5_MATCH_MISC_PARAMETERS_2;
	पूर्ण अन्यथा अणु
		misc = MLX5_ADDR_OF(fte_match_param, spec->match_value, misc_parameters);
		MLX5_SET(fte_match_set_misc, misc, source_port, vport);

		misc = MLX5_ADDR_OF(fte_match_param, spec->match_criteria, misc_parameters);
		MLX5_SET_TO_ONES(fte_match_set_misc, misc, source_port);

		spec->match_criteria_enable = MLX5_MATCH_MISC_PARAMETERS;
	पूर्ण

	flow_act.action = MLX5_FLOW_CONTEXT_ACTION_FWD_DEST;
	flow_rule = mlx5_add_flow_rules(esw->offloads.ft_offloads, spec,
					&flow_act, dest, 1);
	अगर (IS_ERR(flow_rule)) अणु
		esw_warn(esw->dev, "fs offloads: Failed to add vport rx rule err %ld\n", PTR_ERR(flow_rule));
		जाओ out;
	पूर्ण

out:
	kvमुक्त(spec);
	वापस flow_rule;
पूर्ण

अटल पूर्णांक mlx5_eचयन_अंतरभूत_mode_get(काष्ठा mlx5_eचयन *esw, u8 *mode)
अणु
	u8 prev_mlx5_mode, mlx5_mode = MLX5_INLINE_MODE_L2;
	काष्ठा mlx5_core_dev *dev = esw->dev;
	काष्ठा mlx5_vport *vport;
	अचिन्हित दीर्घ i;

	अगर (!MLX5_CAP_GEN(dev, vport_group_manager))
		वापस -EOPNOTSUPP;

	अगर (esw->mode == MLX5_ESWITCH_NONE)
		वापस -EOPNOTSUPP;

	चयन (MLX5_CAP_ETH(dev, wqe_अंतरभूत_mode)) अणु
	हाल MLX5_CAP_INLINE_MODE_NOT_REQUIRED:
		mlx5_mode = MLX5_INLINE_MODE_NONE;
		जाओ out;
	हाल MLX5_CAP_INLINE_MODE_L2:
		mlx5_mode = MLX5_INLINE_MODE_L2;
		जाओ out;
	हाल MLX5_CAP_INLINE_MODE_VPORT_CONTEXT:
		जाओ query_vports;
	पूर्ण

query_vports:
	mlx5_query_nic_vport_min_अंतरभूत(dev, esw->first_host_vport, &prev_mlx5_mode);
	mlx5_esw_क्रम_each_host_func_vport(esw, i, vport, esw->esw_funcs.num_vfs) अणु
		mlx5_query_nic_vport_min_अंतरभूत(dev, vport->vport, &mlx5_mode);
		अगर (prev_mlx5_mode != mlx5_mode)
			वापस -EINVAL;
		prev_mlx5_mode = mlx5_mode;
	पूर्ण

out:
	*mode = mlx5_mode;
	वापस 0;
पूर्ण

अटल व्योम esw_destroy_restore_table(काष्ठा mlx5_eचयन *esw)
अणु
	काष्ठा mlx5_esw_offload *offloads = &esw->offloads;

	अगर (!mlx5_eचयन_reg_c1_loopback_supported(esw))
		वापस;

	mlx5_modअगरy_header_dealloc(esw->dev, offloads->restore_copy_hdr_id);
	mlx5_destroy_flow_group(offloads->restore_group);
	mlx5_destroy_flow_table(offloads->ft_offloads_restore);
पूर्ण

अटल पूर्णांक esw_create_restore_table(काष्ठा mlx5_eचयन *esw)
अणु
	u8 modact[MLX5_UN_SZ_BYTES(set_add_copy_action_in_स्वतः)] = अणुपूर्ण;
	पूर्णांक inlen = MLX5_ST_SZ_BYTES(create_flow_group_in);
	काष्ठा mlx5_flow_table_attr ft_attr = अणुपूर्ण;
	काष्ठा mlx5_core_dev *dev = esw->dev;
	काष्ठा mlx5_flow_namespace *ns;
	काष्ठा mlx5_modअगरy_hdr *mod_hdr;
	व्योम *match_criteria, *misc;
	काष्ठा mlx5_flow_table *ft;
	काष्ठा mlx5_flow_group *g;
	u32 *flow_group_in;
	पूर्णांक err = 0;

	अगर (!mlx5_eचयन_reg_c1_loopback_supported(esw))
		वापस 0;

	ns = mlx5_get_flow_namespace(dev, MLX5_FLOW_NAMESPACE_OFFLOADS);
	अगर (!ns) अणु
		esw_warn(esw->dev, "Failed to get offloads flow namespace\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	flow_group_in = kvzalloc(inlen, GFP_KERNEL);
	अगर (!flow_group_in) अणु
		err = -ENOMEM;
		जाओ out_मुक्त;
	पूर्ण

	ft_attr.max_fte = 1 << ESW_REG_C0_USER_DATA_METADATA_BITS;
	ft = mlx5_create_flow_table(ns, &ft_attr);
	अगर (IS_ERR(ft)) अणु
		err = PTR_ERR(ft);
		esw_warn(esw->dev, "Failed to create restore table, err %d\n",
			 err);
		जाओ out_मुक्त;
	पूर्ण

	match_criteria = MLX5_ADDR_OF(create_flow_group_in, flow_group_in,
				      match_criteria);
	misc = MLX5_ADDR_OF(fte_match_param, match_criteria,
			    misc_parameters_2);

	MLX5_SET(fte_match_set_misc2, misc, metadata_reg_c_0,
		 ESW_REG_C0_USER_DATA_METADATA_MASK);
	MLX5_SET(create_flow_group_in, flow_group_in, start_flow_index, 0);
	MLX5_SET(create_flow_group_in, flow_group_in, end_flow_index,
		 ft_attr.max_fte - 1);
	MLX5_SET(create_flow_group_in, flow_group_in, match_criteria_enable,
		 MLX5_MATCH_MISC_PARAMETERS_2);
	g = mlx5_create_flow_group(ft, flow_group_in);
	अगर (IS_ERR(g)) अणु
		err = PTR_ERR(g);
		esw_warn(dev, "Failed to create restore flow group, err: %d\n",
			 err);
		जाओ err_group;
	पूर्ण

	MLX5_SET(copy_action_in, modact, action_type, MLX5_ACTION_TYPE_COPY);
	MLX5_SET(copy_action_in, modact, src_field,
		 MLX5_ACTION_IN_FIELD_METADATA_REG_C_1);
	MLX5_SET(copy_action_in, modact, dst_field,
		 MLX5_ACTION_IN_FIELD_METADATA_REG_B);
	mod_hdr = mlx5_modअगरy_header_alloc(esw->dev,
					   MLX5_FLOW_NAMESPACE_KERNEL, 1,
					   modact);
	अगर (IS_ERR(mod_hdr)) अणु
		err = PTR_ERR(mod_hdr);
		esw_warn(dev, "Failed to create restore mod header, err: %d\n",
			 err);
		जाओ err_mod_hdr;
	पूर्ण

	esw->offloads.ft_offloads_restore = ft;
	esw->offloads.restore_group = g;
	esw->offloads.restore_copy_hdr_id = mod_hdr;

	kvमुक्त(flow_group_in);

	वापस 0;

err_mod_hdr:
	mlx5_destroy_flow_group(g);
err_group:
	mlx5_destroy_flow_table(ft);
out_मुक्त:
	kvमुक्त(flow_group_in);

	वापस err;
पूर्ण

अटल पूर्णांक esw_offloads_start(काष्ठा mlx5_eचयन *esw,
			      काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक err, err1;

	mlx5_eचयन_disable_locked(esw, false);
	err = mlx5_eचयन_enable_locked(esw, MLX5_ESWITCH_OFFLOADS,
					 esw->dev->priv.sriov.num_vfs);
	अगर (err) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "Failed setting eswitch to offloads");
		err1 = mlx5_eचयन_enable_locked(esw, MLX5_ESWITCH_LEGACY,
						  MLX5_ESWITCH_IGNORE_NUM_VFS);
		अगर (err1) अणु
			NL_SET_ERR_MSG_MOD(extack,
					   "Failed setting eswitch back to legacy");
		पूर्ण
	पूर्ण
	अगर (esw->offloads.अंतरभूत_mode == MLX5_INLINE_MODE_NONE) अणु
		अगर (mlx5_eचयन_अंतरभूत_mode_get(esw,
						 &esw->offloads.अंतरभूत_mode)) अणु
			esw->offloads.अंतरभूत_mode = MLX5_INLINE_MODE_L2;
			NL_SET_ERR_MSG_MOD(extack,
					   "Inline mode is different between vports");
		पूर्ण
	पूर्ण
	वापस err;
पूर्ण

अटल व्योम mlx5_esw_offloads_rep_mark_set(काष्ठा mlx5_eचयन *esw,
					   काष्ठा mlx5_eचयन_rep *rep,
					   xa_mark_t mark)
अणु
	bool mark_set;

	/* Copy the mark from vport to its rep */
	mark_set = xa_get_mark(&esw->vports, rep->vport, mark);
	अगर (mark_set)
		xa_set_mark(&esw->offloads.vport_reps, rep->vport, mark);
पूर्ण

अटल पूर्णांक mlx5_esw_offloads_rep_init(काष्ठा mlx5_eचयन *esw, स्थिर काष्ठा mlx5_vport *vport)
अणु
	काष्ठा mlx5_eचयन_rep *rep;
	पूर्णांक rep_type;
	पूर्णांक err;

	rep = kzalloc(माप(*rep), GFP_KERNEL);
	अगर (!rep)
		वापस -ENOMEM;

	rep->vport = vport->vport;
	rep->vport_index = vport->index;
	क्रम (rep_type = 0; rep_type < NUM_REP_TYPES; rep_type++)
		atomic_set(&rep->rep_data[rep_type].state, REP_UNREGISTERED);

	err = xa_insert(&esw->offloads.vport_reps, rep->vport, rep, GFP_KERNEL);
	अगर (err)
		जाओ insert_err;

	mlx5_esw_offloads_rep_mark_set(esw, rep, MLX5_ESW_VPT_HOST_FN);
	mlx5_esw_offloads_rep_mark_set(esw, rep, MLX5_ESW_VPT_VF);
	mlx5_esw_offloads_rep_mark_set(esw, rep, MLX5_ESW_VPT_SF);
	वापस 0;

insert_err:
	kमुक्त(rep);
	वापस err;
पूर्ण

अटल व्योम mlx5_esw_offloads_rep_cleanup(काष्ठा mlx5_eचयन *esw,
					  काष्ठा mlx5_eचयन_rep *rep)
अणु
	xa_erase(&esw->offloads.vport_reps, rep->vport);
	kमुक्त(rep);
पूर्ण

व्योम esw_offloads_cleanup_reps(काष्ठा mlx5_eचयन *esw)
अणु
	काष्ठा mlx5_eचयन_rep *rep;
	अचिन्हित दीर्घ i;

	mlx5_esw_क्रम_each_rep(esw, i, rep)
		mlx5_esw_offloads_rep_cleanup(esw, rep);
	xa_destroy(&esw->offloads.vport_reps);
पूर्ण

पूर्णांक esw_offloads_init_reps(काष्ठा mlx5_eचयन *esw)
अणु
	काष्ठा mlx5_vport *vport;
	अचिन्हित दीर्घ i;
	पूर्णांक err;

	xa_init(&esw->offloads.vport_reps);

	mlx5_esw_क्रम_each_vport(esw, i, vport) अणु
		err = mlx5_esw_offloads_rep_init(esw, vport);
		अगर (err)
			जाओ err;
	पूर्ण
	वापस 0;

err:
	esw_offloads_cleanup_reps(esw);
	वापस err;
पूर्ण

अटल व्योम __esw_offloads_unload_rep(काष्ठा mlx5_eचयन *esw,
				      काष्ठा mlx5_eचयन_rep *rep, u8 rep_type)
अणु
	अगर (atomic_cmpxchg(&rep->rep_data[rep_type].state,
			   REP_LOADED, REP_REGISTERED) == REP_LOADED)
		esw->offloads.rep_ops[rep_type]->unload(rep);
पूर्ण

अटल व्योम __unload_reps_sf_vport(काष्ठा mlx5_eचयन *esw, u8 rep_type)
अणु
	काष्ठा mlx5_eचयन_rep *rep;
	अचिन्हित दीर्घ i;

	mlx5_esw_क्रम_each_sf_rep(esw, i, rep)
		__esw_offloads_unload_rep(esw, rep, rep_type);
पूर्ण

अटल व्योम __unload_reps_all_vport(काष्ठा mlx5_eचयन *esw, u8 rep_type)
अणु
	काष्ठा mlx5_eचयन_rep *rep;
	अचिन्हित दीर्घ i;

	__unload_reps_sf_vport(esw, rep_type);

	mlx5_esw_क्रम_each_vf_rep(esw, i, rep)
		__esw_offloads_unload_rep(esw, rep, rep_type);

	अगर (mlx5_ecpf_vport_exists(esw->dev)) अणु
		rep = mlx5_eचयन_get_rep(esw, MLX5_VPORT_ECPF);
		__esw_offloads_unload_rep(esw, rep, rep_type);
	पूर्ण

	अगर (mlx5_core_is_ecpf_esw_manager(esw->dev)) अणु
		rep = mlx5_eचयन_get_rep(esw, MLX5_VPORT_PF);
		__esw_offloads_unload_rep(esw, rep, rep_type);
	पूर्ण

	rep = mlx5_eचयन_get_rep(esw, MLX5_VPORT_UPLINK);
	__esw_offloads_unload_rep(esw, rep, rep_type);
पूर्ण

पूर्णांक mlx5_esw_offloads_rep_load(काष्ठा mlx5_eचयन *esw, u16 vport_num)
अणु
	काष्ठा mlx5_eचयन_rep *rep;
	पूर्णांक rep_type;
	पूर्णांक err;

	rep = mlx5_eचयन_get_rep(esw, vport_num);
	क्रम (rep_type = 0; rep_type < NUM_REP_TYPES; rep_type++)
		अगर (atomic_cmpxchg(&rep->rep_data[rep_type].state,
				   REP_REGISTERED, REP_LOADED) == REP_REGISTERED) अणु
			err = esw->offloads.rep_ops[rep_type]->load(esw->dev, rep);
			अगर (err)
				जाओ err_reps;
		पूर्ण

	वापस 0;

err_reps:
	atomic_set(&rep->rep_data[rep_type].state, REP_REGISTERED);
	क्रम (--rep_type; rep_type >= 0; rep_type--)
		__esw_offloads_unload_rep(esw, rep, rep_type);
	वापस err;
पूर्ण

व्योम mlx5_esw_offloads_rep_unload(काष्ठा mlx5_eचयन *esw, u16 vport_num)
अणु
	काष्ठा mlx5_eचयन_rep *rep;
	पूर्णांक rep_type;

	rep = mlx5_eचयन_get_rep(esw, vport_num);
	क्रम (rep_type = NUM_REP_TYPES - 1; rep_type >= 0; rep_type--)
		__esw_offloads_unload_rep(esw, rep, rep_type);
पूर्ण

पूर्णांक esw_offloads_load_rep(काष्ठा mlx5_eचयन *esw, u16 vport_num)
अणु
	पूर्णांक err;

	अगर (esw->mode != MLX5_ESWITCH_OFFLOADS)
		वापस 0;

	अगर (vport_num != MLX5_VPORT_UPLINK) अणु
		err = mlx5_esw_offloads_devlink_port_रेजिस्टर(esw, vport_num);
		अगर (err)
			वापस err;
	पूर्ण

	err = mlx5_esw_offloads_rep_load(esw, vport_num);
	अगर (err)
		जाओ load_err;
	वापस err;

load_err:
	अगर (vport_num != MLX5_VPORT_UPLINK)
		mlx5_esw_offloads_devlink_port_unरेजिस्टर(esw, vport_num);
	वापस err;
पूर्ण

व्योम esw_offloads_unload_rep(काष्ठा mlx5_eचयन *esw, u16 vport_num)
अणु
	अगर (esw->mode != MLX5_ESWITCH_OFFLOADS)
		वापस;

	mlx5_esw_offloads_rep_unload(esw, vport_num);

	अगर (vport_num != MLX5_VPORT_UPLINK)
		mlx5_esw_offloads_devlink_port_unरेजिस्टर(esw, vport_num);
पूर्ण

#घोषणा ESW_OFFLOADS_DEVCOM_PAIR	(0)
#घोषणा ESW_OFFLOADS_DEVCOM_UNPAIR	(1)

अटल पूर्णांक mlx5_esw_offloads_pair(काष्ठा mlx5_eचयन *esw,
				  काष्ठा mlx5_eचयन *peer_esw)
अणु

	वापस esw_add_fdb_peer_miss_rules(esw, peer_esw->dev);
पूर्ण

अटल व्योम mlx5_esw_offloads_unpair(काष्ठा mlx5_eचयन *esw)
अणु
#अगर IS_ENABLED(CONFIG_MLX5_CLS_ACT)
	mlx5e_tc_clean_fdb_peer_flows(esw);
#पूर्ण_अगर
	esw_del_fdb_peer_miss_rules(esw);
पूर्ण

अटल पूर्णांक mlx5_esw_offloads_set_ns_peer(काष्ठा mlx5_eचयन *esw,
					 काष्ठा mlx5_eचयन *peer_esw,
					 bool pair)
अणु
	काष्ठा mlx5_flow_root_namespace *peer_ns;
	काष्ठा mlx5_flow_root_namespace *ns;
	पूर्णांक err;

	peer_ns = peer_esw->dev->priv.steering->fdb_root_ns;
	ns = esw->dev->priv.steering->fdb_root_ns;

	अगर (pair) अणु
		err = mlx5_flow_namespace_set_peer(ns, peer_ns);
		अगर (err)
			वापस err;

		err = mlx5_flow_namespace_set_peer(peer_ns, ns);
		अगर (err) अणु
			mlx5_flow_namespace_set_peer(ns, शून्य);
			वापस err;
		पूर्ण
	पूर्ण अन्यथा अणु
		mlx5_flow_namespace_set_peer(ns, शून्य);
		mlx5_flow_namespace_set_peer(peer_ns, शून्य);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mlx5_esw_offloads_devcom_event(पूर्णांक event,
					  व्योम *my_data,
					  व्योम *event_data)
अणु
	काष्ठा mlx5_eचयन *esw = my_data;
	काष्ठा mlx5_devcom *devcom = esw->dev->priv.devcom;
	काष्ठा mlx5_eचयन *peer_esw = event_data;
	पूर्णांक err;

	चयन (event) अणु
	हाल ESW_OFFLOADS_DEVCOM_PAIR:
		अगर (mlx5_eचयन_vport_match_metadata_enabled(esw) !=
		    mlx5_eचयन_vport_match_metadata_enabled(peer_esw))
			अवरोध;

		err = mlx5_esw_offloads_set_ns_peer(esw, peer_esw, true);
		अगर (err)
			जाओ err_out;
		err = mlx5_esw_offloads_pair(esw, peer_esw);
		अगर (err)
			जाओ err_peer;

		err = mlx5_esw_offloads_pair(peer_esw, esw);
		अगर (err)
			जाओ err_pair;

		mlx5_devcom_set_paired(devcom, MLX5_DEVCOM_ESW_OFFLOADS, true);
		अवरोध;

	हाल ESW_OFFLOADS_DEVCOM_UNPAIR:
		अगर (!mlx5_devcom_is_paired(devcom, MLX5_DEVCOM_ESW_OFFLOADS))
			अवरोध;

		mlx5_devcom_set_paired(devcom, MLX5_DEVCOM_ESW_OFFLOADS, false);
		mlx5_esw_offloads_unpair(peer_esw);
		mlx5_esw_offloads_unpair(esw);
		mlx5_esw_offloads_set_ns_peer(esw, peer_esw, false);
		अवरोध;
	पूर्ण

	वापस 0;

err_pair:
	mlx5_esw_offloads_unpair(esw);
err_peer:
	mlx5_esw_offloads_set_ns_peer(esw, peer_esw, false);
err_out:
	mlx5_core_err(esw->dev, "esw offloads devcom event failure, event %u err %d",
		      event, err);
	वापस err;
पूर्ण

अटल व्योम esw_offloads_devcom_init(काष्ठा mlx5_eचयन *esw)
अणु
	काष्ठा mlx5_devcom *devcom = esw->dev->priv.devcom;

	INIT_LIST_HEAD(&esw->offloads.peer_flows);
	mutex_init(&esw->offloads.peer_mutex);

	अगर (!MLX5_CAP_ESW(esw->dev, merged_eचयन))
		वापस;

	mlx5_devcom_रेजिस्टर_component(devcom,
				       MLX5_DEVCOM_ESW_OFFLOADS,
				       mlx5_esw_offloads_devcom_event,
				       esw);

	mlx5_devcom_send_event(devcom,
			       MLX5_DEVCOM_ESW_OFFLOADS,
			       ESW_OFFLOADS_DEVCOM_PAIR, esw);
पूर्ण

अटल व्योम esw_offloads_devcom_cleanup(काष्ठा mlx5_eचयन *esw)
अणु
	काष्ठा mlx5_devcom *devcom = esw->dev->priv.devcom;

	अगर (!MLX5_CAP_ESW(esw->dev, merged_eचयन))
		वापस;

	mlx5_devcom_send_event(devcom, MLX5_DEVCOM_ESW_OFFLOADS,
			       ESW_OFFLOADS_DEVCOM_UNPAIR, esw);

	mlx5_devcom_unरेजिस्टर_component(devcom, MLX5_DEVCOM_ESW_OFFLOADS);
पूर्ण

bool mlx5_esw_vport_match_metadata_supported(स्थिर काष्ठा mlx5_eचयन *esw)
अणु
	अगर (!MLX5_CAP_ESW(esw->dev, esw_uplink_ingress_acl))
		वापस false;

	अगर (!(MLX5_CAP_ESW_FLOWTABLE(esw->dev, fdb_to_vport_reg_c_id) &
	      MLX5_FDB_TO_VPORT_REG_C_0))
		वापस false;

	अगर (!MLX5_CAP_ESW_FLOWTABLE(esw->dev, flow_source))
		वापस false;

	अगर (mlx5_core_is_ecpf_esw_manager(esw->dev) ||
	    mlx5_ecpf_vport_exists(esw->dev))
		वापस false;

	वापस true;
पूर्ण

u32 mlx5_esw_match_metadata_alloc(काष्ठा mlx5_eचयन *esw)
अणु
	u32 vport_end_ida = (1 << ESW_VPORT_BITS) - 1;
	u32 max_pf_num = (1 << ESW_PFNUM_BITS) - 1;
	u32 pf_num;
	पूर्णांक id;

	/* Only 4 bits of pf_num */
	pf_num = PCI_FUNC(esw->dev->pdev->devfn);
	अगर (pf_num > max_pf_num)
		वापस 0;

	/* Metadata is 4 bits of PFNUM and 12 bits of unique id */
	/* Use only non-zero vport_id (1-4095) क्रम all PF's */
	id = ida_alloc_range(&esw->offloads.vport_metadata_ida, 1, vport_end_ida, GFP_KERNEL);
	अगर (id < 0)
		वापस 0;
	id = (pf_num << ESW_VPORT_BITS) | id;
	वापस id;
पूर्ण

व्योम mlx5_esw_match_metadata_मुक्त(काष्ठा mlx5_eचयन *esw, u32 metadata)
अणु
	u32 vport_bit_mask = (1 << ESW_VPORT_BITS) - 1;

	/* Metadata contains only 12 bits of actual ida id */
	ida_मुक्त(&esw->offloads.vport_metadata_ida, metadata & vport_bit_mask);
पूर्ण

अटल पूर्णांक esw_offloads_vport_metadata_setup(काष्ठा mlx5_eचयन *esw,
					     काष्ठा mlx5_vport *vport)
अणु
	vport->शेष_metadata = mlx5_esw_match_metadata_alloc(esw);
	vport->metadata = vport->शेष_metadata;
	वापस vport->metadata ? 0 : -ENOSPC;
पूर्ण

अटल व्योम esw_offloads_vport_metadata_cleanup(काष्ठा mlx5_eचयन *esw,
						काष्ठा mlx5_vport *vport)
अणु
	अगर (!vport->शेष_metadata)
		वापस;

	WARN_ON(vport->metadata != vport->शेष_metadata);
	mlx5_esw_match_metadata_मुक्त(esw, vport->शेष_metadata);
पूर्ण

अटल व्योम esw_offloads_metadata_uninit(काष्ठा mlx5_eचयन *esw)
अणु
	काष्ठा mlx5_vport *vport;
	अचिन्हित दीर्घ i;

	अगर (!mlx5_eचयन_vport_match_metadata_enabled(esw))
		वापस;

	mlx5_esw_क्रम_each_vport(esw, i, vport)
		esw_offloads_vport_metadata_cleanup(esw, vport);
पूर्ण

अटल पूर्णांक esw_offloads_metadata_init(काष्ठा mlx5_eचयन *esw)
अणु
	काष्ठा mlx5_vport *vport;
	अचिन्हित दीर्घ i;
	पूर्णांक err;

	अगर (!mlx5_eचयन_vport_match_metadata_enabled(esw))
		वापस 0;

	mlx5_esw_क्रम_each_vport(esw, i, vport) अणु
		err = esw_offloads_vport_metadata_setup(esw, vport);
		अगर (err)
			जाओ metadata_err;
	पूर्ण

	वापस 0;

metadata_err:
	esw_offloads_metadata_uninit(esw);
	वापस err;
पूर्ण

पूर्णांक mlx5_esw_offloads_vport_metadata_set(काष्ठा mlx5_eचयन *esw, bool enable)
अणु
	पूर्णांक err = 0;

	करोwn_ग_लिखो(&esw->mode_lock);
	अगर (esw->mode != MLX5_ESWITCH_NONE) अणु
		err = -EBUSY;
		जाओ करोne;
	पूर्ण
	अगर (!mlx5_esw_vport_match_metadata_supported(esw)) अणु
		err = -EOPNOTSUPP;
		जाओ करोne;
	पूर्ण
	अगर (enable)
		esw->flags |= MLX5_ESWITCH_VPORT_MATCH_METADATA;
	अन्यथा
		esw->flags &= ~MLX5_ESWITCH_VPORT_MATCH_METADATA;
करोne:
	up_ग_लिखो(&esw->mode_lock);
	वापस err;
पूर्ण

पूर्णांक
esw_vport_create_offloads_acl_tables(काष्ठा mlx5_eचयन *esw,
				     काष्ठा mlx5_vport *vport)
अणु
	पूर्णांक err;

	err = esw_acl_ingress_ofld_setup(esw, vport);
	अगर (err)
		वापस err;

	err = esw_acl_egress_ofld_setup(esw, vport);
	अगर (err)
		जाओ egress_err;

	वापस 0;

egress_err:
	esw_acl_ingress_ofld_cleanup(esw, vport);
	वापस err;
पूर्ण

व्योम
esw_vport_destroy_offloads_acl_tables(काष्ठा mlx5_eचयन *esw,
				      काष्ठा mlx5_vport *vport)
अणु
	esw_acl_egress_ofld_cleanup(vport);
	esw_acl_ingress_ofld_cleanup(esw, vport);
पूर्ण

अटल पूर्णांक esw_create_uplink_offloads_acl_tables(काष्ठा mlx5_eचयन *esw)
अणु
	काष्ठा mlx5_vport *vport;

	vport = mlx5_eचयन_get_vport(esw, MLX5_VPORT_UPLINK);
	अगर (IS_ERR(vport))
		वापस PTR_ERR(vport);

	वापस esw_vport_create_offloads_acl_tables(esw, vport);
पूर्ण

अटल व्योम esw_destroy_uplink_offloads_acl_tables(काष्ठा mlx5_eचयन *esw)
अणु
	काष्ठा mlx5_vport *vport;

	vport = mlx5_eचयन_get_vport(esw, MLX5_VPORT_UPLINK);
	अगर (IS_ERR(vport))
		वापस;

	esw_vport_destroy_offloads_acl_tables(esw, vport);
पूर्ण

अटल पूर्णांक esw_offloads_steering_init(काष्ठा mlx5_eचयन *esw)
अणु
	काष्ठा mlx5_esw_indir_table *indir;
	पूर्णांक err;

	स_रखो(&esw->fdb_table.offloads, 0, माप(काष्ठा offloads_fdb));
	mutex_init(&esw->fdb_table.offloads.vports.lock);
	hash_init(esw->fdb_table.offloads.vports.table);
	atomic64_set(&esw->user_count, 0);

	indir = mlx5_esw_indir_table_init();
	अगर (IS_ERR(indir)) अणु
		err = PTR_ERR(indir);
		जाओ create_indir_err;
	पूर्ण
	esw->fdb_table.offloads.indir = indir;

	err = esw_create_uplink_offloads_acl_tables(esw);
	अगर (err)
		जाओ create_acl_err;

	err = esw_create_offloads_table(esw);
	अगर (err)
		जाओ create_offloads_err;

	err = esw_create_restore_table(esw);
	अगर (err)
		जाओ create_restore_err;

	err = esw_create_offloads_fdb_tables(esw);
	अगर (err)
		जाओ create_fdb_err;

	err = esw_create_vport_rx_group(esw);
	अगर (err)
		जाओ create_fg_err;

	वापस 0;

create_fg_err:
	esw_destroy_offloads_fdb_tables(esw);
create_fdb_err:
	esw_destroy_restore_table(esw);
create_restore_err:
	esw_destroy_offloads_table(esw);
create_offloads_err:
	esw_destroy_uplink_offloads_acl_tables(esw);
create_acl_err:
	mlx5_esw_indir_table_destroy(esw->fdb_table.offloads.indir);
create_indir_err:
	mutex_destroy(&esw->fdb_table.offloads.vports.lock);
	वापस err;
पूर्ण

अटल व्योम esw_offloads_steering_cleanup(काष्ठा mlx5_eचयन *esw)
अणु
	esw_destroy_vport_rx_group(esw);
	esw_destroy_offloads_fdb_tables(esw);
	esw_destroy_restore_table(esw);
	esw_destroy_offloads_table(esw);
	esw_destroy_uplink_offloads_acl_tables(esw);
	mlx5_esw_indir_table_destroy(esw->fdb_table.offloads.indir);
	mutex_destroy(&esw->fdb_table.offloads.vports.lock);
पूर्ण

अटल व्योम
esw_vfs_changed_event_handler(काष्ठा mlx5_eचयन *esw, स्थिर u32 *out)
अणु
	bool host_pf_disabled;
	u16 new_num_vfs;

	new_num_vfs = MLX5_GET(query_esw_functions_out, out,
			       host_params_context.host_num_of_vfs);
	host_pf_disabled = MLX5_GET(query_esw_functions_out, out,
				    host_params_context.host_pf_disabled);

	अगर (new_num_vfs == esw->esw_funcs.num_vfs || host_pf_disabled)
		वापस;

	/* Number of VFs can only change from "0 to x" or "x to 0". */
	अगर (esw->esw_funcs.num_vfs > 0) अणु
		mlx5_eचयन_unload_vf_vports(esw, esw->esw_funcs.num_vfs);
	पूर्ण अन्यथा अणु
		पूर्णांक err;

		err = mlx5_eचयन_load_vf_vports(esw, new_num_vfs,
						  MLX5_VPORT_UC_ADDR_CHANGE);
		अगर (err)
			वापस;
	पूर्ण
	esw->esw_funcs.num_vfs = new_num_vfs;
पूर्ण

अटल व्योम esw_functions_changed_event_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mlx5_host_work *host_work;
	काष्ठा mlx5_eचयन *esw;
	स्थिर u32 *out;

	host_work = container_of(work, काष्ठा mlx5_host_work, work);
	esw = host_work->esw;

	out = mlx5_esw_query_functions(esw->dev);
	अगर (IS_ERR(out))
		जाओ out;

	esw_vfs_changed_event_handler(esw, out);
	kvमुक्त(out);
out:
	kमुक्त(host_work);
पूर्ण

पूर्णांक mlx5_esw_funcs_changed_handler(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ type, व्योम *data)
अणु
	काष्ठा mlx5_esw_functions *esw_funcs;
	काष्ठा mlx5_host_work *host_work;
	काष्ठा mlx5_eचयन *esw;

	host_work = kzalloc(माप(*host_work), GFP_ATOMIC);
	अगर (!host_work)
		वापस NOTIFY_DONE;

	esw_funcs = mlx5_nb_cof(nb, काष्ठा mlx5_esw_functions, nb);
	esw = container_of(esw_funcs, काष्ठा mlx5_eचयन, esw_funcs);

	host_work->esw = esw;

	INIT_WORK(&host_work->work, esw_functions_changed_event_handler);
	queue_work(esw->work_queue, &host_work->work);

	वापस NOTIFY_OK;
पूर्ण

अटल पूर्णांक mlx5_esw_host_number_init(काष्ठा mlx5_eचयन *esw)
अणु
	स्थिर u32 *query_host_out;

	अगर (!mlx5_core_is_ecpf_esw_manager(esw->dev))
		वापस 0;

	query_host_out = mlx5_esw_query_functions(esw->dev);
	अगर (IS_ERR(query_host_out))
		वापस PTR_ERR(query_host_out);

	/* Mark non local controller with non zero controller number. */
	esw->offloads.host_number = MLX5_GET(query_esw_functions_out, query_host_out,
					     host_params_context.host_number);
	kvमुक्त(query_host_out);
	वापस 0;
पूर्ण

bool mlx5_esw_offloads_controller_valid(स्थिर काष्ठा mlx5_eचयन *esw, u32 controller)
अणु
	/* Local controller is always valid */
	अगर (controller == 0)
		वापस true;

	अगर (!mlx5_core_is_ecpf_esw_manager(esw->dev))
		वापस false;

	/* External host number starts with zero in device */
	वापस (controller == esw->offloads.host_number + 1);
पूर्ण

पूर्णांक esw_offloads_enable(काष्ठा mlx5_eचयन *esw)
अणु
	काष्ठा mapping_ctx *reg_c0_obj_pool;
	काष्ठा mlx5_vport *vport;
	अचिन्हित दीर्घ i;
	पूर्णांक err;

	अगर (MLX5_CAP_ESW_FLOWTABLE_FDB(esw->dev, reक्रमmat) &&
	    MLX5_CAP_ESW_FLOWTABLE_FDB(esw->dev, decap))
		esw->offloads.encap = DEVLINK_ESWITCH_ENCAP_MODE_BASIC;
	अन्यथा
		esw->offloads.encap = DEVLINK_ESWITCH_ENCAP_MODE_NONE;

	mutex_init(&esw->offloads.termtbl_mutex);
	mlx5_rdma_enable_roce(esw->dev);

	err = mlx5_esw_host_number_init(esw);
	अगर (err)
		जाओ err_metadata;

	err = esw_offloads_metadata_init(esw);
	अगर (err)
		जाओ err_metadata;

	err = esw_set_passing_vport_metadata(esw, true);
	अगर (err)
		जाओ err_vport_metadata;

	reg_c0_obj_pool = mapping_create(माप(काष्ठा mlx5_mapped_obj),
					 ESW_REG_C0_USER_DATA_METADATA_MASK,
					 true);
	अगर (IS_ERR(reg_c0_obj_pool)) अणु
		err = PTR_ERR(reg_c0_obj_pool);
		जाओ err_pool;
	पूर्ण
	esw->offloads.reg_c0_obj_pool = reg_c0_obj_pool;

	err = esw_offloads_steering_init(esw);
	अगर (err)
		जाओ err_steering_init;

	/* Representor will control the vport link state */
	mlx5_esw_क्रम_each_vf_vport(esw, i, vport, esw->esw_funcs.num_vfs)
		vport->info.link_state = MLX5_VPORT_ADMIN_STATE_DOWN;

	/* Uplink vport rep must load first. */
	err = esw_offloads_load_rep(esw, MLX5_VPORT_UPLINK);
	अगर (err)
		जाओ err_uplink;

	err = mlx5_eचयन_enable_pf_vf_vports(esw, MLX5_VPORT_UC_ADDR_CHANGE);
	अगर (err)
		जाओ err_vports;

	esw_offloads_devcom_init(esw);

	वापस 0;

err_vports:
	esw_offloads_unload_rep(esw, MLX5_VPORT_UPLINK);
err_uplink:
	esw_offloads_steering_cleanup(esw);
err_steering_init:
	mapping_destroy(reg_c0_obj_pool);
err_pool:
	esw_set_passing_vport_metadata(esw, false);
err_vport_metadata:
	esw_offloads_metadata_uninit(esw);
err_metadata:
	mlx5_rdma_disable_roce(esw->dev);
	mutex_destroy(&esw->offloads.termtbl_mutex);
	वापस err;
पूर्ण

अटल पूर्णांक esw_offloads_stop(काष्ठा mlx5_eचयन *esw,
			     काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक err, err1;

	mlx5_eचयन_disable_locked(esw, false);
	err = mlx5_eचयन_enable_locked(esw, MLX5_ESWITCH_LEGACY,
					 MLX5_ESWITCH_IGNORE_NUM_VFS);
	अगर (err) अणु
		NL_SET_ERR_MSG_MOD(extack, "Failed setting eswitch to legacy");
		err1 = mlx5_eचयन_enable_locked(esw, MLX5_ESWITCH_OFFLOADS,
						  MLX5_ESWITCH_IGNORE_NUM_VFS);
		अगर (err1) अणु
			NL_SET_ERR_MSG_MOD(extack,
					   "Failed setting eswitch back to offloads");
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

व्योम esw_offloads_disable(काष्ठा mlx5_eचयन *esw)
अणु
	esw_offloads_devcom_cleanup(esw);
	mlx5_eचयन_disable_pf_vf_vports(esw);
	esw_offloads_unload_rep(esw, MLX5_VPORT_UPLINK);
	esw_set_passing_vport_metadata(esw, false);
	esw_offloads_steering_cleanup(esw);
	mapping_destroy(esw->offloads.reg_c0_obj_pool);
	esw_offloads_metadata_uninit(esw);
	mlx5_rdma_disable_roce(esw->dev);
	mutex_destroy(&esw->offloads.termtbl_mutex);
	esw->offloads.encap = DEVLINK_ESWITCH_ENCAP_MODE_NONE;
पूर्ण

अटल पूर्णांक esw_mode_from_devlink(u16 mode, u16 *mlx5_mode)
अणु
	चयन (mode) अणु
	हाल DEVLINK_ESWITCH_MODE_LEGACY:
		*mlx5_mode = MLX5_ESWITCH_LEGACY;
		अवरोध;
	हाल DEVLINK_ESWITCH_MODE_SWITCHDEV:
		*mlx5_mode = MLX5_ESWITCH_OFFLOADS;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक esw_mode_to_devlink(u16 mlx5_mode, u16 *mode)
अणु
	चयन (mlx5_mode) अणु
	हाल MLX5_ESWITCH_LEGACY:
		*mode = DEVLINK_ESWITCH_MODE_LEGACY;
		अवरोध;
	हाल MLX5_ESWITCH_OFFLOADS:
		*mode = DEVLINK_ESWITCH_MODE_SWITCHDEV;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक esw_अंतरभूत_mode_from_devlink(u8 mode, u8 *mlx5_mode)
अणु
	चयन (mode) अणु
	हाल DEVLINK_ESWITCH_INLINE_MODE_NONE:
		*mlx5_mode = MLX5_INLINE_MODE_NONE;
		अवरोध;
	हाल DEVLINK_ESWITCH_INLINE_MODE_LINK:
		*mlx5_mode = MLX5_INLINE_MODE_L2;
		अवरोध;
	हाल DEVLINK_ESWITCH_INLINE_MODE_NETWORK:
		*mlx5_mode = MLX5_INLINE_MODE_IP;
		अवरोध;
	हाल DEVLINK_ESWITCH_INLINE_MODE_TRANSPORT:
		*mlx5_mode = MLX5_INLINE_MODE_TCP_UDP;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक esw_अंतरभूत_mode_to_devlink(u8 mlx5_mode, u8 *mode)
अणु
	चयन (mlx5_mode) अणु
	हाल MLX5_INLINE_MODE_NONE:
		*mode = DEVLINK_ESWITCH_INLINE_MODE_NONE;
		अवरोध;
	हाल MLX5_INLINE_MODE_L2:
		*mode = DEVLINK_ESWITCH_INLINE_MODE_LINK;
		अवरोध;
	हाल MLX5_INLINE_MODE_IP:
		*mode = DEVLINK_ESWITCH_INLINE_MODE_NETWORK;
		अवरोध;
	हाल MLX5_INLINE_MODE_TCP_UDP:
		*mode = DEVLINK_ESWITCH_INLINE_MODE_TRANSPORT;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक eचयन_devlink_esw_mode_check(स्थिर काष्ठा mlx5_eचयन *esw)
अणु
	/* devlink commands in NONE eचयन mode are currently supported only
	 * on ECPF.
	 */
	वापस (esw->mode == MLX5_ESWITCH_NONE &&
		!mlx5_core_is_ecpf_esw_manager(esw->dev)) ? -EOPNOTSUPP : 0;
पूर्ण

पूर्णांक mlx5_devlink_eचयन_mode_set(काष्ठा devlink *devlink, u16 mode,
				  काष्ठा netlink_ext_ack *extack)
अणु
	u16 cur_mlx5_mode, mlx5_mode = 0;
	काष्ठा mlx5_eचयन *esw;
	पूर्णांक err = 0;

	esw = mlx5_devlink_eचयन_get(devlink);
	अगर (IS_ERR(esw))
		वापस PTR_ERR(esw);

	अगर (esw_mode_from_devlink(mode, &mlx5_mode))
		वापस -EINVAL;

	err = mlx5_esw_try_lock(esw);
	अगर (err < 0) अणु
		NL_SET_ERR_MSG_MOD(extack, "Can't change mode, E-Switch is busy");
		वापस err;
	पूर्ण
	cur_mlx5_mode = err;
	err = 0;

	अगर (cur_mlx5_mode == mlx5_mode)
		जाओ unlock;

	अगर (mode == DEVLINK_ESWITCH_MODE_SWITCHDEV)
		err = esw_offloads_start(esw, extack);
	अन्यथा अगर (mode == DEVLINK_ESWITCH_MODE_LEGACY)
		err = esw_offloads_stop(esw, extack);
	अन्यथा
		err = -EINVAL;

unlock:
	mlx5_esw_unlock(esw);
	वापस err;
पूर्ण

पूर्णांक mlx5_devlink_eचयन_mode_get(काष्ठा devlink *devlink, u16 *mode)
अणु
	काष्ठा mlx5_eचयन *esw;
	पूर्णांक err;

	esw = mlx5_devlink_eचयन_get(devlink);
	अगर (IS_ERR(esw))
		वापस PTR_ERR(esw);

	करोwn_ग_लिखो(&esw->mode_lock);
	err = eचयन_devlink_esw_mode_check(esw);
	अगर (err)
		जाओ unlock;

	err = esw_mode_to_devlink(esw->mode, mode);
unlock:
	up_ग_लिखो(&esw->mode_lock);
	वापस err;
पूर्ण

अटल पूर्णांक mlx5_esw_vports_अंतरभूत_set(काष्ठा mlx5_eचयन *esw, u8 mlx5_mode,
				      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlx5_core_dev *dev = esw->dev;
	काष्ठा mlx5_vport *vport;
	u16 err_vport_num = 0;
	अचिन्हित दीर्घ i;
	पूर्णांक err = 0;

	mlx5_esw_क्रम_each_host_func_vport(esw, i, vport, esw->esw_funcs.num_vfs) अणु
		err = mlx5_modअगरy_nic_vport_min_अंतरभूत(dev, vport->vport, mlx5_mode);
		अगर (err) अणु
			err_vport_num = vport->vport;
			NL_SET_ERR_MSG_MOD(extack,
					   "Failed to set min inline on vport");
			जाओ revert_अंतरभूत_mode;
		पूर्ण
	पूर्ण
	वापस 0;

revert_अंतरभूत_mode:
	mlx5_esw_क्रम_each_host_func_vport(esw, i, vport, esw->esw_funcs.num_vfs) अणु
		अगर (vport->vport == err_vport_num)
			अवरोध;
		mlx5_modअगरy_nic_vport_min_अंतरभूत(dev,
						 vport->vport,
						 esw->offloads.अंतरभूत_mode);
	पूर्ण
	वापस err;
पूर्ण

पूर्णांक mlx5_devlink_eचयन_अंतरभूत_mode_set(काष्ठा devlink *devlink, u8 mode,
					 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlx5_core_dev *dev = devlink_priv(devlink);
	काष्ठा mlx5_eचयन *esw;
	u8 mlx5_mode;
	पूर्णांक err;

	esw = mlx5_devlink_eचयन_get(devlink);
	अगर (IS_ERR(esw))
		वापस PTR_ERR(esw);

	करोwn_ग_लिखो(&esw->mode_lock);
	err = eचयन_devlink_esw_mode_check(esw);
	अगर (err)
		जाओ out;

	चयन (MLX5_CAP_ETH(dev, wqe_अंतरभूत_mode)) अणु
	हाल MLX5_CAP_INLINE_MODE_NOT_REQUIRED:
		अगर (mode == DEVLINK_ESWITCH_INLINE_MODE_NONE)
			जाओ out;
		fallthrough;
	हाल MLX5_CAP_INLINE_MODE_L2:
		NL_SET_ERR_MSG_MOD(extack, "Inline mode can't be set");
		err = -EOPNOTSUPP;
		जाओ out;
	हाल MLX5_CAP_INLINE_MODE_VPORT_CONTEXT:
		अवरोध;
	पूर्ण

	अगर (atomic64_पढ़ो(&esw->offloads.num_flows) > 0) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "Can't set inline mode when flows are configured");
		err = -EOPNOTSUPP;
		जाओ out;
	पूर्ण

	err = esw_अंतरभूत_mode_from_devlink(mode, &mlx5_mode);
	अगर (err)
		जाओ out;

	err = mlx5_esw_vports_अंतरभूत_set(esw, mlx5_mode, extack);
	अगर (err)
		जाओ out;

	esw->offloads.अंतरभूत_mode = mlx5_mode;
	up_ग_लिखो(&esw->mode_lock);
	वापस 0;

out:
	up_ग_लिखो(&esw->mode_lock);
	वापस err;
पूर्ण

पूर्णांक mlx5_devlink_eचयन_अंतरभूत_mode_get(काष्ठा devlink *devlink, u8 *mode)
अणु
	काष्ठा mlx5_eचयन *esw;
	पूर्णांक err;

	esw = mlx5_devlink_eचयन_get(devlink);
	अगर (IS_ERR(esw))
		वापस PTR_ERR(esw);

	करोwn_ग_लिखो(&esw->mode_lock);
	err = eचयन_devlink_esw_mode_check(esw);
	अगर (err)
		जाओ unlock;

	err = esw_अंतरभूत_mode_to_devlink(esw->offloads.अंतरभूत_mode, mode);
unlock:
	up_ग_लिखो(&esw->mode_lock);
	वापस err;
पूर्ण

पूर्णांक mlx5_devlink_eचयन_encap_mode_set(काष्ठा devlink *devlink,
					क्रमागत devlink_eचयन_encap_mode encap,
					काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlx5_core_dev *dev = devlink_priv(devlink);
	काष्ठा mlx5_eचयन *esw;
	पूर्णांक err;

	esw = mlx5_devlink_eचयन_get(devlink);
	अगर (IS_ERR(esw))
		वापस PTR_ERR(esw);

	करोwn_ग_लिखो(&esw->mode_lock);
	err = eचयन_devlink_esw_mode_check(esw);
	अगर (err)
		जाओ unlock;

	अगर (encap != DEVLINK_ESWITCH_ENCAP_MODE_NONE &&
	    (!MLX5_CAP_ESW_FLOWTABLE_FDB(dev, reक्रमmat) ||
	     !MLX5_CAP_ESW_FLOWTABLE_FDB(dev, decap))) अणु
		err = -EOPNOTSUPP;
		जाओ unlock;
	पूर्ण

	अगर (encap && encap != DEVLINK_ESWITCH_ENCAP_MODE_BASIC) अणु
		err = -EOPNOTSUPP;
		जाओ unlock;
	पूर्ण

	अगर (esw->mode == MLX5_ESWITCH_LEGACY) अणु
		esw->offloads.encap = encap;
		जाओ unlock;
	पूर्ण

	अगर (esw->offloads.encap == encap)
		जाओ unlock;

	अगर (atomic64_पढ़ो(&esw->offloads.num_flows) > 0) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "Can't set encapsulation when flows are configured");
		err = -EOPNOTSUPP;
		जाओ unlock;
	पूर्ण

	esw_destroy_offloads_fdb_tables(esw);

	esw->offloads.encap = encap;

	err = esw_create_offloads_fdb_tables(esw);

	अगर (err) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "Failed re-creating fast FDB table");
		esw->offloads.encap = !encap;
		(व्योम)esw_create_offloads_fdb_tables(esw);
	पूर्ण

unlock:
	up_ग_लिखो(&esw->mode_lock);
	वापस err;
पूर्ण

पूर्णांक mlx5_devlink_eचयन_encap_mode_get(काष्ठा devlink *devlink,
					क्रमागत devlink_eचयन_encap_mode *encap)
अणु
	काष्ठा mlx5_eचयन *esw;
	पूर्णांक err;

	esw = mlx5_devlink_eचयन_get(devlink);
	अगर (IS_ERR(esw))
		वापस PTR_ERR(esw);


	करोwn_ग_लिखो(&esw->mode_lock);
	err = eचयन_devlink_esw_mode_check(esw);
	अगर (err)
		जाओ unlock;

	*encap = esw->offloads.encap;
unlock:
	up_ग_लिखो(&esw->mode_lock);
	वापस 0;
पूर्ण

अटल bool
mlx5_eचयन_vport_has_rep(स्थिर काष्ठा mlx5_eचयन *esw, u16 vport_num)
अणु
	/* Currently, only ECPF based device has representor क्रम host PF. */
	अगर (vport_num == MLX5_VPORT_PF &&
	    !mlx5_core_is_ecpf_esw_manager(esw->dev))
		वापस false;

	अगर (vport_num == MLX5_VPORT_ECPF &&
	    !mlx5_ecpf_vport_exists(esw->dev))
		वापस false;

	वापस true;
पूर्ण

व्योम mlx5_eचयन_रेजिस्टर_vport_reps(काष्ठा mlx5_eचयन *esw,
				      स्थिर काष्ठा mlx5_eचयन_rep_ops *ops,
				      u8 rep_type)
अणु
	काष्ठा mlx5_eचयन_rep_data *rep_data;
	काष्ठा mlx5_eचयन_rep *rep;
	अचिन्हित दीर्घ i;

	esw->offloads.rep_ops[rep_type] = ops;
	mlx5_esw_क्रम_each_rep(esw, i, rep) अणु
		अगर (likely(mlx5_eचयन_vport_has_rep(esw, rep->vport))) अणु
			rep->esw = esw;
			rep_data = &rep->rep_data[rep_type];
			atomic_set(&rep_data->state, REP_REGISTERED);
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL(mlx5_eचयन_रेजिस्टर_vport_reps);

व्योम mlx5_eचयन_unरेजिस्टर_vport_reps(काष्ठा mlx5_eचयन *esw, u8 rep_type)
अणु
	काष्ठा mlx5_eचयन_rep *rep;
	अचिन्हित दीर्घ i;

	अगर (esw->mode == MLX5_ESWITCH_OFFLOADS)
		__unload_reps_all_vport(esw, rep_type);

	mlx5_esw_क्रम_each_rep(esw, i, rep)
		atomic_set(&rep->rep_data[rep_type].state, REP_UNREGISTERED);
पूर्ण
EXPORT_SYMBOL(mlx5_eचयन_unरेजिस्टर_vport_reps);

व्योम *mlx5_eचयन_get_uplink_priv(काष्ठा mlx5_eचयन *esw, u8 rep_type)
अणु
	काष्ठा mlx5_eचयन_rep *rep;

	rep = mlx5_eचयन_get_rep(esw, MLX5_VPORT_UPLINK);
	वापस rep->rep_data[rep_type].priv;
पूर्ण

व्योम *mlx5_eचयन_get_proto_dev(काष्ठा mlx5_eचयन *esw,
				 u16 vport,
				 u8 rep_type)
अणु
	काष्ठा mlx5_eचयन_rep *rep;

	rep = mlx5_eचयन_get_rep(esw, vport);

	अगर (atomic_पढ़ो(&rep->rep_data[rep_type].state) == REP_LOADED &&
	    esw->offloads.rep_ops[rep_type]->get_proto_dev)
		वापस esw->offloads.rep_ops[rep_type]->get_proto_dev(rep);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(mlx5_eचयन_get_proto_dev);

व्योम *mlx5_eचयन_uplink_get_proto_dev(काष्ठा mlx5_eचयन *esw, u8 rep_type)
अणु
	वापस mlx5_eचयन_get_proto_dev(esw, MLX5_VPORT_UPLINK, rep_type);
पूर्ण
EXPORT_SYMBOL(mlx5_eचयन_uplink_get_proto_dev);

काष्ठा mlx5_eचयन_rep *mlx5_eचयन_vport_rep(काष्ठा mlx5_eचयन *esw,
						u16 vport)
अणु
	वापस mlx5_eचयन_get_rep(esw, vport);
पूर्ण
EXPORT_SYMBOL(mlx5_eचयन_vport_rep);

bool mlx5_eचयन_reg_c1_loopback_enabled(स्थिर काष्ठा mlx5_eचयन *esw)
अणु
	वापस !!(esw->flags & MLX5_ESWITCH_REG_C1_LOOPBACK_ENABLED);
पूर्ण
EXPORT_SYMBOL(mlx5_eचयन_reg_c1_loopback_enabled);

bool mlx5_eचयन_vport_match_metadata_enabled(स्थिर काष्ठा mlx5_eचयन *esw)
अणु
	वापस !!(esw->flags & MLX5_ESWITCH_VPORT_MATCH_METADATA);
पूर्ण
EXPORT_SYMBOL(mlx5_eचयन_vport_match_metadata_enabled);

u32 mlx5_eचयन_get_vport_metadata_क्रम_match(काष्ठा mlx5_eचयन *esw,
					      u16 vport_num)
अणु
	काष्ठा mlx5_vport *vport = mlx5_eचयन_get_vport(esw, vport_num);

	अगर (WARN_ON_ONCE(IS_ERR(vport)))
		वापस 0;

	वापस vport->metadata << (32 - ESW_SOURCE_PORT_METADATA_BITS);
पूर्ण
EXPORT_SYMBOL(mlx5_eचयन_get_vport_metadata_क्रम_match);

पूर्णांक mlx5_esw_offloads_sf_vport_enable(काष्ठा mlx5_eचयन *esw, काष्ठा devlink_port *dl_port,
				      u16 vport_num, u32 controller, u32 sfnum)
अणु
	पूर्णांक err;

	err = mlx5_esw_vport_enable(esw, vport_num, MLX5_VPORT_UC_ADDR_CHANGE);
	अगर (err)
		वापस err;

	err = mlx5_esw_devlink_sf_port_रेजिस्टर(esw, dl_port, vport_num, controller, sfnum);
	अगर (err)
		जाओ devlink_err;

	err = mlx5_esw_offloads_rep_load(esw, vport_num);
	अगर (err)
		जाओ rep_err;
	वापस 0;

rep_err:
	mlx5_esw_devlink_sf_port_unरेजिस्टर(esw, vport_num);
devlink_err:
	mlx5_esw_vport_disable(esw, vport_num);
	वापस err;
पूर्ण

व्योम mlx5_esw_offloads_sf_vport_disable(काष्ठा mlx5_eचयन *esw, u16 vport_num)
अणु
	mlx5_esw_offloads_rep_unload(esw, vport_num);
	mlx5_esw_devlink_sf_port_unरेजिस्टर(esw, vport_num);
	mlx5_esw_vport_disable(esw, vport_num);
पूर्ण

अटल पूर्णांक mlx5_esw_query_vport_vhca_id(काष्ठा mlx5_eचयन *esw, u16 vport_num, u16 *vhca_id)
अणु
	पूर्णांक query_out_sz = MLX5_ST_SZ_BYTES(query_hca_cap_out);
	व्योम *query_ctx;
	व्योम *hca_caps;
	पूर्णांक err;

	*vhca_id = 0;
	अगर (mlx5_esw_is_manager_vport(esw, vport_num) ||
	    !MLX5_CAP_GEN(esw->dev, vhca_resource_manager))
		वापस -EPERM;

	query_ctx = kzalloc(query_out_sz, GFP_KERNEL);
	अगर (!query_ctx)
		वापस -ENOMEM;

	err = mlx5_vport_get_other_func_cap(esw->dev, vport_num, query_ctx);
	अगर (err)
		जाओ out_मुक्त;

	hca_caps = MLX5_ADDR_OF(query_hca_cap_out, query_ctx, capability);
	*vhca_id = MLX5_GET(cmd_hca_cap, hca_caps, vhca_id);

out_मुक्त:
	kमुक्त(query_ctx);
	वापस err;
पूर्ण

पूर्णांक mlx5_esw_vport_vhca_id_set(काष्ठा mlx5_eचयन *esw, u16 vport_num)
अणु
	u16 *old_entry, *vhca_map_entry, vhca_id;
	पूर्णांक err;

	err = mlx5_esw_query_vport_vhca_id(esw, vport_num, &vhca_id);
	अगर (err) अणु
		esw_warn(esw->dev, "Getting vhca_id for vport failed (vport=%u,err=%d)\n",
			 vport_num, err);
		वापस err;
	पूर्ण

	vhca_map_entry = kदो_स्मृति(माप(*vhca_map_entry), GFP_KERNEL);
	अगर (!vhca_map_entry)
		वापस -ENOMEM;

	*vhca_map_entry = vport_num;
	old_entry = xa_store(&esw->offloads.vhca_map, vhca_id, vhca_map_entry, GFP_KERNEL);
	अगर (xa_is_err(old_entry)) अणु
		kमुक्त(vhca_map_entry);
		वापस xa_err(old_entry);
	पूर्ण
	kमुक्त(old_entry);
	वापस 0;
पूर्ण

व्योम mlx5_esw_vport_vhca_id_clear(काष्ठा mlx5_eचयन *esw, u16 vport_num)
अणु
	u16 *vhca_map_entry, vhca_id;
	पूर्णांक err;

	err = mlx5_esw_query_vport_vhca_id(esw, vport_num, &vhca_id);
	अगर (err)
		esw_warn(esw->dev, "Getting vhca_id for vport failed (vport=%hu,err=%d)\n",
			 vport_num, err);

	vhca_map_entry = xa_erase(&esw->offloads.vhca_map, vhca_id);
	kमुक्त(vhca_map_entry);
पूर्ण

पूर्णांक mlx5_eचयन_vhca_id_to_vport(काष्ठा mlx5_eचयन *esw, u16 vhca_id, u16 *vport_num)
अणु
	u16 *res = xa_load(&esw->offloads.vhca_map, vhca_id);

	अगर (!res)
		वापस -ENOENT;

	*vport_num = *res;
	वापस 0;
पूर्ण

u32 mlx5_eचयन_get_vport_metadata_क्रम_set(काष्ठा mlx5_eचयन *esw,
					    u16 vport_num)
अणु
	काष्ठा mlx5_vport *vport = mlx5_eचयन_get_vport(esw, vport_num);

	अगर (WARN_ON_ONCE(IS_ERR(vport)))
		वापस 0;

	वापस vport->metadata;
पूर्ण
EXPORT_SYMBOL(mlx5_eचयन_get_vport_metadata_क्रम_set);
