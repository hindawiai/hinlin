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

#समावेश <linux/mlx5/device.h>

#समावेश "fpga/core.h"
#समावेश "fpga/conn.h"
#समावेश "fpga/sdk.h"

काष्ठा mlx5_fpga_conn *
mlx5_fpga_sbu_conn_create(काष्ठा mlx5_fpga_device *fdev,
			  काष्ठा mlx5_fpga_conn_attr *attr)
अणु
	वापस mlx5_fpga_conn_create(fdev, attr, MLX5_FPGA_QPC_QP_TYPE_SANDBOX_QP);
पूर्ण
EXPORT_SYMBOL(mlx5_fpga_sbu_conn_create);

व्योम mlx5_fpga_sbu_conn_destroy(काष्ठा mlx5_fpga_conn *conn)
अणु
	mlx5_fpga_conn_destroy(conn);
पूर्ण
EXPORT_SYMBOL(mlx5_fpga_sbu_conn_destroy);

पूर्णांक mlx5_fpga_sbu_conn_sendmsg(काष्ठा mlx5_fpga_conn *conn,
			       काष्ठा mlx5_fpga_dma_buf *buf)
अणु
	वापस mlx5_fpga_conn_send(conn, buf);
पूर्ण
EXPORT_SYMBOL(mlx5_fpga_sbu_conn_sendmsg);

अटल पूर्णांक mlx5_fpga_mem_पढ़ो_i2c(काष्ठा mlx5_fpga_device *fdev, माप_प्रकार size,
				  u64 addr, u8 *buf)
अणु
	माप_प्रकार max_size = MLX5_FPGA_ACCESS_REG_SIZE_MAX;
	माप_प्रकार bytes_करोne = 0;
	u8 actual_size;
	पूर्णांक err;

	अगर (!size)
		वापस -EINVAL;

	अगर (!fdev->mdev)
		वापस -ENOTCONN;

	जबतक (bytes_करोne < size) अणु
		actual_size = min(max_size, (size - bytes_करोne));

		err = mlx5_fpga_access_reg(fdev->mdev, actual_size,
					   addr + bytes_करोne,
					   buf + bytes_करोne, false);
		अगर (err) अणु
			mlx5_fpga_err(fdev, "Failed to read over I2C: %d\n",
				      err);
			अवरोध;
		पूर्ण

		bytes_करोne += actual_size;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक mlx5_fpga_mem_ग_लिखो_i2c(काष्ठा mlx5_fpga_device *fdev, माप_प्रकार size,
				   u64 addr, u8 *buf)
अणु
	माप_प्रकार max_size = MLX5_FPGA_ACCESS_REG_SIZE_MAX;
	माप_प्रकार bytes_करोne = 0;
	u8 actual_size;
	पूर्णांक err;

	अगर (!size)
		वापस -EINVAL;

	अगर (!fdev->mdev)
		वापस -ENOTCONN;

	जबतक (bytes_करोne < size) अणु
		actual_size = min(max_size, (size - bytes_करोne));

		err = mlx5_fpga_access_reg(fdev->mdev, actual_size,
					   addr + bytes_करोne,
					   buf + bytes_करोne, true);
		अगर (err) अणु
			mlx5_fpga_err(fdev, "Failed to write FPGA crspace\n");
			अवरोध;
		पूर्ण

		bytes_करोne += actual_size;
	पूर्ण

	वापस err;
पूर्ण

पूर्णांक mlx5_fpga_mem_पढ़ो(काष्ठा mlx5_fpga_device *fdev, माप_प्रकार size, u64 addr,
		       व्योम *buf, क्रमागत mlx5_fpga_access_type access_type)
अणु
	पूर्णांक ret;

	चयन (access_type) अणु
	हाल MLX5_FPGA_ACCESS_TYPE_I2C:
		ret = mlx5_fpga_mem_पढ़ो_i2c(fdev, size, addr, buf);
		अगर (ret)
			वापस ret;
		अवरोध;
	शेष:
		mlx5_fpga_warn(fdev, "Unexpected read access_type %u\n",
			       access_type);
		वापस -EACCES;
	पूर्ण

	वापस size;
पूर्ण
EXPORT_SYMBOL(mlx5_fpga_mem_पढ़ो);

पूर्णांक mlx5_fpga_mem_ग_लिखो(काष्ठा mlx5_fpga_device *fdev, माप_प्रकार size, u64 addr,
			व्योम *buf, क्रमागत mlx5_fpga_access_type access_type)
अणु
	पूर्णांक ret;

	चयन (access_type) अणु
	हाल MLX5_FPGA_ACCESS_TYPE_I2C:
		ret = mlx5_fpga_mem_ग_लिखो_i2c(fdev, size, addr, buf);
		अगर (ret)
			वापस ret;
		अवरोध;
	शेष:
		mlx5_fpga_warn(fdev, "Unexpected write access_type %u\n",
			       access_type);
		वापस -EACCES;
	पूर्ण

	वापस size;
पूर्ण
EXPORT_SYMBOL(mlx5_fpga_mem_ग_लिखो);

पूर्णांक mlx5_fpga_get_sbu_caps(काष्ठा mlx5_fpga_device *fdev, पूर्णांक size, व्योम *buf)
अणु
	वापस mlx5_fpga_sbu_caps(fdev->mdev, buf, size);
पूर्ण
EXPORT_SYMBOL(mlx5_fpga_get_sbu_caps);
