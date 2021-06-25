<शैली गुरु>
/*
 * Copyright (c) 2004, 2005 Topspin Communications.  All rights reserved.
 * Copyright (c) 2005 Cisco Systems.  All rights reserved.
 * Copyright (c) 2005 Mellanox Technologies. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#अगर_अघोषित MTHCA_MEMFREE_H
#घोषणा MTHCA_MEMFREE_H

#समावेश <linux/list.h>
#समावेश <linux/mutex.h>

#घोषणा MTHCA_ICM_CHUNK_LEN \
	((256 - माप (काष्ठा list_head) - 2 * माप (पूर्णांक)) /		\
	 (माप (काष्ठा scatterlist)))

क्रमागत अणु
	MTHCA_ICM_PAGE_SHIFT	= 12,
	MTHCA_ICM_PAGE_SIZE	= 1 << MTHCA_ICM_PAGE_SHIFT,
	MTHCA_DB_REC_PER_PAGE	= MTHCA_ICM_PAGE_SIZE / 8
पूर्ण;

काष्ठा mthca_icm_chunk अणु
	काष्ठा list_head   list;
	पूर्णांक                npages;
	पूर्णांक                nsg;
	काष्ठा scatterlist mem[MTHCA_ICM_CHUNK_LEN];
पूर्ण;

काष्ठा mthca_icm अणु
	काष्ठा list_head chunk_list;
	पूर्णांक              refcount;
पूर्ण;

काष्ठा mthca_icm_table अणु
	u64               virt;
	पूर्णांक               num_icm;
	पूर्णांक               num_obj;
	पूर्णांक               obj_size;
	पूर्णांक               lowmem;
	पूर्णांक               coherent;
	काष्ठा mutex      mutex;
	काष्ठा mthca_icm *icm[];
पूर्ण;

काष्ठा mthca_icm_iter अणु
	काष्ठा mthca_icm       *icm;
	काष्ठा mthca_icm_chunk *chunk;
	पूर्णांक                     page_idx;
पूर्ण;

काष्ठा mthca_dev;

काष्ठा mthca_icm *mthca_alloc_icm(काष्ठा mthca_dev *dev, पूर्णांक npages,
				  gfp_t gfp_mask, पूर्णांक coherent);
व्योम mthca_मुक्त_icm(काष्ठा mthca_dev *dev, काष्ठा mthca_icm *icm, पूर्णांक coherent);

काष्ठा mthca_icm_table *mthca_alloc_icm_table(काष्ठा mthca_dev *dev,
					      u64 virt, पूर्णांक obj_size,
					      पूर्णांक nobj, पूर्णांक reserved,
					      पूर्णांक use_lowmem, पूर्णांक use_coherent);
व्योम mthca_मुक्त_icm_table(काष्ठा mthca_dev *dev, काष्ठा mthca_icm_table *table);
पूर्णांक mthca_table_get(काष्ठा mthca_dev *dev, काष्ठा mthca_icm_table *table, पूर्णांक obj);
व्योम mthca_table_put(काष्ठा mthca_dev *dev, काष्ठा mthca_icm_table *table, पूर्णांक obj);
व्योम *mthca_table_find(काष्ठा mthca_icm_table *table, पूर्णांक obj, dma_addr_t *dma_handle);
पूर्णांक mthca_table_get_range(काष्ठा mthca_dev *dev, काष्ठा mthca_icm_table *table,
			  पूर्णांक start, पूर्णांक end);
व्योम mthca_table_put_range(काष्ठा mthca_dev *dev, काष्ठा mthca_icm_table *table,
			   पूर्णांक start, पूर्णांक end);

अटल अंतरभूत व्योम mthca_icm_first(काष्ठा mthca_icm *icm,
				   काष्ठा mthca_icm_iter *iter)
अणु
	iter->icm      = icm;
	iter->chunk    = list_empty(&icm->chunk_list) ?
		शून्य : list_entry(icm->chunk_list.next,
				  काष्ठा mthca_icm_chunk, list);
	iter->page_idx = 0;
पूर्ण

अटल अंतरभूत पूर्णांक mthca_icm_last(काष्ठा mthca_icm_iter *iter)
अणु
	वापस !iter->chunk;
पूर्ण

अटल अंतरभूत व्योम mthca_icm_next(काष्ठा mthca_icm_iter *iter)
अणु
	अगर (++iter->page_idx >= iter->chunk->nsg) अणु
		अगर (iter->chunk->list.next == &iter->icm->chunk_list) अणु
			iter->chunk = शून्य;
			वापस;
		पूर्ण

		iter->chunk = list_entry(iter->chunk->list.next,
					 काष्ठा mthca_icm_chunk, list);
		iter->page_idx = 0;
	पूर्ण
पूर्ण

अटल अंतरभूत dma_addr_t mthca_icm_addr(काष्ठा mthca_icm_iter *iter)
अणु
	वापस sg_dma_address(&iter->chunk->mem[iter->page_idx]);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ mthca_icm_size(काष्ठा mthca_icm_iter *iter)
अणु
	वापस sg_dma_len(&iter->chunk->mem[iter->page_idx]);
पूर्ण

काष्ठा mthca_db_page अणु
	DECLARE_BITMAP(used, MTHCA_DB_REC_PER_PAGE);
	__be64    *db_rec;
	dma_addr_t mapping;
पूर्ण;

काष्ठा mthca_db_table अणु
	पूर्णांक 	       	      npages;
	पूर्णांक 	       	      max_group1;
	पूर्णांक 	       	      min_group2;
	काष्ठा mthca_db_page *page;
	काष्ठा mutex          mutex;
पूर्ण;

क्रमागत mthca_db_type अणु
	MTHCA_DB_TYPE_INVALID   = 0x0,
	MTHCA_DB_TYPE_CQ_SET_CI = 0x1,
	MTHCA_DB_TYPE_CQ_ARM    = 0x2,
	MTHCA_DB_TYPE_SQ        = 0x3,
	MTHCA_DB_TYPE_RQ        = 0x4,
	MTHCA_DB_TYPE_SRQ       = 0x5,
	MTHCA_DB_TYPE_GROUP_SEP = 0x7
पूर्ण;

काष्ठा mthca_user_db_table;
काष्ठा mthca_uar;

पूर्णांक mthca_map_user_db(काष्ठा mthca_dev *dev, काष्ठा mthca_uar *uar,
		      काष्ठा mthca_user_db_table *db_tab, पूर्णांक index, u64 uaddr);
व्योम mthca_unmap_user_db(काष्ठा mthca_dev *dev, काष्ठा mthca_uar *uar,
			 काष्ठा mthca_user_db_table *db_tab, पूर्णांक index);
काष्ठा mthca_user_db_table *mthca_init_user_db_tab(काष्ठा mthca_dev *dev);
व्योम mthca_cleanup_user_db_tab(काष्ठा mthca_dev *dev, काष्ठा mthca_uar *uar,
			       काष्ठा mthca_user_db_table *db_tab);

पूर्णांक mthca_init_db_tab(काष्ठा mthca_dev *dev);
व्योम mthca_cleanup_db_tab(काष्ठा mthca_dev *dev);
पूर्णांक mthca_alloc_db(काष्ठा mthca_dev *dev, क्रमागत mthca_db_type type,
		   u32 qn, __be32 **db);
व्योम mthca_मुक्त_db(काष्ठा mthca_dev *dev, पूर्णांक type, पूर्णांक db_index);

#पूर्ण_अगर /* MTHCA_MEMFREE_H */
