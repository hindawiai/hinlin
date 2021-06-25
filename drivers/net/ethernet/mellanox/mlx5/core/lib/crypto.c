<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
// Copyright (c) 2019 Mellanox Technologies.

#समावेश "mlx5_core.h"
#समावेश "lib/mlx5.h"

पूर्णांक mlx5_create_encryption_key(काष्ठा mlx5_core_dev *mdev,
			       व्योम *key, u32 sz_bytes,
			       u32 key_type, u32 *p_key_id)
अणु
	u32 in[MLX5_ST_SZ_DW(create_encryption_key_in)] = अणुपूर्ण;
	u32 out[MLX5_ST_SZ_DW(general_obj_out_cmd_hdr)];
	u32 sz_bits = sz_bytes * BITS_PER_BYTE;
	u8  general_obj_key_size;
	u64 general_obj_types;
	व्योम *obj, *key_p;
	पूर्णांक err;

	obj = MLX5_ADDR_OF(create_encryption_key_in, in, encryption_key_object);
	key_p = MLX5_ADDR_OF(encryption_key_obj, obj, key);

	general_obj_types = MLX5_CAP_GEN_64(mdev, general_obj_types);
	अगर (!(general_obj_types &
	      MLX5_HCA_CAP_GENERAL_OBJECT_TYPES_ENCRYPTION_KEY))
		वापस -EINVAL;

	चयन (sz_bits) अणु
	हाल 128:
		general_obj_key_size =
			MLX5_GENERAL_OBJECT_TYPE_ENCRYPTION_KEY_KEY_SIZE_128;
		key_p += sz_bytes;
		अवरोध;
	हाल 256:
		general_obj_key_size =
			MLX5_GENERAL_OBJECT_TYPE_ENCRYPTION_KEY_KEY_SIZE_256;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	स_नकल(key_p, key, sz_bytes);

	MLX5_SET(encryption_key_obj, obj, key_size, general_obj_key_size);
	MLX5_SET(encryption_key_obj, obj, key_type, key_type);
	MLX5_SET(general_obj_in_cmd_hdr, in, opcode,
		 MLX5_CMD_OP_CREATE_GENERAL_OBJECT);
	MLX5_SET(general_obj_in_cmd_hdr, in, obj_type,
		 MLX5_GENERAL_OBJECT_TYPES_ENCRYPTION_KEY);
	MLX5_SET(encryption_key_obj, obj, pd, mdev->mlx5e_res.hw_objs.pdn);

	err = mlx5_cmd_exec(mdev, in, माप(in), out, माप(out));
	अगर (!err)
		*p_key_id = MLX5_GET(general_obj_out_cmd_hdr, out, obj_id);

	/* aव्योम leaking key on the stack */
	memzero_explicit(in, माप(in));

	वापस err;
पूर्ण

व्योम mlx5_destroy_encryption_key(काष्ठा mlx5_core_dev *mdev, u32 key_id)
अणु
	u32 in[MLX5_ST_SZ_DW(general_obj_in_cmd_hdr)] = अणुपूर्ण;
	u32 out[MLX5_ST_SZ_DW(general_obj_out_cmd_hdr)];

	MLX5_SET(general_obj_in_cmd_hdr, in, opcode,
		 MLX5_CMD_OP_DESTROY_GENERAL_OBJECT);
	MLX5_SET(general_obj_in_cmd_hdr, in, obj_type,
		 MLX5_GENERAL_OBJECT_TYPES_ENCRYPTION_KEY);
	MLX5_SET(general_obj_in_cmd_hdr, in, obj_id, key_id);

	mlx5_cmd_exec(mdev, in, माप(in), out, माप(out));
पूर्ण
