<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/*
 * Copyright (c) 2017-2020, Mellanox Technologies inc. All rights reserved.
 */

#समावेश "cmd.h"

पूर्णांक mlx5_cmd_dump_fill_mkey(काष्ठा mlx5_core_dev *dev, u32 *mkey)
अणु
	u32 out[MLX5_ST_SZ_DW(query_special_contexts_out)] = अणुपूर्ण;
	u32 in[MLX5_ST_SZ_DW(query_special_contexts_in)] = अणुपूर्ण;
	पूर्णांक err;

	MLX5_SET(query_special_contexts_in, in, opcode,
		 MLX5_CMD_OP_QUERY_SPECIAL_CONTEXTS);
	err = mlx5_cmd_exec_inout(dev, query_special_contexts, in, out);
	अगर (!err)
		*mkey = MLX5_GET(query_special_contexts_out, out,
				 dump_fill_mkey);
	वापस err;
पूर्ण

पूर्णांक mlx5_cmd_null_mkey(काष्ठा mlx5_core_dev *dev, u32 *null_mkey)
अणु
	u32 out[MLX5_ST_SZ_DW(query_special_contexts_out)] = अणुपूर्ण;
	u32 in[MLX5_ST_SZ_DW(query_special_contexts_in)] = अणुपूर्ण;
	पूर्णांक err;

	MLX5_SET(query_special_contexts_in, in, opcode,
		 MLX5_CMD_OP_QUERY_SPECIAL_CONTEXTS);
	err = mlx5_cmd_exec_inout(dev, query_special_contexts, in, out);
	अगर (!err)
		*null_mkey = MLX5_GET(query_special_contexts_out, out,
				      null_mkey);
	वापस err;
पूर्ण

पूर्णांक mlx5_cmd_query_cong_params(काष्ठा mlx5_core_dev *dev, पूर्णांक cong_poपूर्णांक,
			       व्योम *out)
अणु
	u32 in[MLX5_ST_SZ_DW(query_cong_params_in)] = अणुपूर्ण;

	MLX5_SET(query_cong_params_in, in, opcode,
		 MLX5_CMD_OP_QUERY_CONG_PARAMS);
	MLX5_SET(query_cong_params_in, in, cong_protocol, cong_poपूर्णांक);

	वापस mlx5_cmd_exec_inout(dev, query_cong_params, in, out);
पूर्ण

व्योम mlx5_cmd_destroy_tir(काष्ठा mlx5_core_dev *dev, u32 tirn, u16 uid)
अणु
	u32 in[MLX5_ST_SZ_DW(destroy_tir_in)] = अणुपूर्ण;

	MLX5_SET(destroy_tir_in, in, opcode, MLX5_CMD_OP_DESTROY_TIR);
	MLX5_SET(destroy_tir_in, in, tirn, tirn);
	MLX5_SET(destroy_tir_in, in, uid, uid);
	mlx5_cmd_exec_in(dev, destroy_tir, in);
पूर्ण

व्योम mlx5_cmd_destroy_tis(काष्ठा mlx5_core_dev *dev, u32 tisn, u16 uid)
अणु
	u32 in[MLX5_ST_SZ_DW(destroy_tis_in)] = अणुपूर्ण;

	MLX5_SET(destroy_tis_in, in, opcode, MLX5_CMD_OP_DESTROY_TIS);
	MLX5_SET(destroy_tis_in, in, tisn, tisn);
	MLX5_SET(destroy_tis_in, in, uid, uid);
	mlx5_cmd_exec_in(dev, destroy_tis, in);
पूर्ण

पूर्णांक mlx5_cmd_destroy_rqt(काष्ठा mlx5_core_dev *dev, u32 rqtn, u16 uid)
अणु
	u32 in[MLX5_ST_SZ_DW(destroy_rqt_in)] = अणुपूर्ण;

	MLX5_SET(destroy_rqt_in, in, opcode, MLX5_CMD_OP_DESTROY_RQT);
	MLX5_SET(destroy_rqt_in, in, rqtn, rqtn);
	MLX5_SET(destroy_rqt_in, in, uid, uid);
	वापस mlx5_cmd_exec_in(dev, destroy_rqt, in);
पूर्ण

पूर्णांक mlx5_cmd_alloc_transport_करोमुख्य(काष्ठा mlx5_core_dev *dev, u32 *tdn,
				    u16 uid)
अणु
	u32 in[MLX5_ST_SZ_DW(alloc_transport_करोमुख्य_in)] = अणुपूर्ण;
	u32 out[MLX5_ST_SZ_DW(alloc_transport_करोमुख्य_out)] = अणुपूर्ण;
	पूर्णांक err;

	MLX5_SET(alloc_transport_करोमुख्य_in, in, opcode,
		 MLX5_CMD_OP_ALLOC_TRANSPORT_DOMAIN);
	MLX5_SET(alloc_transport_करोमुख्य_in, in, uid, uid);

	err = mlx5_cmd_exec_inout(dev, alloc_transport_करोमुख्य, in, out);
	अगर (!err)
		*tdn = MLX5_GET(alloc_transport_करोमुख्य_out, out,
				transport_करोमुख्य);

	वापस err;
पूर्ण

व्योम mlx5_cmd_dealloc_transport_करोमुख्य(काष्ठा mlx5_core_dev *dev, u32 tdn,
				       u16 uid)
अणु
	u32 in[MLX5_ST_SZ_DW(dealloc_transport_करोमुख्य_in)] = अणुपूर्ण;

	MLX5_SET(dealloc_transport_करोमुख्य_in, in, opcode,
		 MLX5_CMD_OP_DEALLOC_TRANSPORT_DOMAIN);
	MLX5_SET(dealloc_transport_करोमुख्य_in, in, uid, uid);
	MLX5_SET(dealloc_transport_करोमुख्य_in, in, transport_करोमुख्य, tdn);
	mlx5_cmd_exec_in(dev, dealloc_transport_करोमुख्य, in);
