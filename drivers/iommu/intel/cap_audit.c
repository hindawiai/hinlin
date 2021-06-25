<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * cap_audit.c - audit iommu capabilities क्रम boot समय and hot plug
 *
 * Copyright (C) 2021 Intel Corporation
 *
 * Author: Kyung Min Park <kyung.min.park@पूर्णांकel.com>
 *         Lu Baolu <baolu.lu@linux.पूर्णांकel.com>
 */

#घोषणा pr_fmt(fmt)	"DMAR: " fmt

#समावेश <linux/पूर्णांकel-iommu.h>
#समावेश "cap_audit.h"

अटल u64 पूर्णांकel_iommu_cap_sanity;
अटल u64 पूर्णांकel_iommu_ecap_sanity;

अटल अंतरभूत व्योम check_irq_capabilities(काष्ठा पूर्णांकel_iommu *a,
					  काष्ठा पूर्णांकel_iommu *b)
अणु
	CHECK_FEATURE_MISMATCH(a, b, cap, pi_support, CAP_PI_MASK);
	CHECK_FEATURE_MISMATCH(a, b, ecap, eim_support, ECAP_EIM_MASK);
पूर्ण

अटल अंतरभूत व्योम check_dmar_capabilities(काष्ठा पूर्णांकel_iommu *a,
					   काष्ठा पूर्णांकel_iommu *b)
अणु
	MINIMAL_FEATURE_IOMMU(b, cap, CAP_MAMV_MASK);
	MINIMAL_FEATURE_IOMMU(b, cap, CAP_NFR_MASK);
	MINIMAL_FEATURE_IOMMU(b, cap, CAP_SLLPS_MASK);
	MINIMAL_FEATURE_IOMMU(b, cap, CAP_FRO_MASK);
	MINIMAL_FEATURE_IOMMU(b, cap, CAP_MGAW_MASK);
	MINIMAL_FEATURE_IOMMU(b, cap, CAP_SAGAW_MASK);
	MINIMAL_FEATURE_IOMMU(b, cap, CAP_NDOMS_MASK);
	MINIMAL_FEATURE_IOMMU(b, ecap, ECAP_PSS_MASK);
	MINIMAL_FEATURE_IOMMU(b, ecap, ECAP_MHMV_MASK);
	MINIMAL_FEATURE_IOMMU(b, ecap, ECAP_IRO_MASK);

	CHECK_FEATURE_MISMATCH(a, b, cap, 5lp_support, CAP_FL5LP_MASK);
	CHECK_FEATURE_MISMATCH(a, b, cap, fl1gp_support, CAP_FL1GP_MASK);
	CHECK_FEATURE_MISMATCH(a, b, cap, पढ़ो_drain, CAP_RD_MASK);
	CHECK_FEATURE_MISMATCH(a, b, cap, ग_लिखो_drain, CAP_WD_MASK);
	CHECK_FEATURE_MISMATCH(a, b, cap, pgsel_inv, CAP_PSI_MASK);
	CHECK_FEATURE_MISMATCH(a, b, cap, zlr, CAP_ZLR_MASK);
	CHECK_FEATURE_MISMATCH(a, b, cap, caching_mode, CAP_CM_MASK);
	CHECK_FEATURE_MISMATCH(a, b, cap, phmr, CAP_PHMR_MASK);
	CHECK_FEATURE_MISMATCH(a, b, cap, plmr, CAP_PLMR_MASK);
	CHECK_FEATURE_MISMATCH(a, b, cap, rwbf, CAP_RWBF_MASK);
	CHECK_FEATURE_MISMATCH(a, b, cap, afl, CAP_AFL_MASK);
	CHECK_FEATURE_MISMATCH(a, b, ecap, rps, ECAP_RPS_MASK);
	CHECK_FEATURE_MISMATCH(a, b, ecap, smpwc, ECAP_SMPWC_MASK);
	CHECK_FEATURE_MISMATCH(a, b, ecap, flts, ECAP_FLTS_MASK);
	CHECK_FEATURE_MISMATCH(a, b, ecap, slts, ECAP_SLTS_MASK);
	CHECK_FEATURE_MISMATCH(a, b, ecap, nwfs, ECAP_NWFS_MASK);
	CHECK_FEATURE_MISMATCH(a, b, ecap, slads, ECAP_SLADS_MASK);
	CHECK_FEATURE_MISMATCH(a, b, ecap, vcs, ECAP_VCS_MASK);
	CHECK_FEATURE_MISMATCH(a, b, ecap, smts, ECAP_SMTS_MASK);
	CHECK_FEATURE_MISMATCH(a, b, ecap, pds, ECAP_PDS_MASK);
	CHECK_FEATURE_MISMATCH(a, b, ecap, dit, ECAP_DIT_MASK);
	CHECK_FEATURE_MISMATCH(a, b, ecap, pasid, ECAP_PASID_MASK);
	CHECK_FEATURE_MISMATCH(a, b, ecap, eafs, ECAP_EAFS_MASK);
	CHECK_FEATURE_MISMATCH(a, b, ecap, srs, ECAP_SRS_MASK);
	CHECK_FEATURE_MISMATCH(a, b, ecap, ers, ECAP_ERS_MASK);
	CHECK_FEATURE_MISMATCH(a, b, ecap, prs, ECAP_PRS_MASK);
	CHECK_FEATURE_MISMATCH(a, b, ecap, nest, ECAP_NEST_MASK);
	CHECK_FEATURE_MISMATCH(a, b, ecap, mts, ECAP_MTS_MASK);
	CHECK_FEATURE_MISMATCH(a, b, ecap, sc_support, ECAP_SC_MASK);
	CHECK_FEATURE_MISMATCH(a, b, ecap, pass_through, ECAP_PT_MASK);
	CHECK_FEATURE_MISMATCH(a, b, ecap, dev_iotlb_support, ECAP_DT_MASK);
	CHECK_FEATURE_MISMATCH(a, b, ecap, qis, ECAP_QI_MASK);
	CHECK_FEATURE_MISMATCH(a, b, ecap, coherent, ECAP_C_MASK);
