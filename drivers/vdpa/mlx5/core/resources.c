<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/* Copyright (c) 2020 Mellanox Technologies Ltd. */

#समावेश <linux/mlx5/driver.h>
#समावेश "mlx5_vdpa.h"

अटल पूर्णांक alloc_pd(काष्ठा mlx5_vdpa_dev *dev, u32 *pdn, u16 uid)
अणु
	काष्ठा mlx5_core_dev *mdev = dev->mdev;

	u32 out[MLX5_ST_SZ_DW(alloc_pd_out)] = अणुपूर्ण;
	u32 in[MLX5_ST_SZ_DW(alloc_pd_in)] = अणुपूर्ण;
	पूर्णांक err;

	MLX5_SET(alloc_pd_in, in, opcode, MLX5_CMD_OP_ALLOC_PD);
	MLX5_SET(alloc_pd_in, in, uid, uid);

	err = mlx5_cmd_exec_inout(mdev, alloc_pd, in, out);
	अगर (!err)
		*pdn = MLX5_GET(alloc_pd_out, out, pd);

	वापस err;
पूर्ण

अटल पूर्णांक dealloc_pd(काष्ठा mlx5_vdpa_dev *dev, u32 pdn, u16 uid)
अणु
	u32 in[MLX5_ST_SZ_DW(dealloc_pd_in)] = अणुपूर्ण;
	काष्ठा mlx5_core_dev *mdev = dev->mdev;

	MLX5_SET(dealloc_pd_in, in, opcode, MLX5_CMD_OP_DEALLOC_PD);
	MLX5_SET(dealloc_pd_in, in, pd, pdn);
	MLX5_SET(dealloc_pd_in, in, uid, uid);
	वापस mlx5_cmd_exec_in(mdev, dealloc_pd, in);
पूर्ण

अटल पूर्णांक get_null_mkey(काष्ठा mlx5_vdpa_dev *dev, u32 *null_mkey)
अणु
	u32 out[MLX5_ST_SZ_DW(query_special_contexts_out)] = अणुपूर्ण;
	u32 in[MLX5_ST_SZ_DW(query_special_contexts_in)] = अणुपूर्ण;
	काष्ठा mlx5_core_dev *mdev = dev->mdev;
	पूर्णांक err;

	MLX5_SET(query_special_contexts_in, in, opcode, MLX5_CMD_OP_QUERY_SPECIAL_CONTEXTS);
	err = mlx5_cmd_exec_inout(mdev, query_special_contexts, in, out);
	अगर (!err)
		*null_mkey = MLX5_GET(query_special_contexts_out, out, null_mkey);
	वापस err;
पूर्ण

अटल पूर्णांक create_uctx(काष्ठा mlx5_vdpa_dev *mvdev, u16 *uid)
अणु
	u32 out[MLX5_ST_SZ_DW(create_uctx_out)] = अणुपूर्ण;
	पूर्णांक inlen;
	व्योम *in;
	पूर्णांक err;

	/* 0 means not supported */
	अगर (!MLX5_CAP_GEN(mvdev->mdev, log_max_uctx))
		वापस -EOPNOTSUPP;

	inlen = MLX5_ST_SZ_BYTES(create_uctx_in);
	in = kzalloc(inlen, GFP_KERNEL);
	अगर (!in)
		वापस -ENOMEM;

	MLX5_SET(create_uctx_in, in, opcode, MLX5_CMD_OP_CREATE_UCTX);
	MLX5_SET(create_uctx_in, in, uctx.cap, MLX5_UCTX_CAP_RAW_TX);

	err = mlx5_cmd_exec(mvdev->mdev, in, inlen, out, माप(out));
	kमुक्त(in);
	अगर (!err)
		*uid = MLX5_GET(create_uctx_out, out, uid);

	वापस err;
पूर्ण

अटल व्योम destroy_uctx(काष्ठा mlx5_vdpa_dev *mvdev, u32 uid)
अणु
	u32 out[MLX5_ST_SZ_DW(destroy_uctx_out)] = अणुपूर्ण;
	u32 in[MLX5_ST_SZ_DW(destroy_uctx_in)] = अणुपूर्ण;

	MLX5_SET(destroy_uctx_in, in, opcode, MLX5_CMD_OP_DESTROY_UCTX);
	MLX5_SET(destroy_uctx_in, in, uid, uid);

	mlx5_cmd_exec(mvdev->mdev, in, माप(in), out, माप(out));
पूर्ण

पूर्णांक mlx5_vdpa_create_tis(काष्ठा mlx5_vdpa_dev *mvdev, व्योम *in, u32 *tisn)
अणु
	u32 out[MLX5_ST_SZ_DW(create_tis_out)] = अणुपूर्ण;
	पूर्णांक err;

	MLX5_SET(create_tis_in, in, opcode, MLX5_CMD_OP_CREATE_TIS);
	MLX5_SET(create_tis_in, in, uid, mvdev->res.uid);
	err = mlx5_cmd_exec_inout(mvdev->mdev, create_tis, in, out);
	अगर (!err)
		*tisn = MLX5_GET(create_tis_out, out, tisn);

	वापस err;
