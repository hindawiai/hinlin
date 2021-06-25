<शैली गुरु>
/*
 * Copyright तऊ 2014-2017 Intel Corporation
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

#अगर_अघोषित _INTEL_DEVICE_INFO_H_
#घोषणा _INTEL_DEVICE_INFO_H_

#समावेश <uapi/drm/i915_drm.h>

#समावेश "intel_step.h"

#समावेश "display/intel_display.h"

#समावेश "gt/intel_engine_types.h"
#समावेश "gt/intel_context_types.h"
#समावेश "gt/intel_sseu.h"

काष्ठा drm_prपूर्णांकer;
काष्ठा drm_i915_निजी;

/* Keep in gen based order, and chronological order within a gen */
क्रमागत पूर्णांकel_platक्रमm अणु
	INTEL_PLATFORM_UNINITIALIZED = 0,
	/* gen2 */
	INTEL_I830,
	INTEL_I845G,
	INTEL_I85X,
	INTEL_I865G,
	/* gen3 */
	INTEL_I915G,
	INTEL_I915GM,
	INTEL_I945G,
	INTEL_I945GM,
	INTEL_G33,
	INTEL_PINEVIEW,
	/* gen4 */
	INTEL_I965G,
	INTEL_I965GM,
	INTEL_G45,
	INTEL_GM45,
	/* gen5 */
	INTEL_IRONLAKE,
	/* gen6 */
	INTEL_SANDYBRIDGE,
	/* gen7 */
	INTEL_IVYBRIDGE,
	INTEL_VALLEYVIEW,
	INTEL_HASWELL,
	/* gen8 */
	INTEL_BROADWELL,
	INTEL_CHERRYVIEW,
	/* gen9 */
	INTEL_SKYLAKE,
	INTEL_BROXTON,
	INTEL_KABYLAKE,
	INTEL_GEMINILAKE,
	INTEL_COFFEELAKE,
	INTEL_COMETLAKE,
	/* gen10 */
	INTEL_CANNONLAKE,
	/* gen11 */
	INTEL_ICELAKE,
	INTEL_ELKHARTLAKE,
	INTEL_JASPERLAKE,
	/* gen12 */
	INTEL_TIGERLAKE,
	INTEL_ROCKETLAKE,
	INTEL_DG1,
	INTEL_ALDERLAKE_S,
	INTEL_MAX_PLATFORMS
पूर्ण;

/*
 * Subplatक्रमm bits share the same namespace per parent platक्रमm. In other words
 * it is fine क्रम the same bit to be used on multiple parent platक्रमms.
 */

#घोषणा INTEL_SUBPLATFORM_BITS (2)
#घोषणा INTEL_SUBPLATFORM_MASK (BIT(INTEL_SUBPLATFORM_BITS) - 1)

/* HSW/BDW/SKL/KBL/CFL */
#घोषणा INTEL_SUBPLATFORM_ULT	(0)
#घोषणा INTEL_SUBPLATFORM_ULX	(1)

/* CNL/ICL */
#घोषणा INTEL_SUBPLATFORM_PORTF	(0)

क्रमागत पूर्णांकel_ppgtt_type अणु
	INTEL_PPGTT_NONE = I915_GEM_PPGTT_NONE,
	INTEL_PPGTT_ALIASING = I915_GEM_PPGTT_ALIASING,
	INTEL_PPGTT_FULL = I915_GEM_PPGTT_FULL,
पूर्ण;

#घोषणा DEV_INFO_FOR_EACH_FLAG(func) \
	func(is_mobile); \
	func(is_lp); \
	func(require_क्रमce_probe); \
	func(is_dgfx); \
	/* Keep has_* in alphabetical order */ \
	func(has_64bit_reloc); \
	func(gpu_reset_clobbers_display); \
	func(has_reset_engine); \
	func(has_global_mocs); \
	func(has_gt_uc); \
	func(has_l3_dpf); \
	func(has_llc); \
	func(has_logical_ring_contexts); \
	func(has_logical_ring_elsq); \
	func(has_master_unit_irq); \
	func(has_pooled_eu); \
	func(has_rc6); \
	func(has_rc6p); \
	func(has_rps); \
	func(has_runसमय_pm); \
	func(has_snoop); \
	func(has_coherent_ggtt); \
	func(unfenced_needs_alignment); \
	func(hws_needs_physical);