पूर्ण

अटल पूर्णांक cap_audit_hotplug(काष्ठा पूर्णांकel_iommu *iommu, क्रमागत cap_audit_type type)
अणु
	bool mismatch = false;
	u64 old_cap = पूर्णांकel_iommu_cap_sanity;
	u64 old_ecap = पूर्णांकel_iommu_ecap_sanity;

	अगर (type == CAP_AUDIT_HOTPLUG_IRQR) अणु
		CHECK_FEATURE_MISMATCH_HOTPLUG(iommu, cap, pi_support, CAP_PI_MASK);
		CHECK_FEATURE_MISMATCH_HOTPLUG(iommu, ecap, eim_support, ECAP_EIM_MASK);
		जाओ out;
	पूर्ण

	CHECK_FEATURE_MISMATCH_HOTPLUG(iommu, cap, 5lp_support, CAP_FL5LP_MASK);
	CHECK_FEATURE_MISMATCH_HOTPLUG(iommu, cap, fl1gp_support, CAP_FL1GP_MASK);
	CHECK_FEATURE_MISMATCH_HOTPLUG(iommu, cap, पढ़ो_drain, CAP_RD_MASK);
	CHECK_FEATURE_MISMATCH_HOTPLUG(iommu, cap, ग_लिखो_drain, CAP_WD_MASK);
	CHECK_FEATURE_MISMATCH_HOTPLUG(iommu, cap, pgsel_inv, CAP_PSI_MASK);
	CHECK_FEATURE_MISMATCH_HOTPLUG(iommu, cap, zlr, CAP_ZLR_MASK);
	CHECK_FEATURE_MISMATCH_HOTPLUG(iommu, cap, caching_mode, CAP_CM_MASK);
	CHECK_FEATURE_MISMATCH_HOTPLUG(iommu, cap, phmr, CAP_PHMR_MASK);
	CHECK_FEATURE_MISMATCH_HOTPLUG(iommu, cap, plmr, CAP_PLMR_MASK);
	CHECK_FEATURE_MISMATCH_HOTPLUG(iommu, cap, rwbf, CAP_RWBF_MASK);
	CHECK_FEATURE_MISMATCH_HOTPLUG(iommu, cap, afl, CAP_AFL_MASK);
	CHECK_FEATURE_MISMATCH_HOTPLUG(iommu, ecap, rps, ECAP_RPS_MASK);
	CHECK_FEATURE_MISMATCH_HOTPLUG(iommu, ecap, smpwc, ECAP_SMPWC_MASK);
	CHECK_FEATURE_MISMATCH_HOTPLUG(iommu, ecap, flts, ECAP_FLTS_MASK);
	CHECK_FEATURE_MISMATCH_HOTPLUG(iommu, ecap, slts, ECAP_SLTS_MASK);
	CHECK_FEATURE_MISMATCH_HOTPLUG(iommu, ecap, nwfs, ECAP_NWFS_MASK);
	CHECK_FEATURE_MISMATCH_HOTPLUG(iommu, ecap, slads, ECAP_SLADS_MASK);
	CHECK_FEATURE_MISMATCH_HOTPLUG(iommu, ecap, vcs, ECAP_VCS_MASK);
	CHECK_FEATURE_MISMATCH_HOTPLUG(iommu, ecap, smts, ECAP_SMTS_MASK);
	CHECK_FEATURE_MISMATCH_HOTPLUG(iommu, ecap, pds, ECAP_PDS_MASK);
	CHECK_FEATURE_MISMATCH_HOTPLUG(iommu, ecap, dit, ECAP_DIT_MASK);
	CHECK_FEATURE_MISMATCH_HOTPLUG(iommu, ecap, pasid, ECAP_PASID_MASK);
	CHECK_FEATURE_MISMATCH_HOTPLUG(iommu, ecap, eafs, ECAP_EAFS_MASK);
	CHECK_FEATURE_MISMATCH_HOTPLUG(iommu, ecap, srs, ECAP_SRS_MASK);
	CHECK_FEATURE_MISMATCH_HOTPLUG(iommu, ecap, ers, ECAP_ERS_MASK);
	CHECK_FEATURE_MISMATCH_HOTPLUG(iommu, ecap, prs, ECAP_PRS_MASK);
	CHECK_FEATURE_MISMATCH_HOTPLUG(iommu, ecap, nest, ECAP_NEST_MASK);
	CHECK_FEATURE_MISMATCH_HOTPLUG(iommu, ecap, mts, ECAP_MTS_MASK);
	CHECK_FEATURE_MISMATCH_HOTPLUG(iommu, ecap, sc_support, ECAP_SC_MASK);
	CHECK_FEATURE_MISMATCH_HOTPLUG(iommu, ecap, pass_through, ECAP_PT_MASK);
	CHECK_FEATURE_MISMATCH_HOTPLUG(iommu, ecap, dev_iotlb_support, ECAP_DT_MASK);
	CHECK_FEATURE_MISMATCH_HOTPLUG(iommu, ecap, qis, ECAP_QI_MASK);
	CHECK_FEATURE_MISMATCH_HOTPLUG(iommu, ecap, coherent, ECAP_C_MASK);

	/* Abort hot plug अगर the hot plug iommu feature is smaller than global */
	MINIMAL_FEATURE_HOTPLUG(iommu, cap, max_amask_val, CAP_MAMV_MASK, mismatch);
	MINIMAL_FEATURE_HOTPLUG(iommu, cap, num_fault_regs, CAP_NFR_MASK, mismatch);
	MINIMAL_FEATURE_HOTPLUG(iommu, cap, super_page_val, CAP_SLLPS_MASK, mismatch);
	MINIMAL_FEATURE_HOTPLUG(iommu, cap, fault_reg_offset, CAP_FRO_MASK, mismatch);
	MINIMAL_FEATURE_HOTPLUG(iommu, cap, mgaw, CAP_MGAW_MASK, mismatch);
	MINIMAL_FEATURE_HOTPLUG(iommu, cap, sagaw, CAP_SAGAW_MASK, mismatch);
	MINIMAL_FEATURE_HOTPLUG(iommu, cap, nकरोms, CAP_NDOMS_MASK, mismatch);
	MINIMAL_FEATURE_HOTPLUG(iommu, ecap, pss, ECAP_PSS_MASK, mismatch);
	MINIMAL_FEATURE_HOTPLUG(iommu, ecap, max_handle_mask, ECAP_MHMV_MASK, mismatch);
	MINIMAL_FEATURE_HOTPLUG(iommu, ecap, iotlb_offset, ECAP_IRO_MASK, mismatch);

