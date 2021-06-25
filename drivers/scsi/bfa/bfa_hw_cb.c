<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2005-2014 Brocade Communications Systems, Inc.
 * Copyright (c) 2014- QLogic Corporation.
 * All rights reserved
 * www.qlogic.com
 *
 * Linux driver क्रम QLogic BR-series Fibre Channel Host Bus Adapter.
 */

#समावेश "bfad_drv.h"
#समावेश "bfa_modules.h"
#समावेश "bfi_reg.h"

व्योम
bfa_hwcb_reginit(काष्ठा bfa_s *bfa)
अणु
	काष्ठा bfa_iocfc_regs_s	*bfa_regs = &bfa->iocfc.bfa_regs;
	व्योम __iomem *kva = bfa_ioc_bar0(&bfa->ioc);
	पूर्णांक	fn = bfa_ioc_pcअगरn(&bfa->ioc);

	अगर (fn == 0) अणु
		bfa_regs->पूर्णांकr_status = (kva + HOSTFN0_INT_STATUS);
		bfa_regs->पूर्णांकr_mask   = (kva + HOSTFN0_INT_MSK);
	पूर्ण अन्यथा अणु
		bfa_regs->पूर्णांकr_status = (kva + HOSTFN1_INT_STATUS);
		bfa_regs->पूर्णांकr_mask   = (kva + HOSTFN1_INT_MSK);
	पूर्ण
पूर्ण

अटल व्योम
bfa_hwcb_reqq_ack_msix(काष्ठा bfa_s *bfa, पूर्णांक reqq)
अणु
	ग_लिखोl(__HFN_INT_CPE_Q0 << CPE_Q_NUM(bfa_ioc_pcअगरn(&bfa->ioc), reqq),
			bfa->iocfc.bfa_regs.पूर्णांकr_status);
पूर्ण

/*
 * Actions to respond RME Interrupt क्रम Crossbow ASIC:
 * - Write 1 to Interrupt Status रेजिस्टर
 *              INTX - करोne in bfa_पूर्णांकx()
 *              MSIX - करोne in bfa_hwcb_rspq_ack_msix()
 * - Update CI (only अगर new CI)
 */
अटल व्योम
bfa_hwcb_rspq_ack_msix(काष्ठा bfa_s *bfa, पूर्णांक rspq, u32 ci)
अणु
	ग_लिखोl(__HFN_INT_RME_Q0 << RME_Q_NUM(bfa_ioc_pcअगरn(&bfa->ioc), rspq),
		bfa->iocfc.bfa_regs.पूर्णांकr_status);

	अगर (bfa_rspq_ci(bfa, rspq) == ci)
		वापस;

	bfa_rspq_ci(bfa, rspq) = ci;
	ग_लिखोl(ci, bfa->iocfc.bfa_regs.rme_q_ci[rspq]);
पूर्ण

व्योम
bfa_hwcb_rspq_ack(काष्ठा bfa_s *bfa, पूर्णांक rspq, u32 ci)
अणु
	अगर (bfa_rspq_ci(bfa, rspq) == ci)
		वापस;

	bfa_rspq_ci(bfa, rspq) = ci;
	ग_लिखोl(ci, bfa->iocfc.bfa_regs.rme_q_ci[rspq]);
पूर्ण

व्योम
bfa_hwcb_msix_getvecs(काष्ठा bfa_s *bfa, u32 *msix_vecs_bmap,
		 u32 *num_vecs, u32 *max_vec_bit)
अणु
#घोषणा __HFN_NUMINTS	13
	अगर (bfa_ioc_pcअगरn(&bfa->ioc) == 0) अणु
		*msix_vecs_bmap = (__HFN_INT_CPE_Q0 | __HFN_INT_CPE_Q1 |
				   __HFN_INT_CPE_Q2 | __HFN_INT_CPE_Q3 |
				   __HFN_INT_RME_Q0 | __HFN_INT_RME_Q1 |
				   __HFN_INT_RME_Q2 | __HFN_INT_RME_Q3 |
				   __HFN_INT_MBOX_LPU0);
		*max_vec_bit = __HFN_INT_MBOX_LPU0;
	पूर्ण अन्यथा अणु
		*msix_vecs_bmap = (__HFN_INT_CPE_Q4 | __HFN_INT_CPE_Q5 |
				   __HFN_INT_CPE_Q6 | __HFN_INT_CPE_Q7 |
				   __HFN_INT_RME_Q4 | __HFN_INT_RME_Q5 |
				   __HFN_INT_RME_Q6 | __HFN_INT_RME_Q7 |
				   __HFN_INT_MBOX_LPU1);
		*max_vec_bit = __HFN_INT_MBOX_LPU1;
	पूर्ण

	*msix_vecs_bmap |= (__HFN_INT_ERR_EMC | __HFN_INT_ERR_LPU0 |
			    __HFN_INT_ERR_LPU1 | __HFN_INT_ERR_PSS);
	*num_vecs = __HFN_NUMINTS;
