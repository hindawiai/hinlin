<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0 */
/* Copyright (c) 2017-2018 Mellanox Technologies. All rights reserved */

#अगर_अघोषित _MLXSW_SPECTRUM_MCROUTER_H
#घोषणा _MLXSW_SPECTRUM_MCROUTER_H

#समावेश <linux/mroute.h>
#समावेश <linux/mroute6.h>
#समावेश "spectrum_router.h"
#समावेश "spectrum.h"

क्रमागत mlxsw_sp_mr_route_action अणु
	MLXSW_SP_MR_ROUTE_ACTION_FORWARD,
	MLXSW_SP_MR_ROUTE_ACTION_TRAP,
	MLXSW_SP_MR_ROUTE_ACTION_TRAP_AND_FORWARD,
पूर्ण;

काष्ठा mlxsw_sp_mr_route_key अणु
	पूर्णांक vrid;
	क्रमागत mlxsw_sp_l3proto proto;
	जोड़ mlxsw_sp_l3addr group;
	जोड़ mlxsw_sp_l3addr group_mask;
	जोड़ mlxsw_sp_l3addr source;
	जोड़ mlxsw_sp_l3addr source_mask;
पूर्ण;

काष्ठा mlxsw_sp_mr_route_info अणु
	क्रमागत mlxsw_sp_mr_route_action route_action;
	u16 irअगर_index;
	u16 *erअगर_indices;
	माप_प्रकार erअगर_num;
	u16 min_mtu;
पूर्ण;

काष्ठा mlxsw_sp_mr_route_params अणु
	काष्ठा mlxsw_sp_mr_route_key key;
	काष्ठा mlxsw_sp_mr_route_info value;
	क्रमागत mlxsw_sp_mr_route_prio prio;
पूर्ण;

काष्ठा mlxsw_sp_mr_ops अणु
	पूर्णांक priv_size;
	पूर्णांक route_priv_size;
	पूर्णांक (*init)(काष्ठा mlxsw_sp *mlxsw_sp, व्योम *priv);
	पूर्णांक (*route_create)(काष्ठा mlxsw_sp *mlxsw_sp, व्योम *priv,
			    व्योम *route_priv,
			    काष्ठा mlxsw_sp_mr_route_params *route_params);
	पूर्णांक (*route_update)(काष्ठा mlxsw_sp *mlxsw_sp, व्योम *route_priv,
			    काष्ठा mlxsw_sp_mr_route_info *route_info);
	पूर्णांक (*route_stats)(काष्ठा mlxsw_sp *mlxsw_sp, व्योम *route_priv,
			   u64 *packets, u64 *bytes);
	पूर्णांक (*route_action_update)(काष्ठा mlxsw_sp *mlxsw_sp, व्योम *route_priv,
				   क्रमागत mlxsw_sp_mr_route_action route_action);
	पूर्णांक (*route_min_mtu_update)(काष्ठा mlxsw_sp *mlxsw_sp, व्योम *route_priv,
				    u16 min_mtu);
	पूर्णांक (*route_irअगर_update)(काष्ठा mlxsw_sp *mlxsw_sp, व्योम *route_priv,
				 u16 irअगर_index);
	पूर्णांक (*route_erअगर_add)(काष्ठा mlxsw_sp *mlxsw_sp, व्योम *route_priv,
			      u16 erअगर_index);
	पूर्णांक (*route_erअगर_del)(काष्ठा mlxsw_sp *mlxsw_sp, व्योम *route_priv,
			      u16 erअगर_index);
	व्योम (*route_destroy)(काष्ठा mlxsw_sp *mlxsw_sp, व्योम *priv,
			      व्योम *route_priv);
	व्योम (*fini)(काष्ठा mlxsw_sp *mlxsw_sp, व्योम *priv);
पूर्ण;

काष्ठा mlxsw_sp_mr;
काष्ठा mlxsw_sp_mr_table;

पूर्णांक mlxsw_sp_mr_init(काष्ठा mlxsw_sp *mlxsw_sp,
		     स्थिर काष्ठा mlxsw_sp_mr_ops *mr_ops);
व्योम mlxsw_sp_mr_fini(काष्ठा mlxsw_sp *mlxsw_sp);
पूर्णांक mlxsw_sp_mr_route_add(काष्ठा mlxsw_sp_mr_table *mr_table,
			  काष्ठा mr_mfc *mfc, bool replace);
व्योम mlxsw_sp_mr_route_del(काष्ठा mlxsw_sp_mr_table *mr_table,
			   काष्ठा mr_mfc *mfc);
पूर्णांक mlxsw_sp_mr_vअगर_add(काष्ठा mlxsw_sp_mr_table *mr_table,
			काष्ठा net_device *dev, vअगरi_t vअगर_index,
			अचिन्हित दीर्घ vअगर_flags,
			स्थिर काष्ठा mlxsw_sp_rअगर *rअगर);
व्योम mlxsw_sp_mr_vअगर_del(काष्ठा mlxsw_sp_mr_table *mr_table, vअगरi_t vअगर_index);
पूर्णांक mlxsw_sp_mr_rअगर_add(काष्ठा mlxsw_sp_mr_table *mr_table,
			स्थिर काष्ठा mlxsw_sp_rअगर *rअगर);
व्योम mlxsw_sp_mr_rअगर_del(काष्ठा mlxsw_sp_mr_table *mr_table,
			 स्थिर काष्ठा mlxsw_sp_rअगर *rअगर);
व्योम mlxsw_sp_mr_rअगर_mtu_update(काष्ठा mlxsw_sp_mr_table *mr_table,
				स्थिर काष्ठा mlxsw_sp_rअगर *rअगर, पूर्णांक mtu);
काष्ठा mlxsw_sp_mr_table *mlxsw_sp_mr_table_create(काष्ठा mlxsw_sp *mlxsw_sp,
						   u32 tb_id,
						   क्रमागत mlxsw_sp_l3proto proto);
व्योम mlxsw_sp_mr_table_destroy(काष्ठा mlxsw_sp_mr_table *mr_table);
व्योम mlxsw_sp_mr_table_flush(काष्ठा mlxsw_sp_mr_table *mr_table);
bool mlxsw_sp_mr_table_empty(स्थिर काष्ठा mlxsw_sp_mr_table *mr_table);

#पूर्ण_अगर
