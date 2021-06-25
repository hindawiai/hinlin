<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/*
 * Copyright (c) 2021, Mellanox Technologies inc. All rights reserved.
 */

#समावेश <rdma/uverbs_std_types.h>
#समावेश "dm.h"

#घोषणा UVERBS_MODULE_NAME mlx5_ib
#समावेश <rdma/uverbs_named_ioctl.h>

अटल पूर्णांक mlx5_cmd_alloc_memic(काष्ठा mlx5_dm *dm, phys_addr_t *addr,
				u64 length, u32 alignment)
अणु
	काष्ठा mlx5_core_dev *dev = dm->dev;
	u64 num_memic_hw_pages = MLX5_CAP_DEV_MEM(dev, memic_bar_size)
					>> PAGE_SHIFT;
	u64 hw_start_addr = MLX5_CAP64_DEV_MEM(dev, memic_bar_start_addr);
	u32 max_alignment = MLX5_CAP_DEV_MEM(dev, log_max_memic_addr_alignment);
	u32 num_pages = DIV_ROUND_UP(length, PAGE_SIZE);
	u32 out[MLX5_ST_SZ_DW(alloc_memic_out)] = अणुपूर्ण;
	u32 in[MLX5_ST_SZ_DW(alloc_memic_in)] = अणुपूर्ण;
	u32 mlx5_alignment;
	u64 page_idx = 0;
	पूर्णांक ret = 0;

	अगर (!length || (length & MLX5_MEMIC_ALLOC_SIZE_MASK))
		वापस -EINVAL;

	/* mlx5 device sets alignment as 64*2^driver_value
	 * so normalizing is needed.
	 */
	mlx5_alignment = (alignment < MLX5_MEMIC_BASE_ALIGN) ? 0 :
			 alignment - MLX5_MEMIC_BASE_ALIGN;
	अगर (mlx5_alignment > max_alignment)
		वापस -EINVAL;

	MLX5_SET(alloc_memic_in, in, opcode, MLX5_CMD_OP_ALLOC_MEMIC);
	MLX5_SET(alloc_memic_in, in, range_size, num_pages * PAGE_SIZE);
	MLX5_SET(alloc_memic_in, in, memic_size, length);
	MLX5_SET(alloc_memic_in, in, log_memic_addr_alignment,
		 mlx5_alignment);

	जबतक (page_idx < num_memic_hw_pages) अणु
		spin_lock(&dm->lock);
		page_idx = biपंचांगap_find_next_zero_area(dm->memic_alloc_pages,
						      num_memic_hw_pages,
						      page_idx,
						      num_pages, 0);

		अगर (page_idx < num_memic_hw_pages)
			biपंचांगap_set(dm->memic_alloc_pages,
				   page_idx, num_pages);

		spin_unlock(&dm->lock);

		अगर (page_idx >= num_memic_hw_pages)
			अवरोध;

		MLX5_SET64(alloc_memic_in, in, range_start_addr,
			   hw_start_addr + (page_idx * PAGE_SIZE));

		ret = mlx5_cmd_exec_inout(dev, alloc_memic, in, out);
		अगर (ret) अणु
			spin_lock(&dm->lock);
			biपंचांगap_clear(dm->memic_alloc_pages,
				     page_idx, num_pages);
			spin_unlock(&dm->lock);

			अगर (ret == -EAGAIN) अणु
				page_idx++;
				जारी;
			पूर्ण

			वापस ret;
		पूर्ण

		*addr = dev->bar_addr +
			MLX5_GET64(alloc_memic_out, out, memic_start_addr);

		वापस 0;
	पूर्ण

	वापस -ENOMEM;
पूर्ण

व्योम mlx5_cmd_dealloc_memic(काष्ठा mlx5_dm *dm, phys_addr_t addr,
			    u64 length)
