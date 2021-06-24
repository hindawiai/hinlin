<शैली गुरु>
/*
 * Copyright (c) 2017, Mellanox Technologies, Ltd.  All rights reserved.
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

#अगर_अघोषित __MLX5_FPGA_CORE_H__
#घोषणा __MLX5_FPGA_CORE_H__

#अगर_घोषित CONFIG_MLX5_FPGA

#समावेश <linux/mlx5/eq.h>

#समावेश "mlx5_core.h"
#समावेश "lib/eq.h"
#समावेश "fpga/cmd.h"

/* Represents an Innova device */
काष्ठा mlx5_fpga_device अणु
	काष्ठा mlx5_core_dev *mdev;
	काष्ठा mlx5_nb fpga_err_nb;
	काष्ठा mlx5_nb fpga_qp_err_nb;
	spinlock_t state_lock; /* Protects state transitions */
	क्रमागत mlx5_fpga_status state;
	क्रमागत mlx5_fpga_image last_admin_image;
	क्रमागत mlx5_fpga_image last_oper_image;

	/* QP Connection resources */
	काष्ठा अणु
		u32 pdn;
		काष्ठा mlx5_core_mkey mkey;
		काष्ठा mlx5_uars_page *uar;
	पूर्ण conn_res;

	काष्ठा mlx5_fpga_ipsec *ipsec;
	काष्ठा mlx5_fpga_tls *tls;
पूर्ण;

#घोषणा mlx5_fpga_dbg(__adev, क्रमmat, ...) \
	mlx5_core_dbg((__adev)->mdev, "FPGA: %s:%d:(pid %d): " क्रमmat, \
		       __func__, __LINE__, current->pid, ##__VA_ARGS__)

#घोषणा mlx5_fpga_err(__adev, क्रमmat, ...) \
	mlx5_core_err((__adev)->mdev, "FPGA: %s:%d:(pid %d): " क्रमmat, \
		      __func__, __LINE__, current->pid, ##__VA_ARGS__)

#घोषणा mlx5_fpga_warn(__adev, क्रमmat, ...) \
	mlx5_core_warn((__adev)->mdev, "FPGA: %s:%d:(pid %d): " क्रमmat, \
		       __func__, __LINE__, current->pid, ##__VA_ARGS__)

#घोषणा mlx5_fpga_warn_ratelimited(__adev, क्रमmat, ...) \
	mlx5_core_err_rl((__adev)->mdev, "FPGA: %s:%d: " \
			 क्रमmat, __func__, __LINE__, ##__VA_ARGS__)

#घोषणा mlx5_fpga_notice(__adev, क्रमmat, ...) \
	mlx5_core_info((__adev)->mdev, "FPGA: " क्रमmat, ##__VA_ARGS__)

#घोषणा mlx5_fpga_info(__adev, क्रमmat, ...) \
	mlx5_core_info((__adev)->mdev, "FPGA: " क्रमmat, ##__VA_ARGS__)

पूर्णांक mlx5_fpga_init(काष्ठा mlx5_core_dev *mdev);
व्योम mlx5_fpga_cleanup(काष्ठा mlx5_core_dev *mdev);
पूर्णांक mlx5_fpga_device_start(काष्ठा mlx5_core_dev *mdev);
व्योम mlx5_fpga_device_stop(काष्ठा mlx5_core_dev *mdev);

#अन्यथा

अटल अंतरभूत पूर्णांक mlx5_fpga_init(काष्ठा mlx5_core_dev *mdev)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम mlx5_fpga_cleanup(काष्ठा mlx5_core_dev *mdev)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक mlx5_fpga_device_start(काष्ठा mlx5_core_dev *mdev)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम mlx5_fpga_device_stop(काष्ठा mlx5_core_dev *mdev)
अणु
पूर्ण

#पूर्ण_अगर

#पूर्ण_अगर /* __MLX5_FPGA_CORE_H__ */