पूर्ण

व्योम mlx5_vdpa_destroy_tis(काष्ठा mlx5_vdpa_dev *mvdev, u32 tisn)
अणु
	u32 in[MLX5_ST_SZ_DW(destroy_tis_in)] = अणुपूर्ण;

	MLX5_SET(destroy_tis_in, in, opcode, MLX5_CMD_OP_DESTROY_TIS);
	MLX5_SET(destroy_tis_in, in, uid, mvdev->res.uid);
	MLX5_SET(destroy_tis_in, in, tisn, tisn);
	mlx5_cmd_exec_in(mvdev->mdev, destroy_tis, in);
पूर्ण

पूर्णांक mlx5_vdpa_create_rqt(काष्ठा mlx5_vdpa_dev *mvdev, व्योम *in, पूर्णांक inlen, u32 *rqtn)
अणु
	u32 out[MLX5_ST_SZ_DW(create_rqt_out)] = अणुपूर्ण;
	पूर्णांक err;

	MLX5_SET(create_rqt_in, in, opcode, MLX5_CMD_OP_CREATE_RQT);
	err = mlx5_cmd_exec(mvdev->mdev, in, inlen, out, माप(out));
	अगर (!err)
		*rqtn = MLX5_GET(create_rqt_out, out, rqtn);

	वापस err;
पूर्ण

व्योम mlx5_vdpa_destroy_rqt(काष्ठा mlx5_vdpa_dev *mvdev, u32 rqtn)
अणु
	u32 in[MLX5_ST_SZ_DW(destroy_rqt_in)] = अणुपूर्ण;

	MLX5_SET(destroy_rqt_in, in, opcode, MLX5_CMD_OP_DESTROY_RQT);
	MLX5_SET(destroy_rqt_in, in, uid, mvdev->res.uid);
	MLX5_SET(destroy_rqt_in, in, rqtn, rqtn);
	mlx5_cmd_exec_in(mvdev->mdev, destroy_rqt, in);
पूर्ण

पूर्णांक mlx5_vdpa_create_tir(काष्ठा mlx5_vdpa_dev *mvdev, व्योम *in, u32 *tirn)
अणु
	u32 out[MLX5_ST_SZ_DW(create_tir_out)] = अणुपूर्ण;
	पूर्णांक err;

	MLX5_SET(create_tir_in, in, opcode, MLX5_CMD_OP_CREATE_TIR);
	err = mlx5_cmd_exec_inout(mvdev->mdev, create_tir, in, out);
	अगर (!err)
		*tirn = MLX5_GET(create_tir_out, out, tirn);

	वापस err;
पूर्ण

व्योम mlx5_vdpa_destroy_tir(काष्ठा mlx5_vdpa_dev *mvdev, u32 tirn)
अणु
	u32 in[MLX5_ST_SZ_DW(destroy_tir_in)] = अणुपूर्ण;

	MLX5_SET(destroy_tir_in, in, opcode, MLX5_CMD_OP_DESTROY_TIR);
	MLX5_SET(destroy_tir_in, in, uid, mvdev->res.uid);
	MLX5_SET(destroy_tir_in, in, tirn, tirn);
	mlx5_cmd_exec_in(mvdev->mdev, destroy_tir, in);
पूर्ण

पूर्णांक mlx5_vdpa_alloc_transport_करोमुख्य(काष्ठा mlx5_vdpa_dev *mvdev, u32 *tdn)
अणु
	u32 out[MLX5_ST_SZ_DW(alloc_transport_करोमुख्य_out)] = अणुपूर्ण;
	u32 in[MLX5_ST_SZ_DW(alloc_transport_करोमुख्य_in)] = अणुपूर्ण;
	पूर्णांक err;

	MLX5_SET(alloc_transport_करोमुख्य_in, in, opcode, MLX5_CMD_OP_ALLOC_TRANSPORT_DOMAIN);
	MLX5_SET(alloc_transport_करोमुख्य_in, in, uid, mvdev->res.uid);

	err = mlx5_cmd_exec_inout(mvdev->mdev, alloc_transport_करोमुख्य, in, out);
	अगर (!err)
		*tdn = MLX5_GET(alloc_transport_करोमुख्य_out, out, transport_करोमुख्य);

	वापस err;
पूर्ण

व्योम mlx5_vdpa_dealloc_transport_करोमुख्य(काष्ठा mlx5_vdpa_dev *mvdev, u32 tdn)
अणु
	u32 in[MLX5_ST_SZ_DW(dealloc_transport_करोमुख्य_in)] = अणुपूर्ण;

	MLX5_SET(dealloc_transport_करोमुख्य_in, in, opcode, MLX5_CMD_OP_DEALLOC_TRANSPORT_DOMAIN);
	MLX5_SET(dealloc_transport_करोमुख्य_in, in, uid, mvdev->res.uid);
	MLX5_SET(dealloc_transport_करोमुख्य_in, in, transport_करोमुख्य, tdn);
	mlx5_cmd_exec_in(mvdev->mdev, dealloc_transport_करोमुख्य, in);
