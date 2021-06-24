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

#अगर_अघोषित __IA_CSS_MORPH_H
#घोषणा __IA_CSS_MORPH_H

/* @file
 * This file contains supporting क्रम morphing table
 */

#समावेश <ia_css_types.h>

/* @brief Morphing table
 * @param[in]	width Width of the morphing table.
 * @param[in]	height Height of the morphing table.
 * @वापस		Poपूर्णांकer to the morphing table
*/
काष्ठा ia_css_morph_table *
ia_css_morph_table_allocate(अचिन्हित पूर्णांक width, अचिन्हित पूर्णांक height);

/* @brief Free the morph table
 * @param[in]	me Poपूर्णांकer to the morph table.
 * @वापस		None
*/
व्योम
ia_css_morph_table_मुक्त(काष्ठा ia_css_morph_table *me);

#पूर्ण_अगर /* __IA_CSS_MORPH_H */
