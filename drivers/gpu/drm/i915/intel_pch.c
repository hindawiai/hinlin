<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright 2019 Intel Corporation.
 */

#समावेश "i915_drv.h"
#समावेश "intel_pch.h"

/* Map PCH device id to PCH type, or PCH_NONE अगर unknown. */
अटल क्रमागत पूर्णांकel_pch
पूर्णांकel_pch_type(स्थिर काष्ठा drm_i915_निजी *dev_priv, अचिन्हित लघु id)
अणु
	चयन (id) अणु
	हाल INTEL_PCH_IBX_DEVICE_ID_TYPE:
		drm_dbg_kms(&dev_priv->drm, "Found Ibex Peak PCH\n");
		drm_WARN_ON(&dev_priv->drm, !IS_GEN(dev_priv, 5));
		वापस PCH_IBX;
	हाल INTEL_PCH_CPT_DEVICE_ID_TYPE:
		drm_dbg_kms(&dev_priv->drm, "Found CougarPoint PCH\n");
		drm_WARN_ON(&dev_priv->drm,
			    !IS_GEN(dev_priv, 6) && !IS_IVYBRIDGE(dev_priv));
		वापस PCH_CPT;
	हाल INTEL_PCH_PPT_DEVICE_ID_TYPE:
		drm_dbg_kms(&dev_priv->drm, "Found PantherPoint PCH\n");
		drm_WARN_ON(&dev_priv->drm,
			    !IS_GEN(dev_priv, 6) && !IS_IVYBRIDGE(dev_priv));
		/* PantherPoपूर्णांक is CPT compatible */
		वापस PCH_CPT;
	हाल INTEL_PCH_LPT_DEVICE_ID_TYPE:
		drm_dbg_kms(&dev_priv->drm, "Found LynxPoint PCH\n");
		drm_WARN_ON(&dev_priv->drm,
			    !IS_HASWELL(dev_priv) && !IS_BROADWELL(dev_priv));
		drm_WARN_ON(&dev_priv->drm,
			    IS_HSW_ULT(dev_priv) || IS_BDW_ULT(dev_priv));
		वापस PCH_LPT;
	हाल INTEL_PCH_LPT_LP_DEVICE_ID_TYPE:
		drm_dbg_kms(&dev_priv->drm, "Found LynxPoint LP PCH\n");
		drm_WARN_ON(&dev_priv->drm,
			    !IS_HASWELL(dev_priv) && !IS_BROADWELL(dev_priv));
		drm_WARN_ON(&dev_priv->drm,
			    !IS_HSW_ULT(dev_priv) && !IS_BDW_ULT(dev_priv));
		वापस PCH_LPT;
	हाल INTEL_PCH_WPT_DEVICE_ID_TYPE:
		drm_dbg_kms(&dev_priv->drm, "Found WildcatPoint PCH\n");
		drm_WARN_ON(&dev_priv->drm,
			    !IS_HASWELL(dev_priv) && !IS_BROADWELL(dev_priv));
		drm_WARN_ON(&dev_priv->drm,
			    IS_HSW_ULT(dev_priv) || IS_BDW_ULT(dev_priv));
		/* WildcatPoपूर्णांक is LPT compatible */
		वापस PCH_LPT;
	हाल INTEL_PCH_WPT_LP_DEVICE_ID_TYPE:
		drm_dbg_kms(&dev_priv->drm, "Found WildcatPoint LP PCH\n");
		drm_WARN_ON(&dev_priv->drm,
			    !IS_HASWELL(dev_priv) && !IS_BROADWELL(dev_priv));
		drm_WARN_ON(&dev_priv->drm,
			    !IS_HSW_ULT(dev_priv) && !IS_BDW_ULT(dev_priv));
		/* WildcatPoपूर्णांक is LPT compatible */
		वापस PCH_LPT;
	हाल INTEL_PCH_SPT_DEVICE_ID_TYPE:
		drm_dbg_kms(&dev_priv->drm, "Found SunrisePoint PCH\n");
		drm_WARN_ON(&dev_priv->drm,
			    !IS_SKYLAKE(dev_priv) && !IS_KABYLAKE(dev_priv));
		वापस PCH_SPT;
	हाल INTEL_PCH_SPT_LP_DEVICE_ID_TYPE:
		drm_dbg_kms(&dev_priv->drm, "Found SunrisePoint LP PCH\n");
		drm_WARN_ON(&dev_priv->drm,
			    !IS_SKYLAKE(dev_priv) &&
			    !IS_KABYLAKE(dev_priv) &&
			    !IS_COFFEELAKE(dev_priv) &&
			    !IS_COMETLAKE(dev_priv));
		वापस PCH_SPT;
	हाल INTEL_PCH_KBP_DEVICE_ID_TYPE:
		drm_dbg_kms(&dev_priv->drm, "Found Kaby Lake PCH (KBP)\n");
		drm_WARN_ON(&dev_priv->drm,
			    !IS_SKYLAKE(dev_priv) &&
			    !IS_KABYLAKE(dev_priv) &&
			    !IS_COFFEELAKE(dev_priv) &&
			    !IS_COMETLAKE(dev_priv));
		/* KBP is SPT compatible */
		वापस PCH_SPT;
	हाल INTEL_PCH_CNP_DEVICE_ID_TYPE:
		drm_dbg_kms(&dev_priv->drm, "Found Cannon Lake PCH (CNP)\n");
		drm_WARN_ON(&dev_priv->drm,
			    !IS_CANNONLAKE(dev_priv) &&
			    !IS_COFFEELAKE(dev_priv) &&
			    !IS_COMETLAKE(dev_priv));
		वापस PCH_CNP;
	हाल INTEL_PCH_CNP_LP_DEVICE_ID_TYPE:
		drm_dbg_kms(&dev_priv->drm,
			    "Found Cannon Lake LP PCH (CNP-LP)\n");
		drm_WARN_ON(&dev_priv->drm,
			    !IS_CANNONLAKE(dev_priv) &&
			    !IS_COFFEELAKE(dev_priv) &&
			    !IS_COMETLAKE(dev_priv));
		वापस PCH_CNP;
	हाल INTEL_PCH_CMP_DEVICE_ID_TYPE:
	हाल INTEL_PCH_CMP2_DEVICE_ID_TYPE:
		drm_dbg_kms(&dev_priv->drm, "Found Comet Lake PCH (CMP)\n");
		drm_WARN_ON(&dev_priv->drm,
			    !IS_COFFEELAKE(dev_priv) &&
			    !IS_COMETLAKE(dev_priv) &&
			    !IS_ROCKETLAKE(dev_priv));
		/* CometPoपूर्णांक is CNP Compatible */
		वापस PCH_CNP;
	हाल INTEL_PCH_CMP_V_DEVICE_ID_TYPE:
		drm_dbg_kms(&dev_priv->drm, "Found Comet Lake V PCH (CMP-V)\n");
		drm_WARN_ON(&dev_priv->drm,
			    !IS_COFFEELAKE(dev_priv) &&
			    !IS_COMETLAKE(dev_priv));
		/* Comet Lake V PCH is based on KBP, which is SPT compatible */
		वापस PCH_SPT;
	हाल INTEL_PCH_ICP_DEVICE_ID_TYPE:
		drm_dbg_kms(&dev_priv->drm, "Found Ice Lake PCH\n");
		drm_WARN_ON(&dev_priv->drm, !IS_ICELAKE(dev_priv));
		वापस PCH_ICP;
	हाल INTEL_PCH_MCC_DEVICE_ID_TYPE:
		drm_dbg_kms(&dev_priv->drm, "Found Mule Creek Canyon PCH\n");
		drm_WARN_ON(&dev_priv->drm, !IS_JSL_EHL(dev_priv));
		वापस PCH_MCC;
	हाल INTEL_PCH_TGP_DEVICE_ID_TYPE:
	हाल INTEL_PCH_TGP2_DEVICE_ID_TYPE:
		drm_dbg_kms(&dev_priv->drm, "Found Tiger Lake LP PCH\n");
		drm_WARN_ON(&dev_priv->drm, !IS_TIGERLAKE(dev_priv) &&
			    !IS_ROCKETLAKE(dev_priv) &&
			    !IS_GEN9_BC(dev_priv));
		वापस PCH_TGP;
	हाल INTEL_PCH_JSP_DEVICE_ID_TYPE:
	हाल INTEL_PCH_JSP2_DEVICE_ID_TYPE:
		drm_dbg_kms(&dev_priv->drm, "Found Jasper Lake PCH\n");
		drm_WARN_ON(&dev_priv->drm, !IS_JSL_EHL(dev_priv));
		वापस PCH_JSP;
	हाल INTEL_PCH_ADP_DEVICE_ID_TYPE:
		drm_dbg_kms(&dev_priv->drm, "Found Alder Lake PCH\n");
		drm_WARN_ON(&dev_priv->drm, !IS_ALDERLAKE_S(dev_priv));
		वापस PCH_ADP;
	शेष:
		वापस PCH_NONE;
	पूर्ण