पूर्ण

पूर्णांक mlx5_vdpa_create_mkey(काष्ठा mlx5_vdpa_dev *mvdev, काष्ठा mlx5_core_mkey *mkey, u32 *in,
			  पूर्णांक inlen)
अणु
	u32 lout[MLX5_ST_SZ_DW(create_mkey_out)] = अणुपूर्ण;
	u32 mkey_index;
	व्योम *mkc;
	पूर्णांक err;

	MLX5_SET(create_mkey_in, in, opcode, MLX5_CMD_OP_CREATE_MKEY);
	MLX5_SET(create_mkey_in, in, uid, mvdev->res.uid);

	err = mlx5_cmd_exec(mvdev->mdev, in, inlen, lout, माप(lout));
	अगर (err)
		वापस err;

	mkc = MLX5_ADDR_OF(create_mkey_in, in, memory_key_mkey_entry);
	mkey_index = MLX5_GET(create_mkey_out, lout, mkey_index);
	mkey->iova = MLX5_GET64(mkc, mkc, start_addr);
	mkey->size = MLX5_GET64(mkc, mkc, len);
	mkey->key |= mlx5_idx_to_mkey(mkey_index);
	mkey->pd = MLX5_GET(mkc, mkc, pd);
	वापस 0;
पूर्ण

पूर्णांक mlx5_vdpa_destroy_mkey(काष्ठा mlx5_vdpa_dev *mvdev, काष्ठा mlx5_core_mkey *mkey)
अणु
	u32 in[MLX5_ST_SZ_DW(destroy_mkey_in)] = अणुपूर्ण;

	MLX5_SET(destroy_mkey_in, in, uid, mvdev->res.uid);
	MLX5_SET(destroy_mkey_in, in, opcode, MLX5_CMD_OP_DESTROY_MKEY);
	MLX5_SET(destroy_mkey_in, in, mkey_index, mlx5_mkey_to_idx(mkey->key));
	वापस mlx5_cmd_exec_in(mvdev->mdev, destroy_mkey, in);
पूर्ण

पूर्णांक mlx5_vdpa_alloc_resources(काष्ठा mlx5_vdpa_dev *mvdev)
अणु
	u64 offset = MLX5_CAP64_DEV_VDPA_EMULATION(mvdev->mdev, करोorbell_bar_offset);
	काष्ठा mlx5_vdpa_resources *res = &mvdev->res;
	काष्ठा mlx5_core_dev *mdev = mvdev->mdev;
	u64 kick_addr;
	पूर्णांक err;

	अगर (res->valid) अणु
		mlx5_vdpa_warn(mvdev, "resources already allocated\n");
		वापस -EINVAL;
	पूर्ण
	mutex_init(&mvdev->mr.mkey_mtx);
	res->uar = mlx5_get_uars_page(mdev);
	अगर (IS_ERR(res->uar)) अणु
		err = PTR_ERR(res->uar);
		जाओ err_uars;
	पूर्ण

	err = create_uctx(mvdev, &res->uid);
	अगर (err)
		जाओ err_uctx;

	err = alloc_pd(mvdev, &res->pdn, res->uid);
	अगर (err)
		जाओ err_pd;

	err = get_null_mkey(mvdev, &res->null_mkey);
	अगर (err)
		जाओ err_key;

	kick_addr = mdev->bar_addr + offset;

	res->kick_addr = ioremap(kick_addr, PAGE_SIZE);
	अगर (!res->kick_addr) अणु
		err = -ENOMEM;
		जाओ err_key;
	पूर्ण
	res->valid = true;

	वापस 0;

err_key:
	dealloc_pd(mvdev, res->pdn, res->uid);
err_pd:
	destroy_uctx(mvdev, res->uid);
err_uctx:
	mlx5_put_uars_page(mdev, res->uar);
err_uars:
	mutex_destroy(&mvdev->mr.mkey_mtx);
	वापस err;
पूर्ण

व्योम mlx5_vdpa_मुक्त_resources(काष्ठा mlx5_vdpa_dev *mvdev)
अणु
	काष्ठा mlx5_vdpa_resources *res = &mvdev->res;

	अगर (!res->valid)
		वापस;

	iounmap(res->kick_addr);
	res->kick_addr = शून्य;
	dealloc_pd(mvdev, res->pdn, res->uid);
	destroy_uctx(mvdev, res->uid);
	mlx5_put_uars_page(mvdev->mdev, res->uar);
	mutex_destroy(&mvdev->mr.mkey_mtx);
	res->valid = false;
पूर्ण
