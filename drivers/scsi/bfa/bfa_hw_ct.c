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

BFA_TRC_खाता(HAL, IOCFC_CT);

/*
 * Dummy पूर्णांकerrupt handler क्रम handling spurious पूर्णांकerrupt during chip-reinit.
 */
अटल व्योम
bfa_hwct_msix_dummy(काष्ठा bfa_s *bfa, पूर्णांक vec)
अणु
पूर्ण

व्योम
bfa_hwct_reginit(काष्ठा bfa_s *bfa)
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

व्योम
bfa_hwct2_reginit(काष्ठा bfa_s *bfa)
अणु
	काष्ठा bfa_iocfc_regs_s *bfa_regs = &bfa->iocfc.bfa_regs;
	व्योम __iomem	*kva = bfa_ioc_bar0(&bfa->ioc);

	bfa_regs->पूर्णांकr_status = (kva + CT2_HOSTFN_INT_STATUS);
	bfa_regs->पूर्णांकr_mask   = (kva + CT2_HOSTFN_INTR_MASK);
पूर्ण

व्योम
bfa_hwct_reqq_ack(काष्ठा bfa_s *bfa, पूर्णांक reqq)
अणु
	u32	r32;

	r32 = पढ़ोl(bfa->iocfc.bfa_regs.cpe_q_ctrl[reqq]);
	ग_लिखोl(r32, bfa->iocfc.bfa_regs.cpe_q_ctrl[reqq]);
पूर्ण

/*
 * Actions to respond RME Interrupt क्रम Catapult ASIC:
 * - Write 1 to Interrupt Status रेजिस्टर (INTx only - करोne in bfa_पूर्णांकx())
 * - Acknowledge by writing to RME Queue Control रेजिस्टर
 * - Update CI
 */
व्योम
bfa_hwct_rspq_ack(काष्ठा bfa_s *bfa, पूर्णांक rspq, u32 ci)
अणु
	u32	r32;

	r32 = पढ़ोl(bfa->iocfc.bfa_regs.rme_q_ctrl[rspq]);
	ग_लिखोl(r32, bfa->iocfc.bfa_regs.rme_q_ctrl[rspq]);

	bfa_rspq_ci(bfa, rspq) = ci;
	ग_लिखोl(ci, bfa->iocfc.bfa_regs.rme_q_ci[rspq]);
पूर्ण

/*
 * Actions to respond RME Interrupt क्रम Catapult2 ASIC:
 * - Write 1 to Interrupt Status रेजिस्टर (INTx only - करोne in bfa_पूर्णांकx())
 * - Update CI
 */
व्योम
bfa_hwct2_rspq_ack(काष्ठा bfa_s *bfa, पूर्णांक rspq, u32 ci)
अणु
	bfa_rspq_ci(bfa, rspq) = ci;
	ग_लिखोl(ci, bfa->iocfc.bfa_regs.rme_q_ci[rspq]);
पूर्ण

व्योम
bfa_hwct_msix_getvecs(काष्ठा bfa_s *bfa, u32 *msix_vecs_bmap,
		 u32 *num_vecs, u32 *max_vec_bit)
अणु
	*msix_vecs_bmap = (1 << BFI_MSIX_CT_MAX) - 1;
	*max_vec_bit = (1 << (BFI_MSIX_CT_MAX - 1));
	*num_vecs = BFI_MSIX_CT_MAX;
पूर्ण

/*
 * Setup MSI-X vector क्रम catapult
 */
व्योम
bfa_hwct_msix_init(काष्ठा bfa_s *bfa, पूर्णांक nvecs)
अणु
	WARN_ON((nvecs != 1) && (nvecs != BFI_MSIX_CT_MAX));
	bfa_trc(bfa, nvecs);

	bfa->msix.nvecs = nvecs;
	bfa_hwct_msix_uninstall(bfa);
पूर्ण

व्योम
bfa_hwct_msix_ctrl_install(काष्ठा bfa_s *bfa)
अणु
	अगर (bfa->msix.nvecs == 0)
		वापस;

	अगर (bfa->msix.nvecs == 1)
		bfa->msix.handler[BFI_MSIX_LPU_ERR_CT] = bfa_msix_all;
	अन्यथा
		bfa->msix.handler[BFI_MSIX_LPU_ERR_CT] = bfa_msix_lpu_err;
पूर्ण

व्योम
bfa_hwct_msix_queue_install(काष्ठा bfa_s *bfa)
अणु
	पूर्णांक i;

	अगर (bfa->msix.nvecs == 0)
		वापस;

	अगर (bfa->msix.nvecs == 1) अणु
		क्रम (i = BFI_MSIX_CPE_QMIN_CT; i < BFI_MSIX_CT_MAX; i++)
			bfa->msix.handler[i] = bfa_msix_all;
		वापस;
	पूर्ण

	क्रम (i = BFI_MSIX_CPE_QMIN_CT; i <= BFI_MSIX_CPE_QMAX_CT; i++)
		bfa->msix.handler[i] = bfa_msix_reqq;

	क्रम (i = BFI_MSIX_RME_QMIN_CT; i <= BFI_MSIX_RME_QMAX_CT; i++)
		bfa->msix.handler[i] = bfa_msix_rspq;
पूर्ण

व्योम
bfa_hwct_msix_uninstall(काष्ठा bfa_s *bfa)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < BFI_MSIX_CT_MAX; i++)
		bfa->msix.handler[i] = bfa_hwct_msix_dummy;
पूर्ण

/*
 * Enable MSI-X vectors
 */
व्योम
bfa_hwct_isr_mode_set(काष्ठा bfa_s *bfa, bfa_boolean_t msix)
अणु
	bfa_trc(bfa, 0);
	bfa_ioc_isr_mode_set(&bfa->ioc, msix);
पूर्ण

व्योम
bfa_hwct_msix_get_rme_range(काष्ठा bfa_s *bfa, u32 *start, u32 *end)
अणु
	*start = BFI_MSIX_RME_QMIN_CT;
	*end = BFI_MSIX_RME_QMAX_CT;
पूर्ण
