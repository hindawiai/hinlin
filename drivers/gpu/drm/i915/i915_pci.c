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

#समावेश <linux/console.h>
#समावेश <linux/vga_चयनeroo.h>

#समावेश <drm/drm_drv.h>
#समावेश <drm/i915_pciids.h>

#समावेश "display/intel_fbdev.h"

#समावेश "i915_drv.h"
#समावेश "i915_perf.h"
#समावेश "i915_globals.h"
#समावेश "i915_selftest.h"

#घोषणा PLATFORM(x) .platक्रमm = (x)
#घोषणा GEN(x) .gen = (x), .gen_mask = BIT((x) - 1), .display.version = (x)

#घोषणा I845_PIPE_OFFSETS \
	.pipe_offsets = अणु \
		[TRANSCODER_A] = PIPE_A_OFFSET,	\
	पूर्ण, \
	.trans_offsets = अणु \
		[TRANSCODER_A] = TRANSCODER_A_OFFSET, \
	पूर्ण

#घोषणा I9XX_PIPE_OFFSETS \
	.pipe_offsets = अणु \
		[TRANSCODER_A] = PIPE_A_OFFSET,	\
		[TRANSCODER_B] = PIPE_B_OFFSET, \
	पूर्ण, \
	.trans_offsets = अणु \
		[TRANSCODER_A] = TRANSCODER_A_OFFSET, \
		[TRANSCODER_B] = TRANSCODER_B_OFFSET, \
	पूर्ण

#घोषणा IVB_PIPE_OFFSETS \
	.pipe_offsets = अणु \
		[TRANSCODER_A] = PIPE_A_OFFSET,	\
		[TRANSCODER_B] = PIPE_B_OFFSET, \
		[TRANSCODER_C] = PIPE_C_OFFSET, \
	पूर्ण, \
	.trans_offsets = अणु \
		[TRANSCODER_A] = TRANSCODER_A_OFFSET, \
		[TRANSCODER_B] = TRANSCODER_B_OFFSET, \
		[TRANSCODER_C] = TRANSCODER_C_OFFSET, \
	पूर्ण

#घोषणा HSW_PIPE_OFFSETS \
	.pipe_offsets = अणु \
		[TRANSCODER_A] = PIPE_A_OFFSET,	\
		[TRANSCODER_B] = PIPE_B_OFFSET, \
		[TRANSCODER_C] = PIPE_C_OFFSET, \
		[TRANSCODER_EDP] = PIPE_EDP_OFFSET, \
	पूर्ण, \
	.trans_offsets = अणु \
		[TRANSCODER_A] = TRANSCODER_A_OFFSET, \
		[TRANSCODER_B] = TRANSCODER_B_OFFSET, \
		[TRANSCODER_C] = TRANSCODER_C_OFFSET, \
		[TRANSCODER_EDP] = TRANSCODER_EDP_OFFSET, \
	पूर्ण

#घोषणा CHV_PIPE_OFFSETS \
	.pipe_offsets = अणु \
		[TRANSCODER_A] = PIPE_A_OFFSET, \
		[TRANSCODER_B] = PIPE_B_OFFSET, \
		[TRANSCODER_C] = CHV_PIPE_C_OFFSET, \
	पूर्ण, \
	.trans_offsets = अणु \
		[TRANSCODER_A] = TRANSCODER_A_OFFSET, \
		[TRANSCODER_B] = TRANSCODER_B_OFFSET, \
		[TRANSCODER_C] = CHV_TRANSCODER_C_OFFSET, \
	पूर्ण

#घोषणा I845_CURSOR_OFFSETS \
	.cursor_offsets = अणु \
		[PIPE_A] = CURSOR_A_OFFSET, \
	पूर्ण

#घोषणा I9XX_CURSOR_OFFSETS \
	.cursor_offsets = अणु \
		[PIPE_A] = CURSOR_A_OFFSET, \
		[PIPE_B] = CURSOR_B_OFFSET, \
	पूर्ण

#घोषणा CHV_CURSOR_OFFSETS \
	.cursor_offsets = अणु \
		[PIPE_A] = CURSOR_A_OFFSET, \
		[PIPE_B] = CURSOR_B_OFFSET, \
		[PIPE_C] = CHV_CURSOR_C_OFFSET, \
	पूर्ण

#घोषणा IVB_CURSOR_OFFSETS \
	.cursor_offsets = अणु \
		[PIPE_A] = CURSOR_A_OFFSET, \
		[PIPE_B] = IVB_CURSOR_B_OFFSET, \
		[PIPE_C] = IVB_CURSOR_C_OFFSET, \
	पूर्ण

#घोषणा TGL_CURSOR_OFFSETS \
	.cursor_offsets = अणु \
		[PIPE_A] = CURSOR_A_OFFSET, \
		[PIPE_B] = IVB_CURSOR_B_OFFSET, \
		[PIPE_C] = IVB_CURSOR_C_OFFSET, \
		[PIPE_D] = TGL_CURSOR_D_OFFSET, \
	पूर्ण

#घोषणा I9XX_COLORS \
	.color = अणु .gamma_lut_size = 256 पूर्ण
#घोषणा I965_COLORS \
	.color = अणु .gamma_lut_size = 129, \
		   .gamma_lut_tests = DRM_COLOR_LUT_NON_DECREASING, \
	पूर्ण
#घोषणा ILK_COLORS \
	.color = अणु .gamma_lut_size = 1024 पूर्ण
#घोषणा IVB_COLORS \
	.color = अणु .degamma_lut_size = 1024, .gamma_lut_size = 1024 पूर्ण
#घोषणा CHV_COLORS \
	.color = अणु .degamma_lut_size = 65, .gamma_lut_size = 257, \
		   .degamma_lut_tests = DRM_COLOR_LUT_NON_DECREASING, \
		   .gamma_lut_tests = DRM_COLOR_LUT_NON_DECREASING, \
	पूर्ण
#घोषणा GLK_COLORS \
	.color = अणु .degamma_lut_size = 33, .gamma_lut_size = 1024, \
		   .degamma_lut_tests = DRM_COLOR_LUT_NON_DECREASING | \
					DRM_COLOR_LUT_EQUAL_CHANNELS, \
	पूर्ण

