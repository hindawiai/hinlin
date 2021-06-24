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

#समावेश <linux/ethtool.h>
#समावेश <net/sock.h>

#समावेश "en.h"
#समावेश "fpga/sdk.h"
#समावेश "en_accel/tls.h"

अटल स्थिर काष्ठा counter_desc mlx5e_tls_sw_stats_desc[] = अणु
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_tls_sw_stats, tx_tls_drop_metadata) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_tls_sw_stats, tx_tls_drop_resync_alloc) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_tls_sw_stats, tx_tls_drop_no_sync_data) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_tls_sw_stats, tx_tls_drop_bypass_required) पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा counter_desc mlx5e_ktls_sw_stats_desc[] = अणु
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_tls_sw_stats, tx_tls_ctx) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_tls_sw_stats, rx_tls_ctx) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_tls_sw_stats, rx_tls_del) पूर्ण,
पूर्ण;

#घोषणा MLX5E_READ_CTR_ATOMIC64(ptr, dsc, i) \
	atomic64_पढ़ो((atomic64_t *)((अक्षर *)(ptr) + (dsc)[i].offset))

अटल स्थिर काष्ठा counter_desc *get_tls_atomic_stats(काष्ठा mlx5e_priv *priv)
अणु
	अगर (!priv->tls)
		वापस शून्य;
	अगर (mlx5_accel_is_ktls_device(priv->mdev))
		वापस mlx5e_ktls_sw_stats_desc;
	वापस mlx5e_tls_sw_stats_desc;
पूर्ण

पूर्णांक mlx5e_tls_get_count(काष्ठा mlx5e_priv *priv)
अणु
	अगर (!priv->tls)
		वापस 0;
	अगर (mlx5_accel_is_ktls_device(priv->mdev))
		वापस ARRAY_SIZE(mlx5e_ktls_sw_stats_desc);
	वापस ARRAY_SIZE(mlx5e_tls_sw_stats_desc);
पूर्ण

पूर्णांक mlx5e_tls_get_strings(काष्ठा mlx5e_priv *priv, uपूर्णांक8_t *data)
अणु
	स्थिर काष्ठा counter_desc *stats_desc;
	अचिन्हित पूर्णांक i, n, idx = 0;

	stats_desc = get_tls_atomic_stats(priv);
	n = mlx5e_tls_get_count(priv);

	क्रम (i = 0; i < n; i++)
		म_नकल(data + (idx++) * ETH_GSTRING_LEN,
		       stats_desc[i].क्रमmat);

	वापस n;
पूर्ण

पूर्णांक mlx5e_tls_get_stats(काष्ठा mlx5e_priv *priv, u64 *data)
अणु
	स्थिर काष्ठा counter_desc *stats_desc;
	अचिन्हित पूर्णांक i, n, idx = 0;

	stats_desc = get_tls_atomic_stats(priv);
	n = mlx5e_tls_get_count(priv);

	क्रम (i = 0; i < n; i++)
		data[idx++] =
		    MLX5E_READ_CTR_ATOMIC64(&priv->tls->sw_stats,
					    stats_desc, i);

	वापस n;
पूर्ण
