<शैली गुरु>
/*
 * Copyright तऊ 2016 Intel Corporation
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 */

#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/i915_pciids.h>

#समावेश "display/intel_cdclk.h"
#समावेश "display/intel_de.h"
#समावेश "intel_device_info.h"
#समावेश "i915_drv.h"

#घोषणा PLATFORM_NAME(x) [INTEL_##x] = #x
अटल स्थिर अक्षर * स्थिर platक्रमm_names[] = अणु
	PLATFORM_NAME(I830),
	PLATFORM_NAME(I845G),
	PLATFORM_NAME(I85X),
	PLATFORM_NAME(I865G),
	PLATFORM_NAME(I915G),
	PLATFORM_NAME(I915GM),
	PLATFORM_NAME(I945G),
	PLATFORM_NAME(I945GM),
	PLATFORM_NAME(G33),
	PLATFORM_NAME(PINEVIEW),
	PLATFORM_NAME(I965G),
	PLATFORM_NAME(I965GM),
	PLATFORM_NAME(G45),
	PLATFORM_NAME(GM45),
	PLATFORM_NAME(IRONLAKE),
	PLATFORM_NAME(SANDYBRIDGE),
	PLATFORM_NAME(IVYBRIDGE),
	PLATFORM_NAME(VALLEYVIEW),
	PLATFORM_NAME(HASWELL),
	PLATFORM_NAME(BROADWELL),
	PLATFORM_NAME(CHERRYVIEW),
	PLATFORM_NAME(SKYLAKE),
	PLATFORM_NAME(BROXTON),
	PLATFORM_NAME(KABYLAKE),
	PLATFORM_NAME(GEMINILAKE),
	PLATFORM_NAME(COFFEELAKE),
	PLATFORM_NAME(COMETLAKE),
	PLATFORM_NAME(CANNONLAKE),
	PLATFORM_NAME(ICELAKE),
	PLATFORM_NAME(ELKHARTLAKE),
	PLATFORM_NAME(JASPERLAKE),
	PLATFORM_NAME(TIGERLAKE),
	PLATFORM_NAME(ROCKETLAKE),
	PLATFORM_NAME(DG1),
	PLATFORM_NAME(ALDERLAKE_S),
पूर्ण;
#अघोषित PLATFORM_NAME

स्थिर अक्षर *पूर्णांकel_platक्रमm_name(क्रमागत पूर्णांकel_platक्रमm platक्रमm)
अणु
	BUILD_BUG_ON(ARRAY_SIZE(platक्रमm_names) != INTEL_MAX_PLATFORMS);

	अगर (WARN_ON_ONCE(platक्रमm >= ARRAY_SIZE(platक्रमm_names) ||
			 platक्रमm_names[platक्रमm] == शून्य))
		वापस "<unknown>";

	वापस platक्रमm_names[platक्रमm];
पूर्ण

अटल स्थिर अक्षर *iommu_name(व्योम)
अणु
	स्थिर अक्षर *msg = "n/a";

#अगर_घोषित CONFIG_INTEL_IOMMU
	msg = enableddisabled(पूर्णांकel_iommu_gfx_mapped);
#पूर्ण_अगर

	वापस msg;
पूर्ण

व्योम पूर्णांकel_device_info_prपूर्णांक_अटल(स्थिर काष्ठा पूर्णांकel_device_info *info,
				    काष्ठा drm_prपूर्णांकer *p)
अणु
	drm_म_लिखो(p, "gen: %d\n", info->gen);
	drm_म_लिखो(p, "gt: %d\n", info->gt);
	drm_म_लिखो(p, "iommu: %s\n", iommu_name());
	drm_म_लिखो(p, "memory-regions: %x\n", info->memory_regions);
	drm_म_लिखो(p, "page-sizes: %x\n", info->page_sizes);
	drm_म_लिखो(p, "platform: %s\n", पूर्णांकel_platक्रमm_name(info->platक्रमm));
	drm_म_लिखो(p, "ppgtt-size: %d\n", info->ppgtt_size);
	drm_म_लिखो(p, "ppgtt-type: %d\n", info->ppgtt_type);
	drm_म_लिखो(p, "dma_mask_size: %u\n", info->dma_mask_size);

