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
 * Authors:
 *    Rafael Antognolli <rafael.antognolli@पूर्णांकel.com>
 *
 */

#समावेश <linux/module.h>

#समावेश <drm/drm_prपूर्णांक.h>

#समावेश "drm_crtc_helper_internal.h"

MODULE_AUTHOR("David Airlie, Jesse Barnes");
MODULE_DESCRIPTION("DRM KMS helper");
MODULE_LICENSE("GPL and additional rights");

#अगर IS_ENABLED(CONFIG_DRM_LOAD_EDID_FIRMWARE)

/* Backward compatibility क्रम drm_kms_helper.edid_firmware */
अटल पूर्णांक edid_firmware_set(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp)
अणु
	DRM_NOTE("drm_kms_helper.edid_firmware is deprecated, please use drm.edid_firmware instead.\n");

	वापस __drm_set_edid_firmware_path(val);
पूर्ण

अटल पूर्णांक edid_firmware_get(अक्षर *buffer, स्थिर काष्ठा kernel_param *kp)
अणु
	वापस __drm_get_edid_firmware_path(buffer, PAGE_SIZE);
पूर्ण

अटल स्थिर काष्ठा kernel_param_ops edid_firmware_ops = अणु
	.set = edid_firmware_set,
	.get = edid_firmware_get,
पूर्ण;

module_param_cb(edid_firmware, &edid_firmware_ops, शून्य, 0644);
__MODULE_PARM_TYPE(edid_firmware, "charp");
MODULE_PARM_DESC(edid_firmware,
		 "DEPRECATED. Use drm.edid_firmware module parameter instead.");

#पूर्ण_अगर

अटल पूर्णांक __init drm_kms_helper_init(व्योम)
अणु
	/*
	 * The Kconfig DRM_KMS_HELPER selects FRAMEBUFFER_CONSOLE (अगर !EXPERT)
	 * but the module करोesn't depend on any fb console symbols.  At least
	 * attempt to load fbcon to aव्योम leaving the प्रणाली without a usable
	 * console.
	 */
	अगर (IS_ENABLED(CONFIG_DRM_FBDEV_EMULATION) &&
	    IS_MODULE(CONFIG_FRAMEBUFFER_CONSOLE) &&
	    !IS_ENABLED(CONFIG_EXPERT))
		request_module_noरुको("fbcon");

	वापस drm_dp_aux_dev_init();
पूर्ण

अटल व्योम __निकास drm_kms_helper_निकास(व्योम)
अणु
	/* Call निकास functions from specअगरic kms helpers here */
	drm_dp_aux_dev_निकास();
पूर्ण

module_init(drm_kms_helper_init);
module_निकास(drm_kms_helper_निकास);