/* Keep in gen based order, and chronological order within a gen */

#घोषणा GEN_DEFAULT_PAGE_SIZES \
	.page_sizes = I915_GTT_PAGE_SIZE_4K

#घोषणा GEN_DEFAULT_REGIONS \
	.memory_regions = REGION_SMEM | REGION_STOLEN_SMEM

#घोषणा I830_FEATURES \
	GEN(2), \
	.is_mobile = 1, \
	.pipe_mask = BIT(PIPE_A) | BIT(PIPE_B), \
	.cpu_transcoder_mask = BIT(TRANSCODER_A) | BIT(TRANSCODER_B), \
	.display.has_overlay = 1, \
	.display.cursor_needs_physical = 1, \
	.display.overlay_needs_physical = 1, \
	.display.has_gmch = 1, \
	.gpu_reset_clobbers_display = true, \
	.hws_needs_physical = 1, \
	.unfenced_needs_alignment = 1, \
	.platक्रमm_engine_mask = BIT(RCS0), \
	.has_snoop = true, \
	.has_coherent_ggtt = false, \
	.dma_mask_size = 32, \
	I9XX_PIPE_OFFSETS, \
	I9XX_CURSOR_OFFSETS, \
	I9XX_COLORS, \
	GEN_DEFAULT_PAGE_SIZES, \
	GEN_DEFAULT_REGIONS

#घोषणा I845_FEATURES \
	GEN(2), \
	.pipe_mask = BIT(PIPE_A), \
	.cpu_transcoder_mask = BIT(TRANSCODER_A), \
	.display.has_overlay = 1, \
	.display.overlay_needs_physical = 1, \
	.display.has_gmch = 1, \
	.gpu_reset_clobbers_display = true, \
	.hws_needs_physical = 1, \
	.unfenced_needs_alignment = 1, \
	.platक्रमm_engine_mask = BIT(RCS0), \
	.has_snoop = true, \
	.has_coherent_ggtt = false, \
	.dma_mask_size = 32, \
	I845_PIPE_OFFSETS, \
	I845_CURSOR_OFFSETS, \
	I9XX_COLORS, \
	GEN_DEFAULT_PAGE_SIZES, \
	GEN_DEFAULT_REGIONS

अटल स्थिर काष्ठा पूर्णांकel_device_info i830_info = अणु
	I830_FEATURES,
	PLATFORM(INTEL_I830),
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_device_info i845g_info = अणु
	I845_FEATURES,
	PLATFORM(INTEL_I845G),
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_device_info i85x_info = अणु
	I830_FEATURES,
	PLATFORM(INTEL_I85X),
	.display.has_fbc = 1,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_device_info i865g_info = अणु
	I845_FEATURES,
	PLATFORM(INTEL_I865G),
	.display.has_fbc = 1,
पूर्ण;

#घोषणा GEN3_FEATURES \
	GEN(3), \
	.pipe_mask = BIT(PIPE_A) | BIT(PIPE_B), \
	.cpu_transcoder_mask = BIT(TRANSCODER_A) | BIT(TRANSCODER_B), \
	.display.has_gmch = 1, \
	.gpu_reset_clobbers_display = true, \
	.platक्रमm_engine_mask = BIT(RCS0), \
	.has_snoop = true, \
	.has_coherent_ggtt = true, \
	.dma_mask_size = 32, \
	I9XX_PIPE_OFFSETS, \
	I9XX_CURSOR_OFFSETS, \
	I9XX_COLORS, \
	GEN_DEFAULT_PAGE_SIZES, \
	GEN_DEFAULT_REGIONS

अटल स्थिर काष्ठा पूर्णांकel_device_info i915g_info = अणु
	GEN3_FEATURES,
	PLATFORM(INTEL_I915G),
	.has_coherent_ggtt = false,
	.display.cursor_needs_physical = 1,
	.display.has_overlay = 1,
	.display.overlay_needs_physical = 1,
	.hws_needs_physical = 1,
	.unfenced_needs_alignment = 1,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_device_info i915gm_info = अणु
	GEN3_FEATURES,
	PLATFORM(INTEL_I915GM),
	.is_mobile = 1,
	.display.cursor_needs_physical = 1,
	.display.has_overlay = 1,
	.display.overlay_needs_physical = 1,
	.display.supports_tv = 1,
	.display.has_fbc = 1,
	.hws_needs_physical = 1,
	.unfenced_needs_alignment = 1,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_device_info i945g_info = अणु
	GEN3_FEATURES,
	PLATFORM(INTEL_I945G),
	.display.has_hotplug = 1,
	.display.cursor_needs_physical = 1,
	.display.has_overlay = 1,
	.display.overlay_needs_physical = 1,
	.hws_needs_physical = 1,
	.unfenced_needs_alignment = 1,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_device_info i945gm_info = अणु
	GEN3_FEATURES,
	PLATFORM(INTEL_I945GM),
	.is_mobile = 1,
	.display.has_hotplug = 1,
	.display.cursor_needs_physical = 1,
	.display.has_overlay = 1,
	.display.overlay_needs_physical = 1,
	.display.supports_tv = 1,
	.display.has_fbc = 1,
	.hws_needs_physical = 1,
	.unfenced_needs_alignment = 1,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_device_info g33_info = अणु
	GEN3_FEATURES,
	PLATFORM(INTEL_G33),
	.display.has_hotplug = 1,
	.display.has_overlay = 1,
	.dma_mask_size = 36,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_device_info pnv_g_info = अणु
	GEN3_FEATURES,
	PLATFORM(INTEL_PINEVIEW),
	.display.has_hotplug = 1,
	.display.has_overlay = 1,
	.dma_mask_size = 36,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_device_info pnv_m_info = अणु
	GEN3_FEATURES,
	PLATFORM(INTEL_PINEVIEW),
	.is_mobile = 1,
	.display.has_hotplug = 1,
	.display.has_overlay = 1,
	.dma_mask_size = 36,
पूर्ण;