पूर्ण

पूर्णांक mlx5_cmd_dealloc_pd(काष्ठा mlx5_core_dev *dev, u32 pdn, u16 uid)
अणु
	u32 in[MLX5_ST_SZ_DW(dealloc_pd_in)] = अणुपूर्ण;

	MLX5_SET(dealloc_pd_in, in, opcode, MLX5_CMD_OP_DEALLOC_PD);
	MLX5_SET(dealloc_pd_in, in, pd, pdn);
	MLX5_SET(dealloc_pd_in, in, uid, uid);
	वापस mlx5_cmd_exec_in(dev, dealloc_pd, in);
पूर्ण

पूर्णांक mlx5_cmd_attach_mcg(काष्ठा mlx5_core_dev *dev, जोड़ ib_gid *mgid,
			u32 qpn, u16 uid)
अणु
	u32 in[MLX5_ST_SZ_DW(attach_to_mcg_in)] = अणुपूर्ण;
	व्योम *gid;

	MLX5_SET(attach_to_mcg_in, in, opcode, MLX5_CMD_OP_ATTACH_TO_MCG);
	MLX5_SET(attach_to_mcg_in, in, qpn, qpn);
	MLX5_SET(attach_to_mcg_in, in, uid, uid);
	gid = MLX5_ADDR_OF(attach_to_mcg_in, in, multicast_gid);
	स_नकल(gid, mgid, माप(*mgid));
	वापस mlx5_cmd_exec_in(dev, attach_to_mcg, in);
पूर्ण

पूर्णांक mlx5_cmd_detach_mcg(काष्ठा mlx5_core_dev *dev, जोड़ ib_gid *mgid,
			u32 qpn, u16 uid)
अणु
	u32 in[MLX5_ST_SZ_DW(detach_from_mcg_in)] = अणुपूर्ण;
	व्योम *gid;

	MLX5_SET(detach_from_mcg_in, in, opcode, MLX5_CMD_OP_DETACH_FROM_MCG);
	MLX5_SET(detach_from_mcg_in, in, qpn, qpn);
	MLX5_SET(detach_from_mcg_in, in, uid, uid);
	gid = MLX5_ADDR_OF(detach_from_mcg_in, in, multicast_gid);
	स_नकल(gid, mgid, माप(*mgid));
	वापस mlx5_cmd_exec_in(dev, detach_from_mcg, in);
पूर्ण

पूर्णांक mlx5_cmd_xrcd_alloc(काष्ठा mlx5_core_dev *dev, u32 *xrcdn, u16 uid)
अणु
	u32 out[MLX5_ST_SZ_DW(alloc_xrcd_out)] = अणुपूर्ण;
	u32 in[MLX5_ST_SZ_DW(alloc_xrcd_in)] = अणुपूर्ण;
	पूर्णांक err;

	MLX5_SET(alloc_xrcd_in, in, opcode, MLX5_CMD_OP_ALLOC_XRCD);
	MLX5_SET(alloc_xrcd_in, in, uid, uid);
	err = mlx5_cmd_exec_inout(dev, alloc_xrcd, in, out);
	अगर (!err)
		*xrcdn = MLX5_GET(alloc_xrcd_out, out, xrcd);
	वापस err;
पूर्ण

पूर्णांक mlx5_cmd_xrcd_dealloc(काष्ठा mlx5_core_dev *dev, u32 xrcdn, u16 uid)
अणु
	u32 in[MLX5_ST_SZ_DW(dealloc_xrcd_in)] = अणुपूर्ण;

	MLX5_SET(dealloc_xrcd_in, in, opcode, MLX5_CMD_OP_DEALLOC_XRCD);
	MLX5_SET(dealloc_xrcd_in, in, xrcd, xrcdn);
	MLX5_SET(dealloc_xrcd_in, in, uid, uid);
	वापस mlx5_cmd_exec_in(dev, dealloc_xrcd, in);
पूर्ण

पूर्णांक mlx5_cmd_mad_अगरc(काष्ठा mlx5_core_dev *dev, स्थिर व्योम *inb, व्योम *outb,
		     u16 opmod, u8 port)
अणु
	पूर्णांक outlen = MLX5_ST_SZ_BYTES(mad_अगरc_out);
	पूर्णांक inlen = MLX5_ST_SZ_BYTES(mad_अगरc_in);
	पूर्णांक err = -ENOMEM;
	व्योम *data;
	व्योम *resp;
	u32 *out;
	u32 *in;

	in = kzalloc(inlen, GFP_KERNEL);
	out = kzalloc(outlen, GFP_KERNEL);
	अगर (!in || !out)
		जाओ out;

	MLX5_SET(mad_अगरc_in, in, opcode, MLX5_CMD_OP_MAD_IFC);
	MLX5_SET(mad_अगरc_in, in, op_mod, opmod);
	MLX5_SET(mad_अगरc_in, in, port, port);

	data = MLX5_ADDR_OF(mad_अगरc_in, in, mad);
	स_नकल(data, inb, MLX5_FLD_SZ_BYTES(mad_अगरc_in, mad));

	err = mlx5_cmd_exec_inout(dev, mad_अगरc, in, out);
	अगर (err)
		जाओ out;

	resp = MLX5_ADDR_OF(mad_अगरc_out, out, response_mad_packet);
	स_नकल(outb, resp,
	       MLX5_FLD_SZ_BYTES(mad_अगरc_out, response_mad_packet));

out:
	kमुक्त(out);
	kमुक्त(in);
	वापस err;
पूर्ण
