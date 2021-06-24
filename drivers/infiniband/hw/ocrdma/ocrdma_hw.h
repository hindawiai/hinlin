<शैली गुरु>
/* This file is part of the Emulex RoCE Device Driver क्रम
 * RoCE (RDMA over Converged Ethernet) adapters.
 * Copyright (C) 2012-2015 Emulex. All rights reserved.
 * EMULEX and SLI are trademarks of Emulex.
 * www.emulex.com
 *
 * This software is available to you under a choice of one of two licenses.
 * You may choose to be licensed under the terms of the GNU General Public
 * License (GPL) Version 2, available from the file COPYING in the मुख्य
 * directory of this source tree, or the BSD license below:
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 *
 * - Redistributions in binary क्रमm must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in
 *   the करोcumentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Contact Inक्रमmation:
 * linux-drivers@emulex.com
 *
 * Emulex
 * 3333 Susan Street
 * Costa Mesa, CA 92626
 */

#अगर_अघोषित __OCRDMA_HW_H__
#घोषणा __OCRDMA_HW_H__

#समावेश "ocrdma_sli.h"

अटल अंतरभूत व्योम ocrdma_cpu_to_le32(व्योम *dst, u32 len)
अणु
#अगर_घोषित __BIG_ENDIAN
	पूर्णांक i = 0;
	u32 *src_ptr = dst;
	u32 *dst_ptr = dst;
	क्रम (; i < (len / 4); i++)
		*(dst_ptr + i) = cpu_to_le32p(src_ptr + i);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम ocrdma_le32_to_cpu(व्योम *dst, u32 len)
अणु
#अगर_घोषित __BIG_ENDIAN
	पूर्णांक i = 0;
	u32 *src_ptr = dst;
	u32 *dst_ptr = dst;
	क्रम (; i < (len / माप(u32)); i++)
		*(dst_ptr + i) = le32_to_cpu(*(src_ptr + i));
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम ocrdma_copy_cpu_to_le32(व्योम *dst, व्योम *src, u32 len)
अणु
#अगर_घोषित __BIG_ENDIAN
	पूर्णांक i = 0;
	u32 *src_ptr = src;
	u32 *dst_ptr = dst;
	क्रम (; i < (len / माप(u32)); i++)
		*(dst_ptr + i) = cpu_to_le32p(src_ptr + i);
#अन्यथा
	स_नकल(dst, src, len);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम ocrdma_copy_le32_to_cpu(व्योम *dst, व्योम *src, u32 len)
अणु
#अगर_घोषित __BIG_ENDIAN
	पूर्णांक i = 0;
	u32 *src_ptr = src;
	u32 *dst_ptr = dst;
	क्रम (; i < len / माप(u32); i++)
		*(dst_ptr + i) = le32_to_cpu(*(src_ptr + i));
#अन्यथा
	स_नकल(dst, src, len);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत u64 ocrdma_get_db_addr(काष्ठा ocrdma_dev *dev, u32 pdid)
अणु
	वापस dev->nic_info.unmapped_db + (pdid * dev->nic_info.db_page_size);
पूर्ण

पूर्णांक ocrdma_init_hw(काष्ठा ocrdma_dev *);
व्योम ocrdma_cleanup_hw(काष्ठा ocrdma_dev *);

क्रमागत ib_qp_state get_ibqp_state(क्रमागत ocrdma_qp_state qps);
व्योम ocrdma_ring_cq_db(काष्ठा ocrdma_dev *, u16 cq_id, bool armed,
		       bool solicited, u16 cqe_popped);

/* verbs specअगरic mailbox commands */
पूर्णांक ocrdma_mbx_get_link_speed(काष्ठा ocrdma_dev *dev, u8 *lnk_speed,
			      u8 *lnk_st);
पूर्णांक ocrdma_query_config(काष्ठा ocrdma_dev *,
			काष्ठा ocrdma_mbx_query_config *config);

पूर्णांक ocrdma_mbx_alloc_pd(काष्ठा ocrdma_dev *, काष्ठा ocrdma_pd *);
पूर्णांक ocrdma_mbx_dealloc_pd(काष्ठा ocrdma_dev *, काष्ठा ocrdma_pd *);

