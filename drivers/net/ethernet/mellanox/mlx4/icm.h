<शैली गुरु>
/*
 * Copyright (c) 2005, 2006, 2007, 2008 Mellanox Technologies. All rights reserved.
 * Copyright (c) 2006, 2007 Cisco Systems, Inc.  All rights reserved.
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

#अगर_अघोषित MLX4_ICM_H
#घोषणा MLX4_ICM_H

#समावेश <linux/list.h>
#समावेश <linux/pci.h>
#समावेश <linux/mutex.h>

#घोषणा MLX4_ICM_CHUNK_LEN						\
	((256 - माप(काष्ठा list_head) - 2 * माप(पूर्णांक)) /		\
	 (माप(काष्ठा scatterlist)))

क्रमागत अणु
	MLX4_ICM_PAGE_SHIFT	= 12,
	MLX4_ICM_PAGE_SIZE	= 1 << MLX4_ICM_PAGE_SHIFT,
पूर्ण;

काष्ठा mlx4_icm_buf अणु
	व्योम			*addr;
	माप_प्रकार			size;
	dma_addr_t		dma_addr;
पूर्ण;

काष्ठा mlx4_icm_chunk अणु
	काष्ठा list_head	list;
	पूर्णांक			npages;
	पूर्णांक			nsg;
	bool			coherent;
	जोड़ अणु
		काष्ठा scatterlist	sg[MLX4_ICM_CHUNK_LEN];
		काष्ठा mlx4_icm_buf	buf[MLX4_ICM_CHUNK_LEN];
	पूर्ण;
पूर्ण;

काष्ठा mlx4_icm अणु
	काष्ठा list_head	chunk_list;
	पूर्णांक			refcount;
पूर्ण;

काष्ठा mlx4_icm_iter अणु
	काष्ठा mlx4_icm	       *icm;
	काष्ठा mlx4_icm_chunk  *chunk;
	पूर्णांक			page_idx;
पूर्ण;

काष्ठा mlx4_dev;

काष्ठा mlx4_icm *mlx4_alloc_icm(काष्ठा mlx4_dev *dev, पूर्णांक npages,
				gfp_t gfp_mask, पूर्णांक coherent);
व्योम mlx4_मुक्त_icm(काष्ठा mlx4_dev *dev, काष्ठा mlx4_icm *icm, पूर्णांक coherent);

पूर्णांक mlx4_table_get(काष्ठा mlx4_dev *dev, काष्ठा mlx4_icm_table *table, u32 obj);
व्योम mlx4_table_put(काष्ठा mlx4_dev *dev, काष्ठा mlx4_icm_table *table, u32 obj);
पूर्णांक mlx4_table_get_range(काष्ठा mlx4_dev *dev, काष्ठा mlx4_icm_table *table,
			 u32 start, u32 end);
व्योम mlx4_table_put_range(काष्ठा mlx4_dev *dev, काष्ठा mlx4_icm_table *table,
			  u32 start, u32 end);
पूर्णांक mlx4_init_icm_table(काष्ठा mlx4_dev *dev, काष्ठा mlx4_icm_table *table,
			u64 virt, पूर्णांक obj_size,	u32 nobj, पूर्णांक reserved,
			पूर्णांक use_lowmem, पूर्णांक use_coherent);
व्योम mlx4_cleanup_icm_table(काष्ठा mlx4_dev *dev, काष्ठा mlx4_icm_table *table);
व्योम *mlx4_table_find(काष्ठा mlx4_icm_table *table, u32 obj, dma_addr_t *dma_handle);

अटल अंतरभूत व्योम mlx4_icm_first(काष्ठा mlx4_icm *icm,
				  काष्ठा mlx4_icm_iter *iter)
अणु
	iter->icm      = icm;
	iter->chunk    = list_empty(&icm->chunk_list) ?
		शून्य : list_entry(icm->chunk_list.next,
				  काष्ठा mlx4_icm_chunk, list);
	iter->page_idx = 0;
पूर्ण

अटल अंतरभूत पूर्णांक mlx4_icm_last(काष्ठा mlx4_icm_iter *iter)
अणु
	वापस !iter->chunk;
पूर्ण

अटल अंतरभूत व्योम mlx4_icm_next(काष्ठा mlx4_icm_iter *iter)
अणु
	अगर (++iter->page_idx >= iter->chunk->nsg) अणु
		अगर (iter->chunk->list.next == &iter->icm->chunk_list) अणु
			iter->chunk = शून्य;
			वापस;
		पूर्ण

		iter->chunk = list_entry(iter->chunk->list.next,
					 काष्ठा mlx4_icm_chunk, list);
		iter->page_idx = 0;
	पूर्ण
पूर्ण

अटल अंतरभूत dma_addr_t mlx4_icm_addr(काष्ठा mlx4_icm_iter *iter)
अणु
	अगर (iter->chunk->coherent)
		वापस iter->chunk->buf[iter->page_idx].dma_addr;
	अन्यथा
		वापस sg_dma_address(&iter->chunk->sg[iter->page_idx]);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ mlx4_icm_size(काष्ठा mlx4_icm_iter *iter)
अणु
	अगर (iter->chunk->coherent)
		वापस iter->chunk->buf[iter->page_idx].size;
	अन्यथा
		वापस sg_dma_len(&iter->chunk->sg[iter->page_idx]);
पूर्ण

पूर्णांक mlx4_MAP_ICM_AUX(काष्ठा mlx4_dev *dev, काष्ठा mlx4_icm *icm);
पूर्णांक mlx4_UNMAP_ICM_AUX(काष्ठा mlx4_dev *dev);

#पूर्ण_अगर /* MLX4_ICM_H */
