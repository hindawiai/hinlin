<शैली गुरु>
/*
 * Copyright (c) 2016 Intel Corporation
 *
 * Permission to use, copy, modअगरy, distribute, and sell this software and its
 * करोcumentation क्रम any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that copyright
 * notice and this permission notice appear in supporting करोcumentation, and
 * that the name of the copyright holders not be used in advertising or
 * खुलाity pertaining to distribution of the software without specअगरic,
 * written prior permission.  The copyright holders make no representations
 * about the suitability of this software क्रम any purpose.  It is provided "as
 * is" without express or implied warranty.
 *
 * THE COPYRIGHT HOLDERS DISCLAIM ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO
 * EVENT SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY SPECIAL, INसूचीECT OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
 * DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
 * OF THIS SOFTWARE.
 */

#अगर_अघोषित __DRM_KMS_HELPER_H__
#घोषणा __DRM_KMS_HELPER_H__

काष्ठा drm_crtc;
काष्ठा drm_crtc_funcs;
काष्ठा drm_device;
काष्ठा drm_framebuffer;
काष्ठा drm_mode_fb_cmd2;

व्योम drm_helper_move_panel_connectors_to_head(काष्ठा drm_device *);

व्योम drm_helper_mode_fill_fb_काष्ठा(काष्ठा drm_device *dev,
				    काष्ठा drm_framebuffer *fb,
				    स्थिर काष्ठा drm_mode_fb_cmd2 *mode_cmd);

पूर्णांक drm_crtc_init(काष्ठा drm_device *dev, काष्ठा drm_crtc *crtc,
		  स्थिर काष्ठा drm_crtc_funcs *funcs);

पूर्णांक drm_mode_config_helper_suspend(काष्ठा drm_device *dev);
पूर्णांक drm_mode_config_helper_resume(काष्ठा drm_device *dev);

#पूर्ण_अगर
