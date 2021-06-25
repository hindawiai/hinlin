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

#अगर_अघोषित __IA_CSS_PROPERTIES_H
#घोषणा __IA_CSS_PROPERTIES_H

/* @file
 * This file contains support क्रम retrieving properties of some hardware the CSS प्रणाली
 */

#समावेश <type_support.h> /* bool */
#समावेश <ia_css_types.h> /* ia_css_vamem_type */

काष्ठा ia_css_properties अणु
	पूर्णांक  gdc_coord_one;
	bool l1_base_is_index; /** Indicate whether the L1 page base
				    is a page index or a byte address. */
	क्रमागत ia_css_vamem_type vamem_type;
पूर्ण;

/* @brief Get hardware properties
 * @param[in,out]	properties The hardware properties
 * @वापस	None
 *
 * This function वापसs a number of hardware properties.
 */
व्योम
ia_css_get_properties(काष्ठा ia_css_properties *properties);

#पूर्ण_अगर /* __IA_CSS_PROPERTIES_H */
