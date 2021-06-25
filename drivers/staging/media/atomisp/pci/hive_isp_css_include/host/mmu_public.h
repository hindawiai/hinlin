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

#अगर_अघोषित __MMU_PUBLIC_H_INCLUDED__
#घोषणा __MMU_PUBLIC_H_INCLUDED__

#समावेश "system_local.h"
#समावेश "device_access.h"
#समावेश "assert_support.h"

/*! Set the page table base index of MMU[ID]

 \param	ID[in]				MMU identअगरier
 \param	base_index[in]		page table base index

 \लeturn none, MMU[ID].page_table_base_index = base_index
 */
व्योम mmu_set_page_table_base_index(
    स्थिर mmu_ID_t		ID,
    स्थिर hrt_data		base_index);

/*! Get the page table base index of MMU[ID]

 \param	ID[in]				MMU identअगरier
 \param	base_index[in]		page table base index

 \लeturn MMU[ID].page_table_base_index
 */
hrt_data mmu_get_page_table_base_index(
    स्थिर mmu_ID_t		ID);

/*! Invalidate the page table cache of MMU[ID]

 \param	ID[in]				MMU identअगरier

 \लeturn none
 */
व्योम mmu_invalidate_cache(
    स्थिर mmu_ID_t		ID);

/*! Invalidate the page table cache of all MMUs

 \लeturn none
 */
व्योम mmu_invalidate_cache_all(व्योम);

/*! Write to a control रेजिस्टर of MMU[ID]

 \param	ID[in]				MMU identअगरier
 \param	reg[in]				रेजिस्टर index
 \param value[in]			The data to be written

 \लeturn none, MMU[ID].ctrl[reg] = value
 */
अटल अंतरभूत व्योम mmu_reg_store(
    स्थिर mmu_ID_t		ID,
    स्थिर अचिन्हित पूर्णांक	reg,
    स्थिर hrt_data		value)
अणु
	निश्चित(ID < N_MMU_ID);
	निश्चित(MMU_BASE[ID] != (hrt_address) - 1);
	ia_css_device_store_uपूर्णांक32(MMU_BASE[ID] + reg * माप(hrt_data), value);
	वापस;
पूर्ण

/*! Read from a control रेजिस्टर of MMU[ID]

 \param	ID[in]				MMU identअगरier
 \param	reg[in]				रेजिस्टर index
 \param value[in]			The data to be written

 \लeturn MMU[ID].ctrl[reg]
 */
अटल अंतरभूत hrt_data mmu_reg_load(
    स्थिर mmu_ID_t		ID,
    स्थिर अचिन्हित पूर्णांक	reg)
अणु
	निश्चित(ID < N_MMU_ID);
	निश्चित(MMU_BASE[ID] != (hrt_address) - 1);
	वापस ia_css_device_load_uपूर्णांक32(MMU_BASE[ID] + reg * माप(hrt_data));
पूर्ण

#पूर्ण_अगर /* __MMU_PUBLIC_H_INCLUDED__ */
