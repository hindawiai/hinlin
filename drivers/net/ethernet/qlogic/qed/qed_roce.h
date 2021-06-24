<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause) */
/* QLogic qed NIC Driver
 * Copyright (c) 2015-2017  QLogic Corporation
 * Copyright (c) 2019-2020 Marvell International Ltd.
 */

#अगर_अघोषित _QED_ROCE_H
#घोषणा _QED_ROCE_H
#समावेश <linux/types.h>
#समावेश <linux/slab.h>

#अगर IS_ENABLED(CONFIG_QED_RDMA)
व्योम qed_roce_dpm_dcbx(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt);
#अन्यथा
अटल अंतरभूत व्योम qed_roce_dpm_dcbx(काष्ठा qed_hwfn *p_hwfn,
				     काष्ठा qed_ptt *p_ptt) अणुपूर्ण
#पूर्ण_अगर

पूर्णांक qed_roce_setup(काष्ठा qed_hwfn *p_hwfn);
व्योम qed_roce_stop(काष्ठा qed_hwfn *p_hwfn);
पूर्णांक qed_roce_init_hw(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt);
पूर्णांक qed_roce_alloc_cid(काष्ठा qed_hwfn *p_hwfn, u16 *cid);
पूर्णांक qed_roce_destroy_qp(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_rdma_qp *qp);

पूर्णांक qed_roce_query_qp(काष्ठा qed_hwfn *p_hwfn,
		      काष्ठा qed_rdma_qp *qp,
		      काष्ठा qed_rdma_query_qp_out_params *out_params);

पूर्णांक qed_roce_modअगरy_qp(काष्ठा qed_hwfn *p_hwfn,
		       काष्ठा qed_rdma_qp *qp,
		       क्रमागत qed_roce_qp_state prev_state,
		       काष्ठा qed_rdma_modअगरy_qp_in_params *params);

#पूर्ण_अगर
