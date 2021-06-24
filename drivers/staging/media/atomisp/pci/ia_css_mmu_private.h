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

#अगर_अघोषित __IA_CSS_MMU_PRIVATE_H
#घोषणा __IA_CSS_MMU_PRIVATE_H

#समावेश "system_local.h"

/*
 * This function sets the L1 pagetable address.
 * After घातer-up of the ISP the L1 pagetable can be set.
 * Once being set the L1 pagetable is रक्षित against
 * further modअगरications.
 */
व्योम
sh_css_mmu_set_page_table_base_index(hrt_data base_index);

#पूर्ण_अगर /* __IA_CSS_MMU_PRIVATE_H */
