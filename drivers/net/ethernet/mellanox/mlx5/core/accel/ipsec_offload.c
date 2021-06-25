<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/* Copyright (c) 2020, Mellanox Technologies inc. All rights reserved. */

#समावेश "mlx5_core.h"
#समावेश "ipsec_offload.h"
#समावेश "lib/mlx5.h"
#समावेश "en_accel/ipsec_fs.h"

#घोषणा MLX5_IPSEC_DEV_BASIC_CAPS (MLX5_ACCEL_IPSEC_CAP_DEVICE | MLX5_ACCEL_IPSEC_CAP_IPV6 | \
				   MLX5_ACCEL_IPSEC_CAP_LSO)

काष्ठा mlx5_ipsec_sa_ctx अणु
	काष्ठा rhash_head hash;
	u32 enc_key_id;
	u32 ipsec_obj_id;
	/* hw ctx */
	काष्ठा mlx5_core_dev *dev;
	काष्ठा mlx5_ipsec_esp_xfrm *mxfrm;
पूर्ण;

काष्ठा mlx5_ipsec_esp_xfrm अणु
	/* reference counter of SA ctx */
	काष्ठा mlx5_ipsec_sa_ctx *sa_ctx;
	काष्ठा mutex lock; /* protects mlx5_ipsec_esp_xfrm */
	काष्ठा mlx5_accel_esp_xfrm accel_xfrm;
पूर्ण;

अटल u32 mlx5_ipsec_offload_device_caps(काष्ठा mlx5_core_dev *mdev)
अणु
	u32 caps = MLX5_IPSEC_DEV_BASIC_CAPS;

	अगर (!mlx5_is_ipsec_device(mdev))
		वापस 0;

	अगर (!MLX5_CAP_FLOWTABLE_NIC_TX(mdev, ipsec_encrypt) ||
	    !MLX5_CAP_FLOWTABLE_NIC_RX(mdev, ipsec_decrypt))
		वापस 0;

	अगर (MLX5_CAP_IPSEC(mdev, ipsec_crypto_esp_aes_gcm_128_encrypt) &&
	    MLX5_CAP_IPSEC(mdev, ipsec_crypto_esp_aes_gcm_128_decrypt))
		caps |= MLX5_ACCEL_IPSEC_CAP_ESP;

	अगर (MLX5_CAP_IPSEC(mdev, ipsec_esn)) अणु
		caps |= MLX5_ACCEL_IPSEC_CAP_ESN;
		caps |= MLX5_ACCEL_IPSEC_CAP_TX_IV_IS_ESN;
	पूर्ण

	/* We can accommodate up to 2^24 dअगरferent IPsec objects
	 * because we use up to 24 bit in flow table metadata
	 * to hold the IPsec Object unique handle.
	 */
	WARN_ON_ONCE(MLX5_CAP_IPSEC(mdev, log_max_ipsec_offload) > 24);
	वापस caps;
पूर्ण

अटल पूर्णांक
mlx5_ipsec_offload_esp_validate_xfrm_attrs(काष्ठा mlx5_core_dev *mdev,
					   स्थिर काष्ठा mlx5_accel_esp_xfrm_attrs *attrs)
