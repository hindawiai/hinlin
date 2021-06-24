<शैली गुरु>
/*
 * Copyright तऊ 2014 Intel Corporation
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modअगरy, merge, publish,
 * distribute, sub license, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#समावेश <drm/drm_prपूर्णांक.h>

#समावेश "i915_params.h"
#समावेश "i915_drv.h"

#घोषणा i915_param_named(name, T, perm, desc) \
	module_param_named(name, i915_modparams.name, T, perm); \
	MODULE_PARM_DESC(name, desc)
#घोषणा i915_param_named_unsafe(name, T, perm, desc) \
	module_param_named_unsafe(name, i915_modparams.name, T, perm); \
	MODULE_PARM_DESC(name, desc)

काष्ठा i915_params i915_modparams __पढ़ो_mostly = अणु
#घोषणा MEMBER(T, member, value, ...) .member = (value),
	I915_PARAMS_FOR_EACH(MEMBER)
#अघोषित MEMBER
पूर्ण;

/*
 * Note: As a rule, keep module parameter sysfs permissions पढ़ो-only
 * 0400. Runसमय changes are only supported through i915 debugfs.
 *
 * For any exceptions requiring ग_लिखो access and runसमय changes through module
 * parameter sysfs, prevent debugfs file creation by setting the parameter's
 * debugfs mode to 0.
 */

i915_param_named(modeset, पूर्णांक, 0400,
	"Use kernel modesetting [KMS] (0=disable, "
	"1=on, -1=force vga console preference [default])");

i915_param_named_unsafe(enable_dc, पूर्णांक, 0400,
	"Enable power-saving display C-states. "
	"(-1=auto [default]; 0=disable; 1=up to DC5; 2=up to DC6; "
	"3=up to DC5 with DC3CO; 4=up to DC6 with DC3CO)");

i915_param_named_unsafe(enable_fbc, पूर्णांक, 0400,
	"Enable frame buffer compression for power savings "
	"(default: -1 (use per-chip default))");

i915_param_named_unsafe(lvds_channel_mode, पूर्णांक, 0400,
	 "Specify LVDS channel mode "
	 "(0=probe BIOS [default], 1=single-channel, 2=dual-channel)");

i915_param_named_unsafe(panel_use_ssc, पूर्णांक, 0400,
	"Use Spread Spectrum Clock with panels [LVDS/eDP] "
	"(default: auto from VBT)");

i915_param_named_unsafe(vbt_sdvo_panel_type, पूर्णांक, 0400,
	"Override/Ignore selection of SDVO panel mode in the VBT "
	"(-2=ignore, -1=auto [default], index in VBT BIOS table)");

i915_param_named_unsafe(reset, uपूर्णांक, 0400,
	"Attempt GPU resets (0=disabled, 1=full gpu reset, 2=engine reset [default])");

i915_param_named_unsafe(vbt_firmware, अक्षरp, 0400,
	"Load VBT from specified file under /lib/firmware");

#अगर IS_ENABLED(CONFIG_DRM_I915_CAPTURE_ERROR)
i915_param_named(error_capture, bool, 0400,
	"Record the GPU state following a hang. "
	"This information in /sys/class/drm/card<N>/error is vital for "
	"triaging and debugging hangs.");
#पूर्ण_अगर

i915_param_named_unsafe(enable_hangcheck, bool, 0400,
	"Periodically check GPU activity for detecting hangs. "
	"WARNING: Disabling this can cause system wide hangs. "
	"(default: true)");

i915_param_named_unsafe(enable_psr, पूर्णांक, 0400,
	"Enable PSR "
	"(0=disabled, 1=enabled) "
	"Default: -1 (use per-chip default)");

i915_param_named(psr_safest_params, bool, 0400,
	"Replace PSR VBT parameters by the safest and not optimal ones. This "
	"is helpful to detect if PSR issues are related to bad values set in "
	" VBT. (0=use VBT parameters, 1=use safest parameters)");