#घोषणा GEN4_FEATURES \
	GEN(4), \
	.pipe_mask = BIT(PIPE_A) | BIT(PIPE_B), \
	.cpu_transcoder_mask = BIT(TRANSCODER_A) | BIT(TRANSCODER_B), \
	.display.has_hotplug = 1, \
	.display.has_gmch = 1, \
	.gpu_reset_clobbers_display = true, \
	.platक्रमm_engine_mask = BIT(RCS0), \
	.has_snoop = true, \
	.has_coherent_ggtt = true, \
	.dma_mask_size = 36, \
	I9XX_PIPE_OFFSETS, \
	I9XX_CURSOR_OFFSETS, \
	I965_COLORS, \
	GEN_DEFAULT_PAGE_SIZES, \
	GEN_DEFAULT_REGIONS

अटल स्थिर काष्ठा पूर्णांकel_device_info i965g_info = अणु
	GEN4_FEATURES,
	PLATFORM(INTEL_I965G),
	.display.has_overlay = 1,
	.hws_needs_physical = 1,
	.has_snoop = false,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_device_info i965gm_info = अणु
	GEN4_FEATURES,
	PLATFORM(INTEL_I965GM),
	.is_mobile = 1,
	.display.has_fbc = 1,
	.display.has_overlay = 1,
	.display.supports_tv = 1,
	.hws_needs_physical = 1,
	.has_snoop = false,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_device_info g45_info = अणु
	GEN4_FEATURES,
	PLATFORM(INTEL_G45),
	.platक्रमm_engine_mask = BIT(RCS0) | BIT(VCS0),
	.gpu_reset_clobbers_display = false,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_device_info gm45_info = अणु
	GEN4_FEATURES,
	PLATFORM(INTEL_GM45),
	.is_mobile = 1,
	.display.has_fbc = 1,
	.display.supports_tv = 1,
	.platक्रमm_engine_mask = BIT(RCS0) | BIT(VCS0),
	.gpu_reset_clobbers_display = false,
पूर्ण;

#घोषणा GEN5_FEATURES \
	GEN(5), \
	.pipe_mask = BIT(PIPE_A) | BIT(PIPE_B), \
	.cpu_transcoder_mask = BIT(TRANSCODER_A) | BIT(TRANSCODER_B), \
	.display.has_hotplug = 1, \
	.platक्रमm_engine_mask = BIT(RCS0) | BIT(VCS0), \
	.has_snoop = true, \
	.has_coherent_ggtt = true, \
	/* ilk करोes support rc6, but we करो not implement [घातer] contexts */ \
	.has_rc6 = 0, \
	.dma_mask_size = 36, \
	I9XX_PIPE_OFFSETS, \
	I9XX_CURSOR_OFFSETS, \
	ILK_COLORS, \
	GEN_DEFAULT_PAGE_SIZES, \
	GEN_DEFAULT_REGIONS

अटल स्थिर काष्ठा पूर्णांकel_device_info ilk_d_info = अणु
	GEN5_FEATURES,
	PLATFORM(INTEL_IRONLAKE),
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_device_info ilk_m_info = अणु
	GEN5_FEATURES,
	PLATFORM(INTEL_IRONLAKE),
	.is_mobile = 1,
	.has_rps = true,
	.display.has_fbc = 1,
पूर्ण;

#घोषणा GEN6_FEATURES \
	GEN(6), \
	.pipe_mask = BIT(PIPE_A) | BIT(PIPE_B), \
	.cpu_transcoder_mask = BIT(TRANSCODER_A) | BIT(TRANSCODER_B), \
	.display.has_hotplug = 1, \
	.display.has_fbc = 1, \
	.platक्रमm_engine_mask = BIT(RCS0) | BIT(VCS0) | BIT(BCS0), \
	.has_coherent_ggtt = true, \
	.has_llc = 1, \
	.has_rc6 = 1, \
	.has_rc6p = 1, \
	.has_rps = true, \
	.dma_mask_size = 40, \
	.ppgtt_type = INTEL_PPGTT_ALIASING, \
	.ppgtt_size = 31, \
	I9XX_PIPE_OFFSETS, \
	I9XX_CURSOR_OFFSETS, \
	ILK_COLORS, \
	GEN_DEFAULT_PAGE_SIZES, \
	GEN_DEFAULT_REGIONS

#घोषणा SNB_D_PLATFORM \
	GEN6_FEATURES, \
	PLATFORM(INTEL_SANDYBRIDGE)

अटल स्थिर काष्ठा पूर्णांकel_device_info snb_d_gt1_info = अणु
	SNB_D_PLATFORM,
	.gt = 1,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_device_info snb_d_gt2_info = अणु
	SNB_D_PLATFORM,
	.gt = 2,
पूर्ण;

#घोषणा SNB_M_PLATFORM \
	GEN6_FEATURES, \
	PLATFORM(INTEL_SANDYBRIDGE), \
	.is_mobile = 1


अटल स्थिर काष्ठा पूर्णांकel_device_info snb_m_gt1_info = अणु
	SNB_M_PLATFORM,
	.gt = 1,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_device_info snb_m_gt2_info = अणु
	SNB_M_PLATFORM,
	.gt = 2,
पूर्ण;

#घोषणा GEN7_FEATURES  \
	GEN(7), \
	.pipe_mask = BIT(PIPE_A) | BIT(PIPE_B) | BIT(PIPE_C), \
	.cpu_transcoder_mask = BIT(TRANSCODER_A) | BIT(TRANSCODER_B) | BIT(TRANSCODER_C), \
	.display.has_hotplug = 1, \
	.display.has_fbc = 1, \
	.platक्रमm_engine_mask = BIT(RCS0) | BIT(VCS0) | BIT(BCS0), \
	.has_coherent_ggtt = true, \
	.has_llc = 1, \
	.has_rc6 = 1, \
	.has_rc6p = 1, \
	.has_reset_engine = true, \
	.has_rps = true, \
	.dma_mask_size = 40, \
	.ppgtt_type = INTEL_PPGTT_ALIASING, \
	.ppgtt_size = 31, \
	IVB_PIPE_OFFSETS, \
	IVB_CURSOR_OFFSETS, \
	IVB_COLORS, \
	GEN_DEFAULT_PAGE_SIZES, \
	GEN_DEFAULT_REGIONS