पूर्ण

अटल bool पूर्णांकel_is_virt_pch(अचिन्हित लघु id,
			      अचिन्हित लघु svenकरोr, अचिन्हित लघु sdevice)
अणु
	वापस (id == INTEL_PCH_P2X_DEVICE_ID_TYPE ||
		id == INTEL_PCH_P3X_DEVICE_ID_TYPE ||
		(id == INTEL_PCH_QEMU_DEVICE_ID_TYPE &&
		 svenकरोr == PCI_SUBVENDOR_ID_REDHAT_QUMRANET &&
		 sdevice == PCI_SUBDEVICE_ID_QEMU));
पूर्ण

अटल व्योम
पूर्णांकel_virt_detect_pch(स्थिर काष्ठा drm_i915_निजी *dev_priv,
		      अचिन्हित लघु *pch_id, क्रमागत पूर्णांकel_pch *pch_type)
अणु
	अचिन्हित लघु id = 0;

	/*
	 * In a भवized passthrough environment we can be in a
	 * setup where the ISA bridge is not able to be passed through.
	 * In this हाल, a south bridge can be emulated and we have to
	 * make an educated guess as to which PCH is really there.
	 */

	अगर (IS_ALDERLAKE_S(dev_priv))
		id = INTEL_PCH_ADP_DEVICE_ID_TYPE;
	अन्यथा अगर (IS_TIGERLAKE(dev_priv) || IS_ROCKETLAKE(dev_priv))
		id = INTEL_PCH_TGP_DEVICE_ID_TYPE;
	अन्यथा अगर (IS_JSL_EHL(dev_priv))
		id = INTEL_PCH_MCC_DEVICE_ID_TYPE;
	अन्यथा अगर (IS_ICELAKE(dev_priv))
		id = INTEL_PCH_ICP_DEVICE_ID_TYPE;
	अन्यथा अगर (IS_CANNONLAKE(dev_priv) ||
		 IS_COFFEELAKE(dev_priv) ||
		 IS_COMETLAKE(dev_priv))
		id = INTEL_PCH_CNP_DEVICE_ID_TYPE;
	अन्यथा अगर (IS_KABYLAKE(dev_priv) || IS_SKYLAKE(dev_priv))
		id = INTEL_PCH_SPT_DEVICE_ID_TYPE;
	अन्यथा अगर (IS_HSW_ULT(dev_priv) || IS_BDW_ULT(dev_priv))
		id = INTEL_PCH_LPT_LP_DEVICE_ID_TYPE;
	अन्यथा अगर (IS_HASWELL(dev_priv) || IS_BROADWELL(dev_priv))
		id = INTEL_PCH_LPT_DEVICE_ID_TYPE;
	अन्यथा अगर (IS_GEN(dev_priv, 6) || IS_IVYBRIDGE(dev_priv))
		id = INTEL_PCH_CPT_DEVICE_ID_TYPE;
	अन्यथा अगर (IS_GEN(dev_priv, 5))
		id = INTEL_PCH_IBX_DEVICE_ID_TYPE;

	अगर (id)
		drm_dbg_kms(&dev_priv->drm, "Assuming PCH ID %04x\n", id);
	अन्यथा
		drm_dbg_kms(&dev_priv->drm, "Assuming no PCH\n");

	*pch_type = पूर्णांकel_pch_type(dev_priv, id);

	/* Sanity check भव PCH id */
	अगर (drm_WARN_ON(&dev_priv->drm,
			id && *pch_type == PCH_NONE))
		id = 0;

	*pch_id = id;
