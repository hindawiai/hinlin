<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/* Copyright (c) 2019 Mellanox Technologies. */

#समावेश <linux/types.h>
#समावेश "dr_types.h"

काष्ठा mlx5dr_fw_recalc_cs_ft *
mlx5dr_fw_create_recalc_cs_ft(काष्ठा mlx5dr_करोमुख्य *dmn, u32 vport_num)
अणु
	काष्ठा mlx5dr_cmd_create_flow_table_attr ft_attr = अणुपूर्ण;
	काष्ठा mlx5dr_fw_recalc_cs_ft *recalc_cs_ft;
	u32 table_id, group_id, modअगरy_hdr_id;
	u64 rx_icm_addr, modअगरy_ttl_action;
	पूर्णांक ret;

	recalc_cs_ft = kzalloc(माप(*recalc_cs_ft), GFP_KERNEL);
	अगर (!recalc_cs_ft)
		वापस शून्य;

	ft_attr.table_type = MLX5_FLOW_TABLE_TYPE_FDB;
	ft_attr.level = dmn->info.caps.max_ft_level - 1;
	ft_attr.term_tbl = true;

	ret = mlx5dr_cmd_create_flow_table(dmn->mdev,
					   &ft_attr,
					   &rx_icm_addr,
					   &table_id);
	अगर (ret) अणु
		mlx5dr_err(dmn, "Failed creating TTL W/A FW flow table %d\n", ret);
		जाओ मुक्त_ttl_tbl;
	पूर्ण

	ret = mlx5dr_cmd_create_empty_flow_group(dmn->mdev,
						 MLX5_FLOW_TABLE_TYPE_FDB,
						 table_id, &group_id);
	अगर (ret) अणु
		mlx5dr_err(dmn, "Failed creating TTL W/A FW flow group %d\n", ret);
		जाओ destroy_flow_table;
	पूर्ण

	/* Modअगरy TTL action by adding zero to trigger CS recalculation */
	modअगरy_ttl_action = 0;
	MLX5_SET(set_action_in, &modअगरy_ttl_action, action_type, MLX5_ACTION_TYPE_ADD);
	MLX5_SET(set_action_in, &modअगरy_ttl_action, field, MLX5_ACTION_IN_FIELD_OUT_IP_TTL);

	ret = mlx5dr_cmd_alloc_modअगरy_header(dmn->mdev, MLX5_FLOW_TABLE_TYPE_FDB, 1,
					     &modअगरy_ttl_action,
					     &modअगरy_hdr_id);
	अगर (ret) अणु
		mlx5dr_err(dmn, "Failed modify header TTL %d\n", ret);
		जाओ destroy_flow_group;
	पूर्ण

	ret = mlx5dr_cmd_set_fte_modअगरy_and_vport(dmn->mdev,
						  MLX5_FLOW_TABLE_TYPE_FDB,
						  table_id, group_id, modअगरy_hdr_id,
						  vport_num);
	अगर (ret) अणु
		mlx5dr_err(dmn, "Failed setting TTL W/A flow table entry %d\n", ret);
		जाओ dealloc_modअगरy_header;
	पूर्ण

	recalc_cs_ft->modअगरy_hdr_id = modअगरy_hdr_id;
	recalc_cs_ft->rx_icm_addr = rx_icm_addr;
	recalc_cs_ft->table_id = table_id;
	recalc_cs_ft->group_id = group_id;

	वापस recalc_cs_ft;

dealloc_modअगरy_header:
	mlx5dr_cmd_dealloc_modअगरy_header(dmn->mdev, modअगरy_hdr_id);
destroy_flow_group:
	mlx5dr_cmd_destroy_flow_group(dmn->mdev,
				      MLX5_FLOW_TABLE_TYPE_FDB,
				      table_id, group_id);
destroy_flow_table:
	mlx5dr_cmd_destroy_flow_table(dmn->mdev, table_id, MLX5_FLOW_TABLE_TYPE_FDB);
मुक्त_ttl_tbl:
	kमुक्त(recalc_cs_ft);
	वापस शून्य;
पूर्ण

व्योम mlx5dr_fw_destroy_recalc_cs_ft(काष्ठा mlx5dr_करोमुख्य *dmn,
				    काष्ठा mlx5dr_fw_recalc_cs_ft *recalc_cs_ft)
