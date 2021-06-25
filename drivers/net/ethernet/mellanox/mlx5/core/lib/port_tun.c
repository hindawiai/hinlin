<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/* Copyright (c) 2019 Mellanox Technologies. */

#समावेश <linux/module.h>
#समावेश <linux/mlx5/driver.h>
#समावेश <linux/mlx5/port.h>
#समावेश "mlx5_core.h"
#समावेश "lib/port_tun.h"

काष्ठा mlx5_port_tun_entropy_flags अणु
	bool क्रमce_supported, क्रमce_enabled;
	bool calc_supported, calc_enabled;
	bool gre_calc_supported, gre_calc_enabled;
पूर्ण;

अटल व्योम mlx5_query_port_tun_entropy(काष्ठा mlx5_core_dev *mdev,
					काष्ठा mlx5_port_tun_entropy_flags *entropy_flags)
अणु
	u32 out[MLX5_ST_SZ_DW(pcmr_reg)];
	/* Default values क्रम FW which करो not support MLX5_REG_PCMR */
	entropy_flags->क्रमce_supported = false;
	entropy_flags->calc_supported = false;
	entropy_flags->gre_calc_supported = false;
	entropy_flags->क्रमce_enabled = false;
	entropy_flags->calc_enabled = true;
	entropy_flags->gre_calc_enabled = true;

	अगर (!MLX5_CAP_GEN(mdev, ports_check))
		वापस;

	अगर (mlx5_query_ports_check(mdev, out, माप(out)))
		वापस;

	entropy_flags->क्रमce_supported = !!(MLX5_GET(pcmr_reg, out, entropy_क्रमce_cap));
	entropy_flags->calc_supported = !!(MLX5_GET(pcmr_reg, out, entropy_calc_cap));
	entropy_flags->gre_calc_supported = !!(MLX5_GET(pcmr_reg, out, entropy_gre_calc_cap));
	entropy_flags->क्रमce_enabled = !!(MLX5_GET(pcmr_reg, out, entropy_क्रमce));
	entropy_flags->calc_enabled = !!(MLX5_GET(pcmr_reg, out, entropy_calc));
	entropy_flags->gre_calc_enabled = !!(MLX5_GET(pcmr_reg, out, entropy_gre_calc));
पूर्ण

अटल पूर्णांक mlx5_set_port_tun_entropy_calc(काष्ठा mlx5_core_dev *mdev, u8 enable,
					  u8 क्रमce)
अणु
	u32 in[MLX5_ST_SZ_DW(pcmr_reg)] = अणु0पूर्ण;
	पूर्णांक err;

	err = mlx5_query_ports_check(mdev, in, माप(in));
	अगर (err)
		वापस err;
	MLX5_SET(pcmr_reg, in, local_port, 1);
	MLX5_SET(pcmr_reg, in, entropy_क्रमce, क्रमce);
	MLX5_SET(pcmr_reg, in, entropy_calc, enable);
	वापस mlx5_set_ports_check(mdev, in, माप(in));
पूर्ण

अटल पूर्णांक mlx5_set_port_gre_tun_entropy_calc(काष्ठा mlx5_core_dev *mdev,
					      u8 enable, u8 क्रमce)
अणु
	u32 in[MLX5_ST_SZ_DW(pcmr_reg)] = अणु0पूर्ण;
	पूर्णांक err;

	err = mlx5_query_ports_check(mdev, in, माप(in));
	अगर (err)
		वापस err;
	MLX5_SET(pcmr_reg, in, local_port, 1);
	MLX5_SET(pcmr_reg, in, entropy_क्रमce, क्रमce);
	MLX5_SET(pcmr_reg, in, entropy_gre_calc, enable);
	वापस mlx5_set_ports_check(mdev, in, माप(in));
पूर्ण

व्योम mlx5_init_port_tun_entropy(काष्ठा mlx5_tun_entropy *tun_entropy,
				काष्ठा mlx5_core_dev *mdev)
अणु
	काष्ठा mlx5_port_tun_entropy_flags entropy_flags;

	tun_entropy->mdev = mdev;
	mutex_init(&tun_entropy->lock);
	mlx5_query_port_tun_entropy(mdev, &entropy_flags);
	tun_entropy->num_enabling_entries = 0;
	tun_entropy->num_disabling_entries = 0;
	tun_entropy->enabled = entropy_flags.calc_supported ?
			       entropy_flags.calc_enabled : true;
पूर्ण

अटल पूर्णांक mlx5_set_entropy(काष्ठा mlx5_tun_entropy *tun_entropy,
			    पूर्णांक reक्रमmat_type, bool enable)
