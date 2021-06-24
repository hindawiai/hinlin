<शैली गुरु>
/*
 * Copyright (c) 2016 Oracle.  All rights reserved.
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
#अगर_अघोषित _RDS_IB_MR_H
#घोषणा _RDS_IB_MR_H

#समावेश <linux/kernel.h>

#समावेश "rds.h"
#समावेश "ib.h"

#घोषणा RDS_MR_1M_POOL_SIZE		(8192 / 2)
#घोषणा RDS_MR_1M_MSG_SIZE		256
#घोषणा RDS_MR_8K_MSG_SIZE		2
#घोषणा RDS_MR_8K_SCALE			(256 / (RDS_MR_8K_MSG_SIZE + 1))
#घोषणा RDS_MR_8K_POOL_SIZE		(RDS_MR_8K_SCALE * (8192 / 2))

क्रमागत rds_ib_fr_state अणु
	FRMR_IS_FREE,	/* mr invalidated & पढ़ोy क्रम use */
	FRMR_IS_INUSE,	/* mr is in use or used & can be invalidated */
	FRMR_IS_STALE,	/* Stale MR and needs to be dropped  */
पूर्ण;

काष्ठा rds_ib_frmr अणु
	काष्ठा ib_mr		*mr;
	क्रमागत rds_ib_fr_state	fr_state;
	bool			fr_inv;
	रुको_queue_head_t	fr_inv_करोne;
	bool			fr_reg;
	रुको_queue_head_t	fr_reg_करोne;
	काष्ठा ib_send_wr	fr_wr;
	अचिन्हित पूर्णांक		dma_npages;
	अचिन्हित पूर्णांक		sg_byte_len;
पूर्ण;

/* This is stored as mr->r_trans_निजी. */
काष्ठा rds_ib_mr अणु
	काष्ठा delayed_work		work;
	काष्ठा rds_ib_device		*device;
	काष्ठा rds_ib_mr_pool		*pool;
	काष्ठा rds_ib_connection	*ic;

	काष्ठा llist_node		llnode;

	/* unmap_list is क्रम मुक्तing */
	काष्ठा list_head		unmap_list;
	अचिन्हित पूर्णांक			remap_count;

	काष्ठा scatterlist		*sg;
	अचिन्हित पूर्णांक			sg_len;
	पूर्णांक				sg_dma_len;

	u8				odp:1;
	जोड़ अणु
		काष्ठा rds_ib_frmr	frmr;
		काष्ठा ib_mr		*mr;
	पूर्ण u;
पूर्ण;

/* Our own little MR pool */
काष्ठा rds_ib_mr_pool अणु
	अचिन्हित पूर्णांक            pool_type;
	काष्ठा mutex		flush_lock;	/* serialize fmr invalidate */
	काष्ठा delayed_work	flush_worker;	/* flush worker */

	atomic_t		item_count;	/* total # of MRs */
	atomic_t		dirty_count;	/* # dirty of MRs */

	काष्ठा llist_head	drop_list;	/* MRs not reached max_maps */
	काष्ठा llist_head	मुक्त_list;	/* unused MRs */
	काष्ठा llist_head	clean_list;	/* unused & unmapped MRs */
	रुको_queue_head_t	flush_रुको;
	spinlock_t		clean_lock;	/* "clean_list" concurrency */

	atomic_t		मुक्त_pinned;	/* memory pinned by मुक्त MRs */
	अचिन्हित दीर्घ		max_items;
	अचिन्हित दीर्घ		max_items_soft;
	अचिन्हित दीर्घ		max_मुक्त_pinned;
	अचिन्हित पूर्णांक		max_pages;
पूर्ण;

बाह्य काष्ठा workqueue_काष्ठा *rds_ib_mr_wq;
बाह्य bool prefer_frmr;

काष्ठा rds_ib_mr_pool *rds_ib_create_mr_pool(काष्ठा rds_ib_device *rds_dev,
					     पूर्णांक npages);
व्योम rds_ib_get_mr_info(काष्ठा rds_ib_device *rds_ibdev,
			काष्ठा rds_info_rdma_connection *iinfo);
व्योम rds6_ib_get_mr_info(काष्ठा rds_ib_device *rds_ibdev,
			 काष्ठा rds6_info_rdma_connection *iinfo6);
व्योम rds_ib_destroy_mr_pool(काष्ठा rds_ib_mr_pool *);
व्योम *rds_ib_get_mr(काष्ठा scatterlist *sg, अचिन्हित दीर्घ nents,
		    काष्ठा rds_sock *rs, u32 *key_ret,
		    काष्ठा rds_connection *conn, u64 start, u64 length,
		    पूर्णांक need_odp);
व्योम rds_ib_sync_mr(व्योम *trans_निजी, पूर्णांक dir);
व्योम rds_ib_मुक्त_mr(व्योम *trans_निजी, पूर्णांक invalidate);
व्योम rds_ib_flush_mrs(व्योम);
पूर्णांक rds_ib_mr_init(व्योम);
व्योम rds_ib_mr_निकास(व्योम);
u32 rds_ib_get_lkey(व्योम *trans_निजी);

व्योम __rds_ib_tearकरोwn_mr(काष्ठा rds_ib_mr *);
व्योम rds_ib_tearकरोwn_mr(काष्ठा rds_ib_mr *);
काष्ठा rds_ib_mr *rds_ib_reuse_mr(काष्ठा rds_ib_mr_pool *);
पूर्णांक rds_ib_flush_mr_pool(काष्ठा rds_ib_mr_pool *, पूर्णांक, काष्ठा rds_ib_mr **);
काष्ठा rds_ib_mr *rds_ib_try_reuse_ibmr(काष्ठा rds_ib_mr_pool *);
काष्ठा rds_ib_mr *rds_ib_reg_frmr(काष्ठा rds_ib_device *rds_ibdev,
				  काष्ठा rds_ib_connection *ic,
				  काष्ठा scatterlist *sg,
				  अचिन्हित दीर्घ nents, u32 *key);
व्योम rds_ib_unreg_frmr(काष्ठा list_head *list, अचिन्हित पूर्णांक *nमुक्तd,
		       अचिन्हित दीर्घ *unpinned, अचिन्हित पूर्णांक goal);
व्योम rds_ib_मुक्त_frmr_list(काष्ठा rds_ib_mr *);
#पूर्ण_अगर