i915_param_named_unsafe(enable_psr2_sel_fetch, bool, 0400,
	"Enable PSR2 selective fetch "
	"(0=disabled, 1=enabled) "
	"Default: 0");

i915_param_named_unsafe(क्रमce_probe, अक्षरp, 0400,
	"Force probe the driver for specified devices. "
	"See CONFIG_DRM_I915_FORCE_PROBE for details.");

i915_param_named_unsafe(disable_घातer_well, पूर्णांक, 0400,
	"Disable display power wells when possible "
	"(-1=auto [default], 0=power wells always on, 1=power wells disabled when possible)");

i915_param_named_unsafe(enable_ips, पूर्णांक, 0400, "Enable IPS (default: true)");

i915_param_named(fastboot, पूर्णांक, 0400,
	"Try to skip unnecessary mode sets at boot time "
	"(0=disabled, 1=enabled) "
	"Default: -1 (use per-chip default)");

i915_param_named_unsafe(load_detect_test, bool, 0400,
	"Force-enable the VGA load detect code for testing (default:false). "
	"For developers only.");

i915_param_named_unsafe(क्रमce_reset_modeset_test, bool, 0400,
	"Force a modeset during gpu reset for testing (default:false). "
	"For developers only.");

i915_param_named_unsafe(invert_brightness, पूर्णांक, 0400,
	"Invert backlight brightness "
	"(-1 force normal, 0 machine defaults, 1 force inversion), please "
	"report PCI device ID, subsystem vendor and subsystem device ID "
	"to dri-devel@lists.freedesktop.org, if your machine needs it. "
	"It will then be included in an upcoming module version.");

i915_param_named(disable_display, bool, 0400,
	"Disable display (default: false)");

i915_param_named(mmio_debug, पूर्णांक, 0400,
	"Enable the MMIO debug code for the first N failures (default: off). "
	"This may negatively affect performance.");

/* Special हाल writable file */
i915_param_named(verbose_state_checks, bool, 0600,
	"Enable verbose logs (ie. WARN_ON()) in case of unexpected hw state conditions.");

i915_param_named_unsafe(nuclear_pageflip, bool, 0400,
	"Force enable atomic functionality on platforms that don't have full support yet.");

/* WA to get away with the शेष setting in VBT क्रम early platक्रमms.Will be हटाओd */
i915_param_named_unsafe(edp_vswing, पूर्णांक, 0400,
	"Ignore/Override vswing pre-emph table selection from VBT "
	"(0=use value from vbt [default], 1=low power swing(200mV),"
	"2=default swing(400mV))");

i915_param_named_unsafe(enable_guc, पूर्णांक, 0400,
	"Enable GuC load for GuC submission and/or HuC load. "
	"Required functionality can be selected using bitmask values. "
	"(-1=auto, 0=disable [default], 1=GuC submission, 2=HuC load)");

i915_param_named(guc_log_level, पूर्णांक, 0400,
	"GuC firmware logging level. Requires GuC to be loaded. "
	"(-1=auto [default], 0=disable, 1..4=enable with verbosity min..max)");

i915_param_named_unsafe(guc_firmware_path, अक्षरp, 0400,
	"GuC firmware path to use instead of the default one");

i915_param_named_unsafe(huc_firmware_path, अक्षरp, 0400,
	"HuC firmware path to use instead of the default one");

i915_param_named_unsafe(dmc_firmware_path, अक्षरp, 0400,
	"DMC firmware path to use instead of the default one");

i915_param_named_unsafe(enable_dp_mst, bool, 0400,
	"Enable multi-stream transport (MST) for new DisplayPort sinks. (default: true)");

#अगर IS_ENABLED(CONFIG_DRM_I915_DEBUG)
i915_param_named_unsafe(inject_probe_failure, uपूर्णांक, 0400,
	"Force an error after a number of failure check points (0:disabled (default), N:force failure at the Nth failure check point)");
#पूर्ण_अगर

i915_param_named(enable_dpcd_backlight, पूर्णांक, 0400,
	"Enable support for DPCD backlight control"
	"(-1=use per-VBT LFP backlight type setting [default], 0=disabled, 1=enable, 2=force VESA interface, 3=force Intel interface)");