#घोषणा IVB_D_PLATFORM \
	GEN7_FEATURES, \
	PLATFORM(INTEL_IVYBRIDGE), \
	.has_l3_dpf = 1

अटल स्थिर काष्ठा पूर्णांकel_device_info ivb_d_gt1_info = अणु
	IVB_D_PLATFORM,
	.gt = 1,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_device_info ivb_d_gt2_info = अणु
	IVB_D_PLATFORM,
	.gt = 2,
पूर्ण;

#घोषणा IVB_M_PLATFORM \
	GEN7_FEATURES, \
	PLATFORM(INTEL_IVYBRIDGE), \
	.is_mobile = 1, \
	.has_l3_dpf = 1

अटल स्थिर काष्ठा पूर्णांकel_device_info ivb_m_gt1_info = अणु
	IVB_M_PLATFORM,
	.gt = 1,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_device_info ivb_m_gt2_info = अणु
	IVB_M_PLATFORM,
	.gt = 2,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_device_info ivb_q_info = अणु
	GEN7_FEATURES,
	PLATFORM(INTEL_IVYBRIDGE),
	.gt = 2,
	.pipe_mask = 0, /* legal, last one wins */
	.cpu_transcoder_mask = 0,
	.has_l3_dpf = 1,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_device_info vlv_info = अणु
	PLATFORM(INTEL_VALLEYVIEW),
	GEN(7),
	.is_lp = 1,
	.pipe_mask = BIT(PIPE_A) | BIT(PIPE_B),
	.cpu_transcoder_mask = BIT(TRANSCODER_A) | BIT(TRANSCODER_B),
	.has_runसमय_pm = 1,
	.has_rc6 = 1,
	.has_reset_engine = true,
	.has_rps = true,
	.display.has_gmch = 1,
	.display.has_hotplug = 1,
	.dma_mask_size = 40,
	.ppgtt_type = INTEL_PPGTT_ALIASING,
	.ppgtt_size = 31,
	.has_snoop = true,
	.has_coherent_ggtt = false,
	.platक्रमm_engine_mask = BIT(RCS0) | BIT(VCS0) | BIT(BCS0),
	.display_mmio_offset = VLV_DISPLAY_BASE,
	I9XX_PIPE_OFFSETS,
	I9XX_CURSOR_OFFSETS,
	I965_COLORS,
	GEN_DEFAULT_PAGE_SIZES,
	GEN_DEFAULT_REGIONS,
पूर्ण;

#घोषणा G75_FEATURES  \
	GEN7_FEATURES, \
	.platक्रमm_engine_mask = BIT(RCS0) | BIT(VCS0) | BIT(BCS0) | BIT(VECS0), \
	.cpu_transcoder_mask = BIT(TRANSCODER_A) | BIT(TRANSCODER_B) | \
		BIT(TRANSCODER_C) | BIT(TRANSCODER_EDP), \
	.display.has_ddi = 1, \
	.display.has_fpga_dbg = 1, \
	.display.has_psr = 1, \
	.display.has_psr_hw_tracking = 1, \
	.display.has_dp_mst = 1, \
	.has_rc6p = 0 /* RC6p हटाओd-by HSW */, \
	HSW_PIPE_OFFSETS, \
	.has_runसमय_pm = 1

#घोषणा HSW_PLATFORM \
	G75_FEATURES, \
	PLATFORM(INTEL_HASWELL), \
	.has_l3_dpf = 1

अटल स्थिर काष्ठा पूर्णांकel_device_info hsw_gt1_info = अणु
	HSW_PLATFORM,
	.gt = 1,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_device_info hsw_gt2_info = अणु
	HSW_PLATFORM,
	.gt = 2,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_device_info hsw_gt3_info = अणु
	HSW_PLATFORM,
	.gt = 3,
पूर्ण;

#घोषणा GEN8_FEATURES \
	G75_FEATURES, \
	GEN(8), \
	.has_logical_ring_contexts = 1, \
	.dma_mask_size = 39, \
	.ppgtt_type = INTEL_PPGTT_FULL, \
	.ppgtt_size = 48, \
	.has_64bit_reloc = 1

#घोषणा BDW_PLATFORM \
	GEN8_FEATURES, \
	PLATFORM(INTEL_BROADWELL)

अटल स्थिर काष्ठा पूर्णांकel_device_info bdw_gt1_info = अणु
	BDW_PLATFORM,
	.gt = 1,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_device_info bdw_gt2_info = अणु
	BDW_PLATFORM,
	.gt = 2,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_device_info bdw_rsvd_info = अणु
	BDW_PLATFORM,
	.gt = 3,
	/* According to the device ID those devices are GT3, they were
	 * previously treated as not GT3, keep it like that.
	 */
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_device_info bdw_gt3_info = अणु
	BDW_PLATFORM,
	.gt = 3,
	.platक्रमm_engine_mask =
		BIT(RCS0) | BIT(VCS0) | BIT(BCS0) | BIT(VECS0) | BIT(VCS1),
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_device_info chv_info = अणु
	PLATFORM(INTEL_CHERRYVIEW),
	GEN(8),
	.pipe_mask = BIT(PIPE_A) | BIT(PIPE_B) | BIT(PIPE_C),
	.cpu_transcoder_mask = BIT(TRANSCODER_A) | BIT(TRANSCODER_B) | BIT(TRANSCODER_C),
	.display.has_hotplug = 1,
	.is_lp = 1,
	.platक्रमm_engine_mask = BIT(RCS0) | BIT(VCS0) | BIT(BCS0) | BIT(VECS0),
	.has_64bit_reloc = 1,
	.has_runसमय_pm = 1,
	.has_rc6 = 1,
	.has_rps = true,
	.has_logical_ring_contexts = 1,
	.display.has_gmch = 1,
	.dma_mask_size = 39,
	.ppgtt_type = INTEL_PPGTT_FULL,
	.ppgtt_size = 32,
	.has_reset_engine = 1,
	.has_snoop = true,
	.has_coherent_ggtt = false,
	.display_mmio_offset = VLV_DISPLAY_BASE,
	CHV_PIPE_OFFSETS,
	CHV_CURSOR_OFFSETS,
	CHV_COLORS,
	GEN_DEFAULT_PAGE_SIZES,
	GEN_DEFAULT_REGIONS,
