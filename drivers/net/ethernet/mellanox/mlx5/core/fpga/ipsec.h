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

#अगर_अघोषित __MLX5_FPGA_IPSEC_H__
#घोषणा __MLX5_FPGA_IPSEC_H__

#समावेश "accel/ipsec.h"
#समावेश "fs_cmd.h"

#अगर_घोषित CONFIG_MLX5_FPGA_IPSEC
स्थिर काष्ठा mlx5_accel_ipsec_ops *mlx5_fpga_ipsec_ops(काष्ठा mlx5_core_dev *mdev);
u32 mlx5_fpga_ipsec_device_caps(काष्ठा mlx5_core_dev *mdev);
स्थिर काष्ठा mlx5_flow_cmds *
mlx5_fs_cmd_get_शेष_ipsec_fpga_cmds(क्रमागत fs_flow_table_type type);
व्योम mlx5_fpga_ipsec_build_fs_cmds(व्योम);
bool mlx5_fpga_is_ipsec_device(काष्ठा mlx5_core_dev *mdev);
#अन्यथा
अटल अंतरभूत
स्थिर काष्ठा mlx5_accel_ipsec_ops *mlx5_fpga_ipsec_ops(काष्ठा mlx5_core_dev *mdev)
अणु वापस शून्य; पूर्ण
अटल अंतरभूत u32 mlx5_fpga_ipsec_device_caps(काष्ठा mlx5_core_dev *mdev) अणु वापस 0; पूर्ण
अटल अंतरभूत स्थिर काष्ठा mlx5_flow_cmds *
mlx5_fs_cmd_get_शेष_ipsec_fpga_cmds(क्रमागत fs_flow_table_type type)
अणु
	वापस mlx5_fs_cmd_get_शेष(type);
पूर्ण

अटल अंतरभूत व्योम mlx5_fpga_ipsec_build_fs_cmds(व्योम) अणुपूर्ण;
अटल अंतरभूत bool mlx5_fpga_is_ipsec_device(काष्ठा mlx5_core_dev *mdev) अणु वापस false; पूर्ण

#पूर्ण_अगर /* CONFIG_MLX5_FPGA_IPSEC */
#पूर्ण_अगर	/* __MLX5_FPGA_IPSEC_H__ */
