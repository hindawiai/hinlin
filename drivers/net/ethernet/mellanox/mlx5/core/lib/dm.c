<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
// Copyright (c) 2019 Mellanox Technologies

#समावेश <linux/mlx5/driver.h>
#समावेश <linux/mlx5/device.h>

#समावेश "mlx5_core.h"
#समावेश "lib/mlx5.h"

काष्ठा mlx5_dm अणु
	/* protect access to icm biपंचांगask */
	spinlock_t lock;
	अचिन्हित दीर्घ *steering_sw_icm_alloc_blocks;
	अचिन्हित दीर्घ *header_modअगरy_sw_icm_alloc_blocks;
पूर्ण;

काष्ठा mlx5_dm *mlx5_dm_create(काष्ठा mlx5_core_dev *dev)
अणु
	u64 header_modअगरy_icm_blocks = 0;
	u64 steering_icm_blocks = 0;
	काष्ठा mlx5_dm *dm;

	अगर (!(MLX5_CAP_GEN_64(dev, general_obj_types) & MLX5_GENERAL_OBJ_TYPES_CAP_SW_ICM))
		वापस शून्य;

	dm = kzalloc(माप(*dm), GFP_KERNEL);
	अगर (!dm)
		वापस ERR_PTR(-ENOMEM);

	spin_lock_init(&dm->lock);

	अगर (MLX5_CAP64_DEV_MEM(dev, steering_sw_icm_start_address)) अणु
		steering_icm_blocks =
			BIT(MLX5_CAP_DEV_MEM(dev, log_steering_sw_icm_size) -
			    MLX5_LOG_SW_ICM_BLOCK_SIZE(dev));

		dm->steering_sw_icm_alloc_blocks =
			kसुस्मृति(BITS_TO_LONGS(steering_icm_blocks),
				माप(अचिन्हित दीर्घ), GFP_KERNEL);
		अगर (!dm->steering_sw_icm_alloc_blocks)
			जाओ err_steering;
	पूर्ण

	अगर (MLX5_CAP64_DEV_MEM(dev, header_modअगरy_sw_icm_start_address)) अणु
		header_modअगरy_icm_blocks =
			BIT(MLX5_CAP_DEV_MEM(dev, log_header_modअगरy_sw_icm_size) -
			    MLX5_LOG_SW_ICM_BLOCK_SIZE(dev));

		dm->header_modअगरy_sw_icm_alloc_blocks =
			kसुस्मृति(BITS_TO_LONGS(header_modअगरy_icm_blocks),
				माप(अचिन्हित दीर्घ), GFP_KERNEL);
		अगर (!dm->header_modअगरy_sw_icm_alloc_blocks)
			जाओ err_modअगरy_hdr;
	पूर्ण

	वापस dm;

err_modअगरy_hdr:
	kमुक्त(dm->steering_sw_icm_alloc_blocks);

err_steering:
	kमुक्त(dm);

	वापस ERR_PTR(-ENOMEM);
पूर्ण

