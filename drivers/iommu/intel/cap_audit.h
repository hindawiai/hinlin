<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * cap_audit.h - audit iommu capabilities header
 *
 * Copyright (C) 2021 Intel Corporation
 *
 * Author: Kyung Min Park <kyung.min.park@पूर्णांकel.com>
 */

/*
 * Capability Register Mask
 */
#घोषणा CAP_FL5LP_MASK		BIT_ULL(60)
#घोषणा CAP_PI_MASK		BIT_ULL(59)
#घोषणा CAP_FL1GP_MASK		BIT_ULL(56)
#घोषणा CAP_RD_MASK		BIT_ULL(55)
#घोषणा CAP_WD_MASK		BIT_ULL(54)
#घोषणा CAP_MAMV_MASK		GENMASK_ULL(53, 48)
#घोषणा CAP_NFR_MASK		GENMASK_ULL(47, 40)
#घोषणा CAP_PSI_MASK		BIT_ULL(39)
#घोषणा CAP_SLLPS_MASK		GENMASK_ULL(37, 34)
#घोषणा CAP_FRO_MASK		GENMASK_ULL(33, 24)
#घोषणा CAP_ZLR_MASK		BIT_ULL(22)
#घोषणा CAP_MGAW_MASK		GENMASK_ULL(21, 16)
#घोषणा CAP_SAGAW_MASK		GENMASK_ULL(12, 8)
#घोषणा CAP_CM_MASK		BIT_ULL(7)
#घोषणा CAP_PHMR_MASK		BIT_ULL(6)
#घोषणा CAP_PLMR_MASK		BIT_ULL(5)
#घोषणा CAP_RWBF_MASK		BIT_ULL(4)
#घोषणा CAP_AFL_MASK		BIT_ULL(3)
#घोषणा CAP_NDOMS_MASK		GENMASK_ULL(2, 0)

/*
 * Extended Capability Register Mask
 */
#घोषणा ECAP_RPS_MASK		BIT_ULL(49)
#घोषणा ECAP_SMPWC_MASK		BIT_ULL(48)
#घोषणा ECAP_FLTS_MASK		BIT_ULL(47)
#घोषणा ECAP_SLTS_MASK		BIT_ULL(46)
#घोषणा ECAP_SLADS_MASK		BIT_ULL(45)
#घोषणा ECAP_VCS_MASK		BIT_ULL(44)
#घोषणा ECAP_SMTS_MASK		BIT_ULL(43)
#घोषणा ECAP_PDS_MASK		BIT_ULL(42)
#घोषणा ECAP_DIT_MASK		BIT_ULL(41)
#घोषणा ECAP_PASID_MASK		BIT_ULL(40)
#घोषणा ECAP_PSS_MASK		GENMASK_ULL(39, 35)
#घोषणा ECAP_EAFS_MASK		BIT_ULL(34)
#घोषणा ECAP_NWFS_MASK		BIT_ULL(33)
#घोषणा ECAP_SRS_MASK		BIT_ULL(31)
#घोषणा ECAP_ERS_MASK		BIT_ULL(30)
#घोषणा ECAP_PRS_MASK		BIT_ULL(29)
#घोषणा ECAP_NEST_MASK		BIT_ULL(26)
#घोषणा ECAP_MTS_MASK		BIT_ULL(25)
#घोषणा ECAP_MHMV_MASK		GENMASK_ULL(23, 20)
#घोषणा ECAP_IRO_MASK		GENMASK_ULL(17, 8)
#घोषणा ECAP_SC_MASK		BIT_ULL(7)
#घोषणा ECAP_PT_MASK		BIT_ULL(6)
#घोषणा ECAP_EIM_MASK		BIT_ULL(4)
#घोषणा ECAP_DT_MASK		BIT_ULL(2)
#घोषणा ECAP_QI_MASK		BIT_ULL(1)
#घोषणा ECAP_C_MASK		BIT_ULL(0)

/*
 * u64 पूर्णांकel_iommu_cap_sanity, पूर्णांकel_iommu_ecap_sanity will be adjusted as each
 * IOMMU माला_लो audited.
 */
#घोषणा DO_CHECK_FEATURE_MISMATCH(a, b, cap, feature, MASK) \
करो अणु \
	अगर (cap##_##feature(a) != cap##_##feature(b)) अणु \
		पूर्णांकel_iommu_##cap##_sanity &= ~(MASK); \
		pr_info("IOMMU feature %s inconsistent", #feature); \
	पूर्ण \
पूर्ण जबतक (0)

#घोषणा CHECK_FEATURE_MISMATCH(a, b, cap, feature, MASK) \
	DO_CHECK_FEATURE_MISMATCH((a)->cap, (b)->cap, cap, feature, MASK)

#घोषणा CHECK_FEATURE_MISMATCH_HOTPLUG(b, cap, feature, MASK) \
करो अणु \
	अगर (cap##_##feature(पूर्णांकel_iommu_##cap##_sanity)) \
		DO_CHECK_FEATURE_MISMATCH(पूर्णांकel_iommu_##cap##_sanity, \
					  (b)->cap, cap, feature, MASK); \
पूर्ण जबतक (0)

#घोषणा MINIMAL_FEATURE_IOMMU(iommu, cap, MASK) \
करो अणु \
	u64 min_feature = पूर्णांकel_iommu_##cap##_sanity & (MASK); \
	min_feature = min_t(u64, min_feature, (iommu)->cap & (MASK)); \
	पूर्णांकel_iommu_##cap##_sanity = (पूर्णांकel_iommu_##cap##_sanity & ~(MASK)) | \
				     min_feature; \
पूर्ण जबतक (0)

#घोषणा MINIMAL_FEATURE_HOTPLUG(iommu, cap, feature, MASK, mismatch) \
करो अणु \
	अगर ((पूर्णांकel_iommu_##cap##_sanity & (MASK)) > \
	    (cap##_##feature((iommu)->cap))) \
		mismatch = true; \
	अन्यथा \
		(iommu)->cap = ((iommu)->cap & ~(MASK)) | \
		(पूर्णांकel_iommu_##cap##_sanity & (MASK)); \
पूर्ण जबतक (0)

क्रमागत cap_audit_type अणु
	CAP_AUDIT_STATIC_DMAR,
	CAP_AUDIT_STATIC_IRQR,
	CAP_AUDIT_HOTPLUG_DMAR,
	CAP_AUDIT_HOTPLUG_IRQR,
पूर्ण;

bool पूर्णांकel_cap_smts_sanity(व्योम);
bool पूर्णांकel_cap_pasid_sanity(व्योम);
bool पूर्णांकel_cap_nest_sanity(व्योम);
bool पूर्णांकel_cap_flts_sanity(व्योम);

अटल अंतरभूत bool scalable_mode_support(व्योम)
अणु
	वापस (पूर्णांकel_iommu_sm && पूर्णांकel_cap_smts_sanity());
पूर्ण

अटल अंतरभूत bool pasid_mode_support(व्योम)
अणु
	वापस scalable_mode_support() && पूर्णांकel_cap_pasid_sanity();
पूर्ण

अटल अंतरभूत bool nested_mode_support(व्योम)
अणु
	वापस scalable_mode_support() && पूर्णांकel_cap_nest_sanity();
पूर्ण

पूर्णांक पूर्णांकel_cap_audit(क्रमागत cap_audit_type type, काष्ठा पूर्णांकel_iommu *iommu);
