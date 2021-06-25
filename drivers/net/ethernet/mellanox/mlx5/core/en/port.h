<शैली गुरु>
/*
 * Copyright (c) 2018, Mellanox Technologies. All rights reserved.
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

#अगर_अघोषित __MLX5E_EN_PORT_H
#घोषणा __MLX5E_EN_PORT_H

#समावेश <linux/mlx5/driver.h>
#समावेश "en.h"

काष्ठा mlx5e_port_eth_proto अणु
	u32 cap;
	u32 admin;
	u32 oper;
पूर्ण;

पूर्णांक mlx5_port_query_eth_proto(काष्ठा mlx5_core_dev *dev, u8 port, bool ext,
			      काष्ठा mlx5e_port_eth_proto *eproto);
व्योम mlx5_port_query_eth_स्वतःneg(काष्ठा mlx5_core_dev *dev, u8 *an_status,
				 u8 *an_disable_cap, u8 *an_disable_admin);
पूर्णांक mlx5_port_set_eth_ptys(काष्ठा mlx5_core_dev *dev, bool an_disable,
			   u32 proto_admin, bool ext);
u32 mlx5e_port_ptys2speed(काष्ठा mlx5_core_dev *mdev, u32 eth_proto_oper,
			  bool क्रमce_legacy);
पूर्णांक mlx5e_port_linkspeed(काष्ठा mlx5_core_dev *mdev, u32 *speed);
पूर्णांक mlx5e_port_max_linkspeed(काष्ठा mlx5_core_dev *mdev, u32 *speed);
u32 mlx5e_port_speed2linkmodes(काष्ठा mlx5_core_dev *mdev, u32 speed,
			       bool क्रमce_legacy);
bool mlx5e_ptys_ext_supported(काष्ठा mlx5_core_dev *mdev);
पूर्णांक mlx5e_port_query_pbmc(काष्ठा mlx5_core_dev *mdev, व्योम *out);
पूर्णांक mlx5e_port_set_pbmc(काष्ठा mlx5_core_dev *mdev, व्योम *in);
पूर्णांक mlx5e_port_query_priority2buffer(काष्ठा mlx5_core_dev *mdev, u8 *buffer);
पूर्णांक mlx5e_port_set_priority2buffer(काष्ठा mlx5_core_dev *mdev, u8 *buffer);

bool mlx5e_fec_in_caps(काष्ठा mlx5_core_dev *dev, पूर्णांक fec_policy);
पूर्णांक mlx5e_get_fec_mode(काष्ठा mlx5_core_dev *dev, u32 *fec_mode_active,
		       u16 *fec_configured_mode);
पूर्णांक mlx5e_set_fec_mode(काष्ठा mlx5_core_dev *dev, u16 fec_policy);

क्रमागत अणु
	MLX5E_FEC_NOFEC,
	MLX5E_FEC_FIRECODE,
	MLX5E_FEC_RS_528_514,
	MLX5E_FEC_RS_544_514 = 7,
	MLX5E_FEC_LLRS_272_257_1 = 9,
पूर्ण;

#पूर्ण_अगर
