<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/* Copyright (c) 2019 Mellanox Technologies. */

#समावेश "ecpf.h"

bool mlx5_पढ़ो_embedded_cpu(काष्ठा mlx5_core_dev *dev)
अणु
	वापस (ioपढ़ो32be(&dev->iseg->initializing) >> MLX5_ECPU_BIT_NUM) & 1;
पूर्ण

अटल bool mlx5_ecpf_esw_admins_host_pf(स्थिर काष्ठा mlx5_core_dev *dev)
अणु
	/* In separate host mode, PF enables itself.
	 * When ECPF is eचयन manager, eचयन enables host PF after
	 * eचयन is setup.
	 */
	वापस mlx5_core_is_ecpf_esw_manager(dev);
पूर्ण

पूर्णांक mlx5_cmd_host_pf_enable_hca(काष्ठा mlx5_core_dev *dev)
अणु
	u32 out[MLX5_ST_SZ_DW(enable_hca_out)] = अणुपूर्ण;
	u32 in[MLX5_ST_SZ_DW(enable_hca_in)]   = अणुपूर्ण;

	MLX5_SET(enable_hca_in, in, opcode, MLX5_CMD_OP_ENABLE_HCA);
	MLX5_SET(enable_hca_in, in, function_id, 0);
	MLX5_SET(enable_hca_in, in, embedded_cpu_function, 0);
	वापस mlx5_cmd_exec(dev, &in, माप(in), &out, माप(out));
पूर्ण

पूर्णांक mlx5_cmd_host_pf_disable_hca(काष्ठा mlx5_core_dev *dev)
अणु
	u32 out[MLX5_ST_SZ_DW(disable_hca_out)] = अणुपूर्ण;
	u32 in[MLX5_ST_SZ_DW(disable_hca_in)]   = अणुपूर्ण;

	MLX5_SET(disable_hca_in, in, opcode, MLX5_CMD_OP_DISABLE_HCA);
	MLX5_SET(disable_hca_in, in, function_id, 0);
	MLX5_SET(disable_hca_in, in, embedded_cpu_function, 0);
	वापस mlx5_cmd_exec(dev, in, माप(in), out, माप(out));
पूर्ण

अटल पूर्णांक mlx5_host_pf_init(काष्ठा mlx5_core_dev *dev)
अणु
	पूर्णांक err;

	अगर (mlx5_ecpf_esw_admins_host_pf(dev))
		वापस 0;

	/* ECPF shall enable HCA क्रम host PF in the same way a PF
	 * करोes this क्रम its VFs when ECPF is not a eचयन manager.
	 */
	err = mlx5_cmd_host_pf_enable_hca(dev);
	अगर (err)
		mlx5_core_err(dev, "Failed to enable external host PF HCA err(%d)\n", err);

	वापस err;
पूर्ण

अटल व्योम mlx5_host_pf_cleanup(काष्ठा mlx5_core_dev *dev)
अणु
	पूर्णांक err;

	अगर (mlx5_ecpf_esw_admins_host_pf(dev))
		वापस;

	err = mlx5_cmd_host_pf_disable_hca(dev);
	अगर (err) अणु
		mlx5_core_err(dev, "Failed to disable external host PF HCA err(%d)\n", err);
		वापस;
	पूर्ण
पूर्ण

पूर्णांक mlx5_ec_init(काष्ठा mlx5_core_dev *dev)
अणु
	अगर (!mlx5_core_is_ecpf(dev))
		वापस 0;

	वापस mlx5_host_pf_init(dev);
पूर्ण

व्योम mlx5_ec_cleanup(काष्ठा mlx5_core_dev *dev)
अणु
	पूर्णांक err;

	अगर (!mlx5_core_is_ecpf(dev))
		वापस;

	mlx5_host_pf_cleanup(dev);

	err = mlx5_रुको_क्रम_pages(dev, &dev->priv.host_pf_pages);
	अगर (err)
		mlx5_core_warn(dev, "Timeout reclaiming external host PF pages err(%d)\n", err);
पूर्ण
