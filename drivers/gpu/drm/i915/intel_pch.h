<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright 2019 Intel Corporation.
 */

#अगर_अघोषित __INTEL_PCH__
#घोषणा __INTEL_PCH__

काष्ठा drm_i915_निजी;

/*
 * Sorted by south display engine compatibility.
 * If the new PCH comes with a south display engine that is not
 * inherited from the latest item, please करो not add it to the
 * end. Instead, add it right after its "parent" PCH.
 */
क्रमागत पूर्णांकel_pch अणु
	PCH_NOP = -1,	/* PCH without south display */
	PCH_NONE = 0,	/* No PCH present */
	PCH_IBX,	/* Ibexpeak PCH */
	PCH_CPT,	/* Cougarpoपूर्णांक/Pantherpoपूर्णांक PCH */
	PCH_LPT,	/* Lynxpoपूर्णांक/Wildcatpoपूर्णांक PCH */
	PCH_SPT,        /* Sunrisepoपूर्णांक/Kaby Lake PCH */
	PCH_CNP,        /* Cannon/Comet Lake PCH */
	PCH_ICP,	/* Ice Lake PCH */
	PCH_JSP,	/* Jasper Lake PCH */
	PCH_MCC,        /* Mule Creek Canyon PCH */
	PCH_TGP,	/* Tiger Lake PCH */
	PCH_ADP,	/* Alder Lake PCH */

	/* Fake PCHs, functionality handled on the same PCI dev */
	PCH_DG1 = 1024,
पूर्ण;

#घोषणा INTEL_PCH_DEVICE_ID_MASK		0xff80
#घोषणा INTEL_PCH_IBX_DEVICE_ID_TYPE		0x3b00
#घोषणा INTEL_PCH_CPT_DEVICE_ID_TYPE		0x1c00
#घोषणा INTEL_PCH_PPT_DEVICE_ID_TYPE		0x1e00
#घोषणा INTEL_PCH_LPT_DEVICE_ID_TYPE		0x8c00
#घोषणा INTEL_PCH_LPT_LP_DEVICE_ID_TYPE		0x9c00
#घोषणा INTEL_PCH_WPT_DEVICE_ID_TYPE		0x8c80
#घोषणा INTEL_PCH_WPT_LP_DEVICE_ID_TYPE		0x9c80
#घोषणा INTEL_PCH_SPT_DEVICE_ID_TYPE		0xA100
#घोषणा INTEL_PCH_SPT_LP_DEVICE_ID_TYPE		0x9D00
#घोषणा INTEL_PCH_KBP_DEVICE_ID_TYPE		0xA280
#घोषणा INTEL_PCH_CNP_DEVICE_ID_TYPE		0xA300
#घोषणा INTEL_PCH_CNP_LP_DEVICE_ID_TYPE		0x9D80
#घोषणा INTEL_PCH_CMP_DEVICE_ID_TYPE		0x0280
#घोषणा INTEL_PCH_CMP2_DEVICE_ID_TYPE		0x0680
#घोषणा INTEL_PCH_CMP_V_DEVICE_ID_TYPE		0xA380
#घोषणा INTEL_PCH_ICP_DEVICE_ID_TYPE		0x3480
#घोषणा INTEL_PCH_MCC_DEVICE_ID_TYPE		0x4B00
#घोषणा INTEL_PCH_TGP_DEVICE_ID_TYPE		0xA080
#घोषणा INTEL_PCH_TGP2_DEVICE_ID_TYPE		0x4380
#घोषणा INTEL_PCH_JSP_DEVICE_ID_TYPE		0x4D80
#घोषणा INTEL_PCH_JSP2_DEVICE_ID_TYPE		0x3880
#घोषणा INTEL_PCH_ADP_DEVICE_ID_TYPE		0x7A80
#घोषणा INTEL_PCH_P2X_DEVICE_ID_TYPE		0x7100
#घोषणा INTEL_PCH_P3X_DEVICE_ID_TYPE		0x7000
#घोषणा INTEL_PCH_QEMU_DEVICE_ID_TYPE		0x2900 /* qemu q35 has 2918 */

#घोषणा INTEL_PCH_TYPE(dev_priv)		((dev_priv)->pch_type)
#घोषणा INTEL_PCH_ID(dev_priv)			((dev_priv)->pch_id)
#घोषणा HAS_PCH_ADP(dev_priv)			(INTEL_PCH_TYPE(dev_priv) == PCH_ADP)
#घोषणा HAS_PCH_DG1(dev_priv)			(INTEL_PCH_TYPE(dev_priv) == PCH_DG1)
#घोषणा HAS_PCH_JSP(dev_priv)			(INTEL_PCH_TYPE(dev_priv) == PCH_JSP)
#घोषणा HAS_PCH_MCC(dev_priv)			(INTEL_PCH_TYPE(dev_priv) == PCH_MCC)
#घोषणा HAS_PCH_TGP(dev_priv)			(INTEL_PCH_TYPE(dev_priv) == PCH_TGP)
#घोषणा HAS_PCH_ICP(dev_priv)			(INTEL_PCH_TYPE(dev_priv) == PCH_ICP)
#घोषणा HAS_PCH_CNP(dev_priv)			(INTEL_PCH_TYPE(dev_priv) == PCH_CNP)
#घोषणा HAS_PCH_SPT(dev_priv)			(INTEL_PCH_TYPE(dev_priv) == PCH_SPT)
#घोषणा HAS_PCH_LPT(dev_priv)			(INTEL_PCH_TYPE(dev_priv) == PCH_LPT)
#घोषणा HAS_PCH_LPT_LP(dev_priv) \
	(INTEL_PCH_ID(dev_priv) == INTEL_PCH_LPT_LP_DEVICE_ID_TYPE || \
	 INTEL_PCH_ID(dev_priv) == INTEL_PCH_WPT_LP_DEVICE_ID_TYPE)
#घोषणा HAS_PCH_LPT_H(dev_priv) \
	(INTEL_PCH_ID(dev_priv) == INTEL_PCH_LPT_DEVICE_ID_TYPE || \
	 INTEL_PCH_ID(dev_priv) == INTEL_PCH_WPT_DEVICE_ID_TYPE)
#घोषणा HAS_PCH_CPT(dev_priv)			(INTEL_PCH_TYPE(dev_priv) == PCH_CPT)
#घोषणा HAS_PCH_IBX(dev_priv)			(INTEL_PCH_TYPE(dev_priv) == PCH_IBX)
#घोषणा HAS_PCH_NOP(dev_priv)			(INTEL_PCH_TYPE(dev_priv) == PCH_NOP)
#घोषणा HAS_PCH_SPLIT(dev_priv)			(INTEL_PCH_TYPE(dev_priv) != PCH_NONE)

व्योम पूर्णांकel_detect_pch(काष्ठा drm_i915_निजी *dev_priv);

#पूर्ण_अगर /* __INTEL_PCH__ */
