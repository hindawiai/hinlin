<शैली गुरु>
/*
 * Copyright (c) 2017 Mellanox Technologies. All rights reserved.
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

#समावेश <linux/ethtool.h>
#समावेश <net/sock.h>

#समावेश "en.h"
#समावेश "accel/ipsec.h"
#समावेश "fpga/sdk.h"
#समावेश "en_accel/ipsec.h"
#समावेश "fpga/ipsec.h"

अटल स्थिर काष्ठा counter_desc mlx5e_ipsec_hw_stats_desc[] = अणु
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_ipsec_stats, ipsec_dec_in_packets) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_ipsec_stats, ipsec_dec_out_packets) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_ipsec_stats, ipsec_dec_bypass_packets) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_ipsec_stats, ipsec_enc_in_packets) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_ipsec_stats, ipsec_enc_out_packets) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_ipsec_stats, ipsec_enc_bypass_packets) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_ipsec_stats, ipsec_dec_drop_packets) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_ipsec_stats, ipsec_dec_auth_fail_packets) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_ipsec_stats, ipsec_enc_drop_packets) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_ipsec_stats, ipsec_add_sa_success) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_ipsec_stats, ipsec_add_sa_fail) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_ipsec_stats, ipsec_del_sa_success) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_ipsec_stats, ipsec_del_sa_fail) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_ipsec_stats, ipsec_cmd_drop) पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा counter_desc mlx5e_ipsec_sw_stats_desc[] = अणु
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_ipsec_sw_stats, ipsec_rx_drop_sp_alloc) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_ipsec_sw_stats, ipsec_rx_drop_sadb_miss) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_ipsec_sw_stats, ipsec_rx_drop_syndrome) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_ipsec_sw_stats, ipsec_tx_drop_bundle) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_ipsec_sw_stats, ipsec_tx_drop_no_state) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_ipsec_sw_stats, ipsec_tx_drop_not_ip) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_ipsec_sw_stats, ipsec_tx_drop_trailer) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_ipsec_sw_stats, ipsec_tx_drop_metadata) पूर्ण,
पूर्ण;

#घोषणा MLX5E_READ_CTR_ATOMIC64(ptr, dsc, i) \
	atomic64_पढ़ो((atomic64_t *)((अक्षर *)(ptr) + (dsc)[i].offset))

#घोषणा NUM_IPSEC_HW_COUNTERS ARRAY_SIZE(mlx5e_ipsec_hw_stats_desc)
#घोषणा NUM_IPSEC_SW_COUNTERS ARRAY_SIZE(mlx5e_ipsec_sw_stats_desc)

अटल MLX5E_DECLARE_STATS_GRP_OP_NUM_STATS(ipsec_sw)
अणु
	वापस priv->ipsec ? NUM_IPSEC_SW_COUNTERS : 0;
पूर्ण

अटल अंतरभूत MLX5E_DECLARE_STATS_GRP_OP_UPDATE_STATS(ipsec_sw) अणुपूर्ण

अटल MLX5E_DECLARE_STATS_GRP_OP_FILL_STRS(ipsec_sw)
अणु
	अचिन्हित पूर्णांक i;

	अगर (priv->ipsec)
		क्रम (i = 0; i < NUM_IPSEC_SW_COUNTERS; i++)
			म_नकल(data + (idx++) * ETH_GSTRING_LEN,
			       mlx5e_ipsec_sw_stats_desc[i].क्रमmat);
	वापस idx;
पूर्ण

अटल MLX5E_DECLARE_STATS_GRP_OP_FILL_STATS(ipsec_sw)
अणु
	पूर्णांक i;

	अगर (priv->ipsec)
		क्रम (i = 0; i < NUM_IPSEC_SW_COUNTERS; i++)
			data[idx++] = MLX5E_READ_CTR_ATOMIC64(&priv->ipsec->sw_stats,
							      mlx5e_ipsec_sw_stats_desc, i);
	वापस idx;
पूर्ण

अटल MLX5E_DECLARE_STATS_GRP_OP_NUM_STATS(ipsec_hw)
अणु
	वापस (priv->ipsec && mlx5_fpga_ipsec_device_caps(priv->mdev)) ? NUM_IPSEC_HW_COUNTERS : 0;
पूर्ण

अटल MLX5E_DECLARE_STATS_GRP_OP_UPDATE_STATS(ipsec_hw)
अणु
	पूर्णांक ret = 0;

	अगर (priv->ipsec)
		ret = mlx5_accel_ipsec_counters_पढ़ो(priv->mdev, (u64 *)&priv->ipsec->stats,
						     NUM_IPSEC_HW_COUNTERS);
	अगर (ret)
		स_रखो(&priv->ipsec->stats, 0, माप(priv->ipsec->stats));
पूर्ण

अटल MLX5E_DECLARE_STATS_GRP_OP_FILL_STRS(ipsec_hw)
अणु
	अचिन्हित पूर्णांक i;

	अगर (priv->ipsec && mlx5_fpga_ipsec_device_caps(priv->mdev))
		क्रम (i = 0; i < NUM_IPSEC_HW_COUNTERS; i++)
			म_नकल(data + (idx++) * ETH_GSTRING_LEN,
			       mlx5e_ipsec_hw_stats_desc[i].क्रमmat);

	वापस idx;
पूर्ण

अटल MLX5E_DECLARE_STATS_GRP_OP_FILL_STATS(ipsec_hw)
अणु
	पूर्णांक i;

	अगर (priv->ipsec && mlx5_fpga_ipsec_device_caps(priv->mdev))
		क्रम (i = 0; i < NUM_IPSEC_HW_COUNTERS; i++)
			data[idx++] = MLX5E_READ_CTR64_CPU(&priv->ipsec->stats,
							   mlx5e_ipsec_hw_stats_desc,
							   i);
	वापस idx;
पूर्ण

MLX5E_DEFINE_STATS_GRP(ipsec_sw, 0);
MLX5E_DEFINE_STATS_GRP(ipsec_hw, 0);