पूर्ण

व्योम पूर्णांकel_detect_pch(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा pci_dev *pch = शून्य;
	अचिन्हित लघु id;
	क्रमागत पूर्णांकel_pch pch_type;

	/* DG1 has south engine display on the same PCI device */
	अगर (IS_DG1(dev_priv)) अणु
		dev_priv->pch_type = PCH_DG1;
		वापस;
	पूर्ण

	/*
	 * The reason to probe ISA bridge instead of Dev31:Fun0 is to
	 * make graphics device passthrough work easy क्रम VMM, that only
	 * need to expose ISA bridge to let driver know the real hardware
	 * underneath. This is a requirement from भवization team.
	 *
	 * In some भवized environments (e.g. XEN), there is irrelevant
	 * ISA bridge in the प्रणाली. To work reliably, we should scan trhough
	 * all the ISA bridge devices and check क्रम the first match, instead
	 * of only checking the first one.
	 */
	जबतक ((pch = pci_get_class(PCI_CLASS_BRIDGE_ISA << 8, pch))) अणु
		अगर (pch->venकरोr != PCI_VENDOR_ID_INTEL)
			जारी;

		id = pch->device & INTEL_PCH_DEVICE_ID_MASK;

		pch_type = पूर्णांकel_pch_type(dev_priv, id);
		अगर (pch_type != PCH_NONE) अणु
			dev_priv->pch_type = pch_type;
			dev_priv->pch_id = id;
			अवरोध;
		पूर्ण अन्यथा अगर (पूर्णांकel_is_virt_pch(id, pch->subप्रणाली_venकरोr,
					     pch->subप्रणाली_device)) अणु
			पूर्णांकel_virt_detect_pch(dev_priv, &id, &pch_type);
			dev_priv->pch_type = pch_type;
			dev_priv->pch_id = id;
			अवरोध;
		पूर्ण
	पूर्ण

	/*
	 * Use PCH_NOP (PCH but no South Display) क्रम PCH platक्रमms without
	 * display.
	 */
	अगर (pch && !HAS_DISPLAY(dev_priv)) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "Display disabled, reverting to NOP PCH\n");
		dev_priv->pch_type = PCH_NOP;
		dev_priv->pch_id = 0;
	पूर्ण अन्यथा अगर (!pch) अणु
		अगर (run_as_guest() && HAS_DISPLAY(dev_priv)) अणु
			पूर्णांकel_virt_detect_pch(dev_priv, &id, &pch_type);
			dev_priv->pch_type = pch_type;
			dev_priv->pch_id = id;
		पूर्ण अन्यथा अणु
			drm_dbg_kms(&dev_priv->drm, "No PCH found.\n");
		पूर्ण
	पूर्ण

	pci_dev_put(pch);
पूर्ण