अणु
	काष्ठा mlx5_core_dev *dev = dm->dev;
	u64 hw_start_addr = MLX5_CAP64_DEV_MEM(dev, memic_bar_start_addr);
	u32 num_pages = DIV_ROUND_UP(length, PAGE_SIZE);
	u32 in[MLX5_ST_SZ_DW(dealloc_memic_in)] = अणुपूर्ण;
	u64 start_page_idx;
	पूर्णांक err;

	addr -= dev->bar_addr;
	start_page_idx = (addr - hw_start_addr) >> PAGE_SHIFT;

	MLX5_SET(dealloc_memic_in, in, opcode, MLX5_CMD_OP_DEALLOC_MEMIC);
	MLX5_SET64(dealloc_memic_in, in, memic_start_addr, addr);
	MLX5_SET(dealloc_memic_in, in, memic_size, length);

	err =  mlx5_cmd_exec_in(dev, dealloc_memic, in);
	अगर (err)
		वापस;

	spin_lock(&dm->lock);
	biपंचांगap_clear(dm->memic_alloc_pages,
		     start_page_idx, num_pages);
	spin_unlock(&dm->lock);
पूर्ण

व्योम mlx5_cmd_dealloc_memic_op(काष्ठा mlx5_dm *dm, phys_addr_t addr,
			       u8 operation)
अणु
	u32 in[MLX5_ST_SZ_DW(modअगरy_memic_in)] = अणुपूर्ण;
	काष्ठा mlx5_core_dev *dev = dm->dev;

	MLX5_SET(modअगरy_memic_in, in, opcode, MLX5_CMD_OP_MODIFY_MEMIC);
	MLX5_SET(modअगरy_memic_in, in, op_mod, MLX5_MODIFY_MEMIC_OP_MOD_DEALLOC);
	MLX5_SET(modअगरy_memic_in, in, memic_operation_type, operation);
	MLX5_SET64(modअगरy_memic_in, in, memic_start_addr, addr - dev->bar_addr);

	mlx5_cmd_exec_in(dev, modअगरy_memic, in);
पूर्ण

अटल पूर्णांक mlx5_cmd_alloc_memic_op(काष्ठा mlx5_dm *dm, phys_addr_t addr,
				   u8 operation, phys_addr_t *op_addr)
अणु
	u32 out[MLX5_ST_SZ_DW(modअगरy_memic_out)] = अणुपूर्ण;
	u32 in[MLX5_ST_SZ_DW(modअगरy_memic_in)] = अणुपूर्ण;
	काष्ठा mlx5_core_dev *dev = dm->dev;
	पूर्णांक err;

	MLX5_SET(modअगरy_memic_in, in, opcode, MLX5_CMD_OP_MODIFY_MEMIC);
	MLX5_SET(modअगरy_memic_in, in, op_mod, MLX5_MODIFY_MEMIC_OP_MOD_ALLOC);
	MLX5_SET(modअगरy_memic_in, in, memic_operation_type, operation);
	MLX5_SET64(modअगरy_memic_in, in, memic_start_addr, addr - dev->bar_addr);

	err = mlx5_cmd_exec_inout(dev, modअगरy_memic, in, out);
	अगर (err)
		वापस err;

	*op_addr = dev->bar_addr +
		   MLX5_GET64(modअगरy_memic_out, out, memic_operation_addr);
	वापस 0;
पूर्ण

अटल पूर्णांक add_dm_mmap_entry(काष्ठा ib_ucontext *context,
			     काष्ठा mlx5_user_mmap_entry *mentry, u8 mmap_flag,
			     माप_प्रकार size, u64 address)
अणु
	mentry->mmap_flag = mmap_flag;
	mentry->address = address;

	वापस rdma_user_mmap_entry_insert_range(
		context, &mentry->rdma_entry, size,
		MLX5_IB_MMAP_DEVICE_MEM << 16,
		(MLX5_IB_MMAP_DEVICE_MEM << 16) + (1UL << 16) - 1);
पूर्ण

अटल व्योम mlx5_ib_dm_memic_मुक्त(काष्ठा kref *kref)
अणु
	काष्ठा mlx5_ib_dm_memic *dm =
		container_of(kref, काष्ठा mlx5_ib_dm_memic, ref);
	काष्ठा mlx5_ib_dev *dev = to_mdev(dm->base.ibdm.device);

	mlx5_cmd_dealloc_memic(&dev->dm, dm->base.dev_addr, dm->base.size);
	kमुक्त(dm);