#घोषणा PRINT_FLAG(name) drm_म_लिखो(p, "%s: %s\n", #name, yesno(info->name))
	DEV_INFO_FOR_EACH_FLAG(PRINT_FLAG);
#अघोषित PRINT_FLAG

#घोषणा PRINT_FLAG(name) drm_म_लिखो(p, "%s: %s\n", #name, yesno(info->display.name));
	DEV_INFO_DISPLAY_FOR_EACH_FLAG(PRINT_FLAG);
#अघोषित PRINT_FLAG
पूर्ण

व्योम पूर्णांकel_device_info_prपूर्णांक_runसमय(स्थिर काष्ठा पूर्णांकel_runसमय_info *info,
				     काष्ठा drm_prपूर्णांकer *p)
अणु
	drm_म_लिखो(p, "rawclk rate: %u kHz\n", info->rawclk_freq);
पूर्ण

#अघोषित INTEL_VGA_DEVICE
#घोषणा INTEL_VGA_DEVICE(id, info) (id)

अटल स्थिर u16 subplatक्रमm_ult_ids[] = अणु
	INTEL_HSW_ULT_GT1_IDS(0),
	INTEL_HSW_ULT_GT2_IDS(0),
	INTEL_HSW_ULT_GT3_IDS(0),
	INTEL_BDW_ULT_GT1_IDS(0),
	INTEL_BDW_ULT_GT2_IDS(0),
	INTEL_BDW_ULT_GT3_IDS(0),
	INTEL_BDW_ULT_RSVD_IDS(0),
	INTEL_SKL_ULT_GT1_IDS(0),
	INTEL_SKL_ULT_GT2_IDS(0),
	INTEL_SKL_ULT_GT3_IDS(0),
	INTEL_KBL_ULT_GT1_IDS(0),
	INTEL_KBL_ULT_GT2_IDS(0),
	INTEL_KBL_ULT_GT3_IDS(0),
	INTEL_CFL_U_GT2_IDS(0),
	INTEL_CFL_U_GT3_IDS(0),
	INTEL_WHL_U_GT1_IDS(0),
	INTEL_WHL_U_GT2_IDS(0),
	INTEL_WHL_U_GT3_IDS(0),
	INTEL_CML_U_GT1_IDS(0),
	INTEL_CML_U_GT2_IDS(0),
पूर्ण;

अटल स्थिर u16 subplatक्रमm_ulx_ids[] = अणु
	INTEL_HSW_ULX_GT1_IDS(0),
	INTEL_HSW_ULX_GT2_IDS(0),
	INTEL_BDW_ULX_GT1_IDS(0),
	INTEL_BDW_ULX_GT2_IDS(0),
	INTEL_BDW_ULX_GT3_IDS(0),
	INTEL_BDW_ULX_RSVD_IDS(0),
	INTEL_SKL_ULX_GT1_IDS(0),
	INTEL_SKL_ULX_GT2_IDS(0),
	INTEL_KBL_ULX_GT1_IDS(0),
	INTEL_KBL_ULX_GT2_IDS(0),
	INTEL_AML_KBL_GT2_IDS(0),
	INTEL_AML_CFL_GT2_IDS(0),
पूर्ण;

अटल स्थिर u16 subplatक्रमm_portf_ids[] = अणु
	INTEL_CNL_PORT_F_IDS(0),
	INTEL_ICL_PORT_F_IDS(0),
पूर्ण;

अटल bool find_devid(u16 id, स्थिर u16 *p, अचिन्हित पूर्णांक num)
अणु
	क्रम (; num; num--, p++) अणु
		अगर (*p == id)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

