<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0 */
/* Copyright (c) 2020 Mellanox Technologies. All rights reserved */

#अगर_अघोषित _MLXSW_SPECTRUM_TRAP_H
#घोषणा _MLXSW_SPECTRUM_TRAP_H

#समावेश <linux/list.h>
#समावेश <net/devlink.h>

काष्ठा mlxsw_sp_trap अणु
	काष्ठा mlxsw_sp_trap_policer_item *policer_items_arr;
	माप_प्रकार policers_count; /* Number of रेजिस्टरed policers */

	काष्ठा mlxsw_sp_trap_group_item *group_items_arr;
	माप_प्रकार groups_count; /* Number of रेजिस्टरed groups */

	काष्ठा mlxsw_sp_trap_item *trap_items_arr;
	माप_प्रकार traps_count; /* Number of रेजिस्टरed traps */

	u16 thin_policer_hw_id;

	u64 max_policers;
	अचिन्हित दीर्घ policers_usage[]; /* Usage biपंचांगap */
पूर्ण;

काष्ठा mlxsw_sp_trap_ops अणु
	पूर्णांक (*groups_init)(काष्ठा mlxsw_sp *mlxsw_sp,
			   स्थिर काष्ठा mlxsw_sp_trap_group_item **arr,
			   माप_प्रकार *p_groups_count);
	पूर्णांक (*traps_init)(काष्ठा mlxsw_sp *mlxsw_sp,
			  स्थिर काष्ठा mlxsw_sp_trap_item **arr,
			  माप_प्रकार *p_traps_count);
पूर्ण;

बाह्य स्थिर काष्ठा mlxsw_sp_trap_ops mlxsw_sp1_trap_ops;
बाह्य स्थिर काष्ठा mlxsw_sp_trap_ops mlxsw_sp2_trap_ops;

#पूर्ण_अगर