पूर्ण

अटल पूर्णांक copy_op_to_user(काष्ठा mlx5_ib_dm_op_entry *op_entry,
			   काष्ठा uverbs_attr_bundle *attrs)
अणु
	u64 start_offset;
	u16 page_idx;
	पूर्णांक err;

	page_idx = op_entry->mentry.rdma_entry.start_pgoff & 0xFFFF;
	start_offset = op_entry->op_addr & ~PAGE_MASK;
	err = uverbs_copy_to(attrs, MLX5_IB_ATTR_DM_MAP_OP_ADDR_RESP_PAGE_INDEX,
			     &page_idx, माप(page_idx));
	अगर (err)
		वापस err;

	वापस uverbs_copy_to(attrs,
			      MLX5_IB_ATTR_DM_MAP_OP_ADDR_RESP_START_OFFSET,
			      &start_offset, माप(start_offset));
पूर्ण

अटल पूर्णांक map_existing_op(काष्ठा mlx5_ib_dm_memic *dm, u8 op,
			   काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा mlx5_ib_dm_op_entry *op_entry;

	op_entry = xa_load(&dm->ops, op);
	अगर (!op_entry)
		वापस -ENOENT;

	वापस copy_op_to_user(op_entry, attrs);
पूर्ण

अटल पूर्णांक UVERBS_HANDLER(MLX5_IB_METHOD_DM_MAP_OP_ADDR)(
	काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा ib_uobject *uobj = uverbs_attr_get_uobject(
		attrs, MLX5_IB_ATTR_DM_MAP_OP_ADDR_REQ_HANDLE);
	काष्ठा mlx5_ib_dev *dev = to_mdev(uobj->context->device);
	काष्ठा ib_dm *ibdm = uobj->object;
	काष्ठा mlx5_ib_dm_memic *dm = to_memic(ibdm);
	काष्ठा mlx5_ib_dm_op_entry *op_entry;
	पूर्णांक err;
	u8 op;

	err = uverbs_copy_from(&op, attrs, MLX5_IB_ATTR_DM_MAP_OP_ADDR_REQ_OP);
	अगर (err)
		वापस err;

	अगर (op >= BITS_PER_TYPE(u32))
		वापस -EOPNOTSUPP;

	अगर (!(MLX5_CAP_DEV_MEM(dev->mdev, memic_operations) & BIT(op)))
		वापस -EOPNOTSUPP;

	mutex_lock(&dm->ops_xa_lock);
	err = map_existing_op(dm, op, attrs);
	अगर (!err || err != -ENOENT)
		जाओ err_unlock;

	op_entry = kzalloc(माप(*op_entry), GFP_KERNEL);
	अगर (!op_entry)
		जाओ err_unlock;

	err = mlx5_cmd_alloc_memic_op(&dev->dm, dm->base.dev_addr, op,
				      &op_entry->op_addr);
	अगर (err) अणु
		kमुक्त(op_entry);
		जाओ err_unlock;
	पूर्ण
	op_entry->op = op;
	op_entry->dm = dm;

	err = add_dm_mmap_entry(uobj->context, &op_entry->mentry,
				MLX5_IB_MMAP_TYPE_MEMIC_OP, dm->base.size,
				op_entry->op_addr & PAGE_MASK);
	अगर (err) अणु
		mlx5_cmd_dealloc_memic_op(&dev->dm, dm->base.dev_addr, op);
		kमुक्त(op_entry);
		जाओ err_unlock;
	पूर्ण
	/* From this poपूर्णांक, entry will be मुक्तd by mmap_मुक्त */
	kref_get(&dm->ref);

	err = copy_op_to_user(op_entry, attrs);
	अगर (err)
		जाओ err_हटाओ;

	err = xa_insert(&dm->ops, op, op_entry, GFP_KERNEL);
	अगर (err)
		जाओ err_हटाओ;
	mutex_unlock(&dm->ops_xa_lock);

	वापस 0;

err_हटाओ:
	rdma_user_mmap_entry_हटाओ(&op_entry->mentry.rdma_entry);
err_unlock:
	mutex_unlock(&dm->ops_xa_lock);

	वापस err;
पूर्ण

अटल काष्ठा ib_dm *handle_alloc_dm_memic(काष्ठा ib_ucontext *ctx,
					   काष्ठा ib_dm_alloc_attr *attr,
					   काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा mlx5_dm *dm_db = &to_mdev(ctx->device)->dm;
	काष्ठा mlx5_ib_dm_memic *dm;
	u64 start_offset;
	u16 page_idx;
	पूर्णांक err;
	u64 address;

	अगर (!MLX5_CAP_DEV_MEM(dm_db->dev, memic))
		वापस ERR_PTR(-EOPNOTSUPP);

	dm = kzalloc(माप(*dm), GFP_KERNEL);
	अगर (!dm)
		वापस ERR_PTR(-ENOMEM);

	dm->base.type = MLX5_IB_UAPI_DM_TYPE_MEMIC;
	dm->base.size = roundup(attr->length, MLX5_MEMIC_BASE_SIZE);
	dm->base.ibdm.device = ctx->device;

	kref_init(&dm->ref);
	xa_init(&dm->ops);
	mutex_init(&dm->ops_xa_lock);
	dm->req_length = attr->length;

	err = mlx5_cmd_alloc_memic(dm_db, &dm->base.dev_addr,
				   dm->base.size, attr->alignment);
	अगर (err) अणु
		kमुक्त(dm);
		वापस ERR_PTR(err);
	पूर्ण

	address = dm->base.dev_addr & PAGE_MASK;
	err = add_dm_mmap_entry(ctx, &dm->mentry, MLX5_IB_MMAP_TYPE_MEMIC,
				dm->base.size, address);
	अगर (err) अणु
		mlx5_cmd_dealloc_memic(dm_db, dm->base.dev_addr, dm->base.size);
		kमुक्त(dm);
		वापस ERR_PTR(err);
	पूर्ण

	page_idx = dm->mentry.rdma_entry.start_pgoff & 0xFFFF;
	err = uverbs_copy_to(attrs, MLX5_IB_ATTR_ALLOC_DM_RESP_PAGE_INDEX,
			     &page_idx, माप(page_idx));
	अगर (err)
		जाओ err_copy;

	start_offset = dm->base.dev_addr & ~PAGE_MASK;
	err = uverbs_copy_to(attrs,
			     MLX5_IB_ATTR_ALLOC_DM_RESP_START_OFFSET,
			     &start_offset, माप(start_offset));
	अगर (err)
		जाओ err_copy;

	वापस &dm->base.ibdm;

err_copy:
	rdma_user_mmap_entry_हटाओ(&dm->mentry.rdma_entry);
	वापस ERR_PTR(err);
पूर्ण

अटल क्रमागत mlx5_sw_icm_type get_icm_type(पूर्णांक uapi_type)
अणु
	वापस uapi_type == MLX5_IB_UAPI_DM_TYPE_STEERING_SW_ICM ?
		       MLX5_SW_ICM_TYPE_STEERING :
		       MLX5_SW_ICM_TYPE_HEADER_MODIFY;
पूर्ण

अटल काष्ठा ib_dm *handle_alloc_dm_sw_icm(काष्ठा ib_ucontext *ctx,
					    काष्ठा ib_dm_alloc_attr *attr,
					    काष्ठा uverbs_attr_bundle *attrs,
					    पूर्णांक type)
अणु
	काष्ठा mlx5_core_dev *dev = to_mdev(ctx->device)->mdev;
	क्रमागत mlx5_sw_icm_type icm_type = get_icm_type(type);
	काष्ठा mlx5_ib_dm_icm *dm;
	u64 act_size;
	पूर्णांक err;

	dm = kzalloc(माप(*dm), GFP_KERNEL);
	अगर (!dm)
		वापस ERR_PTR(-ENOMEM);

	dm->base.type = type;
	dm->base.ibdm.device = ctx->device;

	अगर (!capable(CAP_SYS_RAWIO) || !capable(CAP_NET_RAW)) अणु
		err = -EPERM;
		जाओ मुक्त;
	पूर्ण

	अगर (!(MLX5_CAP_FLOWTABLE_NIC_RX(dev, sw_owner) ||
	      MLX5_CAP_FLOWTABLE_NIC_TX(dev, sw_owner) ||
	      MLX5_CAP_FLOWTABLE_NIC_RX(dev, sw_owner_v2) ||
	      MLX5_CAP_FLOWTABLE_NIC_TX(dev, sw_owner_v2))) अणु
		err = -EOPNOTSUPP;
		जाओ मुक्त;
	पूर्ण

	/* Allocation size must a multiple of the basic block size
	 * and a घातer of 2.
	 */
	act_size = round_up(attr->length, MLX5_SW_ICM_BLOCK_SIZE(dev));
	act_size = roundup_घात_of_two(act_size);

	dm->base.size = act_size;
	err = mlx5_dm_sw_icm_alloc(dev, icm_type, act_size, attr->alignment,
				   to_mucontext(ctx)->devx_uid,
				   &dm->base.dev_addr, &dm->obj_id);
	अगर (err)
		जाओ मुक्त;

	err = uverbs_copy_to(attrs, MLX5_IB_ATTR_ALLOC_DM_RESP_START_OFFSET,
			     &dm->base.dev_addr, माप(dm->base.dev_addr));
	अगर (err) अणु
		mlx5_dm_sw_icm_dealloc(dev, icm_type, dm->base.size,
				       to_mucontext(ctx)->devx_uid,
				       dm->base.dev_addr, dm->obj_id);
		जाओ मुक्त;
	पूर्ण
	वापस &dm->base.ibdm;
मुक्त:
	kमुक्त(dm);
	वापस ERR_PTR(err);
पूर्ण

काष्ठा ib_dm *mlx5_ib_alloc_dm(काष्ठा ib_device *ibdev,
			       काष्ठा ib_ucontext *context,
			       काष्ठा ib_dm_alloc_attr *attr,
			       काष्ठा uverbs_attr_bundle *attrs)
अणु
	क्रमागत mlx5_ib_uapi_dm_type type;
	पूर्णांक err;

	err = uverbs_get_स्थिर_शेष(&type, attrs,
				       MLX5_IB_ATTR_ALLOC_DM_REQ_TYPE,
				       MLX5_IB_UAPI_DM_TYPE_MEMIC);
	अगर (err)
		वापस ERR_PTR(err);

	mlx5_ib_dbg(to_mdev(ibdev), "alloc_dm req: dm_type=%d user_length=0x%llx log_alignment=%d\n",
		    type, attr->length, attr->alignment);

	चयन (type) अणु
	हाल MLX5_IB_UAPI_DM_TYPE_MEMIC:
		वापस handle_alloc_dm_memic(context, attr, attrs);
	हाल MLX5_IB_UAPI_DM_TYPE_STEERING_SW_ICM:
		वापस handle_alloc_dm_sw_icm(context, attr, attrs, type);
	हाल MLX5_IB_UAPI_DM_TYPE_HEADER_MODIFY_SW_ICM:
		वापस handle_alloc_dm_sw_icm(context, attr, attrs, type);
	शेष:
		वापस ERR_PTR(-EOPNOTSUPP);
	पूर्ण
पूर्ण

अटल व्योम dm_memic_हटाओ_ops(काष्ठा mlx5_ib_dm_memic *dm)
अणु
	काष्ठा mlx5_ib_dm_op_entry *entry;
	अचिन्हित दीर्घ idx;

	mutex_lock(&dm->ops_xa_lock);
	xa_क्रम_each(&dm->ops, idx, entry) अणु
		xa_erase(&dm->ops, idx);
		rdma_user_mmap_entry_हटाओ(&entry->mentry.rdma_entry);
	पूर्ण
	mutex_unlock(&dm->ops_xa_lock);
पूर्ण

अटल व्योम mlx5_dm_memic_dealloc(काष्ठा mlx5_ib_dm_memic *dm)
अणु
	dm_memic_हटाओ_ops(dm);
	rdma_user_mmap_entry_हटाओ(&dm->mentry.rdma_entry);
पूर्ण

अटल पूर्णांक mlx5_dm_icm_dealloc(काष्ठा mlx5_ib_ucontext *ctx,
			       काष्ठा mlx5_ib_dm_icm *dm)
अणु
	क्रमागत mlx5_sw_icm_type type = get_icm_type(dm->base.type);
	काष्ठा mlx5_core_dev *dev = to_mdev(dm->base.ibdm.device)->mdev;
	पूर्णांक err;

	err = mlx5_dm_sw_icm_dealloc(dev, type, dm->base.size, ctx->devx_uid,
				     dm->base.dev_addr, dm->obj_id);
	अगर (!err)
		kमुक्त(dm);
	वापस 0;
पूर्ण

अटल पूर्णांक mlx5_ib_dealloc_dm(काष्ठा ib_dm *ibdm,
			      काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा mlx5_ib_ucontext *ctx = rdma_udata_to_drv_context(
		&attrs->driver_udata, काष्ठा mlx5_ib_ucontext, ibucontext);
	काष्ठा mlx5_ib_dm *dm = to_mdm(ibdm);

	चयन (dm->type) अणु
	हाल MLX5_IB_UAPI_DM_TYPE_MEMIC:
		mlx5_dm_memic_dealloc(to_memic(ibdm));
		वापस 0;
	हाल MLX5_IB_UAPI_DM_TYPE_STEERING_SW_ICM:
	हाल MLX5_IB_UAPI_DM_TYPE_HEADER_MODIFY_SW_ICM:
		वापस mlx5_dm_icm_dealloc(ctx, to_icm(ibdm));
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक UVERBS_HANDLER(MLX5_IB_METHOD_DM_QUERY)(
	काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा ib_dm *ibdm =
		uverbs_attr_get_obj(attrs, MLX5_IB_ATTR_QUERY_DM_REQ_HANDLE);
	काष्ठा mlx5_ib_dm *dm = to_mdm(ibdm);
	काष्ठा mlx5_ib_dm_memic *memic;
	u64 start_offset;
	u16 page_idx;
	पूर्णांक err;

	अगर (dm->type != MLX5_IB_UAPI_DM_TYPE_MEMIC)
		वापस -EOPNOTSUPP;

	memic = to_memic(ibdm);
	page_idx = memic->mentry.rdma_entry.start_pgoff & 0xFFFF;
	err = uverbs_copy_to(attrs, MLX5_IB_ATTR_QUERY_DM_RESP_PAGE_INDEX,
			     &page_idx, माप(page_idx));
	अगर (err)
		वापस err;

	start_offset = memic->base.dev_addr & ~PAGE_MASK;
	err =  uverbs_copy_to(attrs, MLX5_IB_ATTR_QUERY_DM_RESP_START_OFFSET,
			      &start_offset, माप(start_offset));
	अगर (err)
		वापस err;

	वापस uverbs_copy_to(attrs, MLX5_IB_ATTR_QUERY_DM_RESP_LENGTH,
			      &memic->req_length,
			      माप(memic->req_length));
पूर्ण

व्योम mlx5_ib_dm_mmap_मुक्त(काष्ठा mlx5_ib_dev *dev,
			  काष्ठा mlx5_user_mmap_entry *mentry)
अणु
	काष्ठा mlx5_ib_dm_op_entry *op_entry;
	काष्ठा mlx5_ib_dm_memic *mdm;

	चयन (mentry->mmap_flag) अणु
	हाल MLX5_IB_MMAP_TYPE_MEMIC:
		mdm = container_of(mentry, काष्ठा mlx5_ib_dm_memic, mentry);
		kref_put(&mdm->ref, mlx5_ib_dm_memic_मुक्त);
		अवरोध;
	हाल MLX5_IB_MMAP_TYPE_MEMIC_OP:
		op_entry = container_of(mentry, काष्ठा mlx5_ib_dm_op_entry,
					mentry);
		mdm = op_entry->dm;
		mlx5_cmd_dealloc_memic_op(&dev->dm, mdm->base.dev_addr,
					  op_entry->op);
		kमुक्त(op_entry);
		kref_put(&mdm->ref, mlx5_ib_dm_memic_मुक्त);
		अवरोध;
	शेष:
		WARN_ON(true);
	पूर्ण
पूर्ण

DECLARE_UVERBS_NAMED_METHOD(
	MLX5_IB_METHOD_DM_QUERY,
	UVERBS_ATTR_IDR(MLX5_IB_ATTR_QUERY_DM_REQ_HANDLE, UVERBS_OBJECT_DM,
			UVERBS_ACCESS_READ, UA_MANDATORY),
	UVERBS_ATTR_PTR_OUT(MLX5_IB_ATTR_QUERY_DM_RESP_START_OFFSET,
			    UVERBS_ATTR_TYPE(u64), UA_MANDATORY),
	UVERBS_ATTR_PTR_OUT(MLX5_IB_ATTR_QUERY_DM_RESP_PAGE_INDEX,
			    UVERBS_ATTR_TYPE(u16), UA_MANDATORY),
	UVERBS_ATTR_PTR_OUT(MLX5_IB_ATTR_QUERY_DM_RESP_LENGTH,
			    UVERBS_ATTR_TYPE(u64), UA_MANDATORY));

ADD_UVERBS_ATTRIBUTES_SIMPLE(
	mlx5_ib_dm, UVERBS_OBJECT_DM, UVERBS_METHOD_DM_ALLOC,
	UVERBS_ATTR_PTR_OUT(MLX5_IB_ATTR_ALLOC_DM_RESP_START_OFFSET,
			    UVERBS_ATTR_TYPE(u64), UA_MANDATORY),
	UVERBS_ATTR_PTR_OUT(MLX5_IB_ATTR_ALLOC_DM_RESP_PAGE_INDEX,
			    UVERBS_ATTR_TYPE(u16), UA_OPTIONAL),
	UVERBS_ATTR_CONST_IN(MLX5_IB_ATTR_ALLOC_DM_REQ_TYPE,
			     क्रमागत mlx5_ib_uapi_dm_type, UA_OPTIONAL));

DECLARE_UVERBS_NAMED_METHOD(
	MLX5_IB_METHOD_DM_MAP_OP_ADDR,
	UVERBS_ATTR_IDR(MLX5_IB_ATTR_DM_MAP_OP_ADDR_REQ_HANDLE,
			UVERBS_OBJECT_DM,
			UVERBS_ACCESS_READ,
			UA_MANDATORY),
	UVERBS_ATTR_PTR_IN(MLX5_IB_ATTR_DM_MAP_OP_ADDR_REQ_OP,
			   UVERBS_ATTR_TYPE(u8),
			   UA_MANDATORY),
	UVERBS_ATTR_PTR_OUT(MLX5_IB_ATTR_DM_MAP_OP_ADDR_RESP_START_OFFSET,
			    UVERBS_ATTR_TYPE(u64),
			    UA_MANDATORY),
	UVERBS_ATTR_PTR_OUT(MLX5_IB_ATTR_DM_MAP_OP_ADDR_RESP_PAGE_INDEX,
			    UVERBS_ATTR_TYPE(u16),
			    UA_OPTIONAL));

DECLARE_UVERBS_GLOBAL_METHODS(UVERBS_OBJECT_DM,
			      &UVERBS_METHOD(MLX5_IB_METHOD_DM_MAP_OP_ADDR),
			      &UVERBS_METHOD(MLX5_IB_METHOD_DM_QUERY));

स्थिर काष्ठा uapi_definition mlx5_ib_dm_defs[] = अणु
	UAPI_DEF_CHAIN_OBJ_TREE(UVERBS_OBJECT_DM, &mlx5_ib_dm),
	UAPI_DEF_CHAIN_OBJ_TREE_NAMED(UVERBS_OBJECT_DM),
	अणुपूर्ण,
पूर्ण;

स्थिर काष्ठा ib_device_ops mlx5_ib_dev_dm_ops = अणु
	.alloc_dm = mlx5_ib_alloc_dm,
	.dealloc_dm = mlx5_ib_dealloc_dm,
	.reg_dm_mr = mlx5_ib_reg_dm_mr,
पूर्ण;
