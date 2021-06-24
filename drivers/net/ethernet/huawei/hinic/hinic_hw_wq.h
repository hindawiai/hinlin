<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Huawei HiNIC PCI Express Linux driver
 * Copyright(c) 2017 Huawei Technologies Co., Ltd
 */

#अगर_अघोषित HINIC_HW_WQ_H
#घोषणा HINIC_HW_WQ_H

#समावेश <linux/types.h>
#समावेश <linux/semaphore.h>
#समावेश <linux/atomic.h>

#समावेश "hinic_hw_if.h"
#समावेश "hinic_hw_wqe.h"

काष्ठा hinic_मुक्त_block अणु
	पूर्णांक     page_idx;
	पूर्णांक     block_idx;
पूर्ण;

काष्ठा hinic_wq अणु
	काष्ठा hinic_hwअगर       *hwअगर;

	पूर्णांक             page_idx;
	पूर्णांक             block_idx;

	u16             wqebb_size;
	u32             wq_page_size;
	u16             q_depth;
	u16             max_wqe_size;
	u16             num_wqebbs_per_page;
	u16		wqebbs_per_page_shअगरt;
	u16		wqebb_size_shअगरt;
	/* The addresses are 64 bit in the HW */
	u64             block_paddr;
	व्योम            **shaकरोw_block_vaddr;
	u64             *block_vaddr;

	पूर्णांक             num_q_pages;
	u8              *shaकरोw_wqe;
	u16             *shaकरोw_idx;

	atomic_t        cons_idx;
	atomic_t        prod_idx;
	atomic_t        delta;
	u16             mask;
पूर्ण;

काष्ठा hinic_wqs अणु
	काष्ठा hinic_hwअगर       *hwअगर;
	पूर्णांक                     num_pages;

	/* The addresses are 64 bit in the HW */
	u64                     *page_paddr;
	u64                     **page_vaddr;
	व्योम                    ***shaकरोw_page_vaddr;

	काष्ठा hinic_मुक्त_block *मुक्त_blocks;
	पूर्णांक                     alloc_blk_pos;
	पूर्णांक                     वापस_blk_pos;
	पूर्णांक                     num_मुक्त_blks;

	/* Lock क्रम getting a मुक्त block from the WQ set */
	काष्ठा semaphore        alloc_blocks_lock;
पूर्ण;

काष्ठा hinic_cmdq_pages अणु
	/* The addresses are 64 bit in the HW */
	u64                     page_paddr;
	u64                     *page_vaddr;
	व्योम                    **shaकरोw_page_vaddr;

	काष्ठा hinic_hwअगर       *hwअगर;
पूर्ण;

पूर्णांक hinic_wqs_cmdq_alloc(काष्ठा hinic_cmdq_pages *cmdq_pages,
			 काष्ठा hinic_wq *wq, काष्ठा hinic_hwअगर *hwअगर,
			 पूर्णांक cmdq_blocks, u16 wqebb_size, u32 wq_page_size,
			 u16 q_depth, u16 max_wqe_size);

व्योम hinic_wqs_cmdq_मुक्त(काष्ठा hinic_cmdq_pages *cmdq_pages,
			 काष्ठा hinic_wq *wq, पूर्णांक cmdq_blocks);

पूर्णांक hinic_wqs_alloc(काष्ठा hinic_wqs *wqs, पूर्णांक num_wqs,
		    काष्ठा hinic_hwअगर *hwअगर);

व्योम hinic_wqs_मुक्त(काष्ठा hinic_wqs *wqs);

पूर्णांक hinic_wq_allocate(काष्ठा hinic_wqs *wqs, काष्ठा hinic_wq *wq,
		      u16 wqebb_size, u32 wq_page_size, u16 q_depth,
		      u16 max_wqe_size);

व्योम hinic_wq_मुक्त(काष्ठा hinic_wqs *wqs, काष्ठा hinic_wq *wq);

काष्ठा hinic_hw_wqe *hinic_get_wqe(काष्ठा hinic_wq *wq, अचिन्हित पूर्णांक wqe_size,
				   u16 *prod_idx);

व्योम hinic_वापस_wqe(काष्ठा hinic_wq *wq, अचिन्हित पूर्णांक wqe_size);

व्योम hinic_put_wqe(काष्ठा hinic_wq *wq, अचिन्हित पूर्णांक wqe_size);

काष्ठा hinic_hw_wqe *hinic_पढ़ो_wqe(काष्ठा hinic_wq *wq, अचिन्हित पूर्णांक wqe_size,
				    u16 *cons_idx);

काष्ठा hinic_hw_wqe *hinic_पढ़ो_wqe_direct(काष्ठा hinic_wq *wq, u16 cons_idx);

व्योम hinic_ग_लिखो_wqe(काष्ठा hinic_wq *wq, काष्ठा hinic_hw_wqe *wqe,
		     अचिन्हित पूर्णांक wqe_size);

#पूर्ण_अगर