अणु
	अगर (attrs->replay_type != MLX5_ACCEL_ESP_REPLAY_NONE) अणु
		mlx5_core_err(mdev, "Cannot offload xfrm states with anti replay (replay_type = %d)\n",
			      attrs->replay_type);
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (attrs->keymat_type != MLX5_ACCEL_ESP_KEYMAT_AES_GCM) अणु
		mlx5_core_err(mdev, "Only aes gcm keymat is supported (keymat_type = %d)\n",
			      attrs->keymat_type);
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (attrs->keymat.aes_gcm.iv_algo !=
	    MLX5_ACCEL_ESP_AES_GCM_IV_ALGO_SEQ) अणु
		mlx5_core_err(mdev, "Only iv sequence algo is supported (iv_algo = %d)\n",
			      attrs->keymat.aes_gcm.iv_algo);
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (attrs->keymat.aes_gcm.key_len != 128 &&
	    attrs->keymat.aes_gcm.key_len != 256) अणु
		mlx5_core_err(mdev, "Cannot offload xfrm states with key length other than 128/256 bit (key length = %d)\n",
			      attrs->keymat.aes_gcm.key_len);
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर ((attrs->flags & MLX5_ACCEL_ESP_FLAGS_ESN_TRIGGERED) &&
	    !MLX5_CAP_IPSEC(mdev, ipsec_esn)) अणु
		mlx5_core_err(mdev, "Cannot offload xfrm states with ESN triggered\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा mlx5_accel_esp_xfrm *
mlx5_ipsec_offload_esp_create_xfrm(काष्ठा mlx5_core_dev *mdev,
				   स्थिर काष्ठा mlx5_accel_esp_xfrm_attrs *attrs,
				   u32 flags)
अणु
	काष्ठा mlx5_ipsec_esp_xfrm *mxfrm;
	पूर्णांक err = 0;

	err = mlx5_ipsec_offload_esp_validate_xfrm_attrs(mdev, attrs);
	अगर (err)
		वापस ERR_PTR(err);

	mxfrm = kzalloc(माप(*mxfrm), GFP_KERNEL);
	अगर (!mxfrm)
		वापस ERR_PTR(-ENOMEM);

	mutex_init(&mxfrm->lock);
	स_नकल(&mxfrm->accel_xfrm.attrs, attrs,
	       माप(mxfrm->accel_xfrm.attrs));

	वापस &mxfrm->accel_xfrm;
पूर्ण

अटल व्योम mlx5_ipsec_offload_esp_destroy_xfrm(काष्ठा mlx5_accel_esp_xfrm *xfrm)
अणु
	काष्ठा mlx5_ipsec_esp_xfrm *mxfrm = container_of(xfrm, काष्ठा mlx5_ipsec_esp_xfrm,
							 accel_xfrm);

	/* assuming no sa_ctx are connected to this xfrm_ctx */
	WARN_ON(mxfrm->sa_ctx);
	kमुक्त(mxfrm);
पूर्ण

काष्ठा mlx5_ipsec_obj_attrs अणु
	स्थिर काष्ठा aes_gcm_keymat *aes_gcm;
	u32 accel_flags;
	u32 esn_msb;
	u32 enc_key_id;
पूर्ण;

अटल पूर्णांक mlx5_create_ipsec_obj(काष्ठा mlx5_core_dev *mdev,
				 काष्ठा mlx5_ipsec_obj_attrs *attrs,
				 u32 *ipsec_id)
अणु
	स्थिर काष्ठा aes_gcm_keymat *aes_gcm = attrs->aes_gcm;
	u32 out[MLX5_ST_SZ_DW(general_obj_out_cmd_hdr)];
	u32 in[MLX5_ST_SZ_DW(create_ipsec_obj_in)] = अणुपूर्ण;
	व्योम *obj, *salt_p, *salt_iv_p;
	पूर्णांक err;

	obj = MLX5_ADDR_OF(create_ipsec_obj_in, in, ipsec_object);

	/* salt and seq_iv */
	salt_p = MLX5_ADDR_OF(ipsec_obj, obj, salt);
	स_नकल(salt_p, &aes_gcm->salt, माप(aes_gcm->salt));

	चयन (aes_gcm->icv_len) अणु
	हाल 64:
		MLX5_SET(ipsec_obj, obj, icv_length,
			 MLX5_IPSEC_OBJECT_ICV_LEN_8B);
		अवरोध;
	हाल 96:
		MLX5_SET(ipsec_obj, obj, icv_length,
			 MLX5_IPSEC_OBJECT_ICV_LEN_12B);
		अवरोध;
	हाल 128:
		MLX5_SET(ipsec_obj, obj, icv_length,
			 MLX5_IPSEC_OBJECT_ICV_LEN_16B);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	salt_iv_p = MLX5_ADDR_OF(ipsec_obj, obj, implicit_iv);
	स_नकल(salt_iv_p, &aes_gcm->seq_iv, माप(aes_gcm->seq_iv));
	/* esn */
	अगर (attrs->accel_flags & MLX5_ACCEL_ESP_FLAGS_ESN_TRIGGERED) अणु
		MLX5_SET(ipsec_obj, obj, esn_en, 1);
		MLX5_SET(ipsec_obj, obj, esn_msb, attrs->esn_msb);
		अगर (attrs->accel_flags & MLX5_ACCEL_ESP_FLAGS_ESN_STATE_OVERLAP)
			MLX5_SET(ipsec_obj, obj, esn_overlap, 1);
	पूर्ण

	MLX5_SET(ipsec_obj, obj, dekn, attrs->enc_key_id);

	/* general object fields set */
	MLX5_SET(general_obj_in_cmd_hdr, in, opcode,
		 MLX5_CMD_OP_CREATE_GENERAL_OBJECT);
	MLX5_SET(general_obj_in_cmd_hdr, in, obj_type,
		 MLX5_GENERAL_OBJECT_TYPES_IPSEC);

	err = mlx5_cmd_exec(mdev, in, माप(in), out, माप(out));
	अगर (!err)
		*ipsec_id = MLX5_GET(general_obj_out_cmd_hdr, out, obj_id);

	वापस err;
पूर्ण

अटल व्योम mlx5_destroy_ipsec_obj(काष्ठा mlx5_core_dev *mdev, u32 ipsec_id)
अणु
	u32 in[MLX5_ST_SZ_DW(general_obj_in_cmd_hdr)] = अणुपूर्ण;
	u32 out[MLX5_ST_SZ_DW(general_obj_out_cmd_hdr)];

	MLX5_SET(general_obj_in_cmd_hdr, in, opcode,
		 MLX5_CMD_OP_DESTROY_GENERAL_OBJECT);
	MLX5_SET(general_obj_in_cmd_hdr, in, obj_type,
		 MLX5_GENERAL_OBJECT_TYPES_IPSEC);
	MLX5_SET(general_obj_in_cmd_hdr, in, obj_id, ipsec_id);

	mlx5_cmd_exec(mdev, in, माप(in), out, माप(out));
पूर्ण

अटल व्योम *mlx5_ipsec_offload_create_sa_ctx(काष्ठा mlx5_core_dev *mdev,
					      काष्ठा mlx5_accel_esp_xfrm *accel_xfrm,
					      स्थिर __be32 saddr[4], स्थिर __be32 daddr[4],
					      स्थिर __be32 spi, bool is_ipv6, u32 *hw_handle)
अणु
	काष्ठा mlx5_accel_esp_xfrm_attrs *xfrm_attrs = &accel_xfrm->attrs;
	काष्ठा aes_gcm_keymat *aes_gcm = &xfrm_attrs->keymat.aes_gcm;
	काष्ठा mlx5_ipsec_obj_attrs ipsec_attrs = अणुपूर्ण;
	काष्ठा mlx5_ipsec_esp_xfrm *mxfrm;
	काष्ठा mlx5_ipsec_sa_ctx *sa_ctx;
	पूर्णांक err;

	/* alloc SA context */
	sa_ctx = kzalloc(माप(*sa_ctx), GFP_KERNEL);
	अगर (!sa_ctx)
		वापस ERR_PTR(-ENOMEM);

	sa_ctx->dev = mdev;

	mxfrm = container_of(accel_xfrm, काष्ठा mlx5_ipsec_esp_xfrm, accel_xfrm);
	mutex_lock(&mxfrm->lock);
	sa_ctx->mxfrm = mxfrm;

	/* key */
	err = mlx5_create_encryption_key(mdev, aes_gcm->aes_key,
					 aes_gcm->key_len / BITS_PER_BYTE,
					 MLX5_ACCEL_OBJ_IPSEC_KEY,
					 &sa_ctx->enc_key_id);
	अगर (err) अणु
		mlx5_core_dbg(mdev, "Failed to create encryption key (err = %d)\n", err);
		जाओ err_sa_ctx;
	पूर्ण

	ipsec_attrs.aes_gcm = aes_gcm;
	ipsec_attrs.accel_flags = accel_xfrm->attrs.flags;
	ipsec_attrs.esn_msb = accel_xfrm->attrs.esn;
	ipsec_attrs.enc_key_id = sa_ctx->enc_key_id;
	err = mlx5_create_ipsec_obj(mdev, &ipsec_attrs,
				    &sa_ctx->ipsec_obj_id);
	अगर (err) अणु
		mlx5_core_dbg(mdev, "Failed to create IPsec object (err = %d)\n", err);
		जाओ err_enc_key;
	पूर्ण

	*hw_handle = sa_ctx->ipsec_obj_id;
	mxfrm->sa_ctx = sa_ctx;
	mutex_unlock(&mxfrm->lock);

	वापस sa_ctx;

err_enc_key:
	mlx5_destroy_encryption_key(mdev, sa_ctx->enc_key_id);
err_sa_ctx:
	mutex_unlock(&mxfrm->lock);
	kमुक्त(sa_ctx);
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम mlx5_ipsec_offload_delete_sa_ctx(व्योम *context)
अणु
	काष्ठा mlx5_ipsec_sa_ctx *sa_ctx = (काष्ठा mlx5_ipsec_sa_ctx *)context;
	काष्ठा mlx5_ipsec_esp_xfrm *mxfrm = sa_ctx->mxfrm;

	mutex_lock(&mxfrm->lock);
	mlx5_destroy_ipsec_obj(sa_ctx->dev, sa_ctx->ipsec_obj_id);
	mlx5_destroy_encryption_key(sa_ctx->dev, sa_ctx->enc_key_id);
	kमुक्त(sa_ctx);
	mxfrm->sa_ctx = शून्य;
	mutex_unlock(&mxfrm->lock);
पूर्ण

अटल पूर्णांक mlx5_ipsec_offload_init(काष्ठा mlx5_core_dev *mdev)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक mlx5_modअगरy_ipsec_obj(काष्ठा mlx5_core_dev *mdev,
				 काष्ठा mlx5_ipsec_obj_attrs *attrs,
				 u32 ipsec_id)
अणु
	u32 in[MLX5_ST_SZ_DW(modअगरy_ipsec_obj_in)] = अणुपूर्ण;
	u32 out[MLX5_ST_SZ_DW(query_ipsec_obj_out)];
	u64 modअगरy_field_select = 0;
	u64 general_obj_types;
	व्योम *obj;
	पूर्णांक err;

	अगर (!(attrs->accel_flags & MLX5_ACCEL_ESP_FLAGS_ESN_TRIGGERED))
		वापस 0;

	general_obj_types = MLX5_CAP_GEN_64(mdev, general_obj_types);
	अगर (!(general_obj_types & MLX5_HCA_CAP_GENERAL_OBJECT_TYPES_IPSEC))
		वापस -EINVAL;

	/* general object fields set */
	MLX5_SET(general_obj_in_cmd_hdr, in, opcode, MLX5_CMD_OP_QUERY_GENERAL_OBJECT);
	MLX5_SET(general_obj_in_cmd_hdr, in, obj_type, MLX5_GENERAL_OBJECT_TYPES_IPSEC);
	MLX5_SET(general_obj_in_cmd_hdr, in, obj_id, ipsec_id);
	err = mlx5_cmd_exec(mdev, in, माप(in), out, माप(out));
	अगर (err) अणु
		mlx5_core_err(mdev, "Query IPsec object failed (Object id %d), err = %d\n",
			      ipsec_id, err);
		वापस err;
	पूर्ण

	obj = MLX5_ADDR_OF(query_ipsec_obj_out, out, ipsec_object);
	modअगरy_field_select = MLX5_GET64(ipsec_obj, obj, modअगरy_field_select);

	/* esn */
	अगर (!(modअगरy_field_select & MLX5_MODIFY_IPSEC_BITMASK_ESN_OVERLAP) ||
	    !(modअगरy_field_select & MLX5_MODIFY_IPSEC_BITMASK_ESN_MSB))
		वापस -EOPNOTSUPP;

	obj = MLX5_ADDR_OF(modअगरy_ipsec_obj_in, in, ipsec_object);
	MLX5_SET(ipsec_obj, obj, esn_msb, attrs->esn_msb);
	अगर (attrs->accel_flags & MLX5_ACCEL_ESP_FLAGS_ESN_STATE_OVERLAP)
		MLX5_SET(ipsec_obj, obj, esn_overlap, 1);

	/* general object fields set */
	MLX5_SET(general_obj_in_cmd_hdr, in, opcode, MLX5_CMD_OP_MODIFY_GENERAL_OBJECT);

	वापस mlx5_cmd_exec(mdev, in, माप(in), out, माप(out));
पूर्ण

अटल पूर्णांक mlx5_ipsec_offload_esp_modअगरy_xfrm(काष्ठा mlx5_accel_esp_xfrm *xfrm,
					      स्थिर काष्ठा mlx5_accel_esp_xfrm_attrs *attrs)
अणु
	काष्ठा mlx5_ipsec_obj_attrs ipsec_attrs = अणुपूर्ण;
	काष्ठा mlx5_core_dev *mdev = xfrm->mdev;
	काष्ठा mlx5_ipsec_esp_xfrm *mxfrm;

	पूर्णांक err = 0;

	अगर (!स_भेद(&xfrm->attrs, attrs, माप(xfrm->attrs)))
		वापस 0;

	अगर (mlx5_ipsec_offload_esp_validate_xfrm_attrs(mdev, attrs))
		वापस -EOPNOTSUPP;

	mxfrm = container_of(xfrm, काष्ठा mlx5_ipsec_esp_xfrm, accel_xfrm);

	mutex_lock(&mxfrm->lock);

	अगर (!mxfrm->sa_ctx)
		/* Not bound xfrm, change only sw attrs */
		जाओ change_sw_xfrm_attrs;

	/* need to add find and replace in ipsec_rhash_sa the sa_ctx */
	/* modअगरy device with new hw_sa */
	ipsec_attrs.accel_flags = attrs->flags;
	ipsec_attrs.esn_msb = attrs->esn;
	err = mlx5_modअगरy_ipsec_obj(mdev,
				    &ipsec_attrs,
				    mxfrm->sa_ctx->ipsec_obj_id);

change_sw_xfrm_attrs:
	अगर (!err)
		स_नकल(&xfrm->attrs, attrs, माप(xfrm->attrs));

	mutex_unlock(&mxfrm->lock);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा mlx5_accel_ipsec_ops ipsec_offload_ops = अणु
	.device_caps = mlx5_ipsec_offload_device_caps,
	.create_hw_context = mlx5_ipsec_offload_create_sa_ctx,
	.मुक्त_hw_context = mlx5_ipsec_offload_delete_sa_ctx,
	.init = mlx5_ipsec_offload_init,
	.esp_create_xfrm = mlx5_ipsec_offload_esp_create_xfrm,
	.esp_destroy_xfrm = mlx5_ipsec_offload_esp_destroy_xfrm,
	.esp_modअगरy_xfrm = mlx5_ipsec_offload_esp_modअगरy_xfrm,
पूर्ण;

स्थिर काष्ठा mlx5_accel_ipsec_ops *mlx5_ipsec_offload_ops(काष्ठा mlx5_core_dev *mdev)
अणु
	अगर (!mlx5_ipsec_offload_device_caps(mdev))
		वापस शून्य;

	वापस &ipsec_offload_ops;
पूर्ण
