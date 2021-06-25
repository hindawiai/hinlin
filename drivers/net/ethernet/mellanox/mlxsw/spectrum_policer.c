<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/* Copyright (c) 2020 Mellanox Technologies. All rights reserved */

#समावेश <linux/idr.h>
#समावेश <linux/log2.h>
#समावेश <linux/mutex.h>
#समावेश <linux/netlink.h>
#समावेश <net/devlink.h>

#समावेश "spectrum.h"

काष्ठा mlxsw_sp_policer_family अणु
	क्रमागत mlxsw_sp_policer_type type;
	क्रमागत mlxsw_reg_qpcr_g qpcr_type;
	काष्ठा mlxsw_sp *mlxsw_sp;
	u16 start_index; /* Inclusive */
	u16 end_index; /* Exclusive */
	काष्ठा idr policer_idr;
	काष्ठा mutex lock; /* Protects policer_idr */
	atomic_t policers_count;
	स्थिर काष्ठा mlxsw_sp_policer_family_ops *ops;
पूर्ण;

काष्ठा mlxsw_sp_policer अणु
	काष्ठा mlxsw_sp_policer_params params;
	u16 index;
पूर्ण;

काष्ठा mlxsw_sp_policer_family_ops अणु
	पूर्णांक (*init)(काष्ठा mlxsw_sp_policer_family *family);
	व्योम (*fini)(काष्ठा mlxsw_sp_policer_family *family);
	पूर्णांक (*policer_index_alloc)(काष्ठा mlxsw_sp_policer_family *family,
				   काष्ठा mlxsw_sp_policer *policer);
	काष्ठा mlxsw_sp_policer * (*policer_index_मुक्त)(काष्ठा mlxsw_sp_policer_family *family,
							u16 policer_index);
	पूर्णांक (*policer_init)(काष्ठा mlxsw_sp_policer_family *family,
			    स्थिर काष्ठा mlxsw_sp_policer *policer);
	पूर्णांक (*policer_params_check)(स्थिर काष्ठा mlxsw_sp_policer_family *family,
				    स्थिर काष्ठा mlxsw_sp_policer_params *params,
				    काष्ठा netlink_ext_ack *extack);
पूर्ण;

काष्ठा mlxsw_sp_policer_core अणु
	काष्ठा mlxsw_sp_policer_family *family_arr[MLXSW_SP_POLICER_TYPE_MAX + 1];
	स्थिर काष्ठा mlxsw_sp_policer_core_ops *ops;
	u8 lowest_bs_bits;
	u8 highest_bs_bits;
पूर्ण;

काष्ठा mlxsw_sp_policer_core_ops अणु
	पूर्णांक (*init)(काष्ठा mlxsw_sp_policer_core *policer_core);
पूर्ण;

अटल u64 mlxsw_sp_policer_rate_bytes_ps_kbps(u64 rate_bytes_ps)
अणु
	वापस भाग_u64(rate_bytes_ps, 1000) * BITS_PER_BYTE;
पूर्ण

अटल u8 mlxsw_sp_policer_burst_bytes_hw_units(u64 burst_bytes)
अणु
	/* Provided burst size is in bytes. The ASIC burst size value is
	 * (2 ^ bs) * 512 bits. Convert the provided size to 512-bit units.
	 */
	u64 bs512 = भाग_u64(burst_bytes, 64);

	अगर (!bs512)
		वापस 0;

	वापस fls64(bs512) - 1;
पूर्ण

अटल u64 mlxsw_sp_policer_single_rate_occ_get(व्योम *priv)
अणु
	काष्ठा mlxsw_sp_policer_family *family = priv;

	वापस atomic_पढ़ो(&family->policers_count);
पूर्ण

