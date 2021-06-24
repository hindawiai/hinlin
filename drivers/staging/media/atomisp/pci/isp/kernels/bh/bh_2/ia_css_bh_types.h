<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Support क्रम Intel Camera Imaging ISP subप्रणाली.
 * Copyright (c) 2015, Intel Corporation.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License क्रम
 * more details.
 */

#अगर_अघोषित __IA_CSS_BH_TYPES_H
#घोषणा __IA_CSS_BH_TYPES_H

/* Number of elements in the BH table.
  * Should be consistent with hस्मृति.स
  */
#घोषणा IA_CSS_HMEM_BH_TABLE_SIZE	ISP_HIST_DEPTH
#घोषणा IA_CSS_HMEM_BH_UNIT_SIZE	(ISP_HIST_DEPTH / ISP_HIST_COMPONENTS)

#घोषणा BH_COLOR_R	(0)
#घोषणा BH_COLOR_G	(1)
#घोषणा BH_COLOR_B	(2)
#घोषणा BH_COLOR_Y	(3)
#घोषणा BH_COLOR_NUM	(4)

/* BH table */
काष्ठा ia_css_bh_table अणु
	u32 hmem[ISP_HIST_COMPONENTS][IA_CSS_HMEM_BH_UNIT_SIZE];
पूर्ण;

#पूर्ण_अगर /* __IA_CSS_BH_TYPES_H */
