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

#अगर_अघोषित __MLX5_ACCEL_H__
#घोषणा __MLX5_ACCEL_H__

#समावेश <linux/mlx5/driver.h>

क्रमागत mlx5_accel_esp_aes_gcm_keymat_iv_algo अणु
	MLX5_ACCEL_ESP_AES_GCM_IV_ALGO_SEQ,
पूर्ण;

क्रमागत mlx5_accel_esp_flags अणु
	MLX5_ACCEL_ESP_FLAGS_TUNNEL            = 0,    /* Default */
	MLX5_ACCEL_ESP_FLAGS_TRANSPORT         = 1UL << 0,
	MLX5_ACCEL_ESP_FLAGS_ESN_TRIGGERED     = 1UL << 1,
	MLX5_ACCEL_ESP_FLAGS_ESN_STATE_OVERLAP = 1UL << 2,
पूर्ण;

क्रमागत mlx5_accel_esp_action अणु
	MLX5_ACCEL_ESP_ACTION_DECRYPT,
	MLX5_ACCEL_ESP_ACTION_ENCRYPT,
पूर्ण;

क्रमागत mlx5_accel_esp_keymats अणु
	MLX5_ACCEL_ESP_KEYMAT_AES_NONE,
	MLX5_ACCEL_ESP_KEYMAT_AES_GCM,
पूर्ण;

क्रमागत mlx5_accel_esp_replay अणु
	MLX5_ACCEL_ESP_REPLAY_NONE,
	MLX5_ACCEL_ESP_REPLAY_BMP,
पूर्ण;

काष्ठा aes_gcm_keymat अणु
	u64   seq_iv;
	क्रमागत mlx5_accel_esp_aes_gcm_keymat_iv_algo iv_algo;

	u32   salt;
	u32   icv_len;

	u32   key_len;
	u32   aes_key[256 / 32];
पूर्ण;

काष्ठा mlx5_accel_esp_xfrm_attrs अणु
	क्रमागत mlx5_accel_esp_action action;
	u32   esn;
	__be32 spi;
	u32   seq;
	u32   tfc_pad;
	u32   flags;
	u32   sa_handle;
	क्रमागत mlx5_accel_esp_replay replay_type;
	जोड़ अणु
		काष्ठा अणु
			u32 size;

		पूर्ण bmp;
	पूर्ण replay;
	क्रमागत mlx5_accel_esp_keymats keymat_type;
	जोड़ अणु
		काष्ठा aes_gcm_keymat aes_gcm;
	पूर्ण keymat;

	जोड़ अणु
		__be32 a4;
		__be32 a6[4];
	पूर्ण saddr;

	जोड़ अणु
		__be32 a4;
		__be32 a6[4];
	पूर्ण daddr;

	u8 is_ipv6;
पूर्ण;

काष्ठा mlx5_accel_esp_xfrm अणु
	काष्ठा mlx5_core_dev  *mdev;
	काष्ठा mlx5_accel_esp_xfrm_attrs attrs;
पूर्ण;

क्रमागत अणु
	MLX5_ACCEL_XFRM_FLAG_REQUIRE_METADATA = 1UL << 0,
पूर्ण;

क्रमागत mlx5_accel_ipsec_cap अणु
	MLX5_ACCEL_IPSEC_CAP_DEVICE		= 1 << 0,
	MLX5_ACCEL_IPSEC_CAP_REQUIRED_METADATA	= 1 << 1,
	MLX5_ACCEL_IPSEC_CAP_ESP		= 1 << 2,
	MLX5_ACCEL_IPSEC_CAP_IPV6		= 1 << 3,
	MLX5_ACCEL_IPSEC_CAP_LSO		= 1 << 4,
	MLX5_ACCEL_IPSEC_CAP_RX_NO_TRAILER	= 1 << 5,
	MLX5_ACCEL_IPSEC_CAP_ESN		= 1 << 6,
	MLX5_ACCEL_IPSEC_CAP_TX_IV_IS_ESN	= 1 << 7,
पूर्ण;

#अगर_घोषित CONFIG_MLX5_ACCEL

u32 mlx5_accel_ipsec_device_caps(काष्ठा mlx5_core_dev *mdev);

काष्ठा mlx5_accel_esp_xfrm *
mlx5_accel_esp_create_xfrm(काष्ठा mlx5_core_dev *mdev,
			   स्थिर काष्ठा mlx5_accel_esp_xfrm_attrs *attrs,
			   u32 flags);
व्योम mlx5_accel_esp_destroy_xfrm(काष्ठा mlx5_accel_esp_xfrm *xfrm);
पूर्णांक mlx5_accel_esp_modअगरy_xfrm(काष्ठा mlx5_accel_esp_xfrm *xfrm,
			       स्थिर काष्ठा mlx5_accel_esp_xfrm_attrs *attrs);

#अन्यथा

अटल अंतरभूत u32 mlx5_accel_ipsec_device_caps(काष्ठा mlx5_core_dev *mdev) अणु वापस 0; पूर्ण

अटल अंतरभूत काष्ठा mlx5_accel_esp_xfrm *
mlx5_accel_esp_create_xfrm(काष्ठा mlx5_core_dev *mdev,
			   स्थिर काष्ठा mlx5_accel_esp_xfrm_attrs *attrs,
			   u32 flags) अणु वापस ERR_PTR(-EOPNOTSUPP); पूर्ण
अटल अंतरभूत व्योम
mlx5_accel_esp_destroy_xfrm(काष्ठा mlx5_accel_esp_xfrm *xfrm) अणुपूर्ण
अटल अंतरभूत पूर्णांक
mlx5_accel_esp_modअगरy_xfrm(काष्ठा mlx5_accel_esp_xfrm *xfrm,
			   स्थिर काष्ठा mlx5_accel_esp_xfrm_attrs *attrs) अणु वापस -EOPNOTSUPP; पूर्ण

#पूर्ण_अगर /* CONFIG_MLX5_ACCEL */
#पूर्ण_अगर /* __MLX5_ACCEL_H__ */