पूर्ण;

#घोषणा GEN9_DEFAULT_PAGE_SIZES \
	.page_sizes = I915_GTT_PAGE_SIZE_4K | \
		      I915_GTT_PAGE_SIZE_64K

#घोषणा GEN9_FEATURES \
	GEN8_FEATURES, \
	GEN(9), \
	GEN9_DEFAULT_PAGE_SIZES, \
	.display.has_csr = 1, \
	.has_gt_uc = 1, \
	.display.has_hdcp = 1, \
	.display.has_ipc = 1, \
	.ddb_size = 896, \
	.num_supported_dbuf_slices = 1

#घोषणा SKL_PLATFORM \
	GEN9_FEATURES, \
	PLATFORM(INTEL_SKYLAKE)

अटल स्थिर काष्ठा पूर्णांकel_device_info skl_gt1_info = अणु
	SKL_PLATFORM,
	.gt = 1,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_device_info skl_gt2_info = अणु
	SKL_PLATFORM,
	.gt = 2,
पूर्ण;

#घोषणा SKL_GT3_PLUS_PLATFORM \
	SKL_PLATFORM, \
	.platक्रमm_engine_mask = \
		BIT(RCS0) | BIT(VCS0) | BIT(BCS0) | BIT(VECS0) | BIT(VCS1)


अटल स्थिर काष्ठा पूर्णांकel_device_info skl_gt3_info = अणु
	SKL_GT3_PLUS_PLATFORM,
	.gt = 3,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_device_info skl_gt4_info = अणु
	SKL_GT3_PLUS_PLATFORM,
	.gt = 4,
पूर्ण;

#घोषणा GEN9_LP_FEATURES \
	GEN(9), \
	.is_lp = 1, \
	.num_supported_dbuf_slices = 1, \
	.display.has_hotplug = 1, \
	.platक्रमm_engine_mask = BIT(RCS0) | BIT(VCS0) | BIT(BCS0) | BIT(VECS0), \
	.pipe_mask = BIT(PIPE_A) | BIT(PIPE_B) | BIT(PIPE_C), \
	.cpu_transcoder_mask = BIT(TRANSCODER_A) | BIT(TRANSCODER_B) | \
		BIT(TRANSCODER_C) | BIT(TRANSCODER_EDP) | \
		BIT(TRANSCODER_DSI_A) | BIT(TRANSCODER_DSI_C), \
	.has_64bit_reloc = 1, \
	.display.has_ddi = 1, \
	.display.has_fpga_dbg = 1, \
	.display.has_fbc = 1, \
	.display.has_hdcp = 1, \
	.display.has_psr = 1, \
	.display.has_psr_hw_tracking = 1, \
	.has_runसमय_pm = 1, \
	.display.has_csr = 1, \
	.has_rc6 = 1, \
	.has_rps = true, \
	.display.has_dp_mst = 1, \
	.has_logical_ring_contexts = 1, \
	.has_gt_uc = 1, \
	.dma_mask_size = 39, \
	.ppgtt_type = INTEL_PPGTT_FULL, \
	.ppgtt_size = 48, \
	.has_reset_engine = 1, \
	.has_snoop = true, \
	.has_coherent_ggtt = false, \
	.display.has_ipc = 1, \
	HSW_PIPE_OFFSETS, \
	IVB_CURSOR_OFFSETS, \
	IVB_COLORS, \
	GEN9_DEFAULT_PAGE_SIZES, \
	GEN_DEFAULT_REGIONS

अटल स्थिर काष्ठा पूर्णांकel_device_info bxt_info = अणु
	GEN9_LP_FEATURES,
	PLATFORM(INTEL_BROXTON),
	.ddb_size = 512,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_device_info glk_info = अणु
	GEN9_LP_FEATURES,
	PLATFORM(INTEL_GEMINILAKE),
	.display.version = 10,
	.ddb_size = 1024,
	GLK_COLORS,
पूर्ण;

#घोषणा KBL_PLATFORM \
	GEN9_FEATURES, \
	PLATFORM(INTEL_KABYLAKE)

अटल स्थिर काष्ठा पूर्णांकel_device_info kbl_gt1_info = अणु
	KBL_PLATFORM,
	.gt = 1,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_device_info kbl_gt2_info = अणु
	KBL_PLATFORM,
	.gt = 2,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_device_info kbl_gt3_info = अणु
	KBL_PLATFORM,
	.gt = 3,
	.platक्रमm_engine_mask =
		BIT(RCS0) | BIT(VCS0) | BIT(BCS0) | BIT(VECS0) | BIT(VCS1),
पूर्ण;

#घोषणा CFL_PLATFORM \
	GEN9_FEATURES, \
	PLATFORM(INTEL_COFFEELAKE)

अटल स्थिर काष्ठा पूर्णांकel_device_info cfl_gt1_info = अणु
	CFL_PLATFORM,
	.gt = 1,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_device_info cfl_gt2_info = अणु
	CFL_PLATFORM,
	.gt = 2,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_device_info cfl_gt3_info = अणु
	CFL_PLATFORM,
	.gt = 3,
	.platक्रमm_engine_mask =
		BIT(RCS0) | BIT(VCS0) | BIT(BCS0) | BIT(VECS0) | BIT(VCS1),
पूर्ण;

#घोषणा CML_PLATFORM \
	GEN9_FEATURES, \
	PLATFORM(INTEL_COMETLAKE)

अटल स्थिर काष्ठा पूर्णांकel_device_info cml_gt1_info = अणु
	CML_PLATFORM,
	.gt = 1,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_device_info cml_gt2_info = अणु
	CML_PLATFORM,
	.gt = 2,
पूर्ण;

#घोषणा GEN10_FEATURES \
	GEN9_FEATURES, \
	GEN(10), \
	.ddb_size = 1024, \
	.display.has_dsc = 1, \
	.has_coherent_ggtt = false, \
	GLK_COLORS

