<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/*
 * Copyright (c) 2020, Mellanox Technologies inc.  All rights reserved.
 */

#समावेश <rdma/uverbs_ioctl.h>
#समावेश <rdma/mlx5_user_ioctl_cmds.h>
#समावेश <rdma/mlx5_user_ioctl_verbs.h>
#समावेश <linux/mlx5/driver.h>
#समावेश "mlx5_ib.h"

#घोषणा UVERBS_MODULE_NAME mlx5_ib
#समावेश <rdma/uverbs_named_ioctl.h>

अटल bool pp_is_supported(काष्ठा ib_device *device)
अणु
	काष्ठा mlx5_ib_dev *dev = to_mdev(device);

	वापस (MLX5_CAP_GEN(dev->mdev, qos) &&
		MLX5_CAP_QOS(dev->mdev, packet_pacing) &&
		MLX5_CAP_QOS(dev->mdev, packet_pacing_uid));
पूर्ण

अटल पूर्णांक UVERBS_HANDLER(MLX5_IB_METHOD_PP_OBJ_ALLOC)(
	काष्ठा uverbs_attr_bundle *attrs)
अणु
	u8 rl_raw[MLX5_ST_SZ_BYTES(set_pp_rate_limit_context)] = अणुपूर्ण;
	काष्ठा ib_uobject *uobj = uverbs_attr_get_uobject(attrs,
		MLX5_IB_ATTR_PP_OBJ_ALLOC_HANDLE);
	काष्ठा mlx5_ib_dev *dev;
	काष्ठा mlx5_ib_ucontext *c;
	काष्ठा mlx5_ib_pp *pp_entry;
	व्योम *in_ctx;
	u16 uid;
	पूर्णांक inlen;
	u32 flags;
	पूर्णांक err;

	c = to_mucontext(ib_uverbs_get_ucontext(attrs));
	अगर (IS_ERR(c))
		वापस PTR_ERR(c);

	/* The allocated entry can be used only by a DEVX context */
	अगर (!c->devx_uid)
		वापस -EINVAL;

	dev = to_mdev(c->ibucontext.device);
	pp_entry = kzalloc(माप(*pp_entry), GFP_KERNEL);
	अगर (!pp_entry)
		वापस -ENOMEM;

	in_ctx = uverbs_attr_get_alloced_ptr(attrs,
					     MLX5_IB_ATTR_PP_OBJ_ALLOC_CTX);
	inlen = uverbs_attr_get_len(attrs,
				    MLX5_IB_ATTR_PP_OBJ_ALLOC_CTX);
	स_नकल(rl_raw, in_ctx, inlen);
	err = uverbs_get_flags32(&flags, attrs,
		MLX5_IB_ATTR_PP_OBJ_ALLOC_FLAGS,
		MLX5_IB_UAPI_PP_ALLOC_FLAGS_DEDICATED_INDEX);
	अगर (err)
		जाओ err;

	uid = (flags & MLX5_IB_UAPI_PP_ALLOC_FLAGS_DEDICATED_INDEX) ?
		c->devx_uid : MLX5_SHARED_RESOURCE_UID;

	err = mlx5_rl_add_rate_raw(dev->mdev, rl_raw, uid,
			(flags & MLX5_IB_UAPI_PP_ALLOC_FLAGS_DEDICATED_INDEX),
			&pp_entry->index);
	अगर (err)
		जाओ err;

	pp_entry->mdev = dev->mdev;
	uobj->object = pp_entry;
	uverbs_finalize_uobj_create(attrs, MLX5_IB_ATTR_PP_OBJ_ALLOC_HANDLE);

	err = uverbs_copy_to(attrs, MLX5_IB_ATTR_PP_OBJ_ALLOC_INDEX,
			     &pp_entry->index, माप(pp_entry->index));
	वापस err;

err:
	kमुक्त(pp_entry);
	वापस err;
पूर्ण

अटल पूर्णांक pp_obj_cleanup(काष्ठा ib_uobject *uobject,
			  क्रमागत rdma_हटाओ_reason why,
			  काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा mlx5_ib_pp *pp_entry = uobject->object;

	mlx5_rl_हटाओ_rate_raw(pp_entry->mdev, pp_entry->index);
	kमुक्त(pp_entry);
	वापस 0;
पूर्ण

DECLARE_UVERBS_NAMED_METHOD(
	MLX5_IB_METHOD_PP_OBJ_ALLOC,
	UVERBS_ATTR_IDR(MLX5_IB_ATTR_PP_OBJ_ALLOC_HANDLE,
			MLX5_IB_OBJECT_PP,
			UVERBS_ACCESS_NEW,
			UA_MANDATORY),
	UVERBS_ATTR_PTR_IN(
		MLX5_IB_ATTR_PP_OBJ_ALLOC_CTX,
		UVERBS_ATTR_SIZE(1,
			MLX5_ST_SZ_BYTES(set_pp_rate_limit_context)),
		UA_MANDATORY,
		UA_ALLOC_AND_COPY),
	UVERBS_ATTR_FLAGS_IN(MLX5_IB_ATTR_PP_OBJ_ALLOC_FLAGS,
			क्रमागत mlx5_ib_uapi_pp_alloc_flags,
			UA_MANDATORY),
	UVERBS_ATTR_PTR_OUT(MLX5_IB_ATTR_PP_OBJ_ALLOC_INDEX,
			   UVERBS_ATTR_TYPE(u16),
			   UA_MANDATORY));

DECLARE_UVERBS_NAMED_METHOD_DESTROY(
	MLX5_IB_METHOD_PP_OBJ_DESTROY,
	UVERBS_ATTR_IDR(MLX5_IB_ATTR_PP_OBJ_DESTROY_HANDLE,
			MLX5_IB_OBJECT_PP,
			UVERBS_ACCESS_DESTROY,
			UA_MANDATORY));

DECLARE_UVERBS_NAMED_OBJECT(MLX5_IB_OBJECT_PP,
			    UVERBS_TYPE_ALLOC_IDR(pp_obj_cleanup),
			    &UVERBS_METHOD(MLX5_IB_METHOD_PP_OBJ_ALLOC),
			    &UVERBS_METHOD(MLX5_IB_METHOD_PP_OBJ_DESTROY));


स्थिर काष्ठा uapi_definition mlx5_ib_qos_defs[] = अणु
	UAPI_DEF_CHAIN_OBJ_TREE_NAMED(
		MLX5_IB_OBJECT_PP,
		UAPI_DEF_IS_OBJ_SUPPORTED(pp_is_supported)),
	अणुपूर्ण,
पूर्ण;
