<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Support क्रम Intel Camera Imaging ISP subप्रणाली.
 *
 * Copyright (c) 2013 Intel Corporation. All Rights Reserved.
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License version
 * 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 *
 */
#अगर_अघोषित	__ATOMISP_DFS_TABLES_H__
#घोषणा	__ATOMISP_DFS_TABLES_H__

#समावेश <linux/kernel.h>

काष्ठा atomisp_freq_scaling_rule अणु
	अचिन्हित पूर्णांक width;
	अचिन्हित पूर्णांक height;
	अचिन्हित लघु fps;
	अचिन्हित पूर्णांक isp_freq;
	अचिन्हित पूर्णांक run_mode;
पूर्ण;

काष्ठा atomisp_dfs_config अणु
	अचिन्हित पूर्णांक lowest_freq;
	अचिन्हित पूर्णांक max_freq_at_vmin;
	अचिन्हित पूर्णांक highest_freq;
	स्थिर काष्ठा atomisp_freq_scaling_rule *dfs_table;
	अचिन्हित पूर्णांक dfs_table_size;
पूर्ण;

बाह्य स्थिर काष्ठा atomisp_dfs_config dfs_config_cht_soc;

#पूर्ण_अगर /* __ATOMISP_DFS_TABLES_H__ */