अटल स्थिर काष्ठा पूर्णांकel_device_info cnl_info = अणु
	GEN10_FEATURES,
	PLATFORM(INTEL_CANNONLAKE),
	.gt = 2,
पूर्ण;

#घोषणा GEN11_DEFAULT_PAGE_SIZES \
	.page_sizes = I915_GTT_PAGE_SIZE_4K | \
		      I915_GTT_PAGE_SIZE_64K | \
		      I915_GTT_PAGE_SIZE_2M

#घोषणा GEN11_FEATURES \
	GEN10_FEATURES, \
	GEN11_DEFAULT_PAGE_SIZES, \
	.abox_mask = BIT(0), \
	.cpu_transcoder_mask = BIT(TRANSCODER_A) | BIT(TRANSCODER_B) | \
		BIT(TRANSCODER_C) | BIT(TRANSCODER_EDP) | \
		BIT(TRANSCODER_DSI_0) | BIT(TRANSCODER_DSI_1), \
	.pipe_offsets = अणु \
		[TRANSCODER_A] = PIPE_A_OFFSET, \
		[TRANSCODER_B] = PIPE_B_OFFSET, \
		[TRANSCODER_C] = PIPE_C_OFFSET, \
		[TRANSCODER_EDP] = PIPE_EDP_OFFSET, \
		[TRANSCODER_DSI_0] = PIPE_DSI0_OFFSET, \
		[TRANSCODER_DSI_1] = PIPE_DSI1_OFFSET, \
	पूर्ण, \
	.trans_offsets = अणु \
		[TRANSCODER_A] = TRANSCODER_A_OFFSET, \
		[TRANSCODER_B] = TRANSCODER_B_OFFSET, \
		[TRANSCODER_C] = TRANSCODER_C_OFFSET, \
		[TRANSCODER_EDP] = TRANSCODER_EDP_OFFSET, \
		[TRANSCODER_DSI_0] = TRANSCODER_DSI0_OFFSET, \
		[TRANSCODER_DSI_1] = TRANSCODER_DSI1_OFFSET, \
	पूर्ण, \
	GEN(11), \
	.ddb_size = 2048, \
	.num_supported_dbuf_slices = 2, \
	.has_logical_ring_elsq = 1, \
	.color = अणु .degamma_lut_size = 33, .gamma_lut_size = 262145 पूर्ण

अटल स्थिर काष्ठा पूर्णांकel_device_info icl_info = अणु
	GEN11_FEATURES,
	PLATFORM(INTEL_ICELAKE),
	.platक्रमm_engine_mask =
		BIT(RCS0) | BIT(BCS0) | BIT(VECS0) | BIT(VCS0) | BIT(VCS2),
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_device_info ehl_info = अणु
	GEN11_FEATURES,
	PLATFORM(INTEL_ELKHARTLAKE),
	.require_क्रमce_probe = 1,
	.platक्रमm_engine_mask = BIT(RCS0) | BIT(BCS0) | BIT(VCS0) | BIT(VECS0),
	.ppgtt_size = 36,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_device_info jsl_info = अणु
	GEN11_FEATURES,
	PLATFORM(INTEL_JASPERLAKE),
	.require_क्रमce_probe = 1,
	.platक्रमm_engine_mask = BIT(RCS0) | BIT(BCS0) | BIT(VCS0) | BIT(VECS0),
	.ppgtt_size = 36,
पूर्ण;

#घोषणा GEN12_FEATURES \
	GEN11_FEATURES, \
	GEN(12), \
	.abox_mask = GENMASK(2, 1), \
	.pipe_mask = BIT(PIPE_A) | BIT(PIPE_B) | BIT(PIPE_C) | BIT(PIPE_D), \
	.cpu_transcoder_mask = BIT(TRANSCODER_A) | BIT(TRANSCODER_B) | \
		BIT(TRANSCODER_C) | BIT(TRANSCODER_D) | \
		BIT(TRANSCODER_DSI_0) | BIT(TRANSCODER_DSI_1), \
	.pipe_offsets = अणु \
		[TRANSCODER_A] = PIPE_A_OFFSET, \
		[TRANSCODER_B] = PIPE_B_OFFSET, \
		[TRANSCODER_C] = PIPE_C_OFFSET, \
		[TRANSCODER_D] = PIPE_D_OFFSET, \
		[TRANSCODER_DSI_0] = PIPE_DSI0_OFFSET, \
		[TRANSCODER_DSI_1] = PIPE_DSI1_OFFSET, \
	पूर्ण, \
	.trans_offsets = अणु \
		[TRANSCODER_A] = TRANSCODER_A_OFFSET, \
		[TRANSCODER_B] = TRANSCODER_B_OFFSET, \
		[TRANSCODER_C] = TRANSCODER_C_OFFSET, \
		[TRANSCODER_D] = TRANSCODER_D_OFFSET, \
		[TRANSCODER_DSI_0] = TRANSCODER_DSI0_OFFSET, \
		[TRANSCODER_DSI_1] = TRANSCODER_DSI1_OFFSET, \
	पूर्ण, \
	TGL_CURSOR_OFFSETS, \
	.has_global_mocs = 1, \
	.display.has_dsb = 1

अटल स्थिर काष्ठा पूर्णांकel_device_info tgl_info = अणु
	GEN12_FEATURES,
	PLATFORM(INTEL_TIGERLAKE),
	.display.has_modular_fia = 1,
	.platक्रमm_engine_mask =
		BIT(RCS0) | BIT(BCS0) | BIT(VECS0) | BIT(VCS0) | BIT(VCS2),
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_device_info rkl_info = अणु
	GEN12_FEATURES,
	PLATFORM(INTEL_ROCKETLAKE),
	.abox_mask = BIT(0),
	.pipe_mask = BIT(PIPE_A) | BIT(PIPE_B) | BIT(PIPE_C),
	.cpu_transcoder_mask = BIT(TRANSCODER_A) | BIT(TRANSCODER_B) |
		BIT(TRANSCODER_C),
	.display.has_hti = 1,
	.display.has_psr_hw_tracking = 0,
	.platक्रमm_engine_mask =
		BIT(RCS0) | BIT(BCS0) | BIT(VECS0) | BIT(VCS0),
