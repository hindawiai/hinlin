<शैली गुरु>
/*
 * Copyright (c) 2016 Hisilicon Limited.
 * Copyright (c) 2007, 2008 Mellanox Technologies. All rights reserved.
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

#अगर_अघोषित _HNS_ROCE_HEM_H
#घोषणा _HNS_ROCE_HEM_H

#घोषणा HW_SYNC_SLEEP_TIME_INTERVAL	20
#घोषणा HW_SYNC_TIMEOUT_MSECS           (25 * HW_SYNC_SLEEP_TIME_INTERVAL)
#घोषणा BT_CMD_SYNC_SHIFT		31

क्रमागत अणु
	/* MAP HEM(Hardware Entry Memory) */
	HEM_TYPE_QPC = 0,
	HEM_TYPE_MTPT,
	HEM_TYPE_CQC,
	HEM_TYPE_SRQC,
	HEM_TYPE_SCCC,
	HEM_TYPE_QPC_TIMER,
	HEM_TYPE_CQC_TIMER,
	HEM_TYPE_GMV,

	 /* UNMAP HEM */
	HEM_TYPE_MTT,
	HEM_TYPE_CQE,
	HEM_TYPE_SRQWQE,
	HEM_TYPE_IDX,
	HEM_TYPE_IRRL,
	HEM_TYPE_TRRL,
पूर्ण;

#घोषणा HNS_ROCE_HEM_CHUNK_LEN	\
	 ((256 - माप(काष्ठा list_head) - 2 * माप(पूर्णांक)) /	 \
	 (माप(काष्ठा scatterlist) + माप(व्योम *)))

#घोषणा check_whether_bt_num_3(type, hop_num) \
	(type < HEM_TYPE_MTT && hop_num == 2)

#घोषणा check_whether_bt_num_2(type, hop_num) \
	((type < HEM_TYPE_MTT && hop_num == 1) || \
	(type >= HEM_TYPE_MTT && hop_num == 2))

#घोषणा check_whether_bt_num_1(type, hop_num) \
	((type < HEM_TYPE_MTT && hop_num == HNS_ROCE_HOP_NUM_0) || \
	(type >= HEM_TYPE_MTT && hop_num == 1) || \
	(type >= HEM_TYPE_MTT && hop_num == HNS_ROCE_HOP_NUM_0))

क्रमागत अणु
	 HNS_ROCE_HEM_PAGE_SHIFT = 12,
	 HNS_ROCE_HEM_PAGE_SIZE  = 1 << HNS_ROCE_HEM_PAGE_SHIFT,
पूर्ण;

काष्ठा hns_roce_hem_chunk अणु
	काष्ठा list_head	 list;
	पूर्णांक			 npages;
	पूर्णांक			 nsg;
	काष्ठा scatterlist	 mem[HNS_ROCE_HEM_CHUNK_LEN];
	व्योम			 *buf[HNS_ROCE_HEM_CHUNK_LEN];
पूर्ण;

काष्ठा hns_roce_hem अणु
	काष्ठा list_head	 chunk_list;
	पूर्णांक			 refcount;
पूर्ण;

काष्ठा hns_roce_hem_iter अणु
	काष्ठा hns_roce_hem		 *hem;
	काष्ठा hns_roce_hem_chunk	 *chunk;
	पूर्णांक				 page_idx;
पूर्ण;

काष्ठा hns_roce_hem_mhop अणु
	u32	hop_num;
	u32	buf_chunk_size;
	u32	bt_chunk_size;
	u32	ba_l0_num;
	u32	l0_idx; /* level 0 base address table index */
	u32	l1_idx; /* level 1 base address table index */
	u32	l2_idx; /* level 2 base address table index */
पूर्ण;

व्योम hns_roce_मुक्त_hem(काष्ठा hns_roce_dev *hr_dev, काष्ठा hns_roce_hem *hem);
पूर्णांक hns_roce_table_get(काष्ठा hns_roce_dev *hr_dev,
		       काष्ठा hns_roce_hem_table *table, अचिन्हित दीर्घ obj);