#अगर IS_ENABLED(CONFIG_DRM_I915_GVT)
i915_param_named(enable_gvt, bool, 0400,
	"Enable support for Intel GVT-g graphics virtualization host support(default:false)");
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_DRM_I915_UNSTABLE_FAKE_LMEM)
i915_param_named_unsafe(fake_lmem_start, uदीर्घ, 0400,
	"Fake LMEM start offset (default: 0)");
#पूर्ण_अगर

#अगर CONFIG_DRM_I915_REQUEST_TIMEOUT
i915_param_named_unsafe(request_समयout_ms, uपूर्णांक, 0600,
			"Default request/fence/batch buffer expiration timeout.");
#पूर्ण_अगर

अटल __always_अंतरभूत व्योम _prपूर्णांक_param(काष्ठा drm_prपूर्णांकer *p,
					 स्थिर अक्षर *name,
					 स्थिर अक्षर *type,
					 स्थिर व्योम *x)
अणु
	अगर (!__builtin_म_भेद(type, "bool"))
		drm_म_लिखो(p, "i915.%s=%s\n", name, yesno(*(स्थिर bool *)x));
	अन्यथा अगर (!__builtin_म_भेद(type, "int"))
		drm_म_लिखो(p, "i915.%s=%d\n", name, *(स्थिर पूर्णांक *)x);
	अन्यथा अगर (!__builtin_म_भेद(type, "unsigned int"))
		drm_म_लिखो(p, "i915.%s=%u\n", name, *(स्थिर अचिन्हित पूर्णांक *)x);
	अन्यथा अगर (!__builtin_म_भेद(type, "unsigned long"))
		drm_म_लिखो(p, "i915.%s=%lu\n", name, *(स्थिर अचिन्हित दीर्घ *)x);
	अन्यथा अगर (!__builtin_म_भेद(type, "char *"))
		drm_म_लिखो(p, "i915.%s=%s\n", name, *(स्थिर अक्षर **)x);
	अन्यथा
		WARN_ONCE(1, "no printer defined for param type %s (i915.%s)\n",
			  type, name);
पूर्ण

/**
 * i915_params_dump - dump i915 modparams
 * @params: i915 modparams
 * @p: the &drm_prपूर्णांकer
 *
 * Pretty prपूर्णांकer क्रम i915 modparams.
 */
व्योम i915_params_dump(स्थिर काष्ठा i915_params *params, काष्ठा drm_prपूर्णांकer *p)
अणु
#घोषणा PRINT(T, x, ...) _prपूर्णांक_param(p, #x, #T, &params->x);
	I915_PARAMS_FOR_EACH(PRINT);
#अघोषित PRINT
पूर्ण

अटल __always_अंतरभूत व्योम dup_param(स्थिर अक्षर *type, व्योम *x)
अणु
	अगर (!__builtin_म_भेद(type, "char *"))
		*(व्योम **)x = kstrdup(*(व्योम **)x, GFP_ATOMIC);
पूर्ण

व्योम i915_params_copy(काष्ठा i915_params *dest, स्थिर काष्ठा i915_params *src)
अणु
	*dest = *src;
#घोषणा DUP(T, x, ...) dup_param(#T, &dest->x);
	I915_PARAMS_FOR_EACH(DUP);
#अघोषित DUP
पूर्ण

अटल __always_अंतरभूत व्योम मुक्त_param(स्थिर अक्षर *type, व्योम *x)
अणु
	अगर (!__builtin_म_भेद(type, "char *")) अणु
		kमुक्त(*(व्योम **)x);
		*(व्योम **)x = शून्य;
	पूर्ण
पूर्ण

/* मुक्त the allocated members, *not* the passed in params itself */
व्योम i915_params_मुक्त(काष्ठा i915_params *params)
अणु
#घोषणा FREE(T, x, ...) मुक्त_param(#T, &params->x);
	I915_PARAMS_FOR_EACH(FREE);
#अघोषित FREE
पूर्ण
