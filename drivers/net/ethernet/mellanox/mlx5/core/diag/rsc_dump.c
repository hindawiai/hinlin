<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/* Copyright (c) 2019 Mellanox Technologies. */

#समावेश "rsc_dump.h"
#समावेश "lib/mlx5.h"

#घोषणा MLX5_SGMT_TYPE(SGMT) MLX5_SGMT_TYPE_##SGMT
#घोषणा MLX5_SGMT_STR_ASSING(SGMT)[MLX5_SGMT_TYPE(SGMT)] = #SGMT
अटल स्थिर अक्षर *स्थिर mlx5_rsc_sgmt_name[] = अणु
	MLX5_SGMT_STR_ASSING(HW_CQPC),
	MLX5_SGMT_STR_ASSING(HW_SQPC),
	MLX5_SGMT_STR_ASSING(HW_RQPC),
	MLX5_SGMT_STR_ASSING(FULL_SRQC),
	MLX5_SGMT_STR_ASSING(FULL_CQC),
	MLX5_SGMT_STR_ASSING(FULL_EQC),
	MLX5_SGMT_STR_ASSING(FULL_QPC),
	MLX5_SGMT_STR_ASSING(SND_BUFF),
	MLX5_SGMT_STR_ASSING(RCV_BUFF),
	MLX5_SGMT_STR_ASSING(SRQ_BUFF),
	MLX5_SGMT_STR_ASSING(CQ_BUFF),
	MLX5_SGMT_STR_ASSING(EQ_BUFF),
	MLX5_SGMT_STR_ASSING(SX_SLICE),
	MLX5_SGMT_STR_ASSING(SX_SLICE_ALL),
	MLX5_SGMT_STR_ASSING(RDB),
	MLX5_SGMT_STR_ASSING(RX_SLICE_ALL),
	MLX5_SGMT_STR_ASSING(PRM_QUERY_QP),
	MLX5_SGMT_STR_ASSING(PRM_QUERY_CQ),
	MLX5_SGMT_STR_ASSING(PRM_QUERY_MKEY),
पूर्ण;

काष्ठा mlx5_rsc_dump अणु
	u32 pdn;
	काष्ठा mlx5_core_mkey mkey;
	u16 fw_segment_type[MLX5_SGMT_TYPE_NUM];
पूर्ण;

काष्ठा mlx5_rsc_dump_cmd अणु
	u64 mem_size;
	u8 cmd[MLX5_ST_SZ_BYTES(resource_dump)];
पूर्ण;

अटल पूर्णांक mlx5_rsc_dump_sgmt_get_by_name(अक्षर *name)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(mlx5_rsc_sgmt_name); i++)
		अगर (!म_भेद(name, mlx5_rsc_sgmt_name[i]))
			वापस i;

	वापस -EINVAL;
पूर्ण

अटल व्योम mlx5_rsc_dump_पढ़ो_menu_sgmt(काष्ठा mlx5_rsc_dump *rsc_dump, काष्ठा page *page)
अणु
	व्योम *data = page_address(page);
	क्रमागत mlx5_sgmt_type sgmt_idx;
	पूर्णांक num_of_items;
	अक्षर *sgmt_name;
	व्योम *member;
	व्योम *menu;
	पूर्णांक i;

	menu = MLX5_ADDR_OF(menu_resource_dump_response, data, menu);
	num_of_items = MLX5_GET(resource_dump_menu_segment, menu, num_of_records);

	क्रम (i = 0; i < num_of_items; i++) अणु
		member = MLX5_ADDR_OF(resource_dump_menu_segment, menu, record[i]);
		sgmt_name =  MLX5_ADDR_OF(resource_dump_menu_record, member, segment_name);
		sgmt_idx = mlx5_rsc_dump_sgmt_get_by_name(sgmt_name);
		अगर (sgmt_idx == -EINVAL)
			जारी;
		rsc_dump->fw_segment_type[sgmt_idx] = MLX5_GET(resource_dump_menu_record,
							       member, segment_type);
	पूर्ण
पूर्ण

अटल पूर्णांक mlx5_rsc_dump_trigger(काष्ठा mlx5_core_dev *dev, काष्ठा mlx5_rsc_dump_cmd *cmd,
				 काष्ठा page *page)
