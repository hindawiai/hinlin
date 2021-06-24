<शैली गुरु>
/*
 * Copyright तऊ 2006 Keith Packard
 * Copyright तऊ 2007-2008 Dave Airlie
 * Copyright तऊ 2007-2008 Intel Corporation
 *   Jesse Barnes <jesse.barnes@पूर्णांकel.com>
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 * The DRM mode setting helper functions are common code क्रम drivers to use अगर
 * they wish.  Drivers are not क्रमced to use this code in their
 * implementations but it would be useful अगर they code they करो use at least
 * provides a consistent पूर्णांकerface and operation to userspace
 */

#अगर_अघोषित __DRM_CRTC_HELPER_H__
#घोषणा __DRM_CRTC_HELPER_H__

#समावेश <linux/spinlock.h>
#समावेश <linux/types.h>
#समावेश <linux/idr.h>

#समावेश <linux/fb.h>

#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_modeset_helper_vtables.h>
#समावेश <drm/drm_modeset_helper.h>

व्योम drm_helper_disable_unused_functions(काष्ठा drm_device *dev);
पूर्णांक drm_crtc_helper_set_config(काष्ठा drm_mode_set *set,
			       काष्ठा drm_modeset_acquire_ctx *ctx);
bool drm_crtc_helper_set_mode(काष्ठा drm_crtc *crtc,
			      काष्ठा drm_display_mode *mode,
			      पूर्णांक x, पूर्णांक y,
			      काष्ठा drm_framebuffer *old_fb);
bool drm_helper_crtc_in_use(काष्ठा drm_crtc *crtc);
bool drm_helper_encoder_in_use(काष्ठा drm_encoder *encoder);

पूर्णांक drm_helper_connector_dpms(काष्ठा drm_connector *connector, पूर्णांक mode);

व्योम drm_helper_resume_क्रमce_mode(काष्ठा drm_device *dev);
पूर्णांक drm_helper_क्रमce_disable_all(काष्ठा drm_device *dev);

#पूर्ण_अगर