अणु
	mlx5dr_cmd_del_flow_table_entry(dmn->mdev,
					MLX5_FLOW_TABLE_TYPE_FDB,
					recalc_cs_ft->table_id);
	mlx5dr_cmd_dealloc_modअगरy_header(dmn->mdev, recalc_cs_ft->modअगरy_hdr_id);
	mlx5dr_cmd_destroy_flow_group(dmn->mdev,
				      MLX5_FLOW_TABLE_TYPE_FDB,
				      recalc_cs_ft->table_id,
				      recalc_cs_ft->group_id);
	mlx5dr_cmd_destroy_flow_table(dmn->mdev,
				      recalc_cs_ft->table_id,
				      MLX5_FLOW_TABLE_TYPE_FDB);

	kमुक्त(recalc_cs_ft);
पूर्ण

पूर्णांक mlx5dr_fw_create_md_tbl(काष्ठा mlx5dr_करोमुख्य *dmn,
			    काष्ठा mlx5dr_cmd_flow_destination_hw_info *dest,
			    पूर्णांक num_dest,
			    bool reक्रमmat_req,
			    u32 *tbl_id,
			    u32 *group_id)
अणु
	काष्ठा mlx5dr_cmd_create_flow_table_attr ft_attr = अणुपूर्ण;
	काष्ठा mlx5dr_cmd_fte_info fte_info = अणुपूर्ण;
	u32 val[MLX5_ST_SZ_DW_MATCH_PARAM] = अणुपूर्ण;
	काष्ठा mlx5dr_cmd_ft_info ft_info = अणुपूर्ण;
	पूर्णांक ret;

	ft_attr.table_type = MLX5_FLOW_TABLE_TYPE_FDB;
	ft_attr.level = min_t(पूर्णांक, dmn->info.caps.max_ft_level - 2,
			      MLX5_FT_MAX_MULTIPATH_LEVEL);
	ft_attr.reक्रमmat_en = reक्रमmat_req;
	ft_attr.decap_en = reक्रमmat_req;

	ret = mlx5dr_cmd_create_flow_table(dmn->mdev, &ft_attr, शून्य, tbl_id);
	अगर (ret) अणु
		mlx5dr_err(dmn, "Failed creating multi dest FW flow table %d\n", ret);
		वापस ret;
	पूर्ण

	ret = mlx5dr_cmd_create_empty_flow_group(dmn->mdev,
						 MLX5_FLOW_TABLE_TYPE_FDB,
						 *tbl_id, group_id);
	अगर (ret) अणु
		mlx5dr_err(dmn, "Failed creating multi dest FW flow group %d\n", ret);
		जाओ मुक्त_flow_table;
	पूर्ण

	ft_info.id = *tbl_id;
	ft_info.type = FS_FT_FDB;
	fte_info.action.action = MLX5_FLOW_CONTEXT_ACTION_FWD_DEST;
	fte_info.dests_size = num_dest;
	fte_info.val = val;
	fte_info.dest_arr = dest;

	ret = mlx5dr_cmd_set_fte(dmn->mdev, 0, 0, &ft_info, *group_id, &fte_info);
	अगर (ret) अणु
		mlx5dr_err(dmn, "Failed setting fte into table %d\n", ret);
		जाओ मुक्त_flow_group;
	पूर्ण

	वापस 0;

मुक्त_flow_group:
	mlx5dr_cmd_destroy_flow_group(dmn->mdev, MLX5_FLOW_TABLE_TYPE_FDB,
				      *tbl_id, *group_id);
मुक्त_flow_table:
	mlx5dr_cmd_destroy_flow_table(dmn->mdev, *tbl_id,
				      MLX5_FLOW_TABLE_TYPE_FDB);
	वापस ret;
पूर्ण

व्योम mlx5dr_fw_destroy_md_tbl(काष्ठा mlx5dr_करोमुख्य *dmn,
			      u32 tbl_id, u32 group_id)
अणु
	mlx5dr_cmd_del_flow_table_entry(dmn->mdev, FS_FT_FDB, tbl_id);
	mlx5dr_cmd_destroy_flow_group(dmn->mdev,
				      MLX5_FLOW_TABLE_TYPE_FDB,
				      tbl_id, group_id);
	mlx5dr_cmd_destroy_flow_table(dmn->mdev, tbl_id,
				      MLX5_FLOW_TABLE_TYPE_FDB);
पूर्ण