पूर्णांक ocrdma_mbx_alloc_lkey(काष्ठा ocrdma_dev *, काष्ठा ocrdma_hw_mr *hwmr,
			  u32 pd_id, पूर्णांक addr_check);
पूर्णांक ocrdma_mbx_dealloc_lkey(काष्ठा ocrdma_dev *, पूर्णांक fmr, u32 lkey);

पूर्णांक ocrdma_reg_mr(काष्ठा ocrdma_dev *, काष्ठा ocrdma_hw_mr *hwmr,
			u32 pd_id, पूर्णांक acc);
पूर्णांक ocrdma_mbx_create_cq(काष्ठा ocrdma_dev *, काष्ठा ocrdma_cq *,
				पूर्णांक entries, पूर्णांक dpp_cq, u16 pd_id);
व्योम ocrdma_mbx_destroy_cq(काष्ठा ocrdma_dev *dev, काष्ठा ocrdma_cq *cq);

पूर्णांक ocrdma_mbx_create_qp(काष्ठा ocrdma_qp *, काष्ठा ib_qp_init_attr *attrs,
			 u8 enable_dpp_cq, u16 dpp_cq_id, u16 *dpp_offset,
			 u16 *dpp_credit_lmt);
पूर्णांक ocrdma_mbx_modअगरy_qp(काष्ठा ocrdma_dev *, काष्ठा ocrdma_qp *,
			 काष्ठा ib_qp_attr *attrs, पूर्णांक attr_mask);
पूर्णांक ocrdma_mbx_query_qp(काष्ठा ocrdma_dev *, काष्ठा ocrdma_qp *,
			काष्ठा ocrdma_qp_params *param);
पूर्णांक ocrdma_mbx_destroy_qp(काष्ठा ocrdma_dev *, काष्ठा ocrdma_qp *);
पूर्णांक ocrdma_mbx_create_srq(काष्ठा ocrdma_dev *, काष्ठा ocrdma_srq *,
			  काष्ठा ib_srq_init_attr *,
			  काष्ठा ocrdma_pd *);
पूर्णांक ocrdma_mbx_modअगरy_srq(काष्ठा ocrdma_srq *, काष्ठा ib_srq_attr *);
पूर्णांक ocrdma_mbx_query_srq(काष्ठा ocrdma_srq *, काष्ठा ib_srq_attr *);
व्योम ocrdma_mbx_destroy_srq(काष्ठा ocrdma_dev *dev, काष्ठा ocrdma_srq *srq);

पूर्णांक ocrdma_alloc_av(काष्ठा ocrdma_dev *dev, काष्ठा ocrdma_ah *ah);
व्योम ocrdma_मुक्त_av(काष्ठा ocrdma_dev *dev, काष्ठा ocrdma_ah *ah);

पूर्णांक ocrdma_qp_state_change(काष्ठा ocrdma_qp *, क्रमागत ib_qp_state new_state,
			    क्रमागत ib_qp_state *old_ib_state);
bool ocrdma_is_qp_in_sq_flushlist(काष्ठा ocrdma_cq *, काष्ठा ocrdma_qp *);
bool ocrdma_is_qp_in_rq_flushlist(काष्ठा ocrdma_cq *, काष्ठा ocrdma_qp *);
व्योम ocrdma_flush_qp(काष्ठा ocrdma_qp *);
पूर्णांक ocrdma_get_irq(काष्ठा ocrdma_dev *dev, काष्ठा ocrdma_eq *eq);

पूर्णांक ocrdma_mbx_rdma_stats(काष्ठा ocrdma_dev *, bool reset);
अक्षर *port_speed_string(काष्ठा ocrdma_dev *dev);
व्योम ocrdma_init_service_level(काष्ठा ocrdma_dev *);
व्योम ocrdma_alloc_pd_pool(काष्ठा ocrdma_dev *dev);
व्योम ocrdma_मुक्त_pd_range(काष्ठा ocrdma_dev *dev);
व्योम ocrdma_update_link_state(काष्ठा ocrdma_dev *dev, u8 lstate);

#पूर्ण_अगर				/* __OCRDMA_HW_H__ */
