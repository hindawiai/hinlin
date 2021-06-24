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

#अगर_अघोषित __MLX5_ACCEL_TLS_H__
#घोषणा __MLX5_ACCEL_TLS_H__

#समावेश <linux/mlx5/driver.h>
#समावेश <linux/tls.h>

#अगर_घोषित CONFIG_MLX5_TLS
पूर्णांक mlx5_ktls_create_key(काष्ठा mlx5_core_dev *mdev,
			 काष्ठा tls_crypto_info *crypto_info,
			 u32 *p_key_id);
व्योम mlx5_ktls_destroy_key(काष्ठा mlx5_core_dev *mdev, u32 key_id);

अटल अंतरभूत bool mlx5_accel_is_ktls_tx(काष्ठा mlx5_core_dev *mdev)
अणु
	वापस MLX5_CAP_GEN(mdev, tls_tx);
पूर्ण

अटल अंतरभूत bool mlx5_accel_is_ktls_rx(काष्ठा mlx5_core_dev *mdev)
अणु
	वापस MLX5_CAP_GEN(mdev, tls_rx);
पूर्ण

अटल अंतरभूत bool mlx5_accel_is_ktls_device(काष्ठा mlx5_core_dev *mdev)
अणु
	अगर (!mlx5_accel_is_ktls_tx(mdev) &&
	    !mlx5_accel_is_ktls_rx(mdev))
		वापस false;

	अगर (!MLX5_CAP_GEN(mdev, log_max_dek))
		वापस false;

	वापस MLX5_CAP_TLS(mdev, tls_1_2_aes_gcm_128);
पूर्ण

अटल अंतरभूत bool mlx5e_ktls_type_check(काष्ठा mlx5_core_dev *mdev,
					 काष्ठा tls_crypto_info *crypto_info)
अणु
	चयन (crypto_info->cipher_type) अणु
	हाल TLS_CIPHER_AES_GCM_128:
		अगर (crypto_info->version == TLS_1_2_VERSION)
			वापस MLX5_CAP_TLS(mdev,  tls_1_2_aes_gcm_128);
		अवरोध;
	पूर्ण

	वापस false;
पूर्ण
#अन्यथा
अटल अंतरभूत bool mlx5_accel_is_ktls_tx(काष्ठा mlx5_core_dev *mdev)
अणु वापस false; पूर्ण

अटल अंतरभूत bool mlx5_accel_is_ktls_rx(काष्ठा mlx5_core_dev *mdev)
अणु वापस false; पूर्ण

अटल अंतरभूत पूर्णांक
mlx5_ktls_create_key(काष्ठा mlx5_core_dev *mdev,
		     काष्ठा tls_crypto_info *crypto_info,
		     u32 *p_key_id) अणु वापस -ENOTSUPP; पूर्ण
अटल अंतरभूत व्योम
mlx5_ktls_destroy_key(काष्ठा mlx5_core_dev *mdev, u32 key_id) अणुपूर्ण

अटल अंतरभूत bool
mlx5_accel_is_ktls_device(काष्ठा mlx5_core_dev *mdev) अणु वापस false; पूर्ण
अटल अंतरभूत bool
mlx5e_ktls_type_check(काष्ठा mlx5_core_dev *mdev,
		      काष्ठा tls_crypto_info *crypto_info) अणु वापस false; पूर्ण
#पूर्ण_अगर

क्रमागत अणु
	MLX5_ACCEL_TLS_TX = BIT(0),
	MLX5_ACCEL_TLS_RX = BIT(1),
	MLX5_ACCEL_TLS_V12 = BIT(2),
	MLX5_ACCEL_TLS_V13 = BIT(3),
	MLX5_ACCEL_TLS_LRO = BIT(4),
	MLX5_ACCEL_TLS_IPV6 = BIT(5),
	MLX5_ACCEL_TLS_AES_GCM128 = BIT(30),
	MLX5_ACCEL_TLS_AES_GCM256 = BIT(31),
पूर्ण;

काष्ठा mlx5_अगरc_tls_flow_bits अणु
	u8         src_port[0x10];
	u8         dst_port[0x10];
	जोड़ mlx5_अगरc_ipv6_layout_ipv4_layout_स्वतः_bits src_ipv4_src_ipv6;
	जोड़ mlx5_अगरc_ipv6_layout_ipv4_layout_स्वतः_bits dst_ipv4_dst_ipv6;
	u8         ipv6[0x1];
	u8         direction_sx[0x1];
	u8         reserved_at_2[0x1e];
पूर्ण;

#अगर_घोषित CONFIG_MLX5_FPGA_TLS
पूर्णांक mlx5_accel_tls_add_flow(काष्ठा mlx5_core_dev *mdev, व्योम *flow,
			    काष्ठा tls_crypto_info *crypto_info,
			    u32 start_offload_tcp_sn, u32 *p_swid,
			    bool direction_sx);
व्योम mlx5_accel_tls_del_flow(काष्ठा mlx5_core_dev *mdev, u32 swid,
			     bool direction_sx);
पूर्णांक mlx5_accel_tls_resync_rx(काष्ठा mlx5_core_dev *mdev, __be32 handle,
			     u32 seq, __be64 rcd_sn);
bool mlx5_accel_is_tls_device(काष्ठा mlx5_core_dev *mdev);
u32 mlx5_accel_tls_device_caps(काष्ठा mlx5_core_dev *mdev);
पूर्णांक mlx5_accel_tls_init(काष्ठा mlx5_core_dev *mdev);
व्योम mlx5_accel_tls_cleanup(काष्ठा mlx5_core_dev *mdev);

#अन्यथा

अटल अंतरभूत पूर्णांक
mlx5_accel_tls_add_flow(काष्ठा mlx5_core_dev *mdev, व्योम *flow,
			काष्ठा tls_crypto_info *crypto_info,
			u32 start_offload_tcp_sn, u32 *p_swid,
			bool direction_sx) अणु वापस -ENOTSUPP; पूर्ण
अटल अंतरभूत व्योम mlx5_accel_tls_del_flow(काष्ठा mlx5_core_dev *mdev, u32 swid,
					   bool direction_sx) अणु पूर्ण
अटल अंतरभूत पूर्णांक mlx5_accel_tls_resync_rx(काष्ठा mlx5_core_dev *mdev, __be32 handle,
					   u32 seq, __be64 rcd_sn) अणु वापस 0; पूर्ण
अटल अंतरभूत bool mlx5_accel_is_tls_device(काष्ठा mlx5_core_dev *mdev)
अणु
	वापस mlx5_accel_is_ktls_device(mdev);
पूर्ण
अटल अंतरभूत u32 mlx5_accel_tls_device_caps(काष्ठा mlx5_core_dev *mdev) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक mlx5_accel_tls_init(काष्ठा mlx5_core_dev *mdev) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम mlx5_accel_tls_cleanup(काष्ठा mlx5_core_dev *mdev) अणु पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर	/* __MLX5_ACCEL_TLS_H__ */