अटल पूर्णांक
mlxsw_sp_policer_single_rate_family_init(काष्ठा mlxsw_sp_policer_family *family)
अणु
	काष्ठा mlxsw_core *core = family->mlxsw_sp->core;
	काष्ठा devlink *devlink;

	/* CPU policers are allocated from the first N policers in the global
	 * range, so skip them.
	 */
	अगर (!MLXSW_CORE_RES_VALID(core, MAX_GLOBAL_POLICERS) ||
	    !MLXSW_CORE_RES_VALID(core, MAX_CPU_POLICERS))
		वापस -EIO;

	family->start_index = MLXSW_CORE_RES_GET(core, MAX_CPU_POLICERS);
	family->end_index = MLXSW_CORE_RES_GET(core, MAX_GLOBAL_POLICERS);

	atomic_set(&family->policers_count, 0);
	devlink = priv_to_devlink(core);
	devlink_resource_occ_get_रेजिस्टर(devlink,
					  MLXSW_SP_RESOURCE_SINGLE_RATE_POLICERS,
					  mlxsw_sp_policer_single_rate_occ_get,
					  family);

	वापस 0;
पूर्ण

अटल व्योम
mlxsw_sp_policer_single_rate_family_fini(काष्ठा mlxsw_sp_policer_family *family)
अणु
	काष्ठा devlink *devlink = priv_to_devlink(family->mlxsw_sp->core);

	devlink_resource_occ_get_unरेजिस्टर(devlink,
					    MLXSW_SP_RESOURCE_SINGLE_RATE_POLICERS);
	WARN_ON(atomic_पढ़ो(&family->policers_count) != 0);
पूर्ण

अटल पूर्णांक
mlxsw_sp_policer_single_rate_index_alloc(काष्ठा mlxsw_sp_policer_family *family,
					 काष्ठा mlxsw_sp_policer *policer)
अणु
	पूर्णांक id;

	mutex_lock(&family->lock);
	id = idr_alloc(&family->policer_idr, policer, family->start_index,
		       family->end_index, GFP_KERNEL);
	mutex_unlock(&family->lock);

	अगर (id < 0)
		वापस id;

	atomic_inc(&family->policers_count);
	policer->index = id;

	वापस 0;
पूर्ण

अटल काष्ठा mlxsw_sp_policer *
mlxsw_sp_policer_single_rate_index_मुक्त(काष्ठा mlxsw_sp_policer_family *family,
					u16 policer_index)
अणु
	काष्ठा mlxsw_sp_policer *policer;

	atomic_dec(&family->policers_count);

	mutex_lock(&family->lock);
	policer = idr_हटाओ(&family->policer_idr, policer_index);
	mutex_unlock(&family->lock);

	WARN_ON(!policer);

	वापस policer;
पूर्ण

अटल पूर्णांक
mlxsw_sp_policer_single_rate_init(काष्ठा mlxsw_sp_policer_family *family,
				  स्थिर काष्ठा mlxsw_sp_policer *policer)
अणु
	u64 rate_kbps = mlxsw_sp_policer_rate_bytes_ps_kbps(policer->params.rate);
	u8 bs = mlxsw_sp_policer_burst_bytes_hw_units(policer->params.burst);
	काष्ठा mlxsw_sp *mlxsw_sp = family->mlxsw_sp;
	अक्षर qpcr_pl[MLXSW_REG_QPCR_LEN];

	mlxsw_reg_qpcr_pack(qpcr_pl, policer->index, MLXSW_REG_QPCR_IR_UNITS_K,
			    true, rate_kbps, bs);
	mlxsw_reg_qpcr_clear_counter_set(qpcr_pl, true);

	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(qpcr), qpcr_pl);
पूर्ण

