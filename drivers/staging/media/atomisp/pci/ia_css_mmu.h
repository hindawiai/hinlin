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

#अगर_अघोषित __IA_CSS_MMU_H
#घोषणा __IA_CSS_MMU_H

/* @file
 * This file contains one support function क्रम invalidating the CSS MMU cache
 */

/* @brief Invalidate the MMU पूर्णांकernal cache.
 * @वापस	None
 *
 * This function triggers an invalidation of the translate-look-aside
 * buffer (TLB) that's inside the CSS MMU. This function should be called
 * every समय the page tables used by the MMU change.
 */
व्योम
ia_css_mmu_invalidate_cache(व्योम);

#पूर्ण_अगर /* __IA_CSS_MMU_H */
