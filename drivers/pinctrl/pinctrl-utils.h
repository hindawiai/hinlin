<शैली गुरु>
/*
 * Utils functions to implement the pincontrol driver.
 *
 * Copyright (c) 2013, NVIDIA Corporation.
 *
 * Author: Laxman Dewangan <ldewangan@nvidia.com>
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any kind,
 * whether express or implied; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
 * 02111-1307, USA
 */
#अगर_अघोषित __PINCTRL_UTILS_H__
#घोषणा __PINCTRL_UTILS_H__

पूर्णांक pinctrl_utils_reserve_map(काष्ठा pinctrl_dev *pctldev,
		काष्ठा pinctrl_map **map, अचिन्हित *reserved_maps,
		अचिन्हित *num_maps, अचिन्हित reserve);
पूर्णांक pinctrl_utils_add_map_mux(काष्ठा pinctrl_dev *pctldev,
		काष्ठा pinctrl_map **map, अचिन्हित *reserved_maps,
		अचिन्हित *num_maps, स्थिर अक्षर *group,
		स्थिर अक्षर *function);
पूर्णांक pinctrl_utils_add_map_configs(काष्ठा pinctrl_dev *pctldev,
		काष्ठा pinctrl_map **map, अचिन्हित *reserved_maps,
		अचिन्हित *num_maps, स्थिर अक्षर *group,
		अचिन्हित दीर्घ *configs, अचिन्हित num_configs,
		क्रमागत pinctrl_map_type type);
पूर्णांक pinctrl_utils_add_config(काष्ठा pinctrl_dev *pctldev,
		अचिन्हित दीर्घ **configs, अचिन्हित *num_configs,
		अचिन्हित दीर्घ config);
व्योम pinctrl_utils_मुक्त_map(काष्ठा pinctrl_dev *pctldev,
		काष्ठा pinctrl_map *map, अचिन्हित num_maps);

#पूर्ण_अगर /* __PINCTRL_UTILS_H__ */
