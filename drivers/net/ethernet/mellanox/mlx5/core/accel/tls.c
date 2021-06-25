<शैली गुरु>
/*
 * Copyright (c) 2018 Mellanox Technologies. All rights reserved.
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
 *
 */

#समावेश <linux/mlx5/device.h>

#समावेश "accel/tls.h"
#समावेश "mlx5_core.h"
#समावेश "lib/mlx5.h"

#अगर_घोषित CONFIG_MLX5_FPGA_TLS
#समावेश "fpga/tls.h"

पूर्णांक mlx5_accel_tls_add_flow(काष्ठा mlx5_core_dev *mdev, व्योम *flow,
			    काष्ठा tls_crypto_info *crypto_info,
			    u32 start_offload_tcp_sn, u32 *p_swid,
			    bool direction_sx)
अणु
	वापस mlx5_fpga_tls_add_flow(mdev, flow, crypto_info,
				      start_offload_tcp_sn, p_swid,
				      direction_sx);
पूर्ण

व्योम mlx5_accel_tls_del_flow(काष्ठा mlx5_core_dev *mdev, u32 swid,
			     bool direction_sx)
अणु
	mlx5_fpga_tls_del_flow(mdev, swid, GFP_KERNEL, direction_sx);
पूर्ण

पूर्णांक mlx5_accel_tls_resync_rx(काष्ठा mlx5_core_dev *mdev, __be32 handle,
			     u32 seq, __be64 rcd_sn)
अणु
	वापस mlx5_fpga_tls_resync_rx(mdev, handle, seq, rcd_sn);
पूर्ण

bool mlx5_accel_is_tls_device(काष्ठा mlx5_core_dev *mdev)
अणु
	वापस mlx5_fpga_is_tls_device(mdev) ||
		mlx5_accel_is_ktls_device(mdev);
पूर्ण

u32 mlx5_accel_tls_device_caps(काष्ठा mlx5_core_dev *mdev)
अणु
	वापस mlx5_fpga_tls_device_caps(mdev);
पूर्ण

पूर्णांक mlx5_accel_tls_init(काष्ठा mlx5_core_dev *mdev)
अणु
	वापस mlx5_fpga_tls_init(mdev);
पूर्ण

व्योम mlx5_accel_tls_cleanup(काष्ठा mlx5_core_dev *mdev)
अणु
	mlx5_fpga_tls_cleanup(mdev);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_MLX5_TLS
पूर्णांक mlx5_ktls_create_key(काष्ठा mlx5_core_dev *mdev,
			 काष्ठा tls_crypto_info *crypto_info,
			 u32 *p_key_id)
अणु
	u32 sz_bytes;
	व्योम *key;

	चयन (crypto_info->cipher_type) अणु
	हाल TLS_CIPHER_AES_GCM_128: अणु
		काष्ठा tls12_crypto_info_aes_gcm_128 *info =
			(काष्ठा tls12_crypto_info_aes_gcm_128 *)crypto_info;

		key      = info->key;
		sz_bytes = माप(info->key);
		अवरोध;
	पूर्ण
	हाल TLS_CIPHER_AES_GCM_256: अणु
		काष्ठा tls12_crypto_info_aes_gcm_256 *info =
			(काष्ठा tls12_crypto_info_aes_gcm_256 *)crypto_info;

		key      = info->key;
		sz_bytes = माप(info->key);
		अवरोध;
	पूर्ण
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस mlx5_create_encryption_key(mdev, key, sz_bytes,
					  MLX5_ACCEL_OBJ_TLS_KEY,
					  p_key_id);
पूर्ण

व्योम mlx5_ktls_destroy_key(काष्ठा mlx5_core_dev *mdev, u32 key_id)
अणु
	mlx5_destroy_encryption_key(mdev, key_id);
पूर्ण
#पूर्ण_अगर
