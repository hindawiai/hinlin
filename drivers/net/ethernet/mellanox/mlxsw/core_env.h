<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0 */
/* Copyright (c) 2018 Mellanox Technologies. All rights reserved */

#अगर_अघोषित _MLXSW_CORE_ENV_H
#घोषणा _MLXSW_CORE_ENV_H

काष्ठा ethtool_modinfo;
काष्ठा ethtool_eeprom;

पूर्णांक mlxsw_env_module_temp_thresholds_get(काष्ठा mlxsw_core *core, पूर्णांक module,
					 पूर्णांक off, पूर्णांक *temp);

पूर्णांक mlxsw_env_get_module_info(काष्ठा mlxsw_core *mlxsw_core, पूर्णांक module,
			      काष्ठा ethtool_modinfo *modinfo);

पूर्णांक mlxsw_env_get_module_eeprom(काष्ठा net_device *netdev,
				काष्ठा mlxsw_core *mlxsw_core, पूर्णांक module,
				काष्ठा ethtool_eeprom *ee, u8 *data);

पूर्णांक
mlxsw_env_module_overheat_counter_get(काष्ठा mlxsw_core *mlxsw_core, u8 module,
				      u64 *p_counter);
पूर्णांक mlxsw_env_init(काष्ठा mlxsw_core *core, काष्ठा mlxsw_env **p_env);
व्योम mlxsw_env_fini(काष्ठा mlxsw_env *env);

#पूर्ण_अगर