व्योम mlx5_dm_cleanup(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_dm *dm = dev->dm;

	अगर (!dev->dm)
		वापस;

	अगर (dm->steering_sw_icm_alloc_blocks) अणु
		WARN_ON(!biपंचांगap_empty(dm->steering_sw_icm_alloc_blocks,
				      BIT(MLX5_CAP_DEV_MEM(dev, log_steering_sw_icm_size) -
					  MLX5_LOG_SW_ICM_BLOCK_SIZE(dev))));
		kमुक्त(dm->steering_sw_icm_alloc_blocks);
	पूर्ण

	अगर (dm->header_modअगरy_sw_icm_alloc_blocks) अणु
		WARN_ON(!biपंचांगap_empty(dm->header_modअगरy_sw_icm_alloc_blocks,
				      BIT(MLX5_CAP_DEV_MEM(dev,
							   log_header_modअगरy_sw_icm_size) -
				      MLX5_LOG_SW_ICM_BLOCK_SIZE(dev))));
		kमुक्त(dm->header_modअगरy_sw_icm_alloc_blocks);
	पूर्ण

	kमुक्त(dm);
पूर्ण

पूर्णांक mlx5_dm_sw_icm_alloc(काष्ठा mlx5_core_dev *dev, क्रमागत mlx5_sw_icm_type type,
			 u64 length, u32 log_alignment, u16 uid,
			 phys_addr_t *addr, u32 *obj_id)
अणु
	u32 num_blocks = DIV_ROUND_UP_ULL(length, MLX5_SW_ICM_BLOCK_SIZE(dev));
	u32 out[MLX5_ST_SZ_DW(general_obj_out_cmd_hdr)] = अणुपूर्ण;
	u32 in[MLX5_ST_SZ_DW(create_sw_icm_in)] = अणुपूर्ण;
	काष्ठा mlx5_dm *dm = dev->dm;
	अचिन्हित दीर्घ *block_map;
	u64 icm_start_addr;
	u32 log_icm_size;
	u64 align_mask;
	u32 max_blocks;
	u64 block_idx;
	व्योम *sw_icm;
	पूर्णांक ret;

	अगर (!dev->dm)
		वापस -EOPNOTSUPP;

	अगर (!length || (length & (length - 1)) ||
	    length & (MLX5_SW_ICM_BLOCK_SIZE(dev) - 1))
		वापस -EINVAL;

	MLX5_SET(general_obj_in_cmd_hdr, in, opcode,
		 MLX5_CMD_OP_CREATE_GENERAL_OBJECT);
	MLX5_SET(general_obj_in_cmd_hdr, in, obj_type, MLX5_OBJ_TYPE_SW_ICM);
	MLX5_SET(general_obj_in_cmd_hdr, in, uid, uid);

	चयन (type) अणु
	हाल MLX5_SW_ICM_TYPE_STEERING:
		icm_start_addr = MLX5_CAP64_DEV_MEM(dev, steering_sw_icm_start_address);
		log_icm_size = MLX5_CAP_DEV_MEM(dev, log_steering_sw_icm_size);
		block_map = dm->steering_sw_icm_alloc_blocks;
		अवरोध;
	हाल MLX5_SW_ICM_TYPE_HEADER_MODIFY:
		icm_start_addr = MLX5_CAP64_DEV_MEM(dev, header_modअगरy_sw_icm_start_address);
		log_icm_size = MLX5_CAP_DEV_MEM(dev,
						log_header_modअगरy_sw_icm_size);
		block_map = dm->header_modअगरy_sw_icm_alloc_blocks;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (!block_map)
		वापस -EOPNOTSUPP;

	max_blocks = BIT(log_icm_size - MLX5_LOG_SW_ICM_BLOCK_SIZE(dev));

	अगर (log_alignment < MLX5_LOG_SW_ICM_BLOCK_SIZE(dev))
		log_alignment = MLX5_LOG_SW_ICM_BLOCK_SIZE(dev);
	align_mask = BIT(log_alignment - MLX5_LOG_SW_ICM_BLOCK_SIZE(dev)) - 1;

	spin_lock(&dm->lock);
	block_idx = biपंचांगap_find_next_zero_area(block_map, max_blocks, 0,
					       num_blocks, align_mask);

	अगर (block_idx < max_blocks)
		biपंचांगap_set(block_map,
			   block_idx, num_blocks);

	spin_unlock(&dm->lock);

	अगर (block_idx >= max_blocks)
		वापस -ENOMEM;

	sw_icm = MLX5_ADDR_OF(create_sw_icm_in, in, sw_icm);
	icm_start_addr += block_idx << MLX5_LOG_SW_ICM_BLOCK_SIZE(dev);
	MLX5_SET64(sw_icm, sw_icm, sw_icm_start_addr,
		   icm_start_addr);
	MLX5_SET(sw_icm, sw_icm, log_sw_icm_size, ilog2(length));

	ret = mlx5_cmd_exec(dev, in, माप(in), out, माप(out));
	अगर (ret) अणु
		spin_lock(&dm->lock);
		biपंचांगap_clear(block_map,
			     block_idx, num_blocks);
		spin_unlock(&dm->lock);

		वापस ret;
	पूर्ण

	*addr = icm_start_addr;
	*obj_id = MLX5_GET(general_obj_out_cmd_hdr, out, obj_id);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mlx5_dm_sw_icm_alloc);

पूर्णांक mlx5_dm_sw_icm_dealloc(काष्ठा mlx5_core_dev *dev, क्रमागत mlx5_sw_icm_type type,
			   u64 length, u16 uid, phys_addr_t addr, u32 obj_id)
अणु
	u32 num_blocks = DIV_ROUND_UP_ULL(length, MLX5_SW_ICM_BLOCK_SIZE(dev));
	u32 out[MLX5_ST_SZ_DW(general_obj_out_cmd_hdr)] = अणुपूर्ण;
	u32 in[MLX5_ST_SZ_DW(general_obj_in_cmd_hdr)] = अणुपूर्ण;
	काष्ठा mlx5_dm *dm = dev->dm;
	अचिन्हित दीर्घ *block_map;
	u64 icm_start_addr;
	u64 start_idx;
	पूर्णांक err;

	अगर (!dev->dm)
		वापस -EOPNOTSUPP;

	चयन (type) अणु
	हाल MLX5_SW_ICM_TYPE_STEERING:
		icm_start_addr = MLX5_CAP64_DEV_MEM(dev, steering_sw_icm_start_address);
		block_map = dm->steering_sw_icm_alloc_blocks;
		अवरोध;
	हाल MLX5_SW_ICM_TYPE_HEADER_MODIFY:
		icm_start_addr = MLX5_CAP64_DEV_MEM(dev, header_modअगरy_sw_icm_start_address);
		block_map = dm->header_modअगरy_sw_icm_alloc_blocks;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	MLX5_SET(general_obj_in_cmd_hdr, in, opcode,
		 MLX5_CMD_OP_DESTROY_GENERAL_OBJECT);
	MLX5_SET(general_obj_in_cmd_hdr, in, obj_type, MLX5_OBJ_TYPE_SW_ICM);
	MLX5_SET(general_obj_in_cmd_hdr, in, obj_id, obj_id);
	MLX5_SET(general_obj_in_cmd_hdr, in, uid, uid);

	err =  mlx5_cmd_exec(dev, in, माप(in), out, माप(out));
	अगर (err)
		वापस err;

	start_idx = (addr - icm_start_addr) >> MLX5_LOG_SW_ICM_BLOCK_SIZE(dev);
	spin_lock(&dm->lock);
	biपंचांगap_clear(block_map,
		     start_idx, num_blocks);
	spin_unlock(&dm->lock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mlx5_dm_sw_icm_dealloc);