अणु
	काष्ठा mlx5_rsc_dump *rsc_dump = dev->rsc_dump;
	काष्ठा device *ddev = mlx5_core_dma_dev(dev);
	u32 out_seq_num;
	u32 in_seq_num;
	dma_addr_t dma;
	पूर्णांक err;

	dma = dma_map_page(ddev, page, 0, cmd->mem_size, DMA_FROM_DEVICE);
	अगर (unlikely(dma_mapping_error(ddev, dma)))
		वापस -ENOMEM;

	in_seq_num = MLX5_GET(resource_dump, cmd->cmd, seq_num);
	MLX5_SET(resource_dump, cmd->cmd, mkey, rsc_dump->mkey.key);
	MLX5_SET64(resource_dump, cmd->cmd, address, dma);

	err = mlx5_core_access_reg(dev, cmd->cmd, माप(cmd->cmd), cmd->cmd,
				   माप(cmd->cmd), MLX5_REG_RESOURCE_DUMP, 0, 1);
	अगर (err) अणु
		mlx5_core_err(dev, "Resource dump: Failed to access err %d\n", err);
		जाओ out;
	पूर्ण
	out_seq_num = MLX5_GET(resource_dump, cmd->cmd, seq_num);
	अगर (out_seq_num && (in_seq_num + 1 != out_seq_num))
		err = -EIO;
out:
	dma_unmap_page(ddev, dma, cmd->mem_size, DMA_FROM_DEVICE);
	वापस err;
पूर्ण

काष्ठा mlx5_rsc_dump_cmd *mlx5_rsc_dump_cmd_create(काष्ठा mlx5_core_dev *dev,
						   काष्ठा mlx5_rsc_key *key)
अणु
	काष्ठा mlx5_rsc_dump_cmd *cmd;
	पूर्णांक sgmt_type;

	अगर (IS_ERR_OR_शून्य(dev->rsc_dump))
		वापस ERR_PTR(-EOPNOTSUPP);

	sgmt_type = dev->rsc_dump->fw_segment_type[key->rsc];
	अगर (!sgmt_type && key->rsc != MLX5_SGMT_TYPE_MENU)
		वापस ERR_PTR(-EOPNOTSUPP);

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (!cmd) अणु
		mlx5_core_err(dev, "Resource dump: Failed to allocate command\n");
		वापस ERR_PTR(-ENOMEM);
	पूर्ण
	MLX5_SET(resource_dump, cmd->cmd, segment_type, sgmt_type);
	MLX5_SET(resource_dump, cmd->cmd, index1, key->index1);
	MLX5_SET(resource_dump, cmd->cmd, index2, key->index2);
	MLX5_SET(resource_dump, cmd->cmd, num_of_obj1, key->num_of_obj1);
	MLX5_SET(resource_dump, cmd->cmd, num_of_obj2, key->num_of_obj2);
	MLX5_SET(resource_dump, cmd->cmd, size, key->size);
	cmd->mem_size = key->size;
	वापस cmd;
पूर्ण
EXPORT_SYMBOL(mlx5_rsc_dump_cmd_create);

व्योम mlx5_rsc_dump_cmd_destroy(काष्ठा mlx5_rsc_dump_cmd *cmd)
अणु
	kमुक्त(cmd);
पूर्ण
EXPORT_SYMBOL(mlx5_rsc_dump_cmd_destroy);

पूर्णांक mlx5_rsc_dump_next(काष्ठा mlx5_core_dev *dev, काष्ठा mlx5_rsc_dump_cmd *cmd,
		       काष्ठा page *page, पूर्णांक *size)
अणु
	bool more_dump;
	पूर्णांक err;

	अगर (IS_ERR_OR_शून्य(dev->rsc_dump))
		वापस -EOPNOTSUPP;

	err = mlx5_rsc_dump_trigger(dev, cmd, page);
	अगर (err) अणु
		mlx5_core_err(dev, "Resource dump: Failed to trigger dump, %d\n", err);
		वापस err;
	पूर्ण
	*size = MLX5_GET(resource_dump, cmd->cmd, size);
	more_dump = MLX5_GET(resource_dump, cmd->cmd, more_dump);

	वापस more_dump;
पूर्ण
EXPORT_SYMBOL(mlx5_rsc_dump_next);