अणु
	काष्ठा mlx5_port_tun_entropy_flags entropy_flags;
	पूर्णांक err;

	mlx5_query_port_tun_entropy(tun_entropy->mdev, &entropy_flags);
	/* Tunnel entropy calculation may be controlled either on port basis
	 * क्रम all tunneling protocols or specअगरically क्रम GRE protocol.
	 * Prioritize GRE protocol control (अगर capable) over global port
	 * configuration.
	 */
	अगर (entropy_flags.gre_calc_supported &&
	    reक्रमmat_type == MLX5_REFORMAT_TYPE_L2_TO_NVGRE) अणु
		अगर (!entropy_flags.क्रमce_supported)
			वापस 0;
		err = mlx5_set_port_gre_tun_entropy_calc(tun_entropy->mdev,
							 enable, !enable);
		अगर (err)
			वापस err;
	पूर्ण अन्यथा अगर (entropy_flags.calc_supported) अणु
		/* Other applications may change the global FW entropy
		 * calculations settings. Check that the current entropy value
		 * is the negative of the updated value.
		 */
		अगर (entropy_flags.क्रमce_enabled &&
		    enable == entropy_flags.calc_enabled) अणु
			mlx5_core_warn(tun_entropy->mdev,
				       "Unexpected entropy calc setting - expected %d",
				       !entropy_flags.calc_enabled);
			वापस -EOPNOTSUPP;
		पूर्ण
		/* GRE requires disabling entropy calculation. अगर there are
		 * enabling entries (i.e VXLAN) we cannot turn it off क्रम them,
		 * thus fail.
		 */
		अगर (tun_entropy->num_enabling_entries)
			वापस -EOPNOTSUPP;
		err = mlx5_set_port_tun_entropy_calc(tun_entropy->mdev, enable,
						     entropy_flags.क्रमce_supported);
		अगर (err)
			वापस err;
		tun_entropy->enabled = enable;
		/* अगर we turn on the entropy we करोn't need to क्रमce it anymore */
		अगर (entropy_flags.क्रमce_supported && enable) अणु
			err = mlx5_set_port_tun_entropy_calc(tun_entropy->mdev, 1, 0);
			अगर (err)
				वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* the function manages the refcount क्रम enabling/disabling tunnel types.
 * the वापस value indicates अगर the inc is successful or not, depending on
 * entropy capabilities and configuration.
 */
पूर्णांक mlx5_tun_entropy_refcount_inc(काष्ठा mlx5_tun_entropy *tun_entropy,
				  पूर्णांक reक्रमmat_type)
अणु
	पूर्णांक err = -EOPNOTSUPP;

	mutex_lock(&tun_entropy->lock);
	अगर ((reक्रमmat_type == MLX5_REFORMAT_TYPE_L2_TO_VXLAN ||
	     reक्रमmat_type == MLX5_REFORMAT_TYPE_L2_TO_L3_TUNNEL) &&
	    tun_entropy->enabled) अणु
		/* in हाल entropy calculation is enabled क्रम all tunneling
		 * types, it is ok क्रम VXLAN, so approve.
		 * otherwise keep the error शेष.
		 */
		tun_entropy->num_enabling_entries++;
		err = 0;
	पूर्ण अन्यथा अगर (reक्रमmat_type == MLX5_REFORMAT_TYPE_L2_TO_NVGRE) अणु
		/* turn off the entropy only क्रम the first GRE rule.
		 * क्रम the next rules the entropy was alपढ़ोy disabled
		 * successfully.
		 */
		अगर (tun_entropy->num_disabling_entries == 0)
			err = mlx5_set_entropy(tun_entropy, reक्रमmat_type, 0);
		अन्यथा
			err = 0;
		अगर (!err)
			tun_entropy->num_disabling_entries++;
	पूर्ण
	mutex_unlock(&tun_entropy->lock);

	वापस err;
पूर्ण

व्योम mlx5_tun_entropy_refcount_dec(काष्ठा mlx5_tun_entropy *tun_entropy,
				   पूर्णांक reक्रमmat_type)
अणु
	mutex_lock(&tun_entropy->lock);
	अगर (reक्रमmat_type == MLX5_REFORMAT_TYPE_L2_TO_VXLAN)
		tun_entropy->num_enabling_entries--;
	अन्यथा अगर (reक्रमmat_type == MLX5_REFORMAT_TYPE_L2_TO_NVGRE &&
		 --tun_entropy->num_disabling_entries == 0)
		mlx5_set_entropy(tun_entropy, reक्रमmat_type, 1);
	mutex_unlock(&tun_entropy->lock);
पूर्ण