अटल पूर्णांक
mlxsw_sp_policer_single_rate_params_check(स्थिर काष्ठा mlxsw_sp_policer_family *family,
					  स्थिर काष्ठा mlxsw_sp_policer_params *params,
					  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlxsw_sp_policer_core *policer_core = family->mlxsw_sp->policer_core;
	u64 rate_bps = params->rate * BITS_PER_BYTE;
	u8 bs;

	अगर (!params->bytes) अणु
		NL_SET_ERR_MSG_MOD(extack, "Only bandwidth policing is currently supported by single rate policers");
		वापस -EINVAL;
	पूर्ण

	अगर (!is_घातer_of_2(params->burst)) अणु
		NL_SET_ERR_MSG_MOD(extack, "Policer burst size is not power of two");
		वापस -EINVAL;
	पूर्ण

	bs = mlxsw_sp_policer_burst_bytes_hw_units(params->burst);

	अगर (bs < policer_core->lowest_bs_bits) अणु
		NL_SET_ERR_MSG_MOD(extack, "Policer burst size lower than limit");
		वापस -EINVAL;
	पूर्ण

	अगर (bs > policer_core->highest_bs_bits) अणु
		NL_SET_ERR_MSG_MOD(extack, "Policer burst size higher than limit");
		वापस -EINVAL;
	पूर्ण

	अगर (rate_bps < MLXSW_REG_QPCR_LOWEST_CIR_BITS) अणु
		NL_SET_ERR_MSG_MOD(extack, "Policer rate lower than limit");
		वापस -EINVAL;
	पूर्ण

	अगर (rate_bps > MLXSW_REG_QPCR_HIGHEST_CIR_BITS) अणु
		NL_SET_ERR_MSG_MOD(extack, "Policer rate higher than limit");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mlxsw_sp_policer_family_ops mlxsw_sp_policer_single_rate_ops = अणु
	.init			= mlxsw_sp_policer_single_rate_family_init,
	.fini			= mlxsw_sp_policer_single_rate_family_fini,
	.policer_index_alloc	= mlxsw_sp_policer_single_rate_index_alloc,
	.policer_index_मुक्त	= mlxsw_sp_policer_single_rate_index_मुक्त,
	.policer_init		= mlxsw_sp_policer_single_rate_init,
	.policer_params_check	= mlxsw_sp_policer_single_rate_params_check,
पूर्ण;

अटल स्थिर काष्ठा mlxsw_sp_policer_family mlxsw_sp_policer_single_rate_family = अणु
	.type		= MLXSW_SP_POLICER_TYPE_SINGLE_RATE,
	.qpcr_type	= MLXSW_REG_QPCR_G_GLOBAL,
	.ops		= &mlxsw_sp_policer_single_rate_ops,
पूर्ण;

अटल स्थिर काष्ठा mlxsw_sp_policer_family *mlxsw_sp_policer_family_arr[] = अणु
	[MLXSW_SP_POLICER_TYPE_SINGLE_RATE]	= &mlxsw_sp_policer_single_rate_family,
पूर्ण;

पूर्णांक mlxsw_sp_policer_add(काष्ठा mlxsw_sp *mlxsw_sp,
			 क्रमागत mlxsw_sp_policer_type type,
			 स्थिर काष्ठा mlxsw_sp_policer_params *params,
			 काष्ठा netlink_ext_ack *extack, u16 *p_policer_index)
अणु
	काष्ठा mlxsw_sp_policer_family *family;
	काष्ठा mlxsw_sp_policer *policer;
	पूर्णांक err;

	family = mlxsw_sp->policer_core->family_arr[type];

	err = family->ops->policer_params_check(family, params, extack);
	अगर (err)
		वापस err;

	policer = kदो_स्मृति(माप(*policer), GFP_KERNEL);
	अगर (!policer)
		वापस -ENOMEM;
	policer->params = *params;

	err = family->ops->policer_index_alloc(family, policer);
	अगर (err) अणु
		NL_SET_ERR_MSG_MOD(extack, "Failed to allocate policer index");
		जाओ err_policer_index_alloc;
	पूर्ण

	err = family->ops->policer_init(family, policer);
	अगर (err) अणु
		NL_SET_ERR_MSG_MOD(extack, "Failed to initialize policer");
		जाओ err_policer_init;
	पूर्ण

	*p_policer_index = policer->index;

	वापस 0;

err_policer_init:
	family->ops->policer_index_मुक्त(family, policer->index);
err_policer_index_alloc:
	kमुक्त(policer);
	वापस err;
पूर्ण

व्योम mlxsw_sp_policer_del(काष्ठा mlxsw_sp *mlxsw_sp,
			  क्रमागत mlxsw_sp_policer_type type, u16 policer_index)
अणु
	काष्ठा mlxsw_sp_policer_family *family;
	काष्ठा mlxsw_sp_policer *policer;

	family = mlxsw_sp->policer_core->family_arr[type];
	policer = family->ops->policer_index_मुक्त(family, policer_index);
	kमुक्त(policer);
पूर्ण

पूर्णांक mlxsw_sp_policer_drops_counter_get(काष्ठा mlxsw_sp *mlxsw_sp,
				       क्रमागत mlxsw_sp_policer_type type,
				       u16 policer_index, u64 *p_drops)
अणु
	काष्ठा mlxsw_sp_policer_family *family;
	अक्षर qpcr_pl[MLXSW_REG_QPCR_LEN];
	पूर्णांक err;

	family = mlxsw_sp->policer_core->family_arr[type];

	MLXSW_REG_ZERO(qpcr, qpcr_pl);
	mlxsw_reg_qpcr_pid_set(qpcr_pl, policer_index);
	mlxsw_reg_qpcr_g_set(qpcr_pl, family->qpcr_type);
	err = mlxsw_reg_query(mlxsw_sp->core, MLXSW_REG(qpcr), qpcr_pl);
	अगर (err)
		वापस err;

	*p_drops = mlxsw_reg_qpcr_violate_count_get(qpcr_pl);

	वापस 0;
पूर्ण

अटल पूर्णांक
mlxsw_sp_policer_family_रेजिस्टर(काष्ठा mlxsw_sp *mlxsw_sp,
				 स्थिर काष्ठा mlxsw_sp_policer_family *पंचांगpl)
अणु
	काष्ठा mlxsw_sp_policer_family *family;
	पूर्णांक err;

	family = kmemdup(पंचांगpl, माप(*family), GFP_KERNEL);
	अगर (!family)
		वापस -ENOMEM;

	family->mlxsw_sp = mlxsw_sp;
	idr_init(&family->policer_idr);
	mutex_init(&family->lock);

	err = family->ops->init(family);
	अगर (err)
		जाओ err_family_init;

	अगर (WARN_ON(family->start_index >= family->end_index)) अणु
		err = -EINVAL;
		जाओ err_index_check;
	पूर्ण

	mlxsw_sp->policer_core->family_arr[पंचांगpl->type] = family;

	वापस 0;

err_index_check:
	family->ops->fini(family);
err_family_init:
	mutex_destroy(&family->lock);
	idr_destroy(&family->policer_idr);
	kमुक्त(family);
	वापस err;
पूर्ण

अटल व्योम
mlxsw_sp_policer_family_unरेजिस्टर(काष्ठा mlxsw_sp *mlxsw_sp,
				   काष्ठा mlxsw_sp_policer_family *family)
अणु
	family->ops->fini(family);
	mutex_destroy(&family->lock);
	WARN_ON(!idr_is_empty(&family->policer_idr));
	idr_destroy(&family->policer_idr);
	kमुक्त(family);
पूर्ण

पूर्णांक mlxsw_sp_policers_init(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	काष्ठा mlxsw_sp_policer_core *policer_core;
	पूर्णांक i, err;

	policer_core = kzalloc(माप(*policer_core), GFP_KERNEL);
	अगर (!policer_core)
		वापस -ENOMEM;
	mlxsw_sp->policer_core = policer_core;
	policer_core->ops = mlxsw_sp->policer_core_ops;

	err = policer_core->ops->init(policer_core);
	अगर (err)
		जाओ err_init;

	क्रम (i = 0; i < MLXSW_SP_POLICER_TYPE_MAX + 1; i++) अणु
		err = mlxsw_sp_policer_family_रेजिस्टर(mlxsw_sp, mlxsw_sp_policer_family_arr[i]);
		अगर (err)
			जाओ err_family_रेजिस्टर;
	पूर्ण

	वापस 0;

err_family_रेजिस्टर:
	क्रम (i--; i >= 0; i--) अणु
		काष्ठा mlxsw_sp_policer_family *family;

		family = mlxsw_sp->policer_core->family_arr[i];
		mlxsw_sp_policer_family_unरेजिस्टर(mlxsw_sp, family);
	पूर्ण
err_init:
	kमुक्त(mlxsw_sp->policer_core);
	वापस err;
पूर्ण

व्योम mlxsw_sp_policers_fini(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	पूर्णांक i;

	क्रम (i = MLXSW_SP_POLICER_TYPE_MAX; i >= 0; i--) अणु
		काष्ठा mlxsw_sp_policer_family *family;

		family = mlxsw_sp->policer_core->family_arr[i];
		mlxsw_sp_policer_family_unरेजिस्टर(mlxsw_sp, family);
	पूर्ण

	kमुक्त(mlxsw_sp->policer_core);
पूर्ण

पूर्णांक mlxsw_sp_policer_resources_रेजिस्टर(काष्ठा mlxsw_core *mlxsw_core)
अणु
	u64 global_policers, cpu_policers, single_rate_policers;
	काष्ठा devlink *devlink = priv_to_devlink(mlxsw_core);
	काष्ठा devlink_resource_size_params size_params;
	पूर्णांक err;

	अगर (!MLXSW_CORE_RES_VALID(mlxsw_core, MAX_GLOBAL_POLICERS) ||
	    !MLXSW_CORE_RES_VALID(mlxsw_core, MAX_CPU_POLICERS))
		वापस -EIO;

	global_policers = MLXSW_CORE_RES_GET(mlxsw_core, MAX_GLOBAL_POLICERS);
	cpu_policers = MLXSW_CORE_RES_GET(mlxsw_core, MAX_CPU_POLICERS);
	single_rate_policers = global_policers - cpu_policers;

	devlink_resource_size_params_init(&size_params, global_policers,
					  global_policers, 1,
					  DEVLINK_RESOURCE_UNIT_ENTRY);
	err = devlink_resource_रेजिस्टर(devlink, "global_policers",
					global_policers,
					MLXSW_SP_RESOURCE_GLOBAL_POLICERS,
					DEVLINK_RESOURCE_ID_PARENT_TOP,
					&size_params);
	अगर (err)
		वापस err;

	devlink_resource_size_params_init(&size_params, single_rate_policers,
					  single_rate_policers, 1,
					  DEVLINK_RESOURCE_UNIT_ENTRY);
	err = devlink_resource_रेजिस्टर(devlink, "single_rate_policers",
					single_rate_policers,
					MLXSW_SP_RESOURCE_SINGLE_RATE_POLICERS,
					MLXSW_SP_RESOURCE_GLOBAL_POLICERS,
					&size_params);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक
mlxsw_sp1_policer_core_init(काष्ठा mlxsw_sp_policer_core *policer_core)
अणु
	policer_core->lowest_bs_bits = MLXSW_REG_QPCR_LOWEST_CBS_BITS_SP1;
	policer_core->highest_bs_bits = MLXSW_REG_QPCR_HIGHEST_CBS_BITS_SP1;

	वापस 0;
पूर्ण

स्थिर काष्ठा mlxsw_sp_policer_core_ops mlxsw_sp1_policer_core_ops = अणु
	.init = mlxsw_sp1_policer_core_init,
पूर्ण;

अटल पूर्णांक
mlxsw_sp2_policer_core_init(काष्ठा mlxsw_sp_policer_core *policer_core)
अणु
	policer_core->lowest_bs_bits = MLXSW_REG_QPCR_LOWEST_CBS_BITS_SP2;
	policer_core->highest_bs_bits = MLXSW_REG_QPCR_HIGHEST_CBS_BITS_SP2;

	वापस 0;
पूर्ण

स्थिर काष्ठा mlxsw_sp_policer_core_ops mlxsw_sp2_policer_core_ops = अणु
	.init = mlxsw_sp2_policer_core_init,
पूर्ण;