#घोषणा DEV_INFO_DISPLAY_FOR_EACH_FLAG(func) \
	/* Keep in alphabetical order */ \
	func(cursor_needs_physical); \
	func(has_csr); \
	func(has_ddi); \
	func(has_dp_mst); \
	func(has_dsb); \
	func(has_dsc); \
	func(has_fbc); \
	func(has_fpga_dbg); \
	func(has_gmch); \
	func(has_hdcp); \
	func(has_hotplug); \
	func(has_hti); \
	func(has_ipc); \
	func(has_modular_fia); \
	func(has_overlay); \
	func(has_psr); \
	func(has_psr_hw_tracking); \
	func(overlay_needs_physical); \
	func(supports_tv);

काष्ठा पूर्णांकel_device_info अणु
	u16 gen_mask;

	u8 gen;
	u8 gt; /* GT number, 0 अगर undefined */
	पूर्णांकel_engine_mask_t platक्रमm_engine_mask; /* Engines supported by the HW */

	क्रमागत पूर्णांकel_platक्रमm platक्रमm;

	अचिन्हित पूर्णांक dma_mask_size; /* available DMA address bits */

	क्रमागत पूर्णांकel_ppgtt_type ppgtt_type;
	अचिन्हित पूर्णांक ppgtt_size; /* log2, e.g. 31/32/48 bits */

	अचिन्हित पूर्णांक page_sizes; /* page sizes supported by the HW */

	u32 memory_regions; /* regions supported by the HW */

	u32 display_mmio_offset;

	u8 pipe_mask;
	u8 cpu_transcoder_mask;

	u8 abox_mask;

#घोषणा DEFINE_FLAG(name) u8 name:1
	DEV_INFO_FOR_EACH_FLAG(DEFINE_FLAG);
#अघोषित DEFINE_FLAG

	काष्ठा अणु
		u8 version;

#घोषणा DEFINE_FLAG(name) u8 name:1
		DEV_INFO_DISPLAY_FOR_EACH_FLAG(DEFINE_FLAG);
#अघोषित DEFINE_FLAG
	पूर्ण display;

	u16 ddb_size; /* in blocks */
	u8 num_supported_dbuf_slices; /* number of DBuf slices */

	/* Register offsets क्रम the various display pipes and transcoders */
	पूर्णांक pipe_offsets[I915_MAX_TRANSCODERS];
	पूर्णांक trans_offsets[I915_MAX_TRANSCODERS];
	पूर्णांक cursor_offsets[I915_MAX_PIPES];

	काष्ठा color_luts अणु
		u32 degamma_lut_size;
		u32 gamma_lut_size;
		u32 degamma_lut_tests;
		u32 gamma_lut_tests;
	पूर्ण color;
पूर्ण;

काष्ठा पूर्णांकel_runसमय_info अणु
	/*
	 * Platक्रमm mask is used क्रम optimizing or-ed IS_PLATFORM calls पूर्णांकo
	 * पूर्णांकo single runसमय conditionals, and also to provide groundwork
	 * क्रम future per platक्रमm, or per SKU build optimizations.
	 *
	 * Array can be extended when necessary अगर the corresponding
	 * BUILD_BUG_ON is hit.
	 */
	u32 platक्रमm_mask[2];

	u16 device_id;

	u8 num_sprites[I915_MAX_PIPES];
	u8 num_scalers[I915_MAX_PIPES];

	u32 rawclk_freq;

	काष्ठा पूर्णांकel_step_info step;
पूर्ण;

काष्ठा पूर्णांकel_driver_caps अणु
	अचिन्हित पूर्णांक scheduler;
	bool has_logical_contexts:1;
पूर्ण;

स्थिर अक्षर *पूर्णांकel_platक्रमm_name(क्रमागत पूर्णांकel_platक्रमm platक्रमm);

व्योम पूर्णांकel_device_info_subplatक्रमm_init(काष्ठा drm_i915_निजी *dev_priv);
व्योम पूर्णांकel_device_info_runसमय_init(काष्ठा drm_i915_निजी *dev_priv);

व्योम पूर्णांकel_device_info_prपूर्णांक_अटल(स्थिर काष्ठा पूर्णांकel_device_info *info,
				    काष्ठा drm_prपूर्णांकer *p);
व्योम पूर्णांकel_device_info_prपूर्णांक_runसमय(स्थिर काष्ठा पूर्णांकel_runसमय_info *info,
				     काष्ठा drm_prपूर्णांकer *p);

व्योम पूर्णांकel_driver_caps_prपूर्णांक(स्थिर काष्ठा पूर्णांकel_driver_caps *caps,
			     काष्ठा drm_prपूर्णांकer *p);

#पूर्ण_अगर