पूर्ण;

#घोषणा GEN12_DGFX_FEATURES \
	GEN12_FEATURES, \
	.memory_regions = REGION_SMEM | REGION_LMEM, \
	.has_master_unit_irq = 1, \
	.has_llc = 0, \
	.has_snoop = 1, \
	.is_dgfx = 1

अटल स्थिर काष्ठा पूर्णांकel_device_info dg1_info __maybe_unused = अणु
	GEN12_DGFX_FEATURES,
	PLATFORM(INTEL_DG1),
	.pipe_mask = BIT(PIPE_A) | BIT(PIPE_B) | BIT(PIPE_C) | BIT(PIPE_D),
	.require_क्रमce_probe = 1,
	.platक्रमm_engine_mask =
		BIT(RCS0) | BIT(BCS0) | BIT(VECS0) |
		BIT(VCS0) | BIT(VCS2),
	/* Wa_16011227922 */
	.ppgtt_size = 47,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_device_info adl_s_info = अणु
	GEN12_FEATURES,
	PLATFORM(INTEL_ALDERLAKE_S),
	.pipe_mask = BIT(PIPE_A) | BIT(PIPE_B) | BIT(PIPE_C) | BIT(PIPE_D),
	.require_क्रमce_probe = 1,
	.display.has_hti = 1,
	.display.has_psr_hw_tracking = 0,
	.platक्रमm_engine_mask =
		BIT(RCS0) | BIT(BCS0) | BIT(VECS0) | BIT(VCS0) | BIT(VCS2),
	.dma_mask_size = 46,
पूर्ण;

#अघोषित GEN
#अघोषित PLATFORM

/*
 * Make sure any device matches here are from most specअगरic to most
 * general.  For example, since the Quanta match is based on the subप्रणाली
 * and subvenकरोr IDs, we need it to come beक्रमe the more general IVB
 * PCI ID matches, otherwise we'll use the wrong info काष्ठा above.
 */
अटल स्थिर काष्ठा pci_device_id pciidlist[] = अणु
	INTEL_I830_IDS(&i830_info),
	INTEL_I845G_IDS(&i845g_info),
	INTEL_I85X_IDS(&i85x_info),
	INTEL_I865G_IDS(&i865g_info),
	INTEL_I915G_IDS(&i915g_info),
	INTEL_I915GM_IDS(&i915gm_info),
	INTEL_I945G_IDS(&i945g_info),
	INTEL_I945GM_IDS(&i945gm_info),
	INTEL_I965G_IDS(&i965g_info),
	INTEL_G33_IDS(&g33_info),
	INTEL_I965GM_IDS(&i965gm_info),
	INTEL_GM45_IDS(&gm45_info),
	INTEL_G45_IDS(&g45_info),
	INTEL_PINEVIEW_G_IDS(&pnv_g_info),
	INTEL_PINEVIEW_M_IDS(&pnv_m_info),
	INTEL_IRONLAKE_D_IDS(&ilk_d_info),
	INTEL_IRONLAKE_M_IDS(&ilk_m_info),
	INTEL_SNB_D_GT1_IDS(&snb_d_gt1_info),
	INTEL_SNB_D_GT2_IDS(&snb_d_gt2_info),
	INTEL_SNB_M_GT1_IDS(&snb_m_gt1_info),
	INTEL_SNB_M_GT2_IDS(&snb_m_gt2_info),
	INTEL_IVB_Q_IDS(&ivb_q_info), /* must be first IVB */
	INTEL_IVB_M_GT1_IDS(&ivb_m_gt1_info),
	INTEL_IVB_M_GT2_IDS(&ivb_m_gt2_info),
	INTEL_IVB_D_GT1_IDS(&ivb_d_gt1_info),
	INTEL_IVB_D_GT2_IDS(&ivb_d_gt2_info),
	INTEL_HSW_GT1_IDS(&hsw_gt1_info),
	INTEL_HSW_GT2_IDS(&hsw_gt2_info),
	INTEL_HSW_GT3_IDS(&hsw_gt3_info),
	INTEL_VLV_IDS(&vlv_info),
	INTEL_BDW_GT1_IDS(&bdw_gt1_info),
	INTEL_BDW_GT2_IDS(&bdw_gt2_info),
	INTEL_BDW_GT3_IDS(&bdw_gt3_info),
	INTEL_BDW_RSVD_IDS(&bdw_rsvd_info),
	INTEL_CHV_IDS(&chv_info),
	INTEL_SKL_GT1_IDS(&skl_gt1_info),
	INTEL_SKL_GT2_IDS(&skl_gt2_info),
	INTEL_SKL_GT3_IDS(&skl_gt3_info),
	INTEL_SKL_GT4_IDS(&skl_gt4_info),
	INTEL_BXT_IDS(&bxt_info),
	INTEL_GLK_IDS(&glk_info),
	INTEL_KBL_GT1_IDS(&kbl_gt1_info),
	INTEL_KBL_GT2_IDS(&kbl_gt2_info),
	INTEL_KBL_GT3_IDS(&kbl_gt3_info),
	INTEL_KBL_GT4_IDS(&kbl_gt3_info),
	INTEL_AML_KBL_GT2_IDS(&kbl_gt2_info),
	INTEL_CFL_S_GT1_IDS(&cfl_gt1_info),
	INTEL_CFL_S_GT2_IDS(&cfl_gt2_info),
	INTEL_CFL_H_GT1_IDS(&cfl_gt1_info),
	INTEL_CFL_H_GT2_IDS(&cfl_gt2_info),
	INTEL_CFL_U_GT2_IDS(&cfl_gt2_info),
	INTEL_CFL_U_GT3_IDS(&cfl_gt3_info),
	INTEL_WHL_U_GT1_IDS(&cfl_gt1_info),
	INTEL_WHL_U_GT2_IDS(&cfl_gt2_info),
	INTEL_AML_CFL_GT2_IDS(&cfl_gt2_info),
	INTEL_WHL_U_GT3_IDS(&cfl_gt3_info),
	INTEL_CML_GT1_IDS(&cml_gt1_info),
	INTEL_CML_GT2_IDS(&cml_gt2_info),
	INTEL_CML_U_GT1_IDS(&cml_gt1_info),
	INTEL_CML_U_GT2_IDS(&cml_gt2_info),
	INTEL_CNL_IDS(&cnl_info),
	INTEL_ICL_11_IDS(&icl_info),
	INTEL_EHL_IDS(&ehl_info),
	INTEL_JSL_IDS(&jsl_info),
	INTEL_TGL_12_IDS(&tgl_info),
	INTEL_RKL_IDS(&rkl_info),
	INTEL_ADLS_IDS(&adl_s_info),
	अणु0, 0, 0पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, pciidlist);

