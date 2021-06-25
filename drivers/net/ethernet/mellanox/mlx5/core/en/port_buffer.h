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
#अगर_अघोषित __MLX5_EN_PORT_BUFFER_H__
#घोषणा __MLX5_EN_PORT_BUFFER_H__

#समावेश "en.h"
#समावेश "port.h"

#घोषणा MLX5E_MAX_BUFFER 8
#घोषणा MLX5E_DEFAULT_CABLE_LEN 7 /* 7 meters */

#घोषणा MLX5_BUFFER_SUPPORTED(mdev) (MLX5_CAP_GEN(mdev, pcam_reg) && \
				     MLX5_CAP_PCAM_REG(mdev, pbmc) && \
				     MLX5_CAP_PCAM_REG(mdev, pptb))

क्रमागत अणु
	MLX5E_PORT_BUFFER_CABLE_LEN   = BIT(0),
	MLX5E_PORT_BUFFER_PFC         = BIT(1),
	MLX5E_PORT_BUFFER_PRIO2BUFFER = BIT(2),
	MLX5E_PORT_BUFFER_SIZE        = BIT(3),
पूर्ण;

काष्ठा mlx5e_bufferx_reg अणु
	u8   lossy;
	u8   epsb;
	u32  size;
	u32  xoff;
	u32  xon;
पूर्ण;

काष्ठा mlx5e_port_buffer अणु
	u32                       port_buffer_size;
	u32                       spare_buffer_size;
	काष्ठा mlx5e_bufferx_reg  buffer[MLX5E_MAX_BUFFER];
पूर्ण;

पूर्णांक mlx5e_port_manual_buffer_config(काष्ठा mlx5e_priv *priv,
				    u32 change, अचिन्हित पूर्णांक mtu,
				    काष्ठा ieee_pfc *pfc,
				    u32 *buffer_size,
				    u8 *prio2buffer);

पूर्णांक mlx5e_port_query_buffer(काष्ठा mlx5e_priv *priv,
			    काष्ठा mlx5e_port_buffer *port_buffer);
#पूर्ण_अगर