पूर्ण

/*
 * Dummy पूर्णांकerrupt handler क्रम handling spurious पूर्णांकerrupts.
 */
अटल व्योम
bfa_hwcb_msix_dummy(काष्ठा bfa_s *bfa, पूर्णांक vec)
अणु
पूर्ण

/*
 * No special setup required क्रम crossbow -- vector assignments are implicit.
 */
व्योम
bfa_hwcb_msix_init(काष्ठा bfa_s *bfa, पूर्णांक nvecs)
अणु
	WARN_ON((nvecs != 1) && (nvecs != __HFN_NUMINTS));

	bfa->msix.nvecs = nvecs;
	bfa_hwcb_msix_uninstall(bfa);
पूर्ण

व्योम
bfa_hwcb_msix_ctrl_install(काष्ठा bfa_s *bfa)
अणु
	पूर्णांक i;

	अगर (bfa->msix.nvecs == 0)
		वापस;

	अगर (bfa->msix.nvecs == 1) अणु
		क्रम (i = BFI_MSIX_CPE_QMIN_CB; i < BFI_MSIX_CB_MAX; i++)
			bfa->msix.handler[i] = bfa_msix_all;
		वापस;
	पूर्ण

	क्रम (i = BFI_MSIX_RME_QMAX_CB+1; i < BFI_MSIX_CB_MAX; i++)
		bfa->msix.handler[i] = bfa_msix_lpu_err;
पूर्ण

व्योम
bfa_hwcb_msix_queue_install(काष्ठा bfa_s *bfa)
अणु
	पूर्णांक i;

	अगर (bfa->msix.nvecs == 0)
		वापस;

	अगर (bfa->msix.nvecs == 1) अणु
		क्रम (i = BFI_MSIX_CPE_QMIN_CB; i <= BFI_MSIX_RME_QMAX_CB; i++)
			bfa->msix.handler[i] = bfa_msix_all;
		वापस;
	पूर्ण

	क्रम (i = BFI_MSIX_CPE_QMIN_CB; i <= BFI_MSIX_CPE_QMAX_CB; i++)
		bfa->msix.handler[i] = bfa_msix_reqq;

	क्रम (i = BFI_MSIX_RME_QMIN_CB; i <= BFI_MSIX_RME_QMAX_CB; i++)
		bfa->msix.handler[i] = bfa_msix_rspq;
पूर्ण

व्योम
bfa_hwcb_msix_uninstall(काष्ठा bfa_s *bfa)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < BFI_MSIX_CB_MAX; i++)
		bfa->msix.handler[i] = bfa_hwcb_msix_dummy;
पूर्ण

/*
 * No special enable/disable -- vector assignments are implicit.
 */
व्योम
bfa_hwcb_isr_mode_set(काष्ठा bfa_s *bfa, bfa_boolean_t msix)
अणु
	अगर (msix) अणु
		bfa->iocfc.hwअगर.hw_reqq_ack = bfa_hwcb_reqq_ack_msix;
		bfa->iocfc.hwअगर.hw_rspq_ack = bfa_hwcb_rspq_ack_msix;
	पूर्ण अन्यथा अणु
		bfa->iocfc.hwअगर.hw_reqq_ack = शून्य;
		bfa->iocfc.hwअगर.hw_rspq_ack = bfa_hwcb_rspq_ack;
	पूर्ण
पूर्ण

व्योम
bfa_hwcb_msix_get_rme_range(काष्ठा bfa_s *bfa, u32 *start, u32 *end)
अणु
	*start = BFI_MSIX_RME_QMIN_CB;
	*end = BFI_MSIX_RME_QMAX_CB;
पूर्ण
