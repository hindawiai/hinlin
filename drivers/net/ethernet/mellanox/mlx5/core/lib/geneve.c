<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/* Copyright (c) 2019 Mellanox Technologies. */

#समावेश <linux/kernel.h>
#समावेश "mlx5_core.h"
#समावेश "geneve.h"

काष्ठा mlx5_geneve अणु
	काष्ठा mlx5_core_dev *mdev;
	__be16 opt_class;
	u8 opt_type;
	u32 obj_id;
	काष्ठा mutex sync_lock; /* protect GENEVE obj operations */
	u32 refcount;
पूर्ण;

अटल पूर्णांक mlx5_geneve_tlv_option_create(काष्ठा mlx5_core_dev *mdev,
					 __be16 class,
					 u8 type,
					 u8 len)
अणु
	u32 in[MLX5_ST_SZ_DW(create_geneve_tlv_option_in)] = अणुपूर्ण;
	u32 out[MLX5_ST_SZ_DW(general_obj_out_cmd_hdr)] = अणुपूर्ण;
	u64 general_obj_types;
	व्योम *hdr, *opt;
	u16 obj_id;
	पूर्णांक err;

	general_obj_types = MLX5_CAP_GEN_64(mdev, general_obj_types);
	अगर (!(general_obj_types & MLX5_GENERAL_OBJ_TYPES_CAP_GENEVE_TLV_OPT))
		वापस -EINVAL;

	hdr = MLX5_ADDR_OF(create_geneve_tlv_option_in, in, hdr);
	opt = MLX5_ADDR_OF(create_geneve_tlv_option_in, in, geneve_tlv_opt);

	MLX5_SET(general_obj_in_cmd_hdr, hdr, opcode, MLX5_CMD_OP_CREATE_GENERAL_OBJECT);
	MLX5_SET(general_obj_in_cmd_hdr, hdr, obj_type, MLX5_OBJ_TYPE_GENEVE_TLV_OPT);

	MLX5_SET(geneve_tlv_option, opt, option_class, be16_to_cpu(class));
	MLX5_SET(geneve_tlv_option, opt, option_type, type);
	MLX5_SET(geneve_tlv_option, opt, option_data_length, len);

	err = mlx5_cmd_exec(mdev, in, माप(in), out, माप(out));
	अगर (err)
		वापस err;

	obj_id = MLX5_GET(general_obj_out_cmd_hdr, out, obj_id);
	वापस obj_id;
पूर्ण

अटल व्योम mlx5_geneve_tlv_option_destroy(काष्ठा mlx5_core_dev *mdev, u16 obj_id)
अणु
	u32 out[MLX5_ST_SZ_DW(general_obj_out_cmd_hdr)] = अणुपूर्ण;
	u32 in[MLX5_ST_SZ_DW(general_obj_in_cmd_hdr)] = अणुपूर्ण;

	MLX5_SET(general_obj_in_cmd_hdr, in, opcode, MLX5_CMD_OP_DESTROY_GENERAL_OBJECT);
	MLX5_SET(general_obj_in_cmd_hdr, in, obj_type, MLX5_OBJ_TYPE_GENEVE_TLV_OPT);
	MLX5_SET(general_obj_in_cmd_hdr, in, obj_id, obj_id);

	mlx5_cmd_exec(mdev, in, माप(in), out, माप(out));
पूर्ण

पूर्णांक mlx5_geneve_tlv_option_add(काष्ठा mlx5_geneve *geneve, काष्ठा geneve_opt *opt)
अणु
	पूर्णांक res = 0;

	अगर (IS_ERR_OR_शून्य(geneve))
		वापस -EOPNOTSUPP;

	mutex_lock(&geneve->sync_lock);

	अगर (geneve->refcount) अणु
		अगर (geneve->opt_class == opt->opt_class &&
		    geneve->opt_type == opt->type) अणु
			/* We alपढ़ोy have TLV options obj allocated */
			geneve->refcount++;
		पूर्ण अन्यथा अणु
			/* TLV options obj allocated, but its params
			 * करो not match the new request.
			 * We support only one such object.
			 */
			mlx5_core_warn(geneve->mdev,
				       "Won't create Geneve TLV opt object with class:type:len = 0x%x:0x%x:%d (another class:type already exists)\n",
				       be16_to_cpu(opt->opt_class),
				       opt->type,
				       opt->length);
			res = -EOPNOTSUPP;
			जाओ unlock;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* We करोn't have any TLV options obj allocated */

		res = mlx5_geneve_tlv_option_create(geneve->mdev,
						    opt->opt_class,
						    opt->type,
						    opt->length);
		अगर (res < 0) अणु
			mlx5_core_warn(geneve->mdev,
				       "Failed creating Geneve TLV opt object class:type:len = 0x%x:0x%x:%d (err=%d)\n",
				       be16_to_cpu(opt->opt_class),
				       opt->type, opt->length, res);
			जाओ unlock;
		पूर्ण
		geneve->opt_class = opt->opt_class;
		geneve->opt_type = opt->type;
		geneve->obj_id = res;
		geneve->refcount++;
	पूर्ण

unlock:
	mutex_unlock(&geneve->sync_lock);
	वापस res;
पूर्ण

व्योम mlx5_geneve_tlv_option_del(काष्ठा mlx5_geneve *geneve)
अणु
	अगर (IS_ERR_OR_शून्य(geneve))
		वापस;

	mutex_lock(&geneve->sync_lock);
	अगर (--geneve->refcount == 0) अणु
		/* We've just हटाओd the last user of Geneve option.
		 * Now delete the object in FW.
		 */
		mlx5_geneve_tlv_option_destroy(geneve->mdev, geneve->obj_id);

		geneve->opt_class = 0;
		geneve->opt_type = 0;
		geneve->obj_id = 0;
	पूर्ण
	mutex_unlock(&geneve->sync_lock);
पूर्ण

काष्ठा mlx5_geneve *mlx5_geneve_create(काष्ठा mlx5_core_dev *mdev)
अणु
	काष्ठा mlx5_geneve *geneve =
		kzalloc(माप(*geneve), GFP_KERNEL);

	अगर (!geneve)
		वापस ERR_PTR(-ENOMEM);
	geneve->mdev = mdev;
	mutex_init(&geneve->sync_lock);

	वापस geneve;
पूर्ण

व्योम mlx5_geneve_destroy(काष्ठा mlx5_geneve *geneve)
अणु
	अगर (IS_ERR_OR_शून्य(geneve))
		वापस;

	/* Lockless since we are unloading */
	अगर (geneve->refcount)
		mlx5_geneve_tlv_option_destroy(geneve->mdev, geneve->obj_id);

	kमुक्त(geneve);
पूर्ण