out:
	अगर (mismatch) अणु
		पूर्णांकel_iommu_cap_sanity = old_cap;
		पूर्णांकel_iommu_ecap_sanity = old_ecap;
		वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cap_audit_अटल(काष्ठा पूर्णांकel_iommu *iommu, क्रमागत cap_audit_type type)
अणु
	काष्ठा dmar_drhd_unit *d;
	काष्ठा पूर्णांकel_iommu *i;

	rcu_पढ़ो_lock();
	अगर (list_empty(&dmar_drhd_units))
		जाओ out;

	क्रम_each_active_iommu(i, d) अणु
		अगर (!iommu) अणु
			पूर्णांकel_iommu_ecap_sanity = i->ecap;
			पूर्णांकel_iommu_cap_sanity = i->cap;
			iommu = i;
			जारी;
		पूर्ण

		अगर (type == CAP_AUDIT_STATIC_DMAR)
			check_dmar_capabilities(iommu, i);
		अन्यथा
			check_irq_capabilities(iommu, i);
	पूर्ण

out:
	rcu_पढ़ो_unlock();
	वापस 0;
पूर्ण

पूर्णांक पूर्णांकel_cap_audit(क्रमागत cap_audit_type type, काष्ठा पूर्णांकel_iommu *iommu)
अणु
	चयन (type) अणु
	हाल CAP_AUDIT_STATIC_DMAR:
	हाल CAP_AUDIT_STATIC_IRQR:
		वापस cap_audit_अटल(iommu, type);
	हाल CAP_AUDIT_HOTPLUG_DMAR:
	हाल CAP_AUDIT_HOTPLUG_IRQR:
		वापस cap_audit_hotplug(iommu, type);
	शेष:
		अवरोध;
	पूर्ण

	वापस -EFAULT;
पूर्ण

bool पूर्णांकel_cap_smts_sanity(व्योम)
अणु
	वापस ecap_smts(पूर्णांकel_iommu_ecap_sanity);
पूर्ण

bool पूर्णांकel_cap_pasid_sanity(व्योम)
अणु
	वापस ecap_pasid(पूर्णांकel_iommu_ecap_sanity);
पूर्ण

bool पूर्णांकel_cap_nest_sanity(व्योम)
अणु
	वापस ecap_nest(पूर्णांकel_iommu_ecap_sanity);
पूर्ण

bool पूर्णांकel_cap_flts_sanity(व्योम)
अणु
	वापस ecap_flts(पूर्णांकel_iommu_ecap_sanity);
पूर्ण
