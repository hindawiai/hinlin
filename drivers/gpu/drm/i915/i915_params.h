<शैली गुरु>
/*
 * Copyright तऊ 2015 Intel Corporation
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

#अगर_अघोषित _I915_PARAMS_H_
#घोषणा _I915_PARAMS_H_

#समावेश <linux/bitops.h>
#समावेश <linux/cache.h> /* क्रम __पढ़ो_mostly */

काष्ठा drm_prपूर्णांकer;

#घोषणा ENABLE_GUC_SUBMISSION		BIT(0)
#घोषणा ENABLE_GUC_LOAD_HUC		BIT(1)
#घोषणा ENABLE_GUC_MASK			GENMASK(1, 0)

/*
 * Invoke param, a function-like macro, क्रम each i915 param, with arguments:
 *
 * param(type, name, value, mode)
 *
 * type: parameter type, one of अणुbool, पूर्णांक, अचिन्हित पूर्णांक, अचिन्हित दीर्घ, अक्षर *पूर्ण
 * name: name of the parameter
 * value: initial/शेष value of the parameter
 * mode: debugfs file permissions, one of अणु0400, 0600, 0पूर्ण, use 0 to not create
 *       debugfs file
 */
#घोषणा I915_PARAMS_FOR_EACH(param) \
	param(अक्षर *, vbt_firmware, शून्य, 0400) \
	param(पूर्णांक, modeset, -1, 0400) \
	param(पूर्णांक, lvds_channel_mode, 0, 0400) \
	param(पूर्णांक, panel_use_ssc, -1, 0600) \
	param(पूर्णांक, vbt_sdvo_panel_type, -1, 0400) \
	param(पूर्णांक, enable_dc, -1, 0400) \
	param(पूर्णांक, enable_fbc, -1, 0600) \
	param(पूर्णांक, enable_psr, -1, 0600) \
	param(bool, psr_safest_params, false, 0400) \
	param(bool, enable_psr2_sel_fetch, false, 0400) \
	param(पूर्णांक, disable_घातer_well, -1, 0400) \
	param(पूर्णांक, enable_ips, 1, 0600) \
	param(पूर्णांक, invert_brightness, 0, 0600) \
	param(पूर्णांक, enable_guc, 0, 0400) \
	param(पूर्णांक, guc_log_level, -1, 0400) \
	param(अक्षर *, guc_firmware_path, शून्य, 0400) \
	param(अक्षर *, huc_firmware_path, शून्य, 0400) \
	param(अक्षर *, dmc_firmware_path, शून्य, 0400) \
	param(पूर्णांक, mmio_debug, -IS_ENABLED(CONFIG_DRM_I915_DEBUG_MMIO), 0600) \
	param(पूर्णांक, edp_vswing, 0, 0400) \
	param(अचिन्हित पूर्णांक, reset, 3, 0600) \
	param(अचिन्हित पूर्णांक, inject_probe_failure, 0, 0) \
	param(पूर्णांक, fastboot, -1, 0600) \
	param(पूर्णांक, enable_dpcd_backlight, -1, 0600) \
	param(अक्षर *, क्रमce_probe, CONFIG_DRM_I915_FORCE_PROBE, 0400) \
	param(अचिन्हित दीर्घ, fake_lmem_start, 0, 0400) \
	param(अचिन्हित पूर्णांक, request_समयout_ms, CONFIG_DRM_I915_REQUEST_TIMEOUT, 0600) \
	/* leave bools at the end to not create holes */ \
	param(bool, enable_hangcheck, true, 0600) \
	param(bool, load_detect_test, false, 0600) \
	param(bool, क्रमce_reset_modeset_test, false, 0600) \
	param(bool, error_capture, true, 0600) \
	param(bool, disable_display, false, 0400) \
	param(bool, verbose_state_checks, true, 0) \
	param(bool, nuclear_pageflip, false, 0400) \
	param(bool, enable_dp_mst, true, 0600) \
	param(bool, enable_gvt, false, 0400)

#घोषणा MEMBER(T, member, ...) T member;
काष्ठा i915_params अणु
	I915_PARAMS_FOR_EACH(MEMBER);
पूर्ण;
#अघोषित MEMBER

बाह्य काष्ठा i915_params i915_modparams __पढ़ो_mostly;

व्योम i915_params_dump(स्थिर काष्ठा i915_params *params, काष्ठा drm_prपूर्णांकer *p);
व्योम i915_params_copy(काष्ठा i915_params *dest, स्थिर काष्ठा i915_params *src);
व्योम i915_params_मुक्त(काष्ठा i915_params *params);

#पूर्ण_अगर