#घोषणा MLX5_RSC_DUMP_MENU_SEGMENT 0xffff
अटल पूर्णांक mlx5_rsc_dump_menu(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_rsc_dump_cmd *cmd = शून्य;
	काष्ठा mlx5_rsc_key key = अणुपूर्ण;
	काष्ठा page *page;
	पूर्णांक size;
	पूर्णांक err;

	page = alloc_page(GFP_KERNEL);
	अगर (!page)
		वापस -ENOMEM;

	key.rsc = MLX5_SGMT_TYPE_MENU;
	key.size = PAGE_SIZE;
	cmd  = mlx5_rsc_dump_cmd_create(dev, &key);
	अगर (IS_ERR(cmd)) अणु
		err = PTR_ERR(cmd);
		जाओ मुक्त_page;
	पूर्ण
	MLX5_SET(resource_dump, cmd->cmd, segment_type, MLX5_RSC_DUMP_MENU_SEGMENT);

	करो अणु
		err = mlx5_rsc_dump_next(dev, cmd, page, &size);
		अगर (err < 0)
			जाओ destroy_cmd;

		mlx5_rsc_dump_पढ़ो_menu_sgmt(dev->rsc_dump, page);

	पूर्ण जबतक (err > 0);

destroy_cmd:
	mlx5_rsc_dump_cmd_destroy(cmd);
मुक्त_page:
	__मुक्त_page(page);

	वापस err;
पूर्ण

अटल पूर्णांक mlx5_rsc_dump_create_mkey(काष्ठा mlx5_core_dev *mdev, u32 pdn,
				     काष्ठा mlx5_core_mkey *mkey)
अणु
	पूर्णांक inlen = MLX5_ST_SZ_BYTES(create_mkey_in);
	व्योम *mkc;
	u32 *in;
	पूर्णांक err;

	in = kvzalloc(inlen, GFP_KERNEL);
	अगर (!in)
		वापस -ENOMEM;

	mkc = MLX5_ADDR_OF(create_mkey_in, in, memory_key_mkey_entry);
	MLX5_SET(mkc, mkc, access_mode_1_0, MLX5_MKC_ACCESS_MODE_PA);
	MLX5_SET(mkc, mkc, lw, 1);
	MLX5_SET(mkc, mkc, lr, 1);

	MLX5_SET(mkc, mkc, pd, pdn);
	MLX5_SET(mkc, mkc, length64, 1);
	MLX5_SET(mkc, mkc, qpn, 0xffffff);

	err = mlx5_core_create_mkey(mdev, mkey, in, inlen);

	kvमुक्त(in);
	वापस err;
पूर्ण

काष्ठा mlx5_rsc_dump *mlx5_rsc_dump_create(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_rsc_dump *rsc_dump;

	अगर (!MLX5_CAP_DEBUG(dev, resource_dump)) अणु
		mlx5_core_dbg(dev, "Resource dump: capability not present\n");
		वापस शून्य;
	पूर्ण
	rsc_dump = kzalloc(माप(*rsc_dump), GFP_KERNEL);
	अगर (!rsc_dump)
		वापस ERR_PTR(-ENOMEM);

	वापस rsc_dump;
पूर्ण

व्योम mlx5_rsc_dump_destroy(काष्ठा mlx5_core_dev *dev)
अणु
	अगर (IS_ERR_OR_शून्य(dev->rsc_dump))
		वापस;
	kमुक्त(dev->rsc_dump);
पूर्ण

पूर्णांक mlx5_rsc_dump_init(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_rsc_dump *rsc_dump = dev->rsc_dump;
	पूर्णांक err;

	अगर (IS_ERR_OR_शून्य(dev->rsc_dump))
		वापस 0;

	err = mlx5_core_alloc_pd(dev, &rsc_dump->pdn);
	अगर (err) अणु
		mlx5_core_warn(dev, "Resource dump: Failed to allocate PD %d\n", err);
		वापस err;
	पूर्ण
	err = mlx5_rsc_dump_create_mkey(dev, rsc_dump->pdn, &rsc_dump->mkey);
	अगर (err) अणु
		mlx5_core_err(dev, "Resource dump: Failed to create mkey, %d\n", err);
		जाओ मुक्त_pd;
	पूर्ण
	err = mlx5_rsc_dump_menu(dev);
	अगर (err) अणु
		mlx5_core_err(dev, "Resource dump: Failed to read menu, %d\n", err);
		जाओ destroy_mkey;
	पूर्ण
	वापस err;

destroy_mkey:
	mlx5_core_destroy_mkey(dev, &rsc_dump->mkey);
मुक्त_pd:
	mlx5_core_dealloc_pd(dev, rsc_dump->pdn);
	वापस err;
पूर्ण

व्योम mlx5_rsc_dump_cleanup(काष्ठा mlx5_core_dev *dev)
अणु
	अगर (IS_ERR_OR_शून्य(dev->rsc_dump))
		वापस;

	mlx5_core_destroy_mkey(dev, &dev->rsc_dump->mkey);
	mlx5_core_dealloc_pd(dev, dev->rsc_dump->pdn);
पूर्ण
