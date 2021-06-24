<शैली गुरु>
/*
 * Copyright (c) 2013-2015, Mellanox Technologies, Ltd.  All rights reserved.
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

#अगर_अघोषित __TRANSOBJ_H__
#घोषणा __TRANSOBJ_H__

#समावेश <linux/mlx5/driver.h>

पूर्णांक mlx5_core_alloc_transport_करोमुख्य(काष्ठा mlx5_core_dev *dev, u32 *tdn);
व्योम mlx5_core_dealloc_transport_करोमुख्य(काष्ठा mlx5_core_dev *dev, u32 tdn);
पूर्णांक mlx5_core_create_rq(काष्ठा mlx5_core_dev *dev, u32 *in, पूर्णांक inlen,
			u32 *rqn);
पूर्णांक mlx5_core_modअगरy_rq(काष्ठा mlx5_core_dev *dev, u32 rqn, u32 *in);
व्योम mlx5_core_destroy_rq(काष्ठा mlx5_core_dev *dev, u32 rqn);
पूर्णांक mlx5_core_query_rq(काष्ठा mlx5_core_dev *dev, u32 rqn, u32 *out);
पूर्णांक mlx5_core_create_sq(काष्ठा mlx5_core_dev *dev, u32 *in, पूर्णांक inlen,
			u32 *sqn);
पूर्णांक mlx5_core_modअगरy_sq(काष्ठा mlx5_core_dev *dev, u32 sqn, u32 *in);
व्योम mlx5_core_destroy_sq(काष्ठा mlx5_core_dev *dev, u32 sqn);
पूर्णांक mlx5_core_query_sq(काष्ठा mlx5_core_dev *dev, u32 sqn, u32 *out);
पूर्णांक mlx5_core_query_sq_state(काष्ठा mlx5_core_dev *dev, u32 sqn, u8 *state);
पूर्णांक mlx5_core_create_tir(काष्ठा mlx5_core_dev *dev, u32 *in, u32 *tirn);
पूर्णांक mlx5_core_modअगरy_tir(काष्ठा mlx5_core_dev *dev, u32 tirn, u32 *in);
व्योम mlx5_core_destroy_tir(काष्ठा mlx5_core_dev *dev, u32 tirn);
पूर्णांक mlx5_core_create_tis(काष्ठा mlx5_core_dev *dev, u32 *in, u32 *tisn);
पूर्णांक mlx5_core_modअगरy_tis(काष्ठा mlx5_core_dev *dev, u32 tisn, u32 *in);
व्योम mlx5_core_destroy_tis(काष्ठा mlx5_core_dev *dev, u32 tisn);
पूर्णांक mlx5_core_create_rqt(काष्ठा mlx5_core_dev *dev, u32 *in, पूर्णांक inlen,
			 u32 *rqtn);
पूर्णांक mlx5_core_modअगरy_rqt(काष्ठा mlx5_core_dev *dev, u32 rqtn, u32 *in,
			 पूर्णांक inlen);
व्योम mlx5_core_destroy_rqt(काष्ठा mlx5_core_dev *dev, u32 rqtn);

काष्ठा mlx5_hairpin_params अणु
	u8  log_data_size;
	u8  log_num_packets;
	u16 q_counter;
	पूर्णांक num_channels;
पूर्ण;

काष्ठा mlx5_hairpin अणु
	काष्ठा mlx5_core_dev *func_mdev;
	काष्ठा mlx5_core_dev *peer_mdev;

	पूर्णांक num_channels;

	u32 *rqn;
	u32 *sqn;

	bool peer_gone;
पूर्ण;

काष्ठा mlx5_hairpin *
mlx5_core_hairpin_create(काष्ठा mlx5_core_dev *func_mdev,
			 काष्ठा mlx5_core_dev *peer_mdev,
			 काष्ठा mlx5_hairpin_params *params);

व्योम mlx5_core_hairpin_destroy(काष्ठा mlx5_hairpin *pair);
व्योम mlx5_core_hairpin_clear_dead_peer(काष्ठा mlx5_hairpin *hp);
#पूर्ण_अगर /* __TRANSOBJ_H__ */