व्योम पूर्णांकel_device_info_subplatक्रमm_init(काष्ठा drm_i915_निजी *i915)
अणु
	स्थिर काष्ठा पूर्णांकel_device_info *info = INTEL_INFO(i915);
	स्थिर काष्ठा पूर्णांकel_runसमय_info *rinfo = RUNTIME_INFO(i915);
	स्थिर अचिन्हित पूर्णांक pi = __platक्रमm_mask_index(rinfo, info->platक्रमm);
	स्थिर अचिन्हित पूर्णांक pb = __platक्रमm_mask_bit(rinfo, info->platक्रमm);
	u16 devid = INTEL_DEVID(i915);
	u32 mask = 0;

	/* Make sure IS_<platक्रमm> checks are working. */
	RUNTIME_INFO(i915)->platक्रमm_mask[pi] = BIT(pb);

	/* Find and mark subplatक्रमm bits based on the PCI device id. */
	अगर (find_devid(devid, subplatक्रमm_ult_ids,
		       ARRAY_SIZE(subplatक्रमm_ult_ids))) अणु
		mask = BIT(INTEL_SUBPLATFORM_ULT);
	पूर्ण अन्यथा अगर (find_devid(devid, subplatक्रमm_ulx_ids,
			      ARRAY_SIZE(subplatक्रमm_ulx_ids))) अणु
		mask = BIT(INTEL_SUBPLATFORM_ULX);
		अगर (IS_HASWELL(i915) || IS_BROADWELL(i915)) अणु
			/* ULX machines are also considered ULT. */
			mask |= BIT(INTEL_SUBPLATFORM_ULT);
		पूर्ण
	पूर्ण अन्यथा अगर (find_devid(devid, subplatक्रमm_portf_ids,
			      ARRAY_SIZE(subplatक्रमm_portf_ids))) अणु
		mask = BIT(INTEL_SUBPLATFORM_PORTF);
	पूर्ण

	अगर (IS_TIGERLAKE(i915)) अणु
		काष्ठा pci_dev *root, *pdev = to_pci_dev(i915->drm.dev);

		root = list_first_entry(&pdev->bus->devices, typeof(*root), bus_list);

		drm_WARN_ON(&i915->drm, mask);
		drm_WARN_ON(&i915->drm, (root->device & TGL_ROOT_DEVICE_MASK) !=
			    TGL_ROOT_DEVICE_ID);

		चयन (root->device & TGL_ROOT_DEVICE_SKU_MASK) अणु
		हाल TGL_ROOT_DEVICE_SKU_ULX:
			mask = BIT(INTEL_SUBPLATFORM_ULX);
			अवरोध;
		हाल TGL_ROOT_DEVICE_SKU_ULT:
			mask = BIT(INTEL_SUBPLATFORM_ULT);
			अवरोध;
		पूर्ण
	पूर्ण

	GEM_BUG_ON(mask & ~INTEL_SUBPLATFORM_MASK);

	RUNTIME_INFO(i915)->platक्रमm_mask[pi] |= mask;
पूर्ण

/**
 * पूर्णांकel_device_info_runसमय_init - initialize runसमय info
 * @dev_priv: the i915 device
 *
 * Determine various पूर्णांकel_device_info fields at runसमय.
 *
 * Use it when either:
 *   - it's judged too laborious to fill n अटल काष्ठाures with the limit
 *     when a simple अगर statement करोes the job,
 *   - run-समय checks (eg पढ़ो fuse/strap रेजिस्टरs) are needed.
 *
 * This function needs to be called:
 *   - after the MMIO has been setup as we are पढ़ोing रेजिस्टरs,
 *   - after the PCH has been detected,
 *   - beक्रमe the first usage of the fields it can tweak.
 */
