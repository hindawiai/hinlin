<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0 */
/* Copyright (c) 2017-2018 Mellanox Technologies. All rights reserved */

#अगर_अघोषित _MLXSW_SPECTRUM_CNT_H
#घोषणा _MLXSW_SPECTRUM_CNT_H

#समावेश "core.h"
#समावेश "spectrum.h"

क्रमागत mlxsw_sp_counter_sub_pool_id अणु
	MLXSW_SP_COUNTER_SUB_POOL_FLOW,
	MLXSW_SP_COUNTER_SUB_POOL_RIF,
पूर्ण;

पूर्णांक mlxsw_sp_counter_alloc(काष्ठा mlxsw_sp *mlxsw_sp,
			   क्रमागत mlxsw_sp_counter_sub_pool_id sub_pool_id,
			   अचिन्हित पूर्णांक *p_counter_index);
व्योम mlxsw_sp_counter_मुक्त(काष्ठा mlxsw_sp *mlxsw_sp,
			   क्रमागत mlxsw_sp_counter_sub_pool_id sub_pool_id,
			   अचिन्हित पूर्णांक counter_index);
पूर्णांक mlxsw_sp_counter_pool_init(काष्ठा mlxsw_sp *mlxsw_sp);
व्योम mlxsw_sp_counter_pool_fini(काष्ठा mlxsw_sp *mlxsw_sp);
पूर्णांक mlxsw_sp_counter_resources_रेजिस्टर(काष्ठा mlxsw_core *mlxsw_core);

#पूर्ण_अगर