अटल व्योम i915_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा drm_i915_निजी *i915;

	i915 = pci_get_drvdata(pdev);
	अगर (!i915) /* driver load पातed, nothing to cleanup */
		वापस;

	i915_driver_हटाओ(i915);
	pci_set_drvdata(pdev, शून्य);
पूर्ण

/* is device_id present in comma separated list of ids */
अटल bool क्रमce_probe(u16 device_id, स्थिर अक्षर *devices)
अणु
	अक्षर *s, *p, *tok;
	bool ret;

	अगर (!devices || !*devices)
		वापस false;

	/* match everything */
	अगर (म_भेद(devices, "*") == 0)
		वापस true;

	s = kstrdup(devices, GFP_KERNEL);
	अगर (!s)
		वापस false;

	क्रम (p = s, ret = false; (tok = strsep(&p, ",")) != शून्य; ) अणु
		u16 val;

		अगर (kstrtou16(tok, 16, &val) == 0 && val == device_id) अणु
			ret = true;
			अवरोध;
		पूर्ण
	पूर्ण

	kमुक्त(s);

	वापस ret;
पूर्ण

अटल पूर्णांक i915_pci_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा पूर्णांकel_device_info *पूर्णांकel_info =
		(काष्ठा पूर्णांकel_device_info *) ent->driver_data;
	पूर्णांक err;

	अगर (पूर्णांकel_info->require_क्रमce_probe &&
	    !क्रमce_probe(pdev->device, i915_modparams.क्रमce_probe)) अणु
		dev_info(&pdev->dev,
			 "Your graphics device %04x is not properly supported by the driver in this\n"
			 "kernel version. To force driver probe anyway, use i915.force_probe=%04x\n"
			 "module parameter or CONFIG_DRM_I915_FORCE_PROBE=%04x configuration option,\n"
			 "or (recommended) check for kernel updates.\n",
			 pdev->device, pdev->device, pdev->device);
		वापस -ENODEV;
	पूर्ण

	/* Only bind to function 0 of the device. Early generations
	 * used function 1 as a placeholder क्रम multi-head. This causes
	 * us confusion instead, especially on the प्रणालीs where both
	 * functions have the same PCI-ID!
	 */
	अगर (PCI_FUNC(pdev->devfn))
		वापस -ENODEV;

	/*
	 * apple-gmux is needed on dual GPU MacBook Pro
	 * to probe the panel अगर we're the inactive GPU.
	 */
	अगर (vga_चयनeroo_client_probe_defer(pdev))
		वापस -EPROBE_DEFER;

	err = i915_driver_probe(pdev, ent);
	अगर (err)
		वापस err;

	अगर (i915_inject_probe_failure(pci_get_drvdata(pdev))) अणु
		i915_pci_हटाओ(pdev);
		वापस -ENODEV;
	पूर्ण

	err = i915_live_selftests(pdev);
	अगर (err) अणु
		i915_pci_हटाओ(pdev);
		वापस err > 0 ? -ENOTTY : err;
	पूर्ण

	err = i915_perf_selftests(pdev);
	अगर (err) अणु
		i915_pci_हटाओ(pdev);
		वापस err > 0 ? -ENOTTY : err;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम i915_pci_shutकरोwn(काष्ठा pci_dev *pdev)
अणु
	काष्ठा drm_i915_निजी *i915 = pci_get_drvdata(pdev);

	i915_driver_shutकरोwn(i915);
पूर्ण

अटल काष्ठा pci_driver i915_pci_driver = अणु
	.name = DRIVER_NAME,
	.id_table = pciidlist,
	.probe = i915_pci_probe,
	.हटाओ = i915_pci_हटाओ,
	.shutकरोwn = i915_pci_shutकरोwn,
	.driver.pm = &i915_pm_ops,
पूर्ण;

अटल पूर्णांक __init i915_init(व्योम)
अणु
	bool use_kms = true;
	पूर्णांक err;

	err = i915_globals_init();
	अगर (err)
		वापस err;

	err = i915_mock_selftests();
	अगर (err)
		वापस err > 0 ? 0 : err;

	/*
	 * Enable KMS by शेष, unless explicitly overriden by
	 * either the i915.modeset prarameter or by the
	 * vga_text_mode_क्रमce boot option.
	 */

	अगर (i915_modparams.modeset == 0)
		use_kms = false;

	अगर (vgacon_text_क्रमce() && i915_modparams.modeset == -1)
		use_kms = false;

	अगर (!use_kms) अणु
		/* Silently fail loading to not upset userspace. */
		DRM_DEBUG_DRIVER("KMS disabled.\n");
		वापस 0;
	पूर्ण

	i915_pmu_init();

	err = pci_रेजिस्टर_driver(&i915_pci_driver);
	अगर (err) अणु
		i915_pmu_निकास();
		वापस err;
	पूर्ण

	i915_perf_sysctl_रेजिस्टर();
	वापस 0;
पूर्ण

अटल व्योम __निकास i915_निकास(व्योम)
अणु
	अगर (!i915_pci_driver.driver.owner)
		वापस;

	i915_perf_sysctl_unरेजिस्टर();
	pci_unरेजिस्टर_driver(&i915_pci_driver);
	i915_globals_निकास();
	i915_pmu_निकास();
पूर्ण

module_init(i915_init);
module_निकास(i915_निकास);

MODULE_AUTHOR("Tungsten Graphics, Inc.");
MODULE_AUTHOR("Intel Corporation");

MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL and additional rights");