व्योम पूर्णांकel_device_info_runसमय_init(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा पूर्णांकel_device_info *info = mkग_लिखो_device_info(dev_priv);
	काष्ठा पूर्णांकel_runसमय_info *runसमय = RUNTIME_INFO(dev_priv);
	क्रमागत pipe pipe;

	/* Wa_14011765242: adl-s A0 */
	अगर (IS_ADLS_DISPLAY_STEP(dev_priv, STEP_A0, STEP_A0))
		क्रम_each_pipe(dev_priv, pipe)
			runसमय->num_scalers[pipe] = 0;
	अन्यथा अगर (INTEL_GEN(dev_priv) >= 10) अणु
		क्रम_each_pipe(dev_priv, pipe)
			runसमय->num_scalers[pipe] = 2;
	पूर्ण अन्यथा अगर (IS_GEN(dev_priv, 9)) अणु
		runसमय->num_scalers[PIPE_A] = 2;
		runसमय->num_scalers[PIPE_B] = 2;
		runसमय->num_scalers[PIPE_C] = 1;
	पूर्ण

	BUILD_BUG_ON(BITS_PER_TYPE(पूर्णांकel_engine_mask_t) < I915_NUM_ENGINES);

	अगर (HAS_D12_PLANE_MINIMIZATION(dev_priv))
		क्रम_each_pipe(dev_priv, pipe)
			runसमय->num_sprites[pipe] = 4;
	अन्यथा अगर (INTEL_GEN(dev_priv) >= 11)
		क्रम_each_pipe(dev_priv, pipe)
			runसमय->num_sprites[pipe] = 6;
	अन्यथा अगर (IS_GEN(dev_priv, 10) || IS_GEMINILAKE(dev_priv))
		क्रम_each_pipe(dev_priv, pipe)
			runसमय->num_sprites[pipe] = 3;
	अन्यथा अगर (IS_BROXTON(dev_priv)) अणु
		/*
		 * Skylake and Broxton currently करोn't expose the topmost plane as its
		 * use is exclusive with the legacy cursor and we only want to expose
		 * one of those, not both. Until we can safely expose the topmost plane
		 * as a DRM_PLANE_TYPE_CURSOR with all the features exposed/supported,
		 * we करोn't expose the topmost plane at all to prevent ABI अवरोधage
		 * करोwn the line.
		 */

		runसमय->num_sprites[PIPE_A] = 2;
		runसमय->num_sprites[PIPE_B] = 2;
		runसमय->num_sprites[PIPE_C] = 1;
	पूर्ण अन्यथा अगर (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv)) अणु
		क्रम_each_pipe(dev_priv, pipe)
			runसमय->num_sprites[pipe] = 2;
	पूर्ण अन्यथा अगर (INTEL_GEN(dev_priv) >= 5 || IS_G4X(dev_priv)) अणु
		क्रम_each_pipe(dev_priv, pipe)
			runसमय->num_sprites[pipe] = 1;
	पूर्ण

	अगर (HAS_DISPLAY(dev_priv) && IS_GEN_RANGE(dev_priv, 7, 8) &&
	    HAS_PCH_SPLIT(dev_priv)) अणु
		u32 fuse_strap = पूर्णांकel_de_पढ़ो(dev_priv, FUSE_STRAP);
		u32 sfuse_strap = पूर्णांकel_de_पढ़ो(dev_priv, SFUSE_STRAP);

		/*
		 * SFUSE_STRAP is supposed to have a bit संकेतling the display
		 * is fused off. Unक्रमtunately it seems that, at least in
		 * certain हालs, fused off display means that PCH display
		 * पढ़ोs करोn't land anywhere. In that हाल, we पढ़ो 0s.
		 *
		 * On CPT/PPT, we can detect this हाल as SFUSE_STRAP_FUSE_LOCK
		 * should be set when taking over after the firmware.
		 */
		अगर (fuse_strap & ILK_INTERNAL_DISPLAY_DISABLE ||
		    sfuse_strap & SFUSE_STRAP_DISPLAY_DISABLED ||
		    (HAS_PCH_CPT(dev_priv) &&
		     !(sfuse_strap & SFUSE_STRAP_FUSE_LOCK))) अणु
			drm_info(&dev_priv->drm,
				 "Display fused off, disabling\n");
			info->pipe_mask = 0;
			info->cpu_transcoder_mask = 0;
		पूर्ण अन्यथा अगर (fuse_strap & IVB_PIPE_C_DISABLE) अणु
			drm_info(&dev_priv->drm, "PipeC fused off\n");
			info->pipe_mask &= ~BIT(PIPE_C);
			info->cpu_transcoder_mask &= ~BIT(TRANSCODER_C);
		पूर्ण
	पूर्ण अन्यथा अगर (HAS_DISPLAY(dev_priv) && INTEL_GEN(dev_priv) >= 9) अणु
		u32 dfsm = पूर्णांकel_de_पढ़ो(dev_priv, SKL_DFSM);

		अगर (dfsm & SKL_DFSM_PIPE_A_DISABLE) अणु
			info->pipe_mask &= ~BIT(PIPE_A);
			info->cpu_transcoder_mask &= ~BIT(TRANSCODER_A);
		पूर्ण
		अगर (dfsm & SKL_DFSM_PIPE_B_DISABLE) अणु
			info->pipe_mask &= ~BIT(PIPE_B);
			info->cpu_transcoder_mask &= ~BIT(TRANSCODER_B);
		पूर्ण
		अगर (dfsm & SKL_DFSM_PIPE_C_DISABLE) अणु
			info->pipe_mask &= ~BIT(PIPE_C);
			info->cpu_transcoder_mask &= ~BIT(TRANSCODER_C);
		पूर्ण
		अगर (INTEL_GEN(dev_priv) >= 12 &&
		    (dfsm & TGL_DFSM_PIPE_D_DISABLE)) अणु
			info->pipe_mask &= ~BIT(PIPE_D);
			info->cpu_transcoder_mask &= ~BIT(TRANSCODER_D);
		पूर्ण

		अगर (dfsm & SKL_DFSM_DISPLAY_HDCP_DISABLE)
			info->display.has_hdcp = 0;

		अगर (dfsm & SKL_DFSM_DISPLAY_PM_DISABLE)
			info->display.has_fbc = 0;

		अगर (INTEL_GEN(dev_priv) >= 11 && (dfsm & ICL_DFSM_DMC_DISABLE))
			info->display.has_csr = 0;

		अगर (INTEL_GEN(dev_priv) >= 10 &&
		    (dfsm & CNL_DFSM_DISPLAY_DSC_DISABLE))
			info->display.has_dsc = 0;
	पूर्ण

	अगर (IS_GEN(dev_priv, 6) && पूर्णांकel_vtd_active()) अणु
		drm_info(&dev_priv->drm,
			 "Disabling ppGTT for VT-d support\n");
		info->ppgtt_type = INTEL_PPGTT_NONE;
	पूर्ण

	runसमय->rawclk_freq = पूर्णांकel_पढ़ो_rawclk(dev_priv);
	drm_dbg(&dev_priv->drm, "rawclk rate: %d kHz\n", runसमय->rawclk_freq);

	अगर (!HAS_DISPLAY(dev_priv)) अणु
		dev_priv->drm.driver_features &= ~(DRIVER_MODESET |
						   DRIVER_ATOMIC);
		स_रखो(&info->display, 0, माप(info->display));
		स_रखो(runसमय->num_sprites, 0, माप(runसमय->num_sprites));
		स_रखो(runसमय->num_scalers, 0, माप(runसमय->num_scalers));
	पूर्ण
पूर्ण

व्योम पूर्णांकel_driver_caps_prपूर्णांक(स्थिर काष्ठा पूर्णांकel_driver_caps *caps,
			     काष्ठा drm_prपूर्णांकer *p)
अणु
	drm_म_लिखो(p, "Has logical contexts? %s\n",
		   yesno(caps->has_logical_contexts));
	drm_म_लिखो(p, "scheduler: %x\n", caps->scheduler);
पूर्ण
