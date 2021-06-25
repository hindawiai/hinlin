<शैली गुरु>
/*
 * Copyright (c) 2013-2015, Mellanox Technologies. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mlx5/driver.h>
#समावेश "mlx5_core.h"

पूर्णांक mlx5_core_create_mkey(काष्ठा mlx5_core_dev *dev,
			  काष्ठा mlx5_core_mkey *mkey,
			  u32 *in, पूर्णांक inlen)
अणु
	u32 lout[MLX5_ST_SZ_DW(create_mkey_out)] = अणुपूर्ण;
	u32 mkey_index;
	व्योम *mkc;
	पूर्णांक err;

	MLX5_SET(create_mkey_in, in, opcode, MLX5_CMD_OP_CREATE_MKEY);

	err = mlx5_cmd_exec(dev, in, inlen, lout, माप(lout));
	अगर (err)
		वापस err;

	mkc = MLX5_ADDR_OF(create_mkey_in, in, memory_key_mkey_entry);
	mkey_index = MLX5_GET(create_mkey_out, lout, mkey_index);
	mkey->iova = MLX5_GET64(mkc, mkc, start_addr);
	mkey->size = MLX5_GET64(mkc, mkc, len);
	mkey->key = (u32)mlx5_mkey_variant(mkey->key) | mlx5_idx_to_mkey(mkey_index);
	mkey->pd = MLX5_GET(mkc, mkc, pd);
	init_रुकोqueue_head(&mkey->रुको);

	mlx5_core_dbg(dev, "out 0x%x, mkey 0x%x\n", mkey_index, mkey->key);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(mlx5_core_create_mkey);

पूर्णांक mlx5_core_destroy_mkey(काष्ठा mlx5_core_dev *dev,
			   काष्ठा mlx5_core_mkey *mkey)
अणु
	u32 in[MLX5_ST_SZ_DW(destroy_mkey_in)] = अणुपूर्ण;

	MLX5_SET(destroy_mkey_in, in, opcode, MLX5_CMD_OP_DESTROY_MKEY);
	MLX5_SET(destroy_mkey_in, in, mkey_index, mlx5_mkey_to_idx(mkey->key));
	वापस mlx5_cmd_exec_in(dev, destroy_mkey, in);
पूर्ण
EXPORT_SYMBOL(mlx5_core_destroy_mkey);

पूर्णांक mlx5_core_query_mkey(काष्ठा mlx5_core_dev *dev, काष्ठा mlx5_core_mkey *mkey,
			 u32 *out, पूर्णांक outlen)
अणु
	u32 in[MLX5_ST_SZ_DW(query_mkey_in)] = अणुपूर्ण;

	स_रखो(out, 0, outlen);
	MLX5_SET(query_mkey_in, in, opcode, MLX5_CMD_OP_QUERY_MKEY);
	MLX5_SET(query_mkey_in, in, mkey_index, mlx5_mkey_to_idx(mkey->key));
	वापस mlx5_cmd_exec(dev, in, माप(in), out, outlen);
पूर्ण
EXPORT_SYMBOL(mlx5_core_query_mkey);

अटल अंतरभूत u32 mlx5_get_psv(u32 *out, पूर्णांक psv_index)
अणु
	चयन (psv_index) अणु
	हाल 1: वापस MLX5_GET(create_psv_out, out, psv1_index);
	हाल 2: वापस MLX5_GET(create_psv_out, out, psv2_index);
	हाल 3: वापस MLX5_GET(create_psv_out, out, psv3_index);
	शेष: वापस MLX5_GET(create_psv_out, out, psv0_index);
	पूर्ण
पूर्ण

पूर्णांक mlx5_core_create_psv(काष्ठा mlx5_core_dev *dev, u32 pdn,
			 पूर्णांक npsvs, u32 *sig_index)
अणु
	u32 out[MLX5_ST_SZ_DW(create_psv_out)] = अणुपूर्ण;
	u32 in[MLX5_ST_SZ_DW(create_psv_in)] = अणुपूर्ण;
	पूर्णांक i, err;

	अगर (npsvs > MLX5_MAX_PSVS)
		वापस -EINVAL;

	MLX5_SET(create_psv_in, in, opcode, MLX5_CMD_OP_CREATE_PSV);
	MLX5_SET(create_psv_in, in, pd, pdn);
	MLX5_SET(create_psv_in, in, num_psv, npsvs);

	err = mlx5_cmd_exec_inout(dev, create_psv, in, out);
	अगर (err)
		वापस err;

	क्रम (i = 0; i < npsvs; i++)
		sig_index[i] = mlx5_get_psv(out, i);

	वापस err;
पूर्ण
EXPORT_SYMBOL(mlx5_core_create_psv);

पूर्णांक mlx5_core_destroy_psv(काष्ठा mlx5_core_dev *dev, पूर्णांक psv_num)
अणु
	u32 in[MLX5_ST_SZ_DW(destroy_psv_in)] = अणुपूर्ण;

	MLX5_SET(destroy_psv_in, in, opcode, MLX5_CMD_OP_DESTROY_PSV);
	MLX5_SET(destroy_psv_in, in, psvn, psv_num);
	वापस mlx5_cmd_exec_in(dev, destroy_psv, in);
पूर्ण
EXPORT_SYMBOL(mlx5_core_destroy_psv);