व्योम hns_roce_table_put(काष्ठा hns_roce_dev *hr_dev,
			काष्ठा hns_roce_hem_table *table, अचिन्हित दीर्घ obj);
व्योम *hns_roce_table_find(काष्ठा hns_roce_dev *hr_dev,
			  काष्ठा hns_roce_hem_table *table, अचिन्हित दीर्घ obj,
			  dma_addr_t *dma_handle);
पूर्णांक hns_roce_init_hem_table(काष्ठा hns_roce_dev *hr_dev,
			    काष्ठा hns_roce_hem_table *table, u32 type,
			    अचिन्हित दीर्घ obj_size, अचिन्हित दीर्घ nobj,
			    पूर्णांक use_lowmem);
व्योम hns_roce_cleanup_hem_table(काष्ठा hns_roce_dev *hr_dev,
				काष्ठा hns_roce_hem_table *table);
व्योम hns_roce_cleanup_hem(काष्ठा hns_roce_dev *hr_dev);
पूर्णांक hns_roce_calc_hem_mhop(काष्ठा hns_roce_dev *hr_dev,
			   काष्ठा hns_roce_hem_table *table, अचिन्हित दीर्घ *obj,
			   काष्ठा hns_roce_hem_mhop *mhop);
bool hns_roce_check_whether_mhop(काष्ठा hns_roce_dev *hr_dev, u32 type);

व्योम hns_roce_hem_list_init(काष्ठा hns_roce_hem_list *hem_list);
पूर्णांक hns_roce_hem_list_calc_root_ba(स्थिर काष्ठा hns_roce_buf_region *regions,
				   पूर्णांक region_cnt, पूर्णांक unit);
पूर्णांक hns_roce_hem_list_request(काष्ठा hns_roce_dev *hr_dev,
			      काष्ठा hns_roce_hem_list *hem_list,
			      स्थिर काष्ठा hns_roce_buf_region *regions,
			      पूर्णांक region_cnt, अचिन्हित पूर्णांक bt_pg_shअगरt);
व्योम hns_roce_hem_list_release(काष्ठा hns_roce_dev *hr_dev,
			       काष्ठा hns_roce_hem_list *hem_list);
व्योम *hns_roce_hem_list_find_mtt(काष्ठा hns_roce_dev *hr_dev,
				 काष्ठा hns_roce_hem_list *hem_list,
				 पूर्णांक offset, पूर्णांक *mtt_cnt, u64 *phy_addr);

अटल अंतरभूत व्योम hns_roce_hem_first(काष्ठा hns_roce_hem *hem,
				      काष्ठा hns_roce_hem_iter *iter)
अणु
	iter->hem = hem;
	iter->chunk = list_empty(&hem->chunk_list) ? शून्य :
				 list_entry(hem->chunk_list.next,
					    काष्ठा hns_roce_hem_chunk, list);
	iter->page_idx = 0;
पूर्ण

अटल अंतरभूत पूर्णांक hns_roce_hem_last(काष्ठा hns_roce_hem_iter *iter)
अणु
	वापस !iter->chunk;
पूर्ण

अटल अंतरभूत व्योम hns_roce_hem_next(काष्ठा hns_roce_hem_iter *iter)
अणु
	अगर (++iter->page_idx >= iter->chunk->nsg) अणु
		अगर (iter->chunk->list.next == &iter->hem->chunk_list) अणु
			iter->chunk = शून्य;
			वापस;
		पूर्ण

		iter->chunk = list_entry(iter->chunk->list.next,
					 काष्ठा hns_roce_hem_chunk, list);
		iter->page_idx = 0;
	पूर्ण
पूर्ण

अटल अंतरभूत dma_addr_t hns_roce_hem_addr(काष्ठा hns_roce_hem_iter *iter)
अणु
	वापस sg_dma_address(&iter->chunk->mem[iter->page_idx]);
पूर्ण

#पूर्ण_अगर /* _HNS_ROCE_HEM_H */
